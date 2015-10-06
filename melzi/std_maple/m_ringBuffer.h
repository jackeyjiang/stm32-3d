/******************************************************************************
 * The MIT License
 *
 * Copyright (c) 2011 LeafLabs, LLC.
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use, copy,
 * modify, merge, publish, distribute, sublicense, and/or sell copies
 * of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *****************************************************************************/

/**
 * @file libmaple/include/libmaple/ring_buffer.h
 * @brief Simple circular buffer
 *
 * This implementation is not thread-safe.  In particular, none of
 * these functions is guaranteed re-entrant.
 */

#ifndef _LIBMAPLE_RING_BUFFER_H_
#define _LIBMAPLE_RING_BUFFER_H_
#include "typeDefine.h"
#ifdef __cplusplus
extern "C"{
#endif
/**
 * Ring buffer type.
 *
 * The buffer is empty when head == tail.
 *
 * The buffer is full when the head is one byte in front of the tail,
 * modulo buffer length.
 *
 * One byte is left free to distinguish empty from full. */
//---------------------------------------------------------------------
//
//---------------------------------------------------------------------
typedef struct ring_buffer {
    volatile uint8 *buf;    /**< Buffer items are stored into */
    uint16          head;   /**< Index of the next item to remove */
    uint16          tail;   /**< Index where the next item will get inserted */
    uint16          size;   /**< Buffer capacity minus one */
} ring_buffer;

//---------------------------------------------------------------------
// 环型内存 内存初始化
//---------------------------------------------------------------------
static inline void rb_init(ring_buffer *rb, uint16 size, uint8 *buf) {
    rb->head = 0;
    rb->tail = 0;
    rb->size = size - 1;
    rb->buf = buf;
}
//---------------------------------------------------------------------
// 环型内存 判断内存元素计数
//---------------------------------------------------------------------
static inline uint16 rb_full_count(ring_buffer *rb) {
    __io ring_buffer *arb = rb;
    int32 size = arb->tail - arb->head;
    if (arb->tail < arb->head) {
        size += arb->size + 1;
    }
    return (uint16)size;
}
//
//---------------------------------------------------------------------
// 环型内存 判断内存是否满
// return : 1 = full
//          0 = have buf
//---------------------------------------------------------------------
static inline int rb_is_full(ring_buffer *rb) {
    return (rb->tail + 1 == rb->head) ||
        (rb->tail == rb->size && rb->head == 0);
}
//
//---------------------------------------------------------------------
// 环型内存 判断内存是否空
// return: 1 empty
//         0 have massage
//---------------------------------------------------------------------
static inline int rb_is_empty(ring_buffer *rb) {
    return rb->head == rb->tail;
}
//
//---------------------------------------------------------------------
// 环型内存 插入元素
//---------------------------------------------------------------------
static inline void rb_insert(ring_buffer *rb, uint8 element) {
    rb->buf[rb->tail] = element;
    rb->tail = (rb->tail == rb->size) ? 0 : rb->tail + 1;
}
//
//---------------------------------------------------------------------
// 空内存 插入元素
//---------------------------------------------------------------------
static inline void rb_insertIndex(ring_buffer *rb) {
    rb->tail = (rb->tail == rb->size) ? 0 : rb->tail + 1;
}
//
//---------------------------------------------------------------------
// 读取前一个内存下标
//---------------------------------------------------------------------
static inline uint16 rb_get_PreIndex(ring_buffer *rb, uint16 index) {
    return (index == 0) ? (rb->size) : (index - 1);
}
//
//---------------------------------------------------------------------
// 读取下一个内存下标
//---------------------------------------------------------------------
static inline uint16 rb_get_NextIndex(ring_buffer *rb, uint16 index) {
    return (index == rb->size) ? 0 : index + 1;
}
//
//---------------------------------------------------------------------
// 获得头下标
//---------------------------------------------------------------------
static inline uint16 rb_get_head(ring_buffer *rb) {
    return rb->head;
}
//
//---------------------------------------------------------------------
// 获得尾下标
//---------------------------------------------------------------------
static inline uint16 rb_get_tail(ring_buffer *rb) {
    return rb->tail;
}
//
//---------------------------------------------------------------------
// 环型空内存 删除元素标
//---------------------------------------------------------------------
static inline void rb_removeIndex(ring_buffer *rb) {
    rb->head = (rb->head == rb->size) ? 0 : rb->head + 1;
}

//
//---------------------------------------------------------------------
// 环型内存 删除元素
//---------------------------------------------------------------------
static inline uint8 rb_remove(ring_buffer *rb) {
    uint8 ch = rb->buf[rb->head];
    rb->head = (rb->head == rb->size) ? 0 : rb->head + 1;
    return ch;
}
//
//---------------------------------------------------------------------
// 只读取数据，不推出， 操作完成再推出内存
// return ： -1 empty
//           massage
//---------------------------------------------------------------------
static inline int8 rb_only_get_msg(ring_buffer *rb) {
    if (rb_is_empty(rb)) {
        return -1;
    } else {
        return rb->buf[rb->head];
    }
}
//---------------------------------------------------------------------
// 只读取数据，不推出， 操作完成再推出内存
// return ： -1 full
//           massage
//---------------------------------------------------------------------
static inline int8 rb_only_get_buf(ring_buffer *rb) {
    if (rb_is_full(rb)) {
        return -1;
    } else {
        return rb->buf[rb->tail];
    }
}
//
//---------------------------------------------------------------------
// 环型内存 安全删除元素，内存空 返回-1
//---------------------------------------------------------------------
static inline int16 rb_safe_remove(ring_buffer *rb) {
    return rb_is_empty(rb) ? -1 : rb_remove(rb);
}
//
//---------------------------------------------------------------------
// 环型内存 安全插入元素，数据满 返回 0 不做处理
//---------------------------------------------------------------------
static inline int rb_safe_insert(ring_buffer *rb, uint8 element) {
    if (rb_is_full(rb)) {
        return 0;
    }
    rb_insert(rb, element);
    return 1;
}
//
//---------------------------------------------------------------------
// 环型内存 强制插入元素，如果内存满，挤出首数据
//---------------------------------------------------------------------
static inline int rb_push_insert(ring_buffer *rb, uint8 element) {
    int ret = -1;
    if (rb_is_full(rb)) {
        ret = rb_remove(rb);
    }
    rb_insert(rb, element);
    return ret;
}
//
//---------------------------------------------------------------------
// 环型内存复位
//---------------------------------------------------------------------
static inline void rb_reset(ring_buffer *rb) {
    rb->tail = rb->head;
}
//---------------------------------------------------------------------
#ifdef __cplusplus
} // extern "C"
#endif

#endif
//---------------------------------------------------------------------

