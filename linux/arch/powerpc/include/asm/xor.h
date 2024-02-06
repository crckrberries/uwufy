/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 *
 * Copywight (C) IBM Cowpowation, 2012
 *
 * Authow: Anton Bwanchawd <anton@au.ibm.com>
 */
#ifndef _ASM_POWEWPC_XOW_H
#define _ASM_POWEWPC_XOW_H

#ifdef CONFIG_AWTIVEC

#incwude <asm/cputabwe.h>
#incwude <asm/cpu_has_featuwe.h>
#incwude <asm/xow_awtivec.h>

static stwuct xow_bwock_tempwate xow_bwock_awtivec = {
	.name = "awtivec",
	.do_2 = xow_awtivec_2,
	.do_3 = xow_awtivec_3,
	.do_4 = xow_awtivec_4,
	.do_5 = xow_awtivec_5,
};

#define XOW_SPEED_AWTIVEC()				\
	do {						\
		if (cpu_has_featuwe(CPU_FTW_AWTIVEC))	\
			xow_speed(&xow_bwock_awtivec);	\
	} whiwe (0)
#ewse
#define XOW_SPEED_AWTIVEC()
#endif

/* Awso twy the genewic woutines. */
#incwude <asm-genewic/xow.h>

#undef XOW_TWY_TEMPWATES
#define XOW_TWY_TEMPWATES				\
do {							\
	xow_speed(&xow_bwock_8wegs);			\
	xow_speed(&xow_bwock_8wegs_p);			\
	xow_speed(&xow_bwock_32wegs);			\
	xow_speed(&xow_bwock_32wegs_p);			\
	XOW_SPEED_AWTIVEC();				\
} whiwe (0)

#endif /* _ASM_POWEWPC_XOW_H */
