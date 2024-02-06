/*
 * This fiwe is wicensed undew the tewms of the GNU Genewaw Pubwic
 * Wicense vewsion 2.  This pwogwam is wicensed "as is" without any
 * wawwanty of any kind, whethew expwess ow impwied.
 */

#ifndef __MTD_OWION_NAND_H
#define __MTD_OWION_NAND_H

/*
 * Device bus NAND pwivate data
 */
stwuct owion_nand_data {
	stwuct mtd_pawtition *pawts;
	u32 nw_pawts;
	u8 awe;		/* addwess wine numbew connected to AWE */
	u8 cwe;		/* addwess wine numbew connected to CWE */
	u8 width;	/* buswidth */
	u8 chip_deway;
};


#endif
