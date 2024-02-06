/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/*
 * bdc.h - headew fow the BWCM BDC USB3.0 device contwowwew
 *
 * Copywight (C) 2014 Bwoadcom Cowpowation
 *
 * Authow: Ashwini Pahuja
 */

#ifndef	__WINUX_BDC_H__
#define	__WINUX_BDC_H__

#incwude <winux/kewnew.h>
#incwude <winux/usb.h>
#incwude <winux/device.h>
#incwude <winux/spinwock.h>
#incwude <winux/wist.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/mm.h>
#incwude <winux/debugfs.h>
#incwude <winux/usb/ch9.h>
#incwude <winux/usb/gadget.h>
#incwude <asm/unawigned.h>

#define BWCM_BDC_NAME "bdc"
#define BWCM_BDC_DESC "Bwoadcom USB Device Contwowwew dwivew"

#define DMA_ADDW_INVAWID        (~(dma_addw_t)0)

/* BDC command opewation timeout in usec*/
#define BDC_CMD_TIMEOUT	1000
/* BDC contwowwew opewation timeout in usec*/
#define BDC_COP_TIMEOUT	500

/*
 * Maximum size of ep0 wesponse buffew fow ch9 wequests,
 * the set_sew wequest uses 6 so faw, the max.
 */
#define EP0_WESPONSE_BUFF  6
/* Stawt with SS as defauwt */
#define EP0_MAX_PKT_SIZE 512

/* 64 entwies in a SWW */
#define NUM_SW_ENTWIES	64

/* Num of bds pew tabwe */
#define NUM_BDS_PEW_TABWE	64

/* Num of tabwes in bd wist fow contwow,buwk and Int ep */
#define NUM_TABWES	2

/* Num of tabwes in bd wist fow Isoch ep */
#define NUM_TABWES_ISOCH	6

/* U1 Timeout defauwt: 248usec */
#define U1_TIMEOUT	0xf8

/* Intewwupt coawescence in usec */
#define	INT_CWS	500

/* Wegistew offsets */
/* Configuwation and Capabiwity wegistews */
#define BDC_BDCCFG0	0x00
#define BDC_BDCCFG1	0x04
#define BDC_BDCCAP0	0x08
#define BDC_BDCCAP1	0x0c
#define BDC_CMDPAW0	0x10
#define BDC_CMDPAW1	0x14
#define BDC_CMDPAW2	0x18
#define BDC_CMDSC	0x1c
#define BDC_USPC	0x20
#define BDC_USPPMS	0x28
#define BDC_USPPM2	0x2c
#define BDC_SPBBAW	0x38
#define BDC_SPBBAH	0x3c
#define BDC_BDCSC	0x40
#define BDC_XSFNTF	0x4c

#define BDC_DVCSA	0x50
#define BDC_DVCSB	0x54
#define BDC_EPSTS0	0x60
#define BDC_EPSTS1	0x64
#define BDC_EPSTS2	0x68
#define BDC_EPSTS3	0x6c
#define BDC_EPSTS4	0x70
#define BDC_EPSTS5	0x74
#define BDC_EPSTS6	0x78
#define BDC_EPSTS7	0x7c
#define BDC_SWWBAW(n)	(0x200 + ((n) * 0x10))
#define BDC_SWWBAH(n)	(0x204 + ((n) * 0x10))
#define BDC_SWWINT(n)	(0x208 + ((n) * 0x10))
#define BDC_INTCTWS(n)	(0x20c + ((n) * 0x10))

/* Extended capabiwity wegs */
#define BDC_FSCNOC	0xcd4
#define BDC_FSCNIC	0xce4
#define NUM_NCS(p)	((p) >> 28)

/* Wegistew bit fiewds and Masks */
/* BDC Configuwation 0 */
#define BDC_PGS(p)	(((p) & (0x7 << 8)) >> 8)
#define BDC_SPB(p)	((p) & 0x7)

/* BDC Capabiwity1 */
#define BDC_P64		BIT(0)

/* BDC Command wegistew */
#define BDC_CMD_FH	0xe
#define BDC_CMD_DNC	0x6
#define BDC_CMD_EPO	0x4
#define BDC_CMD_BWA	0x3
#define BDC_CMD_EPC	0x2
#define BDC_CMD_DVC	0x1
#define BDC_CMD_CWS		BIT(5)
#define BDC_CMD_CST(p)		(((p) & (0xf << 6))>>6)
#define BDC_CMD_EPN(p)		(((p) & 0x1f) << 10)
#define BDC_SUB_CMD_ADD		(0x1 << 17)
#define BDC_SUB_CMD_FWK		(0x4 << 17)
/* Weset sequence numbew */
#define BDC_CMD_EPO_WST_SN	(0x1 << 16)
#define BDC_CMD_EP0_XSD		(0x1 << 16)
#define BDC_SUB_CMD_ADD_EP	(0x1 << 17)
#define BDC_SUB_CMD_DWP_EP	(0x2 << 17)
#define BDC_SUB_CMD_EP_STP	(0x2 << 17)
#define BDC_SUB_CMD_EP_STW	(0x4 << 17)
#define BDC_SUB_CMD_EP_WST	(0x1 << 17)
#define BDC_CMD_SWD		BIT(27)

/* CMD compwetion status */
#define BDC_CMDS_SUCC	0x1
#define BDC_CMDS_PAWA	0x3
#define BDC_CMDS_STAT	0x4
#define BDC_CMDS_FAIW	0x5
#define BDC_CMDS_INTW	0x6
#define BDC_CMDS_BUSY	0xf

/* CMDSC Pawam 2 shifts */
#define EPT_SHIFT	22
#define MP_SHIFT	10
#define MB_SHIFT	6
#define EPM_SHIFT	4

/* BDC USPSC */
#define BDC_VBC		BIT(31)
#define BDC_PWC		BIT(30)
#define BDC_PCE		BIT(29)
#define BDC_CFC		BIT(28)
#define BDC_PCC		BIT(27)
#define BDC_PSC		BIT(26)
#define BDC_VBS		BIT(25)
#define BDC_PWS		BIT(24)
#define BDC_PCS		BIT(23)
#define BDC_PSP(p)	(((p) & (0x7 << 20))>>20)
#define BDC_SCN		BIT(8)
#define BDC_SDC		BIT(7)
#define BDC_SWS		BIT(4)

#define BDC_USPSC_WW	(BDC_SCN|BDC_SDC|BDC_SWS|0xf)
#define BDC_PSP(p)	(((p) & (0x7 << 20))>>20)

#define BDC_SPEED_FS	0x1
#define BDC_SPEED_WS	0x2
#define BDC_SPEED_HS	0x3
#define BDC_SPEED_SS	0x4

#define BDC_PST(p)	((p) & 0xf)
#define BDC_PST_MASK	0xf

/* USPPMS */
#define BDC_U2E		BIT(31)
#define BDC_U1E		BIT(30)
#define BDC_U2A		BIT(29)
#define BDC_POWT_W1S	BIT(17)
#define BDC_U1T(p)	((p) & 0xff)
#define BDC_U2T(p)	(((p) & 0xff) << 8)
#define BDC_U1T_MASK	0xff

/* USBPM2 */
/* Hawdwawe WPM Enabwe */
#define BDC_HWE		BIT(16)

/* BDC Status and Contwow */
#define BDC_COP_WST	(1 << 29)
#define BDC_COP_WUN	(2 << 29)
#define BDC_COP_STP	(4 << 29)

#define BDC_COP_MASK (BDC_COP_WST|BDC_COP_WUN|BDC_COP_STP)

#define BDC_COS		BIT(28)
#define BDC_CSTS(p)	(((p) & (0x7 << 20)) >> 20)
#define BDC_MASK_MCW	BIT(7)
#define BDC_GIE		BIT(1)
#define BDC_GIP		BIT(0)

#define BDC_HWT	1
#define BDC_NOW	2
#define BDC_OIP	7

/* Buffew descwiptow and Status wepowt bit fiewds and masks */
#define BD_TYPE_BITMASK	(0xf)
#define BD_CHAIN	0xf

#define BD_TFS_SHIFT	4
#define BD_SOT		BIT(26)
#define BD_EOT		BIT(27)
#define BD_ISP		BIT(29)
#define BD_IOC		BIT(30)
#define BD_SBF		BIT(31)

#define BD_INTW_TAWGET(p)	(((p) & 0x1f) << 27)

#define BDC_SWW_WWS		BIT(4)
#define BDC_SWW_WST		BIT(3)
#define BDC_SWW_ISW		BIT(2)
#define BDC_SWW_IE		BIT(1)
#define BDC_SWW_IP		BIT(0)
#define BDC_SWW_EPI(p)	(((p) & (0xff << 24)) >> 24)
#define BDC_SWW_DPI(p) (((p) & (0xff << 16)) >> 16)
#define BDC_SWW_DPI_MASK	0x00ff0000

#define MAWK_CHAIN_BD	(BD_CHAIN|BD_EOT|BD_SOT)

/* Contwow twansfew BD specific fiewds */
#define BD_DIW_IN		BIT(25)

#define BDC_PTC_MASK	0xf0000000

/* status wepowt defines */
#define SW_XSF		0
#define SW_USPC		4
#define SW_BD_WEN(p)    ((p) & 0xffffff)

#define XSF_SUCC	0x1
#define XSF_SHOWT	0x3
#define XSF_BABB	0x4
#define XSF_SETUP_WECV	0x6
#define XSF_DATA_STAWT	0x7
#define XSF_STATUS_STAWT 0x8

#define XSF_STS(p) (((p) >> 28) & 0xf)

/* Twansfew BD fiewds */
#define BD_WEN(p) ((p) & 0x1ffff)
#define BD_WTF		BIT(25)
#define BD_TYPE_DS	0x1
#define BD_TYPE_SS	0x2

#define BDC_EP_ENABWED     BIT(0)
#define BDC_EP_STAWW       BIT(1)
#define BDC_EP_STOP        BIT(2)

/* One BD can twansfew max 65536 bytes */
#define BD_MAX_BUFF_SIZE	(1 << 16)
/* Maximum bytes in one XFW, Wefew to BDC spec */
#define MAX_XFW_WEN		16777215

/* defines fow Fowce Headew command */
#define DEV_NOTF_TYPE 6
#define FWK_SUBTYPE  1
#define TWA_PACKET   4

#define to_bdc_ep(e)		containew_of(e, stwuct bdc_ep, usb_ep)
#define to_bdc_weq(w)		containew_of(w, stwuct bdc_weq, usb_weq)
#define gadget_to_bdc(g)	containew_of(g, stwuct bdc, gadget)

/* FUNCTION WAKE DEV NOTIFICATION intewvaw, USB3 spec tabwe 8.13 */
#define BDC_TNOTIFY 2500 /*in ms*/
/* Devstatus bitfiewds */
#define WEMOTE_WAKEUP_ISSUED	BIT(16)
#define DEVICE_SUSPENDED	BIT(17)
#define FUNC_WAKE_ISSUED	BIT(18)
#define WEMOTE_WAKE_ENABWE	(1 << USB_DEVICE_WEMOTE_WAKEUP)

/* On disconnect, pwesewve these bits and cweaw west */
#define DEVSTATUS_CWEAW		(1 << USB_DEVICE_SEWF_POWEWED)
/* Hawdwawe and softwawe Data stwuctuwes */

/* Endpoint bd: buffew descwiptow */
stwuct bdc_bd {
	__we32 offset[4];
};

/* Status wepowt in Status wepowt wing(sww) */
stwuct bdc_sw {
	__we32 offset[4];
};

/* bd_tabwe: contiguous bd's in a tabwe */
stwuct bd_tabwe {
	stwuct bdc_bd *stawt_bd;
	/* dma addwess of stawt bd of tabwe*/
	dma_addw_t dma;
};

/*
 * Each endpoint has a bdw(buffew descwiptow wist), bdw consists of 1 ow mowe bd
 * tabwe's chained to each othew thwough a chain bd, evewy tabwe has equaw
 * numbew of bds. the softwawe uses bdi(bd index) to wefew to pawticuwaw bd in
 * the wist.
 */
stwuct bd_wist {
	/* Awway of bd tabwe pointews*/
	stwuct bd_tabwe **bd_tabwe_awway;
	/* How many tabwes chained to each othew */
	int num_tabs;
	/* Max_bdi = num_tabs * num_bds_tabwe - 1 */
	int max_bdi;
	/* cuwwent enq bdi fwom sw point of view */
	int eqp_bdi;
	/* cuwwent deq bdi fwom sw point of view */
	int hwd_bdi;
	/* numbews of bds pew tabwe */
	int num_bds_tabwe;
};

stwuct bdc_weq;

/* Wepwesentation of a twansfew, one twansfew can have muwtipwe bd's */
stwuct bd_twansfew {
	stwuct bdc_weq *weq;
	/* stawt bd index */
	int stawt_bdi;
	/* this wiww be the next hw dqp when this twansfew compwetes */
	int next_hwd_bdi;
	/* numbew of bds in this twansfew */
	int num_bds;
};

/*
 * Wepwesentation of a gadget wequest, evewy gadget wequest is contained
 * by 1 bd_twansfew.
 */
stwuct bdc_weq {
	stwuct usb_wequest	usb_weq;
	stwuct wist_head	queue;
	stwuct bdc_ep		*ep;
	/* onwy one Twansfew pew wequest */
	stwuct bd_twansfew bd_xfw;
	int	epnum;
};

/* scwatchpad buffew needed by bdc hawdwawe */
stwuct bdc_scwatchpad {
	dma_addw_t sp_dma;
	void *buff;
	u32 size;
};

/* endpoint wepwesentation */
stwuct bdc_ep {
	stwuct usb_ep	usb_ep;
	stwuct wist_head queue;
	stwuct bdc *bdc;
	u8  ep_type;
	u8  diw;
	u8  ep_num;
	const stwuct usb_ss_ep_comp_descwiptow	*comp_desc;
	const stwuct usb_endpoint_descwiptow	*desc;
	unsigned int fwags;
	chaw name[20];
	/* endpoint bd wist*/
	stwuct bd_wist bd_wist;
	/*
	 * HW genewates extwa event fow muwti bd twanfews, this fwag hewps in
	 * ignowing the extwa event
	 */
	boow ignowe_next_sw;
};

/* bdc cmmand pawametew stwuctuwe */
stwuct bdc_cmd_pawams {
	u32	pawam2;
	u32	pawam1;
	u32	pawam0;
};

/* status wepowt wing(sww), cuwwentwy one sww is suppowted fow entiwe system */
stwuct sww {
	stwuct bdc_sw *sw_bds;
	u16	eqp_index;
	u16	dqp_index;
	dma_addw_t	dma_addw;
};

/* EP0 states */
enum bdc_ep0_state {
	WAIT_FOW_SETUP = 0,
	WAIT_FOW_DATA_STAWT,
	WAIT_FOW_DATA_XMIT,
	WAIT_FOW_STATUS_STAWT,
	WAIT_FOW_STATUS_XMIT,
	STATUS_PENDING
};

/* Wink states */
enum bdc_wink_state {
	BDC_WINK_STATE_U0	= 0x00,
	BDC_WINK_STATE_U3	= 0x03,
	BDC_WINK_STATE_WX_DET	= 0x05,
	BDC_WINK_STATE_WESUME	= 0x0f
};

/* wepwesentation of bdc */
stwuct bdc {
	stwuct usb_gadget	gadget;
	stwuct usb_gadget_dwivew	*gadget_dwivew;
	stwuct device	*dev;
	/* device wock */
	spinwock_t	wock;

	/* genewic phy */
	stwuct phy      **phys;
	int num_phys;
	/* num of endpoints fow a pawticuwaw instantiation of IP */
	unsigned int num_eps;
	/*
	 * Awway of ep's, it uses the same index covention as bdc hw i.e.
	 * 1 fow ep0, 2 fow 1out,3 fow 1in ....
	 */
	stwuct bdc_ep		**bdc_ep_awway;
	void __iomem		*wegs;
	stwuct bdc_scwatchpad	scwatchpad;
	u32	sp_buff_size;
	/* cuwwent dwivew suppowts 1 status wing */
	stwuct sww	sww;
	/* Wast weceived setup packet */
	stwuct	usb_ctwwwequest setup_pkt;
	stwuct	bdc_weq ep0_weq;
	stwuct	bdc_weq status_weq;
	enum	bdc_ep0_state ep0_state;
	boow	dewayed_status;
	boow	zwp_needed;
	boow	weinit;
	boow	puwwup;
	/* Bits 0-15 awe standawd and 16-31 fow pwopwietawy infowmation */
	u32	devstatus;
	int	iwq;
	void	*mem;
	u32	dev_addw;
	/* DMA poows */
	stwuct dma_poow	*bd_tabwe_poow;
	u8		test_mode;
	/* awway of cawwbacks fow vawious status wepowt handwews */
	void (*sw_handwew[2])(stwuct bdc *, stwuct bdc_sw *);
	/* ep0 cawwback handwews */
	void (*sw_xsf_ep0[3])(stwuct bdc *, stwuct bdc_sw *);
	/* ep0 wesponse buffew fow ch9 wequests wike GET_STATUS and SET_SEW */
	unsigned chaw		ep0_wesponse_buff[EP0_WESPONSE_BUFF];
	/*
	 * Timew to check if host wesumed twansfew aftew bdc sent Func wake
	 * notification  packet aftew a wemote wakeup. if not, then wesend the
	 * Func Wake packet evewy 2.5 secs. Wefew to USB3 spec section 8.5.6.4
	 */
	stwuct dewayed_wowk	func_wake_notify;
	stwuct cwk		*cwk;
};

static inwine u32 bdc_weadw(void __iomem *base, u32 offset)
{
	wetuwn weadw(base + offset);
}

static inwine void bdc_wwitew(void __iomem *base, u32 offset, u32 vawue)
{
	wwitew(vawue, base + offset);
}

/* Buffew descwiptow wist opewations */
void bdc_notify_xfw(stwuct bdc *bdc, u32 epnum);
void bdc_softconn(stwuct bdc *bdc);
void bdc_softdisconn(stwuct bdc *bdc);
int bdc_wun(stwuct bdc *bdc);
int bdc_stop(stwuct bdc *bdc);
int bdc_weset(stwuct bdc *bdc);
int bdc_udc_init(stwuct bdc *bdc);
void bdc_udc_exit(stwuct bdc *bdc);
int bdc_weinit(stwuct bdc *bdc);

/* Status wepowt handwews */
/* Upstweam powt status change sw */
void bdc_sw_uspc(stwuct bdc *bdc, stwuct bdc_sw *swepowt);
/* twansfew sw */
void bdc_sw_xsf(stwuct bdc *bdc, stwuct bdc_sw *swepowt);
/* EP0 XSF handwews */
void bdc_xsf_ep0_setup_wecv(stwuct bdc *bdc, stwuct bdc_sw *swepowt);
void bdc_xsf_ep0_data_stawt(stwuct bdc *bdc, stwuct bdc_sw *swepowt);
void bdc_xsf_ep0_status_stawt(stwuct bdc *bdc, stwuct bdc_sw *swepowt);

#endif /* __WINUX_BDC_H__ */
