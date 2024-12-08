#pragma once

#include <mutex>
#include <vector>
#include <unordered_map>
#include "sdk/SexyNightsSDK.hpp"

template <typename F> using callback_ = F*;

namespace SexyNights
{
	class __declspec(dllexport) callbacks final
	{
	public:
		enum class type : std::uint32_t
		{
			main_loop,
			peg_hit,
			after_peg_hit,
			begin_turn_2,
			after_begin_turn_2,
			begin_shot,
			after_begin_shot,
			show_adventure_screen,
			after_show_adventure_screen,
			start_adventure_game,
			after_start_adventure_game,
			just_beat_adventure_true,
			just_beat_adventure_false,
			do_to_menu,
			do_options_dialog,
			finish_options_dialog,
			finish_init_level,
			do_level_done,
			after_beat_level_true,
			after_beat_level_false,
			show_level_screen,
			after_show_level_screen,
			after_main_menu_update,
			load_level,
			do_play,
			after_do_play,
			after_start_game,
		};

		static void init();

		static void on(callbacks::type type, callback_<void __cdecl()> callback);
		static void on(const std::initializer_list<callbacks::type>& types, callback_<void __cdecl()> callback);

		static void on_peg_hit(callback_<void __cdecl(SexyNights::Ball*, SexyNights::PhysObj*, bool)> callback);
		static void after_peg_hit(callback_<void __cdecl(SexyNights::Ball*, SexyNights::PhysObj*, bool)> callback);
		static void on_begin_shot(callback_<void __cdecl()> callback);
		static void after_begin_shot(callback_<void __cdecl()> callback);
		static void after_begin_turn_2(callback_<void __cdecl()> callback);
		static void after_main_menu_update(callback_<void __cdecl(SexyNights::MainMenu*)> callback);
		static void on_load_level(callback_<void __cdecl(SexyNights::Board*, std::string&)> callback);
		static void on_do_play(callback_<void __cdecl(SexyNights::LevelScreen*, unsigned int)> callback);
		static void after_do_play(callback_<void __cdecl(SexyNights::LevelScreen*, unsigned int)> callback);
		static void after_start_game(callback_<void __cdecl(SexyNights::MainMenu*)> callback);

		static void once(callback_<void __cdecl()> callback);

		static void run_basic_callbacks(callbacks::type type);
		static void run_peg_hit_callbacks(SexyNights::Ball* ball, SexyNights::PhysObj* phys_obj, bool a4);
		static void run_after_peg_hit_callbacks(SexyNights::Ball* ball, SexyNights::PhysObj* phys_obj, bool a4);
		static void run_begin_shot_callbacks();
		static void run_after_begin_shot_callbacks();
		static void run_after_begin_turn_2_callbacks();
		static void run_after_main_menu_update_callbacks(SexyNights::MainMenu* main_menu);
		static void run_load_level_callbacks(SexyNights::Board* board, std::string& level_name);
		static void run_do_play_callbacks(SexyNights::LevelScreen* level_screen, unsigned int a3);
		static void run_after_do_play_callbacks(SexyNights::LevelScreen* level_screen, unsigned int a3);
		static void run_after_start_game_callbacks(SexyNights::MainMenu* main_menu);

	private:

		static std::mutex mtx_;
		static std::vector<callback_<void __cdecl()>> once_callbacks_;

		static std::unordered_map<callbacks::type, std::vector<callback_<void __cdecl()>>> basic_callbacks_;
		static std::unordered_map<callbacks::type, std::vector<callback_<void __cdecl(SexyNights::Ball*, SexyNights::PhysObj*, bool)>>> peg_hit_callbacks_;
		static std::unordered_map<callbacks::type, std::vector<callback_<void __cdecl()>>> begin_shot_callbacks_;
		static std::unordered_map<callbacks::type, std::vector<callback_<void __cdecl()>>> begin_turn_2_callbacks_;
		static std::unordered_map<callbacks::type, std::vector<callback_<void __cdecl(SexyNights::MainMenu*)>>> main_menu_update_callbacks_;
		static std::unordered_map<callbacks::type, std::vector<callback_<void __cdecl(SexyNights::Board*, std::string&)>>> load_level_callbacks_;
		static std::unordered_map<callbacks::type, std::vector<callback_<void __cdecl(SexyNights::LevelScreen*, unsigned int)>>> do_play_callbacks_;
		static std::unordered_map<callbacks::type, std::vector<callback_<void __cdecl(SexyNights::MainMenu*)>>> start_game_callbacks_;
	};
}
