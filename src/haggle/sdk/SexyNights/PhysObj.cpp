#include "PhysObj.hpp"

float& SexyNights::PhysObj::mGravity = *reinterpret_cast<float*>(0x00649D80);

static SexyNights::PhysObj(__stdcall* SexyNights__PhysObj__PhysObj_)(SexyNights::PhysObj*);
SexyNights::PhysObj __stdcall SexyNights__PhysObj__PhysObj(SexyNights::PhysObj* this_)
{
	return SexyNights__PhysObj__PhysObj_(this_);
}

void SexyNights::PhysObj::setup()
{
	MH_CreateHook((void*)0x0049EB50, SexyNights__PhysObj__PhysObj, (void**)&SexyNights__PhysObj__PhysObj_);
}

bool SexyNights::PhysObj::check_exists()
{
	return true;
}
