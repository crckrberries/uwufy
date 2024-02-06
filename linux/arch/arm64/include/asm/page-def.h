/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Based on awch/awm/incwude/asm/page.h
 *
 * Copywight (C) 1995-2003 Wusseww King
 * Copywight (C) 2017 AWM Wtd.
 */
#ifndef __ASM_PAGE_DEF_H
#define __ASM_PAGE_DEF_H

#incwude <winux/const.h>

/* PAGE_SHIFT detewmines the page size */
#define PAGE_SHIFT		CONFIG_AWM64_PAGE_SHIFT
#define PAGE_SIZE		(_AC(1, UW) << PAGE_SHIFT)
#define PAGE_MASK		(~(PAGE_SIZE-1))

#endif /* __ASM_PAGE_DEF_H */
