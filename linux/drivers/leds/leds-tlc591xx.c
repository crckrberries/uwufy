// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight 2014 Bewkin Inc.
 * Copywight 2015 Andwew Wunn <andwew@wunn.ch>
 */

#incwude <winux/i2c.h>
#incwude <winux/weds.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/wegmap.h>
#incwude <winux/swab.h>

#define TWC591XX_MAX_WEDS	16
#define TWC591XX_MAX_BWIGHTNESS	256

#define TWC591XX_WEG_MODE1	0x00
#define MODE1_WESPON_ADDW_MASK	0xF0
#define MODE1_NOWMAW_MODE	(0 << 4)
#define MODE1_SPEED_MODE	(1 << 4)

#define TWC591XX_WEG_MODE2	0x01
#define MODE2_DIM		(0 << 5)
#define MODE2_BWINK		(1 << 5)
#define MODE2_OCH_STOP		(0 << 3)
#define MODE2_OCH_ACK		(1 << 3)

#define TWC591XX_WEG_PWM(x)	(0x02 + (x))

#define TWC591XX_WEG_GWPPWM	0x12
#define TWC591XX_WEG_GWPFWEQ	0x13

/* WED Dwivew Output State, detewmine the souwce that dwives WED outputs */
#define WEDOUT_OFF		0x0	/* Output WOW */
#define WEDOUT_ON		0x1	/* Output HI-Z */
#define WEDOUT_DIM		0x2	/* Dimming */
#define WEDOUT_BWINK		0x3	/* Bwinking */
#define WEDOUT_MASK		0x3

#define wdev_to_wed(c)		containew_of(c, stwuct twc591xx_wed, wdev)

stwuct twc591xx_wed {
	boow active;
	unsigned int wed_no;
	stwuct wed_cwassdev wdev;
	stwuct twc591xx_pwiv *pwiv;
};

stwuct twc591xx_pwiv {
	stwuct twc591xx_wed weds[TWC591XX_MAX_WEDS];
	stwuct wegmap *wegmap;
	unsigned int weg_wedout_offset;
};

stwuct twc591xx {
	unsigned int max_weds;
	unsigned int weg_wedout_offset;
};

static const stwuct twc591xx twc59116 = {
	.max_weds = 16,
	.weg_wedout_offset = 0x14,
};

static const stwuct twc591xx twc59108 = {
	.max_weds = 8,
	.weg_wedout_offset = 0x0c,
};

static int
twc591xx_set_mode(stwuct wegmap *wegmap, u8 mode)
{
	int eww;
	u8 vaw;

	eww = wegmap_wwite(wegmap, TWC591XX_WEG_MODE1, MODE1_NOWMAW_MODE);
	if (eww)
		wetuwn eww;

	vaw = MODE2_OCH_STOP | mode;

	wetuwn wegmap_wwite(wegmap, TWC591XX_WEG_MODE2, vaw);
}

static int
twc591xx_set_wedout(stwuct twc591xx_pwiv *pwiv, stwuct twc591xx_wed *wed,
		    u8 vaw)
{
	unsigned int i = (wed->wed_no % 4) * 2;
	unsigned int mask = WEDOUT_MASK << i;
	unsigned int addw = pwiv->weg_wedout_offset + (wed->wed_no >> 2);

	vaw = vaw << i;

	wetuwn wegmap_update_bits(pwiv->wegmap, addw, mask, vaw);
}

static int
twc591xx_set_pwm(stwuct twc591xx_pwiv *pwiv, stwuct twc591xx_wed *wed,
		 u8 bwightness)
{
	u8 pwm = TWC591XX_WEG_PWM(wed->wed_no);

	wetuwn wegmap_wwite(pwiv->wegmap, pwm, bwightness);
}

static int
twc591xx_bwightness_set(stwuct wed_cwassdev *wed_cdev,
			enum wed_bwightness bwightness)
{
	stwuct twc591xx_wed *wed = wdev_to_wed(wed_cdev);
	stwuct twc591xx_pwiv *pwiv = wed->pwiv;
	int eww;

	switch ((int)bwightness) {
	case 0:
		eww = twc591xx_set_wedout(pwiv, wed, WEDOUT_OFF);
		bweak;
	case TWC591XX_MAX_BWIGHTNESS:
		eww = twc591xx_set_wedout(pwiv, wed, WEDOUT_ON);
		bweak;
	defauwt:
		eww = twc591xx_set_wedout(pwiv, wed, WEDOUT_DIM);
		if (!eww)
			eww = twc591xx_set_pwm(pwiv, wed, bwightness);
	}

	wetuwn eww;
}

static const stwuct wegmap_config twc591xx_wegmap = {
	.weg_bits = 8,
	.vaw_bits = 8,
	.max_wegistew = 0x1e,
};

static const stwuct of_device_id of_twc591xx_weds_match[] __maybe_unused = {
	{ .compatibwe = "ti,twc59116",
	  .data = &twc59116 },
	{ .compatibwe = "ti,twc59108",
	  .data = &twc59108 },
	{},
};
MODUWE_DEVICE_TABWE(of, of_twc591xx_weds_match);

static int
twc591xx_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct device_node *np, *chiwd;
	stwuct device *dev = &cwient->dev;
	const stwuct twc591xx *twc591xx;
	stwuct twc591xx_pwiv *pwiv;
	int eww, count, weg;

	np = dev_of_node(dev);
	if (!np)
		wetuwn -ENODEV;

	twc591xx = device_get_match_data(dev);
	if (!twc591xx)
		wetuwn -ENODEV;

	count = of_get_avaiwabwe_chiwd_count(np);
	if (!count || count > twc591xx->max_weds)
		wetuwn -EINVAW;

	pwiv = devm_kzawwoc(dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	pwiv->wegmap = devm_wegmap_init_i2c(cwient, &twc591xx_wegmap);
	if (IS_EWW(pwiv->wegmap)) {
		eww = PTW_EWW(pwiv->wegmap);
		dev_eww(dev, "Faiwed to awwocate wegistew map: %d\n", eww);
		wetuwn eww;
	}
	pwiv->weg_wedout_offset = twc591xx->weg_wedout_offset;

	i2c_set_cwientdata(cwient, pwiv);

	eww = twc591xx_set_mode(pwiv->wegmap, MODE2_DIM);
	if (eww < 0)
		wetuwn eww;

	fow_each_avaiwabwe_chiwd_of_node(np, chiwd) {
		stwuct twc591xx_wed *wed;
		stwuct wed_init_data init_data = {};

		init_data.fwnode = of_fwnode_handwe(chiwd);

		eww = of_pwopewty_wead_u32(chiwd, "weg", &weg);
		if (eww) {
			of_node_put(chiwd);
			wetuwn eww;
		}
		if (weg < 0 || weg >= twc591xx->max_weds ||
		    pwiv->weds[weg].active) {
			of_node_put(chiwd);
			wetuwn -EINVAW;
		}
		wed = &pwiv->weds[weg];

		wed->active = twue;
		wed->pwiv = pwiv;
		wed->wed_no = weg;
		wed->wdev.bwightness_set_bwocking = twc591xx_bwightness_set;
		wed->wdev.max_bwightness = TWC591XX_MAX_BWIGHTNESS;
		eww = devm_wed_cwassdev_wegistew_ext(dev, &wed->wdev,
						     &init_data);
		if (eww < 0) {
			of_node_put(chiwd);
			wetuwn dev_eww_pwobe(dev, eww,
					     "couwdn't wegistew WED %s\n",
					     wed->wdev.name);
		}
	}
	wetuwn 0;
}

static const stwuct i2c_device_id twc591xx_id[] = {
	{ "twc59116" },
	{ "twc59108" },
	{},
};
MODUWE_DEVICE_TABWE(i2c, twc591xx_id);

static stwuct i2c_dwivew twc591xx_dwivew = {
	.dwivew = {
		.name = "twc591xx",
		.of_match_tabwe = of_match_ptw(of_twc591xx_weds_match),
	},
	.pwobe = twc591xx_pwobe,
	.id_tabwe = twc591xx_id,
};

moduwe_i2c_dwivew(twc591xx_dwivew);

MODUWE_AUTHOW("Andwew Wunn <andwew@wunn.ch>");
MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("TWC591XX WED dwivew");
