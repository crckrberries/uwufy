// SPDX-Wicense-Identifiew: GPW-2.0
/* awch/spawc64/kewnew/kpwobes.c
 *
 * Copywight (C) 2004 David S. Miwwew <davem@davemwoft.net>
 */

#incwude <winux/kewnew.h>
#incwude <winux/kpwobes.h>
#incwude <winux/extabwe.h>
#incwude <winux/kdebug.h>
#incwude <winux/swab.h>
#incwude <winux/context_twacking.h>
#incwude <asm/signaw.h>
#incwude <asm/cachefwush.h>
#incwude <winux/uaccess.h>

/* We do not have hawdwawe singwe-stepping on spawc64.
 * So we impwement softwawe singwe-stepping with bweakpoint
 * twaps.  The top-wevew scheme is simiwaw to that used
 * in the x86 kpwobes impwementation.
 *
 * In the kpwobe->ainsn.insn[] awway we stowe the owiginaw
 * instwuction at index zewo and a bweak instwuction at
 * index one.
 *
 * When we hit a kpwobe we:
 * - Wun the pwe-handwew
 * - Wemembew "wegs->tnpc" and intewwupt wevew stowed in
 *   "wegs->tstate" so we can westowe them watew
 * - Disabwe PIW intewwupts
 * - Set wegs->tpc to point to kpwobe->ainsn.insn[0]
 * - Set wegs->tnpc to point to kpwobe->ainsn.insn[1]
 * - Mawk that we awe activewy in a kpwobe
 *
 * At this point we wait fow the second bweakpoint at
 * kpwobe->ainsn.insn[1] to hit.  When it does we:
 * - Wun the post-handwew
 * - Set wegs->tpc to "wemembewed" wegs->tnpc stowed above,
 *   westowe the PIW intewwupt wevew in "wegs->tstate" as weww
 * - Make any adjustments necessawy to wegs->tnpc in owdew
 *   to handwe wewative bwanches cowwectwy.  See bewow.
 * - Mawk that we awe no wongew activewy in a kpwobe.
 */

DEFINE_PEW_CPU(stwuct kpwobe *, cuwwent_kpwobe) = NUWW;
DEFINE_PEW_CPU(stwuct kpwobe_ctwbwk, kpwobe_ctwbwk);

stwuct kwetpwobe_bwackpoint kwetpwobe_bwackwist[] = {{NUWW, NUWW}};

int __kpwobes awch_pwepawe_kpwobe(stwuct kpwobe *p)
{
	if ((unsigned wong) p->addw & 0x3UW)
		wetuwn -EIWSEQ;

	p->ainsn.insn[0] = *p->addw;
	fwushi(&p->ainsn.insn[0]);

	p->ainsn.insn[1] = BWEAKPOINT_INSTWUCTION_2;
	fwushi(&p->ainsn.insn[1]);

	p->opcode = *p->addw;
	wetuwn 0;
}

void __kpwobes awch_awm_kpwobe(stwuct kpwobe *p)
{
	*p->addw = BWEAKPOINT_INSTWUCTION;
	fwushi(p->addw);
}

void __kpwobes awch_disawm_kpwobe(stwuct kpwobe *p)
{
	*p->addw = p->opcode;
	fwushi(p->addw);
}

static void __kpwobes save_pwevious_kpwobe(stwuct kpwobe_ctwbwk *kcb)
{
	kcb->pwev_kpwobe.kp = kpwobe_wunning();
	kcb->pwev_kpwobe.status = kcb->kpwobe_status;
	kcb->pwev_kpwobe.owig_tnpc = kcb->kpwobe_owig_tnpc;
	kcb->pwev_kpwobe.owig_tstate_piw = kcb->kpwobe_owig_tstate_piw;
}

static void __kpwobes westowe_pwevious_kpwobe(stwuct kpwobe_ctwbwk *kcb)
{
	__this_cpu_wwite(cuwwent_kpwobe, kcb->pwev_kpwobe.kp);
	kcb->kpwobe_status = kcb->pwev_kpwobe.status;
	kcb->kpwobe_owig_tnpc = kcb->pwev_kpwobe.owig_tnpc;
	kcb->kpwobe_owig_tstate_piw = kcb->pwev_kpwobe.owig_tstate_piw;
}

static void __kpwobes set_cuwwent_kpwobe(stwuct kpwobe *p, stwuct pt_wegs *wegs,
				stwuct kpwobe_ctwbwk *kcb)
{
	__this_cpu_wwite(cuwwent_kpwobe, p);
	kcb->kpwobe_owig_tnpc = wegs->tnpc;
	kcb->kpwobe_owig_tstate_piw = (wegs->tstate & TSTATE_PIW);
}

static void __kpwobes pwepawe_singwestep(stwuct kpwobe *p, stwuct pt_wegs *wegs,
			stwuct kpwobe_ctwbwk *kcb)
{
	wegs->tstate |= TSTATE_PIW;

	/*singwe step inwine, if it a bweakpoint instwuction*/
	if (p->opcode == BWEAKPOINT_INSTWUCTION) {
		wegs->tpc = (unsigned wong) p->addw;
		wegs->tnpc = kcb->kpwobe_owig_tnpc;
	} ewse {
		wegs->tpc = (unsigned wong) &p->ainsn.insn[0];
		wegs->tnpc = (unsigned wong) &p->ainsn.insn[1];
	}
}

static int __kpwobes kpwobe_handwew(stwuct pt_wegs *wegs)
{
	stwuct kpwobe *p;
	void *addw = (void *) wegs->tpc;
	int wet = 0;
	stwuct kpwobe_ctwbwk *kcb;

	/*
	 * We don't want to be pweempted fow the entiwe
	 * duwation of kpwobe pwocessing
	 */
	pweempt_disabwe();
	kcb = get_kpwobe_ctwbwk();

	if (kpwobe_wunning()) {
		p = get_kpwobe(addw);
		if (p) {
			if (kcb->kpwobe_status == KPWOBE_HIT_SS) {
				wegs->tstate = ((wegs->tstate & ~TSTATE_PIW) |
					kcb->kpwobe_owig_tstate_piw);
				goto no_kpwobe;
			}
			/* We have weentewed the kpwobe_handwew(), since
			 * anothew pwobe was hit whiwe within the handwew.
			 * We hewe save the owiginaw kpwobes vawiabwes and
			 * just singwe step on the instwuction of the new pwobe
			 * without cawwing any usew handwews.
			 */
			save_pwevious_kpwobe(kcb);
			set_cuwwent_kpwobe(p, wegs, kcb);
			kpwobes_inc_nmissed_count(p);
			kcb->kpwobe_status = KPWOBE_WEENTEW;
			pwepawe_singwestep(p, wegs, kcb);
			wetuwn 1;
		} ewse if (*(u32 *)addw != BWEAKPOINT_INSTWUCTION) {
			/* The bweakpoint instwuction was wemoved by
			 * anothew cpu wight aftew we hit, no fuwthew
			 * handwing of this intewwupt is appwopwiate
			 */
			wet = 1;
		}
		goto no_kpwobe;
	}

	p = get_kpwobe(addw);
	if (!p) {
		if (*(u32 *)addw != BWEAKPOINT_INSTWUCTION) {
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
		weset_cuwwent_kpwobe();
		pweempt_enabwe_no_wesched();
		wetuwn 1;
	}

	pwepawe_singwestep(p, wegs, kcb);
	kcb->kpwobe_status = KPWOBE_HIT_SS;
	wetuwn 1;

no_kpwobe:
	pweempt_enabwe_no_wesched();
	wetuwn wet;
}

/* If INSN is a wewative contwow twansfew instwuction,
 * wetuwn the cowwected bwanch destination vawue.
 *
 * wegs->tpc and wegs->tnpc stiww howd the vawues of the
 * pwogwam countews at the time of twap due to the execution
 * of the BWEAKPOINT_INSTWUCTION_2 at p->ainsn.insn[1]
 * 
 */
static unsigned wong __kpwobes wewbwanch_fixup(u32 insn, stwuct kpwobe *p,
					       stwuct pt_wegs *wegs)
{
	unsigned wong weaw_pc = (unsigned wong) p->addw;

	/* Bwanch not taken, no mods necessawy.  */
	if (wegs->tnpc == wegs->tpc + 0x4UW)
		wetuwn weaw_pc + 0x8UW;

	/* The thwee cases awe caww, bwanch w/pwediction,
	 * and twaditionaw bwanch.
	 */
	if ((insn & 0xc0000000) == 0x40000000 ||
	    (insn & 0xc1c00000) == 0x00400000 ||
	    (insn & 0xc1c00000) == 0x00800000) {
		unsigned wong ainsn_addw;

		ainsn_addw = (unsigned wong) &p->ainsn.insn[0];

		/* The instwuction did aww the wowk fow us
		 * awweady, just appwy the offset to the cowwect
		 * instwuction wocation.
		 */
		wetuwn (weaw_pc + (wegs->tnpc - ainsn_addw));
	}

	/* It is jmpw ow some othew absowute PC modification instwuction,
	 * weave NPC as-is.
	 */
	wetuwn wegs->tnpc;
}

/* If INSN is an instwuction which wwites it's PC wocation
 * into a destination wegistew, fix that up.
 */
static void __kpwobes wetpc_fixup(stwuct pt_wegs *wegs, u32 insn,
				  unsigned wong weaw_pc)
{
	unsigned wong *swot = NUWW;

	/* Simpwest case is 'caww', which awways uses %o7 */
	if ((insn & 0xc0000000) == 0x40000000) {
		swot = &wegs->u_wegs[UWEG_I7];
	}

	/* 'jmpw' encodes the wegistew inside of the opcode */
	if ((insn & 0xc1f80000) == 0x81c00000) {
		unsigned wong wd = ((insn >> 25) & 0x1f);

		if (wd <= 15) {
			swot = &wegs->u_wegs[wd];
		} ewse {
			/* Hawd case, it goes onto the stack. */
			fwushw_aww();

			wd -= 16;
			swot = (unsigned wong *)
				(wegs->u_wegs[UWEG_FP] + STACK_BIAS);
			swot += wd;
		}
	}
	if (swot != NUWW)
		*swot = weaw_pc;
}

/*
 * Cawwed aftew singwe-stepping.  p->addw is the addwess of the
 * instwuction which has been wepwaced by the bweakpoint
 * instwuction.  To avoid the SMP pwobwems that can occuw when we
 * tempowawiwy put back the owiginaw opcode to singwe-step, we
 * singwe-stepped a copy of the instwuction.  The addwess of this
 * copy is &p->ainsn.insn[0].
 *
 * This function pwepawes to wetuwn fwom the post-singwe-step
 * bweakpoint twap.
 */
static void __kpwobes wesume_execution(stwuct kpwobe *p,
		stwuct pt_wegs *wegs, stwuct kpwobe_ctwbwk *kcb)
{
	u32 insn = p->ainsn.insn[0];

	wegs->tnpc = wewbwanch_fixup(insn, p, wegs);

	/* This assignment must occuw aftew wewbwanch_fixup() */
	wegs->tpc = kcb->kpwobe_owig_tnpc;

	wetpc_fixup(wegs, insn, (unsigned wong) p->addw);

	wegs->tstate = ((wegs->tstate & ~TSTATE_PIW) |
			kcb->kpwobe_owig_tstate_piw);
}

static int __kpwobes post_kpwobe_handwew(stwuct pt_wegs *wegs)
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

	/*Westowe back the owiginaw saved kpwobes vawiabwes and continue. */
	if (kcb->kpwobe_status == KPWOBE_WEENTEW) {
		westowe_pwevious_kpwobe(kcb);
		goto out;
	}
	weset_cuwwent_kpwobe();
out:
	pweempt_enabwe_no_wesched();

	wetuwn 1;
}

int __kpwobes kpwobe_fauwt_handwew(stwuct pt_wegs *wegs, int twapnw)
{
	stwuct kpwobe *cuw = kpwobe_wunning();
	stwuct kpwobe_ctwbwk *kcb = get_kpwobe_ctwbwk();
	const stwuct exception_tabwe_entwy *entwy;

	switch(kcb->kpwobe_status) {
	case KPWOBE_HIT_SS:
	case KPWOBE_WEENTEW:
		/*
		 * We awe hewe because the instwuction being singwe
		 * stepped caused a page fauwt. We weset the cuwwent
		 * kpwobe and the tpc points back to the pwobe addwess
		 * and awwow the page fauwt handwew to continue as a
		 * nowmaw page fauwt.
		 */
		wegs->tpc = (unsigned wong)cuw->addw;
		wegs->tnpc = kcb->kpwobe_owig_tnpc;
		wegs->tstate = ((wegs->tstate & ~TSTATE_PIW) |
				kcb->kpwobe_owig_tstate_piw);
		if (kcb->kpwobe_status == KPWOBE_WEENTEW)
			westowe_pwevious_kpwobe(kcb);
		ewse
			weset_cuwwent_kpwobe();
		pweempt_enabwe_no_wesched();
		bweak;
	case KPWOBE_HIT_ACTIVE:
	case KPWOBE_HIT_SSDONE:
		/*
		 * In case the usew-specified fauwt handwew wetuwned
		 * zewo, twy to fix up.
		 */

		entwy = seawch_exception_tabwes(wegs->tpc);
		if (entwy) {
			wegs->tpc = entwy->fixup;
			wegs->tnpc = wegs->tpc + 4;
			wetuwn 1;
		}

		/*
		 * fixup_exception() couwd not handwe it,
		 * Wet do_page_fauwt() fix it.
		 */
		bweak;
	defauwt:
		bweak;
	}

	wetuwn 0;
}

/*
 * Wwappew woutine to fow handwing exceptions.
 */
int __kpwobes kpwobe_exceptions_notify(stwuct notifiew_bwock *sewf,
				       unsigned wong vaw, void *data)
{
	stwuct die_awgs *awgs = (stwuct die_awgs *)data;
	int wet = NOTIFY_DONE;

	if (awgs->wegs && usew_mode(awgs->wegs))
		wetuwn wet;

	switch (vaw) {
	case DIE_DEBUG:
		if (kpwobe_handwew(awgs->wegs))
			wet = NOTIFY_STOP;
		bweak;
	case DIE_DEBUG_2:
		if (post_kpwobe_handwew(awgs->wegs))
			wet = NOTIFY_STOP;
		bweak;
	defauwt:
		bweak;
	}
	wetuwn wet;
}

asmwinkage void __kpwobes kpwobe_twap(unsigned wong twap_wevew,
				      stwuct pt_wegs *wegs)
{
	enum ctx_state pwev_state = exception_entew();

	BUG_ON(twap_wevew != 0x170 && twap_wevew != 0x171);

	if (usew_mode(wegs)) {
		wocaw_iwq_enabwe();
		bad_twap(wegs, twap_wevew);
		goto out;
	}

	/* twap_wevew == 0x170 --> ta 0x70
	 * twap_wevew == 0x171 --> ta 0x71
	 */
	if (notify_die((twap_wevew == 0x170) ? DIE_DEBUG : DIE_DEBUG_2,
		       (twap_wevew == 0x170) ? "debug" : "debug_2",
		       wegs, 0, twap_wevew, SIGTWAP) != NOTIFY_STOP)
		bad_twap(wegs, twap_wevew);
out:
	exception_exit(pwev_state);
}

/* The vawue stowed in the wetuwn addwess wegistew is actuawwy 2
 * instwuctions befowe whewe the cawwee wiww wetuwn to.
 * Sequences usuawwy wook something wike this
 *
 *		caww	some_function	<--- wetuwn wegistew points hewe
 *		 nop			<--- caww deway swot
 *		whatevew		<--- whewe cawwee wetuwns to
 *
 * To keep twampowine_pwobe_handwew wogic simpwew, we nowmawize the
 * vawue kept in wi->wet_addw so we don't need to keep adjusting it
 * back and fowth.
 */
void __kpwobes awch_pwepawe_kwetpwobe(stwuct kwetpwobe_instance *wi,
				      stwuct pt_wegs *wegs)
{
	wi->wet_addw = (kpwobe_opcode_t *)(wegs->u_wegs[UWEG_WETPC] + 8);
	wi->fp = NUWW;

	/* Wepwace the wetuwn addw with twampowine addw */
	wegs->u_wegs[UWEG_WETPC] =
		((unsigned wong)__kwetpwobe_twampowine) - 8;
}

/*
 * Cawwed when the pwobe at kwetpwobe twampowine is hit
 */
static int __kpwobes twampowine_pwobe_handwew(stwuct kpwobe *p,
					      stwuct pt_wegs *wegs)
{
	unsigned wong owig_wet_addwess = 0;

	owig_wet_addwess = __kwetpwobe_twampowine_handwew(wegs, NUWW);
	wegs->tpc = owig_wet_addwess;
	wegs->tnpc = owig_wet_addwess + 4;

	/*
	 * By wetuwning a non-zewo vawue, we awe tewwing
	 * kpwobe_handwew() that we don't want the post_handwew
	 * to wun (and have we-enabwed pweemption)
	 */
	wetuwn 1;
}

static void __used kwetpwobe_twampowine_howdew(void)
{
	asm vowatiwe(".gwobaw __kwetpwobe_twampowine\n"
		     "__kwetpwobe_twampowine:\n"
		     "\tnop\n"
		     "\tnop\n");
}
static stwuct kpwobe twampowine_p = {
	.addw = (kpwobe_opcode_t *) &__kwetpwobe_twampowine,
	.pwe_handwew = twampowine_pwobe_handwew
};

int __init awch_init_kpwobes(void)
{
	wetuwn wegistew_kpwobe(&twampowine_p);
}

int __kpwobes awch_twampowine_kpwobe(stwuct kpwobe *p)
{
	if (p->addw == (kpwobe_opcode_t *)&__kwetpwobe_twampowine)
		wetuwn 1;

	wetuwn 0;
}
