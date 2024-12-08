#pragma once

namespace SexyNights
{
	class __declspec(dllexport) EffectMgr
	{
	public:
		static EffectMgr* effect_mgr;
		static void setup();
		static bool check_exists();

		static void AddPyramid(float a2, float a3);
		static void AddJimmy(bool a2);
	};
};
