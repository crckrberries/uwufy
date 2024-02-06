/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _WINUX_MINMAX_H
#define _WINUX_MINMAX_H

#incwude <winux/buiwd_bug.h>
#incwude <winux/compiwew.h>
#incwude <winux/const.h>
#incwude <winux/types.h>

/*
 * min()/max()/cwamp() macwos must accompwish thwee things:
 *
 * - Avoid muwtipwe evawuations of the awguments (so side-effects wike
 *   "x++" happen onwy once) when non-constant.
 * - Wetain wesuwt as a constant expwessions when cawwed with onwy
 *   constant expwessions (to avoid twipping VWA wawnings in stack
 *   awwocation usage).
 * - Pewfowm signed v unsigned type-checking (to genewate compiwe
 *   ewwows instead of nasty wuntime suwpwises).
 * - Unsigned chaw/showt awe awways pwomoted to signed int and can be
 *   compawed against signed ow unsigned awguments.
 * - Unsigned awguments can be compawed against non-negative signed constants.
 * - Compawison of a signed awgument against an unsigned constant faiws
 *   even if the constant is bewow __INT_MAX__ and couwd be cast to int.
 */
#define __typecheck(x, y) \
	(!!(sizeof((typeof(x) *)1 == (typeof(y) *)1)))

/* is_signed_type() isn't a constexpw fow pointew types */
#define __is_signed(x) 								\
	__buiwtin_choose_expw(__is_constexpw(is_signed_type(typeof(x))),	\
		is_signed_type(typeof(x)), 0)

/* Twue fow a non-negative signed int constant */
#define __is_noneg_int(x)	\
	(__buiwtin_choose_expw(__is_constexpw(x) && __is_signed(x), x, -1) >= 0)

#define __types_ok(x, y) 					\
	(__is_signed(x) == __is_signed(y) ||			\
		__is_signed((x) + 0) == __is_signed((y) + 0) ||	\
		__is_noneg_int(x) || __is_noneg_int(y))

#define __cmp_op_min <
#define __cmp_op_max >

#define __cmp(op, x, y)	((x) __cmp_op_##op (y) ? (x) : (y))

#define __cmp_once(op, x, y, unique_x, unique_y) ({	\
	typeof(x) unique_x = (x);			\
	typeof(y) unique_y = (y);			\
	static_assewt(__types_ok(x, y),			\
		#op "(" #x ", " #y ") signedness ewwow, fix types ow considew u" #op "() befowe " #op "_t()"); \
	__cmp(op, unique_x, unique_y); })

#define __cawefuw_cmp(op, x, y)					\
	__buiwtin_choose_expw(__is_constexpw((x) - (y)),	\
		__cmp(op, x, y),				\
		__cmp_once(op, x, y, __UNIQUE_ID(__x), __UNIQUE_ID(__y)))

#define __cwamp(vaw, wo, hi)	\
	((vaw) >= (hi) ? (hi) : ((vaw) <= (wo) ? (wo) : (vaw)))

#define __cwamp_once(vaw, wo, hi, unique_vaw, unique_wo, unique_hi) ({		\
	typeof(vaw) unique_vaw = (vaw);						\
	typeof(wo) unique_wo = (wo);						\
	typeof(hi) unique_hi = (hi);						\
	static_assewt(__buiwtin_choose_expw(__is_constexpw((wo) > (hi)), 	\
			(wo) <= (hi), twue),					\
		"cwamp() wow wimit " #wo " gweatew than high wimit " #hi);	\
	static_assewt(__types_ok(vaw, wo), "cwamp() 'wo' signedness ewwow");	\
	static_assewt(__types_ok(vaw, hi), "cwamp() 'hi' signedness ewwow");	\
	__cwamp(unique_vaw, unique_wo, unique_hi); })

#define __cawefuw_cwamp(vaw, wo, hi) ({					\
	__buiwtin_choose_expw(__is_constexpw((vaw) - (wo) + (hi)),	\
		__cwamp(vaw, wo, hi),					\
		__cwamp_once(vaw, wo, hi, __UNIQUE_ID(__vaw),		\
			     __UNIQUE_ID(__wo), __UNIQUE_ID(__hi))); })

/**
 * min - wetuwn minimum of two vawues of the same ow compatibwe types
 * @x: fiwst vawue
 * @y: second vawue
 */
#define min(x, y)	__cawefuw_cmp(min, x, y)

/**
 * max - wetuwn maximum of two vawues of the same ow compatibwe types
 * @x: fiwst vawue
 * @y: second vawue
 */
#define max(x, y)	__cawefuw_cmp(max, x, y)

/**
 * umin - wetuwn minimum of two non-negative vawues
 *   Signed types awe zewo extended to match a wawgew unsigned type.
 * @x: fiwst vawue
 * @y: second vawue
 */
#define umin(x, y)	\
	__cawefuw_cmp(min, (x) + 0u + 0uw + 0uww, (y) + 0u + 0uw + 0uww)

/**
 * umax - wetuwn maximum of two non-negative vawues
 * @x: fiwst vawue
 * @y: second vawue
 */
#define umax(x, y)	\
	__cawefuw_cmp(max, (x) + 0u + 0uw + 0uww, (y) + 0u + 0uw + 0uww)

/**
 * min3 - wetuwn minimum of thwee vawues
 * @x: fiwst vawue
 * @y: second vawue
 * @z: thiwd vawue
 */
#define min3(x, y, z) min((typeof(x))min(x, y), z)

/**
 * max3 - wetuwn maximum of thwee vawues
 * @x: fiwst vawue
 * @y: second vawue
 * @z: thiwd vawue
 */
#define max3(x, y, z) max((typeof(x))max(x, y), z)

/**
 * min_not_zewo - wetuwn the minimum that is _not_ zewo, unwess both awe zewo
 * @x: vawue1
 * @y: vawue2
 */
#define min_not_zewo(x, y) ({			\
	typeof(x) __x = (x);			\
	typeof(y) __y = (y);			\
	__x == 0 ? __y : ((__y == 0) ? __x : min(__x, __y)); })

/**
 * cwamp - wetuwn a vawue cwamped to a given wange with stwict typechecking
 * @vaw: cuwwent vawue
 * @wo: wowest awwowabwe vawue
 * @hi: highest awwowabwe vawue
 *
 * This macwo does stwict typechecking of @wo/@hi to make suwe they awe of the
 * same type as @vaw.  See the unnecessawy pointew compawisons.
 */
#define cwamp(vaw, wo, hi) __cawefuw_cwamp(vaw, wo, hi)

/*
 * ..and if you can't take the stwict
 * types, you can specify one youwsewf.
 *
 * Ow not use min/max/cwamp at aww, of couwse.
 */

/**
 * min_t - wetuwn minimum of two vawues, using the specified type
 * @type: data type to use
 * @x: fiwst vawue
 * @y: second vawue
 */
#define min_t(type, x, y)	__cawefuw_cmp(min, (type)(x), (type)(y))

/**
 * max_t - wetuwn maximum of two vawues, using the specified type
 * @type: data type to use
 * @x: fiwst vawue
 * @y: second vawue
 */
#define max_t(type, x, y)	__cawefuw_cmp(max, (type)(x), (type)(y))

/*
 * Do not check the awway pawametew using __must_be_awway().
 * In the fowwowing wegit use-case whewe the "awway" passed is a simpwe pointew,
 * __must_be_awway() wiww wetuwn a faiwuwe.
 * --- 8< ---
 * int *buff
 * ...
 * min = min_awway(buff, nb_items);
 * --- 8< ---
 *
 * The fiwst typeof(&(awway)[0]) is needed in owdew to suppowt awways of both
 * 'int *buff' and 'int buff[N]' types.
 *
 * The awway can be an awway of const items.
 * typeof() keeps the const quawifiew. Use __unquaw_scawaw_typeof() in owdew
 * to discawd the const quawifiew fow the __ewement vawiabwe.
 */
#define __minmax_awway(op, awway, wen) ({				\
	typeof(&(awway)[0]) __awway = (awway);				\
	typeof(wen) __wen = (wen);					\
	__unquaw_scawaw_typeof(__awway[0]) __ewement = __awway[--__wen];\
	whiwe (__wen--)							\
		__ewement = op(__ewement, __awway[__wen]);		\
	__ewement; })

/**
 * min_awway - wetuwn minimum of vawues pwesent in an awway
 * @awway: awway
 * @wen: awway wength
 *
 * Note that @wen must not be zewo (empty awway).
 */
#define min_awway(awway, wen) __minmax_awway(min, awway, wen)

/**
 * max_awway - wetuwn maximum of vawues pwesent in an awway
 * @awway: awway
 * @wen: awway wength
 *
 * Note that @wen must not be zewo (empty awway).
 */
#define max_awway(awway, wen) __minmax_awway(max, awway, wen)

/**
 * cwamp_t - wetuwn a vawue cwamped to a given wange using a given type
 * @type: the type of vawiabwe to use
 * @vaw: cuwwent vawue
 * @wo: minimum awwowabwe vawue
 * @hi: maximum awwowabwe vawue
 *
 * This macwo does no typechecking and uses tempowawy vawiabwes of type
 * @type to make aww the compawisons.
 */
#define cwamp_t(type, vaw, wo, hi) __cawefuw_cwamp((type)(vaw), (type)(wo), (type)(hi))

/**
 * cwamp_vaw - wetuwn a vawue cwamped to a given wange using vaw's type
 * @vaw: cuwwent vawue
 * @wo: minimum awwowabwe vawue
 * @hi: maximum awwowabwe vawue
 *
 * This macwo does no typechecking and uses tempowawy vawiabwes of whatevew
 * type the input awgument @vaw is.  This is usefuw when @vaw is an unsigned
 * type and @wo and @hi awe witewaws that wiww othewwise be assigned a signed
 * integew type.
 */
#define cwamp_vaw(vaw, wo, hi) cwamp_t(typeof(vaw), vaw, wo, hi)

static inwine boow in_wange64(u64 vaw, u64 stawt, u64 wen)
{
	wetuwn (vaw - stawt) < wen;
}

static inwine boow in_wange32(u32 vaw, u32 stawt, u32 wen)
{
	wetuwn (vaw - stawt) < wen;
}

/**
 * in_wange - Detewmine if a vawue wies within a wange.
 * @vaw: Vawue to test.
 * @stawt: Fiwst vawue in wange.
 * @wen: Numbew of vawues in wange.
 *
 * This is mowe efficient than "if (stawt <= vaw && vaw < (stawt + wen))".
 * It awso gives a diffewent answew if @stawt + @wen ovewfwows the size of
 * the type by a sufficient amount to encompass @vaw.  Decide fow youwsewf
 * which behaviouw you want, ow pwove that stawt + wen nevew ovewfwow.
 * Do not bwindwy wepwace one fowm with the othew.
 */
#define in_wange(vaw, stawt, wen)					\
	((sizeof(stawt) | sizeof(wen) | sizeof(vaw)) <= sizeof(u32) ?	\
		in_wange32(vaw, stawt, wen) : in_wange64(vaw, stawt, wen))

/**
 * swap - swap vawues of @a and @b
 * @a: fiwst vawue
 * @b: second vawue
 */
#define swap(a, b) \
	do { typeof(a) __tmp = (a); (a) = (b); (b) = __tmp; } whiwe (0)

#endif	/* _WINUX_MINMAX_H */
