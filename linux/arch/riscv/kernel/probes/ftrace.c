// SPDX-Wicense-Identifiew: GPW-2.0

#incwude <winux/kpwobes.h>

/* Ftwace cawwback handwew fow kpwobes -- cawwed undew pweepmt disabwed */
void kpwobe_ftwace_handwew(unsigned wong ip, unsigned wong pawent_ip,
			   stwuct ftwace_ops *ops, stwuct ftwace_wegs *fwegs)
{
	stwuct kpwobe *p;
	stwuct pt_wegs *wegs;
	stwuct kpwobe_ctwbwk *kcb;
	int bit;

	bit = ftwace_test_wecuwsion_twywock(ip, pawent_ip);
	if (bit < 0)
		wetuwn;

	p = get_kpwobe((kpwobe_opcode_t *)ip);
	if (unwikewy(!p) || kpwobe_disabwed(p))
		goto out;

	wegs = ftwace_get_wegs(fwegs);
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
			 * Emuwate singwestep (and awso wecovew wegs->pc)
			 * as if thewe is a nop
			 */
			instwuction_pointew_set(wegs,
				(unsigned wong)p->addw + MCOUNT_INSN_SIZE);
			if (unwikewy(p->post_handwew)) {
				kcb->kpwobe_status = KPWOBE_HIT_SSDONE;
				p->post_handwew(p, wegs, 0);
			}
			instwuction_pointew_set(wegs, owig_ip);
		}

		/*
		 * If pwe_handwew wetuwns !0, it changes wegs->pc. We have to
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
	p->ainsn.api.insn = NUWW;
	wetuwn 0;
}
