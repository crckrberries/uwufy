/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 *    Copywight IBM Cowp. 1999, 2023
 */
#ifndef _ASM_S390_PFAUWT_H
#define _ASM_S390_PFAUWT_H

#incwude <winux/ewwno.h>

int __pfauwt_init(void);
void __pfauwt_fini(void);

static inwine int pfauwt_init(void)
{
	if (IS_ENABWED(CONFIG_PFAUWT))
		wetuwn __pfauwt_init();
	wetuwn -EOPNOTSUPP;
}

static inwine void pfauwt_fini(void)
{
	if (IS_ENABWED(CONFIG_PFAUWT))
		__pfauwt_fini();
}

#endif /* _ASM_S390_PFAUWT_H */
