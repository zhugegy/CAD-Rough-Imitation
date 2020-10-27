#pragma once
#include "afxwin.h"


// CCADBrushStyleDialog dialog

class CADDialogBrushStyle : public CDialog
{
	DECLARE_DYNAMIC(CADDialogBrushStyle)

public:
	CADDialogBrushStyle(CWnd* pParent = NULL);   // standard constructor
	virtual ~CADDialogBrushStyle();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_BRUSHSTYLE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
  int m_nBrushChoice;
  COLORREF m_nBrushColor;
  afx_msg void OnBnClickedOk();
  afx_msg void OnBnClickedCancel();
  virtual BOOL OnInitDialog();
  CMFCButton m_colorButton;
  afx_msg void OnBnClickedButtonBrushColor();
};
