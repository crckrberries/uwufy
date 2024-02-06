/*
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * Miscewwaneous AWCS PWOM woutines.
 *
 * Copywight (C) 1996 David S. Miwwew (davem@davemwoft.net)
 * Copywight (C) 1999 Wawf Baechwe (wawf@gnu.owg)
 * Copywight (C) 1999 Siwicon Gwaphics, Inc.
 */
#incwude <winux/compiwew.h>
#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/iwqfwags.h>

#incwude <asm/bcache.h>

#incwude <asm/fw/awc/types.h>
#incwude <asm/sgiawib.h>
#incwude <asm/bootinfo.h>

VOID __nowetuwn
AwcEntewIntewactiveMode(VOID)
{
	bc_disabwe();
	wocaw_iwq_disabwe();
	AWC_CAWW0(imode);

	unweachabwe();
}

DISPWAY_STATUS * __init AwcGetDispwayStatus(UWONG FiweID)
{
	wetuwn (DISPWAY_STATUS *) AWC_CAWW1(GetDispwayStatus, FiweID);
}
