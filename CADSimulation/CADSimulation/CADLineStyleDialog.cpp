// CADLineStyleDialog.cpp : implementation file
//

#include "stdafx.h"
#include "CADSimulation.h"
#include "CADLineStyleDialog.h"
#include "afxdialogex.h"


// CCADLineStyleDialog dialog

IMPLEMENT_DYNAMIC(CCADLineStyleDialog, CDialog)

CCADLineStyleDialog::CCADLineStyleDialog(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_DIALOG_LINESTYLE, pParent)
  , m_nPenWidth(0)
  , m_nPenStyle(0)
{

}

CCADLineStyleDialog::~CCADLineStyleDialog()
{
}

void CCADLineStyleDialog::DoDataExchange(CDataExchange* pDX)
{
  CDialog::DoDataExchange(pDX);
  DDX_Control(pDX, IDC_SLIDER1, m_sldCtrl);
  DDX_Text(pDX, IDC_EDIT2, m_nPenWidth);
  DDX_Radio(pDX, IDC_RADIO1, m_nPenStyle);
  DDX_Control(pDX, IDC_BUTTON_LINE_STYLE_COLOR, m_colorButton);
}


BEGIN_MESSAGE_MAP(CCADLineStyleDialog, CDialog)
  ON_BN_CLICKED(IDC_BUTTON_OK, &CCADLineStyleDialog::OnBnClickedButtonOk)
  ON_BN_CLICKED(IDC_BUTTON_LINE_STYLE_CANCEL, &CCADLineStyleDialog::OnBnClickedButtonLineStyleCancel)
  ON_BN_CLICKED(IDC_BUTTON_LINE_STYLE_COLOR, &CCADLineStyleDialog::OnBnClickedButtonLineStyleColor)
  ON_WM_CREATE()
  ON_WM_HSCROLL()
//   ON_BN_CLICKED(IDC_RADIO1, &CCADLineStyleDialog::OnBnClickedRadio1)
//   ON_BN_CLICKED(IDC_RADIO2, &CCADLineStyleDialog::OnBnClickedRadio2)
//   ON_BN_CLICKED(IDC_RADIO3, &CCADLineStyleDialog::OnBnClickedRadio3)
END_MESSAGE_MAP()


// CCADLineStyleDialog message handlers


void CCADLineStyleDialog::OnBnClickedButtonOk()
{
  // TODO: Add your control notification handler code here
  CDialog::OnOK();
}


void CCADLineStyleDialog::OnBnClickedButtonLineStyleCancel()
{
  // TODO: Add your control notification handler code here
  CDialog::OnCancel();
}



void CCADLineStyleDialog::OnBnClickedButtonLineStyleColor()
{
  // TODO: Add your control notification handler code here
  CColorDialog dlg;
  dlg.m_cc.Flags |= CC_RGBINIT;
  dlg.m_cc.rgbResult = theApp.m_nPenColor;

  if (IDOK == dlg.DoModal())
  {
    m_nPenColor = dlg.m_cc.rgbResult;
  }

  m_colorButton.SetFaceColor(m_nPenColor);

}

extern CCADSimulationApp theApp;

//这里不能初始化控件，会崩溃，教训
int CCADLineStyleDialog::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
  if (CDialog::OnCreate(lpCreateStruct) == -1)
    return -1;

  // TODO:  Add your specialized creation code here
  //m_sldCtrl.SetSelection(1, 10);
  //m_nPenWidth = theApp.m_nPenWidth;
  //m_sldCtrl.SetPos(m_nPenWidth);


  //UpdateData(FALSE);

  return 0;
}

BOOL CCADLineStyleDialog::OnInitDialog()
{
  CDialog::OnInitDialog();

  // TODO:  Add extra initialization here
  m_sldCtrl.SetRange(1, 10);//设置滑动范围为1到10
  m_sldCtrl.SetTicFreq(1);//每1个单位画一刻度
  m_sldCtrl.SetPos(theApp.m_nPenWidth);//设置滑块初始位置为1 
  m_nPenWidth = theApp.m_nPenWidth;

  switch (theApp.m_nPenStyle)
  {
  case PS_SOLID:
    m_nPenStyle = 0;
    break;
  case PS_DASH:
    m_nPenStyle = 1;
    break;
  case PS_DOT:
    m_nPenStyle = 2;
    break;
  default:
    break;
  }

  m_nPenColor = theApp.m_nPenColor;
  m_colorButton.SetFaceColor(theApp.m_nPenColor);

  UpdateData(FALSE);

  return TRUE;  // return TRUE unless you set the focus to a control
                // EXCEPTION: OCX Property Pages should return FALSE
}

void CCADLineStyleDialog::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
  // TODO: Add your message handler code here and/or call default
  UpdateData(TRUE);
  int nWidthResult = m_sldCtrl.GetPos();
  m_nPenWidth = nWidthResult;
  UpdateData(FALSE);

  CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}


// void CCADLineStyleDialog::OnBnClickedRadio1()
// {
//   // TODO: Add your control notification handler code here
//   //m_nPenStyle = PS_SOLID;
// }
// 
// 
// void CCADLineStyleDialog::OnBnClickedRadio2()
// {
//   // TODO: Add your control notification handler code here
//   m_nPenStyle = PS_DASH;
// }
// 
// 
// void CCADLineStyleDialog::OnBnClickedRadio3()
// {
//   // TODO: Add your control notification handler code here
//   m_nPenStyle = PS_DOT;
// }
