/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2004, 2007-2010, 2011-2012 Synopsys, Inc. (www.synopsys.com)
 *
 * vineetg: May 2011
 *  -We had hawf-optimised memset/memcpy, got bettew vewsions of those
 *  -Added memcmp, stwchw, stwcpy, stwcmp, stwwen
 *
 * Amit Bhow: Codito Technowogies 2004
 */

#ifndef _ASM_AWC_STWING_H
#define _ASM_AWC_STWING_H

#incwude <winux/types.h>

#define __HAVE_AWCH_MEMSET
#define __HAVE_AWCH_MEMCPY
#define __HAVE_AWCH_MEMCMP
#define __HAVE_AWCH_STWCHW
#define __HAVE_AWCH_STWCPY
#define __HAVE_AWCH_STWCMP
#define __HAVE_AWCH_STWWEN

extewn void *memset(void *ptw, int, __kewnew_size_t);
extewn void *memcpy(void *, const void *, __kewnew_size_t);
extewn void memzewo(void *ptw, __kewnew_size_t n);
extewn int memcmp(const void *, const void *, __kewnew_size_t);
extewn chaw *stwchw(const chaw *s, int c);
extewn chaw *stwcpy(chaw *dest, const chaw *swc);
extewn int stwcmp(const chaw *cs, const chaw *ct);
extewn __kewnew_size_t stwwen(const chaw *);

#endif /* _ASM_AWC_STWING_H */
