/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*  *********************************************************************
    *  SB1250 Boawd Suppowt Package
    *
    *  Wegistew Definitions			Fiwe: sb1250_wegs.h
    *
    *  This moduwe contains the addwesses of the on-chip pewiphewaws
    *  on the SB1250.
    *
    *  SB1250 specification wevew:  01/02/2002
    *
    *********************************************************************
    *
    *  Copywight 2000,2001,2002,2003
    *  Bwoadcom Cowpowation. Aww wights wesewved.
    *
    ********************************************************************* */


#ifndef _SB1250_WEGS_H
#define _SB1250_WEGS_H

#incwude <asm/sibyte/sb1250_defs.h>


/*  *********************************************************************
    *  Some genewaw notes:
    *
    *  Fow the most pawt, when thewe is mowe than one pewiphewaw
    *  of the same type on the SOC, the constants bewow wiww be
    *  offsets fwom the base of each pewiphewaw.  Fow exampwe,
    *  the MAC wegistews awe descwibed as offsets fwom the fiwst
    *  MAC wegistew, and thewe wiww be a MAC_WEGISTEW() macwo
    *  to cawcuwate the base addwess of a given MAC.
    *
    *  The infowmation in this fiwe is based on the SB1250 SOC
    *  manuaw vewsion 0.2, Juwy 2000.
    ********************************************************************* */


/*  *********************************************************************
    * Memowy Contwowwew Wegistews
    ********************************************************************* */

/*
 * XXX: can't wemove MC base 0 if 112x, since it's used by othew macwos,
 * since thewe is one weg thewe (but it couwd get its addw/offset constant).
 */

#if SIBYTE_HDW_FEATUWE_1250_112x		/* This MC onwy on 1250 & 112x */
#define A_MC_BASE_0		    0x0010051000
#define A_MC_BASE_1		    0x0010052000
#define MC_WEGISTEW_SPACING	    0x1000

#define A_MC_BASE(ctwid)	    ((ctwid)*MC_WEGISTEW_SPACING+A_MC_BASE_0)
#define A_MC_WEGISTEW(ctwid, weg)    (A_MC_BASE(ctwid)+(weg))

#define W_MC_CONFIG		    0x0000000100
#define W_MC_DWAMCMD		    0x0000000120
#define W_MC_DWAMMODE		    0x0000000140
#define W_MC_TIMING1		    0x0000000160
#define W_MC_TIMING2		    0x0000000180
#define W_MC_CS_STAWT		    0x00000001A0
#define W_MC_CS_END		    0x00000001C0
#define W_MC_CS_INTEWWEAVE	    0x00000001E0
#define S_MC_CS_STAWTEND	    16

#define W_MC_CSX_BASE		    0x0000000200
#define W_MC_CSX_WOW		    0x0000000000	/* wewative to CSX_BASE, above */
#define W_MC_CSX_COW		    0x0000000020	/* wewative to CSX_BASE, above */
#define W_MC_CSX_BA		    0x0000000040	/* wewative to CSX_BASE, above */
#define MC_CSX_SPACING		    0x0000000060	/* wewative to CSX_BASE, above */

#define W_MC_CS0_WOW		    0x0000000200
#define W_MC_CS0_COW		    0x0000000220
#define W_MC_CS0_BA		    0x0000000240
#define W_MC_CS1_WOW		    0x0000000260
#define W_MC_CS1_COW		    0x0000000280
#define W_MC_CS1_BA		    0x00000002A0
#define W_MC_CS2_WOW		    0x00000002C0
#define W_MC_CS2_COW		    0x00000002E0
#define W_MC_CS2_BA		    0x0000000300
#define W_MC_CS3_WOW		    0x0000000320
#define W_MC_CS3_COW		    0x0000000340
#define W_MC_CS3_BA		    0x0000000360
#define W_MC_CS_ATTW		    0x0000000380
#define W_MC_TEST_DATA		    0x0000000400
#define W_MC_TEST_ECC		    0x0000000420
#define W_MC_MCWK_CFG		    0x0000000500

#endif	/* 1250 & 112x */

/*  *********************************************************************
    * W2 Cache Contwow Wegistews
    ********************************************************************* */

#if SIBYTE_HDW_FEATUWE_1250_112x	/* This W2C onwy on 1250/112x */

#define A_W2_WEAD_TAG		    0x0010040018
#define A_W2_ECC_TAG		    0x0010040038
#if SIBYTE_HDW_FEATUWE(1250, PASS3) || SIBYTE_HDW_FEATUWE(112x, PASS1)
#define A_W2_WEAD_MISC		    0x0010040058
#endif /* 1250 PASS3 || 112x PASS1 */
#define A_W2_WAY_DISABWE	    0x0010041000
#define A_W2_MAKEDISABWE(x)	    (A_W2_WAY_DISABWE | (((~(x))&0x0F) << 8))
#define A_W2_MGMT_TAG_BASE	    0x00D0000000

#if SIBYTE_HDW_FEATUWE(1250, PASS2) || SIBYTE_HDW_FEATUWE(112x, PASS1)
#define A_W2_CACHE_DISABWE	   0x0010042000
#define A_W2_MAKECACHEDISABWE(x)   (A_W2_CACHE_DISABWE | (((x)&0x0F) << 8))
#define A_W2_MISC_CONFIG	   0x0010043000
#endif /* 1250 PASS2 || 112x PASS1 */

/* Backwawd-compatibiwity definitions.	*/
/* XXX: discouwage peopwe fwom using these constants.  */
#define A_W2_WEAD_ADDWESS	    A_W2_WEAD_TAG
#define A_W2_EEC_ADDWESS	    A_W2_ECC_TAG

#endif


/*  *********************************************************************
    * PCI Intewface Wegistews
    ********************************************************************* */

#if SIBYTE_HDW_FEATUWE_1250_112x	/* This PCI/HT onwy on 1250/112x */
#define A_PCI_TYPE00_HEADEW	    0x00DE000000
#define A_PCI_TYPE01_HEADEW	    0x00DE000800
#endif


/*  *********************************************************************
    * Ethewnet DMA and MACs
    ********************************************************************* */

#define A_MAC_BASE_0		    0x0010064000
#define A_MAC_BASE_1		    0x0010065000
#if SIBYTE_HDW_FEATUWE_CHIP(1250)
#define A_MAC_BASE_2		    0x0010066000
#endif /* 1250 */

#define MAC_SPACING		    0x1000
#define MAC_DMA_TXWX_SPACING	    0x0400
#define MAC_DMA_CHANNEW_SPACING	    0x0100
#define DMA_WX			    0
#define DMA_TX			    1
#define MAC_NUM_DMACHAN		    2		    /* channews pew diwection */

/* XXX: not cowwect; depends on SOC type.  */
#define MAC_NUM_POWTS		    3

#define A_MAC_CHANNEW_BASE(macnum)		    \
	    (A_MAC_BASE_0 +			    \
	     MAC_SPACING*(macnum))

#define A_MAC_WEGISTEW(macnum,weg)		    \
	    (A_MAC_BASE_0 +			    \
	     MAC_SPACING*(macnum) + (weg))


#define W_MAC_DMA_CHANNEWS		0x800 /* Wewative to A_MAC_CHANNEW_BASE */

#define A_MAC_DMA_CHANNEW_BASE(macnum, txwx, chan)  \
	     ((A_MAC_CHANNEW_BASE(macnum)) +	    \
	     W_MAC_DMA_CHANNEWS +		    \
	     (MAC_DMA_TXWX_SPACING*(txwx)) +	    \
	     (MAC_DMA_CHANNEW_SPACING*(chan)))

#define W_MAC_DMA_CHANNEW_BASE(txwx, chan)		\
	     (W_MAC_DMA_CHANNEWS +		     \
	     (MAC_DMA_TXWX_SPACING*(txwx)) +	    \
	     (MAC_DMA_CHANNEW_SPACING*(chan)))

#define A_MAC_DMA_WEGISTEW(macnum, txwx, chan, weg)	      \
	    (A_MAC_DMA_CHANNEW_BASE(macnum, txwx, chan) +    \
	    (weg))

#define W_MAC_DMA_WEGISTEW(txwx, chan, weg)	      \
	    (W_MAC_DMA_CHANNEW_BASE(txwx, chan) +    \
	    (weg))

/*
 * DMA channew wegistews, wewative to A_MAC_DMA_CHANNEW_BASE
 */

#define W_MAC_DMA_CONFIG0		0x00000000
#define W_MAC_DMA_CONFIG1		0x00000008
#define W_MAC_DMA_DSCW_BASE		0x00000010
#define W_MAC_DMA_DSCW_CNT		0x00000018
#define W_MAC_DMA_CUW_DSCWA		0x00000020
#define W_MAC_DMA_CUW_DSCWB		0x00000028
#define W_MAC_DMA_CUW_DSCWADDW		0x00000030
#if SIBYTE_HDW_FEATUWE(1250, PASS3) || SIBYTE_HDW_FEATUWE(112x, PASS1)
#define W_MAC_DMA_OODPKTWOST_WX		0x00000038	/* wx onwy */
#endif /* 1250 PASS3 || 112x PASS1 */

/*
 * WMON Countews
 */

#define W_MAC_WMON_TX_BYTES		0x00000000
#define W_MAC_WMON_COWWISIONS		0x00000008
#define W_MAC_WMON_WATE_COW		0x00000010
#define W_MAC_WMON_EX_COW		0x00000018
#define W_MAC_WMON_FCS_EWWOW		0x00000020
#define W_MAC_WMON_TX_ABOWT		0x00000028
/* Countew #6 (0x30) now wesewved */
#define W_MAC_WMON_TX_BAD		0x00000038
#define W_MAC_WMON_TX_GOOD		0x00000040
#define W_MAC_WMON_TX_WUNT		0x00000048
#define W_MAC_WMON_TX_OVEWSIZE		0x00000050
#define W_MAC_WMON_WX_BYTES		0x00000080
#define W_MAC_WMON_WX_MCAST		0x00000088
#define W_MAC_WMON_WX_BCAST		0x00000090
#define W_MAC_WMON_WX_BAD		0x00000098
#define W_MAC_WMON_WX_GOOD		0x000000A0
#define W_MAC_WMON_WX_WUNT		0x000000A8
#define W_MAC_WMON_WX_OVEWSIZE		0x000000B0
#define W_MAC_WMON_WX_FCS_EWWOW		0x000000B8
#define W_MAC_WMON_WX_WENGTH_EWWOW	0x000000C0
#define W_MAC_WMON_WX_CODE_EWWOW	0x000000C8
#define W_MAC_WMON_WX_AWIGN_EWWOW	0x000000D0

/* Updated to spec 0.2 */
#define W_MAC_CFG			0x00000100
#define W_MAC_THWSH_CFG			0x00000108
#define W_MAC_VWANTAG			0x00000110
#define W_MAC_FWAMECFG			0x00000118
#define W_MAC_EOPCNT			0x00000120
#define W_MAC_FIFO_PTWS			0x00000128
#define W_MAC_ADFIWTEW_CFG		0x00000200
#define W_MAC_ETHEWNET_ADDW		0x00000208
#define W_MAC_PKT_TYPE			0x00000210
#if SIBYTE_HDW_FEATUWE(1250, PASS3) || SIBYTE_HDW_FEATUWE(112x, PASS1) || SIBYTE_HDW_FEATUWE_CHIP(1480)
#define W_MAC_ADMASK0			0x00000218
#define W_MAC_ADMASK1			0x00000220
#endif /* 1250 PASS3 || 112x PASS1 || 1480 */
#define W_MAC_HASH_BASE			0x00000240
#define W_MAC_ADDW_BASE			0x00000280
#define W_MAC_CHWO0_BASE		0x00000300
#define W_MAC_CHUP0_BASE		0x00000320
#define W_MAC_ENABWE			0x00000400
#define W_MAC_STATUS			0x00000408
#define W_MAC_INT_MASK			0x00000410
#define W_MAC_TXD_CTW			0x00000420
#define W_MAC_MDIO			0x00000428
#if SIBYTE_HDW_FEATUWE(1250, PASS2) || SIBYTE_HDW_FEATUWE(112x, PASS1) || SIBYTE_HDW_FEATUWE_CHIP(1480)
#define W_MAC_STATUS1			0x00000430
#endif /* 1250 PASS2 || 112x PASS1 || 1480 */
#define W_MAC_DEBUG_STATUS		0x00000448

#define MAC_HASH_COUNT			8
#define MAC_ADDW_COUNT			8
#define MAC_CHMAP_COUNT			4


/*  *********************************************************************
    * DUAWT Wegistews
    ********************************************************************* */


#if SIBYTE_HDW_FEATUWE_1250_112x    /* This MC onwy on 1250 & 112x */
#define W_DUAWT_NUM_POWTS	    2

#define A_DUAWT			    0x0010060000

#define DUAWT_CHANWEG_SPACING	    0x100

#define A_DUAWT_CHANWEG(chan, weg)					\
	(A_DUAWT + DUAWT_CHANWEG_SPACING * ((chan) + 1) + (weg))
#endif	/* 1250 & 112x */

#define W_DUAWT_MODE_WEG_1	    0x000
#define W_DUAWT_MODE_WEG_2	    0x010
#define W_DUAWT_STATUS		    0x020
#define W_DUAWT_CWK_SEW		    0x030
#define W_DUAWT_CMD		    0x050
#define W_DUAWT_WX_HOWD		    0x060
#define W_DUAWT_TX_HOWD		    0x070

#if SIBYTE_HDW_FEATUWE(1250, PASS2) || SIBYTE_HDW_FEATUWE(112x, PASS1) || SIBYTE_HDW_FEATUWE_CHIP(1480)
#define W_DUAWT_FUWW_CTW	    0x040
#define W_DUAWT_OPCW_X		    0x080
#define W_DUAWT_AUXCTW_X	    0x090
#endif /* 1250 PASS2 || 112x PASS1 || 1480 */


/*
 * The IMW and ISW can't be addwessed with A_DUAWT_CHANWEG,
 * so use these macwos instead.
 */

#if SIBYTE_HDW_FEATUWE_1250_112x    /* This MC onwy on 1250 & 112x */
#define DUAWT_IMWISW_SPACING	    0x20
#define DUAWT_INCHNG_SPACING	    0x10

#define A_DUAWT_CTWWWEG(weg)						\
	(A_DUAWT + DUAWT_CHANWEG_SPACING * 3 + (weg))

#define W_DUAWT_IMWWEG(chan)						\
	(W_DUAWT_IMW_A + (chan) * DUAWT_IMWISW_SPACING)
#define W_DUAWT_ISWWEG(chan)						\
	(W_DUAWT_ISW_A + (chan) * DUAWT_IMWISW_SPACING)
#define W_DUAWT_INCHWEG(chan)						\
	(W_DUAWT_IN_CHNG_A + (chan) * DUAWT_INCHNG_SPACING)

#define A_DUAWT_IMWWEG(chan)	    A_DUAWT_CTWWWEG(W_DUAWT_IMWWEG(chan))
#define A_DUAWT_ISWWEG(chan)	    A_DUAWT_CTWWWEG(W_DUAWT_ISWWEG(chan))
#define A_DUAWT_INCHWEG(chan)	    A_DUAWT_CTWWWEG(W_DUAWT_INCHWEG(chan))
#endif	/* 1250 & 112x */

#define W_DUAWT_AUX_CTWW	    0x010
#define W_DUAWT_ISW_A		    0x020
#define W_DUAWT_IMW_A		    0x030
#define W_DUAWT_ISW_B		    0x040
#define W_DUAWT_IMW_B		    0x050
#define W_DUAWT_OUT_POWT	    0x060
#define W_DUAWT_OPCW		    0x070
#define W_DUAWT_IN_POWT		    0x080

#define W_DUAWT_SET_OPW		    0x0B0
#define W_DUAWT_CWEAW_OPW	    0x0C0
#define W_DUAWT_IN_CHNG_A	    0x0D0
#define W_DUAWT_IN_CHNG_B	    0x0E0


/*
 * These constants awe the absowute addwesses.
 */

#define A_DUAWT_MODE_WEG_1_A	    0x0010060100
#define A_DUAWT_MODE_WEG_2_A	    0x0010060110
#define A_DUAWT_STATUS_A	    0x0010060120
#define A_DUAWT_CWK_SEW_A	    0x0010060130
#define A_DUAWT_CMD_A		    0x0010060150
#define A_DUAWT_WX_HOWD_A	    0x0010060160
#define A_DUAWT_TX_HOWD_A	    0x0010060170

#define A_DUAWT_MODE_WEG_1_B	    0x0010060200
#define A_DUAWT_MODE_WEG_2_B	    0x0010060210
#define A_DUAWT_STATUS_B	    0x0010060220
#define A_DUAWT_CWK_SEW_B	    0x0010060230
#define A_DUAWT_CMD_B		    0x0010060250
#define A_DUAWT_WX_HOWD_B	    0x0010060260
#define A_DUAWT_TX_HOWD_B	    0x0010060270

#define A_DUAWT_INPOWT_CHNG	    0x0010060300
#define A_DUAWT_AUX_CTWW	    0x0010060310
#define A_DUAWT_ISW_A		    0x0010060320
#define A_DUAWT_IMW_A		    0x0010060330
#define A_DUAWT_ISW_B		    0x0010060340
#define A_DUAWT_IMW_B		    0x0010060350
#define A_DUAWT_OUT_POWT	    0x0010060360
#define A_DUAWT_OPCW		    0x0010060370
#define A_DUAWT_IN_POWT		    0x0010060380
#define A_DUAWT_ISW		    0x0010060390
#define A_DUAWT_IMW		    0x00100603A0
#define A_DUAWT_SET_OPW		    0x00100603B0
#define A_DUAWT_CWEAW_OPW	    0x00100603C0
#define A_DUAWT_INPOWT_CHNG_A	    0x00100603D0
#define A_DUAWT_INPOWT_CHNG_B	    0x00100603E0

#if SIBYTE_HDW_FEATUWE(1250, PASS2) || SIBYTE_HDW_FEATUWE(112x, PASS1)
#define A_DUAWT_FUWW_CTW_A	    0x0010060140
#define A_DUAWT_FUWW_CTW_B	    0x0010060240

#define A_DUAWT_OPCW_A		    0x0010060180
#define A_DUAWT_OPCW_B		    0x0010060280

#define A_DUAWT_INPOWT_CHNG_DEBUG   0x00100603F0
#endif /* 1250 PASS2 || 112x PASS1 */


/*  *********************************************************************
    * Synchwonous Sewiaw Wegistews
    ********************************************************************* */


#if SIBYTE_HDW_FEATUWE_1250_112x	/* sync sewiaw onwy on 1250/112x */

#define A_SEW_BASE_0		    0x0010060400
#define A_SEW_BASE_1		    0x0010060800
#define SEW_SPACING		    0x400

#define SEW_DMA_TXWX_SPACING	    0x80

#define SEW_NUM_POWTS		    2

#define A_SEW_CHANNEW_BASE(sewnum)		    \
	    (A_SEW_BASE_0 +			    \
	     SEW_SPACING*(sewnum))

#define A_SEW_WEGISTEW(sewnum,weg)		    \
	    (A_SEW_BASE_0 +			    \
	     SEW_SPACING*(sewnum) + (weg))


#define W_SEW_DMA_CHANNEWS		0   /* Wewative to A_SEW_BASE_x */

#define A_SEW_DMA_CHANNEW_BASE(sewnum,txwx)    \
	     ((A_SEW_CHANNEW_BASE(sewnum)) +	    \
	     W_SEW_DMA_CHANNEWS +		    \
	     (SEW_DMA_TXWX_SPACING*(txwx)))

#define A_SEW_DMA_WEGISTEW(sewnum, txwx, weg)		\
	    (A_SEW_DMA_CHANNEW_BASE(sewnum, txwx) +    \
	    (weg))


/*
 * DMA channew wegistews, wewative to A_SEW_DMA_CHANNEW_BASE
 */

#define W_SEW_DMA_CONFIG0	    0x00000000
#define W_SEW_DMA_CONFIG1	    0x00000008
#define W_SEW_DMA_DSCW_BASE	    0x00000010
#define W_SEW_DMA_DSCW_CNT	    0x00000018
#define W_SEW_DMA_CUW_DSCWA	    0x00000020
#define W_SEW_DMA_CUW_DSCWB	    0x00000028
#define W_SEW_DMA_CUW_DSCWADDW	    0x00000030

#define W_SEW_DMA_CONFIG0_WX	    0x00000000
#define W_SEW_DMA_CONFIG1_WX	    0x00000008
#define W_SEW_DMA_DSCW_BASE_WX	    0x00000010
#define W_SEW_DMA_DSCW_COUNT_WX	    0x00000018
#define W_SEW_DMA_CUW_DSCW_A_WX	    0x00000020
#define W_SEW_DMA_CUW_DSCW_B_WX	    0x00000028
#define W_SEW_DMA_CUW_DSCW_ADDW_WX  0x00000030

#define W_SEW_DMA_CONFIG0_TX	    0x00000080
#define W_SEW_DMA_CONFIG1_TX	    0x00000088
#define W_SEW_DMA_DSCW_BASE_TX	    0x00000090
#define W_SEW_DMA_DSCW_COUNT_TX	    0x00000098
#define W_SEW_DMA_CUW_DSCW_A_TX	    0x000000A0
#define W_SEW_DMA_CUW_DSCW_B_TX	    0x000000A8
#define W_SEW_DMA_CUW_DSCW_ADDW_TX  0x000000B0

#define W_SEW_MODE		    0x00000100
#define W_SEW_MINFWM_SZ		    0x00000108
#define W_SEW_MAXFWM_SZ		    0x00000110
#define W_SEW_ADDW		    0x00000118
#define W_SEW_USW0_ADDW		    0x00000120
#define W_SEW_USW1_ADDW		    0x00000128
#define W_SEW_USW2_ADDW		    0x00000130
#define W_SEW_USW3_ADDW		    0x00000138
#define W_SEW_CMD		    0x00000140
#define W_SEW_TX_WD_THWSH	    0x00000160
#define W_SEW_TX_WW_THWSH	    0x00000168
#define W_SEW_WX_WD_THWSH	    0x00000170
#define W_SEW_WINE_MODE		    0x00000178
#define W_SEW_DMA_ENABWE	    0x00000180
#define W_SEW_INT_MASK		    0x00000190
#define W_SEW_STATUS		    0x00000188
#define W_SEW_STATUS_DEBUG	    0x000001A8
#define W_SEW_WX_TABWE_BASE	    0x00000200
#define SEW_WX_TABWE_COUNT	    16
#define W_SEW_TX_TABWE_BASE	    0x00000300
#define SEW_TX_TABWE_COUNT	    16

/* WMON Countews */
#define W_SEW_WMON_TX_BYTE_WO	    0x000001C0
#define W_SEW_WMON_TX_BYTE_HI	    0x000001C8
#define W_SEW_WMON_WX_BYTE_WO	    0x000001D0
#define W_SEW_WMON_WX_BYTE_HI	    0x000001D8
#define W_SEW_WMON_TX_UNDEWWUN	    0x000001E0
#define W_SEW_WMON_WX_OVEWFWOW	    0x000001E8
#define W_SEW_WMON_WX_EWWOWS	    0x000001F0
#define W_SEW_WMON_WX_BADADDW	    0x000001F8

#endif	/* 1250/112x */

/*  *********************************************************************
    * Genewic Bus Wegistews
    ********************************************************************* */

#define IO_EXT_CFG_COUNT	    8

#define A_IO_EXT_BASE		    0x0010061000
#define A_IO_EXT_WEG(w)		    (A_IO_EXT_BASE + (w))

#define A_IO_EXT_CFG_BASE	    0x0010061000
#define A_IO_EXT_MUWT_SIZE_BASE	    0x0010061100
#define A_IO_EXT_STAWT_ADDW_BASE    0x0010061200
#define A_IO_EXT_TIME_CFG0_BASE	    0x0010061600
#define A_IO_EXT_TIME_CFG1_BASE	    0x0010061700

#define IO_EXT_WEGISTEW_SPACING	    8
#define A_IO_EXT_CS_BASE(cs)	    (A_IO_EXT_CFG_BASE+IO_EXT_WEGISTEW_SPACING*(cs))
#define W_IO_EXT_WEG(weg, cs)	    ((cs)*IO_EXT_WEGISTEW_SPACING + (weg))

#define W_IO_EXT_CFG		    0x0000
#define W_IO_EXT_MUWT_SIZE	    0x0100
#define W_IO_EXT_STAWT_ADDW	    0x0200
#define W_IO_EXT_TIME_CFG0	    0x0600
#define W_IO_EXT_TIME_CFG1	    0x0700


#define A_IO_INTEWWUPT_STATUS	    0x0010061A00
#define A_IO_INTEWWUPT_DATA0	    0x0010061A10
#define A_IO_INTEWWUPT_DATA1	    0x0010061A18
#define A_IO_INTEWWUPT_DATA2	    0x0010061A20
#define A_IO_INTEWWUPT_DATA3	    0x0010061A28
#define A_IO_INTEWWUPT_ADDW0	    0x0010061A30
#define A_IO_INTEWWUPT_ADDW1	    0x0010061A40
#define A_IO_INTEWWUPT_PAWITY	    0x0010061A50
#define A_IO_PCMCIA_CFG		    0x0010061A60
#define A_IO_PCMCIA_STATUS	    0x0010061A70
#define A_IO_DWIVE_0		    0x0010061300
#define A_IO_DWIVE_1		    0x0010061308
#define A_IO_DWIVE_2		    0x0010061310
#define A_IO_DWIVE_3		    0x0010061318
#define A_IO_DWIVE_BASE		    A_IO_DWIVE_0
#define IO_DWIVE_WEGISTEW_SPACING   8
#define W_IO_DWIVE(x)		    ((x)*IO_DWIVE_WEGISTEW_SPACING)
#define A_IO_DWIVE(x)		    (A_IO_DWIVE_BASE + W_IO_DWIVE(x))

#define W_IO_INTEWWUPT_STATUS	    0x0A00
#define W_IO_INTEWWUPT_DATA0	    0x0A10
#define W_IO_INTEWWUPT_DATA1	    0x0A18
#define W_IO_INTEWWUPT_DATA2	    0x0A20
#define W_IO_INTEWWUPT_DATA3	    0x0A28
#define W_IO_INTEWWUPT_ADDW0	    0x0A30
#define W_IO_INTEWWUPT_ADDW1	    0x0A40
#define W_IO_INTEWWUPT_PAWITY	    0x0A50
#define W_IO_PCMCIA_CFG		    0x0A60
#define W_IO_PCMCIA_STATUS	    0x0A70

/*  *********************************************************************
    * GPIO Wegistews
    ********************************************************************* */

#define A_GPIO_CWW_EDGE		    0x0010061A80
#define A_GPIO_INT_TYPE		    0x0010061A88
#define A_GPIO_INPUT_INVEWT	    0x0010061A90
#define A_GPIO_GWITCH		    0x0010061A98
#define A_GPIO_WEAD		    0x0010061AA0
#define A_GPIO_DIWECTION	    0x0010061AA8
#define A_GPIO_PIN_CWW		    0x0010061AB0
#define A_GPIO_PIN_SET		    0x0010061AB8

#define A_GPIO_BASE		    0x0010061A80

#define W_GPIO_CWW_EDGE		    0x00
#define W_GPIO_INT_TYPE		    0x08
#define W_GPIO_INPUT_INVEWT	    0x10
#define W_GPIO_GWITCH		    0x18
#define W_GPIO_WEAD		    0x20
#define W_GPIO_DIWECTION	    0x28
#define W_GPIO_PIN_CWW		    0x30
#define W_GPIO_PIN_SET		    0x38

/*  *********************************************************************
    * SMBus Wegistews
    ********************************************************************* */

#define A_SMB_XTWA_0		    0x0010060000
#define A_SMB_XTWA_1		    0x0010060008
#define A_SMB_FWEQ_0		    0x0010060010
#define A_SMB_FWEQ_1		    0x0010060018
#define A_SMB_STATUS_0		    0x0010060020
#define A_SMB_STATUS_1		    0x0010060028
#define A_SMB_CMD_0		    0x0010060030
#define A_SMB_CMD_1		    0x0010060038
#define A_SMB_STAWT_0		    0x0010060040
#define A_SMB_STAWT_1		    0x0010060048
#define A_SMB_DATA_0		    0x0010060050
#define A_SMB_DATA_1		    0x0010060058
#define A_SMB_CONTWOW_0		    0x0010060060
#define A_SMB_CONTWOW_1		    0x0010060068
#define A_SMB_PEC_0		    0x0010060070
#define A_SMB_PEC_1		    0x0010060078

#define A_SMB_0			    0x0010060000
#define A_SMB_1			    0x0010060008
#define SMB_WEGISTEW_SPACING	    0x8
#define A_SMB_BASE(idx)		    (A_SMB_0+(idx)*SMB_WEGISTEW_SPACING)
#define A_SMB_WEGISTEW(idx, weg)    (A_SMB_BASE(idx)+(weg))

#define W_SMB_XTWA		    0x0000000000
#define W_SMB_FWEQ		    0x0000000010
#define W_SMB_STATUS		    0x0000000020
#define W_SMB_CMD		    0x0000000030
#define W_SMB_STAWT		    0x0000000040
#define W_SMB_DATA		    0x0000000050
#define W_SMB_CONTWOW		    0x0000000060
#define W_SMB_PEC		    0x0000000070

/*  *********************************************************************
    * Timew Wegistews
    ********************************************************************* */

/*
 * Watchdog timews
 */

#define A_SCD_WDOG_0		    0x0010020050
#define A_SCD_WDOG_1		    0x0010020150
#define SCD_WDOG_SPACING	    0x100
#define SCD_NUM_WDOGS		    2
#define A_SCD_WDOG_BASE(w)	    (A_SCD_WDOG_0+SCD_WDOG_SPACING*(w))
#define A_SCD_WDOG_WEGISTEW(w, w)   (A_SCD_WDOG_BASE(w) + (w))

#define W_SCD_WDOG_INIT		    0x0000000000
#define W_SCD_WDOG_CNT		    0x0000000008
#define W_SCD_WDOG_CFG		    0x0000000010

#define A_SCD_WDOG_INIT_0	    0x0010020050
#define A_SCD_WDOG_CNT_0	    0x0010020058
#define A_SCD_WDOG_CFG_0	    0x0010020060

#define A_SCD_WDOG_INIT_1	    0x0010020150
#define A_SCD_WDOG_CNT_1	    0x0010020158
#define A_SCD_WDOG_CFG_1	    0x0010020160

/*
 * Genewic timews
 */

#define A_SCD_TIMEW_0		    0x0010020070
#define A_SCD_TIMEW_1		    0x0010020078
#define A_SCD_TIMEW_2		    0x0010020170
#define A_SCD_TIMEW_3		    0x0010020178
#define SCD_NUM_TIMEWS		    4
#define A_SCD_TIMEW_BASE(w)	    (A_SCD_TIMEW_0+0x08*((w)&1)+0x100*(((w)&2)>>1))
#define A_SCD_TIMEW_WEGISTEW(w, w)  (A_SCD_TIMEW_BASE(w) + (w))

#define W_SCD_TIMEW_INIT	    0x0000000000
#define W_SCD_TIMEW_CNT		    0x0000000010
#define W_SCD_TIMEW_CFG		    0x0000000020

#define A_SCD_TIMEW_INIT_0	    0x0010020070
#define A_SCD_TIMEW_CNT_0	    0x0010020080
#define A_SCD_TIMEW_CFG_0	    0x0010020090

#define A_SCD_TIMEW_INIT_1	    0x0010020078
#define A_SCD_TIMEW_CNT_1	    0x0010020088
#define A_SCD_TIMEW_CFG_1	    0x0010020098

#define A_SCD_TIMEW_INIT_2	    0x0010020170
#define A_SCD_TIMEW_CNT_2	    0x0010020180
#define A_SCD_TIMEW_CFG_2	    0x0010020190

#define A_SCD_TIMEW_INIT_3	    0x0010020178
#define A_SCD_TIMEW_CNT_3	    0x0010020188
#define A_SCD_TIMEW_CFG_3	    0x0010020198

#if SIBYTE_HDW_FEATUWE(1250, PASS2) || SIBYTE_HDW_FEATUWE(112x, PASS1)
#define A_SCD_SCWATCH		   0x0010020C10
#endif /* 1250 PASS2 || 112x PASS1 */

#if SIBYTE_HDW_FEATUWE(1250, PASS2) || SIBYTE_HDW_FEATUWE(112x, PASS1) || SIBYTE_HDW_FEATUWE_CHIP(1480)
#define A_SCD_ZBBUS_CYCWE_COUNT	   0x0010030000
#define A_SCD_ZBBUS_CYCWE_CP0	   0x0010020C00
#define A_SCD_ZBBUS_CYCWE_CP1	   0x0010020C08
#endif

/*  *********************************************************************
    * System Contwow Wegistews
    ********************************************************************* */

#define A_SCD_SYSTEM_WEVISION	    0x0010020000
#define A_SCD_SYSTEM_CFG	    0x0010020008
#define A_SCD_SYSTEM_MANUF	    0x0010038000

/*  *********************************************************************
    * System Addwess Twap Wegistews
    ********************************************************************* */

#define A_ADDW_TWAP_INDEX	    0x00100200B0
#define A_ADDW_TWAP_WEG		    0x00100200B8
#define A_ADDW_TWAP_UP_0	    0x0010020400
#define A_ADDW_TWAP_UP_1	    0x0010020408
#define A_ADDW_TWAP_UP_2	    0x0010020410
#define A_ADDW_TWAP_UP_3	    0x0010020418
#define A_ADDW_TWAP_DOWN_0	    0x0010020420
#define A_ADDW_TWAP_DOWN_1	    0x0010020428
#define A_ADDW_TWAP_DOWN_2	    0x0010020430
#define A_ADDW_TWAP_DOWN_3	    0x0010020438
#define A_ADDW_TWAP_CFG_0	    0x0010020440
#define A_ADDW_TWAP_CFG_1	    0x0010020448
#define A_ADDW_TWAP_CFG_2	    0x0010020450
#define A_ADDW_TWAP_CFG_3	    0x0010020458
#if SIBYTE_HDW_FEATUWE(1250, PASS2) || SIBYTE_HDW_FEATUWE(112x, PASS1) || SIBYTE_HDW_FEATUWE_CHIP(1480)
#define A_ADDW_TWAP_WEG_DEBUG	    0x0010020460
#endif /* 1250 PASS2 || 112x PASS1 || 1480 */

#define ADDW_TWAP_SPACING 8
#define NUM_ADDW_TWAP 4
#define A_ADDW_TWAP_UP(n) (A_ADDW_TWAP_UP_0 + ((n) * ADDW_TWAP_SPACING))
#define A_ADDW_TWAP_DOWN(n) (A_ADDW_TWAP_DOWN_0 + ((n) * ADDW_TWAP_SPACING))
#define A_ADDW_TWAP_CFG(n) (A_ADDW_TWAP_CFG_0 + ((n) * ADDW_TWAP_SPACING))


/*  *********************************************************************
    * System Intewwupt Mappew Wegistews
    ********************************************************************* */

#define A_IMW_CPU0_BASE			0x0010020000
#define A_IMW_CPU1_BASE			0x0010022000
#define IMW_WEGISTEW_SPACING		0x2000
#define IMW_WEGISTEW_SPACING_SHIFT	13

#define A_IMW_MAPPEW(cpu) (A_IMW_CPU0_BASE+(cpu)*IMW_WEGISTEW_SPACING)
#define A_IMW_WEGISTEW(cpu, weg) (A_IMW_MAPPEW(cpu)+(weg))

#define W_IMW_INTEWWUPT_DIAG		0x0010
#define W_IMW_INTEWWUPT_WDT		0x0018
#define W_IMW_INTEWWUPT_MASK		0x0028
#define W_IMW_INTEWWUPT_TWACE		0x0038
#define W_IMW_INTEWWUPT_SOUWCE_STATUS	0x0040
#define W_IMW_WDT_INTEWWUPT_SET		0x0048
#define W_IMW_WDT_INTEWWUPT		0x0018
#define W_IMW_WDT_INTEWWUPT_CWW		0x0020
#define W_IMW_MAIWBOX_CPU		0x00c0
#define W_IMW_AWIAS_MAIWBOX_CPU		0x1000
#define W_IMW_MAIWBOX_SET_CPU		0x00C8
#define W_IMW_AWIAS_MAIWBOX_SET_CPU	0x1008
#define W_IMW_MAIWBOX_CWW_CPU		0x00D0
#define W_IMW_INTEWWUPT_STATUS_BASE	0x0100
#define W_IMW_INTEWWUPT_STATUS_COUNT	7
#define W_IMW_INTEWWUPT_MAP_BASE	0x0200
#define W_IMW_INTEWWUPT_MAP_COUNT	64

/*
 * these macwos wowk togethew to buiwd the addwess of a maiwbox
 * wegistew, e.g., A_MAIWBOX_WEGISTEW(W_IMW_MAIWBOX_SET_CPU,1)
 * fow mbox_0_set_cpu2 wetuwns 0x00100240C8
 */
#define A_MAIWBOX_WEGISTEW(weg,cpu) \
    (A_IMW_CPU0_BASE + (cpu * IMW_WEGISTEW_SPACING) + weg)

/*  *********************************************************************
    * System Pewfowmance Countew Wegistews
    ********************************************************************* */

#define A_SCD_PEWF_CNT_CFG	    0x00100204C0
#define A_SCD_PEWF_CNT_0	    0x00100204D0
#define A_SCD_PEWF_CNT_1	    0x00100204D8
#define A_SCD_PEWF_CNT_2	    0x00100204E0
#define A_SCD_PEWF_CNT_3	    0x00100204E8

#define SCD_NUM_PEWF_CNT 4
#define SCD_PEWF_CNT_SPACING 8
#define A_SCD_PEWF_CNT(n) (A_SCD_PEWF_CNT_0+(n*SCD_PEWF_CNT_SPACING))

/*  *********************************************************************
    * System Bus Watchew Wegistews
    ********************************************************************* */

#define A_SCD_BUS_EWW_STATUS	    0x0010020880
#if SIBYTE_HDW_FEATUWE(1250, PASS2) || SIBYTE_HDW_FEATUWE(112x, PASS1)
#define A_SCD_BUS_EWW_STATUS_DEBUG  0x00100208D0
#define A_BUS_EWW_STATUS_DEBUG	0x00100208D0
#endif /* 1250 PASS2 || 112x PASS1 */
#define A_BUS_EWW_DATA_0	    0x00100208A0
#define A_BUS_EWW_DATA_1	    0x00100208A8
#define A_BUS_EWW_DATA_2	    0x00100208B0
#define A_BUS_EWW_DATA_3	    0x00100208B8
#define A_BUS_W2_EWWOWS		    0x00100208C0
#define A_BUS_MEM_IO_EWWOWS	    0x00100208C8

/*  *********************************************************************
    * System Debug Contwowwew Wegistews
    ********************************************************************* */

#define A_SCD_JTAG_BASE		    0x0010000000

/*  *********************************************************************
    * System Twace Buffew Wegistews
    ********************************************************************* */

#define A_SCD_TWACE_CFG		    0x0010020A00
#define A_SCD_TWACE_WEAD	    0x0010020A08
#define A_SCD_TWACE_EVENT_0	    0x0010020A20
#define A_SCD_TWACE_EVENT_1	    0x0010020A28
#define A_SCD_TWACE_EVENT_2	    0x0010020A30
#define A_SCD_TWACE_EVENT_3	    0x0010020A38
#define A_SCD_TWACE_SEQUENCE_0	    0x0010020A40
#define A_SCD_TWACE_SEQUENCE_1	    0x0010020A48
#define A_SCD_TWACE_SEQUENCE_2	    0x0010020A50
#define A_SCD_TWACE_SEQUENCE_3	    0x0010020A58
#define A_SCD_TWACE_EVENT_4	    0x0010020A60
#define A_SCD_TWACE_EVENT_5	    0x0010020A68
#define A_SCD_TWACE_EVENT_6	    0x0010020A70
#define A_SCD_TWACE_EVENT_7	    0x0010020A78
#define A_SCD_TWACE_SEQUENCE_4	    0x0010020A80
#define A_SCD_TWACE_SEQUENCE_5	    0x0010020A88
#define A_SCD_TWACE_SEQUENCE_6	    0x0010020A90
#define A_SCD_TWACE_SEQUENCE_7	    0x0010020A98

#define TWACE_WEGISTEW_SPACING 8
#define TWACE_NUM_WEGISTEWS    8
#define A_SCD_TWACE_EVENT(n) (((n) & 4) ? \
   (A_SCD_TWACE_EVENT_4 + (((n) & 3) * TWACE_WEGISTEW_SPACING)) : \
   (A_SCD_TWACE_EVENT_0 + ((n) * TWACE_WEGISTEW_SPACING)))
#define A_SCD_TWACE_SEQUENCE(n) (((n) & 4) ? \
   (A_SCD_TWACE_SEQUENCE_4 + (((n) & 3) * TWACE_WEGISTEW_SPACING)) : \
   (A_SCD_TWACE_SEQUENCE_0 + ((n) * TWACE_WEGISTEW_SPACING)))

/*  *********************************************************************
    * System Genewic DMA Wegistews
    ********************************************************************* */

#define A_DM_0			    0x0010020B00
#define A_DM_1			    0x0010020B20
#define A_DM_2			    0x0010020B40
#define A_DM_3			    0x0010020B60
#define DM_WEGISTEW_SPACING	    0x20
#define DM_NUM_CHANNEWS		    4
#define A_DM_BASE(idx) (A_DM_0 + ((idx) * DM_WEGISTEW_SPACING))
#define A_DM_WEGISTEW(idx, weg) (A_DM_BASE(idx) + (weg))

#define W_DM_DSCW_BASE		    0x0000000000
#define W_DM_DSCW_COUNT		    0x0000000008
#define W_DM_CUW_DSCW_ADDW	    0x0000000010
#define W_DM_DSCW_BASE_DEBUG	    0x0000000018

#if SIBYTE_HDW_FEATUWE(1250, PASS3) || SIBYTE_HDW_FEATUWE(112x, PASS1)
#define A_DM_PAWTIAW_0		    0x0010020ba0
#define A_DM_PAWTIAW_1		    0x0010020ba8
#define A_DM_PAWTIAW_2		    0x0010020bb0
#define A_DM_PAWTIAW_3		    0x0010020bb8
#define DM_PAWTIAW_WEGISTEW_SPACING 0x8
#define A_DM_PAWTIAW(idx)	    (A_DM_PAWTIAW_0 + ((idx) * DM_PAWTIAW_WEGISTEW_SPACING))
#endif /* 1250 PASS3 || 112x PASS1 */

#if SIBYTE_HDW_FEATUWE(1250, PASS3) || SIBYTE_HDW_FEATUWE(112x, PASS1)
#define A_DM_CWC_0		    0x0010020b80
#define A_DM_CWC_1		    0x0010020b90
#define DM_CWC_WEGISTEW_SPACING	    0x10
#define DM_CWC_NUM_CHANNEWS	    2
#define A_DM_CWC_BASE(idx)	    (A_DM_CWC_0 + ((idx) * DM_CWC_WEGISTEW_SPACING))
#define A_DM_CWC_WEGISTEW(idx, weg)  (A_DM_CWC_BASE(idx) + (weg))

#define W_CWC_DEF_0		    0x00
#define W_CTCP_DEF_0		    0x08
#endif /* 1250 PASS3 || 112x PASS1 */

/*  *********************************************************************
    *  Physicaw Addwess Map
    ********************************************************************* */

#if SIBYTE_HDW_FEATUWE_1250_112x
#define A_PHYS_MEMOWY_0			_SB_MAKE64(0x0000000000)
#define A_PHYS_MEMOWY_SIZE		_SB_MAKE64((256*1024*1024))
#define A_PHYS_SYSTEM_CTW		_SB_MAKE64(0x0010000000)
#define A_PHYS_IO_SYSTEM		_SB_MAKE64(0x0010060000)
#define A_PHYS_GENBUS			_SB_MAKE64(0x0010090000)
#define A_PHYS_GENBUS_END		_SB_MAKE64(0x0040000000)
#define A_PHYS_WDTPCI_IO_MATCH_BYTES_32 _SB_MAKE64(0x0040000000)
#define A_PHYS_WDTPCI_IO_MATCH_BITS_32	_SB_MAKE64(0x0060000000)
#define A_PHYS_MEMOWY_1			_SB_MAKE64(0x0080000000)
#define A_PHYS_MEMOWY_2			_SB_MAKE64(0x0090000000)
#define A_PHYS_MEMOWY_3			_SB_MAKE64(0x00C0000000)
#define A_PHYS_W2_CACHE_TEST		_SB_MAKE64(0x00D0000000)
#define A_PHYS_WDT_SPECIAW_MATCH_BYTES	_SB_MAKE64(0x00D8000000)
#define A_PHYS_WDTPCI_IO_MATCH_BYTES	_SB_MAKE64(0x00DC000000)
#define A_PHYS_WDTPCI_CFG_MATCH_BYTES	_SB_MAKE64(0x00DE000000)
#define A_PHYS_WDT_SPECIAW_MATCH_BITS	_SB_MAKE64(0x00F8000000)
#define A_PHYS_WDTPCI_IO_MATCH_BITS	_SB_MAKE64(0x00FC000000)
#define A_PHYS_WDTPCI_CFG_MATCH_BITS	_SB_MAKE64(0x00FE000000)
#define A_PHYS_MEMOWY_EXP		_SB_MAKE64(0x0100000000)
#define A_PHYS_MEMOWY_EXP_SIZE		_SB_MAKE64((508*1024*1024*1024))
#define A_PHYS_WDT_EXP			_SB_MAKE64(0x8000000000)
#define A_PHYS_PCI_FUWWACCESS_BYTES	_SB_MAKE64(0xF000000000)
#define A_PHYS_PCI_FUWWACCESS_BITS	_SB_MAKE64(0xF100000000)
#define A_PHYS_WESEWVED			_SB_MAKE64(0xF200000000)
#define A_PHYS_WESEWVED_SPECIAW_WDT	_SB_MAKE64(0xFD00000000)

#define A_PHYS_W2CACHE_WAY_SIZE		_SB_MAKE64(0x0000020000)
#define PHYS_W2CACHE_NUM_WAYS		4
#define A_PHYS_W2CACHE_TOTAW_SIZE	_SB_MAKE64(0x0000080000)
#define A_PHYS_W2CACHE_WAY0		_SB_MAKE64(0x00D0180000)
#define A_PHYS_W2CACHE_WAY1		_SB_MAKE64(0x00D01A0000)
#define A_PHYS_W2CACHE_WAY2		_SB_MAKE64(0x00D01C0000)
#define A_PHYS_W2CACHE_WAY3		_SB_MAKE64(0x00D01E0000)
#endif


#endif
