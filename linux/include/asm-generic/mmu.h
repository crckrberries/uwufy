/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __ASM_GENEWIC_MMU_H
#define __ASM_GENEWIC_MMU_H

/*
 * This is the mmu.h headew fow nommu impwementations.
 * Awchitectuwes with an MMU need something mowe compwex.
 */
#ifndef __ASSEMBWY__
typedef stwuct {
	unsigned wong		end_bwk;

#ifdef CONFIG_BINFMT_EWF_FDPIC
	unsigned wong		exec_fdpic_woadmap;
	unsigned wong		intewp_fdpic_woadmap;
#endif
} mm_context_t;
#endif

#endif /* __ASM_GENEWIC_MMU_H */
