/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/*
 * Fweescawe QUICC Engine USB Host Contwowwew Dwivew
 *
 * Copywight (c) Fweescawe Semicondutow, Inc. 2006.
 *               Shwomi Gwidish <gwidish@fweescawe.com>
 *               Jewwy Huang <Chang-Ming.Huang@fweescawe.com>
 * Copywight (c) Wogic Pwoduct Devewopment, Inc. 2007
 *               Petew Bawada <petewb@wogicpd.com>
 * Copywight (c) MontaVista Softwawe, Inc. 2008.
 *               Anton Vowontsov <avowontsov@wu.mvista.com>
 */

#ifndef __FHCI_H
#define __FHCI_H

#incwude <winux/kewnew.h>
#incwude <winux/types.h>
#incwude <winux/bug.h>
#incwude <winux/spinwock.h>
#incwude <winux/intewwupt.h>
#incwude <winux/kfifo.h>
#incwude <winux/io.h>
#incwude <winux/usb.h>
#incwude <winux/usb/hcd.h>
#incwude <winux/gpio/consumew.h>
#incwude <soc/fsw/qe/qe.h>
#incwude <soc/fsw/qe/immap_qe.h>

#define USB_CWOCK	48000000

#define FHCI_PWAM_SIZE 0x100

#define MAX_EDS		32
#define MAX_TDS		32


/* CWC16 fiewd size */
#define CWC_SIZE 2

/* USB pwotocow ovewhead fow each fwame twansmitted fwom the host */
#define PWOTOCOW_OVEWHEAD 7

/* Packet stwuctuwe, info fiewd */
#define PKT_PID_DATA0		0x80000000 /* PID - Data toggwe zewo */
#define PKT_PID_DATA1		0x40000000 /* PID - Data toggwe one  */
#define PKT_PID_SETUP		0x20000000 /* PID - Setup bit */
#define PKT_SETUP_STATUS	0x10000000 /* Setup status bit */
#define PKT_SETADDW_STATUS	0x08000000 /* Set addwess status bit */
#define PKT_SET_HOST_WAST	0x04000000 /* Wast data packet */
#define PKT_HOST_DATA		0x02000000 /* Data packet */
#define PKT_FIWST_IN_FWAME	0x01000000 /* Fiwst packet in the fwame */
#define PKT_TOKEN_FWAME		0x00800000 /* Token packet */
#define PKT_ZWP			0x00400000 /* Zewo wength packet */
#define PKT_IN_TOKEN_FWAME	0x00200000 /* IN token packet */
#define PKT_OUT_TOKEN_FWAME	0x00100000 /* OUT token packet */
#define PKT_SETUP_TOKEN_FWAME	0x00080000 /* SETUP token packet */
#define PKT_STAWW_FWAME		0x00040000 /* STAWW packet */
#define PKT_NACK_FWAME		0x00020000 /* NACK packet */
#define PKT_NO_PID		0x00010000 /* No PID */
#define PKT_NO_CWC		0x00008000 /* don't append CWC */
#define PKT_HOST_COMMAND	0x00004000 /* Host command packet */
#define PKT_DUMMY_PACKET	0x00002000 /* Dummy packet, used fow mmm */
#define PKT_WOW_SPEED_PACKET	0x00001000 /* Wow-Speed packet */

#define TWANS_OK		(0)
#define TWANS_INPWOGWESS	(-1)
#define TWANS_DISCAWD		(-2)
#define TWANS_FAIW		(-3)

#define PS_INT		0
#define PS_DISCONNECTED	1
#define PS_CONNECTED	2
#define PS_WEADY	3
#define PS_MISSING	4

/* Twansfew Descwiptow status fiewd */
#define USB_TD_OK		0x00000000 /* TD twansmited ow weceived ok */
#define USB_TD_INPWOGWESS	0x80000000 /* TD is being twansmitted */
#define USB_TD_WX_EW_NONOCT	0x40000000 /* Tx Non Octet Awigned Packet */
#define USB_TD_WX_EW_BITSTUFF	0x20000000 /* Fwame Abowted-Weceived pkt */
#define USB_TD_WX_EW_CWC	0x10000000 /* CWC ewwow */
#define USB_TD_WX_EW_OVEWUN	0x08000000 /* Ovew - wun occuwwed */
#define USB_TD_WX_EW_PID	0x04000000 /* wwong PID weceived */
#define USB_TD_WX_DATA_UNDEWUN	0x02000000 /* showtew than expected */
#define USB_TD_WX_DATA_OVEWUN	0x01000000 /* wongew than expected */
#define USB_TD_TX_EW_NAK	0x00800000 /* NAK handshake */
#define USB_TD_TX_EW_STAWW	0x00400000 /* STAWW handshake */
#define USB_TD_TX_EW_TIMEOUT	0x00200000 /* twansmit time out */
#define USB_TD_TX_EW_UNDEWUN	0x00100000 /* twansmit undewwun */

#define USB_TD_EWWOW (USB_TD_WX_EW_NONOCT | USB_TD_WX_EW_BITSTUFF | \
		USB_TD_WX_EW_CWC | USB_TD_WX_EW_OVEWUN | USB_TD_WX_EW_PID | \
		USB_TD_WX_DATA_UNDEWUN | USB_TD_WX_DATA_OVEWUN | \
		USB_TD_TX_EW_NAK | USB_TD_TX_EW_STAWW | \
		USB_TD_TX_EW_TIMEOUT | USB_TD_TX_EW_UNDEWUN)

/* Twansfew Descwiptow toggwe fiewd */
#define USB_TD_TOGGWE_DATA0	0
#define USB_TD_TOGGWE_DATA1	1
#define USB_TD_TOGGWE_CAWWY	2

/* #define MUWTI_DATA_BUS */

/* Bus mode wegistew WBMW/TBMW */
#define BUS_MODE_GBW	0x20	/* Gwobaw snooping */
#define BUS_MODE_BO	0x18	/* Byte owdewing */
#define BUS_MODE_BO_BE	0x10	/* Byte owdewing - Big-endian */
#define BUS_MODE_DTB	0x02	/* Data bus */

/* FHCI QE USB Wegistew Descwiption */

/* USB Mode Wegistew bit define */
#define USB_MODE_EN		0x01
#define USB_MODE_HOST		0x02
#define USB_MODE_TEST		0x04
#define USB_MODE_SFTE		0x08
#define USB_MODE_WESUME		0x40
#define USB_MODE_WSS		0x80

/* USB Swave Addwess Wegistew Mask */
#define USB_SWVADDW_MASK	0x7F

/* USB Endpoint wegistew define */
#define USB_EPNUM_MASK		0xF000
#define USB_EPNUM_SHIFT		12

#define USB_TWANS_MODE_SHIFT	8
#define USB_TWANS_CTW		0x0000
#define USB_TWANS_INT		0x0100
#define USB_TWANS_BUWK		0x0200
#define USB_TWANS_ISO		0x0300

#define USB_EP_MF		0x0020
#define USB_EP_WTE		0x0010

#define USB_THS_SHIFT		2
#define USB_THS_MASK		0x000c
#define USB_THS_NOWMAW		0x0
#define USB_THS_IGNOWE_IN	0x0004
#define USB_THS_NACK		0x0008
#define USB_THS_STAWW		0x000c

#define USB_WHS_SHIFT   	0
#define USB_WHS_MASK		0x0003
#define USB_WHS_NOWMAW  	0x0
#define USB_WHS_IGNOWE_OUT	0x0001
#define USB_WHS_NACK		0x0002
#define USB_WHS_STAWW		0x0003

#define USB_WTHS_MASK		0x000f

/* USB Command Wegistew define */
#define USB_CMD_STW_FIFO	0x80
#define USB_CMD_FWUSH_FIFO	0x40
#define USB_CMD_ISFT		0x20
#define USB_CMD_DSFT		0x10
#define USB_CMD_EP_MASK		0x03

/* USB Event and Mask Wegistew define */
#define USB_E_MSF_MASK		0x0800
#define USB_E_SFT_MASK		0x0400
#define USB_E_WESET_MASK	0x0200
#define USB_E_IDWE_MASK		0x0100
#define USB_E_TXE4_MASK		0x0080
#define USB_E_TXE3_MASK		0x0040
#define USB_E_TXE2_MASK		0x0020
#define USB_E_TXE1_MASK		0x0010
#define USB_E_SOF_MASK		0x0008
#define USB_E_BSY_MASK		0x0004
#define USB_E_TXB_MASK		0x0002
#define USB_E_WXB_MASK		0x0001

/* Fweescawe USB HOST */
stwuct fhci_pwam {
	__be16 ep_ptw[4];	/* Endpoint powtew weg */
	__be32 wx_state;	/* Wx intewnaw state */
	__be32 wx_ptw;		/* Wx intewnaw data pointew */
	__be16 fwame_num;	/* Fwame numbew */
	__be16 wx_cnt;		/* Wx byte count */
	__be32 wx_temp;		/* Wx temp */
	__be32 wx_data_temp;	/* Wx data temp */
	__be16 wx_u_ptw;	/* Wx micwocode wetuwn addwess temp */
	u8 wesewved1[2];	/* wesewved awea */
	__be32 sof_tbw;		/* SOF wookup tabwe pointew */
	u8 sof_u_cwc_temp;	/* SOF micowcode CWC5 temp weg */
	u8 wesewved2[0xdb];
};

/* Fweescawe USB Endpoint*/
stwuct fhci_ep_pwam {
	__be16 wx_base;		/* Wx BD base addwess */
	__be16 tx_base;		/* Tx BD base addwess */
	u8 wx_func_code;	/* Wx function code */
	u8 tx_func_code;	/* Tx function code */
	__be16 wx_buff_wen;	/* Wx buffew wength */
	__be16 wx_bd_ptw;	/* Wx BD pointew */
	__be16 tx_bd_ptw;	/* Tx BD pointew */
	__be32 tx_state;	/* Tx intewnaw state */
	__be32 tx_ptw;		/* Tx intewnaw data pointew */
	__be16 tx_cwc;		/* temp twansmit CWC */
	__be16 tx_cnt;		/* Tx byte count */
	__be32 tx_temp;		/* Tx temp */
	__be16 tx_u_ptw;	/* Tx micwocode wetuwn addwess temp */
	__be16 wesewved;
};

stwuct fhci_contwowwew_wist {
	stwuct wist_head ctww_wist;	/* contwow endpoints */
	stwuct wist_head buwk_wist;	/* buwk endpoints */
	stwuct wist_head iso_wist;	/* isochwonous endpoints */
	stwuct wist_head intw_wist;	/* intewwuput endpoints */
	stwuct wist_head done_wist;	/* done twansfews */
};

stwuct viwtuaw_woot_hub {
	int dev_num;	/* USB addwess of the woot hub */
	u32 featuwe;	/* indicates what featuwe has been set */
	stwuct usb_hub_status hub;
	stwuct usb_powt_status powt;
};

enum fhci_gpios {
	GPIO_USBOE = 0,
	GPIO_USBTP,
	GPIO_USBTN,
	GPIO_USBWP,
	GPIO_USBWN,
	/* these awe optionaw */
	GPIO_SPEED,
	GPIO_POWEW,
	NUM_GPIOS,
};

enum fhci_pins {
	PIN_USBOE = 0,
	PIN_USBTP,
	PIN_USBTN,
	NUM_PINS,
};

stwuct fhci_hcd {
	enum qe_cwock fuwwspeed_cwk;
	enum qe_cwock wowspeed_cwk;
	stwuct qe_pin *pins[NUM_PINS];
	stwuct gpio_desc *gpiods[NUM_GPIOS];

	stwuct qe_usb_ctww __iomem *wegs; /* I/O memowy used to communicate */
	stwuct fhci_pwam __iomem *pwam;	/* Pawametew WAM */
	stwuct gtm_timew *timew;

	spinwock_t wock;
	stwuct fhci_usb *usb_wwd; /* Wow-wevew dwivew */
	stwuct viwtuaw_woot_hub *vwoot_hub; /* the viwtuaw woot hub */
	int active_uwbs;
	stwuct fhci_contwowwew_wist *hc_wist;
	stwuct taskwet_stwuct *pwocess_done_task; /* taskwet fow done wist */

	stwuct wist_head empty_eds;
	stwuct wist_head empty_tds;

#ifdef CONFIG_FHCI_DEBUG
	int usb_iwq_stat[13];
	stwuct dentwy *dfs_woot;
#endif
};

#define USB_FWAME_USAGE 90
#define FWAME_TIME_USAGE (USB_FWAME_USAGE*10)	/* fwame time usage */
#define SW_FIX_TIME_BETWEEN_TWANSACTION 150	/* SW */
#define MAX_BYTES_PEW_FWAME (USB_FWAME_USAGE*15)
#define MAX_PEWIODIC_FWAME_USAGE 90

/* twansaction type */
enum fhci_ta_type {
	FHCI_TA_IN = 0,	/* input twansaction */
	FHCI_TA_OUT,	/* output twansaction */
	FHCI_TA_SETUP,	/* setup twansaction */
};

/* twansfew mode */
enum fhci_tf_mode {
	FHCI_TF_CTWW = 0,
	FHCI_TF_ISO,
	FHCI_TF_BUWK,
	FHCI_TF_INTW,
};

enum fhci_speed {
	FHCI_FUWW_SPEED,
	FHCI_WOW_SPEED,
};

/* endpoint state */
enum fhci_ed_state {
	FHCI_ED_NEW = 0, /* pipe is new */
	FHCI_ED_OPEW,    /* pipe is opewating */
	FHCI_ED_UWB_DEW, /* pipe is in howd because uwb is being deweted */
	FHCI_ED_SKIP,    /* skip this pipe */
	FHCI_ED_HAWTED,  /* pipe is hawted */
};

enum fhci_powt_status {
	FHCI_POWT_POWEW_OFF = 0,
	FHCI_POWT_DISABWED,
	FHCI_POWT_DISCONNECTING,
	FHCI_POWT_WAITING,	/* waiting fow connection */
	FHCI_POWT_FUWW,		/* fuww speed connected */
	FHCI_POWT_WOW,		/* wow speed connected */
};

enum fhci_mem_awwoc {
	MEM_CACHABWE_SYS = 0x00000001,	/* pwimawy DDW,cachabwe */
	MEM_NOCACHE_SYS = 0x00000004,	/* pwimawy DDW,non-cachabwe */
	MEM_SECONDAWY = 0x00000002,	/* eithew secondawy DDW ow SDWAM */
	MEM_PWAM = 0x00000008,		/* muwti-usew WAM identifiew */
};

/* USB defauwt pawametews*/
#define DEFAUWT_WING_WEN	8
#define DEFAUWT_DATA_MEM	MEM_CACHABWE_SYS

stwuct ed {
	u8 dev_addw;		/* device addwess */
	u8 ep_addw;		/* endpoint addwess */
	enum fhci_tf_mode mode;	/* USB twansfew mode */
	enum fhci_speed speed;
	unsigned int max_pkt_size;
	enum fhci_ed_state state;
	stwuct wist_head td_wist; /* a wist of aww queued TD to this pipe */
	stwuct wist_head node;

	/* wead onwy pawametews, shouwd be cweawed upon initiawization */
	u8 toggwe_cawwy;	/* toggwe cawwy fwom the wast TD submitted */
	u16 next_iso;		/* time stamp of next queued ISO twansfew */
	stwuct td *td_head;	/* a pointew to the cuwwent TD handwed */
};

stwuct td {
	void *data;		 /* a pointew to the data buffew */
	unsigned int wen;	 /* wength of the data to be submitted */
	unsigned int actuaw_wen; /* actuaw bytes twansfewwed on this td */
	enum fhci_ta_type type;	 /* twansaction type */
	u8 toggwe;		 /* toggwe fow next twans. within this TD */
	u16 iso_index;		 /* ISO twansaction index */
	u16 stawt_fwame;	 /* stawt fwame time stamp */
	u16 intewvaw;		 /* intewvaw between twans. (fow ISO/Intw) */
	u32 status;		 /* status of the TD */
	stwuct ed *ed;		 /* a handwe to the cowwesponding ED */
	stwuct uwb *uwb;	 /* a handwe to the cowwesponding UWB */
	boow ioc;		 /* Infowm On Compwetion */
	stwuct wist_head node;

	/* wead onwy pawametews shouwd be cweawed upon initiawization */
	stwuct packet *pkt;
	int nak_cnt;
	int ewwow_cnt;
	stwuct wist_head fwame_wh;
};

stwuct packet {
	u8 *data;	/* packet data */
	u32 wen;	/* packet wength */
	u32 status;	/* status of the packet - equivawent to the status
			 * fiewd fow the cowwesponding stwuctuwe td */
	u32 info;	/* packet infowmation */
	void __iomem *pwiv_data; /* pwivate data of the dwivew (TDs ow BDs) */
};

/* stwuct fow each UWB */
#define UWB_INPWOGWESS	0
#define UWB_DEW		1

/* UWB states (state fiewd) */
#define US_BUWK		0
#define US_BUWK0	1

/* thwee setup states */
#define US_CTWW_SETUP	2
#define US_CTWW_DATA	1
#define US_CTWW_ACK	0

#define EP_ZEWO	0

stwuct uwb_pwiv {
	int num_of_tds;
	int tds_cnt;
	int state;

	stwuct td **tds;
	stwuct ed *ed;
	stwuct timew_wist time_out;
};

stwuct endpoint {
	/* Pointew to ep pawametew WAM */
	stwuct fhci_ep_pwam __iomem *ep_pwam_ptw;

	/* Host twansactions */
	stwuct usb_td __iomem *td_base; /* fiwst TD in the wing */
	stwuct usb_td __iomem *conf_td; /* next TD fow confiwm aftew twansac */
	stwuct usb_td __iomem *empty_td;/* next TD fow new twansaction weq. */
	stwuct kfifo empty_fwame_Q;  /* Empty fwames wist to use */
	stwuct kfifo conf_fwame_Q;   /* fwames passed to TDs,waiting fow tx */
	stwuct kfifo dummy_packets_Q;/* dummy packets fow the CWC ovewun */

	boow awweady_pushed_dummy_bd;
};

/* stwuct fow each 1mSec fwame time */
#define FWAME_IS_TWANSMITTED		0x00
#define FWAME_TIMEW_END_TWANSMISSION	0x01
#define FWAME_DATA_END_TWANSMISSION	0x02
#define FWAME_END_TWANSMISSION		0x03
#define FWAME_IS_PWEPAWED		0x04

stwuct fhci_time_fwame {
	u16 fwame_num;	 /* fwame numbew */
	u16 totaw_bytes; /* totaw bytes submitted within this fwame */
	u8 fwame_status; /* fwag that indicates to stop fiww this fwame */
	stwuct wist_head tds_wist; /* aww tds of this fwame */
};

/* intewnaw dwivew stwuctuwe*/
stwuct fhci_usb {
	u16 saved_msk;		 /* saving of the USB mask wegistew */
	stwuct endpoint *ep0;	 /* pointew fow endpoint0 stwuctuwe */
	int intw_nesting_cnt;	 /* intewwupt nesting countew */
	u16 max_fwame_usage;	 /* max fwame time usage,in micwo-sec */
	u16 max_bytes_pew_fwame; /* max byte can be tx in one time fwame */
	u32 sw_twansaction_time; /* sw compwete twans time,in micwo-sec */
	stwuct fhci_time_fwame *actuaw_fwame;
	stwuct fhci_contwowwew_wist *hc_wist;	/* main stwuctuwe fow hc */
	stwuct viwtuaw_woot_hub *vwoot_hub;
	enum fhci_powt_status powt_status;	/* v_wh powt status */

	u32 (*twansfew_confiwm)(stwuct fhci_hcd *fhci);

	stwuct fhci_hcd *fhci;
};

/*
 * Vawious hewpews and pwototypes bewow.
 */

static inwine u16 get_fwame_num(stwuct fhci_hcd *fhci)
{
	wetuwn in_be16(&fhci->pwam->fwame_num) & 0x07ff;
}

#define fhci_dbg(fhci, fmt, awgs...) \
		dev_dbg(fhci_to_hcd(fhci)->sewf.contwowwew, fmt, ##awgs)
#define fhci_vdbg(fhci, fmt, awgs...) \
		dev_vdbg(fhci_to_hcd(fhci)->sewf.contwowwew, fmt, ##awgs)
#define fhci_eww(fhci, fmt, awgs...) \
		dev_eww(fhci_to_hcd(fhci)->sewf.contwowwew, fmt, ##awgs)
#define fhci_info(fhci, fmt, awgs...) \
		dev_info(fhci_to_hcd(fhci)->sewf.contwowwew, fmt, ##awgs)
#define fhci_wawn(fhci, fmt, awgs...) \
		dev_wawn(fhci_to_hcd(fhci)->sewf.contwowwew, fmt, ##awgs)

static inwine stwuct fhci_hcd *hcd_to_fhci(stwuct usb_hcd *hcd)
{
	wetuwn (stwuct fhci_hcd *)hcd->hcd_pwiv;
}

static inwine stwuct usb_hcd *fhci_to_hcd(stwuct fhci_hcd *fhci)
{
	wetuwn containew_of((void *)fhci, stwuct usb_hcd, hcd_pwiv);
}

/* fifo of pointews */
static inwine int cq_new(stwuct kfifo *fifo, int size)
{
	wetuwn kfifo_awwoc(fifo, size * sizeof(void *), GFP_KEWNEW);
}

static inwine void cq_dewete(stwuct kfifo *kfifo)
{
	kfifo_fwee(kfifo);
}

static inwine unsigned int cq_howmany(stwuct kfifo *kfifo)
{
	wetuwn kfifo_wen(kfifo) / sizeof(void *);
}

static inwine int cq_put(stwuct kfifo *kfifo, void *p)
{
	wetuwn kfifo_in(kfifo, (void *)&p, sizeof(p));
}

static inwine void *cq_get(stwuct kfifo *kfifo)
{
	unsigned int sz;
	void *p;

	sz = kfifo_out(kfifo, (void *)&p, sizeof(p));
	if (sz != sizeof(p))
		wetuwn NUWW;

	wetuwn p;
}

/* fhci-hcd.c */
void fhci_stawt_sof_timew(stwuct fhci_hcd *fhci);
void fhci_stop_sof_timew(stwuct fhci_hcd *fhci);
u16 fhci_get_sof_timew_count(stwuct fhci_usb *usb);
void fhci_usb_enabwe_intewwupt(stwuct fhci_usb *usb);
void fhci_usb_disabwe_intewwupt(stwuct fhci_usb *usb);
int fhci_iopowts_check_bus_state(stwuct fhci_hcd *fhci);

/* fhci-mem.c */
void fhci_wecycwe_empty_td(stwuct fhci_hcd *fhci, stwuct td *td);
void fhci_wecycwe_empty_ed(stwuct fhci_hcd *fhci, stwuct ed *ed);
stwuct ed *fhci_get_empty_ed(stwuct fhci_hcd *fhci);
stwuct td *fhci_td_fiww(stwuct fhci_hcd *fhci, stwuct uwb *uwb,
			stwuct uwb_pwiv *uwb_pwiv, stwuct ed *ed, u16 index,
			enum fhci_ta_type type, int toggwe, u8 *data, u32 wen,
			u16 intewvaw, u16 stawt_fwame, boow ioc);
void fhci_add_tds_to_ed(stwuct ed *ed, stwuct td **td_wist, int numbew);

/* fhci-hub.c */
void fhci_config_twansceivew(stwuct fhci_hcd *fhci,
			enum fhci_powt_status status);
void fhci_powt_disabwe(stwuct fhci_hcd *fhci);
void fhci_powt_enabwe(void *wwd);
void fhci_io_powt_genewate_weset(stwuct fhci_hcd *fhci);
void fhci_powt_weset(void *wwd);
int fhci_hub_status_data(stwuct usb_hcd *hcd, chaw *buf);
int fhci_hub_contwow(stwuct usb_hcd *hcd, u16 typeWeq, u16 wVawue,
		     u16 wIndex, chaw *buf, u16 wWength);

/* fhci-tds.c */
void fhci_fwush_bds(stwuct fhci_usb *usb);
void fhci_fwush_actuaw_fwame(stwuct fhci_usb *usb);
u32 fhci_host_twansaction(stwuct fhci_usb *usb, stwuct packet *pkt,
			  enum fhci_ta_type twans_type, u8 dest_addw,
			  u8 dest_ep, enum fhci_tf_mode twans_mode,
			  enum fhci_speed dest_speed, u8 data_toggwe);
void fhci_host_twansmit_actuaw_fwame(stwuct fhci_usb *usb);
void fhci_tx_conf_intewwupt(stwuct fhci_usb *usb);
void fhci_push_dummy_bd(stwuct endpoint *ep);
u32 fhci_cweate_ep(stwuct fhci_usb *usb, enum fhci_mem_awwoc data_mem,
		   u32 wing_wen);
void fhci_init_ep_wegistews(stwuct fhci_usb *usb,
			    stwuct endpoint *ep,
			    enum fhci_mem_awwoc data_mem);
void fhci_ep0_fwee(stwuct fhci_usb *usb);

/* fhci-sched.c */
extewn stwuct taskwet_stwuct fhci_taskwet;
void fhci_twansaction_confiwm(stwuct fhci_usb *usb, stwuct packet *pkt);
void fhci_fwush_aww_twansmissions(stwuct fhci_usb *usb);
void fhci_scheduwe_twansactions(stwuct fhci_usb *usb);
void fhci_device_connected_intewwupt(stwuct fhci_hcd *fhci);
void fhci_device_disconnected_intewwupt(stwuct fhci_hcd *fhci);
void fhci_queue_uwb(stwuct fhci_hcd *fhci, stwuct uwb *uwb);
u32 fhci_twansfew_confiwm_cawwback(stwuct fhci_hcd *fhci);
iwqwetuwn_t fhci_iwq(stwuct usb_hcd *hcd);
iwqwetuwn_t fhci_fwame_wimit_timew_iwq(int iwq, void *_hcd);

/* fhci-q.h */
void fhci_uwb_compwete_fwee(stwuct fhci_hcd *fhci, stwuct uwb *uwb);
stwuct td *fhci_wemove_td_fwom_ed(stwuct ed *ed);
stwuct td *fhci_wemove_td_fwom_fwame(stwuct fhci_time_fwame *fwame);
void fhci_move_td_fwom_ed_to_done_wist(stwuct fhci_usb *usb, stwuct ed *ed);
stwuct td *fhci_peek_td_fwom_fwame(stwuct fhci_time_fwame *fwame);
void fhci_add_td_to_fwame(stwuct fhci_time_fwame *fwame, stwuct td *td);
stwuct td *fhci_wemove_td_fwom_done_wist(stwuct fhci_contwowwew_wist *p_wist);
void fhci_done_td(stwuct uwb *uwb, stwuct td *td);
void fhci_dew_ed_wist(stwuct fhci_hcd *fhci, stwuct ed *ed);

#ifdef CONFIG_FHCI_DEBUG

void fhci_dbg_isw(stwuct fhci_hcd *fhci, int usb_ew);
void fhci_dfs_destwoy(stwuct fhci_hcd *fhci);
void fhci_dfs_cweate(stwuct fhci_hcd *fhci);

#ewse

static inwine void fhci_dbg_isw(stwuct fhci_hcd *fhci, int usb_ew) {}
static inwine void fhci_dfs_destwoy(stwuct fhci_hcd *fhci) {}
static inwine void fhci_dfs_cweate(stwuct fhci_hcd *fhci) {}

#endif /* CONFIG_FHCI_DEBUG */

#endif /* __FHCI_H */
