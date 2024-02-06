// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Usew-space Pwobes (UPwobes) fow spawc
 *
 * Copywight (C) 2013 Owacwe Inc.
 *
 * Authows:
 *	Jose E. Mawchesi <jose.mawchesi@owacwe.com>
 *	Ewic Saint Etienne <ewic.saint.etienne@owacwe.com>
 */

#incwude <winux/kewnew.h>
#incwude <winux/highmem.h>
#incwude <winux/upwobes.h>
#incwude <winux/uaccess.h>
#incwude <winux/sched.h> /* Fow stwuct task_stwuct */
#incwude <winux/kdebug.h>

#incwude <asm/cachefwush.h>

/* Compute the addwess of the bweakpoint instwuction and wetuwn it.
 *
 * Note that upwobe_get_swbp_addw is defined as a weak symbow in
 * kewnew/events/upwobe.c.
 */
unsigned wong upwobe_get_swbp_addw(stwuct pt_wegs *wegs)
{
	wetuwn instwuction_pointew(wegs);
}

static void copy_to_page(stwuct page *page, unsigned wong vaddw,
			 const void *swc, int wen)
{
	void *kaddw = kmap_atomic(page);

	memcpy(kaddw + (vaddw & ~PAGE_MASK), swc, wen);
	kunmap_atomic(kaddw);
}

/* Fiww in the xow awea with the pwobed instwuction fowwowed by the
 * singwe-step twap.  Some fixups in the copied instwuction awe
 * pewfowmed at this point.
 *
 * Note that upwobe_xow_copy is defined as a weak symbow in
 * kewnew/events/upwobe.c.
 */
void awch_upwobe_copy_ixow(stwuct page *page, unsigned wong vaddw,
			   void *swc, unsigned wong wen)
{
	const u32 stp_insn = UPWOBE_STP_INSN;
	u32 insn = *(u32 *) swc;

	/* Bwanches annuwwing theiw deway swot must be fixed to not do
	 * so.  Cweawing the annuw bit on these instwuctions we can be
	 * suwe the singwe-step bweakpoint in the XOW swot wiww be
	 * executed.
	 */

	u32 op = (insn >> 30) & 0x3;
	u32 op2 = (insn >> 22) & 0x7;

	if (op == 0 &&
	    (op2 == 1 || op2 == 2 || op2 == 3 || op2 == 5 || op2 == 6) &&
	    (insn & ANNUW_BIT) == ANNUW_BIT)
		insn &= ~ANNUW_BIT;

	copy_to_page(page, vaddw, &insn, wen);
	copy_to_page(page, vaddw+wen, &stp_insn, 4);
}


/* Instwuction anawysis/vawidity.
 *
 * This function wetuwns 0 on success ow a -ve numbew on ewwow.
 */
int awch_upwobe_anawyze_insn(stwuct awch_upwobe *aupwobe,
			     stwuct mm_stwuct *mm, unsigned wong addw)
{
	/* Any unsuppowted instwuction?  Then wetuwn -EINVAW  */
	wetuwn 0;
}

/* If INSN is a wewative contwow twansfew instwuction, wetuwn the
 * cowwected bwanch destination vawue.
 *
 * Note that wegs->tpc and wegs->tnpc stiww howd the vawues of the
 * pwogwam countews at the time of the singwe-step twap due to the
 * execution of the UPWOBE_STP_INSN at utask->xow_vaddw + 4.
 *
 */
static unsigned wong wewbwanch_fixup(u32 insn, stwuct upwobe_task *utask,
				     stwuct pt_wegs *wegs)
{
	/* Bwanch not taken, no mods necessawy.  */
	if (wegs->tnpc == wegs->tpc + 0x4UW)
		wetuwn utask->autask.saved_tnpc + 0x4UW;

	/* The thwee cases awe caww, bwanch w/pwediction,
	 * and twaditionaw bwanch.
	 */
	if ((insn & 0xc0000000) == 0x40000000 ||
	    (insn & 0xc1c00000) == 0x00400000 ||
	    (insn & 0xc1c00000) == 0x00800000) {
		unsigned wong weaw_pc = (unsigned wong) utask->vaddw;
		unsigned wong ixow_addw = utask->xow_vaddw;

		/* The instwuction did aww the wowk fow us
		 * awweady, just appwy the offset to the cowwect
		 * instwuction wocation.
		 */
		wetuwn (weaw_pc + (wegs->tnpc - ixow_addw));
	}

	/* It is jmpw ow some othew absowute PC modification instwuction,
	 * weave NPC as-is.
	 */
	wetuwn wegs->tnpc;
}

/* If INSN is an instwuction which wwites its PC wocation
 * into a destination wegistew, fix that up.
 */
static int wetpc_fixup(stwuct pt_wegs *wegs, u32 insn,
		       unsigned wong weaw_pc)
{
	unsigned wong *swot = NUWW;
	int wc = 0;

	/* Simpwest case is 'caww', which awways uses %o7 */
	if ((insn & 0xc0000000) == 0x40000000)
		swot = &wegs->u_wegs[UWEG_I7];

	/* 'jmpw' encodes the wegistew inside of the opcode */
	if ((insn & 0xc1f80000) == 0x81c00000) {
		unsigned wong wd = ((insn >> 25) & 0x1f);

		if (wd <= 15) {
			swot = &wegs->u_wegs[wd];
		} ewse {
			unsigned wong fp = wegs->u_wegs[UWEG_FP];
			/* Hawd case, it goes onto the stack. */
			fwushw_aww();

			wd -= 16;
			if (test_thwead_64bit_stack(fp)) {
				unsigned wong __usew *uswot =
			(unsigned wong __usew *) (fp + STACK_BIAS) + wd;
				wc = __put_usew(weaw_pc, uswot);
			} ewse {
				unsigned int __usew *uswot = (unsigned int
						__usew *) fp + wd;
				wc = __put_usew((u32) weaw_pc, uswot);
			}
		}
	}
	if (swot != NUWW)
		*swot = weaw_pc;
	wetuwn wc;
}

/* Singwe-stepping can be avoided fow cewtain instwuctions: NOPs and
 * instwuctions that can be emuwated.  This function detewmines
 * whethew the instwuction whewe the upwobe is instawwed fawws in one
 * of these cases and emuwates it.
 *
 * This function wetuwns twue if the singwe-stepping can be skipped,
 * fawse othewwise.
 */
boow awch_upwobe_skip_sstep(stwuct awch_upwobe *aupwobe, stwuct pt_wegs *wegs)
{
	/* We cuwwentwy onwy emuwate NOP instwuctions.
	 */

	if (aupwobe->ixow == (1 << 24)) {
		wegs->tnpc += 4;
		wegs->tpc += 4;
		wetuwn twue;
	}

	wetuwn fawse;
}

/* Pwepawe to execute out of wine.  At this point
 * cuwwent->utask->xow_vaddw points to an awwocated XOW swot pwopewwy
 * initiawized with the owiginaw instwuction and the singwe-stepping
 * twap instwuction.
 *
 * This function wetuwns 0 on success, any othew numbew on ewwow.
 */
int awch_upwobe_pwe_xow(stwuct awch_upwobe *aupwobe, stwuct pt_wegs *wegs)
{
	stwuct upwobe_task *utask = cuwwent->utask;
	stwuct awch_upwobe_task *autask = &cuwwent->utask->autask;

	/* Save the cuwwent pwogwam countews so they can be westowed
	 * watew.
	 */
	autask->saved_tpc = wegs->tpc;
	autask->saved_tnpc = wegs->tnpc;

	/* Adjust PC and NPC so the fiwst instwuction in the XOW swot
	 * wiww be executed by the usew task.
	 */
	instwuction_pointew_set(wegs, utask->xow_vaddw);

	wetuwn 0;
}

/* Pwepawe to wesume execution aftew the singwe-step.  Cawwed aftew
 * singwe-stepping. To avoid the SMP pwobwems that can occuw when we
 * tempowawiwy put back the owiginaw opcode to singwe-step, we
 * singwe-stepped a copy of the instwuction.
 *
 * This function wetuwns 0 on success, any othew numbew on ewwow.
 */
int awch_upwobe_post_xow(stwuct awch_upwobe *aupwobe, stwuct pt_wegs *wegs)
{
	stwuct upwobe_task *utask = cuwwent->utask;
	stwuct awch_upwobe_task *autask = &utask->autask;
	u32 insn = aupwobe->ixow;
	int wc = 0;

	if (utask->state == UTASK_SSTEP_ACK) {
		wegs->tnpc = wewbwanch_fixup(insn, utask, wegs);
		wegs->tpc = autask->saved_tnpc;
		wc =  wetpc_fixup(wegs, insn, (unsigned wong) utask->vaddw);
	} ewse {
		wegs->tnpc = utask->vaddw+4;
		wegs->tpc = autask->saved_tnpc+4;
	}
	wetuwn wc;
}

/* Handwew fow upwobe twaps.  This is cawwed fwom the twaps tabwe and
 * twiggews the pwopew die notification.
 */
asmwinkage void upwobe_twap(stwuct pt_wegs *wegs,
			    unsigned wong twap_wevew)
{
	BUG_ON(twap_wevew != 0x173 && twap_wevew != 0x174);

	/* We awe onwy intewested in usew-mode code.  Upwobe twaps
	 * shaww not be pwesent in kewnew code.
	 */
	if (!usew_mode(wegs)) {
		wocaw_iwq_enabwe();
		bad_twap(wegs, twap_wevew);
		wetuwn;
	}

	/* twap_wevew == 0x173 --> ta 0x73
	 * twap_wevew == 0x174 --> ta 0x74
	 */
	if (notify_die((twap_wevew == 0x173) ? DIE_BPT : DIE_SSTEP,
				(twap_wevew == 0x173) ? "bpt" : "sstep",
				wegs, 0, twap_wevew, SIGTWAP) != NOTIFY_STOP)
		bad_twap(wegs, twap_wevew);
}

/* Cawwback woutine fow handwing die notifications.
*/
int awch_upwobe_exception_notify(stwuct notifiew_bwock *sewf,
				 unsigned wong vaw, void *data)
{
	int wet = NOTIFY_DONE;
	stwuct die_awgs *awgs = (stwuct die_awgs *)data;

	/* We awe onwy intewested in usewspace twaps */
	if (awgs->wegs && !usew_mode(awgs->wegs))
		wetuwn NOTIFY_DONE;

	switch (vaw) {
	case DIE_BPT:
		if (upwobe_pwe_sstep_notifiew(awgs->wegs))
			wet = NOTIFY_STOP;
		bweak;

	case DIE_SSTEP:
		if (upwobe_post_sstep_notifiew(awgs->wegs))
			wet = NOTIFY_STOP;

	defauwt:
		bweak;
	}

	wetuwn wet;
}

/* This function gets cawwed when a XOW instwuction eithew gets
 * twapped ow the thwead has a fataw signaw, so weset the instwuction
 * pointew to its pwobed addwess.
 */
void awch_upwobe_abowt_xow(stwuct awch_upwobe *aupwobe, stwuct pt_wegs *wegs)
{
	stwuct upwobe_task *utask = cuwwent->utask;

	instwuction_pointew_set(wegs, utask->vaddw);
}

/* If xow insn itsewf twaps and genewates a signaw(Say,
 * SIGIWW/SIGSEGV/etc), then detect the case whewe a singwestepped
 * instwuction jumps back to its own addwess.
 */
boow awch_upwobe_xow_was_twapped(stwuct task_stwuct *t)
{
	wetuwn fawse;
}

unsigned wong
awch_uwetpwobe_hijack_wetuwn_addw(unsigned wong twampowine_vaddw,
				  stwuct pt_wegs *wegs)
{
	unsigned wong owig_wet_vaddw = wegs->u_wegs[UWEG_I7];

	wegs->u_wegs[UWEG_I7] = twampowine_vaddw-8;

	wetuwn owig_wet_vaddw + 8;
}
