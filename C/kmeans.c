#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define ERROR_MESSAGE "An Error Has Occurred"

// Function Prototypes


struct cord {
    double value;
    struct cord* next;
};

struct vector {
    struct vector* next;
    struct cord* cords;
};

typedef struct vector vector;
typedef struct cord cord;

int validate_K(char* K, int N){
    char* end;
    int k = strtol(K, &end, 10);
    return (*end == '\0' && N > k && k > 1);
}

int validate_iter(char* iter){
    char* end;
    int num_iter = strtol(iter, &end, 10);
    return (*end == '\0' && 1000 > num_iter && num_iter > 1);
}

void print_vector(cord* cord){
    while(cord != NULL){
        printf("%.4f", cord->value);
        cord = cord->next;
        if(cord != NULL){
            printf(",");
        }
    }
    printf("\n");
}

cord* line_to_cord(char* line, int d){
    char* ptr;
    ptr = line;
    struct cord* head_cord;
    head_cord = malloc(sizeof(struct cord));
    head_cord->next = NULL;
    struct cord* curr_cord;
    curr_cord = head_cord;
    for (size_t i = 0; i < d; i++)
    {
        while (*ptr != ',' && *ptr != '\n')
        {
            ptr++;
        }
        struct cord* new_cord;
        new_cord = malloc(sizeof(struct cord));
        new_cord->next = NULL;
        new_cord->value = strtold(line, &ptr);
        ptr++;
        line = ptr;
        curr_cord->next = new_cord;
        curr_cord = new_cord;
    }
    curr_cord = head_cord->next;
    free(head_cord);
    return curr_cord;
}


vector* file_to_vectors() {
    size_t bufsize = 0;
    int is_end_of_file;
    char *line =NULL;
    is_end_of_file = getline(&line, &bufsize, stdin);
    if(is_end_of_file == -1){
        return NULL;
    }
    int d = 1;
    char* ptr = line;
    // find the vector's number of dimensions
    while(*ptr != '\n'){
        if(*ptr == ','){
            d++;
        }
        ptr++;
    }
    struct vector* head_vector;
    head_vector = malloc(sizeof(struct vector));
    head_vector->next = NULL;
    struct vector* curr_vector;
    curr_vector = head_vector;
    do
    {
        struct vector* new_vector;
        new_vector = malloc(sizeof(struct vector));
        curr_vector->next = new_vector;
        curr_vector = new_vector;
        struct cord* curr_cord = line_to_cord(line, d);
        curr_vector->cords = curr_cord;
        curr_vector->next = NULL;

    }while ((is_end_of_file = getline(&line, &bufsize, stdin)) != EOF);
    curr_vector = head_vector->next;
    free(head_vector);
    return curr_vector;
}

int main(int argc, char **argv){
    char* K = argv[1];
    char* iter = argv[2];
    struct vector* vectors = file_to_vectors();
    while (vectors != NULL){
        print_vector(vectors->cords);
        vectors = vectors->next;
    }
}