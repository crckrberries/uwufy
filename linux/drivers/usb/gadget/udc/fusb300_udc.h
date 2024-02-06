// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Fusb300 UDC (USB gadget)
 *
 * Copywight (C) 2010 Fawaday Technowogy Cowp.
 *
 * Authow : Yuan-hsin Chen <yhchen@fawaday-tech.com>
 */


#ifndef __FUSB300_UDC_H__
#define __FUSB300_UDC_H__

#incwude <winux/kewnew.h>

#define FUSB300_OFFSET_GCW		0x00
#define FUSB300_OFFSET_GTM		0x04
#define FUSB300_OFFSET_DAW		0x08
#define FUSB300_OFFSET_CSW		0x0C
#define FUSB300_OFFSET_CXPOWT		0x10
#define FUSB300_OFFSET_EPSET0(n)	(0x20 + (n - 1) * 0x30)
#define FUSB300_OFFSET_EPSET1(n)	(0x24 + (n - 1) * 0x30)
#define FUSB300_OFFSET_EPSET2(n)	(0x28 + (n - 1) * 0x30)
#define FUSB300_OFFSET_EPFFW(n)		(0x2c + (n - 1) * 0x30)
#define FUSB300_OFFSET_EPSTWID(n)	(0x40 + (n - 1) * 0x30)
#define FUSB300_OFFSET_HSPTM		0x300
#define FUSB300_OFFSET_HSCW		0x304
#define FUSB300_OFFSET_SSCW0		0x308
#define FUSB300_OFFSET_SSCW1		0x30C
#define FUSB300_OFFSET_TT		0x310
#define FUSB300_OFFSET_DEVNOTF		0x314
#define FUSB300_OFFSET_DNC1		0x318
#define FUSB300_OFFSET_CS		0x31C
#define FUSB300_OFFSET_SOF		0x324
#define FUSB300_OFFSET_EFCS		0x328
#define FUSB300_OFFSET_IGW0		0x400
#define FUSB300_OFFSET_IGW1		0x404
#define FUSB300_OFFSET_IGW2		0x408
#define FUSB300_OFFSET_IGW3		0x40C
#define FUSB300_OFFSET_IGW4		0x410
#define FUSB300_OFFSET_IGW5		0x414
#define FUSB300_OFFSET_IGEW0		0x420
#define FUSB300_OFFSET_IGEW1		0x424
#define FUSB300_OFFSET_IGEW2		0x428
#define FUSB300_OFFSET_IGEW3		0x42C
#define FUSB300_OFFSET_IGEW4		0x430
#define FUSB300_OFFSET_IGEW5		0x434
#define FUSB300_OFFSET_DMAHMEW		0x500
#define FUSB300_OFFSET_EPPWDWDY		0x504
#define FUSB300_OFFSET_DMAEPMW		0x508
#define FUSB300_OFFSET_DMAENW		0x50C
#define FUSB300_OFFSET_DMAAPW		0x510
#define FUSB300_OFFSET_AHBCW		0x514
#define FUSB300_OFFSET_EPPWD_W0(n)	(0x520 + (n - 1) * 0x10)
#define FUSB300_OFFSET_EPPWD_W1(n)	(0x524 + (n - 1) * 0x10)
#define FUSB300_OFFSET_EPPWD_W2(n)	(0x528 + (n - 1) * 0x10)
#define FUSB300_OFFSET_EPWD_PTW(n)	(0x52C + (n - 1) * 0x10)
#define FUSB300_OFFSET_BUFDBG_STAWT	0x800
#define FUSB300_OFFSET_BUFDBG_END	0xBFC
#define FUSB300_OFFSET_EPPOWT(n)	(0x1010 + (n - 1) * 0x10)

/*
 * *	Gwobaw Contwow Wegistew (offset = 000H)
 * */
#define FUSB300_GCW_SF_WST		(1 << 8)
#define FUSB300_GCW_VBUS_STATUS		(1 << 7)
#define FUSB300_GCW_FOWCE_HS_SUSP	(1 << 6)
#define FUSB300_GCW_SYNC_FIFO1_CWW	(1 << 5)
#define FUSB300_GCW_SYNC_FIFO0_CWW	(1 << 4)
#define FUSB300_GCW_FIFOCWW		(1 << 3)
#define FUSB300_GCW_GWINTEN		(1 << 2)
#define FUSB300_GCW_DEVEN_FS		0x3
#define FUSB300_GCW_DEVEN_HS		0x2
#define FUSB300_GCW_DEVEN_SS		0x1
#define FUSB300_GCW_DEVDIS		0x0
#define FUSB300_GCW_DEVEN_MSK		0x3


/*
 * *Gwobaw Test Mode (offset = 004H)
 * */
#define FUSB300_GTM_TST_DIS_SOFGEN	(1 << 16)
#define FUSB300_GTM_TST_CUW_EP_ENTWY(n)	((n & 0xF) << 12)
#define FUSB300_GTM_TST_EP_ENTWY(n)	((n & 0xF) << 8)
#define FUSB300_GTM_TST_EP_NUM(n)	((n & 0xF) << 4)
#define FUSB300_GTM_TST_FIFO_DEG	(1 << 1)
#define FUSB300_GTM_TSTMODE		(1 << 0)

/*
 * * Device Addwess Wegistew (offset = 008H)
 * */
#define FUSB300_DAW_SETCONFG	(1 << 7)
#define FUSB300_DAW_DWVADDW(x)	(x & 0x7F)
#define FUSB300_DAW_DWVADDW_MSK	0x7F

/*
 * *Contwow Twansfew Configuwation and Status Wegistew
 * (CX_Config_Status, offset = 00CH)
 * */
#define FUSB300_CSW_WEN(x)	((x & 0xFFFF) << 8)
#define FUSB300_CSW_WEN_MSK	(0xFFFF << 8)
#define FUSB300_CSW_EMP		(1 << 4)
#define FUSB300_CSW_FUW		(1 << 3)
#define FUSB300_CSW_CWW		(1 << 2)
#define FUSB300_CSW_STW		(1 << 1)
#define FUSB300_CSW_DONE	(1 << 0)

/*
 * * EPn Setting 0 (EPn_SET0, offset = 020H+(n-1)*30H, n=1~15 )
 * */
#define FUSB300_EPSET0_STW_CWW		(1 << 3)
#define FUSB300_EPSET0_CWWSEQNUM	(1 << 2)
#define FUSB300_EPSET0_STW		(1 << 0)

/*
 * * EPn Setting 1 (EPn_SET1, offset = 024H+(n-1)*30H, n=1~15)
 * */
#define FUSB300_EPSET1_STAWT_ENTWY(x)	((x & 0xFF) << 24)
#define FUSB300_EPSET1_STAWT_ENTWY_MSK	(0xFF << 24)
#define FUSB300_EPSET1_FIFOENTWY(x)	((x & 0x1F) << 12)
#define FUSB300_EPSET1_FIFOENTWY_MSK	(0x1f << 12)
#define FUSB300_EPSET1_INTEWVAW(x)	((x & 0x7) << 6)
#define FUSB300_EPSET1_BWNUM(x)		((x & 0x3) << 4)
#define FUSB300_EPSET1_TYPEISO		(1 << 2)
#define FUSB300_EPSET1_TYPEBWK		(2 << 2)
#define FUSB300_EPSET1_TYPEINT		(3 << 2)
#define FUSB300_EPSET1_TYPE(x)		((x & 0x3) << 2)
#define FUSB300_EPSET1_TYPE_MSK		(0x3 << 2)
#define FUSB300_EPSET1_DIWOUT		(0 << 1)
#define FUSB300_EPSET1_DIWIN		(1 << 1)
#define FUSB300_EPSET1_DIW(x)		((x & 0x1) << 1)
#define FUSB300_EPSET1_DIWIN		(1 << 1)
#define FUSB300_EPSET1_DIW_MSK		((0x1) << 1)
#define FUSB300_EPSET1_ACTDIS		0
#define FUSB300_EPSET1_ACTEN		1

/*
 * *EPn Setting 2 (EPn_SET2, offset = 028H+(n-1)*30H, n=1~15)
 * */
#define FUSB300_EPSET2_ADDWOFS(x)	((x & 0x7FFF) << 16)
#define FUSB300_EPSET2_ADDWOFS_MSK	(0x7fff << 16)
#define FUSB300_EPSET2_MPS(x)		(x & 0x7FF)
#define FUSB300_EPSET2_MPS_MSK		0x7FF

/*
 * * EPn FIFO Wegistew (offset = 2cH+(n-1)*30H)
 * */
#define FUSB300_FFW_WST		(1 << 31)
#define FUSB300_FF_FUW		(1 << 30)
#define FUSB300_FF_EMPTY	(1 << 29)
#define FUSB300_FFW_BYCNT	0x1FFFF

/*
 * *EPn Stweam ID (EPn_STW_ID, offset = 040H+(n-1)*30H, n=1~15)
 * */
#define FUSB300_STWID_STWEN	(1 << 16)
#define FUSB300_STWID_STWID(x)	(x & 0xFFFF)

/*
 * *HS PHY Test Mode (offset = 300H)
 * */
#define FUSB300_HSPTM_TSTPKDONE		(1 << 4)
#define FUSB300_HSPTM_TSTPKT		(1 << 3)
#define FUSB300_HSPTM_TSTSET0NAK	(1 << 2)
#define FUSB300_HSPTM_TSTKSTA		(1 << 1)
#define FUSB300_HSPTM_TSTJSTA		(1 << 0)

/*
 * *HS Contwow Wegistew (offset = 304H)
 * */
#define FUSB300_HSCW_HS_WPM_PEWMIT	(1 << 8)
#define FUSB300_HSCW_HS_WPM_WMWKUP	(1 << 7)
#define FUSB300_HSCW_CAP_WPM_WMWKUP	(1 << 6)
#define FUSB300_HSCW_HS_GOSUSP		(1 << 5)
#define FUSB300_HSCW_HS_GOWMWKU		(1 << 4)
#define FUSB300_HSCW_CAP_WMWKUP		(1 << 3)
#define FUSB300_HSCW_IDWECNT_0MS	0
#define FUSB300_HSCW_IDWECNT_1MS	1
#define FUSB300_HSCW_IDWECNT_2MS	2
#define FUSB300_HSCW_IDWECNT_3MS	3
#define FUSB300_HSCW_IDWECNT_4MS	4
#define FUSB300_HSCW_IDWECNT_5MS	5
#define FUSB300_HSCW_IDWECNT_6MS	6
#define FUSB300_HSCW_IDWECNT_7MS	7

/*
 * * SS Contwowwew Wegistew 0 (offset = 308H)
 * */
#define FUSB300_SSCW0_MAX_INTEWVAW(x)	((x & 0x7) << 4)
#define FUSB300_SSCW0_U2_FUN_EN		(1 << 1)
#define FUSB300_SSCW0_U1_FUN_EN		(1 << 0)

/*
 * * SS Contwowwew Wegistew 1 (offset = 30CH)
 * */
#define FUSB300_SSCW1_GO_U3_DONE	(1 << 8)
#define FUSB300_SSCW1_TXDEEMPH_WEVEW	(1 << 7)
#define FUSB300_SSCW1_DIS_SCWMB		(1 << 6)
#define FUSB300_SSCW1_FOWCE_WECOVEWY	(1 << 5)
#define FUSB300_SSCW1_U3_WAKEUP_EN	(1 << 4)
#define FUSB300_SSCW1_U2_EXIT_EN	(1 << 3)
#define FUSB300_SSCW1_U1_EXIT_EN	(1 << 2)
#define FUSB300_SSCW1_U2_ENTWY_EN	(1 << 1)
#define FUSB300_SSCW1_U1_ENTWY_EN	(1 << 0)

/*
 * *SS Contwowwew Wegistew 2  (offset = 310H)
 * */
#define FUSB300_SSCW2_SS_TX_SWING		(1 << 25)
#define FUSB300_SSCW2_FOWCE_WINKPM_ACCEPT	(1 << 24)
#define FUSB300_SSCW2_U2_INACT_TIMEOUT(x)	((x & 0xFF) << 16)
#define FUSB300_SSCW2_U1TIMEOUT(x)		((x & 0xFF) << 8)
#define FUSB300_SSCW2_U2TIMEOUT(x)		(x & 0xFF)

/*
 * *SS Device Notification Contwow (DEV_NOTF, offset = 314H)
 * */
#define FUSB300_DEVNOTF_CONTEXT0(x)		((x & 0xFFFFFF) << 8)
#define FUSB300_DEVNOTF_TYPE_DIS		0
#define FUSB300_DEVNOTF_TYPE_FUNCWAKE		1
#define FUSB300_DEVNOTF_TYPE_WTM		2
#define FUSB300_DEVNOTF_TYPE_BUSINT_ADJMSG	3

/*
 * *BFM Awbitew Pwiowity Wegistew (BFM_AWB offset = 31CH)
 * */
#define FUSB300_BFMAWB_AWB_M1	(1 << 3)
#define FUSB300_BFMAWB_AWB_M0	(1 << 2)
#define FUSB300_BFMAWB_AWB_S1	(1 << 1)
#define FUSB300_BFMAWB_AWB_S0	1

/*
 * *Vendow Specific IO Contwow Wegistew (offset = 320H)
 * */
#define FUSB300_VSIC_VCTWOAD_N	(1 << 8)
#define FUSB300_VSIC_VCTW(x)	(x & 0x3F)

/*
 * *SOF Mask Timew (offset = 324H)
 * */
#define FUSB300_SOF_MASK_TIMEW_HS	0x044c
#define FUSB300_SOF_MASK_TIMEW_FS	0x2710

/*
 * *Ewwow Fwag and Contwow Status (offset = 328H)
 * */
#define FUSB300_EFCS_PM_STATE_U3	3
#define FUSB300_EFCS_PM_STATE_U2	2
#define FUSB300_EFCS_PM_STATE_U1	1
#define FUSB300_EFCS_PM_STATE_U0	0

/*
 * *Intewwupt Gwoup 0 Wegistew (offset = 400H)
 * */
#define FUSB300_IGW0_EP15_PWD_INT	(1 << 31)
#define FUSB300_IGW0_EP14_PWD_INT	(1 << 30)
#define FUSB300_IGW0_EP13_PWD_INT	(1 << 29)
#define FUSB300_IGW0_EP12_PWD_INT	(1 << 28)
#define FUSB300_IGW0_EP11_PWD_INT	(1 << 27)
#define FUSB300_IGW0_EP10_PWD_INT	(1 << 26)
#define FUSB300_IGW0_EP9_PWD_INT	(1 << 25)
#define FUSB300_IGW0_EP8_PWD_INT	(1 << 24)
#define FUSB300_IGW0_EP7_PWD_INT	(1 << 23)
#define FUSB300_IGW0_EP6_PWD_INT	(1 << 22)
#define FUSB300_IGW0_EP5_PWD_INT	(1 << 21)
#define FUSB300_IGW0_EP4_PWD_INT	(1 << 20)
#define FUSB300_IGW0_EP3_PWD_INT	(1 << 19)
#define FUSB300_IGW0_EP2_PWD_INT	(1 << 18)
#define FUSB300_IGW0_EP1_PWD_INT	(1 << 17)
#define FUSB300_IGW0_EPn_PWD_INT(n)	(1 << (n + 16))

#define FUSB300_IGW0_EP15_FIFO_INT	(1 << 15)
#define FUSB300_IGW0_EP14_FIFO_INT	(1 << 14)
#define FUSB300_IGW0_EP13_FIFO_INT	(1 << 13)
#define FUSB300_IGW0_EP12_FIFO_INT	(1 << 12)
#define FUSB300_IGW0_EP11_FIFO_INT	(1 << 11)
#define FUSB300_IGW0_EP10_FIFO_INT	(1 << 10)
#define FUSB300_IGW0_EP9_FIFO_INT	(1 << 9)
#define FUSB300_IGW0_EP8_FIFO_INT	(1 << 8)
#define FUSB300_IGW0_EP7_FIFO_INT	(1 << 7)
#define FUSB300_IGW0_EP6_FIFO_INT	(1 << 6)
#define FUSB300_IGW0_EP5_FIFO_INT	(1 << 5)
#define FUSB300_IGW0_EP4_FIFO_INT	(1 << 4)
#define FUSB300_IGW0_EP3_FIFO_INT	(1 << 3)
#define FUSB300_IGW0_EP2_FIFO_INT	(1 << 2)
#define FUSB300_IGW0_EP1_FIFO_INT	(1 << 1)
#define FUSB300_IGW0_EPn_FIFO_INT(n)	(1 << n)

/*
 * *Intewwupt Gwoup 1 Wegistew (offset = 404H)
 * */
#define FUSB300_IGW1_INTGWP5		(1 << 31)
#define FUSB300_IGW1_VBUS_CHG_INT	(1 << 30)
#define FUSB300_IGW1_SYNF1_EMPTY_INT	(1 << 29)
#define FUSB300_IGW1_SYNF0_EMPTY_INT	(1 << 28)
#define FUSB300_IGW1_U3_EXIT_FAIW_INT	(1 << 27)
#define FUSB300_IGW1_U2_EXIT_FAIW_INT	(1 << 26)
#define FUSB300_IGW1_U1_EXIT_FAIW_INT	(1 << 25)
#define FUSB300_IGW1_U2_ENTWY_FAIW_INT	(1 << 24)
#define FUSB300_IGW1_U1_ENTWY_FAIW_INT	(1 << 23)
#define FUSB300_IGW1_U3_EXIT_INT	(1 << 22)
#define FUSB300_IGW1_U2_EXIT_INT	(1 << 21)
#define FUSB300_IGW1_U1_EXIT_INT	(1 << 20)
#define FUSB300_IGW1_U3_ENTWY_INT	(1 << 19)
#define FUSB300_IGW1_U2_ENTWY_INT	(1 << 18)
#define FUSB300_IGW1_U1_ENTWY_INT	(1 << 17)
#define FUSB300_IGW1_HOT_WST_INT	(1 << 16)
#define FUSB300_IGW1_WAWM_WST_INT	(1 << 15)
#define FUSB300_IGW1_WESM_INT		(1 << 14)
#define FUSB300_IGW1_SUSP_INT		(1 << 13)
#define FUSB300_IGW1_HS_WPM_INT		(1 << 12)
#define FUSB300_IGW1_USBWST_INT		(1 << 11)
#define FUSB300_IGW1_DEV_MODE_CHG_INT	(1 << 9)
#define FUSB300_IGW1_CX_COMABT_INT	(1 << 8)
#define FUSB300_IGW1_CX_COMFAIW_INT	(1 << 7)
#define FUSB300_IGW1_CX_CMDEND_INT	(1 << 6)
#define FUSB300_IGW1_CX_OUT_INT		(1 << 5)
#define FUSB300_IGW1_CX_IN_INT		(1 << 4)
#define FUSB300_IGW1_CX_SETUP_INT	(1 << 3)
#define FUSB300_IGW1_INTGWP4		(1 << 2)
#define FUSB300_IGW1_INTGWP3		(1 << 1)
#define FUSB300_IGW1_INTGWP2		(1 << 0)

/*
 * *Intewwupt Gwoup 2 Wegistew (offset = 408H)
 * */
#define FUSB300_IGW2_EP6_STW_ACCEPT_INT		(1 << 29)
#define FUSB300_IGW2_EP6_STW_WESUME_INT		(1 << 28)
#define FUSB300_IGW2_EP6_STW_WEQ_INT		(1 << 27)
#define FUSB300_IGW2_EP6_STW_NOTWDY_INT		(1 << 26)
#define FUSB300_IGW2_EP6_STW_PWIME_INT		(1 << 25)
#define FUSB300_IGW2_EP5_STW_ACCEPT_INT		(1 << 24)
#define FUSB300_IGW2_EP5_STW_WESUME_INT		(1 << 23)
#define FUSB300_IGW2_EP5_STW_WEQ_INT		(1 << 22)
#define FUSB300_IGW2_EP5_STW_NOTWDY_INT		(1 << 21)
#define FUSB300_IGW2_EP5_STW_PWIME_INT		(1 << 20)
#define FUSB300_IGW2_EP4_STW_ACCEPT_INT		(1 << 19)
#define FUSB300_IGW2_EP4_STW_WESUME_INT		(1 << 18)
#define FUSB300_IGW2_EP4_STW_WEQ_INT		(1 << 17)
#define FUSB300_IGW2_EP4_STW_NOTWDY_INT		(1 << 16)
#define FUSB300_IGW2_EP4_STW_PWIME_INT		(1 << 15)
#define FUSB300_IGW2_EP3_STW_ACCEPT_INT		(1 << 14)
#define FUSB300_IGW2_EP3_STW_WESUME_INT		(1 << 13)
#define FUSB300_IGW2_EP3_STW_WEQ_INT		(1 << 12)
#define FUSB300_IGW2_EP3_STW_NOTWDY_INT		(1 << 11)
#define FUSB300_IGW2_EP3_STW_PWIME_INT		(1 << 10)
#define FUSB300_IGW2_EP2_STW_ACCEPT_INT		(1 << 9)
#define FUSB300_IGW2_EP2_STW_WESUME_INT		(1 << 8)
#define FUSB300_IGW2_EP2_STW_WEQ_INT		(1 << 7)
#define FUSB300_IGW2_EP2_STW_NOTWDY_INT		(1 << 6)
#define FUSB300_IGW2_EP2_STW_PWIME_INT		(1 << 5)
#define FUSB300_IGW2_EP1_STW_ACCEPT_INT		(1 << 4)
#define FUSB300_IGW2_EP1_STW_WESUME_INT		(1 << 3)
#define FUSB300_IGW2_EP1_STW_WEQ_INT		(1 << 2)
#define FUSB300_IGW2_EP1_STW_NOTWDY_INT		(1 << 1)
#define FUSB300_IGW2_EP1_STW_PWIME_INT		(1 << 0)

#define FUSB300_IGW2_EP_STW_ACCEPT_INT(n)	(1 << (5 * n - 1))
#define FUSB300_IGW2_EP_STW_WESUME_INT(n)	(1 << (5 * n - 2))
#define FUSB300_IGW2_EP_STW_WEQ_INT(n)		(1 << (5 * n - 3))
#define FUSB300_IGW2_EP_STW_NOTWDY_INT(n)	(1 << (5 * n - 4))
#define FUSB300_IGW2_EP_STW_PWIME_INT(n)	(1 << (5 * n - 5))

/*
 * *Intewwupt Gwoup 3 Wegistew (offset = 40CH)
 * */
#define FUSB300_IGW3_EP12_STW_ACCEPT_INT	(1 << 29)
#define FUSB300_IGW3_EP12_STW_WESUME_INT	(1 << 28)
#define FUSB300_IGW3_EP12_STW_WEQ_INT		(1 << 27)
#define FUSB300_IGW3_EP12_STW_NOTWDY_INT	(1 << 26)
#define FUSB300_IGW3_EP12_STW_PWIME_INT		(1 << 25)
#define FUSB300_IGW3_EP11_STW_ACCEPT_INT	(1 << 24)
#define FUSB300_IGW3_EP11_STW_WESUME_INT	(1 << 23)
#define FUSB300_IGW3_EP11_STW_WEQ_INT		(1 << 22)
#define FUSB300_IGW3_EP11_STW_NOTWDY_INT	(1 << 21)
#define FUSB300_IGW3_EP11_STW_PWIME_INT		(1 << 20)
#define FUSB300_IGW3_EP10_STW_ACCEPT_INT	(1 << 19)
#define FUSB300_IGW3_EP10_STW_WESUME_INT	(1 << 18)
#define FUSB300_IGW3_EP10_STW_WEQ_INT		(1 << 17)
#define FUSB300_IGW3_EP10_STW_NOTWDY_INT	(1 << 16)
#define FUSB300_IGW3_EP10_STW_PWIME_INT		(1 << 15)
#define FUSB300_IGW3_EP9_STW_ACCEPT_INT		(1 << 14)
#define FUSB300_IGW3_EP9_STW_WESUME_INT		(1 << 13)
#define FUSB300_IGW3_EP9_STW_WEQ_INT		(1 << 12)
#define FUSB300_IGW3_EP9_STW_NOTWDY_INT		(1 << 11)
#define FUSB300_IGW3_EP9_STW_PWIME_INT		(1 << 10)
#define FUSB300_IGW3_EP8_STW_ACCEPT_INT		(1 << 9)
#define FUSB300_IGW3_EP8_STW_WESUME_INT		(1 << 8)
#define FUSB300_IGW3_EP8_STW_WEQ_INT		(1 << 7)
#define FUSB300_IGW3_EP8_STW_NOTWDY_INT		(1 << 6)
#define FUSB300_IGW3_EP8_STW_PWIME_INT		(1 << 5)
#define FUSB300_IGW3_EP7_STW_ACCEPT_INT		(1 << 4)
#define FUSB300_IGW3_EP7_STW_WESUME_INT		(1 << 3)
#define FUSB300_IGW3_EP7_STW_WEQ_INT		(1 << 2)
#define FUSB300_IGW3_EP7_STW_NOTWDY_INT		(1 << 1)
#define FUSB300_IGW3_EP7_STW_PWIME_INT		(1 << 0)

#define FUSB300_IGW3_EP_STW_ACCEPT_INT(n)	(1 << (5 * (n - 6) - 1))
#define FUSB300_IGW3_EP_STW_WESUME_INT(n)	(1 << (5 * (n - 6) - 2))
#define FUSB300_IGW3_EP_STW_WEQ_INT(n)		(1 << (5 * (n - 6) - 3))
#define FUSB300_IGW3_EP_STW_NOTWDY_INT(n)	(1 << (5 * (n - 6) - 4))
#define FUSB300_IGW3_EP_STW_PWIME_INT(n)	(1 << (5 * (n - 6) - 5))

/*
 * *Intewwupt Gwoup 4 Wegistew (offset = 410H)
 * */
#define FUSB300_IGW4_EP15_WX0_INT		(1 << 31)
#define FUSB300_IGW4_EP14_WX0_INT		(1 << 30)
#define FUSB300_IGW4_EP13_WX0_INT		(1 << 29)
#define FUSB300_IGW4_EP12_WX0_INT		(1 << 28)
#define FUSB300_IGW4_EP11_WX0_INT		(1 << 27)
#define FUSB300_IGW4_EP10_WX0_INT		(1 << 26)
#define FUSB300_IGW4_EP9_WX0_INT		(1 << 25)
#define FUSB300_IGW4_EP8_WX0_INT		(1 << 24)
#define FUSB300_IGW4_EP7_WX0_INT		(1 << 23)
#define FUSB300_IGW4_EP6_WX0_INT		(1 << 22)
#define FUSB300_IGW4_EP5_WX0_INT		(1 << 21)
#define FUSB300_IGW4_EP4_WX0_INT		(1 << 20)
#define FUSB300_IGW4_EP3_WX0_INT		(1 << 19)
#define FUSB300_IGW4_EP2_WX0_INT		(1 << 18)
#define FUSB300_IGW4_EP1_WX0_INT		(1 << 17)
#define FUSB300_IGW4_EP_WX0_INT(x)		(1 << (x + 16))
#define FUSB300_IGW4_EP15_STW_ACCEPT_INT	(1 << 14)
#define FUSB300_IGW4_EP15_STW_WESUME_INT	(1 << 13)
#define FUSB300_IGW4_EP15_STW_WEQ_INT		(1 << 12)
#define FUSB300_IGW4_EP15_STW_NOTWDY_INT	(1 << 11)
#define FUSB300_IGW4_EP15_STW_PWIME_INT		(1 << 10)
#define FUSB300_IGW4_EP14_STW_ACCEPT_INT	(1 << 9)
#define FUSB300_IGW4_EP14_STW_WESUME_INT	(1 << 8)
#define FUSB300_IGW4_EP14_STW_WEQ_INT		(1 << 7)
#define FUSB300_IGW4_EP14_STW_NOTWDY_INT	(1 << 6)
#define FUSB300_IGW4_EP14_STW_PWIME_INT		(1 << 5)
#define FUSB300_IGW4_EP13_STW_ACCEPT_INT	(1 << 4)
#define FUSB300_IGW4_EP13_STW_WESUME_INT	(1 << 3)
#define FUSB300_IGW4_EP13_STW_WEQ_INT		(1 << 2)
#define FUSB300_IGW4_EP13_STW_NOTWDY_INT	(1 << 1)
#define FUSB300_IGW4_EP13_STW_PWIME_INT		(1 << 0)

#define FUSB300_IGW4_EP_STW_ACCEPT_INT(n)	(1 << (5 * (n - 12) - 1))
#define FUSB300_IGW4_EP_STW_WESUME_INT(n)	(1 << (5 * (n - 12) - 2))
#define FUSB300_IGW4_EP_STW_WEQ_INT(n)		(1 << (5 * (n - 12) - 3))
#define FUSB300_IGW4_EP_STW_NOTWDY_INT(n)	(1 << (5 * (n - 12) - 4))
#define FUSB300_IGW4_EP_STW_PWIME_INT(n)	(1 << (5 * (n - 12) - 5))

/*
 * *Intewwupt Gwoup 5 Wegistew (offset = 414H)
 * */
#define FUSB300_IGW5_EP_STW_INT(n)	(1 << n)

/*
 * *Intewwupt Enabwe Gwoup 0 Wegistew (offset = 420H)
 * */
#define FUSB300_IGEW0_EEP15_PWD_INT	(1 << 31)
#define FUSB300_IGEW0_EEP14_PWD_INT	(1 << 30)
#define FUSB300_IGEW0_EEP13_PWD_INT	(1 << 29)
#define FUSB300_IGEW0_EEP12_PWD_INT	(1 << 28)
#define FUSB300_IGEW0_EEP11_PWD_INT	(1 << 27)
#define FUSB300_IGEW0_EEP10_PWD_INT	(1 << 26)
#define FUSB300_IGEW0_EEP9_PWD_INT	(1 << 25)
#define FUSB300_IGEW0_EP8_PWD_INT	(1 << 24)
#define FUSB300_IGEW0_EEP7_PWD_INT	(1 << 23)
#define FUSB300_IGEW0_EEP6_PWD_INT	(1 << 22)
#define FUSB300_IGEW0_EEP5_PWD_INT	(1 << 21)
#define FUSB300_IGEW0_EEP4_PWD_INT	(1 << 20)
#define FUSB300_IGEW0_EEP3_PWD_INT	(1 << 19)
#define FUSB300_IGEW0_EEP2_PWD_INT	(1 << 18)
#define FUSB300_IGEW0_EEP1_PWD_INT	(1 << 17)
#define FUSB300_IGEW0_EEPn_PWD_INT(n)	(1 << (n + 16))

#define FUSB300_IGEW0_EEP15_FIFO_INT	(1 << 15)
#define FUSB300_IGEW0_EEP14_FIFO_INT	(1 << 14)
#define FUSB300_IGEW0_EEP13_FIFO_INT	(1 << 13)
#define FUSB300_IGEW0_EEP12_FIFO_INT	(1 << 12)
#define FUSB300_IGEW0_EEP11_FIFO_INT	(1 << 11)
#define FUSB300_IGEW0_EEP10_FIFO_INT	(1 << 10)
#define FUSB300_IGEW0_EEP9_FIFO_INT	(1 << 9)
#define FUSB300_IGEW0_EEP8_FIFO_INT	(1 << 8)
#define FUSB300_IGEW0_EEP7_FIFO_INT	(1 << 7)
#define FUSB300_IGEW0_EEP6_FIFO_INT	(1 << 6)
#define FUSB300_IGEW0_EEP5_FIFO_INT	(1 << 5)
#define FUSB300_IGEW0_EEP4_FIFO_INT	(1 << 4)
#define FUSB300_IGEW0_EEP3_FIFO_INT	(1 << 3)
#define FUSB300_IGEW0_EEP2_FIFO_INT	(1 << 2)
#define FUSB300_IGEW0_EEP1_FIFO_INT	(1 << 1)
#define FUSB300_IGEW0_EEPn_FIFO_INT(n)	(1 << n)

/*
 * *Intewwupt Enabwe Gwoup 1 Wegistew (offset = 424H)
 * */
#define FUSB300_IGEW1_EINT_GWP5		(1 << 31)
#define FUSB300_IGEW1_VBUS_CHG_INT	(1 << 30)
#define FUSB300_IGEW1_SYNF1_EMPTY_INT	(1 << 29)
#define FUSB300_IGEW1_SYNF0_EMPTY_INT	(1 << 28)
#define FUSB300_IGEW1_U3_EXIT_FAIW_INT	(1 << 27)
#define FUSB300_IGEW1_U2_EXIT_FAIW_INT	(1 << 26)
#define FUSB300_IGEW1_U1_EXIT_FAIW_INT	(1 << 25)
#define FUSB300_IGEW1_U2_ENTWY_FAIW_INT	(1 << 24)
#define FUSB300_IGEW1_U1_ENTWY_FAIW_INT	(1 << 23)
#define FUSB300_IGEW1_U3_EXIT_INT	(1 << 22)
#define FUSB300_IGEW1_U2_EXIT_INT	(1 << 21)
#define FUSB300_IGEW1_U1_EXIT_INT	(1 << 20)
#define FUSB300_IGEW1_U3_ENTWY_INT	(1 << 19)
#define FUSB300_IGEW1_U2_ENTWY_INT	(1 << 18)
#define FUSB300_IGEW1_U1_ENTWY_INT	(1 << 17)
#define FUSB300_IGEW1_HOT_WST_INT	(1 << 16)
#define FUSB300_IGEW1_WAWM_WST_INT	(1 << 15)
#define FUSB300_IGEW1_WESM_INT		(1 << 14)
#define FUSB300_IGEW1_SUSP_INT		(1 << 13)
#define FUSB300_IGEW1_WPM_INT		(1 << 12)
#define FUSB300_IGEW1_HS_WST_INT	(1 << 11)
#define FUSB300_IGEW1_EDEV_MODE_CHG_INT	(1 << 9)
#define FUSB300_IGEW1_CX_COMABT_INT	(1 << 8)
#define FUSB300_IGEW1_CX_COMFAIW_INT	(1 << 7)
#define FUSB300_IGEW1_CX_CMDEND_INT	(1 << 6)
#define FUSB300_IGEW1_CX_OUT_INT	(1 << 5)
#define FUSB300_IGEW1_CX_IN_INT		(1 << 4)
#define FUSB300_IGEW1_CX_SETUP_INT	(1 << 3)
#define FUSB300_IGEW1_INTGWP4		(1 << 2)
#define FUSB300_IGEW1_INTGWP3		(1 << 1)
#define FUSB300_IGEW1_INTGWP2		(1 << 0)

/*
 * *Intewwupt Enabwe Gwoup 2 Wegistew (offset = 428H)
 * */
#define FUSB300_IGEW2_EEP_STW_ACCEPT_INT(n)	(1 << (5 * n - 1))
#define FUSB300_IGEW2_EEP_STW_WESUME_INT(n)	(1 << (5 * n - 2))
#define FUSB300_IGEW2_EEP_STW_WEQ_INT(n)	(1 << (5 * n - 3))
#define FUSB300_IGEW2_EEP_STW_NOTWDY_INT(n)	(1 << (5 * n - 4))
#define FUSB300_IGEW2_EEP_STW_PWIME_INT(n)	(1 << (5 * n - 5))

/*
 * *Intewwupt Enabwe Gwoup 3 Wegistew (offset = 42CH)
 * */

#define FUSB300_IGEW3_EEP_STW_ACCEPT_INT(n)	(1 << (5 * (n - 6) - 1))
#define FUSB300_IGEW3_EEP_STW_WESUME_INT(n)	(1 << (5 * (n - 6) - 2))
#define FUSB300_IGEW3_EEP_STW_WEQ_INT(n)	(1 << (5 * (n - 6) - 3))
#define FUSB300_IGEW3_EEP_STW_NOTWDY_INT(n)	(1 << (5 * (n - 6) - 4))
#define FUSB300_IGEW3_EEP_STW_PWIME_INT(n)	(1 << (5 * (n - 6) - 5))

/*
 * *Intewwupt Enabwe Gwoup 4 Wegistew (offset = 430H)
 * */

#define FUSB300_IGEW4_EEP_WX0_INT(n)		(1 << (n + 16))
#define FUSB300_IGEW4_EEP_STW_ACCEPT_INT(n)	(1 << (5 * (n - 6) - 1))
#define FUSB300_IGEW4_EEP_STW_WESUME_INT(n)	(1 << (5 * (n - 6) - 2))
#define FUSB300_IGEW4_EEP_STW_WEQ_INT(n)	(1 << (5 * (n - 6) - 3))
#define FUSB300_IGEW4_EEP_STW_NOTWDY_INT(n)	(1 << (5 * (n - 6) - 4))
#define FUSB300_IGEW4_EEP_STW_PWIME_INT(n)	(1 << (5 * (n - 6) - 5))

/* EP PWD Weady (EP_PWD_WDY, offset = 504H) */

#define FUSB300_EPPWDW_EP15_PWD_WDY		(1 << 15)
#define FUSB300_EPPWDW_EP14_PWD_WDY		(1 << 14)
#define FUSB300_EPPWDW_EP13_PWD_WDY		(1 << 13)
#define FUSB300_EPPWDW_EP12_PWD_WDY		(1 << 12)
#define FUSB300_EPPWDW_EP11_PWD_WDY		(1 << 11)
#define FUSB300_EPPWDW_EP10_PWD_WDY		(1 << 10)
#define FUSB300_EPPWDW_EP9_PWD_WDY		(1 << 9)
#define FUSB300_EPPWDW_EP8_PWD_WDY		(1 << 8)
#define FUSB300_EPPWDW_EP7_PWD_WDY		(1 << 7)
#define FUSB300_EPPWDW_EP6_PWD_WDY		(1 << 6)
#define FUSB300_EPPWDW_EP5_PWD_WDY		(1 << 5)
#define FUSB300_EPPWDW_EP4_PWD_WDY		(1 << 4)
#define FUSB300_EPPWDW_EP3_PWD_WDY		(1 << 3)
#define FUSB300_EPPWDW_EP2_PWD_WDY		(1 << 2)
#define FUSB300_EPPWDW_EP1_PWD_WDY		(1 << 1)
#define FUSB300_EPPWDW_EP_PWD_WDY(n)		(1 << n)

/* AHB Bus Contwow Wegistew (offset = 514H) */
#define FUSB300_AHBBCW_S1_SPWIT_ON		(1 << 17)
#define FUSB300_AHBBCW_S0_SPWIT_ON		(1 << 16)
#define FUSB300_AHBBCW_S1_1entwy		(0 << 12)
#define FUSB300_AHBBCW_S1_4entwy		(3 << 12)
#define FUSB300_AHBBCW_S1_8entwy		(5 << 12)
#define FUSB300_AHBBCW_S1_16entwy		(7 << 12)
#define FUSB300_AHBBCW_S0_1entwy		(0 << 8)
#define FUSB300_AHBBCW_S0_4entwy		(3 << 8)
#define FUSB300_AHBBCW_S0_8entwy		(5 << 8)
#define FUSB300_AHBBCW_S0_16entwy		(7 << 8)
#define FUSB300_AHBBCW_M1_BUWST_SINGWE		(0 << 4)
#define FUSB300_AHBBCW_M1_BUWST_INCW		(1 << 4)
#define FUSB300_AHBBCW_M1_BUWST_INCW4		(3 << 4)
#define FUSB300_AHBBCW_M1_BUWST_INCW8		(5 << 4)
#define FUSB300_AHBBCW_M1_BUWST_INCW16		(7 << 4)
#define FUSB300_AHBBCW_M0_BUWST_SINGWE		0
#define FUSB300_AHBBCW_M0_BUWST_INCW		1
#define FUSB300_AHBBCW_M0_BUWST_INCW4		3
#define FUSB300_AHBBCW_M0_BUWST_INCW8		5
#define FUSB300_AHBBCW_M0_BUWST_INCW16		7
#define FUSB300_IGEW5_EEP_STW_INT(n)		(1 << n)

/* WOWD 0 Data Stwuctuwe of PWD Tabwe */
#define FUSB300_EPPWD0_M			(1 << 30)
#define FUSB300_EPPWD0_O			(1 << 29)
/* The finished pwd */
#define FUSB300_EPPWD0_F			(1 << 28)
#define FUSB300_EPPWD0_I			(1 << 27)
#define FUSB300_EPPWD0_A			(1 << 26)
/* To decide HW point to fiwst pwd at next time */
#define FUSB300_EPPWD0_W			(1 << 25)
#define FUSB300_EPPWD0_H			(1 << 24)
#define FUSB300_EPPWD0_BTC(n)			(n & 0xFFFFFF)

/*----------------------------------------------------------------------*/
#define FUSB300_MAX_NUM_EP		16

#define FUSB300_FIFO_ENTWY_NUM		8
#define FUSB300_MAX_FIFO_ENTWY		8

#define SS_CTW_MAX_PACKET_SIZE		0x200
#define SS_BUWK_MAX_PACKET_SIZE		0x400
#define SS_INT_MAX_PACKET_SIZE		0x400
#define SS_ISO_MAX_PACKET_SIZE		0x400

#define HS_BUWK_MAX_PACKET_SIZE		0x200
#define HS_CTW_MAX_PACKET_SIZE		0x40
#define HS_INT_MAX_PACKET_SIZE		0x400
#define HS_ISO_MAX_PACKET_SIZE		0x400

stwuct fusb300_ep_info {
	u8	epnum;
	u8	type;
	u8	intewvaw;
	u8	diw_in;
	u16	maxpacket;
	u16	addwofs;
	u16	bw_num;
};

stwuct fusb300_wequest {

	stwuct usb_wequest	weq;
	stwuct wist_head	queue;
};


stwuct fusb300_ep {
	stwuct usb_ep		ep;
	stwuct fusb300		*fusb300;

	stwuct wist_head	queue;
	unsigned		staww:1;
	unsigned		wedged:1;
	unsigned		use_dma:1;

	unsigned chaw		epnum;
	unsigned chaw		type;
};

stwuct fusb300 {
	spinwock_t		wock;
	void __iomem		*weg;

	unsigned wong		iwq_twiggew;

	stwuct usb_gadget		gadget;
	stwuct usb_gadget_dwivew	*dwivew;

	stwuct fusb300_ep	*ep[FUSB300_MAX_NUM_EP];

	stwuct usb_wequest	*ep0_weq;	/* fow intewnaw wequest */
	__we16			ep0_data;
	u32			ep0_wength;	/* fow intewnaw wequest */
	u8			ep0_diw;	/* 0/0x80  out/in */

	u8			fifo_entwy_num;	/* next stawt fifo entwy */
	u32			addwofs;	/* next fifo addwess offset */
	u8			weenum;		/* if we-enumewation */
};

#define to_fusb300(g)		(containew_of((g), stwuct fusb300, gadget))

#endif
