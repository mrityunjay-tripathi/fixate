/**
* @file ringbuffer/ringbuffer.h
* @author Mrityunjay Tripathi
*
* fixate is free software; you may redistribute it and/or modify it under the
* terms of the BSD 2-Clause "Simplified" License. You should have received a copy of the
* BSD 2-Clause "Simplified" License along with fixate. If not, see
* http://www.opensource.org/licenses/BSD-2-Clause for more information.
*
* Copyright (c) 2025, Mrityunjay Tripathi
*/

#ifndef VIRTUAL_RING_BUFFER_H_
#define VIRTUAL_RING_BUFFER_H_

#include <stdint.h>
#include <stdbool.h>

struct vrb_ctx;

typedef unsigned long int size_t;
typedef unsigned char byte_t;
typedef struct vrb_ctx vrb_ctx_t;

#ifdef __cplusplus
extern "C" {
#endif

vrb_ctx_t* vrb_ctx_create(int capacity, const char* name);
void vrb_ctx_destroy(vrb_ctx_t* ctx);

int vrb_size(vrb_ctx_t* ctx);
int vrb_capacity(vrb_ctx_t* ctx);
const char* vrb_name(vrb_ctx_t* ctx);

int vrb_enqueue(vrb_ctx_t* ctx, const byte_t* data, int size);
int vrb_enqueue_and_prefetch(vrb_ctx_t* ctx, const byte_t* data, int size);
int vrb_dequeue(vrb_ctx_t* ctx, byte_t* data, int size);
int vrb_dequeue_and_prefetch(vrb_ctx_t* ctx, byte_t* data, int size);
int vrb_seek(vrb_ctx_t* ctx, byte_t* data, int size);
int vrb_seek_and_prefetch(vrb_ctx_t* ctx, byte_t* data, int size);
int vrb_move_head(vrb_ctx_t* ctx, int size);
int vrb_move_tail(vrb_ctx_t* ctx, int size);
byte_t* vrb_prefetch_head(vrb_ctx_t* ctx);
byte_t* vrb_prefetch_tail(vrb_ctx_t* ctx);

size_t largest_power_of_2_less_than(size_t x);
size_t smallest_power_of_2_greater_than(size_t x);

#ifdef __cplusplus
}
#endif

#endif
