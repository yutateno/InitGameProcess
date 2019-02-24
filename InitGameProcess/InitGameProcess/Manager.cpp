#include "Manager.hpp"



/// --------------------------------------------------------------------------------------------------
void Manager::SceneChange()
{
	// ���̃V�[��
	switch (BASICPARAM::e_nowScene)
	{
		// �^�C�g���̃��[�h
	case ESceneNumber::TITLELOAD:
		BASICPARAM::startFeedNow = true;
		p_loadThread = new LoadThread();
		POINTER_RELEASE(p_baseMove);
		break;


		// �^�C�g��
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


		// �Q�[���̃��[�h
	case ESceneNumber::GAMELOAD:
		BASICPARAM::startFeedNow = true;
		p_loadThread = new LoadThread();
		POINTER_RELEASE(p_baseMove);
		break;


		// �Q�[��
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
		// �w�i�摜
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
		// �w�i�摜
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
	// �w�i
	DrawGraph(0, 0, gaussianScreen, false);
} /// void Manager::OptionDraw()



/// --------------------------------------------------------------------------------------------------
Manager::Manager()
{
	// ������
	BASICPARAM::e_preScene = ESceneNumber::TITLELOAD;
	BASICPARAM::e_nowScene = ESceneNumber::TITLELOAD;


	// �������̏�����
	p_baseMove = nullptr;
	p_loadThread = nullptr;
	moveStr.clear();
	loadType.clear();


	// �ŏ��̃��[�h�𐶐�
	p_loadThread = new LoadThread();
	preLoadScene = false;


	// �Q�[���Ɋւ���
	gameEnd = false;


	// ��ʂɊւ���
	LoadFile::MyLoad("media\\option.png", gaussianScreen, ELOADFILE::graph);


	// �I�v�V�����Ɋւ���
	optionMenuNow = false;


	// �t�F�[�h�����Ɋւ���
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
	// ���̃V�[���ƒ��O�̃V�[��������
	if (BASICPARAM::e_nowScene == BASICPARAM::e_preScene)
	{
		// �ŏ��̃��[�u�̃��[�h��������
		if (BASICPARAM::e_preScene == ESceneNumber::TITLELOAD)
		{
			if (!BASICPARAM::startFeedNow)
			{
				// �V�[���P�̑f�ރt�@�C��
				InitMove1Load();


				p_loadThread->Process(max1, moveStr, loadType);		// ���[�h������


				// ���[�h���I��������
				if (p_loadThread->GetNum() >= max1)
				{
					BASICPARAM::endFeedNow = true;						// �I���t�F�[�h�̃t���b�O�𗧂Ă�
					preLoadScene = true;								// ���O�����[�h�������Ƃ���
					BASICPARAM::e_nowScene = ESceneNumber::TITLE;	// ���̃V�[�����w�肷��
				}
			} /// if (!BASICPARAM::startFeedNow)
			// �J�n�t�F�[�h�������Ă�����
			else
			{
				// �Q�[���Ɋւ����A
				p_loadThread->Draw();


				// �t�F�[�h�J�E���g��������܂�������J�n�t�F�[�h�t���b�O������
				if (feedCount <= 0)
				{
					BASICPARAM::startFeedNow = false;
				}
				else
				{
					// �t�F�[�h�J�E���g��������
					feedCount -= 17;


					// �t�F�[�h�C������
					SetDrawBlendMode(DX_BLENDMODE_ALPHA, feedCount);
					DrawBox(0, 0, BASICPARAM::winWidth, BASICPARAM::winHeight, feedDraw, true);
					SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
				}
			} /// else(!if (!BASICPARAM::startFeedNow))
		}
		// ��Ԗڂ̃��[�u�̃��[�h��������
		else if (BASICPARAM::e_preScene == ESceneNumber::GAMELOAD)
		{
			if (!BASICPARAM::startFeedNow)
			{
				// �V�[���Q�̑f�ރt�@�C��
				InitMove2Load();


				p_loadThread->Process(max2, moveStr, loadType);		// ���[�h������


				// ���[�h���I��������
				if (p_loadThread->GetNum() >= max2)
				{
					BASICPARAM::endFeedNow = true;						// �I���t�F�[�h�̃t���b�O�𗧂Ă�
					preLoadScene = true;								// ���O�����[�h��������
					BASICPARAM::e_nowScene = ESceneNumber::GAME;	// ���̃V�[�����w�肷��
				}
			} /// if (!BASICPARAM::startFeedNow)
			// �J�n�t�F�[�h�������Ă�����
			else
			{
				// �Q�[���Ɋւ����A
				p_loadThread->Draw();


				// �t�F�[�h�J�E���g��������܂�������J�n�t�F�[�h�t���b�O������
				if (feedCount <= 0)
				{
					BASICPARAM::startFeedNow = false;
				}
				else
				{
					// �t�F�[�h�J�E���g��������
					feedCount -= 17;


					// �t�F�[�h�C������
					SetDrawBlendMode(DX_BLENDMODE_ALPHA, feedCount);
					DrawBox(0, 0, BASICPARAM::winWidth, BASICPARAM::winHeight, feedDraw, true);
					SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
				}
			} /// else(!if (!BASICPARAM::startFeedNow))
		}
		// ���[�h�ł͂Ȃ��Q�[����������
		else
		{
			preLoadScene = false;		// ���O�����[�h�ł͂Ȃ��Ƃ���


			// �I�v�V�������j���[�łȂ��Ƃ�
			if (!optionMenuNow)
			{
				// �J�n�t�F�[�h���I�����Ă�����
				if (!BASICPARAM::startFeedNow)
				{
					// �Q�[���Ɋւ���
					p_baseMove->Draw();


					// Effekseer�ɂ��Đ����̃G�t�F�N�g��`�悷��B
					DrawEffekseer3D();
					// Effekseer�ɂ��Đ����̃G�t�F�N�g��`�悷��B
					DrawEffekseer2D();


					BASICPARAM::e_nowScene = p_baseMove->GetScene();


					// �Q�[���Ɋւ���
					p_baseMove->Process();


					// Effekseer�ɂ��Đ����̃G�t�F�N�g���X�V����B
					UpdateEffekseer3D();
					// Effekseer�ɂ��Đ����̃G�t�F�N�g���X�V����B
					UpdateEffekseer2D();


					// �I�v�V������ʂɈڍs����R�}���h�������ꂽ��A�܂��̓E�B���h�E�Y����A�N�e�B�u�ɂȂ�����
					if (DLLXinput::GetPadButtonData(DLLXinput::XINPUT_PAD::NUM01, DLLXinput::XINPUT_PAD::BUTTON_START) == 1
						|| !GetWindowActiveFlag() || CheckHitKey(KEY_INPUT_SPACE) == 1)
					{
						optionMenuNow = true;											// �I�v�V�������j���[�Ɉڍs����t���b�O�𗧂Ă�


						SoundProcess::SetOptionMenuNow(true);							// �T�E���h���ʂ��I�v�V�������j���[�p�ɉ�����悤����
					}
#ifdef _DEBUG
					MyDebug::DebugProcess();
#endif // _DEBUG
				} /// if (!BASICPARAM::startFeedNow)
				// �J�n�t�F�[�h�������Ă�����
				else
				{
					// �Q�[���Ɋւ����A
					p_baseMove->Draw();


					// �t�F�[�h�J�E���g��������܂�������J�n�t�F�[�h�t���b�O������
					if (feedCount <= 0)
					{
						BASICPARAM::startFeedNow = false;
					}
					else
					{
						// �t�F�[�h�J�E���g��������
						feedCount -= 5;


						// �t�F�[�h�C������
						SetDrawBlendMode(DX_BLENDMODE_ALPHA, feedCount);
						DrawBox(0, 0, BASICPARAM::winWidth, BASICPARAM::winHeight, feedDraw, true);
						SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
					}
				} /// else(!if (!BASICPARAM::startFeedNow))
			} /// if (!optionMenuNow)
			// �I�v�V�������j���[�̂Ƃ�
			else
			{
				// �I�v�V�����Ɋւ���
				OptionDraw();
				OptionProcess();


				// �I�v�V������ʂ���߂�
				if (DLLXinput::GetPadButtonData(DLLXinput::XINPUT_PAD::NUM01, DLLXinput::XINPUT_PAD::BUTTON_START) == 1
					|| CheckHitKey(KEY_INPUT_SPACE) == 1)
				{
					SoundProcess::SetOptionMenuNow(false);		// �T�E���h���ʂ��I�v�V�����p����߂�
					optionMenuNow = false;
				}
			} /// else(!if (!optionMenuNow))
		} /// else
	} /// if (BASICPARAM::e_nowScene == BASICPARAM::e_preScene)	
	// �V�[�����ڍs����悤�Ɏw�肳�ꂽ��
	else
	{
		// ���݂̃V�[���̏I���t�F�[�h���I�������
		if (!BASICPARAM::endFeedNow)
		{
			// �V�[����ς���
			SceneChange();


			// ���O�̃V�[���ƍ��̃V�[���𓯂��ɂ���
			BASICPARAM::e_preScene = BASICPARAM::e_nowScene;
		} /// if (!BASICPARAM::endFeedNow)
		// ���݂̃V�[���̏I���t�F�[�h�̂Ƃ�
		else
		{
			// �I���V�[�������[�h�ł͂Ȃ��Ƃ�
			if (!preLoadScene)
			{
				// �t�F�[�h�J�E���g�����ɒB������t���b�O������
				if (feedCount >= 255)
				{
					// �G�t�F�N�g���I������
					DrawEffekseer2D_End();
					DrawEffekseer3D_End();


					// �T�E���h���������
					SoundProcess::Release();
					BASICPARAM::endFeedNow = false;
				}
				else
				{
					// �t�F�[�h�����Z����
					feedCount += 5;


					// �Q�[���̕`��Ɋւ���̂������c���ăQ�[���Ɋւ������
					p_baseMove->Draw();
				}


				// �t�F�[�h�A�E�g����
				SetDrawBlendMode(DX_BLENDMODE_ALPHA, feedCount);
				DrawBox(0, 0, BASICPARAM::winWidth, BASICPARAM::winHeight, feedDraw, true);
				SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
			} /// if (!preLoadScene)
			// �I���V�[�������[�h�̂Ƃ�
			else
			{
				// �t�F�[�h�J�E���g�����ɒB������t���b�O������
				if (feedCount >= 255)
				{
					BASICPARAM::endFeedNow = false;
				}
				else
				{
					// �t�F�[�h�����Z����
					feedCount += 15;


					// �Q�[���̕`��Ɋւ���̂������c���ăQ�[���Ɋւ������
					p_loadThread->Draw();
				}


				// �t�F�[�h�A�E�g����
				SetDrawBlendMode(DX_BLENDMODE_ALPHA, feedCount);
				DrawBox(0, 0, BASICPARAM::winWidth, BASICPARAM::winHeight, feedDraw, true);
				SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
			} /// else(!if (!preLoadScene))
		} /// else(!if (!BASICPARAM::endFeedNow))
	} /// else(!if (BASICPARAM::e_nowScene == BASICPARAM::e_preScene))
} /// void Manager::Update()