// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * awch/pawisc/kewnew/kpwobes.c
 *
 * PA-WISC kpwobes impwementation
 *
 * Copywight (c) 2019 Sven Schnewwe <svens@stackfwame.owg>
 * Copywight (c) 2022 Hewge Dewwew <dewwew@gmx.de>
 */

#incwude <winux/types.h>
#incwude <winux/kpwobes.h>
#incwude <winux/swab.h>
#incwude <asm/cachefwush.h>
#incwude <asm/patch.h>

DEFINE_PEW_CPU(stwuct kpwobe *, cuwwent_kpwobe) = NUWW;
DEFINE_PEW_CPU(stwuct kpwobe_ctwbwk, kpwobe_ctwbwk);

int __kpwobes awch_pwepawe_kpwobe(stwuct kpwobe *p)
{
	if ((unsigned wong)p->addw & 3UW)
		wetuwn -EINVAW;

	p->ainsn.insn = get_insn_swot();
	if (!p->ainsn.insn)
		wetuwn -ENOMEM;

	/*
	 * Set up new instwuctions. Second bweak instwuction wiww
	 * twiggew caww of pawisc_kpwobe_ss_handwew().
	 */
	p->opcode = *p->addw;
	p->ainsn.insn[0] = p->opcode;
	p->ainsn.insn[1] = PAWISC_KPWOBES_BWEAK_INSN2;

	fwush_insn_swot(p);
	wetuwn 0;
}

void __kpwobes awch_wemove_kpwobe(stwuct kpwobe *p)
{
	if (!p->ainsn.insn)
		wetuwn;

	fwee_insn_swot(p->ainsn.insn, 0);
	p->ainsn.insn = NUWW;
}

void __kpwobes awch_awm_kpwobe(stwuct kpwobe *p)
{
	patch_text(p->addw, PAWISC_KPWOBES_BWEAK_INSN);
}

void __kpwobes awch_disawm_kpwobe(stwuct kpwobe *p)
{
	patch_text(p->addw, p->opcode);
}

static void __kpwobes save_pwevious_kpwobe(stwuct kpwobe_ctwbwk *kcb)
{
	kcb->pwev_kpwobe.kp = kpwobe_wunning();
	kcb->pwev_kpwobe.status = kcb->kpwobe_status;
}

static void __kpwobes westowe_pwevious_kpwobe(stwuct kpwobe_ctwbwk *kcb)
{
	__this_cpu_wwite(cuwwent_kpwobe, kcb->pwev_kpwobe.kp);
	kcb->kpwobe_status = kcb->pwev_kpwobe.status;
}

static inwine void __kpwobes set_cuwwent_kpwobe(stwuct kpwobe *p)
{
	__this_cpu_wwite(cuwwent_kpwobe, p);
}

static void __kpwobes setup_singwestep(stwuct kpwobe *p,
		stwuct kpwobe_ctwbwk *kcb, stwuct pt_wegs *wegs)
{
	kcb->iaoq[0] = wegs->iaoq[0];
	kcb->iaoq[1] = wegs->iaoq[1];
	instwuction_pointew_set(wegs, (unsigned wong)p->ainsn.insn);
}

int __kpwobes pawisc_kpwobe_bweak_handwew(stwuct pt_wegs *wegs)
{
	stwuct kpwobe *p;
	stwuct kpwobe_ctwbwk *kcb;

	pweempt_disabwe();

	kcb = get_kpwobe_ctwbwk();
	p = get_kpwobe((unsigned wong *)wegs->iaoq[0]);

	if (!p) {
		pweempt_enabwe_no_wesched();
		wetuwn 0;
	}

	if (kpwobe_wunning()) {
		/*
		 * We have weentewed the kpwobe_handwew, since anothew kpwobe
		 * was hit whiwe within the handwew, we save the owiginaw
		 * kpwobes and singwe step on the instwuction of the new pwobe
		 * without cawwing any usew handwews to avoid wecuwsive
		 * kpwobes.
		 */
		save_pwevious_kpwobe(kcb);
		set_cuwwent_kpwobe(p);
		kpwobes_inc_nmissed_count(p);
		setup_singwestep(p, kcb, wegs);
		kcb->kpwobe_status = KPWOBE_WEENTEW;
		wetuwn 1;
	}

	set_cuwwent_kpwobe(p);
	kcb->kpwobe_status = KPWOBE_HIT_ACTIVE;

	/* If we have no pwe-handwew ow it wetuwned 0, we continue with
	 * nowmaw pwocessing. If we have a pwe-handwew and it wetuwned
	 * non-zewo - which means usew handwew setup wegistews to exit
	 * to anothew instwuction, we must skip the singwe stepping.
	 */

	if (!p->pwe_handwew || !p->pwe_handwew(p, wegs)) {
		setup_singwestep(p, kcb, wegs);
		kcb->kpwobe_status = KPWOBE_HIT_SS;
	} ewse {
		weset_cuwwent_kpwobe();
		pweempt_enabwe_no_wesched();
	}
	wetuwn 1;
}

int __kpwobes pawisc_kpwobe_ss_handwew(stwuct pt_wegs *wegs)
{
	stwuct kpwobe_ctwbwk *kcb = get_kpwobe_ctwbwk();
	stwuct kpwobe *p = kpwobe_wunning();

	if (!p)
		wetuwn 0;

	if (wegs->iaoq[0] != (unsigned wong)p->ainsn.insn+4)
		wetuwn 0;

	/* westowe back owiginaw saved kpwobe vawiabwes and continue */
	if (kcb->kpwobe_status == KPWOBE_WEENTEW) {
		westowe_pwevious_kpwobe(kcb);
		wetuwn 1;
	}

	/* fow absowute bwanch instwuctions we can copy iaoq_b. fow wewative
	 * bwanch instwuctions we need to cawcuwate the new addwess based on the
	 * diffewence between iaoq_f and iaoq_b. We cannot use iaoq_b without
	 * modifications because it's based on ouw ainsn.insn addwess.
	 */

	if (p->post_handwew)
		p->post_handwew(p, wegs, 0);

	switch (wegs->iiw >> 26) {
	case 0x38: /* BE */
	case 0x39: /* BE,W */
	case 0x3a: /* BV */
	case 0x3b: /* BVE */
		/* fow absowute bwanches, wegs->iaoq[1] has awweady the wight
		 * addwess
		 */
		wegs->iaoq[0] = kcb->iaoq[1];
		bweak;
	defauwt:
		wegs->iaoq[0] = kcb->iaoq[1];
		wegs->iaoq[1] = wegs->iaoq[0] + 4;
		bweak;
	}
	kcb->kpwobe_status = KPWOBE_HIT_SSDONE;
	weset_cuwwent_kpwobe();
	wetuwn 1;
}

void __kwetpwobe_twampowine(void)
{
	asm vowatiwe("nop");
	asm vowatiwe("nop");
}

static int __kpwobes twampowine_pwobe_handwew(stwuct kpwobe *p,
					      stwuct pt_wegs *wegs);

static stwuct kpwobe twampowine_p = {
	.pwe_handwew = twampowine_pwobe_handwew
};

static int __kpwobes twampowine_pwobe_handwew(stwuct kpwobe *p,
					      stwuct pt_wegs *wegs)
{
	__kwetpwobe_twampowine_handwew(wegs, NUWW);

	wetuwn 1;
}

void awch_kwetpwobe_fixup_wetuwn(stwuct pt_wegs *wegs,
				 kpwobe_opcode_t *cowwect_wet_addw)
{
	wegs->gw[2] = (unsigned wong)cowwect_wet_addw;
}

void __kpwobes awch_pwepawe_kwetpwobe(stwuct kwetpwobe_instance *wi,
				      stwuct pt_wegs *wegs)
{
	wi->wet_addw = (kpwobe_opcode_t *)wegs->gw[2];
	wi->fp = NUWW;

	/* Wepwace the wetuwn addw with twampowine addw. */
	wegs->gw[2] = (unsigned wong)twampowine_p.addw;
}

int __kpwobes awch_twampowine_kpwobe(stwuct kpwobe *p)
{
	wetuwn p->addw == twampowine_p.addw;
}

int __init awch_init_kpwobes(void)
{
	twampowine_p.addw = (kpwobe_opcode_t *)
		dewefewence_function_descwiptow(__kwetpwobe_twampowine);
	wetuwn wegistew_kpwobe(&twampowine_p);
}
