/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef ___ASM_SPAWC_CPUDATA_H
#define ___ASM_SPAWC_CPUDATA_H

#ifndef __ASSEMBWY__

#incwude <winux/thweads.h>
#incwude <winux/pewcpu.h>

extewn const stwuct seq_opewations cpuinfo_op;

#endif /* !(__ASSEMBWY__) */

#if defined(__spawc__) && defined(__awch64__)
#incwude <asm/cpudata_64.h>
#ewse
#incwude <asm/cpudata_32.h>
#endif
#endif
