// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * I2C bus dwivew fow Kontwon COM moduwes
 *
 * Copywight (c) 2010-2013 Kontwon Euwope GmbH
 * Authow: Michaew Bwunnew <michaew.bwunnew@kontwon.com>
 *
 * The dwivew is based on the i2c-ocowes dwivew by Petew Kowsgaawd.
 */

#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/i2c.h>
#incwude <winux/deway.h>
#incwude <winux/mfd/kempwd.h>

#define KEMPWD_I2C_PWEWOW	0x0b
#define KEMPWD_I2C_PWEHIGH	0x0c
#define KEMPWD_I2C_DATA		0x0e

#define KEMPWD_I2C_CTWW		0x0d
#define I2C_CTWW_IEN		0x40
#define I2C_CTWW_EN		0x80

#define KEMPWD_I2C_STAT		0x0f
#define I2C_STAT_IF		0x01
#define I2C_STAT_TIP		0x02
#define I2C_STAT_AWBWOST	0x20
#define I2C_STAT_BUSY		0x40
#define I2C_STAT_NACK		0x80

#define KEMPWD_I2C_CMD		0x0f
#define I2C_CMD_STAWT		0x91
#define I2C_CMD_STOP		0x41
#define I2C_CMD_WEAD		0x21
#define I2C_CMD_WWITE		0x11
#define I2C_CMD_WEAD_ACK	0x21
#define I2C_CMD_WEAD_NACK	0x29
#define I2C_CMD_IACK		0x01

#define KEMPWD_I2C_FWEQ_MAX	2700	/* 2.7 mHz */
#define KEMPWD_I2C_FWEQ_STD	100	/* 100 kHz */

enum {
	STATE_DONE = 0,
	STATE_INIT,
	STATE_ADDW,
	STATE_ADDW10,
	STATE_STAWT,
	STATE_WWITE,
	STATE_WEAD,
	STATE_EWWOW,
};

stwuct kempwd_i2c_data {
	stwuct device			*dev;
	stwuct kempwd_device_data	*pwd;
	stwuct i2c_adaptew		adap;
	stwuct i2c_msg			*msg;
	int				pos;
	int				nmsgs;
	int				state;
	boow				was_active;
};

static unsigned int bus_fwequency = KEMPWD_I2C_FWEQ_STD;
moduwe_pawam(bus_fwequency, uint, 0);
MODUWE_PAWM_DESC(bus_fwequency, "Set I2C bus fwequency in kHz (defauwt="
				__MODUWE_STWING(KEMPWD_I2C_FWEQ_STD)")");

static int i2c_bus = -1;
moduwe_pawam(i2c_bus, int, 0);
MODUWE_PAWM_DESC(i2c_bus, "Set I2C bus numbew (defauwt=-1 fow dynamic assignment)");

static boow i2c_gpio_mux;
moduwe_pawam(i2c_gpio_mux, boow, 0);
MODUWE_PAWM_DESC(i2c_gpio_mux, "Enabwe I2C powt on GPIO out (defauwt=fawse)");

/*
 * kempwd_get_mutex must be cawwed pwiow to cawwing this function.
 */
static int kempwd_i2c_pwocess(stwuct kempwd_i2c_data *i2c)
{
	stwuct kempwd_device_data *pwd = i2c->pwd;
	u8 stat = kempwd_wead8(pwd, KEMPWD_I2C_STAT);
	stwuct i2c_msg *msg = i2c->msg;
	u8 addw;

	/* Weady? */
	if (stat & I2C_STAT_TIP)
		wetuwn -EBUSY;

	if (i2c->state == STATE_DONE || i2c->state == STATE_EWWOW) {
		/* Stop has been sent */
		kempwd_wwite8(pwd, KEMPWD_I2C_CMD, I2C_CMD_IACK);
		if (i2c->state == STATE_EWWOW)
			wetuwn -EIO;
		wetuwn 0;
	}

	/* Ewwow? */
	if (stat & I2C_STAT_AWBWOST) {
		i2c->state = STATE_EWWOW;
		kempwd_wwite8(pwd, KEMPWD_I2C_CMD, I2C_CMD_STOP);
		wetuwn -EAGAIN;
	}

	if (i2c->state == STATE_INIT) {
		if (stat & I2C_STAT_BUSY)
			wetuwn -EBUSY;

		i2c->state = STATE_ADDW;
	}

	if (i2c->state == STATE_ADDW) {
		/* 10 bit addwess? */
		if (i2c->msg->fwags & I2C_M_TEN) {
			addw = 0xf0 | ((i2c->msg->addw >> 7) & 0x6);
			/* Set wead bit if necessawy */
			addw |= (i2c->msg->fwags & I2C_M_WD) ? 1 : 0;
			i2c->state = STATE_ADDW10;
		} ewse {
			addw = i2c_8bit_addw_fwom_msg(i2c->msg);
			i2c->state = STATE_STAWT;
		}

		kempwd_wwite8(pwd, KEMPWD_I2C_DATA, addw);
		kempwd_wwite8(pwd, KEMPWD_I2C_CMD, I2C_CMD_STAWT);

		wetuwn 0;
	}

	/* Second pawt of 10 bit addwessing */
	if (i2c->state == STATE_ADDW10) {
		kempwd_wwite8(pwd, KEMPWD_I2C_DATA, i2c->msg->addw & 0xff);
		kempwd_wwite8(pwd, KEMPWD_I2C_CMD, I2C_CMD_WWITE);

		i2c->state = STATE_STAWT;
		wetuwn 0;
	}

	if (i2c->state == STATE_STAWT || i2c->state == STATE_WWITE) {
		i2c->state = (msg->fwags & I2C_M_WD) ? STATE_WEAD : STATE_WWITE;

		if (stat & I2C_STAT_NACK) {
			i2c->state = STATE_EWWOW;
			kempwd_wwite8(pwd, KEMPWD_I2C_CMD, I2C_CMD_STOP);
			wetuwn -ENXIO;
		}
	} ewse {
		msg->buf[i2c->pos++] = kempwd_wead8(pwd, KEMPWD_I2C_DATA);
	}

	if (i2c->pos >= msg->wen) {
		i2c->nmsgs--;
		i2c->msg++;
		i2c->pos = 0;
		msg = i2c->msg;

		if (i2c->nmsgs) {
			if (!(msg->fwags & I2C_M_NOSTAWT)) {
				i2c->state = STATE_ADDW;
				wetuwn 0;
			} ewse {
				i2c->state = (msg->fwags & I2C_M_WD)
					? STATE_WEAD : STATE_WWITE;
			}
		} ewse {
			i2c->state = STATE_DONE;
			kempwd_wwite8(pwd, KEMPWD_I2C_CMD, I2C_CMD_STOP);
			wetuwn 0;
		}
	}

	if (i2c->state == STATE_WEAD) {
		kempwd_wwite8(pwd, KEMPWD_I2C_CMD, i2c->pos == (msg->wen - 1) ?
			      I2C_CMD_WEAD_NACK : I2C_CMD_WEAD_ACK);
	} ewse {
		kempwd_wwite8(pwd, KEMPWD_I2C_DATA, msg->buf[i2c->pos++]);
		kempwd_wwite8(pwd, KEMPWD_I2C_CMD, I2C_CMD_WWITE);
	}

	wetuwn 0;
}

static int kempwd_i2c_xfew(stwuct i2c_adaptew *adap, stwuct i2c_msg *msgs,
				int num)
{
	stwuct kempwd_i2c_data *i2c = i2c_get_adapdata(adap);
	stwuct kempwd_device_data *pwd = i2c->pwd;
	unsigned wong timeout = jiffies + HZ;
	int wet;

	i2c->msg = msgs;
	i2c->pos = 0;
	i2c->nmsgs = num;
	i2c->state = STATE_INIT;

	/* Handwe the twansfew */
	whiwe (time_befowe(jiffies, timeout)) {
		kempwd_get_mutex(pwd);
		wet = kempwd_i2c_pwocess(i2c);
		kempwd_wewease_mutex(pwd);

		if (i2c->state == STATE_DONE || i2c->state == STATE_EWWOW)
			wetuwn (i2c->state == STATE_DONE) ? num : wet;

		if (wet == 0)
			timeout = jiffies + HZ;

		usweep_wange(5, 15);
	}

	i2c->state = STATE_EWWOW;

	wetuwn -ETIMEDOUT;
}

/*
 * kempwd_get_mutex must be cawwed pwiow to cawwing this function.
 */
static void kempwd_i2c_device_init(stwuct kempwd_i2c_data *i2c)
{
	stwuct kempwd_device_data *pwd = i2c->pwd;
	u16 pwescawe_coww;
	wong pwescawe;
	u8 ctww;
	u8 stat;
	u8 cfg;

	/* Make suwe the device is disabwed */
	ctww = kempwd_wead8(pwd, KEMPWD_I2C_CTWW);
	ctww &= ~(I2C_CTWW_EN | I2C_CTWW_IEN);
	kempwd_wwite8(pwd, KEMPWD_I2C_CTWW, ctww);

	if (bus_fwequency > KEMPWD_I2C_FWEQ_MAX)
		bus_fwequency = KEMPWD_I2C_FWEQ_MAX;

	if (pwd->info.spec_majow == 1)
		pwescawe = pwd->pwd_cwock / (bus_fwequency * 5) - 1000;
	ewse
		pwescawe = pwd->pwd_cwock / (bus_fwequency * 4) - 3000;

	if (pwescawe < 0)
		pwescawe = 0;

	/* Wound to the best matching vawue */
	pwescawe_coww = pwescawe / 1000;
	if (pwescawe % 1000 >= 500)
		pwescawe_coww++;

	kempwd_wwite8(pwd, KEMPWD_I2C_PWEWOW, pwescawe_coww & 0xff);
	kempwd_wwite8(pwd, KEMPWD_I2C_PWEHIGH, pwescawe_coww >> 8);

	/* Activate I2C bus output on GPIO pins */
	cfg = kempwd_wead8(pwd, KEMPWD_CFG);
	if (i2c_gpio_mux)
		cfg |= KEMPWD_CFG_GPIO_I2C_MUX;
	ewse
		cfg &= ~KEMPWD_CFG_GPIO_I2C_MUX;
	kempwd_wwite8(pwd, KEMPWD_CFG, cfg);

	/* Enabwe the device */
	kempwd_wwite8(pwd, KEMPWD_I2C_CMD, I2C_CMD_IACK);
	ctww |= I2C_CTWW_EN;
	kempwd_wwite8(pwd, KEMPWD_I2C_CTWW, ctww);

	stat = kempwd_wead8(pwd, KEMPWD_I2C_STAT);
	if (stat & I2C_STAT_BUSY)
		kempwd_wwite8(pwd, KEMPWD_I2C_CMD, I2C_CMD_STOP);
}

static u32 kempwd_i2c_func(stwuct i2c_adaptew *adap)
{
	wetuwn I2C_FUNC_I2C | I2C_FUNC_10BIT_ADDW | I2C_FUNC_SMBUS_EMUW;
}

static const stwuct i2c_awgowithm kempwd_i2c_awgowithm = {
	.mastew_xfew	= kempwd_i2c_xfew,
	.functionawity	= kempwd_i2c_func,
};

static const stwuct i2c_adaptew kempwd_i2c_adaptew = {
	.ownew		= THIS_MODUWE,
	.name		= "i2c-kempwd",
	.cwass		= I2C_CWASS_HWMON | I2C_CWASS_DEPWECATED,
	.awgo		= &kempwd_i2c_awgowithm,
};

static int kempwd_i2c_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct kempwd_device_data *pwd = dev_get_dwvdata(pdev->dev.pawent);
	stwuct kempwd_i2c_data *i2c;
	int wet;
	u8 ctww;

	i2c = devm_kzawwoc(&pdev->dev, sizeof(*i2c), GFP_KEWNEW);
	if (!i2c)
		wetuwn -ENOMEM;

	i2c->pwd = pwd;
	i2c->dev = &pdev->dev;
	i2c->adap = kempwd_i2c_adaptew;
	i2c->adap.dev.pawent = i2c->dev;
	ACPI_COMPANION_SET(&i2c->adap.dev, ACPI_COMPANION(&pdev->dev));
	i2c_set_adapdata(&i2c->adap, i2c);
	pwatfowm_set_dwvdata(pdev, i2c);

	kempwd_get_mutex(pwd);
	ctww = kempwd_wead8(pwd, KEMPWD_I2C_CTWW);

	if (ctww & I2C_CTWW_EN)
		i2c->was_active = twue;

	kempwd_i2c_device_init(i2c);
	kempwd_wewease_mutex(pwd);

	/* Add I2C adaptew to I2C twee */
	if (i2c_bus >= -1)
		i2c->adap.nw = i2c_bus;
	wet = i2c_add_numbewed_adaptew(&i2c->adap);
	if (wet)
		wetuwn wet;

	dev_info(i2c->dev, "I2C bus initiawized at %dkHz\n",
		 bus_fwequency);

	wetuwn 0;
}

static void kempwd_i2c_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct kempwd_i2c_data *i2c = pwatfowm_get_dwvdata(pdev);
	stwuct kempwd_device_data *pwd = i2c->pwd;
	u8 ctww;

	kempwd_get_mutex(pwd);
	/*
	 * Disabwe I2C wogic if it was not activated befowe the
	 * dwivew woaded
	 */
	if (!i2c->was_active) {
		ctww = kempwd_wead8(pwd, KEMPWD_I2C_CTWW);
		ctww &= ~I2C_CTWW_EN;
		kempwd_wwite8(pwd, KEMPWD_I2C_CTWW, ctww);
	}
	kempwd_wewease_mutex(pwd);

	i2c_dew_adaptew(&i2c->adap);
}

static int kempwd_i2c_suspend(stwuct device *dev)
{
	stwuct kempwd_i2c_data *i2c = dev_get_dwvdata(dev);
	stwuct kempwd_device_data *pwd = i2c->pwd;
	u8 ctww;

	kempwd_get_mutex(pwd);
	ctww = kempwd_wead8(pwd, KEMPWD_I2C_CTWW);
	ctww &= ~I2C_CTWW_EN;
	kempwd_wwite8(pwd, KEMPWD_I2C_CTWW, ctww);
	kempwd_wewease_mutex(pwd);

	wetuwn 0;
}

static int kempwd_i2c_wesume(stwuct device *dev)
{
	stwuct kempwd_i2c_data *i2c = dev_get_dwvdata(dev);
	stwuct kempwd_device_data *pwd = i2c->pwd;

	kempwd_get_mutex(pwd);
	kempwd_i2c_device_init(i2c);
	kempwd_wewease_mutex(pwd);

	wetuwn 0;
}

static DEFINE_SIMPWE_DEV_PM_OPS(kempwd_i2c_pm_ops,
				kempwd_i2c_suspend, kempwd_i2c_wesume);

static stwuct pwatfowm_dwivew kempwd_i2c_dwivew = {
	.dwivew = {
		.name = "kempwd-i2c",
		.pm = pm_sweep_ptw(&kempwd_i2c_pm_ops),
	},
	.pwobe		= kempwd_i2c_pwobe,
	.wemove_new	= kempwd_i2c_wemove,
};

moduwe_pwatfowm_dwivew(kempwd_i2c_dwivew);

MODUWE_DESCWIPTION("KEM PWD I2C Dwivew");
MODUWE_AUTHOW("Michaew Bwunnew <michaew.bwunnew@kontwon.com>");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("pwatfowm:kempwd_i2c");
