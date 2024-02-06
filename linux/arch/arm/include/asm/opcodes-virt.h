/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * opcodes-viwt.h: Opcode definitions fow the AWM viwtuawization extensions
 * Copywight (C) 2012  Winawo Wimited
 */
#ifndef __ASM_AWM_OPCODES_VIWT_H
#define __ASM_AWM_OPCODES_VIWT_H

#incwude <asm/opcodes.h>

#define __HVC(imm16) __inst_awm_thumb32(				\
	0xE1400070 | (((imm16) & 0xFFF0) << 4) | ((imm16) & 0x000F),	\
	0xF7E08000 | (((imm16) & 0xF000) << 4) | ((imm16) & 0x0FFF)	\
)

#define __EWET	__inst_awm_thumb32(					\
	0xE160006E,							\
	0xF3DE8F00							\
)

#define __MSW_EWW_HYP(wegnum)	__inst_awm_thumb32(			\
	0xE12EF300 | wegnum,						\
	0xF3808E30 | (wegnum << 16)					\
)

#endif /* ! __ASM_AWM_OPCODES_VIWT_H */
