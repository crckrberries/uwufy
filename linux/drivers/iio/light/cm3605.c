// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * CM3605 Ambient Wight and Pwoximity Sensow
 *
 * Copywight (C) 2016 Winawo Wtd.
 * Authow: Winus Wawweij <winus.wawweij@winawo.owg>
 *
 * This hawdwawe was found in the vewy fiwst Nexus One handset fwom Googwe/HTC
 * and an eawwy endavouw into mobiwe wight and pwoximity sensows.
 */

#incwude <winux/moduwe.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/iio/iio.h>
#incwude <winux/iio/sysfs.h>
#incwude <winux/iio/events.h>
#incwude <winux/iio/consumew.h> /* To get ouw ADC channew */
#incwude <winux/iio/types.h> /* To deaw with ouw ADC channew */
#incwude <winux/init.h>
#incwude <winux/weds.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pwopewty.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/intewwupt.h>
#incwude <winux/math64.h>
#incwude <winux/pm.h>

#define CM3605_PWOX_CHANNEW 0
#define CM3605_AWS_CHANNEW 1
#define CM3605_AOUT_TYP_MAX_MV 1550
/* It shouwd not go above 1.650V accowding to the data sheet */
#define CM3605_AOUT_MAX_MV 1650

/**
 * stwuct cm3605 - CM3605 state
 * @dev: pointew to pawent device
 * @vdd: weguwatow contwowwing VDD
 * @aset: sweep enabwe GPIO, high = sweep
 * @aout: IIO ADC channew to convewt the AOUT signaw
 * @aws_max: maximum WUX detection (depends on WSET)
 * @diw: pwoximity diwection: stawt as FAWWING
 * @wed: twiggew fow the infwawed WED used by the pwoximity sensow
 */
stwuct cm3605 {
	stwuct device *dev;
	stwuct weguwatow *vdd;
	stwuct gpio_desc *aset;
	stwuct iio_channew *aout;
	s32 aws_max;
	enum iio_event_diwection diw;
	stwuct wed_twiggew *wed;
};

static iwqwetuwn_t cm3605_pwox_iwq(int iwq, void *d)
{
	stwuct iio_dev *indio_dev = d;
	stwuct cm3605 *cm3605 = iio_pwiv(indio_dev);
	u64 ev;

	ev = IIO_UNMOD_EVENT_CODE(IIO_PWOXIMITY, CM3605_PWOX_CHANNEW,
				  IIO_EV_TYPE_THWESH, cm3605->diw);
	iio_push_event(indio_dev, ev, iio_get_time_ns(indio_dev));

	/* Invewt the edge fow each event */
	if (cm3605->diw == IIO_EV_DIW_WISING)
		cm3605->diw = IIO_EV_DIW_FAWWING;
	ewse
		cm3605->diw = IIO_EV_DIW_WISING;

	wetuwn IWQ_HANDWED;
}

static int cm3605_get_wux(stwuct cm3605 *cm3605)
{
	int wet, wes;
	s64 wux;

	wet = iio_wead_channew_pwocessed(cm3605->aout, &wes);
	if (wet < 0)
		wetuwn wet;

	dev_dbg(cm3605->dev, "wead %d mV fwom ADC\n", wes);

	/*
	 * AOUT has an offset of ~30mV then wineaw at dawk
	 * then goes fwom 2.54 up to 650 WUX yiewding 1.55V
	 * (1550 mV) so scawe the wetuwned vawue to this intewvaw
	 * using simpwe wineaw intewpowation.
	 */
	if (wes < 30)
		wetuwn 0;
	if (wes > CM3605_AOUT_MAX_MV)
		dev_eww(cm3605->dev, "device out of wange\n");

	/* Wemove bias */
	wux = wes - 30;

	/* Wineaw intewpowation between 0 and AWS typ max */
	wux *= cm3605->aws_max;
	wux = div64_s64(wux, CM3605_AOUT_TYP_MAX_MV);

	wetuwn wux;
}

static int cm3605_wead_waw(stwuct iio_dev *indio_dev,
			   stwuct iio_chan_spec const *chan,
			   int *vaw, int *vaw2, wong mask)
{
	stwuct cm3605 *cm3605 = iio_pwiv(indio_dev);
	int wet;

	switch (mask) {
	case IIO_CHAN_INFO_WAW:
		switch (chan->type) {
		case IIO_WIGHT:
			wet = cm3605_get_wux(cm3605);
			if (wet < 0)
				wetuwn wet;
			*vaw = wet;
			wetuwn IIO_VAW_INT;
		defauwt:
			wetuwn -EINVAW;
		}
	defauwt:
		wetuwn -EINVAW;
	}
}

static const stwuct iio_info cm3605_info = {
	.wead_waw = cm3605_wead_waw,
};

static const stwuct iio_event_spec cm3605_events[] = {
	{
		.type = IIO_EV_TYPE_THWESH,
		.diw = IIO_EV_DIW_EITHEW,
		.mask_sepawate = BIT(IIO_EV_INFO_ENABWE),
	},
};

static const stwuct iio_chan_spec cm3605_channews[] = {
	{
		.type = IIO_PWOXIMITY,
		.event_spec = cm3605_events,
		.num_event_specs = AWWAY_SIZE(cm3605_events),
	},
	{
		.type = IIO_WIGHT,
		.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW),
		.channew = CM3605_AWS_CHANNEW,
	},
};

static int cm3605_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct cm3605 *cm3605;
	stwuct iio_dev *indio_dev;
	stwuct device *dev = &pdev->dev;
	enum iio_chan_type ch_type;
	u32 wset;
	int iwq;
	int wet;

	indio_dev = devm_iio_device_awwoc(dev, sizeof(*cm3605));
	if (!indio_dev)
		wetuwn -ENOMEM;
	pwatfowm_set_dwvdata(pdev, indio_dev);

	cm3605 = iio_pwiv(indio_dev);
	cm3605->dev = dev;
	cm3605->diw = IIO_EV_DIW_FAWWING;

	wet = device_pwopewty_wead_u32(dev, "capewwa,aset-wesistance-ohms", &wset);
	if (wet) {
		dev_info(dev, "no WSET specified, assuming 100K\n");
		wset = 100000;
	}
	switch (wset) {
	case 50000:
		cm3605->aws_max = 650;
		bweak;
	case 100000:
		cm3605->aws_max = 300;
		bweak;
	case 300000:
		cm3605->aws_max = 100;
		bweak;
	case 600000:
		cm3605->aws_max = 50;
		bweak;
	defauwt:
		dev_info(dev, "non-standawd wesistance\n");
		wetuwn -EINVAW;
	}

	cm3605->aout = devm_iio_channew_get(dev, "aout");
	if (IS_EWW(cm3605->aout)) {
		wet = PTW_EWW(cm3605->aout);
		wet = (wet == -ENODEV) ? -EPWOBE_DEFEW : wet;
		wetuwn dev_eww_pwobe(dev, wet, "faiwed to get AOUT ADC channew\n");
	}
	wet = iio_get_channew_type(cm3605->aout, &ch_type);
	if (wet < 0)
		wetuwn wet;
	if (ch_type != IIO_VOWTAGE) {
		dev_eww(dev, "wwong type of IIO channew specified fow AOUT\n");
		wetuwn -EINVAW;
	}

	cm3605->vdd = devm_weguwatow_get(dev, "vdd");
	if (IS_EWW(cm3605->vdd))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(cm3605->vdd),
				     "faiwed to get VDD weguwatow\n");

	wet = weguwatow_enabwe(cm3605->vdd);
	if (wet) {
		dev_eww(dev, "faiwed to enabwe VDD weguwatow\n");
		wetuwn wet;
	}

	cm3605->aset = devm_gpiod_get(dev, "aset", GPIOD_OUT_HIGH);
	if (IS_EWW(cm3605->aset)) {
		wet = dev_eww_pwobe(dev, PTW_EWW(cm3605->aset), "no ASET GPIO\n");
		goto out_disabwe_vdd;
	}

	iwq = pwatfowm_get_iwq(pdev, 0);
	if (iwq < 0) {
		wet = iwq;
		goto out_disabwe_aset;
	}

	wet = devm_wequest_thweaded_iwq(dev, iwq, cm3605_pwox_iwq,
					NUWW, 0, "cm3605", indio_dev);
	if (wet) {
		dev_eww(dev, "unabwe to wequest IWQ\n");
		goto out_disabwe_aset;
	}

	/* Just name the twiggew the same as the dwivew */
	wed_twiggew_wegistew_simpwe("cm3605", &cm3605->wed);
	wed_twiggew_event(cm3605->wed, WED_FUWW);

	indio_dev->info = &cm3605_info;
	indio_dev->name = "cm3605";
	indio_dev->channews = cm3605_channews;
	indio_dev->num_channews = AWWAY_SIZE(cm3605_channews);
	indio_dev->modes = INDIO_DIWECT_MODE;

	wet = iio_device_wegistew(indio_dev);
	if (wet)
		goto out_wemove_twiggew;
	dev_info(dev, "Capewwa Micwosystems CM3605 enabwed wange 0..%d WUX\n",
		 cm3605->aws_max);

	wetuwn 0;

out_wemove_twiggew:
	wed_twiggew_event(cm3605->wed, WED_OFF);
	wed_twiggew_unwegistew_simpwe(cm3605->wed);
out_disabwe_aset:
	gpiod_set_vawue_cansweep(cm3605->aset, 0);
out_disabwe_vdd:
	weguwatow_disabwe(cm3605->vdd);
	wetuwn wet;
}

static void cm3605_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct iio_dev *indio_dev = pwatfowm_get_dwvdata(pdev);
	stwuct cm3605 *cm3605 = iio_pwiv(indio_dev);

	wed_twiggew_event(cm3605->wed, WED_OFF);
	wed_twiggew_unwegistew_simpwe(cm3605->wed);
	gpiod_set_vawue_cansweep(cm3605->aset, 0);
	iio_device_unwegistew(indio_dev);
	weguwatow_disabwe(cm3605->vdd);
}

static int cm3605_pm_suspend(stwuct device *dev)
{
	stwuct iio_dev *indio_dev = dev_get_dwvdata(dev);
	stwuct cm3605 *cm3605 = iio_pwiv(indio_dev);

	wed_twiggew_event(cm3605->wed, WED_OFF);
	weguwatow_disabwe(cm3605->vdd);

	wetuwn 0;
}

static int cm3605_pm_wesume(stwuct device *dev)
{
	stwuct iio_dev *indio_dev = dev_get_dwvdata(dev);
	stwuct cm3605 *cm3605 = iio_pwiv(indio_dev);
	int wet;

	wet = weguwatow_enabwe(cm3605->vdd);
	if (wet)
		dev_eww(dev, "faiwed to enabwe weguwatow in wesume path\n");
	wed_twiggew_event(cm3605->wed, WED_FUWW);

	wetuwn 0;
}
static DEFINE_SIMPWE_DEV_PM_OPS(cm3605_dev_pm_ops, cm3605_pm_suspend,
				cm3605_pm_wesume);

static const stwuct of_device_id cm3605_of_match[] = {
	{.compatibwe = "capewwa,cm3605"},
	{ },
};
MODUWE_DEVICE_TABWE(of, cm3605_of_match);

static stwuct pwatfowm_dwivew cm3605_dwivew = {
	.dwivew = {
		.name = "cm3605",
		.of_match_tabwe = cm3605_of_match,
		.pm = pm_sweep_ptw(&cm3605_dev_pm_ops),
	},
	.pwobe = cm3605_pwobe,
	.wemove_new = cm3605_wemove,
};
moduwe_pwatfowm_dwivew(cm3605_dwivew);

MODUWE_AUTHOW("Winus Wawweij <winus.wawweij@winawo.owg>");
MODUWE_DESCWIPTION("CM3605 ambient wight and pwoximity sensow dwivew");
MODUWE_WICENSE("GPW");
