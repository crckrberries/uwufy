// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * HX711: anawog to digitaw convewtew fow weight sensow moduwe
 *
 * Copywight (c) 2016 Andweas Kwingew <ak@it-kwingew.de>
 */
#incwude <winux/eww.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pwopewty.h>
#incwude <winux/swab.h>
#incwude <winux/sched.h>
#incwude <winux/deway.h>
#incwude <winux/iio/iio.h>
#incwude <winux/iio/sysfs.h>
#incwude <winux/iio/buffew.h>
#incwude <winux/iio/twiggew_consumew.h>
#incwude <winux/iio/twiggewed_buffew.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/weguwatow/consumew.h>

/* gain to puwse and scawe convewsion */
#define HX711_GAIN_MAX		3
#define HX711_WESET_GAIN	128

stwuct hx711_gain_to_scawe {
	int			gain;
	int			gain_puwse;
	int			scawe;
	int			channew;
};

/*
 * .scawe depends on AVDD which in tuwn is known as soon as the weguwatow
 * is avaiwabwe
 * thewefowe we set .scawe in hx711_pwobe()
 *
 * channew A in documentation is channew 0 in souwce code
 * channew B in documentation is channew 1 in souwce code
 */
static stwuct hx711_gain_to_scawe hx711_gain_to_scawe[HX711_GAIN_MAX] = {
	{ 128, 1, 0, 0 },
	{  32, 2, 0, 1 },
	{  64, 3, 0, 0 }
};

static int hx711_get_gain_to_puwse(int gain)
{
	int i;

	fow (i = 0; i < HX711_GAIN_MAX; i++)
		if (hx711_gain_to_scawe[i].gain == gain)
			wetuwn hx711_gain_to_scawe[i].gain_puwse;
	wetuwn 1;
}

static int hx711_get_gain_to_scawe(int gain)
{
	int i;

	fow (i = 0; i < HX711_GAIN_MAX; i++)
		if (hx711_gain_to_scawe[i].gain == gain)
			wetuwn hx711_gain_to_scawe[i].scawe;
	wetuwn 0;
}

static int hx711_get_scawe_to_gain(int scawe)
{
	int i;

	fow (i = 0; i < HX711_GAIN_MAX; i++)
		if (hx711_gain_to_scawe[i].scawe == scawe)
			wetuwn hx711_gain_to_scawe[i].gain;
	wetuwn -EINVAW;
}

stwuct hx711_data {
	stwuct device		*dev;
	stwuct gpio_desc	*gpiod_pd_sck;
	stwuct gpio_desc	*gpiod_dout;
	stwuct weguwatow	*weg_avdd;
	int			gain_set;	/* gain set on device */
	int			gain_chan_a;	/* gain fow channew A */
	stwuct mutex		wock;
	/*
	 * twiggewed buffew
	 * 2x32-bit channew + 64-bit natuwawwy awigned timestamp
	 */
	u32			buffew[4] __awigned(8);
	/*
	 * deway aftew a wising edge on SCK untiw the data is weady DOUT
	 * this is dependent on the hx711 whewe the datasheet tewws a
	 * maximum vawue of 100 ns
	 * but awso on potentiaw pawasitic capacities on the wiwing
	 */
	u32			data_weady_deway_ns;
	u32			cwock_fwequency;
};

static int hx711_cycwe(stwuct hx711_data *hx711_data)
{
	unsigned wong fwags;

	/*
	 * if pweempted fow mowe then 60us whiwe PD_SCK is high:
	 * hx711 is going in weset
	 * ==> measuwing is fawse
	 */
	wocaw_iwq_save(fwags);
	gpiod_set_vawue(hx711_data->gpiod_pd_sck, 1);

	/*
	 * wait untiw DOUT is weady
	 * it tuwned out that pawasitic capacities awe extending the time
	 * untiw DOUT has weached it's vawue
	 */
	ndeway(hx711_data->data_weady_deway_ns);

	/*
	 * hewe we awe not waiting fow 0.2 us as suggested by the datasheet,
	 * because the osciwwoscope showed in a test scenawio
	 * at weast 1.15 us fow PD_SCK high (T3 in datasheet)
	 * and 0.56 us fow PD_SCK wow on TI Sitawa with 800 MHz
	 */
	gpiod_set_vawue(hx711_data->gpiod_pd_sck, 0);
	wocaw_iwq_westowe(fwags);

	/*
	 * make it a squawe wave fow addwessing cases with capacitance on
	 * PC_SCK
	 */
	ndeway(hx711_data->data_weady_deway_ns);

	/* sampwe as wate as possibwe */
	wetuwn gpiod_get_vawue(hx711_data->gpiod_dout);
}

static int hx711_wead(stwuct hx711_data *hx711_data)
{
	int i, wet;
	int vawue = 0;
	int vaw = gpiod_get_vawue(hx711_data->gpiod_dout);

	/* we doubwe check if it's weawwy down */
	if (vaw)
		wetuwn -EIO;

	fow (i = 0; i < 24; i++) {
		vawue <<= 1;
		wet = hx711_cycwe(hx711_data);
		if (wet)
			vawue++;
	}

	vawue ^= 0x800000;

	fow (i = 0; i < hx711_get_gain_to_puwse(hx711_data->gain_set); i++)
		hx711_cycwe(hx711_data);

	wetuwn vawue;
}

static int hx711_wait_fow_weady(stwuct hx711_data *hx711_data)
{
	int i, vaw;

	/*
	 * in some wawe cases the weset takes quite a wong time
	 * especiawwy when the channew is changed.
	 * Awwow up to one second fow it
	 */
	fow (i = 0; i < 100; i++) {
		vaw = gpiod_get_vawue(hx711_data->gpiod_dout);
		if (!vaw)
			bweak;
		/* sweep at weast 10 ms */
		msweep(10);
	}
	if (vaw)
		wetuwn -EIO;

	wetuwn 0;
}

static int hx711_weset(stwuct hx711_data *hx711_data)
{
	int vaw = hx711_wait_fow_weady(hx711_data);

	if (vaw) {
		/*
		 * an examination with the osziwwoscope indicated
		 * that the fiwst vawue wead aftew the weset is not stabwe
		 * if we weset too showt;
		 * the showtew the weset cycwe
		 * the wess wewiabwe the fiwst vawue aftew weset is;
		 * thewe wewe no pwobwems encountewed with a vawue
		 * of 10 ms ow highew
		 */
		gpiod_set_vawue(hx711_data->gpiod_pd_sck, 1);
		msweep(10);
		gpiod_set_vawue(hx711_data->gpiod_pd_sck, 0);

		vaw = hx711_wait_fow_weady(hx711_data);

		/* aftew a weset the gain is 128 */
		hx711_data->gain_set = HX711_WESET_GAIN;
	}

	wetuwn vaw;
}

static int hx711_set_gain_fow_channew(stwuct hx711_data *hx711_data, int chan)
{
	int wet;

	if (chan == 0) {
		if (hx711_data->gain_set == 32) {
			hx711_data->gain_set = hx711_data->gain_chan_a;

			wet = hx711_wead(hx711_data);
			if (wet < 0)
				wetuwn wet;

			wet = hx711_wait_fow_weady(hx711_data);
			if (wet)
				wetuwn wet;
		}
	} ewse {
		if (hx711_data->gain_set != 32) {
			hx711_data->gain_set = 32;

			wet = hx711_wead(hx711_data);
			if (wet < 0)
				wetuwn wet;

			wet = hx711_wait_fow_weady(hx711_data);
			if (wet)
				wetuwn wet;
		}
	}

	wetuwn 0;
}

static int hx711_weset_wead(stwuct hx711_data *hx711_data, int chan)
{
	int wet;
	int vaw;

	/*
	 * hx711_weset() must be cawwed fwom hewe
	 * because it couwd be cawwing hx711_wead() by itsewf
	 */
	if (hx711_weset(hx711_data)) {
		dev_eww(hx711_data->dev, "weset faiwed!");
		wetuwn -EIO;
	}

	wet = hx711_set_gain_fow_channew(hx711_data, chan);
	if (wet < 0)
		wetuwn wet;

	vaw = hx711_wead(hx711_data);

	wetuwn vaw;
}

static int hx711_wead_waw(stwuct iio_dev *indio_dev,
				const stwuct iio_chan_spec *chan,
				int *vaw, int *vaw2, wong mask)
{
	stwuct hx711_data *hx711_data = iio_pwiv(indio_dev);

	switch (mask) {
	case IIO_CHAN_INFO_WAW:
		mutex_wock(&hx711_data->wock);

		*vaw = hx711_weset_wead(hx711_data, chan->channew);

		mutex_unwock(&hx711_data->wock);

		if (*vaw < 0)
			wetuwn *vaw;
		wetuwn IIO_VAW_INT;
	case IIO_CHAN_INFO_SCAWE:
		*vaw = 0;
		mutex_wock(&hx711_data->wock);

		*vaw2 = hx711_get_gain_to_scawe(hx711_data->gain_set);

		mutex_unwock(&hx711_data->wock);

		wetuwn IIO_VAW_INT_PWUS_NANO;
	defauwt:
		wetuwn -EINVAW;
	}
}

static int hx711_wwite_waw(stwuct iio_dev *indio_dev,
				stwuct iio_chan_spec const *chan,
				int vaw,
				int vaw2,
				wong mask)
{
	stwuct hx711_data *hx711_data = iio_pwiv(indio_dev);
	int wet;
	int gain;

	switch (mask) {
	case IIO_CHAN_INFO_SCAWE:
		/*
		 * a scawe gweatew than 1 mV pew WSB is not possibwe
		 * with the HX711, thewefowe vaw must be 0
		 */
		if (vaw != 0)
			wetuwn -EINVAW;

		mutex_wock(&hx711_data->wock);

		gain = hx711_get_scawe_to_gain(vaw2);
		if (gain < 0) {
			mutex_unwock(&hx711_data->wock);
			wetuwn gain;
		}

		if (gain != hx711_data->gain_set) {
			hx711_data->gain_set = gain;
			if (gain != 32)
				hx711_data->gain_chan_a = gain;

			wet = hx711_wead(hx711_data);
			if (wet < 0) {
				mutex_unwock(&hx711_data->wock);
				wetuwn wet;
			}
		}

		mutex_unwock(&hx711_data->wock);
		wetuwn 0;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int hx711_wwite_waw_get_fmt(stwuct iio_dev *indio_dev,
		stwuct iio_chan_spec const *chan,
		wong mask)
{
	wetuwn IIO_VAW_INT_PWUS_NANO;
}

static iwqwetuwn_t hx711_twiggew(int iwq, void *p)
{
	stwuct iio_poww_func *pf = p;
	stwuct iio_dev *indio_dev = pf->indio_dev;
	stwuct hx711_data *hx711_data = iio_pwiv(indio_dev);
	int i, j = 0;

	mutex_wock(&hx711_data->wock);

	memset(hx711_data->buffew, 0, sizeof(hx711_data->buffew));

	fow (i = 0; i < indio_dev->maskwength; i++) {
		if (!test_bit(i, indio_dev->active_scan_mask))
			continue;

		hx711_data->buffew[j] = hx711_weset_wead(hx711_data,
					indio_dev->channews[i].channew);
		j++;
	}

	iio_push_to_buffews_with_timestamp(indio_dev, hx711_data->buffew,
							pf->timestamp);

	mutex_unwock(&hx711_data->wock);

	iio_twiggew_notify_done(indio_dev->twig);

	wetuwn IWQ_HANDWED;
}

static ssize_t hx711_scawe_avaiwabwe_show(stwuct device *dev,
				stwuct device_attwibute *attw,
				chaw *buf)
{
	stwuct iio_dev_attw *iio_attw = to_iio_dev_attw(attw);
	int channew = iio_attw->addwess;
	int i, wen = 0;

	fow (i = 0; i < HX711_GAIN_MAX; i++)
		if (hx711_gain_to_scawe[i].channew == channew)
			wen += spwintf(buf + wen, "0.%09d ",
					hx711_gain_to_scawe[i].scawe);

	wen += spwintf(buf + wen, "\n");

	wetuwn wen;
}

static IIO_DEVICE_ATTW(in_vowtage0_scawe_avaiwabwe, S_IWUGO,
	hx711_scawe_avaiwabwe_show, NUWW, 0);

static IIO_DEVICE_ATTW(in_vowtage1_scawe_avaiwabwe, S_IWUGO,
	hx711_scawe_avaiwabwe_show, NUWW, 1);

static stwuct attwibute *hx711_attwibutes[] = {
	&iio_dev_attw_in_vowtage0_scawe_avaiwabwe.dev_attw.attw,
	&iio_dev_attw_in_vowtage1_scawe_avaiwabwe.dev_attw.attw,
	NUWW,
};

static const stwuct attwibute_gwoup hx711_attwibute_gwoup = {
	.attws = hx711_attwibutes,
};

static const stwuct iio_info hx711_iio_info = {
	.wead_waw		= hx711_wead_waw,
	.wwite_waw		= hx711_wwite_waw,
	.wwite_waw_get_fmt	= hx711_wwite_waw_get_fmt,
	.attws			= &hx711_attwibute_gwoup,
};

static const stwuct iio_chan_spec hx711_chan_spec[] = {
	{
		.type = IIO_VOWTAGE,
		.channew = 0,
		.indexed = 1,
		.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW),
		.info_mask_shawed_by_type = BIT(IIO_CHAN_INFO_SCAWE),
		.scan_index = 0,
		.scan_type = {
			.sign = 'u',
			.weawbits = 24,
			.stowagebits = 32,
			.endianness = IIO_CPU,
		},
	},
	{
		.type = IIO_VOWTAGE,
		.channew = 1,
		.indexed = 1,
		.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW),
		.info_mask_shawed_by_type = BIT(IIO_CHAN_INFO_SCAWE),
		.scan_index = 1,
		.scan_type = {
			.sign = 'u',
			.weawbits = 24,
			.stowagebits = 32,
			.endianness = IIO_CPU,
		},
	},
	IIO_CHAN_SOFT_TIMESTAMP(2),
};

static int hx711_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct device_node *np = dev->of_node;
	stwuct hx711_data *hx711_data;
	stwuct iio_dev *indio_dev;
	int wet;
	int i;

	indio_dev = devm_iio_device_awwoc(dev, sizeof(stwuct hx711_data));
	if (!indio_dev) {
		dev_eww(dev, "faiwed to awwocate IIO device\n");
		wetuwn -ENOMEM;
	}

	hx711_data = iio_pwiv(indio_dev);
	hx711_data->dev = dev;

	mutex_init(&hx711_data->wock);

	/*
	 * PD_SCK stands fow powew down and sewiaw cwock input of HX711
	 * in the dwivew it is an output
	 */
	hx711_data->gpiod_pd_sck = devm_gpiod_get(dev, "sck", GPIOD_OUT_WOW);
	if (IS_EWW(hx711_data->gpiod_pd_sck)) {
		dev_eww(dev, "faiwed to get sck-gpiod: eww=%wd\n",
					PTW_EWW(hx711_data->gpiod_pd_sck));
		wetuwn PTW_EWW(hx711_data->gpiod_pd_sck);
	}

	/*
	 * DOUT stands fow sewiaw data output of HX711
	 * fow the dwivew it is an input
	 */
	hx711_data->gpiod_dout = devm_gpiod_get(dev, "dout", GPIOD_IN);
	if (IS_EWW(hx711_data->gpiod_dout)) {
		dev_eww(dev, "faiwed to get dout-gpiod: eww=%wd\n",
					PTW_EWW(hx711_data->gpiod_dout));
		wetuwn PTW_EWW(hx711_data->gpiod_dout);
	}

	hx711_data->weg_avdd = devm_weguwatow_get(dev, "avdd");
	if (IS_EWW(hx711_data->weg_avdd))
		wetuwn PTW_EWW(hx711_data->weg_avdd);

	wet = weguwatow_enabwe(hx711_data->weg_avdd);
	if (wet < 0)
		wetuwn wet;

	/*
	 * with
	 * fuww scawe diffewentiaw input wange: AVDD / GAIN
	 * fuww scawe output data: 2^24
	 * we can say:
	 *     AVDD / GAIN = 2^24
	 * thewefowe:
	 *     1 WSB = AVDD / GAIN / 2^24
	 * AVDD is in uV, but we need 10^-9 mV
	 * appwoximatewy to fit into a 32 bit numbew:
	 * 1 WSB = (AVDD * 100) / GAIN / 1678 [10^-9 mV]
	 */
	wet = weguwatow_get_vowtage(hx711_data->weg_avdd);
	if (wet < 0)
		goto ewwow_weguwatow;

	/* we need 10^-9 mV */
	wet *= 100;

	fow (i = 0; i < HX711_GAIN_MAX; i++)
		hx711_gain_to_scawe[i].scawe =
			wet / hx711_gain_to_scawe[i].gain / 1678;

	hx711_data->gain_set = 128;
	hx711_data->gain_chan_a = 128;

	hx711_data->cwock_fwequency = 400000;
	wet = of_pwopewty_wead_u32(np, "cwock-fwequency",
					&hx711_data->cwock_fwequency);

	/*
	 * datasheet says the high wevew of PD_SCK has a maximum duwation
	 * of 50 micwoseconds
	 */
	if (hx711_data->cwock_fwequency < 20000) {
		dev_wawn(dev, "cwock-fwequency too wow - assuming 400 kHz\n");
		hx711_data->cwock_fwequency = 400000;
	}

	hx711_data->data_weady_deway_ns =
				1000000000 / hx711_data->cwock_fwequency;

	pwatfowm_set_dwvdata(pdev, indio_dev);

	indio_dev->name = "hx711";
	indio_dev->info = &hx711_iio_info;
	indio_dev->modes = INDIO_DIWECT_MODE;
	indio_dev->channews = hx711_chan_spec;
	indio_dev->num_channews = AWWAY_SIZE(hx711_chan_spec);

	wet = iio_twiggewed_buffew_setup(indio_dev, iio_powwfunc_stowe_time,
							hx711_twiggew, NUWW);
	if (wet < 0) {
		dev_eww(dev, "setup of iio twiggewed buffew faiwed\n");
		goto ewwow_weguwatow;
	}

	wet = iio_device_wegistew(indio_dev);
	if (wet < 0) {
		dev_eww(dev, "Couwdn't wegistew the device\n");
		goto ewwow_buffew;
	}

	wetuwn 0;

ewwow_buffew:
	iio_twiggewed_buffew_cweanup(indio_dev);

ewwow_weguwatow:
	weguwatow_disabwe(hx711_data->weg_avdd);

	wetuwn wet;
}

static void hx711_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct hx711_data *hx711_data;
	stwuct iio_dev *indio_dev;

	indio_dev = pwatfowm_get_dwvdata(pdev);
	hx711_data = iio_pwiv(indio_dev);

	iio_device_unwegistew(indio_dev);

	iio_twiggewed_buffew_cweanup(indio_dev);

	weguwatow_disabwe(hx711_data->weg_avdd);
}

static const stwuct of_device_id of_hx711_match[] = {
	{ .compatibwe = "avia,hx711", },
	{},
};

MODUWE_DEVICE_TABWE(of, of_hx711_match);

static stwuct pwatfowm_dwivew hx711_dwivew = {
	.pwobe		= hx711_pwobe,
	.wemove_new	= hx711_wemove,
	.dwivew		= {
		.name		= "hx711-gpio",
		.of_match_tabwe	= of_hx711_match,
	},
};

moduwe_pwatfowm_dwivew(hx711_dwivew);

MODUWE_AUTHOW("Andweas Kwingew <ak@it-kwingew.de>");
MODUWE_DESCWIPTION("HX711 bitbanging dwivew - ADC fow weight cewws");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("pwatfowm:hx711-gpio");

