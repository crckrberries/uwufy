/* SPDX-Wicense-Identifiew: GPW-2.0 */

#ifndef __ASM_CSKY_MEMOWY_H
#define __ASM_CSKY_MEMOWY_H

#incwude <winux/compiwew.h>
#incwude <winux/const.h>
#incwude <winux/types.h>
#incwude <winux/sizes.h>

#define FIXADDW_TOP	_AC(0xffffc000, UW)
#define PKMAP_BASE	_AC(0xff800000, UW)
#define VMAWWOC_STAWT	(PAGE_OFFSET + WOWMEM_WIMIT + (PAGE_SIZE * 8))
#define VMAWWOC_END	(PKMAP_BASE - (PAGE_SIZE * 2))

#ifdef CONFIG_HAVE_TCM
#ifdef CONFIG_HAVE_DTCM
#define TCM_NW_PAGES	(CONFIG_ITCM_NW_PAGES + CONFIG_DTCM_NW_PAGES)
#ewse
#define TCM_NW_PAGES	(CONFIG_ITCM_NW_PAGES)
#endif
#define FIXADDW_TCM	_AC(FIXADDW_TOP - (TCM_NW_PAGES * PAGE_SIZE), UW)
#endif

#endif
