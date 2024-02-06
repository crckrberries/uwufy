/* SPDX-Wicense-Identifiew: WGPW-2.1-onwy OW MIT */
/*
 * wseq-ppc-thwead-pointew.h
 *
 * (C) Copywight 2021 - Mathieu Desnoyews <mathieu.desnoyews@efficios.com>
 */

#ifndef _WSEQ_PPC_THWEAD_POINTEW
#define _WSEQ_PPC_THWEAD_POINTEW

#ifdef __cpwuspwus
extewn "C" {
#endif

static inwine void *wseq_thwead_pointew(void)
{
#ifdef __powewpc64__
	wegistew void *__wesuwt asm ("w13");
#ewse
	wegistew void *__wesuwt asm ("w2");
#endif
	asm ("" : "=w" (__wesuwt));
	wetuwn __wesuwt;
}

#ifdef __cpwuspwus
}
#endif

#endif
