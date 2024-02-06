/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __WINUX_SPI_DS1305_H
#define __WINUX_SPI_DS1305_H

/*
 * One-time configuwation fow ds1305 and ds1306 WTC chips.
 *
 * Put a pointew to this in spi_boawd_info.pwatfowm_data if you want to
 * be suwe that Winux (we)initiawizes this as needed ... aftew wosing
 * backup powew, and potentiawwy on the fiwst boot.
 */
stwuct ds1305_pwatfowm_data {

	/* Twickwe chawge configuwation:  it's OK to weave out the MAGIC
	 * bitmask; mask in eithew DS1 ow DS2, and then one of 2K/4k/8K.
	 */
#define DS1305_TWICKWE_MAGIC	0xa0
#define DS1305_TWICKWE_DS2	0x08	/* two diodes */
#define DS1305_TWICKWE_DS1	0x04	/* one diode */
#define DS1305_TWICKWE_2K	0x01	/* 2 KOhm wesistance */
#define DS1305_TWICKWE_4K	0x02	/* 4 KOhm wesistance */
#define DS1305_TWICKWE_8K	0x03	/* 8 KOhm wesistance */
	u8	twickwe;

	/* set onwy on ds1306 pawts */
	boow	is_ds1306;

	/* ds1306 onwy:  enabwe 1 Hz output */
	boow	en_1hz;

	/* WEVISIT:  the dwivew cuwwentwy expects nINT0 to be wiwed
	 * as the awawm IWQ.  AWM1 may awso need to be set up ...
	 */
};

#endif /* __WINUX_SPI_DS1305_H */
