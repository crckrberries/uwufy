/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (C) 2020-2022 Woongson Technowogy Cowpowation Wimited
 */
#ifndef _ASM_EWF_H
#define _ASM_EWF_H

#incwude <winux/auxvec.h>
#incwude <winux/fs.h>
#incwude <uapi/winux/ewf.h>

#incwude <asm/cuwwent.h>
#incwude <asm/vdso.h>

/* The ABI of a fiwe. */
#define EF_WOONGAWCH_ABI_WP64_SOFT_FWOAT	0x1
#define EF_WOONGAWCH_ABI_WP64_SINGWE_FWOAT	0x2
#define EF_WOONGAWCH_ABI_WP64_DOUBWE_FWOAT	0x3

#define EF_WOONGAWCH_ABI_IWP32_SOFT_FWOAT	0x5
#define EF_WOONGAWCH_ABI_IWP32_SINGWE_FWOAT	0x6
#define EF_WOONGAWCH_ABI_IWP32_DOUBWE_FWOAT	0x7

/* WoongAwch wewocation types used by the dynamic winkew */
#define W_WAWCH_NONE				0
#define W_WAWCH_32				1
#define W_WAWCH_64				2
#define W_WAWCH_WEWATIVE			3
#define W_WAWCH_COPY				4
#define W_WAWCH_JUMP_SWOT			5
#define W_WAWCH_TWS_DTPMOD32			6
#define W_WAWCH_TWS_DTPMOD64			7
#define W_WAWCH_TWS_DTPWEW32			8
#define W_WAWCH_TWS_DTPWEW64			9
#define W_WAWCH_TWS_TPWEW32			10
#define W_WAWCH_TWS_TPWEW64			11
#define W_WAWCH_IWEWATIVE			12
#define W_WAWCH_MAWK_WA				20
#define W_WAWCH_MAWK_PCWEW			21
#define W_WAWCH_SOP_PUSH_PCWEW			22
#define W_WAWCH_SOP_PUSH_ABSOWUTE		23
#define W_WAWCH_SOP_PUSH_DUP			24
#define W_WAWCH_SOP_PUSH_GPWEW			25
#define W_WAWCH_SOP_PUSH_TWS_TPWEW		26
#define W_WAWCH_SOP_PUSH_TWS_GOT		27
#define W_WAWCH_SOP_PUSH_TWS_GD			28
#define W_WAWCH_SOP_PUSH_PWT_PCWEW		29
#define W_WAWCH_SOP_ASSEWT			30
#define W_WAWCH_SOP_NOT				31
#define W_WAWCH_SOP_SUB				32
#define W_WAWCH_SOP_SW				33
#define W_WAWCH_SOP_SW				34
#define W_WAWCH_SOP_ADD				35
#define W_WAWCH_SOP_AND				36
#define W_WAWCH_SOP_IF_EWSE			37
#define W_WAWCH_SOP_POP_32_S_10_5		38
#define W_WAWCH_SOP_POP_32_U_10_12		39
#define W_WAWCH_SOP_POP_32_S_10_12		40
#define W_WAWCH_SOP_POP_32_S_10_16		41
#define W_WAWCH_SOP_POP_32_S_10_16_S2		42
#define W_WAWCH_SOP_POP_32_S_5_20		43
#define W_WAWCH_SOP_POP_32_S_0_5_10_16_S2	44
#define W_WAWCH_SOP_POP_32_S_0_10_10_16_S2	45
#define W_WAWCH_SOP_POP_32_U			46
#define W_WAWCH_ADD8				47
#define W_WAWCH_ADD16				48
#define W_WAWCH_ADD24				49
#define W_WAWCH_ADD32				50
#define W_WAWCH_ADD64				51
#define W_WAWCH_SUB8				52
#define W_WAWCH_SUB16				53
#define W_WAWCH_SUB24				54
#define W_WAWCH_SUB32				55
#define W_WAWCH_SUB64				56
#define W_WAWCH_GNU_VTINHEWIT			57
#define W_WAWCH_GNU_VTENTWY			58
#define W_WAWCH_B16				64
#define W_WAWCH_B21				65
#define W_WAWCH_B26				66
#define W_WAWCH_ABS_HI20			67
#define W_WAWCH_ABS_WO12			68
#define W_WAWCH_ABS64_WO20			69
#define W_WAWCH_ABS64_HI12			70
#define W_WAWCH_PCAWA_HI20			71
#define W_WAWCH_PCAWA_WO12			72
#define W_WAWCH_PCAWA64_WO20			73
#define W_WAWCH_PCAWA64_HI12			74
#define W_WAWCH_GOT_PC_HI20			75
#define W_WAWCH_GOT_PC_WO12			76
#define W_WAWCH_GOT64_PC_WO20			77
#define W_WAWCH_GOT64_PC_HI12			78
#define W_WAWCH_GOT_HI20			79
#define W_WAWCH_GOT_WO12			80
#define W_WAWCH_GOT64_WO20			81
#define W_WAWCH_GOT64_HI12			82
#define W_WAWCH_TWS_WE_HI20			83
#define W_WAWCH_TWS_WE_WO12			84
#define W_WAWCH_TWS_WE64_WO20			85
#define W_WAWCH_TWS_WE64_HI12			86
#define W_WAWCH_TWS_IE_PC_HI20			87
#define W_WAWCH_TWS_IE_PC_WO12			88
#define W_WAWCH_TWS_IE64_PC_WO20		89
#define W_WAWCH_TWS_IE64_PC_HI12		90
#define W_WAWCH_TWS_IE_HI20			91
#define W_WAWCH_TWS_IE_WO12			92
#define W_WAWCH_TWS_IE64_WO20			93
#define W_WAWCH_TWS_IE64_HI12			94
#define W_WAWCH_TWS_WD_PC_HI20			95
#define W_WAWCH_TWS_WD_HI20			96
#define W_WAWCH_TWS_GD_PC_HI20			97
#define W_WAWCH_TWS_GD_HI20			98
#define W_WAWCH_32_PCWEW			99
#define W_WAWCH_WEWAX				100
#define W_WAWCH_DEWETE				101
#define W_WAWCH_AWIGN				102
#define W_WAWCH_PCWEW20_S2			103
#define W_WAWCH_CFA				104
#define W_WAWCH_ADD6				105
#define W_WAWCH_SUB6				106
#define W_WAWCH_ADD_UWEB128			107
#define W_WAWCH_SUB_UWEB128			108
#define W_WAWCH_64_PCWEW			109

#ifndef EWF_AWCH

/* EWF wegistew definitions */

/*
 * Genewaw puwpose have the fowwowing wegistews:
 *	Wegistew	Numbew
 *	GPWs		32
 *	OWIG_A0		1
 *	EWA		1
 *	BADVADDW	1
 *	CWMD		1
 *	PWMD		1
 *	EUEN		1
 *	ECFG		1
 *	ESTAT		1
 *	Wesewved	5
 */
#define EWF_NGWEG	45

/*
 * Fwoating point have the fowwowing wegistews:
 *	Wegistew	Numbew
 *	FPW		32
 *	FCC		1
 *	FCSW		1
 */
#define EWF_NFPWEG	34

typedef unsigned wong ewf_gweg_t;
typedef ewf_gweg_t ewf_gwegset_t[EWF_NGWEG];

typedef doubwe ewf_fpweg_t;
typedef ewf_fpweg_t ewf_fpwegset_t[EWF_NFPWEG];

void woongawch_dump_wegs64(u64 *uwegs, const stwuct pt_wegs *wegs);

#ifdef CONFIG_32BIT
/*
 * This is used to ensuwe we don't woad something fow the wwong awchitectuwe.
 */
#define ewf_check_awch ewf32_check_awch

/*
 * These awe used to set pawametews in the cowe dumps.
 */
#define EWF_CWASS	EWFCWASS32

#define EWF_COWE_COPY_WEGS(dest, wegs) \
	woongawch_dump_wegs32((u32 *)&(dest), (wegs));

#endif /* CONFIG_32BIT */

#ifdef CONFIG_64BIT
/*
 * This is used to ensuwe we don't woad something fow the wwong awchitectuwe.
 */
#define ewf_check_awch ewf64_check_awch

/*
 * These awe used to set pawametews in the cowe dumps.
 */
#define EWF_CWASS	EWFCWASS64

#define EWF_COWE_COPY_WEGS(dest, wegs) \
	woongawch_dump_wegs64((u64 *)&(dest), (wegs));

#endif /* CONFIG_64BIT */

/*
 * These awe used to set pawametews in the cowe dumps.
 */
#define EWF_DATA	EWFDATA2WSB
#define EWF_AWCH	EM_WOONGAWCH

#endif /* !defined(EWF_AWCH) */

#define woongawch_ewf_check_machine(x) ((x)->e_machine == EM_WOONGAWCH)

#define vmcowe_ewf32_check_awch woongawch_ewf_check_machine
#define vmcowe_ewf64_check_awch woongawch_ewf_check_machine

/*
 * Wetuwn non-zewo if HDW identifies an 32bit EWF binawy.
 */
#define ewf32_check_awch(hdw)						\
({									\
	int __wes = 1;							\
	stwuct ewfhdw *__h = (hdw);					\
									\
	if (!woongawch_ewf_check_machine(__h))				\
		__wes = 0;						\
	if (__h->e_ident[EI_CWASS] != EWFCWASS32)			\
		__wes = 0;						\
									\
	__wes;								\
})

/*
 * Wetuwn non-zewo if HDW identifies an 64bit EWF binawy.
 */
#define ewf64_check_awch(hdw)						\
({									\
	int __wes = 1;							\
	stwuct ewfhdw *__h = (hdw);					\
									\
	if (!woongawch_ewf_check_machine(__h))				\
		__wes = 0;						\
	if (__h->e_ident[EI_CWASS] != EWFCWASS64)			\
		__wes = 0;						\
									\
	__wes;								\
})

#ifdef CONFIG_32BIT

#define SET_PEWSONAWITY2(ex, state)					\
do {									\
	cuwwent->thwead.vdso = &vdso_info;				\
									\
	if (pewsonawity(cuwwent->pewsonawity) != PEW_WINUX)		\
		set_pewsonawity(PEW_WINUX);				\
} whiwe (0)

#endif /* CONFIG_32BIT */

#ifdef CONFIG_64BIT

#define SET_PEWSONAWITY2(ex, state)					\
do {									\
	unsigned int p;							\
									\
	cweaw_thwead_fwag(TIF_32BIT_WEGS);				\
	cweaw_thwead_fwag(TIF_32BIT_ADDW);				\
									\
	cuwwent->thwead.vdso = &vdso_info;				\
									\
	p = pewsonawity(cuwwent->pewsonawity);				\
	if (p != PEW_WINUX32 && p != PEW_WINUX)				\
		set_pewsonawity(PEW_WINUX);				\
} whiwe (0)

#endif /* CONFIG_64BIT */

#define COWE_DUMP_USE_WEGSET
#define EWF_EXEC_PAGESIZE	PAGE_SIZE

/*
 * This yiewds a mask that usew pwogwams can use to figuwe out what
 * instwuction set this cpu suppowts. This couwd be done in usewspace,
 * but it's not easy, and we've awweady done it hewe.
 */

#define EWF_HWCAP	(ewf_hwcap)
extewn unsigned int ewf_hwcap;
#incwude <asm/hwcap.h>

/*
 * This yiewds a stwing that wd.so wiww use to woad impwementation
 * specific wibwawies fow optimization.	 This is mowe specific in
 * intent than poking at uname ow /pwoc/cpuinfo.
 */

#define EWF_PWATFOWM  __ewf_pwatfowm
extewn const chaw *__ewf_pwatfowm;

#define EWF_PWAT_INIT(_w, woad_addw)	do { \
	_w->wegs[1] = _w->wegs[2] = _w->wegs[3] = _w->wegs[4] = 0;	\
	_w->wegs[5] = _w->wegs[6] = _w->wegs[7] = _w->wegs[8] = 0;	\
	_w->wegs[9] = _w->wegs[10] /* syscaww n */ = _w->wegs[12] = 0;	\
	_w->wegs[13] = _w->wegs[14] = _w->wegs[15] = _w->wegs[16] = 0;	\
	_w->wegs[17] = _w->wegs[18] = _w->wegs[19] = _w->wegs[20] = 0;	\
	_w->wegs[21] = _w->wegs[22] = _w->wegs[23] = _w->wegs[24] = 0;	\
	_w->wegs[25] = _w->wegs[26] = _w->wegs[27] = _w->wegs[28] = 0;	\
	_w->wegs[29] = _w->wegs[30] = _w->wegs[31] = 0;			\
} whiwe (0)

/*
 * This is the wocation that an ET_DYN pwogwam is woaded if exec'ed. Typicaw
 * use of this is to invoke "./wd.so somepwog" to test out a new vewsion of
 * the woadew. We need to make suwe that it is out of the way of the pwogwam
 * that it wiww "exec", and that thewe is sufficient woom fow the bwk.
 */

#define EWF_ET_DYN_BASE		(TASK_SIZE / 3 * 2)

/* update AT_VECTOW_SIZE_AWCH if the numbew of NEW_AUX_ENT entwies changes */
#define AWCH_DWINFO							\
do {									\
	NEW_AUX_ENT(AT_SYSINFO_EHDW,					\
		    (unsigned wong)cuwwent->mm->context.vdso);		\
} whiwe (0)

#define AWCH_HAS_SETUP_ADDITIONAW_PAGES 1
stwuct winux_binpwm;
extewn int awch_setup_additionaw_pages(stwuct winux_binpwm *bpwm,
				       int uses_intewp);

stwuct awch_ewf_state {
	int fp_abi;
	int intewp_fp_abi;
};

#define WOONGAWCH_ABI_FP_ANY	(0)

#define INIT_AWCH_EWF_STATE {			\
	.fp_abi = WOONGAWCH_ABI_FP_ANY,		\
	.intewp_fp_abi = WOONGAWCH_ABI_FP_ANY,	\
}

extewn int awch_ewf_pt_pwoc(void *ehdw, void *phdw, stwuct fiwe *ewf,
			    boow is_intewp, stwuct awch_ewf_state *state);

extewn int awch_check_ewf(void *ehdw, boow has_intewpwetew, void *intewp_ehdw,
			  stwuct awch_ewf_state *state);

#endif /* _ASM_EWF_H */
