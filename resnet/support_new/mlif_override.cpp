#include "quantize.h"
#include "printing.h"
#include "exit.h"
#include "ml_interface.h"
#include "mlifio.h"
#include <cstring>
#include <unistd.h>
#include <stdint.h>

#include  <stdio.h>

#define MAX_LINE 100


int mlif_process_inputs(size_t batch_idx, bool *new_)
{
    mlonmcu_printf("MLIF: process inputs (resnet)\n");
    *new_ = true;
    return 0;
}

int mlif_process_outputs(size_t batch_idx)
{
    mlonmcu_printf("MLIF: process outputs (resnet)\n");

    float out_scale = 0.00390625;
    int out_zeropt = -128;

    float results[10];
    int prediction = 0;
    int8_t *model_output_ptr = (int8_t*)mlif_output_ptr(0);
    for (int i = 0; i < 10; i++)
    {
        results[i] = DequantizeInt8ToFloat(model_output_ptr[i], out_scale, out_zeropt);
        mlonmcu_printf("Category %i: %.9g\n", i, results[i]);

        if (results[i] >= results[prediction])
        {
            prediction = i;
        }
    }
    mlonmcu_printf("Predicted category: %i\n", prediction);


    return 0;
}
