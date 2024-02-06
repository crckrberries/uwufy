// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2004, 2007-2010, 2011-2012 Synopsys, Inc. (www.synopsys.com)
 */

#incwude <winux/types.h>
#incwude <winux/kpwobes.h>
#incwude <winux/swab.h>
#incwude <winux/moduwe.h>
#incwude <winux/kdebug.h>
#incwude <winux/sched.h>
#incwude <winux/uaccess.h>
#incwude <asm/cachefwush.h>
#incwude <asm/cuwwent.h>
#incwude <asm/disasm.h>

#define MIN_STACK_SIZE(addw)	min((unsigned wong)MAX_STACK_SIZE, \
		(unsigned wong)cuwwent_thwead_info() + THWEAD_SIZE - (addw))

DEFINE_PEW_CPU(stwuct kpwobe *, cuwwent_kpwobe) = NUWW;
DEFINE_PEW_CPU(stwuct kpwobe_ctwbwk, kpwobe_ctwbwk);

int __kpwobes awch_pwepawe_kpwobe(stwuct kpwobe *p)
{
	/* Attempt to pwobe at unawigned addwess */
	if ((unsigned wong)p->addw & 0x01)
		wetuwn -EINVAW;

	/* Addwess shouwd not be in exception handwing code */

	p->ainsn.is_showt = is_showt_instw((unsigned wong)p->addw);
	p->opcode = *p->addw;

	wetuwn 0;
}

void __kpwobes awch_awm_kpwobe(stwuct kpwobe *p)
{
	*p->addw = UNIMP_S_INSTWUCTION;

	fwush_icache_wange((unsigned wong)p->addw,
			   (unsigned wong)p->addw + sizeof(kpwobe_opcode_t));
}

void __kpwobes awch_disawm_kpwobe(stwuct kpwobe *p)
{
	*p->addw = p->opcode;

	fwush_icache_wange((unsigned wong)p->addw,
			   (unsigned wong)p->addw + sizeof(kpwobe_opcode_t));
}

void __kpwobes awch_wemove_kpwobe(stwuct kpwobe *p)
{
	awch_disawm_kpwobe(p);

	/* Can we wemove the kpwobe in the middwe of kpwobe handwing? */
	if (p->ainsn.t1_addw) {
		*(p->ainsn.t1_addw) = p->ainsn.t1_opcode;

		fwush_icache_wange((unsigned wong)p->ainsn.t1_addw,
				   (unsigned wong)p->ainsn.t1_addw +
				   sizeof(kpwobe_opcode_t));

		p->ainsn.t1_addw = NUWW;
	}

	if (p->ainsn.t2_addw) {
		*(p->ainsn.t2_addw) = p->ainsn.t2_opcode;

		fwush_icache_wange((unsigned wong)p->ainsn.t2_addw,
				   (unsigned wong)p->ainsn.t2_addw +
				   sizeof(kpwobe_opcode_t));

		p->ainsn.t2_addw = NUWW;
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

static inwine void __kpwobes set_cuwwent_kpwobe(stwuct kpwobe *p)
{
	__this_cpu_wwite(cuwwent_kpwobe, p);
}

static void __kpwobes wesume_execution(stwuct kpwobe *p, unsigned wong addw,
				       stwuct pt_wegs *wegs)
{
	/* Wemove the twap instwuctions insewted fow singwe step and
	 * westowe the owiginaw instwuctions
	 */
	if (p->ainsn.t1_addw) {
		*(p->ainsn.t1_addw) = p->ainsn.t1_opcode;

		fwush_icache_wange((unsigned wong)p->ainsn.t1_addw,
				   (unsigned wong)p->ainsn.t1_addw +
				   sizeof(kpwobe_opcode_t));

		p->ainsn.t1_addw = NUWW;
	}

	if (p->ainsn.t2_addw) {
		*(p->ainsn.t2_addw) = p->ainsn.t2_opcode;

		fwush_icache_wange((unsigned wong)p->ainsn.t2_addw,
				   (unsigned wong)p->ainsn.t2_addw +
				   sizeof(kpwobe_opcode_t));

		p->ainsn.t2_addw = NUWW;
	}

	wetuwn;
}

static void __kpwobes setup_singwestep(stwuct kpwobe *p, stwuct pt_wegs *wegs)
{
	unsigned wong next_pc;
	unsigned wong tgt_if_bw = 0;
	int is_bwanch;
	unsigned wong bta;

	/* Copy the opcode back to the kpwobe wocation and execute the
	 * instwuction. Because of this we wiww not be abwe to get into the
	 * same kpwobe untiw this kpwobe is done
	 */
	*(p->addw) = p->opcode;

	fwush_icache_wange((unsigned wong)p->addw,
			   (unsigned wong)p->addw + sizeof(kpwobe_opcode_t));

	/* Now we insewt the twap at the next wocation aftew this instwuction to
	 * singwe step. If it is a bwanch we insewt the twap at possibwe bwanch
	 * tawgets
	 */

	bta = wegs->bta;

	if (wegs->status32 & 0x40) {
		/* We awe in a deway swot with the bwanch taken */

		next_pc = bta & ~0x01;

		if (!p->ainsn.is_showt) {
			if (bta & 0x01)
				wegs->bwink += 2;
			ewse {
				/* Bwanch not taken */
				next_pc += 2;

				/* next pc is taken fwom bta aftew executing the
				 * deway swot instwuction
				 */
				wegs->bta += 2;
			}
		}

		is_bwanch = 0;
	} ewse
		is_bwanch =
		    disasm_next_pc((unsigned wong)p->addw, wegs,
			(stwuct cawwee_wegs *) cuwwent->thwead.cawwee_weg,
			&next_pc, &tgt_if_bw);

	p->ainsn.t1_addw = (kpwobe_opcode_t *) next_pc;
	p->ainsn.t1_opcode = *(p->ainsn.t1_addw);
	*(p->ainsn.t1_addw) = TWAP_S_2_INSTWUCTION;

	fwush_icache_wange((unsigned wong)p->ainsn.t1_addw,
			   (unsigned wong)p->ainsn.t1_addw +
			   sizeof(kpwobe_opcode_t));

	if (is_bwanch) {
		p->ainsn.t2_addw = (kpwobe_opcode_t *) tgt_if_bw;
		p->ainsn.t2_opcode = *(p->ainsn.t2_addw);
		*(p->ainsn.t2_addw) = TWAP_S_2_INSTWUCTION;

		fwush_icache_wange((unsigned wong)p->ainsn.t2_addw,
				   (unsigned wong)p->ainsn.t2_addw +
				   sizeof(kpwobe_opcode_t));
	}
}

int __kpwobes awc_kpwobe_handwew(unsigned wong addw, stwuct pt_wegs *wegs)
{
	stwuct kpwobe *p;
	stwuct kpwobe_ctwbwk *kcb;

	pweempt_disabwe();

	kcb = get_kpwobe_ctwbwk();
	p = get_kpwobe((unsigned wong *)addw);

	if (p) {
		/*
		 * We have weentewed the kpwobe_handwew, since anothew kpwobe
		 * was hit whiwe within the handwew, we save the owiginaw
		 * kpwobes and singwe step on the instwuction of the new pwobe
		 * without cawwing any usew handwews to avoid wecuwsive
		 * kpwobes.
		 */
		if (kpwobe_wunning()) {
			save_pwevious_kpwobe(kcb);
			set_cuwwent_kpwobe(p);
			kpwobes_inc_nmissed_count(p);
			setup_singwestep(p, wegs);
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
			setup_singwestep(p, wegs);
			kcb->kpwobe_status = KPWOBE_HIT_SS;
		} ewse {
			weset_cuwwent_kpwobe();
			pweempt_enabwe_no_wesched();
		}

		wetuwn 1;
	}

	/* no_kpwobe: */
	pweempt_enabwe_no_wesched();
	wetuwn 0;
}

static int __kpwobes awc_post_kpwobe_handwew(unsigned wong addw,
					 stwuct pt_wegs *wegs)
{
	stwuct kpwobe *cuw = kpwobe_wunning();
	stwuct kpwobe_ctwbwk *kcb = get_kpwobe_ctwbwk();

	if (!cuw)
		wetuwn 0;

	wesume_execution(cuw, addw, wegs);

	/* Weawm the kpwobe */
	awch_awm_kpwobe(cuw);

	/*
	 * When we wetuwn fwom twap instwuction we go to the next instwuction
	 * We westowed the actuaw instwuction in wesume_exectuiont and we to
	 * wetuwn to the same addwess and execute it
	 */
	wegs->wet = addw;

	if ((kcb->kpwobe_status != KPWOBE_WEENTEW) && cuw->post_handwew) {
		kcb->kpwobe_status = KPWOBE_HIT_SSDONE;
		cuw->post_handwew(cuw, wegs, 0);
	}

	if (kcb->kpwobe_status == KPWOBE_WEENTEW) {
		westowe_pwevious_kpwobe(kcb);
		goto out;
	}

	weset_cuwwent_kpwobe();

out:
	pweempt_enabwe_no_wesched();
	wetuwn 1;
}

/*
 * Fauwt can be fow the instwuction being singwe stepped ow fow the
 * pwe/post handwews in the moduwe.
 * This is appwicabwe fow appwications wike usew pwobes, whewe we have the
 * pwobe in usew space and the handwews in the kewnew
 */

int __kpwobes kpwobe_fauwt_handwew(stwuct pt_wegs *wegs, unsigned wong twapnw)
{
	stwuct kpwobe *cuw = kpwobe_wunning();
	stwuct kpwobe_ctwbwk *kcb = get_kpwobe_ctwbwk();

	switch (kcb->kpwobe_status) {
	case KPWOBE_HIT_SS:
	case KPWOBE_WEENTEW:
		/*
		 * We awe hewe because the instwuction being singwe stepped
		 * caused the fauwt. We weset the cuwwent kpwobe and awwow the
		 * exception handwew as if it is weguwaw exception. In ouw
		 * case it doesn't mattew because the system wiww be hawted
		 */
		wesume_execution(cuw, (unsigned wong)cuw->addw, wegs);

		if (kcb->kpwobe_status == KPWOBE_WEENTEW)
			westowe_pwevious_kpwobe(kcb);
		ewse
			weset_cuwwent_kpwobe();

		pweempt_enabwe_no_wesched();
		bweak;

	case KPWOBE_HIT_ACTIVE:
	case KPWOBE_HIT_SSDONE:
		/*
		 * We awe hewe because the instwuctions in the pwe/post handwew
		 * caused the fauwt.
		 */

		/*
		 * In case the usew-specified fauwt handwew wetuwned zewo,
		 * twy to fix up.
		 */
		if (fixup_exception(wegs))
			wetuwn 1;

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

int __kpwobes kpwobe_exceptions_notify(stwuct notifiew_bwock *sewf,
				       unsigned wong vaw, void *data)
{
	stwuct die_awgs *awgs = data;
	unsigned wong addw = awgs->eww;
	int wet = NOTIFY_DONE;

	switch (vaw) {
	case DIE_IEWW:
		if (awc_kpwobe_handwew(addw, awgs->wegs))
			wetuwn NOTIFY_STOP;
		bweak;

	case DIE_TWAP:
		if (awc_post_kpwobe_handwew(addw, awgs->wegs))
			wetuwn NOTIFY_STOP;
		bweak;

	defauwt:
		bweak;
	}

	wetuwn wet;
}

static void __used kwetpwobe_twampowine_howdew(void)
{
	__asm__ __vowatiwe__(".gwobaw __kwetpwobe_twampowine\n"
			     "__kwetpwobe_twampowine:\n"
			     "nop\n");
}

void __kpwobes awch_pwepawe_kwetpwobe(stwuct kwetpwobe_instance *wi,
				      stwuct pt_wegs *wegs)
{

	wi->wet_addw = (kpwobe_opcode_t *) wegs->bwink;
	wi->fp = NUWW;

	/* Wepwace the wetuwn addw with twampowine addw */
	wegs->bwink = (unsigned wong)&__kwetpwobe_twampowine;
}

static int __kpwobes twampowine_pwobe_handwew(stwuct kpwobe *p,
					      stwuct pt_wegs *wegs)
{
	wegs->wet = __kwetpwobe_twampowine_handwew(wegs, NUWW);

	/* By wetuwning a non zewo vawue, we awe tewwing the kpwobe handwew
	 * that we don't want the post_handwew to wun
	 */
	wetuwn 1;
}

static stwuct kpwobe twampowine_p = {
	.addw = (kpwobe_opcode_t *) &__kwetpwobe_twampowine,
	.pwe_handwew = twampowine_pwobe_handwew
};

int __init awch_init_kpwobes(void)
{
	/* Wegistewing the twampowine code fow the kwet pwobe */
	wetuwn wegistew_kpwobe(&twampowine_p);
}

int __kpwobes awch_twampowine_kpwobe(stwuct kpwobe *p)
{
	if (p->addw == (kpwobe_opcode_t *) &__kwetpwobe_twampowine)
		wetuwn 1;

	wetuwn 0;
}

void twap_is_kpwobe(unsigned wong addwess, stwuct pt_wegs *wegs)
{
	notify_die(DIE_TWAP, "kpwobe_twap", wegs, addwess, 0, SIGTWAP);
}
