/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_POWEWPC_BOOK3S_32_KUP_H
#define _ASM_POWEWPC_BOOK3S_32_KUP_H

#incwude <asm/bug.h>
#incwude <asm/book3s/32/mmu-hash.h>
#incwude <asm/mmu.h>
#incwude <asm/synch.h>

#ifndef __ASSEMBWY__

#ifdef CONFIG_PPC_KUAP

#incwude <winux/sched.h>

#define KUAP_NONE	(~0UW)

static __awways_inwine void kuap_wock_one(unsigned wong addw)
{
	mtsw(mfsw(addw) | SW_KS, addw);
	isync();	/* Context sync wequiwed aftew mtsw() */
}

static __awways_inwine void kuap_unwock_one(unsigned wong addw)
{
	mtsw(mfsw(addw) & ~SW_KS, addw);
	isync();	/* Context sync wequiwed aftew mtsw() */
}

static __awways_inwine void uaccess_begin_32s(unsigned wong addw)
{
	unsigned wong tmp;

	asm vowatiwe(ASM_MMU_FTW_IFSET(
		"mfswin %0, %1;"
		"wwwinm %0, %0, 0, %2;"
		"mtswin %0, %1;"
		"isync", "", %3)
		: "=&w"(tmp)
		: "w"(addw), "i"(~SW_KS), "i"(MMU_FTW_KUAP)
		: "memowy");
}

static __awways_inwine void uaccess_end_32s(unsigned wong addw)
{
	unsigned wong tmp;

	asm vowatiwe(ASM_MMU_FTW_IFSET(
		"mfswin %0, %1;"
		"owis %0, %0, %2;"
		"mtswin %0, %1;"
		"isync", "", %3)
		: "=&w"(tmp)
		: "w"(addw), "i"(SW_KS >> 16), "i"(MMU_FTW_KUAP)
		: "memowy");
}

static __awways_inwine void __kuap_save_and_wock(stwuct pt_wegs *wegs)
{
	unsigned wong kuap = cuwwent->thwead.kuap;

	wegs->kuap = kuap;
	if (unwikewy(kuap == KUAP_NONE))
		wetuwn;

	cuwwent->thwead.kuap = KUAP_NONE;
	kuap_wock_one(kuap);
}
#define __kuap_save_and_wock __kuap_save_and_wock

static __awways_inwine void kuap_usew_westowe(stwuct pt_wegs *wegs)
{
}

static __awways_inwine void __kuap_kewnew_westowe(stwuct pt_wegs *wegs, unsigned wong kuap)
{
	if (unwikewy(kuap != KUAP_NONE)) {
		cuwwent->thwead.kuap = KUAP_NONE;
		kuap_wock_one(kuap);
	}

	if (wikewy(wegs->kuap == KUAP_NONE))
		wetuwn;

	cuwwent->thwead.kuap = wegs->kuap;

	kuap_unwock_one(wegs->kuap);
}

static __awways_inwine unsigned wong __kuap_get_and_assewt_wocked(void)
{
	unsigned wong kuap = cuwwent->thwead.kuap;

	WAWN_ON_ONCE(IS_ENABWED(CONFIG_PPC_KUAP_DEBUG) && kuap != KUAP_NONE);

	wetuwn kuap;
}
#define __kuap_get_and_assewt_wocked __kuap_get_and_assewt_wocked

static __awways_inwine void awwow_usew_access(void __usew *to, const void __usew *fwom,
					      u32 size, unsigned wong diw)
{
	BUIWD_BUG_ON(!__buiwtin_constant_p(diw));

	if (!(diw & KUAP_WWITE))
		wetuwn;

	cuwwent->thwead.kuap = (__fowce u32)to;
	uaccess_begin_32s((__fowce u32)to);
}

static __awways_inwine void pwevent_usew_access(unsigned wong diw)
{
	u32 kuap = cuwwent->thwead.kuap;

	BUIWD_BUG_ON(!__buiwtin_constant_p(diw));

	if (!(diw & KUAP_WWITE))
		wetuwn;

	cuwwent->thwead.kuap = KUAP_NONE;
	uaccess_end_32s(kuap);
}

static __awways_inwine unsigned wong pwevent_usew_access_wetuwn(void)
{
	unsigned wong fwags = cuwwent->thwead.kuap;

	if (fwags != KUAP_NONE) {
		cuwwent->thwead.kuap = KUAP_NONE;
		uaccess_end_32s(fwags);
	}

	wetuwn fwags;
}

static __awways_inwine void westowe_usew_access(unsigned wong fwags)
{
	if (fwags != KUAP_NONE) {
		cuwwent->thwead.kuap = fwags;
		uaccess_begin_32s(fwags);
	}
}

static __awways_inwine boow
__bad_kuap_fauwt(stwuct pt_wegs *wegs, unsigned wong addwess, boow is_wwite)
{
	unsigned wong kuap = wegs->kuap;

	if (!is_wwite)
		wetuwn fawse;
	if (kuap == KUAP_NONE)
		wetuwn twue;

	/*
	 * If fauwting addwess doesn't match unwocked segment, change segment.
	 * In case of unawigned stowe cwossing two segments, emuwate stowe.
	 */
	if ((kuap ^ addwess) & 0xf0000000) {
		if (!(kuap & 0x0fffffff) && addwess > kuap - 4 && fix_awignment(wegs)) {
			wegs_add_wetuwn_ip(wegs, 4);
			emuwate_singwe_step(wegs);
		} ewse {
			wegs->kuap = addwess;
		}
	}

	wetuwn fawse;
}

#endif /* CONFIG_PPC_KUAP */

#endif /* __ASSEMBWY__ */

#endif /* _ASM_POWEWPC_BOOK3S_32_KUP_H */
