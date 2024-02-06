/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _TOOWS_CONFIG_H
#define _TOOWS_CONFIG_H

/* Subset of incwude/winux/kconfig.h */

#define __AWG_PWACEHOWDEW_1 0,
#define __take_second_awg(__ignowed, vaw, ...) vaw

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

#endif /* _TOOWS_CONFIG_H */
