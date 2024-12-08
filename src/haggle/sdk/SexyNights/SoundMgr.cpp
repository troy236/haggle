#include "SoundMgr.hpp"

SexyNights::SoundMgr* SexyNights::SoundMgr::sound_mgr;

static char* (__stdcall* SexyNights__SoundMgr__SoundMgr_)(SexyNights::SoundMgr*);
char* __stdcall SexyNights__SoundMgr__SoundMgr(SexyNights::SoundMgr* this_)
{
	SexyNights::SoundMgr::sound_mgr = this_;
	return SexyNights__SoundMgr__SoundMgr_(this_);
}

void SexyNights::SoundMgr::setup()
{
	MH_CreateHook((void*)0x00478720, SexyNights__SoundMgr__SoundMgr, (void**)&SexyNights__SoundMgr__SoundMgr_);
}

bool SexyNights::SoundMgr::check_exists()
{
	if (SexyNights::SoundMgr::sound_mgr == 0x0) return false;
	return true;
}

void SexyNights::SoundMgr::AddSound(int param1)
{
	if (!SexyNights::SoundMgr::check_exists()) return;

	static constexpr auto param2 = 0x0;
	static constexpr auto param3 = 0xbf800000;
	static constexpr auto add_sound_func = 0x00478A50;
	__asm
	{
		pushad;
		mov edi, SexyNights::SoundMgr::sound_mgr;
		xor eax, eax;
		push param3;
		push param2;
		push param1;
		call add_sound_func; //Callee cleans the stack
		popad;
	}
}
