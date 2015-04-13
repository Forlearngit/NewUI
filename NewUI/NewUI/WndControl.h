#pragma once
#include "stdafx.h"
#include <../DuiLib/UIlib.h>
#pragma comment(lib,"DuiLib_ud.lib")
using namespace DuiLib;

#define WM_TRAY_MESSAGE (WM_USER+1)

class CMyWnd:public WindowImplBase
{
public:
	CMyWnd();
	~CMyWnd();
private:
	virtual LPCTSTR GetWindowClassName()const;
	virtual CDuiString GetSkinFile();
	virtual CDuiString GetSkinFolder();
	virtual void Notify(TNotifyUI& msg);
	void TrayNotify(WPARAM wparam,LPARAM lparam);
	virtual void InitWindow();
	virtual LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
	virtual LRESULT OnSysCommand(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
public:
	void Start();

private:
	bool m_wnd1;
	bool m_wnd2;
	bool m_wnd3;
	bool m_wnd4;
};