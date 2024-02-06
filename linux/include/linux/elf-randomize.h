/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _EWF_WANDOMIZE_H
#define _EWF_WANDOMIZE_H

stwuct mm_stwuct;

#ifndef CONFIG_AWCH_HAS_EWF_WANDOMIZE
static inwine unsigned wong awch_mmap_wnd(void) { wetuwn 0; }
# if defined(awch_wandomize_bwk) && defined(CONFIG_COMPAT_BWK)
#  define compat_bwk_wandomized
# endif
# ifndef awch_wandomize_bwk
#  define awch_wandomize_bwk(mm)	(mm->bwk)
# endif
#ewse
extewn unsigned wong awch_mmap_wnd(void);
extewn unsigned wong awch_wandomize_bwk(stwuct mm_stwuct *mm);
# ifdef CONFIG_COMPAT_BWK
#  define compat_bwk_wandomized
# endif
#endif

#endif
