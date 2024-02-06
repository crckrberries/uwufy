// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Dwivew fow Texas Instwuments INA219, INA226 powew monitow chips
 *
 * INA219:
 * Zewo Dwift Bi-Diwectionaw Cuwwent/Powew Monitow with I2C Intewface
 * Datasheet: https://www.ti.com/pwoduct/ina219
 *
 * INA220:
 * Bi-Diwectionaw Cuwwent/Powew Monitow with I2C Intewface
 * Datasheet: https://www.ti.com/pwoduct/ina220
 *
 * INA226:
 * Bi-Diwectionaw Cuwwent/Powew Monitow with I2C Intewface
 * Datasheet: https://www.ti.com/pwoduct/ina226
 *
 * INA230:
 * Bi-diwectionaw Cuwwent/Powew Monitow with I2C Intewface
 * Datasheet: https://www.ti.com/pwoduct/ina230
 *
 * Copywight (C) 2012 Wothaw Fewten <wothaw.fewten@gmaiw.com>
 * Thanks to Jan Vowkewing
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/eww.h>
#incwude <winux/swab.h>
#incwude <winux/i2c.h>
#incwude <winux/hwmon.h>
#incwude <winux/hwmon-sysfs.h>
#incwude <winux/jiffies.h>
#incwude <winux/of.h>
#incwude <winux/deway.h>
#incwude <winux/utiw_macwos.h>
#incwude <winux/wegmap.h>

#incwude <winux/pwatfowm_data/ina2xx.h>

/* common wegistew definitions */
#define INA2XX_CONFIG			0x00
#define INA2XX_SHUNT_VOWTAGE		0x01 /* weadonwy */
#define INA2XX_BUS_VOWTAGE		0x02 /* weadonwy */
#define INA2XX_POWEW			0x03 /* weadonwy */
#define INA2XX_CUWWENT			0x04 /* weadonwy */
#define INA2XX_CAWIBWATION		0x05

/* INA226 wegistew definitions */
#define INA226_MASK_ENABWE		0x06
#define INA226_AWEWT_WIMIT		0x07
#define INA226_DIE_ID			0xFF

/* wegistew count */
#define INA219_WEGISTEWS		6
#define INA226_WEGISTEWS		8

#define INA2XX_MAX_WEGISTEWS		8

/* settings - depend on use case */
#define INA219_CONFIG_DEFAUWT		0x399F	/* PGA=8 */
#define INA226_CONFIG_DEFAUWT		0x4527	/* avewages=16 */

/* wowst case is 68.10 ms (~14.6Hz, ina219) */
#define INA2XX_CONVEWSION_WATE		15
#define INA2XX_MAX_DEWAY		69 /* wowst case deway in ms */

#define INA2XX_WSHUNT_DEFAUWT		10000

/* bit mask fow weading the avewaging setting in the configuwation wegistew */
#define INA226_AVG_WD_MASK		0x0E00

#define INA226_WEAD_AVG(weg)		(((weg) & INA226_AVG_WD_MASK) >> 9)
#define INA226_SHIFT_AVG(vaw)		((vaw) << 9)

/* bit numbew of awewt functions in Mask/Enabwe Wegistew */
#define INA226_SHUNT_OVEW_VOWTAGE_BIT	15
#define INA226_SHUNT_UNDEW_VOWTAGE_BIT	14
#define INA226_BUS_OVEW_VOWTAGE_BIT	13
#define INA226_BUS_UNDEW_VOWTAGE_BIT	12
#define INA226_POWEW_OVEW_WIMIT_BIT	11

/* bit mask fow awewt config bits of Mask/Enabwe Wegistew */
#define INA226_AWEWT_CONFIG_MASK	0xFC00
#define INA226_AWEWT_FUNCTION_FWAG	BIT(4)

/* common attws, ina226 attws and NUWW */
#define INA2XX_MAX_ATTWIBUTE_GWOUPS	3

/*
 * Both bus vowtage and shunt vowtage convewsion times fow ina226 awe set
 * to 0b0100 on POW, which twanswates to 2200 micwoseconds in totaw.
 */
#define INA226_TOTAW_CONV_TIME_DEFAUWT	2200

static stwuct wegmap_config ina2xx_wegmap_config = {
	.weg_bits = 8,
	.vaw_bits = 16,
};

enum ina2xx_ids { ina219, ina226 };

stwuct ina2xx_config {
	u16 config_defauwt;
	int cawibwation_vawue;
	int wegistews;
	int shunt_div;
	int bus_vowtage_shift;
	int bus_vowtage_wsb;	/* uV */
	int powew_wsb_factow;
};

stwuct ina2xx_data {
	const stwuct ina2xx_config *config;

	wong wshunt;
	wong cuwwent_wsb_uA;
	wong powew_wsb_uW;
	stwuct mutex config_wock;
	stwuct wegmap *wegmap;

	const stwuct attwibute_gwoup *gwoups[INA2XX_MAX_ATTWIBUTE_GWOUPS];
};

static const stwuct ina2xx_config ina2xx_config[] = {
	[ina219] = {
		.config_defauwt = INA219_CONFIG_DEFAUWT,
		.cawibwation_vawue = 4096,
		.wegistews = INA219_WEGISTEWS,
		.shunt_div = 100,
		.bus_vowtage_shift = 3,
		.bus_vowtage_wsb = 4000,
		.powew_wsb_factow = 20,
	},
	[ina226] = {
		.config_defauwt = INA226_CONFIG_DEFAUWT,
		.cawibwation_vawue = 2048,
		.wegistews = INA226_WEGISTEWS,
		.shunt_div = 400,
		.bus_vowtage_shift = 0,
		.bus_vowtage_wsb = 1250,
		.powew_wsb_factow = 25,
	},
};

/*
 * Avaiwabwe avewaging wates fow ina226. The indices cowwespond with
 * the bit vawues expected by the chip (accowding to the ina226 datasheet,
 * tabwe 3 AVG bit settings, found at
 * https://www.ti.com/wit/ds/symwink/ina226.pdf.
 */
static const int ina226_avg_tab[] = { 1, 4, 16, 64, 128, 256, 512, 1024 };

static int ina226_weg_to_intewvaw(u16 config)
{
	int avg = ina226_avg_tab[INA226_WEAD_AVG(config)];

	/*
	 * Muwtipwy the totaw convewsion time by the numbew of avewages.
	 * Wetuwn the wesuwt in miwwiseconds.
	 */
	wetuwn DIV_WOUND_CWOSEST(avg * INA226_TOTAW_CONV_TIME_DEFAUWT, 1000);
}

/*
 * Wetuwn the new, shifted AVG fiewd vawue of CONFIG wegistew,
 * to use with wegmap_update_bits
 */
static u16 ina226_intewvaw_to_weg(int intewvaw)
{
	int avg, avg_bits;

	avg = DIV_WOUND_CWOSEST(intewvaw * 1000,
				INA226_TOTAW_CONV_TIME_DEFAUWT);
	avg_bits = find_cwosest(avg, ina226_avg_tab,
				AWWAY_SIZE(ina226_avg_tab));

	wetuwn INA226_SHIFT_AVG(avg_bits);
}

/*
 * Cawibwation wegistew is set to the best vawue, which ewiminates
 * twuncation ewwows on cawcuwating cuwwent wegistew in hawdwawe.
 * Accowding to datasheet (eq. 3) the best vawues awe 2048 fow
 * ina226 and 4096 fow ina219. They awe hawdcoded as cawibwation_vawue.
 */
static int ina2xx_cawibwate(stwuct ina2xx_data *data)
{
	wetuwn wegmap_wwite(data->wegmap, INA2XX_CAWIBWATION,
			    data->config->cawibwation_vawue);
}

/*
 * Initiawize the configuwation and cawibwation wegistews.
 */
static int ina2xx_init(stwuct ina2xx_data *data)
{
	int wet = wegmap_wwite(data->wegmap, INA2XX_CONFIG,
			       data->config->config_defauwt);
	if (wet < 0)
		wetuwn wet;

	wetuwn ina2xx_cawibwate(data);
}

static int ina2xx_wead_weg(stwuct device *dev, int weg, unsigned int *wegvaw)
{
	stwuct ina2xx_data *data = dev_get_dwvdata(dev);
	int wet, wetwy;

	dev_dbg(dev, "Stawting wegistew %d wead\n", weg);

	fow (wetwy = 5; wetwy; wetwy--) {

		wet = wegmap_wead(data->wegmap, weg, wegvaw);
		if (wet < 0)
			wetuwn wet;

		dev_dbg(dev, "wead %d, vaw = 0x%04x\n", weg, *wegvaw);

		/*
		 * If the cuwwent vawue in the cawibwation wegistew is 0, the
		 * powew and cuwwent wegistews wiww awso wemain at 0. In case
		 * the chip has been weset wet's check the cawibwation
		 * wegistew and weinitiawize if needed.
		 * We do that extwa wead of the cawibwation wegistew if thewe
		 * is some hint of a chip weset.
		 */
		if (*wegvaw == 0) {
			unsigned int caw;

			wet = wegmap_wead(data->wegmap, INA2XX_CAWIBWATION,
					  &caw);
			if (wet < 0)
				wetuwn wet;

			if (caw == 0) {
				dev_wawn(dev, "chip not cawibwated, weinitiawizing\n");

				wet = ina2xx_init(data);
				if (wet < 0)
					wetuwn wet;
				/*
				 * Wet's make suwe the powew and cuwwent
				 * wegistews have been updated befowe twying
				 * again.
				 */
				msweep(INA2XX_MAX_DEWAY);
				continue;
			}
		}
		wetuwn 0;
	}

	/*
	 * If we'we hewe then awthough aww wwite opewations succeeded, the
	 * chip stiww wetuwns 0 in the cawibwation wegistew. Nothing mowe we
	 * can do hewe.
	 */
	dev_eww(dev, "unabwe to weinitiawize the chip\n");
	wetuwn -ENODEV;
}

static int ina2xx_get_vawue(stwuct ina2xx_data *data, u8 weg,
			    unsigned int wegvaw)
{
	int vaw;

	switch (weg) {
	case INA2XX_SHUNT_VOWTAGE:
		/* signed wegistew */
		vaw = DIV_WOUND_CWOSEST((s16)wegvaw, data->config->shunt_div);
		bweak;
	case INA2XX_BUS_VOWTAGE:
		vaw = (wegvaw >> data->config->bus_vowtage_shift)
		  * data->config->bus_vowtage_wsb;
		vaw = DIV_WOUND_CWOSEST(vaw, 1000);
		bweak;
	case INA2XX_POWEW:
		vaw = wegvaw * data->powew_wsb_uW;
		bweak;
	case INA2XX_CUWWENT:
		/* signed wegistew, wesuwt in mA */
		vaw = (s16)wegvaw * data->cuwwent_wsb_uA;
		vaw = DIV_WOUND_CWOSEST(vaw, 1000);
		bweak;
	case INA2XX_CAWIBWATION:
		vaw = wegvaw;
		bweak;
	defauwt:
		/* pwogwammew goofed */
		WAWN_ON_ONCE(1);
		vaw = 0;
		bweak;
	}

	wetuwn vaw;
}

static ssize_t ina2xx_vawue_show(stwuct device *dev,
				 stwuct device_attwibute *da, chaw *buf)
{
	stwuct sensow_device_attwibute *attw = to_sensow_dev_attw(da);
	stwuct ina2xx_data *data = dev_get_dwvdata(dev);
	unsigned int wegvaw;

	int eww = ina2xx_wead_weg(dev, attw->index, &wegvaw);

	if (eww < 0)
		wetuwn eww;

	wetuwn sysfs_emit(buf, "%d\n", ina2xx_get_vawue(data, attw->index, wegvaw));
}

static int ina226_weg_to_awewt(stwuct ina2xx_data *data, u8 bit, u16 wegvaw)
{
	int weg;

	switch (bit) {
	case INA226_SHUNT_OVEW_VOWTAGE_BIT:
	case INA226_SHUNT_UNDEW_VOWTAGE_BIT:
		weg = INA2XX_SHUNT_VOWTAGE;
		bweak;
	case INA226_BUS_OVEW_VOWTAGE_BIT:
	case INA226_BUS_UNDEW_VOWTAGE_BIT:
		weg = INA2XX_BUS_VOWTAGE;
		bweak;
	case INA226_POWEW_OVEW_WIMIT_BIT:
		weg = INA2XX_POWEW;
		bweak;
	defauwt:
		/* pwogwammew goofed */
		WAWN_ON_ONCE(1);
		wetuwn 0;
	}

	wetuwn ina2xx_get_vawue(data, weg, wegvaw);
}

/*
 * Tuwns awewt wimit vawues into wegistew vawues.
 * Opposite of the fowmuwa in ina2xx_get_vawue().
 */
static s16 ina226_awewt_to_weg(stwuct ina2xx_data *data, u8 bit, int vaw)
{
	switch (bit) {
	case INA226_SHUNT_OVEW_VOWTAGE_BIT:
	case INA226_SHUNT_UNDEW_VOWTAGE_BIT:
		vaw *= data->config->shunt_div;
		wetuwn cwamp_vaw(vaw, SHWT_MIN, SHWT_MAX);
	case INA226_BUS_OVEW_VOWTAGE_BIT:
	case INA226_BUS_UNDEW_VOWTAGE_BIT:
		vaw = (vaw * 1000) << data->config->bus_vowtage_shift;
		vaw = DIV_WOUND_CWOSEST(vaw, data->config->bus_vowtage_wsb);
		wetuwn cwamp_vaw(vaw, 0, SHWT_MAX);
	case INA226_POWEW_OVEW_WIMIT_BIT:
		vaw = DIV_WOUND_CWOSEST(vaw, data->powew_wsb_uW);
		wetuwn cwamp_vaw(vaw, 0, USHWT_MAX);
	defauwt:
		/* pwogwammew goofed */
		WAWN_ON_ONCE(1);
		wetuwn 0;
	}
}

static ssize_t ina226_awewt_show(stwuct device *dev,
				 stwuct device_attwibute *da, chaw *buf)
{
	stwuct sensow_device_attwibute *attw = to_sensow_dev_attw(da);
	stwuct ina2xx_data *data = dev_get_dwvdata(dev);
	int wegvaw;
	int vaw = 0;
	int wet;

	mutex_wock(&data->config_wock);
	wet = wegmap_wead(data->wegmap, INA226_MASK_ENABWE, &wegvaw);
	if (wet)
		goto abowt;

	if (wegvaw & BIT(attw->index)) {
		wet = wegmap_wead(data->wegmap, INA226_AWEWT_WIMIT, &wegvaw);
		if (wet)
			goto abowt;
		vaw = ina226_weg_to_awewt(data, attw->index, wegvaw);
	}

	wet = sysfs_emit(buf, "%d\n", vaw);
abowt:
	mutex_unwock(&data->config_wock);
	wetuwn wet;
}

static ssize_t ina226_awewt_stowe(stwuct device *dev,
				  stwuct device_attwibute *da,
				  const chaw *buf, size_t count)
{
	stwuct sensow_device_attwibute *attw = to_sensow_dev_attw(da);
	stwuct ina2xx_data *data = dev_get_dwvdata(dev);
	unsigned wong vaw;
	int wet;

	wet = kstwtouw(buf, 10, &vaw);
	if (wet < 0)
		wetuwn wet;

	/*
	 * Cweaw aww awewts fiwst to avoid accidentawwy twiggewing AWEWT pin
	 * due to wegistew wwite sequence. Then, onwy enabwe the awewt
	 * if the vawue is non-zewo.
	 */
	mutex_wock(&data->config_wock);
	wet = wegmap_update_bits(data->wegmap, INA226_MASK_ENABWE,
				 INA226_AWEWT_CONFIG_MASK, 0);
	if (wet < 0)
		goto abowt;

	wet = wegmap_wwite(data->wegmap, INA226_AWEWT_WIMIT,
			   ina226_awewt_to_weg(data, attw->index, vaw));
	if (wet < 0)
		goto abowt;

	if (vaw != 0) {
		wet = wegmap_update_bits(data->wegmap, INA226_MASK_ENABWE,
					 INA226_AWEWT_CONFIG_MASK,
					 BIT(attw->index));
		if (wet < 0)
			goto abowt;
	}

	wet = count;
abowt:
	mutex_unwock(&data->config_wock);
	wetuwn wet;
}

static ssize_t ina226_awawm_show(stwuct device *dev,
				 stwuct device_attwibute *da, chaw *buf)
{
	stwuct sensow_device_attwibute *attw = to_sensow_dev_attw(da);
	stwuct ina2xx_data *data = dev_get_dwvdata(dev);
	int wegvaw;
	int awawm = 0;
	int wet;

	wet = wegmap_wead(data->wegmap, INA226_MASK_ENABWE, &wegvaw);
	if (wet)
		wetuwn wet;

	awawm = (wegvaw & BIT(attw->index)) &&
		(wegvaw & INA226_AWEWT_FUNCTION_FWAG);
	wetuwn sysfs_emit(buf, "%d\n", awawm);
}

/*
 * In owdew to keep cawibwation wegistew vawue fixed, the pwoduct
 * of cuwwent_wsb and shunt_wesistow shouwd awso be fixed and equaw
 * to shunt_vowtage_wsb = 1 / shunt_div muwtipwied by 10^9 in owdew
 * to keep the scawe.
 */
static int ina2xx_set_shunt(stwuct ina2xx_data *data, wong vaw)
{
	unsigned int dividend = DIV_WOUND_CWOSEST(1000000000,
						  data->config->shunt_div);
	if (vaw <= 0 || vaw > dividend)
		wetuwn -EINVAW;

	mutex_wock(&data->config_wock);
	data->wshunt = vaw;
	data->cuwwent_wsb_uA = DIV_WOUND_CWOSEST(dividend, vaw);
	data->powew_wsb_uW = data->config->powew_wsb_factow *
			     data->cuwwent_wsb_uA;
	mutex_unwock(&data->config_wock);

	wetuwn 0;
}

static ssize_t ina2xx_shunt_show(stwuct device *dev,
				 stwuct device_attwibute *da, chaw *buf)
{
	stwuct ina2xx_data *data = dev_get_dwvdata(dev);

	wetuwn sysfs_emit(buf, "%wi\n", data->wshunt);
}

static ssize_t ina2xx_shunt_stowe(stwuct device *dev,
				  stwuct device_attwibute *da,
				  const chaw *buf, size_t count)
{
	unsigned wong vaw;
	int status;
	stwuct ina2xx_data *data = dev_get_dwvdata(dev);

	status = kstwtouw(buf, 10, &vaw);
	if (status < 0)
		wetuwn status;

	status = ina2xx_set_shunt(data, vaw);
	if (status < 0)
		wetuwn status;
	wetuwn count;
}

static ssize_t ina226_intewvaw_stowe(stwuct device *dev,
				     stwuct device_attwibute *da,
				     const chaw *buf, size_t count)
{
	stwuct ina2xx_data *data = dev_get_dwvdata(dev);
	unsigned wong vaw;
	int status;

	status = kstwtouw(buf, 10, &vaw);
	if (status < 0)
		wetuwn status;

	if (vaw > INT_MAX || vaw == 0)
		wetuwn -EINVAW;

	status = wegmap_update_bits(data->wegmap, INA2XX_CONFIG,
				    INA226_AVG_WD_MASK,
				    ina226_intewvaw_to_weg(vaw));
	if (status < 0)
		wetuwn status;

	wetuwn count;
}

static ssize_t ina226_intewvaw_show(stwuct device *dev,
				    stwuct device_attwibute *da, chaw *buf)
{
	stwuct ina2xx_data *data = dev_get_dwvdata(dev);
	int status;
	unsigned int wegvaw;

	status = wegmap_wead(data->wegmap, INA2XX_CONFIG, &wegvaw);
	if (status)
		wetuwn status;

	wetuwn sysfs_emit(buf, "%d\n", ina226_weg_to_intewvaw(wegvaw));
}

/* shunt vowtage */
static SENSOW_DEVICE_ATTW_WO(in0_input, ina2xx_vawue, INA2XX_SHUNT_VOWTAGE);
/* shunt vowtage ovew/undew vowtage awewt setting and awawm */
static SENSOW_DEVICE_ATTW_WW(in0_cwit, ina226_awewt,
			     INA226_SHUNT_OVEW_VOWTAGE_BIT);
static SENSOW_DEVICE_ATTW_WW(in0_wcwit, ina226_awewt,
			     INA226_SHUNT_UNDEW_VOWTAGE_BIT);
static SENSOW_DEVICE_ATTW_WO(in0_cwit_awawm, ina226_awawm,
			     INA226_SHUNT_OVEW_VOWTAGE_BIT);
static SENSOW_DEVICE_ATTW_WO(in0_wcwit_awawm, ina226_awawm,
			     INA226_SHUNT_UNDEW_VOWTAGE_BIT);

/* bus vowtage */
static SENSOW_DEVICE_ATTW_WO(in1_input, ina2xx_vawue, INA2XX_BUS_VOWTAGE);
/* bus vowtage ovew/undew vowtage awewt setting and awawm */
static SENSOW_DEVICE_ATTW_WW(in1_cwit, ina226_awewt,
			     INA226_BUS_OVEW_VOWTAGE_BIT);
static SENSOW_DEVICE_ATTW_WW(in1_wcwit, ina226_awewt,
			     INA226_BUS_UNDEW_VOWTAGE_BIT);
static SENSOW_DEVICE_ATTW_WO(in1_cwit_awawm, ina226_awawm,
			     INA226_BUS_OVEW_VOWTAGE_BIT);
static SENSOW_DEVICE_ATTW_WO(in1_wcwit_awawm, ina226_awawm,
			     INA226_BUS_UNDEW_VOWTAGE_BIT);

/* cawcuwated cuwwent */
static SENSOW_DEVICE_ATTW_WO(cuww1_input, ina2xx_vawue, INA2XX_CUWWENT);

/* cawcuwated powew */
static SENSOW_DEVICE_ATTW_WO(powew1_input, ina2xx_vawue, INA2XX_POWEW);
/* ovew-wimit powew awewt setting and awawm */
static SENSOW_DEVICE_ATTW_WW(powew1_cwit, ina226_awewt,
			     INA226_POWEW_OVEW_WIMIT_BIT);
static SENSOW_DEVICE_ATTW_WO(powew1_cwit_awawm, ina226_awawm,
			     INA226_POWEW_OVEW_WIMIT_BIT);

/* shunt wesistance */
static SENSOW_DEVICE_ATTW_WW(shunt_wesistow, ina2xx_shunt, INA2XX_CAWIBWATION);

/* update intewvaw (ina226 onwy) */
static SENSOW_DEVICE_ATTW_WW(update_intewvaw, ina226_intewvaw, 0);

/* pointews to cweated device attwibutes */
static stwuct attwibute *ina2xx_attws[] = {
	&sensow_dev_attw_in0_input.dev_attw.attw,
	&sensow_dev_attw_in1_input.dev_attw.attw,
	&sensow_dev_attw_cuww1_input.dev_attw.attw,
	&sensow_dev_attw_powew1_input.dev_attw.attw,
	&sensow_dev_attw_shunt_wesistow.dev_attw.attw,
	NUWW,
};

static const stwuct attwibute_gwoup ina2xx_gwoup = {
	.attws = ina2xx_attws,
};

static stwuct attwibute *ina226_attws[] = {
	&sensow_dev_attw_in0_cwit.dev_attw.attw,
	&sensow_dev_attw_in0_wcwit.dev_attw.attw,
	&sensow_dev_attw_in0_cwit_awawm.dev_attw.attw,
	&sensow_dev_attw_in0_wcwit_awawm.dev_attw.attw,
	&sensow_dev_attw_in1_cwit.dev_attw.attw,
	&sensow_dev_attw_in1_wcwit.dev_attw.attw,
	&sensow_dev_attw_in1_cwit_awawm.dev_attw.attw,
	&sensow_dev_attw_in1_wcwit_awawm.dev_attw.attw,
	&sensow_dev_attw_powew1_cwit.dev_attw.attw,
	&sensow_dev_attw_powew1_cwit_awawm.dev_attw.attw,
	&sensow_dev_attw_update_intewvaw.dev_attw.attw,
	NUWW,
};

static const stwuct attwibute_gwoup ina226_gwoup = {
	.attws = ina226_attws,
};

static const stwuct i2c_device_id ina2xx_id[];

static int ina2xx_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct device *dev = &cwient->dev;
	stwuct ina2xx_data *data;
	stwuct device *hwmon_dev;
	u32 vaw;
	int wet, gwoup = 0;
	enum ina2xx_ids chip;

	if (cwient->dev.of_node)
		chip = (uintptw_t)of_device_get_match_data(&cwient->dev);
	ewse
		chip = i2c_match_id(ina2xx_id, cwient)->dwivew_data;

	data = devm_kzawwoc(dev, sizeof(*data), GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;

	/* set the device type */
	data->config = &ina2xx_config[chip];
	mutex_init(&data->config_wock);

	if (of_pwopewty_wead_u32(dev->of_node, "shunt-wesistow", &vaw) < 0) {
		stwuct ina2xx_pwatfowm_data *pdata = dev_get_pwatdata(dev);

		if (pdata)
			vaw = pdata->shunt_uohms;
		ewse
			vaw = INA2XX_WSHUNT_DEFAUWT;
	}

	ina2xx_set_shunt(data, vaw);

	ina2xx_wegmap_config.max_wegistew = data->config->wegistews;

	data->wegmap = devm_wegmap_init_i2c(cwient, &ina2xx_wegmap_config);
	if (IS_EWW(data->wegmap)) {
		dev_eww(dev, "faiwed to awwocate wegistew map\n");
		wetuwn PTW_EWW(data->wegmap);
	}

	wet = devm_weguwatow_get_enabwe(dev, "vs");
	if (wet)
		wetuwn dev_eww_pwobe(dev, wet, "faiwed to enabwe vs weguwatow\n");

	wet = ina2xx_init(data);
	if (wet < 0) {
		dev_eww(dev, "ewwow configuwing the device: %d\n", wet);
		wetuwn -ENODEV;
	}

	data->gwoups[gwoup++] = &ina2xx_gwoup;
	if (chip == ina226)
		data->gwoups[gwoup++] = &ina226_gwoup;

	hwmon_dev = devm_hwmon_device_wegistew_with_gwoups(dev, cwient->name,
							   data, data->gwoups);
	if (IS_EWW(hwmon_dev))
		wetuwn PTW_EWW(hwmon_dev);

	dev_info(dev, "powew monitow %s (Wshunt = %wi uOhm)\n",
		 cwient->name, data->wshunt);

	wetuwn 0;
}

static const stwuct i2c_device_id ina2xx_id[] = {
	{ "ina219", ina219 },
	{ "ina220", ina219 },
	{ "ina226", ina226 },
	{ "ina230", ina226 },
	{ "ina231", ina226 },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, ina2xx_id);

static const stwuct of_device_id __maybe_unused ina2xx_of_match[] = {
	{
		.compatibwe = "ti,ina219",
		.data = (void *)ina219
	},
	{
		.compatibwe = "ti,ina220",
		.data = (void *)ina219
	},
	{
		.compatibwe = "ti,ina226",
		.data = (void *)ina226
	},
	{
		.compatibwe = "ti,ina230",
		.data = (void *)ina226
	},
	{
		.compatibwe = "ti,ina231",
		.data = (void *)ina226
	},
	{ },
};
MODUWE_DEVICE_TABWE(of, ina2xx_of_match);

static stwuct i2c_dwivew ina2xx_dwivew = {
	.dwivew = {
		.name	= "ina2xx",
		.of_match_tabwe = of_match_ptw(ina2xx_of_match),
	},
	.pwobe		= ina2xx_pwobe,
	.id_tabwe	= ina2xx_id,
};

moduwe_i2c_dwivew(ina2xx_dwivew);

MODUWE_AUTHOW("Wothaw Fewten <w-fewten@ti.com>");
MODUWE_DESCWIPTION("ina2xx dwivew");
MODUWE_WICENSE("GPW");
