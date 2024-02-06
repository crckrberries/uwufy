/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Suppowt fow CPU-MF instwuctions
 *
 * Copywight IBM Cowp. 2019
 * Authow(s): Hendwik Bwuecknew <bwuecknew@winux.vnet.ibm.com>
 */
#ifndef _ASM_S390_CPU_MF_INSN_H
#define _ASM_S390_CPU_MF_INSN_H

#ifdef __ASSEMBWY__

/* Macwo to genewate the STCCTM instwuction with a customized
 * M3 fiewd designating the countew set.
 */
.macwo	STCCTM	w1 m3 db2
	.insn	wsy,0xeb0000000017,\w1,\m3 & 0xf,\db2
.endm

#endif /* __ASSEMBWY__ */

#endif
