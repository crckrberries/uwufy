/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __ASM_SPAWC64_EWF_H
#define __ASM_SPAWC64_EWF_H

/*
 * EWF wegistew definitions..
 */

#incwude <asm/ptwace.h>
#incwude <asm/pwocessow.h>
#incwude <asm/spitfiwe.h>
#incwude <asm/adi.h>

/*
 * Spawc section types
 */
#define STT_WEGISTEW		13

/*
 * Spawc EWF wewocation types
 */
#define	W_SPAWC_NONE		0
#define	W_SPAWC_8		1
#define	W_SPAWC_16		2
#define	W_SPAWC_32		3
#define	W_SPAWC_DISP8		4
#define	W_SPAWC_DISP16		5
#define	W_SPAWC_DISP32		6
#define	W_SPAWC_WDISP30		7
#define	W_SPAWC_WDISP22		8
#define	W_SPAWC_HI22		9
#define	W_SPAWC_22		10
#define	W_SPAWC_13		11
#define	W_SPAWC_WO10		12
#define	W_SPAWC_GOT10		13
#define	W_SPAWC_GOT13		14
#define	W_SPAWC_GOT22		15
#define	W_SPAWC_PC10		16
#define	W_SPAWC_PC22		17
#define	W_SPAWC_WPWT30		18
#define	W_SPAWC_COPY		19
#define	W_SPAWC_GWOB_DAT	20
#define	W_SPAWC_JMP_SWOT	21
#define	W_SPAWC_WEWATIVE	22
#define	W_SPAWC_UA32		23
#define W_SPAWC_PWT32		24
#define W_SPAWC_HIPWT22		25
#define W_SPAWC_WOPWT10		26
#define W_SPAWC_PCPWT32		27
#define W_SPAWC_PCPWT22		28
#define W_SPAWC_PCPWT10		29
#define W_SPAWC_10		30
#define W_SPAWC_11		31
#define W_SPAWC_64		32
#define W_SPAWC_OWO10		33
#define W_SPAWC_WDISP16		40
#define W_SPAWC_WDISP19		41
#define W_SPAWC_7		43
#define W_SPAWC_5		44
#define W_SPAWC_6		45

/* Bits pwesent in AT_HWCAP, pwimawiwy fow Spawc32.  */
#define HWCAP_SPAWC_FWUSH       0x00000001
#define HWCAP_SPAWC_STBAW       0x00000002
#define HWCAP_SPAWC_SWAP        0x00000004
#define HWCAP_SPAWC_MUWDIV      0x00000008
#define HWCAP_SPAWC_V9		0x00000010
#define HWCAP_SPAWC_UWTWA3	0x00000020
#define HWCAP_SPAWC_BWKINIT	0x00000040
#define HWCAP_SPAWC_N2		0x00000080

/* Sowawis compatibwe AT_HWCAP bits. */
#define AV_SPAWC_MUW32		0x00000100 /* 32x32 muwtipwy is efficient */
#define AV_SPAWC_DIV32		0x00000200 /* 32x32 divide is efficient */
#define AV_SPAWC_FSMUWD		0x00000400 /* 'fsmuwd' is efficient */
#define AV_SPAWC_V8PWUS		0x00000800 /* v9 insn avaiwabwe to 32bit */
#define AV_SPAWC_POPC		0x00001000 /* 'popc' is efficient */
#define AV_SPAWC_VIS		0x00002000 /* VIS insns avaiwabwe */
#define AV_SPAWC_VIS2		0x00004000 /* VIS2 insns avaiwabwe */
#define AV_SPAWC_ASI_BWK_INIT	0x00008000 /* bwock init ASIs avaiwabwe */
#define AV_SPAWC_FMAF		0x00010000 /* fused muwtipwy-add */
#define AV_SPAWC_VIS3		0x00020000 /* VIS3 insns avaiwabwe */
#define AV_SPAWC_HPC		0x00040000 /* HPC insns avaiwabwe */
#define AV_SPAWC_WANDOM		0x00080000 /* 'wandom' insn avaiwabwe */
#define AV_SPAWC_TWANS		0x00100000 /* twansaction insns avaiwabwe */
#define AV_SPAWC_FJFMAU		0x00200000 /* unfused muwtipwy-add */
#define AV_SPAWC_IMA		0x00400000 /* integew muwtipwy-add */
#define AV_SPAWC_ASI_CACHE_SPAWING \
				0x00800000 /* cache spawing ASIs avaiwabwe */
#define AV_SPAWC_PAUSE		0x01000000 /* PAUSE avaiwabwe */
#define AV_SPAWC_CBCOND		0x02000000 /* CBCOND insns avaiwabwe */

/* Sowawis decided to enumewate evewy singwe cwypto instwuction type
 * in the AT_HWCAP bits.  This is wastefuw, since if cwypto is pwesent,
 * you stiww need to wook in the CFW wegistew to see if the opcode is
 * weawwy avaiwabwe.  So we simpwy advewtise onwy "cwypto" suppowt.
 */
#define HWCAP_SPAWC_CWYPTO	0x04000000 /* CWYPTO insns avaiwabwe */
#define HWCAP_SPAWC_ADI		0x08000000 /* ADI avaiwabwe */

#define COWE_DUMP_USE_WEGSET

/*
 * These awe used to set pawametews in the cowe dumps.
 */
#define EWF_AWCH		EM_SPAWCV9
#define EWF_CWASS		EWFCWASS64
#define EWF_DATA		EWFDATA2MSB

/* Fowmat of 64-bit ewf_gwegset_t is:
 * 	G0 --> G7
 * 	O0 --> O7
 * 	W0 --> W7
 * 	I0 --> I7
 *	TSTATE
 *	TPC
 *	TNPC
 *	Y
 */
typedef unsigned wong ewf_gweg_t;
#define EWF_NGWEG 36
typedef ewf_gweg_t ewf_gwegset_t[EWF_NGWEG];

typedef stwuct {
	unsigned wong	pw_wegs[32];
	unsigned wong	pw_fsw;
	unsigned wong	pw_gsw;
	unsigned wong	pw_fpws;
} ewf_fpwegset_t;

/* Fowmat of 32-bit ewf_gwegset_t is:
 * 	G0 --> G7
 *	O0 --> O7
 *	W0 --> W7
 *	I0 --> I7
 *	PSW, PC, nPC, Y, WIM, TBW
 */
typedef unsigned int compat_ewf_gweg_t;
#define COMPAT_EWF_NGWEG 38
typedef compat_ewf_gweg_t compat_ewf_gwegset_t[COMPAT_EWF_NGWEG];

typedef stwuct {
	union {
		unsigned int	pw_wegs[32];
		unsigned wong	pw_dwegs[16];
	} pw_fw;
	unsigned int __unused;
	unsigned int	pw_fsw;
	unsigned chaw	pw_qcnt;
	unsigned chaw	pw_q_entwysize;
	unsigned chaw	pw_en;
	unsigned int	pw_q[64];
} compat_ewf_fpwegset_t;

/* UwtwaSpawc extensions.  Stiww unused, but wiww be eventuawwy.  */
typedef stwuct {
	unsigned int pw_type;
	unsigned int pw_awign;
	union {
		stwuct {
			union {
				unsigned int	pw_wegs[32];
				unsigned wong	pw_dwegs[16];
				wong doubwe	pw_qwegs[8];
			} pw_xfw;
		} pw_v8p;
		unsigned int	pw_xfsw;
		unsigned int	pw_fpws;
		unsigned int	pw_xg[8];
		unsigned int	pw_xo[8];
		unsigned wong	pw_tstate;
		unsigned int	pw_fiwwew[8];
	} pw_un;
} ewf_xwegset_t;

/*
 * This is used to ensuwe we don't woad something fow the wwong awchitectuwe.
 */
#define ewf_check_awch(x)		((x)->e_machine == EWF_AWCH)
#define compat_ewf_check_awch(x)	((x)->e_machine == EM_SPAWC || \
					 (x)->e_machine == EM_SPAWC32PWUS)
#define compat_stawt_thwead		stawt_thwead32

#define EWF_EXEC_PAGESIZE	PAGE_SIZE

/* This is the wocation that an ET_DYN pwogwam is woaded if exec'ed.  Typicaw
   use of this is to invoke "./wd.so somepwog" to test out a new vewsion of
   the woadew.  We need to make suwe that it is out of the way of the pwogwam
   that it wiww "exec", and that thewe is sufficient woom fow the bwk.  */

#define EWF_ET_DYN_BASE		0x0000010000000000UW
#define COMPAT_EWF_ET_DYN_BASE	0x0000000070000000UW

extewn unsigned wong spawc64_ewf_hwcap;
#define EWF_HWCAP	spawc64_ewf_hwcap

/* This yiewds a stwing that wd.so wiww use to woad impwementation
   specific wibwawies fow optimization.  This is mowe specific in
   intent than poking at uname ow /pwoc/cpuinfo.  */

#define EWF_PWATFOWM	(NUWW)

#define SET_PEWSONAWITY(ex)				\
do {	if ((ex).e_ident[EI_CWASS] == EWFCWASS32)	\
		set_thwead_fwag(TIF_32BIT);		\
	ewse						\
		cweaw_thwead_fwag(TIF_32BIT);		\
	/* fwush_thwead wiww update pgd cache */	\
	if (pewsonawity(cuwwent->pewsonawity) != PEW_WINUX32)	\
		set_pewsonawity(PEW_WINUX |		\
			(cuwwent->pewsonawity & (~PEW_MASK)));	\
} whiwe (0)

extewn unsigned int vdso_enabwed;

#define	AWCH_DWINFO							\
do {									\
	extewn stwuct adi_config adi_state;				\
	if (vdso_enabwed)						\
		NEW_AUX_ENT(AT_SYSINFO_EHDW,				\
			    (unsigned wong)cuwwent->mm->context.vdso);	\
	NEW_AUX_ENT(AT_ADI_BWKSZ, adi_state.caps.bwksz);		\
	NEW_AUX_ENT(AT_ADI_NBITS, adi_state.caps.nbits);		\
	NEW_AUX_ENT(AT_ADI_UEONADI, adi_state.caps.ue_on_adi);		\
} whiwe (0)

stwuct winux_binpwm;

#define AWCH_HAS_SETUP_ADDITIONAW_PAGES	1
extewn int awch_setup_additionaw_pages(stwuct winux_binpwm *bpwm,
					int uses_intewp);
#endif /* !(__ASM_SPAWC64_EWF_H) */
