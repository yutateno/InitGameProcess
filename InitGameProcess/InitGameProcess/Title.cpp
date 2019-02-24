#include "Title.hpp"



/// --------------------------------------------------------------------------------------------------------------
Title::Title(const std::vector<int> v_file)
{
	backGroundDraw = v_file[static_cast<int>(EFILE::backGroundDraw)];
}



/// --------------------------------------------------------------------------------------------------------------
Title::~Title()
{
}



/// --------------------------------------------------------------------------------------------------------------
void Title::Draw()
{
	DrawGraph(0, 0, backGroundDraw, false);
}



/// --------------------------------------------------------------------------------------------------------------
void Title::Process()
{
	if (DLLXinput::GetPadButtonData(DLLXinput::XINPUT_PAD::NUM01, DLLXinput::XINPUT_PAD::BUTTON_A) == 1
		|| CheckHitKey(KEY_INPUT_Z) == 1)
	{
		BASICPARAM::endFeedNow = true;
		BaseScene::SetScene(ESceneNumber::GAMELOAD);
	}
}
