#pragma once
#include "Basic.hpp"
#include "LoadFile.hpp"


/*
���[�u�̑�{
*/
class BaseScene
{
protected:
	// �V�[���̏I���t���b�O
	static bool endFlag;

	// ���݂̃V�[��
	static ESceneNumber scene;


	/// �A�N�^�[���ƂɊւ���----------------------------------------------

	// ��̃��f���̋���
	template<class T>
	T GetDistance(const VECTOR alpha, const VECTOR beta)
	{
		return static_cast<T>(sqrt((alpha.x - beta.x) * (alpha.x - beta.x) + (alpha.z - beta.z) * (alpha.z - beta.z)));
	}


public:
	// �R���X�g���N�^
	BaseScene();

	// �f�X�g���N�^
	virtual ~BaseScene();

	// �`��
	virtual void Draw() = 0;

	// �v���Z�X
	virtual void Process() = 0;


	/// �Q�b�^�[�Z�b�^�[-------------------------------------------------

	// �I�����ǂ�����n��
	static const bool GetEndFlag() { return endFlag; }

	// ���̃V�[����n��
	static const ESceneNumber GetScene() { return scene; }

	// ���̃V�[���𓾂�
	void SetScene(const ESceneNumber scene) { this->scene = scene; }
};

