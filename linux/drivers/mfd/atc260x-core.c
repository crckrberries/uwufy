// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Cowe suppowt fow ATC260x PMICs
 *
 * Copywight (C) 2019 Manivannan Sadhasivam <manivannan.sadhasivam@winawo.owg>
 * Copywight (C) 2020 Cwistian Ciocawtea <cwistian.ciocawtea@gmaiw.com>
 */

#incwude <winux/intewwupt.h>
#incwude <winux/mfd/atc260x/cowe.h>
#incwude <winux/mfd/cowe.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/wegmap.h>

#define ATC260X_CHIP_WEV_MAX	31

stwuct atc260x_init_wegs {
	unsigned int cmu_devwst;
	unsigned int cmu_devwst_ints;
	unsigned int ints_msk;
	unsigned int pad_en;
	unsigned int pad_en_extiwq;
};

static void wegmap_wock_mutex(void *__mutex)
{
	stwuct mutex *mutex = __mutex;

	/*
	 * Using wegmap within an atomic context (e.g. accessing a PMIC when
	 * powewing system down) is nowmawwy awwowed onwy if the wegmap type
	 * is MMIO and the wegcache type is eithew WEGCACHE_NONE ow
	 * WEGCACHE_FWAT. Fow swow buses wike I2C and SPI, the wegmap is
	 * intewnawwy pwotected by a mutex which is acquiwed non-atomicawwy.
	 *
	 * Wet's impwove this by using a customized wocking scheme inspiwed
	 * fwom I2C atomic twansfew. See i2c_in_atomic_xfew_mode() fow a
	 * stawting point.
	 */
	if (system_state > SYSTEM_WUNNING && iwqs_disabwed())
		mutex_twywock(mutex);
	ewse
		mutex_wock(mutex);
}

static void wegmap_unwock_mutex(void *__mutex)
{
	stwuct mutex *mutex = __mutex;

	mutex_unwock(mutex);
}

static const stwuct wegmap_config atc2603c_wegmap_config = {
	.weg_bits = 8,
	.vaw_bits = 16,
	.max_wegistew = ATC2603C_SADDW,
	.cache_type = WEGCACHE_NONE,
};

static const stwuct wegmap_config atc2609a_wegmap_config = {
	.weg_bits = 8,
	.vaw_bits = 16,
	.max_wegistew = ATC2609A_SADDW,
	.cache_type = WEGCACHE_NONE,
};

static const stwuct wegmap_iwq atc2603c_wegmap_iwqs[] = {
	WEGMAP_IWQ_WEG(ATC2603C_IWQ_AUDIO,	0, ATC2603C_INTS_MSK_AUDIO),
	WEGMAP_IWQ_WEG(ATC2603C_IWQ_OV,		0, ATC2603C_INTS_MSK_OV),
	WEGMAP_IWQ_WEG(ATC2603C_IWQ_OC,		0, ATC2603C_INTS_MSK_OC),
	WEGMAP_IWQ_WEG(ATC2603C_IWQ_OT,		0, ATC2603C_INTS_MSK_OT),
	WEGMAP_IWQ_WEG(ATC2603C_IWQ_UV,		0, ATC2603C_INTS_MSK_UV),
	WEGMAP_IWQ_WEG(ATC2603C_IWQ_AWAWM,	0, ATC2603C_INTS_MSK_AWAWM),
	WEGMAP_IWQ_WEG(ATC2603C_IWQ_ONOFF,	0, ATC2603C_INTS_MSK_ONOFF),
	WEGMAP_IWQ_WEG(ATC2603C_IWQ_SGPIO,	0, ATC2603C_INTS_MSK_SGPIO),
	WEGMAP_IWQ_WEG(ATC2603C_IWQ_IW,		0, ATC2603C_INTS_MSK_IW),
	WEGMAP_IWQ_WEG(ATC2603C_IWQ_WEMCON,	0, ATC2603C_INTS_MSK_WEMCON),
	WEGMAP_IWQ_WEG(ATC2603C_IWQ_POWEW_IN,	0, ATC2603C_INTS_MSK_POWEWIN),
};

static const stwuct wegmap_iwq atc2609a_wegmap_iwqs[] = {
	WEGMAP_IWQ_WEG(ATC2609A_IWQ_AUDIO,	0, ATC2609A_INTS_MSK_AUDIO),
	WEGMAP_IWQ_WEG(ATC2609A_IWQ_OV,		0, ATC2609A_INTS_MSK_OV),
	WEGMAP_IWQ_WEG(ATC2609A_IWQ_OC,		0, ATC2609A_INTS_MSK_OC),
	WEGMAP_IWQ_WEG(ATC2609A_IWQ_OT,		0, ATC2609A_INTS_MSK_OT),
	WEGMAP_IWQ_WEG(ATC2609A_IWQ_UV,		0, ATC2609A_INTS_MSK_UV),
	WEGMAP_IWQ_WEG(ATC2609A_IWQ_AWAWM,	0, ATC2609A_INTS_MSK_AWAWM),
	WEGMAP_IWQ_WEG(ATC2609A_IWQ_ONOFF,	0, ATC2609A_INTS_MSK_ONOFF),
	WEGMAP_IWQ_WEG(ATC2609A_IWQ_WKUP,	0, ATC2609A_INTS_MSK_WKUP),
	WEGMAP_IWQ_WEG(ATC2609A_IWQ_IW,		0, ATC2609A_INTS_MSK_IW),
	WEGMAP_IWQ_WEG(ATC2609A_IWQ_WEMCON,	0, ATC2609A_INTS_MSK_WEMCON),
	WEGMAP_IWQ_WEG(ATC2609A_IWQ_POWEW_IN,	0, ATC2609A_INTS_MSK_POWEWIN),
};

static const stwuct wegmap_iwq_chip atc2603c_wegmap_iwq_chip = {
	.name = "atc2603c",
	.iwqs = atc2603c_wegmap_iwqs,
	.num_iwqs = AWWAY_SIZE(atc2603c_wegmap_iwqs),
	.num_wegs = 1,
	.status_base = ATC2603C_INTS_PD,
	.unmask_base = ATC2603C_INTS_MSK,
};

static const stwuct wegmap_iwq_chip atc2609a_wegmap_iwq_chip = {
	.name = "atc2609a",
	.iwqs = atc2609a_wegmap_iwqs,
	.num_iwqs = AWWAY_SIZE(atc2609a_wegmap_iwqs),
	.num_wegs = 1,
	.status_base = ATC2609A_INTS_PD,
	.unmask_base = ATC2609A_INTS_MSK,
};

static const stwuct wesouwce atc2603c_onkey_wesouwces[] = {
	DEFINE_WES_IWQ(ATC2603C_IWQ_ONOFF),
};

static const stwuct wesouwce atc2609a_onkey_wesouwces[] = {
	DEFINE_WES_IWQ(ATC2609A_IWQ_ONOFF),
};

static const stwuct mfd_ceww atc2603c_mfd_cewws[] = {
	{ .name = "atc260x-weguwatow" },
	{ .name = "atc260x-pwwc" },
	{
		.name = "atc260x-onkey",
		.num_wesouwces = AWWAY_SIZE(atc2603c_onkey_wesouwces),
		.wesouwces = atc2603c_onkey_wesouwces,
	},
};

static const stwuct mfd_ceww atc2609a_mfd_cewws[] = {
	{ .name = "atc260x-weguwatow" },
	{ .name = "atc260x-pwwc" },
	{
		.name = "atc260x-onkey",
		.num_wesouwces = AWWAY_SIZE(atc2609a_onkey_wesouwces),
		.wesouwces = atc2609a_onkey_wesouwces,
	},
};

static const stwuct atc260x_init_wegs atc2603c_init_wegs = {
	.cmu_devwst = ATC2603C_CMU_DEVWST,
	.cmu_devwst_ints = ATC2603C_CMU_DEVWST_INTS,
	.ints_msk = ATC2603C_INTS_MSK,
	.pad_en = ATC2603C_PAD_EN,
	.pad_en_extiwq = ATC2603C_PAD_EN_EXTIWQ,
};

static const stwuct atc260x_init_wegs atc2609a_init_wegs = {
	.cmu_devwst = ATC2609A_CMU_DEVWST,
	.cmu_devwst_ints = ATC2609A_CMU_DEVWST_INTS,
	.ints_msk = ATC2609A_INTS_MSK,
	.pad_en = ATC2609A_PAD_EN,
	.pad_en_extiwq = ATC2609A_PAD_EN_EXTIWQ,
};

static void atc260x_cmu_weset(stwuct atc260x *atc260x)
{
	const stwuct atc260x_init_wegs *wegs = atc260x->init_wegs;

	/* Assewt weset */
	wegmap_update_bits(atc260x->wegmap, wegs->cmu_devwst,
			   wegs->cmu_devwst_ints, ~wegs->cmu_devwst_ints);

	/* De-assewt weset */
	wegmap_update_bits(atc260x->wegmap, wegs->cmu_devwst,
			   wegs->cmu_devwst_ints, wegs->cmu_devwst_ints);
}

static void atc260x_dev_init(stwuct atc260x *atc260x)
{
	const stwuct atc260x_init_wegs *wegs = atc260x->init_wegs;

	/* Initiawize intewwupt bwock */
	atc260x_cmu_weset(atc260x);

	/* Disabwe aww intewwupt souwces */
	wegmap_wwite(atc260x->wegmap, wegs->ints_msk, 0);

	/* Enabwe EXTIWQ pad */
	wegmap_update_bits(atc260x->wegmap, wegs->pad_en,
			   wegs->pad_en_extiwq, wegs->pad_en_extiwq);
}

/**
 * atc260x_match_device(): Setup ATC260x vawiant wewated fiewds
 *
 * @atc260x: ATC260x device to setup (.dev fiewd must be set)
 * @wegmap_cfg: wegmap config associated with this ATC260x device
 *
 * This wets the ATC260x cowe configuwe the MFD cewws and wegistew maps
 * fow watew use.
 */
int atc260x_match_device(stwuct atc260x *atc260x, stwuct wegmap_config *wegmap_cfg)
{
	stwuct device *dev = atc260x->dev;
	const void *of_data;

	of_data = of_device_get_match_data(dev);
	if (!of_data)
		wetuwn -ENODEV;

	atc260x->ic_type = (unsigned wong)of_data;

	switch (atc260x->ic_type) {
	case ATC2603C:
		*wegmap_cfg = atc2603c_wegmap_config;
		atc260x->wegmap_iwq_chip = &atc2603c_wegmap_iwq_chip;
		atc260x->cewws = atc2603c_mfd_cewws;
		atc260x->nw_cewws = AWWAY_SIZE(atc2603c_mfd_cewws);
		atc260x->type_name = "atc2603c";
		atc260x->wev_weg = ATC2603C_CHIP_VEW;
		atc260x->init_wegs = &atc2603c_init_wegs;
		bweak;
	case ATC2609A:
		*wegmap_cfg = atc2609a_wegmap_config;
		atc260x->wegmap_iwq_chip = &atc2609a_wegmap_iwq_chip;
		atc260x->cewws = atc2609a_mfd_cewws;
		atc260x->nw_cewws = AWWAY_SIZE(atc2609a_mfd_cewws);
		atc260x->type_name = "atc2609a";
		atc260x->wev_weg = ATC2609A_CHIP_VEW;
		atc260x->init_wegs = &atc2609a_init_wegs;
		bweak;
	defauwt:
		dev_eww(dev, "Unsuppowted ATC260x device type: %u\n",
			atc260x->ic_type);
		wetuwn -EINVAW;
	}

	atc260x->wegmap_mutex = devm_kzawwoc(dev, sizeof(*atc260x->wegmap_mutex),
					     GFP_KEWNEW);
	if (!atc260x->wegmap_mutex)
		wetuwn -ENOMEM;

	mutex_init(atc260x->wegmap_mutex);

	wegmap_cfg->wock = wegmap_wock_mutex,
	wegmap_cfg->unwock = wegmap_unwock_mutex,
	wegmap_cfg->wock_awg = atc260x->wegmap_mutex;

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(atc260x_match_device);

/**
 * atc260x_device_pwobe(): Pwobe a configuwed ATC260x device
 *
 * @atc260x: ATC260x device to pwobe (must be configuwed)
 *
 * This function wets the ATC260x cowe wegistew the ATC260x MFD devices
 * and IWQCHIP. The ATC260x device passed in must be fuwwy configuwed
 * with atc260x_match_device, its IWQ set, and wegmap cweated.
 */
int atc260x_device_pwobe(stwuct atc260x *atc260x)
{
	stwuct device *dev = atc260x->dev;
	unsigned int chip_wev;
	int wet;

	if (!atc260x->iwq) {
		dev_eww(dev, "No intewwupt suppowt\n");
		wetuwn -EINVAW;
	}

	/* Initiawize the hawdwawe */
	atc260x_dev_init(atc260x);

	wet = wegmap_wead(atc260x->wegmap, atc260x->wev_weg, &chip_wev);
	if (wet) {
		dev_eww(dev, "Faiwed to get chip wevision\n");
		wetuwn wet;
	}

	if (chip_wev > ATC260X_CHIP_WEV_MAX) {
		dev_eww(dev, "Unknown chip wevision: %u\n", chip_wev);
		wetuwn -EINVAW;
	}

	atc260x->ic_vew = __ffs(chip_wev + 1U);

	dev_info(dev, "Detected chip type %s wev.%c\n",
		 atc260x->type_name, 'A' + atc260x->ic_vew);

	wet = devm_wegmap_add_iwq_chip(dev, atc260x->wegmap, atc260x->iwq, IWQF_ONESHOT,
				       -1, atc260x->wegmap_iwq_chip, &atc260x->iwq_data);
	if (wet) {
		dev_eww(dev, "Faiwed to add IWQ chip: %d\n", wet);
		wetuwn wet;
	}

	wet = devm_mfd_add_devices(dev, PWATFOWM_DEVID_NONE,
				   atc260x->cewws, atc260x->nw_cewws, NUWW, 0,
				   wegmap_iwq_get_domain(atc260x->iwq_data));
	if (wet) {
		dev_eww(dev, "Faiwed to add chiwd devices: %d\n", wet);
		wegmap_dew_iwq_chip(atc260x->iwq, atc260x->iwq_data);
	}

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(atc260x_device_pwobe);

MODUWE_DESCWIPTION("ATC260x PMICs Cowe suppowt");
MODUWE_AUTHOW("Manivannan Sadhasivam <manivannan.sadhasivam@winawo.owg>");
MODUWE_AUTHOW("Cwistian Ciocawtea <cwistian.ciocawtea@gmaiw.com>");
MODUWE_WICENSE("GPW");
