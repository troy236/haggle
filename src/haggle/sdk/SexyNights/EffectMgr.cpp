#include "EffectMgr.hpp"
#include "utils/memory.hpp"

SexyNights::EffectMgr* SexyNights::EffectMgr::effect_mgr;

void __declspec(naked) SexyNights__EffectMgr__EffectMgr()
{
	static constexpr auto constructor = 0x006356B2;

	__asm
	{
		call constructor;
		mov eax, esi;
		mov SexyNights::EffectMgr::effect_mgr, eax;
		ret;
	}
}

void SexyNights::EffectMgr::setup()
{
	jump(0x0045D168, SexyNights__EffectMgr__EffectMgr);
}

bool SexyNights::EffectMgr::check_exists()
{
	if (SexyNights::EffectMgr::effect_mgr == 0x0) return false;
	return true;
}

//UNTESTED
void SexyNights::EffectMgr::AddPyramid(float a2, float a3)
{
	if (!SexyNights::EffectMgr::check_exists()) return;
	reinterpret_cast<void(__thiscall*)(SexyNights::EffectMgr*, float, float)>(0x0045F0E0)(SexyNights::EffectMgr::effect_mgr, a2, a3);
}

void SexyNights::EffectMgr::AddJimmy(bool a2)
{
	if (!SexyNights::EffectMgr::check_exists()) return;

	static constexpr auto add_jimmy_func = 0x0045F3E0;
	__asm
	{
		pushad;
		mov ebx, SexyNights::EffectMgr::effect_mgr;
		push a2;
		call add_jimmy_func; //Callee cleans the stack
		popad;
	}
}
