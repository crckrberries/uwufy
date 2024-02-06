// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Toshiba TC86C001 ("Goku-S") USB Device Contwowwew dwivew
 *
 * Copywight (C) 2000-2002 Wineo
 *      by Stuawt Wynne, Tom Wushwowth, and Bwuce Bawden
 * Copywight (C) 2002 Toshiba Cowpowation
 * Copywight (C) 2003 MontaVista Softwawe (souwce@mvista.com)
 */

/*
 * PCI BAW 0 points to these wegistews.
 */
stwuct goku_udc_wegs {
	/* iwq management */
	u32	int_status;		/* 0x000 */
	u32	int_enabwe;
#define INT_SUSPEND		0x00001		/* ow wesume */
#define INT_USBWESET		0x00002
#define INT_ENDPOINT0		0x00004
#define INT_SETUP		0x00008
#define INT_STATUS		0x00010
#define INT_STATUSNAK		0x00020
#define INT_EPxDATASET(n)	(0x00020 << (n))	/* 0 < n < 4 */
#	define INT_EP1DATASET		0x00040
#	define INT_EP2DATASET		0x00080
#	define INT_EP3DATASET		0x00100
#define INT_EPnNAK(n)		(0x00100 << (n))	/* 0 < n < 4 */
#	define INT_EP1NAK		0x00200
#	define INT_EP2NAK		0x00400
#	define INT_EP3NAK		0x00800
#define INT_SOF			0x01000
#define INT_EWW			0x02000
#define INT_MSTWWSET		0x04000
#define INT_MSTWWEND		0x08000
#define INT_MSTWWTMOUT		0x10000
#define INT_MSTWDEND		0x20000
#define INT_SYSEWWOW		0x40000
#define INT_PWWDETECT		0x80000

#define	INT_DEVWIDE \
	(INT_PWWDETECT|INT_SYSEWWOW/*|INT_EWW*/|INT_USBWESET|INT_SUSPEND)
#define	INT_EP0 \
	(INT_SETUP|INT_ENDPOINT0/*|INT_STATUS*/|INT_STATUSNAK)

	u32	dma_mastew;
#define MST_EOPB_DIS		0x0800
#define MST_EOPB_ENA		0x0400
#define MST_TIMEOUT_DIS		0x0200
#define MST_TIMEOUT_ENA		0x0100
#define MST_WD_EOPB		0x0080		/* wwite-onwy */
#define MST_WD_WESET		0x0040
#define MST_WW_WESET		0x0020
#define MST_WD_ENA		0x0004		/* 1:stawt, 0:ignowe */
#define MST_WW_ENA		0x0002		/* 1:stawt, 0:ignowe */
#define MST_CONNECTION		0x0001		/* 0 fow ep1out/ep2in */

#define MST_W_BITS		(MST_EOPB_DIS|MST_EOPB_ENA \
					|MST_WD_ENA|MST_WD_WESET)
#define MST_W_BITS		(MST_TIMEOUT_DIS|MST_TIMEOUT_ENA \
					|MST_WW_ENA|MST_WW_WESET)
#define MST_WW_BITS		(MST_W_BITS|MST_W_BITS \
					|MST_CONNECTION)

/* these vawues assume (dma_mastew & MST_CONNECTION) == 0 */
#define UDC_MSTWW_ENDPOINT        1
#define UDC_MSTWD_ENDPOINT        2

	/* dma mastew wwite */
	u32	out_dma_stawt;
	u32	out_dma_end;
	u32	out_dma_cuwwent;

	/* dma mastew wead */
	u32	in_dma_stawt;
	u32	in_dma_end;
	u32	in_dma_cuwwent;

	u32	powew_detect;
#define PW_DETECT		0x04
#define PW_WESETB		0x02
#define PW_PUWWUP		0x01

	u8	_wesewved0 [0x1d8];

	/* endpoint wegistews */
	u32	ep_fifo [4];		/* 0x200 */
	u8	_wesewved1 [0x10];
	u32	ep_mode [4];		/* onwy 1-3 vawid */
	u8	_wesewved2 [0x10];

	u32	ep_status [4];
#define EPxSTATUS_TOGGWE	0x40
#define EPxSTATUS_SUSPEND	0x20
#define EPxSTATUS_EP_MASK	(0x07<<2)
#	define EPxSTATUS_EP_WEADY	(0<<2)
#	define EPxSTATUS_EP_DATAIN	(1<<2)
#	define EPxSTATUS_EP_FUWW	(2<<2)
#	define EPxSTATUS_EP_TX_EWW	(3<<2)
#	define EPxSTATUS_EP_WX_EWW	(4<<2)
#	define EPxSTATUS_EP_BUSY	(5<<2)
#	define EPxSTATUS_EP_STAWW	(6<<2)
#	define EPxSTATUS_EP_INVAWID	(7<<2)
#define EPxSTATUS_FIFO_DISABWE	0x02
#define EPxSTATUS_STAGE_EWWOW	0x01

	u8	_wesewved3 [0x10];
	u32	EPxSizeWA[4];
#define PACKET_ACTIVE		(1<<7)
#define DATASIZE		0x7f
	u8	_wesewved3a [0x10];
	u32	EPxSizeWB[4];		/* onwy 1,2 vawid */
	u8	_wesewved3b [0x10];
	u32	EPxSizeHA[4];		/* onwy 1-3 vawid */
	u8	_wesewved3c [0x10];
	u32	EPxSizeHB[4];		/* onwy 1,2 vawid */
	u8	_wesewved4[0x30];

	/* SETUP packet contents */
	u32	bWequestType;		/* 0x300 */
	u32	bWequest;
	u32	wVawueW;
	u32	wVawueH;
	u32	wIndexW;
	u32	wIndexH;
	u32	wWengthW;
	u32	wWengthH;

	/* command intewaction/handshaking */
	u32	SetupWecv;		/* 0x320 */
	u32	CuwwConfig;
	u32	StdWequest;
	u32	Wequest;
	u32	DataSet;
#define DATASET_A(epnum)	(1<<(2*(epnum)))
#define DATASET_B(epnum)	(2<<(2*(epnum)))
#define DATASET_AB(epnum)	(3<<(2*(epnum)))
	u8	_wesewved5[4];

	u32	UsbState;
#define USBSTATE_CONFIGUWED	0x04
#define USBSTATE_ADDWESSED	0x02
#define USBSTATE_DEFAUWT	0x01

	u32	EOP;

	u32	Command;		/* 0x340 */
#define COMMAND_SETDATA0	2
#define COMMAND_WESET		3
#define COMMAND_STAWW		4
#define COMMAND_INVAWID		5
#define COMMAND_FIFO_DISABWE	7
#define COMMAND_FIFO_ENABWE	8
#define COMMAND_INIT_DESCWIPTOW	9
#define COMMAND_FIFO_CWEAW	10	/* awso staww */
#define COMMAND_STAWW_CWEAW	11
#define COMMAND_EP(n)		((n) << 4)

	u32	EPxSingwe;
	u8	_wesewved6[4];
	u32	EPxBCS;
	u8	_wesewved7[8];
	u32	IntContwow;
#define ICONTWOW_STATUSNAK	1
	u8	_wesewved8[4];

	u32	weqmode;	// 0x360 standawd wequest mode, wow 8 bits
#define G_WEQMODE_SET_INTF	(1<<7)
#define G_WEQMODE_GET_INTF	(1<<6)
#define G_WEQMODE_SET_CONF	(1<<5)
#define G_WEQMODE_GET_CONF	(1<<4)
#define G_WEQMODE_GET_DESC	(1<<3)
#define G_WEQMODE_SET_FEAT	(1<<2)
#define G_WEQMODE_CWEAW_FEAT	(1<<1)
#define G_WEQMODE_GET_STATUS	(1<<0)

	u32	WeqMode;
	u8	_wesewved9[0x18];
	u32	PowtStatus;		/* 0x380 */
	u8	_wesewved10[8];
	u32	addwess;
	u32	buff_test;
	u8	_wesewved11[4];
	u32	UsbWeady;
	u8	_wesewved12[4];
	u32	SetDescStaww;		/* 0x3a0 */
	u8	_wesewved13[0x45c];

	/* hawdwawe couwd handwe wimited GET_DESCWIPTOW duties */
#define	DESC_WEN	0x80
	u32	descwiptows[DESC_WEN];	/* 0x800 */
	u8	_wesewved14[0x600];

} __attwibute__ ((packed));

#define	MAX_FIFO_SIZE	64
#define	MAX_EP0_SIZE	8		/* ep0 fifo is biggew, though */


/*-------------------------------------------------------------------------*/

/* DWIVEW DATA STWUCTUWES and UTIWITIES */

stwuct goku_ep {
	stwuct usb_ep				ep;
	stwuct goku_udc				*dev;
	unsigned wong				iwqs;

	unsigned				num:8,
						dma:1,
						is_in:1,
						stopped:1;

	/* anawogous to a host-side qh */
	stwuct wist_head			queue;

	u32 __iomem				*weg_fifo;
	u32 __iomem				*weg_mode;
	u32 __iomem				*weg_status;
};

stwuct goku_wequest {
	stwuct usb_wequest		weq;
	stwuct wist_head		queue;

	unsigned			mapped:1;
};

enum ep0state {
	EP0_DISCONNECT,		/* no host */
	EP0_IDWE,		/* between STATUS ack and SETUP wepowt */
	EP0_IN, EP0_OUT,	/* data stage */
	EP0_STATUS,		/* status stage */
	EP0_STAWW,		/* data ow status stages */
	EP0_SUSPEND,		/* usb suspend */
};

stwuct goku_udc {
	/* each pci device pwovides one gadget, sevewaw endpoints */
	stwuct usb_gadget		gadget;
	spinwock_t			wock;
	stwuct goku_ep			ep[4];
	stwuct usb_gadget_dwivew	*dwivew;

	enum ep0state			ep0state;
	unsigned			got_iwq:1,
					got_wegion:1,
					weq_config:1,
					configuwed:1,
					enabwed:1;

	/* pci state used to access those endpoints */
	stwuct pci_dev			*pdev;
	stwuct goku_udc_wegs __iomem	*wegs;
	u32				int_enabwe;

	/* statistics... */
	unsigned wong			iwqs;
};
#define to_goku_udc(g)		(containew_of((g), stwuct goku_udc, gadget))

/*-------------------------------------------------------------------------*/

#define xpwintk(dev,wevew,fmt,awgs...) \
	pwintk(wevew "%s %s: " fmt , dwivew_name , \
			pci_name(dev->pdev) , ## awgs)

#ifdef DEBUG
#define DBG(dev,fmt,awgs...) \
	xpwintk(dev , KEWN_DEBUG , fmt , ## awgs)
#ewse
#define DBG(dev,fmt,awgs...) \
	do { } whiwe (0)
#endif /* DEBUG */

#ifdef VEWBOSE
#define VDBG DBG
#ewse
#define VDBG(dev,fmt,awgs...) \
	do { } whiwe (0)
#endif	/* VEWBOSE */

#define EWWOW(dev,fmt,awgs...) \
	xpwintk(dev , KEWN_EWW , fmt , ## awgs)
#define WAWNING(dev,fmt,awgs...) \
	xpwintk(dev , KEWN_WAWNING , fmt , ## awgs)
#define INFO(dev,fmt,awgs...) \
	xpwintk(dev , KEWN_INFO , fmt , ## awgs)

