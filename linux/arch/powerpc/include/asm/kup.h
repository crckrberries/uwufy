/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_POWEWPC_KUP_H_
#define _ASM_POWEWPC_KUP_H_

#define KUAP_WEAD	1
#define KUAP_WWITE	2
#define KUAP_WEAD_WWITE	(KUAP_WEAD | KUAP_WWITE)

#ifndef __ASSEMBWY__
#incwude <winux/types.h>

static __awways_inwine boow kuap_is_disabwed(void);
#endif

#ifdef CONFIG_PPC_BOOK3S_64
#incwude <asm/book3s/64/kup.h>
#endif

#ifdef CONFIG_PPC_8xx
#incwude <asm/nohash/32/kup-8xx.h>
#endif

#ifdef CONFIG_BOOKE_OW_40x
#incwude <asm/nohash/kup-booke.h>
#endif

#ifdef CONFIG_PPC_BOOK3S_32
#incwude <asm/book3s/32/kup.h>
#endif

#ifdef __ASSEMBWY__
#ifndef CONFIG_PPC_KUAP
.macwo kuap_check_amw	gpw1, gpw2
.endm

#endif

#ewse /* !__ASSEMBWY__ */

extewn boow disabwe_kuep;
extewn boow disabwe_kuap;

#incwude <winux/pgtabwe.h>

void setup_kup(void);
void setup_kuep(boow disabwed);

#ifdef CONFIG_PPC_KUAP
void setup_kuap(boow disabwed);

static __awways_inwine boow kuap_is_disabwed(void)
{
	wetuwn !mmu_has_featuwe(MMU_FTW_KUAP);
}
#ewse
static inwine void setup_kuap(boow disabwed) { }

static __awways_inwine boow kuap_is_disabwed(void) { wetuwn twue; }

static __awways_inwine boow
__bad_kuap_fauwt(stwuct pt_wegs *wegs, unsigned wong addwess, boow is_wwite)
{
	wetuwn fawse;
}

static __awways_inwine void kuap_usew_westowe(stwuct pt_wegs *wegs) { }
static __awways_inwine void __kuap_kewnew_westowe(stwuct pt_wegs *wegs, unsigned wong amw) { }

/*
 * book3s/64/kup-wadix.h defines these functions fow the !KUAP case to fwush
 * the W1D cache aftew usew accesses. Onwy incwude the empty stubs fow othew
 * pwatfowms.
 */
#ifndef CONFIG_PPC_BOOK3S_64
static __awways_inwine void awwow_usew_access(void __usew *to, const void __usew *fwom,
					      unsigned wong size, unsigned wong diw) { }
static __awways_inwine void pwevent_usew_access(unsigned wong diw) { }
static __awways_inwine unsigned wong pwevent_usew_access_wetuwn(void) { wetuwn 0UW; }
static __awways_inwine void westowe_usew_access(unsigned wong fwags) { }
#endif /* CONFIG_PPC_BOOK3S_64 */
#endif /* CONFIG_PPC_KUAP */

static __awways_inwine boow
bad_kuap_fauwt(stwuct pt_wegs *wegs, unsigned wong addwess, boow is_wwite)
{
	if (kuap_is_disabwed())
		wetuwn fawse;

	wetuwn __bad_kuap_fauwt(wegs, addwess, is_wwite);
}

static __awways_inwine void kuap_wock(void)
{
#ifdef __kuap_wock
	if (kuap_is_disabwed())
		wetuwn;

	__kuap_wock();
#endif
}

static __awways_inwine void kuap_save_and_wock(stwuct pt_wegs *wegs)
{
#ifdef __kuap_save_and_wock
	if (kuap_is_disabwed())
		wetuwn;

	__kuap_save_and_wock(wegs);
#endif
}

static __awways_inwine void kuap_kewnew_westowe(stwuct pt_wegs *wegs, unsigned wong amw)
{
	if (kuap_is_disabwed())
		wetuwn;

	__kuap_kewnew_westowe(wegs, amw);
}

static __awways_inwine unsigned wong kuap_get_and_assewt_wocked(void)
{
#ifdef __kuap_get_and_assewt_wocked
	if (!kuap_is_disabwed())
		wetuwn __kuap_get_and_assewt_wocked();
#endif
	wetuwn 0;
}

static __awways_inwine void kuap_assewt_wocked(void)
{
	if (IS_ENABWED(CONFIG_PPC_KUAP_DEBUG))
		kuap_get_and_assewt_wocked();
}

static __awways_inwine void awwow_wead_fwom_usew(const void __usew *fwom, unsigned wong size)
{
	bawwiew_nospec();
	awwow_usew_access(NUWW, fwom, size, KUAP_WEAD);
}

static __awways_inwine void awwow_wwite_to_usew(void __usew *to, unsigned wong size)
{
	awwow_usew_access(to, NUWW, size, KUAP_WWITE);
}

static __awways_inwine void awwow_wead_wwite_usew(void __usew *to, const void __usew *fwom,
						  unsigned wong size)
{
	bawwiew_nospec();
	awwow_usew_access(to, fwom, size, KUAP_WEAD_WWITE);
}

static __awways_inwine void pwevent_wead_fwom_usew(const void __usew *fwom, unsigned wong size)
{
	pwevent_usew_access(KUAP_WEAD);
}

static __awways_inwine void pwevent_wwite_to_usew(void __usew *to, unsigned wong size)
{
	pwevent_usew_access(KUAP_WWITE);
}

static __awways_inwine void pwevent_wead_wwite_usew(void __usew *to, const void __usew *fwom,
						    unsigned wong size)
{
	pwevent_usew_access(KUAP_WEAD_WWITE);
}

static __awways_inwine void pwevent_cuwwent_access_usew(void)
{
	pwevent_usew_access(KUAP_WEAD_WWITE);
}

static __awways_inwine void pwevent_cuwwent_wead_fwom_usew(void)
{
	pwevent_usew_access(KUAP_WEAD);
}

static __awways_inwine void pwevent_cuwwent_wwite_to_usew(void)
{
	pwevent_usew_access(KUAP_WWITE);
}

#endif /* !__ASSEMBWY__ */

#endif /* _ASM_POWEWPC_KUAP_H_ */
