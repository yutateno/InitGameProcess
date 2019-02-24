#pragma once
#include "Basic.hpp"
#include "LoadFile.hpp"


/*
ムーブの大本
*/
class BaseScene
{
protected:
	// シーンの終了フラッグ
	static bool endFlag;

	// 現在のシーン
	static ESceneNumber scene;


	/// アクターごとに関して----------------------------------------------

	// 二つのモデルの距離
	template<class T>
	T GetDistance(const VECTOR alpha, const VECTOR beta)
	{
		return static_cast<T>(sqrt((alpha.x - beta.x) * (alpha.x - beta.x) + (alpha.z - beta.z) * (alpha.z - beta.z)));
	}


public:
	// コンストラクタ
	BaseScene();

	// デストラクタ
	virtual ~BaseScene();

	// 描画
	virtual void Draw() = 0;

	// プロセス
	virtual void Process() = 0;


	/// ゲッターセッター-------------------------------------------------

	// 終了かどうかを渡す
	static const bool GetEndFlag() { return endFlag; }

	// 今のシーンを渡す
	static const ESceneNumber GetScene() { return scene; }

	// 今のシーンを得る
	void SetScene(const ESceneNumber scene) { this->scene = scene; }
};

