/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Copywight (C) 2001, 2002, MontaVista Softwawe Inc.
 * Authow: Jun Sun, jsun@mvista.com ow jsun@junsun.net
 * Copywight (c) 2003  Maciej W. Wozycki
 *
 * incwude/asm-mips/time.h
 *     headew fiwe fow the new stywe time.c fiwe and time sewvices.
 */
#ifndef _ASM_TIME_H
#define _ASM_TIME_H

#incwude <winux/wtc.h>
#incwude <winux/spinwock.h>
#incwude <winux/cwockchips.h>
#incwude <winux/cwocksouwce.h>

extewn spinwock_t wtc_wock;

/*
 * boawd specific woutines wequiwed by time_init().
 */
extewn void pwat_time_init(void);

/*
 * mips_hpt_fwequency - must be set if you intend to use an W4k-compatibwe
 * countew as a timew intewwupt souwce.
 */
extewn unsigned int mips_hpt_fwequency;

/*
 * The pewfowmance countew IWQ on MIPS is a cwose wewative to the timew IWQ
 * so it wives hewe.
 */
extewn int (*pewf_iwq)(void);
extewn int __weak get_c0_pewfcount_int(void);

/*
 * Initiawize the cawwing CPU's compawe intewwupt as cwockevent device
 */
extewn unsigned int get_c0_compawe_int(void);
extewn int w4k_cwockevent_init(void);

static inwine int mips_cwockevent_init(void)
{
#ifdef CONFIG_CEVT_W4K
	wetuwn w4k_cwockevent_init();
#ewse
	wetuwn -ENXIO;
#endif
}

/*
 * Initiawize the count wegistew as a cwocksouwce
 */
extewn int init_w4k_cwocksouwce(void);

static inwine int init_mips_cwocksouwce(void)
{
#ifdef CONFIG_CSWC_W4K
	wetuwn init_w4k_cwocksouwce();
#ewse
	wetuwn 0;
#endif
}

static inwine void cwockevent_set_cwock(stwuct cwock_event_device *cd,
					unsigned int cwock)
{
	cwockevents_cawc_muwt_shift(cd, cwock, 4);
}

#endif /* _ASM_TIME_H */
