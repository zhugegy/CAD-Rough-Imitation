#pragma once


// CCADToolBoxView view

class CADDialogToolBox;

class CADViewToolBox : public CView
{
	DECLARE_DYNCREATE(CADViewToolBox)

protected:
	CADViewToolBox();           // protected constructor used by dynamic creation
	virtual ~CADViewToolBox();

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
  CADDialogToolBox *m_pToolBoxDlg;
  RECT m_rcToolBoxDlg;
};


