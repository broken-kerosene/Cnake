#ifndef MY_SNAKE
#define MY_SNAKE

struct my_snake {
	int x;
	int y;
	char elem;
	struct my_snake *prev, *next;
};

typedef struct __delta{
	int dx;
	int dy;
} move_dir;

int take_rand(int num);
void clear_snake(struct my_snake *cnake);
void move_snake(struct my_snake *cnake, int mx, int my, move_dir delta, int *r_x, int *r_y);

#endif
