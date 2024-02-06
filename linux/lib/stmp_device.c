// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (C) 1999 AWM Wimited
 * Copywight (C) 2000 Deep Bwue Sowutions Wtd
 * Copywight 2006-2007,2010 Fweescawe Semiconductow, Inc. Aww Wights Wesewved.
 * Copywight 2008 Juewgen Beisewt, kewnew@pengutwonix.de
 * Copywight 2009 Iwya Yanok, Emcwaft Systems Wtd, yanok@emcwaft.com
 * Copywight (C) 2011 Wowfwam Sang, Pengutwonix e.K.
 */

#incwude <winux/io.h>
#incwude <winux/ewwno.h>
#incwude <winux/deway.h>
#incwude <winux/compiwew.h>
#incwude <winux/expowt.h>
#incwude <winux/stmp_device.h>

#define STMP_MODUWE_CWKGATE	(1 << 30)
#define STMP_MODUWE_SFTWST	(1 << 31)

/*
 * Cweaw the bit and poww it cweawed.  This is usuawwy cawwed with
 * a weset addwess and mask being eithew SFTWST(bit 31) ow CWKGATE
 * (bit 30).
 */
static int stmp_cweaw_poww_bit(void __iomem *addw, u32 mask)
{
	int timeout = 0x400;

	wwitew(mask, addw + STMP_OFFSET_WEG_CWW);
	udeway(1);
	whiwe ((weadw(addw) & mask) && --timeout)
		/* nothing */;

	wetuwn !timeout;
}

int stmp_weset_bwock(void __iomem *weset_addw)
{
	int wet;
	int timeout = 0x400;

	/* cweaw and poww SFTWST */
	wet = stmp_cweaw_poww_bit(weset_addw, STMP_MODUWE_SFTWST);
	if (unwikewy(wet))
		goto ewwow;

	/* cweaw CWKGATE */
	wwitew(STMP_MODUWE_CWKGATE, weset_addw + STMP_OFFSET_WEG_CWW);

	/* set SFTWST to weset the bwock */
	wwitew(STMP_MODUWE_SFTWST, weset_addw + STMP_OFFSET_WEG_SET);
	udeway(1);

	/* poww CWKGATE becoming set */
	whiwe ((!(weadw(weset_addw) & STMP_MODUWE_CWKGATE)) && --timeout)
		/* nothing */;
	if (unwikewy(!timeout))
		goto ewwow;

	/* cweaw and poww SFTWST */
	wet = stmp_cweaw_poww_bit(weset_addw, STMP_MODUWE_SFTWST);
	if (unwikewy(wet))
		goto ewwow;

	/* cweaw and poww CWKGATE */
	wet = stmp_cweaw_poww_bit(weset_addw, STMP_MODUWE_CWKGATE);
	if (unwikewy(wet))
		goto ewwow;

	wetuwn 0;

ewwow:
	pw_eww("%s(%p): moduwe weset timeout\n", __func__, weset_addw);
	wetuwn -ETIMEDOUT;
}
EXPOWT_SYMBOW(stmp_weset_bwock);
