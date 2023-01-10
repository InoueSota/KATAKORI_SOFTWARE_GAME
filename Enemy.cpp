#include "Enemy.h"
#include "Key.h"
#include "Function.h"



void Snake::Init() {
	mHeadRadius = 50;
	mBodyRadius = 30;
	mFollowFrame = 0;
	mHeadPosition = { 0, 0 };
	for (int i = 0; i < kMaxFrame; i++){
		mOldHeadPosition[i] = mHeadPosition;
	}
}



void Snake::Update() {
	Move();
}

void Snake::Move() {

	//�ړ�����
	if (Key::IsPress(DIK_UP)){
		mHeadPosition.y += 3;
	}
	if (Key::IsPress(DIK_DOWN)) {
		mHeadPosition.y -= 3;
	}
	if (Key::IsPress(DIK_LEFT)) {
		mHeadPosition.x -= 3;
	}
	if (Key::IsPress(DIK_RIGHT)) {
		mHeadPosition.x += 3;
	}

	//������ς��鏈��
	Angle();

	//�̕������ǂ�����
	Follow();
}

void Snake::Angle() {

	//����ƌ����x�N�g��
	Vec2 base = { 1,0 };
	Vec2 tmpDirection = mHeadPosition - mOldHeadPosition[1];

	//�����x�N�g���ɂ���
	tmpDirection = tmpDirection.Normalized();

	//�Ȃ��p�����߂�
	float dp = tmpDirection.Dot(base);
	float cp = tmpDirection.Cross(base);
	mHeadAngle = atan2(cp, dp);

}

void Snake::Follow() {

	//���������Ă���Ƃ�
	if (mOldHeadPosition[0].x != mHeadPosition.x || mOldHeadPosition[0].y != mHeadPosition.y) {

		//���Z���Ă���t���[�����ő�l�ȉ��̂Ƃ�
		if (mFollowFrame < kMaxFrame) {

			//�P�t���[�����X�V����
			for (int i = mFollowFrame - 1; i > -1; i--) {
				if (i != 0) {
					mOldHeadPosition[i] = mOldHeadPosition[i - 1];
					mOldHeadAngle[i] = mOldHeadAngle[i - 1];
				}
			}

			//�O�t���[���ڂ͓�
			mOldHeadPosition[0] = mHeadPosition;
			mOldHeadAngle[0] = mHeadAngle;

			//�t���[�������Z����
			mFollowFrame++;
		}
		else {

			//�P�t���[�����X�V����
			for (int i = kMaxFrame - 1; i > -1; i--) {
				if (i != 0) {
					mOldHeadPosition[i] = mOldHeadPosition[i - 1];
					mOldHeadAngle[i] = mOldHeadAngle[i - 1];
				}
			}
			//�O�Ԗڂ͓��ɍX�V����
			mOldHeadPosition[0] = mHeadPosition;
			mOldHeadAngle[0] = mHeadAngle;
		}
	}
	
	//�C�ӂ�OldPosition��������
	//�́i�P�ځj
	mFirstBodyPosition = mOldHeadPosition[19];
	mFirstBodyAngle = mOldHeadAngle[19];
	//�́i�Q�ځj
	mSecondBodyPosition = mOldHeadPosition[39];
	mSecondBodyAngle = mOldHeadAngle[39];
	//�́i�R�ځj
	mThirdBodyPosition = mOldHeadPosition[59];
	mThirdBodyAngle = mOldHeadAngle[59];
	//�́i�S�ځj
	mFourthBodyPosition = mOldHeadPosition[79];
	mFourthBodyAngle = mOldHeadAngle[79];

}



void Snake::Draw(Screen& screen) {

	if (!mIsLoadTexture){
		head = Novice::LoadTexture("./Resources/Debugs/head.png");
		mIsLoadTexture = true;
	}

	//�̕`��
	screen.DrawPicture(mFourthBodyPosition, mBodyRadius, mFourthBodyAngle, 100, 100, head);
	screen.DrawPicture(mThirdBodyPosition, mBodyRadius, mThirdBodyAngle, 100, 100, head);
	screen.DrawPicture(mSecondBodyPosition, mBodyRadius, mSecondBodyAngle, 100, 100, head);
	screen.DrawPicture(mFirstBodyPosition, mBodyRadius, mFirstBodyAngle, 100, 100, head);

	//���`��
	screen.DrawPicture(mHeadPosition, mHeadRadius, mHeadAngle, 100, 100, head);

}
