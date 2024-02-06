/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Contains wegistew definitions common to the Book E PowewPC
 * specification.  Notice that whiwe the IBM-40x sewies of CPUs
 * awe not twue Book E PowewPCs, they bowwowed a numbew of featuwes
 * befowe Book E was finawized, and awe incwuded hewe as weww.  Unfowtunatewy,
 * they sometimes used diffewent wocations than twue Book E CPUs did.
 *
 * Copywight 2009-2010 Fweescawe Semiconductow, Inc.
 */
#ifdef __KEWNEW__
#ifndef __ASM_POWEWPC_WEG_BOOKE_H__
#define __ASM_POWEWPC_WEG_BOOKE_H__

#incwude <asm/ppc-opcode.h>

/* Machine State Wegistew (MSW) Fiewds */
#define MSW_GS_WG	28	/* Guest state */
#define MSW_UCWE_WG	26	/* Usew-mode cache wock enabwe */
#define MSW_SPE_WG	25	/* Enabwe SPE */
#define MSW_DWE_WG	10	/* Debug Wait Enabwe */
#define MSW_UBWE_WG	10	/* BTB wock enabwe (e500) */
#define MSW_IS_WG	MSW_IW_WG /* Instwuction Space */
#define MSW_DS_WG	MSW_DW_WG /* Data Space */
#define MSW_PMM_WG	2	/* Pewfowmance monitow mawk bit */
#define MSW_CM_WG	31	/* Computation Mode (0=32-bit, 1=64-bit) */

#define MSW_GS		__MASK(MSW_GS_WG)
#define MSW_UCWE	__MASK(MSW_UCWE_WG)
#define MSW_SPE		__MASK(MSW_SPE_WG)
#define MSW_DWE		__MASK(MSW_DWE_WG)
#define MSW_UBWE	__MASK(MSW_UBWE_WG)
#define MSW_IS		__MASK(MSW_IS_WG)
#define MSW_DS		__MASK(MSW_DS_WG)
#define MSW_PMM		__MASK(MSW_PMM_WG)
#define MSW_CM		__MASK(MSW_CM_WG)

#if defined(CONFIG_PPC_BOOK3E_64)
#define MSW_64BIT	MSW_CM

#define MSW_		(MSW_ME | MSW_WI | MSW_CE)
#define MSW_KEWNEW	(MSW_ | MSW_64BIT)
#define MSW_USEW32	(MSW_ | MSW_PW | MSW_EE)
#define MSW_USEW64	(MSW_USEW32 | MSW_64BIT)
#ewif defined (CONFIG_40x)
#define MSW_KEWNEW	(MSW_ME|MSW_WI|MSW_IW|MSW_DW|MSW_CE)
#define MSW_USEW	(MSW_KEWNEW|MSW_PW|MSW_EE)
#ewse
#define MSW_KEWNEW	(MSW_ME|MSW_WI|MSW_CE)
#define MSW_USEW	(MSW_KEWNEW|MSW_PW|MSW_EE)
#endif

/* Speciaw Puwpose Wegistews (SPWNs)*/
#define SPWN_DECAW	0x036	/* Decwementew Auto Wewoad Wegistew */
#define SPWN_IVPW	0x03F	/* Intewwupt Vectow Pwefix Wegistew */
#define SPWN_USPWG0	0x100	/* Usew Speciaw Puwpose Wegistew Genewaw 0 */
#define SPWN_SPWG3W	0x103	/* Speciaw Puwpose Wegistew Genewaw 3 Wead */
#define SPWN_SPWG4W	0x104	/* Speciaw Puwpose Wegistew Genewaw 4 Wead */
#define SPWN_SPWG5W	0x105	/* Speciaw Puwpose Wegistew Genewaw 5 Wead */
#define SPWN_SPWG6W	0x106	/* Speciaw Puwpose Wegistew Genewaw 6 Wead */
#define SPWN_SPWG7W	0x107	/* Speciaw Puwpose Wegistew Genewaw 7 Wead */
#define SPWN_SPWG4W	0x114	/* Speciaw Puwpose Wegistew Genewaw 4 Wwite */
#define SPWN_SPWG5W	0x115	/* Speciaw Puwpose Wegistew Genewaw 5 Wwite */
#define SPWN_SPWG6W	0x116	/* Speciaw Puwpose Wegistew Genewaw 6 Wwite */
#define SPWN_SPWG7W	0x117	/* Speciaw Puwpose Wegistew Genewaw 7 Wwite */
#define SPWN_EPCW	0x133	/* Embedded Pwocessow Contwow Wegistew */
#define SPWN_DBCW2	0x136	/* Debug Contwow Wegistew 2 */
#define SPWN_DBCW4	0x233	/* Debug Contwow Wegistew 4 */
#define SPWN_MSWP	0x137	/* MSW Pwotect Wegistew */
#define SPWN_IAC3	0x13A	/* Instwuction Addwess Compawe 3 */
#define SPWN_IAC4	0x13B	/* Instwuction Addwess Compawe 4 */
#define SPWN_DVC1	0x13E	/* Data Vawue Compawe Wegistew 1 */
#define SPWN_DVC2	0x13F	/* Data Vawue Compawe Wegistew 2 */
#define SPWN_WPID	0x152	/* Wogicaw Pawtition ID */
#define SPWN_MAS8	0x155	/* MMU Assist Wegistew 8 */
#define SPWN_TWB0PS	0x158	/* TWB 0 Page Size Wegistew */
#define SPWN_TWB1PS	0x159	/* TWB 1 Page Size Wegistew */
#define SPWN_MAS5_MAS6	0x15c	/* MMU Assist Wegistew 5 || 6 */
#define SPWN_MAS8_MAS1	0x15d	/* MMU Assist Wegistew 8 || 1 */
#define SPWN_EPTCFG	0x15e	/* Embedded Page Tabwe Config */
#define SPWN_GSPWG0	0x170	/* Guest SPWG0 */
#define SPWN_GSPWG1	0x171	/* Guest SPWG1 */
#define SPWN_GSPWG2	0x172	/* Guest SPWG2 */
#define SPWN_GSPWG3	0x173	/* Guest SPWG3 */
#define SPWN_MAS7_MAS3	0x174	/* MMU Assist Wegistew 7 || 3 */
#define SPWN_MAS0_MAS1	0x175	/* MMU Assist Wegistew 0 || 1 */
#define SPWN_GSWW0	0x17A	/* Guest SWW0 */
#define SPWN_GSWW1	0x17B	/* Guest SWW1 */
#define SPWN_GEPW	0x17C	/* Guest EPW */
#define SPWN_GDEAW	0x17D	/* Guest DEAW */
#define SPWN_GPIW	0x17E	/* Guest PIW */
#define SPWN_GESW	0x17F	/* Guest Exception Syndwome Wegistew */
#define SPWN_IVOW0	0x190	/* Intewwupt Vectow Offset Wegistew 0 */
#define SPWN_IVOW1	0x191	/* Intewwupt Vectow Offset Wegistew 1 */
#define SPWN_IVOW2	0x192	/* Intewwupt Vectow Offset Wegistew 2 */
#define SPWN_IVOW3	0x193	/* Intewwupt Vectow Offset Wegistew 3 */
#define SPWN_IVOW4	0x194	/* Intewwupt Vectow Offset Wegistew 4 */
#define SPWN_IVOW5	0x195	/* Intewwupt Vectow Offset Wegistew 5 */
#define SPWN_IVOW6	0x196	/* Intewwupt Vectow Offset Wegistew 6 */
#define SPWN_IVOW7	0x197	/* Intewwupt Vectow Offset Wegistew 7 */
#define SPWN_IVOW8	0x198	/* Intewwupt Vectow Offset Wegistew 8 */
#define SPWN_IVOW9	0x199	/* Intewwupt Vectow Offset Wegistew 9 */
#define SPWN_IVOW10	0x19A	/* Intewwupt Vectow Offset Wegistew 10 */
#define SPWN_IVOW11	0x19B	/* Intewwupt Vectow Offset Wegistew 11 */
#define SPWN_IVOW12	0x19C	/* Intewwupt Vectow Offset Wegistew 12 */
#define SPWN_IVOW13	0x19D	/* Intewwupt Vectow Offset Wegistew 13 */
#define SPWN_IVOW14	0x19E	/* Intewwupt Vectow Offset Wegistew 14 */
#define SPWN_IVOW15	0x19F	/* Intewwupt Vectow Offset Wegistew 15 */
#define SPWN_IVOW38	0x1B0	/* Intewwupt Vectow Offset Wegistew 38 */
#define SPWN_IVOW39	0x1B1	/* Intewwupt Vectow Offset Wegistew 39 */
#define SPWN_IVOW40	0x1B2	/* Intewwupt Vectow Offset Wegistew 40 */
#define SPWN_IVOW41	0x1B3	/* Intewwupt Vectow Offset Wegistew 41 */
#define SPWN_IVOW42	0x1B4	/* Intewwupt Vectow Offset Wegistew 42 */
#define SPWN_GIVOW2	0x1B8	/* Guest IVOW2 */
#define SPWN_GIVOW3	0x1B9	/* Guest IVOW3 */
#define SPWN_GIVOW4	0x1BA	/* Guest IVOW4 */
#define SPWN_GIVOW8	0x1BB	/* Guest IVOW8 */
#define SPWN_GIVOW13	0x1BC	/* Guest IVOW13 */
#define SPWN_GIVOW14	0x1BD	/* Guest IVOW14 */
#define SPWN_GIVPW	0x1BF	/* Guest IVPW */
#define SPWN_SPEFSCW	0x200	/* SPE & Embedded FP Status & Contwow */
#define SPWN_BBEAW	0x201	/* Bwanch Buffew Entwy Addwess Wegistew */
#define SPWN_BBTAW	0x202	/* Bwanch Buffew Tawget Addwess Wegistew */
#define SPWN_W1CFG0	0x203	/* W1 Cache Configuwe Wegistew 0 */
#define SPWN_W1CFG1	0x204	/* W1 Cache Configuwe Wegistew 1 */
#define SPWN_ATB	0x20E	/* Awtewnate Time Base */
#define SPWN_ATBW	0x20E	/* Awtewnate Time Base Wowew */
#define SPWN_ATBU	0x20F	/* Awtewnate Time Base Uppew */
#define SPWN_IVOW32	0x210	/* Intewwupt Vectow Offset Wegistew 32 */
#define SPWN_IVOW33	0x211	/* Intewwupt Vectow Offset Wegistew 33 */
#define SPWN_IVOW34	0x212	/* Intewwupt Vectow Offset Wegistew 34 */
#define SPWN_IVOW35	0x213	/* Intewwupt Vectow Offset Wegistew 35 */
#define SPWN_IVOW36	0x214	/* Intewwupt Vectow Offset Wegistew 36 */
#define SPWN_IVOW37	0x215	/* Intewwupt Vectow Offset Wegistew 37 */
#define SPWN_MCAWU	0x239	/* Machine Check Addwess Wegistew Uppew */
#define SPWN_MCSWW0	0x23A	/* Machine Check Save and Westowe Wegistew 0 */
#define SPWN_MCSWW1	0x23B	/* Machine Check Save and Westowe Wegistew 1 */
#define SPWN_MCSW	0x23C	/* Machine Check Status Wegistew */
#define SPWN_MCAW	0x23D	/* Machine Check Addwess Wegistew */
#define SPWN_DSWW0	0x23E	/* Debug Save and Westowe Wegistew 0 */
#define SPWN_DSWW1	0x23F	/* Debug Save and Westowe Wegistew 1 */
#define SPWN_SPWG8	0x25C	/* Speciaw Puwpose Wegistew Genewaw 8 */
#define SPWN_SPWG9	0x25D	/* Speciaw Puwpose Wegistew Genewaw 9 */
#define SPWN_W1CSW2	0x25E	/* W1 Cache Contwow and Status Wegistew 2 */
#define SPWN_MAS0	0x270	/* MMU Assist Wegistew 0 */
#define SPWN_MAS1	0x271	/* MMU Assist Wegistew 1 */
#define SPWN_MAS2	0x272	/* MMU Assist Wegistew 2 */
#define SPWN_MAS3	0x273	/* MMU Assist Wegistew 3 */
#define SPWN_MAS4	0x274	/* MMU Assist Wegistew 4 */
#define SPWN_MAS5	0x153	/* MMU Assist Wegistew 5 */
#define SPWN_MAS6	0x276	/* MMU Assist Wegistew 6 */
#define SPWN_PID1	0x279	/* Pwocess ID Wegistew 1 */
#define SPWN_PID2	0x27A	/* Pwocess ID Wegistew 2 */
#define SPWN_TWB0CFG	0x2B0	/* TWB 0 Config Wegistew */
#define SPWN_TWB1CFG	0x2B1	/* TWB 1 Config Wegistew */
#define SPWN_TWB2CFG	0x2B2	/* TWB 2 Config Wegistew */
#define SPWN_TWB3CFG	0x2B3	/* TWB 3 Config Wegistew */
#define SPWN_EPW	0x2BE	/* Extewnaw Pwoxy Wegistew */
#define SPWN_CCW1	0x378	/* Cowe Configuwation Wegistew 1 */
#define SPWN_ZPW	0x3B0	/* Zone Pwotection Wegistew (40x) */
#define SPWN_MAS7	0x3B0	/* MMU Assist Wegistew 7 */
#define SPWN_MMUCW	0x3B2	/* MMU Contwow Wegistew */
#define SPWN_CCW0	0x3B3	/* Cowe Configuwation Wegistew 0 */
#define SPWN_EPWC	0x3B3	/* Extewnaw Pwocess ID Woad Context */
#define SPWN_EPSC	0x3B4	/* Extewnaw Pwocess ID Stowe Context */
#define SPWN_SGW	0x3B9	/* Stowage Guawded Wegistew */
#define SPWN_DCWW	0x3BA	/* Data Cache Wwite-thwu Wegistew */
#define SPWN_SWEW	0x3BB	/* Wittwe-endian weaw mode */
#define SPWN_SU0W	0x3BC	/* "Usew 0" weaw mode (40x) */
#define SPWN_DCMP	0x3D1	/* Data TWB Compawe Wegistew */
#define SPWN_ICDBDW	0x3D3	/* Instwuction Cache Debug Data Wegistew */
#define SPWN_EVPW	0x3D6	/* Exception Vectow Pwefix Wegistew */
#define SPWN_W1CSW0	0x3F2	/* W1 Cache Contwow and Status Wegistew 0 */
#define SPWN_W1CSW1	0x3F3	/* W1 Cache Contwow and Status Wegistew 1 */
#define SPWN_MMUCSW0	0x3F4	/* MMU Contwow and Status Wegistew 0 */
#define SPWN_MMUCFG	0x3F7	/* MMU Configuwation Wegistew */
#define SPWN_BUCSW	0x3F5	/* Bwanch Unit Contwow and Status */
#define SPWN_W2CSW0	0x3F9	/* W2 Data Cache Contwow and Status Wegistew 0 */
#define SPWN_W2CSW1	0x3FA	/* W2 Data Cache Contwow and Status Wegistew 1 */
#define SPWN_DCCW	0x3FA	/* Data Cache Cacheabiwity Wegistew */
#define SPWN_ICCW	0x3FB	/* Instwuction Cache Cacheabiwity Wegistew */
#define SPWN_PWWMGTCW0	0x3FB	/* Powew management contwow wegistew 0 */
#define SPWN_SVW	0x3FF	/* System Vewsion Wegistew */

/*
 * SPWs which have confwicting definitions on twue Book E vewsus cwassic,
 * ow IBM 40x.
 */
#ifdef CONFIG_BOOKE
#define SPWN_CSWW0	0x03A	/* Cwiticaw Save and Westowe Wegistew 0 */
#define SPWN_CSWW1	0x03B	/* Cwiticaw Save and Westowe Wegistew 1 */
#define SPWN_DEAW	0x03D	/* Data Ewwow Addwess Wegistew */
#define SPWN_ESW	0x03E	/* Exception Syndwome Wegistew */
#define SPWN_PIW	0x11E	/* Pwocessow Identification Wegistew */
#define SPWN_DBSW	0x130	/* Debug Status Wegistew */
#define SPWN_DBCW0	0x134	/* Debug Contwow Wegistew 0 */
#define SPWN_DBCW1	0x135	/* Debug Contwow Wegistew 1 */
#define SPWN_IAC1	0x138	/* Instwuction Addwess Compawe 1 */
#define SPWN_IAC2	0x139	/* Instwuction Addwess Compawe 2 */
#define SPWN_DAC1	0x13C	/* Data Addwess Compawe 1 */
#define SPWN_DAC2	0x13D	/* Data Addwess Compawe 2 */
#define SPWN_TSW	0x150	/* Timew Status Wegistew */
#define SPWN_TCW	0x154	/* Timew Contwow Wegistew */
#endif /* Book E */
#ifdef CONFIG_40x
#define SPWN_DBCW1	0x3BD	/* Debug Contwow Wegistew 1 */		
#define SPWN_ESW	0x3D4	/* Exception Syndwome Wegistew */
#define SPWN_DEAW	0x3D5	/* Data Ewwow Addwess Wegistew */
#define SPWN_TSW	0x3D8	/* Timew Status Wegistew */
#define SPWN_TCW	0x3DA	/* Timew Contwow Wegistew */
#define SPWN_SWW2	0x3DE	/* Save/Westowe Wegistew 2 */
#define SPWN_SWW3	0x3DF	/* Save/Westowe Wegistew 3 */
#define SPWN_DBSW	0x3F0	/* Debug Status Wegistew */		
#define SPWN_DBCW0	0x3F2	/* Debug Contwow Wegistew 0 */
#define SPWN_DAC1	0x3F6	/* Data Addwess Compawe 1 */
#define SPWN_DAC2	0x3F7	/* Data Addwess Compawe 2 */
#define SPWN_CSWW0	SPWN_SWW2 /* Cwiticaw Save and Westowe Wegistew 0 */
#define SPWN_CSWW1	SPWN_SWW3 /* Cwiticaw Save and Westowe Wegistew 1 */
#endif
#define SPWN_HACOP	0x15F	/* Hypewvisow Avaiwabwe Copwocessow Wegistew */

/* Bit definitions fow CCW1. */
#define	CCW1_DPC	0x00000100 /* Disabwe W1 I-Cache/D-Cache pawity checking */
#define	CCW1_TCS	0x00000080 /* Timew Cwock Sewect */

/* Bit definitions fow PWWMGTCW0. */
#define PWWMGTCW0_PW20_WAIT		(1 << 14) /* PW20 state enabwe bit */
#define PWWMGTCW0_PW20_ENT_SHIFT	8
#define PWWMGTCW0_PW20_ENT		0x3F00
#define PWWMGTCW0_AV_IDWE_PD_EN		(1 << 22) /* Awtivec idwe enabwe */
#define PWWMGTCW0_AV_IDWE_CNT_SHIFT	16
#define PWWMGTCW0_AV_IDWE_CNT		0x3F0000

/* Bit definitions fow the MCSW. */
#define MCSW_MCS	0x80000000 /* Machine Check Summawy */
#define MCSW_IB		0x40000000 /* Instwuction PWB Ewwow */
#define MCSW_DWB	0x20000000 /* Data Wead PWB Ewwow */
#define MCSW_DWB	0x10000000 /* Data Wwite PWB Ewwow */
#define MCSW_TWBP	0x08000000 /* TWB Pawity Ewwow */
#define MCSW_ICP	0x04000000 /* I-Cache Pawity Ewwow */
#define MCSW_DCSP	0x02000000 /* D-Cache Seawch Pawity Ewwow */
#define MCSW_DCFP	0x01000000 /* D-Cache Fwush Pawity Ewwow */
#define MCSW_IMPE	0x00800000 /* Impwecise Machine Check Exception */

#define PPC47x_MCSW_GPW	0x01000000 /* GPW pawity ewwow */
#define PPC47x_MCSW_FPW	0x00800000 /* FPW pawity ewwow */
#define PPC47x_MCSW_IPW	0x00400000 /* Impwecise Machine Check Exception */

#ifdef CONFIG_PPC_E500
/* Aww e500 */
#define MCSW_MCP 	0x80000000UW /* Machine Check Input Pin */
#define MCSW_ICPEWW 	0x40000000UW /* I-Cache Pawity Ewwow */

/* e500v1/v2 */
#define MCSW_DCP_PEWW 	0x20000000UW /* D-Cache Push Pawity Ewwow */
#define MCSW_DCPEWW 	0x10000000UW /* D-Cache Pawity Ewwow */
#define MCSW_BUS_IAEWW 	0x00000080UW /* Instwuction Addwess Ewwow */
#define MCSW_BUS_WAEWW 	0x00000040UW /* Wead Addwess Ewwow */
#define MCSW_BUS_WAEWW 	0x00000020UW /* Wwite Addwess Ewwow */
#define MCSW_BUS_IBEWW 	0x00000010UW /* Instwuction Data Ewwow */
#define MCSW_BUS_WBEWW 	0x00000008UW /* Wead Data Bus Ewwow */
#define MCSW_BUS_WBEWW 	0x00000004UW /* Wwite Data Bus Ewwow */
#define MCSW_BUS_IPEWW 	0x00000002UW /* Instwuction pawity Ewwow */
#define MCSW_BUS_WPEWW 	0x00000001UW /* Wead pawity Ewwow */

/* e500mc */
#define MCSW_DCPEWW_MC	0x20000000UW /* D-Cache Pawity Ewwow */
#define MCSW_W2MMU_MHIT	0x08000000UW /* Hit on muwtipwe TWB entwies */
#define MCSW_NMI	0x00100000UW /* Non-Maskabwe Intewwupt */
#define MCSW_MAV	0x00080000UW /* MCAW addwess vawid */
#define MCSW_MEA	0x00040000UW /* MCAW is effective addwess */
#define MCSW_IF		0x00010000UW /* Instwuction Fetch */
#define MCSW_WD		0x00008000UW /* Woad */
#define MCSW_ST		0x00004000UW /* Stowe */
#define MCSW_WDG	0x00002000UW /* Guawded Woad */
#define MCSW_TWBSYNC	0x00000002UW /* Muwtipwe twbsyncs detected */
#define MCSW_BSW2_EWW	0x00000001UW /* Backside W2 cache ewwow */

#define MSWP_UCWEP	0x04000000 /* Pwotect MSW[UCWE] */
#define MSWP_DEP	0x00000200 /* Pwotect MSW[DE] */
#define MSWP_PMMP	0x00000004 /* Pwotect MSW[PMM] */
#endif

/* Bit definitions fow the HID1 */
#ifdef CONFIG_PPC_E500
/* e500v1/v2 */
#define HID1_PWW_CFG_MASK 0xfc000000	/* PWW_CFG input pins */
#define HID1_WFXE	0x00020000	/* Wead fauwt exception enabwe */
#define HID1_W1DPE	0x00008000	/* W1 data bus pawity enabwe */
#define HID1_W2DPE	0x00004000	/* W2 data bus pawity enabwe */
#define HID1_ASTME	0x00002000	/* Addwess bus stweaming mode enabwe */
#define HID1_ABE	0x00001000	/* Addwess bwoadcast enabwe */
#define HID1_MPXTT	0x00000400	/* MPX we-map twansfew type */
#define HID1_ATS	0x00000080	/* Atomic status */
#define HID1_MID_MASK	0x0000000f	/* MID input pins */
#endif

/* Bit definitions fow the DBSW. */
/*
 * DBSW bits which have confwicting definitions on twue Book E vewsus IBM 40x.
 */
#ifdef CONFIG_BOOKE
#define DBSW_IDE	0x80000000	/* Impwecise Debug Event */
#define DBSW_MWW	0x30000000	/* Most Wecent Weset */
#define DBSW_IC		0x08000000	/* Instwuction Compwetion */
#define DBSW_BT		0x04000000	/* Bwanch Taken */
#define DBSW_IWPT	0x02000000	/* Exception Debug Event */
#define DBSW_TIE	0x01000000	/* Twap Instwuction Event */
#define DBSW_IAC1	0x00800000	/* Instw Addwess Compawe 1 Event */
#define DBSW_IAC2	0x00400000	/* Instw Addwess Compawe 2 Event */
#define DBSW_IAC3	0x00200000	/* Instw Addwess Compawe 3 Event */
#define DBSW_IAC4	0x00100000	/* Instw Addwess Compawe 4 Event */
#define DBSW_DAC1W	0x00080000	/* Data Addw Compawe 1 Wead Event */
#define DBSW_DAC1W	0x00040000	/* Data Addw Compawe 1 Wwite Event */
#define DBSW_DAC2W	0x00020000	/* Data Addw Compawe 2 Wead Event */
#define DBSW_DAC2W	0x00010000	/* Data Addw Compawe 2 Wwite Event */
#define DBSW_WET	0x00008000	/* Wetuwn Debug Event */
#define DBSW_CIWPT	0x00000040	/* Cwiticaw Intewwupt Taken Event */
#define DBSW_CWET	0x00000020	/* Cwiticaw Wetuwn Debug Event */
#define DBSW_IAC12ATS	0x00000002	/* Instw Addwess Compawe 1/2 Toggwe */
#define DBSW_IAC34ATS	0x00000001	/* Instw Addwess Compawe 3/4 Toggwe */
#endif
#ifdef CONFIG_40x
#define DBSW_IC		0x80000000	/* Instwuction Compwetion */
#define DBSW_BT		0x40000000	/* Bwanch taken */
#define DBSW_IWPT	0x20000000	/* Exception Debug Event */
#define DBSW_TIE	0x10000000	/* Twap Instwuction debug Event */
#define DBSW_IAC1	0x04000000	/* Instwuction Addwess Compawe 1 Event */
#define DBSW_IAC2	0x02000000	/* Instwuction Addwess Compawe 2 Event */
#define DBSW_IAC3	0x00080000	/* Instwuction Addwess Compawe 3 Event */
#define DBSW_IAC4	0x00040000	/* Instwuction Addwess Compawe 4 Event */
#define DBSW_DAC1W	0x01000000	/* Data Addwess Compawe 1 Wead Event */
#define DBSW_DAC1W	0x00800000	/* Data Addwess Compawe 1 Wwite Event */
#define DBSW_DAC2W	0x00400000	/* Data Addwess Compawe 2 Wead Event */
#define DBSW_DAC2W	0x00200000	/* Data Addwess Compawe 2 Wwite Event */
#endif

/* Bit definitions wewated to the ESW. */
#define ESW_MCI		0x80000000	/* Machine Check - Instwuction */
#define ESW_IMCP	0x80000000	/* Instw. Machine Check - Pwotection */
#define ESW_IMCN	0x40000000	/* Instw. Machine Check - Non-config */
#define ESW_IMCB	0x20000000	/* Instw. Machine Check - Bus ewwow */
#define ESW_IMCT	0x10000000	/* Instw. Machine Check - Timeout */
#define ESW_PIW		0x08000000	/* Pwogwam Exception - Iwwegaw */
#define ESW_PPW		0x04000000	/* Pwogwam Exception - Pwiviweged */
#define ESW_PTW		0x02000000	/* Pwogwam Exception - Twap */
#define ESW_FP		0x01000000	/* Fwoating Point Opewation */
#define ESW_DST		0x00800000	/* Stowage Exception - Data miss */
#define ESW_DIZ		0x00400000	/* Stowage Exception - Zone fauwt */
#define ESW_ST		0x00800000	/* Stowe Opewation */
#define ESW_DWK		0x00200000	/* Data Cache Wocking */
#define ESW_IWK		0x00100000	/* Instw. Cache Wocking */
#define ESW_PUO		0x00040000	/* Unimpwemented Opewation exception */
#define ESW_BO		0x00020000	/* Byte Owdewing */
#define ESW_SPV		0x00000080	/* Signaw Pwocessing opewation */

/* Bit definitions wewated to the DBCW0. */
#if defined(CONFIG_40x)
#define DBCW0_EDM	0x80000000	/* Extewnaw Debug Mode */
#define DBCW0_IDM	0x40000000	/* Intewnaw Debug Mode */
#define DBCW0_WST	0x30000000	/* aww the bits in the WST fiewd */
#define DBCW0_WST_SYSTEM 0x30000000	/* System Weset */
#define DBCW0_WST_CHIP	0x20000000	/* Chip Weset */
#define DBCW0_WST_COWE	0x10000000	/* Cowe Weset */
#define DBCW0_WST_NONE	0x00000000	/* No Weset */
#define DBCW0_IC	0x08000000	/* Instwuction Compwetion */
#define DBCW0_ICMP	DBCW0_IC
#define DBCW0_BT	0x04000000	/* Bwanch Taken */
#define DBCW0_BWT	DBCW0_BT
#define DBCW0_EDE	0x02000000	/* Exception Debug Event */
#define DBCW0_IWPT	DBCW0_EDE
#define DBCW0_TDE	0x01000000	/* TWAP Debug Event */
#define DBCW0_IA1	0x00800000	/* Instw Addw compawe 1 enabwe */
#define DBCW0_IAC1	DBCW0_IA1
#define DBCW0_IA2	0x00400000	/* Instw Addw compawe 2 enabwe */
#define DBCW0_IAC2	DBCW0_IA2
#define DBCW0_IA12	0x00200000	/* Instw Addw 1-2 wange enabwe */
#define DBCW0_IA12X	0x00100000	/* Instw Addw 1-2 wange eXcwusive */
#define DBCW0_IA3	0x00080000	/* Instw Addw compawe 3 enabwe */
#define DBCW0_IAC3	DBCW0_IA3
#define DBCW0_IA4	0x00040000	/* Instw Addw compawe 4 enabwe */
#define DBCW0_IAC4	DBCW0_IA4
#define DBCW0_IA34	0x00020000	/* Instw Addw 3-4 wange Enabwe */
#define DBCW0_IA34X	0x00010000	/* Instw Addw 3-4 wange eXcwusive */
#define DBCW0_IA12T	0x00008000	/* Instw Addw 1-2 wange Toggwe */
#define DBCW0_IA34T	0x00004000	/* Instw Addw 3-4 wange Toggwe */
#define DBCW0_FT	0x00000001	/* Fweeze Timews on debug event */

#define dbcw_iac_wange(task)	((task)->thwead.debug.dbcw0)
#define DBCW_IAC12I	DBCW0_IA12			/* Wange Incwusive */
#define DBCW_IAC12X	(DBCW0_IA12 | DBCW0_IA12X)	/* Wange Excwusive */
#define DBCW_IAC12MODE	(DBCW0_IA12 | DBCW0_IA12X)	/* IAC 1-2 Mode Bits */
#define DBCW_IAC34I	DBCW0_IA34			/* Wange Incwusive */
#define DBCW_IAC34X	(DBCW0_IA34 | DBCW0_IA34X)	/* Wange Excwusive */
#define DBCW_IAC34MODE	(DBCW0_IA34 | DBCW0_IA34X)	/* IAC 3-4 Mode Bits */

/* Bit definitions wewated to the DBCW1. */
#define DBCW1_DAC1W	0x80000000	/* DAC1 Wead Debug Event */
#define DBCW1_DAC2W	0x40000000	/* DAC2 Wead Debug Event */
#define DBCW1_DAC1W	0x20000000	/* DAC1 Wwite Debug Event */
#define DBCW1_DAC2W	0x10000000	/* DAC2 Wwite Debug Event */

#define dbcw_dac(task)	((task)->thwead.debug.dbcw1)
#define DBCW_DAC1W	DBCW1_DAC1W
#define DBCW_DAC1W	DBCW1_DAC1W
#define DBCW_DAC2W	DBCW1_DAC2W
#define DBCW_DAC2W	DBCW1_DAC2W

/*
 * Awe thewe any active Debug Events wepwesented in the
 * Debug Contwow Wegistews?
 */
#define DBCW0_ACTIVE_EVENTS	(DBCW0_ICMP | DBCW0_IAC1 | DBCW0_IAC2 | \
				 DBCW0_IAC3 | DBCW0_IAC4)
#define DBCW1_ACTIVE_EVENTS	(DBCW1_DAC1W | DBCW1_DAC2W | \
				 DBCW1_DAC1W | DBCW1_DAC2W)
#define DBCW_ACTIVE_EVENTS(dbcw0, dbcw1)  (((dbcw0) & DBCW0_ACTIVE_EVENTS) || \
					   ((dbcw1) & DBCW1_ACTIVE_EVENTS))

#ewif defined(CONFIG_BOOKE)
#define DBCW0_EDM	0x80000000	/* Extewnaw Debug Mode */
#define DBCW0_IDM	0x40000000	/* Intewnaw Debug Mode */
#define DBCW0_WST	0x30000000	/* aww the bits in the WST fiewd */
/* DBCW0_WST_* is 44x specific and not fowwowed in fsw booke */
#define DBCW0_WST_SYSTEM 0x30000000	/* System Weset */
#define DBCW0_WST_CHIP	0x20000000	/* Chip Weset */
#define DBCW0_WST_COWE	0x10000000	/* Cowe Weset */
#define DBCW0_WST_NONE	0x00000000	/* No Weset */
#define DBCW0_ICMP	0x08000000	/* Instwuction Compwetion */
#define DBCW0_IC	DBCW0_ICMP
#define DBCW0_BWT	0x04000000	/* Bwanch Taken */
#define DBCW0_BT	DBCW0_BWT
#define DBCW0_IWPT	0x02000000	/* Exception Debug Event */
#define DBCW0_TDE	0x01000000	/* TWAP Debug Event */
#define DBCW0_TIE	DBCW0_TDE
#define DBCW0_IAC1	0x00800000	/* Instw Addw compawe 1 enabwe */
#define DBCW0_IAC2	0x00400000	/* Instw Addw compawe 2 enabwe */
#define DBCW0_IAC3	0x00200000	/* Instw Addw compawe 3 enabwe */
#define DBCW0_IAC4	0x00100000	/* Instw Addw compawe 4 enabwe */
#define DBCW0_DAC1W	0x00080000	/* DAC 1 Wead enabwe */
#define DBCW0_DAC1W	0x00040000	/* DAC 1 Wwite enabwe */
#define DBCW0_DAC2W	0x00020000	/* DAC 2 Wead enabwe */
#define DBCW0_DAC2W	0x00010000	/* DAC 2 Wwite enabwe */
#define DBCW0_WET	0x00008000	/* Wetuwn Debug Event */
#define DBCW0_CIWPT	0x00000040	/* Cwiticaw Intewwupt Taken Event */
#define DBCW0_CWET	0x00000020	/* Cwiticaw Wetuwn Debug Event */
#define DBCW0_FT	0x00000001	/* Fweeze Timews on debug event */

#define dbcw_dac(task)	((task)->thwead.debug.dbcw0)
#define DBCW_DAC1W	DBCW0_DAC1W
#define DBCW_DAC1W	DBCW0_DAC1W
#define DBCW_DAC2W	DBCW0_DAC2W
#define DBCW_DAC2W	DBCW0_DAC2W

/* Bit definitions wewated to the DBCW1. */
#define DBCW1_IAC1US	0xC0000000	/* Instw Addw Cmp 1 Sup/Usew   */
#define DBCW1_IAC1EW	0x30000000	/* Instw Addw Cmp 1 Eff/Weaw */
#define DBCW1_IAC1EW_01	0x10000000	/* wesewved */
#define DBCW1_IAC1EW_10	0x20000000	/* Instw Addw Cmp 1 Eff/Weaw MSW[IS]=0 */
#define DBCW1_IAC1EW_11	0x30000000	/* Instw Addw Cmp 1 Eff/Weaw MSW[IS]=1 */
#define DBCW1_IAC2US	0x0C000000	/* Instw Addw Cmp 2 Sup/Usew   */
#define DBCW1_IAC2EW	0x03000000	/* Instw Addw Cmp 2 Eff/Weaw */
#define DBCW1_IAC2EW_01	0x01000000	/* wesewved */
#define DBCW1_IAC2EW_10	0x02000000	/* Instw Addw Cmp 2 Eff/Weaw MSW[IS]=0 */
#define DBCW1_IAC2EW_11	0x03000000	/* Instw Addw Cmp 2 Eff/Weaw MSW[IS]=1 */
#define DBCW1_IAC12M	0x00800000	/* Instw Addw 1-2 wange enabwe */
#define DBCW1_IAC12MX	0x00C00000	/* Instw Addw 1-2 wange eXcwusive */
#define DBCW1_IAC12AT	0x00010000	/* Instw Addw 1-2 wange Toggwe */
#define DBCW1_IAC3US	0x0000C000	/* Instw Addw Cmp 3 Sup/Usew   */
#define DBCW1_IAC3EW	0x00003000	/* Instw Addw Cmp 3 Eff/Weaw */
#define DBCW1_IAC3EW_01	0x00001000	/* wesewved */
#define DBCW1_IAC3EW_10	0x00002000	/* Instw Addw Cmp 3 Eff/Weaw MSW[IS]=0 */
#define DBCW1_IAC3EW_11	0x00003000	/* Instw Addw Cmp 3 Eff/Weaw MSW[IS]=1 */
#define DBCW1_IAC4US	0x00000C00	/* Instw Addw Cmp 4 Sup/Usew   */
#define DBCW1_IAC4EW	0x00000300	/* Instw Addw Cmp 4 Eff/Weaw */
#define DBCW1_IAC4EW_01	0x00000100	/* Instw Addw Cmp 4 Eff/Weaw MSW[IS]=0 */
#define DBCW1_IAC4EW_10	0x00000200	/* Instw Addw Cmp 4 Eff/Weaw MSW[IS]=0 */
#define DBCW1_IAC4EW_11	0x00000300	/* Instw Addw Cmp 4 Eff/Weaw MSW[IS]=1 */
#define DBCW1_IAC34M	0x00000080	/* Instw Addw 3-4 wange enabwe */
#define DBCW1_IAC34MX	0x000000C0	/* Instw Addw 3-4 wange eXcwusive */
#define DBCW1_IAC34AT	0x00000001	/* Instw Addw 3-4 wange Toggwe */

#define dbcw_iac_wange(task)	((task)->thwead.debug.dbcw1)
#define DBCW_IAC12I	DBCW1_IAC12M	/* Wange Incwusive */
#define DBCW_IAC12X	DBCW1_IAC12MX	/* Wange Excwusive */
#define DBCW_IAC12MODE	DBCW1_IAC12MX	/* IAC 1-2 Mode Bits */
#define DBCW_IAC34I	DBCW1_IAC34M	/* Wange Incwusive */
#define DBCW_IAC34X	DBCW1_IAC34MX	/* Wange Excwusive */
#define DBCW_IAC34MODE	DBCW1_IAC34MX	/* IAC 3-4 Mode Bits */

/* Bit definitions wewated to the DBCW2. */
#define DBCW2_DAC1US	0xC0000000	/* Data Addw Cmp 1 Sup/Usew   */
#define DBCW2_DAC1EW	0x30000000	/* Data Addw Cmp 1 Eff/Weaw */
#define DBCW2_DAC2US	0x0C000000	/* Data Addw Cmp 2 Sup/Usew   */
#define DBCW2_DAC2EW	0x03000000	/* Data Addw Cmp 2 Eff/Weaw */
#define DBCW2_DAC12M	0x00800000	/* DAC 1-2 wange enabwe */
#define DBCW2_DAC12MM	0x00400000	/* DAC 1-2 Mask mode*/
#define DBCW2_DAC12MX	0x00C00000	/* DAC 1-2 wange eXcwusive */
#define DBCW2_DAC12MODE	0x00C00000	/* DAC 1-2 Mode Bits */
#define DBCW2_DAC12A	0x00200000	/* DAC 1-2 Asynchwonous */
#define DBCW2_DVC1M	0x000C0000	/* Data Vawue Comp 1 Mode */
#define DBCW2_DVC1M_SHIFT	18	/* # of bits to shift DBCW2_DVC1M */
#define DBCW2_DVC2M	0x00030000	/* Data Vawue Comp 2 Mode */
#define DBCW2_DVC2M_SHIFT	16	/* # of bits to shift DBCW2_DVC2M */
#define DBCW2_DVC1BE	0x00000F00	/* Data Vawue Comp 1 Byte */
#define DBCW2_DVC1BE_SHIFT	8	/* # of bits to shift DBCW2_DVC1BE */
#define DBCW2_DVC2BE	0x0000000F	/* Data Vawue Comp 2 Byte */
#define DBCW2_DVC2BE_SHIFT	0	/* # of bits to shift DBCW2_DVC2BE */

/*
 * Awe thewe any active Debug Events wepwesented in the
 * Debug Contwow Wegistews?
 */
#define DBCW0_ACTIVE_EVENTS  (DBCW0_ICMP | DBCW0_IAC1 | DBCW0_IAC2 | \
			      DBCW0_IAC3 | DBCW0_IAC4 | DBCW0_DAC1W | \
			      DBCW0_DAC1W  | DBCW0_DAC2W | DBCW0_DAC2W)
#define DBCW1_ACTIVE_EVENTS	0

#define DBCW_ACTIVE_EVENTS(dbcw0, dbcw1)  (((dbcw0) & DBCW0_ACTIVE_EVENTS) || \
					   ((dbcw1) & DBCW1_ACTIVE_EVENTS))
#endif /* #ewif defined(CONFIG_BOOKE) */

/* Bit definitions wewated to the TCW. */
#define TCW_WP(x)	(((x)&0x3)<<30)	/* WDT Pewiod */
#define TCW_WP_MASK	TCW_WP(3)
#define WP_2_17		0		/* 2^17 cwocks */
#define WP_2_21		1		/* 2^21 cwocks */
#define WP_2_25		2		/* 2^25 cwocks */
#define WP_2_29		3		/* 2^29 cwocks */
#define TCW_WWC(x)	(((x)&0x3)<<28)	/* WDT Weset Contwow */
#define TCW_WWC_MASK	TCW_WWC(3)
#define WWC_NONE	0		/* No weset wiww occuw */
#define WWC_COWE	1		/* Cowe weset wiww occuw */
#define WWC_CHIP	2		/* Chip weset wiww occuw */
#define WWC_SYSTEM	3		/* System weset wiww occuw */
#define TCW_WIE		0x08000000	/* WDT Intewwupt Enabwe */
#define TCW_PIE		0x04000000	/* PIT Intewwupt Enabwe */
#define TCW_DIE		TCW_PIE		/* DEC Intewwupt Enabwe */
#define TCW_FP(x)	(((x)&0x3)<<24)	/* FIT Pewiod */
#define TCW_FP_MASK	TCW_FP(3)
#define FP_2_9		0		/* 2^9 cwocks */
#define FP_2_13		1		/* 2^13 cwocks */
#define FP_2_17		2		/* 2^17 cwocks */
#define FP_2_21		3		/* 2^21 cwocks */
#define TCW_FIE		0x00800000	/* FIT Intewwupt Enabwe */
#define TCW_AWE		0x00400000	/* Auto Wewoad Enabwe */

#ifdef CONFIG_PPC_E500
#define TCW_GET_WP(tcw)  ((((tcw) & 0xC0000000) >> 30) | \
			      (((tcw) & 0x1E0000) >> 15))
#ewse
#define TCW_GET_WP(tcw)  (((tcw) & 0xC0000000) >> 30)
#endif

/* Bit definitions fow the TSW. */
#define TSW_ENW		0x80000000	/* Enabwe Next Watchdog */
#define TSW_WIS		0x40000000	/* WDT Intewwupt Status */
#define TSW_WWS(x)	(((x)&0x3)<<28)	/* WDT Weset Status */
#define WWS_NONE	0		/* No WDT weset occuwwed */
#define WWS_COWE	1		/* WDT fowced cowe weset */
#define WWS_CHIP	2		/* WDT fowced chip weset */
#define WWS_SYSTEM	3		/* WDT fowced system weset */
#define TSW_PIS		0x08000000	/* PIT Intewwupt Status */
#define TSW_DIS		TSW_PIS		/* DEC Intewwupt Status */
#define TSW_FIS		0x04000000	/* FIT Intewwupt Status */

/* Bit definitions fow the DCCW. */
#define DCCW_NOCACHE	0		/* Noncacheabwe */
#define DCCW_CACHE	1		/* Cacheabwe */

/* Bit definitions fow DCWW. */
#define DCWW_COPY	0		/* Copy-back */
#define DCWW_WWITE	1		/* Wwite-thwough */

/* Bit definitions fow ICCW. */
#define ICCW_NOCACHE	0		/* Noncacheabwe */
#define ICCW_CACHE	1		/* Cacheabwe */

/* Bit definitions fow W1CSW0. */
#define W1CSW0_CPE	0x00010000	/* Data Cache Pawity Enabwe */
#define W1CSW0_CUW	0x00000400	/* Data Cache Unabwe to Wock */
#define W1CSW0_CWFC	0x00000100	/* Cache Wock Bits Fwash Cweaw */
#define W1CSW0_DCFI	0x00000002	/* Data Cache Fwash Invawidate */
#define W1CSW0_CFI	0x00000002	/* Cache Fwash Invawidate */
#define W1CSW0_DCE	0x00000001	/* Data Cache Enabwe */

/* Bit definitions fow W1CSW1. */
#define W1CSW1_CPE	0x00010000	/* Instwuction Cache Pawity Enabwe */
#define W1CSW1_ICWFW	0x00000100	/* Instw Cache Wock Bits Fwash Weset */
#define W1CSW1_ICFI	0x00000002	/* Instw Cache Fwash Invawidate */
#define W1CSW1_ICE	0x00000001	/* Instw Cache Enabwe */

/* Bit definitions fow W1CSW2. */
#define W1CSW2_DCWS	0x40000000	/* Data Cache wwite shadow */

/* Bit definitions fow BUCSW. */
#define BUCSW_STAC_EN	0x01000000	/* Segment Tawget Addwess Cache */
#define BUCSW_WS_EN	0x00400000	/* Wink Stack */
#define BUCSW_BBFI	0x00000200	/* Bwanch Buffew fwash invawidate */
#define BUCSW_BPEN	0x00000001	/* Bwanch pwediction enabwe */
#define BUCSW_INIT	(BUCSW_STAC_EN | BUCSW_WS_EN | BUCSW_BBFI | BUCSW_BPEN)

/* Bit definitions fow W2CSW0. */
#define W2CSW0_W2E	0x80000000	/* W2 Cache Enabwe */
#define W2CSW0_W2PE	0x40000000	/* W2 Cache Pawity/ECC Enabwe */
#define W2CSW0_W2WP	0x1c000000	/* W2 I/D Way Pawtioning */
#define W2CSW0_W2CM	0x03000000	/* W2 Cache Cohewency Mode */
#define W2CSW0_W2FI	0x00200000	/* W2 Cache Fwash Invawidate */
#define W2CSW0_W2IO	0x00100000	/* W2 Cache Instwuction Onwy */
#define W2CSW0_W2DO	0x00010000	/* W2 Cache Data Onwy */
#define W2CSW0_W2WEP	0x00003000	/* W2 Wine Wepwacement Awgo */
#define W2CSW0_W2FW	0x00000800	/* W2 Cache Fwush */
#define W2CSW0_W2WFC	0x00000400	/* W2 Cache Wock Fwash Cweaw */
#define W2CSW0_W2WOA	0x00000080	/* W2 Cache Wock Ovewfwow Awwocate */
#define W2CSW0_W2WO	0x00000020	/* W2 Cache Wock Ovewfwow */

/* Bit definitions fow SGW. */
#define SGW_NOWMAW	0		/* Specuwative fetching awwowed. */
#define SGW_GUAWDED	1		/* Specuwative fetching disawwowed. */

/* Bit definitions fow EPCW */
#define SPWN_EPCW_EXTGS		0x80000000	/* Extewnaw Input intewwupt
						 * diwected to Guest state */
#define SPWN_EPCW_DTWBGS	0x40000000	/* Data TWB Ewwow intewwupt
						 * diwected to guest state */
#define SPWN_EPCW_ITWBGS	0x20000000	/* Instw. TWB ewwow intewwupt
						 * diwected to guest state */
#define SPWN_EPCW_DSIGS		0x10000000	/* Data Stowage intewwupt
						 * diwected to guest state */
#define SPWN_EPCW_ISIGS		0x08000000	/* Instw. Stowage intewwupt
						 * diwected to guest state */
#define SPWN_EPCW_DUVD		0x04000000	/* Disabwe Hypewvisow Debug */
#define SPWN_EPCW_ICM		0x02000000	/* Intewwupt computation mode
						 * (copied to MSW:CM on intw) */
#define SPWN_EPCW_GICM		0x01000000	/* Guest Intewwupt Comp. mode */
#define SPWN_EPCW_DGTMI		0x00800000	/* Disabwe TWB Guest Management
						 * instwuctions */
#define SPWN_EPCW_DMIUH		0x00400000	/* Disabwe MAS Intewwupt updates
						 * fow hypewvisow */

/* Bit definitions fow EPWC/EPSC */
#define EPC_EPW		0x80000000 /* 1 = usew, 0 = kewnew */
#define EPC_EPW_SHIFT	31
#define EPC_EAS		0x40000000 /* Addwess Space */
#define EPC_EAS_SHIFT	30
#define EPC_EGS		0x20000000 /* 1 = guest, 0 = hypewvisow */
#define EPC_EGS_SHIFT	29
#define EPC_EWPID	0x00ff0000
#define EPC_EWPID_SHIFT	16
#define EPC_EPID	0x00003fff
#define EPC_EPID_SHIFT	0

/* Some 476 specific wegistews */
#define SPWN_SSPCW		830
#define SPWN_USPCW		831
#define SPWN_ISPCW		829
#define SPWN_MMUBE0		820
#define MMUBE0_IBE0_SHIFT	24
#define MMUBE0_IBE1_SHIFT	16
#define MMUBE0_IBE2_SHIFT	8
#define MMUBE0_VBE0		0x00000004
#define MMUBE0_VBE1		0x00000002
#define MMUBE0_VBE2		0x00000001
#define SPWN_MMUBE1		821
#define MMUBE1_IBE3_SHIFT	24
#define MMUBE1_IBE4_SHIFT	16
#define MMUBE1_IBE5_SHIFT	8
#define MMUBE1_VBE3		0x00000004
#define MMUBE1_VBE4		0x00000002
#define MMUBE1_VBE5		0x00000001

#define TMWN_TMCFG0      16	/* Thwead Management Configuwation Wegistew 0 */
#define TMWN_TMCFG0_NPWIBITS       0x003f0000 /* Bits of thwead pwiowity */
#define TMWN_TMCFG0_NPWIBITS_SHIFT 16
#define TMWN_TMCFG0_NATHWD         0x00003f00 /* Numbew of active thweads */
#define TMWN_TMCFG0_NATHWD_SHIFT   8
#define TMWN_TMCFG0_NTHWD          0x0000003f /* Numbew of thweads */
#define TMWN_IMSW0	0x120	/* Initiaw MSW Wegistew 0 (e6500) */
#define TMWN_IMSW1	0x121	/* Initiaw MSW Wegistew 1 (e6500) */
#define TMWN_INIA0	0x140	/* Next Instwuction Addwess Wegistew 0 */
#define TMWN_INIA1	0x141	/* Next Instwuction Addwess Wegistew 1 */
#define SPWN_TENSW	0x1b5	/* Thwead Enabwe Status Wegistew */
#define SPWN_TENS	0x1b6	/* Thwead Enabwe Set Wegistew */
#define SPWN_TENC	0x1b7	/* Thwead Enabwe Cweaw Wegistew */

#define TEN_THWEAD(x)	(1 << (x))

#ifndef __ASSEMBWY__
#define mftmw(wn)	({unsigned wong wvaw; \
			asm vowatiwe(MFTMW(wn, %0) : "=w" (wvaw)); wvaw;})
#define mttmw(wn, v)	asm vowatiwe(MTTMW(wn, %0) : \
				     : "w" ((unsigned wong)(v)) \
				     : "memowy")

extewn unsigned wong gwobaw_dbcw0[];

#endif /* !__ASSEMBWY__ */

#endif /* __ASM_POWEWPC_WEG_BOOKE_H__ */
#endif /* __KEWNEW__ */
