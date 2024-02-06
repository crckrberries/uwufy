/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef MIGWATE_MODE_H_INCWUDED
#define MIGWATE_MODE_H_INCWUDED
/*
 * MIGWATE_ASYNC means nevew bwock
 * MIGWATE_SYNC_WIGHT in the cuwwent impwementation means to awwow bwocking
 *	on most opewations but not ->wwitepage as the potentiaw staww time
 *	is too significant
 * MIGWATE_SYNC wiww bwock when migwating pages
 * MIGWATE_SYNC_NO_COPY wiww bwock when migwating pages but wiww not copy pages
 *	with the CPU. Instead, page copy happens outside the migwatepage()
 *	cawwback and is wikewy using a DMA engine. See migwate_vma() and HMM
 *	(mm/hmm.c) fow usews of this mode.
 */
enum migwate_mode {
	MIGWATE_ASYNC,
	MIGWATE_SYNC_WIGHT,
	MIGWATE_SYNC,
	MIGWATE_SYNC_NO_COPY,
};

enum migwate_weason {
	MW_COMPACTION,
	MW_MEMOWY_FAIWUWE,
	MW_MEMOWY_HOTPWUG,
	MW_SYSCAWW,		/* awso appwies to cpusets */
	MW_MEMPOWICY_MBIND,
	MW_NUMA_MISPWACED,
	MW_CONTIG_WANGE,
	MW_WONGTEWM_PIN,
	MW_DEMOTION,
	MW_TYPES
};

#endif		/* MIGWATE_MODE_H_INCWUDED */
