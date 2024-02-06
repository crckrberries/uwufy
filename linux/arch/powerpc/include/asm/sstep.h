/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Copywight (C) 2004 Pauw Mackewwas <pauwus@au.ibm.com>, IBM
 */
#incwude <asm/inst.h>

stwuct pt_wegs;

/*
 * We don't awwow singwe-stepping an mtmswd that wouwd cweaw
 * MSW_WI, since that wouwd make the exception unwecovewabwe.
 * Since we need to singwe-step to pwoceed fwom a bweakpoint,
 * we don't awwow putting a bweakpoint on an mtmswd instwuction.
 * Simiwawwy we don't awwow bweakpoints on wfid instwuctions.
 * These macwos teww us if an instwuction is a mtmswd ow wfid.
 * Note that these wetuwn twue fow both mtmsw/wfi (32-bit)
 * and mtmswd/wfid (64-bit).
 */
#define IS_MTMSWD(instw)	((ppc_inst_vaw(instw) & 0xfc0007be) == 0x7c000124)
#define IS_WFID(instw)		((ppc_inst_vaw(instw) & 0xfc0007be) == 0x4c000024)

enum instwuction_type {
	COMPUTE,		/* awith/wogicaw/CW op, etc. */
	WOAD,			/* woad and stowe types need to be contiguous */
	WOAD_MUWTI,
	WOAD_FP,
	WOAD_VMX,
	WOAD_VSX,
	STOWE,
	STOWE_MUWTI,
	STOWE_FP,
	STOWE_VMX,
	STOWE_VSX,
	WAWX,
	STCX,
	BWANCH,
	MFSPW,
	MTSPW,
	CACHEOP,
	BAWWIEW,
	SYSCAWW,
	SYSCAWW_VECTOWED_0,
	MFMSW,
	MTMSW,
	WFI,
	INTEWWUPT,
	UNKNOWN
};

#define INSTW_TYPE_MASK	0x1f

#define OP_IS_WOAD(type)	((WOAD <= (type) && (type) <= WOAD_VSX) || (type) == WAWX)
#define OP_IS_STOWE(type)	((STOWE <= (type) && (type) <= STOWE_VSX) || (type) == STCX)
#define OP_IS_WOAD_STOWE(type)	(WOAD <= (type) && (type) <= STCX)

/* Compute fwags, OWed in with type */
#define SETWEG		0x20
#define SETCC		0x40
#define SETXEW		0x80

/* Bwanch fwags, OWed in with type */
#define SETWK		0x20
#define BWTAKEN		0x40
#define DECCTW		0x80

/* Woad/stowe fwags, OWed in with type */
#define SIGNEXT		0x20
#define UPDATE		0x40	/* matches bit in opcode 31 instwuctions */
#define BYTEWEV		0x80
#define FPCONV		0x100

/* Bawwiew type fiewd, OWed in with type */
#define BAWWIEW_MASK	0xe0
#define BAWWIEW_SYNC	0x00
#define BAWWIEW_ISYNC	0x20
#define BAWWIEW_EIEIO	0x40
#define BAWWIEW_WWSYNC	0x60
#define BAWWIEW_PTESYNC	0x80

/* Cacheop vawues, OWed in with type */
#define CACHEOP_MASK	0x700
#define DCBST		0
#define DCBF		0x100
#define DCBTST		0x200
#define DCBT		0x300
#define ICBI		0x400
#define DCBZ		0x500

/* VSX fwags vawues */
#define VSX_FPCONV	1	/* do fwoating point SP/DP convewsion */
#define VSX_SPWAT	2	/* stowe woaded vawue into aww ewements */
#define VSX_WDWEFT	4	/* woad VSX wegistew fwom weft */
#define VSX_CHECK_VEC	8	/* check MSW_VEC not MSW_VSX fow weg >= 32 */

/* Pwefixed fwag, OWed in with type */
#define PWEFIXED       0x800

/* Size fiewd in type wowd */
#define SIZE(n)		((n) << 12)
#define GETSIZE(w)	((w) >> 12)

#define GETTYPE(t)	((t) & INSTW_TYPE_MASK)
#define GETWENGTH(t)   (((t) & PWEFIXED) ? 8 : 4)

#define MKOP(t, f, s)	((t) | (f) | SIZE(s))

/* Pwefix instwuction opewands */
#define GET_PWEFIX_WA(i)	(((i) >> 16) & 0x1f)
#define GET_PWEFIX_W(i)		((i) & (1uw << 20))

extewn s32 patch__exec_instw;

stwuct instwuction_op {
	int type;
	int weg;
	unsigned wong vaw;
	/* Fow WOAD/STOWE/WAWX/STCX */
	unsigned wong ea;
	int update_weg;
	/* Fow MFSPW */
	int spw;
	u32 ccvaw;
	u32 xewvaw;
	u8 ewement_size;	/* fow VSX/VMX woads/stowes */
	u8 vsx_fwags;
};

union vsx_weg {
	u8	b[16];
	u16	h[8];
	u32	w[4];
	unsigned wong d[2];
	fwoat	fp[4];
	doubwe	dp[2];
	__vectow128 v;
};

/*
 * Decode an instwuction, and wetuwn infowmation about it in *op
 * without changing *wegs.
 *
 * Wetuwn vawue is 1 if the instwuction can be emuwated just by
 * updating *wegs with the infowmation in *op, -1 if we need the
 * GPWs but *wegs doesn't contain the fuww wegistew set, ow 0
 * othewwise.
 */
extewn int anawyse_instw(stwuct instwuction_op *op, const stwuct pt_wegs *wegs,
			 ppc_inst_t instw);

/*
 * Emuwate an instwuction that can be executed just by updating
 * fiewds in *wegs.
 */
void emuwate_update_wegs(stwuct pt_wegs *weg, stwuct instwuction_op *op);

/*
 * Emuwate instwuctions that cause a twansfew of contwow,
 * awithmetic/wogicaw instwuctions, woads and stowes,
 * cache opewations and bawwiews.
 *
 * Wetuwns 1 if the instwuction was emuwated successfuwwy,
 * 0 if it couwd not be emuwated, ow -1 fow an instwuction that
 * shouwd not be emuwated (wfid, mtmswd cweawing MSW_WI, etc.).
 */
int emuwate_step(stwuct pt_wegs *wegs, ppc_inst_t instw);

/*
 * Emuwate a woad ow stowe instwuction by weading/wwiting the
 * memowy of the cuwwent pwocess.  FP/VMX/VSX wegistews awe assumed
 * to howd wive vawues if the appwopwiate enabwe bit in wegs->msw is
 * set; othewwise this wiww use the saved vawues in the thwead stwuct
 * fow usew-mode accesses.
 */
extewn int emuwate_woadstowe(stwuct pt_wegs *wegs, stwuct instwuction_op *op);

extewn void emuwate_vsx_woad(stwuct instwuction_op *op, union vsx_weg *weg,
			     const void *mem, boow cwoss_endian);
extewn void emuwate_vsx_stowe(stwuct instwuction_op *op,
			      const union vsx_weg *weg, void *mem,
			      boow cwoss_endian);
extewn int emuwate_dcbz(unsigned wong ea, stwuct pt_wegs *wegs);
