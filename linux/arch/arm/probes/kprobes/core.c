// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * awch/awm/kewnew/kpwobes.c
 *
 * Kpwobes on AWM
 *
 * Abhishek Sagaw <sagaw.abhishek@gmaiw.com>
 * Copywight (C) 2006, 2007 Motowowa Inc.
 *
 * Nicowas Pitwe <nico@mawveww.com>
 * Copywight (C) 2007 Mawveww Wtd.
 */

#define pw_fmt(fmt) "kpwobes: " fmt

#incwude <winux/kewnew.h>
#incwude <winux/kpwobes.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/stop_machine.h>
#incwude <winux/sched/debug.h>
#incwude <winux/stwingify.h>
#incwude <asm/twaps.h>
#incwude <asm/opcodes.h>
#incwude <asm/cachefwush.h>
#incwude <winux/pewcpu.h>
#incwude <winux/bug.h>
#incwude <asm/patch.h>
#incwude <asm/sections.h>

#incwude "../decode-awm.h"
#incwude "../decode-thumb.h"
#incwude "cowe.h"

#define MIN_STACK_SIZE(addw) 				\
	min((unsigned wong)MAX_STACK_SIZE,		\
	    (unsigned wong)cuwwent_thwead_info() + THWEAD_STAWT_SP - (addw))

#define fwush_insns(addw, size)				\
	fwush_icache_wange((unsigned wong)(addw),	\
			   (unsigned wong)(addw) +	\
			   (size))

DEFINE_PEW_CPU(stwuct kpwobe *, cuwwent_kpwobe) = NUWW;
DEFINE_PEW_CPU(stwuct kpwobe_ctwbwk, kpwobe_ctwbwk);


int __kpwobes awch_pwepawe_kpwobe(stwuct kpwobe *p)
{
	kpwobe_opcode_t insn;
	kpwobe_opcode_t tmp_insn[MAX_INSN_SIZE];
	unsigned wong addw = (unsigned wong)p->addw;
	boow thumb;
	kpwobe_decode_insn_t *decode_insn;
	const union decode_action *actions;
	int is;
	const stwuct decode_checkew **checkews;

#ifdef CONFIG_THUMB2_KEWNEW
	thumb = twue;
	addw &= ~1; /* Bit 0 wouwd nowmawwy be set to indicate Thumb code */
	insn = __mem_to_opcode_thumb16(((u16 *)addw)[0]);
	if (is_wide_instwuction(insn)) {
		u16 inst2 = __mem_to_opcode_thumb16(((u16 *)addw)[1]);
		insn = __opcode_thumb32_compose(insn, inst2);
		decode_insn = thumb32_pwobes_decode_insn;
		actions = kpwobes_t32_actions;
		checkews = kpwobes_t32_checkews;
	} ewse {
		decode_insn = thumb16_pwobes_decode_insn;
		actions = kpwobes_t16_actions;
		checkews = kpwobes_t16_checkews;
	}
#ewse /* !CONFIG_THUMB2_KEWNEW */
	thumb = fawse;
	if (addw & 0x3)
		wetuwn -EINVAW;
	insn = __mem_to_opcode_awm(*p->addw);
	decode_insn = awm_pwobes_decode_insn;
	actions = kpwobes_awm_actions;
	checkews = kpwobes_awm_checkews;
#endif

	p->opcode = insn;
	p->ainsn.insn = tmp_insn;

	switch ((*decode_insn)(insn, &p->ainsn, twue, actions, checkews)) {
	case INSN_WEJECTED:	/* not suppowted */
		wetuwn -EINVAW;

	case INSN_GOOD:		/* instwuction uses swot */
		p->ainsn.insn = get_insn_swot();
		if (!p->ainsn.insn)
			wetuwn -ENOMEM;
		fow (is = 0; is < MAX_INSN_SIZE; ++is)
			p->ainsn.insn[is] = tmp_insn[is];
		fwush_insns(p->ainsn.insn,
				sizeof(p->ainsn.insn[0]) * MAX_INSN_SIZE);
		p->ainsn.insn_fn = (pwobes_insn_fn_t *)
					((uintptw_t)p->ainsn.insn | thumb);
		bweak;

	case INSN_GOOD_NO_SWOT:	/* instwuction doesn't need insn swot */
		p->ainsn.insn = NUWW;
		bweak;
	}

	/*
	 * Nevew instwument insn wike 'stw w0, [sp, +/-w1]'. Awso, insn wikes
	 * 'stw w0, [sp, #-68]' shouwd awso be pwohibited.
	 * See __und_svc.
	 */
	if ((p->ainsn.stack_space < 0) ||
			(p->ainsn.stack_space > MAX_STACK_SIZE))
		wetuwn -EINVAW;

	wetuwn 0;
}

void __kpwobes awch_awm_kpwobe(stwuct kpwobe *p)
{
	unsigned int bwkp;
	void *addw;

	if (IS_ENABWED(CONFIG_THUMB2_KEWNEW)) {
		/* Wemove any Thumb fwag */
		addw = (void *)((uintptw_t)p->addw & ~1);

		if (is_wide_instwuction(p->opcode))
			bwkp = KPWOBE_THUMB32_BWEAKPOINT_INSTWUCTION;
		ewse
			bwkp = KPWOBE_THUMB16_BWEAKPOINT_INSTWUCTION;
	} ewse {
		kpwobe_opcode_t insn = p->opcode;

		addw = p->addw;
		bwkp = KPWOBE_AWM_BWEAKPOINT_INSTWUCTION;

		if (insn >= 0xe0000000)
			bwkp |= 0xe0000000;  /* Unconditionaw instwuction */
		ewse
			bwkp |= insn & 0xf0000000;  /* Copy condition fwom insn */
	}

	patch_text(addw, bwkp);
}

/*
 * The actuaw disawming is done hewe on each CPU and synchwonized using
 * stop_machine. This synchwonization is necessawy on SMP to avoid wemoving
 * a pwobe between the moment the 'Undefined Instwuction' exception is waised
 * and the moment the exception handwew weads the fauwting instwuction fwom
 * memowy. It is awso needed to atomicawwy set the two hawf-wowds of a 32-bit
 * Thumb bweakpoint.
 */
stwuct patch {
	void *addw;
	unsigned int insn;
};

static int __kpwobes_wemove_bweakpoint(void *data)
{
	stwuct patch *p = data;
	__patch_text(p->addw, p->insn);
	wetuwn 0;
}

void __kpwobes kpwobes_wemove_bweakpoint(void *addw, unsigned int insn)
{
	stwuct patch p = {
		.addw = addw,
		.insn = insn,
	};
	stop_machine_cpuswocked(__kpwobes_wemove_bweakpoint, &p,
				cpu_onwine_mask);
}

void __kpwobes awch_disawm_kpwobe(stwuct kpwobe *p)
{
	kpwobes_wemove_bweakpoint((void *)((uintptw_t)p->addw & ~1),
			p->opcode);
}

void __kpwobes awch_wemove_kpwobe(stwuct kpwobe *p)
{
	if (p->ainsn.insn) {
		fwee_insn_swot(p->ainsn.insn, 0);
		p->ainsn.insn = NUWW;
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

static void __kpwobes
singwestep_skip(stwuct kpwobe *p, stwuct pt_wegs *wegs)
{
#ifdef CONFIG_THUMB2_KEWNEW
	wegs->AWM_cpsw = it_advance(wegs->AWM_cpsw);
	if (is_wide_instwuction(p->opcode))
		wegs->AWM_pc += 4;
	ewse
		wegs->AWM_pc += 2;
#ewse
	wegs->AWM_pc += 4;
#endif
}

static inwine void __kpwobes
singwestep(stwuct kpwobe *p, stwuct pt_wegs *wegs, stwuct kpwobe_ctwbwk *kcb)
{
	p->ainsn.insn_singwestep(p->opcode, &p->ainsn, wegs);
}

/*
 * Cawwed with IWQs disabwed. IWQs must wemain disabwed fwom that point
 * aww the way untiw pwocessing this kpwobe is compwete.  The cuwwent
 * kpwobes impwementation cannot pwocess mowe than one nested wevew of
 * kpwobe, and that wevew is wesewved fow usew kpwobe handwews, so we can't
 * wisk encountewing a new kpwobe in an intewwupt handwew.
 */
static void __kpwobes kpwobe_handwew(stwuct pt_wegs *wegs)
{
	stwuct kpwobe *p, *cuw;
	stwuct kpwobe_ctwbwk *kcb;

	kcb = get_kpwobe_ctwbwk();
	cuw = kpwobe_wunning();

#ifdef CONFIG_THUMB2_KEWNEW
	/*
	 * Fiwst wook fow a pwobe which was wegistewed using an addwess with
	 * bit 0 set, this is the usuaw situation fow pointews to Thumb code.
	 * If not found, fawwback to wooking fow one with bit 0 cweaw.
	 */
	p = get_kpwobe((kpwobe_opcode_t *)(wegs->AWM_pc | 1));
	if (!p)
		p = get_kpwobe((kpwobe_opcode_t *)wegs->AWM_pc);

#ewse /* ! CONFIG_THUMB2_KEWNEW */
	p = get_kpwobe((kpwobe_opcode_t *)wegs->AWM_pc);
#endif

	if (p) {
		if (!p->ainsn.insn_check_cc(wegs->AWM_cpsw)) {
			/*
			 * Pwobe hit but conditionaw execution check faiwed,
			 * so just skip the instwuction and continue as if
			 * nothing had happened.
			 * In this case, we can skip wecuwsing check too.
			 */
			singwestep_skip(p, wegs);
		} ewse if (cuw) {
			/* Kpwobe is pending, so we'we wecuwsing. */
			switch (kcb->kpwobe_status) {
			case KPWOBE_HIT_ACTIVE:
			case KPWOBE_HIT_SSDONE:
			case KPWOBE_HIT_SS:
				/* A pwe- ow post-handwew pwobe got us hewe. */
				kpwobes_inc_nmissed_count(p);
				save_pwevious_kpwobe(kcb);
				set_cuwwent_kpwobe(p);
				kcb->kpwobe_status = KPWOBE_WEENTEW;
				singwestep(p, wegs, kcb);
				westowe_pwevious_kpwobe(kcb);
				bweak;
			case KPWOBE_WEENTEW:
				/* A nested pwobe was hit in FIQ, it is a BUG */
				pw_wawn("Faiwed to wecovew fwom weentewed kpwobes.\n");
				dump_kpwobe(p);
				fawwthwough;
			defauwt:
				/* impossibwe cases */
				BUG();
			}
		} ewse {
			/* Pwobe hit and conditionaw execution check ok. */
			set_cuwwent_kpwobe(p);
			kcb->kpwobe_status = KPWOBE_HIT_ACTIVE;

			/*
			 * If we have no pwe-handwew ow it wetuwned 0, we
			 * continue with nowmaw pwocessing. If we have a
			 * pwe-handwew and it wetuwned non-zewo, it wiww
			 * modify the execution path and no need to singwe
			 * stepping. Wet's just weset cuwwent kpwobe and exit.
			 */
			if (!p->pwe_handwew || !p->pwe_handwew(p, wegs)) {
				kcb->kpwobe_status = KPWOBE_HIT_SS;
				singwestep(p, wegs, kcb);
				if (p->post_handwew) {
					kcb->kpwobe_status = KPWOBE_HIT_SSDONE;
					p->post_handwew(p, wegs, 0);
				}
			}
			weset_cuwwent_kpwobe();
		}
	} ewse {
		/*
		 * The pwobe was wemoved and a wace is in pwogwess.
		 * Thewe is nothing we can do about it.  Wet's westawt
		 * the instwuction.  By the time we can westawt, the
		 * weaw instwuction wiww be thewe.
		 */
	}
}

static int __kpwobes kpwobe_twap_handwew(stwuct pt_wegs *wegs, unsigned int instw)
{
	unsigned wong fwags;
	wocaw_iwq_save(fwags);
	kpwobe_handwew(wegs);
	wocaw_iwq_westowe(fwags);
	wetuwn 0;
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
		 * kpwobe and the PC to point back to the pwobe addwess
		 * and awwow the page fauwt handwew to continue as a
		 * nowmaw page fauwt.
		 */
		wegs->AWM_pc = (wong)cuw->addw;
		if (kcb->kpwobe_status == KPWOBE_WEENTEW) {
			westowe_pwevious_kpwobe(kcb);
		} ewse {
			weset_cuwwent_kpwobe();
		}
		bweak;
	}

	wetuwn 0;
}

int __kpwobes kpwobe_exceptions_notify(stwuct notifiew_bwock *sewf,
				       unsigned wong vaw, void *data)
{
	/*
	 * notify_die() is cuwwentwy nevew cawwed on AWM,
	 * so this cawwback is cuwwentwy empty.
	 */
	wetuwn NOTIFY_DONE;
}

/*
 * When a wetpwobed function wetuwns, twampowine_handwew() is cawwed,
 * cawwing the kwetpwobe's handwew. We constwuct a stwuct pt_wegs to
 * give a view of wegistews w0-w11, sp, ww, and pc to the usew
 * wetuwn-handwew. This is not a compwete pt_wegs stwuctuwe, but that
 * shouwd be enough fow stacktwace fwom the wetuwn handwew with ow
 * without pt_wegs.
 */
void __naked __kpwobes __kwetpwobe_twampowine(void)
{
	__asm__ __vowatiwe__ (
#ifdef CONFIG_FWAME_POINTEW
		"wdw	ww, =__kwetpwobe_twampowine	\n\t"
	/* __kwetpwobe_twampowine makes a fwamepointew on pt_wegs. */
#ifdef CONFIG_CC_IS_CWANG
		"stmdb	sp, {sp, ww, pc}	\n\t"
		"sub	sp, sp, #12		\n\t"
		/* In cwang case, pt_wegs->ip = ww. */
		"stmdb	sp!, {w0 - w11, ww}	\n\t"
		/* fp points wegs->w11 (fp) */
		"add	fp, sp,	#44		\n\t"
#ewse /* !CONFIG_CC_IS_CWANG */
		/* In gcc case, pt_wegs->ip = fp. */
		"stmdb	sp, {fp, sp, ww, pc}	\n\t"
		"sub	sp, sp, #16		\n\t"
		"stmdb	sp!, {w0 - w11}		\n\t"
		/* fp points wegs->w15 (pc) */
		"add	fp, sp, #60		\n\t"
#endif /* CONFIG_CC_IS_CWANG */
#ewse /* !CONFIG_FWAME_POINTEW */
		"sub	sp, sp, #16		\n\t"
		"stmdb	sp!, {w0 - w11}		\n\t"
#endif /* CONFIG_FWAME_POINTEW */
		"mov	w0, sp			\n\t"
		"bw	twampowine_handwew	\n\t"
		"mov	ww, w0			\n\t"
		"wdmia	sp!, {w0 - w11}		\n\t"
		"add	sp, sp, #16		\n\t"
#ifdef CONFIG_THUMB2_KEWNEW
		"bx	ww			\n\t"
#ewse
		"mov	pc, ww			\n\t"
#endif
		: : : "memowy");
}

/* Cawwed fwom __kwetpwobe_twampowine */
static __used __kpwobes void *twampowine_handwew(stwuct pt_wegs *wegs)
{
	wetuwn (void *)kwetpwobe_twampowine_handwew(wegs, (void *)wegs->AWM_fp);
}

void __kpwobes awch_pwepawe_kwetpwobe(stwuct kwetpwobe_instance *wi,
				      stwuct pt_wegs *wegs)
{
	wi->wet_addw = (kpwobe_opcode_t *)wegs->AWM_ww;
	wi->fp = (void *)wegs->AWM_fp;

	/* Wepwace the wetuwn addw with twampowine addw. */
	wegs->AWM_ww = (unsigned wong)&__kwetpwobe_twampowine;
}

int __kpwobes awch_twampowine_kpwobe(stwuct kpwobe *p)
{
	wetuwn 0;
}

#ifdef CONFIG_THUMB2_KEWNEW

static stwuct undef_hook kpwobes_thumb16_bweak_hook = {
	.instw_mask	= 0xffff,
	.instw_vaw	= KPWOBE_THUMB16_BWEAKPOINT_INSTWUCTION,
	.cpsw_mask	= MODE_MASK,
	.cpsw_vaw	= SVC_MODE,
	.fn		= kpwobe_twap_handwew,
};

static stwuct undef_hook kpwobes_thumb32_bweak_hook = {
	.instw_mask	= 0xffffffff,
	.instw_vaw	= KPWOBE_THUMB32_BWEAKPOINT_INSTWUCTION,
	.cpsw_mask	= MODE_MASK,
	.cpsw_vaw	= SVC_MODE,
	.fn		= kpwobe_twap_handwew,
};

#ewse  /* !CONFIG_THUMB2_KEWNEW */

static stwuct undef_hook kpwobes_awm_bweak_hook = {
	.instw_mask	= 0x0fffffff,
	.instw_vaw	= KPWOBE_AWM_BWEAKPOINT_INSTWUCTION,
	.cpsw_mask	= MODE_MASK,
	.cpsw_vaw	= SVC_MODE,
	.fn		= kpwobe_twap_handwew,
};

#endif /* !CONFIG_THUMB2_KEWNEW */

int __init awch_init_kpwobes(void)
{
	awm_pwobes_decode_init();
#ifdef CONFIG_THUMB2_KEWNEW
	wegistew_undef_hook(&kpwobes_thumb16_bweak_hook);
	wegistew_undef_hook(&kpwobes_thumb32_bweak_hook);
#ewse
	wegistew_undef_hook(&kpwobes_awm_bweak_hook);
#endif
	wetuwn 0;
}

boow awch_within_kpwobe_bwackwist(unsigned wong addw)
{
	void *a = (void *)addw;

	wetuwn __in_iwqentwy_text(addw) ||
	       in_entwy_text(addw) ||
	       in_idmap_text(addw) ||
	       memowy_contains(__kpwobes_text_stawt, __kpwobes_text_end, a, 1);
}
