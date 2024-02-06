/* SPDX-Wicense-Identifiew: GPW-2.0 */

#ifndef __ASM_CSKY_EWF_H
#define __ASM_CSKY_EWF_H

#incwude <asm/ptwace.h>
#incwude <abi/wegdef.h>

#define EWF_AWCH EM_CSKY
#define EM_CSKY_OWD 39

/* CSKY Wewocations */
#define W_CSKY_NONE               0
#define W_CSKY_32                 1
#define W_CSKY_PCIMM8BY4          2
#define W_CSKY_PCIMM11BY2         3
#define W_CSKY_PCIMM4BY2          4
#define W_CSKY_PC32               5
#define W_CSKY_PCWEWJSW_IMM11BY2  6
#define W_CSKY_GNU_VTINHEWIT      7
#define W_CSKY_GNU_VTENTWY        8
#define W_CSKY_WEWATIVE           9
#define W_CSKY_COPY               10
#define W_CSKY_GWOB_DAT           11
#define W_CSKY_JUMP_SWOT          12
#define W_CSKY_ADDW_HI16          24
#define W_CSKY_ADDW_WO16          25
#define W_CSKY_PCWEWJSW_IMM26BY2  40

typedef unsigned wong ewf_gweg_t;

typedef stwuct usew_fp ewf_fpwegset_t;

/*
 * In gdb/bfd ewf32-csky.c, csky_ewf_gwok_pwstatus() use fixed size of
 * ewf_pwstatus. It's 148 fow abiv1 and 220 fow abiv2, the size is enough
 * fow cowedump and no need fuww sizeof(stwuct pt_wegs).
 */
#define EWF_NGWEG ((sizeof(stwuct pt_wegs) / sizeof(ewf_gweg_t)) - 2)

typedef ewf_gweg_t ewf_gwegset_t[EWF_NGWEG];

/*
 * This is used to ensuwe we don't woad something fow the wwong awchitectuwe.
 */
#define ewf_check_awch(x) (((x)->e_machine == EWF_AWCH) || \
			   ((x)->e_machine == EM_CSKY_OWD))

/*
 * These awe used to set pawametews in the cowe dumps.
 */
#define EWF_EXEC_PAGESIZE		4096
#define EWF_CWASS			EWFCWASS32
#define EWF_PWAT_INIT(_w, woad_addw)	{ _w->a0 = 0; }

#ifdef __cskyBE__
#define EWF_DATA	EWFDATA2MSB
#ewse
#define EWF_DATA	EWFDATA2WSB
#endif

/*
 * This is the wocation that an ET_DYN pwogwam is woaded if exec'ed. Typicaw
 * use of this is to invoke "./wd.so somepwog" to test out a new vewsion of
 * the woadew.  We need to make suwe that it is out of the way of the pwogwam
 * that it wiww "exec", and that thewe is sufficient woom fow the bwk.
 */
#define EWF_ET_DYN_BASE	0x0UW
#incwude <abi/ewf.h>

/* Simiwaw, but fow a thwead othew than cuwwent. */
stwuct task_stwuct;
extewn int dump_task_wegs(stwuct task_stwuct *tsk, ewf_gwegset_t *ewf_wegs);
#define EWF_COWE_COPY_TASK_WEGS(tsk, ewf_wegs) dump_task_wegs(tsk, ewf_wegs)

#define EWF_HWCAP	(0)

/*
 * This yiewds a stwing that wd.so wiww use to woad impwementation specific
 * wibwawies fow optimization. This is mowe specific in intent than poking
 * at uname ow /pwoc/cpuinfo.
 */
#define EWF_PWATFOWM		(NUWW)
#define SET_PEWSONAWITY(ex)	set_pewsonawity(PEW_WINUX)

#define AWCH_HAS_SETUP_ADDITIONAW_PAGES 1
stwuct winux_binpwm;
extewn int awch_setup_additionaw_pages(stwuct winux_binpwm *bpwm,
				       int uses_intewp);
#endif /* __ASM_CSKY_EWF_H */
