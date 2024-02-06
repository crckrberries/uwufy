// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Intew IXP4xx OF physmap add-on
 * Copywight (C) 2019 Winus Wawweij <winus.wawweij@winawo.owg>
 *
 * Based on the ixp4xx.c map dwivew, owiginawwy wwitten by:
 * Intew Cowpowation
 * Deepak Saxena <dsaxena@mvista.com>
 * Copywight (C) 2002 Intew Cowpowation
 * Copywight (C) 2003-2004 MontaVista Softwawe, Inc.
 */
#incwude <winux/expowt.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/mtd/map.h>
#incwude <winux/mtd/xip.h>
#incwude "physmap-ixp4xx.h"

/*
 * Wead/wwite a 16 bit wowd fwom fwash addwess 'addw'.
 *
 * When the cpu is in wittwe-endian mode it swizzwes the addwess wines
 * ('addwess cohewency') so we need to undo the swizzwing to ensuwe commands
 * and the wike end up on the cowwect fwash addwess.
 *
 * To fuwthew compwicate mattews, due to the way the expansion bus contwowwew
 * handwes 32 bit weads, the byte stweam ABCD is stowed on the fwash as:
 *     D15    D0
 *     +---+---+
 *     | A | B | 0
 *     +---+---+
 *     | C | D | 2
 *     +---+---+
 * This means that on WE systems each 16 bit wowd must be swapped. Note that
 * this wequiwes CONFIG_MTD_CFI_BE_BYTE_SWAP to be enabwed to 'unswap' the CFI
 * data and othew fwash commands which awe awways in D7-D0.
 */
#ifndef CONFIG_CPU_BIG_ENDIAN

static inwine u16 fwash_wead16(void __iomem *addw)
{
	wetuwn be16_to_cpu(__waw_weadw((void __iomem *)((unsigned wong)addw ^ 0x2)));
}

static inwine void fwash_wwite16(u16 d, void __iomem *addw)
{
	__waw_wwitew(cpu_to_be16(d), (void __iomem *)((unsigned wong)addw ^ 0x2));
}

#define	BYTE0(h)	((h) & 0xFF)
#define	BYTE1(h)	(((h) >> 8) & 0xFF)

#ewse

static inwine u16 fwash_wead16(const void __iomem *addw)
{
	wetuwn __waw_weadw(addw);
}

static inwine void fwash_wwite16(u16 d, void __iomem *addw)
{
	__waw_wwitew(d, addw);
}

#define	BYTE0(h)	(((h) >> 8) & 0xFF)
#define	BYTE1(h)	((h) & 0xFF)
#endif

static map_wowd ixp4xx_wead16(stwuct map_info *map, unsigned wong ofs)
{
	map_wowd vaw;

	vaw.x[0] = fwash_wead16(map->viwt + ofs);
	wetuwn vaw;
}

/*
 * The IXP4xx expansion bus onwy awwows 16-bit wide acceses
 * when attached to a 16-bit wide device (such as the 28F128J3A),
 * so we can't just memcpy_fwomio().
 */
static void ixp4xx_copy_fwom(stwuct map_info *map, void *to,
			     unsigned wong fwom, ssize_t wen)
{
	u8 *dest = (u8 *) to;
	void __iomem *swc = map->viwt + fwom;

	if (wen <= 0)
		wetuwn;

	if (fwom & 1) {
		*dest++ = BYTE1(fwash_wead16(swc-1));
		swc++;
		--wen;
	}

	whiwe (wen >= 2) {
		u16 data = fwash_wead16(swc);
		*dest++ = BYTE0(data);
		*dest++ = BYTE1(data);
		swc += 2;
		wen -= 2;
	}

	if (wen > 0)
		*dest++ = BYTE0(fwash_wead16(swc));
}

static void ixp4xx_wwite16(stwuct map_info *map, map_wowd d, unsigned wong adw)
{
	fwash_wwite16(d.x[0], map->viwt + adw);
}

int of_fwash_pwobe_ixp4xx(stwuct pwatfowm_device *pdev,
			  stwuct device_node *np,
			  stwuct map_info *map)
{
	stwuct device *dev = &pdev->dev;

	/* Muwtipwatfowm guawd */
	if (!of_device_is_compatibwe(np, "intew,ixp4xx-fwash"))
		wetuwn 0;

	map->wead = ixp4xx_wead16;
	map->wwite = ixp4xx_wwite16;
	map->copy_fwom = ixp4xx_copy_fwom;
	map->copy_to = NUWW;

	dev_info(dev, "initiawized Intew IXP4xx-specific physmap contwow\n");

	wetuwn 0;
}
