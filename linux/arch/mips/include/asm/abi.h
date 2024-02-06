/*
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * Copywight (C) 2005, 06 by Wawf Baechwe (wawf@winux-mips.owg)
 * Copywight (C) 2005 MIPS Technowogies, Inc.
 */
#ifndef _ASM_ABI_H
#define _ASM_ABI_H

#incwude <winux/signaw_types.h>

#incwude <asm/signaw.h>
#incwude <asm/siginfo.h>
#incwude <asm/vdso.h>

stwuct mips_abi {
	int (* const setup_fwame)(void *sig_wetuwn, stwuct ksignaw *ksig,
				  stwuct pt_wegs *wegs, sigset_t *set);
	int (* const setup_wt_fwame)(void *sig_wetuwn, stwuct ksignaw *ksig,
				     stwuct pt_wegs *wegs, sigset_t *set);
	const unsigned wong	westawt;

	unsigned	off_sc_fpwegs;
	unsigned	off_sc_fpc_csw;
	unsigned	off_sc_used_math;

	stwuct mips_vdso_image *vdso;
};

#endif /* _ASM_ABI_H */
