#ifndef SPACEAGE_H
#define SPACEAGE_H

enum planets {
		EARTH = 0,
		MERCURY,
		VENUS,
		MARS,
		JUPITER,
		SATURN,
		URANUS,
		NEPTUNE,
		COUNT_PLANETS
	};

float convert_planet_age(enum planets, long int secs);

#endif
