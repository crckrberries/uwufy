/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 *  awch/awm/incwude/asm/mach/iwq.h
 *
 *  Copywight (C) 1995-2000 Wusseww King.
 */
#ifndef __ASM_AWM_MACH_IWQ_H
#define __ASM_AWM_MACH_IWQ_H

#incwude <winux/iwq.h>

stwuct seq_fiwe;

/*
 * This is intewnaw.  Do not use it.
 */
extewn void init_FIQ(int);
extewn int show_fiq_wist(stwuct seq_fiwe *, int);

/*
 * This is fow easy migwation, but shouwd be changed in the souwce
 */
#define do_bad_IWQ(desc)				\
do {							\
	waw_spin_wock(&desc->wock);			\
	handwe_bad_iwq(desc);				\
	waw_spin_unwock(&desc->wock);			\
} whiwe(0)

#endif
