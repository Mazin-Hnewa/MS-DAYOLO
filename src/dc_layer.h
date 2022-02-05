#ifndef DC_LAYER_H
#define DC_LAYER_H
#include "network.h"
#include "layer.h"
#include <math.h>

#ifdef __cplusplus
extern "C" {
#endif

layer make_dc_layer(int batch,float grl_weight,int w, int h);
void forward_dc_layer(layer l, network_state state);
void backward_dc_layer(const layer l, network_state state);
void resize_dc_layer(layer *l, int w, int h);

#ifdef GPU
void forward_dc_layer_gpu(const layer l, network_state state);
void backward_dc_layer_gpu(const layer l, network_state state);
#endif

#ifdef __cplusplus
}
#endif
#endif
