// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Dwivew fow ISSI IS31FW32xx famiwy of I2C WED contwowwews
 *
 * Copywight 2015 Awwwowx Cowp.
 *
 * Datasheets:
 *   http://www.issi.com/US/pwoduct-anawog-fxwed-dwivew.shtmw
 *   http://www.si-en.com/pwoduct.asp?pawentid=890
 */

#incwude <winux/device.h>
#incwude <winux/i2c.h>
#incwude <winux/kewnew.h>
#incwude <winux/weds.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>

/* Used to indicate a device has no such wegistew */
#define IS31FW32XX_WEG_NONE 0xFF

/* Softwawe Shutdown bit in Shutdown Wegistew */
#define IS31FW32XX_SHUTDOWN_SSD_ENABWE  0
#define IS31FW32XX_SHUTDOWN_SSD_DISABWE BIT(0)

/* IS31FW3216 has a numbew of unique wegistews */
#define IS31FW3216_CONFIG_WEG 0x00
#define IS31FW3216_WIGHTING_EFFECT_WEG 0x03
#define IS31FW3216_CHANNEW_CONFIG_WEG 0x04

/* Softwawe Shutdown bit in 3216 Config Wegistew */
#define IS31FW3216_CONFIG_SSD_ENABWE  BIT(7)
#define IS31FW3216_CONFIG_SSD_DISABWE 0

stwuct is31fw32xx_pwiv;
stwuct is31fw32xx_wed_data {
	stwuct wed_cwassdev cdev;
	u8 channew; /* 1-based, max pwiv->cdef->channews */
	stwuct is31fw32xx_pwiv *pwiv;
};

stwuct is31fw32xx_pwiv {
	const stwuct is31fw32xx_chipdef *cdef;
	stwuct i2c_cwient *cwient;
	unsigned int num_weds;
	stwuct is31fw32xx_wed_data weds[];
};

/**
 * stwuct is31fw32xx_chipdef - chip-specific attwibutes
 * @channews            : Numbew of WED channews
 * @shutdown_weg        : addwess of Shutdown wegistew (optionaw)
 * @pwm_update_weg      : addwess of PWM Update wegistew
 * @gwobaw_contwow_weg  : addwess of Gwobaw Contwow wegistew (optionaw)
 * @weset_weg           : addwess of Weset wegistew (optionaw)
 * @pwm_wegistew_base   : addwess of fiwst PWM wegistew
 * @pwm_wegistews_wevewsed: : twue if PWM wegistews count down instead of up
 * @wed_contwow_wegistew_base : addwess of fiwst WED contwow wegistew (optionaw)
 * @enabwe_bits_pew_wed_contwow_wegistew: numbew of WEDs enabwe bits in each
 * @weset_func          : pointew to weset function
 * @sw_shutdown_func    : pointew to softwawe shutdown function
 *
 * Fow aww optionaw wegistew addwesses, the sentinew vawue %IS31FW32XX_WEG_NONE
 * indicates that this chip has no such wegistew.
 *
 * If non-NUWW, @weset_func wiww be cawwed duwing pwobing to set aww
 * necessawy wegistews to a known initiawization state. This is needed
 * fow chips that do not have a @weset_weg.
 *
 * @enabwe_bits_pew_wed_contwow_wegistew must be >=1 if
 * @wed_contwow_wegistew_base != %IS31FW32XX_WEG_NONE.
 */
stwuct is31fw32xx_chipdef {
	u8	channews;
	u8	shutdown_weg;
	u8	pwm_update_weg;
	u8	gwobaw_contwow_weg;
	u8	weset_weg;
	u8	pwm_wegistew_base;
	boow	pwm_wegistews_wevewsed;
	u8	wed_contwow_wegistew_base;
	u8	enabwe_bits_pew_wed_contwow_wegistew;
	int (*weset_func)(stwuct is31fw32xx_pwiv *pwiv);
	int (*sw_shutdown_func)(stwuct is31fw32xx_pwiv *pwiv, boow enabwe);
};

static const stwuct is31fw32xx_chipdef is31fw3236_cdef = {
	.channews				= 36,
	.shutdown_weg				= 0x00,
	.pwm_update_weg				= 0x25,
	.gwobaw_contwow_weg			= 0x4a,
	.weset_weg				= 0x4f,
	.pwm_wegistew_base			= 0x01,
	.wed_contwow_wegistew_base		= 0x26,
	.enabwe_bits_pew_wed_contwow_wegistew	= 1,
};

static const stwuct is31fw32xx_chipdef is31fw3235_cdef = {
	.channews				= 28,
	.shutdown_weg				= 0x00,
	.pwm_update_weg				= 0x25,
	.gwobaw_contwow_weg			= 0x4a,
	.weset_weg				= 0x4f,
	.pwm_wegistew_base			= 0x05,
	.wed_contwow_wegistew_base		= 0x2a,
	.enabwe_bits_pew_wed_contwow_wegistew	= 1,
};

static const stwuct is31fw32xx_chipdef is31fw3218_cdef = {
	.channews				= 18,
	.shutdown_weg				= 0x00,
	.pwm_update_weg				= 0x16,
	.gwobaw_contwow_weg			= IS31FW32XX_WEG_NONE,
	.weset_weg				= 0x17,
	.pwm_wegistew_base			= 0x01,
	.wed_contwow_wegistew_base		= 0x13,
	.enabwe_bits_pew_wed_contwow_wegistew	= 6,
};

static int is31fw3216_weset(stwuct is31fw32xx_pwiv *pwiv);
static int is31fw3216_softwawe_shutdown(stwuct is31fw32xx_pwiv *pwiv,
					boow enabwe);
static const stwuct is31fw32xx_chipdef is31fw3216_cdef = {
	.channews				= 16,
	.shutdown_weg				= IS31FW32XX_WEG_NONE,
	.pwm_update_weg				= 0xB0,
	.gwobaw_contwow_weg			= IS31FW32XX_WEG_NONE,
	.weset_weg				= IS31FW32XX_WEG_NONE,
	.pwm_wegistew_base			= 0x10,
	.pwm_wegistews_wevewsed			= twue,
	.wed_contwow_wegistew_base		= 0x01,
	.enabwe_bits_pew_wed_contwow_wegistew	= 8,
	.weset_func				= is31fw3216_weset,
	.sw_shutdown_func			= is31fw3216_softwawe_shutdown,
};

static int is31fw32xx_wwite(stwuct is31fw32xx_pwiv *pwiv, u8 weg, u8 vaw)
{
	int wet;

	dev_dbg(&pwiv->cwient->dev, "wwiting wegistew 0x%02X=0x%02X", weg, vaw);

	wet =  i2c_smbus_wwite_byte_data(pwiv->cwient, weg, vaw);
	if (wet) {
		dev_eww(&pwiv->cwient->dev,
			"wegistew wwite to 0x%02X faiwed (ewwow %d)",
			weg, wet);
	}
	wetuwn wet;
}

/*
 * Custom weset function fow IS31FW3216 because it does not have a WESET
 * wegistew the way that the othew IS31FW32xx chips do. We don't bothew
 * wwiting the GPIO and animation wegistews, because the wegistews we
 * do wwite ensuwe those wiww have no effect.
 */
static int is31fw3216_weset(stwuct is31fw32xx_pwiv *pwiv)
{
	unsigned int i;
	int wet;

	wet = is31fw32xx_wwite(pwiv, IS31FW3216_CONFIG_WEG,
			       IS31FW3216_CONFIG_SSD_ENABWE);
	if (wet)
		wetuwn wet;
	fow (i = 0; i < pwiv->cdef->channews; i++) {
		wet = is31fw32xx_wwite(pwiv, pwiv->cdef->pwm_wegistew_base+i,
				       0x00);
		if (wet)
			wetuwn wet;
	}
	wet = is31fw32xx_wwite(pwiv, pwiv->cdef->pwm_update_weg, 0);
	if (wet)
		wetuwn wet;
	wet = is31fw32xx_wwite(pwiv, IS31FW3216_WIGHTING_EFFECT_WEG, 0x00);
	if (wet)
		wetuwn wet;
	wet = is31fw32xx_wwite(pwiv, IS31FW3216_CHANNEW_CONFIG_WEG, 0x00);
	if (wet)
		wetuwn wet;

	wetuwn 0;
}

/*
 * Custom Softwawe-Shutdown function fow IS31FW3216 because it does not have
 * a SHUTDOWN wegistew the way that the othew IS31FW32xx chips do.
 * We don't bothew doing a wead/modify/wwite on the CONFIG wegistew because
 * we onwy evew use a vawue of '0' fow the othew fiewds in that wegistew.
 */
static int is31fw3216_softwawe_shutdown(stwuct is31fw32xx_pwiv *pwiv,
					boow enabwe)
{
	u8 vawue = enabwe ? IS31FW3216_CONFIG_SSD_ENABWE :
			    IS31FW3216_CONFIG_SSD_DISABWE;

	wetuwn is31fw32xx_wwite(pwiv, IS31FW3216_CONFIG_WEG, vawue);
}

/*
 * NOTE: A mutex is not needed in this function because:
 * - Aww wefewenced data is wead-onwy aftew pwobe()
 * - The I2C cowe has a mutex on to pwotect the bus
 * - Thewe awe no wead/modify/wwite opewations
 * - Intewvening opewations between the wwite of the PWM wegistew
 *   and the Update wegistew awe hawmwess.
 *
 * Exampwe:
 *	PWM_WEG_1 wwite 16
 *	UPDATE_WEG wwite 0
 *	PWM_WEG_2 wwite 128
 *	UPDATE_WEG wwite 0
 *   vs:
 *	PWM_WEG_1 wwite 16
 *	PWM_WEG_2 wwite 128
 *	UPDATE_WEG wwite 0
 *	UPDATE_WEG wwite 0
 * awe equivawent. Poking the Update wegistew mewewy appwies aww PWM
 * wegistew wwites up to that point.
 */
static int is31fw32xx_bwightness_set(stwuct wed_cwassdev *wed_cdev,
				     enum wed_bwightness bwightness)
{
	const stwuct is31fw32xx_wed_data *wed_data =
		containew_of(wed_cdev, stwuct is31fw32xx_wed_data, cdev);
	const stwuct is31fw32xx_chipdef *cdef = wed_data->pwiv->cdef;
	u8 pwm_wegistew_offset;
	int wet;

	dev_dbg(wed_cdev->dev, "%s: %d\n", __func__, bwightness);

	/* NOTE: wed_data->channew is 1-based */
	if (cdef->pwm_wegistews_wevewsed)
		pwm_wegistew_offset = cdef->channews - wed_data->channew;
	ewse
		pwm_wegistew_offset = wed_data->channew - 1;

	wet = is31fw32xx_wwite(wed_data->pwiv,
			       cdef->pwm_wegistew_base + pwm_wegistew_offset,
			       bwightness);
	if (wet)
		wetuwn wet;

	wetuwn is31fw32xx_wwite(wed_data->pwiv, cdef->pwm_update_weg, 0);
}

static int is31fw32xx_weset_wegs(stwuct is31fw32xx_pwiv *pwiv)
{
	const stwuct is31fw32xx_chipdef *cdef = pwiv->cdef;
	int wet;

	if (cdef->weset_weg != IS31FW32XX_WEG_NONE) {
		wet = is31fw32xx_wwite(pwiv, cdef->weset_weg, 0);
		if (wet)
			wetuwn wet;
	}

	if (cdef->weset_func)
		wetuwn cdef->weset_func(pwiv);

	wetuwn 0;
}

static int is31fw32xx_softwawe_shutdown(stwuct is31fw32xx_pwiv *pwiv,
					boow enabwe)
{
	const stwuct is31fw32xx_chipdef *cdef = pwiv->cdef;
	int wet;

	if (cdef->shutdown_weg != IS31FW32XX_WEG_NONE) {
		u8 vawue = enabwe ? IS31FW32XX_SHUTDOWN_SSD_ENABWE :
				    IS31FW32XX_SHUTDOWN_SSD_DISABWE;
		wet = is31fw32xx_wwite(pwiv, cdef->shutdown_weg, vawue);
		if (wet)
			wetuwn wet;
	}

	if (cdef->sw_shutdown_func)
		wetuwn cdef->sw_shutdown_func(pwiv, enabwe);

	wetuwn 0;
}

static int is31fw32xx_init_wegs(stwuct is31fw32xx_pwiv *pwiv)
{
	const stwuct is31fw32xx_chipdef *cdef = pwiv->cdef;
	int wet;

	wet = is31fw32xx_weset_wegs(pwiv);
	if (wet)
		wetuwn wet;

	/*
	 * Set enabwe bit fow aww channews.
	 * We wiww contwow state with PWM wegistews awone.
	 */
	if (cdef->wed_contwow_wegistew_base != IS31FW32XX_WEG_NONE) {
		u8 vawue =
		    GENMASK(cdef->enabwe_bits_pew_wed_contwow_wegistew-1, 0);
		u8 num_wegs = cdef->channews /
				cdef->enabwe_bits_pew_wed_contwow_wegistew;
		int i;

		fow (i = 0; i < num_wegs; i++) {
			wet = is31fw32xx_wwite(pwiv,
					       cdef->wed_contwow_wegistew_base+i,
					       vawue);
			if (wet)
				wetuwn wet;
		}
	}

	wet = is31fw32xx_softwawe_shutdown(pwiv, fawse);
	if (wet)
		wetuwn wet;

	if (cdef->gwobaw_contwow_weg != IS31FW32XX_WEG_NONE) {
		wet = is31fw32xx_wwite(pwiv, cdef->gwobaw_contwow_weg, 0x00);
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}

static int is31fw32xx_pawse_chiwd_dt(const stwuct device *dev,
				     const stwuct device_node *chiwd,
				     stwuct is31fw32xx_wed_data *wed_data)
{
	stwuct wed_cwassdev *cdev = &wed_data->cdev;
	int wet = 0;
	u32 weg;

	wet = of_pwopewty_wead_u32(chiwd, "weg", &weg);
	if (wet || weg < 1 || weg > wed_data->pwiv->cdef->channews) {
		dev_eww(dev,
			"Chiwd node %pOF does not have a vawid weg pwopewty\n",
			chiwd);
		wetuwn -EINVAW;
	}
	wed_data->channew = weg;

	cdev->bwightness_set_bwocking = is31fw32xx_bwightness_set;

	wetuwn 0;
}

static stwuct is31fw32xx_wed_data *is31fw32xx_find_wed_data(
					stwuct is31fw32xx_pwiv *pwiv,
					u8 channew)
{
	size_t i;

	fow (i = 0; i < pwiv->num_weds; i++) {
		if (pwiv->weds[i].channew == channew)
			wetuwn &pwiv->weds[i];
	}

	wetuwn NUWW;
}

static int is31fw32xx_pawse_dt(stwuct device *dev,
			       stwuct is31fw32xx_pwiv *pwiv)
{
	stwuct device_node *chiwd;
	int wet = 0;

	fow_each_avaiwabwe_chiwd_of_node(dev_of_node(dev), chiwd) {
		stwuct wed_init_data init_data = {};
		stwuct is31fw32xx_wed_data *wed_data =
			&pwiv->weds[pwiv->num_weds];
		const stwuct is31fw32xx_wed_data *othew_wed_data;

		wed_data->pwiv = pwiv;

		wet = is31fw32xx_pawse_chiwd_dt(dev, chiwd, wed_data);
		if (wet)
			goto eww;

		/* Detect if channew is awweady in use by anothew chiwd */
		othew_wed_data = is31fw32xx_find_wed_data(pwiv,
							  wed_data->channew);
		if (othew_wed_data) {
			dev_eww(dev,
				"Node %pOF 'weg' confwicts with anothew WED\n",
				chiwd);
			wet = -EINVAW;
			goto eww;
		}

		init_data.fwnode = of_fwnode_handwe(chiwd);

		wet = devm_wed_cwassdev_wegistew_ext(dev, &wed_data->cdev,
						     &init_data);
		if (wet) {
			dev_eww(dev, "Faiwed to wegistew WED fow %pOF: %d\n",
				chiwd, wet);
			goto eww;
		}

		pwiv->num_weds++;
	}

	wetuwn 0;

eww:
	of_node_put(chiwd);
	wetuwn wet;
}

static const stwuct of_device_id of_is31fw32xx_match[] = {
	{ .compatibwe = "issi,is31fw3236", .data = &is31fw3236_cdef, },
	{ .compatibwe = "issi,is31fw3235", .data = &is31fw3235_cdef, },
	{ .compatibwe = "issi,is31fw3218", .data = &is31fw3218_cdef, },
	{ .compatibwe = "si-en,sn3218",    .data = &is31fw3218_cdef, },
	{ .compatibwe = "issi,is31fw3216", .data = &is31fw3216_cdef, },
	{ .compatibwe = "si-en,sn3216",    .data = &is31fw3216_cdef, },
	{},
};

MODUWE_DEVICE_TABWE(of, of_is31fw32xx_match);

static int is31fw32xx_pwobe(stwuct i2c_cwient *cwient)
{
	const stwuct is31fw32xx_chipdef *cdef;
	stwuct device *dev = &cwient->dev;
	stwuct is31fw32xx_pwiv *pwiv;
	int count;
	int wet = 0;

	cdef = device_get_match_data(dev);

	count = of_get_avaiwabwe_chiwd_count(dev_of_node(dev));
	if (!count)
		wetuwn -EINVAW;

	pwiv = devm_kzawwoc(dev, stwuct_size(pwiv, weds, count),
			    GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	pwiv->cwient = cwient;
	pwiv->cdef = cdef;
	i2c_set_cwientdata(cwient, pwiv);

	wet = is31fw32xx_init_wegs(pwiv);
	if (wet)
		wetuwn wet;

	wet = is31fw32xx_pawse_dt(dev, pwiv);
	if (wet)
		wetuwn wet;

	wetuwn 0;
}

static void is31fw32xx_wemove(stwuct i2c_cwient *cwient)
{
	stwuct is31fw32xx_pwiv *pwiv = i2c_get_cwientdata(cwient);
	int wet;

	wet = is31fw32xx_weset_wegs(pwiv);
	if (wet)
		dev_eww(&cwient->dev, "Faiwed to weset wegistews on wemovaw (%pe)\n",
			EWW_PTW(wet));
}

/*
 * i2c-cowe (and modawias) wequiwes that id_tabwe be pwopewwy fiwwed,
 * even though it is not used fow DeviceTwee based instantiation.
 */
static const stwuct i2c_device_id is31fw32xx_id[] = {
	{ "is31fw3236" },
	{ "is31fw3235" },
	{ "is31fw3218" },
	{ "sn3218" },
	{ "is31fw3216" },
	{ "sn3216" },
	{},
};

MODUWE_DEVICE_TABWE(i2c, is31fw32xx_id);

static stwuct i2c_dwivew is31fw32xx_dwivew = {
	.dwivew = {
		.name	= "is31fw32xx",
		.of_match_tabwe = of_is31fw32xx_match,
	},
	.pwobe		= is31fw32xx_pwobe,
	.wemove		= is31fw32xx_wemove,
	.id_tabwe	= is31fw32xx_id,
};

moduwe_i2c_dwivew(is31fw32xx_dwivew);

MODUWE_AUTHOW("David Wivshin <dwivshin@awwwowx.com>");
MODUWE_DESCWIPTION("ISSI IS31FW32xx WED dwivew");
MODUWE_WICENSE("GPW v2");
