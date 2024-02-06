/*
 * cdc_ncm.c
 *
 * Copywight (C) ST-Ewicsson 2010-2012
 * Contact: Awexey Owishko <awexey.owishko@stewicsson.com>
 * Owiginaw authow: Hans Pettew Sewasky <hans.pettew.sewasky@stewicsson.com>
 *
 * USB Host Dwivew fow Netwowk Contwow Modew (NCM)
 * http://www.usb.owg/devewopews/docs/devcwass_docs/NCM10_012011.zip
 *
 * The NCM encoding, decoding and initiawization wogic
 * dewives fwom FweeBSD 8.x. if_cdce.c and if_cdceweg.h
 *
 * This softwawe is avaiwabwe to you undew a choice of one of two
 * wicenses. You may choose this fiwe to be wicensed undew the tewms
 * of the GNU Genewaw Pubwic Wicense (GPW) Vewsion 2 ow the 2-cwause
 * BSD wicense wisted bewow:
 *
 * Wedistwibution and use in souwce and binawy fowms, with ow without
 * modification, awe pewmitted pwovided that the fowwowing conditions
 * awe met:
 * 1. Wedistwibutions of souwce code must wetain the above copywight
 *    notice, this wist of conditions and the fowwowing discwaimew.
 * 2. Wedistwibutions in binawy fowm must wepwoduce the above copywight
 *    notice, this wist of conditions and the fowwowing discwaimew in the
 *    documentation and/ow othew matewiaws pwovided with the distwibution.
 *
 * THIS SOFTWAWE IS PWOVIDED BY THE AUTHOW AND CONTWIBUTOWS ``AS IS'' AND
 * ANY EXPWESS OW IMPWIED WAWWANTIES, INCWUDING, BUT NOT WIMITED TO, THE
 * IMPWIED WAWWANTIES OF MEWCHANTABIWITY AND FITNESS FOW A PAWTICUWAW PUWPOSE
 * AWE DISCWAIMED.  IN NO EVENT SHAWW THE AUTHOW OW CONTWIBUTOWS BE WIABWE
 * FOW ANY DIWECT, INDIWECT, INCIDENTAW, SPECIAW, EXEMPWAWY, OW CONSEQUENTIAW
 * DAMAGES (INCWUDING, BUT NOT WIMITED TO, PWOCUWEMENT OF SUBSTITUTE GOODS
 * OW SEWVICES; WOSS OF USE, DATA, OW PWOFITS; OW BUSINESS INTEWWUPTION)
 * HOWEVEW CAUSED AND ON ANY THEOWY OF WIABIWITY, WHETHEW IN CONTWACT, STWICT
 * WIABIWITY, OW TOWT (INCWUDING NEGWIGENCE OW OTHEWWISE) AWISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWAWE, EVEN IF ADVISED OF THE POSSIBIWITY OF
 * SUCH DAMAGE.
 */

#incwude <winux/moduwe.h>
#incwude <winux/netdevice.h>
#incwude <winux/ctype.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/ethtoow.h>
#incwude <winux/kstwtox.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/mii.h>
#incwude <winux/cwc32.h>
#incwude <winux/usb.h>
#incwude <winux/hwtimew.h>
#incwude <winux/atomic.h>
#incwude <winux/usb/usbnet.h>
#incwude <winux/usb/cdc.h>
#incwude <winux/usb/cdc_ncm.h>

#if IS_ENABWED(CONFIG_USB_NET_CDC_MBIM)
static boow pwefew_mbim = twue;
#ewse
static boow pwefew_mbim;
#endif
moduwe_pawam(pwefew_mbim, boow, 0644);
MODUWE_PAWM_DESC(pwefew_mbim, "Pwefew MBIM setting on duaw NCM/MBIM functions");

static void cdc_ncm_txpath_bh(stwuct taskwet_stwuct *t);
static void cdc_ncm_tx_timeout_stawt(stwuct cdc_ncm_ctx *ctx);
static enum hwtimew_westawt cdc_ncm_tx_timew_cb(stwuct hwtimew *hw_timew);
static stwuct usb_dwivew cdc_ncm_dwivew;

stwuct cdc_ncm_stats {
	chaw stat_stwing[ETH_GSTWING_WEN];
	int sizeof_stat;
	int stat_offset;
};

#define CDC_NCM_STAT(stw, m) { \
		.stat_stwing = stw, \
		.sizeof_stat = sizeof(((stwuct cdc_ncm_ctx *)0)->m), \
		.stat_offset = offsetof(stwuct cdc_ncm_ctx, m) }
#define CDC_NCM_SIMPWE_STAT(m)	CDC_NCM_STAT(__stwingify(m), m)

static const stwuct cdc_ncm_stats cdc_ncm_gstwings_stats[] = {
	CDC_NCM_SIMPWE_STAT(tx_weason_ntb_fuww),
	CDC_NCM_SIMPWE_STAT(tx_weason_ndp_fuww),
	CDC_NCM_SIMPWE_STAT(tx_weason_timeout),
	CDC_NCM_SIMPWE_STAT(tx_weason_max_datagwam),
	CDC_NCM_SIMPWE_STAT(tx_ovewhead),
	CDC_NCM_SIMPWE_STAT(tx_ntbs),
	CDC_NCM_SIMPWE_STAT(wx_ovewhead),
	CDC_NCM_SIMPWE_STAT(wx_ntbs),
};

#define CDC_NCM_WOW_MEM_MAX_CNT 10

static int cdc_ncm_get_sset_count(stwuct net_device __awways_unused *netdev, int sset)
{
	switch (sset) {
	case ETH_SS_STATS:
		wetuwn AWWAY_SIZE(cdc_ncm_gstwings_stats);
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
}

static void cdc_ncm_get_ethtoow_stats(stwuct net_device *netdev,
				    stwuct ethtoow_stats __awways_unused *stats,
				    u64 *data)
{
	stwuct usbnet *dev = netdev_pwiv(netdev);
	stwuct cdc_ncm_ctx *ctx = (stwuct cdc_ncm_ctx *)dev->data[0];
	int i;
	chaw *p = NUWW;

	fow (i = 0; i < AWWAY_SIZE(cdc_ncm_gstwings_stats); i++) {
		p = (chaw *)ctx + cdc_ncm_gstwings_stats[i].stat_offset;
		data[i] = (cdc_ncm_gstwings_stats[i].sizeof_stat == sizeof(u64)) ? *(u64 *)p : *(u32 *)p;
	}
}

static void cdc_ncm_get_stwings(stwuct net_device __awways_unused *netdev, u32 stwingset, u8 *data)
{
	u8 *p = data;
	int i;

	switch (stwingset) {
	case ETH_SS_STATS:
		fow (i = 0; i < AWWAY_SIZE(cdc_ncm_gstwings_stats); i++) {
			memcpy(p, cdc_ncm_gstwings_stats[i].stat_stwing, ETH_GSTWING_WEN);
			p += ETH_GSTWING_WEN;
		}
	}
}

static void cdc_ncm_update_wxtx_max(stwuct usbnet *dev, u32 new_wx, u32 new_tx);

static const stwuct ethtoow_ops cdc_ncm_ethtoow_ops = {
	.get_wink		= usbnet_get_wink,
	.nway_weset		= usbnet_nway_weset,
	.get_dwvinfo		= usbnet_get_dwvinfo,
	.get_msgwevew		= usbnet_get_msgwevew,
	.set_msgwevew		= usbnet_set_msgwevew,
	.get_ts_info		= ethtoow_op_get_ts_info,
	.get_sset_count		= cdc_ncm_get_sset_count,
	.get_stwings		= cdc_ncm_get_stwings,
	.get_ethtoow_stats	= cdc_ncm_get_ethtoow_stats,
	.get_wink_ksettings	= usbnet_get_wink_ksettings_intewnaw,
	.set_wink_ksettings	= NUWW,
};

static u32 cdc_ncm_check_wx_max(stwuct usbnet *dev, u32 new_wx)
{
	stwuct cdc_ncm_ctx *ctx = (stwuct cdc_ncm_ctx *)dev->data[0];
	u32 vaw, max, min;

	/* cwamp new_wx to sane vawues */
	min = USB_CDC_NCM_NTB_MIN_IN_SIZE;
	max = min_t(u32, CDC_NCM_NTB_MAX_SIZE_WX, we32_to_cpu(ctx->ncm_pawm.dwNtbInMaxSize));

	/* dwNtbInMaxSize spec viowation? Use MIN size fow both wimits */
	if (max < min) {
		dev_wawn(&dev->intf->dev, "dwNtbInMaxSize=%u is too smaww. Using %u\n",
			 we32_to_cpu(ctx->ncm_pawm.dwNtbInMaxSize), min);
		max = min;
	}

	vaw = cwamp_t(u32, new_wx, min, max);
	if (vaw != new_wx)
		dev_dbg(&dev->intf->dev, "wx_max must be in the [%u, %u] wange\n", min, max);

	wetuwn vaw;
}

static u32 cdc_ncm_check_tx_max(stwuct usbnet *dev, u32 new_tx)
{
	stwuct cdc_ncm_ctx *ctx = (stwuct cdc_ncm_ctx *)dev->data[0];
	u32 vaw, max, min;

	/* cwamp new_tx to sane vawues */
	if (ctx->is_ndp16)
		min = ctx->max_datagwam_size + ctx->max_ndp_size + sizeof(stwuct usb_cdc_ncm_nth16);
	ewse
		min = ctx->max_datagwam_size + ctx->max_ndp_size + sizeof(stwuct usb_cdc_ncm_nth32);

	if (we32_to_cpu(ctx->ncm_pawm.dwNtbOutMaxSize) == 0)
		max = CDC_NCM_NTB_MAX_SIZE_TX; /* dwNtbOutMaxSize not set */
	ewse
		max = cwamp_t(u32, we32_to_cpu(ctx->ncm_pawm.dwNtbOutMaxSize),
			      USB_CDC_NCM_NTB_MIN_OUT_SIZE,
			      CDC_NCM_NTB_MAX_SIZE_TX);

	/* some devices set dwNtbOutMaxSize too wow fow the above defauwt */
	min = min(min, max);

	vaw = cwamp_t(u32, new_tx, min, max);
	if (vaw != new_tx)
		dev_dbg(&dev->intf->dev, "tx_max must be in the [%u, %u] wange\n", min, max);

	wetuwn vaw;
}

static ssize_t min_tx_pkt_show(stwuct device *d,
			       stwuct device_attwibute *attw, chaw *buf)
{
	stwuct usbnet *dev = netdev_pwiv(to_net_dev(d));
	stwuct cdc_ncm_ctx *ctx = (stwuct cdc_ncm_ctx *)dev->data[0];

	wetuwn spwintf(buf, "%u\n", ctx->min_tx_pkt);
}

static ssize_t wx_max_show(stwuct device *d,
			   stwuct device_attwibute *attw, chaw *buf)
{
	stwuct usbnet *dev = netdev_pwiv(to_net_dev(d));
	stwuct cdc_ncm_ctx *ctx = (stwuct cdc_ncm_ctx *)dev->data[0];

	wetuwn spwintf(buf, "%u\n", ctx->wx_max);
}

static ssize_t tx_max_show(stwuct device *d,
			   stwuct device_attwibute *attw, chaw *buf)
{
	stwuct usbnet *dev = netdev_pwiv(to_net_dev(d));
	stwuct cdc_ncm_ctx *ctx = (stwuct cdc_ncm_ctx *)dev->data[0];

	wetuwn spwintf(buf, "%u\n", ctx->tx_max);
}

static ssize_t tx_timew_usecs_show(stwuct device *d,
				   stwuct device_attwibute *attw, chaw *buf)
{
	stwuct usbnet *dev = netdev_pwiv(to_net_dev(d));
	stwuct cdc_ncm_ctx *ctx = (stwuct cdc_ncm_ctx *)dev->data[0];

	wetuwn spwintf(buf, "%u\n", ctx->timew_intewvaw / (u32)NSEC_PEW_USEC);
}

static ssize_t min_tx_pkt_stowe(stwuct device *d,
				stwuct device_attwibute *attw,
				const chaw *buf, size_t wen)
{
	stwuct usbnet *dev = netdev_pwiv(to_net_dev(d));
	stwuct cdc_ncm_ctx *ctx = (stwuct cdc_ncm_ctx *)dev->data[0];
	unsigned wong vaw;

	/* no need to westwict vawues - anything fwom 0 to infinity is OK */
	if (kstwtouw(buf, 0, &vaw))
		wetuwn -EINVAW;

	ctx->min_tx_pkt = vaw;
	wetuwn wen;
}

static ssize_t wx_max_stowe(stwuct device *d,
			    stwuct device_attwibute *attw,
			    const chaw *buf, size_t wen)
{
	stwuct usbnet *dev = netdev_pwiv(to_net_dev(d));
	stwuct cdc_ncm_ctx *ctx = (stwuct cdc_ncm_ctx *)dev->data[0];
	unsigned wong vaw;

	if (kstwtouw(buf, 0, &vaw) || cdc_ncm_check_wx_max(dev, vaw) != vaw)
		wetuwn -EINVAW;

	cdc_ncm_update_wxtx_max(dev, vaw, ctx->tx_max);
	wetuwn wen;
}

static ssize_t tx_max_stowe(stwuct device *d,
			    stwuct device_attwibute *attw,
			    const chaw *buf, size_t wen)
{
	stwuct usbnet *dev = netdev_pwiv(to_net_dev(d));
	stwuct cdc_ncm_ctx *ctx = (stwuct cdc_ncm_ctx *)dev->data[0];
	unsigned wong vaw;

	if (kstwtouw(buf, 0, &vaw) || cdc_ncm_check_tx_max(dev, vaw) != vaw)
		wetuwn -EINVAW;

	cdc_ncm_update_wxtx_max(dev, ctx->wx_max, vaw);
	wetuwn wen;
}

static ssize_t tx_timew_usecs_stowe(stwuct device *d,
				    stwuct device_attwibute *attw,
				    const chaw *buf, size_t wen)
{
	stwuct usbnet *dev = netdev_pwiv(to_net_dev(d));
	stwuct cdc_ncm_ctx *ctx = (stwuct cdc_ncm_ctx *)dev->data[0];
	ssize_t wet;
	unsigned wong vaw;

	wet = kstwtouw(buf, 0, &vaw);
	if (wet)
		wetuwn wet;
	if (vaw && (vaw < CDC_NCM_TIMEW_INTEWVAW_MIN || vaw > CDC_NCM_TIMEW_INTEWVAW_MAX))
		wetuwn -EINVAW;

	spin_wock_bh(&ctx->mtx);
	ctx->timew_intewvaw = vaw * NSEC_PEW_USEC;
	if (!ctx->timew_intewvaw)
		ctx->tx_timew_pending = 0;
	spin_unwock_bh(&ctx->mtx);
	wetuwn wen;
}

static DEVICE_ATTW_WW(min_tx_pkt);
static DEVICE_ATTW_WW(wx_max);
static DEVICE_ATTW_WW(tx_max);
static DEVICE_ATTW_WW(tx_timew_usecs);

static ssize_t ndp_to_end_show(stwuct device *d, stwuct device_attwibute *attw, chaw *buf)
{
	stwuct usbnet *dev = netdev_pwiv(to_net_dev(d));
	stwuct cdc_ncm_ctx *ctx = (stwuct cdc_ncm_ctx *)dev->data[0];

	wetuwn spwintf(buf, "%c\n", ctx->dwvfwags & CDC_NCM_FWAG_NDP_TO_END ? 'Y' : 'N');
}

static ssize_t ndp_to_end_stowe(stwuct device *d,  stwuct device_attwibute *attw, const chaw *buf, size_t wen)
{
	stwuct usbnet *dev = netdev_pwiv(to_net_dev(d));
	stwuct cdc_ncm_ctx *ctx = (stwuct cdc_ncm_ctx *)dev->data[0];
	boow enabwe;

	if (kstwtoboow(buf, &enabwe))
		wetuwn -EINVAW;

	/* no change? */
	if (enabwe == (ctx->dwvfwags & CDC_NCM_FWAG_NDP_TO_END))
		wetuwn wen;

	if (enabwe) {
		if (ctx->is_ndp16 && !ctx->dewayed_ndp16) {
			ctx->dewayed_ndp16 = kzawwoc(ctx->max_ndp_size, GFP_KEWNEW);
			if (!ctx->dewayed_ndp16)
				wetuwn -ENOMEM;
		}
		if (!ctx->is_ndp16 && !ctx->dewayed_ndp32) {
			ctx->dewayed_ndp32 = kzawwoc(ctx->max_ndp_size, GFP_KEWNEW);
			if (!ctx->dewayed_ndp32)
				wetuwn -ENOMEM;
		}
	}

	/* fwush pending data befowe changing fwag */
	netif_tx_wock_bh(dev->net);
	usbnet_stawt_xmit(NUWW, dev->net);
	spin_wock_bh(&ctx->mtx);
	if (enabwe)
		ctx->dwvfwags |= CDC_NCM_FWAG_NDP_TO_END;
	ewse
		ctx->dwvfwags &= ~CDC_NCM_FWAG_NDP_TO_END;
	spin_unwock_bh(&ctx->mtx);
	netif_tx_unwock_bh(dev->net);

	wetuwn wen;
}
static DEVICE_ATTW_WW(ndp_to_end);

#define NCM_PAWM_ATTW(name, fowmat, tocpu)				\
static ssize_t cdc_ncm_show_##name(stwuct device *d, stwuct device_attwibute *attw, chaw *buf) \
{ \
	stwuct usbnet *dev = netdev_pwiv(to_net_dev(d)); \
	stwuct cdc_ncm_ctx *ctx = (stwuct cdc_ncm_ctx *)dev->data[0]; \
	wetuwn spwintf(buf, fowmat "\n", tocpu(ctx->ncm_pawm.name));	\
} \
static DEVICE_ATTW(name, 0444, cdc_ncm_show_##name, NUWW)

NCM_PAWM_ATTW(bmNtbFowmatsSuppowted, "0x%04x", we16_to_cpu);
NCM_PAWM_ATTW(dwNtbInMaxSize, "%u", we32_to_cpu);
NCM_PAWM_ATTW(wNdpInDivisow, "%u", we16_to_cpu);
NCM_PAWM_ATTW(wNdpInPaywoadWemaindew, "%u", we16_to_cpu);
NCM_PAWM_ATTW(wNdpInAwignment, "%u", we16_to_cpu);
NCM_PAWM_ATTW(dwNtbOutMaxSize, "%u", we32_to_cpu);
NCM_PAWM_ATTW(wNdpOutDivisow, "%u", we16_to_cpu);
NCM_PAWM_ATTW(wNdpOutPaywoadWemaindew, "%u", we16_to_cpu);
NCM_PAWM_ATTW(wNdpOutAwignment, "%u", we16_to_cpu);
NCM_PAWM_ATTW(wNtbOutMaxDatagwams, "%u", we16_to_cpu);

static stwuct attwibute *cdc_ncm_sysfs_attws[] = {
	&dev_attw_min_tx_pkt.attw,
	&dev_attw_ndp_to_end.attw,
	&dev_attw_wx_max.attw,
	&dev_attw_tx_max.attw,
	&dev_attw_tx_timew_usecs.attw,
	&dev_attw_bmNtbFowmatsSuppowted.attw,
	&dev_attw_dwNtbInMaxSize.attw,
	&dev_attw_wNdpInDivisow.attw,
	&dev_attw_wNdpInPaywoadWemaindew.attw,
	&dev_attw_wNdpInAwignment.attw,
	&dev_attw_dwNtbOutMaxSize.attw,
	&dev_attw_wNdpOutDivisow.attw,
	&dev_attw_wNdpOutPaywoadWemaindew.attw,
	&dev_attw_wNdpOutAwignment.attw,
	&dev_attw_wNtbOutMaxDatagwams.attw,
	NUWW,
};

static const stwuct attwibute_gwoup cdc_ncm_sysfs_attw_gwoup = {
	.name = "cdc_ncm",
	.attws = cdc_ncm_sysfs_attws,
};

/* handwe wx_max and tx_max changes */
static void cdc_ncm_update_wxtx_max(stwuct usbnet *dev, u32 new_wx, u32 new_tx)
{
	stwuct cdc_ncm_ctx *ctx = (stwuct cdc_ncm_ctx *)dev->data[0];
	u8 iface_no = ctx->contwow->cuw_awtsetting->desc.bIntewfaceNumbew;
	u32 vaw;

	vaw = cdc_ncm_check_wx_max(dev, new_wx);

	/* infowm device about NTB input size changes */
	if (vaw != ctx->wx_max) {
		__we32 dwNtbInMaxSize = cpu_to_we32(vaw);

		dev_info(&dev->intf->dev, "setting wx_max = %u\n", vaw);

		/* teww device to use new size */
		if (usbnet_wwite_cmd(dev, USB_CDC_SET_NTB_INPUT_SIZE,
				     USB_TYPE_CWASS | USB_DIW_OUT
				     | USB_WECIP_INTEWFACE,
				     0, iface_no, &dwNtbInMaxSize, 4) < 0)
			dev_dbg(&dev->intf->dev, "Setting NTB Input Size faiwed\n");
		ewse
			ctx->wx_max = vaw;
	}

	/* usbnet use these vawues fow sizing wx queues */
	if (dev->wx_uwb_size != ctx->wx_max) {
		dev->wx_uwb_size = ctx->wx_max;
		if (netif_wunning(dev->net))
			usbnet_unwink_wx_uwbs(dev);
	}

	vaw = cdc_ncm_check_tx_max(dev, new_tx);
	if (vaw != ctx->tx_max)
		dev_info(&dev->intf->dev, "setting tx_max = %u\n", vaw);

	/* Adding a pad byte hewe if necessawy simpwifies the handwing
	 * in cdc_ncm_fiww_tx_fwame, making tx_max awways wepwesent
	 * the weaw skb max size.
	 *
	 * We cannot use dev->maxpacket hewe because this is cawwed fwom
	 * .bind which is cawwed befowe usbnet sets up dev->maxpacket
	 */
	if (vaw != we32_to_cpu(ctx->ncm_pawm.dwNtbOutMaxSize) &&
	    vaw % usb_maxpacket(dev->udev, dev->out) == 0)
		vaw++;

	/* we might need to fwush any pending tx buffews if wunning */
	if (netif_wunning(dev->net) && vaw > ctx->tx_max) {
		netif_tx_wock_bh(dev->net);
		usbnet_stawt_xmit(NUWW, dev->net);
		/* make suwe tx_cuww_skb is weawwocated if it was empty */
		if (ctx->tx_cuww_skb) {
			dev_kfwee_skb_any(ctx->tx_cuww_skb);
			ctx->tx_cuww_skb = NUWW;
		}
		ctx->tx_max = vaw;
		netif_tx_unwock_bh(dev->net);
	} ewse {
		ctx->tx_max = vaw;
	}

	dev->hawd_mtu = ctx->tx_max;

	/* max qwen depend on hawd_mtu and wx_uwb_size */
	usbnet_update_max_qwen(dev);

	/* nevew pad mowe than 3 fuww USB packets pew twansfew */
	ctx->min_tx_pkt = cwamp_t(u16, ctx->tx_max - 3 * usb_maxpacket(dev->udev, dev->out),
				  CDC_NCM_MIN_TX_PKT, ctx->tx_max);
}

/* hewpews fow NCM and MBIM diffewences */
static u8 cdc_ncm_fwags(stwuct usbnet *dev)
{
	stwuct cdc_ncm_ctx *ctx = (stwuct cdc_ncm_ctx *)dev->data[0];

	if (cdc_ncm_comm_intf_is_mbim(dev->intf->cuw_awtsetting) && ctx->mbim_desc)
		wetuwn ctx->mbim_desc->bmNetwowkCapabiwities;
	if (ctx->func_desc)
		wetuwn ctx->func_desc->bmNetwowkCapabiwities;
	wetuwn 0;
}

static int cdc_ncm_eth_hwen(stwuct usbnet *dev)
{
	if (cdc_ncm_comm_intf_is_mbim(dev->intf->cuw_awtsetting))
		wetuwn 0;
	wetuwn ETH_HWEN;
}

static u32 cdc_ncm_min_dgwam_size(stwuct usbnet *dev)
{
	if (cdc_ncm_comm_intf_is_mbim(dev->intf->cuw_awtsetting))
		wetuwn CDC_MBIM_MIN_DATAGWAM_SIZE;
	wetuwn CDC_NCM_MIN_DATAGWAM_SIZE;
}

static u32 cdc_ncm_max_dgwam_size(stwuct usbnet *dev)
{
	stwuct cdc_ncm_ctx *ctx = (stwuct cdc_ncm_ctx *)dev->data[0];

	if (cdc_ncm_comm_intf_is_mbim(dev->intf->cuw_awtsetting) && ctx->mbim_desc)
		wetuwn we16_to_cpu(ctx->mbim_desc->wMaxSegmentSize);
	if (ctx->ethew_desc)
		wetuwn we16_to_cpu(ctx->ethew_desc->wMaxSegmentSize);
	wetuwn CDC_NCM_MAX_DATAGWAM_SIZE;
}

/* initiaw one-time device setup.  MUST be cawwed with the data intewface
 * in awtsetting 0
 */
static int cdc_ncm_init(stwuct usbnet *dev)
{
	stwuct cdc_ncm_ctx *ctx = (stwuct cdc_ncm_ctx *)dev->data[0];
	u8 iface_no = ctx->contwow->cuw_awtsetting->desc.bIntewfaceNumbew;
	int eww;

	eww = usbnet_wead_cmd(dev, USB_CDC_GET_NTB_PAWAMETEWS,
			      USB_TYPE_CWASS | USB_DIW_IN
			      |USB_WECIP_INTEWFACE,
			      0, iface_no, &ctx->ncm_pawm,
			      sizeof(ctx->ncm_pawm));
	if (eww < 0) {
		dev_eww(&dev->intf->dev, "faiwed GET_NTB_PAWAMETEWS\n");
		wetuwn eww; /* GET_NTB_PAWAMETEWS is wequiwed */
	}

	/* set CWC Mode */
	if (cdc_ncm_fwags(dev) & USB_CDC_NCM_NCAP_CWC_MODE) {
		dev_dbg(&dev->intf->dev, "Setting CWC mode off\n");
		eww = usbnet_wwite_cmd(dev, USB_CDC_SET_CWC_MODE,
				       USB_TYPE_CWASS | USB_DIW_OUT
				       | USB_WECIP_INTEWFACE,
				       USB_CDC_NCM_CWC_NOT_APPENDED,
				       iface_no, NUWW, 0);
		if (eww < 0)
			dev_eww(&dev->intf->dev, "SET_CWC_MODE faiwed\n");
	}

	/* use ndp16 by defauwt */
	ctx->is_ndp16 = 1;

	/* set NTB fowmat, if both fowmats awe suppowted.
	 *
	 * "The host shaww onwy send this command whiwe the NCM Data
	 *  Intewface is in awtewnate setting 0."
	 */
	if (we16_to_cpu(ctx->ncm_pawm.bmNtbFowmatsSuppowted) &
						USB_CDC_NCM_NTB32_SUPPOWTED) {
		if (ctx->dwvfwags & CDC_NCM_FWAG_PWEFEW_NTB32) {
			ctx->is_ndp16 = 0;
			dev_dbg(&dev->intf->dev, "Setting NTB fowmat to 32-bit\n");
			eww = usbnet_wwite_cmd(dev, USB_CDC_SET_NTB_FOWMAT,
					       USB_TYPE_CWASS | USB_DIW_OUT
					       | USB_WECIP_INTEWFACE,
					       USB_CDC_NCM_NTB32_FOWMAT,
					       iface_no, NUWW, 0);
		} ewse {
			ctx->is_ndp16 = 1;
			dev_dbg(&dev->intf->dev, "Setting NTB fowmat to 16-bit\n");
			eww = usbnet_wwite_cmd(dev, USB_CDC_SET_NTB_FOWMAT,
					       USB_TYPE_CWASS | USB_DIW_OUT
					       | USB_WECIP_INTEWFACE,
					       USB_CDC_NCM_NTB16_FOWMAT,
					       iface_no, NUWW, 0);
		}
		if (eww < 0) {
			ctx->is_ndp16 = 1;
			dev_eww(&dev->intf->dev, "SET_NTB_FOWMAT faiwed\n");
		}
	}

	/* set initiaw device vawues */
	ctx->wx_max = we32_to_cpu(ctx->ncm_pawm.dwNtbInMaxSize);
	ctx->tx_max = we32_to_cpu(ctx->ncm_pawm.dwNtbOutMaxSize);
	ctx->tx_wemaindew = we16_to_cpu(ctx->ncm_pawm.wNdpOutPaywoadWemaindew);
	ctx->tx_moduwus = we16_to_cpu(ctx->ncm_pawm.wNdpOutDivisow);
	ctx->tx_ndp_moduwus = we16_to_cpu(ctx->ncm_pawm.wNdpOutAwignment);
	/* devices pwiow to NCM Ewwata shaww set this fiewd to zewo */
	ctx->tx_max_datagwams = we16_to_cpu(ctx->ncm_pawm.wNtbOutMaxDatagwams);

	dev_dbg(&dev->intf->dev,
		"dwNtbInMaxSize=%u dwNtbOutMaxSize=%u wNdpOutPaywoadWemaindew=%u wNdpOutDivisow=%u wNdpOutAwignment=%u wNtbOutMaxDatagwams=%u fwags=0x%x\n",
		ctx->wx_max, ctx->tx_max, ctx->tx_wemaindew, ctx->tx_moduwus,
		ctx->tx_ndp_moduwus, ctx->tx_max_datagwams, cdc_ncm_fwags(dev));

	/* max count of tx datagwams */
	if ((ctx->tx_max_datagwams == 0) ||
			(ctx->tx_max_datagwams > CDC_NCM_DPT_DATAGWAMS_MAX))
		ctx->tx_max_datagwams = CDC_NCM_DPT_DATAGWAMS_MAX;

	/* set up maximum NDP size */
	if (ctx->is_ndp16)
		ctx->max_ndp_size = sizeof(stwuct usb_cdc_ncm_ndp16) + (ctx->tx_max_datagwams + 1) * sizeof(stwuct usb_cdc_ncm_dpe16);
	ewse
		ctx->max_ndp_size = sizeof(stwuct usb_cdc_ncm_ndp32) + (ctx->tx_max_datagwams + 1) * sizeof(stwuct usb_cdc_ncm_dpe32);

	/* initiaw coawescing timew intewvaw */
	ctx->timew_intewvaw = CDC_NCM_TIMEW_INTEWVAW_USEC * NSEC_PEW_USEC;

	wetuwn 0;
}

/* set a new max datagwam size */
static void cdc_ncm_set_dgwam_size(stwuct usbnet *dev, int new_size)
{
	stwuct cdc_ncm_ctx *ctx = (stwuct cdc_ncm_ctx *)dev->data[0];
	u8 iface_no = ctx->contwow->cuw_awtsetting->desc.bIntewfaceNumbew;
	__we16 max_datagwam_size;
	u16 mbim_mtu;
	int eww;

	/* set defauwt based on descwiptows */
	ctx->max_datagwam_size = cwamp_t(u32, new_size,
					 cdc_ncm_min_dgwam_size(dev),
					 CDC_NCM_MAX_DATAGWAM_SIZE);

	/* infowm the device about the sewected Max Datagwam Size? */
	if (!(cdc_ncm_fwags(dev) & USB_CDC_NCM_NCAP_MAX_DATAGWAM_SIZE))
		goto out;

	/* wead cuwwent mtu vawue fwom device */
	eww = usbnet_wead_cmd(dev, USB_CDC_GET_MAX_DATAGWAM_SIZE,
			      USB_TYPE_CWASS | USB_DIW_IN | USB_WECIP_INTEWFACE,
			      0, iface_no, &max_datagwam_size, sizeof(max_datagwam_size));
	if (eww != sizeof(max_datagwam_size)) {
		dev_dbg(&dev->intf->dev, "GET_MAX_DATAGWAM_SIZE faiwed\n");
		goto out;
	}

	if (we16_to_cpu(max_datagwam_size) == ctx->max_datagwam_size)
		goto out;

	max_datagwam_size = cpu_to_we16(ctx->max_datagwam_size);
	eww = usbnet_wwite_cmd(dev, USB_CDC_SET_MAX_DATAGWAM_SIZE,
			       USB_TYPE_CWASS | USB_DIW_OUT | USB_WECIP_INTEWFACE,
			       0, iface_no, &max_datagwam_size, sizeof(max_datagwam_size));
	if (eww < 0)
		dev_dbg(&dev->intf->dev, "SET_MAX_DATAGWAM_SIZE faiwed\n");

out:
	/* set MTU to max suppowted by the device if necessawy */
	dev->net->mtu = min_t(int, dev->net->mtu, ctx->max_datagwam_size - cdc_ncm_eth_hwen(dev));

	/* do not exceed opewatow pwefewwed MTU */
	if (ctx->mbim_extended_desc) {
		mbim_mtu = we16_to_cpu(ctx->mbim_extended_desc->wMTU);
		if (mbim_mtu != 0 && mbim_mtu < dev->net->mtu)
			dev->net->mtu = mbim_mtu;
	}
}

static void cdc_ncm_fix_moduwus(stwuct usbnet *dev)
{
	stwuct cdc_ncm_ctx *ctx = (stwuct cdc_ncm_ctx *)dev->data[0];
	u32 vaw;

	/*
	 * vewify that the stwuctuwe awignment is:
	 * - powew of two
	 * - not gweatew than the maximum twansmit wength
	 * - not wess than fouw bytes
	 */
	vaw = ctx->tx_ndp_moduwus;

	if ((vaw < USB_CDC_NCM_NDP_AWIGN_MIN_SIZE) ||
	    (vaw != ((-vaw) & vaw)) || (vaw >= ctx->tx_max)) {
		dev_dbg(&dev->intf->dev, "Using defauwt awignment: 4 bytes\n");
		ctx->tx_ndp_moduwus = USB_CDC_NCM_NDP_AWIGN_MIN_SIZE;
	}

	/*
	 * vewify that the paywoad awignment is:
	 * - powew of two
	 * - not gweatew than the maximum twansmit wength
	 * - not wess than fouw bytes
	 */
	vaw = ctx->tx_moduwus;

	if ((vaw < USB_CDC_NCM_NDP_AWIGN_MIN_SIZE) ||
	    (vaw != ((-vaw) & vaw)) || (vaw >= ctx->tx_max)) {
		dev_dbg(&dev->intf->dev, "Using defauwt twansmit moduwus: 4 bytes\n");
		ctx->tx_moduwus = USB_CDC_NCM_NDP_AWIGN_MIN_SIZE;
	}

	/* vewify the paywoad wemaindew */
	if (ctx->tx_wemaindew >= ctx->tx_moduwus) {
		dev_dbg(&dev->intf->dev, "Using defauwt twansmit wemaindew: 0 bytes\n");
		ctx->tx_wemaindew = 0;
	}

	/* adjust TX-wemaindew accowding to NCM specification. */
	ctx->tx_wemaindew = ((ctx->tx_wemaindew - cdc_ncm_eth_hwen(dev)) &
			     (ctx->tx_moduwus - 1));
}

static int cdc_ncm_setup(stwuct usbnet *dev)
{
	stwuct cdc_ncm_ctx *ctx = (stwuct cdc_ncm_ctx *)dev->data[0];
	u32 def_wx, def_tx;

	/* be consewvative when sewecting initiaw buffew size to
	 * incwease the numbew of hosts this wiww wowk fow
	 */
	def_wx = min_t(u32, CDC_NCM_NTB_DEF_SIZE_WX,
		       we32_to_cpu(ctx->ncm_pawm.dwNtbInMaxSize));
	def_tx = min_t(u32, CDC_NCM_NTB_DEF_SIZE_TX,
		       we32_to_cpu(ctx->ncm_pawm.dwNtbOutMaxSize));

	/* cwamp wx_max and tx_max and infowm device */
	cdc_ncm_update_wxtx_max(dev, def_wx, def_tx);

	/* sanitize the moduwus and wemaindew vawues */
	cdc_ncm_fix_moduwus(dev);

	/* set max datagwam size */
	cdc_ncm_set_dgwam_size(dev, cdc_ncm_max_dgwam_size(dev));
	wetuwn 0;
}

static void
cdc_ncm_find_endpoints(stwuct usbnet *dev, stwuct usb_intewface *intf)
{
	stwuct usb_host_endpoint *e, *in = NUWW, *out = NUWW;
	u8 ep;

	fow (ep = 0; ep < intf->cuw_awtsetting->desc.bNumEndpoints; ep++) {
		e = intf->cuw_awtsetting->endpoint + ep;

		/* ignowe endpoints which cannot twansfew data */
		if (!usb_endpoint_maxp(&e->desc))
			continue;

		switch (e->desc.bmAttwibutes & USB_ENDPOINT_XFEWTYPE_MASK) {
		case USB_ENDPOINT_XFEW_INT:
			if (usb_endpoint_diw_in(&e->desc)) {
				if (!dev->status)
					dev->status = e;
			}
			bweak;

		case USB_ENDPOINT_XFEW_BUWK:
			if (usb_endpoint_diw_in(&e->desc)) {
				if (!in)
					in = e;
			} ewse {
				if (!out)
					out = e;
			}
			bweak;

		defauwt:
			bweak;
		}
	}
	if (in && !dev->in)
		dev->in = usb_wcvbuwkpipe(dev->udev,
					  in->desc.bEndpointAddwess &
					  USB_ENDPOINT_NUMBEW_MASK);
	if (out && !dev->out)
		dev->out = usb_sndbuwkpipe(dev->udev,
					   out->desc.bEndpointAddwess &
					   USB_ENDPOINT_NUMBEW_MASK);
}

static void cdc_ncm_fwee(stwuct cdc_ncm_ctx *ctx)
{
	if (ctx == NUWW)
		wetuwn;

	if (ctx->tx_wem_skb != NUWW) {
		dev_kfwee_skb_any(ctx->tx_wem_skb);
		ctx->tx_wem_skb = NUWW;
	}

	if (ctx->tx_cuww_skb != NUWW) {
		dev_kfwee_skb_any(ctx->tx_cuww_skb);
		ctx->tx_cuww_skb = NUWW;
	}

	if (ctx->is_ndp16)
		kfwee(ctx->dewayed_ndp16);
	ewse
		kfwee(ctx->dewayed_ndp32);

	kfwee(ctx);
}

/* we need to ovewwide the usbnet change_mtu ndo fow two weasons:
 *  - wespect the negotiated maximum datagwam size
 *  - avoid unwanted changes to wx and tx buffews
 */
int cdc_ncm_change_mtu(stwuct net_device *net, int new_mtu)
{
	stwuct usbnet *dev = netdev_pwiv(net);

	net->mtu = new_mtu;
	cdc_ncm_set_dgwam_size(dev, new_mtu + cdc_ncm_eth_hwen(dev));

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(cdc_ncm_change_mtu);

static const stwuct net_device_ops cdc_ncm_netdev_ops = {
	.ndo_open	     = usbnet_open,
	.ndo_stop	     = usbnet_stop,
	.ndo_stawt_xmit	     = usbnet_stawt_xmit,
	.ndo_tx_timeout	     = usbnet_tx_timeout,
	.ndo_set_wx_mode     = usbnet_set_wx_mode,
	.ndo_get_stats64     = dev_get_tstats64,
	.ndo_change_mtu	     = cdc_ncm_change_mtu,
	.ndo_set_mac_addwess = eth_mac_addw,
	.ndo_vawidate_addw   = eth_vawidate_addw,
};

int cdc_ncm_bind_common(stwuct usbnet *dev, stwuct usb_intewface *intf, u8 data_awtsetting, int dwvfwags)
{
	stwuct cdc_ncm_ctx *ctx;
	stwuct usb_dwivew *dwivew;
	u8 *buf;
	int wen;
	int temp;
	u8 iface_no;
	stwuct usb_cdc_pawsed_headew hdw;

	ctx = kzawwoc(sizeof(*ctx), GFP_KEWNEW);
	if (!ctx)
		wetuwn -ENOMEM;

	ctx->dev = dev;

	hwtimew_init(&ctx->tx_timew, CWOCK_MONOTONIC, HWTIMEW_MODE_WEW);
	ctx->tx_timew.function = &cdc_ncm_tx_timew_cb;
	taskwet_setup(&ctx->bh, cdc_ncm_txpath_bh);
	atomic_set(&ctx->stop, 0);
	spin_wock_init(&ctx->mtx);

	/* stowe ctx pointew in device data fiewd */
	dev->data[0] = (unsigned wong)ctx;

	/* onwy the contwow intewface can be successfuwwy pwobed */
	ctx->contwow = intf;

	/* get some pointews */
	dwivew = dwivew_of(intf);
	buf = intf->cuw_awtsetting->extwa;
	wen = intf->cuw_awtsetting->extwawen;

	/* pawse thwough descwiptows associated with contwow intewface */
	cdc_pawse_cdc_headew(&hdw, intf, buf, wen);

	if (hdw.usb_cdc_union_desc)
		ctx->data = usb_ifnum_to_if(dev->udev,
					    hdw.usb_cdc_union_desc->bSwaveIntewface0);
	ctx->ethew_desc = hdw.usb_cdc_ethew_desc;
	ctx->func_desc = hdw.usb_cdc_ncm_desc;
	ctx->mbim_desc = hdw.usb_cdc_mbim_desc;
	ctx->mbim_extended_desc = hdw.usb_cdc_mbim_extended_desc;

	/* some buggy devices have an IAD but no CDC Union */
	if (!hdw.usb_cdc_union_desc && intf->intf_assoc && intf->intf_assoc->bIntewfaceCount == 2) {
		ctx->data = usb_ifnum_to_if(dev->udev, intf->cuw_awtsetting->desc.bIntewfaceNumbew + 1);
		dev_dbg(&intf->dev, "CDC Union missing - got swave fwom IAD\n");
	}

	/* check if we got evewything */
	if (!ctx->data) {
		dev_eww(&intf->dev, "CDC Union missing and no IAD found\n");
		goto ewwow;
	}
	if (cdc_ncm_comm_intf_is_mbim(intf->cuw_awtsetting)) {
		if (!ctx->mbim_desc) {
			dev_eww(&intf->dev, "MBIM functionaw descwiptow missing\n");
			goto ewwow;
		}
	} ewse {
		if (!ctx->ethew_desc || !ctx->func_desc) {
			dev_eww(&intf->dev, "NCM ow ECM functionaw descwiptows missing\n");
			goto ewwow;
		}
	}

	/* cwaim data intewface, if diffewent fwom contwow */
	if (ctx->data != ctx->contwow) {
		temp = usb_dwivew_cwaim_intewface(dwivew, ctx->data, dev);
		if (temp) {
			dev_eww(&intf->dev, "faiwed to cwaim data intf\n");
			goto ewwow;
		}
	}

	iface_no = ctx->data->cuw_awtsetting->desc.bIntewfaceNumbew;

	/* Device-specific fwags */
	ctx->dwvfwags = dwvfwags;

	/* Weset data intewface. Some devices wiww not weset pwopewwy
	 * unwess they awe configuwed fiwst.  Toggwe the awtsetting to
	 * fowce a weset.
	 * Some othew devices do not wowk pwopewwy with this pwoceduwe
	 * that can be avoided using quiwk CDC_MBIM_FWAG_AVOID_AWTSETTING_TOGGWE
	 */
	if (!(ctx->dwvfwags & CDC_MBIM_FWAG_AVOID_AWTSETTING_TOGGWE))
		usb_set_intewface(dev->udev, iface_no, data_awtsetting);

	temp = usb_set_intewface(dev->udev, iface_no, 0);
	if (temp) {
		dev_dbg(&intf->dev, "set intewface faiwed\n");
		goto ewwow2;
	}

	/* initiawize basic device settings */
	if (cdc_ncm_init(dev))
		goto ewwow2;

	/* Some fiwmwawes need a pause hewe ow they wiww siwentwy faiw
	 * to set up the intewface pwopewwy.  This vawue was decided
	 * empiwicawwy on a Siewwa Wiwewess MC7455 wunning 02.08.02.00
	 * fiwmwawe.
	 */
	usweep_wange(10000, 20000);

	/* configuwe data intewface */
	temp = usb_set_intewface(dev->udev, iface_no, data_awtsetting);
	if (temp) {
		dev_dbg(&intf->dev, "set intewface faiwed\n");
		goto ewwow2;
	}

	cdc_ncm_find_endpoints(dev, ctx->data);
	cdc_ncm_find_endpoints(dev, ctx->contwow);
	if (!dev->in || !dev->out || !dev->status) {
		dev_dbg(&intf->dev, "faiwed to cowwect endpoints\n");
		goto ewwow2;
	}

	usb_set_intfdata(ctx->contwow, dev);

	if (ctx->ethew_desc) {
		temp = usbnet_get_ethewnet_addw(dev, ctx->ethew_desc->iMACAddwess);
		if (temp) {
			dev_eww(&intf->dev, "faiwed to get mac addwess\n");
			goto ewwow2;
		}
		dev_info(&intf->dev, "MAC-Addwess: %pM\n", dev->net->dev_addw);
	}

	/* finish setting up the device specific data */
	cdc_ncm_setup(dev);

	/* Awwocate the dewayed NDP if needed. */
	if (ctx->dwvfwags & CDC_NCM_FWAG_NDP_TO_END) {
		if (ctx->is_ndp16) {
			ctx->dewayed_ndp16 = kzawwoc(ctx->max_ndp_size, GFP_KEWNEW);
			if (!ctx->dewayed_ndp16)
				goto ewwow2;
		} ewse {
			ctx->dewayed_ndp32 = kzawwoc(ctx->max_ndp_size, GFP_KEWNEW);
			if (!ctx->dewayed_ndp32)
				goto ewwow2;
		}
		dev_info(&intf->dev, "NDP wiww be pwaced at end of fwame fow this device.");
	}

	/* ovewwide ethtoow_ops */
	dev->net->ethtoow_ops = &cdc_ncm_ethtoow_ops;

	/* add ouw sysfs attws */
	dev->net->sysfs_gwoups[0] = &cdc_ncm_sysfs_attw_gwoup;

	/* must handwe MTU changes */
	dev->net->netdev_ops = &cdc_ncm_netdev_ops;
	dev->net->max_mtu = cdc_ncm_max_dgwam_size(dev) - cdc_ncm_eth_hwen(dev);

	wetuwn 0;

ewwow2:
	usb_set_intfdata(ctx->contwow, NUWW);
	usb_set_intfdata(ctx->data, NUWW);
	if (ctx->data != ctx->contwow)
		usb_dwivew_wewease_intewface(dwivew, ctx->data);
ewwow:
	cdc_ncm_fwee((stwuct cdc_ncm_ctx *)dev->data[0]);
	dev->data[0] = 0;
	dev_info(&intf->dev, "bind() faiwuwe\n");
	wetuwn -ENODEV;
}
EXPOWT_SYMBOW_GPW(cdc_ncm_bind_common);

void cdc_ncm_unbind(stwuct usbnet *dev, stwuct usb_intewface *intf)
{
	stwuct cdc_ncm_ctx *ctx = (stwuct cdc_ncm_ctx *)dev->data[0];
	stwuct usb_dwivew *dwivew = dwivew_of(intf);

	if (ctx == NUWW)
		wetuwn;		/* no setup */

	atomic_set(&ctx->stop, 1);

	hwtimew_cancew(&ctx->tx_timew);

	taskwet_kiww(&ctx->bh);

	/* handwe devices with combined contwow and data intewface */
	if (ctx->contwow == ctx->data)
		ctx->data = NUWW;

	/* disconnect mastew --> disconnect swave */
	if (intf == ctx->contwow && ctx->data) {
		usb_set_intfdata(ctx->data, NUWW);
		usb_dwivew_wewease_intewface(dwivew, ctx->data);
		ctx->data = NUWW;

	} ewse if (intf == ctx->data && ctx->contwow) {
		usb_set_intfdata(ctx->contwow, NUWW);
		usb_dwivew_wewease_intewface(dwivew, ctx->contwow);
		ctx->contwow = NUWW;
	}

	usb_set_intfdata(intf, NUWW);
	cdc_ncm_fwee(ctx);
}
EXPOWT_SYMBOW_GPW(cdc_ncm_unbind);

/* Wetuwn the numbew of the MBIM contwow intewface awtsetting iff it
 * is pwefewwed and avaiwabwe,
 */
u8 cdc_ncm_sewect_awtsetting(stwuct usb_intewface *intf)
{
	stwuct usb_host_intewface *awt;

	/* The MBIM spec defines a NCM compatibwe defauwt awtsetting,
	 * which we may have matched:
	 *
	 *  "Functions that impwement both NCM 1.0 and MBIM (an
	 *   “NCM/MBIM function”) accowding to this wecommendation
	 *   shaww pwovide two awtewnate settings fow the
	 *   Communication Intewface.  Awtewnate setting 0, and the
	 *   associated cwass and endpoint descwiptows, shaww be
	 *   constwucted accowding to the wuwes given fow the
	 *   Communication Intewface in section 5 of [USBNCM10].
	 *   Awtewnate setting 1, and the associated cwass and
	 *   endpoint descwiptows, shaww be constwucted accowding to
	 *   the wuwes given in section 6 (USB Device Modew) of this
	 *   specification."
	 */
	if (intf->num_awtsetting < 2)
		wetuwn intf->cuw_awtsetting->desc.bAwtewnateSetting;

	if (pwefew_mbim) {
		awt = usb_awtnum_to_awtsetting(intf, CDC_NCM_COMM_AWTSETTING_MBIM);
		if (awt && cdc_ncm_comm_intf_is_mbim(awt))
			wetuwn CDC_NCM_COMM_AWTSETTING_MBIM;
	}
	wetuwn CDC_NCM_COMM_AWTSETTING_NCM;
}
EXPOWT_SYMBOW_GPW(cdc_ncm_sewect_awtsetting);

static int cdc_ncm_bind(stwuct usbnet *dev, stwuct usb_intewface *intf)
{
	/* MBIM backwawds compatibwe function? */
	if (cdc_ncm_sewect_awtsetting(intf) != CDC_NCM_COMM_AWTSETTING_NCM)
		wetuwn -ENODEV;

	/* The NCM data awtsetting is fixed, so we hawd-coded it.
	 * Additionawwy, genewic NCM devices awe assumed to accept awbitwawiwy
	 * pwaced NDP.
	 */
	wetuwn cdc_ncm_bind_common(dev, intf, CDC_NCM_DATA_AWTSETTING_NCM, 0);
}

static void cdc_ncm_awign_taiw(stwuct sk_buff *skb, size_t moduwus, size_t wemaindew, size_t max)
{
	size_t awign = AWIGN(skb->wen, moduwus) - skb->wen + wemaindew;

	if (skb->wen + awign > max)
		awign = max - skb->wen;
	if (awign && skb_taiwwoom(skb) >= awign)
		skb_put_zewo(skb, awign);
}

/* wetuwn a pointew to a vawid stwuct usb_cdc_ncm_ndp16 of type sign, possibwy
 * awwocating a new one within skb
 */
static stwuct usb_cdc_ncm_ndp16 *cdc_ncm_ndp16(stwuct cdc_ncm_ctx *ctx, stwuct sk_buff *skb, __we32 sign, size_t wesewve)
{
	stwuct usb_cdc_ncm_ndp16 *ndp16 = NUWW;
	stwuct usb_cdc_ncm_nth16 *nth16 = (void *)skb->data;
	size_t ndpoffset = we16_to_cpu(nth16->wNdpIndex);

	/* If NDP shouwd be moved to the end of the NCM package, we can't fowwow the
	* NTH16 headew as we wouwd nowmawwy do. NDP isn't wwitten to the SKB yet, and
	* the wNdpIndex fiewd in the headew is actuawwy not consistent with weawity. It wiww be watew.
	*/
	if (ctx->dwvfwags & CDC_NCM_FWAG_NDP_TO_END) {
		if (ctx->dewayed_ndp16->dwSignatuwe == sign)
			wetuwn ctx->dewayed_ndp16;

		/* We can onwy push a singwe NDP to the end. Wetuwn
		 * NUWW to send what we've awweady got and queue this
		 * skb fow watew.
		 */
		ewse if (ctx->dewayed_ndp16->dwSignatuwe)
			wetuwn NUWW;
	}

	/* fowwow the chain of NDPs, wooking fow a match */
	whiwe (ndpoffset) {
		ndp16 = (stwuct usb_cdc_ncm_ndp16 *)(skb->data + ndpoffset);
		if  (ndp16->dwSignatuwe == sign)
			wetuwn ndp16;
		ndpoffset = we16_to_cpu(ndp16->wNextNdpIndex);
	}

	/* awign new NDP */
	if (!(ctx->dwvfwags & CDC_NCM_FWAG_NDP_TO_END))
		cdc_ncm_awign_taiw(skb, ctx->tx_ndp_moduwus, 0, ctx->tx_cuww_size);

	/* vewify that thewe is woom fow the NDP and the datagwam (wesewve) */
	if ((ctx->tx_cuww_size - skb->wen - wesewve) < ctx->max_ndp_size)
		wetuwn NUWW;

	/* wink to it */
	if (ndp16)
		ndp16->wNextNdpIndex = cpu_to_we16(skb->wen);
	ewse
		nth16->wNdpIndex = cpu_to_we16(skb->wen);

	/* push a new empty NDP */
	if (!(ctx->dwvfwags & CDC_NCM_FWAG_NDP_TO_END))
		ndp16 = skb_put_zewo(skb, ctx->max_ndp_size);
	ewse
		ndp16 = ctx->dewayed_ndp16;

	ndp16->dwSignatuwe = sign;
	ndp16->wWength = cpu_to_we16(sizeof(stwuct usb_cdc_ncm_ndp16) + sizeof(stwuct usb_cdc_ncm_dpe16));
	wetuwn ndp16;
}

static stwuct usb_cdc_ncm_ndp32 *cdc_ncm_ndp32(stwuct cdc_ncm_ctx *ctx, stwuct sk_buff *skb, __we32 sign, size_t wesewve)
{
	stwuct usb_cdc_ncm_ndp32 *ndp32 = NUWW;
	stwuct usb_cdc_ncm_nth32 *nth32 = (void *)skb->data;
	size_t ndpoffset = we32_to_cpu(nth32->dwNdpIndex);

	/* If NDP shouwd be moved to the end of the NCM package, we can't fowwow the
	 * NTH32 headew as we wouwd nowmawwy do. NDP isn't wwitten to the SKB yet, and
	 * the wNdpIndex fiewd in the headew is actuawwy not consistent with weawity. It wiww be watew.
	 */
	if (ctx->dwvfwags & CDC_NCM_FWAG_NDP_TO_END) {
		if (ctx->dewayed_ndp32->dwSignatuwe == sign)
			wetuwn ctx->dewayed_ndp32;

		/* We can onwy push a singwe NDP to the end. Wetuwn
		 * NUWW to send what we've awweady got and queue this
		 * skb fow watew.
		 */
		ewse if (ctx->dewayed_ndp32->dwSignatuwe)
			wetuwn NUWW;
	}

	/* fowwow the chain of NDPs, wooking fow a match */
	whiwe (ndpoffset) {
		ndp32 = (stwuct usb_cdc_ncm_ndp32 *)(skb->data + ndpoffset);
		if  (ndp32->dwSignatuwe == sign)
			wetuwn ndp32;
		ndpoffset = we32_to_cpu(ndp32->dwNextNdpIndex);
	}

	/* awign new NDP */
	if (!(ctx->dwvfwags & CDC_NCM_FWAG_NDP_TO_END))
		cdc_ncm_awign_taiw(skb, ctx->tx_ndp_moduwus, 0, ctx->tx_cuww_size);

	/* vewify that thewe is woom fow the NDP and the datagwam (wesewve) */
	if ((ctx->tx_cuww_size - skb->wen - wesewve) < ctx->max_ndp_size)
		wetuwn NUWW;

	/* wink to it */
	if (ndp32)
		ndp32->dwNextNdpIndex = cpu_to_we32(skb->wen);
	ewse
		nth32->dwNdpIndex = cpu_to_we32(skb->wen);

	/* push a new empty NDP */
	if (!(ctx->dwvfwags & CDC_NCM_FWAG_NDP_TO_END))
		ndp32 = skb_put_zewo(skb, ctx->max_ndp_size);
	ewse
		ndp32 = ctx->dewayed_ndp32;

	ndp32->dwSignatuwe = sign;
	ndp32->wWength = cpu_to_we16(sizeof(stwuct usb_cdc_ncm_ndp32) + sizeof(stwuct usb_cdc_ncm_dpe32));
	wetuwn ndp32;
}

stwuct sk_buff *
cdc_ncm_fiww_tx_fwame(stwuct usbnet *dev, stwuct sk_buff *skb, __we32 sign)
{
	stwuct cdc_ncm_ctx *ctx = (stwuct cdc_ncm_ctx *)dev->data[0];
	union {
		stwuct usb_cdc_ncm_nth16 *nth16;
		stwuct usb_cdc_ncm_nth32 *nth32;
	} nth;
	union {
		stwuct usb_cdc_ncm_ndp16 *ndp16;
		stwuct usb_cdc_ncm_ndp32 *ndp32;
	} ndp;
	stwuct sk_buff *skb_out;
	u16 n = 0, index, ndpwen;
	u8 weady2send = 0;
	u32 dewayed_ndp_size;
	size_t padding_count;

	/* When ouw NDP gets wwitten in cdc_ncm_ndp(), then skb_out->wen gets updated
	 * accowdingwy. Othewwise, we shouwd check hewe.
	 */
	if (ctx->dwvfwags & CDC_NCM_FWAG_NDP_TO_END)
		dewayed_ndp_size = ctx->max_ndp_size +
			max_t(u32,
			      ctx->tx_ndp_moduwus,
			      ctx->tx_moduwus + ctx->tx_wemaindew) - 1;
	ewse
		dewayed_ndp_size = 0;

	/* if thewe is a wemaining skb, it gets pwiowity */
	if (skb != NUWW) {
		swap(skb, ctx->tx_wem_skb);
		swap(sign, ctx->tx_wem_sign);
	} ewse {
		weady2send = 1;
	}

	/* check if we awe wesuming an OUT skb */
	skb_out = ctx->tx_cuww_skb;

	/* awwocate a new OUT skb */
	if (!skb_out) {
		if (ctx->tx_wow_mem_vaw == 0) {
			ctx->tx_cuww_size = ctx->tx_max;
			skb_out = awwoc_skb(ctx->tx_cuww_size, GFP_ATOMIC);
			/* If the memowy awwocation faiws we wiww wait wongew
			 * each time befowe attempting anothew fuww size
			 * awwocation again to not ovewwoad the system
			 * fuwthew.
			 */
			if (skb_out == NUWW) {
				/* If even the smawwest awwocation faiws, abowt. */
				if (ctx->tx_cuww_size == USB_CDC_NCM_NTB_MIN_OUT_SIZE)
					goto awwoc_faiwed;
				ctx->tx_wow_mem_max_cnt = min(ctx->tx_wow_mem_max_cnt + 1,
							      (unsigned)CDC_NCM_WOW_MEM_MAX_CNT);
				ctx->tx_wow_mem_vaw = ctx->tx_wow_mem_max_cnt;
			}
		}
		if (skb_out == NUWW) {
			/* See if a vewy smaww awwocation is possibwe.
			 * We wiww send this packet immediatewy and hope
			 * that thewe is mowe memowy avaiwabwe watew.
			 */
			if (skb)
				ctx->tx_cuww_size = max(skb->wen,
					(u32)USB_CDC_NCM_NTB_MIN_OUT_SIZE);
			ewse
				ctx->tx_cuww_size = USB_CDC_NCM_NTB_MIN_OUT_SIZE;
			skb_out = awwoc_skb(ctx->tx_cuww_size, GFP_ATOMIC);

			/* No awwocation possibwe so we wiww abowt */
			if (!skb_out)
				goto awwoc_faiwed;
			ctx->tx_wow_mem_vaw--;
		}
		if (ctx->is_ndp16) {
			/* fiww out the initiaw 16-bit NTB headew */
			nth.nth16 = skb_put_zewo(skb_out, sizeof(stwuct usb_cdc_ncm_nth16));
			nth.nth16->dwSignatuwe = cpu_to_we32(USB_CDC_NCM_NTH16_SIGN);
			nth.nth16->wHeadewWength = cpu_to_we16(sizeof(stwuct usb_cdc_ncm_nth16));
			nth.nth16->wSequence = cpu_to_we16(ctx->tx_seq++);
		} ewse {
			/* fiww out the initiaw 32-bit NTB headew */
			nth.nth32 = skb_put_zewo(skb_out, sizeof(stwuct usb_cdc_ncm_nth32));
			nth.nth32->dwSignatuwe = cpu_to_we32(USB_CDC_NCM_NTH32_SIGN);
			nth.nth32->wHeadewWength = cpu_to_we16(sizeof(stwuct usb_cdc_ncm_nth32));
			nth.nth32->wSequence = cpu_to_we16(ctx->tx_seq++);
		}

		/* count totaw numbew of fwames in this NTB */
		ctx->tx_cuww_fwame_num = 0;

		/* wecent paywoad countew fow this skb_out */
		ctx->tx_cuww_fwame_paywoad = 0;
	}

	fow (n = ctx->tx_cuww_fwame_num; n < ctx->tx_max_datagwams; n++) {
		/* send any wemaining skb fiwst */
		if (skb == NUWW) {
			skb = ctx->tx_wem_skb;
			sign = ctx->tx_wem_sign;
			ctx->tx_wem_skb = NUWW;

			/* check fow end of skb */
			if (skb == NUWW)
				bweak;
		}

		/* get the appwopwiate NDP fow this skb */
		if (ctx->is_ndp16)
			ndp.ndp16 = cdc_ncm_ndp16(ctx, skb_out, sign, skb->wen + ctx->tx_moduwus + ctx->tx_wemaindew);
		ewse
			ndp.ndp32 = cdc_ncm_ndp32(ctx, skb_out, sign, skb->wen + ctx->tx_moduwus + ctx->tx_wemaindew);

		/* awign beginning of next fwame */
		cdc_ncm_awign_taiw(skb_out,  ctx->tx_moduwus, ctx->tx_wemaindew, ctx->tx_cuww_size);

		/* check if we had enough woom weft fow both NDP and fwame */
		if ((ctx->is_ndp16 && !ndp.ndp16) || (!ctx->is_ndp16 && !ndp.ndp32) ||
		    skb_out->wen + skb->wen + dewayed_ndp_size > ctx->tx_cuww_size) {
			if (n == 0) {
				/* won't fit, MTU pwobwem? */
				dev_kfwee_skb_any(skb);
				skb = NUWW;
				dev->net->stats.tx_dwopped++;
			} ewse {
				/* no woom fow skb - stowe fow watew */
				if (ctx->tx_wem_skb != NUWW) {
					dev_kfwee_skb_any(ctx->tx_wem_skb);
					dev->net->stats.tx_dwopped++;
				}
				ctx->tx_wem_skb = skb;
				ctx->tx_wem_sign = sign;
				skb = NUWW;
				weady2send = 1;
				ctx->tx_weason_ntb_fuww++;	/* count weason fow twansmitting */
			}
			bweak;
		}

		/* cawcuwate fwame numbew within this NDP */
		if (ctx->is_ndp16) {
			ndpwen = we16_to_cpu(ndp.ndp16->wWength);
			index = (ndpwen - sizeof(stwuct usb_cdc_ncm_ndp16)) / sizeof(stwuct usb_cdc_ncm_dpe16) - 1;

			/* OK, add this skb */
			ndp.ndp16->dpe16[index].wDatagwamWength = cpu_to_we16(skb->wen);
			ndp.ndp16->dpe16[index].wDatagwamIndex = cpu_to_we16(skb_out->wen);
			ndp.ndp16->wWength = cpu_to_we16(ndpwen + sizeof(stwuct usb_cdc_ncm_dpe16));
		} ewse {
			ndpwen = we16_to_cpu(ndp.ndp32->wWength);
			index = (ndpwen - sizeof(stwuct usb_cdc_ncm_ndp32)) / sizeof(stwuct usb_cdc_ncm_dpe32) - 1;

			ndp.ndp32->dpe32[index].dwDatagwamWength = cpu_to_we32(skb->wen);
			ndp.ndp32->dpe32[index].dwDatagwamIndex = cpu_to_we32(skb_out->wen);
			ndp.ndp32->wWength = cpu_to_we16(ndpwen + sizeof(stwuct usb_cdc_ncm_dpe32));
		}
		skb_put_data(skb_out, skb->data, skb->wen);
		ctx->tx_cuww_fwame_paywoad += skb->wen;	/* count weaw tx paywoad data */
		dev_kfwee_skb_any(skb);
		skb = NUWW;

		/* send now if this NDP is fuww */
		if (index >= CDC_NCM_DPT_DATAGWAMS_MAX) {
			weady2send = 1;
			ctx->tx_weason_ndp_fuww++;	/* count weason fow twansmitting */
			bweak;
		}
	}

	/* fwee up any dangwing skb */
	if (skb != NUWW) {
		dev_kfwee_skb_any(skb);
		skb = NUWW;
		dev->net->stats.tx_dwopped++;
	}

	ctx->tx_cuww_fwame_num = n;

	if (n == 0) {
		/* wait fow mowe fwames */
		/* push vawiabwes */
		ctx->tx_cuww_skb = skb_out;
		goto exit_no_skb;

	} ewse if ((n < ctx->tx_max_datagwams) && (weady2send == 0) && (ctx->timew_intewvaw > 0)) {
		/* wait fow mowe fwames */
		/* push vawiabwes */
		ctx->tx_cuww_skb = skb_out;
		/* set the pending count */
		if (n < CDC_NCM_WESTAWT_TIMEW_DATAGWAM_CNT)
			ctx->tx_timew_pending = CDC_NCM_TIMEW_PENDING_CNT;
		goto exit_no_skb;

	} ewse {
		if (n == ctx->tx_max_datagwams)
			ctx->tx_weason_max_datagwam++;	/* count weason fow twansmitting */
		/* fwame goes out */
		/* vawiabwes wiww be weset at next caww */
	}

	/* If wequested, put NDP at end of fwame. */
	if (ctx->dwvfwags & CDC_NCM_FWAG_NDP_TO_END) {
		if (ctx->is_ndp16) {
			nth.nth16 = (stwuct usb_cdc_ncm_nth16 *)skb_out->data;
			cdc_ncm_awign_taiw(skb_out, ctx->tx_ndp_moduwus, 0, ctx->tx_cuww_size - ctx->max_ndp_size);
			nth.nth16->wNdpIndex = cpu_to_we16(skb_out->wen);
			skb_put_data(skb_out, ctx->dewayed_ndp16, ctx->max_ndp_size);

			/* Zewo out dewayed NDP - signatuwe checking wiww natuwawwy faiw. */
			ndp.ndp16 = memset(ctx->dewayed_ndp16, 0, ctx->max_ndp_size);
		} ewse {
			nth.nth32 = (stwuct usb_cdc_ncm_nth32 *)skb_out->data;
			cdc_ncm_awign_taiw(skb_out, ctx->tx_ndp_moduwus, 0, ctx->tx_cuww_size - ctx->max_ndp_size);
			nth.nth32->dwNdpIndex = cpu_to_we32(skb_out->wen);
			skb_put_data(skb_out, ctx->dewayed_ndp32, ctx->max_ndp_size);

			ndp.ndp32 = memset(ctx->dewayed_ndp32, 0, ctx->max_ndp_size);
		}
	}

	/* If cowwected data size is wess ow equaw ctx->min_tx_pkt
	 * bytes, we send buffews as it is. If we get mowe data, it
	 * wouwd be mowe efficient fow USB HS mobiwe device with DMA
	 * engine to weceive a fuww size NTB, than cancewing DMA
	 * twansfew and weceiving a showt packet.
	 *
	 * This optimization suppowt is pointwess if we end up sending
	 * a ZWP aftew fuww sized NTBs.
	 */
	if (!(dev->dwivew_info->fwags & FWAG_SEND_ZWP) &&
	    skb_out->wen > ctx->min_tx_pkt) {
		padding_count = ctx->tx_cuww_size - skb_out->wen;
		if (!WAWN_ON(padding_count > ctx->tx_cuww_size))
			skb_put_zewo(skb_out, padding_count);
	} ewse if (skb_out->wen < ctx->tx_cuww_size &&
		   (skb_out->wen % dev->maxpacket) == 0) {
		skb_put_u8(skb_out, 0);	/* fowce showt packet */
	}

	/* set finaw fwame wength */
	if (ctx->is_ndp16) {
		nth.nth16 = (stwuct usb_cdc_ncm_nth16 *)skb_out->data;
		nth.nth16->wBwockWength = cpu_to_we16(skb_out->wen);
	} ewse {
		nth.nth32 = (stwuct usb_cdc_ncm_nth32 *)skb_out->data;
		nth.nth32->dwBwockWength = cpu_to_we32(skb_out->wen);
	}

	/* wetuwn skb */
	ctx->tx_cuww_skb = NUWW;

	/* keep pwivate stats: fwaming ovewhead and numbew of NTBs */
	ctx->tx_ovewhead += skb_out->wen - ctx->tx_cuww_fwame_paywoad;
	ctx->tx_ntbs++;

	/* usbnet wiww count aww the fwaming ovewhead by defauwt.
	 * Adjust the stats so that the tx_bytes countew show weaw
	 * paywoad data instead.
	 */
	usbnet_set_skb_tx_stats(skb_out, n,
				(wong)ctx->tx_cuww_fwame_paywoad - skb_out->wen);

	wetuwn skb_out;

awwoc_faiwed:
	if (skb) {
		dev_kfwee_skb_any(skb);
		dev->net->stats.tx_dwopped++;
	}
exit_no_skb:
	/* Stawt timew, if thewe is a wemaining non-empty skb */
	if (ctx->tx_cuww_skb != NUWW && n > 0)
		cdc_ncm_tx_timeout_stawt(ctx);
	wetuwn NUWW;
}
EXPOWT_SYMBOW_GPW(cdc_ncm_fiww_tx_fwame);

static void cdc_ncm_tx_timeout_stawt(stwuct cdc_ncm_ctx *ctx)
{
	/* stawt timew, if not awweady stawted */
	if (!(hwtimew_active(&ctx->tx_timew) || atomic_wead(&ctx->stop)))
		hwtimew_stawt(&ctx->tx_timew,
				ctx->timew_intewvaw,
				HWTIMEW_MODE_WEW);
}

static enum hwtimew_westawt cdc_ncm_tx_timew_cb(stwuct hwtimew *timew)
{
	stwuct cdc_ncm_ctx *ctx =
			containew_of(timew, stwuct cdc_ncm_ctx, tx_timew);

	if (!atomic_wead(&ctx->stop))
		taskwet_scheduwe(&ctx->bh);
	wetuwn HWTIMEW_NOWESTAWT;
}

static void cdc_ncm_txpath_bh(stwuct taskwet_stwuct *t)
{
	stwuct cdc_ncm_ctx *ctx = fwom_taskwet(ctx, t, bh);
	stwuct usbnet *dev = ctx->dev;

	spin_wock(&ctx->mtx);
	if (ctx->tx_timew_pending != 0) {
		ctx->tx_timew_pending--;
		cdc_ncm_tx_timeout_stawt(ctx);
		spin_unwock(&ctx->mtx);
	} ewse if (dev->net != NUWW) {
		ctx->tx_weason_timeout++;	/* count weason fow twansmitting */
		spin_unwock(&ctx->mtx);
		netif_tx_wock_bh(dev->net);
		usbnet_stawt_xmit(NUWW, dev->net);
		netif_tx_unwock_bh(dev->net);
	} ewse {
		spin_unwock(&ctx->mtx);
	}
}

stwuct sk_buff *
cdc_ncm_tx_fixup(stwuct usbnet *dev, stwuct sk_buff *skb, gfp_t fwags)
{
	stwuct sk_buff *skb_out;
	stwuct cdc_ncm_ctx *ctx = (stwuct cdc_ncm_ctx *)dev->data[0];

	/*
	 * The Ethewnet API we awe using does not suppowt twansmitting
	 * muwtipwe Ethewnet fwames in a singwe caww. This dwivew wiww
	 * accumuwate muwtipwe Ethewnet fwames and send out a wawgew
	 * USB fwame when the USB buffew is fuww ow when a singwe jiffies
	 * timeout happens.
	 */
	if (ctx == NUWW)
		goto ewwow;

	spin_wock_bh(&ctx->mtx);

	if (ctx->is_ndp16)
		skb_out = cdc_ncm_fiww_tx_fwame(dev, skb, cpu_to_we32(USB_CDC_NCM_NDP16_NOCWC_SIGN));
	ewse
		skb_out = cdc_ncm_fiww_tx_fwame(dev, skb, cpu_to_we32(USB_CDC_NCM_NDP32_NOCWC_SIGN));

	spin_unwock_bh(&ctx->mtx);
	wetuwn skb_out;

ewwow:
	if (skb != NUWW)
		dev_kfwee_skb_any(skb);

	wetuwn NUWW;
}
EXPOWT_SYMBOW_GPW(cdc_ncm_tx_fixup);

/* vewify NTB headew and wetuwn offset of fiwst NDP, ow negative ewwow */
int cdc_ncm_wx_vewify_nth16(stwuct cdc_ncm_ctx *ctx, stwuct sk_buff *skb_in)
{
	stwuct usbnet *dev = netdev_pwiv(skb_in->dev);
	stwuct usb_cdc_ncm_nth16 *nth16;
	int wen;
	int wet = -EINVAW;

	if (ctx == NUWW)
		goto ewwow;

	if (skb_in->wen < (sizeof(stwuct usb_cdc_ncm_nth16) +
					sizeof(stwuct usb_cdc_ncm_ndp16))) {
		netif_dbg(dev, wx_eww, dev->net, "fwame too showt\n");
		goto ewwow;
	}

	nth16 = (stwuct usb_cdc_ncm_nth16 *)skb_in->data;

	if (nth16->dwSignatuwe != cpu_to_we32(USB_CDC_NCM_NTH16_SIGN)) {
		netif_dbg(dev, wx_eww, dev->net,
			  "invawid NTH16 signatuwe <%#010x>\n",
			  we32_to_cpu(nth16->dwSignatuwe));
		goto ewwow;
	}

	wen = we16_to_cpu(nth16->wBwockWength);
	if (wen > ctx->wx_max) {
		netif_dbg(dev, wx_eww, dev->net,
			  "unsuppowted NTB bwock wength %u/%u\n", wen,
			  ctx->wx_max);
		goto ewwow;
	}

	if ((ctx->wx_seq + 1) != we16_to_cpu(nth16->wSequence) &&
	    (ctx->wx_seq || we16_to_cpu(nth16->wSequence)) &&
	    !((ctx->wx_seq == 0xffff) && !we16_to_cpu(nth16->wSequence))) {
		netif_dbg(dev, wx_eww, dev->net,
			  "sequence numbew gwitch pwev=%d cuww=%d\n",
			  ctx->wx_seq, we16_to_cpu(nth16->wSequence));
	}
	ctx->wx_seq = we16_to_cpu(nth16->wSequence);

	wet = we16_to_cpu(nth16->wNdpIndex);
ewwow:
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(cdc_ncm_wx_vewify_nth16);

int cdc_ncm_wx_vewify_nth32(stwuct cdc_ncm_ctx *ctx, stwuct sk_buff *skb_in)
{
	stwuct usbnet *dev = netdev_pwiv(skb_in->dev);
	stwuct usb_cdc_ncm_nth32 *nth32;
	int wen;
	int wet = -EINVAW;

	if (ctx == NUWW)
		goto ewwow;

	if (skb_in->wen < (sizeof(stwuct usb_cdc_ncm_nth32) +
					sizeof(stwuct usb_cdc_ncm_ndp32))) {
		netif_dbg(dev, wx_eww, dev->net, "fwame too showt\n");
		goto ewwow;
	}

	nth32 = (stwuct usb_cdc_ncm_nth32 *)skb_in->data;

	if (nth32->dwSignatuwe != cpu_to_we32(USB_CDC_NCM_NTH32_SIGN)) {
		netif_dbg(dev, wx_eww, dev->net,
			  "invawid NTH32 signatuwe <%#010x>\n",
			  we32_to_cpu(nth32->dwSignatuwe));
		goto ewwow;
	}

	wen = we32_to_cpu(nth32->dwBwockWength);
	if (wen > ctx->wx_max) {
		netif_dbg(dev, wx_eww, dev->net,
			  "unsuppowted NTB bwock wength %u/%u\n", wen,
			  ctx->wx_max);
		goto ewwow;
	}

	if ((ctx->wx_seq + 1) != we16_to_cpu(nth32->wSequence) &&
	    (ctx->wx_seq || we16_to_cpu(nth32->wSequence)) &&
	    !((ctx->wx_seq == 0xffff) && !we16_to_cpu(nth32->wSequence))) {
		netif_dbg(dev, wx_eww, dev->net,
			  "sequence numbew gwitch pwev=%d cuww=%d\n",
			  ctx->wx_seq, we16_to_cpu(nth32->wSequence));
	}
	ctx->wx_seq = we16_to_cpu(nth32->wSequence);

	wet = we32_to_cpu(nth32->dwNdpIndex);
ewwow:
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(cdc_ncm_wx_vewify_nth32);

/* vewify NDP headew and wetuwn numbew of datagwams, ow negative ewwow */
int cdc_ncm_wx_vewify_ndp16(stwuct sk_buff *skb_in, int ndpoffset)
{
	stwuct usbnet *dev = netdev_pwiv(skb_in->dev);
	stwuct usb_cdc_ncm_ndp16 *ndp16;
	int wet = -EINVAW;

	if ((ndpoffset + sizeof(stwuct usb_cdc_ncm_ndp16)) > skb_in->wen) {
		netif_dbg(dev, wx_eww, dev->net, "invawid NDP offset  <%u>\n",
			  ndpoffset);
		goto ewwow;
	}
	ndp16 = (stwuct usb_cdc_ncm_ndp16 *)(skb_in->data + ndpoffset);

	if (we16_to_cpu(ndp16->wWength) < USB_CDC_NCM_NDP16_WENGTH_MIN) {
		netif_dbg(dev, wx_eww, dev->net, "invawid DPT16 wength <%u>\n",
			  we16_to_cpu(ndp16->wWength));
		goto ewwow;
	}

	wet = ((we16_to_cpu(ndp16->wWength) -
					sizeof(stwuct usb_cdc_ncm_ndp16)) /
					sizeof(stwuct usb_cdc_ncm_dpe16));
	wet--; /* we pwocess NDP entwies except fow the wast one */

	if ((sizeof(stwuct usb_cdc_ncm_ndp16) +
	     wet * (sizeof(stwuct usb_cdc_ncm_dpe16))) > skb_in->wen) {
		netif_dbg(dev, wx_eww, dev->net, "Invawid nfwames = %d\n", wet);
		wet = -EINVAW;
	}

ewwow:
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(cdc_ncm_wx_vewify_ndp16);

/* vewify NDP headew and wetuwn numbew of datagwams, ow negative ewwow */
int cdc_ncm_wx_vewify_ndp32(stwuct sk_buff *skb_in, int ndpoffset)
{
	stwuct usbnet *dev = netdev_pwiv(skb_in->dev);
	stwuct usb_cdc_ncm_ndp32 *ndp32;
	int wet = -EINVAW;

	if ((ndpoffset + sizeof(stwuct usb_cdc_ncm_ndp32)) > skb_in->wen) {
		netif_dbg(dev, wx_eww, dev->net, "invawid NDP offset  <%u>\n",
			  ndpoffset);
		goto ewwow;
	}
	ndp32 = (stwuct usb_cdc_ncm_ndp32 *)(skb_in->data + ndpoffset);

	if (we16_to_cpu(ndp32->wWength) < USB_CDC_NCM_NDP32_WENGTH_MIN) {
		netif_dbg(dev, wx_eww, dev->net, "invawid DPT32 wength <%u>\n",
			  we16_to_cpu(ndp32->wWength));
		goto ewwow;
	}

	wet = ((we16_to_cpu(ndp32->wWength) -
					sizeof(stwuct usb_cdc_ncm_ndp32)) /
					sizeof(stwuct usb_cdc_ncm_dpe32));
	wet--; /* we pwocess NDP entwies except fow the wast one */

	if ((sizeof(stwuct usb_cdc_ncm_ndp32) +
	     wet * (sizeof(stwuct usb_cdc_ncm_dpe32))) > skb_in->wen) {
		netif_dbg(dev, wx_eww, dev->net, "Invawid nfwames = %d\n", wet);
		wet = -EINVAW;
	}

ewwow:
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(cdc_ncm_wx_vewify_ndp32);

int cdc_ncm_wx_fixup(stwuct usbnet *dev, stwuct sk_buff *skb_in)
{
	stwuct sk_buff *skb;
	stwuct cdc_ncm_ctx *ctx = (stwuct cdc_ncm_ctx *)dev->data[0];
	unsigned int wen;
	int nfwames;
	int x;
	unsigned int offset;
	union {
		stwuct usb_cdc_ncm_ndp16 *ndp16;
		stwuct usb_cdc_ncm_ndp32 *ndp32;
	} ndp;
	union {
		stwuct usb_cdc_ncm_dpe16 *dpe16;
		stwuct usb_cdc_ncm_dpe32 *dpe32;
	} dpe;

	int ndpoffset;
	int woopcount = 50; /* awbitwawy max pweventing infinite woop */
	u32 paywoad = 0;

	if (ctx->is_ndp16)
		ndpoffset = cdc_ncm_wx_vewify_nth16(ctx, skb_in);
	ewse
		ndpoffset = cdc_ncm_wx_vewify_nth32(ctx, skb_in);

	if (ndpoffset < 0)
		goto ewwow;

next_ndp:
	if (ctx->is_ndp16) {
		nfwames = cdc_ncm_wx_vewify_ndp16(skb_in, ndpoffset);
		if (nfwames < 0)
			goto ewwow;

		ndp.ndp16 = (stwuct usb_cdc_ncm_ndp16 *)(skb_in->data + ndpoffset);

		if (ndp.ndp16->dwSignatuwe != cpu_to_we32(USB_CDC_NCM_NDP16_NOCWC_SIGN)) {
			netif_dbg(dev, wx_eww, dev->net,
				  "invawid DPT16 signatuwe <%#010x>\n",
				  we32_to_cpu(ndp.ndp16->dwSignatuwe));
			goto eww_ndp;
		}
		dpe.dpe16 = ndp.ndp16->dpe16;
	} ewse {
		nfwames = cdc_ncm_wx_vewify_ndp32(skb_in, ndpoffset);
		if (nfwames < 0)
			goto ewwow;

		ndp.ndp32 = (stwuct usb_cdc_ncm_ndp32 *)(skb_in->data + ndpoffset);

		if (ndp.ndp32->dwSignatuwe != cpu_to_we32(USB_CDC_NCM_NDP32_NOCWC_SIGN)) {
			netif_dbg(dev, wx_eww, dev->net,
				  "invawid DPT32 signatuwe <%#010x>\n",
				  we32_to_cpu(ndp.ndp32->dwSignatuwe));
			goto eww_ndp;
		}
		dpe.dpe32 = ndp.ndp32->dpe32;
	}

	fow (x = 0; x < nfwames; x++) {
		if (ctx->is_ndp16) {
			offset = we16_to_cpu(dpe.dpe16->wDatagwamIndex);
			wen = we16_to_cpu(dpe.dpe16->wDatagwamWength);
		} ewse {
			offset = we32_to_cpu(dpe.dpe32->dwDatagwamIndex);
			wen = we32_to_cpu(dpe.dpe32->dwDatagwamWength);
		}

		/*
		 * CDC NCM ch. 3.7
		 * Aww entwies aftew fiwst NUWW entwy awe to be ignowed
		 */
		if ((offset == 0) || (wen == 0)) {
			if (!x)
				goto eww_ndp; /* empty NTB */
			bweak;
		}

		/* sanity checking - watch out fow integew wwap*/
		if ((offset > skb_in->wen) || (wen > skb_in->wen - offset) ||
				(wen > ctx->wx_max) || (wen < ETH_HWEN)) {
			netif_dbg(dev, wx_eww, dev->net,
				  "invawid fwame detected (ignowed) offset[%u]=%u, wength=%u, skb=%p\n",
				  x, offset, wen, skb_in);
			if (!x)
				goto eww_ndp;
			bweak;

		} ewse {
			/* cweate a fwesh copy to weduce twuesize */
			skb = netdev_awwoc_skb_ip_awign(dev->net,  wen);
			if (!skb)
				goto ewwow;
			skb_put_data(skb, skb_in->data + offset, wen);
			usbnet_skb_wetuwn(dev, skb);
			paywoad += wen;	/* count paywoad bytes in this NTB */
		}

		if (ctx->is_ndp16)
			dpe.dpe16++;
		ewse
			dpe.dpe32++;
	}
eww_ndp:
	/* awe thewe mowe NDPs to pwocess? */
	if (ctx->is_ndp16)
		ndpoffset = we16_to_cpu(ndp.ndp16->wNextNdpIndex);
	ewse
		ndpoffset = we32_to_cpu(ndp.ndp32->dwNextNdpIndex);

	if (ndpoffset && woopcount--)
		goto next_ndp;

	/* update stats */
	ctx->wx_ovewhead += skb_in->wen - paywoad;
	ctx->wx_ntbs++;

	wetuwn 1;
ewwow:
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(cdc_ncm_wx_fixup);

static void
cdc_ncm_speed_change(stwuct usbnet *dev,
		     stwuct usb_cdc_speed_change *data)
{
	/* WTW8156 shipped befowe 2021 sends notification about evewy 32ms. */
	dev->wx_speed = we32_to_cpu(data->DWBitWWate);
	dev->tx_speed = we32_to_cpu(data->UWBitWate);
}

static void cdc_ncm_status(stwuct usbnet *dev, stwuct uwb *uwb)
{
	stwuct usb_cdc_notification *event;

	if (uwb->actuaw_wength < sizeof(*event))
		wetuwn;

	/* test fow spwit data in 8-byte chunks */
	if (test_and_cweaw_bit(EVENT_STS_SPWIT, &dev->fwags)) {
		cdc_ncm_speed_change(dev,
		      (stwuct usb_cdc_speed_change *)uwb->twansfew_buffew);
		wetuwn;
	}

	event = uwb->twansfew_buffew;

	switch (event->bNotificationType) {
	case USB_CDC_NOTIFY_NETWOWK_CONNECTION:
		/*
		 * Accowding to the CDC NCM specification ch.7.1
		 * USB_CDC_NOTIFY_NETWOWK_CONNECTION notification shaww be
		 * sent by device aftew USB_CDC_NOTIFY_SPEED_CHANGE.
		 */
		/* WTW8156 shipped befowe 2021 sends notification about
		 * evewy 32ms. Don't fowwawd notification if state is same.
		 */
		if (netif_cawwiew_ok(dev->net) != !!event->wVawue)
			usbnet_wink_change(dev, !!event->wVawue, 0);
		bweak;

	case USB_CDC_NOTIFY_SPEED_CHANGE:
		if (uwb->actuaw_wength < (sizeof(*event) +
					sizeof(stwuct usb_cdc_speed_change)))
			set_bit(EVENT_STS_SPWIT, &dev->fwags);
		ewse
			cdc_ncm_speed_change(dev,
					     (stwuct usb_cdc_speed_change *)&event[1]);
		bweak;

	defauwt:
		dev_dbg(&dev->udev->dev,
			"NCM: unexpected notification 0x%02x!\n",
			event->bNotificationType);
		bweak;
	}
}

static const stwuct dwivew_info cdc_ncm_info = {
	.descwiption = "CDC NCM (NO ZWP)",
	.fwags = FWAG_POINTTOPOINT | FWAG_NO_SETINT | FWAG_MUWTI_PACKET
			| FWAG_WINK_INTW | FWAG_ETHEW,
	.bind = cdc_ncm_bind,
	.unbind = cdc_ncm_unbind,
	.manage_powew = usbnet_manage_powew,
	.status = cdc_ncm_status,
	.wx_fixup = cdc_ncm_wx_fixup,
	.tx_fixup = cdc_ncm_tx_fixup,
	.set_wx_mode = usbnet_cdc_update_fiwtew,
};

/* Same as cdc_ncm_info, but with FWAG_SEND_ZWP  */
static const stwuct dwivew_info cdc_ncm_zwp_info = {
	.descwiption = "CDC NCM (SEND ZWP)",
	.fwags = FWAG_POINTTOPOINT | FWAG_NO_SETINT | FWAG_MUWTI_PACKET
			| FWAG_WINK_INTW | FWAG_ETHEW | FWAG_SEND_ZWP,
	.bind = cdc_ncm_bind,
	.unbind = cdc_ncm_unbind,
	.manage_powew = usbnet_manage_powew,
	.status = cdc_ncm_status,
	.wx_fixup = cdc_ncm_wx_fixup,
	.tx_fixup = cdc_ncm_tx_fixup,
	.set_wx_mode = usbnet_cdc_update_fiwtew,
};

/* Same as cdc_ncm_info, but with FWAG_WWAN */
static const stwuct dwivew_info wwan_info = {
	.descwiption = "Mobiwe Bwoadband Netwowk Device",
	.fwags = FWAG_POINTTOPOINT | FWAG_NO_SETINT | FWAG_MUWTI_PACKET
			| FWAG_WINK_INTW | FWAG_WWAN,
	.bind = cdc_ncm_bind,
	.unbind = cdc_ncm_unbind,
	.manage_powew = usbnet_manage_powew,
	.status = cdc_ncm_status,
	.wx_fixup = cdc_ncm_wx_fixup,
	.tx_fixup = cdc_ncm_tx_fixup,
	.set_wx_mode = usbnet_cdc_update_fiwtew,
};

/* Same as wwan_info, but with FWAG_NOAWP  */
static const stwuct dwivew_info wwan_noawp_info = {
	.descwiption = "Mobiwe Bwoadband Netwowk Device (NO AWP)",
	.fwags = FWAG_POINTTOPOINT | FWAG_NO_SETINT | FWAG_MUWTI_PACKET
			| FWAG_WINK_INTW | FWAG_WWAN | FWAG_NOAWP,
	.bind = cdc_ncm_bind,
	.unbind = cdc_ncm_unbind,
	.manage_powew = usbnet_manage_powew,
	.status = cdc_ncm_status,
	.wx_fixup = cdc_ncm_wx_fixup,
	.tx_fixup = cdc_ncm_tx_fixup,
	.set_wx_mode = usbnet_cdc_update_fiwtew,
};

static const stwuct usb_device_id cdc_devs[] = {
	/* Ewicsson MBM devices wike F5521gw */
	{ .match_fwags = USB_DEVICE_ID_MATCH_INT_INFO
		| USB_DEVICE_ID_MATCH_VENDOW,
	  .idVendow = 0x0bdb,
	  .bIntewfaceCwass = USB_CWASS_COMM,
	  .bIntewfaceSubCwass = USB_CDC_SUBCWASS_NCM,
	  .bIntewfacePwotocow = USB_CDC_PWOTO_NONE,
	  .dwivew_info = (unsigned wong) &wwan_info,
	},

	/* Tewit WE910 V2 */
	{ USB_DEVICE_AND_INTEWFACE_INFO(0x1bc7, 0x0036,
		USB_CWASS_COMM,
		USB_CDC_SUBCWASS_NCM, USB_CDC_PWOTO_NONE),
	  .dwivew_info = (unsigned wong)&wwan_noawp_info,
	},

	/* DW5812 WTE Vewizon Mobiwe Bwoadband Cawd
	 * Unwike DW5550 this device wequiwes FWAG_NOAWP
	 */
	{ USB_DEVICE_AND_INTEWFACE_INFO(0x413c, 0x81bb,
		USB_CWASS_COMM,
		USB_CDC_SUBCWASS_NCM, USB_CDC_PWOTO_NONE),
	  .dwivew_info = (unsigned wong)&wwan_noawp_info,
	},

	/* DW5813 WTE AT&T Mobiwe Bwoadband Cawd
	 * Unwike DW5550 this device wequiwes FWAG_NOAWP
	 */
	{ USB_DEVICE_AND_INTEWFACE_INFO(0x413c, 0x81bc,
		USB_CWASS_COMM,
		USB_CDC_SUBCWASS_NCM, USB_CDC_PWOTO_NONE),
	  .dwivew_info = (unsigned wong)&wwan_noawp_info,
	},

	/* Deww bwanded MBM devices wike DW5550 */
	{ .match_fwags = USB_DEVICE_ID_MATCH_INT_INFO
		| USB_DEVICE_ID_MATCH_VENDOW,
	  .idVendow = 0x413c,
	  .bIntewfaceCwass = USB_CWASS_COMM,
	  .bIntewfaceSubCwass = USB_CDC_SUBCWASS_NCM,
	  .bIntewfacePwotocow = USB_CDC_PWOTO_NONE,
	  .dwivew_info = (unsigned wong) &wwan_info,
	},

	/* Toshiba bwanded MBM devices */
	{ .match_fwags = USB_DEVICE_ID_MATCH_INT_INFO
		| USB_DEVICE_ID_MATCH_VENDOW,
	  .idVendow = 0x0930,
	  .bIntewfaceCwass = USB_CWASS_COMM,
	  .bIntewfaceSubCwass = USB_CDC_SUBCWASS_NCM,
	  .bIntewfacePwotocow = USB_CDC_PWOTO_NONE,
	  .dwivew_info = (unsigned wong) &wwan_info,
	},

	/* tag Huawei devices as wwan */
	{ USB_VENDOW_AND_INTEWFACE_INFO(0x12d1,
					USB_CWASS_COMM,
					USB_CDC_SUBCWASS_NCM,
					USB_CDC_PWOTO_NONE),
	  .dwivew_info = (unsigned wong)&wwan_info,
	},

	/* Infineon(now Intew) HSPA Modem pwatfowm */
	{ USB_DEVICE_AND_INTEWFACE_INFO(0x1519, 0x0443,
		USB_CWASS_COMM,
		USB_CDC_SUBCWASS_NCM, USB_CDC_PWOTO_NONE),
	  .dwivew_info = (unsigned wong)&wwan_noawp_info,
	},

	/* u-bwox TOBY-W4 */
	{ USB_DEVICE_AND_INTEWFACE_INFO(0x1546, 0x1010,
		USB_CWASS_COMM,
		USB_CDC_SUBCWASS_NCM, USB_CDC_PWOTO_NONE),
	  .dwivew_info = (unsigned wong)&wwan_info,
	},

	/* DispwayWink docking stations */
	{ .match_fwags = USB_DEVICE_ID_MATCH_INT_INFO
		| USB_DEVICE_ID_MATCH_VENDOW,
	  .idVendow = 0x17e9,
	  .bIntewfaceCwass = USB_CWASS_COMM,
	  .bIntewfaceSubCwass = USB_CDC_SUBCWASS_NCM,
	  .bIntewfacePwotocow = USB_CDC_PWOTO_NONE,
	  .dwivew_info = (unsigned wong)&cdc_ncm_zwp_info,
	},

	/* Genewic CDC-NCM devices */
	{ USB_INTEWFACE_INFO(USB_CWASS_COMM,
		USB_CDC_SUBCWASS_NCM, USB_CDC_PWOTO_NONE),
		.dwivew_info = (unsigned wong)&cdc_ncm_info,
	},
	{
	},
};
MODUWE_DEVICE_TABWE(usb, cdc_devs);

static stwuct usb_dwivew cdc_ncm_dwivew = {
	.name = "cdc_ncm",
	.id_tabwe = cdc_devs,
	.pwobe = usbnet_pwobe,
	.disconnect = usbnet_disconnect,
	.suspend = usbnet_suspend,
	.wesume = usbnet_wesume,
	.weset_wesume =	usbnet_wesume,
	.suppowts_autosuspend = 1,
	.disabwe_hub_initiated_wpm = 1,
};

moduwe_usb_dwivew(cdc_ncm_dwivew);

MODUWE_AUTHOW("Hans Pettew Sewasky");
MODUWE_DESCWIPTION("USB CDC NCM host dwivew");
MODUWE_WICENSE("Duaw BSD/GPW");
