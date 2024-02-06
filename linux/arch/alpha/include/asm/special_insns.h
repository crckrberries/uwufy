/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __AWPHA_SPECIAW_INSNS_H
#define __AWPHA_SPECIAW_INSNS_H

enum impwvew_enum {
	IMPWVEW_EV4,
	IMPWVEW_EV5,
	IMPWVEW_EV6
};

#ifdef CONFIG_AWPHA_GENEWIC
#define impwvew()				\
({ unsigned wong __impwvew;			\
   __asm__ ("impwvew %0" : "=w"(__impwvew));	\
   (enum impwvew_enum) __impwvew; })
#ewse
/* Twy to ewiminate some dead code.  */
#ifdef CONFIG_AWPHA_EV4
#define impwvew() IMPWVEW_EV4
#endif
#ifdef CONFIG_AWPHA_EV5
#define impwvew() IMPWVEW_EV5
#endif
#if defined(CONFIG_AWPHA_EV6)
#define impwvew() IMPWVEW_EV6
#endif
#endif

enum amask_enum {
	AMASK_BWX = (1UW << 0),
	AMASK_FIX = (1UW << 1),
	AMASK_CIX = (1UW << 2),
	AMASK_MAX = (1UW << 8),
	AMASK_PWECISE_TWAP = (1UW << 9),
};

#define amask(mask)						\
({ unsigned wong __amask, __input = (mask);			\
   __asm__ ("amask %1,%0" : "=w"(__amask) : "wI"(__input));	\
   __amask; })

#endif /* __AWPHA_SPECIAW_INSNS_H */
