#pragma once
#include "afxcmn.h"


// CCadDrawToolBox dialog

class CCadDrawToolBox : public CDialog
{
	DECLARE_DYNAMIC(CCadDrawToolBox)

public:
	CCadDrawToolBox(CWnd* pParent = NULL);   // standard constructor
	virtual ~CCadDrawToolBox();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_DRAWTOOLBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
  afx_msg void OnBnClickedButtonDrawToolBoxLine();
  afx_msg void OnBnClickedButtonDrawToolBoxRect();
  afx_msg void OnBnClickedButtonDrawToolBoxEllipse();
  afx_msg void OnBnClickedButtonToolBoxSetPen();
  afx_msg void OnBnClickedButtonToolBoxSetBrush();
  afx_msg void OnBnClickedButtonDrawToolBoxCustomizeShape();
  afx_msg void OnBnClickedButtonDrawToolBoxCustomizedShape();
  afx_msg void OnBnClickedButtonDrawToolBoxSelect();
  afx_msg void OnBnClickedButtonDrawToolBoxCancelSelection();
  afx_msg void OnBnClickedButtonDrawToolBoxMove();
  CSliderCtrl m_sldCtrlRotation;
  virtual BOOL OnInitDialog();
  afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
  afx_msg void OnBnClickedButtonDrawBoxRotateLeft();
  int RotateTheShape();
  afx_msg void OnBnClickedButtonDrawToolBoxRotateRight();
  int m_nShapeRotation;
};
