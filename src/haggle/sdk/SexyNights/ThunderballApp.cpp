#include "ThunderballApp.hpp"
#include "callbacks/callbacks.hpp"
#include "utils/memory.hpp"

SexyNights::ThunderballApp* SexyNights::ThunderballApp::thunderball = *reinterpret_cast<SexyNights::ThunderballApp**>(0x006CBE04);

static void(__stdcall* SexyNights__ThunderballApp__DoToMenu_)(SexyNights::ThunderballApp*);
void __stdcall SexyNights__ThunderballApp__DoToMenu(SexyNights::ThunderballApp* this_)
{
	SexyNights::callbacks::run_basic_callbacks(SexyNights::callbacks::type::do_to_menu);
	SexyNights__ThunderballApp__DoToMenu_(this_);
}

static int(__fastcall* SexyNights__ThunderballApp__DoOptionsDialog_)(SexyNights::ThunderballApp*, char*);
int __fastcall SexyNights__ThunderballApp__DoOptionsDialog(SexyNights::ThunderballApp* this_, char* edx)
{
	SexyNights::callbacks::run_basic_callbacks(SexyNights::callbacks::type::do_options_dialog);
	return SexyNights__ThunderballApp__DoOptionsDialog_(this_, edx);
}

void __declspec(naked) SexyNights__ThunderballApp__FinishOptionsDialog()
{
	static constexpr auto hook_type = SexyNights::callbacks::type::finish_options_dialog;
	static constexpr auto jmp_back = 0x0042fdd5;

	__asm
	{
		push ebp;
		mov ebp, esp;
		push ecx;
		push ebx;
		pushad;
		push hook_type;
		call SexyNights::callbacks::run_basic_callbacks;
		add esp, 0x04;
		popad;
		jmp jmp_back
	}
}

void SexyNights::ThunderballApp::setup()
{
	MH_CreateHook((void*)0x00430360, SexyNights__ThunderballApp__DoToMenu, (void**)&SexyNights__ThunderballApp__DoToMenu_);
	MH_CreateHook((void*)0x0042E420, SexyNights__ThunderballApp__DoOptionsDialog, (void**)&SexyNights__ThunderballApp__DoOptionsDialog_);
	jump(0x0042FDD0, SexyNights__ThunderballApp__FinishOptionsDialog);
}

bool SexyNights::ThunderballApp::check_exists()
{
	if (SexyNights::ThunderballApp::thunderball == 0x0) return false;
	return true;
}

void SexyNights::ThunderballApp::DoToMenu()
{
	if (!SexyNights::ThunderballApp::check_exists()) return;

	static constexpr auto do_to_menu_func = 0x00430360;
	__asm
	{
		pushad;
		mov esi, SexyNights::ThunderballApp::thunderball;
		call do_to_menu_func;
		popad;
	}
}
