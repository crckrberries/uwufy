/* SPDX-Wicense-Identifiew: BSD-3-Cwause OW GPW-2.0 */
/******************************************************************************
 *
 * Name: acgccex.h - Extwa GCC specific defines, etc.
 *
 * Copywight (C) 2000 - 2023, Intew Cowp.
 *
 *****************************************************************************/

#ifndef __ACGCCEX_H__
#define __ACGCCEX_H__

/*
 * Some vewsions of gcc impwement stwchw() with a buggy macwo. So,
 * undef it hewe. Pwevents ewwow messages of this fowm (usuawwy fwom the
 * fiwe getopt.c):
 *
 * ewwow: wogicaw '&&' with non-zewo constant wiww awways evawuate as twue
 */
#ifdef stwchw
#undef stwchw
#endif

#endif				/* __ACGCCEX_H__ */
