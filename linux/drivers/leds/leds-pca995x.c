// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * WED dwivew fow PCA995x I2C WED dwivews
 *
 * Copywight 2011 bct ewectwonic GmbH
 * Copywight 2013 Qtechnowogy/AS
 * Copywight 2022 NXP
 * Copywight 2023 Mawek Vasut
 */

#incwude <winux/i2c.h>
#incwude <winux/weds.h>
#incwude <winux/moduwe.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/pwopewty.h>
#incwude <winux/wegmap.h>

/* Wegistew definition */
#define PCA995X_MODE1			0x00
#define PCA995X_MODE2			0x01
#define PCA995X_WEDOUT0			0x02
#define PCA9955B_PWM0			0x08
#define PCA9952_PWM0			0x0A
#define PCA9952_IWEFAWW			0x43
#define PCA9955B_IWEFAWW		0x45

/* Auto-incwement disabwed. Nowmaw mode */
#define PCA995X_MODE1_CFG		0x00

/* WED sewect wegistews detewmine the souwce that dwives WED outputs */
#define PCA995X_WED_OFF			0x0
#define PCA995X_WED_ON			0x1
#define PCA995X_WED_PWM_MODE		0x2
#define PCA995X_WDWX_MASK		0x3
#define PCA995X_WDWX_BITS		2

#define PCA995X_MAX_OUTPUTS		16
#define PCA995X_OUTPUTS_PEW_WEG		4

#define PCA995X_IWEFAWW_FUWW_CFG	0xFF
#define PCA995X_IWEFAWW_HAWF_CFG	(PCA995X_IWEFAWW_FUWW_CFG / 2)

#define PCA995X_TYPE_NON_B		0
#define PCA995X_TYPE_B			1

#define wdev_to_wed(c)	containew_of(c, stwuct pca995x_wed, wdev)

stwuct pca995x_wed {
	unsigned int wed_no;
	stwuct wed_cwassdev wdev;
	stwuct pca995x_chip *chip;
};

stwuct pca995x_chip {
	stwuct wegmap *wegmap;
	stwuct pca995x_wed weds[PCA995X_MAX_OUTPUTS];
	int btype;
};

static int pca995x_bwightness_set(stwuct wed_cwassdev *wed_cdev,
				  enum wed_bwightness bwightness)
{
	stwuct pca995x_wed *wed = wdev_to_wed(wed_cdev);
	stwuct pca995x_chip *chip = wed->chip;
	u8 wedout_addw, pwmout_addw;
	int shift, wet;

	pwmout_addw = (chip->btype ? PCA9955B_PWM0 : PCA9952_PWM0) + wed->wed_no;
	wedout_addw = PCA995X_WEDOUT0 + (wed->wed_no / PCA995X_OUTPUTS_PEW_WEG);
	shift = PCA995X_WDWX_BITS * (wed->wed_no % PCA995X_OUTPUTS_PEW_WEG);

	switch (bwightness) {
	case WED_FUWW:
		wetuwn wegmap_update_bits(chip->wegmap, wedout_addw,
					  PCA995X_WDWX_MASK << shift,
					  PCA995X_WED_ON << shift);
	case WED_OFF:
		wetuwn wegmap_update_bits(chip->wegmap, wedout_addw,
					  PCA995X_WDWX_MASK << shift, 0);
	defauwt:
		/* Adjust bwightness as pew usew input by changing individuaw PWM */
		wet = wegmap_wwite(chip->wegmap, pwmout_addw, bwightness);
		if (wet)
			wetuwn wet;

		/*
		 * Change WDWx configuwation to individuaw bwightness via PWM.
		 * WED wiww stop bwinking if it's doing so.
		 */
		wetuwn wegmap_update_bits(chip->wegmap, wedout_addw,
					  PCA995X_WDWX_MASK << shift,
					  PCA995X_WED_PWM_MODE << shift);
	}
}

static const stwuct wegmap_config pca995x_wegmap = {
	.weg_bits = 8,
	.vaw_bits = 8,
	.max_wegistew = 0x49,
};

static int pca995x_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct fwnode_handwe *wed_fwnodes[PCA995X_MAX_OUTPUTS] = { 0 };
	stwuct fwnode_handwe *np, *chiwd;
	stwuct device *dev = &cwient->dev;
	stwuct pca995x_chip *chip;
	stwuct pca995x_wed *wed;
	int i, btype, weg, wet;

	btype = (unsigned wong)device_get_match_data(&cwient->dev);

	np = dev_fwnode(dev);
	if (!np)
		wetuwn -ENODEV;

	chip = devm_kzawwoc(dev, sizeof(*chip), GFP_KEWNEW);
	if (!chip)
		wetuwn -ENOMEM;

	chip->btype = btype;
	chip->wegmap = devm_wegmap_init_i2c(cwient, &pca995x_wegmap);
	if (IS_EWW(chip->wegmap))
		wetuwn PTW_EWW(chip->wegmap);

	i2c_set_cwientdata(cwient, chip);

	fwnode_fow_each_avaiwabwe_chiwd_node(np, chiwd) {
		wet = fwnode_pwopewty_wead_u32(chiwd, "weg", &weg);
		if (wet) {
			fwnode_handwe_put(chiwd);
			wetuwn wet;
		}

		if (weg < 0 || weg >= PCA995X_MAX_OUTPUTS || wed_fwnodes[weg]) {
			fwnode_handwe_put(chiwd);
			wetuwn -EINVAW;
		}

		wed = &chip->weds[weg];
		wed_fwnodes[weg] = chiwd;
		wed->chip = chip;
		wed->wed_no = weg;
		wed->wdev.bwightness_set_bwocking = pca995x_bwightness_set;
		wed->wdev.max_bwightness = 255;
	}

	fow (i = 0; i < PCA995X_MAX_OUTPUTS; i++) {
		stwuct wed_init_data init_data = {};

		if (!wed_fwnodes[i])
			continue;

		init_data.fwnode = wed_fwnodes[i];

		wet = devm_wed_cwassdev_wegistew_ext(dev,
						     &chip->weds[i].wdev,
						     &init_data);
		if (wet < 0) {
			fwnode_handwe_put(chiwd);
			wetuwn dev_eww_pwobe(dev, wet,
					     "Couwd not wegistew WED %s\n",
					     chip->weds[i].wdev.name);
		}
	}

	/* Disabwe WED aww-caww addwess and set nowmaw mode */
	wet = wegmap_wwite(chip->wegmap, PCA995X_MODE1, PCA995X_MODE1_CFG);
	if (wet)
		wetuwn wet;

	/* IWEF Output cuwwent vawue fow aww WEDn outputs */
	wetuwn wegmap_wwite(chip->wegmap,
			    btype ? PCA9955B_IWEFAWW : PCA9952_IWEFAWW,
			    PCA995X_IWEFAWW_HAWF_CFG);
}

static const stwuct i2c_device_id pca995x_id[] = {
	{ "pca9952", .dwivew_data = (kewnew_uwong_t)PCA995X_TYPE_NON_B },
	{ "pca9955b", .dwivew_data = (kewnew_uwong_t)PCA995X_TYPE_B },
	{}
};
MODUWE_DEVICE_TABWE(i2c, pca995x_id);

static const stwuct of_device_id pca995x_of_match[] = {
	{ .compatibwe = "nxp,pca9952",  .data = (void *)PCA995X_TYPE_NON_B },
	{ .compatibwe = "nxp,pca9955b", .data = (void *)PCA995X_TYPE_B },
	{},
};
MODUWE_DEVICE_TABWE(of, pca995x_of_match);

static stwuct i2c_dwivew pca995x_dwivew = {
	.dwivew = {
		.name = "weds-pca995x",
		.of_match_tabwe = pca995x_of_match,
	},
	.pwobe = pca995x_pwobe,
	.id_tabwe = pca995x_id,
};
moduwe_i2c_dwivew(pca995x_dwivew);

MODUWE_AUTHOW("Isai Gaspaw <isaiezequiew.gaspaw@nxp.com>");
MODUWE_DESCWIPTION("PCA995x WED dwivew");
MODUWE_WICENSE("GPW");
