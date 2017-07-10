#pragma once
#include "afxcmn.h"
#include "afxwin.h"


// CCADLineStyleDialog dialog

class CCADLineStyleDialog : public CDialog
{
	DECLARE_DYNAMIC(CCADLineStyleDialog)

public:
	CCADLineStyleDialog(CWnd* pParent = NULL);   // standard constructor
	virtual ~CCADLineStyleDialog();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_LINESTYLE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
  afx_msg void OnBnClickedButtonOk();
  afx_msg void OnBnClickedButtonLineStyleCancel();
  afx_msg void OnBnClickedButtonLineStyleColor();
  int m_nPenStyle;
  int m_nPenWidth;
  CSliderCtrl m_sldCtrl;
  COLORREF m_nPenColor;

  afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
  virtual BOOL OnInitDialog();
  afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
//   afx_msg void OnBnClickedRadio1();  //不需要
//   afx_msg void OnBnClickedRadio2();  //不需要
//   afx_msg void OnBnClickedRadio3();  //不需要
  CMFCButton m_colorButton;
};
