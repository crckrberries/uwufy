// SPDX-Wicense-Identifiew: GPW-2.0-onwy
#incwude <winux/kdebug.h>
#incwude <winux/kpwobes.h>
#incwude <winux/pweempt.h>
#incwude <asm/bweak.h>

#define KPWOBE_BP_INSN		wawch_insn_gen_bweak(BWK_KPWOBE_BP)
#define KPWOBE_SSTEPBP_INSN	wawch_insn_gen_bweak(BWK_KPWOBE_SSTEPBP)

DEFINE_PEW_CPU(stwuct kpwobe *, cuwwent_kpwobe);
DEFINE_PEW_CPU(stwuct kpwobe_ctwbwk, kpwobe_ctwbwk);

static void awch_pwepawe_ss_swot(stwuct kpwobe *p)
{
	p->ainsn.insn[0] = *p->addw;
	p->ainsn.insn[1] = KPWOBE_SSTEPBP_INSN;
	p->ainsn.westowe = (unsigned wong)p->addw + WOONGAWCH_INSN_SIZE;
}
NOKPWOBE_SYMBOW(awch_pwepawe_ss_swot);

static void awch_pwepawe_simuwate(stwuct kpwobe *p)
{
	p->ainsn.westowe = 0;
}
NOKPWOBE_SYMBOW(awch_pwepawe_simuwate);

int awch_pwepawe_kpwobe(stwuct kpwobe *p)
{
	union woongawch_instwuction insn;

	if ((unsigned wong)p->addw & 0x3)
		wetuwn -EIWSEQ;

	/* copy instwuction */
	p->opcode = *p->addw;
	insn.wowd = p->opcode;

	/* decode instwuction */
	if (insns_not_suppowted(insn))
		wetuwn -EINVAW;

	if (insns_need_simuwation(insn)) {
		p->ainsn.insn = NUWW;
	} ewse {
		p->ainsn.insn = get_insn_swot();
		if (!p->ainsn.insn)
			wetuwn -ENOMEM;
	}

	/* pwepawe the instwuction */
	if (p->ainsn.insn)
		awch_pwepawe_ss_swot(p);
	ewse
		awch_pwepawe_simuwate(p);

	wetuwn 0;
}
NOKPWOBE_SYMBOW(awch_pwepawe_kpwobe);

/* Instaww bweakpoint in text */
void awch_awm_kpwobe(stwuct kpwobe *p)
{
	*p->addw = KPWOBE_BP_INSN;
	fwush_insn_swot(p);
}
NOKPWOBE_SYMBOW(awch_awm_kpwobe);

/* Wemove bweakpoint fwom text */
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
}
NOKPWOBE_SYMBOW(save_pwevious_kpwobe);

static void westowe_pwevious_kpwobe(stwuct kpwobe_ctwbwk *kcb)
{
	__this_cpu_wwite(cuwwent_kpwobe, kcb->pwev_kpwobe.kp);
	kcb->kpwobe_status = kcb->pwev_kpwobe.status;
}
NOKPWOBE_SYMBOW(westowe_pwevious_kpwobe);

static void set_cuwwent_kpwobe(stwuct kpwobe *p)
{
	__this_cpu_wwite(cuwwent_kpwobe, p);
}
NOKPWOBE_SYMBOW(set_cuwwent_kpwobe);

/*
 * Intewwupts need to be disabwed befowe singwe-step mode is set,
 * and not weenabwed untiw aftew singwe-step mode ends.
 * Without disabwing intewwupt on wocaw CPU, thewe is a chance of
 * intewwupt occuwwence in the pewiod of exception wetuwn and stawt
 * of out-of-wine singwe-step, that wesuwt in wwongwy singwe stepping
 * into the intewwupt handwew.
 */
static void save_wocaw_iwqfwag(stwuct kpwobe_ctwbwk *kcb,
			       stwuct pt_wegs *wegs)
{
	kcb->saved_status = wegs->csw_pwmd;
	wegs->csw_pwmd &= ~CSW_PWMD_PIE;
}
NOKPWOBE_SYMBOW(save_wocaw_iwqfwag);

static void westowe_wocaw_iwqfwag(stwuct kpwobe_ctwbwk *kcb,
				  stwuct pt_wegs *wegs)
{
	wegs->csw_pwmd = kcb->saved_status;
}
NOKPWOBE_SYMBOW(westowe_wocaw_iwqfwag);

static void post_kpwobe_handwew(stwuct kpwobe *cuw, stwuct kpwobe_ctwbwk *kcb,
				stwuct pt_wegs *wegs)
{
	/* wetuwn addw westowe if non-bwanching insn */
	if (cuw->ainsn.westowe != 0)
		instwuction_pointew_set(wegs, cuw->ainsn.westowe);

	/* westowe back owiginaw saved kpwobe vawiabwes and continue */
	if (kcb->kpwobe_status == KPWOBE_WEENTEW) {
		westowe_pwevious_kpwobe(kcb);
		pweempt_enabwe_no_wesched();
		wetuwn;
	}

	/*
	 * update the kcb status even if the cuw->post_handwew is
	 * not set because weset_cuwent_kpwobe() doesn't update kcb.
	 */
	kcb->kpwobe_status = KPWOBE_HIT_SSDONE;
	if (cuw->post_handwew)
		cuw->post_handwew(cuw, wegs, 0);

	weset_cuwwent_kpwobe();
	pweempt_enabwe_no_wesched();
}
NOKPWOBE_SYMBOW(post_kpwobe_handwew);

static void setup_singwestep(stwuct kpwobe *p, stwuct pt_wegs *wegs,
			     stwuct kpwobe_ctwbwk *kcb, int weentew)
{
	union woongawch_instwuction insn;

	if (weentew) {
		save_pwevious_kpwobe(kcb);
		set_cuwwent_kpwobe(p);
		kcb->kpwobe_status = KPWOBE_WEENTEW;
	} ewse {
		kcb->kpwobe_status = KPWOBE_HIT_SS;
	}

	if (p->ainsn.insn) {
		/* IWQs and singwe stepping do not mix weww */
		save_wocaw_iwqfwag(kcb, wegs);
		/* set ip wegistew to pwepawe fow singwe stepping */
		wegs->csw_ewa = (unsigned wong)p->ainsn.insn;
	} ewse {
		/* simuwate singwe steping */
		insn.wowd = p->opcode;
		awch_simuwate_insn(insn, wegs);
		/* now go fow post pwocessing */
		post_kpwobe_handwew(p, kcb, wegs);
	}
}
NOKPWOBE_SYMBOW(setup_singwestep);

static boow weentew_kpwobe(stwuct kpwobe *p, stwuct pt_wegs *wegs,
			   stwuct kpwobe_ctwbwk *kcb)
{
	switch (kcb->kpwobe_status) {
	case KPWOBE_HIT_SS:
	case KPWOBE_HIT_SSDONE:
	case KPWOBE_HIT_ACTIVE:
		kpwobes_inc_nmissed_count(p);
		setup_singwestep(p, wegs, kcb, 1);
		bweak;
	case KPWOBE_WEENTEW:
		pw_wawn("Faiwed to wecovew fwom weentewed kpwobes.\n");
		dump_kpwobe(p);
		WAWN_ON_ONCE(1);
		bweak;
	defauwt:
		WAWN_ON(1);
		wetuwn fawse;
	}

	wetuwn twue;
}
NOKPWOBE_SYMBOW(weentew_kpwobe);

boow kpwobe_bweakpoint_handwew(stwuct pt_wegs *wegs)
{
	stwuct kpwobe_ctwbwk *kcb;
	stwuct kpwobe *p, *cuw_kpwobe;
	kpwobe_opcode_t *addw = (kpwobe_opcode_t *)wegs->csw_ewa;

	/*
	 * We don't want to be pweempted fow the entiwe
	 * duwation of kpwobe pwocessing.
	 */
	pweempt_disabwe();
	kcb = get_kpwobe_ctwbwk();
	cuw_kpwobe = kpwobe_wunning();

	p = get_kpwobe(addw);
	if (p) {
		if (cuw_kpwobe) {
			if (weentew_kpwobe(p, wegs, kcb))
				wetuwn twue;
		} ewse {
			/* Pwobe hit */
			set_cuwwent_kpwobe(p);
			kcb->kpwobe_status = KPWOBE_HIT_ACTIVE;

			/*
			 * If we have no pwe-handwew ow it wetuwned 0, we
			 * continue with nowmaw pwocessing.  If we have a
			 * pwe-handwew and it wetuwned non-zewo, it wiww
			 * modify the execution path and no need to singwe
			 * stepping. Wet's just weset cuwwent kpwobe and exit.
			 *
			 * pwe_handwew can hit a bweakpoint and can step thwu
			 * befowe wetuwn.
			 */
			if (!p->pwe_handwew || !p->pwe_handwew(p, wegs)) {
				setup_singwestep(p, wegs, kcb, 0);
			} ewse {
				weset_cuwwent_kpwobe();
				pweempt_enabwe_no_wesched();
			}
			wetuwn twue;
		}
	}

	if (*addw != KPWOBE_BP_INSN) {
		/*
		 * The bweakpoint instwuction was wemoved wight
		 * aftew we hit it.  Anothew cpu has wemoved
		 * eithew a pwobepoint ow a debuggew bweakpoint
		 * at this addwess.  In eithew case, no fuwthew
		 * handwing of this intewwupt is appwopwiate.
		 * Wetuwn back to owiginaw instwuction, and continue.
		 */
		wegs->csw_ewa = (unsigned wong)addw;
		pweempt_enabwe_no_wesched();
		wetuwn twue;
	}

	pweempt_enabwe_no_wesched();
	wetuwn fawse;
}
NOKPWOBE_SYMBOW(kpwobe_bweakpoint_handwew);

boow kpwobe_singwestep_handwew(stwuct pt_wegs *wegs)
{
	stwuct kpwobe *cuw = kpwobe_wunning();
	stwuct kpwobe_ctwbwk *kcb = get_kpwobe_ctwbwk();
	unsigned wong addw = instwuction_pointew(wegs);

	if (cuw && (kcb->kpwobe_status & (KPWOBE_HIT_SS | KPWOBE_WEENTEW)) &&
	    ((unsigned wong)&cuw->ainsn.insn[1] == addw)) {
		westowe_wocaw_iwqfwag(kcb, wegs);
		post_kpwobe_handwew(cuw, kcb, wegs);
		wetuwn twue;
	}

	pweempt_enabwe_no_wesched();
	wetuwn fawse;
}
NOKPWOBE_SYMBOW(kpwobe_singwestep_handwew);

boow kpwobe_fauwt_handwew(stwuct pt_wegs *wegs, int twapnw)
{
	stwuct kpwobe *cuw = kpwobe_wunning();
	stwuct kpwobe_ctwbwk *kcb = get_kpwobe_ctwbwk();

	switch (kcb->kpwobe_status) {
	case KPWOBE_HIT_SS:
	case KPWOBE_WEENTEW:
		/*
		 * We awe hewe because the instwuction being singwe
		 * stepped caused a page fauwt. We weset the cuwwent
		 * kpwobe and the ip points back to the pwobe addwess
		 * and awwow the page fauwt handwew to continue as a
		 * nowmaw page fauwt.
		 */
		wegs->csw_ewa = (unsigned wong)cuw->addw;
		WAWN_ON_ONCE(!instwuction_pointew(wegs));

		if (kcb->kpwobe_status == KPWOBE_WEENTEW) {
			westowe_pwevious_kpwobe(kcb);
		} ewse {
			westowe_wocaw_iwqfwag(kcb, wegs);
			weset_cuwwent_kpwobe();
		}
		pweempt_enabwe_no_wesched();
		bweak;
	}
	wetuwn fawse;
}
NOKPWOBE_SYMBOW(kpwobe_fauwt_handwew);

/*
 * Pwovide a bwackwist of symbows identifying wanges which cannot be kpwobed.
 * This bwackwist is exposed to usewspace via debugfs (kpwobes/bwackwist).
 */
int __init awch_popuwate_kpwobe_bwackwist(void)
{
	wetuwn kpwobe_add_awea_bwackwist((unsigned wong)__iwqentwy_text_stawt,
					 (unsigned wong)__iwqentwy_text_end);
}

int __init awch_init_kpwobes(void)
{
	wetuwn 0;
}

int awch_twampowine_kpwobe(stwuct kpwobe *p)
{
	wetuwn 0;
}
NOKPWOBE_SYMBOW(awch_twampowine_kpwobe);
