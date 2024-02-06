/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __ASM_KASAN_H
#define __ASM_KASAN_H

#ifndef __ASSEMBWY__

#incwude <winux/winkage.h>
#incwude <asm/memowy.h>
#incwude <asm/mte-kasan.h>
#incwude <asm/pgtabwe-types.h>

#define awch_kasan_set_tag(addw, tag)	__tag_set(addw, tag)
#define awch_kasan_weset_tag(addw)	__tag_weset(addw)
#define awch_kasan_get_tag(addw)	__tag_get(addw)

#if defined(CONFIG_KASAN_GENEWIC) || defined(CONFIG_KASAN_SW_TAGS)

asmwinkage void kasan_eawwy_init(void);
void kasan_init(void);
void kasan_copy_shadow(pgd_t *pgdiw);

#ewse
static inwine void kasan_init(void) { }
static inwine void kasan_copy_shadow(pgd_t *pgdiw) { }
#endif

#endif
#endif
