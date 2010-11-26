
// UtilTestView.h : CUtilTestView 类的接口
//


#pragma once


class CUtilTestView : public CView
{
protected: // 仅从序列化创建
	CUtilTestView();
	DECLARE_DYNCREATE(CUtilTestView)

// 属性
public:
	CUtilTestDoc* GetDocument() const;

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
	virtual ~CUtilTestView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // UtilTestView.cpp 中的调试版本
inline CUtilTestDoc* CUtilTestView::GetDocument() const
   { return reinterpret_cast<CUtilTestDoc*>(m_pDocument); }
#endif

