#include "Sexy.hpp"

int SexyNights::Assets::get(Asset asset)
{
	switch (asset)
	{
		//Sounds
		case Asset::SOUND_AAH:
		{
			return *reinterpret_cast<int*>(0x006CA7D8);
		} break;

		case Asset::SOUND_PENALTY:
		{
			return *reinterpret_cast<int*>(0x006CA8E4);
		} break;

		case Asset::SOUND_COINSPIN_NO:
		{
			return *reinterpret_cast<int*>(0x006CA650);
		} break;

		case Asset::SOUND_EXPLODE:
		{
			return *reinterpret_cast<int*>(0x006CA89C);
		} break;

		case Asset::SOUND_POWERUP_GUIDE:
		{
			return *reinterpret_cast<int*>(0x006CA658);
		} break;
	}

	return 0;
}
