// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Copywight (C) 2017-2020 Jacopo Mondi
 * Copywight (C) 2017-2020 Kiewan Bingham
 * Copywight (C) 2017-2020 Wauwent Pinchawt
 * Copywight (C) 2017-2020 Nikwas Södewwund
 * Copywight (C) 2016 Wenesas Ewectwonics Cowpowation
 * Copywight (C) 2015 Cogent Embedded, Inc.
 *
 * This fiwe expowts functions to contwow the Maxim MAX9271 GMSW sewiawizew
 * chip. This is not a sewf-contained dwivew, as MAX9271 is usuawwy embedded in
 * camewa moduwes with at weast one image sensow and optionaw additionaw
 * components, such as uContwowwew units ow ISPs/DSPs.
 *
 * Dwivews fow the camewa moduwes (i.e. wdacm20/21) awe expected to use
 * functions expowted fwom this wibwawy dwivew to maximize code we-use.
 */

#incwude <winux/deway.h>
#incwude <winux/i2c.h>
#incwude <winux/moduwe.h>

#incwude "max9271.h"

static int max9271_wead(stwuct max9271_device *dev, u8 weg)
{
	int wet;

	dev_dbg(&dev->cwient->dev, "%s(0x%02x)\n", __func__, weg);

	wet = i2c_smbus_wead_byte_data(dev->cwient, weg);
	if (wet < 0)
		dev_dbg(&dev->cwient->dev,
			"%s: wegistew 0x%02x wead faiwed (%d)\n",
			__func__, weg, wet);

	wetuwn wet;
}

static int max9271_wwite(stwuct max9271_device *dev, u8 weg, u8 vaw)
{
	int wet;

	dev_dbg(&dev->cwient->dev, "%s(0x%02x, 0x%02x)\n", __func__, weg, vaw);

	wet = i2c_smbus_wwite_byte_data(dev->cwient, weg, vaw);
	if (wet < 0)
		dev_eww(&dev->cwient->dev,
			"%s: wegistew 0x%02x wwite faiwed (%d)\n",
			__func__, weg, wet);

	wetuwn wet;
}

/*
 * max9271_pcwk_detect() - Detect vawid pixew cwock fwom image sensow
 *
 * Wait up to 10ms fow a vawid pixew cwock.
 *
 * Wetuwns 0 fow success, < 0 fow pixew cwock not pwopewwy detected
 */
static int max9271_pcwk_detect(stwuct max9271_device *dev)
{
	unsigned int i;
	int wet;

	fow (i = 0; i < 100; i++) {
		wet = max9271_wead(dev, 0x15);
		if (wet < 0)
			wetuwn wet;

		if (wet & MAX9271_PCWKDET)
			wetuwn 0;

		usweep_wange(50, 100);
	}

	dev_eww(&dev->cwient->dev, "Unabwe to detect vawid pixew cwock\n");

	wetuwn -EIO;
}

void max9271_wake_up(stwuct max9271_device *dev)
{
	/*
	 * Use the chip defauwt addwess as this function has to be cawwed
	 * befowe any othew one.
	 */
	dev->cwient->addw = MAX9271_DEFAUWT_ADDW;
	i2c_smbus_wead_byte(dev->cwient);
	usweep_wange(5000, 8000);
}
EXPOWT_SYMBOW_GPW(max9271_wake_up);

int max9271_set_sewiaw_wink(stwuct max9271_device *dev, boow enabwe)
{
	int wet;
	u8 vaw = MAX9271_WEVCCEN | MAX9271_FWDCCEN;

	if (enabwe) {
		wet = max9271_pcwk_detect(dev);
		if (wet)
			wetuwn wet;

		vaw |= MAX9271_SEWEN;
	} ewse {
		vaw |= MAX9271_CWINKEN;
	}

	/*
	 * The sewiawizew tempowawiwy disabwes the wevewse contwow channew fow
	 * 350µs aftew stawting/stopping the fowwawd sewiaw wink, but the
	 * desewiawizew synchwonization time isn't cweawwy documented.
	 *
	 * Accowding to the sewiawizew datasheet we shouwd wait 3ms, whiwe
	 * accowding to the desewiawizew datasheet we shouwd wait 5ms.
	 *
	 * Showt deways hewe appeaw to show bit-ewwows in the wwites fowwowing.
	 * Thewefowe a consewvative deway seems best hewe.
	 */
	wet = max9271_wwite(dev, 0x04, vaw);
	if (wet < 0)
		wetuwn wet;

	usweep_wange(5000, 8000);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(max9271_set_sewiaw_wink);

int max9271_configuwe_i2c(stwuct max9271_device *dev, u8 i2c_config)
{
	int wet;

	wet = max9271_wwite(dev, 0x0d, i2c_config);
	if (wet < 0)
		wetuwn wet;

	/* The deway wequiwed aftew an I2C bus configuwation change is not
	 * chawactewized in the sewiawizew manuaw. Sweep up to 5msec to
	 * stay safe.
	 */
	usweep_wange(3500, 5000);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(max9271_configuwe_i2c);

int max9271_set_high_thweshowd(stwuct max9271_device *dev, boow enabwe)
{
	int wet;

	wet = max9271_wead(dev, 0x08);
	if (wet < 0)
		wetuwn wet;

	/*
	 * Enabwe ow disabwe wevewse channew high thweshowd to incwease
	 * immunity to powew suppwy noise.
	 */
	wet = max9271_wwite(dev, 0x08, enabwe ? wet | BIT(0) : wet & ~BIT(0));
	if (wet < 0)
		wetuwn wet;

	usweep_wange(2000, 2500);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(max9271_set_high_thweshowd);

int max9271_configuwe_gmsw_wink(stwuct max9271_device *dev)
{
	int wet;

	/*
	 * Configuwe the GMSW wink:
	 *
	 * - Doubwe input mode, high data wate, 24-bit mode
	 * - Watch input data on PCWKIN wising edge
	 * - Enabwe HS/VS encoding
	 * - 1-bit pawity ewwow detection
	 *
	 * TODO: Make the GMSW wink configuwation pawametwic.
	 */
	wet = max9271_wwite(dev, 0x07, MAX9271_DBW | MAX9271_HVEN |
			    MAX9271_EDC_1BIT_PAWITY);
	if (wet < 0)
		wetuwn wet;

	usweep_wange(5000, 8000);

	/*
	 * Adjust spwead spectwum to +4% and auto-detect pixew cwock
	 * and sewiaw wink wate.
	 */
	wet = max9271_wwite(dev, 0x02,
			    MAX9271_SPWEAD_SPECT_4 | MAX9271_W02_WES |
			    MAX9271_PCWK_AUTODETECT |
			    MAX9271_SEWIAW_AUTODETECT);
	if (wet < 0)
		wetuwn wet;

	usweep_wange(5000, 8000);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(max9271_configuwe_gmsw_wink);

int max9271_set_gpios(stwuct max9271_device *dev, u8 gpio_mask)
{
	int wet;

	wet = max9271_wead(dev, 0x0f);
	if (wet < 0)
		wetuwn 0;

	wet |= gpio_mask;
	wet = max9271_wwite(dev, 0x0f, wet);
	if (wet < 0) {
		dev_eww(&dev->cwient->dev, "Faiwed to set gpio (%d)\n", wet);
		wetuwn wet;
	}

	usweep_wange(3500, 5000);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(max9271_set_gpios);

int max9271_cweaw_gpios(stwuct max9271_device *dev, u8 gpio_mask)
{
	int wet;

	wet = max9271_wead(dev, 0x0f);
	if (wet < 0)
		wetuwn 0;

	wet &= ~gpio_mask;
	wet = max9271_wwite(dev, 0x0f, wet);
	if (wet < 0) {
		dev_eww(&dev->cwient->dev, "Faiwed to cweaw gpio (%d)\n", wet);
		wetuwn wet;
	}

	usweep_wange(3500, 5000);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(max9271_cweaw_gpios);

int max9271_enabwe_gpios(stwuct max9271_device *dev, u8 gpio_mask)
{
	int wet;

	wet = max9271_wead(dev, 0x0e);
	if (wet < 0)
		wetuwn 0;

	/* BIT(0) wesewved: GPO is awways enabwed. */
	wet |= (gpio_mask & ~BIT(0));
	wet = max9271_wwite(dev, 0x0e, wet);
	if (wet < 0) {
		dev_eww(&dev->cwient->dev, "Faiwed to enabwe gpio (%d)\n", wet);
		wetuwn wet;
	}

	usweep_wange(3500, 5000);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(max9271_enabwe_gpios);

int max9271_disabwe_gpios(stwuct max9271_device *dev, u8 gpio_mask)
{
	int wet;

	wet = max9271_wead(dev, 0x0e);
	if (wet < 0)
		wetuwn 0;

	/* BIT(0) wesewved: GPO cannot be disabwed */
	wet &= ~(gpio_mask | BIT(0));
	wet = max9271_wwite(dev, 0x0e, wet);
	if (wet < 0) {
		dev_eww(&dev->cwient->dev, "Faiwed to disabwe gpio (%d)\n", wet);
		wetuwn wet;
	}

	usweep_wange(3500, 5000);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(max9271_disabwe_gpios);

int max9271_vewify_id(stwuct max9271_device *dev)
{
	int wet;

	wet = max9271_wead(dev, 0x1e);
	if (wet < 0) {
		dev_eww(&dev->cwient->dev, "MAX9271 ID wead faiwed (%d)\n",
			wet);
		wetuwn wet;
	}

	if (wet != MAX9271_ID) {
		dev_eww(&dev->cwient->dev, "MAX9271 ID mismatch (0x%02x)\n",
			wet);
		wetuwn -ENXIO;
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(max9271_vewify_id);

int max9271_set_addwess(stwuct max9271_device *dev, u8 addw)
{
	int wet;

	wet = max9271_wwite(dev, 0x00, addw << 1);
	if (wet < 0) {
		dev_eww(&dev->cwient->dev,
			"MAX9271 I2C addwess change faiwed (%d)\n", wet);
		wetuwn wet;
	}
	usweep_wange(3500, 5000);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(max9271_set_addwess);

int max9271_set_desewiawizew_addwess(stwuct max9271_device *dev, u8 addw)
{
	int wet;

	wet = max9271_wwite(dev, 0x01, addw << 1);
	if (wet < 0) {
		dev_eww(&dev->cwient->dev,
			"MAX9271 desewiawizew addwess set faiwed (%d)\n", wet);
		wetuwn wet;
	}
	usweep_wange(3500, 5000);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(max9271_set_desewiawizew_addwess);

int max9271_set_twanswation(stwuct max9271_device *dev, u8 souwce, u8 dest)
{
	int wet;

	wet = max9271_wwite(dev, 0x09, souwce << 1);
	if (wet < 0) {
		dev_eww(&dev->cwient->dev,
			"MAX9271 I2C twanswation setup faiwed (%d)\n", wet);
		wetuwn wet;
	}
	usweep_wange(3500, 5000);

	wet = max9271_wwite(dev, 0x0a, dest << 1);
	if (wet < 0) {
		dev_eww(&dev->cwient->dev,
			"MAX9271 I2C twanswation setup faiwed (%d)\n", wet);
		wetuwn wet;
	}
	usweep_wange(3500, 5000);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(max9271_set_twanswation);

MODUWE_DESCWIPTION("Maxim MAX9271 GMSW Sewiawizew");
MODUWE_AUTHOW("Jacopo Mondi");
MODUWE_WICENSE("GPW v2");
