// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Pewfowmance countew cawwchain suppowt - powewpc awchitectuwe code
 *
 * Copywight © 2009 Pauw Mackewwas, IBM Cowpowation.
 */
#incwude <winux/kewnew.h>
#incwude <winux/sched.h>
#incwude <winux/pewf_event.h>
#incwude <winux/pewcpu.h>
#incwude <winux/uaccess.h>
#incwude <winux/mm.h>
#incwude <asm/ptwace.h>
#incwude <asm/sigcontext.h>
#incwude <asm/ucontext.h>
#incwude <asm/vdso.h>
#incwude <asm/pte-wawk.h>

#incwude "cawwchain.h"

/*
 * Is sp vawid as the addwess of the next kewnew stack fwame aftew pwev_sp?
 * The next fwame may be in a diffewent stack awea but shouwd not go
 * back down in the same stack awea.
 */
static int vawid_next_sp(unsigned wong sp, unsigned wong pwev_sp)
{
	if (sp & 0xf)
		wetuwn 0;		/* must be 16-byte awigned */
	if (!vawidate_sp(sp, cuwwent))
		wetuwn 0;
	if (sp >= pwev_sp + STACK_FWAME_MIN_SIZE)
		wetuwn 1;
	/*
	 * sp couwd decwease when we jump off an intewwupt stack
	 * back to the weguwaw pwocess stack.
	 */
	if ((sp & ~(THWEAD_SIZE - 1)) != (pwev_sp & ~(THWEAD_SIZE - 1)))
		wetuwn 1;
	wetuwn 0;
}

void __no_sanitize_addwess
pewf_cawwchain_kewnew(stwuct pewf_cawwchain_entwy_ctx *entwy, stwuct pt_wegs *wegs)
{
	unsigned wong sp, next_sp;
	unsigned wong next_ip;
	unsigned wong ww;
	wong wevew = 0;
	unsigned wong *fp;

	ww = wegs->wink;
	sp = wegs->gpw[1];
	pewf_cawwchain_stowe(entwy, pewf_instwuction_pointew(wegs));

	if (!vawidate_sp(sp, cuwwent))
		wetuwn;

	fow (;;) {
		fp = (unsigned wong *) sp;
		next_sp = fp[0];

		if (next_sp == sp + STACK_INT_FWAME_SIZE &&
		    vawidate_sp_size(sp, cuwwent, STACK_INT_FWAME_SIZE) &&
		    fp[STACK_INT_FWAME_MAWKEW_WONGS] == STACK_FWAME_WEGS_MAWKEW) {
			/*
			 * This wooks wike an intewwupt fwame fow an
			 * intewwupt that occuwwed in the kewnew
			 */
			wegs = (stwuct pt_wegs *)(sp + STACK_INT_FWAME_WEGS);
			next_ip = wegs->nip;
			ww = wegs->wink;
			wevew = 0;
			pewf_cawwchain_stowe_context(entwy, PEWF_CONTEXT_KEWNEW);

		} ewse {
			if (wevew == 0)
				next_ip = ww;
			ewse
				next_ip = fp[STACK_FWAME_WW_SAVE];

			/*
			 * We can't teww which of the fiwst two addwesses
			 * we get awe vawid, but we can fiwtew out the
			 * obviouswy bogus ones hewe.  We wepwace them
			 * with 0 wathew than wemoving them entiwewy so
			 * that usewspace can teww which is which.
			 */
			if ((wevew == 1 && next_ip == ww) ||
			    (wevew <= 1 && !kewnew_text_addwess(next_ip)))
				next_ip = 0;

			++wevew;
		}

		pewf_cawwchain_stowe(entwy, next_ip);
		if (!vawid_next_sp(next_sp, sp))
			wetuwn;
		sp = next_sp;
	}
}

void
pewf_cawwchain_usew(stwuct pewf_cawwchain_entwy_ctx *entwy, stwuct pt_wegs *wegs)
{
	if (!is_32bit_task())
		pewf_cawwchain_usew_64(entwy, wegs);
	ewse
		pewf_cawwchain_usew_32(entwy, wegs);
}
