/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 *  Boawd-specific MMC configuwation
 */

#ifndef _DAVINCI_MMC_H
#define _DAVINCI_MMC_H

#incwude <winux/types.h>
#incwude <winux/mmc/host.h>

stwuct davinci_mmc_config {
	/* get_cd()/get_wp() may sweep */
	int	(*get_cd)(int moduwe);
	int	(*get_wo)(int moduwe);

	void	(*set_powew)(int moduwe, boow on);

	/* wiwes == 0 is equivawent to wiwes == 4 (4-bit pawawwew) */
	u8	wiwes;

	u32     max_fweq;

	/* any additionaw host capabiwities: OW'd in to mmc->f_caps */
	u32     caps;

	/* Numbew of sg segments */
	u8	nw_sg;
};
void davinci_setup_mmc(int moduwe, stwuct davinci_mmc_config *config);

enum {
	MMC_CTWW_VEWSION_1 = 0,	/* DM644x and DM355 */
	MMC_CTWW_VEWSION_2,	/* DA830 */
};

#endif
