
// Pen2View.cpp: CPen2View 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "Pen2.h"
#endif

#include "Pen2Doc.h"
#include "Pen2View.h"
#include "CLine.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CPen2View

IMPLEMENT_DYNCREATE(CPen2View, CView)

BEGIN_MESSAGE_MAP(CPen2View, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_MOUSEMOVE()
	ON_COMMAND(ID_SELECT_COLOR, &CPen2View::OnSelectColor)
END_MESSAGE_MAP()

// CPen2View 생성/소멸

CPen2View::CPen2View() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CPen2View::~CPen2View()
{
}

BOOL CPen2View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CPen2View 그리기
COLORREF col;
void CPen2View::OnDraw(CDC* pDC)
{
	CPen2Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	int n = pDoc->m_oa.GetSize();
	CLine* p;
	for (int i = 0; i < n; i++) {
		p = (CLine*)pDoc->m_oa[i];
		p->Draw(pDC);
	}
	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
}


// CPen2View 인쇄

BOOL CPen2View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CPen2View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CPen2View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CPen2View 진단

#ifdef _DEBUG
void CPen2View::AssertValid() const
{
	CView::AssertValid();
}

void CPen2View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CPen2Doc* CPen2View::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPen2Doc)));
	return (CPen2Doc*)m_pDocument;
}
#endif //_DEBUG


// CPen2View 메시지 처리기

CPoint pnt;
void CPen2View::OnMouseMove(UINT nFlags, CPoint point)
{
	if (nFlags == MK_LBUTTON) {
		CLine* p = new CLine(pnt, point, col);
		GetDocument()->m_oa.Add(p);
		Invalidate(0);
	}
	pnt = point;

	CView::OnMouseMove(nFlags, point);
}


void CPen2View::OnSelectColor()
{
	CColorDialog dlg;
	if (dlg.DoModal() == IDOK)
		col = dlg.GetColor();

}
