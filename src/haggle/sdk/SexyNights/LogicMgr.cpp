#include "LogicMgr.hpp"
#include "utils/memory.hpp"
#include "callbacks/callbacks.hpp"

SexyNights::LogicMgr* SexyNights::LogicMgr::logic_mgr;

static char* (__stdcall* SexyNights__LogicMgr__LogicMgr_)(SexyNights::LogicMgr*, int);
char* __stdcall SexyNights__LogicMgr__LogicMgr(SexyNights::LogicMgr* this_, int a2)
{
	SexyNights::LogicMgr::logic_mgr = this_;
	return SexyNights__LogicMgr__LogicMgr_(this_, a2);
}

static char* (__fastcall* SexyNights__LogicMgr__LogicMgr_dtor_)(SexyNights::LogicMgr*, char*);
char* __fastcall SexyNights__LogicMgr__LogicMgr_dtor(SexyNights::LogicMgr* this_, char* edx)
{
	SexyNights::LogicMgr::logic_mgr = nullptr;
	return SexyNights__LogicMgr__LogicMgr_dtor_(this_, edx);
}

static void(__fastcall* SexyNights__LogicMgr__DoPowerup_)(SexyNights::LogicMgr*, char*, SexyNights::Ball*, SexyNights::PhysObj*, int, int);
void __fastcall SexyNights__LogicMgr__DoPowerup(SexyNights::LogicMgr* this_, char* edx, SexyNights::Ball* a2, SexyNights::PhysObj* a3, int powerup, int a5)
{
	return SexyNights__LogicMgr__DoPowerup_(this_, edx, a2, a3, powerup, a5);
}

static void(__fastcall* SexyNights__LogicMgr__PegHit_)(SexyNights::LogicMgr*, char*, SexyNights::Ball*, SexyNights::PhysObj*, bool);
void __fastcall SexyNights__LogicMgr__PegHit(SexyNights::LogicMgr* this_, char* edx, SexyNights::Ball* ball, SexyNights::PhysObj* phys_obj, bool a4)
{
	SexyNights::callbacks::run_peg_hit_callbacks(ball, phys_obj, a4);
	SexyNights__LogicMgr__PegHit_(this_, edx, ball, phys_obj, a4);
	SexyNights::callbacks::run_after_peg_hit_callbacks(ball, phys_obj, a4);
}

void __declspec(naked) SexyNights__LogicMgr__BeginShot()
{
	static constexpr auto jmp_back = 0x0046C236;

	__asm
	{
		push ebp;
		mov ebp, esp;
		sub esp, 0x30;
		pushad;
		call SexyNights::callbacks::run_begin_shot_callbacks;
		popad;
		pushad;
		call SexyNights::callbacks::run_after_begin_shot_callbacks;
		popad;
		jmp jmp_back
	}
}

void __declspec(naked) SexyNights__LogicMgr__BeginTurn2()
{
	static constexpr auto hook_type = SexyNights::callbacks::type::begin_turn_2;
	static constexpr auto jmp_back = 0x0046B95A;

	__asm
	{
		push ecx;
		cmp byte ptr[ebx + 0x101], 0x0;
		push esi;
		push edi;
		pushad;
		push hook_type;
		call SexyNights::callbacks::run_basic_callbacks;
		add esp, 0x04;
		popad;
		pushad;
		call SexyNights::callbacks::run_after_begin_turn_2_callbacks;
		popad;
		jmp jmp_back
	}
}

void __declspec(naked) SexyNights__LogicMgr__DoLevelDone()
{
	static constexpr auto hook_type = SexyNights::callbacks::type::do_level_done;
	static constexpr auto jmp_back = 0x0046BE6A;

	__asm
	{
		push ebx;
		push esi;
		mov esi, eax;
		mov eax, dword ptr[esi + 0x184];
		pushad;
		push hook_type;
		call SexyNights::callbacks::run_basic_callbacks;
		add esp, 0x04;
		popad;
		jmp jmp_back
	}
}

void SexyNights::LogicMgr::setup()
{
	MH_CreateHook((void*)0x00466C30, SexyNights__LogicMgr__LogicMgr, (void**)&SexyNights__LogicMgr__LogicMgr_);
	MH_CreateHook((void*)0x00466E80, SexyNights__LogicMgr__LogicMgr_dtor, (void**)&SexyNights__LogicMgr__LogicMgr_dtor_);
	MH_CreateHook((void*)0x0046E9C0, SexyNights__LogicMgr__DoPowerup, (void**)&SexyNights__LogicMgr__DoPowerup_);
	MH_CreateHook((void*)0x004701B0, SexyNights__LogicMgr__PegHit, (void**)&SexyNights__LogicMgr__PegHit_);

	jump(0x0046C230, SexyNights__LogicMgr__BeginShot);
	jump(0x0046B950, SexyNights__LogicMgr__BeginTurn2);
	//MH_CreateHook((void*)0x0046C220, SexyNights__LogicMgr__FinishInitLevelText, (void**)&SexyNights__LogicMgr__FinishInitLevelText_);
	jump(0x0046BE60, SexyNights__LogicMgr__DoLevelDone);
	//MH_CreateHook((void*)0x0046BA90, SexyNights__LogicMgr__BeatLevel, (void**)&SexyNights__LogicMgr__BeatLevel_);
}

bool SexyNights::LogicMgr::check_exists()
{
	if (logic_mgr != nullptr)
	{
		return true;
	}
	return false;
}

int SexyNights::LogicMgr::GetBallCount()
{
	if (!check_exists()) return -1;
	return *(int*)(SexyNights::LogicMgr::logic_mgr + 0x208 + *(int*)(SexyNights::LogicMgr::logic_mgr + 0x1ac) * 4);
}

SexyNights::LogicMgr* SexyNights::LogicMgr::IncNumBalls(int top_count, bool bottom)
{
	if (!check_exists()) return 0;

	static constexpr auto inc_num_balls_func = 0x00468360;
	__asm
	{
		push esi;
		push eax;
		mov esi, SexyNights::LogicMgr::logic_mgr;
		mov eax, top_count;
		push bottom;
		call inc_num_balls_func; //Callee cleans the stack
		pop eax;
		pop esi;
	}
}

void SexyNights::LogicMgr::DoPowerup(SexyNights::Ball* ball, SexyNights::PhysObj* phys_obj, int powerup, int a5)
{
	if (!check_exists()) return;
	reinterpret_cast<void(__thiscall*)(LogicMgr*, SexyNights::Ball*, SexyNights::PhysObj*, int, int)>(0x0046E9C0)
		(logic_mgr, ball, phys_obj, powerup, a5);
}

void SexyNights::LogicMgr::ActivatePowerup(int powerup, int a3)
{
	if (!check_exists()) return;
	reinterpret_cast<void(__thiscall*)(LogicMgr*, int, int)>(0x0046AA40)(logic_mgr, powerup, a3);
}

SexyNights::FloatingText* SexyNights::LogicMgr::AddStandardText(std::string& string_param, float x_pos, float y_pos, int font_type)
{
	if (!check_exists()) return 0;

	static constexpr auto add_standard_text_func = 0x00468DD0;
	void* return_value = (void*)0x0;
	__asm
	{
		push eax;
		push edi;
		mov eax, SexyNights::LogicMgr::logic_mgr;
		mov edi, font_type;
		push y_pos;
		push x_pos;
		push string_param;
		call add_standard_text_func; //Callee cleans the stack
		mov return_value, eax;
		pop edi;
		pop eax;
	}
	return (SexyNights::FloatingText*)return_value;
}

bool SexyNights::LogicMgr::BeginTurn2()
{
	if (!check_exists()) return false;
	return reinterpret_cast<bool(__thiscall*)(LogicMgr*)>(0x0046B950)(logic_mgr);
}

void SexyNights::LogicMgr::SetWearHat(int a2)
{
	if (!check_exists()) return;
	//Crash
	//reinterpret_cast<void(__thiscall*)(LogicMgr*, int)>(0x0046ADA0)(logic_mgr, a2);
}

void SexyNights::LogicMgr::SetState(State newState)
{
	if (!check_exists()) return;
	reinterpret_cast<int(__thiscall*)(LogicMgr*, State)>(0x00468190)(logic_mgr, newState);
}

SexyNights::LogicMgr::State SexyNights::LogicMgr::GetState(void)
{
	if (!check_exists()) return State::None;

	int* logicState = reinterpret_cast<int*>(logic_mgr + 0x04);

	if (logicState == nullptr)
	{
		return State::None;
	}

	return static_cast<State>(*logicState);
}

void SexyNights::LogicMgr::SetGunAngleRadians(float newAngleRadians)
{
	SexyNights::LogicMgr::SetGunAngle(newAngleRadians);
}

void SexyNights::LogicMgr::SetGunAngleDegrees(float newAngleDegrees)
{
	SexyNights::LogicMgr::SetGunAngle(DegreesToRadians(newAngleDegrees));
}

void SexyNights::LogicMgr::SetGunAngle(float newAngleDegrees)
{
	if (!check_exists()) return;

	static constexpr auto set_gun_angle_func = 0x00468d00;
	__asm
	{
		push esi;
		mov esi, SexyNights::LogicMgr::logic_mgr;
		push newAngleDegrees;
		call set_gun_angle_func; //Callee cleans the stack
		pop esi;
	}
}

float SexyNights::LogicMgr::GetGunAngleRadians(void)
{
	if (!check_exists()) return 0.0f;

	float* gunAnglePtr = reinterpret_cast<float*>(logic_mgr + 0xEC);

	if (gunAnglePtr == nullptr)
	{
		return 0.0f;
	}

	return *gunAnglePtr;
}

float SexyNights::LogicMgr::GetGunAngleDegrees(void)
{
	if (!check_exists()) return 0.0f;

	float* gunAnglePtr = reinterpret_cast<float*>(logic_mgr + 0xEC);

	if (gunAnglePtr == nullptr)
	{
		return 0.0f;
	}

	return RadiansToDegrees(*gunAnglePtr);
}

constexpr float DOWN_ROTATION_DEGREES = 270.0f;
float SexyNights::LogicMgr::DegreesToRadians(float angleDegrees)
{
	constexpr double PI = 3.141592653589793238;
	constexpr float DEG_TO_RAD_SCALAR = PI / 180.0f;

	return std::fmodf(DOWN_ROTATION_DEGREES + angleDegrees, 360.0f) * DEG_TO_RAD_SCALAR;
}

float SexyNights::LogicMgr::RadiansToDegrees(float angleRadians)
{
	constexpr double PI = 3.141592653589793238;
	constexpr float DEG_TO_RAD_SCALAR = PI / 180.0f;
	constexpr float RAD_TO_DEG_SCALAR = 180.0f / PI;

	return std::fmodf(angleRadians * RAD_TO_DEG_SCALAR + DOWN_ROTATION_DEGREES, 360.0f) - 180.0f;
}
