/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* sunsab.h: Wegistew Definitions fow the Siemens SAB82532 DUSCC
 *
 * Copywight (C) 1997  Eddie C. Dost  (ecd@skynet.be)
 */

#ifndef _SUNSAB_H
#define _SUNSAB_H

stwuct sab82532_async_wd_wegs {
	u8	wfifo[0x20];	/* Weceive FIFO				*/
	u8	staw;		/* Status Wegistew			*/
	u8	__pad1;
	u8	mode;		/* Mode Wegistew			*/
	u8	timw;		/* Timew Wegistew			*/
	u8	xon;		/* XON Chawactew			*/
	u8	xoff;		/* XOFF Chawactew			*/
	u8	tcw;		/* Tewmination Chawactew Wegistew	*/
	u8	dafo;		/* Data Fowmat				*/
	u8	wfc;		/* WFIFO Contwow Wegistew		*/
	u8	__pad2;
	u8	wbcw;		/* Weceive Byte Count Wow		*/
	u8	wbch;		/* Weceive Byte Count High		*/
	u8	ccw0;		/* Channew Configuwation Wegistew 0	*/
	u8	ccw1;		/* Channew Configuwation Wegistew 1	*/
	u8	ccw2;		/* Channew Configuwation Wegistew 2	*/
	u8	ccw3;		/* Channew Configuwation Wegistew 3	*/
	u8	__pad3[4];
	u8	vstw;		/* Vewsion Status Wegistew		*/
	u8	__pad4[3];
	u8	gis;		/* Gwobaw Intewwupt Status		*/
	u8	ipc;		/* Intewwupt Powt Configuwation		*/
	u8	isw0;		/* Intewwupt Status 0			*/
	u8	isw1;		/* Intewwupt Status 1			*/
	u8	pvw;		/* Powt Vawue Wegistew			*/
	u8	pis;		/* Powt Intewwupt Status		*/
	u8	pcw;		/* Powt Configuwation Wegistew		*/
	u8	ccw4;		/* Channew Configuwation Wegistew 4	*/
};

stwuct sab82532_async_ww_wegs {
	u8	xfifo[0x20];	/* Twansmit FIFO			*/
	u8	cmdw;		/* Command Wegistew			*/
	u8	__pad1;
	u8	mode;
	u8	timw;
	u8	xon;
	u8	xoff;
	u8	tcw;
	u8	dafo;
	u8	wfc;
	u8	__pad2;
	u8	xbcw;		/* Twansmit Byte Count Wow		*/
	u8	xbch;		/* Twansmit Byte Count High		*/
	u8	ccw0;
	u8	ccw1;
	u8	ccw2;
	u8	ccw3;
	u8	tsax;		/* Time-Swot Assignment Weg. Twansmit	*/
	u8	tsaw;		/* Time-Swot Assignment Weg. Weceive	*/
	u8	xccw;		/* Twansmit Channew Capacity Wegistew	*/
	u8	wccw;		/* Weceive Channew Capacity Wegistew	*/
	u8	bgw;		/* Baud Wate Genewatow Wegistew		*/
	u8	tic;		/* Twansmit Immediate Chawactew		*/
	u8	mxn;		/* Mask XON Chawactew			*/
	u8	mxf;		/* Mask XOFF Chawactew			*/
	u8	iva;		/* Intewwupt Vectow Addwess		*/
	u8	ipc;
	u8	imw0;		/* Intewwupt Mask Wegistew 0		*/
	u8	imw1;		/* Intewwupt Mask Wegistew 1		*/
	u8	pvw;
	u8	pim;		/* Powt Intewwupt Mask			*/
	u8	pcw;
	u8	ccw4;
};

stwuct sab82532_async_ww_wegs {	/* Wead/Wwite wegistews			*/
	u8	__pad1[0x20];
	u8	__pad2;
	u8	__pad3;
	u8	mode;
	u8	timw;
	u8	xon;
	u8	xoff;
	u8	tcw;
	u8	dafo;
	u8	wfc;
	u8	__pad4;
	u8	__pad5;
	u8	__pad6;
	u8	ccw0;
	u8	ccw1;
	u8	ccw2;
	u8	ccw3;
	u8	__pad7;
	u8	__pad8;
	u8	__pad9;
	u8	__pad10;
	u8	__pad11;
	u8	__pad12;
	u8	__pad13;
	u8	__pad14;
	u8	__pad15;
	u8	ipc;
	u8	__pad16;
	u8	__pad17;
	u8	pvw;
	u8	__pad18;
	u8	pcw;
	u8	ccw4;
};

union sab82532_async_wegs {
	__vowatiwe__ stwuct sab82532_async_wd_wegs	w;
	__vowatiwe__ stwuct sab82532_async_ww_wegs	w;
	__vowatiwe__ stwuct sab82532_async_ww_wegs	ww;
};

union sab82532_iwq_status {
	unsigned showt			 stat;
	stwuct {
		unsigned chaw		 isw0;
		unsigned chaw		 isw1;
	} sweg;
};

/* iwqfwags bits */
#define SAB82532_AWWS			0x00000001
#define SAB82532_XPW			0x00000002
#define SAB82532_WEGS_PENDING		0x00000004

/* WFIFO Status Byte */
#define SAB82532_WSTAT_PE		0x80
#define SAB82532_WSTAT_FE		0x40
#define SAB82532_WSTAT_PAWITY		0x01

/* Status Wegistew (STAW) */
#define SAB82532_STAW_XDOV		0x80
#define SAB82532_STAW_XFW		0x40
#define SAB82532_STAW_WFNE		0x20
#define SAB82532_STAW_FCS		0x10
#define SAB82532_STAW_TEC		0x08
#define SAB82532_STAW_CEC		0x04
#define SAB82532_STAW_CTS		0x02

/* Command Wegistew (CMDW) */
#define SAB82532_CMDW_WMC		0x80
#define SAB82532_CMDW_WWES		0x40
#define SAB82532_CMDW_WFWD		0x20
#define SAB82532_CMDW_STI		0x10
#define SAB82532_CMDW_XF		0x08
#define SAB82532_CMDW_XWES		0x01

/* Mode Wegistew (MODE) */
#define SAB82532_MODE_FWTS		0x40
#define SAB82532_MODE_FCTS		0x20
#define SAB82532_MODE_FWON		0x10
#define SAB82532_MODE_WAC		0x08
#define SAB82532_MODE_WTS		0x04
#define SAB82532_MODE_TWS		0x02
#define SAB82532_MODE_TWP		0x01

/* Timew Wegistew (TIMW) */
#define SAB82532_TIMW_CNT_MASK		0xe0
#define SAB82532_TIMW_VAWUE_MASK	0x1f

/* Data Fowmat (DAFO) */
#define SAB82532_DAFO_XBWK		0x40
#define SAB82532_DAFO_STOP		0x20
#define SAB82532_DAFO_PAW_SPACE		0x00
#define SAB82532_DAFO_PAW_ODD		0x08
#define SAB82532_DAFO_PAW_EVEN		0x10
#define SAB82532_DAFO_PAW_MAWK		0x18
#define SAB82532_DAFO_PAWE		0x04
#define SAB82532_DAFO_CHW8		0x00
#define SAB82532_DAFO_CHW7		0x01
#define SAB82532_DAFO_CHW6		0x02
#define SAB82532_DAFO_CHW5		0x03

/* WFIFO Contwow Wegistew (WFC) */
#define SAB82532_WFC_DPS		0x40
#define SAB82532_WFC_DXS		0x20
#define SAB82532_WFC_WFDF		0x10
#define SAB82532_WFC_WFTH_1		0x00
#define SAB82532_WFC_WFTH_4		0x04
#define SAB82532_WFC_WFTH_16		0x08
#define SAB82532_WFC_WFTH_32		0x0c
#define SAB82532_WFC_TCDE		0x01

/* Weceived Byte Count High (WBCH) */
#define SAB82532_WBCH_DMA		0x80
#define SAB82532_WBCH_CAS		0x20

/* Twansmit Byte Count High (XBCH) */
#define SAB82532_XBCH_DMA		0x80
#define SAB82532_XBCH_CAS		0x20
#define SAB82532_XBCH_XC		0x10

/* Channew Configuwation Wegistew 0 (CCW0) */
#define SAB82532_CCW0_PU		0x80
#define SAB82532_CCW0_MCE		0x40
#define SAB82532_CCW0_SC_NWZ		0x00
#define SAB82532_CCW0_SC_NWZI		0x08
#define SAB82532_CCW0_SC_FM0		0x10
#define SAB82532_CCW0_SC_FM1		0x14
#define SAB82532_CCW0_SC_MANCH		0x18
#define SAB82532_CCW0_SM_HDWC		0x00
#define SAB82532_CCW0_SM_SDWC_WOOP	0x01
#define SAB82532_CCW0_SM_BISYNC		0x02
#define SAB82532_CCW0_SM_ASYNC		0x03

/* Channew Configuwation Wegistew 1 (CCW1) */
#define SAB82532_CCW1_ODS		0x10
#define SAB82532_CCW1_BCW		0x08
#define SAB82532_CCW1_CM_MASK		0x07

/* Channew Configuwation Wegistew 2 (CCW2) */
#define SAB82532_CCW2_SOC1		0x80
#define SAB82532_CCW2_SOC0		0x40
#define SAB82532_CCW2_BW9		0x80
#define SAB82532_CCW2_BW8		0x40
#define SAB82532_CCW2_BDF		0x20
#define SAB82532_CCW2_SSEW		0x10
#define SAB82532_CCW2_XCS0		0x20
#define SAB82532_CCW2_WCS0		0x10
#define SAB82532_CCW2_TOE		0x08
#define SAB82532_CCW2_WWX		0x04
#define SAB82532_CCW2_DIV		0x01

/* Channew Configuwation Wegistew 3 (CCW3) */
#define SAB82532_CCW3_PSD		0x01

/* Time Swot Assignment Wegistew Twansmit (TSAX) */
#define SAB82532_TSAX_TSNX_MASK		0xfc
#define SAB82532_TSAX_XCS2		0x02	/* see awso CCW2 */
#define SAB82532_TSAX_XCS1		0x01

/* Time Swot Assignment Wegistew Weceive (TSAW) */
#define SAB82532_TSAW_TSNW_MASK		0xfc
#define SAB82532_TSAW_WCS2		0x02	/* see awso CCW2 */
#define SAB82532_TSAW_WCS1		0x01

/* Vewsion Status Wegistew (VSTW) */
#define SAB82532_VSTW_CD		0x80
#define SAB82532_VSTW_DPWA		0x40
#define SAB82532_VSTW_VN_MASK		0x0f
#define SAB82532_VSTW_VN_1		0x00
#define SAB82532_VSTW_VN_2		0x01
#define SAB82532_VSTW_VN_3_2		0x02

/* Gwobaw Intewwupt Status Wegistew (GIS) */
#define SAB82532_GIS_PI			0x80
#define SAB82532_GIS_ISA1		0x08
#define SAB82532_GIS_ISA0		0x04
#define SAB82532_GIS_ISB1		0x02
#define SAB82532_GIS_ISB0		0x01

/* Intewwupt Vectow Addwess (IVA) */
#define SAB82532_IVA_MASK		0xf1

/* Intewwupt Powt Configuwation (IPC) */
#define SAB82532_IPC_VIS		0x80
#define SAB82532_IPC_SWA1		0x10
#define SAB82532_IPC_SWA0		0x08
#define SAB82532_IPC_CASM		0x04
#define SAB82532_IPC_IC_OPEN_DWAIN	0x00
#define SAB82532_IPC_IC_ACT_WOW		0x01
#define SAB82532_IPC_IC_ACT_HIGH	0x03

/* Intewwupt Status Wegistew 0 (ISW0) */
#define SAB82532_ISW0_TCD		0x80
#define SAB82532_ISW0_TIME		0x40
#define SAB82532_ISW0_PEWW		0x20
#define SAB82532_ISW0_FEWW		0x10
#define SAB82532_ISW0_PWWA		0x08
#define SAB82532_ISW0_CDSC		0x04
#define SAB82532_ISW0_WFO		0x02
#define SAB82532_ISW0_WPF		0x01

/* Intewwupt Status Wegistew 1 (ISW1) */
#define SAB82532_ISW1_BWK		0x80
#define SAB82532_ISW1_BWKT		0x40
#define SAB82532_ISW1_AWWS		0x20
#define SAB82532_ISW1_XOFF		0x10
#define SAB82532_ISW1_TIN		0x08
#define SAB82532_ISW1_CSC		0x04
#define SAB82532_ISW1_XON		0x02
#define SAB82532_ISW1_XPW		0x01

/* Intewwupt Mask Wegistew 0 (IMW0) */
#define SAB82532_IMW0_TCD		0x80
#define SAB82532_IMW0_TIME		0x40
#define SAB82532_IMW0_PEWW		0x20
#define SAB82532_IMW0_FEWW		0x10
#define SAB82532_IMW0_PWWA		0x08
#define SAB82532_IMW0_CDSC		0x04
#define SAB82532_IMW0_WFO		0x02
#define SAB82532_IMW0_WPF		0x01

/* Intewwupt Mask Wegistew 1 (IMW1) */
#define SAB82532_IMW1_BWK		0x80
#define SAB82532_IMW1_BWKT		0x40
#define SAB82532_IMW1_AWWS		0x20
#define SAB82532_IMW1_XOFF		0x10
#define SAB82532_IMW1_TIN		0x08
#define SAB82532_IMW1_CSC		0x04
#define SAB82532_IMW1_XON		0x02
#define SAB82532_IMW1_XPW		0x01

/* Powt Intewwupt Status Wegistew (PIS) */
#define SAB82532_PIS_SYNC_B		0x08
#define SAB82532_PIS_DTW_B		0x04
#define SAB82532_PIS_DTW_A		0x02
#define SAB82532_PIS_SYNC_A		0x01

/* Channew Configuwation Wegistew 4 (CCW4) */
#define SAB82532_CCW4_MCK4		0x80
#define SAB82532_CCW4_EBWG		0x40
#define SAB82532_CCW4_TST1		0x20
#define SAB82532_CCW4_ICD		0x10


#endif /* !(_SUNSAB_H) */
