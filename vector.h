#ifndef VECTOR_H_
#define VECTOR_H_

#include <stdlib.h>
#include <string.h>

#define VECTOR(TYPE) TYPE##_vector_t
#define SIZEOF_VECTOR(TYPE) sizeof(TYPE##_vector_t)

#define TYPEOF_VECTOR(VECTOR) __typeof__(*VECTOR->data)

#define VECTOR_FOREACH(I, VECTOR)                                              \
  for (TYPEOF_VECTOR(VECTOR) *I = VECTOR->data;                                \
       I < &VECTOR->data[VECTOR->size]; I++)

#define TYPE_VECTOR_T(TYPE)                                                    \
  struct TYPE##_vector_s {                                                     \
    size_t size;                                                               \
    size_t capacity;                                                           \
    TYPE data[];                                                               \
  };                                                                           \
  typedef struct TYPE##_vector_s VECTOR(TYPE);

#define NEW_TYPE_VECTOR_PROTO(TYPE) VECTOR(TYPE) * new_##TYPE##_vector(void)

#define NEW_TYPE_VECTOR(TYPE)                                                  \
  NEW_TYPE_VECTOR_PROTO(TYPE) {                                                \
    VECTOR(TYPE) *vector = malloc(SIZEOF_VECTOR(TYPE));                        \
    if (vector) {                                                              \
      vector->size = 0;                                                        \
      vector->capacity = 0;                                                    \
    }                                                                          \
    return vector;                                                             \
  }

#define DELETE_TYPE_VECTOR_PROTO(TYPE)                                         \
  void delete_##TYPE##_vector(VECTOR(TYPE) * vector)

#define DELETE_TYPE_VECTOR(TYPE)                                               \
  DELETE_TYPE_VECTOR_PROTO(TYPE) { free(vector); }

#define TYPE_VECTOR_SIZE_PROTO(TYPE)                                           \
  size_t TYPE##_vector_size(VECTOR(TYPE) * vector)

#define TYPE_VECTOR_SIZE(TYPE)                                                 \
  TYPE_VECTOR_SIZE_PROTO(TYPE) { return vector->size; }

#define TYPE_VECTOR_CAPACITY_PROTO(TYPE)                                       \
  size_t TYPE##_vector_capacity(VECTOR(TYPE) * vector)

#define TYPE_VECTOR_CAPACITY(TYPE)                                             \
  TYPE_VECTOR_CAPACITY_PROTO(TYPE) { return vector->capacity; }

#define TYPE_VECTOR_RESERVE_PROTO(TYPE)                                        \
  VECTOR(TYPE) * TYPE##_vector_reserve(VECTOR(TYPE) * vector, size_t size)

#define TYPE_VECTOR_RESERVE(TYPE)                                              \
  TYPE_VECTOR_RESERVE_PROTO(TYPE) {                                            \
    size_t new_size = SIZEOF_VECTOR(TYPE) + sizeof(TYPE) * size;               \
    vector = realloc(vector, new_size);                                        \
    if (vector) {                                                              \
      if (size < vector->size) {                                               \
        vector->size = size;                                                   \
      }                                                                        \
      vector->capacity = size;                                                 \
    }                                                                          \
    return vector;                                                             \
  }

#define TYPE_VECTOR_RESIZE_PROTO(TYPE)                                         \
  VECTOR(TYPE) * TYPE##_vector_resize(VECTOR(TYPE) * vector, size_t size)

#define TYPE_VECTOR_RESIZE(TYPE)                                               \
  TYPE_VECTOR_RESIZE_PROTO(TYPE) {                                             \
    if (size < vector->capacity) {                                             \
      vector->size = size;                                                     \
      return vector;                                                           \
    } else {                                                                   \
      vector = TYPE##_vector_reserve(vector, size);                            \
      if (vector) {                                                            \
        vector->size = size;                                                   \
      }                                                                        \
      return vector;                                                           \
    }                                                                          \
  }

#define TYPE_VECTOR_EMPTY_PROTO(TYPE)                                          \
  int TYPE##_vector_empty(VECTOR(TYPE) * vector)

#define TYPE_VECTOR_EMPTY(TYPE)                                                \
  TYPE_VECTOR_EMPTY_PROTO(TYPE) { return !vector->size; }

#define TYPE_VECTOR_SHRINK_TO_FIT_PROTO(TYPE)                                  \
  VECTOR(TYPE) * TYPE##_vector_shrink_to_fit(VECTOR(TYPE) * vector)

#define TYPE_VECTOR_SHRINK_TO_FIT(TYPE)                                        \
  TYPE_VECTOR_SHRINK_TO_FIT_PROTO(TYPE) {                                      \
    return TYPE##_vector_reserve(vector, vector->size);                        \
  }

#define TYPE_VECTOR_AT_PROTO(TYPE)                                             \
  TYPE *TYPE##_vector_at(VECTOR(TYPE) * vector, size_t index)

#define TYPE_VECTOR_AT(TYPE)                                                   \
  TYPE_VECTOR_AT_PROTO(TYPE) {                                                 \
    if (vector->size < index) {                                                \
      return NULL;                                                             \
    } else {                                                                   \
      return vector->data + index;                                             \
    }                                                                          \
  }

#define TYPE_VECTOR_FRONT_PROTO(TYPE)                                          \
  TYPE *TYPE##_vector_front(VECTOR(TYPE) * vector)

#define TYPE_VECTOR_FRONT(TYPE)                                                \
  TYPE_VECTOR_FRONT_PROTO(TYPE) { return TYPE##_vector_at(vector, 0); }

#define TYPE_VECTOR_BACK_PROTO(TYPE)                                           \
  TYPE *TYPE##_vector_back(VECTOR(TYPE) * vector)

#define TYPE_VECTOR_BACK(TYPE)                                                 \
  TYPE_VECTOR_BACK_PROTO(TYPE) {                                               \
    return TYPE##_vector_at(vector, vector->size);                             \
  }

#define TYPE_VECTOR_ASSING_PROTO(TYPE)                                         \
  VECTOR(TYPE) * TYPE##_vector_assing(size_t n, TYPE *val)

#define TYPE_VECTOR_ASSING(TYPE)                                               \
  TYPE_VECTOR_ASSING_PROTO(TYPE) { return NULL; }

#define TYPE_VECTOR_PUSH_BACK_PROTO(TYPE)                                      \
  VECTOR(TYPE) * TYPE##_vector_push_back(VECTOR(TYPE) * vector, TYPE * data)

#define TYPE_VECTOR_PUSH_BACK(TYPE)                                            \
  TYPE_VECTOR_PUSH_BACK_PROTO(TYPE) {                                          \
    if (vector->size + 1 > vector->capacity) {                                 \
      size_t size = vector->size ? vector->size : 1;                           \
      vector = TYPE##_vector_reserve(vector, size * 2);                        \
    }                                                                          \
    if (vector) {                                                              \
      memmove(&vector->data[vector->size], data, sizeof(TYPE));                \
      vector->size++;                                                          \
    }                                                                          \
    return vector;                                                             \
  }

#define TYPE_VECTOR_POP_BACK_PROTO(TYPE)                                       \
  void TYPE##_vector_pop_back(VECTOR(TYPE) * vector)

#define TYPE_VECTOR_POP_BACK(TYPE)                                             \
  TYPE_VECTOR_POP_BACK_PROTO(TYPE) {                                           \
    if (1 <= vector->size) {                                                   \
      vector->size--;                                                          \
    }                                                                          \
  }

#define TYPE_VECTOR_INSERT_PROTO(TYPE)                                         \
  void TYPE##_vector_insert(VECTOR(TYPE) * vector, TYPE * data, size_t index)

#define TYPE_VECTOR_INSERT(TYPE)                                               \
  TYPE_VECTOR_INSERT_PROTO(TYPE) {                                             \
    if (vector->size + 1 > vector->capacity) {                                 \
      size_t size = vector->size ? vector->size : 1;                           \
      vector = TYPE##_vector_reserve(vector, size * 2);                        \
    }                                                                          \
    if (vector) {                                                              \
      size_t size = sizeof(TYPE) * (vector->size - index);                     \
      memmove(&vector->data[index + 1], &vector->data[index], size);           \
      memmove(&vector->data[index], data, sizeof(TYPE));                       \
    }                                                                          \
  }

#define TYPE_VECTOR_ERASE_PROTO(TYPE)                                          \
  void TYPE##_vector_erase(VECTOR(TYPE) * vector, size_t index)

#define TYPE_VECTOR_ERASE(TYPE)                                                \
  TYPE_VECTOR_ERASE_PROTO(TYPE) {                                              \
    size_t size = sizeof(TYPE) * (vector->size - index - 1);                   \
    memmove(&vector->data[index], &vector->data[index + 1], size);             \
  }

#define TYPE_VECTOR_CLEAR_PROTO(TYPE)                                          \
  void TYPE##_vector_clear(VECTOR(TYPE) * vector)

#define TYPE_VECTOR_CLEAR(TYPE)                                                \
  TYPE_VECTOR_CLEAR_PROTO(TYPE) { vector->size = 0; }

#define CREATE_VECTOR_TYPE_PROTO(TYPE)                                         \
  TYPE_VECTOR_T(TYPE)                                                          \
                                                                               \
  NEW_TYPE_VECTOR_PROTO(TYPE);                                                 \
  DELETE_TYPE_VECTOR_PROTO(TYPE);                                              \
                                                                               \
  TYPE_VECTOR_SIZE_PROTO(TYPE);                                                \
  TYPE_VECTOR_CAPACITY_PROTO(TYPE);                                            \
  TYPE_VECTOR_RESERVE_PROTO(TYPE);                                             \
  TYPE_VECTOR_RESIZE_PROTO(TYPE);                                              \
  TYPE_VECTOR_EMPTY_PROTO(TYPE);                                               \
  TYPE_VECTOR_SHRINK_TO_FIT_PROTO(TYPE);                                       \
  TYPE_VECTOR_AT_PROTO(TYPE);                                                  \
  TYPE_VECTOR_FRONT_PROTO(TYPE);                                               \
  TYPE_VECTOR_BACK_PROTO(TYPE);                                                \
  TYPE_VECTOR_PUSH_BACK_PROTO(TYPE);                                           \
  TYPE_VECTOR_POP_BACK_PROTO(TYPE);                                            \
  TYPE_VECTOR_INSERT_PROTO(TYPE);                                              \
  TYPE_VECTOR_ERASE_PROTO(TYPE);                                               \
  TYPE_VECTOR_CLEAR_PROTO(TYPE);

#define CREATE_VECTOR_TYPE(TYPE)                                               \
  NEW_TYPE_VECTOR(TYPE)                                                        \
  DELETE_TYPE_VECTOR(TYPE)                                                     \
                                                                               \
  TYPE_VECTOR_SIZE(TYPE)                                                       \
  TYPE_VECTOR_CAPACITY(TYPE)                                                   \
  TYPE_VECTOR_RESERVE(TYPE)                                                    \
  TYPE_VECTOR_RESIZE(TYPE)                                                     \
  TYPE_VECTOR_EMPTY(TYPE)                                                      \
  TYPE_VECTOR_SHRINK_TO_FIT(TYPE)                                              \
  TYPE_VECTOR_AT(TYPE)                                                         \
  TYPE_VECTOR_FRONT(TYPE)                                                      \
  TYPE_VECTOR_BACK(TYPE)                                                       \
  TYPE_VECTOR_PUSH_BACK(TYPE)                                                  \
  TYPE_VECTOR_POP_BACK(TYPE)                                                   \
  TYPE_VECTOR_INSERT(TYPE)                                                     \
  TYPE_VECTOR_ERASE(TYPE)                                                      \
  TYPE_VECTOR_CLEAR(TYPE)

#endif /* !VECTOR_H_ */
