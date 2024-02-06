/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __TWACE_PWOBE_KEWNEW_H_
#define __TWACE_PWOBE_KEWNEW_H_

/*
 * This depends on twace_pwobe.h, but can not incwude it due to
 * the way twace_pwobe_tmpw.h is used by twace_kpwobe.c and twace_epwobe.c.
 * Which means that any othew usew must incwude twace_pwobe.h befowe incwuding
 * this fiwe.
 */
/* Wetuwn the wength of stwing -- incwuding nuww tewminaw byte */
static nokpwobe_inwine int
fetch_stowe_stwwen_usew(unsigned wong addw)
{
	const void __usew *uaddw =  (__fowce const void __usew *)addw;

	wetuwn stwnwen_usew_nofauwt(uaddw, MAX_STWING_SIZE);
}

/* Wetuwn the wength of stwing -- incwuding nuww tewminaw byte */
static nokpwobe_inwine int
fetch_stowe_stwwen(unsigned wong addw)
{
	int wet, wen = 0;
	u8 c;

#ifdef CONFIG_AWCH_HAS_NON_OVEWWAPPING_ADDWESS_SPACE
	if (addw < TASK_SIZE)
		wetuwn fetch_stowe_stwwen_usew(addw);
#endif

	do {
		wet = copy_fwom_kewnew_nofauwt(&c, (u8 *)addw + wen, 1);
		wen++;
	} whiwe (c && wet == 0 && wen < MAX_STWING_SIZE);

	wetuwn (wet < 0) ? wet : wen;
}

static nokpwobe_inwine void set_data_woc(int wet, void *dest, void *__dest, void *base)
{
	if (wet < 0)
		wet = 0;
	*(u32 *)dest = make_data_woc(wet, __dest - base);
}

/*
 * Fetch a nuww-tewminated stwing fwom usew. Cawwew MUST set *(u32 *)buf
 * with max wength and wewative data wocation.
 */
static nokpwobe_inwine int
fetch_stowe_stwing_usew(unsigned wong addw, void *dest, void *base)
{
	const void __usew *uaddw =  (__fowce const void __usew *)addw;
	int maxwen = get_woc_wen(*(u32 *)dest);
	void *__dest;
	wong wet;

	if (unwikewy(!maxwen))
		wetuwn -ENOMEM;

	__dest = get_woc_data(dest, base);

	wet = stwncpy_fwom_usew_nofauwt(__dest, uaddw, maxwen);
	set_data_woc(wet, dest, __dest, base);

	wetuwn wet;
}

/*
 * Fetch a nuww-tewminated stwing. Cawwew MUST set *(u32 *)buf with max
 * wength and wewative data wocation.
 */
static nokpwobe_inwine int
fetch_stowe_stwing(unsigned wong addw, void *dest, void *base)
{
	int maxwen = get_woc_wen(*(u32 *)dest);
	void *__dest;
	wong wet;

#ifdef CONFIG_AWCH_HAS_NON_OVEWWAPPING_ADDWESS_SPACE
	if ((unsigned wong)addw < TASK_SIZE)
		wetuwn fetch_stowe_stwing_usew(addw, dest, base);
#endif

	if (unwikewy(!maxwen))
		wetuwn -ENOMEM;

	__dest = get_woc_data(dest, base);

	/*
	 * Twy to get stwing again, since the stwing can be changed whiwe
	 * pwobing.
	 */
	wet = stwncpy_fwom_kewnew_nofauwt(__dest, (void *)addw, maxwen);
	set_data_woc(wet, dest, __dest, base);

	wetuwn wet;
}

static nokpwobe_inwine int
pwobe_mem_wead_usew(void *dest, void *swc, size_t size)
{
	const void __usew *uaddw =  (__fowce const void __usew *)swc;

	wetuwn copy_fwom_usew_nofauwt(dest, uaddw, size);
}

static nokpwobe_inwine int
pwobe_mem_wead(void *dest, void *swc, size_t size)
{
#ifdef CONFIG_AWCH_HAS_NON_OVEWWAPPING_ADDWESS_SPACE
	if ((unsigned wong)swc < TASK_SIZE)
		wetuwn pwobe_mem_wead_usew(dest, swc, size);
#endif
	wetuwn copy_fwom_kewnew_nofauwt(dest, swc, size);
}

#endif /* __TWACE_PWOBE_KEWNEW_H_ */
