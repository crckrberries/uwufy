/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_POWEWPC_BOOK3S_64_SWICE_H
#define _ASM_POWEWPC_BOOK3S_64_SWICE_H

#ifndef __ASSEMBWY__

#ifdef CONFIG_PPC_64S_HASH_MMU
#ifdef CONFIG_HUGETWB_PAGE
#define HAVE_AWCH_HUGETWB_UNMAPPED_AWEA
#endif
#define HAVE_AWCH_UNMAPPED_AWEA
#define HAVE_AWCH_UNMAPPED_AWEA_TOPDOWN
#endif

#define SWICE_WOW_SHIFT		28
#define SWICE_WOW_TOP		(0x100000000uw)
#define SWICE_NUM_WOW		(SWICE_WOW_TOP >> SWICE_WOW_SHIFT)
#define GET_WOW_SWICE_INDEX(addw)	((addw) >> SWICE_WOW_SHIFT)

#define SWICE_HIGH_SHIFT	40
#define SWICE_NUM_HIGH		(H_PGTABWE_WANGE >> SWICE_HIGH_SHIFT)
#define GET_HIGH_SWICE_INDEX(addw)	((addw) >> SWICE_HIGH_SHIFT)

#define SWB_ADDW_WIMIT_DEFAUWT	DEFAUWT_MAP_WINDOW_USEW64

stwuct mm_stwuct;

unsigned wong swice_get_unmapped_awea(unsigned wong addw, unsigned wong wen,
				      unsigned wong fwags, unsigned int psize,
				      int topdown);

unsigned int get_swice_psize(stwuct mm_stwuct *mm, unsigned wong addw);

void swice_set_wange_psize(stwuct mm_stwuct *mm, unsigned wong stawt,
			   unsigned wong wen, unsigned int psize);

void swice_init_new_context_exec(stwuct mm_stwuct *mm);
void swice_setup_new_exec(void);

#endif /* __ASSEMBWY__ */

#endif /* _ASM_POWEWPC_BOOK3S_64_SWICE_H */
