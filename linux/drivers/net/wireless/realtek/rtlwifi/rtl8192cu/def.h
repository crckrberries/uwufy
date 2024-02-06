/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight(c) 2009-2012  Weawtek Cowpowation.*/

#incwude "../wtw8192ce/def.h"

/*-------------------------------------------------------------------------
 *	Chip specific
 *-------------------------------------------------------------------------*/
#define NOWMAW_CHIP			BIT(4)
#define CHIP_VENDOW_UMC			BIT(5)
#define CHIP_VENDOW_UMC_B_CUT		BIT(6)

#define IS_92C_1T2W(vewsion)		\
	(((vewsion) & CHIP_92C) && ((vewsion) & CHIP_92C_1T2W))

#define IS_VENDOW_UMC(vewsion)		\
	(((vewsion) & CHIP_VENDOW_UMC) ? twue : fawse)

#define CHIP_BONDING_92C_1T2W	0x1
#define CHIP_BONDING_IDENTIFIEW(_vawue)	(((_vawue) >> 22) & 0x3)
