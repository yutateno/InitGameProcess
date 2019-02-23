#include "DLLXinput.h"
#include "EffekseerForDXLib.h"
#include "SoundProcess.hpp"



/// --------------------------------------------------------------------------------------------------
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// �E�B���h�E�T�C�Y�����߂�
	int winWidth = 1920;
	int winHeight = 1080;
	int bitColor = 32;


#ifdef _DEBUG
	SetOutApplicationLogValidFlag(TRUE);	// ���O�e�L�X�g�o�͂���
#elif NDEBUG
	SetOutApplicationLogValidFlag(FALSE);	// ���O�e�L�X�g�o�͂��Ȃ�
#endif


	SetWindowText("Re.Gleam");					// ���C���E�C���h�E�̃E�C���h�E�^�C�g����ύX����
	SetBackgroundColor(255, 255, 255);			// �w�i�F�𔒂ɕύX
	SetUseDirect3DVersion(DX_DIRECT3D_11);		// Direct3D11���g�p����
	ChangeWindowMode(TRUE);						// �E�B���h�E�Y���[�h�ɂ�����
	SetEnableXAudioFlag(TRUE);					// XAudio���g�p����悤�ɂ���
	SetUseLarge3DPositionSupport(TRUE);			// ����ȍ��W�l���T�|�[�g
	SetWindowIconID(333);


	SetGraphMode(winWidth, winHeight, bitColor);			// ��ʃT�C�Y�ݒ�
	GetDefaultState(&winWidth, &winHeight, &bitColor);		// �f�t�H���g�E�B���h�E�l�𓾂�
	SetWindowSize(winWidth, winHeight);									// �f�t�H���g�E�B���h�E�T�C�Y�ɍ��킹�ăQ�[���T�C�Y��ύX


	// ��ʃT�C�Y�ɖ߂�
	winWidth = 1920;
	winHeight = 1080;
	bitColor = 32;


	// �c�w���C�u��������������
	if (DxLib_Init() == -1)
	{
		return -1;			// �G���[���N�����璼���ɏI��
	}


	// Effekseer������������B�����ɂ͉�ʂɕ\������ő�p�[�e�B�N������ݒ肷��B
	if (Effkseer_Init(500) == -1)
	{
		DxLib_End();
		return -1;
	}


	// �t���X�N���[���E�C���h�E�̐؂�ւ��Ń��\�[�X��������̂�h���B
	SetChangeScreenModeGraphicsSystemResetFlag(FALSE);


	Effekseer_Set2DSetting(1920, 1080);	// 2D�G�t�F�N�g�̍ő�͈͂�ݒ�


	SetAlwaysRunFlag(TRUE);			// ���ł��A�N�e�B�u�ɂ���
	SetDrawScreen(DX_SCREEN_BACK);	// �w�i�`��
	SetMouseDispFlag(FALSE);		// �}�E�X�J�[�\�����\���ɂ���


	SoundProcess::Init();			// �T�E���h�v���Z�X�̏�����

	DLLXinput::Init();				// DLLXinput�̍X�V
	DLLXinput::FirstUpdate();		// DLLXinput�̏����X�V


	// �Q�[���̊j
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		ClearDrawScreen();

		SoundProcess::Process();
		DLLXinput::EverUpdate();

		printfDx("%d\n", DLLXinput::GetPadButtonData(DLLXinput::XINPUT_PAD::NUM01, DLLXinput::XINPUT_PAD::BUTTON_A));

		ScreenFlip();
	} /// while


	SoundProcess::Release();		// �T�E���h�J��
	InitSoundMem();					// �T�E���h�J��
	InitGraph();					// �摜���
	MV1InitModel();					// ���f���J��


	Effkseer_End();		// Effekseer���I������B


	DLLXinput::Clean();	// DLLXinput�̉��


	DxLib_End();		// DX���C�u�����̌�n��


	return 0;
}