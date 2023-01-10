#include "Player.h"
#include "Key.h"
#include "ControllerInput.h"
#include "Function.h"
#include "Easing.h"


void Player::Init() {
	//�p�����[�^
	mPosition.setZero();
	mVelocity.setZero();
	mSize = 64;

	//�ʏ�ړ�
	mNormalMag = 3.0f;

	//�_�b�V��
	mDushMag = 200.0f;

	//�}�[�L���O
	mIsMarkActive = false;
	mMarkFrame = 0;

	//�X�g���C�N
	mIsStrikeActive = false;
	mStrikeEasingt = 0.0f;
}



void Player::Update() {

	//���x������������
	mVelocity.setZero();

	//�X�g���C�N�����Ă��Ȃ����ɉ\
	if (!mIsStrikeActive) {

		//�ʏ�ړ�
		NormalMove();

		//�_�b�V��
		Dush();

		//�}�[�L���O
		Mark();
	}

	//�X�g���C�N
	Strike();

	//���x��������
	mPosition += mVelocity;

}

void Player::NormalMove() {

	//�X�e�B�b�N�̕������擾����
	int tmpX, tmpY;
	Controller::GetLeftStick(0, tmpX, tmpY);

	//int�^ �̒l�� float�^ �ɓ����iint�^�̂܂܂��ƌv�Z���O���P�ɂȂ�j
	mNormalVelocity.x = tmpX;
	mNormalVelocity.y = tmpY;

	//�ő�l���P�ɂ���
	mNormalVelocity = mNormalVelocity.Normalized();

	//���{����
	mNormalVelocity *= mNormalMag;

	//���x��������
	mVelocity += mNormalVelocity;
}

void Player::Dush() {

	//�X�e�B�b�N�̕������擾����
	int tmpX, tmpY;
	Controller::GetLeftStick(0, tmpX, tmpY);
	
	//�X�e�B�b�N�𗣂��Ă��_�b�V�����o����悤�ɂ���
	if (tmpX != 0 && tmpY != 0){

		//int�^ �̒l�� float�^ �ɓ����iint�^�̂܂܂��ƌv�Z���O���P�ɂȂ�j
		mDushVelocity.x = tmpX;
		mDushVelocity.y = tmpY;

		//�ő�l���P�ɂ���
		mDushVelocity = mDushVelocity.Normalized();

		//���{����
		mDushVelocity *= mDushMag;
	}

	//A�{�^��������
	if (Controller::IsTriggerButton(0,Controller::bA)){

		//���x��������
		mVelocity += mDushVelocity;
	}
}

void Player::Mark() {

	//X�{�^����������Position��ݒ聕�t���O��true�ɂ���
	if (!mIsMarkActive && Controller::IsTriggerButton(0,Controller::bX)){

		mMarkPosition = mPosition;
		mIsMarkActive = true;

	}

	//�������ԂŃ}�[�L���O������
	if (mIsMarkActive){

		//�t���[���̉��Z
		mMarkFrame++;

		//�������Ԃ𒴂�����t���O��false�ɂ���
		if (kMarkTimeLimit <= mMarkFrame){
			mIsMarkActive = false;
		}
	}

	//������
	if (!mIsMarkActive){
		mMarkFrame = 0;
	}

}

void Player::Strike() {

	if (mIsMarkActive && !mIsStrikeActive){

		//LT�{�^����RT�{�^�������������Ƀt���O��true�ɂ���
		if (Controller::IsPressedButton(0, Controller::lTrigger) && Controller::IsPressedButton(0, Controller::rTrigger)) {

			//�����ɉ����ăC�[�W���O�̑����ʂ�ω�������
			//�}�[�N�Ƃ̋��������߂�
			float tmpDistance = (mMarkPosition - mPosition).Length();

			//������0�������璆�~����
			if (tmpDistance == 0){
				mIsMarkActive = false;
				mIsStrikeActive = false;
			}
			//������0����Ȃ��Ƃ�
			else {
				//�����ʂ������ɉ����ĕς��邽�߂̌v�Z
				float tmpValue = tmpDistance / 100;

				// n / tmpValue �̂Ƃ��An�͋�����100�̂Ƃ���Easingt�̑����ʂɂȂ�
				mStrikeEasingtIncrementValue = 0.15f / tmpValue;

				//�C�[�W���O���̎n�_�ƏI�_�̐ݒ�
				mStrikeStartPosition = mPosition;
				mStrikeEndPosition = mMarkPosition;

				//�t���O��true�ɂ���
				mIsStrikeActive = true;
			}
		}
	}

	if (mIsStrikeActive){

		//�C�[�W���O�ړ�
		mStrikeEasingt = EasingClamp(mStrikeEasingtIncrementValue, mStrikeEasingt);
		mPosition = EasingMove(mStrikeStartPosition, mStrikeEndPosition, easeInSine(mStrikeEasingt));

		//�ړ����I��������
		if (mStrikeEasingt == 1.0f){
			mIsMarkActive = false;
			mIsStrikeActive = false;
		}

	}

	//������
	if (!mIsStrikeActive){

		mStrikeEasingt = 0.0f;

	}

}



void Player::Draw(Screen& screen) {

	if (mIsMarkActive){

		screen.DrawLine(mPosition, mMarkPosition, WHITE);
		screen.DrawSquare(mMarkPosition, mSize, WHITE);

	}

	screen.DrawSquare(mPosition, mSize, 0x606060FF);

}
