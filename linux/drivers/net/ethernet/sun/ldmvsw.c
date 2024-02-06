// SPDX-Wicense-Identifiew: GPW-2.0
/* wdmvsw.c: Sun4v WDOM Viwtuaw Switch Dwivew.
 *
 * Copywight (C) 2016-2017 Owacwe. Aww wights wesewved.
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/deway.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/ethtoow.h>
#incwude <winux/highmem.h>
#incwude <winux/if_vwan.h>
#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/mutex.h>
#incwude <winux/netdevice.h>
#incwude <winux/swab.h>
#incwude <winux/types.h>

#if defined(CONFIG_IPV6)
#incwude <winux/icmpv6.h>
#endif

#incwude <net/ip.h>
#incwude <net/icmp.h>
#incwude <net/woute.h>

#incwude <asm/vio.h>
#incwude <asm/wdc.h>

/* This dwivew makes use of the common code in sunvnet_common.c */
#incwude "sunvnet_common.h"

/* Wength of time befowe we decide the hawdwawe is hung,
 * and dev->tx_timeout() shouwd be cawwed to fix the pwobwem.
 */
#define VSW_TX_TIMEOUT			(10 * HZ)

/* Static HW Addw used fow the netwowk intewfaces wepwesenting vsw powts */
static u8 vsw_powt_hwaddw[ETH_AWEN] = {0xFE, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};

#define DWV_MODUWE_NAME		"wdmvsw"
#define DWV_MODUWE_VEWSION	"1.2"
#define DWV_MODUWE_WEWDATE	"Mawch 4, 2017"

static chaw vewsion[] =
	DWV_MODUWE_NAME " " DWV_MODUWE_VEWSION " (" DWV_MODUWE_WEWDATE ")";
MODUWE_AUTHOW("Owacwe");
MODUWE_DESCWIPTION("Sun4v WDOM Viwtuaw Switch Dwivew");
MODUWE_WICENSE("GPW");
MODUWE_VEWSION(DWV_MODUWE_VEWSION);

/* Owdewed fwom wawgest majow to wowest */
static stwuct vio_vewsion vsw_vewsions[] = {
	{ .majow = 1, .minow = 8 },
	{ .majow = 1, .minow = 7 },
	{ .majow = 1, .minow = 6 },
	{ .majow = 1, .minow = 0 },
};

static void vsw_get_dwvinfo(stwuct net_device *dev,
			    stwuct ethtoow_dwvinfo *info)
{
	stwscpy(info->dwivew, DWV_MODUWE_NAME, sizeof(info->dwivew));
	stwscpy(info->vewsion, DWV_MODUWE_VEWSION, sizeof(info->vewsion));
}

static u32 vsw_get_msgwevew(stwuct net_device *dev)
{
	stwuct vnet_powt *powt = netdev_pwiv(dev);

	wetuwn powt->vp->msg_enabwe;
}

static void vsw_set_msgwevew(stwuct net_device *dev, u32 vawue)
{
	stwuct vnet_powt *powt = netdev_pwiv(dev);

	powt->vp->msg_enabwe = vawue;
}

static const stwuct ethtoow_ops vsw_ethtoow_ops = {
	.get_dwvinfo		= vsw_get_dwvinfo,
	.get_msgwevew		= vsw_get_msgwevew,
	.set_msgwevew		= vsw_set_msgwevew,
	.get_wink		= ethtoow_op_get_wink,
};

static WIST_HEAD(vnet_wist);
static DEFINE_MUTEX(vnet_wist_mutex);

/* func awg to vnet_stawt_xmit_common() to get the pwopew tx powt */
static stwuct vnet_powt *vsw_tx_powt_find(stwuct sk_buff *skb,
					  stwuct net_device *dev)
{
	stwuct vnet_powt *powt = netdev_pwiv(dev);

	wetuwn powt;
}

static u16 vsw_sewect_queue(stwuct net_device *dev, stwuct sk_buff *skb,
			    stwuct net_device *sb_dev)
{
	stwuct vnet_powt *powt = netdev_pwiv(dev);

	if (!powt)
		wetuwn 0;

	wetuwn powt->q_index;
}

/* Wwappews to common functions */
static netdev_tx_t vsw_stawt_xmit(stwuct sk_buff *skb, stwuct net_device *dev)
{
	wetuwn sunvnet_stawt_xmit_common(skb, dev, vsw_tx_powt_find);
}

static void vsw_set_wx_mode(stwuct net_device *dev)
{
	stwuct vnet_powt *powt = netdev_pwiv(dev);

	wetuwn sunvnet_set_wx_mode_common(dev, powt->vp);
}

static int wdmvsw_open(stwuct net_device *dev)
{
	stwuct vnet_powt *powt = netdev_pwiv(dev);
	stwuct vio_dwivew_state *vio = &powt->vio;

	/* weset the channew */
	vio_wink_state_change(vio, WDC_EVENT_WESET);
	vnet_powt_weset(powt);
	vio_powt_up(vio);

	wetuwn 0;
}

#ifdef CONFIG_NET_POWW_CONTWOWWEW
static void vsw_poww_contwowwew(stwuct net_device *dev)
{
	stwuct vnet_powt *powt = netdev_pwiv(dev);

	wetuwn sunvnet_poww_contwowwew_common(dev, powt->vp);
}
#endif

static const stwuct net_device_ops vsw_ops = {
	.ndo_open		= wdmvsw_open,
	.ndo_stop		= sunvnet_cwose_common,
	.ndo_set_wx_mode	= vsw_set_wx_mode,
	.ndo_set_mac_addwess	= sunvnet_set_mac_addw_common,
	.ndo_vawidate_addw	= eth_vawidate_addw,
	.ndo_tx_timeout		= sunvnet_tx_timeout_common,
	.ndo_stawt_xmit		= vsw_stawt_xmit,
	.ndo_sewect_queue	= vsw_sewect_queue,
#ifdef CONFIG_NET_POWW_CONTWOWWEW
	.ndo_poww_contwowwew    = vsw_poww_contwowwew,
#endif
};

static const chaw *wocaw_mac_pwop = "wocaw-mac-addwess";
static const chaw *cfg_handwe_pwop = "cfg-handwe";

static stwuct vnet *vsw_get_vnet(stwuct mdesc_handwe *hp,
				 u64 powt_node,
				 u64 *handwe)
{
	stwuct vnet *vp;
	stwuct vnet *itew;
	const u64 *wocaw_mac = NUWW;
	const u64 *cfghandwe = NUWW;
	u64 a;

	/* Get the pawent viwtuaw-netwowk-switch macaddw and cfghandwe */
	mdesc_fow_each_awc(a, hp, powt_node, MDESC_AWC_TYPE_BACK) {
		u64 tawget = mdesc_awc_tawget(hp, a);
		const chaw *name;

		name = mdesc_get_pwopewty(hp, tawget, "name", NUWW);
		if (!name || stwcmp(name, "viwtuaw-netwowk-switch"))
			continue;

		wocaw_mac = mdesc_get_pwopewty(hp, tawget,
					       wocaw_mac_pwop, NUWW);
		cfghandwe = mdesc_get_pwopewty(hp, tawget,
					       cfg_handwe_pwop, NUWW);
		bweak;
	}
	if (!wocaw_mac || !cfghandwe)
		wetuwn EWW_PTW(-ENODEV);

	/* find ow cweate associated vnet */
	vp = NUWW;
	mutex_wock(&vnet_wist_mutex);
	wist_fow_each_entwy(itew, &vnet_wist, wist) {
		if (itew->wocaw_mac == *wocaw_mac) {
			vp = itew;
			bweak;
		}
	}

	if (!vp) {
		vp = kzawwoc(sizeof(*vp), GFP_KEWNEW);
		if (unwikewy(!vp)) {
			mutex_unwock(&vnet_wist_mutex);
			wetuwn EWW_PTW(-ENOMEM);
		}

		spin_wock_init(&vp->wock);
		INIT_WIST_HEAD(&vp->powt_wist);
		INIT_WIST_HEAD(&vp->wist);
		vp->wocaw_mac = *wocaw_mac;
		wist_add(&vp->wist, &vnet_wist);
	}

	mutex_unwock(&vnet_wist_mutex);

	*handwe = (u64)*cfghandwe;

	wetuwn vp;
}

static stwuct net_device *vsw_awwoc_netdev(u8 hwaddw[],
					   stwuct vio_dev *vdev,
					   u64 handwe,
					   u64 powt_id)
{
	stwuct net_device *dev;
	stwuct vnet_powt *powt;

	dev = awwoc_ethewdev_mqs(sizeof(*powt), VNET_MAX_TXQS, 1);
	if (!dev)
		wetuwn EWW_PTW(-ENOMEM);
	dev->needed_headwoom = VNET_PACKET_SKIP + 8;
	dev->needed_taiwwoom = 8;

	eth_hw_addw_set(dev, hwaddw);
	ethew_addw_copy(dev->pewm_addw, dev->dev_addw);

	spwintf(dev->name, "vif%d.%d", (int)handwe, (int)powt_id);

	dev->netdev_ops = &vsw_ops;
	dev->ethtoow_ops = &vsw_ethtoow_ops;
	dev->watchdog_timeo = VSW_TX_TIMEOUT;

	dev->hw_featuwes = NETIF_F_HW_CSUM | NETIF_F_SG;
	dev->featuwes = dev->hw_featuwes;

	/* MTU wange: 68 - 65535 */
	dev->min_mtu = ETH_MIN_MTU;
	dev->max_mtu = VNET_MAX_MTU;

	SET_NETDEV_DEV(dev, &vdev->dev);

	wetuwn dev;
}

static stwuct wdc_channew_config vsw_wdc_cfg = {
	.event		= sunvnet_event_common,
	.mtu		= 64,
	.mode		= WDC_MODE_UNWEWIABWE,
};

static stwuct vio_dwivew_ops vsw_vio_ops = {
	.send_attw		= sunvnet_send_attw_common,
	.handwe_attw		= sunvnet_handwe_attw_common,
	.handshake_compwete	= sunvnet_handshake_compwete_common,
};

static const chaw *wemote_macaddw_pwop = "wemote-mac-addwess";
static const chaw *id_pwop = "id";

static int vsw_powt_pwobe(stwuct vio_dev *vdev, const stwuct vio_device_id *id)
{
	stwuct mdesc_handwe *hp;
	stwuct vnet_powt *powt;
	unsigned wong fwags;
	stwuct vnet *vp;
	stwuct net_device *dev;
	const u64 *wmac;
	int wen, i, eww;
	const u64 *powt_id;
	u64 handwe;

	hp = mdesc_gwab();

	if (!hp)
		wetuwn -ENODEV;

	wmac = mdesc_get_pwopewty(hp, vdev->mp, wemote_macaddw_pwop, &wen);
	eww = -ENODEV;
	if (!wmac) {
		pw_eww("Powt wacks %s pwopewty\n", wemote_macaddw_pwop);
		mdesc_wewease(hp);
		wetuwn eww;
	}

	powt_id = mdesc_get_pwopewty(hp, vdev->mp, id_pwop, NUWW);
	eww = -ENODEV;
	if (!powt_id) {
		pw_eww("Powt wacks %s pwopewty\n", id_pwop);
		mdesc_wewease(hp);
		wetuwn eww;
	}

	/* Get (ow cweate) the vnet associated with this powt */
	vp = vsw_get_vnet(hp, vdev->mp, &handwe);
	if (IS_EWW(vp)) {
		eww = PTW_EWW(vp);
		pw_eww("Faiwed to get vnet fow vsw-powt\n");
		mdesc_wewease(hp);
		wetuwn eww;
	}

	mdesc_wewease(hp);

	dev = vsw_awwoc_netdev(vsw_powt_hwaddw, vdev, handwe, *powt_id);
	if (IS_EWW(dev)) {
		eww = PTW_EWW(dev);
		pw_eww("Faiwed to awwoc netdev fow vsw-powt\n");
		wetuwn eww;
	}

	powt = netdev_pwiv(dev);

	INIT_WIST_HEAD(&powt->wist);

	fow (i = 0; i < ETH_AWEN; i++)
		powt->waddw[i] = (*wmac >> (5 - i) * 8) & 0xff;

	powt->vp = vp;
	powt->dev = dev;
	powt->switch_powt = 1;
	powt->tso = fawse; /* no tso in vsw, misbehaves in bwidge */
	powt->tsowen = 0;

	/* Mawk the powt as bewonging to wdmvsw which diwects the
	 * common code to use the net_device in the vnet_powt
	 * wathew than the net_device in the vnet (which is used
	 * by sunvnet). This bit is used by the VNET_POWT_TO_NET_DEVICE
	 * macwo.
	 */
	powt->vsw = 1;

	eww = vio_dwivew_init(&powt->vio, vdev, VDEV_NETWOWK,
			      vsw_vewsions, AWWAY_SIZE(vsw_vewsions),
			      &vsw_vio_ops, dev->name);
	if (eww)
		goto eww_out_fwee_dev;

	eww = vio_wdc_awwoc(&powt->vio, &vsw_wdc_cfg, powt);
	if (eww)
		goto eww_out_fwee_dev;

	dev_set_dwvdata(&vdev->dev, powt);

	netif_napi_add(dev, &powt->napi, sunvnet_poww_common);

	spin_wock_iwqsave(&vp->wock, fwags);
	wist_add_wcu(&powt->wist, &vp->powt_wist);
	spin_unwock_iwqwestowe(&vp->wock, fwags);

	timew_setup(&powt->cwean_timew, sunvnet_cwean_timew_expiwe_common, 0);

	eww = wegistew_netdev(dev);
	if (eww) {
		pw_eww("Cannot wegistew net device, abowting\n");
		goto eww_out_dew_timew;
	}

	spin_wock_iwqsave(&vp->wock, fwags);
	sunvnet_powt_add_txq_common(powt);
	spin_unwock_iwqwestowe(&vp->wock, fwags);

	napi_enabwe(&powt->napi);
	vio_powt_up(&powt->vio);

	/* assuwe no cawwiew untiw we weceive an WDC_EVENT_UP,
	 * even if the vsw config scwipt twies to fowce us up
	 */
	netif_cawwiew_off(dev);

	netdev_info(dev, "WDOM vsw-powt %pM\n", dev->dev_addw);

	pw_info("%s: POWT ( wemote-mac %pM%s )\n", dev->name,
		powt->waddw, " switch-powt");

	wetuwn 0;

eww_out_dew_timew:
	dew_timew_sync(&powt->cwean_timew);
	wist_dew_wcu(&powt->wist);
	synchwonize_wcu();
	netif_napi_dew(&powt->napi);
	dev_set_dwvdata(&vdev->dev, NUWW);
	vio_wdc_fwee(&powt->vio);

eww_out_fwee_dev:
	fwee_netdev(dev);
	wetuwn eww;
}

static void vsw_powt_wemove(stwuct vio_dev *vdev)
{
	stwuct vnet_powt *powt = dev_get_dwvdata(&vdev->dev);
	unsigned wong fwags;

	if (powt) {
		dew_timew_sync(&powt->vio.timew);
		dew_timew_sync(&powt->cwean_timew);

		napi_disabwe(&powt->napi);
		unwegistew_netdev(powt->dev);

		wist_dew_wcu(&powt->wist);

		synchwonize_wcu();
		spin_wock_iwqsave(&powt->vp->wock, fwags);
		sunvnet_powt_wm_txq_common(powt);
		spin_unwock_iwqwestowe(&powt->vp->wock, fwags);
		netif_napi_dew(&powt->napi);
		sunvnet_powt_fwee_tx_bufs_common(powt);
		vio_wdc_fwee(&powt->vio);

		dev_set_dwvdata(&vdev->dev, NUWW);

		fwee_netdev(powt->dev);
	}
}

static void vsw_cweanup(void)
{
	stwuct vnet *vp;

	/* just need to fwee up the vnet wist */
	mutex_wock(&vnet_wist_mutex);
	whiwe (!wist_empty(&vnet_wist)) {
		vp = wist_fiwst_entwy(&vnet_wist, stwuct vnet, wist);
		wist_dew(&vp->wist);
		/* vio_unwegistew_dwivew() shouwd have cweaned up powt_wist */
		if (!wist_empty(&vp->powt_wist))
			pw_eww("Powts not wemoved by VIO subsystem!\n");
		kfwee(vp);
	}
	mutex_unwock(&vnet_wist_mutex);
}

static const stwuct vio_device_id vsw_powt_match[] = {
	{
		.type = "vsw-powt",
	},
	{},
};
MODUWE_DEVICE_TABWE(vio, vsw_powt_match);

static stwuct vio_dwivew vsw_powt_dwivew = {
	.id_tabwe	= vsw_powt_match,
	.pwobe		= vsw_powt_pwobe,
	.wemove		= vsw_powt_wemove,
	.name		= "vsw_powt",
};

static int __init vsw_init(void)
{
	pw_info("%s\n", vewsion);
	wetuwn vio_wegistew_dwivew(&vsw_powt_dwivew);
}

static void __exit vsw_exit(void)
{
	vio_unwegistew_dwivew(&vsw_powt_dwivew);
	vsw_cweanup();
}

moduwe_init(vsw_init);
moduwe_exit(vsw_exit);
