// GenDat.cpp : implementation file
//

#include "stdafx.h"
#include "exsylor.h"

BOOL Reduction(CBM& Matr);
void RedDom1(CBM& Matr, CBV& MaskRow,CBV& MaskCol0);
void CheckFollowRow(CBM& Matr);
void ChangeOneZero(CBM& Matr);
BOOL Cover(CBM& Matr,CBV& MaskRez,CBV& MaskCol);
void CreatMaskDom();
BOOL RedRows (CBM& Matr,CBV& MaskRow,CBV& MaskCol);
void RedRowsDom(CBM& Matr,CBV& MaskRow,CBV& MaskCol);
BOOL RedRowsDom1(CBM& Matr,CBV& MaskRow,CBV& MaskCol);
void RedCols(CBM& tm,CBV& MaskRow,CBV& MaskCol);
void FindColsZero(CBM& tm,CBV& MaskRow,CBV& MaskCol);
int ComputeNomDom(int nc);
BOOL OtherWay(CBM& MaskStepRow,CBM& MaskStepCol,CBV& MaskRow,CBV& MaskCol,
              CBV& MaskRez,CWordArray& StepColDom,int &step,int &nc);

BOOL SimpleDiz(CBM& SDiz);
void AbsorbRows(CBM& SDiz,CBV& MaskRow);
void CheckOneDom(CBM& SDiz,CBV& MaskRow);
void DelRows(CBM& SDiz,CBV& MaskRow);
int SearchSmDom(CBV& Vect1, CBV& Vect2,int nd, int& Fl);
void ComputeNewIndex(int& ind1, int& ind2, CBV& MaskRow);
BOOL PasteDom(CBV& Vect1, CBV& Vect2, CBV& VectRez, int nd);
BOOL AbsorbNewVect(CBM& SDiz, CBV& Vect, CBV& MaskRow);
int Recogn(CBM& Matr,CBM& RecMatr,CBV& RecVect,CBV& RecRez,int nd, int nv);

extern int nDoms;
extern CBM MaskDom;
extern CWordArray* DomVal;   //значность доменов
extern CWordArray* DomAdr;   //адреса доменов в строке (nDom+1 элементов)


//-------------------------------------------------------------Reduction
//  Упрощение cекционированной матрицы     
//  FALSE - результ.матрица не имеет строк или исх.м-ца вырождена
//-------------------------------------------------------------
BOOL Reduction(CBM& Matr)  
{ int i,nRow;

  CBM tm(Matr,FALSE);              //Построение трансп.матрицы
  CBV MaskCol(1,Matr.GetCountC(),TRUE);
  CBV Work(0,Matr.GetCountC(),TRUE);
  nRow = Matr.GetCountR();
  CBV MaskRow(1,nRow,TRUE);
  
//----------------------------------Редукция (1-4), построение MaskCol,MaskRow 
 
 if (Cover(Matr,Work,MaskCol)) return FALSE;
 if (Matr.IsZero())            return FALSE;        
 if (Matr.IsOne())             return FALSE;
 MaskCol.One();
 AbsorbRows(Matr,MaskRow);                //1)Редукция - поглощение строк 
 CheckOneDom(Matr,MaskRow);               //2)Редукция - в домене все "1"
 if (MaskRow.IsZero()) return FALSE;  
 RedDom1(Matr,MaskRow,MaskCol);           //3)Редукция - только в одном домене есть "1"-ы
 RedCols(tm,MaskRow,MaskCol);             //4)Редукция - поглощение столбцов внутри домена

//------------------------------------------Обнуление отмеченных столбцов
 if (!MaskCol.IsOne()) {
   Work = ~MaskCol;
   for (i=Work.LeftOne(); i>=0; i=Work.LeftOne(i))  tm.Zero(i);
   Matr = tm.Trans();
 }
 if (!MaskRow.IsOne()) DelRows(Matr,MaskRow); //Удаление отмеченных строк 
 CheckFollowRow (Matr);                       //Проверка лог.следствия строк
 ChangeOneZero (Matr);                        //Замена отдельных "1" на "0"
return TRUE;
}

//-------------------------------------------------------------RedDom1
//   Редукция (только в одном домене есть "1"-ы)                 
//-------------------------------------------------------------
void RedDom1(CBM& Matr, CBV& MaskRow,CBV& MaskCol) 
{ int i,j,k,n;
  CBV Row;
  CBV Work;
  CBM tm(Matr,FALSE);              //Построение трансп.матрицы
    
//--------------------------------------------------------Построение MaskCol  
  for (i=MaskRow.LeftOne(); i>=0; i=MaskRow.LeftOne(i)) { //цикл по строкам
    Row = Matr.GetRowBv(i) & MaskCol;
    for (j=0; j<nDoms; j++)  {           //цикл по доменам
      Work = MaskDom[j] & MaskCol;
      if (Work.IsZero()) continue;        //домен не из минора
      Work = ~(MaskDom.GetRowBv(j)) & Row;
      if (Work.IsZero()) { // найдена строка, в к-ой только в j-ом домене есть "1"-ы
        n = DomAdr->GetAt(j);
        for (k=0; k<(const int)DomVal->GetAt(j); k++) {   //изменить MaskCol
          if (MaskCol.GetBitAt(n+k)==0) continue;
          if (Row.GetBitAt(n+k)==0)  MaskCol.SetBitAt(n+k,0);
        }   
      break;
      }
    }  
  }     //цикл по строкам
}                                 

//-------------------------------------------------------------CheckFollowRow
//     Проверка логического следствия строк и удаление                
//-------------------------------------------------------------
void CheckFollowRow(CBM& Matr) 
{ int i=0,nRow;
  CBV Row;
  CBV Work;
  CBV MaskRez(0,Matr.GetCountC(),TRUE);

 nRow = Matr.GetCountR();
 while (i<nRow-1)  {
   Row = Matr.GetRowBv(i);
   Matr.RemoveRow(i);
   Work = ~Row;
   if (Cover(Matr,MaskRez,Work)) nRow--; //есть следствие
   else { Matr.InsertRow(i,Row); i++;}
 }
}

//-------------------------------------------------------------ChangeOneZero
//     Замена отдельных "1" на "0"                
//-------------------------------------------------------------
void ChangeOneZero(CBM& Matr) 
{ int i,j,nd,nRow,a;
  CBV Row;
  CBV Work;
  CBV MaskRez(0,Matr.GetCountC(),TRUE);
  
 nRow = Matr.GetCountR(); 
 for (i=0; i<nRow; i++) { //цикл по строкам
   Row = Matr.GetRowBv(i);
   for (j=Row.LeftOne(); j>=0; j=Row.LeftOne(j)) { 
     nd = ComputeNomDom(j);  //Опр-ние N домена по N столбца в строке
     Work = Row | MaskDom[nd];
     Work.SetBitAt(j,0);  Work = ~Work;
     if (a=Cover(Matr,MaskRez,Work)) 
       Matr.SetBitAt(i,j,0);   //замена "1" на "0"
     else continue;  
   }
 } //цикл по строкам
} 

//-------------------------------------------------------------Cover
//  Поиск столбцового покрытия cекционированной матрицы     
//  return TRUE - нет решения 
//-------------------------------------------------------------
BOOL Cover(CBM& Matr,CBV& MaskRez,CBV& MaskCol)  
{ int nd,nc,nRow;                   //тек.номер домена, номер столбца в строке 
  int step=0;                       //шаг поиска решения
  CWordArray StepColDom;            //номер столбца домена для шага
  nRow = Matr.GetCountR();
  CBM MaskStepRow(nDoms,nRow);     //м-ца масок строк законченных шагов поиска покрытия
  CBM MaskStepCol(nDoms,Matr.GetCountC());   //м-ца масок столбцов законченных шагов поиска покрытия 
 
  StepColDom.SetSize(nDoms+1);
//---------------------Построение начальных масок MaskRow,MaskCol
 CBM tm(Matr,FALSE);                // Построение транспонированной матрицы
 CBV MaskRow(1,nRow,TRUE);
 MaskRez.Zero();
 if (Matr.IsZero())          return TRUE;
 if (Matr.IsOne())           return TRUE;
 if (RedRows(Matr,MaskRow,MaskCol)) return TRUE;     //Редукция (поглощение строк)
 RedRowsDom(Matr,MaskRow,MaskCol);                   //Редукция (в домене все "1")
 if (MaskRow.IsZero())         return TRUE;
 if (RedRowsDom1(Matr,MaskRow,MaskCol)) return TRUE; //Редукция (только в одном домене есть "1"-ы)  
// RedCols(tm,MaskRow,MaskCol);                   //Редукция (поглощение столбцов внутри домена)
 FindColsZero(tm,MaskRow,MaskCol);              //Исключение пустых столбцов
 if (MaskCol.IsZero())         return TRUE;
 MaskStepRow.SetRow(step,MaskRow);              //Cохранение масок шага
 MaskStepCol.SetRow(step,MaskCol);
 StepColDom[0]=-1;  step++;
 nc = MaskCol.LeftOne();

//------------------------------------Основной цикл поиска решения
while (1) { 
  nd = ComputeNomDom(nc);         //Опр-ние N домена по N столбца в строке
  MaskRow &= ~tm.GetRowBv(nc);    //Исключение строк по выбранному столбцу
  if (MaskRow.IsZero())           //Решение найдено
    { MaskRez.SetBitAt(nc,1); return FALSE;} 
  MaskCol &= ~MaskDom.GetRowBv(nd);
  if (RedRows(Matr,MaskRow,MaskCol))        //выбор иного пути решения
    if (OtherWay(MaskStepRow,MaskStepCol,MaskRow,MaskCol,MaskRez,StepColDom,step,nc)) return TRUE; 
    else                      continue; 
  RedRowsDom(Matr,MaskRow,MaskCol);         //Редукция (в домене все "1")
  if (MaskRow.IsZero())                     //Решение найдено
    { MaskRez.SetBitAt(nc,1); return FALSE;}
  if (RedRowsDom1(Matr,MaskRow,MaskCol))    //Редукция (только в одном домене есть "1"-ы)
    if (OtherWay(MaskStepRow,MaskStepCol,MaskRow,MaskCol,MaskRez,StepColDom,step,nc)) return TRUE; 
    else                      continue; 
//  RedCols(tm,MaskRow,MaskCol);              //Редукция (поглощение столбцов внутри домена)
  FindColsZero(tm,MaskRow,MaskCol);         //Исключение пустых столбцов
  if (MaskCol.IsZero())
    if (OtherWay(MaskStepRow,MaskStepCol,MaskRow,MaskCol,MaskRez,StepColDom,step,nc)) return TRUE; 
    else                      continue; 
  if (step == nDoms || nd == nDoms -1)
    if (OtherWay(MaskStepRow,MaskStepCol,MaskRow,MaskCol,MaskRez,StepColDom,step,nc)) return TRUE; 
    else                      continue; 
  MaskStepRow.SetRow(step,MaskRow);         //Cохранение масок шага
  MaskStepCol.SetRow(step,MaskCol); 
  StepColDom[step]=nc;
  MaskRez.SetBitAt(nc,1);
  nc = DomAdr->GetAt(nd+1); step++;
  nc = MaskCol.LeftOne(nc-1);
 }
return FALSE;
}

//-------------------------------------------------------------CreatMaskDom
//   Построение масок для выделения доменов
//-------------------------------------------------------------
void CreatMaskDom()
{ int i,j;
  
 DomAdr->Add(0);
 for (i=0; i<nDoms; i++) DomAdr->Add(DomAdr->GetAt(i) + DomVal->GetAt(i));
   
 CBM work(nDoms,DomAdr->GetAt(nDoms),0);
 for (i=0; i<nDoms; i++)           //цикл по строкам
   for (j=0; j<(const int) DomVal->GetAt(i); j++)    //цикл по домену
     work.SetBitAt(i,j+DomAdr->GetAt(i),1);
 MaskDom = work;   
}

//-------------------------------------------------------------RedRows
//   Редукция (поглoщение строк)
//   return TRUE - найдена пустая строка
//-------------------------------------------------------------
BOOL RedRows (CBM& Matr,CBV& MaskRow,CBV& MaskCol) 
{ int i,j,Fl;
  
  for (i=MaskRow.LeftOne(); i>=0; i=MaskRow.LeftOne(i)) {
    if (Matr.IsZero((const BYTE *)MaskCol,i)) return TRUE;
    for (j=MaskRow.LeftOne(i); j>=0; j=MaskRow.LeftOne(j)) {
      Fl= Matr.CoverRow(i,j,(const BYTE *)MaskCol);
      if (Fl>0) MaskRow.SetBitAt(j,0);
      else if (Fl<0) { MaskRow.SetBitAt(i,0); break; }
    }
  }                     
  return FALSE;
} 

//-------------------------------------------------------------RedRowsDom
//   Редукция (в домене все "1")
//-------------------------------------------------------------
void RedRowsDom(CBM& Matr,CBV& MaskRow,CBV& MaskCol)
{ int i,j;
  CBV Row;
  
  for (i=MaskRow.LeftOne(); i>=0; i=MaskRow.LeftOne(i)) { //цикл по строкам
    Row = Matr.GetRowBv(i) & MaskCol;
    for (j=0; j<nDoms; j++)                                //цикл по доменам
      if ((MaskDom[j] & Row) == MaskDom[j]) { MaskRow.SetBitAt(i,0); break;}
  } 
}

//-------------------------------------------------------------RedRowsDom1
//   Редукция (только в одном домене есть "1"-ы)                 
//   return TRUE - найдена пустая строка
//-------------------------------------------------------------
BOOL RedRowsDom1(CBM& Matr,CBV& MaskRow,CBV& MaskCol) 
{ int i,j,k,n;
  CBV Row;
  CBV Work;
  
  for (i=MaskRow.LeftOne(); i>=0; i=MaskRow.LeftOne(i)) { //цикл по строкам
    Row = Matr.GetRowBv(i) & MaskCol;
    if (Row.IsZero()) return TRUE;
    for (j=0; j<nDoms; j++)  {           //цикл по доменам
      Work = MaskDom[j] & MaskCol;
      if (Work.IsZero()) continue;        //домен не из минора
      Work = ~(MaskDom.GetRowBv(j)) & Row;
      if (Work.IsZero()) { // найдена строка, в к-ой только в j-ом домене есть "1"-ы
        n = DomAdr->GetAt(j);
        for (k=0; k<(int)DomVal->GetAt(j); k++) {   //изменить MaskCol
          if (MaskCol.GetBitAt(n+k)==0) continue;
          if (Row.GetBitAt(n+k)==0)  MaskCol.SetBitAt(n+k,0);
        }   
      break;
      }
    }  
  }     //цикл по строкам
 return FALSE; 
}                                 

//-------------------------------------------------------------RedCols
//   Редукция (поглощение столбцов внутри домена)  
//-------------------------------------------------------------
void RedCols(CBM& tm,CBV& MaskRow,CBV& MaskCol)
{ int i,j,k,Fl;
   
for (i=1; i<nDoms+1; i++)  //цикл по доменам
  for(j=MaskCol.LeftOne((int)DomAdr->GetAt(i-1)-1); j<(int)DomAdr->GetAt(i) && j>=0; j=MaskCol.LeftOne(j)) //цикл по (i-1)-ому домену
    for (k=MaskCol.LeftOne(j); k<(int)DomAdr->GetAt(i) && k>0; k=MaskCol.LeftOne(k)) { 
       Fl= tm.CoverRow(j,k,(const BYTE *)MaskRow);
       if (Fl>0) MaskCol.SetBitAt(j,0);
       else if (Fl<0) { MaskCol.SetBitAt(k,0); break; }
    }
}

//-------------------------------------------------------------FindColsZero
//   Исключение пустых столбцов
//-------------------------------------------------------------
void FindColsZero(CBM& tm,CBV& MaskRow,CBV& MaskCol)
{ int i;
   
 for (i=MaskCol.LeftOne(); i>=0; i=MaskCol.LeftOne(i)) 
   if (tm.IsZero((const BYTE*) MaskRow, i)) 
     MaskCol.SetBitAt(i,0); 
}

//-------------------------------------------------------------ComputeNomDom
//   Определение N домена и столбца в домене по N столбца в строке
//-------------------------------------------------------------
int ComputeNomDom(int nc)
{ int i;

 for (i=1; i<nDoms+1; i++) 
   if (nc < (int)DomAdr->GetAt(i))  return i-1;
 return -1;  
}


//-------------------------------------------------------------OtherWay
//   Выбор иного пути решения (FALSE - путь выбран)
//-------------------------------------------------------------
BOOL OtherWay(CBM& MaskStepRow,CBM& MaskStepCol,CBV& MaskRow,CBV& MaskCol,
                         CBV& MaskRez,CWordArray& StepColDom,int &step,int &nc)
{ 
 while (1)  {
   MaskRow = MaskStepRow[step-1];  MaskCol = MaskStepCol[step-1];
   nc = MaskCol.LeftOne(nc);
   if (nc != -1)      return FALSE;
   if ((--step) == 0) return TRUE;
   nc = StepColDom[step];  MaskRez.SetBitAt(nc,0);
 }
}

/////////////////////////////////    D E D U C T ///////////////////////
//------------------------------------------------------------- SimpleDiz
//  Построение матрицы простых дизъюнктов
//  TRUE - nRow < 2
//-------------------------------------------------------------
BOOL SimpleDiz(CBM& SDiz) 
{ int i,j,nRow,nd,Fl=0;
  CBV Worki(0,SDiz.GetCountC(),TRUE);
  CBV Workj(0,SDiz.GetCountC(),TRUE);
  CBV Vect(0,SDiz.GetCountC(),TRUE);
//--------------------------Проверка поглощения строк и удаление  
 nRow = SDiz.GetCountR();
 CBV MaskRow(1,nRow,TRUE);
 AbsorbRows(SDiz,MaskRow);        //Проверка поглощения строк
 CheckOneDom(SDiz,MaskRow);       //Проверка в домене все "1"
 if (!MaskRow.IsOne())  {
   DelRows(SDiz,MaskRow);         //Удаление отмеченных строк
   nRow = SDiz.GetCountR();
   if (nRow < 2) return TRUE;
// 2007   MaskRow.GetBufferSetLength(nRow);
   MaskRow.SetSize(nRow);
   MaskRow.One();
 }  
//---------------------------------------------------------------
 i=1; j=0;
 while (i<nRow)  {
   Worki = SDiz.GetRowBv(i); 
   nd=0;
   while (j>=0)  {
    Workj = SDiz.GetRowBv(j);
    nd = SearchSmDom(Worki,Workj,nd,Fl); //Поиск смежного домена, Fl=1 - конец поиска
    if (nd < 0)                          //Смежного домена нет
      if (MaskRow.IsOne())  { nd=0; j--; continue; }  //Переход на while (j>=0)
      else break;                                    //Переход на while (i<nRow)
    else         {                              //Смежный домен найден
      if (PasteDom(Worki,Workj,Vect,nd)==FALSE)        //Склеивание двух векторов по домену nd 
        if (AbsorbNewVect(SDiz,Vect,MaskRow)==FALSE) { //Проверка поглощения нового вектора      
          nRow = SDiz.Add(Vect)+1;                     //Добавление нового вектора в матрицу 
// 2007          MaskRow.GetBufferSetLength(nRow);
          MaskRow.SetSize(nRow);
          MaskRow.SetBitAt(nRow-1,1);
        }
      if (Fl==1) { nd=0; j--;}     
      else         nd++;
    }  
   }//while (j>=0)
   if (MaskRow.IsOne())  { i++; j=i-1; continue; } 
   DelRows(SDiz,MaskRow);                    //Удаление отмеченных строк
   ComputeNewIndex(i,j,MaskRow);             //Вычисление новых i,j
   nRow = SDiz.GetCountR();
// 2007  MaskRow.GetBufferSetLength(nRow);
   MaskRow.SetSize(nRow);
   MaskRow.One();
 }//while (i<nRow)
return FALSE;  
}

//-------------------------------------------------------------AbsorbRows
//   Проверка поглощения строк
//-------------------------------------------------------------
void AbsorbRows(CBM& SDiz,CBV& MaskRow)
{ int i,j,Fl;
  
  for (i=MaskRow.LeftOne(); i>=0; i=MaskRow.LeftOne(i)) 
    for (j=MaskRow.LeftOne(i); j>=0; j=MaskRow.LeftOne(j)) {
      Fl= SDiz.CoverRow(i,j);
      if (Fl>0) MaskRow.SetBitAt(j,0);
      else if (Fl<0) { MaskRow.SetBitAt(i,0); break; }
    }
} 

//-------------------------------------------------------------CheckOneDom
//    Проверка в домене все "1"
//-------------------------------------------------------------
void CheckOneDom(CBM& SDiz,CBV& MaskRow)
{ int i,j;
 for (i=MaskRow.LeftOne(); i>=0; i=MaskRow.LeftOne(i))  //цикл по строкам
   for (j=0; j<nDoms; j++)                             //цикл по доменам
     if ((MaskDom.GetRowBv(j) & SDiz.GetRowBv(i)) == MaskDom[j]) 
       { MaskRow.SetBitAt(i,0); break;}
}


//-------------------------------------------------------------DelRows
//    Удаление строк, отмеченных в MaskRow
//-------------------------------------------------------------
void DelRows(CBM& SDiz,CBV& MaskRow)
{ int i;
 MaskRow = ~MaskRow;
 for (i=MaskRow.RightOne(); i>=0; i=MaskRow.RightOne(i)) SDiz.RemoveRow(i);       
}        
   
//-------------------------------------------------------------SearchSmDom
//    Поиск смежного домена
//-------------------------------------------------------------
int SearchSmDom(CBV& Vect1, CBV& Vect2,int nd, int& Fl)
{ int i;
  CBV Work1(0,Vect1.GetBitLength(),TRUE);
  CBV Work2(0,Vect1.GetBitLength(),TRUE);
  CBV Work(0,Vect1.GetBitLength(),TRUE);

 Fl=0; 
 for (i=nd; i<nDoms; i++) {
   Work1 = MaskDom[i] & Vect1; Work2 = MaskDom[i] & Vect2;
   Work = Work1 | Work2;
   if (Work != Work1 && Work != Work2) {
     if (Work == MaskDom[i]) Fl=1;
     return i;
   }  
 }
 return -1;
}     

//-------------------------------------------------------------ComputeNewIndex
//    Вычисление новых индексов i,j в обновленной матрице
//              (в MaskRow "1" - удаленные строки)
//-------------------------------------------------------------
void ComputeNewIndex(int& ind1, int& ind2, CBV& MaskRow)
{ int i,i1=0,j1=0,Fl=0;

 for (i=MaskRow.LeftOne(); i>=0; i=MaskRow.LeftOne(i)) {
   if (i < ind2)  j1++;
   if (i < ind1)  i1++;
   else { if (i == ind1)  Fl=1; break;}   
 }   
 ind1 -=i1;          
 if (ind1 == 0)  { ind1=1; ind2=0; return; }
 if (Fl == 1)    { ind2=ind1-1;    return; }
 ind2 -=j1+1;                                 
 if (ind2 < 0)   { ind1++; ind2=ind1-1; } 
 return;  
}

//-------------------------------------------------------------PasteDom
//    Склеивание двух векторов по домену nd
//    TRUE - VectRez имеет домен со всеми "1"
//-------------------------------------------------------------
BOOL PasteDom(CBV& Vect1, CBV& Vect2, CBV& VectRez, int nd)
{ int i;
  CBV Work(0,Vect1.GetBitLength(),TRUE);  
  
 Work = ~MaskDom.GetRowBv(nd); 
 VectRez = (Vect1 & Work) | (Vect2 & Work);
 for (i=0; i<nDoms; i++)                    //TRUE - VectRez имеет домен со всеми "1"
   if ((VectRez & MaskDom[i]) == MaskDom[i]) return TRUE;
 Work = (MaskDom[nd] & Vect1) & (MaskDom[nd] & Vect2);
 VectRez |= Work;
 return FALSE;
}

//-------------------------------------------------------------AbsorbNewVect
//    Проверка поглощения нового вектора
//    TRUE - Vect >= некоторой строке матрицы
//-------------------------------------------------------------
BOOL AbsorbNewVect(CBM& SDiz, CBV& Vect, CBV& MaskRow)
{ int i;
 for (i=MaskRow.LeftOne(); i>=0; i=MaskRow.LeftOne(i)) {
   if (SDiz[i] <= Vect)  return TRUE;  
   if (SDiz[i] > Vect)   MaskRow.SetBitAt(i,0);
 }
 return FALSE;
} 

//------------------------------------------------------------- Recogn
//  Распознавание по одному из трех режимов:
//  1) nd =-1, nv =-1 - по всем признакам,
//  2) nd = j, nv =-1 - по j-ому признаку,
//  3) nd = j, nv = i - по i-ому значению j-ого признака.
//------------------------------------------------------------------------
// Выход: 
//   -1 - RecVect противоречит исходной матрице 
//    0 - распознавание выполнено
//------------------------------------------------------------------------
int Recogn(CBM& Matr,CBM& RecMatr,CBV& RecVect,CBV& RecRez,int nd, int nv) 
{ int i,j,nRow,reg=1;
  CBM Work(Matr);
  CBV MaskRow(1,Matr.GetCountR(),TRUE);
  CBV MaskCol(1,Matr.GetCountC(),TRUE);
  CBV CoverVect(0,Matr.GetCountC(),TRUE);  
  CBV MaskRec(1,Matr.GetCountC(),TRUE);
  
//----------------------------------------Построение матрицы Work для распознавания
 for (i=0; i<Matr.GetCountR(); i++)  { 
   Work.SetRow(i, (Work.GetRowBv(i) & RecVect));
   if (Work.GetRowBv(i).IsZero()) return -1;
 }

//----------------------------------------Преобразование матрицы Work
 if (RedRows(Work,MaskRow,MaskCol)) return -1;       //Редукция (поглощение строк)
 RedRowsDom(Work,MaskRow,MaskCol);                   //Редукция (в домене все "1")
 if (MaskRow.IsZero())              return -1;
 if (RedRowsDom1(Work,MaskRow,MaskCol)) return -1;   //Редукция (только в одном домене есть "1"-ы)  
 DelRows(Work,MaskRow);         //Удаление отмеченных строк
 nRow = Work.GetCountR();
 MaskCol.One();
 if (Cover(Work,CoverVect,MaskCol)) return -1;       //Проверка выполнимости
 CoverVect.Zero(); 

//----------------------------------------Определение режима распознавания
 RecRez = RecVect;
 if (nd >= 0 && nv < 0)    reg=2; 
 else 
   if (nd >= 0 && nv >= 0) reg = 3;
 switch (reg) {
  case 1: // распознавание по всем признакам
          for (i=0; i<nDoms; i++) 
            for (j=0; j<(int)DomVal->GetAt(i); j++)  {
              MaskRec = MaskDom[i];
              MaskRec.SetBitAt(DomAdr->GetAt(i)+j,0);
              MaskRec = ~MaskRec;  CoverVect.Zero();
              if (Cover(Work,CoverVect,MaskRec)) RecRez.SetBitAt(DomAdr->GetAt(i)+j,0);
              else RecMatr.SetRow(DomAdr->GetAt(i)+j,CoverVect); 
            }
          break;
  case 2: // распознавание по j-ому признаку
          for (j=0; j<(int)DomVal->GetAt(nd); j++)  {
            MaskRec = MaskDom[nd];
            MaskRec.SetBitAt(DomAdr->GetAt(nd)+j,0);
            MaskRec = ~MaskRec;   CoverVect.Zero();
            if (Cover(Work,CoverVect,MaskRec)) RecRez.SetBitAt(DomAdr->GetAt(nd)+j,0);
            else RecMatr.SetRow(DomAdr->GetAt(nd)+j,CoverVect); 
          }
          break;
  case 3: // распознавание по i-ому значению j-ого признака
          MaskRec = MaskDom[nd];
          MaskRec.SetBitAt(DomAdr->GetAt(nd) + nv,0);
          MaskRec = ~MaskRec;    CoverVect.Zero();      
          if (Cover(Work,CoverVect,MaskRec)) RecRez.SetBitAt(DomAdr->GetAt(nd)+nv,0);
          else RecMatr.SetRow(DomAdr->GetAt(nd)+nv,CoverVect); 
 }
 return 0;
} 

