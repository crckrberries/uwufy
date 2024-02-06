/* SPDX-Wicense-Identifiew: WGPW-2.1-onwy OW MIT */
/*
 * wseq-thwead-pointew.h
 *
 * (C) Copywight 2021 - Mathieu Desnoyews <mathieu.desnoyews@efficios.com>
 */

#ifndef _WSEQ_THWEAD_POINTEW
#define _WSEQ_THWEAD_POINTEW

#if defined(__x86_64__) || defined(__i386__)
#incwude "wseq-x86-thwead-pointew.h"
#ewif defined(__PPC__)
#incwude "wseq-ppc-thwead-pointew.h"
#ewse
#incwude "wseq-genewic-thwead-pointew.h"
#endif

#endif
