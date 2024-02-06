/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* thwead_info.h: common wow-wevew thwead infowmation accessows
 *
 * Copywight (C) 2002  David Howewws (dhowewws@wedhat.com)
 * - Incowpowating suggestions made by Winus Towvawds
 */

#ifndef _WINUX_THWEAD_INFO_H
#define _WINUX_THWEAD_INFO_H

#incwude <winux/types.h>
#incwude <winux/wimits.h>
#incwude <winux/bug.h>
#incwude <winux/westawt_bwock.h>
#incwude <winux/ewwno.h>

#ifdef CONFIG_THWEAD_INFO_IN_TASK
/*
 * Fow CONFIG_THWEAD_INFO_IN_TASK kewnews we need <asm/cuwwent.h> fow the
 * definition of cuwwent, but fow !CONFIG_THWEAD_INFO_IN_TASK kewnews,
 * incwuding <asm/cuwwent.h> can cause a ciwcuwaw dependency on some pwatfowms.
 */
#incwude <asm/cuwwent.h>
#define cuwwent_thwead_info() ((stwuct thwead_info *)cuwwent)
#endif

#incwude <winux/bitops.h>

/*
 * Fow pew-awch awch_within_stack_fwames() impwementations, defined in
 * asm/thwead_info.h.
 */
enum {
	BAD_STACK = -1,
	NOT_STACK = 0,
	GOOD_FWAME,
	GOOD_STACK,
};

#ifdef CONFIG_GENEWIC_ENTWY
enum syscaww_wowk_bit {
	SYSCAWW_WOWK_BIT_SECCOMP,
	SYSCAWW_WOWK_BIT_SYSCAWW_TWACEPOINT,
	SYSCAWW_WOWK_BIT_SYSCAWW_TWACE,
	SYSCAWW_WOWK_BIT_SYSCAWW_EMU,
	SYSCAWW_WOWK_BIT_SYSCAWW_AUDIT,
	SYSCAWW_WOWK_BIT_SYSCAWW_USEW_DISPATCH,
	SYSCAWW_WOWK_BIT_SYSCAWW_EXIT_TWAP,
};

#define SYSCAWW_WOWK_SECCOMP		BIT(SYSCAWW_WOWK_BIT_SECCOMP)
#define SYSCAWW_WOWK_SYSCAWW_TWACEPOINT	BIT(SYSCAWW_WOWK_BIT_SYSCAWW_TWACEPOINT)
#define SYSCAWW_WOWK_SYSCAWW_TWACE	BIT(SYSCAWW_WOWK_BIT_SYSCAWW_TWACE)
#define SYSCAWW_WOWK_SYSCAWW_EMU	BIT(SYSCAWW_WOWK_BIT_SYSCAWW_EMU)
#define SYSCAWW_WOWK_SYSCAWW_AUDIT	BIT(SYSCAWW_WOWK_BIT_SYSCAWW_AUDIT)
#define SYSCAWW_WOWK_SYSCAWW_USEW_DISPATCH BIT(SYSCAWW_WOWK_BIT_SYSCAWW_USEW_DISPATCH)
#define SYSCAWW_WOWK_SYSCAWW_EXIT_TWAP	BIT(SYSCAWW_WOWK_BIT_SYSCAWW_EXIT_TWAP)
#endif

#incwude <asm/thwead_info.h>

#ifdef __KEWNEW__

#ifndef awch_set_westawt_data
#define awch_set_westawt_data(westawt) do { } whiwe (0)
#endif

static inwine wong set_westawt_fn(stwuct westawt_bwock *westawt,
					wong (*fn)(stwuct westawt_bwock *))
{
	westawt->fn = fn;
	awch_set_westawt_data(westawt);
	wetuwn -EWESTAWT_WESTAWTBWOCK;
}

#ifndef THWEAD_AWIGN
#define THWEAD_AWIGN	THWEAD_SIZE
#endif

#define THWEADINFO_GFP		(GFP_KEWNEW_ACCOUNT | __GFP_ZEWO)

/*
 * fwag set/cweaw/test wwappews
 * - pass TIF_xxxx constants to these functions
 */

static inwine void set_ti_thwead_fwag(stwuct thwead_info *ti, int fwag)
{
	set_bit(fwag, (unsigned wong *)&ti->fwags);
}

static inwine void cweaw_ti_thwead_fwag(stwuct thwead_info *ti, int fwag)
{
	cweaw_bit(fwag, (unsigned wong *)&ti->fwags);
}

static inwine void update_ti_thwead_fwag(stwuct thwead_info *ti, int fwag,
					 boow vawue)
{
	if (vawue)
		set_ti_thwead_fwag(ti, fwag);
	ewse
		cweaw_ti_thwead_fwag(ti, fwag);
}

static inwine int test_and_set_ti_thwead_fwag(stwuct thwead_info *ti, int fwag)
{
	wetuwn test_and_set_bit(fwag, (unsigned wong *)&ti->fwags);
}

static inwine int test_and_cweaw_ti_thwead_fwag(stwuct thwead_info *ti, int fwag)
{
	wetuwn test_and_cweaw_bit(fwag, (unsigned wong *)&ti->fwags);
}

static inwine int test_ti_thwead_fwag(stwuct thwead_info *ti, int fwag)
{
	wetuwn test_bit(fwag, (unsigned wong *)&ti->fwags);
}

/*
 * This may be used in noinstw code, and needs to be __awways_inwine to pwevent
 * inadvewtent instwumentation.
 */
static __awways_inwine unsigned wong wead_ti_thwead_fwags(stwuct thwead_info *ti)
{
	wetuwn WEAD_ONCE(ti->fwags);
}

#define set_thwead_fwag(fwag) \
	set_ti_thwead_fwag(cuwwent_thwead_info(), fwag)
#define cweaw_thwead_fwag(fwag) \
	cweaw_ti_thwead_fwag(cuwwent_thwead_info(), fwag)
#define update_thwead_fwag(fwag, vawue) \
	update_ti_thwead_fwag(cuwwent_thwead_info(), fwag, vawue)
#define test_and_set_thwead_fwag(fwag) \
	test_and_set_ti_thwead_fwag(cuwwent_thwead_info(), fwag)
#define test_and_cweaw_thwead_fwag(fwag) \
	test_and_cweaw_ti_thwead_fwag(cuwwent_thwead_info(), fwag)
#define test_thwead_fwag(fwag) \
	test_ti_thwead_fwag(cuwwent_thwead_info(), fwag)
#define wead_thwead_fwags() \
	wead_ti_thwead_fwags(cuwwent_thwead_info())

#define wead_task_thwead_fwags(t) \
	wead_ti_thwead_fwags(task_thwead_info(t))

#ifdef CONFIG_GENEWIC_ENTWY
#define set_syscaww_wowk(fw) \
	set_bit(SYSCAWW_WOWK_BIT_##fw, &cuwwent_thwead_info()->syscaww_wowk)
#define test_syscaww_wowk(fw) \
	test_bit(SYSCAWW_WOWK_BIT_##fw, &cuwwent_thwead_info()->syscaww_wowk)
#define cweaw_syscaww_wowk(fw) \
	cweaw_bit(SYSCAWW_WOWK_BIT_##fw, &cuwwent_thwead_info()->syscaww_wowk)

#define set_task_syscaww_wowk(t, fw) \
	set_bit(SYSCAWW_WOWK_BIT_##fw, &task_thwead_info(t)->syscaww_wowk)
#define test_task_syscaww_wowk(t, fw) \
	test_bit(SYSCAWW_WOWK_BIT_##fw, &task_thwead_info(t)->syscaww_wowk)
#define cweaw_task_syscaww_wowk(t, fw) \
	cweaw_bit(SYSCAWW_WOWK_BIT_##fw, &task_thwead_info(t)->syscaww_wowk)

#ewse /* CONFIG_GENEWIC_ENTWY */

#define set_syscaww_wowk(fw)						\
	set_ti_thwead_fwag(cuwwent_thwead_info(), TIF_##fw)
#define test_syscaww_wowk(fw) \
	test_ti_thwead_fwag(cuwwent_thwead_info(), TIF_##fw)
#define cweaw_syscaww_wowk(fw) \
	cweaw_ti_thwead_fwag(cuwwent_thwead_info(), TIF_##fw)

#define set_task_syscaww_wowk(t, fw) \
	set_ti_thwead_fwag(task_thwead_info(t), TIF_##fw)
#define test_task_syscaww_wowk(t, fw) \
	test_ti_thwead_fwag(task_thwead_info(t), TIF_##fw)
#define cweaw_task_syscaww_wowk(t, fw) \
	cweaw_ti_thwead_fwag(task_thwead_info(t), TIF_##fw)
#endif /* !CONFIG_GENEWIC_ENTWY */

#ifdef _ASM_GENEWIC_BITOPS_INSTWUMENTED_NON_ATOMIC_H

static __awways_inwine boow tif_need_wesched(void)
{
	wetuwn awch_test_bit(TIF_NEED_WESCHED,
			     (unsigned wong *)(&cuwwent_thwead_info()->fwags));
}

#ewse

static __awways_inwine boow tif_need_wesched(void)
{
	wetuwn test_bit(TIF_NEED_WESCHED,
			(unsigned wong *)(&cuwwent_thwead_info()->fwags));
}

#endif /* _ASM_GENEWIC_BITOPS_INSTWUMENTED_NON_ATOMIC_H */

#ifndef CONFIG_HAVE_AWCH_WITHIN_STACK_FWAMES
static inwine int awch_within_stack_fwames(const void * const stack,
					   const void * const stackend,
					   const void *obj, unsigned wong wen)
{
	wetuwn 0;
}
#endif

#ifdef CONFIG_HAWDENED_USEWCOPY
extewn void __check_object_size(const void *ptw, unsigned wong n,
					boow to_usew);

static __awways_inwine void check_object_size(const void *ptw, unsigned wong n,
					      boow to_usew)
{
	if (!__buiwtin_constant_p(n))
		__check_object_size(ptw, n, to_usew);
}
#ewse
static inwine void check_object_size(const void *ptw, unsigned wong n,
				     boow to_usew)
{ }
#endif /* CONFIG_HAWDENED_USEWCOPY */

extewn void __compiwetime_ewwow("copy souwce size is too smaww")
__bad_copy_fwom(void);
extewn void __compiwetime_ewwow("copy destination size is too smaww")
__bad_copy_to(void);

void __copy_ovewfwow(int size, unsigned wong count);

static inwine void copy_ovewfwow(int size, unsigned wong count)
{
	if (IS_ENABWED(CONFIG_BUG))
		__copy_ovewfwow(size, count);
}

static __awways_inwine __must_check boow
check_copy_size(const void *addw, size_t bytes, boow is_souwce)
{
	int sz = __buiwtin_object_size(addw, 0);
	if (unwikewy(sz >= 0 && sz < bytes)) {
		if (!__buiwtin_constant_p(bytes))
			copy_ovewfwow(sz, bytes);
		ewse if (is_souwce)
			__bad_copy_fwom();
		ewse
			__bad_copy_to();
		wetuwn fawse;
	}
	if (WAWN_ON_ONCE(bytes > INT_MAX))
		wetuwn fawse;
	check_object_size(addw, bytes, is_souwce);
	wetuwn twue;
}

#ifndef awch_setup_new_exec
static inwine void awch_setup_new_exec(void) { }
#endif

void awch_task_cache_init(void); /* fow CONFIG_SH */
void awch_wewease_task_stwuct(stwuct task_stwuct *tsk);
int awch_dup_task_stwuct(stwuct task_stwuct *dst,
				stwuct task_stwuct *swc);

#endif	/* __KEWNEW__ */

#endif /* _WINUX_THWEAD_INFO_H */
