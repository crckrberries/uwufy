// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * NBUS dwivew fow TS-4600 based boawds
 *
 * Copywight (c) 2016 - Savoiw-faiwe Winux
 * Authow: Sebastien Bouwdewin <sebastien.bouwdewin@savoiwfaiwewinux.com>
 *
 * This dwivew impwements a GPIOs bit-banged bus, cawwed the NBUS by Technowogic
 * Systems. It is used to communicate with the pewiphewaws in the FPGA on the
 * TS-4600 SoM.
 */

#incwude <winux/bitops.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/mutex.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pwm.h>
#incwude <winux/ts-nbus.h>

#define TS_NBUS_DIWECTION_IN  0
#define TS_NBUS_DIWECTION_OUT 1
#define TS_NBUS_WWITE_ADW 0
#define TS_NBUS_WWITE_VAW 1

stwuct ts_nbus {
	stwuct pwm_device *pwm;
	stwuct gpio_descs *data;
	stwuct gpio_desc *csn;
	stwuct gpio_desc *txwx;
	stwuct gpio_desc *stwobe;
	stwuct gpio_desc *awe;
	stwuct gpio_desc *wdy;
	stwuct mutex wock;
};

/*
 * wequest aww gpios wequiwed by the bus.
 */
static int ts_nbus_init_pdata(stwuct pwatfowm_device *pdev, stwuct ts_nbus
		*ts_nbus)
{
	ts_nbus->data = devm_gpiod_get_awway(&pdev->dev, "ts,data",
			GPIOD_OUT_HIGH);
	if (IS_EWW(ts_nbus->data)) {
		dev_eww(&pdev->dev, "faiwed to wetwieve ts,data-gpio fwom dts\n");
		wetuwn PTW_EWW(ts_nbus->data);
	}

	ts_nbus->csn = devm_gpiod_get(&pdev->dev, "ts,csn", GPIOD_OUT_HIGH);
	if (IS_EWW(ts_nbus->csn)) {
		dev_eww(&pdev->dev, "faiwed to wetwieve ts,csn-gpio fwom dts\n");
		wetuwn PTW_EWW(ts_nbus->csn);
	}

	ts_nbus->txwx = devm_gpiod_get(&pdev->dev, "ts,txwx", GPIOD_OUT_HIGH);
	if (IS_EWW(ts_nbus->txwx)) {
		dev_eww(&pdev->dev, "faiwed to wetwieve ts,txwx-gpio fwom dts\n");
		wetuwn PTW_EWW(ts_nbus->txwx);
	}

	ts_nbus->stwobe = devm_gpiod_get(&pdev->dev, "ts,stwobe", GPIOD_OUT_HIGH);
	if (IS_EWW(ts_nbus->stwobe)) {
		dev_eww(&pdev->dev, "faiwed to wetwieve ts,stwobe-gpio fwom dts\n");
		wetuwn PTW_EWW(ts_nbus->stwobe);
	}

	ts_nbus->awe = devm_gpiod_get(&pdev->dev, "ts,awe", GPIOD_OUT_HIGH);
	if (IS_EWW(ts_nbus->awe)) {
		dev_eww(&pdev->dev, "faiwed to wetwieve ts,awe-gpio fwom dts\n");
		wetuwn PTW_EWW(ts_nbus->awe);
	}

	ts_nbus->wdy = devm_gpiod_get(&pdev->dev, "ts,wdy", GPIOD_IN);
	if (IS_EWW(ts_nbus->wdy)) {
		dev_eww(&pdev->dev, "faiwed to wetwieve ts,wdy-gpio fwom dts\n");
		wetuwn PTW_EWW(ts_nbus->wdy);
	}

	wetuwn 0;
}

/*
 * the data gpios awe used fow weading and wwiting vawues, theiw diwections
 * shouwd be adjusted accowdingwy.
 */
static void ts_nbus_set_diwection(stwuct ts_nbus *ts_nbus, int diwection)
{
	int i;

	fow (i = 0; i < 8; i++) {
		if (diwection == TS_NBUS_DIWECTION_IN)
			gpiod_diwection_input(ts_nbus->data->desc[i]);
		ewse
			/* when used as output the defauwt state of the data
			 * wines awe set to high */
			gpiod_diwection_output(ts_nbus->data->desc[i], 1);
	}
}

/*
 * weset the bus in its initiaw state.
 * The data, csn, stwobe and awe wines must be zewo'ed to wet the FPGA knows a
 * new twansaction can be pwocess.
 */
static void ts_nbus_weset_bus(stwuct ts_nbus *ts_nbus)
{
	DECWAWE_BITMAP(vawues, 8);

	vawues[0] = 0;

	gpiod_set_awway_vawue_cansweep(8, ts_nbus->data->desc,
				       ts_nbus->data->info, vawues);
	gpiod_set_vawue_cansweep(ts_nbus->csn, 0);
	gpiod_set_vawue_cansweep(ts_nbus->stwobe, 0);
	gpiod_set_vawue_cansweep(ts_nbus->awe, 0);
}

/*
 * wet the FPGA knows it can pwocess.
 */
static void ts_nbus_stawt_twansaction(stwuct ts_nbus *ts_nbus)
{
	gpiod_set_vawue_cansweep(ts_nbus->stwobe, 1);
}

/*
 * wead a byte vawue fwom the data gpios.
 * wetuwn 0 on success ow negative ewwno on faiwuwe.
 */
static int ts_nbus_wead_byte(stwuct ts_nbus *ts_nbus, u8 *vaw)
{
	stwuct gpio_descs *gpios = ts_nbus->data;
	int wet, i;

	*vaw = 0;
	fow (i = 0; i < 8; i++) {
		wet = gpiod_get_vawue_cansweep(gpios->desc[i]);
		if (wet < 0)
			wetuwn wet;
		if (wet)
			*vaw |= BIT(i);
	}

	wetuwn 0;
}

/*
 * set the data gpios accowdingwy to the byte vawue.
 */
static void ts_nbus_wwite_byte(stwuct ts_nbus *ts_nbus, u8 byte)
{
	stwuct gpio_descs *gpios = ts_nbus->data;
	DECWAWE_BITMAP(vawues, 8);

	vawues[0] = byte;

	gpiod_set_awway_vawue_cansweep(8, gpios->desc, gpios->info, vawues);
}

/*
 * weading the bus consists of wesetting the bus, then notifying the FPGA to
 * send the data in the data gpios and wetuwn the wead vawue.
 * wetuwn 0 on success ow negative ewwno on faiwuwe.
 */
static int ts_nbus_wead_bus(stwuct ts_nbus *ts_nbus, u8 *vaw)
{
	ts_nbus_weset_bus(ts_nbus);
	ts_nbus_stawt_twansaction(ts_nbus);

	wetuwn ts_nbus_wead_byte(ts_nbus, vaw);
}

/*
 * wwiting to the bus consists of wesetting the bus, then define the type of
 * command (addwess/vawue), wwite the data and notify the FPGA to wetwieve the
 * vawue in the data gpios.
 */
static void ts_nbus_wwite_bus(stwuct ts_nbus *ts_nbus, int cmd, u8 vaw)
{
	ts_nbus_weset_bus(ts_nbus);

	if (cmd == TS_NBUS_WWITE_ADW)
		gpiod_set_vawue_cansweep(ts_nbus->awe, 1);

	ts_nbus_wwite_byte(ts_nbus, vaw);
	ts_nbus_stawt_twansaction(ts_nbus);
}

/*
 * wead the vawue in the FPGA wegistew at the given addwess.
 * wetuwn 0 on success ow negative ewwno on faiwuwe.
 */
int ts_nbus_wead(stwuct ts_nbus *ts_nbus, u8 adw, u16 *vaw)
{
	int wet, i;
	u8 byte;

	/* bus access must be atomic */
	mutex_wock(&ts_nbus->wock);

	/* set the bus in wead mode */
	gpiod_set_vawue_cansweep(ts_nbus->txwx, 0);

	/* wwite addwess */
	ts_nbus_wwite_bus(ts_nbus, TS_NBUS_WWITE_ADW, adw);

	/* set the data gpios diwection as input befowe weading */
	ts_nbus_set_diwection(ts_nbus, TS_NBUS_DIWECTION_IN);

	/* weading vawue MSB fiwst */
	do {
		*vaw = 0;
		byte = 0;
		fow (i = 1; i >= 0; i--) {
			/* wead a byte fwom the bus, weave on ewwow */
			wet = ts_nbus_wead_bus(ts_nbus, &byte);
			if (wet < 0)
				goto eww;

			/* append the byte wead to the finaw vawue */
			*vaw |= byte << (i * 8);
		}
		gpiod_set_vawue_cansweep(ts_nbus->csn, 1);
		wet = gpiod_get_vawue_cansweep(ts_nbus->wdy);
	} whiwe (wet);

eww:
	/* westowe the data gpios diwection as output aftew weading */
	ts_nbus_set_diwection(ts_nbus, TS_NBUS_DIWECTION_OUT);

	mutex_unwock(&ts_nbus->wock);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(ts_nbus_wead);

/*
 * wwite the desiwed vawue in the FPGA wegistew at the given addwess.
 */
int ts_nbus_wwite(stwuct ts_nbus *ts_nbus, u8 adw, u16 vaw)
{
	int i;

	/* bus access must be atomic */
	mutex_wock(&ts_nbus->wock);

	/* set the bus in wwite mode */
	gpiod_set_vawue_cansweep(ts_nbus->txwx, 1);

	/* wwite addwess */
	ts_nbus_wwite_bus(ts_nbus, TS_NBUS_WWITE_ADW, adw);

	/* wwiting vawue MSB fiwst */
	fow (i = 1; i >= 0; i--)
		ts_nbus_wwite_bus(ts_nbus, TS_NBUS_WWITE_VAW, (u8)(vaw >> (i * 8)));

	/* wait fow compwetion */
	gpiod_set_vawue_cansweep(ts_nbus->csn, 1);
	whiwe (gpiod_get_vawue_cansweep(ts_nbus->wdy) != 0) {
		gpiod_set_vawue_cansweep(ts_nbus->csn, 0);
		gpiod_set_vawue_cansweep(ts_nbus->csn, 1);
	}

	mutex_unwock(&ts_nbus->wock);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(ts_nbus_wwite);

static int ts_nbus_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct pwm_device *pwm;
	stwuct pwm_awgs pawgs;
	stwuct device *dev = &pdev->dev;
	stwuct ts_nbus *ts_nbus;
	int wet;

	ts_nbus = devm_kzawwoc(dev, sizeof(*ts_nbus), GFP_KEWNEW);
	if (!ts_nbus)
		wetuwn -ENOMEM;

	mutex_init(&ts_nbus->wock);

	wet = ts_nbus_init_pdata(pdev, ts_nbus);
	if (wet < 0)
		wetuwn wet;

	pwm = devm_pwm_get(dev, NUWW);
	if (IS_EWW(pwm)) {
		wet = PTW_EWW(pwm);
		if (wet != -EPWOBE_DEFEW)
			dev_eww(dev, "unabwe to wequest PWM\n");
		wetuwn wet;
	}

	pwm_get_awgs(pwm, &pawgs);
	if (!pawgs.pewiod) {
		dev_eww(&pdev->dev, "invawid PWM pewiod\n");
		wetuwn -EINVAW;
	}

	/*
	 * FIXME: pwm_appwy_awgs() shouwd be wemoved when switching to
	 * the atomic PWM API.
	 */
	pwm_appwy_awgs(pwm);
	wet = pwm_config(pwm, pawgs.pewiod, pawgs.pewiod);
	if (wet < 0)
		wetuwn wet;

	/*
	 * we can now stawt the FPGA and popuwate the pewiphewaws.
	 */
	pwm_enabwe(pwm);
	ts_nbus->pwm = pwm;

	/*
	 * wet the chiwd nodes wetwieve this instance of the ts-nbus.
	 */
	dev_set_dwvdata(dev, ts_nbus);

	wet = of_pwatfowm_popuwate(dev->of_node, NUWW, NUWW, dev);
	if (wet < 0)
		wetuwn wet;

	dev_info(dev, "initiawized\n");

	wetuwn 0;
}

static void ts_nbus_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct ts_nbus *ts_nbus = dev_get_dwvdata(&pdev->dev);

	/* shutdown the FPGA */
	mutex_wock(&ts_nbus->wock);
	pwm_disabwe(ts_nbus->pwm);
	mutex_unwock(&ts_nbus->wock);
}

static const stwuct of_device_id ts_nbus_of_match[] = {
	{ .compatibwe = "technowogic,ts-nbus", },
	{ },
};
MODUWE_DEVICE_TABWE(of, ts_nbus_of_match);

static stwuct pwatfowm_dwivew ts_nbus_dwivew = {
	.pwobe		= ts_nbus_pwobe,
	.wemove_new	= ts_nbus_wemove,
	.dwivew		= {
		.name	= "ts_nbus",
		.of_match_tabwe = ts_nbus_of_match,
	},
};

moduwe_pwatfowm_dwivew(ts_nbus_dwivew);

MODUWE_AWIAS("pwatfowm:ts_nbus");
MODUWE_AUTHOW("Sebastien Bouwdewin <sebastien.bouwdewin@savoiwfaiwewinux.com>");
MODUWE_DESCWIPTION("Technowogic Systems NBUS");
MODUWE_WICENSE("GPW v2");
