
// WSCAD.h : главный файл заголовка для приложения PROJECT_NAME
//

#pragma once

#ifndef __AFXWIN_H__
	#error "включить stdafx.h до включения этого файла в PCH"
#endif

#include "resource.h"		// основные символы


// CWSCADApp:
// О реализации данного класса см. WSCAD.cpp
//

class CWSCADApp : public CWinApp
{
public:
	CWSCADApp();

// Переопределение
public:
	virtual BOOL InitInstance();

// Реализация

	DECLARE_MESSAGE_MAP()
};

extern CWSCADApp theApp;