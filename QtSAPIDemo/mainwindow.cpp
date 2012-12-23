#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <Speech/SREngine.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //SAPI init
    m_bSoundStart = false;
    m_bSoundEnd = false;
    m_tPreTime = 0;
    m_tDelay = 1000;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButtonStart_clicked()
{
    HRESULT hr = m_SREngine.InitializeSapi(this->winId(), WM_RECOEVENT);  //初始化SAPI
    if(FAILED(hr))
    {
        return;
    }
    QString grammarFileName = "../SpeechGrammar.xml";
    hr = m_SREngine.LoadCmdFromFile(grammarFileName);   //创建语法规则
    if(FAILED(hr))
    {
        return;
    }

    /* 激活语音控制 */
    hr = m_SREngine.SetRuleState(NULL, NULL, SPRS_ACTIVE);
    if(FAILED(hr))
    {
        QMessageBox::information(NULL, "Error", "SetRuleState Active Error!", MB_OK);
        return;
    }

    setWindowTitle("Sound Start");
    ui->pushButtonStart->setEnabled(false);
}

bool MainWindow::winEvent(MSG* pMsg, long* result)
{
    setWindowTitle("Control - Debug: winEvent");
    if(pMsg->message == WM_RECOEVENT)
    {
        *result = this->OnRecoEvent();
    }
    return false;
}

// Speech Recognition Event Process
LRESULT MainWindow::OnRecoEvent()
{
    USES_CONVERSION;
    CSpEvent event;

    HRESULT hr = S_OK;
    if(m_SREngine.m_cpRecoContext)
    {
        while(event.GetFrom(m_SREngine.m_cpRecoContext) == S_OK)
        {
            //Get the ID
            setWindowTitle("Control - Debug");
            switch(event.eEventId)
            {
                case SPEI_REQUEST_UI:
                case SPEI_INTERFERENCE:
                case SPEI_PROPERTY_NUM_CHANGE:
                case SPEI_PROPERTY_STRING_CHANGE:
                case SPEI_RECO_STATE_CHANGE:
                case SPEI_RECO_OTHER_CONTEXT:
                    break;
                case SPEI_SOUND_START:
                    m_bSoundStart = true;
                    setWindowTitle("Control - Sound Start");
                    break;
                case SPEI_SOUND_END:
                    m_bSoundEnd = true;
                    setWindowTitle("Control - Sound End");
                    break;
                case SPEI_FALSE_RECOGNITION:
                    setWindowTitle("Control - False Recognition");
                    break;
                case SPEI_HYPOTHESIS:
                    setWindowTitle("Control - Hypothesis");
                    //break;
                case SPEI_RECOGNITION:
                {
                    CComPtr <ISpRecoResult> cpResult;
                    CSpDynamicString dstrText;
                    QString strResult;
                    cpResult = event.RecoResult();
                    cpResult->GetText(SP_GETWHOLEPHRASE, SP_GETWHOLEPHRASE, TRUE, &dstrText, NULL);
                    strResult = W2T(dstrText);

                    if(m_bSoundStart && m_bSoundEnd)
                    //if(1)
                    {
                        int dt;
                        QString strLogTxt;
                        SYSTEMTIME st;
                        GetLocalTime(&st);

                        if(!m_tPreTime)
                        {
                            m_tPreTime = (st.wHour*3600+st.wMinute*60+st.wSecond)*1000+st.wMilliseconds;
                            m_tDelay = 1000;
                        }
                        else
                        {
                            dt = (st.wHour*3600+st.wMinute*60+st.wSecond)*1000+st.wMilliseconds;
                            m_tDelay = dt - m_tPreTime;
                            if(m_tDelay < 0)m_tDelay += 24*3600*1000;
                            m_tPreTime = dt;
                        }

                        if(m_tDelay>500){
                            if((strResult == QString("Forward") || strResult == QString("Move Forward") || strResult == QString("Move") ))
                            {
                                //OnForeback();
                            }
                            else if(/*dTimems>500 && (strResult == QString("Turn left") || */strResult == QString("Left") )
                            {
                                //OnLeft();
                            }
                            else if(/*dTimems>500 && (strResult == QString("Turn right") || */strResult == QString("Right") )
                            {
                                //OnRight();
                            }
                            else if(strResult == QString("Stop")/* || strResult == QString("Stop moving")*/)
                            {
                                //OnForward();
                            }
                            else if(strResult == QString("Open") )
                            {
                                //OnFOpen();
                            }


                            char temp[256];
                            sprintf(temp,"[%02d:%02d:%02d %03d] %d ",st.wHour,st.wMinute,st.wSecond,st.wMilliseconds,m_tDelay);
                            strLogTxt.append(temp);
                            ui->textEdit->insertPlainText(strLogTxt + strResult+" Sent\n");

                            QString strWinTxt = "Control - ";
                            strWinTxt += strResult;
                            setWindowTitle(strWinTxt);

                            cpResult.Release();
                            m_bSoundStart = false;
                            m_bSoundEnd = false;
                            //Sleep(200);
                        }
                    }
                    break;
                }
                default:
                    break;
            }
        }
    }
    return true;
}
