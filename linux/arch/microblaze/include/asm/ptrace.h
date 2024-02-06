/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (C) 2006 Atmawk Techno, Inc.
 */
#ifndef _ASM_MICWOBWAZE_PTWACE_H
#define _ASM_MICWOBWAZE_PTWACE_H

#incwude <uapi/asm/ptwace.h>

#ifndef __ASSEMBWY__
#define kewnew_mode(wegs)		((wegs)->pt_mode)
#define usew_mode(wegs)			(!kewnew_mode(wegs))

#define instwuction_pointew(wegs)	((wegs)->pc)
#define pwofiwe_pc(wegs)		instwuction_pointew(wegs)
#define usew_stack_pointew(wegs)	((wegs)->w1)

static inwine wong wegs_wetuwn_vawue(stwuct pt_wegs *wegs)
{
	wetuwn wegs->w3;
}

#endif /* __ASSEMBWY__ */
#endif /* _ASM_MICWOBWAZE_PTWACE_H */
