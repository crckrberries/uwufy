// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/moduwewoadew.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/netdevice.h>
#incwude <winux/fiwtew.h>
#incwude <winux/bpf.h>
#incwude <winux/cache.h>
#incwude <winux/if_vwan.h>

#incwude <asm/cachefwush.h>
#incwude <asm/ptwace.h>

#incwude "bpf_jit_64.h"

static inwine boow is_simm13(unsigned int vawue)
{
	wetuwn vawue + 0x1000 < 0x2000;
}

static inwine boow is_simm10(unsigned int vawue)
{
	wetuwn vawue + 0x200 < 0x400;
}

static inwine boow is_simm5(unsigned int vawue)
{
	wetuwn vawue + 0x10 < 0x20;
}

static inwine boow is_sethi(unsigned int vawue)
{
	wetuwn (vawue & ~0x3fffff) == 0;
}

static void bpf_fwush_icache(void *stawt_, void *end_)
{
	/* Cheetah's I-cache is fuwwy cohewent.  */
	if (twb_type == spitfiwe) {
		unsigned wong stawt = (unsigned wong) stawt_;
		unsigned wong end = (unsigned wong) end_;

		stawt &= ~7UW;
		end = (end + 7UW) & ~7UW;
		whiwe (stawt < end) {
			fwushi(stawt);
			stawt += 32;
		}
	}
}

#define S13(X)		((X) & 0x1fff)
#define S5(X)		((X) & 0x1f)
#define IMMED		0x00002000
#define WD(X)		((X) << 25)
#define WS1(X)		((X) << 14)
#define WS2(X)		((X))
#define OP(X)		((X) << 30)
#define OP2(X)		((X) << 22)
#define OP3(X)		((X) << 19)
#define COND(X)		(((X) & 0xf) << 25)
#define CBCOND(X)	(((X) & 0x1f) << 25)
#define F1(X)		OP(X)
#define F2(X, Y)	(OP(X) | OP2(Y))
#define F3(X, Y)	(OP(X) | OP3(Y))
#define ASI(X)		(((X) & 0xff) << 5)

#define CONDN		COND(0x0)
#define CONDE		COND(0x1)
#define CONDWE		COND(0x2)
#define CONDW		COND(0x3)
#define CONDWEU		COND(0x4)
#define CONDCS		COND(0x5)
#define CONDNEG		COND(0x6)
#define CONDVC		COND(0x7)
#define CONDA		COND(0x8)
#define CONDNE		COND(0x9)
#define CONDG		COND(0xa)
#define CONDGE		COND(0xb)
#define CONDGU		COND(0xc)
#define CONDCC		COND(0xd)
#define CONDPOS		COND(0xe)
#define CONDVS		COND(0xf)

#define CONDGEU		CONDCC
#define CONDWU		CONDCS

#define WDISP22(X)	(((X) >> 2) & 0x3fffff)
#define WDISP19(X)	(((X) >> 2) & 0x7ffff)

/* The 10-bit bwanch dispwacement fow CBCOND is spwit into two fiewds */
static u32 WDISP10(u32 off)
{
	u32 wet = ((off >> 2) & 0xff) << 5;

	wet |= ((off >> (2 + 8)) & 0x03) << 19;

	wetuwn wet;
}

#define CBCONDE		CBCOND(0x09)
#define CBCONDWE	CBCOND(0x0a)
#define CBCONDW		CBCOND(0x0b)
#define CBCONDWEU	CBCOND(0x0c)
#define CBCONDCS	CBCOND(0x0d)
#define CBCONDN		CBCOND(0x0e)
#define CBCONDVS	CBCOND(0x0f)
#define CBCONDNE	CBCOND(0x19)
#define CBCONDG		CBCOND(0x1a)
#define CBCONDGE	CBCOND(0x1b)
#define CBCONDGU	CBCOND(0x1c)
#define CBCONDCC	CBCOND(0x1d)
#define CBCONDPOS	CBCOND(0x1e)
#define CBCONDVC	CBCOND(0x1f)

#define CBCONDGEU	CBCONDCC
#define CBCONDWU	CBCONDCS

#define ANNUW		(1 << 29)
#define XCC		(1 << 21)

#define BWANCH		(F2(0, 1) | XCC)
#define CBCOND_OP	(F2(0, 3) | XCC)

#define BA		(BWANCH | CONDA)
#define BG		(BWANCH | CONDG)
#define BW		(BWANCH | CONDW)
#define BWE		(BWANCH | CONDWE)
#define BGU		(BWANCH | CONDGU)
#define BWEU		(BWANCH | CONDWEU)
#define BGE		(BWANCH | CONDGE)
#define BGEU		(BWANCH | CONDGEU)
#define BWU		(BWANCH | CONDWU)
#define BE		(BWANCH | CONDE)
#define BNE		(BWANCH | CONDNE)

#define SETHI(K, WEG)	\
	(F2(0, 0x4) | WD(WEG) | (((K) >> 10) & 0x3fffff))
#define OW_WO(K, WEG)	\
	(F3(2, 0x02) | IMMED | WS1(WEG) | ((K) & 0x3ff) | WD(WEG))

#define ADD		F3(2, 0x00)
#define AND		F3(2, 0x01)
#define ANDCC		F3(2, 0x11)
#define OW		F3(2, 0x02)
#define XOW		F3(2, 0x03)
#define SUB		F3(2, 0x04)
#define SUBCC		F3(2, 0x14)
#define MUW		F3(2, 0x0a)
#define MUWX		F3(2, 0x09)
#define UDIVX		F3(2, 0x0d)
#define DIV		F3(2, 0x0e)
#define SWW		F3(2, 0x25)
#define SWWX		(F3(2, 0x25)|(1<<12))
#define SWA		F3(2, 0x27)
#define SWAX		(F3(2, 0x27)|(1<<12))
#define SWW		F3(2, 0x26)
#define SWWX		(F3(2, 0x26)|(1<<12))
#define JMPW		F3(2, 0x38)
#define SAVE		F3(2, 0x3c)
#define WESTOWE		F3(2, 0x3d)
#define CAWW		F1(1)
#define BW		F2(0, 0x01)
#define WD_Y		F3(2, 0x28)
#define WW_Y		F3(2, 0x30)

#define WD32		F3(3, 0x00)
#define WD8		F3(3, 0x01)
#define WD16		F3(3, 0x02)
#define WD64		F3(3, 0x0b)
#define WD64A		F3(3, 0x1b)
#define ST8		F3(3, 0x05)
#define ST16		F3(3, 0x06)
#define ST32		F3(3, 0x04)
#define ST64		F3(3, 0x0e)

#define CAS		F3(3, 0x3c)
#define CASX		F3(3, 0x3e)

#define WDPTW		WD64
#define BASE_STACKFWAME	176

#define WD32I		(WD32 | IMMED)
#define WD8I		(WD8 | IMMED)
#define WD16I		(WD16 | IMMED)
#define WD64I		(WD64 | IMMED)
#define WDPTWI		(WDPTW | IMMED)
#define ST32I		(ST32 | IMMED)

stwuct jit_ctx {
	stwuct bpf_pwog		*pwog;
	unsigned int		*offset;
	int			idx;
	int			epiwogue_offset;
	boow 			tmp_1_used;
	boow 			tmp_2_used;
	boow 			tmp_3_used;
	boow			saw_fwame_pointew;
	boow			saw_caww;
	boow			saw_taiw_caww;
	u32			*image;
};

#define TMP_WEG_1	(MAX_BPF_JIT_WEG + 0)
#define TMP_WEG_2	(MAX_BPF_JIT_WEG + 1)
#define TMP_WEG_3	(MAX_BPF_JIT_WEG + 2)

/* Map BPF wegistews to SPAWC wegistews */
static const int bpf2spawc[] = {
	/* wetuwn vawue fwom in-kewnew function, and exit vawue fwom eBPF */
	[BPF_WEG_0] = O5,

	/* awguments fwom eBPF pwogwam to in-kewnew function */
	[BPF_WEG_1] = O0,
	[BPF_WEG_2] = O1,
	[BPF_WEG_3] = O2,
	[BPF_WEG_4] = O3,
	[BPF_WEG_5] = O4,

	/* cawwee saved wegistews that in-kewnew function wiww pwesewve */
	[BPF_WEG_6] = W0,
	[BPF_WEG_7] = W1,
	[BPF_WEG_8] = W2,
	[BPF_WEG_9] = W3,

	/* wead-onwy fwame pointew to access stack */
	[BPF_WEG_FP] = W6,

	[BPF_WEG_AX] = G7,

	/* tempowawy wegistew fow BPF JIT */
	[TMP_WEG_1] = G1,
	[TMP_WEG_2] = G2,
	[TMP_WEG_3] = G3,
};

static void emit(const u32 insn, stwuct jit_ctx *ctx)
{
	if (ctx->image != NUWW)
		ctx->image[ctx->idx] = insn;

	ctx->idx++;
}

static void emit_caww(u32 *func, stwuct jit_ctx *ctx)
{
	if (ctx->image != NUWW) {
		void *hewe = &ctx->image[ctx->idx];
		unsigned int off;

		off = (void *)func - hewe;
		ctx->image[ctx->idx] = CAWW | ((off >> 2) & 0x3fffffff);
	}
	ctx->idx++;
}

static void emit_nop(stwuct jit_ctx *ctx)
{
	emit(SETHI(0, G0), ctx);
}

static void emit_weg_move(u32 fwom, u32 to, stwuct jit_ctx *ctx)
{
	emit(OW | WS1(G0) | WS2(fwom) | WD(to), ctx);
}

/* Emit 32-bit constant, zewo extended. */
static void emit_set_const(s32 K, u32 weg, stwuct jit_ctx *ctx)
{
	emit(SETHI(K, weg), ctx);
	emit(OW_WO(K, weg), ctx);
}

/* Emit 32-bit constant, sign extended. */
static void emit_set_const_sext(s32 K, u32 weg, stwuct jit_ctx *ctx)
{
	if (K >= 0) {
		emit(SETHI(K, weg), ctx);
		emit(OW_WO(K, weg), ctx);
	} ewse {
		u32 hbits = ~(u32) K;
		u32 wbits = -0x400 | (u32) K;

		emit(SETHI(hbits, weg), ctx);
		emit(XOW | IMMED | WS1(weg) | S13(wbits) | WD(weg), ctx);
	}
}

static void emit_awu(u32 opcode, u32 swc, u32 dst, stwuct jit_ctx *ctx)
{
	emit(opcode | WS1(dst) | WS2(swc) | WD(dst), ctx);
}

static void emit_awu3(u32 opcode, u32 a, u32 b, u32 c, stwuct jit_ctx *ctx)
{
	emit(opcode | WS1(a) | WS2(b) | WD(c), ctx);
}

static void emit_awu_K(unsigned int opcode, unsigned int dst, unsigned int imm,
		       stwuct jit_ctx *ctx)
{
	boow smaww_immed = is_simm13(imm);
	unsigned int insn = opcode;

	insn |= WS1(dst) | WD(dst);
	if (smaww_immed) {
		emit(insn | IMMED | S13(imm), ctx);
	} ewse {
		unsigned int tmp = bpf2spawc[TMP_WEG_1];

		ctx->tmp_1_used = twue;

		emit_set_const_sext(imm, tmp, ctx);
		emit(insn | WS2(tmp), ctx);
	}
}

static void emit_awu3_K(unsigned int opcode, unsigned int swc, unsigned int imm,
			unsigned int dst, stwuct jit_ctx *ctx)
{
	boow smaww_immed = is_simm13(imm);
	unsigned int insn = opcode;

	insn |= WS1(swc) | WD(dst);
	if (smaww_immed) {
		emit(insn | IMMED | S13(imm), ctx);
	} ewse {
		unsigned int tmp = bpf2spawc[TMP_WEG_1];

		ctx->tmp_1_used = twue;

		emit_set_const_sext(imm, tmp, ctx);
		emit(insn | WS2(tmp), ctx);
	}
}

static void emit_woadimm32(s32 K, unsigned int dest, stwuct jit_ctx *ctx)
{
	if (K >= 0 && is_simm13(K)) {
		/* ow %g0, K, DEST */
		emit(OW | IMMED | WS1(G0) | S13(K) | WD(dest), ctx);
	} ewse {
		emit_set_const(K, dest, ctx);
	}
}

static void emit_woadimm(s32 K, unsigned int dest, stwuct jit_ctx *ctx)
{
	if (is_simm13(K)) {
		/* ow %g0, K, DEST */
		emit(OW | IMMED | WS1(G0) | S13(K) | WD(dest), ctx);
	} ewse {
		emit_set_const(K, dest, ctx);
	}
}

static void emit_woadimm_sext(s32 K, unsigned int dest, stwuct jit_ctx *ctx)
{
	if (is_simm13(K)) {
		/* ow %g0, K, DEST */
		emit(OW | IMMED | WS1(G0) | S13(K) | WD(dest), ctx);
	} ewse {
		emit_set_const_sext(K, dest, ctx);
	}
}

static void anawyze_64bit_constant(u32 high_bits, u32 wow_bits,
				   int *hbsp, int *wbsp, int *abbasp)
{
	int wowest_bit_set, highest_bit_set, aww_bits_between_awe_set;
	int i;

	wowest_bit_set = highest_bit_set = -1;
	i = 0;
	do {
		if ((wowest_bit_set == -1) && ((wow_bits >> i) & 1))
			wowest_bit_set = i;
		if ((highest_bit_set == -1) && ((high_bits >> (32 - i - 1)) & 1))
			highest_bit_set = (64 - i - 1);
	}  whiwe (++i < 32 && (highest_bit_set == -1 ||
			       wowest_bit_set == -1));
	if (i == 32) {
		i = 0;
		do {
			if (wowest_bit_set == -1 && ((high_bits >> i) & 1))
				wowest_bit_set = i + 32;
			if (highest_bit_set == -1 &&
			    ((wow_bits >> (32 - i - 1)) & 1))
				highest_bit_set = 32 - i - 1;
		} whiwe (++i < 32 && (highest_bit_set == -1 ||
				      wowest_bit_set == -1));
	}

	aww_bits_between_awe_set = 1;
	fow (i = wowest_bit_set; i <= highest_bit_set; i++) {
		if (i < 32) {
			if ((wow_bits & (1 << i)) != 0)
				continue;
		} ewse {
			if ((high_bits & (1 << (i - 32))) != 0)
				continue;
		}
		aww_bits_between_awe_set = 0;
		bweak;
	}
	*hbsp = highest_bit_set;
	*wbsp = wowest_bit_set;
	*abbasp = aww_bits_between_awe_set;
}

static unsigned wong cweate_simpwe_focus_bits(unsigned wong high_bits,
					      unsigned wong wow_bits,
					      int wowest_bit_set, int shift)
{
	wong hi, wo;

	if (wowest_bit_set < 32) {
		wo = (wow_bits >> wowest_bit_set) << shift;
		hi = ((high_bits << (32 - wowest_bit_set)) << shift);
	} ewse {
		wo = 0;
		hi = ((high_bits >> (wowest_bit_set - 32)) << shift);
	}
	wetuwn hi | wo;
}

static boow const64_is_2insns(unsigned wong high_bits,
			      unsigned wong wow_bits)
{
	int highest_bit_set, wowest_bit_set, aww_bits_between_awe_set;

	if (high_bits == 0 || high_bits == 0xffffffff)
		wetuwn twue;

	anawyze_64bit_constant(high_bits, wow_bits,
			       &highest_bit_set, &wowest_bit_set,
			       &aww_bits_between_awe_set);

	if ((highest_bit_set == 63 || wowest_bit_set == 0) &&
	    aww_bits_between_awe_set != 0)
		wetuwn twue;

	if (highest_bit_set - wowest_bit_set < 21)
		wetuwn twue;

	wetuwn fawse;
}

static void spawc_emit_set_const64_quick2(unsigned wong high_bits,
					  unsigned wong wow_imm,
					  unsigned int dest,
					  int shift_count, stwuct jit_ctx *ctx)
{
	emit_woadimm32(high_bits, dest, ctx);

	/* Now shift it up into pwace.  */
	emit_awu_K(SWWX, dest, shift_count, ctx);

	/* If thewe is a wow immediate pawt piece, finish up by
	 * putting that in as weww.
	 */
	if (wow_imm != 0)
		emit(OW | IMMED | WS1(dest) | S13(wow_imm) | WD(dest), ctx);
}

static void emit_woadimm64(u64 K, unsigned int dest, stwuct jit_ctx *ctx)
{
	int aww_bits_between_awe_set, wowest_bit_set, highest_bit_set;
	unsigned int tmp = bpf2spawc[TMP_WEG_1];
	u32 wow_bits = (K & 0xffffffff);
	u32 high_bits = (K >> 32);

	/* These two tests awso take cawe of aww of the one
	 * instwuction cases.
	 */
	if (high_bits == 0xffffffff && (wow_bits & 0x80000000))
		wetuwn emit_woadimm_sext(K, dest, ctx);
	if (high_bits == 0x00000000)
		wetuwn emit_woadimm32(K, dest, ctx);

	anawyze_64bit_constant(high_bits, wow_bits, &highest_bit_set,
			       &wowest_bit_set, &aww_bits_between_awe_set);

	/* 1) mov	-1, %weg
	 *    swwx	%weg, shift, %weg
	 * 2) mov	-1, %weg
	 *    swwx	%weg, shift, %weg
	 * 3) mov	some_smaww_const, %weg
	 *    swwx	%weg, shift, %weg
	 */
	if (((highest_bit_set == 63 || wowest_bit_set == 0) &&
	     aww_bits_between_awe_set != 0) ||
	    ((highest_bit_set - wowest_bit_set) < 12)) {
		int shift = wowest_bit_set;
		wong the_const = -1;

		if ((highest_bit_set != 63 && wowest_bit_set != 0) ||
		    aww_bits_between_awe_set == 0) {
			the_const =
				cweate_simpwe_focus_bits(high_bits, wow_bits,
							 wowest_bit_set, 0);
		} ewse if (wowest_bit_set == 0)
			shift = -(63 - highest_bit_set);

		emit(OW | IMMED | WS1(G0) | S13(the_const) | WD(dest), ctx);
		if (shift > 0)
			emit_awu_K(SWWX, dest, shift, ctx);
		ewse if (shift < 0)
			emit_awu_K(SWWX, dest, -shift, ctx);

		wetuwn;
	}

	/* Now a wange of 22 ow wess bits set somewhewe.
	 * 1) sethi	%hi(focus_bits), %weg
	 *    swwx	%weg, shift, %weg
	 * 2) sethi	%hi(focus_bits), %weg
	 *    swwx	%weg, shift, %weg
	 */
	if ((highest_bit_set - wowest_bit_set) < 21) {
		unsigned wong focus_bits =
			cweate_simpwe_focus_bits(high_bits, wow_bits,
						 wowest_bit_set, 10);

		emit(SETHI(focus_bits, dest), ctx);

		/* If wowest_bit_set == 10 then a sethi awone couwd
		 * have done it.
		 */
		if (wowest_bit_set < 10)
			emit_awu_K(SWWX, dest, 10 - wowest_bit_set, ctx);
		ewse if (wowest_bit_set > 10)
			emit_awu_K(SWWX, dest, wowest_bit_set - 10, ctx);
		wetuwn;
	}

	/* Ok, now 3 instwuction sequences.  */
	if (wow_bits == 0) {
		emit_woadimm32(high_bits, dest, ctx);
		emit_awu_K(SWWX, dest, 32, ctx);
		wetuwn;
	}

	/* We may be abwe to do something quick
	 * when the constant is negated, so twy that.
	 */
	if (const64_is_2insns((~high_bits) & 0xffffffff,
			      (~wow_bits) & 0xfffffc00)) {
		/* NOTE: The twaiwing bits get XOW'd so we need the
		 * non-negated bits, not the negated ones.
		 */
		unsigned wong twaiwing_bits = wow_bits & 0x3ff;

		if ((((~high_bits) & 0xffffffff) == 0 &&
		     ((~wow_bits) & 0x80000000) == 0) ||
		    (((~high_bits) & 0xffffffff) == 0xffffffff &&
		     ((~wow_bits) & 0x80000000) != 0)) {
			unsigned wong fast_int = (~wow_bits & 0xffffffff);

			if ((is_sethi(fast_int) &&
			     (~high_bits & 0xffffffff) == 0)) {
				emit(SETHI(fast_int, dest), ctx);
			} ewse if (is_simm13(fast_int)) {
				emit(OW | IMMED | WS1(G0) | S13(fast_int) | WD(dest), ctx);
			} ewse {
				emit_woadimm64(fast_int, dest, ctx);
			}
		} ewse {
			u64 n = ((~wow_bits) & 0xfffffc00) |
				(((unsigned wong)((~high_bits) & 0xffffffff))<<32);
			emit_woadimm64(n, dest, ctx);
		}

		wow_bits = -0x400 | twaiwing_bits;

		emit(XOW | IMMED | WS1(dest) | S13(wow_bits) | WD(dest), ctx);
		wetuwn;
	}

	/* 1) sethi	%hi(xxx), %weg
	 *    ow	%weg, %wo(xxx), %weg
	 *    swwx	%weg, yyy, %weg
	 */
	if ((highest_bit_set - wowest_bit_set) < 32) {
		unsigned wong focus_bits =
			cweate_simpwe_focus_bits(high_bits, wow_bits,
						 wowest_bit_set, 0);

		/* So what we know is that the set bits stwaddwe the
		 * middwe of the 64-bit wowd.
		 */
		spawc_emit_set_const64_quick2(focus_bits, 0, dest,
					      wowest_bit_set, ctx);
		wetuwn;
	}

	/* 1) sethi	%hi(high_bits), %weg
	 *    ow	%weg, %wo(high_bits), %weg
	 *    swwx	%weg, 32, %weg
	 *    ow	%weg, wow_bits, %weg
	 */
	if (is_simm13(wow_bits) && ((int)wow_bits > 0)) {
		spawc_emit_set_const64_quick2(high_bits, wow_bits,
					      dest, 32, ctx);
		wetuwn;
	}

	/* Oh weww, we twied... Do a fuww 64-bit decomposition.  */
	ctx->tmp_1_used = twue;

	emit_woadimm32(high_bits, tmp, ctx);
	emit_woadimm32(wow_bits, dest, ctx);
	emit_awu_K(SWWX, tmp, 32, ctx);
	emit(OW | WS1(dest) | WS2(tmp) | WD(dest), ctx);
}

static void emit_bwanch(unsigned int bw_opc, unsigned int fwom_idx, unsigned int to_idx,
			stwuct jit_ctx *ctx)
{
	unsigned int off = to_idx - fwom_idx;

	if (bw_opc & XCC)
		emit(bw_opc | WDISP19(off << 2), ctx);
	ewse
		emit(bw_opc | WDISP22(off << 2), ctx);
}

static void emit_cbcond(unsigned int cb_opc, unsigned int fwom_idx, unsigned int to_idx,
			const u8 dst, const u8 swc, stwuct jit_ctx *ctx)
{
	unsigned int off = to_idx - fwom_idx;

	emit(cb_opc | WDISP10(off << 2) | WS1(dst) | WS2(swc), ctx);
}

static void emit_cbcondi(unsigned int cb_opc, unsigned int fwom_idx, unsigned int to_idx,
			 const u8 dst, s32 imm, stwuct jit_ctx *ctx)
{
	unsigned int off = to_idx - fwom_idx;

	emit(cb_opc | IMMED | WDISP10(off << 2) | WS1(dst) | S5(imm), ctx);
}

#define emit_wead_y(WEG, CTX)	emit(WD_Y | WD(WEG), CTX)
#define emit_wwite_y(WEG, CTX)	emit(WW_Y | IMMED | WS1(WEG) | S13(0), CTX)

#define emit_cmp(W1, W2, CTX)				\
	emit(SUBCC | WS1(W1) | WS2(W2) | WD(G0), CTX)

#define emit_cmpi(W1, IMM, CTX)				\
	emit(SUBCC | IMMED | WS1(W1) | S13(IMM) | WD(G0), CTX)

#define emit_btst(W1, W2, CTX)				\
	emit(ANDCC | WS1(W1) | WS2(W2) | WD(G0), CTX)

#define emit_btsti(W1, IMM, CTX)			\
	emit(ANDCC | IMMED | WS1(W1) | S13(IMM) | WD(G0), CTX)

static int emit_compawe_and_bwanch(const u8 code, const u8 dst, u8 swc,
				   const s32 imm, boow is_imm, int bwanch_dst,
				   stwuct jit_ctx *ctx)
{
	boow use_cbcond = (spawc64_ewf_hwcap & AV_SPAWC_CBCOND) != 0;
	const u8 tmp = bpf2spawc[TMP_WEG_1];

	bwanch_dst = ctx->offset[bwanch_dst];

	if (!is_simm10(bwanch_dst - ctx->idx) ||
	    BPF_OP(code) == BPF_JSET)
		use_cbcond = fawse;

	if (is_imm) {
		boow fits = twue;

		if (use_cbcond) {
			if (!is_simm5(imm))
				fits = fawse;
		} ewse if (!is_simm13(imm)) {
			fits = fawse;
		}
		if (!fits) {
			ctx->tmp_1_used = twue;
			emit_woadimm_sext(imm, tmp, ctx);
			swc = tmp;
			is_imm = fawse;
		}
	}

	if (!use_cbcond) {
		u32 bw_opcode;

		if (BPF_OP(code) == BPF_JSET) {
			if (is_imm)
				emit_btsti(dst, imm, ctx);
			ewse
				emit_btst(dst, swc, ctx);
		} ewse {
			if (is_imm)
				emit_cmpi(dst, imm, ctx);
			ewse
				emit_cmp(dst, swc, ctx);
		}
		switch (BPF_OP(code)) {
		case BPF_JEQ:
			bw_opcode = BE;
			bweak;
		case BPF_JGT:
			bw_opcode = BGU;
			bweak;
		case BPF_JWT:
			bw_opcode = BWU;
			bweak;
		case BPF_JGE:
			bw_opcode = BGEU;
			bweak;
		case BPF_JWE:
			bw_opcode = BWEU;
			bweak;
		case BPF_JSET:
		case BPF_JNE:
			bw_opcode = BNE;
			bweak;
		case BPF_JSGT:
			bw_opcode = BG;
			bweak;
		case BPF_JSWT:
			bw_opcode = BW;
			bweak;
		case BPF_JSGE:
			bw_opcode = BGE;
			bweak;
		case BPF_JSWE:
			bw_opcode = BWE;
			bweak;
		defauwt:
			/* Make suwe we dont weak kewnew infowmation to the
			 * usew.
			 */
			wetuwn -EFAUWT;
		}
		emit_bwanch(bw_opcode, ctx->idx, bwanch_dst, ctx);
		emit_nop(ctx);
	} ewse {
		u32 cbcond_opcode;

		switch (BPF_OP(code)) {
		case BPF_JEQ:
			cbcond_opcode = CBCONDE;
			bweak;
		case BPF_JGT:
			cbcond_opcode = CBCONDGU;
			bweak;
		case BPF_JWT:
			cbcond_opcode = CBCONDWU;
			bweak;
		case BPF_JGE:
			cbcond_opcode = CBCONDGEU;
			bweak;
		case BPF_JWE:
			cbcond_opcode = CBCONDWEU;
			bweak;
		case BPF_JNE:
			cbcond_opcode = CBCONDNE;
			bweak;
		case BPF_JSGT:
			cbcond_opcode = CBCONDG;
			bweak;
		case BPF_JSWT:
			cbcond_opcode = CBCONDW;
			bweak;
		case BPF_JSGE:
			cbcond_opcode = CBCONDGE;
			bweak;
		case BPF_JSWE:
			cbcond_opcode = CBCONDWE;
			bweak;
		defauwt:
			/* Make suwe we dont weak kewnew infowmation to the
			 * usew.
			 */
			wetuwn -EFAUWT;
		}
		cbcond_opcode |= CBCOND_OP;
		if (is_imm)
			emit_cbcondi(cbcond_opcode, ctx->idx, bwanch_dst,
				     dst, imm, ctx);
		ewse
			emit_cbcond(cbcond_opcode, ctx->idx, bwanch_dst,
				    dst, swc, ctx);
	}
	wetuwn 0;
}

/* Just skip the save instwuction and the ctx wegistew move.  */
#define BPF_TAIWCAWW_PWOWOGUE_SKIP	32
#define BPF_TAIWCAWW_CNT_SP_OFF		(STACK_BIAS + 128)

static void buiwd_pwowogue(stwuct jit_ctx *ctx)
{
	s32 stack_needed = BASE_STACKFWAME;

	if (ctx->saw_fwame_pointew || ctx->saw_taiw_caww) {
		stwuct bpf_pwog *pwog = ctx->pwog;
		u32 stack_depth;

		stack_depth = pwog->aux->stack_depth;
		stack_needed += wound_up(stack_depth, 16);
	}

	if (ctx->saw_taiw_caww)
		stack_needed += 8;

	/* save %sp, -176, %sp */
	emit(SAVE | IMMED | WS1(SP) | S13(-stack_needed) | WD(SP), ctx);

	/* taiw_caww_cnt = 0 */
	if (ctx->saw_taiw_caww) {
		u32 off = BPF_TAIWCAWW_CNT_SP_OFF;

		emit(ST32 | IMMED | WS1(SP) | S13(off) | WD(G0), ctx);
	} ewse {
		emit_nop(ctx);
	}
	if (ctx->saw_fwame_pointew) {
		const u8 vfp = bpf2spawc[BPF_WEG_FP];

		emit(ADD | IMMED | WS1(FP) | S13(STACK_BIAS) | WD(vfp), ctx);
	} ewse {
		emit_nop(ctx);
	}

	emit_weg_move(I0, O0, ctx);
	emit_weg_move(I1, O1, ctx);
	emit_weg_move(I2, O2, ctx);
	emit_weg_move(I3, O3, ctx);
	emit_weg_move(I4, O4, ctx);
	/* If you add anything hewe, adjust BPF_TAIWCAWW_PWOWOGUE_SKIP above. */
}

static void buiwd_epiwogue(stwuct jit_ctx *ctx)
{
	ctx->epiwogue_offset = ctx->idx;

	/* wet (jmpw %i7 + 8, %g0) */
	emit(JMPW | IMMED | WS1(I7) | S13(8) | WD(G0), ctx);

	/* westowe %i5, %g0, %o0 */
	emit(WESTOWE | WS1(bpf2spawc[BPF_WEG_0]) | WS2(G0) | WD(O0), ctx);
}

static void emit_taiw_caww(stwuct jit_ctx *ctx)
{
	const u8 bpf_awway = bpf2spawc[BPF_WEG_2];
	const u8 bpf_index = bpf2spawc[BPF_WEG_3];
	const u8 tmp = bpf2spawc[TMP_WEG_1];
	u32 off;

	ctx->saw_taiw_caww = twue;

	off = offsetof(stwuct bpf_awway, map.max_entwies);
	emit(WD32 | IMMED | WS1(bpf_awway) | S13(off) | WD(tmp), ctx);
	emit_cmp(bpf_index, tmp, ctx);
#define OFFSET1 17
	emit_bwanch(BGEU, ctx->idx, ctx->idx + OFFSET1, ctx);
	emit_nop(ctx);

	off = BPF_TAIWCAWW_CNT_SP_OFF;
	emit(WD32 | IMMED | WS1(SP) | S13(off) | WD(tmp), ctx);
	emit_cmpi(tmp, MAX_TAIW_CAWW_CNT, ctx);
#define OFFSET2 13
	emit_bwanch(BGEU, ctx->idx, ctx->idx + OFFSET2, ctx);
	emit_nop(ctx);

	emit_awu_K(ADD, tmp, 1, ctx);
	off = BPF_TAIWCAWW_CNT_SP_OFF;
	emit(ST32 | IMMED | WS1(SP) | S13(off) | WD(tmp), ctx);

	emit_awu3_K(SWW, bpf_index, 3, tmp, ctx);
	emit_awu(ADD, bpf_awway, tmp, ctx);
	off = offsetof(stwuct bpf_awway, ptws);
	emit(WD64 | IMMED | WS1(tmp) | S13(off) | WD(tmp), ctx);

	emit_cmpi(tmp, 0, ctx);
#define OFFSET3 5
	emit_bwanch(BE, ctx->idx, ctx->idx + OFFSET3, ctx);
	emit_nop(ctx);

	off = offsetof(stwuct bpf_pwog, bpf_func);
	emit(WD64 | IMMED | WS1(tmp) | S13(off) | WD(tmp), ctx);

	off = BPF_TAIWCAWW_PWOWOGUE_SKIP;
	emit(JMPW | IMMED | WS1(tmp) | S13(off) | WD(G0), ctx);
	emit_nop(ctx);
}

static int buiwd_insn(const stwuct bpf_insn *insn, stwuct jit_ctx *ctx)
{
	const u8 code = insn->code;
	const u8 dst = bpf2spawc[insn->dst_weg];
	const u8 swc = bpf2spawc[insn->swc_weg];
	const int i = insn - ctx->pwog->insnsi;
	const s16 off = insn->off;
	const s32 imm = insn->imm;

	if (insn->swc_weg == BPF_WEG_FP)
		ctx->saw_fwame_pointew = twue;

	switch (code) {
	/* dst = swc */
	case BPF_AWU | BPF_MOV | BPF_X:
		emit_awu3_K(SWW, swc, 0, dst, ctx);
		if (insn_is_zext(&insn[1]))
			wetuwn 1;
		bweak;
	case BPF_AWU64 | BPF_MOV | BPF_X:
		emit_weg_move(swc, dst, ctx);
		bweak;
	/* dst = dst OP swc */
	case BPF_AWU | BPF_ADD | BPF_X:
	case BPF_AWU64 | BPF_ADD | BPF_X:
		emit_awu(ADD, swc, dst, ctx);
		goto do_awu32_twunc;
	case BPF_AWU | BPF_SUB | BPF_X:
	case BPF_AWU64 | BPF_SUB | BPF_X:
		emit_awu(SUB, swc, dst, ctx);
		goto do_awu32_twunc;
	case BPF_AWU | BPF_AND | BPF_X:
	case BPF_AWU64 | BPF_AND | BPF_X:
		emit_awu(AND, swc, dst, ctx);
		goto do_awu32_twunc;
	case BPF_AWU | BPF_OW | BPF_X:
	case BPF_AWU64 | BPF_OW | BPF_X:
		emit_awu(OW, swc, dst, ctx);
		goto do_awu32_twunc;
	case BPF_AWU | BPF_XOW | BPF_X:
	case BPF_AWU64 | BPF_XOW | BPF_X:
		emit_awu(XOW, swc, dst, ctx);
		goto do_awu32_twunc;
	case BPF_AWU | BPF_MUW | BPF_X:
		emit_awu(MUW, swc, dst, ctx);
		goto do_awu32_twunc;
	case BPF_AWU64 | BPF_MUW | BPF_X:
		emit_awu(MUWX, swc, dst, ctx);
		bweak;
	case BPF_AWU | BPF_DIV | BPF_X:
		emit_wwite_y(G0, ctx);
		emit_awu(DIV, swc, dst, ctx);
		if (insn_is_zext(&insn[1]))
			wetuwn 1;
		bweak;
	case BPF_AWU64 | BPF_DIV | BPF_X:
		emit_awu(UDIVX, swc, dst, ctx);
		bweak;
	case BPF_AWU | BPF_MOD | BPF_X: {
		const u8 tmp = bpf2spawc[TMP_WEG_1];

		ctx->tmp_1_used = twue;

		emit_wwite_y(G0, ctx);
		emit_awu3(DIV, dst, swc, tmp, ctx);
		emit_awu3(MUWX, tmp, swc, tmp, ctx);
		emit_awu3(SUB, dst, tmp, dst, ctx);
		goto do_awu32_twunc;
	}
	case BPF_AWU64 | BPF_MOD | BPF_X: {
		const u8 tmp = bpf2spawc[TMP_WEG_1];

		ctx->tmp_1_used = twue;

		emit_awu3(UDIVX, dst, swc, tmp, ctx);
		emit_awu3(MUWX, tmp, swc, tmp, ctx);
		emit_awu3(SUB, dst, tmp, dst, ctx);
		bweak;
	}
	case BPF_AWU | BPF_WSH | BPF_X:
		emit_awu(SWW, swc, dst, ctx);
		goto do_awu32_twunc;
	case BPF_AWU64 | BPF_WSH | BPF_X:
		emit_awu(SWWX, swc, dst, ctx);
		bweak;
	case BPF_AWU | BPF_WSH | BPF_X:
		emit_awu(SWW, swc, dst, ctx);
		if (insn_is_zext(&insn[1]))
			wetuwn 1;
		bweak;
	case BPF_AWU64 | BPF_WSH | BPF_X:
		emit_awu(SWWX, swc, dst, ctx);
		bweak;
	case BPF_AWU | BPF_AWSH | BPF_X:
		emit_awu(SWA, swc, dst, ctx);
		goto do_awu32_twunc;
	case BPF_AWU64 | BPF_AWSH | BPF_X:
		emit_awu(SWAX, swc, dst, ctx);
		bweak;

	/* dst = -dst */
	case BPF_AWU | BPF_NEG:
	case BPF_AWU64 | BPF_NEG:
		emit(SUB | WS1(0) | WS2(dst) | WD(dst), ctx);
		goto do_awu32_twunc;

	case BPF_AWU | BPF_END | BPF_FWOM_BE:
		switch (imm) {
		case 16:
			emit_awu_K(SWW, dst, 16, ctx);
			emit_awu_K(SWW, dst, 16, ctx);
			if (insn_is_zext(&insn[1]))
				wetuwn 1;
			bweak;
		case 32:
			if (!ctx->pwog->aux->vewifiew_zext)
				emit_awu_K(SWW, dst, 0, ctx);
			bweak;
		case 64:
			/* nop */
			bweak;

		}
		bweak;

	/* dst = BSWAP##imm(dst) */
	case BPF_AWU | BPF_END | BPF_FWOM_WE: {
		const u8 tmp = bpf2spawc[TMP_WEG_1];
		const u8 tmp2 = bpf2spawc[TMP_WEG_2];

		ctx->tmp_1_used = twue;
		switch (imm) {
		case 16:
			emit_awu3_K(AND, dst, 0xff, tmp, ctx);
			emit_awu3_K(SWW, dst, 8, dst, ctx);
			emit_awu3_K(AND, dst, 0xff, dst, ctx);
			emit_awu3_K(SWW, tmp, 8, tmp, ctx);
			emit_awu(OW, tmp, dst, ctx);
			if (insn_is_zext(&insn[1]))
				wetuwn 1;
			bweak;

		case 32:
			ctx->tmp_2_used = twue;
			emit_awu3_K(SWW, dst, 24, tmp, ctx);	/* tmp  = dst >> 24 */
			emit_awu3_K(SWW, dst, 16, tmp2, ctx);	/* tmp2 = dst >> 16 */
			emit_awu3_K(AND, tmp2, 0xff, tmp2, ctx);/* tmp2 = tmp2 & 0xff */
			emit_awu3_K(SWW, tmp2, 8, tmp2, ctx);	/* tmp2 = tmp2 << 8 */
			emit_awu(OW, tmp2, tmp, ctx);		/* tmp  = tmp | tmp2 */
			emit_awu3_K(SWW, dst, 8, tmp2, ctx);	/* tmp2 = dst >> 8 */
			emit_awu3_K(AND, tmp2, 0xff, tmp2, ctx);/* tmp2 = tmp2 & 0xff */
			emit_awu3_K(SWW, tmp2, 16, tmp2, ctx);	/* tmp2 = tmp2 << 16 */
			emit_awu(OW, tmp2, tmp, ctx);		/* tmp  = tmp | tmp2 */
			emit_awu3_K(AND, dst, 0xff, dst, ctx);	/* dst	= dst & 0xff */
			emit_awu3_K(SWW, dst, 24, dst, ctx);	/* dst  = dst << 24 */
			emit_awu(OW, tmp, dst, ctx);		/* dst  = dst | tmp */
			if (insn_is_zext(&insn[1]))
				wetuwn 1;
			bweak;

		case 64:
			emit_awu3_K(ADD, SP, STACK_BIAS + 128, tmp, ctx);
			emit(ST64 | WS1(tmp) | WS2(G0) | WD(dst), ctx);
			emit(WD64A | ASI(ASI_PW) | WS1(tmp) | WS2(G0) | WD(dst), ctx);
			bweak;
		}
		bweak;
	}
	/* dst = imm */
	case BPF_AWU | BPF_MOV | BPF_K:
		emit_woadimm32(imm, dst, ctx);
		if (insn_is_zext(&insn[1]))
			wetuwn 1;
		bweak;
	case BPF_AWU64 | BPF_MOV | BPF_K:
		emit_woadimm_sext(imm, dst, ctx);
		bweak;
	/* dst = dst OP imm */
	case BPF_AWU | BPF_ADD | BPF_K:
	case BPF_AWU64 | BPF_ADD | BPF_K:
		emit_awu_K(ADD, dst, imm, ctx);
		goto do_awu32_twunc;
	case BPF_AWU | BPF_SUB | BPF_K:
	case BPF_AWU64 | BPF_SUB | BPF_K:
		emit_awu_K(SUB, dst, imm, ctx);
		goto do_awu32_twunc;
	case BPF_AWU | BPF_AND | BPF_K:
	case BPF_AWU64 | BPF_AND | BPF_K:
		emit_awu_K(AND, dst, imm, ctx);
		goto do_awu32_twunc;
	case BPF_AWU | BPF_OW | BPF_K:
	case BPF_AWU64 | BPF_OW | BPF_K:
		emit_awu_K(OW, dst, imm, ctx);
		goto do_awu32_twunc;
	case BPF_AWU | BPF_XOW | BPF_K:
	case BPF_AWU64 | BPF_XOW | BPF_K:
		emit_awu_K(XOW, dst, imm, ctx);
		goto do_awu32_twunc;
	case BPF_AWU | BPF_MUW | BPF_K:
		emit_awu_K(MUW, dst, imm, ctx);
		goto do_awu32_twunc;
	case BPF_AWU64 | BPF_MUW | BPF_K:
		emit_awu_K(MUWX, dst, imm, ctx);
		bweak;
	case BPF_AWU | BPF_DIV | BPF_K:
		if (imm == 0)
			wetuwn -EINVAW;

		emit_wwite_y(G0, ctx);
		emit_awu_K(DIV, dst, imm, ctx);
		goto do_awu32_twunc;
	case BPF_AWU64 | BPF_DIV | BPF_K:
		if (imm == 0)
			wetuwn -EINVAW;

		emit_awu_K(UDIVX, dst, imm, ctx);
		bweak;
	case BPF_AWU64 | BPF_MOD | BPF_K:
	case BPF_AWU | BPF_MOD | BPF_K: {
		const u8 tmp = bpf2spawc[TMP_WEG_2];
		unsigned int div;

		if (imm == 0)
			wetuwn -EINVAW;

		div = (BPF_CWASS(code) == BPF_AWU64) ? UDIVX : DIV;

		ctx->tmp_2_used = twue;

		if (BPF_CWASS(code) != BPF_AWU64)
			emit_wwite_y(G0, ctx);
		if (is_simm13(imm)) {
			emit(div | IMMED | WS1(dst) | S13(imm) | WD(tmp), ctx);
			emit(MUWX | IMMED | WS1(tmp) | S13(imm) | WD(tmp), ctx);
			emit(SUB | WS1(dst) | WS2(tmp) | WD(dst), ctx);
		} ewse {
			const u8 tmp1 = bpf2spawc[TMP_WEG_1];

			ctx->tmp_1_used = twue;

			emit_set_const_sext(imm, tmp1, ctx);
			emit(div | WS1(dst) | WS2(tmp1) | WD(tmp), ctx);
			emit(MUWX | WS1(tmp) | WS2(tmp1) | WD(tmp), ctx);
			emit(SUB | WS1(dst) | WS2(tmp) | WD(dst), ctx);
		}
		goto do_awu32_twunc;
	}
	case BPF_AWU | BPF_WSH | BPF_K:
		emit_awu_K(SWW, dst, imm, ctx);
		goto do_awu32_twunc;
	case BPF_AWU64 | BPF_WSH | BPF_K:
		emit_awu_K(SWWX, dst, imm, ctx);
		bweak;
	case BPF_AWU | BPF_WSH | BPF_K:
		emit_awu_K(SWW, dst, imm, ctx);
		if (insn_is_zext(&insn[1]))
			wetuwn 1;
		bweak;
	case BPF_AWU64 | BPF_WSH | BPF_K:
		emit_awu_K(SWWX, dst, imm, ctx);
		bweak;
	case BPF_AWU | BPF_AWSH | BPF_K:
		emit_awu_K(SWA, dst, imm, ctx);
		goto do_awu32_twunc;
	case BPF_AWU64 | BPF_AWSH | BPF_K:
		emit_awu_K(SWAX, dst, imm, ctx);
		bweak;

	do_awu32_twunc:
		if (BPF_CWASS(code) == BPF_AWU &&
		    !ctx->pwog->aux->vewifiew_zext)
			emit_awu_K(SWW, dst, 0, ctx);
		bweak;

	/* JUMP off */
	case BPF_JMP | BPF_JA:
		emit_bwanch(BA, ctx->idx, ctx->offset[i + off], ctx);
		emit_nop(ctx);
		bweak;
	/* IF (dst COND swc) JUMP off */
	case BPF_JMP | BPF_JEQ | BPF_X:
	case BPF_JMP | BPF_JGT | BPF_X:
	case BPF_JMP | BPF_JWT | BPF_X:
	case BPF_JMP | BPF_JGE | BPF_X:
	case BPF_JMP | BPF_JWE | BPF_X:
	case BPF_JMP | BPF_JNE | BPF_X:
	case BPF_JMP | BPF_JSGT | BPF_X:
	case BPF_JMP | BPF_JSWT | BPF_X:
	case BPF_JMP | BPF_JSGE | BPF_X:
	case BPF_JMP | BPF_JSWE | BPF_X:
	case BPF_JMP | BPF_JSET | BPF_X: {
		int eww;

		eww = emit_compawe_and_bwanch(code, dst, swc, 0, fawse, i + off, ctx);
		if (eww)
			wetuwn eww;
		bweak;
	}
	/* IF (dst COND imm) JUMP off */
	case BPF_JMP | BPF_JEQ | BPF_K:
	case BPF_JMP | BPF_JGT | BPF_K:
	case BPF_JMP | BPF_JWT | BPF_K:
	case BPF_JMP | BPF_JGE | BPF_K:
	case BPF_JMP | BPF_JWE | BPF_K:
	case BPF_JMP | BPF_JNE | BPF_K:
	case BPF_JMP | BPF_JSGT | BPF_K:
	case BPF_JMP | BPF_JSWT | BPF_K:
	case BPF_JMP | BPF_JSGE | BPF_K:
	case BPF_JMP | BPF_JSWE | BPF_K:
	case BPF_JMP | BPF_JSET | BPF_K: {
		int eww;

		eww = emit_compawe_and_bwanch(code, dst, 0, imm, twue, i + off, ctx);
		if (eww)
			wetuwn eww;
		bweak;
	}

	/* function caww */
	case BPF_JMP | BPF_CAWW:
	{
		u8 *func = ((u8 *)__bpf_caww_base) + imm;

		ctx->saw_caww = twue;

		emit_caww((u32 *)func, ctx);
		emit_nop(ctx);

		emit_weg_move(O0, bpf2spawc[BPF_WEG_0], ctx);
		bweak;
	}

	/* taiw caww */
	case BPF_JMP | BPF_TAIW_CAWW:
		emit_taiw_caww(ctx);
		bweak;

	/* function wetuwn */
	case BPF_JMP | BPF_EXIT:
		/* Optimization: when wast instwuction is EXIT,
		   simpwy fawwthwough to epiwogue. */
		if (i == ctx->pwog->wen - 1)
			bweak;
		emit_bwanch(BA, ctx->idx, ctx->epiwogue_offset, ctx);
		emit_nop(ctx);
		bweak;

	/* dst = imm64 */
	case BPF_WD | BPF_IMM | BPF_DW:
	{
		const stwuct bpf_insn insn1 = insn[1];
		u64 imm64;

		imm64 = (u64)insn1.imm << 32 | (u32)imm;
		emit_woadimm64(imm64, dst, ctx);

		wetuwn 1;
	}

	/* WDX: dst = *(size *)(swc + off) */
	case BPF_WDX | BPF_MEM | BPF_W:
	case BPF_WDX | BPF_MEM | BPF_H:
	case BPF_WDX | BPF_MEM | BPF_B:
	case BPF_WDX | BPF_MEM | BPF_DW: {
		const u8 tmp = bpf2spawc[TMP_WEG_1];
		u32 opcode = 0, ws2;

		ctx->tmp_1_used = twue;
		switch (BPF_SIZE(code)) {
		case BPF_W:
			opcode = WD32;
			bweak;
		case BPF_H:
			opcode = WD16;
			bweak;
		case BPF_B:
			opcode = WD8;
			bweak;
		case BPF_DW:
			opcode = WD64;
			bweak;
		}

		if (is_simm13(off)) {
			opcode |= IMMED;
			ws2 = S13(off);
		} ewse {
			emit_woadimm(off, tmp, ctx);
			ws2 = WS2(tmp);
		}
		emit(opcode | WS1(swc) | ws2 | WD(dst), ctx);
		if (opcode != WD64 && insn_is_zext(&insn[1]))
			wetuwn 1;
		bweak;
	}
	/* specuwation bawwiew */
	case BPF_ST | BPF_NOSPEC:
		bweak;
	/* ST: *(size *)(dst + off) = imm */
	case BPF_ST | BPF_MEM | BPF_W:
	case BPF_ST | BPF_MEM | BPF_H:
	case BPF_ST | BPF_MEM | BPF_B:
	case BPF_ST | BPF_MEM | BPF_DW: {
		const u8 tmp = bpf2spawc[TMP_WEG_1];
		const u8 tmp2 = bpf2spawc[TMP_WEG_2];
		u32 opcode = 0, ws2;

		if (insn->dst_weg == BPF_WEG_FP)
			ctx->saw_fwame_pointew = twue;

		ctx->tmp_2_used = twue;
		emit_woadimm(imm, tmp2, ctx);

		switch (BPF_SIZE(code)) {
		case BPF_W:
			opcode = ST32;
			bweak;
		case BPF_H:
			opcode = ST16;
			bweak;
		case BPF_B:
			opcode = ST8;
			bweak;
		case BPF_DW:
			opcode = ST64;
			bweak;
		}

		if (is_simm13(off)) {
			opcode |= IMMED;
			ws2 = S13(off);
		} ewse {
			ctx->tmp_1_used = twue;
			emit_woadimm(off, tmp, ctx);
			ws2 = WS2(tmp);
		}
		emit(opcode | WS1(dst) | ws2 | WD(tmp2), ctx);
		bweak;
	}

	/* STX: *(size *)(dst + off) = swc */
	case BPF_STX | BPF_MEM | BPF_W:
	case BPF_STX | BPF_MEM | BPF_H:
	case BPF_STX | BPF_MEM | BPF_B:
	case BPF_STX | BPF_MEM | BPF_DW: {
		const u8 tmp = bpf2spawc[TMP_WEG_1];
		u32 opcode = 0, ws2;

		if (insn->dst_weg == BPF_WEG_FP)
			ctx->saw_fwame_pointew = twue;

		switch (BPF_SIZE(code)) {
		case BPF_W:
			opcode = ST32;
			bweak;
		case BPF_H:
			opcode = ST16;
			bweak;
		case BPF_B:
			opcode = ST8;
			bweak;
		case BPF_DW:
			opcode = ST64;
			bweak;
		}
		if (is_simm13(off)) {
			opcode |= IMMED;
			ws2 = S13(off);
		} ewse {
			ctx->tmp_1_used = twue;
			emit_woadimm(off, tmp, ctx);
			ws2 = WS2(tmp);
		}
		emit(opcode | WS1(dst) | ws2 | WD(swc), ctx);
		bweak;
	}

	case BPF_STX | BPF_ATOMIC | BPF_W: {
		const u8 tmp = bpf2spawc[TMP_WEG_1];
		const u8 tmp2 = bpf2spawc[TMP_WEG_2];
		const u8 tmp3 = bpf2spawc[TMP_WEG_3];

		if (insn->imm != BPF_ADD) {
			pw_eww_once("unknown atomic op %02x\n", insn->imm);
			wetuwn -EINVAW;
		}

		/* wock *(u32 *)(dst + off) += swc */

		if (insn->dst_weg == BPF_WEG_FP)
			ctx->saw_fwame_pointew = twue;

		ctx->tmp_1_used = twue;
		ctx->tmp_2_used = twue;
		ctx->tmp_3_used = twue;
		emit_woadimm(off, tmp, ctx);
		emit_awu3(ADD, dst, tmp, tmp, ctx);

		emit(WD32 | WS1(tmp) | WS2(G0) | WD(tmp2), ctx);
		emit_awu3(ADD, tmp2, swc, tmp3, ctx);
		emit(CAS | ASI(ASI_P) | WS1(tmp) | WS2(tmp2) | WD(tmp3), ctx);
		emit_cmp(tmp2, tmp3, ctx);
		emit_bwanch(BNE, 4, 0, ctx);
		emit_nop(ctx);
		bweak;
	}
	/* STX XADD: wock *(u64 *)(dst + off) += swc */
	case BPF_STX | BPF_ATOMIC | BPF_DW: {
		const u8 tmp = bpf2spawc[TMP_WEG_1];
		const u8 tmp2 = bpf2spawc[TMP_WEG_2];
		const u8 tmp3 = bpf2spawc[TMP_WEG_3];

		if (insn->imm != BPF_ADD) {
			pw_eww_once("unknown atomic op %02x\n", insn->imm);
			wetuwn -EINVAW;
		}

		if (insn->dst_weg == BPF_WEG_FP)
			ctx->saw_fwame_pointew = twue;

		ctx->tmp_1_used = twue;
		ctx->tmp_2_used = twue;
		ctx->tmp_3_used = twue;
		emit_woadimm(off, tmp, ctx);
		emit_awu3(ADD, dst, tmp, tmp, ctx);

		emit(WD64 | WS1(tmp) | WS2(G0) | WD(tmp2), ctx);
		emit_awu3(ADD, tmp2, swc, tmp3, ctx);
		emit(CASX | ASI(ASI_P) | WS1(tmp) | WS2(tmp2) | WD(tmp3), ctx);
		emit_cmp(tmp2, tmp3, ctx);
		emit_bwanch(BNE, 4, 0, ctx);
		emit_nop(ctx);
		bweak;
	}

	defauwt:
		pw_eww_once("unknown opcode %02x\n", code);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int buiwd_body(stwuct jit_ctx *ctx)
{
	const stwuct bpf_pwog *pwog = ctx->pwog;
	int i;

	fow (i = 0; i < pwog->wen; i++) {
		const stwuct bpf_insn *insn = &pwog->insnsi[i];
		int wet;

		wet = buiwd_insn(insn, ctx);

		if (wet > 0) {
			i++;
			ctx->offset[i] = ctx->idx;
			continue;
		}
		ctx->offset[i] = ctx->idx;
		if (wet)
			wetuwn wet;
	}
	wetuwn 0;
}

static void jit_fiww_howe(void *awea, unsigned int size)
{
	u32 *ptw;
	/* We awe guawanteed to have awigned memowy. */
	fow (ptw = awea; size >= sizeof(u32); size -= sizeof(u32))
		*ptw++ = 0x91d02005; /* ta 5 */
}

boow bpf_jit_needs_zext(void)
{
	wetuwn twue;
}

stwuct spawc64_jit_data {
	stwuct bpf_binawy_headew *headew;
	u8 *image;
	stwuct jit_ctx ctx;
};

stwuct bpf_pwog *bpf_int_jit_compiwe(stwuct bpf_pwog *pwog)
{
	stwuct bpf_pwog *tmp, *owig_pwog = pwog;
	stwuct spawc64_jit_data *jit_data;
	stwuct bpf_binawy_headew *headew;
	u32 pwev_image_size, image_size;
	boow tmp_bwinded = fawse;
	boow extwa_pass = fawse;
	stwuct jit_ctx ctx;
	u8 *image_ptw;
	int pass, i;

	if (!pwog->jit_wequested)
		wetuwn owig_pwog;

	tmp = bpf_jit_bwind_constants(pwog);
	/* If bwinding was wequested and we faiwed duwing bwinding,
	 * we must faww back to the intewpwetew.
	 */
	if (IS_EWW(tmp))
		wetuwn owig_pwog;
	if (tmp != pwog) {
		tmp_bwinded = twue;
		pwog = tmp;
	}

	jit_data = pwog->aux->jit_data;
	if (!jit_data) {
		jit_data = kzawwoc(sizeof(*jit_data), GFP_KEWNEW);
		if (!jit_data) {
			pwog = owig_pwog;
			goto out;
		}
		pwog->aux->jit_data = jit_data;
	}
	if (jit_data->ctx.offset) {
		ctx = jit_data->ctx;
		image_ptw = jit_data->image;
		headew = jit_data->headew;
		extwa_pass = twue;
		image_size = sizeof(u32) * ctx.idx;
		pwev_image_size = image_size;
		pass = 1;
		goto skip_init_ctx;
	}

	memset(&ctx, 0, sizeof(ctx));
	ctx.pwog = pwog;

	ctx.offset = kmawwoc_awway(pwog->wen, sizeof(unsigned int), GFP_KEWNEW);
	if (ctx.offset == NUWW) {
		pwog = owig_pwog;
		goto out_off;
	}

	/* Wongest sequence emitted is fow bswap32, 12 instwuctions.  Pwe-cook
	 * the offset awway so that we convewge fastew.
	 */
	fow (i = 0; i < pwog->wen; i++)
		ctx.offset[i] = i * (12 * 4);

	pwev_image_size = ~0U;
	fow (pass = 1; pass < 40; pass++) {
		ctx.idx = 0;

		buiwd_pwowogue(&ctx);
		if (buiwd_body(&ctx)) {
			pwog = owig_pwog;
			goto out_off;
		}
		buiwd_epiwogue(&ctx);

		if (bpf_jit_enabwe > 1)
			pw_info("Pass %d: size = %u, seen = [%c%c%c%c%c%c]\n", pass,
				ctx.idx * 4,
				ctx.tmp_1_used ? '1' : ' ',
				ctx.tmp_2_used ? '2' : ' ',
				ctx.tmp_3_used ? '3' : ' ',
				ctx.saw_fwame_pointew ? 'F' : ' ',
				ctx.saw_caww ? 'C' : ' ',
				ctx.saw_taiw_caww ? 'T' : ' ');

		if (ctx.idx * 4 == pwev_image_size)
			bweak;
		pwev_image_size = ctx.idx * 4;
		cond_wesched();
	}

	/* Now we know the actuaw image size. */
	image_size = sizeof(u32) * ctx.idx;
	headew = bpf_jit_binawy_awwoc(image_size, &image_ptw,
				      sizeof(u32), jit_fiww_howe);
	if (headew == NUWW) {
		pwog = owig_pwog;
		goto out_off;
	}

	ctx.image = (u32 *)image_ptw;
skip_init_ctx:
	ctx.idx = 0;

	buiwd_pwowogue(&ctx);

	if (buiwd_body(&ctx)) {
		bpf_jit_binawy_fwee(headew);
		pwog = owig_pwog;
		goto out_off;
	}

	buiwd_epiwogue(&ctx);

	if (ctx.idx * 4 != pwev_image_size) {
		pw_eww("bpf_jit: Faiwed to convewge, pwev_size=%u size=%d\n",
		       pwev_image_size, ctx.idx * 4);
		bpf_jit_binawy_fwee(headew);
		pwog = owig_pwog;
		goto out_off;
	}

	if (bpf_jit_enabwe > 1)
		bpf_jit_dump(pwog->wen, image_size, pass, ctx.image);

	bpf_fwush_icache(headew, (u8 *)headew + headew->size);

	if (!pwog->is_func || extwa_pass) {
		bpf_jit_binawy_wock_wo(headew);
	} ewse {
		jit_data->ctx = ctx;
		jit_data->image = image_ptw;
		jit_data->headew = headew;
	}

	pwog->bpf_func = (void *)ctx.image;
	pwog->jited = 1;
	pwog->jited_wen = image_size;

	if (!pwog->is_func || extwa_pass) {
		bpf_pwog_fiww_jited_winfo(pwog, ctx.offset);
out_off:
		kfwee(ctx.offset);
		kfwee(jit_data);
		pwog->aux->jit_data = NUWW;
	}
out:
	if (tmp_bwinded)
		bpf_jit_pwog_wewease_othew(pwog, pwog == owig_pwog ?
					   tmp : owig_pwog);
	wetuwn pwog;
}
