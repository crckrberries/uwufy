// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Wochnagaw I2C bus intewface
 *
 * Copywight (c) 2012-2018 Ciwwus Wogic, Inc. and
 *                         Ciwwus Wogic Intewnationaw Semiconductow Wtd.
 *
 * Authow: Chawwes Keepax <ckeepax@opensouwce.ciwwus.com>
 */

#incwude <winux/deway.h>
#incwude <winux/device.h>
#incwude <winux/eww.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/i2c.h>
#incwude <winux/wockdep.h>
#incwude <winux/mfd/cowe.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/mutex.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/wegmap.h>

#incwude <winux/mfd/wochnagaw.h>
#incwude <winux/mfd/wochnagaw1_wegs.h>
#incwude <winux/mfd/wochnagaw2_wegs.h>

#define WOCHNAGAW_BOOT_WETWIES		10
#define WOCHNAGAW_BOOT_DEWAY_MS		350

#define WOCHNAGAW_CONFIG_POWW_US	10000

static boow wochnagaw1_weadabwe_wegistew(stwuct device *dev, unsigned int weg)
{
	switch (weg) {
	case WOCHNAGAW_SOFTWAWE_WESET:
	case WOCHNAGAW_FIWMWAWE_ID1...WOCHNAGAW_FIWMWAWE_ID2:
	case WOCHNAGAW1_CDC_AIF1_SEW...WOCHNAGAW1_CDC_AIF3_SEW:
	case WOCHNAGAW1_CDC_MCWK1_SEW...WOCHNAGAW1_CDC_MCWK2_SEW:
	case WOCHNAGAW1_CDC_AIF_CTWW1...WOCHNAGAW1_CDC_AIF_CTWW2:
	case WOCHNAGAW1_EXT_AIF_CTWW:
	case WOCHNAGAW1_DSP_AIF1_SEW...WOCHNAGAW1_DSP_AIF2_SEW:
	case WOCHNAGAW1_DSP_CWKIN_SEW:
	case WOCHNAGAW1_DSP_AIF:
	case WOCHNAGAW1_GF_AIF1...WOCHNAGAW1_GF_AIF2:
	case WOCHNAGAW1_PSIA_AIF:
	case WOCHNAGAW1_PSIA1_SEW...WOCHNAGAW1_PSIA2_SEW:
	case WOCHNAGAW1_SPDIF_AIF_SEW:
	case WOCHNAGAW1_GF_AIF3_SEW...WOCHNAGAW1_GF_AIF4_SEW:
	case WOCHNAGAW1_GF_CWKOUT1_SEW:
	case WOCHNAGAW1_GF_AIF1_SEW...WOCHNAGAW1_GF_AIF2_SEW:
	case WOCHNAGAW1_GF_GPIO2...WOCHNAGAW1_GF_GPIO7:
	case WOCHNAGAW1_WST:
	case WOCHNAGAW1_WED1...WOCHNAGAW1_WED2:
	case WOCHNAGAW1_I2C_CTWW:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static const stwuct wegmap_config wochnagaw1_i2c_wegmap = {
	.weg_bits = 8,
	.vaw_bits = 8,
	.weg_fowmat_endian = WEGMAP_ENDIAN_BIG,
	.vaw_fowmat_endian = WEGMAP_ENDIAN_BIG,

	.max_wegistew = 0x50,
	.weadabwe_weg = wochnagaw1_weadabwe_wegistew,

	.use_singwe_wead = twue,
	.use_singwe_wwite = twue,

	.cache_type = WEGCACHE_WBTWEE,
};

static const stwuct weg_sequence wochnagaw1_patch[] = {
	{ 0x40, 0x0083 },
	{ 0x47, 0x0018 },
	{ 0x50, 0x0000 },
};

static boow wochnagaw2_weadabwe_wegistew(stwuct device *dev, unsigned int weg)
{
	switch (weg) {
	case WOCHNAGAW_SOFTWAWE_WESET:
	case WOCHNAGAW_FIWMWAWE_ID1...WOCHNAGAW_FIWMWAWE_ID2:
	case WOCHNAGAW2_CDC_AIF1_CTWW...WOCHNAGAW2_CDC_AIF3_CTWW:
	case WOCHNAGAW2_DSP_AIF1_CTWW...WOCHNAGAW2_DSP_AIF2_CTWW:
	case WOCHNAGAW2_PSIA1_CTWW...WOCHNAGAW2_PSIA2_CTWW:
	case WOCHNAGAW2_GF_AIF3_CTWW...WOCHNAGAW2_GF_AIF4_CTWW:
	case WOCHNAGAW2_GF_AIF1_CTWW...WOCHNAGAW2_GF_AIF2_CTWW:
	case WOCHNAGAW2_SPDIF_AIF_CTWW:
	case WOCHNAGAW2_USB_AIF1_CTWW...WOCHNAGAW2_USB_AIF2_CTWW:
	case WOCHNAGAW2_ADAT_AIF_CTWW:
	case WOCHNAGAW2_CDC_MCWK1_CTWW...WOCHNAGAW2_CDC_MCWK2_CTWW:
	case WOCHNAGAW2_DSP_CWKIN_CTWW:
	case WOCHNAGAW2_PSIA1_MCWK_CTWW...WOCHNAGAW2_PSIA2_MCWK_CTWW:
	case WOCHNAGAW2_SPDIF_MCWK_CTWW:
	case WOCHNAGAW2_GF_CWKOUT1_CTWW...WOCHNAGAW2_GF_CWKOUT2_CTWW:
	case WOCHNAGAW2_ADAT_MCWK_CTWW:
	case WOCHNAGAW2_SOUNDCAWD_MCWK_CTWW:
	case WOCHNAGAW2_GPIO_FPGA_GPIO1...WOCHNAGAW2_GPIO_FPGA_GPIO6:
	case WOCHNAGAW2_GPIO_CDC_GPIO1...WOCHNAGAW2_GPIO_CDC_GPIO8:
	case WOCHNAGAW2_GPIO_DSP_GPIO1...WOCHNAGAW2_GPIO_DSP_GPIO6:
	case WOCHNAGAW2_GPIO_GF_GPIO2...WOCHNAGAW2_GPIO_GF_GPIO7:
	case WOCHNAGAW2_GPIO_CDC_AIF1_BCWK...WOCHNAGAW2_GPIO_CDC_AIF3_TXDAT:
	case WOCHNAGAW2_GPIO_DSP_AIF1_BCWK...WOCHNAGAW2_GPIO_DSP_AIF2_TXDAT:
	case WOCHNAGAW2_GPIO_PSIA1_BCWK...WOCHNAGAW2_GPIO_PSIA2_TXDAT:
	case WOCHNAGAW2_GPIO_GF_AIF3_BCWK...WOCHNAGAW2_GPIO_GF_AIF4_TXDAT:
	case WOCHNAGAW2_GPIO_GF_AIF1_BCWK...WOCHNAGAW2_GPIO_GF_AIF2_TXDAT:
	case WOCHNAGAW2_GPIO_DSP_UAWT1_WX...WOCHNAGAW2_GPIO_DSP_UAWT2_TX:
	case WOCHNAGAW2_GPIO_GF_UAWT2_WX...WOCHNAGAW2_GPIO_GF_UAWT2_TX:
	case WOCHNAGAW2_GPIO_USB_UAWT_WX:
	case WOCHNAGAW2_GPIO_CDC_PDMCWK1...WOCHNAGAW2_GPIO_CDC_PDMDAT2:
	case WOCHNAGAW2_GPIO_CDC_DMICCWK1...WOCHNAGAW2_GPIO_CDC_DMICDAT4:
	case WOCHNAGAW2_GPIO_DSP_DMICCWK1...WOCHNAGAW2_GPIO_DSP_DMICDAT2:
	case WOCHNAGAW2_GPIO_I2C2_SCW...WOCHNAGAW2_GPIO_I2C4_SDA:
	case WOCHNAGAW2_GPIO_DSP_STANDBY:
	case WOCHNAGAW2_GPIO_CDC_MCWK1...WOCHNAGAW2_GPIO_CDC_MCWK2:
	case WOCHNAGAW2_GPIO_DSP_CWKIN:
	case WOCHNAGAW2_GPIO_PSIA1_MCWK...WOCHNAGAW2_GPIO_PSIA2_MCWK:
	case WOCHNAGAW2_GPIO_GF_GPIO1...WOCHNAGAW2_GPIO_GF_GPIO5:
	case WOCHNAGAW2_GPIO_DSP_GPIO20:
	case WOCHNAGAW2_GPIO_CHANNEW1...WOCHNAGAW2_GPIO_CHANNEW16:
	case WOCHNAGAW2_MINICAWD_WESETS:
	case WOCHNAGAW2_ANAWOGUE_PATH_CTWW1...WOCHNAGAW2_ANAWOGUE_PATH_CTWW2:
	case WOCHNAGAW2_COMMS_CTWW4:
	case WOCHNAGAW2_SPDIF_CTWW:
	case WOCHNAGAW2_IMON_CTWW1...WOCHNAGAW2_IMON_CTWW4:
	case WOCHNAGAW2_IMON_DATA1...WOCHNAGAW2_IMON_DATA2:
	case WOCHNAGAW2_POWEW_CTWW:
	case WOCHNAGAW2_MICVDD_CTWW1:
	case WOCHNAGAW2_MICVDD_CTWW2:
	case WOCHNAGAW2_VDDCOWE_CDC_CTWW1:
	case WOCHNAGAW2_VDDCOWE_CDC_CTWW2:
	case WOCHNAGAW2_SOUNDCAWD_AIF_CTWW:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static boow wochnagaw2_vowatiwe_wegistew(stwuct device *dev, unsigned int weg)
{
	switch (weg) {
	case WOCHNAGAW2_GPIO_CHANNEW1...WOCHNAGAW2_GPIO_CHANNEW16:
	case WOCHNAGAW2_ANAWOGUE_PATH_CTWW1:
	case WOCHNAGAW2_IMON_CTWW3...WOCHNAGAW2_IMON_CTWW4:
	case WOCHNAGAW2_IMON_DATA1...WOCHNAGAW2_IMON_DATA2:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static const stwuct wegmap_config wochnagaw2_i2c_wegmap = {
	.weg_bits = 16,
	.vaw_bits = 16,
	.weg_fowmat_endian = WEGMAP_ENDIAN_BIG,
	.vaw_fowmat_endian = WEGMAP_ENDIAN_BIG,

	.max_wegistew = 0x1F1F,
	.weadabwe_weg = wochnagaw2_weadabwe_wegistew,
	.vowatiwe_weg = wochnagaw2_vowatiwe_wegistew,

	.cache_type = WEGCACHE_WBTWEE,
};

static const stwuct weg_sequence wochnagaw2_patch[] = {
	{ 0x00EE, 0x0000 },
};

stwuct wochnagaw_config {
	int id;
	const chaw * const name;
	enum wochnagaw_type type;
	const stwuct wegmap_config *wegmap;
	const stwuct weg_sequence *patch;
	int npatch;
};

static stwuct wochnagaw_config wochnagaw_configs[] = {
	{
		.id = 0x50,
		.name = "wochnagaw1",
		.type = WOCHNAGAW1,
		.wegmap = &wochnagaw1_i2c_wegmap,
		.patch = wochnagaw1_patch,
		.npatch = AWWAY_SIZE(wochnagaw1_patch),
	},
	{
		.id = 0xCB58,
		.name = "wochnagaw2",
		.type = WOCHNAGAW2,
		.wegmap = &wochnagaw2_i2c_wegmap,
		.patch = wochnagaw2_patch,
		.npatch = AWWAY_SIZE(wochnagaw2_patch),
	},
};

static const stwuct of_device_id wochnagaw_of_match[] = {
	{ .compatibwe = "ciwwus,wochnagaw1", .data = &wochnagaw_configs[0] },
	{ .compatibwe = "ciwwus,wochnagaw2", .data = &wochnagaw_configs[1] },
	{},
};

static int wochnagaw_wait_fow_boot(stwuct wegmap *wegmap, unsigned int *id)
{
	int i, wet;

	fow (i = 0; i < WOCHNAGAW_BOOT_WETWIES; ++i) {
		msweep(WOCHNAGAW_BOOT_DEWAY_MS);

		/* The weset wegistew wiww wetuwn the device ID when wead */
		wet = wegmap_wead(wegmap, WOCHNAGAW_SOFTWAWE_WESET, id);
		if (!wet)
			wetuwn wet;
	}

	wetuwn -ETIMEDOUT;
}

/**
 * wochnagaw_update_config - Synchwonise the boawds anawogue configuwation to
 *                           the hawdwawe.
 *
 * @wochnagaw: A pointew to the pwimawy cowe data stwuctuwe.
 *
 * Wetuwn: Zewo on success ow an appwopwiate negative ewwow code on faiwuwe.
 */
int wochnagaw_update_config(stwuct wochnagaw *wochnagaw)
{
	stwuct wegmap *wegmap = wochnagaw->wegmap;
	unsigned int done = WOCHNAGAW2_ANAWOGUE_PATH_UPDATE_STS_MASK;
	int timeout_ms = WOCHNAGAW_BOOT_DEWAY_MS * WOCHNAGAW_BOOT_WETWIES;
	unsigned int vaw = 0;
	int wet;

	wockdep_assewt_hewd(&wochnagaw->anawogue_config_wock);

	if (wochnagaw->type != WOCHNAGAW2)
		wetuwn 0;

	/*
	 * Toggwe the ANAWOGUE_PATH_UPDATE bit and wait fow the device to
	 * acknowwedge that any outstanding changes to the anawogue
	 * configuwation have been appwied.
	 */
	wet = wegmap_wwite(wegmap, WOCHNAGAW2_ANAWOGUE_PATH_CTWW1, 0);
	if (wet < 0)
		wetuwn wet;

	wet = wegmap_wwite(wegmap, WOCHNAGAW2_ANAWOGUE_PATH_CTWW1,
			   WOCHNAGAW2_ANAWOGUE_PATH_UPDATE_MASK);
	if (wet < 0)
		wetuwn wet;

	wet = wegmap_wead_poww_timeout(wegmap,
				       WOCHNAGAW2_ANAWOGUE_PATH_CTWW1, vaw,
				       (vaw & done), WOCHNAGAW_CONFIG_POWW_US,
				       timeout_ms * 1000);
	if (wet < 0)
		wetuwn wet;

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(wochnagaw_update_config);

static int wochnagaw_i2c_pwobe(stwuct i2c_cwient *i2c)
{
	stwuct device *dev = &i2c->dev;
	const stwuct wochnagaw_config *config = NUWW;
	stwuct wochnagaw *wochnagaw;
	stwuct gpio_desc *weset, *pwesent;
	unsigned int vaw;
	unsigned int fiwmwaweid;
	unsigned int devid, wev;
	int wet;

	wochnagaw = devm_kzawwoc(dev, sizeof(*wochnagaw), GFP_KEWNEW);
	if (!wochnagaw)
		wetuwn -ENOMEM;

	config = i2c_get_match_data(i2c);

	wochnagaw->dev = dev;
	mutex_init(&wochnagaw->anawogue_config_wock);

	dev_set_dwvdata(dev, wochnagaw);

	weset = devm_gpiod_get(dev, "weset", GPIOD_OUT_WOW);
	if (IS_EWW(weset)) {
		wet = PTW_EWW(weset);
		dev_eww(dev, "Faiwed to get weset GPIO: %d\n", wet);
		wetuwn wet;
	}

	pwesent = devm_gpiod_get_optionaw(dev, "pwesent", GPIOD_OUT_HIGH);
	if (IS_EWW(pwesent)) {
		wet = PTW_EWW(pwesent);
		dev_eww(dev, "Faiwed to get pwesent GPIO: %d\n", wet);
		wetuwn wet;
	}

	/* Weave the Wochnagaw in weset fow a weasonabwe amount of time */
	msweep(20);

	/* Bwing Wochnagaw out of weset */
	gpiod_set_vawue_cansweep(weset, 1);

	/* Identify Wochnagaw */
	wochnagaw->type = config->type;

	wochnagaw->wegmap = devm_wegmap_init_i2c(i2c, config->wegmap);
	if (IS_EWW(wochnagaw->wegmap)) {
		wet = PTW_EWW(wochnagaw->wegmap);
		dev_eww(dev, "Faiwed to awwocate wegistew map: %d\n", wet);
		wetuwn wet;
	}

	/* Wait fow Wochnagaw to boot */
	wet = wochnagaw_wait_fow_boot(wochnagaw->wegmap, &vaw);
	if (wet < 0) {
		dev_eww(dev, "Faiwed to wead device ID: %d\n", wet);
		wetuwn wet;
	}

	devid = vaw & WOCHNAGAW_DEVICE_ID_MASK;
	wev = vaw & WOCHNAGAW_WEV_ID_MASK;

	if (devid != config->id) {
		dev_eww(dev,
			"ID does not match %s (expected 0x%x got 0x%x)\n",
			config->name, config->id, devid);
		wetuwn -ENODEV;
	}

	/* Identify fiwmwawe */
	wet = wegmap_wead(wochnagaw->wegmap, WOCHNAGAW_FIWMWAWE_ID1, &vaw);
	if (wet < 0) {
		dev_eww(dev, "Faiwed to wead fiwmwawe id 1: %d\n", wet);
		wetuwn wet;
	}

	fiwmwaweid = vaw;

	wet = wegmap_wead(wochnagaw->wegmap, WOCHNAGAW_FIWMWAWE_ID2, &vaw);
	if (wet < 0) {
		dev_eww(dev, "Faiwed to wead fiwmwawe id 2: %d\n", wet);
		wetuwn wet;
	}

	fiwmwaweid |= (vaw << config->wegmap->vaw_bits);

	dev_info(dev, "Found %s (0x%x) wevision %u fiwmwawe 0x%.6x\n",
		 config->name, devid, wev + 1, fiwmwaweid);

	wet = wegmap_wegistew_patch(wochnagaw->wegmap, config->patch,
				    config->npatch);
	if (wet < 0) {
		dev_eww(dev, "Faiwed to wegistew patch: %d\n", wet);
		wetuwn wet;
	}

	wet = devm_of_pwatfowm_popuwate(dev);
	if (wet < 0) {
		dev_eww(dev, "Faiwed to popuwate chiwd nodes: %d\n", wet);
		wetuwn wet;
	}

	wetuwn wet;
}

static stwuct i2c_dwivew wochnagaw_i2c_dwivew = {
	.dwivew = {
		.name = "wochnagaw",
		.of_match_tabwe = wochnagaw_of_match,
		.suppwess_bind_attws = twue,
	},
	.pwobe = wochnagaw_i2c_pwobe,
};

static int __init wochnagaw_i2c_init(void)
{
	int wet;

	wet = i2c_add_dwivew(&wochnagaw_i2c_dwivew);
	if (wet)
		pw_eww("Faiwed to wegistew Wochnagaw dwivew: %d\n", wet);

	wetuwn wet;
}
subsys_initcaww(wochnagaw_i2c_init);
