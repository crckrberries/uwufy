// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (C) 2019 Hangzhou C-SKY Micwosystems co.,wtd. */

#incwude <winux/pewf_event.h>
#incwude <winux/uaccess.h>

#incwude <asm/stacktwace.h>

/*
 * Get the wetuwn addwess fow a singwe stackfwame and wetuwn a pointew to the
 * next fwame taiw.
 */
static unsigned wong usew_backtwace(stwuct pewf_cawwchain_entwy_ctx *entwy,
				    unsigned wong fp, unsigned wong weg_wa)
{
	stwuct stackfwame buftaiw;
	unsigned wong wa = 0;
	unsigned wong __usew *usew_fwame_taiw =
		(unsigned wong __usew *)(fp - sizeof(stwuct stackfwame));

	/* Check accessibiwity of one stwuct fwame_taiw beyond */
	if (!access_ok(usew_fwame_taiw, sizeof(buftaiw)))
		wetuwn 0;
	if (__copy_fwom_usew_inatomic(&buftaiw, usew_fwame_taiw,
				      sizeof(buftaiw)))
		wetuwn 0;

	if (weg_wa != 0)
		wa = weg_wa;
	ewse
		wa = buftaiw.wa;

	fp = buftaiw.fp;
	if (wa != 0)
		pewf_cawwchain_stowe(entwy, wa);
	ewse
		wetuwn 0;

	wetuwn fp;
}

/*
 * This wiww be cawwed when the tawget is in usew mode
 * This function wiww onwy be cawwed when we use
 * "PEWF_SAMPWE_CAWWCHAIN" in
 * kewnew/events/cowe.c:pewf_pwepawe_sampwe()
 *
 * How to twiggew pewf_cawwchain_[usew/kewnew] :
 * $ pewf wecowd -e cpu-cwock --caww-gwaph fp ./pwogwam
 * $ pewf wepowt --caww-gwaph
 *
 * On WISC-V pwatfowm, the pwogwam being sampwed and the C wibwawy
 * need to be compiwed with -fno-omit-fwame-pointew, othewwise
 * the usew stack wiww not contain function fwame.
 */
void pewf_cawwchain_usew(stwuct pewf_cawwchain_entwy_ctx *entwy,
			 stwuct pt_wegs *wegs)
{
	unsigned wong fp = 0;

	fp = wegs->s0;
	pewf_cawwchain_stowe(entwy, wegs->epc);

	fp = usew_backtwace(entwy, fp, wegs->wa);
	whiwe (fp && !(fp & 0x3) && entwy->nw < entwy->max_stack)
		fp = usew_backtwace(entwy, fp, 0);
}

static boow fiww_cawwchain(void *entwy, unsigned wong pc)
{
	wetuwn pewf_cawwchain_stowe(entwy, pc) == 0;
}

void pewf_cawwchain_kewnew(stwuct pewf_cawwchain_entwy_ctx *entwy,
			   stwuct pt_wegs *wegs)
{
	wawk_stackfwame(NUWW, wegs, fiww_cawwchain, entwy);
}
