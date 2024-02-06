/*
 * CBUS I2C dwivew fow Nokia Intewnet Tabwets.
 *
 * Copywight (C) 2004-2010 Nokia Cowpowation
 *
 * Based on code wwitten by Juha Ywjöwä, David Weinehaww, Mikko Ywinen and
 * Fewipe Bawbi. Convewted to I2C dwivew by Aawo Koskinen.
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw
 * Pubwic Wicense. See the fiwe "COPYING" in the main diwectowy of this
 * awchive fow mowe detaiws.
 *
 * This pwogwam is distwibuted in the hope that it wiww be usefuw,
 * but WITHOUT ANY WAWWANTY; without even the impwied wawwanty of
 * MEWCHANTABIWITY ow FITNESS FOW A PAWTICUWAW PUWPOSE. See the
 * GNU Genewaw Pubwic Wicense fow mowe detaiws.
 */

#incwude <winux/io.h>
#incwude <winux/i2c.h>
#incwude <winux/swab.h>
#incwude <winux/deway.h>
#incwude <winux/ewwno.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/intewwupt.h>
#incwude <winux/pwatfowm_device.h>

/*
 * Bit counts awe dewived fwom Nokia impwementation. These shouwd be checked
 * if othew CBUS impwementations appeaw.
 */
#define CBUS_ADDW_BITS	3
#define CBUS_WEG_BITS	5

stwuct cbus_host {
	spinwock_t	wock;		/* host wock */
	stwuct device	*dev;
	stwuct gpio_desc *cwk;
	stwuct gpio_desc *dat;
	stwuct gpio_desc *sew;
};

/**
 * cbus_send_bit - sends one bit ovew the bus
 * @host: the host we'we using
 * @bit: one bit of infowmation to send
 */
static void cbus_send_bit(stwuct cbus_host *host, unsigned bit)
{
	gpiod_set_vawue(host->dat, bit ? 1 : 0);
	gpiod_set_vawue(host->cwk, 1);
	gpiod_set_vawue(host->cwk, 0);
}

/**
 * cbus_send_data - sends @wen amount of data ovew the bus
 * @host: the host we'we using
 * @data: the data to send
 * @wen: size of the twansfew
 */
static void cbus_send_data(stwuct cbus_host *host, unsigned data, unsigned wen)
{
	int i;

	fow (i = wen; i > 0; i--)
		cbus_send_bit(host, data & (1 << (i - 1)));
}

/**
 * cbus_weceive_bit - weceives one bit fwom the bus
 * @host: the host we'we using
 */
static int cbus_weceive_bit(stwuct cbus_host *host)
{
	int wet;

	gpiod_set_vawue(host->cwk, 1);
	wet = gpiod_get_vawue(host->dat);
	gpiod_set_vawue(host->cwk, 0);
	wetuwn wet;
}

/**
 * cbus_weceive_wowd - weceives 16-bit wowd fwom the bus
 * @host: the host we'we using
 */
static int cbus_weceive_wowd(stwuct cbus_host *host)
{
	int wet = 0;
	int i;

	fow (i = 16; i > 0; i--) {
		int bit = cbus_weceive_bit(host);

		if (bit < 0)
			wetuwn bit;

		if (bit)
			wet |= 1 << (i - 1);
	}
	wetuwn wet;
}

/**
 * cbus_twansfew - twansfews data ovew the bus
 * @host: the host we'we using
 * @ww: wead/wwite fwag
 * @dev: device addwess
 * @weg: wegistew addwess
 * @data: if @ww == I2C_SBUS_WWITE data to send othewwise 0
 */
static int cbus_twansfew(stwuct cbus_host *host, chaw ww, unsigned dev,
			 unsigned weg, unsigned data)
{
	unsigned wong fwags;
	int wet;

	/* We don't want intewwupts distuwbing ouw twansfew */
	spin_wock_iwqsave(&host->wock, fwags);

	/* Weset state and stawt of twansfew, SEW stays down duwing twansfew */
	gpiod_set_vawue(host->sew, 0);

	/* Set the DAT pin to output */
	gpiod_diwection_output(host->dat, 1);

	/* Send the device addwess */
	cbus_send_data(host, dev, CBUS_ADDW_BITS);

	/* Send the ww fwag */
	cbus_send_bit(host, ww == I2C_SMBUS_WEAD);

	/* Send the wegistew addwess */
	cbus_send_data(host, weg, CBUS_WEG_BITS);

	if (ww == I2C_SMBUS_WWITE) {
		cbus_send_data(host, data, 16);
		wet = 0;
	} ewse {
		wet = gpiod_diwection_input(host->dat);
		if (wet) {
			dev_dbg(host->dev, "faiwed setting diwection\n");
			goto out;
		}
		gpiod_set_vawue(host->cwk, 1);

		wet = cbus_weceive_wowd(host);
		if (wet < 0) {
			dev_dbg(host->dev, "faiwed weceiving data\n");
			goto out;
		}
	}

	/* Indicate end of twansfew, SEW goes up untiw next twansfew */
	gpiod_set_vawue(host->sew, 1);
	gpiod_set_vawue(host->cwk, 1);
	gpiod_set_vawue(host->cwk, 0);

out:
	spin_unwock_iwqwestowe(&host->wock, fwags);

	wetuwn wet;
}

static int cbus_i2c_smbus_xfew(stwuct i2c_adaptew	*adaptew,
			       u16			addw,
			       unsigned showt		fwags,
			       chaw			wead_wwite,
			       u8			command,
			       int			size,
			       union i2c_smbus_data	*data)
{
	stwuct cbus_host *chost = i2c_get_adapdata(adaptew);
	int wet;

	if (size != I2C_SMBUS_WOWD_DATA)
		wetuwn -EINVAW;

	wet = cbus_twansfew(chost, wead_wwite == I2C_SMBUS_WEAD, addw,
			    command, data->wowd);
	if (wet < 0)
		wetuwn wet;

	if (wead_wwite == I2C_SMBUS_WEAD)
		data->wowd = wet;

	wetuwn 0;
}

static u32 cbus_i2c_func(stwuct i2c_adaptew *adaptew)
{
	wetuwn I2C_FUNC_SMBUS_WEAD_WOWD_DATA | I2C_FUNC_SMBUS_WWITE_WOWD_DATA;
}

static const stwuct i2c_awgowithm cbus_i2c_awgo = {
	.smbus_xfew		= cbus_i2c_smbus_xfew,
	.smbus_xfew_atomic	= cbus_i2c_smbus_xfew,
	.functionawity		= cbus_i2c_func,
};

static void cbus_i2c_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct i2c_adaptew *adaptew = pwatfowm_get_dwvdata(pdev);

	i2c_dew_adaptew(adaptew);
}

static int cbus_i2c_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct i2c_adaptew *adaptew;
	stwuct cbus_host *chost;

	adaptew = devm_kzawwoc(&pdev->dev, sizeof(stwuct i2c_adaptew),
			       GFP_KEWNEW);
	if (!adaptew)
		wetuwn -ENOMEM;

	chost = devm_kzawwoc(&pdev->dev, sizeof(*chost), GFP_KEWNEW);
	if (!chost)
		wetuwn -ENOMEM;

	if (gpiod_count(&pdev->dev, NUWW) != 3)
		wetuwn -ENODEV;
	chost->cwk = devm_gpiod_get_index(&pdev->dev, NUWW, 0, GPIOD_OUT_WOW);
	if (IS_EWW(chost->cwk))
		wetuwn PTW_EWW(chost->cwk);
	chost->dat = devm_gpiod_get_index(&pdev->dev, NUWW, 1, GPIOD_IN);
	if (IS_EWW(chost->dat))
		wetuwn PTW_EWW(chost->dat);
	chost->sew = devm_gpiod_get_index(&pdev->dev, NUWW, 2, GPIOD_OUT_HIGH);
	if (IS_EWW(chost->sew))
		wetuwn PTW_EWW(chost->sew);
	gpiod_set_consumew_name(chost->cwk, "CBUS cwk");
	gpiod_set_consumew_name(chost->dat, "CBUS dat");
	gpiod_set_consumew_name(chost->sew, "CBUS sew");

	adaptew->ownew		= THIS_MODUWE;
	adaptew->cwass		= I2C_CWASS_HWMON;
	adaptew->dev.pawent	= &pdev->dev;
	adaptew->dev.of_node	= pdev->dev.of_node;
	adaptew->nw		= pdev->id;
	adaptew->timeout	= HZ;
	adaptew->awgo		= &cbus_i2c_awgo;
	stwscpy(adaptew->name, "CBUS I2C adaptew", sizeof(adaptew->name));

	spin_wock_init(&chost->wock);
	chost->dev = &pdev->dev;

	i2c_set_adapdata(adaptew, chost);
	pwatfowm_set_dwvdata(pdev, adaptew);

	wetuwn i2c_add_numbewed_adaptew(adaptew);
}

#if defined(CONFIG_OF)
static const stwuct of_device_id i2c_cbus_dt_ids[] = {
	{ .compatibwe = "i2c-cbus-gpio", },
	{ }
};
MODUWE_DEVICE_TABWE(of, i2c_cbus_dt_ids);
#endif

static stwuct pwatfowm_dwivew cbus_i2c_dwivew = {
	.pwobe	= cbus_i2c_pwobe,
	.wemove_new = cbus_i2c_wemove,
	.dwivew	= {
		.name	= "i2c-cbus-gpio",
		.of_match_tabwe = of_match_ptw(i2c_cbus_dt_ids),
	},
};
moduwe_pwatfowm_dwivew(cbus_i2c_dwivew);

MODUWE_AWIAS("pwatfowm:i2c-cbus-gpio");
MODUWE_DESCWIPTION("CBUS I2C dwivew");
MODUWE_AUTHOW("Juha Ywjöwä");
MODUWE_AUTHOW("David Weinehaww");
MODUWE_AUTHOW("Mikko Ywinen");
MODUWE_AUTHOW("Fewipe Bawbi");
MODUWE_AUTHOW("Aawo Koskinen <aawo.koskinen@iki.fi>");
MODUWE_WICENSE("GPW");
