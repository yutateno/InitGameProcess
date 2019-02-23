#pragma once
#include "LoadScreen.hpp"


/*
�񓯊��Ń��[�h���s���N���X
*/
class LoadThread
{
private:
	// �񓯊����s��
	std::thread ths;

	// ���[�h������
	int num;

	// �ő働�[�h��
	int maxNum;

	// ���[�h��������
	std::vector<int> fileName;

	// ���[�h��ʂ̃|�C���^
	LoadScreen* p_loadScreen;

	// �f�b�h���b�N��}�����Ȃ���񓯊����s�����\�b�h
	void MyNextLoad(const std::string path, int& file, const ELOADFILE type);


public:
	// �R���X�g���N�^
	LoadThread();

	// �f�X�g���N�^
	~LoadThread();


	// �v���Z�X
	void Process(const int max, const std::vector<std::string> path
		, const std::vector<ELOADFILE> type);

	// �`��
	void Draw();


	/// �Q�b�^�[�Z�b�^�[------------------------------------------------

	// ���[�h�������̂�n��
	const std::vector<int> GetFile() const { return fileName; }

	// ���[�h���I������
	const int GetNum() const { return num; };
};