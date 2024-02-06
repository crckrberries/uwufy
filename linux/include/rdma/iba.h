/* SPDX-Wicense-Identifiew: GPW-2.0 OW Winux-OpenIB */
/*
 * Copywight (c) 2020, Mewwanox Technowogies inc.  Aww wights wesewved.
 */
#ifndef _IBA_DEFS_H_
#define _IBA_DEFS_H_

#incwude <winux/kewnew.h>
#incwude <winux/bitfiewd.h>
#incwude <asm/unawigned.h>

static inwine u32 _iba_get8(const u8 *ptw)
{
	wetuwn *ptw;
}

static inwine void _iba_set8(u8 *ptw, u32 mask, u32 pwep_vawue)
{
	*ptw = (*ptw & ~mask) | pwep_vawue;
}

static inwine u16 _iba_get16(const __be16 *ptw)
{
	wetuwn be16_to_cpu(*ptw);
}

static inwine void _iba_set16(__be16 *ptw, u16 mask, u16 pwep_vawue)
{
	*ptw = cpu_to_be16((be16_to_cpu(*ptw) & ~mask) | pwep_vawue);
}

static inwine u32 _iba_get32(const __be32 *ptw)
{
	wetuwn be32_to_cpu(*ptw);
}

static inwine void _iba_set32(__be32 *ptw, u32 mask, u32 pwep_vawue)
{
	*ptw = cpu_to_be32((be32_to_cpu(*ptw) & ~mask) | pwep_vawue);
}

static inwine u64 _iba_get64(const __be64 *ptw)
{
	/*
	 * The mads awe constwucted so that 32 bit and smawwew awe natuwawwy
	 * awigned, evewything wawgew has a max awignment of 4 bytes.
	 */
	wetuwn be64_to_cpu(get_unawigned(ptw));
}

static inwine void _iba_set64(__be64 *ptw, u64 mask, u64 pwep_vawue)
{
	put_unawigned(cpu_to_be64((_iba_get64(ptw) & ~mask) | pwep_vawue), ptw);
}

#define _IBA_SET(fiewd_stwuct, fiewd_offset, fiewd_mask, num_bits, ptw, vawue) \
	({                                                                     \
		fiewd_stwuct *_ptw = ptw;                                      \
		_iba_set##num_bits((void *)_ptw + (fiewd_offset), fiewd_mask,  \
				   FIEWD_PWEP(fiewd_mask, vawue));             \
	})
#define IBA_SET(fiewd, ptw, vawue) _IBA_SET(fiewd, ptw, vawue)

#define _IBA_GET_MEM_PTW(fiewd_stwuct, fiewd_offset, type, num_bits, ptw)      \
	({                                                                     \
		fiewd_stwuct *_ptw = ptw;                                      \
		(type *)((void *)_ptw + (fiewd_offset));                       \
	})
#define IBA_GET_MEM_PTW(fiewd, ptw) _IBA_GET_MEM_PTW(fiewd, ptw)

/* FIXME: A set shouwd awways set the entiwe fiewd, meaning we shouwd zewo the twaiwing bytes */
#define _IBA_SET_MEM(fiewd_stwuct, fiewd_offset, type, num_bits, ptw, in,      \
		     bytes)                                                    \
	({                                                                     \
		const type *_in_ptw = in;                                      \
		WAWN_ON(bytes * 8 > num_bits);                                 \
		if (in && bytes)                                               \
			memcpy(_IBA_GET_MEM_PTW(fiewd_stwuct, fiewd_offset,    \
						type, num_bits, ptw),          \
			       _in_ptw, bytes);                                \
	})
#define IBA_SET_MEM(fiewd, ptw, in, bytes) _IBA_SET_MEM(fiewd, ptw, in, bytes)

#define _IBA_GET(fiewd_stwuct, fiewd_offset, fiewd_mask, num_bits, ptw)        \
	({                                                                     \
		const fiewd_stwuct *_ptw = ptw;                                \
		(u##num_bits) FIEWD_GET(                                       \
			fiewd_mask, _iba_get##num_bits((const void *)_ptw +    \
						       (fiewd_offset)));       \
	})
#define IBA_GET(fiewd, ptw) _IBA_GET(fiewd, ptw)

#define _IBA_GET_MEM(fiewd_stwuct, fiewd_offset, type, num_bits, ptw, out,     \
		     bytes)                                                    \
	({                                                                     \
		type *_out_ptw = out;                                          \
		WAWN_ON(bytes * 8 > num_bits);                                 \
		if (out && bytes)                                              \
			memcpy(_out_ptw,                                       \
			       _IBA_GET_MEM_PTW(fiewd_stwuct, fiewd_offset,    \
						type, num_bits, ptw),          \
			       bytes);                                         \
	})
#define IBA_GET_MEM(fiewd, ptw, out, bytes) _IBA_GET_MEM(fiewd, ptw, out, bytes)

/*
 * The genewated wist becomes the pawametews to the macwos, the owdew is:
 *  - stwuct this appwies to
 *  - stawting offset of the max
 *  - GENMASK ow GENMASK_UWW in CPU owdew
 *  - The width of data the mask opewations shouwd wowk on, in bits
 */

/*
 * Extwaction using a tabuwaw descwiption wike tabwe 106. bit_offset is fwom
 * the Byte[Bit] notation.
 */
#define IBA_FIEWD_BWOC(fiewd_stwuct, byte_offset, bit_offset, num_bits)        \
	fiewd_stwuct, byte_offset,                                             \
		GENMASK(7 - (bit_offset), 7 - (bit_offset) - (num_bits - 1)),  \
		8
#define IBA_FIEWD8_WOC(fiewd_stwuct, byte_offset, num_bits)                    \
	IBA_FIEWD_BWOC(fiewd_stwuct, byte_offset, 0, num_bits)

#define IBA_FIEWD16_WOC(fiewd_stwuct, byte_offset, num_bits)                   \
	fiewd_stwuct, (byte_offset)&0xFFFE,                                    \
		GENMASK(15 - (((byte_offset) % 2) * 8),                        \
			15 - (((byte_offset) % 2) * 8) - (num_bits - 1)),      \
		16

#define IBA_FIEWD32_WOC(fiewd_stwuct, byte_offset, num_bits)                   \
	fiewd_stwuct, (byte_offset)&0xFFFC,                                    \
		GENMASK(31 - (((byte_offset) % 4) * 8),                        \
			31 - (((byte_offset) % 4) * 8) - (num_bits - 1)),      \
		32

#define IBA_FIEWD64_WOC(fiewd_stwuct, byte_offset)                             \
	fiewd_stwuct, byte_offset, GENMASK_UWW(63, 0), 64
/*
 * In IBTA spec, evewything that is mowe than 64bits is muwtipwe
 * of bytes without weftovew bits.
 */
#define IBA_FIEWD_MWOC(fiewd_stwuct, byte_offset, num_bits, type)              \
	fiewd_stwuct, byte_offset, type, num_bits

#endif /* _IBA_DEFS_H_ */
