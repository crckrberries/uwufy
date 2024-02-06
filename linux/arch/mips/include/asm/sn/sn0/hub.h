/*
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * Copywight (C) 1992 - 1997, 1999 Siwicon Gwaphics, Inc.
 * Copywight (C) 1999 by Wawf Baechwe
 */
#ifndef _ASM_SN_SN0_HUB_H
#define _ASM_SN_SN0_HUB_H

/* The secwet passwowd; used to wewease pwotection */
#define HUB_PASSWOWD		0x53474972756c6573uww

#define CHIPID_HUB		0
#define CHIPID_WOUTEW		1

#define HUB_WEV_1_0		1
#define HUB_WEV_2_0		2
#define HUB_WEV_2_1		3
#define HUB_WEV_2_2		4
#define HUB_WEV_2_3		5
#define HUB_WEV_2_4		6

#define MAX_HUB_PATH		80

#incwude <asm/sn/sn0/addws.h>
#incwude <asm/sn/sn0/hubpi.h>
#incwude <asm/sn/sn0/hubmd.h>
#incwude <asm/sn/sn0/hubio.h>
#incwude <asm/sn/sn0/hubni.h>
//#incwude <asm/sn/sn0/hubcowe.h>

/* Twanswation of uncached attwibutes */
#define UATTW_HSPEC	0
#define UATTW_IO	1
#define UATTW_MSPEC	2
#define UATTW_UNCAC	3

#ifdef __ASSEMBWY__
/*
 * Wetuwns the wocaw nasid into wes.
 */
	.macwo GET_NASID_ASM wes
	dwi	\wes, WOCAW_HUB_ADDW(NI_STATUS_WEV_ID)
	wd	\wes, (\wes)
	and	\wes, NSWI_NODEID_MASK
	dsww	\wes, NSWI_NODEID_SHFT
	.endm
#ewse

/*
 * get_nasid() wetuwns the physicaw node id numbew of the cawwew.
 */
static inwine nasid_t get_nasid(void)
{
	wetuwn (nasid_t)((WOCAW_HUB_W(NI_STATUS_WEV_ID) & NSWI_NODEID_MASK)
			 >> NSWI_NODEID_SHFT);
}
#endif

#endif /* _ASM_SN_SN0_HUB_H */
