; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CSettingDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "Graphic.h"
LastPage=0

ClassCount=6
Class1=CGraphicApp
Class2=CGraphicDoc
Class3=CGraphicView
Class4=CMainFrame

ResourceCount=7
Resource1=IDR_TOOLBAR2
Class5=CAboutDlg
Resource2=IDR_MAINFRAME
Class6=CSettingDlg
Resource3=IDD_ABOUTBOX
Resource4=IDR_ACCELERATOR1
Resource5=IDR_TOOLBAR3
Resource6=IDR_TOOLBAR1
Resource7=IDD_DLG_SETTING

[CLS:CGraphicApp]
Type=0
HeaderFile=Graphic.h
ImplementationFile=Graphic.cpp
Filter=N

[CLS:CGraphicDoc]
Type=0
HeaderFile=GraphicDoc.h
ImplementationFile=GraphicDoc.cpp
Filter=N

[CLS:CGraphicView]
Type=0
HeaderFile=GraphicView.h
ImplementationFile=GraphicView.cpp
Filter=C
BaseClass=CScrollView
VirtualFilter=VWC
LastObject=IDM_SETTING


[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T
LastObject=IDM_LINE




[CLS:CAboutDlg]
Type=0
HeaderFile=Graphic.cpp
ImplementationFile=Graphic.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[MNU:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_SAVE_AS
Command5=ID_FILE_PRINT
Command6=ID_FILE_PRINT_PREVIEW
Command7=ID_FILE_PRINT_SETUP
Command8=ID_FILE_MRU_FILE1
Command9=ID_APP_EXIT
Command10=ID_EDIT_UNDO
Command11=ID_EDIT_CUT
Command12=ID_EDIT_COPY
Command13=ID_EDIT_PASTE
Command14=ID_VIEW_TOOLBAR
Command15=ID_VIEW_STATUS_BAR
Command16=ID_APP_ABOUT
Command17=IDM_DOT
Command18=IDM_LINE
Command19=IDM_RECTANGLE
Command20=IDM_ELLIPSE
Command21=IDM_SETTING
Command22=IDM_COLOR
CommandCount=22

[ACL:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_PRINT
Command5=ID_EDIT_UNDO
Command6=ID_EDIT_CUT
Command7=ID_EDIT_COPY
Command8=ID_EDIT_PASTE
Command9=ID_EDIT_UNDO
Command10=ID_EDIT_CUT
Command11=ID_EDIT_COPY
Command12=ID_EDIT_PASTE
Command13=ID_NEXT_PANE
Command14=ID_PREV_PANE
CommandCount=14

[TB:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_EDIT_CUT
Command5=ID_EDIT_COPY
Command6=ID_EDIT_PASTE
Command7=ID_FILE_PRINT
Command8=ID_APP_ABOUT
CommandCount=8

[DLG:IDD_DLG_SETTING]
Type=1
Class=CSettingDlg
ControlCount=9
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_LINE_WIDTH,edit,1350631552
Control5=IDC_LINESTYLE_STATIC,button,1342177287
Control6=IDC_RADIO1,button,1342308361
Control7=IDC_RADIO2,button,1342177289
Control8=IDC_RADIO3,button,1342177289
Control9=IDC_SAMPLE,button,1342177287

[CLS:CSettingDlg]
Type=0
HeaderFile=SettingDlg.h
ImplementationFile=SettingDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=IDC_RADIO3
VirtualFilter=dWC

[ACL:IDR_ACCELERATOR1]
Type=1
Class=?
Command1=IDR_DRAWTOOLS
CommandCount=1

[TB:IDR_TOOLBAR1]
Type=1
Class=?
CommandCount=0

[TB:IDR_TOOLBAR2]
Type=1
Class=?
CommandCount=0

[TB:IDR_TOOLBAR3]
Type=1
Class=?
CommandCount=0

