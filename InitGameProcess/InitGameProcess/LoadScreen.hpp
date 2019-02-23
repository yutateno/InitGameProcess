#pragma once
#include "LoadFile.hpp"


/*
ロード中の画面のクラス
*/
class LoadScreen
{
private:
	// ロード画面
	int draw[1];

	// ロード画面の画像の動き
	int walkCount;

	// ロード終了
	int endDraw;


public:
	// コンストラクタ
	LoadScreen();

	// デストラクタ
	~LoadScreen();


	// 非同期で行うメソッド
	void Process(const int num, const int max);
};

