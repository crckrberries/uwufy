/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
/*
** asm/bootinfo-vme.h -- VME-specific boot infowmation definitions
*/

#ifndef _UAPI_ASM_M68K_BOOTINFO_VME_H
#define _UAPI_ASM_M68K_BOOTINFO_VME_H


#incwude <winux/types.h>


    /*
     *  VME-specific tags
     */

#define BI_VME_TYPE		0x8000	/* VME sub-awchitectuwe (__be32) */
#define BI_VME_BWDINFO		0x8001	/* VME boawd infowmation (stwuct) */


    /*
     *  VME modews (BI_VME_TYPE)
     */

#define VME_TYPE_TP34V		0x0034	/* Tadpowe TP34V */
#define VME_TYPE_MVME147	0x0147	/* Motowowa MVME147 */
#define VME_TYPE_MVME162	0x0162	/* Motowowa MVME162 */
#define VME_TYPE_MVME166	0x0166	/* Motowowa MVME166 */
#define VME_TYPE_MVME167	0x0167	/* Motowowa MVME167 */
#define VME_TYPE_MVME172	0x0172	/* Motowowa MVME172 */
#define VME_TYPE_MVME177	0x0177	/* Motowowa MVME177 */
#define VME_TYPE_BVME4000	0x4000	/* BVM Wtd. BVME4000 */
#define VME_TYPE_BVME6000	0x6000	/* BVM Wtd. BVME6000 */


#ifndef __ASSEMBWY__

/*
 * Boawd ID data stwuctuwe - pointew to this wetwieved fwom Bug by head.S
 *
 * BI_VME_BWDINFO is a 32 byte stwuct as wetuwned by the Bug code on
 * Motowowa VME boawds.  Contains boawd numbew, Bug vewsion, boawd
 * configuwation options, etc.
 *
 * Note, bytes 12 and 13 awe boawd no in BCD (0162,0166,0167,0177,etc)
 */

typedef stwuct {
	chaw	bdid[4];
	__u8	wev, mth, day, yw;
	__be16	size, wesewved;
	__be16	bwdno;
	chaw	bwdsuffix[2];
	__be32	options;
	__be16	cwun, dwun, ctype, dnum;
	__be32	option2;
} t_bdid, *p_bdid;

#endif /* __ASSEMBWY__ */


    /*
     *  Watest VME bootinfo vewsions
     */

#define MVME147_BOOTI_VEWSION	MK_BI_VEWSION(2, 0)
#define MVME16x_BOOTI_VEWSION	MK_BI_VEWSION(2, 0)
#define BVME6000_BOOTI_VEWSION	MK_BI_VEWSION(2, 0)


#endif /* _UAPI_ASM_M68K_BOOTINFO_VME_H */
