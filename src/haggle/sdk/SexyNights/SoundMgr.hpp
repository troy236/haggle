#pragma once

namespace SexyNights
{
	class __declspec(dllexport) SoundMgr
	{
	public:
		static SoundMgr* sound_mgr;
		static void setup();
		static bool check_exists();

		static void AddSound(int param1);
		static int FadeMusic(int a2);
	};
};
