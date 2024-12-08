#include "Ball.hpp"

SexyNights::Ball* SexyNights::Ball::ball;

static SexyNights::Ball* (__stdcall* SexyNights__Ball__Ball_)();
SexyNights::Ball* __stdcall SexyNights__Ball__Ball()
{
	auto result = SexyNights__Ball__Ball_();
	SexyNights::Ball::ball = result;
	return result;
}

void SexyNights::Ball::setup()
{
	MH_CreateHook((void*)0x00491AC0, SexyNights__Ball__Ball, (void**)&SexyNights__Ball__Ball_);
}

bool SexyNights::Ball::check_exists()
{
	if (SexyNights::Ball::ball == 0x0) return false;
	return true;
}

void SexyNights::Ball::SetPos(float x_pos, float y_pos)
{
	if (!SexyNights::Ball::check_exists()) return;
	reinterpret_cast<void(__thiscall*)(SexyNights::Ball*, float, float)>(0x00492470)(SexyNights::Ball::ball, x_pos, y_pos);
}

void SexyNights::Ball::SetVelocity(float x_velo, float y_velo)
{
	if (!SexyNights::Ball::check_exists()) return;
	reinterpret_cast<void(__thiscall*)(SexyNights::Ball*, float, float)>(0x004924C0)(SexyNights::Ball::ball, x_velo, y_velo);
}
