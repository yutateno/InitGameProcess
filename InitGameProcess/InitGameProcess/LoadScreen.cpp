#include "LoadScreen.hpp"



/// ---------------------------------------------------------------------------------------
LoadScreen::LoadScreen()
{
	// ��񏉊���
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


	// �ǂݍ��݌��ɉ����ĉE���獶�ɑ��点��
	if (num <= max)
	{
		DrawGraph(0, 0, draw, false);
	}
}
