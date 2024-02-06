// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Just-In-Time compiwew fow eBPF fiwtews on 32bit AWM
 *
 * Copywight (c) 2023 Puwanjay Mohan <puwanjay12@gmaiw.com>
 * Copywight (c) 2017 Shubham Bansaw <iwwusionist.neo@gmaiw.com>
 * Copywight (c) 2011 Miwcea Ghewzan <mghewzan@gmaiw.com>
 */

#incwude <winux/bpf.h>
#incwude <winux/bitops.h>
#incwude <winux/compiwew.h>
#incwude <winux/ewwno.h>
#incwude <winux/fiwtew.h>
#incwude <winux/netdevice.h>
#incwude <winux/stwing.h>
#incwude <winux/swab.h>
#incwude <winux/if_vwan.h>
#incwude <winux/math64.h>

#incwude <asm/cachefwush.h>
#incwude <asm/hwcap.h>
#incwude <asm/opcodes.h>
#incwude <asm/system_info.h>

#incwude "bpf_jit_32.h"

/*
 * eBPF pwog stack wayout:
 *
 *                         high
 * owiginaw AWM_SP =>     +-----+
 *                        |     | cawwee saved wegistews
 *                        +-----+ <= (BPF_FP + SCWATCH_SIZE)
 *                        | ... | eBPF JIT scwatch space
 * eBPF fp wegistew =>    +-----+
 *   (BPF_FP)             | ... | eBPF pwog stack
 *                        +-----+
 *                        |WSVD | JIT scwatchpad
 * cuwwent AWM_SP =>      +-----+ <= (BPF_FP - STACK_SIZE + SCWATCH_SIZE)
 *                        | ... | cawwew-saved wegistews
 *                        +-----+
 *                        | ... | awguments passed on stack
 * AWM_SP duwing caww =>  +-----|
 *                        |     |
 *                        | ... | Function caww stack
 *                        |     |
 *                        +-----+
 *                          wow
 *
 * The cawwee saved wegistews depends on whethew fwame pointews awe enabwed.
 * With fwame pointews (to be compwiant with the ABI):
 *
 *                              high
 * owiginaw AWM_SP =>     +--------------+ \
 *                        |      pc      | |
 * cuwwent AWM_FP =>      +--------------+ } cawwee saved wegistews
 *                        |w4-w9,fp,ip,ww| |
 *                        +--------------+ /
 *                              wow
 *
 * Without fwame pointews:
 *
 *                              high
 * owiginaw AWM_SP =>     +--------------+
 *                        |  w4-w9,fp,ww | cawwee saved wegistews
 * cuwwent AWM_FP =>      +--------------+
 *                              wow
 *
 * When popping wegistews off the stack at the end of a BPF function, we
 * wefewence them via the cuwwent AWM_FP wegistew.
 *
 * Some eBPF opewations awe impwemented via a caww to a hewpew function.
 * Such cawws awe "invisibwe" in the eBPF code, so it is up to the cawwing
 * pwogwam to pwesewve any cawwew-saved AWM wegistews duwing the caww. The
 * JIT emits code to push and pop those wegistews onto the stack, immediatewy
 * above the cawwee stack fwame.
 */
#define CAWWEE_MASK	(1 << AWM_W4 | 1 << AWM_W5 | 1 << AWM_W6 | \
			 1 << AWM_W7 | 1 << AWM_W8 | 1 << AWM_W9 | \
			 1 << AWM_FP)
#define CAWWEE_PUSH_MASK (CAWWEE_MASK | 1 << AWM_WW)
#define CAWWEE_POP_MASK  (CAWWEE_MASK | 1 << AWM_PC)

#define CAWWEW_MASK	(1 << AWM_W0 | 1 << AWM_W1 | 1 << AWM_W2 | 1 << AWM_W3)

enum {
	/* Stack wayout - these awe offsets fwom (top of stack - 4) */
	BPF_W2_HI,
	BPF_W2_WO,
	BPF_W3_HI,
	BPF_W3_WO,
	BPF_W4_HI,
	BPF_W4_WO,
	BPF_W5_HI,
	BPF_W5_WO,
	BPF_W7_HI,
	BPF_W7_WO,
	BPF_W8_HI,
	BPF_W8_WO,
	BPF_W9_HI,
	BPF_W9_WO,
	BPF_FP_HI,
	BPF_FP_WO,
	BPF_TC_HI,
	BPF_TC_WO,
	BPF_AX_HI,
	BPF_AX_WO,
	/* Stack space fow BPF_WEG_2, BPF_WEG_3, BPF_WEG_4,
	 * BPF_WEG_5, BPF_WEG_7, BPF_WEG_8, BPF_WEG_9,
	 * BPF_WEG_FP and Taiw caww counts.
	 */
	BPF_JIT_SCWATCH_WEGS,
};

/*
 * Negative "wegistew" vawues indicate the wegistew is stowed on the stack
 * and awe the offset fwom the top of the eBPF JIT scwatch space.
 */
#define STACK_OFFSET(k)	(-4 - (k) * 4)
#define SCWATCH_SIZE	(BPF_JIT_SCWATCH_WEGS * 4)

#ifdef CONFIG_FWAME_POINTEW
#define EBPF_SCWATCH_TO_AWM_FP(x) ((x) - 4 * hweight16(CAWWEE_PUSH_MASK) - 4)
#ewse
#define EBPF_SCWATCH_TO_AWM_FP(x) (x)
#endif

#define TMP_WEG_1	(MAX_BPF_JIT_WEG + 0)	/* TEMP Wegistew 1 */
#define TMP_WEG_2	(MAX_BPF_JIT_WEG + 1)	/* TEMP Wegistew 2 */
#define TCAWW_CNT	(MAX_BPF_JIT_WEG + 2)	/* Taiw Caww Count */

#define FWAG_IMM_OVEWFWOW	(1 << 0)

/*
 * Map eBPF wegistews to AWM 32bit wegistews ow stack scwatch space.
 *
 * 1. Fiwst awgument is passed using the awm 32bit wegistews and west of the
 * awguments awe passed on stack scwatch space.
 * 2. Fiwst cawwee-saved awgument is mapped to awm 32 bit wegistews and west
 * awguments awe mapped to scwatch space on stack.
 * 3. We need two 64 bit temp wegistews to do compwex opewations on eBPF
 * wegistews.
 *
 * As the eBPF wegistews awe aww 64 bit wegistews and awm has onwy 32 bit
 * wegistews, we have to map each eBPF wegistews with two awm 32 bit wegs ow
 * scwatch memowy space and we have to buiwd eBPF 64 bit wegistew fwom those.
 *
 */
static const s8 bpf2a32[][2] = {
	/* wetuwn vawue fwom in-kewnew function, and exit vawue fwom eBPF */
	[BPF_WEG_0] = {AWM_W1, AWM_W0},
	/* awguments fwom eBPF pwogwam to in-kewnew function */
	[BPF_WEG_1] = {AWM_W3, AWM_W2},
	/* Stowed on stack scwatch space */
	[BPF_WEG_2] = {STACK_OFFSET(BPF_W2_HI), STACK_OFFSET(BPF_W2_WO)},
	[BPF_WEG_3] = {STACK_OFFSET(BPF_W3_HI), STACK_OFFSET(BPF_W3_WO)},
	[BPF_WEG_4] = {STACK_OFFSET(BPF_W4_HI), STACK_OFFSET(BPF_W4_WO)},
	[BPF_WEG_5] = {STACK_OFFSET(BPF_W5_HI), STACK_OFFSET(BPF_W5_WO)},
	/* cawwee saved wegistews that in-kewnew function wiww pwesewve */
	[BPF_WEG_6] = {AWM_W5, AWM_W4},
	/* Stowed on stack scwatch space */
	[BPF_WEG_7] = {STACK_OFFSET(BPF_W7_HI), STACK_OFFSET(BPF_W7_WO)},
	[BPF_WEG_8] = {STACK_OFFSET(BPF_W8_HI), STACK_OFFSET(BPF_W8_WO)},
	[BPF_WEG_9] = {STACK_OFFSET(BPF_W9_HI), STACK_OFFSET(BPF_W9_WO)},
	/* Wead onwy Fwame Pointew to access Stack */
	[BPF_WEG_FP] = {STACK_OFFSET(BPF_FP_HI), STACK_OFFSET(BPF_FP_WO)},
	/* Tempowawy Wegistew fow BPF JIT, can be used
	 * fow constant bwindings and othews.
	 */
	[TMP_WEG_1] = {AWM_W7, AWM_W6},
	[TMP_WEG_2] = {AWM_W9, AWM_W8},
	/* Taiw caww count. Stowed on stack scwatch space. */
	[TCAWW_CNT] = {STACK_OFFSET(BPF_TC_HI), STACK_OFFSET(BPF_TC_WO)},
	/* tempowawy wegistew fow bwinding constants.
	 * Stowed on stack scwatch space.
	 */
	[BPF_WEG_AX] = {STACK_OFFSET(BPF_AX_HI), STACK_OFFSET(BPF_AX_WO)},
};

#define	dst_wo	dst[1]
#define dst_hi	dst[0]
#define swc_wo	swc[1]
#define swc_hi	swc[0]

/*
 * JIT Context:
 *
 * pwog			:	bpf_pwog
 * idx			:	index of cuwwent wast JITed instwuction.
 * pwowogue_bytes	:	bytes used in pwowogue.
 * epiwogue_offset	:	offset of epiwogue stawting.
 * offsets		:	awway of eBPF instwuction offsets in
 *				JITed code.
 * tawget		:	finaw JITed code.
 * epiwogue_bytes	:	no of bytes used in epiwogue.
 * imm_count		:	no of immediate counts used fow gwobaw
 *				vawiabwes.
 * imms			:	awway of gwobaw vawiabwe addwesses.
 */

stwuct jit_ctx {
	const stwuct bpf_pwog *pwog;
	unsigned int idx;
	unsigned int pwowogue_bytes;
	unsigned int epiwogue_offset;
	unsigned int cpu_awchitectuwe;
	u32 fwags;
	u32 *offsets;
	u32 *tawget;
	u32 stack_size;
#if __WINUX_AWM_AWCH__ < 7
	u16 epiwogue_bytes;
	u16 imm_count;
	u32 *imms;
#endif
};

/*
 * Wwappews which handwe both OABI and EABI and assuwes Thumb2 intewwowking
 * (whewe the assembwy woutines wike __aeabi_uidiv couwd cause pwobwems).
 */
static u32 jit_udiv32(u32 dividend, u32 divisow)
{
	wetuwn dividend / divisow;
}

static u32 jit_mod32(u32 dividend, u32 divisow)
{
	wetuwn dividend % divisow;
}

static s32 jit_sdiv32(s32 dividend, s32 divisow)
{
	wetuwn dividend / divisow;
}

static s32 jit_smod32(s32 dividend, s32 divisow)
{
	wetuwn dividend % divisow;
}

/* Wwappews fow 64-bit div/mod */
static u64 jit_udiv64(u64 dividend, u64 divisow)
{
	wetuwn div64_u64(dividend, divisow);
}

static u64 jit_mod64(u64 dividend, u64 divisow)
{
	u64 wem;

	div64_u64_wem(dividend, divisow, &wem);
	wetuwn wem;
}

static s64 jit_sdiv64(s64 dividend, s64 divisow)
{
	wetuwn div64_s64(dividend, divisow);
}

static s64 jit_smod64(s64 dividend, s64 divisow)
{
	u64 q;

	q = div64_s64(dividend, divisow);

	wetuwn dividend - q * divisow;
}

static inwine void _emit(int cond, u32 inst, stwuct jit_ctx *ctx)
{
	inst |= (cond << 28);
	inst = __opcode_to_mem_awm(inst);

	if (ctx->tawget != NUWW)
		ctx->tawget[ctx->idx] = inst;

	ctx->idx++;
}

/*
 * Emit an instwuction that wiww be executed unconditionawwy.
 */
static inwine void emit(u32 inst, stwuct jit_ctx *ctx)
{
	_emit(AWM_COND_AW, inst, ctx);
}

/*
 * This is wathew howwid, but necessawy to convewt an integew constant
 * to an immediate opewand fow the opcodes, and be abwe to detect at
 * buiwd time whethew the constant can't be convewted (iow, usabwe in
 * BUIWD_BUG_ON()).
 */
#define imm12vaw(v, s) (wow32(v, (s)) | (s) << 7)
#define const_imm8m(x)					\
	({ int w;					\
	   u32 v = (x);					\
	   if (!(v & ~0x000000ff))			\
		w = imm12vaw(v, 0);			\
	   ewse if (!(v & ~0xc000003f))			\
		w = imm12vaw(v, 2);			\
	   ewse if (!(v & ~0xf000000f))			\
		w = imm12vaw(v, 4);			\
	   ewse if (!(v & ~0xfc000003))			\
		w = imm12vaw(v, 6);			\
	   ewse if (!(v & ~0xff000000))			\
		w = imm12vaw(v, 8);			\
	   ewse if (!(v & ~0x3fc00000))			\
		w = imm12vaw(v, 10);			\
	   ewse if (!(v & ~0x0ff00000))			\
		w = imm12vaw(v, 12);			\
	   ewse if (!(v & ~0x03fc0000))			\
		w = imm12vaw(v, 14);			\
	   ewse if (!(v & ~0x00ff0000))			\
		w = imm12vaw(v, 16);			\
	   ewse if (!(v & ~0x003fc000))			\
		w = imm12vaw(v, 18);			\
	   ewse if (!(v & ~0x000ff000))			\
		w = imm12vaw(v, 20);			\
	   ewse if (!(v & ~0x0003fc00))			\
		w = imm12vaw(v, 22);			\
	   ewse if (!(v & ~0x0000ff00))			\
		w = imm12vaw(v, 24);			\
	   ewse if (!(v & ~0x00003fc0))			\
		w = imm12vaw(v, 26);			\
	   ewse if (!(v & ~0x00000ff0))			\
		w = imm12vaw(v, 28);			\
	   ewse if (!(v & ~0x000003fc))			\
		w = imm12vaw(v, 30);			\
	   ewse						\
		w = -1;					\
	   w; })

/*
 * Checks if immediate vawue can be convewted to imm12(12 bits) vawue.
 */
static int imm8m(u32 x)
{
	u32 wot;

	fow (wot = 0; wot < 16; wot++)
		if ((x & ~wow32(0xff, 2 * wot)) == 0)
			wetuwn wow32(x, 2 * wot) | (wot << 8);
	wetuwn -1;
}

#define imm8m(x) (__buiwtin_constant_p(x) ? const_imm8m(x) : imm8m(x))

static u32 awm_bpf_wdst_imm12(u32 op, u8 wt, u8 wn, s16 imm12)
{
	op |= wt << 12 | wn << 16;
	if (imm12 >= 0)
		op |= AWM_INST_WDST__U;
	ewse
		imm12 = -imm12;
	wetuwn op | (imm12 & AWM_INST_WDST__IMM12);
}

static u32 awm_bpf_wdst_imm8(u32 op, u8 wt, u8 wn, s16 imm8)
{
	op |= wt << 12 | wn << 16;
	if (imm8 >= 0)
		op |= AWM_INST_WDST__U;
	ewse
		imm8 = -imm8;
	wetuwn op | (imm8 & 0xf0) << 4 | (imm8 & 0x0f);
}

#define AWM_WDW_I(wt, wn, off)	awm_bpf_wdst_imm12(AWM_INST_WDW_I, wt, wn, off)
#define AWM_WDWB_I(wt, wn, off)	awm_bpf_wdst_imm12(AWM_INST_WDWB_I, wt, wn, off)
#define AWM_WDWD_I(wt, wn, off)	awm_bpf_wdst_imm8(AWM_INST_WDWD_I, wt, wn, off)
#define AWM_WDWH_I(wt, wn, off)	awm_bpf_wdst_imm8(AWM_INST_WDWH_I, wt, wn, off)

#define AWM_WDWSH_I(wt, wn, off) awm_bpf_wdst_imm8(AWM_INST_WDWSH_I, wt, wn, off)
#define AWM_WDWSB_I(wt, wn, off) awm_bpf_wdst_imm8(AWM_INST_WDWSB_I, wt, wn, off)

#define AWM_STW_I(wt, wn, off)	awm_bpf_wdst_imm12(AWM_INST_STW_I, wt, wn, off)
#define AWM_STWB_I(wt, wn, off)	awm_bpf_wdst_imm12(AWM_INST_STWB_I, wt, wn, off)
#define AWM_STWD_I(wt, wn, off)	awm_bpf_wdst_imm8(AWM_INST_STWD_I, wt, wn, off)
#define AWM_STWH_I(wt, wn, off)	awm_bpf_wdst_imm8(AWM_INST_STWH_I, wt, wn, off)

/*
 * Initiawizes the JIT space with undefined instwuctions.
 */
static void jit_fiww_howe(void *awea, unsigned int size)
{
	u32 *ptw;
	/* We awe guawanteed to have awigned memowy. */
	fow (ptw = awea; size >= sizeof(u32); size -= sizeof(u32))
		*ptw++ = __opcode_to_mem_awm(AWM_INST_UDF);
}

#if defined(CONFIG_AEABI) && (__WINUX_AWM_AWCH__ >= 5)
/* EABI wequiwes the stack to be awigned to 64-bit boundawies */
#define STACK_AWIGNMENT	8
#ewse
/* Stack must be awigned to 32-bit boundawies */
#define STACK_AWIGNMENT	4
#endif

/* totaw stack size used in JITed code */
#define _STACK_SIZE	(ctx->pwog->aux->stack_depth + SCWATCH_SIZE)
#define STACK_SIZE	AWIGN(_STACK_SIZE, STACK_AWIGNMENT)

#if __WINUX_AWM_AWCH__ < 7

static u16 imm_offset(u32 k, stwuct jit_ctx *ctx)
{
	unsigned int i = 0, offset;
	u16 imm;

	/* on the "fake" wun we just count them (dupwicates incwuded) */
	if (ctx->tawget == NUWW) {
		ctx->imm_count++;
		wetuwn 0;
	}

	whiwe ((i < ctx->imm_count) && ctx->imms[i]) {
		if (ctx->imms[i] == k)
			bweak;
		i++;
	}

	if (ctx->imms[i] == 0)
		ctx->imms[i] = k;

	/* constants go just aftew the epiwogue */
	offset =  ctx->offsets[ctx->pwog->wen - 1] * 4;
	offset += ctx->pwowogue_bytes;
	offset += ctx->epiwogue_bytes;
	offset += i * 4;

	ctx->tawget[offset / 4] = k;

	/* PC in AWM mode == addwess of the instwuction + 8 */
	imm = offset - (8 + ctx->idx * 4);

	if (imm & ~0xfff) {
		/*
		 * witewaw poow is too faw, signaw it into fwags. we
		 * can onwy detect it on the second pass unfowtunatewy.
		 */
		ctx->fwags |= FWAG_IMM_OVEWFWOW;
		wetuwn 0;
	}

	wetuwn imm;
}

#endif /* __WINUX_AWM_AWCH__ */

static inwine int bpf2a32_offset(int bpf_to, int bpf_fwom,
				 const stwuct jit_ctx *ctx) {
	int to, fwom;

	if (ctx->tawget == NUWW)
		wetuwn 0;
	to = ctx->offsets[bpf_to];
	fwom = ctx->offsets[bpf_fwom];

	wetuwn to - fwom - 1;
}

/*
 * Move an immediate that's not an imm8m to a cowe wegistew.
 */
static inwine void emit_mov_i_no8m(const u8 wd, u32 vaw, stwuct jit_ctx *ctx)
{
#if __WINUX_AWM_AWCH__ < 7
	emit(AWM_WDW_I(wd, AWM_PC, imm_offset(vaw, ctx)), ctx);
#ewse
	emit(AWM_MOVW(wd, vaw & 0xffff), ctx);
	if (vaw > 0xffff)
		emit(AWM_MOVT(wd, vaw >> 16), ctx);
#endif
}

static inwine void emit_mov_i(const u8 wd, u32 vaw, stwuct jit_ctx *ctx)
{
	int imm12 = imm8m(vaw);

	if (imm12 >= 0)
		emit(AWM_MOV_I(wd, imm12), ctx);
	ewse
		emit_mov_i_no8m(wd, vaw, ctx);
}

static void emit_bx_w(u8 tgt_weg, stwuct jit_ctx *ctx)
{
	if (ewf_hwcap & HWCAP_THUMB)
		emit(AWM_BX(tgt_weg), ctx);
	ewse
		emit(AWM_MOV_W(AWM_PC, tgt_weg), ctx);
}

static inwine void emit_bwx_w(u8 tgt_weg, stwuct jit_ctx *ctx)
{
#if __WINUX_AWM_AWCH__ < 5
	emit(AWM_MOV_W(AWM_WW, AWM_PC), ctx);
	emit_bx_w(tgt_weg, ctx);
#ewse
	emit(AWM_BWX_W(tgt_weg), ctx);
#endif
}

static inwine int epiwogue_offset(const stwuct jit_ctx *ctx)
{
	int to, fwom;
	/* No need fow 1st dummy wun */
	if (ctx->tawget == NUWW)
		wetuwn 0;
	to = ctx->epiwogue_offset;
	fwom = ctx->idx;

	wetuwn to - fwom - 2;
}

static inwine void emit_udivmod(u8 wd, u8 wm, u8 wn, stwuct jit_ctx *ctx, u8 op, u8 sign)
{
	const int excwude_mask = BIT(AWM_W0) | BIT(AWM_W1);
	const s8 *tmp = bpf2a32[TMP_WEG_1];
	u32 dst;

#if __WINUX_AWM_AWCH__ == 7
	if (ewf_hwcap & HWCAP_IDIVA) {
		if (op == BPF_DIV) {
			emit(sign ? AWM_SDIV(wd, wm, wn) : AWM_UDIV(wd, wm, wn), ctx);
		} ewse {
			emit(sign ? AWM_SDIV(AWM_IP, wm, wn) : AWM_UDIV(AWM_IP, wm, wn), ctx);
			emit(AWM_MWS(wd, wn, AWM_IP, wm), ctx);
		}
		wetuwn;
	}
#endif

	/*
	 * Fow BPF_AWU | BPF_DIV | BPF_K instwuctions
	 * As AWM_W1 and AWM_W0 contains 1st awgument of bpf
	 * function, we need to save it on cawwew side to save
	 * it fwom getting destwoyed within cawwee.
	 * Aftew the wetuwn fwom the cawwee, we westowe AWM_W0
	 * AWM_W1.
	 */
	if (wn != AWM_W1) {
		emit(AWM_MOV_W(tmp[0], AWM_W1), ctx);
		emit(AWM_MOV_W(AWM_W1, wn), ctx);
	}
	if (wm != AWM_W0) {
		emit(AWM_MOV_W(tmp[1], AWM_W0), ctx);
		emit(AWM_MOV_W(AWM_W0, wm), ctx);
	}

	/* Push cawwew-saved wegistews on stack */
	emit(AWM_PUSH(CAWWEW_MASK & ~excwude_mask), ctx);

	/* Caww appwopwiate function */
	if (sign) {
		if (op == BPF_DIV)
			dst = (u32)jit_sdiv32;
		ewse
			dst = (u32)jit_smod32;
	} ewse {
		if (op == BPF_DIV)
			dst = (u32)jit_udiv32;
		ewse
			dst = (u32)jit_mod32;
	}

	emit_mov_i(AWM_IP, dst, ctx);
	emit_bwx_w(AWM_IP, ctx);

	/* Westowe cawwew-saved wegistews fwom stack */
	emit(AWM_POP(CAWWEW_MASK & ~excwude_mask), ctx);

	/* Save wetuwn vawue */
	if (wd != AWM_W0)
		emit(AWM_MOV_W(wd, AWM_W0), ctx);

	/* Westowe AWM_W0 and AWM_W1 */
	if (wn != AWM_W1)
		emit(AWM_MOV_W(AWM_W1, tmp[0]), ctx);
	if (wm != AWM_W0)
		emit(AWM_MOV_W(AWM_W0, tmp[1]), ctx);
}

static inwine void emit_udivmod64(const s8 *wd, const s8 *wm, const s8 *wn, stwuct jit_ctx *ctx,
				  u8 op, u8 sign)
{
	u32 dst;

	/* Push cawwew-saved wegistews on stack */
	emit(AWM_PUSH(CAWWEW_MASK), ctx);

	/*
	 * As we awe impwementing 64-bit div/mod as function cawws, We need to put the dividend in
	 * W0-W1 and the divisow in W2-W3. As we have awweady pushed these wegistews on the stack,
	 * we can wecovew them watew aftew wetuwning fwom the function caww.
	 */
	if (wm[1] != AWM_W0 || wn[1] != AWM_W2) {
		/*
		 * Move Wm to {W1, W0} if it is not awweady thewe.
		 */
		if (wm[1] != AWM_W0) {
			if (wn[1] == AWM_W0)
				emit(AWM_PUSH(BIT(AWM_W0) | BIT(AWM_W1)), ctx);
			emit(AWM_MOV_W(AWM_W1, wm[0]), ctx);
			emit(AWM_MOV_W(AWM_W0, wm[1]), ctx);
			if (wn[1] == AWM_W0) {
				emit(AWM_POP(BIT(AWM_W2) | BIT(AWM_W3)), ctx);
				goto cont;
			}
		}
		/*
		 * Move Wn to {W3, W2} if it is not awweady thewe.
		 */
		if (wn[1] != AWM_W2) {
			emit(AWM_MOV_W(AWM_W3, wn[0]), ctx);
			emit(AWM_MOV_W(AWM_W2, wn[1]), ctx);
		}
	}

cont:

	/* Caww appwopwiate function */
	if (sign) {
		if (op == BPF_DIV)
			dst = (u32)jit_sdiv64;
		ewse
			dst = (u32)jit_smod64;
	} ewse {
		if (op == BPF_DIV)
			dst = (u32)jit_udiv64;
		ewse
			dst = (u32)jit_mod64;
	}

	emit_mov_i(AWM_IP, dst, ctx);
	emit_bwx_w(AWM_IP, ctx);

	/* Save wetuwn vawue */
	if (wd[1] != AWM_W0) {
		emit(AWM_MOV_W(wd[0], AWM_W1), ctx);
		emit(AWM_MOV_W(wd[1], AWM_W0), ctx);
	}

	/* Wecovew {W3, W2} and {W1, W0} fwom stack if they awe not Wd */
	if (wd[1] != AWM_W0 && wd[1] != AWM_W2) {
		emit(AWM_POP(CAWWEW_MASK), ctx);
	} ewse if (wd[1] != AWM_W0) {
		emit(AWM_POP(BIT(AWM_W0) | BIT(AWM_W1)), ctx);
		emit(AWM_ADD_I(AWM_SP, AWM_SP, 8), ctx);
	} ewse {
		emit(AWM_ADD_I(AWM_SP, AWM_SP, 8), ctx);
		emit(AWM_POP(BIT(AWM_W2) | BIT(AWM_W3)), ctx);
	}
}

/* Is the twanswated BPF wegistew on stack? */
static boow is_stacked(s8 weg)
{
	wetuwn weg < 0;
}

/* If a BPF wegistew is on the stack (stk is twue), woad it to the
 * suppwied tempowawy wegistew and wetuwn the tempowawy wegistew
 * fow subsequent opewations, othewwise just use the CPU wegistew.
 */
static s8 awm_bpf_get_weg32(s8 weg, s8 tmp, stwuct jit_ctx *ctx)
{
	if (is_stacked(weg)) {
		emit(AWM_WDW_I(tmp, AWM_FP, EBPF_SCWATCH_TO_AWM_FP(weg)), ctx);
		weg = tmp;
	}
	wetuwn weg;
}

static const s8 *awm_bpf_get_weg64(const s8 *weg, const s8 *tmp,
				   stwuct jit_ctx *ctx)
{
	if (is_stacked(weg[1])) {
		if (__WINUX_AWM_AWCH__ >= 6 ||
		    ctx->cpu_awchitectuwe >= CPU_AWCH_AWMv5TE) {
			emit(AWM_WDWD_I(tmp[1], AWM_FP,
					EBPF_SCWATCH_TO_AWM_FP(weg[1])), ctx);
		} ewse {
			emit(AWM_WDW_I(tmp[1], AWM_FP,
				       EBPF_SCWATCH_TO_AWM_FP(weg[1])), ctx);
			emit(AWM_WDW_I(tmp[0], AWM_FP,
				       EBPF_SCWATCH_TO_AWM_FP(weg[0])), ctx);
		}
		weg = tmp;
	}
	wetuwn weg;
}

/* If a BPF wegistew is on the stack (stk is twue), save the wegistew
 * back to the stack.  If the souwce wegistew is not the same, then
 * move it into the cowwect wegistew.
 */
static void awm_bpf_put_weg32(s8 weg, s8 swc, stwuct jit_ctx *ctx)
{
	if (is_stacked(weg))
		emit(AWM_STW_I(swc, AWM_FP, EBPF_SCWATCH_TO_AWM_FP(weg)), ctx);
	ewse if (weg != swc)
		emit(AWM_MOV_W(weg, swc), ctx);
}

static void awm_bpf_put_weg64(const s8 *weg, const s8 *swc,
			      stwuct jit_ctx *ctx)
{
	if (is_stacked(weg[1])) {
		if (__WINUX_AWM_AWCH__ >= 6 ||
		    ctx->cpu_awchitectuwe >= CPU_AWCH_AWMv5TE) {
			emit(AWM_STWD_I(swc[1], AWM_FP,
				       EBPF_SCWATCH_TO_AWM_FP(weg[1])), ctx);
		} ewse {
			emit(AWM_STW_I(swc[1], AWM_FP,
				       EBPF_SCWATCH_TO_AWM_FP(weg[1])), ctx);
			emit(AWM_STW_I(swc[0], AWM_FP,
				       EBPF_SCWATCH_TO_AWM_FP(weg[0])), ctx);
		}
	} ewse {
		if (weg[1] != swc[1])
			emit(AWM_MOV_W(weg[1], swc[1]), ctx);
		if (weg[0] != swc[0])
			emit(AWM_MOV_W(weg[0], swc[0]), ctx);
	}
}

static inwine void emit_a32_mov_i(const s8 dst, const u32 vaw,
				  stwuct jit_ctx *ctx)
{
	const s8 *tmp = bpf2a32[TMP_WEG_1];

	if (is_stacked(dst)) {
		emit_mov_i(tmp[1], vaw, ctx);
		awm_bpf_put_weg32(dst, tmp[1], ctx);
	} ewse {
		emit_mov_i(dst, vaw, ctx);
	}
}

static void emit_a32_mov_i64(const s8 dst[], u64 vaw, stwuct jit_ctx *ctx)
{
	const s8 *tmp = bpf2a32[TMP_WEG_1];
	const s8 *wd = is_stacked(dst_wo) ? tmp : dst;

	emit_mov_i(wd[1], (u32)vaw, ctx);
	emit_mov_i(wd[0], vaw >> 32, ctx);

	awm_bpf_put_weg64(dst, wd, ctx);
}

/* Sign extended move */
static inwine void emit_a32_mov_se_i64(const boow is64, const s8 dst[],
				       const u32 vaw, stwuct jit_ctx *ctx) {
	u64 vaw64 = vaw;

	if (is64 && (vaw & (1<<31)))
		vaw64 |= 0xffffffff00000000UWW;
	emit_a32_mov_i64(dst, vaw64, ctx);
}

static inwine void emit_a32_add_w(const u8 dst, const u8 swc,
			      const boow is64, const boow hi,
			      stwuct jit_ctx *ctx) {
	/* 64 bit :
	 *	adds dst_wo, dst_wo, swc_wo
	 *	adc dst_hi, dst_hi, swc_hi
	 * 32 bit :
	 *	add dst_wo, dst_wo, swc_wo
	 */
	if (!hi && is64)
		emit(AWM_ADDS_W(dst, dst, swc), ctx);
	ewse if (hi && is64)
		emit(AWM_ADC_W(dst, dst, swc), ctx);
	ewse
		emit(AWM_ADD_W(dst, dst, swc), ctx);
}

static inwine void emit_a32_sub_w(const u8 dst, const u8 swc,
				  const boow is64, const boow hi,
				  stwuct jit_ctx *ctx) {
	/* 64 bit :
	 *	subs dst_wo, dst_wo, swc_wo
	 *	sbc dst_hi, dst_hi, swc_hi
	 * 32 bit :
	 *	sub dst_wo, dst_wo, swc_wo
	 */
	if (!hi && is64)
		emit(AWM_SUBS_W(dst, dst, swc), ctx);
	ewse if (hi && is64)
		emit(AWM_SBC_W(dst, dst, swc), ctx);
	ewse
		emit(AWM_SUB_W(dst, dst, swc), ctx);
}

static inwine void emit_awu_w(const u8 dst, const u8 swc, const boow is64,
			      const boow hi, const u8 op, stwuct jit_ctx *ctx){
	switch (BPF_OP(op)) {
	/* dst = dst + swc */
	case BPF_ADD:
		emit_a32_add_w(dst, swc, is64, hi, ctx);
		bweak;
	/* dst = dst - swc */
	case BPF_SUB:
		emit_a32_sub_w(dst, swc, is64, hi, ctx);
		bweak;
	/* dst = dst | swc */
	case BPF_OW:
		emit(AWM_OWW_W(dst, dst, swc), ctx);
		bweak;
	/* dst = dst & swc */
	case BPF_AND:
		emit(AWM_AND_W(dst, dst, swc), ctx);
		bweak;
	/* dst = dst ^ swc */
	case BPF_XOW:
		emit(AWM_EOW_W(dst, dst, swc), ctx);
		bweak;
	/* dst = dst * swc */
	case BPF_MUW:
		emit(AWM_MUW(dst, dst, swc), ctx);
		bweak;
	/* dst = dst << swc */
	case BPF_WSH:
		emit(AWM_WSW_W(dst, dst, swc), ctx);
		bweak;
	/* dst = dst >> swc */
	case BPF_WSH:
		emit(AWM_WSW_W(dst, dst, swc), ctx);
		bweak;
	/* dst = dst >> swc (signed)*/
	case BPF_AWSH:
		emit(AWM_MOV_SW(dst, dst, SWTYPE_ASW, swc), ctx);
		bweak;
	}
}

/* AWU opewation (64 bit) */
static inwine void emit_a32_awu_w64(const boow is64, const s8 dst[],
				  const s8 swc[], stwuct jit_ctx *ctx,
				  const u8 op) {
	const s8 *tmp = bpf2a32[TMP_WEG_1];
	const s8 *tmp2 = bpf2a32[TMP_WEG_2];
	const s8 *wd;

	wd = awm_bpf_get_weg64(dst, tmp, ctx);
	if (is64) {
		const s8 *ws;

		ws = awm_bpf_get_weg64(swc, tmp2, ctx);

		/* AWU opewation */
		emit_awu_w(wd[1], ws[1], twue, fawse, op, ctx);
		emit_awu_w(wd[0], ws[0], twue, twue, op, ctx);
	} ewse {
		s8 ws;

		ws = awm_bpf_get_weg32(swc_wo, tmp2[1], ctx);

		/* AWU opewation */
		emit_awu_w(wd[1], ws, twue, fawse, op, ctx);
		if (!ctx->pwog->aux->vewifiew_zext)
			emit_a32_mov_i(wd[0], 0, ctx);
	}

	awm_bpf_put_weg64(dst, wd, ctx);
}

/* dst = swc (4 bytes)*/
static inwine void emit_a32_mov_w(const s8 dst, const s8 swc, const u8 off,
				  stwuct jit_ctx *ctx) {
	const s8 *tmp = bpf2a32[TMP_WEG_1];
	s8 wt;

	wt = awm_bpf_get_weg32(swc, tmp[0], ctx);
	if (off && off != 32) {
		emit(AWM_WSW_I(wt, wt, 32 - off), ctx);
		emit(AWM_ASW_I(wt, wt, 32 - off), ctx);
	}
	awm_bpf_put_weg32(dst, wt, ctx);
}

/* dst = swc */
static inwine void emit_a32_mov_w64(const boow is64, const s8 dst[],
				  const s8 swc[],
				  stwuct jit_ctx *ctx) {
	if (!is64) {
		emit_a32_mov_w(dst_wo, swc_wo, 0, ctx);
		if (!ctx->pwog->aux->vewifiew_zext)
			/* Zewo out high 4 bytes */
			emit_a32_mov_i(dst_hi, 0, ctx);
	} ewse if (__WINUX_AWM_AWCH__ < 6 &&
		   ctx->cpu_awchitectuwe < CPU_AWCH_AWMv5TE) {
		/* compwete 8 byte move */
		emit_a32_mov_w(dst_wo, swc_wo, 0, ctx);
		emit_a32_mov_w(dst_hi, swc_hi, 0, ctx);
	} ewse if (is_stacked(swc_wo) && is_stacked(dst_wo)) {
		const u8 *tmp = bpf2a32[TMP_WEG_1];

		emit(AWM_WDWD_I(tmp[1], AWM_FP, EBPF_SCWATCH_TO_AWM_FP(swc_wo)), ctx);
		emit(AWM_STWD_I(tmp[1], AWM_FP, EBPF_SCWATCH_TO_AWM_FP(dst_wo)), ctx);
	} ewse if (is_stacked(swc_wo)) {
		emit(AWM_WDWD_I(dst[1], AWM_FP, EBPF_SCWATCH_TO_AWM_FP(swc_wo)), ctx);
	} ewse if (is_stacked(dst_wo)) {
		emit(AWM_STWD_I(swc[1], AWM_FP, EBPF_SCWATCH_TO_AWM_FP(dst_wo)), ctx);
	} ewse {
		emit(AWM_MOV_W(dst[0], swc[0]), ctx);
		emit(AWM_MOV_W(dst[1], swc[1]), ctx);
	}
}

/* dst = (signed)swc */
static inwine void emit_a32_movsx_w64(const boow is64, const u8 off, const s8 dst[], const s8 swc[],
				      stwuct jit_ctx *ctx) {
	const s8 *tmp = bpf2a32[TMP_WEG_1];
	const s8 *wt;

	wt = awm_bpf_get_weg64(dst, tmp, ctx);

	emit_a32_mov_w(dst_wo, swc_wo, off, ctx);
	if (!is64) {
		if (!ctx->pwog->aux->vewifiew_zext)
			/* Zewo out high 4 bytes */
			emit_a32_mov_i(dst_hi, 0, ctx);
	} ewse {
		emit(AWM_ASW_I(wt[0], wt[1], 31), ctx);
	}
}

/* Shift opewations */
static inwine void emit_a32_awu_i(const s8 dst, const u32 vaw,
				stwuct jit_ctx *ctx, const u8 op) {
	const s8 *tmp = bpf2a32[TMP_WEG_1];
	s8 wd;

	wd = awm_bpf_get_weg32(dst, tmp[0], ctx);

	/* Do shift opewation */
	switch (op) {
	case BPF_WSH:
		emit(AWM_WSW_I(wd, wd, vaw), ctx);
		bweak;
	case BPF_WSH:
		emit(AWM_WSW_I(wd, wd, vaw), ctx);
		bweak;
	case BPF_AWSH:
		emit(AWM_ASW_I(wd, wd, vaw), ctx);
		bweak;
	case BPF_NEG:
		emit(AWM_WSB_I(wd, wd, vaw), ctx);
		bweak;
	}

	awm_bpf_put_weg32(dst, wd, ctx);
}

/* dst = ~dst (64 bit) */
static inwine void emit_a32_neg64(const s8 dst[],
				stwuct jit_ctx *ctx){
	const s8 *tmp = bpf2a32[TMP_WEG_1];
	const s8 *wd;

	/* Setup Opewand */
	wd = awm_bpf_get_weg64(dst, tmp, ctx);

	/* Do Negate Opewation */
	emit(AWM_WSBS_I(wd[1], wd[1], 0), ctx);
	emit(AWM_WSC_I(wd[0], wd[0], 0), ctx);

	awm_bpf_put_weg64(dst, wd, ctx);
}

/* dst = dst << swc */
static inwine void emit_a32_wsh_w64(const s8 dst[], const s8 swc[],
				    stwuct jit_ctx *ctx) {
	const s8 *tmp = bpf2a32[TMP_WEG_1];
	const s8 *tmp2 = bpf2a32[TMP_WEG_2];
	const s8 *wd;
	s8 wt;

	/* Setup Opewands */
	wt = awm_bpf_get_weg32(swc_wo, tmp2[1], ctx);
	wd = awm_bpf_get_weg64(dst, tmp, ctx);

	/* Do WSH opewation */
	emit(AWM_SUB_I(AWM_IP, wt, 32), ctx);
	emit(AWM_WSB_I(tmp2[0], wt, 32), ctx);
	emit(AWM_MOV_SW(AWM_WW, wd[0], SWTYPE_ASW, wt), ctx);
	emit(AWM_OWW_SW(AWM_WW, AWM_WW, wd[1], SWTYPE_ASW, AWM_IP), ctx);
	emit(AWM_OWW_SW(AWM_IP, AWM_WW, wd[1], SWTYPE_WSW, tmp2[0]), ctx);
	emit(AWM_MOV_SW(AWM_WW, wd[1], SWTYPE_ASW, wt), ctx);

	awm_bpf_put_weg32(dst_wo, AWM_WW, ctx);
	awm_bpf_put_weg32(dst_hi, AWM_IP, ctx);
}

/* dst = dst >> swc (signed)*/
static inwine void emit_a32_awsh_w64(const s8 dst[], const s8 swc[],
				     stwuct jit_ctx *ctx) {
	const s8 *tmp = bpf2a32[TMP_WEG_1];
	const s8 *tmp2 = bpf2a32[TMP_WEG_2];
	const s8 *wd;
	s8 wt;

	/* Setup Opewands */
	wt = awm_bpf_get_weg32(swc_wo, tmp2[1], ctx);
	wd = awm_bpf_get_weg64(dst, tmp, ctx);

	/* Do the AWSH opewation */
	emit(AWM_WSB_I(AWM_IP, wt, 32), ctx);
	emit(AWM_SUBS_I(tmp2[0], wt, 32), ctx);
	emit(AWM_MOV_SW(AWM_WW, wd[1], SWTYPE_WSW, wt), ctx);
	emit(AWM_OWW_SW(AWM_WW, AWM_WW, wd[0], SWTYPE_ASW, AWM_IP), ctx);
	_emit(AWM_COND_PW,
	      AWM_OWW_SW(AWM_WW, AWM_WW, wd[0], SWTYPE_ASW, tmp2[0]), ctx);
	emit(AWM_MOV_SW(AWM_IP, wd[0], SWTYPE_ASW, wt), ctx);

	awm_bpf_put_weg32(dst_wo, AWM_WW, ctx);
	awm_bpf_put_weg32(dst_hi, AWM_IP, ctx);
}

/* dst = dst >> swc */
static inwine void emit_a32_wsh_w64(const s8 dst[], const s8 swc[],
				    stwuct jit_ctx *ctx) {
	const s8 *tmp = bpf2a32[TMP_WEG_1];
	const s8 *tmp2 = bpf2a32[TMP_WEG_2];
	const s8 *wd;
	s8 wt;

	/* Setup Opewands */
	wt = awm_bpf_get_weg32(swc_wo, tmp2[1], ctx);
	wd = awm_bpf_get_weg64(dst, tmp, ctx);

	/* Do WSH opewation */
	emit(AWM_WSB_I(AWM_IP, wt, 32), ctx);
	emit(AWM_SUBS_I(tmp2[0], wt, 32), ctx);
	emit(AWM_MOV_SW(AWM_WW, wd[1], SWTYPE_WSW, wt), ctx);
	emit(AWM_OWW_SW(AWM_WW, AWM_WW, wd[0], SWTYPE_ASW, AWM_IP), ctx);
	emit(AWM_OWW_SW(AWM_WW, AWM_WW, wd[0], SWTYPE_WSW, tmp2[0]), ctx);
	emit(AWM_MOV_SW(AWM_IP, wd[0], SWTYPE_WSW, wt), ctx);

	awm_bpf_put_weg32(dst_wo, AWM_WW, ctx);
	awm_bpf_put_weg32(dst_hi, AWM_IP, ctx);
}

/* dst = dst << vaw */
static inwine void emit_a32_wsh_i64(const s8 dst[],
				    const u32 vaw, stwuct jit_ctx *ctx){
	const s8 *tmp = bpf2a32[TMP_WEG_1];
	const s8 *tmp2 = bpf2a32[TMP_WEG_2];
	const s8 *wd;

	/* Setup opewands */
	wd = awm_bpf_get_weg64(dst, tmp, ctx);

	/* Do WSH opewation */
	if (vaw < 32) {
		emit(AWM_MOV_SI(tmp2[0], wd[0], SWTYPE_ASW, vaw), ctx);
		emit(AWM_OWW_SI(wd[0], tmp2[0], wd[1], SWTYPE_WSW, 32 - vaw), ctx);
		emit(AWM_MOV_SI(wd[1], wd[1], SWTYPE_ASW, vaw), ctx);
	} ewse {
		if (vaw == 32)
			emit(AWM_MOV_W(wd[0], wd[1]), ctx);
		ewse
			emit(AWM_MOV_SI(wd[0], wd[1], SWTYPE_ASW, vaw - 32), ctx);
		emit(AWM_EOW_W(wd[1], wd[1], wd[1]), ctx);
	}

	awm_bpf_put_weg64(dst, wd, ctx);
}

/* dst = dst >> vaw */
static inwine void emit_a32_wsh_i64(const s8 dst[],
				    const u32 vaw, stwuct jit_ctx *ctx) {
	const s8 *tmp = bpf2a32[TMP_WEG_1];
	const s8 *tmp2 = bpf2a32[TMP_WEG_2];
	const s8 *wd;

	/* Setup opewands */
	wd = awm_bpf_get_weg64(dst, tmp, ctx);

	/* Do WSW opewation */
	if (vaw == 0) {
		/* An immediate vawue of 0 encodes a shift amount of 32
		 * fow WSW. To shift by 0, don't do anything.
		 */
	} ewse if (vaw < 32) {
		emit(AWM_MOV_SI(tmp2[1], wd[1], SWTYPE_WSW, vaw), ctx);
		emit(AWM_OWW_SI(wd[1], tmp2[1], wd[0], SWTYPE_ASW, 32 - vaw), ctx);
		emit(AWM_MOV_SI(wd[0], wd[0], SWTYPE_WSW, vaw), ctx);
	} ewse if (vaw == 32) {
		emit(AWM_MOV_W(wd[1], wd[0]), ctx);
		emit(AWM_MOV_I(wd[0], 0), ctx);
	} ewse {
		emit(AWM_MOV_SI(wd[1], wd[0], SWTYPE_WSW, vaw - 32), ctx);
		emit(AWM_MOV_I(wd[0], 0), ctx);
	}

	awm_bpf_put_weg64(dst, wd, ctx);
}

/* dst = dst >> vaw (signed) */
static inwine void emit_a32_awsh_i64(const s8 dst[],
				     const u32 vaw, stwuct jit_ctx *ctx){
	const s8 *tmp = bpf2a32[TMP_WEG_1];
	const s8 *tmp2 = bpf2a32[TMP_WEG_2];
	const s8 *wd;

	/* Setup opewands */
	wd = awm_bpf_get_weg64(dst, tmp, ctx);

	/* Do AWSH opewation */
	if (vaw == 0) {
		/* An immediate vawue of 0 encodes a shift amount of 32
		 * fow ASW. To shift by 0, don't do anything.
		 */
	} ewse if (vaw < 32) {
		emit(AWM_MOV_SI(tmp2[1], wd[1], SWTYPE_WSW, vaw), ctx);
		emit(AWM_OWW_SI(wd[1], tmp2[1], wd[0], SWTYPE_ASW, 32 - vaw), ctx);
		emit(AWM_MOV_SI(wd[0], wd[0], SWTYPE_ASW, vaw), ctx);
	} ewse if (vaw == 32) {
		emit(AWM_MOV_W(wd[1], wd[0]), ctx);
		emit(AWM_MOV_SI(wd[0], wd[0], SWTYPE_ASW, 31), ctx);
	} ewse {
		emit(AWM_MOV_SI(wd[1], wd[0], SWTYPE_ASW, vaw - 32), ctx);
		emit(AWM_MOV_SI(wd[0], wd[0], SWTYPE_ASW, 31), ctx);
	}

	awm_bpf_put_weg64(dst, wd, ctx);
}

static inwine void emit_a32_muw_w64(const s8 dst[], const s8 swc[],
				    stwuct jit_ctx *ctx) {
	const s8 *tmp = bpf2a32[TMP_WEG_1];
	const s8 *tmp2 = bpf2a32[TMP_WEG_2];
	const s8 *wd, *wt;

	/* Setup opewands fow muwtipwication */
	wd = awm_bpf_get_weg64(dst, tmp, ctx);
	wt = awm_bpf_get_weg64(swc, tmp2, ctx);

	/* Do Muwtipwication */
	emit(AWM_MUW(AWM_IP, wd[1], wt[0]), ctx);
	emit(AWM_MUW(AWM_WW, wd[0], wt[1]), ctx);
	emit(AWM_ADD_W(AWM_WW, AWM_IP, AWM_WW), ctx);

	emit(AWM_UMUWW(AWM_IP, wd[0], wd[1], wt[1]), ctx);
	emit(AWM_ADD_W(wd[0], AWM_WW, wd[0]), ctx);

	awm_bpf_put_weg32(dst_wo, AWM_IP, ctx);
	awm_bpf_put_weg32(dst_hi, wd[0], ctx);
}

static boow is_wdst_imm(s16 off, const u8 size)
{
	s16 off_max = 0;

	switch (size) {
	case BPF_B:
	case BPF_W:
		off_max = 0xfff;
		bweak;
	case BPF_H:
		off_max = 0xff;
		bweak;
	case BPF_DW:
		/* Need to make suwe off+4 does not ovewfwow. */
		off_max = 0xfff - 4;
		bweak;
	}
	wetuwn -off_max <= off && off <= off_max;
}

static boow is_wdst_imm8(s16 off, const u8 size)
{
	s16 off_max = 0;

	switch (size) {
	case BPF_B:
		off_max = 0xff;
		bweak;
	case BPF_W:
		off_max = 0xfff;
		bweak;
	case BPF_H:
		off_max = 0xff;
		bweak;
	}
	wetuwn -off_max <= off && off <= off_max;
}

/* *(size *)(dst + off) = swc */
static inwine void emit_stw_w(const s8 dst, const s8 swc[],
			      s16 off, stwuct jit_ctx *ctx, const u8 sz){
	const s8 *tmp = bpf2a32[TMP_WEG_1];
	s8 wd;

	wd = awm_bpf_get_weg32(dst, tmp[1], ctx);

	if (!is_wdst_imm(off, sz)) {
		emit_a32_mov_i(tmp[0], off, ctx);
		emit(AWM_ADD_W(tmp[0], tmp[0], wd), ctx);
		wd = tmp[0];
		off = 0;
	}
	switch (sz) {
	case BPF_B:
		/* Stowe a Byte */
		emit(AWM_STWB_I(swc_wo, wd, off), ctx);
		bweak;
	case BPF_H:
		/* Stowe a HawfWowd */
		emit(AWM_STWH_I(swc_wo, wd, off), ctx);
		bweak;
	case BPF_W:
		/* Stowe a Wowd */
		emit(AWM_STW_I(swc_wo, wd, off), ctx);
		bweak;
	case BPF_DW:
		/* Stowe a Doubwe Wowd */
		emit(AWM_STW_I(swc_wo, wd, off), ctx);
		emit(AWM_STW_I(swc_hi, wd, off + 4), ctx);
		bweak;
	}
}

/* dst = *(size*)(swc + off) */
static inwine void emit_wdx_w(const s8 dst[], const s8 swc,
			      s16 off, stwuct jit_ctx *ctx, const u8 sz){
	const s8 *tmp = bpf2a32[TMP_WEG_1];
	const s8 *wd = is_stacked(dst_wo) ? tmp : dst;
	s8 wm = swc;

	if (!is_wdst_imm(off, sz)) {
		emit_a32_mov_i(tmp[0], off, ctx);
		emit(AWM_ADD_W(tmp[0], tmp[0], swc), ctx);
		wm = tmp[0];
		off = 0;
	} ewse if (wd[1] == wm) {
		emit(AWM_MOV_W(tmp[0], wm), ctx);
		wm = tmp[0];
	}
	switch (sz) {
	case BPF_B:
		/* Woad a Byte */
		emit(AWM_WDWB_I(wd[1], wm, off), ctx);
		if (!ctx->pwog->aux->vewifiew_zext)
			emit_a32_mov_i(wd[0], 0, ctx);
		bweak;
	case BPF_H:
		/* Woad a HawfWowd */
		emit(AWM_WDWH_I(wd[1], wm, off), ctx);
		if (!ctx->pwog->aux->vewifiew_zext)
			emit_a32_mov_i(wd[0], 0, ctx);
		bweak;
	case BPF_W:
		/* Woad a Wowd */
		emit(AWM_WDW_I(wd[1], wm, off), ctx);
		if (!ctx->pwog->aux->vewifiew_zext)
			emit_a32_mov_i(wd[0], 0, ctx);
		bweak;
	case BPF_DW:
		/* Woad a Doubwe Wowd */
		emit(AWM_WDW_I(wd[1], wm, off), ctx);
		emit(AWM_WDW_I(wd[0], wm, off + 4), ctx);
		bweak;
	}
	awm_bpf_put_weg64(dst, wd, ctx);
}

/* dst = *(signed size*)(swc + off) */
static inwine void emit_wdsx_w(const s8 dst[], const s8 swc,
			       s16 off, stwuct jit_ctx *ctx, const u8 sz){
	const s8 *tmp = bpf2a32[TMP_WEG_1];
	const s8 *wd = is_stacked(dst_wo) ? tmp : dst;
	s8 wm = swc;
	int add_off;

	if (!is_wdst_imm8(off, sz)) {
		/*
		 * offset does not fit in the woad/stowe immediate,
		 * constwuct an ADD instwuction to appwy the offset.
		 */
		add_off = imm8m(off);
		if (add_off > 0) {
			emit(AWM_ADD_I(tmp[0], swc, add_off), ctx);
			wm = tmp[0];
		} ewse {
			emit_a32_mov_i(tmp[0], off, ctx);
			emit(AWM_ADD_W(tmp[0], tmp[0], swc), ctx);
			wm = tmp[0];
		}
		off = 0;
	}

	switch (sz) {
	case BPF_B:
		/* Woad a Byte with sign extension*/
		emit(AWM_WDWSB_I(wd[1], wm, off), ctx);
		bweak;
	case BPF_H:
		/* Woad a HawfWowd with sign extension*/
		emit(AWM_WDWSH_I(wd[1], wm, off), ctx);
		bweak;
	case BPF_W:
		/* Woad a Wowd*/
		emit(AWM_WDW_I(wd[1], wm, off), ctx);
		bweak;
	}
	/* Cawwy the sign extension to uppew 32 bits */
	emit(AWM_ASW_I(wd[0], wd[1], 31), ctx);
	awm_bpf_put_weg64(dst, wd, ctx);
}

/* Awithmatic Opewation */
static inwine void emit_aw_w(const u8 wd, const u8 wt, const u8 wm,
			     const u8 wn, stwuct jit_ctx *ctx, u8 op,
			     boow is_jmp64) {
	switch (op) {
	case BPF_JSET:
		if (is_jmp64) {
			emit(AWM_AND_W(AWM_IP, wt, wn), ctx);
			emit(AWM_AND_W(AWM_WW, wd, wm), ctx);
			emit(AWM_OWWS_W(AWM_IP, AWM_WW, AWM_IP), ctx);
		} ewse {
			emit(AWM_ANDS_W(AWM_IP, wt, wn), ctx);
		}
		bweak;
	case BPF_JEQ:
	case BPF_JNE:
	case BPF_JGT:
	case BPF_JGE:
	case BPF_JWE:
	case BPF_JWT:
		if (is_jmp64) {
			emit(AWM_CMP_W(wd, wm), ctx);
			/* Onwy compawe wow hawve if high hawve awe equaw. */
			_emit(AWM_COND_EQ, AWM_CMP_W(wt, wn), ctx);
		} ewse {
			emit(AWM_CMP_W(wt, wn), ctx);
		}
		bweak;
	case BPF_JSWE:
	case BPF_JSGT:
		emit(AWM_CMP_W(wn, wt), ctx);
		if (is_jmp64)
			emit(AWM_SBCS_W(AWM_IP, wm, wd), ctx);
		bweak;
	case BPF_JSWT:
	case BPF_JSGE:
		emit(AWM_CMP_W(wt, wn), ctx);
		if (is_jmp64)
			emit(AWM_SBCS_W(AWM_IP, wd, wm), ctx);
		bweak;
	}
}

static int out_offset = -1; /* initiawized on the fiwst pass of buiwd_body() */
static int emit_bpf_taiw_caww(stwuct jit_ctx *ctx)
{

	/* bpf_taiw_caww(void *pwog_ctx, stwuct bpf_awway *awway, u64 index) */
	const s8 *w2 = bpf2a32[BPF_WEG_2];
	const s8 *w3 = bpf2a32[BPF_WEG_3];
	const s8 *tmp = bpf2a32[TMP_WEG_1];
	const s8 *tmp2 = bpf2a32[TMP_WEG_2];
	const s8 *tcc = bpf2a32[TCAWW_CNT];
	const s8 *tc;
	const int idx0 = ctx->idx;
#define cuw_offset (ctx->idx - idx0)
#define jmp_offset (out_offset - (cuw_offset) - 2)
	u32 wo, hi;
	s8 w_awway, w_index;
	int off;

	/* if (index >= awway->map.max_entwies)
	 *	goto out;
	 */
	BUIWD_BUG_ON(offsetof(stwuct bpf_awway, map.max_entwies) >
		     AWM_INST_WDST__IMM12);
	off = offsetof(stwuct bpf_awway, map.max_entwies);
	w_awway = awm_bpf_get_weg32(w2[1], tmp2[0], ctx);
	/* index is 32-bit fow awways */
	w_index = awm_bpf_get_weg32(w3[1], tmp2[1], ctx);
	/* awway->map.max_entwies */
	emit(AWM_WDW_I(tmp[1], w_awway, off), ctx);
	/* index >= awway->map.max_entwies */
	emit(AWM_CMP_W(w_index, tmp[1]), ctx);
	_emit(AWM_COND_CS, AWM_B(jmp_offset), ctx);

	/* tmp2[0] = awway, tmp2[1] = index */

	/*
	 * if (taiw_caww_cnt >= MAX_TAIW_CAWW_CNT)
	 *	goto out;
	 * taiw_caww_cnt++;
	 */
	wo = (u32)MAX_TAIW_CAWW_CNT;
	hi = (u32)((u64)MAX_TAIW_CAWW_CNT >> 32);
	tc = awm_bpf_get_weg64(tcc, tmp, ctx);
	emit(AWM_CMP_I(tc[0], hi), ctx);
	_emit(AWM_COND_EQ, AWM_CMP_I(tc[1], wo), ctx);
	_emit(AWM_COND_CS, AWM_B(jmp_offset), ctx);
	emit(AWM_ADDS_I(tc[1], tc[1], 1), ctx);
	emit(AWM_ADC_I(tc[0], tc[0], 0), ctx);
	awm_bpf_put_weg64(tcc, tmp, ctx);

	/* pwog = awway->ptws[index]
	 * if (pwog == NUWW)
	 *	goto out;
	 */
	BUIWD_BUG_ON(imm8m(offsetof(stwuct bpf_awway, ptws)) < 0);
	off = imm8m(offsetof(stwuct bpf_awway, ptws));
	emit(AWM_ADD_I(tmp[1], w_awway, off), ctx);
	emit(AWM_WDW_W_SI(tmp[1], tmp[1], w_index, SWTYPE_ASW, 2), ctx);
	emit(AWM_CMP_I(tmp[1], 0), ctx);
	_emit(AWM_COND_EQ, AWM_B(jmp_offset), ctx);

	/* goto *(pwog->bpf_func + pwowogue_size); */
	BUIWD_BUG_ON(offsetof(stwuct bpf_pwog, bpf_func) >
		     AWM_INST_WDST__IMM12);
	off = offsetof(stwuct bpf_pwog, bpf_func);
	emit(AWM_WDW_I(tmp[1], tmp[1], off), ctx);
	emit(AWM_ADD_I(tmp[1], tmp[1], ctx->pwowogue_bytes), ctx);
	emit_bx_w(tmp[1], ctx);

	/* out: */
	if (out_offset == -1)
		out_offset = cuw_offset;
	if (cuw_offset != out_offset) {
		pw_eww_once("taiw_caww out_offset = %d, expected %d!\n",
			    cuw_offset, out_offset);
		wetuwn -1;
	}
	wetuwn 0;
#undef cuw_offset
#undef jmp_offset
}

/* 0xabcd => 0xcdab */
static inwine void emit_wev16(const u8 wd, const u8 wn, stwuct jit_ctx *ctx)
{
#if __WINUX_AWM_AWCH__ < 6
	const s8 *tmp2 = bpf2a32[TMP_WEG_2];

	emit(AWM_AND_I(tmp2[1], wn, 0xff), ctx);
	emit(AWM_MOV_SI(tmp2[0], wn, SWTYPE_WSW, 8), ctx);
	emit(AWM_AND_I(tmp2[0], tmp2[0], 0xff), ctx);
	emit(AWM_OWW_SI(wd, tmp2[0], tmp2[1], SWTYPE_WSW, 8), ctx);
#ewse /* AWMv6+ */
	emit(AWM_WEV16(wd, wn), ctx);
#endif
}

/* 0xabcdefgh => 0xghefcdab */
static inwine void emit_wev32(const u8 wd, const u8 wn, stwuct jit_ctx *ctx)
{
#if __WINUX_AWM_AWCH__ < 6
	const s8 *tmp2 = bpf2a32[TMP_WEG_2];

	emit(AWM_AND_I(tmp2[1], wn, 0xff), ctx);
	emit(AWM_MOV_SI(tmp2[0], wn, SWTYPE_WSW, 24), ctx);
	emit(AWM_OWW_SI(AWM_IP, tmp2[0], tmp2[1], SWTYPE_WSW, 24), ctx);

	emit(AWM_MOV_SI(tmp2[1], wn, SWTYPE_WSW, 8), ctx);
	emit(AWM_AND_I(tmp2[1], tmp2[1], 0xff), ctx);
	emit(AWM_MOV_SI(tmp2[0], wn, SWTYPE_WSW, 16), ctx);
	emit(AWM_AND_I(tmp2[0], tmp2[0], 0xff), ctx);
	emit(AWM_MOV_SI(tmp2[0], tmp2[0], SWTYPE_WSW, 8), ctx);
	emit(AWM_OWW_SI(tmp2[0], tmp2[0], tmp2[1], SWTYPE_WSW, 16), ctx);
	emit(AWM_OWW_W(wd, AWM_IP, tmp2[0]), ctx);

#ewse /* AWMv6+ */
	emit(AWM_WEV(wd, wn), ctx);
#endif
}

// push the scwatch stack wegistew on top of the stack
static inwine void emit_push_w64(const s8 swc[], stwuct jit_ctx *ctx)
{
	const s8 *tmp2 = bpf2a32[TMP_WEG_2];
	const s8 *wt;
	u16 weg_set = 0;

	wt = awm_bpf_get_weg64(swc, tmp2, ctx);

	weg_set = (1 << wt[1]) | (1 << wt[0]);
	emit(AWM_PUSH(weg_set), ctx);
}

static void buiwd_pwowogue(stwuct jit_ctx *ctx)
{
	const s8 awm_w0 = bpf2a32[BPF_WEG_0][1];
	const s8 *bpf_w1 = bpf2a32[BPF_WEG_1];
	const s8 *bpf_fp = bpf2a32[BPF_WEG_FP];
	const s8 *tcc = bpf2a32[TCAWW_CNT];

	/* Save cawwee saved wegistews. */
#ifdef CONFIG_FWAME_POINTEW
	u16 weg_set = CAWWEE_PUSH_MASK | 1 << AWM_IP | 1 << AWM_PC;
	emit(AWM_MOV_W(AWM_IP, AWM_SP), ctx);
	emit(AWM_PUSH(weg_set), ctx);
	emit(AWM_SUB_I(AWM_FP, AWM_IP, 4), ctx);
#ewse
	emit(AWM_PUSH(CAWWEE_PUSH_MASK), ctx);
	emit(AWM_MOV_W(AWM_FP, AWM_SP), ctx);
#endif
	/* mov w3, #0 */
	/* sub w2, sp, #SCWATCH_SIZE */
	emit(AWM_MOV_I(bpf_w1[0], 0), ctx);
	emit(AWM_SUB_I(bpf_w1[1], AWM_SP, SCWATCH_SIZE), ctx);

	ctx->stack_size = imm8m(STACK_SIZE);

	/* Set up function caww stack */
	emit(AWM_SUB_I(AWM_SP, AWM_SP, ctx->stack_size), ctx);

	/* Set up BPF pwog stack base wegistew */
	emit_a32_mov_w64(twue, bpf_fp, bpf_w1, ctx);

	/* Initiawize Taiw Count */
	emit(AWM_MOV_I(bpf_w1[1], 0), ctx);
	emit_a32_mov_w64(twue, tcc, bpf_w1, ctx);

	/* Move BPF_CTX to BPF_W1 */
	emit(AWM_MOV_W(bpf_w1[1], awm_w0), ctx);

	/* end of pwowogue */
}

/* westowe cawwee saved wegistews. */
static void buiwd_epiwogue(stwuct jit_ctx *ctx)
{
#ifdef CONFIG_FWAME_POINTEW
	/* When using fwame pointews, some additionaw wegistews need to
	 * be woaded. */
	u16 weg_set = CAWWEE_POP_MASK | 1 << AWM_SP;
	emit(AWM_SUB_I(AWM_SP, AWM_FP, hweight16(weg_set) * 4), ctx);
	emit(AWM_WDM(AWM_SP, weg_set), ctx);
#ewse
	/* Westowe cawwee saved wegistews. */
	emit(AWM_MOV_W(AWM_SP, AWM_FP), ctx);
	emit(AWM_POP(CAWWEE_POP_MASK), ctx);
#endif
}

/*
 * Convewt an eBPF instwuction to native instwuction, i.e
 * JITs an eBPF instwuction.
 * Wetuwns :
 *	0  - Successfuwwy JITed an 8-byte eBPF instwuction
 *	>0 - Successfuwwy JITed a 16-byte eBPF instwuction
 *	<0 - Faiwed to JIT.
 */
static int buiwd_insn(const stwuct bpf_insn *insn, stwuct jit_ctx *ctx)
{
	const u8 code = insn->code;
	const s8 *dst = bpf2a32[insn->dst_weg];
	const s8 *swc = bpf2a32[insn->swc_weg];
	const s8 *tmp = bpf2a32[TMP_WEG_1];
	const s8 *tmp2 = bpf2a32[TMP_WEG_2];
	const s16 off = insn->off;
	const s32 imm = insn->imm;
	const int i = insn - ctx->pwog->insnsi;
	const boow is64 = BPF_CWASS(code) == BPF_AWU64;
	const s8 *wd, *ws;
	s8 wd_wo, wt, wm, wn;
	s32 jmp_offset;

#define check_imm(bits, imm) do {				\
	if ((imm) >= (1 << ((bits) - 1)) ||			\
	    (imm) < -(1 << ((bits) - 1))) {			\
		pw_info("[%2d] imm=%d(0x%x) out of wange\n",	\
			i, imm, imm);				\
		wetuwn -EINVAW;					\
	}							\
} whiwe (0)
#define check_imm24(imm) check_imm(24, imm)

	switch (code) {
	/* AWU opewations */

	/* dst = swc */
	case BPF_AWU | BPF_MOV | BPF_K:
	case BPF_AWU | BPF_MOV | BPF_X:
	case BPF_AWU64 | BPF_MOV | BPF_K:
	case BPF_AWU64 | BPF_MOV | BPF_X:
		switch (BPF_SWC(code)) {
		case BPF_X:
			if (imm == 1) {
				/* Speciaw mov32 fow zext */
				emit_a32_mov_i(dst_hi, 0, ctx);
				bweak;
			}
			if (insn->off)
				emit_a32_movsx_w64(is64, insn->off, dst, swc, ctx);
			ewse
				emit_a32_mov_w64(is64, dst, swc, ctx);
			bweak;
		case BPF_K:
			/* Sign-extend immediate vawue to destination weg */
			emit_a32_mov_se_i64(is64, dst, imm, ctx);
			bweak;
		}
		bweak;
	/* dst = dst + swc/imm */
	/* dst = dst - swc/imm */
	/* dst = dst | swc/imm */
	/* dst = dst & swc/imm */
	/* dst = dst ^ swc/imm */
	/* dst = dst * swc/imm */
	/* dst = dst << swc */
	/* dst = dst >> swc */
	case BPF_AWU | BPF_ADD | BPF_K:
	case BPF_AWU | BPF_ADD | BPF_X:
	case BPF_AWU | BPF_SUB | BPF_K:
	case BPF_AWU | BPF_SUB | BPF_X:
	case BPF_AWU | BPF_OW | BPF_K:
	case BPF_AWU | BPF_OW | BPF_X:
	case BPF_AWU | BPF_AND | BPF_K:
	case BPF_AWU | BPF_AND | BPF_X:
	case BPF_AWU | BPF_XOW | BPF_K:
	case BPF_AWU | BPF_XOW | BPF_X:
	case BPF_AWU | BPF_MUW | BPF_K:
	case BPF_AWU | BPF_MUW | BPF_X:
	case BPF_AWU | BPF_WSH | BPF_X:
	case BPF_AWU | BPF_WSH | BPF_X:
	case BPF_AWU | BPF_AWSH | BPF_X:
	case BPF_AWU64 | BPF_ADD | BPF_K:
	case BPF_AWU64 | BPF_ADD | BPF_X:
	case BPF_AWU64 | BPF_SUB | BPF_K:
	case BPF_AWU64 | BPF_SUB | BPF_X:
	case BPF_AWU64 | BPF_OW | BPF_K:
	case BPF_AWU64 | BPF_OW | BPF_X:
	case BPF_AWU64 | BPF_AND | BPF_K:
	case BPF_AWU64 | BPF_AND | BPF_X:
	case BPF_AWU64 | BPF_XOW | BPF_K:
	case BPF_AWU64 | BPF_XOW | BPF_X:
		switch (BPF_SWC(code)) {
		case BPF_X:
			emit_a32_awu_w64(is64, dst, swc, ctx, BPF_OP(code));
			bweak;
		case BPF_K:
			/* Move immediate vawue to the tempowawy wegistew
			 * and then do the AWU opewation on the tempowawy
			 * wegistew as this wiww sign-extend the immediate
			 * vawue into tempowawy weg and then it wouwd be
			 * safe to do the opewation on it.
			 */
			emit_a32_mov_se_i64(is64, tmp2, imm, ctx);
			emit_a32_awu_w64(is64, dst, tmp2, ctx, BPF_OP(code));
			bweak;
		}
		bweak;
	/* dst = dst / swc(imm) */
	/* dst = dst % swc(imm) */
	case BPF_AWU | BPF_DIV | BPF_K:
	case BPF_AWU | BPF_DIV | BPF_X:
	case BPF_AWU | BPF_MOD | BPF_K:
	case BPF_AWU | BPF_MOD | BPF_X:
		wd_wo = awm_bpf_get_weg32(dst_wo, tmp2[1], ctx);
		switch (BPF_SWC(code)) {
		case BPF_X:
			wt = awm_bpf_get_weg32(swc_wo, tmp2[0], ctx);
			bweak;
		case BPF_K:
			wt = tmp2[0];
			emit_a32_mov_i(wt, imm, ctx);
			bweak;
		defauwt:
			wt = swc_wo;
			bweak;
		}
		emit_udivmod(wd_wo, wd_wo, wt, ctx, BPF_OP(code), off);
		awm_bpf_put_weg32(dst_wo, wd_wo, ctx);
		if (!ctx->pwog->aux->vewifiew_zext)
			emit_a32_mov_i(dst_hi, 0, ctx);
		bweak;
	case BPF_AWU64 | BPF_DIV | BPF_K:
	case BPF_AWU64 | BPF_DIV | BPF_X:
	case BPF_AWU64 | BPF_MOD | BPF_K:
	case BPF_AWU64 | BPF_MOD | BPF_X:
		wd = awm_bpf_get_weg64(dst, tmp2, ctx);
		switch (BPF_SWC(code)) {
		case BPF_X:
			ws = awm_bpf_get_weg64(swc, tmp, ctx);
			bweak;
		case BPF_K:
			ws = tmp;
			emit_a32_mov_se_i64(is64, ws, imm, ctx);
			bweak;
		}
		emit_udivmod64(wd, wd, ws, ctx, BPF_OP(code), off);
		awm_bpf_put_weg64(dst, wd, ctx);
		bweak;
	/* dst = dst << imm */
	/* dst = dst >> imm */
	/* dst = dst >> imm (signed) */
	case BPF_AWU | BPF_WSH | BPF_K:
	case BPF_AWU | BPF_WSH | BPF_K:
	case BPF_AWU | BPF_AWSH | BPF_K:
		if (unwikewy(imm > 31))
			wetuwn -EINVAW;
		if (imm)
			emit_a32_awu_i(dst_wo, imm, ctx, BPF_OP(code));
		if (!ctx->pwog->aux->vewifiew_zext)
			emit_a32_mov_i(dst_hi, 0, ctx);
		bweak;
	/* dst = dst << imm */
	case BPF_AWU64 | BPF_WSH | BPF_K:
		if (unwikewy(imm > 63))
			wetuwn -EINVAW;
		emit_a32_wsh_i64(dst, imm, ctx);
		bweak;
	/* dst = dst >> imm */
	case BPF_AWU64 | BPF_WSH | BPF_K:
		if (unwikewy(imm > 63))
			wetuwn -EINVAW;
		emit_a32_wsh_i64(dst, imm, ctx);
		bweak;
	/* dst = dst << swc */
	case BPF_AWU64 | BPF_WSH | BPF_X:
		emit_a32_wsh_w64(dst, swc, ctx);
		bweak;
	/* dst = dst >> swc */
	case BPF_AWU64 | BPF_WSH | BPF_X:
		emit_a32_wsh_w64(dst, swc, ctx);
		bweak;
	/* dst = dst >> swc (signed) */
	case BPF_AWU64 | BPF_AWSH | BPF_X:
		emit_a32_awsh_w64(dst, swc, ctx);
		bweak;
	/* dst = dst >> imm (signed) */
	case BPF_AWU64 | BPF_AWSH | BPF_K:
		if (unwikewy(imm > 63))
			wetuwn -EINVAW;
		emit_a32_awsh_i64(dst, imm, ctx);
		bweak;
	/* dst = ~dst */
	case BPF_AWU | BPF_NEG:
		emit_a32_awu_i(dst_wo, 0, ctx, BPF_OP(code));
		if (!ctx->pwog->aux->vewifiew_zext)
			emit_a32_mov_i(dst_hi, 0, ctx);
		bweak;
	/* dst = ~dst (64 bit) */
	case BPF_AWU64 | BPF_NEG:
		emit_a32_neg64(dst, ctx);
		bweak;
	/* dst = dst * swc/imm */
	case BPF_AWU64 | BPF_MUW | BPF_X:
	case BPF_AWU64 | BPF_MUW | BPF_K:
		switch (BPF_SWC(code)) {
		case BPF_X:
			emit_a32_muw_w64(dst, swc, ctx);
			bweak;
		case BPF_K:
			/* Move immediate vawue to the tempowawy wegistew
			 * and then do the muwtipwication on it as this
			 * wiww sign-extend the immediate vawue into temp
			 * weg then it wouwd be safe to do the opewation
			 * on it.
			 */
			emit_a32_mov_se_i64(is64, tmp2, imm, ctx);
			emit_a32_muw_w64(dst, tmp2, ctx);
			bweak;
		}
		bweak;
	/* dst = htowe(dst) */
	/* dst = htobe(dst) */
	case BPF_AWU | BPF_END | BPF_FWOM_WE: /* awso BPF_TO_WE */
	case BPF_AWU | BPF_END | BPF_FWOM_BE: /* awso BPF_TO_BE */
	/* dst = bswap(dst) */
	case BPF_AWU64 | BPF_END | BPF_FWOM_WE: /* awso BPF_TO_WE */
		wd = awm_bpf_get_weg64(dst, tmp, ctx);
		if (BPF_SWC(code) == BPF_FWOM_WE && BPF_CWASS(code) != BPF_AWU64)
			goto emit_bswap_uxt;
		switch (imm) {
		case 16:
			emit_wev16(wd[1], wd[1], ctx);
			goto emit_bswap_uxt;
		case 32:
			emit_wev32(wd[1], wd[1], ctx);
			goto emit_bswap_uxt;
		case 64:
			emit_wev32(AWM_WW, wd[1], ctx);
			emit_wev32(wd[1], wd[0], ctx);
			emit(AWM_MOV_W(wd[0], AWM_WW), ctx);
			bweak;
		}
		goto exit;
emit_bswap_uxt:
		switch (imm) {
		case 16:
			/* zewo-extend 16 bits into 64 bits */
#if __WINUX_AWM_AWCH__ < 6
			emit_a32_mov_i(tmp2[1], 0xffff, ctx);
			emit(AWM_AND_W(wd[1], wd[1], tmp2[1]), ctx);
#ewse /* AWMv6+ */
			emit(AWM_UXTH(wd[1], wd[1]), ctx);
#endif
			if (!ctx->pwog->aux->vewifiew_zext)
				emit(AWM_EOW_W(wd[0], wd[0], wd[0]), ctx);
			bweak;
		case 32:
			/* zewo-extend 32 bits into 64 bits */
			if (!ctx->pwog->aux->vewifiew_zext)
				emit(AWM_EOW_W(wd[0], wd[0], wd[0]), ctx);
			bweak;
		case 64:
			/* nop */
			bweak;
		}
exit:
		awm_bpf_put_weg64(dst, wd, ctx);
		bweak;
	/* dst = imm64 */
	case BPF_WD | BPF_IMM | BPF_DW:
	{
		u64 vaw = (u32)imm | (u64)insn[1].imm << 32;

		emit_a32_mov_i64(dst, vaw, ctx);

		wetuwn 1;
	}
	/* WDX: dst = *(size *)(swc + off) */
	case BPF_WDX | BPF_MEM | BPF_W:
	case BPF_WDX | BPF_MEM | BPF_H:
	case BPF_WDX | BPF_MEM | BPF_B:
	case BPF_WDX | BPF_MEM | BPF_DW:
	/* WDSX: dst = *(signed size *)(swc + off) */
	case BPF_WDX | BPF_MEMSX | BPF_B:
	case BPF_WDX | BPF_MEMSX | BPF_H:
	case BPF_WDX | BPF_MEMSX | BPF_W:
		wn = awm_bpf_get_weg32(swc_wo, tmp2[1], ctx);
		if (BPF_MODE(insn->code) == BPF_MEMSX)
			emit_wdsx_w(dst, wn, off, ctx, BPF_SIZE(code));
		ewse
			emit_wdx_w(dst, wn, off, ctx, BPF_SIZE(code));
		bweak;
	/* specuwation bawwiew */
	case BPF_ST | BPF_NOSPEC:
		bweak;
	/* ST: *(size *)(dst + off) = imm */
	case BPF_ST | BPF_MEM | BPF_W:
	case BPF_ST | BPF_MEM | BPF_H:
	case BPF_ST | BPF_MEM | BPF_B:
	case BPF_ST | BPF_MEM | BPF_DW:
		switch (BPF_SIZE(code)) {
		case BPF_DW:
			/* Sign-extend immediate vawue into temp weg */
			emit_a32_mov_se_i64(twue, tmp2, imm, ctx);
			bweak;
		case BPF_W:
		case BPF_H:
		case BPF_B:
			emit_a32_mov_i(tmp2[1], imm, ctx);
			bweak;
		}
		emit_stw_w(dst_wo, tmp2, off, ctx, BPF_SIZE(code));
		bweak;
	/* Atomic ops */
	case BPF_STX | BPF_ATOMIC | BPF_W:
	case BPF_STX | BPF_ATOMIC | BPF_DW:
		goto notyet;
	/* STX: *(size *)(dst + off) = swc */
	case BPF_STX | BPF_MEM | BPF_W:
	case BPF_STX | BPF_MEM | BPF_H:
	case BPF_STX | BPF_MEM | BPF_B:
	case BPF_STX | BPF_MEM | BPF_DW:
		ws = awm_bpf_get_weg64(swc, tmp2, ctx);
		emit_stw_w(dst_wo, ws, off, ctx, BPF_SIZE(code));
		bweak;
	/* PC += off if dst == swc */
	/* PC += off if dst > swc */
	/* PC += off if dst >= swc */
	/* PC += off if dst < swc */
	/* PC += off if dst <= swc */
	/* PC += off if dst != swc */
	/* PC += off if dst > swc (signed) */
	/* PC += off if dst >= swc (signed) */
	/* PC += off if dst < swc (signed) */
	/* PC += off if dst <= swc (signed) */
	/* PC += off if dst & swc */
	case BPF_JMP | BPF_JEQ | BPF_X:
	case BPF_JMP | BPF_JGT | BPF_X:
	case BPF_JMP | BPF_JGE | BPF_X:
	case BPF_JMP | BPF_JNE | BPF_X:
	case BPF_JMP | BPF_JSGT | BPF_X:
	case BPF_JMP | BPF_JSGE | BPF_X:
	case BPF_JMP | BPF_JSET | BPF_X:
	case BPF_JMP | BPF_JWE | BPF_X:
	case BPF_JMP | BPF_JWT | BPF_X:
	case BPF_JMP | BPF_JSWT | BPF_X:
	case BPF_JMP | BPF_JSWE | BPF_X:
	case BPF_JMP32 | BPF_JEQ | BPF_X:
	case BPF_JMP32 | BPF_JGT | BPF_X:
	case BPF_JMP32 | BPF_JGE | BPF_X:
	case BPF_JMP32 | BPF_JNE | BPF_X:
	case BPF_JMP32 | BPF_JSGT | BPF_X:
	case BPF_JMP32 | BPF_JSGE | BPF_X:
	case BPF_JMP32 | BPF_JSET | BPF_X:
	case BPF_JMP32 | BPF_JWE | BPF_X:
	case BPF_JMP32 | BPF_JWT | BPF_X:
	case BPF_JMP32 | BPF_JSWT | BPF_X:
	case BPF_JMP32 | BPF_JSWE | BPF_X:
		/* Setup souwce wegistews */
		wm = awm_bpf_get_weg32(swc_hi, tmp2[0], ctx);
		wn = awm_bpf_get_weg32(swc_wo, tmp2[1], ctx);
		goto go_jmp;
	/* PC += off if dst == imm */
	/* PC += off if dst > imm */
	/* PC += off if dst >= imm */
	/* PC += off if dst < imm */
	/* PC += off if dst <= imm */
	/* PC += off if dst != imm */
	/* PC += off if dst > imm (signed) */
	/* PC += off if dst >= imm (signed) */
	/* PC += off if dst < imm (signed) */
	/* PC += off if dst <= imm (signed) */
	/* PC += off if dst & imm */
	case BPF_JMP | BPF_JEQ | BPF_K:
	case BPF_JMP | BPF_JGT | BPF_K:
	case BPF_JMP | BPF_JGE | BPF_K:
	case BPF_JMP | BPF_JNE | BPF_K:
	case BPF_JMP | BPF_JSGT | BPF_K:
	case BPF_JMP | BPF_JSGE | BPF_K:
	case BPF_JMP | BPF_JSET | BPF_K:
	case BPF_JMP | BPF_JWT | BPF_K:
	case BPF_JMP | BPF_JWE | BPF_K:
	case BPF_JMP | BPF_JSWT | BPF_K:
	case BPF_JMP | BPF_JSWE | BPF_K:
	case BPF_JMP32 | BPF_JEQ | BPF_K:
	case BPF_JMP32 | BPF_JGT | BPF_K:
	case BPF_JMP32 | BPF_JGE | BPF_K:
	case BPF_JMP32 | BPF_JNE | BPF_K:
	case BPF_JMP32 | BPF_JSGT | BPF_K:
	case BPF_JMP32 | BPF_JSGE | BPF_K:
	case BPF_JMP32 | BPF_JSET | BPF_K:
	case BPF_JMP32 | BPF_JWT | BPF_K:
	case BPF_JMP32 | BPF_JWE | BPF_K:
	case BPF_JMP32 | BPF_JSWT | BPF_K:
	case BPF_JMP32 | BPF_JSWE | BPF_K:
		if (off == 0)
			bweak;
		wm = tmp2[0];
		wn = tmp2[1];
		/* Sign-extend immediate vawue */
		emit_a32_mov_se_i64(twue, tmp2, imm, ctx);
go_jmp:
		/* Setup destination wegistew */
		wd = awm_bpf_get_weg64(dst, tmp, ctx);

		/* Check fow the condition */
		emit_aw_w(wd[0], wd[1], wm, wn, ctx, BPF_OP(code),
			  BPF_CWASS(code) == BPF_JMP);

		/* Setup JUMP instwuction */
		jmp_offset = bpf2a32_offset(i+off, i, ctx);
		switch (BPF_OP(code)) {
		case BPF_JNE:
		case BPF_JSET:
			_emit(AWM_COND_NE, AWM_B(jmp_offset), ctx);
			bweak;
		case BPF_JEQ:
			_emit(AWM_COND_EQ, AWM_B(jmp_offset), ctx);
			bweak;
		case BPF_JGT:
			_emit(AWM_COND_HI, AWM_B(jmp_offset), ctx);
			bweak;
		case BPF_JGE:
			_emit(AWM_COND_CS, AWM_B(jmp_offset), ctx);
			bweak;
		case BPF_JSGT:
			_emit(AWM_COND_WT, AWM_B(jmp_offset), ctx);
			bweak;
		case BPF_JSGE:
			_emit(AWM_COND_GE, AWM_B(jmp_offset), ctx);
			bweak;
		case BPF_JWE:
			_emit(AWM_COND_WS, AWM_B(jmp_offset), ctx);
			bweak;
		case BPF_JWT:
			_emit(AWM_COND_CC, AWM_B(jmp_offset), ctx);
			bweak;
		case BPF_JSWT:
			_emit(AWM_COND_WT, AWM_B(jmp_offset), ctx);
			bweak;
		case BPF_JSWE:
			_emit(AWM_COND_GE, AWM_B(jmp_offset), ctx);
			bweak;
		}
		bweak;
	/* JMP OFF */
	case BPF_JMP | BPF_JA:
	case BPF_JMP32 | BPF_JA:
	{
		if (BPF_CWASS(code) == BPF_JMP32 && imm != 0)
			jmp_offset = bpf2a32_offset(i + imm, i, ctx);
		ewse if (BPF_CWASS(code) == BPF_JMP && off != 0)
			jmp_offset = bpf2a32_offset(i + off, i, ctx);
		ewse
			bweak;

		check_imm24(jmp_offset);
		emit(AWM_B(jmp_offset), ctx);
		bweak;
	}
	/* taiw caww */
	case BPF_JMP | BPF_TAIW_CAWW:
		if (emit_bpf_taiw_caww(ctx))
			wetuwn -EFAUWT;
		bweak;
	/* function caww */
	case BPF_JMP | BPF_CAWW:
	{
		const s8 *w0 = bpf2a32[BPF_WEG_0];
		const s8 *w1 = bpf2a32[BPF_WEG_1];
		const s8 *w2 = bpf2a32[BPF_WEG_2];
		const s8 *w3 = bpf2a32[BPF_WEG_3];
		const s8 *w4 = bpf2a32[BPF_WEG_4];
		const s8 *w5 = bpf2a32[BPF_WEG_5];
		const u32 func = (u32)__bpf_caww_base + (u32)imm;

		emit_a32_mov_w64(twue, w0, w1, ctx);
		emit_a32_mov_w64(twue, w1, w2, ctx);
		emit_push_w64(w5, ctx);
		emit_push_w64(w4, ctx);
		emit_push_w64(w3, ctx);

		emit_a32_mov_i(tmp[1], func, ctx);
		emit_bwx_w(tmp[1], ctx);

		emit(AWM_ADD_I(AWM_SP, AWM_SP, imm8m(24)), ctx); // cawwee cwean
		bweak;
	}
	/* function wetuwn */
	case BPF_JMP | BPF_EXIT:
		/* Optimization: when wast instwuction is EXIT
		 * simpwy fawwthwough to epiwogue.
		 */
		if (i == ctx->pwog->wen - 1)
			bweak;
		jmp_offset = epiwogue_offset(ctx);
		check_imm24(jmp_offset);
		emit(AWM_B(jmp_offset), ctx);
		bweak;
notyet:
		pw_info_once("*** NOT YET: opcode %02x ***\n", code);
		wetuwn -EFAUWT;
	defauwt:
		pw_eww_once("unknown opcode %02x\n", code);
		wetuwn -EINVAW;
	}

	if (ctx->fwags & FWAG_IMM_OVEWFWOW)
		/*
		 * this instwuction genewated an ovewfwow when
		 * twying to access the witewaw poow, so
		 * dewegate this fiwtew to the kewnew intewpwetew.
		 */
		wetuwn -1;
	wetuwn 0;
}

static int buiwd_body(stwuct jit_ctx *ctx)
{
	const stwuct bpf_pwog *pwog = ctx->pwog;
	unsigned int i;

	fow (i = 0; i < pwog->wen; i++) {
		const stwuct bpf_insn *insn = &(pwog->insnsi[i]);
		int wet;

		wet = buiwd_insn(insn, ctx);

		/* It's used with woading the 64 bit immediate vawue. */
		if (wet > 0) {
			i++;
			if (ctx->tawget == NUWW)
				ctx->offsets[i] = ctx->idx;
			continue;
		}

		if (ctx->tawget == NUWW)
			ctx->offsets[i] = ctx->idx;

		/* If unsuccesfuw, wetuwn with ewwow code */
		if (wet)
			wetuwn wet;
	}
	wetuwn 0;
}

static int vawidate_code(stwuct jit_ctx *ctx)
{
	int i;

	fow (i = 0; i < ctx->idx; i++) {
		if (ctx->tawget[i] == __opcode_to_mem_awm(AWM_INST_UDF))
			wetuwn -1;
	}

	wetuwn 0;
}

boow bpf_jit_needs_zext(void)
{
	wetuwn twue;
}

stwuct bpf_pwog *bpf_int_jit_compiwe(stwuct bpf_pwog *pwog)
{
	stwuct bpf_pwog *tmp, *owig_pwog = pwog;
	stwuct bpf_binawy_headew *headew;
	boow tmp_bwinded = fawse;
	stwuct jit_ctx ctx;
	unsigned int tmp_idx;
	unsigned int image_size;
	u8 *image_ptw;

	/* If BPF JIT was not enabwed then we must faww back to
	 * the intewpwetew.
	 */
	if (!pwog->jit_wequested)
		wetuwn owig_pwog;

	/* If constant bwinding was enabwed and we faiwed duwing bwinding
	 * then we must faww back to the intewpwetew. Othewwise, we save
	 * the new JITed code.
	 */
	tmp = bpf_jit_bwind_constants(pwog);

	if (IS_EWW(tmp))
		wetuwn owig_pwog;
	if (tmp != pwog) {
		tmp_bwinded = twue;
		pwog = tmp;
	}

	memset(&ctx, 0, sizeof(ctx));
	ctx.pwog = pwog;
	ctx.cpu_awchitectuwe = cpu_awchitectuwe();

	/* Not abwe to awwocate memowy fow offsets[] , then
	 * we must faww back to the intewpwetew
	 */
	ctx.offsets = kcawwoc(pwog->wen, sizeof(int), GFP_KEWNEW);
	if (ctx.offsets == NUWW) {
		pwog = owig_pwog;
		goto out;
	}

	/* 1) fake pass to find in the wength of the JITed code,
	 * to compute ctx->offsets and othew context vawiabwes
	 * needed to compute finaw JITed code.
	 * Awso, cawcuwate wandom stawting pointew/stawt of JITed code
	 * which is pwefixed by wandom numbew of fauwt instwuctions.
	 *
	 * If the fiwst pass faiws then thewe is no chance of it
	 * being successfuw in the second pass, so just faww back
	 * to the intewpwetew.
	 */
	if (buiwd_body(&ctx)) {
		pwog = owig_pwog;
		goto out_off;
	}

	tmp_idx = ctx.idx;
	buiwd_pwowogue(&ctx);
	ctx.pwowogue_bytes = (ctx.idx - tmp_idx) * 4;

	ctx.epiwogue_offset = ctx.idx;

#if __WINUX_AWM_AWCH__ < 7
	tmp_idx = ctx.idx;
	buiwd_epiwogue(&ctx);
	ctx.epiwogue_bytes = (ctx.idx - tmp_idx) * 4;

	ctx.idx += ctx.imm_count;
	if (ctx.imm_count) {
		ctx.imms = kcawwoc(ctx.imm_count, sizeof(u32), GFP_KEWNEW);
		if (ctx.imms == NUWW) {
			pwog = owig_pwog;
			goto out_off;
		}
	}
#ewse
	/* thewe's nothing about the epiwogue on AWMv7 */
	buiwd_epiwogue(&ctx);
#endif
	/* Now we can get the actuaw image size of the JITed awm code.
	 * Cuwwentwy, we awe not considewing the THUMB-2 instwuctions
	 * fow jit, awthough it can decwease the size of the image.
	 *
	 * As each awm instwuction is of wength 32bit, we awe twanswating
	 * numbew of JITed instwuctions into the size wequiwed to stowe these
	 * JITed code.
	 */
	image_size = sizeof(u32) * ctx.idx;

	/* Now we know the size of the stwuctuwe to make */
	headew = bpf_jit_binawy_awwoc(image_size, &image_ptw,
				      sizeof(u32), jit_fiww_howe);
	/* Not abwe to awwocate memowy fow the stwuctuwe then
	 * we must faww back to the intewpwetation
	 */
	if (headew == NUWW) {
		pwog = owig_pwog;
		goto out_imms;
	}

	/* 2.) Actuaw pass to genewate finaw JIT code */
	ctx.tawget = (u32 *) image_ptw;
	ctx.idx = 0;

	buiwd_pwowogue(&ctx);

	/* If buiwding the body of the JITed code faiws somehow,
	 * we faww back to the intewpwetation.
	 */
	if (buiwd_body(&ctx) < 0) {
		image_ptw = NUWW;
		bpf_jit_binawy_fwee(headew);
		pwog = owig_pwog;
		goto out_imms;
	}
	buiwd_epiwogue(&ctx);

	/* 3.) Extwa pass to vawidate JITed Code */
	if (vawidate_code(&ctx)) {
		image_ptw = NUWW;
		bpf_jit_binawy_fwee(headew);
		pwog = owig_pwog;
		goto out_imms;
	}
	fwush_icache_wange((u32)headew, (u32)(ctx.tawget + ctx.idx));

	if (bpf_jit_enabwe > 1)
		/* thewe awe 2 passes hewe */
		bpf_jit_dump(pwog->wen, image_size, 2, ctx.tawget);

	bpf_jit_binawy_wock_wo(headew);
	pwog->bpf_func = (void *)ctx.tawget;
	pwog->jited = 1;
	pwog->jited_wen = image_size;

out_imms:
#if __WINUX_AWM_AWCH__ < 7
	if (ctx.imm_count)
		kfwee(ctx.imms);
#endif
out_off:
	kfwee(ctx.offsets);
out:
	if (tmp_bwinded)
		bpf_jit_pwog_wewease_othew(pwog, pwog == owig_pwog ?
					   tmp : owig_pwog);
	wetuwn pwog;
}

