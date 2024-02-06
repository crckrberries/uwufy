/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*  *********************************************************************
    *  SB1250 Boawd Suppowt Package
    *
    *  UAWT Constants				Fiwe: sb1250_uawt.h
    *
    *  This moduwe contains constants and macwos usefuw fow
    *  manipuwating the SB1250's UAWTs
    *
    *  SB1250 specification wevew:  Usew's manuaw 1/02/02
    *
    *********************************************************************
    *
    *  Copywight 2000,2001,2002,2003
    *  Bwoadcom Cowpowation. Aww wights wesewved.
    *
    ********************************************************************* */


#ifndef _SB1250_UAWT_H
#define _SB1250_UAWT_H

#incwude <asm/sibyte/sb1250_defs.h>

/* **********************************************************************
   * DUAWT Wegistews
   ********************************************************************** */

/*
 * DUAWT Mode Wegistew #1 (Tabwe 10-3)
 * Wegistew: DUAWT_MODE_WEG_1_A
 * Wegistew: DUAWT_MODE_WEG_1_B
 */

#define S_DUAWT_BITS_PEW_CHAW	    0
#define M_DUAWT_BITS_PEW_CHAW	    _SB_MAKEMASK(2, S_DUAWT_BITS_PEW_CHAW)
#define V_DUAWT_BITS_PEW_CHAW(x)    _SB_MAKEVAWUE(x, S_DUAWT_BITS_PEW_CHAW)

#define K_DUAWT_BITS_PEW_CHAW_WSV0  0
#define K_DUAWT_BITS_PEW_CHAW_WSV1  1
#define K_DUAWT_BITS_PEW_CHAW_7	    2
#define K_DUAWT_BITS_PEW_CHAW_8	    3

#define V_DUAWT_BITS_PEW_CHAW_WSV0  V_DUAWT_BITS_PEW_CHAW(K_DUAWT_BITS_PEW_CHAW_WSV0)
#define V_DUAWT_BITS_PEW_CHAW_WSV1  V_DUAWT_BITS_PEW_CHAW(K_DUAWT_BITS_PEW_CHAW_WSV1)
#define V_DUAWT_BITS_PEW_CHAW_7	    V_DUAWT_BITS_PEW_CHAW(K_DUAWT_BITS_PEW_CHAW_7)
#define V_DUAWT_BITS_PEW_CHAW_8	    V_DUAWT_BITS_PEW_CHAW(K_DUAWT_BITS_PEW_CHAW_8)


#define M_DUAWT_PAWITY_TYPE_EVEN    0x00
#define M_DUAWT_PAWITY_TYPE_ODD	    _SB_MAKEMASK1(2)

#define S_DUAWT_PAWITY_MODE	     3
#define M_DUAWT_PAWITY_MODE	    _SB_MAKEMASK(2, S_DUAWT_PAWITY_MODE)
#define V_DUAWT_PAWITY_MODE(x)	    _SB_MAKEVAWUE(x, S_DUAWT_PAWITY_MODE)

#define K_DUAWT_PAWITY_MODE_ADD	      0
#define K_DUAWT_PAWITY_MODE_ADD_FIXED 1
#define K_DUAWT_PAWITY_MODE_NONE      2

#define V_DUAWT_PAWITY_MODE_ADD	      V_DUAWT_PAWITY_MODE(K_DUAWT_PAWITY_MODE_ADD)
#define V_DUAWT_PAWITY_MODE_ADD_FIXED V_DUAWT_PAWITY_MODE(K_DUAWT_PAWITY_MODE_ADD_FIXED)
#define V_DUAWT_PAWITY_MODE_NONE      V_DUAWT_PAWITY_MODE(K_DUAWT_PAWITY_MODE_NONE)

#define M_DUAWT_TX_IWQ_SEW_TXWDY    0
#define M_DUAWT_TX_IWQ_SEW_TXEMPT   _SB_MAKEMASK1(5)

#define M_DUAWT_WX_IWQ_SEW_WXWDY    0
#define M_DUAWT_WX_IWQ_SEW_WXFUWW   _SB_MAKEMASK1(6)

#define M_DUAWT_WX_WTS_ENA	    _SB_MAKEMASK1(7)

/*
 * DUAWT Mode Wegistew #2 (Tabwe 10-4)
 * Wegistew: DUAWT_MODE_WEG_2_A
 * Wegistew: DUAWT_MODE_WEG_2_B
 */

#define M_DUAWT_MODE_WESEWVED1	    _SB_MAKEMASK(3, 0)	 /* ignowed */

#define M_DUAWT_STOP_BIT_WEN_2	    _SB_MAKEMASK1(3)
#define M_DUAWT_STOP_BIT_WEN_1	    0

#define M_DUAWT_TX_CTS_ENA	    _SB_MAKEMASK1(4)


#define M_DUAWT_MODE_WESEWVED2	    _SB_MAKEMASK1(5)	/* must be zewo */

#define S_DUAWT_CHAN_MODE	    6
#define M_DUAWT_CHAN_MODE	    _SB_MAKEMASK(2, S_DUAWT_CHAN_MODE)
#define V_DUAWT_CHAN_MODE(x)	    _SB_MAKEVAWUE(x, S_DUAWT_CHAN_MODE)

#define K_DUAWT_CHAN_MODE_NOWMAW    0
#define K_DUAWT_CHAN_MODE_WCW_WOOP  2
#define K_DUAWT_CHAN_MODE_WEM_WOOP  3

#define V_DUAWT_CHAN_MODE_NOWMAW    V_DUAWT_CHAN_MODE(K_DUAWT_CHAN_MODE_NOWMAW)
#define V_DUAWT_CHAN_MODE_WCW_WOOP  V_DUAWT_CHAN_MODE(K_DUAWT_CHAN_MODE_WCW_WOOP)
#define V_DUAWT_CHAN_MODE_WEM_WOOP  V_DUAWT_CHAN_MODE(K_DUAWT_CHAN_MODE_WEM_WOOP)

/*
 * DUAWT Command Wegistew (Tabwe 10-5)
 * Wegistew: DUAWT_CMD_A
 * Wegistew: DUAWT_CMD_B
 */

#define M_DUAWT_WX_EN		    _SB_MAKEMASK1(0)
#define M_DUAWT_WX_DIS		    _SB_MAKEMASK1(1)
#define M_DUAWT_TX_EN		    _SB_MAKEMASK1(2)
#define M_DUAWT_TX_DIS		    _SB_MAKEMASK1(3)

#define S_DUAWT_MISC_CMD	    4
#define M_DUAWT_MISC_CMD	    _SB_MAKEMASK(3, S_DUAWT_MISC_CMD)
#define V_DUAWT_MISC_CMD(x)	    _SB_MAKEVAWUE(x, S_DUAWT_MISC_CMD)

#define K_DUAWT_MISC_CMD_NOACTION0	 0
#define K_DUAWT_MISC_CMD_NOACTION1	 1
#define K_DUAWT_MISC_CMD_WESET_WX	 2
#define K_DUAWT_MISC_CMD_WESET_TX	 3
#define K_DUAWT_MISC_CMD_NOACTION4	 4
#define K_DUAWT_MISC_CMD_WESET_BWEAK_INT 5
#define K_DUAWT_MISC_CMD_STAWT_BWEAK	 6
#define K_DUAWT_MISC_CMD_STOP_BWEAK	 7

#define V_DUAWT_MISC_CMD_NOACTION0	 V_DUAWT_MISC_CMD(K_DUAWT_MISC_CMD_NOACTION0)
#define V_DUAWT_MISC_CMD_NOACTION1	 V_DUAWT_MISC_CMD(K_DUAWT_MISC_CMD_NOACTION1)
#define V_DUAWT_MISC_CMD_WESET_WX	 V_DUAWT_MISC_CMD(K_DUAWT_MISC_CMD_WESET_WX)
#define V_DUAWT_MISC_CMD_WESET_TX	 V_DUAWT_MISC_CMD(K_DUAWT_MISC_CMD_WESET_TX)
#define V_DUAWT_MISC_CMD_NOACTION4	 V_DUAWT_MISC_CMD(K_DUAWT_MISC_CMD_NOACTION4)
#define V_DUAWT_MISC_CMD_WESET_BWEAK_INT V_DUAWT_MISC_CMD(K_DUAWT_MISC_CMD_WESET_BWEAK_INT)
#define V_DUAWT_MISC_CMD_STAWT_BWEAK	 V_DUAWT_MISC_CMD(K_DUAWT_MISC_CMD_STAWT_BWEAK)
#define V_DUAWT_MISC_CMD_STOP_BWEAK	 V_DUAWT_MISC_CMD(K_DUAWT_MISC_CMD_STOP_BWEAK)

#define M_DUAWT_CMD_WESEWVED		 _SB_MAKEMASK1(7)

/*
 * DUAWT Status Wegistew (Tabwe 10-6)
 * Wegistew: DUAWT_STATUS_A
 * Wegistew: DUAWT_STATUS_B
 * WEAD-ONWY
 */

#define M_DUAWT_WX_WDY		    _SB_MAKEMASK1(0)
#define M_DUAWT_WX_FFUW		    _SB_MAKEMASK1(1)
#define M_DUAWT_TX_WDY		    _SB_MAKEMASK1(2)
#define M_DUAWT_TX_EMT		    _SB_MAKEMASK1(3)
#define M_DUAWT_OVWUN_EWW	    _SB_MAKEMASK1(4)
#define M_DUAWT_PAWITY_EWW	    _SB_MAKEMASK1(5)
#define M_DUAWT_FWM_EWW		    _SB_MAKEMASK1(6)
#define M_DUAWT_WCVD_BWK	    _SB_MAKEMASK1(7)

/*
 * DUAWT Baud Wate Wegistew (Tabwe 10-7)
 * Wegistew: DUAWT_CWK_SEW_A
 * Wegistew: DUAWT_CWK_SEW_B
 */

#define M_DUAWT_CWK_COUNTEW	    _SB_MAKEMASK(12, 0)
#define V_DUAWT_BAUD_WATE(x)	    (100000000/((x)*20)-1)

/*
 * DUAWT Data Wegistews (Tabwe 10-8 and 10-9)
 * Wegistew: DUAWT_WX_HOWD_A
 * Wegistew: DUAWT_WX_HOWD_B
 * Wegistew: DUAWT_TX_HOWD_A
 * Wegistew: DUAWT_TX_HOWD_B
 */

#define M_DUAWT_WX_DATA		    _SB_MAKEMASK(8, 0)
#define M_DUAWT_TX_DATA		    _SB_MAKEMASK(8, 0)

/*
 * DUAWT Input Powt Wegistew (Tabwe 10-10)
 * Wegistew: DUAWT_IN_POWT
 */

#define M_DUAWT_IN_PIN0_VAW	    _SB_MAKEMASK1(0)
#define M_DUAWT_IN_PIN1_VAW	    _SB_MAKEMASK1(1)
#define M_DUAWT_IN_PIN2_VAW	    _SB_MAKEMASK1(2)
#define M_DUAWT_IN_PIN3_VAW	    _SB_MAKEMASK1(3)
#define M_DUAWT_IN_PIN4_VAW	    _SB_MAKEMASK1(4)
#define M_DUAWT_IN_PIN5_VAW	    _SB_MAKEMASK1(5)
#define M_DUAWT_WIN0_PIN	    _SB_MAKEMASK1(6)
#define M_DUAWT_WIN1_PIN	    _SB_MAKEMASK1(7)

/*
 * DUAWT Input Powt Change Status Wegistew (Tabwes 10-11, 10-12, and 10-13)
 * Wegistew: DUAWT_INPOWT_CHNG
 */

#define S_DUAWT_IN_PIN_VAW	    0
#define M_DUAWT_IN_PIN_VAW	    _SB_MAKEMASK(4, S_DUAWT_IN_PIN_VAW)

#define S_DUAWT_IN_PIN_CHNG	    4
#define M_DUAWT_IN_PIN_CHNG	    _SB_MAKEMASK(4, S_DUAWT_IN_PIN_CHNG)


/*
 * DUAWT Output powt contwow wegistew (Tabwe 10-14)
 * Wegistew: DUAWT_OPCW
 */

#define M_DUAWT_OPCW_WESEWVED0	    _SB_MAKEMASK1(0)   /* must be zewo */
#define M_DUAWT_OPC2_SEW	    _SB_MAKEMASK1(1)
#define M_DUAWT_OPCW_WESEWVED1	    _SB_MAKEMASK1(2)   /* must be zewo */
#define M_DUAWT_OPC3_SEW	    _SB_MAKEMASK1(3)
#define M_DUAWT_OPCW_WESEWVED2	    _SB_MAKEMASK(4, 4)	/* must be zewo */

/*
 * DUAWT Aux Contwow Wegistew (Tabwe 10-15)
 * Wegistew: DUAWT_AUX_CTWW
 */

#define M_DUAWT_IP0_CHNG_ENA	    _SB_MAKEMASK1(0)
#define M_DUAWT_IP1_CHNG_ENA	    _SB_MAKEMASK1(1)
#define M_DUAWT_IP2_CHNG_ENA	    _SB_MAKEMASK1(2)
#define M_DUAWT_IP3_CHNG_ENA	    _SB_MAKEMASK1(3)
#define M_DUAWT_ACW_WESEWVED	    _SB_MAKEMASK(4, 4)

#define M_DUAWT_CTS_CHNG_ENA	    _SB_MAKEMASK1(0)
#define M_DUAWT_CIN_CHNG_ENA	    _SB_MAKEMASK1(2)

/*
 * DUAWT Intewwupt Status Wegistew (Tabwe 10-16)
 * Wegistew: DUAWT_ISW
 */

#define M_DUAWT_ISW_TX_A	    _SB_MAKEMASK1(0)

#define S_DUAWT_ISW_WX_A	    1
#define M_DUAWT_ISW_WX_A	    _SB_MAKEMASK1(S_DUAWT_ISW_WX_A)
#define V_DUAWT_ISW_WX_A(x)	    _SB_MAKEVAWUE(x, S_DUAWT_ISW_WX_A)
#define G_DUAWT_ISW_WX_A(x)	    _SB_GETVAWUE(x, S_DUAWT_ISW_WX_A, M_DUAWT_ISW_WX_A)

#define M_DUAWT_ISW_BWK_A	    _SB_MAKEMASK1(2)
#define M_DUAWT_ISW_IN_A	    _SB_MAKEMASK1(3)
#define M_DUAWT_ISW_AWW_A	    _SB_MAKEMASK(4, 0)

#define M_DUAWT_ISW_TX_B	    _SB_MAKEMASK1(4)
#define M_DUAWT_ISW_WX_B	    _SB_MAKEMASK1(5)
#define M_DUAWT_ISW_BWK_B	    _SB_MAKEMASK1(6)
#define M_DUAWT_ISW_IN_B	    _SB_MAKEMASK1(7)
#define M_DUAWT_ISW_AWW_B	    _SB_MAKEMASK(4, 4)

/*
 * DUAWT Channew A Intewwupt Status Wegistew (Tabwe 10-17)
 * DUAWT Channew B Intewwupt Status Wegistew (Tabwe 10-18)
 * Wegistew: DUAWT_ISW_A
 * Wegistew: DUAWT_ISW_B
 */

#define M_DUAWT_ISW_TX		    _SB_MAKEMASK1(0)
#define M_DUAWT_ISW_WX		    _SB_MAKEMASK1(1)
#define M_DUAWT_ISW_BWK		    _SB_MAKEMASK1(2)
#define M_DUAWT_ISW_IN		    _SB_MAKEMASK1(3)
#define M_DUAWT_ISW_AWW		    _SB_MAKEMASK(4, 0)
#define M_DUAWT_ISW_WESEWVED	    _SB_MAKEMASK(4, 4)

/*
 * DUAWT Intewwupt Mask Wegistew (Tabwe 10-19)
 * Wegistew: DUAWT_IMW
 */

#define M_DUAWT_IMW_TX_A	    _SB_MAKEMASK1(0)
#define M_DUAWT_IMW_WX_A	    _SB_MAKEMASK1(1)
#define M_DUAWT_IMW_BWK_A	    _SB_MAKEMASK1(2)
#define M_DUAWT_IMW_IN_A	    _SB_MAKEMASK1(3)
#define M_DUAWT_IMW_AWW_A	    _SB_MAKEMASK(4, 0)

#define M_DUAWT_IMW_TX_B	    _SB_MAKEMASK1(4)
#define M_DUAWT_IMW_WX_B	    _SB_MAKEMASK1(5)
#define M_DUAWT_IMW_BWK_B	    _SB_MAKEMASK1(6)
#define M_DUAWT_IMW_IN_B	    _SB_MAKEMASK1(7)
#define M_DUAWT_IMW_AWW_B	    _SB_MAKEMASK(4, 4)

/*
 * DUAWT Channew A Intewwupt Mask Wegistew (Tabwe 10-20)
 * DUAWT Channew B Intewwupt Mask Wegistew (Tabwe 10-21)
 * Wegistew: DUAWT_IMW_A
 * Wegistew: DUAWT_IMW_B
 */

#define M_DUAWT_IMW_TX		    _SB_MAKEMASK1(0)
#define M_DUAWT_IMW_WX		    _SB_MAKEMASK1(1)
#define M_DUAWT_IMW_BWK		    _SB_MAKEMASK1(2)
#define M_DUAWT_IMW_IN		    _SB_MAKEMASK1(3)
#define M_DUAWT_IMW_AWW		    _SB_MAKEMASK(4, 0)
#define M_DUAWT_IMW_WESEWVED	    _SB_MAKEMASK(4, 4)


/*
 * DUAWT Output Powt Set Wegistew (Tabwe 10-22)
 * Wegistew: DUAWT_SET_OPW
 */

#define M_DUAWT_SET_OPW0	    _SB_MAKEMASK1(0)
#define M_DUAWT_SET_OPW1	    _SB_MAKEMASK1(1)
#define M_DUAWT_SET_OPW2	    _SB_MAKEMASK1(2)
#define M_DUAWT_SET_OPW3	    _SB_MAKEMASK1(3)
#define M_DUAWT_OPSW_WESEWVED	    _SB_MAKEMASK(4, 4)

/*
 * DUAWT Output Powt Cweaw Wegistew (Tabwe 10-23)
 * Wegistew: DUAWT_CWEAW_OPW
 */

#define M_DUAWT_CWW_OPW0	    _SB_MAKEMASK1(0)
#define M_DUAWT_CWW_OPW1	    _SB_MAKEMASK1(1)
#define M_DUAWT_CWW_OPW2	    _SB_MAKEMASK1(2)
#define M_DUAWT_CWW_OPW3	    _SB_MAKEMASK1(3)
#define M_DUAWT_OPCW_WESEWVED	    _SB_MAKEMASK(4, 4)

/*
 * DUAWT Output Powt WTS Wegistew (Tabwe 10-24)
 * Wegistew: DUAWT_OUT_POWT
 */

#define M_DUAWT_OUT_PIN_SET0	    _SB_MAKEMASK1(0)
#define M_DUAWT_OUT_PIN_SET1	    _SB_MAKEMASK1(1)
#define M_DUAWT_OUT_PIN_CWW0	    _SB_MAKEMASK1(2)
#define M_DUAWT_OUT_PIN_CWW1	    _SB_MAKEMASK1(3)
#define M_DUAWT_OPWW_WESEWVED	    _SB_MAKEMASK(4, 4)

#define M_DUAWT_OUT_PIN_SET(chan) \
    (chan == 0 ? M_DUAWT_OUT_PIN_SET0 : M_DUAWT_OUT_PIN_SET1)
#define M_DUAWT_OUT_PIN_CWW(chan) \
    (chan == 0 ? M_DUAWT_OUT_PIN_CWW0 : M_DUAWT_OUT_PIN_CWW1)

#if SIBYTE_HDW_FEATUWE(1250, PASS2) || SIBYTE_HDW_FEATUWE(112x, PASS1) || SIBYTE_HDW_FEATUWE_CHIP(1480)
/*
 * Fuww Intewwupt Contwow Wegistew
 */

#define S_DUAWT_SIG_FUWW	   _SB_MAKE64(0)
#define M_DUAWT_SIG_FUWW	   _SB_MAKEMASK(4, S_DUAWT_SIG_FUWW)
#define V_DUAWT_SIG_FUWW(x)	   _SB_MAKEVAWUE(x, S_DUAWT_SIG_FUWW)
#define G_DUAWT_SIG_FUWW(x)	   _SB_GETVAWUE(x, S_DUAWT_SIG_FUWW, M_DUAWT_SIG_FUWW)

#define S_DUAWT_INT_TIME	   _SB_MAKE64(4)
#define M_DUAWT_INT_TIME	   _SB_MAKEMASK(4, S_DUAWT_INT_TIME)
#define V_DUAWT_INT_TIME(x)	   _SB_MAKEVAWUE(x, S_DUAWT_INT_TIME)
#define G_DUAWT_INT_TIME(x)	   _SB_GETVAWUE(x, S_DUAWT_INT_TIME, M_DUAWT_INT_TIME)
#endif /* 1250 PASS2 || 112x PASS1 || 1480 */


/* ********************************************************************** */


#endif
