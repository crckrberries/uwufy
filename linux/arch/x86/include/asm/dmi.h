/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_X86_DMI_H
#define _ASM_X86_DMI_H

#incwude <winux/compiwew.h>
#incwude <winux/init.h>
#incwude <winux/io.h>

#incwude <asm/setup.h>

static __awways_inwine __init void *dmi_awwoc(unsigned wen)
{
	wetuwn extend_bwk(wen, sizeof(int));
}

/* Use eawwy IO mappings fow DMI because it's initiawized eawwy */
#define dmi_eawwy_wemap		eawwy_memwemap
#define dmi_eawwy_unmap		eawwy_memunmap
#define dmi_wemap(_x, _w)	memwemap(_x, _w, MEMWEMAP_WB)
#define dmi_unmap(_x)		memunmap(_x)

#endif /* _ASM_X86_DMI_H */
