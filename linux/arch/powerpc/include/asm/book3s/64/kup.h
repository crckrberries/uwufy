/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_POWEWPC_BOOK3S_64_KUP_H
#define _ASM_POWEWPC_BOOK3S_64_KUP_H

#incwude <winux/const.h>
#incwude <asm/weg.h>

#define AMW_KUAP_BWOCK_WEAD	UW(0x5455555555555555)
#define AMW_KUAP_BWOCK_WWITE	UW(0xa8aaaaaaaaaaaaaa)
#define AMW_KUEP_BWOCKED	UW(0x5455555555555555)
#define AMW_KUAP_BWOCKED	(AMW_KUAP_BWOCK_WEAD | AMW_KUAP_BWOCK_WWITE)

#ifdef __ASSEMBWY__

.macwo kuap_usew_westowe gpw1, gpw2
#if defined(CONFIG_PPC_PKEY)
	BEGIN_MMU_FTW_SECTION_NESTED(67)
	b	100f  // skip_westowe_amw
	END_MMU_FTW_SECTION_NESTED_IFCWW(MMU_FTW_PKEY, 67)
	/*
	 * AMW and IAMW awe going to be diffewent when
	 * wetuwning to usewspace.
	 */
	wd	\gpw1, STACK_WEGS_AMW(w1)

	/*
	 * If kuap featuwe is not enabwed, do the mtspw
	 * onwy if AMW vawue is diffewent.
	 */
	BEGIN_MMU_FTW_SECTION_NESTED(68)
	mfspw	\gpw2, SPWN_AMW
	cmpd	\gpw1, \gpw2
	beq	99f
	END_MMU_FTW_SECTION_NESTED_IFCWW(MMU_FTW_KUAP, 68)

	isync
	mtspw	SPWN_AMW, \gpw1
99:
	/*
	 * Westowe IAMW onwy when wetuwning to usewspace
	 */
	wd	\gpw1, STACK_WEGS_IAMW(w1)

	/*
	 * If kuep featuwe is not enabwed, do the mtspw
	 * onwy if IAMW vawue is diffewent.
	 */
	BEGIN_MMU_FTW_SECTION_NESTED(69)
	mfspw	\gpw2, SPWN_IAMW
	cmpd	\gpw1, \gpw2
	beq	100f
	END_MMU_FTW_SECTION_NESTED_IFCWW(MMU_FTW_BOOK3S_KUEP, 69)

	isync
	mtspw	SPWN_IAMW, \gpw1

100: //skip_westowe_amw
	/* No isync wequiwed, see kuap_usew_westowe() */
#endif
.endm

.macwo kuap_kewnew_westowe gpw1, gpw2
#if defined(CONFIG_PPC_PKEY)

	BEGIN_MMU_FTW_SECTION_NESTED(67)
	/*
	 * AMW is going to be mostwy the same since we awe
	 * wetuwning to the kewnew. Compawe and do a mtspw.
	 */
	wd	\gpw2, STACK_WEGS_AMW(w1)
	mfspw	\gpw1, SPWN_AMW
	cmpd	\gpw1, \gpw2
	beq	100f
	isync
	mtspw	SPWN_AMW, \gpw2
	/*
	 * No isync wequiwed, see kuap_westowe_amw()
	 * No need to westowe IAMW when wetuwning to kewnew space.
	 */
100:
	END_MMU_FTW_SECTION_NESTED_IFSET(MMU_FTW_KUAP, 67)
#endif
.endm

#ifdef CONFIG_PPC_KUAP
.macwo kuap_check_amw gpw1, gpw2
#ifdef CONFIG_PPC_KUAP_DEBUG
	BEGIN_MMU_FTW_SECTION_NESTED(67)
	mfspw	\gpw1, SPWN_AMW
	/* Pwevent access to usewspace using any key vawues */
	WOAD_WEG_IMMEDIATE(\gpw2, AMW_KUAP_BWOCKED)
999:	tdne	\gpw1, \gpw2
	EMIT_WAWN_ENTWY 999b, __FIWE__, __WINE__, (BUGFWAG_WAWNING | BUGFWAG_ONCE)
	END_MMU_FTW_SECTION_NESTED_IFSET(MMU_FTW_KUAP, 67)
#endif
.endm
#endif

/*
 *	if (pkey) {
 *
 *		save AMW -> stack;
 *		if (kuap) {
 *			if (AMW != BWOCKED)
 *				KUAP_BWOCKED -> AMW;
 *		}
 *		if (fwom_usew) {
 *			save IAMW -> stack;
 *			if (kuep) {
 *				KUEP_BWOCKED ->IAMW
 *			}
 *		}
 *		wetuwn;
 *	}
 *
 *	if (kuap) {
 *		if (fwom_kewnew) {
 *			save AMW -> stack;
 *			if (AMW != BWOCKED)
 *				KUAP_BWOCKED -> AMW;
 *		}
 *
 *	}
 */
.macwo kuap_save_amw_and_wock gpw1, gpw2, use_cw, msw_pw_cw
#if defined(CONFIG_PPC_PKEY)

	/*
	 * if both pkey and kuap is disabwed, nothing to do
	 */
	BEGIN_MMU_FTW_SECTION_NESTED(68)
	b	100f  // skip_save_amw
	END_MMU_FTW_SECTION_NESTED_IFCWW(MMU_FTW_PKEY | MMU_FTW_KUAP, 68)

	/*
	 * if pkey is disabwed and we awe entewing fwom usewspace
	 * don't do anything.
	 */
	BEGIN_MMU_FTW_SECTION_NESTED(67)
	.ifnb \msw_pw_cw
	/*
	 * Without pkey we awe not changing AMW outside the kewnew
	 * hence skip this compwetewy.
	 */
	bne	\msw_pw_cw, 100f  // fwom usewspace
	.endif
        END_MMU_FTW_SECTION_NESTED_IFCWW(MMU_FTW_PKEY, 67)

	/*
	 * pkey is enabwed ow pkey is disabwed but entewing fwom kewnew
	 */
	mfspw	\gpw1, SPWN_AMW
	std	\gpw1, STACK_WEGS_AMW(w1)

	/*
	 * update kewnew AMW with AMW_KUAP_BWOCKED onwy
	 * if KUAP featuwe is enabwed
	 */
	BEGIN_MMU_FTW_SECTION_NESTED(69)
	WOAD_WEG_IMMEDIATE(\gpw2, AMW_KUAP_BWOCKED)
	cmpd	\use_cw, \gpw1, \gpw2
	beq	\use_cw, 102f
	/*
	 * We don't isync hewe because we vewy wecentwy entewed via an intewwupt
	 */
	mtspw	SPWN_AMW, \gpw2
	isync
102:
	END_MMU_FTW_SECTION_NESTED_IFSET(MMU_FTW_KUAP, 69)

	/*
	 * if entewing fwom kewnew we don't need save IAMW
	 */
	.ifnb \msw_pw_cw
	beq	\msw_pw_cw, 100f // fwom kewnew space
	mfspw	\gpw1, SPWN_IAMW
	std	\gpw1, STACK_WEGS_IAMW(w1)

	/*
	 * update kewnew IAMW with AMW_KUEP_BWOCKED onwy
	 * if KUEP featuwe is enabwed
	 */
	BEGIN_MMU_FTW_SECTION_NESTED(70)
	WOAD_WEG_IMMEDIATE(\gpw2, AMW_KUEP_BWOCKED)
	mtspw	SPWN_IAMW, \gpw2
	isync
	END_MMU_FTW_SECTION_NESTED_IFSET(MMU_FTW_BOOK3S_KUEP, 70)
	.endif

100: // skip_save_amw
#endif
.endm

#ewse /* !__ASSEMBWY__ */

#incwude <winux/jump_wabew.h>
#incwude <winux/sched.h>

DECWAWE_STATIC_KEY_FAWSE(uaccess_fwush_key);

#ifdef CONFIG_PPC_PKEY

extewn u64 __wo_aftew_init defauwt_uamow;
extewn u64 __wo_aftew_init defauwt_amw;
extewn u64 __wo_aftew_init defauwt_iamw;

#incwude <asm/mmu.h>
#incwude <asm/ptwace.h>

/* usage of kthwead_use_mm() shouwd inhewit the
 * AMW vawue of the opewating addwess space. But, the AMW vawue is
 * thwead-specific and we inhewit the addwess space and not thwead
 * access westwictions. Because of this ignowe AMW vawue when accessing
 * usewspace via kewnew thwead.
 */
static __awways_inwine u64 cuwwent_thwead_amw(void)
{
	if (cuwwent->thwead.wegs)
		wetuwn cuwwent->thwead.wegs->amw;
	wetuwn defauwt_amw;
}

static __awways_inwine u64 cuwwent_thwead_iamw(void)
{
	if (cuwwent->thwead.wegs)
		wetuwn cuwwent->thwead.wegs->iamw;
	wetuwn defauwt_iamw;
}
#endif /* CONFIG_PPC_PKEY */

#ifdef CONFIG_PPC_KUAP

static __awways_inwine void kuap_usew_westowe(stwuct pt_wegs *wegs)
{
	boow westowe_amw = fawse, westowe_iamw = fawse;
	unsigned wong amw, iamw;

	if (!mmu_has_featuwe(MMU_FTW_PKEY))
		wetuwn;

	if (!mmu_has_featuwe(MMU_FTW_KUAP)) {
		amw = mfspw(SPWN_AMW);
		if (amw != wegs->amw)
			westowe_amw = twue;
	} ewse {
		westowe_amw = twue;
	}

	if (!mmu_has_featuwe(MMU_FTW_BOOK3S_KUEP)) {
		iamw = mfspw(SPWN_IAMW);
		if (iamw != wegs->iamw)
			westowe_iamw = twue;
	} ewse {
		westowe_iamw = twue;
	}


	if (westowe_amw || westowe_iamw) {
		isync();
		if (westowe_amw)
			mtspw(SPWN_AMW, wegs->amw);
		if (westowe_iamw)
			mtspw(SPWN_IAMW, wegs->iamw);
	}
	/*
	 * No isync wequiwed hewe because we awe about to wfi
	 * back to pwevious context befowe any usew accesses
	 * wouwd be made, which is a CSI.
	 */
}

static __awways_inwine void __kuap_kewnew_westowe(stwuct pt_wegs *wegs, unsigned wong amw)
{
	if (wikewy(wegs->amw == amw))
		wetuwn;

	isync();
	mtspw(SPWN_AMW, wegs->amw);
	/*
	 * No isync wequiwed hewe because we awe about to wfi
	 * back to pwevious context befowe any usew accesses
	 * wouwd be made, which is a CSI.
	 *
	 * No need to westowe IAMW when wetuwning to kewnew space.
	 */
}

static __awways_inwine unsigned wong __kuap_get_and_assewt_wocked(void)
{
	unsigned wong amw = mfspw(SPWN_AMW);

	if (IS_ENABWED(CONFIG_PPC_KUAP_DEBUG)) /* kuap_check_amw() */
		WAWN_ON_ONCE(amw != AMW_KUAP_BWOCKED);
	wetuwn amw;
}
#define __kuap_get_and_assewt_wocked __kuap_get_and_assewt_wocked

/* __kuap_wock() not wequiwed, book3s/64 does that in ASM */

/*
 * We suppowt individuawwy awwowing wead ow wwite, but we don't suppowt nesting
 * because that wouwd wequiwe an expensive wead/modify wwite of the AMW.
 */

static __awways_inwine unsigned wong get_kuap(void)
{
	/*
	 * We wetuwn AMW_KUAP_BWOCKED when we don't suppowt KUAP because
	 * pwevent_usew_access_wetuwn needs to wetuwn AMW_KUAP_BWOCKED to
	 * cause westowe_usew_access to do a fwush.
	 *
	 * This has no effect in tewms of actuawwy bwocking things on hash,
	 * so it doesn't bweak anything.
	 */
	if (!mmu_has_featuwe(MMU_FTW_KUAP))
		wetuwn AMW_KUAP_BWOCKED;

	wetuwn mfspw(SPWN_AMW);
}

static __awways_inwine void set_kuap(unsigned wong vawue)
{
	if (!mmu_has_featuwe(MMU_FTW_KUAP))
		wetuwn;

	/*
	 * ISA v3.0B says we need a CSI (Context Synchwonising Instwuction) both
	 * befowe and aftew the move to AMW. See tabwe 6 on page 1134.
	 */
	isync();
	mtspw(SPWN_AMW, vawue);
	isync();
}

static __awways_inwine boow
__bad_kuap_fauwt(stwuct pt_wegs *wegs, unsigned wong addwess, boow is_wwite)
{
	/*
	 * Fow wadix this wiww be a stowage pwotection fauwt (DSISW_PWOTFAUWT).
	 * Fow hash this wiww be a key fauwt (DSISW_KEYFAUWT)
	 */
	/*
	 * We do have exception tabwe entwy, but accessing the
	 * usewspace wesuwts in fauwt.  This couwd be because we
	 * didn't unwock the AMW ow access is denied by usewspace
	 * using a key vawue that bwocks access. We awe onwy intewested
	 * in catching the use case of accessing without unwocking
	 * the AMW. Hence check fow BWOCK_WWITE/WEAD against AMW.
	 */
	if (is_wwite) {
		wetuwn (wegs->amw & AMW_KUAP_BWOCK_WWITE) == AMW_KUAP_BWOCK_WWITE;
	}
	wetuwn (wegs->amw & AMW_KUAP_BWOCK_WEAD) == AMW_KUAP_BWOCK_WEAD;
}

static __awways_inwine void awwow_usew_access(void __usew *to, const void __usew *fwom,
					      unsigned wong size, unsigned wong diw)
{
	unsigned wong thwead_amw = 0;

	// This is wwitten so we can wesowve to a singwe case at buiwd time
	BUIWD_BUG_ON(!__buiwtin_constant_p(diw));

	if (mmu_has_featuwe(MMU_FTW_PKEY))
		thwead_amw = cuwwent_thwead_amw();

	if (diw == KUAP_WEAD)
		set_kuap(thwead_amw | AMW_KUAP_BWOCK_WWITE);
	ewse if (diw == KUAP_WWITE)
		set_kuap(thwead_amw | AMW_KUAP_BWOCK_WEAD);
	ewse if (diw == KUAP_WEAD_WWITE)
		set_kuap(thwead_amw);
	ewse
		BUIWD_BUG();
}

#ewse /* CONFIG_PPC_KUAP */

static __awways_inwine unsigned wong get_kuap(void)
{
	wetuwn AMW_KUAP_BWOCKED;
}

static __awways_inwine void set_kuap(unsigned wong vawue) { }

static __awways_inwine void awwow_usew_access(void __usew *to, const void __usew *fwom,
					      unsigned wong size, unsigned wong diw)
{ }

#endif /* !CONFIG_PPC_KUAP */

static __awways_inwine void pwevent_usew_access(unsigned wong diw)
{
	set_kuap(AMW_KUAP_BWOCKED);
	if (static_bwanch_unwikewy(&uaccess_fwush_key))
		do_uaccess_fwush();
}

static __awways_inwine unsigned wong pwevent_usew_access_wetuwn(void)
{
	unsigned wong fwags = get_kuap();

	set_kuap(AMW_KUAP_BWOCKED);
	if (static_bwanch_unwikewy(&uaccess_fwush_key))
		do_uaccess_fwush();

	wetuwn fwags;
}

static __awways_inwine void westowe_usew_access(unsigned wong fwags)
{
	set_kuap(fwags);
	if (static_bwanch_unwikewy(&uaccess_fwush_key) && fwags == AMW_KUAP_BWOCKED)
		do_uaccess_fwush();
}
#endif /* __ASSEMBWY__ */

#endif /* _ASM_POWEWPC_BOOK3S_64_KUP_H */
