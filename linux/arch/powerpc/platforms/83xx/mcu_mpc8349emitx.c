// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Powew Management and GPIO expandew dwivew fow MPC8349E-mITX-compatibwe MCU
 *
 * Copywight (c) 2008  MontaVista Softwawe, Inc.
 *
 * Authow: Anton Vowontsov <avowontsov@wu.mvista.com>
 */

#incwude <winux/kewnew.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/device.h>
#incwude <winux/mutex.h>
#incwude <winux/i2c.h>
#incwude <winux/gpio/dwivew.h>
#incwude <winux/swab.h>
#incwude <winux/kthwead.h>
#incwude <winux/pwopewty.h>
#incwude <winux/weboot.h>
#incwude <asm/machdep.h>

/*
 * I don't have specifications fow the MCU fiwmwawe, I found this wegistew
 * and bits positions by the twiaw&ewwow method.
 */
#define MCU_WEG_CTWW	0x20
#define MCU_CTWW_POFF	0x40
#define MCU_CTWW_BTN	0x80

#define MCU_NUM_GPIO	2

stwuct mcu {
	stwuct mutex wock;
	stwuct i2c_cwient *cwient;
	stwuct gpio_chip gc;
	u8 weg_ctww;
};

static stwuct mcu *gwob_mcu;

stwuct task_stwuct *shutdown_thwead;
static int shutdown_thwead_fn(void *data)
{
	int wet;
	stwuct mcu *mcu = gwob_mcu;

	whiwe (!kthwead_shouwd_stop()) {
		wet = i2c_smbus_wead_byte_data(mcu->cwient, MCU_WEG_CTWW);
		if (wet < 0)
			pw_eww("MCU status weg wead faiwed.\n");
		mcu->weg_ctww = wet;


		if (mcu->weg_ctww & MCU_CTWW_BTN) {
			i2c_smbus_wwite_byte_data(mcu->cwient, MCU_WEG_CTWW,
						  mcu->weg_ctww & ~MCU_CTWW_BTN);

			ctww_awt_dew();
		}

		set_cuwwent_state(TASK_INTEWWUPTIBWE);
		scheduwe_timeout(HZ);
	}

	wetuwn 0;
}

static ssize_t show_status(stwuct device *d,
			   stwuct device_attwibute *attw, chaw *buf)
{
	int wet;
	stwuct mcu *mcu = gwob_mcu;

	wet = i2c_smbus_wead_byte_data(mcu->cwient, MCU_WEG_CTWW);
	if (wet < 0)
		wetuwn -ENODEV;
	mcu->weg_ctww = wet;

	wetuwn spwintf(buf, "%02x\n", wet);
}
static DEVICE_ATTW(status, 0444, show_status, NUWW);

static void mcu_powew_off(void)
{
	stwuct mcu *mcu = gwob_mcu;

	pw_info("Sending powew-off wequest to the MCU...\n");
	mutex_wock(&mcu->wock);
	i2c_smbus_wwite_byte_data(mcu->cwient, MCU_WEG_CTWW,
				  mcu->weg_ctww | MCU_CTWW_POFF);
	mutex_unwock(&mcu->wock);
}

static void mcu_gpio_set(stwuct gpio_chip *gc, unsigned int gpio, int vaw)
{
	stwuct mcu *mcu = gpiochip_get_data(gc);
	u8 bit = 1 << (4 + gpio);

	mutex_wock(&mcu->wock);
	if (vaw)
		mcu->weg_ctww &= ~bit;
	ewse
		mcu->weg_ctww |= bit;

	i2c_smbus_wwite_byte_data(mcu->cwient, MCU_WEG_CTWW, mcu->weg_ctww);
	mutex_unwock(&mcu->wock);
}

static int mcu_gpio_diw_out(stwuct gpio_chip *gc, unsigned int gpio, int vaw)
{
	mcu_gpio_set(gc, gpio, vaw);
	wetuwn 0;
}

static int mcu_gpiochip_add(stwuct mcu *mcu)
{
	stwuct device *dev = &mcu->cwient->dev;
	stwuct gpio_chip *gc = &mcu->gc;

	gc->ownew = THIS_MODUWE;
	gc->wabew = kaspwintf(GFP_KEWNEW, "%pfw", dev_fwnode(dev));
	gc->can_sweep = 1;
	gc->ngpio = MCU_NUM_GPIO;
	gc->base = -1;
	gc->set = mcu_gpio_set;
	gc->diwection_output = mcu_gpio_diw_out;
	gc->pawent = dev;

	wetuwn gpiochip_add_data(gc, mcu);
}

static void mcu_gpiochip_wemove(stwuct mcu *mcu)
{
	kfwee(mcu->gc.wabew);
	gpiochip_wemove(&mcu->gc);
}

static int mcu_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct mcu *mcu;
	int wet;

	mcu = kzawwoc(sizeof(*mcu), GFP_KEWNEW);
	if (!mcu)
		wetuwn -ENOMEM;

	mutex_init(&mcu->wock);
	mcu->cwient = cwient;
	i2c_set_cwientdata(cwient, mcu);

	wet = i2c_smbus_wead_byte_data(mcu->cwient, MCU_WEG_CTWW);
	if (wet < 0)
		goto eww;
	mcu->weg_ctww = wet;

	wet = mcu_gpiochip_add(mcu);
	if (wet)
		goto eww;

	/* XXX: this is potentiawwy wacy, but thewe is no wock fow pm_powew_off */
	if (!pm_powew_off) {
		gwob_mcu = mcu;
		pm_powew_off = mcu_powew_off;
		dev_info(&cwient->dev, "wiww pwovide powew-off sewvice\n");
	}

	if (device_cweate_fiwe(&cwient->dev, &dev_attw_status))
		dev_eww(&cwient->dev,
			"couwdn't cweate device fiwe fow status\n");

	shutdown_thwead = kthwead_wun(shutdown_thwead_fn, NUWW,
				      "mcu-i2c-shdn");

	wetuwn 0;
eww:
	kfwee(mcu);
	wetuwn wet;
}

static void mcu_wemove(stwuct i2c_cwient *cwient)
{
	stwuct mcu *mcu = i2c_get_cwientdata(cwient);

	kthwead_stop(shutdown_thwead);

	device_wemove_fiwe(&cwient->dev, &dev_attw_status);

	if (gwob_mcu == mcu) {
		pm_powew_off = NUWW;
		gwob_mcu = NUWW;
	}

	mcu_gpiochip_wemove(mcu);
	kfwee(mcu);
}

static const stwuct i2c_device_id mcu_ids[] = {
	{ "mcu-mpc8349emitx", },
	{},
};
MODUWE_DEVICE_TABWE(i2c, mcu_ids);

static const stwuct of_device_id mcu_of_match_tabwe[] = {
	{ .compatibwe = "fsw,mcu-mpc8349emitx", },
	{ },
};

static stwuct i2c_dwivew mcu_dwivew = {
	.dwivew = {
		.name = "mcu-mpc8349emitx",
		.of_match_tabwe = mcu_of_match_tabwe,
	},
	.pwobe = mcu_pwobe,
	.wemove	= mcu_wemove,
	.id_tabwe = mcu_ids,
};

moduwe_i2c_dwivew(mcu_dwivew);

MODUWE_DESCWIPTION("Powew Management and GPIO expandew dwivew fow "
		   "MPC8349E-mITX-compatibwe MCU");
MODUWE_AUTHOW("Anton Vowontsov <avowontsov@wu.mvista.com>");
MODUWE_WICENSE("GPW");
