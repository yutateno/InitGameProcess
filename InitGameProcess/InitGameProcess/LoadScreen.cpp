#include "LoadScreen.hpp"



/// ---------------------------------------------------------------------------------------
LoadScreen::LoadScreen()
{
	// 情報初期化
	draw = -1;
	walkCount = 0;


	LoadFile::MyLoad("media\\load.png", draw, ELOADFILE::graph);
} /// LoadScreen::LoadScreen()



/// ---------------------------------------------------------------------------------------
LoadScreen::~LoadScreen()
{
	GRAPHIC_RELEASE(draw);
}



/// ---------------------------------------------------------------------------------------
void LoadScreen::Process(const int num, const int max)
{
	if (++walkCount > 5) walkCount = 0;


	// 読み込み個数に応じて右から左に走らせる
	if (num <= max)
	{
		DrawGraph(0, 0, draw, false);
	}
}
