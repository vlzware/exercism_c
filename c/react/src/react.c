#include "react.h"
#include <stdlib.h>
#include <stdio.h>

void check_alloc(void *p);
void free_list(struct cell* p);
void free_deps(struct dep* p);
int add_deps(struct cell *c, struct cell *dst);
void call_deps(struct cell *c);
void scv_helper(struct cell *c, int new_value);
void set_state(struct cell *p);
void parse_state(struct cell *p);

struct reactor *r_global = NULL;

struct reactor *create_reactor()
{
	if (r_global != NULL) {
		fprintf(stderr, "Only one reactor possible!\n");
		return NULL;
	}
	r_global = (struct reactor*) malloc(sizeof(struct reactor));
	check_alloc(r_global);

	r_global->head = NULL;

	return r_global;
}

void destroy_reactor(struct reactor *r)
{
	if (r != r_global) {
		fprintf(stderr, "Invalid reactor!\n");
		return;
	}
	free_list(r_global->head);
	free(r_global);
	r_global = NULL;
}

struct cell *create_input_cell(struct reactor *r, int initial_value)
{
	struct cell* tmp = (struct cell*) malloc(sizeof(struct cell));
	check_alloc(tmp);

	tmp->next = r->head;
	tmp->val = initial_value;
	tmp->type = INPUT;
	tmp->deps = NULL;
	int i;
	for (i = 0; i < MAXCLB; i++)
		tmp->clb[i] = NULL;

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
	set_state(r_global->head);

	scv_helper(c, new_value);

	parse_state(r_global->head);
}

callback_id add_callback(struct cell *c, void *v, callback call)
{
	callback_id res = 0;
	while ((res < MAXCLB) && (c->clb[res] != NULL))
		res++;
	if (res == MAXCLB) {
		fprintf(stderr, "MAXCLB reached!\n");
		return -1;
	}

	c->clb[res] = call;
	c->clb_obj[res] = v;

	return res;
}

void remove_callback(struct cell *c, callback_id id)
{
	if (id < 0 || id >= MAXCLB) {
		fprintf(stderr, "Invalid callback_id!\n");
		return;
	}

	c->clb[id] = NULL;
}


/*
 ****************************************************
 * helpers
 ****************************************************
 */

void set_state(struct cell *p)
{
	if (p == NULL)
	 	return;

	if (p->next != NULL)
		set_state(p->next);

	p->clb_fire = 0;
}

void parse_state(struct cell *p)
{
	if (p == NULL)
		return;

	if (p->next != NULL)
		parse_state(p->next);

	if (p->clb_fire == 0)
	 	return;

	call_deps(p);

	int i;
	for (i = 0; i < MAXCLB; i++)
		if (p->clb[i] != NULL)
			p->clb[i](p->clb_obj[i], p->val);
}

 /* set cell values */
 void scv_helper(struct cell *c, int new_value)
 {
 	if ((c == NULL) || (c->val == new_value))
 		return;

	c->val = new_value;
	c->clb_fire = 1;
 }

void check_alloc(void *p)
{
	if (p == NULL) {
		fprintf(stderr, "Memory error!\n");
		exit(1);
	}
}

void free_list(struct cell *p)
{
	if (p == NULL)
		return;

	if (p->deps != NULL)
		free_deps(p->deps);

	if (p->next != NULL)
		free_list(p->next);

	free(p);
}

void free_deps(struct dep *p)
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
			scv_helper(tmp,
				tmp->fun1(c->val));
		else if (tmp->type == TWO_VARS)
			scv_helper(tmp,
				tmp->fun2(tmp->dep_a->val, tmp->dep_b->val));
		dp = dp->next;
	}
}
