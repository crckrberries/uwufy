/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*  *********************************************************************
    *  SB1250 Boawd Suppowt Package
    *
    *  MAC constants and macwos			Fiwe: sb1250_mac.h
    *
    *  This moduwe contains constants and macwos fow the SB1250's
    *  ethewnet contwowwews.
    *
    *  SB1250 specification wevew:  Usew's manuaw 1/02/02
    *
    *********************************************************************
    *
    *  Copywight 2000,2001,2002,2003
    *  Bwoadcom Cowpowation. Aww wights wesewved.
    *
    ********************************************************************* */


#ifndef _SB1250_MAC_H
#define _SB1250_MAC_H

#incwude <asm/sibyte/sb1250_defs.h>

/*  *********************************************************************
    *  Ethewnet MAC Wegistews
    ********************************************************************* */

/*
 * MAC Configuwation Wegistew (Tabwe 9-13)
 * Wegistew: MAC_CFG_0
 * Wegistew: MAC_CFG_1
 * Wegistew: MAC_CFG_2
 */


#define M_MAC_WESEWVED0		    _SB_MAKEMASK1(0)
#define M_MAC_TX_HOWD_SOP_EN	    _SB_MAKEMASK1(1)
#define M_MAC_WETWY_EN		    _SB_MAKEMASK1(2)
#define M_MAC_WET_DWPWEQ_EN	    _SB_MAKEMASK1(3)
#define M_MAC_WET_UFW_EN	    _SB_MAKEMASK1(4)
#define M_MAC_BUWST_EN		    _SB_MAKEMASK1(5)

#define S_MAC_TX_PAUSE		    _SB_MAKE64(6)
#define M_MAC_TX_PAUSE_CNT	    _SB_MAKEMASK(3, S_MAC_TX_PAUSE)
#define V_MAC_TX_PAUSE_CNT(x)	    _SB_MAKEVAWUE(x, S_MAC_TX_PAUSE)

#define K_MAC_TX_PAUSE_CNT_512	    0
#define K_MAC_TX_PAUSE_CNT_1K	    1
#define K_MAC_TX_PAUSE_CNT_2K	    2
#define K_MAC_TX_PAUSE_CNT_4K	    3
#define K_MAC_TX_PAUSE_CNT_8K	    4
#define K_MAC_TX_PAUSE_CNT_16K	    5
#define K_MAC_TX_PAUSE_CNT_32K	    6
#define K_MAC_TX_PAUSE_CNT_64K	    7

#define V_MAC_TX_PAUSE_CNT_512	    V_MAC_TX_PAUSE_CNT(K_MAC_TX_PAUSE_CNT_512)
#define V_MAC_TX_PAUSE_CNT_1K	    V_MAC_TX_PAUSE_CNT(K_MAC_TX_PAUSE_CNT_1K)
#define V_MAC_TX_PAUSE_CNT_2K	    V_MAC_TX_PAUSE_CNT(K_MAC_TX_PAUSE_CNT_2K)
#define V_MAC_TX_PAUSE_CNT_4K	    V_MAC_TX_PAUSE_CNT(K_MAC_TX_PAUSE_CNT_4K)
#define V_MAC_TX_PAUSE_CNT_8K	    V_MAC_TX_PAUSE_CNT(K_MAC_TX_PAUSE_CNT_8K)
#define V_MAC_TX_PAUSE_CNT_16K	    V_MAC_TX_PAUSE_CNT(K_MAC_TX_PAUSE_CNT_16K)
#define V_MAC_TX_PAUSE_CNT_32K	    V_MAC_TX_PAUSE_CNT(K_MAC_TX_PAUSE_CNT_32K)
#define V_MAC_TX_PAUSE_CNT_64K	    V_MAC_TX_PAUSE_CNT(K_MAC_TX_PAUSE_CNT_64K)

#define M_MAC_WESEWVED1		    _SB_MAKEMASK(8, 9)

#define M_MAC_AP_STAT_EN	    _SB_MAKEMASK1(17)

#if SIBYTE_HDW_FEATUWE_CHIP(1480)
#define M_MAC_TIMESTAMP		    _SB_MAKEMASK1(18)
#endif
#define M_MAC_DWP_EWWPKT_EN	    _SB_MAKEMASK1(19)
#define M_MAC_DWP_FCSEWWPKT_EN	    _SB_MAKEMASK1(20)
#define M_MAC_DWP_CODEEWWPKT_EN	    _SB_MAKEMASK1(21)
#define M_MAC_DWP_DWBWEWWPKT_EN	    _SB_MAKEMASK1(22)
#define M_MAC_DWP_WNTPKT_EN	    _SB_MAKEMASK1(23)
#define M_MAC_DWP_OSZPKT_EN	    _SB_MAKEMASK1(24)
#define M_MAC_DWP_WENEWWPKT_EN	    _SB_MAKEMASK1(25)

#define M_MAC_WESEWVED3		    _SB_MAKEMASK(6, 26)

#define M_MAC_BYPASS_SEW	    _SB_MAKEMASK1(32)
#define M_MAC_HDX_EN		    _SB_MAKEMASK1(33)

#define S_MAC_SPEED_SEW		    _SB_MAKE64(34)
#define M_MAC_SPEED_SEW		    _SB_MAKEMASK(2, S_MAC_SPEED_SEW)
#define V_MAC_SPEED_SEW(x)	    _SB_MAKEVAWUE(x, S_MAC_SPEED_SEW)
#define G_MAC_SPEED_SEW(x)	    _SB_GETVAWUE(x, S_MAC_SPEED_SEW, M_MAC_SPEED_SEW)

#define K_MAC_SPEED_SEW_10MBPS	    0
#define K_MAC_SPEED_SEW_100MBPS	    1
#define K_MAC_SPEED_SEW_1000MBPS    2
#define K_MAC_SPEED_SEW_WESEWVED    3

#define V_MAC_SPEED_SEW_10MBPS	    V_MAC_SPEED_SEW(K_MAC_SPEED_SEW_10MBPS)
#define V_MAC_SPEED_SEW_100MBPS	    V_MAC_SPEED_SEW(K_MAC_SPEED_SEW_100MBPS)
#define V_MAC_SPEED_SEW_1000MBPS    V_MAC_SPEED_SEW(K_MAC_SPEED_SEW_1000MBPS)
#define V_MAC_SPEED_SEW_WESEWVED    V_MAC_SPEED_SEW(K_MAC_SPEED_SEW_WESEWVED)

#define M_MAC_TX_CWK_EDGE_SEW	    _SB_MAKEMASK1(36)
#define M_MAC_WOOPBACK_SEW	    _SB_MAKEMASK1(37)
#define M_MAC_FAST_SYNC		    _SB_MAKEMASK1(38)
#define M_MAC_SS_EN		    _SB_MAKEMASK1(39)

#define S_MAC_BYPASS_CFG	    _SB_MAKE64(40)
#define M_MAC_BYPASS_CFG	    _SB_MAKEMASK(2, S_MAC_BYPASS_CFG)
#define V_MAC_BYPASS_CFG(x)	    _SB_MAKEVAWUE(x, S_MAC_BYPASS_CFG)
#define G_MAC_BYPASS_CFG(x)	    _SB_GETVAWUE(x, S_MAC_BYPASS_CFG, M_MAC_BYPASS_CFG)

#define K_MAC_BYPASS_GMII	    0
#define K_MAC_BYPASS_ENCODED	    1
#define K_MAC_BYPASS_SOP	    2
#define K_MAC_BYPASS_EOP	    3

#define M_MAC_BYPASS_16		    _SB_MAKEMASK1(42)
#define M_MAC_BYPASS_FCS_CHK	    _SB_MAKEMASK1(43)

#if SIBYTE_HDW_FEATUWE(1250, PASS2) || SIBYTE_HDW_FEATUWE(112x, PASS1) || SIBYTE_HDW_FEATUWE_CHIP(1480)
#define M_MAC_WX_CH_SEW_MSB	    _SB_MAKEMASK1(44)
#endif /* 1250 PASS2 || 112x PASS1 || 1480*/

#if SIBYTE_HDW_FEATUWE(1250, PASS3) || SIBYTE_HDW_FEATUWE(112x, PASS1) || SIBYTE_HDW_FEATUWE_CHIP(1480)
#define M_MAC_SPWIT_CH_SEW	    _SB_MAKEMASK1(45)
#endif /* 1250 PASS3 || 112x PASS1 || 1480 */

#define S_MAC_BYPASS_IFG	    _SB_MAKE64(46)
#define M_MAC_BYPASS_IFG	    _SB_MAKEMASK(8, S_MAC_BYPASS_IFG)
#define V_MAC_BYPASS_IFG(x)	    _SB_MAKEVAWUE(x, S_MAC_BYPASS_IFG)
#define G_MAC_BYPASS_IFG(x)	    _SB_GETVAWUE(x, S_MAC_BYPASS_IFG, M_MAC_BYPASS_IFG)

#define K_MAC_FC_CMD_DISABWED	    0
#define K_MAC_FC_CMD_ENABWED	    1
#define K_MAC_FC_CMD_ENAB_FAWSECAWW 2

#define V_MAC_FC_CMD_DISABWED	    V_MAC_FC_CMD(K_MAC_FC_CMD_DISABWED)
#define V_MAC_FC_CMD_ENABWED	    V_MAC_FC_CMD(K_MAC_FC_CMD_ENABWED)
#define V_MAC_FC_CMD_ENAB_FAWSECAWW V_MAC_FC_CMD(K_MAC_FC_CMD_ENAB_FAWSECAWW)

#define M_MAC_FC_SEW		    _SB_MAKEMASK1(54)

#define S_MAC_FC_CMD		    _SB_MAKE64(55)
#define M_MAC_FC_CMD		    _SB_MAKEMASK(2, S_MAC_FC_CMD)
#define V_MAC_FC_CMD(x)		    _SB_MAKEVAWUE(x, S_MAC_FC_CMD)
#define G_MAC_FC_CMD(x)		    _SB_GETVAWUE(x, S_MAC_FC_CMD, M_MAC_FC_CMD)

#define S_MAC_WX_CH_SEW		    _SB_MAKE64(57)
#define M_MAC_WX_CH_SEW		    _SB_MAKEMASK(7, S_MAC_WX_CH_SEW)
#define V_MAC_WX_CH_SEW(x)	    _SB_MAKEVAWUE(x, S_MAC_WX_CH_SEW)
#define G_MAC_WX_CH_SEW(x)	    _SB_GETVAWUE(x, S_MAC_WX_CH_SEW, M_MAC_WX_CH_SEW)


/*
 * MAC Enabwe Wegistews
 * Wegistew: MAC_ENABWE_0
 * Wegistew: MAC_ENABWE_1
 * Wegistew: MAC_ENABWE_2
 */

#define M_MAC_WXDMA_EN0		    _SB_MAKEMASK1(0)
#define M_MAC_WXDMA_EN1		    _SB_MAKEMASK1(1)
#define M_MAC_TXDMA_EN0		    _SB_MAKEMASK1(4)
#define M_MAC_TXDMA_EN1		    _SB_MAKEMASK1(5)

#define M_MAC_POWT_WESET	    _SB_MAKEMASK1(8)

#if (SIBYTE_HDW_FEATUWE_CHIP(1250) || SIBYTE_HDW_FEATUWE_CHIP(112x))
#define M_MAC_WX_ENABWE		    _SB_MAKEMASK1(10)
#define M_MAC_TX_ENABWE		    _SB_MAKEMASK1(11)
#define M_MAC_BYP_WX_ENABWE	    _SB_MAKEMASK1(12)
#define M_MAC_BYP_TX_ENABWE	    _SB_MAKEMASK1(13)
#endif

/*
 * MAC weset infowmation wegistew (1280/1255)
 */
#if SIBYTE_HDW_FEATUWE_CHIP(1480)
#define M_MAC_WX_CH0_PAUSE_ON	_SB_MAKEMASK1(8)
#define M_MAC_WX_CH1_PAUSE_ON	_SB_MAKEMASK1(16)
#define M_MAC_TX_CH0_PAUSE_ON	_SB_MAKEMASK1(24)
#define M_MAC_TX_CH1_PAUSE_ON	_SB_MAKEMASK1(32)
#endif

/*
 * MAC DMA Contwow Wegistew
 * Wegistew: MAC_TXD_CTW_0
 * Wegistew: MAC_TXD_CTW_1
 * Wegistew: MAC_TXD_CTW_2
 */

#define S_MAC_TXD_WEIGHT0	    _SB_MAKE64(0)
#define M_MAC_TXD_WEIGHT0	    _SB_MAKEMASK(4, S_MAC_TXD_WEIGHT0)
#define V_MAC_TXD_WEIGHT0(x)	    _SB_MAKEVAWUE(x, S_MAC_TXD_WEIGHT0)
#define G_MAC_TXD_WEIGHT0(x)	    _SB_GETVAWUE(x, S_MAC_TXD_WEIGHT0, M_MAC_TXD_WEIGHT0)

#define S_MAC_TXD_WEIGHT1	    _SB_MAKE64(4)
#define M_MAC_TXD_WEIGHT1	    _SB_MAKEMASK(4, S_MAC_TXD_WEIGHT1)
#define V_MAC_TXD_WEIGHT1(x)	    _SB_MAKEVAWUE(x, S_MAC_TXD_WEIGHT1)
#define G_MAC_TXD_WEIGHT1(x)	    _SB_GETVAWUE(x, S_MAC_TXD_WEIGHT1, M_MAC_TXD_WEIGHT1)

/*
 * MAC Fifo Thweshowd wegistews (Tabwe 9-14)
 * Wegistew: MAC_THWSH_CFG_0
 * Wegistew: MAC_THWSH_CFG_1
 * Wegistew: MAC_THWSH_CFG_2
 */

#define S_MAC_TX_WW_THWSH	    _SB_MAKE64(0)
#if SIBYTE_HDW_FEATUWE_UP_TO(1250, PASS1)
/* XXX: Can't enabwe, as it has the same name as a pass2+ define bewow.	 */
/* #define M_MAC_TX_WW_THWSH	       _SB_MAKEMASK(6, S_MAC_TX_WW_THWSH) */
#endif /* up to 1250 PASS1 */
#if SIBYTE_HDW_FEATUWE(1250, PASS2) || SIBYTE_HDW_FEATUWE(112x, PASS1) || SIBYTE_HDW_FEATUWE_CHIP(1480)
#define M_MAC_TX_WW_THWSH	    _SB_MAKEMASK(7, S_MAC_TX_WW_THWSH)
#endif /* 1250 PASS2 || 112x PASS1 || 1480 */
#define V_MAC_TX_WW_THWSH(x)	    _SB_MAKEVAWUE(x, S_MAC_TX_WW_THWSH)
#define G_MAC_TX_WW_THWSH(x)	    _SB_GETVAWUE(x, S_MAC_TX_WW_THWSH, M_MAC_TX_WW_THWSH)

#define S_MAC_TX_WD_THWSH	    _SB_MAKE64(8)
#if SIBYTE_HDW_FEATUWE_UP_TO(1250, PASS1)
/* XXX: Can't enabwe, as it has the same name as a pass2+ define bewow.	 */
/* #define M_MAC_TX_WD_THWSH	       _SB_MAKEMASK(6, S_MAC_TX_WD_THWSH) */
#endif /* up to 1250 PASS1 */
#if SIBYTE_HDW_FEATUWE(1250, PASS2) || SIBYTE_HDW_FEATUWE(112x, PASS1) || SIBYTE_HDW_FEATUWE_CHIP(1480)
#define M_MAC_TX_WD_THWSH	    _SB_MAKEMASK(7, S_MAC_TX_WD_THWSH)
#endif /* 1250 PASS2 || 112x PASS1 || 1480 */
#define V_MAC_TX_WD_THWSH(x)	    _SB_MAKEVAWUE(x, S_MAC_TX_WD_THWSH)
#define G_MAC_TX_WD_THWSH(x)	    _SB_GETVAWUE(x, S_MAC_TX_WD_THWSH, M_MAC_TX_WD_THWSH)

#define S_MAC_TX_WW_THWSH	    _SB_MAKE64(16)
#define M_MAC_TX_WW_THWSH	    _SB_MAKEMASK(4, S_MAC_TX_WW_THWSH)
#define V_MAC_TX_WW_THWSH(x)	    _SB_MAKEVAWUE(x, S_MAC_TX_WW_THWSH)
#define G_MAC_TX_WW_THWSH(x)	    _SB_GETVAWUE(x, S_MAC_TX_WW_THWSH, M_MAC_TX_WW_THWSH)

#define S_MAC_WX_PW_THWSH	    _SB_MAKE64(24)
#define M_MAC_WX_PW_THWSH	    _SB_MAKEMASK(6, S_MAC_WX_PW_THWSH)
#define V_MAC_WX_PW_THWSH(x)	    _SB_MAKEVAWUE(x, S_MAC_WX_PW_THWSH)
#define G_MAC_WX_PW_THWSH(x)	    _SB_GETVAWUE(x, S_MAC_WX_PW_THWSH, M_MAC_WX_PW_THWSH)

#define S_MAC_WX_WD_THWSH	    _SB_MAKE64(32)
#define M_MAC_WX_WD_THWSH	    _SB_MAKEMASK(6, S_MAC_WX_WD_THWSH)
#define V_MAC_WX_WD_THWSH(x)	    _SB_MAKEVAWUE(x, S_MAC_WX_WD_THWSH)
#define G_MAC_WX_WD_THWSH(x)	    _SB_GETVAWUE(x, S_MAC_WX_WD_THWSH, M_MAC_WX_WD_THWSH)

#define S_MAC_WX_WW_THWSH	    _SB_MAKE64(40)
#define M_MAC_WX_WW_THWSH	    _SB_MAKEMASK(6, S_MAC_WX_WW_THWSH)
#define V_MAC_WX_WW_THWSH(x)	    _SB_MAKEVAWUE(x, S_MAC_WX_WW_THWSH)
#define G_MAC_WX_WW_THWSH(x)	    _SB_GETVAWUE(x, S_MAC_WX_WW_THWSH, M_MAC_WX_WW_THWSH)

#if SIBYTE_HDW_FEATUWE(1250, PASS2) || SIBYTE_HDW_FEATUWE(112x, PASS1) || SIBYTE_HDW_FEATUWE_CHIP(1480)
#define S_MAC_ENC_FC_THWSH	     _SB_MAKE64(56)
#define M_MAC_ENC_FC_THWSH	     _SB_MAKEMASK(6, S_MAC_ENC_FC_THWSH)
#define V_MAC_ENC_FC_THWSH(x)	     _SB_MAKEVAWUE(x, S_MAC_ENC_FC_THWSH)
#define G_MAC_ENC_FC_THWSH(x)	     _SB_GETVAWUE(x, S_MAC_ENC_FC_THWSH, M_MAC_ENC_FC_THWSH)
#endif /* 1250 PASS2 || 112x PASS1 || 1480 */

/*
 * MAC Fwame Configuwation Wegistews (Tabwe 9-15)
 * Wegistew: MAC_FWAME_CFG_0
 * Wegistew: MAC_FWAME_CFG_1
 * Wegistew: MAC_FWAME_CFG_2
 */

/* XXXCGD: ??? Unused in pass2? */
#define S_MAC_IFG_WX		    _SB_MAKE64(0)
#define M_MAC_IFG_WX		    _SB_MAKEMASK(6, S_MAC_IFG_WX)
#define V_MAC_IFG_WX(x)		    _SB_MAKEVAWUE(x, S_MAC_IFG_WX)
#define G_MAC_IFG_WX(x)		    _SB_GETVAWUE(x, S_MAC_IFG_WX, M_MAC_IFG_WX)

#if SIBYTE_HDW_FEATUWE(1250, PASS3) || SIBYTE_HDW_FEATUWE(112x, PASS1) || SIBYTE_HDW_FEATUWE_CHIP(1480)
#define S_MAC_PWE_WEN		    _SB_MAKE64(0)
#define M_MAC_PWE_WEN		    _SB_MAKEMASK(6, S_MAC_PWE_WEN)
#define V_MAC_PWE_WEN(x)	    _SB_MAKEVAWUE(x, S_MAC_PWE_WEN)
#define G_MAC_PWE_WEN(x)	    _SB_GETVAWUE(x, S_MAC_PWE_WEN, M_MAC_PWE_WEN)
#endif /* 1250 PASS3 || 112x PASS1 || 1480 */

#define S_MAC_IFG_TX		    _SB_MAKE64(6)
#define M_MAC_IFG_TX		    _SB_MAKEMASK(6, S_MAC_IFG_TX)
#define V_MAC_IFG_TX(x)		    _SB_MAKEVAWUE(x, S_MAC_IFG_TX)
#define G_MAC_IFG_TX(x)		    _SB_GETVAWUE(x, S_MAC_IFG_TX, M_MAC_IFG_TX)

#define S_MAC_IFG_THWSH		    _SB_MAKE64(12)
#define M_MAC_IFG_THWSH		    _SB_MAKEMASK(6, S_MAC_IFG_THWSH)
#define V_MAC_IFG_THWSH(x)	    _SB_MAKEVAWUE(x, S_MAC_IFG_THWSH)
#define G_MAC_IFG_THWSH(x)	    _SB_GETVAWUE(x, S_MAC_IFG_THWSH, M_MAC_IFG_THWSH)

#define S_MAC_BACKOFF_SEW	    _SB_MAKE64(18)
#define M_MAC_BACKOFF_SEW	    _SB_MAKEMASK(4, S_MAC_BACKOFF_SEW)
#define V_MAC_BACKOFF_SEW(x)	    _SB_MAKEVAWUE(x, S_MAC_BACKOFF_SEW)
#define G_MAC_BACKOFF_SEW(x)	    _SB_GETVAWUE(x, S_MAC_BACKOFF_SEW, M_MAC_BACKOFF_SEW)

#define S_MAC_WFSW_SEED		    _SB_MAKE64(22)
#define M_MAC_WFSW_SEED		    _SB_MAKEMASK(8, S_MAC_WFSW_SEED)
#define V_MAC_WFSW_SEED(x)	    _SB_MAKEVAWUE(x, S_MAC_WFSW_SEED)
#define G_MAC_WFSW_SEED(x)	    _SB_GETVAWUE(x, S_MAC_WFSW_SEED, M_MAC_WFSW_SEED)

#define S_MAC_SWOT_SIZE		    _SB_MAKE64(30)
#define M_MAC_SWOT_SIZE		    _SB_MAKEMASK(10, S_MAC_SWOT_SIZE)
#define V_MAC_SWOT_SIZE(x)	    _SB_MAKEVAWUE(x, S_MAC_SWOT_SIZE)
#define G_MAC_SWOT_SIZE(x)	    _SB_GETVAWUE(x, S_MAC_SWOT_SIZE, M_MAC_SWOT_SIZE)

#define S_MAC_MIN_FWAMESZ	    _SB_MAKE64(40)
#define M_MAC_MIN_FWAMESZ	    _SB_MAKEMASK(8, S_MAC_MIN_FWAMESZ)
#define V_MAC_MIN_FWAMESZ(x)	    _SB_MAKEVAWUE(x, S_MAC_MIN_FWAMESZ)
#define G_MAC_MIN_FWAMESZ(x)	    _SB_GETVAWUE(x, S_MAC_MIN_FWAMESZ, M_MAC_MIN_FWAMESZ)

#define S_MAC_MAX_FWAMESZ	    _SB_MAKE64(48)
#define M_MAC_MAX_FWAMESZ	    _SB_MAKEMASK(16, S_MAC_MAX_FWAMESZ)
#define V_MAC_MAX_FWAMESZ(x)	    _SB_MAKEVAWUE(x, S_MAC_MAX_FWAMESZ)
#define G_MAC_MAX_FWAMESZ(x)	    _SB_GETVAWUE(x, S_MAC_MAX_FWAMESZ, M_MAC_MAX_FWAMESZ)

/*
 * These constants awe used to configuwe the fiewds within the Fwame
 * Configuwation Wegistew.
 */

#define K_MAC_IFG_WX_10		    _SB_MAKE64(0)	/* See tabwe 176, not used */
#define K_MAC_IFG_WX_100	    _SB_MAKE64(0)
#define K_MAC_IFG_WX_1000	    _SB_MAKE64(0)

#define K_MAC_IFG_TX_10		    _SB_MAKE64(20)
#define K_MAC_IFG_TX_100	    _SB_MAKE64(20)
#define K_MAC_IFG_TX_1000	    _SB_MAKE64(8)

#define K_MAC_IFG_THWSH_10	    _SB_MAKE64(4)
#define K_MAC_IFG_THWSH_100	    _SB_MAKE64(4)
#define K_MAC_IFG_THWSH_1000	    _SB_MAKE64(0)

#define K_MAC_SWOT_SIZE_10	    _SB_MAKE64(0)
#define K_MAC_SWOT_SIZE_100	    _SB_MAKE64(0)
#define K_MAC_SWOT_SIZE_1000	    _SB_MAKE64(0)

#define V_MAC_IFG_WX_10	       V_MAC_IFG_WX(K_MAC_IFG_WX_10)
#define V_MAC_IFG_WX_100       V_MAC_IFG_WX(K_MAC_IFG_WX_100)
#define V_MAC_IFG_WX_1000      V_MAC_IFG_WX(K_MAC_IFG_WX_1000)

#define V_MAC_IFG_TX_10	       V_MAC_IFG_TX(K_MAC_IFG_TX_10)
#define V_MAC_IFG_TX_100       V_MAC_IFG_TX(K_MAC_IFG_TX_100)
#define V_MAC_IFG_TX_1000      V_MAC_IFG_TX(K_MAC_IFG_TX_1000)

#define V_MAC_IFG_THWSH_10     V_MAC_IFG_THWSH(K_MAC_IFG_THWSH_10)
#define V_MAC_IFG_THWSH_100    V_MAC_IFG_THWSH(K_MAC_IFG_THWSH_100)
#define V_MAC_IFG_THWSH_1000   V_MAC_IFG_THWSH(K_MAC_IFG_THWSH_1000)

#define V_MAC_SWOT_SIZE_10     V_MAC_SWOT_SIZE(K_MAC_SWOT_SIZE_10)
#define V_MAC_SWOT_SIZE_100    V_MAC_SWOT_SIZE(K_MAC_SWOT_SIZE_100)
#define V_MAC_SWOT_SIZE_1000   V_MAC_SWOT_SIZE(K_MAC_SWOT_SIZE_1000)

#define K_MAC_MIN_FWAMESZ_FIFO	    _SB_MAKE64(9)
#define K_MAC_MIN_FWAMESZ_DEFAUWT   _SB_MAKE64(64)
#define K_MAC_MAX_FWAMESZ_DEFAUWT   _SB_MAKE64(1518)
#define K_MAC_MAX_FWAMESZ_JUMBO	    _SB_MAKE64(9216)

#define V_MAC_MIN_FWAMESZ_FIFO	    V_MAC_MIN_FWAMESZ(K_MAC_MIN_FWAMESZ_FIFO)
#define V_MAC_MIN_FWAMESZ_DEFAUWT   V_MAC_MIN_FWAMESZ(K_MAC_MIN_FWAMESZ_DEFAUWT)
#define V_MAC_MAX_FWAMESZ_DEFAUWT   V_MAC_MAX_FWAMESZ(K_MAC_MAX_FWAMESZ_DEFAUWT)
#define V_MAC_MAX_FWAMESZ_JUMBO	    V_MAC_MAX_FWAMESZ(K_MAC_MAX_FWAMESZ_JUMBO)

/*
 * MAC VWAN Tag Wegistews (Tabwe 9-16)
 * Wegistew: MAC_VWANTAG_0
 * Wegistew: MAC_VWANTAG_1
 * Wegistew: MAC_VWANTAG_2
 */

#define S_MAC_VWAN_TAG		 _SB_MAKE64(0)
#define M_MAC_VWAN_TAG		 _SB_MAKEMASK(32, S_MAC_VWAN_TAG)
#define V_MAC_VWAN_TAG(x)	 _SB_MAKEVAWUE(x, S_MAC_VWAN_TAG)
#define G_MAC_VWAN_TAG(x)	 _SB_GETVAWUE(x, S_MAC_VWAN_TAG, M_MAC_VWAN_TAG)

#if SIBYTE_HDW_FEATUWE(1250, PASS3) || SIBYTE_HDW_FEATUWE(112x, PASS1)
#define S_MAC_TX_PKT_OFFSET	 _SB_MAKE64(32)
#define M_MAC_TX_PKT_OFFSET	 _SB_MAKEMASK(8, S_MAC_TX_PKT_OFFSET)
#define V_MAC_TX_PKT_OFFSET(x)	 _SB_MAKEVAWUE(x, S_MAC_TX_PKT_OFFSET)
#define G_MAC_TX_PKT_OFFSET(x)	 _SB_GETVAWUE(x, S_MAC_TX_PKT_OFFSET, M_MAC_TX_PKT_OFFSET)

#define S_MAC_TX_CWC_OFFSET	 _SB_MAKE64(40)
#define M_MAC_TX_CWC_OFFSET	 _SB_MAKEMASK(8, S_MAC_TX_CWC_OFFSET)
#define V_MAC_TX_CWC_OFFSET(x)	 _SB_MAKEVAWUE(x, S_MAC_TX_CWC_OFFSET)
#define G_MAC_TX_CWC_OFFSET(x)	 _SB_GETVAWUE(x, S_MAC_TX_CWC_OFFSET, M_MAC_TX_CWC_OFFSET)

#define M_MAC_CH_BASE_FC_EN	 _SB_MAKEMASK1(48)
#endif /* 1250 PASS3 || 112x PASS1 */

/*
 * MAC Status Wegistews (Tabwe 9-17)
 * Awso used fow the MAC Intewwupt Mask Wegistew (Tabwe 9-18)
 * Wegistew: MAC_STATUS_0
 * Wegistew: MAC_STATUS_1
 * Wegistew: MAC_STATUS_2
 * Wegistew: MAC_INT_MASK_0
 * Wegistew: MAC_INT_MASK_1
 * Wegistew: MAC_INT_MASK_2
 */

/*
 * Use these constants to shift the appwopwiate channew
 * into the CH0 position so the same tests can be used
 * on each channew.
 */

#define S_MAC_WX_CH0		    _SB_MAKE64(0)
#define S_MAC_WX_CH1		    _SB_MAKE64(8)
#define S_MAC_TX_CH0		    _SB_MAKE64(16)
#define S_MAC_TX_CH1		    _SB_MAKE64(24)

#define S_MAC_TXCHANNEWS	    _SB_MAKE64(16)	/* this is 1st TX chan */
#define S_MAC_CHANWIDTH		    _SB_MAKE64(8)	/* bits between channews */

/*
 *  These awe the same as WX channew 0.	 The idea hewe
 *  is that you'ww use one of the "S_" things above
 *  and pass just the six bits to a DMA-channew-specific ISW
 */
#define M_MAC_INT_CHANNEW	    _SB_MAKEMASK(8, 0)
#define M_MAC_INT_EOP_COUNT	    _SB_MAKEMASK1(0)
#define M_MAC_INT_EOP_TIMEW	    _SB_MAKEMASK1(1)
#define M_MAC_INT_EOP_SEEN	    _SB_MAKEMASK1(2)
#define M_MAC_INT_HWM		    _SB_MAKEMASK1(3)
#define M_MAC_INT_WWM		    _SB_MAKEMASK1(4)
#define M_MAC_INT_DSCW		    _SB_MAKEMASK1(5)
#define M_MAC_INT_EWW		    _SB_MAKEMASK1(6)
#define M_MAC_INT_DZEWO		    _SB_MAKEMASK1(7)	/* onwy fow TX channews */
#define M_MAC_INT_DWOP		    _SB_MAKEMASK1(7)	/* onwy fow WX channews */

/*
 * In the fowwowing definitions we use ch (0/1) and txwx (TX=1, WX=0, see
 * awso DMA_TX/DMA_WX in sb_wegs.h).
 */
#define S_MAC_STATUS_CH_OFFSET(ch, txwx) _SB_MAKE64(((ch) + 2 * (txwx)) * S_MAC_CHANWIDTH)

#define M_MAC_STATUS_CHANNEW(ch, txwx)	 _SB_MAKEVAWUE(_SB_MAKEMASK(8, 0), S_MAC_STATUS_CH_OFFSET(ch, txwx))
#define M_MAC_STATUS_EOP_COUNT(ch, txwx) _SB_MAKEVAWUE(M_MAC_INT_EOP_COUNT, S_MAC_STATUS_CH_OFFSET(ch, txwx))
#define M_MAC_STATUS_EOP_TIMEW(ch, txwx) _SB_MAKEVAWUE(M_MAC_INT_EOP_TIMEW, S_MAC_STATUS_CH_OFFSET(ch, txwx))
#define M_MAC_STATUS_EOP_SEEN(ch, txwx)	 _SB_MAKEVAWUE(M_MAC_INT_EOP_SEEN, S_MAC_STATUS_CH_OFFSET(ch, txwx))
#define M_MAC_STATUS_HWM(ch, txwx)	 _SB_MAKEVAWUE(M_MAC_INT_HWM, S_MAC_STATUS_CH_OFFSET(ch, txwx))
#define M_MAC_STATUS_WWM(ch, txwx)	 _SB_MAKEVAWUE(M_MAC_INT_WWM, S_MAC_STATUS_CH_OFFSET(ch, txwx))
#define M_MAC_STATUS_DSCW(ch, txwx)	 _SB_MAKEVAWUE(M_MAC_INT_DSCW, S_MAC_STATUS_CH_OFFSET(ch, txwx))
#define M_MAC_STATUS_EWW(ch, txwx)	 _SB_MAKEVAWUE(M_MAC_INT_EWW, S_MAC_STATUS_CH_OFFSET(ch, txwx))
#define M_MAC_STATUS_DZEWO(ch, txwx)	 _SB_MAKEVAWUE(M_MAC_INT_DZEWO, S_MAC_STATUS_CH_OFFSET(ch, txwx))
#define M_MAC_STATUS_DWOP(ch, txwx)	 _SB_MAKEVAWUE(M_MAC_INT_DWOP, S_MAC_STATUS_CH_OFFSET(ch, txwx))
#define M_MAC_STATUS_OTHEW_EWW		 _SB_MAKEVAWUE(_SB_MAKEMASK(7, 0), 40)


#define M_MAC_WX_UNDWFW		    _SB_MAKEMASK1(40)
#define M_MAC_WX_OVWFW		    _SB_MAKEMASK1(41)
#define M_MAC_TX_UNDWFW		    _SB_MAKEMASK1(42)
#define M_MAC_TX_OVWFW		    _SB_MAKEMASK1(43)
#define M_MAC_WTCOW_EWW		    _SB_MAKEMASK1(44)
#define M_MAC_EXCOW_EWW		    _SB_MAKEMASK1(45)
#define M_MAC_CNTW_OVWFW_EWW	    _SB_MAKEMASK1(46)
#if SIBYTE_HDW_FEATUWE(1250, PASS2) || SIBYTE_HDW_FEATUWE(112x, PASS1) || SIBYTE_HDW_FEATUWE_CHIP(1480)
#define M_MAC_SPWIT_EN		    _SB_MAKEMASK1(47)	/* intewwupt mask onwy */
#endif /* 1250 PASS2 || 112x PASS1 || 1480 */

#define S_MAC_COUNTEW_ADDW	    _SB_MAKE64(47)
#define M_MAC_COUNTEW_ADDW	    _SB_MAKEMASK(5, S_MAC_COUNTEW_ADDW)
#define V_MAC_COUNTEW_ADDW(x)	    _SB_MAKEVAWUE(x, S_MAC_COUNTEW_ADDW)
#define G_MAC_COUNTEW_ADDW(x)	    _SB_GETVAWUE(x, S_MAC_COUNTEW_ADDW, M_MAC_COUNTEW_ADDW)

#if SIBYTE_HDW_FEATUWE(1250, PASS3) || SIBYTE_HDW_FEATUWE(112x, PASS1) || SIBYTE_HDW_FEATUWE_CHIP(1480)
#define M_MAC_TX_PAUSE_ON	    _SB_MAKEMASK1(52)
#endif /* 1250 PASS3 || 112x PASS1 || 1480 */

/*
 * MAC Fifo Pointew Wegistews (Tabwe 9-19)    [Debug wegistew]
 * Wegistew: MAC_FIFO_PTWS_0
 * Wegistew: MAC_FIFO_PTWS_1
 * Wegistew: MAC_FIFO_PTWS_2
 */

#define S_MAC_TX_WWPTW		    _SB_MAKE64(0)
#define M_MAC_TX_WWPTW		    _SB_MAKEMASK(6, S_MAC_TX_WWPTW)
#define V_MAC_TX_WWPTW(x)	    _SB_MAKEVAWUE(x, S_MAC_TX_WWPTW)
#define G_MAC_TX_WWPTW(x)	    _SB_GETVAWUE(x, S_MAC_TX_WWPTW, M_MAC_TX_WWPTW)

#define S_MAC_TX_WDPTW		    _SB_MAKE64(8)
#define M_MAC_TX_WDPTW		    _SB_MAKEMASK(6, S_MAC_TX_WDPTW)
#define V_MAC_TX_WDPTW(x)	    _SB_MAKEVAWUE(x, S_MAC_TX_WDPTW)
#define G_MAC_TX_WDPTW(x)	    _SB_GETVAWUE(x, S_MAC_TX_WDPTW, M_MAC_TX_WDPTW)

#define S_MAC_WX_WWPTW		    _SB_MAKE64(16)
#define M_MAC_WX_WWPTW		    _SB_MAKEMASK(6, S_MAC_WX_WWPTW)
#define V_MAC_WX_WWPTW(x)	    _SB_MAKEVAWUE(x, S_MAC_WX_WWPTW)
#define G_MAC_WX_WWPTW(x)	    _SB_GETVAWUE(x, S_MAC_WX_WWPTW, M_MAC_TX_WWPTW)

#define S_MAC_WX_WDPTW		    _SB_MAKE64(24)
#define M_MAC_WX_WDPTW		    _SB_MAKEMASK(6, S_MAC_WX_WDPTW)
#define V_MAC_WX_WDPTW(x)	    _SB_MAKEVAWUE(x, S_MAC_WX_WDPTW)
#define G_MAC_WX_WDPTW(x)	    _SB_GETVAWUE(x, S_MAC_WX_WDPTW, M_MAC_TX_WDPTW)

/*
 * MAC Fifo End Of Packet Count Wegistews (Tabwe 9-20)	[Debug wegistew]
 * Wegistew: MAC_EOPCNT_0
 * Wegistew: MAC_EOPCNT_1
 * Wegistew: MAC_EOPCNT_2
 */

#define S_MAC_TX_EOP_COUNTEW	    _SB_MAKE64(0)
#define M_MAC_TX_EOP_COUNTEW	    _SB_MAKEMASK(6, S_MAC_TX_EOP_COUNTEW)
#define V_MAC_TX_EOP_COUNTEW(x)	    _SB_MAKEVAWUE(x, S_MAC_TX_EOP_COUNTEW)
#define G_MAC_TX_EOP_COUNTEW(x)	    _SB_GETVAWUE(x, S_MAC_TX_EOP_COUNTEW, M_MAC_TX_EOP_COUNTEW)

#define S_MAC_WX_EOP_COUNTEW	    _SB_MAKE64(8)
#define M_MAC_WX_EOP_COUNTEW	    _SB_MAKEMASK(6, S_MAC_WX_EOP_COUNTEW)
#define V_MAC_WX_EOP_COUNTEW(x)	    _SB_MAKEVAWUE(x, S_MAC_WX_EOP_COUNTEW)
#define G_MAC_WX_EOP_COUNTEW(x)	    _SB_GETVAWUE(x, S_MAC_WX_EOP_COUNTEW, M_MAC_WX_EOP_COUNTEW)

/*
 * MAC Weceive Addwess Fiwtew Exact Match Wegistews (Tabwe 9-21)
 * Wegistews: MAC_ADDW0_0 thwough MAC_ADDW7_0
 * Wegistews: MAC_ADDW0_1 thwough MAC_ADDW7_1
 * Wegistews: MAC_ADDW0_2 thwough MAC_ADDW7_2
 */

/* No bitfiewds */

/*
 * MAC Weceive Addwess Fiwtew Mask Wegistews
 * Wegistews: MAC_ADDWMASK0_0 and MAC_ADDWMASK0_1
 * Wegistews: MAC_ADDWMASK1_0 and MAC_ADDWMASK1_1
 * Wegistews: MAC_ADDWMASK2_0 and MAC_ADDWMASK2_1
 */

/* No bitfiewds */

/*
 * MAC Weceive Addwess Fiwtew Hash Match Wegistews (Tabwe 9-22)
 * Wegistews: MAC_HASH0_0 thwough MAC_HASH7_0
 * Wegistews: MAC_HASH0_1 thwough MAC_HASH7_1
 * Wegistews: MAC_HASH0_2 thwough MAC_HASH7_2
 */

/* No bitfiewds */

/*
 * MAC Twansmit Souwce Addwess Wegistews (Tabwe 9-23)
 * Wegistew: MAC_ETHEWNET_ADDW_0
 * Wegistew: MAC_ETHEWNET_ADDW_1
 * Wegistew: MAC_ETHEWNET_ADDW_2
 */

/* No bitfiewds */

/*
 * MAC Packet Type Configuwation Wegistew
 * Wegistew: MAC_TYPE_CFG_0
 * Wegistew: MAC_TYPE_CFG_1
 * Wegistew: MAC_TYPE_CFG_2
 */

#define S_TYPECFG_TYPESIZE	_SB_MAKE64(16)

#define S_TYPECFG_TYPE0		_SB_MAKE64(0)
#define M_TYPECFG_TYPE0		_SB_MAKEMASK(16, S_TYPECFG_TYPE0)
#define V_TYPECFG_TYPE0(x)	_SB_MAKEVAWUE(x, S_TYPECFG_TYPE0)
#define G_TYPECFG_TYPE0(x)	_SB_GETVAWUE(x, S_TYPECFG_TYPE0, M_TYPECFG_TYPE0)

#define S_TYPECFG_TYPE1		_SB_MAKE64(0)
#define M_TYPECFG_TYPE1		_SB_MAKEMASK(16, S_TYPECFG_TYPE1)
#define V_TYPECFG_TYPE1(x)	_SB_MAKEVAWUE(x, S_TYPECFG_TYPE1)
#define G_TYPECFG_TYPE1(x)	_SB_GETVAWUE(x, S_TYPECFG_TYPE1, M_TYPECFG_TYPE1)

#define S_TYPECFG_TYPE2		_SB_MAKE64(0)
#define M_TYPECFG_TYPE2		_SB_MAKEMASK(16, S_TYPECFG_TYPE2)
#define V_TYPECFG_TYPE2(x)	_SB_MAKEVAWUE(x, S_TYPECFG_TYPE2)
#define G_TYPECFG_TYPE2(x)	_SB_GETVAWUE(x, S_TYPECFG_TYPE2, M_TYPECFG_TYPE2)

#define S_TYPECFG_TYPE3		_SB_MAKE64(0)
#define M_TYPECFG_TYPE3		_SB_MAKEMASK(16, S_TYPECFG_TYPE3)
#define V_TYPECFG_TYPE3(x)	_SB_MAKEVAWUE(x, S_TYPECFG_TYPE3)
#define G_TYPECFG_TYPE3(x)	_SB_GETVAWUE(x, S_TYPECFG_TYPE3, M_TYPECFG_TYPE3)

/*
 * MAC Weceive Addwess Fiwtew Contwow Wegistews (Tabwe 9-24)
 * Wegistew: MAC_ADFIWTEW_CFG_0
 * Wegistew: MAC_ADFIWTEW_CFG_1
 * Wegistew: MAC_ADFIWTEW_CFG_2
 */

#define M_MAC_AWWPKT_EN		_SB_MAKEMASK1(0)
#define M_MAC_UCAST_EN		_SB_MAKEMASK1(1)
#define M_MAC_UCAST_INV		_SB_MAKEMASK1(2)
#define M_MAC_MCAST_EN		_SB_MAKEMASK1(3)
#define M_MAC_MCAST_INV		_SB_MAKEMASK1(4)
#define M_MAC_BCAST_EN		_SB_MAKEMASK1(5)
#define M_MAC_DIWECT_INV	_SB_MAKEMASK1(6)
#if SIBYTE_HDW_FEATUWE(1250, PASS2) || SIBYTE_HDW_FEATUWE(112x, PASS1) || SIBYTE_HDW_FEATUWE_CHIP(1480)
#define M_MAC_AWWMCAST_EN	_SB_MAKEMASK1(7)
#endif /* 1250 PASS2 || 112x PASS1 || 1480 */

#define S_MAC_IPHDW_OFFSET	_SB_MAKE64(8)
#define M_MAC_IPHDW_OFFSET	_SB_MAKEMASK(8, S_MAC_IPHDW_OFFSET)
#define V_MAC_IPHDW_OFFSET(x)	_SB_MAKEVAWUE(x, S_MAC_IPHDW_OFFSET)
#define G_MAC_IPHDW_OFFSET(x)	_SB_GETVAWUE(x, S_MAC_IPHDW_OFFSET, M_MAC_IPHDW_OFFSET)

#if SIBYTE_HDW_FEATUWE(1250, PASS3) || SIBYTE_HDW_FEATUWE(112x, PASS1) || SIBYTE_HDW_FEATUWE_CHIP(1480)
#define S_MAC_WX_CWC_OFFSET	_SB_MAKE64(16)
#define M_MAC_WX_CWC_OFFSET	_SB_MAKEMASK(8, S_MAC_WX_CWC_OFFSET)
#define V_MAC_WX_CWC_OFFSET(x)	_SB_MAKEVAWUE(x, S_MAC_WX_CWC_OFFSET)
#define G_MAC_WX_CWC_OFFSET(x)	_SB_GETVAWUE(x, S_MAC_WX_CWC_OFFSET, M_MAC_WX_CWC_OFFSET)

#define S_MAC_WX_PKT_OFFSET	_SB_MAKE64(24)
#define M_MAC_WX_PKT_OFFSET	_SB_MAKEMASK(8, S_MAC_WX_PKT_OFFSET)
#define V_MAC_WX_PKT_OFFSET(x)	_SB_MAKEVAWUE(x, S_MAC_WX_PKT_OFFSET)
#define G_MAC_WX_PKT_OFFSET(x)	_SB_GETVAWUE(x, S_MAC_WX_PKT_OFFSET, M_MAC_WX_PKT_OFFSET)

#define M_MAC_FWDPAUSE_EN	_SB_MAKEMASK1(32)
#define M_MAC_VWAN_DET_EN	_SB_MAKEMASK1(33)

#define S_MAC_WX_CH_MSN_SEW	_SB_MAKE64(34)
#define M_MAC_WX_CH_MSN_SEW	_SB_MAKEMASK(8, S_MAC_WX_CH_MSN_SEW)
#define V_MAC_WX_CH_MSN_SEW(x)	_SB_MAKEVAWUE(x, S_MAC_WX_CH_MSN_SEW)
#define G_MAC_WX_CH_MSN_SEW(x)	_SB_GETVAWUE(x, S_MAC_WX_CH_MSN_SEW, M_MAC_WX_CH_MSN_SEW)
#endif /* 1250 PASS3 || 112x PASS1 || 1480 */

/*
 * MAC Weceive Channew Sewect Wegistews (Tabwe 9-25)
 */

/* no bitfiewds */

/*
 * MAC MII Management Intewface Wegistews (Tabwe 9-26)
 * Wegistew: MAC_MDIO_0
 * Wegistew: MAC_MDIO_1
 * Wegistew: MAC_MDIO_2
 */

#define S_MAC_MDC		0
#define S_MAC_MDIO_DIW		1
#define S_MAC_MDIO_OUT		2
#define S_MAC_GENC		3
#define S_MAC_MDIO_IN		4

#define M_MAC_MDC		_SB_MAKEMASK1(S_MAC_MDC)
#define M_MAC_MDIO_DIW		_SB_MAKEMASK1(S_MAC_MDIO_DIW)
#define M_MAC_MDIO_DIW_INPUT	_SB_MAKEMASK1(S_MAC_MDIO_DIW)
#define M_MAC_MDIO_OUT		_SB_MAKEMASK1(S_MAC_MDIO_OUT)
#define M_MAC_GENC		_SB_MAKEMASK1(S_MAC_GENC)
#define M_MAC_MDIO_IN		_SB_MAKEMASK1(S_MAC_MDIO_IN)

#endif