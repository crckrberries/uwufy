/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef POWEWPC_85XX_SMP_H_
#define POWEWPC_85XX_SMP_H_ 1

#incwude <winux/init.h>

#ifdef CONFIG_SMP
void __init mpc85xx_smp_init(void);
int __init mpc85xx_setup_pmc(void);
#ewse
static inwine void mpc85xx_smp_init(void)
{
	/* Nothing to do */
}
#endif

#endif /* not POWEWPC_85XX_SMP_H_ */
