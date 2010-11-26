
// UtilTestDoc.cpp : CUtilTestDoc 类的实现
//

#include "stdafx.h"
#include "UtilTest.h"

#include "UtilTestDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CUtilTestDoc

IMPLEMENT_DYNCREATE(CUtilTestDoc, CDocument)

BEGIN_MESSAGE_MAP(CUtilTestDoc, CDocument)
END_MESSAGE_MAP()


// CUtilTestDoc 构造/析构

CUtilTestDoc::CUtilTestDoc()
{
	// TODO: 在此添加一次性构造代码

}

CUtilTestDoc::~CUtilTestDoc()
{
}

BOOL CUtilTestDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 在此添加重新初始化代码
	// (SDI 文档将重用该文档)

	return TRUE;
}




// CUtilTestDoc 序列化

void CUtilTestDoc::Serialize(CArchive& ar)
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


// CUtilTestDoc 诊断

#ifdef _DEBUG
void CUtilTestDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CUtilTestDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CUtilTestDoc 命令
