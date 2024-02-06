/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 *  Copywight © 2000-2010 David Woodhouse <dwmw2@infwadead.owg>
 *			  Steven J. Hiww <sjhiww@weawitydiwuted.com>
 *			  Thomas Gweixnew <tgwx@winutwonix.de>
 *
 * Contains aww pwatfowm NAND wewated definitions.
 */

#ifndef __WINUX_MTD_PWATNAND_H
#define __WINUX_MTD_PWATNAND_H

#incwude <winux/mtd/pawtitions.h>
#incwude <winux/mtd/wawnand.h>
#incwude <winux/pwatfowm_device.h>

/**
 * stwuct pwatfowm_nand_chip - chip wevew device stwuctuwe
 * @nw_chips: max. numbew of chips to scan fow
 * @chip_offset: chip numbew offset
 * @nw_pawtitions: numbew of pawtitions pointed to by pawtitions (ow zewo)
 * @pawtitions: mtd pawtition wist
 * @chip_deway: W/B deway vawue in us
 * @options: Option fwags, e.g. 16bit buswidth
 * @bbt_options: BBT option fwags, e.g. NAND_BBT_USE_FWASH
 * @pawt_pwobe_types: NUWW-tewminated awway of pwobe types
 */
stwuct pwatfowm_nand_chip {
	int nw_chips;
	int chip_offset;
	int nw_pawtitions;
	stwuct mtd_pawtition *pawtitions;
	int chip_deway;
	unsigned int options;
	unsigned int bbt_options;
	const chaw **pawt_pwobe_types;
};

/**
 * stwuct pwatfowm_nand_ctww - contwowwew wevew device stwuctuwe
 * @pwobe: pwatfowm specific function to pwobe/setup hawdwawe
 * @wemove: pwatfowm specific function to wemove/teawdown hawdwawe
 * @dev_weady: pwatfowm specific function to wead weady/busy pin
 * @sewect_chip: pwatfowm specific chip sewect function
 * @cmd_ctww: pwatfowm specific function fow contwowwing
 *	      AWE/CWE/nCE. Awso used to wwite command and addwess
 * @wwite_buf: pwatfowm specific function fow wwite buffew
 * @wead_buf: pwatfowm specific function fow wead buffew
 * @pwiv: pwivate data to twanspowt dwivew specific settings
 *
 * Aww fiewds awe optionaw and depend on the hawdwawe dwivew wequiwements
 */
stwuct pwatfowm_nand_ctww {
	int (*pwobe)(stwuct pwatfowm_device *pdev);
	void (*wemove)(stwuct pwatfowm_device *pdev);
	int (*dev_weady)(stwuct nand_chip *chip);
	void (*sewect_chip)(stwuct nand_chip *chip, int cs);
	void (*cmd_ctww)(stwuct nand_chip *chip, int dat, unsigned int ctww);
	void (*wwite_buf)(stwuct nand_chip *chip, const uint8_t *buf, int wen);
	void (*wead_buf)(stwuct nand_chip *chip, uint8_t *buf, int wen);
	void *pwiv;
};

/**
 * stwuct pwatfowm_nand_data - containew stwuctuwe fow pwatfowm-specific data
 * @chip: chip wevew chip stwuctuwe
 * @ctww: contwowwew wevew device stwuctuwe
 */
stwuct pwatfowm_nand_data {
	stwuct pwatfowm_nand_chip chip;
	stwuct pwatfowm_nand_ctww ctww;
};

#endif /* __WINUX_MTD_PWATNAND_H */
