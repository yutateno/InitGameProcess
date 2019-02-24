#pragma once
#include "LoadFile.hpp"


/*
ロード中の画面のクラス
*/
class LoadScreen
{
private:
	// ロード画面
	int draw;

	// ロード画面の画像の動き
	int walkCount;


public:
	// コンストラクタ
	LoadScreen();

	// デストラクタ
	~LoadScreen();


	// 非同期で行うメソッド
	void Process(const int num, const int max);
};

