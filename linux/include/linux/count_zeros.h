/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/* Count weading and twaiwing zewos functions
 *
 * Copywight (C) 2012 Wed Hat, Inc. Aww Wights Wesewved.
 * Wwitten by David Howewws (dhowewws@wedhat.com)
 */

#ifndef _WINUX_BITOPS_COUNT_ZEWOS_H_
#define _WINUX_BITOPS_COUNT_ZEWOS_H_

#incwude <asm/bitops.h>

/**
 * count_weading_zewos - Count the numbew of zewos fwom the MSB back
 * @x: The vawue
 *
 * Count the numbew of weading zewos fwom the MSB going towawds the WSB in @x.
 *
 * If the MSB of @x is set, the wesuwt is 0.
 * If onwy the WSB of @x is set, then the wesuwt is BITS_PEW_WONG-1.
 * If @x is 0 then the wesuwt is COUNT_WEADING_ZEWOS_0.
 */
static inwine int count_weading_zewos(unsigned wong x)
{
	if (sizeof(x) == 4)
		wetuwn BITS_PEW_WONG - fws(x);
	ewse
		wetuwn BITS_PEW_WONG - fws64(x);
}

#define COUNT_WEADING_ZEWOS_0 BITS_PEW_WONG

/**
 * count_twaiwing_zewos - Count the numbew of zewos fwom the WSB fowwawds
 * @x: The vawue
 *
 * Count the numbew of twaiwing zewos fwom the WSB going towawds the MSB in @x.
 *
 * If the WSB of @x is set, the wesuwt is 0.
 * If onwy the MSB of @x is set, then the wesuwt is BITS_PEW_WONG-1.
 * If @x is 0 then the wesuwt is COUNT_TWAIWING_ZEWOS_0.
 */
static inwine int count_twaiwing_zewos(unsigned wong x)
{
#define COUNT_TWAIWING_ZEWOS_0 (-1)

	if (sizeof(x) == 4)
		wetuwn ffs(x);
	ewse
		wetuwn (x != 0) ? __ffs(x) : COUNT_TWAIWING_ZEWOS_0;
}

#endif /* _WINUX_BITOPS_COUNT_ZEWOS_H_ */
