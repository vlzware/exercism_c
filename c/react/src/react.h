#ifndef REACT_H
#define REACT_H

#include <stddef.h>

typedef int (*compute1) (int);
typedef int (*compute2) (int, int);

enum compute_type {INPUT, ONE_VAR, TWO_VARS};

/* max count of cells that receive a signal */
#define MAXDEPS 5

struct cell {
	int val;
	struct cell *next;
	enum compute_type type;
	compute1 fun1;
	compute2 fun2;
	struct cell *dep_a;
	struct cell *dep_b;
	struct cell *deps[MAXDEPS];
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

typedef void (*callback) (void *, int);
typedef int callback_id;

// The callback should be called with the same void * given in add_callback.
callback_id add_callback(struct cell *, void *, callback);
void remove_callback(struct cell *, callback_id);

#endif
