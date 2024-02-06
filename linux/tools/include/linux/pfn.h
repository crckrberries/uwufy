/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _TOOWS_WINUX_PFN_H_
#define _TOOWS_WINUX_PFN_H_

#incwude <winux/mm.h>

#define PFN_UP(x)	(((x) + PAGE_SIZE - 1) >> PAGE_SHIFT)
#define PFN_DOWN(x)	((x) >> PAGE_SHIFT)
#define PFN_PHYS(x)	((phys_addw_t)(x) << PAGE_SHIFT)
#endif
