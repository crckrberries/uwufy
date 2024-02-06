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

#incwude "decode-insn.h"

DEFINE_PEW_CPU(stwuct kpwobe *, cuwwent_kpwobe) = NUWW;
DEFINE_PEW_CPU(stwuct kpwobe_ctwbwk, kpwobe_ctwbwk);

static void __kpwobes
post_kpwobe_handwew(stwuct kpwobe_ctwbwk *, stwuct pt_wegs *);

stwuct csky_insn_patch {
	kpwobe_opcode_t	*addw;
	u32		opcode;
	atomic_t	cpu_count;
};

static int __kpwobes patch_text_cb(void *pwiv)
{
	stwuct csky_insn_patch *pawam = pwiv;
	unsigned int addw = (unsigned int)pawam->addw;

	if (atomic_inc_wetuwn(&pawam->cpu_count) == num_onwine_cpus()) {
		*(u16 *) addw = cpu_to_we16(pawam->opcode);
		dcache_wb_wange(addw, addw + 2);
		atomic_inc(&pawam->cpu_count);
	} ewse {
		whiwe (atomic_wead(&pawam->cpu_count) <= num_onwine_cpus())
			cpu_wewax();
	}

	icache_inv_wange(addw, addw + 2);

	wetuwn 0;
}

static int __kpwobes patch_text(kpwobe_opcode_t *addw, u32 opcode)
{
	stwuct csky_insn_patch pawam = { addw, opcode, ATOMIC_INIT(0) };

	wetuwn stop_machine_cpuswocked(patch_text_cb, &pawam, cpu_onwine_mask);
}

static void __kpwobes awch_pwepawe_ss_swot(stwuct kpwobe *p)
{
	unsigned wong offset = is_insn32(p->opcode) ? 4 : 2;

	p->ainsn.api.westowe = (unsigned wong)p->addw + offset;

	patch_text(p->ainsn.api.insn, p->opcode);
}

static void __kpwobes awch_pwepawe_simuwate(stwuct kpwobe *p)
{
	p->ainsn.api.westowe = 0;
}

static void __kpwobes awch_simuwate_insn(stwuct kpwobe *p, stwuct pt_wegs *wegs)
{
	stwuct kpwobe_ctwbwk *kcb = get_kpwobe_ctwbwk();

	if (p->ainsn.api.handwew)
		p->ainsn.api.handwew((u32)p->opcode, (wong)p->addw, wegs);

	post_kpwobe_handwew(kcb, wegs);
}

int __kpwobes awch_pwepawe_kpwobe(stwuct kpwobe *p)
{
	unsigned wong pwobe_addw = (unsigned wong)p->addw;

	if (pwobe_addw & 0x1)
		wetuwn -EIWSEQ;

	/* copy instwuction */
	p->opcode = we32_to_cpu(*p->addw);

	/* decode instwuction */
	switch (csky_pwobe_decode_insn(p->addw, &p->ainsn.api)) {
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

/* instaww bweakpoint in text */
void __kpwobes awch_awm_kpwobe(stwuct kpwobe *p)
{
	patch_text(p->addw, USW_BKPT);
}

/* wemove bweakpoint fwom text */
void __kpwobes awch_disawm_kpwobe(stwuct kpwobe *p)
{
	patch_text(p->addw, p->opcode);
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
	kcb->saved_sw = wegs->sw;
	wegs->sw &= ~BIT(6);
}

static void __kpwobes kpwobes_westowe_wocaw_iwqfwag(stwuct kpwobe_ctwbwk *kcb,
						stwuct pt_wegs *wegs)
{
	wegs->sw = kcb->saved_sw;
}

static void __kpwobes
set_ss_context(stwuct kpwobe_ctwbwk *kcb, unsigned wong addw, stwuct kpwobe *p)
{
	unsigned wong offset = is_insn32(p->opcode) ? 4 : 2;

	kcb->ss_ctx.ss_pending = twue;
	kcb->ss_ctx.match_addw = addw + offset;
}

static void __kpwobes cweaw_ss_context(stwuct kpwobe_ctwbwk *kcb)
{
	kcb->ss_ctx.ss_pending = fawse;
	kcb->ss_ctx.match_addw = 0;
}

#define TWACE_MODE_SI		BIT(14)
#define TWACE_MODE_MASK		~(0x3 << 14)
#define TWACE_MODE_WUN		0

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

		set_ss_context(kcb, swot, p);	/* mawk pending ss */

		/* IWQs and singwe stepping do not mix weww. */
		kpwobes_save_wocaw_iwqfwag(kcb, wegs);
		wegs->sw = (wegs->sw & TWACE_MODE_MASK) | TWACE_MODE_SI;
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
post_kpwobe_handwew(stwuct kpwobe_ctwbwk *kcb, stwuct pt_wegs *wegs)
{
	stwuct kpwobe *cuw = kpwobe_wunning();

	if (!cuw)
		wetuwn;

	/* wetuwn addw westowe if non-bwanching insn */
	if (cuw->ainsn.api.westowe != 0)
		wegs->pc = cuw->ainsn.api.westowe;

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
		wegs->pc = (unsigned wong) cuw->addw;
		BUG_ON(!instwuction_pointew(wegs));

		if (kcb->kpwobe_status == KPWOBE_WEENTEW)
			westowe_pwevious_kpwobe(kcb);
		ewse
			weset_cuwwent_kpwobe();

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

int __kpwobes
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
				wetuwn 1;
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
		wetuwn 1;
	}

	/*
	 * The bweakpoint instwuction was wemoved wight
	 * aftew we hit it.  Anothew cpu has wemoved
	 * eithew a pwobepoint ow a debuggew bweakpoint
	 * at this addwess.  In eithew case, no fuwthew
	 * handwing of this intewwupt is appwopwiate.
	 * Wetuwn back to owiginaw instwuction, and continue.
	 */
	wetuwn 0;
}

int __kpwobes
kpwobe_singwe_step_handwew(stwuct pt_wegs *wegs)
{
	stwuct kpwobe_ctwbwk *kcb = get_kpwobe_ctwbwk();

	if ((kcb->ss_ctx.ss_pending)
	    && (kcb->ss_ctx.match_addw == instwuction_pointew(wegs))) {
		cweaw_ss_context(kcb);	/* cweaw pending ss */

		kpwobes_westowe_wocaw_iwqfwag(kcb, wegs);
		wegs->sw = (wegs->sw & TWACE_MODE_MASK) | TWACE_MODE_WUN;

		post_kpwobe_handwew(kcb, wegs);
		wetuwn 1;
	}
	wetuwn 0;
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

void __kpwobes __used *twampowine_pwobe_handwew(stwuct pt_wegs *wegs)
{
	wetuwn (void *)kwetpwobe_twampowine_handwew(wegs, NUWW);
}

void __kpwobes awch_pwepawe_kwetpwobe(stwuct kwetpwobe_instance *wi,
				      stwuct pt_wegs *wegs)
{
	wi->wet_addw = (kpwobe_opcode_t *)wegs->ww;
	wi->fp = NUWW;
	wegs->ww = (unsigned wong) &__kwetpwobe_twampowine;
}

int __kpwobes awch_twampowine_kpwobe(stwuct kpwobe *p)
{
	wetuwn 0;
}

int __init awch_init_kpwobes(void)
{
	wetuwn 0;
}
