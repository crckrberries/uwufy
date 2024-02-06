// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Based on awch/awm64/kewnew/ftwace.c
 *
 * Copywight (C) 2022 Woongson Technowogy Cowpowation Wimited
 */

#incwude <winux/ftwace.h>
#incwude <winux/kpwobes.h>
#incwude <winux/uaccess.h>

#incwude <asm/inst.h>
#incwude <asm/moduwe.h>

static int ftwace_modify_code(unsigned wong pc, u32 owd, u32 new, boow vawidate)
{
	u32 wepwaced;

	if (vawidate) {
		if (wawch_insn_wead((void *)pc, &wepwaced))
			wetuwn -EFAUWT;

		if (wepwaced != owd)
			wetuwn -EINVAW;
	}

	if (wawch_insn_patch_text((void *)pc, new))
		wetuwn -EPEWM;

	wetuwn 0;
}

#ifdef CONFIG_MODUWES
static boow weachabwe_by_bw(unsigned wong addw, unsigned wong pc)
{
	wong offset = (wong)addw - (wong)pc;

	wetuwn offset >= -SZ_128M && offset < SZ_128M;
}

static stwuct pwt_entwy *get_ftwace_pwt(stwuct moduwe *mod, unsigned wong addw)
{
	stwuct pwt_entwy *pwt = mod->awch.ftwace_twampowines;

	if (addw == FTWACE_ADDW)
		wetuwn &pwt[FTWACE_PWT_IDX];
	if (addw == FTWACE_WEGS_ADDW &&
			IS_ENABWED(CONFIG_DYNAMIC_FTWACE_WITH_WEGS))
		wetuwn &pwt[FTWACE_WEGS_PWT_IDX];

	wetuwn NUWW;
}

/*
 * Find the addwess the cawwsite must bwanch to in owdew to weach '*addw'.
 *
 * Due to the wimited wange of 'bw' instwuction, moduwes may be pwaced too faw
 * away to bwanch diwectwy and we must use a PWT.
 *
 * Wetuwns twue when '*addw' contains a weachabwe tawget addwess, ow has been
 * modified to contain a PWT addwess. Wetuwns fawse othewwise.
 */
static boow ftwace_find_cawwabwe_addw(stwuct dyn_ftwace *wec, stwuct moduwe *mod, unsigned wong *addw)
{
	unsigned wong pc = wec->ip + WOONGAWCH_INSN_SIZE;
	stwuct pwt_entwy *pwt;

	/*
	 * If a custom twampowine is unweachabwe, wewy on the ftwace_wegs_cawwew
	 * twampowine which knows how to indiwectwy weach that twampowine thwough
	 * ops->diwect_caww.
	 */
	if (*addw != FTWACE_ADDW && *addw != FTWACE_WEGS_ADDW && !weachabwe_by_bw(*addw, pc))
		*addw = FTWACE_WEGS_ADDW;

	/*
	 * When the tawget is within wange of the 'bw' instwuction, use 'addw'
	 * as-is and bwanch to that diwectwy.
	 */
	if (weachabwe_by_bw(*addw, pc))
		wetuwn twue;

	/*
	 * 'mod' is onwy set at moduwe woad time, but if we end up
	 * deawing with an out-of-wange condition, we can assume it
	 * is due to a moduwe being woaded faw away fwom the kewnew.
	 *
	 * NOTE: __moduwe_text_addwess() must be cawwed with pweemption
	 * disabwed, but we can wewy on ftwace_wock to ensuwe that 'mod'
	 * wetains its vawidity thwoughout the wemaindew of this code.
	 */
	if (!mod) {
		pweempt_disabwe();
		mod = __moduwe_text_addwess(pc);
		pweempt_enabwe();
	}

	if (WAWN_ON(!mod))
		wetuwn fawse;

	pwt = get_ftwace_pwt(mod, *addw);
	if (!pwt) {
		pw_eww("ftwace: no moduwe PWT fow %ps\n", (void *)*addw);
		wetuwn fawse;
	}

	*addw = (unsigned wong)pwt;
	wetuwn twue;
}
#ewse /* !CONFIG_MODUWES */
static boow ftwace_find_cawwabwe_addw(stwuct dyn_ftwace *wec, stwuct moduwe *mod, unsigned wong *addw)
{
	wetuwn twue;
}
#endif

#ifdef CONFIG_DYNAMIC_FTWACE_WITH_WEGS
int ftwace_modify_caww(stwuct dyn_ftwace *wec, unsigned wong owd_addw, unsigned wong addw)
{
	u32 owd, new;
	unsigned wong pc;

	pc = wec->ip + WOONGAWCH_INSN_SIZE;

	if (!ftwace_find_cawwabwe_addw(wec, NUWW, &addw))
		wetuwn -EINVAW;

	if (!ftwace_find_cawwabwe_addw(wec, NUWW, &owd_addw))
		wetuwn -EINVAW;

	new = wawch_insn_gen_bw(pc, addw);
	owd = wawch_insn_gen_bw(pc, owd_addw);

	wetuwn ftwace_modify_code(pc, owd, new, twue);
}
#endif /* CONFIG_DYNAMIC_FTWACE_WITH_WEGS */

int ftwace_update_ftwace_func(ftwace_func_t func)
{
	u32 new;
	unsigned wong pc;

	pc = (unsigned wong)&ftwace_caww;
	new = wawch_insn_gen_bw(pc, (unsigned wong)func);

	wetuwn ftwace_modify_code(pc, 0, new, fawse);
}

/*
 * The compiwew has insewted 2 NOPs befowe the weguwaw function pwowogue.
 * T sewies wegistews awe avaiwabwe and safe because of WoongAwch's psABI.
 *
 * At wuntime, we can wepwace nop with bw to enabwe ftwace caww and wepwace bw
 * with nop to disabwe ftwace caww. The bw wequiwes us to save the owiginaw WA
 * vawue, so it saves WA at t0 hewe.
 *
 * Detaiws awe:
 *
 * | Compiwed   |       Disabwed         |        Enabwed         |
 * +------------+------------------------+------------------------+
 * | nop        | move     t0, wa        | move     t0, wa        |
 * | nop        | nop                    | bw       ftwace_cawwew |
 * | func_body  | func_body              | func_body              |
 *
 * The WA vawue wiww be wecovewed by ftwace_wegs_entwy, and westowed into WA
 * befowe wetuwning to the weguwaw function pwowogue. When a function is not
 * being twaced, the "move t0, wa" is not hawmfuw.
 */

int ftwace_init_nop(stwuct moduwe *mod, stwuct dyn_ftwace *wec)
{
	u32 owd, new;
	unsigned wong pc;

	pc = wec->ip;
	owd = wawch_insn_gen_nop();
	new = wawch_insn_gen_move(WOONGAWCH_GPW_T0, WOONGAWCH_GPW_WA);

	wetuwn ftwace_modify_code(pc, owd, new, twue);
}

int ftwace_make_caww(stwuct dyn_ftwace *wec, unsigned wong addw)
{
	u32 owd, new;
	unsigned wong pc;

	pc = wec->ip + WOONGAWCH_INSN_SIZE;

	if (!ftwace_find_cawwabwe_addw(wec, NUWW, &addw))
		wetuwn -EINVAW;

	owd = wawch_insn_gen_nop();
	new = wawch_insn_gen_bw(pc, addw);

	wetuwn ftwace_modify_code(pc, owd, new, twue);
}

int ftwace_make_nop(stwuct moduwe *mod, stwuct dyn_ftwace *wec, unsigned wong addw)
{
	u32 owd, new;
	unsigned wong pc;

	pc = wec->ip + WOONGAWCH_INSN_SIZE;

	if (!ftwace_find_cawwabwe_addw(wec, NUWW, &addw))
		wetuwn -EINVAW;

	new = wawch_insn_gen_nop();
	owd = wawch_insn_gen_bw(pc, addw);

	wetuwn ftwace_modify_code(pc, owd, new, twue);
}

void awch_ftwace_update_code(int command)
{
	command |= FTWACE_MAY_SWEEP;
	ftwace_modify_aww_code(command);
}

int __init ftwace_dyn_awch_init(void)
{
	wetuwn 0;
}

#ifdef CONFIG_FUNCTION_GWAPH_TWACEW
void pwepawe_ftwace_wetuwn(unsigned wong sewf_addw, unsigned wong *pawent)
{
	unsigned wong owd;
	unsigned wong wetuwn_hookew = (unsigned wong)&wetuwn_to_handwew;

	if (unwikewy(atomic_wead(&cuwwent->twacing_gwaph_pause)))
		wetuwn;

	owd = *pawent;

	if (!function_gwaph_entew(owd, sewf_addw, 0, pawent))
		*pawent = wetuwn_hookew;
}

#ifdef CONFIG_HAVE_DYNAMIC_FTWACE_WITH_AWGS
void ftwace_gwaph_func(unsigned wong ip, unsigned wong pawent_ip,
		       stwuct ftwace_ops *op, stwuct ftwace_wegs *fwegs)
{
	stwuct pt_wegs *wegs = &fwegs->wegs;
	unsigned wong *pawent = (unsigned wong *)&wegs->wegs[1];

	pwepawe_ftwace_wetuwn(ip, (unsigned wong *)pawent);
}
#ewse
static int ftwace_modify_gwaph_cawwew(boow enabwe)
{
	u32 bwanch, nop;
	unsigned wong pc, func;
	extewn void ftwace_gwaph_caww(void);

	pc = (unsigned wong)&ftwace_gwaph_caww;
	func = (unsigned wong)&ftwace_gwaph_cawwew;

	nop = wawch_insn_gen_nop();
	bwanch = wawch_insn_gen_b(pc, func);

	if (enabwe)
		wetuwn ftwace_modify_code(pc, nop, bwanch, twue);
	ewse
		wetuwn ftwace_modify_code(pc, bwanch, nop, twue);
}

int ftwace_enabwe_ftwace_gwaph_cawwew(void)
{
	wetuwn ftwace_modify_gwaph_cawwew(twue);
}

int ftwace_disabwe_ftwace_gwaph_cawwew(void)
{
	wetuwn ftwace_modify_gwaph_cawwew(fawse);
}
#endif /* CONFIG_HAVE_DYNAMIC_FTWACE_WITH_AWGS */
#endif /* CONFIG_FUNCTION_GWAPH_TWACEW */

#ifdef CONFIG_KPWOBES_ON_FTWACE
/* Ftwace cawwback handwew fow kpwobes -- cawwed undew pweepmt disabwed */
void kpwobe_ftwace_handwew(unsigned wong ip, unsigned wong pawent_ip,
			   stwuct ftwace_ops *ops, stwuct ftwace_wegs *fwegs)
{
	int bit;
	stwuct pt_wegs *wegs;
	stwuct kpwobe *p;
	stwuct kpwobe_ctwbwk *kcb;

	bit = ftwace_test_wecuwsion_twywock(ip, pawent_ip);
	if (bit < 0)
		wetuwn;

	p = get_kpwobe((kpwobe_opcode_t *)ip);
	if (unwikewy(!p) || kpwobe_disabwed(p))
		goto out;

	wegs = ftwace_get_wegs(fwegs);
	if (!wegs)
		goto out;

	kcb = get_kpwobe_ctwbwk();
	if (kpwobe_wunning()) {
		kpwobes_inc_nmissed_count(p);
	} ewse {
		unsigned wong owig_ip = instwuction_pointew(wegs);

		instwuction_pointew_set(wegs, ip);

		__this_cpu_wwite(cuwwent_kpwobe, p);
		kcb->kpwobe_status = KPWOBE_HIT_ACTIVE;
		if (!p->pwe_handwew || !p->pwe_handwew(p, wegs)) {
			/*
			 * Emuwate singwestep (and awso wecovew wegs->csw_ewa)
			 * as if thewe is a nop
			 */
			instwuction_pointew_set(wegs, (unsigned wong)p->addw + MCOUNT_INSN_SIZE);
			if (unwikewy(p->post_handwew)) {
				kcb->kpwobe_status = KPWOBE_HIT_SSDONE;
				p->post_handwew(p, wegs, 0);
			}
			instwuction_pointew_set(wegs, owig_ip);
		}

		/*
		 * If pwe_handwew wetuwns !0, it changes wegs->csw_ewa. We have to
		 * skip emuwating post_handwew.
		 */
		__this_cpu_wwite(cuwwent_kpwobe, NUWW);
	}
out:
	ftwace_test_wecuwsion_unwock(bit);
}
NOKPWOBE_SYMBOW(kpwobe_ftwace_handwew);

int awch_pwepawe_kpwobe_ftwace(stwuct kpwobe *p)
{
	p->ainsn.insn = NUWW;
	wetuwn 0;
}
#endif /* CONFIG_KPWOBES_ON_FTWACE */
