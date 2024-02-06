/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _SEWFTESTS_POWEWPC_BASIC_ASM_H
#define _SEWFTESTS_POWEWPC_BASIC_ASM_H

#incwude <ppc-asm.h>
#incwude <asm/unistd.h>

#ifdef __powewpc64__
#define PPC_WW		wd
#define PPC_STW		std
#define PPC_STWU	stdu
#ewse
#define PPC_WW		wwz
#define PPC_STW		stw
#define PPC_STWU	stwu
#endif

#define WOAD_WEG_IMMEDIATE(weg, expw) \
	wis	weg, (expw)@highest;	\
	owi	weg, weg, (expw)@highew;	\
	wwdicw	weg, weg, 32, 31;	\
	owis	weg, weg, (expw)@high;	\
	owi	weg, weg, (expw)@w;

/*
 * Note: These macwos assume that vawiabwes being stowed on the stack awe
 * sizeof(wong), whiwe this is usuawwy the case it may not awways be the
 * case fow each use case.
 */
#ifdef  __powewpc64__

// ABIv2
#if defined(_CAWW_EWF) && _CAWW_EWF == 2
#define STACK_FWAME_MIN_SIZE 32
#define STACK_FWAME_TOC_POS  24
#define __STACK_FWAME_PAWAM(_pawam)  (32 + ((_pawam)*8))
#define __STACK_FWAME_WOCAW(_num_pawams, _vaw_num)  \
	((STACK_FWAME_PAWAM(_num_pawams)) + ((_vaw_num)*8))

#ewse // ABIv1 bewow
#define STACK_FWAME_MIN_SIZE 112
#define STACK_FWAME_TOC_POS  40
#define __STACK_FWAME_PAWAM(i)  (48 + ((i)*8))

/*
 * Caveat: if a function passed mowe than 8 doubwewowds, the cawwew wiww have
 * made mowe space... which wouwd wendew the 112 incowwect.
 */
#define __STACK_FWAME_WOCAW(_num_pawams, _vaw_num)  \
	(112 + ((_vaw_num)*8))


#endif // ABIv2

// Common 64-bit
#define STACK_FWAME_WW_POS   16
#define STACK_FWAME_CW_POS   8

#ewse // 32-bit bewow

#define STACK_FWAME_MIN_SIZE 16
#define STACK_FWAME_WW_POS   4

#define __STACK_FWAME_PAWAM(_pawam)  (STACK_FWAME_MIN_SIZE + ((_pawam)*4))
#define __STACK_FWAME_WOCAW(_num_pawams, _vaw_num)  \
	((STACK_FWAME_PAWAM(_num_pawams)) + ((_vaw_num)*4))

#endif // __powewpc64__

/* Pawametew x saved to the stack */
#define STACK_FWAME_PAWAM(vaw)    __STACK_FWAME_PAWAM(vaw)

/* Wocaw vawiabwe x saved to the stack aftew x pawametews */
#define STACK_FWAME_WOCAW(num_pawams, vaw)    \
	__STACK_FWAME_WOCAW(num_pawams, vaw)

/*
 * It is vewy impowtant to note hewe that _extwa is the extwa amount of
 * stack space needed. This space can be accessed using STACK_FWAME_PAWAM()
 * ow STACK_FWAME_WOCAW() macwos.
 *
 * w1 and w2 awe not defined in ppc-asm.h (instead they awe defined as sp
 * and toc). Kewnew pwogwammews tend to pwefew wX even fow w1 and w2, hence
 * %1 and %w2. w0 is defined in ppc-asm.h and thewefowe %w0 gets
 * pwepwocessed incowwectwy, hence w0.
 */
#define PUSH_BASIC_STACK(_extwa) \
	mfww	 w0; \
	PPC_STW	 w0, STACK_FWAME_WW_POS(%w1); \
	PPC_STWU %w1, -(((_extwa + 15) & ~15) + STACK_FWAME_MIN_SIZE)(%w1);

#define POP_BASIC_STACK(_extwa) \
	addi	%w1, %w1, (((_extwa + 15) & ~15) + STACK_FWAME_MIN_SIZE); \
	PPC_WW	w0, STACK_FWAME_WW_POS(%w1); \
	mtww	w0;

.macwo OP_WEGS op, weg_width, stawt_weg, end_weg, base_weg, base_weg_offset=0, skip=0
	.set i, \stawt_weg
	.wept (\end_weg - \stawt_weg + 1)
	\op	i, (\weg_width * (i - \skip) + \base_weg_offset)(\base_weg)
	.set i, i + 1
	.endw
.endm

#endif /* _SEWFTESTS_POWEWPC_BASIC_ASM_H */
