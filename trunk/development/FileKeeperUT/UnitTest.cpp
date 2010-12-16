
// UnitTest.cpp : 定义应用程序的类行为。
//

#include "stdafx.h"
#include "afxwinappex.h"
#include "UnitTest.h"
#include "MainFrm.h"

#include "UnitTestDoc.h"
#include "UnitTestView.h"

#include <cppunit.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CUnitTestApp

BEGIN_MESSAGE_MAP(CUnitTestApp, CWinApp)
	ON_COMMAND(ID_APP_ABOUT, &CUnitTestApp::OnAppAbout)
	// 基于文件的标准文档命令
	ON_COMMAND(ID_FILE_NEW, &CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, &CWinApp::OnFileOpen)
	// 标准打印设置命令
	ON_COMMAND(ID_FILE_PRINT_SETUP, &CWinApp::OnFilePrintSetup)
END_MESSAGE_MAP()


// CUnitTestApp 构造

CUnitTestApp::CUnitTestApp()
{

	// TODO: 在此处添加构造代码，
	// 将所有重要的初始化放置在 InitInstance 中
}

// 唯一的一个 CUnitTestApp 对象

CUnitTestApp theApp;


// CUnitTestApp 初始化

BOOL CUnitTestApp::InitInstance()
{
	CWinApp::InitInstance();
	RunUnitTest();
	return FALSE;
}



// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()

// 用于运行对话框的应用程序命令
void CUnitTestApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

// CUnitTestApp 消息处理程序



void CUnitTestApp::RunUnitTest()
{
	CppUnit::MfcUi::TestRunner runner;
	CppUnit::TestFactoryRegistry& reg = CppUnit::TestFactoryRegistry::getRegistry();
	runner.addTest(reg.makeTest());
	runner.run();
}

