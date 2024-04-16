#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// Function to sort the array in ascending order
void sort_array(float *array, int *num_elements) {
    int i, j;
    int swapped;
    float temp;
    for (i = 0; i < *num_elements - 1; i++) {
        swapped = 0;
        for (j = 0; j < *num_elements - i - 1; j++) {
            if ((array)[j] > (array)[j + 1]) {
                temp = (array)[j];
                (array)[j] = (array)[j + 1];
                (array)[j + 1] = temp;
                swapped = 1;
            }
        }
        if (!swapped) // If the array is already sorted, break
            break;
    }
}

// Function to double the capacity of the array
float *expand_array(float *small_array, int *num_elements, int *array_size) {
    float *large_array;
    large_array = (float *)malloc(2 * (*array_size * sizeof(float)));
    if (large_array == NULL) {
        printf("The Memory allocation is failed\n");
        exit(1);
    }
    for (int i = 0; i < *num_elements; i++) {
        large_array[i] = small_array[i];
    }
    *array_size = *array_size * 2;
    free(small_array);
    return large_array;
}

// Function to calculate the mean of the array
double calculate_mean(float *array, int *num_elements) {
    double mean;
    double sum = 0;
    for (int i = 0; i < *num_elements; i++) {
        sum = sum + array[i];
    }
    mean = sum / (*num_elements);
    return mean;
}

// Function to calculate the geometric mean of the array
float calculate_geometric_mean(float *array, int *num_elements) {
    float geometric_mean;
    double product = 1;
    for (int i = 0; i < *num_elements; i++) {
        product = product * array[i];
    }
    geometric_mean = pow(product, 1.0 / (*num_elements));
    return geometric_mean;
}

// Function to calculate the harmonic mean of the array
float calculate_harmonic_mean(float *array, int *num_elements) {
    float harmonic_mean;
    double sum_reciprocal = 0;
    for (int i = 0; i < *num_elements; i++) {
        sum_reciprocal = sum_reciprocal + 1 / array[i];
    }
    harmonic_mean = *num_elements / sum_reciprocal;
    return harmonic_mean;
}

// Function to calculate the median of the array
float calculate_median(float *array, int *num_elements) {
    float median;
    if (*num_elements % 2 == 1) {
        median = array[(*num_elements - 1) / 2];
    } else
        median = (array[(*num_elements / 2) - 1] + array[(*num_elements / 2)]) / 2;
    return median;
}

// Function to calculate the mode of the array
int calculate_mode(float *array, int *num_elements, float **modes) {
    int max_count = 0;
    int mode_count = 0;
    *modes = (float *)malloc(*num_elements * sizeof(float));
    if (*modes == NULL) {
        printf("The Memory allocation is failed\n");
        exit(1);
    }

    // Count occurrences of each number
    int *counts = (int *)calloc(*num_elements, sizeof(int));
    if (counts == NULL) {
        printf("The Memory allocation is failed\n");
        exit(1);
    }

    for (int i = 0; i < *num_elements; ++i) {
        counts[i] = 1; // Initialize count to 1 for each number
        for (int j = i + 1; j < *num_elements; ++j) {
            if (array[j] == array[i])
                counts[i]++;
        }
    }

    // Find max count
    for (int i = 0; i < *num_elements; ++i) {
        if (counts[i] > max_count)
            max_count = counts[i];
    }

    // If max count is 1, indicating no repeated value
    if (max_count == 1) {
        free(counts);
        return 0;
    }

    // Find modes
    for (int i = 0; i < *num_elements; ++i) {
        if (counts[i] == max_count) {
            (*modes)[mode_count++] = array[i];
        }
    }

    free(counts);
    return mode_count;
}

// Function to calculate the standard deviation of the array
float calculate_stddev(float *array, int *num_elements, double *mean) {
    float stddev;
    double sumdev = 0;
    for (int i = 0; i < *num_elements; i++) {
        sumdev = sumdev + pow((array[i] - *mean), 2);
    }
    stddev = sqrt(sumdev / (*num_elements));
    return stddev;
}

// The main function
int main(int argc, char **argv) {
    if (argc != 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        return -1;
    }
    char *filename = argv[1];
    int array_size = 20;
    int num_elements = 0;
    float *num_array;

    num_array = (float *)malloc(array_size * sizeof(float));
    if (num_array == NULL) {
        printf("The Memory allocation is failed\n");
        return -1;
    }

    // Reading the file and storing into an array
    char buffer[100];
    int ret;
    FILE *reads;
    reads = fopen(filename, "r");
    if (reads == NULL) {
        printf("Error! Run the program again with a proper filename\n");
        free(num_array);
        return -1;
    } else {
        while (fgets(buffer, sizeof(buffer), reads) != NULL) {
            if (buffer[0] != '\n')  // if the line is not a blank line
            {
                ret = sscanf(buffer, "%f", &num_array[num_elements]);
                num_elements++;
                if (num_elements == array_size && !feof(reads)) {
                    num_array = expand_array(num_array, &num_elements, &array_size);
                }
            } else {
                continue;
            }
        }
    }

    // Sort the array
    sort_array(num_array, &num_elements);

    double mean, gMean, hMean;
    float median, stddev;
    float *modes;
    int mode_count;

    // Calculating the mean
    mean = calculate_mean(num_array, &num_elements);

    // Calculating the geometric mean
    gMean = calculate_geometric_mean(num_array, &num_elements);

    // Calculating the harmonic mean
    hMean = calculate_harmonic_mean(num_array, &num_elements);

    // Calculating the median
    median = calculate_median(num_array, &num_elements);

    // Calculating the mode
    mode_count = calculate_mode(num_array, &num_elements, &modes);

    // Calculating the standard deviation
    stddev = calculate_stddev(num_array, &num_elements, &mean);

    // Printing the statistics
    printf("\n          DATA STATISTICS\n");
    printf("-------------------------------------\n");
    printf("   Number of elements:%15d\n", num_elements);
    printf("                 Mean:%15.3f\n", mean);
    printf("       Geometric Mean:%15.3f\n", gMean);
    printf("        Harmonic Mean:%15.3f\n", hMean);
    printf("               Median:%15.3f\n", median);
    if (mode_count > 0) {
        printf("                 Mode:");
        for (int i = 0; i < mode_count; ++i) {
            printf("%15.3f", modes[i]);
        }
        printf("\n");
        free(modes);
    } else {
        printf("                 Mode: No mode found\n");
    }
    printf("   Standard Deviation:%15.3f\n", stddev);
    printf("Unused array capacity:%15d\n", (array_size - num_elements));

    // Deallocating the space for the array
    free(num_array);

    return 0;
}
