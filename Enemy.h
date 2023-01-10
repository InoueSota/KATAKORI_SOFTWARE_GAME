#pragma once
#include "Screen.h"
#include "Vec2.h"



class Snake
{
public:
	Snake() {
		Init();
	}

	void Init();
	void Update();
	void Draw(Screen& screen);

	static constexpr int kMaxLength = 10;

	//�p�����[�^
	//������
	Vec2 mHeadPosition;
	int mHeadRadius;
	float mHeadAngle;
	void Move();
	void Angle();

	//�̕�������
	static constexpr int kMaxFrame = 120;
	Vec2 mOldHeadPosition[kMaxFrame];
	float mOldHeadAngle[kMaxFrame];
	int mFollowFrame;
	int mBodyRadius;
	void Follow();
	//�́i�P�ځj
	Vec2 mFirstBodyPosition;
	float mFirstBodyAngle;
	//�́i�Q�ځj
	Vec2 mSecondBodyPosition;
	float mSecondBodyAngle;
	//�́i�R�ځj
	Vec2 mThirdBodyPosition;
	float mThirdBodyAngle;
	//�́i�S�ځj
	Vec2 mFourthBodyPosition;
	float mFourthBodyAngle;

	//�摜�֌W
	bool mIsLoadTexture = false;
	int head;

};
