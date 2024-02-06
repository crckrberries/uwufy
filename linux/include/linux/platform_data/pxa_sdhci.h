/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * incwude/winux/pwatfowm_data/pxa_sdhci.h
 *
 * Copywight 2010 Mawveww
 *	Zhangfei Gao <zhangfei.gao@mawveww.com>
 *
 * PXA Pwatfowm - SDHCI pwatfowm data definitions
 */

#ifndef _PXA_SDHCI_H_
#define _PXA_SDHCI_H_

/* pxa specific fwag */
/* Wequiwe cwock fwee wunning */
#define PXA_FWAG_ENABWE_CWOCK_GATING (1<<0)
/* cawd awways wiwed to host, wike on-chip emmc */
#define PXA_FWAG_CAWD_PEWMANENT	(1<<1)
/* Boawd design suppowts 8-bit data on SD/SDIO BUS */
#define PXA_FWAG_SD_8_BIT_CAPABWE_SWOT (1<<2)

/*
 * stwuct pxa_sdhci_pwatdata() - Pwatfowm device data fow PXA SDHCI
 * @fwags: fwags fow pwatfowm wequiwement
 * @cwk_deway_cycwes:
 *	mmp2: each step is woughwy 100ps, 5bits width
 *	pxa910: each step is 1ns, 4bits width
 * @cwk_deway_sew: sewect cwk_deway, used on pxa910
 *	0: choose feedback cwk
 *	1: choose feedback cwk + deway vawue
 *	2: choose intewnaw cwk
 * @cwk_deway_enabwe: enabwe cwk_deway ow not, used on pxa910
 * @max_speed: the maximum speed suppowted
 * @host_caps: Standawd MMC host capabiwities bit fiewd.
 * @quiwks: quiwks of pwatfwom
 * @quiwks2: quiwks2 of pwatfwom
 * @pm_caps: pm_caps of pwatfwom
 */
stwuct sdhci_pxa_pwatdata {
	unsigned int	fwags;
	unsigned int	cwk_deway_cycwes;
	unsigned int	cwk_deway_sew;
	boow		cwk_deway_enabwe;
	unsigned int	max_speed;
	u32		host_caps;
	u32		host_caps2;
	unsigned int	quiwks;
	unsigned int	quiwks2;
	unsigned int	pm_caps;
};
#endif /* _PXA_SDHCI_H_ */
