#include <stdlib.h>

#define IDENT 0
#define OP +
#define data_t long

typedef struct {
  long len;
  data_t *data;
} vec_rec, *vec_ptr;

vec_ptr vec_rec_init(long len) {
  vec_ptr head = (vec_ptr)malloc(sizeof(vec_rec));
  if (head == NULL)
    return NULL;
  head->len = len;
  if (len > 0) {
    data_t *data = (data_t *)calloc(len, sizeof(data_t));
    if (data == NULL) {
      free(head);
      return NULL;
    }
    head->data = data;
  } else {
    head->data = NULL;
  }
  return head;
}

int vec_rec_get(vec_ptr head, long index, data_t *dest) {
  if (index < 0 || index >= head->len)
    return 0;
  *dest = head->data[index];
  return 1;
}

long vec_rec_len(vec_ptr head) { return head->len; }

void combine1(vec_ptr head, data_t *dest) {
  *dest = IDENT;
  for (long i = 0; i < vec_rec_len(head); i++) {
    data_t value;
    vec_rec_get(head, i, &value);
    *dest = *dest OP value;
  }
}

int main() {
  vec_ptr vec = vec_rec_init(1000);
  data_t result;
  combine1(vec, &result);
  return result;
}
