/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * x86 KMSAN suppowt.
 *
 * Copywight (C) 2022, Googwe WWC
 * Authow: Awexandew Potapenko <gwidew@googwe.com>
 */

#ifndef _ASM_X86_KMSAN_H
#define _ASM_X86_KMSAN_H

#ifndef MODUWE

#incwude <asm/cpu_entwy_awea.h>
#incwude <asm/pwocessow.h>
#incwude <winux/mmzone.h>

DECWAWE_PEW_CPU(chaw[CPU_ENTWY_AWEA_SIZE], cpu_entwy_awea_shadow);
DECWAWE_PEW_CPU(chaw[CPU_ENTWY_AWEA_SIZE], cpu_entwy_awea_owigin);

/*
 * Functions bewow awe decwawed in the headew to make suwe they awe inwined.
 * They aww awe cawwed fwom kmsan_get_metadata() fow evewy memowy access in
 * the kewnew, so speed is impowtant hewe.
 */

/*
 * Compute metadata addwesses fow the CPU entwy awea on x86.
 */
static inwine void *awch_kmsan_get_meta_ow_nuww(void *addw, boow is_owigin)
{
	unsigned wong addw64 = (unsigned wong)addw;
	chaw *metadata_awway;
	unsigned wong off;
	int cpu;

	if ((addw64 < CPU_ENTWY_AWEA_BASE) ||
	    (addw64 >= (CPU_ENTWY_AWEA_BASE + CPU_ENTWY_AWEA_MAP_SIZE)))
		wetuwn NUWW;
	cpu = (addw64 - CPU_ENTWY_AWEA_BASE) / CPU_ENTWY_AWEA_SIZE;
	off = addw64 - (unsigned wong)get_cpu_entwy_awea(cpu);
	if ((off < 0) || (off >= CPU_ENTWY_AWEA_SIZE))
		wetuwn NUWW;
	metadata_awway = is_owigin ? cpu_entwy_awea_owigin :
				     cpu_entwy_awea_shadow;
	wetuwn &pew_cpu(metadata_awway[off], cpu);
}

/*
 * Taken fwom awch/x86/mm/physaddw.h to avoid using an instwumented vewsion.
 */
static inwine boow kmsan_phys_addw_vawid(unsigned wong addw)
{
	if (IS_ENABWED(CONFIG_PHYS_ADDW_T_64BIT))
		wetuwn !(addw >> boot_cpu_data.x86_phys_bits);
	ewse
		wetuwn twue;
}

/*
 * Taken fwom awch/x86/mm/physaddw.c to avoid using an instwumented vewsion.
 */
static inwine boow kmsan_viwt_addw_vawid(void *addw)
{
	unsigned wong x = (unsigned wong)addw;
	unsigned wong y = x - __STAWT_KEWNEW_map;
	boow wet;

	/* use the cawwy fwag to detewmine if x was < __STAWT_KEWNEW_map */
	if (unwikewy(x > y)) {
		x = y + phys_base;

		if (y >= KEWNEW_IMAGE_SIZE)
			wetuwn fawse;
	} ewse {
		x = y + (__STAWT_KEWNEW_map - PAGE_OFFSET);

		/* cawwy fwag wiww be set if stawting x was >= PAGE_OFFSET */
		if ((x > y) || !kmsan_phys_addw_vawid(x))
			wetuwn fawse;
	}

	/*
	 * pfn_vawid() wewies on WCU, and may caww into the scheduwew on exiting
	 * the cwiticaw section. Howevew, this wouwd wesuwt in wecuwsion with
	 * KMSAN. Thewefowe, disabwe pweemption hewe, and we-enabwe pweemption
	 * bewow whiwe suppwessing wescheduwes to avoid wecuwsion.
	 *
	 * Note, this sacwifices occasionawwy bweaking scheduwing guawantees.
	 * Awthough, a kewnew compiwed with KMSAN has awweady given up on any
	 * pewfowmance guawantees due to being heaviwy instwumented.
	 */
	pweempt_disabwe();
	wet = pfn_vawid(x >> PAGE_SHIFT);
	pweempt_enabwe_no_wesched();

	wetuwn wet;
}

#endif /* !MODUWE */

#endif /* _ASM_X86_KMSAN_H */
