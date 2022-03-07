#include "quantize.h"
#include "printing.h"
#include "exit.h"
#include <cstring>


extern "C" {
void mlif_process_input(const void *, size_t, void *, size_t);
void mlif_process_output(void *, size_t, const void *, size_t);
}


void mlif_process_input(const void *in_data, size_t in_size, void *model_input_ptr, size_t model_input_sz)
{
    float in_scale = 0.0039215688593685627;
    int in_zeropt = -128;

    if (in_size / 4 != model_input_sz)
    {
        DBGPRINTF("MLIF: Wrong input size!\n");
        exit(EXIT_MLIF_INVALID_SIZE);
    }

    for (int i = 0; i < model_input_sz; i++)
    {
        ((int8_t*)model_input_ptr)[i] = QuantizeFloatToInt8(((float*)in_data)[i], in_scale, in_zeropt) - 128;
    }
}

void mlif_process_output(void *model_output_ptr, size_t model_output_sz, const void *expected_out_data, size_t expected_out_size)
{
    if (model_output_sz != 2)
    {
        DBGPRINTF("MLIF: Wrong output size!\n");
        exit(EXIT_MLIF_INVALID_SIZE);
    }

    float out_scale = 0.00390625;
    int out_zeropt = -128;

    float results[2];
    int prediction = 0;
    for (int i = 0; i < 2; i++)
    {
        results[i] = DequantizeInt8ToFloat(((int8_t*)model_output_ptr)[i], out_scale, out_zeropt);
        DBGPRINTF("Category %i: %.9g\n", i, results[i]);

        if (results[i] >= results[prediction])
        {
            prediction = i;
        }
    }
    DBGPRINTF("Predicted category: %i\n", prediction);


    for (int i = 0; i < 2; i++)
    {
        float expected = ((float*)expected_out_data)[i];
        if (results[i] != expected)
        {
            DBGPRINTF("MLIF: Wrong output in category %i! Expected %.9g\n", i, expected);
            exit(EXIT_MLIF_MISSMATCH);
        }
    }
}
