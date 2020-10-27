// CADCutomizeShape.cpp : implementation file
//

#include "stdafx.h"
#include "CADSimulation.h"
#include "CADDialogDrawCustomizeShape.h"
#include "afxdialogex.h"

// CCADCutomizeShape dialog

IMPLEMENT_DYNAMIC(CADDialogDrawCustomizeShape, CDialog)

CADDialogDrawCustomizeShape::CADDialogDrawCustomizeShape(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_DIALOG_CUSTOMIZE_SHAPE, pParent)
  , m_strCurrentCusorPostion(_T(""))
{

}

CADDialogDrawCustomizeShape::~CADDialogDrawCustomizeShape()
{
}

void CADDialogDrawCustomizeShape::DoDataExchange(CDataExchange* pDX)
{
  CDialog::DoDataExchange(pDX);
  DDX_Text(pDX, IDC_EDIT_CUSTOMIZE_SHAPE_COORD_EDIT, m_strCurrentCusorPostion);
}


BEGIN_MESSAGE_MAP(CADDialogDrawCustomizeShape, CDialog)
  ON_BN_CLICKED(IDOK, &CADDialogDrawCustomizeShape::OnBnClickedOk)
  ON_BN_CLICKED(IDCANCEL, &CADDialogDrawCustomizeShape::OnBnClickedCancel)
  ON_WM_MOUSEMOVE()
  ON_WM_LBUTTONUP()
END_MESSAGE_MAP()


// CCADCutomizeShape message handlers


void CADDialogDrawCustomizeShape::OnBnClickedOk()
{
  // TODO: Add your control notification handler code here
  CDialog::OnOK();
}


void CADDialogDrawCustomizeShape::OnBnClickedCancel()
{
  // TODO: Add your control notification handler code here
  CDialog::OnCancel();
}


void CADDialogDrawCustomizeShape::OnMouseMove(UINT nFlags, CPoint point)
{
  // TODO: Add your message handler code here and/or call default
  int nDrawPosX = point.x - CUSTOMIZE_SHAPE_MATRIX_OFFSET;
  int nDrawPosY = point.y - CUSTOMIZE_SHAPE_MATRIX_OFFSET;

  if (nDrawPosX >= 0 && nDrawPosX < CUSTOMIZE_SHAPE_MATRIX_WIDTH &&
      nDrawPosY >= 0 && nDrawPosY < CUSTOMIZE_SHAPE_MATRIX_WIDTH)
  {
    m_strCurrentCusorPostion.Format(_T("x: %d, y: %d "), nDrawPosX, nDrawPosY);
  }
  else
  {
    m_strCurrentCusorPostion.Format(_T("%s"), _T("���곬����ͼ��Χ"));
  }

  UpdateData(FALSE);

  CDialog::OnMouseMove(nFlags, point);
}


BOOL CADDialogDrawCustomizeShape::OnInitDialog()
{
  CDialog::OnInitDialog();

  m_nCounter = 0;

  // TODO:  Add extra initialization here

  return TRUE;  // return TRUE unless you set the focus to a control
                // EXCEPTION: OCX Property Pages should return FALSE
}


void CADDialogDrawCustomizeShape::OnLButtonUp(UINT nFlags, CPoint point)
{
  // TODO: Add your message handler code here and/or call default
  int nDrawPosX = point.x - CUSTOMIZE_SHAPE_MATRIX_OFFSET;
  int nDrawPosY = point.y - CUSTOMIZE_SHAPE_MATRIX_OFFSET;

  if (nDrawPosX >= 0 && nDrawPosX < CUSTOMIZE_SHAPE_MATRIX_WIDTH &&
      nDrawPosY >= 0 && nDrawPosY < CUSTOMIZE_SHAPE_MATRIX_WIDTH
    && m_nCounter < CUSTOMIZE_SHAPE_MAX_POINTS)
  {
    m_aryDrawPoints[m_nCounter] = point;
    CClientDC dc(this);
    CBrush brush;
    brush.CreateSolidBrush(RGB(255, 0, 0));
    dc.SelectObject(brush);

    POINT ptElliStart;
    POINT ptElliEnd;

    ptElliStart.x = m_aryDrawPoints[m_nCounter].x - 5;
    ptElliStart.y = m_aryDrawPoints[m_nCounter].y - 5;
    ptElliEnd.x = m_aryDrawPoints[m_nCounter].x + 5;
    ptElliEnd.y = m_aryDrawPoints[m_nCounter].y + 5;


    dc.Ellipse(CRect(ptElliStart, ptElliEnd));

    if (m_nCounter > 0)
    {
      dc.MoveTo(m_aryDrawPoints[m_nCounter - 1]);
      dc.LineTo(m_aryDrawPoints[m_nCounter]);
    }

    m_nCounter++;
  }

  CDialog::OnLButtonUp(nFlags, point);
}
