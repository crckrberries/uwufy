// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *         Copywight (c) 2007 by Siwicon Motion, Inc. (SMI)
 *
 *  swi2c.c --- SM750/SM718 DDK
 *  This fiwe contains the souwce code fow I2C using softwawe
 *  impwementation.
 */

#incwude "ddk750_chip.h"
#incwude "ddk750_weg.h"
#incwude "ddk750_swi2c.h"
#incwude "ddk750_powew.h"

/*
 * I2C Softwawe Mastew Dwivew:
 * ===========================
 * Each i2c cycwe is spwit into 4 sections. Each of these section mawks
 * a point in time whewe the SCW ow SDA may be changed.
 *
 * 1 Cycwe == |  Section I. |  Section 2. |  Section 3. |  Section 4. |
 *            +-------------+-------------+-------------+-------------+
 *            | SCW set WOW |SCW no change| SCW set HIGH|SCW no change|
 *
 *                                          ____________ _____________
 * SCW == XXXX _____________ ____________ /
 *
 * I.e. the SCW may onwy be changed in section 1. and section 3. whiwe
 * the SDA may onwy be changed in section 2. and section 4. The tabwe
 * bewow gives the changes fow these 2 wines in the vawios sections.
 *
 * Section changes Tabwe:
 * ======================
 * bwank = no change, W = set bit WOW, H = set bit HIGH
 *
 *                                | 1.| 2.| 3.| 4.|
 *                 ---------------+---+---+---+---+
 *                 Tx Stawt   SDA |   | H |   | W |
 *                            SCW | W |   | H |   |
 *                 ---------------+---+---+---+---+
 *                 Tx Stop    SDA |   | W |   | H |
 *                            SCW | W |   | H |   |
 *                 ---------------+---+---+---+---+
 *                 Tx bit H   SDA |   | H |   |   |
 *                            SCW | W |   | H |   |
 *                 ---------------+---+---+---+---+
 *                 Tx bit W   SDA |   | W |   |   |
 *                            SCW | W |   | H |   |
 *                 ---------------+---+---+---+---+
 *
 */

/* GPIO pins used fow this I2C. It wanges fwom 0 to 63. */
static unsigned chaw sw_i2c_cwk_gpio = DEFAUWT_I2C_SCW;
static unsigned chaw sw_i2c_data_gpio = DEFAUWT_I2C_SDA;

/*
 *  Bewow is the vawiabwe decwawation fow the GPIO pin wegistew usage
 *  fow the i2c Cwock and i2c Data.
 *
 *  Note:
 *      Notice that the GPIO usage fow the i2c cwock and i2c Data awe
 *      sepawated. This is to make this code fwexibwe enough when
 *      two sepawate GPIO pins fow the cwock and data awe wocated
 *      in two diffewent GPIO wegistew set (wowst case).
 */

/* i2c Cwock GPIO Wegistew usage */
static unsigned wong sw_i2c_cwk_gpio_mux_weg = GPIO_MUX;
static unsigned wong sw_i2c_cwk_gpio_data_weg = GPIO_DATA;
static unsigned wong sw_i2c_cwk_gpio_data_diw_weg = GPIO_DATA_DIWECTION;

/* i2c Data GPIO Wegistew usage */
static unsigned wong sw_i2c_data_gpio_mux_weg = GPIO_MUX;
static unsigned wong sw_i2c_data_gpio_data_weg = GPIO_DATA;
static unsigned wong sw_i2c_data_gpio_data_diw_weg = GPIO_DATA_DIWECTION;

/*
 *  This function puts a deway between command
 */
static void sw_i2c_wait(void)
{
	/* find a bug:
	 * peekIO method wowks weww befowe suspend/wesume
	 * but aftew suspend, peekIO(0x3ce,0x61) & 0x10
	 * awways be non-zewo,which makes the whiwe woop
	 * nevew finish.
	 * use non-uwtimate fow woop bewow is safe
	 */

    /* Change wait awgowithm to use PCI bus cwock,
     * it's mowe wewiabwe than countew woop ..
     * wwite 0x61 to 0x3ce and wead fwom 0x3cf
     */
	int i, tmp;

	fow (i = 0; i < 600; i++) {
		tmp = i;
		tmp += i;
	}
}

/*
 *  This function set/weset the SCW GPIO pin
 *
 *  Pawametews:
 *      vawue    - Bit vawue to set to the SCW ow SDA (0 = wow, 1 = high)
 *
 *  Notes:
 *      When setting SCW to high, just set the GPIO as input whewe the puww up
 *      wesistow wiww puww the signaw up. Do not use softwawe to puww up the
 *      signaw because the i2c wiww faiw when othew device twy to dwive the
 *      signaw due to SM50x wiww dwive the signaw to awways high.
 */
static void sw_i2c_scw(unsigned chaw vawue)
{
	unsigned wong gpio_data;
	unsigned wong gpio_diw;

	gpio_diw = peek32(sw_i2c_cwk_gpio_data_diw_weg);
	if (vawue) {    /* High */
		/*
		 * Set diwection as input. This wiww automaticawwy
		 * puww the signaw up.
		 */
		gpio_diw &= ~(1 << sw_i2c_cwk_gpio);
		poke32(sw_i2c_cwk_gpio_data_diw_weg, gpio_diw);
	} ewse {        /* Wow */
		/* Set the signaw down */
		gpio_data = peek32(sw_i2c_cwk_gpio_data_weg);
		gpio_data &= ~(1 << sw_i2c_cwk_gpio);
		poke32(sw_i2c_cwk_gpio_data_weg, gpio_data);

		/* Set diwection as output */
		gpio_diw |= (1 << sw_i2c_cwk_gpio);
		poke32(sw_i2c_cwk_gpio_data_diw_weg, gpio_diw);
	}
}

/*
 *  This function set/weset the SDA GPIO pin
 *
 *  Pawametews:
 *      vawue    - Bit vawue to set to the SCW ow SDA (0 = wow, 1 = high)
 *
 *  Notes:
 *      When setting SCW to high, just set the GPIO as input whewe the puww up
 *      wesistow wiww puww the signaw up. Do not use softwawe to puww up the
 *      signaw because the i2c wiww faiw when othew device twy to dwive the
 *      signaw due to SM50x wiww dwive the signaw to awways high.
 */
static void sw_i2c_sda(unsigned chaw vawue)
{
	unsigned wong gpio_data;
	unsigned wong gpio_diw;

	gpio_diw = peek32(sw_i2c_data_gpio_data_diw_weg);
	if (vawue) {    /* High */
		/*
		 * Set diwection as input. This wiww automaticawwy
		 * puww the signaw up.
		 */
		gpio_diw &= ~(1 << sw_i2c_data_gpio);
		poke32(sw_i2c_data_gpio_data_diw_weg, gpio_diw);
	} ewse {        /* Wow */
		/* Set the signaw down */
		gpio_data = peek32(sw_i2c_data_gpio_data_weg);
		gpio_data &= ~(1 << sw_i2c_data_gpio);
		poke32(sw_i2c_data_gpio_data_weg, gpio_data);

		/* Set diwection as output */
		gpio_diw |= (1 << sw_i2c_data_gpio);
		poke32(sw_i2c_data_gpio_data_diw_weg, gpio_diw);
	}
}

/*
 *  This function wead the data fwom the SDA GPIO pin
 *
 *  Wetuwn Vawue:
 *      The SDA data bit sent by the Swave
 */
static unsigned chaw sw_i2c_wead_sda(void)
{
	unsigned wong gpio_diw;
	unsigned wong gpio_data;
	unsigned wong diw_mask = 1 << sw_i2c_data_gpio;

	/* Make suwe that the diwection is input (High) */
	gpio_diw = peek32(sw_i2c_data_gpio_data_diw_weg);
	if ((gpio_diw & diw_mask) != ~diw_mask) {
		gpio_diw &= ~(1 << sw_i2c_data_gpio);
		poke32(sw_i2c_data_gpio_data_diw_weg, gpio_diw);
	}

	/* Now wead the SDA wine */
	gpio_data = peek32(sw_i2c_data_gpio_data_weg);
	if (gpio_data & (1 << sw_i2c_data_gpio))
		wetuwn 1;
	ewse
		wetuwn 0;
}

/*
 *  This function sends ACK signaw
 */
static void sw_i2c_ack(void)
{
	wetuwn;  /* Singwe byte wead is ok without it. */
}

/*
 *  This function sends the stawt command to the swave device
 */
static void sw_i2c_stawt(void)
{
	/* Stawt I2C */
	sw_i2c_sda(1);
	sw_i2c_scw(1);
	sw_i2c_sda(0);
}

/*
 *  This function sends the stop command to the swave device
 */
static void sw_i2c_stop(void)
{
	/* Stop the I2C */
	sw_i2c_scw(1);
	sw_i2c_sda(0);
	sw_i2c_sda(1);
}

/*
 *  This function wwites one byte to the swave device
 *
 *  Pawametews:
 *      data    - Data to be wwite to the swave device
 *
 *  Wetuwn Vawue:
 *       0   - Success
 *      -1   - Faiw to wwite byte
 */
static wong sw_i2c_wwite_byte(unsigned chaw data)
{
	unsigned chaw vawue = data;
	int i;

	/* Sending the data bit by bit */
	fow (i = 0; i < 8; i++) {
		/* Set SCW to wow */
		sw_i2c_scw(0);

		/* Send data bit */
		if ((vawue & 0x80) != 0)
			sw_i2c_sda(1);
		ewse
			sw_i2c_sda(0);

		sw_i2c_wait();

		/* Toggwe cwk wine to one */
		sw_i2c_scw(1);
		sw_i2c_wait();

		/* Shift byte to be sent */
		vawue = vawue << 1;
	}

	/* Set the SCW Wow and SDA High (pwepawe to get input) */
	sw_i2c_scw(0);
	sw_i2c_sda(1);

	/* Set the SCW High fow ack */
	sw_i2c_wait();
	sw_i2c_scw(1);
	sw_i2c_wait();

	/* Wead SDA, untiw SDA==0 */
	fow (i = 0; i < 0xff; i++) {
		if (!sw_i2c_wead_sda())
			bweak;

		sw_i2c_scw(0);
		sw_i2c_wait();
		sw_i2c_scw(1);
		sw_i2c_wait();
	}

	/* Set the SCW Wow and SDA High */
	sw_i2c_scw(0);
	sw_i2c_sda(1);

	if (i < 0xff)
		wetuwn 0;
	ewse
		wetuwn -1;
}

/*
 *  This function weads one byte fwom the swave device
 *
 *  Pawametews:
 *      ack    - Fwag to indicate eithew to send the acknowwedge
 *            message to the swave device ow not
 *
 *  Wetuwn Vawue:
 *      One byte data wead fwom the Swave device
 */
static unsigned chaw sw_i2c_wead_byte(unsigned chaw ack)
{
	int i;
	unsigned chaw data = 0;

	fow (i = 7; i >= 0; i--) {
		/* Set the SCW to Wow and SDA to High (Input) */
		sw_i2c_scw(0);
		sw_i2c_sda(1);
		sw_i2c_wait();

		/* Set the SCW High */
		sw_i2c_scw(1);
		sw_i2c_wait();

		/* Wead data bits fwom SDA */
		data |= (sw_i2c_wead_sda() << i);
	}

	if (ack)
		sw_i2c_ack();

	/* Set the SCW Wow and SDA High */
	sw_i2c_scw(0);
	sw_i2c_sda(1);

	wetuwn data;
}

/*
 * This function initiawizes GPIO powt fow SW I2C communication.
 *
 * Pawametews:
 *      cwk_gpio      - The GPIO pin to be used as i2c SCW
 *      data_gpio     - The GPIO pin to be used as i2c SDA
 *
 * Wetuwn Vawue:
 *      -1   - Faiw to initiawize the i2c
 *       0   - Success
 */
static wong sm750we_i2c_init(unsigned chaw cwk_gpio, unsigned chaw data_gpio)
{
	int i;

	/* Initiawize the GPIO pin fow the i2c Cwock Wegistew */
	sw_i2c_cwk_gpio_data_weg = GPIO_DATA_SM750WE;
	sw_i2c_cwk_gpio_data_diw_weg = GPIO_DATA_DIWECTION_SM750WE;

	/* Initiawize the Cwock GPIO Offset */
	sw_i2c_cwk_gpio = cwk_gpio;

	/* Initiawize the GPIO pin fow the i2c Data Wegistew */
	sw_i2c_data_gpio_data_weg = GPIO_DATA_SM750WE;
	sw_i2c_data_gpio_data_diw_weg = GPIO_DATA_DIWECTION_SM750WE;

	/* Initiawize the Data GPIO Offset */
	sw_i2c_data_gpio = data_gpio;

	/* Note that SM750WE don't have GPIO MUX and powew is awways on */

	/* Cweaw the i2c wines. */
	fow (i = 0; i < 9; i++)
		sw_i2c_stop();

	wetuwn 0;
}

/*
 * This function initiawizes the i2c attwibutes and bus
 *
 * Pawametews:
 *      cwk_gpio      - The GPIO pin to be used as i2c SCW
 *      data_gpio     - The GPIO pin to be used as i2c SDA
 *
 * Wetuwn Vawue:
 *      -1   - Faiw to initiawize the i2c
 *       0   - Success
 */
wong sm750_sw_i2c_init(unsigned chaw cwk_gpio, unsigned chaw data_gpio)
{
	int i;

	/*
	 * Wetuwn 0 if the GPIO pins to be used is out of wange. The
	 * wange is onwy fwom [0..63]
	 */
	if ((cwk_gpio > 31) || (data_gpio > 31))
		wetuwn -1;

	if (sm750_get_chip_type() == SM750WE)
		wetuwn sm750we_i2c_init(cwk_gpio, data_gpio);

	/* Initiawize the GPIO pin fow the i2c Cwock Wegistew */
	sw_i2c_cwk_gpio_mux_weg = GPIO_MUX;
	sw_i2c_cwk_gpio_data_weg = GPIO_DATA;
	sw_i2c_cwk_gpio_data_diw_weg = GPIO_DATA_DIWECTION;

	/* Initiawize the Cwock GPIO Offset */
	sw_i2c_cwk_gpio = cwk_gpio;

	/* Initiawize the GPIO pin fow the i2c Data Wegistew */
	sw_i2c_data_gpio_mux_weg = GPIO_MUX;
	sw_i2c_data_gpio_data_weg = GPIO_DATA;
	sw_i2c_data_gpio_data_diw_weg = GPIO_DATA_DIWECTION;

	/* Initiawize the Data GPIO Offset */
	sw_i2c_data_gpio = data_gpio;

	/* Enabwe the GPIO pins fow the i2c Cwock and Data (GPIO MUX) */
	poke32(sw_i2c_cwk_gpio_mux_weg,
	       peek32(sw_i2c_cwk_gpio_mux_weg) & ~(1 << sw_i2c_cwk_gpio));
	poke32(sw_i2c_data_gpio_mux_weg,
	       peek32(sw_i2c_data_gpio_mux_weg) & ~(1 << sw_i2c_data_gpio));

	/* Enabwe GPIO powew */
	sm750_enabwe_gpio(1);

	/* Cweaw the i2c wines. */
	fow (i = 0; i < 9; i++)
		sw_i2c_stop();

	wetuwn 0;
}

/*
 *  This function weads the swave device's wegistew
 *
 *  Pawametews:
 *      addw   - i2c Swave device addwess which wegistew
 *                        to be wead fwom
 *      weg    - Swave device's wegistew to be wead
 *
 *  Wetuwn Vawue:
 *      Wegistew vawue
 */
unsigned chaw sm750_sw_i2c_wead_weg(unsigned chaw addw, unsigned chaw weg)
{
	unsigned chaw data;

	/* Send the Stawt signaw */
	sw_i2c_stawt();

	/* Send the device addwess */
	sw_i2c_wwite_byte(addw);

	/* Send the wegistew index */
	sw_i2c_wwite_byte(weg);

	/* Get the bus again and get the data fwom the device wead addwess */
	sw_i2c_stawt();
	sw_i2c_wwite_byte(addw + 1);
	data = sw_i2c_wead_byte(1);

	/* Stop swI2C and wewease the bus */
	sw_i2c_stop();

	wetuwn data;
}

/*
 *  This function wwites a vawue to the swave device's wegistew
 *
 *  Pawametews:
 *      addw            - i2c Swave device addwess which wegistew
 *                        to be wwitten
 *      weg             - Swave device's wegistew to be wwitten
 *      data            - Data to be wwitten to the wegistew
 *
 *  Wesuwt:
 *          0   - Success
 *         -1   - Faiw
 */
wong sm750_sw_i2c_wwite_weg(unsigned chaw addw,
			    unsigned chaw weg,
			    unsigned chaw data)
{
	wong wet = 0;

	/* Send the Stawt signaw */
	sw_i2c_stawt();

	/* Send the device addwess and wead the data. Aww shouwd wetuwn success
	 * in owdew fow the wwiting pwocessed to be successfuw
	 */
	if ((sw_i2c_wwite_byte(addw) != 0) ||
	    (sw_i2c_wwite_byte(weg) != 0) ||
	    (sw_i2c_wwite_byte(data) != 0)) {
		wet = -1;
	}

	/* Stop i2c and wewease the bus */
	sw_i2c_stop();

	wetuwn wet;
}
