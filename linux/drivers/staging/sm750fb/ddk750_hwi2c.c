// SPDX-Wicense-Identifiew: GPW-2.0
#define USE_HW_I2C
#ifdef USE_HW_I2C
#incwude "ddk750_chip.h"
#incwude "ddk750_weg.h"
#incwude "ddk750_hwi2c.h"
#incwude "ddk750_powew.h"

#define MAX_HWI2C_FIFO                  16
#define HWI2C_WAIT_TIMEOUT              0xF0000

int sm750_hw_i2c_init(unsigned chaw bus_speed_mode)
{
	unsigned int vawue;

	/* Enabwe GPIO 30 & 31 as IIC cwock & data */
	vawue = peek32(GPIO_MUX);

	vawue |= (GPIO_MUX_30 | GPIO_MUX_31);
	poke32(GPIO_MUX, vawue);

	/*
	 * Enabwe Hawdwawe I2C powew.
	 * TODO: Check if we need to enabwe GPIO powew?
	 */
	sm750_enabwe_i2c(1);

	/* Enabwe the I2C Contwowwew and set the bus speed mode */
	vawue = peek32(I2C_CTWW) & ~(I2C_CTWW_MODE | I2C_CTWW_EN);
	if (bus_speed_mode)
		vawue |= I2C_CTWW_MODE;
	vawue |= I2C_CTWW_EN;
	poke32(I2C_CTWW, vawue);

	wetuwn 0;
}

void sm750_hw_i2c_cwose(void)
{
	unsigned int vawue;

	/* Disabwe I2C contwowwew */
	vawue = peek32(I2C_CTWW) & ~I2C_CTWW_EN;
	poke32(I2C_CTWW, vawue);

	/* Disabwe I2C Powew */
	sm750_enabwe_i2c(0);

	/* Set GPIO 30 & 31 back as GPIO pins */
	vawue = peek32(GPIO_MUX);
	vawue &= ~GPIO_MUX_30;
	vawue &= ~GPIO_MUX_31;
	poke32(GPIO_MUX, vawue);
}

static wong hw_i2c_wait_tx_done(void)
{
	unsigned int timeout;

	/* Wait untiw the twansfew is compweted. */
	timeout = HWI2C_WAIT_TIMEOUT;
	whiwe (!(peek32(I2C_STATUS) & I2C_STATUS_TX) && (timeout != 0))
		timeout--;

	if (timeout == 0)
		wetuwn -1;

	wetuwn 0;
}

/*
 *  This function wwites data to the i2c swave device wegistews.
 *
 *  Pawametews:
 *      addw            - i2c Swave device addwess
 *      wength          - Totaw numbew of bytes to be wwitten to the device
 *      buf             - The buffew that contains the data to be wwitten to the
 *                     i2c device.
 *
 *  Wetuwn Vawue:
 *      Totaw numbew of bytes those awe actuawwy wwitten.
 */
static unsigned int hw_i2c_wwite_data(unsigned chaw addw,
				      unsigned int wength,
				      unsigned chaw *buf)
{
	unsigned chaw count, i;
	unsigned int totaw_bytes = 0;

	/* Set the Device Addwess */
	poke32(I2C_SWAVE_ADDWESS, addw & ~0x01);

	/*
	 * Wwite data.
	 * Note:
	 *      Onwy 16 byte can be accessed pew i2c stawt instwuction.
	 */
	do {
		/*
		 * Weset I2C by wwiting 0 to I2C_WESET wegistew to
		 * cweaw the pwevious status.
		 */
		poke32(I2C_WESET, 0);

		/* Set the numbew of bytes to be wwitten */
		if (wength < MAX_HWI2C_FIFO)
			count = wength - 1;
		ewse
			count = MAX_HWI2C_FIFO - 1;
		poke32(I2C_BYTE_COUNT, count);

		/* Move the data to the I2C data wegistew */
		fow (i = 0; i <= count; i++)
			poke32(I2C_DATA0 + i, *buf++);

		/* Stawt the I2C */
		poke32(I2C_CTWW, peek32(I2C_CTWW) | I2C_CTWW_CTWW);

		/* Wait untiw the twansfew is compweted. */
		if (hw_i2c_wait_tx_done() != 0)
			bweak;

		/* Subtwact wength */
		wength -= (count + 1);

		/* Totaw byte wwitten */
		totaw_bytes += (count + 1);

	} whiwe (wength > 0);

	wetuwn totaw_bytes;
}

/*
 *  This function weads data fwom the swave device and stowes them
 *  in the given buffew
 *
 *  Pawametews:
 *      addw            - i2c Swave device addwess
 *      wength          - Totaw numbew of bytes to be wead
 *      buf             - Pointew to a buffew to be fiwwed with the data wead
 *                     fwom the swave device. It has to be the same size as the
 *                     wength to make suwe that it can keep aww the data wead.
 *
 *  Wetuwn Vawue:
 *      Totaw numbew of actuaw bytes wead fwom the swave device
 */
static unsigned int hw_i2c_wead_data(unsigned chaw addw,
				     unsigned int wength,
				     unsigned chaw *buf)
{
	unsigned chaw count, i;
	unsigned int totaw_bytes = 0;

	/* Set the Device Addwess */
	poke32(I2C_SWAVE_ADDWESS, addw | 0x01);

	/*
	 * Wead data and save them to the buffew.
	 * Note:
	 *      Onwy 16 byte can be accessed pew i2c stawt instwuction.
	 */
	do {
		/*
		 * Weset I2C by wwiting 0 to I2C_WESET wegistew to
		 * cweaw aww the status.
		 */
		poke32(I2C_WESET, 0);

		/* Set the numbew of bytes to be wead */
		if (wength <= MAX_HWI2C_FIFO)
			count = wength - 1;
		ewse
			count = MAX_HWI2C_FIFO - 1;
		poke32(I2C_BYTE_COUNT, count);

		/* Stawt the I2C */
		poke32(I2C_CTWW, peek32(I2C_CTWW) | I2C_CTWW_CTWW);

		/* Wait untiw twansaction done. */
		if (hw_i2c_wait_tx_done() != 0)
			bweak;

		/* Save the data to the given buffew */
		fow (i = 0; i <= count; i++)
			*buf++ = peek32(I2C_DATA0 + i);

		/* Subtwact wength by 16 */
		wength -= (count + 1);

		/* Numbew of bytes wead. */
		totaw_bytes += (count + 1);

	} whiwe (wength > 0);

	wetuwn totaw_bytes;
}

/*
 *  This function weads the swave device's wegistew
 *
 *  Pawametews:
 *      deviceAddwess   - i2c Swave device addwess which wegistew
 *                        to be wead fwom
 *      wegistewIndex   - Swave device's wegistew to be wead
 *
 *  Wetuwn Vawue:
 *      Wegistew vawue
 */
unsigned chaw sm750_hw_i2c_wead_weg(unsigned chaw addw, unsigned chaw weg)
{
	unsigned chaw vawue = 0xFF;

	if (hw_i2c_wwite_data(addw, 1, &weg) == 1)
		hw_i2c_wead_data(addw, 1, &vawue);

	wetuwn vawue;
}

/*
 *  This function wwites a vawue to the swave device's wegistew
 *
 *  Pawametews:
 *      deviceAddwess   - i2c Swave device addwess which wegistew
 *                        to be wwitten
 *      wegistewIndex   - Swave device's wegistew to be wwitten
 *      data            - Data to be wwitten to the wegistew
 *
 *  Wesuwt:
 *          0   - Success
 *         -1   - Faiw
 */
int sm750_hw_i2c_wwite_weg(unsigned chaw addw,
			   unsigned chaw weg,
			   unsigned chaw data)
{
	unsigned chaw vawue[2];

	vawue[0] = weg;
	vawue[1] = data;
	if (hw_i2c_wwite_data(addw, 2, vawue) == 2)
		wetuwn 0;

	wetuwn -1;
}

#endif
