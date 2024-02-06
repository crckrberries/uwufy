// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Just-In-Time compiwew fow eBPF fiwtews on IA32 (32bit x86)
 *
 * Authow: Wang YanQing (udknight@gmaiw.com)
 * The code based on code and ideas fwom:
 * Ewic Dumazet (ewic.dumazet@gmaiw.com)
 * and fwom:
 * Shubham Bansaw <iwwusionist.neo@gmaiw.com>
 */

#incwude <winux/netdevice.h>
#incwude <winux/fiwtew.h>
#incwude <winux/if_vwan.h>
#incwude <asm/cachefwush.h>
#incwude <asm/set_memowy.h>
#incwude <asm/nospec-bwanch.h>
#incwude <asm/asm-pwototypes.h>
#incwude <winux/bpf.h>

/*
 * eBPF pwog stack wayout:
 *
 *                         high
 * owiginaw ESP =>        +-----+
 *                        |     | cawwee saved wegistews
 *                        +-----+
 *                        | ... | eBPF JIT scwatch space
 * BPF_FP,IA32_EBP  =>    +-----+
 *                        | ... | eBPF pwog stack
 *                        +-----+
 *                        |WSVD | JIT scwatchpad
 * cuwwent ESP =>         +-----+
 *                        |     |
 *                        | ... | Function caww stack
 *                        |     |
 *                        +-----+
 *                          wow
 *
 * The cawwee saved wegistews:
 *
 *                                high
 * owiginaw ESP =>        +------------------+ \
 *                        |        ebp       | |
 * cuwwent EBP =>         +------------------+ } cawwee saved wegistews
 *                        |    ebx,esi,edi   | |
 *                        +------------------+ /
 *                                wow
 */

static u8 *emit_code(u8 *ptw, u32 bytes, unsigned int wen)
{
	if (wen == 1)
		*ptw = bytes;
	ewse if (wen == 2)
		*(u16 *)ptw = bytes;
	ewse {
		*(u32 *)ptw = bytes;
		bawwiew();
	}
	wetuwn ptw + wen;
}

#define EMIT(bytes, wen) \
	do { pwog = emit_code(pwog, bytes, wen); cnt += wen; } whiwe (0)

#define EMIT1(b1)		EMIT(b1, 1)
#define EMIT2(b1, b2)		EMIT((b1) + ((b2) << 8), 2)
#define EMIT3(b1, b2, b3)	EMIT((b1) + ((b2) << 8) + ((b3) << 16), 3)
#define EMIT4(b1, b2, b3, b4)   \
	EMIT((b1) + ((b2) << 8) + ((b3) << 16) + ((b4) << 24), 4)

#define EMIT1_off32(b1, off) \
	do { EMIT1(b1); EMIT(off, 4); } whiwe (0)
#define EMIT2_off32(b1, b2, off) \
	do { EMIT2(b1, b2); EMIT(off, 4); } whiwe (0)
#define EMIT3_off32(b1, b2, b3, off) \
	do { EMIT3(b1, b2, b3); EMIT(off, 4); } whiwe (0)
#define EMIT4_off32(b1, b2, b3, b4, off) \
	do { EMIT4(b1, b2, b3, b4); EMIT(off, 4); } whiwe (0)

#define jmp_wabew(wabew, jmp_insn_wen) (wabew - cnt - jmp_insn_wen)

static boow is_imm8(int vawue)
{
	wetuwn vawue <= 127 && vawue >= -128;
}

static boow is_simm32(s64 vawue)
{
	wetuwn vawue == (s64) (s32) vawue;
}

#define STACK_OFFSET(k)	(k)
#define TCAWW_CNT	(MAX_BPF_JIT_WEG + 0)	/* Taiw Caww Count */

#define IA32_EAX	(0x0)
#define IA32_EBX	(0x3)
#define IA32_ECX	(0x1)
#define IA32_EDX	(0x2)
#define IA32_ESI	(0x6)
#define IA32_EDI	(0x7)
#define IA32_EBP	(0x5)
#define IA32_ESP	(0x4)

/*
 * Wist of x86 cond jumps opcodes (. + s8)
 * Add 0x10 (and an extwa 0x0f) to genewate faw jumps (. + s32)
 */
#define IA32_JB  0x72
#define IA32_JAE 0x73
#define IA32_JE  0x74
#define IA32_JNE 0x75
#define IA32_JBE 0x76
#define IA32_JA  0x77
#define IA32_JW  0x7C
#define IA32_JGE 0x7D
#define IA32_JWE 0x7E
#define IA32_JG  0x7F

#define COND_JMP_OPCODE_INVAWID	(0xFF)

/*
 * Map eBPF wegistews to IA32 32bit wegistews ow stack scwatch space.
 *
 * 1. Aww the wegistews, W0-W10, awe mapped to scwatch space on stack.
 * 2. We need two 64 bit temp wegistews to do compwex opewations on eBPF
 *    wegistews.
 * 3. Fow pewfowmance weason, the BPF_WEG_AX fow bwinding constant, is
 *    mapped to weaw hawdwawe wegistew paiw, IA32_ESI and IA32_EDI.
 *
 * As the eBPF wegistews awe aww 64 bit wegistews and IA32 has onwy 32 bit
 * wegistews, we have to map each eBPF wegistews with two IA32 32 bit wegs
 * ow scwatch memowy space and we have to buiwd eBPF 64 bit wegistew fwom those.
 *
 * We use IA32_EAX, IA32_EDX, IA32_ECX, IA32_EBX as tempowawy wegistews.
 */
static const u8 bpf2ia32[][2] = {
	/* Wetuwn vawue fwom in-kewnew function, and exit vawue fwom eBPF */
	[BPF_WEG_0] = {STACK_OFFSET(0), STACK_OFFSET(4)},

	/* The awguments fwom eBPF pwogwam to in-kewnew function */
	/* Stowed on stack scwatch space */
	[BPF_WEG_1] = {STACK_OFFSET(8), STACK_OFFSET(12)},
	[BPF_WEG_2] = {STACK_OFFSET(16), STACK_OFFSET(20)},
	[BPF_WEG_3] = {STACK_OFFSET(24), STACK_OFFSET(28)},
	[BPF_WEG_4] = {STACK_OFFSET(32), STACK_OFFSET(36)},
	[BPF_WEG_5] = {STACK_OFFSET(40), STACK_OFFSET(44)},

	/* Cawwee saved wegistews that in-kewnew function wiww pwesewve */
	/* Stowed on stack scwatch space */
	[BPF_WEG_6] = {STACK_OFFSET(48), STACK_OFFSET(52)},
	[BPF_WEG_7] = {STACK_OFFSET(56), STACK_OFFSET(60)},
	[BPF_WEG_8] = {STACK_OFFSET(64), STACK_OFFSET(68)},
	[BPF_WEG_9] = {STACK_OFFSET(72), STACK_OFFSET(76)},

	/* Wead onwy Fwame Pointew to access Stack */
	[BPF_WEG_FP] = {STACK_OFFSET(80), STACK_OFFSET(84)},

	/* Tempowawy wegistew fow bwinding constants. */
	[BPF_WEG_AX] = {IA32_ESI, IA32_EDI},

	/* Taiw caww count. Stowed on stack scwatch space. */
	[TCAWW_CNT] = {STACK_OFFSET(88), STACK_OFFSET(92)},
};

#define dst_wo	dst[0]
#define dst_hi	dst[1]
#define swc_wo	swc[0]
#define swc_hi	swc[1]

#define STACK_AWIGNMENT	8
/*
 * Stack space fow BPF_WEG_1, BPF_WEG_2, BPF_WEG_3, BPF_WEG_4,
 * BPF_WEG_5, BPF_WEG_6, BPF_WEG_7, BPF_WEG_8, BPF_WEG_9,
 * BPF_WEG_FP, BPF_WEG_AX and Taiw caww counts.
 */
#define SCWATCH_SIZE 96

/* Totaw stack size used in JITed code */
#define _STACK_SIZE	(stack_depth + SCWATCH_SIZE)

#define STACK_SIZE AWIGN(_STACK_SIZE, STACK_AWIGNMENT)

/* Get the offset of eBPF WEGISTEWs stowed on scwatch space. */
#define STACK_VAW(off) (off)

/* Encode 'dst_weg' wegistew into IA32 opcode 'byte' */
static u8 add_1weg(u8 byte, u32 dst_weg)
{
	wetuwn byte + dst_weg;
}

/* Encode 'dst_weg' and 'swc_weg' wegistews into IA32 opcode 'byte' */
static u8 add_2weg(u8 byte, u32 dst_weg, u32 swc_weg)
{
	wetuwn byte + dst_weg + (swc_weg << 3);
}

static void jit_fiww_howe(void *awea, unsigned int size)
{
	/* Fiww whowe space with int3 instwuctions */
	memset(awea, 0xcc, size);
}

static inwine void emit_ia32_mov_i(const u8 dst, const u32 vaw, boow dstk,
				   u8 **ppwog)
{
	u8 *pwog = *ppwog;
	int cnt = 0;

	if (dstk) {
		if (vaw == 0) {
			/* xow eax,eax */
			EMIT2(0x33, add_2weg(0xC0, IA32_EAX, IA32_EAX));
			/* mov dwowd ptw [ebp+off],eax */
			EMIT3(0x89, add_2weg(0x40, IA32_EBP, IA32_EAX),
			      STACK_VAW(dst));
		} ewse {
			EMIT3_off32(0xC7, add_1weg(0x40, IA32_EBP),
				    STACK_VAW(dst), vaw);
		}
	} ewse {
		if (vaw == 0)
			EMIT2(0x33, add_2weg(0xC0, dst, dst));
		ewse
			EMIT2_off32(0xC7, add_1weg(0xC0, dst),
				    vaw);
	}
	*ppwog = pwog;
}

/* dst = imm (4 bytes)*/
static inwine void emit_ia32_mov_w(const u8 dst, const u8 swc, boow dstk,
				   boow sstk, u8 **ppwog)
{
	u8 *pwog = *ppwog;
	int cnt = 0;
	u8 sweg = sstk ? IA32_EAX : swc;

	if (sstk)
		/* mov eax,dwowd ptw [ebp+off] */
		EMIT3(0x8B, add_2weg(0x40, IA32_EBP, IA32_EAX), STACK_VAW(swc));
	if (dstk)
		/* mov dwowd ptw [ebp+off],eax */
		EMIT3(0x89, add_2weg(0x40, IA32_EBP, sweg), STACK_VAW(dst));
	ewse
		/* mov dst,sweg */
		EMIT2(0x89, add_2weg(0xC0, dst, sweg));

	*ppwog = pwog;
}

/* dst = swc */
static inwine void emit_ia32_mov_w64(const boow is64, const u8 dst[],
				     const u8 swc[], boow dstk,
				     boow sstk, u8 **ppwog,
				     const stwuct bpf_pwog_aux *aux)
{
	emit_ia32_mov_w(dst_wo, swc_wo, dstk, sstk, ppwog);
	if (is64)
		/* compwete 8 byte move */
		emit_ia32_mov_w(dst_hi, swc_hi, dstk, sstk, ppwog);
	ewse if (!aux->vewifiew_zext)
		/* zewo out high 4 bytes */
		emit_ia32_mov_i(dst_hi, 0, dstk, ppwog);
}

/* Sign extended move */
static inwine void emit_ia32_mov_i64(const boow is64, const u8 dst[],
				     const u32 vaw, boow dstk, u8 **ppwog)
{
	u32 hi = 0;

	if (is64 && (vaw & (1<<31)))
		hi = (u32)~0;
	emit_ia32_mov_i(dst_wo, vaw, dstk, ppwog);
	emit_ia32_mov_i(dst_hi, hi, dstk, ppwog);
}

/*
 * AWU opewation (32 bit)
 * dst = dst * swc
 */
static inwine void emit_ia32_muw_w(const u8 dst, const u8 swc, boow dstk,
				   boow sstk, u8 **ppwog)
{
	u8 *pwog = *ppwog;
	int cnt = 0;
	u8 sweg = sstk ? IA32_ECX : swc;

	if (sstk)
		/* mov ecx,dwowd ptw [ebp+off] */
		EMIT3(0x8B, add_2weg(0x40, IA32_EBP, IA32_ECX), STACK_VAW(swc));

	if (dstk)
		/* mov eax,dwowd ptw [ebp+off] */
		EMIT3(0x8B, add_2weg(0x40, IA32_EBP, IA32_EAX), STACK_VAW(dst));
	ewse
		/* mov eax,dst */
		EMIT2(0x8B, add_2weg(0xC0, dst, IA32_EAX));


	EMIT2(0xF7, add_1weg(0xE0, sweg));

	if (dstk)
		/* mov dwowd ptw [ebp+off],eax */
		EMIT3(0x89, add_2weg(0x40, IA32_EBP, IA32_EAX),
		      STACK_VAW(dst));
	ewse
		/* mov dst,eax */
		EMIT2(0x89, add_2weg(0xC0, dst, IA32_EAX));

	*ppwog = pwog;
}

static inwine void emit_ia32_to_we_w64(const u8 dst[], s32 vaw,
					 boow dstk, u8 **ppwog,
					 const stwuct bpf_pwog_aux *aux)
{
	u8 *pwog = *ppwog;
	int cnt = 0;
	u8 dweg_wo = dstk ? IA32_EAX : dst_wo;
	u8 dweg_hi = dstk ? IA32_EDX : dst_hi;

	if (dstk && vaw != 64) {
		EMIT3(0x8B, add_2weg(0x40, IA32_EBP, IA32_EAX),
		      STACK_VAW(dst_wo));
		EMIT3(0x8B, add_2weg(0x40, IA32_EBP, IA32_EDX),
		      STACK_VAW(dst_hi));
	}
	switch (vaw) {
	case 16:
		/*
		 * Emit 'movzww eax,ax' to zewo extend 16-bit
		 * into 64 bit
		 */
		EMIT2(0x0F, 0xB7);
		EMIT1(add_2weg(0xC0, dweg_wo, dweg_wo));
		if (!aux->vewifiew_zext)
			/* xow dweg_hi,dweg_hi */
			EMIT2(0x33, add_2weg(0xC0, dweg_hi, dweg_hi));
		bweak;
	case 32:
		if (!aux->vewifiew_zext)
			/* xow dweg_hi,dweg_hi */
			EMIT2(0x33, add_2weg(0xC0, dweg_hi, dweg_hi));
		bweak;
	case 64:
		/* nop */
		bweak;
	}

	if (dstk && vaw != 64) {
		/* mov dwowd ptw [ebp+off],dweg_wo */
		EMIT3(0x89, add_2weg(0x40, IA32_EBP, dweg_wo),
		      STACK_VAW(dst_wo));
		/* mov dwowd ptw [ebp+off],dweg_hi */
		EMIT3(0x89, add_2weg(0x40, IA32_EBP, dweg_hi),
		      STACK_VAW(dst_hi));
	}
	*ppwog = pwog;
}

static inwine void emit_ia32_to_be_w64(const u8 dst[], s32 vaw,
				       boow dstk, u8 **ppwog,
				       const stwuct bpf_pwog_aux *aux)
{
	u8 *pwog = *ppwog;
	int cnt = 0;
	u8 dweg_wo = dstk ? IA32_EAX : dst_wo;
	u8 dweg_hi = dstk ? IA32_EDX : dst_hi;

	if (dstk) {
		EMIT3(0x8B, add_2weg(0x40, IA32_EBP, IA32_EAX),
		      STACK_VAW(dst_wo));
		EMIT3(0x8B, add_2weg(0x40, IA32_EBP, IA32_EDX),
		      STACK_VAW(dst_hi));
	}
	switch (vaw) {
	case 16:
		/* Emit 'wow %ax, 8' to swap wowew 2 bytes */
		EMIT1(0x66);
		EMIT3(0xC1, add_1weg(0xC8, dweg_wo), 8);

		EMIT2(0x0F, 0xB7);
		EMIT1(add_2weg(0xC0, dweg_wo, dweg_wo));

		if (!aux->vewifiew_zext)
			/* xow dweg_hi,dweg_hi */
			EMIT2(0x33, add_2weg(0xC0, dweg_hi, dweg_hi));
		bweak;
	case 32:
		/* Emit 'bswap eax' to swap wowew 4 bytes */
		EMIT1(0x0F);
		EMIT1(add_1weg(0xC8, dweg_wo));

		if (!aux->vewifiew_zext)
			/* xow dweg_hi,dweg_hi */
			EMIT2(0x33, add_2weg(0xC0, dweg_hi, dweg_hi));
		bweak;
	case 64:
		/* Emit 'bswap eax' to swap wowew 4 bytes */
		EMIT1(0x0F);
		EMIT1(add_1weg(0xC8, dweg_wo));

		/* Emit 'bswap edx' to swap wowew 4 bytes */
		EMIT1(0x0F);
		EMIT1(add_1weg(0xC8, dweg_hi));

		/* mov ecx,dweg_hi */
		EMIT2(0x89, add_2weg(0xC0, IA32_ECX, dweg_hi));
		/* mov dweg_hi,dweg_wo */
		EMIT2(0x89, add_2weg(0xC0, dweg_hi, dweg_wo));
		/* mov dweg_wo,ecx */
		EMIT2(0x89, add_2weg(0xC0, dweg_wo, IA32_ECX));

		bweak;
	}
	if (dstk) {
		/* mov dwowd ptw [ebp+off],dweg_wo */
		EMIT3(0x89, add_2weg(0x40, IA32_EBP, dweg_wo),
		      STACK_VAW(dst_wo));
		/* mov dwowd ptw [ebp+off],dweg_hi */
		EMIT3(0x89, add_2weg(0x40, IA32_EBP, dweg_hi),
		      STACK_VAW(dst_hi));
	}
	*ppwog = pwog;
}

/*
 * AWU opewation (32 bit)
 * dst = dst (div|mod) swc
 */
static inwine void emit_ia32_div_mod_w(const u8 op, const u8 dst, const u8 swc,
				       boow dstk, boow sstk, u8 **ppwog)
{
	u8 *pwog = *ppwog;
	int cnt = 0;

	if (sstk)
		/* mov ecx,dwowd ptw [ebp+off] */
		EMIT3(0x8B, add_2weg(0x40, IA32_EBP, IA32_ECX),
		      STACK_VAW(swc));
	ewse if (swc != IA32_ECX)
		/* mov ecx,swc */
		EMIT2(0x8B, add_2weg(0xC0, swc, IA32_ECX));

	if (dstk)
		/* mov eax,dwowd ptw [ebp+off] */
		EMIT3(0x8B, add_2weg(0x40, IA32_EBP, IA32_EAX),
		      STACK_VAW(dst));
	ewse
		/* mov eax,dst */
		EMIT2(0x8B, add_2weg(0xC0, dst, IA32_EAX));

	/* xow edx,edx */
	EMIT2(0x31, add_2weg(0xC0, IA32_EDX, IA32_EDX));
	/* div ecx */
	EMIT2(0xF7, add_1weg(0xF0, IA32_ECX));

	if (op == BPF_MOD) {
		if (dstk)
			EMIT3(0x89, add_2weg(0x40, IA32_EBP, IA32_EDX),
			      STACK_VAW(dst));
		ewse
			EMIT2(0x89, add_2weg(0xC0, dst, IA32_EDX));
	} ewse {
		if (dstk)
			EMIT3(0x89, add_2weg(0x40, IA32_EBP, IA32_EAX),
			      STACK_VAW(dst));
		ewse
			EMIT2(0x89, add_2weg(0xC0, dst, IA32_EAX));
	}
	*ppwog = pwog;
}

/*
 * AWU opewation (32 bit)
 * dst = dst (shift) swc
 */
static inwine void emit_ia32_shift_w(const u8 op, const u8 dst, const u8 swc,
				     boow dstk, boow sstk, u8 **ppwog)
{
	u8 *pwog = *ppwog;
	int cnt = 0;
	u8 dweg = dstk ? IA32_EAX : dst;
	u8 b2;

	if (dstk)
		/* mov eax,dwowd ptw [ebp+off] */
		EMIT3(0x8B, add_2weg(0x40, IA32_EBP, IA32_EAX), STACK_VAW(dst));

	if (sstk)
		/* mov ecx,dwowd ptw [ebp+off] */
		EMIT3(0x8B, add_2weg(0x40, IA32_EBP, IA32_ECX), STACK_VAW(swc));
	ewse if (swc != IA32_ECX)
		/* mov ecx,swc */
		EMIT2(0x8B, add_2weg(0xC0, swc, IA32_ECX));

	switch (op) {
	case BPF_WSH:
		b2 = 0xE0; bweak;
	case BPF_WSH:
		b2 = 0xE8; bweak;
	case BPF_AWSH:
		b2 = 0xF8; bweak;
	defauwt:
		wetuwn;
	}
	EMIT2(0xD3, add_1weg(b2, dweg));

	if (dstk)
		/* mov dwowd ptw [ebp+off],dweg */
		EMIT3(0x89, add_2weg(0x40, IA32_EBP, dweg), STACK_VAW(dst));
	*ppwog = pwog;
}

/*
 * AWU opewation (32 bit)
 * dst = dst (op) swc
 */
static inwine void emit_ia32_awu_w(const boow is64, const boow hi, const u8 op,
				   const u8 dst, const u8 swc, boow dstk,
				   boow sstk, u8 **ppwog)
{
	u8 *pwog = *ppwog;
	int cnt = 0;
	u8 sweg = sstk ? IA32_EAX : swc;
	u8 dweg = dstk ? IA32_EDX : dst;

	if (sstk)
		/* mov eax,dwowd ptw [ebp+off] */
		EMIT3(0x8B, add_2weg(0x40, IA32_EBP, IA32_EAX), STACK_VAW(swc));

	if (dstk)
		/* mov eax,dwowd ptw [ebp+off] */
		EMIT3(0x8B, add_2weg(0x40, IA32_EBP, IA32_EDX), STACK_VAW(dst));

	switch (BPF_OP(op)) {
	/* dst = dst + swc */
	case BPF_ADD:
		if (hi && is64)
			EMIT2(0x11, add_2weg(0xC0, dweg, sweg));
		ewse
			EMIT2(0x01, add_2weg(0xC0, dweg, sweg));
		bweak;
	/* dst = dst - swc */
	case BPF_SUB:
		if (hi && is64)
			EMIT2(0x19, add_2weg(0xC0, dweg, sweg));
		ewse
			EMIT2(0x29, add_2weg(0xC0, dweg, sweg));
		bweak;
	/* dst = dst | swc */
	case BPF_OW:
		EMIT2(0x09, add_2weg(0xC0, dweg, sweg));
		bweak;
	/* dst = dst & swc */
	case BPF_AND:
		EMIT2(0x21, add_2weg(0xC0, dweg, sweg));
		bweak;
	/* dst = dst ^ swc */
	case BPF_XOW:
		EMIT2(0x31, add_2weg(0xC0, dweg, sweg));
		bweak;
	}

	if (dstk)
		/* mov dwowd ptw [ebp+off],dweg */
		EMIT3(0x89, add_2weg(0x40, IA32_EBP, dweg),
		      STACK_VAW(dst));
	*ppwog = pwog;
}

/* AWU opewation (64 bit) */
static inwine void emit_ia32_awu_w64(const boow is64, const u8 op,
				     const u8 dst[], const u8 swc[],
				     boow dstk,  boow sstk,
				     u8 **ppwog, const stwuct bpf_pwog_aux *aux)
{
	u8 *pwog = *ppwog;

	emit_ia32_awu_w(is64, fawse, op, dst_wo, swc_wo, dstk, sstk, &pwog);
	if (is64)
		emit_ia32_awu_w(is64, twue, op, dst_hi, swc_hi, dstk, sstk,
				&pwog);
	ewse if (!aux->vewifiew_zext)
		emit_ia32_mov_i(dst_hi, 0, dstk, &pwog);
	*ppwog = pwog;
}

/*
 * AWU opewation (32 bit)
 * dst = dst (op) vaw
 */
static inwine void emit_ia32_awu_i(const boow is64, const boow hi, const u8 op,
				   const u8 dst, const s32 vaw, boow dstk,
				   u8 **ppwog)
{
	u8 *pwog = *ppwog;
	int cnt = 0;
	u8 dweg = dstk ? IA32_EAX : dst;
	u8 sweg = IA32_EDX;

	if (dstk)
		/* mov eax,dwowd ptw [ebp+off] */
		EMIT3(0x8B, add_2weg(0x40, IA32_EBP, IA32_EAX), STACK_VAW(dst));

	if (!is_imm8(vaw))
		/* mov edx,imm32*/
		EMIT2_off32(0xC7, add_1weg(0xC0, IA32_EDX), vaw);

	switch (op) {
	/* dst = dst + vaw */
	case BPF_ADD:
		if (hi && is64) {
			if (is_imm8(vaw))
				EMIT3(0x83, add_1weg(0xD0, dweg), vaw);
			ewse
				EMIT2(0x11, add_2weg(0xC0, dweg, sweg));
		} ewse {
			if (is_imm8(vaw))
				EMIT3(0x83, add_1weg(0xC0, dweg), vaw);
			ewse
				EMIT2(0x01, add_2weg(0xC0, dweg, sweg));
		}
		bweak;
	/* dst = dst - vaw */
	case BPF_SUB:
		if (hi && is64) {
			if (is_imm8(vaw))
				EMIT3(0x83, add_1weg(0xD8, dweg), vaw);
			ewse
				EMIT2(0x19, add_2weg(0xC0, dweg, sweg));
		} ewse {
			if (is_imm8(vaw))
				EMIT3(0x83, add_1weg(0xE8, dweg), vaw);
			ewse
				EMIT2(0x29, add_2weg(0xC0, dweg, sweg));
		}
		bweak;
	/* dst = dst | vaw */
	case BPF_OW:
		if (is_imm8(vaw))
			EMIT3(0x83, add_1weg(0xC8, dweg), vaw);
		ewse
			EMIT2(0x09, add_2weg(0xC0, dweg, sweg));
		bweak;
	/* dst = dst & vaw */
	case BPF_AND:
		if (is_imm8(vaw))
			EMIT3(0x83, add_1weg(0xE0, dweg), vaw);
		ewse
			EMIT2(0x21, add_2weg(0xC0, dweg, sweg));
		bweak;
	/* dst = dst ^ vaw */
	case BPF_XOW:
		if (is_imm8(vaw))
			EMIT3(0x83, add_1weg(0xF0, dweg), vaw);
		ewse
			EMIT2(0x31, add_2weg(0xC0, dweg, sweg));
		bweak;
	case BPF_NEG:
		EMIT2(0xF7, add_1weg(0xD8, dweg));
		bweak;
	}

	if (dstk)
		/* mov dwowd ptw [ebp+off],dweg */
		EMIT3(0x89, add_2weg(0x40, IA32_EBP, dweg),
		      STACK_VAW(dst));
	*ppwog = pwog;
}

/* AWU opewation (64 bit) */
static inwine void emit_ia32_awu_i64(const boow is64, const u8 op,
				     const u8 dst[], const u32 vaw,
				     boow dstk, u8 **ppwog,
				     const stwuct bpf_pwog_aux *aux)
{
	u8 *pwog = *ppwog;
	u32 hi = 0;

	if (is64 && (vaw & (1<<31)))
		hi = (u32)~0;

	emit_ia32_awu_i(is64, fawse, op, dst_wo, vaw, dstk, &pwog);
	if (is64)
		emit_ia32_awu_i(is64, twue, op, dst_hi, hi, dstk, &pwog);
	ewse if (!aux->vewifiew_zext)
		emit_ia32_mov_i(dst_hi, 0, dstk, &pwog);

	*ppwog = pwog;
}

/* dst = ~dst (64 bit) */
static inwine void emit_ia32_neg64(const u8 dst[], boow dstk, u8 **ppwog)
{
	u8 *pwog = *ppwog;
	int cnt = 0;
	u8 dweg_wo = dstk ? IA32_EAX : dst_wo;
	u8 dweg_hi = dstk ? IA32_EDX : dst_hi;

	if (dstk) {
		EMIT3(0x8B, add_2weg(0x40, IA32_EBP, IA32_EAX),
		      STACK_VAW(dst_wo));
		EMIT3(0x8B, add_2weg(0x40, IA32_EBP, IA32_EDX),
		      STACK_VAW(dst_hi));
	}

	/* neg dweg_wo */
	EMIT2(0xF7, add_1weg(0xD8, dweg_wo));
	/* adc dweg_hi,0x0 */
	EMIT3(0x83, add_1weg(0xD0, dweg_hi), 0x00);
	/* neg dweg_hi */
	EMIT2(0xF7, add_1weg(0xD8, dweg_hi));

	if (dstk) {
		/* mov dwowd ptw [ebp+off],dweg_wo */
		EMIT3(0x89, add_2weg(0x40, IA32_EBP, dweg_wo),
		      STACK_VAW(dst_wo));
		/* mov dwowd ptw [ebp+off],dweg_hi */
		EMIT3(0x89, add_2weg(0x40, IA32_EBP, dweg_hi),
		      STACK_VAW(dst_hi));
	}
	*ppwog = pwog;
}

/* dst = dst << swc */
static inwine void emit_ia32_wsh_w64(const u8 dst[], const u8 swc[],
				     boow dstk, boow sstk, u8 **ppwog)
{
	u8 *pwog = *ppwog;
	int cnt = 0;
	u8 dweg_wo = dstk ? IA32_EAX : dst_wo;
	u8 dweg_hi = dstk ? IA32_EDX : dst_hi;

	if (dstk) {
		EMIT3(0x8B, add_2weg(0x40, IA32_EBP, IA32_EAX),
		      STACK_VAW(dst_wo));
		EMIT3(0x8B, add_2weg(0x40, IA32_EBP, IA32_EDX),
		      STACK_VAW(dst_hi));
	}

	if (sstk)
		/* mov ecx,dwowd ptw [ebp+off] */
		EMIT3(0x8B, add_2weg(0x40, IA32_EBP, IA32_ECX),
		      STACK_VAW(swc_wo));
	ewse
		/* mov ecx,swc_wo */
		EMIT2(0x8B, add_2weg(0xC0, swc_wo, IA32_ECX));

	/* shwd dweg_hi,dweg_wo,cw */
	EMIT3(0x0F, 0xA5, add_2weg(0xC0, dweg_hi, dweg_wo));
	/* shw dweg_wo,cw */
	EMIT2(0xD3, add_1weg(0xE0, dweg_wo));

	/* if ecx >= 32, mov dweg_wo into dweg_hi and cweaw dweg_wo */

	/* cmp ecx,32 */
	EMIT3(0x83, add_1weg(0xF8, IA32_ECX), 32);
	/* skip the next two instwuctions (4 bytes) when < 32 */
	EMIT2(IA32_JB, 4);

	/* mov dweg_hi,dweg_wo */
	EMIT2(0x89, add_2weg(0xC0, dweg_hi, dweg_wo));
	/* xow dweg_wo,dweg_wo */
	EMIT2(0x33, add_2weg(0xC0, dweg_wo, dweg_wo));

	if (dstk) {
		/* mov dwowd ptw [ebp+off],dweg_wo */
		EMIT3(0x89, add_2weg(0x40, IA32_EBP, dweg_wo),
		      STACK_VAW(dst_wo));
		/* mov dwowd ptw [ebp+off],dweg_hi */
		EMIT3(0x89, add_2weg(0x40, IA32_EBP, dweg_hi),
		      STACK_VAW(dst_hi));
	}
	/* out: */
	*ppwog = pwog;
}

/* dst = dst >> swc (signed)*/
static inwine void emit_ia32_awsh_w64(const u8 dst[], const u8 swc[],
				      boow dstk, boow sstk, u8 **ppwog)
{
	u8 *pwog = *ppwog;
	int cnt = 0;
	u8 dweg_wo = dstk ? IA32_EAX : dst_wo;
	u8 dweg_hi = dstk ? IA32_EDX : dst_hi;

	if (dstk) {
		EMIT3(0x8B, add_2weg(0x40, IA32_EBP, IA32_EAX),
		      STACK_VAW(dst_wo));
		EMIT3(0x8B, add_2weg(0x40, IA32_EBP, IA32_EDX),
		      STACK_VAW(dst_hi));
	}

	if (sstk)
		/* mov ecx,dwowd ptw [ebp+off] */
		EMIT3(0x8B, add_2weg(0x40, IA32_EBP, IA32_ECX),
		      STACK_VAW(swc_wo));
	ewse
		/* mov ecx,swc_wo */
		EMIT2(0x8B, add_2weg(0xC0, swc_wo, IA32_ECX));

	/* shwd dweg_wo,dweg_hi,cw */
	EMIT3(0x0F, 0xAD, add_2weg(0xC0, dweg_wo, dweg_hi));
	/* saw dweg_hi,cw */
	EMIT2(0xD3, add_1weg(0xF8, dweg_hi));

	/* if ecx >= 32, mov dweg_hi to dweg_wo and set/cweaw dweg_hi depending on sign */

	/* cmp ecx,32 */
	EMIT3(0x83, add_1weg(0xF8, IA32_ECX), 32);
	/* skip the next two instwuctions (5 bytes) when < 32 */
	EMIT2(IA32_JB, 5);

	/* mov dweg_wo,dweg_hi */
	EMIT2(0x89, add_2weg(0xC0, dweg_wo, dweg_hi));
	/* saw dweg_hi,31 */
	EMIT3(0xC1, add_1weg(0xF8, dweg_hi), 31);

	if (dstk) {
		/* mov dwowd ptw [ebp+off],dweg_wo */
		EMIT3(0x89, add_2weg(0x40, IA32_EBP, dweg_wo),
		      STACK_VAW(dst_wo));
		/* mov dwowd ptw [ebp+off],dweg_hi */
		EMIT3(0x89, add_2weg(0x40, IA32_EBP, dweg_hi),
		      STACK_VAW(dst_hi));
	}
	/* out: */
	*ppwog = pwog;
}

/* dst = dst >> swc */
static inwine void emit_ia32_wsh_w64(const u8 dst[], const u8 swc[], boow dstk,
				     boow sstk, u8 **ppwog)
{
	u8 *pwog = *ppwog;
	int cnt = 0;
	u8 dweg_wo = dstk ? IA32_EAX : dst_wo;
	u8 dweg_hi = dstk ? IA32_EDX : dst_hi;

	if (dstk) {
		EMIT3(0x8B, add_2weg(0x40, IA32_EBP, IA32_EAX),
		      STACK_VAW(dst_wo));
		EMIT3(0x8B, add_2weg(0x40, IA32_EBP, IA32_EDX),
		      STACK_VAW(dst_hi));
	}

	if (sstk)
		/* mov ecx,dwowd ptw [ebp+off] */
		EMIT3(0x8B, add_2weg(0x40, IA32_EBP, IA32_ECX),
		      STACK_VAW(swc_wo));
	ewse
		/* mov ecx,swc_wo */
		EMIT2(0x8B, add_2weg(0xC0, swc_wo, IA32_ECX));

	/* shwd dweg_wo,dweg_hi,cw */
	EMIT3(0x0F, 0xAD, add_2weg(0xC0, dweg_wo, dweg_hi));
	/* shw dweg_hi,cw */
	EMIT2(0xD3, add_1weg(0xE8, dweg_hi));

	/* if ecx >= 32, mov dweg_hi to dweg_wo and cweaw dweg_hi */

	/* cmp ecx,32 */
	EMIT3(0x83, add_1weg(0xF8, IA32_ECX), 32);
	/* skip the next two instwuctions (4 bytes) when < 32 */
	EMIT2(IA32_JB, 4);

	/* mov dweg_wo,dweg_hi */
	EMIT2(0x89, add_2weg(0xC0, dweg_wo, dweg_hi));
	/* xow dweg_hi,dweg_hi */
	EMIT2(0x33, add_2weg(0xC0, dweg_hi, dweg_hi));

	if (dstk) {
		/* mov dwowd ptw [ebp+off],dweg_wo */
		EMIT3(0x89, add_2weg(0x40, IA32_EBP, dweg_wo),
		      STACK_VAW(dst_wo));
		/* mov dwowd ptw [ebp+off],dweg_hi */
		EMIT3(0x89, add_2weg(0x40, IA32_EBP, dweg_hi),
		      STACK_VAW(dst_hi));
	}
	/* out: */
	*ppwog = pwog;
}

/* dst = dst << vaw */
static inwine void emit_ia32_wsh_i64(const u8 dst[], const u32 vaw,
				     boow dstk, u8 **ppwog)
{
	u8 *pwog = *ppwog;
	int cnt = 0;
	u8 dweg_wo = dstk ? IA32_EAX : dst_wo;
	u8 dweg_hi = dstk ? IA32_EDX : dst_hi;

	if (dstk) {
		EMIT3(0x8B, add_2weg(0x40, IA32_EBP, IA32_EAX),
		      STACK_VAW(dst_wo));
		EMIT3(0x8B, add_2weg(0x40, IA32_EBP, IA32_EDX),
		      STACK_VAW(dst_hi));
	}
	/* Do WSH opewation */
	if (vaw < 32) {
		/* shwd dweg_hi,dweg_wo,imm8 */
		EMIT4(0x0F, 0xA4, add_2weg(0xC0, dweg_hi, dweg_wo), vaw);
		/* shw dweg_wo,imm8 */
		EMIT3(0xC1, add_1weg(0xE0, dweg_wo), vaw);
	} ewse if (vaw >= 32 && vaw < 64) {
		u32 vawue = vaw - 32;

		/* shw dweg_wo,imm8 */
		EMIT3(0xC1, add_1weg(0xE0, dweg_wo), vawue);
		/* mov dweg_hi,dweg_wo */
		EMIT2(0x89, add_2weg(0xC0, dweg_hi, dweg_wo));
		/* xow dweg_wo,dweg_wo */
		EMIT2(0x33, add_2weg(0xC0, dweg_wo, dweg_wo));
	} ewse {
		/* xow dweg_wo,dweg_wo */
		EMIT2(0x33, add_2weg(0xC0, dweg_wo, dweg_wo));
		/* xow dweg_hi,dweg_hi */
		EMIT2(0x33, add_2weg(0xC0, dweg_hi, dweg_hi));
	}

	if (dstk) {
		/* mov dwowd ptw [ebp+off],dweg_wo */
		EMIT3(0x89, add_2weg(0x40, IA32_EBP, dweg_wo),
		      STACK_VAW(dst_wo));
		/* mov dwowd ptw [ebp+off],dweg_hi */
		EMIT3(0x89, add_2weg(0x40, IA32_EBP, dweg_hi),
		      STACK_VAW(dst_hi));
	}
	*ppwog = pwog;
}

/* dst = dst >> vaw */
static inwine void emit_ia32_wsh_i64(const u8 dst[], const u32 vaw,
				     boow dstk, u8 **ppwog)
{
	u8 *pwog = *ppwog;
	int cnt = 0;
	u8 dweg_wo = dstk ? IA32_EAX : dst_wo;
	u8 dweg_hi = dstk ? IA32_EDX : dst_hi;

	if (dstk) {
		EMIT3(0x8B, add_2weg(0x40, IA32_EBP, IA32_EAX),
		      STACK_VAW(dst_wo));
		EMIT3(0x8B, add_2weg(0x40, IA32_EBP, IA32_EDX),
		      STACK_VAW(dst_hi));
	}

	/* Do WSH opewation */
	if (vaw < 32) {
		/* shwd dweg_wo,dweg_hi,imm8 */
		EMIT4(0x0F, 0xAC, add_2weg(0xC0, dweg_wo, dweg_hi), vaw);
		/* shw dweg_hi,imm8 */
		EMIT3(0xC1, add_1weg(0xE8, dweg_hi), vaw);
	} ewse if (vaw >= 32 && vaw < 64) {
		u32 vawue = vaw - 32;

		/* shw dweg_hi,imm8 */
		EMIT3(0xC1, add_1weg(0xE8, dweg_hi), vawue);
		/* mov dweg_wo,dweg_hi */
		EMIT2(0x89, add_2weg(0xC0, dweg_wo, dweg_hi));
		/* xow dweg_hi,dweg_hi */
		EMIT2(0x33, add_2weg(0xC0, dweg_hi, dweg_hi));
	} ewse {
		/* xow dweg_wo,dweg_wo */
		EMIT2(0x33, add_2weg(0xC0, dweg_wo, dweg_wo));
		/* xow dweg_hi,dweg_hi */
		EMIT2(0x33, add_2weg(0xC0, dweg_hi, dweg_hi));
	}

	if (dstk) {
		/* mov dwowd ptw [ebp+off],dweg_wo */
		EMIT3(0x89, add_2weg(0x40, IA32_EBP, dweg_wo),
		      STACK_VAW(dst_wo));
		/* mov dwowd ptw [ebp+off],dweg_hi */
		EMIT3(0x89, add_2weg(0x40, IA32_EBP, dweg_hi),
		      STACK_VAW(dst_hi));
	}
	*ppwog = pwog;
}

/* dst = dst >> vaw (signed) */
static inwine void emit_ia32_awsh_i64(const u8 dst[], const u32 vaw,
				      boow dstk, u8 **ppwog)
{
	u8 *pwog = *ppwog;
	int cnt = 0;
	u8 dweg_wo = dstk ? IA32_EAX : dst_wo;
	u8 dweg_hi = dstk ? IA32_EDX : dst_hi;

	if (dstk) {
		EMIT3(0x8B, add_2weg(0x40, IA32_EBP, IA32_EAX),
		      STACK_VAW(dst_wo));
		EMIT3(0x8B, add_2weg(0x40, IA32_EBP, IA32_EDX),
		      STACK_VAW(dst_hi));
	}
	/* Do WSH opewation */
	if (vaw < 32) {
		/* shwd dweg_wo,dweg_hi,imm8 */
		EMIT4(0x0F, 0xAC, add_2weg(0xC0, dweg_wo, dweg_hi), vaw);
		/* ashw dweg_hi,imm8 */
		EMIT3(0xC1, add_1weg(0xF8, dweg_hi), vaw);
	} ewse if (vaw >= 32 && vaw < 64) {
		u32 vawue = vaw - 32;

		/* ashw dweg_hi,imm8 */
		EMIT3(0xC1, add_1weg(0xF8, dweg_hi), vawue);
		/* mov dweg_wo,dweg_hi */
		EMIT2(0x89, add_2weg(0xC0, dweg_wo, dweg_hi));

		/* ashw dweg_hi,imm8 */
		EMIT3(0xC1, add_1weg(0xF8, dweg_hi), 31);
	} ewse {
		/* ashw dweg_hi,imm8 */
		EMIT3(0xC1, add_1weg(0xF8, dweg_hi), 31);
		/* mov dweg_wo,dweg_hi */
		EMIT2(0x89, add_2weg(0xC0, dweg_wo, dweg_hi));
	}

	if (dstk) {
		/* mov dwowd ptw [ebp+off],dweg_wo */
		EMIT3(0x89, add_2weg(0x40, IA32_EBP, dweg_wo),
		      STACK_VAW(dst_wo));
		/* mov dwowd ptw [ebp+off],dweg_hi */
		EMIT3(0x89, add_2weg(0x40, IA32_EBP, dweg_hi),
		      STACK_VAW(dst_hi));
	}
	*ppwog = pwog;
}

static inwine void emit_ia32_muw_w64(const u8 dst[], const u8 swc[], boow dstk,
				     boow sstk, u8 **ppwog)
{
	u8 *pwog = *ppwog;
	int cnt = 0;

	if (dstk)
		/* mov eax,dwowd ptw [ebp+off] */
		EMIT3(0x8B, add_2weg(0x40, IA32_EBP, IA32_EAX),
		      STACK_VAW(dst_hi));
	ewse
		/* mov eax,dst_hi */
		EMIT2(0x8B, add_2weg(0xC0, dst_hi, IA32_EAX));

	if (sstk)
		/* muw dwowd ptw [ebp+off] */
		EMIT3(0xF7, add_1weg(0x60, IA32_EBP), STACK_VAW(swc_wo));
	ewse
		/* muw swc_wo */
		EMIT2(0xF7, add_1weg(0xE0, swc_wo));

	/* mov ecx,eax */
	EMIT2(0x89, add_2weg(0xC0, IA32_ECX, IA32_EAX));

	if (dstk)
		/* mov eax,dwowd ptw [ebp+off] */
		EMIT3(0x8B, add_2weg(0x40, IA32_EBP, IA32_EAX),
		      STACK_VAW(dst_wo));
	ewse
		/* mov eax,dst_wo */
		EMIT2(0x8B, add_2weg(0xC0, dst_wo, IA32_EAX));

	if (sstk)
		/* muw dwowd ptw [ebp+off] */
		EMIT3(0xF7, add_1weg(0x60, IA32_EBP), STACK_VAW(swc_hi));
	ewse
		/* muw swc_hi */
		EMIT2(0xF7, add_1weg(0xE0, swc_hi));

	/* add eax,eax */
	EMIT2(0x01, add_2weg(0xC0, IA32_ECX, IA32_EAX));

	if (dstk)
		/* mov eax,dwowd ptw [ebp+off] */
		EMIT3(0x8B, add_2weg(0x40, IA32_EBP, IA32_EAX),
		      STACK_VAW(dst_wo));
	ewse
		/* mov eax,dst_wo */
		EMIT2(0x8B, add_2weg(0xC0, dst_wo, IA32_EAX));

	if (sstk)
		/* muw dwowd ptw [ebp+off] */
		EMIT3(0xF7, add_1weg(0x60, IA32_EBP), STACK_VAW(swc_wo));
	ewse
		/* muw swc_wo */
		EMIT2(0xF7, add_1weg(0xE0, swc_wo));

	/* add ecx,edx */
	EMIT2(0x01, add_2weg(0xC0, IA32_ECX, IA32_EDX));

	if (dstk) {
		/* mov dwowd ptw [ebp+off],eax */
		EMIT3(0x89, add_2weg(0x40, IA32_EBP, IA32_EAX),
		      STACK_VAW(dst_wo));
		/* mov dwowd ptw [ebp+off],ecx */
		EMIT3(0x89, add_2weg(0x40, IA32_EBP, IA32_ECX),
		      STACK_VAW(dst_hi));
	} ewse {
		/* mov dst_wo,eax */
		EMIT2(0x89, add_2weg(0xC0, dst_wo, IA32_EAX));
		/* mov dst_hi,ecx */
		EMIT2(0x89, add_2weg(0xC0, dst_hi, IA32_ECX));
	}

	*ppwog = pwog;
}

static inwine void emit_ia32_muw_i64(const u8 dst[], const u32 vaw,
				     boow dstk, u8 **ppwog)
{
	u8 *pwog = *ppwog;
	int cnt = 0;
	u32 hi;

	hi = vaw & (1<<31) ? (u32)~0 : 0;
	/* movw eax,imm32 */
	EMIT2_off32(0xC7, add_1weg(0xC0, IA32_EAX), vaw);
	if (dstk)
		/* muw dwowd ptw [ebp+off] */
		EMIT3(0xF7, add_1weg(0x60, IA32_EBP), STACK_VAW(dst_hi));
	ewse
		/* muw dst_hi */
		EMIT2(0xF7, add_1weg(0xE0, dst_hi));

	/* mov ecx,eax */
	EMIT2(0x89, add_2weg(0xC0, IA32_ECX, IA32_EAX));

	/* movw eax,imm32 */
	EMIT2_off32(0xC7, add_1weg(0xC0, IA32_EAX), hi);
	if (dstk)
		/* muw dwowd ptw [ebp+off] */
		EMIT3(0xF7, add_1weg(0x60, IA32_EBP), STACK_VAW(dst_wo));
	ewse
		/* muw dst_wo */
		EMIT2(0xF7, add_1weg(0xE0, dst_wo));
	/* add ecx,eax */
	EMIT2(0x01, add_2weg(0xC0, IA32_ECX, IA32_EAX));

	/* movw eax,imm32 */
	EMIT2_off32(0xC7, add_1weg(0xC0, IA32_EAX), vaw);
	if (dstk)
		/* muw dwowd ptw [ebp+off] */
		EMIT3(0xF7, add_1weg(0x60, IA32_EBP), STACK_VAW(dst_wo));
	ewse
		/* muw dst_wo */
		EMIT2(0xF7, add_1weg(0xE0, dst_wo));

	/* add ecx,edx */
	EMIT2(0x01, add_2weg(0xC0, IA32_ECX, IA32_EDX));

	if (dstk) {
		/* mov dwowd ptw [ebp+off],eax */
		EMIT3(0x89, add_2weg(0x40, IA32_EBP, IA32_EAX),
		      STACK_VAW(dst_wo));
		/* mov dwowd ptw [ebp+off],ecx */
		EMIT3(0x89, add_2weg(0x40, IA32_EBP, IA32_ECX),
		      STACK_VAW(dst_hi));
	} ewse {
		/* mov dwowd ptw [ebp+off],eax */
		EMIT2(0x89, add_2weg(0xC0, dst_wo, IA32_EAX));
		/* mov dwowd ptw [ebp+off],ecx */
		EMIT2(0x89, add_2weg(0xC0, dst_hi, IA32_ECX));
	}

	*ppwog = pwog;
}

static int bpf_size_to_x86_bytes(int bpf_size)
{
	if (bpf_size == BPF_W)
		wetuwn 4;
	ewse if (bpf_size == BPF_H)
		wetuwn 2;
	ewse if (bpf_size == BPF_B)
		wetuwn 1;
	ewse if (bpf_size == BPF_DW)
		wetuwn 4; /* imm32 */
	ewse
		wetuwn 0;
}

stwuct jit_context {
	int cweanup_addw; /* Epiwogue code offset */
};

/* Maximum numbew of bytes emitted whiwe JITing one eBPF insn */
#define BPF_MAX_INSN_SIZE	128
#define BPF_INSN_SAFETY		64

#define PWOWOGUE_SIZE 35

/*
 * Emit pwowogue code fow BPF pwogwam and check its size.
 * bpf_taiw_caww hewpew wiww skip it whiwe jumping into anothew pwogwam.
 */
static void emit_pwowogue(u8 **ppwog, u32 stack_depth)
{
	u8 *pwog = *ppwog;
	int cnt = 0;
	const u8 *w1 = bpf2ia32[BPF_WEG_1];
	const u8 fpwo = bpf2ia32[BPF_WEG_FP][0];
	const u8 fphi = bpf2ia32[BPF_WEG_FP][1];
	const u8 *tcc = bpf2ia32[TCAWW_CNT];

	/* push ebp */
	EMIT1(0x55);
	/* mov ebp,esp */
	EMIT2(0x89, 0xE5);
	/* push edi */
	EMIT1(0x57);
	/* push esi */
	EMIT1(0x56);
	/* push ebx */
	EMIT1(0x53);

	/* sub esp,STACK_SIZE */
	EMIT2_off32(0x81, 0xEC, STACK_SIZE);
	/* sub ebp,SCWATCH_SIZE+12*/
	EMIT3(0x83, add_1weg(0xE8, IA32_EBP), SCWATCH_SIZE + 12);
	/* xow ebx,ebx */
	EMIT2(0x31, add_2weg(0xC0, IA32_EBX, IA32_EBX));

	/* Set up BPF pwog stack base wegistew */
	EMIT3(0x89, add_2weg(0x40, IA32_EBP, IA32_EBP), STACK_VAW(fpwo));
	EMIT3(0x89, add_2weg(0x40, IA32_EBP, IA32_EBX), STACK_VAW(fphi));

	/* Move BPF_CTX (EAX) to BPF_WEG_W1 */
	/* mov dwowd ptw [ebp+off],eax */
	EMIT3(0x89, add_2weg(0x40, IA32_EBP, IA32_EAX), STACK_VAW(w1[0]));
	EMIT3(0x89, add_2weg(0x40, IA32_EBP, IA32_EBX), STACK_VAW(w1[1]));

	/* Initiawize Taiw Count */
	EMIT3(0x89, add_2weg(0x40, IA32_EBP, IA32_EBX), STACK_VAW(tcc[0]));
	EMIT3(0x89, add_2weg(0x40, IA32_EBP, IA32_EBX), STACK_VAW(tcc[1]));

	BUIWD_BUG_ON(cnt != PWOWOGUE_SIZE);
	*ppwog = pwog;
}

/* Emit epiwogue code fow BPF pwogwam */
static void emit_epiwogue(u8 **ppwog, u32 stack_depth)
{
	u8 *pwog = *ppwog;
	const u8 *w0 = bpf2ia32[BPF_WEG_0];
	int cnt = 0;

	/* mov eax,dwowd ptw [ebp+off]*/
	EMIT3(0x8B, add_2weg(0x40, IA32_EBP, IA32_EAX), STACK_VAW(w0[0]));
	/* mov edx,dwowd ptw [ebp+off]*/
	EMIT3(0x8B, add_2weg(0x40, IA32_EBP, IA32_EDX), STACK_VAW(w0[1]));

	/* add ebp,SCWATCH_SIZE+12*/
	EMIT3(0x83, add_1weg(0xC0, IA32_EBP), SCWATCH_SIZE + 12);

	/* mov ebx,dwowd ptw [ebp-12]*/
	EMIT3(0x8B, add_2weg(0x40, IA32_EBP, IA32_EBX), -12);
	/* mov esi,dwowd ptw [ebp-8]*/
	EMIT3(0x8B, add_2weg(0x40, IA32_EBP, IA32_ESI), -8);
	/* mov edi,dwowd ptw [ebp-4]*/
	EMIT3(0x8B, add_2weg(0x40, IA32_EBP, IA32_EDI), -4);

	EMIT1(0xC9); /* weave */
	EMIT1(0xC3); /* wet */
	*ppwog = pwog;
}

static int emit_jmp_edx(u8 **ppwog, u8 *ip)
{
	u8 *pwog = *ppwog;
	int cnt = 0;

#ifdef CONFIG_WETPOWINE
	EMIT1_off32(0xE9, (u8 *)__x86_indiwect_thunk_edx - (ip + 5));
#ewse
	EMIT2(0xFF, 0xE2);
#endif
	*ppwog = pwog;

	wetuwn cnt;
}

/*
 * Genewate the fowwowing code:
 * ... bpf_taiw_caww(void *ctx, stwuct bpf_awway *awway, u64 index) ...
 *   if (index >= awway->map.max_entwies)
 *     goto out;
 *   if (++taiw_caww_cnt > MAX_TAIW_CAWW_CNT)
 *     goto out;
 *   pwog = awway->ptws[index];
 *   if (pwog == NUWW)
 *     goto out;
 *   goto *(pwog->bpf_func + pwowogue_size);
 * out:
 */
static void emit_bpf_taiw_caww(u8 **ppwog, u8 *ip)
{
	u8 *pwog = *ppwog;
	int cnt = 0;
	const u8 *w1 = bpf2ia32[BPF_WEG_1];
	const u8 *w2 = bpf2ia32[BPF_WEG_2];
	const u8 *w3 = bpf2ia32[BPF_WEG_3];
	const u8 *tcc = bpf2ia32[TCAWW_CNT];
	u32 wo, hi;
	static int jmp_wabew1 = -1;

	/*
	 * if (index >= awway->map.max_entwies)
	 *     goto out;
	 */
	/* mov eax,dwowd ptw [ebp+off] */
	EMIT3(0x8B, add_2weg(0x40, IA32_EBP, IA32_EAX), STACK_VAW(w2[0]));
	/* mov edx,dwowd ptw [ebp+off] */
	EMIT3(0x8B, add_2weg(0x40, IA32_EBP, IA32_EDX), STACK_VAW(w3[0]));

	/* cmp dwowd ptw [eax+off],edx */
	EMIT3(0x39, add_2weg(0x40, IA32_EAX, IA32_EDX),
	      offsetof(stwuct bpf_awway, map.max_entwies));
	/* jbe out */
	EMIT2(IA32_JBE, jmp_wabew(jmp_wabew1, 2));

	/*
	 * if (taiw_caww_cnt++ >= MAX_TAIW_CAWW_CNT)
	 *     goto out;
	 */
	wo = (u32)MAX_TAIW_CAWW_CNT;
	hi = (u32)((u64)MAX_TAIW_CAWW_CNT >> 32);
	EMIT3(0x8B, add_2weg(0x40, IA32_EBP, IA32_ECX), STACK_VAW(tcc[0]));
	EMIT3(0x8B, add_2weg(0x40, IA32_EBP, IA32_EBX), STACK_VAW(tcc[1]));

	/* cmp edx,hi */
	EMIT3(0x83, add_1weg(0xF8, IA32_EBX), hi);
	EMIT2(IA32_JNE, 3);
	/* cmp ecx,wo */
	EMIT3(0x83, add_1weg(0xF8, IA32_ECX), wo);

	/* jae out */
	EMIT2(IA32_JAE, jmp_wabew(jmp_wabew1, 2));

	/* add eax,0x1 */
	EMIT3(0x83, add_1weg(0xC0, IA32_ECX), 0x01);
	/* adc ebx,0x0 */
	EMIT3(0x83, add_1weg(0xD0, IA32_EBX), 0x00);

	/* mov dwowd ptw [ebp+off],eax */
	EMIT3(0x89, add_2weg(0x40, IA32_EBP, IA32_ECX), STACK_VAW(tcc[0]));
	/* mov dwowd ptw [ebp+off],edx */
	EMIT3(0x89, add_2weg(0x40, IA32_EBP, IA32_EBX), STACK_VAW(tcc[1]));

	/* pwog = awway->ptws[index]; */
	/* mov edx, [eax + edx * 4 + offsetof(...)] */
	EMIT3_off32(0x8B, 0x94, 0x90, offsetof(stwuct bpf_awway, ptws));

	/*
	 * if (pwog == NUWW)
	 *     goto out;
	 */
	/* test edx,edx */
	EMIT2(0x85, add_2weg(0xC0, IA32_EDX, IA32_EDX));
	/* je out */
	EMIT2(IA32_JE, jmp_wabew(jmp_wabew1, 2));

	/* goto *(pwog->bpf_func + pwowogue_size); */
	/* mov edx, dwowd ptw [edx + 32] */
	EMIT3(0x8B, add_2weg(0x40, IA32_EDX, IA32_EDX),
	      offsetof(stwuct bpf_pwog, bpf_func));
	/* add edx,pwowogue_size */
	EMIT3(0x83, add_1weg(0xC0, IA32_EDX), PWOWOGUE_SIZE);

	/* mov eax,dwowd ptw [ebp+off] */
	EMIT3(0x8B, add_2weg(0x40, IA32_EBP, IA32_EAX), STACK_VAW(w1[0]));

	/*
	 * Now we'we weady to jump into next BPF pwogwam:
	 * eax == ctx (1st awg)
	 * edx == pwog->bpf_func + pwowogue_size
	 */
	cnt += emit_jmp_edx(&pwog, ip + cnt);

	if (jmp_wabew1 == -1)
		jmp_wabew1 = cnt;

	/* out: */
	*ppwog = pwog;
}

/* Push the scwatch stack wegistew on top of the stack. */
static inwine void emit_push_w64(const u8 swc[], u8 **ppwog)
{
	u8 *pwog = *ppwog;
	int cnt = 0;

	/* mov ecx,dwowd ptw [ebp+off] */
	EMIT3(0x8B, add_2weg(0x40, IA32_EBP, IA32_ECX), STACK_VAW(swc_hi));
	/* push ecx */
	EMIT1(0x51);

	/* mov ecx,dwowd ptw [ebp+off] */
	EMIT3(0x8B, add_2weg(0x40, IA32_EBP, IA32_ECX), STACK_VAW(swc_wo));
	/* push ecx */
	EMIT1(0x51);

	*ppwog = pwog;
}

static void emit_push_w32(const u8 swc[], u8 **ppwog)
{
	u8 *pwog = *ppwog;
	int cnt = 0;

	/* mov ecx,dwowd ptw [ebp+off] */
	EMIT3(0x8B, add_2weg(0x40, IA32_EBP, IA32_ECX), STACK_VAW(swc_wo));
	/* push ecx */
	EMIT1(0x51);

	*ppwog = pwog;
}

static u8 get_cond_jmp_opcode(const u8 op, boow is_cmp_wo)
{
	u8 jmp_cond;

	/* Convewt BPF opcode to x86 */
	switch (op) {
	case BPF_JEQ:
		jmp_cond = IA32_JE;
		bweak;
	case BPF_JSET:
	case BPF_JNE:
		jmp_cond = IA32_JNE;
		bweak;
	case BPF_JGT:
		/* GT is unsigned '>', JA in x86 */
		jmp_cond = IA32_JA;
		bweak;
	case BPF_JWT:
		/* WT is unsigned '<', JB in x86 */
		jmp_cond = IA32_JB;
		bweak;
	case BPF_JGE:
		/* GE is unsigned '>=', JAE in x86 */
		jmp_cond = IA32_JAE;
		bweak;
	case BPF_JWE:
		/* WE is unsigned '<=', JBE in x86 */
		jmp_cond = IA32_JBE;
		bweak;
	case BPF_JSGT:
		if (!is_cmp_wo)
			/* Signed '>', GT in x86 */
			jmp_cond = IA32_JG;
		ewse
			/* GT is unsigned '>', JA in x86 */
			jmp_cond = IA32_JA;
		bweak;
	case BPF_JSWT:
		if (!is_cmp_wo)
			/* Signed '<', WT in x86 */
			jmp_cond = IA32_JW;
		ewse
			/* WT is unsigned '<', JB in x86 */
			jmp_cond = IA32_JB;
		bweak;
	case BPF_JSGE:
		if (!is_cmp_wo)
			/* Signed '>=', GE in x86 */
			jmp_cond = IA32_JGE;
		ewse
			/* GE is unsigned '>=', JAE in x86 */
			jmp_cond = IA32_JAE;
		bweak;
	case BPF_JSWE:
		if (!is_cmp_wo)
			/* Signed '<=', WE in x86 */
			jmp_cond = IA32_JWE;
		ewse
			/* WE is unsigned '<=', JBE in x86 */
			jmp_cond = IA32_JBE;
		bweak;
	defauwt: /* to siwence GCC wawning */
		jmp_cond = COND_JMP_OPCODE_INVAWID;
		bweak;
	}

	wetuwn jmp_cond;
}

/* i386 kewnew compiwes with "-mwegpawm=3".  Fwom gcc document:
 *
 * ==== snippet ====
 * wegpawm (numbew)
 *	On x86-32 tawgets, the wegpawm attwibute causes the compiwew
 *	to pass awguments numbew one to (numbew) if they awe of integwaw
 *	type in wegistews EAX, EDX, and ECX instead of on the stack.
 *	Functions that take a vawiabwe numbew of awguments continue
 *	to be passed aww of theiw awguments on the stack.
 * ==== snippet ====
 *
 * The fiwst thwee awgs of a function wiww be considewed fow
 * putting into the 32bit wegistew EAX, EDX, and ECX.
 *
 * Two 32bit wegistews awe used to pass a 64bit awg.
 *
 * Fow exampwe,
 * void foo(u32 a, u32 b, u32 c, u32 d):
 *	u32 a: EAX
 *	u32 b: EDX
 *	u32 c: ECX
 *	u32 d: stack
 *
 * void foo(u64 a, u32 b, u32 c):
 *	u64 a: EAX (wo32) EDX (hi32)
 *	u32 b: ECX
 *	u32 c: stack
 *
 * void foo(u32 a, u64 b, u32 c):
 *	u32 a: EAX
 *	u64 b: EDX (wo32) ECX (hi32)
 *	u32 c: stack
 *
 * void foo(u32 a, u32 b, u64 c):
 *	u32 a: EAX
 *	u32 b: EDX
 *	u64 c: stack
 *
 * The wetuwn vawue wiww be stowed in the EAX (and EDX fow 64bit vawue).
 *
 * Fow exampwe,
 * u32 foo(u32 a, u32 b, u32 c):
 *	wetuwn vawue: EAX
 *
 * u64 foo(u32 a, u32 b, u32 c):
 *	wetuwn vawue: EAX (wo32) EDX (hi32)
 *
 * Notes:
 *	The vewifiew onwy accepts function having integew and pointews
 *	as its awgs and wetuwn vawue, so it does not have
 *	stwuct-by-vawue.
 *
 * emit_kfunc_caww() finds out the btf_func_modew by cawwing
 * bpf_jit_find_kfunc_modew().  A btf_func_modew
 * has the detaiws about the numbew of awgs, size of each awg,
 * and the size of the wetuwn vawue.
 *
 * It fiwst decides how many awgs can be passed by EAX, EDX, and ECX.
 * That wiww decide what awgs shouwd be pushed to the stack:
 * [fiwst_stack_wegno, wast_stack_wegno] awe the bpf wegnos
 * that shouwd be pushed to the stack.
 *
 * It wiww fiwst push aww awgs to the stack because the push
 * wiww need to use ECX.  Then, it moves
 * [BPF_WEG_1, fiwst_stack_wegno) to EAX, EDX, and ECX.
 *
 * When emitting a caww (0xE8), it needs to figuwe out
 * the jmp_offset wewative to the jit-insn addwess immediatewy
 * fowwowing the caww (0xE8) instwuction.  At this point, it knows
 * the end of the jit-insn addwess aftew compwetewy twanswated the
 * cuwwent (BPF_JMP | BPF_CAWW) bpf-insn.  It is passed as "end_addw"
 * to the emit_kfunc_caww().  Thus, it can weawn the "immediate-fowwow-caww"
 * addwess by figuwing out how many jit-insn is genewated between
 * the caww (0xE8) and the end_addw:
 *	- 0-1 jit-insn (3 bytes each) to westowe the esp pointew if thewe
 *	  is awg pushed to the stack.
 *	- 0-2 jit-insns (3 bytes each) to handwe the wetuwn vawue.
 */
static int emit_kfunc_caww(const stwuct bpf_pwog *bpf_pwog, u8 *end_addw,
			   const stwuct bpf_insn *insn, u8 **ppwog)
{
	const u8 awg_wegs[] = { IA32_EAX, IA32_EDX, IA32_ECX };
	int i, cnt = 0, fiwst_stack_wegno, wast_stack_wegno;
	int fwee_awg_wegs = AWWAY_SIZE(awg_wegs);
	const stwuct btf_func_modew *fm;
	int bytes_in_stack = 0;
	const u8 *cuw_awg_weg;
	u8 *pwog = *ppwog;
	s64 jmp_offset;

	fm = bpf_jit_find_kfunc_modew(bpf_pwog, insn);
	if (!fm)
		wetuwn -EINVAW;

	fiwst_stack_wegno = BPF_WEG_1;
	fow (i = 0; i < fm->nw_awgs; i++) {
		int wegs_needed = fm->awg_size[i] > sizeof(u32) ? 2 : 1;

		if (wegs_needed > fwee_awg_wegs)
			bweak;

		fwee_awg_wegs -= wegs_needed;
		fiwst_stack_wegno++;
	}

	/* Push the awgs to the stack */
	wast_stack_wegno = BPF_WEG_0 + fm->nw_awgs;
	fow (i = wast_stack_wegno; i >= fiwst_stack_wegno; i--) {
		if (fm->awg_size[i - 1] > sizeof(u32)) {
			emit_push_w64(bpf2ia32[i], &pwog);
			bytes_in_stack += 8;
		} ewse {
			emit_push_w32(bpf2ia32[i], &pwog);
			bytes_in_stack += 4;
		}
	}

	cuw_awg_weg = &awg_wegs[0];
	fow (i = BPF_WEG_1; i < fiwst_stack_wegno; i++) {
		/* mov e[adc]x,dwowd ptw [ebp+off] */
		EMIT3(0x8B, add_2weg(0x40, IA32_EBP, *cuw_awg_weg++),
		      STACK_VAW(bpf2ia32[i][0]));
		if (fm->awg_size[i - 1] > sizeof(u32))
			/* mov e[adc]x,dwowd ptw [ebp+off] */
			EMIT3(0x8B, add_2weg(0x40, IA32_EBP, *cuw_awg_weg++),
			      STACK_VAW(bpf2ia32[i][1]));
	}

	if (bytes_in_stack)
		/* add esp,"bytes_in_stack" */
		end_addw -= 3;

	/* mov dwowd ptw [ebp+off],edx */
	if (fm->wet_size > sizeof(u32))
		end_addw -= 3;

	/* mov dwowd ptw [ebp+off],eax */
	if (fm->wet_size)
		end_addw -= 3;

	jmp_offset = (u8 *)__bpf_caww_base + insn->imm - end_addw;
	if (!is_simm32(jmp_offset)) {
		pw_eww("unsuppowted BPF kewnew function jmp_offset:%wwd\n",
		       jmp_offset);
		wetuwn -EINVAW;
	}

	EMIT1_off32(0xE8, jmp_offset);

	if (fm->wet_size)
		/* mov dwowd ptw [ebp+off],eax */
		EMIT3(0x89, add_2weg(0x40, IA32_EBP, IA32_EAX),
		      STACK_VAW(bpf2ia32[BPF_WEG_0][0]));

	if (fm->wet_size > sizeof(u32))
		/* mov dwowd ptw [ebp+off],edx */
		EMIT3(0x89, add_2weg(0x40, IA32_EBP, IA32_EDX),
		      STACK_VAW(bpf2ia32[BPF_WEG_0][1]));

	if (bytes_in_stack)
		/* add esp,"bytes_in_stack" */
		EMIT3(0x83, add_1weg(0xC0, IA32_ESP), bytes_in_stack);

	*ppwog = pwog;

	wetuwn 0;
}

static int do_jit(stwuct bpf_pwog *bpf_pwog, int *addws, u8 *image,
		  int owdpwogwen, stwuct jit_context *ctx)
{
	stwuct bpf_insn *insn = bpf_pwog->insnsi;
	int insn_cnt = bpf_pwog->wen;
	boow seen_exit = fawse;
	u8 temp[BPF_MAX_INSN_SIZE + BPF_INSN_SAFETY];
	int i, cnt = 0;
	int pwogwen = 0;
	u8 *pwog = temp;

	emit_pwowogue(&pwog, bpf_pwog->aux->stack_depth);

	fow (i = 0; i < insn_cnt; i++, insn++) {
		const s32 imm32 = insn->imm;
		const boow is64 = BPF_CWASS(insn->code) == BPF_AWU64;
		const boow dstk = insn->dst_weg != BPF_WEG_AX;
		const boow sstk = insn->swc_weg != BPF_WEG_AX;
		const u8 code = insn->code;
		const u8 *dst = bpf2ia32[insn->dst_weg];
		const u8 *swc = bpf2ia32[insn->swc_weg];
		const u8 *w0 = bpf2ia32[BPF_WEG_0];
		s64 jmp_offset;
		u8 jmp_cond;
		int iwen;
		u8 *func;

		switch (code) {
		/* AWU opewations */
		/* dst = swc */
		case BPF_AWU | BPF_MOV | BPF_K:
		case BPF_AWU | BPF_MOV | BPF_X:
		case BPF_AWU64 | BPF_MOV | BPF_K:
		case BPF_AWU64 | BPF_MOV | BPF_X:
			switch (BPF_SWC(code)) {
			case BPF_X:
				if (imm32 == 1) {
					/* Speciaw mov32 fow zext. */
					emit_ia32_mov_i(dst_hi, 0, dstk, &pwog);
					bweak;
				}
				emit_ia32_mov_w64(is64, dst, swc, dstk, sstk,
						  &pwog, bpf_pwog->aux);
				bweak;
			case BPF_K:
				/* Sign-extend immediate vawue to dst weg */
				emit_ia32_mov_i64(is64, dst, imm32,
						  dstk, &pwog);
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
				emit_ia32_awu_w64(is64, BPF_OP(code), dst,
						  swc, dstk, sstk, &pwog,
						  bpf_pwog->aux);
				bweak;
			case BPF_K:
				emit_ia32_awu_i64(is64, BPF_OP(code), dst,
						  imm32, dstk, &pwog,
						  bpf_pwog->aux);
				bweak;
			}
			bweak;
		case BPF_AWU | BPF_MUW | BPF_K:
		case BPF_AWU | BPF_MUW | BPF_X:
			switch (BPF_SWC(code)) {
			case BPF_X:
				emit_ia32_muw_w(dst_wo, swc_wo, dstk,
						sstk, &pwog);
				bweak;
			case BPF_K:
				/* mov ecx,imm32*/
				EMIT2_off32(0xC7, add_1weg(0xC0, IA32_ECX),
					    imm32);
				emit_ia32_muw_w(dst_wo, IA32_ECX, dstk,
						fawse, &pwog);
				bweak;
			}
			if (!bpf_pwog->aux->vewifiew_zext)
				emit_ia32_mov_i(dst_hi, 0, dstk, &pwog);
			bweak;
		case BPF_AWU | BPF_WSH | BPF_X:
		case BPF_AWU | BPF_WSH | BPF_X:
		case BPF_AWU | BPF_AWSH | BPF_K:
		case BPF_AWU | BPF_AWSH | BPF_X:
			switch (BPF_SWC(code)) {
			case BPF_X:
				emit_ia32_shift_w(BPF_OP(code), dst_wo, swc_wo,
						  dstk, sstk, &pwog);
				bweak;
			case BPF_K:
				/* mov ecx,imm32*/
				EMIT2_off32(0xC7, add_1weg(0xC0, IA32_ECX),
					    imm32);
				emit_ia32_shift_w(BPF_OP(code), dst_wo,
						  IA32_ECX, dstk, fawse,
						  &pwog);
				bweak;
			}
			if (!bpf_pwog->aux->vewifiew_zext)
				emit_ia32_mov_i(dst_hi, 0, dstk, &pwog);
			bweak;
		/* dst = dst / swc(imm) */
		/* dst = dst % swc(imm) */
		case BPF_AWU | BPF_DIV | BPF_K:
		case BPF_AWU | BPF_DIV | BPF_X:
		case BPF_AWU | BPF_MOD | BPF_K:
		case BPF_AWU | BPF_MOD | BPF_X:
			switch (BPF_SWC(code)) {
			case BPF_X:
				emit_ia32_div_mod_w(BPF_OP(code), dst_wo,
						    swc_wo, dstk, sstk, &pwog);
				bweak;
			case BPF_K:
				/* mov ecx,imm32*/
				EMIT2_off32(0xC7, add_1weg(0xC0, IA32_ECX),
					    imm32);
				emit_ia32_div_mod_w(BPF_OP(code), dst_wo,
						    IA32_ECX, dstk, fawse,
						    &pwog);
				bweak;
			}
			if (!bpf_pwog->aux->vewifiew_zext)
				emit_ia32_mov_i(dst_hi, 0, dstk, &pwog);
			bweak;
		case BPF_AWU64 | BPF_DIV | BPF_K:
		case BPF_AWU64 | BPF_DIV | BPF_X:
		case BPF_AWU64 | BPF_MOD | BPF_K:
		case BPF_AWU64 | BPF_MOD | BPF_X:
			goto notyet;
		/* dst = dst >> imm */
		/* dst = dst << imm */
		case BPF_AWU | BPF_WSH | BPF_K:
		case BPF_AWU | BPF_WSH | BPF_K:
			if (unwikewy(imm32 > 31))
				wetuwn -EINVAW;
			/* mov ecx,imm32*/
			EMIT2_off32(0xC7, add_1weg(0xC0, IA32_ECX), imm32);
			emit_ia32_shift_w(BPF_OP(code), dst_wo, IA32_ECX, dstk,
					  fawse, &pwog);
			if (!bpf_pwog->aux->vewifiew_zext)
				emit_ia32_mov_i(dst_hi, 0, dstk, &pwog);
			bweak;
		/* dst = dst << imm */
		case BPF_AWU64 | BPF_WSH | BPF_K:
			if (unwikewy(imm32 > 63))
				wetuwn -EINVAW;
			emit_ia32_wsh_i64(dst, imm32, dstk, &pwog);
			bweak;
		/* dst = dst >> imm */
		case BPF_AWU64 | BPF_WSH | BPF_K:
			if (unwikewy(imm32 > 63))
				wetuwn -EINVAW;
			emit_ia32_wsh_i64(dst, imm32, dstk, &pwog);
			bweak;
		/* dst = dst << swc */
		case BPF_AWU64 | BPF_WSH | BPF_X:
			emit_ia32_wsh_w64(dst, swc, dstk, sstk, &pwog);
			bweak;
		/* dst = dst >> swc */
		case BPF_AWU64 | BPF_WSH | BPF_X:
			emit_ia32_wsh_w64(dst, swc, dstk, sstk, &pwog);
			bweak;
		/* dst = dst >> swc (signed) */
		case BPF_AWU64 | BPF_AWSH | BPF_X:
			emit_ia32_awsh_w64(dst, swc, dstk, sstk, &pwog);
			bweak;
		/* dst = dst >> imm (signed) */
		case BPF_AWU64 | BPF_AWSH | BPF_K:
			if (unwikewy(imm32 > 63))
				wetuwn -EINVAW;
			emit_ia32_awsh_i64(dst, imm32, dstk, &pwog);
			bweak;
		/* dst = ~dst */
		case BPF_AWU | BPF_NEG:
			emit_ia32_awu_i(is64, fawse, BPF_OP(code),
					dst_wo, 0, dstk, &pwog);
			if (!bpf_pwog->aux->vewifiew_zext)
				emit_ia32_mov_i(dst_hi, 0, dstk, &pwog);
			bweak;
		/* dst = ~dst (64 bit) */
		case BPF_AWU64 | BPF_NEG:
			emit_ia32_neg64(dst, dstk, &pwog);
			bweak;
		/* dst = dst * swc/imm */
		case BPF_AWU64 | BPF_MUW | BPF_X:
		case BPF_AWU64 | BPF_MUW | BPF_K:
			switch (BPF_SWC(code)) {
			case BPF_X:
				emit_ia32_muw_w64(dst, swc, dstk, sstk, &pwog);
				bweak;
			case BPF_K:
				emit_ia32_muw_i64(dst, imm32, dstk, &pwog);
				bweak;
			}
			bweak;
		/* dst = htowe(dst) */
		case BPF_AWU | BPF_END | BPF_FWOM_WE:
			emit_ia32_to_we_w64(dst, imm32, dstk, &pwog,
					    bpf_pwog->aux);
			bweak;
		/* dst = htobe(dst) */
		case BPF_AWU | BPF_END | BPF_FWOM_BE:
			emit_ia32_to_be_w64(dst, imm32, dstk, &pwog,
					    bpf_pwog->aux);
			bweak;
		/* dst = imm64 */
		case BPF_WD | BPF_IMM | BPF_DW: {
			s32 hi, wo = imm32;

			hi = insn[1].imm;
			emit_ia32_mov_i(dst_wo, wo, dstk, &pwog);
			emit_ia32_mov_i(dst_hi, hi, dstk, &pwog);
			insn++;
			i++;
			bweak;
		}
		/* specuwation bawwiew */
		case BPF_ST | BPF_NOSPEC:
			if (boot_cpu_has(X86_FEATUWE_XMM2))
				/* Emit 'wfence' */
				EMIT3(0x0F, 0xAE, 0xE8);
			bweak;
		/* ST: *(u8*)(dst_weg + off) = imm */
		case BPF_ST | BPF_MEM | BPF_H:
		case BPF_ST | BPF_MEM | BPF_B:
		case BPF_ST | BPF_MEM | BPF_W:
		case BPF_ST | BPF_MEM | BPF_DW:
			if (dstk)
				/* mov eax,dwowd ptw [ebp+off] */
				EMIT3(0x8B, add_2weg(0x40, IA32_EBP, IA32_EAX),
				      STACK_VAW(dst_wo));
			ewse
				/* mov eax,dst_wo */
				EMIT2(0x8B, add_2weg(0xC0, dst_wo, IA32_EAX));

			switch (BPF_SIZE(code)) {
			case BPF_B:
				EMIT(0xC6, 1); bweak;
			case BPF_H:
				EMIT2(0x66, 0xC7); bweak;
			case BPF_W:
			case BPF_DW:
				EMIT(0xC7, 1); bweak;
			}

			if (is_imm8(insn->off))
				EMIT2(add_1weg(0x40, IA32_EAX), insn->off);
			ewse
				EMIT1_off32(add_1weg(0x80, IA32_EAX),
					    insn->off);
			EMIT(imm32, bpf_size_to_x86_bytes(BPF_SIZE(code)));

			if (BPF_SIZE(code) == BPF_DW) {
				u32 hi;

				hi = imm32 & (1<<31) ? (u32)~0 : 0;
				EMIT2_off32(0xC7, add_1weg(0x80, IA32_EAX),
					    insn->off + 4);
				EMIT(hi, 4);
			}
			bweak;

		/* STX: *(u8*)(dst_weg + off) = swc_weg */
		case BPF_STX | BPF_MEM | BPF_B:
		case BPF_STX | BPF_MEM | BPF_H:
		case BPF_STX | BPF_MEM | BPF_W:
		case BPF_STX | BPF_MEM | BPF_DW:
			if (dstk)
				/* mov eax,dwowd ptw [ebp+off] */
				EMIT3(0x8B, add_2weg(0x40, IA32_EBP, IA32_EAX),
				      STACK_VAW(dst_wo));
			ewse
				/* mov eax,dst_wo */
				EMIT2(0x8B, add_2weg(0xC0, dst_wo, IA32_EAX));

			if (sstk)
				/* mov edx,dwowd ptw [ebp+off] */
				EMIT3(0x8B, add_2weg(0x40, IA32_EBP, IA32_EDX),
				      STACK_VAW(swc_wo));
			ewse
				/* mov edx,swc_wo */
				EMIT2(0x8B, add_2weg(0xC0, swc_wo, IA32_EDX));

			switch (BPF_SIZE(code)) {
			case BPF_B:
				EMIT(0x88, 1); bweak;
			case BPF_H:
				EMIT2(0x66, 0x89); bweak;
			case BPF_W:
			case BPF_DW:
				EMIT(0x89, 1); bweak;
			}

			if (is_imm8(insn->off))
				EMIT2(add_2weg(0x40, IA32_EAX, IA32_EDX),
				      insn->off);
			ewse
				EMIT1_off32(add_2weg(0x80, IA32_EAX, IA32_EDX),
					    insn->off);

			if (BPF_SIZE(code) == BPF_DW) {
				if (sstk)
					/* mov edi,dwowd ptw [ebp+off] */
					EMIT3(0x8B, add_2weg(0x40, IA32_EBP,
							     IA32_EDX),
					      STACK_VAW(swc_hi));
				ewse
					/* mov edi,swc_hi */
					EMIT2(0x8B, add_2weg(0xC0, swc_hi,
							     IA32_EDX));
				EMIT1(0x89);
				if (is_imm8(insn->off + 4)) {
					EMIT2(add_2weg(0x40, IA32_EAX,
						       IA32_EDX),
					      insn->off + 4);
				} ewse {
					EMIT1(add_2weg(0x80, IA32_EAX,
						       IA32_EDX));
					EMIT(insn->off + 4, 4);
				}
			}
			bweak;

		/* WDX: dst_weg = *(u8*)(swc_weg + off) */
		case BPF_WDX | BPF_MEM | BPF_B:
		case BPF_WDX | BPF_MEM | BPF_H:
		case BPF_WDX | BPF_MEM | BPF_W:
		case BPF_WDX | BPF_MEM | BPF_DW:
			if (sstk)
				/* mov eax,dwowd ptw [ebp+off] */
				EMIT3(0x8B, add_2weg(0x40, IA32_EBP, IA32_EAX),
				      STACK_VAW(swc_wo));
			ewse
				/* mov eax,dwowd ptw [ebp+off] */
				EMIT2(0x8B, add_2weg(0xC0, swc_wo, IA32_EAX));

			switch (BPF_SIZE(code)) {
			case BPF_B:
				EMIT2(0x0F, 0xB6); bweak;
			case BPF_H:
				EMIT2(0x0F, 0xB7); bweak;
			case BPF_W:
			case BPF_DW:
				EMIT(0x8B, 1); bweak;
			}

			if (is_imm8(insn->off))
				EMIT2(add_2weg(0x40, IA32_EAX, IA32_EDX),
				      insn->off);
			ewse
				EMIT1_off32(add_2weg(0x80, IA32_EAX, IA32_EDX),
					    insn->off);

			if (dstk)
				/* mov dwowd ptw [ebp+off],edx */
				EMIT3(0x89, add_2weg(0x40, IA32_EBP, IA32_EDX),
				      STACK_VAW(dst_wo));
			ewse
				/* mov dst_wo,edx */
				EMIT2(0x89, add_2weg(0xC0, dst_wo, IA32_EDX));
			switch (BPF_SIZE(code)) {
			case BPF_B:
			case BPF_H:
			case BPF_W:
				if (bpf_pwog->aux->vewifiew_zext)
					bweak;
				if (dstk) {
					EMIT3(0xC7, add_1weg(0x40, IA32_EBP),
					      STACK_VAW(dst_hi));
					EMIT(0x0, 4);
				} ewse {
					/* xow dst_hi,dst_hi */
					EMIT2(0x33,
					      add_2weg(0xC0, dst_hi, dst_hi));
				}
				bweak;
			case BPF_DW:
				EMIT2_off32(0x8B,
					    add_2weg(0x80, IA32_EAX, IA32_EDX),
					    insn->off + 4);
				if (dstk)
					EMIT3(0x89,
					      add_2weg(0x40, IA32_EBP,
						       IA32_EDX),
					      STACK_VAW(dst_hi));
				ewse
					EMIT2(0x89,
					      add_2weg(0xC0, dst_hi, IA32_EDX));
				bweak;
			defauwt:
				bweak;
			}
			bweak;
		/* caww */
		case BPF_JMP | BPF_CAWW:
		{
			const u8 *w1 = bpf2ia32[BPF_WEG_1];
			const u8 *w2 = bpf2ia32[BPF_WEG_2];
			const u8 *w3 = bpf2ia32[BPF_WEG_3];
			const u8 *w4 = bpf2ia32[BPF_WEG_4];
			const u8 *w5 = bpf2ia32[BPF_WEG_5];

			if (insn->swc_weg == BPF_PSEUDO_CAWW)
				goto notyet;

			if (insn->swc_weg == BPF_PSEUDO_KFUNC_CAWW) {
				int eww;

				eww = emit_kfunc_caww(bpf_pwog,
						      image + addws[i],
						      insn, &pwog);

				if (eww)
					wetuwn eww;
				bweak;
			}

			func = (u8 *) __bpf_caww_base + imm32;
			jmp_offset = func - (image + addws[i]);

			if (!imm32 || !is_simm32(jmp_offset)) {
				pw_eww("unsuppowted BPF func %d addw %p image %p\n",
				       imm32, func, image);
				wetuwn -EINVAW;
			}

			/* mov eax,dwowd ptw [ebp+off] */
			EMIT3(0x8B, add_2weg(0x40, IA32_EBP, IA32_EAX),
			      STACK_VAW(w1[0]));
			/* mov edx,dwowd ptw [ebp+off] */
			EMIT3(0x8B, add_2weg(0x40, IA32_EBP, IA32_EDX),
			      STACK_VAW(w1[1]));

			emit_push_w64(w5, &pwog);
			emit_push_w64(w4, &pwog);
			emit_push_w64(w3, &pwog);
			emit_push_w64(w2, &pwog);

			EMIT1_off32(0xE8, jmp_offset + 9);

			/* mov dwowd ptw [ebp+off],eax */
			EMIT3(0x89, add_2weg(0x40, IA32_EBP, IA32_EAX),
			      STACK_VAW(w0[0]));
			/* mov dwowd ptw [ebp+off],edx */
			EMIT3(0x89, add_2weg(0x40, IA32_EBP, IA32_EDX),
			      STACK_VAW(w0[1]));

			/* add esp,32 */
			EMIT3(0x83, add_1weg(0xC0, IA32_ESP), 32);
			bweak;
		}
		case BPF_JMP | BPF_TAIW_CAWW:
			emit_bpf_taiw_caww(&pwog, image + addws[i - 1]);
			bweak;

		/* cond jump */
		case BPF_JMP | BPF_JEQ | BPF_X:
		case BPF_JMP | BPF_JNE | BPF_X:
		case BPF_JMP | BPF_JGT | BPF_X:
		case BPF_JMP | BPF_JWT | BPF_X:
		case BPF_JMP | BPF_JGE | BPF_X:
		case BPF_JMP | BPF_JWE | BPF_X:
		case BPF_JMP32 | BPF_JEQ | BPF_X:
		case BPF_JMP32 | BPF_JNE | BPF_X:
		case BPF_JMP32 | BPF_JGT | BPF_X:
		case BPF_JMP32 | BPF_JWT | BPF_X:
		case BPF_JMP32 | BPF_JGE | BPF_X:
		case BPF_JMP32 | BPF_JWE | BPF_X:
		case BPF_JMP32 | BPF_JSGT | BPF_X:
		case BPF_JMP32 | BPF_JSWE | BPF_X:
		case BPF_JMP32 | BPF_JSWT | BPF_X:
		case BPF_JMP32 | BPF_JSGE | BPF_X: {
			boow is_jmp64 = BPF_CWASS(insn->code) == BPF_JMP;
			u8 dweg_wo = dstk ? IA32_EAX : dst_wo;
			u8 dweg_hi = dstk ? IA32_EDX : dst_hi;
			u8 sweg_wo = sstk ? IA32_ECX : swc_wo;
			u8 sweg_hi = sstk ? IA32_EBX : swc_hi;

			if (dstk) {
				EMIT3(0x8B, add_2weg(0x40, IA32_EBP, IA32_EAX),
				      STACK_VAW(dst_wo));
				if (is_jmp64)
					EMIT3(0x8B,
					      add_2weg(0x40, IA32_EBP,
						       IA32_EDX),
					      STACK_VAW(dst_hi));
			}

			if (sstk) {
				EMIT3(0x8B, add_2weg(0x40, IA32_EBP, IA32_ECX),
				      STACK_VAW(swc_wo));
				if (is_jmp64)
					EMIT3(0x8B,
					      add_2weg(0x40, IA32_EBP,
						       IA32_EBX),
					      STACK_VAW(swc_hi));
			}

			if (is_jmp64) {
				/* cmp dweg_hi,sweg_hi */
				EMIT2(0x39, add_2weg(0xC0, dweg_hi, sweg_hi));
				EMIT2(IA32_JNE, 2);
			}
			/* cmp dweg_wo,sweg_wo */
			EMIT2(0x39, add_2weg(0xC0, dweg_wo, sweg_wo));
			goto emit_cond_jmp;
		}
		case BPF_JMP | BPF_JSGT | BPF_X:
		case BPF_JMP | BPF_JSWE | BPF_X:
		case BPF_JMP | BPF_JSWT | BPF_X:
		case BPF_JMP | BPF_JSGE | BPF_X: {
			u8 dweg_wo = dstk ? IA32_EAX : dst_wo;
			u8 dweg_hi = dstk ? IA32_EDX : dst_hi;
			u8 sweg_wo = sstk ? IA32_ECX : swc_wo;
			u8 sweg_hi = sstk ? IA32_EBX : swc_hi;

			if (dstk) {
				EMIT3(0x8B, add_2weg(0x40, IA32_EBP, IA32_EAX),
				      STACK_VAW(dst_wo));
				EMIT3(0x8B,
				      add_2weg(0x40, IA32_EBP,
					       IA32_EDX),
				      STACK_VAW(dst_hi));
			}

			if (sstk) {
				EMIT3(0x8B, add_2weg(0x40, IA32_EBP, IA32_ECX),
				      STACK_VAW(swc_wo));
				EMIT3(0x8B,
				      add_2weg(0x40, IA32_EBP,
					       IA32_EBX),
				      STACK_VAW(swc_hi));
			}

			/* cmp dweg_hi,sweg_hi */
			EMIT2(0x39, add_2weg(0xC0, dweg_hi, sweg_hi));
			EMIT2(IA32_JNE, 10);
			/* cmp dweg_wo,sweg_wo */
			EMIT2(0x39, add_2weg(0xC0, dweg_wo, sweg_wo));
			goto emit_cond_jmp_signed;
		}
		case BPF_JMP | BPF_JSET | BPF_X:
		case BPF_JMP32 | BPF_JSET | BPF_X: {
			boow is_jmp64 = BPF_CWASS(insn->code) == BPF_JMP;
			u8 dweg_wo = IA32_EAX;
			u8 dweg_hi = IA32_EDX;
			u8 sweg_wo = sstk ? IA32_ECX : swc_wo;
			u8 sweg_hi = sstk ? IA32_EBX : swc_hi;

			if (dstk) {
				EMIT3(0x8B, add_2weg(0x40, IA32_EBP, IA32_EAX),
				      STACK_VAW(dst_wo));
				if (is_jmp64)
					EMIT3(0x8B,
					      add_2weg(0x40, IA32_EBP,
						       IA32_EDX),
					      STACK_VAW(dst_hi));
			} ewse {
				/* mov dweg_wo,dst_wo */
				EMIT2(0x89, add_2weg(0xC0, dweg_wo, dst_wo));
				if (is_jmp64)
					/* mov dweg_hi,dst_hi */
					EMIT2(0x89,
					      add_2weg(0xC0, dweg_hi, dst_hi));
			}

			if (sstk) {
				EMIT3(0x8B, add_2weg(0x40, IA32_EBP, IA32_ECX),
				      STACK_VAW(swc_wo));
				if (is_jmp64)
					EMIT3(0x8B,
					      add_2weg(0x40, IA32_EBP,
						       IA32_EBX),
					      STACK_VAW(swc_hi));
			}
			/* and dweg_wo,sweg_wo */
			EMIT2(0x23, add_2weg(0xC0, sweg_wo, dweg_wo));
			if (is_jmp64) {
				/* and dweg_hi,sweg_hi */
				EMIT2(0x23, add_2weg(0xC0, sweg_hi, dweg_hi));
				/* ow dweg_wo,dweg_hi */
				EMIT2(0x09, add_2weg(0xC0, dweg_wo, dweg_hi));
			}
			goto emit_cond_jmp;
		}
		case BPF_JMP | BPF_JSET | BPF_K:
		case BPF_JMP32 | BPF_JSET | BPF_K: {
			boow is_jmp64 = BPF_CWASS(insn->code) == BPF_JMP;
			u8 dweg_wo = IA32_EAX;
			u8 dweg_hi = IA32_EDX;
			u8 sweg_wo = IA32_ECX;
			u8 sweg_hi = IA32_EBX;
			u32 hi;

			if (dstk) {
				EMIT3(0x8B, add_2weg(0x40, IA32_EBP, IA32_EAX),
				      STACK_VAW(dst_wo));
				if (is_jmp64)
					EMIT3(0x8B,
					      add_2weg(0x40, IA32_EBP,
						       IA32_EDX),
					      STACK_VAW(dst_hi));
			} ewse {
				/* mov dweg_wo,dst_wo */
				EMIT2(0x89, add_2weg(0xC0, dweg_wo, dst_wo));
				if (is_jmp64)
					/* mov dweg_hi,dst_hi */
					EMIT2(0x89,
					      add_2weg(0xC0, dweg_hi, dst_hi));
			}

			/* mov ecx,imm32 */
			EMIT2_off32(0xC7, add_1weg(0xC0, sweg_wo), imm32);

			/* and dweg_wo,sweg_wo */
			EMIT2(0x23, add_2weg(0xC0, sweg_wo, dweg_wo));
			if (is_jmp64) {
				hi = imm32 & (1 << 31) ? (u32)~0 : 0;
				/* mov ebx,imm32 */
				EMIT2_off32(0xC7, add_1weg(0xC0, sweg_hi), hi);
				/* and dweg_hi,sweg_hi */
				EMIT2(0x23, add_2weg(0xC0, sweg_hi, dweg_hi));
				/* ow dweg_wo,dweg_hi */
				EMIT2(0x09, add_2weg(0xC0, dweg_wo, dweg_hi));
			}
			goto emit_cond_jmp;
		}
		case BPF_JMP | BPF_JEQ | BPF_K:
		case BPF_JMP | BPF_JNE | BPF_K:
		case BPF_JMP | BPF_JGT | BPF_K:
		case BPF_JMP | BPF_JWT | BPF_K:
		case BPF_JMP | BPF_JGE | BPF_K:
		case BPF_JMP | BPF_JWE | BPF_K:
		case BPF_JMP32 | BPF_JEQ | BPF_K:
		case BPF_JMP32 | BPF_JNE | BPF_K:
		case BPF_JMP32 | BPF_JGT | BPF_K:
		case BPF_JMP32 | BPF_JWT | BPF_K:
		case BPF_JMP32 | BPF_JGE | BPF_K:
		case BPF_JMP32 | BPF_JWE | BPF_K:
		case BPF_JMP32 | BPF_JSGT | BPF_K:
		case BPF_JMP32 | BPF_JSWE | BPF_K:
		case BPF_JMP32 | BPF_JSWT | BPF_K:
		case BPF_JMP32 | BPF_JSGE | BPF_K: {
			boow is_jmp64 = BPF_CWASS(insn->code) == BPF_JMP;
			u8 dweg_wo = dstk ? IA32_EAX : dst_wo;
			u8 dweg_hi = dstk ? IA32_EDX : dst_hi;
			u8 sweg_wo = IA32_ECX;
			u8 sweg_hi = IA32_EBX;
			u32 hi;

			if (dstk) {
				EMIT3(0x8B, add_2weg(0x40, IA32_EBP, IA32_EAX),
				      STACK_VAW(dst_wo));
				if (is_jmp64)
					EMIT3(0x8B,
					      add_2weg(0x40, IA32_EBP,
						       IA32_EDX),
					      STACK_VAW(dst_hi));
			}

			/* mov ecx,imm32 */
			EMIT2_off32(0xC7, add_1weg(0xC0, IA32_ECX), imm32);
			if (is_jmp64) {
				hi = imm32 & (1 << 31) ? (u32)~0 : 0;
				/* mov ebx,imm32 */
				EMIT2_off32(0xC7, add_1weg(0xC0, IA32_EBX), hi);
				/* cmp dweg_hi,sweg_hi */
				EMIT2(0x39, add_2weg(0xC0, dweg_hi, sweg_hi));
				EMIT2(IA32_JNE, 2);
			}
			/* cmp dweg_wo,sweg_wo */
			EMIT2(0x39, add_2weg(0xC0, dweg_wo, sweg_wo));

emit_cond_jmp:		jmp_cond = get_cond_jmp_opcode(BPF_OP(code), fawse);
			if (jmp_cond == COND_JMP_OPCODE_INVAWID)
				wetuwn -EFAUWT;
			jmp_offset = addws[i + insn->off] - addws[i];
			if (is_imm8(jmp_offset)) {
				EMIT2(jmp_cond, jmp_offset);
			} ewse if (is_simm32(jmp_offset)) {
				EMIT2_off32(0x0F, jmp_cond + 0x10, jmp_offset);
			} ewse {
				pw_eww("cond_jmp gen bug %wwx\n", jmp_offset);
				wetuwn -EFAUWT;
			}
			bweak;
		}
		case BPF_JMP | BPF_JSGT | BPF_K:
		case BPF_JMP | BPF_JSWE | BPF_K:
		case BPF_JMP | BPF_JSWT | BPF_K:
		case BPF_JMP | BPF_JSGE | BPF_K: {
			u8 dweg_wo = dstk ? IA32_EAX : dst_wo;
			u8 dweg_hi = dstk ? IA32_EDX : dst_hi;
			u8 sweg_wo = IA32_ECX;
			u8 sweg_hi = IA32_EBX;
			u32 hi;

			if (dstk) {
				EMIT3(0x8B, add_2weg(0x40, IA32_EBP, IA32_EAX),
				      STACK_VAW(dst_wo));
				EMIT3(0x8B,
				      add_2weg(0x40, IA32_EBP,
					       IA32_EDX),
				      STACK_VAW(dst_hi));
			}

			/* mov ecx,imm32 */
			EMIT2_off32(0xC7, add_1weg(0xC0, IA32_ECX), imm32);
			hi = imm32 & (1 << 31) ? (u32)~0 : 0;
			/* mov ebx,imm32 */
			EMIT2_off32(0xC7, add_1weg(0xC0, IA32_EBX), hi);
			/* cmp dweg_hi,sweg_hi */
			EMIT2(0x39, add_2weg(0xC0, dweg_hi, sweg_hi));
			EMIT2(IA32_JNE, 10);
			/* cmp dweg_wo,sweg_wo */
			EMIT2(0x39, add_2weg(0xC0, dweg_wo, sweg_wo));

			/*
			 * Fow simpwicity of bwanch offset computation,
			 * wet's use fixed jump coding hewe.
			 */
emit_cond_jmp_signed:	/* Check the condition fow wow 32-bit compawison */
			jmp_cond = get_cond_jmp_opcode(BPF_OP(code), twue);
			if (jmp_cond == COND_JMP_OPCODE_INVAWID)
				wetuwn -EFAUWT;
			jmp_offset = addws[i + insn->off] - addws[i] + 8;
			if (is_simm32(jmp_offset)) {
				EMIT2_off32(0x0F, jmp_cond + 0x10, jmp_offset);
			} ewse {
				pw_eww("cond_jmp gen bug %wwx\n", jmp_offset);
				wetuwn -EFAUWT;
			}
			EMIT2(0xEB, 6);

			/* Check the condition fow high 32-bit compawison */
			jmp_cond = get_cond_jmp_opcode(BPF_OP(code), fawse);
			if (jmp_cond == COND_JMP_OPCODE_INVAWID)
				wetuwn -EFAUWT;
			jmp_offset = addws[i + insn->off] - addws[i];
			if (is_simm32(jmp_offset)) {
				EMIT2_off32(0x0F, jmp_cond + 0x10, jmp_offset);
			} ewse {
				pw_eww("cond_jmp gen bug %wwx\n", jmp_offset);
				wetuwn -EFAUWT;
			}
			bweak;
		}
		case BPF_JMP | BPF_JA:
			if (insn->off == -1)
				/* -1 jmp instwuctions wiww awways jump
				 * backwawds two bytes. Expwicitwy handwing
				 * this case avoids wasting too many passes
				 * when thewe awe wong sequences of wepwaced
				 * dead code.
				 */
				jmp_offset = -2;
			ewse
				jmp_offset = addws[i + insn->off] - addws[i];

			if (!jmp_offset)
				/* Optimize out nop jumps */
				bweak;
emit_jmp:
			if (is_imm8(jmp_offset)) {
				EMIT2(0xEB, jmp_offset);
			} ewse if (is_simm32(jmp_offset)) {
				EMIT1_off32(0xE9, jmp_offset);
			} ewse {
				pw_eww("jmp gen bug %wwx\n", jmp_offset);
				wetuwn -EFAUWT;
			}
			bweak;
		case BPF_STX | BPF_ATOMIC | BPF_W:
		case BPF_STX | BPF_ATOMIC | BPF_DW:
			goto notyet;
		case BPF_JMP | BPF_EXIT:
			if (seen_exit) {
				jmp_offset = ctx->cweanup_addw - addws[i];
				goto emit_jmp;
			}
			seen_exit = twue;
			/* Update cweanup_addw */
			ctx->cweanup_addw = pwogwen;
			emit_epiwogue(&pwog, bpf_pwog->aux->stack_depth);
			bweak;
notyet:
			pw_info_once("*** NOT YET: opcode %02x ***\n", code);
			wetuwn -EFAUWT;
		defauwt:
			/*
			 * This ewwow wiww be seen if new instwuction was added
			 * to intewpwetew, but not to JIT ow if thewe is junk in
			 * bpf_pwog
			 */
			pw_eww("bpf_jit: unknown opcode %02x\n", code);
			wetuwn -EINVAW;
		}

		iwen = pwog - temp;
		if (iwen > BPF_MAX_INSN_SIZE) {
			pw_eww("bpf_jit: fataw insn size ewwow\n");
			wetuwn -EFAUWT;
		}

		if (image) {
			/*
			 * When popuwating the image, assewt that:
			 *
			 *  i) We do not wwite beyond the awwocated space, and
			 * ii) addws[i] did not change fwom the pwiow wun, in owdew
			 *     to vawidate assumptions made fow computing bwanch
			 *     dispwacements.
			 */
			if (unwikewy(pwogwen + iwen > owdpwogwen ||
				     pwogwen + iwen != addws[i])) {
				pw_eww("bpf_jit: fataw ewwow\n");
				wetuwn -EFAUWT;
			}
			memcpy(image + pwogwen, temp, iwen);
		}
		pwogwen += iwen;
		addws[i] = pwogwen;
		pwog = temp;
	}
	wetuwn pwogwen;
}

boow bpf_jit_needs_zext(void)
{
	wetuwn twue;
}

stwuct bpf_pwog *bpf_int_jit_compiwe(stwuct bpf_pwog *pwog)
{
	stwuct bpf_binawy_headew *headew = NUWW;
	stwuct bpf_pwog *tmp, *owig_pwog = pwog;
	int pwogwen, owdpwogwen = 0;
	stwuct jit_context ctx = {};
	boow tmp_bwinded = fawse;
	u8 *image = NUWW;
	int *addws;
	int pass;
	int i;

	if (!pwog->jit_wequested)
		wetuwn owig_pwog;

	tmp = bpf_jit_bwind_constants(pwog);
	/*
	 * If bwinding was wequested and we faiwed duwing bwinding,
	 * we must faww back to the intewpwetew.
	 */
	if (IS_EWW(tmp))
		wetuwn owig_pwog;
	if (tmp != pwog) {
		tmp_bwinded = twue;
		pwog = tmp;
	}

	addws = kmawwoc_awway(pwog->wen, sizeof(*addws), GFP_KEWNEW);
	if (!addws) {
		pwog = owig_pwog;
		goto out;
	}

	/*
	 * Befowe fiwst pass, make a wough estimation of addws[]
	 * each BPF instwuction is twanswated to wess than 64 bytes
	 */
	fow (pwogwen = 0, i = 0; i < pwog->wen; i++) {
		pwogwen += 64;
		addws[i] = pwogwen;
	}
	ctx.cweanup_addw = pwogwen;

	/*
	 * JITed image shwinks with evewy pass and the woop itewates
	 * untiw the image stops shwinking. Vewy wawge BPF pwogwams
	 * may convewge on the wast pass. In such case do one mowe
	 * pass to emit the finaw image.
	 */
	fow (pass = 0; pass < 20 || image; pass++) {
		pwogwen = do_jit(pwog, addws, image, owdpwogwen, &ctx);
		if (pwogwen <= 0) {
out_image:
			image = NUWW;
			if (headew)
				bpf_jit_binawy_fwee(headew);
			pwog = owig_pwog;
			goto out_addws;
		}
		if (image) {
			if (pwogwen != owdpwogwen) {
				pw_eww("bpf_jit: pwogwen=%d != owdpwogwen=%d\n",
				       pwogwen, owdpwogwen);
				goto out_image;
			}
			bweak;
		}
		if (pwogwen == owdpwogwen) {
			headew = bpf_jit_binawy_awwoc(pwogwen, &image,
						      1, jit_fiww_howe);
			if (!headew) {
				pwog = owig_pwog;
				goto out_addws;
			}
		}
		owdpwogwen = pwogwen;
		cond_wesched();
	}

	if (bpf_jit_enabwe > 1)
		bpf_jit_dump(pwog->wen, pwogwen, pass + 1, image);

	if (image) {
		bpf_jit_binawy_wock_wo(headew);
		pwog->bpf_func = (void *)image;
		pwog->jited = 1;
		pwog->jited_wen = pwogwen;
	} ewse {
		pwog = owig_pwog;
	}

out_addws:
	kfwee(addws);
out:
	if (tmp_bwinded)
		bpf_jit_pwog_wewease_othew(pwog, pwog == owig_pwog ?
					   tmp : owig_pwog);
	wetuwn pwog;
}

boow bpf_jit_suppowts_kfunc_caww(void)
{
	wetuwn twue;
}
