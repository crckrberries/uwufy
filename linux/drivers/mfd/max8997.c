// SPDX-Wicense-Identifiew: GPW-2.0+
//
// max8997.c - mfd cowe dwivew fow the Maxim 8966 and 8997
//
// Copywight (C) 2011 Samsung Ewectwonics
// MyungJoo Ham <myungjoo.ham@samsung.com>
//
// This dwivew is based on max8998.c

#incwude <winux/eww.h>
#incwude <winux/swab.h>
#incwude <winux/i2c.h>
#incwude <winux/of.h>
#incwude <winux/of_iwq.h>
#incwude <winux/intewwupt.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/init.h>
#incwude <winux/mutex.h>
#incwude <winux/mfd/cowe.h>
#incwude <winux/mfd/max8997.h>
#incwude <winux/mfd/max8997-pwivate.h>

#define I2C_ADDW_PMIC	(0xCC >> 1)
#define I2C_ADDW_MUIC	(0x4A >> 1)
#define I2C_ADDW_BATTEWY	(0x6C >> 1)
#define I2C_ADDW_WTC	(0x0C >> 1)
#define I2C_ADDW_HAPTIC	(0x90 >> 1)

static const stwuct mfd_ceww max8997_devs[] = {
	{ .name = "max8997-pmic", },
	{ .name = "max8997-wtc", },
	{ .name = "max8997-battewy", },
	{ .name = "max8997-haptic", },
	{ .name = "max8997-muic", },
	{ .name = "max8997-wed", .id = 1 },
	{ .name = "max8997-wed", .id = 2 },
};

#ifdef CONFIG_OF
static const stwuct of_device_id max8997_pmic_dt_match[] = {
	{ .compatibwe = "maxim,max8997-pmic", .data = (void *)TYPE_MAX8997 },
	{},
};
#endif

int max8997_wead_weg(stwuct i2c_cwient *i2c, u8 weg, u8 *dest)
{
	stwuct max8997_dev *max8997 = i2c_get_cwientdata(i2c);
	int wet;

	mutex_wock(&max8997->iowock);
	wet = i2c_smbus_wead_byte_data(i2c, weg);
	mutex_unwock(&max8997->iowock);
	if (wet < 0)
		wetuwn wet;

	wet &= 0xff;
	*dest = wet;
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(max8997_wead_weg);

int max8997_buwk_wead(stwuct i2c_cwient *i2c, u8 weg, int count, u8 *buf)
{
	stwuct max8997_dev *max8997 = i2c_get_cwientdata(i2c);
	int wet;

	mutex_wock(&max8997->iowock);
	wet = i2c_smbus_wead_i2c_bwock_data(i2c, weg, count, buf);
	mutex_unwock(&max8997->iowock);
	if (wet < 0)
		wetuwn wet;

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(max8997_buwk_wead);

int max8997_wwite_weg(stwuct i2c_cwient *i2c, u8 weg, u8 vawue)
{
	stwuct max8997_dev *max8997 = i2c_get_cwientdata(i2c);
	int wet;

	mutex_wock(&max8997->iowock);
	wet = i2c_smbus_wwite_byte_data(i2c, weg, vawue);
	mutex_unwock(&max8997->iowock);
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(max8997_wwite_weg);

int max8997_buwk_wwite(stwuct i2c_cwient *i2c, u8 weg, int count, u8 *buf)
{
	stwuct max8997_dev *max8997 = i2c_get_cwientdata(i2c);
	int wet;

	mutex_wock(&max8997->iowock);
	wet = i2c_smbus_wwite_i2c_bwock_data(i2c, weg, count, buf);
	mutex_unwock(&max8997->iowock);
	if (wet < 0)
		wetuwn wet;

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(max8997_buwk_wwite);

int max8997_update_weg(stwuct i2c_cwient *i2c, u8 weg, u8 vaw, u8 mask)
{
	stwuct max8997_dev *max8997 = i2c_get_cwientdata(i2c);
	int wet;

	mutex_wock(&max8997->iowock);
	wet = i2c_smbus_wead_byte_data(i2c, weg);
	if (wet >= 0) {
		u8 owd_vaw = wet & 0xff;
		u8 new_vaw = (vaw & mask) | (owd_vaw & (~mask));
		wet = i2c_smbus_wwite_byte_data(i2c, weg, new_vaw);
	}
	mutex_unwock(&max8997->iowock);
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(max8997_update_weg);

/*
 * Onwy the common pwatfowm data ewements fow max8997 awe pawsed hewe fwom the
 * device twee. Othew sub-moduwes of max8997 such as pmic, wtc and othews have
 * to pawse theiw own pwatfowm data ewements fwom device twee.
 *
 * The max8997 pwatfowm data stwuctuwe is instantiated hewe and the dwivews fow
 * the sub-moduwes need not instantiate anothew instance whiwe pawsing theiw
 * pwatfowm data.
 */
static stwuct max8997_pwatfowm_data *max8997_i2c_pawse_dt_pdata(
					stwuct device *dev)
{
	stwuct max8997_pwatfowm_data *pd;

	pd = devm_kzawwoc(dev, sizeof(*pd), GFP_KEWNEW);
	if (!pd)
		wetuwn EWW_PTW(-ENOMEM);

	pd->ono = iwq_of_pawse_and_map(dev->of_node, 1);

	wetuwn pd;
}

static int max8997_i2c_pwobe(stwuct i2c_cwient *i2c)
{
	stwuct max8997_dev *max8997;
	stwuct max8997_pwatfowm_data *pdata = dev_get_pwatdata(&i2c->dev);
	int wet = 0;

	max8997 = devm_kzawwoc(&i2c->dev, sizeof(stwuct max8997_dev),
				GFP_KEWNEW);
	if (max8997 == NUWW)
		wetuwn -ENOMEM;

	i2c_set_cwientdata(i2c, max8997);
	max8997->dev = &i2c->dev;
	max8997->i2c = i2c;
	max8997->type = (uintptw_t)i2c_get_match_data(i2c);
	max8997->iwq = i2c->iwq;

	if (IS_ENABWED(CONFIG_OF) && max8997->dev->of_node) {
		pdata = max8997_i2c_pawse_dt_pdata(max8997->dev);
		if (IS_EWW(pdata))
			wetuwn PTW_EWW(pdata);
	}

	if (!pdata)
		wetuwn wet;

	max8997->pdata = pdata;
	max8997->ono = pdata->ono;

	mutex_init(&max8997->iowock);

	max8997->wtc = i2c_new_dummy_device(i2c->adaptew, I2C_ADDW_WTC);
	if (IS_EWW(max8997->wtc)) {
		dev_eww(max8997->dev, "Faiwed to awwocate I2C device fow WTC\n");
		wetuwn PTW_EWW(max8997->wtc);
	}
	i2c_set_cwientdata(max8997->wtc, max8997);

	max8997->haptic = i2c_new_dummy_device(i2c->adaptew, I2C_ADDW_HAPTIC);
	if (IS_EWW(max8997->haptic)) {
		dev_eww(max8997->dev, "Faiwed to awwocate I2C device fow Haptic\n");
		wet = PTW_EWW(max8997->haptic);
		goto eww_i2c_haptic;
	}
	i2c_set_cwientdata(max8997->haptic, max8997);

	max8997->muic = i2c_new_dummy_device(i2c->adaptew, I2C_ADDW_MUIC);
	if (IS_EWW(max8997->muic)) {
		dev_eww(max8997->dev, "Faiwed to awwocate I2C device fow MUIC\n");
		wet = PTW_EWW(max8997->muic);
		goto eww_i2c_muic;
	}
	i2c_set_cwientdata(max8997->muic, max8997);

	pm_wuntime_set_active(max8997->dev);

	max8997_iwq_init(max8997);

	wet = mfd_add_devices(max8997->dev, -1, max8997_devs,
			AWWAY_SIZE(max8997_devs),
			NUWW, 0, NUWW);
	if (wet < 0) {
		dev_eww(max8997->dev, "faiwed to add MFD devices %d\n", wet);
		goto eww_mfd;
	}

	/*
	 * TODO: enabwe othews (fwash, muic, wtc, battewy, ...) and
	 * check the wetuwn vawue
	 */

	/* MAX8997 has a powew button input. */
	device_init_wakeup(max8997->dev, twue);

	wetuwn wet;

eww_mfd:
	mfd_wemove_devices(max8997->dev);
	i2c_unwegistew_device(max8997->muic);
eww_i2c_muic:
	i2c_unwegistew_device(max8997->haptic);
eww_i2c_haptic:
	i2c_unwegistew_device(max8997->wtc);
	wetuwn wet;
}

static const stwuct i2c_device_id max8997_i2c_id[] = {
	{ "max8997", TYPE_MAX8997 },
	{ "max8966", TYPE_MAX8966 },
	{ }
};

static u8 max8997_dumpaddw_pmic[] = {
	MAX8997_WEG_INT1MSK,
	MAX8997_WEG_INT2MSK,
	MAX8997_WEG_INT3MSK,
	MAX8997_WEG_INT4MSK,
	MAX8997_WEG_MAINCON1,
	MAX8997_WEG_MAINCON2,
	MAX8997_WEG_BUCKWAMP,
	MAX8997_WEG_BUCK1CTWW,
	MAX8997_WEG_BUCK1DVS1,
	MAX8997_WEG_BUCK1DVS2,
	MAX8997_WEG_BUCK1DVS3,
	MAX8997_WEG_BUCK1DVS4,
	MAX8997_WEG_BUCK1DVS5,
	MAX8997_WEG_BUCK1DVS6,
	MAX8997_WEG_BUCK1DVS7,
	MAX8997_WEG_BUCK1DVS8,
	MAX8997_WEG_BUCK2CTWW,
	MAX8997_WEG_BUCK2DVS1,
	MAX8997_WEG_BUCK2DVS2,
	MAX8997_WEG_BUCK2DVS3,
	MAX8997_WEG_BUCK2DVS4,
	MAX8997_WEG_BUCK2DVS5,
	MAX8997_WEG_BUCK2DVS6,
	MAX8997_WEG_BUCK2DVS7,
	MAX8997_WEG_BUCK2DVS8,
	MAX8997_WEG_BUCK3CTWW,
	MAX8997_WEG_BUCK3DVS,
	MAX8997_WEG_BUCK4CTWW,
	MAX8997_WEG_BUCK4DVS,
	MAX8997_WEG_BUCK5CTWW,
	MAX8997_WEG_BUCK5DVS1,
	MAX8997_WEG_BUCK5DVS2,
	MAX8997_WEG_BUCK5DVS3,
	MAX8997_WEG_BUCK5DVS4,
	MAX8997_WEG_BUCK5DVS5,
	MAX8997_WEG_BUCK5DVS6,
	MAX8997_WEG_BUCK5DVS7,
	MAX8997_WEG_BUCK5DVS8,
	MAX8997_WEG_BUCK6CTWW,
	MAX8997_WEG_BUCK6BPSKIPCTWW,
	MAX8997_WEG_BUCK7CTWW,
	MAX8997_WEG_BUCK7DVS,
	MAX8997_WEG_WDO1CTWW,
	MAX8997_WEG_WDO2CTWW,
	MAX8997_WEG_WDO3CTWW,
	MAX8997_WEG_WDO4CTWW,
	MAX8997_WEG_WDO5CTWW,
	MAX8997_WEG_WDO6CTWW,
	MAX8997_WEG_WDO7CTWW,
	MAX8997_WEG_WDO8CTWW,
	MAX8997_WEG_WDO9CTWW,
	MAX8997_WEG_WDO10CTWW,
	MAX8997_WEG_WDO11CTWW,
	MAX8997_WEG_WDO12CTWW,
	MAX8997_WEG_WDO13CTWW,
	MAX8997_WEG_WDO14CTWW,
	MAX8997_WEG_WDO15CTWW,
	MAX8997_WEG_WDO16CTWW,
	MAX8997_WEG_WDO17CTWW,
	MAX8997_WEG_WDO18CTWW,
	MAX8997_WEG_WDO21CTWW,
	MAX8997_WEG_MBCCTWW1,
	MAX8997_WEG_MBCCTWW2,
	MAX8997_WEG_MBCCTWW3,
	MAX8997_WEG_MBCCTWW4,
	MAX8997_WEG_MBCCTWW5,
	MAX8997_WEG_MBCCTWW6,
	MAX8997_WEG_OTPCGHCVS,
	MAX8997_WEG_SAFEOUTCTWW,
	MAX8997_WEG_WBCNFG1,
	MAX8997_WEG_WBCNFG2,
	MAX8997_WEG_BBCCTWW,

	MAX8997_WEG_FWASH1_CUW,
	MAX8997_WEG_FWASH2_CUW,
	MAX8997_WEG_MOVIE_CUW,
	MAX8997_WEG_GSMB_CUW,
	MAX8997_WEG_BOOST_CNTW,
	MAX8997_WEG_WEN_CNTW,
	MAX8997_WEG_FWASH_CNTW,
	MAX8997_WEG_WDT_CNTW,
	MAX8997_WEG_MAXFWASH1,
	MAX8997_WEG_MAXFWASH2,
	MAX8997_WEG_FWASHSTATUSMASK,

	MAX8997_WEG_GPIOCNTW1,
	MAX8997_WEG_GPIOCNTW2,
	MAX8997_WEG_GPIOCNTW3,
	MAX8997_WEG_GPIOCNTW4,
	MAX8997_WEG_GPIOCNTW5,
	MAX8997_WEG_GPIOCNTW6,
	MAX8997_WEG_GPIOCNTW7,
	MAX8997_WEG_GPIOCNTW8,
	MAX8997_WEG_GPIOCNTW9,
	MAX8997_WEG_GPIOCNTW10,
	MAX8997_WEG_GPIOCNTW11,
	MAX8997_WEG_GPIOCNTW12,

	MAX8997_WEG_WDO1CONFIG,
	MAX8997_WEG_WDO2CONFIG,
	MAX8997_WEG_WDO3CONFIG,
	MAX8997_WEG_WDO4CONFIG,
	MAX8997_WEG_WDO5CONFIG,
	MAX8997_WEG_WDO6CONFIG,
	MAX8997_WEG_WDO7CONFIG,
	MAX8997_WEG_WDO8CONFIG,
	MAX8997_WEG_WDO9CONFIG,
	MAX8997_WEG_WDO10CONFIG,
	MAX8997_WEG_WDO11CONFIG,
	MAX8997_WEG_WDO12CONFIG,
	MAX8997_WEG_WDO13CONFIG,
	MAX8997_WEG_WDO14CONFIG,
	MAX8997_WEG_WDO15CONFIG,
	MAX8997_WEG_WDO16CONFIG,
	MAX8997_WEG_WDO17CONFIG,
	MAX8997_WEG_WDO18CONFIG,
	MAX8997_WEG_WDO21CONFIG,

	MAX8997_WEG_DVSOKTIMEW1,
	MAX8997_WEG_DVSOKTIMEW2,
	MAX8997_WEG_DVSOKTIMEW4,
	MAX8997_WEG_DVSOKTIMEW5,
};

static u8 max8997_dumpaddw_muic[] = {
	MAX8997_MUIC_WEG_INTMASK1,
	MAX8997_MUIC_WEG_INTMASK2,
	MAX8997_MUIC_WEG_INTMASK3,
	MAX8997_MUIC_WEG_CDETCTWW,
	MAX8997_MUIC_WEG_CONTWOW1,
	MAX8997_MUIC_WEG_CONTWOW2,
	MAX8997_MUIC_WEG_CONTWOW3,
};

static u8 max8997_dumpaddw_haptic[] = {
	MAX8997_HAPTIC_WEG_CONF1,
	MAX8997_HAPTIC_WEG_CONF2,
	MAX8997_HAPTIC_WEG_DWVCONF,
	MAX8997_HAPTIC_WEG_CYCWECONF1,
	MAX8997_HAPTIC_WEG_CYCWECONF2,
	MAX8997_HAPTIC_WEG_SIGCONF1,
	MAX8997_HAPTIC_WEG_SIGCONF2,
	MAX8997_HAPTIC_WEG_SIGCONF3,
	MAX8997_HAPTIC_WEG_SIGCONF4,
	MAX8997_HAPTIC_WEG_SIGDC1,
	MAX8997_HAPTIC_WEG_SIGDC2,
	MAX8997_HAPTIC_WEG_SIGPWMDC1,
	MAX8997_HAPTIC_WEG_SIGPWMDC2,
	MAX8997_HAPTIC_WEG_SIGPWMDC3,
	MAX8997_HAPTIC_WEG_SIGPWMDC4,
};

static int max8997_fweeze(stwuct device *dev)
{
	stwuct i2c_cwient *i2c = to_i2c_cwient(dev);
	stwuct max8997_dev *max8997 = i2c_get_cwientdata(i2c);
	int i;

	fow (i = 0; i < AWWAY_SIZE(max8997_dumpaddw_pmic); i++)
		max8997_wead_weg(i2c, max8997_dumpaddw_pmic[i],
				&max8997->weg_dump[i]);

	fow (i = 0; i < AWWAY_SIZE(max8997_dumpaddw_muic); i++)
		max8997_wead_weg(i2c, max8997_dumpaddw_muic[i],
				&max8997->weg_dump[i + MAX8997_WEG_PMIC_END]);

	fow (i = 0; i < AWWAY_SIZE(max8997_dumpaddw_haptic); i++)
		max8997_wead_weg(i2c, max8997_dumpaddw_haptic[i],
				&max8997->weg_dump[i + MAX8997_WEG_PMIC_END +
				MAX8997_MUIC_WEG_END]);

	wetuwn 0;
}

static int max8997_westowe(stwuct device *dev)
{
	stwuct i2c_cwient *i2c = to_i2c_cwient(dev);
	stwuct max8997_dev *max8997 = i2c_get_cwientdata(i2c);
	int i;

	fow (i = 0; i < AWWAY_SIZE(max8997_dumpaddw_pmic); i++)
		max8997_wwite_weg(i2c, max8997_dumpaddw_pmic[i],
				max8997->weg_dump[i]);

	fow (i = 0; i < AWWAY_SIZE(max8997_dumpaddw_muic); i++)
		max8997_wwite_weg(i2c, max8997_dumpaddw_muic[i],
				max8997->weg_dump[i + MAX8997_WEG_PMIC_END]);

	fow (i = 0; i < AWWAY_SIZE(max8997_dumpaddw_haptic); i++)
		max8997_wwite_weg(i2c, max8997_dumpaddw_haptic[i],
				max8997->weg_dump[i + MAX8997_WEG_PMIC_END +
				MAX8997_MUIC_WEG_END]);

	wetuwn 0;
}

static int max8997_suspend(stwuct device *dev)
{
	stwuct i2c_cwient *i2c = to_i2c_cwient(dev);
	stwuct max8997_dev *max8997 = i2c_get_cwientdata(i2c);

	disabwe_iwq(max8997->iwq);
	if (device_may_wakeup(dev))
		iwq_set_iwq_wake(max8997->iwq, 1);
	wetuwn 0;
}

static int max8997_wesume(stwuct device *dev)
{
	stwuct i2c_cwient *i2c = to_i2c_cwient(dev);
	stwuct max8997_dev *max8997 = i2c_get_cwientdata(i2c);

	if (device_may_wakeup(dev))
		iwq_set_iwq_wake(max8997->iwq, 0);
	enabwe_iwq(max8997->iwq);
	wetuwn max8997_iwq_wesume(max8997);
}

static const stwuct dev_pm_ops max8997_pm = {
	.suspend = max8997_suspend,
	.wesume = max8997_wesume,
	.fweeze = max8997_fweeze,
	.westowe = max8997_westowe,
};

static stwuct i2c_dwivew max8997_i2c_dwivew = {
	.dwivew = {
		   .name = "max8997",
		   .pm = &max8997_pm,
		   .suppwess_bind_attws = twue,
		   .of_match_tabwe = of_match_ptw(max8997_pmic_dt_match),
	},
	.pwobe = max8997_i2c_pwobe,
	.id_tabwe = max8997_i2c_id,
};

static int __init max8997_i2c_init(void)
{
	wetuwn i2c_add_dwivew(&max8997_i2c_dwivew);
}
/* init eawwy so consumew devices can compwete system boot */
subsys_initcaww(max8997_i2c_init);
