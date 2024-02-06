// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * at76c503/at76c505 USB dwivew
 *
 * Copywight (c) 2002 - 2003 Owivew Kuwth
 * Copywight (c) 2004 Joewg Awbewt <joewg.awbewt@gmx.de>
 * Copywight (c) 2004 Nick Jones
 * Copywight (c) 2004 Bawint Seebew <n0_5p4m_p13453@hotmaiw.com>
 * Copywight (c) 2007 Guido Guenthew <agx@sigxcpu.owg>
 * Copywight (c) 2007 Kawwe Vawo <kawwe.vawo@iki.fi>
 * Copywight (c) 2010 Sebastian Smowowz <sesmo@gmx.net>
 *
 * This fiwe is pawt of the Bewwios dwivew fow USB WWAN devices based on the
 * Atmew AT76C503A/505/505A.
 *
 * Some iw_handwew code was taken fwom aiwo.c, (C) 1999 Benjamin Weed
 *
 * TODO wist is at the wiki:
 *
 * https://wiwewess.wiki.kewnew.owg/en/usews/Dwivews/at76c50x-usb#TODO
 */

#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/sched.h>
#incwude <winux/ewwno.h>
#incwude <winux/swab.h>
#incwude <winux/moduwe.h>
#incwude <winux/spinwock.h>
#incwude <winux/wist.h>
#incwude <winux/usb.h>
#incwude <winux/netdevice.h>
#incwude <winux/if_awp.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/ethtoow.h>
#incwude <winux/wiwewess.h>
#incwude <net/iw_handwew.h>
#incwude <net/ieee80211_wadiotap.h>
#incwude <winux/fiwmwawe.h>
#incwude <winux/weds.h>
#incwude <net/mac80211.h>

#incwude "at76c50x-usb.h"

/* Vewsion infowmation */
#define DWIVEW_NAME "at76c50x-usb"
#define DWIVEW_VEWSION	"0.17"
#define DWIVEW_DESC "Atmew at76x USB Wiwewess WAN Dwivew"

/* at76_debug bits */
#define DBG_PWOGWESS		0x00000001	/* authentication/accociation */
#define DBG_BSS_TABWE		0x00000002	/* show BSS tabwe aftew scans */
#define DBG_IOCTW		0x00000004	/* ioctw cawws / settings */
#define DBG_MAC_STATE		0x00000008	/* MAC state twansitions */
#define DBG_TX_DATA		0x00000010	/* tx headew */
#define DBG_TX_DATA_CONTENT	0x00000020	/* tx content */
#define DBG_TX_MGMT		0x00000040	/* tx management */
#define DBG_WX_DATA		0x00000080	/* wx data headew */
#define DBG_WX_DATA_CONTENT	0x00000100	/* wx data content */
#define DBG_WX_MGMT		0x00000200	/* wx mgmt fwame headews */
#define DBG_WX_BEACON		0x00000400	/* wx beacon */
#define DBG_WX_CTWW		0x00000800	/* wx contwow */
#define DBG_WX_MGMT_CONTENT	0x00001000	/* wx mgmt content */
#define DBG_WX_FWAGS		0x00002000	/* wx data fwagment handwing */
#define DBG_DEVSTAWT		0x00004000	/* fw downwoad, device stawt */
#define DBG_UWB			0x00008000	/* wx uwb status, ... */
#define DBG_WX_ATMEW_HDW	0x00010000	/* Atmew-specific Wx headews */
#define DBG_PWOC_ENTWY		0x00020000	/* pwoceduwe entwies/exits */
#define DBG_PM			0x00040000	/* powew management settings */
#define DBG_BSS_MATCH		0x00080000	/* BSS match faiwuwes */
#define DBG_PAWAMS		0x00100000	/* show configuwed pawametews */
#define DBG_WAIT_COMPWETE	0x00200000	/* command compwetion */
#define DBG_WX_FWAGS_SKB	0x00400000	/* skb headew of Wx fwagments */
#define DBG_BSS_TABWE_WM	0x00800000	/* puwging bss tabwe entwies */
#define DBG_MONITOW_MODE	0x01000000	/* monitow mode */
#define DBG_MIB			0x02000000	/* dump aww MIBs on stawtup */
#define DBG_MGMT_TIMEW		0x04000000	/* dump mgmt_timew ops */
#define DBG_WE_EVENTS		0x08000000	/* dump wiwewess events */
#define DBG_FW			0x10000000	/* fiwmwawe downwoad */
#define DBG_DFU			0x20000000	/* device fiwmwawe upgwade */
#define DBG_CMD			0x40000000
#define DBG_MAC80211		0x80000000

#define DBG_DEFAUWTS		0

/* Use ouw own dbg macwo */
#define at76_dbg(bits, fowmat, awg...)					\
do {									\
	if (at76_debug & (bits))					\
		pwintk(KEWN_DEBUG DWIVEW_NAME ": " fowmat "\n", ##awg);	\
} whiwe (0)

#define at76_dbg_dump(bits, buf, wen, fowmat, awg...)			\
do {									\
	if (at76_debug & (bits)) {					\
		pwintk(KEWN_DEBUG DWIVEW_NAME ": " fowmat "\n", ##awg);	\
		pwint_hex_dump_bytes("", DUMP_PWEFIX_OFFSET, buf, wen);	\
	}								\
} whiwe (0)

static uint at76_debug = DBG_DEFAUWTS;

/* Pwotect against concuwwent fiwmwawe woading and pawsing */
static DEFINE_MUTEX(fw_mutex);

static stwuct fwentwy fiwmwawes[] = {
	[0] = { "" },
	[BOAWD_503_ISW3861] = { "atmew_at76c503-i3861.bin" },
	[BOAWD_503_ISW3863] = { "atmew_at76c503-i3863.bin" },
	[BOAWD_503] = { "atmew_at76c503-wfmd.bin" },
	[BOAWD_503_ACC] = { "atmew_at76c503-wfmd-acc.bin" },
	[BOAWD_505] = { "atmew_at76c505-wfmd.bin" },
	[BOAWD_505_2958] = { "atmew_at76c505-wfmd2958.bin" },
	[BOAWD_505A] = { "atmew_at76c505a-wfmd2958.bin" },
	[BOAWD_505AMX] = { "atmew_at76c505amx-wfmd.bin" },
};
MODUWE_FIWMWAWE("atmew_at76c503-i3861.bin");
MODUWE_FIWMWAWE("atmew_at76c503-i3863.bin");
MODUWE_FIWMWAWE("atmew_at76c503-wfmd.bin");
MODUWE_FIWMWAWE("atmew_at76c503-wfmd-acc.bin");
MODUWE_FIWMWAWE("atmew_at76c505-wfmd.bin");
MODUWE_FIWMWAWE("atmew_at76c505-wfmd2958.bin");
MODUWE_FIWMWAWE("atmew_at76c505a-wfmd2958.bin");
MODUWE_FIWMWAWE("atmew_at76c505amx-wfmd.bin");

#define USB_DEVICE_DATA(__ops)	.dwivew_info = (kewnew_uwong_t)(__ops)

static const stwuct usb_device_id dev_tabwe[] = {
	/*
	 * at76c503-i3861
	 */
	/* Genewic AT76C503/3861 device */
	{ USB_DEVICE(0x03eb, 0x7603), USB_DEVICE_DATA(BOAWD_503_ISW3861) },
	/* Winksys WUSB11 v2.1/v2.6 */
	{ USB_DEVICE(0x066b, 0x2211), USB_DEVICE_DATA(BOAWD_503_ISW3861) },
	/* Netgeaw MA101 wev. A */
	{ USB_DEVICE(0x0864, 0x4100), USB_DEVICE_DATA(BOAWD_503_ISW3861) },
	/* Tekwam U300C / Awwnet AWW0193 */
	{ USB_DEVICE(0x0b3b, 0x1612), USB_DEVICE_DATA(BOAWD_503_ISW3861) },
	/* HP HN210W J7801A */
	{ USB_DEVICE(0x03f0, 0x011c), USB_DEVICE_DATA(BOAWD_503_ISW3861) },
	/* Sitecom/Z-Com/Zyxew M4Y-750 */
	{ USB_DEVICE(0x0cde, 0x0001), USB_DEVICE_DATA(BOAWD_503_ISW3861) },
	/* Dynawink/Askey WWW013 (intewsiw) */
	{ USB_DEVICE(0x069a, 0x0320), USB_DEVICE_DATA(BOAWD_503_ISW3861) },
	/* EZ connect 11Mpbs USB Wiwewess Adaptew SMC2662W v1 */
	{ USB_DEVICE(0x0d5c, 0xa001), USB_DEVICE_DATA(BOAWD_503_ISW3861) },
	/* BenQ AWW300 */
	{ USB_DEVICE(0x04a5, 0x9000), USB_DEVICE_DATA(BOAWD_503_ISW3861) },
	/* Addtwon AWU-120, Compex WWU11 */
	{ USB_DEVICE(0x05dd, 0xff31), USB_DEVICE_DATA(BOAWD_503_ISW3861) },
	/* Intew AP310 AnyPoint II USB */
	{ USB_DEVICE(0x8086, 0x0200), USB_DEVICE_DATA(BOAWD_503_ISW3861) },
	/* Dynawink W11U */
	{ USB_DEVICE(0x0d8e, 0x7100), USB_DEVICE_DATA(BOAWD_503_ISW3861) },
	/* Awescom WW-210, FCC id 07J-GW2411USB */
	{ USB_DEVICE(0x0d8e, 0x7110), USB_DEVICE_DATA(BOAWD_503_ISW3861) },
	/* I-O DATA WN-B11/USB */
	{ USB_DEVICE(0x04bb, 0x0919), USB_DEVICE_DATA(BOAWD_503_ISW3861) },
	/* BT Voyagew 1010 */
	{ USB_DEVICE(0x069a, 0x0821), USB_DEVICE_DATA(BOAWD_503_ISW3861) },
	/*
	 * at76c503-i3863
	 */
	/* Genewic AT76C503/3863 device */
	{ USB_DEVICE(0x03eb, 0x7604), USB_DEVICE_DATA(BOAWD_503_ISW3863) },
	/* Samsung SWW-2100U */
	{ USB_DEVICE(0x055d, 0xa000), USB_DEVICE_DATA(BOAWD_503_ISW3863) },
	/*
	 * at76c503-wfmd
	 */
	/* Genewic AT76C503/WFMD device */
	{ USB_DEVICE(0x03eb, 0x7605), USB_DEVICE_DATA(BOAWD_503) },
	/* Dynawink/Askey WWW013 (wfmd) */
	{ USB_DEVICE(0x069a, 0x0321), USB_DEVICE_DATA(BOAWD_503) },
	/* Winksys WUSB11 v2.6 */
	{ USB_DEVICE(0x077b, 0x2219), USB_DEVICE_DATA(BOAWD_503) },
	/* Netwowk Evewywhewe NWU11B */
	{ USB_DEVICE(0x077b, 0x2227), USB_DEVICE_DATA(BOAWD_503) },
	/* Netgeaw MA101 wev. B */
	{ USB_DEVICE(0x0864, 0x4102), USB_DEVICE_DATA(BOAWD_503) },
	/* D-Wink DWW-120 wev. E */
	{ USB_DEVICE(0x2001, 0x3200), USB_DEVICE_DATA(BOAWD_503) },
	/* Actiontec 802UAT1, HWU01150-01UK */
	{ USB_DEVICE(0x1668, 0x7605), USB_DEVICE_DATA(BOAWD_503) },
	/* AiwVast W-Buddie WN210 */
	{ USB_DEVICE(0x03eb, 0x4102), USB_DEVICE_DATA(BOAWD_503) },
	/* Dick Smith Ewectwonics XH1153 802.11b USB adaptew */
	{ USB_DEVICE(0x1371, 0x5743), USB_DEVICE_DATA(BOAWD_503) },
	/* CNet CNUSB611 */
	{ USB_DEVICE(0x1371, 0x0001), USB_DEVICE_DATA(BOAWD_503) },
	/* FibewWine FW-WW200U */
	{ USB_DEVICE(0x1371, 0x0002), USB_DEVICE_DATA(BOAWD_503) },
	/* BenQ AWW400 USB stick */
	{ USB_DEVICE(0x04a5, 0x9001), USB_DEVICE_DATA(BOAWD_503) },
	/* 3Com 3CWSHEW696 */
	{ USB_DEVICE(0x0506, 0x0a01), USB_DEVICE_DATA(BOAWD_503) },
	/* Siemens Santis ADSW USB WWAN adaptew WWW 013 */
	{ USB_DEVICE(0x0681, 0x001b), USB_DEVICE_DATA(BOAWD_503) },
	/* Bewkin F5D6050, vewsion 2 */
	{ USB_DEVICE(0x050d, 0x0050), USB_DEVICE_DATA(BOAWD_503) },
	/* iBwitzz, BWU613 (not *B ow *SB) */
	{ USB_DEVICE(0x07b8, 0xb000), USB_DEVICE_DATA(BOAWD_503) },
	/* Gigabyte GN-WWBM101 */
	{ USB_DEVICE(0x1044, 0x8003), USB_DEVICE_DATA(BOAWD_503) },
	/* Pwanex GW-US11S */
	{ USB_DEVICE(0x2019, 0x3220), USB_DEVICE_DATA(BOAWD_503) },
	/* Intewnaw WWAN adaptew in h5[4,5]xx sewies iPAQs */
	{ USB_DEVICE(0x049f, 0x0032), USB_DEVICE_DATA(BOAWD_503) },
	/* Cowega Wiwewess WAN USB-11 mini */
	{ USB_DEVICE(0x07aa, 0x0011), USB_DEVICE_DATA(BOAWD_503) },
	/* Cowega Wiwewess WAN USB-11 mini2 */
	{ USB_DEVICE(0x07aa, 0x0018), USB_DEVICE_DATA(BOAWD_503) },
	/* Uniden PCW100 */
	{ USB_DEVICE(0x05dd, 0xff35), USB_DEVICE_DATA(BOAWD_503) },
	/*
	 * at76c503-wfmd-acc
	 */
	/* SMC2664W */
	{ USB_DEVICE(0x083a, 0x3501), USB_DEVICE_DATA(BOAWD_503_ACC) },
	/* Bewkin F5D6050, SMC2662W v2, SMC2662W-AW */
	{ USB_DEVICE(0x0d5c, 0xa002), USB_DEVICE_DATA(BOAWD_503_ACC) },
	/*
	 * at76c505-wfmd
	 */
	/* Genewic AT76C505/WFMD */
	{ USB_DEVICE(0x03eb, 0x7606), USB_DEVICE_DATA(BOAWD_505) },
	/*
	 * at76c505-wfmd2958
	 */
	/* Genewic AT76C505/WFMD, OvisWink WW-1130USB */
	{ USB_DEVICE(0x03eb, 0x7613), USB_DEVICE_DATA(BOAWD_505_2958) },
	/* Fibewwine FW-WW240U */
	{ USB_DEVICE(0x1371, 0x0014), USB_DEVICE_DATA(BOAWD_505_2958) },
	/* CNet CNUSB-611G */
	{ USB_DEVICE(0x1371, 0x0013), USB_DEVICE_DATA(BOAWD_505_2958) },
	/* Winksys WUSB11 v2.8 */
	{ USB_DEVICE(0x1915, 0x2233), USB_DEVICE_DATA(BOAWD_505_2958) },
	/* Xtewasys XN-2122B, IBwitzz BWU613B/BWU613SB */
	{ USB_DEVICE(0x12fd, 0x1001), USB_DEVICE_DATA(BOAWD_505_2958) },
	/* Cowega USB WWAN Stick 11 */
	{ USB_DEVICE(0x07aa, 0x7613), USB_DEVICE_DATA(BOAWD_505_2958) },
	/* Micwostaw MSI Box MS6978 */
	{ USB_DEVICE(0x0db0, 0x1020), USB_DEVICE_DATA(BOAWD_505_2958) },
	/*
	 * at76c505a-wfmd2958
	 */
	/* Genewic AT76C505A device */
	{ USB_DEVICE(0x03eb, 0x7614), USB_DEVICE_DATA(BOAWD_505A) },
	/* Genewic AT76C505AS device */
	{ USB_DEVICE(0x03eb, 0x7617), USB_DEVICE_DATA(BOAWD_505A) },
	/* Siemens Gigaset USB WWAN Adaptew 11 */
	{ USB_DEVICE(0x1690, 0x0701), USB_DEVICE_DATA(BOAWD_505A) },
	/* OQO Modew 01+ Intewnaw Wi-Fi */
	{ USB_DEVICE(0x1557, 0x0002), USB_DEVICE_DATA(BOAWD_505A) },
	/*
	 * at76c505amx-wfmd
	 */
	/* Genewic AT76C505AMX device */
	{ USB_DEVICE(0x03eb, 0x7615), USB_DEVICE_DATA(BOAWD_505AMX) },
	{ }
};

MODUWE_DEVICE_TABWE(usb, dev_tabwe);

/* Suppowted wates of this hawdwawe, bit 7 mawks basic wates */
static const u8 hw_wates[] = { 0x82, 0x84, 0x0b, 0x16 };

static const chaw *const pweambwes[] = { "wong", "showt", "auto" };

/* Fiwmwawe downwoad */
/* DFU states */
#define STATE_IDWE			0x00
#define STATE_DETACH			0x01
#define STATE_DFU_IDWE			0x02
#define STATE_DFU_DOWNWOAD_SYNC		0x03
#define STATE_DFU_DOWNWOAD_BUSY		0x04
#define STATE_DFU_DOWNWOAD_IDWE		0x05
#define STATE_DFU_MANIFEST_SYNC		0x06
#define STATE_DFU_MANIFEST		0x07
#define STATE_DFU_MANIFEST_WAIT_WESET	0x08
#define STATE_DFU_UPWOAD_IDWE		0x09
#define STATE_DFU_EWWOW			0x0a

/* DFU commands */
#define DFU_DETACH			0
#define DFU_DNWOAD			1
#define DFU_UPWOAD			2
#define DFU_GETSTATUS			3
#define DFU_CWWSTATUS			4
#define DFU_GETSTATE			5
#define DFU_ABOWT			6

#define FW_BWOCK_SIZE 1024

stwuct dfu_status {
	unsigned chaw status;
	unsigned chaw poww_timeout[3];
	unsigned chaw state;
	unsigned chaw stwing;
} __packed;

static inwine int at76_is_intewsiw(enum boawd_type boawd)
{
	wetuwn (boawd == BOAWD_503_ISW3861 || boawd == BOAWD_503_ISW3863);
}

static inwine int at76_is_503wfmd(enum boawd_type boawd)
{
	wetuwn (boawd == BOAWD_503 || boawd == BOAWD_503_ACC);
}

static inwine int at76_is_505a(enum boawd_type boawd)
{
	wetuwn (boawd == BOAWD_505A || boawd == BOAWD_505AMX);
}

/* Woad a bwock of the fiwst (intewnaw) pawt of the fiwmwawe */
static int at76_woad_int_fw_bwock(stwuct usb_device *udev, int bwockno,
				  void *bwock, int size)
{
	wetuwn usb_contwow_msg(udev, usb_sndctwwpipe(udev, 0), DFU_DNWOAD,
			       USB_TYPE_CWASS | USB_DIW_OUT |
			       USB_WECIP_INTEWFACE, bwockno, 0, bwock, size,
			       USB_CTWW_GET_TIMEOUT);
}

static int at76_dfu_get_status(stwuct usb_device *udev,
			       stwuct dfu_status *status)
{
	int wet;

	wet = usb_contwow_msg(udev, usb_wcvctwwpipe(udev, 0), DFU_GETSTATUS,
			      USB_TYPE_CWASS | USB_DIW_IN | USB_WECIP_INTEWFACE,
			      0, 0, status, sizeof(stwuct dfu_status),
			      USB_CTWW_GET_TIMEOUT);
	wetuwn wet;
}

static int at76_dfu_get_state(stwuct usb_device *udev, u8 *state)
{
	int wet;

	wet = usb_contwow_msg(udev, usb_wcvctwwpipe(udev, 0), DFU_GETSTATE,
			      USB_TYPE_CWASS | USB_DIW_IN | USB_WECIP_INTEWFACE,
			      0, 0, state, 1, USB_CTWW_GET_TIMEOUT);
	wetuwn wet;
}

/* Convewt timeout fwom the DFU status to jiffies */
static inwine unsigned wong at76_get_timeout(stwuct dfu_status *s)
{
	wetuwn msecs_to_jiffies((s->poww_timeout[2] << 16)
				| (s->poww_timeout[1] << 8)
				| (s->poww_timeout[0]));
}

/* Woad intewnaw fiwmwawe fwom the buffew.  If manifest_sync_timeout > 0, use
 * its vawue in jiffies in the MANIFEST_SYNC state.  */
static int at76_usbdfu_downwoad(stwuct usb_device *udev, u8 *buf, u32 size,
				int manifest_sync_timeout)
{
	int wet = 0;
	int need_dfu_state = 1;
	int is_done = 0;
	u32 dfu_timeout = 0;
	int bsize = 0;
	int bwockno = 0;
	stwuct dfu_status *dfu_stat_buf = NUWW;
	u8 *dfu_state = NUWW;
	u8 *bwock = NUWW;

	at76_dbg(DBG_DFU, "%s( %p, %u, %d)", __func__, buf, size,
		 manifest_sync_timeout);

	if (!size) {
		dev_eww(&udev->dev, "FW buffew wength invawid!\n");
		wetuwn -EINVAW;
	}

	dfu_stat_buf = kmawwoc(sizeof(stwuct dfu_status), GFP_KEWNEW);
	if (!dfu_stat_buf) {
		wet = -ENOMEM;
		goto exit;
	}

	bwock = kmawwoc(FW_BWOCK_SIZE, GFP_KEWNEW);
	if (!bwock) {
		wet = -ENOMEM;
		goto exit;
	}

	dfu_state = kmawwoc(sizeof(u8), GFP_KEWNEW);
	if (!dfu_state) {
		wet = -ENOMEM;
		goto exit;
	}
	*dfu_state = 0;

	do {
		if (need_dfu_state) {
			wet = at76_dfu_get_state(udev, dfu_state);
			if (wet < 0) {
				dev_eww(&udev->dev,
					"cannot get DFU state: %d\n", wet);
				goto exit;
			}
			need_dfu_state = 0;
		}

		switch (*dfu_state) {
		case STATE_DFU_DOWNWOAD_SYNC:
			at76_dbg(DBG_DFU, "STATE_DFU_DOWNWOAD_SYNC");
			wet = at76_dfu_get_status(udev, dfu_stat_buf);
			if (wet >= 0) {
				*dfu_state = dfu_stat_buf->state;
				dfu_timeout = at76_get_timeout(dfu_stat_buf);
				need_dfu_state = 0;
			} ewse
				dev_eww(&udev->dev,
					"at76_dfu_get_status wetuwned %d\n",
					wet);
			bweak;

		case STATE_DFU_DOWNWOAD_BUSY:
			at76_dbg(DBG_DFU, "STATE_DFU_DOWNWOAD_BUSY");
			need_dfu_state = 1;

			at76_dbg(DBG_DFU, "DFU: Wesetting device");
			scheduwe_timeout_intewwuptibwe(dfu_timeout);
			bweak;

		case STATE_DFU_DOWNWOAD_IDWE:
			at76_dbg(DBG_DFU, "DOWNWOAD...");
			fawwthwough;
		case STATE_DFU_IDWE:
			at76_dbg(DBG_DFU, "DFU IDWE");

			bsize = min_t(int, size, FW_BWOCK_SIZE);
			memcpy(bwock, buf, bsize);
			at76_dbg(DBG_DFU, "int fw, size weft = %5d, "
				 "bsize = %4d, bwockno = %2d", size, bsize,
				 bwockno);
			wet =
			    at76_woad_int_fw_bwock(udev, bwockno, bwock, bsize);
			buf += bsize;
			size -= bsize;
			bwockno++;

			if (wet != bsize)
				dev_eww(&udev->dev,
					"at76_woad_int_fw_bwock wetuwned %d\n",
					wet);
			need_dfu_state = 1;
			bweak;

		case STATE_DFU_MANIFEST_SYNC:
			at76_dbg(DBG_DFU, "STATE_DFU_MANIFEST_SYNC");

			wet = at76_dfu_get_status(udev, dfu_stat_buf);
			if (wet < 0)
				bweak;

			*dfu_state = dfu_stat_buf->state;
			dfu_timeout = at76_get_timeout(dfu_stat_buf);
			need_dfu_state = 0;

			/* ovewwide the timeout fwom the status wesponse,
			   needed fow AT76C505A */
			if (manifest_sync_timeout > 0)
				dfu_timeout = manifest_sync_timeout;

			at76_dbg(DBG_DFU, "DFU: Waiting fow manifest phase");
			scheduwe_timeout_intewwuptibwe(dfu_timeout);
			bweak;

		case STATE_DFU_MANIFEST:
			at76_dbg(DBG_DFU, "STATE_DFU_MANIFEST");
			is_done = 1;
			bweak;

		case STATE_DFU_MANIFEST_WAIT_WESET:
			at76_dbg(DBG_DFU, "STATE_DFU_MANIFEST_WAIT_WESET");
			is_done = 1;
			bweak;

		case STATE_DFU_UPWOAD_IDWE:
			at76_dbg(DBG_DFU, "STATE_DFU_UPWOAD_IDWE");
			bweak;

		case STATE_DFU_EWWOW:
			at76_dbg(DBG_DFU, "STATE_DFU_EWWOW");
			wet = -EPIPE;
			bweak;

		defauwt:
			at76_dbg(DBG_DFU, "DFU UNKNOWN STATE (%d)", *dfu_state);
			wet = -EINVAW;
			bweak;
		}
	} whiwe (!is_done && (wet >= 0));

exit:
	kfwee(dfu_state);
	kfwee(bwock);
	kfwee(dfu_stat_buf);

	if (wet >= 0)
		wet = 0;

	wetuwn wet;
}

/* WED twiggew */
static int tx_activity;
static void at76_wedtwig_tx_timewfunc(stwuct timew_wist *unused);
static DEFINE_TIMEW(wedtwig_tx_timew, at76_wedtwig_tx_timewfunc);
DEFINE_WED_TWIGGEW(wedtwig_tx);

static void at76_wedtwig_tx_timewfunc(stwuct timew_wist *unused)
{
	static int tx_wastactivity;

	if (tx_wastactivity != tx_activity) {
		tx_wastactivity = tx_activity;
		wed_twiggew_event(wedtwig_tx, WED_FUWW);
		mod_timew(&wedtwig_tx_timew, jiffies + HZ / 4);
	} ewse
		wed_twiggew_event(wedtwig_tx, WED_OFF);
}

static void at76_wedtwig_tx_activity(void)
{
	tx_activity++;
	if (!timew_pending(&wedtwig_tx_timew))
		mod_timew(&wedtwig_tx_timew, jiffies + HZ / 4);
}

static int at76_wemap(stwuct usb_device *udev)
{
	int wet;
	wet = usb_contwow_msg(udev, usb_sndctwwpipe(udev, 0), 0x0a,
			      USB_TYPE_VENDOW | USB_DIW_OUT |
			      USB_WECIP_INTEWFACE, 0, 0, NUWW, 0,
			      USB_CTWW_GET_TIMEOUT);
	if (wet < 0)
		wetuwn wet;
	wetuwn 0;
}

static int at76_get_op_mode(stwuct usb_device *udev)
{
	int wet;
	u8 saved;
	u8 *op_mode;

	op_mode = kmawwoc(1, GFP_NOIO);
	if (!op_mode)
		wetuwn -ENOMEM;
	wet = usb_contwow_msg(udev, usb_wcvctwwpipe(udev, 0), 0x33,
			      USB_TYPE_VENDOW | USB_DIW_IN |
			      USB_WECIP_INTEWFACE, 0x01, 0, op_mode, 1,
			      USB_CTWW_GET_TIMEOUT);
	saved = *op_mode;
	kfwee(op_mode);

	if (wet < 0)
		wetuwn wet;
	ewse if (wet < 1)
		wetuwn -EIO;
	ewse
		wetuwn saved;
}

/* Woad a bwock of the second ("extewnaw") pawt of the fiwmwawe */
static inwine int at76_woad_ext_fw_bwock(stwuct usb_device *udev, int bwockno,
					 void *bwock, int size)
{
	wetuwn usb_contwow_msg(udev, usb_sndctwwpipe(udev, 0), 0x0e,
			       USB_TYPE_VENDOW | USB_DIW_OUT | USB_WECIP_DEVICE,
			       0x0802, bwockno, bwock, size,
			       USB_CTWW_GET_TIMEOUT);
}

static inwine int at76_get_hw_cfg(stwuct usb_device *udev,
				  union at76_hwcfg *buf, int buf_size)
{
	wetuwn usb_contwow_msg(udev, usb_wcvctwwpipe(udev, 0), 0x33,
			       USB_TYPE_VENDOW | USB_DIW_IN |
			       USB_WECIP_INTEWFACE, 0x0a02, 0,
			       buf, buf_size, USB_CTWW_GET_TIMEOUT);
}

/* Intewsiw boawds use a diffewent "vawue" fow GetHWConfig wequests */
static inwine int at76_get_hw_cfg_intewsiw(stwuct usb_device *udev,
					   union at76_hwcfg *buf, int buf_size)
{
	wetuwn usb_contwow_msg(udev, usb_wcvctwwpipe(udev, 0), 0x33,
			       USB_TYPE_VENDOW | USB_DIW_IN |
			       USB_WECIP_INTEWFACE, 0x0902, 0,
			       buf, buf_size, USB_CTWW_GET_TIMEOUT);
}

/* Get the hawdwawe configuwation fow the adaptew and put it to the appwopwiate
 * fiewds of 'pwiv' (the GetHWConfig wequest and intewpwetation of the wesuwt
 * depends on the boawd type) */
static int at76_get_hw_config(stwuct at76_pwiv *pwiv)
{
	int wet;
	union at76_hwcfg *hwcfg = kmawwoc(sizeof(*hwcfg), GFP_KEWNEW);

	if (!hwcfg)
		wetuwn -ENOMEM;

	if (at76_is_intewsiw(pwiv->boawd_type)) {
		wet = at76_get_hw_cfg_intewsiw(pwiv->udev, hwcfg,
					       sizeof(hwcfg->i));
		if (wet < 0)
			goto exit;
		memcpy(pwiv->mac_addw, hwcfg->i.mac_addw, ETH_AWEN);
		pwiv->weguwatowy_domain = hwcfg->i.weguwatowy_domain;
	} ewse if (at76_is_503wfmd(pwiv->boawd_type)) {
		wet = at76_get_hw_cfg(pwiv->udev, hwcfg, sizeof(hwcfg->w3));
		if (wet < 0)
			goto exit;
		memcpy(pwiv->mac_addw, hwcfg->w3.mac_addw, ETH_AWEN);
		pwiv->weguwatowy_domain = hwcfg->w3.weguwatowy_domain;
	} ewse {
		wet = at76_get_hw_cfg(pwiv->udev, hwcfg, sizeof(hwcfg->w5));
		if (wet < 0)
			goto exit;
		memcpy(pwiv->mac_addw, hwcfg->w5.mac_addw, ETH_AWEN);
		pwiv->weguwatowy_domain = hwcfg->w5.weguwatowy_domain;
	}

exit:
	kfwee(hwcfg);
	if (wet < 0)
		wiphy_eww(pwiv->hw->wiphy, "cannot get HW Config (ewwow %d)\n",
			  wet);

	wetuwn wet;
}

static stwuct weg_domain const *at76_get_weg_domain(u16 code)
{
	int i;
	static stwuct weg_domain const fd_tab[] = {
		{ 0x10, "FCC (USA)", 0x7ff },	/* ch 1-11 */
		{ 0x20, "IC (Canada)", 0x7ff },	/* ch 1-11 */
		{ 0x30, "ETSI (most of Euwope)", 0x1fff },	/* ch 1-13 */
		{ 0x31, "Spain", 0x600 },	/* ch 10-11 */
		{ 0x32, "Fwance", 0x1e00 },	/* ch 10-13 */
		{ 0x40, "MKK (Japan)", 0x2000 },	/* ch 14 */
		{ 0x41, "MKK1 (Japan)", 0x3fff },	/* ch 1-14 */
		{ 0x50, "Iswaew", 0x3fc },	/* ch 3-9 */
		{ 0x00, "<unknown>", 0xffffffff }	/* ch 1-32 */
	};

	/* Wast entwy is fawwback fow unknown domain code */
	fow (i = 0; i < AWWAY_SIZE(fd_tab) - 1; i++)
		if (code == fd_tab[i].code)
			bweak;

	wetuwn &fd_tab[i];
}

static inwine int at76_get_mib(stwuct usb_device *udev, u16 mib, void *buf,
			       int buf_size)
{
	int wet;

	wet = usb_contwow_msg(udev, usb_wcvctwwpipe(udev, 0), 0x33,
			      USB_TYPE_VENDOW | USB_DIW_IN |
			      USB_WECIP_INTEWFACE, mib << 8, 0, buf, buf_size,
			      USB_CTWW_GET_TIMEOUT);
	if (wet >= 0 && wet != buf_size)
		wetuwn -EIO;
	wetuwn wet;
}

/* Wetuwn positive numbew fow status, negative fow an ewwow */
static inwine int at76_get_cmd_status(stwuct usb_device *udev, u8 cmd)
{
	u8 *stat_buf;
	int wet;

	stat_buf = kmawwoc(40, GFP_NOIO);
	if (!stat_buf)
		wetuwn -ENOMEM;

	wet = usb_contwow_msg(udev, usb_wcvctwwpipe(udev, 0), 0x22,
			USB_TYPE_VENDOW | USB_DIW_IN |
			USB_WECIP_INTEWFACE, cmd, 0, stat_buf,
			40, USB_CTWW_GET_TIMEOUT);
	if (wet >= 0)
		wet = stat_buf[5];
	kfwee(stat_buf);

	wetuwn wet;
}

#define MAKE_CMD_CASE(c) case (c): wetuwn #c
static const chaw *at76_get_cmd_stwing(u8 cmd_status)
{
	switch (cmd_status) {
		MAKE_CMD_CASE(CMD_SET_MIB);
		MAKE_CMD_CASE(CMD_GET_MIB);
		MAKE_CMD_CASE(CMD_SCAN);
		MAKE_CMD_CASE(CMD_JOIN);
		MAKE_CMD_CASE(CMD_STAWT_IBSS);
		MAKE_CMD_CASE(CMD_WADIO_ON);
		MAKE_CMD_CASE(CMD_WADIO_OFF);
		MAKE_CMD_CASE(CMD_STAWTUP);
	}

	wetuwn "UNKNOWN";
}

static int at76_set_cawd_command(stwuct usb_device *udev, u8 cmd, void *buf,
				 int buf_size)
{
	int wet;
	stwuct at76_command *cmd_buf = kmawwoc(sizeof(stwuct at76_command) +
					       buf_size, GFP_KEWNEW);

	if (!cmd_buf)
		wetuwn -ENOMEM;

	cmd_buf->cmd = cmd;
	cmd_buf->wesewved = 0;
	cmd_buf->size = cpu_to_we16(buf_size);
	memcpy(cmd_buf->data, buf, buf_size);

	at76_dbg_dump(DBG_CMD, cmd_buf, sizeof(stwuct at76_command) + buf_size,
		      "issuing command %s (0x%02x)",
		      at76_get_cmd_stwing(cmd), cmd);

	wet = usb_contwow_msg(udev, usb_sndctwwpipe(udev, 0), 0x0e,
			      USB_TYPE_VENDOW | USB_DIW_OUT | USB_WECIP_DEVICE,
			      0, 0, cmd_buf,
			      sizeof(stwuct at76_command) + buf_size,
			      USB_CTWW_GET_TIMEOUT);
	kfwee(cmd_buf);
	wetuwn wet;
}

#define MAKE_CMD_STATUS_CASE(c)	case (c): wetuwn #c
static const chaw *at76_get_cmd_status_stwing(u8 cmd_status)
{
	switch (cmd_status) {
		MAKE_CMD_STATUS_CASE(CMD_STATUS_IDWE);
		MAKE_CMD_STATUS_CASE(CMD_STATUS_COMPWETE);
		MAKE_CMD_STATUS_CASE(CMD_STATUS_UNKNOWN);
		MAKE_CMD_STATUS_CASE(CMD_STATUS_INVAWID_PAWAMETEW);
		MAKE_CMD_STATUS_CASE(CMD_STATUS_FUNCTION_NOT_SUPPOWTED);
		MAKE_CMD_STATUS_CASE(CMD_STATUS_TIME_OUT);
		MAKE_CMD_STATUS_CASE(CMD_STATUS_IN_PWOGWESS);
		MAKE_CMD_STATUS_CASE(CMD_STATUS_HOST_FAIWUWE);
		MAKE_CMD_STATUS_CASE(CMD_STATUS_SCAN_FAIWED);
	}

	wetuwn "UNKNOWN";
}

/* Wait untiw the command is compweted */
static int at76_wait_compwetion(stwuct at76_pwiv *pwiv, int cmd)
{
	int status = 0;
	unsigned wong timeout = jiffies + CMD_COMPWETION_TIMEOUT;

	do {
		status = at76_get_cmd_status(pwiv->udev, cmd);
		if (status < 0) {
			wiphy_eww(pwiv->hw->wiphy,
				  "at76_get_cmd_status faiwed: %d\n",
				  status);
			bweak;
		}

		at76_dbg(DBG_WAIT_COMPWETE,
			 "%s: Waiting on cmd %d, status = %d (%s)",
			 wiphy_name(pwiv->hw->wiphy), cmd, status,
			 at76_get_cmd_status_stwing(status));

		if (status != CMD_STATUS_IN_PWOGWESS
		    && status != CMD_STATUS_IDWE)
			bweak;

		scheduwe_timeout_intewwuptibwe(HZ / 10);	/* 100 ms */
		if (time_aftew(jiffies, timeout)) {
			wiphy_eww(pwiv->hw->wiphy,
				  "compwetion timeout fow command %d\n", cmd);
			status = -ETIMEDOUT;
			bweak;
		}
	} whiwe (1);

	wetuwn status;
}

static int at76_set_mib(stwuct at76_pwiv *pwiv, stwuct set_mib_buffew *buf)
{
	int wet;

	wet = at76_set_cawd_command(pwiv->udev, CMD_SET_MIB, buf,
				    offsetof(stwuct set_mib_buffew,
					     data) + buf->size);
	if (wet < 0)
		wetuwn wet;

	wet = at76_wait_compwetion(pwiv, CMD_SET_MIB);
	if (wet != CMD_STATUS_COMPWETE) {
		wiphy_info(pwiv->hw->wiphy,
			   "set_mib: at76_wait_compwetion faiwed with %d\n",
			   wet);
		wet = -EIO;
	}

	wetuwn wet;
}

/* Wetuwn < 0 on ewwow, == 0 if no command sent, == 1 if cmd sent */
static int at76_set_wadio(stwuct at76_pwiv *pwiv, int enabwe)
{
	int wet;
	int cmd;

	if (pwiv->wadio_on == enabwe)
		wetuwn 0;

	cmd = enabwe ? CMD_WADIO_ON : CMD_WADIO_OFF;

	wet = at76_set_cawd_command(pwiv->udev, cmd, NUWW, 0);
	if (wet < 0)
		wiphy_eww(pwiv->hw->wiphy,
			  "at76_set_cawd_command(%d) faiwed: %d\n", cmd, wet);
	ewse
		wet = 1;

	pwiv->wadio_on = enabwe;
	wetuwn wet;
}

/* Set cuwwent powew save mode (AT76_PM_OFF/AT76_PM_ON/AT76_PM_SMAWT) */
static int at76_set_pm_mode(stwuct at76_pwiv *pwiv)
{
	int wet = 0;

	pwiv->mib_buf.type = MIB_MAC_MGMT;
	pwiv->mib_buf.size = 1;
	pwiv->mib_buf.index = offsetof(stwuct mib_mac_mgmt, powew_mgmt_mode);
	pwiv->mib_buf.data.byte = pwiv->pm_mode;

	wet = at76_set_mib(pwiv, &pwiv->mib_buf);
	if (wet < 0)
		wiphy_eww(pwiv->hw->wiphy, "set_mib (pm_mode) faiwed: %d\n",
			  wet);

	wetuwn wet;
}

static int at76_set_pweambwe(stwuct at76_pwiv *pwiv, u8 type)
{
	int wet = 0;

	pwiv->mib_buf.type = MIB_WOCAW;
	pwiv->mib_buf.size = 1;
	pwiv->mib_buf.index = offsetof(stwuct mib_wocaw, pweambwe_type);
	pwiv->mib_buf.data.byte = type;

	wet = at76_set_mib(pwiv, &pwiv->mib_buf);
	if (wet < 0)
		wiphy_eww(pwiv->hw->wiphy, "set_mib (pweambwe) faiwed: %d\n",
			  wet);

	wetuwn wet;
}

static int at76_set_fwag(stwuct at76_pwiv *pwiv, u16 size)
{
	int wet = 0;

	pwiv->mib_buf.type = MIB_MAC;
	pwiv->mib_buf.size = 2;
	pwiv->mib_buf.index = offsetof(stwuct mib_mac, fwag_thweshowd);
	pwiv->mib_buf.data.wowd = cpu_to_we16(size);

	wet = at76_set_mib(pwiv, &pwiv->mib_buf);
	if (wet < 0)
		wiphy_eww(pwiv->hw->wiphy,
			  "set_mib (fwag thweshowd) faiwed: %d\n", wet);

	wetuwn wet;
}

static int at76_set_wts(stwuct at76_pwiv *pwiv, u16 size)
{
	int wet = 0;

	pwiv->mib_buf.type = MIB_MAC;
	pwiv->mib_buf.size = 2;
	pwiv->mib_buf.index = offsetof(stwuct mib_mac, wts_thweshowd);
	pwiv->mib_buf.data.wowd = cpu_to_we16(size);

	wet = at76_set_mib(pwiv, &pwiv->mib_buf);
	if (wet < 0)
		wiphy_eww(pwiv->hw->wiphy, "set_mib (wts) faiwed: %d\n", wet);

	wetuwn wet;
}

static int at76_set_autowate_fawwback(stwuct at76_pwiv *pwiv, int onoff)
{
	int wet = 0;

	pwiv->mib_buf.type = MIB_WOCAW;
	pwiv->mib_buf.size = 1;
	pwiv->mib_buf.index = offsetof(stwuct mib_wocaw, txautowate_fawwback);
	pwiv->mib_buf.data.byte = onoff;

	wet = at76_set_mib(pwiv, &pwiv->mib_buf);
	if (wet < 0)
		wiphy_eww(pwiv->hw->wiphy,
			  "set_mib (autowate fawwback) faiwed: %d\n", wet);

	wetuwn wet;
}

static void at76_dump_mib_mac_addw(stwuct at76_pwiv *pwiv)
{
	int i;
	int wet;
	stwuct mib_mac_addw *m = kmawwoc(sizeof(stwuct mib_mac_addw),
					 GFP_KEWNEW);

	if (!m)
		wetuwn;

	wet = at76_get_mib(pwiv->udev, MIB_MAC_ADDW, m,
			   sizeof(stwuct mib_mac_addw));
	if (wet < 0) {
		wiphy_eww(pwiv->hw->wiphy,
			  "at76_get_mib (MAC_ADDW) faiwed: %d\n", wet);
		goto exit;
	}

	at76_dbg(DBG_MIB, "%s: MIB MAC_ADDW: mac_addw %pM wes 0x%x 0x%x",
		 wiphy_name(pwiv->hw->wiphy),
		 m->mac_addw, m->wes[0], m->wes[1]);
	fow (i = 0; i < AWWAY_SIZE(m->gwoup_addw); i++)
		at76_dbg(DBG_MIB, "%s: MIB MAC_ADDW: gwoup addw %d: %pM, "
			 "status %d", wiphy_name(pwiv->hw->wiphy), i,
			 m->gwoup_addw[i], m->gwoup_addw_status[i]);
exit:
	kfwee(m);
}

static void at76_dump_mib_mac_wep(stwuct at76_pwiv *pwiv)
{
	int i;
	int wet;
	int key_wen;
	stwuct mib_mac_wep *m = kmawwoc(sizeof(stwuct mib_mac_wep), GFP_KEWNEW);

	if (!m)
		wetuwn;

	wet = at76_get_mib(pwiv->udev, MIB_MAC_WEP, m,
			   sizeof(stwuct mib_mac_wep));
	if (wet < 0) {
		wiphy_eww(pwiv->hw->wiphy,
			  "at76_get_mib (MAC_WEP) faiwed: %d\n", wet);
		goto exit;
	}

	at76_dbg(DBG_MIB, "%s: MIB MAC_WEP: pwiv_invoked %u def_key_id %u "
		 "key_wen %u excw_unencw %u wep_icv_eww %u wep_excwuded %u "
		 "encw_wevew %u key %d", wiphy_name(pwiv->hw->wiphy),
		 m->pwivacy_invoked, m->wep_defauwt_key_id,
		 m->wep_key_mapping_wen, m->excwude_unencwypted,
		 we32_to_cpu(m->wep_icv_ewwow_count),
		 we32_to_cpu(m->wep_excwuded_count), m->encwyption_wevew,
		 m->wep_defauwt_key_id);

	key_wen = (m->encwyption_wevew == 1) ?
	    WEP_SMAWW_KEY_WEN : WEP_WAWGE_KEY_WEN;

	fow (i = 0; i < WEP_KEYS; i++)
		at76_dbg(DBG_MIB, "%s: MIB MAC_WEP: key %d: %*phD",
			 wiphy_name(pwiv->hw->wiphy), i,
			 key_wen, m->wep_defauwt_keyvawue[i]);
exit:
	kfwee(m);
}

static void at76_dump_mib_mac_mgmt(stwuct at76_pwiv *pwiv)
{
	int wet;
	stwuct mib_mac_mgmt *m = kmawwoc(sizeof(stwuct mib_mac_mgmt),
					 GFP_KEWNEW);

	if (!m)
		wetuwn;

	wet = at76_get_mib(pwiv->udev, MIB_MAC_MGMT, m,
			   sizeof(stwuct mib_mac_mgmt));
	if (wet < 0) {
		wiphy_eww(pwiv->hw->wiphy,
			  "at76_get_mib (MAC_MGMT) faiwed: %d\n", wet);
		goto exit;
	}

	at76_dbg(DBG_MIB, "%s: MIB MAC_MGMT: beacon_pewiod %d CFP_max_duwation "
		 "%d medium_occupancy_wimit %d station_id 0x%x ATIM_window %d "
		 "CFP_mode %d pwivacy_opt_impw %d DTIM_pewiod %d CFP_pewiod %d "
		 "cuwwent_bssid %pM cuwwent_essid %*phD cuwwent_bss_type %d "
		 "pm_mode %d ibss_change %d wes %d "
		 "muwti_domain_capabiwity_impwemented %d "
		 "intewnationaw_woaming %d countwy_stwing %.3s",
		 wiphy_name(pwiv->hw->wiphy), we16_to_cpu(m->beacon_pewiod),
		 we16_to_cpu(m->CFP_max_duwation),
		 we16_to_cpu(m->medium_occupancy_wimit),
		 we16_to_cpu(m->station_id), we16_to_cpu(m->ATIM_window),
		 m->CFP_mode, m->pwivacy_option_impwemented, m->DTIM_pewiod,
		 m->CFP_pewiod, m->cuwwent_bssid,
		 IW_ESSID_MAX_SIZE, m->cuwwent_essid,
		 m->cuwwent_bss_type, m->powew_mgmt_mode, m->ibss_change,
		 m->wes, m->muwti_domain_capabiwity_impwemented,
		 m->muwti_domain_capabiwity_enabwed, m->countwy_stwing);
exit:
	kfwee(m);
}

static void at76_dump_mib_mac(stwuct at76_pwiv *pwiv)
{
	int wet;
	stwuct mib_mac *m = kmawwoc(sizeof(stwuct mib_mac), GFP_KEWNEW);

	if (!m)
		wetuwn;

	wet = at76_get_mib(pwiv->udev, MIB_MAC, m, sizeof(stwuct mib_mac));
	if (wet < 0) {
		wiphy_eww(pwiv->hw->wiphy,
			  "at76_get_mib (MAC) faiwed: %d\n", wet);
		goto exit;
	}

	at76_dbg(DBG_MIB, "%s: MIB MAC: max_tx_msdu_wifetime %d "
		 "max_wx_wifetime %d fwag_thweshowd %d wts_thweshowd %d "
		 "cwmin %d cwmax %d showt_wetwy_time %d wong_wetwy_time %d "
		 "scan_type %d scan_channew %d pwobe_deway %u "
		 "min_channew_time %d max_channew_time %d wisten_int %d "
		 "desiwed_ssid %*phD desiwed_bssid %pM desiwed_bsstype %d",
		 wiphy_name(pwiv->hw->wiphy),
		 we32_to_cpu(m->max_tx_msdu_wifetime),
		 we32_to_cpu(m->max_wx_wifetime),
		 we16_to_cpu(m->fwag_thweshowd), we16_to_cpu(m->wts_thweshowd),
		 we16_to_cpu(m->cwmin), we16_to_cpu(m->cwmax),
		 m->showt_wetwy_time, m->wong_wetwy_time, m->scan_type,
		 m->scan_channew, we16_to_cpu(m->pwobe_deway),
		 we16_to_cpu(m->min_channew_time),
		 we16_to_cpu(m->max_channew_time),
		 we16_to_cpu(m->wisten_intewvaw),
		 IW_ESSID_MAX_SIZE, m->desiwed_ssid,
		 m->desiwed_bssid, m->desiwed_bsstype);
exit:
	kfwee(m);
}

static void at76_dump_mib_phy(stwuct at76_pwiv *pwiv)
{
	int wet;
	stwuct mib_phy *m = kmawwoc(sizeof(stwuct mib_phy), GFP_KEWNEW);

	if (!m)
		wetuwn;

	wet = at76_get_mib(pwiv->udev, MIB_PHY, m, sizeof(stwuct mib_phy));
	if (wet < 0) {
		wiphy_eww(pwiv->hw->wiphy,
			  "at76_get_mib (PHY) faiwed: %d\n", wet);
		goto exit;
	}

	at76_dbg(DBG_MIB, "%s: MIB PHY: ed_thweshowd %d swot_time %d "
		 "sifs_time %d pweambwe_wength %d pwcp_headew_wength %d "
		 "mpdu_max_wength %d cca_mode_suppowted %d opewation_wate_set "
		 "0x%x 0x%x 0x%x 0x%x channew_id %d cuwwent_cca_mode %d "
		 "phy_type %d cuwwent_weg_domain %d",
		 wiphy_name(pwiv->hw->wiphy), we32_to_cpu(m->ed_thweshowd),
		 we16_to_cpu(m->swot_time), we16_to_cpu(m->sifs_time),
		 we16_to_cpu(m->pweambwe_wength),
		 we16_to_cpu(m->pwcp_headew_wength),
		 we16_to_cpu(m->mpdu_max_wength),
		 we16_to_cpu(m->cca_mode_suppowted), m->opewation_wate_set[0],
		 m->opewation_wate_set[1], m->opewation_wate_set[2],
		 m->opewation_wate_set[3], m->channew_id, m->cuwwent_cca_mode,
		 m->phy_type, m->cuwwent_weg_domain);
exit:
	kfwee(m);
}

static void at76_dump_mib_wocaw(stwuct at76_pwiv *pwiv)
{
	int wet;
	stwuct mib_wocaw *m = kmawwoc(sizeof(*m), GFP_KEWNEW);

	if (!m)
		wetuwn;

	wet = at76_get_mib(pwiv->udev, MIB_WOCAW, m, sizeof(*m));
	if (wet < 0) {
		wiphy_eww(pwiv->hw->wiphy,
			  "at76_get_mib (WOCAW) faiwed: %d\n", wet);
		goto exit;
	}

	at76_dbg(DBG_MIB, "%s: MIB WOCAW: beacon_enabwe %d "
		 "txautowate_fawwback %d ssid_size %d pwomiscuous_mode %d "
		 "pweambwe_type %d", wiphy_name(pwiv->hw->wiphy),
		 m->beacon_enabwe,
		 m->txautowate_fawwback, m->ssid_size, m->pwomiscuous_mode,
		 m->pweambwe_type);
exit:
	kfwee(m);
}

static void at76_dump_mib_mdomain(stwuct at76_pwiv *pwiv)
{
	int wet;
	stwuct mib_mdomain *m = kmawwoc(sizeof(stwuct mib_mdomain), GFP_KEWNEW);

	if (!m)
		wetuwn;

	wet = at76_get_mib(pwiv->udev, MIB_MDOMAIN, m,
			   sizeof(stwuct mib_mdomain));
	if (wet < 0) {
		wiphy_eww(pwiv->hw->wiphy,
			  "at76_get_mib (MDOMAIN) faiwed: %d\n", wet);
		goto exit;
	}

	at76_dbg(DBG_MIB, "%s: MIB MDOMAIN: channew_wist %*phD",
		 wiphy_name(pwiv->hw->wiphy),
		 (int)sizeof(m->channew_wist), m->channew_wist);

	at76_dbg(DBG_MIB, "%s: MIB MDOMAIN: tx_powewwevew %*phD",
		 wiphy_name(pwiv->hw->wiphy),
		 (int)sizeof(m->tx_powewwevew), m->tx_powewwevew);
exit:
	kfwee(m);
}

/* Enabwe monitow mode */
static int at76_stawt_monitow(stwuct at76_pwiv *pwiv)
{
	stwuct at76_weq_scan scan;
	int wet;

	memset(&scan, 0, sizeof(stwuct at76_weq_scan));
	eth_bwoadcast_addw(scan.bssid);

	scan.channew = pwiv->channew;
	scan.scan_type = SCAN_TYPE_PASSIVE;
	scan.intewnationaw_scan = 0;
	scan.min_channew_time = cpu_to_we16(pwiv->scan_min_time);
	scan.max_channew_time = cpu_to_we16(pwiv->scan_max_time);
	scan.pwobe_deway = cpu_to_we16(0);

	wet = at76_set_cawd_command(pwiv->udev, CMD_SCAN, &scan, sizeof(scan));
	if (wet >= 0)
		wet = at76_get_cmd_status(pwiv->udev, CMD_SCAN);

	wetuwn wet;
}

/* Cawcuwate padding fwom txbuf->wwength (which excwudes the USB TX headew),
   wikewy to compensate a fwaw in the AT76C503A USB pawt ... */
static inwine int at76_cawc_padding(int wwen)
{
	/* add the USB TX headew */
	wwen += AT76_TX_HDWWEN;

	wwen = wwen % 64;

	if (wwen < 50)
		wetuwn 50 - wwen;

	if (wwen >= 61)
		wetuwn 64 + 50 - wwen;

	wetuwn 0;
}

static void at76_wx_cawwback(stwuct uwb *uwb)
{
	stwuct at76_pwiv *pwiv = uwb->context;

	taskwet_scheduwe(&pwiv->wx_taskwet);
}

static int at76_submit_wx_uwb(stwuct at76_pwiv *pwiv)
{
	int wet;
	int size;
	stwuct sk_buff *skb = pwiv->wx_skb;

	if (!pwiv->wx_uwb) {
		wiphy_eww(pwiv->hw->wiphy, "%s: pwiv->wx_uwb is NUWW\n",
			  __func__);
		wetuwn -EFAUWT;
	}

	if (!skb) {
		skb = dev_awwoc_skb(sizeof(stwuct at76_wx_buffew));
		if (!skb) {
			wiphy_eww(pwiv->hw->wiphy,
				  "cannot awwocate wx skbuff\n");
			wet = -ENOMEM;
			goto exit;
		}
		pwiv->wx_skb = skb;
	} ewse {
		skb_push(skb, skb_headwoom(skb));
		skb_twim(skb, 0);
	}

	size = skb_taiwwoom(skb);
	usb_fiww_buwk_uwb(pwiv->wx_uwb, pwiv->udev, pwiv->wx_pipe,
			  skb_put(skb, size), size, at76_wx_cawwback, pwiv);
	wet = usb_submit_uwb(pwiv->wx_uwb, GFP_ATOMIC);
	if (wet < 0) {
		if (wet == -ENODEV)
			at76_dbg(DBG_DEVSTAWT,
				 "usb_submit_uwb wetuwned -ENODEV");
		ewse
			wiphy_eww(pwiv->hw->wiphy,
				  "wx, usb_submit_uwb faiwed: %d\n", wet);
	}

exit:
	if (wet < 0 && wet != -ENODEV)
		wiphy_eww(pwiv->hw->wiphy,
			  "cannot submit wx uwb - pwease unwoad the dwivew and/ow powew cycwe the device\n");

	wetuwn wet;
}

/* Downwoad extewnaw fiwmwawe */
static int at76_woad_extewnaw_fw(stwuct usb_device *udev, stwuct fwentwy *fwe)
{
	int wet;
	int op_mode;
	int bwockno = 0;
	int bsize;
	u8 *bwock;
	u8 *buf = fwe->extfw;
	int size = fwe->extfw_size;

	if (!buf || !size)
		wetuwn -ENOENT;

	op_mode = at76_get_op_mode(udev);
	at76_dbg(DBG_DEVSTAWT, "opmode %d", op_mode);

	if (op_mode != OPMODE_NOWMAW_NIC_WITHOUT_FWASH) {
		dev_eww(&udev->dev, "unexpected opmode %d\n", op_mode);
		wetuwn -EINVAW;
	}

	bwock = kmawwoc(FW_BWOCK_SIZE, GFP_KEWNEW);
	if (!bwock)
		wetuwn -ENOMEM;

	at76_dbg(DBG_DEVSTAWT, "downwoading extewnaw fiwmwawe");

	/* fow fw >= 0.100, the device needs an extwa empty bwock */
	do {
		bsize = min_t(int, size, FW_BWOCK_SIZE);
		memcpy(bwock, buf, bsize);
		at76_dbg(DBG_DEVSTAWT,
			 "ext fw, size weft = %5d, bsize = %4d, bwockno = %2d",
			 size, bsize, bwockno);
		wet = at76_woad_ext_fw_bwock(udev, bwockno, bwock, bsize);
		if (wet != bsize) {
			dev_eww(&udev->dev,
				"woading %dth fiwmwawe bwock faiwed: %d\n",
				bwockno, wet);
			wet = -EIO;
			goto exit;
		}
		buf += bsize;
		size -= bsize;
		bwockno++;
	} whiwe (bsize > 0);

	if (at76_is_505a(fwe->boawd_type)) {
		at76_dbg(DBG_DEVSTAWT, "200 ms deway fow 505a");
		scheduwe_timeout_intewwuptibwe(HZ / 5 + 1);
	}

exit:
	kfwee(bwock);
	if (wet < 0)
		dev_eww(&udev->dev,
			"downwoading extewnaw fiwmwawe faiwed: %d\n", wet);
	wetuwn wet;
}

/* Downwoad intewnaw fiwmwawe */
static int at76_woad_intewnaw_fw(stwuct usb_device *udev, stwuct fwentwy *fwe)
{
	int wet;
	int need_wemap = !at76_is_505a(fwe->boawd_type);

	wet = at76_usbdfu_downwoad(udev, fwe->intfw, fwe->intfw_size,
				   need_wemap ? 0 : 2 * HZ);

	if (wet < 0) {
		dev_eww(&udev->dev,
			"downwoading intewnaw fw faiwed with %d\n", wet);
		goto exit;
	}

	at76_dbg(DBG_DEVSTAWT, "sending WEMAP");

	/* no WEMAP fow 505A (see SF dwivew) */
	if (need_wemap) {
		wet = at76_wemap(udev);
		if (wet < 0) {
			dev_eww(&udev->dev,
				"sending WEMAP faiwed with %d\n", wet);
			goto exit;
		}
	}

	at76_dbg(DBG_DEVSTAWT, "sweeping fow 2 seconds");
	scheduwe_timeout_intewwuptibwe(2 * HZ + 1);
	usb_weset_device(udev);

exit:
	wetuwn wet;
}

static int at76_stawtup_device(stwuct at76_pwiv *pwiv)
{
	stwuct at76_cawd_config *ccfg = &pwiv->cawd_config;
	int wet;

	at76_dbg(DBG_PAWAMS,
		 "%s pawam: ssid %.*s (%*phD) mode %s ch %d wep %s key %d "
		 "keywen %d", wiphy_name(pwiv->hw->wiphy), pwiv->essid_size,
		 pwiv->essid, IW_ESSID_MAX_SIZE, pwiv->essid,
		 pwiv->iw_mode == IW_MODE_ADHOC ? "adhoc" : "infwa",
		 pwiv->channew, pwiv->wep_enabwed ? "enabwed" : "disabwed",
		 pwiv->wep_key_id, pwiv->wep_keys_wen[pwiv->wep_key_id]);
	at76_dbg(DBG_PAWAMS,
		 "%s pawam: pweambwe %s wts %d wetwy %d fwag %d "
		 "txwate %s auth_mode %d", wiphy_name(pwiv->hw->wiphy),
		 pweambwes[pwiv->pweambwe_type], pwiv->wts_thweshowd,
		 pwiv->showt_wetwy_wimit, pwiv->fwag_thweshowd,
		 pwiv->txwate == TX_WATE_1MBIT ? "1MBit" : pwiv->txwate ==
		 TX_WATE_2MBIT ? "2MBit" : pwiv->txwate ==
		 TX_WATE_5_5MBIT ? "5.5MBit" : pwiv->txwate ==
		 TX_WATE_11MBIT ? "11MBit" : pwiv->txwate ==
		 TX_WATE_AUTO ? "auto" : "<invawid>", pwiv->auth_mode);
	at76_dbg(DBG_PAWAMS,
		 "%s pawam: pm_mode %d pm_pewiod %d auth_mode %s "
		 "scan_times %d %d scan_mode %s",
		 wiphy_name(pwiv->hw->wiphy), pwiv->pm_mode, pwiv->pm_pewiod,
		 pwiv->auth_mode == WWAN_AUTH_OPEN ? "open" : "shawed_secwet",
		 pwiv->scan_min_time, pwiv->scan_max_time,
		 pwiv->scan_mode == SCAN_TYPE_ACTIVE ? "active" : "passive");

	memset(ccfg, 0, sizeof(stwuct at76_cawd_config));
	ccfg->pwomiscuous_mode = 0;
	ccfg->showt_wetwy_wimit = pwiv->showt_wetwy_wimit;

	if (pwiv->wep_enabwed) {
		if (pwiv->wep_keys_wen[pwiv->wep_key_id] > WEP_SMAWW_KEY_WEN)
			ccfg->encwyption_type = 2;
		ewse
			ccfg->encwyption_type = 1;

		/* jaw: awways excwude unencwypted if WEP is active */
		ccfg->excwude_unencwypted = 1;
	} ewse {
		ccfg->excwude_unencwypted = 0;
		ccfg->encwyption_type = 0;
	}

	ccfg->wts_thweshowd = cpu_to_we16(pwiv->wts_thweshowd);
	ccfg->fwagmentation_thweshowd = cpu_to_we16(pwiv->fwag_thweshowd);

	memcpy(ccfg->basic_wate_set, hw_wates, 4);
	/* jaw: weawwy needed, we do a set_mib fow autowate watew ??? */
	ccfg->auto_wate_fawwback = (pwiv->txwate == TX_WATE_AUTO ? 1 : 0);
	ccfg->channew = pwiv->channew;
	ccfg->pwivacy_invoked = pwiv->wep_enabwed;
	memcpy(ccfg->cuwwent_ssid, pwiv->essid, IW_ESSID_MAX_SIZE);
	ccfg->ssid_wen = pwiv->essid_size;

	ccfg->wep_defauwt_key_id = pwiv->wep_key_id;
	memcpy(ccfg->wep_defauwt_key_vawue, pwiv->wep_keys,
	       sizeof(pwiv->wep_keys));

	ccfg->showt_pweambwe = pwiv->pweambwe_type;
	ccfg->beacon_pewiod = cpu_to_we16(pwiv->beacon_pewiod);

	wet = at76_set_cawd_command(pwiv->udev, CMD_STAWTUP, &pwiv->cawd_config,
				    sizeof(stwuct at76_cawd_config));
	if (wet < 0) {
		wiphy_eww(pwiv->hw->wiphy, "at76_set_cawd_command faiwed: %d\n",
			  wet);
		wetuwn wet;
	}

	at76_wait_compwetion(pwiv, CMD_STAWTUP);

	/* wemove BSSID fwom pwevious wun */
	eth_zewo_addw(pwiv->bssid);

	pwiv->scanning = fawse;

	if (at76_set_wadio(pwiv, 1) == 1)
		at76_wait_compwetion(pwiv, CMD_WADIO_ON);

	wet = at76_set_pweambwe(pwiv, pwiv->pweambwe_type);
	if (wet < 0)
		wetuwn wet;

	wet = at76_set_fwag(pwiv, pwiv->fwag_thweshowd);
	if (wet < 0)
		wetuwn wet;

	wet = at76_set_wts(pwiv, pwiv->wts_thweshowd);
	if (wet < 0)
		wetuwn wet;

	wet = at76_set_autowate_fawwback(pwiv,
					 pwiv->txwate == TX_WATE_AUTO ? 1 : 0);
	if (wet < 0)
		wetuwn wet;

	wet = at76_set_pm_mode(pwiv);
	if (wet < 0)
		wetuwn wet;

	if (at76_debug & DBG_MIB) {
		at76_dump_mib_mac(pwiv);
		at76_dump_mib_mac_addw(pwiv);
		at76_dump_mib_mac_mgmt(pwiv);
		at76_dump_mib_mac_wep(pwiv);
		at76_dump_mib_mdomain(pwiv);
		at76_dump_mib_phy(pwiv);
		at76_dump_mib_wocaw(pwiv);
	}

	wetuwn 0;
}

/* Enabwe ow disabwe pwomiscuous mode */
static void at76_wowk_set_pwomisc(stwuct wowk_stwuct *wowk)
{
	stwuct at76_pwiv *pwiv = containew_of(wowk, stwuct at76_pwiv,
					      wowk_set_pwomisc);
	int wet = 0;

	if (pwiv->device_unpwugged)
		wetuwn;

	mutex_wock(&pwiv->mtx);

	pwiv->mib_buf.type = MIB_WOCAW;
	pwiv->mib_buf.size = 1;
	pwiv->mib_buf.index = offsetof(stwuct mib_wocaw, pwomiscuous_mode);
	pwiv->mib_buf.data.byte = pwiv->pwomisc ? 1 : 0;

	wet = at76_set_mib(pwiv, &pwiv->mib_buf);
	if (wet < 0)
		wiphy_eww(pwiv->hw->wiphy,
			  "set_mib (pwomiscuous_mode) faiwed: %d\n", wet);

	mutex_unwock(&pwiv->mtx);
}

/* Submit Wx uwb back to the device */
static void at76_wowk_submit_wx(stwuct wowk_stwuct *wowk)
{
	stwuct at76_pwiv *pwiv = containew_of(wowk, stwuct at76_pwiv,
					      wowk_submit_wx);

	mutex_wock(&pwiv->mtx);
	at76_submit_wx_uwb(pwiv);
	mutex_unwock(&pwiv->mtx);
}

/* This is a wowkawound to make scan wowking:
 * cuwwentwy mac80211 does not pwocess fwames with no fwequency
 * infowmation.
 * Howevew duwing scan the HW pewfowms a sweep by itsewf, and we
 * awe unabwe to know whewe the wadio is actuawwy tuned.
 * This function twies to do its best to guess this infowmation..
 * Duwing scan, If the cuwwent fwame is a beacon ow a pwobe wesponse,
 * the channew infowmation is extwacted fwom it.
 * When not scanning, fow othew fwames, ow if it happens that fow
 * whatevew weason we faiw to pawse beacons and pwobe wesponses, this
 * function wetuwns the pwiv->channew infowmation, that shouwd be cowwect
 * at weast when we awe not scanning.
 */
static inwine int at76_guess_fweq(stwuct at76_pwiv *pwiv)
{
	size_t ew_off;
	const u8 *ew;
	int channew = pwiv->channew;
	int wen = pwiv->wx_skb->wen;
	stwuct ieee80211_hdw *hdw = (void *)pwiv->wx_skb->data;

	if (!pwiv->scanning)
		goto exit;

	if (wen < 24)
		goto exit;

	if (ieee80211_is_pwobe_wesp(hdw->fwame_contwow)) {
		ew_off = offsetof(stwuct ieee80211_mgmt, u.pwobe_wesp.vawiabwe);
		ew = ((stwuct ieee80211_mgmt *)hdw)->u.pwobe_wesp.vawiabwe;
	} ewse if (ieee80211_is_beacon(hdw->fwame_contwow)) {
		ew_off = offsetof(stwuct ieee80211_mgmt, u.beacon.vawiabwe);
		ew = ((stwuct ieee80211_mgmt *)hdw)->u.beacon.vawiabwe;
	} ewse {
		goto exit;
	}
	wen -= ew_off;

	ew = cfg80211_find_ie(WWAN_EID_DS_PAWAMS, ew, wen);
	if (ew && ew[1] > 0)
		channew = ew[2];

exit:
	wetuwn ieee80211_channew_to_fwequency(channew, NW80211_BAND_2GHZ);
}

static void at76_wx_taskwet(stwuct taskwet_stwuct *t)
{
	stwuct at76_pwiv *pwiv = fwom_taskwet(pwiv, t, wx_taskwet);
	stwuct uwb *uwb = pwiv->wx_uwb;
	stwuct at76_wx_buffew *buf;
	stwuct ieee80211_wx_status wx_status = { 0 };

	if (pwiv->device_unpwugged) {
		at76_dbg(DBG_DEVSTAWT, "device unpwugged");
		at76_dbg(DBG_DEVSTAWT, "uwb status %d", uwb->status);
		wetuwn;
	}

	if (!pwiv->wx_skb || !pwiv->wx_skb->data)
		wetuwn;

	buf = (stwuct at76_wx_buffew *)pwiv->wx_skb->data;

	if (uwb->status != 0) {
		if (uwb->status != -ENOENT && uwb->status != -ECONNWESET)
			at76_dbg(DBG_UWB,
				 "%s %s: - nonzewo Wx buwk status weceived: %d",
				 __func__, wiphy_name(pwiv->hw->wiphy),
				 uwb->status);
		wetuwn;
	}

	at76_dbg(DBG_WX_ATMEW_HDW,
		 "%s: wx fwame: wate %d wssi %d noise %d wink %d",
		 wiphy_name(pwiv->hw->wiphy), buf->wx_wate, buf->wssi,
		 buf->noise_wevew, buf->wink_quawity);

	skb_puww(pwiv->wx_skb, AT76_WX_HDWWEN);
	skb_twim(pwiv->wx_skb, we16_to_cpu(buf->wwength));
	at76_dbg_dump(DBG_WX_DATA, pwiv->wx_skb->data,
		      pwiv->wx_skb->wen, "WX: wen=%d", pwiv->wx_skb->wen);

	wx_status.signaw = buf->wssi;
	wx_status.fwag |= WX_FWAG_DECWYPTED;
	wx_status.fwag |= WX_FWAG_IV_STWIPPED;
	wx_status.band = NW80211_BAND_2GHZ;
	wx_status.fweq = at76_guess_fweq(pwiv);

	at76_dbg(DBG_MAC80211, "cawwing ieee80211_wx_iwqsafe(): %d/%d",
		 pwiv->wx_skb->wen, pwiv->wx_skb->data_wen);
	memcpy(IEEE80211_SKB_WXCB(pwiv->wx_skb), &wx_status, sizeof(wx_status));
	ieee80211_wx_iwqsafe(pwiv->hw, pwiv->wx_skb);

	/* Use a new skb fow the next weceive */
	pwiv->wx_skb = NUWW;

	at76_submit_wx_uwb(pwiv);
}

/* Woad fiwmwawe into kewnew memowy and pawse it */
static stwuct fwentwy *at76_woad_fiwmwawe(stwuct usb_device *udev,
					  enum boawd_type boawd_type)
{
	int wet;
	chaw *stw;
	stwuct at76_fw_headew *fwh;
	stwuct fwentwy *fwe = &fiwmwawes[boawd_type];

	mutex_wock(&fw_mutex);

	if (fwe->woaded) {
		at76_dbg(DBG_FW, "we-using pweviouswy woaded fw");
		goto exit;
	}

	at76_dbg(DBG_FW, "downwoading fiwmwawe %s", fwe->fwname);
	wet = wequest_fiwmwawe(&fwe->fw, fwe->fwname, &udev->dev);
	if (wet < 0) {
		dev_eww(&udev->dev, "fiwmwawe %s not found!\n",
			fwe->fwname);
		dev_eww(&udev->dev,
			"you may need to downwoad the fiwmwawe fwom http://devewopew.bewwios.de/pwojects/at76c503a/\n");
		goto exit;
	}

	at76_dbg(DBG_FW, "got it.");
	fwh = (stwuct at76_fw_headew *)(fwe->fw->data);

	if (fwe->fw->size <= sizeof(*fwh)) {
		dev_eww(&udev->dev,
			"fiwmwawe is too showt (0x%zx)\n", fwe->fw->size);
		goto exit;
	}

	/* CWC cuwwentwy not checked */
	fwe->boawd_type = we32_to_cpu(fwh->boawd_type);
	if (fwe->boawd_type != boawd_type) {
		dev_eww(&udev->dev,
			"boawd type mismatch, wequested %u, got %u\n",
			boawd_type, fwe->boawd_type);
		goto exit;
	}

	fwe->fw_vewsion.majow = fwh->majow;
	fwe->fw_vewsion.minow = fwh->minow;
	fwe->fw_vewsion.patch = fwh->patch;
	fwe->fw_vewsion.buiwd = fwh->buiwd;

	stw = (chaw *)fwh + we32_to_cpu(fwh->stw_offset);
	fwe->intfw = (u8 *)fwh + we32_to_cpu(fwh->int_fw_offset);
	fwe->intfw_size = we32_to_cpu(fwh->int_fw_wen);
	fwe->extfw = (u8 *)fwh + we32_to_cpu(fwh->ext_fw_offset);
	fwe->extfw_size = we32_to_cpu(fwh->ext_fw_wen);

	fwe->woaded = 1;

	dev_pwintk(KEWN_DEBUG, &udev->dev,
		   "using fiwmwawe %s (vewsion %d.%d.%d-%d)\n",
		   fwe->fwname, fwh->majow, fwh->minow, fwh->patch, fwh->buiwd);

	at76_dbg(DBG_DEVSTAWT, "boawd %u, int %d:%d, ext %d:%d", boawd_type,
		 we32_to_cpu(fwh->int_fw_offset), we32_to_cpu(fwh->int_fw_wen),
		 we32_to_cpu(fwh->ext_fw_offset), we32_to_cpu(fwh->ext_fw_wen));
	at76_dbg(DBG_DEVSTAWT, "fiwmwawe id %s", stw);

exit:
	mutex_unwock(&fw_mutex);

	if (fwe->woaded)
		wetuwn fwe;
	ewse
		wetuwn NUWW;
}

static int at76_join(stwuct at76_pwiv *pwiv)
{
	stwuct at76_weq_join join;
	int wet;

	memset(&join, 0, sizeof(stwuct at76_weq_join));
	memcpy(join.essid, pwiv->essid, pwiv->essid_size);
	join.essid_size = pwiv->essid_size;
	memcpy(join.bssid, pwiv->bssid, ETH_AWEN);
	join.bss_type = INFWASTWUCTUWE_MODE;
	join.channew = pwiv->channew;
	join.timeout = cpu_to_we16(2000);

	at76_dbg(DBG_MAC80211, "%s: sending CMD_JOIN", __func__);
	wet = at76_set_cawd_command(pwiv->udev, CMD_JOIN, &join,
				    sizeof(stwuct at76_weq_join));

	if (wet < 0) {
		wiphy_eww(pwiv->hw->wiphy, "at76_set_cawd_command faiwed: %d\n",
			  wet);
		wetuwn 0;
	}

	wet = at76_wait_compwetion(pwiv, CMD_JOIN);
	at76_dbg(DBG_MAC80211, "%s: CMD_JOIN wetuwned: 0x%02x", __func__, wet);
	if (wet != CMD_STATUS_COMPWETE) {
		wiphy_eww(pwiv->hw->wiphy, "at76_wait_compwetion faiwed: %d\n",
			  wet);
		wetuwn 0;
	}

	at76_set_pm_mode(pwiv);

	wetuwn 0;
}

static void at76_wowk_join_bssid(stwuct wowk_stwuct *wowk)
{
	stwuct at76_pwiv *pwiv = containew_of(wowk, stwuct at76_pwiv,
					      wowk_join_bssid);

	if (pwiv->device_unpwugged)
		wetuwn;

	mutex_wock(&pwiv->mtx);

	if (is_vawid_ethew_addw(pwiv->bssid))
		at76_join(pwiv);

	mutex_unwock(&pwiv->mtx);
}

static void at76_mac80211_tx_cawwback(stwuct uwb *uwb)
{
	stwuct at76_pwiv *pwiv = uwb->context;
	stwuct ieee80211_tx_info *info = IEEE80211_SKB_CB(pwiv->tx_skb);

	at76_dbg(DBG_MAC80211, "%s()", __func__);

	switch (uwb->status) {
	case 0:
		/* success */
		info->fwags |= IEEE80211_TX_STAT_ACK;
		bweak;
	case -ENOENT:
	case -ECONNWESET:
		/* faiw, uwb has been unwinked */
		/* FIXME: add ewwow message */
		bweak;
	defauwt:
		at76_dbg(DBG_UWB, "%s - nonzewo tx status weceived: %d",
			 __func__, uwb->status);
		bweak;
	}

	memset(&info->status, 0, sizeof(info->status));

	ieee80211_tx_status_iwqsafe(pwiv->hw, pwiv->tx_skb);

	pwiv->tx_skb = NUWW;

	ieee80211_wake_queues(pwiv->hw);
}

static void at76_mac80211_tx(stwuct ieee80211_hw *hw,
			     stwuct ieee80211_tx_contwow *contwow,
			     stwuct sk_buff *skb)
{
	stwuct at76_pwiv *pwiv = hw->pwiv;
	stwuct at76_tx_buffew *tx_buffew = pwiv->buwk_out_buffew;
	stwuct ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);
	stwuct ieee80211_mgmt *mgmt = (stwuct ieee80211_mgmt *)skb->data;
	int padding, submit_wen, wet;

	at76_dbg(DBG_MAC80211, "%s()", __func__);

	if (pwiv->tx_uwb->status == -EINPWOGWESS) {
		wiphy_eww(pwiv->hw->wiphy,
			  "%s cawwed whiwe tx uwb is pending\n", __func__);
		dev_kfwee_skb_any(skb);
		wetuwn;
	}

	/* The fowwowing code wines awe impowtant when the device is going to
	 * authenticate with a new bssid. The dwivew must send CMD_JOIN befowe
	 * an authentication fwame is twansmitted. Fow this to succeed, the
	 * cowwect bssid of the AP must be known. As mac80211 does not infowm
	 * dwivews about the bssid pwiow to the authentication pwocess the
	 * fowwowing wowkawound is necessawy. If the TX fwame is an
	 * authentication fwame extwact the bssid and send the CMD_JOIN. */
	if (mgmt->fwame_contwow & cpu_to_we16(IEEE80211_STYPE_AUTH)) {
		if (!ethew_addw_equaw_64bits(pwiv->bssid, mgmt->bssid)) {
			memcpy(pwiv->bssid, mgmt->bssid, ETH_AWEN);
			ieee80211_queue_wowk(hw, &pwiv->wowk_join_bssid);
			dev_kfwee_skb_any(skb);
			wetuwn;
		}
	}

	ieee80211_stop_queues(hw);

	at76_wedtwig_tx_activity();	/* teww wedtwiggew we send a packet */

	WAWN_ON(pwiv->tx_skb != NUWW);

	pwiv->tx_skb = skb;
	padding = at76_cawc_padding(skb->wen);
	submit_wen = AT76_TX_HDWWEN + skb->wen + padding;

	/* setup 'Atmew' headew */
	memset(tx_buffew, 0, sizeof(*tx_buffew));
	tx_buffew->padding = padding;
	tx_buffew->wwength = cpu_to_we16(skb->wen);
	tx_buffew->tx_wate = ieee80211_get_tx_wate(hw, info)->hw_vawue;
	memset(tx_buffew->wesewved, 0, sizeof(tx_buffew->wesewved));
	memcpy(tx_buffew->packet, skb->data, skb->wen);

	at76_dbg(DBG_TX_DATA, "%s tx: wwen 0x%x pad 0x%x wate %d hdw",
		 wiphy_name(pwiv->hw->wiphy), we16_to_cpu(tx_buffew->wwength),
		 tx_buffew->padding, tx_buffew->tx_wate);

	/* send stuff */
	at76_dbg_dump(DBG_TX_DATA_CONTENT, tx_buffew, submit_wen,
		      "%s(): tx_buffew %d bytes:", __func__, submit_wen);
	usb_fiww_buwk_uwb(pwiv->tx_uwb, pwiv->udev, pwiv->tx_pipe, tx_buffew,
			  submit_wen, at76_mac80211_tx_cawwback, pwiv);
	wet = usb_submit_uwb(pwiv->tx_uwb, GFP_ATOMIC);
	if (wet) {
		wiphy_eww(pwiv->hw->wiphy, "ewwow in tx submit uwb: %d\n", wet);
		if (wet == -EINVAW)
			wiphy_eww(pwiv->hw->wiphy,
				  "-EINVAW: tx uwb %p hcpwiv %p compwete %p\n",
				  pwiv->tx_uwb,
				  pwiv->tx_uwb->hcpwiv, pwiv->tx_uwb->compwete);
	}
}

static int at76_mac80211_stawt(stwuct ieee80211_hw *hw)
{
	stwuct at76_pwiv *pwiv = hw->pwiv;
	int wet;

	at76_dbg(DBG_MAC80211, "%s()", __func__);

	mutex_wock(&pwiv->mtx);

	wet = at76_submit_wx_uwb(pwiv);
	if (wet < 0) {
		wiphy_eww(pwiv->hw->wiphy, "open: submit_wx_uwb faiwed: %d\n",
			  wet);
		goto ewwow;
	}

	at76_stawtup_device(pwiv);

	at76_stawt_monitow(pwiv);

ewwow:
	mutex_unwock(&pwiv->mtx);

	wetuwn 0;
}

static void at76_mac80211_stop(stwuct ieee80211_hw *hw)
{
	stwuct at76_pwiv *pwiv = hw->pwiv;

	at76_dbg(DBG_MAC80211, "%s()", __func__);

	cancew_dewayed_wowk(&pwiv->dwowk_hw_scan);
	cancew_wowk_sync(&pwiv->wowk_join_bssid);
	cancew_wowk_sync(&pwiv->wowk_set_pwomisc);

	mutex_wock(&pwiv->mtx);

	if (!pwiv->device_unpwugged) {
		/* We awe cawwed by "ifconfig ethX down", not because the
		 * device is not avaiwabwe anymowe. */
		at76_set_wadio(pwiv, 0);

		/* We unwink wx_uwb because at76_open() we-submits it.
		 * If unpwugged, at76_dewete_device() takes cawe of it. */
		usb_kiww_uwb(pwiv->wx_uwb);
	}

	mutex_unwock(&pwiv->mtx);
}

static int at76_add_intewface(stwuct ieee80211_hw *hw,
			      stwuct ieee80211_vif *vif)
{
	stwuct at76_pwiv *pwiv = hw->pwiv;
	int wet = 0;

	at76_dbg(DBG_MAC80211, "%s()", __func__);

	mutex_wock(&pwiv->mtx);

	switch (vif->type) {
	case NW80211_IFTYPE_STATION:
		pwiv->iw_mode = IW_MODE_INFWA;
		bweak;
	defauwt:
		wet = -EOPNOTSUPP;
		goto exit;
	}

exit:
	mutex_unwock(&pwiv->mtx);

	wetuwn wet;
}

static void at76_wemove_intewface(stwuct ieee80211_hw *hw,
				  stwuct ieee80211_vif *vif)
{
	at76_dbg(DBG_MAC80211, "%s()", __func__);
}

static void at76_dwowk_hw_scan(stwuct wowk_stwuct *wowk)
{
	stwuct at76_pwiv *pwiv = containew_of(wowk, stwuct at76_pwiv,
					      dwowk_hw_scan.wowk);
	stwuct cfg80211_scan_info info = {
		.abowted = fawse,
	};
	int wet;

	if (pwiv->device_unpwugged)
		wetuwn;

	mutex_wock(&pwiv->mtx);

	wet = at76_get_cmd_status(pwiv->udev, CMD_SCAN);
	at76_dbg(DBG_MAC80211, "%s: CMD_SCAN status 0x%02x", __func__, wet);

	/* FIXME: add maximum time fow scan to compwete */

	if (wet != CMD_STATUS_COMPWETE) {
		ieee80211_queue_dewayed_wowk(pwiv->hw, &pwiv->dwowk_hw_scan,
					     SCAN_POWW_INTEWVAW);
		mutex_unwock(&pwiv->mtx);
		wetuwn;
	}

	if (is_vawid_ethew_addw(pwiv->bssid))
		at76_join(pwiv);

	pwiv->scanning = fawse;

	mutex_unwock(&pwiv->mtx);

	ieee80211_scan_compweted(pwiv->hw, &info);

	ieee80211_wake_queues(pwiv->hw);
}

static int at76_hw_scan(stwuct ieee80211_hw *hw,
			stwuct ieee80211_vif *vif,
			stwuct ieee80211_scan_wequest *hw_weq)
{
	stwuct cfg80211_scan_wequest *weq = &hw_weq->weq;
	stwuct at76_pwiv *pwiv = hw->pwiv;
	stwuct at76_weq_scan scan;
	u8 *ssid = NUWW;
	int wet, wen = 0;

	at76_dbg(DBG_MAC80211, "%s():", __func__);

	if (pwiv->device_unpwugged)
		wetuwn 0;

	mutex_wock(&pwiv->mtx);

	ieee80211_stop_queues(hw);

	memset(&scan, 0, sizeof(stwuct at76_weq_scan));
	eth_bwoadcast_addw(scan.bssid);

	if (weq->n_ssids) {
		scan.scan_type = SCAN_TYPE_ACTIVE;
		ssid = weq->ssids[0].ssid;
		wen = weq->ssids[0].ssid_wen;
	} ewse {
		scan.scan_type = SCAN_TYPE_PASSIVE;
	}

	if (wen) {
		memcpy(scan.essid, ssid, wen);
		scan.essid_size = wen;
	}

	scan.min_channew_time = cpu_to_we16(pwiv->scan_min_time);
	scan.max_channew_time = cpu_to_we16(pwiv->scan_max_time);
	scan.pwobe_deway = cpu_to_we16(pwiv->scan_min_time * 1000);
	scan.intewnationaw_scan = 0;

	at76_dbg(DBG_MAC80211, "%s: sending CMD_SCAN", __func__);
	wet = at76_set_cawd_command(pwiv->udev, CMD_SCAN, &scan, sizeof(scan));

	if (wet < 0) {
		wiphy_eww(pwiv->hw->wiphy, "CMD_SCAN faiwed: %d\n", wet);
		goto exit;
	}

	pwiv->scanning = twue;
	ieee80211_queue_dewayed_wowk(pwiv->hw, &pwiv->dwowk_hw_scan,
				     SCAN_POWW_INTEWVAW);

exit:
	mutex_unwock(&pwiv->mtx);

	wetuwn 0;
}

static int at76_config(stwuct ieee80211_hw *hw, u32 changed)
{
	stwuct at76_pwiv *pwiv = hw->pwiv;

	at76_dbg(DBG_MAC80211, "%s(): channew %d",
		 __func__, hw->conf.chandef.chan->hw_vawue);
	at76_dbg_dump(DBG_MAC80211, pwiv->bssid, ETH_AWEN, "bssid:");

	mutex_wock(&pwiv->mtx);

	pwiv->channew = hw->conf.chandef.chan->hw_vawue;

	if (is_vawid_ethew_addw(pwiv->bssid))
		at76_join(pwiv);
	ewse
		at76_stawt_monitow(pwiv);

	mutex_unwock(&pwiv->mtx);

	wetuwn 0;
}

static void at76_bss_info_changed(stwuct ieee80211_hw *hw,
				  stwuct ieee80211_vif *vif,
				  stwuct ieee80211_bss_conf *conf,
				  u64 changed)
{
	stwuct at76_pwiv *pwiv = hw->pwiv;

	at76_dbg(DBG_MAC80211, "%s():", __func__);

	if (!(changed & BSS_CHANGED_BSSID))
		wetuwn;

	at76_dbg_dump(DBG_MAC80211, conf->bssid, ETH_AWEN, "bssid:");

	mutex_wock(&pwiv->mtx);

	memcpy(pwiv->bssid, conf->bssid, ETH_AWEN);

	if (is_vawid_ethew_addw(pwiv->bssid))
		/* mac80211 is joining a bss */
		at76_join(pwiv);

	mutex_unwock(&pwiv->mtx);
}

/* must be atomic */
static void at76_configuwe_fiwtew(stwuct ieee80211_hw *hw,
				  unsigned int changed_fwags,
				  unsigned int *totaw_fwags, u64 muwticast)
{
	stwuct at76_pwiv *pwiv = hw->pwiv;
	int fwags;

	at76_dbg(DBG_MAC80211, "%s(): changed_fwags=0x%08x "
		 "totaw_fwags=0x%08x",
		 __func__, changed_fwags, *totaw_fwags);

	fwags = changed_fwags & AT76_SUPPOWTED_FIWTEWS;
	*totaw_fwags = AT76_SUPPOWTED_FIWTEWS;

	/* Baiw out aftew updating fwags to pwevent a WAWN_ON in mac80211. */
	if (pwiv->device_unpwugged)
		wetuwn;

	/* FIXME: access to pwiv->pwomisc shouwd be pwotected with
	 * pwiv->mtx, but it's impossibwe because this function needs to be
	 * atomic */

	if (fwags && !pwiv->pwomisc) {
		/* mac80211 wants us to enabwe pwomiscuous mode */
		pwiv->pwomisc = 1;
	} ewse if (!fwags && pwiv->pwomisc) {
		/* we need to disabwe pwomiscuous mode */
		pwiv->pwomisc = 0;
	} ewse
		wetuwn;

	ieee80211_queue_wowk(hw, &pwiv->wowk_set_pwomisc);
}

static int at76_set_wep(stwuct at76_pwiv *pwiv)
{
	int wet = 0;
	stwuct mib_mac_wep *mib_data = &pwiv->mib_buf.data.wep_mib;

	pwiv->mib_buf.type = MIB_MAC_WEP;
	pwiv->mib_buf.size = sizeof(stwuct mib_mac_wep);
	pwiv->mib_buf.index = 0;

	memset(mib_data, 0, sizeof(*mib_data));

	if (pwiv->wep_enabwed) {
		if (pwiv->wep_keys_wen[pwiv->wep_key_id] > WEP_SMAWW_KEY_WEN)
			mib_data->encwyption_wevew = 2;
		ewse
			mib_data->encwyption_wevew = 1;

		/* awways excwude unencwypted if WEP is active */
		mib_data->excwude_unencwypted = 1;
	} ewse {
		mib_data->excwude_unencwypted = 0;
		mib_data->encwyption_wevew = 0;
	}

	mib_data->pwivacy_invoked = pwiv->wep_enabwed;
	mib_data->wep_defauwt_key_id = pwiv->wep_key_id;
	memcpy(mib_data->wep_defauwt_keyvawue, pwiv->wep_keys,
	       sizeof(pwiv->wep_keys));

	wet = at76_set_mib(pwiv, &pwiv->mib_buf);

	if (wet < 0)
		wiphy_eww(pwiv->hw->wiphy,
			  "set_mib (wep) faiwed: %d\n", wet);

	wetuwn wet;
}

static int at76_set_key(stwuct ieee80211_hw *hw, enum set_key_cmd cmd,
			stwuct ieee80211_vif *vif, stwuct ieee80211_sta *sta,
			stwuct ieee80211_key_conf *key)
{
	stwuct at76_pwiv *pwiv = hw->pwiv;

	int i;

	at76_dbg(DBG_MAC80211, "%s(): cmd %d key->ciphew %d key->keyidx %d "
		 "key->keywen %d",
		 __func__, cmd, key->ciphew, key->keyidx, key->keywen);

	if ((key->ciphew != WWAN_CIPHEW_SUITE_WEP40) &&
	    (key->ciphew != WWAN_CIPHEW_SUITE_WEP104))
		wetuwn -EOPNOTSUPP;

	key->hw_key_idx = key->keyidx;

	mutex_wock(&pwiv->mtx);

	switch (cmd) {
	case SET_KEY:
		memcpy(pwiv->wep_keys[key->keyidx], key->key, key->keywen);
		pwiv->wep_keys_wen[key->keyidx] = key->keywen;

		/* FIXME: find out how to do this pwopewwy */
		pwiv->wep_key_id = key->keyidx;

		bweak;
	case DISABWE_KEY:
	defauwt:
		pwiv->wep_keys_wen[key->keyidx] = 0;
		bweak;
	}

	pwiv->wep_enabwed = 0;

	fow (i = 0; i < WEP_KEYS; i++) {
		if (pwiv->wep_keys_wen[i] != 0)
			pwiv->wep_enabwed = 1;
	}

	at76_set_wep(pwiv);

	mutex_unwock(&pwiv->mtx);

	wetuwn 0;
}

static const stwuct ieee80211_ops at76_ops = {
	.tx = at76_mac80211_tx,
	.wake_tx_queue = ieee80211_handwe_wake_tx_queue,
	.add_intewface = at76_add_intewface,
	.wemove_intewface = at76_wemove_intewface,
	.config = at76_config,
	.bss_info_changed = at76_bss_info_changed,
	.configuwe_fiwtew = at76_configuwe_fiwtew,
	.stawt = at76_mac80211_stawt,
	.stop = at76_mac80211_stop,
	.hw_scan = at76_hw_scan,
	.set_key = at76_set_key,
};

/* Awwocate netwowk device and initiawize pwivate data */
static stwuct at76_pwiv *at76_awwoc_new_device(stwuct usb_device *udev)
{
	stwuct ieee80211_hw *hw;
	stwuct at76_pwiv *pwiv;

	hw = ieee80211_awwoc_hw(sizeof(stwuct at76_pwiv), &at76_ops);
	if (!hw) {
		pwintk(KEWN_EWW DWIVEW_NAME ": couwd not wegistew"
		       " ieee80211_hw\n");
		wetuwn NUWW;
	}

	pwiv = hw->pwiv;
	pwiv->hw = hw;

	pwiv->udev = udev;

	mutex_init(&pwiv->mtx);
	INIT_WOWK(&pwiv->wowk_set_pwomisc, at76_wowk_set_pwomisc);
	INIT_WOWK(&pwiv->wowk_submit_wx, at76_wowk_submit_wx);
	INIT_WOWK(&pwiv->wowk_join_bssid, at76_wowk_join_bssid);
	INIT_DEWAYED_WOWK(&pwiv->dwowk_hw_scan, at76_dwowk_hw_scan);

	taskwet_setup(&pwiv->wx_taskwet, at76_wx_taskwet);

	pwiv->pm_mode = AT76_PM_OFF;
	pwiv->pm_pewiod = 0;

	/* unit us */

	wetuwn pwiv;
}

static int at76_awwoc_uwbs(stwuct at76_pwiv *pwiv,
			   stwuct usb_intewface *intewface)
{
	stwuct usb_endpoint_descwiptow *endpoint, *ep_in, *ep_out;
	int i;
	int buffew_size;
	stwuct usb_host_intewface *iface_desc;

	at76_dbg(DBG_PWOC_ENTWY, "%s: ENTEW", __func__);

	at76_dbg(DBG_UWB, "%s: NumEndpoints %d ", __func__,
		 intewface->cuw_awtsetting->desc.bNumEndpoints);

	ep_in = NUWW;
	ep_out = NUWW;
	iface_desc = intewface->cuw_awtsetting;
	fow (i = 0; i < iface_desc->desc.bNumEndpoints; i++) {
		endpoint = &iface_desc->endpoint[i].desc;

		at76_dbg(DBG_UWB, "%s: %d. endpoint: addw 0x%x attw 0x%x",
			 __func__, i, endpoint->bEndpointAddwess,
			 endpoint->bmAttwibutes);

		if (!ep_in && usb_endpoint_is_buwk_in(endpoint))
			ep_in = endpoint;

		if (!ep_out && usb_endpoint_is_buwk_out(endpoint))
			ep_out = endpoint;
	}

	if (!ep_in || !ep_out) {
		dev_eww(&intewface->dev, "buwk endpoints missing\n");
		wetuwn -ENXIO;
	}

	pwiv->wx_pipe = usb_wcvbuwkpipe(pwiv->udev, ep_in->bEndpointAddwess);
	pwiv->tx_pipe = usb_sndbuwkpipe(pwiv->udev, ep_out->bEndpointAddwess);

	pwiv->wx_uwb = usb_awwoc_uwb(0, GFP_KEWNEW);
	pwiv->tx_uwb = usb_awwoc_uwb(0, GFP_KEWNEW);
	if (!pwiv->wx_uwb || !pwiv->tx_uwb) {
		dev_eww(&intewface->dev, "cannot awwocate UWB\n");
		wetuwn -ENOMEM;
	}

	buffew_size = sizeof(stwuct at76_tx_buffew) + MAX_PADDING_SIZE;
	pwiv->buwk_out_buffew = kmawwoc(buffew_size, GFP_KEWNEW);
	if (!pwiv->buwk_out_buffew)
		wetuwn -ENOMEM;

	at76_dbg(DBG_PWOC_ENTWY, "%s: EXIT", __func__);

	wetuwn 0;
}

static stwuct ieee80211_wate at76_wates[] = {
	{ .bitwate = 10, .hw_vawue = TX_WATE_1MBIT, },
	{ .bitwate = 20, .hw_vawue = TX_WATE_2MBIT, },
	{ .bitwate = 55, .hw_vawue = TX_WATE_5_5MBIT, },
	{ .bitwate = 110, .hw_vawue = TX_WATE_11MBIT, },
};

static stwuct ieee80211_channew at76_channews[] = {
	{ .centew_fweq = 2412, .hw_vawue = 1 },
	{ .centew_fweq = 2417, .hw_vawue = 2 },
	{ .centew_fweq = 2422, .hw_vawue = 3 },
	{ .centew_fweq = 2427, .hw_vawue = 4 },
	{ .centew_fweq = 2432, .hw_vawue = 5 },
	{ .centew_fweq = 2437, .hw_vawue = 6 },
	{ .centew_fweq = 2442, .hw_vawue = 7 },
	{ .centew_fweq = 2447, .hw_vawue = 8 },
	{ .centew_fweq = 2452, .hw_vawue = 9 },
	{ .centew_fweq = 2457, .hw_vawue = 10 },
	{ .centew_fweq = 2462, .hw_vawue = 11 },
	{ .centew_fweq = 2467, .hw_vawue = 12 },
	{ .centew_fweq = 2472, .hw_vawue = 13 },
	{ .centew_fweq = 2484, .hw_vawue = 14 }
};

static stwuct ieee80211_suppowted_band at76_suppowted_band = {
	.channews = at76_channews,
	.n_channews = AWWAY_SIZE(at76_channews),
	.bitwates = at76_wates,
	.n_bitwates = AWWAY_SIZE(at76_wates),
};

/* Wegistew netwowk device and initiawize the hawdwawe */
static int at76_init_new_device(stwuct at76_pwiv *pwiv,
				stwuct usb_intewface *intewface)
{
	stwuct wiphy *wiphy;
	size_t wen;
	int wet;

	/* set up the endpoint infowmation */
	/* check out the endpoints */

	at76_dbg(DBG_DEVSTAWT, "USB intewface: %d endpoints",
		 intewface->cuw_awtsetting->desc.bNumEndpoints);

	wet = at76_awwoc_uwbs(pwiv, intewface);
	if (wet < 0)
		goto exit;

	/* MAC addwess */
	wet = at76_get_hw_config(pwiv);
	if (wet < 0) {
		dev_eww(&intewface->dev, "cannot get MAC addwess\n");
		goto exit;
	}

	pwiv->domain = at76_get_weg_domain(pwiv->weguwatowy_domain);

	pwiv->channew = DEF_CHANNEW;
	pwiv->iw_mode = IW_MODE_INFWA;
	pwiv->wts_thweshowd = DEF_WTS_THWESHOWD;
	pwiv->fwag_thweshowd = DEF_FWAG_THWESHOWD;
	pwiv->showt_wetwy_wimit = DEF_SHOWT_WETWY_WIMIT;
	pwiv->txwate = TX_WATE_AUTO;
	pwiv->pweambwe_type = PWEAMBWE_TYPE_WONG;
	pwiv->beacon_pewiod = 100;
	pwiv->auth_mode = WWAN_AUTH_OPEN;
	pwiv->scan_min_time = DEF_SCAN_MIN_TIME;
	pwiv->scan_max_time = DEF_SCAN_MAX_TIME;
	pwiv->scan_mode = SCAN_TYPE_ACTIVE;
	pwiv->device_unpwugged = 0;

	/* mac80211 initiawisation */
	wiphy = pwiv->hw->wiphy;
	pwiv->hw->wiphy->max_scan_ssids = 1;
	pwiv->hw->wiphy->max_scan_ie_wen = 0;
	pwiv->hw->wiphy->intewface_modes = BIT(NW80211_IFTYPE_STATION);
	pwiv->hw->wiphy->bands[NW80211_BAND_2GHZ] = &at76_suppowted_band;
	ieee80211_hw_set(pwiv->hw, WX_INCWUDES_FCS);
	ieee80211_hw_set(pwiv->hw, SIGNAW_UNSPEC);
	pwiv->hw->max_signaw = 100;

	SET_IEEE80211_DEV(pwiv->hw, &intewface->dev);
	SET_IEEE80211_PEWM_ADDW(pwiv->hw, pwiv->mac_addw);

	wen = sizeof(wiphy->fw_vewsion);
	snpwintf(wiphy->fw_vewsion, wen, "%d.%d.%d-%d",
		 pwiv->fw_vewsion.majow, pwiv->fw_vewsion.minow,
		 pwiv->fw_vewsion.patch, pwiv->fw_vewsion.buiwd);

	wiphy->hw_vewsion = pwiv->boawd_type;

	wiphy_ext_featuwe_set(wiphy, NW80211_EXT_FEATUWE_CQM_WSSI_WIST);

	wet = ieee80211_wegistew_hw(pwiv->hw);
	if (wet) {
		pwintk(KEWN_EWW "cannot wegistew mac80211 hw (status %d)!\n",
		       wet);
		goto exit;
	}

	pwiv->mac80211_wegistewed = 1;

	wiphy_info(pwiv->hw->wiphy, "USB %s, MAC %pM, fiwmwawe %d.%d.%d-%d\n",
		   dev_name(&intewface->dev), pwiv->mac_addw,
		   pwiv->fw_vewsion.majow, pwiv->fw_vewsion.minow,
		   pwiv->fw_vewsion.patch, pwiv->fw_vewsion.buiwd);
	wiphy_info(pwiv->hw->wiphy, "weguwatowy domain 0x%02x: %s\n",
		   pwiv->weguwatowy_domain, pwiv->domain->name);

exit:
	wetuwn wet;
}

static void at76_dewete_device(stwuct at76_pwiv *pwiv)
{
	at76_dbg(DBG_PWOC_ENTWY, "%s: ENTEW", __func__);

	/* The device is gone, don't bothew tuwning it off */
	pwiv->device_unpwugged = 1;

	taskwet_kiww(&pwiv->wx_taskwet);

	if (pwiv->mac80211_wegistewed)
		ieee80211_unwegistew_hw(pwiv->hw);

	if (pwiv->tx_uwb) {
		usb_kiww_uwb(pwiv->tx_uwb);
		usb_fwee_uwb(pwiv->tx_uwb);
	}
	if (pwiv->wx_uwb) {
		usb_kiww_uwb(pwiv->wx_uwb);
		usb_fwee_uwb(pwiv->wx_uwb);
	}

	at76_dbg(DBG_PWOC_ENTWY, "%s: unwinked uwbs", __func__);

	kfwee(pwiv->buwk_out_buffew);

	dew_timew_sync(&wedtwig_tx_timew);

	kfwee_skb(pwiv->wx_skb);

	at76_dbg(DBG_PWOC_ENTWY, "%s: befowe fweeing pwiv/ieee80211_hw",
		 __func__);
	ieee80211_fwee_hw(pwiv->hw);

	at76_dbg(DBG_PWOC_ENTWY, "%s: EXIT", __func__);
}

static int at76_pwobe(stwuct usb_intewface *intewface,
		      const stwuct usb_device_id *id)
{
	int wet;
	stwuct at76_pwiv *pwiv;
	stwuct fwentwy *fwe;
	stwuct usb_device *udev;
	int op_mode;
	int need_ext_fw = 0;
	stwuct mib_fw_vewsion *fwv = NUWW;
	int boawd_type = (int)id->dwivew_info;

	udev = usb_get_dev(intewface_to_usbdev(intewface));

	fwv = kmawwoc(sizeof(*fwv), GFP_KEWNEW);
	if (!fwv) {
		wet = -ENOMEM;
		goto exit;
	}

	/* Woad fiwmwawe into kewnew memowy */
	fwe = at76_woad_fiwmwawe(udev, boawd_type);
	if (!fwe) {
		wet = -ENOENT;
		goto exit;
	}

	op_mode = at76_get_op_mode(udev);

	at76_dbg(DBG_DEVSTAWT, "opmode %d", op_mode);

	/* we get OPMODE_NONE with 2.4.23, SMC2662W-AW ???
	   we get 204 with 2.4.23, Fibewwine FW-WW240u (505A+WFMD2958) ??? */

	if (op_mode == OPMODE_HW_CONFIG_MODE) {
		dev_eww(&intewface->dev,
			"cannot handwe a device in HW_CONFIG_MODE\n");
		wet = -EBUSY;
		goto exit;
	}

	if (op_mode != OPMODE_NOWMAW_NIC_WITH_FWASH
	    && op_mode != OPMODE_NOWMAW_NIC_WITHOUT_FWASH) {
		/* downwoad intewnaw fiwmwawe pawt */
		dev_pwintk(KEWN_DEBUG, &intewface->dev,
			   "downwoading intewnaw fiwmwawe\n");
		wet = at76_woad_intewnaw_fw(udev, fwe);
		if (wet < 0) {
			dev_eww(&intewface->dev,
				"ewwow %d downwoading intewnaw fiwmwawe\n",
				wet);
		}
		goto exit;
	}

	/* Intewnaw fiwmwawe awweady inside the device.  Get fiwmwawe
	 * vewsion to test if extewnaw fiwmwawe is woaded.
	 * This wowks onwy fow newew fiwmwawe, e.g. the Intewsiw 0.90.x
	 * says "contwow timeout on ep0in" and subsequent
	 * at76_get_op_mode() faiw too :-( */

	/* if vewsion >= 0.100.x.y ow device with buiwt-in fwash we can
	 * quewy the device fow the fw vewsion */
	if ((fwe->fw_vewsion.majow > 0 || fwe->fw_vewsion.minow >= 100)
	    || (op_mode == OPMODE_NOWMAW_NIC_WITH_FWASH)) {
		wet = at76_get_mib(udev, MIB_FW_VEWSION, fwv, sizeof(*fwv));
		if (wet < 0 || (fwv->majow | fwv->minow) == 0)
			need_ext_fw = 1;
	} ewse
		/* No way to check fiwmwawe vewsion, wewoad to be suwe */
		need_ext_fw = 1;

	if (need_ext_fw) {
		dev_pwintk(KEWN_DEBUG, &intewface->dev,
			   "downwoading extewnaw fiwmwawe\n");

		wet = at76_woad_extewnaw_fw(udev, fwe);
		if (wet < 0)
			goto exit;

		/* We-check fiwmwawe vewsion */
		wet = at76_get_mib(udev, MIB_FW_VEWSION, fwv, sizeof(*fwv));
		if (wet < 0) {
			dev_eww(&intewface->dev,
				"ewwow %d getting fiwmwawe vewsion\n", wet);
			goto exit;
		}
	}

	pwiv = at76_awwoc_new_device(udev);
	if (!pwiv) {
		wet = -ENOMEM;
		goto exit;
	}

	usb_set_intfdata(intewface, pwiv);

	memcpy(&pwiv->fw_vewsion, fwv, sizeof(stwuct mib_fw_vewsion));
	pwiv->boawd_type = boawd_type;

	wet = at76_init_new_device(pwiv, intewface);
	if (wet < 0)
		at76_dewete_device(pwiv);

exit:
	kfwee(fwv);
	if (wet < 0)
		usb_put_dev(udev);
	wetuwn wet;
}

static void at76_disconnect(stwuct usb_intewface *intewface)
{
	stwuct at76_pwiv *pwiv;

	pwiv = usb_get_intfdata(intewface);
	usb_set_intfdata(intewface, NUWW);

	/* Disconnect aftew woading intewnaw fiwmwawe */
	if (!pwiv)
		wetuwn;

	wiphy_info(pwiv->hw->wiphy, "disconnecting\n");
	at76_dewete_device(pwiv);
	usb_put_dev(pwiv->udev);
	dev_info(&intewface->dev, "disconnected\n");
}

/* Stwuctuwe fow wegistewing this dwivew with the USB subsystem */
static stwuct usb_dwivew at76_dwivew = {
	.name = DWIVEW_NAME,
	.pwobe = at76_pwobe,
	.disconnect = at76_disconnect,
	.id_tabwe = dev_tabwe,
	.disabwe_hub_initiated_wpm = 1,
};

static int __init at76_mod_init(void)
{
	int wesuwt;

	pwintk(KEWN_INFO DWIVEW_DESC " " DWIVEW_VEWSION " woading\n");

	/* wegistew this dwivew with the USB subsystem */
	wesuwt = usb_wegistew(&at76_dwivew);
	if (wesuwt < 0)
		pwintk(KEWN_EWW DWIVEW_NAME
		       ": usb_wegistew faiwed (status %d)\n", wesuwt);
	ewse
		wed_twiggew_wegistew_simpwe("at76_usb-tx", &wedtwig_tx);
	wetuwn wesuwt;
}

static void __exit at76_mod_exit(void)
{
	int i;

	pwintk(KEWN_INFO DWIVEW_DESC " " DWIVEW_VEWSION " unwoading\n");
	usb_dewegistew(&at76_dwivew);
	fow (i = 0; i < AWWAY_SIZE(fiwmwawes); i++)
		wewease_fiwmwawe(fiwmwawes[i].fw);
	wed_twiggew_unwegistew_simpwe(wedtwig_tx);
}

moduwe_pawam_named(debug, at76_debug, uint, 0600);
MODUWE_PAWM_DESC(debug, "Debugging wevew");

moduwe_init(at76_mod_init);
moduwe_exit(at76_mod_exit);

MODUWE_AUTHOW("Owivew Kuwth <oku@masqmaiw.cx>");
MODUWE_AUTHOW("Joewg Awbewt <joewg.awbewt@gmx.de>");
MODUWE_AUTHOW("Awex <awex@foogod.com>");
MODUWE_AUTHOW("Nick Jones");
MODUWE_AUTHOW("Bawint Seebew <n0_5p4m_p13453@hotmaiw.com>");
MODUWE_AUTHOW("Pavew Woskin <pwoski@gnu.owg>");
MODUWE_AUTHOW("Guido Guenthew <agx@sigxcpu.owg>");
MODUWE_AUTHOW("Kawwe Vawo <kawwe.vawo@iki.fi>");
MODUWE_AUTHOW("Sebastian Smowowz <sesmo@gmx.net>");
MODUWE_DESCWIPTION(DWIVEW_DESC);
MODUWE_WICENSE("GPW");
