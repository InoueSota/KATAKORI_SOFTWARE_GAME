#pragma once
#include "Screen.h"
#include "Vec2.h"

class Player
{
public:

	Player() {
		Init();
	}

	void Init();
	void Update();
	void Draw(Screen& screen);

	//�p�����[�^
	Vec2 mPosition;
	Vec2 mVelocity;
	float mSize;

	//�ʏ�ړ� = NormalMove
	Vec2 mNormalVelocity;
	float mNormalMag;
	void NormalMove();

	//�_�b�V�� = Dush
	Vec2 mDushVelocity;
	float mDushMag;
	void Dush();

	//�}�[�L���O = Mark
	bool mIsMarkActive;
	Vec2 mMarkPosition;
	static constexpr int kMarkTimeLimit = 300;
	int mMarkFrame;
	void Mark();

	//�X�g���C�N = Strike
	bool mIsStrikeActive;
	float mStrikeEasingt;
	float mStrikeEasingtIncrementValue;
	Vec2 mStrikeStartPosition;
	Vec2 mStrikeEndPosition;
	void Strike();

};


