#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>

// Image dimensions
#define WIDTH 800
#define HEIGHT 600

// Maximum number of iterations
#define MAX_ITER 1000

// Mandelbrot parameters (adjustable zoom levels)
#define MIN_X -2.0
#define MAX_X  1.0
#define MIN_Y -1.25
#define MAX_Y  1.25

// Struct for passing arguments to threads
typedef struct {
    int start_row;
    int end_row;
    unsigned char* image;
} thread_data_t;

// Function to calculate the Mandelbrot iteration count for a pixel
int mandelbrot(double real, double imag) {
    double r = real;
    double i = imag;
    int n;
    for (n = 0; n < MAX_ITER; n++) {
        double r2 = r * r;
        double i2 = i * i;
        if (r2 + i2 > 4) break;
        double temp_r = r2 - i2 + real;
        i = 2 * r * i + imag;
        r = temp_r;
    }
    return n;
}

// Function to generate the color based on the number of iterations
void get_color(int iterations, unsigned char* color) {
    if (iterations == MAX_ITER) {
        color[0] = 0;    // R (Red)
        color[1] = 0;    // G (Green)
        color[2] = 0;    // B (Blue)
    } else {
        // Color gradient (more iterations = more red)
        color[0] = (iterations % 256);  // Red
        color[1] = (iterations * 2) % 256;  // Green
        color[2] = (iterations * 5) % 256;  // Blue
    }
}

// Function to compute a part of the Mandelbrot set
void* compute_mandelbrot(void* arg) {
    thread_data_t* data = (thread_data_t*) arg;
    int start_row = data->start_row;
    int end_row = data->end_row;
    unsigned char* image = data->image;

    double scale_x = (MAX_X - MIN_X) / WIDTH;
    double scale_y = (MAX_Y - MIN_Y) / HEIGHT;

    for (int y = start_row; y < end_row; y++) {
        for (int x = 0; x < WIDTH; x++) {
            double real = MIN_X + x * scale_x;
            double imag = MIN_Y + y * scale_y;
            int iterations = mandelbrot(real, imag);

            unsigned char color[3];
            get_color(iterations, color);  // Get color based on iteration count

            image[(y * WIDTH + x) * 3 + 0] = color[0]; // R
            image[(y * WIDTH + x) * 3 + 1] = color[1]; // G
            image[(y * WIDTH + x) * 3 + 2] = color[2]; // B
        }
    }
    return NULL;
}

// Function to write the PPM file
void write_ppm(const char* filename, unsigned char* image) {
    FILE* fp = fopen(filename, "wb");
    if (!fp) {
        perror("Error opening file for writing");
        exit(1);
    }

    // Write PPM header
    fprintf(fp, "P6\n%d %d\n255\n", WIDTH, HEIGHT);

    // Write pixel data
    fwrite(image, 3, WIDTH * HEIGHT, fp);

    fclose(fp);
}

int main() {
    pthread_t threads[8];
    unsigned char* image = malloc(3 * WIDTH * HEIGHT);
    int rows_per_thread = HEIGHT / 8;

    // Create threads to compute Mandelbrot set
    for (int i = 0; i < 8; i++) {
        thread_data_t* data = malloc(sizeof(thread_data_t));
        data->start_row = i * rows_per_thread;
        data->end_row = (i + 1) * rows_per_thread;
        data->image = image;

        if (pthread_create(&threads[i], NULL, compute_mandelbrot, data) != 0) {
            perror("Error creating thread");
            exit(1);
        }
    }

    // Join all threads
    for (int i = 0; i < 8; i++) {
        pthread_join(threads[i], NULL);
    }

    // Write the final image to a PPM file
    write_ppm("mandelbrot_color.ppm", image);

    free(image);
    return 0;
}
