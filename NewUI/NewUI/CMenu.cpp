#include "stdafx.h"
#include "CMenu.h"

CMenu::CMenu(LPCTSTR pszXMLPath):m_strXMLPath(pszXMLPath){}
CMenu::~CMenu(){ delete this;}
LPCTSTR CMenu::GetWindowClassName()const{ return _T("Config");}
CDuiString CMenu::GetSkinFile(){ return m_strXMLPath; }
CDuiString CMenu::GetSkinFolder(){ return _T(""); }
void CMenu::Init(HWND hWndParent, POINT ptPos)
{
	Create(hWndParent, _T("ConfigWnd"), UI_WNDSTYLE_FRAME, WS_EX_WINDOWEDGE);
	::ClientToScreen(hWndParent, &ptPos);
	::SetWindowPos(*this, NULL, ptPos.x, ptPos.y+20, 0, 0, SWP_NOZORDER | SWP_NOSIZE | SWP_NOACTIVATE);
}
void CMenu::Notify(TNotifyUI& msg)
{
	if (msg.sType==_T("click"))
	{
		CDuiString str=msg.pSender->GetName();
		if (str==_T("ok_btn"))
		{
			TCHAR strEdit[24];
			TCHAR strCombo[24];
			for (int i=0;i<5;++i)
			{
				_stprintf(strEdit,_T("%s%d"),_T("config_edit"),i);
				_stprintf(strCombo,_T("%s%d"),_T("config_combo"),i);
				CEditUI* pEdit=static_cast<CEditUI*>(m_PaintManager.FindControl(strEdit));
				CComboBoxUI* pCombo=static_cast<CComboBoxUI*>(m_PaintManager.FindControl(strCombo));
				CDuiString str=pEdit->GetText();
				pCombo->SetText(pEdit->GetText());
				pCombo->GetText();		
			}
			HWND hwnd = ::FindWindow(_T("Config"),_T("ConfigWnd"));
			::DestroyWindow(hwnd);
		}
	}
}
