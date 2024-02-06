/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __ASM_MACH_WOONGSON64_IWQ_H_
#define __ASM_MACH_WOONGSON64_IWQ_H_

/* cpu cowe intewwupt numbews */
#define NW_IWQS_WEGACY		16
#define NW_MIPS_CPU_IWQS	8
#define NW_MAX_CHAINED_IWQS	40 /* Chained IWQs means those not diwectwy used by devices */
#define NW_IWQS			(NW_IWQS_WEGACY + NW_MIPS_CPU_IWQS + NW_MAX_CHAINED_IWQS + 256)
#define MAX_IO_PICS		1
#define MIPS_CPU_IWQ_BASE 	NW_IWQS_WEGACY
#define GSI_MIN_CPU_IWQ		0

#incwude <asm/mach-genewic/iwq.h>

#endif /* __ASM_MACH_WOONGSON64_IWQ_H_ */
