#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define ERROR_MESSAGE "An Error Has Occurred"

// Function Prototypes
int validate_K(char *K, int N);
int validate_iter(char *iter);
int validate_input_data(char *input_data);
double** file_to_vectors();
double** compute_centroids(int K, int iter, double **vectors, int num_vectors, int dim, double epsilon);
double* compute_new_centroid(double **group, int group_size, int dim);
double round_four_digits(double num);
void print_centroids(double **centroids, int K, int dim);



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

double** file_to_vectors() {
    size_t bufsize = 0;
    int c;
    char *line =NULL;
    c = getline(&line, &bufsize, stdin);
    int d = 1;
    char* ptr = line;
    // find the vector's number of dimensions
    while(*ptr != '\n'){
        if(*ptr == ','){
            d++;
        }
        ptr++;
    }
    do
    {
        char* vector = (char*)malloc(d*sizeof(char)+1);
        ptr = line;
        for(int i=0;i < d; i++){
            int count = 0;
            while(*ptr != ',' && *ptr != '\n'){
                count++;
                ptr++;
            }
            char* word = (char*)malloc(count*sizeof(char));
            for(int j=0; j < count; j++){
                word[j] = line[j];
            }
            //printf("%s", word);
            vector[i] = *word;
            if(*ptr == ','){
                line = ptr++;
            }
        }
        // printf("%s\n", vector);
    } while ((c = getline(&line, &bufsize, stdin)) != -1);
    

    // do
    // {
    //     double *vector = (double*)malloc(d*sizeof(double));
    //     for (int i = 0; i < d; i++)
    //     {
    //         double sign = 1;
    //         double full = 0;
    //         double fraction = 0;
    //         if(*line == '-'){
    //             sign = -1;
    //             line++;
    //         }
    //         while(*line != '.'){
    //             full = full * 10 + (*line - '0');
    //             line++;
    //         while (*line != ',' && *line != '\n')
    //         {
    //             fraction = fraction * 0.1 + (*line - '0');
    //             line++;
    //         }
    //         vector[i] = full + fraction * 0.1;
    //     }
        
    //     printf(".2f\n", vector);
        
    // }
        
    // } while ((c = getline(&line, &bufsize, stdin)) != -1);
    double** f;
    return f;
}

int main(int argc, char **argv){
    char* K = argv[1];
    char* iter = argv[2];
    printf("%s", iter);
    file_to_vectors();
}