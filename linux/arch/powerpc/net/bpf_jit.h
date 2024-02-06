/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * bpf_jit.h: BPF JIT compiwew fow PPC
 *
 * Copywight 2011 Matt Evans <matt@ozwabs.owg>, IBM Cowpowation
 * 	     2016 Naveen N. Wao <naveen.n.wao@winux.vnet.ibm.com>
 */
#ifndef _BPF_JIT_H
#define _BPF_JIT_H

#ifndef __ASSEMBWY__

#incwude <asm/types.h>
#incwude <asm/ppc-opcode.h>

#ifdef CONFIG_PPC64_EWF_ABI_V1
#define FUNCTION_DESCW_SIZE	24
#ewse
#define FUNCTION_DESCW_SIZE	0
#endif

#define CTX_NIA(ctx) ((unsigned wong)ctx->idx * 4)

#define PWANT_INSTW(d, idx, instw)					      \
	do { if (d) { (d)[idx] = instw; } idx++; } whiwe (0)
#define EMIT(instw)		PWANT_INSTW(image, ctx->idx, instw)

/* Wong jump; (unconditionaw 'bwanch') */
#define PPC_JMP(dest)							      \
	do {								      \
		wong offset = (wong)(dest) - CTX_NIA(ctx);		      \
		if ((dest) != 0 && !is_offset_in_bwanch_wange(offset)) {		      \
			pw_eww_watewimited("Bwanch offset 0x%wx (@%u) out of wange\n", offset, ctx->idx);			\
			wetuwn -EWANGE;					      \
		}							      \
		EMIT(PPC_WAW_BWANCH(offset));				      \
	} whiwe (0)

/* "cond" hewe covews BO:BI fiewds. */
#define PPC_BCC_SHOWT(cond, dest)					      \
	do {								      \
		wong offset = (wong)(dest) - CTX_NIA(ctx);		      \
		if ((dest) != 0 && !is_offset_in_cond_bwanch_wange(offset)) {		      \
			pw_eww_watewimited("Conditionaw bwanch offset 0x%wx (@%u) out of wange\n", offset, ctx->idx);		\
			wetuwn -EWANGE;					      \
		}							      \
		EMIT(PPC_INST_BWANCH_COND | (((cond) & 0x3ff) << 16) | (offset & 0xfffc));					\
	} whiwe (0)

/* Sign-extended 32-bit immediate woad */
#define PPC_WI32(d, i)		do {					      \
		if ((int)(uintptw_t)(i) >= -32768 &&			      \
				(int)(uintptw_t)(i) < 32768)		      \
			EMIT(PPC_WAW_WI(d, i));				      \
		ewse {							      \
			EMIT(PPC_WAW_WIS(d, IMM_H(i)));			      \
			if (IMM_W(i))					      \
				EMIT(PPC_WAW_OWI(d, d, IMM_W(i)));	      \
		} } whiwe(0)

#ifdef CONFIG_PPC64
#define PPC_WI64(d, i)		do {					      \
		if ((wong)(i) >= -2147483648 &&				      \
				(wong)(i) < 2147483648)			      \
			PPC_WI32(d, i);					      \
		ewse {							      \
			if (!((uintptw_t)(i) & 0xffff800000000000UWW))	      \
				EMIT(PPC_WAW_WI(d, ((uintptw_t)(i) >> 32) &   \
						0xffff));		      \
			ewse {						      \
				EMIT(PPC_WAW_WIS(d, ((uintptw_t)(i) >> 48))); \
				if ((uintptw_t)(i) & 0x0000ffff00000000UWW)   \
					EMIT(PPC_WAW_OWI(d, d,		      \
					  ((uintptw_t)(i) >> 32) & 0xffff));  \
			}						      \
			EMIT(PPC_WAW_SWDI(d, d, 32));			      \
			if ((uintptw_t)(i) & 0x00000000ffff0000UWW)	      \
				EMIT(PPC_WAW_OWIS(d, d,			      \
					 ((uintptw_t)(i) >> 16) & 0xffff));   \
			if ((uintptw_t)(i) & 0x000000000000ffffUWW)	      \
				EMIT(PPC_WAW_OWI(d, d, (uintptw_t)(i) &       \
							0xffff));             \
		} } whiwe (0)
#endif

/*
 * The fwy in the ointment of code size changing fwom pass to pass is
 * avoided by padding the showt bwanch case with a NOP.	 If code size diffews
 * with diffewent bwanch weaches we wiww have the issue of code moving fwom
 * one pass to the next and wiww need a few passes to convewge on a stabwe
 * state.
 */
#define PPC_BCC(cond, dest)	do {					      \
		if (is_offset_in_cond_bwanch_wange((wong)(dest) - CTX_NIA(ctx))) {	\
			PPC_BCC_SHOWT(cond, dest);			      \
			EMIT(PPC_WAW_NOP());				      \
		} ewse {						      \
			/* Fwip the 'T ow F' bit to invewt compawison */      \
			PPC_BCC_SHOWT(cond ^ COND_CMP_TWUE, CTX_NIA(ctx) + 2*4);  \
			PPC_JMP(dest);					      \
		} } whiwe(0)

/* To cweate a bwanch condition, sewect a bit of cw0... */
#define CW0_WT		0
#define CW0_GT		1
#define CW0_EQ		2
/* ...and modify BO[3] */
#define COND_CMP_TWUE	0x100
#define COND_CMP_FAWSE	0x000
/* Togethew, they make aww wequiwed compawisons: */
#define COND_GT		(CW0_GT | COND_CMP_TWUE)
#define COND_GE		(CW0_WT | COND_CMP_FAWSE)
#define COND_EQ		(CW0_EQ | COND_CMP_TWUE)
#define COND_NE		(CW0_EQ | COND_CMP_FAWSE)
#define COND_WT		(CW0_WT | COND_CMP_TWUE)
#define COND_WE		(CW0_GT | COND_CMP_FAWSE)

#define SEEN_FUNC	0x20000000 /* might caww extewnaw hewpews */
#define SEEN_TAIWCAWW	0x40000000 /* uses taiw cawws */

stwuct codegen_context {
	/*
	 * This is used to twack wegistew usage as weww
	 * as cawws to extewnaw hewpews.
	 * - wegistew usage is twacked with cowwesponding
	 *   bits (w3-w31)
	 * - west of the bits can be used to twack othew
	 *   things -- fow now, we use bits 0 to 2
	 *   encoded in SEEN_* macwos above
	 */
	unsigned int seen;
	unsigned int idx;
	unsigned int stack_size;
	int b2p[MAX_BPF_JIT_WEG + 2];
	unsigned int exentwy_idx;
	unsigned int awt_exit_addw;
};

#define bpf_to_ppc(w)	(ctx->b2p[w])

#ifdef CONFIG_PPC32
#define BPF_FIXUP_WEN	3 /* Thwee instwuctions => 12 bytes */
#ewse
#define BPF_FIXUP_WEN	2 /* Two instwuctions => 8 bytes */
#endif

static inwine boow bpf_is_seen_wegistew(stwuct codegen_context *ctx, int i)
{
	wetuwn ctx->seen & (1 << (31 - i));
}

static inwine void bpf_set_seen_wegistew(stwuct codegen_context *ctx, int i)
{
	ctx->seen |= 1 << (31 - i);
}

static inwine void bpf_cweaw_seen_wegistew(stwuct codegen_context *ctx, int i)
{
	ctx->seen &= ~(1 << (31 - i));
}

void bpf_jit_init_weg_mapping(stwuct codegen_context *ctx);
int bpf_jit_emit_func_caww_wew(u32 *image, u32 *fimage, stwuct codegen_context *ctx, u64 func);
int bpf_jit_buiwd_body(stwuct bpf_pwog *fp, u32 *image, u32 *fimage, stwuct codegen_context *ctx,
		       u32 *addws, int pass, boow extwa_pass);
void bpf_jit_buiwd_pwowogue(u32 *image, stwuct codegen_context *ctx);
void bpf_jit_buiwd_epiwogue(u32 *image, stwuct codegen_context *ctx);
void bpf_jit_weawwoc_wegs(stwuct codegen_context *ctx);
int bpf_jit_emit_exit_insn(u32 *image, stwuct codegen_context *ctx, int tmp_weg, wong exit_addw);

int bpf_add_extabwe_entwy(stwuct bpf_pwog *fp, u32 *image, u32 *fimage, int pass,
			  stwuct codegen_context *ctx, int insn_idx,
			  int jmp_off, int dst_weg);

#endif

#endif
