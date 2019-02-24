#pragma once
#include "BaseScene.hpp"
#include "LoadThread.hpp"

#include "Title.hpp"
#include "Game.hpp"


/*
�Q�[���̑�{
*/
class Manager
{
private:
	/// �e�V�[���Ɋւ���-----------------------------------------------------
	// �V�[���̊��N���X
	BaseScene* p_baseMove;

	// ���[�h�̃N���X
	LoadThread* p_loadThread;

	// �V�[����؂�ւ���
	void SceneChange();

	// ���O�̃V�[�������[�h���Q�[�����ǂ���
	bool preLoadScene;

	// ���[�h�̃t�@�C��
	std::vector<std::string> moveStr;

	// ���[�h�̎��
	std::vector<ELOADFILE> loadType;

	// �V�[���؂�ւ��̃t�F�[�h�J�E���g
	int feedCount;

	// �t�F�[�h�̐F
	int feedDraw;


	/// �Q�[���Ɋւ���-----------------------------------------------------------

	// �Q�[�����I������
	bool gameEnd;


	/// �^�C�g���Ɋւ���--------------------------------------------------------

	// �^�C�g���̃��[�h��
	const int max1 = 1;

	// �^�C�g���̃��[�h�̏�����
	void InitMove1Load();


	/// �Q�[���Ɋւ���--------------------------------------------------------

	// �Q�[���̃��[�h��
	const int max2 = 1;

	// �Q�[���̃��[�h�̏�����
	void InitMove2Load();


	/// �I�v�V������ʂɊւ���---------------------------------------------------

	// �I�v�V�����̉摜
	int gaussianScreen;

	// �I�v�V������ʂɂ��邩�ǂ���
	bool optionMenuNow;

	// �I�v�V������ʂ̃v���Z�X
	void OptionProcess();

	// �I�v�V������ʂ̕`��
	void OptionDraw();


public:
	// �R���X�g���N�^
	Manager();

	// �f�X�g���N�^
	~Manager();


	// ���C���v���Z�X
	void Update();

	// �Q�[�����I�����邩�ǂ���
	const bool GetEnd() const { return gameEnd; }
};
