#include "dc_layer.h"
#include "utils.h"
#include "dark_cuda.h"
#include "blas.h"
#include <stdio.h>
#include <math.h>

layer make_dc_layer(int batch, float grl_weight, int w, int h)
{

    layer l = { (LAYER_TYPE)0 };
    l.type = DC;
    l.batch = batch;
    fprintf(stderr, "domain_classifier  weight = %.2f      ",grl_weight);
    l.grl_weight=grl_weight;
    l.w = l.out_w = w;
    l.h = l.out_h = h;
    l.outputs = w*h;
    l.inputs = l.outputs;

    l.da_loss = (float*)xcalloc(2, sizeof(float));

    l.delta = (float*)xcalloc(l.outputs  * batch, sizeof(float));
    l.output = (float*)xcalloc(l.outputs  * batch, sizeof(float));
    l.d_truth = (int*)xcalloc(l.outputs  * batch, sizeof(int));
    for (int i=0;i<l.outputs * batch/2;++i) l.d_truth[i]=1;
    for (int i=l.outputs * batch/2;i<l.outputs * batch;++i) l.d_truth[i]=0;

    l.forward = forward_dc_layer;
    l.backward = backward_dc_layer;

    #ifdef GPU
    l.delta_gpu =  cuda_make_array(l.delta, l.outputs *batch);
    l.output_gpu = cuda_make_array(l.output, l.outputs *batch);

    l.forward_gpu = forward_dc_layer_gpu;
    l.backward_gpu = backward_dc_layer_gpu;

    #endif
    return l;
}

void forward_dc_layer(layer l, network_state state)
{  int size=l.batch * l.outputs;
  memset(l.delta, 0, size * sizeof(float));
#ifndef GPU
memcpy(l.output, state.input, size * sizeof(float));
activate_array(l.output, size, LOGISTIC);
#endif
int i,q=0;
float x,loss=0,w=0;

for (i = 0; i < size; ++i)
{  //x=(l.d_truth[i]*log(l.output[i]))+((1-l.d_truth[i])*log(1-l.output[i]));
  if (l.d_truth[i]==1) x = log(l.output[i]);
  else if (l.d_truth[i]==0) x = log(1-l.output[i]);
  else printf("error error error error error  \n");
  if (x>-100.0){loss+=-x; q+=1;}
  else w+=1;
  l.delta[i]=(l.d_truth[i]-l.output[i])/size;
}
if (q>0) loss/=q;
l.da_loss[0]=loss;
l.da_loss[1]=w/size;
}

void backward_dc_layer(const layer l, network_state state)
{
  int size=l.batch * l.outputs;int i;
  for (i = 0; i < 15; ++i) printf(" %f \t %f \n",l.delta[i],state.delta[i]);
   axpy_cpu(size, l.grl_weight, l.delta, 1, state.delta, 1);
   for (i = 0; i < 15; ++i) printf(" %f \t %f \n",l.delta[i],state.delta[i]);

}

void resize_dc_layer(layer *l, int w, int h)
{
l->w = w;
l->h = h;
l->out_w = w ;
l->out_h = h;
l->outputs = w*h;
int size=l->outputs * l->batch;
l->inputs = l->outputs;
l->output = (float*)xrealloc(l->output, size * sizeof(float));
l->delta = (float*)xrealloc(l->delta, size * sizeof(float));
l->d_truth = (float*)xrealloc(l->d_truth, size * sizeof(float));
for (int i=0;i<size/2;++i) l->d_truth[i]=1;
for (int i=size/2;i<size;++i) l->d_truth[i]=0;

#ifdef GPU
    cuda_free(l->output_gpu);
    cuda_free(l->delta_gpu);
    l->output_gpu  = cuda_make_array(l->output, l->outputs*l->batch);
    l->delta_gpu   = cuda_make_array(l->delta,  l->outputs*l->batch);
#endif

  }

#ifdef GPU
void forward_dc_layer_gpu(layer l, network_state state)
{
  int size=l.batch * l.outputs;
 simple_copy_ongpu(size, state.input, l.output_gpu);
 activate_array_ongpu(l.output_gpu, size, LOGISTIC);
 cuda_pull_array(l.output_gpu, l.output, size);
 forward_dc_layer(l,state);
 cuda_push_array(l.delta_gpu, l.delta, size);
}

void backward_dc_layer_gpu(const layer l, network_state state)
{
  axpy_ongpu(l.batch * l.outputs, l.grl_weight , l.delta_gpu, 1, state.delta, 1);
}
#endif
