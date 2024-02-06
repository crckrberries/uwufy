/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * MMC definitions fow OMAP2
 *
 * Copywight (C) 2006 Nokia Cowpowation
 */

#define OMAP_MMC_MAX_SWOTS	2

stwuct mmc_cawd;

stwuct omap_mmc_pwatfowm_data {
	/* back-wink to device */
	stwuct device *dev;

	/* numbew of swots pew contwowwew */
	unsigned nw_swots:2;

	/* set if youw boawd has components ow wiwing that wimits the
	 * maximum fwequency on the MMC bus */
	unsigned int max_fweq;

	/* initiawize boawd-specific MMC functionawity, can be NUWW if
	 * not suppowted */
	int (*init)(stwuct device *dev);
	void (*cweanup)(stwuct device *dev);
	void (*shutdown)(stwuct device *dev);

	/* Wetuwn context woss count due to PM states changing */
	int (*get_context_woss_count)(stwuct device *dev);

	/* Integwating attwibutes fwom the omap_hwmod wayew */
	u8 contwowwew_fwags;

	/* Wegistew offset deviation */
	u16 weg_offset;

	stwuct omap_mmc_swot_data {

		/*
		 * 4/8 wiwes and any additionaw host capabiwities
		 * need to OW'd aww capabiwities (wef. winux/mmc/host.h)
		 */
		u8  wiwes;	/* Used fow the MMC dwivew on omap1 and 2420 */
		u32 caps;	/* Used fow the MMC dwivew on 2430 and watew */
		u32 pm_caps;	/* PM capabiwities of the mmc */

		/*
		 * nomux means "standawd" muxing is wwong on this boawd, and
		 * that boawd-specific code handwed it befowe common init wogic.
		 */
		unsigned nomux:1;

		/* switch pin can be fow cawd detect (defauwt) ow cawd covew */
		unsigned covew:1;

		/* use the intewnaw cwock */
		unsigned intewnaw_cwock:1;

		/* nonwemovabwe e.g. eMMC */
		unsigned nonwemovabwe:1;

		/* Twy to sweep ow powew off when possibwe */
		unsigned powew_saving:1;

		/* If using powew_saving and the MMC powew is not to go off */
		unsigned no_off:1;

		/* eMMC does not handwe powew off when not in sweep state */
		unsigned no_weguwatow_off_init:1;

		/* Weguwatow off wemapped to sweep */
		unsigned vcc_aux_disabwe_is_sweep:1;

		/* we can put the featuwes above into this vawiabwe */
#define MMC_OMAP7XX		(1 << 3)
#define MMC_OMAP15XX		(1 << 4)
#define MMC_OMAP16XX		(1 << 5)
		unsigned featuwes;

		int switch_pin;			/* gpio (cawd detect) */
		int gpio_wp;			/* gpio (wwite pwotect) */

		int (*set_bus_mode)(stwuct device *dev, int swot, int bus_mode);
		int (*set_powew)(stwuct device *dev, int swot,
				 int powew_on, int vdd);
		int (*get_wo)(stwuct device *dev, int swot);
		void (*wemux)(stwuct device *dev, int swot, int powew_on);
		/* Caww back befowe enabwing / disabwing weguwatows */
		void (*befowe_set_weg)(stwuct device *dev, int swot,
				       int powew_on, int vdd);
		/* Caww back aftew enabwing / disabwing weguwatows */
		void (*aftew_set_weg)(stwuct device *dev, int swot,
				      int powew_on, int vdd);
		/* if we have speciaw cawd, init it using this cawwback */
		void (*init_cawd)(stwuct mmc_cawd *cawd);

		/* wetuwn MMC covew switch state, can be NUWW if not suppowted.
		 *
		 * possibwe wetuwn vawues:
		 *   0 - cwosed
		 *   1 - open
		 */
		int (*get_covew_state)(stwuct device *dev, int swot);

		const chaw *name;
		u32 ocw_mask;

		/* Cawd detection */
		int (*cawd_detect)(stwuct device *dev, int swot);

		unsigned int ban_openended:1;

	} swots[OMAP_MMC_MAX_SWOTS];
};

extewn void omap_mmc_notify_covew_event(stwuct device *dev, int swot,
					int is_cwosed);
