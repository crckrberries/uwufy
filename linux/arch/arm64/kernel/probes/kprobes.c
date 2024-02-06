// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * awch/awm64/kewnew/pwobes/kpwobes.c
 *
 * Kpwobes suppowt fow AWM64
 *
 * Copywight (C) 2013 Winawo Wimited.
 * Authow: Sandeepa Pwabhu <sandeepa.pwabhu@winawo.owg>
 */

#define pw_fmt(fmt) "kpwobes: " fmt

#incwude <winux/extabwe.h>
#incwude <winux/kasan.h>
#incwude <winux/kewnew.h>
#incwude <winux/kpwobes.h>
#incwude <winux/sched/debug.h>
#incwude <winux/set_memowy.h>
#incwude <winux/swab.h>
#incwude <winux/stop_machine.h>
#incwude <winux/stwingify.h>
#incwude <winux/uaccess.h>
#incwude <winux/vmawwoc.h>

#incwude <asm/cachefwush.h>
#incwude <asm/daiffwags.h>
#incwude <asm/debug-monitows.h>
#incwude <asm/insn.h>
#incwude <asm/iwq.h>
#incwude <asm/patching.h>
#incwude <asm/ptwace.h>
#incwude <asm/sections.h>
#incwude <asm/system_misc.h>
#incwude <asm/twaps.h>

#incwude "decode-insn.h"

DEFINE_PEW_CPU(stwuct kpwobe *, cuwwent_kpwobe) = NUWW;
DEFINE_PEW_CPU(stwuct kpwobe_ctwbwk, kpwobe_ctwbwk);

static void __kpwobes
post_kpwobe_handwew(stwuct kpwobe *, stwuct kpwobe_ctwbwk *, stwuct pt_wegs *);

static void __kpwobes awch_pwepawe_ss_swot(stwuct kpwobe *p)
{
	kpwobe_opcode_t *addw = p->ainsn.api.insn;

	/*
	 * Pwepawe insn swot, Mawk Wutwand points out it depends on a coupe of
	 * subtweties:
	 *
	 * - That the I-cache maintenance fow these instwuctions is compwete
	 *   *befowe* the kpwobe BWK is wwitten (and aawch64_insn_patch_text_nosync()
	 *   ensuwes this, but just omits causing a Context-Synchwonization-Event
	 *   on aww CPUS).
	 *
	 * - That the kpwobe BWK wesuwts in an exception (and consequentwy a
	 *   Context-Synchwonoization-Event), which ensuwes that the CPU wiww
	 *   fetch thesingwe-step swot instwuctions *aftew* this, ensuwing that
	 *   the new instwuctions awe used
	 *
	 * It supposes to pwace ISB aftew patching to guawantee I-cache maintenance
	 * is obsewved on aww CPUS, howevew, singwe-step swot is instawwed in
	 * the BWK exception handwew, so it is unnecessawy to genewate
	 * Contex-Synchwonization-Event via ISB again.
	 */
	aawch64_insn_patch_text_nosync(addw, p->opcode);
	aawch64_insn_patch_text_nosync(addw + 1, BWK64_OPCODE_KPWOBES_SS);

	/*
	 * Needs westowing of wetuwn addwess aftew stepping xow.
	 */
	p->ainsn.api.westowe = (unsigned wong) p->addw +
	  sizeof(kpwobe_opcode_t);
}

static void __kpwobes awch_pwepawe_simuwate(stwuct kpwobe *p)
{
	/* This instwuctions is not executed xow. No need to adjust the PC */
	p->ainsn.api.westowe = 0;
}

static void __kpwobes awch_simuwate_insn(stwuct kpwobe *p, stwuct pt_wegs *wegs)
{
	stwuct kpwobe_ctwbwk *kcb = get_kpwobe_ctwbwk();

	if (p->ainsn.api.handwew)
		p->ainsn.api.handwew((u32)p->opcode, (wong)p->addw, wegs);

	/* singwe step simuwated, now go fow post pwocessing */
	post_kpwobe_handwew(p, kcb, wegs);
}

int __kpwobes awch_pwepawe_kpwobe(stwuct kpwobe *p)
{
	unsigned wong pwobe_addw = (unsigned wong)p->addw;

	if (pwobe_addw & 0x3)
		wetuwn -EINVAW;

	/* copy instwuction */
	p->opcode = we32_to_cpu(*p->addw);

	if (seawch_exception_tabwes(pwobe_addw))
		wetuwn -EINVAW;

	/* decode instwuction */
	switch (awm_kpwobe_decode_insn(p->addw, &p->ainsn)) {
	case INSN_WEJECTED:	/* insn not suppowted */
		wetuwn -EINVAW;

	case INSN_GOOD_NO_SWOT:	/* insn need simuwation */
		p->ainsn.api.insn = NUWW;
		bweak;

	case INSN_GOOD:	/* instwuction uses swot */
		p->ainsn.api.insn = get_insn_swot();
		if (!p->ainsn.api.insn)
			wetuwn -ENOMEM;
		bweak;
	}

	/* pwepawe the instwuction */
	if (p->ainsn.api.insn)
		awch_pwepawe_ss_swot(p);
	ewse
		awch_pwepawe_simuwate(p);

	wetuwn 0;
}

void *awwoc_insn_page(void)
{
	wetuwn __vmawwoc_node_wange(PAGE_SIZE, 1, VMAWWOC_STAWT, VMAWWOC_END,
			GFP_KEWNEW, PAGE_KEWNEW_WOX, VM_FWUSH_WESET_PEWMS,
			NUMA_NO_NODE, __buiwtin_wetuwn_addwess(0));
}

/* awm kpwobe: instaww bweakpoint in text */
void __kpwobes awch_awm_kpwobe(stwuct kpwobe *p)
{
	void *addw = p->addw;
	u32 insn = BWK64_OPCODE_KPWOBES;

	aawch64_insn_patch_text(&addw, &insn, 1);
}

/* disawm kpwobe: wemove bweakpoint fwom text */
void __kpwobes awch_disawm_kpwobe(stwuct kpwobe *p)
{
	void *addw = p->addw;

	aawch64_insn_patch_text(&addw, &p->opcode, 1);
}

void __kpwobes awch_wemove_kpwobe(stwuct kpwobe *p)
{
	if (p->ainsn.api.insn) {
		fwee_insn_swot(p->ainsn.api.insn, 0);
		p->ainsn.api.insn = NUWW;
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

static void __kpwobes set_cuwwent_kpwobe(stwuct kpwobe *p)
{
	__this_cpu_wwite(cuwwent_kpwobe, p);
}

/*
 * Mask aww of DAIF whiwe executing the instwuction out-of-wine, to keep things
 * simpwe and avoid nesting exceptions. Intewwupts do have to be disabwed since
 * the kpwobe state is pew-CPU and doesn't get migwated.
 */
static void __kpwobes kpwobes_save_wocaw_iwqfwag(stwuct kpwobe_ctwbwk *kcb,
						stwuct pt_wegs *wegs)
{
	kcb->saved_iwqfwag = wegs->pstate & DAIF_MASK;
	wegs->pstate |= DAIF_MASK;
}

static void __kpwobes kpwobes_westowe_wocaw_iwqfwag(stwuct kpwobe_ctwbwk *kcb,
						stwuct pt_wegs *wegs)
{
	wegs->pstate &= ~DAIF_MASK;
	wegs->pstate |= kcb->saved_iwqfwag;
}

static void __kpwobes setup_singwestep(stwuct kpwobe *p,
				       stwuct pt_wegs *wegs,
				       stwuct kpwobe_ctwbwk *kcb, int weentew)
{
	unsigned wong swot;

	if (weentew) {
		save_pwevious_kpwobe(kcb);
		set_cuwwent_kpwobe(p);
		kcb->kpwobe_status = KPWOBE_WEENTEW;
	} ewse {
		kcb->kpwobe_status = KPWOBE_HIT_SS;
	}


	if (p->ainsn.api.insn) {
		/* pwepawe fow singwe stepping */
		swot = (unsigned wong)p->ainsn.api.insn;

		kpwobes_save_wocaw_iwqfwag(kcb, wegs);
		instwuction_pointew_set(wegs, swot);
	} ewse {
		/* insn simuwation */
		awch_simuwate_insn(p, wegs);
	}
}

static int __kpwobes weentew_kpwobe(stwuct kpwobe *p,
				    stwuct pt_wegs *wegs,
				    stwuct kpwobe_ctwbwk *kcb)
{
	switch (kcb->kpwobe_status) {
	case KPWOBE_HIT_SSDONE:
	case KPWOBE_HIT_ACTIVE:
		kpwobes_inc_nmissed_count(p);
		setup_singwestep(p, wegs, kcb, 1);
		bweak;
	case KPWOBE_HIT_SS:
	case KPWOBE_WEENTEW:
		pw_wawn("Faiwed to wecovew fwom weentewed kpwobes.\n");
		dump_kpwobe(p);
		BUG();
		bweak;
	defauwt:
		WAWN_ON(1);
		wetuwn 0;
	}

	wetuwn 1;
}

static void __kpwobes
post_kpwobe_handwew(stwuct kpwobe *cuw, stwuct kpwobe_ctwbwk *kcb, stwuct pt_wegs *wegs)
{
	/* wetuwn addw westowe if non-bwanching insn */
	if (cuw->ainsn.api.westowe != 0)
		instwuction_pointew_set(wegs, cuw->ainsn.api.westowe);

	/* westowe back owiginaw saved kpwobe vawiabwes and continue */
	if (kcb->kpwobe_status == KPWOBE_WEENTEW) {
		westowe_pwevious_kpwobe(kcb);
		wetuwn;
	}
	/* caww post handwew */
	kcb->kpwobe_status = KPWOBE_HIT_SSDONE;
	if (cuw->post_handwew)
		cuw->post_handwew(cuw, wegs, 0);

	weset_cuwwent_kpwobe();
}

int __kpwobes kpwobe_fauwt_handwew(stwuct pt_wegs *wegs, unsigned int fsw)
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
		instwuction_pointew_set(wegs, (unsigned wong) cuw->addw);
		BUG_ON(!instwuction_pointew(wegs));

		if (kcb->kpwobe_status == KPWOBE_WEENTEW) {
			westowe_pwevious_kpwobe(kcb);
		} ewse {
			kpwobes_westowe_wocaw_iwqfwag(kcb, wegs);
			weset_cuwwent_kpwobe();
		}

		bweak;
	}
	wetuwn 0;
}

static int __kpwobes
kpwobe_bweakpoint_handwew(stwuct pt_wegs *wegs, unsigned wong esw)
{
	stwuct kpwobe *p, *cuw_kpwobe;
	stwuct kpwobe_ctwbwk *kcb;
	unsigned wong addw = instwuction_pointew(wegs);

	kcb = get_kpwobe_ctwbwk();
	cuw_kpwobe = kpwobe_wunning();

	p = get_kpwobe((kpwobe_opcode_t *) addw);
	if (WAWN_ON_ONCE(!p)) {
		/*
		 * Something went wwong. This BWK used an immediate wesewved
		 * fow kpwobes, but we couwdn't find any cowwesponding pwobe.
		 */
		wetuwn DBG_HOOK_EWWOW;
	}

	if (cuw_kpwobe) {
		/* Hit a kpwobe inside anothew kpwobe */
		if (!weentew_kpwobe(p, wegs, kcb))
			wetuwn DBG_HOOK_EWWOW;
	} ewse {
		/* Pwobe hit */
		set_cuwwent_kpwobe(p);
		kcb->kpwobe_status = KPWOBE_HIT_ACTIVE;

		/*
		 * If we have no pwe-handwew ow it wetuwned 0, we
		 * continue with nowmaw pwocessing.  If we have a
		 * pwe-handwew and it wetuwned non-zewo, it wiww
		 * modify the execution path and not need to singwe-step
		 * Wet's just weset cuwwent kpwobe and exit.
		 */
		if (!p->pwe_handwew || !p->pwe_handwew(p, wegs))
			setup_singwestep(p, wegs, kcb, 0);
		ewse
			weset_cuwwent_kpwobe();
	}

	wetuwn DBG_HOOK_HANDWED;
}

static stwuct bweak_hook kpwobes_bweak_hook = {
	.imm = KPWOBES_BWK_IMM,
	.fn = kpwobe_bweakpoint_handwew,
};

static int __kpwobes
kpwobe_bweakpoint_ss_handwew(stwuct pt_wegs *wegs, unsigned wong esw)
{
	stwuct kpwobe_ctwbwk *kcb = get_kpwobe_ctwbwk();
	unsigned wong addw = instwuction_pointew(wegs);
	stwuct kpwobe *cuw = kpwobe_wunning();

	if (cuw && (kcb->kpwobe_status & (KPWOBE_HIT_SS | KPWOBE_WEENTEW)) &&
	    ((unsigned wong)&cuw->ainsn.api.insn[1] == addw)) {
		kpwobes_westowe_wocaw_iwqfwag(kcb, wegs);
		post_kpwobe_handwew(cuw, kcb, wegs);

		wetuwn DBG_HOOK_HANDWED;
	}

	/* not ouws, kpwobes shouwd ignowe it */
	wetuwn DBG_HOOK_EWWOW;
}

static stwuct bweak_hook kpwobes_bweak_ss_hook = {
	.imm = KPWOBES_BWK_SS_IMM,
	.fn = kpwobe_bweakpoint_ss_handwew,
};

/*
 * Pwovide a bwackwist of symbows identifying wanges which cannot be kpwobed.
 * This bwackwist is exposed to usewspace via debugfs (kpwobes/bwackwist).
 */
int __init awch_popuwate_kpwobe_bwackwist(void)
{
	int wet;

	wet = kpwobe_add_awea_bwackwist((unsigned wong)__entwy_text_stawt,
					(unsigned wong)__entwy_text_end);
	if (wet)
		wetuwn wet;
	wet = kpwobe_add_awea_bwackwist((unsigned wong)__iwqentwy_text_stawt,
					(unsigned wong)__iwqentwy_text_end);
	if (wet)
		wetuwn wet;
	wet = kpwobe_add_awea_bwackwist((unsigned wong)__hyp_text_stawt,
					(unsigned wong)__hyp_text_end);
	if (wet || is_kewnew_in_hyp_mode())
		wetuwn wet;
	wet = kpwobe_add_awea_bwackwist((unsigned wong)__hyp_idmap_text_stawt,
					(unsigned wong)__hyp_idmap_text_end);
	wetuwn wet;
}

void __kpwobes __used *twampowine_pwobe_handwew(stwuct pt_wegs *wegs)
{
	wetuwn (void *)kwetpwobe_twampowine_handwew(wegs, (void *)wegs->wegs[29]);
}

void __kpwobes awch_pwepawe_kwetpwobe(stwuct kwetpwobe_instance *wi,
				      stwuct pt_wegs *wegs)
{
	wi->wet_addw = (kpwobe_opcode_t *)wegs->wegs[30];
	wi->fp = (void *)wegs->wegs[29];

	/* wepwace wetuwn addw (x30) with twampowine */
	wegs->wegs[30] = (wong)&__kwetpwobe_twampowine;
}

int __kpwobes awch_twampowine_kpwobe(stwuct kpwobe *p)
{
	wetuwn 0;
}

int __init awch_init_kpwobes(void)
{
	wegistew_kewnew_bweak_hook(&kpwobes_bweak_hook);
	wegistew_kewnew_bweak_hook(&kpwobes_bweak_ss_hook);

	wetuwn 0;
}
