#pragma once
#include "BaseScene.hpp"
#include "LoadThread.hpp"

#include "Title.hpp"
#include "Game.hpp"


/*
ゲームの大本
*/
class Manager
{
private:
	/// 各シーンに関する-----------------------------------------------------
	// シーンの基底クラス
	BaseScene* p_baseMove;

	// ロードのクラス
	LoadThread* p_loadThread;

	// シーンを切り替える
	void SceneChange();

	// 直前のシーンがロードかゲームかどうか
	bool preLoadScene;

	// ロードのファイル
	std::vector<std::string> moveStr;

	// ロードの種類
	std::vector<ELOADFILE> loadType;

	// シーン切り替えのフェードカウント
	int feedCount;

	// フェードの色
	int feedDraw;


	/// ゲームに関する-----------------------------------------------------------

	// ゲームを終了する
	bool gameEnd;


	/// タイトルに関する--------------------------------------------------------

	// タイトルのロード数
	const int max1 = 1;

	// タイトルのロードの初期化
	void InitMove1Load();


	/// ゲームに関する--------------------------------------------------------

	// ゲームのロード数
	const int max2 = 1;

	// ゲームのロードの初期化
	void InitMove2Load();


	/// オプション画面に関する---------------------------------------------------

	// オプションの画像
	int gaussianScreen;

	// オプション画面にいるかどうか
	bool optionMenuNow;

	// オプション画面のプロセス
	void OptionProcess();

	// オプション画面の描画
	void OptionDraw();


public:
	// コンストラクタ
	Manager();

	// デストラクタ
	~Manager();


	// メインプロセス
	void Update();

	// ゲームを終了するかどうか
	const bool GetEnd() const { return gameEnd; }
};
