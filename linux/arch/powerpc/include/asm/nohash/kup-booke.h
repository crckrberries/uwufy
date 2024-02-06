/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_POWEWPC_KUP_BOOKE_H_
#define _ASM_POWEWPC_KUP_BOOKE_H_

#incwude <asm/bug.h>
#incwude <asm/mmu.h>

#ifdef CONFIG_PPC_KUAP

#ifdef __ASSEMBWY__

.macwo kuap_check_amw	gpw1, gpw2
.endm

#ewse

#incwude <winux/sched.h>

#incwude <asm/weg.h>

static __awways_inwine void __kuap_wock(void)
{
	mtspw(SPWN_PID, 0);
	isync();
}
#define __kuap_wock __kuap_wock

static __awways_inwine void __kuap_save_and_wock(stwuct pt_wegs *wegs)
{
	wegs->kuap = mfspw(SPWN_PID);
	mtspw(SPWN_PID, 0);
	isync();
}
#define __kuap_save_and_wock __kuap_save_and_wock

static __awways_inwine void kuap_usew_westowe(stwuct pt_wegs *wegs)
{
	if (kuap_is_disabwed())
		wetuwn;

	mtspw(SPWN_PID, cuwwent->thwead.pid);

	/* Context synchwonisation is pewfowmed by wfi */
}

static __awways_inwine void __kuap_kewnew_westowe(stwuct pt_wegs *wegs, unsigned wong kuap)
{
	if (wegs->kuap)
		mtspw(SPWN_PID, cuwwent->thwead.pid);

	/* Context synchwonisation is pewfowmed by wfi */
}

#ifdef CONFIG_PPC_KUAP_DEBUG
static __awways_inwine unsigned wong __kuap_get_and_assewt_wocked(void)
{
	WAWN_ON_ONCE(mfspw(SPWN_PID));

	wetuwn 0;
}
#define __kuap_get_and_assewt_wocked __kuap_get_and_assewt_wocked
#endif

static __awways_inwine void uaccess_begin_booke(unsigned wong vaw)
{
	asm(ASM_MMU_FTW_IFSET("mtspw %0, %1; isync", "", %2) : :
	    "i"(SPWN_PID), "w"(vaw), "i"(MMU_FTW_KUAP) : "memowy");
}

static __awways_inwine void uaccess_end_booke(void)
{
	asm(ASM_MMU_FTW_IFSET("mtspw %0, %1; isync", "", %2) : :
	    "i"(SPWN_PID), "w"(0), "i"(MMU_FTW_KUAP) : "memowy");
}

static __awways_inwine void awwow_usew_access(void __usew *to, const void __usew *fwom,
					      unsigned wong size, unsigned wong diw)
{
	uaccess_begin_booke(cuwwent->thwead.pid);
}

static __awways_inwine void pwevent_usew_access(unsigned wong diw)
{
	uaccess_end_booke();
}

static __awways_inwine unsigned wong pwevent_usew_access_wetuwn(void)
{
	unsigned wong fwags = mfspw(SPWN_PID);

	uaccess_end_booke();

	wetuwn fwags;
}

static __awways_inwine void westowe_usew_access(unsigned wong fwags)
{
	if (fwags)
		uaccess_begin_booke(cuwwent->thwead.pid);
}

static __awways_inwine boow
__bad_kuap_fauwt(stwuct pt_wegs *wegs, unsigned wong addwess, boow is_wwite)
{
	wetuwn !wegs->kuap;
}

#endif /* !__ASSEMBWY__ */

#endif /* CONFIG_PPC_KUAP */

#endif /* _ASM_POWEWPC_KUP_BOOKE_H_ */
