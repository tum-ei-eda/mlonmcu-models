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

    mlif_data_config cfg;

    size_t shape[4] = {1, 32, 32, 3};
    cfg.nbatch = 1;                 // number of batches
    cfg.nsample = 1;                // number of total inputs/outputs
    cfg.ndim = 4;                   // dimension of a single input, in this case is {1, 3}
    cfg.shape = shape;              // data shape for each input is 1x3
    cfg.dtype = MLIF_DTYPE_INT8;    // dtype int8
    cfg.order = MLIF_C_ORDER;       // row first

    void *data = mlif_input_ptr(0);

    MLIF_IO_STATUS status;

    status = mlifio_from_file(MLIF_FILE_BIN, "in.bin", &cfg, data, 0);
    printf("status=%d\n", status);
    status = mlifio_from_file(MLIF_FILE_NPY, "in.npy", &cfg, data, 0);
    printf("status=%d\n", status);
    // status = mlifio_from_stdin(MLIF_STDIO_BIN, &cfg, data);
    // printf("status=%d\n", status);
    // status = mlifio_from_stdin(MLIF_STDIO_PLAIN, &cfg, data);
    // printf("status=%d\n", status);


    return 0;
}

int mlif_process_outputs(size_t batch_idx)
{
    mlonmcu_printf("MLIF: process outputs (resnet)\n");

    mlif_data_config cfg;

    size_t shape[2] = {1, 10};
    cfg.nbatch = 1;                 // number of batches
    cfg.nsample = 1;                // number of total inputs/outputs
    cfg.ndim = 2;                   // dimension of a single input, in this case is {1, 3}
    cfg.shape = shape;              // data shape for each input is 1x3
    cfg.dtype = MLIF_DTYPE_INT8;    // dtype int8
    cfg.order = MLIF_C_ORDER;       // row first

    int8_t *data = (int8_t*)mlif_output_ptr(0);

    MLIF_IO_STATUS status;

    status = mlifio_to_file(MLIF_FILE_BIN, "out.npy", &cfg, data);
    printf("status=%d\n", status);
    status = mlifio_to_file(MLIF_FILE_NPY, "out.bin", &cfg, data);
    printf("status=%d\n", status);
    status = mlifio_to_stdout(MLIF_STDIO_BIN, &cfg, data, batch_idx * 1 + 0);
    printf("status=%d\n", status);
    status = mlifio_to_stdout(MLIF_STDIO_PLAIN, &cfg, data, batch_idx * 1 + 0);
    printf("status=%d\n", status);

    return 0;
}
