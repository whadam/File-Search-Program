
// SearchFileDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "SearchFile.h"
#include "SearchFileDlg.h"
#include "afxdialogex.h"
#include "FileFindEx.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
public:
//	CImageList m_img;
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CSearchFileDlg dialog



CSearchFileDlg::CSearchFileDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_SEARCHFILE_DIALOG, pParent)
	, m_strFileName(_T(""))
	, m_strFileLocation(_T(""))
	, m_bSub(FALSE)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_strToken = _T("");
}

void CSearchFileDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB1, m_tab);
	DDX_Text(pDX, IDC_EDIT_FILENAME, m_strFileName);
	DDX_Text(pDX, IDC_EDIT_FILELOCATION, m_strFileLocation);
	DDX_Check(pDX, IDC_CHECK_SUB, m_bSub);
	DDX_Control(pDX, IDC_BUTTON_START, m_btnStart);
	DDX_Control(pDX, IDC_BUTTON_STOP, m_btn_search);
	DDX_Control(pDX, IDC_LIST_RESULT, m_lstResult);
	DDX_Control(pDX, IDC_STATIC_STATUS, m_stcStatus);
}

BEGIN_MESSAGE_MAP(CSearchFileDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_START, &CSearchFileDlg::OnBnClickedButtonStart)
	ON_BN_CLICKED(IDC_BUTTON_STOP, &CSearchFileDlg::OnBnClickedButtonStop)
END_MESSAGE_MAP()


// CSearchFileDlg message handlers

BOOL CSearchFileDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	// link image to list control
	m_img.Create(IDB_LIST, 16, 2, RGB(255, 255, 255));
	m_lstResult.SetImageList(&m_img, LVSIL_SMALL);

	// list control header config
	m_lstResult.InsertColumn(0, "name", LVCFMT_LEFT, 150);
	m_lstResult.InsertColumn(1, "location", LVCFMT_LEFT, 150);
	m_lstResult.InsertColumn(2, "size(byte)", LVCFMT_RIGHT, 80);
	m_lstResult.InsertColumn(3, "create date", LVCFMT_CENTER, 80);
	m_tab.InsertItem(0, "name n location");

	// show current directory
	char pBuf[256];
	GetCurrentDirectory(256, pBuf);
	m_strFileLocation.Format("%s", pBuf);
	UpdateData(FALSE);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CSearchFileDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CSearchFileDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CSearchFileDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CSearchFileDlg::SearFileNotSub()
{
	// TODO: Add your implementation code here.
	// search excluding subfolders.
	UpdateData(TRUE);

	CString strTmp, strFolder, strName;
	CFileFindEx cfile;
	int i;
	BOOL b;
	MSG msg;

	if (m_strFileLocation.Right(1) == "\\")
		strTmp = m_strFileLocation + "*.*";
	else {
		strTmp = m_strFileLocation + "\\";
		strTmp += "*.*";
	}

	b = cfile.FindFile(strTmp);

	while (b) {
		while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		if (m_bStop) return;

		b = cfile.FindNextFile();

		if (cfile.IsDots())
			continue;

		i = m_lstResult.GetItemCount();

		m_stcStatus.SetWindowText(cfile.GetFilePath());

		strFolder = cfile.GetFilePath().Left(cfile.GetFilePath().ReverseFind('\\') + 1);

		strName = cfile.GetFileName();
		strName.MakeUpper();

		if (strName.Find(m_strToken) != -1) {
			if (cfile.IsDirectory()) {
				m_lstResult.AddItem(cfile.GetFileName(), i, 0, -1, 0);
				m_lstResult.AddItem(strFolder, i, 1);
				m_lstResult.AddItem("file folder", i, 2);
				m_lstResult.AddItem(cfile.GetCreationTimeString(), i, 3);
			}
			else {
				m_lstResult.AddItem(cfile.GetFileName(), i, 0, -1, 1);
				m_lstResult.AddItem(strFolder, i, 1);
				m_lstResult.AddItem(cfile.GetLengthString(), i, 2);
				m_lstResult.AddItem(cfile.GetCreationTimeString(), i, 3);
			}
		}
	}
}


void CSearchFileDlg::SearFile(CString strStartFolder)
{
	// TODO: Add your implementation code here.
	UpdateData(TRUE);

	CString strTmp, strFolder, strName;
	CFileFindEx cfile;
	int i;
	BOOL b;
	MSG msg;

	if (strStartFolder.Right(1) == '\\')
		strTmp = strStartFolder + "*.*";
	else {
		strTmp = strStartFolder + '\\';
		strTmp += "*.*";
	}

	b = cfile.FindFile(strTmp);

	while (b) {
		while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		if (m_bStop) return;

		b = cfile.FindNextFile();

		if (cfile.IsDots())
			continue;

		i = m_lstResult.GetItemCount();
		m_stcStatus.SetWindowText(cfile.GetFilePath());
		strFolder = cfile.GetFilePath().Left(cfile.GetFilePath().ReverseFind('\\') + 1);
		strName = cfile.GetFileName();
		strName.MakeUpper();

		if (cfile.IsDirectory()) {
			if (strName.Find(m_strToken) != -1) {
				m_lstResult.AddItem(cfile.GetFileName(), i, 0, -1, 0);
				m_lstResult.AddItem(strFolder, i, 1);
				m_lstResult.AddItem("file folder", i, 2);
				m_lstResult.AddItem(cfile.GetCreationTimeString(), i, 3);
			}
			SearFile(cfile.GetFilePath());
		}
		else {
			if (strName.Find(m_strToken) != -1) {
				m_lstResult.AddItem(cfile.GetFileName(), i, 0, -1, 1);
				m_lstResult.AddItem(strFolder, i, 1);
				m_lstResult.AddItem(cfile.GetLengthString(), i, 2);
				m_lstResult.AddItem(cfile.GetCreationTimeString(), i, 3);
			}
		}
	}
}


void CSearchFileDlg::OnBnClickedButtonStart()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	if (!IsFolder()) {
		MessageBox("not exist folder.");
		return;
	}

	GetDlgItem(IDC_BUTTON_START)->EnableWindow(FALSE);

	m_bStop = FALSE;

	m_strToken = m_strFileName;
	m_strToken.MakeUpper();

	if (m_lstResult.GetItemCount())
		m_lstResult.DeleteAllItems();
	if (m_bSub)
		SearFile(m_strFileLocation);
	else
		SearFileNotSub();

	GetDlgItem(IDC_BUTTON_START)->EnableWindow(TRUE);
}


void CSearchFileDlg::OnBnClickedButtonStop()
{
	// TODO: Add your control notification handler code here
	m_bStop = TRUE;
}

BOOL CSearchFileDlg::IsFolder(void)
{
	// 폴더나 드라이브가 존재하는지 검사
	UpdateData(TRUE);
	CFileFind cFile;
	BOOL b;

	if (m_strFileLocation.GetLength() <= 3) //드라이브명 검사
	{
		CString strTmp;
		if (m_strFileLocation.Right(1) == "\\")
			strTmp = m_strFileLocation + "*.*";
		else
			strTmp = m_strFileLocation + "\\*.*";

		if (cFile.FindFile(strTmp))
			return TRUE;
	}
	else//폴더명 검사
	{
		b = cFile.FindFile(m_strFileLocation);
		while (b)
		{
			b = cFile.FindNextFile();
			if (cFile.IsDirectory())
				return TRUE;
		}
	}
	return FALSE;

}