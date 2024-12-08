#include "Board.hpp"
#include "callbacks/callbacks.hpp"
#include "utils/memory.hpp"

SexyNights::Board* SexyNights::Board::board;

static char* (__stdcall* SexyNights__Board__Board_)(SexyNights::Board*, char*);
char* __stdcall SexyNights__Board__Board(SexyNights::Board* this_, char* thunderball)
{
	SexyNights::Board::board = this_;
	return SexyNights__Board__Board_(this_, thunderball);
}


void __declspec(naked) SexyNights__Board__LoadLevel()
{
	static constexpr auto jmp_back = 0x0040998E;
	static constexpr auto call_me = 0x00408C50;

	__asm
	{
		pushad;
		push eax;
		push edi;
		call SexyNights::callbacks::run_load_level_callbacks;
		add esp, 0x08;
		popad;
		call call_me;
		jmp jmp_back
	}
}

void SexyNights::Board::setup()
{
	MH_CreateHook((void*)0x00403FB0, SexyNights__Board__Board, (void**)&SexyNights__Board__Board_);
	jump(0x00409989, SexyNights__Board__LoadLevel);
}

bool SexyNights::Board::check_exists()
{
	if (SexyNights::Board::board == 0x0) return false;
	return true;
}

//UNTESTED
void SexyNights::Board::Reload()
{
	if (!SexyNights::Board::check_exists()) return;
	reinterpret_cast<void(__thiscall*)(SexyNights::Board*)>(0x0040E120)(SexyNights::Board::board);
}

int SexyNights::Board::Reset()
{
	if (!SexyNights::Board::check_exists()) return -1;

	static constexpr auto param1 = 0x0;
	static constexpr auto reset_func = 0x00407DE0;
	__asm
	{
		pushad;
		mov eax, SexyNights::Board::board;
		push param1;
		call reset_func; //Callee cleans the stack
		popad;
	}
}

void SexyNights::Board::SyncColorblind()
{
	if (!SexyNights::Board::check_exists()) return;
	//reinterpret_cast<int(__thiscall*)(SexyNights::Board*)>(0x004098B0)(SexyNights::Board::board);
}
