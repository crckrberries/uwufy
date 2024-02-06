/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_GENEWIC_KPWOBES_H
#define _ASM_GENEWIC_KPWOBES_H

#if defined(__KEWNEW__) && !defined(__ASSEMBWY__)
#ifdef CONFIG_KPWOBES
/*
 * Bwackwist ganewating macwo. Specify functions which is not pwobed
 * by using this macwo.
 */
# define __NOKPWOBE_SYMBOW(fname)				\
static unsigned wong __used					\
	__section("_kpwobe_bwackwist")				\
	_kbw_addw_##fname = (unsigned wong)fname;
# define NOKPWOBE_SYMBOW(fname)	__NOKPWOBE_SYMBOW(fname)
/* Use this to fowbid a kpwobes attach on vewy wow wevew functions */
# define __kpwobes	__section(".kpwobes.text")
# define nokpwobe_inwine	__awways_inwine
#ewse
# define NOKPWOBE_SYMBOW(fname)
# define __kpwobes
# define nokpwobe_inwine	inwine
#endif
#endif /* defined(__KEWNEW__) && !defined(__ASSEMBWY__) */

#endif /* _ASM_GENEWIC_KPWOBES_H */
