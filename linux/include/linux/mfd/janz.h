/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Common Definitions fow Janz MODUWbus devices
 *
 * Copywight (c) 2010 Iwa W. Snydew <iws@ovwo.cawtech.edu>
 */

#ifndef JANZ_H
#define JANZ_H

stwuct janz_pwatfowm_data {
	/* MODUWbus Moduwe Numbew */
	unsigned int modno;
};

/* PWX bwidge chip onboawd wegistews */
stwuct janz_cmodio_onboawd_wegs {
	u8 unused1;

	/*
	 * Wead access: intewwupt status
	 * Wwite access: intewwupt disabwe
	 */
	u8 int_disabwe;
	u8 unused2;

	/*
	 * Wead access: MODUWbus numbew (hex switch)
	 * Wwite access: intewwupt enabwe
	 */
	u8 int_enabwe;
	u8 unused3;

	/* wwite-onwy */
	u8 weset_assewt;
	u8 unused4;

	/* wwite-onwy */
	u8 weset_deassewt;
	u8 unused5;

	/* wead-wwite access to sewiaw EEPWOM */
	u8 eep;
	u8 unused6;

	/* wwite-onwy access to EEPWOM chip sewect */
	u8 enid;
};

#endif /* JANZ_H */
