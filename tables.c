#include <stdio.h>
#include <math.h>

#define TABLE_SIZE 10000
#define TABLE_MIN -100.0f
#define TABLE_MAX 100.0f
#define GELU_SCALING_FACTOR sqrtf(2.0f / M_PI)

void generate_gelu_table(float gelu_table[TABLE_SIZE]) {
    float step = (TABLE_MAX - TABLE_MIN) / (TABLE_SIZE - 1);
    for (int i = 0; i < TABLE_SIZE; i++) {
        float x = TABLE_MIN + i * step;
        float cube = 0.044715f * x * x * x;
        float tanh_arg = GELU_SCALING_FACTOR * (x + cube);
        float tanh_out = tanhf(tanh_arg);
        float coshf_out = coshf(tanh_arg);
        float sech_out = 1.0f / (coshf_out * coshf_out);
        float local_grad = 0.5f * (1.0f + tanh_out) + x * 0.5f * sech_out * GELU_SCALING_FACTOR * (1.0f + 3.0f * 0.044715f * x * x);
        gelu_table[i] = local_grad;
    }
}

int main() {
    float gelu_table[TABLE_SIZE];
    generate_gelu_table(gelu_table);

    FILE* gelu_file = fopen("gelu_table.bin", "wb");
    fwrite(gelu_table, sizeof(float), TABLE_SIZE, gelu_file);
    fclose(gelu_file);

    return 0;
}
