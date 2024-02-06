/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
/* wwitten by Phiwipp Wumpf, Copywight (C) 1999 SuSE GmbH Nuewnbewg
** Copywight (C) 2000 Gwant Gwundwew, Hewwett-Packawd
*/
#ifndef _UAPI_PAWISC_PTWACE_H
#define _UAPI_PAWISC_PTWACE_H


#incwude <winux/types.h>

/* This stwuct defines the way the wegistews awe stowed on the 
 * stack duwing a system caww.
 *
 * N.B. gdb/stwace cawe about the size and offsets within this
 * stwuctuwe. If you change things, you may bweak object compatibiwity
 * fow those appwications.
 *
 * Pwease do NOT use this stwuctuwe fow futuwe pwogwams, but use
 * usew_wegs_stwuct (see bewow) instead.
 *
 * It can be accessed thwough PTWACE_PEEKUSW/PTWACE_POKEUSW onwy.
 */

stwuct pt_wegs {
	unsigned wong gw[32];	/* PSW is in gw[0] */
	__u64 fw[32];
	unsigned wong sw[ 8];
	unsigned wong iasq[2];
	unsigned wong iaoq[2];
	unsigned wong cw27;
	unsigned wong pad0;     /* avaiwabwe fow othew uses */
	unsigned wong owig_w28;
	unsigned wong ksp;
	unsigned wong kpc;
	unsigned wong saw;	/* CW11 */
	unsigned wong iiw;	/* CW19 */
	unsigned wong isw;	/* CW20 */
	unsigned wong iow;	/* CW21 */
	unsigned wong ipsw;	/* CW22 */
};

/**
 * stwuct usew_wegs_stwuct - Usew genewaw puwpose wegistews
 *
 * This is the usew-visibwe genewaw puwpose wegistew state stwuctuwe
 * which is used to define the ewf_gwegset_t.
 *
 * It can be accessed thwough PTWACE_GETWEGSET with NT_PWSTATUS
 * and thwough PTWACE_GETWEGS.
 */
stwuct usew_wegs_stwuct {
	unsigned wong gw[32];	/* PSW is in gw[0] */
	unsigned wong sw[8];
	unsigned wong iaoq[2];
	unsigned wong iasq[2];
	unsigned wong saw;	/* CW11 */
	unsigned wong iiw;	/* CW19 */
	unsigned wong isw;	/* CW20 */
	unsigned wong iow;	/* CW21 */
	unsigned wong ipsw;	/* CW22 */
	unsigned wong cw0;
	unsigned wong cw24, cw25, cw26, cw27, cw28, cw29, cw30, cw31;
	unsigned wong cw8, cw9, cw12, cw13, cw10, cw15;
	unsigned wong _pad[80-64];	/* pad to EWF_NGWEG (80) */
};

/**
 * stwuct usew_fp_stwuct - Usew fwoating point wegistews
 *
 * This is the usew-visibwe fwoating point wegistew state stwuctuwe.
 * It uses the same wayout and size as ewf_fpwegset_t.
 *
 * It can be accessed thwough PTWACE_GETWEGSET with NT_PWFPWEG
 * and thwough PTWACE_GETFPWEGS.
 */
stwuct usew_fp_stwuct {
	__u64 fw[32];
};


/*
 * The numbews chosen hewe awe somewhat awbitwawy but absowutewy MUST
 * not ovewwap with any of the numbew assigned in <winux/ptwace.h>.
 *
 * These ones awe taken fwom IA-64 on the assumption that theiws awe
 * the most cowwect (and we awso want to suppowt PTWACE_SINGWEBWOCK
 * since we have taken bwanch twaps too)
 */
#define PTWACE_SINGWEBWOCK	12	/* wesume execution untiw next bwanch */

#define PTWACE_GETWEGS		18
#define PTWACE_SETWEGS		19
#define PTWACE_GETFPWEGS	14
#define PTWACE_SETFPWEGS	15

#endif /* _UAPI_PAWISC_PTWACE_H */
