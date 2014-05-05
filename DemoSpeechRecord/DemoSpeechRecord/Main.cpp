//************ Main.cpp *****************
//Created on Wed Jun 05 16:12:36 2013
//@author: Bill
// To use it, you should add the dependency of "Winmm.lib" in the project preferences.
//******************************************************************************************//
#include <stdio.h>
#include <Windows.h>
#include "SpeechRecord.h"

#pragma comment(lib,"Winmm.lib")

int main()
{
	// Set wave format when sampling the audio
	WAVEFORMATEX wf;
	SetWaveFormat(&wf,1,1,12000,1,8,0);
	
	// Open wave input channel
	HWAVEIN hWaveIn;
	OpenWaveIn(&hWaveIn,&wf);

	// Prepare Wave In Header and allocate memory
	WAVEHDR waveHdr;
	DWORD dataSize = 240000L;
	PrepareWaveIn(&hWaveIn, &waveHdr, dataSize);

	// Start recording
	StartRecord(&hWaveIn);
	
	Sleep(10000);

	// Stop recording
	MMTIME mmt;
	StopRecord(&hWaveIn, &mmt);

	SaveRecordtoFile("test//myTest.wav",&wf,&hWaveIn,&waveHdr,&mmt);

	ReleaseWaveIn(&hWaveIn, &waveHdr);
	CloseWaveIn(&hWaveIn);

	system("pause");
	return 0;
}