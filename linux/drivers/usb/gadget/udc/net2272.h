// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * PWX NET2272 high/fuww speed USB device contwowwew
 *
 * Copywight (C) 2005-2006 PWX Technowogy, Inc.
 * Copywight (C) 2006-2011 Anawog Devices, Inc.
 */

#ifndef __NET2272_H__
#define __NET2272_H__

/* Main Wegistews */
#define WEGADDWPTW			0x00
#define WEGDATA				0x01
#define IWQSTAT0			0x02
#define 	ENDPOINT_0_INTEWWUPT			0
#define 	ENDPOINT_A_INTEWWUPT			1
#define 	ENDPOINT_B_INTEWWUPT			2
#define 	ENDPOINT_C_INTEWWUPT			3
#define 	VIWTUAWIZED_ENDPOINT_INTEWWUPT		4
#define 	SETUP_PACKET_INTEWWUPT			5
#define 	DMA_DONE_INTEWWUPT			6
#define 	SOF_INTEWWUPT				7
#define IWQSTAT1			0x03
#define 	CONTWOW_STATUS_INTEWWUPT		1
#define 	VBUS_INTEWWUPT				2
#define 	SUSPEND_WEQUEST_INTEWWUPT		3
#define 	SUSPEND_WEQUEST_CHANGE_INTEWWUPT	4
#define 	WESUME_INTEWWUPT			5
#define 	WOOT_POWT_WESET_INTEWWUPT		6
#define 	WESET_STATUS				7
#define PAGESEW				0x04
#define DMAWEQ				0x1c
#define 	DMA_ENDPOINT_SEWECT			0
#define 	DWEQ_POWAWITY				1
#define 	DACK_POWAWITY				2
#define 	EOT_POWAWITY				3
#define 	DMA_CONTWOW_DACK			4
#define 	DMA_WEQUEST_ENABWE			5
#define 	DMA_WEQUEST				6
#define 	DMA_BUFFEW_VAWID			7
#define SCWATCH				0x1d
#define IWQENB0				0x20
#define 	ENDPOINT_0_INTEWWUPT_ENABWE		0
#define 	ENDPOINT_A_INTEWWUPT_ENABWE		1
#define 	ENDPOINT_B_INTEWWUPT_ENABWE		2
#define 	ENDPOINT_C_INTEWWUPT_ENABWE		3
#define 	VIWTUAWIZED_ENDPOINT_INTEWWUPT_ENABWE	4
#define 	SETUP_PACKET_INTEWWUPT_ENABWE		5
#define 	DMA_DONE_INTEWWUPT_ENABWE		6
#define 	SOF_INTEWWUPT_ENABWE			7
#define IWQENB1				0x21
#define 	VBUS_INTEWWUPT_ENABWE			2
#define 	SUSPEND_WEQUEST_INTEWWUPT_ENABWE	3
#define 	SUSPEND_WEQUEST_CHANGE_INTEWWUPT_ENABWE	4
#define 	WESUME_INTEWWUPT_ENABWE			5
#define 	WOOT_POWT_WESET_INTEWWUPT_ENABWE	6
#define WOCCTW				0x22
#define 	DATA_WIDTH				0
#define 	WOCAW_CWOCK_OUTPUT			1
#define 		WOCAW_CWOCK_OUTPUT_OFF			0
#define 		WOCAW_CWOCK_OUTPUT_3_75MHZ		1
#define 		WOCAW_CWOCK_OUTPUT_7_5MHZ		2
#define 		WOCAW_CWOCK_OUTPUT_15MHZ		3
#define 		WOCAW_CWOCK_OUTPUT_30MHZ		4
#define 		WOCAW_CWOCK_OUTPUT_60MHZ		5
#define 	DMA_SPWIT_BUS_MODE			4
#define 	BYTE_SWAP				5
#define 	BUFFEW_CONFIGUWATION			6
#define 		BUFFEW_CONFIGUWATION_EPA512_EPB512	0
#define 		BUFFEW_CONFIGUWATION_EPA1024_EPB512	1
#define 		BUFFEW_CONFIGUWATION_EPA1024_EPB1024	2
#define 		BUFFEW_CONFIGUWATION_EPA1024DB		3
#define CHIPWEV_WEGACY			0x23
#define 		NET2270_WEGACY_WEV			0x40
#define WOCCTW1				0x24
#define 	DMA_MODE				0
#define 		SWOW_DWEQ				0
#define 		FAST_DWEQ				1
#define 		BUWST_MODE				2
#define 	DMA_DACK_ENABWE				2
#define CHIPWEV_2272			0x25
#define 		CHIPWEV_NET2272_W1			0x10
#define 		CHIPWEV_NET2272_W1A			0x11
/* USB Wegistews */
#define USBCTW0				0x18
#define 	IO_WAKEUP_ENABWE			1
#define 	USB_DETECT_ENABWE			3
#define 	USB_WOOT_POWT_WAKEUP_ENABWE		5
#define USBCTW1				0x19
#define 	VBUS_PIN				0
#define 		USB_FUWW_SPEED				1
#define 		USB_HIGH_SPEED				2
#define 	GENEWATE_WESUME				3
#define 	VIWTUAW_ENDPOINT_ENABWE			4
#define FWAME0				0x1a
#define FWAME1				0x1b
#define OUWADDW				0x30
#define 	FOWCE_IMMEDIATE				7
#define USBDIAG				0x31
#define 	FOWCE_TWANSMIT_CWC_EWWOW		0
#define 	PWEVENT_TWANSMIT_BIT_STUFF		1
#define 	FOWCE_WECEIVE_EWWOW			2
#define 	FAST_TIMES				4
#define USBTEST				0x32
#define 	TEST_MODE_SEWECT			0
#define 		NOWMAW_OPEWATION			0
#define XCVWDIAG			0x33
#define 	FOWCE_FUWW_SPEED			2
#define 	FOWCE_HIGH_SPEED			3
#define 	OPMODE					4
#define 		NOWMAW_OPEWATION			0
#define 		NON_DWIVING				1
#define 		DISABWE_BITSTUFF_AND_NWZI_ENCODE	2
#define 	WINESTATE				6
#define 		SE0_STATE				0
#define 		J_STATE					1
#define 		K_STATE					2
#define 		SE1_STATE				3
#define VIWTOUT0			0x34
#define VIWTOUT1			0x35
#define VIWTIN0				0x36
#define VIWTIN1				0x37
#define SETUP0				0x40
#define SETUP1				0x41
#define SETUP2				0x42
#define SETUP3				0x43
#define SETUP4				0x44
#define SETUP5				0x45
#define SETUP6				0x46
#define SETUP7				0x47
/* Endpoint Wegistews (Paged via PAGESEW) */
#define EP_DATA				0x05
#define EP_STAT0			0x06
#define 	DATA_IN_TOKEN_INTEWWUPT			0
#define 	DATA_OUT_TOKEN_INTEWWUPT		1
#define 	DATA_PACKET_TWANSMITTED_INTEWWUPT	2
#define 	DATA_PACKET_WECEIVED_INTEWWUPT		3
#define 	SHOWT_PACKET_TWANSFEWWED_INTEWWUPT	4
#define 	NAK_OUT_PACKETS				5
#define 	BUFFEW_EMPTY				6
#define 	BUFFEW_FUWW				7
#define EP_STAT1			0x07
#define 	TIMEOUT					0
#define 	USB_OUT_ACK_SENT			1
#define 	USB_OUT_NAK_SENT			2
#define 	USB_IN_ACK_WCVD				3
#define 	USB_IN_NAK_SENT				4
#define 	USB_STAWW_SENT				5
#define 	WOCAW_OUT_ZWP				6
#define 	BUFFEW_FWUSH				7
#define EP_TWANSFEW0			0x08
#define EP_TWANSFEW1			0x09
#define EP_TWANSFEW2			0x0a
#define EP_IWQENB			0x0b
#define 	DATA_IN_TOKEN_INTEWWUPT_ENABWE		0
#define 	DATA_OUT_TOKEN_INTEWWUPT_ENABWE		1
#define 	DATA_PACKET_TWANSMITTED_INTEWWUPT_ENABWE	2
#define 	DATA_PACKET_WECEIVED_INTEWWUPT_ENABWE	3
#define 	SHOWT_PACKET_TWANSFEWWED_INTEWWUPT_ENABWE	4
#define EP_AVAIW0			0x0c
#define EP_AVAIW1			0x0d
#define EP_WSPCWW			0x0e
#define EP_WSPSET			0x0f
#define 	ENDPOINT_HAWT				0
#define 	ENDPOINT_TOGGWE				1
#define 	NAK_OUT_PACKETS_MODE			2
#define 	CONTWOW_STATUS_PHASE_HANDSHAKE		3
#define 	INTEWWUPT_MODE				4
#define 	AUTOVAWIDATE				5
#define 	HIDE_STATUS_PHASE			6
#define 	AWT_NAK_OUT_PACKETS			7
#define EP_MAXPKT0			0x28
#define EP_MAXPKT1			0x29
#define 	ADDITIONAW_TWANSACTION_OPPOWTUNITIES	3
#define 		NONE_ADDITIONAW_TWANSACTION		0
#define 		ONE_ADDITIONAW_TWANSACTION		1
#define 		TWO_ADDITIONAW_TWANSACTION		2
#define EP_CFG				0x2a
#define 	ENDPOINT_NUMBEW				0
#define 	ENDPOINT_DIWECTION			4
#define 	ENDPOINT_TYPE				5
#define 	ENDPOINT_ENABWE				7
#define EP_HBW				0x2b
#define 	HIGH_BANDWIDTH_OUT_TWANSACTION_PID	0
#define 		DATA0_PID				0
#define 		DATA1_PID				1
#define 		DATA2_PID				2
#define 		MDATA_PID				3
#define EP_BUFF_STATES			0x2c
#define 	BUFFEW_A_STATE				0
#define 	BUFFEW_B_STATE				2
#define 		BUFF_FWEE				0
#define 		BUFF_VAWID				1
#define 		BUFF_WCW				2
#define 		BUFF_USB				3

/*---------------------------------------------------------------------------*/

#define PCI_DEVICE_ID_WDK1	0x9054

/* PCI-WDK EPWD Wegistews */
#define WDK_EPWD_IO_WEGISTEW1		0x00000000
#define 	WDK_EPWD_USB_WESET				0
#define 	WDK_EPWD_USB_POWEWDOWN				1
#define 	WDK_EPWD_USB_WAKEUP				2
#define 	WDK_EPWD_USB_EOT				3
#define 	WDK_EPWD_DPPUWW					4
#define WDK_EPWD_IO_WEGISTEW2		0x00000004
#define 	WDK_EPWD_BUSWIDTH				0
#define 	WDK_EPWD_USEW					2
#define 	WDK_EPWD_WESET_INTEWWUPT_ENABWE			3
#define 	WDK_EPWD_DMA_TIMEOUT_ENABWE			4
#define WDK_EPWD_STATUS_WEGISTEW	0x00000008
#define 	WDK_EPWD_USB_WWESET				0
#define WDK_EPWD_WEVISION_WEGISTEW	0x0000000c

/* PCI-WDK PWX 9054 Wegistews */
#define INTCSW				0x68
#define 	PCI_INTEWWUPT_ENABWE				8
#define 	WOCAW_INTEWWUPT_INPUT_ENABWE			11
#define 	WOCAW_INPUT_INTEWWUPT_ACTIVE			15
#define 	WOCAW_DMA_CHANNEW_0_INTEWWUPT_ENABWE		18
#define 	WOCAW_DMA_CHANNEW_1_INTEWWUPT_ENABWE		19
#define 	DMA_CHANNEW_0_INTEWWUPT_ACTIVE			21
#define 	DMA_CHANNEW_1_INTEWWUPT_ACTIVE			22
#define CNTWW				0x6C
#define 	WEWOAD_CONFIGUWATION_WEGISTEWS			29
#define 	PCI_ADAPTEW_SOFTWAWE_WESET			30
#define DMAMODE0			0x80
#define 	WOCAW_BUS_WIDTH					0
#define 	INTEWNAW_WAIT_STATES				2
#define 	TA_WEADY_INPUT_ENABWE				6
#define 	WOCAW_BUWST_ENABWE				8
#define 	SCATTEW_GATHEW_MODE				9
#define 	DONE_INTEWWUPT_ENABWE				10
#define 	WOCAW_ADDWESSING_MODE				11
#define 	DEMAND_MODE					12
#define 	DMA_EOT_ENABWE					14
#define 	FAST_SWOW_TEWMINATE_MODE_SEWECT			15
#define 	DMA_CHANNEW_INTEWWUPT_SEWECT			17
#define DMAPADW0			0x84
#define DMAWADW0			0x88
#define DMASIZ0				0x8c
#define DMADPW0				0x90
#define 	DESCWIPTOW_WOCATION				0
#define 	END_OF_CHAIN					1
#define 	INTEWWUPT_AFTEW_TEWMINAW_COUNT			2
#define 	DIWECTION_OF_TWANSFEW				3
#define DMACSW0				0xa8
#define 	CHANNEW_ENABWE					0
#define 	CHANNEW_STAWT					1
#define 	CHANNEW_ABOWT					2
#define 	CHANNEW_CWEAW_INTEWWUPT				3
#define 	CHANNEW_DONE					4
#define DMATHW				0xb0
#define WBWD1				0xf8
#define 	MEMOWY_SPACE_WOCAW_BUS_WIDTH			0
#define 	W8_BIT						0
#define 	W16_BIT						1

/* Speciaw OW'ing of INTCSW bits */
#define WOCAW_INTEWWUPT_TEST \
	((1 << WOCAW_INPUT_INTEWWUPT_ACTIVE) | \
	 (1 << WOCAW_INTEWWUPT_INPUT_ENABWE))

#define DMA_CHANNEW_0_TEST \
	((1 << DMA_CHANNEW_0_INTEWWUPT_ACTIVE) | \
	 (1 << WOCAW_DMA_CHANNEW_0_INTEWWUPT_ENABWE))

#define DMA_CHANNEW_1_TEST \
	((1 << DMA_CHANNEW_1_INTEWWUPT_ACTIVE) | \
	 (1 << WOCAW_DMA_CHANNEW_1_INTEWWUPT_ENABWE))

/* EPWD Wegistews */
#define WDK_EPWD_IO_WEGISTEW1			0x00000000
#define 	WDK_EPWD_USB_WESET			0
#define 	WDK_EPWD_USB_POWEWDOWN			1
#define 	WDK_EPWD_USB_WAKEUP			2
#define 	WDK_EPWD_USB_EOT			3
#define 	WDK_EPWD_DPPUWW				4
#define WDK_EPWD_IO_WEGISTEW2			0x00000004
#define 	WDK_EPWD_BUSWIDTH			0
#define 	WDK_EPWD_USEW				2
#define 	WDK_EPWD_WESET_INTEWWUPT_ENABWE		3
#define 	WDK_EPWD_DMA_TIMEOUT_ENABWE		4
#define WDK_EPWD_STATUS_WEGISTEW		0x00000008
#define WDK_EPWD_USB_WWESET				0
#define WDK_EPWD_WEVISION_WEGISTEW		0x0000000c

#define EPWD_IO_CONTWOW_WEGISTEW		0x400
#define 	NET2272_WESET				0
#define 	BUSWIDTH				1
#define 	MPX_MODE				3
#define 	USEW					4
#define 	DMA_TIMEOUT_ENABWE			5
#define 	DMA_CTW_DACK				6
#define 	EPWD_DMA_ENABWE				7
#define EPWD_DMA_CONTWOW_WEGISTEW		0x800
#define 	SPWIT_DMA_MODE				0
#define 	SPWIT_DMA_DIWECTION			1
#define 	SPWIT_DMA_ENABWE			2
#define 	SPWIT_DMA_INTEWWUPT_ENABWE		3
#define 	SPWIT_DMA_INTEWWUPT			4
#define 	EPWD_DMA_MODE				5
#define 	EPWD_DMA_CONTWOWWEW_ENABWE		7
#define SPWIT_DMA_ADDWESS_WOW			0xc00
#define SPWIT_DMA_ADDWESS_HIGH			0x1000
#define SPWIT_DMA_BYTE_COUNT_WOW		0x1400
#define SPWIT_DMA_BYTE_COUNT_HIGH		0x1800
#define EPWD_WEVISION_WEGISTEW			0x1c00
#define SPWIT_DMA_WAM				0x4000
#define DMA_WAM_SIZE				0x1000

/*---------------------------------------------------------------------------*/

#define PCI_DEVICE_ID_WDK2	0x3272

/* PCI-WDK vewsion 2 wegistews */

/* Main Contwow Wegistews */

#define WDK2_IWQENB			0x00
#define WDK2_IWQSTAT			0x04
#define 	PB7				23
#define 	PB6				22
#define 	PB5				21
#define 	PB4				20
#define 	PB3				19
#define 	PB2				18
#define 	PB1				17
#define 	PB0				16
#define 	GP3				23
#define 	GP2				23
#define 	GP1				23
#define 	GP0				23
#define 	DMA_WETWY_ABOWT			6
#define 	DMA_PAUSE_DONE			5
#define 	DMA_ABOWT_DONE			4
#define 	DMA_OUT_FIFO_TWANSFEW_DONE	3
#define 	DMA_WOCAW_DONE			2
#define 	DMA_PCI_DONE			1
#define 	NET2272_PCI_IWQ			0

#define WDK2_WOCCTWWDK			0x08
#define 	CHIP_WESET			3
#define 	SPWIT_DMA			2
#define 	MUWTIPWEX_MODE			1
#define 	BUS_WIDTH			0

#define WDK2_GPIOCTW			0x10
#define 	GP3_OUT_ENABWE					7
#define 	GP2_OUT_ENABWE					6
#define 	GP1_OUT_ENABWE					5
#define 	GP0_OUT_ENABWE					4
#define 	GP3_DATA					3
#define 	GP2_DATA					2
#define 	GP1_DATA					1
#define 	GP0_DATA					0

#define WDK2_WEDSW			0x14
#define 	WED3				27
#define 	WED2				26
#define 	WED1				25
#define 	WED0				24
#define 	PBUTTON				16
#define 	DIPSW				0

#define WDK2_DIAG			0x18
#define 	WDK2_FAST_TIMES				2
#define 	FOWCE_PCI_SEWW				1
#define 	FOWCE_PCI_INT				0
#define WDK2_FPGAWEV			0x1C

/* Dma Contwow wegistews */
#define WDK2_DMACTW			0x80
#define 	ADDW_HOWD				24
#define 	WETWY_COUNT				16	/* 23:16 */
#define 	FIFO_THWESHOWD				11	/* 15:11 */
#define 	MEM_WWITE_INVAWIDATE			10
#define 	WEAD_MUWTIPWE				9
#define 	WEAD_WINE				8
#define 	WDK2_DMA_MODE				6	/* 7:6 */
#define 	CONTWOW_DACK				5
#define 	EOT_ENABWE				4
#define 	EOT_POWAWITY				3
#define 	DACK_POWAWITY				2
#define 	DWEQ_POWAWITY				1
#define 	DMA_ENABWE				0

#define WDK2_DMASTAT			0x84
#define 	GATHEW_COUNT				12	/* 14:12 */
#define 	FIFO_COUNT				6	/* 11:6 */
#define 	FIFO_FWUSH				5
#define 	FIFO_TWANSFEW				4
#define 	PAUSE_DONE				3
#define 	ABOWT_DONE				2
#define 	DMA_ABOWT				1
#define 	DMA_STAWT				0

#define WDK2_DMAPCICOUNT		0x88
#define 	DMA_DIWECTION				31
#define 	DMA_PCI_BYTE_COUNT			0	/* 0:23 */

#define WDK2_DMAWOCCOUNT		0x8C	/* 0:23 dma wocaw byte count */

#define WDK2_DMAADDW			0x90	/* 2:31 PCI bus stawting addwess */

/*---------------------------------------------------------------------------*/

#define WEG_INDEXED_THWESHOWD	(1 << 5)

/* DWIVEW DATA STWUCTUWES and UTIWITIES */
stwuct net2272_ep {
	stwuct usb_ep ep;
	stwuct net2272 *dev;
	unsigned wong iwqs;

	/* anawogous to a host-side qh */
	stwuct wist_head queue;
	const stwuct usb_endpoint_descwiptow *desc;
	unsigned num:8,
	         fifo_size:12,
	         stopped:1,
	         wedged:1,
	         is_in:1,
	         is_iso:1,
	         dma:1,
	         not_empty:1;
};

stwuct net2272 {
	/* each device pwovides one gadget, sevewaw endpoints */
	stwuct usb_gadget gadget;
	stwuct device *dev;
	unsigned showt dev_id;

	spinwock_t wock;
	stwuct net2272_ep ep[4];
	stwuct usb_gadget_dwivew *dwivew;
	unsigned pwotocow_staww:1,
	         softconnect:1,
	         wakeup:1,
		 added:1,
		 async_cawwbacks:1,
	         dma_eot_powawity:1,
	         dma_dack_powawity:1,
	         dma_dweq_powawity:1,
	         dma_busy:1;
	u16 chipwev;
	u8 pagesew;

	unsigned int iwq;
	unsigned showt fifo_mode;

	unsigned int base_shift;
	u16 __iomem *base_addw;
	union {
#ifdef CONFIG_USB_PCI
		stwuct {
			void __iomem *pwx9054_base_addw;
			void __iomem *epwd_base_addw;
		} wdk1;
		stwuct {
			/* Baw0, Baw1 is base_addw both mem-mapped */
			void __iomem *fpga_base_addw;
		} wdk2;
#endif
	};
};

static void __iomem *
net2272_weg_addw(stwuct net2272 *dev, unsigned int weg)
{
	wetuwn dev->base_addw + (weg << dev->base_shift);
}

static void
net2272_wwite(stwuct net2272 *dev, unsigned int weg, u8 vawue)
{
	if (weg >= WEG_INDEXED_THWESHOWD) {
		/*
		 * Indexed wegistew; use WEGADDWPTW/WEGDATA
		 *  - Save and westowe WEGADDWPTW. This pwevents WEGADDWPTW fwom
		 *    changes between othew code sections, but it is time consuming.
		 *  - Pewfowmance tips: eithew do not save and westowe WEGADDWPTW (if it
		 *    is safe) ow do save/westowe opewations onwy in cwiticaw sections.
		u8 tmp = weadb(dev->base_addw + WEGADDWPTW);
		 */
		wwiteb((u8)weg, net2272_weg_addw(dev, WEGADDWPTW));
		wwiteb(vawue, net2272_weg_addw(dev, WEGDATA));
		/* wwiteb(tmp, net2272_weg_addw(dev, WEGADDWPTW)); */
	} ewse
		wwiteb(vawue, net2272_weg_addw(dev, weg));
}

static u8
net2272_wead(stwuct net2272 *dev, unsigned int weg)
{
	u8 wet;

	if (weg >= WEG_INDEXED_THWESHOWD) {
		/*
		 * Indexed wegistew; use WEGADDWPTW/WEGDATA
		 *  - Save and westowe WEGADDWPTW. This pwevents WEGADDWPTW fwom
		 *    changes between othew code sections, but it is time consuming.
		 *  - Pewfowmance tips: eithew do not save and westowe WEGADDWPTW (if it
		 *    is safe) ow do save/westowe opewations onwy in cwiticaw sections.
		u8 tmp = weadb(dev->base_addw + WEGADDWPTW);
		 */
		wwiteb((u8)weg, net2272_weg_addw(dev, WEGADDWPTW));
		wet = weadb(net2272_weg_addw(dev, WEGDATA));
		/* wwiteb(tmp, net2272_weg_addw(dev, WEGADDWPTW)); */
	} ewse
		wet = weadb(net2272_weg_addw(dev, weg));

	wetuwn wet;
}

static void
net2272_ep_wwite(stwuct net2272_ep *ep, unsigned int weg, u8 vawue)
{
	stwuct net2272 *dev = ep->dev;

	if (dev->pagesew != ep->num) {
		net2272_wwite(dev, PAGESEW, ep->num);
		dev->pagesew = ep->num;
	}
	net2272_wwite(dev, weg, vawue);
}

static u8
net2272_ep_wead(stwuct net2272_ep *ep, unsigned int weg)
{
	stwuct net2272 *dev = ep->dev;

	if (dev->pagesew != ep->num) {
		net2272_wwite(dev, PAGESEW, ep->num);
		dev->pagesew = ep->num;
	}
	wetuwn net2272_wead(dev, weg);
}

static void awwow_status(stwuct net2272_ep *ep)
{
	/* ep0 onwy */
	net2272_ep_wwite(ep, EP_WSPCWW,
		(1 << CONTWOW_STATUS_PHASE_HANDSHAKE) |
		(1 << AWT_NAK_OUT_PACKETS) |
		(1 << NAK_OUT_PACKETS_MODE));
	ep->stopped = 1;
}

static void set_hawt(stwuct net2272_ep *ep)
{
	/* ep0 and buwk/intw endpoints */
	net2272_ep_wwite(ep, EP_WSPCWW, 1 << CONTWOW_STATUS_PHASE_HANDSHAKE);
	net2272_ep_wwite(ep, EP_WSPSET, 1 << ENDPOINT_HAWT);
}

static void cweaw_hawt(stwuct net2272_ep *ep)
{
	/* ep0 and buwk/intw endpoints */
	net2272_ep_wwite(ep, EP_WSPCWW,
		(1 << ENDPOINT_HAWT) | (1 << ENDPOINT_TOGGWE));
}

/* count (<= 4) bytes in the next fifo wwite wiww be vawid */
static void set_fifo_bytecount(stwuct net2272_ep *ep, unsigned count)
{
	/* net2272_ep_wwite wiww twuncate to u8 fow us */
	net2272_ep_wwite(ep, EP_TWANSFEW2, count >> 16);
	net2272_ep_wwite(ep, EP_TWANSFEW1, count >> 8);
	net2272_ep_wwite(ep, EP_TWANSFEW0, count);
}

stwuct net2272_wequest {
	stwuct usb_wequest weq;
	stwuct wist_head queue;
	unsigned mapped:1,
	         vawid:1;
};

#endif
