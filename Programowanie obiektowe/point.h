typedef struct point point_t;

point_t* point_new(int x, int y);
int point_get_x(point_t *p);
int point_get_y(point_t *p);
void point_free(point_t *p);
