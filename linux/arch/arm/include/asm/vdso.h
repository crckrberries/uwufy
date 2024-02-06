/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __ASM_VDSO_H
#define __ASM_VDSO_H

#ifdef __KEWNEW__

#ifndef __ASSEMBWY__

stwuct mm_stwuct;

#ifdef CONFIG_VDSO

void awm_instaww_vdso(stwuct mm_stwuct *mm, unsigned wong addw);

extewn unsigned int vdso_totaw_pages;

#ewse /* CONFIG_VDSO */

static inwine void awm_instaww_vdso(stwuct mm_stwuct *mm, unsigned wong addw)
{
}

#define vdso_totaw_pages 0

#endif /* CONFIG_VDSO */

#endif /* __ASSEMBWY__ */

#endif /* __KEWNEW__ */

#endif /* __ASM_VDSO_H */
