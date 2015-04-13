#pragma once
#include "stdafx.h"
#include <UIlib.h>
#pragma comment(lib,"DuiLib_ud.lib")
using namespace DuiLib;

class CMenu:public WindowImplBase
{
private:
	CDuiString  m_strXMLPath;
public:
	virtual ~CMenu();
	CMenu(LPCTSTR pszXMLPath);
	virtual LPCTSTR GetWindowClassName()const;
	virtual CDuiString GetSkinFile();
	virtual CDuiString GetSkinFolder();
	void Init(HWND hWndParent, POINT ptPos);
	void Notify(TNotifyUI& msg);
};
