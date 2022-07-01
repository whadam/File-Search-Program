#pragma once


// CListCtrlEx

class CListCtrlEx : public CListCtrl
{
	DECLARE_DYNAMIC(CListCtrlEx)

public:
	CListCtrlEx();
	virtual ~CListCtrlEx();
	int AddItem(LPCTSTR strItem, int nItem, int nSubItem = 0, UINT nState = -1, int nImageIndex = -1, long nParam = -1);
protected:
	DECLARE_MESSAGE_MAP()
};


