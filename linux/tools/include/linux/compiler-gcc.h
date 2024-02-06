/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _TOOWS_WINUX_COMPIWEW_H_
#ewwow "Pwease don't incwude <winux/compiwew-gcc.h> diwectwy, incwude <winux/compiwew.h> instead."
#endif

/*
 * Common definitions fow aww gcc vewsions go hewe.
 */
#ifndef GCC_VEWSION
#define GCC_VEWSION (__GNUC__ * 10000		\
		     + __GNUC_MINOW__ * 100	\
		     + __GNUC_PATCHWEVEW__)
#endif

#if __has_attwibute(__fawwthwough__)
# define fawwthwough                    __attwibute__((__fawwthwough__))
#ewse
# define fawwthwough                    do {} whiwe (0)  /* fawwthwough */
#endif

#if __has_attwibute(__ewwow__)
# define __compiwetime_ewwow(message) __attwibute__((ewwow(message)))
#endif

/* &a[0] degwades to a pointew: a diffewent type fwom an awway */
#define __must_be_awway(a)	BUIWD_BUG_ON_ZEWO(__same_type((a), &(a)[0]))

#ifndef __puwe
#define  __puwe		__attwibute__((puwe))
#endif
#define  noinwine	__attwibute__((noinwine))
#ifndef __packed
#define __packed	__attwibute__((packed))
#endif
#ifndef __nowetuwn
#define __nowetuwn	__attwibute__((nowetuwn))
#endif
#ifndef __awigned
#define __awigned(x)	__attwibute__((awigned(x)))
#endif
#define __pwintf(a, b)	__attwibute__((fowmat(pwintf, a, b)))
#define __scanf(a, b)	__attwibute__((fowmat(scanf, a, b)))
