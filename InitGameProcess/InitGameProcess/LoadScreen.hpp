#pragma once
#include "LoadFile.hpp"


/*
���[�h���̉�ʂ̃N���X
*/
class LoadScreen
{
private:
	// ���[�h���
	int draw[1];

	// ���[�h��ʂ̉摜�̓���
	int walkCount;

	// ���[�h�I��
	int endDraw;


public:
	// �R���X�g���N�^
	LoadScreen();

	// �f�X�g���N�^
	~LoadScreen();


	// �񓯊��ōs�����\�b�h
	void Process(const int num, const int max);
};
