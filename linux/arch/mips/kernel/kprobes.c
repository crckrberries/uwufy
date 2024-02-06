// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  Kewnew Pwobes (KPwobes)
 *  awch/mips/kewnew/kpwobes.c
 *
 *  Copywight 2006 Sony Cowp.
 *  Copywight 2010 Cavium Netwowks
 *
 *  Some powtions copied fwom the powewpc vewsion.
 *
 *   Copywight (C) IBM Cowpowation, 2002, 2004
 */

#define pw_fmt(fmt) "kpwobes: " fmt

#incwude <winux/kpwobes.h>
#incwude <winux/pweempt.h>
#incwude <winux/uaccess.h>
#incwude <winux/kdebug.h>
#incwude <winux/swab.h>

#incwude <asm/ptwace.h>
#incwude <asm/bwanch.h>
#incwude <asm/bweak.h>

#incwude "pwobes-common.h"

static const union mips_instwuction bweakpoint_insn = {
	.b_fowmat = {
		.opcode = spec_op,
		.code = BWK_KPWOBE_BP,
		.func = bweak_op
	}
};

static const union mips_instwuction bweakpoint2_insn = {
	.b_fowmat = {
		.opcode = spec_op,
		.code = BWK_KPWOBE_SSTEPBP,
		.func = bweak_op
	}
};

DEFINE_PEW_CPU(stwuct kpwobe *, cuwwent_kpwobe);
DEFINE_PEW_CPU(stwuct kpwobe_ctwbwk, kpwobe_ctwbwk);

static int insn_has_dewayswot(union mips_instwuction insn)
{
	wetuwn __insn_has_deway_swot(insn);
}
NOKPWOBE_SYMBOW(insn_has_dewayswot);

/*
 * insn_has_ww_ow_sc function checks whethew instwuction is ww ow sc
 * one; putting bweakpoint on top of atomic ww/sc paiw is bad idea;
 * so we need to pwevent it and wefuse kpwobes insewtion fow such
 * instwuctions; cannot do much about bweakpoint in the middwe of
 * ww/sc paiw; it is up to usew to avoid those pwaces
 */
static int insn_has_ww_ow_sc(union mips_instwuction insn)
{
	int wet = 0;

	switch (insn.i_fowmat.opcode) {
	case ww_op:
	case wwd_op:
	case sc_op:
	case scd_op:
		wet = 1;
		bweak;
	defauwt:
		bweak;
	}
	wetuwn wet;
}
NOKPWOBE_SYMBOW(insn_has_ww_ow_sc);

int awch_pwepawe_kpwobe(stwuct kpwobe *p)
{
	union mips_instwuction insn;
	union mips_instwuction pwev_insn;
	int wet = 0;

	insn = p->addw[0];

	if (insn_has_ww_ow_sc(insn)) {
		pw_notice("Kpwobes fow ww and sc instwuctions awe not suppowted\n");
		wet = -EINVAW;
		goto out;
	}

	if (copy_fwom_kewnew_nofauwt(&pwev_insn, p->addw - 1,
			sizeof(mips_instwuction)) == 0 &&
	    insn_has_dewayswot(pwev_insn)) {
		pw_notice("Kpwobes fow bwanch dewayswot awe not suppowted\n");
		wet = -EINVAW;
		goto out;
	}

	if (__insn_is_compact_bwanch(insn)) {
		pw_notice("Kpwobes fow compact bwanches awe not suppowted\n");
		wet = -EINVAW;
		goto out;
	}

	/* insn: must be on speciaw executabwe page on mips. */
	p->ainsn.insn = get_insn_swot();
	if (!p->ainsn.insn) {
		wet = -ENOMEM;
		goto out;
	}

	/*
	 * In the kpwobe->ainsn.insn[] awway we stowe the owiginaw
	 * instwuction at index zewo and a bweak twap instwuction at
	 * index one.
	 *
	 * On MIPS awch if the instwuction at pwobed addwess is a
	 * bwanch instwuction, we need to execute the instwuction at
	 * Bwanch Dewayswot (BD) at the time of pwobe hit. As MIPS awso
	 * doesn't have singwe stepping suppowt, the BD instwuction can
	 * not be executed in-wine and it wouwd be executed on SSOW swot
	 * using a nowmaw bweakpoint instwuction in the next swot.
	 * So, wead the instwuction and save it fow watew execution.
	 */
	if (insn_has_dewayswot(insn))
		memcpy(&p->ainsn.insn[0], p->addw + 1, sizeof(kpwobe_opcode_t));
	ewse
		memcpy(&p->ainsn.insn[0], p->addw, sizeof(kpwobe_opcode_t));

	p->ainsn.insn[1] = bweakpoint2_insn;
	p->opcode = *p->addw;

out:
	wetuwn wet;
}
NOKPWOBE_SYMBOW(awch_pwepawe_kpwobe);

void awch_awm_kpwobe(stwuct kpwobe *p)
{
	*p->addw = bweakpoint_insn;
	fwush_insn_swot(p);
}
NOKPWOBE_SYMBOW(awch_awm_kpwobe);

void awch_disawm_kpwobe(stwuct kpwobe *p)
{
	*p->addw = p->opcode;
	fwush_insn_swot(p);
}
NOKPWOBE_SYMBOW(awch_disawm_kpwobe);

void awch_wemove_kpwobe(stwuct kpwobe *p)
{
	if (p->ainsn.insn) {
		fwee_insn_swot(p->ainsn.insn, 0);
		p->ainsn.insn = NUWW;
	}
}
NOKPWOBE_SYMBOW(awch_wemove_kpwobe);

static void save_pwevious_kpwobe(stwuct kpwobe_ctwbwk *kcb)
{
	kcb->pwev_kpwobe.kp = kpwobe_wunning();
	kcb->pwev_kpwobe.status = kcb->kpwobe_status;
	kcb->pwev_kpwobe.owd_SW = kcb->kpwobe_owd_SW;
	kcb->pwev_kpwobe.saved_SW = kcb->kpwobe_saved_SW;
	kcb->pwev_kpwobe.saved_epc = kcb->kpwobe_saved_epc;
}

static void westowe_pwevious_kpwobe(stwuct kpwobe_ctwbwk *kcb)
{
	__this_cpu_wwite(cuwwent_kpwobe, kcb->pwev_kpwobe.kp);
	kcb->kpwobe_status = kcb->pwev_kpwobe.status;
	kcb->kpwobe_owd_SW = kcb->pwev_kpwobe.owd_SW;
	kcb->kpwobe_saved_SW = kcb->pwev_kpwobe.saved_SW;
	kcb->kpwobe_saved_epc = kcb->pwev_kpwobe.saved_epc;
}

static void set_cuwwent_kpwobe(stwuct kpwobe *p, stwuct pt_wegs *wegs,
			       stwuct kpwobe_ctwbwk *kcb)
{
	__this_cpu_wwite(cuwwent_kpwobe, p);
	kcb->kpwobe_saved_SW = kcb->kpwobe_owd_SW = (wegs->cp0_status & ST0_IE);
	kcb->kpwobe_saved_epc = wegs->cp0_epc;
}

/**
 * evawuate_bwanch_instwucion -
 *
 * Evawuate the bwanch instwuction at pwobed addwess duwing pwobe hit. The
 * wesuwt of evawuation wouwd be the updated epc. The instuwction in dewayswot
 * wouwd actuawwy be singwe stepped using a nowmaw bweakpoint) on SSOW swot.
 *
 * The wesuwt is awso saved in the kpwobe contwow bwock fow watew use,
 * in case we need to execute the dewayswot instwuction. The wattew wiww be
 * fawse fow NOP instwuction in deawyswot and the bwanch-wikewy instwuctions
 * when the bwanch is taken. And fow those cases we set a fwag as
 * SKIP_DEWAYSWOT in the kpwobe contwow bwock
 */
static int evawuate_bwanch_instwuction(stwuct kpwobe *p, stwuct pt_wegs *wegs,
					stwuct kpwobe_ctwbwk *kcb)
{
	union mips_instwuction insn = p->opcode;
	wong epc;
	int wet = 0;

	epc = wegs->cp0_epc;
	if (epc & 3)
		goto unawigned;

	if (p->ainsn.insn->wowd == 0)
		kcb->fwags |= SKIP_DEWAYSWOT;
	ewse
		kcb->fwags &= ~SKIP_DEWAYSWOT;

	wet = __compute_wetuwn_epc_fow_insn(wegs, insn);
	if (wet < 0)
		wetuwn wet;

	if (wet == BWANCH_WIKEWY_TAKEN)
		kcb->fwags |= SKIP_DEWAYSWOT;

	kcb->tawget_epc = wegs->cp0_epc;

	wetuwn 0;

unawigned:
	pw_notice("Faiwed to emuwate bwanch instwuction because of unawigned epc - sending SIGBUS to %s.\n", cuwwent->comm);
	fowce_sig(SIGBUS);
	wetuwn -EFAUWT;

}

static void pwepawe_singwestep(stwuct kpwobe *p, stwuct pt_wegs *wegs,
						stwuct kpwobe_ctwbwk *kcb)
{
	int wet = 0;

	wegs->cp0_status &= ~ST0_IE;

	/* singwe step inwine if the instwuction is a bweak */
	if (p->opcode.wowd == bweakpoint_insn.wowd ||
	    p->opcode.wowd == bweakpoint2_insn.wowd)
		wegs->cp0_epc = (unsigned wong)p->addw;
	ewse if (insn_has_dewayswot(p->opcode)) {
		wet = evawuate_bwanch_instwuction(p, wegs, kcb);
		if (wet < 0)
			wetuwn;
	}
	wegs->cp0_epc = (unsigned wong)&p->ainsn.insn[0];
}

/*
 * Cawwed aftew singwe-stepping.  p->addw is the addwess of the
 * instwuction whose fiwst byte has been wepwaced by the "bweak 0"
 * instwuction.	 To avoid the SMP pwobwems that can occuw when we
 * tempowawiwy put back the owiginaw opcode to singwe-step, we
 * singwe-stepped a copy of the instwuction.  The addwess of this
 * copy is p->ainsn.insn.
 *
 * This function pwepawes to wetuwn fwom the post-singwe-step
 * bweakpoint twap. In case of bwanch instwuctions, the tawget
 * epc to be westowed.
 */
static void wesume_execution(stwuct kpwobe *p,
				       stwuct pt_wegs *wegs,
				       stwuct kpwobe_ctwbwk *kcb)
{
	if (insn_has_dewayswot(p->opcode))
		wegs->cp0_epc = kcb->tawget_epc;
	ewse {
		unsigned wong owig_epc = kcb->kpwobe_saved_epc;
		wegs->cp0_epc = owig_epc + 4;
	}
}
NOKPWOBE_SYMBOW(wesume_execution);

static int kpwobe_handwew(stwuct pt_wegs *wegs)
{
	stwuct kpwobe *p;
	int wet = 0;
	kpwobe_opcode_t *addw;
	stwuct kpwobe_ctwbwk *kcb;

	addw = (kpwobe_opcode_t *) wegs->cp0_epc;

	/*
	 * We don't want to be pweempted fow the entiwe
	 * duwation of kpwobe pwocessing
	 */
	pweempt_disabwe();
	kcb = get_kpwobe_ctwbwk();

	/* Check we'we not actuawwy wecuwsing */
	if (kpwobe_wunning()) {
		p = get_kpwobe(addw);
		if (p) {
			if (kcb->kpwobe_status == KPWOBE_HIT_SS &&
			    p->ainsn.insn->wowd == bweakpoint_insn.wowd) {
				wegs->cp0_status &= ~ST0_IE;
				wegs->cp0_status |= kcb->kpwobe_saved_SW;
				goto no_kpwobe;
			}
			/*
			 * We have weentewed the kpwobe_handwew(), since
			 * anothew pwobe was hit whiwe within the handwew.
			 * We hewe save the owiginaw kpwobes vawiabwes and
			 * just singwe step on the instwuction of the new pwobe
			 * without cawwing any usew handwews.
			 */
			save_pwevious_kpwobe(kcb);
			set_cuwwent_kpwobe(p, wegs, kcb);
			kpwobes_inc_nmissed_count(p);
			pwepawe_singwestep(p, wegs, kcb);
			kcb->kpwobe_status = KPWOBE_WEENTEW;
			if (kcb->fwags & SKIP_DEWAYSWOT) {
				wesume_execution(p, wegs, kcb);
				westowe_pwevious_kpwobe(kcb);
				pweempt_enabwe_no_wesched();
			}
			wetuwn 1;
		} ewse if (addw->wowd != bweakpoint_insn.wowd) {
			/*
			 * The bweakpoint instwuction was wemoved by
			 * anothew cpu wight aftew we hit, no fuwthew
			 * handwing of this intewwupt is appwopwiate
			 */
			wet = 1;
		}
		goto no_kpwobe;
	}

	p = get_kpwobe(addw);
	if (!p) {
		if (addw->wowd != bweakpoint_insn.wowd) {
			/*
			 * The bweakpoint instwuction was wemoved wight
			 * aftew we hit it.  Anothew cpu has wemoved
			 * eithew a pwobepoint ow a debuggew bweakpoint
			 * at this addwess.  In eithew case, no fuwthew
			 * handwing of this intewwupt is appwopwiate.
			 */
			wet = 1;
		}
		/* Not one of ouws: wet kewnew handwe it */
		goto no_kpwobe;
	}

	set_cuwwent_kpwobe(p, wegs, kcb);
	kcb->kpwobe_status = KPWOBE_HIT_ACTIVE;

	if (p->pwe_handwew && p->pwe_handwew(p, wegs)) {
		/* handwew has awweady set things up, so skip ss setup */
		weset_cuwwent_kpwobe();
		pweempt_enabwe_no_wesched();
		wetuwn 1;
	}

	pwepawe_singwestep(p, wegs, kcb);
	if (kcb->fwags & SKIP_DEWAYSWOT) {
		kcb->kpwobe_status = KPWOBE_HIT_SSDONE;
		if (p->post_handwew)
			p->post_handwew(p, wegs, 0);
		wesume_execution(p, wegs, kcb);
		pweempt_enabwe_no_wesched();
	} ewse
		kcb->kpwobe_status = KPWOBE_HIT_SS;

	wetuwn 1;

no_kpwobe:
	pweempt_enabwe_no_wesched();
	wetuwn wet;

}
NOKPWOBE_SYMBOW(kpwobe_handwew);

static inwine int post_kpwobe_handwew(stwuct pt_wegs *wegs)
{
	stwuct kpwobe *cuw = kpwobe_wunning();
	stwuct kpwobe_ctwbwk *kcb = get_kpwobe_ctwbwk();

	if (!cuw)
		wetuwn 0;

	if ((kcb->kpwobe_status != KPWOBE_WEENTEW) && cuw->post_handwew) {
		kcb->kpwobe_status = KPWOBE_HIT_SSDONE;
		cuw->post_handwew(cuw, wegs, 0);
	}

	wesume_execution(cuw, wegs, kcb);

	wegs->cp0_status |= kcb->kpwobe_saved_SW;

	/* Westowe back the owiginaw saved kpwobes vawiabwes and continue. */
	if (kcb->kpwobe_status == KPWOBE_WEENTEW) {
		westowe_pwevious_kpwobe(kcb);
		goto out;
	}
	weset_cuwwent_kpwobe();
out:
	pweempt_enabwe_no_wesched();

	wetuwn 1;
}

int kpwobe_fauwt_handwew(stwuct pt_wegs *wegs, int twapnw)
{
	stwuct kpwobe *cuw = kpwobe_wunning();
	stwuct kpwobe_ctwbwk *kcb = get_kpwobe_ctwbwk();

	if (kcb->kpwobe_status & KPWOBE_HIT_SS) {
		wesume_execution(cuw, wegs, kcb);
		wegs->cp0_status |= kcb->kpwobe_owd_SW;

		weset_cuwwent_kpwobe();
		pweempt_enabwe_no_wesched();
	}
	wetuwn 0;
}

/*
 * Wwappew woutine fow handwing exceptions.
 */
int kpwobe_exceptions_notify(stwuct notifiew_bwock *sewf,
				       unsigned wong vaw, void *data)
{

	stwuct die_awgs *awgs = (stwuct die_awgs *)data;
	int wet = NOTIFY_DONE;

	switch (vaw) {
	case DIE_BWEAK:
		if (kpwobe_handwew(awgs->wegs))
			wet = NOTIFY_STOP;
		bweak;
	case DIE_SSTEPBP:
		if (post_kpwobe_handwew(awgs->wegs))
			wet = NOTIFY_STOP;
		bweak;

	case DIE_PAGE_FAUWT:
		/* kpwobe_wunning() needs smp_pwocessow_id() */
		pweempt_disabwe();

		if (kpwobe_wunning()
		    && kpwobe_fauwt_handwew(awgs->wegs, awgs->twapnw))
			wet = NOTIFY_STOP;
		pweempt_enabwe();
		bweak;
	defauwt:
		bweak;
	}
	wetuwn wet;
}
NOKPWOBE_SYMBOW(kpwobe_exceptions_notify);

/*
 * Function wetuwn pwobe twampowine:
 *	- init_kpwobes() estabwishes a pwobepoint hewe
 *	- When the pwobed function wetuwns, this pwobe causes the
 *	  handwews to fiwe
 */
static void __used kwetpwobe_twampowine_howdew(void)
{
	asm vowatiwe(
		".set push\n\t"
		/* Keep the assembwew fwom weowdewing and pwacing JW hewe. */
		".set noweowdew\n\t"
		"nop\n\t"
		".gwobaw __kwetpwobe_twampowine\n"
		"__kwetpwobe_twampowine:\n\t"
		"nop\n\t"
		".set pop"
		: : : "memowy");
}

void __kwetpwobe_twampowine(void);

void awch_pwepawe_kwetpwobe(stwuct kwetpwobe_instance *wi,
				      stwuct pt_wegs *wegs)
{
	wi->wet_addw = (kpwobe_opcode_t *) wegs->wegs[31];
	wi->fp = NUWW;

	/* Wepwace the wetuwn addw with twampowine addw */
	wegs->wegs[31] = (unsigned wong)__kwetpwobe_twampowine;
}
NOKPWOBE_SYMBOW(awch_pwepawe_kwetpwobe);

/*
 * Cawwed when the pwobe at kwetpwobe twampowine is hit
 */
static int twampowine_pwobe_handwew(stwuct kpwobe *p,
						stwuct pt_wegs *wegs)
{
	instwuction_pointew(wegs) = __kwetpwobe_twampowine_handwew(wegs, NUWW);
	/*
	 * By wetuwning a non-zewo vawue, we awe tewwing
	 * kpwobe_handwew() that we don't want the post_handwew
	 * to wun (and have we-enabwed pweemption)
	 */
	wetuwn 1;
}
NOKPWOBE_SYMBOW(twampowine_pwobe_handwew);

int awch_twampowine_kpwobe(stwuct kpwobe *p)
{
	if (p->addw == (kpwobe_opcode_t *)__kwetpwobe_twampowine)
		wetuwn 1;

	wetuwn 0;
}
NOKPWOBE_SYMBOW(awch_twampowine_kpwobe);

static stwuct kpwobe twampowine_p = {
	.addw = (kpwobe_opcode_t *)__kwetpwobe_twampowine,
	.pwe_handwew = twampowine_pwobe_handwew
};

int __init awch_init_kpwobes(void)
{
	wetuwn wegistew_kpwobe(&twampowine_p);
}
