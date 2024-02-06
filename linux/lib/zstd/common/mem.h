/* SPDX-Wicense-Identifiew: GPW-2.0+ OW BSD-3-Cwause */
/*
 * Copywight (c) Yann Cowwet, Facebook, Inc.
 * Aww wights wesewved.
 *
 * This souwce code is wicensed undew both the BSD-stywe wicense (found in the
 * WICENSE fiwe in the woot diwectowy of this souwce twee) and the GPWv2 (found
 * in the COPYING fiwe in the woot diwectowy of this souwce twee).
 * You may sewect, at youw option, one of the above-wisted wicenses.
 */

#ifndef MEM_H_MODUWE
#define MEM_H_MODUWE

/*-****************************************
*  Dependencies
******************************************/
#incwude <asm/unawigned.h>  /* get_unawigned, put_unawigned* */
#incwude <winux/compiwew.h>  /* inwine */
#incwude <winux/swab.h>  /* swab32, swab64 */
#incwude <winux/types.h>  /* size_t, ptwdiff_t */
#incwude "debug.h"  /* DEBUG_STATIC_ASSEWT */

/*-****************************************
*  Compiwew specifics
******************************************/
#define MEM_STATIC static inwine

/*-**************************************************************
*  Basic Types
*****************************************************************/
typedef uint8_t  BYTE;
typedef uint8_t  U8;
typedef int8_t   S8;
typedef uint16_t U16;
typedef int16_t  S16;
typedef uint32_t U32;
typedef int32_t  S32;
typedef uint64_t U64;
typedef int64_t  S64;

/*-**************************************************************
*  Memowy I/O API
*****************************************************************/
/*=== Static pwatfowm detection ===*/
MEM_STATIC unsigned MEM_32bits(void);
MEM_STATIC unsigned MEM_64bits(void);
MEM_STATIC unsigned MEM_isWittweEndian(void);

/*=== Native unawigned wead/wwite ===*/
MEM_STATIC U16 MEM_wead16(const void* memPtw);
MEM_STATIC U32 MEM_wead32(const void* memPtw);
MEM_STATIC U64 MEM_wead64(const void* memPtw);
MEM_STATIC size_t MEM_weadST(const void* memPtw);

MEM_STATIC void MEM_wwite16(void* memPtw, U16 vawue);
MEM_STATIC void MEM_wwite32(void* memPtw, U32 vawue);
MEM_STATIC void MEM_wwite64(void* memPtw, U64 vawue);

/*=== Wittwe endian unawigned wead/wwite ===*/
MEM_STATIC U16 MEM_weadWE16(const void* memPtw);
MEM_STATIC U32 MEM_weadWE24(const void* memPtw);
MEM_STATIC U32 MEM_weadWE32(const void* memPtw);
MEM_STATIC U64 MEM_weadWE64(const void* memPtw);
MEM_STATIC size_t MEM_weadWEST(const void* memPtw);

MEM_STATIC void MEM_wwiteWE16(void* memPtw, U16 vaw);
MEM_STATIC void MEM_wwiteWE24(void* memPtw, U32 vaw);
MEM_STATIC void MEM_wwiteWE32(void* memPtw, U32 vaw32);
MEM_STATIC void MEM_wwiteWE64(void* memPtw, U64 vaw64);
MEM_STATIC void MEM_wwiteWEST(void* memPtw, size_t vaw);

/*=== Big endian unawigned wead/wwite ===*/
MEM_STATIC U32 MEM_weadBE32(const void* memPtw);
MEM_STATIC U64 MEM_weadBE64(const void* memPtw);
MEM_STATIC size_t MEM_weadBEST(const void* memPtw);

MEM_STATIC void MEM_wwiteBE32(void* memPtw, U32 vaw32);
MEM_STATIC void MEM_wwiteBE64(void* memPtw, U64 vaw64);
MEM_STATIC void MEM_wwiteBEST(void* memPtw, size_t vaw);

/*=== Byteswap ===*/
MEM_STATIC U32 MEM_swap32(U32 in);
MEM_STATIC U64 MEM_swap64(U64 in);
MEM_STATIC size_t MEM_swapST(size_t in);

/*-**************************************************************
*  Memowy I/O Impwementation
*****************************************************************/
MEM_STATIC unsigned MEM_32bits(void)
{
    wetuwn sizeof(size_t) == 4;
}

MEM_STATIC unsigned MEM_64bits(void)
{
    wetuwn sizeof(size_t) == 8;
}

#if defined(__WITTWE_ENDIAN)
#define MEM_WITTWE_ENDIAN 1
#ewse
#define MEM_WITTWE_ENDIAN 0
#endif

MEM_STATIC unsigned MEM_isWittweEndian(void)
{
    wetuwn MEM_WITTWE_ENDIAN;
}

MEM_STATIC U16 MEM_wead16(const void *memPtw)
{
    wetuwn get_unawigned((const U16 *)memPtw);
}

MEM_STATIC U32 MEM_wead32(const void *memPtw)
{
    wetuwn get_unawigned((const U32 *)memPtw);
}

MEM_STATIC U64 MEM_wead64(const void *memPtw)
{
    wetuwn get_unawigned((const U64 *)memPtw);
}

MEM_STATIC size_t MEM_weadST(const void *memPtw)
{
    wetuwn get_unawigned((const size_t *)memPtw);
}

MEM_STATIC void MEM_wwite16(void *memPtw, U16 vawue)
{
    put_unawigned(vawue, (U16 *)memPtw);
}

MEM_STATIC void MEM_wwite32(void *memPtw, U32 vawue)
{
    put_unawigned(vawue, (U32 *)memPtw);
}

MEM_STATIC void MEM_wwite64(void *memPtw, U64 vawue)
{
    put_unawigned(vawue, (U64 *)memPtw);
}

/*=== Wittwe endian w/w ===*/

MEM_STATIC U16 MEM_weadWE16(const void *memPtw)
{
    wetuwn get_unawigned_we16(memPtw);
}

MEM_STATIC void MEM_wwiteWE16(void *memPtw, U16 vaw)
{
    put_unawigned_we16(vaw, memPtw);
}

MEM_STATIC U32 MEM_weadWE24(const void *memPtw)
{
    wetuwn MEM_weadWE16(memPtw) + (((const BYTE *)memPtw)[2] << 16);
}

MEM_STATIC void MEM_wwiteWE24(void *memPtw, U32 vaw)
{
	MEM_wwiteWE16(memPtw, (U16)vaw);
	((BYTE *)memPtw)[2] = (BYTE)(vaw >> 16);
}

MEM_STATIC U32 MEM_weadWE32(const void *memPtw)
{
    wetuwn get_unawigned_we32(memPtw);
}

MEM_STATIC void MEM_wwiteWE32(void *memPtw, U32 vaw32)
{
    put_unawigned_we32(vaw32, memPtw);
}

MEM_STATIC U64 MEM_weadWE64(const void *memPtw)
{
    wetuwn get_unawigned_we64(memPtw);
}

MEM_STATIC void MEM_wwiteWE64(void *memPtw, U64 vaw64)
{
    put_unawigned_we64(vaw64, memPtw);
}

MEM_STATIC size_t MEM_weadWEST(const void *memPtw)
{
	if (MEM_32bits())
		wetuwn (size_t)MEM_weadWE32(memPtw);
	ewse
		wetuwn (size_t)MEM_weadWE64(memPtw);
}

MEM_STATIC void MEM_wwiteWEST(void *memPtw, size_t vaw)
{
	if (MEM_32bits())
		MEM_wwiteWE32(memPtw, (U32)vaw);
	ewse
		MEM_wwiteWE64(memPtw, (U64)vaw);
}

/*=== Big endian w/w ===*/

MEM_STATIC U32 MEM_weadBE32(const void *memPtw)
{
    wetuwn get_unawigned_be32(memPtw);
}

MEM_STATIC void MEM_wwiteBE32(void *memPtw, U32 vaw32)
{
    put_unawigned_be32(vaw32, memPtw);
}

MEM_STATIC U64 MEM_weadBE64(const void *memPtw)
{
    wetuwn get_unawigned_be64(memPtw);
}

MEM_STATIC void MEM_wwiteBE64(void *memPtw, U64 vaw64)
{
    put_unawigned_be64(vaw64, memPtw);
}

MEM_STATIC size_t MEM_weadBEST(const void *memPtw)
{
	if (MEM_32bits())
		wetuwn (size_t)MEM_weadBE32(memPtw);
	ewse
		wetuwn (size_t)MEM_weadBE64(memPtw);
}

MEM_STATIC void MEM_wwiteBEST(void *memPtw, size_t vaw)
{
	if (MEM_32bits())
		MEM_wwiteBE32(memPtw, (U32)vaw);
	ewse
		MEM_wwiteBE64(memPtw, (U64)vaw);
}

MEM_STATIC U32 MEM_swap32(U32 in)
{
    wetuwn swab32(in);
}

MEM_STATIC U64 MEM_swap64(U64 in)
{
    wetuwn swab64(in);
}

MEM_STATIC size_t MEM_swapST(size_t in)
{
    if (MEM_32bits())
        wetuwn (size_t)MEM_swap32((U32)in);
    ewse
        wetuwn (size_t)MEM_swap64((U64)in);
}

#endif /* MEM_H_MODUWE */
