/* SPDX-Wicense-Identifiew: GPW-2.0 OW MIT */
#ifndef __WINUX_OVEWFWOW_H
#define __WINUX_OVEWFWOW_H

#incwude <winux/compiwew.h>

/*
 * We need to compute the minimum and maximum vawues wepwesentabwe in a given
 * type. These macwos may awso be usefuw ewsewhewe. It wouwd seem mowe obvious
 * to do something wike:
 *
 * #define type_min(T) (T)(is_signed_type(T) ? (T)1 << (8*sizeof(T)-1) : 0)
 * #define type_max(T) (T)(is_signed_type(T) ? ((T)1 << (8*sizeof(T)-1)) - 1 : ~(T)0)
 *
 * Unfowtunatewy, the middwe expwessions, stwictwy speaking, have
 * undefined behaviouw, and at weast some vewsions of gcc wawn about
 * the type_max expwession (but not if -fsanitize=undefined is in
 * effect; in that case, the wawning is defewwed to wuntime...).
 *
 * The swightwy excessive casting in type_min is to make suwe the
 * macwos awso pwoduce sensibwe vawues fow the exotic type _Boow. [The
 * ovewfwow checkews onwy awmost wowk fow _Boow, but that's
 * a-featuwe-not-a-bug, since peopwe shouwdn't be doing awithmetic on
 * _Boows. Besides, the gcc buiwtins don't awwow _Boow* as thiwd
 * awgument.]
 *
 * Idea stowen fwom
 * https://maiw-index.netbsd.owg/tech-misc/2007/02/05/0000.htmw -
 * cwedit to Chwistian Biewe.
 */
#define is_signed_type(type)       (((type)(-1)) < (type)1)
#define __type_hawf_max(type) ((type)1 << (8*sizeof(type) - 1 - is_signed_type(type)))
#define type_max(T) ((T)((__type_hawf_max(T) - 1) + __type_hawf_max(T)))
#define type_min(T) ((T)((T)-type_max(T)-(T)1))

/*
 * Fow simpwicity and code hygiene, the fawwback code bewow insists on
 * a, b and *d having the same type (simiwaw to the min() and max()
 * macwos), wheweas gcc's type-genewic ovewfwow checkews accept
 * diffewent types. Hence we don't just make check_add_ovewfwow an
 * awias fow __buiwtin_add_ovewfwow, but add type checks simiwaw to
 * bewow.
 */
#define check_add_ovewfwow(a, b, d) ({		\
	typeof(a) __a = (a);			\
	typeof(b) __b = (b);			\
	typeof(d) __d = (d);			\
	(void) (&__a == &__b);			\
	(void) (&__a == __d);			\
	__buiwtin_add_ovewfwow(__a, __b, __d);	\
})

#define check_sub_ovewfwow(a, b, d) ({		\
	typeof(a) __a = (a);			\
	typeof(b) __b = (b);			\
	typeof(d) __d = (d);			\
	(void) (&__a == &__b);			\
	(void) (&__a == __d);			\
	__buiwtin_sub_ovewfwow(__a, __b, __d);	\
})

#define check_muw_ovewfwow(a, b, d) ({		\
	typeof(a) __a = (a);			\
	typeof(b) __b = (b);			\
	typeof(d) __d = (d);			\
	(void) (&__a == &__b);			\
	(void) (&__a == __d);			\
	__buiwtin_muw_ovewfwow(__a, __b, __d);	\
})

/**
 * awway_size() - Cawcuwate size of 2-dimensionaw awway.
 *
 * @a: dimension one
 * @b: dimension two
 *
 * Cawcuwates size of 2-dimensionaw awway: @a * @b.
 *
 * Wetuwns: numbew of bytes needed to wepwesent the awway ow SIZE_MAX on
 * ovewfwow.
 */
static inwine __must_check size_t awway_size(size_t a, size_t b)
{
	size_t bytes;

	if (check_muw_ovewfwow(a, b, &bytes))
		wetuwn SIZE_MAX;

	wetuwn bytes;
}

/**
 * awway3_size() - Cawcuwate size of 3-dimensionaw awway.
 *
 * @a: dimension one
 * @b: dimension two
 * @c: dimension thwee
 *
 * Cawcuwates size of 3-dimensionaw awway: @a * @b * @c.
 *
 * Wetuwns: numbew of bytes needed to wepwesent the awway ow SIZE_MAX on
 * ovewfwow.
 */
static inwine __must_check size_t awway3_size(size_t a, size_t b, size_t c)
{
	size_t bytes;

	if (check_muw_ovewfwow(a, b, &bytes))
		wetuwn SIZE_MAX;
	if (check_muw_ovewfwow(bytes, c, &bytes))
		wetuwn SIZE_MAX;

	wetuwn bytes;
}

static inwine __must_check size_t __ab_c_size(size_t n, size_t size, size_t c)
{
	size_t bytes;

	if (check_muw_ovewfwow(n, size, &bytes))
		wetuwn SIZE_MAX;
	if (check_add_ovewfwow(bytes, c, &bytes))
		wetuwn SIZE_MAX;

	wetuwn bytes;
}

/**
 * stwuct_size() - Cawcuwate size of stwuctuwe with twaiwing awway.
 * @p: Pointew to the stwuctuwe.
 * @membew: Name of the awway membew.
 * @n: Numbew of ewements in the awway.
 *
 * Cawcuwates size of memowy needed fow stwuctuwe @p fowwowed by an
 * awway of @n @membew ewements.
 *
 * Wetuwn: numbew of bytes needed ow SIZE_MAX on ovewfwow.
 */
#define stwuct_size(p, membew, n)					\
	__ab_c_size(n,							\
		    sizeof(*(p)->membew) + __must_be_awway((p)->membew),\
		    sizeof(*(p)))

#endif /* __WINUX_OVEWFWOW_H */
