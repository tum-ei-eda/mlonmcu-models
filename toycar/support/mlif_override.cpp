#include "quantize.h"
#include "printing.h"
#include "exit.h"


extern "C" {
int mlif_process_input(const void *, size_t, void *, size_t);
int mlif_process_output(void *, size_t, const void *, size_t);
}

const float *current_input = 0;


int mlif_process_input(const void *in_data, size_t in_size, void *model_input_ptr, size_t model_input_sz)
{
    float in_scale = 0.39101523160934448;
    int in_zeropt = 89;

    if (in_size / 4 != model_input_sz)
    {
        DBGPRINTF("MLIF: Wrong input size!\n");
        return EXIT_MLIF_INVALID_SIZE;
    }

    for (int i = 0; i < model_input_sz; i++)
    {
        ((int8_t*)model_input_ptr)[i] = QuantizeFloatToInt8(((float*)in_data)[i], in_scale, in_zeropt);
    }

    current_input = (const float*)in_data;
    return 0;
}

int mlif_process_output(void *model_output_ptr, size_t model_output_sz, const void *expected_out_data, size_t expected_out_size)
{
    if (model_output_sz != 640)
    {
        DBGPRINTF("MLIF: Wrong output size!\n");
        return EXIT_MLIF_INVALID_SIZE;
    }

    float out_scale = 0.36449846625328064;
    int out_zeropt = 96;

    float diffsum = 0;
    for (int i = 0; i < 640; i++)
    {
        float converted = DequantizeInt8ToFloat(((int8_t*)model_output_ptr)[i], out_scale, out_zeropt);
        float diff = converted - current_input[i];
        diffsum += diff * diff;
    }
    diffsum /= 640;

    DBGPRINTF("Toycar final result: %f\n", diffsum);

    float expected = *(float*)expected_out_data;
    if (diffsum != expected)
    {
        DBGPRINTF("MLIF: Wrong output! Expected %f\n", expected);
        return EXIT_MLIF_MISSMATCH;
    }
    return 0;
}
