#include "space_age.h"

const long int EARTH_YEAR = 31557600;

const float orb_period[COUNT_PLANETS] = {
		1.0,
		0.2408467,
		0.61519726,
		1.8808158,
		11.862615,
		29.447498,
		84.016846,
		164.79132
	};

float convert_planet_age(enum planets planet, long int secs)
{
	return (float) (secs / (orb_period[planet] * EARTH_YEAR));
}
