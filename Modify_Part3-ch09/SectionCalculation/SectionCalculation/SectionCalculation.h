
// SectionCalculation.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CSectionCalculationApp: 
// �йش����ʵ�֣������ SectionCalculation.cpp
//

class CSectionCalculationApp : public CWinApp
{
public:
	CSectionCalculationApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CSectionCalculationApp theApp;