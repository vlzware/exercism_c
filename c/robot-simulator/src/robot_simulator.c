#include "robot_simulator.h"

robot_grid_status_t robot_init(void)
{
	robot_grid_status_t grid = {
		(bearing_t) DEFAULT_BEARING,
		{DEFAULT_X_COORDINATE, DEFAULT_Y_COORDINATE}
	};
	return grid;
}

robot_grid_status_t robot_init_with_position(int bearing, int x, int y)
{
	if (bearing < 0 || bearing >= HEADING_MAX)
		bearing = DEFAULT_BEARING;
	bearing_t b = (bearing_t) bearing;
	robot_grid_status_t grid = { b, {x, y} };
	return grid;
}

void robot_turn_right(robot_grid_status_t *robot)
{
	int b = robot->bearing;
	robot->bearing =
		((bearing_t) (b + 1) == HEADING_MAX)?
		HEADING_NORTH : (bearing_t)(b + 1);
}

void robot_turn_left(robot_grid_status_t *robot)
{
	int b = robot->bearing;
	robot->bearing =
		((bearing_t) b == HEADING_NORTH)?
		HEADING_WEST : (bearing_t)(b - 1);

}

void robot_advance(robot_grid_status_t *robot)
{
	switch (robot->bearing) {
	case HEADING_NORTH:
		robot->grid.y_position++;
		break;
	case HEADING_EAST:
		robot->grid.x_position++;
		break;
	case HEADING_SOUTH:
		robot->grid.y_position--;
		break;
	case HEADING_WEST:
		robot->grid.x_position--;
		break;
	case HEADING_MAX:
		break;
	}
}

void robot_simulator(robot_grid_status_t *robot, const char *commands)
{
	char *cmd = (char*) commands;
	while (*cmd) {
		switch (*cmd) {
		case COMMAND_LEFT:
			robot_turn_left(robot);
			break;
		case COMMAND_RIGHT:
			robot_turn_right(robot);
			break;
		case COMMAND_ADVANCE:
			robot_advance(robot);
			break;
		}
		cmd++;
	}
}
