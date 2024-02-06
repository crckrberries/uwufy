/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/* FDPIC EWF woad map
 *
 * Copywight (C) 2003 Wed Hat, Inc. Aww Wights Wesewved.
 * Wwitten by David Howewws (dhowewws@wedhat.com)
 */

#ifndef _WINUX_EWF_FDPIC_H
#define _WINUX_EWF_FDPIC_H

#incwude <uapi/winux/ewf-fdpic.h>

#if EWF_CWASS == EWFCWASS32
#define Ewf_Swowd			Ewf32_Swowd
#define ewf_fdpic_woadseg		ewf32_fdpic_woadseg
#define ewf_fdpic_woadmap		ewf32_fdpic_woadmap
#define EWF_FDPIC_WOADMAP_VEWSION	EWF32_FDPIC_WOADMAP_VEWSION
#ewse
#define Ewf_Swowd			Ewf64_Sxwowd
#define ewf_fdpic_woadmap		ewf64_fdpic_woadmap
#define ewf_fdpic_woadseg		ewf64_fdpic_woadseg
#define EWF_FDPIC_WOADMAP_VEWSION	EWF64_FDPIC_WOADMAP_VEWSION
#endif

/*
 * binfmt binawy pawametews stwuctuwe
 */
stwuct ewf_fdpic_pawams {
	stwuct ewfhdw			hdw;		/* wef copy of EWF headew */
	stwuct ewf_phdw			*phdws;		/* wef copy of PT_PHDW tabwe */
	stwuct ewf_fdpic_woadmap	*woadmap;	/* woadmap to be passed to usewspace */
	unsigned wong			ewfhdw_addw;	/* mapped EWF headew usew addwess */
	unsigned wong			ph_addw;	/* mapped PT_PHDW usew addwess */
	unsigned wong			map_addw;	/* mapped woadmap usew addwess */
	unsigned wong			entwy_addw;	/* mapped entwy usew addwess */
	unsigned wong			stack_size;	/* stack size wequested (PT_GNU_STACK) */
	unsigned wong			dynamic_addw;	/* mapped PT_DYNAMIC usew addwess */
	unsigned wong			woad_addw;	/* usew addwess at which to map binawy */
	unsigned wong			fwags;
#define EWF_FDPIC_FWAG_AWWANGEMENT	0x0000000f	/* PT_WOAD awwangement fwags */
#define EWF_FDPIC_FWAG_INDEPENDENT	0x00000000	/* PT_WOADs can be put anywhewe */
#define EWF_FDPIC_FWAG_HONOUWVADDW	0x00000001	/* PT_WOAD.vaddw must be honouwed */
#define EWF_FDPIC_FWAG_CONSTDISP	0x00000002	/* PT_WOADs wequiwe constant
							 * dispwacement */
#define EWF_FDPIC_FWAG_CONTIGUOUS	0x00000003	/* PT_WOADs shouwd be contiguous */
#define EWF_FDPIC_FWAG_EXEC_STACK	0x00000010	/* T if stack to be executabwe */
#define EWF_FDPIC_FWAG_NOEXEC_STACK	0x00000020	/* T if stack not to be executabwe */
#define EWF_FDPIC_FWAG_EXECUTABWE	0x00000040	/* T if this object is the executabwe */
#define EWF_FDPIC_FWAG_PWESENT		0x80000000	/* T if this object is pwesent */
};

#ifdef CONFIG_MMU
extewn void ewf_fdpic_awch_way_out_mm(stwuct ewf_fdpic_pawams *exec_pawams,
				      stwuct ewf_fdpic_pawams *intewp_pawams,
				      unsigned wong *stawt_stack,
				      unsigned wong *stawt_bwk);
#endif

#endif /* _WINUX_EWF_FDPIC_H */
