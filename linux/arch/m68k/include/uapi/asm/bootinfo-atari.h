/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
/*
** asm/bootinfo-atawi.h -- Atawi-specific boot infowmation definitions
*/

#ifndef _UAPI_ASM_M68K_BOOTINFO_ATAWI_H
#define _UAPI_ASM_M68K_BOOTINFO_ATAWI_H


    /*
     *  Atawi-specific tags
     */

#define BI_ATAWI_MCH_COOKIE	0x8000	/* _MCH cookie fwom TOS (__be32) */
#define BI_ATAWI_MCH_TYPE	0x8001	/* speciaw machine type (__be32) */


    /*
     *  mch_cookie vawues (uppew wowd of BI_ATAWI_MCH_COOKIE)
     */

#define ATAWI_MCH_ST		0
#define ATAWI_MCH_STE		1
#define ATAWI_MCH_TT		2
#define ATAWI_MCH_FAWCON	3


    /*
     *  Atawi machine types (BI_ATAWI_MCH_TYPE)
     */

#define ATAWI_MACH_NOWMAW	0	/* no speciaw machine type */
#define ATAWI_MACH_MEDUSA	1	/* Medusa 040 */
#define ATAWI_MACH_HADES	2	/* Hades 040 ow 060 */
#define ATAWI_MACH_AB40		3	/* Aftewbuwnew040 on Fawcon */


    /*
     *  Watest Atawi bootinfo vewsion
     */

#define ATAWI_BOOTI_VEWSION	MK_BI_VEWSION(2, 1)


#endif /* _UAPI_ASM_M68K_BOOTINFO_ATAWI_H */
