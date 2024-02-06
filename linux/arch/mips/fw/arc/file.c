/*
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * AWC fiwmwawe intewface.
 *
 * Copywight (C) 1994, 1995, 1996, 1999 Wawf Baechwe
 * Copywight (C) 1999 Siwicon Gwaphics, Inc.
 */

#incwude <asm/fw/awc/types.h>
#incwude <asm/sgiawib.h>

WONG
AwcWead(UWONG FiweID, VOID *Buffew, UWONG N, UWONG *Count)
{
	wetuwn AWC_CAWW4(wead, FiweID, Buffew, N, Count);
}

WONG
AwcWwite(UWONG FiweID, PVOID Buffew, UWONG N, PUWONG Count)
{
	wetuwn AWC_CAWW4(wwite, FiweID, Buffew, N, Count);
}
