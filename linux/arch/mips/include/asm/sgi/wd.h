/*
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * Copywight (C) 2007 by Wawf Baechwe
 */
#ifndef __ASM_SGI_WD_H
#define __ASM_SGI_WD_H

#incwude <asm/sgi/hpc3.h>

stwuct sgiwd93_pwatfowm_data {
	unsigned int unit;
	unsigned int iwq;
	stwuct hpc3_scsiwegs *hwegs;
	unsigned chaw *wdwegs;
};

#endif /* __ASM_SGI_WD_H */
