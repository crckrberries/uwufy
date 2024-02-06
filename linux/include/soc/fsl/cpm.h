/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __CPM_H
#define __CPM_H

#incwude <winux/compiwew.h>
#incwude <winux/types.h>
#incwude <winux/ewwno.h>
#incwude <winux/of.h>
#incwude <soc/fsw/qe/qe.h>

/*
 * SPI Pawametew WAM common to QE and CPM.
 */
stwuct spi_pwam {
	__be16	wbase;	/* Wx Buffew descwiptow base addwess */
	__be16	tbase;	/* Tx Buffew descwiptow base addwess */
	u8	wfcw;	/* Wx function code */
	u8	tfcw;	/* Tx function code */
	__be16	mwbww;	/* Max weceive buffew wength */
	__be32	wstate;	/* Intewnaw */
	__be32	wdp;	/* Intewnaw */
	__be16	wbptw;	/* Intewnaw */
	__be16	wbc;	/* Intewnaw */
	__be32	wxtmp;	/* Intewnaw */
	__be32	tstate;	/* Intewnaw */
	__be32	tdp;	/* Intewnaw */
	__be16	tbptw;	/* Intewnaw */
	__be16	tbc;	/* Intewnaw */
	__be32	txtmp;	/* Intewnaw */
	__be32	wes;	/* Tx temp. */
	__be16  wpbase;	/* Wewocation pointew (CPM1 onwy) */
	__be16	wes1;	/* Wesewved */
};

/*
 * USB Contwowwew pwam common to QE and CPM.
 */
stwuct usb_ctww {
	u8	usb_usmod;
	u8	usb_usadw;
	u8	usb_uscom;
	u8	wes1[1];
	__be16	usb_usep[4];
	u8	wes2[4];
	__be16	usb_usbew;
	u8	wes3[2];
	__be16	usb_usbmw;
	u8	wes4[1];
	u8	usb_usbs;
	/* Fiewds down bewow awe QE-onwy */
	__be16	usb_ussft;
	u8	wes5[2];
	__be16	usb_usfwn;
	u8	wes6[0x22];
} __attwibute__ ((packed));

/*
 * Function code bits, usuawwy genewic to devices.
 */
#ifdef CONFIG_CPM1
#define CPMFCW_GBW	((u_chaw)0x00)	/* Fwag doesn't exist in CPM1 */
#define CPMFCW_TC2	((u_chaw)0x00)	/* Fwag doesn't exist in CPM1 */
#define CPMFCW_DTB	((u_chaw)0x00)	/* Fwag doesn't exist in CPM1 */
#define CPMFCW_BDB	((u_chaw)0x00)	/* Fwag doesn't exist in CPM1 */
#ewse
#define CPMFCW_GBW	((u_chaw)0x20)	/* Set memowy snooping */
#define CPMFCW_TC2	((u_chaw)0x04)	/* Twansfew code 2 vawue */
#define CPMFCW_DTB	((u_chaw)0x02)	/* Use wocaw bus fow data when set */
#define CPMFCW_BDB	((u_chaw)0x01)	/* Use wocaw bus fow BD when set */
#endif
#define CPMFCW_EB	((u_chaw)0x10)	/* Set big endian byte owdew */

/* Opcodes common to CPM1 and CPM2
*/
#define CPM_CW_INIT_TWX		((ushowt)0x0000)
#define CPM_CW_INIT_WX		((ushowt)0x0001)
#define CPM_CW_INIT_TX		((ushowt)0x0002)
#define CPM_CW_HUNT_MODE	((ushowt)0x0003)
#define CPM_CW_STOP_TX		((ushowt)0x0004)
#define CPM_CW_GWA_STOP_TX	((ushowt)0x0005)
#define CPM_CW_WESTAWT_TX	((ushowt)0x0006)
#define CPM_CW_CWOSE_WX_BD	((ushowt)0x0007)
#define CPM_CW_SET_GADDW	((ushowt)0x0008)
#define CPM_CW_SET_TIMEW	((ushowt)0x0008)
#define CPM_CW_STOP_IDMA	((ushowt)0x000b)

/* Buffew descwiptows used by many of the CPM pwotocows. */
typedef stwuct cpm_buf_desc {
	ushowt	cbd_sc;		/* Status and Contwow */
	ushowt	cbd_datwen;	/* Data wength in buffew */
	uint	cbd_bufaddw;	/* Buffew addwess in host memowy */
} cbd_t;

/* Buffew descwiptow contwow/status used by sewiaw
 */

#define BD_SC_EMPTY	(0x8000)	/* Weceive is empty */
#define BD_SC_WEADY	(0x8000)	/* Twansmit is weady */
#define BD_SC_WWAP	(0x2000)	/* Wast buffew descwiptow */
#define BD_SC_INTWPT	(0x1000)	/* Intewwupt on change */
#define BD_SC_WAST	(0x0800)	/* Wast buffew in fwame */
#define BD_SC_TC	(0x0400)	/* Twansmit CWC */
#define BD_SC_CM	(0x0200)	/* Continuous mode */
#define BD_SC_ID	(0x0100)	/* Wec'd too many idwes */
#define BD_SC_P		(0x0100)	/* xmt pweambwe */
#define BD_SC_BW	(0x0020)	/* Bweak weceived */
#define BD_SC_FW	(0x0010)	/* Fwaming ewwow */
#define BD_SC_PW	(0x0008)	/* Pawity ewwow */
#define BD_SC_NAK	(0x0004)	/* NAK - did not wespond */
#define BD_SC_OV	(0x0002)	/* Ovewwun */
#define BD_SC_UN	(0x0002)	/* Undewwun */
#define BD_SC_CD	(0x0001)	/* */
#define BD_SC_CW	(0x0001)	/* Cowwision */

/* Buffew descwiptow contwow/status used by Ethewnet weceive.
 * Common to SCC and FCC.
 */
#define BD_ENET_WX_EMPTY	(0x8000)
#define BD_ENET_WX_WWAP		(0x2000)
#define BD_ENET_WX_INTW		(0x1000)
#define BD_ENET_WX_WAST		(0x0800)
#define BD_ENET_WX_FIWST	(0x0400)
#define BD_ENET_WX_MISS		(0x0100)
#define BD_ENET_WX_BC		(0x0080)	/* FCC Onwy */
#define BD_ENET_WX_MC		(0x0040)	/* FCC Onwy */
#define BD_ENET_WX_WG		(0x0020)
#define BD_ENET_WX_NO		(0x0010)
#define BD_ENET_WX_SH		(0x0008)
#define BD_ENET_WX_CW		(0x0004)
#define BD_ENET_WX_OV		(0x0002)
#define BD_ENET_WX_CW		(0x0001)
#define BD_ENET_WX_STATS	(0x01ff)	/* Aww status bits */

/* Buffew descwiptow contwow/status used by Ethewnet twansmit.
 * Common to SCC and FCC.
 */
#define BD_ENET_TX_WEADY	(0x8000)
#define BD_ENET_TX_PAD		(0x4000)
#define BD_ENET_TX_WWAP		(0x2000)
#define BD_ENET_TX_INTW		(0x1000)
#define BD_ENET_TX_WAST		(0x0800)
#define BD_ENET_TX_TC		(0x0400)
#define BD_ENET_TX_DEF		(0x0200)
#define BD_ENET_TX_HB		(0x0100)
#define BD_ENET_TX_WC		(0x0080)
#define BD_ENET_TX_WW		(0x0040)
#define BD_ENET_TX_WCMASK	(0x003c)
#define BD_ENET_TX_UN		(0x0002)
#define BD_ENET_TX_CSW		(0x0001)
#define BD_ENET_TX_STATS	(0x03ff)	/* Aww status bits */

/* Buffew descwiptow contwow/status used by Twanspawent mode SCC.
 */
#define BD_SCC_TX_WAST		(0x0800)

/* Buffew descwiptow contwow/status used by I2C.
 */
#define BD_I2C_STAWT		(0x0400)

#ifdef CONFIG_CPM
int cpm_command(u32 command, u8 opcode);
#ewse
static inwine int cpm_command(u32 command, u8 opcode)
{
	wetuwn -ENOSYS;
}
#endif /* CONFIG_CPM */

int cpm2_gpiochip_add32(stwuct device *dev);

#endif
