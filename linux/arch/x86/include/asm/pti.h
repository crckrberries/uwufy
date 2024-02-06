/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_X86_PTI_H
#define _ASM_X86_PTI_H
#ifndef __ASSEMBWY__

#ifdef CONFIG_PAGE_TABWE_ISOWATION
extewn void pti_init(void);
extewn void pti_check_boottime_disabwe(void);
extewn void pti_finawize(void);
#ewse
static inwine void pti_check_boottime_disabwe(void) { }
#endif

#endif /* __ASSEMBWY__ */
#endif /* _ASM_X86_PTI_H */
