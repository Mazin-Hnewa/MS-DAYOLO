#include "grl_layer.h"
#include "utils.h"
#include "dark_cuda.h"
#include "blas.h"
#include <stdio.h>

layer make_grl_layer(int batch, float grl_weight, int w, int h, int c)
{

    layer l = { (LAYER_TYPE)0 };
    l.type = GRL;
    l.batch = batch;
    fprintf(stderr, "grl  weight = %.2f    ",grl_weight);
    l.grl_weight=grl_weight;
    l.w = l.out_w = w;
    l.h = l.out_h = h;
    l.c = l.out_c = c;
    l.outputs = w*h*c;
    l.inputs = l.outputs;


    l.delta = (float*)xcalloc(l.outputs  * batch, sizeof(float));
    l.output = (float*)xcalloc(l.outputs  * batch, sizeof(float));

    l.forward = forward_grl_layer;
    l.backward = backward_grl_layer;

    #ifdef GPU
    l.delta_gpu =  cuda_make_array(l.delta, l.outputs *batch);
    l.output_gpu = cuda_make_array(l.output, l.outputs *batch);

    l.forward_gpu = forward_grl_layer_gpu;
    l.backward_gpu = backward_grl_layer_gpu;

    #endif
    return l;
}

void forward_grl_layer(layer l, network_state state)
{
  int size=l.batch * l.outputs;
 axpy_cpu(size, 1 , state.input, 1,l.output, 1);
}

void backward_grl_layer(const layer l, network_state state)
{   /*int N=l.outputs;
  int i,j;
   float *X, *Y;
   for(j = 0; j < l.batch; ++j)
   { X=l.delta+j*N;  Y=state.delta+j*N;
   for(i = 0; i < N; ++i) Y[i] =-1*l.grl_weight * X[i];}*/
   int size=l.batch * l.outputs;
  axpy_cpu(size, -1*l.grl_weight , l.delta, 1, state.delta, 1);
  //axpy_cpu(size, 1 , l.delta, 1, state.delta, 1);

}

void resize_grl_layer(layer *l, int w, int h)
{
l->w = w;
l->h = h;
l->out_w = w ;
l->out_h = h;
l->outputs = w*h*l->out_c;
l->inputs = l->outputs;
l->delta = (float*)xrealloc(l->delta, l->outputs * l->batch * sizeof(float));
l->output = (float*)xrealloc(l->output, l->outputs * l->batch * sizeof(float));

#ifdef GPU
    cuda_free(l->output_gpu);
    cuda_free(l->delta_gpu);
    l->output_gpu  = cuda_make_array(l->output, l->outputs*l->batch);
    l->delta_gpu   = cuda_make_array(l->delta,  l->outputs*l->batch);
#endif
  }

#ifdef GPU
void forward_grl_layer_gpu(const layer l, network_state state)
{  int size=l.batch * l.outputs;
 simple_copy_ongpu(size, state.input, l.output_gpu);
}

void backward_grl_layer_gpu(const layer l, network_state state)
{int size=l.batch * l.outputs;
  axpy_ongpu(size, -1*l.grl_weight , l.delta_gpu, 1, state.delta, 1);

  // float min_input=100000000000, max_input=-100000000000;
  // float * state_delta= (float*)xcalloc(size, sizeof(float));
  // cuda_pull_array(l.delta_gpu, state_delta, size);
  //   for(int j = 0; j < size; ++j){
  //     if (state_delta[j]>max_input) max_input=state_delta[j];
  //     if (state_delta[j]<min_input) min_input=state_delta[j];
  //   }
  // free(state_delta);
  //  printf(" grl deltal : %f  %f     \n", max_input,min_input);


}
#endif
