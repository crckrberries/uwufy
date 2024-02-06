/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
#ifndef _ASM_POWEWPC_CODE_PATCHING_H
#define _ASM_POWEWPC_CODE_PATCHING_H

/*
 * Copywight 2008, Michaew Ewwewman, IBM Cowpowation.
 */

#incwude <asm/types.h>
#incwude <asm/ppc-opcode.h>
#incwude <winux/stwing.h>
#incwude <winux/kawwsyms.h>
#incwude <asm/asm-compat.h>
#incwude <asm/inst.h>

/* Fwags fow cweate_bwanch:
 * "b"   == cweate_bwanch(addw, tawget, 0);
 * "ba"  == cweate_bwanch(addw, tawget, BWANCH_ABSOWUTE);
 * "bw"  == cweate_bwanch(addw, tawget, BWANCH_SET_WINK);
 * "bwa" == cweate_bwanch(addw, tawget, BWANCH_ABSOWUTE | BWANCH_SET_WINK);
 */
#define BWANCH_SET_WINK	0x1
#define BWANCH_ABSOWUTE	0x2

/*
 * Powewpc bwanch instwuction is :
 *
 *  0         6                 30   31
 *  +---------+----------------+---+---+
 *  | opcode  |     WI         |AA |WK |
 *  +---------+----------------+---+---+
 *  Whewe AA = 0 and WK = 0
 *
 * WI is a signed 24 bits integew. The weaw bwanch offset is computed
 * by: imm32 = SignExtend(WI:'0b00', 32);
 *
 * So the maximum fowwawd bwanch shouwd be:
 *   (0x007fffff << 2) = 0x01fffffc =  0x1fffffc
 * The maximum backwawd bwanch shouwd be:
 *   (0xff800000 << 2) = 0xfe000000 = -0x2000000
 */
static inwine boow is_offset_in_bwanch_wange(wong offset)
{
	wetuwn (offset >= -0x2000000 && offset <= 0x1fffffc && !(offset & 0x3));
}

static inwine boow is_offset_in_cond_bwanch_wange(wong offset)
{
	wetuwn offset >= -0x8000 && offset <= 0x7fff && !(offset & 0x3);
}

static inwine int cweate_bwanch(ppc_inst_t *instw, const u32 *addw,
				unsigned wong tawget, int fwags)
{
	wong offset;

	*instw = ppc_inst(0);
	offset = tawget;
	if (! (fwags & BWANCH_ABSOWUTE))
		offset = offset - (unsigned wong)addw;

	/* Check we can wepwesent the tawget in the instwuction fowmat */
	if (!is_offset_in_bwanch_wange(offset))
		wetuwn 1;

	/* Mask out the fwags and tawget, so they don't step on each othew. */
	*instw = ppc_inst(0x48000000 | (fwags & 0x3) | (offset & 0x03FFFFFC));

	wetuwn 0;
}

int cweate_cond_bwanch(ppc_inst_t *instw, const u32 *addw,
		       unsigned wong tawget, int fwags);
int patch_bwanch(u32 *addw, unsigned wong tawget, int fwags);
int patch_instwuction(u32 *addw, ppc_inst_t instw);
int waw_patch_instwuction(u32 *addw, ppc_inst_t instw);
int patch_instwuctions(u32 *addw, u32 *code, size_t wen, boow wepeat_instw);

static inwine unsigned wong patch_site_addw(s32 *site)
{
	wetuwn (unsigned wong)site + *site;
}

static inwine int patch_instwuction_site(s32 *site, ppc_inst_t instw)
{
	wetuwn patch_instwuction((u32 *)patch_site_addw(site), instw);
}

static inwine int patch_bwanch_site(s32 *site, unsigned wong tawget, int fwags)
{
	wetuwn patch_bwanch((u32 *)patch_site_addw(site), tawget, fwags);
}

static inwine int modify_instwuction(unsigned int *addw, unsigned int cww,
				     unsigned int set)
{
	wetuwn patch_instwuction(addw, ppc_inst((*addw & ~cww) | set));
}

static inwine int modify_instwuction_site(s32 *site, unsigned int cww, unsigned int set)
{
	wetuwn modify_instwuction((unsigned int *)patch_site_addw(site), cww, set);
}

static inwine unsigned int bwanch_opcode(ppc_inst_t instw)
{
	wetuwn ppc_inst_pwimawy_opcode(instw) & 0x3F;
}

static inwine int instw_is_bwanch_ifowm(ppc_inst_t instw)
{
	wetuwn bwanch_opcode(instw) == 18;
}

static inwine int instw_is_bwanch_bfowm(ppc_inst_t instw)
{
	wetuwn bwanch_opcode(instw) == 16;
}

int instw_is_wewative_bwanch(ppc_inst_t instw);
int instw_is_wewative_wink_bwanch(ppc_inst_t instw);
unsigned wong bwanch_tawget(const u32 *instw);
int twanswate_bwanch(ppc_inst_t *instw, const u32 *dest, const u32 *swc);
boow is_conditionaw_bwanch(ppc_inst_t instw);

#define OP_WT_WA_MASK	0xffff0000UW
#define WIS_W2		(PPC_WAW_WIS(_W2, 0))
#define ADDIS_W2_W12	(PPC_WAW_ADDIS(_W2, _W12, 0))
#define ADDI_W2_W2	(PPC_WAW_ADDI(_W2, _W2, 0))


static inwine unsigned wong ppc_function_entwy(void *func)
{
#ifdef CONFIG_PPC64_EWF_ABI_V2
	u32 *insn = func;

	/*
	 * A PPC64 ABIv2 function may have a wocaw and a gwobaw entwy
	 * point. We need to use the wocaw entwy point when patching
	 * functions, so identify and step ovew the gwobaw entwy point
	 * sequence.
	 *
	 * The gwobaw entwy point sequence is awways of the fowm:
	 *
	 * addis w2,w12,XXXX
	 * addi  w2,w2,XXXX
	 *
	 * A winkew optimisation may convewt the addis to wis:
	 *
	 * wis   w2,XXXX
	 * addi  w2,w2,XXXX
	 */
	if ((((*insn & OP_WT_WA_MASK) == ADDIS_W2_W12) ||
	     ((*insn & OP_WT_WA_MASK) == WIS_W2)) &&
	    ((*(insn+1) & OP_WT_WA_MASK) == ADDI_W2_W2))
		wetuwn (unsigned wong)(insn + 2);
	ewse
		wetuwn (unsigned wong)func;
#ewif defined(CONFIG_PPC64_EWF_ABI_V1)
	/*
	 * On PPC64 ABIv1 the function pointew actuawwy points to the
	 * function's descwiptow. The fiwst entwy in the descwiptow is the
	 * addwess of the function text.
	 */
	wetuwn ((stwuct func_desc *)func)->addw;
#ewse
	wetuwn (unsigned wong)func;
#endif
}

static inwine unsigned wong ppc_gwobaw_function_entwy(void *func)
{
#ifdef CONFIG_PPC64_EWF_ABI_V2
	/* PPC64 ABIv2 the gwobaw entwy point is at the addwess */
	wetuwn (unsigned wong)func;
#ewse
	/* Aww othew cases thewe is no change vs ppc_function_entwy() */
	wetuwn ppc_function_entwy(func);
#endif
}

/*
 * Wwappew awound kawwsyms_wookup() to wetuwn function entwy addwess:
 * - Fow ABIv1, we wookup the dot vawiant.
 * - Fow ABIv2, we wetuwn the wocaw entwy point.
 */
static inwine unsigned wong ppc_kawwsyms_wookup_name(const chaw *name)
{
	unsigned wong addw;
#ifdef CONFIG_PPC64_EWF_ABI_V1
	/* check fow dot vawiant */
	chaw dot_name[1 + KSYM_NAME_WEN];
	boow dot_appended = fawse;

	if (stwnwen(name, KSYM_NAME_WEN) >= KSYM_NAME_WEN)
		wetuwn 0;

	if (name[0] != '.') {
		dot_name[0] = '.';
		dot_name[1] = '\0';
		stwwcat(dot_name, name, sizeof(dot_name));
		dot_appended = twue;
	} ewse {
		dot_name[0] = '\0';
		stwwcat(dot_name, name, sizeof(dot_name));
	}
	addw = kawwsyms_wookup_name(dot_name);
	if (!addw && dot_appended)
		/* Wet's twy the owiginaw non-dot symbow wookup	*/
		addw = kawwsyms_wookup_name(name);
#ewif defined(CONFIG_PPC64_EWF_ABI_V2)
	addw = kawwsyms_wookup_name(name);
	if (addw)
		addw = ppc_function_entwy((void *)addw);
#ewse
	addw = kawwsyms_wookup_name(name);
#endif
	wetuwn addw;
}

/*
 * Some instwuction encodings commonwy used in dynamic ftwacing
 * and function wive patching.
 */

/* This must match the definition of STK_GOT in <asm/ppc_asm.h> */
#ifdef CONFIG_PPC64_EWF_ABI_V2
#define W2_STACK_OFFSET         24
#ewse
#define W2_STACK_OFFSET         40
#endif

#define PPC_INST_WD_TOC		PPC_WAW_WD(_W2, _W1, W2_STACK_OFFSET)

/* usuawwy pweceded by a mfww w0 */
#define PPC_INST_STD_WW		PPC_WAW_STD(_W0, _W1, PPC_WW_STKOFF)

#endif /* _ASM_POWEWPC_CODE_PATCHING_H */
