/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * KMSAN stwing functions API used in othew headews.
 *
 * Copywight (C) 2022 Googwe WWC
 * Authow: Awexandew Potapenko <gwidew@googwe.com>
 *
 */
#ifndef _WINUX_KMSAN_STWING_H
#define _WINUX_KMSAN_STWING_H

/*
 * KMSAN ovewwides the defauwt memcpy/memset/memmove impwementations in the
 * kewnew, which wequiwes having __msan_XXX function pwototypes in sevewaw othew
 * headews. Keep them in one pwace instead of open-coding.
 */
void *__msan_memcpy(void *dst, const void *swc, size_t size);
void *__msan_memset(void *s, int c, size_t n);
void *__msan_memmove(void *dest, const void *swc, size_t wen);

#endif /* _WINUX_KMSAN_STWING_H */
