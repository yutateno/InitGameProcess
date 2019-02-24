#pragma once

/*
��{
*/

/// �C���N���[�h�t�@�C��--------------------------------------------------------
#include "DLLXinput.h"
#include "EffekseerForDXLib.h"
#include "SoundProcess.hpp"
#include <vector>


/// �F��ȏ��Ŏg�������Ȃ���----------------------------------------------------

// �V�[���̓���
enum class ESceneNumber
{
	TITLELOAD, TITLE, GAMELOAD, GAME
};


namespace BASICPARAM
{
	// ���O�̃V�[��
	extern ESceneNumber e_preScene;

	// ���̃V�[��
	extern ESceneNumber e_nowScene;


	// �E�B���h�E�T�C�Y
	extern int winWidth;
	extern int winHeight;
	extern int bitColor;


	// �O�V�[���̏I���t�F�[�h���I�������ǂ���
	extern bool endFeedNow;

	// ���V�[���̊J�n�t�F�[�h���I���ĂȂ����ǂ���
	extern bool startFeedNow;

	// �t�F�[�h�̐F
	extern int feedColor;
}


/// �}�N��-------------------------------------------------------------------------------------

// �|�C���^�p����}�N��
#define POINTER_RELEASE(p) { if(p!=nullptr) {delete p; (p)=nullptr; } }

// 2D�֘A�摜����}�N��
#define GRAPHIC_RELEASE(p) { if(p!=-1) { DeleteGraph(p); (p)=-1; } }

// 3D�֘A�摜����}�N��
#define MODEL_RELEASE(p) { if(p!=-1) { MV1DeleteModel(p); (p)=-1; } }

// ������}�N��
#define SOUND_RELEASE(p) { if(p!=-1) { StopSoundMem(p); DeleteSoundMem(p); (p)=-1; } }

// �����n���h������}�N��
#define LIGHT_RELEASE(p) { if(p!=-1) { DeleteLightHandle(p); (p)=-1; } }

// �V���h�E�}�b�v����}�N��
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
