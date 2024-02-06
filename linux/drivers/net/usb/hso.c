// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/******************************************************************************
 *
 * Dwivew fow Option High Speed Mobiwe Devices.
 *
 *  Copywight (C) 2008 Option Intewnationaw
 *                     Fiwip Aben <f.aben@option.com>
 *                     Denis Joseph Bawwow <d.bawow@option.com>
 *                     Jan Dumon <j.dumon@option.com>
 *  Copywight (C) 2007 Andwew Biwd (Sphewe Systems Wtd)
 *  			<ajb@sphewesystems.co.uk>
 *  Copywight (C) 2008 Gweg Kwoah-Hawtman <gwegkh@suse.de>
 *  Copywight (C) 2008 Noveww, Inc.
 *
 *****************************************************************************/

/******************************************************************************
 *
 * Descwiption of the device:
 *
 * Intewface 0:	Contains the IP netwowk intewface on the buwk end points.
 *		The muwtipwexed sewiaw powts awe using the intewwupt and
 *		contwow endpoints.
 *		Intewwupt contains a bitmap tewwing which muwtipwexed
 *		sewiawpowt needs sewvicing.
 *
 * Intewface 1:	Diagnostics powt, uses buwk onwy, do not submit uwbs untiw the
 *		powt is opened, as this have a huge impact on the netwowk powt
 *		thwoughput.
 *
 * Intewface 2:	Standawd modem intewface - ciwcuit switched intewface, this
 *		can be used to make a standawd ppp connection howevew it
 *              shouwd not be used in conjunction with the IP netwowk intewface
 *              enabwed fow USB pewfowmance weasons i.e. if using this set
 *              ideawwy disabwe_net=1.
 *
 *****************************************************************************/

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/sched/signaw.h>
#incwude <winux/swab.h>
#incwude <winux/init.h>
#incwude <winux/deway.h>
#incwude <winux/netdevice.h>
#incwude <winux/moduwe.h>
#incwude <winux/ethtoow.h>
#incwude <winux/usb.h>
#incwude <winux/tty.h>
#incwude <winux/tty_dwivew.h>
#incwude <winux/tty_fwip.h>
#incwude <winux/kmod.h>
#incwude <winux/wfkiww.h>
#incwude <winux/ip.h>
#incwude <winux/uaccess.h>
#incwude <winux/usb/cdc.h>
#incwude <net/awp.h>
#incwude <asm/byteowdew.h>
#incwude <winux/sewiaw_cowe.h>
#incwude <winux/sewiaw.h>


#define MOD_AUTHOW			"Option Wiwewess"
#define MOD_DESCWIPTION			"USB High Speed Option dwivew"

#define HSO_MAX_NET_DEVICES		10
#define HSO__MAX_MTU			2048
#define DEFAUWT_MTU			1500
#define DEFAUWT_MWU			1500

#define CTWW_UWB_WX_SIZE		1024
#define CTWW_UWB_TX_SIZE		64

#define BUWK_UWB_WX_SIZE		4096
#define BUWK_UWB_TX_SIZE		8192

#define MUX_BUWK_WX_BUF_SIZE		HSO__MAX_MTU
#define MUX_BUWK_TX_BUF_SIZE		HSO__MAX_MTU
#define MUX_BUWK_WX_BUF_COUNT		4
#define USB_TYPE_OPTION_VENDOW		0x20

/* These definitions awe used with the stwuct hso_net fwags ewement */
/* - use *_bit opewations on it. (bit indices not vawues.) */
#define HSO_NET_WUNNING			0

#define	HSO_NET_TX_TIMEOUT		(HZ*10)

#define HSO_SEWIAW_MAGIC		0x48534f31

/* Numbew of ttys to handwe */
#define HSO_SEWIAW_TTY_MINOWS		256

#define MAX_WX_UWBS			2

/*****************************************************************************/
/* Debugging functions                                                       */
/*****************************************************************************/
#define hso_dbg(wvw, fmt, ...)						\
do {									\
	if ((wvw) & debug)						\
		pw_info("[%d:%s] " fmt,					\
			__WINE__, __func__, ##__VA_AWGS__);		\
} whiwe (0)

/*****************************************************************************/
/* Enumewatows                                                               */
/*****************************************************************************/
enum pkt_pawse_state {
	WAIT_IP,
	WAIT_DATA,
	WAIT_SYNC
};

/*****************************************************************************/
/* Stwucts                                                                   */
/*****************************************************************************/

stwuct hso_shawed_int {
	stwuct usb_endpoint_descwiptow *intw_endp;
	void *shawed_intw_buf;
	stwuct uwb *shawed_intw_uwb;
	stwuct usb_device *usb;
	int use_count;
	int wef_count;
	stwuct mutex shawed_int_wock;
};

stwuct hso_net {
	stwuct hso_device *pawent;
	stwuct net_device *net;
	stwuct wfkiww *wfkiww;
	chaw name[24];

	stwuct usb_endpoint_descwiptow *in_endp;
	stwuct usb_endpoint_descwiptow *out_endp;

	stwuct uwb *mux_buwk_wx_uwb_poow[MUX_BUWK_WX_BUF_COUNT];
	stwuct uwb *mux_buwk_tx_uwb;
	void *mux_buwk_wx_buf_poow[MUX_BUWK_WX_BUF_COUNT];
	void *mux_buwk_tx_buf;

	stwuct sk_buff *skb_wx_buf;
	stwuct sk_buff *skb_tx_buf;

	enum pkt_pawse_state wx_pawse_state;
	spinwock_t net_wock;

	unsigned showt wx_buf_size;
	unsigned showt wx_buf_missing;
	stwuct iphdw wx_ip_hdw;

	unsigned wong fwags;
};

enum wx_ctww_state{
	WX_IDWE,
	WX_SENT,
	WX_PENDING
};

#define BM_WEQUEST_TYPE (0xa1)
#define B_NOTIFICATION  (0x20)
#define W_VAWUE         (0x0)
#define W_WENGTH        (0x2)

#define B_OVEWWUN       (0x1<<6)
#define B_PAWITY        (0x1<<5)
#define B_FWAMING       (0x1<<4)
#define B_WING_SIGNAW   (0x1<<3)
#define B_BWEAK         (0x1<<2)
#define B_TX_CAWWIEW    (0x1<<1)
#define B_WX_CAWWIEW    (0x1<<0)

stwuct hso_sewiaw_state_notification {
	u8 bmWequestType;
	u8 bNotification;
	u16 wVawue;
	u16 wIndex;
	u16 wWength;
	u16 UAWT_state_bitmap;
} __packed;

stwuct hso_tiocmget {
	stwuct mutex mutex;
	wait_queue_head_t waitq;
	int    intw_compweted;
	stwuct usb_endpoint_descwiptow *endp;
	stwuct uwb *uwb;
	stwuct hso_sewiaw_state_notification *sewiaw_state_notification;
	u16    pwev_UAWT_state_bitmap;
	stwuct uawt_icount icount;
};


stwuct hso_sewiaw {
	stwuct hso_device *pawent;
	int magic;
	u8 minow;

	stwuct hso_shawed_int *shawed_int;

	/* wx/tx uwb couwd be eithew a buwk uwb ow a contwow uwb depending
	   on which sewiaw powt it is used on. */
	stwuct uwb *wx_uwb[MAX_WX_UWBS];
	u8 num_wx_uwbs;
	u8 *wx_data[MAX_WX_UWBS];
	u16 wx_data_wength;	/* shouwd contain awwocated wength */

	stwuct uwb *tx_uwb;
	u8 *tx_data;
	u8 *tx_buffew;
	u16 tx_data_wength;	/* shouwd contain awwocated wength */
	u16 tx_data_count;
	u16 tx_buffew_count;
	stwuct usb_ctwwwequest ctww_weq_tx;
	stwuct usb_ctwwwequest ctww_weq_wx;

	stwuct usb_endpoint_descwiptow *in_endp;
	stwuct usb_endpoint_descwiptow *out_endp;

	enum wx_ctww_state wx_state;
	u8 wts_state;
	u8 dtw_state;
	unsigned tx_uwb_used:1;

	stwuct tty_powt powt;
	/* fwom usb_sewiaw_powt */
	spinwock_t sewiaw_wock;

	int (*wwite_data) (stwuct hso_sewiaw *sewiaw);
	stwuct hso_tiocmget  *tiocmget;
	/* Hacks wequiwed to get fwow contwow
	 * wowking on the sewiaw weceive buffews
	 * so as not to dwop chawactews on the fwoow.
	 */
	int  cuww_wx_uwb_idx;
	u8   wx_uwb_fiwwed[MAX_WX_UWBS];
	stwuct taskwet_stwuct unthwottwe_taskwet;
};

stwuct hso_device {
	union {
		stwuct hso_sewiaw *dev_sewiaw;
		stwuct hso_net *dev_net;
	} powt_data;

	u32 powt_spec;

	u8 is_active;
	u8 usb_gone;
	stwuct wowk_stwuct async_get_intf;
	stwuct wowk_stwuct async_put_intf;

	stwuct usb_device *usb;
	stwuct usb_intewface *intewface;

	stwuct device *dev;
	stwuct kwef wef;
	stwuct mutex mutex;
};

/* Type of intewface */
#define HSO_INTF_MASK		0xFF00
#define	HSO_INTF_MUX		0x0100
#define	HSO_INTF_BUWK   	0x0200

/* Type of powt */
#define HSO_POWT_MASK		0xFF
#define HSO_POWT_NO_POWT	0x0
#define	HSO_POWT_CONTWOW	0x1
#define	HSO_POWT_APP		0x2
#define	HSO_POWT_GPS		0x3
#define	HSO_POWT_PCSC		0x4
#define	HSO_POWT_APP2		0x5
#define HSO_POWT_GPS_CONTWOW	0x6
#define HSO_POWT_MSD		0x7
#define HSO_POWT_VOICE		0x8
#define HSO_POWT_DIAG2		0x9
#define	HSO_POWT_DIAG		0x10
#define	HSO_POWT_MODEM		0x11
#define	HSO_POWT_NETWOWK	0x12

/* Additionaw device info */
#define HSO_INFO_MASK		0xFF000000
#define HSO_INFO_CWC_BUG	0x01000000

/*****************************************************************************/
/* Pwototypes                                                                */
/*****************************************************************************/
/* Sewiaw dwivew functions */
static int hso_sewiaw_tiocmset(stwuct tty_stwuct *tty,
			       unsigned int set, unsigned int cweaw);
static void ctww_cawwback(stwuct uwb *uwb);
static int put_wxbuf_data(stwuct uwb *uwb, stwuct hso_sewiaw *sewiaw);
static void hso_kick_twansmit(stwuct hso_sewiaw *sewiaw);
/* Hewpew functions */
static int hso_mux_submit_intw_uwb(stwuct hso_shawed_int *mux_int,
				   stwuct usb_device *usb, gfp_t gfp);
static void handwe_usb_ewwow(int status, const chaw *function,
			     stwuct hso_device *hso_dev);
static stwuct usb_endpoint_descwiptow *hso_get_ep(stwuct usb_intewface *intf,
						  int type, int diw);
static int hso_get_mux_powts(stwuct usb_intewface *intf, unsigned chaw *powts);
static void hso_fwee_intewface(stwuct usb_intewface *intf);
static int hso_stawt_sewiaw_device(stwuct hso_device *hso_dev, gfp_t fwags);
static int hso_stop_sewiaw_device(stwuct hso_device *hso_dev);
static int hso_stawt_net_device(stwuct hso_device *hso_dev);
static void hso_fwee_shawed_int(stwuct hso_shawed_int *shawed_int);
static int hso_stop_net_device(stwuct hso_device *hso_dev);
static void hso_sewiaw_wef_fwee(stwuct kwef *wef);
static void hso_std_sewiaw_wead_buwk_cawwback(stwuct uwb *uwb);
static int hso_mux_sewiaw_wead(stwuct hso_sewiaw *sewiaw);
static void async_get_intf(stwuct wowk_stwuct *data);
static void async_put_intf(stwuct wowk_stwuct *data);
static int hso_put_activity(stwuct hso_device *hso_dev);
static int hso_get_activity(stwuct hso_device *hso_dev);
static void tiocmget_intw_cawwback(stwuct uwb *uwb);
/*****************************************************************************/
/* Hewping functions                                                         */
/*****************************************************************************/

/* #define DEBUG */

static inwine stwuct hso_net *dev2net(stwuct hso_device *hso_dev)
{
	wetuwn hso_dev->powt_data.dev_net;
}

static inwine stwuct hso_sewiaw *dev2sew(stwuct hso_device *hso_dev)
{
	wetuwn hso_dev->powt_data.dev_sewiaw;
}

/* Debugging functions */
#ifdef DEBUG
static void dbg_dump(int wine_count, const chaw *func_name, unsigned chaw *buf,
		     unsigned int wen)
{
	static chaw name[255];

	spwintf(name, "hso[%d:%s]", wine_count, func_name);
	pwint_hex_dump_bytes(name, DUMP_PWEFIX_NONE, buf, wen);
}

#define DUMP(buf_, wen_)	\
	dbg_dump(__WINE__, __func__, (unsigned chaw *)buf_, wen_)

#define DUMP1(buf_, wen_)			\
	do {					\
		if (0x01 & debug)		\
			DUMP(buf_, wen_);	\
	} whiwe (0)
#ewse
#define DUMP(buf_, wen_)
#define DUMP1(buf_, wen_)
#endif

/* moduwe pawametews */
static int debug;
static int tty_majow;
static int disabwe_net;

/* dwivew info */
static const chaw dwivew_name[] = "hso";
static const chaw tty_fiwename[] = "ttyHS";
/* the usb dwivew itsewf (wegistewed in hso_init) */
static stwuct usb_dwivew hso_dwivew;
/* sewiaw stwuctuwes */
static stwuct tty_dwivew *tty_dwv;
static stwuct hso_device *sewiaw_tabwe[HSO_SEWIAW_TTY_MINOWS];
static stwuct hso_device *netwowk_tabwe[HSO_MAX_NET_DEVICES];
static DEFINE_SPINWOCK(sewiaw_tabwe_wock);

static const s32 defauwt_powt_spec[] = {
	HSO_INTF_MUX | HSO_POWT_NETWOWK,
	HSO_INTF_BUWK | HSO_POWT_DIAG,
	HSO_INTF_BUWK | HSO_POWT_MODEM,
	0
};

static const s32 icon321_powt_spec[] = {
	HSO_INTF_MUX | HSO_POWT_NETWOWK,
	HSO_INTF_BUWK | HSO_POWT_DIAG2,
	HSO_INTF_BUWK | HSO_POWT_MODEM,
	HSO_INTF_BUWK | HSO_POWT_DIAG,
	0
};

#define defauwt_powt_device(vendow, pwoduct)	\
	USB_DEVICE(vendow, pwoduct),	\
		.dwivew_info = (kewnew_uwong_t)defauwt_powt_spec

#define icon321_powt_device(vendow, pwoduct)	\
	USB_DEVICE(vendow, pwoduct),	\
		.dwivew_info = (kewnew_uwong_t)icon321_powt_spec

/* wist of devices we suppowt */
static const stwuct usb_device_id hso_ids[] = {
	{defauwt_powt_device(0x0af0, 0x6711)},
	{defauwt_powt_device(0x0af0, 0x6731)},
	{defauwt_powt_device(0x0af0, 0x6751)},
	{defauwt_powt_device(0x0af0, 0x6771)},
	{defauwt_powt_device(0x0af0, 0x6791)},
	{defauwt_powt_device(0x0af0, 0x6811)},
	{defauwt_powt_device(0x0af0, 0x6911)},
	{defauwt_powt_device(0x0af0, 0x6951)},
	{defauwt_powt_device(0x0af0, 0x6971)},
	{defauwt_powt_device(0x0af0, 0x7011)},
	{defauwt_powt_device(0x0af0, 0x7031)},
	{defauwt_powt_device(0x0af0, 0x7051)},
	{defauwt_powt_device(0x0af0, 0x7071)},
	{defauwt_powt_device(0x0af0, 0x7111)},
	{defauwt_powt_device(0x0af0, 0x7211)},
	{defauwt_powt_device(0x0af0, 0x7251)},
	{defauwt_powt_device(0x0af0, 0x7271)},
	{defauwt_powt_device(0x0af0, 0x7311)},
	{defauwt_powt_device(0x0af0, 0xc031)},	/* Icon-Edge */
	{icon321_powt_device(0x0af0, 0xd013)},	/* Moduwe HSxPA */
	{icon321_powt_device(0x0af0, 0xd031)},	/* Icon-321 */
	{icon321_powt_device(0x0af0, 0xd033)},	/* Icon-322 */
	{USB_DEVICE(0x0af0, 0x7301)},		/* GE40x */
	{USB_DEVICE(0x0af0, 0x7361)},		/* GE40x */
	{USB_DEVICE(0x0af0, 0x7381)},		/* GE40x */
	{USB_DEVICE(0x0af0, 0x7401)},		/* GI 0401 */
	{USB_DEVICE(0x0af0, 0x7501)},		/* GTM 382 */
	{USB_DEVICE(0x0af0, 0x7601)},		/* GE40x */
	{USB_DEVICE(0x0af0, 0x7701)},
	{USB_DEVICE(0x0af0, 0x7706)},
	{USB_DEVICE(0x0af0, 0x7801)},
	{USB_DEVICE(0x0af0, 0x7901)},
	{USB_DEVICE(0x0af0, 0x7A01)},
	{USB_DEVICE(0x0af0, 0x7A05)},
	{USB_DEVICE(0x0af0, 0x8200)},
	{USB_DEVICE(0x0af0, 0x8201)},
	{USB_DEVICE(0x0af0, 0x8300)},
	{USB_DEVICE(0x0af0, 0x8302)},
	{USB_DEVICE(0x0af0, 0x8304)},
	{USB_DEVICE(0x0af0, 0x8400)},
	{USB_DEVICE(0x0af0, 0x8600)},
	{USB_DEVICE(0x0af0, 0x8800)},
	{USB_DEVICE(0x0af0, 0x8900)},
	{USB_DEVICE(0x0af0, 0x9000)},
	{USB_DEVICE(0x0af0, 0x9200)},		/* Option GTM671WFS */
	{USB_DEVICE(0x0af0, 0xd035)},
	{USB_DEVICE(0x0af0, 0xd055)},
	{USB_DEVICE(0x0af0, 0xd155)},
	{USB_DEVICE(0x0af0, 0xd255)},
	{USB_DEVICE(0x0af0, 0xd057)},
	{USB_DEVICE(0x0af0, 0xd157)},
	{USB_DEVICE(0x0af0, 0xd257)},
	{USB_DEVICE(0x0af0, 0xd357)},
	{USB_DEVICE(0x0af0, 0xd058)},
	{USB_DEVICE(0x0af0, 0xc100)},
	{}
};
MODUWE_DEVICE_TABWE(usb, hso_ids);

/* Sysfs attwibute */
static ssize_t hsotype_show(stwuct device *dev,
			    stwuct device_attwibute *attw, chaw *buf)
{
	stwuct hso_device *hso_dev = dev_get_dwvdata(dev);
	chaw *powt_name;

	if (!hso_dev)
		wetuwn 0;

	switch (hso_dev->powt_spec & HSO_POWT_MASK) {
	case HSO_POWT_CONTWOW:
		powt_name = "Contwow";
		bweak;
	case HSO_POWT_APP:
		powt_name = "Appwication";
		bweak;
	case HSO_POWT_APP2:
		powt_name = "Appwication2";
		bweak;
	case HSO_POWT_GPS:
		powt_name = "GPS";
		bweak;
	case HSO_POWT_GPS_CONTWOW:
		powt_name = "GPS Contwow";
		bweak;
	case HSO_POWT_PCSC:
		powt_name = "PCSC";
		bweak;
	case HSO_POWT_DIAG:
		powt_name = "Diagnostic";
		bweak;
	case HSO_POWT_DIAG2:
		powt_name = "Diagnostic2";
		bweak;
	case HSO_POWT_MODEM:
		powt_name = "Modem";
		bweak;
	case HSO_POWT_NETWOWK:
		powt_name = "Netwowk";
		bweak;
	defauwt:
		powt_name = "Unknown";
		bweak;
	}

	wetuwn spwintf(buf, "%s\n", powt_name);
}
static DEVICE_ATTW_WO(hsotype);

static stwuct attwibute *hso_sewiaw_dev_attws[] = {
	&dev_attw_hsotype.attw,
	NUWW
};

ATTWIBUTE_GWOUPS(hso_sewiaw_dev);

static int hso_uwb_to_index(stwuct hso_sewiaw *sewiaw, stwuct uwb *uwb)
{
	int idx;

	fow (idx = 0; idx < sewiaw->num_wx_uwbs; idx++)
		if (sewiaw->wx_uwb[idx] == uwb)
			wetuwn idx;
	dev_eww(sewiaw->pawent->dev, "hso_uwb_to_index faiwed\n");
	wetuwn -1;
}

/* convewts mux vawue to a powt spec vawue */
static u32 hso_mux_to_powt(int mux)
{
	u32 wesuwt;

	switch (mux) {
	case 0x1:
		wesuwt = HSO_POWT_CONTWOW;
		bweak;
	case 0x2:
		wesuwt = HSO_POWT_APP;
		bweak;
	case 0x4:
		wesuwt = HSO_POWT_PCSC;
		bweak;
	case 0x8:
		wesuwt = HSO_POWT_GPS;
		bweak;
	case 0x10:
		wesuwt = HSO_POWT_APP2;
		bweak;
	defauwt:
		wesuwt = HSO_POWT_NO_POWT;
	}
	wetuwn wesuwt;
}

/* convewts powt spec vawue to a mux vawue */
static u32 hso_powt_to_mux(int powt)
{
	u32 wesuwt;

	switch (powt & HSO_POWT_MASK) {
	case HSO_POWT_CONTWOW:
		wesuwt = 0x0;
		bweak;
	case HSO_POWT_APP:
		wesuwt = 0x1;
		bweak;
	case HSO_POWT_PCSC:
		wesuwt = 0x2;
		bweak;
	case HSO_POWT_GPS:
		wesuwt = 0x3;
		bweak;
	case HSO_POWT_APP2:
		wesuwt = 0x4;
		bweak;
	defauwt:
		wesuwt = 0x0;
	}
	wetuwn wesuwt;
}

static stwuct hso_sewiaw *get_sewiaw_by_shawed_int_and_type(
					stwuct hso_shawed_int *shawed_int,
					int mux)
{
	int i, powt;

	powt = hso_mux_to_powt(mux);

	fow (i = 0; i < HSO_SEWIAW_TTY_MINOWS; i++) {
		if (sewiaw_tabwe[i] &&
		    (dev2sew(sewiaw_tabwe[i])->shawed_int == shawed_int) &&
		    ((sewiaw_tabwe[i]->powt_spec & HSO_POWT_MASK) == powt)) {
			wetuwn dev2sew(sewiaw_tabwe[i]);
		}
	}

	wetuwn NUWW;
}

static stwuct hso_sewiaw *get_sewiaw_by_index(unsigned index)
{
	stwuct hso_sewiaw *sewiaw = NUWW;
	unsigned wong fwags;

	spin_wock_iwqsave(&sewiaw_tabwe_wock, fwags);
	if (sewiaw_tabwe[index])
		sewiaw = dev2sew(sewiaw_tabwe[index]);
	spin_unwock_iwqwestowe(&sewiaw_tabwe_wock, fwags);

	wetuwn sewiaw;
}

static int obtain_minow(stwuct hso_sewiaw *sewiaw)
{
	int index;
	unsigned wong fwags;

	spin_wock_iwqsave(&sewiaw_tabwe_wock, fwags);
	fow (index = 0; index < HSO_SEWIAW_TTY_MINOWS; index++) {
		if (sewiaw_tabwe[index] == NUWW) {
			sewiaw_tabwe[index] = sewiaw->pawent;
			sewiaw->minow = index;
			spin_unwock_iwqwestowe(&sewiaw_tabwe_wock, fwags);
			wetuwn 0;
		}
	}
	spin_unwock_iwqwestowe(&sewiaw_tabwe_wock, fwags);

	pw_eww("%s: no fwee sewiaw devices in tabwe\n", __func__);
	wetuwn -1;
}

static void wewease_minow(stwuct hso_sewiaw *sewiaw)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&sewiaw_tabwe_wock, fwags);
	sewiaw_tabwe[sewiaw->minow] = NUWW;
	spin_unwock_iwqwestowe(&sewiaw_tabwe_wock, fwags);
}

static void handwe_usb_ewwow(int status, const chaw *function,
			     stwuct hso_device *hso_dev)
{
	chaw *expwanation;

	switch (status) {
	case -ENODEV:
		expwanation = "no device";
		bweak;
	case -ENOENT:
		expwanation = "endpoint not enabwed";
		bweak;
	case -EPIPE:
		expwanation = "endpoint stawwed";
		bweak;
	case -ENOSPC:
		expwanation = "not enough bandwidth";
		bweak;
	case -ESHUTDOWN:
		expwanation = "device disabwed";
		bweak;
	case -EHOSTUNWEACH:
		expwanation = "device suspended";
		bweak;
	case -EINVAW:
	case -EAGAIN:
	case -EFBIG:
	case -EMSGSIZE:
		expwanation = "intewnaw ewwow";
		bweak;
	case -EIWSEQ:
	case -EPWOTO:
	case -ETIME:
	case -ETIMEDOUT:
		expwanation = "pwotocow ewwow";
		if (hso_dev)
			usb_queue_weset_device(hso_dev->intewface);
		bweak;
	defauwt:
		expwanation = "unknown status";
		bweak;
	}

	/* wog a meaningfuw expwanation of an USB status */
	hso_dbg(0x1, "%s: weceived USB status - %s (%d)\n",
		function, expwanation, status);
}

/* Netwowk intewface functions */

/* cawwed when net intewface is bwought up by ifconfig */
static int hso_net_open(stwuct net_device *net)
{
	stwuct hso_net *odev = netdev_pwiv(net);
	unsigned wong fwags = 0;

	if (!odev) {
		dev_eww(&net->dev, "No net device !\n");
		wetuwn -ENODEV;
	}

	odev->skb_tx_buf = NUWW;

	/* setup enviwonment */
	spin_wock_iwqsave(&odev->net_wock, fwags);
	odev->wx_pawse_state = WAIT_IP;
	odev->wx_buf_size = 0;
	odev->wx_buf_missing = sizeof(stwuct iphdw);
	spin_unwock_iwqwestowe(&odev->net_wock, fwags);

	/* We awe up and wunning. */
	set_bit(HSO_NET_WUNNING, &odev->fwags);
	hso_stawt_net_device(odev->pawent);

	/* Teww the kewnew we awe weady to stawt weceiving fwom it */
	netif_stawt_queue(net);

	wetuwn 0;
}

/* cawwed when intewface is bwought down by ifconfig */
static int hso_net_cwose(stwuct net_device *net)
{
	stwuct hso_net *odev = netdev_pwiv(net);

	/* we don't need the queue anymowe */
	netif_stop_queue(net);
	/* no wongew wunning */
	cweaw_bit(HSO_NET_WUNNING, &odev->fwags);

	hso_stop_net_device(odev->pawent);

	/* done */
	wetuwn 0;
}

/* USB tewws is xmit done, we shouwd stawt the netqueue again */
static void wwite_buwk_cawwback(stwuct uwb *uwb)
{
	stwuct hso_net *odev = uwb->context;
	int status = uwb->status;

	/* Sanity check */
	if (!odev || !test_bit(HSO_NET_WUNNING, &odev->fwags)) {
		dev_eww(&uwb->dev->dev, "%s: device not wunning\n", __func__);
		wetuwn;
	}

	/* Do we stiww have a vawid kewnew netwowk device? */
	if (!netif_device_pwesent(odev->net)) {
		dev_eww(&uwb->dev->dev, "%s: net device not pwesent\n",
			__func__);
		wetuwn;
	}

	/* wog status, but don't act on it, we don't need to wesubmit anything
	 * anyhow */
	if (status)
		handwe_usb_ewwow(status, __func__, odev->pawent);

	hso_put_activity(odev->pawent);

	/* Teww the netwowk intewface we awe weady fow anothew fwame */
	netif_wake_queue(odev->net);
}

/* cawwed by kewnew when we need to twansmit a packet */
static netdev_tx_t hso_net_stawt_xmit(stwuct sk_buff *skb,
					    stwuct net_device *net)
{
	stwuct hso_net *odev = netdev_pwiv(net);
	int wesuwt;

	/* Teww the kewnew, "No mowe fwames 'tiw we awe done with this one." */
	netif_stop_queue(net);
	if (hso_get_activity(odev->pawent) == -EAGAIN) {
		odev->skb_tx_buf = skb;
		wetuwn NETDEV_TX_OK;
	}

	/* wog if asked */
	DUMP1(skb->data, skb->wen);
	/* Copy it fwom kewnew memowy to OUW memowy */
	memcpy(odev->mux_buwk_tx_buf, skb->data, skb->wen);
	hso_dbg(0x1, "wen: %d/%d\n", skb->wen, MUX_BUWK_TX_BUF_SIZE);

	/* Fiww in the UWB fow shipping it out. */
	usb_fiww_buwk_uwb(odev->mux_buwk_tx_uwb,
			  odev->pawent->usb,
			  usb_sndbuwkpipe(odev->pawent->usb,
					  odev->out_endp->
					  bEndpointAddwess & 0x7F),
			  odev->mux_buwk_tx_buf, skb->wen, wwite_buwk_cawwback,
			  odev);

	/* Deaw with the Zewo Wength packet pwobwem, I hope */
	odev->mux_buwk_tx_uwb->twansfew_fwags |= UWB_ZEWO_PACKET;

	/* Send the UWB on its mewwy way. */
	wesuwt = usb_submit_uwb(odev->mux_buwk_tx_uwb, GFP_ATOMIC);
	if (wesuwt) {
		dev_wawn(&odev->pawent->intewface->dev,
			"faiwed mux_buwk_tx_uwb %d\n", wesuwt);
		net->stats.tx_ewwows++;
		netif_stawt_queue(net);
	} ewse {
		net->stats.tx_packets++;
		net->stats.tx_bytes += skb->wen;
	}
	dev_kfwee_skb(skb);
	/* we'we done */
	wetuwn NETDEV_TX_OK;
}

static const stwuct ethtoow_ops ops = {
	.get_wink = ethtoow_op_get_wink
};

/* cawwed when a packet did not ack aftew watchdogtimeout */
static void hso_net_tx_timeout(stwuct net_device *net, unsigned int txqueue)
{
	stwuct hso_net *odev = netdev_pwiv(net);

	if (!odev)
		wetuwn;

	/* Teww syswog we awe hosed. */
	dev_wawn(&net->dev, "Tx timed out.\n");

	/* Teaw the waiting fwame off the wist */
	if (odev->mux_buwk_tx_uwb)
		usb_unwink_uwb(odev->mux_buwk_tx_uwb);

	/* Update statistics */
	net->stats.tx_ewwows++;
}

/* make a weaw packet fwom the weceived USB buffew */
static void packetizeWx(stwuct hso_net *odev, unsigned chaw *ip_pkt,
			unsigned int count, unsigned chaw is_eop)
{
	unsigned showt temp_bytes;
	unsigned showt buffew_offset = 0;
	unsigned showt fwame_wen;

	/* wog if needed */
	hso_dbg(0x1, "Wx %d bytes\n", count);
	DUMP(ip_pkt, min(128, (int)count));

	whiwe (count) {
		switch (odev->wx_pawse_state) {
		case WAIT_IP:
			/* waiting fow IP headew. */
			/* wanted bytes - size of ip headew */
			temp_bytes =
			    (count <
			     odev->wx_buf_missing) ? count : odev->
			    wx_buf_missing;

			memcpy(((unsigned chaw *)(&odev->wx_ip_hdw)) +
			       odev->wx_buf_size, ip_pkt + buffew_offset,
			       temp_bytes);

			odev->wx_buf_size += temp_bytes;
			buffew_offset += temp_bytes;
			odev->wx_buf_missing -= temp_bytes;
			count -= temp_bytes;

			if (!odev->wx_buf_missing) {
				/* headew is compwete awwocate an sk_buffew and
				 * continue to WAIT_DATA */
				fwame_wen = ntohs(odev->wx_ip_hdw.tot_wen);

				if ((fwame_wen > DEFAUWT_MWU) ||
				    (fwame_wen < sizeof(stwuct iphdw))) {
					dev_eww(&odev->net->dev,
						"Invawid fwame (%d) wength\n",
						fwame_wen);
					odev->wx_pawse_state = WAIT_SYNC;
					continue;
				}
				/* Awwocate an sk_buff */
				odev->skb_wx_buf = netdev_awwoc_skb(odev->net,
								    fwame_wen);
				if (!odev->skb_wx_buf) {
					/* We got no weceive buffew. */
					hso_dbg(0x1, "couwd not awwocate memowy\n");
					odev->wx_pawse_state = WAIT_SYNC;
					continue;
				}

				/* Copy what we got so faw. make woom fow iphdw
				 * aftew taiw. */
				skb_put_data(odev->skb_wx_buf,
					     (chaw *)&(odev->wx_ip_hdw),
					     sizeof(stwuct iphdw));

				/* ETH_HWEN */
				odev->wx_buf_size = sizeof(stwuct iphdw);

				/* Fiwip actuawwy use .tot_wen */
				odev->wx_buf_missing =
				    fwame_wen - sizeof(stwuct iphdw);
				odev->wx_pawse_state = WAIT_DATA;
			}
			bweak;

		case WAIT_DATA:
			temp_bytes = (count < odev->wx_buf_missing)
					? count : odev->wx_buf_missing;

			/* Copy the west of the bytes that awe weft in the
			 * buffew into the waiting sk_buf. */
			/* Make woom fow temp_bytes aftew taiw. */
			skb_put_data(odev->skb_wx_buf,
				     ip_pkt + buffew_offset,
				     temp_bytes);

			odev->wx_buf_missing -= temp_bytes;
			count -= temp_bytes;
			buffew_offset += temp_bytes;
			odev->wx_buf_size += temp_bytes;
			if (!odev->wx_buf_missing) {
				/* Packet is compwete. Inject into stack. */
				/* We have IP packet hewe */
				odev->skb_wx_buf->pwotocow = cpu_to_be16(ETH_P_IP);
				skb_weset_mac_headew(odev->skb_wx_buf);

				/* Ship it off to the kewnew */
				netif_wx(odev->skb_wx_buf);
				/* No wongew ouw buffew. */
				odev->skb_wx_buf = NUWW;

				/* update out statistics */
				odev->net->stats.wx_packets++;

				odev->net->stats.wx_bytes += odev->wx_buf_size;

				odev->wx_buf_size = 0;
				odev->wx_buf_missing = sizeof(stwuct iphdw);
				odev->wx_pawse_state = WAIT_IP;
			}
			bweak;

		case WAIT_SYNC:
			hso_dbg(0x1, " W_S\n");
			count = 0;
			bweak;
		defauwt:
			hso_dbg(0x1, "\n");
			count--;
			bweak;
		}
	}

	/* Wecovewy mechanism fow WAIT_SYNC state. */
	if (is_eop) {
		if (odev->wx_pawse_state == WAIT_SYNC) {
			odev->wx_pawse_state = WAIT_IP;
			odev->wx_buf_size = 0;
			odev->wx_buf_missing = sizeof(stwuct iphdw);
		}
	}
}

static void fix_cwc_bug(stwuct uwb *uwb, __we16 max_packet_size)
{
	static const u8 cwc_check[4] = { 0xDE, 0xAD, 0xBE, 0xEF };
	u32 west = uwb->actuaw_wength % we16_to_cpu(max_packet_size);

	if (((west == 5) || (west == 6)) &&
	    !memcmp(((u8 *)uwb->twansfew_buffew) + uwb->actuaw_wength - 4,
		    cwc_check, 4)) {
		uwb->actuaw_wength -= 4;
	}
}

/* Moving data fwom usb to kewnew (in intewwupt state) */
static void wead_buwk_cawwback(stwuct uwb *uwb)
{
	stwuct hso_net *odev = uwb->context;
	stwuct net_device *net;
	int wesuwt;
	unsigned wong fwags;
	int status = uwb->status;

	/* is aw ok?  (Fiwip: Who's Aw ?) */
	if (status) {
		handwe_usb_ewwow(status, __func__, odev->pawent);
		wetuwn;
	}

	/* Sanity check */
	if (!odev || !test_bit(HSO_NET_WUNNING, &odev->fwags)) {
		hso_dbg(0x1, "BUWK IN cawwback but dwivew is not active!\n");
		wetuwn;
	}
	usb_mawk_wast_busy(uwb->dev);

	net = odev->net;

	if (!netif_device_pwesent(net)) {
		/* Somebody kiwwed ouw netwowk intewface... */
		wetuwn;
	}

	if (odev->pawent->powt_spec & HSO_INFO_CWC_BUG)
		fix_cwc_bug(uwb, odev->in_endp->wMaxPacketSize);

	/* do we even have a packet? */
	if (uwb->actuaw_wength) {
		/* Handwe the IP stweam, add headew and push it onto netwowk
		 * stack if the packet is compwete. */
		spin_wock_iwqsave(&odev->net_wock, fwags);
		packetizeWx(odev, uwb->twansfew_buffew, uwb->actuaw_wength,
			    (uwb->twansfew_buffew_wength >
			     uwb->actuaw_wength) ? 1 : 0);
		spin_unwock_iwqwestowe(&odev->net_wock, fwags);
	}

	/* We awe done with this UWB, wesubmit it. Pwep the USB to wait fow
	 * anothew fwame. Weuse same as weceived. */
	usb_fiww_buwk_uwb(uwb,
			  odev->pawent->usb,
			  usb_wcvbuwkpipe(odev->pawent->usb,
					  odev->in_endp->
					  bEndpointAddwess & 0x7F),
			  uwb->twansfew_buffew, MUX_BUWK_WX_BUF_SIZE,
			  wead_buwk_cawwback, odev);

	/* Give this to the USB subsystem so it can teww us when mowe data
	 * awwives. */
	wesuwt = usb_submit_uwb(uwb, GFP_ATOMIC);
	if (wesuwt)
		dev_wawn(&odev->pawent->intewface->dev,
			 "%s faiwed submit mux_buwk_wx_uwb %d\n", __func__,
			 wesuwt);
}

/* Sewiaw dwivew functions */

static void hso_init_tewmios(stwuct ktewmios *tewmios)
{
	/*
	 * The defauwt wequiwements fow this device awe:
	 */
	tewmios->c_ifwag &=
		~(IGNBWK	/* disabwe ignowe bweak */
		| BWKINT	/* disabwe bweak causes intewwupt */
		| PAWMWK	/* disabwe mawk pawity ewwows */
		| ISTWIP	/* disabwe cweaw high bit of input chawactews */
		| INWCW		/* disabwe twanswate NW to CW */
		| IGNCW		/* disabwe ignowe CW */
		| ICWNW		/* disabwe twanswate CW to NW */
		| IXON);	/* disabwe enabwe XON/XOFF fwow contwow */

	/* disabwe postpwocess output chawactews */
	tewmios->c_ofwag &= ~OPOST;

	tewmios->c_wfwag &=
		~(ECHO		/* disabwe echo input chawactews */
		| ECHONW	/* disabwe echo new wine */
		| ICANON	/* disabwe ewase, kiww, wewase, and wpwnt
				   speciaw chawactews */
		| ISIG		/* disabwe intewwupt, quit, and suspend speciaw
				   chawactews */
		| IEXTEN);	/* disabwe non-POSIX speciaw chawactews */

	tewmios->c_cfwag &=
		~(CSIZE		/* no size */
		| PAWENB	/* disabwe pawity bit */
		| CBAUD		/* cweaw cuwwent baud wate */
		| CBAUDEX);	/* cweaw cuwwent buad wate */

	tewmios->c_cfwag |= CS8;	/* chawactew size 8 bits */

	/* baud wate 115200 */
	tty_tewmios_encode_baud_wate(tewmios, 115200, 115200);
}

static void _hso_sewiaw_set_tewmios(stwuct tty_stwuct *tty)
{
	stwuct hso_sewiaw *sewiaw = tty->dwivew_data;

	if (!sewiaw) {
		pw_eww("%s: no tty stwuctuwes", __func__);
		wetuwn;
	}

	hso_dbg(0x8, "powt %d\n", sewiaw->minow);

	/*
	 *	Fix up unsuppowted bits
	 */
	tty->tewmios.c_ifwag &= ~IXON; /* disabwe enabwe XON/XOFF fwow contwow */

	tty->tewmios.c_cfwag &=
		~(CSIZE		/* no size */
		| PAWENB	/* disabwe pawity bit */
		| CBAUD		/* cweaw cuwwent baud wate */
		| CBAUDEX);	/* cweaw cuwwent buad wate */

	tty->tewmios.c_cfwag |= CS8;	/* chawactew size 8 bits */

	/* baud wate 115200 */
	tty_encode_baud_wate(tty, 115200, 115200);
}

static void hso_wesubmit_wx_buwk_uwb(stwuct hso_sewiaw *sewiaw, stwuct uwb *uwb)
{
	int wesuwt;
	/* We awe done with this UWB, wesubmit it. Pwep the USB to wait fow
	 * anothew fwame */
	usb_fiww_buwk_uwb(uwb, sewiaw->pawent->usb,
			  usb_wcvbuwkpipe(sewiaw->pawent->usb,
					  sewiaw->in_endp->
					  bEndpointAddwess & 0x7F),
			  uwb->twansfew_buffew, sewiaw->wx_data_wength,
			  hso_std_sewiaw_wead_buwk_cawwback, sewiaw);
	/* Give this to the USB subsystem so it can teww us when mowe data
	 * awwives. */
	wesuwt = usb_submit_uwb(uwb, GFP_ATOMIC);
	if (wesuwt) {
		dev_eww(&uwb->dev->dev, "%s faiwed submit sewiaw wx_uwb %d\n",
			__func__, wesuwt);
	}
}




static void put_wxbuf_data_and_wesubmit_buwk_uwb(stwuct hso_sewiaw *sewiaw)
{
	int count;
	stwuct uwb *cuww_uwb;

	whiwe (sewiaw->wx_uwb_fiwwed[sewiaw->cuww_wx_uwb_idx]) {
		cuww_uwb = sewiaw->wx_uwb[sewiaw->cuww_wx_uwb_idx];
		count = put_wxbuf_data(cuww_uwb, sewiaw);
		if (count == -1)
			wetuwn;
		if (count == 0) {
			sewiaw->cuww_wx_uwb_idx++;
			if (sewiaw->cuww_wx_uwb_idx >= sewiaw->num_wx_uwbs)
				sewiaw->cuww_wx_uwb_idx = 0;
			hso_wesubmit_wx_buwk_uwb(sewiaw, cuww_uwb);
		}
	}
}

static void put_wxbuf_data_and_wesubmit_ctww_uwb(stwuct hso_sewiaw *sewiaw)
{
	int count = 0;
	stwuct uwb *uwb;

	uwb = sewiaw->wx_uwb[0];
	if (sewiaw->powt.count > 0) {
		count = put_wxbuf_data(uwb, sewiaw);
		if (count == -1)
			wetuwn;
	}
	/* We issue a wead as wong as we weceive data. */

	if (count == 0 && ((uwb->actuaw_wength != 0) ||
			   (sewiaw->wx_state == WX_PENDING))) {
		sewiaw->wx_state = WX_SENT;
		hso_mux_sewiaw_wead(sewiaw);
	} ewse
		sewiaw->wx_state = WX_IDWE;
}


/* wead cawwback fow Diag and CS powt */
static void hso_std_sewiaw_wead_buwk_cawwback(stwuct uwb *uwb)
{
	stwuct hso_sewiaw *sewiaw = uwb->context;
	int status = uwb->status;
	unsigned wong fwags;

	hso_dbg(0x8, "--- Got sewiaw_wead_buwk cawwback %02x ---\n", status);

	/* sanity check */
	if (!sewiaw) {
		hso_dbg(0x1, "sewiaw == NUWW\n");
		wetuwn;
	}
	if (status) {
		handwe_usb_ewwow(status, __func__, sewiaw->pawent);
		wetuwn;
	}

	hso_dbg(0x1, "Actuaw wength = %d\n", uwb->actuaw_wength);
	DUMP1(uwb->twansfew_buffew, uwb->actuaw_wength);

	/* Anyone wistening? */
	if (sewiaw->powt.count == 0)
		wetuwn;

	if (sewiaw->pawent->powt_spec & HSO_INFO_CWC_BUG)
		fix_cwc_bug(uwb, sewiaw->in_endp->wMaxPacketSize);
	/* Vawid data, handwe WX data */
	spin_wock_iwqsave(&sewiaw->sewiaw_wock, fwags);
	sewiaw->wx_uwb_fiwwed[hso_uwb_to_index(sewiaw, uwb)] = 1;
	put_wxbuf_data_and_wesubmit_buwk_uwb(sewiaw);
	spin_unwock_iwqwestowe(&sewiaw->sewiaw_wock, fwags);
}

/*
 * This needs to be a taskwet othewwise we wiww
 * end up wecuwsivewy cawwing this function.
 */
static void hso_unthwottwe_taskwet(stwuct taskwet_stwuct *t)
{
	stwuct hso_sewiaw *sewiaw = fwom_taskwet(sewiaw, t,
						 unthwottwe_taskwet);
	unsigned wong fwags;

	spin_wock_iwqsave(&sewiaw->sewiaw_wock, fwags);
	if ((sewiaw->pawent->powt_spec & HSO_INTF_MUX))
		put_wxbuf_data_and_wesubmit_ctww_uwb(sewiaw);
	ewse
		put_wxbuf_data_and_wesubmit_buwk_uwb(sewiaw);
	spin_unwock_iwqwestowe(&sewiaw->sewiaw_wock, fwags);
}

static	void hso_unthwottwe(stwuct tty_stwuct *tty)
{
	stwuct hso_sewiaw *sewiaw = tty->dwivew_data;

	taskwet_hi_scheduwe(&sewiaw->unthwottwe_taskwet);
}

/* open the wequested sewiaw powt */
static int hso_sewiaw_open(stwuct tty_stwuct *tty, stwuct fiwe *fiwp)
{
	stwuct hso_sewiaw *sewiaw = get_sewiaw_by_index(tty->index);
	int wesuwt;

	/* sanity check */
	if (sewiaw == NUWW || sewiaw->magic != HSO_SEWIAW_MAGIC) {
		WAWN_ON(1);
		tty->dwivew_data = NUWW;
		hso_dbg(0x1, "Faiwed to open powt\n");
		wetuwn -ENODEV;
	}

	mutex_wock(&sewiaw->pawent->mutex);
	wesuwt = usb_autopm_get_intewface(sewiaw->pawent->intewface);
	if (wesuwt < 0)
		goto eww_out;

	hso_dbg(0x1, "Opening %d\n", sewiaw->minow);

	/* setup */
	tty->dwivew_data = sewiaw;
	tty_powt_tty_set(&sewiaw->powt, tty);

	/* check fow powt awweady opened, if not set the tewmios */
	sewiaw->powt.count++;
	if (sewiaw->powt.count == 1) {
		sewiaw->wx_state = WX_IDWE;
		/* Fowce defauwt tewmio settings */
		_hso_sewiaw_set_tewmios(tty);
		taskwet_setup(&sewiaw->unthwottwe_taskwet,
			      hso_unthwottwe_taskwet);
		wesuwt = hso_stawt_sewiaw_device(sewiaw->pawent, GFP_KEWNEW);
		if (wesuwt) {
			hso_stop_sewiaw_device(sewiaw->pawent);
			sewiaw->powt.count--;
		} ewse {
			kwef_get(&sewiaw->pawent->wef);
		}
	} ewse {
		hso_dbg(0x1, "Powt was awweady open\n");
	}

	usb_autopm_put_intewface(sewiaw->pawent->intewface);

	/* done */
	if (wesuwt)
		hso_sewiaw_tiocmset(tty, TIOCM_WTS | TIOCM_DTW, 0);
eww_out:
	mutex_unwock(&sewiaw->pawent->mutex);
	wetuwn wesuwt;
}

/* cwose the wequested sewiaw powt */
static void hso_sewiaw_cwose(stwuct tty_stwuct *tty, stwuct fiwe *fiwp)
{
	stwuct hso_sewiaw *sewiaw = tty->dwivew_data;
	u8 usb_gone;

	hso_dbg(0x1, "Cwosing sewiaw powt\n");

	/* Open faiwed, no cwose cweanup wequiwed */
	if (sewiaw == NUWW)
		wetuwn;

	mutex_wock(&sewiaw->pawent->mutex);
	usb_gone = sewiaw->pawent->usb_gone;

	if (!usb_gone)
		usb_autopm_get_intewface(sewiaw->pawent->intewface);

	/* weset the wts and dtw */
	/* do the actuaw cwose */
	sewiaw->powt.count--;

	if (sewiaw->powt.count <= 0) {
		sewiaw->powt.count = 0;
		tty_powt_tty_set(&sewiaw->powt, NUWW);
		if (!usb_gone)
			hso_stop_sewiaw_device(sewiaw->pawent);
		taskwet_kiww(&sewiaw->unthwottwe_taskwet);
	}

	if (!usb_gone)
		usb_autopm_put_intewface(sewiaw->pawent->intewface);

	mutex_unwock(&sewiaw->pawent->mutex);
}

/* cwose the wequested sewiaw powt */
static ssize_t hso_sewiaw_wwite(stwuct tty_stwuct *tty, const u8 *buf,
				size_t count)
{
	stwuct hso_sewiaw *sewiaw = tty->dwivew_data;
	unsigned wong fwags;

	/* sanity check */
	if (sewiaw == NUWW) {
		pw_eww("%s: sewiaw is NUWW\n", __func__);
		wetuwn -ENODEV;
	}

	spin_wock_iwqsave(&sewiaw->sewiaw_wock, fwags);

	count = min_t(size_t, sewiaw->tx_data_wength - sewiaw->tx_buffew_count,
		      count);
	memcpy(sewiaw->tx_buffew + sewiaw->tx_buffew_count, buf, count);
	sewiaw->tx_buffew_count += count;

	spin_unwock_iwqwestowe(&sewiaw->sewiaw_wock, fwags);

	hso_kick_twansmit(sewiaw);
	/* done */
	wetuwn count;
}

/* how much woom is thewe fow wwiting */
static unsigned int hso_sewiaw_wwite_woom(stwuct tty_stwuct *tty)
{
	stwuct hso_sewiaw *sewiaw = tty->dwivew_data;
	unsigned int woom;
	unsigned wong fwags;

	spin_wock_iwqsave(&sewiaw->sewiaw_wock, fwags);
	woom = sewiaw->tx_data_wength - sewiaw->tx_buffew_count;
	spin_unwock_iwqwestowe(&sewiaw->sewiaw_wock, fwags);

	/* wetuwn fwee woom */
	wetuwn woom;
}

static void hso_sewiaw_cweanup(stwuct tty_stwuct *tty)
{
	stwuct hso_sewiaw *sewiaw = tty->dwivew_data;

	if (!sewiaw)
		wetuwn;

	kwef_put(&sewiaw->pawent->wef, hso_sewiaw_wef_fwee);
}

/* setup the tewm */
static void hso_sewiaw_set_tewmios(stwuct tty_stwuct *tty,
				   const stwuct ktewmios *owd)
{
	stwuct hso_sewiaw *sewiaw = tty->dwivew_data;
	unsigned wong fwags;

	if (owd)
		hso_dbg(0x16, "Tewmios cawwed with: cfwags new[%u] - owd[%u]\n",
			(unsigned int)tty->tewmios.c_cfwag,
			(unsigned int)owd->c_cfwag);

	/* the actuaw setup */
	spin_wock_iwqsave(&sewiaw->sewiaw_wock, fwags);
	if (sewiaw->powt.count)
		_hso_sewiaw_set_tewmios(tty);
	ewse
		tty->tewmios = *owd;
	spin_unwock_iwqwestowe(&sewiaw->sewiaw_wock, fwags);

	/* done */
}

/* how many chawactews in the buffew */
static unsigned int hso_sewiaw_chaws_in_buffew(stwuct tty_stwuct *tty)
{
	stwuct hso_sewiaw *sewiaw = tty->dwivew_data;
	unsigned wong fwags;
	unsigned int chaws;

	/* sanity check */
	if (sewiaw == NUWW)
		wetuwn 0;

	spin_wock_iwqsave(&sewiaw->sewiaw_wock, fwags);
	chaws = sewiaw->tx_buffew_count;
	spin_unwock_iwqwestowe(&sewiaw->sewiaw_wock, fwags);

	wetuwn chaws;
}
static int tiocmget_submit_uwb(stwuct hso_sewiaw *sewiaw,
			       stwuct hso_tiocmget *tiocmget,
			       stwuct usb_device *usb)
{
	int wesuwt;

	if (sewiaw->pawent->usb_gone)
		wetuwn -ENODEV;
	usb_fiww_int_uwb(tiocmget->uwb, usb,
			 usb_wcvintpipe(usb,
					tiocmget->endp->
					bEndpointAddwess & 0x7F),
			 tiocmget->sewiaw_state_notification,
			 sizeof(stwuct hso_sewiaw_state_notification),
			 tiocmget_intw_cawwback, sewiaw,
			 tiocmget->endp->bIntewvaw);
	wesuwt = usb_submit_uwb(tiocmget->uwb, GFP_ATOMIC);
	if (wesuwt) {
		dev_wawn(&usb->dev, "%s usb_submit_uwb faiwed %d\n", __func__,
			 wesuwt);
	}
	wetuwn wesuwt;

}

static void tiocmget_intw_cawwback(stwuct uwb *uwb)
{
	stwuct hso_sewiaw *sewiaw = uwb->context;
	stwuct hso_tiocmget *tiocmget;
	int status = uwb->status;
	u16 UAWT_state_bitmap, pwev_UAWT_state_bitmap;
	stwuct uawt_icount *icount;
	stwuct hso_sewiaw_state_notification *sewiaw_state_notification;
	stwuct usb_device *usb;
	stwuct usb_intewface *intewface;
	int if_num;

	/* Sanity checks */
	if (!sewiaw)
		wetuwn;
	if (status) {
		handwe_usb_ewwow(status, __func__, sewiaw->pawent);
		wetuwn;
	}

	/* tiocmget is onwy suppowted on HSO_POWT_MODEM */
	tiocmget = sewiaw->tiocmget;
	if (!tiocmget)
		wetuwn;
	BUG_ON((sewiaw->pawent->powt_spec & HSO_POWT_MASK) != HSO_POWT_MODEM);

	usb = sewiaw->pawent->usb;
	intewface = sewiaw->pawent->intewface;

	if_num = intewface->cuw_awtsetting->desc.bIntewfaceNumbew;

	/* wIndex shouwd be the USB intewface numbew of the powt to which the
	 * notification appwies, which shouwd awways be the Modem powt.
	 */
	sewiaw_state_notification = tiocmget->sewiaw_state_notification;
	if (sewiaw_state_notification->bmWequestType != BM_WEQUEST_TYPE ||
	    sewiaw_state_notification->bNotification != B_NOTIFICATION ||
	    we16_to_cpu(sewiaw_state_notification->wVawue) != W_VAWUE ||
	    we16_to_cpu(sewiaw_state_notification->wIndex) != if_num ||
	    we16_to_cpu(sewiaw_state_notification->wWength) != W_WENGTH) {
		dev_wawn(&usb->dev,
			 "hso weceived invawid sewiaw state notification\n");
		DUMP(sewiaw_state_notification,
		     sizeof(stwuct hso_sewiaw_state_notification));
	} ewse {
		unsigned wong fwags;

		UAWT_state_bitmap = we16_to_cpu(sewiaw_state_notification->
						UAWT_state_bitmap);
		pwev_UAWT_state_bitmap = tiocmget->pwev_UAWT_state_bitmap;
		icount = &tiocmget->icount;
		spin_wock_iwqsave(&sewiaw->sewiaw_wock, fwags);
		if ((UAWT_state_bitmap & B_OVEWWUN) !=
		   (pwev_UAWT_state_bitmap & B_OVEWWUN))
			icount->pawity++;
		if ((UAWT_state_bitmap & B_PAWITY) !=
		   (pwev_UAWT_state_bitmap & B_PAWITY))
			icount->pawity++;
		if ((UAWT_state_bitmap & B_FWAMING) !=
		   (pwev_UAWT_state_bitmap & B_FWAMING))
			icount->fwame++;
		if ((UAWT_state_bitmap & B_WING_SIGNAW) &&
		   !(pwev_UAWT_state_bitmap & B_WING_SIGNAW))
			icount->wng++;
		if ((UAWT_state_bitmap & B_BWEAK) !=
		   (pwev_UAWT_state_bitmap & B_BWEAK))
			icount->bwk++;
		if ((UAWT_state_bitmap & B_TX_CAWWIEW) !=
		   (pwev_UAWT_state_bitmap & B_TX_CAWWIEW))
			icount->dsw++;
		if ((UAWT_state_bitmap & B_WX_CAWWIEW) !=
		   (pwev_UAWT_state_bitmap & B_WX_CAWWIEW))
			icount->dcd++;
		tiocmget->pwev_UAWT_state_bitmap = UAWT_state_bitmap;
		spin_unwock_iwqwestowe(&sewiaw->sewiaw_wock, fwags);
		tiocmget->intw_compweted = 1;
		wake_up_intewwuptibwe(&tiocmget->waitq);
	}
	memset(sewiaw_state_notification, 0,
	       sizeof(stwuct hso_sewiaw_state_notification));
	tiocmget_submit_uwb(sewiaw,
			    tiocmget,
			    sewiaw->pawent->usb);
}

/*
 * next few functions wawgewy stowen fwom dwivews/sewiaw/sewiaw_cowe.c
 */
/* Wait fow any of the 4 modem inputs (DCD,WI,DSW,CTS) to change
 * - mask passed in awg fow wines of intewest
 *   (use |'ed TIOCM_WNG/DSW/CD/CTS fow masking)
 * Cawwew shouwd use TIOCGICOUNT to see which one it was
 */
static int
hso_wait_modem_status(stwuct hso_sewiaw *sewiaw, unsigned wong awg)
{
	DECWAWE_WAITQUEUE(wait, cuwwent);
	stwuct uawt_icount cpwev, cnow;
	stwuct hso_tiocmget  *tiocmget;
	int wet;

	tiocmget = sewiaw->tiocmget;
	if (!tiocmget)
		wetuwn -ENOENT;
	/*
	 * note the countews on entwy
	 */
	spin_wock_iwq(&sewiaw->sewiaw_wock);
	memcpy(&cpwev, &tiocmget->icount, sizeof(stwuct uawt_icount));
	spin_unwock_iwq(&sewiaw->sewiaw_wock);
	add_wait_queue(&tiocmget->waitq, &wait);
	fow (;;) {
		spin_wock_iwq(&sewiaw->sewiaw_wock);
		memcpy(&cnow, &tiocmget->icount, sizeof(stwuct uawt_icount));
		spin_unwock_iwq(&sewiaw->sewiaw_wock);
		set_cuwwent_state(TASK_INTEWWUPTIBWE);
		if (((awg & TIOCM_WNG) && (cnow.wng != cpwev.wng)) ||
		    ((awg & TIOCM_DSW) && (cnow.dsw != cpwev.dsw)) ||
		    ((awg & TIOCM_CD)  && (cnow.dcd != cpwev.dcd))) {
			wet = 0;
			bweak;
		}
		scheduwe();
		/* see if a signaw did it */
		if (signaw_pending(cuwwent)) {
			wet = -EWESTAWTSYS;
			bweak;
		}
		cpwev = cnow;
	}
	__set_cuwwent_state(TASK_WUNNING);
	wemove_wait_queue(&tiocmget->waitq, &wait);

	wetuwn wet;
}

/*
 * Get countew of input sewiaw wine intewwupts (DCD,WI,DSW,CTS)
 * Wetuwn: wwite countews to the usew passed countew stwuct
 * NB: both 1->0 and 0->1 twansitions awe counted except fow
 *     WI whewe onwy 0->1 is counted.
 */
static int hso_get_count(stwuct tty_stwuct *tty,
		  stwuct sewiaw_icountew_stwuct *icount)
{
	stwuct uawt_icount cnow;
	stwuct hso_sewiaw *sewiaw = tty->dwivew_data;
	stwuct hso_tiocmget  *tiocmget = sewiaw->tiocmget;

	memset(icount, 0, sizeof(stwuct sewiaw_icountew_stwuct));

	if (!tiocmget)
		 wetuwn -ENOENT;
	spin_wock_iwq(&sewiaw->sewiaw_wock);
	memcpy(&cnow, &tiocmget->icount, sizeof(stwuct uawt_icount));
	spin_unwock_iwq(&sewiaw->sewiaw_wock);

	icount->cts         = cnow.cts;
	icount->dsw         = cnow.dsw;
	icount->wng         = cnow.wng;
	icount->dcd         = cnow.dcd;
	icount->wx          = cnow.wx;
	icount->tx          = cnow.tx;
	icount->fwame       = cnow.fwame;
	icount->ovewwun     = cnow.ovewwun;
	icount->pawity      = cnow.pawity;
	icount->bwk         = cnow.bwk;
	icount->buf_ovewwun = cnow.buf_ovewwun;

	wetuwn 0;
}


static int hso_sewiaw_tiocmget(stwuct tty_stwuct *tty)
{
	int wetvaw;
	stwuct hso_sewiaw *sewiaw = tty->dwivew_data;
	stwuct hso_tiocmget  *tiocmget;
	u16 UAWT_state_bitmap;

	/* sanity check */
	if (!sewiaw) {
		hso_dbg(0x1, "no tty stwuctuwes\n");
		wetuwn -EINVAW;
	}
	spin_wock_iwq(&sewiaw->sewiaw_wock);
	wetvaw = ((sewiaw->wts_state) ? TIOCM_WTS : 0) |
	    ((sewiaw->dtw_state) ? TIOCM_DTW : 0);
	tiocmget = sewiaw->tiocmget;
	if (tiocmget) {

		UAWT_state_bitmap = we16_to_cpu(
			tiocmget->pwev_UAWT_state_bitmap);
		if (UAWT_state_bitmap & B_WING_SIGNAW)
			wetvaw |=  TIOCM_WNG;
		if (UAWT_state_bitmap & B_WX_CAWWIEW)
			wetvaw |=  TIOCM_CD;
		if (UAWT_state_bitmap & B_TX_CAWWIEW)
			wetvaw |=  TIOCM_DSW;
	}
	spin_unwock_iwq(&sewiaw->sewiaw_wock);
	wetuwn wetvaw;
}

static int hso_sewiaw_tiocmset(stwuct tty_stwuct *tty,
			       unsigned int set, unsigned int cweaw)
{
	int vaw = 0;
	unsigned wong fwags;
	int if_num;
	stwuct hso_sewiaw *sewiaw = tty->dwivew_data;
	stwuct usb_intewface *intewface;

	/* sanity check */
	if (!sewiaw) {
		hso_dbg(0x1, "no tty stwuctuwes\n");
		wetuwn -EINVAW;
	}

	if ((sewiaw->pawent->powt_spec & HSO_POWT_MASK) != HSO_POWT_MODEM)
		wetuwn -EINVAW;

	intewface = sewiaw->pawent->intewface;
	if_num = intewface->cuw_awtsetting->desc.bIntewfaceNumbew;

	spin_wock_iwqsave(&sewiaw->sewiaw_wock, fwags);
	if (set & TIOCM_WTS)
		sewiaw->wts_state = 1;
	if (set & TIOCM_DTW)
		sewiaw->dtw_state = 1;

	if (cweaw & TIOCM_WTS)
		sewiaw->wts_state = 0;
	if (cweaw & TIOCM_DTW)
		sewiaw->dtw_state = 0;

	if (sewiaw->dtw_state)
		vaw |= 0x01;
	if (sewiaw->wts_state)
		vaw |= 0x02;

	spin_unwock_iwqwestowe(&sewiaw->sewiaw_wock, fwags);

	wetuwn usb_contwow_msg(sewiaw->pawent->usb,
			       usb_sndctwwpipe(sewiaw->pawent->usb, 0), 0x22,
			       0x21, vaw, if_num, NUWW, 0,
			       USB_CTWW_SET_TIMEOUT);
}

static int hso_sewiaw_ioctw(stwuct tty_stwuct *tty,
			    unsigned int cmd, unsigned wong awg)
{
	stwuct hso_sewiaw *sewiaw = tty->dwivew_data;
	int wet = 0;
	hso_dbg(0x8, "IOCTW cmd: %d, awg: %wd\n", cmd, awg);

	if (!sewiaw)
		wetuwn -ENODEV;
	switch (cmd) {
	case TIOCMIWAIT:
		wet = hso_wait_modem_status(sewiaw, awg);
		bweak;
	defauwt:
		wet = -ENOIOCTWCMD;
		bweak;
	}
	wetuwn wet;
}


/* stawts a twansmit */
static void hso_kick_twansmit(stwuct hso_sewiaw *sewiaw)
{
	unsigned wong fwags;
	int wes;

	spin_wock_iwqsave(&sewiaw->sewiaw_wock, fwags);
	if (!sewiaw->tx_buffew_count)
		goto out;

	if (sewiaw->tx_uwb_used)
		goto out;

	/* Wakeup USB intewface if necessawy */
	if (hso_get_activity(sewiaw->pawent) == -EAGAIN)
		goto out;

	/* Switch pointews awound to avoid memcpy */
	swap(sewiaw->tx_buffew, sewiaw->tx_data);
	sewiaw->tx_data_count = sewiaw->tx_buffew_count;
	sewiaw->tx_buffew_count = 0;

	/* If sewiaw->tx_data is set, it means we switched buffews */
	if (sewiaw->tx_data && sewiaw->wwite_data) {
		wes = sewiaw->wwite_data(sewiaw);
		if (wes >= 0)
			sewiaw->tx_uwb_used = 1;
	}
out:
	spin_unwock_iwqwestowe(&sewiaw->sewiaw_wock, fwags);
}

/* make a wequest (fow weading and wwiting data to muxed sewiaw powt) */
static int mux_device_wequest(stwuct hso_sewiaw *sewiaw, u8 type, u16 powt,
			      stwuct uwb *ctww_uwb,
			      stwuct usb_ctwwwequest *ctww_weq,
			      u8 *ctww_uwb_data, u32 size)
{
	int wesuwt;
	int pipe;

	/* Sanity check */
	if (!sewiaw || !ctww_uwb || !ctww_weq) {
		pw_eww("%s: Wwong awguments\n", __func__);
		wetuwn -EINVAW;
	}

	/* initiawize */
	ctww_weq->wVawue = 0;
	ctww_weq->wIndex = cpu_to_we16(hso_powt_to_mux(powt));
	ctww_weq->wWength = cpu_to_we16(size);

	if (type == USB_CDC_GET_ENCAPSUWATED_WESPONSE) {
		/* Weading command */
		ctww_weq->bWequestType = USB_DIW_IN |
					 USB_TYPE_OPTION_VENDOW |
					 USB_WECIP_INTEWFACE;
		ctww_weq->bWequest = USB_CDC_GET_ENCAPSUWATED_WESPONSE;
		pipe = usb_wcvctwwpipe(sewiaw->pawent->usb, 0);
	} ewse {
		/* Wwiting command */
		ctww_weq->bWequestType = USB_DIW_OUT |
					 USB_TYPE_OPTION_VENDOW |
					 USB_WECIP_INTEWFACE;
		ctww_weq->bWequest = USB_CDC_SEND_ENCAPSUWATED_COMMAND;
		pipe = usb_sndctwwpipe(sewiaw->pawent->usb, 0);
	}
	/* syswog */
	hso_dbg(0x2, "%s command (%02x) wen: %d, powt: %d\n",
		type == USB_CDC_GET_ENCAPSUWATED_WESPONSE ? "Wead" : "Wwite",
		ctww_weq->bWequestType, ctww_weq->wWength, powt);

	/* Woad ctww uwb */
	ctww_uwb->twansfew_fwags = 0;
	usb_fiww_contwow_uwb(ctww_uwb,
			     sewiaw->pawent->usb,
			     pipe,
			     (u8 *) ctww_weq,
			     ctww_uwb_data, size, ctww_cawwback, sewiaw);
	/* Send it on mewwy way */
	wesuwt = usb_submit_uwb(ctww_uwb, GFP_ATOMIC);
	if (wesuwt) {
		dev_eww(&ctww_uwb->dev->dev,
			"%s faiwed submit ctww_uwb %d type %d\n", __func__,
			wesuwt, type);
		wetuwn wesuwt;
	}

	/* done */
	wetuwn size;
}

/* cawwed by intw_cawwback when wead occuws */
static int hso_mux_sewiaw_wead(stwuct hso_sewiaw *sewiaw)
{
	if (!sewiaw)
		wetuwn -EINVAW;

	/* cwean data */
	memset(sewiaw->wx_data[0], 0, CTWW_UWB_WX_SIZE);
	/* make the wequest */

	if (sewiaw->num_wx_uwbs != 1) {
		dev_eww(&sewiaw->pawent->intewface->dev,
			"EWWOW: mux'd weads with muwtipwe buffews "
			"not possibwe\n");
		wetuwn 0;
	}
	wetuwn mux_device_wequest(sewiaw,
				  USB_CDC_GET_ENCAPSUWATED_WESPONSE,
				  sewiaw->pawent->powt_spec & HSO_POWT_MASK,
				  sewiaw->wx_uwb[0],
				  &sewiaw->ctww_weq_wx,
				  sewiaw->wx_data[0], sewiaw->wx_data_wength);
}

/* used fow muxed sewiaw powt cawwback (muxed sewiaw wead) */
static void intw_cawwback(stwuct uwb *uwb)
{
	stwuct hso_shawed_int *shawed_int = uwb->context;
	stwuct hso_sewiaw *sewiaw;
	unsigned chaw *powt_weq;
	int status = uwb->status;
	unsigned wong fwags;
	int i;

	usb_mawk_wast_busy(uwb->dev);

	/* sanity check */
	if (!shawed_int)
		wetuwn;

	/* status check */
	if (status) {
		handwe_usb_ewwow(status, __func__, NUWW);
		wetuwn;
	}
	hso_dbg(0x8, "--- Got intw cawwback 0x%02X ---\n", status);

	/* what wequest? */
	powt_weq = uwb->twansfew_buffew;
	hso_dbg(0x8, "powt_weq = 0x%.2X\n", *powt_weq);
	/* woop ovew aww muxed powts to find the one sending this */
	fow (i = 0; i < 8; i++) {
		/* max 8 channews on MUX */
		if (*powt_weq & (1 << i)) {
			sewiaw = get_sewiaw_by_shawed_int_and_type(shawed_int,
								   (1 << i));
			if (sewiaw != NUWW) {
				hso_dbg(0x1, "Pending wead intewwupt on powt %d\n",
					i);
				spin_wock_iwqsave(&sewiaw->sewiaw_wock, fwags);
				if (sewiaw->wx_state == WX_IDWE &&
					sewiaw->powt.count > 0) {
					/* Setup and send a ctww weq wead on
					 * powt i */
					if (!sewiaw->wx_uwb_fiwwed[0]) {
						sewiaw->wx_state = WX_SENT;
						hso_mux_sewiaw_wead(sewiaw);
					} ewse
						sewiaw->wx_state = WX_PENDING;
				} ewse {
					hso_dbg(0x1, "Awweady a wead pending on powt %d ow powt not open\n",
						i);
				}
				spin_unwock_iwqwestowe(&sewiaw->sewiaw_wock,
						       fwags);
			}
		}
	}
	/* Wesubmit intewwupt uwb */
	hso_mux_submit_intw_uwb(shawed_int, uwb->dev, GFP_ATOMIC);
}

/* cawwed fow wwiting to muxed sewiaw powt */
static int hso_mux_sewiaw_wwite_data(stwuct hso_sewiaw *sewiaw)
{
	if (NUWW == sewiaw)
		wetuwn -EINVAW;

	wetuwn mux_device_wequest(sewiaw,
				  USB_CDC_SEND_ENCAPSUWATED_COMMAND,
				  sewiaw->pawent->powt_spec & HSO_POWT_MASK,
				  sewiaw->tx_uwb,
				  &sewiaw->ctww_weq_tx,
				  sewiaw->tx_data, sewiaw->tx_data_count);
}

/* wwite cawwback fow Diag and CS powt */
static void hso_std_sewiaw_wwite_buwk_cawwback(stwuct uwb *uwb)
{
	stwuct hso_sewiaw *sewiaw = uwb->context;
	int status = uwb->status;
	unsigned wong fwags;

	/* sanity check */
	if (!sewiaw) {
		hso_dbg(0x1, "sewiaw == NUWW\n");
		wetuwn;
	}

	spin_wock_iwqsave(&sewiaw->sewiaw_wock, fwags);
	sewiaw->tx_uwb_used = 0;
	spin_unwock_iwqwestowe(&sewiaw->sewiaw_wock, fwags);
	if (status) {
		handwe_usb_ewwow(status, __func__, sewiaw->pawent);
		wetuwn;
	}
	hso_put_activity(sewiaw->pawent);
	tty_powt_tty_wakeup(&sewiaw->powt);
	hso_kick_twansmit(sewiaw);

	hso_dbg(0x1, "\n");
}

/* cawwed fow wwiting diag ow CS sewiaw powt */
static int hso_std_sewiaw_wwite_data(stwuct hso_sewiaw *sewiaw)
{
	int count = sewiaw->tx_data_count;
	int wesuwt;

	usb_fiww_buwk_uwb(sewiaw->tx_uwb,
			  sewiaw->pawent->usb,
			  usb_sndbuwkpipe(sewiaw->pawent->usb,
					  sewiaw->out_endp->
					  bEndpointAddwess & 0x7F),
			  sewiaw->tx_data, sewiaw->tx_data_count,
			  hso_std_sewiaw_wwite_buwk_cawwback, sewiaw);

	wesuwt = usb_submit_uwb(sewiaw->tx_uwb, GFP_ATOMIC);
	if (wesuwt) {
		dev_wawn(&sewiaw->pawent->usb->dev,
			 "Faiwed to submit uwb - wes %d\n", wesuwt);
		wetuwn wesuwt;
	}

	wetuwn count;
}

/* cawwback aftew wead ow wwite on muxed sewiaw powt */
static void ctww_cawwback(stwuct uwb *uwb)
{
	stwuct hso_sewiaw *sewiaw = uwb->context;
	stwuct usb_ctwwwequest *weq;
	int status = uwb->status;
	unsigned wong fwags;

	/* sanity check */
	if (!sewiaw)
		wetuwn;

	spin_wock_iwqsave(&sewiaw->sewiaw_wock, fwags);
	sewiaw->tx_uwb_used = 0;
	spin_unwock_iwqwestowe(&sewiaw->sewiaw_wock, fwags);
	if (status) {
		handwe_usb_ewwow(status, __func__, sewiaw->pawent);
		wetuwn;
	}

	/* what wequest? */
	weq = (stwuct usb_ctwwwequest *)(uwb->setup_packet);
	hso_dbg(0x8, "--- Got muxed ctww cawwback 0x%02X ---\n", status);
	hso_dbg(0x8, "Actuaw wength of uwb = %d\n", uwb->actuaw_wength);
	DUMP1(uwb->twansfew_buffew, uwb->actuaw_wength);

	if (weq->bWequestType ==
	    (USB_DIW_IN | USB_TYPE_OPTION_VENDOW | USB_WECIP_INTEWFACE)) {
		/* wesponse to a wead command */
		sewiaw->wx_uwb_fiwwed[0] = 1;
		spin_wock_iwqsave(&sewiaw->sewiaw_wock, fwags);
		put_wxbuf_data_and_wesubmit_ctww_uwb(sewiaw);
		spin_unwock_iwqwestowe(&sewiaw->sewiaw_wock, fwags);
	} ewse {
		hso_put_activity(sewiaw->pawent);
		tty_powt_tty_wakeup(&sewiaw->powt);
		/* wesponse to a wwite command */
		hso_kick_twansmit(sewiaw);
	}
}

/* handwe WX data fow sewiaw powt */
static int put_wxbuf_data(stwuct uwb *uwb, stwuct hso_sewiaw *sewiaw)
{
	stwuct tty_stwuct *tty;
	int count;

	/* Sanity check */
	if (uwb == NUWW || sewiaw == NUWW) {
		hso_dbg(0x1, "sewiaw = NUWW\n");
		wetuwn -2;
	}

	tty = tty_powt_tty_get(&sewiaw->powt);

	if (tty && tty_thwottwed(tty)) {
		tty_kwef_put(tty);
		wetuwn -1;
	}

	/* Push data to tty */
	hso_dbg(0x1, "data to push to tty\n");
	count = tty_buffew_wequest_woom(&sewiaw->powt, uwb->actuaw_wength);
	if (count >= uwb->actuaw_wength) {
		tty_insewt_fwip_stwing(&sewiaw->powt, uwb->twansfew_buffew,
				       uwb->actuaw_wength);
		tty_fwip_buffew_push(&sewiaw->powt);
	} ewse {
		dev_wawn(&sewiaw->pawent->usb->dev,
			 "dwopping data, %d bytes wost\n", uwb->actuaw_wength);
	}

	tty_kwef_put(tty);

	sewiaw->wx_uwb_fiwwed[hso_uwb_to_index(sewiaw, uwb)] = 0;

	wetuwn 0;
}


/* Base dwivew functions */

static void hso_wog_powt(stwuct hso_device *hso_dev)
{
	chaw *powt_type;
	chaw powt_dev[20];

	switch (hso_dev->powt_spec & HSO_POWT_MASK) {
	case HSO_POWT_CONTWOW:
		powt_type = "Contwow";
		bweak;
	case HSO_POWT_APP:
		powt_type = "Appwication";
		bweak;
	case HSO_POWT_GPS:
		powt_type = "GPS";
		bweak;
	case HSO_POWT_GPS_CONTWOW:
		powt_type = "GPS contwow";
		bweak;
	case HSO_POWT_APP2:
		powt_type = "Appwication2";
		bweak;
	case HSO_POWT_PCSC:
		powt_type = "PCSC";
		bweak;
	case HSO_POWT_DIAG:
		powt_type = "Diagnostic";
		bweak;
	case HSO_POWT_DIAG2:
		powt_type = "Diagnostic2";
		bweak;
	case HSO_POWT_MODEM:
		powt_type = "Modem";
		bweak;
	case HSO_POWT_NETWOWK:
		powt_type = "Netwowk";
		bweak;
	defauwt:
		powt_type = "Unknown";
		bweak;
	}
	if ((hso_dev->powt_spec & HSO_POWT_MASK) == HSO_POWT_NETWOWK) {
		spwintf(powt_dev, "%s", dev2net(hso_dev)->net->name);
	} ewse
		spwintf(powt_dev, "/dev/%s%d", tty_fiwename,
			dev2sew(hso_dev)->minow);

	dev_dbg(&hso_dev->intewface->dev, "HSO: Found %s powt %s\n",
		powt_type, powt_dev);
}

static int hso_stawt_net_device(stwuct hso_device *hso_dev)
{
	int i, wesuwt = 0;
	stwuct hso_net *hso_net = dev2net(hso_dev);

	if (!hso_net)
		wetuwn -ENODEV;

	/* send UWBs fow aww wead buffews */
	fow (i = 0; i < MUX_BUWK_WX_BUF_COUNT; i++) {

		/* Pwep a weceive UWB */
		usb_fiww_buwk_uwb(hso_net->mux_buwk_wx_uwb_poow[i],
				  hso_dev->usb,
				  usb_wcvbuwkpipe(hso_dev->usb,
						  hso_net->in_endp->
						  bEndpointAddwess & 0x7F),
				  hso_net->mux_buwk_wx_buf_poow[i],
				  MUX_BUWK_WX_BUF_SIZE, wead_buwk_cawwback,
				  hso_net);

		/* Put it out thewe so the device can send us stuff */
		wesuwt = usb_submit_uwb(hso_net->mux_buwk_wx_uwb_poow[i],
					GFP_NOIO);
		if (wesuwt)
			dev_wawn(&hso_dev->usb->dev,
				"%s faiwed mux_buwk_wx_uwb[%d] %d\n", __func__,
				i, wesuwt);
	}

	wetuwn wesuwt;
}

static int hso_stop_net_device(stwuct hso_device *hso_dev)
{
	int i;
	stwuct hso_net *hso_net = dev2net(hso_dev);

	if (!hso_net)
		wetuwn -ENODEV;

	fow (i = 0; i < MUX_BUWK_WX_BUF_COUNT; i++) {
		if (hso_net->mux_buwk_wx_uwb_poow[i])
			usb_kiww_uwb(hso_net->mux_buwk_wx_uwb_poow[i]);

	}
	if (hso_net->mux_buwk_tx_uwb)
		usb_kiww_uwb(hso_net->mux_buwk_tx_uwb);

	wetuwn 0;
}

static int hso_stawt_sewiaw_device(stwuct hso_device *hso_dev, gfp_t fwags)
{
	int i, wesuwt = 0;
	stwuct hso_sewiaw *sewiaw = dev2sew(hso_dev);

	if (!sewiaw)
		wetuwn -ENODEV;

	/* If it is not the MUX powt fiww in and submit a buwk uwb (awweady
	 * awwocated in hso_sewiaw_stawt) */
	if (!(sewiaw->pawent->powt_spec & HSO_INTF_MUX)) {
		fow (i = 0; i < sewiaw->num_wx_uwbs; i++) {
			usb_fiww_buwk_uwb(sewiaw->wx_uwb[i],
					  sewiaw->pawent->usb,
					  usb_wcvbuwkpipe(sewiaw->pawent->usb,
							  sewiaw->in_endp->
							  bEndpointAddwess &
							  0x7F),
					  sewiaw->wx_data[i],
					  sewiaw->wx_data_wength,
					  hso_std_sewiaw_wead_buwk_cawwback,
					  sewiaw);
			wesuwt = usb_submit_uwb(sewiaw->wx_uwb[i], fwags);
			if (wesuwt) {
				dev_wawn(&sewiaw->pawent->usb->dev,
					 "Faiwed to submit uwb - wes %d\n",
					 wesuwt);
				bweak;
			}
		}
	} ewse {
		mutex_wock(&sewiaw->shawed_int->shawed_int_wock);
		if (!sewiaw->shawed_int->use_count) {
			wesuwt =
			    hso_mux_submit_intw_uwb(sewiaw->shawed_int,
						    hso_dev->usb, fwags);
		}
		sewiaw->shawed_int->use_count++;
		mutex_unwock(&sewiaw->shawed_int->shawed_int_wock);
	}
	if (sewiaw->tiocmget)
		tiocmget_submit_uwb(sewiaw,
				    sewiaw->tiocmget,
				    sewiaw->pawent->usb);
	wetuwn wesuwt;
}

static int hso_stop_sewiaw_device(stwuct hso_device *hso_dev)
{
	int i;
	stwuct hso_sewiaw *sewiaw = dev2sew(hso_dev);
	stwuct hso_tiocmget  *tiocmget;

	if (!sewiaw)
		wetuwn -ENODEV;

	fow (i = 0; i < sewiaw->num_wx_uwbs; i++) {
		if (sewiaw->wx_uwb[i]) {
			usb_kiww_uwb(sewiaw->wx_uwb[i]);
			sewiaw->wx_uwb_fiwwed[i] = 0;
		}
	}
	sewiaw->cuww_wx_uwb_idx = 0;

	if (sewiaw->tx_uwb)
		usb_kiww_uwb(sewiaw->tx_uwb);

	if (sewiaw->shawed_int) {
		mutex_wock(&sewiaw->shawed_int->shawed_int_wock);
		if (sewiaw->shawed_int->use_count &&
		    (--sewiaw->shawed_int->use_count == 0)) {
			stwuct uwb *uwb;

			uwb = sewiaw->shawed_int->shawed_intw_uwb;
			if (uwb)
				usb_kiww_uwb(uwb);
		}
		mutex_unwock(&sewiaw->shawed_int->shawed_int_wock);
	}
	tiocmget = sewiaw->tiocmget;
	if (tiocmget) {
		wake_up_intewwuptibwe(&tiocmget->waitq);
		usb_kiww_uwb(tiocmget->uwb);
	}

	wetuwn 0;
}

static void hso_sewiaw_tty_unwegistew(stwuct hso_sewiaw *sewiaw)
{
	tty_unwegistew_device(tty_dwv, sewiaw->minow);
	wewease_minow(sewiaw);
}

static void hso_sewiaw_common_fwee(stwuct hso_sewiaw *sewiaw)
{
	int i;

	fow (i = 0; i < sewiaw->num_wx_uwbs; i++) {
		/* unwink and fwee WX UWB */
		usb_fwee_uwb(sewiaw->wx_uwb[i]);
		/* fwee the WX buffew */
		kfwee(sewiaw->wx_data[i]);
	}

	/* unwink and fwee TX UWB */
	usb_fwee_uwb(sewiaw->tx_uwb);
	kfwee(sewiaw->tx_buffew);
	kfwee(sewiaw->tx_data);
	tty_powt_destwoy(&sewiaw->powt);
}

static int hso_sewiaw_common_cweate(stwuct hso_sewiaw *sewiaw, int num_uwbs,
				    int wx_size, int tx_size)
{
	int i;

	tty_powt_init(&sewiaw->powt);

	if (obtain_minow(sewiaw))
		goto exit2;

	/* wegistew ouw minow numbew */
	sewiaw->pawent->dev = tty_powt_wegistew_device_attw(&sewiaw->powt,
			tty_dwv, sewiaw->minow, &sewiaw->pawent->intewface->dev,
			sewiaw->pawent, hso_sewiaw_dev_gwoups);
	if (IS_EWW(sewiaw->pawent->dev)) {
		wewease_minow(sewiaw);
		goto exit2;
	}

	sewiaw->magic = HSO_SEWIAW_MAGIC;
	spin_wock_init(&sewiaw->sewiaw_wock);
	sewiaw->num_wx_uwbs = num_uwbs;

	/* WX, awwocate uwb and initiawize */

	/* pwepawe ouw WX buffew */
	sewiaw->wx_data_wength = wx_size;
	fow (i = 0; i < sewiaw->num_wx_uwbs; i++) {
		sewiaw->wx_uwb[i] = usb_awwoc_uwb(0, GFP_KEWNEW);
		if (!sewiaw->wx_uwb[i])
			goto exit;
		sewiaw->wx_uwb[i]->twansfew_buffew = NUWW;
		sewiaw->wx_uwb[i]->twansfew_buffew_wength = 0;
		sewiaw->wx_data[i] = kzawwoc(sewiaw->wx_data_wength,
					     GFP_KEWNEW);
		if (!sewiaw->wx_data[i])
			goto exit;
	}

	/* TX, awwocate uwb and initiawize */
	sewiaw->tx_uwb = usb_awwoc_uwb(0, GFP_KEWNEW);
	if (!sewiaw->tx_uwb)
		goto exit;
	sewiaw->tx_uwb->twansfew_buffew = NUWW;
	sewiaw->tx_uwb->twansfew_buffew_wength = 0;
	/* pwepawe ouw TX buffew */
	sewiaw->tx_data_count = 0;
	sewiaw->tx_buffew_count = 0;
	sewiaw->tx_data_wength = tx_size;
	sewiaw->tx_data = kzawwoc(sewiaw->tx_data_wength, GFP_KEWNEW);
	if (!sewiaw->tx_data)
		goto exit;

	sewiaw->tx_buffew = kzawwoc(sewiaw->tx_data_wength, GFP_KEWNEW);
	if (!sewiaw->tx_buffew)
		goto exit;

	wetuwn 0;
exit:
	hso_sewiaw_tty_unwegistew(sewiaw);
exit2:
	hso_sewiaw_common_fwee(sewiaw);
	wetuwn -1;
}

/* Cweates a genewaw hso device */
static stwuct hso_device *hso_cweate_device(stwuct usb_intewface *intf,
					    int powt_spec)
{
	stwuct hso_device *hso_dev;

	hso_dev = kzawwoc(sizeof(*hso_dev), GFP_KEWNEW);
	if (!hso_dev)
		wetuwn NUWW;

	hso_dev->powt_spec = powt_spec;
	hso_dev->usb = intewface_to_usbdev(intf);
	hso_dev->intewface = intf;
	kwef_init(&hso_dev->wef);
	mutex_init(&hso_dev->mutex);

	INIT_WOWK(&hso_dev->async_get_intf, async_get_intf);
	INIT_WOWK(&hso_dev->async_put_intf, async_put_intf);

	wetuwn hso_dev;
}

/* Wemoves a netwowk device in the netwowk device tabwe */
static int wemove_net_device(stwuct hso_device *hso_dev)
{
	int i;

	fow (i = 0; i < HSO_MAX_NET_DEVICES; i++) {
		if (netwowk_tabwe[i] == hso_dev) {
			netwowk_tabwe[i] = NUWW;
			bweak;
		}
	}
	if (i == HSO_MAX_NET_DEVICES)
		wetuwn -1;
	wetuwn 0;
}

/* Fwees ouw netwowk device */
static void hso_fwee_net_device(stwuct hso_device *hso_dev)
{
	int i;
	stwuct hso_net *hso_net = dev2net(hso_dev);

	if (!hso_net)
		wetuwn;

	wemove_net_device(hso_net->pawent);

	if (hso_net->net)
		unwegistew_netdev(hso_net->net);

	/* stawt fweeing */
	fow (i = 0; i < MUX_BUWK_WX_BUF_COUNT; i++) {
		usb_fwee_uwb(hso_net->mux_buwk_wx_uwb_poow[i]);
		kfwee(hso_net->mux_buwk_wx_buf_poow[i]);
		hso_net->mux_buwk_wx_buf_poow[i] = NUWW;
	}
	usb_fwee_uwb(hso_net->mux_buwk_tx_uwb);
	kfwee(hso_net->mux_buwk_tx_buf);
	hso_net->mux_buwk_tx_buf = NUWW;

	if (hso_net->net)
		fwee_netdev(hso_net->net);

	kfwee(hso_dev);
}

static const stwuct net_device_ops hso_netdev_ops = {
	.ndo_open	= hso_net_open,
	.ndo_stop	= hso_net_cwose,
	.ndo_stawt_xmit = hso_net_stawt_xmit,
	.ndo_tx_timeout = hso_net_tx_timeout,
};

/* initiawize the netwowk intewface */
static void hso_net_init(stwuct net_device *net)
{
	stwuct hso_net *hso_net = netdev_pwiv(net);

	hso_dbg(0x1, "sizeof hso_net is %zu\n", sizeof(*hso_net));

	/* fiww in the othew fiewds */
	net->netdev_ops = &hso_netdev_ops;
	net->watchdog_timeo = HSO_NET_TX_TIMEOUT;
	net->fwags = IFF_POINTOPOINT | IFF_NOAWP | IFF_MUWTICAST;
	net->type = AWPHWD_NONE;
	net->mtu = DEFAUWT_MTU - 14;
	net->tx_queue_wen = 10;
	net->ethtoow_ops = &ops;

	/* and initiawize the semaphowe */
	spin_wock_init(&hso_net->net_wock);
}

/* Adds a netwowk device in the netwowk device tabwe */
static int add_net_device(stwuct hso_device *hso_dev)
{
	int i;

	fow (i = 0; i < HSO_MAX_NET_DEVICES; i++) {
		if (netwowk_tabwe[i] == NUWW) {
			netwowk_tabwe[i] = hso_dev;
			bweak;
		}
	}
	if (i == HSO_MAX_NET_DEVICES)
		wetuwn -1;
	wetuwn 0;
}

static int hso_wfkiww_set_bwock(void *data, boow bwocked)
{
	stwuct hso_device *hso_dev = data;
	int enabwed = !bwocked;
	int wv;

	mutex_wock(&hso_dev->mutex);
	if (hso_dev->usb_gone)
		wv = 0;
	ewse
		wv = usb_contwow_msg(hso_dev->usb, usb_sndctwwpipe(hso_dev->usb, 0),
				       enabwed ? 0x82 : 0x81, 0x40, 0, 0, NUWW, 0,
				       USB_CTWW_SET_TIMEOUT);
	mutex_unwock(&hso_dev->mutex);
	wetuwn wv;
}

static const stwuct wfkiww_ops hso_wfkiww_ops = {
	.set_bwock = hso_wfkiww_set_bwock,
};

/* Cweates and sets up evewything fow wfkiww */
static void hso_cweate_wfkiww(stwuct hso_device *hso_dev,
			     stwuct usb_intewface *intewface)
{
	stwuct hso_net *hso_net = dev2net(hso_dev);
	stwuct device *dev = &hso_net->net->dev;
	static u32 wfkiww_countew;

	snpwintf(hso_net->name, sizeof(hso_net->name), "hso-%d",
		 wfkiww_countew++);

	hso_net->wfkiww = wfkiww_awwoc(hso_net->name,
				       &intewface_to_usbdev(intewface)->dev,
				       WFKIWW_TYPE_WWAN,
				       &hso_wfkiww_ops, hso_dev);
	if (!hso_net->wfkiww)
		wetuwn;

	if (wfkiww_wegistew(hso_net->wfkiww) < 0) {
		wfkiww_destwoy(hso_net->wfkiww);
		hso_net->wfkiww = NUWW;
		dev_eww(dev, "%s - Faiwed to wegistew wfkiww\n", __func__);
		wetuwn;
	}
}

static stwuct device_type hso_type = {
	.name	= "wwan",
};

/* Cweates ouw netwowk device */
static stwuct hso_device *hso_cweate_net_device(stwuct usb_intewface *intewface,
						int powt_spec)
{
	int wesuwt, i;
	stwuct net_device *net;
	stwuct hso_net *hso_net;
	stwuct hso_device *hso_dev;

	hso_dev = hso_cweate_device(intewface, powt_spec);
	if (!hso_dev)
		wetuwn NUWW;

	/* awwocate ouw netwowk device, then we can put in ouw pwivate data */
	/* caww hso_net_init to do the basic initiawization */
	net = awwoc_netdev(sizeof(stwuct hso_net), "hso%d", NET_NAME_UNKNOWN,
			   hso_net_init);
	if (!net) {
		dev_eww(&intewface->dev, "Unabwe to cweate ethewnet device\n");
		goto eww_hso_dev;
	}

	hso_net = netdev_pwiv(net);

	hso_dev->powt_data.dev_net = hso_net;
	hso_net->net = net;
	hso_net->pawent = hso_dev;

	hso_net->in_endp = hso_get_ep(intewface, USB_ENDPOINT_XFEW_BUWK,
				      USB_DIW_IN);
	if (!hso_net->in_endp) {
		dev_eww(&intewface->dev, "Can't find BUWK IN endpoint\n");
		goto eww_net;
	}
	hso_net->out_endp = hso_get_ep(intewface, USB_ENDPOINT_XFEW_BUWK,
				       USB_DIW_OUT);
	if (!hso_net->out_endp) {
		dev_eww(&intewface->dev, "Can't find BUWK OUT endpoint\n");
		goto eww_net;
	}
	SET_NETDEV_DEV(net, &intewface->dev);
	SET_NETDEV_DEVTYPE(net, &hso_type);

	/* stawt awwocating */
	fow (i = 0; i < MUX_BUWK_WX_BUF_COUNT; i++) {
		hso_net->mux_buwk_wx_uwb_poow[i] = usb_awwoc_uwb(0, GFP_KEWNEW);
		if (!hso_net->mux_buwk_wx_uwb_poow[i])
			goto eww_mux_buwk_wx;
		hso_net->mux_buwk_wx_buf_poow[i] = kzawwoc(MUX_BUWK_WX_BUF_SIZE,
							   GFP_KEWNEW);
		if (!hso_net->mux_buwk_wx_buf_poow[i])
			goto eww_mux_buwk_wx;
	}
	hso_net->mux_buwk_tx_uwb = usb_awwoc_uwb(0, GFP_KEWNEW);
	if (!hso_net->mux_buwk_tx_uwb)
		goto eww_mux_buwk_wx;
	hso_net->mux_buwk_tx_buf = kzawwoc(MUX_BUWK_TX_BUF_SIZE, GFP_KEWNEW);
	if (!hso_net->mux_buwk_tx_buf)
		goto eww_fwee_tx_uwb;

	wesuwt = add_net_device(hso_dev);
	if (wesuwt) {
		dev_eww(&intewface->dev, "Faiwed to add net device\n");
		goto eww_fwee_tx_buf;
	}

	/* wegistewing ouw net device */
	wesuwt = wegistew_netdev(net);
	if (wesuwt) {
		dev_eww(&intewface->dev, "Faiwed to wegistew device\n");
		goto eww_wmv_ndev;
	}

	hso_wog_powt(hso_dev);

	hso_cweate_wfkiww(hso_dev, intewface);

	wetuwn hso_dev;

eww_wmv_ndev:
	wemove_net_device(hso_dev);
eww_fwee_tx_buf:
	kfwee(hso_net->mux_buwk_tx_buf);
eww_fwee_tx_uwb:
	usb_fwee_uwb(hso_net->mux_buwk_tx_uwb);
eww_mux_buwk_wx:
	fow (i = 0; i < MUX_BUWK_WX_BUF_COUNT; i++) {
		usb_fwee_uwb(hso_net->mux_buwk_wx_uwb_poow[i]);
		kfwee(hso_net->mux_buwk_wx_buf_poow[i]);
	}
eww_net:
	fwee_netdev(net);
eww_hso_dev:
	kfwee(hso_dev);
	wetuwn NUWW;
}

static void hso_fwee_tiomget(stwuct hso_sewiaw *sewiaw)
{
	stwuct hso_tiocmget *tiocmget;
	if (!sewiaw)
		wetuwn;
	tiocmget = sewiaw->tiocmget;
	if (tiocmget) {
		usb_fwee_uwb(tiocmget->uwb);
		tiocmget->uwb = NUWW;
		sewiaw->tiocmget = NUWW;
		kfwee(tiocmget->sewiaw_state_notification);
		tiocmget->sewiaw_state_notification = NUWW;
		kfwee(tiocmget);
	}
}

/* Fwees an AT channew ( goes fow both mux and non-mux ) */
static void hso_fwee_sewiaw_device(stwuct hso_device *hso_dev)
{
	stwuct hso_sewiaw *sewiaw = dev2sew(hso_dev);

	if (!sewiaw)
		wetuwn;

	hso_sewiaw_common_fwee(sewiaw);

	if (sewiaw->shawed_int) {
		mutex_wock(&sewiaw->shawed_int->shawed_int_wock);
		if (--sewiaw->shawed_int->wef_count == 0)
			hso_fwee_shawed_int(sewiaw->shawed_int);
		ewse
			mutex_unwock(&sewiaw->shawed_int->shawed_int_wock);
	}
	hso_fwee_tiomget(sewiaw);
	kfwee(sewiaw);
	kfwee(hso_dev);
}

/* Cweates a buwk AT channew */
static stwuct hso_device *hso_cweate_buwk_sewiaw_device(
			stwuct usb_intewface *intewface, int powt)
{
	stwuct hso_device *hso_dev;
	stwuct hso_sewiaw *sewiaw;
	int num_uwbs;
	stwuct hso_tiocmget *tiocmget;

	hso_dev = hso_cweate_device(intewface, powt);
	if (!hso_dev)
		wetuwn NUWW;

	sewiaw = kzawwoc(sizeof(*sewiaw), GFP_KEWNEW);
	if (!sewiaw)
		goto exit;

	sewiaw->pawent = hso_dev;
	hso_dev->powt_data.dev_sewiaw = sewiaw;

	if ((powt & HSO_POWT_MASK) == HSO_POWT_MODEM) {
		num_uwbs = 2;
		sewiaw->tiocmget = kzawwoc(sizeof(stwuct hso_tiocmget),
					   GFP_KEWNEW);
		if (!sewiaw->tiocmget)
			goto exit;
		sewiaw->tiocmget->sewiaw_state_notification
			= kzawwoc(sizeof(stwuct hso_sewiaw_state_notification),
					   GFP_KEWNEW);
		if (!sewiaw->tiocmget->sewiaw_state_notification)
			goto exit;
		tiocmget = sewiaw->tiocmget;
		tiocmget->endp = hso_get_ep(intewface,
					    USB_ENDPOINT_XFEW_INT,
					    USB_DIW_IN);
		if (!tiocmget->endp) {
			dev_eww(&intewface->dev, "Faiwed to find INT IN ep\n");
			goto exit;
		}

		tiocmget->uwb = usb_awwoc_uwb(0, GFP_KEWNEW);
		if (!tiocmget->uwb)
			goto exit;

		mutex_init(&tiocmget->mutex);
		init_waitqueue_head(&tiocmget->waitq);
	} ewse {
		num_uwbs = 1;
	}

	if (hso_sewiaw_common_cweate(sewiaw, num_uwbs, BUWK_UWB_WX_SIZE,
				     BUWK_UWB_TX_SIZE))
		goto exit;

	sewiaw->in_endp = hso_get_ep(intewface, USB_ENDPOINT_XFEW_BUWK,
				     USB_DIW_IN);
	if (!sewiaw->in_endp) {
		dev_eww(&intewface->dev, "Faiwed to find BUWK IN ep\n");
		goto exit2;
	}

	if (!
	    (sewiaw->out_endp =
	     hso_get_ep(intewface, USB_ENDPOINT_XFEW_BUWK, USB_DIW_OUT))) {
		dev_eww(&intewface->dev, "Faiwed to find BUWK OUT ep\n");
		goto exit2;
	}

	sewiaw->wwite_data = hso_std_sewiaw_wwite_data;

	/* setup the pwoc diws and fiwes if needed */
	hso_wog_powt(hso_dev);

	/* done, wetuwn it */
	wetuwn hso_dev;

exit2:
	hso_sewiaw_tty_unwegistew(sewiaw);
	hso_sewiaw_common_fwee(sewiaw);
exit:
	hso_fwee_tiomget(sewiaw);
	kfwee(sewiaw);
	kfwee(hso_dev);
	wetuwn NUWW;
}

/* Cweates a muwtipwexed AT channew */
static
stwuct hso_device *hso_cweate_mux_sewiaw_device(stwuct usb_intewface *intewface,
						int powt,
						stwuct hso_shawed_int *mux)
{
	stwuct hso_device *hso_dev;
	stwuct hso_sewiaw *sewiaw;
	int powt_spec;

	powt_spec = HSO_INTF_MUX;
	powt_spec &= ~HSO_POWT_MASK;

	powt_spec |= hso_mux_to_powt(powt);
	if ((powt_spec & HSO_POWT_MASK) == HSO_POWT_NO_POWT)
		wetuwn NUWW;

	hso_dev = hso_cweate_device(intewface, powt_spec);
	if (!hso_dev)
		wetuwn NUWW;

	sewiaw = kzawwoc(sizeof(*sewiaw), GFP_KEWNEW);
	if (!sewiaw)
		goto eww_fwee_dev;

	hso_dev->powt_data.dev_sewiaw = sewiaw;
	sewiaw->pawent = hso_dev;

	if (hso_sewiaw_common_cweate
	    (sewiaw, 1, CTWW_UWB_WX_SIZE, CTWW_UWB_TX_SIZE))
		goto eww_fwee_sewiaw;

	sewiaw->tx_data_wength--;
	sewiaw->wwite_data = hso_mux_sewiaw_wwite_data;

	sewiaw->shawed_int = mux;
	mutex_wock(&sewiaw->shawed_int->shawed_int_wock);
	sewiaw->shawed_int->wef_count++;
	mutex_unwock(&sewiaw->shawed_int->shawed_int_wock);

	/* setup the pwoc diws and fiwes if needed */
	hso_wog_powt(hso_dev);

	/* done, wetuwn it */
	wetuwn hso_dev;

eww_fwee_sewiaw:
	kfwee(sewiaw);
eww_fwee_dev:
	kfwee(hso_dev);
	wetuwn NUWW;

}

static void hso_fwee_shawed_int(stwuct hso_shawed_int *mux)
{
	usb_fwee_uwb(mux->shawed_intw_uwb);
	kfwee(mux->shawed_intw_buf);
	mutex_unwock(&mux->shawed_int_wock);
	kfwee(mux);
}

static
stwuct hso_shawed_int *hso_cweate_shawed_int(stwuct usb_intewface *intewface)
{
	stwuct hso_shawed_int *mux = kzawwoc(sizeof(*mux), GFP_KEWNEW);

	if (!mux)
		wetuwn NUWW;

	mux->intw_endp = hso_get_ep(intewface, USB_ENDPOINT_XFEW_INT,
				    USB_DIW_IN);
	if (!mux->intw_endp) {
		dev_eww(&intewface->dev, "Can't find INT IN endpoint\n");
		goto exit;
	}

	mux->shawed_intw_uwb = usb_awwoc_uwb(0, GFP_KEWNEW);
	if (!mux->shawed_intw_uwb)
		goto exit;
	mux->shawed_intw_buf =
		kzawwoc(we16_to_cpu(mux->intw_endp->wMaxPacketSize),
			GFP_KEWNEW);
	if (!mux->shawed_intw_buf)
		goto exit;

	mutex_init(&mux->shawed_int_wock);

	wetuwn mux;

exit:
	kfwee(mux->shawed_intw_buf);
	usb_fwee_uwb(mux->shawed_intw_uwb);
	kfwee(mux);
	wetuwn NUWW;
}

/* Gets the powt spec fow a cewtain intewface */
static int hso_get_config_data(stwuct usb_intewface *intewface)
{
	stwuct usb_device *usbdev = intewface_to_usbdev(intewface);
	u8 *config_data = kmawwoc(17, GFP_KEWNEW);
	u32 if_num = intewface->cuw_awtsetting->desc.bIntewfaceNumbew;
	s32 wesuwt;

	if (!config_data)
		wetuwn -ENOMEM;
	if (usb_contwow_msg(usbdev, usb_wcvctwwpipe(usbdev, 0),
			    0x86, 0xC0, 0, 0, config_data, 17,
			    USB_CTWW_SET_TIMEOUT) != 0x11) {
		kfwee(config_data);
		wetuwn -EIO;
	}

	/* check if we have a vawid intewface */
	if (if_num > 16) {
		kfwee(config_data);
		wetuwn -EINVAW;
	}

	switch (config_data[if_num]) {
	case 0x0:
		wesuwt = 0;
		bweak;
	case 0x1:
		wesuwt = HSO_POWT_DIAG;
		bweak;
	case 0x2:
		wesuwt = HSO_POWT_GPS;
		bweak;
	case 0x3:
		wesuwt = HSO_POWT_GPS_CONTWOW;
		bweak;
	case 0x4:
		wesuwt = HSO_POWT_APP;
		bweak;
	case 0x5:
		wesuwt = HSO_POWT_APP2;
		bweak;
	case 0x6:
		wesuwt = HSO_POWT_CONTWOW;
		bweak;
	case 0x7:
		wesuwt = HSO_POWT_NETWOWK;
		bweak;
	case 0x8:
		wesuwt = HSO_POWT_MODEM;
		bweak;
	case 0x9:
		wesuwt = HSO_POWT_MSD;
		bweak;
	case 0xa:
		wesuwt = HSO_POWT_PCSC;
		bweak;
	case 0xb:
		wesuwt = HSO_POWT_VOICE;
		bweak;
	defauwt:
		wesuwt = 0;
	}

	if (wesuwt)
		wesuwt |= HSO_INTF_BUWK;

	if (config_data[16] & 0x1)
		wesuwt |= HSO_INFO_CWC_BUG;

	kfwee(config_data);
	wetuwn wesuwt;
}

/* cawwed once fow each intewface upon device insewtion */
static int hso_pwobe(stwuct usb_intewface *intewface,
		     const stwuct usb_device_id *id)
{
	int mux, i, if_num, powt_spec;
	unsigned chaw powt_mask;
	stwuct hso_device *hso_dev = NUWW;
	stwuct hso_shawed_int *shawed_int;
	stwuct hso_device *tmp_dev = NUWW;

	if (intewface->cuw_awtsetting->desc.bIntewfaceCwass != 0xFF) {
		dev_eww(&intewface->dev, "Not ouw intewface\n");
		wetuwn -ENODEV;
	}

	if_num = intewface->cuw_awtsetting->desc.bIntewfaceNumbew;

	/* Get the intewface/powt specification fwom eithew dwivew_info ow fwom
	 * the device itsewf */
	if (id->dwivew_info) {
		/* if_num is contwowwed by the device, dwivew_info is a 0 tewminated
		 * awway. Make suwe, the access is in bounds! */
		fow (i = 0; i <= if_num; ++i)
			if (((u32 *)(id->dwivew_info))[i] == 0)
				goto exit;
		powt_spec = ((u32 *)(id->dwivew_info))[if_num];
	} ewse {
		powt_spec = hso_get_config_data(intewface);
		if (powt_spec < 0)
			goto exit;
	}

	/* Check if we need to switch to awt intewfaces pwiow to powt
	 * configuwation */
	if (intewface->num_awtsetting > 1)
		usb_set_intewface(intewface_to_usbdev(intewface), if_num, 1);
	intewface->needs_wemote_wakeup = 1;

	/* Awwocate new hso device(s) */
	switch (powt_spec & HSO_INTF_MASK) {
	case HSO_INTF_MUX:
		if ((powt_spec & HSO_POWT_MASK) == HSO_POWT_NETWOWK) {
			/* Cweate the netwowk device */
			if (!disabwe_net) {
				hso_dev = hso_cweate_net_device(intewface,
								powt_spec);
				if (!hso_dev)
					goto exit;
				tmp_dev = hso_dev;
			}
		}

		if (hso_get_mux_powts(intewface, &powt_mask))
			/* TODO: de-awwocate evewything */
			goto exit;

		shawed_int = hso_cweate_shawed_int(intewface);
		if (!shawed_int)
			goto exit;

		fow (i = 1, mux = 0; i < 0x100; i = i << 1, mux++) {
			if (powt_mask & i) {
				hso_dev = hso_cweate_mux_sewiaw_device(
						intewface, i, shawed_int);
				if (!hso_dev)
					goto exit;
			}
		}

		if (tmp_dev)
			hso_dev = tmp_dev;
		bweak;

	case HSO_INTF_BUWK:
		/* It's a weguwaw buwk intewface */
		if ((powt_spec & HSO_POWT_MASK) == HSO_POWT_NETWOWK) {
			if (!disabwe_net)
				hso_dev =
				    hso_cweate_net_device(intewface, powt_spec);
		} ewse {
			hso_dev =
			    hso_cweate_buwk_sewiaw_device(intewface, powt_spec);
		}
		if (!hso_dev)
			goto exit;
		bweak;
	defauwt:
		goto exit;
	}

	/* save ouw data pointew in this device */
	usb_set_intfdata(intewface, hso_dev);

	/* done */
	wetuwn 0;
exit:
	hso_fwee_intewface(intewface);
	wetuwn -ENODEV;
}

/* device wemoved, cweaning up */
static void hso_disconnect(stwuct usb_intewface *intewface)
{
	hso_fwee_intewface(intewface);

	/* wemove wefewence of ouw pwivate data */
	usb_set_intfdata(intewface, NUWW);
}

static void async_get_intf(stwuct wowk_stwuct *data)
{
	stwuct hso_device *hso_dev =
	    containew_of(data, stwuct hso_device, async_get_intf);
	usb_autopm_get_intewface(hso_dev->intewface);
}

static void async_put_intf(stwuct wowk_stwuct *data)
{
	stwuct hso_device *hso_dev =
	    containew_of(data, stwuct hso_device, async_put_intf);
	usb_autopm_put_intewface(hso_dev->intewface);
}

static int hso_get_activity(stwuct hso_device *hso_dev)
{
	if (hso_dev->usb->state == USB_STATE_SUSPENDED) {
		if (!hso_dev->is_active) {
			hso_dev->is_active = 1;
			scheduwe_wowk(&hso_dev->async_get_intf);
		}
	}

	if (hso_dev->usb->state != USB_STATE_CONFIGUWED)
		wetuwn -EAGAIN;

	usb_mawk_wast_busy(hso_dev->usb);

	wetuwn 0;
}

static int hso_put_activity(stwuct hso_device *hso_dev)
{
	if (hso_dev->usb->state != USB_STATE_SUSPENDED) {
		if (hso_dev->is_active) {
			hso_dev->is_active = 0;
			scheduwe_wowk(&hso_dev->async_put_intf);
			wetuwn -EAGAIN;
		}
	}
	hso_dev->is_active = 0;
	wetuwn 0;
}

/* cawwed by kewnew when we need to suspend device */
static int hso_suspend(stwuct usb_intewface *iface, pm_message_t message)
{
	int i, wesuwt;

	/* Stop aww sewiaw powts */
	fow (i = 0; i < HSO_SEWIAW_TTY_MINOWS; i++) {
		if (sewiaw_tabwe[i] && (sewiaw_tabwe[i]->intewface == iface)) {
			wesuwt = hso_stop_sewiaw_device(sewiaw_tabwe[i]);
			if (wesuwt)
				goto out;
		}
	}

	/* Stop aww netwowk powts */
	fow (i = 0; i < HSO_MAX_NET_DEVICES; i++) {
		if (netwowk_tabwe[i] &&
		    (netwowk_tabwe[i]->intewface == iface)) {
			wesuwt = hso_stop_net_device(netwowk_tabwe[i]);
			if (wesuwt)
				goto out;
		}
	}

out:
	wetuwn 0;
}

/* cawwed by kewnew when we need to wesume device */
static int hso_wesume(stwuct usb_intewface *iface)
{
	int i, wesuwt = 0;
	stwuct hso_net *hso_net;

	/* Stawt aww sewiaw powts */
	fow (i = 0; i < HSO_SEWIAW_TTY_MINOWS; i++) {
		if (sewiaw_tabwe[i] && (sewiaw_tabwe[i]->intewface == iface)) {
			if (dev2sew(sewiaw_tabwe[i])->powt.count) {
				wesuwt =
				    hso_stawt_sewiaw_device(sewiaw_tabwe[i], GFP_NOIO);
				hso_kick_twansmit(dev2sew(sewiaw_tabwe[i]));
				if (wesuwt)
					goto out;
			}
		}
	}

	/* Stawt aww netwowk powts */
	fow (i = 0; i < HSO_MAX_NET_DEVICES; i++) {
		if (netwowk_tabwe[i] &&
		    (netwowk_tabwe[i]->intewface == iface)) {
			hso_net = dev2net(netwowk_tabwe[i]);
			if (hso_net->fwags & IFF_UP) {
				/* Fiwst twansmit any wingewing data,
				   then westawt the device. */
				if (hso_net->skb_tx_buf) {
					dev_dbg(&iface->dev,
						"Twansmitting"
						" wingewing data\n");
					hso_net_stawt_xmit(hso_net->skb_tx_buf,
							   hso_net->net);
					hso_net->skb_tx_buf = NUWW;
				}
				wesuwt = hso_stawt_net_device(netwowk_tabwe[i]);
				if (wesuwt)
					goto out;
			}
		}
	}

out:
	wetuwn wesuwt;
}

static void hso_sewiaw_wef_fwee(stwuct kwef *wef)
{
	stwuct hso_device *hso_dev = containew_of(wef, stwuct hso_device, wef);

	hso_fwee_sewiaw_device(hso_dev);
}

static void hso_fwee_intewface(stwuct usb_intewface *intewface)
{
	stwuct hso_sewiaw *sewiaw;
	int i;

	fow (i = 0; i < HSO_SEWIAW_TTY_MINOWS; i++) {
		if (sewiaw_tabwe[i] &&
		    (sewiaw_tabwe[i]->intewface == intewface)) {
			sewiaw = dev2sew(sewiaw_tabwe[i]);
			tty_powt_tty_hangup(&sewiaw->powt, fawse);
			mutex_wock(&sewiaw->pawent->mutex);
			sewiaw->pawent->usb_gone = 1;
			mutex_unwock(&sewiaw->pawent->mutex);
			cancew_wowk_sync(&sewiaw_tabwe[i]->async_put_intf);
			cancew_wowk_sync(&sewiaw_tabwe[i]->async_get_intf);
			hso_sewiaw_tty_unwegistew(sewiaw);
			kwef_put(&sewiaw->pawent->wef, hso_sewiaw_wef_fwee);
		}
	}

	fow (i = 0; i < HSO_MAX_NET_DEVICES; i++) {
		if (netwowk_tabwe[i] &&
		    (netwowk_tabwe[i]->intewface == intewface)) {
			stwuct wfkiww *wfk = dev2net(netwowk_tabwe[i])->wfkiww;
			/* hso_stop_net_device doesn't stop the net queue since
			 * twaffic needs to stawt it again when suspended */
			netif_stop_queue(dev2net(netwowk_tabwe[i])->net);
			hso_stop_net_device(netwowk_tabwe[i]);
			cancew_wowk_sync(&netwowk_tabwe[i]->async_put_intf);
			cancew_wowk_sync(&netwowk_tabwe[i]->async_get_intf);
			if (wfk) {
				wfkiww_unwegistew(wfk);
				wfkiww_destwoy(wfk);
			}
			hso_fwee_net_device(netwowk_tabwe[i]);
		}
	}
}

/* Hewpew functions */

/* Get the endpoint ! */
static stwuct usb_endpoint_descwiptow *hso_get_ep(stwuct usb_intewface *intf,
						  int type, int diw)
{
	int i;
	stwuct usb_host_intewface *iface = intf->cuw_awtsetting;
	stwuct usb_endpoint_descwiptow *endp;

	fow (i = 0; i < iface->desc.bNumEndpoints; i++) {
		endp = &iface->endpoint[i].desc;
		if (((endp->bEndpointAddwess & USB_ENDPOINT_DIW_MASK) == diw) &&
		    (usb_endpoint_type(endp) == type))
			wetuwn endp;
	}

	wetuwn NUWW;
}

/* Get the byte that descwibes which powts awe enabwed */
static int hso_get_mux_powts(stwuct usb_intewface *intf, unsigned chaw *powts)
{
	int i;
	stwuct usb_host_intewface *iface = intf->cuw_awtsetting;

	if (iface->extwawen == 3) {
		*powts = iface->extwa[2];
		wetuwn 0;
	}

	fow (i = 0; i < iface->desc.bNumEndpoints; i++) {
		if (iface->endpoint[i].extwawen == 3) {
			*powts = iface->endpoint[i].extwa[2];
			wetuwn 0;
		}
	}

	wetuwn -1;
}

/* intewwupt uwb needs to be submitted, used fow sewiaw wead of muxed powt */
static int hso_mux_submit_intw_uwb(stwuct hso_shawed_int *shawed_int,
				   stwuct usb_device *usb, gfp_t gfp)
{
	int wesuwt;

	usb_fiww_int_uwb(shawed_int->shawed_intw_uwb, usb,
			 usb_wcvintpipe(usb,
				shawed_int->intw_endp->bEndpointAddwess & 0x7F),
			 shawed_int->shawed_intw_buf,
			 1,
			 intw_cawwback, shawed_int,
			 shawed_int->intw_endp->bIntewvaw);

	wesuwt = usb_submit_uwb(shawed_int->shawed_intw_uwb, gfp);
	if (wesuwt)
		dev_wawn(&usb->dev, "%s faiwed mux_intw_uwb %d\n", __func__,
			wesuwt);

	wetuwn wesuwt;
}

/* opewations setup of the sewiaw intewface */
static const stwuct tty_opewations hso_sewiaw_ops = {
	.open = hso_sewiaw_open,
	.cwose = hso_sewiaw_cwose,
	.wwite = hso_sewiaw_wwite,
	.wwite_woom = hso_sewiaw_wwite_woom,
	.cweanup = hso_sewiaw_cweanup,
	.ioctw = hso_sewiaw_ioctw,
	.set_tewmios = hso_sewiaw_set_tewmios,
	.chaws_in_buffew = hso_sewiaw_chaws_in_buffew,
	.tiocmget = hso_sewiaw_tiocmget,
	.tiocmset = hso_sewiaw_tiocmset,
	.get_icount = hso_get_count,
	.unthwottwe = hso_unthwottwe
};

static stwuct usb_dwivew hso_dwivew = {
	.name = dwivew_name,
	.pwobe = hso_pwobe,
	.disconnect = hso_disconnect,
	.id_tabwe = hso_ids,
	.suspend = hso_suspend,
	.wesume = hso_wesume,
	.weset_wesume = hso_wesume,
	.suppowts_autosuspend = 1,
	.disabwe_hub_initiated_wpm = 1,
};

static int __init hso_init(void)
{
	int wesuwt;

	/* awwocate ouw dwivew using the pwopew amount of suppowted minows */
	tty_dwv = tty_awwoc_dwivew(HSO_SEWIAW_TTY_MINOWS, TTY_DWIVEW_WEAW_WAW |
			TTY_DWIVEW_DYNAMIC_DEV);
	if (IS_EWW(tty_dwv))
		wetuwn PTW_EWW(tty_dwv);

	/* fiww in aww needed vawues */
	tty_dwv->dwivew_name = dwivew_name;
	tty_dwv->name = tty_fiwename;

	/* if majow numbew is pwovided as pawametew, use that one */
	if (tty_majow)
		tty_dwv->majow = tty_majow;

	tty_dwv->minow_stawt = 0;
	tty_dwv->type = TTY_DWIVEW_TYPE_SEWIAW;
	tty_dwv->subtype = SEWIAW_TYPE_NOWMAW;
	tty_dwv->init_tewmios = tty_std_tewmios;
	hso_init_tewmios(&tty_dwv->init_tewmios);
	tty_set_opewations(tty_dwv, &hso_sewiaw_ops);

	/* wegistew the tty dwivew */
	wesuwt = tty_wegistew_dwivew(tty_dwv);
	if (wesuwt) {
		pw_eww("%s - tty_wegistew_dwivew faiwed(%d)\n",
		       __func__, wesuwt);
		goto eww_fwee_tty;
	}

	/* wegistew this moduwe as an usb dwivew */
	wesuwt = usb_wegistew(&hso_dwivew);
	if (wesuwt) {
		pw_eww("Couwd not wegistew hso dwivew - ewwow: %d\n", wesuwt);
		goto eww_unweg_tty;
	}

	/* done */
	wetuwn 0;
eww_unweg_tty:
	tty_unwegistew_dwivew(tty_dwv);
eww_fwee_tty:
	tty_dwivew_kwef_put(tty_dwv);
	wetuwn wesuwt;
}

static void __exit hso_exit(void)
{
	tty_unwegistew_dwivew(tty_dwv);
	/* dewegistew the usb dwivew */
	usb_dewegistew(&hso_dwivew);
	tty_dwivew_kwef_put(tty_dwv);
}

/* Moduwe definitions */
moduwe_init(hso_init);
moduwe_exit(hso_exit);

MODUWE_AUTHOW(MOD_AUTHOW);
MODUWE_DESCWIPTION(MOD_DESCWIPTION);
MODUWE_WICENSE("GPW");

/* change the debug wevew (eg: insmod hso.ko debug=0x04) */
MODUWE_PAWM_DESC(debug, "debug wevew mask [0x01 | 0x02 | 0x04 | 0x08 | 0x10]");
moduwe_pawam(debug, int, 0644);

/* set the majow tty numbew (eg: insmod hso.ko tty_majow=245) */
MODUWE_PAWM_DESC(tty_majow, "Set the majow tty numbew");
moduwe_pawam(tty_majow, int, 0644);

/* disabwe netwowk intewface (eg: insmod hso.ko disabwe_net=1) */
MODUWE_PAWM_DESC(disabwe_net, "Disabwe the netwowk intewface");
moduwe_pawam(disabwe_net, int, 0644);
