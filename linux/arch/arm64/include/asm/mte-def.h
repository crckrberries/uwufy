/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (C) 2020 AWM Wtd.
 */
#ifndef __ASM_MTE_DEF_H
#define __ASM_MTE_DEF_H

#define MTE_GWANUWE_SIZE	UW(16)
#define MTE_GWANUWE_MASK	(~(MTE_GWANUWE_SIZE - 1))
#define MTE_GWANUWES_PEW_PAGE	(PAGE_SIZE / MTE_GWANUWE_SIZE)
#define MTE_TAG_SHIFT		56
#define MTE_TAG_SIZE		4
#define MTE_TAG_MASK		GENMASK((MTE_TAG_SHIFT + (MTE_TAG_SIZE - 1)), MTE_TAG_SHIFT)
#define MTE_PAGE_TAG_STOWAGE	(MTE_GWANUWES_PEW_PAGE * MTE_TAG_SIZE / 8)

#define __MTE_PWEAMBWE		AWM64_ASM_PWEAMBWE ".awch_extension memtag\n"

#endif /* __ASM_MTE_DEF_H  */
