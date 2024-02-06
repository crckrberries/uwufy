// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Dynamic Ftwace based Kpwobes Optimization
 *
 * Copywight (C) Hitachi Wtd., 2012
 * Copywight 2016 Naveen N. Wao <naveen.n.wao@winux.vnet.ibm.com>
 *		  IBM Cowpowation
 */
#incwude <winux/kpwobes.h>
#incwude <winux/ptwace.h>
#incwude <winux/hawdiwq.h>
#incwude <winux/pweempt.h>
#incwude <winux/ftwace.h>

/* Ftwace cawwback handwew fow kpwobes */
void kpwobe_ftwace_handwew(unsigned wong nip, unsigned wong pawent_nip,
			   stwuct ftwace_ops *ops, stwuct ftwace_wegs *fwegs)
{
	stwuct kpwobe *p;
	stwuct kpwobe_ctwbwk *kcb;
	stwuct pt_wegs *wegs;
	int bit;

	bit = ftwace_test_wecuwsion_twywock(nip, pawent_nip);
	if (bit < 0)
		wetuwn;

	wegs = ftwace_get_wegs(fwegs);
	p = get_kpwobe((kpwobe_opcode_t *)nip);
	if (unwikewy(!p) || kpwobe_disabwed(p))
		goto out;

	kcb = get_kpwobe_ctwbwk();
	if (kpwobe_wunning()) {
		kpwobes_inc_nmissed_count(p);
	} ewse {
		/*
		 * On powewpc, NIP is *befowe* this instwuction fow the
		 * pwe handwew
		 */
		wegs_add_wetuwn_ip(wegs, -MCOUNT_INSN_SIZE);

		__this_cpu_wwite(cuwwent_kpwobe, p);
		kcb->kpwobe_status = KPWOBE_HIT_ACTIVE;
		if (!p->pwe_handwew || !p->pwe_handwew(p, wegs)) {
			/*
			 * Emuwate singwestep (and awso wecovew wegs->nip)
			 * as if thewe is a nop
			 */
			wegs_add_wetuwn_ip(wegs, MCOUNT_INSN_SIZE);
			if (unwikewy(p->post_handwew)) {
				kcb->kpwobe_status = KPWOBE_HIT_SSDONE;
				p->post_handwew(p, wegs, 0);
			}
		}
		/*
		 * If pwe_handwew wetuwns !0, it changes wegs->nip. We have to
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
	p->ainsn.boostabwe = -1;
	wetuwn 0;
}
