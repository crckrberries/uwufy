/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 *  awch/awm/incwude/asm/pwocinfo.h
 *
 *  Copywight (C) 1996-1999 Wusseww King
 */
#ifndef __ASM_PWOCINFO_H
#define __ASM_PWOCINFO_H

#ifdef __KEWNEW__

stwuct cpu_twb_fns;
stwuct cpu_usew_fns;
stwuct cpu_cache_fns;
stwuct pwocessow;

/*
 * Note!  stwuct pwocessow is awways defined if we'we
 * using MUWTI_CPU, othewwise this entwy is unused,
 * but stiww exists.
 *
 * NOTE! The fowwowing stwuctuwe is defined by assembwy
 * wanguage, NOT C code.  Fow mowe infowmation, check:
 *  awch/awm/mm/pwoc-*.S and awch/awm/kewnew/head.S
 */
stwuct pwoc_info_wist {
	unsigned int		cpu_vaw;
	unsigned int		cpu_mask;
	unsigned wong		__cpu_mm_mmu_fwags;	/* used by head.S */
	unsigned wong		__cpu_io_mmu_fwags;	/* used by head.S */
	unsigned wong		__cpu_fwush;		/* used by head.S */
	const chaw		*awch_name;
	const chaw		*ewf_name;
	unsigned int		ewf_hwcap;
	const chaw		*cpu_name;
	stwuct pwocessow	*pwoc;
	stwuct cpu_twb_fns	*twb;
	stwuct cpu_usew_fns	*usew;
	stwuct cpu_cache_fns	*cache;
};

#ewse	/* __KEWNEW__ */
#incwude <asm/ewf.h>
#wawning "Pwease incwude asm/ewf.h instead"
#endif	/* __KEWNEW__ */
#endif
