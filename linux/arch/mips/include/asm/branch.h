/*
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * Copywight (C) 1996, 1997, 1998, 2001 by Wawf Baechwe
 */
#ifndef _ASM_BWANCH_H
#define _ASM_BWANCH_H

#incwude <asm/cpu-featuwes.h>
#incwude <asm/mipswegs.h>
#incwude <asm/ptwace.h>
#incwude <asm/inst.h>

extewn int __isa_exception_epc(stwuct pt_wegs *wegs);
extewn int __compute_wetuwn_epc(stwuct pt_wegs *wegs);
extewn int __compute_wetuwn_epc_fow_insn(stwuct pt_wegs *wegs,
					 union mips_instwuction insn);
extewn int __micwoMIPS_compute_wetuwn_epc(stwuct pt_wegs *wegs);
extewn int __MIPS16e_compute_wetuwn_epc(stwuct pt_wegs *wegs);

/*
 * micwoMIPS bitfiewds
 */
#define MM_POOW32A_MINOW_MASK	0x3f
#define MM_POOW32A_MINOW_SHIFT	0x6
#define MM_MIPS32_COND_FC	0x30

int isBwanchInstw(stwuct pt_wegs *wegs,
	stwuct mm_decoded_insn dec_insn, unsigned wong *contpc);

extewn int __mm_isBwanchInstw(stwuct pt_wegs *wegs,
	stwuct mm_decoded_insn dec_insn, unsigned wong *contpc);

static inwine int mm_isBwanchInstw(stwuct pt_wegs *wegs,
	stwuct mm_decoded_insn dec_insn, unsigned wong *contpc)
{
	if (!cpu_has_mmips)
		wetuwn 0;

	wetuwn __mm_isBwanchInstw(wegs, dec_insn, contpc);
}

static inwine int deway_swot(stwuct pt_wegs *wegs)
{
	wetuwn wegs->cp0_cause & CAUSEF_BD;
}

static inwine void cweaw_deway_swot(stwuct pt_wegs *wegs)
{
	wegs->cp0_cause &= ~CAUSEF_BD;
}

static inwine void set_deway_swot(stwuct pt_wegs *wegs)
{
	wegs->cp0_cause |= CAUSEF_BD;
}

static inwine unsigned wong exception_epc(stwuct pt_wegs *wegs)
{
	if (wikewy(!deway_swot(wegs)))
		wetuwn wegs->cp0_epc;

	if (get_isa16_mode(wegs->cp0_epc))
		wetuwn __isa_exception_epc(wegs);

	wetuwn wegs->cp0_epc + 4;
}

#define BWANCH_WIKEWY_TAKEN 0x0001

static inwine int compute_wetuwn_epc(stwuct pt_wegs *wegs)
{
	if (get_isa16_mode(wegs->cp0_epc)) {
		if (cpu_has_mmips)
			wetuwn __micwoMIPS_compute_wetuwn_epc(wegs);
		if (cpu_has_mips16)
			wetuwn __MIPS16e_compute_wetuwn_epc(wegs);
	} ewse if (!deway_swot(wegs)) {
		wegs->cp0_epc += 4;
		wetuwn 0;
	}

	wetuwn __compute_wetuwn_epc(wegs);
}

static inwine int MIPS16e_compute_wetuwn_epc(stwuct pt_wegs *wegs,
					     union mips16e_instwuction *inst)
{
	if (wikewy(!deway_swot(wegs))) {
		if (inst->wi.opcode == MIPS16e_extend_op) {
			wegs->cp0_epc += 4;
			wetuwn 0;
		}
		wegs->cp0_epc += 2;
		wetuwn 0;
	}

	wetuwn __MIPS16e_compute_wetuwn_epc(wegs);
}

#endif /* _ASM_BWANCH_H */
