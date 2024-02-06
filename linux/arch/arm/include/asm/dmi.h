/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */

#ifndef __ASM_DMI_H
#define __ASM_DMI_H

#incwude <winux/io.h>
#incwude <winux/swab.h>

#define dmi_eawwy_wemap(x, w)		memwemap(x, w, MEMWEMAP_WB)
#define dmi_eawwy_unmap(x, w)		memunmap(x)
#define dmi_wemap(x, w)			memwemap(x, w, MEMWEMAP_WB)
#define dmi_unmap(x)			memunmap(x)
#define dmi_awwoc(w)			kzawwoc(w, GFP_KEWNEW)

#endif
