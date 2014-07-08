// Induct.cpp : implementation file
//

#include <math.h>
#include "ScrDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

void gen_diz(CBM& MatrCon, CBM& MatrDis, CBM& msk_une, char *kol_one);
int countbit(unsigned short x);
void ChangeDom(CBV& Vect, int k, unsigned short mask);

extern int nDoms;
extern CBM MaskDom;
extern CWordArray* DomVal;   //значность доменов
extern CWordArray* DomAdr;   //адреса доменов в строке (nDom+1 элементов)


//-----------------------------------------------------------countbit 
int countbit(unsigned short x)
{ static unsigned char tbz[257] =
 { 0,1,1,2,1,2,2,3,1,2,2,3,2,3,3,4,
   1,2,2,3,2,3,3,4,2,3,3,4,3,4,4,5,
   1,2,2,3,2,3,3,4,2,3,3,4,3,4,4,5,
   2,3,3,4,3,4,4,5,3,4,4,5,4,5,5,6,
   1,2,2,3,2,3,3,4,2,3,3,4,3,4,4,5,
   2,3,3,4,3,4,4,5,3,4,4,5,4,5,5,6,
   2,3,3,4,3,4,4,5,3,4,4,5,4,5,5,6,
   3,4,4,5,4,5,5,6,4,5,5,6,5,6,6,7,
   1,2,2,3,2,3,3,4,2,3,3,4,3,4,4,5,
   2,3,3,4,3,4,4,5,3,4,4,5,4,5,5,6,
   2,3,3,4,3,4,4,5,3,4,4,5,4,5,5,6,
   3,4,4,5,4,5,5,6,4,5,5,6,5,6,6,7,
   2,3,3,4,3,4,4,5,3,4,4,5,4,5,5,6,
   3,4,4,5,4,5,5,6,4,5,5,6,5,6,6,7,
   3,4,4,5,4,5,5,6,4,5,5,6,5,6,6,7,
   4,5,5,6,5,6,6,7,5,6,6,7,6,7,7,8 };
   return (tbz[x>>8] + tbz[x&255]);
}

/*--------------------------------*/
/*  Индукция нового блока знаний  */
/*--------------------------------*/

unsigned short *d1;           /* начальные значения доменов */
unsigned short *d2;           /* текущие значения доменов */

BOOL CScriptDoc::Induct(CBM& MatrCon,CBM& MatrDis)
{ CBM msk_une(MaskDom);
  CDiaInd dlg;              // Dialog for getting parameters
  int Flag;                 // For checking the empty rank level 

//-------------------------------
  CString W00(theApp.BazePath);
  int Num00 = 1;
  W00 += "prob.txt";
  char buff[200];
  CFile f;
  if( !f.Open( (const char *)W00, CFile::modeCreate | CFile::modeWrite )) {
    CString W1; W1.LoadString(IDS_ERROR_FILE); W1+=W00;
    AfxMessageBox(W1); return FALSE;
  }
//-------------------------------
    
  char *kol_one, buf[30];            // Array of allocation of "1" 
  int k1, i, i1, j, j1, sum;
  double *p[200], bounds[7], New0, New_s;
  MSG msg;
  HCURSOR hcur;
  hcur = ::SetCursor(::LoadCursor(NULL,IDC_WAIT));
  k1 = ind_bound(bounds, 7);
  ::SetCursor(hcur);
  
 msk_une = ~MaskDom;        // Invert mask for attributes
 kol_one=(char *)malloc(nDoms);     

// 1. ---------- Counting the probability array
 j1 = 0;  
 for (i=0; i<nDoms; i++) {
   k1 = DomVal->GetAt(i);
   p[i]=(double *)malloc(k1 * sizeof(double));
   //for (j=0; j<k1; j++)   p[i][j]=(double)(k1-j)/(double)k1;
   for (j=0; j<k1; j++)    p[i][j]= 1 - (double)(j)/(double)k1;
 }
 
//------------------------------- Взвешивание влияния доменов
//  double domens[10],ddd,dww1,dww2;
//  ddd = 1.0;
//  for (i=0; i<nDoms; i++) ddd *= (double)DomVal->GetAt(i); // П ai = 
//  dww2 = 1.0 /(double)nDoms;
//  dww1 = 1.0 /ddd;
//  ddd = pow(dww1,dww2);
//  for (i=0; i<nDoms; i++) domens[i]= (double)DomVal->GetAt(i) * ddd;
//  ddd = 1.0;
//  for (i=0; i<nDoms; i++) ddd *=domens[i];
//
//-------------------------------
 
 
 
// 2.---------- Preparing of induction
  d1=(unsigned short *)malloc(nDoms*4);
  d2=d1+nDoms;
  FactRank = 1;
  memset(kol_one,0,nDoms);
  
// 3. --------------------- Input limit parameters
 sprintf(buf,"%6.2lf",bounds[0]*100.);
 dlg.m_1 = buf;
 sprintf(buf,"%6.2lf",bounds[1]*100.);
 dlg.m_2 = buf;
 sprintf(buf,"%6.2lf",bounds[2]*100.);
 dlg.m_3 = buf;
 sprintf(buf,"%6.2lf",bounds[3]*100.);
 dlg.m_4 = buf;
 sprintf(buf,"%6.2lf",bounds[4]*100.);
 dlg.m_5 = buf;
 sprintf(buf,"%6.2lf",bounds[5]*100.);
 dlg.m_6 = buf;
 sprintf(buf,"%6.2lf",bounds[6]*100.);
 dlg.m_7 = buf;
  
 if (dlg.DoModal() == IDCANCEL) return FALSE;
 Rank = MatrCon.GetCountC()-nDoms - 1;
 if (dlg.m_chRank && (dlg.m_Rank <Rank)) Rank = dlg.m_Rank; 
 if (dlg.m_chNumber)  Numb = dlg.m_Number;
 else Numb = 2000;
 if (dlg.m_chProb)    Prob = bounds[6-(dlg.m_Power-1)];
 else Prob = 0.0;

// 4. ------------------------------Open visualisation of work

 //  strtime(buf);
 //  sprintf (buf,"%4.3f",Gr);
 Num_Con = MatrCon.GetCountR();
 FactRank = 1;
 FactNum  = 0;
 FactProb = 1.0;
 CMainFrame* pFrameWnd = (CMainFrame*)theApp.m_pMainWnd;
 pFrameWnd-> CreateOrActivateFrame(theApp.pViewIndTemplate, RUNTIME_CLASS(CFormInd));
 UpdateAllViews(NULL,NULL,NULL);
   
// 5. -------------------------------Main loop
 Flag = 1;
 for ( ; FactRank <= Rank; FactRank++) {
   i=0; sum = FactRank; 
   if (Flag == 0 && MatrDis.GetCountR()) goto kon; // Check empty loop for rank level
   Flag = 0;
wh:
   while (PeekMessage(&msg, hTable, 0, 0, PM_REMOVE)) {
     if (msg.message == WM_LBUTTONDOWN) goto kon;  
     DispatchMessage(&msg);
   }
   for (i1=i;i1<nDoms;i1++) kol_one[i1]=0;        // "1" allocation to domens
   while (sum>=(const int)DomVal->GetAt(i)-1) {
     kol_one[i]=(const int)DomVal->GetAt(i)-1; 
     sum-=(const int)DomVal->GetAt(i)-1; i++;
     if (i>=nDoms) break;
   }
   if (i>=nDoms && sum!=0) continue;
   if (sum) kol_one[i]=sum;
   
   FactProb =1.0; New0 = 0.0; New_s=0;
   
   for (j=0; j<nDoms; j++) {
     FactProb*=p[j][kol_one[j]];       // Count current probability 
     if (kol_one[j] == 0) continue;
     New0 +=(int)DomVal->GetAt(j);  New_s++;/////////////
   }
   
   //FactProb = (FactProb*(MaskDom.GetCountC()-New0+1))/((MaskDom.GetCountC()*New0)/New_s);
   FactProb = FactProb/pow(New0/New_s,1.0/nDoms);
//---------------------     
    sprintf(buff,"%6u:: ",Num00++);f.Write(buff,lstrlen(buff));
    for (j=0; j<nDoms; j++) 
      if (kol_one[j]==0) f.Write("_ ",2);
      else { sprintf(buff,"%u ",kol_one[j]); f.Write(buff,lstrlen(buff)); }
    sprintf(buff," = %5.2lf\n",FactProb*100.0); f.Write(buff,lstrlen(buff));
//---------------------          
   
   if (FactProb>=Prob) {  // Limit probability check
     Flag = 1;


     gen_diz(MatrCon, MatrDis, msk_une,kol_one); // Generation hypothethis

     FactNum = MatrDis.GetCountR();
     UpdateAllViews(NULL,1213456789L,NULL);
     if (MatrDis.GetCountR() > Numb) goto kon;
   }
      
   i=nDoms-1; sum=0;
   if (kol_one[i] == (const int)DomVal->GetAt(i)-1)
     while (kol_one[i]==(const int)DomVal->GetAt(i)-1) {sum+=kol_one[i]; i--;}
   sum+=kol_one[i]; i--;
   while (kol_one[i]==0) {i--; if (i<0) continue; }
   if (i<0) continue;
   kol_one[i]--; sum++; i++; goto wh;
 }  // Enf of main loop
kon:
  free(d1);     for(i=nDoms-1;i>=0;i--) free(p[i]);      free(kol_one);

  CMDIChildWnd* pMDIActive = pFrameWnd->MDIGetActive();
  if (pMDIActive != NULL) pMDIActive->MDIDestroy();
  if (MatrDis.IsEmpty()) return FALSE;
  return TRUE;
}
 
/*------------------------------------------------------------------*/
/*  Программа генерации дизьюнктов по заданному распределению "1"   */
/*                            GEN_DIZ                               */
/*------------------------------------------------------------------*/

void gen_diz(CBM& MatrCon, CBM& MatrDis, CBM& msk_une, char *kol_one)
{ int i,j,k;
  unsigned short d3;
  char a;
  CBV Vect(0,MatrCon.GetCountC(),1);    /* дизьюнкт */

 for (k=0; k<nDoms; k++) {
   if (kol_one[k]==0) { d1[k]=0; d2[k]=0;   }
   else               d1[k]=(1<<kol_one[k])-1;
 }

 for (k=0; k<nDoms; k++)            /* построение начального вектора */
   for (i=0; i<(const int)DomVal->GetAt(k); i++) 
     if(d1[k] & (1<<i)) Vect.SetBitAt((const int)DomAdr->GetAt(k)+i,1);

 for (k=0; k<nDoms; k++)
    if(kol_one[k] !=0)
      { d1[k]=d1[k]<<((const int)DomVal->GetAt(k)-kol_one[k]); d2[k]=d1[k]; }
      
 for (i=0; i<MatrDis.GetCountR(); i++)   /*  Проверка на поглощение  */
   if (MatrDis[i]<=Vect) goto next;
 for (i=0; i<MatrCon.GetCountR(); i++)   /*  Проверка на противоречие  */ 
   if ((MatrCon[i] & Vect).IsZero()) goto next;   /* есть противоречие */
 MatrDis.Add(Vect);  
/*----------------------------------------------------------------------*/

next:
 for (k=0; k<nDoms; k++)
   if (kol_one[k]==0) continue;      /* поиск первого ненулевого домена */
   else break;
 if (k==nDoms) goto kon;
/* Генерация очередного домена по алгоритму Уткина А.А.*/
gen:
 d3=(d2[k]+1)^d2[k];  a=countbit(d3);
 d2[k]=d2[k]>>a;    d3=(~d2[k]+1)&d2[k];  d2[k]=(d2[k]<<a)-d3;
/*-----------------------------------------------------*/
 if (d2[k] !=0)   {                        /* не все домены получены    */
   ChangeDom(Vect,k,d2[k]);
   for (i=0; i<MatrDis.GetCountR(); i++)   /*  Проверка на поглощение   */
     if (MatrDis[i]<=Vect) goto gen;               /* есть поглощение   */
   for (i=0; i<MatrCon.GetCountR(); i++)   /*  Проверка на противоречие */ 
     if ((MatrCon[i] & Vect).IsZero()) goto gen;   /* есть противоречие */
   MatrDis.Add(Vect);  
   goto gen;
 }
/* Генерация k-ого домена завершена */
 if(k==nDoms-1) goto kon;
 d2[k]=d1[k];                   
 ChangeDom(Vect,k,d2[k]);      /*  Корректировка вектора  */
 
 for (j=k+1; j<nDoms; j++)  { /* цикл по j */
   if(kol_one[j] == 0) continue;
/* Генерация очередного домена */
   d3=(d2[j]+1)^d2[j];     a=countbit(d3);
   d2[j]=d2[j]>>a;  d3=(~d2[j]+1)&d2[j];  d2[j]=(d2[j]<<a)-d3;
/*--------------------------------------------------------------*/
   if(d2[j] !=0)   {  /* не все домены получены */
     ChangeDom(Vect,j,d2[j]);      /*  Корректировка вектора  */
     for (i=0; i<MatrDis.GetCountR(); i++)   /*  Проверка на поглощение   */
       if (MatrDis[i]<=Vect) goto gen;               /* есть поглощение   */
     for (i=0; i<MatrCon.GetCountR(); i++)   /*  Проверка на противоречие */ 
       if ((MatrCon[i] & Vect).IsZero()) goto gen;   /* есть противоречие */
     MatrDis.Add(Vect);  
     goto gen;
   }
   d2[j]=d1[j];
/*  Корректировка вектора  */
   ChangeDom(Vect,j,d2[j]);      /*  Корректировка вектора  */
 } /* цикл по j */
kon:
 return;
}

//-----------------------------------------------------------ChangeDom
void ChangeDom(CBV& Vect, int k, unsigned short mask)
{ int i;
 for (i=0; i<(const int)DomVal->GetAt(k); i++) 
   Vect.SetBitAt((const int)DomAdr->GetAt(k)+(const int)DomVal->GetAt(k)-i-1,(mask & (1<<i)));
}

//-----------------------------------------------------------------------------
int CScriptDoc::ind_bound(double * bound, int n )
{ int k,k1,i,i1,i2,j1,j,sum;
  //unsigned long qsum,q1,q2,*qn,tsum=0L;
  int g_qn,N;
  char b[100];
  double  New0, New_s; // *New,
  double *p[100],  p1; // *pn,
  double qsum,q1,q2,tsum=0; //*qn,

  double pn[2000], qn[2000], New[2000];
//  if ((pn=(double *)malloc(2000*sizeof(double)))==NULL) {
//err5: AfxMessageBox ("Not memory"); return(-1);
//  }   

//  if ((qn=(double *)malloc(2000*sizeof(double)))==NULL) goto err5;
//  if ((New=(double *)malloc(2000*sizeof(double)))==NULL) goto err5;
  
  p1 = 0.00000001;  for (i=0; i<n; i++) bound[i]=p1*=10.0;   
  g_qn=0;
/*==============================================================================*/
  for (i=0; i<nDoms; i++) {
    k1 = DomVal->GetAt(i);
    if ((p[i]=(double *)malloc(k1*sizeof(double)))==NULL) //goto err5;
    {  AfxMessageBox ("Not memory"); return(-1); }
    for (j=0; j<k1; j++) 
      p[i][j]=(double)(k1-j)/(double)k1;
  }
  memset (b,0,nDoms);  
  for (i=0; i<2000; i++) { pn[i]=0.0; New[i]=0.0; }
  qn[0]=0;
/*==============================================================================*/
 for (N=1; N<MaskDom.GetCountC() - nDoms; N++) { 
  i=i2=0; sum=N;
wh:
  for (i1=i;i1<nDoms;i1++) b[i1]=0;
  while (sum>=(int)DomVal->GetAt(i)-1) { 
    b[i]=(int)DomVal->GetAt(i)-1; sum-=(int)DomVal->GetAt(i)-1; i++;
    if (i>=nDoms) break;
  }
  if (i>=nDoms && sum!=0) continue;
  if (sum) b[i]=sum;
  p1=1; qsum=1.;
  for (k=0; k<nDoms; k++) 
    p1*=p[k][b[k]];          
  if (p1 >= 0.05) {
    i2++; New0 = 0.0;New_s=0;
    for (k=0; k<nDoms; k++) {
      q1=q2=1.0;
      if (b[k]==0) continue;
      New0 +=(int)DomVal->GetAt(k);  New_s++;/////////////
      for (k1=(int)DomVal->GetAt(k);k1>(int)DomVal->GetAt(k)-b[k]; k1--) q2*=(double)k1;
      for (k1=1;k1<=b[k]; k1++)          q1*=(double)k1;
      qsum*=q2/q1;
    }
/*===========================================================================*/
    //New0 = (p1*(MaskDom.GetCountC()-New0+1))/((MaskDom.GetCountC()*New0)/New_s);
    New0 = p1/pow(New0/New_s,1.0/nDoms);
    tsum +=qsum;
    j1=0;
    while (p1<pn[j1]) j1++;
    if (p1 == pn[j1]) {
       while (p1 == pn[j1] && New0!=New[j1]) j1++;
       if (p1 == pn[j1]) {
         if (New0 == New[j1]) {
          qn[j1]+=qsum; 
          goto hod;
         }
       }  
    }
    if(g_qn == 1999) g_qn--;
    k1=g_qn-j1;
    memmove(pn+j1+1,pn+j1,k1*sizeof(double));
    memmove(qn+j1+1,qn+j1,k1*sizeof(double));
    memmove(New+j1+1,New+j1,k1*sizeof(double));
    
    New[j1]=New0;    pn[j1]=p1;    qn[j1]=qsum;    g_qn++;
  } /* if ­  Gr=0.05 */
hod:
  i=nDoms-1; sum=0;
  if (b[i] == (int)DomVal->GetAt(i)-1)
    while (b[i]==(int)DomVal->GetAt(i)-1) {sum+=b[i]; i--;}
  sum+=b[i]; i--;
  while (b[i]==0) {i--; if (i<0) goto kon1; }
  if (i<0) goto kon1;
  b[i]--; sum++; i++; goto wh;
kon1:
  if(i2==0)  break;
 }  // Main loop

 for (i=0; i<g_qn-1; i++) {
   i2=i; New0=New[i];
   for (j1=i+1; j1<g_qn; j1++) {
     if (New[j1] > New0) {New0=New[j1];i2=j1; }
   }
   if (i2!=i) {
     New[i2] = New[i];  New[i] = New0;
     New0 = pn[i2]; pn[i2] = pn[i]; pn[i] = New0;
     New0 = qn[i2]; qn[i2] = qn[i]; qn[i] = New0;
   }
 }
 n = Mat(n,bound,g_qn,pn,qn,New);  

 for (i=0; i<nDoms; i++)   free(p[nDoms-i-1]);
// free(bound);
// free(qn); free(pn); free(b);
 return(n);
}

//-----------------------------------------------------------------------------
int CScriptDoc::Mat(int n,double *bound,int kol,double *pn,double *qn, double * New)
{
  double a,b,c,d,M,M_P=0.0,p11;
  int i,j=0,q=0;
  //-------------------------------
  CString W00(theApp.BazePath);
  int Num00 = 1;
  W00 += "Expect.txt";
  char buff[200];
  CFile f;
  if( !f.Open( (const char *)W00, CFile::modeCreate | CFile::modeWrite )) {
    CString W1; W1.LoadString(IDS_ERROR_FILE); W1+=W00;
    AfxMessageBox(W1); return FALSE;
  }
//-------------------------------
  for (i=0; i<kol; i++) {
    a= qn[i]; b= (double)m_pSamples.GetSize(); c= 1.0 - (double)pn[i];
    d= b*log(c)+log(a); M= exp(d);  M_P +=M;
m1: if (M_P<bound[j]) { 
      q=1; 
//---------------------     
      sprintf(buff,"%3u:",Num00++);f.Write(buff,lstrlen(buff));
      sprintf(buff,"%7.3lf :%8.0lf :%5.2lf :%8.6lf :%10.8lf\n",
              pn[i]*100.0,qn[i],New[i]*100.0,M,M_P);
      f.Write(buff,lstrlen(buff)); 
//---------------------          
      continue;
    }
    if (q==0 || i==0) p11=1.0;  else p11=New[i-1];

//---------------------     
    sprintf(buff,"--------------------------------------------------\n"); 
    f.Write(buff,lstrlen(buff));
//---------------------          
    
    bound[j] = p11; j++; if (j>=n) break;
    goto m1;
  }
 return (j); 
}
