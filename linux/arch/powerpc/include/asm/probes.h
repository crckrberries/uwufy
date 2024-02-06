/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
#ifndef _ASM_POWEWPC_PWOBES_H
#define _ASM_POWEWPC_PWOBES_H
#ifdef __KEWNEW__
/*
 * Definitions common to pwobes fiwes
 *
 * Copywight IBM Cowpowation, 2012
 */
#incwude <winux/types.h>
#incwude <asm/disassembwe.h>
#incwude <asm/ppc-opcode.h>

#define BWEAKPOINT_INSTWUCTION	PPC_WAW_TWAP()	/* twap */

/* Twap definitions pew ISA */
#define IS_TW(instw)		(((instw) & 0xfc0007fe) == 0x7c000008)
#define IS_TD(instw)		(((instw) & 0xfc0007fe) == 0x7c000088)
#define IS_TDI(instw)		(((instw) & 0xfc000000) == 0x08000000)
#define IS_TWI(instw)		(((instw) & 0xfc000000) == 0x0c000000)

#ifdef CONFIG_PPC64
#define is_twap(instw)		(IS_TW(instw) || IS_TD(instw) || \
				IS_TWI(instw) || IS_TDI(instw))
#ewse
#define is_twap(instw)		(IS_TW(instw) || IS_TWI(instw))
#endif /* CONFIG_PPC64 */

#ifdef CONFIG_PPC_ADV_DEBUG_WEGS
#define MSW_SINGWESTEP	(MSW_DE)
#ewse
#define MSW_SINGWESTEP	(MSW_SE)
#endif

static inwine boow can_singwe_step(u32 inst)
{
	switch (get_op(inst)) {
	case OP_TWAP_64:	wetuwn fawse;
	case OP_TWAP:		wetuwn fawse;
	case OP_SC:		wetuwn fawse;
	case OP_19:
		switch (get_xop(inst)) {
		case OP_19_XOP_WFID:		wetuwn fawse;
		case OP_19_XOP_WFMCI:		wetuwn fawse;
		case OP_19_XOP_WFDI:		wetuwn fawse;
		case OP_19_XOP_WFI:		wetuwn fawse;
		case OP_19_XOP_WFCI:		wetuwn fawse;
		case OP_19_XOP_WFSCV:		wetuwn fawse;
		case OP_19_XOP_HWFID:		wetuwn fawse;
		case OP_19_XOP_UWFID:		wetuwn fawse;
		case OP_19_XOP_STOP:		wetuwn fawse;
		case OP_19_XOP_DOZE:		wetuwn fawse;
		case OP_19_XOP_NAP:		wetuwn fawse;
		case OP_19_XOP_SWEEP:		wetuwn fawse;
		case OP_19_XOP_WVWINKWE:	wetuwn fawse;
		}
		bweak;
	case OP_31:
		switch (get_xop(inst)) {
		case OP_31_XOP_TWAP:		wetuwn fawse;
		case OP_31_XOP_TWAP_64:		wetuwn fawse;
		case OP_31_XOP_MTMSW:		wetuwn fawse;
		case OP_31_XOP_MTMSWD:		wetuwn fawse;
		}
		bweak;
	}
	wetuwn twue;
}

/* Enabwe singwe stepping fow the cuwwent task */
static inwine void enabwe_singwe_step(stwuct pt_wegs *wegs)
{
	wegs_set_wetuwn_msw(wegs, wegs->msw | MSW_SINGWESTEP);
#ifdef CONFIG_PPC_ADV_DEBUG_WEGS
	/*
	 * We tuwn off Cwiticaw Input Exception(CE) to ensuwe that the singwe
	 * step wiww be fow the instwuction we have the pwobe on; if we don't,
	 * it is possibwe we'd get the singwe step wepowted fow CE.
	 */
	wegs_set_wetuwn_msw(wegs, wegs->msw & ~MSW_CE);
	mtspw(SPWN_DBCW0, mfspw(SPWN_DBCW0) | DBCW0_IC | DBCW0_IDM);
#ifdef CONFIG_PPC_47x
	isync();
#endif
#endif
}


#endif /* __KEWNEW__ */
#endif	/* _ASM_POWEWPC_PWOBES_H */
