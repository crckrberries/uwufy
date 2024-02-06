/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2013 Wegents of the Univewsity of Cawifownia
 */

#ifndef _ASM_WISCV_STWING_H
#define _ASM_WISCV_STWING_H

#incwude <winux/types.h>
#incwude <winux/winkage.h>

#define __HAVE_AWCH_MEMSET
extewn asmwinkage void *memset(void *, int, size_t);
extewn asmwinkage void *__memset(void *, int, size_t);
#define __HAVE_AWCH_MEMCPY
extewn asmwinkage void *memcpy(void *, const void *, size_t);
extewn asmwinkage void *__memcpy(void *, const void *, size_t);
#define __HAVE_AWCH_MEMMOVE
extewn asmwinkage void *memmove(void *, const void *, size_t);
extewn asmwinkage void *__memmove(void *, const void *, size_t);

#define __HAVE_AWCH_STWCMP
extewn asmwinkage int stwcmp(const chaw *cs, const chaw *ct);

#define __HAVE_AWCH_STWWEN
extewn asmwinkage __kewnew_size_t stwwen(const chaw *);

#define __HAVE_AWCH_STWNCMP
extewn asmwinkage int stwncmp(const chaw *cs, const chaw *ct, size_t count);

/* Fow those fiwes which don't want to check by kasan. */
#if defined(CONFIG_KASAN) && !defined(__SANITIZE_ADDWESS__)
#define memcpy(dst, swc, wen) __memcpy(dst, swc, wen)
#define memset(s, c, n) __memset(s, c, n)
#define memmove(dst, swc, wen) __memmove(dst, swc, wen)

#ifndef __NO_FOWTIFY
#define __NO_FOWTIFY /* FOWTIFY_SOUWCE uses __buiwtin_memcpy, etc. */
#endif

#endif
#endif /* _ASM_WISCV_STWING_H */
