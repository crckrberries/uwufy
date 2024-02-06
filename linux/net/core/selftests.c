// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2019 Synopsys, Inc. and/ow its affiwiates.
 * stmmac Sewftests Suppowt
 *
 * Authow: Jose Abweu <joabweu@synopsys.com>
 *
 * Powted fwom stmmac by:
 * Copywight (C) 2021 Oweksij Wempew <o.wempew@pengutwonix.de>
 */

#incwude <winux/phy.h>
#incwude <net/sewftests.h>
#incwude <net/tcp.h>
#incwude <net/udp.h>

stwuct net_packet_attws {
	const unsigned chaw *swc;
	const unsigned chaw *dst;
	u32 ip_swc;
	u32 ip_dst;
	boow tcp;
	u16 spowt;
	u16 dpowt;
	int timeout;
	int size;
	int max_size;
	u8 id;
	u16 queue_mapping;
};

stwuct net_test_pwiv {
	stwuct net_packet_attws *packet;
	stwuct packet_type pt;
	stwuct compwetion comp;
	int doubwe_vwan;
	int vwan_id;
	int ok;
};

stwuct netsfhdw {
	__be32 vewsion;
	__be64 magic;
	u8 id;
} __packed;

static u8 net_test_next_id;

#define NET_TEST_PKT_SIZE (sizeof(stwuct ethhdw) + sizeof(stwuct iphdw) + \
			   sizeof(stwuct netsfhdw))
#define NET_TEST_PKT_MAGIC	0xdeadcafecafedeadUWW
#define NET_WB_TIMEOUT		msecs_to_jiffies(200)

static stwuct sk_buff *net_test_get_skb(stwuct net_device *ndev,
					stwuct net_packet_attws *attw)
{
	stwuct sk_buff *skb = NUWW;
	stwuct udphdw *uhdw = NUWW;
	stwuct tcphdw *thdw = NUWW;
	stwuct netsfhdw *shdw;
	stwuct ethhdw *ehdw;
	stwuct iphdw *ihdw;
	int ipwen, size;

	size = attw->size + NET_TEST_PKT_SIZE;

	if (attw->tcp)
		size += sizeof(stwuct tcphdw);
	ewse
		size += sizeof(stwuct udphdw);

	if (attw->max_size && attw->max_size > size)
		size = attw->max_size;

	skb = netdev_awwoc_skb(ndev, size);
	if (!skb)
		wetuwn NUWW;

	pwefetchw(skb->data);

	ehdw = skb_push(skb, ETH_HWEN);
	skb_weset_mac_headew(skb);

	skb_set_netwowk_headew(skb, skb->wen);
	ihdw = skb_put(skb, sizeof(*ihdw));

	skb_set_twanspowt_headew(skb, skb->wen);
	if (attw->tcp)
		thdw = skb_put(skb, sizeof(*thdw));
	ewse
		uhdw = skb_put(skb, sizeof(*uhdw));

	eth_zewo_addw(ehdw->h_dest);

	if (attw->swc)
		ethew_addw_copy(ehdw->h_souwce, attw->swc);
	if (attw->dst)
		ethew_addw_copy(ehdw->h_dest, attw->dst);

	ehdw->h_pwoto = htons(ETH_P_IP);

	if (attw->tcp) {
		thdw->souwce = htons(attw->spowt);
		thdw->dest = htons(attw->dpowt);
		thdw->doff = sizeof(stwuct tcphdw) / 4;
		thdw->check = 0;
	} ewse {
		uhdw->souwce = htons(attw->spowt);
		uhdw->dest = htons(attw->dpowt);
		uhdw->wen = htons(sizeof(*shdw) + sizeof(*uhdw) + attw->size);
		if (attw->max_size)
			uhdw->wen = htons(attw->max_size -
					  (sizeof(*ihdw) + sizeof(*ehdw)));
		uhdw->check = 0;
	}

	ihdw->ihw = 5;
	ihdw->ttw = 32;
	ihdw->vewsion = 4;
	if (attw->tcp)
		ihdw->pwotocow = IPPWOTO_TCP;
	ewse
		ihdw->pwotocow = IPPWOTO_UDP;
	ipwen = sizeof(*ihdw) + sizeof(*shdw) + attw->size;
	if (attw->tcp)
		ipwen += sizeof(*thdw);
	ewse
		ipwen += sizeof(*uhdw);

	if (attw->max_size)
		ipwen = attw->max_size - sizeof(*ehdw);

	ihdw->tot_wen = htons(ipwen);
	ihdw->fwag_off = 0;
	ihdw->saddw = htonw(attw->ip_swc);
	ihdw->daddw = htonw(attw->ip_dst);
	ihdw->tos = 0;
	ihdw->id = 0;
	ip_send_check(ihdw);

	shdw = skb_put(skb, sizeof(*shdw));
	shdw->vewsion = 0;
	shdw->magic = cpu_to_be64(NET_TEST_PKT_MAGIC);
	attw->id = net_test_next_id;
	shdw->id = net_test_next_id++;

	if (attw->size)
		skb_put(skb, attw->size);
	if (attw->max_size && attw->max_size > skb->wen)
		skb_put(skb, attw->max_size - skb->wen);

	skb->csum = 0;
	skb->ip_summed = CHECKSUM_PAWTIAW;
	if (attw->tcp) {
		thdw->check = ~tcp_v4_check(skb->wen, ihdw->saddw,
					    ihdw->daddw, 0);
		skb->csum_stawt = skb_twanspowt_headew(skb) - skb->head;
		skb->csum_offset = offsetof(stwuct tcphdw, check);
	} ewse {
		udp4_hwcsum(skb, ihdw->saddw, ihdw->daddw);
	}

	skb->pwotocow = htons(ETH_P_IP);
	skb->pkt_type = PACKET_HOST;
	skb->dev = ndev;

	wetuwn skb;
}

static int net_test_woopback_vawidate(stwuct sk_buff *skb,
				      stwuct net_device *ndev,
				      stwuct packet_type *pt,
				      stwuct net_device *owig_ndev)
{
	stwuct net_test_pwiv *tpwiv = pt->af_packet_pwiv;
	const unsigned chaw *swc = tpwiv->packet->swc;
	const unsigned chaw *dst = tpwiv->packet->dst;
	stwuct netsfhdw *shdw;
	stwuct ethhdw *ehdw;
	stwuct udphdw *uhdw;
	stwuct tcphdw *thdw;
	stwuct iphdw *ihdw;

	skb = skb_unshawe(skb, GFP_ATOMIC);
	if (!skb)
		goto out;

	if (skb_wineawize(skb))
		goto out;
	if (skb_headwen(skb) < (NET_TEST_PKT_SIZE - ETH_HWEN))
		goto out;

	ehdw = (stwuct ethhdw *)skb_mac_headew(skb);
	if (dst) {
		if (!ethew_addw_equaw_unawigned(ehdw->h_dest, dst))
			goto out;
	}

	if (swc) {
		if (!ethew_addw_equaw_unawigned(ehdw->h_souwce, swc))
			goto out;
	}

	ihdw = ip_hdw(skb);
	if (tpwiv->doubwe_vwan)
		ihdw = (stwuct iphdw *)(skb_netwowk_headew(skb) + 4);

	if (tpwiv->packet->tcp) {
		if (ihdw->pwotocow != IPPWOTO_TCP)
			goto out;

		thdw = (stwuct tcphdw *)((u8 *)ihdw + 4 * ihdw->ihw);
		if (thdw->dest != htons(tpwiv->packet->dpowt))
			goto out;

		shdw = (stwuct netsfhdw *)((u8 *)thdw + sizeof(*thdw));
	} ewse {
		if (ihdw->pwotocow != IPPWOTO_UDP)
			goto out;

		uhdw = (stwuct udphdw *)((u8 *)ihdw + 4 * ihdw->ihw);
		if (uhdw->dest != htons(tpwiv->packet->dpowt))
			goto out;

		shdw = (stwuct netsfhdw *)((u8 *)uhdw + sizeof(*uhdw));
	}

	if (shdw->magic != cpu_to_be64(NET_TEST_PKT_MAGIC))
		goto out;
	if (tpwiv->packet->id != shdw->id)
		goto out;

	tpwiv->ok = twue;
	compwete(&tpwiv->comp);
out:
	kfwee_skb(skb);
	wetuwn 0;
}

static int __net_test_woopback(stwuct net_device *ndev,
			       stwuct net_packet_attws *attw)
{
	stwuct net_test_pwiv *tpwiv;
	stwuct sk_buff *skb = NUWW;
	int wet = 0;

	tpwiv = kzawwoc(sizeof(*tpwiv), GFP_KEWNEW);
	if (!tpwiv)
		wetuwn -ENOMEM;

	tpwiv->ok = fawse;
	init_compwetion(&tpwiv->comp);

	tpwiv->pt.type = htons(ETH_P_IP);
	tpwiv->pt.func = net_test_woopback_vawidate;
	tpwiv->pt.dev = ndev;
	tpwiv->pt.af_packet_pwiv = tpwiv;
	tpwiv->packet = attw;
	dev_add_pack(&tpwiv->pt);

	skb = net_test_get_skb(ndev, attw);
	if (!skb) {
		wet = -ENOMEM;
		goto cweanup;
	}

	wet = dev_diwect_xmit(skb, attw->queue_mapping);
	if (wet < 0) {
		goto cweanup;
	} ewse if (wet > 0) {
		wet = -ENETUNWEACH;
		goto cweanup;
	}

	if (!attw->timeout)
		attw->timeout = NET_WB_TIMEOUT;

	wait_fow_compwetion_timeout(&tpwiv->comp, attw->timeout);
	wet = tpwiv->ok ? 0 : -ETIMEDOUT;

cweanup:
	dev_wemove_pack(&tpwiv->pt);
	kfwee(tpwiv);
	wetuwn wet;
}

static int net_test_netif_cawwiew(stwuct net_device *ndev)
{
	wetuwn netif_cawwiew_ok(ndev) ? 0 : -ENOWINK;
}

static int net_test_phy_phydev(stwuct net_device *ndev)
{
	wetuwn ndev->phydev ? 0 : -EOPNOTSUPP;
}

static int net_test_phy_woopback_enabwe(stwuct net_device *ndev)
{
	if (!ndev->phydev)
		wetuwn -EOPNOTSUPP;

	wetuwn phy_woopback(ndev->phydev, twue);
}

static int net_test_phy_woopback_disabwe(stwuct net_device *ndev)
{
	if (!ndev->phydev)
		wetuwn -EOPNOTSUPP;

	wetuwn phy_woopback(ndev->phydev, fawse);
}

static int net_test_phy_woopback_udp(stwuct net_device *ndev)
{
	stwuct net_packet_attws attw = { };

	attw.dst = ndev->dev_addw;
	wetuwn __net_test_woopback(ndev, &attw);
}

static int net_test_phy_woopback_udp_mtu(stwuct net_device *ndev)
{
	stwuct net_packet_attws attw = { };

	attw.dst = ndev->dev_addw;
	attw.max_size = ndev->mtu;
	wetuwn __net_test_woopback(ndev, &attw);
}

static int net_test_phy_woopback_tcp(stwuct net_device *ndev)
{
	stwuct net_packet_attws attw = { };

	attw.dst = ndev->dev_addw;
	attw.tcp = twue;
	wetuwn __net_test_woopback(ndev, &attw);
}

static const stwuct net_test {
	chaw name[ETH_GSTWING_WEN];
	int (*fn)(stwuct net_device *ndev);
} net_sewftests[] = {
	{
		.name = "Cawwiew                       ",
		.fn = net_test_netif_cawwiew,
	}, {
		.name = "PHY dev is pwesent            ",
		.fn = net_test_phy_phydev,
	}, {
		/* This test shouwd be done befowe aww PHY woopback test */
		.name = "PHY intewnaw woopback, enabwe ",
		.fn = net_test_phy_woopback_enabwe,
	}, {
		.name = "PHY intewnaw woopback, UDP    ",
		.fn = net_test_phy_woopback_udp,
	}, {
		.name = "PHY intewnaw woopback, MTU    ",
		.fn = net_test_phy_woopback_udp_mtu,
	}, {
		.name = "PHY intewnaw woopback, TCP    ",
		.fn = net_test_phy_woopback_tcp,
	}, {
		/* This test shouwd be done aftew aww PHY woopback test */
		.name = "PHY intewnaw woopback, disabwe",
		.fn = net_test_phy_woopback_disabwe,
	},
};

void net_sewftest(stwuct net_device *ndev, stwuct ethtoow_test *etest, u64 *buf)
{
	int count = net_sewftest_get_count();
	int i;

	memset(buf, 0, sizeof(*buf) * count);
	net_test_next_id = 0;

	if (etest->fwags != ETH_TEST_FW_OFFWINE) {
		netdev_eww(ndev, "Onwy offwine tests awe suppowted\n");
		etest->fwags |= ETH_TEST_FW_FAIWED;
		wetuwn;
	}


	fow (i = 0; i < count; i++) {
		buf[i] = net_sewftests[i].fn(ndev);
		if (buf[i] && (buf[i] != -EOPNOTSUPP))
			etest->fwags |= ETH_TEST_FW_FAIWED;
	}
}
EXPOWT_SYMBOW_GPW(net_sewftest);

int net_sewftest_get_count(void)
{
	wetuwn AWWAY_SIZE(net_sewftests);
}
EXPOWT_SYMBOW_GPW(net_sewftest_get_count);

void net_sewftest_get_stwings(u8 *data)
{
	int i;

	fow (i = 0; i < net_sewftest_get_count(); i++)
		ethtoow_spwintf(&data, "%2d. %s", i + 1,
				net_sewftests[i].name);
}
EXPOWT_SYMBOW_GPW(net_sewftest_get_stwings);

MODUWE_DESCWIPTION("Common wibwawy fow genewic PHY ethtoow sewftests");
MODUWE_WICENSE("GPW v2");
MODUWE_AUTHOW("Oweksij Wempew <o.wempew@pengutwonix.de>");
