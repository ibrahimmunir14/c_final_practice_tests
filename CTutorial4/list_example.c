#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct list_elem *list_iter;


struct list_elem{
  int value;
  struct list_elem *prev;
  struct list_elem *next;
 };

struct list{
  struct list_elem *header;
  struct list_elem *footer;
};

struct list_elem* list_alloc_elem(void);
void list_free_elem(struct list_elem *elem);
void list_insert(struct list *l, list_iter iter, int value);
list_iter list_iter_next(list_iter iter);
list_iter list_begin(struct list *l);
struct list_elem* list_end(struct list *l);
struct list_elem* list_end(struct list *l);
int list_internal(list_iter iter);
int list_iter_value(list_iter iter);
void list_insert_front(struct list *l, int value);
void list_insert_back(struct list *l, int value);
void list_destroy(struct list *l) ;
void list_init(struct list *l);

struct list_elem* list_alloc_elem(void){
  struct list_elem *elem = malloc(sizeof(struct list_elem));
  if(elem == NULL){
    perror("list_alloc_elem");
    exit(EXIT_FAILURE);
  }
  return elem;
}

void list_free_elem(struct list_elem *elem){
  free(elem);
}

void list_insert(struct list *l, list_iter iter, int value){
  struct list_elem *new_elem = list_alloc_elem();
  new_elem->value = value;

  new_elem->next = iter;
  new_elem->prev = iter->prev;

  iter->prev->next = new_elem;
  iter->prev = new_elem;

}

list_iter list_iter_next(list_iter iter){
  return iter->next;
}
list_iter list_begin(struct list *l){
  return l->header->next;
}

struct list_elem* list_end(struct list *l){
  return l->footer;
}

int list_internal(list_iter iter){
  return iter->prev !=NULL && iter->next !=NULL;
}

int list_iter_value(list_iter iter){
  assert(list_internal(iter));
  return iter->value;
}


void list_insert_front(struct list *l, int value) {
  list_insert(l, list_begin(l), value);
}

void list_insert_back(struct list *l, int value) {
  list_insert(l, list_end(l), value);
}


void list_destroy(struct list *l) {
  struct list_elem *elem = l->header;
  while (elem != NULL) {
    struct list_elem *next = elem->next;
    list_free_elem(elem);
    elem = next;
  }
}
void list_init(struct list *l){
  l->header = list_alloc_elem();
  l->footer = list_alloc_elem();
  l->header->prev = NULL;
  l->footer->next = NULL;
  l->header->next = l->footer;
  l->footer->prev = l->header;
}

void list_display(struct list *l) {
  for(list_iter iter = list_begin(l);
      iter != list_end(l);
      iter = list_iter_next(iter)) {
    printf("%i ", list_iter_value(iter));
  }
}
// Question 1
void list_drop(struct list *l, int n) {
  list_iter elem = l->header;
  for (int i = 0; i < n; i++) {
    list_iter next = elem->next;
    list_free_elem(elem);
    elem = next;
  }
  l->header = elem;
  elem->prev = l->header;
}

int main(void) {
  struct list l;
  list_init(&l);

  list_insert_front(&l, 1);
  list_insert_front(&l, 2);
  list_insert_back(&l, 1);
  list_insert_back(&l, 2);
  list_insert_front(&l, 2);
  list_insert_front(&l, 5);
  list_insert_front(&l, 7);
  list_insert_front(&l, 3);
  list_display(&l);

  printf("\nDropping 0 items\n");
  list_drop(&l, 0);
  list_display(&l);

  printf("\nDropping 5 items\n");
  list_drop(&l, 5);
  list_display(&l);

  list_destroy(&l);
  return 0;
}

