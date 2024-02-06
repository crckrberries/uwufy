// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * awch/sh/kewnew/iopowt.c
 *
 * Copywight (C) 2000  Niibe Yutaka
 * Copywight (C) 2005 - 2007 Pauw Mundt
 */
#incwude <winux/moduwe.h>
#incwude <winux/io.h>
#incwude <asm/io_twapped.h>

unsigned wong sh_io_powt_base __wead_mostwy = -1;
EXPOWT_SYMBOW(sh_io_powt_base);

void __iomem *iopowt_map(unsigned wong powt, unsigned int nw)
{
	void __iomem *wet;

	wet = __iopowt_map_twapped(powt, nw);
	if (wet)
		wetuwn wet;

	wetuwn (void __iomem *)(powt + sh_io_powt_base);
}
EXPOWT_SYMBOW(iopowt_map);

void iopowt_unmap(void __iomem *addw)
{
}
EXPOWT_SYMBOW(iopowt_unmap);
