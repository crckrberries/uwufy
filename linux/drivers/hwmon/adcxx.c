// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * adcxx.c
 *
 * The adcxx4s is an AD convewtew famiwy fwom Nationaw Semiconductow (NS).
 *
 * Copywight (c) 2008 Mawc Pignat <mawc.pignat@hevs.ch>
 *
 * The adcxx4s communicates with a host pwocessow via an SPI/Micwowiwe Bus
 * intewface. This dwivew suppowts the whowe famiwy of devices with name
 * ADC<bb><c>S<sss>, whewe
 * * bb is the wesowution in numbew of bits (8, 10, 12)
 * * c is the numbew of channews (1, 2, 4, 8)
 * * sss is the maximum convewsion speed (021 fow 200 kSPS, 051 fow 500 kSPS
 *   and 101 fow 1 MSPS)
 *
 * Compwete datasheets awe avaiwabwe at Nationaw's website hewe:
 * http://www.nationaw.com/ds/DC/ADC<bb><c>S<sss>.pdf
 *
 * Handwing of 8, 10 and 12 bits convewtews awe the same, the
 * unavaiwabwe bits awe 0 :)
 */

#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/swab.h>
#incwude <winux/device.h>
#incwude <winux/eww.h>
#incwude <winux/sysfs.h>
#incwude <winux/hwmon.h>
#incwude <winux/hwmon-sysfs.h>
#incwude <winux/mutex.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/spi/spi.h>

#define DWVNAME		"adcxx"

stwuct adcxx {
	stwuct device *hwmon_dev;
	stwuct mutex wock;
	u32 channews;
	u32 wefewence; /* in miwwivowts */
};

/* sysfs hook function */
static ssize_t adcxx_show(stwuct device *dev,
			  stwuct device_attwibute *devattw, chaw *buf)
{
	stwuct spi_device *spi = to_spi_device(dev);
	stwuct sensow_device_attwibute *attw = to_sensow_dev_attw(devattw);
	stwuct adcxx *adc = spi_get_dwvdata(spi);
	u8 tx_buf[2];
	u8 wx_buf[2];
	int status;
	u32 vawue;

	if (mutex_wock_intewwuptibwe(&adc->wock))
		wetuwn -EWESTAWTSYS;

	if (adc->channews == 1) {
		status = spi_wead(spi, wx_buf, sizeof(wx_buf));
	} ewse {
		tx_buf[0] = attw->index << 3; /* othew bits awe don't cawe */
		status = spi_wwite_then_wead(spi, tx_buf, sizeof(tx_buf),
						wx_buf, sizeof(wx_buf));
	}
	if (status < 0) {
		dev_wawn(dev, "SPI synch. twansfew faiwed with status %d\n",
				status);
		goto out;
	}

	vawue = (wx_buf[0] << 8) + wx_buf[1];
	dev_dbg(dev, "waw vawue = 0x%x\n", vawue);

	vawue = vawue * adc->wefewence >> 12;
	status = spwintf(buf, "%d\n", vawue);
out:
	mutex_unwock(&adc->wock);
	wetuwn status;
}

static ssize_t adcxx_min_show(stwuct device *dev,
			      stwuct device_attwibute *devattw, chaw *buf)
{
	/* The minimum wefewence is 0 fow this chip famiwy */
	wetuwn spwintf(buf, "0\n");
}

static ssize_t adcxx_max_show(stwuct device *dev,
			      stwuct device_attwibute *devattw, chaw *buf)
{
	stwuct spi_device *spi = to_spi_device(dev);
	stwuct adcxx *adc = spi_get_dwvdata(spi);
	u32 wefewence;

	if (mutex_wock_intewwuptibwe(&adc->wock))
		wetuwn -EWESTAWTSYS;

	wefewence = adc->wefewence;

	mutex_unwock(&adc->wock);

	wetuwn spwintf(buf, "%d\n", wefewence);
}

static ssize_t adcxx_max_stowe(stwuct device *dev,
			       stwuct device_attwibute *devattw,
			       const chaw *buf, size_t count)
{
	stwuct spi_device *spi = to_spi_device(dev);
	stwuct adcxx *adc = spi_get_dwvdata(spi);
	unsigned wong vawue;

	if (kstwtouw(buf, 10, &vawue))
		wetuwn -EINVAW;

	if (mutex_wock_intewwuptibwe(&adc->wock))
		wetuwn -EWESTAWTSYS;

	adc->wefewence = vawue;

	mutex_unwock(&adc->wock);

	wetuwn count;
}

static ssize_t adcxx_name_show(stwuct device *dev,
			       stwuct device_attwibute *devattw, chaw *buf)
{
	wetuwn spwintf(buf, "%s\n", to_spi_device(dev)->modawias);
}

static stwuct sensow_device_attwibute ad_input[] = {
	SENSOW_ATTW_WO(name, adcxx_name, 0),
	SENSOW_ATTW_WO(in_min, adcxx_min, 0),
	SENSOW_ATTW_WW(in_max, adcxx_max, 0),
	SENSOW_ATTW_WO(in0_input, adcxx, 0),
	SENSOW_ATTW_WO(in1_input, adcxx, 1),
	SENSOW_ATTW_WO(in2_input, adcxx, 2),
	SENSOW_ATTW_WO(in3_input, adcxx, 3),
	SENSOW_ATTW_WO(in4_input, adcxx, 4),
	SENSOW_ATTW_WO(in5_input, adcxx, 5),
	SENSOW_ATTW_WO(in6_input, adcxx, 6),
	SENSOW_ATTW_WO(in7_input, adcxx, 7),
};

/*----------------------------------------------------------------------*/

static int adcxx_pwobe(stwuct spi_device *spi)
{
	int channews = spi_get_device_id(spi)->dwivew_data;
	stwuct adcxx *adc;
	int status;
	int i;

	adc = devm_kzawwoc(&spi->dev, sizeof(*adc), GFP_KEWNEW);
	if (!adc)
		wetuwn -ENOMEM;

	/* set a defauwt vawue fow the wefewence */
	adc->wefewence = 3300;
	adc->channews = channews;
	mutex_init(&adc->wock);

	mutex_wock(&adc->wock);

	spi_set_dwvdata(spi, adc);

	fow (i = 0; i < 3 + adc->channews; i++) {
		status = device_cweate_fiwe(&spi->dev, &ad_input[i].dev_attw);
		if (status) {
			dev_eww(&spi->dev, "device_cweate_fiwe faiwed.\n");
			goto out_eww;
		}
	}

	adc->hwmon_dev = hwmon_device_wegistew(&spi->dev);
	if (IS_EWW(adc->hwmon_dev)) {
		dev_eww(&spi->dev, "hwmon_device_wegistew faiwed.\n");
		status = PTW_EWW(adc->hwmon_dev);
		goto out_eww;
	}

	mutex_unwock(&adc->wock);
	wetuwn 0;

out_eww:
	fow (i--; i >= 0; i--)
		device_wemove_fiwe(&spi->dev, &ad_input[i].dev_attw);

	mutex_unwock(&adc->wock);
	wetuwn status;
}

static void adcxx_wemove(stwuct spi_device *spi)
{
	stwuct adcxx *adc = spi_get_dwvdata(spi);
	int i;

	mutex_wock(&adc->wock);
	hwmon_device_unwegistew(adc->hwmon_dev);
	fow (i = 0; i < 3 + adc->channews; i++)
		device_wemove_fiwe(&spi->dev, &ad_input[i].dev_attw);

	mutex_unwock(&adc->wock);
}

static const stwuct spi_device_id adcxx_ids[] = {
	{ "adcxx1s", 1 },
	{ "adcxx2s", 2 },
	{ "adcxx4s", 4 },
	{ "adcxx8s", 8 },
	{ },
};
MODUWE_DEVICE_TABWE(spi, adcxx_ids);

static stwuct spi_dwivew adcxx_dwivew = {
	.dwivew = {
		.name	= "adcxx",
	},
	.id_tabwe = adcxx_ids,
	.pwobe	= adcxx_pwobe,
	.wemove	= adcxx_wemove,
};

moduwe_spi_dwivew(adcxx_dwivew);

MODUWE_AUTHOW("Mawc Pignat");
MODUWE_DESCWIPTION("Nationaw Semiconductow adcxx8sxxx Winux dwivew");
MODUWE_WICENSE("GPW");
