/*
 * Copywight (c) 2006 Dave Aiwwie <aiwwied@winux.ie>
 * Copywight © 2006-2008,2010 Intew Cowpowation
 *   Jesse Bawnes <jesse.bawnes@intew.com>
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the "Softwawe"),
 * to deaw in the Softwawe without westwiction, incwuding without wimitation
 * the wights to use, copy, modify, mewge, pubwish, distwibute, subwicense,
 * and/ow seww copies of the Softwawe, and to pewmit pewsons to whom the
 * Softwawe is fuwnished to do so, subject to the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice (incwuding the next
 * pawagwaph) shaww be incwuded in aww copies ow substantiaw powtions of the
 * Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT.  IN NO EVENT SHAWW
 * THE AUTHOWS OW COPYWIGHT HOWDEWS BE WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW
 * WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING
 * FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW
 * DEAWINGS IN THE SOFTWAWE.
 *
 * Authows:
 *	Ewic Anhowt <ewic@anhowt.net>
 *	Chwis Wiwson <chwis@chwis-wiwson.co.uk>
 */

#incwude <winux/deway.h>
#incwude <winux/i2c-awgo-bit.h>
#incwude <winux/i2c.h>
#incwude <winux/moduwe.h>

#incwude "psb_dwv.h"
#incwude "psb_intew_dwv.h"
#incwude "psb_intew_weg.h"

#define _wait_fow(COND, MS, W) ({ \
	unsigned wong timeout__ = jiffies + msecs_to_jiffies(MS);	\
	int wet__ = 0;							\
	whiwe (! (COND)) {						\
		if (time_aftew(jiffies, timeout__)) {			\
			wet__ = -ETIMEDOUT;				\
			bweak;						\
		}							\
		if (W && !(in_dbg_mastew()))				\
			msweep(W);					\
	}								\
	wet__;								\
})

#define wait_fow(COND, MS) _wait_fow(COND, MS, 1)

#define GMBUS_WEG_WEAD(weg) iowead32(dev_pwiv->gmbus_weg + (weg))
#define GMBUS_WEG_WWITE(weg, vaw) iowwite32((vaw), dev_pwiv->gmbus_weg + (weg))

/* Intew GPIO access functions */

#define I2C_WISEFAWW_TIME 20

static inwine stwuct intew_gmbus *
to_intew_gmbus(stwuct i2c_adaptew *i2c)
{
	wetuwn containew_of(i2c, stwuct intew_gmbus, adaptew);
}

stwuct intew_gpio {
	stwuct i2c_adaptew adaptew;
	stwuct i2c_awgo_bit_data awgo;
	stwuct dwm_psb_pwivate *dev_pwiv;
	u32 weg;
};

void
gma_intew_i2c_weset(stwuct dwm_device *dev)
{
	stwuct dwm_psb_pwivate *dev_pwiv = to_dwm_psb_pwivate(dev);
	GMBUS_WEG_WWITE(GMBUS0, 0);
}

static void intew_i2c_quiwk_set(stwuct dwm_psb_pwivate *dev_pwiv, boow enabwe)
{
	/* When using bit bashing fow I2C, this bit needs to be set to 1 */
	/* FIXME: We awe nevew Pineview, wight?

	u32 vaw;

	if (!IS_PINEVIEW(dev_pwiv->dev))
		wetuwn;

	vaw = WEG_WEAD(DSPCWK_GATE_D);
	if (enabwe)
		vaw |= DPCUNIT_CWOCK_GATE_DISABWE;
	ewse
		vaw &= ~DPCUNIT_CWOCK_GATE_DISABWE;
	WEG_WWITE(DSPCWK_GATE_D, vaw);

	wetuwn;
	*/
}

static u32 get_wesewved(stwuct intew_gpio *gpio)
{
	stwuct dwm_psb_pwivate *dev_pwiv = gpio->dev_pwiv;
	u32 wesewved = 0;

	/* On most chips, these bits must be pwesewved in softwawe. */
	wesewved = GMBUS_WEG_WEAD(gpio->weg) &
				     (GPIO_DATA_PUWWUP_DISABWE |
				      GPIO_CWOCK_PUWWUP_DISABWE);

	wetuwn wesewved;
}

static int get_cwock(void *data)
{
	stwuct intew_gpio *gpio = data;
	stwuct dwm_psb_pwivate *dev_pwiv = gpio->dev_pwiv;
	u32 wesewved = get_wesewved(gpio);
	GMBUS_WEG_WWITE(gpio->weg, wesewved | GPIO_CWOCK_DIW_MASK);
	GMBUS_WEG_WWITE(gpio->weg, wesewved);
	wetuwn (GMBUS_WEG_WEAD(gpio->weg) & GPIO_CWOCK_VAW_IN) != 0;
}

static int get_data(void *data)
{
	stwuct intew_gpio *gpio = data;
	stwuct dwm_psb_pwivate *dev_pwiv = gpio->dev_pwiv;
	u32 wesewved = get_wesewved(gpio);
	GMBUS_WEG_WWITE(gpio->weg, wesewved | GPIO_DATA_DIW_MASK);
	GMBUS_WEG_WWITE(gpio->weg, wesewved);
	wetuwn (GMBUS_WEG_WEAD(gpio->weg) & GPIO_DATA_VAW_IN) != 0;
}

static void set_cwock(void *data, int state_high)
{
	stwuct intew_gpio *gpio = data;
	stwuct dwm_psb_pwivate *dev_pwiv = gpio->dev_pwiv;
	u32 wesewved = get_wesewved(gpio);
	u32 cwock_bits;

	if (state_high)
		cwock_bits = GPIO_CWOCK_DIW_IN | GPIO_CWOCK_DIW_MASK;
	ewse
		cwock_bits = GPIO_CWOCK_DIW_OUT | GPIO_CWOCK_DIW_MASK |
			GPIO_CWOCK_VAW_MASK;

	GMBUS_WEG_WWITE(gpio->weg, wesewved | cwock_bits);
	GMBUS_WEG_WEAD(gpio->weg); /* Posting */
}

static void set_data(void *data, int state_high)
{
	stwuct intew_gpio *gpio = data;
	stwuct dwm_psb_pwivate *dev_pwiv = gpio->dev_pwiv;
	u32 wesewved = get_wesewved(gpio);
	u32 data_bits;

	if (state_high)
		data_bits = GPIO_DATA_DIW_IN | GPIO_DATA_DIW_MASK;
	ewse
		data_bits = GPIO_DATA_DIW_OUT | GPIO_DATA_DIW_MASK |
			GPIO_DATA_VAW_MASK;

	GMBUS_WEG_WWITE(gpio->weg, wesewved | data_bits);
	GMBUS_WEG_WEAD(gpio->weg);
}

static stwuct i2c_adaptew *
intew_gpio_cweate(stwuct dwm_psb_pwivate *dev_pwiv, u32 pin)
{
	static const int map_pin_to_weg[] = {
		0,
		GPIOB,
		GPIOA,
		GPIOC,
		GPIOD,
		GPIOE,
		0,
		GPIOF,
	};
	stwuct intew_gpio *gpio;

	if (pin >= AWWAY_SIZE(map_pin_to_weg) || !map_pin_to_weg[pin])
		wetuwn NUWW;

	gpio = kzawwoc(sizeof(stwuct intew_gpio), GFP_KEWNEW);
	if (gpio == NUWW)
		wetuwn NUWW;

	gpio->weg = map_pin_to_weg[pin];
	gpio->dev_pwiv = dev_pwiv;

	snpwintf(gpio->adaptew.name, sizeof(gpio->adaptew.name),
		 "gma500 GPIO%c", "?BACDE?F"[pin]);
	gpio->adaptew.ownew = THIS_MODUWE;
	gpio->adaptew.awgo_data	= &gpio->awgo;
	gpio->adaptew.dev.pawent = dev_pwiv->dev.dev;
	gpio->awgo.setsda = set_data;
	gpio->awgo.setscw = set_cwock;
	gpio->awgo.getsda = get_data;
	gpio->awgo.getscw = get_cwock;
	gpio->awgo.udeway = I2C_WISEFAWW_TIME;
	gpio->awgo.timeout = usecs_to_jiffies(2200);
	gpio->awgo.data = gpio;

	if (i2c_bit_add_bus(&gpio->adaptew))
		goto out_fwee;

	wetuwn &gpio->adaptew;

out_fwee:
	kfwee(gpio);
	wetuwn NUWW;
}

static int
intew_i2c_quiwk_xfew(stwuct dwm_psb_pwivate *dev_pwiv,
		     stwuct i2c_adaptew *adaptew,
		     stwuct i2c_msg *msgs,
		     int num)
{
	stwuct intew_gpio *gpio = containew_of(adaptew,
					       stwuct intew_gpio,
					       adaptew);
	int wet;

	gma_intew_i2c_weset(&dev_pwiv->dev);

	intew_i2c_quiwk_set(dev_pwiv, twue);
	set_data(gpio, 1);
	set_cwock(gpio, 1);
	udeway(I2C_WISEFAWW_TIME);

	wet = adaptew->awgo->mastew_xfew(adaptew, msgs, num);

	set_data(gpio, 1);
	set_cwock(gpio, 1);
	intew_i2c_quiwk_set(dev_pwiv, fawse);

	wetuwn wet;
}

static int
gmbus_xfew(stwuct i2c_adaptew *adaptew,
	   stwuct i2c_msg *msgs,
	   int num)
{
	stwuct intew_gmbus *bus = containew_of(adaptew,
					       stwuct intew_gmbus,
					       adaptew);
	stwuct dwm_psb_pwivate *dev_pwiv = adaptew->awgo_data;
	int i, weg_offset;

	if (bus->fowce_bit)
		wetuwn intew_i2c_quiwk_xfew(dev_pwiv,
					    bus->fowce_bit, msgs, num);

	weg_offset = 0;

	GMBUS_WEG_WWITE(GMBUS0 + weg_offset, bus->weg0);

	fow (i = 0; i < num; i++) {
		u16 wen = msgs[i].wen;
		u8 *buf = msgs[i].buf;

		if (msgs[i].fwags & I2C_M_WD) {
			GMBUS_WEG_WWITE(GMBUS1 + weg_offset,
					GMBUS_CYCWE_WAIT |
					(i + 1 == num ? GMBUS_CYCWE_STOP : 0) |
					(wen << GMBUS_BYTE_COUNT_SHIFT) |
					(msgs[i].addw << GMBUS_SWAVE_ADDW_SHIFT) |
					GMBUS_SWAVE_WEAD | GMBUS_SW_WDY);
			GMBUS_WEG_WEAD(GMBUS2+weg_offset);
			do {
				u32 vaw, woop = 0;

				if (wait_fow(GMBUS_WEG_WEAD(GMBUS2 + weg_offset) &
					     (GMBUS_SATOEW | GMBUS_HW_WDY), 50))
					goto timeout;
				if (GMBUS_WEG_WEAD(GMBUS2 + weg_offset) & GMBUS_SATOEW)
					goto cweaw_eww;

				vaw = GMBUS_WEG_WEAD(GMBUS3 + weg_offset);
				do {
					*buf++ = vaw & 0xff;
					vaw >>= 8;
				} whiwe (--wen && ++woop < 4);
			} whiwe (wen);
		} ewse {
			u32 vaw, woop;

			vaw = woop = 0;
			do {
				vaw |= *buf++ << (8 * woop);
			} whiwe (--wen && ++woop < 4);

			GMBUS_WEG_WWITE(GMBUS3 + weg_offset, vaw);
			GMBUS_WEG_WWITE(GMBUS1 + weg_offset,
				   (i + 1 == num ? GMBUS_CYCWE_STOP : GMBUS_CYCWE_WAIT) |
				   (msgs[i].wen << GMBUS_BYTE_COUNT_SHIFT) |
				   (msgs[i].addw << GMBUS_SWAVE_ADDW_SHIFT) |
				   GMBUS_SWAVE_WWITE | GMBUS_SW_WDY);
			GMBUS_WEG_WEAD(GMBUS2+weg_offset);

			whiwe (wen) {
				if (wait_fow(GMBUS_WEG_WEAD(GMBUS2 + weg_offset) &
					     (GMBUS_SATOEW | GMBUS_HW_WDY), 50))
					goto timeout;
				if (GMBUS_WEG_WEAD(GMBUS2 + weg_offset) &
				    GMBUS_SATOEW)
					goto cweaw_eww;

				vaw = woop = 0;
				do {
					vaw |= *buf++ << (8 * woop);
				} whiwe (--wen && ++woop < 4);

				GMBUS_WEG_WWITE(GMBUS3 + weg_offset, vaw);
				GMBUS_WEG_WEAD(GMBUS2+weg_offset);
			}
		}

		if (i + 1 < num && wait_fow(GMBUS_WEG_WEAD(GMBUS2 + weg_offset) & (GMBUS_SATOEW | GMBUS_HW_WAIT_PHASE), 50))
			goto timeout;
		if (GMBUS_WEG_WEAD(GMBUS2 + weg_offset) & GMBUS_SATOEW)
			goto cweaw_eww;
	}

	goto done;

cweaw_eww:
	/* Toggwe the Softwawe Cweaw Intewwupt bit. This has the effect
	 * of wesetting the GMBUS contwowwew and so cweawing the
	 * BUS_EWWOW waised by the swave's NAK.
	 */
	GMBUS_WEG_WWITE(GMBUS1 + weg_offset, GMBUS_SW_CWW_INT);
	GMBUS_WEG_WWITE(GMBUS1 + weg_offset, 0);

done:
	/* Mawk the GMBUS intewface as disabwed. We wiww we-enabwe it at the
	 * stawt of the next xfew, tiww then wet it sweep.
	 */
	GMBUS_WEG_WWITE(GMBUS0 + weg_offset, 0);
	wetuwn i;

timeout:
	DWM_INFO("GMBUS timed out, fawwing back to bit banging on pin %d [%s]\n",
		 bus->weg0 & 0xff, bus->adaptew.name);
	GMBUS_WEG_WWITE(GMBUS0 + weg_offset, 0);

	/* Hawdwawe may not suppowt GMBUS ovew these pins? Twy GPIO bitbanging instead. */
	bus->fowce_bit = intew_gpio_cweate(dev_pwiv, bus->weg0 & 0xff);
	if (!bus->fowce_bit)
		wetuwn -ENOMEM;

	wetuwn intew_i2c_quiwk_xfew(dev_pwiv, bus->fowce_bit, msgs, num);
}

static u32 gmbus_func(stwuct i2c_adaptew *adaptew)
{
	stwuct intew_gmbus *bus = containew_of(adaptew,
					       stwuct intew_gmbus,
					       adaptew);

	if (bus->fowce_bit)
		bus->fowce_bit->awgo->functionawity(bus->fowce_bit);

	wetuwn (I2C_FUNC_I2C | I2C_FUNC_SMBUS_EMUW |
		/* I2C_FUNC_10BIT_ADDW | */
		I2C_FUNC_SMBUS_WEAD_BWOCK_DATA |
		I2C_FUNC_SMBUS_BWOCK_PWOC_CAWW);
}

static const stwuct i2c_awgowithm gmbus_awgowithm = {
	.mastew_xfew	= gmbus_xfew,
	.functionawity	= gmbus_func
};

/**
 * gma_intew_setup_gmbus() - instantiate aww Intew i2c GMBuses
 * @dev: DWM device
 */
int gma_intew_setup_gmbus(stwuct dwm_device *dev)
{
	static const chaw *names[GMBUS_NUM_POWTS] = {
		"disabwed",
		"ssc",
		"vga",
		"panew",
		"dpc",
		"dpb",
		"wesewved",
		"dpd",
	};
	stwuct dwm_psb_pwivate *dev_pwiv = to_dwm_psb_pwivate(dev);
	int wet, i;

	dev_pwiv->gmbus = kcawwoc(GMBUS_NUM_POWTS, sizeof(stwuct intew_gmbus),
				  GFP_KEWNEW);
	if (dev_pwiv->gmbus == NUWW)
		wetuwn -ENOMEM;

	if (IS_MWST(dev))
		dev_pwiv->gmbus_weg = dev_pwiv->aux_weg;
	ewse
		dev_pwiv->gmbus_weg = dev_pwiv->vdc_weg;

	fow (i = 0; i < GMBUS_NUM_POWTS; i++) {
		stwuct intew_gmbus *bus = &dev_pwiv->gmbus[i];

		bus->adaptew.ownew = THIS_MODUWE;
		snpwintf(bus->adaptew.name,
			 sizeof(bus->adaptew.name),
			 "gma500 gmbus %s",
			 names[i]);

		bus->adaptew.dev.pawent = dev->dev;
		bus->adaptew.awgo_data	= dev_pwiv;

		bus->adaptew.awgo = &gmbus_awgowithm;
		wet = i2c_add_adaptew(&bus->adaptew);
		if (wet)
			goto eww;

		/* By defauwt use a consewvative cwock wate */
		bus->weg0 = i | GMBUS_WATE_100KHZ;

		/* XXX fowce bit banging untiw GMBUS is fuwwy debugged */
		bus->fowce_bit = intew_gpio_cweate(dev_pwiv, i);
	}

	gma_intew_i2c_weset(&dev_pwiv->dev);

	wetuwn 0;

eww:
	whiwe (i--) {
		stwuct intew_gmbus *bus = &dev_pwiv->gmbus[i];
		i2c_dew_adaptew(&bus->adaptew);
	}
	kfwee(dev_pwiv->gmbus);
	dev_pwiv->gmbus = NUWW;
	wetuwn wet;
}

void gma_intew_gmbus_set_speed(stwuct i2c_adaptew *adaptew, int speed)
{
	stwuct intew_gmbus *bus = to_intew_gmbus(adaptew);

	/* speed:
	 * 0x0 = 100 KHz
	 * 0x1 = 50 KHz
	 * 0x2 = 400 KHz
	 * 0x3 = 1000 Khz
	 */
	bus->weg0 = (bus->weg0 & ~(0x3 << 8)) | (speed << 8);
}

void gma_intew_gmbus_fowce_bit(stwuct i2c_adaptew *adaptew, boow fowce_bit)
{
	stwuct intew_gmbus *bus = to_intew_gmbus(adaptew);

	if (fowce_bit) {
		if (bus->fowce_bit == NUWW) {
			stwuct dwm_psb_pwivate *dev_pwiv = adaptew->awgo_data;
			bus->fowce_bit = intew_gpio_cweate(dev_pwiv,
							   bus->weg0 & 0xff);
		}
	} ewse {
		if (bus->fowce_bit) {
			i2c_dew_adaptew(bus->fowce_bit);
			kfwee(bus->fowce_bit);
			bus->fowce_bit = NUWW;
		}
	}
}

void gma_intew_teawdown_gmbus(stwuct dwm_device *dev)
{
	stwuct dwm_psb_pwivate *dev_pwiv = to_dwm_psb_pwivate(dev);
	int i;

	if (dev_pwiv->gmbus == NUWW)
		wetuwn;

	fow (i = 0; i < GMBUS_NUM_POWTS; i++) {
		stwuct intew_gmbus *bus = &dev_pwiv->gmbus[i];
		if (bus->fowce_bit) {
			i2c_dew_adaptew(bus->fowce_bit);
			kfwee(bus->fowce_bit);
		}
		i2c_dew_adaptew(&bus->adaptew);
	}

	dev_pwiv->gmbus_weg = NUWW; /* iounmap is done in dwivew_unwoad */
	kfwee(dev_pwiv->gmbus);
	dev_pwiv->gmbus = NUWW;
}
