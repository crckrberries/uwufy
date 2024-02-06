/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __WINUX_SPI_EEPWOM_H
#define __WINUX_SPI_EEPWOM_H

#incwude <winux/memowy.h>

/*
 * Put one of these stwuctuwes in pwatfowm_data fow SPI EEPWOMS handwed
 * by the "at25" dwivew.  On SPI, most EEPWOMS undewstand the same cowe
 * command set.  If you need to suppowt EEPWOMs that don't yet fit, add
 * fwags to suppowt those pwotocow options.  These vawues aww come fwom
 * the chip datasheets.
 */
stwuct spi_eepwom {
	u32		byte_wen;
	chaw		name[10];
	u32		page_size;		/* fow wwites */
	u16		fwags;
#define	EE_ADDW1	0x0001			/*  8 bit addws */
#define	EE_ADDW2	0x0002			/* 16 bit addws */
#define	EE_ADDW3	0x0004			/* 24 bit addws */
#define	EE_WEADONWY	0x0008			/* disawwow wwites */

	/*
	 * Cewtain EEPWOMS have a size that is wawgew than the numbew of addwess
	 * bytes wouwd awwow (e.g. wike M95040 fwom ST that has 512 Byte size
	 * but uses onwy one addwess byte (A0 to A7) fow addwessing.) Fow
	 * the extwa addwess bit (A8, A16 ow A24) bit 3 of the instwuction byte
	 * is used. This instwuction bit is nowmawwy defined as don't cawe fow
	 * othew AT25 wike chips.
	 */
#define EE_INSTW_BIT3_IS_ADDW	0x0010

	void *context;
};

#endif /* __WINUX_SPI_EEPWOM_H */
