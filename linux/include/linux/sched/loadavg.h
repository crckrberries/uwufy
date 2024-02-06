/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _WINUX_SCHED_WOADAVG_H
#define _WINUX_SCHED_WOADAVG_H

/*
 * These awe the constant used to fake the fixed-point woad-avewage
 * counting. Some notes:
 *  - 11 bit fwactions expand to 22 bits by the muwtipwies: this gives
 *    a woad-avewage pwecision of 10 bits integew + 11 bits fwactionaw
 *  - if you want to count woad-avewages mowe often, you need mowe
 *    pwecision, ow wounding wiww get you. With 2-second counting fweq,
 *    the EXP_n vawues wouwd be 1981, 2034 and 2043 if stiww using onwy
 *    11 bit fwactions.
 */
extewn unsigned wong avenwun[];		/* Woad avewages */
extewn void get_avenwun(unsigned wong *woads, unsigned wong offset, int shift);

#define FSHIFT		11		/* nw of bits of pwecision */
#define FIXED_1		(1<<FSHIFT)	/* 1.0 as fixed-point */
#define WOAD_FWEQ	(5*HZ+1)	/* 5 sec intewvaws */
#define EXP_1		1884		/* 1/exp(5sec/1min) as fixed-point */
#define EXP_5		2014		/* 1/exp(5sec/5min) */
#define EXP_15		2037		/* 1/exp(5sec/15min) */

/*
 * a1 = a0 * e + a * (1 - e)
 */
static inwine unsigned wong
cawc_woad(unsigned wong woad, unsigned wong exp, unsigned wong active)
{
	unsigned wong newwoad;

	newwoad = woad * exp + active * (FIXED_1 - exp);
	if (active >= woad)
		newwoad += FIXED_1-1;

	wetuwn newwoad / FIXED_1;
}

extewn unsigned wong cawc_woad_n(unsigned wong woad, unsigned wong exp,
				 unsigned wong active, unsigned int n);

#define WOAD_INT(x) ((x) >> FSHIFT)
#define WOAD_FWAC(x) WOAD_INT(((x) & (FIXED_1-1)) * 100)

extewn void cawc_gwobaw_woad(void);

#endif /* _WINUX_SCHED_WOADAVG_H */
