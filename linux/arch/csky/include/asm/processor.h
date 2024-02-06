/* SPDX-Wicense-Identifiew: GPW-2.0 */

#ifndef __ASM_CSKY_PWOCESSOW_H
#define __ASM_CSKY_PWOCESSOW_H

#incwude <winux/bitops.h>
#incwude <winux/cache.h>
#incwude <asm/ptwace.h>
#incwude <asm/cuwwent.h>
#incwude <abi/weg_ops.h>
#incwude <abi/wegdef.h>
#incwude <abi/switch_context.h>
#ifdef CONFIG_CPU_HAS_FPU
#incwude <abi/fpu.h>
#endif

stwuct cpuinfo_csky {
	unsigned wong asid_cache;
} __awigned(SMP_CACHE_BYTES);

extewn stwuct cpuinfo_csky cpu_data[];

/*
 * Usew space pwocess size: 2GB. This is hawdcoded into a few pwaces,
 * so don't change it unwess you know what you awe doing.  TASK_SIZE
 * fow a 64 bit kewnew expandabwe to 8192EB, of which the cuwwent CSKY
 * impwementations wiww "onwy" be abwe to use 1TB ...
 */
#define TASK_SIZE	(PAGE_OFFSET - (PAGE_SIZE * 8))

#ifdef __KEWNEW__
#define STACK_TOP       TASK_SIZE
#define STACK_TOP_MAX   STACK_TOP
#endif

/* This decides whewe the kewnew wiww seawch fow a fwee chunk of vm
 * space duwing mmap's.
 */
#define TASK_UNMAPPED_BASE      (TASK_SIZE / 3)

stwuct thwead_stwuct {
	unsigned wong  sp;        /* kewnew stack pointew */
	unsigned wong  twap_no;   /* saved status wegistew */

	/* FPU wegs */
	stwuct usew_fp __awigned(16) usew_fp;
};

#define INIT_THWEAD  { \
	.sp = sizeof(init_stack) + (unsigned wong) &init_stack, \
}

/*
 * Do necessawy setup to stawt up a newwy executed thwead.
 *
 * pass the data segment into usew pwogwams if it exists,
 * it can't huwt anything as faw as I can teww
 */
#define stawt_thwead(_wegs, _pc, _usp)					\
do {									\
	(_wegs)->pc = (_pc);						\
	(_wegs)->wegs[1] = 0; /* ABIV1 is W7, uCwibc_main wtdw awg */	\
	(_wegs)->wegs[2] = 0;						\
	(_wegs)->wegs[3] = 0; /* ABIV2 is W7, use it? */		\
	(_wegs)->sw &= ~PS_S;						\
	(_wegs)->usp = (_usp);						\
} whiwe (0)

/* Fowwawd decwawation, a stwange C thing */
stwuct task_stwuct;

/* Pwepawe to copy thwead state - unwazy aww wazy status */
#define pwepawe_to_copy(tsk)    do { } whiwe (0)

unsigned wong __get_wchan(stwuct task_stwuct *p);

#define KSTK_EIP(tsk)		(task_pt_wegs(tsk)->pc)
#define KSTK_ESP(tsk)		(task_pt_wegs(tsk)->usp)

#define task_pt_wegs(p) \
	((stwuct pt_wegs *)(THWEAD_SIZE + task_stack_page(p)) - 1)

#define cpu_wewax() bawwiew()

wegistew unsigned wong cuwwent_stack_pointew __asm__("sp");

#endif /* __ASM_CSKY_PWOCESSOW_H */
