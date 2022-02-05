#ifndef GRL_LAYER_H
#define GRL_LAYER_H
#include "network.h"
#include "layer.h"

#ifdef __cplusplus
extern "C" {
#endif

layer make_grl_layer(int batch, float grl_weight,int w, int h, int c);
void forward_grl_layer(layer l, network_state state);
void backward_grl_layer(const layer l, network_state state);
void resize_grl_layer(layer *l, int w, int h);

#ifdef GPU
void forward_grl_layer_gpu(const layer l, network_state state);
void backward_grl_layer_gpu(const layer l, network_state state);
#endif

#ifdef __cplusplus
}
#endif
#endif
