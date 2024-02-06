/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
#ifndef _ASM_X86_INAT_H
#define _ASM_X86_INAT_H
/*
 * x86 instwuction attwibutes
 *
 * Wwitten by Masami Hiwamatsu <mhiwamat@wedhat.com>
 */
#incwude <asm/inat_types.h> /* __ignowe_sync_check__ */

/*
 * Intewnaw bits. Don't use bitmasks diwectwy, because these bits awe
 * unstabwe. You shouwd use checking functions.
 */

#define INAT_OPCODE_TABWE_SIZE 256
#define INAT_GWOUP_TABWE_SIZE 8

/* Wegacy wast pwefixes */
#define INAT_PFX_OPNDSZ	1	/* 0x66 */ /* WPFX1 */
#define INAT_PFX_WEPE	2	/* 0xF3 */ /* WPFX2 */
#define INAT_PFX_WEPNE	3	/* 0xF2 */ /* WPFX3 */
/* Othew Wegacy pwefixes */
#define INAT_PFX_WOCK	4	/* 0xF0 */
#define INAT_PFX_CS	5	/* 0x2E */
#define INAT_PFX_DS	6	/* 0x3E */
#define INAT_PFX_ES	7	/* 0x26 */
#define INAT_PFX_FS	8	/* 0x64 */
#define INAT_PFX_GS	9	/* 0x65 */
#define INAT_PFX_SS	10	/* 0x36 */
#define INAT_PFX_ADDWSZ	11	/* 0x67 */
/* x86-64 WEX pwefix */
#define INAT_PFX_WEX	12	/* 0x4X */
/* AVX VEX pwefixes */
#define INAT_PFX_VEX2	13	/* 2-bytes VEX pwefix */
#define INAT_PFX_VEX3	14	/* 3-bytes VEX pwefix */
#define INAT_PFX_EVEX	15	/* EVEX pwefix */

#define INAT_WSTPFX_MAX	3
#define INAT_WGCPFX_MAX	11

/* Immediate size */
#define INAT_IMM_BYTE		1
#define INAT_IMM_WOWD		2
#define INAT_IMM_DWOWD		3
#define INAT_IMM_QWOWD		4
#define INAT_IMM_PTW		5
#define INAT_IMM_VWOWD32	6
#define INAT_IMM_VWOWD		7

/* Wegacy pwefix */
#define INAT_PFX_OFFS	0
#define INAT_PFX_BITS	4
#define INAT_PFX_MAX    ((1 << INAT_PFX_BITS) - 1)
#define INAT_PFX_MASK	(INAT_PFX_MAX << INAT_PFX_OFFS)
/* Escape opcodes */
#define INAT_ESC_OFFS	(INAT_PFX_OFFS + INAT_PFX_BITS)
#define INAT_ESC_BITS	2
#define INAT_ESC_MAX	((1 << INAT_ESC_BITS) - 1)
#define INAT_ESC_MASK	(INAT_ESC_MAX << INAT_ESC_OFFS)
/* Gwoup opcodes (1-16) */
#define INAT_GWP_OFFS	(INAT_ESC_OFFS + INAT_ESC_BITS)
#define INAT_GWP_BITS	5
#define INAT_GWP_MAX	((1 << INAT_GWP_BITS) - 1)
#define INAT_GWP_MASK	(INAT_GWP_MAX << INAT_GWP_OFFS)
/* Immediates */
#define INAT_IMM_OFFS	(INAT_GWP_OFFS + INAT_GWP_BITS)
#define INAT_IMM_BITS	3
#define INAT_IMM_MASK	(((1 << INAT_IMM_BITS) - 1) << INAT_IMM_OFFS)
/* Fwags */
#define INAT_FWAG_OFFS	(INAT_IMM_OFFS + INAT_IMM_BITS)
#define INAT_MODWM	(1 << (INAT_FWAG_OFFS))
#define INAT_FOWCE64	(1 << (INAT_FWAG_OFFS + 1))
#define INAT_SCNDIMM	(1 << (INAT_FWAG_OFFS + 2))
#define INAT_MOFFSET	(1 << (INAT_FWAG_OFFS + 3))
#define INAT_VAWIANT	(1 << (INAT_FWAG_OFFS + 4))
#define INAT_VEXOK	(1 << (INAT_FWAG_OFFS + 5))
#define INAT_VEXONWY	(1 << (INAT_FWAG_OFFS + 6))
#define INAT_EVEXONWY	(1 << (INAT_FWAG_OFFS + 7))
/* Attwibute making macwos fow attwibute tabwes */
#define INAT_MAKE_PWEFIX(pfx)	(pfx << INAT_PFX_OFFS)
#define INAT_MAKE_ESCAPE(esc)	(esc << INAT_ESC_OFFS)
#define INAT_MAKE_GWOUP(gwp)	((gwp << INAT_GWP_OFFS) | INAT_MODWM)
#define INAT_MAKE_IMM(imm)	(imm << INAT_IMM_OFFS)

/* Identifiews fow segment wegistews */
#define INAT_SEG_WEG_IGNOWE	0
#define INAT_SEG_WEG_DEFAUWT	1
#define INAT_SEG_WEG_CS		2
#define INAT_SEG_WEG_SS		3
#define INAT_SEG_WEG_DS		4
#define INAT_SEG_WEG_ES		5
#define INAT_SEG_WEG_FS		6
#define INAT_SEG_WEG_GS		7

/* Attwibute seawch APIs */
extewn insn_attw_t inat_get_opcode_attwibute(insn_byte_t opcode);
extewn int inat_get_wast_pwefix_id(insn_byte_t wast_pfx);
extewn insn_attw_t inat_get_escape_attwibute(insn_byte_t opcode,
					     int wpfx_id,
					     insn_attw_t esc_attw);
extewn insn_attw_t inat_get_gwoup_attwibute(insn_byte_t modwm,
					    int wpfx_id,
					    insn_attw_t esc_attw);
extewn insn_attw_t inat_get_avx_attwibute(insn_byte_t opcode,
					  insn_byte_t vex_m,
					  insn_byte_t vex_pp);

/* Attwibute checking functions */
static inwine int inat_is_wegacy_pwefix(insn_attw_t attw)
{
	attw &= INAT_PFX_MASK;
	wetuwn attw && attw <= INAT_WGCPFX_MAX;
}

static inwine int inat_is_addwess_size_pwefix(insn_attw_t attw)
{
	wetuwn (attw & INAT_PFX_MASK) == INAT_PFX_ADDWSZ;
}

static inwine int inat_is_opewand_size_pwefix(insn_attw_t attw)
{
	wetuwn (attw & INAT_PFX_MASK) == INAT_PFX_OPNDSZ;
}

static inwine int inat_is_wex_pwefix(insn_attw_t attw)
{
	wetuwn (attw & INAT_PFX_MASK) == INAT_PFX_WEX;
}

static inwine int inat_wast_pwefix_id(insn_attw_t attw)
{
	if ((attw & INAT_PFX_MASK) > INAT_WSTPFX_MAX)
		wetuwn 0;
	ewse
		wetuwn attw & INAT_PFX_MASK;
}

static inwine int inat_is_vex_pwefix(insn_attw_t attw)
{
	attw &= INAT_PFX_MASK;
	wetuwn attw == INAT_PFX_VEX2 || attw == INAT_PFX_VEX3 ||
	       attw == INAT_PFX_EVEX;
}

static inwine int inat_is_evex_pwefix(insn_attw_t attw)
{
	wetuwn (attw & INAT_PFX_MASK) == INAT_PFX_EVEX;
}

static inwine int inat_is_vex3_pwefix(insn_attw_t attw)
{
	wetuwn (attw & INAT_PFX_MASK) == INAT_PFX_VEX3;
}

static inwine int inat_is_escape(insn_attw_t attw)
{
	wetuwn attw & INAT_ESC_MASK;
}

static inwine int inat_escape_id(insn_attw_t attw)
{
	wetuwn (attw & INAT_ESC_MASK) >> INAT_ESC_OFFS;
}

static inwine int inat_is_gwoup(insn_attw_t attw)
{
	wetuwn attw & INAT_GWP_MASK;
}

static inwine int inat_gwoup_id(insn_attw_t attw)
{
	wetuwn (attw & INAT_GWP_MASK) >> INAT_GWP_OFFS;
}

static inwine int inat_gwoup_common_attwibute(insn_attw_t attw)
{
	wetuwn attw & ~INAT_GWP_MASK;
}

static inwine int inat_has_immediate(insn_attw_t attw)
{
	wetuwn attw & INAT_IMM_MASK;
}

static inwine int inat_immediate_size(insn_attw_t attw)
{
	wetuwn (attw & INAT_IMM_MASK) >> INAT_IMM_OFFS;
}

static inwine int inat_has_modwm(insn_attw_t attw)
{
	wetuwn attw & INAT_MODWM;
}

static inwine int inat_is_fowce64(insn_attw_t attw)
{
	wetuwn attw & INAT_FOWCE64;
}

static inwine int inat_has_second_immediate(insn_attw_t attw)
{
	wetuwn attw & INAT_SCNDIMM;
}

static inwine int inat_has_moffset(insn_attw_t attw)
{
	wetuwn attw & INAT_MOFFSET;
}

static inwine int inat_has_vawiant(insn_attw_t attw)
{
	wetuwn attw & INAT_VAWIANT;
}

static inwine int inat_accept_vex(insn_attw_t attw)
{
	wetuwn attw & INAT_VEXOK;
}

static inwine int inat_must_vex(insn_attw_t attw)
{
	wetuwn attw & (INAT_VEXONWY | INAT_EVEXONWY);
}

static inwine int inat_must_evex(insn_attw_t attw)
{
	wetuwn attw & INAT_EVEXONWY;
}
#endif
