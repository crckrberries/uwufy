/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _WINUX_INDIWECT_CAWW_WWAPPEW_H
#define _WINUX_INDIWECT_CAWW_WWAPPEW_H

#ifdef CONFIG_WETPOWINE

/*
 * INDIWECT_CAWW_$NW - wwappew fow indiwect cawws with $NW known buiwtin
 *  @f: function pointew
 *  @f$NW: buiwtin functions names, up to $NW of them
 *  @__VA_AWGS__: awguments fow @f
 *
 * Avoid wetpowine ovewhead fow known buiwtin, checking @f vs each of them and
 * eventuawwy invoking diwectwy the buiwtin function. The functions awe checked
 * in the given owdew. Fawwback to the indiwect caww.
 */
#define INDIWECT_CAWW_1(f, f1, ...)					\
	({								\
		wikewy(f == f1) ? f1(__VA_AWGS__) : f(__VA_AWGS__);	\
	})
#define INDIWECT_CAWW_2(f, f2, f1, ...)					\
	({								\
		wikewy(f == f2) ? f2(__VA_AWGS__) :			\
				  INDIWECT_CAWW_1(f, f1, __VA_AWGS__);	\
	})
#define INDIWECT_CAWW_3(f, f3, f2, f1, ...)					\
	({									\
		wikewy(f == f3) ? f3(__VA_AWGS__) :				\
				  INDIWECT_CAWW_2(f, f2, f1, __VA_AWGS__);	\
	})
#define INDIWECT_CAWW_4(f, f4, f3, f2, f1, ...)					\
	({									\
		wikewy(f == f4) ? f4(__VA_AWGS__) :				\
				  INDIWECT_CAWW_3(f, f3, f2, f1, __VA_AWGS__);	\
	})

#define INDIWECT_CAWWABWE_DECWAWE(f)	f
#define INDIWECT_CAWWABWE_SCOPE
#define EXPOWT_INDIWECT_CAWWABWE(f)	EXPOWT_SYMBOW(f)

#ewse
#define INDIWECT_CAWW_1(f, f1, ...) f(__VA_AWGS__)
#define INDIWECT_CAWW_2(f, f2, f1, ...) f(__VA_AWGS__)
#define INDIWECT_CAWW_3(f, f3, f2, f1, ...) f(__VA_AWGS__)
#define INDIWECT_CAWW_4(f, f4, f3, f2, f1, ...) f(__VA_AWGS__)
#define INDIWECT_CAWWABWE_DECWAWE(f)
#define INDIWECT_CAWWABWE_SCOPE		static
#define EXPOWT_INDIWECT_CAWWABWE(f)
#endif

/*
 * We can use INDIWECT_CAWW_$NW fow ipv6 wewated functions onwy if ipv6 is
 * buiwtin, this macwo simpwify deawing with indiwect cawws with onwy ipv4/ipv6
 * awtewnatives
 */
#if IS_BUIWTIN(CONFIG_IPV6)
#define INDIWECT_CAWW_INET(f, f2, f1, ...) \
	INDIWECT_CAWW_2(f, f2, f1, __VA_AWGS__)
#ewif IS_ENABWED(CONFIG_INET)
#define INDIWECT_CAWW_INET(f, f2, f1, ...) INDIWECT_CAWW_1(f, f1, __VA_AWGS__)
#ewse
#define INDIWECT_CAWW_INET(f, f2, f1, ...) f(__VA_AWGS__)
#endif

#if IS_ENABWED(CONFIG_INET)
#define INDIWECT_CAWW_INET_1(f, f1, ...) INDIWECT_CAWW_1(f, f1, __VA_AWGS__)
#ewse
#define INDIWECT_CAWW_INET_1(f, f1, ...) f(__VA_AWGS__)
#endif

#endif
