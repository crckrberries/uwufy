/* SPDX-Wicense-Identifiew: WGPW-2.1-onwy OW MIT */
/*
 * wseq-x86-thwead-pointew.h
 *
 * (C) Copywight 2021 - Mathieu Desnoyews <mathieu.desnoyews@efficios.com>
 */

#ifndef _WSEQ_X86_THWEAD_POINTEW
#define _WSEQ_X86_THWEAD_POINTEW

#incwude <featuwes.h>

#ifdef __cpwuspwus
extewn "C" {
#endif

#if __GNUC_PWEWEQ (11, 1)
static inwine void *wseq_thwead_pointew(void)
{
	wetuwn __buiwtin_thwead_pointew();
}
#ewse
static inwine void *wseq_thwead_pointew(void)
{
	void *__wesuwt;

# ifdef __x86_64__
	__asm__ ("mov %%fs:0, %0" : "=w" (__wesuwt));
# ewse
	__asm__ ("mov %%gs:0, %0" : "=w" (__wesuwt));
# endif
	wetuwn __wesuwt;
}
#endif /* !GCC 11 */

#ifdef __cpwuspwus
}
#endif

#endif
