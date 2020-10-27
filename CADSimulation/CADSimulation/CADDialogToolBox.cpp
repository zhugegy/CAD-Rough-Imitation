// CadDrawToolBox.cpp : implementation file
//

#include "stdafx.h"
#include "CADSimulation.h"
#include "CADDialogToolBox.h"
#include "afxdialogex.h"

#include "CADDialogLineStyle.h"
#include "CADDialogBrushStyle.h"
#include "CADDialogDrawCustomizeShape.h"
#include "CADSimulationView.h"

#include "CADStaticFunctions.h"

#include "CADCommandGroupCmds.h"
#include "CADCommandRotateShape.h"
#include "CADCommandSetPenToShape.h"
#include "CADCommandSetBrushToShape.h"

#include "CADStorage.h"

#include <fstream>


// CCadDrawToolBox dialog

IMPLEMENT_DYNAMIC(CADDialogToolBox, CDialog)

CADDialogToolBox::CADDialogToolBox(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_DIALOG_DRAWTOOLBOX, pParent)
  , m_nShapeRotation(0)
{

}

CADDialogToolBox::~CADDialogToolBox()
{
}

void CADDialogToolBox::DoDataExchange(CDataExchange* pDX)
{
  CDialog::DoDataExchange(pDX);
  DDX_Control(pDX, IDC_SLIDER1, m_sldCtrlRotation);
  DDX_Text(pDX, IDC_EDIT3, m_nShapeRotation);
  DDX_Control(pDX, IDC_COMBO_DRAW_TOOL_BOX_SELECT_CUSTOMIZED_SHAPE, m_ctlComboSelectCustomizedShape);
}


BEGIN_MESSAGE_MAP(CADDialogToolBox, CDialog)
  ON_BN_CLICKED(IDC_BUTTON_DRAW_TOOL_BOX_LINE, &CADDialogToolBox::OnBnClickedButtonDrawToolBoxLine)
  ON_BN_CLICKED(IDC_BUTTON_DRAW_TOOL_BOX_RECT, &CADDialogToolBox::OnBnClickedButtonDrawToolBoxRect)
  ON_BN_CLICKED(IDC_BUTTON_DRAW_TOOL_BOX_ELLIPSE, &CADDialogToolBox::OnBnClickedButtonDrawToolBoxEllipse)
  ON_BN_CLICKED(IDC_BUTTON_TOOL_BOX_SET_PEN, &CADDialogToolBox::OnBnClickedButtonToolBoxSetPen)
  ON_BN_CLICKED(IDC_BUTTON_TOOL_BOX_SET_BRUSH, &CADDialogToolBox::OnBnClickedButtonToolBoxSetBrush)
  ON_BN_CLICKED(IDC_BUTTON_DRAW_TOOL_BOX_CUSTOMIZE_SHAPE, &CADDialogToolBox::OnBnClickedButtonDrawToolBoxCustomizeShape)
  ON_BN_CLICKED(IDC_BUTTON_DRAW_TOOL_BOX_CUSTOMIZED_SHAPE, &CADDialogToolBox::OnBnClickedButtonDrawToolBoxCustomizedShape)
  ON_BN_CLICKED(IDC_BUTTON_DRAW_TOOL_BOX_SELECT, &CADDialogToolBox::OnBnClickedButtonDrawToolBoxSelect)
  ON_BN_CLICKED(IDC_BUTTON_DRAW_TOOL_BOX_CANCEL_SELECTION, &CADDialogToolBox::OnBnClickedButtonDrawToolBoxCancelSelection)
  ON_BN_CLICKED(IDC_BUTTON_DRAW_TOOL_BOX_MOVE, &CADDialogToolBox::OnBnClickedButtonDrawToolBoxMove)
  ON_WM_HSCROLL()
  ON_BN_CLICKED(IDC_BUTTON_DRAW_BOX_ROTATE_LEFT, &CADDialogToolBox::OnBnClickedButtonDrawBoxRotateLeft)
  ON_BN_CLICKED(IDC_BUTTON_DRAW_TOOL_BOX_ROTATE_RIGHT, &CADDialogToolBox::OnBnClickedButtonDrawToolBoxRotateRight)
  ON_BN_CLICKED(IDC_BUTTON_DRAW_TOOL_BOX_CUSTOMIZED_SHAPE_SAVE, &CADDialogToolBox::OnBnClickedButtonDrawToolBoxCustomizedShapeSave)
  ON_BN_CLICKED(IDC_BUTTON_DRAW_TOOL_BOX_CUSTOMIZED_SHAPE_LOAD, &CADDialogToolBox::OnBnClickedButtonDrawToolBoxCustomizedShapeLoad)
  ON_CBN_SELCHANGE(IDC_COMBO_DRAW_TOOL_BOX_SELECT_CUSTOMIZED_SHAPE, &CADDialogToolBox::OnSelchangeComboDrawToolBoxSelectCustomizedShape)
  ON_BN_CLICKED(IDC_BUTTON_DRAW_TOOL_BOX_PENCIL, &CADDialogToolBox::OnBnClickedButtonDrawToolBoxPencil)
END_MESSAGE_MAP()


// CCadDrawToolBox message handlers

extern CCADSimulationApp theApp;

void CADDialogToolBox::OnBnClickedButtonDrawToolBoxPencil()
{
  // TODO: Add your control notification handler code here
  theApp.SetLastShapeName(GetDlgItem(IDC_BUTTON_DRAW_TOOL_BOX_PENCIL));
}

void CADDialogToolBox::OnBnClickedButtonDrawToolBoxLine()
{
  // TODO: Add your control notification handler code here
  theApp.SetLastShapeName(GetDlgItem(IDC_BUTTON_DRAW_TOOL_BOX_LINE));
}

void CADDialogToolBox::OnBnClickedButtonDrawToolBoxRect()
{
  // TODO: Add your control notification handler code here
  theApp.SetLastShapeName(GetDlgItem(IDC_BUTTON_DRAW_TOOL_BOX_RECT));
}


void CADDialogToolBox::OnBnClickedButtonDrawToolBoxEllipse()
{
  // TODO: Add your control notification handler code here
  theApp.SetLastShapeName(GetDlgItem(IDC_BUTTON_DRAW_TOOL_BOX_ELLIPSE));
}

void CADDialogToolBox::OnBnClickedButtonDrawToolBoxCustomizedShape()
{
  // TODO: Add your control notification handler code here
  if (theApp.m_nCustomiezedShapePointCount == 0)
  {
    AfxMessageBox(_T("请绘制或者载入自定义图形。"));
    return;
  }

  theApp.SetLastShapeName(GetDlgItem(IDC_BUTTON_DRAW_TOOL_BOX_CUSTOMIZED_SHAPE));
}

//选择也当做画图来看
void CADDialogToolBox::OnBnClickedButtonDrawToolBoxSelect()
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

void CADDialogToolBox::OnBnClickedButtonDrawToolBoxCancelSelection()
{
  // TODO: Add your control notification handler code here
  theApp.SetLastShapeName(GetDlgItem(IDC_BUTTON_DRAW_TOOL_BOX_CANCEL_SELECTION));

  CADStaticFunctions::unselect_all();

  //通知窗口进行重绘
  theApp.m_pView->InvalidateRect(NULL, FALSE);
}

void CADDialogToolBox::OnBnClickedButtonDrawToolBoxMove()
{
  // TODO: Add your control notification handler code here
  theApp.SetLastShapeName(GetDlgItem(IDC_BUTTON_DRAW_TOOL_BOX_MOVE));

}

void CADDialogToolBox::OnBnClickedButtonToolBoxSetPen()
{
  // TODO: Add your control notification handler code here

  CADDialogLineStyle dlg;
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

    if (posSelected == NULL)
    {
      return;
    }

    CCADStorage* pStorage = GET_SINGLE(CCADStorage);
    CADCommandGroupCmds* pCmdSetPenToShapes = new CADCommandGroupCmds;


    while (posSelected)
    {
      CCADShape * pShape = (theApp.m_lstSelectedShapes).GetNext(posSelected);

      if (pShape)
      {
        CADCommandSetPenToShape* pCmdSetPenToShape = new CADCommandSetPenToShape;
        pCmdSetPenToShape->m_pShapeSetPenTo = pShape;

        int nPenWidth;
        int nPenStyle;
        COLORREF colPenColor;
        pShape->GetPen(nPenWidth, nPenStyle, colPenColor);

        pCmdSetPenToShape->m_nPenWidthBefore = nPenWidth;
        pCmdSetPenToShape->m_nPenStyleBefore = nPenStyle;
        pCmdSetPenToShape->m_nPenColorBefore = colPenColor;


        pShape->SetPen(theApp.m_nPenWidth, theApp.m_nPenStyle,
          theApp.m_nPenColor);

        pCmdSetPenToShape->m_nPenWidthAfter = theApp.m_nPenWidth;
        pCmdSetPenToShape->m_nPenStyleAfter = theApp.m_nPenStyle;
        pCmdSetPenToShape->m_nPenColorAfter = theApp.m_nPenColor;

        pCmdSetPenToShapes->PushCommand(pCmdSetPenToShape);

        pShape->WhenUnselected();
      }
    }

    ASSERT(pCmdSetPenToShapes->GetCommandCount() != 0);
    pStorage->m_stkToUndo.push(pCmdSetPenToShapes);

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

void CADDialogToolBox::OnBnClickedButtonToolBoxSetBrush()
{
  // TODO: Add your control notification handler code here
  CADDialogBrushStyle dlg;

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

    if (posSelected == NULL)
    {
      return;
    }

    CCADStorage* pStorage = GET_SINGLE(CCADStorage);
    CADCommandGroupCmds* pCmdSetBrushToShapes = new CADCommandGroupCmds;

    while (posSelected)
    {
      CCADShape * pShape = (theApp.m_lstSelectedShapes).GetNext(posSelected);

      if (pShape)
      {
        CADCommandSetBrushToShape* pCmdSetBrushToShape = new CADCommandSetBrushToShape;
        pCmdSetBrushToShape->m_pShapeSetBrushTo = pShape;

        COLORREF colBrushColor;
        pShape->GetBrush(colBrushColor);
        pCmdSetBrushToShape->m_nBrushColorBefore = colBrushColor;

        pShape->SetBrush(theApp.m_nBrushColor);

        pCmdSetBrushToShape->m_nBrushColorAfter = theApp.m_nBrushColor;

        pCmdSetBrushToShapes->PushCommand(pCmdSetBrushToShape);

        pShape->WhenUnselected();
      }
    }

    ASSERT(pCmdSetBrushToShapes->GetCommandCount() != 0);
    pStorage->m_stkToUndo.push(pCmdSetBrushToShapes);

    (theApp.m_lstSelectedShapes).RemoveAll();

    //通知窗口进行重绘
    theApp.m_pView->InvalidateRect(NULL, FALSE);
  }

}


void CADDialogToolBox::OnBnClickedButtonDrawToolBoxCustomizeShape()
{
  // TODO: Add your control notification handler code here
  CADDialogDrawCustomizeShape dlg;

  if (IDOK == dlg.DoModal())
  {
    if (dlg.m_nCounter < 3)
    {
      AfxMessageBox(_T("绘制失败。转折点数目必须大于等于3。"));
      return;
    }

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

BOOL CADDialogToolBox::OnInitDialog()
{
  CDialog::OnInitDialog();

  // TODO:  Add extra initialization here
  m_sldCtrlRotation.SetRange(0, 360);//设置滑动范围为1到10
  m_sldCtrlRotation.SetTicFreq(1);//每1个单位画一刻度
  m_sldCtrlRotation.SetPos(0);//设置滑块初始位置为1 

  m_ctlComboSelectCustomizedShape.AddString(_T("已载入的图形"));
  m_ctlComboSelectCustomizedShape.SetCurSel(0);

  return TRUE;  // return TRUE unless you set the focus to a control
                // EXCEPTION: OCX Property Pages should return FALSE
}


void CADDialogToolBox::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
  // TODO: Add your message handler code here and/or call default
   
  //if pScrollBar == 目标pscrollbar
  m_nShapeRotation = m_sldCtrlRotation.GetPos();
  UpdateData(FALSE);

  RotateTheShape();

  CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}


void CADDialogToolBox::OnBnClickedButtonDrawBoxRotateLeft()
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


void CADDialogToolBox::OnBnClickedButtonDrawToolBoxRotateRight()
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


int CADDialogToolBox::RotateTheShape()
{
  int nRotationResult = m_sldCtrlRotation.GetPos();

  //遍历当前选择
  POSITION posSelected = (theApp.m_lstSelectedShapes).GetHeadPosition();

  if (posSelected == NULL)
  {
    return -1;
  }

  CCADStorage* pStorage = GET_SINGLE(CCADStorage);
  CADCommandGroupCmds* pCmdRotateShapes = new CADCommandGroupCmds;

  while (posSelected)
  {
    CCADShape * pShape = (theApp.m_lstSelectedShapes).GetNext(posSelected);

    if (pShape)
    {
      CADCommandRotateShape* pCmdRotateShape = new CADCommandRotateShape;
      pCmdRotateShape->m_pShapeRotated = pShape;
      pCmdRotateShape->m_nRotationDegreeBefore = pShape->GetRotation();

      pShape->SetRotation(nRotationResult);
      pCmdRotateShape->m_nRotationDegreeAfter = nRotationResult;
      pCmdRotateShapes->PushCommand(pCmdRotateShape);
    }
  }

  ASSERT(pCmdRotateShapes->GetCommandCount() != 0);
  pStorage->m_stkToUndo.push(pCmdRotateShapes);

  //通知窗口进行重绘
  theApp.m_pView->InvalidateRect(NULL, FALSE);

  return 0;
}


void CADDialogToolBox::OnBnClickedButtonDrawToolBoxCustomizedShapeSave()
{
  // TODO: Add your control notification handler code here
  if (theApp.m_nCustomiezedShapePointCount == 0)
  {
    AfxMessageBox(_T("请先绘制自定义图形，再进行保存操作。"));
    return;
  }

  CFileDialog dlg(FALSE);

  dlg.m_ofn.lpstrTitle = _T("保存自定义图形到文件");
  dlg.m_ofn.lpstrFilter = _T("Shape Files(*.shp)\0*.shp\0All Files(*.*)\0*.*\0\0");
  dlg.m_ofn.lpstrDefExt = _T("shp");

  if (IDOK == dlg.DoModal())
  {
    CString str = dlg.GetFileName();
    theApp.SaveCustomizedShapeToFile(str);
    m_ctlComboSelectCustomizedShape.InsertString(1, str);
  }

}


void CADDialogToolBox::OnBnClickedButtonDrawToolBoxCustomizedShapeLoad()
{
  // TODO: Add your control notification handler code here
  CFileDialog dlg(TRUE);

  dlg.m_ofn.lpstrTitle = _T("载入自定义图形到文件");
  dlg.m_ofn.lpstrFilter = _T("Shape Files(*.shp)\0*.shp\0All Files(*.*)\0*.*\0\0");
  dlg.m_ofn.lpstrDefExt = _T("shp");

  if (IDOK == dlg.DoModal())
  {
    CString str = dlg.GetFileName();
    theApp.LoadCustomizedShapeFromFile(str);
    m_ctlComboSelectCustomizedShape.InsertString(1, str);

  }
}

void CADDialogToolBox::OnSelchangeComboDrawToolBoxSelectCustomizedShape()
{
  // TODO: Add your control notification handler code here
  int n = m_ctlComboSelectCustomizedShape.GetCurSel();
  if (m_ctlComboSelectCustomizedShape.GetCurSel() != 0)
  {
    CString str;
    
    m_ctlComboSelectCustomizedShape.GetLBText(
      m_ctlComboSelectCustomizedShape.GetCurSel(), str);

    theApp.LoadCustomizedShapeFromFile(str);
  }

}
