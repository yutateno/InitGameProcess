#pragma once

/*
大本
*/

/// インクルードファイル--------------------------------------------------------
#include "DLLXinput.h"
#include "EffekseerForDXLib.h"
#include "SoundProcess.hpp"
#include <vector>


/// 色んな所で使いそうなもの----------------------------------------------------

// シーンの動き
enum class ESceneNumber
{
	TITLELOAD, TITLE, GAMELOAD, GAME
};


namespace BASICPARAM
{
	// 直前のシーン
	extern ESceneNumber e_preScene;

	// 今のシーン
	extern ESceneNumber e_nowScene;


	// ウィンドウサイズ
	extern int winWidth;
	extern int winHeight;
	extern int bitColor;


	// 前シーンの終了フェードを終えたかどうか
	extern bool endFeedNow;

	// 次シーンの開始フェードを終えてないかどうか
	extern bool startFeedNow;

	// フェードの色
	extern int feedColor;
}


/// マクロ-------------------------------------------------------------------------------------

// ポインタ用解放マクロ
#define POINTER_RELEASE(p) { if(p!=nullptr) {delete p; (p)=nullptr; } }

// 2D関連画像解放マクロ
#define GRAPHIC_RELEASE(p) { if(p!=-1) { DeleteGraph(p); (p)=-1; } }

// 3D関連画像解放マクロ
#define MODEL_RELEASE(p) { if(p!=-1) { MV1DeleteModel(p); (p)=-1; } }

// 音解放マクロ
#define SOUND_RELEASE(p) { if(p!=-1) { StopSoundMem(p); DeleteSoundMem(p); (p)=-1; } }

// 光源ハンドル解放マクロ
#define LIGHT_RELEASE(p) { if(p!=-1) { DeleteLightHandle(p); (p)=-1; } }

// シャドウマップ解放マクロ
#define SHADOW_MAP_RELEASE(p) { if(p!=-1) { DeleteShadowMap(p); (p)=-1; } }



// debug
#ifdef _DEBUG
namespace MyDebug
{
	// static bool checkFlag;
	// static bool characterDrawFlag;

	void Init();

	void DebugProcess();
}
#endif // _DEBUG
