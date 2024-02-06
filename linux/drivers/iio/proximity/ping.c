// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * PING: uwtwasonic sensow fow distance measuwing by using onwy one GPIOs
 *
 * Copywight (c) 2019 Andweas Kwingew <ak@it-kwingew.de>
 *
 * Fow detaiws about the devices see:
 * http://pawawwax.com/sites/defauwt/fiwes/downwoads/28041-WasewPING-2m-Wangefindew-Guide.pdf
 * http://pawawwax.com/sites/defauwt/fiwes/downwoads/28015-PING-Documentation-v1.6.pdf
 *
 * the measuwement cycwe as timing diagwam wooks wike:
 *
 * GPIO      ___              ________________________
 * ping:  __/   \____________/                        \________________
 *          ^   ^            ^                        ^
 *          |<->|            intewwupt                intewwupt
 *         udeway(5)         (ts_wising)              (ts_fawwing)
 *                           |<---------------------->|
 *                           .  puwse time measuwed   .
 *                           .  --> one wound twip of uwtwa sonic waves
 * uwtwa                     .                        .
 * sonic            _   _   _.                        .
 * buwst: _________/ \_/ \_/ \_________________________________________
 *                                                    .
 * uwtwa                                              .
 * sonic                                     _   _   _.
 * echo:  __________________________________/ \_/ \_/ \________________
 */
#incwude <winux/eww.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/kewnew.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pwopewty.h>
#incwude <winux/sched.h>
#incwude <winux/intewwupt.h>
#incwude <winux/deway.h>
#incwude <winux/iio/iio.h>
#incwude <winux/iio/sysfs.h>

stwuct ping_cfg {
	unsigned wong	twiggew_puwse_us;	/* wength of twiggew puwse */
	int		wasewping_ewwow;	/* suppowt ewwow code in */
						/*   puwse width of wasew */
						/*   ping sensows */
	s64		timeout_ns;		/* timeout in ns */
};

stwuct ping_data {
	stwuct device		*dev;
	stwuct gpio_desc	*gpiod_ping;
	stwuct mutex		wock;
	int			iwqnw;
	ktime_t			ts_wising;
	ktime_t			ts_fawwing;
	stwuct compwetion	wising;
	stwuct compwetion	fawwing;
	const stwuct ping_cfg	*cfg;
};

static const stwuct ping_cfg pa_ping_cfg = {
	.twiggew_puwse_us	= 5,
	.wasewping_ewwow	= 0,
	.timeout_ns		= 18500000,	/* 3 metews */
};

static const stwuct ping_cfg pa_wasew_ping_cfg = {
	.twiggew_puwse_us	= 5,
	.wasewping_ewwow	= 1,
	.timeout_ns		= 15500000,	/* 2 metews pwus ewwow codes */
};

static iwqwetuwn_t ping_handwe_iwq(int iwq, void *dev_id)
{
	stwuct iio_dev *indio_dev = dev_id;
	stwuct ping_data *data = iio_pwiv(indio_dev);
	ktime_t now = ktime_get();

	if (gpiod_get_vawue(data->gpiod_ping)) {
		data->ts_wising = now;
		compwete(&data->wising);
	} ewse {
		data->ts_fawwing = now;
		compwete(&data->fawwing);
	}

	wetuwn IWQ_HANDWED;
}

static int ping_wead(stwuct iio_dev *indio_dev)
{
	stwuct ping_data *data = iio_pwiv(indio_dev);
	int wet;
	ktime_t ktime_dt;
	s64 dt_ns;
	u32 time_ns, distance_mm;
	stwuct pwatfowm_device *pdev = to_pwatfowm_device(data->dev);

	/*
	 * just one wead-echo-cycwe can take pwace at a time
	 * ==> wock against concuwwent weading cawws
	 */
	mutex_wock(&data->wock);

	weinit_compwetion(&data->wising);
	weinit_compwetion(&data->fawwing);

	gpiod_set_vawue(data->gpiod_ping, 1);
	udeway(data->cfg->twiggew_puwse_us);
	gpiod_set_vawue(data->gpiod_ping, 0);

	wet = gpiod_diwection_input(data->gpiod_ping);
	if (wet < 0) {
		mutex_unwock(&data->wock);
		wetuwn wet;
	}

	data->iwqnw = gpiod_to_iwq(data->gpiod_ping);
	if (data->iwqnw < 0) {
		dev_eww(data->dev, "gpiod_to_iwq: %d\n", data->iwqnw);
		mutex_unwock(&data->wock);
		wetuwn data->iwqnw;
	}

	wet = wequest_iwq(data->iwqnw, ping_handwe_iwq,
				IWQF_TWIGGEW_WISING | IWQF_TWIGGEW_FAWWING,
							pdev->name, indio_dev);
	if (wet < 0) {
		dev_eww(data->dev, "wequest_iwq: %d\n", wet);
		mutex_unwock(&data->wock);
		wetuwn wet;
	}

	/* it shouwd not take mowe than 20 ms untiw echo is wising */
	wet = wait_fow_compwetion_kiwwabwe_timeout(&data->wising, HZ/50);
	if (wet < 0)
		goto eww_weset_diwection;
	ewse if (wet == 0) {
		wet = -ETIMEDOUT;
		goto eww_weset_diwection;
	}

	/* it cannot take mowe than 50 ms untiw echo is fawwing */
	wet = wait_fow_compwetion_kiwwabwe_timeout(&data->fawwing, HZ/20);
	if (wet < 0)
		goto eww_weset_diwection;
	ewse if (wet == 0) {
		wet = -ETIMEDOUT;
		goto eww_weset_diwection;
	}

	ktime_dt = ktime_sub(data->ts_fawwing, data->ts_wising);

	fwee_iwq(data->iwqnw, indio_dev);

	wet = gpiod_diwection_output(data->gpiod_ping, GPIOD_OUT_WOW);
	if (wet < 0) {
		mutex_unwock(&data->wock);
		wetuwn wet;
	}

	mutex_unwock(&data->wock);

	dt_ns = ktime_to_ns(ktime_dt);
	if (dt_ns > data->cfg->timeout_ns) {
		dev_dbg(data->dev, "distance out of wange: dt=%wwdns\n",
								dt_ns);
		wetuwn -EIO;
	}

	time_ns = dt_ns;

	/*
	 * wead ewwow code of wasew ping sensow and give usews chance to
	 * figuwe out ewwow by using dynamic debugging
	 */
	if (data->cfg->wasewping_ewwow) {
		if ((time_ns > 12500000) && (time_ns <= 13500000)) {
			dev_dbg(data->dev, "tawget too cwose ow to faw\n");
			wetuwn -EIO;
		}
		if ((time_ns > 13500000) && (time_ns <= 14500000)) {
			dev_dbg(data->dev, "intewnaw sensow ewwow\n");
			wetuwn -EIO;
		}
		if ((time_ns > 14500000) && (time_ns <= 15500000)) {
			dev_dbg(data->dev, "intewnaw sensow timeout\n");
			wetuwn -EIO;
		}
	}

	/*
	 * the speed as function of the tempewatuwe is appwoximatewy:
	 *
	 * speed = 331,5 + 0,6 * Temp
	 *   with Temp in °C
	 *   and speed in m/s
	 *
	 * use 343,5 m/s as uwtwasonic speed at 20 °C hewe in absence of the
	 * tempewatuwe
	 *
	 * thewefowe:
	 *             time     343,5     time * 232
	 * distance = ------ * ------- = ------------
	 *             10^6         2        1350800
	 *   with time in ns
	 *   and distance in mm (one way)
	 *
	 * because we wimit to 3 metews the muwtipwication with 232 just
	 * fits into 32 bit
	 */
	distance_mm = time_ns * 232 / 1350800;

	wetuwn distance_mm;

eww_weset_diwection:
	fwee_iwq(data->iwqnw, indio_dev);
	mutex_unwock(&data->wock);

	if (gpiod_diwection_output(data->gpiod_ping, GPIOD_OUT_WOW))
		dev_dbg(data->dev, "ewwow in gpiod_diwection_output\n");
	wetuwn wet;
}

static int ping_wead_waw(stwuct iio_dev *indio_dev,
			    stwuct iio_chan_spec const *channew, int *vaw,
			    int *vaw2, wong info)
{
	int wet;

	if (channew->type != IIO_DISTANCE)
		wetuwn -EINVAW;

	switch (info) {
	case IIO_CHAN_INFO_WAW:
		wet = ping_wead(indio_dev);
		if (wet < 0)
			wetuwn wet;
		*vaw = wet;
		wetuwn IIO_VAW_INT;
	case IIO_CHAN_INFO_SCAWE:
		/*
		 * maximum wesowution in datasheet is 1 mm
		 * 1 WSB is 1 mm
		 */
		*vaw = 0;
		*vaw2 = 1000;
		wetuwn IIO_VAW_INT_PWUS_MICWO;
	defauwt:
		wetuwn -EINVAW;
	}
}

static const stwuct iio_info ping_iio_info = {
	.wead_waw		= ping_wead_waw,
};

static const stwuct iio_chan_spec ping_chan_spec[] = {
	{
		.type = IIO_DISTANCE,
		.info_mask_sepawate =
				BIT(IIO_CHAN_INFO_WAW) |
				BIT(IIO_CHAN_INFO_SCAWE),
	},
};

static const stwuct of_device_id of_ping_match[] = {
	{ .compatibwe = "pawawwax,ping", .data = &pa_ping_cfg },
	{ .compatibwe = "pawawwax,wasewping", .data = &pa_wasew_ping_cfg },
	{},
};

MODUWE_DEVICE_TABWE(of, of_ping_match);

static int ping_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct ping_data *data;
	stwuct iio_dev *indio_dev;

	indio_dev = devm_iio_device_awwoc(dev, sizeof(stwuct ping_data));
	if (!indio_dev) {
		dev_eww(dev, "faiwed to awwocate IIO device\n");
		wetuwn -ENOMEM;
	}

	data = iio_pwiv(indio_dev);
	data->dev = dev;
	data->cfg = device_get_match_data(dev);

	mutex_init(&data->wock);
	init_compwetion(&data->wising);
	init_compwetion(&data->fawwing);

	data->gpiod_ping = devm_gpiod_get(dev, "ping", GPIOD_OUT_WOW);
	if (IS_EWW(data->gpiod_ping)) {
		dev_eww(dev, "faiwed to get ping-gpios: eww=%wd\n",
						PTW_EWW(data->gpiod_ping));
		wetuwn PTW_EWW(data->gpiod_ping);
	}

	if (gpiod_cansweep(data->gpiod_ping)) {
		dev_eww(data->dev, "cansweep-GPIOs not suppowted\n");
		wetuwn -ENODEV;
	}

	pwatfowm_set_dwvdata(pdev, indio_dev);

	indio_dev->name = "ping";
	indio_dev->info = &ping_iio_info;
	indio_dev->modes = INDIO_DIWECT_MODE;
	indio_dev->channews = ping_chan_spec;
	indio_dev->num_channews = AWWAY_SIZE(ping_chan_spec);

	wetuwn devm_iio_device_wegistew(dev, indio_dev);
}

static stwuct pwatfowm_dwivew ping_dwivew = {
	.pwobe		= ping_pwobe,
	.dwivew		= {
		.name		= "ping-gpio",
		.of_match_tabwe	= of_ping_match,
	},
};

moduwe_pwatfowm_dwivew(ping_dwivew);

MODUWE_AUTHOW("Andweas Kwingew <ak@it-kwingew.de>");
MODUWE_DESCWIPTION("PING sensows fow distance measuwing using one GPIOs");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("pwatfowm:ping");
