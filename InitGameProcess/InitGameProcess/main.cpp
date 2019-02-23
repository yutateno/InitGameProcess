#include "DLLXinput.h"
#include "EffekseerForDXLib.h"
#include "SoundProcess.hpp"



/// --------------------------------------------------------------------------------------------------
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// ウィンドウサイズを決める
	int winWidth = 1920;
	int winHeight = 1080;
	int bitColor = 32;


#ifdef _DEBUG
	SetOutApplicationLogValidFlag(TRUE);	// ログテキスト出力する
#elif NDEBUG
	SetOutApplicationLogValidFlag(FALSE);	// ログテキスト出力しない
#endif


	SetWindowText("Re.Gleam");					// メインウインドウのウインドウタイトルを変更する
	SetBackgroundColor(255, 255, 255);			// 背景色を白に変更
	SetUseDirect3DVersion(DX_DIRECT3D_11);		// Direct3D11を使用する
	ChangeWindowMode(TRUE);						// ウィンドウズモードにさせる
	SetEnableXAudioFlag(TRUE);					// XAudioを使用するようにする
	SetUseLarge3DPositionSupport(TRUE);			// 巨大な座標値をサポート
	SetWindowIconID(333);


	SetGraphMode(winWidth, winHeight, bitColor);			// 画面サイズ設定
	GetDefaultState(&winWidth, &winHeight, &bitColor);		// デフォルトウィンドウ値を得る
	SetWindowSize(winWidth, winHeight);									// デフォルトウィンドウサイズに合わせてゲームサイズを変更


	// 画面サイズに戻す
	winWidth = 1920;
	winHeight = 1080;
	bitColor = 32;


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
	SetDrawScreen(DX_SCREEN_BACK);	// 背景描画
	SetMouseDispFlag(FALSE);		// マウスカーソルを非表示にする


	SoundProcess::Init();			// サウンドプロセスの初期化

	DLLXinput::Init();				// DLLXinputの更新
	DLLXinput::FirstUpdate();		// DLLXinputの初期更新


	// ゲームの核
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		ClearDrawScreen();

		SoundProcess::Process();
		DLLXinput::EverUpdate();

		printfDx("%d\n", DLLXinput::GetPadButtonData(DLLXinput::XINPUT_PAD::NUM01, DLLXinput::XINPUT_PAD::BUTTON_A));

		ScreenFlip();
	} /// while


	SoundProcess::Release();		// サウンド開放
	InitSoundMem();					// サウンド開放
	InitGraph();					// 画像解放
	MV1InitModel();					// モデル開放


	Effkseer_End();		// Effekseerを終了する。


	DLLXinput::Clean();	// DLLXinputの解放


	DxLib_End();		// DXライブラリの後始末


	return 0;
}