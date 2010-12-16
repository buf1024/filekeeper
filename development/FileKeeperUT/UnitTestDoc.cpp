
// UnitTestDoc.cpp : CUnitTestDoc 类的实现
//

#include "stdafx.h"
#include "UnitTest.h"

#include "UnitTestDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CUnitTestDoc

IMPLEMENT_DYNCREATE(CUnitTestDoc, CDocument)

BEGIN_MESSAGE_MAP(CUnitTestDoc, CDocument)
END_MESSAGE_MAP()


// CUnitTestDoc 构造/析构

CUnitTestDoc::CUnitTestDoc()
{
	// TODO: 在此添加一次性构造代码

}

CUnitTestDoc::~CUnitTestDoc()
{
}

BOOL CUnitTestDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 在此添加重新初始化代码
	// (SDI 文档将重用该文档)

	return TRUE;
}




// CUnitTestDoc 序列化

void CUnitTestDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 在此添加存储代码
	}
	else
	{
		// TODO: 在此添加加载代码
	}
}


// CUnitTestDoc 诊断

#ifdef _DEBUG
void CUnitTestDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CUnitTestDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CUnitTestDoc 命令
