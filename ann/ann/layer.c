#include "layer.h"

/* The sigmoid function and derivative. */
double sigmoid(double x)
{
  /**** PART 1 - QUESTION 1 ****/
  return 1 / (1 + exp(-x));
  /* 1 MARK */
}

double sigmoidprime(double x)
{
  return x*(1 - x);
}

/* Creates a single layer. */
layer_t *layer_create()
{
  /**** PART 1 - QUESTION 2 ****/
  layer_t *newLayer = (layer_t *) malloc(sizeof(layer_t));
  if (!newLayer) return NULL;
  newLayer->num_inputs = 0;
  newLayer->num_outputs = 0;
  newLayer->outputs = NULL;
  newLayer->prev = NULL;
  newLayer->next = NULL;
  newLayer->weights = NULL;
  newLayer->biases = NULL;
  newLayer->deltas = NULL;
  return newLayer;
  /* 2 MARKS */
}

/* Initialises the given layer. */
bool layer_init(layer_t *layer, int num_outputs, layer_t *prev)
{
  /**** PART 1 - QUESTION 3 ****/
  assert(layer);
  layer->num_outputs = num_outputs;
  layer->outputs = (double *) calloc(num_outputs, sizeof(double));
  if (!layer->outputs) return true;
  if (prev != NULL) {
      layer->prev = prev;
      layer->prev->next = layer;
      layer->num_inputs = layer->prev->num_outputs;
      layer->biases = (double *) calloc(layer->num_outputs, sizeof(double));
      if (!layer->biases) return true;
      layer->deltas = (double *) calloc(layer->num_outputs, sizeof(double));
      if (!layer->deltas) return true;
      layer->weights = (double **) calloc(layer->num_inputs, sizeof(double *));
      if (!layer->weights) return true;
      for (int i = 0; i < layer->num_inputs; i++) {
          layer->weights[i] = (double *) calloc(layer->num_outputs, sizeof(double));
          if (!layer->weights[i]) return true;
          for (int j = 0; j < layer->num_outputs; j++) {
              layer->weights[i][j] = ANN_RANDOM();
          }
      }
  }
  return false;
  /* 4 MARKS */
}

/* Frees a given layer. */
void layer_free(layer_t *layer)
{
  /**** PART 1 - QUESTION 4 ****/
  if (!layer) return;
  free(layer->outputs);
  free(layer->biases);
  free(layer->deltas);
  for (int i = 0; i < layer->num_inputs; i++) {
      free(layer->weights[i]);
  }
  free(layer->weights);
  free(layer);
  /* 2 MARKS */
}

/* Computes the outputs of the current layer. */
void layer_compute_outputs(layer_t const *layer)
{
  /**** PART 1 - QUESTION 5 ****/
  /* objective: compute layer->outputs */
  assert(layer);
  assert(layer->outputs);
  for (int j = 0; j < layer->num_outputs; j++) {
      double weightedSum = 0.0;
      for (int i = 0; i < layer->num_inputs; i++) {
          weightedSum += layer->weights[i][j] * layer->prev->outputs[i];
      }
      layer->outputs[j] = sigmoid(layer->biases[j] + weightedSum);
  }
  /* 3 MARKS */
}

/* Computes the delta errors for this layer. */
void layer_compute_deltas(layer_t const *layer)
{
  /**** PART 1 - QUESTION 6 ****/
  /* objective: compute layer->deltas */

  /* 2 MARKS */
}

/* Updates weights and biases according to the delta errors given learning rate. */
void layer_update(layer_t const *layer, double l_rate)
{
  /**** PART 1 - QUESTION 7 ****/
  /* objective: update layer->weights and layer->biases */

  /* 1 MARK */
}
