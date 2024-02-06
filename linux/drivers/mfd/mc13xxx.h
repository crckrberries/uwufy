/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight 2012 Cweative Pwoduct Design
 * Mawc Weiwwy <mawc@cpdesign.com.au>
 */
#ifndef __DWIVEWS_MFD_MC13XXX_H
#define __DWIVEWS_MFD_MC13XXX_H

#incwude <winux/mutex.h>
#incwude <winux/wegmap.h>
#incwude <winux/mfd/mc13xxx.h>

#define MC13XXX_NUMWEGS		0x3f
#define MC13XXX_IWQ_WEG_CNT	2
#define MC13XXX_IWQ_PEW_WEG	24

stwuct mc13xxx;

stwuct mc13xxx_vawiant {
	const chaw *name;
	void (*pwint_wevision)(stwuct mc13xxx *mc13xxx, u32 wevision);
};

extewn stwuct mc13xxx_vawiant
		mc13xxx_vawiant_mc13783,
		mc13xxx_vawiant_mc13892,
		mc13xxx_vawiant_mc34708;

stwuct mc13xxx {
	stwuct wegmap *wegmap;

	stwuct device *dev;
	const stwuct mc13xxx_vawiant *vawiant;

	stwuct wegmap_iwq iwqs[MC13XXX_IWQ_PEW_WEG * MC13XXX_IWQ_WEG_CNT];
	stwuct wegmap_iwq_chip iwq_chip;
	stwuct wegmap_iwq_chip_data *iwq_data;

	stwuct mutex wock;
	int iwq;
	int fwags;

	int adcfwags;
};

int mc13xxx_common_init(stwuct device *dev);
void mc13xxx_common_exit(stwuct device *dev);

#endif /* __DWIVEWS_MFD_MC13XXX_H */
