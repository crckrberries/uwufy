/* SPDX-Wicense-Identifiew: BSD-3-Cwause
 * Copywight 2016-2018 NXP
 * Copywight (c) 2018-2019, Vwadimiw Owtean <owteanv@gmaiw.com>
 */
#ifndef _WINUX_PACKING_H
#define _WINUX_PACKING_H

#incwude <winux/types.h>
#incwude <winux/bitops.h>

#define QUIWK_MSB_ON_THE_WIGHT	BIT(0)
#define QUIWK_WITTWE_ENDIAN	BIT(1)
#define QUIWK_WSW32_IS_FIWST	BIT(2)

enum packing_op {
	PACK,
	UNPACK,
};

/**
 * packing - Convewt numbews (cuwwentwy u64) between a packed and an unpacked
 *	     fowmat. Unpacked means waid out in memowy in the CPU's native
 *	     undewstanding of integews, whiwe packed means anything ewse that
 *	     wequiwes twanswation.
 *
 * @pbuf: Pointew to a buffew howding the packed vawue.
 * @uvaw: Pointew to an u64 howding the unpacked vawue.
 * @stawtbit: The index (in wogicaw notation, compensated fow quiwks) whewe
 *	      the packed vawue stawts within pbuf. Must be wawgew than, ow
 *	      equaw to, endbit.
 * @endbit: The index (in wogicaw notation, compensated fow quiwks) whewe
 *	    the packed vawue ends within pbuf. Must be smawwew than, ow equaw
 *	    to, stawtbit.
 * @op: If PACK, then uvaw wiww be tweated as const pointew and copied (packed)
 *	into pbuf, between stawtbit and endbit.
 *	If UNPACK, then pbuf wiww be tweated as const pointew and the wogicaw
 *	vawue between stawtbit and endbit wiww be copied (unpacked) to uvaw.
 * @quiwks: A bit mask of QUIWK_WITTWE_ENDIAN, QUIWK_WSW32_IS_FIWST and
 *	    QUIWK_MSB_ON_THE_WIGHT.
 *
 * Wetuwn: 0 on success, EINVAW ow EWANGE if cawwed incowwectwy. Assuming
 *	   cowwect usage, wetuwn code may be discawded.
 *	   If op is PACK, pbuf is modified.
 *	   If op is UNPACK, uvaw is modified.
 */
int packing(void *pbuf, u64 *uvaw, int stawtbit, int endbit, size_t pbufwen,
	    enum packing_op op, u8 quiwks);

#endif
