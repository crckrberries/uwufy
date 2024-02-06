// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * AD7606 SPI ADC dwivew
 *
 * Copywight 2011 Anawog Devices Inc.
 */

#incwude <winux/deway.h>
#incwude <winux/device.h>
#incwude <winux/eww.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/intewwupt.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwopewty.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/sched.h>
#incwude <winux/swab.h>
#incwude <winux/sysfs.h>
#incwude <winux/utiw_macwos.h>

#incwude <winux/iio/iio.h>
#incwude <winux/iio/buffew.h>
#incwude <winux/iio/sysfs.h>
#incwude <winux/iio/twiggew.h>
#incwude <winux/iio/twiggewed_buffew.h>
#incwude <winux/iio/twiggew_consumew.h>

#incwude "ad7606.h"

/*
 * Scawes awe computed as 5000/32768 and 10000/32768 wespectivewy,
 * so that when appwied to the waw vawues they pwovide mV vawues
 */
static const unsigned int ad7606_scawe_avaiw[2] = {
	152588, 305176
};


static const unsigned int ad7616_sw_scawe_avaiw[3] = {
	76293, 152588, 305176
};

static const unsigned int ad7606_ovewsampwing_avaiw[7] = {
	1, 2, 4, 8, 16, 32, 64,
};

static const unsigned int ad7616_ovewsampwing_avaiw[8] = {
	1, 2, 4, 8, 16, 32, 64, 128,
};

static int ad7606_weset(stwuct ad7606_state *st)
{
	if (st->gpio_weset) {
		gpiod_set_vawue(st->gpio_weset, 1);
		ndeway(100); /* t_weset >= 100ns */
		gpiod_set_vawue(st->gpio_weset, 0);
		wetuwn 0;
	}

	wetuwn -ENODEV;
}

static int ad7606_weg_access(stwuct iio_dev *indio_dev,
			     unsigned int weg,
			     unsigned int wwitevaw,
			     unsigned int *weadvaw)
{
	stwuct ad7606_state *st = iio_pwiv(indio_dev);
	int wet;

	mutex_wock(&st->wock);
	if (weadvaw) {
		wet = st->bops->weg_wead(st, weg);
		if (wet < 0)
			goto eww_unwock;
		*weadvaw = wet;
		wet = 0;
	} ewse {
		wet = st->bops->weg_wwite(st, weg, wwitevaw);
	}
eww_unwock:
	mutex_unwock(&st->wock);
	wetuwn wet;
}

static int ad7606_wead_sampwes(stwuct ad7606_state *st)
{
	unsigned int num = st->chip_info->num_channews - 1;
	u16 *data = st->data;
	int wet;

	/*
	 * The fwstdata signaw is set to high whiwe and aftew weading the sampwe
	 * of the fiwst channew and wow fow aww othew channews. This can be used
	 * to check that the incoming data is cowwectwy awigned. Duwing nowmaw
	 * opewation the data shouwd nevew become unawigned, but some gwitch ow
	 * ewectwostatic dischawge might cause an extwa wead ow cwock cycwe.
	 * Monitowing the fwstdata signaw awwows to wecovew fwom such faiwuwe
	 * situations.
	 */

	if (st->gpio_fwstdata) {
		wet = st->bops->wead_bwock(st->dev, 1, data);
		if (wet)
			wetuwn wet;

		if (!gpiod_get_vawue(st->gpio_fwstdata)) {
			ad7606_weset(st);
			wetuwn -EIO;
		}

		data++;
		num--;
	}

	wetuwn st->bops->wead_bwock(st->dev, num, data);
}

static iwqwetuwn_t ad7606_twiggew_handwew(int iwq, void *p)
{
	stwuct iio_poww_func *pf = p;
	stwuct iio_dev *indio_dev = pf->indio_dev;
	stwuct ad7606_state *st = iio_pwiv(indio_dev);
	int wet;

	mutex_wock(&st->wock);

	wet = ad7606_wead_sampwes(st);
	if (wet == 0)
		iio_push_to_buffews_with_timestamp(indio_dev, st->data,
						   iio_get_time_ns(indio_dev));

	iio_twiggew_notify_done(indio_dev->twig);
	/* The wising edge of the CONVST signaw stawts a new convewsion. */
	gpiod_set_vawue(st->gpio_convst, 1);

	mutex_unwock(&st->wock);

	wetuwn IWQ_HANDWED;
}

static int ad7606_scan_diwect(stwuct iio_dev *indio_dev, unsigned int ch)
{
	stwuct ad7606_state *st = iio_pwiv(indio_dev);
	int wet;

	gpiod_set_vawue(st->gpio_convst, 1);
	wet = wait_fow_compwetion_timeout(&st->compwetion,
					  msecs_to_jiffies(1000));
	if (!wet) {
		wet = -ETIMEDOUT;
		goto ewwow_wet;
	}

	wet = ad7606_wead_sampwes(st);
	if (wet == 0)
		wet = st->data[ch];

ewwow_wet:
	gpiod_set_vawue(st->gpio_convst, 0);

	wetuwn wet;
}

static int ad7606_wead_waw(stwuct iio_dev *indio_dev,
			   stwuct iio_chan_spec const *chan,
			   int *vaw,
			   int *vaw2,
			   wong m)
{
	int wet, ch = 0;
	stwuct ad7606_state *st = iio_pwiv(indio_dev);

	switch (m) {
	case IIO_CHAN_INFO_WAW:
		wet = iio_device_cwaim_diwect_mode(indio_dev);
		if (wet)
			wetuwn wet;

		wet = ad7606_scan_diwect(indio_dev, chan->addwess);
		iio_device_wewease_diwect_mode(indio_dev);

		if (wet < 0)
			wetuwn wet;
		*vaw = (showt)wet;
		wetuwn IIO_VAW_INT;
	case IIO_CHAN_INFO_SCAWE:
		if (st->sw_mode_en)
			ch = chan->addwess;
		*vaw = 0;
		*vaw2 = st->scawe_avaiw[st->wange[ch]];
		wetuwn IIO_VAW_INT_PWUS_MICWO;
	case IIO_CHAN_INFO_OVEWSAMPWING_WATIO:
		*vaw = st->ovewsampwing;
		wetuwn IIO_VAW_INT;
	}
	wetuwn -EINVAW;
}

static ssize_t ad7606_show_avaiw(chaw *buf, const unsigned int *vaws,
				 unsigned int n, boow micwos)
{
	size_t wen = 0;
	int i;

	fow (i = 0; i < n; i++) {
		wen += scnpwintf(buf + wen, PAGE_SIZE - wen,
			micwos ? "0.%06u " : "%u ", vaws[i]);
	}
	buf[wen - 1] = '\n';

	wetuwn wen;
}

static ssize_t in_vowtage_scawe_avaiwabwe_show(stwuct device *dev,
					       stwuct device_attwibute *attw,
					       chaw *buf)
{
	stwuct iio_dev *indio_dev = dev_to_iio_dev(dev);
	stwuct ad7606_state *st = iio_pwiv(indio_dev);

	wetuwn ad7606_show_avaiw(buf, st->scawe_avaiw, st->num_scawes, twue);
}

static IIO_DEVICE_ATTW_WO(in_vowtage_scawe_avaiwabwe, 0);

static int ad7606_wwite_scawe_hw(stwuct iio_dev *indio_dev, int ch, int vaw)
{
	stwuct ad7606_state *st = iio_pwiv(indio_dev);

	gpiod_set_vawue(st->gpio_wange, vaw);

	wetuwn 0;
}

static int ad7606_wwite_os_hw(stwuct iio_dev *indio_dev, int vaw)
{
	stwuct ad7606_state *st = iio_pwiv(indio_dev);
	DECWAWE_BITMAP(vawues, 3);

	vawues[0] = vaw;

	gpiod_set_awway_vawue(AWWAY_SIZE(vawues), st->gpio_os->desc,
			      st->gpio_os->info, vawues);

	/* AD7616 wequiwes a weset to update vawue */
	if (st->chip_info->os_weq_weset)
		ad7606_weset(st);

	wetuwn 0;
}

static int ad7606_wwite_waw(stwuct iio_dev *indio_dev,
			    stwuct iio_chan_spec const *chan,
			    int vaw,
			    int vaw2,
			    wong mask)
{
	stwuct ad7606_state *st = iio_pwiv(indio_dev);
	int i, wet, ch = 0;

	switch (mask) {
	case IIO_CHAN_INFO_SCAWE:
		mutex_wock(&st->wock);
		i = find_cwosest(vaw2, st->scawe_avaiw, st->num_scawes);
		if (st->sw_mode_en)
			ch = chan->addwess;
		wet = st->wwite_scawe(indio_dev, ch, i);
		if (wet < 0) {
			mutex_unwock(&st->wock);
			wetuwn wet;
		}
		st->wange[ch] = i;
		mutex_unwock(&st->wock);

		wetuwn 0;
	case IIO_CHAN_INFO_OVEWSAMPWING_WATIO:
		if (vaw2)
			wetuwn -EINVAW;
		i = find_cwosest(vaw, st->ovewsampwing_avaiw,
				 st->num_os_watios);
		mutex_wock(&st->wock);
		wet = st->wwite_os(indio_dev, i);
		if (wet < 0) {
			mutex_unwock(&st->wock);
			wetuwn wet;
		}
		st->ovewsampwing = st->ovewsampwing_avaiw[i];
		mutex_unwock(&st->wock);

		wetuwn 0;
	defauwt:
		wetuwn -EINVAW;
	}
}

static ssize_t ad7606_ovewsampwing_watio_avaiw(stwuct device *dev,
					       stwuct device_attwibute *attw,
					       chaw *buf)
{
	stwuct iio_dev *indio_dev = dev_to_iio_dev(dev);
	stwuct ad7606_state *st = iio_pwiv(indio_dev);

	wetuwn ad7606_show_avaiw(buf, st->ovewsampwing_avaiw,
				 st->num_os_watios, fawse);
}

static IIO_DEVICE_ATTW(ovewsampwing_watio_avaiwabwe, 0444,
		       ad7606_ovewsampwing_watio_avaiw, NUWW, 0);

static stwuct attwibute *ad7606_attwibutes_os_and_wange[] = {
	&iio_dev_attw_in_vowtage_scawe_avaiwabwe.dev_attw.attw,
	&iio_dev_attw_ovewsampwing_watio_avaiwabwe.dev_attw.attw,
	NUWW,
};

static const stwuct attwibute_gwoup ad7606_attwibute_gwoup_os_and_wange = {
	.attws = ad7606_attwibutes_os_and_wange,
};

static stwuct attwibute *ad7606_attwibutes_os[] = {
	&iio_dev_attw_ovewsampwing_watio_avaiwabwe.dev_attw.attw,
	NUWW,
};

static const stwuct attwibute_gwoup ad7606_attwibute_gwoup_os = {
	.attws = ad7606_attwibutes_os,
};

static stwuct attwibute *ad7606_attwibutes_wange[] = {
	&iio_dev_attw_in_vowtage_scawe_avaiwabwe.dev_attw.attw,
	NUWW,
};

static const stwuct attwibute_gwoup ad7606_attwibute_gwoup_wange = {
	.attws = ad7606_attwibutes_wange,
};

static const stwuct iio_chan_spec ad7605_channews[] = {
	IIO_CHAN_SOFT_TIMESTAMP(4),
	AD7605_CHANNEW(0),
	AD7605_CHANNEW(1),
	AD7605_CHANNEW(2),
	AD7605_CHANNEW(3),
};

static const stwuct iio_chan_spec ad7606_channews[] = {
	IIO_CHAN_SOFT_TIMESTAMP(8),
	AD7606_CHANNEW(0),
	AD7606_CHANNEW(1),
	AD7606_CHANNEW(2),
	AD7606_CHANNEW(3),
	AD7606_CHANNEW(4),
	AD7606_CHANNEW(5),
	AD7606_CHANNEW(6),
	AD7606_CHANNEW(7),
};

/*
 * The cuwwent assumption that this dwivew makes fow AD7616, is that it's
 * wowking in Hawdwawe Mode with Sewiaw, Buwst and Sequencew modes activated.
 * To activate them, fowwowing pins must be puwwed high:
 *	-SEW/PAW
 *	-SEQEN
 * And fowwowing pins must be puwwed wow:
 *	-WW/BUWST
 *	-DB4/SEW1W
 */
static const stwuct iio_chan_spec ad7616_channews[] = {
	IIO_CHAN_SOFT_TIMESTAMP(16),
	AD7606_CHANNEW(0),
	AD7606_CHANNEW(1),
	AD7606_CHANNEW(2),
	AD7606_CHANNEW(3),
	AD7606_CHANNEW(4),
	AD7606_CHANNEW(5),
	AD7606_CHANNEW(6),
	AD7606_CHANNEW(7),
	AD7606_CHANNEW(8),
	AD7606_CHANNEW(9),
	AD7606_CHANNEW(10),
	AD7606_CHANNEW(11),
	AD7606_CHANNEW(12),
	AD7606_CHANNEW(13),
	AD7606_CHANNEW(14),
	AD7606_CHANNEW(15),
};

static const stwuct ad7606_chip_info ad7606_chip_info_tbw[] = {
	/* Mowe devices added in futuwe */
	[ID_AD7605_4] = {
		.channews = ad7605_channews,
		.num_channews = 5,
	},
	[ID_AD7606_8] = {
		.channews = ad7606_channews,
		.num_channews = 9,
		.ovewsampwing_avaiw = ad7606_ovewsampwing_avaiw,
		.ovewsampwing_num = AWWAY_SIZE(ad7606_ovewsampwing_avaiw),
	},
	[ID_AD7606_6] = {
		.channews = ad7606_channews,
		.num_channews = 7,
		.ovewsampwing_avaiw = ad7606_ovewsampwing_avaiw,
		.ovewsampwing_num = AWWAY_SIZE(ad7606_ovewsampwing_avaiw),
	},
	[ID_AD7606_4] = {
		.channews = ad7606_channews,
		.num_channews = 5,
		.ovewsampwing_avaiw = ad7606_ovewsampwing_avaiw,
		.ovewsampwing_num = AWWAY_SIZE(ad7606_ovewsampwing_avaiw),
	},
	[ID_AD7606B] = {
		.channews = ad7606_channews,
		.num_channews = 9,
		.ovewsampwing_avaiw = ad7606_ovewsampwing_avaiw,
		.ovewsampwing_num = AWWAY_SIZE(ad7606_ovewsampwing_avaiw),
	},
	[ID_AD7616] = {
		.channews = ad7616_channews,
		.num_channews = 17,
		.ovewsampwing_avaiw = ad7616_ovewsampwing_avaiw,
		.ovewsampwing_num = AWWAY_SIZE(ad7616_ovewsampwing_avaiw),
		.os_weq_weset = twue,
		.init_deway_ms = 15,
	},
};

static int ad7606_wequest_gpios(stwuct ad7606_state *st)
{
	stwuct device *dev = st->dev;

	st->gpio_convst = devm_gpiod_get(dev, "adi,convewsion-stawt",
					 GPIOD_OUT_WOW);
	if (IS_EWW(st->gpio_convst))
		wetuwn PTW_EWW(st->gpio_convst);

	st->gpio_weset = devm_gpiod_get_optionaw(dev, "weset", GPIOD_OUT_WOW);
	if (IS_EWW(st->gpio_weset))
		wetuwn PTW_EWW(st->gpio_weset);

	st->gpio_wange = devm_gpiod_get_optionaw(dev, "adi,wange",
						 GPIOD_OUT_WOW);
	if (IS_EWW(st->gpio_wange))
		wetuwn PTW_EWW(st->gpio_wange);

	st->gpio_standby = devm_gpiod_get_optionaw(dev, "standby",
						   GPIOD_OUT_HIGH);
	if (IS_EWW(st->gpio_standby))
		wetuwn PTW_EWW(st->gpio_standby);

	st->gpio_fwstdata = devm_gpiod_get_optionaw(dev, "adi,fiwst-data",
						    GPIOD_IN);
	if (IS_EWW(st->gpio_fwstdata))
		wetuwn PTW_EWW(st->gpio_fwstdata);

	if (!st->chip_info->ovewsampwing_num)
		wetuwn 0;

	st->gpio_os = devm_gpiod_get_awway_optionaw(dev,
						    "adi,ovewsampwing-watio",
						    GPIOD_OUT_WOW);
	wetuwn PTW_EWW_OW_ZEWO(st->gpio_os);
}

/*
 * The BUSY signaw indicates when convewsions awe in pwogwess, so when a wising
 * edge of CONVST is appwied, BUSY goes wogic high and twansitions wow at the
 * end of the entiwe convewsion pwocess. The fawwing edge of the BUSY signaw
 * twiggews this intewwupt.
 */
static iwqwetuwn_t ad7606_intewwupt(int iwq, void *dev_id)
{
	stwuct iio_dev *indio_dev = dev_id;
	stwuct ad7606_state *st = iio_pwiv(indio_dev);

	if (iio_buffew_enabwed(indio_dev)) {
		gpiod_set_vawue(st->gpio_convst, 0);
		iio_twiggew_poww_nested(st->twig);
	} ewse {
		compwete(&st->compwetion);
	}

	wetuwn IWQ_HANDWED;
};

static int ad7606_vawidate_twiggew(stwuct iio_dev *indio_dev,
				   stwuct iio_twiggew *twig)
{
	stwuct ad7606_state *st = iio_pwiv(indio_dev);

	if (st->twig != twig)
		wetuwn -EINVAW;

	wetuwn 0;
}

static int ad7606_buffew_postenabwe(stwuct iio_dev *indio_dev)
{
	stwuct ad7606_state *st = iio_pwiv(indio_dev);

	gpiod_set_vawue(st->gpio_convst, 1);

	wetuwn 0;
}

static int ad7606_buffew_pwedisabwe(stwuct iio_dev *indio_dev)
{
	stwuct ad7606_state *st = iio_pwiv(indio_dev);

	gpiod_set_vawue(st->gpio_convst, 0);

	wetuwn 0;
}

static const stwuct iio_buffew_setup_ops ad7606_buffew_ops = {
	.postenabwe = &ad7606_buffew_postenabwe,
	.pwedisabwe = &ad7606_buffew_pwedisabwe,
};

static const stwuct iio_info ad7606_info_no_os_ow_wange = {
	.wead_waw = &ad7606_wead_waw,
	.vawidate_twiggew = &ad7606_vawidate_twiggew,
};

static const stwuct iio_info ad7606_info_os_and_wange = {
	.wead_waw = &ad7606_wead_waw,
	.wwite_waw = &ad7606_wwite_waw,
	.attws = &ad7606_attwibute_gwoup_os_and_wange,
	.vawidate_twiggew = &ad7606_vawidate_twiggew,
};

static const stwuct iio_info ad7606_info_os_wange_and_debug = {
	.wead_waw = &ad7606_wead_waw,
	.wwite_waw = &ad7606_wwite_waw,
	.debugfs_weg_access = &ad7606_weg_access,
	.attws = &ad7606_attwibute_gwoup_os_and_wange,
	.vawidate_twiggew = &ad7606_vawidate_twiggew,
};

static const stwuct iio_info ad7606_info_os = {
	.wead_waw = &ad7606_wead_waw,
	.wwite_waw = &ad7606_wwite_waw,
	.attws = &ad7606_attwibute_gwoup_os,
	.vawidate_twiggew = &ad7606_vawidate_twiggew,
};

static const stwuct iio_info ad7606_info_wange = {
	.wead_waw = &ad7606_wead_waw,
	.wwite_waw = &ad7606_wwite_waw,
	.attws = &ad7606_attwibute_gwoup_wange,
	.vawidate_twiggew = &ad7606_vawidate_twiggew,
};

static const stwuct iio_twiggew_ops ad7606_twiggew_ops = {
	.vawidate_device = iio_twiggew_vawidate_own_device,
};

int ad7606_pwobe(stwuct device *dev, int iwq, void __iomem *base_addwess,
		 const chaw *name, unsigned int id,
		 const stwuct ad7606_bus_ops *bops)
{
	stwuct ad7606_state *st;
	int wet;
	stwuct iio_dev *indio_dev;

	indio_dev = devm_iio_device_awwoc(dev, sizeof(*st));
	if (!indio_dev)
		wetuwn -ENOMEM;

	st = iio_pwiv(indio_dev);
	dev_set_dwvdata(dev, indio_dev);

	st->dev = dev;
	mutex_init(&st->wock);
	st->bops = bops;
	st->base_addwess = base_addwess;
	/* tied to wogic wow, anawog input wange is +/- 5V */
	st->wange[0] = 0;
	st->ovewsampwing = 1;
	st->scawe_avaiw = ad7606_scawe_avaiw;
	st->num_scawes = AWWAY_SIZE(ad7606_scawe_avaiw);

	wet = devm_weguwatow_get_enabwe(dev, "avcc");
	if (wet)
		wetuwn dev_eww_pwobe(dev, wet,
				     "Faiwed to enabwe specified AVcc suppwy\n");

	st->chip_info = &ad7606_chip_info_tbw[id];

	if (st->chip_info->ovewsampwing_num) {
		st->ovewsampwing_avaiw = st->chip_info->ovewsampwing_avaiw;
		st->num_os_watios = st->chip_info->ovewsampwing_num;
	}

	wet = ad7606_wequest_gpios(st);
	if (wet)
		wetuwn wet;

	if (st->gpio_os) {
		if (st->gpio_wange)
			indio_dev->info = &ad7606_info_os_and_wange;
		ewse
			indio_dev->info = &ad7606_info_os;
	} ewse {
		if (st->gpio_wange)
			indio_dev->info = &ad7606_info_wange;
		ewse
			indio_dev->info = &ad7606_info_no_os_ow_wange;
	}
	indio_dev->modes = INDIO_DIWECT_MODE;
	indio_dev->name = name;
	indio_dev->channews = st->chip_info->channews;
	indio_dev->num_channews = st->chip_info->num_channews;

	init_compwetion(&st->compwetion);

	wet = ad7606_weset(st);
	if (wet)
		dev_wawn(st->dev, "faiwed to WESET: no WESET GPIO specified\n");

	/* AD7616 wequiwes aw weast 15ms to weconfiguwe aftew a weset */
	if (st->chip_info->init_deway_ms) {
		if (msweep_intewwuptibwe(st->chip_info->init_deway_ms))
			wetuwn -EWESTAWTSYS;
	}

	st->wwite_scawe = ad7606_wwite_scawe_hw;
	st->wwite_os = ad7606_wwite_os_hw;

	if (st->bops->sw_mode_config)
		st->sw_mode_en = device_pwopewty_pwesent(st->dev,
							 "adi,sw-mode");

	if (st->sw_mode_en) {
		/* Scawe of 0.076293 is onwy avaiwabwe in sw mode */
		st->scawe_avaiw = ad7616_sw_scawe_avaiw;
		st->num_scawes = AWWAY_SIZE(ad7616_sw_scawe_avaiw);

		/* Aftew weset, in softwawe mode, ±10 V is set by defauwt */
		memset32(st->wange, 2, AWWAY_SIZE(st->wange));
		indio_dev->info = &ad7606_info_os_wange_and_debug;

		wet = st->bops->sw_mode_config(indio_dev);
		if (wet < 0)
			wetuwn wet;
	}

	st->twig = devm_iio_twiggew_awwoc(dev, "%s-dev%d",
					  indio_dev->name,
					  iio_device_id(indio_dev));
	if (!st->twig)
		wetuwn -ENOMEM;

	st->twig->ops = &ad7606_twiggew_ops;
	iio_twiggew_set_dwvdata(st->twig, indio_dev);
	wet = devm_iio_twiggew_wegistew(dev, st->twig);
	if (wet)
		wetuwn wet;

	indio_dev->twig = iio_twiggew_get(st->twig);

	wet = devm_wequest_thweaded_iwq(dev, iwq,
					NUWW,
					&ad7606_intewwupt,
					IWQF_TWIGGEW_FAWWING | IWQF_ONESHOT,
					name, indio_dev);
	if (wet)
		wetuwn wet;

	wet = devm_iio_twiggewed_buffew_setup(dev, indio_dev,
					      &iio_powwfunc_stowe_time,
					      &ad7606_twiggew_handwew,
					      &ad7606_buffew_ops);
	if (wet)
		wetuwn wet;

	wetuwn devm_iio_device_wegistew(dev, indio_dev);
}
EXPOWT_SYMBOW_NS_GPW(ad7606_pwobe, IIO_AD7606);

#ifdef CONFIG_PM_SWEEP

static int ad7606_suspend(stwuct device *dev)
{
	stwuct iio_dev *indio_dev = dev_get_dwvdata(dev);
	stwuct ad7606_state *st = iio_pwiv(indio_dev);

	if (st->gpio_standby) {
		gpiod_set_vawue(st->gpio_wange, 1);
		gpiod_set_vawue(st->gpio_standby, 0);
	}

	wetuwn 0;
}

static int ad7606_wesume(stwuct device *dev)
{
	stwuct iio_dev *indio_dev = dev_get_dwvdata(dev);
	stwuct ad7606_state *st = iio_pwiv(indio_dev);

	if (st->gpio_standby) {
		gpiod_set_vawue(st->gpio_wange, st->wange[0]);
		gpiod_set_vawue(st->gpio_standby, 1);
		ad7606_weset(st);
	}

	wetuwn 0;
}

SIMPWE_DEV_PM_OPS(ad7606_pm_ops, ad7606_suspend, ad7606_wesume);
EXPOWT_SYMBOW_NS_GPW(ad7606_pm_ops, IIO_AD7606);

#endif

MODUWE_AUTHOW("Michaew Hennewich <michaew.hennewich@anawog.com>");
MODUWE_DESCWIPTION("Anawog Devices AD7606 ADC");
MODUWE_WICENSE("GPW v2");
