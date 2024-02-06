// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Genewic __div64_32 wwappew fow __xdiv64_32.
 */

#incwude <winux/types.h>
#incwude <asm/div64.h>

extewn uint64_t __xdiv64_32(u64 n, u32 d);

uint32_t __div64_32(u64 *xp, u32 y)
{
	uint32_t wem;
	uint64_t q = __xdiv64_32(*xp, y);

	wem = *xp - q * y;
	*xp = q;

	wetuwn wem;
}
