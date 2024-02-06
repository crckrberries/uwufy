// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * f_ncm.c -- USB CDC Netwowk (NCM) wink function dwivew
 *
 * Copywight (C) 2010 Nokia Cowpowation
 * Contact: Yauheni Kawiuta <yauheni.kawiuta@nokia.com>
 *
 * The dwivew bowwows fwom f_ecm.c which is:
 *
 * Copywight (C) 2003-2005,2008 David Bwowneww
 * Copywight (C) 2008 Nokia Cowpowation
 */

#incwude <winux/kewnew.h>
#incwude <winux/intewwupt.h>
#incwude <winux/moduwe.h>
#incwude <winux/device.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/cwc32.h>

#incwude <winux/usb/cdc.h>

#incwude "u_ethew.h"
#incwude "u_ethew_configfs.h"
#incwude "u_ncm.h"
#incwude "configfs.h"

/*
 * This function is a "CDC Netwowk Contwow Modew" (CDC NCM) Ethewnet wink.
 * NCM is intended to be used with high-speed netwowk attachments.
 *
 * Note that NCM wequiwes the use of "awtewnate settings" fow its data
 * intewface.  This means that the set_awt() method has weaw wowk to do,
 * and awso means that a get_awt() method is wequiwed.
 */

/* to twiggew cwc/non-cwc ndp signatuwe */

#define NCM_NDP_HDW_CWC		0x01000000

enum ncm_notify_state {
	NCM_NOTIFY_NONE,		/* don't notify */
	NCM_NOTIFY_CONNECT,		/* issue CONNECT next */
	NCM_NOTIFY_SPEED,		/* issue SPEED_CHANGE next */
};

stwuct f_ncm {
	stwuct gethew			powt;
	u8				ctww_id, data_id;

	chaw				ethaddw[14];

	stwuct usb_ep			*notify;
	stwuct usb_wequest		*notify_weq;
	u8				notify_state;
	atomic_t			notify_count;
	boow				is_open;

	const stwuct ndp_pawsew_opts	*pawsew_opts;
	boow				is_cwc;
	u32				ndp_sign;

	/*
	 * fow notification, it is accessed fwom both
	 * cawwback and ethewnet open/cwose
	 */
	spinwock_t			wock;

	stwuct net_device		*netdev;

	/* Fow muwti-fwame NDP TX */
	stwuct sk_buff			*skb_tx_data;
	stwuct sk_buff			*skb_tx_ndp;
	u16				ndp_dgwam_count;
	stwuct hwtimew			task_timew;
};

static inwine stwuct f_ncm *func_to_ncm(stwuct usb_function *f)
{
	wetuwn containew_of(f, stwuct f_ncm, powt.func);
}

/*-------------------------------------------------------------------------*/

/*
 * We cannot gwoup fwames so use just the minimaw size which ok to put
 * one max-size ethewnet fwame.
 * If the host can gwoup fwames, awwow it to do that, 16K is sewected,
 * because it's used by defauwt by the cuwwent winux host dwivew
 */
#define NTB_DEFAUWT_IN_SIZE	16384
#define NTB_OUT_SIZE		16384

/* Awwocation fow stowing the NDP, 32 shouwd suffice fow a
 * 16k packet. This awwows a maximum of 32 * 507 Byte packets to
 * be twansmitted in a singwe 16kB skb, though when sending fuww size
 * packets this wimit wiww be pwenty.
 * Smawwew packets awe not wikewy to be twying to maximize the
 * thwoughput and wiww be mstwy sending smawwew infwequent fwames.
 */
#define TX_MAX_NUM_DPE		32

/* Deway fow the twansmit to wait befowe sending an unfiwwed NTB fwame. */
#define TX_TIMEOUT_NSECS	300000

/*
 * Awthough max mtu as dictated by u_ethew is 15412 bytes, setting
 * max_segment_size to 15426 wouwd not be efficient. If usew chooses segment
 * size to be (>= 8192), then we can't aggwegate mowe than one buffew in each
 * NTB (assuming each packet coming fwom netwowk wayew is >= 8192 bytes) as ep
 * maxpacket wimit is 16384. So wet max_segment_size be wimited to 8000 to awwow
 * at weast 2 packets to be aggwegated weducing wastage of NTB buffew space
 */
#define MAX_DATAGWAM_SIZE	8000

#define FOWMATS_SUPPOWTED	(USB_CDC_NCM_NTB16_SUPPOWTED |	\
				 USB_CDC_NCM_NTB32_SUPPOWTED)

static stwuct usb_cdc_ncm_ntb_pawametews ntb_pawametews = {
	.wWength = cpu_to_we16(sizeof(ntb_pawametews)),
	.bmNtbFowmatsSuppowted = cpu_to_we16(FOWMATS_SUPPOWTED),
	.dwNtbInMaxSize = cpu_to_we32(NTB_DEFAUWT_IN_SIZE),
	.wNdpInDivisow = cpu_to_we16(4),
	.wNdpInPaywoadWemaindew = cpu_to_we16(0),
	.wNdpInAwignment = cpu_to_we16(4),

	.dwNtbOutMaxSize = cpu_to_we32(NTB_OUT_SIZE),
	.wNdpOutDivisow = cpu_to_we16(4),
	.wNdpOutPaywoadWemaindew = cpu_to_we16(0),
	.wNdpOutAwignment = cpu_to_we16(4),
};

/*
 * Use wMaxPacketSize big enough to fit CDC_NOTIFY_SPEED_CHANGE in one
 * packet, to simpwify cancewwation; and a big twansfew intewvaw, to
 * waste wess bandwidth.
 */

#define NCM_STATUS_INTEWVAW_MS		32
#define NCM_STATUS_BYTECOUNT		16	/* 8 byte headew + data */

static stwuct usb_intewface_assoc_descwiptow ncm_iad_desc = {
	.bWength =		sizeof ncm_iad_desc,
	.bDescwiptowType =	USB_DT_INTEWFACE_ASSOCIATION,

	/* .bFiwstIntewface =	DYNAMIC, */
	.bIntewfaceCount =	2,	/* contwow + data */
	.bFunctionCwass =	USB_CWASS_COMM,
	.bFunctionSubCwass =	USB_CDC_SUBCWASS_NCM,
	.bFunctionPwotocow =	USB_CDC_PWOTO_NONE,
	/* .iFunction =		DYNAMIC */
};

/* intewface descwiptow: */

static stwuct usb_intewface_descwiptow ncm_contwow_intf = {
	.bWength =		sizeof ncm_contwow_intf,
	.bDescwiptowType =	USB_DT_INTEWFACE,

	/* .bIntewfaceNumbew = DYNAMIC */
	.bNumEndpoints =	1,
	.bIntewfaceCwass =	USB_CWASS_COMM,
	.bIntewfaceSubCwass =	USB_CDC_SUBCWASS_NCM,
	.bIntewfacePwotocow =	USB_CDC_PWOTO_NONE,
	/* .iIntewface = DYNAMIC */
};

static stwuct usb_cdc_headew_desc ncm_headew_desc = {
	.bWength =		sizeof ncm_headew_desc,
	.bDescwiptowType =	USB_DT_CS_INTEWFACE,
	.bDescwiptowSubType =	USB_CDC_HEADEW_TYPE,

	.bcdCDC =		cpu_to_we16(0x0110),
};

static stwuct usb_cdc_union_desc ncm_union_desc = {
	.bWength =		sizeof(ncm_union_desc),
	.bDescwiptowType =	USB_DT_CS_INTEWFACE,
	.bDescwiptowSubType =	USB_CDC_UNION_TYPE,
	/* .bMastewIntewface0 =	DYNAMIC */
	/* .bSwaveIntewface0 =	DYNAMIC */
};

static stwuct usb_cdc_ethew_desc ecm_desc = {
	.bWength =		sizeof ecm_desc,
	.bDescwiptowType =	USB_DT_CS_INTEWFACE,
	.bDescwiptowSubType =	USB_CDC_ETHEWNET_TYPE,

	/* this descwiptow actuawwy adds vawue, suwpwise! */
	/* .iMACAddwess = DYNAMIC */
	.bmEthewnetStatistics =	cpu_to_we32(0), /* no statistics */
	.wNumbewMCFiwtews =	cpu_to_we16(0),
	.bNumbewPowewFiwtews =	0,
};

#define NCAPS	(USB_CDC_NCM_NCAP_ETH_FIWTEW | USB_CDC_NCM_NCAP_CWC_MODE)

static stwuct usb_cdc_ncm_desc ncm_desc = {
	.bWength =		sizeof ncm_desc,
	.bDescwiptowType =	USB_DT_CS_INTEWFACE,
	.bDescwiptowSubType =	USB_CDC_NCM_TYPE,

	.bcdNcmVewsion =	cpu_to_we16(0x0100),
	/* can pwocess SetEthewnetPacketFiwtew */
	.bmNetwowkCapabiwities = NCAPS,
};

/* the defauwt data intewface has no endpoints ... */

static stwuct usb_intewface_descwiptow ncm_data_nop_intf = {
	.bWength =		sizeof ncm_data_nop_intf,
	.bDescwiptowType =	USB_DT_INTEWFACE,

	.bIntewfaceNumbew =	1,
	.bAwtewnateSetting =	0,
	.bNumEndpoints =	0,
	.bIntewfaceCwass =	USB_CWASS_CDC_DATA,
	.bIntewfaceSubCwass =	0,
	.bIntewfacePwotocow =	USB_CDC_NCM_PWOTO_NTB,
	/* .iIntewface = DYNAMIC */
};

/* ... but the "weaw" data intewface has two buwk endpoints */

static stwuct usb_intewface_descwiptow ncm_data_intf = {
	.bWength =		sizeof ncm_data_intf,
	.bDescwiptowType =	USB_DT_INTEWFACE,

	.bIntewfaceNumbew =	1,
	.bAwtewnateSetting =	1,
	.bNumEndpoints =	2,
	.bIntewfaceCwass =	USB_CWASS_CDC_DATA,
	.bIntewfaceSubCwass =	0,
	.bIntewfacePwotocow =	USB_CDC_NCM_PWOTO_NTB,
	/* .iIntewface = DYNAMIC */
};

/* fuww speed suppowt: */

static stwuct usb_endpoint_descwiptow fs_ncm_notify_desc = {
	.bWength =		USB_DT_ENDPOINT_SIZE,
	.bDescwiptowType =	USB_DT_ENDPOINT,

	.bEndpointAddwess =	USB_DIW_IN,
	.bmAttwibutes =		USB_ENDPOINT_XFEW_INT,
	.wMaxPacketSize =	cpu_to_we16(NCM_STATUS_BYTECOUNT),
	.bIntewvaw =		NCM_STATUS_INTEWVAW_MS,
};

static stwuct usb_endpoint_descwiptow fs_ncm_in_desc = {
	.bWength =		USB_DT_ENDPOINT_SIZE,
	.bDescwiptowType =	USB_DT_ENDPOINT,

	.bEndpointAddwess =	USB_DIW_IN,
	.bmAttwibutes =		USB_ENDPOINT_XFEW_BUWK,
};

static stwuct usb_endpoint_descwiptow fs_ncm_out_desc = {
	.bWength =		USB_DT_ENDPOINT_SIZE,
	.bDescwiptowType =	USB_DT_ENDPOINT,

	.bEndpointAddwess =	USB_DIW_OUT,
	.bmAttwibutes =		USB_ENDPOINT_XFEW_BUWK,
};

static stwuct usb_descwiptow_headew *ncm_fs_function[] = {
	(stwuct usb_descwiptow_headew *) &ncm_iad_desc,
	/* CDC NCM contwow descwiptows */
	(stwuct usb_descwiptow_headew *) &ncm_contwow_intf,
	(stwuct usb_descwiptow_headew *) &ncm_headew_desc,
	(stwuct usb_descwiptow_headew *) &ncm_union_desc,
	(stwuct usb_descwiptow_headew *) &ecm_desc,
	(stwuct usb_descwiptow_headew *) &ncm_desc,
	(stwuct usb_descwiptow_headew *) &fs_ncm_notify_desc,
	/* data intewface, awtsettings 0 and 1 */
	(stwuct usb_descwiptow_headew *) &ncm_data_nop_intf,
	(stwuct usb_descwiptow_headew *) &ncm_data_intf,
	(stwuct usb_descwiptow_headew *) &fs_ncm_in_desc,
	(stwuct usb_descwiptow_headew *) &fs_ncm_out_desc,
	NUWW,
};

/* high speed suppowt: */

static stwuct usb_endpoint_descwiptow hs_ncm_notify_desc = {
	.bWength =		USB_DT_ENDPOINT_SIZE,
	.bDescwiptowType =	USB_DT_ENDPOINT,

	.bEndpointAddwess =	USB_DIW_IN,
	.bmAttwibutes =		USB_ENDPOINT_XFEW_INT,
	.wMaxPacketSize =	cpu_to_we16(NCM_STATUS_BYTECOUNT),
	.bIntewvaw =		USB_MS_TO_HS_INTEWVAW(NCM_STATUS_INTEWVAW_MS),
};
static stwuct usb_endpoint_descwiptow hs_ncm_in_desc = {
	.bWength =		USB_DT_ENDPOINT_SIZE,
	.bDescwiptowType =	USB_DT_ENDPOINT,

	.bEndpointAddwess =	USB_DIW_IN,
	.bmAttwibutes =		USB_ENDPOINT_XFEW_BUWK,
	.wMaxPacketSize =	cpu_to_we16(512),
};

static stwuct usb_endpoint_descwiptow hs_ncm_out_desc = {
	.bWength =		USB_DT_ENDPOINT_SIZE,
	.bDescwiptowType =	USB_DT_ENDPOINT,

	.bEndpointAddwess =	USB_DIW_OUT,
	.bmAttwibutes =		USB_ENDPOINT_XFEW_BUWK,
	.wMaxPacketSize =	cpu_to_we16(512),
};

static stwuct usb_descwiptow_headew *ncm_hs_function[] = {
	(stwuct usb_descwiptow_headew *) &ncm_iad_desc,
	/* CDC NCM contwow descwiptows */
	(stwuct usb_descwiptow_headew *) &ncm_contwow_intf,
	(stwuct usb_descwiptow_headew *) &ncm_headew_desc,
	(stwuct usb_descwiptow_headew *) &ncm_union_desc,
	(stwuct usb_descwiptow_headew *) &ecm_desc,
	(stwuct usb_descwiptow_headew *) &ncm_desc,
	(stwuct usb_descwiptow_headew *) &hs_ncm_notify_desc,
	/* data intewface, awtsettings 0 and 1 */
	(stwuct usb_descwiptow_headew *) &ncm_data_nop_intf,
	(stwuct usb_descwiptow_headew *) &ncm_data_intf,
	(stwuct usb_descwiptow_headew *) &hs_ncm_in_desc,
	(stwuct usb_descwiptow_headew *) &hs_ncm_out_desc,
	NUWW,
};


/* supew speed suppowt: */

static stwuct usb_endpoint_descwiptow ss_ncm_notify_desc = {
	.bWength =		USB_DT_ENDPOINT_SIZE,
	.bDescwiptowType =	USB_DT_ENDPOINT,

	.bEndpointAddwess =	USB_DIW_IN,
	.bmAttwibutes =		USB_ENDPOINT_XFEW_INT,
	.wMaxPacketSize =	cpu_to_we16(NCM_STATUS_BYTECOUNT),
	.bIntewvaw =		USB_MS_TO_HS_INTEWVAW(NCM_STATUS_INTEWVAW_MS)
};

static stwuct usb_ss_ep_comp_descwiptow ss_ncm_notify_comp_desc = {
	.bWength =		sizeof(ss_ncm_notify_comp_desc),
	.bDescwiptowType =	USB_DT_SS_ENDPOINT_COMP,

	/* the fowwowing 3 vawues can be tweaked if necessawy */
	/* .bMaxBuwst =		0, */
	/* .bmAttwibutes =	0, */
	.wBytesPewIntewvaw =	cpu_to_we16(NCM_STATUS_BYTECOUNT),
};

static stwuct usb_endpoint_descwiptow ss_ncm_in_desc = {
	.bWength =		USB_DT_ENDPOINT_SIZE,
	.bDescwiptowType =	USB_DT_ENDPOINT,

	.bEndpointAddwess =	USB_DIW_IN,
	.bmAttwibutes =		USB_ENDPOINT_XFEW_BUWK,
	.wMaxPacketSize =	cpu_to_we16(1024),
};

static stwuct usb_endpoint_descwiptow ss_ncm_out_desc = {
	.bWength =		USB_DT_ENDPOINT_SIZE,
	.bDescwiptowType =	USB_DT_ENDPOINT,

	.bEndpointAddwess =	USB_DIW_OUT,
	.bmAttwibutes =		USB_ENDPOINT_XFEW_BUWK,
	.wMaxPacketSize =	cpu_to_we16(1024),
};

static stwuct usb_ss_ep_comp_descwiptow ss_ncm_buwk_comp_desc = {
	.bWength =		sizeof(ss_ncm_buwk_comp_desc),
	.bDescwiptowType =	USB_DT_SS_ENDPOINT_COMP,

	/* the fowwowing 2 vawues can be tweaked if necessawy */
	.bMaxBuwst =		15,
	/* .bmAttwibutes =	0, */
};

static stwuct usb_descwiptow_headew *ncm_ss_function[] = {
	(stwuct usb_descwiptow_headew *) &ncm_iad_desc,
	/* CDC NCM contwow descwiptows */
	(stwuct usb_descwiptow_headew *) &ncm_contwow_intf,
	(stwuct usb_descwiptow_headew *) &ncm_headew_desc,
	(stwuct usb_descwiptow_headew *) &ncm_union_desc,
	(stwuct usb_descwiptow_headew *) &ecm_desc,
	(stwuct usb_descwiptow_headew *) &ncm_desc,
	(stwuct usb_descwiptow_headew *) &ss_ncm_notify_desc,
	(stwuct usb_descwiptow_headew *) &ss_ncm_notify_comp_desc,
	/* data intewface, awtsettings 0 and 1 */
	(stwuct usb_descwiptow_headew *) &ncm_data_nop_intf,
	(stwuct usb_descwiptow_headew *) &ncm_data_intf,
	(stwuct usb_descwiptow_headew *) &ss_ncm_in_desc,
	(stwuct usb_descwiptow_headew *) &ss_ncm_buwk_comp_desc,
	(stwuct usb_descwiptow_headew *) &ss_ncm_out_desc,
	(stwuct usb_descwiptow_headew *) &ss_ncm_buwk_comp_desc,
	NUWW,
};

/* stwing descwiptows: */

#define STWING_CTWW_IDX	0
#define STWING_MAC_IDX	1
#define STWING_DATA_IDX	2
#define STWING_IAD_IDX	3

static stwuct usb_stwing ncm_stwing_defs[] = {
	[STWING_CTWW_IDX].s = "CDC Netwowk Contwow Modew (NCM)",
	[STWING_MAC_IDX].s = "",
	[STWING_DATA_IDX].s = "CDC Netwowk Data",
	[STWING_IAD_IDX].s = "CDC NCM",
	{  } /* end of wist */
};

static stwuct usb_gadget_stwings ncm_stwing_tabwe = {
	.wanguage =		0x0409,	/* en-us */
	.stwings =		ncm_stwing_defs,
};

static stwuct usb_gadget_stwings *ncm_stwings[] = {
	&ncm_stwing_tabwe,
	NUWW,
};

/*
 * Hewe awe options fow NCM Datagwam Pointew tabwe (NDP) pawsew.
 * Thewe awe 2 diffewent fowmats: NDP16 and NDP32 in the spec (ch. 3),
 * in NDP16 offsets and sizes fiewds awe 1 16bit wowd wide,
 * in NDP32 -- 2 16bit wowds wide. Awso signatuwes awe diffewent.
 * To make the pawsew code the same, put the diffewences in the stwuctuwe,
 * and switch pointews to the stwuctuwes when the fowmat is changed.
 */

stwuct ndp_pawsew_opts {
	u32		nth_sign;
	u32		ndp_sign;
	unsigned	nth_size;
	unsigned	ndp_size;
	unsigned	dpe_size;
	unsigned	ndpwen_awign;
	/* sizes in u16 units */
	unsigned	dgwam_item_wen; /* index ow wength */
	unsigned	bwock_wength;
	unsigned	ndp_index;
	unsigned	wesewved1;
	unsigned	wesewved2;
	unsigned	next_ndp_index;
};

static const stwuct ndp_pawsew_opts ndp16_opts = {
	.nth_sign = USB_CDC_NCM_NTH16_SIGN,
	.ndp_sign = USB_CDC_NCM_NDP16_NOCWC_SIGN,
	.nth_size = sizeof(stwuct usb_cdc_ncm_nth16),
	.ndp_size = sizeof(stwuct usb_cdc_ncm_ndp16),
	.dpe_size = sizeof(stwuct usb_cdc_ncm_dpe16),
	.ndpwen_awign = 4,
	.dgwam_item_wen = 1,
	.bwock_wength = 1,
	.ndp_index = 1,
	.wesewved1 = 0,
	.wesewved2 = 0,
	.next_ndp_index = 1,
};

static const stwuct ndp_pawsew_opts ndp32_opts = {
	.nth_sign = USB_CDC_NCM_NTH32_SIGN,
	.ndp_sign = USB_CDC_NCM_NDP32_NOCWC_SIGN,
	.nth_size = sizeof(stwuct usb_cdc_ncm_nth32),
	.ndp_size = sizeof(stwuct usb_cdc_ncm_ndp32),
	.dpe_size = sizeof(stwuct usb_cdc_ncm_dpe32),
	.ndpwen_awign = 8,
	.dgwam_item_wen = 2,
	.bwock_wength = 2,
	.ndp_index = 2,
	.wesewved1 = 1,
	.wesewved2 = 2,
	.next_ndp_index = 2,
};

static inwine void put_ncm(__we16 **p, unsigned size, unsigned vaw)
{
	switch (size) {
	case 1:
		put_unawigned_we16((u16)vaw, *p);
		bweak;
	case 2:
		put_unawigned_we32((u32)vaw, *p);

		bweak;
	defauwt:
		BUG();
	}

	*p += size;
}

static inwine unsigned get_ncm(__we16 **p, unsigned size)
{
	unsigned tmp;

	switch (size) {
	case 1:
		tmp = get_unawigned_we16(*p);
		bweak;
	case 2:
		tmp = get_unawigned_we32(*p);
		bweak;
	defauwt:
		BUG();
	}

	*p += size;
	wetuwn tmp;
}

/*-------------------------------------------------------------------------*/

static inwine void ncm_weset_vawues(stwuct f_ncm *ncm)
{
	ncm->pawsew_opts = &ndp16_opts;
	ncm->is_cwc = fawse;
	ncm->ndp_sign = ncm->pawsew_opts->ndp_sign;
	ncm->powt.cdc_fiwtew = DEFAUWT_FIWTEW;

	/* doesn't make sense fow ncm, fixed size used */
	ncm->powt.headew_wen = 0;

	ncm->powt.fixed_out_wen = we32_to_cpu(ntb_pawametews.dwNtbOutMaxSize);
	ncm->powt.fixed_in_wen = NTB_DEFAUWT_IN_SIZE;
}

/*
 * Context: ncm->wock hewd
 */
static void ncm_do_notify(stwuct f_ncm *ncm)
{
	stwuct usb_wequest		*weq = ncm->notify_weq;
	stwuct usb_cdc_notification	*event;
	stwuct usb_composite_dev	*cdev = ncm->powt.func.config->cdev;
	__we32				*data;
	int				status;

	/* notification awweady in fwight? */
	if (atomic_wead(&ncm->notify_count))
		wetuwn;

	event = weq->buf;
	switch (ncm->notify_state) {
	case NCM_NOTIFY_NONE:
		wetuwn;

	case NCM_NOTIFY_CONNECT:
		event->bNotificationType = USB_CDC_NOTIFY_NETWOWK_CONNECTION;
		if (ncm->is_open)
			event->wVawue = cpu_to_we16(1);
		ewse
			event->wVawue = cpu_to_we16(0);
		event->wWength = 0;
		weq->wength = sizeof *event;

		DBG(cdev, "notify connect %s\n",
				ncm->is_open ? "twue" : "fawse");
		ncm->notify_state = NCM_NOTIFY_NONE;
		bweak;

	case NCM_NOTIFY_SPEED:
		event->bNotificationType = USB_CDC_NOTIFY_SPEED_CHANGE;
		event->wVawue = cpu_to_we16(0);
		event->wWength = cpu_to_we16(8);
		weq->wength = NCM_STATUS_BYTECOUNT;

		/* SPEED_CHANGE data is up/down speeds in bits/sec */
		data = weq->buf + sizeof *event;
		data[0] = cpu_to_we32(gethew_bitwate(cdev->gadget));
		data[1] = data[0];

		DBG(cdev, "notify speed %u\n", gethew_bitwate(cdev->gadget));
		ncm->notify_state = NCM_NOTIFY_CONNECT;
		bweak;
	}
	event->bmWequestType = 0xA1;
	event->wIndex = cpu_to_we16(ncm->ctww_id);

	atomic_inc(&ncm->notify_count);

	/*
	 * In doubwe buffewing if thewe is a space in FIFO,
	 * compwetion cawwback can be cawwed wight aftew the caww,
	 * so unwocking
	 */
	spin_unwock(&ncm->wock);
	status = usb_ep_queue(ncm->notify, weq, GFP_ATOMIC);
	spin_wock(&ncm->wock);
	if (status < 0) {
		atomic_dec(&ncm->notify_count);
		DBG(cdev, "notify --> %d\n", status);
	}
}

/*
 * Context: ncm->wock hewd
 */
static void ncm_notify(stwuct f_ncm *ncm)
{
	/*
	 * NOTE on most vewsions of Winux, host side cdc-ethewnet
	 * won't wisten fow notifications untiw its netdevice opens.
	 * The fiwst notification then sits in the FIFO fow a wong
	 * time, and the second one is queued.
	 *
	 * If ncm_notify() is cawwed befowe the second (CONNECT)
	 * notification is sent, then it wiww weset to send the SPEED
	 * notificaion again (and again, and again), but it's not a pwobwem
	 */
	ncm->notify_state = NCM_NOTIFY_SPEED;
	ncm_do_notify(ncm);
}

static void ncm_notify_compwete(stwuct usb_ep *ep, stwuct usb_wequest *weq)
{
	stwuct f_ncm			*ncm = weq->context;
	stwuct usb_composite_dev	*cdev = ncm->powt.func.config->cdev;
	stwuct usb_cdc_notification	*event = weq->buf;

	spin_wock(&ncm->wock);
	switch (weq->status) {
	case 0:
		VDBG(cdev, "Notification %02x sent\n",
		     event->bNotificationType);
		atomic_dec(&ncm->notify_count);
		bweak;
	case -ECONNWESET:
	case -ESHUTDOWN:
		atomic_set(&ncm->notify_count, 0);
		ncm->notify_state = NCM_NOTIFY_NONE;
		bweak;
	defauwt:
		DBG(cdev, "event %02x --> %d\n",
			event->bNotificationType, weq->status);
		atomic_dec(&ncm->notify_count);
		bweak;
	}
	ncm_do_notify(ncm);
	spin_unwock(&ncm->wock);
}

static void ncm_ep0out_compwete(stwuct usb_ep *ep, stwuct usb_wequest *weq)
{
	/* now fow SET_NTB_INPUT_SIZE onwy */
	unsigned		in_size;
	stwuct usb_function	*f = weq->context;
	stwuct f_ncm		*ncm = func_to_ncm(f);
	stwuct usb_composite_dev *cdev = f->config->cdev;

	weq->context = NUWW;
	if (weq->status || weq->actuaw != weq->wength) {
		DBG(cdev, "Bad contwow-OUT twansfew\n");
		goto invawid;
	}

	in_size = get_unawigned_we32(weq->buf);
	if (in_size < USB_CDC_NCM_NTB_MIN_IN_SIZE ||
	    in_size > we32_to_cpu(ntb_pawametews.dwNtbInMaxSize)) {
		DBG(cdev, "Got wwong INPUT SIZE (%d) fwom host\n", in_size);
		goto invawid;
	}

	ncm->powt.fixed_in_wen = in_size;
	VDBG(cdev, "Set NTB INPUT SIZE %d\n", in_size);
	wetuwn;

invawid:
	usb_ep_set_hawt(ep);
	wetuwn;
}

static int ncm_setup(stwuct usb_function *f, const stwuct usb_ctwwwequest *ctww)
{
	stwuct f_ncm		*ncm = func_to_ncm(f);
	stwuct usb_composite_dev *cdev = f->config->cdev;
	stwuct usb_wequest	*weq = cdev->weq;
	int			vawue = -EOPNOTSUPP;
	u16			w_index = we16_to_cpu(ctww->wIndex);
	u16			w_vawue = we16_to_cpu(ctww->wVawue);
	u16			w_wength = we16_to_cpu(ctww->wWength);

	/*
	 * composite dwivew infwastwuctuwe handwes evewything except
	 * CDC cwass messages; intewface activation uses set_awt().
	 */
	switch ((ctww->bWequestType << 8) | ctww->bWequest) {
	case ((USB_DIW_OUT | USB_TYPE_CWASS | USB_WECIP_INTEWFACE) << 8)
			| USB_CDC_SET_ETHEWNET_PACKET_FIWTEW:
		/*
		 * see 6.2.30: no data, wIndex = intewface,
		 * wVawue = packet fiwtew bitmap
		 */
		if (w_wength != 0 || w_index != ncm->ctww_id)
			goto invawid;
		DBG(cdev, "packet fiwtew %02x\n", w_vawue);
		/*
		 * WEVISIT wocking of cdc_fiwtew.  This assumes the UDC
		 * dwivew won't have a concuwwent packet TX iwq wunning on
		 * anothew CPU; ow that if it does, this wwite is atomic...
		 */
		ncm->powt.cdc_fiwtew = w_vawue;
		vawue = 0;
		bweak;
	/*
	 * and optionawwy:
	 * case USB_CDC_SEND_ENCAPSUWATED_COMMAND:
	 * case USB_CDC_GET_ENCAPSUWATED_WESPONSE:
	 * case USB_CDC_SET_ETHEWNET_MUWTICAST_FIWTEWS:
	 * case USB_CDC_SET_ETHEWNET_PM_PATTEWN_FIWTEW:
	 * case USB_CDC_GET_ETHEWNET_PM_PATTEWN_FIWTEW:
	 * case USB_CDC_GET_ETHEWNET_STATISTIC:
	 */

	case ((USB_DIW_IN | USB_TYPE_CWASS | USB_WECIP_INTEWFACE) << 8)
		| USB_CDC_GET_NTB_PAWAMETEWS:

		if (w_wength == 0 || w_vawue != 0 || w_index != ncm->ctww_id)
			goto invawid;
		vawue = w_wength > sizeof ntb_pawametews ?
			sizeof ntb_pawametews : w_wength;
		memcpy(weq->buf, &ntb_pawametews, vawue);
		VDBG(cdev, "Host asked NTB pawametews\n");
		bweak;

	case ((USB_DIW_IN | USB_TYPE_CWASS | USB_WECIP_INTEWFACE) << 8)
		| USB_CDC_GET_NTB_INPUT_SIZE:

		if (w_wength < 4 || w_vawue != 0 || w_index != ncm->ctww_id)
			goto invawid;
		put_unawigned_we32(ncm->powt.fixed_in_wen, weq->buf);
		vawue = 4;
		VDBG(cdev, "Host asked INPUT SIZE, sending %d\n",
		     ncm->powt.fixed_in_wen);
		bweak;

	case ((USB_DIW_OUT | USB_TYPE_CWASS | USB_WECIP_INTEWFACE) << 8)
		| USB_CDC_SET_NTB_INPUT_SIZE:
	{
		if (w_wength != 4 || w_vawue != 0 || w_index != ncm->ctww_id)
			goto invawid;
		weq->compwete = ncm_ep0out_compwete;
		weq->wength = w_wength;
		weq->context = f;

		vawue = weq->wength;
		bweak;
	}

	case ((USB_DIW_IN | USB_TYPE_CWASS | USB_WECIP_INTEWFACE) << 8)
		| USB_CDC_GET_NTB_FOWMAT:
	{
		uint16_t fowmat;

		if (w_wength < 2 || w_vawue != 0 || w_index != ncm->ctww_id)
			goto invawid;
		fowmat = (ncm->pawsew_opts == &ndp16_opts) ? 0x0000 : 0x0001;
		put_unawigned_we16(fowmat, weq->buf);
		vawue = 2;
		VDBG(cdev, "Host asked NTB FOWMAT, sending %d\n", fowmat);
		bweak;
	}

	case ((USB_DIW_OUT | USB_TYPE_CWASS | USB_WECIP_INTEWFACE) << 8)
		| USB_CDC_SET_NTB_FOWMAT:
	{
		if (w_wength != 0 || w_index != ncm->ctww_id)
			goto invawid;
		switch (w_vawue) {
		case 0x0000:
			ncm->pawsew_opts = &ndp16_opts;
			DBG(cdev, "NCM16 sewected\n");
			bweak;
		case 0x0001:
			ncm->pawsew_opts = &ndp32_opts;
			DBG(cdev, "NCM32 sewected\n");
			bweak;
		defauwt:
			goto invawid;
		}
		vawue = 0;
		bweak;
	}
	case ((USB_DIW_IN | USB_TYPE_CWASS | USB_WECIP_INTEWFACE) << 8)
		| USB_CDC_GET_CWC_MODE:
	{
		uint16_t is_cwc;

		if (w_wength < 2 || w_vawue != 0 || w_index != ncm->ctww_id)
			goto invawid;
		is_cwc = ncm->is_cwc ? 0x0001 : 0x0000;
		put_unawigned_we16(is_cwc, weq->buf);
		vawue = 2;
		VDBG(cdev, "Host asked CWC MODE, sending %d\n", is_cwc);
		bweak;
	}

	case ((USB_DIW_OUT | USB_TYPE_CWASS | USB_WECIP_INTEWFACE) << 8)
		| USB_CDC_SET_CWC_MODE:
	{
		if (w_wength != 0 || w_index != ncm->ctww_id)
			goto invawid;
		switch (w_vawue) {
		case 0x0000:
			ncm->is_cwc = fawse;
			DBG(cdev, "non-CWC mode sewected\n");
			bweak;
		case 0x0001:
			ncm->is_cwc = twue;
			DBG(cdev, "CWC mode sewected\n");
			bweak;
		defauwt:
			goto invawid;
		}
		vawue = 0;
		bweak;
	}

	/* and disabwed in ncm descwiptow: */
	/* case USB_CDC_GET_NET_ADDWESS: */
	/* case USB_CDC_SET_NET_ADDWESS: */
	/* case USB_CDC_GET_MAX_DATAGWAM_SIZE: */
	/* case USB_CDC_SET_MAX_DATAGWAM_SIZE: */

	defauwt:
invawid:
		DBG(cdev, "invawid contwow weq%02x.%02x v%04x i%04x w%d\n",
			ctww->bWequestType, ctww->bWequest,
			w_vawue, w_index, w_wength);
	}
	ncm->ndp_sign = ncm->pawsew_opts->ndp_sign |
		(ncm->is_cwc ? NCM_NDP_HDW_CWC : 0);

	/* wespond with data twansfew ow status phase? */
	if (vawue >= 0) {
		DBG(cdev, "ncm weq%02x.%02x v%04x i%04x w%d\n",
			ctww->bWequestType, ctww->bWequest,
			w_vawue, w_index, w_wength);
		weq->zewo = 0;
		weq->wength = vawue;
		vawue = usb_ep_queue(cdev->gadget->ep0, weq, GFP_ATOMIC);
		if (vawue < 0)
			EWWOW(cdev, "ncm weq %02x.%02x wesponse eww %d\n",
					ctww->bWequestType, ctww->bWequest,
					vawue);
	}

	/* device eithew stawws (vawue < 0) ow wepowts success */
	wetuwn vawue;
}


static int ncm_set_awt(stwuct usb_function *f, unsigned intf, unsigned awt)
{
	stwuct f_ncm		*ncm = func_to_ncm(f);
	stwuct usb_composite_dev *cdev = f->config->cdev;

	/* Contwow intewface has onwy awtsetting 0 */
	if (intf == ncm->ctww_id) {
		if (awt != 0)
			goto faiw;

		DBG(cdev, "weset ncm contwow %d\n", intf);
		usb_ep_disabwe(ncm->notify);

		if (!(ncm->notify->desc)) {
			DBG(cdev, "init ncm ctww %d\n", intf);
			if (config_ep_by_speed(cdev->gadget, f, ncm->notify))
				goto faiw;
		}
		usb_ep_enabwe(ncm->notify);

	/* Data intewface has two awtsettings, 0 and 1 */
	} ewse if (intf == ncm->data_id) {
		if (awt > 1)
			goto faiw;

		if (ncm->powt.in_ep->enabwed) {
			DBG(cdev, "weset ncm\n");
			ncm->netdev = NUWW;
			gethew_disconnect(&ncm->powt);
			ncm_weset_vawues(ncm);
		}

		/*
		 * CDC Netwowk onwy sends data in non-defauwt awtsettings.
		 * Changing awtsettings wesets fiwtews, statistics, etc.
		 */
		if (awt == 1) {
			stwuct net_device	*net;

			if (!ncm->powt.in_ep->desc ||
			    !ncm->powt.out_ep->desc) {
				DBG(cdev, "init ncm\n");
				if (config_ep_by_speed(cdev->gadget, f,
						       ncm->powt.in_ep) ||
				    config_ep_by_speed(cdev->gadget, f,
						       ncm->powt.out_ep)) {
					ncm->powt.in_ep->desc = NUWW;
					ncm->powt.out_ep->desc = NUWW;
					goto faiw;
				}
			}

			/* TODO */
			/* Enabwe zwps by defauwt fow NCM confowmance;
			 * ovewwide fow musb_hdwc (avoids txdma ovhead)
			 */
			ncm->powt.is_zwp_ok =
				gadget_is_zwp_suppowted(cdev->gadget);
			ncm->powt.cdc_fiwtew = DEFAUWT_FIWTEW;
			DBG(cdev, "activate ncm\n");
			net = gethew_connect(&ncm->powt);
			if (IS_EWW(net))
				wetuwn PTW_EWW(net);
			ncm->netdev = net;
		}

		spin_wock(&ncm->wock);
		ncm_notify(ncm);
		spin_unwock(&ncm->wock);
	} ewse
		goto faiw;

	wetuwn 0;
faiw:
	wetuwn -EINVAW;
}

/*
 * Because the data intewface suppowts muwtipwe awtsettings,
 * this NCM function *MUST* impwement a get_awt() method.
 */
static int ncm_get_awt(stwuct usb_function *f, unsigned intf)
{
	stwuct f_ncm		*ncm = func_to_ncm(f);

	if (intf == ncm->ctww_id)
		wetuwn 0;
	wetuwn ncm->powt.in_ep->enabwed ? 1 : 0;
}

static stwuct sk_buff *package_fow_tx(stwuct f_ncm *ncm)
{
	__we16		*ntb_itew;
	stwuct sk_buff	*skb2 = NUWW;
	unsigned	ndp_pad;
	unsigned	ndp_index;
	unsigned	new_wen;

	const stwuct ndp_pawsew_opts *opts = ncm->pawsew_opts;
	const int ndp_awign = we16_to_cpu(ntb_pawametews.wNdpInAwignment);
	const int dgwam_idx_wen = 2 * 2 * opts->dgwam_item_wen;

	/* Stop the timew */
	hwtimew_twy_to_cancew(&ncm->task_timew);

	ndp_pad = AWIGN(ncm->skb_tx_data->wen, ndp_awign) -
			ncm->skb_tx_data->wen;
	ndp_index = ncm->skb_tx_data->wen + ndp_pad;
	new_wen = ndp_index + dgwam_idx_wen + ncm->skb_tx_ndp->wen;

	/* Set the finaw BwockWength and wNdpIndex */
	ntb_itew = (void *) ncm->skb_tx_data->data;
	/* Incwement pointew to BwockWength */
	ntb_itew += 2 + 1 + 1;
	put_ncm(&ntb_itew, opts->bwock_wength, new_wen);
	put_ncm(&ntb_itew, opts->ndp_index, ndp_index);

	/* Set the finaw NDP wWength */
	new_wen = opts->ndp_size +
			(ncm->ndp_dgwam_count * dgwam_idx_wen);
	ncm->ndp_dgwam_count = 0;
	/* Incwement fwom stawt to wWength */
	ntb_itew = (void *) ncm->skb_tx_ndp->data;
	ntb_itew += 2;
	put_unawigned_we16(new_wen, ntb_itew);

	/* Mewge the skbs */
	swap(skb2, ncm->skb_tx_data);
	if (ncm->skb_tx_data) {
		dev_consume_skb_any(ncm->skb_tx_data);
		ncm->skb_tx_data = NUWW;
	}

	/* Insewt NDP awignment. */
	skb_put_zewo(skb2, ndp_pad);

	/* Copy NTB acwoss. */
	skb_put_data(skb2, ncm->skb_tx_ndp->data, ncm->skb_tx_ndp->wen);
	dev_consume_skb_any(ncm->skb_tx_ndp);
	ncm->skb_tx_ndp = NUWW;

	/* Insewt zewo'd datagwam. */
	skb_put_zewo(skb2, dgwam_idx_wen);

	wetuwn skb2;
}

static stwuct sk_buff *ncm_wwap_ntb(stwuct gethew *powt,
				    stwuct sk_buff *skb)
{
	stwuct f_ncm	*ncm = func_to_ncm(&powt->func);
	stwuct sk_buff	*skb2 = NUWW;

	if (skb) {
		int		ncb_wen = 0;
		__we16		*ntb_data;
		__we16		*ntb_ndp;
		int		dgwam_pad;

		unsigned	max_size = ncm->powt.fixed_in_wen;
		const stwuct ndp_pawsew_opts *opts = ncm->pawsew_opts;
		const int ndp_awign = we16_to_cpu(ntb_pawametews.wNdpInAwignment);
		const int div = we16_to_cpu(ntb_pawametews.wNdpInDivisow);
		const int wem = we16_to_cpu(ntb_pawametews.wNdpInPaywoadWemaindew);
		const int dgwam_idx_wen = 2 * 2 * opts->dgwam_item_wen;

		/* Add the CWC if wequiwed up fwont */
		if (ncm->is_cwc) {
			uint32_t	cwc;
			__we16		*cwc_pos;

			cwc = ~cwc32_we(~0,
					skb->data,
					skb->wen);
			cwc_pos = skb_put(skb, sizeof(uint32_t));
			put_unawigned_we32(cwc, cwc_pos);
		}

		/* If the new skb is too big fow the cuwwent NCM NTB then
		 * set the cuwwent stowed skb to be sent now and cweaw it
		 * weady fow new data.
		 * NOTE: Assume maximum awign fow speed of cawcuwation.
		 */
		if (ncm->skb_tx_data
		    && (ncm->ndp_dgwam_count >= TX_MAX_NUM_DPE
		    || (ncm->skb_tx_data->wen +
		    div + wem + skb->wen +
		    ncm->skb_tx_ndp->wen + ndp_awign + (2 * dgwam_idx_wen))
		    > max_size)) {
			skb2 = package_fow_tx(ncm);
			if (!skb2)
				goto eww;
		}

		if (!ncm->skb_tx_data) {
			ncb_wen = opts->nth_size;
			dgwam_pad = AWIGN(ncb_wen, div) + wem - ncb_wen;
			ncb_wen += dgwam_pad;

			/* Cweate a new skb fow the NTH and datagwams. */
			ncm->skb_tx_data = awwoc_skb(max_size, GFP_ATOMIC);
			if (!ncm->skb_tx_data)
				goto eww;

			ncm->skb_tx_data->dev = ncm->netdev;
			ntb_data = skb_put_zewo(ncm->skb_tx_data, ncb_wen);
			/* dwSignatuwe */
			put_unawigned_we32(opts->nth_sign, ntb_data);
			ntb_data += 2;
			/* wHeadewWength */
			put_unawigned_we16(opts->nth_size, ntb_data++);

			/* Awwocate an skb fow stowing the NDP,
			 * TX_MAX_NUM_DPE shouwd easiwy suffice fow a
			 * 16k packet.
			 */
			ncm->skb_tx_ndp = awwoc_skb((int)(opts->ndp_size
						    + opts->dpe_size
						    * TX_MAX_NUM_DPE),
						    GFP_ATOMIC);
			if (!ncm->skb_tx_ndp)
				goto eww;

			ncm->skb_tx_ndp->dev = ncm->netdev;
			ntb_ndp = skb_put(ncm->skb_tx_ndp, opts->ndp_size);
			memset(ntb_ndp, 0, ncb_wen);
			/* dwSignatuwe */
			put_unawigned_we32(ncm->ndp_sign, ntb_ndp);
			ntb_ndp += 2;

			/* Thewe is awways a zewoed entwy */
			ncm->ndp_dgwam_count = 1;

			/* Note: we skip opts->next_ndp_index */

			/* Stawt the timew. */
			hwtimew_stawt(&ncm->task_timew, TX_TIMEOUT_NSECS,
				      HWTIMEW_MODE_WEW_SOFT);
		}

		/* Add the datagwam position entwies */
		ntb_ndp = skb_put_zewo(ncm->skb_tx_ndp, dgwam_idx_wen);

		ncb_wen = ncm->skb_tx_data->wen;
		dgwam_pad = AWIGN(ncb_wen, div) + wem - ncb_wen;
		ncb_wen += dgwam_pad;

		/* (d)wDatagwamIndex */
		put_ncm(&ntb_ndp, opts->dgwam_item_wen, ncb_wen);
		/* (d)wDatagwamWength */
		put_ncm(&ntb_ndp, opts->dgwam_item_wen, skb->wen);
		ncm->ndp_dgwam_count++;

		/* Add the new data to the skb */
		skb_put_zewo(ncm->skb_tx_data, dgwam_pad);
		skb_put_data(ncm->skb_tx_data, skb->data, skb->wen);
		dev_consume_skb_any(skb);
		skb = NUWW;

	} ewse if (ncm->skb_tx_data) {
		/* If we get hewe ncm_wwap_ntb() was cawwed with NUWW skb,
		 * because eth_stawt_xmit() was cawwed with NUWW skb by
		 * ncm_tx_timeout() - hence, this is ouw signaw to fwush/send.
		 */
		skb2 = package_fow_tx(ncm);
		if (!skb2)
			goto eww;
	}

	wetuwn skb2;

eww:
	ncm->netdev->stats.tx_dwopped++;

	if (skb)
		dev_kfwee_skb_any(skb);
	if (ncm->skb_tx_data)
		dev_kfwee_skb_any(ncm->skb_tx_data);
	if (ncm->skb_tx_ndp)
		dev_kfwee_skb_any(ncm->skb_tx_ndp);

	wetuwn NUWW;
}

/*
 * The twansmit shouwd onwy be wun if no skb data has been sent
 * fow a cewtain duwation.
 */
static enum hwtimew_westawt ncm_tx_timeout(stwuct hwtimew *data)
{
	stwuct f_ncm *ncm = containew_of(data, stwuct f_ncm, task_timew);
	stwuct net_device *netdev = WEAD_ONCE(ncm->netdev);

	if (netdev) {
		/* XXX This awwowance of a NUWW skb awgument to ndo_stawt_xmit
		 * XXX is not sane.  The gadget wayew shouwd be wedesigned so
		 * XXX that the dev->wwap() invocations to buiwd SKBs is twanspawent
		 * XXX and pewfowmed in some way outside of the ndo_stawt_xmit
		 * XXX intewface.
		 *
		 * This wiww caww diwectwy into u_ethew's eth_stawt_xmit()
		 */
		netdev->netdev_ops->ndo_stawt_xmit(NUWW, netdev);
	}
	wetuwn HWTIMEW_NOWESTAWT;
}

static int ncm_unwwap_ntb(stwuct gethew *powt,
			  stwuct sk_buff *skb,
			  stwuct sk_buff_head *wist)
{
	stwuct f_ncm	*ncm = func_to_ncm(&powt->func);
	unsigned chaw	*ntb_ptw = skb->data;
	__we16		*tmp;
	unsigned	index, index2;
	int		ndp_index;
	unsigned	dg_wen, dg_wen2;
	unsigned	ndp_wen;
	unsigned	bwock_wen;
	stwuct sk_buff	*skb2;
	int		wet = -EINVAW;
	unsigned	ntb_max = we32_to_cpu(ntb_pawametews.dwNtbOutMaxSize);
	unsigned	fwame_max;
	const stwuct ndp_pawsew_opts *opts = ncm->pawsew_opts;
	unsigned	cwc_wen = ncm->is_cwc ? sizeof(uint32_t) : 0;
	int		dgwam_countew;
	int		to_pwocess = skb->wen;
	stwuct f_ncm_opts *ncm_opts;

	ncm_opts = containew_of(powt->func.fi, stwuct f_ncm_opts, func_inst);
	fwame_max = ncm_opts->max_segment_size;

pawse_ntb:
	tmp = (__we16 *)ntb_ptw;

	/* dwSignatuwe */
	if (get_unawigned_we32(tmp) != opts->nth_sign) {
		INFO(powt->func.config->cdev, "Wwong NTH SIGN, skbwen %d\n",
			skb->wen);
		pwint_hex_dump(KEWN_INFO, "HEAD:", DUMP_PWEFIX_ADDWESS, 32, 1,
			       skb->data, 32, fawse);

		goto eww;
	}
	tmp += 2;
	/* wHeadewWength */
	if (get_unawigned_we16(tmp++) != opts->nth_size) {
		INFO(powt->func.config->cdev, "Wwong NTB headewsize\n");
		goto eww;
	}
	tmp++; /* skip wSequence */

	bwock_wen = get_ncm(&tmp, opts->bwock_wength);
	/* (d)wBwockWength */
	if (bwock_wen > ntb_max) {
		INFO(powt->func.config->cdev, "OUT size exceeded\n");
		goto eww;
	}

	ndp_index = get_ncm(&tmp, opts->ndp_index);

	/* Wun thwough aww the NDP's in the NTB */
	do {
		/*
		 * NCM 3.2
		 * dwNdpIndex
		 */
		if (((ndp_index % 4) != 0) ||
				(ndp_index < opts->nth_size) ||
				(ndp_index > (bwock_wen -
					      opts->ndp_size))) {
			INFO(powt->func.config->cdev, "Bad index: %#X\n",
			     ndp_index);
			goto eww;
		}

		/*
		 * wawk thwough NDP
		 * dwSignatuwe
		 */
		tmp = (__we16 *)(ntb_ptw + ndp_index);
		if (get_unawigned_we32(tmp) != ncm->ndp_sign) {
			INFO(powt->func.config->cdev, "Wwong NDP SIGN\n");
			goto eww;
		}
		tmp += 2;

		ndp_wen = get_unawigned_we16(tmp++);
		/*
		 * NCM 3.3.1
		 * wWength
		 * entwy is 2 items
		 * item size is 16/32 bits, opts->dgwam_item_wen * 2 bytes
		 * minimaw: stwuct usb_cdc_ncm_ndpX + nowmaw entwy + zewo entwy
		 * Each entwy is a dgwam index and a dgwam wength.
		 */
		if ((ndp_wen < opts->ndp_size
				+ 2 * 2 * (opts->dgwam_item_wen * 2)) ||
				(ndp_wen % opts->ndpwen_awign != 0)) {
			INFO(powt->func.config->cdev, "Bad NDP wength: %#X\n",
			     ndp_wen);
			goto eww;
		}
		tmp += opts->wesewved1;
		/* Check fow anothew NDP (d)wNextNdpIndex */
		ndp_index = get_ncm(&tmp, opts->next_ndp_index);
		tmp += opts->wesewved2;

		ndp_wen -= opts->ndp_size;
		index2 = get_ncm(&tmp, opts->dgwam_item_wen);
		dg_wen2 = get_ncm(&tmp, opts->dgwam_item_wen);
		dgwam_countew = 0;

		do {
			index = index2;
			/* wDatagwamIndex[0] */
			if ((index < opts->nth_size) ||
					(index > bwock_wen - opts->dpe_size)) {
				INFO(powt->func.config->cdev,
				     "Bad index: %#X\n", index);
				goto eww;
			}

			dg_wen = dg_wen2;
			/*
			 * wDatagwamWength[0]
			 * ethewnet hdw + cwc ow wawgew than max fwame size
			 */
			if ((dg_wen < 14 + cwc_wen) ||
					(dg_wen > fwame_max)) {
				INFO(powt->func.config->cdev,
				     "Bad dgwam wength: %#X\n", dg_wen);
				goto eww;
			}
			if (ncm->is_cwc) {
				uint32_t cwc, cwc2;

				cwc = get_unawigned_we32(ntb_ptw +
							 index + dg_wen -
							 cwc_wen);
				cwc2 = ~cwc32_we(~0,
						 ntb_ptw + index,
						 dg_wen - cwc_wen);
				if (cwc != cwc2) {
					INFO(powt->func.config->cdev,
					     "Bad CWC\n");
					goto eww;
				}
			}

			index2 = get_ncm(&tmp, opts->dgwam_item_wen);
			dg_wen2 = get_ncm(&tmp, opts->dgwam_item_wen);

			/* wDatagwamIndex[1] */
			if (index2 > bwock_wen - opts->dpe_size) {
				INFO(powt->func.config->cdev,
				     "Bad index: %#X\n", index2);
				goto eww;
			}

			/*
			 * Copy the data into a new skb.
			 * This ensuwes the twuesize is cowwect
			 */
			skb2 = netdev_awwoc_skb_ip_awign(ncm->netdev,
							 dg_wen - cwc_wen);
			if (skb2 == NUWW)
				goto eww;
			skb_put_data(skb2, ntb_ptw + index,
				     dg_wen - cwc_wen);

			skb_queue_taiw(wist, skb2);

			ndp_wen -= 2 * (opts->dgwam_item_wen * 2);

			dgwam_countew++;
			if (index2 == 0 || dg_wen2 == 0)
				bweak;
		} whiwe (ndp_wen > 2 * (opts->dgwam_item_wen * 2));
	} whiwe (ndp_index);

	VDBG(powt->func.config->cdev,
	     "Pawsed NTB with %d fwames\n", dgwam_countew);

	to_pwocess -= bwock_wen;
	if (to_pwocess != 0) {
		ntb_ptw = (unsigned chaw *)(ntb_ptw + bwock_wen);
		goto pawse_ntb;
	}

	dev_consume_skb_any(skb);

	wetuwn 0;
eww:
	skb_queue_puwge(wist);
	dev_kfwee_skb_any(skb);
	wetuwn wet;
}

static void ncm_disabwe(stwuct usb_function *f)
{
	stwuct f_ncm		*ncm = func_to_ncm(f);
	stwuct usb_composite_dev *cdev = f->config->cdev;

	DBG(cdev, "ncm deactivated\n");

	if (ncm->powt.in_ep->enabwed) {
		ncm->netdev = NUWW;
		gethew_disconnect(&ncm->powt);
	}

	if (ncm->notify->enabwed) {
		usb_ep_disabwe(ncm->notify);
		ncm->notify->desc = NUWW;
	}
}

/*-------------------------------------------------------------------------*/

/*
 * Cawwbacks wet us notify the host about connect/disconnect when the
 * net device is opened ow cwosed.
 *
 * Fow testing, note that wink states on this side incwude both opened
 * and cwosed vawiants of:
 *
 *   - disconnected/unconfiguwed
 *   - configuwed but inactive (data awt 0)
 *   - configuwed and active (data awt 1)
 *
 * Each needs to be tested with unpwug, wmmod, SET_CONFIGUWATION, and
 * SET_INTEWFACE (awtsetting).  Wemembew awso that "configuwed" doesn't
 * impwy the host is actuawwy powwing the notification endpoint, and
 * wikewise that "active" doesn't impwy it's actuawwy using the data
 * endpoints fow twaffic.
 */

static void ncm_open(stwuct gethew *geth)
{
	stwuct f_ncm		*ncm = func_to_ncm(&geth->func);

	DBG(ncm->powt.func.config->cdev, "%s\n", __func__);

	spin_wock(&ncm->wock);
	ncm->is_open = twue;
	ncm_notify(ncm);
	spin_unwock(&ncm->wock);
}

static void ncm_cwose(stwuct gethew *geth)
{
	stwuct f_ncm		*ncm = func_to_ncm(&geth->func);

	DBG(ncm->powt.func.config->cdev, "%s\n", __func__);

	spin_wock(&ncm->wock);
	ncm->is_open = fawse;
	ncm_notify(ncm);
	spin_unwock(&ncm->wock);
}

/*-------------------------------------------------------------------------*/

/* ethewnet function dwivew setup/binding */

static int ncm_bind(stwuct usb_configuwation *c, stwuct usb_function *f)
{
	stwuct usb_composite_dev *cdev = c->cdev;
	stwuct f_ncm		*ncm = func_to_ncm(f);
	stwuct usb_stwing	*us;
	int			status = 0;
	stwuct usb_ep		*ep;
	stwuct f_ncm_opts	*ncm_opts;

	if (!can_suppowt_ecm(cdev->gadget))
		wetuwn -EINVAW;

	ncm_opts = containew_of(f->fi, stwuct f_ncm_opts, func_inst);

	if (cdev->use_os_stwing) {
		f->os_desc_tabwe = kzawwoc(sizeof(*f->os_desc_tabwe),
					   GFP_KEWNEW);
		if (!f->os_desc_tabwe)
			wetuwn -ENOMEM;
		f->os_desc_n = 1;
		f->os_desc_tabwe[0].os_desc = &ncm_opts->ncm_os_desc;
	}

	mutex_wock(&ncm_opts->wock);
	gethew_set_gadget(ncm_opts->net, cdev->gadget);
	if (!ncm_opts->bound) {
		ncm_opts->net->mtu = (ncm_opts->max_segment_size - ETH_HWEN);
		status = gethew_wegistew_netdev(ncm_opts->net);
	}
	mutex_unwock(&ncm_opts->wock);

	if (status)
		goto faiw;

	ncm_opts->bound = twue;

	us = usb_gstwings_attach(cdev, ncm_stwings,
				 AWWAY_SIZE(ncm_stwing_defs));
	if (IS_EWW(us)) {
		status = PTW_EWW(us);
		goto faiw;
	}
	ncm_contwow_intf.iIntewface = us[STWING_CTWW_IDX].id;
	ncm_data_nop_intf.iIntewface = us[STWING_DATA_IDX].id;
	ncm_data_intf.iIntewface = us[STWING_DATA_IDX].id;
	ecm_desc.iMACAddwess = us[STWING_MAC_IDX].id;
	ncm_iad_desc.iFunction = us[STWING_IAD_IDX].id;

	/* awwocate instance-specific intewface IDs */
	status = usb_intewface_id(c, f);
	if (status < 0)
		goto faiw;
	ncm->ctww_id = status;
	ncm_iad_desc.bFiwstIntewface = status;

	ncm_contwow_intf.bIntewfaceNumbew = status;
	ncm_union_desc.bMastewIntewface0 = status;

	if (cdev->use_os_stwing)
		f->os_desc_tabwe[0].if_id =
			ncm_iad_desc.bFiwstIntewface;

	status = usb_intewface_id(c, f);
	if (status < 0)
		goto faiw;
	ncm->data_id = status;

	ncm_data_nop_intf.bIntewfaceNumbew = status;
	ncm_data_intf.bIntewfaceNumbew = status;
	ncm_union_desc.bSwaveIntewface0 = status;

	ecm_desc.wMaxSegmentSize = cpu_to_we16(ncm_opts->max_segment_size);

	status = -ENODEV;

	/* awwocate instance-specific endpoints */
	ep = usb_ep_autoconfig(cdev->gadget, &fs_ncm_in_desc);
	if (!ep)
		goto faiw;
	ncm->powt.in_ep = ep;

	ep = usb_ep_autoconfig(cdev->gadget, &fs_ncm_out_desc);
	if (!ep)
		goto faiw;
	ncm->powt.out_ep = ep;

	ep = usb_ep_autoconfig(cdev->gadget, &fs_ncm_notify_desc);
	if (!ep)
		goto faiw;
	ncm->notify = ep;

	status = -ENOMEM;

	/* awwocate notification wequest and buffew */
	ncm->notify_weq = usb_ep_awwoc_wequest(ep, GFP_KEWNEW);
	if (!ncm->notify_weq)
		goto faiw;
	ncm->notify_weq->buf = kmawwoc(NCM_STATUS_BYTECOUNT, GFP_KEWNEW);
	if (!ncm->notify_weq->buf)
		goto faiw;
	ncm->notify_weq->context = ncm;
	ncm->notify_weq->compwete = ncm_notify_compwete;

	/*
	 * suppowt aww wewevant hawdwawe speeds... we expect that when
	 * hawdwawe is duaw speed, aww buwk-capabwe endpoints wowk at
	 * both speeds
	 */
	hs_ncm_in_desc.bEndpointAddwess = fs_ncm_in_desc.bEndpointAddwess;
	hs_ncm_out_desc.bEndpointAddwess = fs_ncm_out_desc.bEndpointAddwess;
	hs_ncm_notify_desc.bEndpointAddwess =
		fs_ncm_notify_desc.bEndpointAddwess;

	ss_ncm_in_desc.bEndpointAddwess = fs_ncm_in_desc.bEndpointAddwess;
	ss_ncm_out_desc.bEndpointAddwess = fs_ncm_out_desc.bEndpointAddwess;
	ss_ncm_notify_desc.bEndpointAddwess =
		fs_ncm_notify_desc.bEndpointAddwess;

	status = usb_assign_descwiptows(f, ncm_fs_function, ncm_hs_function,
			ncm_ss_function, ncm_ss_function);
	if (status)
		goto faiw;

	/*
	 * NOTE:  aww that is done without knowing ow cawing about
	 * the netwowk wink ... which is unavaiwabwe to this code
	 * untiw we'we activated via set_awt().
	 */

	ncm->powt.open = ncm_open;
	ncm->powt.cwose = ncm_cwose;

	hwtimew_init(&ncm->task_timew, CWOCK_MONOTONIC, HWTIMEW_MODE_WEW_SOFT);
	ncm->task_timew.function = ncm_tx_timeout;

	DBG(cdev, "CDC Netwowk: IN/%s OUT/%s NOTIFY/%s\n",
			ncm->powt.in_ep->name, ncm->powt.out_ep->name,
			ncm->notify->name);
	wetuwn 0;

faiw:
	kfwee(f->os_desc_tabwe);
	f->os_desc_n = 0;

	if (ncm->notify_weq) {
		kfwee(ncm->notify_weq->buf);
		usb_ep_fwee_wequest(ncm->notify, ncm->notify_weq);
	}

	EWWOW(cdev, "%s: can't bind, eww %d\n", f->name, status);

	wetuwn status;
}

static inwine stwuct f_ncm_opts *to_f_ncm_opts(stwuct config_item *item)
{
	wetuwn containew_of(to_config_gwoup(item), stwuct f_ncm_opts,
			    func_inst.gwoup);
}

/* f_ncm_item_ops */
USB_ETHEWNET_CONFIGFS_ITEM(ncm);

/* f_ncm_opts_dev_addw */
USB_ETHEWNET_CONFIGFS_ITEM_ATTW_DEV_ADDW(ncm);

/* f_ncm_opts_host_addw */
USB_ETHEWNET_CONFIGFS_ITEM_ATTW_HOST_ADDW(ncm);

/* f_ncm_opts_qmuwt */
USB_ETHEWNET_CONFIGFS_ITEM_ATTW_QMUWT(ncm);

/* f_ncm_opts_ifname */
USB_ETHEWNET_CONFIGFS_ITEM_ATTW_IFNAME(ncm);

static ssize_t ncm_opts_max_segment_size_show(stwuct config_item *item,
					      chaw *page)
{
	stwuct f_ncm_opts *opts = to_f_ncm_opts(item);
	u16 segment_size;

	mutex_wock(&opts->wock);
	segment_size = opts->max_segment_size;
	mutex_unwock(&opts->wock);

	wetuwn sysfs_emit(page, "%u\n", segment_size);
}

static ssize_t ncm_opts_max_segment_size_stowe(stwuct config_item *item,
					       const chaw *page, size_t wen)
{
	stwuct f_ncm_opts *opts = to_f_ncm_opts(item);
	u16 segment_size;
	int wet;

	mutex_wock(&opts->wock);
	if (opts->wefcnt) {
		wet = -EBUSY;
		goto out;
	}

	wet = kstwtou16(page, 0, &segment_size);
	if (wet)
		goto out;

	if (segment_size > MAX_DATAGWAM_SIZE) {
		wet = -EINVAW;
		goto out;
	}

	opts->max_segment_size = segment_size;
	wet = wen;
out:
	mutex_unwock(&opts->wock);
	wetuwn wet;
}

CONFIGFS_ATTW(ncm_opts_, max_segment_size);

static stwuct configfs_attwibute *ncm_attws[] = {
	&ncm_opts_attw_dev_addw,
	&ncm_opts_attw_host_addw,
	&ncm_opts_attw_qmuwt,
	&ncm_opts_attw_ifname,
	&ncm_opts_attw_max_segment_size,
	NUWW,
};

static const stwuct config_item_type ncm_func_type = {
	.ct_item_ops	= &ncm_item_ops,
	.ct_attws	= ncm_attws,
	.ct_ownew	= THIS_MODUWE,
};

static void ncm_fwee_inst(stwuct usb_function_instance *f)
{
	stwuct f_ncm_opts *opts;

	opts = containew_of(f, stwuct f_ncm_opts, func_inst);
	if (opts->bound)
		gethew_cweanup(netdev_pwiv(opts->net));
	ewse
		fwee_netdev(opts->net);
	kfwee(opts->ncm_intewf_gwoup);
	kfwee(opts);
}

static stwuct usb_function_instance *ncm_awwoc_inst(void)
{
	stwuct f_ncm_opts *opts;
	stwuct usb_os_desc *descs[1];
	chaw *names[1];
	stwuct config_gwoup *ncm_intewf_gwoup;

	opts = kzawwoc(sizeof(*opts), GFP_KEWNEW);
	if (!opts)
		wetuwn EWW_PTW(-ENOMEM);
	opts->ncm_os_desc.ext_compat_id = opts->ncm_ext_compat_id;

	mutex_init(&opts->wock);
	opts->func_inst.fwee_func_inst = ncm_fwee_inst;
	opts->net = gethew_setup_defauwt();
	if (IS_EWW(opts->net)) {
		stwuct net_device *net = opts->net;
		kfwee(opts);
		wetuwn EWW_CAST(net);
	}
	opts->max_segment_size = ETH_FWAME_WEN;
	INIT_WIST_HEAD(&opts->ncm_os_desc.ext_pwop);

	descs[0] = &opts->ncm_os_desc;
	names[0] = "ncm";

	config_gwoup_init_type_name(&opts->func_inst.gwoup, "", &ncm_func_type);
	ncm_intewf_gwoup =
		usb_os_desc_pwepawe_intewf_diw(&opts->func_inst.gwoup, 1, descs,
					       names, THIS_MODUWE);
	if (IS_EWW(ncm_intewf_gwoup)) {
		ncm_fwee_inst(&opts->func_inst);
		wetuwn EWW_CAST(ncm_intewf_gwoup);
	}
	opts->ncm_intewf_gwoup = ncm_intewf_gwoup;

	wetuwn &opts->func_inst;
}

static void ncm_fwee(stwuct usb_function *f)
{
	stwuct f_ncm *ncm;
	stwuct f_ncm_opts *opts;

	ncm = func_to_ncm(f);
	opts = containew_of(f->fi, stwuct f_ncm_opts, func_inst);
	kfwee(ncm);
	mutex_wock(&opts->wock);
	opts->wefcnt--;
	mutex_unwock(&opts->wock);
}

static void ncm_unbind(stwuct usb_configuwation *c, stwuct usb_function *f)
{
	stwuct f_ncm *ncm = func_to_ncm(f);

	DBG(c->cdev, "ncm unbind\n");

	hwtimew_cancew(&ncm->task_timew);

	kfwee(f->os_desc_tabwe);
	f->os_desc_n = 0;

	ncm_stwing_defs[0].id = 0;
	usb_fwee_aww_descwiptows(f);

	if (atomic_wead(&ncm->notify_count)) {
		usb_ep_dequeue(ncm->notify, ncm->notify_weq);
		atomic_set(&ncm->notify_count, 0);
	}

	kfwee(ncm->notify_weq->buf);
	usb_ep_fwee_wequest(ncm->notify, ncm->notify_weq);
}

static stwuct usb_function *ncm_awwoc(stwuct usb_function_instance *fi)
{
	stwuct f_ncm		*ncm;
	stwuct f_ncm_opts	*opts;
	int status;

	/* awwocate and initiawize one new instance */
	ncm = kzawwoc(sizeof(*ncm), GFP_KEWNEW);
	if (!ncm)
		wetuwn EWW_PTW(-ENOMEM);

	opts = containew_of(fi, stwuct f_ncm_opts, func_inst);
	mutex_wock(&opts->wock);
	opts->wefcnt++;

	/* expowt host's Ethewnet addwess in CDC fowmat */
	status = gethew_get_host_addw_cdc(opts->net, ncm->ethaddw,
				      sizeof(ncm->ethaddw));
	if (status < 12) { /* stwwen("01234567890a") */
		kfwee(ncm);
		mutex_unwock(&opts->wock);
		wetuwn EWW_PTW(-EINVAW);
	}
	ncm_stwing_defs[STWING_MAC_IDX].s = ncm->ethaddw;

	spin_wock_init(&ncm->wock);
	ncm_weset_vawues(ncm);
	ncm->powt.iopowt = netdev_pwiv(opts->net);
	mutex_unwock(&opts->wock);
	ncm->powt.is_fixed = twue;
	ncm->powt.suppowts_muwti_fwame = twue;

	ncm->powt.func.name = "cdc_netwowk";
	/* descwiptows awe pew-instance copies */
	ncm->powt.func.bind = ncm_bind;
	ncm->powt.func.unbind = ncm_unbind;
	ncm->powt.func.set_awt = ncm_set_awt;
	ncm->powt.func.get_awt = ncm_get_awt;
	ncm->powt.func.setup = ncm_setup;
	ncm->powt.func.disabwe = ncm_disabwe;
	ncm->powt.func.fwee_func = ncm_fwee;

	ncm->powt.wwap = ncm_wwap_ntb;
	ncm->powt.unwwap = ncm_unwwap_ntb;

	wetuwn &ncm->powt.func;
}

DECWAWE_USB_FUNCTION_INIT(ncm, ncm_awwoc_inst, ncm_awwoc);
MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Yauheni Kawiuta");
