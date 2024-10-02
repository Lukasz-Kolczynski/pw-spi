#include <stdio.h>
#include "line.h"
#include "point.h"

int main()
{
    point *p1 = point_new(10,20);
    point *p2 = point_new(30,40);

    line *l1 = line_new(p1, p2);

    printf("Długość linii: %f\n", line_get_length(l1));

    line_free(l1);
    point_free(p2);
    point_free(p1);
} 

point_t *point_new(int x, int y)
{
    point_t *p = malloc(sizeof(struct point));
    p->x = x;
    p->y = y;
    return p;
}

point_t *line_new(point *pl, point *p2)
{
    point_t *l = malloc(sizeof(struct line));
    l-> start = pl;
    l->end =  p2;
    return l;
}