/**
 * Design:
 * reactor->head points to a linked list of all cell's
 * each cell can be input, or two types of output (see compute_type)
 * dep_a and dep_b point to the cells needed to calculate fun1/fun2
 * deps is a linked list which contains every cell which depends on
 * 	the content of the current cell
 * each cell can have up to MAXCLB callbacks with their clb_obj
 * clb_fire get set to 1 if the value got updated between state changes
 */

#ifndef REACT_H
#define REACT_H

#define MAXCLB 5 /* max callbacks pro cell */

typedef int (*compute1) (int);
typedef int (*compute2) (int, int);

typedef void (*callback) (void *, int);
typedef int callback_id;

enum compute_type {INPUT, ONE_VAR, TWO_VARS};

struct dep {
	struct dep *next;
	struct cell *dep;
};

struct cell {
	int val;
	struct cell *next;

	enum compute_type type;
	compute1 fun1;
	compute2 fun2;
	struct cell *dep_a;
	struct cell *dep_b;

	struct dep *deps;

	callback clb[MAXCLB];
	void *clb_obj[MAXCLB];

	int clb_fire;
};

struct reactor {
	struct cell *head;
};

struct reactor *create_reactor();
// destroy_reactor should free all cells created under that reactor.
void destroy_reactor(struct reactor *r);

struct cell *create_input_cell(struct reactor *, int initial_value);
struct cell *create_compute1_cell(struct reactor *, struct cell *, compute1);
struct cell *create_compute2_cell(struct reactor *, struct cell *,
                                  struct cell *, compute2);

int get_cell_value(struct cell *);
void set_cell_value(struct cell *, int new_value);

// The callback should be called with the same void * given in add_callback.
callback_id add_callback(struct cell *, void *, callback);
void remove_callback(struct cell *, callback_id);

#endif
