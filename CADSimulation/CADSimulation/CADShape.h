#pragma once
class CCADShape : public CObject
{
public:
  CCADShape();
  virtual ~CCADShape();

  enum RealName
  {
    SHAPE_TYPE_DEFAULT,
    SHAPE_TYPE_DRAG
  };

protected:
  CPoint m_objBeginPoint;
  CPoint m_objEndPoint;
  int m_nRotation;

  CPoint m_objBeginPointBefore;  //用于精确拖拽操作
  CPoint m_objEndPointBefore;

  int m_nPenWidth;
  int m_nPenStyle;
  COLORREF  m_nPenColor;
  COLORREF  m_nBrushColor;

  int m_nPenWidthSwitch;
  int m_nPenStyleSwitch;
  COLORREF  m_nPenColorSwitch;
  COLORREF  m_nBrushColorSwitch;

  bool m_bIsSavable;

  static CDC *m_pStaticDCMem;
  static CBitmap *m_pStaticBitmap;
  static bool m_bIsDrawingBackground;
public:
  virtual int SetBeginPoint(CPoint & objBeginPoint);
  virtual int SetEndPoint(CPoint & objEndPoint);
  virtual CDC * Draw(HWND hWnd, CDC * pDC);
  virtual int SaveThisShape(CPoint & objPoint);
  CDC * GetMemDC(HWND hWnd, CDC * pDC);
  int DrawTheBigPicture(HWND hWnd, CDC * pDC);
  int ResetMemDCBackground(HWND hWnd, CDC * pDC);
  virtual BOOL IsSelected(LPRECT pUserRect);
  int WhenSelected();
  int WhenUnselected();
  virtual int WhenDragged(int nCoordXOffset, int nCoordYOffset);
  virtual int WhenDraggedCommandMode(int nCoordXOffset, int nCoordYOffset);
  virtual int WhenUndraggedCommandMode(CPoint &ptBegin, CPoint& ptEnd);
  virtual int BeforeBeingDragged();
  int AfterBeingDragged();
  int SetBrush(COLORREF color);
  int SetPen(int PenWidth, int PenStyle, COLORREF PenColor);
  int SetRotation(int nRotation);

  void Serialize(CArchive& archive);

  virtual RealName RevealActualType();

  CPoint GetBeginPointBeforeDragged();
  CPoint GetEndPointBeforeDragged();
  void ResetDraggingAnchor();
};

