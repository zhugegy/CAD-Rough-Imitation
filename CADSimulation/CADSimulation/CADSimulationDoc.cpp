
// CADSimulationDoc.cpp : implementation of the CCADSimulationDoc class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "CADSimulation.h"
#endif

#include "CADSimulationDoc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#include "CADStorage.h"
#include "GYSingleInstanceMacro.h"

// CCADSimulationDoc

IMPLEMENT_DYNCREATE(CCADSimulationDoc, CDocument)

BEGIN_MESSAGE_MAP(CCADSimulationDoc, CDocument)
END_MESSAGE_MAP()


// CCADSimulationDoc construction/destruction

CCADSimulationDoc::CCADSimulationDoc()
{
	// TODO: add one-time construction code here

}

CCADSimulationDoc::~CCADSimulationDoc()
{
}

BOOL CCADSimulationDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}




// CCADSimulationDoc serialization
void CCADSimulationDoc::Serialize(CArchive& ar)
{
  CCADStorage *pStorage = GET_SINGLE(CCADStorage);

	if (ar.IsStoring())
	{
		// TODO: add storing code here
    ar << (pStorage->m_lstShapes).GetCount();

    //遍历链表,依次保存每个对象
    POSITION pos = (pStorage->m_lstShapes).GetHeadPosition();
    while (pos)
    {
      CCADShape* pShape = (pStorage->m_lstShapes).GetNext(pos);
      ar << pShape;
    }

	}
	else
	{
		(pStorage->m_lstShapes).RemoveAll();
		// TODO: add loading code here
    int nCnt = 0;
    ar >> nCnt;

    CObject* pObj = NULL;
    while (nCnt--)
    {
      ar >> pObj;
      (pStorage->m_lstShapes).AddTail((CCADShape*)pObj);
    }

	}

}

#ifdef SHARED_HANDLERS

// Support for thumbnails
void CCADSimulationDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// Modify this code to draw the document's data
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// Support for Search Handlers
void CCADSimulationDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// Set search contents from document's data. 
	// The content parts should be separated by ";"

	// For example:  strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CCADSimulationDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = NULL;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != NULL)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CCADSimulationDoc diagnostics

#ifdef _DEBUG
void CCADSimulationDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CCADSimulationDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

