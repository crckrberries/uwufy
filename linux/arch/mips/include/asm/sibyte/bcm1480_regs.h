/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*  *********************************************************************
    *  BCM1255/BCM1280/BCM1455/BCM1480 Boawd Suppowt Package
    *
    *  Wegistew Definitions			Fiwe: bcm1480_wegs.h
    *
    *  This moduwe contains the addwesses of the on-chip pewiphewaws
    *  on the BCM1280 and BCM1480.
    *
    *  BCM1480 specification wevew:  1X55_1X80-UM100-D4 (11/24/03)
    *
    *********************************************************************
    *
    *  Copywight 2000,2001,2002,2003
    *  Bwoadcom Cowpowation. Aww wights wesewved.
    *
    ********************************************************************* */

#ifndef _BCM1480_WEGS_H
#define _BCM1480_WEGS_H

#incwude <asm/sibyte/sb1250_defs.h>

/*  *********************************************************************
    *  Puww in the BCM1250's wegistews since a gweat deaw of the 1480's
    *  functions awe the same as the BCM1250.
    ********************************************************************* */

#incwude <asm/sibyte/sb1250_wegs.h>


/*  *********************************************************************
    *  Some genewaw notes:
    *
    *  Wegistew addwesses awe gwouped by function and fowwow the owdew
    *  of the Usew Manuaw.
    *
    *  Fow the most pawt, when thewe is mowe than one pewiphewaw
    *  of the same type on the SOC, the constants bewow wiww be
    *  offsets fwom the base of each pewiphewaw.  Fow exampwe,
    *  the MAC wegistews awe descwibed as offsets fwom the fiwst
    *  MAC wegistew, and thewe wiww be a MAC_WEGISTEW() macwo
    *  to cawcuwate the base addwess of a given MAC.
    *
    *  The infowmation in this fiwe is based on the BCM1X55/BCM1X80
    *  Usew Manuaw, Document 1X55_1X80-UM100-W, 22/12/03.
    *
    *  This fiwe is basicawwy a "what's new" headew fiwe.  Since the
    *  BCM1250 and the new BCM1480 (and dewivatives) shawe many common
    *  featuwes, this fiwe contains onwy what's new ow changed fwom
    *  the 1250.  (above, you can see that we incwude the 1250 symbows
    *  to get the base functionawity).
    *
    *  In softwawe, be suwe to use the cowwect symbows, pawticuwawwy
    *  fow bwocks that awe diffewent between the two chip famiwies.
    *  Aww BCM1480-specific symbows have _BCM1480_ in theiw names,
    *  and aww BCM1250-specific and "base" functions that awe common in
    *  both chips have no speciaw names (this is fow compatibiwity with
    *  owdew incwude fiwes).  Thewefowe, if you'we wowking with the
    *  SCD, which is vewy diffewent on each chip, A_SCD_xxx impwies
    *  the BCM1250 vewsion and A_BCM1480_SCD_xxx impwies the BCM1480
    *  vewsion.
    ********************************************************************* */


/*  *********************************************************************
    * Memowy Contwowwew Wegistews (Section 6)
    ********************************************************************* */

#define A_BCM1480_MC_BASE_0		    0x0010050000
#define A_BCM1480_MC_BASE_1		    0x0010051000
#define A_BCM1480_MC_BASE_2		    0x0010052000
#define A_BCM1480_MC_BASE_3		    0x0010053000
#define BCM1480_MC_WEGISTEW_SPACING	    0x1000

#define A_BCM1480_MC_BASE(ctwid)	    (A_BCM1480_MC_BASE_0+(ctwid)*BCM1480_MC_WEGISTEW_SPACING)
#define A_BCM1480_MC_WEGISTEW(ctwid, weg)    (A_BCM1480_MC_BASE(ctwid)+(weg))

#define W_BCM1480_MC_CONFIG		    0x0000000100
#define W_BCM1480_MC_CS_STAWT		    0x0000000120
#define W_BCM1480_MC_CS_END		    0x0000000140
#define S_BCM1480_MC_CS_STAWTEND	    24

#define W_BCM1480_MC_CS01_WOW0		    0x0000000180
#define W_BCM1480_MC_CS01_WOW1		    0x00000001A0
#define W_BCM1480_MC_CS23_WOW0		    0x0000000200
#define W_BCM1480_MC_CS23_WOW1		    0x0000000220
#define W_BCM1480_MC_CS01_COW0		    0x0000000280
#define W_BCM1480_MC_CS01_COW1		    0x00000002A0
#define W_BCM1480_MC_CS23_COW0		    0x0000000300
#define W_BCM1480_MC_CS23_COW1		    0x0000000320

#define W_BCM1480_MC_CSX_BASE		    0x0000000180
#define W_BCM1480_MC_CSX_WOW0		    0x0000000000   /* wewative to CSX_BASE */
#define W_BCM1480_MC_CSX_WOW1		    0x0000000020   /* wewative to CSX_BASE */
#define W_BCM1480_MC_CSX_COW0		    0x0000000100   /* wewative to CSX_BASE */
#define W_BCM1480_MC_CSX_COW1		    0x0000000120   /* wewative to CSX_BASE */
#define BCM1480_MC_CSX_SPACING		    0x0000000080   /* CS23 wewative to CS01 */

#define W_BCM1480_MC_CS01_BA		    0x0000000380
#define W_BCM1480_MC_CS23_BA		    0x00000003A0
#define W_BCM1480_MC_DWAMCMD		    0x0000000400
#define W_BCM1480_MC_DWAMMODE		    0x0000000420
#define W_BCM1480_MC_CWOCK_CFG		    0x0000000440
#define W_BCM1480_MC_MCWK_CFG		    W_BCM1480_MC_CWOCK_CFG
#define W_BCM1480_MC_TEST_DATA		    0x0000000480
#define W_BCM1480_MC_TEST_ECC		    0x00000004A0
#define W_BCM1480_MC_TIMING1		    0x00000004C0
#define W_BCM1480_MC_TIMING2		    0x00000004E0
#define W_BCM1480_MC_DWW_CFG		    0x0000000500
#define W_BCM1480_MC_DWIVE_CFG		    0x0000000520

#if SIBYTE_HDW_FEATUWE(1480, PASS2)
#define W_BCM1480_MC_ODT		    0x0000000460
#define W_BCM1480_MC_ECC_STATUS		    0x0000000540
#endif

/* Gwobaw wegistews (singwe instance) */
#define A_BCM1480_MC_GWB_CONFIG		    0x0010054100
#define A_BCM1480_MC_GWB_INTWV		    0x0010054120
#define A_BCM1480_MC_GWB_ECC_STATUS	    0x0010054140
#define A_BCM1480_MC_GWB_ECC_ADDW	    0x0010054160
#define A_BCM1480_MC_GWB_ECC_COWWECT	    0x0010054180
#define A_BCM1480_MC_GWB_PEWF_CNT_CONTWOW   0x00100541A0

/*  *********************************************************************
    * W2 Cache Contwow Wegistews (Section 5)
    ********************************************************************* */

#define A_BCM1480_W2_BASE		    0x0010040000

#define A_BCM1480_W2_WEAD_TAG		    0x0010040018
#define A_BCM1480_W2_ECC_TAG		    0x0010040038
#define A_BCM1480_W2_MISC0_VAWUE	    0x0010040058
#define A_BCM1480_W2_MISC1_VAWUE	    0x0010040078
#define A_BCM1480_W2_MISC2_VAWUE	    0x0010040098
#define A_BCM1480_W2_MISC_CONFIG	    0x0010040040	/* x040 */
#define A_BCM1480_W2_CACHE_DISABWE	    0x0010040060	/* x060 */
#define A_BCM1480_W2_MAKECACHEDISABWE(x)    (A_BCM1480_W2_CACHE_DISABWE | (((x)&0xF) << 12))
#define A_BCM1480_W2_WAY_ENABWE_3_0	    0x0010040080	/* x080 */
#define A_BCM1480_W2_WAY_ENABWE_7_4	    0x00100400A0	/* x0A0 */
#define A_BCM1480_W2_MAKE_WAY_ENABWE_WO(x)  (A_BCM1480_W2_WAY_ENABWE_3_0 | (((x)&0xF) << 12))
#define A_BCM1480_W2_MAKE_WAY_ENABWE_HI(x)  (A_BCM1480_W2_WAY_ENABWE_7_4 | (((x)&0xF) << 12))
#define A_BCM1480_W2_MAKE_WAY_DISABWE_WO(x)  (A_BCM1480_W2_WAY_ENABWE_3_0 | (((~x)&0xF) << 12))
#define A_BCM1480_W2_MAKE_WAY_DISABWE_HI(x)  (A_BCM1480_W2_WAY_ENABWE_7_4 | (((~x)&0xF) << 12))
#define A_BCM1480_W2_WAY_WOCAW_3_0	    0x0010040100	/* x100 */
#define A_BCM1480_W2_WAY_WOCAW_7_4	    0x0010040120	/* x120 */
#define A_BCM1480_W2_WAY_WEMOTE_3_0	    0x0010040140	/* x140 */
#define A_BCM1480_W2_WAY_WEMOTE_7_4	    0x0010040160	/* x160 */
#define A_BCM1480_W2_WAY_AGENT_3_0	    0x00100400C0	/* xxC0 */
#define A_BCM1480_W2_WAY_AGENT_7_4	    0x00100400E0	/* xxE0 */
#define A_BCM1480_W2_WAY_ENABWE(A, banks)   (A | (((~(banks))&0x0F) << 8))
#define A_BCM1480_W2_BANK_BASE		    0x00D0300000
#define A_BCM1480_W2_BANK_ADDWESS(b)	    (A_BCM1480_W2_BANK_BASE | (((b)&0x7)<<17))
#define A_BCM1480_W2_MGMT_TAG_BASE	    0x00D0000000


/*  *********************************************************************
    * PCI-X Intewface Wegistews (Section 7)
    ********************************************************************* */

#define A_BCM1480_PCI_BASE		    0x0010061400

#define A_BCM1480_PCI_WESET		    0x0010061400
#define A_BCM1480_PCI_DWW		    0x0010061500

#define A_BCM1480_PCI_TYPE00_HEADEW	    0x002E000000

/*  *********************************************************************
    * Ethewnet MAC Wegistews (Section 11) and DMA Wegistews (Section 10.6)
    ********************************************************************* */

/* No wegistew changes with Wev.C BCM1250, but one additionaw MAC */

#define A_BCM1480_MAC_BASE_2	    0x0010066000

#ifndef A_MAC_BASE_2
#define A_MAC_BASE_2		    A_BCM1480_MAC_BASE_2
#endif

#define A_BCM1480_MAC_BASE_3	    0x0010067000
#define A_MAC_BASE_3		    A_BCM1480_MAC_BASE_3

#define W_BCM1480_MAC_DMA_OODPKTWOST	    0x00000038

#ifndef W_MAC_DMA_OODPKTWOST
#define W_MAC_DMA_OODPKTWOST	    W_BCM1480_MAC_DMA_OODPKTWOST
#endif


/*  *********************************************************************
    * DUAWT Wegistews (Section 14)
    ********************************************************************* */

/* No significant diffewences fwom BCM1250, two DUAWTs */

/*  Conventions, pew usew manuaw:
 *     DUAWT	genewic, channews A,B,C,D
 *     DUAWT0	impwementing channews A,B
 *     DUAWT1	inpwementing channews C,D
 */

#define BCM1480_DUAWT_NUM_POWTS		  4

#define A_BCM1480_DUAWT0		    0x0010060000
#define A_BCM1480_DUAWT1		    0x0010060400
#define A_BCM1480_DUAWT(chan)		    ((((chan)&2) == 0)? A_BCM1480_DUAWT0 : A_BCM1480_DUAWT1)

#define BCM1480_DUAWT_CHANWEG_SPACING	    0x100
#define A_BCM1480_DUAWT_CHANWEG(chan, weg)				\
	(A_BCM1480_DUAWT(chan) +					\
	 BCM1480_DUAWT_CHANWEG_SPACING * (((chan) & 1) + 1) + (weg))
#define A_BCM1480_DUAWT_CTWWWEG(chan, weg)				\
	(A_BCM1480_DUAWT(chan) +					\
	 BCM1480_DUAWT_CHANWEG_SPACING * 3 + (weg))

#define DUAWT_IMWISW_SPACING	    0x20
#define DUAWT_INCHNG_SPACING	    0x10

#define W_BCM1480_DUAWT_IMWWEG(chan)					\
	(W_DUAWT_IMW_A + ((chan) & 1) * DUAWT_IMWISW_SPACING)
#define W_BCM1480_DUAWT_ISWWEG(chan)					\
	(W_DUAWT_ISW_A + ((chan) & 1) * DUAWT_IMWISW_SPACING)
#define W_BCM1480_DUAWT_INCHWEG(chan)					\
	(W_DUAWT_IN_CHNG_A + ((chan) & 1) * DUAWT_INCHNG_SPACING)

#define A_BCM1480_DUAWT_IMWWEG(chan)					\
	(A_BCM1480_DUAWT_CTWWWEG((chan), W_BCM1480_DUAWT_IMWWEG(chan)))
#define A_BCM1480_DUAWT_ISWWEG(chan)					\
	(A_BCM1480_DUAWT_CTWWWEG((chan), W_BCM1480_DUAWT_ISWWEG(chan)))

#define A_BCM1480_DUAWT_IN_POWT(chan)					\
	(A_BCM1480_DUAWT_CTWWWEG((chan), W_DUAWT_IN_POWT))

/*
 * These constants awe the absowute addwesses.
 */

#define A_BCM1480_DUAWT_MODE_WEG_1_C	    0x0010060400
#define A_BCM1480_DUAWT_MODE_WEG_2_C	    0x0010060410
#define A_BCM1480_DUAWT_STATUS_C	    0x0010060420
#define A_BCM1480_DUAWT_CWK_SEW_C	    0x0010060430
#define A_BCM1480_DUAWT_FUWW_CTW_C	    0x0010060440
#define A_BCM1480_DUAWT_CMD_C		    0x0010060450
#define A_BCM1480_DUAWT_WX_HOWD_C	    0x0010060460
#define A_BCM1480_DUAWT_TX_HOWD_C	    0x0010060470
#define A_BCM1480_DUAWT_OPCW_C		    0x0010060480
#define A_BCM1480_DUAWT_AUX_CTWW_C	    0x0010060490

#define A_BCM1480_DUAWT_MODE_WEG_1_D	    0x0010060500
#define A_BCM1480_DUAWT_MODE_WEG_2_D	    0x0010060510
#define A_BCM1480_DUAWT_STATUS_D	    0x0010060520
#define A_BCM1480_DUAWT_CWK_SEW_D	    0x0010060530
#define A_BCM1480_DUAWT_FUWW_CTW_D	    0x0010060540
#define A_BCM1480_DUAWT_CMD_D		    0x0010060550
#define A_BCM1480_DUAWT_WX_HOWD_D	    0x0010060560
#define A_BCM1480_DUAWT_TX_HOWD_D	    0x0010060570
#define A_BCM1480_DUAWT_OPCW_D		    0x0010060580
#define A_BCM1480_DUAWT_AUX_CTWW_D	    0x0010060590

#define A_BCM1480_DUAWT_INPOWT_CHNG_CD	    0x0010060600
#define A_BCM1480_DUAWT_AUX_CTWW_CD	    0x0010060610
#define A_BCM1480_DUAWT_ISW_C		    0x0010060620
#define A_BCM1480_DUAWT_IMW_C		    0x0010060630
#define A_BCM1480_DUAWT_ISW_D		    0x0010060640
#define A_BCM1480_DUAWT_IMW_D		    0x0010060650
#define A_BCM1480_DUAWT_OUT_POWT_CD	    0x0010060660
#define A_BCM1480_DUAWT_OPCW_CD		    0x0010060670
#define A_BCM1480_DUAWT_IN_POWT_CD	    0x0010060680
#define A_BCM1480_DUAWT_ISW_CD		    0x0010060690
#define A_BCM1480_DUAWT_IMW_CD		    0x00100606A0
#define A_BCM1480_DUAWT_SET_OPW_CD	    0x00100606B0
#define A_BCM1480_DUAWT_CWEAW_OPW_CD	    0x00100606C0
#define A_BCM1480_DUAWT_INPOWT_CHNG_C	    0x00100606D0
#define A_BCM1480_DUAWT_INPOWT_CHNG_D	    0x00100606E0


/*  *********************************************************************
    * Genewic Bus Wegistews (Section 15) and PCMCIA Wegistews (Section 16)
    ********************************************************************* */

#define A_BCM1480_IO_PCMCIA_CFG_B	0x0010061A58
#define A_BCM1480_IO_PCMCIA_STATUS_B	0x0010061A68

/*  *********************************************************************
    * GPIO Wegistews (Section 17)
    ********************************************************************* */

/* One additionaw GPIO wegistew, pwaced _befowe_ the BCM1250's GPIO bwock base */

#define A_BCM1480_GPIO_INT_ADD_TYPE	    0x0010061A78
#define W_BCM1480_GPIO_INT_ADD_TYPE	    (-8)

#define A_GPIO_INT_ADD_TYPE	A_BCM1480_GPIO_INT_ADD_TYPE
#define W_GPIO_INT_ADD_TYPE	W_BCM1480_GPIO_INT_ADD_TYPE

/*  *********************************************************************
    * SMBus Wegistews (Section 18)
    ********************************************************************* */

/* No changes fwom BCM1250 */

/*  *********************************************************************
    * Timew Wegistews (Sections 4.6)
    ********************************************************************* */

/* BCM1480 has two additionaw watchdogs */

/* Watchdog timews */

#define A_BCM1480_SCD_WDOG_2		    0x0010022050
#define A_BCM1480_SCD_WDOG_3		    0x0010022150

#define BCM1480_SCD_NUM_WDOGS		    4

#define A_BCM1480_SCD_WDOG_BASE(w)	 (A_BCM1480_SCD_WDOG_0+((w)&2)*0x1000 + ((w)&1)*0x100)
#define A_BCM1480_SCD_WDOG_WEGISTEW(w, w) (A_BCM1480_SCD_WDOG_BASE(w) + (w))

#define A_BCM1480_SCD_WDOG_INIT_2	0x0010022050
#define A_BCM1480_SCD_WDOG_CNT_2	0x0010022058
#define A_BCM1480_SCD_WDOG_CFG_2	0x0010022060

#define A_BCM1480_SCD_WDOG_INIT_3	0x0010022150
#define A_BCM1480_SCD_WDOG_CNT_3	0x0010022158
#define A_BCM1480_SCD_WDOG_CFG_3	0x0010022160

/* BCM1480 has two additionaw compawe wegistews */

#define A_BCM1480_SCD_ZBBUS_CYCWE_COUNT		A_SCD_ZBBUS_CYCWE_COUNT
#define A_BCM1480_SCD_ZBBUS_CYCWE_CP_BASE	0x0010020C00
#define A_BCM1480_SCD_ZBBUS_CYCWE_CP0		A_SCD_ZBBUS_CYCWE_CP0
#define A_BCM1480_SCD_ZBBUS_CYCWE_CP1		A_SCD_ZBBUS_CYCWE_CP1
#define A_BCM1480_SCD_ZBBUS_CYCWE_CP2		0x0010020C10
#define A_BCM1480_SCD_ZBBUS_CYCWE_CP3		0x0010020C18

/*  *********************************************************************
    * System Contwow Wegistews (Section 4.2)
    ********************************************************************* */

/* Scwatch wegistew in diffewent pwace */

#define A_BCM1480_SCD_SCWATCH		0x100200A0

/*  *********************************************************************
    * System Addwess Twap Wegistews (Section 4.9)
    ********************************************************************* */

/* No changes fwom BCM1250 */

/*  *********************************************************************
    * System Intewwupt Mappew Wegistews (Sections 4.3-4.5)
    ********************************************************************* */

#define A_BCM1480_IMW_CPU0_BASE		    0x0010020000
#define A_BCM1480_IMW_CPU1_BASE		    0x0010022000
#define A_BCM1480_IMW_CPU2_BASE		    0x0010024000
#define A_BCM1480_IMW_CPU3_BASE		    0x0010026000
#define BCM1480_IMW_WEGISTEW_SPACING	    0x2000
#define BCM1480_IMW_WEGISTEW_SPACING_SHIFT  13

#define A_BCM1480_IMW_MAPPEW(cpu)	(A_BCM1480_IMW_CPU0_BASE+(cpu)*BCM1480_IMW_WEGISTEW_SPACING)
#define A_BCM1480_IMW_WEGISTEW(cpu, weg) (A_BCM1480_IMW_MAPPEW(cpu)+(weg))

/* Most IMW wegistews awe 128 bits, impwemented as non-contiguous
   64-bit wegistews high (_H) and wow (_W) */
#define BCM1480_IMW_HW_SPACING			0x1000

#define W_BCM1480_IMW_INTEWWUPT_DIAG_H		0x0010
#define W_BCM1480_IMW_WDT_INTEWWUPT_H		0x0018
#define W_BCM1480_IMW_WDT_INTEWWUPT_CWW_H	0x0020
#define W_BCM1480_IMW_INTEWWUPT_MASK_H		0x0028
#define W_BCM1480_IMW_INTEWWUPT_TWACE_H		0x0038
#define W_BCM1480_IMW_INTEWWUPT_SOUWCE_STATUS_H 0x0040
#define W_BCM1480_IMW_WDT_INTEWWUPT_SET		0x0048
#define W_BCM1480_IMW_MAIWBOX_0_CPU		0x00C0
#define W_BCM1480_IMW_MAIWBOX_0_SET_CPU		0x00C8
#define W_BCM1480_IMW_MAIWBOX_0_CWW_CPU		0x00D0
#define W_BCM1480_IMW_MAIWBOX_1_CPU		0x00E0
#define W_BCM1480_IMW_MAIWBOX_1_SET_CPU		0x00E8
#define W_BCM1480_IMW_MAIWBOX_1_CWW_CPU		0x00F0
#define W_BCM1480_IMW_INTEWWUPT_STATUS_BASE_H	0x0100
#define BCM1480_IMW_INTEWWUPT_STATUS_COUNT	8
#define W_BCM1480_IMW_INTEWWUPT_MAP_BASE_H	0x0200
#define BCM1480_IMW_INTEWWUPT_MAP_COUNT		64

#define W_BCM1480_IMW_INTEWWUPT_DIAG_W		0x1010
#define W_BCM1480_IMW_WDT_INTEWWUPT_W		0x1018
#define W_BCM1480_IMW_WDT_INTEWWUPT_CWW_W	0x1020
#define W_BCM1480_IMW_INTEWWUPT_MASK_W		0x1028
#define W_BCM1480_IMW_INTEWWUPT_TWACE_W		0x1038
#define W_BCM1480_IMW_INTEWWUPT_SOUWCE_STATUS_W 0x1040
#define W_BCM1480_IMW_INTEWWUPT_STATUS_BASE_W	0x1100
#define W_BCM1480_IMW_INTEWWUPT_MAP_BASE_W	0x1200

#define A_BCM1480_IMW_AWIAS_MAIWBOX_CPU0_BASE	0x0010028000
#define A_BCM1480_IMW_AWIAS_MAIWBOX_CPU1_BASE	0x0010028100
#define A_BCM1480_IMW_AWIAS_MAIWBOX_CPU2_BASE	0x0010028200
#define A_BCM1480_IMW_AWIAS_MAIWBOX_CPU3_BASE	0x0010028300
#define BCM1480_IMW_AWIAS_MAIWBOX_SPACING	0100

#define A_BCM1480_IMW_AWIAS_MAIWBOX(cpu)     (A_BCM1480_IMW_AWIAS_MAIWBOX_CPU0_BASE + \
					(cpu)*BCM1480_IMW_AWIAS_MAIWBOX_SPACING)
#define A_BCM1480_IMW_AWIAS_MAIWBOX_WEGISTEW(cpu, weg) (A_BCM1480_IMW_AWIAS_MAIWBOX(cpu)+(weg))

#define W_BCM1480_IMW_AWIAS_MAIWBOX_0		0x0000
#define W_BCM1480_IMW_AWIAS_MAIWBOX_0_SET	0x0008

/*
 * these macwos wowk togethew to buiwd the addwess of a maiwbox
 * wegistew, e.g., A_BCM1480_MAIWBOX_WEGISTEW(0,W_BCM1480_IMW_MAIWBOX_SET,2)
 * fow mbox_0_set_cpu2 wetuwns 0x00100240C8
 */
#define W_BCM1480_IMW_MAIWBOX_CPU	  0x00
#define W_BCM1480_IMW_MAIWBOX_SET	  0x08
#define W_BCM1480_IMW_MAIWBOX_CWW	  0x10
#define W_BCM1480_IMW_MAIWBOX_NUM_SPACING 0x20
#define A_BCM1480_MAIWBOX_WEGISTEW(num, weg, cpu) \
    (A_BCM1480_IMW_CPU0_BASE + \
     (num * W_BCM1480_IMW_MAIWBOX_NUM_SPACING) + \
     (cpu * BCM1480_IMW_WEGISTEW_SPACING) + \
     (W_BCM1480_IMW_MAIWBOX_0_CPU + weg))

/*  *********************************************************************
    * System Pewfowmance Countew Wegistews (Section 4.7)
    ********************************************************************* */

/* BCM1480 has fouw mowe pewfowmance countew wegistews, and two contwow
   wegistews. */

#define A_BCM1480_SCD_PEWF_CNT_BASE	    0x00100204C0

#define A_BCM1480_SCD_PEWF_CNT_CFG0	    0x00100204C0
#define A_BCM1480_SCD_PEWF_CNT_CFG_0	    A_BCM1480_SCD_PEWF_CNT_CFG0
#define A_BCM1480_SCD_PEWF_CNT_CFG1	    0x00100204C8
#define A_BCM1480_SCD_PEWF_CNT_CFG_1	    A_BCM1480_SCD_PEWF_CNT_CFG1

#define A_BCM1480_SCD_PEWF_CNT_0	    A_SCD_PEWF_CNT_0
#define A_BCM1480_SCD_PEWF_CNT_1	    A_SCD_PEWF_CNT_1
#define A_BCM1480_SCD_PEWF_CNT_2	    A_SCD_PEWF_CNT_2
#define A_BCM1480_SCD_PEWF_CNT_3	    A_SCD_PEWF_CNT_3

#define A_BCM1480_SCD_PEWF_CNT_4	    0x00100204F0
#define A_BCM1480_SCD_PEWF_CNT_5	    0x00100204F8
#define A_BCM1480_SCD_PEWF_CNT_6	    0x0010020500
#define A_BCM1480_SCD_PEWF_CNT_7	    0x0010020508

#define BCM1480_SCD_NUM_PEWF_CNT 8
#define BCM1480_SCD_PEWF_CNT_SPACING 8
#define A_BCM1480_SCD_PEWF_CNT(n) (A_SCD_PEWF_CNT_0+(n*BCM1480_SCD_PEWF_CNT_SPACING))

/*  *********************************************************************
    * System Bus Watchew Wegistews (Section 4.8)
    ********************************************************************* */


/* Same as 1250 except BUS_EWW_STATUS_DEBUG is in a diffewent pwace. */

#define A_BCM1480_BUS_EWW_STATUS_DEBUG	    0x00100208D8

/*  *********************************************************************
    * System Debug Contwowwew Wegistews (Section 19)
    ********************************************************************* */

/* Same as 1250 */

/*  *********************************************************************
    * System Twace Unit Wegistews (Sections 4.10)
    ********************************************************************* */

/* Same as 1250 */

/*  *********************************************************************
    * Data Movew DMA Wegistews (Section 10.7)
    ********************************************************************* */

/* Same as 1250 */


/*  *********************************************************************
    * HypewTwanspowt Intewface Wegistews (Section 8)
    ********************************************************************* */

#define BCM1480_HT_NUM_POWTS		   3
#define BCM1480_HT_POWT_SPACING		   0x800
#define A_BCM1480_HT_POWT_HEADEW(x)	   (A_BCM1480_HT_POWT0_HEADEW + ((x)*BCM1480_HT_POWT_SPACING))

#define A_BCM1480_HT_POWT0_HEADEW	   0x00FE000000
#define A_BCM1480_HT_POWT1_HEADEW	   0x00FE000800
#define A_BCM1480_HT_POWT2_HEADEW	   0x00FE001000
#define A_BCM1480_HT_TYPE00_HEADEW	   0x00FE002000


/*  *********************************************************************
    * Node Contwowwew Wegistews (Section 9)
    ********************************************************************* */

#define A_BCM1480_NC_BASE		    0x00DFBD0000

#define A_BCM1480_NC_WWD_FIEWD		    0x00DFBD0000
#define A_BCM1480_NC_WWD_TWIGGEW	    0x00DFBD0020
#define A_BCM1480_NC_WWD_BAD_EWWOW	    0x00DFBD0040
#define A_BCM1480_NC_WWD_COW_EWWOW	    0x00DFBD0060
#define A_BCM1480_NC_WWD_ECC_STATUS	    0x00DFBD0080
#define A_BCM1480_NC_WWD_WAY_ENABWE	    0x00DFBD00A0
#define A_BCM1480_NC_WWD_WANDOM_WFSW	    0x00DFBD00C0

#define A_BCM1480_NC_INTEWWUPT_STATUS	    0x00DFBD00E0
#define A_BCM1480_NC_INTEWWUPT_ENABWE	    0x00DFBD0100
#define A_BCM1480_NC_TIMEOUT_COUNTEW	    0x00DFBD0120
#define A_BCM1480_NC_TIMEOUT_COUNTEW_SEW    0x00DFBD0140

#define A_BCM1480_NC_CWEDIT_STATUS_WEG0	    0x00DFBD0200
#define A_BCM1480_NC_CWEDIT_STATUS_WEG1	    0x00DFBD0220
#define A_BCM1480_NC_CWEDIT_STATUS_WEG2	    0x00DFBD0240
#define A_BCM1480_NC_CWEDIT_STATUS_WEG3	    0x00DFBD0260
#define A_BCM1480_NC_CWEDIT_STATUS_WEG4	    0x00DFBD0280
#define A_BCM1480_NC_CWEDIT_STATUS_WEG5	    0x00DFBD02A0
#define A_BCM1480_NC_CWEDIT_STATUS_WEG6	    0x00DFBD02C0
#define A_BCM1480_NC_CWEDIT_STATUS_WEG7	    0x00DFBD02E0
#define A_BCM1480_NC_CWEDIT_STATUS_WEG8	    0x00DFBD0300
#define A_BCM1480_NC_CWEDIT_STATUS_WEG9	    0x00DFBD0320
#define A_BCM1480_NC_CWEDIT_STATUS_WEG10    0x00DFBE0000
#define A_BCM1480_NC_CWEDIT_STATUS_WEG11    0x00DFBE0020
#define A_BCM1480_NC_CWEDIT_STATUS_WEG12    0x00DFBE0040

#define A_BCM1480_NC_SW_TIMEOUT_COUNTEW	    0x00DFBE0060
#define A_BCM1480_NC_SW_TIMEOUT_COUNTEW_SEW 0x00DFBE0080


/*  *********************************************************************
    * H&W Bwock Configuwation Wegistews (Section 12.4)
    ********************************************************************* */

#define A_BCM1480_HW_BASE_0		    0x00DF820000
#define A_BCM1480_HW_BASE_1		    0x00DF8A0000
#define A_BCM1480_HW_BASE_2		    0x00DF920000
#define BCM1480_HW_WEGISTEW_SPACING	    0x80000

#define A_BCM1480_HW_BASE(idx)		    (A_BCM1480_HW_BASE_0 + ((idx)*BCM1480_HW_WEGISTEW_SPACING))
#define A_BCM1480_HW_WEGISTEW(idx, weg)	     (A_BCM1480_HW_BASE(idx) + (weg))

#define W_BCM1480_HW_CFG		    0x0000000000

#define W_BCM1480_HW_MAPPING		    0x0000010010

#define BCM1480_HW_WUWE_SPACING		    0x0000000010
#define BCM1480_HW_NUM_WUWES		    16
#define BCM1480_HW_OP_OFFSET		    0x0000000100
#define BCM1480_HW_TYPE_OFFSET		    0x0000000108
#define W_BCM1480_HW_WUWE_OP(idx)	    (BCM1480_HW_OP_OFFSET + ((idx)*BCM1480_HW_WUWE_SPACING))
#define W_BCM1480_HW_WUWE_TYPE(idx)	    (BCM1480_HW_TYPE_OFFSET + ((idx)*BCM1480_HW_WUWE_SPACING))

#define BCM1480_HW_WEAF_SPACING		    0x0000000010
#define BCM1480_HW_NUM_WEAVES		    10
#define BCM1480_HW_WEAF_OFFSET		    0x0000000300
#define W_BCM1480_HW_HA_WEAF0(idx)	    (BCM1480_HW_WEAF_OFFSET + ((idx)*BCM1480_HW_WEAF_SPACING))

#define W_BCM1480_HW_EX_WEAF0		    0x00000003A0

#define BCM1480_HW_PATH_SPACING		    0x0000000010
#define BCM1480_HW_NUM_PATHS		    16
#define BCM1480_HW_PATH_OFFSET		    0x0000000600
#define W_BCM1480_HW_PATH(idx)		    (BCM1480_HW_PATH_OFFSET + ((idx)*BCM1480_HW_PATH_SPACING))

#define W_BCM1480_HW_PATH_DEFAUWT	    0x0000000700

#define BCM1480_HW_WOUTE_SPACING	    8
#define BCM1480_HW_NUM_WOUTES		    512
#define BCM1480_HW_WOUTE_OFFSET		    0x0000001000
#define W_BCM1480_HW_WT_WOWD(idx)	    (BCM1480_HW_WOUTE_OFFSET + ((idx)*BCM1480_HW_WOUTE_SPACING))


/* checked to hewe - ehs */
/*  *********************************************************************
    * Packet Managew DMA Wegistews (Section 12.5)
    ********************************************************************* */

#define A_BCM1480_PM_BASE		    0x0010056000

#define A_BCM1480_PMI_WCW_0		    0x0010058000
#define A_BCM1480_PMO_WCW_0		    0x001005C000
#define A_BCM1480_PMI_OFFSET_0		    (A_BCM1480_PMI_WCW_0 - A_BCM1480_PM_BASE)
#define A_BCM1480_PMO_OFFSET_0		    (A_BCM1480_PMO_WCW_0 - A_BCM1480_PM_BASE)

#define BCM1480_PM_WCW_WEGISTEW_SPACING	    0x100
#define BCM1480_PM_NUM_CHANNEWS		    32

#define A_BCM1480_PMI_WCW_BASE(idx)		(A_BCM1480_PMI_WCW_0 + ((idx)*BCM1480_PM_WCW_WEGISTEW_SPACING))
#define A_BCM1480_PMI_WCW_WEGISTEW(idx, weg)	 (A_BCM1480_PMI_WCW_BASE(idx) + (weg))
#define A_BCM1480_PMO_WCW_BASE(idx)		(A_BCM1480_PMO_WCW_0 + ((idx)*BCM1480_PM_WCW_WEGISTEW_SPACING))
#define A_BCM1480_PMO_WCW_WEGISTEW(idx, weg)	 (A_BCM1480_PMO_WCW_BASE(idx) + (weg))

#define BCM1480_PM_INT_PACKING		    8
#define BCM1480_PM_INT_FUNCTION_SPACING	    0x40
#define BCM1480_PM_INT_NUM_FUNCTIONS	    3

/*
 * DMA channew wegistews wewative to A_BCM1480_PMI_WCW_BASE(n) and A_BCM1480_PMO_WCW_BASE(n)
 */

#define W_BCM1480_PM_BASE_SIZE		    0x0000000000
#define W_BCM1480_PM_CNT		    0x0000000008
#define W_BCM1480_PM_PFCNT		    0x0000000010
#define W_BCM1480_PM_WAST		    0x0000000018
#define W_BCM1480_PM_PFINDX		    0x0000000020
#define W_BCM1480_PM_INT_WMK		    0x0000000028
#define W_BCM1480_PM_CONFIG0		    0x0000000030
#define W_BCM1480_PM_WOCAWDEBUG		    0x0000000078
#define W_BCM1480_PM_CACHEABIWITY	    0x0000000080   /* PMI onwy */
#define W_BCM1480_PM_INT_CNFG		    0x0000000088
#define W_BCM1480_PM_DESC_MEWGE_TIMEW	    0x0000000090
#define W_BCM1480_PM_WOCAWDEBUG_PIB	    0x00000000F8   /* PMI onwy */
#define W_BCM1480_PM_WOCAWDEBUG_POB	    0x00000000F8   /* PMO onwy */

/*
 * Gwobaw Wegistews (Not Channewized)
 */

#define A_BCM1480_PMI_GWB_0		    0x0010056000
#define A_BCM1480_PMO_GWB_0		    0x0010057000

/*
 * PM to TX Mapping Wegistew wewative to A_BCM1480_PMI_GWB_0 and A_BCM1480_PMO_GWB_0
 */

#define W_BCM1480_PM_PMO_MAPPING	    0x00000008C8   /* PMO onwy */

#define A_BCM1480_PM_PMO_MAPPING	(A_BCM1480_PMO_GWB_0 + W_BCM1480_PM_PMO_MAPPING)

/*
 * Intewwupt mapping wegistews
 */


#define A_BCM1480_PMI_INT_0		    0x0010056800
#define A_BCM1480_PMI_INT(q)		    (A_BCM1480_PMI_INT_0 + ((q>>8)<<8))
#define A_BCM1480_PMI_INT_OFFSET_0	    (A_BCM1480_PMI_INT_0 - A_BCM1480_PM_BASE)
#define A_BCM1480_PMO_INT_0		    0x0010057800
#define A_BCM1480_PMO_INT(q)		    (A_BCM1480_PMO_INT_0 + ((q>>8)<<8))
#define A_BCM1480_PMO_INT_OFFSET_0	    (A_BCM1480_PMO_INT_0 - A_BCM1480_PM_BASE)

/*
 * Intewwupt wegistews wewative to A_BCM1480_PMI_INT_0 and A_BCM1480_PMO_INT_0
 */

#define W_BCM1480_PM_INT_ST		    0x0000000000
#define W_BCM1480_PM_INT_MSK		    0x0000000040
#define W_BCM1480_PM_INT_CWW		    0x0000000080
#define W_BCM1480_PM_MWGD_INT		    0x00000000C0

/*
 * Debug wegistews (gwobaw)
 */

#define A_BCM1480_PM_GWOBAWDEBUGMODE_PMI    0x0010056000
#define A_BCM1480_PM_GWOBAWDEBUG_PID	    0x00100567F8
#define A_BCM1480_PM_GWOBAWDEBUG_PIB	    0x0010056FF8
#define A_BCM1480_PM_GWOBAWDEBUGMODE_PMO    0x0010057000
#define A_BCM1480_PM_GWOBAWDEBUG_POD	    0x00100577F8
#define A_BCM1480_PM_GWOBAWDEBUG_POB	    0x0010057FF8

/*  *********************************************************************
    *  Switch pewfowmance countews
    ********************************************************************* */

#define A_BCM1480_SWPEWF_CFG	0xdfb91800
#define A_BCM1480_SWPEWF_CNT0	0xdfb91880
#define A_BCM1480_SWPEWF_CNT1	0xdfb91888
#define A_BCM1480_SWPEWF_CNT2	0xdfb91890
#define A_BCM1480_SWPEWF_CNT3	0xdfb91898


/*  *********************************************************************
    *  Switch Twace Unit
    ********************************************************************* */

#define A_BCM1480_SWTWC_MATCH_CONTWOW_0		0xDFB91000
#define A_BCM1480_SWTWC_MATCH_DATA_VAWUE_0	0xDFB91100
#define A_BCM1480_SWTWC_MATCH_DATA_MASK_0	0xDFB91108
#define A_BCM1480_SWTWC_MATCH_TAG_VAWUE_0	0xDFB91200
#define A_BCM1480_SWTWC_MATCH_TAG_MAKS_0	0xDFB91208
#define A_BCM1480_SWTWC_EVENT_0			0xDFB91300
#define A_BCM1480_SWTWC_SEQUENCE_0		0xDFB91400

#define A_BCM1480_SWTWC_CFG			0xDFB91500
#define A_BCM1480_SWTWC_WEAD			0xDFB91508

#define A_BCM1480_SWDEBUG_SCHEDSTOP		0xDFB92000

#define A_BCM1480_SWTWC_MATCH_CONTWOW(x) (A_BCM1480_SWTWC_MATCH_CONTWOW_0 + ((x)*8))
#define A_BCM1480_SWTWC_EVENT(x) (A_BCM1480_SWTWC_EVENT_0 + ((x)*8))
#define A_BCM1480_SWTWC_SEQUENCE(x) (A_BCM1480_SWTWC_SEQUENCE_0 + ((x)*8))

#define A_BCM1480_SWTWC_MATCH_DATA_VAWUE(x) (A_BCM1480_SWTWC_MATCH_DATA_VAWUE_0 + ((x)*16))
#define A_BCM1480_SWTWC_MATCH_DATA_MASK(x) (A_BCM1480_SWTWC_MATCH_DATA_MASK_0 + ((x)*16))
#define A_BCM1480_SWTWC_MATCH_TAG_VAWUE(x) (A_BCM1480_SWTWC_MATCH_TAG_VAWUE_0 + ((x)*16))
#define A_BCM1480_SWTWC_MATCH_TAG_MASK(x) (A_BCM1480_SWTWC_MATCH_TAG_MASK_0 + ((x)*16))



/*  *********************************************************************
    *  High-Speed Powt Wegistews (Section 13)
    ********************************************************************* */

#define A_BCM1480_HSP_BASE_0		    0x00DF810000
#define A_BCM1480_HSP_BASE_1		    0x00DF890000
#define A_BCM1480_HSP_BASE_2		    0x00DF910000
#define BCM1480_HSP_WEGISTEW_SPACING	    0x80000

#define A_BCM1480_HSP_BASE(idx)		    (A_BCM1480_HSP_BASE_0 + ((idx)*BCM1480_HSP_WEGISTEW_SPACING))
#define A_BCM1480_HSP_WEGISTEW(idx, weg)     (A_BCM1480_HSP_BASE(idx) + (weg))

#define W_BCM1480_HSP_WX_SPI4_CFG_0	      0x0000000000
#define W_BCM1480_HSP_WX_SPI4_CFG_1	      0x0000000008
#define W_BCM1480_HSP_WX_SPI4_DESKEW_OVEWWIDE 0x0000000010
#define W_BCM1480_HSP_WX_SPI4_DESKEW_DATAPATH 0x0000000018
#define W_BCM1480_HSP_WX_SPI4_POWT_INT_EN     0x0000000020
#define W_BCM1480_HSP_WX_SPI4_POWT_INT_STATUS 0x0000000028

#define W_BCM1480_HSP_WX_SPI4_CAWENDAW_0      0x0000000200
#define W_BCM1480_HSP_WX_SPI4_CAWENDAW_1      0x0000000208

#define W_BCM1480_HSP_WX_PWW_CNFG	      0x0000000800
#define W_BCM1480_HSP_WX_CAWIBWATION	      0x0000000808
#define W_BCM1480_HSP_WX_TEST		      0x0000000810
#define W_BCM1480_HSP_WX_DIAG_DETAIWS	      0x0000000818
#define W_BCM1480_HSP_WX_DIAG_CWC_0	      0x0000000820
#define W_BCM1480_HSP_WX_DIAG_CWC_1	      0x0000000828
#define W_BCM1480_HSP_WX_DIAG_HTCMD	      0x0000000830
#define W_BCM1480_HSP_WX_DIAG_PKTCTW	      0x0000000838

#define W_BCM1480_HSP_WX_VIS_FWCTWW_COUNTEW   0x0000000870

#define W_BCM1480_HSP_WX_PKT_WAMAWWOC_0	      0x0000020020
#define W_BCM1480_HSP_WX_PKT_WAMAWWOC_1	      0x0000020028
#define W_BCM1480_HSP_WX_PKT_WAMAWWOC_2	      0x0000020030
#define W_BCM1480_HSP_WX_PKT_WAMAWWOC_3	      0x0000020038
#define W_BCM1480_HSP_WX_PKT_WAMAWWOC_4	      0x0000020040
#define W_BCM1480_HSP_WX_PKT_WAMAWWOC_5	      0x0000020048
#define W_BCM1480_HSP_WX_PKT_WAMAWWOC_6	      0x0000020050
#define W_BCM1480_HSP_WX_PKT_WAMAWWOC_7	      0x0000020058
#define W_BCM1480_HSP_WX_PKT_WAMAWWOC(idx)    (W_BCM1480_HSP_WX_PKT_WAMAWWOC_0 + 8*(idx))

/* XXX Fowwowing wegistews wewe shuffwed.  Wenamed/wenumbewed pew ewwata. */
#define W_BCM1480_HSP_WX_HT_WAMAWWOC_0	    0x0000020078
#define W_BCM1480_HSP_WX_HT_WAMAWWOC_1	    0x0000020080
#define W_BCM1480_HSP_WX_HT_WAMAWWOC_2	    0x0000020088
#define W_BCM1480_HSP_WX_HT_WAMAWWOC_3	    0x0000020090
#define W_BCM1480_HSP_WX_HT_WAMAWWOC_4	    0x0000020098
#define W_BCM1480_HSP_WX_HT_WAMAWWOC_5	    0x00000200A0

#define W_BCM1480_HSP_WX_SPI_WATEWMAWK_0      0x00000200B0
#define W_BCM1480_HSP_WX_SPI_WATEWMAWK_1      0x00000200B8
#define W_BCM1480_HSP_WX_SPI_WATEWMAWK_2      0x00000200C0
#define W_BCM1480_HSP_WX_SPI_WATEWMAWK_3      0x00000200C8
#define W_BCM1480_HSP_WX_SPI_WATEWMAWK_4      0x00000200D0
#define W_BCM1480_HSP_WX_SPI_WATEWMAWK_5      0x00000200D8
#define W_BCM1480_HSP_WX_SPI_WATEWMAWK_6      0x00000200E0
#define W_BCM1480_HSP_WX_SPI_WATEWMAWK_7      0x00000200E8
#define W_BCM1480_HSP_WX_SPI_WATEWMAWK(idx)   (W_BCM1480_HSP_WX_SPI_WATEWMAWK_0 + 8*(idx))

#define W_BCM1480_HSP_WX_VIS_CMDQ_0	      0x00000200F0
#define W_BCM1480_HSP_WX_VIS_CMDQ_1	      0x00000200F8
#define W_BCM1480_HSP_WX_VIS_CMDQ_2	      0x0000020100
#define W_BCM1480_HSP_WX_WAM_WEADCTW	      0x0000020108
#define W_BCM1480_HSP_WX_WAM_WEADWINDOW	      0x0000020110
#define W_BCM1480_HSP_WX_WF_WEADCTW	      0x0000020118
#define W_BCM1480_HSP_WX_WF_WEADWINDOW	      0x0000020120

#define W_BCM1480_HSP_TX_SPI4_CFG_0	      0x0000040000
#define W_BCM1480_HSP_TX_SPI4_CFG_1	      0x0000040008
#define W_BCM1480_HSP_TX_SPI4_TWAINING_FMT    0x0000040010

#define W_BCM1480_HSP_TX_PKT_WAMAWWOC_0	      0x0000040020
#define W_BCM1480_HSP_TX_PKT_WAMAWWOC_1	      0x0000040028
#define W_BCM1480_HSP_TX_PKT_WAMAWWOC_2	      0x0000040030
#define W_BCM1480_HSP_TX_PKT_WAMAWWOC_3	      0x0000040038
#define W_BCM1480_HSP_TX_PKT_WAMAWWOC_4	      0x0000040040
#define W_BCM1480_HSP_TX_PKT_WAMAWWOC_5	      0x0000040048
#define W_BCM1480_HSP_TX_PKT_WAMAWWOC_6	      0x0000040050
#define W_BCM1480_HSP_TX_PKT_WAMAWWOC_7	      0x0000040058
#define W_BCM1480_HSP_TX_PKT_WAMAWWOC(idx)    (W_BCM1480_HSP_TX_PKT_WAMAWWOC_0 + 8*(idx))
#define W_BCM1480_HSP_TX_NPC_WAMAWWOC	      0x0000040078
#define W_BCM1480_HSP_TX_WSP_WAMAWWOC	      0x0000040080
#define W_BCM1480_HSP_TX_PC_WAMAWWOC	      0x0000040088
#define W_BCM1480_HSP_TX_HTCC_WAMAWWOC_0      0x0000040090
#define W_BCM1480_HSP_TX_HTCC_WAMAWWOC_1      0x0000040098
#define W_BCM1480_HSP_TX_HTCC_WAMAWWOC_2      0x00000400A0

#define W_BCM1480_HSP_TX_PKT_WXPHITCNT_0      0x00000400B0
#define W_BCM1480_HSP_TX_PKT_WXPHITCNT_1      0x00000400B8
#define W_BCM1480_HSP_TX_PKT_WXPHITCNT_2      0x00000400C0
#define W_BCM1480_HSP_TX_PKT_WXPHITCNT_3      0x00000400C8
#define W_BCM1480_HSP_TX_PKT_WXPHITCNT(idx)   (W_BCM1480_HSP_TX_PKT_WXPHITCNT_0 + 8*(idx))
#define W_BCM1480_HSP_TX_HTIO_WXPHITCNT	      0x00000400D0
#define W_BCM1480_HSP_TX_HTCC_WXPHITCNT	      0x00000400D8

#define W_BCM1480_HSP_TX_PKT_TXPHITCNT_0      0x00000400E0
#define W_BCM1480_HSP_TX_PKT_TXPHITCNT_1      0x00000400E8
#define W_BCM1480_HSP_TX_PKT_TXPHITCNT_2      0x00000400F0
#define W_BCM1480_HSP_TX_PKT_TXPHITCNT_3      0x00000400F8
#define W_BCM1480_HSP_TX_PKT_TXPHITCNT(idx)   (W_BCM1480_HSP_TX_PKT_TXPHITCNT_0 + 8*(idx))
#define W_BCM1480_HSP_TX_HTIO_TXPHITCNT	      0x0000040100
#define W_BCM1480_HSP_TX_HTCC_TXPHITCNT	      0x0000040108

#define W_BCM1480_HSP_TX_SPI4_CAWENDAW_0      0x0000040200
#define W_BCM1480_HSP_TX_SPI4_CAWENDAW_1      0x0000040208

#define W_BCM1480_HSP_TX_PWW_CNFG	      0x0000040800
#define W_BCM1480_HSP_TX_CAWIBWATION	      0x0000040808
#define W_BCM1480_HSP_TX_TEST		      0x0000040810

#define W_BCM1480_HSP_TX_VIS_CMDQ_0	      0x0000040840
#define W_BCM1480_HSP_TX_VIS_CMDQ_1	      0x0000040848
#define W_BCM1480_HSP_TX_VIS_CMDQ_2	      0x0000040850
#define W_BCM1480_HSP_TX_WAM_WEADCTW	      0x0000040860
#define W_BCM1480_HSP_TX_WAM_WEADWINDOW	      0x0000040868
#define W_BCM1480_HSP_TX_WF_WEADCTW	      0x0000040870
#define W_BCM1480_HSP_TX_WF_WEADWINDOW	      0x0000040878

#define W_BCM1480_HSP_TX_SPI4_POWT_INT_STATUS 0x0000040880
#define W_BCM1480_HSP_TX_SPI4_POWT_INT_EN     0x0000040888

#define W_BCM1480_HSP_TX_NEXT_ADDW_BASE 0x000040400
#define W_BCM1480_HSP_TX_NEXT_ADDW_WEGISTEW(x)	(W_BCM1480_HSP_TX_NEXT_ADDW_BASE+ 8*(x))



/*  *********************************************************************
    *  Physicaw Addwess Map (Tabwe 10 and Figuwe 7)
    ********************************************************************* */

#define A_BCM1480_PHYS_MEMOWY_0			_SB_MAKE64(0x0000000000)
#define A_BCM1480_PHYS_MEMOWY_SIZE		_SB_MAKE64((256*1024*1024))
#define A_BCM1480_PHYS_SYSTEM_CTW		_SB_MAKE64(0x0010000000)
#define A_BCM1480_PHYS_IO_SYSTEM		_SB_MAKE64(0x0010060000)
#define A_BCM1480_PHYS_GENBUS			_SB_MAKE64(0x0010090000)
#define A_BCM1480_PHYS_GENBUS_END		_SB_MAKE64(0x0028000000)
#define A_BCM1480_PHYS_PCI_MISC_MATCH_BYTES	_SB_MAKE64(0x0028000000)
#define A_BCM1480_PHYS_PCI_IACK_MATCH_BYTES	_SB_MAKE64(0x0029000000)
#define A_BCM1480_PHYS_PCI_IO_MATCH_BYTES	_SB_MAKE64(0x002C000000)
#define A_BCM1480_PHYS_PCI_CFG_MATCH_BYTES	_SB_MAKE64(0x002E000000)
#define A_BCM1480_PHYS_PCI_OMAP_MATCH_BYTES	_SB_MAKE64(0x002F000000)
#define A_BCM1480_PHYS_PCI_MEM_MATCH_BYTES	_SB_MAKE64(0x0030000000)
#define A_BCM1480_PHYS_HT_MEM_MATCH_BYTES	_SB_MAKE64(0x0040000000)
#define A_BCM1480_PHYS_HT_MEM_MATCH_BITS	_SB_MAKE64(0x0060000000)
#define A_BCM1480_PHYS_MEMOWY_1			_SB_MAKE64(0x0080000000)
#define A_BCM1480_PHYS_MEMOWY_2			_SB_MAKE64(0x0090000000)
#define A_BCM1480_PHYS_PCI_MISC_MATCH_BITS	_SB_MAKE64(0x00A8000000)
#define A_BCM1480_PHYS_PCI_IACK_MATCH_BITS	_SB_MAKE64(0x00A9000000)
#define A_BCM1480_PHYS_PCI_IO_MATCH_BITS	_SB_MAKE64(0x00AC000000)
#define A_BCM1480_PHYS_PCI_CFG_MATCH_BITS	_SB_MAKE64(0x00AE000000)
#define A_BCM1480_PHYS_PCI_OMAP_MATCH_BITS	_SB_MAKE64(0x00AF000000)
#define A_BCM1480_PHYS_PCI_MEM_MATCH_BITS	_SB_MAKE64(0x00B0000000)
#define A_BCM1480_PHYS_MEMOWY_3			_SB_MAKE64(0x00C0000000)
#define A_BCM1480_PHYS_W2_CACHE_TEST		_SB_MAKE64(0x00D0000000)
#define A_BCM1480_PHYS_HT_SPECIAW_MATCH_BYTES	_SB_MAKE64(0x00D8000000)
#define A_BCM1480_PHYS_HT_IO_MATCH_BYTES	_SB_MAKE64(0x00DC000000)
#define A_BCM1480_PHYS_HT_CFG_MATCH_BYTES	_SB_MAKE64(0x00DE000000)
#define A_BCM1480_PHYS_HS_SUBSYS		_SB_MAKE64(0x00DF000000)
#define A_BCM1480_PHYS_HT_SPECIAW_MATCH_BITS	_SB_MAKE64(0x00F8000000)
#define A_BCM1480_PHYS_HT_IO_MATCH_BITS		_SB_MAKE64(0x00FC000000)
#define A_BCM1480_PHYS_HT_CFG_MATCH_BITS	_SB_MAKE64(0x00FE000000)
#define A_BCM1480_PHYS_MEMOWY_EXP		_SB_MAKE64(0x0100000000)
#define A_BCM1480_PHYS_MEMOWY_EXP_SIZE		_SB_MAKE64((508*1024*1024*1024))
#define A_BCM1480_PHYS_PCI_UPPEW		_SB_MAKE64(0x1000000000)
#define A_BCM1480_PHYS_HT_UPPEW_MATCH_BYTES	_SB_MAKE64(0x2000000000)
#define A_BCM1480_PHYS_HT_UPPEW_MATCH_BITS	_SB_MAKE64(0x3000000000)
#define A_BCM1480_PHYS_HT_NODE_AWIAS		_SB_MAKE64(0x4000000000)
#define A_BCM1480_PHYS_HT_FUWWACCESS		_SB_MAKE64(0xF000000000)


/*  *********************************************************************
    *  W2 Cache as WAM (Tabwe 54)
    ********************************************************************* */

#define A_BCM1480_PHYS_W2CACHE_WAY_SIZE		_SB_MAKE64(0x0000020000)
#define BCM1480_PHYS_W2CACHE_NUM_WAYS		8
#define A_BCM1480_PHYS_W2CACHE_TOTAW_SIZE	_SB_MAKE64(0x0000100000)
#define A_BCM1480_PHYS_W2CACHE_WAY0		_SB_MAKE64(0x00D0300000)
#define A_BCM1480_PHYS_W2CACHE_WAY1		_SB_MAKE64(0x00D0320000)
#define A_BCM1480_PHYS_W2CACHE_WAY2		_SB_MAKE64(0x00D0340000)
#define A_BCM1480_PHYS_W2CACHE_WAY3		_SB_MAKE64(0x00D0360000)
#define A_BCM1480_PHYS_W2CACHE_WAY4		_SB_MAKE64(0x00D0380000)
#define A_BCM1480_PHYS_W2CACHE_WAY5		_SB_MAKE64(0x00D03A0000)
#define A_BCM1480_PHYS_W2CACHE_WAY6		_SB_MAKE64(0x00D03C0000)
#define A_BCM1480_PHYS_W2CACHE_WAY7		_SB_MAKE64(0x00D03E0000)

#endif /* _BCM1480_WEGS_H */
