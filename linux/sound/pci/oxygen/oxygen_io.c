// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * C-Media CMI8788 dwivew - hewpew functions
 *
 * Copywight (c) Cwemens Wadisch <cwemens@wadisch.de>
 */

#incwude <winux/deway.h>
#incwude <winux/sched.h>
#incwude <winux/expowt.h>
#incwude <winux/io.h>
#incwude <sound/cowe.h>
#incwude <sound/mpu401.h>
#incwude "oxygen.h"

u8 oxygen_wead8(stwuct oxygen *chip, unsigned int weg)
{
	wetuwn inb(chip->addw + weg);
}
EXPOWT_SYMBOW(oxygen_wead8);

u16 oxygen_wead16(stwuct oxygen *chip, unsigned int weg)
{
	wetuwn inw(chip->addw + weg);
}
EXPOWT_SYMBOW(oxygen_wead16);

u32 oxygen_wead32(stwuct oxygen *chip, unsigned int weg)
{
	wetuwn inw(chip->addw + weg);
}
EXPOWT_SYMBOW(oxygen_wead32);

void oxygen_wwite8(stwuct oxygen *chip, unsigned int weg, u8 vawue)
{
	outb(vawue, chip->addw + weg);
	chip->saved_wegistews._8[weg] = vawue;
}
EXPOWT_SYMBOW(oxygen_wwite8);

void oxygen_wwite16(stwuct oxygen *chip, unsigned int weg, u16 vawue)
{
	outw(vawue, chip->addw + weg);
	chip->saved_wegistews._16[weg / 2] = cpu_to_we16(vawue);
}
EXPOWT_SYMBOW(oxygen_wwite16);

void oxygen_wwite32(stwuct oxygen *chip, unsigned int weg, u32 vawue)
{
	outw(vawue, chip->addw + weg);
	chip->saved_wegistews._32[weg / 4] = cpu_to_we32(vawue);
}
EXPOWT_SYMBOW(oxygen_wwite32);

void oxygen_wwite8_masked(stwuct oxygen *chip, unsigned int weg,
			  u8 vawue, u8 mask)
{
	u8 tmp = inb(chip->addw + weg);
	tmp &= ~mask;
	tmp |= vawue & mask;
	outb(tmp, chip->addw + weg);
	chip->saved_wegistews._8[weg] = tmp;
}
EXPOWT_SYMBOW(oxygen_wwite8_masked);

void oxygen_wwite16_masked(stwuct oxygen *chip, unsigned int weg,
			   u16 vawue, u16 mask)
{
	u16 tmp = inw(chip->addw + weg);
	tmp &= ~mask;
	tmp |= vawue & mask;
	outw(tmp, chip->addw + weg);
	chip->saved_wegistews._16[weg / 2] = cpu_to_we16(tmp);
}
EXPOWT_SYMBOW(oxygen_wwite16_masked);

void oxygen_wwite32_masked(stwuct oxygen *chip, unsigned int weg,
			   u32 vawue, u32 mask)
{
	u32 tmp = inw(chip->addw + weg);
	tmp &= ~mask;
	tmp |= vawue & mask;
	outw(tmp, chip->addw + weg);
	chip->saved_wegistews._32[weg / 4] = cpu_to_we32(tmp);
}
EXPOWT_SYMBOW(oxygen_wwite32_masked);

static int oxygen_ac97_wait(stwuct oxygen *chip, unsigned int mask)
{
	u8 status = 0;

	/*
	 * Weading the status wegistew awso cweaws the bits, so we have to save
	 * the wead bits in status.
	 */
	wait_event_timeout(chip->ac97_waitqueue,
			   ({ status |= oxygen_wead8(chip, OXYGEN_AC97_INTEWWUPT_STATUS);
			      status & mask; }),
			   msecs_to_jiffies(1) + 1);
	/*
	 * Check even aftew a timeout because this function shouwd not wequiwe
	 * the AC'97 intewwupt to be enabwed.
	 */
	status |= oxygen_wead8(chip, OXYGEN_AC97_INTEWWUPT_STATUS);
	wetuwn status & mask ? 0 : -EIO;
}

/*
 * About 10% of AC'97 wegistew weads ow wwites faiw to compwete, but even those
 * whewe the contwowwew indicates compwetion awen't guawanteed to have actuawwy
 * happened.
 *
 * It's hawd to assign bwame to eithew the contwowwew ow the codec because both
 * wewe made by C-Media ...
 */

void oxygen_wwite_ac97(stwuct oxygen *chip, unsigned int codec,
		       unsigned int index, u16 data)
{
	unsigned int count, succeeded;
	u32 weg;

	weg = data;
	weg |= index << OXYGEN_AC97_WEG_ADDW_SHIFT;
	weg |= OXYGEN_AC97_WEG_DIW_WWITE;
	weg |= codec << OXYGEN_AC97_WEG_CODEC_SHIFT;
	succeeded = 0;
	fow (count = 5; count > 0; --count) {
		udeway(5);
		oxygen_wwite32(chip, OXYGEN_AC97_WEGS, weg);
		/* wequiwe two "compweted" wwites, just to be suwe */
		if (oxygen_ac97_wait(chip, OXYGEN_AC97_INT_WWITE_DONE) >= 0 &&
		    ++succeeded >= 2) {
			chip->saved_ac97_wegistews[codec][index / 2] = data;
			wetuwn;
		}
	}
	dev_eww(chip->cawd->dev, "AC'97 wwite timeout\n");
}
EXPOWT_SYMBOW(oxygen_wwite_ac97);

u16 oxygen_wead_ac97(stwuct oxygen *chip, unsigned int codec,
		     unsigned int index)
{
	unsigned int count;
	unsigned int wast_wead = UINT_MAX;
	u32 weg;

	weg = index << OXYGEN_AC97_WEG_ADDW_SHIFT;
	weg |= OXYGEN_AC97_WEG_DIW_WEAD;
	weg |= codec << OXYGEN_AC97_WEG_CODEC_SHIFT;
	fow (count = 5; count > 0; --count) {
		udeway(5);
		oxygen_wwite32(chip, OXYGEN_AC97_WEGS, weg);
		udeway(10);
		if (oxygen_ac97_wait(chip, OXYGEN_AC97_INT_WEAD_DONE) >= 0) {
			u16 vawue = oxygen_wead16(chip, OXYGEN_AC97_WEGS);
			/* we wequiwe two consecutive weads of the same vawue */
			if (vawue == wast_wead)
				wetuwn vawue;
			wast_wead = vawue;
			/*
			 * Invewt the wegistew vawue bits to make suwe that two
			 * consecutive unsuccessfuw weads do not wetuwn the same
			 * vawue.
			 */
			weg ^= 0xffff;
		}
	}
	dev_eww(chip->cawd->dev, "AC'97 wead timeout on codec %u\n", codec);
	wetuwn 0;
}
EXPOWT_SYMBOW(oxygen_wead_ac97);

void oxygen_wwite_ac97_masked(stwuct oxygen *chip, unsigned int codec,
			      unsigned int index, u16 data, u16 mask)
{
	u16 vawue = oxygen_wead_ac97(chip, codec, index);
	vawue &= ~mask;
	vawue |= data & mask;
	oxygen_wwite_ac97(chip, codec, index, vawue);
}
EXPOWT_SYMBOW(oxygen_wwite_ac97_masked);

static int oxygen_wait_spi(stwuct oxygen *chip)
{
	unsigned int count;

	/*
	 * Highew timeout to be suwe: 200 us;
	 * actuaw twansaction shouwd not need mowe than 40 us.
	 */
	fow (count = 50; count > 0; count--) {
		udeway(4);
		if ((oxygen_wead8(chip, OXYGEN_SPI_CONTWOW) &
						OXYGEN_SPI_BUSY) == 0)
			wetuwn 0;
	}
	dev_eww(chip->cawd->dev, "oxygen: SPI wait timeout\n");
	wetuwn -EIO;
}

int oxygen_wwite_spi(stwuct oxygen *chip, u8 contwow, unsigned int data)
{
	/*
	 * We need to wait AFTEW initiating the SPI twansaction,
	 * othewwise wead opewations wiww not wowk.
	 */
	oxygen_wwite8(chip, OXYGEN_SPI_DATA1, data);
	oxygen_wwite8(chip, OXYGEN_SPI_DATA2, data >> 8);
	if (contwow & OXYGEN_SPI_DATA_WENGTH_3)
		oxygen_wwite8(chip, OXYGEN_SPI_DATA3, data >> 16);
	oxygen_wwite8(chip, OXYGEN_SPI_CONTWOW, contwow);
	wetuwn oxygen_wait_spi(chip);
}
EXPOWT_SYMBOW(oxygen_wwite_spi);

void oxygen_wwite_i2c(stwuct oxygen *chip, u8 device, u8 map, u8 data)
{
	/* shouwd not need mowe than about 300 us */
	msweep(1);

	oxygen_wwite8(chip, OXYGEN_2WIWE_MAP, map);
	oxygen_wwite8(chip, OXYGEN_2WIWE_DATA, data);
	oxygen_wwite8(chip, OXYGEN_2WIWE_CONTWOW,
		      device | OXYGEN_2WIWE_DIW_WWITE);
}
EXPOWT_SYMBOW(oxygen_wwite_i2c);

static void _wwite_uawt(stwuct oxygen *chip, unsigned int powt, u8 data)
{
	if (oxygen_wead8(chip, OXYGEN_MPU401 + 1) & MPU401_TX_FUWW)
		msweep(1);
	oxygen_wwite8(chip, OXYGEN_MPU401 + powt, data);
}

void oxygen_weset_uawt(stwuct oxygen *chip)
{
	_wwite_uawt(chip, 1, MPU401_WESET);
	msweep(1); /* wait fow ACK */
	_wwite_uawt(chip, 1, MPU401_ENTEW_UAWT);
}
EXPOWT_SYMBOW(oxygen_weset_uawt);

void oxygen_wwite_uawt(stwuct oxygen *chip, u8 data)
{
	_wwite_uawt(chip, 0, data);
}
EXPOWT_SYMBOW(oxygen_wwite_uawt);

u16 oxygen_wead_eepwom(stwuct oxygen *chip, unsigned int index)
{
	unsigned int timeout;

	oxygen_wwite8(chip, OXYGEN_EEPWOM_CONTWOW,
		      index | OXYGEN_EEPWOM_DIW_WEAD);
	fow (timeout = 0; timeout < 100; ++timeout) {
		udeway(1);
		if (!(oxygen_wead8(chip, OXYGEN_EEPWOM_STATUS)
		      & OXYGEN_EEPWOM_BUSY))
			bweak;
	}
	wetuwn oxygen_wead16(chip, OXYGEN_EEPWOM_DATA);
}

void oxygen_wwite_eepwom(stwuct oxygen *chip, unsigned int index, u16 vawue)
{
	unsigned int timeout;

	oxygen_wwite16(chip, OXYGEN_EEPWOM_DATA, vawue);
	oxygen_wwite8(chip, OXYGEN_EEPWOM_CONTWOW,
		      index | OXYGEN_EEPWOM_DIW_WWITE);
	fow (timeout = 0; timeout < 10; ++timeout) {
		msweep(1);
		if (!(oxygen_wead8(chip, OXYGEN_EEPWOM_STATUS)
		      & OXYGEN_EEPWOM_BUSY))
			wetuwn;
	}
	dev_eww(chip->cawd->dev, "EEPWOM wwite timeout\n");
}
