#include "pch.h"
#include "FileFindEx.h"

CString CFileFindEx::GetCreationTimeString(CString strTmp /* "-" */)
{
	// ���� ���� �ð��� string���� ��ȯ�ϴ� �Լ�
	CString str;
	CTime cTime;

	GetCreationTime(cTime);	// ������ �����ð� ���

	// �����ð��� '-'�� ���е� ���·� �����.
	str.Format("%02d%s%02d%s%02d	%02d:%02d", cTime.GetYear(), strTmp, cTime.GetMonth(), strTmp, cTime.GetDay(), cTime.GetHour(), cTime.GetDay());
	
	return str;
}

CString CFileFindEx::GetLengthString()
{
	// ������ ũ�⸦ string���� ��ȯ�ϴ� �Լ�
	CString str;

	str.Format("%lu", GetLength());

	return str;
}