/****************************************************
   SREngine类，将MS SAPI的语音识别引擎封装，用于语音识别
****************************************************/

#ifndef SRENGINE_H
#define SRENGINE_H

#include <QString.h>
#include <QMessageBox>

// Microsoft Speech API
#undef UNICODE
#include <sapi.h>
#include <sphelper.h>
#include <spuihelp.h>
#include <comdef.h>
#define UNICODE

#include <windows.h>
#include <windowsx.h>
#include <commctrl.h>

#define  WM_RECOEVENT WM_USER+100
#define GID_SRCMD_CN 1234
#define MYGRAMMARID  101

class SREngine
{
public:
    SREngine();
    ~SREngine();

public:
    //speech varibale
    CComPtr <ISpRecognizer> m_cpRecognizer;
    CComPtr <ISpRecoContext> m_cpRecoContext;
    CComPtr <ISpRecoGrammar> m_cpCmdGrammar;

    //audio variable
    CComPtr <ISpAudio> m_cpAudio;

public:
    HRESULT SetRuleState(const WCHAR * pszRuleName, const WCHAR *pszValue, BOOL fActivate);
    HRESULT LoadCmdFromFile(QString XMLFileName);
    HRESULT InitializeSapi(WId hWnd, UINT Msg);

};

#endif // SRENGINE_H
