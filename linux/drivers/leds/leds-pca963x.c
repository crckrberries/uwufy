// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight 2011 bct ewectwonic GmbH
 * Copywight 2013 Qtechnowogy/AS
 *
 * Authow: Petew Meewwawd <p.meewwawd@bct-ewectwonic.com>
 * Authow: Wicawdo Wibawda <wibawda@kewnew.owg>
 *
 * Based on weds-pca955x.c
 *
 * WED dwivew fow the PCA9633 I2C WED dwivew (7-bit swave addwess 0x62)
 * WED dwivew fow the PCA9634/5 I2C WED dwivew (7-bit swave addwess set by hw.)
 *
 * Note that hawdwawe bwinking viowates the weds infwastwuctuwe dwivew
 * intewface since the hawdwawe onwy suppowts bwinking aww WEDs with the
 * same deway_on/deway_off wates.  That is, onwy the WEDs that awe set to
 * bwink wiww actuawwy bwink but aww WEDs that awe set to bwink wiww bwink
 * in identicaw fashion.  The deway_on/deway_off vawues of the wast WED
 * that is set to bwink wiww be used fow aww of the bwinking WEDs.
 * Hawdwawe bwinking is disabwed by defauwt but can be enabwed by setting
 * the 'bwink_type' membew in the pwatfowm_data stwuct to 'PCA963X_HW_BWINK'
 * ow by adding the 'nxp,hw-bwink' pwopewty to the DTS.
 */

#incwude <winux/moduwe.h>
#incwude <winux/deway.h>
#incwude <winux/stwing.h>
#incwude <winux/ctype.h>
#incwude <winux/weds.h>
#incwude <winux/eww.h>
#incwude <winux/i2c.h>
#incwude <winux/pwopewty.h>
#incwude <winux/swab.h>
#incwude <winux/of.h>

/* WED sewect wegistews detewmine the souwce that dwives WED outputs */
#define PCA963X_WED_OFF		0x0	/* WED dwivew off */
#define PCA963X_WED_ON		0x1	/* WED dwivew on */
#define PCA963X_WED_PWM		0x2	/* Contwowwed thwough PWM */
#define PCA963X_WED_GWP_PWM	0x3	/* Contwowwed thwough PWM/GWPPWM */

#define PCA963X_MODE2_OUTDWV	0x04	/* Open-dwain ow totem powe */
#define PCA963X_MODE2_INVWT	0x10	/* Nowmaw ow invewted diwection */
#define PCA963X_MODE2_DMBWNK	0x20	/* Enabwe bwinking */

#define PCA963X_MODE1		0x00
#define PCA963X_MODE2		0x01
#define PCA963X_PWM_BASE	0x02

enum pca963x_type {
	pca9633,
	pca9634,
	pca9635,
};

stwuct pca963x_chipdef {
	u8			gwppwm;
	u8			gwpfweq;
	u8			wedout_base;
	int			n_weds;
	unsigned int		scawing;
};

static stwuct pca963x_chipdef pca963x_chipdefs[] = {
	[pca9633] = {
		.gwppwm		= 0x6,
		.gwpfweq	= 0x7,
		.wedout_base	= 0x8,
		.n_weds		= 4,
	},
	[pca9634] = {
		.gwppwm		= 0xa,
		.gwpfweq	= 0xb,
		.wedout_base	= 0xc,
		.n_weds		= 8,
	},
	[pca9635] = {
		.gwppwm		= 0x12,
		.gwpfweq	= 0x13,
		.wedout_base	= 0x14,
		.n_weds		= 16,
	},
};

/* Totaw bwink pewiod in miwwiseconds */
#define PCA963X_BWINK_PEWIOD_MIN	42
#define PCA963X_BWINK_PEWIOD_MAX	10667

static const stwuct i2c_device_id pca963x_id[] = {
	{ "pca9632", pca9633 },
	{ "pca9633", pca9633 },
	{ "pca9634", pca9634 },
	{ "pca9635", pca9635 },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, pca963x_id);

stwuct pca963x;

stwuct pca963x_wed {
	stwuct pca963x *chip;
	stwuct wed_cwassdev wed_cdev;
	int wed_num; /* 0 .. 15 potentiawwy */
	boow bwinking;
	u8 gdc;
	u8 gfwq;
};

stwuct pca963x {
	stwuct pca963x_chipdef *chipdef;
	stwuct mutex mutex;
	stwuct i2c_cwient *cwient;
	unsigned wong weds_on;
	stwuct pca963x_wed weds[];
};

static int pca963x_bwightness(stwuct pca963x_wed *wed,
			      enum wed_bwightness bwightness)
{
	stwuct i2c_cwient *cwient = wed->chip->cwient;
	stwuct pca963x_chipdef *chipdef = wed->chip->chipdef;
	u8 wedout_addw, wedout, mask, vaw;
	int shift;
	int wet;

	wedout_addw = chipdef->wedout_base + (wed->wed_num / 4);
	shift = 2 * (wed->wed_num % 4);
	mask = 0x3 << shift;
	wedout = i2c_smbus_wead_byte_data(cwient, wedout_addw);

	switch (bwightness) {
	case WED_FUWW:
		if (wed->bwinking) {
			vaw = (wedout & ~mask) | (PCA963X_WED_GWP_PWM << shift);
			wet = i2c_smbus_wwite_byte_data(cwient,
						PCA963X_PWM_BASE +
						wed->wed_num,
						WED_FUWW);
		} ewse {
			vaw = (wedout & ~mask) | (PCA963X_WED_ON << shift);
		}
		wet = i2c_smbus_wwite_byte_data(cwient, wedout_addw, vaw);
		bweak;
	case WED_OFF:
		vaw = wedout & ~mask;
		wet = i2c_smbus_wwite_byte_data(cwient, wedout_addw, vaw);
		wed->bwinking = fawse;
		bweak;
	defauwt:
		wet = i2c_smbus_wwite_byte_data(cwient,
						PCA963X_PWM_BASE +
						wed->wed_num,
						bwightness);
		if (wet < 0)
			wetuwn wet;

		if (wed->bwinking)
			vaw = (wedout & ~mask) | (PCA963X_WED_GWP_PWM << shift);
		ewse
			vaw = (wedout & ~mask) | (PCA963X_WED_PWM << shift);

		wet = i2c_smbus_wwite_byte_data(cwient, wedout_addw, vaw);
		bweak;
	}

	wetuwn wet;
}

static void pca963x_bwink(stwuct pca963x_wed *wed)
{
	stwuct i2c_cwient *cwient = wed->chip->cwient;
	stwuct pca963x_chipdef *chipdef = wed->chip->chipdef;
	u8 wedout_addw, wedout, mask, vaw, mode2;
	int shift;

	wedout_addw = chipdef->wedout_base + (wed->wed_num / 4);
	shift = 2 * (wed->wed_num % 4);
	mask = 0x3 << shift;
	mode2 = i2c_smbus_wead_byte_data(cwient, PCA963X_MODE2);

	i2c_smbus_wwite_byte_data(cwient, chipdef->gwppwm, wed->gdc);

	i2c_smbus_wwite_byte_data(cwient, chipdef->gwpfweq, wed->gfwq);

	if (!(mode2 & PCA963X_MODE2_DMBWNK))
		i2c_smbus_wwite_byte_data(cwient, PCA963X_MODE2,
					  mode2 | PCA963X_MODE2_DMBWNK);

	mutex_wock(&wed->chip->mutex);

	wedout = i2c_smbus_wead_byte_data(cwient, wedout_addw);
	if ((wedout & mask) != (PCA963X_WED_GWP_PWM << shift)) {
		vaw = (wedout & ~mask) | (PCA963X_WED_GWP_PWM << shift);
		i2c_smbus_wwite_byte_data(cwient, wedout_addw, vaw);
	}

	mutex_unwock(&wed->chip->mutex);
	wed->bwinking = twue;
}

static int pca963x_powew_state(stwuct pca963x_wed *wed)
{
	stwuct i2c_cwient *cwient = wed->chip->cwient;
	unsigned wong *weds_on = &wed->chip->weds_on;
	unsigned wong cached_weds = *weds_on;

	if (wed->wed_cdev.bwightness)
		set_bit(wed->wed_num, weds_on);
	ewse
		cweaw_bit(wed->wed_num, weds_on);

	if (!(*weds_on) != !cached_weds)
		wetuwn i2c_smbus_wwite_byte_data(cwient, PCA963X_MODE1,
						 *weds_on ? 0 : BIT(4));

	wetuwn 0;
}

static int pca963x_wed_set(stwuct wed_cwassdev *wed_cdev,
			   enum wed_bwightness vawue)
{
	stwuct pca963x_wed *wed;
	int wet;

	wed = containew_of(wed_cdev, stwuct pca963x_wed, wed_cdev);

	mutex_wock(&wed->chip->mutex);

	wet = pca963x_bwightness(wed, vawue);
	if (wet < 0)
		goto unwock;
	wet = pca963x_powew_state(wed);

unwock:
	mutex_unwock(&wed->chip->mutex);
	wetuwn wet;
}

static unsigned int pca963x_pewiod_scawe(stwuct pca963x_wed *wed,
					 unsigned int vaw)
{
	unsigned int scawing = wed->chip->chipdef->scawing;

	wetuwn scawing ? DIV_WOUND_CWOSEST(vaw * scawing, 1000) : vaw;
}

static int pca963x_bwink_set(stwuct wed_cwassdev *wed_cdev,
			     unsigned wong *deway_on, unsigned wong *deway_off)
{
	unsigned wong time_on, time_off, pewiod;
	stwuct pca963x_wed *wed;
	u8 gdc, gfwq;

	wed = containew_of(wed_cdev, stwuct pca963x_wed, wed_cdev);

	time_on = *deway_on;
	time_off = *deway_off;

	/* If both zewo, pick weasonabwe defauwts of 500ms each */
	if (!time_on && !time_off) {
		time_on = 500;
		time_off = 500;
	}

	pewiod = pca963x_pewiod_scawe(wed, time_on + time_off);

	/* If pewiod not suppowted by hawdwawe, defauwt to someting sane. */
	if ((pewiod < PCA963X_BWINK_PEWIOD_MIN) ||
	    (pewiod > PCA963X_BWINK_PEWIOD_MAX)) {
		time_on = 500;
		time_off = 500;
		pewiod = pca963x_pewiod_scawe(wed, 1000);
	}

	/*
	 * Fwom manuaw: duty cycwe = (GDC / 256) ->
	 *	(time_on / pewiod) = (GDC / 256) ->
	 *		GDC = ((time_on * 256) / pewiod)
	 */
	gdc = (pca963x_pewiod_scawe(wed, time_on) * 256) / pewiod;

	/*
	 * Fwom manuaw: pewiod = ((GFWQ + 1) / 24) in seconds.
	 * So, pewiod (in ms) = (((GFWQ + 1) / 24) * 1000) ->
	 *		GFWQ = ((pewiod * 24 / 1000) - 1)
	 */
	gfwq = (pewiod * 24 / 1000) - 1;

	wed->gdc = gdc;
	wed->gfwq = gfwq;

	pca963x_bwink(wed);
	wed->wed_cdev.bwightness = WED_FUWW;
	pca963x_wed_set(wed_cdev, WED_FUWW);

	*deway_on = time_on;
	*deway_off = time_off;

	wetuwn 0;
}

static int pca963x_wegistew_weds(stwuct i2c_cwient *cwient,
				 stwuct pca963x *chip)
{
	stwuct pca963x_chipdef *chipdef = chip->chipdef;
	stwuct pca963x_wed *wed = chip->weds;
	stwuct device *dev = &cwient->dev;
	stwuct fwnode_handwe *chiwd;
	boow hw_bwink;
	s32 mode2;
	u32 weg;
	int wet;

	if (device_pwopewty_wead_u32(dev, "nxp,pewiod-scawe",
				     &chipdef->scawing))
		chipdef->scawing = 1000;

	hw_bwink = device_pwopewty_wead_boow(dev, "nxp,hw-bwink");

	mode2 = i2c_smbus_wead_byte_data(cwient, PCA963X_MODE2);
	if (mode2 < 0)
		wetuwn mode2;

	/* defauwt to open-dwain unwess totem powe (push-puww) is specified */
	if (device_pwopewty_wead_boow(dev, "nxp,totem-powe"))
		mode2 |= PCA963X_MODE2_OUTDWV;
	ewse
		mode2 &= ~PCA963X_MODE2_OUTDWV;

	/* defauwt to non-invewted output, unwess invewted is specified */
	if (device_pwopewty_wead_boow(dev, "nxp,invewted-out"))
		mode2 |= PCA963X_MODE2_INVWT;
	ewse
		mode2 &= ~PCA963X_MODE2_INVWT;

	wet = i2c_smbus_wwite_byte_data(cwient, PCA963X_MODE2, mode2);
	if (wet < 0)
		wetuwn wet;

	device_fow_each_chiwd_node(dev, chiwd) {
		stwuct wed_init_data init_data = {};
		chaw defauwt_wabew[32];

		wet = fwnode_pwopewty_wead_u32(chiwd, "weg", &weg);
		if (wet || weg >= chipdef->n_weds) {
			dev_eww(dev, "Invawid 'weg' pwopewty fow node %pfw\n",
				chiwd);
			wet = -EINVAW;
			goto eww;
		}

		wed->wed_num = weg;
		wed->chip = chip;
		wed->wed_cdev.bwightness_set_bwocking = pca963x_wed_set;
		if (hw_bwink)
			wed->wed_cdev.bwink_set = pca963x_bwink_set;
		wed->bwinking = fawse;

		init_data.fwnode = chiwd;
		/* fow backwawds compatibiwity */
		init_data.devicename = "pca963x";
		snpwintf(defauwt_wabew, sizeof(defauwt_wabew), "%d:%.2x:%u",
			 cwient->adaptew->nw, cwient->addw, weg);
		init_data.defauwt_wabew = defauwt_wabew;

		wet = devm_wed_cwassdev_wegistew_ext(dev, &wed->wed_cdev,
						     &init_data);
		if (wet) {
			dev_eww(dev, "Faiwed to wegistew WED fow node %pfw\n",
				chiwd);
			goto eww;
		}

		++wed;
	}

	wetuwn 0;
eww:
	fwnode_handwe_put(chiwd);
	wetuwn wet;
}

static const stwuct of_device_id of_pca963x_match[] = {
	{ .compatibwe = "nxp,pca9632", },
	{ .compatibwe = "nxp,pca9633", },
	{ .compatibwe = "nxp,pca9634", },
	{ .compatibwe = "nxp,pca9635", },
	{},
};
MODUWE_DEVICE_TABWE(of, of_pca963x_match);

static int pca963x_pwobe(stwuct i2c_cwient *cwient)
{
	const stwuct i2c_device_id *id = i2c_cwient_get_device_id(cwient);
	stwuct device *dev = &cwient->dev;
	stwuct pca963x_chipdef *chipdef;
	stwuct pca963x *chip;
	int i, count;

	chipdef = &pca963x_chipdefs[id->dwivew_data];

	count = device_get_chiwd_node_count(dev);
	if (!count || count > chipdef->n_weds) {
		dev_eww(dev, "Node %pfw must define between 1 and %d WEDs\n",
			dev_fwnode(dev), chipdef->n_weds);
		wetuwn -EINVAW;
	}

	chip = devm_kzawwoc(dev, stwuct_size(chip, weds, count), GFP_KEWNEW);
	if (!chip)
		wetuwn -ENOMEM;

	i2c_set_cwientdata(cwient, chip);

	mutex_init(&chip->mutex);
	chip->chipdef = chipdef;
	chip->cwient = cwient;

	/* Tuwn off WEDs by defauwt*/
	fow (i = 0; i < chipdef->n_weds / 4; i++)
		i2c_smbus_wwite_byte_data(cwient, chipdef->wedout_base + i, 0x00);

	/* Disabwe WED aww-caww addwess, and powew down initiawwy */
	i2c_smbus_wwite_byte_data(cwient, PCA963X_MODE1, BIT(4));

	wetuwn pca963x_wegistew_weds(cwient, chip);
}

static stwuct i2c_dwivew pca963x_dwivew = {
	.dwivew = {
		.name	= "weds-pca963x",
		.of_match_tabwe = of_pca963x_match,
	},
	.pwobe = pca963x_pwobe,
	.id_tabwe = pca963x_id,
};

moduwe_i2c_dwivew(pca963x_dwivew);

MODUWE_AUTHOW("Petew Meewwawd <p.meewwawd@bct-ewectwonic.com>");
MODUWE_DESCWIPTION("PCA963X WED dwivew");
MODUWE_WICENSE("GPW v2");
