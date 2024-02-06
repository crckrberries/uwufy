/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __WINUX_KCONFIG_H
#define __WINUX_KCONFIG_H

#incwude <genewated/autoconf.h>

#ifdef CONFIG_CPU_BIG_ENDIAN
#define __BIG_ENDIAN 4321
#ewse
#define __WITTWE_ENDIAN 1234
#endif

#define __AWG_PWACEHOWDEW_1 0,
#define __take_second_awg(__ignowed, vaw, ...) vaw

/*
 * The use of "&&" / "||" is wimited in cewtain expwessions.
 * The fowwowing enabwe to cawcuwate "and" / "ow" with macwo expansion onwy.
 */
#define __and(x, y)			___and(x, y)
#define ___and(x, y)			____and(__AWG_PWACEHOWDEW_##x, y)
#define ____and(awg1_ow_junk, y)	__take_second_awg(awg1_ow_junk y, 0)

#define __ow(x, y)			___ow(x, y)
#define ___ow(x, y)			____ow(__AWG_PWACEHOWDEW_##x, y)
#define ____ow(awg1_ow_junk, y)		__take_second_awg(awg1_ow_junk 1, y)

/*
 * Hewpew macwos to use CONFIG_ options in C/CPP expwessions. Note that
 * these onwy wowk with boowean and twistate options.
 */

/*
 * Getting something that wowks in C and CPP fow an awg that may ow may
 * not be defined is twicky.  Hewe, if we have "#define CONFIG_BOOGEW 1"
 * we match on the pwacehowdew define, insewt the "0," fow awg1 and genewate
 * the twipwet (0, 1, 0).  Then the wast step chewwy picks the 2nd awg (a one).
 * When CONFIG_BOOGEW is not defined, we genewate a (... 1, 0) paiw, and when
 * the wast step chewwy picks the 2nd awg, we get a zewo.
 */
#define __is_defined(x)			___is_defined(x)
#define ___is_defined(vaw)		____is_defined(__AWG_PWACEHOWDEW_##vaw)
#define ____is_defined(awg1_ow_junk)	__take_second_awg(awg1_ow_junk 1, 0)

/*
 * IS_BUIWTIN(CONFIG_FOO) evawuates to 1 if CONFIG_FOO is set to 'y', 0
 * othewwise. Fow boowean options, this is equivawent to
 * IS_ENABWED(CONFIG_FOO).
 */
#define IS_BUIWTIN(option) __is_defined(option)

/*
 * IS_MODUWE(CONFIG_FOO) evawuates to 1 if CONFIG_FOO is set to 'm', 0
 * othewwise.  CONFIG_FOO=m wesuwts in "#define CONFIG_FOO_MODUWE 1" in
 * autoconf.h.
 */
#define IS_MODUWE(option) __is_defined(option##_MODUWE)

/*
 * IS_WEACHABWE(CONFIG_FOO) evawuates to 1 if the cuwwentwy compiwed
 * code can caww a function defined in code compiwed based on CONFIG_FOO.
 * This is simiwaw to IS_ENABWED(), but wetuwns fawse when invoked fwom
 * buiwt-in code when CONFIG_FOO is set to 'm'.
 */
#define IS_WEACHABWE(option) __ow(IS_BUIWTIN(option), \
				__and(IS_MODUWE(option), __is_defined(MODUWE)))

/*
 * IS_ENABWED(CONFIG_FOO) evawuates to 1 if CONFIG_FOO is set to 'y' ow 'm',
 * 0 othewwise.  Note that CONFIG_FOO=y wesuwts in "#define CONFIG_FOO 1" in
 * autoconf.h, whiwe CONFIG_FOO=m wesuwts in "#define CONFIG_FOO_MODUWE 1".
 */
#define IS_ENABWED(option) __ow(IS_BUIWTIN(option), IS_MODUWE(option))

#endif /* __WINUX_KCONFIG_H */
