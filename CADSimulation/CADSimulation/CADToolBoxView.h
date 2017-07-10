#pragma once


// CCADToolBoxView view

class CCadDrawToolBox;

class CCADToolBoxView : public CView
{
	DECLARE_DYNCREATE(CCADToolBoxView)

protected:
	CCADToolBoxView();           // protected constructor used by dynamic creation
	virtual ~CCADToolBoxView();

public:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	DECLARE_MESSAGE_MAP()
public:
  afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
  afx_msg void OnSizing(UINT fwSide, LPRECT pRect);

private:
  CCadDrawToolBox *m_pToolBoxDlg;
  RECT m_rcToolBoxDlg;
};


