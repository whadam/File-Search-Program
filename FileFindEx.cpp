#include "pch.h"
#include "FileFindEx.h"

CString CFileFindEx::GetCreationTimeString(CString strTmp /* "-" */)
{
	// 파일 생성 시간을 string으로 반환하는 함수
	CString str;
	CTime cTime;

	GetCreationTime(cTime);	// 파일의 생성시간 얻기

	// 생성시간을 '-'로 구분된 형태로 만든다.
	str.Format("%02d%s%02d%s%02d	%02d:%02d", cTime.GetYear(), strTmp, cTime.GetMonth(), strTmp, cTime.GetDay(), cTime.GetHour(), cTime.GetDay());
	
	return str;
}

CString CFileFindEx::GetLengthString()
{
	// 파일의 크기를 string으로 반환하는 함수
	CString str;

	str.Format("%lu", GetLength());

	return str;
}