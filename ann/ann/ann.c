#include "ann.h"

/* Creates and returns a new ann. */
ann_t *ann_create(int num_layers, int *layer_outputs)
{
  /**** PART 2 - QUESTION 1 ****/
  assert(num_layers >= 2);
  assert(layer_outputs);
  ann_t *ann = (ann_t *) malloc(sizeof(ann_t));
  if (!ann) return NULL;

  ann->input_layer = layer_create();
  if (layer_init(ann->input_layer, layer_outputs[0], NULL)) return NULL;

  layer_t *prev = ann->input_layer;
  for (int i = 1; i < num_layers; i++) {
      layer_t *layer = layer_create();
      if (layer_init(layer, layer_outputs[i], prev)) return NULL;
      prev->next = layer;
      layer->prev = prev;
      prev = layer;
  }
  ann->output_layer = prev;
  return ann;
  /* 4 MARKS */
}

/* Frees the space allocated to ann. */
void ann_free(ann_t *ann)
{
  /**** PART 2 - QUESTION 2 ****/
  if (!ann) return;
  layer_t *layer = ann->input_layer;
  while (layer) {
      layer_t *next = layer->next;
      layer_free(layer);
      layer = next;
  }
  free(ann);
  /* 2 MARKS */
}

/* Forward run of given ann with inputs. */
void ann_predict(ann_t const *ann, double const *inputs)
{
  /**** PART 2 - QUESTION 3 ****/
  assert(ann);
  assert(ann->input_layer);
  assert(ann->input_layer->outputs);
  for (int i = 0; i < ann->input_layer->num_outputs; i++) {
      ann->input_layer->outputs[i] = inputs[i];
  }
  layer_t *layer = ann->input_layer->next;
  while (layer) {
      layer_compute_outputs(layer);
      layer = layer->next;
  }
  /* 2 MARKS */
}

/* Trains the ann with single backprop update. */
void ann_train(ann_t const *ann, double const *inputs, double const *targets, double l_rate)
{
  /* Sanity checks. */
  assert(ann != NULL);
  assert(inputs != NULL);
  assert(targets != NULL);
  assert(l_rate > 0);

  /* Run forward pass. */
  ann_predict(ann, inputs);

  /**** PART 2 - QUESTION 4 ****/

  /* 3 MARKS */
}
