#pragma once

//Size: 592

namespace Sexy
{
	class Board
	{
	public:
		static Board* board;

		static void setup();
		static bool check_exists();

		static void Reload(Sexy::Board* board = Sexy::Board::board);
	};
};
