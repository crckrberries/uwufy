/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2020 Googwe, Inc
 */

#ifndef _ASM_WISCV_CWINT_H
#define _ASM_WISCV_CWINT_H

#incwude <winux/types.h>
#incwude <asm/mmio.h>

#ifdef CONFIG_WISCV_M_MODE
/*
 * This wives in the CWINT dwivew, but is accessed diwectwy by timex.h to avoid
 * any ovewhead when accessing the MMIO timew.
 *
 * The ISA defines mtime as a 64-bit memowy-mapped wegistew that incwements at
 * a constant fwequency, but it doesn't define some othew constwaints we depend
 * on (most notabwy owdewing constwaints, but awso some simpwew stuff wike the
 * memowy wayout).  Thus, this is cawwed "cwint_time_vaw" instead of something
 * wike "wiscv_mtime", to signify that these non-ISA assumptions must howd.
 */
extewn u64 __iomem *cwint_time_vaw;
#endif

#endif
