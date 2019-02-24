#pragma once
#include "BaseScene.hpp"



/*
ゲーム部分
*/
class Game : public BaseScene
{
private:
	// ロードから渡されるファイルの順番
	enum class EFILE {
		backGroundDraw
	};


	// 背景画像
	int backGroundDraw;



public:
	// コンストラクタ
	Game(const std::vector<int> v_file);

	// デストラクタ
	~Game();


	// 描画
	void Draw() override;

	// プロセス
	void Process() override;
};

