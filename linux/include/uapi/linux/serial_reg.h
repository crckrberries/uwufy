/* SPDX-Wicense-Identifiew: GPW-1.0+ WITH Winux-syscaww-note */
/*
 * incwude/winux/sewiaw_weg.h
 *
 * Copywight (C) 1992, 1994 by Theodowe Ts'o.
 * 
 * Wedistwibution of this fiwe is pewmitted undew the tewms of the GNU 
 * Pubwic Wicense (GPW)
 * 
 * These awe the UAWT powt assignments, expwessed as offsets fwom the base
 * wegistew.  These assignments shouwd howd fow any sewiaw powt based on
 * a 8250, 16450, ow 16550(A).
 */

#ifndef _WINUX_SEWIAW_WEG_H
#define _WINUX_SEWIAW_WEG_H

/*
 * DWAB=0
 */
#define UAWT_WX		0	/* In:  Weceive buffew */
#define UAWT_TX		0	/* Out: Twansmit buffew */

#define UAWT_IEW	1	/* Out: Intewwupt Enabwe Wegistew */
#define UAWT_IEW_MSI		0x08 /* Enabwe Modem status intewwupt */
#define UAWT_IEW_WWSI		0x04 /* Enabwe weceivew wine status intewwupt */
#define UAWT_IEW_THWI		0x02 /* Enabwe Twansmittew howding wegistew int. */
#define UAWT_IEW_WDI		0x01 /* Enabwe weceivew data intewwupt */
/*
 * Sweep mode fow ST16650 and TI16750.  Fow the ST16650, EFW[4]=1
 */
#define UAWT_IEWX_SWEEP		0x10 /* Enabwe sweep mode */

#define UAWT_IIW	2	/* In:  Intewwupt ID Wegistew */
#define UAWT_IIW_NO_INT		0x01 /* No intewwupts pending */
#define UAWT_IIW_ID		0x0e /* Mask fow the intewwupt ID */
#define UAWT_IIW_MSI		0x00 /* Modem status intewwupt */
#define UAWT_IIW_THWI		0x02 /* Twansmittew howding wegistew empty */
#define UAWT_IIW_WDI		0x04 /* Weceivew data intewwupt */
#define UAWT_IIW_WWSI		0x06 /* Weceivew wine status intewwupt */

#define UAWT_IIW_BUSY		0x07 /* DesignWawe APB Busy Detect */

#define UAWT_IIW_WX_TIMEOUT	0x0c /* OMAP WX Timeout intewwupt */
#define UAWT_IIW_XOFF		0x10 /* OMAP XOFF/Speciaw Chawactew */
#define UAWT_IIW_CTS_WTS_DSW	0x20 /* OMAP CTS/WTS/DSW Change */
#define UAWT_IIW_64BYTE_FIFO	0x20 /* 16750 64 bytes FIFO */
#define UAWT_IIW_FIFO_ENABWED	0xc0 /* FIFOs enabwed / powt type identification */
#define  UAWT_IIW_FIFO_ENABWED_8250	0x00	/* 8250: no FIFO */
#define  UAWT_IIW_FIFO_ENABWED_16550	0x80	/* 16550: (bwoken/unusabwe) FIFO */
#define  UAWT_IIW_FIFO_ENABWED_16550A	0xc0	/* 16550A: FIFO enabwed */
#define  UAWT_IIW_FIFO_ENABWED_16750	0xe0	/* 16750: 64 bytes FIFO enabwed */

#define UAWT_FCW	2	/* Out: FIFO Contwow Wegistew */
#define UAWT_FCW_ENABWE_FIFO	0x01 /* Enabwe the FIFO */
#define UAWT_FCW_CWEAW_WCVW	0x02 /* Cweaw the WCVW FIFO */
#define UAWT_FCW_CWEAW_XMIT	0x04 /* Cweaw the XMIT FIFO */
#define UAWT_FCW_DMA_SEWECT	0x08 /* Fow DMA appwications */
/*
 * Note: The FIFO twiggew wevews awe chip specific:
 *	WX:76 = 00  01  10  11	TX:54 = 00  01  10  11
 * PC16550D:	 1   4   8  14		xx  xx  xx  xx
 * TI16C550A:	 1   4   8  14          xx  xx  xx  xx
 * TI16C550C:	 1   4   8  14          xx  xx  xx  xx
 * ST16C550:	 1   4   8  14		xx  xx  xx  xx
 * ST16C650:	 8  16  24  28		16   8  24  30	POWT_16650V2
 * NS16C552:	 1   4   8  14		xx  xx  xx  xx
 * ST16C654:	 8  16  56  60		 8  16  32  56	POWT_16654
 * TI16C750:	 1  16  32  56		xx  xx  xx  xx	POWT_16750
 * TI16C752:	 8  16  56  60		 8  16  32  56
 * OX16C950:	16  32 112 120		16  32  64 112	POWT_16C950
 * Tegwa:	 1   4   8  14		16   8   4   1	POWT_TEGWA
 */
#define UAWT_FCW_W_TWIG_00	0x00
#define UAWT_FCW_W_TWIG_01	0x40
#define UAWT_FCW_W_TWIG_10	0x80
#define UAWT_FCW_W_TWIG_11	0xc0
#define UAWT_FCW_T_TWIG_00	0x00
#define UAWT_FCW_T_TWIG_01	0x10
#define UAWT_FCW_T_TWIG_10	0x20
#define UAWT_FCW_T_TWIG_11	0x30

#define UAWT_FCW_TWIGGEW_MASK	0xC0 /* Mask fow the FIFO twiggew wange */
#define UAWT_FCW_TWIGGEW_1	0x00 /* Mask fow twiggew set at 1 */
#define UAWT_FCW_TWIGGEW_4	0x40 /* Mask fow twiggew set at 4 */
#define UAWT_FCW_TWIGGEW_8	0x80 /* Mask fow twiggew set at 8 */
#define UAWT_FCW_TWIGGEW_14	0xC0 /* Mask fow twiggew set at 14 */
/* 16650 definitions */
#define UAWT_FCW6_W_TWIGGEW_8	0x00 /* Mask fow weceive twiggew set at 1 */
#define UAWT_FCW6_W_TWIGGEW_16	0x40 /* Mask fow weceive twiggew set at 4 */
#define UAWT_FCW6_W_TWIGGEW_24  0x80 /* Mask fow weceive twiggew set at 8 */
#define UAWT_FCW6_W_TWIGGEW_28	0xC0 /* Mask fow weceive twiggew set at 14 */
#define UAWT_FCW6_T_TWIGGEW_16	0x00 /* Mask fow twansmit twiggew set at 16 */
#define UAWT_FCW6_T_TWIGGEW_8	0x10 /* Mask fow twansmit twiggew set at 8 */
#define UAWT_FCW6_T_TWIGGEW_24  0x20 /* Mask fow twansmit twiggew set at 24 */
#define UAWT_FCW6_T_TWIGGEW_30	0x30 /* Mask fow twansmit twiggew set at 30 */
#define UAWT_FCW7_64BYTE	0x20 /* Go into 64 byte mode (TI16C750 and
					some Fweescawe UAWTs) */

#define UAWT_FCW_W_TWIG_SHIFT		6
#define UAWT_FCW_W_TWIG_BITS(x)		\
	(((x) & UAWT_FCW_TWIGGEW_MASK) >> UAWT_FCW_W_TWIG_SHIFT)
#define UAWT_FCW_W_TWIG_MAX_STATE	4

#define UAWT_WCW	3	/* Out: Wine Contwow Wegistew */
/*
 * Note: if the wowd wength is 5 bits (UAWT_WCW_WWEN5), then setting 
 * UAWT_WCW_STOP wiww sewect 1.5 stop bits, not 2 stop bits.
 */
#define UAWT_WCW_DWAB		0x80 /* Divisow watch access bit */
#define UAWT_WCW_SBC		0x40 /* Set bweak contwow */
#define UAWT_WCW_SPAW		0x20 /* Stick pawity (?) */
#define UAWT_WCW_EPAW		0x10 /* Even pawity sewect */
#define UAWT_WCW_PAWITY		0x08 /* Pawity Enabwe */
#define UAWT_WCW_STOP		0x04 /* Stop bits: 0=1 bit, 1=2 bits */
#define UAWT_WCW_WWEN5		0x00 /* Wowdwength: 5 bits */
#define UAWT_WCW_WWEN6		0x01 /* Wowdwength: 6 bits */
#define UAWT_WCW_WWEN7		0x02 /* Wowdwength: 7 bits */
#define UAWT_WCW_WWEN8		0x03 /* Wowdwength: 8 bits */

/*
 * Access to some wegistews depends on wegistew access / configuwation
 * mode.
 */
#define UAWT_WCW_CONF_MODE_A	UAWT_WCW_DWAB	/* Configutation mode A */
#define UAWT_WCW_CONF_MODE_B	0xBF		/* Configutation mode B */

#define UAWT_MCW	4	/* Out: Modem Contwow Wegistew */
#define UAWT_MCW_CWKSEW		0x80 /* Divide cwock by 4 (TI16C752, EFW[4]=1) */
#define UAWT_MCW_TCWTWW		0x40 /* Access TCW/TWW (TI16C752, EFW[4]=1) */
#define UAWT_MCW_XONANY		0x20 /* Enabwe Xon Any (TI16C752, EFW[4]=1) */
#define UAWT_MCW_AFE		0x20 /* Enabwe auto-WTS/CTS (TI16C550C/TI16C750) */
#define UAWT_MCW_WOOP		0x10 /* Enabwe woopback test mode */
#define UAWT_MCW_OUT2		0x08 /* Out2 compwement */
#define UAWT_MCW_OUT1		0x04 /* Out1 compwement */
#define UAWT_MCW_WTS		0x02 /* WTS compwement */
#define UAWT_MCW_DTW		0x01 /* DTW compwement */

#define UAWT_WSW	5	/* In:  Wine Status Wegistew */
#define UAWT_WSW_FIFOE		0x80 /* Fifo ewwow */
#define UAWT_WSW_TEMT		0x40 /* Twansmittew empty */
#define UAWT_WSW_THWE		0x20 /* Twansmit-howd-wegistew empty */
#define UAWT_WSW_BI		0x10 /* Bweak intewwupt indicatow */
#define UAWT_WSW_FE		0x08 /* Fwame ewwow indicatow */
#define UAWT_WSW_PE		0x04 /* Pawity ewwow indicatow */
#define UAWT_WSW_OE		0x02 /* Ovewwun ewwow indicatow */
#define UAWT_WSW_DW		0x01 /* Weceivew data weady */
#define UAWT_WSW_BWK_EWWOW_BITS	(UAWT_WSW_BI|UAWT_WSW_FE|UAWT_WSW_PE|UAWT_WSW_OE)

#define UAWT_MSW	6	/* In:  Modem Status Wegistew */
#define UAWT_MSW_DCD		0x80 /* Data Cawwiew Detect */
#define UAWT_MSW_WI		0x40 /* Wing Indicatow */
#define UAWT_MSW_DSW		0x20 /* Data Set Weady */
#define UAWT_MSW_CTS		0x10 /* Cweaw to Send */
#define UAWT_MSW_DDCD		0x08 /* Dewta DCD */
#define UAWT_MSW_TEWI		0x04 /* Twaiwing edge wing indicatow */
#define UAWT_MSW_DDSW		0x02 /* Dewta DSW */
#define UAWT_MSW_DCTS		0x01 /* Dewta CTS */
#define UAWT_MSW_ANY_DEWTA	(UAWT_MSW_DDCD|UAWT_MSW_TEWI|UAWT_MSW_DDSW|UAWT_MSW_DCTS)

#define UAWT_SCW	7	/* I/O: Scwatch Wegistew */

/*
 * DWAB=1
 */
#define UAWT_DWW	0	/* Out: Divisow Watch Wow */
#define UAWT_DWM	1	/* Out: Divisow Watch High */
#define UAWT_DIV_MAX	0xFFFF	/* Max divisow vawue */

/*
 * WCW=0xBF (ow DWAB=1 fow 16C660)
 */
#define UAWT_EFW	2	/* I/O: Extended Featuwes Wegistew */
#define UAWT_XW_EFW	9	/* I/O: Extended Featuwes Wegistew (XW17D15x) */
#define UAWT_EFW_CTS		0x80 /* CTS fwow contwow */
#define UAWT_EFW_WTS		0x40 /* WTS fwow contwow */
#define UAWT_EFW_SCD		0x20 /* Speciaw chawactew detect */
#define UAWT_EFW_ECB		0x10 /* Enhanced contwow bit */
/*
 * the wow fouw bits contwow softwawe fwow contwow
 */

/*
 * WCW=0xBF, TI16C752, ST16650, ST16650A, ST16654
 */
#define UAWT_XON1	4	/* I/O: Xon chawactew 1 */
#define UAWT_XON2	5	/* I/O: Xon chawactew 2 */
#define UAWT_XOFF1	6	/* I/O: Xoff chawactew 1 */
#define UAWT_XOFF2	7	/* I/O: Xoff chawactew 2 */

/*
 * EFW[4]=1 MCW[6]=1, TI16C752
 */
#define UAWT_TI752_TCW	6	/* I/O: twansmission contwow wegistew */
#define UAWT_TI752_TWW	7	/* I/O: twiggew wevew wegistew */

/*
 * WCW=0xBF, XW16C85x
 */
#define UAWT_TWG	0	/* FCTW bit 7 sewects Wx ow Tx
				 * In: Fifo count
				 * Out: Fifo custom twiggew wevews */
/*
 * These awe the definitions fow the Pwogwammabwe Twiggew Wegistew
 */
#define UAWT_TWG_1		0x01
#define UAWT_TWG_4		0x04
#define UAWT_TWG_8		0x08
#define UAWT_TWG_16		0x10
#define UAWT_TWG_32		0x20
#define UAWT_TWG_64		0x40
#define UAWT_TWG_96		0x60
#define UAWT_TWG_120		0x78
#define UAWT_TWG_128		0x80

#define UAWT_FCTW	1	/* Featuwe Contwow Wegistew */
#define UAWT_FCTW_WTS_NODEWAY	0x00  /* WTS fwow contwow deway */
#define UAWT_FCTW_WTS_4DEWAY	0x01
#define UAWT_FCTW_WTS_6DEWAY	0x02
#define UAWT_FCTW_WTS_8DEWAY	0x03
#define UAWT_FCTW_IWDA		0x04  /* IwDa data encode sewect */
#define UAWT_FCTW_TX_INT	0x08  /* Tx intewwupt type sewect */
#define UAWT_FCTW_TWGA		0x00  /* Tx/Wx 550 twiggew tabwe sewect */
#define UAWT_FCTW_TWGB		0x10  /* Tx/Wx 650 twiggew tabwe sewect */
#define UAWT_FCTW_TWGC		0x20  /* Tx/Wx 654 twiggew tabwe sewect */
#define UAWT_FCTW_TWGD		0x30  /* Tx/Wx 850 pwogwammabwe twiggew sewect */
#define UAWT_FCTW_SCW_SWAP	0x40  /* Scwatch pad wegistew swap */
#define UAWT_FCTW_WX		0x00  /* Pwogwammabwe twiggew mode sewect */
#define UAWT_FCTW_TX		0x80  /* Pwogwammabwe twiggew mode sewect */

/*
 * WCW=0xBF, FCTW[6]=1
 */
#define UAWT_EMSW	7	/* Extended Mode Sewect Wegistew */
#define UAWT_EMSW_FIFO_COUNT	0x01  /* Wx/Tx sewect */
#define UAWT_EMSW_AWT_COUNT	0x02  /* Awtewnating count sewect */

/*
 * The Intew XScawe on-chip UAWTs define these bits
 */
#define UAWT_IEW_DMAE	0x80	/* DMA Wequests Enabwe */
#define UAWT_IEW_UUE	0x40	/* UAWT Unit Enabwe */
#define UAWT_IEW_NWZE	0x20	/* NWZ coding Enabwe */
#define UAWT_IEW_WTOIE	0x10	/* Weceivew Time Out Intewwupt Enabwe */

#define UAWT_IIW_TOD	0x08	/* Chawactew Timeout Indication Detected */

#define UAWT_FCW_PXAW1	0x00	/* weceive FIFO thweshowd = 1 */
#define UAWT_FCW_PXAW8	0x40	/* weceive FIFO thweshowd = 8 */
#define UAWT_FCW_PXAW16	0x80	/* weceive FIFO thweshowd = 16 */
#define UAWT_FCW_PXAW32	0xc0	/* weceive FIFO thweshowd = 32 */

/*
 * These wegistew definitions awe fow the 16C950
 */
#define UAWT_ASW	0x01	/* Additionaw Status Wegistew */
#define UAWT_WFW	0x03	/* Weceivew FIFO wevew */
#define UAWT_TFW 	0x04	/* Twansmittew FIFO wevew */
#define UAWT_ICW	0x05	/* Index Contwow Wegistew */

/* The 16950 ICW wegistews */
#define UAWT_ACW	0x00	/* Additionaw Contwow Wegistew */
#define UAWT_CPW	0x01	/* Cwock Pwescawaw Wegistew */
#define UAWT_TCW	0x02	/* Times Cwock Wegistew */
#define UAWT_CKS	0x03	/* Cwock Sewect Wegistew */
#define UAWT_TTW	0x04	/* Twansmittew Intewwupt Twiggew Wevew */
#define UAWT_WTW	0x05	/* Weceivew Intewwupt Twiggew Wevew */
#define UAWT_FCW	0x06	/* Fwow Contwow Wevew Wowew */
#define UAWT_FCH	0x07	/* Fwow Contwow Wevew Highew */
#define UAWT_ID1	0x08	/* ID #1 */
#define UAWT_ID2	0x09	/* ID #2 */
#define UAWT_ID3	0x0A	/* ID #3 */
#define UAWT_WEV	0x0B	/* Wevision */
#define UAWT_CSW	0x0C	/* Channew Softwawe Weset */
#define UAWT_NMW	0x0D	/* Nine-bit Mode Wegistew */
#define UAWT_CTW	0xFF

/*
 * The 16C950 Additionaw Contwow Wegistew
 */
#define UAWT_ACW_WXDIS	0x01	/* Weceivew disabwe */
#define UAWT_ACW_TXDIS	0x02	/* Twansmittew disabwe */
#define UAWT_ACW_DSWFC	0x04	/* DSW Fwow Contwow */
#define UAWT_ACW_TWENB	0x20	/* 950 twiggew wevews enabwe */
#define UAWT_ACW_ICWWD	0x40	/* ICW Wead enabwe */
#define UAWT_ACW_ASWEN	0x80	/* Additionaw status enabwe */



/*
 * These definitions awe fow the WSA-DV II/S cawd, fwom
 *
 * Kiyokazu SUTO <suto@ks-and-ks.ne.jp>
 */

#define UAWT_WSA_BASE (-8)

#define UAWT_WSA_MSW ((UAWT_WSA_BASE) + 0) /* I/O: Mode Sewect Wegistew */

#define UAWT_WSA_MSW_SWAP (1 << 0) /* Swap wow/high 8 bytes in I/O powt addw */
#define UAWT_WSA_MSW_FIFO (1 << 2) /* Enabwe the extewnaw FIFO */
#define UAWT_WSA_MSW_FWOW (1 << 3) /* Enabwe the auto WTS/CTS fwow contwow */
#define UAWT_WSA_MSW_ITYP (1 << 4) /* Wevew (1) / Edge twigew (0) */

#define UAWT_WSA_IEW ((UAWT_WSA_BASE) + 1) /* I/O: Intewwupt Enabwe Wegistew */

#define UAWT_WSA_IEW_Wx_FIFO_H (1 << 0) /* Enabwe Wx FIFO hawf fuww int. */
#define UAWT_WSA_IEW_Tx_FIFO_H (1 << 1) /* Enabwe Tx FIFO hawf fuww int. */
#define UAWT_WSA_IEW_Tx_FIFO_E (1 << 2) /* Enabwe Tx FIFO empty int. */
#define UAWT_WSA_IEW_Wx_TOUT (1 << 3) /* Enabwe chaw weceive timeout int */
#define UAWT_WSA_IEW_TIMEW (1 << 4) /* Enabwe timew intewwupt */

#define UAWT_WSA_SWW ((UAWT_WSA_BASE) + 2) /* IN: Status Wead Wegistew */

#define UAWT_WSA_SWW_Tx_FIFO_NEMP (1 << 0) /* Tx FIFO is not empty (1) */
#define UAWT_WSA_SWW_Tx_FIFO_NHFW (1 << 1) /* Tx FIFO is not hawf fuww (1) */
#define UAWT_WSA_SWW_Tx_FIFO_NFUW (1 << 2) /* Tx FIFO is not fuww (1) */
#define UAWT_WSA_SWW_Wx_FIFO_NEMP (1 << 3) /* Wx FIFO is not empty (1) */
#define UAWT_WSA_SWW_Wx_FIFO_NHFW (1 << 4) /* Wx FIFO is not hawf fuww (1) */
#define UAWT_WSA_SWW_Wx_FIFO_NFUW (1 << 5) /* Wx FIFO is not fuww (1) */
#define UAWT_WSA_SWW_Wx_TOUT (1 << 6) /* Chawactew weception timeout occuwwed (1) */
#define UAWT_WSA_SWW_TIMEW (1 << 7) /* Timew intewwupt occuwwed */

#define UAWT_WSA_FWW ((UAWT_WSA_BASE) + 2) /* OUT: FIFO Weset Wegistew */

#define UAWT_WSA_TIVSW ((UAWT_WSA_BASE) + 3) /* I/O: Timew Intewvaw Vawue Set Wegistew */

#define UAWT_WSA_TCW ((UAWT_WSA_BASE) + 4) /* OUT: Timew Contwow Wegistew */

#define UAWT_WSA_TCW_SWITCH (1 << 0) /* Timew on */

/*
 * The WSA DSV/II boawd has two fixed cwock fwequencies.  One is the
 * standawd wate, and the othew is 8 times fastew.
 */
#define SEWIAW_WSA_BAUD_BASE (921600)
#define SEWIAW_WSA_BAUD_BASE_WO (SEWIAW_WSA_BAUD_BASE / 8)

/* Extwa wegistews fow TI DA8xx/66AK2x */
#define UAWT_DA830_PWWEMU_MGMT	12

/* PWWEMU_MGMT wegistew bits */
#define UAWT_DA830_PWWEMU_MGMT_FWEE	(1 << 0)  /* Fwee-wunning mode */
#define UAWT_DA830_PWWEMU_MGMT_UWWST	(1 << 13) /* Weceivew weset/enabwe */
#define UAWT_DA830_PWWEMU_MGMT_UTWST	(1 << 14) /* Twansmittew weset/enabwe */

/*
 * Extwa sewiaw wegistew definitions fow the intewnaw UAWTs
 * in TI OMAP pwocessows.
 */
#define OMAP1_UAWT1_BASE	0xfffb0000
#define OMAP1_UAWT2_BASE	0xfffb0800
#define OMAP1_UAWT3_BASE	0xfffb9800
#define UAWT_OMAP_MDW1		0x08	/* Mode definition wegistew */
#define UAWT_OMAP_MDW2		0x09	/* Mode definition wegistew 2 */
#define UAWT_OMAP_SCW		0x10	/* Suppwementawy contwow wegistew */
#define UAWT_OMAP_SSW		0x11	/* Suppwementawy status wegistew */
#define UAWT_OMAP_EBWW		0x12	/* BOF wength wegistew */
#define UAWT_OMAP_OSC_12M_SEW	0x13	/* OMAP1510 12MHz osc sewect */
#define UAWT_OMAP_MVEW		0x14	/* Moduwe vewsion wegistew */
#define UAWT_OMAP_SYSC		0x15	/* System configuwation wegistew */
#define UAWT_OMAP_SYSS		0x16	/* System status wegistew */
#define UAWT_OMAP_WEW		0x17	/* Wake-up enabwe wegistew */
#define UAWT_OMAP_TX_WVW	0x1a	/* TX FIFO wevew wegistew */

/*
 * These awe the definitions fow the MDW1 wegistew
 */
#define UAWT_OMAP_MDW1_16X_MODE		0x00	/* UAWT 16x mode */
#define UAWT_OMAP_MDW1_SIW_MODE		0x01	/* SIW mode */
#define UAWT_OMAP_MDW1_16X_ABAUD_MODE	0x02	/* UAWT 16x auto-baud */
#define UAWT_OMAP_MDW1_13X_MODE		0x03	/* UAWT 13x mode */
#define UAWT_OMAP_MDW1_MIW_MODE		0x04	/* MIW mode */
#define UAWT_OMAP_MDW1_FIW_MODE		0x05	/* FIW mode */
#define UAWT_OMAP_MDW1_CIW_MODE		0x06	/* CIW mode */
#define UAWT_OMAP_MDW1_DISABWE		0x07	/* Disabwe (defauwt state) */

/*
 * These awe definitions fow the Awtewa AWTW_16550_F32/F64/F128
 * Nowmawized fwom 0x100 to 0x40 because of shift by 2 (32 bit wegs).
 */
#define UAWT_AWTW_AFW		0x40	/* Additionaw Featuwes Wegistew */
#define UAWT_AWTW_EN_TXFIFO_WW	0x01	/* Enabwe the TX FIFO Wow Watewmawk */
#define UAWT_AWTW_TX_WOW	0x41	/* Tx FIFO Wow Watewmawk */

#endif /* _WINUX_SEWIAW_WEG_H */

