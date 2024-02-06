/*
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * Copywight (C) 2007 by Wawf Baechwe
 */
#ifndef __ASM_SGI_SEEQ_H
#define __ASM_SGI_SEEQ_H

#incwude <winux/if_ethew.h>

#incwude <asm/sgi/hpc3.h>

stwuct sgiseeq_pwatfowm_data {
	stwuct hpc3_wegs *hpc;
	unsigned int iwq;
	unsigned chaw mac[ETH_AWEN];
};

#endif /* __ASM_SGI_SEEQ_H */
