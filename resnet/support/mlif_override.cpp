#include "quantize.h"
#include "printing.h"
#include "exit.h"
#include <cstring>
#include <unistd.h>

#include  <stdio.h>

#define MAX_LINE 100


extern "C" {
int mlif_process_input(const void *, size_t, void *, size_t);
int mlif_process_output(void *, size_t, const void *, size_t);
}


int mlif_process_input(const void *in_data, size_t in_size, void *model_input_ptr, size_t model_input_sz)
{
    if (in_size != model_input_sz)
    {
        DBGPRINTF("MLIF: Wrong input size!\n");
        return EXIT_MLIF_INVALID_SIZE;
    }
    // char line[MAX_LINE];
    // char *result;

    // printf("Please enter a string:\n");
    // if ((result = gets(line)) != NULL)
    //   printf("The string is: %s\n", line);
    // else if (ferror(stdin))
    //   perror("Error");
    char ch;
    int cnt = 0;
    while(read(STDIN_FILENO, &ch, 1) > 0) {
        // printf("c=%c / %d\n", ch, ch);
        ((char*)model_input_ptr)[cnt] = ch;
        cnt++;
        if (cnt == in_size) {
            break;
        }
    }
    // printf("cnt=%d in_size=%lu\n", cnt, in_size);
    if (cnt < in_size) {
        return EXIT_MLIF_INVALID_SIZE;
    }

    // memcpy(model_input_ptr, in_data, in_size);
    return 0;
}

int mlif_process_output(void *model_output_ptr, size_t model_output_sz, const void *expected_out_data, size_t expected_out_size)
{
    if (model_output_sz != 10)
    {
        DBGPRINTF("MLIF: Wrong output size!\n");
        return EXIT_MLIF_INVALID_SIZE;
    }

    float out_scale = 0.00390625;
    int out_zeropt = -128;

    float results[10];
    int prediction = 0;
    write(1,"-?-",3);
    write(1,model_output_ptr,10);
    write(1,"-!-",3);
    // printf("---END---\n");
    for (int i = 0; i < 10; i++)
    {
        int8_t data = ((int8_t*)model_output_ptr)[i];
        // printf("output_0[%d]=%d / %u / %c / %x\n", i, data, data, data, data);
        results[i] = DequantizeInt8ToFloat(((int8_t*)model_output_ptr)[i], out_scale, out_zeropt);
        DBGPRINTF("Category %i: %.9g\n", i, results[i]);

        if (results[i] >= results[prediction])
        {
            prediction = i;
        }
    }
    DBGPRINTF("Predicted category: %i\n", prediction);


    // for (int i = 0; i < 10; i++)
    // {
    //     float expected = ((float*)expected_out_data)[i];
    //     if (results[i] != expected)
    //     {
    //         DBGPRINTF("MLIF: Wrong output in category %i! Expected %.9g\n", i, expected);
    //         return EXIT_MLIF_MISSMATCH;
    //     }
    // }
    return 0;
}
