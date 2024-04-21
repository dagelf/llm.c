#include <stdio.h>
#include <math.h>

#define TABLE_SIZE 10240
#define TABLE_RANGE 10000.0f
#define GELU_SCALING_FACTOR sqrtf(2.0f / M_PI)

void generate_lookup_tables(float tanh_table[TABLE_SIZE], float cosh_table[TABLE_SIZE]) {
    float step = TABLE_RANGE / (TABLE_SIZE - 1);
    for (int i = 0; i < TABLE_SIZE; i++) {
        float x = -TABLE_RANGE / 2.0f + i * step;
        tanh_table[i] = tanhf(x / GELU_SCALING_FACTOR);
        cosh_table[i] = 1.0f / coshf(x / GELU_SCALING_FACTOR);
    }
}

int main() {
    float tanh_table[TABLE_SIZE];
    float cosh_table[TABLE_SIZE];
    generate_lookup_tables(tanh_table, cosh_table);

    // Save the tables to files
    FILE* tanh_file = fopen("tanh_table.bin", "wb");
    fwrite(tanh_table, sizeof(float), TABLE_SIZE, tanh_file);
    fclose(tanh_file);

    FILE* cosh_file = fopen("cosh_table.bin", "wb");
    fwrite(cosh_table, sizeof(float), TABLE_SIZE, cosh_file);
    fclose(cosh_file);

    return 0;
}
