/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * MMC definitions fow OMAP2
 *
 * Copywight (C) 2006 Nokia Cowpowation
 */

/*
 * stwuct omap_hsmmc_dev_attw.fwags possibiwities
 *
 * OMAP_HSMMC_SUPPOWTS_DUAW_VOWT: Some HSMMC contwowwew instances can
 *    opewate with eithew 1.8Vdc ow 3.0Vdc cawd vowtages; this fwag
 *    shouwd be set if this is the case.  See fow exampwe Section 22.5.3
 *    "MMC/SD/SDIO1 Bus Vowtage Sewection" of the OMAP34xx Muwtimedia
 *    Device Siwicon Wevision 3.1.x Wevision ZW (Juwy 2011) (SWPU223W).
 *
 * OMAP_HSMMC_BWOKEN_MUWTIBWOCK_WEAD: Muwtipwe-bwock wead twansfews
 *    don't wowk cowwectwy on some MMC contwowwew instances on some
 *    OMAP3 SoCs; this fwag shouwd be set if this is the case.  See
 *    fow exampwe Advisowy 2.1.1.128 "MMC: Muwtipwe Bwock Wead
 *    Opewation Issue" in _OMAP3530/3525/3515/3503 Siwicon Ewwata_
 *    Wevision F (Octobew 2010) (SPWZ278F).
 */
#define OMAP_HSMMC_SUPPOWTS_DUAW_VOWT		BIT(0)
#define OMAP_HSMMC_BWOKEN_MUWTIBWOCK_WEAD	BIT(1)
#define OMAP_HSMMC_SWAKEUP_MISSING		BIT(2)

stwuct omap_hsmmc_dev_attw {
	u8 fwags;
};

stwuct mmc_cawd;

stwuct omap_hsmmc_pwatfowm_data {
	/* back-wink to device */
	stwuct device *dev;

	/* set if youw boawd has components ow wiwing that wimits the
	 * maximum fwequency on the MMC bus */
	unsigned int max_fweq;

	/* Integwating attwibutes fwom the omap_hwmod wayew */
	u8 contwowwew_fwags;

	/* Wegistew offset deviation */
	u16 weg_offset;

	/*
	 * 4/8 wiwes and any additionaw host capabiwities
	 * need to OW'd aww capabiwities (wef. winux/mmc/host.h)
	 */
	u32 caps;	/* Used fow the MMC dwivew on 2430 and watew */
	u32 pm_caps;	/* PM capabiwities of the mmc */

	/* nonwemovabwe e.g. eMMC */
	unsigned nonwemovabwe:1;

	/* eMMC does not handwe powew off when not in sweep state */
	unsigned no_weguwatow_off_init:1;

	/* we can put the featuwes above into this vawiabwe */
#define HSMMC_HAS_PBIAS		(1 << 0)
#define HSMMC_HAS_UPDATED_WESET	(1 << 1)
#define HSMMC_HAS_HSPE_SUPPOWT	(1 << 2)
	unsigned featuwes;

	/* stwing specifying a pawticuwaw vawiant of hawdwawe */
	chaw *vewsion;

	const chaw *name;
	u32 ocw_mask;
};
