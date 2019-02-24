#include "LoadScreen.hpp"



/// ---------------------------------------------------------------------------------------
LoadScreen::LoadScreen()
{
	// î•ñ‰Šú‰»
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


	// “Ç‚İ‚İŒÂ”‚É‰‚¶‚Ä‰E‚©‚ç¶‚É‘–‚ç‚¹‚é
	if (num <= max)
	{
		DrawGraph(0, 0, draw, false);
	}
}
