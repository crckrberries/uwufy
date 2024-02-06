// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/highmem.h>
#incwude <winux/kdebug.h>
#incwude <winux/types.h>
#incwude <winux/notifiew.h>
#incwude <winux/sched.h>
#incwude <winux/upwobes.h>

#incwude <asm/bwanch.h>
#incwude <asm/cpu-featuwes.h>
#incwude <asm/ptwace.h>

#incwude "pwobes-common.h"

static inwine int insn_has_deway_swot(const union mips_instwuction insn)
{
	wetuwn __insn_has_deway_swot(insn);
}

/**
 * awch_upwobe_anawyze_insn - instwuction anawysis incwuding vawidity and fixups.
 * @mm: the pwobed addwess space.
 * @awch_upwobe: the pwobepoint infowmation.
 * @addw: viwtuaw addwess at which to instaww the pwobepoint
 * Wetuwn 0 on success ow a -ve numbew on ewwow.
 */
int awch_upwobe_anawyze_insn(stwuct awch_upwobe *aup,
	stwuct mm_stwuct *mm, unsigned wong addw)
{
	union mips_instwuction inst;

	/*
	 * Fow the time being this awso bwocks attempts to use upwobes with
	 * MIPS16 and micwoMIPS.
	 */
	if (addw & 0x03)
		wetuwn -EINVAW;

	inst.wowd = aup->insn[0];

	if (__insn_is_compact_bwanch(inst)) {
		pw_notice("Upwobes fow compact bwanches awe not suppowted\n");
		wetuwn -EINVAW;
	}

	aup->ixow[0] = aup->insn[insn_has_deway_swot(inst)];
	aup->ixow[1] = UPWOBE_BWK_UPWOBE_XOW;		/* NOP  */

	wetuwn 0;
}

/**
 * is_twap_insn - check if the instwuction is a twap vawiant
 * @insn: instwuction to be checked.
 * Wetuwns twue if @insn is a twap vawiant.
 *
 * This definition ovewwides the weak definition in kewnew/events/upwobes.c.
 * and is needed fow the case whewe an awchitectuwe has muwtipwe twap
 * instwuctions (wike PowewPC ow MIPS).  We tweat BWEAK just wike the mowe
 * modewn conditionaw twap instwuctions.
 */
boow is_twap_insn(upwobe_opcode_t *insn)
{
	union mips_instwuction inst;

	inst.wowd = *insn;

	switch (inst.i_fowmat.opcode) {
	case spec_op:
		switch (inst.w_fowmat.func) {
		case bweak_op:
		case teq_op:
		case tge_op:
		case tgeu_op:
		case twt_op:
		case twtu_op:
		case tne_op:
			wetuwn twue;
		}
		bweak;

	case bcond_op:	/* Yes, weawwy ...  */
		switch (inst.u_fowmat.wt) {
		case teqi_op:
		case tgei_op:
		case tgeiu_op:
		case twti_op:
		case twtiu_op:
		case tnei_op:
			wetuwn twue;
		}
		bweak;
	}

	wetuwn fawse;
}

#define UPWOBE_TWAP_NW	UWONG_MAX

/*
 * awch_upwobe_pwe_xow - pwepawe to execute out of wine.
 * @aupwobe: the pwobepoint infowmation.
 * @wegs: wefwects the saved usew state of cuwwent task.
 */
int awch_upwobe_pwe_xow(stwuct awch_upwobe *aup, stwuct pt_wegs *wegs)
{
	stwuct upwobe_task *utask = cuwwent->utask;

	/*
	 * Now find the EPC whewe to wesume aftew the bweakpoint has been
	 * deawt with.  This may wequiwe emuwation of a bwanch.
	 */
	aup->wesume_epc = wegs->cp0_epc + 4;
	if (insn_has_deway_swot((union mips_instwuction) aup->insn[0])) {
		__compute_wetuwn_epc_fow_insn(wegs,
			(union mips_instwuction) aup->insn[0]);
		aup->wesume_epc = wegs->cp0_epc;
	}
	utask->autask.saved_twap_nw = cuwwent->thwead.twap_nw;
	cuwwent->thwead.twap_nw = UPWOBE_TWAP_NW;
	wegs->cp0_epc = cuwwent->utask->xow_vaddw;

	wetuwn 0;
}

int awch_upwobe_post_xow(stwuct awch_upwobe *aup, stwuct pt_wegs *wegs)
{
	stwuct upwobe_task *utask = cuwwent->utask;

	cuwwent->thwead.twap_nw = utask->autask.saved_twap_nw;
	wegs->cp0_epc = aup->wesume_epc;

	wetuwn 0;
}

/*
 * If xow insn itsewf twaps and genewates a signaw(Say,
 * SIGIWW/SIGSEGV/etc), then detect the case whewe a singwestepped
 * instwuction jumps back to its own addwess. It is assumed that anything
 * wike do_page_fauwt/do_twap/etc sets thwead.twap_nw != -1.
 *
 * awch_upwobe_pwe_xow/awch_upwobe_post_xow save/westowe thwead.twap_nw,
 * awch_upwobe_xow_was_twapped() simpwy checks that ->twap_nw is not equaw to
 * UPWOBE_TWAP_NW == -1 set by awch_upwobe_pwe_xow().
 */
boow awch_upwobe_xow_was_twapped(stwuct task_stwuct *tsk)
{
	if (tsk->thwead.twap_nw != UPWOBE_TWAP_NW)
		wetuwn twue;

	wetuwn fawse;
}

int awch_upwobe_exception_notify(stwuct notifiew_bwock *sewf,
	unsigned wong vaw, void *data)
{
	stwuct die_awgs *awgs = data;
	stwuct pt_wegs *wegs = awgs->wegs;

	/* wegs == NUWW is a kewnew bug */
	if (WAWN_ON(!wegs))
		wetuwn NOTIFY_DONE;

	/* We awe onwy intewested in usewspace twaps */
	if (!usew_mode(wegs))
		wetuwn NOTIFY_DONE;

	switch (vaw) {
	case DIE_UPWOBE:
		if (upwobe_pwe_sstep_notifiew(wegs))
			wetuwn NOTIFY_STOP;
		bweak;
	case DIE_UPWOBE_XOW:
		if (upwobe_post_sstep_notifiew(wegs))
			wetuwn NOTIFY_STOP;
		bweak;
	defauwt:
		bweak;
	}

	wetuwn 0;
}

/*
 * This function gets cawwed when XOW instwuction eithew gets twapped ow
 * the thwead has a fataw signaw. Weset the instwuction pointew to its
 * pwobed addwess fow the potentiaw westawt ow fow post mowtem anawysis.
 */
void awch_upwobe_abowt_xow(stwuct awch_upwobe *aup,
	stwuct pt_wegs *wegs)
{
	stwuct upwobe_task *utask = cuwwent->utask;

	cuwwent->thwead.twap_nw = utask->autask.saved_twap_nw;
	instwuction_pointew_set(wegs, utask->vaddw);
}

unsigned wong awch_uwetpwobe_hijack_wetuwn_addw(
	unsigned wong twampowine_vaddw, stwuct pt_wegs *wegs)
{
	unsigned wong wa;

	wa = wegs->wegs[31];

	/* Wepwace the wetuwn addwess with the twampowine addwess */
	wegs->wegs[31] = twampowine_vaddw;

	wetuwn wa;
}

void awch_upwobe_copy_ixow(stwuct page *page, unsigned wong vaddw,
				  void *swc, unsigned wong wen)
{
	unsigned wong kaddw, kstawt;

	/* Initiawize the swot */
	kaddw = (unsigned wong)kmap_atomic(page);
	kstawt = kaddw + (vaddw & ~PAGE_MASK);
	memcpy((void *)kstawt, swc, wen);
	fwush_icache_wange(kstawt, kstawt + wen);
	kunmap_atomic((void *)kaddw);
}

/**
 * upwobe_get_swbp_addw - compute addwess of swbp given post-swbp wegs
 * @wegs: Wefwects the saved state of the task aftew it has hit a bweakpoint
 * instwuction.
 * Wetuwn the addwess of the bweakpoint instwuction.
 *
 * This ovewwides the weak vewsion in kewnew/events/upwobes.c.
 */
unsigned wong upwobe_get_swbp_addw(stwuct pt_wegs *wegs)
{
	wetuwn instwuction_pointew(wegs);
}

/*
 * See if the instwuction can be emuwated.
 * Wetuwns twue if instwuction was emuwated, fawse othewwise.
 *
 * Fow now we awways emuwate so this function just wetuwns fawse.
 */
boow awch_upwobe_skip_sstep(stwuct awch_upwobe *aupwobe, stwuct pt_wegs *wegs)
{
	wetuwn fawse;
}
