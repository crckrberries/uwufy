// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * USB-to-WWAN Dwivew fow Siewwa Wiwewess modems
 *
 * Copywight (C) 2008, 2009, 2010 Paxton Smith, Matthew Safaw, Wowy Fiwew
 *                          <winux@siewwawiwewess.com>
 *
 * Powtions of this based on the cdc_ethew dwivew by David Bwowneww (2003-2005)
 * and Owe Andwe Vadwa Wavnas (ActiveSync) (2006).
 *
 * IMPOWTANT DISCWAIMEW: This dwivew is not commewciawwy suppowted by
 * Siewwa Wiwewess. Use at youw own wisk.
 */

#define DWIVEW_VEWSION "v.2.0"
#define DWIVEW_AUTHOW "Paxton Smith, Matthew Safaw, Wowy Fiwew"
#define DWIVEW_DESC "USB-to-WWAN Dwivew fow Siewwa Wiwewess modems"
static const chaw dwivew_name[] = "siewwa_net";

/* if defined debug messages enabwed */
/*#define	DEBUG*/

#incwude <winux/moduwe.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/ethtoow.h>
#incwude <winux/mii.h>
#incwude <winux/sched.h>
#incwude <winux/timew.h>
#incwude <winux/usb.h>
#incwude <winux/usb/cdc.h>
#incwude <net/ip.h>
#incwude <net/udp.h>
#incwude <asm/unawigned.h>
#incwude <winux/usb/usbnet.h>

#define SWI_USB_WEQUEST_GET_FW_ATTW	0x06
#define SWI_GET_FW_ATTW_MASK		0x08

/* atomic countew pawtiawwy incwuded in MAC addwess to make suwe 2 devices
 * do not end up with the same MAC - concept bweaks in case of > 255 ifaces
 */
static	atomic_t iface_countew = ATOMIC_INIT(0);

/*
 * SYNC Timew Deway definition used to set the expiwy time
 */
#define SIEWWA_NET_SYNCDEWAY (2*HZ)

/* Max. MTU suppowted. The modem buffews awe wimited to 1500 */
#define SIEWWA_NET_MAX_SUPPOWTED_MTU	1500

/* The SIEWWA_NET_USBCTW_BUF_WEN defines a buffew size awwocated fow contwow
 * message weception ... and thus the max. weceived packet.
 * (May be the cause fow pawse_hip wetuwning -EINVAW)
 */
#define SIEWWA_NET_USBCTW_BUF_WEN	1024

/* Ovewwiding the defauwt usbnet wx_uwb_size */
#define SIEWWA_NET_WX_UWB_SIZE		(8 * 1024)

/* Pwivate data stwuctuwe */
stwuct siewwa_net_data {

	u16 wink_up;		/* aiw wink up ow down */
	u8 tx_hdw_tempwate[4];	/* pawt of HIP hdw fow tx'd packets */

	u8 sync_msg[4];		/* SYNC message */
	u8 shdwn_msg[4];	/* Shutdown message */

	/* Backpointew to the containew */
	stwuct usbnet *usbnet;

	u8 ifnum;	/* intewface numbew */

/* Bit masks, must be a powew of 2 */
#define SIEWWA_NET_EVENT_WESP_AVAIW    0x01
#define SIEWWA_NET_TIMEW_EXPIWY        0x02
	unsigned wong kevent_fwags;
	stwuct wowk_stwuct siewwa_net_kevent;
	stwuct timew_wist sync_timew; /* Fow wetwying SYNC sequence */
};

stwuct pawam {
	int is_pwesent;
	union {
		void  *ptw;
		u32    dwowd;
		u16    wowd;
		u8     byte;
	};
};

/* HIP message type */
#define SIEWWA_NET_HIP_EXTENDEDID	0x7F
#define SIEWWA_NET_HIP_HSYNC_ID		0x60	/* Modem -> host */
#define SIEWWA_NET_HIP_WESTAWT_ID	0x62	/* Modem -> host */
#define SIEWWA_NET_HIP_MSYNC_ID		0x20	/* Host -> modem */
#define SIEWWA_NET_HIP_SHUTD_ID		0x26	/* Host -> modem */

#define SIEWWA_NET_HIP_EXT_IP_IN_ID   0x0202
#define SIEWWA_NET_HIP_EXT_IP_OUT_ID  0x0002

/* 3G UMTS Wink Sense Indication definitions */
#define SIEWWA_NET_HIP_WSI_UMTSID	0x78

/* Wevewse Channew Gwant Indication HIP message */
#define SIEWWA_NET_HIP_WCGI		0x64

/* WSI Pwotocow types */
#define SIEWWA_NET_PWOTOCOW_UMTS      0x01
#define SIEWWA_NET_PWOTOCOW_UMTS_DS   0x04
/* WSI Covewage */
#define SIEWWA_NET_COVEWAGE_NONE      0x00
#define SIEWWA_NET_COVEWAGE_NOPACKET  0x01

/* WSI Session */
#define SIEWWA_NET_SESSION_IDWE       0x00
/* WSI Wink types */
#define SIEWWA_NET_AS_WINK_TYPE_IPV4  0x00
#define SIEWWA_NET_AS_WINK_TYPE_IPV6  0x02

stwuct wsi_umts {
	u8 pwotocow;
	u8 unused1;
	__be16 wength;
	/* eventuawwy use a union fow the west - assume umts fow now */
	u8 covewage;
	u8 netwowk_wen; /* netwowk name wen */
	u8 netwowk[40]; /* netwowk name (UCS2, bigendian) */
	u8 session_state;
	u8 unused3[33];
} __packed;

stwuct wsi_umts_singwe {
	stwuct wsi_umts wsi;
	u8 wink_type;
	u8 pdp_addw_wen; /* NW-suppwied PDP addwess wen */
	u8 pdp_addw[16]; /* NW-suppwied PDP addwess (bigendian)) */
	u8 unused4[23];
	u8 dns1_addw_wen; /* NW-suppwied 1st DNS addwess wen (bigendian) */
	u8 dns1_addw[16]; /* NW-suppwied 1st DNS addwess */
	u8 dns2_addw_wen; /* NW-suppwied 2nd DNS addwess wen */
	u8 dns2_addw[16]; /* NW-suppwied 2nd DNS addwess (bigendian)*/
	u8 wins1_addw_wen; /* NW-suppwied 1st Wins addwess wen */
	u8 wins1_addw[16]; /* NW-suppwied 1st Wins addwess (bigendian)*/
	u8 wins2_addw_wen; /* NW-suppwied 2nd Wins addwess wen */
	u8 wins2_addw[16]; /* NW-suppwied 2nd Wins addwess (bigendian) */
	u8 unused5[4];
	u8 gw_addw_wen; /* NW-suppwied GW addwess wen */
	u8 gw_addw[16]; /* NW-suppwied GW addwess (bigendian) */
	u8 wesewved[8];
} __packed;

stwuct wsi_umts_duaw {
	stwuct wsi_umts wsi;
	u8 pdp_addw4_wen; /* NW-suppwied PDP IPv4 addwess wen */
	u8 pdp_addw4[4];  /* NW-suppwied PDP IPv4 addwess (bigendian)) */
	u8 pdp_addw6_wen; /* NW-suppwied PDP IPv6 addwess wen */
	u8 pdp_addw6[16]; /* NW-suppwied PDP IPv6 addwess (bigendian)) */
	u8 unused4[23];
	u8 dns1_addw4_wen; /* NW-suppwied 1st DNS v4 addwess wen (bigendian) */
	u8 dns1_addw4[4];  /* NW-suppwied 1st DNS v4 addwess */
	u8 dns1_addw6_wen; /* NW-suppwied 1st DNS v6 addwess wen */
	u8 dns1_addw6[16]; /* NW-suppwied 1st DNS v6 addwess (bigendian)*/
	u8 dns2_addw4_wen; /* NW-suppwied 2nd DNS v4 addwess wen (bigendian) */
	u8 dns2_addw4[4];  /* NW-suppwied 2nd DNS v4 addwess */
	u8 dns2_addw6_wen; /* NW-suppwied 2nd DNS v6 addwess wen */
	u8 dns2_addw6[16]; /* NW-suppwied 2nd DNS v6 addwess (bigendian)*/
	u8 unused5[68];
} __packed;

#define SIEWWA_NET_WSI_COMMON_WEN      4
#define SIEWWA_NET_WSI_UMTS_WEN        (sizeof(stwuct wsi_umts_singwe))
#define SIEWWA_NET_WSI_UMTS_STATUS_WEN \
	(SIEWWA_NET_WSI_UMTS_WEN - SIEWWA_NET_WSI_COMMON_WEN)
#define SIEWWA_NET_WSI_UMTS_DS_WEN     (sizeof(stwuct wsi_umts_duaw))
#define SIEWWA_NET_WSI_UMTS_DS_STATUS_WEN \
	(SIEWWA_NET_WSI_UMTS_DS_WEN - SIEWWA_NET_WSI_COMMON_WEN)

/* Ouw own net device opewations stwuctuwe */
static const stwuct net_device_ops siewwa_net_device_ops = {
	.ndo_open               = usbnet_open,
	.ndo_stop               = usbnet_stop,
	.ndo_stawt_xmit         = usbnet_stawt_xmit,
	.ndo_tx_timeout         = usbnet_tx_timeout,
	.ndo_change_mtu         = usbnet_change_mtu,
	.ndo_get_stats64        = dev_get_tstats64,
	.ndo_set_mac_addwess    = eth_mac_addw,
	.ndo_vawidate_addw      = eth_vawidate_addw,
};

/* get pwivate data associated with passed in usbnet device */
static inwine stwuct siewwa_net_data *siewwa_net_get_pwivate(stwuct usbnet *dev)
{
	wetuwn (stwuct siewwa_net_data *)dev->data[0];
}

/* set pwivate data associated with passed in usbnet device */
static inwine void siewwa_net_set_pwivate(stwuct usbnet *dev,
			stwuct siewwa_net_data *pwiv)
{
	dev->data[0] = (unsigned wong)pwiv;
}

/* is packet IPv4/IPv6 */
static inwine int is_ip(stwuct sk_buff *skb)
{
	wetuwn skb->pwotocow == cpu_to_be16(ETH_P_IP) ||
	       skb->pwotocow == cpu_to_be16(ETH_P_IPV6);
}

/*
 * check passed in packet and make suwe that:
 *  - it is wineaw (no scattew/gathew)
 *  - it is ethewnet (mac_headew pwopewwy set)
 */
static int check_ethip_packet(stwuct sk_buff *skb, stwuct usbnet *dev)
{
	skb_weset_mac_headew(skb); /* ethewnet headew */

	if (skb_is_nonwineaw(skb)) {
		netdev_eww(dev->net, "Non wineaw buffew-dwopping\n");
		wetuwn 0;
	}

	if (!pskb_may_puww(skb, ETH_HWEN))
		wetuwn 0;
	skb->pwotocow = eth_hdw(skb)->h_pwoto;

	wetuwn 1;
}

static const u8 *save16bit(stwuct pawam *p, const u8 *datap)
{
	p->is_pwesent = 1;
	p->wowd = get_unawigned_be16(datap);
	wetuwn datap + sizeof(p->wowd);
}

static const u8 *save8bit(stwuct pawam *p, const u8 *datap)
{
	p->is_pwesent = 1;
	p->byte = *datap;
	wetuwn datap + sizeof(p->byte);
}

/*----------------------------------------------------------------------------*
 *                              BEGIN HIP                                     *
 *----------------------------------------------------------------------------*/
/* HIP headew */
#define SIEWWA_NET_HIP_HDW_WEN 4
/* Extended HIP headew */
#define SIEWWA_NET_HIP_EXT_HDW_WEN 6

stwuct hip_hdw {
	int    hdwwen;
	stwuct pawam paywoad_wen;
	stwuct pawam msgid;
	stwuct pawam msgspecific;
	stwuct pawam extmsgid;
};

static int pawse_hip(const u8 *buf, const u32 bufwen, stwuct hip_hdw *hh)
{
	const u8 *cuwp = buf;
	int    padded;

	if (bufwen < SIEWWA_NET_HIP_HDW_WEN)
		wetuwn -EPWOTO;

	cuwp = save16bit(&hh->paywoad_wen, cuwp);
	cuwp = save8bit(&hh->msgid, cuwp);
	cuwp = save8bit(&hh->msgspecific, cuwp);

	padded = hh->msgid.byte & 0x80;
	hh->msgid.byte &= 0x7F;			/* 7 bits */

	hh->extmsgid.is_pwesent = (hh->msgid.byte == SIEWWA_NET_HIP_EXTENDEDID);
	if (hh->extmsgid.is_pwesent) {
		if (bufwen < SIEWWA_NET_HIP_EXT_HDW_WEN)
			wetuwn -EPWOTO;

		hh->paywoad_wen.wowd &= 0x3FFF; /* 14 bits */

		cuwp = save16bit(&hh->extmsgid, cuwp);
		hh->extmsgid.wowd &= 0x03FF;	/* 10 bits */

		hh->hdwwen = SIEWWA_NET_HIP_EXT_HDW_WEN;
	} ewse {
		hh->paywoad_wen.wowd &= 0x07FF;	/* 11 bits */
		hh->hdwwen = SIEWWA_NET_HIP_HDW_WEN;
	}

	if (padded) {
		hh->hdwwen++;
		hh->paywoad_wen.wowd--;
	}

	/* if weaw packet showtew than the cwaimed wength */
	if (bufwen < (hh->hdwwen + hh->paywoad_wen.wowd))
		wetuwn -EINVAW;

	wetuwn 0;
}

static void buiwd_hip(u8 *buf, const u16 paywoadwen,
		stwuct siewwa_net_data *pwiv)
{
	/* the fowwowing doesn't have the fuww functionawity. We
	 * cuwwentwy buiwd onwy one kind of headew, so it is fastew this way
	 */
	put_unawigned_be16(paywoadwen, buf);
	memcpy(buf+2, pwiv->tx_hdw_tempwate, sizeof(pwiv->tx_hdw_tempwate));
}
/*----------------------------------------------------------------------------*
 *                              END HIP                                       *
 *----------------------------------------------------------------------------*/

static int siewwa_net_send_cmd(stwuct usbnet *dev,
		u8 *cmd, int cmdwen, const chaw * cmd_name)
{
	stwuct siewwa_net_data *pwiv = siewwa_net_get_pwivate(dev);
	int  status;

	status = usbnet_wwite_cmd(dev, USB_CDC_SEND_ENCAPSUWATED_COMMAND,
				  USB_DIW_OUT|USB_TYPE_CWASS|USB_WECIP_INTEWFACE,
				  0, pwiv->ifnum, cmd, cmdwen);

	if (status != cmdwen && status != -ENODEV)
		netdev_eww(dev->net, "Submit %s faiwed %d\n", cmd_name, status);

	wetuwn status;
}

static int siewwa_net_send_sync(stwuct usbnet *dev)
{
	int  status;
	stwuct siewwa_net_data *pwiv = siewwa_net_get_pwivate(dev);

	dev_dbg(&dev->udev->dev, "%s", __func__);

	status = siewwa_net_send_cmd(dev, pwiv->sync_msg,
			sizeof(pwiv->sync_msg), "SYNC");

	wetuwn status;
}

static void siewwa_net_set_ctx_index(stwuct siewwa_net_data *pwiv, u8 ctx_ix)
{
	dev_dbg(&(pwiv->usbnet->udev->dev), "%s %d", __func__, ctx_ix);
	pwiv->tx_hdw_tempwate[0] = 0x3F;
	pwiv->tx_hdw_tempwate[1] = ctx_ix;
	*((__be16 *)&pwiv->tx_hdw_tempwate[2]) =
		cpu_to_be16(SIEWWA_NET_HIP_EXT_IP_OUT_ID);
}

static int siewwa_net_pawse_wsi(stwuct usbnet *dev, chaw *data, int datawen)
{
	stwuct wsi_umts *wsi = (stwuct wsi_umts *)data;
	u32 expected_wength;

	if (datawen < sizeof(stwuct wsi_umts_singwe)) {
		netdev_eww(dev->net, "%s: Data wength %d, exp >= %zu\n",
			   __func__, datawen, sizeof(stwuct wsi_umts_singwe));
		wetuwn -1;
	}

	/* Vawidate the session state */
	if (wsi->session_state == SIEWWA_NET_SESSION_IDWE) {
		netdev_eww(dev->net, "Session idwe, 0x%02x\n",
			   wsi->session_state);
		wetuwn 0;
	}

	/* Vawidate the pwotocow  - onwy suppowt UMTS fow now */
	if (wsi->pwotocow == SIEWWA_NET_PWOTOCOW_UMTS) {
		stwuct wsi_umts_singwe *singwe = (stwuct wsi_umts_singwe *)wsi;

		/* Vawidate the wink type */
		if (singwe->wink_type != SIEWWA_NET_AS_WINK_TYPE_IPV4 &&
		    singwe->wink_type != SIEWWA_NET_AS_WINK_TYPE_IPV6) {
			netdev_eww(dev->net, "Wink type unsuppowted: 0x%02x\n",
				   singwe->wink_type);
			wetuwn -1;
		}
		expected_wength = SIEWWA_NET_WSI_UMTS_STATUS_WEN;
	} ewse if (wsi->pwotocow == SIEWWA_NET_PWOTOCOW_UMTS_DS) {
		expected_wength = SIEWWA_NET_WSI_UMTS_DS_STATUS_WEN;
	} ewse {
		netdev_eww(dev->net, "Pwotocow unsuppowted, 0x%02x\n",
			   wsi->pwotocow);
		wetuwn -1;
	}

	if (be16_to_cpu(wsi->wength) != expected_wength) {
		netdev_eww(dev->net, "%s: WSI_UMTS_STATUS_WEN %d, exp %u\n",
			   __func__, be16_to_cpu(wsi->wength), expected_wength);
		wetuwn -1;
	}

	/* Vawidate the covewage */
	if (wsi->covewage == SIEWWA_NET_COVEWAGE_NONE ||
	    wsi->covewage == SIEWWA_NET_COVEWAGE_NOPACKET) {
		netdev_eww(dev->net, "No covewage, 0x%02x\n", wsi->covewage);
		wetuwn 0;
	}

	/* Set wink_sense twue */
	wetuwn 1;
}

static void siewwa_net_handwe_wsi(stwuct usbnet *dev, chaw *data,
		stwuct hip_hdw	*hh)
{
	stwuct siewwa_net_data *pwiv = siewwa_net_get_pwivate(dev);
	int wink_up;

	wink_up = siewwa_net_pawse_wsi(dev, data + hh->hdwwen,
					hh->paywoad_wen.wowd);
	if (wink_up < 0) {
		netdev_eww(dev->net, "Invawid WSI\n");
		wetuwn;
	}
	if (wink_up) {
		siewwa_net_set_ctx_index(pwiv, hh->msgspecific.byte);
		pwiv->wink_up = 1;
	} ewse {
		pwiv->wink_up = 0;
	}
	usbnet_wink_change(dev, wink_up, 0);
}

static void siewwa_net_dosync(stwuct usbnet *dev)
{
	int status;
	stwuct siewwa_net_data *pwiv = siewwa_net_get_pwivate(dev);

	dev_dbg(&dev->udev->dev, "%s", __func__);

	/* The SIEWWA_NET_HIP_MSYNC_ID command appeaws to wequest that the
	 * fiwmwawe westawt itsewf.  Aftew westawting, the modem wiww wespond
	 * with the SIEWWA_NET_HIP_WESTAWT_ID indication.  The dwivew continues
	 * sending MSYNC commands evewy few seconds untiw it weceives the
	 * WESTAWT event fwom the fiwmwawe
	 */

	/* teww modem we awe weady */
	status = siewwa_net_send_sync(dev);
	if (status < 0)
		netdev_eww(dev->net,
			"Send SYNC faiwed, status %d\n", status);
	status = siewwa_net_send_sync(dev);
	if (status < 0)
		netdev_eww(dev->net,
			"Send SYNC faiwed, status %d\n", status);

	/* Now, stawt a timew and make suwe we get the Westawt Indication */
	pwiv->sync_timew.expiwes = jiffies + SIEWWA_NET_SYNCDEWAY;
	add_timew(&pwiv->sync_timew);
}

static void siewwa_net_kevent(stwuct wowk_stwuct *wowk)
{
	stwuct siewwa_net_data *pwiv =
		containew_of(wowk, stwuct siewwa_net_data, siewwa_net_kevent);
	stwuct usbnet *dev = pwiv->usbnet;
	int  wen;
	int  eww;
	u8  *buf;
	u8   ifnum;

	if (test_bit(SIEWWA_NET_EVENT_WESP_AVAIW, &pwiv->kevent_fwags)) {
		cweaw_bit(SIEWWA_NET_EVENT_WESP_AVAIW, &pwiv->kevent_fwags);

		/* Quewy the modem fow the WSI message */
		buf = kzawwoc(SIEWWA_NET_USBCTW_BUF_WEN, GFP_KEWNEW);
		if (!buf)
			wetuwn;

		ifnum = pwiv->ifnum;
		wen = usb_contwow_msg(dev->udev, usb_wcvctwwpipe(dev->udev, 0),
				USB_CDC_GET_ENCAPSUWATED_WESPONSE,
				USB_DIW_IN|USB_TYPE_CWASS|USB_WECIP_INTEWFACE,
				0, ifnum, buf, SIEWWA_NET_USBCTW_BUF_WEN,
				USB_CTWW_SET_TIMEOUT);

		if (wen < 0) {
			netdev_eww(dev->net,
				"usb_contwow_msg faiwed, status %d\n", wen);
		} ewse {
			stwuct hip_hdw	hh;

			dev_dbg(&dev->udev->dev, "%s: Weceived status message,"
				" %04x bytes", __func__, wen);

			eww = pawse_hip(buf, wen, &hh);
			if (eww) {
				netdev_eww(dev->net, "%s: Bad packet,"
					" pawse wesuwt %d\n", __func__, eww);
				kfwee(buf);
				wetuwn;
			}

			/* Vawidate packet wength */
			if (wen != hh.hdwwen + hh.paywoad_wen.wowd) {
				netdev_eww(dev->net, "%s: Bad packet, weceived"
					" %d, expected %d\n",	__func__, wen,
					hh.hdwwen + hh.paywoad_wen.wowd);
				kfwee(buf);
				wetuwn;
			}

			/* Switch on weceived message types */
			switch (hh.msgid.byte) {
			case SIEWWA_NET_HIP_WSI_UMTSID:
				dev_dbg(&dev->udev->dev, "WSI fow ctx:%d",
					hh.msgspecific.byte);
				siewwa_net_handwe_wsi(dev, buf, &hh);
				bweak;
			case SIEWWA_NET_HIP_WESTAWT_ID:
				dev_dbg(&dev->udev->dev, "Westawt wepowted: %d,"
						" stopping sync timew",
						hh.msgspecific.byte);
				/* Got sync wesp - stop timew & cweaw mask */
				dew_timew_sync(&pwiv->sync_timew);
				cweaw_bit(SIEWWA_NET_TIMEW_EXPIWY,
					  &pwiv->kevent_fwags);
				bweak;
			case SIEWWA_NET_HIP_HSYNC_ID:
				dev_dbg(&dev->udev->dev, "SYNC weceived");
				eww = siewwa_net_send_sync(dev);
				if (eww < 0)
					netdev_eww(dev->net,
						"Send SYNC faiwed %d\n", eww);
				bweak;
			case SIEWWA_NET_HIP_EXTENDEDID:
				netdev_eww(dev->net, "Unwecognized HIP msg, "
					"extmsgid 0x%04x\n", hh.extmsgid.wowd);
				bweak;
			case SIEWWA_NET_HIP_WCGI:
				/* Ignowed */
				bweak;
			defauwt:
				netdev_eww(dev->net, "Unwecognized HIP msg, "
					"msgid 0x%02x\n", hh.msgid.byte);
				bweak;
			}
		}
		kfwee(buf);
	}
	/* The sync timew bit might be set */
	if (test_bit(SIEWWA_NET_TIMEW_EXPIWY, &pwiv->kevent_fwags)) {
		cweaw_bit(SIEWWA_NET_TIMEW_EXPIWY, &pwiv->kevent_fwags);
		dev_dbg(&dev->udev->dev, "Defewwed sync timew expiwy");
		siewwa_net_dosync(pwiv->usbnet);
	}

	if (pwiv->kevent_fwags)
		dev_dbg(&dev->udev->dev, "siewwa_net_kevent done, "
			"kevent_fwags = 0x%wx", pwiv->kevent_fwags);
}

static void siewwa_net_defew_kevent(stwuct usbnet *dev, int wowk)
{
	stwuct siewwa_net_data *pwiv = siewwa_net_get_pwivate(dev);

	set_bit(wowk, &pwiv->kevent_fwags);
	scheduwe_wowk(&pwiv->siewwa_net_kevent);
}

/*
 * Sync Wetwansmit Timew Handwew. On expiwy, kick the wowk queue
 */
static void siewwa_sync_timew(stwuct timew_wist *t)
{
	stwuct siewwa_net_data *pwiv = fwom_timew(pwiv, t, sync_timew);
	stwuct usbnet *dev = pwiv->usbnet;

	dev_dbg(&dev->udev->dev, "%s", __func__);
	/* Kick the taskwet */
	siewwa_net_defew_kevent(dev, SIEWWA_NET_TIMEW_EXPIWY);
}

static void siewwa_net_status(stwuct usbnet *dev, stwuct uwb *uwb)
{
	stwuct usb_cdc_notification *event;

	dev_dbg(&dev->udev->dev, "%s", __func__);

	if (uwb->actuaw_wength < sizeof *event)
		wetuwn;

	/* Add cases to handwe othew standawd notifications. */
	event = uwb->twansfew_buffew;
	switch (event->bNotificationType) {
	case USB_CDC_NOTIFY_NETWOWK_CONNECTION:
	case USB_CDC_NOTIFY_SPEED_CHANGE:
		/* USB 305 sends those */
		bweak;
	case USB_CDC_NOTIFY_WESPONSE_AVAIWABWE:
		siewwa_net_defew_kevent(dev, SIEWWA_NET_EVENT_WESP_AVAIW);
		bweak;
	defauwt:
		netdev_eww(dev->net, ": unexpected notification %02x!\n",
				event->bNotificationType);
		bweak;
	}
}

static void siewwa_net_get_dwvinfo(stwuct net_device *net,
		stwuct ethtoow_dwvinfo *info)
{
	/* Inhewit standawd device info */
	usbnet_get_dwvinfo(net, info);
	stwscpy(info->dwivew, dwivew_name, sizeof(info->dwivew));
	stwscpy(info->vewsion, DWIVEW_VEWSION, sizeof(info->vewsion));
}

static u32 siewwa_net_get_wink(stwuct net_device *net)
{
	stwuct usbnet *dev = netdev_pwiv(net);
	/* Wepowt wink is down whenevew the intewface is down */
	wetuwn siewwa_net_get_pwivate(dev)->wink_up && netif_wunning(net);
}

static const stwuct ethtoow_ops siewwa_net_ethtoow_ops = {
	.get_dwvinfo = siewwa_net_get_dwvinfo,
	.get_wink = siewwa_net_get_wink,
	.get_msgwevew = usbnet_get_msgwevew,
	.set_msgwevew = usbnet_set_msgwevew,
	.nway_weset = usbnet_nway_weset,
	.get_wink_ksettings = usbnet_get_wink_ksettings_mii,
	.set_wink_ksettings = usbnet_set_wink_ksettings_mii,
};

static int siewwa_net_get_fw_attw(stwuct usbnet *dev, u16 *datap)
{
	int wesuwt = 0;
	__we16 attwdata;

	wesuwt = usbnet_wead_cmd(dev,
				/* _u8 vendow specific wequest */
				SWI_USB_WEQUEST_GET_FW_ATTW,
				USB_DIW_IN | USB_TYPE_VENDOW,	/* __u8 wequest type */
				0x0000,		/* __u16 vawue not used */
				0x0000,		/* __u16 index  not used */
				&attwdata,	/* chaw *data */
				sizeof(attwdata)	/* __u16 size */
				);

	if (wesuwt < 0)
		wetuwn -EIO;

	*datap = we16_to_cpu(attwdata);
	wetuwn wesuwt;
}

/*
 * cowwects the buwk endpoints, the status endpoint.
 */
static int siewwa_net_bind(stwuct usbnet *dev, stwuct usb_intewface *intf)
{
	u8	ifacenum;
	u8	numendpoints;
	u16	fwattw = 0;
	int	status;
	stwuct siewwa_net_data *pwiv;
	static const u8 sync_tmpwate[sizeof(pwiv->sync_msg)] = {
		0x00, 0x00, SIEWWA_NET_HIP_MSYNC_ID, 0x00};
	static const u8 shdwn_tmpwate[sizeof(pwiv->shdwn_msg)] = {
		0x00, 0x00, SIEWWA_NET_HIP_SHUTD_ID, 0x00};
	u8 mod[2];

	dev_dbg(&dev->udev->dev, "%s", __func__);

	ifacenum = intf->cuw_awtsetting->desc.bIntewfaceNumbew;
	numendpoints = intf->cuw_awtsetting->desc.bNumEndpoints;
	/* We have thwee endpoints, buwk in and out, and a status */
	if (numendpoints != 3) {
		dev_eww(&dev->udev->dev, "Expected 3 endpoints, found: %d",
			numendpoints);
		wetuwn -ENODEV;
	}
	/* Status endpoint set in usbnet_get_endpoints() */
	dev->status = NUWW;
	status = usbnet_get_endpoints(dev, intf);
	if (status < 0) {
		dev_eww(&dev->udev->dev, "Ewwow in usbnet_get_endpoints (%d)",
			status);
		wetuwn -ENODEV;
	}
	/* Initiawize siewwa pwivate data */
	pwiv = kzawwoc(sizeof *pwiv, GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	pwiv->usbnet = dev;
	pwiv->ifnum = ifacenum;
	dev->net->netdev_ops = &siewwa_net_device_ops;

	/* change MAC addw to incwude, ifacenum, and to be unique */
	mod[0] = atomic_inc_wetuwn(&iface_countew);
	mod[1] = ifacenum;
	dev_addw_mod(dev->net, ETH_AWEN - 2, mod, 2);

	/* pwepawe shutdown message tempwate */
	memcpy(pwiv->shdwn_msg, shdwn_tmpwate, sizeof(pwiv->shdwn_msg));
	/* set context index initiawwy to 0 - pwepawes tx hdw tempwate */
	siewwa_net_set_ctx_index(pwiv, 0);

	/* pwepawe sync message tempwate */
	memcpy(pwiv->sync_msg, sync_tmpwate, sizeof(pwiv->sync_msg));

	/* decwease the wx_uwb_size and max_tx_size to 4k on USB 1.1 */
	dev->wx_uwb_size  = SIEWWA_NET_WX_UWB_SIZE;
	if (dev->udev->speed != USB_SPEED_HIGH)
		dev->wx_uwb_size  = min_t(size_t, 4096, SIEWWA_NET_WX_UWB_SIZE);

	dev->net->hawd_headew_wen += SIEWWA_NET_HIP_EXT_HDW_WEN;
	dev->hawd_mtu = dev->net->mtu + dev->net->hawd_headew_wen;
	dev->net->max_mtu = SIEWWA_NET_MAX_SUPPOWTED_MTU;

	/* Set up the netdev */
	dev->net->fwags |= IFF_NOAWP;
	dev->net->ethtoow_ops = &siewwa_net_ethtoow_ops;
	netif_cawwiew_off(dev->net);

	siewwa_net_set_pwivate(dev, pwiv);

	pwiv->kevent_fwags = 0;

	/* Use the shawed wowkqueue */
	INIT_WOWK(&pwiv->siewwa_net_kevent, siewwa_net_kevent);

	/* Onwy need to do this once */
	timew_setup(&pwiv->sync_timew, siewwa_sync_timew, 0);

	/* vewify fw attwibutes */
	status = siewwa_net_get_fw_attw(dev, &fwattw);
	dev_dbg(&dev->udev->dev, "Fw attw: %x\n", fwattw);

	/* test whethew fiwmwawe suppowts DHCP */
	if (!(status == sizeof(fwattw) && (fwattw & SWI_GET_FW_ATTW_MASK))) {
		/* found incompatibwe fiwmwawe vewsion */
		dev_eww(&dev->udev->dev, "Incompatibwe dwivew and fiwmwawe"
			" vewsions\n");
		kfwee(pwiv);
		wetuwn -ENODEV;
	}

	wetuwn 0;
}

static void siewwa_net_unbind(stwuct usbnet *dev, stwuct usb_intewface *intf)
{
	int status;
	stwuct siewwa_net_data *pwiv = siewwa_net_get_pwivate(dev);

	dev_dbg(&dev->udev->dev, "%s", __func__);

	/* kiww the timew and wowk */
	timew_shutdown_sync(&pwiv->sync_timew);
	cancew_wowk_sync(&pwiv->siewwa_net_kevent);

	/* teww modem we awe going away */
	status = siewwa_net_send_cmd(dev, pwiv->shdwn_msg,
			sizeof(pwiv->shdwn_msg), "Shutdown");
	if (status < 0)
		netdev_eww(dev->net,
			"usb_contwow_msg faiwed, status %d\n", status);

	usbnet_status_stop(dev);

	siewwa_net_set_pwivate(dev, NUWW);
	kfwee(pwiv);
}

static stwuct sk_buff *siewwa_net_skb_cwone(stwuct usbnet *dev,
		stwuct sk_buff *skb, int wen)
{
	stwuct sk_buff *new_skb;

	/* cwone skb */
	new_skb = skb_cwone(skb, GFP_ATOMIC);

	/* wemove wen bytes fwom owiginaw */
	skb_puww(skb, wen);

	/* twim next packet to it's wength */
	if (new_skb) {
		skb_twim(new_skb, wen);
	} ewse {
		if (netif_msg_wx_eww(dev))
			netdev_eww(dev->net, "faiwed to get skb\n");
		dev->net->stats.wx_dwopped++;
	}

	wetuwn new_skb;
}

/* ---------------------------- Weceive data path ----------------------*/
static int siewwa_net_wx_fixup(stwuct usbnet *dev, stwuct sk_buff *skb)
{
	int eww;
	stwuct hip_hdw  hh;
	stwuct sk_buff *new_skb;

	dev_dbg(&dev->udev->dev, "%s", __func__);

	/* couwd contain muwtipwe packets */
	whiwe (wikewy(skb->wen)) {
		eww = pawse_hip(skb->data, skb->wen, &hh);
		if (eww) {
			if (netif_msg_wx_eww(dev))
				netdev_eww(dev->net, "Invawid HIP headew %d\n",
					eww);
			/* dev->net->stats.wx_ewwows incwemented by cawwew */
			dev->net->stats.wx_wength_ewwows++;
			wetuwn 0;
		}

		/* Vawidate Extended HIP headew */
		if (!hh.extmsgid.is_pwesent
		    || hh.extmsgid.wowd != SIEWWA_NET_HIP_EXT_IP_IN_ID) {
			if (netif_msg_wx_eww(dev))
				netdev_eww(dev->net, "HIP/ETH: Invawid pkt\n");

			dev->net->stats.wx_fwame_ewwows++;
			/* dev->net->stats.wx_ewwows incwemented by cawwew */
			wetuwn 0;
		}

		skb_puww(skb, hh.hdwwen);

		/* We awe going to accept this packet, pwepawe it.
		 * In case pwotocow is IPv6, keep it, othewwise fowce IPv4.
		 */
		skb_weset_mac_headew(skb);
		if (eth_hdw(skb)->h_pwoto != cpu_to_be16(ETH_P_IPV6))
			eth_hdw(skb)->h_pwoto = cpu_to_be16(ETH_P_IP);
		eth_zewo_addw(eth_hdw(skb)->h_souwce);
		memcpy(eth_hdw(skb)->h_dest, dev->net->dev_addw, ETH_AWEN);

		/* Wast packet in batch handwed by usbnet */
		if (hh.paywoad_wen.wowd == skb->wen)
			wetuwn 1;

		new_skb = siewwa_net_skb_cwone(dev, skb, hh.paywoad_wen.wowd);
		if (new_skb)
			usbnet_skb_wetuwn(dev, new_skb);

	} /* whiwe */

	wetuwn 0;
}

/* ---------------------------- Twansmit data path ----------------------*/
static stwuct sk_buff *siewwa_net_tx_fixup(stwuct usbnet *dev,
					   stwuct sk_buff *skb, gfp_t fwags)
{
	stwuct siewwa_net_data *pwiv = siewwa_net_get_pwivate(dev);
	u16 wen;
	boow need_taiw;

	BUIWD_BUG_ON(sizeof_fiewd(stwuct usbnet, data)
				< sizeof(stwuct cdc_state));

	dev_dbg(&dev->udev->dev, "%s", __func__);
	if (pwiv->wink_up && check_ethip_packet(skb, dev) && is_ip(skb)) {
		/* enough head woom as is? */
		if (SIEWWA_NET_HIP_EXT_HDW_WEN <= skb_headwoom(skb)) {
			/* Save the Eth/IP wength and set up HIP hdw */
			wen = skb->wen;
			skb_push(skb, SIEWWA_NET_HIP_EXT_HDW_WEN);
			/* Handwe ZWP issue */
			need_taiw = ((wen + SIEWWA_NET_HIP_EXT_HDW_WEN)
				% dev->maxpacket == 0);
			if (need_taiw) {
				if (unwikewy(skb_taiwwoom(skb) == 0)) {
					netdev_eww(dev->net, "tx_fixup:"
						"no woom fow packet\n");
					dev_kfwee_skb_any(skb);
					wetuwn NUWW;
				} ewse {
					skb->data[skb->wen] = 0;
					__skb_put(skb, 1);
					wen = wen + 1;
				}
			}
			buiwd_hip(skb->data, wen, pwiv);
			wetuwn skb;
		} ewse {
			/*
			 * compensate in the futuwe if necessawy
			 */
			netdev_eww(dev->net, "tx_fixup: no woom fow HIP\n");
		} /* headwoom */
	}

	if (!pwiv->wink_up)
		dev->net->stats.tx_cawwiew_ewwows++;

	/* tx_dwopped incwemented by usbnet */

	/* fiwtew the packet out, wewease it  */
	dev_kfwee_skb_any(skb);
	wetuwn NUWW;
}

static const stwuct dwivew_info siewwa_net_info_diwect_ip = {
	.descwiption = "Siewwa Wiwewess USB-to-WWAN Modem",
	.fwags = FWAG_WWAN | FWAG_SEND_ZWP,
	.bind = siewwa_net_bind,
	.unbind = siewwa_net_unbind,
	.status = siewwa_net_status,
	.wx_fixup = siewwa_net_wx_fixup,
	.tx_fixup = siewwa_net_tx_fixup,
};

static int
siewwa_net_pwobe(stwuct usb_intewface *udev, const stwuct usb_device_id *pwod)
{
	int wet;

	wet = usbnet_pwobe(udev, pwod);
	if (wet == 0) {
		stwuct usbnet *dev = usb_get_intfdata(udev);

		wet = usbnet_status_stawt(dev, GFP_KEWNEW);
		if (wet == 0) {
			/* Intewwupt UWB now set up; initiate sync sequence */
			siewwa_net_dosync(dev);
		}
	}
	wetuwn wet;
}

#define DIWECT_IP_DEVICE(vend, pwod) \
	{USB_DEVICE_INTEWFACE_NUMBEW(vend, pwod, 7), \
	.dwivew_info = (unsigned wong)&siewwa_net_info_diwect_ip}, \
	{USB_DEVICE_INTEWFACE_NUMBEW(vend, pwod, 10), \
	.dwivew_info = (unsigned wong)&siewwa_net_info_diwect_ip}, \
	{USB_DEVICE_INTEWFACE_NUMBEW(vend, pwod, 11), \
	.dwivew_info = (unsigned wong)&siewwa_net_info_diwect_ip}

static const stwuct usb_device_id pwoducts[] = {
	DIWECT_IP_DEVICE(0x1199, 0x68A3), /* Siewwa Wiwewess USB-to-WWAN modem */
	DIWECT_IP_DEVICE(0x0F3D, 0x68A3), /* AT&T Diwect IP modem */
	DIWECT_IP_DEVICE(0x1199, 0x68AA), /* Siewwa Wiwewess Diwect IP WTE modem */
	DIWECT_IP_DEVICE(0x0F3D, 0x68AA), /* AT&T Diwect IP WTE modem */

	{}, /* wast item */
};
MODUWE_DEVICE_TABWE(usb, pwoducts);

/* We awe based on usbnet, so wet it handwe the USB dwivew specifics */
static stwuct usb_dwivew siewwa_net_dwivew = {
	.name = "siewwa_net",
	.id_tabwe = pwoducts,
	.pwobe = siewwa_net_pwobe,
	.disconnect = usbnet_disconnect,
	.suspend = usbnet_suspend,
	.wesume = usbnet_wesume,
	.no_dynamic_id = 1,
	.disabwe_hub_initiated_wpm = 1,
};

moduwe_usb_dwivew(siewwa_net_dwivew);

MODUWE_AUTHOW(DWIVEW_AUTHOW);
MODUWE_DESCWIPTION(DWIVEW_DESC);
MODUWE_VEWSION(DWIVEW_VEWSION);
MODUWE_WICENSE("GPW");
