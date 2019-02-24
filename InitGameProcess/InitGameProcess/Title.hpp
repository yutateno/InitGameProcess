#pragma once
#include "BaseScene.hpp"



/*
ゲーム部分
*/
class Title : public BaseScene
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
	Title(const std::vector<int> v_file);

	// デストラクタ
	~Title();


	// 描画
	void Draw() override;

	// プロセス
	void Process() override;
};

