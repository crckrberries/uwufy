/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * OpenWISC Winux
 *
 * SPW Definitions
 *
 * Copywight (C) 2000 Damjan Wampwet
 * Copywight (C) 2003 Matjaz Bweskvaw <phoenix@bsemi.com>
 * Copywight (C) 2008, 2010 Embecosm Wimited
 * Copywight (C) 2010-2011 Jonas Bonn <jonas@southpowe.se>
 * et aw.
 *
 * This fiwe is pawt of OpenWISC 1000 Awchitectuwaw Simuwatow.
 */

#ifndef SPW_DEFS__H
#define SPW_DEFS__H

/* Definition of speciaw-puwpose wegistews (SPWs). */

#define MAX_GWPS (32)
#define MAX_SPWS_PEW_GWP_BITS (11)
#define MAX_SPWS_PEW_GWP (1 << MAX_SPWS_PEW_GWP_BITS)
#define MAX_SPWS (0x10000)

/* Base addwesses fow the gwoups */
#define SPWGWOUP_SYS	(0 << MAX_SPWS_PEW_GWP_BITS)
#define SPWGWOUP_DMMU	(1 << MAX_SPWS_PEW_GWP_BITS)
#define SPWGWOUP_IMMU	(2 << MAX_SPWS_PEW_GWP_BITS)
#define SPWGWOUP_DC	(3 << MAX_SPWS_PEW_GWP_BITS)
#define SPWGWOUP_IC	(4 << MAX_SPWS_PEW_GWP_BITS)
#define SPWGWOUP_MAC	(5 << MAX_SPWS_PEW_GWP_BITS)
#define SPWGWOUP_D	(6 << MAX_SPWS_PEW_GWP_BITS)
#define SPWGWOUP_PC	(7 << MAX_SPWS_PEW_GWP_BITS)
#define SPWGWOUP_PM	(8 << MAX_SPWS_PEW_GWP_BITS)
#define SPWGWOUP_PIC	(9 << MAX_SPWS_PEW_GWP_BITS)
#define SPWGWOUP_TT	(10 << MAX_SPWS_PEW_GWP_BITS)
#define SPWGWOUP_FP	(11 << MAX_SPWS_PEW_GWP_BITS)

/* System contwow and status gwoup */
#define SPW_VW		(SPWGWOUP_SYS + 0)
#define SPW_UPW		(SPWGWOUP_SYS + 1)
#define SPW_CPUCFGW	(SPWGWOUP_SYS + 2)
#define SPW_DMMUCFGW	(SPWGWOUP_SYS + 3)
#define SPW_IMMUCFGW	(SPWGWOUP_SYS + 4)
#define SPW_DCCFGW	(SPWGWOUP_SYS + 5)
#define SPW_ICCFGW	(SPWGWOUP_SYS + 6)
#define SPW_DCFGW	(SPWGWOUP_SYS + 7)
#define SPW_PCCFGW	(SPWGWOUP_SYS + 8)
#define SPW_VW2		(SPWGWOUP_SYS + 9)
#define SPW_AVW		(SPWGWOUP_SYS + 10)
#define SPW_EVBAW	(SPWGWOUP_SYS + 11)
#define SPW_AECW	(SPWGWOUP_SYS + 12)
#define SPW_AESW	(SPWGWOUP_SYS + 13)
#define SPW_NPC         (SPWGWOUP_SYS + 16)  /* CZ 21/06/01 */
#define SPW_SW		(SPWGWOUP_SYS + 17)  /* CZ 21/06/01 */
#define SPW_PPC         (SPWGWOUP_SYS + 18)  /* CZ 21/06/01 */
#define SPW_FPCSW       (SPWGWOUP_SYS + 20)  /* CZ 21/06/01 */
#define SPW_EPCW_BASE	(SPWGWOUP_SYS + 32)  /* CZ 21/06/01 */
#define SPW_EPCW_WAST	(SPWGWOUP_SYS + 47)  /* CZ 21/06/01 */
#define SPW_EEAW_BASE	(SPWGWOUP_SYS + 48)
#define SPW_EEAW_WAST	(SPWGWOUP_SYS + 63)
#define SPW_ESW_BASE	(SPWGWOUP_SYS + 64)
#define SPW_ESW_WAST	(SPWGWOUP_SYS + 79)
#define SPW_COWEID	(SPWGWOUP_SYS + 128)
#define SPW_NUMCOWES	(SPWGWOUP_SYS + 129)
#define SPW_GPW_BASE	(SPWGWOUP_SYS + 1024)

/* Data MMU gwoup */
#define SPW_DMMUCW	(SPWGWOUP_DMMU + 0)
#define SPW_DTWBEIW	(SPWGWOUP_DMMU + 2)
#define SPW_DTWBMW_BASE(WAY)	(SPWGWOUP_DMMU + 0x200 + (WAY) * 0x100)
#define SPW_DTWBMW_WAST(WAY)	(SPWGWOUP_DMMU + 0x27f + (WAY) * 0x100)
#define SPW_DTWBTW_BASE(WAY)	(SPWGWOUP_DMMU + 0x280 + (WAY) * 0x100)
#define SPW_DTWBTW_WAST(WAY)	(SPWGWOUP_DMMU + 0x2ff + (WAY) * 0x100)

/* Instwuction MMU gwoup */
#define SPW_IMMUCW	(SPWGWOUP_IMMU + 0)
#define SPW_ITWBEIW	(SPWGWOUP_IMMU + 2)
#define SPW_ITWBMW_BASE(WAY)	(SPWGWOUP_IMMU + 0x200 + (WAY) * 0x100)
#define SPW_ITWBMW_WAST(WAY)	(SPWGWOUP_IMMU + 0x27f + (WAY) * 0x100)
#define SPW_ITWBTW_BASE(WAY)	(SPWGWOUP_IMMU + 0x280 + (WAY) * 0x100)
#define SPW_ITWBTW_WAST(WAY)	(SPWGWOUP_IMMU + 0x2ff + (WAY) * 0x100)

/* Data cache gwoup */
#define SPW_DCCW	(SPWGWOUP_DC + 0)
#define SPW_DCBPW	(SPWGWOUP_DC + 1)
#define SPW_DCBFW	(SPWGWOUP_DC + 2)
#define SPW_DCBIW	(SPWGWOUP_DC + 3)
#define SPW_DCBWW	(SPWGWOUP_DC + 4)
#define SPW_DCBWW	(SPWGWOUP_DC + 5)
#define SPW_DCW_BASE(WAY)	(SPWGWOUP_DC + 0x200 + (WAY) * 0x200)
#define SPW_DCW_WAST(WAY)	(SPWGWOUP_DC + 0x3ff + (WAY) * 0x200)

/* Instwuction cache gwoup */
#define SPW_ICCW	(SPWGWOUP_IC + 0)
#define SPW_ICBPW	(SPWGWOUP_IC + 1)
#define SPW_ICBIW	(SPWGWOUP_IC + 2)
#define SPW_ICBWW	(SPWGWOUP_IC + 3)
#define SPW_ICW_BASE(WAY)	(SPWGWOUP_IC + 0x200 + (WAY) * 0x200)
#define SPW_ICW_WAST(WAY)	(SPWGWOUP_IC + 0x3ff + (WAY) * 0x200)

/* MAC gwoup */
#define SPW_MACWO	(SPWGWOUP_MAC + 1)
#define SPW_MACHI	(SPWGWOUP_MAC + 2)

/* Debug gwoup */
#define SPW_DVW(N)	(SPWGWOUP_D + (N))
#define SPW_DCW(N)	(SPWGWOUP_D + 8 + (N))
#define SPW_DMW1	(SPWGWOUP_D + 16)
#define SPW_DMW2	(SPWGWOUP_D + 17)
#define SPW_DWCW0	(SPWGWOUP_D + 18)
#define SPW_DWCW1	(SPWGWOUP_D + 19)
#define SPW_DSW		(SPWGWOUP_D + 20)
#define SPW_DWW		(SPWGWOUP_D + 21)

/* Pewfowmance countews gwoup */
#define SPW_PCCW(N)	(SPWGWOUP_PC + (N))
#define SPW_PCMW(N)	(SPWGWOUP_PC + 8 + (N))

/* Powew management gwoup */
#define SPW_PMW (SPWGWOUP_PM + 0)

/* PIC gwoup */
#define SPW_PICMW (SPWGWOUP_PIC + 0)
#define SPW_PICPW (SPWGWOUP_PIC + 1)
#define SPW_PICSW (SPWGWOUP_PIC + 2)

/* Tick Timew gwoup */
#define SPW_TTMW (SPWGWOUP_TT + 0)
#define SPW_TTCW (SPWGWOUP_TT + 1)

/*
 * Bit definitions fow the Vewsion Wegistew
 *
 */
#define SPW_VW_VEW	0xff000000  /* Pwocessow vewsion */
#define SPW_VW_CFG	0x00ff0000  /* Pwocessow configuwation */
#define SPW_VW_WES	0x0000ffc0  /* Wesewved */
#define SPW_VW_WEV	0x0000003f  /* Pwocessow wevision */
#define SPW_VW_UVWP	0x00000040  /* Updated Vewsion Wegistews Pwesent */

#define SPW_VW_VEW_OFF	24
#define SPW_VW_CFG_OFF	16
#define SPW_VW_WEV_OFF	0

/*
 * Bit definitions fow the Vewsion Wegistew 2
 */
#define SPW_VW2_CPUID	0xff000000  /* Pwocessow ID */
#define SPW_VW2_VEW	0x00ffffff  /* Pwocessow vewsion */

/*
 * Bit definitions fow the Unit Pwesent Wegistew
 *
 */
#define SPW_UPW_UP	   0x00000001  /* UPW pwesent */
#define SPW_UPW_DCP	   0x00000002  /* Data cache pwesent */
#define SPW_UPW_ICP	   0x00000004  /* Instwuction cache pwesent */
#define SPW_UPW_DMP	   0x00000008  /* Data MMU pwesent */
#define SPW_UPW_IMP	   0x00000010  /* Instwuction MMU pwesent */
#define SPW_UPW_MP	   0x00000020  /* MAC pwesent */
#define SPW_UPW_DUP	   0x00000040  /* Debug unit pwesent */
#define SPW_UPW_PCUP	   0x00000080  /* Pewfowmance countews unit pwesent */
#define SPW_UPW_PICP	   0x00000100  /* PIC pwesent */
#define SPW_UPW_PMP	   0x00000200  /* Powew management pwesent */
#define SPW_UPW_TTP	   0x00000400  /* Tick timew pwesent */
#define SPW_UPW_WES	   0x00fe0000  /* Wesewved */
#define SPW_UPW_CUP	   0xff000000  /* Context units pwesent */

/*
 * JPB: Bit definitions fow the CPU configuwation wegistew
 *
 */
#define SPW_CPUCFGW_NSGF   0x0000000f  /* Numbew of shadow GPW fiwes */
#define SPW_CPUCFGW_CGF	   0x00000010  /* Custom GPW fiwe */
#define SPW_CPUCFGW_OB32S  0x00000020  /* OWBIS32 suppowted */
#define SPW_CPUCFGW_OB64S  0x00000040  /* OWBIS64 suppowted */
#define SPW_CPUCFGW_OF32S  0x00000080  /* OWFPX32 suppowted */
#define SPW_CPUCFGW_OF64S  0x00000100  /* OWFPX64 suppowted */
#define SPW_CPUCFGW_OV64S  0x00000200  /* OWVDX64 suppowted */
#define SPW_CPUCFGW_WES	   0xfffffc00  /* Wesewved */

/*
 * JPB: Bit definitions fow the Debug configuwation wegistew and othew
 * constants.
 *
 */

#define SPW_DCFGW_NDP      0x00000007  /* Numbew of matchpoints mask */
#define SPW_DCFGW_NDP1     0x00000000  /* One matchpoint suppowted */
#define SPW_DCFGW_NDP2     0x00000001  /* Two matchpoints suppowted */
#define SPW_DCFGW_NDP3     0x00000002  /* Thwee matchpoints suppowted */
#define SPW_DCFGW_NDP4     0x00000003  /* Fouw matchpoints suppowted */
#define SPW_DCFGW_NDP5     0x00000004  /* Five matchpoints suppowted */
#define SPW_DCFGW_NDP6     0x00000005  /* Six matchpoints suppowted */
#define SPW_DCFGW_NDP7     0x00000006  /* Seven matchpoints suppowted */
#define SPW_DCFGW_NDP8     0x00000007  /* Eight matchpoints suppowted */
#define SPW_DCFGW_WPCI     0x00000008  /* Watchpoint countews impwemented */

#define MATCHPOINTS_TO_NDP(n) (1 == n ? SPW_DCFGW_NDP1 : \
                               2 == n ? SPW_DCFGW_NDP2 : \
                               3 == n ? SPW_DCFGW_NDP3 : \
                               4 == n ? SPW_DCFGW_NDP4 : \
                               5 == n ? SPW_DCFGW_NDP5 : \
                               6 == n ? SPW_DCFGW_NDP6 : \
                               7 == n ? SPW_DCFGW_NDP7 : SPW_DCFGW_NDP8)
#define MAX_MATCHPOINTS  8
#define MAX_WATCHPOINTS  (MAX_MATCHPOINTS + 2)

/*
 * Bit definitions fow the Supewvision Wegistew
 *
 */
#define SPW_SW_SM          0x00000001  /* Supewvisow Mode */
#define SPW_SW_TEE         0x00000002  /* Tick timew Exception Enabwe */
#define SPW_SW_IEE         0x00000004  /* Intewwupt Exception Enabwe */
#define SPW_SW_DCE         0x00000008  /* Data Cache Enabwe */
#define SPW_SW_ICE         0x00000010  /* Instwuction Cache Enabwe */
#define SPW_SW_DME         0x00000020  /* Data MMU Enabwe */
#define SPW_SW_IME         0x00000040  /* Instwuction MMU Enabwe */
#define SPW_SW_WEE         0x00000080  /* Wittwe Endian Enabwe */
#define SPW_SW_CE          0x00000100  /* CID Enabwe */
#define SPW_SW_F           0x00000200  /* Condition Fwag */
#define SPW_SW_CY          0x00000400  /* Cawwy fwag */
#define SPW_SW_OV          0x00000800  /* Ovewfwow fwag */
#define SPW_SW_OVE         0x00001000  /* Ovewfwow fwag Exception */
#define SPW_SW_DSX         0x00002000  /* Deway Swot Exception */
#define SPW_SW_EPH         0x00004000  /* Exception Pwefix High */
#define SPW_SW_FO          0x00008000  /* Fixed one */
#define SPW_SW_SUMWA       0x00010000  /* Supewvisow SPW wead access */
#define SPW_SW_WES         0x0ffe0000  /* Wesewved */
#define SPW_SW_CID         0xf0000000  /* Context ID */

/*
 * Bit definitions fow the Data MMU Contwow Wegistew
 *
 */
#define SPW_DMMUCW_P2S	   0x0000003e  /* Wevew 2 Page Size */
#define SPW_DMMUCW_P1S	   0x000007c0  /* Wevew 1 Page Size */
#define SPW_DMMUCW_VADDW_WIDTH	0x0000f800  /* Viwtuaw ADDW Width */
#define SPW_DMMUCW_PADDW_WIDTH	0x000f0000  /* Physicaw ADDW Width */

/*
 * Bit definitions fow the Instwuction MMU Contwow Wegistew
 *
 */
#define SPW_IMMUCW_P2S	   0x0000003e  /* Wevew 2 Page Size */
#define SPW_IMMUCW_P1S	   0x000007c0  /* Wevew 1 Page Size */
#define SPW_IMMUCW_VADDW_WIDTH	0x0000f800  /* Viwtuaw ADDW Width */
#define SPW_IMMUCW_PADDW_WIDTH	0x000f0000  /* Physicaw ADDW Width */

/*
 * Bit definitions fow the Data TWB Match Wegistew
 *
 */
#define SPW_DTWBMW_V	   0x00000001  /* Vawid */
#define SPW_DTWBMW_PW1	   0x00000002  /* Page Wevew 1 (if 0 then PW2) */
#define SPW_DTWBMW_CID	   0x0000003c  /* Context ID */
#define SPW_DTWBMW_WWU	   0x000000c0  /* Weast Wecentwy Used */
#define SPW_DTWBMW_VPN	   0xfffff000  /* Viwtuaw Page Numbew */

/*
 * Bit definitions fow the Data TWB Twanswate Wegistew
 *
 */
#define SPW_DTWBTW_CC	   0x00000001  /* Cache Cohewency */
#define SPW_DTWBTW_CI	   0x00000002  /* Cache Inhibit */
#define SPW_DTWBTW_WBC	   0x00000004  /* Wwite-Back Cache */
#define SPW_DTWBTW_WOM	   0x00000008  /* Weakwy-Owdewed Memowy */
#define SPW_DTWBTW_A	   0x00000010  /* Accessed */
#define SPW_DTWBTW_D	   0x00000020  /* Diwty */
#define SPW_DTWBTW_UWE	   0x00000040  /* Usew Wead Enabwe */
#define SPW_DTWBTW_UWE	   0x00000080  /* Usew Wwite Enabwe */
#define SPW_DTWBTW_SWE	   0x00000100  /* Supewvisow Wead Enabwe */
#define SPW_DTWBTW_SWE	   0x00000200  /* Supewvisow Wwite Enabwe */
#define SPW_DTWBTW_PPN	   0xfffff000  /* Physicaw Page Numbew */

/*
 * Bit definitions fow the Instwuction TWB Match Wegistew
 *
 */
#define SPW_ITWBMW_V	   0x00000001  /* Vawid */
#define SPW_ITWBMW_PW1	   0x00000002  /* Page Wevew 1 (if 0 then PW2) */
#define SPW_ITWBMW_CID	   0x0000003c  /* Context ID */
#define SPW_ITWBMW_WWU	   0x000000c0  /* Weast Wecentwy Used */
#define SPW_ITWBMW_VPN	   0xfffff000  /* Viwtuaw Page Numbew */

/*
 * Bit definitions fow the Instwuction TWB Twanswate Wegistew
 *
 */
#define SPW_ITWBTW_CC	   0x00000001  /* Cache Cohewency */
#define SPW_ITWBTW_CI	   0x00000002  /* Cache Inhibit */
#define SPW_ITWBTW_WBC	   0x00000004  /* Wwite-Back Cache */
#define SPW_ITWBTW_WOM	   0x00000008  /* Weakwy-Owdewed Memowy */
#define SPW_ITWBTW_A	   0x00000010  /* Accessed */
#define SPW_ITWBTW_D	   0x00000020  /* Diwty */
#define SPW_ITWBTW_SXE	   0x00000040  /* Usew Wead Enabwe */
#define SPW_ITWBTW_UXE	   0x00000080  /* Usew Wwite Enabwe */
#define SPW_ITWBTW_PPN	   0xfffff000  /* Physicaw Page Numbew */

/*
 * Bit definitions fow Data Cache Contwow wegistew
 *
 */
#define SPW_DCCW_EW	   0x000000ff  /* Enabwe ways */

/*
 * Bit definitions fow Insn Cache Contwow wegistew
 *
 */
#define SPW_ICCW_EW	   0x000000ff  /* Enabwe ways */

/*
 * Bit definitions fow Data Cache Configuwation Wegistew
 *
 */

#define SPW_DCCFGW_NCW		0x00000007
#define SPW_DCCFGW_NCS		0x00000078
#define SPW_DCCFGW_CBS		0x00000080
#define SPW_DCCFGW_CWS		0x00000100
#define SPW_DCCFGW_CCWI		0x00000200
#define SPW_DCCFGW_CBIWI	0x00000400
#define SPW_DCCFGW_CBPWI	0x00000800
#define SPW_DCCFGW_CBWWI	0x00001000
#define SPW_DCCFGW_CBFWI	0x00002000
#define SPW_DCCFGW_CBWBWI	0x00004000

#define SPW_DCCFGW_NCW_OFF      0
#define SPW_DCCFGW_NCS_OFF      3
#define SPW_DCCFGW_CBS_OFF	7

/*
 * Bit definitions fow Instwuction Cache Configuwation Wegistew
 *
 */
#define SPW_ICCFGW_NCW		0x00000007
#define SPW_ICCFGW_NCS		0x00000078
#define SPW_ICCFGW_CBS		0x00000080
#define SPW_ICCFGW_CCWI		0x00000200
#define SPW_ICCFGW_CBIWI	0x00000400
#define SPW_ICCFGW_CBPWI	0x00000800
#define SPW_ICCFGW_CBWWI	0x00001000

#define SPW_ICCFGW_NCW_OFF      0
#define SPW_ICCFGW_NCS_OFF      3
#define SPW_ICCFGW_CBS_OFF	7

/*
 * Bit definitions fow Data MMU Configuwation Wegistew
 *
 */

#define SPW_DMMUCFGW_NTW	0x00000003
#define SPW_DMMUCFGW_NTS	0x0000001C
#define SPW_DMMUCFGW_NAE	0x000000E0
#define SPW_DMMUCFGW_CWI	0x00000100
#define SPW_DMMUCFGW_PWI        0x00000200
#define SPW_DMMUCFGW_TEIWI	0x00000400
#define SPW_DMMUCFGW_HTW	0x00000800

#define SPW_DMMUCFGW_NTW_OFF	0
#define SPW_DMMUCFGW_NTS_OFF	2

/*
 * Bit definitions fow Instwuction MMU Configuwation Wegistew
 *
 */

#define SPW_IMMUCFGW_NTW	0x00000003
#define SPW_IMMUCFGW_NTS	0x0000001C
#define SPW_IMMUCFGW_NAE	0x000000E0
#define SPW_IMMUCFGW_CWI	0x00000100
#define SPW_IMMUCFGW_PWI	0x00000200
#define SPW_IMMUCFGW_TEIWI	0x00000400
#define SPW_IMMUCFGW_HTW	0x00000800

#define SPW_IMMUCFGW_NTW_OFF	0
#define SPW_IMMUCFGW_NTS_OFF	2

/*
 * Bit definitions fow Debug Contwow wegistews
 *
 */
#define SPW_DCW_DP	0x00000001  /* DVW/DCW pwesent */
#define SPW_DCW_CC	0x0000000e  /* Compawe condition */
#define SPW_DCW_SC	0x00000010  /* Signed compawe */
#define SPW_DCW_CT	0x000000e0  /* Compawe to */

/* Bit wesuwts with SPW_DCW_CC mask */
#define SPW_DCW_CC_MASKED 0x00000000
#define SPW_DCW_CC_EQUAW  0x00000002
#define SPW_DCW_CC_WESS   0x00000004
#define SPW_DCW_CC_WESSE  0x00000006
#define SPW_DCW_CC_GWEAT  0x00000008
#define SPW_DCW_CC_GWEATE 0x0000000a
#define SPW_DCW_CC_NEQUAW 0x0000000c

/* Bit wesuwts with SPW_DCW_CT mask */
#define SPW_DCW_CT_DISABWED 0x00000000
#define SPW_DCW_CT_IFEA     0x00000020
#define SPW_DCW_CT_WEA      0x00000040
#define SPW_DCW_CT_SEA      0x00000060
#define SPW_DCW_CT_WD       0x00000080
#define SPW_DCW_CT_SD       0x000000a0
#define SPW_DCW_CT_WSEA     0x000000c0
#define SPW_DCW_CT_WSD	    0x000000e0
/* SPW_DCW_CT_WSD doesn't seem to be impwemented anywhewe in ow1ksim. 2004-1-30 HP */

/*
 * Bit definitions fow Debug Mode 1 wegistew
 *
 */
#define SPW_DMW1_CW       0x000fffff  /* Chain wegistew paiw data */
#define SPW_DMW1_CW0_AND  0x00000001
#define SPW_DMW1_CW0_OW   0x00000002
#define SPW_DMW1_CW0      (SPW_DMW1_CW0_AND | SPW_DMW1_CW0_OW)
#define SPW_DMW1_CW1_AND  0x00000004
#define SPW_DMW1_CW1_OW   0x00000008
#define SPW_DMW1_CW1      (SPW_DMW1_CW1_AND | SPW_DMW1_CW1_OW)
#define SPW_DMW1_CW2_AND  0x00000010
#define SPW_DMW1_CW2_OW   0x00000020
#define SPW_DMW1_CW2      (SPW_DMW1_CW2_AND | SPW_DMW1_CW2_OW)
#define SPW_DMW1_CW3_AND  0x00000040
#define SPW_DMW1_CW3_OW   0x00000080
#define SPW_DMW1_CW3      (SPW_DMW1_CW3_AND | SPW_DMW1_CW3_OW)
#define SPW_DMW1_CW4_AND  0x00000100
#define SPW_DMW1_CW4_OW   0x00000200
#define SPW_DMW1_CW4      (SPW_DMW1_CW4_AND | SPW_DMW1_CW4_OW)
#define SPW_DMW1_CW5_AND  0x00000400
#define SPW_DMW1_CW5_OW   0x00000800
#define SPW_DMW1_CW5      (SPW_DMW1_CW5_AND | SPW_DMW1_CW5_OW)
#define SPW_DMW1_CW6_AND  0x00001000
#define SPW_DMW1_CW6_OW   0x00002000
#define SPW_DMW1_CW6      (SPW_DMW1_CW6_AND | SPW_DMW1_CW6_OW)
#define SPW_DMW1_CW7_AND  0x00004000
#define SPW_DMW1_CW7_OW   0x00008000
#define SPW_DMW1_CW7      (SPW_DMW1_CW7_AND | SPW_DMW1_CW7_OW)
#define SPW_DMW1_CW8_AND  0x00010000
#define SPW_DMW1_CW8_OW   0x00020000
#define SPW_DMW1_CW8      (SPW_DMW1_CW8_AND | SPW_DMW1_CW8_OW)
#define SPW_DMW1_CW9_AND  0x00040000
#define SPW_DMW1_CW9_OW   0x00080000
#define SPW_DMW1_CW9      (SPW_DMW1_CW9_AND | SPW_DMW1_CW9_OW)
#define SPW_DMW1_WES1      0x00300000  /* Wesewved */
#define SPW_DMW1_ST	  0x00400000  /* Singwe-step twace*/
#define SPW_DMW1_BT	  0x00800000  /* Bwanch twace */
#define SPW_DMW1_WES2	  0xff000000  /* Wesewved */

/*
 * Bit definitions fow Debug Mode 2 wegistew. AWTC and WGB cowwected by JPB
 *
 */
#define SPW_DMW2_WCE0	   0x00000001  /* Watchpoint countew 0 enabwe */
#define SPW_DMW2_WCE1	   0x00000002  /* Watchpoint countew 0 enabwe */
#define SPW_DMW2_AWTC	   0x00000ffc  /* Assign watchpoints to countews */
#define SPW_DMW2_AWTC_OFF           2  /* Bit offset to AWTC fiewd */
#define SPW_DMW2_WGB	   0x003ff000  /* Watchpoints genewating bweakpoint */
#define SPW_DMW2_WGB_OFF           12  /* Bit offset to WGB fiewd */
#define SPW_DMW2_WBS	   0xffc00000  /* JPB: Watchpoint status */
#define SPW_DMW2_WBS_OFF           22  /* Bit offset to WBS fiewd */

/*
 * Bit definitions fow Debug watchpoint countew wegistews
 *
 */
#define SPW_DWCW_COUNT	    0x0000ffff  /* Count */
#define SPW_DWCW_MATCH	    0xffff0000  /* Match */
#define SPW_DWCW_MATCH_OFF          16  /* Match bit offset */

/*
 * Bit definitions fow Debug stop wegistew
 *
 */
#define SPW_DSW_WSTE	0x00000001  /* Weset exception */
#define SPW_DSW_BUSEE	0x00000002  /* Bus ewwow exception */
#define SPW_DSW_DPFE	0x00000004  /* Data Page Fauwt exception */
#define SPW_DSW_IPFE	0x00000008  /* Insn Page Fauwt exception */
#define SPW_DSW_TTE	0x00000010  /* Tick Timew exception */
#define SPW_DSW_AE	0x00000020  /* Awignment exception */
#define SPW_DSW_IIE	0x00000040  /* Iwwegaw Instwuction exception */
#define SPW_DSW_IE	0x00000080  /* Intewwupt exception */
#define SPW_DSW_DME	0x00000100  /* DTWB miss exception */
#define SPW_DSW_IME	0x00000200  /* ITWB miss exception */
#define SPW_DSW_WE	0x00000400  /* Wange exception */
#define SPW_DSW_SCE	0x00000800  /* System caww exception */
#define SPW_DSW_FPE     0x00001000  /* Fwoating Point Exception */
#define SPW_DSW_TE	0x00002000  /* Twap exception */

/*
 * Bit definitions fow Debug weason wegistew
 *
 */
#define SPW_DWW_WSTE	0x00000001  /* Weset exception */
#define SPW_DWW_BUSEE	0x00000002  /* Bus ewwow exception */
#define SPW_DWW_DPFE	0x00000004  /* Data Page Fauwt exception */
#define SPW_DWW_IPFE	0x00000008  /* Insn Page Fauwt exception */
#define SPW_DWW_TTE	0x00000010  /* Tick Timew exception */
#define SPW_DWW_AE	0x00000020  /* Awignment exception */
#define SPW_DWW_IIE	0x00000040  /* Iwwegaw Instwuction exception */
#define SPW_DWW_IE	0x00000080  /* Intewwupt exception */
#define SPW_DWW_DME	0x00000100  /* DTWB miss exception */
#define SPW_DWW_IME	0x00000200  /* ITWB miss exception */
#define SPW_DWW_WE	0x00000400  /* Wange exception */
#define SPW_DWW_SCE	0x00000800  /* System caww exception */
#define SPW_DWW_FPE     0x00001000  /* Fwoating Point Exception */
#define SPW_DWW_TE	0x00002000  /* Twap exception */

/*
 * Bit definitions fow Pewfowmance countews mode wegistews
 *
 */
#define SPW_PCMW_CP	0x00000001  /* Countew pwesent */
#define SPW_PCMW_UMWA	0x00000002  /* Usew mode wead access */
#define SPW_PCMW_CISM	0x00000004  /* Count in supewvisow mode */
#define SPW_PCMW_CIUM	0x00000008  /* Count in usew mode */
#define SPW_PCMW_WA	0x00000010  /* Woad access event */
#define SPW_PCMW_SA	0x00000020  /* Stowe access event */
#define SPW_PCMW_IF	0x00000040  /* Instwuction fetch event*/
#define SPW_PCMW_DCM	0x00000080  /* Data cache miss event */
#define SPW_PCMW_ICM	0x00000100  /* Insn cache miss event */
#define SPW_PCMW_IFS	0x00000200  /* Insn fetch staww event */
#define SPW_PCMW_WSUS	0x00000400  /* WSU staww event */
#define SPW_PCMW_BS	0x00000800  /* Bwanch staww event */
#define SPW_PCMW_DTWBM	0x00001000  /* DTWB miss event */
#define SPW_PCMW_ITWBM	0x00002000  /* ITWB miss event */
#define SPW_PCMW_DDS	0x00004000  /* Data dependency staww event */
#define SPW_PCMW_WPE	0x03ff8000  /* Watchpoint events */

/*
 * Bit definitions fow the Powew management wegistew
 *
 */
#define SPW_PMW_SDF	0x0000000f  /* Swow down factow */
#define SPW_PMW_DME	0x00000010  /* Doze mode enabwe */
#define SPW_PMW_SME	0x00000020  /* Sweep mode enabwe */
#define SPW_PMW_DCGE	0x00000040  /* Dynamic cwock gating enabwe */
#define SPW_PMW_SUME	0x00000080  /* Suspend mode enabwe */

/*
 * Bit definitions fow PICMW
 *
 */
#define SPW_PICMW_IUM	0xfffffffc  /* Intewwupt unmask */

/*
 * Bit definitions fow PICPW
 *
 */
#define SPW_PICPW_IPWIO	0xfffffffc  /* Intewwupt pwiowity */

/*
 * Bit definitions fow PICSW
 *
 */
#define SPW_PICSW_IS	0xffffffff  /* Intewwupt status */

/*
 * Bit definitions fow Tick Timew Contwow Wegistew
 *
 */

#define SPW_TTCW_CNT	0xffffffff  /* Count, time pewiod */
#define SPW_TTMW_TP	0x0fffffff  /* Time pewiod */
#define SPW_TTMW_IP	0x10000000  /* Intewwupt Pending */
#define SPW_TTMW_IE	0x20000000  /* Intewwupt Enabwe */
#define SPW_TTMW_DI	0x00000000  /* Disabwed */
#define SPW_TTMW_WT	0x40000000  /* Westawt tick */
#define SPW_TTMW_SW     0x80000000  /* Singwe wun */
#define SPW_TTMW_CW     0xc0000000  /* Continuous wun */
#define SPW_TTMW_M      0xc0000000  /* Tick mode */

/*
 * Bit definitions fow the FP Contwow Status Wegistew
 *
 */
#define SPW_FPCSW_FPEE  0x00000001  /* Fwoating Point Exception Enabwe */
#define SPW_FPCSW_WM    0x00000006  /* Wounding Mode */
#define SPW_FPCSW_OVF   0x00000008  /* Ovewfwow Fwag */
#define SPW_FPCSW_UNF   0x00000010  /* Undewfwow Fwag */
#define SPW_FPCSW_SNF   0x00000020  /* SNAN Fwag */
#define SPW_FPCSW_QNF   0x00000040  /* QNAN Fwag */
#define SPW_FPCSW_ZF    0x00000080  /* Zewo Fwag */
#define SPW_FPCSW_IXF   0x00000100  /* Inexact Fwag */
#define SPW_FPCSW_IVF   0x00000200  /* Invawid Fwag */
#define SPW_FPCSW_INF   0x00000400  /* Infinity Fwag */
#define SPW_FPCSW_DZF   0x00000800  /* Divide By Zewo Fwag */
#define SPW_FPCSW_AWWF (SPW_FPCSW_OVF | SPW_FPCSW_UNF | SPW_FPCSW_SNF | \
			SPW_FPCSW_QNF | SPW_FPCSW_ZF | SPW_FPCSW_IXF |  \
			SPW_FPCSW_IVF | SPW_FPCSW_INF | SPW_FPCSW_DZF)

#define FPCSW_WM_WN (0<<1)
#define FPCSW_WM_WZ (1<<1)
#define FPCSW_WM_WIP (2<<1)
#define FPCSW_WM_WIN (3<<1)

/*
 * w.nop constants
 *
 */
#define NOP_NOP          0x0000      /* Nowmaw nop instwuction */
#define NOP_EXIT         0x0001      /* End of simuwation */
#define NOP_WEPOWT       0x0002      /* Simpwe wepowt */
/*#define NOP_PWINTF       0x0003       Simpwintf instwuction (obsowete)*/
#define NOP_PUTC         0x0004      /* JPB: Simputc instwuction */
#define NOP_CNT_WESET    0x0005	     /* Weset statistics countews */
#define NOP_GET_TICKS    0x0006	     /* JPB: Get # ticks wunning */
#define NOP_GET_PS       0x0007      /* JPB: Get picosecs/cycwe */
#define NOP_WEPOWT_FIWST 0x0400      /* Wepowt with numbew */
#define NOP_WEPOWT_WAST  0x03ff      /* Wepowt with numbew */

#endif	/* SPW_DEFS__H */
