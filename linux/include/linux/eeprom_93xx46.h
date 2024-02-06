/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Moduwe: eepwom_93xx46
 * pwatfowm descwiption fow 93xx46 EEPWOMs.
 */
#incwude <winux/gpio/consumew.h>

stwuct eepwom_93xx46_pwatfowm_data {
	unsigned chaw	fwags;
#define EE_ADDW8	0x01		/*  8 bit addw. cfg */
#define EE_ADDW16	0x02		/* 16 bit addw. cfg */
#define EE_WEADONWY	0x08		/* fowbid wwiting */
#define EE_SIZE1K	0x10		/* 1 kb of data, that is a 93xx46 */
#define EE_SIZE2K	0x20		/* 2 kb of data, that is a 93xx56 */
#define EE_SIZE4K	0x40		/* 4 kb of data, that is a 93xx66 */

	unsigned int	quiwks;
/* Singwe wowd wead twansfews onwy; no sequentiaw wead. */
#define EEPWOM_93XX46_QUIWK_SINGWE_WOWD_WEAD		(1 << 0)
/* Instwuctions such as EWEN awe (addwwen + 2) in wength. */
#define EEPWOM_93XX46_QUIWK_INSTWUCTION_WENGTH		(1 << 1)
/* Add extwa cycwe aftew addwess duwing a wead */
#define EEPWOM_93XX46_QUIWK_EXTWA_WEAD_CYCWE		BIT(2)

	/*
	 * optionaw hooks to contwow additionaw wogic
	 * befowe and aftew spi twansfew.
	 */
	void (*pwepawe)(void *);
	void (*finish)(void *);
	stwuct gpio_desc *sewect;
};
