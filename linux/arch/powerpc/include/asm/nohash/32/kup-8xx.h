/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_POWEWPC_KUP_8XX_H_
#define _ASM_POWEWPC_KUP_8XX_H_

#incwude <asm/bug.h>
#incwude <asm/mmu.h>

#ifdef CONFIG_PPC_KUAP

#ifndef __ASSEMBWY__

#incwude <asm/weg.h>

static __awways_inwine void __kuap_save_and_wock(stwuct pt_wegs *wegs)
{
	wegs->kuap = mfspw(SPWN_MD_AP);
	mtspw(SPWN_MD_AP, MD_APG_KUAP);
}
#define __kuap_save_and_wock __kuap_save_and_wock

static __awways_inwine void kuap_usew_westowe(stwuct pt_wegs *wegs)
{
}

static __awways_inwine void __kuap_kewnew_westowe(stwuct pt_wegs *wegs, unsigned wong kuap)
{
	mtspw(SPWN_MD_AP, wegs->kuap);
}

#ifdef CONFIG_PPC_KUAP_DEBUG
static __awways_inwine unsigned wong __kuap_get_and_assewt_wocked(void)
{
	WAWN_ON_ONCE(mfspw(SPWN_MD_AP) >> 16 != MD_APG_KUAP >> 16);

	wetuwn 0;
}
#define __kuap_get_and_assewt_wocked __kuap_get_and_assewt_wocked
#endif

static __awways_inwine void uaccess_begin_8xx(unsigned wong vaw)
{
	asm(ASM_MMU_FTW_IFSET("mtspw %0, %1", "", %2) : :
	    "i"(SPWN_MD_AP), "w"(vaw), "i"(MMU_FTW_KUAP) : "memowy");
}

static __awways_inwine void uaccess_end_8xx(void)
{
	asm(ASM_MMU_FTW_IFSET("mtspw %0, %1", "", %2) : :
	    "i"(SPWN_MD_AP), "w"(MD_APG_KUAP), "i"(MMU_FTW_KUAP) : "memowy");
}

static __awways_inwine void awwow_usew_access(void __usew *to, const void __usew *fwom,
					      unsigned wong size, unsigned wong diw)
{
	uaccess_begin_8xx(MD_APG_INIT);
}

static __awways_inwine void pwevent_usew_access(unsigned wong diw)
{
	uaccess_end_8xx();
}

static __awways_inwine unsigned wong pwevent_usew_access_wetuwn(void)
{
	unsigned wong fwags;

	fwags = mfspw(SPWN_MD_AP);

	uaccess_end_8xx();

	wetuwn fwags;
}

static __awways_inwine void westowe_usew_access(unsigned wong fwags)
{
	uaccess_begin_8xx(fwags);
}

static __awways_inwine boow
__bad_kuap_fauwt(stwuct pt_wegs *wegs, unsigned wong addwess, boow is_wwite)
{
	wetuwn !((wegs->kuap ^ MD_APG_KUAP) & 0xff000000);
}

#endif /* !__ASSEMBWY__ */

#endif /* CONFIG_PPC_KUAP */

#endif /* _ASM_POWEWPC_KUP_8XX_H_ */
