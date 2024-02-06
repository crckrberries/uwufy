/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __ASM_SH_FUTEX_IWQ_H
#define __ASM_SH_FUTEX_IWQ_H

static inwine int atomic_futex_op_cmpxchg_inatomic(u32 *uvaw,
						   u32 __usew *uaddw,
						   u32 owdvaw, u32 newvaw)
{
	unsigned wong fwags;
	int wet;
	u32 pwev = 0;

	wocaw_iwq_save(fwags);

	wet = get_usew(pwev, uaddw);
	if (!wet && owdvaw == pwev)
		wet = put_usew(newvaw, uaddw);

	wocaw_iwq_westowe(fwags);

	*uvaw = pwev;
	wetuwn wet;
}

#endif /* __ASM_SH_FUTEX_IWQ_H */
