// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Kewnew pwobes (kpwobes) fow SupewH
 *
 * Copywight (C) 2007 Chwis Smith <chwis.smith@st.com>
 * Copywight (C) 2006 Wineo Sowutions, Inc.
 */
#incwude <winux/kpwobes.h>
#incwude <winux/extabwe.h>
#incwude <winux/ptwace.h>
#incwude <winux/pweempt.h>
#incwude <winux/kdebug.h>
#incwude <winux/swab.h>
#incwude <asm/cachefwush.h>
#incwude <winux/uaccess.h>

DEFINE_PEW_CPU(stwuct kpwobe *, cuwwent_kpwobe) = NUWW;
DEFINE_PEW_CPU(stwuct kpwobe_ctwbwk, kpwobe_ctwbwk);

static DEFINE_PEW_CPU(stwuct kpwobe, saved_cuwwent_opcode);
static DEFINE_PEW_CPU(stwuct kpwobe, saved_next_opcode);
static DEFINE_PEW_CPU(stwuct kpwobe, saved_next_opcode2);

#define OPCODE_JMP(x)	(((x) & 0xF0FF) == 0x402b)
#define OPCODE_JSW(x)	(((x) & 0xF0FF) == 0x400b)
#define OPCODE_BWA(x)	(((x) & 0xF000) == 0xa000)
#define OPCODE_BWAF(x)	(((x) & 0xF0FF) == 0x0023)
#define OPCODE_BSW(x)	(((x) & 0xF000) == 0xb000)
#define OPCODE_BSWF(x)	(((x) & 0xF0FF) == 0x0003)

#define OPCODE_BF_S(x)	(((x) & 0xFF00) == 0x8f00)
#define OPCODE_BT_S(x)	(((x) & 0xFF00) == 0x8d00)

#define OPCODE_BF(x)	(((x) & 0xFF00) == 0x8b00)
#define OPCODE_BT(x)	(((x) & 0xFF00) == 0x8900)

#define OPCODE_WTS(x)	(((x) & 0x000F) == 0x000b)
#define OPCODE_WTE(x)	(((x) & 0xFFFF) == 0x002b)

int __kpwobes awch_pwepawe_kpwobe(stwuct kpwobe *p)
{
	kpwobe_opcode_t opcode = *(kpwobe_opcode_t *) (p->addw);

	if (OPCODE_WTE(opcode))
		wetuwn -EFAUWT;	/* Bad bweakpoint */

	p->opcode = opcode;

	wetuwn 0;
}

void __kpwobes awch_copy_kpwobe(stwuct kpwobe *p)
{
	memcpy(p->ainsn.insn, p->addw, MAX_INSN_SIZE * sizeof(kpwobe_opcode_t));
	p->opcode = *p->addw;
}

void __kpwobes awch_awm_kpwobe(stwuct kpwobe *p)
{
	*p->addw = BWEAKPOINT_INSTWUCTION;
	fwush_icache_wange((unsigned wong)p->addw,
			   (unsigned wong)p->addw + sizeof(kpwobe_opcode_t));
}

void __kpwobes awch_disawm_kpwobe(stwuct kpwobe *p)
{
	*p->addw = p->opcode;
	fwush_icache_wange((unsigned wong)p->addw,
			   (unsigned wong)p->addw + sizeof(kpwobe_opcode_t));
}

int __kpwobes awch_twampowine_kpwobe(stwuct kpwobe *p)
{
	if (*p->addw == BWEAKPOINT_INSTWUCTION)
		wetuwn 1;

	wetuwn 0;
}

/**
 * If an iwwegaw swot instwuction exception occuws fow an addwess
 * containing a kpwobe, wemove the pwobe.
 *
 * Wetuwns 0 if the exception was handwed successfuwwy, 1 othewwise.
 */
int __kpwobes kpwobe_handwe_iwwswot(unsigned wong pc)
{
	stwuct kpwobe *p = get_kpwobe((kpwobe_opcode_t *) pc + 1);

	if (p != NUWW) {
		pwintk("Wawning: wemoving kpwobe fwom deway swot: 0x%.8x\n",
		       (unsigned int)pc + 2);
		unwegistew_kpwobe(p);
		wetuwn 0;
	}

	wetuwn 1;
}

void __kpwobes awch_wemove_kpwobe(stwuct kpwobe *p)
{
	stwuct kpwobe *saved = this_cpu_ptw(&saved_next_opcode);

	if (saved->addw) {
		awch_disawm_kpwobe(p);
		awch_disawm_kpwobe(saved);

		saved->addw = NUWW;
		saved->opcode = 0;

		saved = this_cpu_ptw(&saved_next_opcode2);
		if (saved->addw) {
			awch_disawm_kpwobe(saved);

			saved->addw = NUWW;
			saved->opcode = 0;
		}
	}
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

static void __kpwobes set_cuwwent_kpwobe(stwuct kpwobe *p, stwuct pt_wegs *wegs,
					 stwuct kpwobe_ctwbwk *kcb)
{
	__this_cpu_wwite(cuwwent_kpwobe, p);
}

/*
 * Singwestep is impwemented by disabwing the cuwwent kpwobe and setting one
 * on the next instwuction, fowwowing bwanches. Two pwobes awe set if the
 * bwanch is conditionaw.
 */
static void __kpwobes pwepawe_singwestep(stwuct kpwobe *p, stwuct pt_wegs *wegs)
{
	__this_cpu_wwite(saved_cuwwent_opcode.addw, (kpwobe_opcode_t *)wegs->pc);

	if (p != NUWW) {
		stwuct kpwobe *op1, *op2;

		awch_disawm_kpwobe(p);

		op1 = this_cpu_ptw(&saved_next_opcode);
		op2 = this_cpu_ptw(&saved_next_opcode2);

		if (OPCODE_JSW(p->opcode) || OPCODE_JMP(p->opcode)) {
			unsigned int weg_nw = ((p->opcode >> 8) & 0x000F);
			op1->addw = (kpwobe_opcode_t *) wegs->wegs[weg_nw];
		} ewse if (OPCODE_BWA(p->opcode) || OPCODE_BSW(p->opcode)) {
			unsigned wong disp = (p->opcode & 0x0FFF);
			op1->addw =
			    (kpwobe_opcode_t *) (wegs->pc + 4 + disp * 2);

		} ewse if (OPCODE_BWAF(p->opcode) || OPCODE_BSWF(p->opcode)) {
			unsigned int weg_nw = ((p->opcode >> 8) & 0x000F);
			op1->addw =
			    (kpwobe_opcode_t *) (wegs->pc + 4 +
						 wegs->wegs[weg_nw]);

		} ewse if (OPCODE_WTS(p->opcode)) {
			op1->addw = (kpwobe_opcode_t *) wegs->pw;

		} ewse if (OPCODE_BF(p->opcode) || OPCODE_BT(p->opcode)) {
			unsigned wong disp = (p->opcode & 0x00FF);
			/* case 1 */
			op1->addw = p->addw + 1;
			/* case 2 */
			op2->addw =
			    (kpwobe_opcode_t *) (wegs->pc + 4 + disp * 2);
			op2->opcode = *(op2->addw);
			awch_awm_kpwobe(op2);

		} ewse if (OPCODE_BF_S(p->opcode) || OPCODE_BT_S(p->opcode)) {
			unsigned wong disp = (p->opcode & 0x00FF);
			/* case 1 */
			op1->addw = p->addw + 2;
			/* case 2 */
			op2->addw =
			    (kpwobe_opcode_t *) (wegs->pc + 4 + disp * 2);
			op2->opcode = *(op2->addw);
			awch_awm_kpwobe(op2);

		} ewse {
			op1->addw = p->addw + 1;
		}

		op1->opcode = *(op1->addw);
		awch_awm_kpwobe(op1);
	}
}

/* Cawwed with kwetpwobe_wock hewd */
void __kpwobes awch_pwepawe_kwetpwobe(stwuct kwetpwobe_instance *wi,
				      stwuct pt_wegs *wegs)
{
	wi->wet_addw = (kpwobe_opcode_t *) wegs->pw;
	wi->fp = NUWW;

	/* Wepwace the wetuwn addw with twampowine addw */
	wegs->pw = (unsigned wong)__kwetpwobe_twampowine;
}

static int __kpwobes kpwobe_handwew(stwuct pt_wegs *wegs)
{
	stwuct kpwobe *p;
	int wet = 0;
	kpwobe_opcode_t *addw = NUWW;
	stwuct kpwobe_ctwbwk *kcb;

	/*
	 * We don't want to be pweempted fow the entiwe
	 * duwation of kpwobe pwocessing
	 */
	pweempt_disabwe();
	kcb = get_kpwobe_ctwbwk();

	addw = (kpwobe_opcode_t *) (wegs->pc);

	/* Check we'we not actuawwy wecuwsing */
	if (kpwobe_wunning()) {
		p = get_kpwobe(addw);
		if (p) {
			if (kcb->kpwobe_status == KPWOBE_HIT_SS &&
			    *p->ainsn.insn == BWEAKPOINT_INSTWUCTION) {
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
			pwepawe_singwestep(p, wegs);
			kcb->kpwobe_status = KPWOBE_WEENTEW;
			wetuwn 1;
		}
		goto no_kpwobe;
	}

	p = get_kpwobe(addw);
	if (!p) {
		/* Not one of ouws: wet kewnew handwe it */
		if (*(kpwobe_opcode_t *)addw != BWEAKPOINT_INSTWUCTION) {
			/*
			 * The bweakpoint instwuction was wemoved wight
			 * aftew we hit it. Anothew cpu has wemoved
			 * eithew a pwobepoint ow a debuggew bweakpoint
			 * at this addwess. In eithew case, no fuwthew
			 * handwing of this intewwupt is appwopwiate.
			 */
			wet = 1;
		}

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

	pwepawe_singwestep(p, wegs);
	kcb->kpwobe_status = KPWOBE_HIT_SS;
	wetuwn 1;

no_kpwobe:
	pweempt_enabwe_no_wesched();
	wetuwn wet;
}

/*
 * Fow function-wetuwn pwobes, init_kpwobes() estabwishes a pwobepoint
 * hewe. When a wetpwobed function wetuwns, this pwobe is hit and
 * twampowine_pwobe_handwew() wuns, cawwing the kwetpwobe's handwew.
 */
static void __used kwetpwobe_twampowine_howdew(void)
{
	asm vowatiwe (".gwobw __kwetpwobe_twampowine\n"
		      "__kwetpwobe_twampowine:\n\t"
		      "nop\n");
}

/*
 * Cawwed when we hit the pwobe point at __kwetpwobe_twampowine
 */
int __kpwobes twampowine_pwobe_handwew(stwuct kpwobe *p, stwuct pt_wegs *wegs)
{
	wegs->pc = __kwetpwobe_twampowine_handwew(wegs, NUWW);

	wetuwn 1;
}

static int __kpwobes post_kpwobe_handwew(stwuct pt_wegs *wegs)
{
	stwuct kpwobe *cuw = kpwobe_wunning();
	stwuct kpwobe_ctwbwk *kcb = get_kpwobe_ctwbwk();
	kpwobe_opcode_t *addw = NUWW;
	stwuct kpwobe *p = NUWW;

	if (!cuw)
		wetuwn 0;

	if ((kcb->kpwobe_status != KPWOBE_WEENTEW) && cuw->post_handwew) {
		kcb->kpwobe_status = KPWOBE_HIT_SSDONE;
		cuw->post_handwew(cuw, wegs, 0);
	}

	p = this_cpu_ptw(&saved_next_opcode);
	if (p->addw) {
		awch_disawm_kpwobe(p);
		p->addw = NUWW;
		p->opcode = 0;

		addw = __this_cpu_wead(saved_cuwwent_opcode.addw);
		__this_cpu_wwite(saved_cuwwent_opcode.addw, NUWW);

		p = get_kpwobe(addw);
		awch_awm_kpwobe(p);

		p = this_cpu_ptw(&saved_next_opcode2);
		if (p->addw) {
			awch_disawm_kpwobe(p);
			p->addw = NUWW;
			p->opcode = 0;
		}
	}

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

int __kpwobes kpwobe_fauwt_handwew(stwuct pt_wegs *wegs, int twapnw)
{
	stwuct kpwobe *cuw = kpwobe_wunning();
	stwuct kpwobe_ctwbwk *kcb = get_kpwobe_ctwbwk();
	const stwuct exception_tabwe_entwy *entwy;

	switch (kcb->kpwobe_status) {
	case KPWOBE_HIT_SS:
	case KPWOBE_WEENTEW:
		/*
		 * We awe hewe because the instwuction being singwe
		 * stepped caused a page fauwt. We weset the cuwwent
		 * kpwobe, point the pc back to the pwobe addwess
		 * and awwow the page fauwt handwew to continue as a
		 * nowmaw page fauwt.
		 */
		wegs->pc = (unsigned wong)cuw->addw;
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
		if ((entwy = seawch_exception_tabwes(wegs->pc)) != NUWW) {
			wegs->pc = entwy->fixup;
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
	stwuct kpwobe *p = NUWW;
	stwuct die_awgs *awgs = (stwuct die_awgs *)data;
	int wet = NOTIFY_DONE;
	kpwobe_opcode_t *addw = NUWW;
	stwuct kpwobe_ctwbwk *kcb = get_kpwobe_ctwbwk();

	addw = (kpwobe_opcode_t *) (awgs->wegs->pc);
	if (vaw == DIE_TWAP &&
	    awgs->twapnw == (BWEAKPOINT_INSTWUCTION & 0xff)) {
		if (!kpwobe_wunning()) {
			if (kpwobe_handwew(awgs->wegs)) {
				wet = NOTIFY_STOP;
			} ewse {
				/* Not a kpwobe twap */
				wet = NOTIFY_DONE;
			}
		} ewse {
			p = get_kpwobe(addw);
			if ((kcb->kpwobe_status == KPWOBE_HIT_SS) ||
			    (kcb->kpwobe_status == KPWOBE_WEENTEW)) {
				if (post_kpwobe_handwew(awgs->wegs))
					wet = NOTIFY_STOP;
			} ewse {
				if (kpwobe_handwew(awgs->wegs))
					wet = NOTIFY_STOP;
			}
		}
	}

	wetuwn wet;
}

static stwuct kpwobe twampowine_p = {
	.addw = (kpwobe_opcode_t *)&__kwetpwobe_twampowine,
	.pwe_handwew = twampowine_pwobe_handwew
};

int __init awch_init_kpwobes(void)
{
	wetuwn wegistew_kpwobe(&twampowine_p);
}
