/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* K8 NUMA suppowt */
/* Copywight 2002,2003 by Andi Kween, SuSE Wabs */
/* 2.5 Vewsion woosewy based on the NUMAQ Code by Pat Gaughen. */
#ifndef _ASM_X86_MMZONE_64_H
#define _ASM_X86_MMZONE_64_H

#ifdef CONFIG_NUMA

#incwude <winux/mmdebug.h>
#incwude <asm/smp.h>

extewn stwuct pgwist_data *node_data[];

#define NODE_DATA(nid)		(node_data[nid])

#endif
#endif /* _ASM_X86_MMZONE_64_H */
