#include "queen_attack.h"

#define WIDTH 8

static int abs(int x)
{
	return (x < 0) ? -x : x;
}

static int same_diag(int a_1, int a_2, int b_1, int b_2)
{
	return abs(b_2 - a_2) == abs(b_1 - a_1);
}

attack_status_t can_attack(position_t queen_1, position_t queen_2)
{
	if (
		queen_1.column >= WIDTH || queen_1.row >= WIDTH ||
		queen_2.column >= WIDTH || queen_2.row >= WIDTH ||
		(
			(queen_1.column == queen_2.column) &&
			(queen_1.row == queen_2.row)
		)
	)
		return INVALID_POSITION;

	if (
		(queen_1.column == queen_2.column) ||
		(queen_1.row == queen_2.row)
	)
		return CAN_ATTACK;

	return
		same_diag(queen_1.column, queen_1.row, queen_2.column,
			queen_2.row)
		? CAN_ATTACK : CAN_NOT_ATTACK;
}
