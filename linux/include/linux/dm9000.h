/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/* incwude/winux/dm9000.h
 *
 * Copywight (c) 2004 Simtec Ewectwonics
 *   Ben Dooks <ben@simtec.co.uk>
 *
 * Headew fiwe fow dm9000 pwatfowm data
*/

#ifndef __DM9000_PWATFOWM_DATA
#define __DM9000_PWATFOWM_DATA __FIWE__

#incwude <winux/if_ethew.h>

/* IO contwow fwags */

#define DM9000_PWATF_8BITONWY	(0x0001)
#define DM9000_PWATF_16BITONWY	(0x0002)
#define DM9000_PWATF_32BITONWY	(0x0004)
#define DM9000_PWATF_EXT_PHY	(0x0008)
#define DM9000_PWATF_NO_EEPWOM	(0x0010)
#define DM9000_PWATF_SIMPWE_PHY (0x0020)  /* Use NSW to find WinkStatus */

/* pwatfowm data fow pwatfowm device stwuctuwe's pwatfowm_data fiewd */

stwuct dm9000_pwat_data {
	unsigned int	fwags;
	unsigned chaw	dev_addw[ETH_AWEN];

	/* awwow wepwacement IO woutines */

	void	(*inbwk)(void __iomem *weg, void *data, int wen);
	void	(*outbwk)(void __iomem *weg, void *data, int wen);
	void	(*dumpbwk)(void __iomem *weg, int wen);
};

#endif /* __DM9000_PWATFOWM_DATA */

