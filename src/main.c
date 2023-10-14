#include "../inc/pathfinder.h"
#include <stdio.h>

int main(int argc, const char* argv[]) {
    if(argc != 2) {
        mx_handle_err(INVALID_ARGS, NULL);
    }

    const char *filename = argv[1];
    int fd, num_of_islands = 0;
    t_list *bridges_list = NULL, *islands_list = NULL;

    fd = open(filename, O_RDONLY);
    if(fd < 0) {
        mx_handle_err(INVALID_FILE, (void*)filename);
    }

    if(mx_file_size(fd) == 0) {
        mx_handle_err(EMPTY_FILE, (void*)filename);
    }
    
    num_of_islands = read_file(filename, &bridges_list);

    if(mx_check_duplicates(bridges_list)) {
        mx_handle_err(DUPLICATE_BRIDGES, NULL);
    }

    if(check_invalid_sum(bridges_list)) {
        mx_handle_err(INVALID_SUM_OF_BRIDGES, NULL);
    }

    islands_list = mx_create_islands_list(bridges_list); 

    if(mx_list_size(islands_list) != num_of_islands) {
        mx_handle_err(INVALID_NUM_OF_ISLANDS, NULL);
    }

    int **matrix = mx_create_adjacency_matrix(bridges_list, islands_list);

    for(int i = 0; i < num_of_islands; i++) {
        for(int j = 0; j < num_of_islands; j++) {
            if(matrix[i][j] == INT_MAX) {
                printf("%s\t", "inf");
            }
            else printf("%d\t", matrix[i][j]);
        }
        printf("\n");
    }
    printf("\n");

    // mx_floyd_warshall(matrix, num_of_islands);

    // for(int i = 0; i < num_of_islands; i++) {
    //     for(int j = 0; j < num_of_islands; j++) {
    //         if(matrix[i][j] == INT_MAX) {
    //             printf("%s\t", "inf");
    //         }
    //         else printf("%d\t", matrix[i][j]);
    //     }
    //     printf("\n\n");
    // }

    for(int i = 0; i < num_of_islands; i++) {
        mx_dijkstra(matrix, num_of_islands, i, islands_list);
    }

    return EXIT_SUCCESS;
}

