# Microsoft Developer Studio Project File - Name="Exsylor" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=Exsylor - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "Exsylor.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Exsylor.mak" CFG="Exsylor - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Exsylor - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "Exsylor - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Exsylor - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /D "_JOINT" /FD /c
# SUBTRACT CPP /YX /Yc /Yu
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x419 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x419 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "Exsylor - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "../bin/Debug"
# PROP Intermediate_Dir "../bin/Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /D "_JOINT" /FD /GZ /c
# SUBTRACT CPP /YX /Yc /Yu
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x419 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x419 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "Exsylor - Win32 Release"
# Name "Exsylor - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\BlockSelDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\Bm.cpp
# End Source File
# Begin Source File

SOURCE=.\Bmview.cpp
# End Source File
# Begin Source File

SOURCE=.\Brtitle.cpp
# End Source File
# Begin Source File

SOURCE=.\Brview.cpp
# End Source File
# Begin Source File

SOURCE=.\Bv.cpp
# End Source File
# Begin Source File

SOURCE=.\Bvview.cpp
# End Source File
# Begin Source File

SOURCE=.\ChildFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\DiaInd.cpp
# End Source File
# Begin Source File

SOURCE=.\EditNameDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\Exsylor.cpp
# End Source File
# Begin Source File

SOURCE=.\Exsylor.rc
# End Source File
# Begin Source File

SOURCE=.\FormInd.cpp
# End Source File
# Begin Source File

SOURCE=.\GenDat.cpp
# End Source File
# Begin Source File

SOURCE=.\Gener.cpp
# End Source File
# Begin Source File

SOURCE=.\GenKnow.cpp
# End Source File
# Begin Source File

SOURCE=.\Induct.cpp
# End Source File
# Begin Source File

SOURCE=.\Linkuser.cpp
# End Source File
# Begin Source File

SOURCE=.\MainFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\ModDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\Modview.cpp
# End Source File
# Begin Source File

SOURCE=.\Proof.cpp
# End Source File
# Begin Source File

SOURCE=.\Reduction.cpp
# End Source File
# Begin Source File

SOURCE=.\ScrDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\ScrDocEx.cpp
# End Source File
# Begin Source File

SOURCE=.\ScrDocExpImp.cpp
# End Source File
# Begin Source File

SOURCE=.\Scrdocmd.cpp
# End Source File
# Begin Source File

SOURCE=.\ScrDocRg.cpp
# End Source File
# Begin Source File

SOURCE=.\ScrDocSM.cpp
# End Source File
# Begin Source File

SOURCE=.\ScrInit.cpp
# End Source File
# Begin Source File

SOURCE=.\Scriptvw.cpp
# End Source File
# Begin Source File

SOURCE=.\ScrObj.cpp
# End Source File
# Begin Source File

SOURCE=.\Splitter.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\Trbzview.cpp
# End Source File
# Begin Source File

SOURCE=.\Treeview.cpp
# End Source File
# Begin Source File

SOURCE=.\Wordview.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\BaseBool.h
# End Source File
# Begin Source File

SOURCE=.\BlockSelDlg.h
# End Source File
# Begin Source File

SOURCE=.\Bmview.h
# End Source File
# Begin Source File

SOURCE=.\Brtitle.h
# End Source File
# Begin Source File

SOURCE=.\Brview.h
# End Source File
# Begin Source File

SOURCE=.\Bvview.h
# End Source File
# Begin Source File

SOURCE=.\ChildFrm.h
# End Source File
# Begin Source File

SOURCE=.\coverdoc.h
# End Source File
# Begin Source File

SOURCE=.\DiaInd.h
# End Source File
# Begin Source File

SOURCE=.\EditNameDlg.h
# End Source File
# Begin Source File

SOURCE=.\Exsylor.h
# End Source File
# Begin Source File

SOURCE=.\ExsylorDoc.h
# End Source File
# Begin Source File

SOURCE=.\FormInd.h
# End Source File
# Begin Source File

SOURCE=.\GenDat.h
# End Source File
# Begin Source File

SOURCE=.\GenKnow.h
# End Source File
# Begin Source File

SOURCE=.\MainFrm.h
# End Source File
# Begin Source File

SOURCE=.\ModDlg.h
# End Source File
# Begin Source File

SOURCE=.\Modview.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\ScrDoc.h
# End Source File
# Begin Source File

SOURCE=.\Scriptvw.h
# End Source File
# Begin Source File

SOURCE=.\Splitter.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\Trbzview.h
# End Source File
# Begin Source File

SOURCE=.\Treeview.h
# End Source File
# Begin Source File

SOURCE=.\Wordview.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\bitmap1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bitmap10.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bitmap11.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bitmap12.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bitmap13.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bitmap14.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bitmap15.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bitmap16.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bitmap2.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bitmap3.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bitmap4.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bitmap5.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bitmap6.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bitmap7.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bitmap8.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bitmap9.bmp
# End Source File
# Begin Source File

SOURCE=.\res\direct.ico
# End Source File
# Begin Source File

SOURCE=.\res\empt.ico
# End Source File
# Begin Source File

SOURCE=.\res\empty.bmp
# End Source File
# Begin Source File

SOURCE=.\res\explan.bmp
# End Source File
# Begin Source File

SOURCE=.\res\exstype.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Exsylor.ico
# End Source File
# Begin Source File

SOURCE=.\res\Exsylor.rc2
# End Source File
# Begin Source File

SOURCE=.\res\ExsylorDoc.ico
# End Source File
# Begin Source File

SOURCE=.\res\reg.ico
# End Source File
# Begin Source File

SOURCE=.\res\reg_edit.bmp
# End Source File
# Begin Source File

SOURCE=.\res\reg_scri.bmp
# End Source File
# Begin Source File

SOURCE=.\res\regu.ico
# End Source File
# Begin Source File

SOURCE=.\res\scri.ico
# End Source File
# Begin Source File

SOURCE=.\res\scroptty.bmp
# End Source File
# Begin Source File

SOURCE=.\res\system.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Toolbar.bmp
# End Source File
# Begin Source File

SOURCE=.\res\word.ico
# End Source File
# Begin Source File

SOURCE=.\res\word_ed.ico
# End Source File
# Begin Source File

SOURCE=.\res\word_edi.bmp
# End Source File
# Begin Source File

SOURCE=.\res\word_scr.bmp
# End Source File
# End Group
# Begin Source File

SOURCE=.\Exsylor.reg
# End Source File
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
