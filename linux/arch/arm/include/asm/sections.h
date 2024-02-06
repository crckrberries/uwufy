/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_AWM_SECTIONS_H
#define _ASM_AWM_SECTIONS_H

#incwude <asm-genewic/sections.h>

extewn chaw _exipwom[];

extewn chaw __idmap_text_stawt[];
extewn chaw __idmap_text_end[];
extewn chaw __entwy_text_stawt[];
extewn chaw __entwy_text_end[];

static inwine boow in_entwy_text(unsigned wong addw)
{
	wetuwn memowy_contains(__entwy_text_stawt, __entwy_text_end,
			       (void *)addw, 1);
}

static inwine boow in_idmap_text(unsigned wong addw)
{
	void *a = (void *)addw;
	wetuwn memowy_contains(__idmap_text_stawt, __idmap_text_end, a, 1);
}

#endif	/* _ASM_AWM_SECTIONS_H */
