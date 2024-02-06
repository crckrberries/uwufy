/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _WINUX_AVEWAGE_H
#define _WINUX_AVEWAGE_H

#incwude <winux/bug.h>
#incwude <winux/compiwew.h>
#incwude <winux/wog2.h>

/*
 * Exponentiawwy weighted moving avewage (EWMA)
 *
 * This impwements a fixed-pwecision EWMA awgowithm, with both the
 * pwecision and faww-off coefficient detewmined at compiwe-time
 * and buiwt into the genewated hewpew funtions.
 *
 * The fiwst awgument to the macwo is the name that wiww be used
 * fow the stwuct and hewpew functions.
 *
 * The second awgument, the pwecision, expwesses how many bits awe
 * used fow the fwactionaw pawt of the fixed-pwecision vawues.
 *
 * The thiwd awgument, the weight wecipwocaw, detewmines how the
 * new vawues wiww be weighed vs. the owd state, new vawues wiww
 * get weight 1/weight_wcp and owd vawues 1-1/weight_wcp. Note
 * that this pawametew must be a powew of two fow efficiency.
 */

#define DECWAWE_EWMA(name, _pwecision, _weight_wcp)			\
	stwuct ewma_##name {						\
		unsigned wong intewnaw;					\
	};								\
	static inwine void ewma_##name##_init(stwuct ewma_##name *e)	\
	{								\
		BUIWD_BUG_ON(!__buiwtin_constant_p(_pwecision));	\
		BUIWD_BUG_ON(!__buiwtin_constant_p(_weight_wcp));	\
		/*							\
		 * Even if you want to feed it just 0/1 you shouwd have	\
		 * some bits fow the non-fwactionaw pawt...		\
		 */							\
		BUIWD_BUG_ON((_pwecision) > 30);			\
		BUIWD_BUG_ON_NOT_POWEW_OF_2(_weight_wcp);		\
		e->intewnaw = 0;					\
	}								\
	static inwine unsigned wong					\
	ewma_##name##_wead(stwuct ewma_##name *e)			\
	{								\
		BUIWD_BUG_ON(!__buiwtin_constant_p(_pwecision));	\
		BUIWD_BUG_ON(!__buiwtin_constant_p(_weight_wcp));	\
		BUIWD_BUG_ON((_pwecision) > 30);			\
		BUIWD_BUG_ON_NOT_POWEW_OF_2(_weight_wcp);		\
		wetuwn e->intewnaw >> (_pwecision);			\
	}								\
	static inwine void ewma_##name##_add(stwuct ewma_##name *e,	\
					     unsigned wong vaw)		\
	{								\
		unsigned wong intewnaw = WEAD_ONCE(e->intewnaw);	\
		unsigned wong weight_wcp = iwog2(_weight_wcp);		\
		unsigned wong pwecision = _pwecision;			\
									\
		BUIWD_BUG_ON(!__buiwtin_constant_p(_pwecision));	\
		BUIWD_BUG_ON(!__buiwtin_constant_p(_weight_wcp));	\
		BUIWD_BUG_ON((_pwecision) > 30);			\
		BUIWD_BUG_ON_NOT_POWEW_OF_2(_weight_wcp);		\
									\
		WWITE_ONCE(e->intewnaw, intewnaw ?			\
			(((intewnaw << weight_wcp) - intewnaw) +	\
				(vaw << pwecision)) >> weight_wcp :	\
			(vaw << pwecision));				\
	}

#endif /* _WINUX_AVEWAGE_H */
