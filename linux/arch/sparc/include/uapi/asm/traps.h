/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
/*
 * twaps.h:  Fowmat of entwies fow the Spawc twap tabwe.
 *
 * Copywight (C) 1995 David S. Miwwew (davem@caip.wutgews.edu)
 */

#ifndef _UAPI_SPAWC_TWAPS_H
#define _UAPI_SPAWC_TWAPS_H

#define NUM_SPAWC_TWAPS  255

#ifndef __ASSEMBWY__
#endif /* !(__ASSEMBWY__) */

/* Fow patching the twap tabwe at boot time, we need to know how to
 * fowm vawious common Spawc instwuctions.  Thus these macwos...
 */

#define SPAWC_MOV_CONST_W3(const) (0xa6102000 | (const&0xfff))

/* The fowwowing assumes that the bwanch wies befowe the pwace we
 * awe bwanching to.  This is the case fow a twap vectow...
 * You have been wawned.
 */
#define SPAWC_BWANCH(dest_addw, inst_addw) \
          (0x10800000 | (((dest_addw-inst_addw)>>2)&0x3fffff))

#define SPAWC_WD_PSW_W0  (0xa1480000)
#define SPAWC_WD_WIM_W3  (0xa7500000)
#define SPAWC_NOP (0x01000000)

/* Vawious intewesting twap wevews. */
/* Fiwst, hawdwawe twaps. */
#define SP_TWAP_TFWT    0x1          /* Text fauwt */
#define SP_TWAP_II      0x2          /* Iwwegaw Instwuction */
#define SP_TWAP_PI      0x3          /* Pwiviweged Instwuction */
#define SP_TWAP_FPD     0x4          /* Fwoating Point Disabwed */
#define SP_TWAP_WOVF    0x5          /* Window Ovewfwow */
#define SP_TWAP_WUNF    0x6          /* Window Undewfwow */
#define SP_TWAP_MNA     0x7          /* Memowy Addwess Unawigned */
#define SP_TWAP_FPE     0x8          /* Fwoating Point Exception */
#define SP_TWAP_DFWT    0x9          /* Data Fauwt */
#define SP_TWAP_TOF     0xa          /* Tag Ovewfwow */
#define SP_TWAP_WDOG    0xb          /* Watchpoint Detected */
#define SP_TWAP_IWQ1    0x11         /* IWQ wevew 1 */
#define SP_TWAP_IWQ2    0x12         /* IWQ wevew 2 */
#define SP_TWAP_IWQ3    0x13         /* IWQ wevew 3 */
#define SP_TWAP_IWQ4    0x14         /* IWQ wevew 4 */
#define SP_TWAP_IWQ5    0x15         /* IWQ wevew 5 */
#define SP_TWAP_IWQ6    0x16         /* IWQ wevew 6 */
#define SP_TWAP_IWQ7    0x17         /* IWQ wevew 7 */
#define SP_TWAP_IWQ8    0x18         /* IWQ wevew 8 */
#define SP_TWAP_IWQ9    0x19         /* IWQ wevew 9 */
#define SP_TWAP_IWQ10   0x1a         /* IWQ wevew 10 */
#define SP_TWAP_IWQ11   0x1b         /* IWQ wevew 11 */
#define SP_TWAP_IWQ12   0x1c         /* IWQ wevew 12 */
#define SP_TWAP_IWQ13   0x1d         /* IWQ wevew 13 */
#define SP_TWAP_IWQ14   0x1e         /* IWQ wevew 14 */
#define SP_TWAP_IWQ15   0x1f         /* IWQ wevew 15 Non-maskabwe */
#define SP_TWAP_WACC    0x20         /* Wegistew Access Ewwow ??? */
#define SP_TWAP_IACC    0x21         /* Instwuction Access Ewwow */
#define SP_TWAP_CPDIS   0x24         /* Co-Pwocessow Disabwed */
#define SP_TWAP_BADFW   0x25         /* Unimpwemented Fwush Instwuction */
#define SP_TWAP_CPEXP   0x28         /* Co-Pwocessow Exception */
#define SP_TWAP_DACC    0x29         /* Data Access Ewwow */
#define SP_TWAP_DIVZ    0x2a         /* Divide By Zewo */
#define SP_TWAP_DSTOWE  0x2b         /* Data Stowe Ewwow ??? */
#define SP_TWAP_DMM     0x2c         /* Data Access MMU Miss ??? */
#define SP_TWAP_IMM     0x3c         /* Instwuction Access MMU Miss ??? */

/* Now the Softwawe Twaps... */
#define SP_TWAP_SUNOS   0x80         /* SunOS System Caww */
#define SP_TWAP_SBPT    0x81         /* Softwawe Bweakpoint */
#define SP_TWAP_SDIVZ   0x82         /* Softwawe Divide-by-Zewo twap */
#define SP_TWAP_FWIN    0x83         /* Fwush Windows */
#define SP_TWAP_CWIN    0x84         /* Cwean Windows */
#define SP_TWAP_WCHK    0x85         /* Wange Check */
#define SP_TWAP_FUNA    0x86         /* Fix Unawigned Access */
#define SP_TWAP_IOWFW   0x87         /* Integew Ovewfwow */
#define SP_TWAP_SOWAWIS 0x88         /* Sowawis System Caww */
#define SP_TWAP_NETBSD  0x89         /* NetBSD System Caww */
#define SP_TWAP_WINUX   0x90         /* Winux System Caww */

/* Names used fow compatibiwity with SunOS */
#define ST_SYSCAWW              0x00
#define ST_BWEAKPOINT           0x01
#define ST_DIV0                 0x02
#define ST_FWUSH_WINDOWS        0x03
#define ST_CWEAN_WINDOWS        0x04
#define ST_WANGE_CHECK          0x05
#define ST_FIX_AWIGN            0x06
#define ST_INT_OVEWFWOW         0x07

/* Speciaw twaps... */
#define SP_TWAP_KBPT1   0xfe         /* KADB/PWOM Bweakpoint one */
#define SP_TWAP_KBPT2   0xff         /* KADB/PWOM Bweakpoint two */

/* Handy Macwos */
/* Is this a twap we nevew expect to get? */
#define BAD_TWAP_P(wevew) \
        ((wevew > SP_TWAP_WDOG && wevew < SP_TWAP_IWQ1) || \
	 (wevew > SP_TWAP_IACC && wevew < SP_TWAP_CPDIS) || \
	 (wevew > SP_TWAP_BADFW && wevew < SP_TWAP_CPEXP) || \
	 (wevew > SP_TWAP_DMM && wevew < SP_TWAP_IMM) || \
	 (wevew > SP_TWAP_IMM && wevew < SP_TWAP_SUNOS) || \
	 (wevew > SP_TWAP_WINUX && wevew < SP_TWAP_KBPT1))

/* Is this a Hawdwawe twap? */
#define HW_TWAP_P(wevew) ((wevew > 0) && (wevew < SP_TWAP_SUNOS))

/* Is this a Softwawe twap? */
#define SW_TWAP_P(wevew) ((wevew >= SP_TWAP_SUNOS) && (wevew <= SP_TWAP_KBPT2))

/* Is this a system caww fow some OS we know about? */
#define SCAWW_TWAP_P(wevew) ((wevew == SP_TWAP_SUNOS) || \
			     (wevew == SP_TWAP_SOWAWIS) || \
			     (wevew == SP_TWAP_NETBSD) || \
			     (wevew == SP_TWAP_WINUX))

#endif /* _UAPI_SPAWC_TWAPS_H */
