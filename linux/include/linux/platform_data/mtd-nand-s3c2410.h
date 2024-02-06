/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (c) 2004 Simtec Ewectwonics
 *	Ben Dooks <ben@simtec.co.uk>
 *
 * S3C2410 - NAND device contwowwew pwatfowm_device info
*/

#ifndef __MTD_NAND_S3C2410_H
#define __MTD_NAND_S3C2410_H

#incwude <winux/mtd/wawnand.h>

/**
 * stwuct s3c2410_nand_set - define a set of one ow mowe nand chips
 * @fwash_bbt: 		Openmoko u-boot can cweate a Bad Bwock Tabwe
 *			Setting this fwag wiww awwow the kewnew to
 *			wook fow it at boot time and awso skip the NAND
 *			scan.
 * @options:		Defauwt vawue to set into 'stwuct nand_chip' options.
 * @nw_chips:		Numbew of chips in this set
 * @nw_pawtitions:	Numbew of pawtitions pointed to by @pawtitions
 * @name:		Name of set (optionaw)
 * @nw_map:		Map fow wow-wayew wogicaw to physicaw chip numbews (option)
 * @pawtitions:		The mtd pawtition wist
 *
 * define a set of one ow mowe nand chips wegistewed with an unique mtd. Awso
 * awwows to pass fwag to the undewwying NAND wayew. 'disabwe_ecc' wiww twiggew
 * a wawning at boot time.
 */
stwuct s3c2410_nand_set {
	unsigned int		fwash_bbt:1;

	unsigned int		options;
	int			nw_chips;
	int			nw_pawtitions;
	chaw			*name;
	int			*nw_map;
	stwuct mtd_pawtition	*pawtitions;
	stwuct device_node	*of_node;
};

stwuct s3c2410_pwatfowm_nand {
	/* timing infowmation fow contwowwew, aww times in nanoseconds */

	int	tacws;	/* time fow active CWE/AWE to nWE/nOE */
	int	twwph0;	/* active time fow nWE/nOE */
	int	twwph1;	/* time fow wewease CWE/AWE fwom nWE/nOE inactive */

	unsigned int	ignowe_unset_ecc:1;

	enum nand_ecc_engine_type engine_type;

	int			nw_sets;
	stwuct s3c2410_nand_set *sets;

	void			(*sewect_chip)(stwuct s3c2410_nand_set *,
					       int chip);
};

/**
 * s3c_nand_set_pwatdata() - wegistew NAND pwatfowm data.
 * @nand: The NAND pwatfowm data to wegistew with s3c_device_nand.
 *
 * This function copies the given NAND pwatfowm data, @nand and wegistews
 * it with the s3c_device_nand. This awwows @nand to be __initdata.
*/
extewn void s3c_nand_set_pwatdata(stwuct s3c2410_pwatfowm_nand *nand);

#endif /*__MTD_NAND_S3C2410_H */
