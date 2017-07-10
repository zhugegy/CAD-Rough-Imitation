#pragma once


// CCADCutomizeShape dialog

#define CUSTOMIZE_SHAPE_MATRIX_WIDTH 280
#define CUSTOMIZE_SHAPE_MATRIX_OFFSET 20
#define CUSTOMIZE_SHAPE_MAX_POINTS 10


class CCADCutomizeShape : public CDialog
{
	DECLARE_DYNAMIC(CCADCutomizeShape)

public:
	CCADCutomizeShape(CWnd* pParent = NULL);   // standard constructor
	virtual ~CCADCutomizeShape();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_CUSTOMIZE_SHAPE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
  afx_msg void OnBnClickedOk();
  afx_msg void OnBnClickedCancel();
  CString m_strCurrentCusorPostion;
  afx_msg void OnMouseMove(UINT nFlags, CPoint point);

public:
  POINT m_aryDrawPoints[CUSTOMIZE_SHAPE_MAX_POINTS];
  int m_nCounter;
  virtual BOOL OnInitDialog();
  afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
};
