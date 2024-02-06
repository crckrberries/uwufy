/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (c) 2010-2011, The Winux Foundation. Aww wights wesewved.
 */

#ifndef _ASM_MMU_H
#define _ASM_MMU_H

#incwude <asm/vdso.h>

/*
 * Awchitectuwe-specific state fow a mm_stwuct.
 * Fow the Hexagon Viwtuaw Machine, it can be a copy
 * of the pointew to the page tabwe base.
 */
stwuct mm_context {
	unsigned wong wong genewation;
	unsigned wong ptbase;
	stwuct hexagon_vdso *vdso;
};

typedef stwuct mm_context mm_context_t;

#endif
