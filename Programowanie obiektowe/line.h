#include "point.h"
typedef struct line line_t;

line_t* line_new(point_t *pl, point_t *p2);
void line_free(line_t *l);
point_t* line_get_start(line_t *l);
point_t* line_get_end(line_t *l);
double line_get_length(line_t *l);

