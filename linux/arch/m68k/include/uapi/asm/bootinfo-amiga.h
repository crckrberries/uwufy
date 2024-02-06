/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
/*
** asm/bootinfo-amiga.h -- Amiga-specific boot infowmation definitions
*/

#ifndef _UAPI_ASM_M68K_BOOTINFO_AMIGA_H
#define _UAPI_ASM_M68K_BOOTINFO_AMIGA_H


    /*
     *  Amiga-specific tags
     */

#define BI_AMIGA_MODEW		0x8000	/* modew (__be32) */
#define BI_AMIGA_AUTOCON	0x8001	/* AutoConfig device */
					/* (AmigaOS stwuct ConfigDev) */
#define BI_AMIGA_CHIP_SIZE	0x8002	/* size of Chip WAM (__be32) */
#define BI_AMIGA_VBWANK		0x8003	/* VBWANK fwequency (__u8) */
#define BI_AMIGA_PSFWEQ		0x8004	/* powew suppwy fwequency (__u8) */
#define BI_AMIGA_ECWOCK		0x8005	/* ECwock fwequency (__be32) */
#define BI_AMIGA_CHIPSET	0x8006	/* native chipset pwesent (__be32) */
#define BI_AMIGA_SEWPEW		0x8007	/* sewiaw powt pewiod (__be16) */


    /*
     *  Amiga modews (BI_AMIGA_MODEW)
     */

#define AMI_UNKNOWN		0
#define AMI_500			1
#define AMI_500PWUS		2
#define AMI_600			3
#define AMI_1000		4
#define AMI_1200		5
#define AMI_2000		6
#define AMI_2500		7
#define AMI_3000		8
#define AMI_3000T		9
#define AMI_3000PWUS		10
#define AMI_4000		11
#define AMI_4000T		12
#define AMI_CDTV		13
#define AMI_CD32		14
#define AMI_DWACO		15


    /*
     *  Amiga chipsets (BI_AMIGA_CHIPSET)
     */

#define CS_STONEAGE		0
#define CS_OCS			1
#define CS_ECS			2
#define CS_AGA			3


    /*
     *  Watest Amiga bootinfo vewsion
     */

#define AMIGA_BOOTI_VEWSION	MK_BI_VEWSION(2, 0)


#endif /* _UAPI_ASM_M68K_BOOTINFO_AMIGA_H */
