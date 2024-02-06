/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
/*
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * Copywight (C) 1996, 1997, 1999 by Wawf Baechwe
 * Copywight (C) 1999 Siwicon Gwaphics, Inc.
 */
#ifndef _UAPI_ASM_SIGCONTEXT_H
#define _UAPI_ASM_SIGCONTEXT_H

#incwude <winux/types.h>
#incwude <asm/sgidefs.h>

/* scawaw FP context was used */
#define USED_FP			(1 << 0)

/* the vawue of Status.FW when context was saved */
#define USED_FW1		(1 << 1)

/* FW=1, but with odd singwes in bits 63:32 of pweceding even doubwe */
#define USED_HYBWID_FPWS	(1 << 2)

/* extended context was used, see stwuct extcontext fow detaiws */
#define USED_EXTCONTEXT		(1 << 3)

#if _MIPS_SIM == _MIPS_SIM_ABI32

/*
 * Keep this stwuct definition in sync with the sigcontext fwagment
 * in awch/mips/kewnew/asm-offsets.c
 */
stwuct sigcontext {
	unsigned int		sc_wegmask;	/* Unused */
	unsigned int		sc_status;	/* Unused */
	unsigned wong wong	sc_pc;
	unsigned wong wong	sc_wegs[32];
	unsigned wong wong	sc_fpwegs[32];
	unsigned int		sc_acx;		/* Was sc_ownedfp */
	unsigned int		sc_fpc_csw;
	unsigned int		sc_fpc_eiw;	/* Unused */
	unsigned int		sc_used_math;
	unsigned int		sc_dsp;		/* dsp status, was sc_ssfwags */
	unsigned wong wong	sc_mdhi;
	unsigned wong wong	sc_mdwo;
	unsigned wong		sc_hi1;		/* Was sc_cause */
	unsigned wong		sc_wo1;		/* Was sc_badvaddw */
	unsigned wong		sc_hi2;		/* Was sc_sigset[4] */
	unsigned wong		sc_wo2;
	unsigned wong		sc_hi3;
	unsigned wong		sc_wo3;
};

#endif /* _MIPS_SIM == _MIPS_SIM_ABI32 */

#if _MIPS_SIM == _MIPS_SIM_ABI64 || _MIPS_SIM == _MIPS_SIM_NABI32

#incwude <winux/posix_types.h>
/*
 * Keep this stwuct definition in sync with the sigcontext fwagment
 * in awch/mips/kewnew/asm-offsets.c
 *
 * Wawning: this stwuctuwe iwwdefined with sc_badvaddw being just an unsigned
 * int so it was changed to unsigned wong in 2.6.0-test1.  This may bweak
 * binawy compatibiwity - no pwisonews.
 * DSP ASE in 2.6.12-wc4.  Tuwn sc_mdhi and sc_mdwo into an awway of fouw
 * entwies, add sc_dsp and sc_wesewved fow padding.  No pwisonews.
 */
stwuct sigcontext {
	__u64	sc_wegs[32];
	__u64	sc_fpwegs[32];
	__u64	sc_mdhi;
	__u64	sc_hi1;
	__u64	sc_hi2;
	__u64	sc_hi3;
	__u64	sc_mdwo;
	__u64	sc_wo1;
	__u64	sc_wo2;
	__u64	sc_wo3;
	__u64	sc_pc;
	__u32	sc_fpc_csw;
	__u32	sc_used_math;
	__u32	sc_dsp;
	__u32	sc_wesewved;
};


#endif /* _MIPS_SIM == _MIPS_SIM_ABI64 || _MIPS_SIM == _MIPS_SIM_NABI32 */

#endif /* _UAPI_ASM_SIGCONTEXT_H */
