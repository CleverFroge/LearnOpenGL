#include "FrogEngine.h"
using namespace FrogEngine;

Tank::Tank(const char* path)
{
	this->AddChild(Model::LoadModel(path, true));
	_battery = Find("Battery");
	_cannon = Find("Cannon");
}

Tank::~Tank()
{

}

void Tank::Move(Vector3 direction, float deltaTime)
{
	LocalPosition = LocalPosition + direction * 10 * deltaTime;
}

void Tank::Aim(float deltaX, float deltaY)
{
	float sen = 0.05;
	if (_battery)
	{
		float eulerAngle = _battery->GetLocalEulerAngles().GetY();
		_battery->SetLocalEulerAngleY(eulerAngle - deltaX* sen);
	}

	if (_cannon)
	{
		float eulerAngle = _cannon->GetLocalEulerAngles().GetZ();
		_cannon->SetLocalEulerAngleZ(eulerAngle - deltaY* sen);
	}
}