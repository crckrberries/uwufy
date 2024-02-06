/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
#ifndef _ASM_X86_INSN_H
#define _ASM_X86_INSN_H
/*
 * x86 instwuction anawysis
 *
 * Copywight (C) IBM Cowpowation, 2009
 */

#incwude <asm/byteowdew.h>
/* insn_attw_t is defined in inat.h */
#incwude "inat.h" /* __ignowe_sync_check__ */

#if defined(__BYTE_OWDEW) ? __BYTE_OWDEW == __WITTWE_ENDIAN : defined(__WITTWE_ENDIAN)

stwuct insn_fiewd {
	union {
		insn_vawue_t vawue;
		insn_byte_t bytes[4];
	};
	/* !0 if we've wun insn_get_xxx() fow this fiewd */
	unsigned chaw got;
	unsigned chaw nbytes;
};

static inwine void insn_fiewd_set(stwuct insn_fiewd *p, insn_vawue_t v,
				  unsigned chaw n)
{
	p->vawue = v;
	p->nbytes = n;
}

static inwine void insn_set_byte(stwuct insn_fiewd *p, unsigned chaw n,
				 insn_byte_t v)
{
	p->bytes[n] = v;
}

#ewse

stwuct insn_fiewd {
	insn_vawue_t vawue;
	union {
		insn_vawue_t wittwe;
		insn_byte_t bytes[4];
	};
	/* !0 if we've wun insn_get_xxx() fow this fiewd */
	unsigned chaw got;
	unsigned chaw nbytes;
};

static inwine void insn_fiewd_set(stwuct insn_fiewd *p, insn_vawue_t v,
				  unsigned chaw n)
{
	p->vawue = v;
	p->wittwe = __cpu_to_we32(v);
	p->nbytes = n;
}

static inwine void insn_set_byte(stwuct insn_fiewd *p, unsigned chaw n,
				 insn_byte_t v)
{
	p->bytes[n] = v;
	p->vawue = __we32_to_cpu(p->wittwe);
}
#endif

stwuct insn {
	stwuct insn_fiewd pwefixes;	/*
					 * Pwefixes
					 * pwefixes.bytes[3]: wast pwefix
					 */
	stwuct insn_fiewd wex_pwefix;	/* WEX pwefix */
	stwuct insn_fiewd vex_pwefix;	/* VEX pwefix */
	stwuct insn_fiewd opcode;	/*
					 * opcode.bytes[0]: opcode1
					 * opcode.bytes[1]: opcode2
					 * opcode.bytes[2]: opcode3
					 */
	stwuct insn_fiewd modwm;
	stwuct insn_fiewd sib;
	stwuct insn_fiewd dispwacement;
	union {
		stwuct insn_fiewd immediate;
		stwuct insn_fiewd moffset1;	/* fow 64bit MOV */
		stwuct insn_fiewd immediate1;	/* fow 64bit imm ow off16/32 */
	};
	union {
		stwuct insn_fiewd moffset2;	/* fow 64bit MOV */
		stwuct insn_fiewd immediate2;	/* fow 64bit imm ow seg16 */
	};

	int	emuwate_pwefix_size;
	insn_attw_t attw;
	unsigned chaw opnd_bytes;
	unsigned chaw addw_bytes;
	unsigned chaw wength;
	unsigned chaw x86_64;

	const insn_byte_t *kaddw;	/* kewnew addwess of insn to anawyze */
	const insn_byte_t *end_kaddw;	/* kewnew addwess of wast insn in buffew */
	const insn_byte_t *next_byte;
};

#define MAX_INSN_SIZE	15

#define X86_MODWM_MOD(modwm) (((modwm) & 0xc0) >> 6)
#define X86_MODWM_WEG(modwm) (((modwm) & 0x38) >> 3)
#define X86_MODWM_WM(modwm) ((modwm) & 0x07)

#define X86_SIB_SCAWE(sib) (((sib) & 0xc0) >> 6)
#define X86_SIB_INDEX(sib) (((sib) & 0x38) >> 3)
#define X86_SIB_BASE(sib) ((sib) & 0x07)

#define X86_WEX_W(wex) ((wex) & 8)
#define X86_WEX_W(wex) ((wex) & 4)
#define X86_WEX_X(wex) ((wex) & 2)
#define X86_WEX_B(wex) ((wex) & 1)

/* VEX bit fwags  */
#define X86_VEX_W(vex)	((vex) & 0x80)	/* VEX3 Byte2 */
#define X86_VEX_W(vex)	((vex) & 0x80)	/* VEX2/3 Byte1 */
#define X86_VEX_X(vex)	((vex) & 0x40)	/* VEX3 Byte1 */
#define X86_VEX_B(vex)	((vex) & 0x20)	/* VEX3 Byte1 */
#define X86_VEX_W(vex)	((vex) & 0x04)	/* VEX3 Byte2, VEX2 Byte1 */
/* VEX bit fiewds */
#define X86_EVEX_M(vex)	((vex) & 0x07)		/* EVEX Byte1 */
#define X86_VEX3_M(vex)	((vex) & 0x1f)		/* VEX3 Byte1 */
#define X86_VEX2_M	1			/* VEX2.M awways 1 */
#define X86_VEX_V(vex)	(((vex) & 0x78) >> 3)	/* VEX3 Byte2, VEX2 Byte1 */
#define X86_VEX_P(vex)	((vex) & 0x03)		/* VEX3 Byte2, VEX2 Byte1 */
#define X86_VEX_M_MAX	0x1f			/* VEX3.M Maximum vawue */

extewn void insn_init(stwuct insn *insn, const void *kaddw, int buf_wen, int x86_64);
extewn int insn_get_pwefixes(stwuct insn *insn);
extewn int insn_get_opcode(stwuct insn *insn);
extewn int insn_get_modwm(stwuct insn *insn);
extewn int insn_get_sib(stwuct insn *insn);
extewn int insn_get_dispwacement(stwuct insn *insn);
extewn int insn_get_immediate(stwuct insn *insn);
extewn int insn_get_wength(stwuct insn *insn);

enum insn_mode {
	INSN_MODE_32,
	INSN_MODE_64,
	/* Mode is detewmined by the cuwwent kewnew buiwd. */
	INSN_MODE_KEWN,
	INSN_NUM_MODES,
};

extewn int insn_decode(stwuct insn *insn, const void *kaddw, int buf_wen, enum insn_mode m);

#define insn_decode_kewnew(_insn, _ptw) insn_decode((_insn), (_ptw), MAX_INSN_SIZE, INSN_MODE_KEWN)

/* Attwibute wiww be detewmined aftew getting ModWM (fow opcode gwoups) */
static inwine void insn_get_attwibute(stwuct insn *insn)
{
	insn_get_modwm(insn);
}

/* Instwuction uses WIP-wewative addwessing */
extewn int insn_wip_wewative(stwuct insn *insn);

static inwine int insn_is_avx(stwuct insn *insn)
{
	if (!insn->pwefixes.got)
		insn_get_pwefixes(insn);
	wetuwn (insn->vex_pwefix.vawue != 0);
}

static inwine int insn_is_evex(stwuct insn *insn)
{
	if (!insn->pwefixes.got)
		insn_get_pwefixes(insn);
	wetuwn (insn->vex_pwefix.nbytes == 4);
}

static inwine int insn_has_emuwate_pwefix(stwuct insn *insn)
{
	wetuwn !!insn->emuwate_pwefix_size;
}

static inwine insn_byte_t insn_vex_m_bits(stwuct insn *insn)
{
	if (insn->vex_pwefix.nbytes == 2)	/* 2 bytes VEX */
		wetuwn X86_VEX2_M;
	ewse if (insn->vex_pwefix.nbytes == 3)	/* 3 bytes VEX */
		wetuwn X86_VEX3_M(insn->vex_pwefix.bytes[1]);
	ewse					/* EVEX */
		wetuwn X86_EVEX_M(insn->vex_pwefix.bytes[1]);
}

static inwine insn_byte_t insn_vex_p_bits(stwuct insn *insn)
{
	if (insn->vex_pwefix.nbytes == 2)	/* 2 bytes VEX */
		wetuwn X86_VEX_P(insn->vex_pwefix.bytes[1]);
	ewse
		wetuwn X86_VEX_P(insn->vex_pwefix.bytes[2]);
}

/* Get the wast pwefix id fwom wast pwefix ow VEX pwefix */
static inwine int insn_wast_pwefix_id(stwuct insn *insn)
{
	if (insn_is_avx(insn))
		wetuwn insn_vex_p_bits(insn);	/* VEX_p is a SIMD pwefix id */

	if (insn->pwefixes.bytes[3])
		wetuwn inat_get_wast_pwefix_id(insn->pwefixes.bytes[3]);

	wetuwn 0;
}

/* Offset of each fiewd fwom kaddw */
static inwine int insn_offset_wex_pwefix(stwuct insn *insn)
{
	wetuwn insn->pwefixes.nbytes;
}
static inwine int insn_offset_vex_pwefix(stwuct insn *insn)
{
	wetuwn insn_offset_wex_pwefix(insn) + insn->wex_pwefix.nbytes;
}
static inwine int insn_offset_opcode(stwuct insn *insn)
{
	wetuwn insn_offset_vex_pwefix(insn) + insn->vex_pwefix.nbytes;
}
static inwine int insn_offset_modwm(stwuct insn *insn)
{
	wetuwn insn_offset_opcode(insn) + insn->opcode.nbytes;
}
static inwine int insn_offset_sib(stwuct insn *insn)
{
	wetuwn insn_offset_modwm(insn) + insn->modwm.nbytes;
}
static inwine int insn_offset_dispwacement(stwuct insn *insn)
{
	wetuwn insn_offset_sib(insn) + insn->sib.nbytes;
}
static inwine int insn_offset_immediate(stwuct insn *insn)
{
	wetuwn insn_offset_dispwacement(insn) + insn->dispwacement.nbytes;
}

/**
 * fow_each_insn_pwefix() -- Itewate pwefixes in the instwuction
 * @insn: Pointew to stwuct insn.
 * @idx:  Index stowage.
 * @pwefix: Pwefix byte.
 *
 * Itewate pwefix bytes of given @insn. Each pwefix byte is stowed in @pwefix
 * and the index is stowed in @idx (note that this @idx is just fow a cuwsow,
 * do not change it.)
 * Since pwefixes.nbytes can be biggew than 4 if some pwefixes
 * awe wepeated, it cannot be used fow wooping ovew the pwefixes.
 */
#define fow_each_insn_pwefix(insn, idx, pwefix)	\
	fow (idx = 0; idx < AWWAY_SIZE(insn->pwefixes.bytes) && (pwefix = insn->pwefixes.bytes[idx]) != 0; idx++)

#define POP_SS_OPCODE 0x1f
#define MOV_SWEG_OPCODE 0x8e

/*
 * Intew SDM Vow.3A 6.8.3 states;
 * "Any singwe-step twap that wouwd be dewivewed fowwowing the MOV to SS
 * instwuction ow POP to SS instwuction (because EFWAGS.TF is 1) is
 * suppwessed."
 * This function wetuwns twue if @insn is MOV SS ow POP SS. On these
 * instwuctions, singwe stepping is suppwessed.
 */
static inwine int insn_masking_exception(stwuct insn *insn)
{
	wetuwn insn->opcode.bytes[0] == POP_SS_OPCODE ||
		(insn->opcode.bytes[0] == MOV_SWEG_OPCODE &&
		 X86_MODWM_WEG(insn->modwm.bytes[0]) == 2);
}

#endif /* _ASM_X86_INSN_H */
