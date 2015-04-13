#include "stdafx.h"
#include "WndControl.h"
#include "CMenu.h"
#include "resource.h"



CMyWnd::CMyWnd():m_wnd1(false),m_wnd2(false),m_wnd3(false),m_wnd4(false){}
CMyWnd::~CMyWnd()
{
	m_wnd1=false;
	m_wnd2=false;
	m_wnd3=false;
	m_wnd4=false;
}
LPCTSTR CMyWnd::GetWindowClassName()const{ return _T("SendWnd"); }
CDuiString CMyWnd::GetSkinFile(){ return _T("XML\\skinUI.xml"); }
CDuiString CMyWnd::GetSkinFolder(){ return _T(""); }

void CMyWnd::Notify(TNotifyUI& msg)
{
	if (msg.sType==_T("click"))
	{
		CDuiString str = msg.pSender->GetName();
		if (str == _T("wnd1"))
		{
			m_wnd1=!m_wnd1;
			msg.pSender->SetText(m_wnd1?_T("审讯中"):_T("空闲中"));
			// To do here ...
		}
		else if (str == _T("wnd2"))
		{
			m_wnd2=!m_wnd2;
			msg.pSender->SetText(m_wnd2?_T("审讯中"):_T("空闲中"));
			// To do here ...
		}
		else if (str == _T("wnd3"))
		{
			m_wnd3=!m_wnd3;
			msg.pSender->SetText(m_wnd3?_T("审讯中"):_T("空闲中"));
			// To do here ...
		}
		else if (str == _T("wnd4"))
		{
			m_wnd4=!m_wnd4;
			msg.pSender->SetText(m_wnd4?_T("审讯中"):_T("空闲中"));
			// To do here ...
		}
		else if (str == _T("setbtn"))
		{
			POINT pt = {msg.ptMouse.x, msg.ptMouse.y};
			CMenu *pMenu = new CMenu(_T("XML/menu.xml"));
			pMenu->Init(*this, pt);
			pMenu->ShowWindow(TRUE);
		}
	}		
	return WindowImplBase::Notify(msg);
}

void CMyWnd::Start()
{
	HMODULE hd = (HMODULE)GetModuleHandle(NULL);
	CPaintManagerUI::SetInstance(hd);
	CMyWnd myWnd;
	myWnd.Create(NULL,_T("窗口控制台"),UI_WNDSTYLE_FRAME,WS_EX_WINDOWEDGE);
	myWnd.CenterWindow();
	myWnd.ShowModal();
}

void CMyWnd::TrayNotify(WPARAM wparam,LPARAM lparam)
{
	UINT uID = (UINT)wparam;
	UINT uMsg = (UINT)lparam;
	POINT pt;
	if (uMsg==WM_LBUTTONDBLCLK)
	{
		if (uID == IDI_ICON1)
		{
			GetCursorPos(&pt);
			::ShowWindow(m_hWnd,SW_SHOW);
		}
	}
}

LRESULT CMyWnd::OnSysCommand(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	LRESULT LR = WindowImplBase::OnSysCommand(uMsg,wParam,lParam,bHandled);
	if (wParam == SC_MINIMIZE )
	{
		::ShowWindow(m_hWnd,SW_HIDE);
	}
	return LR;
}

void CMyWnd::InitWindow()
{
	SetIcon(IDI_ICON1);
	NOTIFYICONDATA nid;
	nid.cbSize=sizeof(NOTIFYICONDATA);
	nid.hWnd=m_hWnd;
	nid.uID=IDI_ICON1;
	nid.uFlags=NIF_ICON|NIF_TIP|NIF_MESSAGE;
	nid.uCallbackMessage=WM_TRAY_MESSAGE;
	HMODULE hd = (HMODULE)GetModuleHandle(NULL);
	nid.hIcon=LoadIcon(hd,MAKEINTRESOURCE(IDI_ICON1));
	_tcscpy_s(nid.szTip,sizeof(nid.szTip),_T("窗口控制台"));
	Shell_NotifyIcon(NIM_ADD,&nid);
}

LRESULT CMyWnd::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if (uMsg==WM_TRAY_MESSAGE)
	{
		TrayNotify(wParam,lParam);
	}
	return WindowImplBase::HandleMessage(uMsg,wParam,lParam);
}