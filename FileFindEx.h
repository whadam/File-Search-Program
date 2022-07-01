#pragma once
#include <afx.h>

class CFileFindEx : public CFileFind
{
public:
	CString GetCreationTimeString(CString strTmp = "-");
	CString GetLengthString();
};

