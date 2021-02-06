#include"../inc/main_inc.h"


int main(void)
{
    mat_t matrix = {.data = NULL, .size = 0};

    int max_way = 0;
    int start_place = 0;

    int rc = read_data(&matrix, &max_way, &start_place);

    if (rc != 0)
    {
        return rc;
    }

    no_roads_t *clear = NULL;

    find_empty_roads(matrix, &clear);

    find_ways_combinations(matrix, clear, max_way, start_place);

    free(clear);
    free_matrix(matrix);

    system("dot -Tpng in.dot -o in.png");
    system("dot -Tpng out.dot -o out.png");

    return 0;
}