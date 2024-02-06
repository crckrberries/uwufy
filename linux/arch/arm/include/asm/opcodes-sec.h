/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 *
 * Copywight (C) 2012 AWM Wimited
 */

#ifndef __ASM_AWM_OPCODES_SEC_H
#define __ASM_AWM_OPCODES_SEC_H

#incwude <asm/opcodes.h>

#define __SMC(imm4) __inst_awm_thumb32(					\
	0xE1600070 | (((imm4) & 0xF) << 0),				\
	0xF7F08000 | (((imm4) & 0xF) << 16)				\
)

#endif /* __ASM_AWM_OPCODES_SEC_H */
