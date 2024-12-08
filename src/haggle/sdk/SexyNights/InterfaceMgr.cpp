#include "InterfaceMgr.hpp"
#include "Graphics.hpp"
#include "utils/memory.hpp"

SexyNights::InterfaceMgr* SexyNights::InterfaceMgr::interface_mgr;

void __declspec(naked) SexyNights__InterfaceMgr__InterfaceMgr()
{
	static constexpr auto constructor = 0x006356B2;
	static constexpr auto jmp_back = 0x00462AD5;

	__asm
	{
		call constructor;
		mov SexyNights::InterfaceMgr::interface_mgr, esi;
		jmp jmp_back;
	}
}

void SexyNights::InterfaceMgr::setup()
{
	jump(0x00462AD0, SexyNights__InterfaceMgr__InterfaceMgr);
}

bool SexyNights::InterfaceMgr::check_exists()
{
	if (SexyNights::InterfaceMgr::interface_mgr == 0x0) return false;
	return true;
}

//UNTESTED
SexyNights::InterfaceMgr* SexyNights::InterfaceMgr::LoadGun()
{
	if (!SexyNights::InterfaceMgr::check_exists()) return 0;
	return reinterpret_cast<SexyNights::InterfaceMgr * (__thiscall*)(SexyNights::InterfaceMgr*)>(0x00463BC0)(SexyNights::InterfaceMgr::interface_mgr);
}

void SexyNights::InterfaceMgr::SetNumBalls(int count)
{
	if (!SexyNights::InterfaceMgr::check_exists()) return;

	static constexpr auto set_num_balls_func = 0x00463C10;
	__asm
	{
		push ebx;
		push eax;
		mov ebx, SexyNights::InterfaceMgr::interface_mgr;
		mov eax, count;
		call set_num_balls_func;
		pop eax;
		pop ebx;
	}
}
