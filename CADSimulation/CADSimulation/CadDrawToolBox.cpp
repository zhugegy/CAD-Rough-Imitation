// CadDrawToolBox.cpp : implementation file
//

#include "stdafx.h"
#include "CADSimulation.h"
#include "CadDrawToolBox.h"
#include "afxdialogex.h"

#include "CADLineStyleDialog.h"
#include "CADBrushStyleDialog.h"
#include "CADCutomizeShape.h"
#include "CADSimulationView.h"

// CCadDrawToolBox dialog

IMPLEMENT_DYNAMIC(CCadDrawToolBox, CDialog)

CCadDrawToolBox::CCadDrawToolBox(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_DIALOG_DRAWTOOLBOX, pParent)
  , m_nShapeRotation(0)
{

}

CCadDrawToolBox::~CCadDrawToolBox()
{
}

void CCadDrawToolBox::DoDataExchange(CDataExchange* pDX)
{
  CDialog::DoDataExchange(pDX);
  DDX_Control(pDX, IDC_SLIDER1, m_sldCtrlRotation);
  DDX_Text(pDX, IDC_EDIT3, m_nShapeRotation);
}


BEGIN_MESSAGE_MAP(CCadDrawToolBox, CDialog)
  ON_BN_CLICKED(IDC_BUTTON_DRAW_TOOL_BOX_LINE, &CCadDrawToolBox::OnBnClickedButtonDrawToolBoxLine)
  ON_BN_CLICKED(IDC_BUTTON_DRAW_TOOL_BOX_RECT, &CCadDrawToolBox::OnBnClickedButtonDrawToolBoxRect)
  ON_BN_CLICKED(IDC_BUTTON_DRAW_TOOL_BOX_ELLIPSE, &CCadDrawToolBox::OnBnClickedButtonDrawToolBoxEllipse)
  ON_BN_CLICKED(IDC_BUTTON_TOOL_BOX_SET_PEN, &CCadDrawToolBox::OnBnClickedButtonToolBoxSetPen)
  ON_BN_CLICKED(IDC_BUTTON_TOOL_BOX_SET_BRUSH, &CCadDrawToolBox::OnBnClickedButtonToolBoxSetBrush)
  ON_BN_CLICKED(IDC_BUTTON_DRAW_TOOL_BOX_CUSTOMIZE_SHAPE, &CCadDrawToolBox::OnBnClickedButtonDrawToolBoxCustomizeShape)
  ON_BN_CLICKED(IDC_BUTTON_DRAW_TOOL_BOX_CUSTOMIZED_SHAPE, &CCadDrawToolBox::OnBnClickedButtonDrawToolBoxCustomizedShape)
  ON_BN_CLICKED(IDC_BUTTON_DRAW_TOOL_BOX_SELECT, &CCadDrawToolBox::OnBnClickedButtonDrawToolBoxSelect)
  ON_BN_CLICKED(IDC_BUTTON_DRAW_TOOL_BOX_CANCEL_SELECTION, &CCadDrawToolBox::OnBnClickedButtonDrawToolBoxCancelSelection)
  ON_BN_CLICKED(IDC_BUTTON_DRAW_TOOL_BOX_MOVE, &CCadDrawToolBox::OnBnClickedButtonDrawToolBoxMove)
  ON_WM_HSCROLL()
  ON_BN_CLICKED(IDC_BUTTON_DRAW_BOX_ROTATE_LEFT, &CCadDrawToolBox::OnBnClickedButtonDrawBoxRotateLeft)
  ON_BN_CLICKED(IDC_BUTTON_DRAW_TOOL_BOX_ROTATE_RIGHT, &CCadDrawToolBox::OnBnClickedButtonDrawToolBoxRotateRight)
END_MESSAGE_MAP()


// CCadDrawToolBox message handlers

extern CCADSimulationApp theApp;

void CCadDrawToolBox::OnBnClickedButtonDrawToolBoxLine()
{
  // TODO: Add your control notification handler code here
  theApp.SetLastShapeName(GetDlgItem(IDC_BUTTON_DRAW_TOOL_BOX_LINE));
}

void CCadDrawToolBox::OnBnClickedButtonDrawToolBoxRect()
{
  // TODO: Add your control notification handler code here
  theApp.SetLastShapeName(GetDlgItem(IDC_BUTTON_DRAW_TOOL_BOX_RECT));
}


void CCadDrawToolBox::OnBnClickedButtonDrawToolBoxEllipse()
{
  // TODO: Add your control notification handler code here
  theApp.SetLastShapeName(GetDlgItem(IDC_BUTTON_DRAW_TOOL_BOX_ELLIPSE));
}

void CCadDrawToolBox::OnBnClickedButtonDrawToolBoxCustomizedShape()
{
  // TODO: Add your control notification handler code here
  theApp.SetLastShapeName(GetDlgItem(IDC_BUTTON_DRAW_TOOL_BOX_CUSTOMIZED_SHAPE));
}

//选择也当做画图来看
void CCadDrawToolBox::OnBnClickedButtonDrawToolBoxSelect()
{
  // TODO: Add your control notification handler code here
  theApp.SetLastShapeName(GetDlgItem(IDC_BUTTON_DRAW_TOOL_BOX_SELECT));

    //清空当前选择
  POSITION posSelected = (theApp.m_lstSelectedShapes).GetHeadPosition();
  while (posSelected)
  {
    CCADShape * pShape = (theApp.m_lstSelectedShapes).GetNext(posSelected);

    pShape->WhenUnselected();
  }

  (theApp.m_lstSelectedShapes).RemoveAll();

  //通知窗口进行重绘
  theApp.m_pView->InvalidateRect(NULL, FALSE);
}

void CCadDrawToolBox::OnBnClickedButtonDrawToolBoxCancelSelection()
{
  // TODO: Add your control notification handler code here
  theApp.SetLastShapeName(GetDlgItem(IDC_BUTTON_DRAW_TOOL_BOX_CANCEL_SELECTION));


  //清空当前选择
  POSITION posSelected = (theApp.m_lstSelectedShapes).GetHeadPosition();
  while (posSelected)
  {
    CCADShape * pShape = (theApp.m_lstSelectedShapes).GetNext(posSelected);

    pShape->WhenUnselected();
  }

  (theApp.m_lstSelectedShapes).RemoveAll();

  //通知窗口进行重绘
  theApp.m_pView->InvalidateRect(NULL, FALSE);
}

void CCadDrawToolBox::OnBnClickedButtonDrawToolBoxMove()
{
  // TODO: Add your control notification handler code here
  theApp.SetLastShapeName(GetDlgItem(IDC_BUTTON_DRAW_TOOL_BOX_MOVE));

}

void CCadDrawToolBox::OnBnClickedButtonToolBoxSetPen()
{
  // TODO: Add your control notification handler code here

  CCADLineStyleDialog dlg;
  if (IDOK == dlg.DoModal())
  {
    theApp.m_nPenWidth = dlg.m_nPenWidth;

    switch (dlg.m_nPenStyle)
    {
    case 0:
      theApp.m_nPenStyle = PS_SOLID;
      break;
    case 1:
      theApp.m_nPenStyle = PS_DASH;
      break;
    case 2:
      theApp.m_nPenStyle = PS_DOT;
      break;
    default:
      break;
    }

    theApp.m_nPenColor = dlg.m_nPenColor;

    //遍历当前选择
    POSITION posSelected = (theApp.m_lstSelectedShapes).GetHeadPosition();
    while (posSelected)
    {
      CCADShape * pShape = (theApp.m_lstSelectedShapes).GetNext(posSelected);

      pShape->SetPen(theApp.m_nPenWidth, theApp.m_nPenStyle, 
        theApp.m_nPenColor);

      pShape->WhenUnselected();
    }

    (theApp.m_lstSelectedShapes).RemoveAll();

    //通知窗口进行重绘
    theApp.m_pView->InvalidateRect(NULL, FALSE);
  }

  //非模态
//   CCADLineStyleDialog *pTmp = new CCADLineStyleDialog;
//   pTmp->Create(IDD_DIALOG_LINESTYLE, this);
//   //m_pToolBoxDlg->MoveWindow(&m_rcToolBoxDlg);
//   pTmp->ShowWindow(SW_SHOW);
}

void CCadDrawToolBox::OnBnClickedButtonToolBoxSetBrush()
{
  // TODO: Add your control notification handler code here
  CCADBrushStyleDialog dlg;

  if (IDOK == dlg.DoModal())
  {
    switch (dlg.m_nBrushChoice)
    {
    case 0:
      theApp.m_nBrushColor = -1;
      break;
    case 1:
      theApp.m_nBrushColor = dlg.m_nBrushColor;
      break;
    default:
      break;
    }

    //遍历当前选择
    POSITION posSelected = (theApp.m_lstSelectedShapes).GetHeadPosition();
    while (posSelected)
    {
      CCADShape * pShape = (theApp.m_lstSelectedShapes).GetNext(posSelected);

      pShape->SetBrush(theApp.m_nBrushColor);
      pShape->WhenUnselected();
    }

    (theApp.m_lstSelectedShapes).RemoveAll();

    //通知窗口进行重绘
    theApp.m_pView->InvalidateRect(NULL, FALSE);

  }

}


void CCadDrawToolBox::OnBnClickedButtonDrawToolBoxCustomizeShape()
{
  // TODO: Add your control notification handler code here
  CCADCutomizeShape dlg;

  if (IDOK == dlg.DoModal() && dlg.m_nCounter >= 3)
  {
    memcpy(theApp.m_aryCustomizedShapePoints, dlg.m_aryDrawPoints, 
      sizeof(theApp.m_aryCustomizedShapePoints));

    theApp.m_nCustomiezedShapePointCount = dlg.m_nCounter;

    for (int i = 0; i < theApp.m_nCustomiezedShapePointCount; i ++)
    {
      ((theApp.m_aryCustomizedShapePoints)[i]).x -= CUSTOMIZE_SHAPE_MATRIX_OFFSET;
      ((theApp.m_aryCustomizedShapePoints)[i]).y -= CUSTOMIZE_SHAPE_MATRIX_OFFSET;

    }
  }
}

BOOL CCadDrawToolBox::OnInitDialog()
{
  CDialog::OnInitDialog();

  // TODO:  Add extra initialization here
  m_sldCtrlRotation.SetRange(0, 360);//设置滑动范围为1到10
  m_sldCtrlRotation.SetTicFreq(1);//每1个单位画一刻度
  m_sldCtrlRotation.SetPos(0);//设置滑块初始位置为1 


  return TRUE;  // return TRUE unless you set the focus to a control
                // EXCEPTION: OCX Property Pages should return FALSE
}


void CCadDrawToolBox::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
  // TODO: Add your message handler code here and/or call default
  m_nShapeRotation = m_sldCtrlRotation.GetPos();
  UpdateData(FALSE);


  RotateTheShape();

  CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}


void CCadDrawToolBox::OnBnClickedButtonDrawBoxRotateLeft()
{
  // TODO: Add your control notification handler code here
  int nRotationResult = m_sldCtrlRotation.GetPos();
  if (nRotationResult == 0)
  {
    m_sldCtrlRotation.SetPos(359);
  }
  else
  {
    m_sldCtrlRotation.SetPos(nRotationResult - 1);
  }

  m_nShapeRotation = m_sldCtrlRotation.GetPos();

  UpdateData(FALSE);

  RotateTheShape();
}


void CCadDrawToolBox::OnBnClickedButtonDrawToolBoxRotateRight()
{
  // TODO: Add your control notification handler code here
  int nRotationResult = m_sldCtrlRotation.GetPos();
  if (nRotationResult == 360)
  {
    m_sldCtrlRotation.SetPos(1);
  }
  else
  {
    m_sldCtrlRotation.SetPos(nRotationResult + 1);
  }

  m_nShapeRotation = m_sldCtrlRotation.GetPos();

  UpdateData(FALSE);

  RotateTheShape();
}


int CCadDrawToolBox::RotateTheShape()
{
  int nRotationResult = m_sldCtrlRotation.GetPos();

  //遍历当前选择
  POSITION posSelected = (theApp.m_lstSelectedShapes).GetHeadPosition();
  while (posSelected)
  {
    CCADShape * pShape = (theApp.m_lstSelectedShapes).GetNext(posSelected);

    pShape->SetRotation(nRotationResult);
  }

  //通知窗口进行重绘
  theApp.m_pView->InvalidateRect(NULL, FALSE);

  return 0;
}

