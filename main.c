#include <curses.h>
#include <stdlib.h>
#include <time.h>
#include "func.h"

const char message[] = "Cnake @@@@@@o";
enum { key_escape = 27 };



int main()
{
	move_dir delta;	
	delta.dx = 0;
	delta.dy = 0;

	struct my_snake *cnake = malloc(sizeof(struct my_snake));
	cnake->x = 0;
	cnake->y = 0;
	cnake->elem = 'O';
	cnake->next = NULL;
	cnake->prev = NULL;

	int row, col, mx, my, key, r_x, r_y;
	initscr();
	cbreak();
	timeout(300);
	keypad(stdscr,1);
	noecho();
	getmaxyx(stdscr, row, col);
	mx = col-sizeof(message)+1;
	my = row-1;

	srand(time(NULL));
	r_x = take_rand(mx);
	r_y = take_rand(my);
	move(r_y, r_x);
	addch('#');

	curs_set(0);
	while((key = getch()) != key_escape){
		switch(key){
				case KEY_UP:
					delta.dx = 0;
					delta.dy = -1;
					move_snake(cnake, mx, my, delta, &r_x, &r_y);
					break;
				case KEY_DOWN:
					delta.dx = 0;
					delta.dy = 1;
					move_snake(cnake, mx, my, delta, &r_x, &r_y);
					break;
				case KEY_LEFT:
					delta.dx = -1;
					delta.dy = 0;
					move_snake(cnake, mx, my, delta, &r_x, &r_y);
					break;
				case KEY_RIGHT:
					delta.dx = 1;
					delta.dy = 0;
					move_snake(cnake, mx, my, delta, &r_x, &r_y);
					break;	
				case ERR:
					move_snake(cnake, mx, my, delta, &r_x, &r_y);
					break;
		}
	}
	clear_snake(cnake); 
	cnake = NULL;
	endwin();
	return 0;
}
