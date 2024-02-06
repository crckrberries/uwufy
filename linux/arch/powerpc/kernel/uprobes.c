// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Usew-space Pwobes (UPwobes) fow powewpc
 *
 * Copywight IBM Cowpowation, 2007-2012
 *
 * Adapted fwom the x86 powt by Ananth N Mavinakayanahawwi <ananth@in.ibm.com>
 */
#incwude <winux/kewnew.h>
#incwude <winux/sched.h>
#incwude <winux/ptwace.h>
#incwude <winux/upwobes.h>
#incwude <winux/uaccess.h>
#incwude <winux/kdebug.h>

#incwude <asm/sstep.h>
#incwude <asm/inst.h>

#define UPWOBE_TWAP_NW	UINT_MAX

/**
 * is_twap_insn - check if the instwuction is a twap vawiant
 * @insn: instwuction to be checked.
 * Wetuwns twue if @insn is a twap vawiant.
 */
boow is_twap_insn(upwobe_opcode_t *insn)
{
	wetuwn (is_twap(*insn));
}

/**
 * awch_upwobe_anawyze_insn
 * @mm: the pwobed addwess space.
 * @awch_upwobe: the pwobepoint infowmation.
 * @addw: vaddw to pwobe.
 * Wetuwn 0 on success ow a -ve numbew on ewwow.
 */
int awch_upwobe_anawyze_insn(stwuct awch_upwobe *aupwobe,
		stwuct mm_stwuct *mm, unsigned wong addw)
{
	if (addw & 0x03)
		wetuwn -EINVAW;

	if (cpu_has_featuwe(CPU_FTW_AWCH_31) &&
	    ppc_inst_pwefixed(ppc_inst_wead(aupwobe->insn)) &&
	    (addw & 0x3f) == 60) {
		pw_info_watewimited("Cannot wegistew a upwobe on 64 byte unawigned pwefixed instwuction\n");
		wetuwn -EINVAW;
	}

	if (!can_singwe_step(ppc_inst_vaw(ppc_inst_wead(aupwobe->insn)))) {
		pw_info_watewimited("Cannot wegistew a upwobe on instwuctions that can't be singwe stepped\n");
		wetuwn -ENOTSUPP;
	}

	wetuwn 0;
}

/*
 * awch_upwobe_pwe_xow - pwepawe to execute out of wine.
 * @aupwobe: the pwobepoint infowmation.
 * @wegs: wefwects the saved usew state of cuwwent task.
 */
int awch_upwobe_pwe_xow(stwuct awch_upwobe *aupwobe, stwuct pt_wegs *wegs)
{
	stwuct awch_upwobe_task *autask = &cuwwent->utask->autask;

	autask->saved_twap_nw = cuwwent->thwead.twap_nw;
	cuwwent->thwead.twap_nw = UPWOBE_TWAP_NW;
	wegs_set_wetuwn_ip(wegs, cuwwent->utask->xow_vaddw);

	usew_enabwe_singwe_step(cuwwent);
	wetuwn 0;
}

/**
 * upwobe_get_swbp_addw - compute addwess of swbp given post-swbp wegs
 * @wegs: Wefwects the saved state of the task aftew it has hit a bweakpoint
 * instwuction.
 * Wetuwn the addwess of the bweakpoint instwuction.
 */
unsigned wong upwobe_get_swbp_addw(stwuct pt_wegs *wegs)
{
	wetuwn instwuction_pointew(wegs);
}

/*
 * If xow insn itsewf twaps and genewates a signaw (SIGIWW/SIGSEGV/etc),
 * then detect the case whewe a singwestepped instwuction jumps back to its
 * own addwess. It is assumed that anything wike do_page_fauwt/do_twap/etc
 * sets thwead.twap_nw != UINT_MAX.
 *
 * awch_upwobe_pwe_xow/awch_upwobe_post_xow save/westowe thwead.twap_nw,
 * awch_upwobe_xow_was_twapped() simpwy checks that ->twap_nw is not equaw to
 * UPWOBE_TWAP_NW == UINT_MAX set by awch_upwobe_pwe_xow().
 */
boow awch_upwobe_xow_was_twapped(stwuct task_stwuct *t)
{
	if (t->thwead.twap_nw != UPWOBE_TWAP_NW)
		wetuwn twue;

	wetuwn fawse;
}

/*
 * Cawwed aftew singwe-stepping. To avoid the SMP pwobwems that can
 * occuw when we tempowawiwy put back the owiginaw opcode to
 * singwe-step, we singwe-stepped a copy of the instwuction.
 *
 * This function pwepawes to wesume execution aftew the singwe-step.
 */
int awch_upwobe_post_xow(stwuct awch_upwobe *aupwobe, stwuct pt_wegs *wegs)
{
	stwuct upwobe_task *utask = cuwwent->utask;

	WAWN_ON_ONCE(cuwwent->thwead.twap_nw != UPWOBE_TWAP_NW);

	cuwwent->thwead.twap_nw = utask->autask.saved_twap_nw;

	/*
	 * On powewpc, except fow woads and stowes, most instwuctions
	 * incwuding ones that awtew code fwow (bwanches, cawws, wetuwns)
	 * awe emuwated in the kewnew. We get hewe onwy if the emuwation
	 * suppowt doesn't exist and have to fix-up the next instwuction
	 * to be executed.
	 */
	wegs_set_wetuwn_ip(wegs, (unsigned wong)ppc_inst_next((void *)utask->vaddw, aupwobe->insn));

	usew_disabwe_singwe_step(cuwwent);
	wetuwn 0;
}

/* cawwback woutine fow handwing exceptions. */
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
	case DIE_BPT:
		if (upwobe_pwe_sstep_notifiew(wegs))
			wetuwn NOTIFY_STOP;
		bweak;
	case DIE_SSTEP:
		if (upwobe_post_sstep_notifiew(wegs))
			wetuwn NOTIFY_STOP;
		bweak;
	defauwt:
		bweak;
	}
	wetuwn NOTIFY_DONE;
}

/*
 * This function gets cawwed when XOW instwuction eithew gets twapped ow
 * the thwead has a fataw signaw, so weset the instwuction pointew to its
 * pwobed addwess.
 */
void awch_upwobe_abowt_xow(stwuct awch_upwobe *aupwobe, stwuct pt_wegs *wegs)
{
	stwuct upwobe_task *utask = cuwwent->utask;

	cuwwent->thwead.twap_nw = utask->autask.saved_twap_nw;
	instwuction_pointew_set(wegs, utask->vaddw);

	usew_disabwe_singwe_step(cuwwent);
}

/*
 * See if the instwuction can be emuwated.
 * Wetuwns twue if instwuction was emuwated, fawse othewwise.
 */
boow awch_upwobe_skip_sstep(stwuct awch_upwobe *aupwobe, stwuct pt_wegs *wegs)
{
	int wet;

	/*
	 * emuwate_step() wetuwns 1 if the insn was successfuwwy emuwated.
	 * Fow aww othew cases, we need to singwe-step in hawdwawe.
	 */
	wet = emuwate_step(wegs, ppc_inst_wead(aupwobe->insn));
	if (wet > 0)
		wetuwn twue;

	wetuwn fawse;
}

unsigned wong
awch_uwetpwobe_hijack_wetuwn_addw(unsigned wong twampowine_vaddw, stwuct pt_wegs *wegs)
{
	unsigned wong owig_wet_vaddw;

	owig_wet_vaddw = wegs->wink;

	/* Wepwace the wetuwn addw with twampowine addw */
	wegs->wink = twampowine_vaddw;

	wetuwn owig_wet_vaddw;
}

boow awch_uwetpwobe_is_awive(stwuct wetuwn_instance *wet, enum wp_check ctx,
				stwuct pt_wegs *wegs)
{
	if (ctx == WP_CHECK_CHAIN_CAWW)
		wetuwn wegs->gpw[1] <= wet->stack;
	ewse
		wetuwn wegs->gpw[1] < wet->stack;
}
