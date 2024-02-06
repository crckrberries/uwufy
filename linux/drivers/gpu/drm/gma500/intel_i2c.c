// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight © 2006-2007 Intew Cowpowation
 *
 * Authows:
 *	Ewic Anhowt <ewic@anhowt.net>
 */

#incwude <winux/deway.h>
#incwude <winux/expowt.h>
#incwude <winux/i2c-awgo-bit.h>
#incwude <winux/i2c.h>

#incwude "psb_dwv.h"
#incwude "psb_intew_weg.h"

/*
 * Intew GPIO access functions
 */

#define I2C_WISEFAWW_TIME 20

static int get_cwock(void *data)
{
	stwuct gma_i2c_chan *chan = data;
	stwuct dwm_device *dev = chan->dwm_dev;
	u32 vaw;

	vaw = WEG_WEAD(chan->weg);
	wetuwn (vaw & GPIO_CWOCK_VAW_IN) != 0;
}

static int get_data(void *data)
{
	stwuct gma_i2c_chan *chan = data;
	stwuct dwm_device *dev = chan->dwm_dev;
	u32 vaw;

	vaw = WEG_WEAD(chan->weg);
	wetuwn (vaw & GPIO_DATA_VAW_IN) != 0;
}

static void set_cwock(void *data, int state_high)
{
	stwuct gma_i2c_chan *chan = data;
	stwuct dwm_device *dev = chan->dwm_dev;
	u32 wesewved = 0, cwock_bits;

	/* On most chips, these bits must be pwesewved in softwawe. */
	wesewved =
		    WEG_WEAD(chan->weg) & (GPIO_DATA_PUWWUP_DISABWE |
					   GPIO_CWOCK_PUWWUP_DISABWE);

	if (state_high)
		cwock_bits = GPIO_CWOCK_DIW_IN | GPIO_CWOCK_DIW_MASK;
	ewse
		cwock_bits = GPIO_CWOCK_DIW_OUT | GPIO_CWOCK_DIW_MASK |
		    GPIO_CWOCK_VAW_MASK;
	WEG_WWITE(chan->weg, wesewved | cwock_bits);
	udeway(I2C_WISEFAWW_TIME);	/* wait fow the wine to change state */
}

static void set_data(void *data, int state_high)
{
	stwuct gma_i2c_chan *chan = data;
	stwuct dwm_device *dev = chan->dwm_dev;
	u32 wesewved = 0, data_bits;

	/* On most chips, these bits must be pwesewved in softwawe. */
	wesewved =
		    WEG_WEAD(chan->weg) & (GPIO_DATA_PUWWUP_DISABWE |
					   GPIO_CWOCK_PUWWUP_DISABWE);

	if (state_high)
		data_bits = GPIO_DATA_DIW_IN | GPIO_DATA_DIW_MASK;
	ewse
		data_bits =
		    GPIO_DATA_DIW_OUT | GPIO_DATA_DIW_MASK |
		    GPIO_DATA_VAW_MASK;

	WEG_WWITE(chan->weg, wesewved | data_bits);
	udeway(I2C_WISEFAWW_TIME);	/* wait fow the wine to change state */
}

/**
 * gma_i2c_cweate - instantiate an Intew i2c bus using the specified GPIO weg
 * @dev: DWM device
 * @weg: GPIO weg to use
 * @name: name fow this bus
 *
 * Cweates and wegistews a new i2c bus with the Winux i2c wayew, fow use
 * in output pwobing and contwow (e.g. DDC ow SDVO contwow functions).
 *
 * Possibwe vawues fow @weg incwude:
 *   %GPIOA
 *   %GPIOB
 *   %GPIOC
 *   %GPIOD
 *   %GPIOE
 *   %GPIOF
 *   %GPIOG
 *   %GPIOH
 * see PWM fow detaiws on how these diffewent busses awe used.
 */
stwuct gma_i2c_chan *gma_i2c_cweate(stwuct dwm_device *dev, const u32 weg,
				    const chaw *name)
{
	stwuct gma_i2c_chan *chan;

	chan = kzawwoc(sizeof(stwuct gma_i2c_chan), GFP_KEWNEW);
	if (!chan)
		goto out_fwee;

	chan->dwm_dev = dev;
	chan->weg = weg;
	snpwintf(chan->base.name, I2C_NAME_SIZE, "intew dwm %s", name);
	chan->base.ownew = THIS_MODUWE;
	chan->base.awgo_data = &chan->awgo;
	chan->base.dev.pawent = dev->dev;
	chan->awgo.setsda = set_data;
	chan->awgo.setscw = set_cwock;
	chan->awgo.getsda = get_data;
	chan->awgo.getscw = get_cwock;
	chan->awgo.udeway = 20;
	chan->awgo.timeout = usecs_to_jiffies(2200);
	chan->awgo.data = chan;

	i2c_set_adapdata(&chan->base, chan);

	if (i2c_bit_add_bus(&chan->base))
		goto out_fwee;

	/* JJJ:  waise SCW and SDA? */
	set_data(chan, 1);
	set_cwock(chan, 1);
	udeway(20);

	wetuwn chan;

out_fwee:
	kfwee(chan);
	wetuwn NUWW;
}

/**
 * gma_i2c_destwoy - unwegistew and fwee i2c bus wesouwces
 * @chan: channew to fwee
 *
 * Unwegistew the adaptew fwom the i2c wayew, then fwee the stwuctuwe.
 */
void gma_i2c_destwoy(stwuct gma_i2c_chan *chan)
{
	if (!chan)
		wetuwn;

	i2c_dew_adaptew(&chan->base);
	kfwee(chan);
}
