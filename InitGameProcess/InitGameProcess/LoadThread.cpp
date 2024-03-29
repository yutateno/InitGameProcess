#include "LoadThread.hpp"

using namespace std;
mutex mtx;



/// ---------------------------------------------------------------------------------------
void LoadThread::MyNextLoad(const std::string path, int& file, const ELOADFILE type)
{
	lock_guard<mutex> lock(mtx);

	LoadFile::MyLoad(path, file, type);
}



/// ---------------------------------------------------------------------------------------
LoadThread::LoadThread()
{
	num = 0;
	p_loadScreen = nullptr;
	p_loadScreen = new LoadScreen();
}



/// ---------------------------------------------------------------------------------------
LoadThread::~LoadThread()
{
	POINTER_RELEASE(p_loadScreen);
	fileName.clear();
	fileName.shrink_to_fit();
}



/// ---------------------------------------------------------------------------------------
void LoadThread::Process(const int max, const std::vector<std::string> path
	, const std::vector<ELOADFILE> type)
{
	if (num < max)
	{
		ClearDrawScreen();
		SetDrawScreen(DX_SCREEN_BACK);				// 背景描画
		p_loadScreen->Process(num, max);			// ロード画面
		ScreenFlip();
		fileName.push_back(-1);
		ths = thread(&LoadThread::MyNextLoad, this, path[num], ref(fileName[num]), type[num]);
		ths.join();
		num++;
		Process(max, path, type);					// 読み込み終わるまで再帰
	}
}



/// ---------------------------------------------------------------------------------------
void LoadThread::Draw()
{
	p_loadScreen->Process(num, num);			// ロード画面
}
