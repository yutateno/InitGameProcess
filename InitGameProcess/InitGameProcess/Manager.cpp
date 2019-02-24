#include "Manager.hpp"



/// --------------------------------------------------------------------------------------------------
void Manager::SceneChange()
{
	// 今のシーン
	switch (BASICPARAM::e_nowScene)
	{
		// タイトルのロード
	case ESceneNumber::TITLELOAD:
		BASICPARAM::startFeedNow = true;
		p_loadThread = new LoadThread();
		POINTER_RELEASE(p_baseMove);
		break;


		// タイトル
	case ESceneNumber::TITLE:
		BASICPARAM::startFeedNow = true;
		p_baseMove = new Title(p_loadThread->GetFile());
		p_baseMove->SetScene(BASICPARAM::e_nowScene);
		POINTER_RELEASE(p_loadThread);
		moveStr.clear();
		moveStr.shrink_to_fit();
		loadType.clear();
		loadType.shrink_to_fit();
		break;


		// ゲームのロード
	case ESceneNumber::GAMELOAD:
		BASICPARAM::startFeedNow = true;
		p_loadThread = new LoadThread();
		POINTER_RELEASE(p_baseMove);
		break;


		// ゲーム
	case ESceneNumber::GAME:
		BASICPARAM::startFeedNow = true;
		p_baseMove = new Game(p_loadThread->GetFile());
		p_baseMove->SetScene(BASICPARAM::e_nowScene);
		POINTER_RELEASE(p_loadThread);
		moveStr.clear();
		moveStr.shrink_to_fit();
		loadType.clear();
		loadType.shrink_to_fit();
		break;


	default:
		break;
	} /// switch (BASICPARAM::e_nowScene)
} /// void Manager::SceneChange()



/// --------------------------------------------------------------------------------------------------
void Manager::InitMove1Load()
{
	moveStr.resize(max1 + 1);
	{
		// 背景画像
		moveStr[0] = "media\\title_back.png";
	}


	loadType.resize(max1 + 1);
	{
		loadType[0] = ELOADFILE::graph;
	}
} /// void Manager::InitMove1Load()



/// --------------------------------------------------------------------------------------------------
void Manager::InitMove2Load()
{
	moveStr.resize(max2 + 1);
	{
		// 背景画像
		moveStr[0] = "media\\game.png";
	}


	loadType.resize(max2 + 1);
	{
		loadType[0] = ELOADFILE::graph;
	}
} /// void Manager::InitMove2Load()



/// --------------------------------------------------------------------------------------------------
void Manager::OptionProcess()
{
	
} /// void Manager::OptionProcess()



/// --------------------------------------------------------------------------------------------------
void Manager::OptionDraw()
{
	// 背景
	DrawGraph(0, 0, gaussianScreen, false);
} /// void Manager::OptionDraw()



/// --------------------------------------------------------------------------------------------------
Manager::Manager()
{
	// 初期化
	BASICPARAM::e_preScene = ESceneNumber::TITLELOAD;
	BASICPARAM::e_nowScene = ESceneNumber::TITLELOAD;


	// メモリの初期化
	p_baseMove = nullptr;
	p_loadThread = nullptr;
	moveStr.clear();
	loadType.clear();


	// 最初のロードを生成
	p_loadThread = new LoadThread();
	preLoadScene = false;


	// ゲームに関する
	gameEnd = false;


	// 画面に関する
	LoadFile::MyLoad("media\\option.png", gaussianScreen, ELOADFILE::graph);


	// オプションに関する
	optionMenuNow = false;


	// フェード処理に関する
	feedCount = 0;
	BASICPARAM::endFeedNow = false;
	BASICPARAM::startFeedNow = true;
	feedDraw = BASICPARAM::feedColor;
} /// Manager::Manager()



/// --------------------------------------------------------------------------------------------------
Manager::~Manager()
{
	GRAPHIC_RELEASE(gaussianScreen);


	POINTER_RELEASE(p_baseMove);
	POINTER_RELEASE(p_loadThread);
}



/// --------------------------------------------------------------------------------------------------
void Manager::Update()
{
	// 今のシーンと直前のシーンが同じ
	if (BASICPARAM::e_nowScene == BASICPARAM::e_preScene)
	{
		// 最初のムーブのロードだったら
		if (BASICPARAM::e_preScene == ESceneNumber::TITLELOAD)
		{
			if (!BASICPARAM::startFeedNow)
			{
				// シーン１の素材ファイル
				InitMove1Load();


				p_loadThread->Process(max1, moveStr, loadType);		// ロードをする


				// ロードが終了したら
				if (p_loadThread->GetNum() >= max1)
				{
					BASICPARAM::endFeedNow = true;						// 終了フェードのフラッグを立てる
					preLoadScene = true;								// 直前がロードだったとする
					BASICPARAM::e_nowScene = ESceneNumber::TITLE;	// 次のシーンを指定する
				}
			} /// if (!BASICPARAM::startFeedNow)
			// 開始フェードが立っていたら
			else
			{
				// ゲームに関する一連
				p_loadThread->Draw();


				// フェードカウントが下がりまくったら開始フェードフラッグを下す
				if (feedCount <= 0)
				{
					BASICPARAM::startFeedNow = false;
				}
				else
				{
					// フェードカウントを下げる
					feedCount -= 17;


					// フェードイン処理
					SetDrawBlendMode(DX_BLENDMODE_ALPHA, feedCount);
					DrawBox(0, 0, BASICPARAM::winWidth, BASICPARAM::winHeight, feedDraw, true);
					SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
				}
			} /// else(!if (!BASICPARAM::startFeedNow))
		}
		// 二番目のムーブのロードだったら
		else if (BASICPARAM::e_preScene == ESceneNumber::GAMELOAD)
		{
			if (!BASICPARAM::startFeedNow)
			{
				// シーン２の素材ファイル
				InitMove2Load();


				p_loadThread->Process(max2, moveStr, loadType);		// ロードをする


				// ロードが終了したら
				if (p_loadThread->GetNum() >= max2)
				{
					BASICPARAM::endFeedNow = true;						// 終了フェードのフラッグを立てる
					preLoadScene = true;								// 直前がロードだったら
					BASICPARAM::e_nowScene = ESceneNumber::GAME;	// 次のシーンを指定する
				}
			} /// if (!BASICPARAM::startFeedNow)
			// 開始フェードが立っていたら
			else
			{
				// ゲームに関する一連
				p_loadThread->Draw();


				// フェードカウントが下がりまくったら開始フェードフラッグを下す
				if (feedCount <= 0)
				{
					BASICPARAM::startFeedNow = false;
				}
				else
				{
					// フェードカウントを下げる
					feedCount -= 17;


					// フェードイン処理
					SetDrawBlendMode(DX_BLENDMODE_ALPHA, feedCount);
					DrawBox(0, 0, BASICPARAM::winWidth, BASICPARAM::winHeight, feedDraw, true);
					SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
				}
			} /// else(!if (!BASICPARAM::startFeedNow))
		}
		// ロードではなくゲームだったら
		else
		{
			preLoadScene = false;		// 直前がロードではないとする


			// オプションメニューでないとき
			if (!optionMenuNow)
			{
				// 開始フェードが終了していたら
				if (!BASICPARAM::startFeedNow)
				{
					// ゲームに関する
					p_baseMove->Draw();


					// Effekseerにより再生中のエフェクトを描画する。
					DrawEffekseer3D();
					// Effekseerにより再生中のエフェクトを描画する。
					DrawEffekseer2D();


					BASICPARAM::e_nowScene = p_baseMove->GetScene();


					// ゲームに関する
					p_baseMove->Process();


					// Effekseerにより再生中のエフェクトを更新する。
					UpdateEffekseer3D();
					// Effekseerにより再生中のエフェクトを更新する。
					UpdateEffekseer2D();


					// オプション画面に移行するコマンドを押されたら、またはウィンドウズが非アクティブになったら
					if (DLLXinput::GetPadButtonData(DLLXinput::XINPUT_PAD::NUM01, DLLXinput::XINPUT_PAD::BUTTON_START) == 1
						|| !GetWindowActiveFlag() || CheckHitKey(KEY_INPUT_SPACE) == 1)
					{
						optionMenuNow = true;											// オプションメニューに移行するフラッグを立てる


						SoundProcess::SetOptionMenuNow(true);							// サウンド音量をオプションメニュー用に下げるよう命令
					}
#ifdef _DEBUG
					MyDebug::DebugProcess();
#endif // _DEBUG
				} /// if (!BASICPARAM::startFeedNow)
				// 開始フェードが立っていたら
				else
				{
					// ゲームに関する一連
					p_baseMove->Draw();


					// フェードカウントが下がりまくったら開始フェードフラッグを下す
					if (feedCount <= 0)
					{
						BASICPARAM::startFeedNow = false;
					}
					else
					{
						// フェードカウントを下げる
						feedCount -= 5;


						// フェードイン処理
						SetDrawBlendMode(DX_BLENDMODE_ALPHA, feedCount);
						DrawBox(0, 0, BASICPARAM::winWidth, BASICPARAM::winHeight, feedDraw, true);
						SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
					}
				} /// else(!if (!BASICPARAM::startFeedNow))
			} /// if (!optionMenuNow)
			// オプションメニューのとき
			else
			{
				// オプションに関する
				OptionDraw();
				OptionProcess();


				// オプション画面から戻る
				if (DLLXinput::GetPadButtonData(DLLXinput::XINPUT_PAD::NUM01, DLLXinput::XINPUT_PAD::BUTTON_START) == 1
					|| CheckHitKey(KEY_INPUT_SPACE) == 1)
				{
					SoundProcess::SetOptionMenuNow(false);		// サウンド音量をオプション用から戻す
					optionMenuNow = false;
				}
			} /// else(!if (!optionMenuNow))
		} /// else
	} /// if (BASICPARAM::e_nowScene == BASICPARAM::e_preScene)	
	// シーンを移行するように指定されたら
	else
	{
		// 現在のシーンの終了フェードが終わったら
		if (!BASICPARAM::endFeedNow)
		{
			// シーンを変える
			SceneChange();


			// 直前のシーンと今のシーンを同じにする
			BASICPARAM::e_preScene = BASICPARAM::e_nowScene;
		} /// if (!BASICPARAM::endFeedNow)
		// 現在のシーンの終了フェードのとき
		else
		{
			// 終了シーンがロードではないとき
			if (!preLoadScene)
			{
				// フェードカウントが一定に達したらフラッグを下す
				if (feedCount >= 255)
				{
					// エフェクトを終了する
					DrawEffekseer2D_End();
					DrawEffekseer3D_End();


					// サウンドを解放する
					SoundProcess::Release();
					BASICPARAM::endFeedNow = false;
				}
				else
				{
					// フェードを加算する
					feedCount += 5;


					// ゲームの描画に関するのだけを残してゲームに関するもの
					p_baseMove->Draw();
				}


				// フェードアウト処理
				SetDrawBlendMode(DX_BLENDMODE_ALPHA, feedCount);
				DrawBox(0, 0, BASICPARAM::winWidth, BASICPARAM::winHeight, feedDraw, true);
				SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
			} /// if (!preLoadScene)
			// 終了シーンがロードのとき
			else
			{
				// フェードカウントが一定に達したらフラッグを下す
				if (feedCount >= 255)
				{
					BASICPARAM::endFeedNow = false;
				}
				else
				{
					// フェードを加算する
					feedCount += 15;


					// ゲームの描画に関するのだけを残してゲームに関するもの
					p_loadThread->Draw();
				}


				// フェードアウト処理
				SetDrawBlendMode(DX_BLENDMODE_ALPHA, feedCount);
				DrawBox(0, 0, BASICPARAM::winWidth, BASICPARAM::winHeight, feedDraw, true);
				SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
			} /// else(!if (!preLoadScene))
		} /// else(!if (!BASICPARAM::endFeedNow))
	} /// else(!if (BASICPARAM::e_nowScene == BASICPARAM::e_preScene))
} /// void Manager::Update()