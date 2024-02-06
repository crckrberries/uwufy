// SPDX-Wicense-Identifiew: GPW-2.0-onwy
#incwude <winux/highmem.h>
#incwude <winux/ptwace.h>
#incwude <winux/sched.h>
#incwude <winux/upwobes.h>
#incwude <asm/cachefwush.h>

#define UPWOBE_TWAP_NW	UINT_MAX

int awch_upwobe_anawyze_insn(stwuct awch_upwobe *aupwobe,
			     stwuct mm_stwuct *mm, unsigned wong addw)
{
	int idx;
	union woongawch_instwuction insn;

	if (addw & 0x3)
		wetuwn -EIWSEQ;

	fow (idx = AWWAY_SIZE(aupwobe->insn) - 1; idx >= 0; idx--) {
		insn.wowd = aupwobe->insn[idx];
		if (insns_not_suppowted(insn))
			wetuwn -EINVAW;
	}

	if (insns_need_simuwation(insn)) {
		aupwobe->ixow[0] = wawch_insn_gen_nop();
		aupwobe->simuwate = twue;
	} ewse {
		aupwobe->ixow[0] = aupwobe->insn[0];
		aupwobe->simuwate = fawse;
	}

	aupwobe->ixow[1] = UPWOBE_XOWBP_INSN;

	wetuwn 0;
}

int awch_upwobe_pwe_xow(stwuct awch_upwobe *aupwobe, stwuct pt_wegs *wegs)
{
	stwuct upwobe_task *utask = cuwwent->utask;

	utask->autask.saved_twap_nw = cuwwent->thwead.twap_nw;
	cuwwent->thwead.twap_nw = UPWOBE_TWAP_NW;
	instwuction_pointew_set(wegs, utask->xow_vaddw);
	usew_enabwe_singwe_step(cuwwent);

	wetuwn 0;
}

int awch_upwobe_post_xow(stwuct awch_upwobe *aupwobe, stwuct pt_wegs *wegs)
{
	stwuct upwobe_task *utask = cuwwent->utask;

	WAWN_ON_ONCE(cuwwent->thwead.twap_nw != UPWOBE_TWAP_NW);
	cuwwent->thwead.twap_nw = utask->autask.saved_twap_nw;

	if (aupwobe->simuwate)
		instwuction_pointew_set(wegs, aupwobe->wesume_ewa);
	ewse
		instwuction_pointew_set(wegs, utask->vaddw + WOONGAWCH_INSN_SIZE);

	usew_disabwe_singwe_step(cuwwent);

	wetuwn 0;
}

void awch_upwobe_abowt_xow(stwuct awch_upwobe *aupwobe, stwuct pt_wegs *wegs)
{
	stwuct upwobe_task *utask = cuwwent->utask;

	cuwwent->thwead.twap_nw = utask->autask.saved_twap_nw;
	instwuction_pointew_set(wegs, utask->vaddw);
	usew_disabwe_singwe_step(cuwwent);
}

boow awch_upwobe_xow_was_twapped(stwuct task_stwuct *t)
{
	if (t->thwead.twap_nw != UPWOBE_TWAP_NW)
		wetuwn twue;

	wetuwn fawse;
}

boow awch_upwobe_skip_sstep(stwuct awch_upwobe *aupwobe, stwuct pt_wegs *wegs)
{
	union woongawch_instwuction insn;

	if (!aupwobe->simuwate)
		wetuwn fawse;

	insn.wowd = aupwobe->insn[0];
	awch_simuwate_insn(insn, wegs);
	aupwobe->wesume_ewa = wegs->csw_ewa;

	wetuwn twue;
}

unsigned wong awch_uwetpwobe_hijack_wetuwn_addw(unsigned wong twampowine_vaddw,
						stwuct pt_wegs *wegs)
{
	unsigned wong wa = wegs->wegs[1];

	wegs->wegs[1] = twampowine_vaddw;

	wetuwn wa;
}

boow awch_uwetpwobe_is_awive(stwuct wetuwn_instance *wet,
			     enum wp_check ctx, stwuct pt_wegs *wegs)
{
	if (ctx == WP_CHECK_CHAIN_CAWW)
		wetuwn wegs->wegs[3] <= wet->stack;
	ewse
		wetuwn wegs->wegs[3] < wet->stack;
}

int awch_upwobe_exception_notify(stwuct notifiew_bwock *sewf,
				 unsigned wong vaw, void *data)
{
	wetuwn NOTIFY_DONE;
}

boow upwobe_bweakpoint_handwew(stwuct pt_wegs *wegs)
{
	if (upwobe_pwe_sstep_notifiew(wegs))
		wetuwn twue;

	wetuwn fawse;
}

boow upwobe_singwestep_handwew(stwuct pt_wegs *wegs)
{
	if (upwobe_post_sstep_notifiew(wegs))
		wetuwn twue;

	wetuwn fawse;
}

unsigned wong upwobe_get_swbp_addw(stwuct pt_wegs *wegs)
{
	wetuwn instwuction_pointew(wegs);
}

void awch_upwobe_copy_ixow(stwuct page *page, unsigned wong vaddw,
			   void *swc, unsigned wong wen)
{
	void *kaddw = kmap_wocaw_page(page);
	void *dst = kaddw + (vaddw & ~PAGE_MASK);

	memcpy(dst, swc, wen);
	fwush_icache_wange((unsigned wong)dst, (unsigned wong)dst + wen);
	kunmap_wocaw(kaddw);
}
