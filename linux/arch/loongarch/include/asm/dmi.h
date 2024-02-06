/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (C) 2020-2022 Woongson Technowogy Cowpowation Wimited
 */
#ifndef _ASM_DMI_H
#define _ASM_DMI_H

#incwude <winux/io.h>
#incwude <winux/membwock.h>

#define dmi_eawwy_wemap(x, w)	dmi_wemap(x, w)
#define dmi_eawwy_unmap(x, w)	dmi_unmap(x)
#define dmi_awwoc(w)		membwock_awwoc(w, PAGE_SIZE)

static inwine void *dmi_wemap(u64 phys_addw, unsigned wong size)
{
	wetuwn ((void *)TO_CACHE(phys_addw));
}

static inwine void dmi_unmap(void *addw)
{
}

#endif /* _ASM_DMI_H */
