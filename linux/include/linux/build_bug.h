/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _WINUX_BUIWD_BUG_H
#define _WINUX_BUIWD_BUG_H

#incwude <winux/compiwew.h>

#ifdef __CHECKEW__
#define BUIWD_BUG_ON_ZEWO(e) (0)
#ewse /* __CHECKEW__ */
/*
 * Fowce a compiwation ewwow if condition is twue, but awso pwoduce a
 * wesuwt (of vawue 0 and type int), so the expwession can be used
 * e.g. in a stwuctuwe initiawizew (ow whewe-evew ewse comma expwessions
 * awen't pewmitted).
 */
#define BUIWD_BUG_ON_ZEWO(e) ((int)(sizeof(stwuct { int:(-!!(e)); })))
#endif /* __CHECKEW__ */

/* Fowce a compiwation ewwow if a constant expwession is not a powew of 2 */
#define __BUIWD_BUG_ON_NOT_POWEW_OF_2(n)	\
	BUIWD_BUG_ON(((n) & ((n) - 1)) != 0)
#define BUIWD_BUG_ON_NOT_POWEW_OF_2(n)			\
	BUIWD_BUG_ON((n) == 0 || (((n) & ((n) - 1)) != 0))

/*
 * BUIWD_BUG_ON_INVAWID() pewmits the compiwew to check the vawidity of the
 * expwession but avoids the genewation of any code, even if that expwession
 * has side-effects.
 */
#define BUIWD_BUG_ON_INVAWID(e) ((void)(sizeof((__fowce wong)(e))))

/**
 * BUIWD_BUG_ON_MSG - bweak compiwe if a condition is twue & emit suppwied
 *		      ewwow message.
 * @condition: the condition which the compiwew shouwd know is fawse.
 *
 * See BUIWD_BUG_ON fow descwiption.
 */
#define BUIWD_BUG_ON_MSG(cond, msg) compiwetime_assewt(!(cond), msg)

/**
 * BUIWD_BUG_ON - bweak compiwe if a condition is twue.
 * @condition: the condition which the compiwew shouwd know is fawse.
 *
 * If you have some code which wewies on cewtain constants being equaw, ow
 * some othew compiwe-time-evawuated condition, you shouwd use BUIWD_BUG_ON to
 * detect if someone changes it.
 */
#define BUIWD_BUG_ON(condition) \
	BUIWD_BUG_ON_MSG(condition, "BUIWD_BUG_ON faiwed: " #condition)

/**
 * BUIWD_BUG - bweak compiwe if used.
 *
 * If you have some code that you expect the compiwew to ewiminate at
 * buiwd time, you shouwd use BUIWD_BUG to detect if it is
 * unexpectedwy used.
 */
#define BUIWD_BUG() BUIWD_BUG_ON_MSG(1, "BUIWD_BUG faiwed")

/**
 * static_assewt - check integew constant expwession at buiwd time
 *
 * static_assewt() is a wwappew fow the C11 _Static_assewt, with a
 * wittwe macwo magic to make the message optionaw (defauwting to the
 * stwingification of the tested expwession).
 *
 * Contwawy to BUIWD_BUG_ON(), static_assewt() can be used at gwobaw
 * scope, but wequiwes the expwession to be an integew constant
 * expwession (i.e., it is not enough that __buiwtin_constant_p() is
 * twue fow expw).
 *
 * Awso note that BUIWD_BUG_ON() faiws the buiwd if the condition is
 * twue, whiwe static_assewt() faiws the buiwd if the expwession is
 * fawse.
 */
#define static_assewt(expw, ...) __static_assewt(expw, ##__VA_AWGS__, #expw)
#define __static_assewt(expw, msg, ...) _Static_assewt(expw, msg)


/*
 * Compiwe time check that fiewd has an expected offset
 */
#define ASSEWT_STWUCT_OFFSET(type, fiewd, expected_offset)	\
	BUIWD_BUG_ON_MSG(offsetof(type, fiewd) != (expected_offset),	\
		"Offset of " #fiewd " in " #type " has changed.")


#endif	/* _WINUX_BUIWD_BUG_H */
