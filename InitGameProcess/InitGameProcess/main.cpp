#include "Manager.hpp"



/// --------------------------------------------------------------------------------------------------
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// ウィンドウサイズを決める
	BASICPARAM::winWidth = 1920;
	BASICPARAM::winHeight = 1080;
	BASICPARAM::bitColor = 32;


#ifdef _DEBUG
	SetOutApplicationLogValidFlag(TRUE);	// ログテキスト出力する
#elif NDEBUG
	SetOutApplicationLogValidFlag(FALSE);	// ログテキスト出力しない
#endif


	SetWindowText("InitGame");					// メインウインドウのウインドウタイトルを変更する
	BASICPARAM::feedColor = GetColor(0, 0, 0);
	SetBackgroundColor(0, 0, 0);			// 背景色を白に変更
	SetUseDirect3DVersion(DX_DIRECT3D_11);		// Direct3D11を使用する
	ChangeWindowMode(TRUE);						// ウィンドウズモードにさせる
	SetEnableXAudioFlag(TRUE);					// XAudioを使用するようにする
	SetUseLarge3DPositionSupport(TRUE);			// 巨大な座標値をサポート
	SetWindowIconID(333);


	SetGraphMode(BASICPARAM::winWidth, BASICPARAM::winHeight, BASICPARAM::bitColor);			// 画面サイズ設定
	GetDefaultState(&BASICPARAM::winWidth, &BASICPARAM::winHeight, &BASICPARAM::bitColor);		// デフォルトウィンドウ値を得る
	SetWindowSize(BASICPARAM::winWidth, BASICPARAM::winHeight);									// デフォルトウィンドウサイズに合わせてゲームサイズを変更


	// 画面サイズに戻す
	BASICPARAM::winWidth = 1920;
	BASICPARAM::winHeight = 1080;
	BASICPARAM::bitColor = 32;


	// ＤＸライブラリ初期化処理
	if (DxLib_Init() == -1)
	{
		return -1;			// エラーが起きたら直ちに終了
	}


	// Effekseerを初期化する。引数には画面に表示する最大パーティクル数を設定する。
	if (Effkseer_Init(500) == -1)
	{
		DxLib_End();
		return -1;
	}


	// フルスクリーンウインドウの切り替えでリソースが消えるのを防ぐ。
	SetChangeScreenModeGraphicsSystemResetFlag(FALSE);


	Effekseer_Set2DSetting(1920, 1080);	// 2Dエフェクトの最大範囲を設定


	SetAlwaysRunFlag(TRUE);			// 裏でもアクティブにする
	SetMouseDispFlag(FALSE);		// マウスカーソルを非表示にする

	SoundProcess::Init();			// サウンドプロセスの初期化

	DLLXinput::Init();				// DLLXinputの更新


	Manager* p_manager = new Manager();


	SetDrawScreen(DX_SCREEN_BACK);	// 背景描画


	// ゲームの核
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0 && !p_manager->GetEnd())
	{
		ClearDrawScreen();

		SoundProcess::Process();
		DLLXinput::AllControllerUpdate();

		p_manager->Update();

		ScreenFlip();
	} /// while


	delete p_manager;


	SoundProcess::Release();		// サウンド開放
	InitSoundMem();					// サウンド開放
	InitGraph();					// 画像解放
	MV1InitModel();					// モデル開放


	DLLXinput::Clean();	// DLLXinputの解放


	Effkseer_End();		// Effekseerを終了する。


	DxLib_End();		// DXライブラリの後始末


	return 0;
}