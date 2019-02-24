#include "Basic.hpp"


// extern ïœêî
ESceneNumber BASICPARAM::e_preScene;
ESceneNumber BASICPARAM::e_nowScene;
int BASICPARAM::winWidth;
int BASICPARAM::winHeight;
int BASICPARAM::bitColor;
bool BASICPARAM::startFeedNow;
bool BASICPARAM::endFeedNow;
int BASICPARAM::feedColor;



/// debug-----------------------------------------------------------------------------------------------------------------------
#ifdef _DEBUG
//bool MyDebug::checkFlag = false;
//bool MyDebug::characterDrawFlag = false;



/// --------------------------------------------------------------------------------------------------
void MyDebug::Init()
{
	//checkFlag = false;
	//characterDrawFlag = false;
}



/// --------------------------------------------------------------------------------------------------
void MyDebug::DebugProcess()
{
	/*if (CheckHitKey(KEY_INPUT_LCONTROL) == 1 && DLLXinput::GetPadButtonData(DLLXinput::GetPlayerPadNumber(), DLLXinput::XINPUT_PAD::BUTTON_BACK) == 1)
	{
		checkFlag = !checkFlag;
	}*/

	if (CheckHitKey(KEY_INPUT_RCONTROL) == 1 && DLLXinput::GetPadButtonData(DLLXinput::GetPlayerPadNumber(), DLLXinput::XINPUT_PAD::BUTTON_BACK) == 1)
	{
		Init();
	}

	/*if (checkFlag)
	{
		DrawBox(960, 0, 1920, 540, GetColor(255, 255, 255), true);
		DrawFormatString(970, 520, GetColor(0, 0, 0), "checkFlag: LCONTROL: %s", checkFlag ? "true" : "false");
		DrawFormatString(970, 500, GetColor(0, 0, 0), "Init(): RCONTROL");

		DrawFormatString(970, 10, GetColor(0, 0, 0), "characterDrawFlag: A: %s", characterDrawFlag ? "true" : "false");
		if (CheckHitKey(KEY_INPUT_A) == 1 && DLLXinput::GetPadButtonData(DLLXinput::GetPlayerPadNumber(), DLLXinput::XINPUT_PAD::BUTTON_BACK) == 1)
		{
			characterDrawFlag = !characterDrawFlag;
		}
	}*/
}
#endif // _DEBUG
/// debug-----------------------------------------------------------------------------------------------------------------------
