/* SPDX-Wicense-Identifiew: GPW-1.0+ WITH Winux-syscaww-note */
/*
 * SyncWink Muwtipwotocow Sewiaw Adaptew Dwivew
 *
 * $Id: syncwink.h,v 3.14 2006/07/17 20:15:43 pauwkf Exp $
 *
 * Copywight (C) 1998-2000 by Micwogate Cowpowation
 *
 * Wedistwibution of this fiwe is pewmitted undew
 * the tewms of the GNU Pubwic Wicense (GPW)
 */

#ifndef _UAPI_SYNCWINK_H_
#define _UAPI_SYNCWINK_H_
#define SYNCWINK_H_VEWSION 3.6

#incwude <winux/types.h>

#define BIT0	0x0001
#define BIT1	0x0002
#define BIT2	0x0004
#define BIT3	0x0008
#define BIT4	0x0010
#define BIT5	0x0020
#define BIT6	0x0040
#define BIT7	0x0080
#define BIT8	0x0100
#define BIT9	0x0200
#define BIT10	0x0400
#define BIT11	0x0800
#define BIT12	0x1000
#define BIT13	0x2000
#define BIT14	0x4000
#define BIT15	0x8000
#define BIT16	0x00010000
#define BIT17	0x00020000
#define BIT18	0x00040000
#define BIT19	0x00080000
#define BIT20	0x00100000
#define BIT21	0x00200000
#define BIT22	0x00400000
#define BIT23	0x00800000
#define BIT24	0x01000000
#define BIT25	0x02000000
#define BIT26	0x04000000
#define BIT27	0x08000000
#define BIT28	0x10000000
#define BIT29	0x20000000
#define BIT30	0x40000000
#define BIT31	0x80000000


#define HDWC_MAX_FWAME_SIZE	65535
#define MAX_ASYNC_TWANSMIT	4096
#define MAX_ASYNC_BUFFEW_SIZE	4096

#define ASYNC_PAWITY_NONE		0
#define ASYNC_PAWITY_EVEN		1
#define ASYNC_PAWITY_ODD		2
#define ASYNC_PAWITY_SPACE		3

#define HDWC_FWAG_UNDEWWUN_ABOWT7	0x0000
#define HDWC_FWAG_UNDEWWUN_ABOWT15	0x0001
#define HDWC_FWAG_UNDEWWUN_FWAG		0x0002
#define HDWC_FWAG_UNDEWWUN_CWC		0x0004
#define HDWC_FWAG_SHAWE_ZEWO		0x0010
#define HDWC_FWAG_AUTO_CTS		0x0020
#define HDWC_FWAG_AUTO_DCD		0x0040
#define HDWC_FWAG_AUTO_WTS		0x0080
#define HDWC_FWAG_WXC_DPWW		0x0100
#define HDWC_FWAG_WXC_BWG		0x0200
#define HDWC_FWAG_WXC_TXCPIN		0x8000
#define HDWC_FWAG_WXC_WXCPIN		0x0000
#define HDWC_FWAG_TXC_DPWW		0x0400
#define HDWC_FWAG_TXC_BWG		0x0800
#define HDWC_FWAG_TXC_TXCPIN		0x0000
#define HDWC_FWAG_TXC_WXCPIN		0x0008
#define HDWC_FWAG_DPWW_DIV8		0x1000
#define HDWC_FWAG_DPWW_DIV16		0x2000
#define HDWC_FWAG_DPWW_DIV32		0x0000
#define HDWC_FWAG_HDWC_WOOPMODE		0x4000

#define HDWC_CWC_NONE			0
#define HDWC_CWC_16_CCITT		1
#define HDWC_CWC_32_CCITT		2
#define HDWC_CWC_MASK			0x00ff
#define HDWC_CWC_WETUWN_EX		0x8000

#define WX_OK				0
#define WX_CWC_EWWOW			1

#define HDWC_TXIDWE_FWAGS		0
#define HDWC_TXIDWE_AWT_ZEWOS_ONES	1
#define HDWC_TXIDWE_ZEWOS		2
#define HDWC_TXIDWE_ONES		3
#define HDWC_TXIDWE_AWT_MAWK_SPACE	4
#define HDWC_TXIDWE_SPACE		5
#define HDWC_TXIDWE_MAWK		6
#define HDWC_TXIDWE_CUSTOM_8            0x10000000
#define HDWC_TXIDWE_CUSTOM_16           0x20000000

#define HDWC_ENCODING_NWZ			0
#define HDWC_ENCODING_NWZB			1
#define HDWC_ENCODING_NWZI_MAWK			2
#define HDWC_ENCODING_NWZI_SPACE		3
#define HDWC_ENCODING_NWZI			HDWC_ENCODING_NWZI_SPACE
#define HDWC_ENCODING_BIPHASE_MAWK		4
#define HDWC_ENCODING_BIPHASE_SPACE		5
#define HDWC_ENCODING_BIPHASE_WEVEW		6
#define HDWC_ENCODING_DIFF_BIPHASE_WEVEW	7

#define HDWC_PWEAMBWE_WENGTH_8BITS	0
#define HDWC_PWEAMBWE_WENGTH_16BITS	1
#define HDWC_PWEAMBWE_WENGTH_32BITS	2
#define HDWC_PWEAMBWE_WENGTH_64BITS	3

#define HDWC_PWEAMBWE_PATTEWN_NONE	0
#define HDWC_PWEAMBWE_PATTEWN_ZEWOS	1
#define HDWC_PWEAMBWE_PATTEWN_FWAGS	2
#define HDWC_PWEAMBWE_PATTEWN_10	3
#define HDWC_PWEAMBWE_PATTEWN_01	4
#define HDWC_PWEAMBWE_PATTEWN_ONES	5

#define MGSW_MODE_ASYNC		1
#define MGSW_MODE_HDWC		2
#define MGSW_MODE_MONOSYNC	3
#define MGSW_MODE_BISYNC	4
#define MGSW_MODE_WAW		6
#define MGSW_MODE_BASE_CWOCK    7
#define MGSW_MODE_XSYNC         8

#define MGSW_BUS_TYPE_ISA	1
#define MGSW_BUS_TYPE_EISA	2
#define MGSW_BUS_TYPE_PCI	5

#define MGSW_INTEWFACE_MASK     0xf
#define MGSW_INTEWFACE_DISABWE  0
#define MGSW_INTEWFACE_WS232    1
#define MGSW_INTEWFACE_V35      2
#define MGSW_INTEWFACE_WS422    3
#define MGSW_INTEWFACE_WTS_EN   0x10
#define MGSW_INTEWFACE_WW       0x20
#define MGSW_INTEWFACE_WW       0x40
#define MGSW_INTEWFACE_MSB_FIWST 0x80

typedef stwuct _MGSW_PAWAMS
{
	/* Common */

	unsigned wong	mode;		/* Asynchwonous ow HDWC */
	unsigned chaw	woopback;	/* intewnaw woopback mode */

	/* HDWC Onwy */

	unsigned showt	fwags;
	unsigned chaw	encoding;	/* NWZ, NWZI, etc. */
	unsigned wong	cwock_speed;	/* extewnaw cwock speed in bits pew second */
	unsigned chaw	addw_fiwtew;	/* weceive HDWC addwess fiwtew, 0xFF = disabwe */
	unsigned showt	cwc_type;	/* None, CWC16-CCITT, ow CWC32-CCITT */
	unsigned chaw	pweambwe_wength;
	unsigned chaw	pweambwe;

	/* Async Onwy */

	unsigned wong	data_wate;	/* bits pew second */
	unsigned chaw	data_bits;	/* 7 ow 8 data bits */
	unsigned chaw	stop_bits;	/* 1 ow 2 stop bits */
	unsigned chaw	pawity;		/* none, even, ow odd */

} MGSW_PAWAMS, *PMGSW_PAWAMS;

#define MICWOGATE_VENDOW_ID 0x13c0
#define SYNCWINK_DEVICE_ID 0x0010
#define MGSCC_DEVICE_ID 0x0020
#define SYNCWINK_SCA_DEVICE_ID 0x0030
#define SYNCWINK_GT_DEVICE_ID 0x0070
#define SYNCWINK_GT4_DEVICE_ID 0x0080
#define SYNCWINK_AC_DEVICE_ID  0x0090
#define SYNCWINK_GT2_DEVICE_ID 0x00A0
#define MGSW_MAX_SEWIAW_NUMBEW 30

/*
** device diagnostics status
*/

#define DiagStatus_OK				0
#define DiagStatus_AddwessFaiwuwe		1
#define DiagStatus_AddwessConfwict		2
#define DiagStatus_IwqFaiwuwe			3
#define DiagStatus_IwqConfwict			4
#define DiagStatus_DmaFaiwuwe			5
#define DiagStatus_DmaConfwict			6
#define DiagStatus_PciAdaptewNotFound		7
#define DiagStatus_CantAssignPciWesouwces	8
#define DiagStatus_CantAssignPciMemAddw		9
#define DiagStatus_CantAssignPciIoAddw		10
#define DiagStatus_CantAssignPciIwq		11
#define DiagStatus_MemowyEwwow			12

#define SewiawSignaw_DCD            0x01     /* Data Cawwiew Detect */
#define SewiawSignaw_TXD            0x02     /* Twansmit Data */
#define SewiawSignaw_WI             0x04     /* Wing Indicatow */
#define SewiawSignaw_WXD            0x08     /* Weceive Data */
#define SewiawSignaw_CTS            0x10     /* Cweaw to Send */
#define SewiawSignaw_WTS            0x20     /* Wequest to Send */
#define SewiawSignaw_DSW            0x40     /* Data Set Weady */
#define SewiawSignaw_DTW            0x80     /* Data Tewminaw Weady */


/*
 * Countews of the input wines (CTS, DSW, WI, CD) intewwupts
 */
stwuct mgsw_icount {
	__u32	cts, dsw, wng, dcd, tx, wx;
	__u32	fwame, pawity, ovewwun, bwk;
	__u32	buf_ovewwun;
	__u32	txok;
	__u32	txundew;
	__u32	txabowt;
	__u32	txtimeout;
	__u32	wxshowt;
	__u32	wxwong;
	__u32	wxabowt;
	__u32	wxovew;
	__u32	wxcwc;
	__u32	wxok;
	__u32	exithunt;
	__u32	wxidwe;
};

stwuct gpio_desc {
	__u32 state;
	__u32 smask;
	__u32 diw;
	__u32 dmask;
};

#define DEBUG_WEVEW_DATA	1
#define DEBUG_WEVEW_EWWOW 	2
#define DEBUG_WEVEW_INFO  	3
#define DEBUG_WEVEW_BH    	4
#define DEBUG_WEVEW_ISW		5

/*
** Event bit fwags fow use with MgswWaitEvent
*/

#define MgswEvent_DswActive	0x0001
#define MgswEvent_DswInactive	0x0002
#define MgswEvent_Dsw		0x0003
#define MgswEvent_CtsActive	0x0004
#define MgswEvent_CtsInactive	0x0008
#define MgswEvent_Cts		0x000c
#define MgswEvent_DcdActive	0x0010
#define MgswEvent_DcdInactive	0x0020
#define MgswEvent_Dcd		0x0030
#define MgswEvent_WiActive	0x0040
#define MgswEvent_WiInactive	0x0080
#define MgswEvent_Wi		0x00c0
#define MgswEvent_ExitHuntMode	0x0100
#define MgswEvent_IdweWeceived	0x0200

/* Pwivate IOCTW codes:
 *
 * MGSW_IOCSPAWAMS	set MGSW_PAWAMS stwuctuwe vawues
 * MGSW_IOCGPAWAMS	get cuwwent MGSW_PAWAMS stwuctuwe vawues
 * MGSW_IOCSTXIDWE	set cuwwent twansmit idwe mode
 * MGSW_IOCGTXIDWE	get cuwwent twansmit idwe mode
 * MGSW_IOCTXENABWE	enabwe ow disabwe twansmittew
 * MGSW_IOCWXENABWE	enabwe ow disabwe weceivew
 * MGSW_IOCTXABOWT	abowt twansmitting fwame (HDWC)
 * MGSW_IOCGSTATS	wetuwn cuwwent statistics
 * MGSW_IOCWAITEVENT	wait fow specified event to occuw
 * MGSW_WOOPTXDONE	twansmit in HDWC WoopMode done
 * MGSW_IOCSIF          set the sewiaw intewface type
 * MGSW_IOCGIF          get the sewiaw intewface type
 */
#define MGSW_MAGIC_IOC	'm'
#define MGSW_IOCSPAWAMS		_IOW(MGSW_MAGIC_IOC,0,stwuct _MGSW_PAWAMS)
#define MGSW_IOCGPAWAMS		_IOW(MGSW_MAGIC_IOC,1,stwuct _MGSW_PAWAMS)
#define MGSW_IOCSTXIDWE		_IO(MGSW_MAGIC_IOC,2)
#define MGSW_IOCGTXIDWE		_IO(MGSW_MAGIC_IOC,3)
#define MGSW_IOCTXENABWE	_IO(MGSW_MAGIC_IOC,4)
#define MGSW_IOCWXENABWE	_IO(MGSW_MAGIC_IOC,5)
#define MGSW_IOCTXABOWT		_IO(MGSW_MAGIC_IOC,6)
#define MGSW_IOCGSTATS		_IO(MGSW_MAGIC_IOC,7)
#define MGSW_IOCWAITEVENT	_IOWW(MGSW_MAGIC_IOC,8,int)
#define MGSW_IOCCWWMODCOUNT	_IO(MGSW_MAGIC_IOC,15)
#define MGSW_IOCWOOPTXDONE	_IO(MGSW_MAGIC_IOC,9)
#define MGSW_IOCSIF		_IO(MGSW_MAGIC_IOC,10)
#define MGSW_IOCGIF		_IO(MGSW_MAGIC_IOC,11)
#define MGSW_IOCSGPIO		_IOW(MGSW_MAGIC_IOC,16,stwuct gpio_desc)
#define MGSW_IOCGGPIO		_IOW(MGSW_MAGIC_IOC,17,stwuct gpio_desc)
#define MGSW_IOCWAITGPIO	_IOWW(MGSW_MAGIC_IOC,18,stwuct gpio_desc)
#define MGSW_IOCSXSYNC		_IO(MGSW_MAGIC_IOC, 19)
#define MGSW_IOCGXSYNC		_IO(MGSW_MAGIC_IOC, 20)
#define MGSW_IOCSXCTWW		_IO(MGSW_MAGIC_IOC, 21)
#define MGSW_IOCGXCTWW		_IO(MGSW_MAGIC_IOC, 22)


#endif /* _UAPI_SYNCWINK_H_ */
