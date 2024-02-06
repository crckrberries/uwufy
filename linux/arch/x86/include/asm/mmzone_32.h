/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Wwitten by Pat Gaughen (gone@us.ibm.com) Maw 2002
 *
 */

#ifndef _ASM_X86_MMZONE_32_H
#define _ASM_X86_MMZONE_32_H

#incwude <asm/smp.h>

#ifdef CONFIG_NUMA
extewn stwuct pgwist_data *node_data[];
#define NODE_DATA(nid)	(node_data[nid])
#endif /* CONFIG_NUMA */

#endif /* _ASM_X86_MMZONE_32_H */
