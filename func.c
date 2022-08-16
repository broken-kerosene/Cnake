#include "func.h"
#include <unistd.h>
#include <curses.h>
#include <stdlib.h>


static struct my_snake * growth(struct my_snake * cnake)
{
	struct my_snake *last;
	last = cnake;
	while(last->prev != NULL){
		last = last->prev;
	}

	struct my_snake *k = malloc(sizeof(struct my_snake));
	k->x = last->x;
	k->y = last->y;
	k->elem = '@';
	k->next = NULL;
	k->prev = NULL;
	return k;
}


static void show_snake(struct my_snake * cnake)
{
	move(cnake->y, cnake->x);
	addch(cnake->elem | A_BOLD);

	struct my_snake * prev_elem;
	if(cnake->prev != NULL){
		prev_elem = cnake->prev;
		while(prev_elem != NULL){
			move(prev_elem->y, prev_elem->x);
			addch(prev_elem->elem | A_BOLD);
			prev_elem = prev_elem->prev;
		}
	}
	refresh();	
}

static void hide_snake(struct my_snake * cnake)
{
	move(cnake->y, cnake->x);
	addch(' ');

	struct my_snake * prev_elem;
	if(cnake->prev != NULL){
		prev_elem = cnake->prev;
		while(prev_elem != NULL){
			move(prev_elem->y, prev_elem->x);
			addch(' ');
			prev_elem = prev_elem->prev;
		}
	}
	refresh();
}

static int check(int coor,  int max)
{
	if(coor < 0){
		return 0;
	}
	else{
		if(coor > max){
			return max;
		}
	}
	return coor;	
}

void clear_snake(struct my_snake *first)
{
	if(first->prev == NULL){
		free(first);
		return;
	}
	first = first->prev;
	while(first){
		free(first->next);
		if(first->prev == NULL){
			free(first);
			first = NULL;
		}
		else{
			first = first->prev;
		}
	}
}

int take_rand(int num)
{
		int result = 1 + (int)((double)num*rand()/(RAND_MAX+1.0));
		return result;
}

void move_snake(struct my_snake * cnake, int mx, int my, move_dir delta, int * r_x, int * r_y)
{
	hide_snake(cnake);
	int flag=0;
	struct my_snake * k;
	if(cnake->x == *r_x && cnake->y == *r_y){
		k = growth(cnake);		
		flag = 1;
		*r_x = take_rand(mx);
		*r_y = take_rand(my);
		move(*r_y, *r_x);
		addch('#');
	}

	struct my_snake *last;
	last = cnake;
	while(last->prev != NULL){
		last = last->prev;
	}

	if(flag){
		last->prev = k;
		k->next = last;
	}

	while(last->next != NULL){
		last->x = last->next->x;
		last->y = last->next->y;
		last = last->next;
	}
	

	cnake->x += delta.dx;
	cnake->x = check(cnake->x, mx);
	cnake->y += delta.dy;
	cnake->y = check(cnake->y, my);

	show_snake(cnake);
}
