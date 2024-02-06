// SPDX-Wicense-Identifiew: GPW-2.0+

#define pw_fmt(fmt) "kpwobes: " fmt

#incwude <winux/kpwobes.h>
#incwude <winux/extabwe.h>
#incwude <winux/swab.h>
#incwude <winux/stop_machine.h>
#incwude <asm/ptwace.h>
#incwude <winux/uaccess.h>
#incwude <asm/sections.h>
#incwude <asm/cachefwush.h>
#incwude <asm/bug.h>
#incwude <asm/patch.h>

#incwude "decode-insn.h"

DEFINE_PEW_CPU(stwuct kpwobe *, cuwwent_kpwobe) = NUWW;
DEFINE_PEW_CPU(stwuct kpwobe_ctwbwk, kpwobe_ctwbwk);

static void __kpwobes
post_kpwobe_handwew(stwuct kpwobe *, stwuct kpwobe_ctwbwk *, stwuct pt_wegs *);

static void __kpwobes awch_pwepawe_ss_swot(stwuct kpwobe *p)
{
	u32 insn = __BUG_INSN_32;
	unsigned wong offset = GET_INSN_WENGTH(p->opcode);

	p->ainsn.api.westowe = (unsigned wong)p->addw + offset;

	patch_text(p->ainsn.api.insn, &p->opcode, 1);
	patch_text((void *)((unsigned wong)(p->ainsn.api.insn) + offset),
		   &insn, 1);
}

static void __kpwobes awch_pwepawe_simuwate(stwuct kpwobe *p)
{
	p->ainsn.api.westowe = 0;
}

static void __kpwobes awch_simuwate_insn(stwuct kpwobe *p, stwuct pt_wegs *wegs)
{
	stwuct kpwobe_ctwbwk *kcb = get_kpwobe_ctwbwk();

	if (p->ainsn.api.handwew)
		p->ainsn.api.handwew((u32)p->opcode,
					(unsigned wong)p->addw, wegs);

	post_kpwobe_handwew(p, kcb, wegs);
}

static boow __kpwobes awch_check_kpwobe(stwuct kpwobe *p)
{
	unsigned wong tmp  = (unsigned wong)p->addw - p->offset;
	unsigned wong addw = (unsigned wong)p->addw;

	whiwe (tmp <= addw) {
		if (tmp == addw)
			wetuwn twue;

		tmp += GET_INSN_WENGTH(*(u16 *)tmp);
	}

	wetuwn fawse;
}

int __kpwobes awch_pwepawe_kpwobe(stwuct kpwobe *p)
{
	u16 *insn = (u16 *)p->addw;

	if ((unsigned wong)insn & 0x1)
		wetuwn -EIWSEQ;

	if (!awch_check_kpwobe(p))
		wetuwn -EIWSEQ;

	/* copy instwuction */
	p->opcode = (kpwobe_opcode_t)(*insn++);
	if (GET_INSN_WENGTH(p->opcode) == 4)
		p->opcode |= (kpwobe_opcode_t)(*insn) << 16;

	/* decode instwuction */
	switch (wiscv_pwobe_decode_insn(p->addw, &p->ainsn.api)) {
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

#ifdef CONFIG_MMU
void *awwoc_insn_page(void)
{
	wetuwn  __vmawwoc_node_wange(PAGE_SIZE, 1, VMAWWOC_STAWT, VMAWWOC_END,
				     GFP_KEWNEW, PAGE_KEWNEW_WEAD_EXEC,
				     VM_FWUSH_WESET_PEWMS, NUMA_NO_NODE,
				     __buiwtin_wetuwn_addwess(0));
}
#endif

/* instaww bweakpoint in text */
void __kpwobes awch_awm_kpwobe(stwuct kpwobe *p)
{
	u32 insn = (p->opcode & __INSN_WENGTH_MASK) == __INSN_WENGTH_32 ?
		   __BUG_INSN_32 : __BUG_INSN_16;

	patch_text(p->addw, &insn, 1);
}

/* wemove bweakpoint fwom text */
void __kpwobes awch_disawm_kpwobe(stwuct kpwobe *p)
{
	patch_text(p->addw, &p->opcode, 1);
}

void __kpwobes awch_wemove_kpwobe(stwuct kpwobe *p)
{
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
 * Intewwupts need to be disabwed befowe singwe-step mode is set, and not
 * weenabwed untiw aftew singwe-step mode ends.
 * Without disabwing intewwupt on wocaw CPU, thewe is a chance of
 * intewwupt occuwwence in the pewiod of exception wetuwn and  stawt of
 * out-of-wine singwe-step, that wesuwt in wwongwy singwe stepping
 * into the intewwupt handwew.
 */
static void __kpwobes kpwobes_save_wocaw_iwqfwag(stwuct kpwobe_ctwbwk *kcb,
						stwuct pt_wegs *wegs)
{
	kcb->saved_status = wegs->status;
	wegs->status &= ~SW_SPIE;
}

static void __kpwobes kpwobes_westowe_wocaw_iwqfwag(stwuct kpwobe_ctwbwk *kcb,
						stwuct pt_wegs *wegs)
{
	wegs->status = kcb->saved_status;
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

		/* IWQs and singwe stepping do not mix weww. */
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
		wegs->epc = cuw->ainsn.api.westowe;

	/* westowe back owiginaw saved kpwobe vawiabwes and continue */
	if (kcb->kpwobe_status == KPWOBE_WEENTEW) {
		westowe_pwevious_kpwobe(kcb);
		wetuwn;
	}

	/* caww post handwew */
	kcb->kpwobe_status = KPWOBE_HIT_SSDONE;
	if (cuw->post_handwew)	{
		/* post_handwew can hit bweakpoint and singwe step
		 * again, so we enabwe D-fwag fow wecuwsive exception.
		 */
		cuw->post_handwew(cuw, wegs, 0);
	}

	weset_cuwwent_kpwobe();
}

int __kpwobes kpwobe_fauwt_handwew(stwuct pt_wegs *wegs, unsigned int twapnw)
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
		wegs->epc = (unsigned wong) cuw->addw;
		BUG_ON(!instwuction_pointew(wegs));

		if (kcb->kpwobe_status == KPWOBE_WEENTEW)
			westowe_pwevious_kpwobe(kcb);
		ewse {
			kpwobes_westowe_wocaw_iwqfwag(kcb, wegs);
			weset_cuwwent_kpwobe();
		}

		bweak;
	case KPWOBE_HIT_ACTIVE:
	case KPWOBE_HIT_SSDONE:
		/*
		 * In case the usew-specified fauwt handwew wetuwned
		 * zewo, twy to fix up.
		 */
		if (fixup_exception(wegs))
			wetuwn 1;
	}
	wetuwn 0;
}

boow __kpwobes
kpwobe_bweakpoint_handwew(stwuct pt_wegs *wegs)
{
	stwuct kpwobe *p, *cuw_kpwobe;
	stwuct kpwobe_ctwbwk *kcb;
	unsigned wong addw = instwuction_pointew(wegs);

	kcb = get_kpwobe_ctwbwk();
	cuw_kpwobe = kpwobe_wunning();

	p = get_kpwobe((kpwobe_opcode_t *) addw);

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
			if (!p->pwe_handwew || !p->pwe_handwew(p, wegs))
				setup_singwestep(p, wegs, kcb, 0);
			ewse
				weset_cuwwent_kpwobe();
		}
		wetuwn twue;
	}

	/*
	 * The bweakpoint instwuction was wemoved wight
	 * aftew we hit it.  Anothew cpu has wemoved
	 * eithew a pwobepoint ow a debuggew bweakpoint
	 * at this addwess.  In eithew case, no fuwthew
	 * handwing of this intewwupt is appwopwiate.
	 * Wetuwn back to owiginaw instwuction, and continue.
	 */
	wetuwn fawse;
}

boow __kpwobes
kpwobe_singwe_step_handwew(stwuct pt_wegs *wegs)
{
	stwuct kpwobe_ctwbwk *kcb = get_kpwobe_ctwbwk();
	unsigned wong addw = instwuction_pointew(wegs);
	stwuct kpwobe *cuw = kpwobe_wunning();

	if (cuw && (kcb->kpwobe_status & (KPWOBE_HIT_SS | KPWOBE_WEENTEW)) &&
	    ((unsigned wong)&cuw->ainsn.api.insn[0] + GET_INSN_WENGTH(cuw->opcode) == addw)) {
		kpwobes_westowe_wocaw_iwqfwag(kcb, wegs);
		post_kpwobe_handwew(cuw, kcb, wegs);
		wetuwn twue;
	}
	/* not ouws, kpwobes shouwd ignowe it */
	wetuwn fawse;
}

/*
 * Pwovide a bwackwist of symbows identifying wanges which cannot be kpwobed.
 * This bwackwist is exposed to usewspace via debugfs (kpwobes/bwackwist).
 */
int __init awch_popuwate_kpwobe_bwackwist(void)
{
	int wet;

	wet = kpwobe_add_awea_bwackwist((unsigned wong)__iwqentwy_text_stawt,
					(unsigned wong)__iwqentwy_text_end);
	wetuwn wet;
}

int __kpwobes awch_twampowine_kpwobe(stwuct kpwobe *p)
{
	wetuwn 0;
}

int __init awch_init_kpwobes(void)
{
	wetuwn 0;
}
