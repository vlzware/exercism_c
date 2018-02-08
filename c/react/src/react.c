#include "react.h"
#include <stdlib.h>
#include <stdio.h>

void check_alloc(void *p);
void free_list(struct cell* p);
void free_deps(struct dep* p);
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
	tmp->deps = NULL;

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
	if (p != NULL) {
		if (p->deps != NULL)
			free_deps(p->deps);
		if (p->next != NULL)
			free(p->next);
		free(p);
	}
}

void free_deps(struct dep* p)
{
	if (p->next != NULL)
		free_deps(p->next);
	free(p);
}


int add_deps(struct cell *c, struct cell *dst)
{
	struct dep* tmp = (struct dep*) malloc(sizeof(struct dep));
	check_alloc(tmp);

	tmp->next = c->deps;
	tmp->dep = dst;
	c->deps = tmp;

	return 0;
}

void call_deps(struct cell *c)
{
	struct dep *dp = c->deps;
	while (dp != NULL) {
		struct cell *tmp = dp->dep;
		if (tmp->type == ONE_VAR)
			set_cell_value(tmp, tmp->fun1(c->val));
		else if (tmp->type == TWO_VARS)
			set_cell_value(tmp, tmp->fun2(tmp->dep_a->val,
				  tmp->dep_a->val));
		dp = dp->next;
	}
}

#ifndef TTT
static int times2(int x)
{
   return x * 2;
}
// static int times30(int x)
// {
//    return x * 30;
// }
static int plus(int x, int y)
{
   return x + y;
}
int main(void)
{
	struct reactor *r = 	create_reactor();
	struct cell *input = 	create_input_cell(r, 1);
	struct cell *times_two =create_compute1_cell(r, input, times2);
	struct cell *output = 	create_compute2_cell(r, input, times_two, plus);

	printf("32? %i\n", get_cell_value(output));
	set_cell_value(input, 3);
	printf("96? %i\n", get_cell_value(output));

	destroy_reactor(r);

	return 0;
}
#endif
