#include "LoadScreen.hpp"



/// ---------------------------------------------------------------------------------------
LoadScreen::LoadScreen()
{
	// î•ñ‰Šú‰»
	for (int i = 0; i != 1; ++i)
	{
		draw[i] = -1;
	}
	endDraw = 0;
	walkCount = 0;


	LoadFile::MyLoad("media\\clph_2d\\scrollaction\\walk\\normal\\1.pyn", draw[0], ELOADFILE::graph);
	LoadFile::MyLoad("media\\clph_2d\\scrollaction\\ex\\normal\\jamp2.pyn", endDraw, ELOADFILE::graph);
} /// LoadScreen::LoadScreen()



/// ---------------------------------------------------------------------------------------
LoadScreen::~LoadScreen()
{
	for (int i = 0; i != 1; ++i)
	{
		GRAPHIC_RELEASE(draw[i]);
	}
	GRAPHIC_RELEASE(endDraw);
}



/// ---------------------------------------------------------------------------------------
void LoadScreen::Process(const int num, const int max)
{
	if (++walkCount > 5) walkCount = 0;


	// “Ç‚İ‚İŒÂ”‚É‰‚¶‚Ä‰E‚©‚ç¶‚É‘–‚ç‚¹‚é
	if (num < max)
	{
		DrawGraph(BASICPARAM::winWidth, BASICPARAM::winHeight - 260, draw[0], true);
	}
	else
	{
		DrawGraph(0, BASICPARAM::winHeight - 260, endDraw, true);
	}
}
