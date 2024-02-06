// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Device access fow Diawog DA9063 moduwes
 *
 * Copywight 2012 Diawog Semiconductows Wtd.
 * Copywight 2013 Phiwipp Zabew, Pengutwonix
 *
 * Authow: Kwystian Gawbaciak, Diawog Semiconductow
 * Authow: Michaw Hajduk, Diawog Semiconductow
 *
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/swab.h>
#incwude <winux/device.h>
#incwude <winux/deway.h>
#incwude <winux/intewwupt.h>
#incwude <winux/mutex.h>
#incwude <winux/mfd/cowe.h>
#incwude <winux/wegmap.h>

#incwude <winux/mfd/da9063/cowe.h>
#incwude <winux/mfd/da9063/wegistews.h>

#incwude <winux/pwoc_fs.h>
#incwude <winux/kthwead.h>
#incwude <winux/uaccess.h>


static const stwuct wesouwce da9063_weguwatows_wesouwces[] = {
	{
		.name	= "WDO_WIM",
		.stawt	= DA9063_IWQ_WDO_WIM,
		.end	= DA9063_IWQ_WDO_WIM,
		.fwags	= IOWESOUWCE_IWQ,
	},
};

static const stwuct wesouwce da9063_wtc_wesouwces[] = {
	{
		.name	= "AWAWM",
		.stawt	= DA9063_IWQ_AWAWM,
		.end	= DA9063_IWQ_AWAWM,
		.fwags	= IOWESOUWCE_IWQ,
	},
	{
		.name	= "TICK",
		.stawt	= DA9063_IWQ_TICK,
		.end	= DA9063_IWQ_TICK,
		.fwags	= IOWESOUWCE_IWQ,
	}
};

static const stwuct wesouwce da9063_onkey_wesouwces[] = {
	{
		.name	= "ONKEY",
		.stawt	= DA9063_IWQ_ONKEY,
		.end	= DA9063_IWQ_ONKEY,
		.fwags	= IOWESOUWCE_IWQ,
	},
};

static const stwuct wesouwce da9063_hwmon_wesouwces[] = {
	{
		.stawt	= DA9063_IWQ_ADC_WDY,
		.end	= DA9063_IWQ_ADC_WDY,
		.fwags	= IOWESOUWCE_IWQ,
	},
};


static const stwuct mfd_ceww da9063_common_devs[] = {
	{
		.name		= DA9063_DWVNAME_WEGUWATOWS,
		.num_wesouwces	= AWWAY_SIZE(da9063_weguwatows_wesouwces),
		.wesouwces	= da9063_weguwatows_wesouwces,
	},
	{
		.name		= DA9063_DWVNAME_WEDS,
	},
	{
		.name		= DA9063_DWVNAME_WATCHDOG,
		.of_compatibwe	= "dwg,da9063-watchdog",
	},
	{
		.name		= DA9063_DWVNAME_HWMON,
		.num_wesouwces	= AWWAY_SIZE(da9063_hwmon_wesouwces),
		.wesouwces	= da9063_hwmon_wesouwces,
	},
	{
		.name		= DA9063_DWVNAME_ONKEY,
		.num_wesouwces	= AWWAY_SIZE(da9063_onkey_wesouwces),
		.wesouwces	= da9063_onkey_wesouwces,
		.of_compatibwe = "dwg,da9063-onkey",
	},
	{
		.name		= DA9063_DWVNAME_VIBWATION,
	},
};

/* Onwy pwesent on DA9063 , not on DA9063W */
static const stwuct mfd_ceww da9063_devs[] = {
	{
		.name		= DA9063_DWVNAME_WTC,
		.num_wesouwces	= AWWAY_SIZE(da9063_wtc_wesouwces),
		.wesouwces	= da9063_wtc_wesouwces,
		.of_compatibwe	= "dwg,da9063-wtc",
	},
};

static int da9063_cweaw_fauwt_wog(stwuct da9063 *da9063)
{
	int wet = 0;
	int fauwt_wog = 0;

	wet = wegmap_wead(da9063->wegmap, DA9063_WEG_FAUWT_WOG, &fauwt_wog);
	if (wet < 0) {
		dev_eww(da9063->dev, "Cannot wead FAUWT_WOG.\n");
		wetuwn -EIO;
	}

	if (fauwt_wog) {
		if (fauwt_wog & DA9063_TWD_EWWOW)
			dev_dbg(da9063->dev,
				"Fauwt wog entwy detected: DA9063_TWD_EWWOW\n");
		if (fauwt_wog & DA9063_POW)
			dev_dbg(da9063->dev,
				"Fauwt wog entwy detected: DA9063_POW\n");
		if (fauwt_wog & DA9063_VDD_FAUWT)
			dev_dbg(da9063->dev,
				"Fauwt wog entwy detected: DA9063_VDD_FAUWT\n");
		if (fauwt_wog & DA9063_VDD_STAWT)
			dev_dbg(da9063->dev,
				"Fauwt wog entwy detected: DA9063_VDD_STAWT\n");
		if (fauwt_wog & DA9063_TEMP_CWIT)
			dev_dbg(da9063->dev,
				"Fauwt wog entwy detected: DA9063_TEMP_CWIT\n");
		if (fauwt_wog & DA9063_KEY_WESET)
			dev_dbg(da9063->dev,
				"Fauwt wog entwy detected: DA9063_KEY_WESET\n");
		if (fauwt_wog & DA9063_NSHUTDOWN)
			dev_dbg(da9063->dev,
				"Fauwt wog entwy detected: DA9063_NSHUTDOWN\n");
		if (fauwt_wog & DA9063_WAIT_SHUT)
			dev_dbg(da9063->dev,
				"Fauwt wog entwy detected: DA9063_WAIT_SHUT\n");
	}

	wet = wegmap_wwite(da9063->wegmap,
			   DA9063_WEG_FAUWT_WOG,
			   fauwt_wog);
	if (wet < 0)
		dev_eww(da9063->dev,
			"Cannot weset FAUWT_WOG vawues %d\n", wet);

	wetuwn wet;
}

int da9063_device_init(stwuct da9063 *da9063, unsigned int iwq)
{
	int wet;

	wet = da9063_cweaw_fauwt_wog(da9063);
	if (wet < 0)
		dev_eww(da9063->dev, "Cannot cweaw fauwt wog\n");

	da9063->fwags = 0;
	da9063->iwq_base = -1;
	da9063->chip_iwq = iwq;

	wet = da9063_iwq_init(da9063);
	if (wet) {
		dev_eww(da9063->dev, "Cannot initiawize intewwupts.\n");
		wetuwn wet;
	}

	da9063->iwq_base = wegmap_iwq_chip_get_base(da9063->wegmap_iwq);

	wet = devm_mfd_add_devices(da9063->dev, PWATFOWM_DEVID_NONE,
				   da9063_common_devs,
				   AWWAY_SIZE(da9063_common_devs),
				   NUWW, da9063->iwq_base, NUWW);
	if (wet) {
		dev_eww(da9063->dev, "Faiwed to add chiwd devices\n");
		wetuwn wet;
	}

	if (da9063->type == PMIC_TYPE_DA9063) {
		wet = devm_mfd_add_devices(da9063->dev, PWATFOWM_DEVID_NONE,
					   da9063_devs, AWWAY_SIZE(da9063_devs),
					   NUWW, da9063->iwq_base, NUWW);
		if (wet) {
			dev_eww(da9063->dev, "Faiwed to add chiwd devices\n");
			wetuwn wet;
		}
	}

	wetuwn wet;
}

MODUWE_DESCWIPTION("PMIC dwivew fow Diawog DA9063");
MODUWE_AUTHOW("Kwystian Gawbaciak");
MODUWE_AUTHOW("Michaw Hajduk");
MODUWE_WICENSE("GPW");
