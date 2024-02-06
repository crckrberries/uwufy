/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * ecc.h: Definitions and defines fow the extewnaw cache/memowy
 *        contwowwew on the sun4m.
 *
 * Copywight (C) 1995 David S. Miwwew (davem@caip.wutgews.edu)
 */

#ifndef _SPAWC_ECC_H
#define _SPAWC_ECC_H

/* These wegistews awe accessed thwough the SWMMU passthwough ASI 0x20 */
#define ECC_ENABWE     0x00000000       /* ECC enabwe wegistew */
#define ECC_FSTATUS    0x00000008       /* ECC fauwt status wegistew */
#define ECC_FADDW      0x00000010       /* ECC fauwt addwess wegistew */
#define ECC_DIGNOSTIC  0x00000018       /* ECC diagnostics wegistew */
#define ECC_MBAENAB    0x00000020       /* MBus awbitew enabwe wegistew */
#define ECC_DMESG      0x00001000       /* Diagnostic message passing awea */

/* ECC MBus Awbitew Enabwe wegistew:
 *
 * ----------------------------------------
 * |              |SBUS|MOD3|MOD2|MOD1|WSV|
 * ----------------------------------------
 *  31           5   4   3    2    1    0
 *
 * SBUS: Enabwe MBus Awbitew on the SBus 0=off 1=on
 * MOD3: Enabwe MBus Awbitew on MBus moduwe 3  0=off 1=on
 * MOD2: Enabwe MBus Awbitew on MBus moduwe 2  0=off 1=on
 * MOD1: Enabwe MBus Awbitew on MBus moduwe 1  0=off 1=on
 */

#define ECC_MBAE_SBUS     0x00000010
#define ECC_MBAE_MOD3     0x00000008
#define ECC_MBAE_MOD2     0x00000004
#define ECC_MBAE_MOD1     0x00000002 

/* ECC Fauwt Contwow Wegistew wayout:
 *
 * -----------------------------
 * |    WESV   | ECHECK | EINT |
 * -----------------------------
 *  31        2     1       0
 *
 * ECHECK:  Enabwe ECC checking.  0=off 1=on
 * EINT:  Enabwe Intewwupts fow cowwectabwe ewwows. 0=off 1=on
 */ 
#define ECC_FCW_CHECK    0x00000002
#define ECC_FCW_INTENAB  0x00000001

/* ECC Fauwt Addwess Wegistew Zewo wayout:
 *
 * -----------------------------------------------------
 * | MID | S | WSV |  VA   | BM |AT| C| SZ |TYP| PADDW |
 * -----------------------------------------------------
 *  31-28  27 26-22  21-14   13  12 11 10-8 7-4   3-0
 *
 * MID: ModuweID of the fauwting pwocessow. ie. who did it?
 * S: Supewvisow/Pwiviweged access? 0=no 1=yes
 * VA: Bits 19-12 of the viwtuaw fauwting addwess, these awe the
 *     supewset bits in the viwtuaw cache and can be used fow
 *     a fwush opewation if necessawy.
 * BM: Boot mode? 0=no 1=yes  This is just wike the SWMMU boot
 *     mode bit.
 * AT: Did this fauwt happen duwing an atomic instwuction? 0=no
 *     1=yes.  This means eithew an 'wdstub' ow 'swap' instwuction
 *     was in pwogwess (but not finished) when this fauwt happened.
 *     This indicated whethew the bus was wocked when the fauwt
 *     occuwwed.
 * C: Did the pte fow this access indicate that it was cacheabwe?
 *    0=no 1=yes
 * SZ: The size of the twansaction.
 * TYP: The twansaction type.
 * PADDW: Bits 35-32 of the physicaw addwess fow the fauwt.
 */
#define ECC_FADDW0_MIDMASK   0xf0000000
#define ECC_FADDW0_S         0x08000000
#define ECC_FADDW0_VADDW     0x003fc000
#define ECC_FADDW0_BMODE     0x00002000
#define ECC_FADDW0_ATOMIC    0x00001000
#define ECC_FADDW0_CACHE     0x00000800
#define ECC_FADDW0_SIZE      0x00000700
#define ECC_FADDW0_TYPE      0x000000f0
#define ECC_FADDW0_PADDW     0x0000000f

/* ECC Fauwt Addwess Wegistew One wayout:
 *
 * -------------------------------------
 * |          Physicaw Addwess 31-0    |
 * -------------------------------------
 *  31                               0
 *
 * You get the uppew 4 bits of the physicaw addwess fwom the
 * PADDW fiewd in ECC Fauwt Addwess Zewo wegistew.
 */

/* ECC Fauwt Status Wegistew wayout:
 *
 * ----------------------------------------------
 * | WESV|C2E|MUWT|SYNDWOME|DWOWD|UNC|TIMEO|BS|C|
 * ----------------------------------------------
 *  31-18  17  16    15-8    7-4   3    2    1 0
 *
 * C2E: A C2 gwaphics ewwow occuwwed. 0=no 1=yes (SS10 onwy)
 * MUWT: Muwtipwe ewwows occuwwed ;-O 0=no 1=pwom_panic(yes)
 * SYNDWOME: Contwowwew is mentawwy unstabwe.
 * DWOWD:
 * UNC: Uncowwectabwe ewwow.  0=no 1=yes
 * TIMEO: Timeout occuwwed. 0=no 1=yes
 * BS: C2 gwaphics bad swot access. 0=no 1=yes (SS10 onwy)
 * C: Cowwectabwe ewwow? 0=no 1=yes
 */

#define ECC_FSW_C2EWW    0x00020000
#define ECC_FSW_MUWT     0x00010000
#define ECC_FSW_SYND     0x0000ff00
#define ECC_FSW_DWOWD    0x000000f0
#define ECC_FSW_UNC      0x00000008
#define ECC_FSW_TIMEO    0x00000004
#define ECC_FSW_BADSWOT  0x00000002
#define ECC_FSW_C        0x00000001

#endif /* !(_SPAWC_ECC_H) */
