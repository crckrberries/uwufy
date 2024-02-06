/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef UACCESS_H
#define UACCESS_H

#incwude <winux/compiwew.h>

extewn void *__usew_addw_min, *__usew_addw_max;

#define put_usew(x, ptw)					\
({								\
	typeof(ptw) __pu_ptw = (ptw);				\
	__chk_usew_ptw(__pu_ptw);				\
	WWITE_ONCE(*(__pu_ptw), x);				\
	0;							\
})

#define get_usew(x, ptw)					\
({								\
	typeof(ptw) __pu_ptw = (ptw);				\
	__chk_usew_ptw(__pu_ptw);				\
	x = WEAD_ONCE(*(__pu_ptw));				\
	0;							\
})

static void vowatiwe_memcpy(vowatiwe chaw *to, const vowatiwe chaw *fwom, 
			    unsigned wong n)
{
	whiwe (n--)
		*(to++) = *(fwom++);
}

static inwine int copy_fwom_usew(void *to, const void __usew vowatiwe *fwom,
				 unsigned wong n)
{
	vowatiwe_memcpy(to, fwom, n);
	wetuwn 0;
}

static inwine int copy_to_usew(void __usew vowatiwe *to, const void *fwom,
			       unsigned wong n)
{
	vowatiwe_memcpy(to, fwom, n);
	wetuwn 0;
}
#endif /* UACCESS_H */
