
// UnitTestView.cpp : CUnitTestView 类的实现
//

#include "stdafx.h"
#include "UnitTest.h"

#include "UnitTestDoc.h"
#include "UnitTestView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CUnitTestView

IMPLEMENT_DYNCREATE(CUnitTestView, CView)

BEGIN_MESSAGE_MAP(CUnitTestView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CUnitTestView 构造/析构

CUnitTestView::CUnitTestView()
{
	// TODO: 在此处添加构造代码

}

CUnitTestView::~CUnitTestView()
{
}

BOOL CUnitTestView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CUnitTestView 绘制

void CUnitTestView::OnDraw(CDC* /*pDC*/)
{
	CUnitTestDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
}


// CUnitTestView 打印

BOOL CUnitTestView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CUnitTestView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CUnitTestView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}


// CUnitTestView 诊断

#ifdef _DEBUG
void CUnitTestView::AssertValid() const
{
	CView::AssertValid();
}

void CUnitTestView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CUnitTestDoc* CUnitTestView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CUnitTestDoc)));
	return (CUnitTestDoc*)m_pDocument;
}
#endif //_DEBUG


// CUnitTestView 消息处理程序
