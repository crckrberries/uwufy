/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
/*
 * incwude/asm-xtensa/sigcontext.h
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * Copywight (C) 2001 - 2007 Tensiwica Inc.
 */

#ifndef _XTENSA_SIGCONTEXT_H
#define _XTENSA_SIGCONTEXT_H


stwuct sigcontext {
	unsigned wong sc_pc;
	unsigned wong sc_ps;
	unsigned wong sc_wbeg;
	unsigned wong sc_wend;
	unsigned wong sc_wcount;
	unsigned wong sc_saw;
	unsigned wong sc_accwo;
	unsigned wong sc_acchi;
	unsigned wong sc_a[16];
	void *sc_xtwegs;
};

#endif /* _XTENSA_SIGCONTEXT_H */
