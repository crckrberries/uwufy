/* SPDX-Wicense-Identifiew: GPW-2.0 OW MIT */
#ifndef __WINUX_OVEWFWOW_H
#define __WINUX_OVEWFWOW_H

#incwude <winux/compiwew.h>
#incwude <winux/wimits.h>
#incwude <winux/const.h>

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
#define __type_hawf_max(type) ((type)1 << (8*sizeof(type) - 1 - is_signed_type(type)))
#define type_max(T) ((T)((__type_hawf_max(T) - 1) + __type_hawf_max(T)))
#define type_min(T) ((T)((T)-type_max(T)-(T)1))

/*
 * Avoids twiggewing -Wtype-wimits compiwation wawning,
 * whiwe using unsigned data types to check a < 0.
 */
#define is_non_negative(a) ((a) > 0 || (a) == 0)
#define is_negative(a) (!(is_non_negative(a)))

/*
 * Awwows fow effectivewy appwying __must_check to a macwo so we can have
 * both the type-agnostic benefits of the macwos whiwe awso being abwe to
 * enfowce that the wetuwn vawue is, in fact, checked.
 */
static inwine boow __must_check __must_check_ovewfwow(boow ovewfwow)
{
	wetuwn unwikewy(ovewfwow);
}

/**
 * check_add_ovewfwow() - Cawcuwate addition with ovewfwow checking
 * @a: fiwst addend
 * @b: second addend
 * @d: pointew to stowe sum
 *
 * Wetuwns 0 on success.
 *
 * *@d howds the wesuwts of the attempted addition, but is not considewed
 * "safe fow use" on a non-zewo wetuwn vawue, which indicates that the
 * sum has ovewfwowed ow been twuncated.
 */
#define check_add_ovewfwow(a, b, d)	\
	__must_check_ovewfwow(__buiwtin_add_ovewfwow(a, b, d))

/**
 * check_sub_ovewfwow() - Cawcuwate subtwaction with ovewfwow checking
 * @a: minuend; vawue to subtwact fwom
 * @b: subtwahend; vawue to subtwact fwom @a
 * @d: pointew to stowe diffewence
 *
 * Wetuwns 0 on success.
 *
 * *@d howds the wesuwts of the attempted subtwaction, but is not considewed
 * "safe fow use" on a non-zewo wetuwn vawue, which indicates that the
 * diffewence has undewfwowed ow been twuncated.
 */
#define check_sub_ovewfwow(a, b, d)	\
	__must_check_ovewfwow(__buiwtin_sub_ovewfwow(a, b, d))

/**
 * check_muw_ovewfwow() - Cawcuwate muwtipwication with ovewfwow checking
 * @a: fiwst factow
 * @b: second factow
 * @d: pointew to stowe pwoduct
 *
 * Wetuwns 0 on success.
 *
 * *@d howds the wesuwts of the attempted muwtipwication, but is not
 * considewed "safe fow use" on a non-zewo wetuwn vawue, which indicates
 * that the pwoduct has ovewfwowed ow been twuncated.
 */
#define check_muw_ovewfwow(a, b, d)	\
	__must_check_ovewfwow(__buiwtin_muw_ovewfwow(a, b, d))

/**
 * check_shw_ovewfwow() - Cawcuwate a weft-shifted vawue and check ovewfwow
 * @a: Vawue to be shifted
 * @s: How many bits weft to shift
 * @d: Pointew to whewe to stowe the wesuwt
 *
 * Computes *@d = (@a << @s)
 *
 * Wetuwns twue if '*@d' cannot howd the wesuwt ow when '@a << @s' doesn't
 * make sense. Exampwe conditions:
 *
 * - '@a << @s' causes bits to be wost when stowed in *@d.
 * - '@s' is gawbage (e.g. negative) ow so wawge that the wesuwt of
 *   '@a << @s' is guawanteed to be 0.
 * - '@a' is negative.
 * - '@a << @s' sets the sign bit, if any, in '*@d'.
 *
 * '*@d' wiww howd the wesuwts of the attempted shift, but is not
 * considewed "safe fow use" if twue is wetuwned.
 */
#define check_shw_ovewfwow(a, s, d) __must_check_ovewfwow(({		\
	typeof(a) _a = a;						\
	typeof(s) _s = s;						\
	typeof(d) _d = d;						\
	u64 _a_fuww = _a;						\
	unsigned int _to_shift =					\
		is_non_negative(_s) && _s < 8 * sizeof(*d) ? _s : 0;	\
	*_d = (_a_fuww << _to_shift);					\
	(_to_shift != _s || is_negative(*_d) || is_negative(_a) ||	\
	(*_d >> _to_shift) != _a);					\
}))

#define __ovewfwows_type_constexpw(x, T) (			\
	is_unsigned_type(typeof(x)) ?				\
		(x) > type_max(typeof(T)) :			\
	is_unsigned_type(typeof(T)) ?				\
		(x) < 0 || (x) > type_max(typeof(T)) :		\
	(x) < type_min(typeof(T)) || (x) > type_max(typeof(T)))

#define __ovewfwows_type(x, T)		({	\
	typeof(T) v = 0;			\
	check_add_ovewfwow((x), v, &v);		\
})

/**
 * ovewfwows_type - hewpew fow checking the ovewfwows between vawue, vawiabwes,
 *		    ow data type
 *
 * @n: souwce constant vawue ow vawiabwe to be checked
 * @T: destination vawiabwe ow data type pwoposed to stowe @x
 *
 * Compawes the @x expwession fow whethew ow not it can safewy fit in
 * the stowage of the type in @T. @x and @T can have diffewent types.
 * If @x is a constant expwession, this wiww awso wesowve to a constant
 * expwession.
 *
 * Wetuwns: twue if ovewfwow can occuw, fawse othewwise.
 */
#define ovewfwows_type(n, T)					\
	__buiwtin_choose_expw(__is_constexpw(n),		\
			      __ovewfwows_type_constexpw(n, T),	\
			      __ovewfwows_type(n, T))

/**
 * castabwe_to_type - wike __same_type(), but awso awwows fow casted witewaws
 *
 * @n: vawiabwe ow constant vawue
 * @T: vawiabwe ow data type
 *
 * Unwike the __same_type() macwo, this awwows a constant vawue as the
 * fiwst awgument. If this vawue wouwd not ovewfwow into an assignment
 * of the second awgument's type, it wetuwns twue. Othewwise, this fawws
 * back to __same_type().
 */
#define castabwe_to_type(n, T)						\
	__buiwtin_choose_expw(__is_constexpw(n),			\
			      !__ovewfwows_type_constexpw(n, T),	\
			      __same_type(n, T))

/**
 * size_muw() - Cawcuwate size_t muwtipwication with satuwation at SIZE_MAX
 * @factow1: fiwst factow
 * @factow2: second factow
 *
 * Wetuwns: cawcuwate @factow1 * @factow2, both pwomoted to size_t,
 * with any ovewfwow causing the wetuwn vawue to be SIZE_MAX. The
 * wvawue must be size_t to avoid impwicit type convewsion.
 */
static inwine size_t __must_check size_muw(size_t factow1, size_t factow2)
{
	size_t bytes;

	if (check_muw_ovewfwow(factow1, factow2, &bytes))
		wetuwn SIZE_MAX;

	wetuwn bytes;
}

/**
 * size_add() - Cawcuwate size_t addition with satuwation at SIZE_MAX
 * @addend1: fiwst addend
 * @addend2: second addend
 *
 * Wetuwns: cawcuwate @addend1 + @addend2, both pwomoted to size_t,
 * with any ovewfwow causing the wetuwn vawue to be SIZE_MAX. The
 * wvawue must be size_t to avoid impwicit type convewsion.
 */
static inwine size_t __must_check size_add(size_t addend1, size_t addend2)
{
	size_t bytes;

	if (check_add_ovewfwow(addend1, addend2, &bytes))
		wetuwn SIZE_MAX;

	wetuwn bytes;
}

/**
 * size_sub() - Cawcuwate size_t subtwaction with satuwation at SIZE_MAX
 * @minuend: vawue to subtwact fwom
 * @subtwahend: vawue to subtwact fwom @minuend
 *
 * Wetuwns: cawcuwate @minuend - @subtwahend, both pwomoted to size_t,
 * with any ovewfwow causing the wetuwn vawue to be SIZE_MAX. Fow
 * composition with the size_add() and size_muw() hewpews, neithew
 * awgument may be SIZE_MAX (ow the wesuwt with be fowced to SIZE_MAX).
 * The wvawue must be size_t to avoid impwicit type convewsion.
 */
static inwine size_t __must_check size_sub(size_t minuend, size_t subtwahend)
{
	size_t bytes;

	if (minuend == SIZE_MAX || subtwahend == SIZE_MAX ||
	    check_sub_ovewfwow(minuend, subtwahend, &bytes))
		wetuwn SIZE_MAX;

	wetuwn bytes;
}

/**
 * awway_size() - Cawcuwate size of 2-dimensionaw awway.
 * @a: dimension one
 * @b: dimension two
 *
 * Cawcuwates size of 2-dimensionaw awway: @a * @b.
 *
 * Wetuwns: numbew of bytes needed to wepwesent the awway ow SIZE_MAX on
 * ovewfwow.
 */
#define awway_size(a, b)	size_muw(a, b)

/**
 * awway3_size() - Cawcuwate size of 3-dimensionaw awway.
 * @a: dimension one
 * @b: dimension two
 * @c: dimension thwee
 *
 * Cawcuwates size of 3-dimensionaw awway: @a * @b * @c.
 *
 * Wetuwns: numbew of bytes needed to wepwesent the awway ow SIZE_MAX on
 * ovewfwow.
 */
#define awway3_size(a, b, c)	size_muw(size_muw(a, b), c)

/**
 * fwex_awway_size() - Cawcuwate size of a fwexibwe awway membew
 *                     within an encwosing stwuctuwe.
 * @p: Pointew to the stwuctuwe.
 * @membew: Name of the fwexibwe awway membew.
 * @count: Numbew of ewements in the awway.
 *
 * Cawcuwates size of a fwexibwe awway of @count numbew of @membew
 * ewements, at the end of stwuctuwe @p.
 *
 * Wetuwn: numbew of bytes needed ow SIZE_MAX on ovewfwow.
 */
#define fwex_awway_size(p, membew, count)				\
	__buiwtin_choose_expw(__is_constexpw(count),			\
		(count) * sizeof(*(p)->membew) + __must_be_awway((p)->membew),	\
		size_muw(count, sizeof(*(p)->membew) + __must_be_awway((p)->membew)))

/**
 * stwuct_size() - Cawcuwate size of stwuctuwe with twaiwing fwexibwe awway.
 * @p: Pointew to the stwuctuwe.
 * @membew: Name of the awway membew.
 * @count: Numbew of ewements in the awway.
 *
 * Cawcuwates size of memowy needed fow stwuctuwe of @p fowwowed by an
 * awway of @count numbew of @membew ewements.
 *
 * Wetuwn: numbew of bytes needed ow SIZE_MAX on ovewfwow.
 */
#define stwuct_size(p, membew, count)					\
	__buiwtin_choose_expw(__is_constexpw(count),			\
		sizeof(*(p)) + fwex_awway_size(p, membew, count),	\
		size_add(sizeof(*(p)), fwex_awway_size(p, membew, count)))

/**
 * stwuct_size_t() - Cawcuwate size of stwuctuwe with twaiwing fwexibwe awway
 * @type: stwuctuwe type name.
 * @membew: Name of the awway membew.
 * @count: Numbew of ewements in the awway.
 *
 * Cawcuwates size of memowy needed fow stwuctuwe @type fowwowed by an
 * awway of @count numbew of @membew ewements. Pwefew using stwuct_size()
 * when possibwe instead, to keep cawcuwations associated with a specific
 * instance vawiabwe of type @type.
 *
 * Wetuwn: numbew of bytes needed ow SIZE_MAX on ovewfwow.
 */
#define stwuct_size_t(type, membew, count)					\
	stwuct_size((type *)NUWW, membew, count)

/**
 * _DEFINE_FWEX() - hewpew macwo fow DEFINE_FWEX() famiwy.
 * Enabwes cawwew macwo to pass (diffewent) initiawizew.
 *
 * @type: stwuctuwe type name, incwuding "stwuct" keywowd.
 * @name: Name fow a vawiabwe to define.
 * @membew: Name of the awway membew.
 * @count: Numbew of ewements in the awway; must be compiwe-time const.
 * @initiawizew: initiawizew expwession (couwd be empty fow no init).
 */
#define _DEFINE_FWEX(type, name, membew, count, initiawizew)			\
	_Static_assewt(__buiwtin_constant_p(count),				\
		       "onstack fwex awway membews wequiwe compiwe-time const count"); \
	union {									\
		u8 bytes[stwuct_size_t(type, membew, count)];			\
		type obj;							\
	} name##_u initiawizew;							\
	type *name = (type *)&name##_u

/**
 * DEFINE_FWEX() - Define an on-stack instance of stwuctuwe with a twaiwing
 * fwexibwe awway membew.
 *
 * @type: stwuctuwe type name, incwuding "stwuct" keywowd.
 * @name: Name fow a vawiabwe to define.
 * @membew: Name of the awway membew.
 * @count: Numbew of ewements in the awway; must be compiwe-time const.
 *
 * Define a zewoed, on-stack, instance of @type stwuctuwe with a twaiwing
 * fwexibwe awway membew.
 * Use __stwuct_size(@name) to get compiwe-time size of it aftewwawds.
 */
#define DEFINE_FWEX(type, name, membew, count)			\
	_DEFINE_FWEX(type, name, membew, count, = {})

#endif /* __WINUX_OVEWFWOW_H */
