#include "react.h"
#include <stdlib.h>
#include <stdio.h>

void check_alloc(void *p);
void free_list(struct cell* p);
int add_deps(struct cell *c, struct cell *dst);
void call_deps(struct cell *c);

struct reactor *create_reactor()
{
	struct reactor *r;
	r = (struct reactor*) malloc(sizeof(struct reactor));
	check_alloc(r);

	r->head = NULL;

	return r;
}

void destroy_reactor(struct reactor *r)
{
	free_list(r->head);
	free(r);
}

struct cell *create_input_cell(struct reactor *r, int initial_value)
{
	struct cell* tmp = (struct cell*) malloc(sizeof(struct cell));
	check_alloc(tmp);

	tmp->next = r->head;
	tmp->val = initial_value;
	tmp->type = INPUT;
	int i;
	for (i = 0; i < MAXDEPS; i++)
		tmp->deps[i] = NULL;

	r->head = tmp;

	return r->head;
}

struct cell *create_compute1_cell(struct reactor *r, struct cell *c,
				  compute1 fun)
{
	int val = fun(get_cell_value(c));

	struct cell *res = create_input_cell(r, val);
	res->type = ONE_VAR;
	res->fun1 = fun;
	res->dep_a = c;

	add_deps(c, res);

	return res;
}

struct cell *create_compute2_cell(struct reactor *r, struct cell *ca,
				  struct cell *cb, compute2 fun)
{
	int val = fun(get_cell_value(ca), get_cell_value(cb));

	struct cell *res = create_input_cell(r, val);
	res->type = TWO_VARS;
	res->fun2 = fun;
	res->dep_a = ca;
	res->dep_b = cb;

	add_deps(ca, res);
	add_deps(cb, res);

	return res;
}

int get_cell_value(struct cell *c)
{
	if (c == NULL)
		return -1;
	return c->val;
}

void set_cell_value(struct cell *c, int new_value)
{
	if (c == NULL)
		return;
	if (c->val != new_value) {
		c->val = new_value;
		call_deps(c);
	}
}

callback_id add_callback(struct cell *c, void *v, callback call)
{
	c = c; v = v; call = call;

	callback_id res = 0;
	return res;
}

void remove_callback(struct cell *c, callback_id id)
{
	c = c; id= id;
}


/*
 ****************************************************
 * helpers
 ****************************************************
 */

void check_alloc(void *p)
{
	if (p == NULL) {
		fprintf(stderr, "Memory error!\n");
		exit(1);
	}
}

void free_list(struct cell* p)
{
	if (p->next == NULL)
		free(p);
	else
		free_list(p->next);
}

int add_deps(struct cell *c, struct cell *dst)
{
	int i = 0;
	while (c->deps[i] != NULL)
		if (++i == MAXDEPS) {
			fprintf(stderr, "Max deps reached\n");
			return 1;
		}
	c->deps[i] = dst;
	return 0;
}

void call_deps(struct cell *c)
{
	int i;
	struct cell *cd;
	for (i = 0; i < MAXDEPS; i++) {
		cd = c->deps[i];
		if (cd != NULL) {
			if (cd->type == ONE_VAR)
				set_cell_value(cd, cd->fun1(c->val));
			else if (cd->type == TWO_VARS)
				set_cell_value(cd, cd->fun2(cd->dep_a->val,
					  cd->dep_a->val));
		}
	}
}
