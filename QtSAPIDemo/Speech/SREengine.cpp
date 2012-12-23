#include "SREngine.h"

SREngine::SREngine()
{
}

SREngine::~SREngine()
{
}

HRESULT SREngine::InitializeSapi(WId hWnd, UINT Msg)
{
    HRESULT hr = S_OK;

    //FOR ONE NOT FOR ALL
    /* 独享模式的配置 */
    hr = m_cpRecognizer.CoCreateInstance( CLSID_SpInprocRecognizer);  //独享模式
    if(FAILED(hr))
    {
        QMessageBox::information(NULL, "Error", "Create recognizer error", MB_OK);
        return hr;
    }

    hr = SpCreateDefaultObjectFromCategoryId(SPCAT_AUDIOIN, &m_cpAudio); //建立默认的音频输入对象
    if(FAILED(hr))
    {
        QMessageBox::information(NULL, "Error", "Create default audio object error", MB_OK);
        return hr;
    }

    hr = m_cpRecognizer ->SetInput(m_cpAudio, TRUE);  //设置识别引擎输入源
    if(FAILED(hr))
    {
        QMessageBox::information(NULL, "Error", "Error setINPUT", MB_OK);
        return hr;
    }

    hr = m_cpRecognizer->CreateRecoContext(&m_cpRecoContext);   //创建识别上下文接口
    if(FAILED(hr))
    {
        QMessageBox::information(NULL, "Error", "Error CreateRecoContext", MB_OK);
        return hr;
    }

    hr =  m_cpRecoContext->SetNotifyWindowMessage(hWnd, Msg, 0, 0);  //设置识别消息
    if(FAILED(hr))
    {
        QMessageBox::information(NULL, "Error", "Error SetNotifyWindowMessage", MB_OK);
        return hr;
    }

    const ULONGLONG ullInterest = SPFEI(SPEI_SOUND_START) | SPFEI(SPEI_SOUND_END) |
                                      SPFEI(SPEI_PHRASE_START) | SPFEI(SPEI_RECOGNITION) |
                                      SPFEI(SPEI_FALSE_RECOGNITION) | SPFEI(SPEI_HYPOTHESIS) |
                                      SPFEI(SPEI_INTERFERENCE) | SPFEI(SPEI_RECO_OTHER_CONTEXT) |
                                      SPFEI(SPEI_REQUEST_UI) | SPFEI(SPEI_RECO_STATE_CHANGE) |
                                      SPFEI(SPEI_PROPERTY_NUM_CHANGE) | SPFEI(SPEI_PROPERTY_STRING_CHANGE);
    hr = m_cpRecoContext->SetInterest(ullInterest, ullInterest);   //设置感兴趣的事件
    if(FAILED(hr))
    {
        QMessageBox::information(NULL, "Error", "Error set interest", MB_OK);
    }

    return hr;
}

HRESULT SREngine::LoadCmdFromFile(QString XMLFileName)
{
    HRESULT hr = S_OK;

    if(!m_cpCmdGrammar)
    {
        hr = m_cpRecoContext ->CreateGrammar(MYGRAMMARID, &m_cpCmdGrammar);  //命令式（command and control---C&C）
        if(FAILED(hr))
        {
            QMessageBox::information(NULL, "Error", "Error Creategammar", MB_OK);
            return hr;
        }

        WCHAR wszXMLFile[256] = L"";
        XMLFileName.toWCharArray(wszXMLFile);  //ASNI TO UNICODE

        //LAOD RULE FROME XML FILE
        hr = m_cpCmdGrammar->LoadCmdFromFile(wszXMLFile, SPLO_DYNAMIC);
        if(FAILED(hr))
        {
            QMessageBox::information(NULL, "Error", "Error LoadCmdFromFile", MB_OK);
            return hr;
        }
    }
    return hr;
}

HRESULT SREngine::SetRuleState(const WCHAR * pszRuleName, const WCHAR *pszValue, BOOL fActivate)
{
    HRESULT hr = S_OK;

    if(fActivate)
    {
        hr = m_cpCmdGrammar ->SetRuleState(pszRuleName, NULL, SPRS_ACTIVE);
    }
    else
    {
        hr = m_cpCmdGrammar ->SetRuleState(pszRuleName, NULL, SPRS_INACTIVE);
    }
    return hr;

}
