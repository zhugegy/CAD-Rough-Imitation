// CADBrushStyleDialog.cpp : implementation file
//

#include "stdafx.h"
#include "CADSimulation.h"
#include "CADBrushStyleDialog.h"
#include "afxdialogex.h"


// CCADBrushStyleDialog dialog

IMPLEMENT_DYNAMIC(CCADBrushStyleDialog, CDialog)

CCADBrushStyleDialog::CCADBrushStyleDialog(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_DIALOG_BRUSHSTYLE, pParent)
  , m_nBrushChoice(0)
{

}

CCADBrushStyleDialog::~CCADBrushStyleDialog()
{
}

void CCADBrushStyleDialog::DoDataExchange(CDataExchange* pDX)
{
  CDialog::DoDataExchange(pDX);
  DDX_Radio(pDX, IDC_RADIO1, m_nBrushChoice);
  DDX_Control(pDX, IDC_BUTTON_BRUSH_COLOR, m_colorButton);
}


BEGIN_MESSAGE_MAP(CCADBrushStyleDialog, CDialog)
  ON_BN_CLICKED(IDOK, &CCADBrushStyleDialog::OnBnClickedOk)
  ON_BN_CLICKED(IDCANCEL, &CCADBrushStyleDialog::OnBnClickedCancel)
  ON_BN_CLICKED(IDC_BUTTON_BRUSH_COLOR, &CCADBrushStyleDialog::OnBnClickedButtonBrushColor)
END_MESSAGE_MAP()


// CCADBrushStyleDialog message handlers


void CCADBrushStyleDialog::OnBnClickedOk()
{
  // TODO: Add your control notification handler code here
  CDialog::OnOK();
}


void CCADBrushStyleDialog::OnBnClickedCancel()
{
  // TODO: Add your control notification handler code here
  CDialog::OnCancel();
}


BOOL CCADBrushStyleDialog::OnInitDialog()
{
  CDialog::OnInitDialog();

  if (theApp.m_nBrushColor == -1)
  {
    m_nBrushChoice = 0;
  }
  else
  {
    m_nBrushChoice = 1;
    m_colorButton.SetFaceColor(theApp.m_nBrushColor);
  }

  UpdateData(FALSE);

  // TODO:  Add extra initialization here

  return TRUE;  // return TRUE unless you set the focus to a control
                // EXCEPTION: OCX Property Pages should return FALSE
}


void CCADBrushStyleDialog::OnBnClickedButtonBrushColor()
{
  // TODO: Add your control notification handler code here
  CColorDialog dlg;
  dlg.m_cc.Flags |= CC_RGBINIT;
  dlg.m_cc.rgbResult = theApp.m_nPenColor;

  if (IDOK == dlg.DoModal())
  {
    m_nBrushColor = dlg.m_cc.rgbResult;
  }

  m_colorButton.SetFaceColor(m_nBrushColor);
}
