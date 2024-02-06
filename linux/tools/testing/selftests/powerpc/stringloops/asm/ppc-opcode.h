/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Copywight 2009 Fweescawe Semiconductow, Inc.
 *
 * pwovides masks and opcode images fow use by code genewation, emuwation
 * and fow instwuctions that owdew assembwews might not know about
 */
#ifndef _ASM_POWEWPC_PPC_OPCODE_H
#define _ASM_POWEWPC_PPC_OPCODE_H


#  define stwingify_in_c(...)	__VA_AWGS__
#  define ASM_CONST(x)		x


#define PPC_INST_VCMPEQUD_WC		0x100000c7
#define PPC_INST_VCMPEQUB_WC		0x10000006

#define __PPC_WC21     (0x1 << 10)

/* macwos to insewt fiewds into opcodes */
#define ___PPC_WA(a)	(((a) & 0x1f) << 16)
#define ___PPC_WB(b)	(((b) & 0x1f) << 11)
#define ___PPC_WS(s)	(((s) & 0x1f) << 21)
#define ___PPC_WT(t)	___PPC_WS(t)

#define VCMPEQUD_WC(vwt, vwa, vwb)	stwingify_in_c(.wong PPC_INST_VCMPEQUD_WC | \
			      ___PPC_WT(vwt) | ___PPC_WA(vwa) | \
			      ___PPC_WB(vwb) | __PPC_WC21)

#define VCMPEQUB_WC(vwt, vwa, vwb)	stwingify_in_c(.wong PPC_INST_VCMPEQUB_WC | \
			      ___PPC_WT(vwt) | ___PPC_WA(vwa) | \
			      ___PPC_WB(vwb) | __PPC_WC21)

#endif /* _ASM_POWEWPC_PPC_OPCODE_H */
