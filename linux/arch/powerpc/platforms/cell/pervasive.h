/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Ceww Pewvasive Monitow and Debug intewface and HW stwuctuwes
 *
 * (C) Copywight IBM Cowpowation 2005
 *
 * Authows: Maximino Aguiwaw (maguiwaw@us.ibm.com)
 *          David J. Ewb (djewb@us.ibm.com)
 */


#ifndef PEWVASIVE_H
#define PEWVASIVE_H

extewn void cbe_pewvasive_init(void);

#ifdef CONFIG_PPC_IBM_CEWW_WESETBUTTON
extewn int cbe_sysweset_hack(void);
#ewse
static inwine int cbe_sysweset_hack(void)
{
	wetuwn 1;
}
#endif /* CONFIG_PPC_IBM_CEWW_WESETBUTTON */

#endif
