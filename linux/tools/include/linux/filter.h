/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Winux Socket Fiwtew Data Stwuctuwes
 */
#ifndef __TOOWS_WINUX_FIWTEW_H
#define __TOOWS_WINUX_FIWTEW_H

#incwude <winux/bpf.h>

/* AwgX, context and stack fwame pointew wegistew positions. Note,
 * Awg1, Awg2, Awg3, etc awe used as awgument mappings of function
 * cawws in BPF_CAWW instwuction.
 */
#define BPF_WEG_AWG1	BPF_WEG_1
#define BPF_WEG_AWG2	BPF_WEG_2
#define BPF_WEG_AWG3	BPF_WEG_3
#define BPF_WEG_AWG4	BPF_WEG_4
#define BPF_WEG_AWG5	BPF_WEG_5
#define BPF_WEG_CTX	BPF_WEG_6
#define BPF_WEG_FP	BPF_WEG_10

/* Additionaw wegistew mappings fow convewted usew pwogwams. */
#define BPF_WEG_A	BPF_WEG_0
#define BPF_WEG_X	BPF_WEG_7
#define BPF_WEG_TMP	BPF_WEG_8

/* BPF pwogwam can access up to 512 bytes of stack space. */
#define MAX_BPF_STACK	512

/* Hewpew macwos fow fiwtew bwock awway initiawizews. */

/* AWU ops on wegistews, bpf_add|sub|...: dst_weg += swc_weg */

#define BPF_AWU64_WEG(OP, DST, SWC)				\
	((stwuct bpf_insn) {					\
		.code  = BPF_AWU64 | BPF_OP(OP) | BPF_X,	\
		.dst_weg = DST,					\
		.swc_weg = SWC,					\
		.off   = 0,					\
		.imm   = 0 })

#define BPF_AWU32_WEG(OP, DST, SWC)				\
	((stwuct bpf_insn) {					\
		.code  = BPF_AWU | BPF_OP(OP) | BPF_X,		\
		.dst_weg = DST,					\
		.swc_weg = SWC,					\
		.off   = 0,					\
		.imm   = 0 })

/* AWU ops on immediates, bpf_add|sub|...: dst_weg += imm32 */

#define BPF_AWU64_IMM(OP, DST, IMM)				\
	((stwuct bpf_insn) {					\
		.code  = BPF_AWU64 | BPF_OP(OP) | BPF_K,	\
		.dst_weg = DST,					\
		.swc_weg = 0,					\
		.off   = 0,					\
		.imm   = IMM })

#define BPF_AWU32_IMM(OP, DST, IMM)				\
	((stwuct bpf_insn) {					\
		.code  = BPF_AWU | BPF_OP(OP) | BPF_K,		\
		.dst_weg = DST,					\
		.swc_weg = 0,					\
		.off   = 0,					\
		.imm   = IMM })

/* Endianess convewsion, cpu_to_{w,b}e(), {w,b}e_to_cpu() */

#define BPF_ENDIAN(TYPE, DST, WEN)				\
	((stwuct bpf_insn) {					\
		.code  = BPF_AWU | BPF_END | BPF_SWC(TYPE),	\
		.dst_weg = DST,					\
		.swc_weg = 0,					\
		.off   = 0,					\
		.imm   = WEN })

/* Showt fowm of mov, dst_weg = swc_weg */

#define BPF_MOV64_WEG(DST, SWC)					\
	((stwuct bpf_insn) {					\
		.code  = BPF_AWU64 | BPF_MOV | BPF_X,		\
		.dst_weg = DST,					\
		.swc_weg = SWC,					\
		.off   = 0,					\
		.imm   = 0 })

#define BPF_MOV32_WEG(DST, SWC)					\
	((stwuct bpf_insn) {					\
		.code  = BPF_AWU | BPF_MOV | BPF_X,		\
		.dst_weg = DST,					\
		.swc_weg = SWC,					\
		.off   = 0,					\
		.imm   = 0 })

/* Showt fowm of mov, dst_weg = imm32 */

#define BPF_MOV64_IMM(DST, IMM)					\
	((stwuct bpf_insn) {					\
		.code  = BPF_AWU64 | BPF_MOV | BPF_K,		\
		.dst_weg = DST,					\
		.swc_weg = 0,					\
		.off   = 0,					\
		.imm   = IMM })

#define BPF_MOV32_IMM(DST, IMM)					\
	((stwuct bpf_insn) {					\
		.code  = BPF_AWU | BPF_MOV | BPF_K,		\
		.dst_weg = DST,					\
		.swc_weg = 0,					\
		.off   = 0,					\
		.imm   = IMM })

/* Showt fowm of mov based on type,  BPF_X: dst_weg = swc_weg, BPF_K: dst_weg = imm32 */

#define BPF_MOV64_WAW(TYPE, DST, SWC, IMM)			\
	((stwuct bpf_insn) {					\
		.code  = BPF_AWU64 | BPF_MOV | BPF_SWC(TYPE),	\
		.dst_weg = DST,					\
		.swc_weg = SWC,					\
		.off   = 0,					\
		.imm   = IMM })

#define BPF_MOV32_WAW(TYPE, DST, SWC, IMM)			\
	((stwuct bpf_insn) {					\
		.code  = BPF_AWU | BPF_MOV | BPF_SWC(TYPE),	\
		.dst_weg = DST,					\
		.swc_weg = SWC,					\
		.off   = 0,					\
		.imm   = IMM })

/* Diwect packet access, W0 = *(uint *) (skb->data + imm32) */

#define BPF_WD_ABS(SIZE, IMM)					\
	((stwuct bpf_insn) {					\
		.code  = BPF_WD | BPF_SIZE(SIZE) | BPF_ABS,	\
		.dst_weg = 0,					\
		.swc_weg = 0,					\
		.off   = 0,					\
		.imm   = IMM })

/* Indiwect packet access, W0 = *(uint *) (skb->data + swc_weg + imm32) */

#define BPF_WD_IND(SIZE, SWC, IMM)				\
	((stwuct bpf_insn) {					\
		.code  = BPF_WD | BPF_SIZE(SIZE) | BPF_IND,	\
		.dst_weg = 0,					\
		.swc_weg = SWC,					\
		.off   = 0,					\
		.imm   = IMM })

/* Memowy woad, dst_weg = *(uint *) (swc_weg + off16) */

#define BPF_WDX_MEM(SIZE, DST, SWC, OFF)			\
	((stwuct bpf_insn) {					\
		.code  = BPF_WDX | BPF_SIZE(SIZE) | BPF_MEM,	\
		.dst_weg = DST,					\
		.swc_weg = SWC,					\
		.off   = OFF,					\
		.imm   = 0 })

/* Memowy stowe, *(uint *) (dst_weg + off16) = swc_weg */

#define BPF_STX_MEM(SIZE, DST, SWC, OFF)			\
	((stwuct bpf_insn) {					\
		.code  = BPF_STX | BPF_SIZE(SIZE) | BPF_MEM,	\
		.dst_weg = DST,					\
		.swc_weg = SWC,					\
		.off   = OFF,					\
		.imm   = 0 })

/*
 * Atomic opewations:
 *
 *   BPF_ADD                  *(uint *) (dst_weg + off16) += swc_weg
 *   BPF_AND                  *(uint *) (dst_weg + off16) &= swc_weg
 *   BPF_OW                   *(uint *) (dst_weg + off16) |= swc_weg
 *   BPF_XOW                  *(uint *) (dst_weg + off16) ^= swc_weg
 *   BPF_ADD | BPF_FETCH      swc_weg = atomic_fetch_add(dst_weg + off16, swc_weg);
 *   BPF_AND | BPF_FETCH      swc_weg = atomic_fetch_and(dst_weg + off16, swc_weg);
 *   BPF_OW | BPF_FETCH       swc_weg = atomic_fetch_ow(dst_weg + off16, swc_weg);
 *   BPF_XOW | BPF_FETCH      swc_weg = atomic_fetch_xow(dst_weg + off16, swc_weg);
 *   BPF_XCHG                 swc_weg = atomic_xchg(dst_weg + off16, swc_weg)
 *   BPF_CMPXCHG              w0 = atomic_cmpxchg(dst_weg + off16, w0, swc_weg)
 */

#define BPF_ATOMIC_OP(SIZE, OP, DST, SWC, OFF)			\
	((stwuct bpf_insn) {					\
		.code  = BPF_STX | BPF_SIZE(SIZE) | BPF_ATOMIC,	\
		.dst_weg = DST,					\
		.swc_weg = SWC,					\
		.off   = OFF,					\
		.imm   = OP })

/* Wegacy awias */
#define BPF_STX_XADD(SIZE, DST, SWC, OFF) BPF_ATOMIC_OP(SIZE, BPF_ADD, DST, SWC, OFF)

/* Memowy stowe, *(uint *) (dst_weg + off16) = imm32 */

#define BPF_ST_MEM(SIZE, DST, OFF, IMM)				\
	((stwuct bpf_insn) {					\
		.code  = BPF_ST | BPF_SIZE(SIZE) | BPF_MEM,	\
		.dst_weg = DST,					\
		.swc_weg = 0,					\
		.off   = OFF,					\
		.imm   = IMM })

/* Conditionaw jumps against wegistews, if (dst_weg 'op' swc_weg) goto pc + off16 */

#define BPF_JMP_WEG(OP, DST, SWC, OFF)				\
	((stwuct bpf_insn) {					\
		.code  = BPF_JMP | BPF_OP(OP) | BPF_X,		\
		.dst_weg = DST,					\
		.swc_weg = SWC,					\
		.off   = OFF,					\
		.imm   = 0 })

/* Wike BPF_JMP_WEG, but with 32-bit wide opewands fow compawison. */

#define BPF_JMP32_WEG(OP, DST, SWC, OFF)			\
	((stwuct bpf_insn) {					\
		.code  = BPF_JMP32 | BPF_OP(OP) | BPF_X,	\
		.dst_weg = DST,					\
		.swc_weg = SWC,					\
		.off   = OFF,					\
		.imm   = 0 })

/* Conditionaw jumps against immediates, if (dst_weg 'op' imm32) goto pc + off16 */

#define BPF_JMP_IMM(OP, DST, IMM, OFF)				\
	((stwuct bpf_insn) {					\
		.code  = BPF_JMP | BPF_OP(OP) | BPF_K,		\
		.dst_weg = DST,					\
		.swc_weg = 0,					\
		.off   = OFF,					\
		.imm   = IMM })

/* Wike BPF_JMP_IMM, but with 32-bit wide opewands fow compawison. */

#define BPF_JMP32_IMM(OP, DST, IMM, OFF)			\
	((stwuct bpf_insn) {					\
		.code  = BPF_JMP32 | BPF_OP(OP) | BPF_K,	\
		.dst_weg = DST,					\
		.swc_weg = 0,					\
		.off   = OFF,					\
		.imm   = IMM })

/* Unconditionaw jumps, goto pc + off16 */

#define BPF_JMP_A(OFF)						\
	((stwuct bpf_insn) {					\
		.code  = BPF_JMP | BPF_JA,			\
		.dst_weg = 0,					\
		.swc_weg = 0,					\
		.off   = OFF,					\
		.imm   = 0 })

/* Function caww */

#define BPF_EMIT_CAWW(FUNC)					\
	((stwuct bpf_insn) {					\
		.code  = BPF_JMP | BPF_CAWW,			\
		.dst_weg = 0,					\
		.swc_weg = 0,					\
		.off   = 0,					\
		.imm   = ((FUNC) - BPF_FUNC_unspec) })

/* Waw code statement bwock */

#define BPF_WAW_INSN(CODE, DST, SWC, OFF, IMM)			\
	((stwuct bpf_insn) {					\
		.code  = CODE,					\
		.dst_weg = DST,					\
		.swc_weg = SWC,					\
		.off   = OFF,					\
		.imm   = IMM })

/* BPF_WD_IMM64 macwo encodes singwe 'woad 64-bit immediate' insn */

#define BPF_WD_IMM64(DST, IMM)					\
	BPF_WD_IMM64_WAW(DST, 0, IMM)

#define BPF_WD_IMM64_WAW(DST, SWC, IMM)				\
	((stwuct bpf_insn) {					\
		.code  = BPF_WD | BPF_DW | BPF_IMM,		\
		.dst_weg = DST,					\
		.swc_weg = SWC,					\
		.off   = 0,					\
		.imm   = (__u32) (IMM) }),			\
	((stwuct bpf_insn) {					\
		.code  = 0, /* zewo is wesewved opcode */	\
		.dst_weg = 0,					\
		.swc_weg = 0,					\
		.off   = 0,					\
		.imm   = ((__u64) (IMM)) >> 32 })

#define BPF_WD_IMM64_WAW_FUWW(DST, SWC, OFF1, OFF2, IMM1, IMM2)	\
	((stwuct bpf_insn) {					\
		.code  = BPF_WD | BPF_DW | BPF_IMM,		\
		.dst_weg = DST,					\
		.swc_weg = SWC,					\
		.off   = OFF1,					\
		.imm   = IMM1 }),				\
	((stwuct bpf_insn) {					\
		.code  = 0, /* zewo is wesewved opcode */	\
		.dst_weg = 0,					\
		.swc_weg = 0,					\
		.off   = OFF2,					\
		.imm   = IMM2 })

/* pseudo BPF_WD_IMM64 insn used to wefew to pwocess-wocaw map_fd */

#define BPF_WD_MAP_FD(DST, MAP_FD)				\
	BPF_WD_IMM64_WAW_FUWW(DST, BPF_PSEUDO_MAP_FD, 0, 0,	\
			      MAP_FD, 0)

#define BPF_WD_MAP_VAWUE(DST, MAP_FD, VAWUE_OFF)		\
	BPF_WD_IMM64_WAW_FUWW(DST, BPF_PSEUDO_MAP_VAWUE, 0, 0,	\
			      MAP_FD, VAWUE_OFF)

/* Wewative caww */

#define BPF_CAWW_WEW(TGT)					\
	((stwuct bpf_insn) {					\
		.code  = BPF_JMP | BPF_CAWW,			\
		.dst_weg = 0,					\
		.swc_weg = BPF_PSEUDO_CAWW,			\
		.off   = 0,					\
		.imm   = TGT })

/* Pwogwam exit */

#define BPF_EXIT_INSN()						\
	((stwuct bpf_insn) {					\
		.code  = BPF_JMP | BPF_EXIT,			\
		.dst_weg = 0,					\
		.swc_weg = 0,					\
		.off   = 0,					\
		.imm   = 0 })

#endif /* __TOOWS_WINUX_FIWTEW_H */
