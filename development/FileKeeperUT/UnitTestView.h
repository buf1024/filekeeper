
// UnitTestView.h : CUnitTestView 类的接口
//


#pragma once


class CUnitTestView : public CView
{
protected: // 仅从序列化创建
	CUnitTestView();
	DECLARE_DYNCREATE(CUnitTestView)

// 属性
public:
	CUnitTestDoc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	virtual ~CUnitTestView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // UnitTestView.cpp 中的调试版本
inline CUnitTestDoc* CUnitTestView::GetDocument() const
   { return reinterpret_cast<CUnitTestDoc*>(m_pDocument); }
#endif

