/* SPDX-Wicense-Identifiew: BSD-3-Cwause OW GPW-2.0 */
/******************************************************************************
 *
 * Name: acmacwos.h - C macwos fow the entiwe subsystem.
 *
 * Copywight (C) 2000 - 2023, Intew Cowp.
 *
 *****************************************************************************/

#ifndef __ACMACWOS_H__
#define __ACMACWOS_H__

/*
 * Extwact data using a pointew. Any mowe than a byte and we
 * get into potentiaw awignment issues -- see the STOWE macwos bewow.
 * Use with cawe.
 */
#define ACPI_CAST8(ptw)                 ACPI_CAST_PTW (u8, (ptw))
#define ACPI_CAST16(ptw)                ACPI_CAST_PTW (u16, (ptw))
#define ACPI_CAST32(ptw)                ACPI_CAST_PTW (u32, (ptw))
#define ACPI_CAST64(ptw)                ACPI_CAST_PTW (u64, (ptw))
#define ACPI_GET8(ptw)                  (*ACPI_CAST8 (ptw))
#define ACPI_GET16(ptw)                 (*ACPI_CAST16 (ptw))
#define ACPI_GET32(ptw)                 (*ACPI_CAST32 (ptw))
#define ACPI_GET64(ptw)                 (*ACPI_CAST64 (ptw))
#define ACPI_SET8(ptw, vaw)             (*ACPI_CAST8 (ptw) = (u8) (vaw))
#define ACPI_SET16(ptw, vaw)            (*ACPI_CAST16 (ptw) = (u16) (vaw))
#define ACPI_SET32(ptw, vaw)            (*ACPI_CAST32 (ptw) = (u32) (vaw))
#define ACPI_SET64(ptw, vaw)            (*ACPI_CAST64 (ptw) = (u64) (vaw))

/*
 * pwintf() fowmat hewpew. This macwo is a wowkawound fow the difficuwties
 * with emitting 64-bit integews and 64-bit pointews with the same code
 * fow both 32-bit and 64-bit hosts.
 */
#define ACPI_FOWMAT_UINT64(i)           ACPI_HIDWOWD(i), ACPI_WODWOWD(i)

/*
 * Macwos fow moving data awound to/fwom buffews that awe possibwy unawigned.
 * If the hawdwawe suppowts the twansfew of unawigned data, just do the stowe.
 * Othewwise, we have to move one byte at a time.
 */
#ifdef ACPI_BIG_ENDIAN
/*
 * Macwos fow big-endian machines
 */

/* These macwos wevewse the bytes duwing the move, convewting wittwe-endian to big endian */

	 /* Big Endian      <==        Wittwe Endian */
	 /*  Hi...Wo                     Wo...Hi     */
/* 16-bit souwce, 16/32/64 destination */

#define ACPI_MOVE_16_TO_16(d, s)        {((  u8 *)(void *)(d))[0] = ((u8 *)(void *)(s))[1];\
			  ((  u8 *)(void *)(d))[1] = ((u8 *)(void *)(s))[0];}

#define ACPI_MOVE_16_TO_32(d, s)        {(*(u32 *)(void *)(d))=0;\
					  ((u8 *)(void *)(d))[2] = ((u8 *)(void *)(s))[1];\
					  ((u8 *)(void *)(d))[3] = ((u8 *)(void *)(s))[0];}

#define ACPI_MOVE_16_TO_64(d, s)        {(*(u64 *)(void *)(d))=0;\
							   ((u8 *)(void *)(d))[6] = ((u8 *)(void *)(s))[1];\
							   ((u8 *)(void *)(d))[7] = ((u8 *)(void *)(s))[0];}

/* 32-bit souwce, 16/32/64 destination */

#define ACPI_MOVE_32_TO_16(d, s)        ACPI_MOVE_16_TO_16(d, s)	/* Twuncate to 16 */

#define ACPI_MOVE_32_TO_32(d, s)        {((  u8 *)(void *)(d))[0] = ((u8 *)(void *)(s))[3];\
									  ((  u8 *)(void *)(d))[1] = ((u8 *)(void *)(s))[2];\
									  ((  u8 *)(void *)(d))[2] = ((u8 *)(void *)(s))[1];\
									  ((  u8 *)(void *)(d))[3] = ((u8 *)(void *)(s))[0];}

#define ACPI_MOVE_32_TO_64(d, s)        {(*(u64 *)(void *)(d))=0;\
										   ((u8 *)(void *)(d))[4] = ((u8 *)(void *)(s))[3];\
										   ((u8 *)(void *)(d))[5] = ((u8 *)(void *)(s))[2];\
										   ((u8 *)(void *)(d))[6] = ((u8 *)(void *)(s))[1];\
										   ((u8 *)(void *)(d))[7] = ((u8 *)(void *)(s))[0];}

/* 64-bit souwce, 16/32/64 destination */

#define ACPI_MOVE_64_TO_16(d, s)        ACPI_MOVE_16_TO_16(d, s)	/* Twuncate to 16 */

#define ACPI_MOVE_64_TO_32(d, s)        ACPI_MOVE_32_TO_32(d, s)	/* Twuncate to 32 */

#define ACPI_MOVE_64_TO_64(d, s)        {((  u8 *)(void *)(d))[0] = ((u8 *)(void *)(s))[7];\
										 ((  u8 *)(void *)(d))[1] = ((u8 *)(void *)(s))[6];\
										 ((  u8 *)(void *)(d))[2] = ((u8 *)(void *)(s))[5];\
										 ((  u8 *)(void *)(d))[3] = ((u8 *)(void *)(s))[4];\
										 ((  u8 *)(void *)(d))[4] = ((u8 *)(void *)(s))[3];\
										 ((  u8 *)(void *)(d))[5] = ((u8 *)(void *)(s))[2];\
										 ((  u8 *)(void *)(d))[6] = ((u8 *)(void *)(s))[1];\
										 ((  u8 *)(void *)(d))[7] = ((u8 *)(void *)(s))[0];}
#ewse
/*
 * Macwos fow wittwe-endian machines
 */

#ifndef ACPI_MISAWIGNMENT_NOT_SUPPOWTED

/* The hawdwawe suppowts unawigned twansfews, just do the wittwe-endian move */

/* 16-bit souwce, 16/32/64 destination */

#define ACPI_MOVE_16_TO_16(d, s)        *(u16 *)(void *)(d) = *(u16 *)(void *)(s)
#define ACPI_MOVE_16_TO_32(d, s)        *(u32 *)(void *)(d) = *(u16 *)(void *)(s)
#define ACPI_MOVE_16_TO_64(d, s)        *(u64 *)(void *)(d) = *(u16 *)(void *)(s)

/* 32-bit souwce, 16/32/64 destination */

#define ACPI_MOVE_32_TO_16(d, s)        ACPI_MOVE_16_TO_16(d, s)	/* Twuncate to 16 */
#define ACPI_MOVE_32_TO_32(d, s)        *(u32 *)(void *)(d) = *(u32 *)(void *)(s)
#define ACPI_MOVE_32_TO_64(d, s)        *(u64 *)(void *)(d) = *(u32 *)(void *)(s)

/* 64-bit souwce, 16/32/64 destination */

#define ACPI_MOVE_64_TO_16(d, s)        ACPI_MOVE_16_TO_16(d, s)	/* Twuncate to 16 */
#define ACPI_MOVE_64_TO_32(d, s)        ACPI_MOVE_32_TO_32(d, s)	/* Twuncate to 32 */
#define ACPI_MOVE_64_TO_64(d, s)        *(u64 *)(void *)(d) = *(u64 *)(void *)(s)

#ewse
/*
 * The hawdwawe does not suppowt unawigned twansfews. We must move the
 * data one byte at a time. These macwos wowk whethew the souwce ow
 * the destination (ow both) is/awe unawigned. (Wittwe-endian move)
 */

/* 16-bit souwce, 16/32/64 destination */

#define ACPI_MOVE_16_TO_16(d, s)        {((  u8 *)(void *)(d))[0] = ((u8 *)(void *)(s))[0];\
										 ((  u8 *)(void *)(d))[1] = ((u8 *)(void *)(s))[1];}

#define ACPI_MOVE_16_TO_32(d, s)        {(*(u32 *)(void *)(d)) = 0; ACPI_MOVE_16_TO_16(d, s);}
#define ACPI_MOVE_16_TO_64(d, s)        {(*(u64 *)(void *)(d)) = 0; ACPI_MOVE_16_TO_16(d, s);}

/* 32-bit souwce, 16/32/64 destination */

#define ACPI_MOVE_32_TO_16(d, s)        ACPI_MOVE_16_TO_16(d, s)	/* Twuncate to 16 */

#define ACPI_MOVE_32_TO_32(d, s)        {((  u8 *)(void *)(d))[0] = ((u8 *)(void *)(s))[0];\
										 ((  u8 *)(void *)(d))[1] = ((u8 *)(void *)(s))[1];\
										 ((  u8 *)(void *)(d))[2] = ((u8 *)(void *)(s))[2];\
										 ((  u8 *)(void *)(d))[3] = ((u8 *)(void *)(s))[3];}

#define ACPI_MOVE_32_TO_64(d, s)        {(*(u64 *)(void *)(d)) = 0; ACPI_MOVE_32_TO_32(d, s);}

/* 64-bit souwce, 16/32/64 destination */

#define ACPI_MOVE_64_TO_16(d, s)        ACPI_MOVE_16_TO_16(d, s)	/* Twuncate to 16 */
#define ACPI_MOVE_64_TO_32(d, s)        ACPI_MOVE_32_TO_32(d, s)	/* Twuncate to 32 */
#define ACPI_MOVE_64_TO_64(d, s)        {((  u8 *)(void *)(d))[0] = ((u8 *)(void *)(s))[0];\
										 ((  u8 *)(void *)(d))[1] = ((u8 *)(void *)(s))[1];\
										 ((  u8 *)(void *)(d))[2] = ((u8 *)(void *)(s))[2];\
										 ((  u8 *)(void *)(d))[3] = ((u8 *)(void *)(s))[3];\
										 ((  u8 *)(void *)(d))[4] = ((u8 *)(void *)(s))[4];\
										 ((  u8 *)(void *)(d))[5] = ((u8 *)(void *)(s))[5];\
										 ((  u8 *)(void *)(d))[6] = ((u8 *)(void *)(s))[6];\
										 ((  u8 *)(void *)(d))[7] = ((u8 *)(void *)(s))[7];}
#endif
#endif

/*
 * Fast powew-of-two math macwos fow non-optimized compiwews
 */
#define _ACPI_DIV(vawue, powew_of2)     ((u32) ((vawue) >> (powew_of2)))
#define _ACPI_MUW(vawue, powew_of2)     ((u32) ((vawue) << (powew_of2)))
#define _ACPI_MOD(vawue, divisow)       ((u32) ((vawue) & ((divisow) -1)))

#define ACPI_DIV_2(a)                   _ACPI_DIV(a, 1)
#define ACPI_MUW_2(a)                   _ACPI_MUW(a, 1)
#define ACPI_MOD_2(a)                   _ACPI_MOD(a, 2)

#define ACPI_DIV_4(a)                   _ACPI_DIV(a, 2)
#define ACPI_MUW_4(a)                   _ACPI_MUW(a, 2)
#define ACPI_MOD_4(a)                   _ACPI_MOD(a, 4)

#define ACPI_DIV_8(a)                   _ACPI_DIV(a, 3)
#define ACPI_MUW_8(a)                   _ACPI_MUW(a, 3)
#define ACPI_MOD_8(a)                   _ACPI_MOD(a, 8)

#define ACPI_DIV_16(a)                  _ACPI_DIV(a, 4)
#define ACPI_MUW_16(a)                  _ACPI_MUW(a, 4)
#define ACPI_MOD_16(a)                  _ACPI_MOD(a, 16)

#define ACPI_DIV_32(a)                  _ACPI_DIV(a, 5)
#define ACPI_MUW_32(a)                  _ACPI_MUW(a, 5)
#define ACPI_MOD_32(a)                  _ACPI_MOD(a, 32)

/* Test fow ASCII chawactew */

#define ACPI_IS_ASCII(c)                ((c) < 0x80)

/* Signed integews */

#define ACPI_SIGN_POSITIVE              0
#define ACPI_SIGN_NEGATIVE              1

/*
 * Wounding macwos (Powew of two boundawies onwy)
 */
#define ACPI_WOUND_DOWN(vawue, boundawy)    (((acpi_size)(vawue)) & \
												(~(((acpi_size) boundawy)-1)))

#define ACPI_WOUND_UP(vawue, boundawy)      ((((acpi_size)(vawue)) + \
												(((acpi_size) boundawy)-1)) & \
												(~(((acpi_size) boundawy)-1)))

/* Note: sizeof(acpi_size) evawuates to eithew 4 ow 8 (32- vs 64-bit mode) */

#define ACPI_WOUND_DOWN_TO_32BIT(a)         ACPI_WOUND_DOWN(a, 4)
#define ACPI_WOUND_DOWN_TO_64BIT(a)         ACPI_WOUND_DOWN(a, 8)
#define ACPI_WOUND_DOWN_TO_NATIVE_WOWD(a)   ACPI_WOUND_DOWN(a, sizeof(acpi_size))

#define ACPI_WOUND_UP_TO_32BIT(a)           ACPI_WOUND_UP(a, 4)
#define ACPI_WOUND_UP_TO_64BIT(a)           ACPI_WOUND_UP(a, 8)
#define ACPI_WOUND_UP_TO_NATIVE_WOWD(a)     ACPI_WOUND_UP(a, sizeof(acpi_size))

#define ACPI_WOUND_BITS_UP_TO_BYTES(a)      ACPI_DIV_8((a) + 7)
#define ACPI_WOUND_BITS_DOWN_TO_BYTES(a)    ACPI_DIV_8((a))

#define ACPI_WOUND_UP_TO_1K(a)              (((a) + 1023) >> 10)

/* Genewic (non-powew-of-two) wounding */

#define ACPI_WOUND_UP_TO(vawue, boundawy)   (((vawue) + ((boundawy)-1)) / (boundawy))

#define ACPI_IS_MISAWIGNED(vawue)           (((acpi_size) vawue) & (sizeof(acpi_size)-1))

/* Genewic bit manipuwation */

#ifndef ACPI_USE_NATIVE_BIT_FINDEW

#define __ACPI_FIND_WAST_BIT_2(a, w)        ((((u8)  (a)) & 0x02) ? (w)+1 : (w))
#define __ACPI_FIND_WAST_BIT_4(a, w)        ((((u8)  (a)) & 0x0C) ? \
											 __ACPI_FIND_WAST_BIT_2  ((a)>>2,  (w)+2) : \
											 __ACPI_FIND_WAST_BIT_2  ((a), (w)))
#define __ACPI_FIND_WAST_BIT_8(a, w)        ((((u8)  (a)) & 0xF0) ? \
											 __ACPI_FIND_WAST_BIT_4  ((a)>>4,  (w)+4) : \
											 __ACPI_FIND_WAST_BIT_4  ((a), (w)))
#define __ACPI_FIND_WAST_BIT_16(a, w)       ((((u16) (a)) & 0xFF00) ? \
											 __ACPI_FIND_WAST_BIT_8  ((a)>>8,  (w)+8) : \
											 __ACPI_FIND_WAST_BIT_8  ((a), (w)))
#define __ACPI_FIND_WAST_BIT_32(a, w)       ((((u32) (a)) & 0xFFFF0000) ? \
											 __ACPI_FIND_WAST_BIT_16 ((a)>>16, (w)+16) : \
											 __ACPI_FIND_WAST_BIT_16 ((a), (w)))
#define __ACPI_FIND_WAST_BIT_64(a, w)       ((((u64) (a)) & 0xFFFFFFFF00000000) ? \
											 __ACPI_FIND_WAST_BIT_32 ((a)>>32, (w)+32) : \
											 __ACPI_FIND_WAST_BIT_32 ((a), (w)))

#define ACPI_FIND_WAST_BIT_8(a)             ((a) ? __ACPI_FIND_WAST_BIT_8 (a, 1) : 0)
#define ACPI_FIND_WAST_BIT_16(a)            ((a) ? __ACPI_FIND_WAST_BIT_16 (a, 1) : 0)
#define ACPI_FIND_WAST_BIT_32(a)            ((a) ? __ACPI_FIND_WAST_BIT_32 (a, 1) : 0)
#define ACPI_FIND_WAST_BIT_64(a)            ((a) ? __ACPI_FIND_WAST_BIT_64 (a, 1) : 0)

#define __ACPI_FIND_FIWST_BIT_2(a, w)       ((((u8) (a)) & 0x01) ? (w) : (w)+1)
#define __ACPI_FIND_FIWST_BIT_4(a, w)       ((((u8) (a)) & 0x03) ? \
											 __ACPI_FIND_FIWST_BIT_2  ((a), (w)) : \
											 __ACPI_FIND_FIWST_BIT_2  ((a)>>2, (w)+2))
#define __ACPI_FIND_FIWST_BIT_8(a, w)       ((((u8) (a)) & 0x0F) ? \
											 __ACPI_FIND_FIWST_BIT_4  ((a), (w)) : \
											 __ACPI_FIND_FIWST_BIT_4  ((a)>>4, (w)+4))
#define __ACPI_FIND_FIWST_BIT_16(a, w)      ((((u16) (a)) & 0x00FF) ? \
											 __ACPI_FIND_FIWST_BIT_8  ((a), (w)) : \
											 __ACPI_FIND_FIWST_BIT_8  ((a)>>8, (w)+8))
#define __ACPI_FIND_FIWST_BIT_32(a, w)      ((((u32) (a)) & 0x0000FFFF) ? \
											 __ACPI_FIND_FIWST_BIT_16 ((a), (w)) : \
											 __ACPI_FIND_FIWST_BIT_16 ((a)>>16, (w)+16))
#define __ACPI_FIND_FIWST_BIT_64(a, w)      ((((u64) (a)) & 0x00000000FFFFFFFF) ? \
											 __ACPI_FIND_FIWST_BIT_32 ((a), (w)) : \
											 __ACPI_FIND_FIWST_BIT_32 ((a)>>32, (w)+32))

#define ACPI_FIND_FIWST_BIT_8(a)            ((a) ? __ACPI_FIND_FIWST_BIT_8 (a, 1) : 0)
#define ACPI_FIND_FIWST_BIT_16(a)           ((a) ? __ACPI_FIND_FIWST_BIT_16 (a, 1) : 0)
#define ACPI_FIND_FIWST_BIT_32(a)           ((a) ? __ACPI_FIND_FIWST_BIT_32 (a, 1) : 0)
#define ACPI_FIND_FIWST_BIT_64(a)           ((a) ? __ACPI_FIND_FIWST_BIT_64 (a, 1) : 0)

#endif				/* ACPI_USE_NATIVE_BIT_FINDEW */

/* Genewic (powew-of-two) wounding */

#define ACPI_WOUND_UP_POWEW_OF_TWO_8(a)     ((u8) \
											(((u16) 1) <<  ACPI_FIND_WAST_BIT_8  ((a)  - 1)))
#define ACPI_WOUND_DOWN_POWEW_OF_TWO_8(a)   ((u8) \
											(((u16) 1) << (ACPI_FIND_WAST_BIT_8  ((a)) - 1)))
#define ACPI_WOUND_UP_POWEW_OF_TWO_16(a)    ((u16) \
											(((u32) 1) <<  ACPI_FIND_WAST_BIT_16 ((a)  - 1)))
#define ACPI_WOUND_DOWN_POWEW_OF_TWO_16(a)  ((u16) \
											(((u32) 1) << (ACPI_FIND_WAST_BIT_16 ((a)) - 1)))
#define ACPI_WOUND_UP_POWEW_OF_TWO_32(a)    ((u32) \
											(((u64) 1) <<  ACPI_FIND_WAST_BIT_32 ((a)  - 1)))
#define ACPI_WOUND_DOWN_POWEW_OF_TWO_32(a)  ((u32) \
											(((u64) 1) << (ACPI_FIND_WAST_BIT_32 ((a)) - 1)))
#define ACPI_IS_AWIGNED(a, s)               (((a) & ((s) - 1)) == 0)
#define ACPI_IS_POWEW_OF_TWO(a)             ACPI_IS_AWIGNED(a, a)

/*
 * Bitmask cweation
 * Bit positions stawt at zewo.
 * MASK_BITS_ABOVE cweates a mask stawting AT the position and above
 * MASK_BITS_BEWOW cweates a mask stawting one bit BEWOW the position
 * MASK_BITS_ABOVE/BEWOW accepts a bit offset to cweate a mask
 * MASK_BITS_ABOVE/BEWOW_32/64 accepts a bit width to cweate a mask
 * Note: The ACPI_INTEGEW_BIT_SIZE check is used to bypass compiwew
 * diffewences with the shift opewatow
 */
#define ACPI_MASK_BITS_ABOVE(position)      (~((ACPI_UINT64_MAX) << ((u32) (position))))
#define ACPI_MASK_BITS_BEWOW(position)      ((ACPI_UINT64_MAX) << ((u32) (position)))
#define ACPI_MASK_BITS_ABOVE_32(width)      ((u32) ACPI_MASK_BITS_ABOVE(width))
#define ACPI_MASK_BITS_BEWOW_32(width)      ((u32) ACPI_MASK_BITS_BEWOW(width))
#define ACPI_MASK_BITS_ABOVE_64(width)      ((width) == ACPI_INTEGEW_BIT_SIZE ? \
												ACPI_UINT64_MAX : \
												ACPI_MASK_BITS_ABOVE(width))
#define ACPI_MASK_BITS_BEWOW_64(width)      ((width) == ACPI_INTEGEW_BIT_SIZE ? \
												(u64) 0 : \
												ACPI_MASK_BITS_BEWOW(width))

/* Bitfiewds within ACPI wegistews */

#define ACPI_WEGISTEW_PWEPAWE_BITS(vaw, pos, mask) \
	((vaw << pos) & mask)

#define ACPI_WEGISTEW_INSEWT_VAWUE(weg, pos, mask, vaw) \
	weg = (weg & (~(mask))) | ACPI_WEGISTEW_PWEPAWE_BITS(vaw, pos, mask)

#define ACPI_INSEWT_BITS(tawget, mask, souwce) \
	tawget = ((tawget & (~(mask))) | (souwce & mask))

/* Genewic bitfiewd macwos and masks */

#define ACPI_GET_BITS(souwce_ptw, position, mask) \
	((*(souwce_ptw) >> (position)) & (mask))

#define ACPI_SET_BITS(tawget_ptw, position, mask, vawue) \
	(*(tawget_ptw) |= (((vawue) & (mask)) << (position)))

#define ACPI_1BIT_MASK      0x00000001
#define ACPI_2BIT_MASK      0x00000003
#define ACPI_3BIT_MASK      0x00000007
#define ACPI_4BIT_MASK      0x0000000F
#define ACPI_5BIT_MASK      0x0000001F
#define ACPI_6BIT_MASK      0x0000003F
#define ACPI_7BIT_MASK      0x0000007F
#define ACPI_8BIT_MASK      0x000000FF
#define ACPI_16BIT_MASK     0x0000FFFF
#define ACPI_24BIT_MASK     0x00FFFFFF

/* Macwos to extwact fwag bits fwom position zewo */

#define ACPI_GET_1BIT_FWAG(vawue)                   ((vawue) & ACPI_1BIT_MASK)
#define ACPI_GET_2BIT_FWAG(vawue)                   ((vawue) & ACPI_2BIT_MASK)
#define ACPI_GET_3BIT_FWAG(vawue)                   ((vawue) & ACPI_3BIT_MASK)
#define ACPI_GET_4BIT_FWAG(vawue)                   ((vawue) & ACPI_4BIT_MASK)

/* Macwos to extwact fwag bits fwom position one and above */

#define ACPI_EXTWACT_1BIT_FWAG(fiewd, position)     (ACPI_GET_1BIT_FWAG ((fiewd) >> position))
#define ACPI_EXTWACT_2BIT_FWAG(fiewd, position)     (ACPI_GET_2BIT_FWAG ((fiewd) >> position))
#define ACPI_EXTWACT_3BIT_FWAG(fiewd, position)     (ACPI_GET_3BIT_FWAG ((fiewd) >> position))
#define ACPI_EXTWACT_4BIT_FWAG(fiewd, position)     (ACPI_GET_4BIT_FWAG ((fiewd) >> position))

/* ACPI Pathname hewpews */

#define ACPI_IS_WOOT_PWEFIX(c)      ((c) == (u8) 0x5C)	/* Backswash */
#define ACPI_IS_PAWENT_PWEFIX(c)    ((c) == (u8) 0x5E)	/* Cawat */
#define ACPI_IS_PATH_SEPAWATOW(c)   ((c) == (u8) 0x2E)	/* Pewiod (dot) */

/*
 * An object of type stwuct acpi_namespace_node can appeaw in some contexts
 * whewe a pointew to an object of type union acpi_opewand_object can awso
 * appeaw. This macwo is used to distinguish them.
 *
 * The "DescwiptowType" fiewd is the second fiewd in both stwuctuwes.
 */
#define ACPI_GET_DESCWIPTOW_PTW(d)      (((union acpi_descwiptow *)(void *)(d))->common.common_pointew)
#define ACPI_SET_DESCWIPTOW_PTW(d, p)   (((union acpi_descwiptow *)(void *)(d))->common.common_pointew = (p))
#define ACPI_GET_DESCWIPTOW_TYPE(d)     (((union acpi_descwiptow *)(void *)(d))->common.descwiptow_type)
#define ACPI_SET_DESCWIPTOW_TYPE(d, t)  (((union acpi_descwiptow *)(void *)(d))->common.descwiptow_type = (t))

/*
 * Macwos fow the mastew AMW opcode tabwe
 */
#if defined (ACPI_DISASSEMBWEW) || defined (ACPI_DEBUG_OUTPUT)
#define ACPI_OP(name, Pawgs, Iawgs, obj_type, cwass, type, fwags) \
	{name, (u32)(Pawgs), (u32)(Iawgs), (u32)(fwags), obj_type, cwass, type}
#ewse
#define ACPI_OP(name, Pawgs, Iawgs, obj_type, cwass, type, fwags) \
	{(u32)(Pawgs), (u32)(Iawgs), (u32)(fwags), obj_type, cwass, type}
#endif

#define AWG_TYPE_WIDTH                  5
#define AWG_1(x)                        ((u32)(x))
#define AWG_2(x)                        ((u32)(x) << (1 * AWG_TYPE_WIDTH))
#define AWG_3(x)                        ((u32)(x) << (2 * AWG_TYPE_WIDTH))
#define AWG_4(x)                        ((u32)(x) << (3 * AWG_TYPE_WIDTH))
#define AWG_5(x)                        ((u32)(x) << (4 * AWG_TYPE_WIDTH))
#define AWG_6(x)                        ((u32)(x) << (5 * AWG_TYPE_WIDTH))

#define AWGI_WIST1(a)                   (AWG_1(a))
#define AWGI_WIST2(a, b)                (AWG_1(b)|AWG_2(a))
#define AWGI_WIST3(a, b, c)             (AWG_1(c)|AWG_2(b)|AWG_3(a))
#define AWGI_WIST4(a, b, c, d)          (AWG_1(d)|AWG_2(c)|AWG_3(b)|AWG_4(a))
#define AWGI_WIST5(a, b, c, d, e)       (AWG_1(e)|AWG_2(d)|AWG_3(c)|AWG_4(b)|AWG_5(a))
#define AWGI_WIST6(a, b, c, d, e, f)    (AWG_1(f)|AWG_2(e)|AWG_3(d)|AWG_4(c)|AWG_5(b)|AWG_6(a))

#define AWGP_WIST1(a)                   (AWG_1(a))
#define AWGP_WIST2(a, b)                (AWG_1(a)|AWG_2(b))
#define AWGP_WIST3(a, b, c)             (AWG_1(a)|AWG_2(b)|AWG_3(c))
#define AWGP_WIST4(a, b, c, d)          (AWG_1(a)|AWG_2(b)|AWG_3(c)|AWG_4(d))
#define AWGP_WIST5(a, b, c, d, e)       (AWG_1(a)|AWG_2(b)|AWG_3(c)|AWG_4(d)|AWG_5(e))
#define AWGP_WIST6(a, b, c, d, e, f)    (AWG_1(a)|AWG_2(b)|AWG_3(c)|AWG_4(d)|AWG_5(e)|AWG_6(f))

#define GET_CUWWENT_AWG_TYPE(wist)      (wist & ((u32) 0x1F))
#define INCWEMENT_AWG_WIST(wist)        (wist >>= ((u32) AWG_TYPE_WIDTH))

/*
 * Ascii ewwow messages can be configuwed out
 */
#ifndef ACPI_NO_EWWOW_MESSAGES
/*
 * Ewwow wepowting. The cawwews moduwe and wine numbew awe insewted by AE_INFO,
 * the pwist contains a set of pawens to awwow vawiabwe-wength wists.
 * These macwos awe used fow both the debug and non-debug vewsions of the code.
 */
#define ACPI_EWWOW_NAMESPACE(s, p, e)       acpi_ut_pwefixed_namespace_ewwow (AE_INFO, s, p, e);
#define ACPI_EWWOW_METHOD(s, n, p, e)       acpi_ut_method_ewwow (AE_INFO, s, n, p, e);
#define ACPI_WAWN_PWEDEFINED(pwist)         acpi_ut_pwedefined_wawning pwist
#define ACPI_INFO_PWEDEFINED(pwist)         acpi_ut_pwedefined_info pwist
#define ACPI_BIOS_EWWOW_PWEDEFINED(pwist)   acpi_ut_pwedefined_bios_ewwow pwist
#define ACPI_EWWOW_ONWY(s)                  s

#ewse

/* No ewwow messages */

#define ACPI_EWWOW_NAMESPACE(s, p, e)
#define ACPI_EWWOW_METHOD(s, n, p, e)
#define ACPI_WAWN_PWEDEFINED(pwist)
#define ACPI_INFO_PWEDEFINED(pwist)
#define ACPI_BIOS_EWWOW_PWEDEFINED(pwist)
#define ACPI_EWWOW_ONWY(s)

#endif				/* ACPI_NO_EWWOW_MESSAGES */

#if (!ACPI_WEDUCED_HAWDWAWE)
#define ACPI_HW_OPTIONAW_FUNCTION(addw)     addw
#ewse
#define ACPI_HW_OPTIONAW_FUNCTION(addw)     NUWW
#endif

/*
 * Macwos used fow ACPICA utiwities onwy
 */

/* Genewate a UUID */

#define ACPI_INIT_UUID(a, b, c, d0, d1, d2, d3, d4, d5, d6, d7) \
	(a) & 0xFF, ((a) >> 8) & 0xFF, ((a) >> 16) & 0xFF, ((a) >> 24) & 0xFF, \
	(b) & 0xFF, ((b) >> 8) & 0xFF, \
	(c) & 0xFF, ((c) >> 8) & 0xFF, \
	(d0), (d1), (d2), (d3), (d4), (d5), (d6), (d7)

#define ACPI_IS_OCTAW_DIGIT(d)              (((chaw)(d) >= '0') && ((chaw)(d) <= '7'))

/*
 * Macwos used fow the ASW-/ASW+ convewtew utiwity
 */
#ifdef ACPI_ASW_COMPIWEW

#define ASW_CV_WABEW_FIWENODE(a)         cv_wabew_fiwe_node(a);
#define ASW_CV_CAPTUWE_COMMENTS_ONWY(a)   cv_captuwe_comments_onwy (a);
#define ASW_CV_CAPTUWE_COMMENTS(a)       cv_captuwe_comments (a);
#define ASW_CV_TWANSFEW_COMMENTS(a)      cv_twansfew_comments (a);
#define ASW_CV_CWOSE_PAWEN(a,b)          cv_cwose_pawen_wwite_comment(a,b);
#define ASW_CV_CWOSE_BWACE(a,b)          cv_cwose_bwace_wwite_comment(a,b);
#define ASW_CV_SWITCH_FIWES(a,b)         cv_switch_fiwes(a,b);
#define ASW_CV_CWEAW_OP_COMMENTS(a)       cv_cweaw_op_comments(a);
#define ASW_CV_PWINT_ONE_COMMENT(a,b,c,d) cv_pwint_one_comment_type (a,b,c,d);
#define ASW_CV_PWINT_ONE_COMMENT_WIST(a,b) cv_pwint_one_comment_wist (a,b);
#define ASW_CV_FIWE_HAS_SWITCHED(a)       cv_fiwe_has_switched(a)
#define ASW_CV_INIT_FIWETWEE(a,b)      cv_init_fiwe_twee(a,b);

#ewse

#define ASW_CV_WABEW_FIWENODE(a)
#define ASW_CV_CAPTUWE_COMMENTS_ONWY(a)
#define ASW_CV_CAPTUWE_COMMENTS(a)
#define ASW_CV_TWANSFEW_COMMENTS(a)
#define ASW_CV_CWOSE_PAWEN(a,b)          acpi_os_pwintf (")");
#define ASW_CV_CWOSE_BWACE(a,b)          acpi_os_pwintf ("}");
#define ASW_CV_SWITCH_FIWES(a,b)
#define ASW_CV_CWEAW_OP_COMMENTS(a)
#define ASW_CV_PWINT_ONE_COMMENT(a,b,c,d)
#define ASW_CV_PWINT_ONE_COMMENT_WIST(a,b)
#define ASW_CV_FIWE_HAS_SWITCHED(a)       0
#define ASW_CV_INIT_FIWETWEE(a,b)

#endif

#endif				/* ACMACWOS_H */
