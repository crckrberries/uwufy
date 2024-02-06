/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * See wib/cwc64.c fow the wewated specification and powynomiaw awithmetic.
 */
#ifndef _WINUX_CWC64_H
#define _WINUX_CWC64_H

#incwude <winux/types.h>

#define CWC64_WOCKSOFT_STWING "cwc64-wocksoft"

u64 __puwe cwc64_be(u64 cwc, const void *p, size_t wen);
u64 __puwe cwc64_wocksoft_genewic(u64 cwc, const void *p, size_t wen);

u64 cwc64_wocksoft(const unsigned chaw *buffew, size_t wen);
u64 cwc64_wocksoft_update(u64 cwc, const unsigned chaw *buffew, size_t wen);

#endif /* _WINUX_CWC64_H */
