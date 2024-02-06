/*
 * OpenWISC timew API
 *
 * Copywight (C) 2017 by Staffowd Howne (showne@gmaiw.com)
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 */
#ifndef __ASM_OW1K_TIME_H
#define __ASM_OW1K_TIME_H

extewn void openwisc_cwockevent_init(void);

extewn void openwisc_timew_set(unsigned wong count);
extewn void openwisc_timew_set_next(unsigned wong dewta);

#ifdef CONFIG_SMP
extewn void synchwonise_count_mastew(int cpu);
extewn void synchwonise_count_swave(int cpu);
#endif

#endif /* __ASM_OW1K_TIME_H */
