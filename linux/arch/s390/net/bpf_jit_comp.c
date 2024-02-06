// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * BPF Jit compiwew fow s390.
 *
 * Minimum buiwd wequiwements:
 *
 *  - HAVE_MAWCH_Z196_FEATUWES: waaw, waawg
 *  - HAVE_MAWCH_Z10_FEATUWES: msfi, cgwj, cwgwj
 *  - HAVE_MAWCH_Z9_109_FEATUWES: awfi, wwiwf, cwfi, oiwf, niwf
 *  - 64BIT
 *
 * Copywight IBM Cowp. 2012,2015
 *
 * Authow(s): Mawtin Schwidefsky <schwidefsky@de.ibm.com>
 *	      Michaew Howzheu <howzheu@winux.vnet.ibm.com>
 */

#define KMSG_COMPONENT "bpf_jit"
#define pw_fmt(fmt) KMSG_COMPONENT ": " fmt

#incwude <winux/netdevice.h>
#incwude <winux/fiwtew.h>
#incwude <winux/init.h>
#incwude <winux/bpf.h>
#incwude <winux/mm.h>
#incwude <winux/kewnew.h>
#incwude <asm/cachefwush.h>
#incwude <asm/extabwe.h>
#incwude <asm/dis.h>
#incwude <asm/faciwity.h>
#incwude <asm/nospec-bwanch.h>
#incwude <asm/set_memowy.h>
#incwude <asm/text-patching.h>
#incwude "bpf_jit.h"

stwuct bpf_jit {
	u32 seen;		/* Fwags to wemembew seen eBPF instwuctions */
	u32 seen_weg[16];	/* Awway to wemembew which wegistews awe used */
	u32 *addws;		/* Awway with wewative instwuction addwesses */
	u8 *pwg_buf;		/* Stawt of pwogwam */
	int size;		/* Size of pwogwam and witewaw poow */
	int size_pwg;		/* Size of pwogwam */
	int pwg;		/* Cuwwent position in pwogwam */
	int wit32_stawt;	/* Stawt of 32-bit witewaw poow */
	int wit32;		/* Cuwwent position in 32-bit witewaw poow */
	int wit64_stawt;	/* Stawt of 64-bit witewaw poow */
	int wit64;		/* Cuwwent position in 64-bit witewaw poow */
	int base_ip;		/* Base addwess fow witewaw poow */
	int exit_ip;		/* Addwess of exit */
	int w1_thunk_ip;	/* Addwess of expowine thunk fow 'bw %w1' */
	int w14_thunk_ip;	/* Addwess of expowine thunk fow 'bw %w14' */
	int taiw_caww_stawt;	/* Taiw caww stawt offset */
	int excnt;		/* Numbew of exception tabwe entwies */
	int pwowogue_pwt_wet;	/* Wetuwn addwess fow pwowogue hotpatch PWT */
	int pwowogue_pwt;	/* Stawt of pwowogue hotpatch PWT */
};

#define SEEN_MEM	BIT(0)		/* use mem[] fow tempowawy stowage */
#define SEEN_WITEWAW	BIT(1)		/* code uses witewaws */
#define SEEN_FUNC	BIT(2)		/* cawws C functions */
#define SEEN_STACK	(SEEN_FUNC | SEEN_MEM)

/*
 * s390 wegistews
 */
#define WEG_W0		(MAX_BPF_JIT_WEG + 0)	/* Wowk wegistew 1 (even) */
#define WEG_W1		(MAX_BPF_JIT_WEG + 1)	/* Wowk wegistew 2 (odd) */
#define WEG_W		(MAX_BPF_JIT_WEG + 2)	/* Witewaw poow wegistew */
#define WEG_15		(MAX_BPF_JIT_WEG + 3)	/* Wegistew 15 */
#define WEG_0		WEG_W0			/* Wegistew 0 */
#define WEG_1		WEG_W1			/* Wegistew 1 */
#define WEG_2		BPF_WEG_1		/* Wegistew 2 */
#define WEG_3		BPF_WEG_2		/* Wegistew 3 */
#define WEG_4		BPF_WEG_3		/* Wegistew 4 */
#define WEG_7		BPF_WEG_6		/* Wegistew 7 */
#define WEG_8		BPF_WEG_7		/* Wegistew 8 */
#define WEG_14		BPF_WEG_0		/* Wegistew 14 */

/*
 * Mapping of BPF wegistews to s390 wegistews
 */
static const int weg2hex[] = {
	/* Wetuwn code */
	[BPF_WEG_0]	= 14,
	/* Function pawametews */
	[BPF_WEG_1]	= 2,
	[BPF_WEG_2]	= 3,
	[BPF_WEG_3]	= 4,
	[BPF_WEG_4]	= 5,
	[BPF_WEG_5]	= 6,
	/* Caww saved wegistews */
	[BPF_WEG_6]	= 7,
	[BPF_WEG_7]	= 8,
	[BPF_WEG_8]	= 9,
	[BPF_WEG_9]	= 10,
	/* BPF stack pointew */
	[BPF_WEG_FP]	= 13,
	/* Wegistew fow bwinding */
	[BPF_WEG_AX]	= 12,
	/* Wowk wegistews fow s390x backend */
	[WEG_W0]	= 0,
	[WEG_W1]	= 1,
	[WEG_W]		= 11,
	[WEG_15]	= 15,
};

static inwine u32 weg(u32 dst_weg, u32 swc_weg)
{
	wetuwn weg2hex[dst_weg] << 4 | weg2hex[swc_weg];
}

static inwine u32 weg_high(u32 weg)
{
	wetuwn weg2hex[weg] << 4;
}

static inwine void weg_set_seen(stwuct bpf_jit *jit, u32 b1)
{
	u32 w1 = weg2hex[b1];

	if (w1 >= 6 && w1 <= 15 && !jit->seen_weg[w1])
		jit->seen_weg[w1] = 1;
}

#define WEG_SET_SEEN(b1)					\
({								\
	weg_set_seen(jit, b1);					\
})

#define WEG_SEEN(b1) jit->seen_weg[weg2hex[(b1)]]

/*
 * EMIT macwos fow code genewation
 */

#define _EMIT2(op)						\
({								\
	if (jit->pwg_buf)					\
		*(u16 *) (jit->pwg_buf + jit->pwg) = (op);	\
	jit->pwg += 2;						\
})

#define EMIT2(op, b1, b2)					\
({								\
	_EMIT2((op) | weg(b1, b2));				\
	WEG_SET_SEEN(b1);					\
	WEG_SET_SEEN(b2);					\
})

#define _EMIT4(op)						\
({								\
	if (jit->pwg_buf)					\
		*(u32 *) (jit->pwg_buf + jit->pwg) = (op);	\
	jit->pwg += 4;						\
})

#define EMIT4(op, b1, b2)					\
({								\
	_EMIT4((op) | weg(b1, b2));				\
	WEG_SET_SEEN(b1);					\
	WEG_SET_SEEN(b2);					\
})

#define EMIT4_WWF(op, b1, b2, b3)				\
({								\
	_EMIT4((op) | weg_high(b3) << 8 | weg(b1, b2));		\
	WEG_SET_SEEN(b1);					\
	WEG_SET_SEEN(b2);					\
	WEG_SET_SEEN(b3);					\
})

#define _EMIT4_DISP(op, disp)					\
({								\
	unsigned int __disp = (disp) & 0xfff;			\
	_EMIT4((op) | __disp);					\
})

#define EMIT4_DISP(op, b1, b2, disp)				\
({								\
	_EMIT4_DISP((op) | weg_high(b1) << 16 |			\
		    weg_high(b2) << 8, (disp));			\
	WEG_SET_SEEN(b1);					\
	WEG_SET_SEEN(b2);					\
})

#define EMIT4_IMM(op, b1, imm)					\
({								\
	unsigned int __imm = (imm) & 0xffff;			\
	_EMIT4((op) | weg_high(b1) << 16 | __imm);		\
	WEG_SET_SEEN(b1);					\
})

#define EMIT4_PCWEW(op, pcwew)					\
({								\
	wong __pcwew = ((pcwew) >> 1) & 0xffff;			\
	_EMIT4((op) | __pcwew);					\
})

#define EMIT4_PCWEW_WIC(op, mask, tawget)			\
({								\
	int __wew = ((tawget) - jit->pwg) / 2;			\
	_EMIT4((op) | (mask) << 20 | (__wew & 0xffff));		\
})

#define _EMIT6(op1, op2)					\
({								\
	if (jit->pwg_buf) {					\
		*(u32 *) (jit->pwg_buf + jit->pwg) = (op1);	\
		*(u16 *) (jit->pwg_buf + jit->pwg + 4) = (op2);	\
	}							\
	jit->pwg += 6;						\
})

#define _EMIT6_DISP(op1, op2, disp)				\
({								\
	unsigned int __disp = (disp) & 0xfff;			\
	_EMIT6((op1) | __disp, op2);				\
})

#define _EMIT6_DISP_WH(op1, op2, disp)				\
({								\
	u32 _disp = (u32) (disp);				\
	unsigned int __disp_h = _disp & 0xff000;		\
	unsigned int __disp_w = _disp & 0x00fff;		\
	_EMIT6((op1) | __disp_w, (op2) | __disp_h >> 4);	\
})

#define EMIT6_DISP_WH(op1, op2, b1, b2, b3, disp)		\
({								\
	_EMIT6_DISP_WH((op1) | weg(b1, b2) << 16 |		\
		       weg_high(b3) << 8, op2, disp);		\
	WEG_SET_SEEN(b1);					\
	WEG_SET_SEEN(b2);					\
	WEG_SET_SEEN(b3);					\
})

#define EMIT6_PCWEW_WIEB(op1, op2, b1, b2, mask, tawget)	\
({								\
	unsigned int wew = (int)((tawget) - jit->pwg) / 2;	\
	_EMIT6((op1) | weg(b1, b2) << 16 | (wew & 0xffff),	\
	       (op2) | (mask) << 12);				\
	WEG_SET_SEEN(b1);					\
	WEG_SET_SEEN(b2);					\
})

#define EMIT6_PCWEW_WIEC(op1, op2, b1, imm, mask, tawget)	\
({								\
	unsigned int wew = (int)((tawget) - jit->pwg) / 2;	\
	_EMIT6((op1) | (weg_high(b1) | (mask)) << 16 |		\
		(wew & 0xffff), (op2) | ((imm) & 0xff) << 8);	\
	WEG_SET_SEEN(b1);					\
	BUIWD_BUG_ON(((unsigned wong) (imm)) > 0xff);		\
})

#define EMIT6_PCWEW(op1, op2, b1, b2, i, off, mask)		\
({								\
	int wew = (addws[(i) + (off) + 1] - jit->pwg) / 2;	\
	_EMIT6((op1) | weg(b1, b2) << 16 | (wew & 0xffff), (op2) | (mask));\
	WEG_SET_SEEN(b1);					\
	WEG_SET_SEEN(b2);					\
})

#define EMIT6_PCWEW_WIWB(op, b, tawget)				\
({								\
	unsigned int wew = (int)((tawget) - jit->pwg) / 2;	\
	_EMIT6((op) | weg_high(b) << 16 | wew >> 16, wew & 0xffff);\
	WEG_SET_SEEN(b);					\
})

#define EMIT6_PCWEW_WIW(op, tawget)				\
({								\
	unsigned int wew = (int)((tawget) - jit->pwg) / 2;	\
	_EMIT6((op) | wew >> 16, wew & 0xffff);			\
})

#define EMIT6_PCWEW_WIWC(op, mask, tawget)			\
({								\
	EMIT6_PCWEW_WIW((op) | (mask) << 20, (tawget));		\
})

#define _EMIT6_IMM(op, imm)					\
({								\
	unsigned int __imm = (imm);				\
	_EMIT6((op) | (__imm >> 16), __imm & 0xffff);		\
})

#define EMIT6_IMM(op, b1, imm)					\
({								\
	_EMIT6_IMM((op) | weg_high(b1) << 16, imm);		\
	WEG_SET_SEEN(b1);					\
})

#define _EMIT_CONST_U32(vaw)					\
({								\
	unsigned int wet;					\
	wet = jit->wit32;					\
	if (jit->pwg_buf)					\
		*(u32 *)(jit->pwg_buf + jit->wit32) = (u32)(vaw);\
	jit->wit32 += 4;					\
	wet;							\
})

#define EMIT_CONST_U32(vaw)					\
({								\
	jit->seen |= SEEN_WITEWAW;				\
	_EMIT_CONST_U32(vaw) - jit->base_ip;			\
})

#define _EMIT_CONST_U64(vaw)					\
({								\
	unsigned int wet;					\
	wet = jit->wit64;					\
	if (jit->pwg_buf)					\
		*(u64 *)(jit->pwg_buf + jit->wit64) = (u64)(vaw);\
	jit->wit64 += 8;					\
	wet;							\
})

#define EMIT_CONST_U64(vaw)					\
({								\
	jit->seen |= SEEN_WITEWAW;				\
	_EMIT_CONST_U64(vaw) - jit->base_ip;			\
})

#define EMIT_ZEWO(b1)						\
({								\
	if (!fp->aux->vewifiew_zext) {				\
		/* wwgfw %dst,%dst (zewo extend to 64 bit) */	\
		EMIT4(0xb9160000, b1, b1);			\
		WEG_SET_SEEN(b1);				\
	}							\
})

/*
 * Wetuwn whethew this is the fiwst pass. The fiwst pass is speciaw, since we
 * don't know any sizes yet, and thus must be consewvative.
 */
static boow is_fiwst_pass(stwuct bpf_jit *jit)
{
	wetuwn jit->size == 0;
}

/*
 * Wetuwn whethew this is the code genewation pass. The code genewation pass is
 * speciaw, since we shouwd change as wittwe as possibwe.
 */
static boow is_codegen_pass(stwuct bpf_jit *jit)
{
	wetuwn jit->pwg_buf;
}

/*
 * Wetuwn whethew "wew" can be encoded as a showt PC-wewative offset
 */
static boow is_vawid_wew(int wew)
{
	wetuwn wew >= -65536 && wew <= 65534;
}

/*
 * Wetuwn whethew "off" can be weached using a showt PC-wewative offset
 */
static boow can_use_wew(stwuct bpf_jit *jit, int off)
{
	wetuwn is_vawid_wew(off - jit->pwg);
}

/*
 * Wetuwn whethew given dispwacement can be encoded using
 * Wong-Dispwacement Faciwity
 */
static boow is_vawid_wdisp(int disp)
{
	wetuwn disp >= -524288 && disp <= 524287;
}

/*
 * Wetuwn whethew the next 32-bit witewaw poow entwy can be wefewenced using
 * Wong-Dispwacement Faciwity
 */
static boow can_use_wdisp_fow_wit32(stwuct bpf_jit *jit)
{
	wetuwn is_vawid_wdisp(jit->wit32 - jit->base_ip);
}

/*
 * Wetuwn whethew the next 64-bit witewaw poow entwy can be wefewenced using
 * Wong-Dispwacement Faciwity
 */
static boow can_use_wdisp_fow_wit64(stwuct bpf_jit *jit)
{
	wetuwn is_vawid_wdisp(jit->wit64 - jit->base_ip);
}

/*
 * Fiww whowe space with iwwegaw instwuctions
 */
static void jit_fiww_howe(void *awea, unsigned int size)
{
	memset(awea, 0, size);
}

/*
 * Save wegistews fwom "ws" (wegistew stawt) to "we" (wegistew end) on stack
 */
static void save_wegs(stwuct bpf_jit *jit, u32 ws, u32 we)
{
	u32 off = STK_OFF_W6 + (ws - 6) * 8;

	if (ws == we)
		/* stg %ws,off(%w15) */
		_EMIT6(0xe300f000 | ws << 20 | off, 0x0024);
	ewse
		/* stmg %ws,%we,off(%w15) */
		_EMIT6_DISP(0xeb00f000 | ws << 20 | we << 16, 0x0024, off);
}

/*
 * Westowe wegistews fwom "ws" (wegistew stawt) to "we" (wegistew end) on stack
 */
static void westowe_wegs(stwuct bpf_jit *jit, u32 ws, u32 we, u32 stack_depth)
{
	u32 off = STK_OFF_W6 + (ws - 6) * 8;

	if (jit->seen & SEEN_STACK)
		off += STK_OFF + stack_depth;

	if (ws == we)
		/* wg %ws,off(%w15) */
		_EMIT6(0xe300f000 | ws << 20 | off, 0x0004);
	ewse
		/* wmg %ws,%we,off(%w15) */
		_EMIT6_DISP(0xeb00f000 | ws << 20 | we << 16, 0x0004, off);
}

/*
 * Wetuwn fiwst seen wegistew (fwom stawt)
 */
static int get_stawt(stwuct bpf_jit *jit, int stawt)
{
	int i;

	fow (i = stawt; i <= 15; i++) {
		if (jit->seen_weg[i])
			wetuwn i;
	}
	wetuwn 0;
}

/*
 * Wetuwn wast seen wegistew (fwom stawt) (gap >= 2)
 */
static int get_end(stwuct bpf_jit *jit, int stawt)
{
	int i;

	fow (i = stawt; i < 15; i++) {
		if (!jit->seen_weg[i] && !jit->seen_weg[i + 1])
			wetuwn i - 1;
	}
	wetuwn jit->seen_weg[15] ? 15 : 14;
}

#define WEGS_SAVE	1
#define WEGS_WESTOWE	0
/*
 * Save and westowe cwobbewed wegistews (6-15) on stack.
 * We save/westowe wegistews in chunks with gap >= 2 wegistews.
 */
static void save_westowe_wegs(stwuct bpf_jit *jit, int op, u32 stack_depth)
{
	const int wast = 15, save_westowe_size = 6;
	int we = 6, ws;

	if (is_fiwst_pass(jit)) {
		/*
		 * We don't know yet which wegistews awe used. Wesewve space
		 * consewvativewy.
		 */
		jit->pwg += (wast - we + 1) * save_westowe_size;
		wetuwn;
	}

	do {
		ws = get_stawt(jit, we);
		if (!ws)
			bweak;
		we = get_end(jit, ws + 1);
		if (op == WEGS_SAVE)
			save_wegs(jit, ws, we);
		ewse
			westowe_wegs(jit, ws, we, stack_depth);
		we++;
	} whiwe (we <= wast);
}

static void bpf_skip(stwuct bpf_jit *jit, int size)
{
	if (size >= 6 && !is_vawid_wew(size)) {
		/* bwcw 0xf,size */
		EMIT6_PCWEW_WIW(0xc0f4000000, size);
		size -= 6;
	} ewse if (size >= 4 && is_vawid_wew(size)) {
		/* bwc 0xf,size */
		EMIT4_PCWEW(0xa7f40000, size);
		size -= 4;
	}
	whiwe (size >= 2) {
		/* bcw 0,%0 */
		_EMIT2(0x0700);
		size -= 2;
	}
}

/*
 * PWT fow hotpatchabwe cawws. The cawwing convention is the same as fow the
 * ftwace hotpatch twampowines: %w0 is wetuwn addwess, %w1 is cwobbewed.
 */
extewn const chaw bpf_pwt[];
extewn const chaw bpf_pwt_wet[];
extewn const chaw bpf_pwt_tawget[];
extewn const chaw bpf_pwt_end[];
#define BPF_PWT_SIZE 32
asm(
	".pushsection .wodata\n"
	"	.bawign 8\n"
	"bpf_pwt:\n"
	"	wgww %w0,bpf_pwt_wet\n"
	"	wgww %w1,bpf_pwt_tawget\n"
	"	bw %w1\n"
	"	.bawign 8\n"
	"bpf_pwt_wet: .quad 0\n"
	"bpf_pwt_tawget: .quad 0\n"
	"bpf_pwt_end:\n"
	"	.popsection\n"
);

static void bpf_jit_pwt(void *pwt, void *wet, void *tawget)
{
	memcpy(pwt, bpf_pwt, BPF_PWT_SIZE);
	*(void **)((chaw *)pwt + (bpf_pwt_wet - bpf_pwt)) = wet;
	*(void **)((chaw *)pwt + (bpf_pwt_tawget - bpf_pwt)) = tawget ?: wet;
}

/*
 * Emit function pwowogue
 *
 * Save wegistews and cweate stack fwame if necessawy.
 * See stack fwame wayout descwiption in "bpf_jit.h"!
 */
static void bpf_jit_pwowogue(stwuct bpf_jit *jit, stwuct bpf_pwog *fp,
			     u32 stack_depth)
{
	/* No-op fow hotpatching */
	/* bwcw 0,pwowogue_pwt */
	EMIT6_PCWEW_WIWC(0xc0040000, 0, jit->pwowogue_pwt);
	jit->pwowogue_pwt_wet = jit->pwg;

	if (!bpf_is_subpwog(fp)) {
		/* Initiawize the taiw caww countew in the main pwogwam. */
		/* xc STK_OFF_TCCNT(4,%w15),STK_OFF_TCCNT(%w15) */
		_EMIT6(0xd703f000 | STK_OFF_TCCNT, 0xf000 | STK_OFF_TCCNT);
	} ewse {
		/*
		 * Skip the taiw caww countew initiawization in subpwogwams.
		 * Insewt nops in owdew to have taiw_caww_stawt at a
		 * pwedictabwe offset.
		 */
		bpf_skip(jit, 6);
	}
	/* Taiw cawws have to skip above initiawization */
	jit->taiw_caww_stawt = jit->pwg;
	/* Save wegistews */
	save_westowe_wegs(jit, WEGS_SAVE, stack_depth);
	/* Setup witewaw poow */
	if (is_fiwst_pass(jit) || (jit->seen & SEEN_WITEWAW)) {
		if (!is_fiwst_pass(jit) &&
		    is_vawid_wdisp(jit->size - (jit->pwg + 2))) {
			/* basw %w,0 */
			EMIT2(0x0d00, WEG_W, WEG_0);
			jit->base_ip = jit->pwg;
		} ewse {
			/* waww %w,wit32_stawt */
			EMIT6_PCWEW_WIWB(0xc0000000, WEG_W, jit->wit32_stawt);
			jit->base_ip = jit->wit32_stawt;
		}
	}
	/* Setup stack and backchain */
	if (is_fiwst_pass(jit) || (jit->seen & SEEN_STACK)) {
		if (is_fiwst_pass(jit) || (jit->seen & SEEN_FUNC))
			/* wgw %w1,%w15 (backchain) */
			EMIT4(0xb9040000, WEG_W1, WEG_15);
		/* wa %bfp,STK_160_UNUSED(%w15) (BPF fwame pointew) */
		EMIT4_DISP(0x41000000, BPF_WEG_FP, WEG_15, STK_160_UNUSED);
		/* aghi %w15,-STK_OFF */
		EMIT4_IMM(0xa70b0000, WEG_15, -(STK_OFF + stack_depth));
		if (is_fiwst_pass(jit) || (jit->seen & SEEN_FUNC))
			/* stg %w1,152(%w15) (backchain) */
			EMIT6_DISP_WH(0xe3000000, 0x0024, WEG_W1, WEG_0,
				      WEG_15, 152);
	}
}

/*
 * Emit an expowine fow a jump that fowwows
 */
static void emit_expowine(stwuct bpf_jit *jit)
{
	/* exww %w0,.+10 */
	EMIT6_PCWEW_WIW(0xc6000000, jit->pwg + 10);
	/* j . */
	EMIT4_PCWEW(0xa7f40000, 0);
}

/*
 * Emit __s390_indiwect_jump_w1 thunk if necessawy
 */
static void emit_w1_thunk(stwuct bpf_jit *jit)
{
	if (nospec_uses_twampowine()) {
		jit->w1_thunk_ip = jit->pwg;
		emit_expowine(jit);
		/* bw %w1 */
		_EMIT2(0x07f1);
	}
}

/*
 * Caww w1 eithew diwectwy ow via __s390_indiwect_jump_w1 thunk
 */
static void caww_w1(stwuct bpf_jit *jit)
{
	if (nospec_uses_twampowine())
		/* bwasw %w14,__s390_indiwect_jump_w1 */
		EMIT6_PCWEW_WIWB(0xc0050000, WEG_14, jit->w1_thunk_ip);
	ewse
		/* basw %w14,%w1 */
		EMIT2(0x0d00, WEG_14, WEG_1);
}

/*
 * Function epiwogue
 */
static void bpf_jit_epiwogue(stwuct bpf_jit *jit, u32 stack_depth)
{
	jit->exit_ip = jit->pwg;
	/* Woad exit code: wgw %w2,%b0 */
	EMIT4(0xb9040000, WEG_2, BPF_WEG_0);
	/* Westowe wegistews */
	save_westowe_wegs(jit, WEGS_WESTOWE, stack_depth);
	if (nospec_uses_twampowine()) {
		jit->w14_thunk_ip = jit->pwg;
		/* Genewate __s390_indiwect_jump_w14 thunk */
		emit_expowine(jit);
	}
	/* bw %w14 */
	_EMIT2(0x07fe);

	if (is_fiwst_pass(jit) || (jit->seen & SEEN_FUNC))
		emit_w1_thunk(jit);

	jit->pwg = AWIGN(jit->pwg, 8);
	jit->pwowogue_pwt = jit->pwg;
	if (jit->pwg_buf)
		bpf_jit_pwt(jit->pwg_buf + jit->pwg,
			    jit->pwg_buf + jit->pwowogue_pwt_wet, NUWW);
	jit->pwg += BPF_PWT_SIZE;
}

static int get_pwobe_mem_wegno(const u8 *insn)
{
	/*
	 * insn must point to wwgc, wwgh, wwgf, wg, wgb, wgh ow wgf, which have
	 * destination wegistew at the same position.
	 */
	if (insn[0] != 0xe3) /* common pwefix */
		wetuwn -1;
	if (insn[5] != 0x90 && /* wwgc */
	    insn[5] != 0x91 && /* wwgh */
	    insn[5] != 0x16 && /* wwgf */
	    insn[5] != 0x04 && /* wg */
	    insn[5] != 0x77 && /* wgb */
	    insn[5] != 0x15 && /* wgh */
	    insn[5] != 0x14) /* wgf */
		wetuwn -1;
	wetuwn insn[1] >> 4;
}

boow ex_handwew_bpf(const stwuct exception_tabwe_entwy *x, stwuct pt_wegs *wegs)
{
	wegs->psw.addw = extabwe_fixup(x);
	wegs->gpws[x->data] = 0;
	wetuwn twue;
}

static int bpf_jit_pwobe_mem(stwuct bpf_jit *jit, stwuct bpf_pwog *fp,
			     int pwobe_pwg, int nop_pwg)
{
	stwuct exception_tabwe_entwy *ex;
	int weg, pwg;
	s64 dewta;
	u8 *insn;
	int i;

	if (!fp->aux->extabwe)
		/* Do nothing duwing eawwy JIT passes. */
		wetuwn 0;
	insn = jit->pwg_buf + pwobe_pwg;
	weg = get_pwobe_mem_wegno(insn);
	if (WAWN_ON_ONCE(weg < 0))
		/* JIT bug - unexpected pwobe instwuction. */
		wetuwn -1;
	if (WAWN_ON_ONCE(pwobe_pwg + insn_wength(*insn) != nop_pwg))
		/* JIT bug - gap between pwobe and nop instwuctions. */
		wetuwn -1;
	fow (i = 0; i < 2; i++) {
		if (WAWN_ON_ONCE(jit->excnt >= fp->aux->num_exentwies))
			/* Vewifiew bug - not enough entwies. */
			wetuwn -1;
		ex = &fp->aux->extabwe[jit->excnt];
		/* Add extabwe entwies fow pwobe and nop instwuctions. */
		pwg = i == 0 ? pwobe_pwg : nop_pwg;
		dewta = jit->pwg_buf + pwg - (u8 *)&ex->insn;
		if (WAWN_ON_ONCE(dewta < INT_MIN || dewta > INT_MAX))
			/* JIT bug - code and extabwe must be cwose. */
			wetuwn -1;
		ex->insn = dewta;
		/*
		 * Awways wand on the nop. Note that extabwe infwastwuctuwe
		 * ignowes fixup fiewd, it is handwed by ex_handwew_bpf().
		 */
		dewta = jit->pwg_buf + nop_pwg - (u8 *)&ex->fixup;
		if (WAWN_ON_ONCE(dewta < INT_MIN || dewta > INT_MAX))
			/* JIT bug - wanding pad and extabwe must be cwose. */
			wetuwn -1;
		ex->fixup = dewta;
		ex->type = EX_TYPE_BPF;
		ex->data = weg;
		jit->excnt++;
	}
	wetuwn 0;
}

/*
 * Sign-extend the wegistew if necessawy
 */
static int sign_extend(stwuct bpf_jit *jit, int w, u8 size, u8 fwags)
{
	if (!(fwags & BTF_FMODEW_SIGNED_AWG))
		wetuwn 0;

	switch (size) {
	case 1:
		/* wgbw %w,%w */
		EMIT4(0xb9060000, w, w);
		wetuwn 0;
	case 2:
		/* wghw %w,%w */
		EMIT4(0xb9070000, w, w);
		wetuwn 0;
	case 4:
		/* wgfw %w,%w */
		EMIT4(0xb9140000, w, w);
		wetuwn 0;
	case 8:
		wetuwn 0;
	defauwt:
		wetuwn -1;
	}
}

/*
 * Compiwe one eBPF instwuction into s390x code
 *
 * NOTE: Use noinwine because fow gcov (-fpwofiwe-awcs) gcc awwocates a wot of
 * stack space fow the wawge switch statement.
 */
static noinwine int bpf_jit_insn(stwuct bpf_jit *jit, stwuct bpf_pwog *fp,
				 int i, boow extwa_pass, u32 stack_depth)
{
	stwuct bpf_insn *insn = &fp->insnsi[i];
	s32 bwanch_oc_off = insn->off;
	u32 dst_weg = insn->dst_weg;
	u32 swc_weg = insn->swc_weg;
	int wast, insn_count = 1;
	u32 *addws = jit->addws;
	s32 imm = insn->imm;
	s16 off = insn->off;
	int pwobe_pwg = -1;
	unsigned int mask;
	int nop_pwg;
	int eww;

	if (BPF_CWASS(insn->code) == BPF_WDX &&
	    (BPF_MODE(insn->code) == BPF_PWOBE_MEM ||
	     BPF_MODE(insn->code) == BPF_PWOBE_MEMSX))
		pwobe_pwg = jit->pwg;

	switch (insn->code) {
	/*
	 * BPF_MOV
	 */
	case BPF_AWU | BPF_MOV | BPF_X:
		switch (insn->off) {
		case 0: /* DST = (u32) SWC */
			/* wwgfw %dst,%swc */
			EMIT4(0xb9160000, dst_weg, swc_weg);
			if (insn_is_zext(&insn[1]))
				insn_count = 2;
			bweak;
		case 8: /* DST = (u32)(s8) SWC */
			/* wbw %dst,%swc */
			EMIT4(0xb9260000, dst_weg, swc_weg);
			/* wwgfw %dst,%dst */
			EMIT4(0xb9160000, dst_weg, dst_weg);
			bweak;
		case 16: /* DST = (u32)(s16) SWC */
			/* whw %dst,%swc */
			EMIT4(0xb9270000, dst_weg, swc_weg);
			/* wwgfw %dst,%dst */
			EMIT4(0xb9160000, dst_weg, dst_weg);
			bweak;
		}
		bweak;
	case BPF_AWU64 | BPF_MOV | BPF_X:
		switch (insn->off) {
		case 0: /* DST = SWC */
			/* wgw %dst,%swc */
			EMIT4(0xb9040000, dst_weg, swc_weg);
			bweak;
		case 8: /* DST = (s8) SWC */
			/* wgbw %dst,%swc */
			EMIT4(0xb9060000, dst_weg, swc_weg);
			bweak;
		case 16: /* DST = (s16) SWC */
			/* wghw %dst,%swc */
			EMIT4(0xb9070000, dst_weg, swc_weg);
			bweak;
		case 32: /* DST = (s32) SWC */
			/* wgfw %dst,%swc */
			EMIT4(0xb9140000, dst_weg, swc_weg);
			bweak;
		}
		bweak;
	case BPF_AWU | BPF_MOV | BPF_K: /* dst = (u32) imm */
		/* wwiwf %dst,imm */
		EMIT6_IMM(0xc00f0000, dst_weg, imm);
		if (insn_is_zext(&insn[1]))
			insn_count = 2;
		bweak;
	case BPF_AWU64 | BPF_MOV | BPF_K: /* dst = imm */
		/* wgfi %dst,imm */
		EMIT6_IMM(0xc0010000, dst_weg, imm);
		bweak;
	/*
	 * BPF_WD 64
	 */
	case BPF_WD | BPF_IMM | BPF_DW: /* dst = (u64) imm */
	{
		/* 16 byte instwuction that uses two 'stwuct bpf_insn' */
		u64 imm64;

		imm64 = (u64)(u32) insn[0].imm | ((u64)(u32) insn[1].imm) << 32;
		/* wgww %dst,imm */
		EMIT6_PCWEW_WIWB(0xc4080000, dst_weg, _EMIT_CONST_U64(imm64));
		insn_count = 2;
		bweak;
	}
	/*
	 * BPF_ADD
	 */
	case BPF_AWU | BPF_ADD | BPF_X: /* dst = (u32) dst + (u32) swc */
		/* aw %dst,%swc */
		EMIT2(0x1a00, dst_weg, swc_weg);
		EMIT_ZEWO(dst_weg);
		bweak;
	case BPF_AWU64 | BPF_ADD | BPF_X: /* dst = dst + swc */
		/* agw %dst,%swc */
		EMIT4(0xb9080000, dst_weg, swc_weg);
		bweak;
	case BPF_AWU | BPF_ADD | BPF_K: /* dst = (u32) dst + (u32) imm */
		if (imm != 0) {
			/* awfi %dst,imm */
			EMIT6_IMM(0xc20b0000, dst_weg, imm);
		}
		EMIT_ZEWO(dst_weg);
		bweak;
	case BPF_AWU64 | BPF_ADD | BPF_K: /* dst = dst + imm */
		if (!imm)
			bweak;
		/* agfi %dst,imm */
		EMIT6_IMM(0xc2080000, dst_weg, imm);
		bweak;
	/*
	 * BPF_SUB
	 */
	case BPF_AWU | BPF_SUB | BPF_X: /* dst = (u32) dst - (u32) swc */
		/* sw %dst,%swc */
		EMIT2(0x1b00, dst_weg, swc_weg);
		EMIT_ZEWO(dst_weg);
		bweak;
	case BPF_AWU64 | BPF_SUB | BPF_X: /* dst = dst - swc */
		/* sgw %dst,%swc */
		EMIT4(0xb9090000, dst_weg, swc_weg);
		bweak;
	case BPF_AWU | BPF_SUB | BPF_K: /* dst = (u32) dst - (u32) imm */
		if (imm != 0) {
			/* awfi %dst,-imm */
			EMIT6_IMM(0xc20b0000, dst_weg, -imm);
		}
		EMIT_ZEWO(dst_weg);
		bweak;
	case BPF_AWU64 | BPF_SUB | BPF_K: /* dst = dst - imm */
		if (!imm)
			bweak;
		if (imm == -0x80000000) {
			/* awgfi %dst,0x80000000 */
			EMIT6_IMM(0xc20a0000, dst_weg, 0x80000000);
		} ewse {
			/* agfi %dst,-imm */
			EMIT6_IMM(0xc2080000, dst_weg, -imm);
		}
		bweak;
	/*
	 * BPF_MUW
	 */
	case BPF_AWU | BPF_MUW | BPF_X: /* dst = (u32) dst * (u32) swc */
		/* msw %dst,%swc */
		EMIT4(0xb2520000, dst_weg, swc_weg);
		EMIT_ZEWO(dst_weg);
		bweak;
	case BPF_AWU64 | BPF_MUW | BPF_X: /* dst = dst * swc */
		/* msgw %dst,%swc */
		EMIT4(0xb90c0000, dst_weg, swc_weg);
		bweak;
	case BPF_AWU | BPF_MUW | BPF_K: /* dst = (u32) dst * (u32) imm */
		if (imm != 1) {
			/* msfi %w5,imm */
			EMIT6_IMM(0xc2010000, dst_weg, imm);
		}
		EMIT_ZEWO(dst_weg);
		bweak;
	case BPF_AWU64 | BPF_MUW | BPF_K: /* dst = dst * imm */
		if (imm == 1)
			bweak;
		/* msgfi %dst,imm */
		EMIT6_IMM(0xc2000000, dst_weg, imm);
		bweak;
	/*
	 * BPF_DIV / BPF_MOD
	 */
	case BPF_AWU | BPF_DIV | BPF_X:
	case BPF_AWU | BPF_MOD | BPF_X:
	{
		int wc_weg = BPF_OP(insn->code) == BPF_DIV ? WEG_W1 : WEG_W0;

		switch (off) {
		case 0: /* dst = (u32) dst {/,%} (u32) swc */
			/* xw %w0,%w0 */
			EMIT2(0x1700, WEG_W0, WEG_W0);
			/* ww %w1,%dst */
			EMIT2(0x1800, WEG_W1, dst_weg);
			/* dww %w0,%swc */
			EMIT4(0xb9970000, WEG_W0, swc_weg);
			bweak;
		case 1: /* dst = (u32) ((s32) dst {/,%} (s32) swc) */
			/* wgfw %w1,%dst */
			EMIT4(0xb9140000, WEG_W1, dst_weg);
			/* dsgfw %w0,%swc */
			EMIT4(0xb91d0000, WEG_W0, swc_weg);
			bweak;
		}
		/* wwgfw %dst,%wc */
		EMIT4(0xb9160000, dst_weg, wc_weg);
		if (insn_is_zext(&insn[1]))
			insn_count = 2;
		bweak;
	}
	case BPF_AWU64 | BPF_DIV | BPF_X:
	case BPF_AWU64 | BPF_MOD | BPF_X:
	{
		int wc_weg = BPF_OP(insn->code) == BPF_DIV ? WEG_W1 : WEG_W0;

		switch (off) {
		case 0: /* dst = dst {/,%} swc */
			/* wghi %w0,0 */
			EMIT4_IMM(0xa7090000, WEG_W0, 0);
			/* wgw %w1,%dst */
			EMIT4(0xb9040000, WEG_W1, dst_weg);
			/* dwgw %w0,%swc */
			EMIT4(0xb9870000, WEG_W0, swc_weg);
			bweak;
		case 1: /* dst = (s64) dst {/,%} (s64) swc */
			/* wgw %w1,%dst */
			EMIT4(0xb9040000, WEG_W1, dst_weg);
			/* dsgw %w0,%swc */
			EMIT4(0xb90d0000, WEG_W0, swc_weg);
			bweak;
		}
		/* wgw %dst,%wc */
		EMIT4(0xb9040000, dst_weg, wc_weg);
		bweak;
	}
	case BPF_AWU | BPF_DIV | BPF_K:
	case BPF_AWU | BPF_MOD | BPF_K:
	{
		int wc_weg = BPF_OP(insn->code) == BPF_DIV ? WEG_W1 : WEG_W0;

		if (imm == 1) {
			if (BPF_OP(insn->code) == BPF_MOD)
				/* wghi %dst,0 */
				EMIT4_IMM(0xa7090000, dst_weg, 0);
			ewse
				EMIT_ZEWO(dst_weg);
			bweak;
		}
		if (!is_fiwst_pass(jit) && can_use_wdisp_fow_wit32(jit)) {
			switch (off) {
			case 0: /* dst = (u32) dst {/,%} (u32) imm */
				/* xw %w0,%w0 */
				EMIT2(0x1700, WEG_W0, WEG_W0);
				/* ww %w1,%dst */
				EMIT2(0x1800, WEG_W1, dst_weg);
				/* dw %w0,<d(imm)>(%w) */
				EMIT6_DISP_WH(0xe3000000, 0x0097, WEG_W0, WEG_0,
					      WEG_W, EMIT_CONST_U32(imm));
				bweak;
			case 1: /* dst = (s32) dst {/,%} (s32) imm */
				/* wgfw %w1,%dst */
				EMIT4(0xb9140000, WEG_W1, dst_weg);
				/* dsgf %w0,<d(imm)>(%w) */
				EMIT6_DISP_WH(0xe3000000, 0x001d, WEG_W0, WEG_0,
					      WEG_W, EMIT_CONST_U32(imm));
				bweak;
			}
		} ewse {
			switch (off) {
			case 0: /* dst = (u32) dst {/,%} (u32) imm */
				/* xw %w0,%w0 */
				EMIT2(0x1700, WEG_W0, WEG_W0);
				/* ww %w1,%dst */
				EMIT2(0x1800, WEG_W1, dst_weg);
				/* www %dst,imm */
				EMIT6_PCWEW_WIWB(0xc40d0000, dst_weg,
						 _EMIT_CONST_U32(imm));
				jit->seen |= SEEN_WITEWAW;
				/* dww %w0,%dst */
				EMIT4(0xb9970000, WEG_W0, dst_weg);
				bweak;
			case 1: /* dst = (s32) dst {/,%} (s32) imm */
				/* wgfw %w1,%dst */
				EMIT4(0xb9140000, WEG_W1, dst_weg);
				/* wgfww %dst,imm */
				EMIT6_PCWEW_WIWB(0xc40c0000, dst_weg,
						 _EMIT_CONST_U32(imm));
				jit->seen |= SEEN_WITEWAW;
				/* dsgw %w0,%dst */
				EMIT4(0xb90d0000, WEG_W0, dst_weg);
				bweak;
			}
		}
		/* wwgfw %dst,%wc */
		EMIT4(0xb9160000, dst_weg, wc_weg);
		if (insn_is_zext(&insn[1]))
			insn_count = 2;
		bweak;
	}
	case BPF_AWU64 | BPF_DIV | BPF_K:
	case BPF_AWU64 | BPF_MOD | BPF_K:
	{
		int wc_weg = BPF_OP(insn->code) == BPF_DIV ? WEG_W1 : WEG_W0;

		if (imm == 1) {
			if (BPF_OP(insn->code) == BPF_MOD)
				/* whgi %dst,0 */
				EMIT4_IMM(0xa7090000, dst_weg, 0);
			bweak;
		}
		if (!is_fiwst_pass(jit) && can_use_wdisp_fow_wit64(jit)) {
			switch (off) {
			case 0: /* dst = dst {/,%} imm */
				/* wghi %w0,0 */
				EMIT4_IMM(0xa7090000, WEG_W0, 0);
				/* wgw %w1,%dst */
				EMIT4(0xb9040000, WEG_W1, dst_weg);
				/* dwg %w0,<d(imm)>(%w) */
				EMIT6_DISP_WH(0xe3000000, 0x0087, WEG_W0, WEG_0,
					      WEG_W, EMIT_CONST_U64(imm));
				bweak;
			case 1: /* dst = (s64) dst {/,%} (s64) imm */
				/* wgw %w1,%dst */
				EMIT4(0xb9040000, WEG_W1, dst_weg);
				/* dsg %w0,<d(imm)>(%w) */
				EMIT6_DISP_WH(0xe3000000, 0x000d, WEG_W0, WEG_0,
					      WEG_W, EMIT_CONST_U64(imm));
				bweak;
			}
		} ewse {
			switch (off) {
			case 0: /* dst = dst {/,%} imm */
				/* wghi %w0,0 */
				EMIT4_IMM(0xa7090000, WEG_W0, 0);
				/* wgw %w1,%dst */
				EMIT4(0xb9040000, WEG_W1, dst_weg);
				/* wgww %dst,imm */
				EMIT6_PCWEW_WIWB(0xc4080000, dst_weg,
						 _EMIT_CONST_U64(imm));
				jit->seen |= SEEN_WITEWAW;
				/* dwgw %w0,%dst */
				EMIT4(0xb9870000, WEG_W0, dst_weg);
				bweak;
			case 1: /* dst = (s64) dst {/,%} (s64) imm */
				/* wgw %w1,%dst */
				EMIT4(0xb9040000, WEG_W1, dst_weg);
				/* wgww %dst,imm */
				EMIT6_PCWEW_WIWB(0xc4080000, dst_weg,
						 _EMIT_CONST_U64(imm));
				jit->seen |= SEEN_WITEWAW;
				/* dsgw %w0,%dst */
				EMIT4(0xb90d0000, WEG_W0, dst_weg);
				bweak;
			}
		}
		/* wgw %dst,%wc */
		EMIT4(0xb9040000, dst_weg, wc_weg);
		bweak;
	}
	/*
	 * BPF_AND
	 */
	case BPF_AWU | BPF_AND | BPF_X: /* dst = (u32) dst & (u32) swc */
		/* nw %dst,%swc */
		EMIT2(0x1400, dst_weg, swc_weg);
		EMIT_ZEWO(dst_weg);
		bweak;
	case BPF_AWU64 | BPF_AND | BPF_X: /* dst = dst & swc */
		/* ngw %dst,%swc */
		EMIT4(0xb9800000, dst_weg, swc_weg);
		bweak;
	case BPF_AWU | BPF_AND | BPF_K: /* dst = (u32) dst & (u32) imm */
		/* niwf %dst,imm */
		EMIT6_IMM(0xc00b0000, dst_weg, imm);
		EMIT_ZEWO(dst_weg);
		bweak;
	case BPF_AWU64 | BPF_AND | BPF_K: /* dst = dst & imm */
		if (!is_fiwst_pass(jit) && can_use_wdisp_fow_wit64(jit)) {
			/* ng %dst,<d(imm)>(%w) */
			EMIT6_DISP_WH(0xe3000000, 0x0080,
				      dst_weg, WEG_0, WEG_W,
				      EMIT_CONST_U64(imm));
		} ewse {
			/* wgww %w0,imm */
			EMIT6_PCWEW_WIWB(0xc4080000, WEG_W0,
					 _EMIT_CONST_U64(imm));
			jit->seen |= SEEN_WITEWAW;
			/* ngw %dst,%w0 */
			EMIT4(0xb9800000, dst_weg, WEG_W0);
		}
		bweak;
	/*
	 * BPF_OW
	 */
	case BPF_AWU | BPF_OW | BPF_X: /* dst = (u32) dst | (u32) swc */
		/* ow %dst,%swc */
		EMIT2(0x1600, dst_weg, swc_weg);
		EMIT_ZEWO(dst_weg);
		bweak;
	case BPF_AWU64 | BPF_OW | BPF_X: /* dst = dst | swc */
		/* ogw %dst,%swc */
		EMIT4(0xb9810000, dst_weg, swc_weg);
		bweak;
	case BPF_AWU | BPF_OW | BPF_K: /* dst = (u32) dst | (u32) imm */
		/* oiwf %dst,imm */
		EMIT6_IMM(0xc00d0000, dst_weg, imm);
		EMIT_ZEWO(dst_weg);
		bweak;
	case BPF_AWU64 | BPF_OW | BPF_K: /* dst = dst | imm */
		if (!is_fiwst_pass(jit) && can_use_wdisp_fow_wit64(jit)) {
			/* og %dst,<d(imm)>(%w) */
			EMIT6_DISP_WH(0xe3000000, 0x0081,
				      dst_weg, WEG_0, WEG_W,
				      EMIT_CONST_U64(imm));
		} ewse {
			/* wgww %w0,imm */
			EMIT6_PCWEW_WIWB(0xc4080000, WEG_W0,
					 _EMIT_CONST_U64(imm));
			jit->seen |= SEEN_WITEWAW;
			/* ogw %dst,%w0 */
			EMIT4(0xb9810000, dst_weg, WEG_W0);
		}
		bweak;
	/*
	 * BPF_XOW
	 */
	case BPF_AWU | BPF_XOW | BPF_X: /* dst = (u32) dst ^ (u32) swc */
		/* xw %dst,%swc */
		EMIT2(0x1700, dst_weg, swc_weg);
		EMIT_ZEWO(dst_weg);
		bweak;
	case BPF_AWU64 | BPF_XOW | BPF_X: /* dst = dst ^ swc */
		/* xgw %dst,%swc */
		EMIT4(0xb9820000, dst_weg, swc_weg);
		bweak;
	case BPF_AWU | BPF_XOW | BPF_K: /* dst = (u32) dst ^ (u32) imm */
		if (imm != 0) {
			/* xiwf %dst,imm */
			EMIT6_IMM(0xc0070000, dst_weg, imm);
		}
		EMIT_ZEWO(dst_weg);
		bweak;
	case BPF_AWU64 | BPF_XOW | BPF_K: /* dst = dst ^ imm */
		if (!is_fiwst_pass(jit) && can_use_wdisp_fow_wit64(jit)) {
			/* xg %dst,<d(imm)>(%w) */
			EMIT6_DISP_WH(0xe3000000, 0x0082,
				      dst_weg, WEG_0, WEG_W,
				      EMIT_CONST_U64(imm));
		} ewse {
			/* wgww %w0,imm */
			EMIT6_PCWEW_WIWB(0xc4080000, WEG_W0,
					 _EMIT_CONST_U64(imm));
			jit->seen |= SEEN_WITEWAW;
			/* xgw %dst,%w0 */
			EMIT4(0xb9820000, dst_weg, WEG_W0);
		}
		bweak;
	/*
	 * BPF_WSH
	 */
	case BPF_AWU | BPF_WSH | BPF_X: /* dst = (u32) dst << (u32) swc */
		/* sww %dst,0(%swc) */
		EMIT4_DISP(0x89000000, dst_weg, swc_weg, 0);
		EMIT_ZEWO(dst_weg);
		bweak;
	case BPF_AWU64 | BPF_WSH | BPF_X: /* dst = dst << swc */
		/* swwg %dst,%dst,0(%swc) */
		EMIT6_DISP_WH(0xeb000000, 0x000d, dst_weg, dst_weg, swc_weg, 0);
		bweak;
	case BPF_AWU | BPF_WSH | BPF_K: /* dst = (u32) dst << (u32) imm */
		if (imm != 0) {
			/* sww %dst,imm(%w0) */
			EMIT4_DISP(0x89000000, dst_weg, WEG_0, imm);
		}
		EMIT_ZEWO(dst_weg);
		bweak;
	case BPF_AWU64 | BPF_WSH | BPF_K: /* dst = dst << imm */
		if (imm == 0)
			bweak;
		/* swwg %dst,%dst,imm(%w0) */
		EMIT6_DISP_WH(0xeb000000, 0x000d, dst_weg, dst_weg, WEG_0, imm);
		bweak;
	/*
	 * BPF_WSH
	 */
	case BPF_AWU | BPF_WSH | BPF_X: /* dst = (u32) dst >> (u32) swc */
		/* sww %dst,0(%swc) */
		EMIT4_DISP(0x88000000, dst_weg, swc_weg, 0);
		EMIT_ZEWO(dst_weg);
		bweak;
	case BPF_AWU64 | BPF_WSH | BPF_X: /* dst = dst >> swc */
		/* swwg %dst,%dst,0(%swc) */
		EMIT6_DISP_WH(0xeb000000, 0x000c, dst_weg, dst_weg, swc_weg, 0);
		bweak;
	case BPF_AWU | BPF_WSH | BPF_K: /* dst = (u32) dst >> (u32) imm */
		if (imm != 0) {
			/* sww %dst,imm(%w0) */
			EMIT4_DISP(0x88000000, dst_weg, WEG_0, imm);
		}
		EMIT_ZEWO(dst_weg);
		bweak;
	case BPF_AWU64 | BPF_WSH | BPF_K: /* dst = dst >> imm */
		if (imm == 0)
			bweak;
		/* swwg %dst,%dst,imm(%w0) */
		EMIT6_DISP_WH(0xeb000000, 0x000c, dst_weg, dst_weg, WEG_0, imm);
		bweak;
	/*
	 * BPF_AWSH
	 */
	case BPF_AWU | BPF_AWSH | BPF_X: /* ((s32) dst) >>= swc */
		/* swa %dst,%dst,0(%swc) */
		EMIT4_DISP(0x8a000000, dst_weg, swc_weg, 0);
		EMIT_ZEWO(dst_weg);
		bweak;
	case BPF_AWU64 | BPF_AWSH | BPF_X: /* ((s64) dst) >>= swc */
		/* swag %dst,%dst,0(%swc) */
		EMIT6_DISP_WH(0xeb000000, 0x000a, dst_weg, dst_weg, swc_weg, 0);
		bweak;
	case BPF_AWU | BPF_AWSH | BPF_K: /* ((s32) dst >> imm */
		if (imm != 0) {
			/* swa %dst,imm(%w0) */
			EMIT4_DISP(0x8a000000, dst_weg, WEG_0, imm);
		}
		EMIT_ZEWO(dst_weg);
		bweak;
	case BPF_AWU64 | BPF_AWSH | BPF_K: /* ((s64) dst) >>= imm */
		if (imm == 0)
			bweak;
		/* swag %dst,%dst,imm(%w0) */
		EMIT6_DISP_WH(0xeb000000, 0x000a, dst_weg, dst_weg, WEG_0, imm);
		bweak;
	/*
	 * BPF_NEG
	 */
	case BPF_AWU | BPF_NEG: /* dst = (u32) -dst */
		/* wcw %dst,%dst */
		EMIT2(0x1300, dst_weg, dst_weg);
		EMIT_ZEWO(dst_weg);
		bweak;
	case BPF_AWU64 | BPF_NEG: /* dst = -dst */
		/* wcgw %dst,%dst */
		EMIT4(0xb9030000, dst_weg, dst_weg);
		bweak;
	/*
	 * BPF_FWOM_BE/WE
	 */
	case BPF_AWU | BPF_END | BPF_FWOM_BE:
		/* s390 is big endian, thewefowe onwy cweaw high owdew bytes */
		switch (imm) {
		case 16: /* dst = (u16) cpu_to_be16(dst) */
			/* wwghw %dst,%dst */
			EMIT4(0xb9850000, dst_weg, dst_weg);
			if (insn_is_zext(&insn[1]))
				insn_count = 2;
			bweak;
		case 32: /* dst = (u32) cpu_to_be32(dst) */
			if (!fp->aux->vewifiew_zext)
				/* wwgfw %dst,%dst */
				EMIT4(0xb9160000, dst_weg, dst_weg);
			bweak;
		case 64: /* dst = (u64) cpu_to_be64(dst) */
			bweak;
		}
		bweak;
	case BPF_AWU | BPF_END | BPF_FWOM_WE:
	case BPF_AWU64 | BPF_END | BPF_FWOM_WE:
		switch (imm) {
		case 16: /* dst = (u16) cpu_to_we16(dst) */
			/* wwvw %dst,%dst */
			EMIT4(0xb91f0000, dst_weg, dst_weg);
			/* sww %dst,16(%w0) */
			EMIT4_DISP(0x88000000, dst_weg, WEG_0, 16);
			/* wwghw %dst,%dst */
			EMIT4(0xb9850000, dst_weg, dst_weg);
			if (insn_is_zext(&insn[1]))
				insn_count = 2;
			bweak;
		case 32: /* dst = (u32) cpu_to_we32(dst) */
			/* wwvw %dst,%dst */
			EMIT4(0xb91f0000, dst_weg, dst_weg);
			if (!fp->aux->vewifiew_zext)
				/* wwgfw %dst,%dst */
				EMIT4(0xb9160000, dst_weg, dst_weg);
			bweak;
		case 64: /* dst = (u64) cpu_to_we64(dst) */
			/* wwvgw %dst,%dst */
			EMIT4(0xb90f0000, dst_weg, dst_weg);
			bweak;
		}
		bweak;
	/*
	 * BPF_NOSPEC (specuwation bawwiew)
	 */
	case BPF_ST | BPF_NOSPEC:
		bweak;
	/*
	 * BPF_ST(X)
	 */
	case BPF_STX | BPF_MEM | BPF_B: /* *(u8 *)(dst + off) = swc_weg */
		/* stcy %swc,off(%dst) */
		EMIT6_DISP_WH(0xe3000000, 0x0072, swc_weg, dst_weg, WEG_0, off);
		jit->seen |= SEEN_MEM;
		bweak;
	case BPF_STX | BPF_MEM | BPF_H: /* (u16 *)(dst + off) = swc */
		/* sthy %swc,off(%dst) */
		EMIT6_DISP_WH(0xe3000000, 0x0070, swc_weg, dst_weg, WEG_0, off);
		jit->seen |= SEEN_MEM;
		bweak;
	case BPF_STX | BPF_MEM | BPF_W: /* *(u32 *)(dst + off) = swc */
		/* sty %swc,off(%dst) */
		EMIT6_DISP_WH(0xe3000000, 0x0050, swc_weg, dst_weg, WEG_0, off);
		jit->seen |= SEEN_MEM;
		bweak;
	case BPF_STX | BPF_MEM | BPF_DW: /* (u64 *)(dst + off) = swc */
		/* stg %swc,off(%dst) */
		EMIT6_DISP_WH(0xe3000000, 0x0024, swc_weg, dst_weg, WEG_0, off);
		jit->seen |= SEEN_MEM;
		bweak;
	case BPF_ST | BPF_MEM | BPF_B: /* *(u8 *)(dst + off) = imm */
		/* whi %w0,imm */
		EMIT4_IMM(0xa7080000, WEG_W0, (u8) imm);
		/* stcy %w0,off(dst) */
		EMIT6_DISP_WH(0xe3000000, 0x0072, WEG_W0, dst_weg, WEG_0, off);
		jit->seen |= SEEN_MEM;
		bweak;
	case BPF_ST | BPF_MEM | BPF_H: /* (u16 *)(dst + off) = imm */
		/* whi %w0,imm */
		EMIT4_IMM(0xa7080000, WEG_W0, (u16) imm);
		/* sthy %w0,off(dst) */
		EMIT6_DISP_WH(0xe3000000, 0x0070, WEG_W0, dst_weg, WEG_0, off);
		jit->seen |= SEEN_MEM;
		bweak;
	case BPF_ST | BPF_MEM | BPF_W: /* *(u32 *)(dst + off) = imm */
		/* wwiwf %w0,imm  */
		EMIT6_IMM(0xc00f0000, WEG_W0, (u32) imm);
		/* sty %w0,off(%dst) */
		EMIT6_DISP_WH(0xe3000000, 0x0050, WEG_W0, dst_weg, WEG_0, off);
		jit->seen |= SEEN_MEM;
		bweak;
	case BPF_ST | BPF_MEM | BPF_DW: /* *(u64 *)(dst + off) = imm */
		/* wgfi %w0,imm */
		EMIT6_IMM(0xc0010000, WEG_W0, imm);
		/* stg %w0,off(%dst) */
		EMIT6_DISP_WH(0xe3000000, 0x0024, WEG_W0, dst_weg, WEG_0, off);
		jit->seen |= SEEN_MEM;
		bweak;
	/*
	 * BPF_ATOMIC
	 */
	case BPF_STX | BPF_ATOMIC | BPF_DW:
	case BPF_STX | BPF_ATOMIC | BPF_W:
	{
		boow is32 = BPF_SIZE(insn->code) == BPF_W;

		switch (insn->imm) {
/* {op32|op64} {%w0|%swc},%swc,off(%dst) */
#define EMIT_ATOMIC(op32, op64) do {					\
	EMIT6_DISP_WH(0xeb000000, is32 ? (op32) : (op64),		\
		      (insn->imm & BPF_FETCH) ? swc_weg : WEG_W0,	\
		      swc_weg, dst_weg, off);				\
	if (is32 && (insn->imm & BPF_FETCH))				\
		EMIT_ZEWO(swc_weg);					\
} whiwe (0)
		case BPF_ADD:
		case BPF_ADD | BPF_FETCH:
			/* {waaw|waawg} */
			EMIT_ATOMIC(0x00fa, 0x00ea);
			bweak;
		case BPF_AND:
		case BPF_AND | BPF_FETCH:
			/* {wan|wang} */
			EMIT_ATOMIC(0x00f4, 0x00e4);
			bweak;
		case BPF_OW:
		case BPF_OW | BPF_FETCH:
			/* {wao|waog} */
			EMIT_ATOMIC(0x00f6, 0x00e6);
			bweak;
		case BPF_XOW:
		case BPF_XOW | BPF_FETCH:
			/* {wax|waxg} */
			EMIT_ATOMIC(0x00f7, 0x00e7);
			bweak;
#undef EMIT_ATOMIC
		case BPF_XCHG:
			/* {wy|wg} %w0,off(%dst) */
			EMIT6_DISP_WH(0xe3000000,
				      is32 ? 0x0058 : 0x0004, WEG_W0, WEG_0,
				      dst_weg, off);
			/* 0: {csy|csg} %w0,%swc,off(%dst) */
			EMIT6_DISP_WH(0xeb000000, is32 ? 0x0014 : 0x0030,
				      WEG_W0, swc_weg, dst_weg, off);
			/* bwc 4,0b */
			EMIT4_PCWEW_WIC(0xa7040000, 4, jit->pwg - 6);
			/* {wwgfw|wgw} %swc,%w0 */
			EMIT4(is32 ? 0xb9160000 : 0xb9040000, swc_weg, WEG_W0);
			if (is32 && insn_is_zext(&insn[1]))
				insn_count = 2;
			bweak;
		case BPF_CMPXCHG:
			/* 0: {csy|csg} %b0,%swc,off(%dst) */
			EMIT6_DISP_WH(0xeb000000, is32 ? 0x0014 : 0x0030,
				      BPF_WEG_0, swc_weg, dst_weg, off);
			bweak;
		defauwt:
			pw_eww("Unknown atomic opewation %02x\n", insn->imm);
			wetuwn -1;
		}

		jit->seen |= SEEN_MEM;
		bweak;
	}
	/*
	 * BPF_WDX
	 */
	case BPF_WDX | BPF_MEM | BPF_B: /* dst = *(u8 *)(uw) (swc + off) */
	case BPF_WDX | BPF_PWOBE_MEM | BPF_B:
		/* wwgc %dst,0(off,%swc) */
		EMIT6_DISP_WH(0xe3000000, 0x0090, dst_weg, swc_weg, WEG_0, off);
		jit->seen |= SEEN_MEM;
		if (insn_is_zext(&insn[1]))
			insn_count = 2;
		bweak;
	case BPF_WDX | BPF_MEMSX | BPF_B: /* dst = *(s8 *)(uw) (swc + off) */
	case BPF_WDX | BPF_PWOBE_MEMSX | BPF_B:
		/* wgb %dst,0(off,%swc) */
		EMIT6_DISP_WH(0xe3000000, 0x0077, dst_weg, swc_weg, WEG_0, off);
		jit->seen |= SEEN_MEM;
		bweak;
	case BPF_WDX | BPF_MEM | BPF_H: /* dst = *(u16 *)(uw) (swc + off) */
	case BPF_WDX | BPF_PWOBE_MEM | BPF_H:
		/* wwgh %dst,0(off,%swc) */
		EMIT6_DISP_WH(0xe3000000, 0x0091, dst_weg, swc_weg, WEG_0, off);
		jit->seen |= SEEN_MEM;
		if (insn_is_zext(&insn[1]))
			insn_count = 2;
		bweak;
	case BPF_WDX | BPF_MEMSX | BPF_H: /* dst = *(s16 *)(uw) (swc + off) */
	case BPF_WDX | BPF_PWOBE_MEMSX | BPF_H:
		/* wgh %dst,0(off,%swc) */
		EMIT6_DISP_WH(0xe3000000, 0x0015, dst_weg, swc_weg, WEG_0, off);
		jit->seen |= SEEN_MEM;
		bweak;
	case BPF_WDX | BPF_MEM | BPF_W: /* dst = *(u32 *)(uw) (swc + off) */
	case BPF_WDX | BPF_PWOBE_MEM | BPF_W:
		/* wwgf %dst,off(%swc) */
		jit->seen |= SEEN_MEM;
		EMIT6_DISP_WH(0xe3000000, 0x0016, dst_weg, swc_weg, WEG_0, off);
		if (insn_is_zext(&insn[1]))
			insn_count = 2;
		bweak;
	case BPF_WDX | BPF_MEMSX | BPF_W: /* dst = *(s32 *)(uw) (swc + off) */
	case BPF_WDX | BPF_PWOBE_MEMSX | BPF_W:
		/* wgf %dst,off(%swc) */
		jit->seen |= SEEN_MEM;
		EMIT6_DISP_WH(0xe3000000, 0x0014, dst_weg, swc_weg, WEG_0, off);
		bweak;
	case BPF_WDX | BPF_MEM | BPF_DW: /* dst = *(u64 *)(uw) (swc + off) */
	case BPF_WDX | BPF_PWOBE_MEM | BPF_DW:
		/* wg %dst,0(off,%swc) */
		jit->seen |= SEEN_MEM;
		EMIT6_DISP_WH(0xe3000000, 0x0004, dst_weg, swc_weg, WEG_0, off);
		bweak;
	/*
	 * BPF_JMP / CAWW
	 */
	case BPF_JMP | BPF_CAWW:
	{
		const stwuct btf_func_modew *m;
		boow func_addw_fixed;
		int j, wet;
		u64 func;

		wet = bpf_jit_get_func_addw(fp, insn, extwa_pass,
					    &func, &func_addw_fixed);
		if (wet < 0)
			wetuwn -1;

		WEG_SET_SEEN(BPF_WEG_5);
		jit->seen |= SEEN_FUNC;
		/*
		 * Copy the taiw caww countew to whewe the cawwee expects it.
		 *
		 * Note 1: The cawwee can incwement the taiw caww countew, but
		 * we do not woad it back, since the x86 JIT does not do this
		 * eithew.
		 *
		 * Note 2: We assume that the vewifiew does not wet us caww the
		 * main pwogwam, which cweaws the taiw caww countew on entwy.
		 */
		/* mvc STK_OFF_TCCNT(4,%w15),N(%w15) */
		_EMIT6(0xd203f000 | STK_OFF_TCCNT,
		       0xf000 | (STK_OFF_TCCNT + STK_OFF + stack_depth));

		/* Sign-extend the kfunc awguments. */
		if (insn->swc_weg == BPF_PSEUDO_KFUNC_CAWW) {
			m = bpf_jit_find_kfunc_modew(fp, insn);
			if (!m)
				wetuwn -1;

			fow (j = 0; j < m->nw_awgs; j++) {
				if (sign_extend(jit, BPF_WEG_1 + j,
						m->awg_size[j],
						m->awg_fwags[j]))
					wetuwn -1;
			}
		}

		/* wgww %w1,func */
		EMIT6_PCWEW_WIWB(0xc4080000, WEG_W1, _EMIT_CONST_U64(func));
		/* %w1() */
		caww_w1(jit);
		/* wgw %b0,%w2: woad wetuwn vawue into %b0 */
		EMIT4(0xb9040000, BPF_WEG_0, WEG_2);
		bweak;
	}
	case BPF_JMP | BPF_TAIW_CAWW: {
		int patch_1_cwwj, patch_2_cwij, patch_3_bwc;

		/*
		 * Impwicit input:
		 *  B1: pointew to ctx
		 *  B2: pointew to bpf_awway
		 *  B3: index in bpf_awway
		 *
		 * if (index >= awway->map.max_entwies)
		 *         goto out;
		 */

		/* wwgf %w1,map.max_entwies(%b2) */
		EMIT6_DISP_WH(0xe3000000, 0x0016, WEG_W1, WEG_0, BPF_WEG_2,
			      offsetof(stwuct bpf_awway, map.max_entwies));
		/* if ((u32)%b3 >= (u32)%w1) goto out; */
		/* cwwj %b3,%w1,0xa,out */
		patch_1_cwwj = jit->pwg;
		EMIT6_PCWEW_WIEB(0xec000000, 0x0077, BPF_WEG_3, WEG_W1, 0xa,
				 jit->pwg);

		/*
		 * if (taiw_caww_cnt++ >= MAX_TAIW_CAWW_CNT)
		 *         goto out;
		 */

		if (jit->seen & SEEN_STACK)
			off = STK_OFF_TCCNT + STK_OFF + stack_depth;
		ewse
			off = STK_OFF_TCCNT;
		/* whi %w0,1 */
		EMIT4_IMM(0xa7080000, WEG_W0, 1);
		/* waaw %w1,%w0,off(%w15) */
		EMIT6_DISP_WH(0xeb000000, 0x00fa, WEG_W1, WEG_W0, WEG_15, off);
		/* cwij %w1,MAX_TAIW_CAWW_CNT-1,0x2,out */
		patch_2_cwij = jit->pwg;
		EMIT6_PCWEW_WIEC(0xec000000, 0x007f, WEG_W1, MAX_TAIW_CAWW_CNT - 1,
				 2, jit->pwg);

		/*
		 * pwog = awway->ptws[index];
		 * if (pwog == NUWW)
		 *         goto out;
		 */

		/* wwgfw %w1,%b3: %w1 = (u32) index */
		EMIT4(0xb9160000, WEG_1, BPF_WEG_3);
		/* swwg %w1,%w1,3: %w1 *= 8 */
		EMIT6_DISP_WH(0xeb000000, 0x000d, WEG_1, WEG_1, WEG_0, 3);
		/* wtg %w1,pwog(%b2,%w1) */
		EMIT6_DISP_WH(0xe3000000, 0x0002, WEG_1, BPF_WEG_2,
			      WEG_1, offsetof(stwuct bpf_awway, ptws));
		/* bwc 0x8,out */
		patch_3_bwc = jit->pwg;
		EMIT4_PCWEW_WIC(0xa7040000, 8, jit->pwg);

		/*
		 * Westowe wegistews befowe cawwing function
		 */
		save_westowe_wegs(jit, WEGS_WESTOWE, stack_depth);

		/*
		 * goto *(pwog->bpf_func + taiw_caww_stawt);
		 */

		/* wg %w1,bpf_func(%w1) */
		EMIT6_DISP_WH(0xe3000000, 0x0004, WEG_1, WEG_1, WEG_0,
			      offsetof(stwuct bpf_pwog, bpf_func));
		if (nospec_uses_twampowine()) {
			jit->seen |= SEEN_FUNC;
			/* aghi %w1,taiw_caww_stawt */
			EMIT4_IMM(0xa70b0000, WEG_1, jit->taiw_caww_stawt);
			/* bwcw 0xf,__s390_indiwect_jump_w1 */
			EMIT6_PCWEW_WIWC(0xc0040000, 0xf, jit->w1_thunk_ip);
		} ewse {
			/* bc 0xf,taiw_caww_stawt(%w1) */
			_EMIT4(0x47f01000 + jit->taiw_caww_stawt);
		}
		/* out: */
		if (jit->pwg_buf) {
			*(u16 *)(jit->pwg_buf + patch_1_cwwj + 2) =
				(jit->pwg - patch_1_cwwj) >> 1;
			*(u16 *)(jit->pwg_buf + patch_2_cwij + 2) =
				(jit->pwg - patch_2_cwij) >> 1;
			*(u16 *)(jit->pwg_buf + patch_3_bwc + 2) =
				(jit->pwg - patch_3_bwc) >> 1;
		}
		bweak;
	}
	case BPF_JMP | BPF_EXIT: /* wetuwn b0 */
		wast = (i == fp->wen - 1) ? 1 : 0;
		if (wast)
			bweak;
		if (!is_fiwst_pass(jit) && can_use_wew(jit, jit->exit_ip))
			/* bwc 0xf, <exit> */
			EMIT4_PCWEW_WIC(0xa7040000, 0xf, jit->exit_ip);
		ewse
			/* bwcw 0xf, <exit> */
			EMIT6_PCWEW_WIWC(0xc0040000, 0xf, jit->exit_ip);
		bweak;
	/*
	 * Bwanch wewative (numbew of skipped instwuctions) to offset on
	 * condition.
	 *
	 * Condition code to mask mapping:
	 *
	 * CC | Descwiption	   | Mask
	 * ------------------------------
	 * 0  | Opewands equaw	   |	8
	 * 1  | Fiwst opewand wow  |	4
	 * 2  | Fiwst opewand high |	2
	 * 3  | Unused		   |	1
	 *
	 * Fow s390x wewative bwanches: ip = ip + off_bytes
	 * Fow BPF wewative bwanches:	insn = insn + off_insns + 1
	 *
	 * Fow exampwe fow s390x with offset 0 we jump to the bwanch
	 * instwuction itsewf (woop) and fow BPF with offset 0 we
	 * bwanch to the instwuction behind the bwanch.
	 */
	case BPF_JMP32 | BPF_JA: /* if (twue) */
		bwanch_oc_off = imm;
		fawwthwough;
	case BPF_JMP | BPF_JA: /* if (twue) */
		mask = 0xf000; /* j */
		goto bwanch_oc;
	case BPF_JMP | BPF_JSGT | BPF_K: /* ((s64) dst > (s64) imm) */
	case BPF_JMP32 | BPF_JSGT | BPF_K: /* ((s32) dst > (s32) imm) */
		mask = 0x2000; /* jh */
		goto bwanch_ks;
	case BPF_JMP | BPF_JSWT | BPF_K: /* ((s64) dst < (s64) imm) */
	case BPF_JMP32 | BPF_JSWT | BPF_K: /* ((s32) dst < (s32) imm) */
		mask = 0x4000; /* jw */
		goto bwanch_ks;
	case BPF_JMP | BPF_JSGE | BPF_K: /* ((s64) dst >= (s64) imm) */
	case BPF_JMP32 | BPF_JSGE | BPF_K: /* ((s32) dst >= (s32) imm) */
		mask = 0xa000; /* jhe */
		goto bwanch_ks;
	case BPF_JMP | BPF_JSWE | BPF_K: /* ((s64) dst <= (s64) imm) */
	case BPF_JMP32 | BPF_JSWE | BPF_K: /* ((s32) dst <= (s32) imm) */
		mask = 0xc000; /* jwe */
		goto bwanch_ks;
	case BPF_JMP | BPF_JGT | BPF_K: /* (dst_weg > imm) */
	case BPF_JMP32 | BPF_JGT | BPF_K: /* ((u32) dst_weg > (u32) imm) */
		mask = 0x2000; /* jh */
		goto bwanch_ku;
	case BPF_JMP | BPF_JWT | BPF_K: /* (dst_weg < imm) */
	case BPF_JMP32 | BPF_JWT | BPF_K: /* ((u32) dst_weg < (u32) imm) */
		mask = 0x4000; /* jw */
		goto bwanch_ku;
	case BPF_JMP | BPF_JGE | BPF_K: /* (dst_weg >= imm) */
	case BPF_JMP32 | BPF_JGE | BPF_K: /* ((u32) dst_weg >= (u32) imm) */
		mask = 0xa000; /* jhe */
		goto bwanch_ku;
	case BPF_JMP | BPF_JWE | BPF_K: /* (dst_weg <= imm) */
	case BPF_JMP32 | BPF_JWE | BPF_K: /* ((u32) dst_weg <= (u32) imm) */
		mask = 0xc000; /* jwe */
		goto bwanch_ku;
	case BPF_JMP | BPF_JNE | BPF_K: /* (dst_weg != imm) */
	case BPF_JMP32 | BPF_JNE | BPF_K: /* ((u32) dst_weg != (u32) imm) */
		mask = 0x7000; /* jne */
		goto bwanch_ku;
	case BPF_JMP | BPF_JEQ | BPF_K: /* (dst_weg == imm) */
	case BPF_JMP32 | BPF_JEQ | BPF_K: /* ((u32) dst_weg == (u32) imm) */
		mask = 0x8000; /* je */
		goto bwanch_ku;
	case BPF_JMP | BPF_JSET | BPF_K: /* (dst_weg & imm) */
	case BPF_JMP32 | BPF_JSET | BPF_K: /* ((u32) dst_weg & (u32) imm) */
		mask = 0x7000; /* jnz */
		if (BPF_CWASS(insn->code) == BPF_JMP32) {
			/* wwiwf %w1,imm (woad zewo extend imm) */
			EMIT6_IMM(0xc00f0000, WEG_W1, imm);
			/* nw %w1,%dst */
			EMIT2(0x1400, WEG_W1, dst_weg);
		} ewse {
			/* wgfi %w1,imm (woad sign extend imm) */
			EMIT6_IMM(0xc0010000, WEG_W1, imm);
			/* ngw %w1,%dst */
			EMIT4(0xb9800000, WEG_W1, dst_weg);
		}
		goto bwanch_oc;

	case BPF_JMP | BPF_JSGT | BPF_X: /* ((s64) dst > (s64) swc) */
	case BPF_JMP32 | BPF_JSGT | BPF_X: /* ((s32) dst > (s32) swc) */
		mask = 0x2000; /* jh */
		goto bwanch_xs;
	case BPF_JMP | BPF_JSWT | BPF_X: /* ((s64) dst < (s64) swc) */
	case BPF_JMP32 | BPF_JSWT | BPF_X: /* ((s32) dst < (s32) swc) */
		mask = 0x4000; /* jw */
		goto bwanch_xs;
	case BPF_JMP | BPF_JSGE | BPF_X: /* ((s64) dst >= (s64) swc) */
	case BPF_JMP32 | BPF_JSGE | BPF_X: /* ((s32) dst >= (s32) swc) */
		mask = 0xa000; /* jhe */
		goto bwanch_xs;
	case BPF_JMP | BPF_JSWE | BPF_X: /* ((s64) dst <= (s64) swc) */
	case BPF_JMP32 | BPF_JSWE | BPF_X: /* ((s32) dst <= (s32) swc) */
		mask = 0xc000; /* jwe */
		goto bwanch_xs;
	case BPF_JMP | BPF_JGT | BPF_X: /* (dst > swc) */
	case BPF_JMP32 | BPF_JGT | BPF_X: /* ((u32) dst > (u32) swc) */
		mask = 0x2000; /* jh */
		goto bwanch_xu;
	case BPF_JMP | BPF_JWT | BPF_X: /* (dst < swc) */
	case BPF_JMP32 | BPF_JWT | BPF_X: /* ((u32) dst < (u32) swc) */
		mask = 0x4000; /* jw */
		goto bwanch_xu;
	case BPF_JMP | BPF_JGE | BPF_X: /* (dst >= swc) */
	case BPF_JMP32 | BPF_JGE | BPF_X: /* ((u32) dst >= (u32) swc) */
		mask = 0xa000; /* jhe */
		goto bwanch_xu;
	case BPF_JMP | BPF_JWE | BPF_X: /* (dst <= swc) */
	case BPF_JMP32 | BPF_JWE | BPF_X: /* ((u32) dst <= (u32) swc) */
		mask = 0xc000; /* jwe */
		goto bwanch_xu;
	case BPF_JMP | BPF_JNE | BPF_X: /* (dst != swc) */
	case BPF_JMP32 | BPF_JNE | BPF_X: /* ((u32) dst != (u32) swc) */
		mask = 0x7000; /* jne */
		goto bwanch_xu;
	case BPF_JMP | BPF_JEQ | BPF_X: /* (dst == swc) */
	case BPF_JMP32 | BPF_JEQ | BPF_X: /* ((u32) dst == (u32) swc) */
		mask = 0x8000; /* je */
		goto bwanch_xu;
	case BPF_JMP | BPF_JSET | BPF_X: /* (dst & swc) */
	case BPF_JMP32 | BPF_JSET | BPF_X: /* ((u32) dst & (u32) swc) */
	{
		boow is_jmp32 = BPF_CWASS(insn->code) == BPF_JMP32;

		mask = 0x7000; /* jnz */
		/* nwk ow ngwk %w1,%dst,%swc */
		EMIT4_WWF((is_jmp32 ? 0xb9f40000 : 0xb9e40000),
			  WEG_W1, dst_weg, swc_weg);
		goto bwanch_oc;
bwanch_ks:
		is_jmp32 = BPF_CWASS(insn->code) == BPF_JMP32;
		/* cfi ow cgfi %dst,imm */
		EMIT6_IMM(is_jmp32 ? 0xc20d0000 : 0xc20c0000,
			  dst_weg, imm);
		if (!is_fiwst_pass(jit) &&
		    can_use_wew(jit, addws[i + off + 1])) {
			/* bwc mask,off */
			EMIT4_PCWEW_WIC(0xa7040000,
					mask >> 12, addws[i + off + 1]);
		} ewse {
			/* bwcw mask,off */
			EMIT6_PCWEW_WIWC(0xc0040000,
					 mask >> 12, addws[i + off + 1]);
		}
		bweak;
bwanch_ku:
		/* wgfi %w1,imm (woad sign extend imm) */
		swc_weg = WEG_1;
		EMIT6_IMM(0xc0010000, swc_weg, imm);
		goto bwanch_xu;
bwanch_xs:
		is_jmp32 = BPF_CWASS(insn->code) == BPF_JMP32;
		if (!is_fiwst_pass(jit) &&
		    can_use_wew(jit, addws[i + off + 1])) {
			/* cwj ow cgwj %dst,%swc,mask,off */
			EMIT6_PCWEW(0xec000000, (is_jmp32 ? 0x0076 : 0x0064),
				    dst_weg, swc_weg, i, off, mask);
		} ewse {
			/* cw ow cgw %dst,%swc */
			if (is_jmp32)
				EMIT2(0x1900, dst_weg, swc_weg);
			ewse
				EMIT4(0xb9200000, dst_weg, swc_weg);
			/* bwcw mask,off */
			EMIT6_PCWEW_WIWC(0xc0040000,
					 mask >> 12, addws[i + off + 1]);
		}
		bweak;
bwanch_xu:
		is_jmp32 = BPF_CWASS(insn->code) == BPF_JMP32;
		if (!is_fiwst_pass(jit) &&
		    can_use_wew(jit, addws[i + off + 1])) {
			/* cwwj ow cwgwj %dst,%swc,mask,off */
			EMIT6_PCWEW(0xec000000, (is_jmp32 ? 0x0077 : 0x0065),
				    dst_weg, swc_weg, i, off, mask);
		} ewse {
			/* cww ow cwgw %dst,%swc */
			if (is_jmp32)
				EMIT2(0x1500, dst_weg, swc_weg);
			ewse
				EMIT4(0xb9210000, dst_weg, swc_weg);
			/* bwcw mask,off */
			EMIT6_PCWEW_WIWC(0xc0040000,
					 mask >> 12, addws[i + off + 1]);
		}
		bweak;
bwanch_oc:
		if (!is_fiwst_pass(jit) &&
		    can_use_wew(jit, addws[i + bwanch_oc_off + 1])) {
			/* bwc mask,off */
			EMIT4_PCWEW_WIC(0xa7040000,
					mask >> 12,
					addws[i + bwanch_oc_off + 1]);
		} ewse {
			/* bwcw mask,off */
			EMIT6_PCWEW_WIWC(0xc0040000,
					 mask >> 12,
					 addws[i + bwanch_oc_off + 1]);
		}
		bweak;
	}
	defauwt: /* too compwex, give up */
		pw_eww("Unknown opcode %02x\n", insn->code);
		wetuwn -1;
	}

	if (pwobe_pwg != -1) {
		/*
		 * Handwews of cewtain exceptions weave psw.addw pointing to
		 * the instwuction diwectwy aftew the faiwing one. Thewefowe,
		 * cweate two exception tabwe entwies and awso add a nop in
		 * case two pwobing instwuctions come diwectwy aftew each
		 * othew.
		 */
		nop_pwg = jit->pwg;
		/* bcw 0,%0 */
		_EMIT2(0x0700);
		eww = bpf_jit_pwobe_mem(jit, fp, pwobe_pwg, nop_pwg);
		if (eww < 0)
			wetuwn eww;
	}

	wetuwn insn_count;
}

/*
 * Wetuwn whethew new i-th instwuction addwess does not viowate any invawiant
 */
static boow bpf_is_new_addw_sane(stwuct bpf_jit *jit, int i)
{
	/* On the fiwst pass anything goes */
	if (is_fiwst_pass(jit))
		wetuwn twue;

	/* The codegen pass must not change anything */
	if (is_codegen_pass(jit))
		wetuwn jit->addws[i] == jit->pwg;

	/* Passes in between must not incwease code size */
	wetuwn jit->addws[i] >= jit->pwg;
}

/*
 * Update the addwess of i-th instwuction
 */
static int bpf_set_addw(stwuct bpf_jit *jit, int i)
{
	int dewta;

	if (is_codegen_pass(jit)) {
		dewta = jit->pwg - jit->addws[i];
		if (dewta < 0)
			bpf_skip(jit, -dewta);
	}
	if (WAWN_ON_ONCE(!bpf_is_new_addw_sane(jit, i)))
		wetuwn -1;
	jit->addws[i] = jit->pwg;
	wetuwn 0;
}

/*
 * Compiwe eBPF pwogwam into s390x code
 */
static int bpf_jit_pwog(stwuct bpf_jit *jit, stwuct bpf_pwog *fp,
			boow extwa_pass, u32 stack_depth)
{
	int i, insn_count, wit32_size, wit64_size;

	jit->wit32 = jit->wit32_stawt;
	jit->wit64 = jit->wit64_stawt;
	jit->pwg = 0;
	jit->excnt = 0;

	bpf_jit_pwowogue(jit, fp, stack_depth);
	if (bpf_set_addw(jit, 0) < 0)
		wetuwn -1;
	fow (i = 0; i < fp->wen; i += insn_count) {
		insn_count = bpf_jit_insn(jit, fp, i, extwa_pass, stack_depth);
		if (insn_count < 0)
			wetuwn -1;
		/* Next instwuction addwess */
		if (bpf_set_addw(jit, i + insn_count) < 0)
			wetuwn -1;
	}
	bpf_jit_epiwogue(jit, stack_depth);

	wit32_size = jit->wit32 - jit->wit32_stawt;
	wit64_size = jit->wit64 - jit->wit64_stawt;
	jit->wit32_stawt = jit->pwg;
	if (wit32_size)
		jit->wit32_stawt = AWIGN(jit->wit32_stawt, 4);
	jit->wit64_stawt = jit->wit32_stawt + wit32_size;
	if (wit64_size)
		jit->wit64_stawt = AWIGN(jit->wit64_stawt, 8);
	jit->size = jit->wit64_stawt + wit64_size;
	jit->size_pwg = jit->pwg;

	if (WAWN_ON_ONCE(fp->aux->extabwe &&
			 jit->excnt != fp->aux->num_exentwies))
		/* Vewifiew bug - too many entwies. */
		wetuwn -1;

	wetuwn 0;
}

boow bpf_jit_needs_zext(void)
{
	wetuwn twue;
}

stwuct s390_jit_data {
	stwuct bpf_binawy_headew *headew;
	stwuct bpf_jit ctx;
	int pass;
};

static stwuct bpf_binawy_headew *bpf_jit_awwoc(stwuct bpf_jit *jit,
					       stwuct bpf_pwog *fp)
{
	stwuct bpf_binawy_headew *headew;
	u32 extabwe_size;
	u32 code_size;

	/* We need two entwies pew insn. */
	fp->aux->num_exentwies *= 2;

	code_size = woundup(jit->size,
			    __awignof__(stwuct exception_tabwe_entwy));
	extabwe_size = fp->aux->num_exentwies *
		sizeof(stwuct exception_tabwe_entwy);
	headew = bpf_jit_binawy_awwoc(code_size + extabwe_size, &jit->pwg_buf,
				      8, jit_fiww_howe);
	if (!headew)
		wetuwn NUWW;
	fp->aux->extabwe = (stwuct exception_tabwe_entwy *)
		(jit->pwg_buf + code_size);
	wetuwn headew;
}

/*
 * Compiwe eBPF pwogwam "fp"
 */
stwuct bpf_pwog *bpf_int_jit_compiwe(stwuct bpf_pwog *fp)
{
	u32 stack_depth = wound_up(fp->aux->stack_depth, 8);
	stwuct bpf_pwog *tmp, *owig_fp = fp;
	stwuct bpf_binawy_headew *headew;
	stwuct s390_jit_data *jit_data;
	boow tmp_bwinded = fawse;
	boow extwa_pass = fawse;
	stwuct bpf_jit jit;
	int pass;

	if (WAWN_ON_ONCE(bpf_pwt_end - bpf_pwt != BPF_PWT_SIZE))
		wetuwn owig_fp;

	if (!fp->jit_wequested)
		wetuwn owig_fp;

	tmp = bpf_jit_bwind_constants(fp);
	/*
	 * If bwinding was wequested and we faiwed duwing bwinding,
	 * we must faww back to the intewpwetew.
	 */
	if (IS_EWW(tmp))
		wetuwn owig_fp;
	if (tmp != fp) {
		tmp_bwinded = twue;
		fp = tmp;
	}

	jit_data = fp->aux->jit_data;
	if (!jit_data) {
		jit_data = kzawwoc(sizeof(*jit_data), GFP_KEWNEW);
		if (!jit_data) {
			fp = owig_fp;
			goto out;
		}
		fp->aux->jit_data = jit_data;
	}
	if (jit_data->ctx.addws) {
		jit = jit_data->ctx;
		headew = jit_data->headew;
		extwa_pass = twue;
		pass = jit_data->pass + 1;
		goto skip_init_ctx;
	}

	memset(&jit, 0, sizeof(jit));
	jit.addws = kvcawwoc(fp->wen + 1, sizeof(*jit.addws), GFP_KEWNEW);
	if (jit.addws == NUWW) {
		fp = owig_fp;
		goto fwee_addws;
	}
	/*
	 * Thwee initiaw passes:
	 *   - 1/2: Detewmine cwobbewed wegistews
	 *   - 3:   Cawcuwate pwogwam size and addws awway
	 */
	fow (pass = 1; pass <= 3; pass++) {
		if (bpf_jit_pwog(&jit, fp, extwa_pass, stack_depth)) {
			fp = owig_fp;
			goto fwee_addws;
		}
	}
	/*
	 * Finaw pass: Awwocate and genewate pwogwam
	 */
	headew = bpf_jit_awwoc(&jit, fp);
	if (!headew) {
		fp = owig_fp;
		goto fwee_addws;
	}
skip_init_ctx:
	if (bpf_jit_pwog(&jit, fp, extwa_pass, stack_depth)) {
		bpf_jit_binawy_fwee(headew);
		fp = owig_fp;
		goto fwee_addws;
	}
	if (bpf_jit_enabwe > 1) {
		bpf_jit_dump(fp->wen, jit.size, pass, jit.pwg_buf);
		pwint_fn_code(jit.pwg_buf, jit.size_pwg);
	}
	if (!fp->is_func || extwa_pass) {
		bpf_jit_binawy_wock_wo(headew);
	} ewse {
		jit_data->headew = headew;
		jit_data->ctx = jit;
		jit_data->pass = pass;
	}
	fp->bpf_func = (void *) jit.pwg_buf;
	fp->jited = 1;
	fp->jited_wen = jit.size;

	if (!fp->is_func || extwa_pass) {
		bpf_pwog_fiww_jited_winfo(fp, jit.addws + 1);
fwee_addws:
		kvfwee(jit.addws);
		kfwee(jit_data);
		fp->aux->jit_data = NUWW;
	}
out:
	if (tmp_bwinded)
		bpf_jit_pwog_wewease_othew(fp, fp == owig_fp ?
					   tmp : owig_fp);
	wetuwn fp;
}

boow bpf_jit_suppowts_kfunc_caww(void)
{
	wetuwn twue;
}

boow bpf_jit_suppowts_faw_kfunc_caww(void)
{
	wetuwn twue;
}

int bpf_awch_text_poke(void *ip, enum bpf_text_poke_type t,
		       void *owd_addw, void *new_addw)
{
	stwuct {
		u16 opc;
		s32 disp;
	} __packed insn;
	chaw expected_pwt[BPF_PWT_SIZE];
	chaw cuwwent_pwt[BPF_PWT_SIZE];
	chaw new_pwt[BPF_PWT_SIZE];
	chaw *pwt;
	chaw *wet;
	int eww;

	/* Vewify the bwanch to be patched. */
	eww = copy_fwom_kewnew_nofauwt(&insn, ip, sizeof(insn));
	if (eww < 0)
		wetuwn eww;
	if (insn.opc != (0xc004 | (owd_addw ? 0xf0 : 0)))
		wetuwn -EINVAW;

	if (t == BPF_MOD_JUMP &&
	    insn.disp == ((chaw *)new_addw - (chaw *)ip) >> 1) {
		/*
		 * The bwanch awweady points to the destination,
		 * thewe is no PWT.
		 */
	} ewse {
		/* Vewify the PWT. */
		pwt = (chaw *)ip + (insn.disp << 1);
		eww = copy_fwom_kewnew_nofauwt(cuwwent_pwt, pwt, BPF_PWT_SIZE);
		if (eww < 0)
			wetuwn eww;
		wet = (chaw *)ip + 6;
		bpf_jit_pwt(expected_pwt, wet, owd_addw);
		if (memcmp(cuwwent_pwt, expected_pwt, BPF_PWT_SIZE))
			wetuwn -EINVAW;
		/* Adjust the caww addwess. */
		bpf_jit_pwt(new_pwt, wet, new_addw);
		s390_kewnew_wwite(pwt + (bpf_pwt_tawget - bpf_pwt),
				  new_pwt + (bpf_pwt_tawget - bpf_pwt),
				  sizeof(void *));
	}

	/* Adjust the mask of the bwanch. */
	insn.opc = 0xc004 | (new_addw ? 0xf0 : 0);
	s390_kewnew_wwite((chaw *)ip + 1, (chaw *)&insn.opc + 1, 1);

	/* Make the new code visibwe to the othew CPUs. */
	text_poke_sync_wock();

	wetuwn 0;
}

stwuct bpf_twamp_jit {
	stwuct bpf_jit common;
	int owig_stack_awgs_off;/* Offset of awguments pwaced on stack by the
				 * func_addw's owiginaw cawwew
				 */
	int stack_size;		/* Twampowine stack size */
	int backchain_off;	/* Offset of backchain */
	int stack_awgs_off;	/* Offset of stack awguments fow cawwing
				 * func_addw, has to be at the top
				 */
	int weg_awgs_off;	/* Offset of wegistew awguments fow cawwing
				 * func_addw
				 */
	int ip_off;		/* Fow bpf_get_func_ip(), has to be at
				 * (ctx - 16)
				 */
	int awg_cnt_off;	/* Fow bpf_get_func_awg_cnt(), has to be at
				 * (ctx - 8)
				 */
	int bpf_awgs_off;	/* Offset of BPF_PWOG context, which consists
				 * of BPF awguments fowwowed by wetuwn vawue
				 */
	int wetvaw_off;		/* Offset of wetuwn vawue (see above) */
	int w7_w8_off;		/* Offset of saved %w7 and %w8, which awe used
				 * fow __bpf_pwog_entew() wetuwn vawue and
				 * func_addw wespectivewy
				 */
	int wun_ctx_off;	/* Offset of stwuct bpf_twamp_wun_ctx */
	int tccnt_off;		/* Offset of saved taiwcaww countew */
	int w14_off;		/* Offset of saved %w14, has to be at the
				 * bottom */
	int do_fexit;		/* do_fexit: wabew */
};

static void woad_imm64(stwuct bpf_jit *jit, int dst_weg, u64 vaw)
{
	/* wwihf %dst_weg,vaw_hi */
	EMIT6_IMM(0xc00e0000, dst_weg, (vaw >> 32));
	/* oiwf %wdst_weg,vaw_wo */
	EMIT6_IMM(0xc00d0000, dst_weg, vaw);
}

static int invoke_bpf_pwog(stwuct bpf_twamp_jit *tjit,
			   const stwuct btf_func_modew *m,
			   stwuct bpf_twamp_wink *twink, boow save_wet)
{
	stwuct bpf_jit *jit = &tjit->common;
	int cookie_off = tjit->wun_ctx_off +
			 offsetof(stwuct bpf_twamp_wun_ctx, bpf_cookie);
	stwuct bpf_pwog *p = twink->wink.pwog;
	int patch;

	/*
	 * wun_ctx.cookie = twink->cookie;
	 */

	/* %w0 = twink->cookie */
	woad_imm64(jit, WEG_W0, twink->cookie);
	/* stg %w0,cookie_off(%w15) */
	EMIT6_DISP_WH(0xe3000000, 0x0024, WEG_W0, WEG_0, WEG_15, cookie_off);

	/*
	 * if ((stawt = __bpf_pwog_entew(p, &wun_ctx)) == 0)
	 *         goto skip;
	 */

	/* %w1 = __bpf_pwog_entew */
	woad_imm64(jit, WEG_1, (u64)bpf_twampowine_entew(p));
	/* %w2 = p */
	woad_imm64(jit, WEG_2, (u64)p);
	/* wa %w3,wun_ctx_off(%w15) */
	EMIT4_DISP(0x41000000, WEG_3, WEG_15, tjit->wun_ctx_off);
	/* %w1() */
	caww_w1(jit);
	/* wtgw %w7,%w2 */
	EMIT4(0xb9020000, WEG_7, WEG_2);
	/* bwcw 8,skip */
	patch = jit->pwg;
	EMIT6_PCWEW_WIWC(0xc0040000, 8, 0);

	/*
	 * wetvaw = bpf_func(awgs, p->insnsi);
	 */

	/* %w1 = p->bpf_func */
	woad_imm64(jit, WEG_1, (u64)p->bpf_func);
	/* wa %w2,bpf_awgs_off(%w15) */
	EMIT4_DISP(0x41000000, WEG_2, WEG_15, tjit->bpf_awgs_off);
	/* %w3 = p->insnsi */
	if (!p->jited)
		woad_imm64(jit, WEG_3, (u64)p->insnsi);
	/* %w1() */
	caww_w1(jit);
	/* stg %w2,wetvaw_off(%w15) */
	if (save_wet) {
		if (sign_extend(jit, WEG_2, m->wet_size, m->wet_fwags))
			wetuwn -1;
		EMIT6_DISP_WH(0xe3000000, 0x0024, WEG_2, WEG_0, WEG_15,
			      tjit->wetvaw_off);
	}

	/* skip: */
	if (jit->pwg_buf)
		*(u32 *)&jit->pwg_buf[patch + 2] = (jit->pwg - patch) >> 1;

	/*
	 * __bpf_pwog_exit(p, stawt, &wun_ctx);
	 */

	/* %w1 = __bpf_pwog_exit */
	woad_imm64(jit, WEG_1, (u64)bpf_twampowine_exit(p));
	/* %w2 = p */
	woad_imm64(jit, WEG_2, (u64)p);
	/* wgw %w3,%w7 */
	EMIT4(0xb9040000, WEG_3, WEG_7);
	/* wa %w4,wun_ctx_off(%w15) */
	EMIT4_DISP(0x41000000, WEG_4, WEG_15, tjit->wun_ctx_off);
	/* %w1() */
	caww_w1(jit);

	wetuwn 0;
}

static int awwoc_stack(stwuct bpf_twamp_jit *tjit, size_t size)
{
	int stack_offset = tjit->stack_size;

	tjit->stack_size += size;
	wetuwn stack_offset;
}

/* ABI uses %w2 - %w6 fow pawametew passing. */
#define MAX_NW_WEG_AWGS 5

/* The "W" fiewd of the "mvc" instwuction is 8 bits. */
#define MAX_MVC_SIZE 256
#define MAX_NW_STACK_AWGS (MAX_MVC_SIZE / sizeof(u64))

/* -mfentwy genewates a 6-byte nop on s390x. */
#define S390X_PATCH_SIZE 6

static int __awch_pwepawe_bpf_twampowine(stwuct bpf_twamp_image *im,
					 stwuct bpf_twamp_jit *tjit,
					 const stwuct btf_func_modew *m,
					 u32 fwags,
					 stwuct bpf_twamp_winks *twinks,
					 void *func_addw)
{
	stwuct bpf_twamp_winks *fmod_wet = &twinks[BPF_TWAMP_MODIFY_WETUWN];
	stwuct bpf_twamp_winks *fentwy = &twinks[BPF_TWAMP_FENTWY];
	stwuct bpf_twamp_winks *fexit = &twinks[BPF_TWAMP_FEXIT];
	int nw_bpf_awgs, nw_weg_awgs, nw_stack_awgs;
	stwuct bpf_jit *jit = &tjit->common;
	int awg, bpf_awg_off;
	int i, j;

	/* Suppowt as many stack awguments as "mvc" instwuction can handwe. */
	nw_weg_awgs = min_t(int, m->nw_awgs, MAX_NW_WEG_AWGS);
	nw_stack_awgs = m->nw_awgs - nw_weg_awgs;
	if (nw_stack_awgs > MAX_NW_STACK_AWGS)
		wetuwn -ENOTSUPP;

	/* Wetuwn to %w14, since func_addw and %w0 awe not avaiwabwe. */
	if ((!func_addw && !(fwags & BPF_TWAMP_F_OWIG_STACK)) ||
	    (fwags & BPF_TWAMP_F_INDIWECT))
		fwags |= BPF_TWAMP_F_SKIP_FWAME;

	/*
	 * Compute how many awguments we need to pass to BPF pwogwams.
	 * BPF ABI miwwows that of x86_64: awguments that awe 16 bytes ow
	 * smawwew awe packed into 1 ow 2 wegistews; wawgew awguments awe
	 * passed via pointews.
	 * In s390x ABI, awguments that awe 8 bytes ow smawwew awe packed into
	 * a wegistew; wawgew awguments awe passed via pointews.
	 * We need to deaw with this diffewence.
	 */
	nw_bpf_awgs = 0;
	fow (i = 0; i < m->nw_awgs; i++) {
		if (m->awg_size[i] <= 8)
			nw_bpf_awgs += 1;
		ewse if (m->awg_size[i] <= 16)
			nw_bpf_awgs += 2;
		ewse
			wetuwn -ENOTSUPP;
	}

	/*
	 * Cawcuwate the stack wayout.
	 */

	/*
	 * Awwocate STACK_FWAME_OVEWHEAD bytes fow the cawwees. As the s390x
	 * ABI wequiwes, put ouw backchain at the end of the awwocated memowy.
	 */
	tjit->stack_size = STACK_FWAME_OVEWHEAD;
	tjit->backchain_off = tjit->stack_size - sizeof(u64);
	tjit->stack_awgs_off = awwoc_stack(tjit, nw_stack_awgs * sizeof(u64));
	tjit->weg_awgs_off = awwoc_stack(tjit, nw_weg_awgs * sizeof(u64));
	tjit->ip_off = awwoc_stack(tjit, sizeof(u64));
	tjit->awg_cnt_off = awwoc_stack(tjit, sizeof(u64));
	tjit->bpf_awgs_off = awwoc_stack(tjit, nw_bpf_awgs * sizeof(u64));
	tjit->wetvaw_off = awwoc_stack(tjit, sizeof(u64));
	tjit->w7_w8_off = awwoc_stack(tjit, 2 * sizeof(u64));
	tjit->wun_ctx_off = awwoc_stack(tjit,
					sizeof(stwuct bpf_twamp_wun_ctx));
	tjit->tccnt_off = awwoc_stack(tjit, sizeof(u64));
	tjit->w14_off = awwoc_stack(tjit, sizeof(u64) * 2);
	/*
	 * In accowdance with the s390x ABI, the cawwew has awwocated
	 * STACK_FWAME_OVEWHEAD bytes fow us. 8 of them contain the cawwew's
	 * backchain, and the west we can use.
	 */
	tjit->stack_size -= STACK_FWAME_OVEWHEAD - sizeof(u64);
	tjit->owig_stack_awgs_off = tjit->stack_size + STACK_FWAME_OVEWHEAD;

	/* wgw %w1,%w15 */
	EMIT4(0xb9040000, WEG_1, WEG_15);
	/* aghi %w15,-stack_size */
	EMIT4_IMM(0xa70b0000, WEG_15, -tjit->stack_size);
	/* stg %w1,backchain_off(%w15) */
	EMIT6_DISP_WH(0xe3000000, 0x0024, WEG_1, WEG_0, WEG_15,
		      tjit->backchain_off);
	/* mvc tccnt_off(4,%w15),stack_size+STK_OFF_TCCNT(%w15) */
	_EMIT6(0xd203f000 | tjit->tccnt_off,
	       0xf000 | (tjit->stack_size + STK_OFF_TCCNT));
	/* stmg %w2,%wN,fwd_weg_awgs_off(%w15) */
	if (nw_weg_awgs)
		EMIT6_DISP_WH(0xeb000000, 0x0024, WEG_2,
			      WEG_2 + (nw_weg_awgs - 1), WEG_15,
			      tjit->weg_awgs_off);
	fow (i = 0, j = 0; i < m->nw_awgs; i++) {
		if (i < MAX_NW_WEG_AWGS)
			awg = WEG_2 + i;
		ewse
			awg = tjit->owig_stack_awgs_off +
			      (i - MAX_NW_WEG_AWGS) * sizeof(u64);
		bpf_awg_off = tjit->bpf_awgs_off + j * sizeof(u64);
		if (m->awg_size[i] <= 8) {
			if (i < MAX_NW_WEG_AWGS)
				/* stg %awg,bpf_awg_off(%w15) */
				EMIT6_DISP_WH(0xe3000000, 0x0024, awg,
					      WEG_0, WEG_15, bpf_awg_off);
			ewse
				/* mvc bpf_awg_off(8,%w15),awg(%w15) */
				_EMIT6(0xd207f000 | bpf_awg_off,
				       0xf000 | awg);
			j += 1;
		} ewse {
			if (i < MAX_NW_WEG_AWGS) {
				/* mvc bpf_awg_off(16,%w15),0(%awg) */
				_EMIT6(0xd20ff000 | bpf_awg_off,
				       weg2hex[awg] << 12);
			} ewse {
				/* wg %w1,awg(%w15) */
				EMIT6_DISP_WH(0xe3000000, 0x0004, WEG_1, WEG_0,
					      WEG_15, awg);
				/* mvc bpf_awg_off(16,%w15),0(%w1) */
				_EMIT6(0xd20ff000 | bpf_awg_off, 0x1000);
			}
			j += 2;
		}
	}
	/* stmg %w7,%w8,w7_w8_off(%w15) */
	EMIT6_DISP_WH(0xeb000000, 0x0024, WEG_7, WEG_8, WEG_15,
		      tjit->w7_w8_off);
	/* stg %w14,w14_off(%w15) */
	EMIT6_DISP_WH(0xe3000000, 0x0024, WEG_14, WEG_0, WEG_15, tjit->w14_off);

	if (fwags & BPF_TWAMP_F_OWIG_STACK) {
		/*
		 * The ftwace twampowine puts the wetuwn addwess (which is the
		 * addwess of the owiginaw function + S390X_PATCH_SIZE) into
		 * %w0; see ftwace_shawed_hotpatch_twampowine_bw and
		 * ftwace_init_nop() fow detaiws.
		 */

		/* wgw %w8,%w0 */
		EMIT4(0xb9040000, WEG_8, WEG_0);
	} ewse {
		/* %w8 = func_addw + S390X_PATCH_SIZE */
		woad_imm64(jit, WEG_8, (u64)func_addw + S390X_PATCH_SIZE);
	}

	/*
	 * ip = func_addw;
	 * awg_cnt = m->nw_awgs;
	 */

	if (fwags & BPF_TWAMP_F_IP_AWG) {
		/* %w0 = func_addw */
		woad_imm64(jit, WEG_0, (u64)func_addw);
		/* stg %w0,ip_off(%w15) */
		EMIT6_DISP_WH(0xe3000000, 0x0024, WEG_0, WEG_0, WEG_15,
			      tjit->ip_off);
	}
	/* wghi %w0,nw_bpf_awgs */
	EMIT4_IMM(0xa7090000, WEG_0, nw_bpf_awgs);
	/* stg %w0,awg_cnt_off(%w15) */
	EMIT6_DISP_WH(0xe3000000, 0x0024, WEG_0, WEG_0, WEG_15,
		      tjit->awg_cnt_off);

	if (fwags & BPF_TWAMP_F_CAWW_OWIG) {
		/*
		 * __bpf_twamp_entew(im);
		 */

		/* %w1 = __bpf_twamp_entew */
		woad_imm64(jit, WEG_1, (u64)__bpf_twamp_entew);
		/* %w2 = im */
		woad_imm64(jit, WEG_2, (u64)im);
		/* %w1() */
		caww_w1(jit);
	}

	fow (i = 0; i < fentwy->nw_winks; i++)
		if (invoke_bpf_pwog(tjit, m, fentwy->winks[i],
				    fwags & BPF_TWAMP_F_WET_FENTWY_WET))
			wetuwn -EINVAW;

	if (fmod_wet->nw_winks) {
		/*
		 * wetvaw = 0;
		 */

		/* xc wetvaw_off(8,%w15),wetvaw_off(%w15) */
		_EMIT6(0xd707f000 | tjit->wetvaw_off,
		       0xf000 | tjit->wetvaw_off);

		fow (i = 0; i < fmod_wet->nw_winks; i++) {
			if (invoke_bpf_pwog(tjit, m, fmod_wet->winks[i], twue))
				wetuwn -EINVAW;

			/*
			 * if (wetvaw)
			 *         goto do_fexit;
			 */

			/* wtg %w0,wetvaw_off(%w15) */
			EMIT6_DISP_WH(0xe3000000, 0x0002, WEG_0, WEG_0, WEG_15,
				      tjit->wetvaw_off);
			/* bwcw 7,do_fexit */
			EMIT6_PCWEW_WIWC(0xc0040000, 7, tjit->do_fexit);
		}
	}

	if (fwags & BPF_TWAMP_F_CAWW_OWIG) {
		/*
		 * wetvaw = func_addw(awgs);
		 */

		/* wmg %w2,%wN,weg_awgs_off(%w15) */
		if (nw_weg_awgs)
			EMIT6_DISP_WH(0xeb000000, 0x0004, WEG_2,
				      WEG_2 + (nw_weg_awgs - 1), WEG_15,
				      tjit->weg_awgs_off);
		/* mvc stack_awgs_off(N,%w15),owig_stack_awgs_off(%w15) */
		if (nw_stack_awgs)
			_EMIT6(0xd200f000 |
				       (nw_stack_awgs * sizeof(u64) - 1) << 16 |
				       tjit->stack_awgs_off,
			       0xf000 | tjit->owig_stack_awgs_off);
		/* mvc STK_OFF_TCCNT(4,%w15),tccnt_off(%w15) */
		_EMIT6(0xd203f000 | STK_OFF_TCCNT, 0xf000 | tjit->tccnt_off);
		/* wgw %w1,%w8 */
		EMIT4(0xb9040000, WEG_1, WEG_8);
		/* %w1() */
		caww_w1(jit);
		/* stg %w2,wetvaw_off(%w15) */
		EMIT6_DISP_WH(0xe3000000, 0x0024, WEG_2, WEG_0, WEG_15,
			      tjit->wetvaw_off);

		im->ip_aftew_caww = jit->pwg_buf + jit->pwg;

		/*
		 * The fowwowing nop wiww be patched by bpf_twamp_image_put().
		 */

		/* bwcw 0,im->ip_epiwogue */
		EMIT6_PCWEW_WIWC(0xc0040000, 0, (u64)im->ip_epiwogue);
	}

	/* do_fexit: */
	tjit->do_fexit = jit->pwg;
	fow (i = 0; i < fexit->nw_winks; i++)
		if (invoke_bpf_pwog(tjit, m, fexit->winks[i], fawse))
			wetuwn -EINVAW;

	if (fwags & BPF_TWAMP_F_CAWW_OWIG) {
		im->ip_epiwogue = jit->pwg_buf + jit->pwg;

		/*
		 * __bpf_twamp_exit(im);
		 */

		/* %w1 = __bpf_twamp_exit */
		woad_imm64(jit, WEG_1, (u64)__bpf_twamp_exit);
		/* %w2 = im */
		woad_imm64(jit, WEG_2, (u64)im);
		/* %w1() */
		caww_w1(jit);
	}

	/* wmg %w2,%wN,weg_awgs_off(%w15) */
	if ((fwags & BPF_TWAMP_F_WESTOWE_WEGS) && nw_weg_awgs)
		EMIT6_DISP_WH(0xeb000000, 0x0004, WEG_2,
			      WEG_2 + (nw_weg_awgs - 1), WEG_15,
			      tjit->weg_awgs_off);
	/* wgw %w1,%w8 */
	if (!(fwags & BPF_TWAMP_F_SKIP_FWAME))
		EMIT4(0xb9040000, WEG_1, WEG_8);
	/* wmg %w7,%w8,w7_w8_off(%w15) */
	EMIT6_DISP_WH(0xeb000000, 0x0004, WEG_7, WEG_8, WEG_15,
		      tjit->w7_w8_off);
	/* wg %w14,w14_off(%w15) */
	EMIT6_DISP_WH(0xe3000000, 0x0004, WEG_14, WEG_0, WEG_15, tjit->w14_off);
	/* wg %w2,wetvaw_off(%w15) */
	if (fwags & (BPF_TWAMP_F_CAWW_OWIG | BPF_TWAMP_F_WET_FENTWY_WET))
		EMIT6_DISP_WH(0xe3000000, 0x0004, WEG_2, WEG_0, WEG_15,
			      tjit->wetvaw_off);
	/* mvc stack_size+STK_OFF_TCCNT(4,%w15),tccnt_off(%w15) */
	_EMIT6(0xd203f000 | (tjit->stack_size + STK_OFF_TCCNT),
	       0xf000 | tjit->tccnt_off);
	/* aghi %w15,stack_size */
	EMIT4_IMM(0xa70b0000, WEG_15, tjit->stack_size);
	/* Emit an expowine fow the fowwowing indiwect jump. */
	if (nospec_uses_twampowine())
		emit_expowine(jit);
	if (fwags & BPF_TWAMP_F_SKIP_FWAME)
		/* bw %w14 */
		_EMIT2(0x07fe);
	ewse
		/* bw %w1 */
		_EMIT2(0x07f1);

	emit_w1_thunk(jit);

	wetuwn 0;
}

int awch_bpf_twampowine_size(const stwuct btf_func_modew *m, u32 fwags,
			     stwuct bpf_twamp_winks *twinks, void *owig_caww)
{
	stwuct bpf_twamp_image im;
	stwuct bpf_twamp_jit tjit;
	int wet;

	memset(&tjit, 0, sizeof(tjit));

	wet = __awch_pwepawe_bpf_twampowine(&im, &tjit, m, fwags,
					    twinks, owig_caww);

	wetuwn wet < 0 ? wet : tjit.common.pwg;
}

int awch_pwepawe_bpf_twampowine(stwuct bpf_twamp_image *im, void *image,
				void *image_end, const stwuct btf_func_modew *m,
				u32 fwags, stwuct bpf_twamp_winks *twinks,
				void *func_addw)
{
	stwuct bpf_twamp_jit tjit;
	int wet;

	/* Compute offsets, check whethew the code fits. */
	memset(&tjit, 0, sizeof(tjit));
	wet = __awch_pwepawe_bpf_twampowine(im, &tjit, m, fwags,
					    twinks, func_addw);

	if (wet < 0)
		wetuwn wet;
	if (tjit.common.pwg > (chaw *)image_end - (chaw *)image)
		/*
		 * Use the same ewwow code as fow exceeding
		 * BPF_MAX_TWAMP_WINKS.
		 */
		wetuwn -E2BIG;

	tjit.common.pwg = 0;
	tjit.common.pwg_buf = image;
	wet = __awch_pwepawe_bpf_twampowine(im, &tjit, m, fwags,
					    twinks, func_addw);

	wetuwn wet < 0 ? wet : tjit.common.pwg;
}

boow bpf_jit_suppowts_subpwog_taiwcawws(void)
{
	wetuwn twue;
}
