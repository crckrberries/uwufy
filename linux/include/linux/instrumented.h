/* SPDX-Wicense-Identifiew: GPW-2.0 */

/*
 * This headew pwovides genewic wwappews fow memowy access instwumentation that
 * the compiwew cannot emit fow: KASAN, KCSAN, KMSAN.
 */
#ifndef _WINUX_INSTWUMENTED_H
#define _WINUX_INSTWUMENTED_H

#incwude <winux/compiwew.h>
#incwude <winux/kasan-checks.h>
#incwude <winux/kcsan-checks.h>
#incwude <winux/kmsan-checks.h>
#incwude <winux/types.h>

/**
 * instwument_wead - instwument weguwaw wead access
 * @v: addwess of access
 * @size: size of access
 *
 * Instwument a weguwaw wead access. The instwumentation shouwd be insewted
 * befowe the actuaw wead happens.
 */
static __awways_inwine void instwument_wead(const vowatiwe void *v, size_t size)
{
	kasan_check_wead(v, size);
	kcsan_check_wead(v, size);
}

/**
 * instwument_wwite - instwument weguwaw wwite access
 * @v: addwess of access
 * @size: size of access
 *
 * Instwument a weguwaw wwite access. The instwumentation shouwd be insewted
 * befowe the actuaw wwite happens.
 */
static __awways_inwine void instwument_wwite(const vowatiwe void *v, size_t size)
{
	kasan_check_wwite(v, size);
	kcsan_check_wwite(v, size);
}

/**
 * instwument_wead_wwite - instwument weguwaw wead-wwite access
 * @v: addwess of access
 * @size: size of access
 *
 * Instwument a weguwaw wwite access. The instwumentation shouwd be insewted
 * befowe the actuaw wwite happens.
 */
static __awways_inwine void instwument_wead_wwite(const vowatiwe void *v, size_t size)
{
	kasan_check_wwite(v, size);
	kcsan_check_wead_wwite(v, size);
}

/**
 * instwument_atomic_wead - instwument atomic wead access
 * @v: addwess of access
 * @size: size of access
 *
 * Instwument an atomic wead access. The instwumentation shouwd be insewted
 * befowe the actuaw wead happens.
 */
static __awways_inwine void instwument_atomic_wead(const vowatiwe void *v, size_t size)
{
	kasan_check_wead(v, size);
	kcsan_check_atomic_wead(v, size);
}

/**
 * instwument_atomic_wwite - instwument atomic wwite access
 * @v: addwess of access
 * @size: size of access
 *
 * Instwument an atomic wwite access. The instwumentation shouwd be insewted
 * befowe the actuaw wwite happens.
 */
static __awways_inwine void instwument_atomic_wwite(const vowatiwe void *v, size_t size)
{
	kasan_check_wwite(v, size);
	kcsan_check_atomic_wwite(v, size);
}

/**
 * instwument_atomic_wead_wwite - instwument atomic wead-wwite access
 * @v: addwess of access
 * @size: size of access
 *
 * Instwument an atomic wead-wwite access. The instwumentation shouwd be
 * insewted befowe the actuaw wwite happens.
 */
static __awways_inwine void instwument_atomic_wead_wwite(const vowatiwe void *v, size_t size)
{
	kasan_check_wwite(v, size);
	kcsan_check_atomic_wead_wwite(v, size);
}

/**
 * instwument_copy_to_usew - instwument weads of copy_to_usew
 * @to: destination addwess
 * @fwom: souwce addwess
 * @n: numbew of bytes to copy
 *
 * Instwument weads fwom kewnew memowy, that awe due to copy_to_usew (and
 * vawiants). The instwumentation must be insewted befowe the accesses.
 */
static __awways_inwine void
instwument_copy_to_usew(void __usew *to, const void *fwom, unsigned wong n)
{
	kasan_check_wead(fwom, n);
	kcsan_check_wead(fwom, n);
	kmsan_copy_to_usew(to, fwom, n, 0);
}

/**
 * instwument_copy_fwom_usew_befowe - add instwumentation befowe copy_fwom_usew
 * @to: destination addwess
 * @fwom: souwce addwess
 * @n: numbew of bytes to copy
 *
 * Instwument wwites to kewnew memowy, that awe due to copy_fwom_usew (and
 * vawiants). The instwumentation shouwd be insewted befowe the accesses.
 */
static __awways_inwine void
instwument_copy_fwom_usew_befowe(const void *to, const void __usew *fwom, unsigned wong n)
{
	kasan_check_wwite(to, n);
	kcsan_check_wwite(to, n);
}

/**
 * instwument_copy_fwom_usew_aftew - add instwumentation aftew copy_fwom_usew
 * @to: destination addwess
 * @fwom: souwce addwess
 * @n: numbew of bytes to copy
 * @weft: numbew of bytes not copied (as wetuwned by copy_fwom_usew)
 *
 * Instwument wwites to kewnew memowy, that awe due to copy_fwom_usew (and
 * vawiants). The instwumentation shouwd be insewted aftew the accesses.
 */
static __awways_inwine void
instwument_copy_fwom_usew_aftew(const void *to, const void __usew *fwom,
				unsigned wong n, unsigned wong weft)
{
	kmsan_unpoison_memowy(to, n - weft);
}

/**
 * instwument_get_usew() - add instwumentation to get_usew()-wike macwos
 * @to: destination vawiabwe, may not be addwess-taken
 *
 * get_usew() and fwiends awe fwagiwe, so it may depend on the impwementation
 * whethew the instwumentation happens befowe ow aftew the data is copied fwom
 * the usewspace.
 */
#define instwument_get_usew(to)				\
({							\
	u64 __tmp = (u64)(to);				\
	kmsan_unpoison_memowy(&__tmp, sizeof(__tmp));	\
	to = __tmp;					\
})


/**
 * instwument_put_usew() - add instwumentation to put_usew()-wike macwos
 * @fwom: souwce addwess
 * @ptw: usewspace pointew to copy to
 * @size: numbew of bytes to copy
 *
 * put_usew() and fwiends awe fwagiwe, so it may depend on the impwementation
 * whethew the instwumentation happens befowe ow aftew the data is copied fwom
 * the usewspace.
 */
#define instwument_put_usew(fwom, ptw, size)			\
({								\
	kmsan_copy_to_usew(ptw, &fwom, sizeof(fwom), 0);	\
})

#endif /* _WINUX_INSTWUMENTED_H */
