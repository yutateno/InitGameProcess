#pragma once
#include "BaseScene.hpp"



/*
�Q�[������
*/
class Title : public BaseScene
{
private:
	// ���[�h����n�����t�@�C���̏���
	enum class EFILE {
		backGroundDraw
	};


	// �w�i�摜
	int backGroundDraw;



public:
	// �R���X�g���N�^
	Title(const std::vector<int> v_file);

	// �f�X�g���N�^
	~Title();


	// �`��
	void Draw() override;

	// �v���Z�X
	void Process() override;
};

