
// ReadPch.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// CReadPchApp:
// �� Ŭ������ ������ ���ؼ��� ReadPch.cpp�� �����Ͻʽÿ�.
//

class CReadPchApp : public CWinApp
{
public:
	CReadPchApp();

// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern CReadPchApp theApp;