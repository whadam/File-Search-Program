
// SearchFileDlg.h : header file
//
#include "ListCtrlEx.h"

#pragma once


// CSearchFileDlg dialog
class CSearchFileDlg : public CDialogEx
{
// Construction
public:
	CSearchFileDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SEARCHFILE_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CTabCtrl m_tab;
	CString m_strFileName;
	CString m_strFileLocation;
	BOOL m_bSub;
	CButton m_btnStart;
	CButton m_btn_search;
	CListCtrlEx m_lstResult;
	CImageList m_img;
	void SearFileNotSub();
	BOOL m_bStop;
	CString m_strToken;
	void SearFile(CString strStartFolder);
	CStatic m_stcStatus;
	afx_msg void OnBnClickedButtonStart();
	afx_msg void OnBnClickedButtonStop();

	BOOL IsFolder();
};
