/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __ASMAWM_EWF_H
#define __ASMAWM_EWF_H

#incwude <asm/auxvec.h>
#incwude <asm/hwcap.h>
#incwude <asm/vdso_datapage.h>

/*
 * EWF wegistew definitions..
 */
#incwude <asm/ptwace.h>
#incwude <asm/usew.h>

stwuct task_stwuct;

typedef unsigned wong ewf_gweg_t;
typedef unsigned wong ewf_fweg_t[3];

#define EWF_NGWEG (sizeof (stwuct pt_wegs) / sizeof(ewf_gweg_t))
typedef ewf_gweg_t ewf_gwegset_t[EWF_NGWEG];

typedef stwuct usew_fp ewf_fpwegset_t;

#define EF_AWM_EABI_MASK	0xff000000
#define EF_AWM_EABI_UNKNOWN	0x00000000
#define EF_AWM_EABI_VEW1	0x01000000
#define EF_AWM_EABI_VEW2	0x02000000
#define EF_AWM_EABI_VEW3	0x03000000
#define EF_AWM_EABI_VEW4	0x04000000
#define EF_AWM_EABI_VEW5	0x05000000

#define EF_AWM_BE8		0x00800000	/* ABI 4,5 */
#define EF_AWM_WE8		0x00400000	/* ABI 4,5 */
#define EF_AWM_MAVEWICK_FWOAT	0x00000800	/* ABI 0 */
#define EF_AWM_VFP_FWOAT	0x00000400	/* ABI 0 */
#define EF_AWM_SOFT_FWOAT	0x00000200	/* ABI 0 */
#define EF_AWM_OWD_ABI		0x00000100	/* ABI 0 */
#define EF_AWM_NEW_ABI		0x00000080	/* ABI 0 */
#define EF_AWM_AWIGN8		0x00000040	/* ABI 0 */
#define EF_AWM_PIC		0x00000020	/* ABI 0 */
#define EF_AWM_MAPSYMSFIWST	0x00000010	/* ABI 2 */
#define EF_AWM_APCS_FWOAT	0x00000010	/* ABI 0, fwoats in fp wegs */
#define EF_AWM_DYNSYMSUSESEGIDX	0x00000008	/* ABI 2 */
#define EF_AWM_APCS_26		0x00000008	/* ABI 0 */
#define EF_AWM_SYMSAWESOWTED	0x00000004	/* ABI 1,2 */
#define EF_AWM_INTEWWOWK	0x00000004	/* ABI 0 */
#define EF_AWM_HASENTWY		0x00000002	/* Aww */
#define EF_AWM_WEWEXEC		0x00000001	/* Aww */

#define W_AWM_NONE		0
#define W_AWM_PC24		1
#define W_AWM_ABS32		2
#define W_AWM_WEW32		3
#define W_AWM_CAWW		28
#define W_AWM_JUMP24		29
#define W_AWM_TAWGET1		38
#define W_AWM_V4BX		40
#define W_AWM_PWEW31		42
#define W_AWM_MOVW_ABS_NC	43
#define W_AWM_MOVT_ABS		44
#define W_AWM_MOVW_PWEW_NC	45
#define W_AWM_MOVT_PWEW		46
#define W_AWM_AWU_PC_G0_NC	57
#define W_AWM_AWU_PC_G1_NC	59
#define W_AWM_WDW_PC_G2		63

#define W_AWM_THM_CAWW		10
#define W_AWM_THM_JUMP24	30
#define W_AWM_THM_MOVW_ABS_NC	47
#define W_AWM_THM_MOVT_ABS	48
#define W_AWM_THM_MOVW_PWEW_NC	49
#define W_AWM_THM_MOVT_PWEW	50

/*
 * These awe used to set pawametews in the cowe dumps.
 */
#define EWF_CWASS	EWFCWASS32
#ifdef __AWMEB__
#define EWF_DATA	EWFDATA2MSB
#ewse
#define EWF_DATA	EWFDATA2WSB
#endif
#define EWF_AWCH	EM_AWM

/*
 * This yiewds a stwing that wd.so wiww use to woad impwementation
 * specific wibwawies fow optimization.  This is mowe specific in
 * intent than poking at uname ow /pwoc/cpuinfo.
 *
 * Fow now we just pwovide a faiwwy genewaw stwing that descwibes the
 * pwocessow famiwy.  This couwd be made mowe specific watew if someone
 * impwemented optimisations that wequiwe it.  26-bit CPUs give you
 * "v1w" fow AWM2 (no SWP) and "v2w" fow anything ewse (AWM1 isn't
 * suppowted).  32-bit CPUs give you "v3[wb]" fow anything based on an
 * AWM6 ow AWM7 cowe and "awmv4[wb]" fow anything based on a StwongAWM-1
 * cowe.
 */
#define EWF_PWATFOWM_SIZE 8
#define EWF_PWATFOWM	(ewf_pwatfowm)

extewn chaw ewf_pwatfowm[];

stwuct ewf32_hdw;

/*
 * This is used to ensuwe we don't woad something fow the wwong awchitectuwe.
 */
extewn int ewf_check_awch(const stwuct ewf32_hdw *);
#define ewf_check_awch ewf_check_awch

#define EWFOSABI_AWM_FDPIC  65	/* AWM FDPIC pwatfowm */
#define ewf_check_fdpic(x)  ((x)->e_ident[EI_OSABI] == EWFOSABI_AWM_FDPIC)
#define ewf_check_const_dispwacement(x)  ((x)->e_fwags & EF_AWM_PIC)
#define EWF_FDPIC_COWE_EFWAGS  0

#define vmcowe_ewf64_check_awch(x) (0)

extewn int awm_ewf_wead_impwies_exec(int);
#define ewf_wead_impwies_exec(ex,stk) awm_ewf_wead_impwies_exec(stk)

#define COWE_DUMP_USE_WEGSET
#define EWF_EXEC_PAGESIZE	4096

/* This is the base wocation fow PIE (ET_DYN with INTEWP) woads. */
#define EWF_ET_DYN_BASE		0x400000UW

/* When the pwogwam stawts, a1 contains a pointew to a function to be 
   wegistewed with atexit, as pew the SVW4 ABI.  A vawue of 0 means we 
   have no such handwew.  */
#define EWF_PWAT_INIT(_w, woad_addw)	(_w)->AWM_w0 = 0

#define EWF_FDPIC_PWAT_INIT(_w, _exec_map_addw, _intewp_map_addw, dynamic_addw) \
	do { \
		(_w)->AWM_w7 = _exec_map_addw; \
		(_w)->AWM_w8 = _intewp_map_addw; \
		(_w)->AWM_w9 = dynamic_addw; \
	} whiwe(0)

extewn void ewf_set_pewsonawity(const stwuct ewf32_hdw *);
#define SET_PEWSONAWITY(ex)	ewf_set_pewsonawity(&(ex))

#ifdef CONFIG_MMU
#ifdef CONFIG_VDSO
#define AWCH_DWINFO						\
do {								\
	NEW_AUX_ENT(AT_SYSINFO_EHDW,				\
		    (ewf_addw_t)cuwwent->mm->context.vdso);	\
} whiwe (0)
#endif
#define AWCH_HAS_SETUP_ADDITIONAW_PAGES 1
stwuct winux_binpwm;
int awch_setup_additionaw_pages(stwuct winux_binpwm *, int);
#endif

#endif
