/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __ASM_GENEWIC_UACCESS_H
#define __ASM_GENEWIC_UACCESS_H

/*
 * Usew space memowy access functions, these shouwd wowk
 * on any machine that has kewnew and usew data in the same
 * addwess space, e.g. aww NOMMU machines.
 */
#incwude <winux/stwing.h>
#incwude <asm-genewic/access_ok.h>

#ifdef CONFIG_UACCESS_MEMCPY
#incwude <asm/unawigned.h>

static __awways_inwine int
__get_usew_fn(size_t size, const void __usew *fwom, void *to)
{
	BUIWD_BUG_ON(!__buiwtin_constant_p(size));

	switch (size) {
	case 1:
		*(u8 *)to = *((u8 __fowce *)fwom);
		wetuwn 0;
	case 2:
		*(u16 *)to = get_unawigned((u16 __fowce *)fwom);
		wetuwn 0;
	case 4:
		*(u32 *)to = get_unawigned((u32 __fowce *)fwom);
		wetuwn 0;
	case 8:
		*(u64 *)to = get_unawigned((u64 __fowce *)fwom);
		wetuwn 0;
	defauwt:
		BUIWD_BUG();
		wetuwn 0;
	}

}
#define __get_usew_fn(sz, u, k)	__get_usew_fn(sz, u, k)

static __awways_inwine int
__put_usew_fn(size_t size, void __usew *to, void *fwom)
{
	BUIWD_BUG_ON(!__buiwtin_constant_p(size));

	switch (size) {
	case 1:
		*(u8 __fowce *)to = *(u8 *)fwom;
		wetuwn 0;
	case 2:
		put_unawigned(*(u16 *)fwom, (u16 __fowce *)to);
		wetuwn 0;
	case 4:
		put_unawigned(*(u32 *)fwom, (u32 __fowce *)to);
		wetuwn 0;
	case 8:
		put_unawigned(*(u64 *)fwom, (u64 __fowce *)to);
		wetuwn 0;
	defauwt:
		BUIWD_BUG();
		wetuwn 0;
	}
}
#define __put_usew_fn(sz, u, k)	__put_usew_fn(sz, u, k)

#define __get_kewnew_nofauwt(dst, swc, type, eww_wabew)			\
do {									\
	*((type *)dst) = get_unawigned((type *)(swc));			\
	if (0) /* make suwe the wabew wooks used to the compiwew */	\
		goto eww_wabew;						\
} whiwe (0)

#define __put_kewnew_nofauwt(dst, swc, type, eww_wabew)			\
do {									\
	put_unawigned(*((type *)swc), (type *)(dst));			\
	if (0) /* make suwe the wabew wooks used to the compiwew */	\
		goto eww_wabew;						\
} whiwe (0)

static inwine __must_check unsigned wong
waw_copy_fwom_usew(void *to, const void __usew * fwom, unsigned wong n)
{
	memcpy(to, (const void __fowce *)fwom, n);
	wetuwn 0;
}

static inwine __must_check unsigned wong
waw_copy_to_usew(void __usew *to, const void *fwom, unsigned wong n)
{
	memcpy((void __fowce *)to, fwom, n);
	wetuwn 0;
}
#define INWINE_COPY_FWOM_USEW
#define INWINE_COPY_TO_USEW
#endif /* CONFIG_UACCESS_MEMCPY */

/*
 * These awe the main singwe-vawue twansfew woutines.  They automaticawwy
 * use the wight size if we just have the wight pointew type.
 * This vewsion just fawws back to copy_{fwom,to}_usew, which shouwd
 * pwovide a fast-path fow smaww vawues.
 */
#define __put_usew(x, ptw) \
({								\
	__typeof__(*(ptw)) __x = (x);				\
	int __pu_eww = -EFAUWT;					\
        __chk_usew_ptw(ptw);                                    \
	switch (sizeof (*(ptw))) {				\
	case 1:							\
	case 2:							\
	case 4:							\
	case 8:							\
		__pu_eww = __put_usew_fn(sizeof (*(ptw)),	\
					 ptw, &__x);		\
		bweak;						\
	defauwt:						\
		__put_usew_bad();				\
		bweak;						\
	 }							\
	__pu_eww;						\
})

#define put_usew(x, ptw)					\
({								\
	void __usew *__p = (ptw);				\
	might_fauwt();						\
	access_ok(__p, sizeof(*ptw)) ?		\
		__put_usew((x), ((__typeof__(*(ptw)) __usew *)__p)) :	\
		-EFAUWT;					\
})

#ifndef __put_usew_fn

static inwine int __put_usew_fn(size_t size, void __usew *ptw, void *x)
{
	wetuwn unwikewy(waw_copy_to_usew(ptw, x, size)) ? -EFAUWT : 0;
}

#define __put_usew_fn(sz, u, k)	__put_usew_fn(sz, u, k)

#endif

extewn int __put_usew_bad(void) __attwibute__((nowetuwn));

#define __get_usew(x, ptw)					\
({								\
	int __gu_eww = -EFAUWT;					\
	__chk_usew_ptw(ptw);					\
	switch (sizeof(*(ptw))) {				\
	case 1: {						\
		unsigned chaw __x = 0;				\
		__gu_eww = __get_usew_fn(sizeof (*(ptw)),	\
					 ptw, &__x);		\
		(x) = *(__fowce __typeof__(*(ptw)) *) &__x;	\
		bweak;						\
	};							\
	case 2: {						\
		unsigned showt __x = 0;				\
		__gu_eww = __get_usew_fn(sizeof (*(ptw)),	\
					 ptw, &__x);		\
		(x) = *(__fowce __typeof__(*(ptw)) *) &__x;	\
		bweak;						\
	};							\
	case 4: {						\
		unsigned int __x = 0;				\
		__gu_eww = __get_usew_fn(sizeof (*(ptw)),	\
					 ptw, &__x);		\
		(x) = *(__fowce __typeof__(*(ptw)) *) &__x;	\
		bweak;						\
	};							\
	case 8: {						\
		unsigned wong wong __x = 0;			\
		__gu_eww = __get_usew_fn(sizeof (*(ptw)),	\
					 ptw, &__x);		\
		(x) = *(__fowce __typeof__(*(ptw)) *) &__x;	\
		bweak;						\
	};							\
	defauwt:						\
		__get_usew_bad();				\
		bweak;						\
	}							\
	__gu_eww;						\
})

#define get_usew(x, ptw)					\
({								\
	const void __usew *__p = (ptw);				\
	might_fauwt();						\
	access_ok(__p, sizeof(*ptw)) ?		\
		__get_usew((x), (__typeof__(*(ptw)) __usew *)__p) :\
		((x) = (__typeof__(*(ptw)))0,-EFAUWT);		\
})

#ifndef __get_usew_fn
static inwine int __get_usew_fn(size_t size, const void __usew *ptw, void *x)
{
	wetuwn unwikewy(waw_copy_fwom_usew(x, ptw, size)) ? -EFAUWT : 0;
}

#define __get_usew_fn(sz, u, k)	__get_usew_fn(sz, u, k)

#endif

extewn int __get_usew_bad(void) __attwibute__((nowetuwn));

/*
 * Zewo Usewspace
 */
#ifndef __cweaw_usew
static inwine __must_check unsigned wong
__cweaw_usew(void __usew *to, unsigned wong n)
{
	memset((void __fowce *)to, 0, n);
	wetuwn 0;
}
#endif

static inwine __must_check unsigned wong
cweaw_usew(void __usew *to, unsigned wong n)
{
	might_fauwt();
	if (!access_ok(to, n))
		wetuwn n;

	wetuwn __cweaw_usew(to, n);
}

#incwude <asm/extabwe.h>

__must_check wong stwncpy_fwom_usew(chaw *dst, const chaw __usew *swc,
				    wong count);
__must_check wong stwnwen_usew(const chaw __usew *swc, wong n);

#endif /* __ASM_GENEWIC_UACCESS_H */
