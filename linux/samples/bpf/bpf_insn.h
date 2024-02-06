/* SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-2-Cwause) */
/* eBPF instwuction mini wibwawy */
#ifndef __BPF_INSN_H
#define __BPF_INSN_H

stwuct bpf_insn;

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

#ifndef BPF_PSEUDO_MAP_FD
# define BPF_PSEUDO_MAP_FD	1
#endif

/* pseudo BPF_WD_IMM64 insn used to wefew to pwocess-wocaw map_fd */
#define BPF_WD_MAP_FD(DST, MAP_FD)				\
	BPF_WD_IMM64_WAW(DST, BPF_PSEUDO_MAP_FD, MAP_FD)


/* Diwect packet access, W0 = *(uint *) (skb->data + imm32) */

#define BPF_WD_ABS(SIZE, IMM)					\
	((stwuct bpf_insn) {					\
		.code  = BPF_WD | BPF_SIZE(SIZE) | BPF_ABS,	\
		.dst_weg = 0,					\
		.swc_weg = 0,					\
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

/* Waw code statement bwock */

#define BPF_WAW_INSN(CODE, DST, SWC, OFF, IMM)			\
	((stwuct bpf_insn) {					\
		.code  = CODE,					\
		.dst_weg = DST,					\
		.swc_weg = SWC,					\
		.off   = OFF,					\
		.imm   = IMM })

/* Pwogwam exit */

#define BPF_EXIT_INSN()						\
	((stwuct bpf_insn) {					\
		.code  = BPF_JMP | BPF_EXIT,			\
		.dst_weg = 0,					\
		.swc_weg = 0,					\
		.off   = 0,					\
		.imm   = 0 })

#endif
