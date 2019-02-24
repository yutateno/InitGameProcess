#include "Manager.hpp"



/// --------------------------------------------------------------------------------------------------
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// �E�B���h�E�T�C�Y�����߂�
	BASICPARAM::winWidth = 1920;
	BASICPARAM::winHeight = 1080;
	BASICPARAM::bitColor = 32;


#ifdef _DEBUG
	SetOutApplicationLogValidFlag(TRUE);	// ���O�e�L�X�g�o�͂���
#elif NDEBUG
	SetOutApplicationLogValidFlag(FALSE);	// ���O�e�L�X�g�o�͂��Ȃ�
#endif


	SetWindowText("InitGame");					// ���C���E�C���h�E�̃E�C���h�E�^�C�g����ύX����
	BASICPARAM::feedColor = GetColor(0, 0, 0);
	SetBackgroundColor(0, 0, 0);			// �w�i�F�𔒂ɕύX
	SetUseDirect3DVersion(DX_DIRECT3D_11);		// Direct3D11���g�p����
	ChangeWindowMode(TRUE);						// �E�B���h�E�Y���[�h�ɂ�����
	SetEnableXAudioFlag(TRUE);					// XAudio���g�p����悤�ɂ���
	SetUseLarge3DPositionSupport(TRUE);			// ����ȍ��W�l���T�|�[�g
	SetWindowIconID(333);


	SetGraphMode(BASICPARAM::winWidth, BASICPARAM::winHeight, BASICPARAM::bitColor);			// ��ʃT�C�Y�ݒ�
	GetDefaultState(&BASICPARAM::winWidth, &BASICPARAM::winHeight, &BASICPARAM::bitColor);		// �f�t�H���g�E�B���h�E�l�𓾂�
	SetWindowSize(BASICPARAM::winWidth, BASICPARAM::winHeight);									// �f�t�H���g�E�B���h�E�T�C�Y�ɍ��킹�ăQ�[���T�C�Y��ύX


	// ��ʃT�C�Y�ɖ߂�
	BASICPARAM::winWidth = 1920;
	BASICPARAM::winHeight = 1080;
	BASICPARAM::bitColor = 32;


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
	SetMouseDispFlag(FALSE);		// �}�E�X�J�[�\�����\���ɂ���

	SoundProcess::Init();			// �T�E���h�v���Z�X�̏�����

	DLLXinput::Init();				// DLLXinput�̍X�V


	Manager* p_manager = new Manager();


	SetDrawScreen(DX_SCREEN_BACK);	// �w�i�`��


	// �Q�[���̊j
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0 && !p_manager->GetEnd())
	{
		ClearDrawScreen();

		SoundProcess::Process();
		DLLXinput::AllControllerUpdate();

		p_manager->Update();

		ScreenFlip();
	} /// while


	delete p_manager;


	SoundProcess::Release();		// �T�E���h�J��
	InitSoundMem();					// �T�E���h�J��
	InitGraph();					// �摜���
	MV1InitModel();					// ���f���J��


	DLLXinput::Clean();	// DLLXinput�̉��


	Effkseer_End();		// Effekseer���I������B


	DxLib_End();		// DX���C�u�����̌�n��


	return 0;
}