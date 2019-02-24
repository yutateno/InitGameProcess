#pragma once
#include "BaseScene.hpp"



/*
�Q�[������
*/
class Game : public BaseScene
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
	Game(const std::vector<int> v_file);

	// �f�X�g���N�^
	~Game();


	// �`��
	void Draw() override;

	// �v���Z�X
	void Process() override;
};

