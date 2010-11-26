
// UtilTestView.cpp : CUtilTestView 类的实现
//

#include "stdafx.h"
#include "UtilTest.h"

#include "UtilTestDoc.h"
#include "UtilTestView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CUtilTestView

IMPLEMENT_DYNCREATE(CUtilTestView, CView)

BEGIN_MESSAGE_MAP(CUtilTestView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CUtilTestView 构造/析构

CUtilTestView::CUtilTestView()
{
	// TODO: 在此处添加构造代码

}

CUtilTestView::~CUtilTestView()
{
}

BOOL CUtilTestView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CUtilTestView 绘制

void CUtilTestView::OnDraw(CDC* /*pDC*/)
{
	CUtilTestDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
}


// CUtilTestView 打印

BOOL CUtilTestView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CUtilTestView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CUtilTestView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}


// CUtilTestView 诊断

#ifdef _DEBUG
void CUtilTestView::AssertValid() const
{
	CView::AssertValid();
}

void CUtilTestView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CUtilTestDoc* CUtilTestView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CUtilTestDoc)));
	return (CUtilTestDoc*)m_pDocument;
}
#endif //_DEBUG


// CUtilTestView 消息处理程序
