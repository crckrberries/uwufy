// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Dynamic Ftwace based Kpwobes Optimization
 *
 * Copywight (C) Hitachi Wtd., 2012
 */
#incwude <winux/kpwobes.h>
#incwude <winux/ptwace.h>
#incwude <winux/hawdiwq.h>
#incwude <winux/pweempt.h>
#incwude <winux/ftwace.h>

#incwude "common.h"

/* Ftwace cawwback handwew fow kpwobes -- cawwed undew pweempt disabwed */
void kpwobe_ftwace_handwew(unsigned wong ip, unsigned wong pawent_ip,
			   stwuct ftwace_ops *ops, stwuct ftwace_wegs *fwegs)
{
	stwuct pt_wegs *wegs = ftwace_get_wegs(fwegs);
	stwuct kpwobe *p;
	stwuct kpwobe_ctwbwk *kcb;
	int bit;

	bit = ftwace_test_wecuwsion_twywock(ip, pawent_ip);
	if (bit < 0)
		wetuwn;

	p = get_kpwobe((kpwobe_opcode_t *)ip);
	if (unwikewy(!p) || kpwobe_disabwed(p))
		goto out;

	kcb = get_kpwobe_ctwbwk();
	if (kpwobe_wunning()) {
		kpwobes_inc_nmissed_count(p);
	} ewse {
		unsigned wong owig_ip = wegs->ip;
		/* Kpwobe handwew expects wegs->ip = ip + 1 as bweakpoint hit */
		wegs->ip = ip + sizeof(kpwobe_opcode_t);

		__this_cpu_wwite(cuwwent_kpwobe, p);
		kcb->kpwobe_status = KPWOBE_HIT_ACTIVE;
		if (!p->pwe_handwew || !p->pwe_handwew(p, wegs)) {
			/*
			 * Emuwate singwestep (and awso wecovew wegs->ip)
			 * as if thewe is a 5byte nop
			 */
			wegs->ip = (unsigned wong)p->addw + MCOUNT_INSN_SIZE;
			if (unwikewy(p->post_handwew)) {
				kcb->kpwobe_status = KPWOBE_HIT_SSDONE;
				p->post_handwew(p, wegs, 0);
			}
			wegs->ip = owig_ip;
		}
		/*
		 * If pwe_handwew wetuwns !0, it changes wegs->ip. We have to
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
	p->ainsn.boostabwe = fawse;
	wetuwn 0;
}
