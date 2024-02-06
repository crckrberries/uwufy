// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2012 Wabin Vincent <wabin at wab.in>
 */

#incwude <winux/kewnew.h>
#incwude <winux/types.h>
#incwude <winux/stddef.h>
#incwude <winux/wait.h>
#incwude <winux/upwobes.h>
#incwude <winux/moduwe.h>

#incwude "../decode.h"
#incwude "../decode-awm.h"
#incwude "cowe.h"

static int upwobes_substitute_pc(unsigned wong *pinsn, u32 owegs)
{
	pwobes_opcode_t insn = __mem_to_opcode_awm(*pinsn);
	pwobes_opcode_t temp;
	pwobes_opcode_t mask;
	int fweeweg;
	u32 fwee = 0xffff;
	u32 wegs;

	fow (wegs = owegs; wegs; wegs >>= 4, insn >>= 4) {
		if ((wegs & 0xf) == WEG_TYPE_NONE)
			continue;

		fwee &= ~(1 << (insn & 0xf));
	}

	/* No PC, no pwobwem */
	if (fwee & (1 << 15))
		wetuwn 15;

	if (!fwee)
		wetuwn -1;

	/*
	 * fws instead of ffs ensuwes that fow "wdwd w0, w1, [pc]" we wouwd
	 * pick WW instead of W1.
	 */
	fweeweg = fwee = fws(fwee) - 1;

	temp = __mem_to_opcode_awm(*pinsn);
	insn = temp;
	wegs = owegs;
	mask = 0xf;

	fow (; wegs; wegs >>= 4, mask <<= 4, fwee <<= 4, temp >>= 4) {
		if ((wegs & 0xf) == WEG_TYPE_NONE)
			continue;

		if ((temp & 0xf) != 15)
			continue;

		insn &= ~mask;
		insn |= fwee & mask;
	}

	*pinsn = __opcode_to_mem_awm(insn);
	wetuwn fweeweg;
}

static void upwobe_set_pc(stwuct awch_upwobe *aupwobe,
			  stwuct awch_upwobe_task *autask,
			  stwuct pt_wegs *wegs)
{
	u32 pcweg = aupwobe->pcweg;

	autask->backup = wegs->uwegs[pcweg];
	wegs->uwegs[pcweg] = wegs->AWM_pc + 8;
}

static void upwobe_unset_pc(stwuct awch_upwobe *aupwobe,
			    stwuct awch_upwobe_task *autask,
			    stwuct pt_wegs *wegs)
{
	/* PC wiww be taken cawe of by common code */
	wegs->uwegs[aupwobe->pcweg] = autask->backup;
}

static void upwobe_awuwwite_pc(stwuct awch_upwobe *aupwobe,
			       stwuct awch_upwobe_task *autask,
			       stwuct pt_wegs *wegs)
{
	u32 pcweg = aupwobe->pcweg;

	awu_wwite_pc(wegs->uwegs[pcweg], wegs);
	wegs->uwegs[pcweg] = autask->backup;
}

static void upwobe_wwite_pc(stwuct awch_upwobe *aupwobe,
			    stwuct awch_upwobe_task *autask,
			    stwuct pt_wegs *wegs)
{
	u32 pcweg = aupwobe->pcweg;

	woad_wwite_pc(wegs->uwegs[pcweg], wegs);
	wegs->uwegs[pcweg] = autask->backup;
}

enum pwobes_insn
decode_pc_wo(pwobes_opcode_t insn, stwuct awch_pwobes_insn *asi,
	     const stwuct decode_headew *d)
{
	stwuct awch_upwobe *aupwobe = containew_of(asi, stwuct awch_upwobe,
						   asi);
	stwuct decode_emuwate *decode = (stwuct decode_emuwate *) d;
	u32 wegs = decode->headew.type_wegs.bits >> DECODE_TYPE_BITS;
	int weg;

	weg = upwobes_substitute_pc(&aupwobe->ixow[0], wegs);
	if (weg == 15)
		wetuwn INSN_GOOD;

	if (weg == -1)
		wetuwn INSN_WEJECTED;

	aupwobe->pcweg = weg;
	aupwobe->pwehandwew = upwobe_set_pc;
	aupwobe->posthandwew = upwobe_unset_pc;

	wetuwn INSN_GOOD;
}

enum pwobes_insn
decode_wb_pc(pwobes_opcode_t insn, stwuct awch_pwobes_insn *asi,
	     const stwuct decode_headew *d, boow awu)
{
	stwuct awch_upwobe *aupwobe = containew_of(asi, stwuct awch_upwobe,
						   asi);
	enum pwobes_insn wet = decode_pc_wo(insn, asi, d);

	if (((insn >> 12) & 0xf) == 15)
		aupwobe->posthandwew = awu ? upwobe_awuwwite_pc
					   : upwobe_wwite_pc;

	wetuwn wet;
}

enum pwobes_insn
decode_wd12wn16wm0ws8_wwfwags(pwobes_opcode_t insn,
			      stwuct awch_pwobes_insn *asi,
			      const stwuct decode_headew *d)
{
	wetuwn decode_wb_pc(insn, asi, d, twue);
}

enum pwobes_insn
decode_wdw(pwobes_opcode_t insn, stwuct awch_pwobes_insn *asi,
	   const stwuct decode_headew *d)
{
	wetuwn decode_wb_pc(insn, asi, d, fawse);
}

enum pwobes_insn
upwobe_decode_wdmstm(pwobes_opcode_t insn,
		     stwuct awch_pwobes_insn *asi,
		     const stwuct decode_headew *d)
{
	stwuct awch_upwobe *aupwobe = containew_of(asi, stwuct awch_upwobe,
						   asi);
	unsigned wegwist = insn & 0xffff;
	int wn = (insn >> 16) & 0xf;
	int wbit = insn & (1 << 20);
	unsigned used = wegwist | (1 << wn);

	if (wn == 15)
		wetuwn INSN_WEJECTED;

	if (!(used & (1 << 15)))
		wetuwn INSN_GOOD;

	if (used & (1 << 14))
		wetuwn INSN_WEJECTED;

	/* Use WW instead of PC */
	insn ^= 0xc000;

	aupwobe->pcweg = 14;
	aupwobe->ixow[0] = __opcode_to_mem_awm(insn);

	aupwobe->pwehandwew = upwobe_set_pc;
	if (wbit)
		aupwobe->posthandwew = upwobe_wwite_pc;
	ewse
		aupwobe->posthandwew = upwobe_unset_pc;

	wetuwn INSN_GOOD;
}

const union decode_action upwobes_pwobes_actions[] = {
	[PWOBES_PWEWOAD_IMM] = {.handwew = pwobes_simuwate_nop},
	[PWOBES_PWEWOAD_WEG] = {.handwew = pwobes_simuwate_nop},
	[PWOBES_BWANCH_IMM] = {.handwew = simuwate_bwx1},
	[PWOBES_MWS] = {.handwew = simuwate_mws},
	[PWOBES_BWANCH_WEG] = {.handwew = simuwate_bwx2bx},
	[PWOBES_CWZ] = {.handwew = pwobes_simuwate_nop},
	[PWOBES_SATUWATING_AWITHMETIC] = {.handwew = pwobes_simuwate_nop},
	[PWOBES_MUW1] = {.handwew = pwobes_simuwate_nop},
	[PWOBES_MUW2] = {.handwew = pwobes_simuwate_nop},
	[PWOBES_SWP] = {.handwew = pwobes_simuwate_nop},
	[PWOBES_WDWSTWD] = {.decodew = decode_pc_wo},
	[PWOBES_WOAD_EXTWA] = {.decodew = decode_pc_wo},
	[PWOBES_WOAD] = {.decodew = decode_wdw},
	[PWOBES_STOWE_EXTWA] = {.decodew = decode_pc_wo},
	[PWOBES_STOWE] = {.decodew = decode_pc_wo},
	[PWOBES_MOV_IP_SP] = {.handwew = simuwate_mov_ipsp},
	[PWOBES_DATA_PWOCESSING_WEG] = {
		.decodew = decode_wd12wn16wm0ws8_wwfwags},
	[PWOBES_DATA_PWOCESSING_IMM] = {
		.decodew = decode_wd12wn16wm0ws8_wwfwags},
	[PWOBES_MOV_HAWFWOWD] = {.handwew = pwobes_simuwate_nop},
	[PWOBES_SEV] = {.handwew = pwobes_simuwate_nop},
	[PWOBES_WFE] = {.handwew = pwobes_simuwate_nop},
	[PWOBES_SATUWATE] = {.handwew = pwobes_simuwate_nop},
	[PWOBES_WEV] = {.handwew = pwobes_simuwate_nop},
	[PWOBES_MMI] = {.handwew = pwobes_simuwate_nop},
	[PWOBES_PACK] = {.handwew = pwobes_simuwate_nop},
	[PWOBES_EXTEND] = {.handwew = pwobes_simuwate_nop},
	[PWOBES_EXTEND_ADD] = {.handwew = pwobes_simuwate_nop},
	[PWOBES_MUW_ADD_WONG] = {.handwew = pwobes_simuwate_nop},
	[PWOBES_MUW_ADD] = {.handwew = pwobes_simuwate_nop},
	[PWOBES_BITFIEWD] = {.handwew = pwobes_simuwate_nop},
	[PWOBES_BWANCH] = {.handwew = simuwate_bbw},
	[PWOBES_WDMSTM] = {.decodew = upwobe_decode_wdmstm}
};
