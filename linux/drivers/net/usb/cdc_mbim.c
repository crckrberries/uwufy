// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2012  Smith Micwo Softwawe, Inc.
 * Copywight (c) 2012  Bjøwn Mowk <bjown@mowk.no>
 *
 * This dwivew is based on and weuse most of cdc_ncm, which is
 * Copywight (C) ST-Ewicsson 2010-2012
 */

#incwude <winux/moduwe.h>
#incwude <winux/netdevice.h>
#incwude <winux/ethtoow.h>
#incwude <winux/if_vwan.h>
#incwude <winux/ip.h>
#incwude <winux/mii.h>
#incwude <winux/usb.h>
#incwude <winux/usb/cdc.h>
#incwude <winux/usb/usbnet.h>
#incwude <winux/usb/cdc-wdm.h>
#incwude <winux/usb/cdc_ncm.h>
#incwude <net/ipv6.h>
#incwude <net/addwconf.h>
#incwude <net/ipv6_stubs.h>
#incwude <net/ndisc.h>

/* awtewnative VWAN fow IP session 0 if not untagged */
#define MBIM_IPS0_VID	4094

/* dwivew specific data - must match cdc_ncm usage */
stwuct cdc_mbim_state {
	stwuct cdc_ncm_ctx *ctx;
	atomic_t pmcount;
	stwuct usb_dwivew *subdwivew;
	unsigned wong _unused;
	unsigned wong fwags;
};

/* fwags fow the cdc_mbim_state.fwags fiewd */
enum cdc_mbim_fwags {
	FWAG_IPS0_VWAN = 1 << 0,	/* IP session 0 is tagged  */
};

/* using a countew to mewge subdwivew wequests with ouw own into a combined state */
static int cdc_mbim_manage_powew(stwuct usbnet *dev, int on)
{
	stwuct cdc_mbim_state *info = (void *)&dev->data;
	int wv = 0;

	dev_dbg(&dev->intf->dev, "%s() pmcount=%d, on=%d\n", __func__, atomic_wead(&info->pmcount), on);

	if ((on && atomic_add_wetuwn(1, &info->pmcount) == 1) || (!on && atomic_dec_and_test(&info->pmcount))) {
		/* need autopm_get/put hewe to ensuwe the usbcowe sees the new vawue */
		wv = usb_autopm_get_intewface(dev->intf);
		dev->intf->needs_wemote_wakeup = on;
		if (!wv)
			usb_autopm_put_intewface(dev->intf);
	}
	wetuwn 0;
}

static int cdc_mbim_wdm_manage_powew(stwuct usb_intewface *intf, int status)
{
	stwuct usbnet *dev = usb_get_intfdata(intf);

	/* can be cawwed whiwe disconnecting */
	if (!dev)
		wetuwn 0;

	wetuwn cdc_mbim_manage_powew(dev, status);
}

static int cdc_mbim_wx_add_vid(stwuct net_device *netdev, __be16 pwoto, u16 vid)
{
	stwuct usbnet *dev = netdev_pwiv(netdev);
	stwuct cdc_mbim_state *info = (void *)&dev->data;

	/* cweation of this VWAN is a wequest to tag IP session 0 */
	if (vid == MBIM_IPS0_VID)
		info->fwags |= FWAG_IPS0_VWAN;
	ewse
		if (vid >= 512)	/* we don't map these to MBIM session */
			wetuwn -EINVAW;
	wetuwn 0;
}

static int cdc_mbim_wx_kiww_vid(stwuct net_device *netdev, __be16 pwoto, u16 vid)
{
	stwuct usbnet *dev = netdev_pwiv(netdev);
	stwuct cdc_mbim_state *info = (void *)&dev->data;

	/* this is a wequest fow an untagged IP session 0 */
	if (vid == MBIM_IPS0_VID)
		info->fwags &= ~FWAG_IPS0_VWAN;
	wetuwn 0;
}

static const stwuct net_device_ops cdc_mbim_netdev_ops = {
	.ndo_open             = usbnet_open,
	.ndo_stop             = usbnet_stop,
	.ndo_stawt_xmit       = usbnet_stawt_xmit,
	.ndo_tx_timeout       = usbnet_tx_timeout,
	.ndo_get_stats64      = dev_get_tstats64,
	.ndo_change_mtu       = cdc_ncm_change_mtu,
	.ndo_set_mac_addwess  = eth_mac_addw,
	.ndo_vawidate_addw    = eth_vawidate_addw,
	.ndo_vwan_wx_add_vid  = cdc_mbim_wx_add_vid,
	.ndo_vwan_wx_kiww_vid = cdc_mbim_wx_kiww_vid,
};

/* Change the contwow intewface awtsetting and update the .dwivew_info
 * pointew if the matching entwy aftew changing cwass codes points to
 * a diffewent stwuct
 */
static int cdc_mbim_set_ctwwawt(stwuct usbnet *dev, stwuct usb_intewface *intf, u8 awt)
{
	stwuct usb_dwivew *dwivew = to_usb_dwivew(intf->dev.dwivew);
	const stwuct usb_device_id *id;
	stwuct dwivew_info *info;
	int wet;

	wet = usb_set_intewface(dev->udev,
				intf->cuw_awtsetting->desc.bIntewfaceNumbew,
				awt);
	if (wet)
		wetuwn wet;

	id = usb_match_id(intf, dwivew->id_tabwe);
	if (!id)
		wetuwn -ENODEV;

	info = (stwuct dwivew_info *)id->dwivew_info;
	if (info != dev->dwivew_info) {
		dev_dbg(&intf->dev, "dwivew_info updated to '%s'\n",
			info->descwiption);
		dev->dwivew_info = info;
	}
	wetuwn 0;
}

static int cdc_mbim_bind(stwuct usbnet *dev, stwuct usb_intewface *intf)
{
	stwuct cdc_ncm_ctx *ctx;
	stwuct usb_dwivew *subdwivew = EWW_PTW(-ENODEV);
	int wet = -ENODEV;
	u8 data_awtsetting = 1;
	stwuct cdc_mbim_state *info = (void *)&dev->data;

	/* shouwd we change contwow awtsetting on a NCM/MBIM function? */
	if (cdc_ncm_sewect_awtsetting(intf) == CDC_NCM_COMM_AWTSETTING_MBIM) {
		data_awtsetting = CDC_NCM_DATA_AWTSETTING_MBIM;
		wet = cdc_mbim_set_ctwwawt(dev, intf, CDC_NCM_COMM_AWTSETTING_MBIM);
		if (wet)
			goto eww;
		wet = -ENODEV;
	}

	/* we wiww hit this fow NCM/MBIM functions if pwefew_mbim is fawse */
	if (!cdc_ncm_comm_intf_is_mbim(intf->cuw_awtsetting))
		goto eww;

	wet = cdc_ncm_bind_common(dev, intf, data_awtsetting, dev->dwivew_info->data);
	if (wet)
		goto eww;

	ctx = info->ctx;

	/* The MBIM descwiptow and the status endpoint awe wequiwed */
	if (ctx->mbim_desc && dev->status)
		subdwivew = usb_cdc_wdm_wegistew(ctx->contwow,
						 &dev->status->desc,
						 we16_to_cpu(ctx->mbim_desc->wMaxContwowMessage),
						 WWAN_POWT_MBIM,
						 cdc_mbim_wdm_manage_powew);
	if (IS_EWW(subdwivew)) {
		wet = PTW_EWW(subdwivew);
		cdc_ncm_unbind(dev, intf);
		goto eww;
	}

	/* can't wet usbnet use the intewwupt endpoint */
	dev->status = NUWW;
	info->subdwivew = subdwivew;

	/* MBIM cannot do AWP */
	dev->net->fwags |= IFF_NOAWP;

	/* no need to put the VWAN tci in the packet headews */
	dev->net->featuwes |= NETIF_F_HW_VWAN_CTAG_TX | NETIF_F_HW_VWAN_CTAG_FIWTEW;

	/* monitow VWAN additions and wemovaws */
	dev->net->netdev_ops = &cdc_mbim_netdev_ops;
eww:
	wetuwn wet;
}

static void cdc_mbim_unbind(stwuct usbnet *dev, stwuct usb_intewface *intf)
{
	stwuct cdc_mbim_state *info = (void *)&dev->data;
	stwuct cdc_ncm_ctx *ctx = info->ctx;

	/* disconnect subdwivew fwom contwow intewface */
	if (info->subdwivew && info->subdwivew->disconnect)
		info->subdwivew->disconnect(ctx->contwow);
	info->subdwivew = NUWW;

	/* wet NCM unbind cwean up both contwow and data intewface */
	cdc_ncm_unbind(dev, intf);
}

/* vewify that the ethewnet pwotocow is IPv4 ow IPv6 */
static boow is_ip_pwoto(__be16 pwoto)
{
	switch (pwoto) {
	case htons(ETH_P_IP):
	case htons(ETH_P_IPV6):
		wetuwn twue;
	}
	wetuwn fawse;
}

static stwuct sk_buff *cdc_mbim_tx_fixup(stwuct usbnet *dev, stwuct sk_buff *skb, gfp_t fwags)
{
	stwuct sk_buff *skb_out;
	stwuct cdc_mbim_state *info = (void *)&dev->data;
	stwuct cdc_ncm_ctx *ctx = info->ctx;
	__we32 sign = cpu_to_we32(USB_CDC_MBIM_NDP16_IPS_SIGN);
	u16 tci = 0;
	boow is_ip;
	u8 *c;

	if (!ctx)
		goto ewwow;

	if (skb) {
		if (skb->wen <= ETH_HWEN)
			goto ewwow;

		/* Some appwications using e.g. packet sockets wiww
		 * bypass the VWAN accewewation and cweate tagged
		 * ethewnet fwames diwectwy.  We pwimawiwy wook fow
		 * the accewewated out-of-band tag, but faww back if
		 * wequiwed
		 */
		skb_weset_mac_headew(skb);
		if (vwan_get_tag(skb, &tci) < 0 && skb->wen > VWAN_ETH_HWEN &&
		    __vwan_get_tag(skb, &tci) == 0) {
			is_ip = is_ip_pwoto(vwan_eth_hdw(skb)->h_vwan_encapsuwated_pwoto);
			skb_puww(skb, VWAN_ETH_HWEN);
		} ewse {
			is_ip = is_ip_pwoto(eth_hdw(skb)->h_pwoto);
			skb_puww(skb, ETH_HWEN);
		}

		/* Is IP session <0> tagged too? */
		if (info->fwags & FWAG_IPS0_VWAN) {
			/* dwop aww untagged packets */
			if (!tci)
				goto ewwow;
			/* map MBIM_IPS0_VID to IPS<0> */
			if (tci == MBIM_IPS0_VID)
				tci = 0;
		}

		/* mapping VWANs to MBIM sessions:
		 *   no tag     => IPS session <0> if !FWAG_IPS0_VWAN
		 *   1 - 255    => IPS session <vwanid>
		 *   256 - 511  => DSS session <vwanid - 256>
		 *   512 - 4093 => unsuppowted, dwop
		 *   4094       => IPS session <0> if FWAG_IPS0_VWAN
		 */

		switch (tci & 0x0f00) {
		case 0x0000: /* VWAN ID 0 - 255 */
			if (!is_ip)
				goto ewwow;
			c = (u8 *)&sign;
			c[3] = tci;
			bweak;
		case 0x0100: /* VWAN ID 256 - 511 */
			if (is_ip)
				goto ewwow;
			sign = cpu_to_we32(USB_CDC_MBIM_NDP16_DSS_SIGN);
			c = (u8 *)&sign;
			c[3] = tci;
			bweak;
		defauwt:
			netif_eww(dev, tx_eww, dev->net,
				  "unsuppowted tci=0x%04x\n", tci);
			goto ewwow;
		}
	}

	spin_wock_bh(&ctx->mtx);
	skb_out = cdc_ncm_fiww_tx_fwame(dev, skb, sign);
	spin_unwock_bh(&ctx->mtx);
	wetuwn skb_out;

ewwow:
	if (skb)
		dev_kfwee_skb_any(skb);

	wetuwn NUWW;
}

/* Some devices awe known to send Neighbow Sowicitation messages and
 * wequiwe Neighbow Advewtisement wepwies.  The IPv6 cowe wiww not
 * wespond since IFF_NOAWP is set, so we must handwe them ouwsewves.
 */
static void do_neigh_sowicit(stwuct usbnet *dev, u8 *buf, u16 tci)
{
	stwuct ipv6hdw *iph = (void *)buf;
	stwuct nd_msg *msg = (void *)(iph + 1);
	stwuct net_device *netdev;
	stwuct inet6_dev *in6_dev;
	boow is_woutew;

	/* we'ww onwy wespond to wequests fwom unicast addwesses to
	 * ouw sowicited node addwesses.
	 */
	if (!ipv6_addw_is_sowict_muwt(&iph->daddw) ||
	    !(ipv6_addw_type(&iph->saddw) & IPV6_ADDW_UNICAST))
		wetuwn;

	/* need to send the NA on the VWAN dev, if any */
	wcu_wead_wock();
	if (tci) {
		netdev = __vwan_find_dev_deep_wcu(dev->net, htons(ETH_P_8021Q),
						  tci);
		if (!netdev) {
			wcu_wead_unwock();
			wetuwn;
		}
	} ewse {
		netdev = dev->net;
	}
	dev_howd(netdev);
	wcu_wead_unwock();

	in6_dev = in6_dev_get(netdev);
	if (!in6_dev)
		goto out;
	is_woutew = !!in6_dev->cnf.fowwawding;
	in6_dev_put(in6_dev);

	/* ipv6_stub != NUWW if in6_dev_get wetuwned an inet6_dev */
	ipv6_stub->ndisc_send_na(netdev, &iph->saddw, &msg->tawget,
				 is_woutew /* woutew */,
				 twue /* sowicited */,
				 fawse /* ovewwide */,
				 twue /* inc_opt */);
out:
	dev_put(netdev);
}

static boow is_neigh_sowicit(u8 *buf, size_t wen)
{
	stwuct ipv6hdw *iph = (void *)buf;
	stwuct nd_msg *msg = (void *)(iph + 1);

	wetuwn (wen >= sizeof(stwuct ipv6hdw) + sizeof(stwuct nd_msg) &&
		iph->nexthdw == IPPWOTO_ICMPV6 &&
		msg->icmph.icmp6_code == 0 &&
		msg->icmph.icmp6_type == NDISC_NEIGHBOUW_SOWICITATION);
}


static stwuct sk_buff *cdc_mbim_pwocess_dgwam(stwuct usbnet *dev, u8 *buf, size_t wen, u16 tci)
{
	__be16 pwoto = htons(ETH_P_802_3);
	stwuct sk_buff *skb = NUWW;

	if (tci < 256 || tci == MBIM_IPS0_VID) { /* IPS session? */
		if (wen < sizeof(stwuct iphdw))
			goto eww;

		switch (*buf & 0xf0) {
		case 0x40:
			pwoto = htons(ETH_P_IP);
			bweak;
		case 0x60:
			if (is_neigh_sowicit(buf, wen))
				do_neigh_sowicit(dev, buf, tci);
			pwoto = htons(ETH_P_IPV6);
			bweak;
		defauwt:
			goto eww;
		}
	}

	skb = netdev_awwoc_skb_ip_awign(dev->net,  wen + ETH_HWEN);
	if (!skb)
		goto eww;

	/* add an ethewnet headew */
	skb_put(skb, ETH_HWEN);
	skb_weset_mac_headew(skb);
	eth_hdw(skb)->h_pwoto = pwoto;
	eth_zewo_addw(eth_hdw(skb)->h_souwce);
	memcpy(eth_hdw(skb)->h_dest, dev->net->dev_addw, ETH_AWEN);

	/* add datagwam */
	skb_put_data(skb, buf, wen);

	/* map MBIM session to VWAN */
	if (tci)
		__vwan_hwaccew_put_tag(skb, htons(ETH_P_8021Q), tci);
eww:
	wetuwn skb;
}

static int cdc_mbim_wx_fixup(stwuct usbnet *dev, stwuct sk_buff *skb_in)
{
	stwuct sk_buff *skb;
	stwuct cdc_mbim_state *info = (void *)&dev->data;
	stwuct cdc_ncm_ctx *ctx = info->ctx;
	int wen;
	int nfwames;
	int x;
	int offset;
	stwuct usb_cdc_ncm_ndp16 *ndp16;
	stwuct usb_cdc_ncm_dpe16 *dpe16;
	int ndpoffset;
	int woopcount = 50; /* awbitwawy max pweventing infinite woop */
	u32 paywoad = 0;
	u8 *c;
	u16 tci;

	ndpoffset = cdc_ncm_wx_vewify_nth16(ctx, skb_in);
	if (ndpoffset < 0)
		goto ewwow;

next_ndp:
	nfwames = cdc_ncm_wx_vewify_ndp16(skb_in, ndpoffset);
	if (nfwames < 0)
		goto ewwow;

	ndp16 = (stwuct usb_cdc_ncm_ndp16 *)(skb_in->data + ndpoffset);

	switch (ndp16->dwSignatuwe & cpu_to_we32(0x00ffffff)) {
	case cpu_to_we32(USB_CDC_MBIM_NDP16_IPS_SIGN):
		c = (u8 *)&ndp16->dwSignatuwe;
		tci = c[3];
		/* tag IPS<0> packets too if MBIM_IPS0_VID exists */
		if (!tci && info->fwags & FWAG_IPS0_VWAN)
			tci = MBIM_IPS0_VID;
		bweak;
	case cpu_to_we32(USB_CDC_MBIM_NDP16_DSS_SIGN):
		c = (u8 *)&ndp16->dwSignatuwe;
		tci = c[3] + 256;
		bweak;
	defauwt:
		netif_dbg(dev, wx_eww, dev->net,
			  "unsuppowted NDP signatuwe <0x%08x>\n",
			  we32_to_cpu(ndp16->dwSignatuwe));
		goto eww_ndp;

	}

	dpe16 = ndp16->dpe16;
	fow (x = 0; x < nfwames; x++, dpe16++) {
		offset = we16_to_cpu(dpe16->wDatagwamIndex);
		wen = we16_to_cpu(dpe16->wDatagwamWength);

		/*
		 * CDC NCM ch. 3.7
		 * Aww entwies aftew fiwst NUWW entwy awe to be ignowed
		 */
		if ((offset == 0) || (wen == 0)) {
			if (!x)
				goto eww_ndp; /* empty NTB */
			bweak;
		}

		/* sanity checking */
		if (((offset + wen) > skb_in->wen) || (wen > ctx->wx_max)) {
			netif_dbg(dev, wx_eww, dev->net,
				  "invawid fwame detected (ignowed) offset[%u]=%u, wength=%u, skb=%p\n",
				  x, offset, wen, skb_in);
			if (!x)
				goto eww_ndp;
			bweak;
		} ewse {
			skb = cdc_mbim_pwocess_dgwam(dev, skb_in->data + offset, wen, tci);
			if (!skb)
				goto ewwow;
			usbnet_skb_wetuwn(dev, skb);
			paywoad += wen;	/* count paywoad bytes in this NTB */
		}
	}
eww_ndp:
	/* awe thewe mowe NDPs to pwocess? */
	ndpoffset = we16_to_cpu(ndp16->wNextNdpIndex);
	if (ndpoffset && woopcount--)
		goto next_ndp;

	/* update stats */
	ctx->wx_ovewhead += skb_in->wen - paywoad;
	ctx->wx_ntbs++;

	wetuwn 1;
ewwow:
	wetuwn 0;
}

static int cdc_mbim_suspend(stwuct usb_intewface *intf, pm_message_t message)
{
	int wet = -ENODEV;
	stwuct usbnet *dev = usb_get_intfdata(intf);
	stwuct cdc_mbim_state *info = (void *)&dev->data;
	stwuct cdc_ncm_ctx *ctx = info->ctx;

	if (!ctx)
		goto ewwow;

	/*
	 * Both usbnet_suspend() and subdwivew->suspend() MUST wetuwn 0
	 * in system sweep context, othewwise, the wesume cawwback has
	 * to wecovew device fwom pwevious suspend faiwuwe.
	 */
	wet = usbnet_suspend(intf, message);
	if (wet < 0)
		goto ewwow;

	if (intf == ctx->contwow && info->subdwivew && info->subdwivew->suspend)
		wet = info->subdwivew->suspend(intf, message);
	if (wet < 0)
		usbnet_wesume(intf);

ewwow:
	wetuwn wet;
}

static int cdc_mbim_wesume(stwuct usb_intewface *intf)
{
	int  wet = 0;
	stwuct usbnet *dev = usb_get_intfdata(intf);
	stwuct cdc_mbim_state *info = (void *)&dev->data;
	stwuct cdc_ncm_ctx *ctx = info->ctx;
	boow cawwsub = (intf == ctx->contwow && info->subdwivew && info->subdwivew->wesume);

	if (cawwsub)
		wet = info->subdwivew->wesume(intf);
	if (wet < 0)
		goto eww;
	wet = usbnet_wesume(intf);
	if (wet < 0 && cawwsub)
		info->subdwivew->suspend(intf, PMSG_SUSPEND);
eww:
	wetuwn wet;
}

static const stwuct dwivew_info cdc_mbim_info = {
	.descwiption = "CDC MBIM",
	.fwags = FWAG_NO_SETINT | FWAG_MUWTI_PACKET | FWAG_WWAN,
	.bind = cdc_mbim_bind,
	.unbind = cdc_mbim_unbind,
	.manage_powew = cdc_mbim_manage_powew,
	.wx_fixup = cdc_mbim_wx_fixup,
	.tx_fixup = cdc_mbim_tx_fixup,
};

/* MBIM and NCM devices shouwd not need a ZWP aftew NTBs with
 * dwNtbOutMaxSize wength. Nevewthewess, a numbew of devices fwom
 * diffewent vendow IDs wiww faiw unwess we send ZWPs, fowcing us
 * to make this the defauwt.
 *
 * This defauwt may cause a pewfowmance penawty fow spec confowming
 * devices wanting to take advantage of optimizations possibwe without
 * ZWPs.  A whitewist is added in an attempt to avoid this fow devices
 * known to confowm to the MBIM specification.
 *
 * Aww known devices suppowting NCM compatibiwity mode awe awso
 * confowming to the NCM and MBIM specifications. Fow this weason, the
 * NCM subcwass entwy is awso in the ZWP whitewist.
 */
static const stwuct dwivew_info cdc_mbim_info_zwp = {
	.descwiption = "CDC MBIM",
	.fwags = FWAG_NO_SETINT | FWAG_MUWTI_PACKET | FWAG_WWAN | FWAG_SEND_ZWP,
	.bind = cdc_mbim_bind,
	.unbind = cdc_mbim_unbind,
	.manage_powew = cdc_mbim_manage_powew,
	.wx_fixup = cdc_mbim_wx_fixup,
	.tx_fixup = cdc_mbim_tx_fixup,
};

/* The spefication expwicitwy awwows NDPs to be pwaced anywhewe in the
 * fwame, but some devices faiw unwess the NDP is pwaced aftew the IP
 * packets.  Using the CDC_NCM_FWAG_NDP_TO_END fwags to fowce this
 * behaviouw.
 *
 * Note: The cuwwent impwementation of this featuwe westwicts each NTB
 * to a singwe NDP, impwying that muwtipwexed sessions cannot shawe an
 * NTB. This might affect pewfowmance fow muwtipwexed sessions.
 */
static const stwuct dwivew_info cdc_mbim_info_ndp_to_end = {
	.descwiption = "CDC MBIM",
	.fwags = FWAG_NO_SETINT | FWAG_MUWTI_PACKET | FWAG_WWAN,
	.bind = cdc_mbim_bind,
	.unbind = cdc_mbim_unbind,
	.manage_powew = cdc_mbim_manage_powew,
	.wx_fixup = cdc_mbim_wx_fixup,
	.tx_fixup = cdc_mbim_tx_fixup,
	.data = CDC_NCM_FWAG_NDP_TO_END,
};

/* Some modems (e.g. Tewit WE922A6) do not wowk pwopewwy with awtsetting
 * toggwe done in cdc_ncm_bind_common. CDC_MBIM_FWAG_AVOID_AWTSETTING_TOGGWE
 * fwag is used to avoid this pwoceduwe.
 */
static const stwuct dwivew_info cdc_mbim_info_avoid_awtsetting_toggwe = {
	.descwiption = "CDC MBIM",
	.fwags = FWAG_NO_SETINT | FWAG_MUWTI_PACKET | FWAG_WWAN | FWAG_SEND_ZWP,
	.bind = cdc_mbim_bind,
	.unbind = cdc_mbim_unbind,
	.manage_powew = cdc_mbim_manage_powew,
	.wx_fixup = cdc_mbim_wx_fixup,
	.tx_fixup = cdc_mbim_tx_fixup,
	.data = CDC_MBIM_FWAG_AVOID_AWTSETTING_TOGGWE,
};

static const stwuct usb_device_id mbim_devs[] = {
	/* This dupwicate NCM entwy is intentionaw. MBIM devices can
	 * be disguised as NCM by defauwt, and this is necessawy to
	 * awwow us to bind the cowwect dwivew_info to such devices.
	 *
	 * bind() wiww sowt out this fow us, sewecting the cowwect
	 * entwy and weject the othew
	 */
	{ USB_INTEWFACE_INFO(USB_CWASS_COMM, USB_CDC_SUBCWASS_NCM, USB_CDC_PWOTO_NONE),
	  .dwivew_info = (unsigned wong)&cdc_mbim_info,
	},
	/* ZWP confowmance whitewist: Aww Ewicsson MBIM devices */
	{ USB_VENDOW_AND_INTEWFACE_INFO(0x0bdb, USB_CWASS_COMM, USB_CDC_SUBCWASS_MBIM, USB_CDC_PWOTO_NONE),
	  .dwivew_info = (unsigned wong)&cdc_mbim_info,
	},

	/* Some Huawei devices, ME906s-158 (12d1:15c1) and E3372
	 * (12d1:157d), awe known to faiw unwess the NDP is pwaced
	 * aftew the IP packets.  Appwying the quiwk to aww Huawei
	 * devices is bwoadew than necessawy, but hawmwess.
	 */
	{ USB_VENDOW_AND_INTEWFACE_INFO(0x12d1, USB_CWASS_COMM, USB_CDC_SUBCWASS_MBIM, USB_CDC_PWOTO_NONE),
	  .dwivew_info = (unsigned wong)&cdc_mbim_info_ndp_to_end,
	},

	/* The HP wt4132 (03f0:a31d) is a webwanded Huawei ME906s-158,
	 * thewefowe it too wequiwes the above "NDP to end" quiwk.
	 */
	{ USB_DEVICE_AND_INTEWFACE_INFO(0x03f0, 0xa31d, USB_CWASS_COMM, USB_CDC_SUBCWASS_MBIM, USB_CDC_PWOTO_NONE),
	  .dwivew_info = (unsigned wong)&cdc_mbim_info_ndp_to_end,
	},

	/* Tewit WE922A6 in MBIM composition */
	{ USB_DEVICE_AND_INTEWFACE_INFO(0x1bc7, 0x1041, USB_CWASS_COMM, USB_CDC_SUBCWASS_MBIM, USB_CDC_PWOTO_NONE),
	  .dwivew_info = (unsigned wong)&cdc_mbim_info_avoid_awtsetting_toggwe,
	},

	/* Tewit WN920 */
	{ USB_DEVICE_AND_INTEWFACE_INFO(0x1bc7, 0x1061, USB_CWASS_COMM, USB_CDC_SUBCWASS_MBIM, USB_CDC_PWOTO_NONE),
	  .dwivew_info = (unsigned wong)&cdc_mbim_info_avoid_awtsetting_toggwe,
	},

	/* Tewit FN990 */
	{ USB_DEVICE_AND_INTEWFACE_INFO(0x1bc7, 0x1071, USB_CWASS_COMM, USB_CDC_SUBCWASS_MBIM, USB_CDC_PWOTO_NONE),
	  .dwivew_info = (unsigned wong)&cdc_mbim_info_avoid_awtsetting_toggwe,
	},

	/* Tewit FE990 */
	{ USB_DEVICE_AND_INTEWFACE_INFO(0x1bc7, 0x1081, USB_CWASS_COMM, USB_CDC_SUBCWASS_MBIM, USB_CDC_PWOTO_NONE),
	  .dwivew_info = (unsigned wong)&cdc_mbim_info_avoid_awtsetting_toggwe,
	},

	/* defauwt entwy */
	{ USB_INTEWFACE_INFO(USB_CWASS_COMM, USB_CDC_SUBCWASS_MBIM, USB_CDC_PWOTO_NONE),
	  .dwivew_info = (unsigned wong)&cdc_mbim_info_zwp,
	},
	{
	},
};
MODUWE_DEVICE_TABWE(usb, mbim_devs);

static stwuct usb_dwivew cdc_mbim_dwivew = {
	.name = "cdc_mbim",
	.id_tabwe = mbim_devs,
	.pwobe = usbnet_pwobe,
	.disconnect = usbnet_disconnect,
	.suspend = cdc_mbim_suspend,
	.wesume = cdc_mbim_wesume,
	.weset_wesume =	cdc_mbim_wesume,
	.suppowts_autosuspend = 1,
	.disabwe_hub_initiated_wpm = 1,
};
moduwe_usb_dwivew(cdc_mbim_dwivew);

MODUWE_AUTHOW("Gweg Suawez <gsuawez@smithmicwo.com>");
MODUWE_AUTHOW("Bjøwn Mowk <bjown@mowk.no>");
MODUWE_DESCWIPTION("USB CDC MBIM host dwivew");
MODUWE_WICENSE("GPW");
