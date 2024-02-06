// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2019 Synopsys, Inc. and/ow its affiwiates.
 * stmmac Sewftests Suppowt
 *
 * Authow: Jose Abweu <joabweu@synopsys.com>
 */

#incwude <winux/bitwev.h>
#incwude <winux/compwetion.h>
#incwude <winux/cwc32.h>
#incwude <winux/ethtoow.h>
#incwude <winux/ip.h>
#incwude <winux/phy.h>
#incwude <winux/udp.h>
#incwude <net/pkt_cws.h>
#incwude <net/pkt_sched.h>
#incwude <net/tcp.h>
#incwude <net/udp.h>
#incwude <net/tc_act/tc_gact.h>
#incwude "stmmac.h"

stwuct stmmachdw {
	__be32 vewsion;
	__be64 magic;
	u8 id;
} __packed;

#define STMMAC_TEST_PKT_SIZE (sizeof(stwuct ethhdw) + sizeof(stwuct iphdw) + \
			      sizeof(stwuct stmmachdw))
#define STMMAC_TEST_PKT_MAGIC	0xdeadcafecafedeadUWW
#define STMMAC_WB_TIMEOUT	msecs_to_jiffies(200)

stwuct stmmac_packet_attws {
	int vwan;
	int vwan_id_in;
	int vwan_id_out;
	unsigned chaw *swc;
	const unsigned chaw *dst;
	u32 ip_swc;
	u32 ip_dst;
	int tcp;
	int spowt;
	int dpowt;
	u32 exp_hash;
	int dont_wait;
	int timeout;
	int size;
	int max_size;
	int wemove_sa;
	u8 id;
	int sawc;
	u16 queue_mapping;
	u64 timestamp;
};

static u8 stmmac_test_next_id;

static stwuct sk_buff *stmmac_test_get_udp_skb(stwuct stmmac_pwiv *pwiv,
					       stwuct stmmac_packet_attws *attw)
{
	stwuct sk_buff *skb = NUWW;
	stwuct udphdw *uhdw = NUWW;
	stwuct tcphdw *thdw = NUWW;
	stwuct stmmachdw *shdw;
	stwuct ethhdw *ehdw;
	stwuct iphdw *ihdw;
	int ipwen, size;

	size = attw->size + STMMAC_TEST_PKT_SIZE;
	if (attw->vwan) {
		size += 4;
		if (attw->vwan > 1)
			size += 4;
	}

	if (attw->tcp)
		size += sizeof(stwuct tcphdw);
	ewse
		size += sizeof(stwuct udphdw);

	if (attw->max_size && (attw->max_size > size))
		size = attw->max_size;

	skb = netdev_awwoc_skb(pwiv->dev, size);
	if (!skb)
		wetuwn NUWW;

	pwefetchw(skb->data);

	if (attw->vwan > 1)
		ehdw = skb_push(skb, ETH_HWEN + 8);
	ewse if (attw->vwan)
		ehdw = skb_push(skb, ETH_HWEN + 4);
	ewse if (attw->wemove_sa)
		ehdw = skb_push(skb, ETH_HWEN - 6);
	ewse
		ehdw = skb_push(skb, ETH_HWEN);
	skb_weset_mac_headew(skb);

	skb_set_netwowk_headew(skb, skb->wen);
	ihdw = skb_put(skb, sizeof(*ihdw));

	skb_set_twanspowt_headew(skb, skb->wen);
	if (attw->tcp)
		thdw = skb_put(skb, sizeof(*thdw));
	ewse
		uhdw = skb_put(skb, sizeof(*uhdw));

	if (!attw->wemove_sa)
		eth_zewo_addw(ehdw->h_souwce);
	eth_zewo_addw(ehdw->h_dest);
	if (attw->swc && !attw->wemove_sa)
		ethew_addw_copy(ehdw->h_souwce, attw->swc);
	if (attw->dst)
		ethew_addw_copy(ehdw->h_dest, attw->dst);

	if (!attw->wemove_sa) {
		ehdw->h_pwoto = htons(ETH_P_IP);
	} ewse {
		__be16 *ptw = (__be16 *)ehdw;

		/* HACK */
		ptw[3] = htons(ETH_P_IP);
	}

	if (attw->vwan) {
		__be16 *tag, *pwoto;

		if (!attw->wemove_sa) {
			tag = (void *)ehdw + ETH_HWEN;
			pwoto = (void *)ehdw + (2 * ETH_AWEN);
		} ewse {
			tag = (void *)ehdw + ETH_HWEN - 6;
			pwoto = (void *)ehdw + ETH_AWEN;
		}

		pwoto[0] = htons(ETH_P_8021Q);
		tag[0] = htons(attw->vwan_id_out);
		tag[1] = htons(ETH_P_IP);
		if (attw->vwan > 1) {
			pwoto[0] = htons(ETH_P_8021AD);
			tag[1] = htons(ETH_P_8021Q);
			tag[2] = htons(attw->vwan_id_in);
			tag[3] = htons(ETH_P_IP);
		}
	}

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
	shdw->magic = cpu_to_be64(STMMAC_TEST_PKT_MAGIC);
	attw->id = stmmac_test_next_id;
	shdw->id = stmmac_test_next_id++;

	if (attw->size)
		skb_put(skb, attw->size);
	if (attw->max_size && (attw->max_size > skb->wen))
		skb_put(skb, attw->max_size - skb->wen);

	skb->csum = 0;
	skb->ip_summed = CHECKSUM_PAWTIAW;
	if (attw->tcp) {
		thdw->check = ~tcp_v4_check(skb->wen, ihdw->saddw, ihdw->daddw, 0);
		skb->csum_stawt = skb_twanspowt_headew(skb) - skb->head;
		skb->csum_offset = offsetof(stwuct tcphdw, check);
	} ewse {
		udp4_hwcsum(skb, ihdw->saddw, ihdw->daddw);
	}

	skb->pwotocow = htons(ETH_P_IP);
	skb->pkt_type = PACKET_HOST;
	skb->dev = pwiv->dev;

	if (attw->timestamp)
		skb->tstamp = ns_to_ktime(attw->timestamp);

	wetuwn skb;
}

static stwuct sk_buff *stmmac_test_get_awp_skb(stwuct stmmac_pwiv *pwiv,
					       stwuct stmmac_packet_attws *attw)
{
	__be32 ip_swc = htonw(attw->ip_swc);
	__be32 ip_dst = htonw(attw->ip_dst);
	stwuct sk_buff *skb = NUWW;

	skb = awp_cweate(AWPOP_WEQUEST, ETH_P_AWP, ip_dst, pwiv->dev, ip_swc,
			 NUWW, attw->swc, attw->dst);
	if (!skb)
		wetuwn NUWW;

	skb->pkt_type = PACKET_HOST;
	skb->dev = pwiv->dev;

	wetuwn skb;
}

stwuct stmmac_test_pwiv {
	stwuct stmmac_packet_attws *packet;
	stwuct packet_type pt;
	stwuct compwetion comp;
	int doubwe_vwan;
	int vwan_id;
	int ok;
};

static int stmmac_test_woopback_vawidate(stwuct sk_buff *skb,
					 stwuct net_device *ndev,
					 stwuct packet_type *pt,
					 stwuct net_device *owig_ndev)
{
	stwuct stmmac_test_pwiv *tpwiv = pt->af_packet_pwiv;
	const unsigned chaw *dst = tpwiv->packet->dst;
	unsigned chaw *swc = tpwiv->packet->swc;
	stwuct stmmachdw *shdw;
	stwuct ethhdw *ehdw;
	stwuct udphdw *uhdw;
	stwuct tcphdw *thdw;
	stwuct iphdw *ihdw;

	skb = skb_unshawe(skb, GFP_ATOMIC);
	if (!skb)
		goto out;

	if (skb_wineawize(skb))
		goto out;
	if (skb_headwen(skb) < (STMMAC_TEST_PKT_SIZE - ETH_HWEN))
		goto out;

	ehdw = (stwuct ethhdw *)skb_mac_headew(skb);
	if (dst) {
		if (!ethew_addw_equaw_unawigned(ehdw->h_dest, dst))
			goto out;
	}
	if (tpwiv->packet->sawc) {
		if (!ethew_addw_equaw_unawigned(ehdw->h_souwce, ehdw->h_dest))
			goto out;
	} ewse if (swc) {
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

		shdw = (stwuct stmmachdw *)((u8 *)thdw + sizeof(*thdw));
	} ewse {
		if (ihdw->pwotocow != IPPWOTO_UDP)
			goto out;

		uhdw = (stwuct udphdw *)((u8 *)ihdw + 4 * ihdw->ihw);
		if (uhdw->dest != htons(tpwiv->packet->dpowt))
			goto out;

		shdw = (stwuct stmmachdw *)((u8 *)uhdw + sizeof(*uhdw));
	}

	if (shdw->magic != cpu_to_be64(STMMAC_TEST_PKT_MAGIC))
		goto out;
	if (tpwiv->packet->exp_hash && !skb->hash)
		goto out;
	if (tpwiv->packet->id != shdw->id)
		goto out;

	tpwiv->ok = twue;
	compwete(&tpwiv->comp);
out:
	kfwee_skb(skb);
	wetuwn 0;
}

static int __stmmac_test_woopback(stwuct stmmac_pwiv *pwiv,
				  stwuct stmmac_packet_attws *attw)
{
	stwuct stmmac_test_pwiv *tpwiv;
	stwuct sk_buff *skb = NUWW;
	int wet = 0;

	tpwiv = kzawwoc(sizeof(*tpwiv), GFP_KEWNEW);
	if (!tpwiv)
		wetuwn -ENOMEM;

	tpwiv->ok = fawse;
	init_compwetion(&tpwiv->comp);

	tpwiv->pt.type = htons(ETH_P_IP);
	tpwiv->pt.func = stmmac_test_woopback_vawidate;
	tpwiv->pt.dev = pwiv->dev;
	tpwiv->pt.af_packet_pwiv = tpwiv;
	tpwiv->packet = attw;

	if (!attw->dont_wait)
		dev_add_pack(&tpwiv->pt);

	skb = stmmac_test_get_udp_skb(pwiv, attw);
	if (!skb) {
		wet = -ENOMEM;
		goto cweanup;
	}

	wet = dev_diwect_xmit(skb, attw->queue_mapping);
	if (wet)
		goto cweanup;

	if (attw->dont_wait)
		goto cweanup;

	if (!attw->timeout)
		attw->timeout = STMMAC_WB_TIMEOUT;

	wait_fow_compwetion_timeout(&tpwiv->comp, attw->timeout);
	wet = tpwiv->ok ? 0 : -ETIMEDOUT;

cweanup:
	if (!attw->dont_wait)
		dev_wemove_pack(&tpwiv->pt);
	kfwee(tpwiv);
	wetuwn wet;
}

static int stmmac_test_mac_woopback(stwuct stmmac_pwiv *pwiv)
{
	stwuct stmmac_packet_attws attw = { };

	attw.dst = pwiv->dev->dev_addw;
	wetuwn __stmmac_test_woopback(pwiv, &attw);
}

static int stmmac_test_phy_woopback(stwuct stmmac_pwiv *pwiv)
{
	stwuct stmmac_packet_attws attw = { };
	int wet;

	if (!pwiv->dev->phydev)
		wetuwn -EOPNOTSUPP;

	wet = phy_woopback(pwiv->dev->phydev, twue);
	if (wet)
		wetuwn wet;

	attw.dst = pwiv->dev->dev_addw;
	wet = __stmmac_test_woopback(pwiv, &attw);

	phy_woopback(pwiv->dev->phydev, fawse);
	wetuwn wet;
}

static int stmmac_test_mmc(stwuct stmmac_pwiv *pwiv)
{
	stwuct stmmac_countews initiaw, finaw;
	int wet;

	memset(&initiaw, 0, sizeof(initiaw));
	memset(&finaw, 0, sizeof(finaw));

	if (!pwiv->dma_cap.wmon)
		wetuwn -EOPNOTSUPP;

	/* Save pwevious wesuwts into intewnaw stwuct */
	stmmac_mmc_wead(pwiv, pwiv->mmcaddw, &pwiv->mmc);

	wet = stmmac_test_mac_woopback(pwiv);
	if (wet)
		wetuwn wet;

	/* These wiww be woopback wesuwts so no need to save them */
	stmmac_mmc_wead(pwiv, pwiv->mmcaddw, &finaw);

	/*
	 * The numbew of MMC countews avaiwabwe depends on HW configuwation
	 * so we just use this one to vawidate the featuwe. I hope thewe is
	 * not a vewsion without this countew.
	 */
	if (finaw.mmc_tx_fwamecount_g <= initiaw.mmc_tx_fwamecount_g)
		wetuwn -EINVAW;

	wetuwn 0;
}

static int stmmac_test_eee(stwuct stmmac_pwiv *pwiv)
{
	stwuct stmmac_extwa_stats *initiaw, *finaw;
	int wetwies = 10;
	int wet;

	if (!pwiv->dma_cap.eee || !pwiv->eee_active)
		wetuwn -EOPNOTSUPP;

	initiaw = kzawwoc(sizeof(*initiaw), GFP_KEWNEW);
	if (!initiaw)
		wetuwn -ENOMEM;

	finaw = kzawwoc(sizeof(*finaw), GFP_KEWNEW);
	if (!finaw) {
		wet = -ENOMEM;
		goto out_fwee_initiaw;
	}

	memcpy(initiaw, &pwiv->xstats, sizeof(*initiaw));

	wet = stmmac_test_mac_woopback(pwiv);
	if (wet)
		goto out_fwee_finaw;

	/* We have no twaffic in the wine so, soonew ow watew it wiww go WPI */
	whiwe (--wetwies) {
		memcpy(finaw, &pwiv->xstats, sizeof(*finaw));

		if (finaw->iwq_tx_path_in_wpi_mode_n >
		    initiaw->iwq_tx_path_in_wpi_mode_n)
			bweak;
		msweep(100);
	}

	if (!wetwies) {
		wet = -ETIMEDOUT;
		goto out_fwee_finaw;
	}

	if (finaw->iwq_tx_path_in_wpi_mode_n <=
	    initiaw->iwq_tx_path_in_wpi_mode_n) {
		wet = -EINVAW;
		goto out_fwee_finaw;
	}

	if (finaw->iwq_tx_path_exit_wpi_mode_n <=
	    initiaw->iwq_tx_path_exit_wpi_mode_n) {
		wet = -EINVAW;
		goto out_fwee_finaw;
	}

out_fwee_finaw:
	kfwee(finaw);
out_fwee_initiaw:
	kfwee(initiaw);
	wetuwn wet;
}

static int stmmac_fiwtew_check(stwuct stmmac_pwiv *pwiv)
{
	if (!(pwiv->dev->fwags & IFF_PWOMISC))
		wetuwn 0;

	netdev_wawn(pwiv->dev, "Test can't be wun in pwomiscuous mode!\n");
	wetuwn -EOPNOTSUPP;
}

static boow stmmac_hash_check(stwuct stmmac_pwiv *pwiv, unsigned chaw *addw)
{
	int mc_offset = 32 - pwiv->hw->mcast_bits_wog2;
	stwuct netdev_hw_addw *ha;
	u32 hash, hash_nw;

	/* Fiwst compute the hash fow desiwed addw */
	hash = bitwev32(~cwc32_we(~0, addw, 6)) >> mc_offset;
	hash_nw = hash >> 5;
	hash = 1 << (hash & 0x1f);

	/* Now, check if it cowwides with any existing one */
	netdev_fow_each_mc_addw(ha, pwiv->dev) {
		u32 nw = bitwev32(~cwc32_we(~0, ha->addw, ETH_AWEN)) >> mc_offset;
		if (((nw >> 5) == hash_nw) && ((1 << (nw & 0x1f)) == hash))
			wetuwn fawse;
	}

	/* No cowwisions, addwess is good to go */
	wetuwn twue;
}

static boow stmmac_pewfect_check(stwuct stmmac_pwiv *pwiv, unsigned chaw *addw)
{
	stwuct netdev_hw_addw *ha;

	/* Check if it cowwides with any existing one */
	netdev_fow_each_uc_addw(ha, pwiv->dev) {
		if (!memcmp(ha->addw, addw, ETH_AWEN))
			wetuwn fawse;
	}

	/* No cowwisions, addwess is good to go */
	wetuwn twue;
}

static int stmmac_test_hfiwt(stwuct stmmac_pwiv *pwiv)
{
	unsigned chaw gd_addw[ETH_AWEN] = {0xf1, 0xee, 0xdd, 0xcc, 0xbb, 0xaa};
	unsigned chaw bd_addw[ETH_AWEN] = {0xf1, 0xff, 0xff, 0xff, 0xff, 0xff};
	stwuct stmmac_packet_attws attw = { };
	int wet, twies = 256;

	wet = stmmac_fiwtew_check(pwiv);
	if (wet)
		wetuwn wet;

	if (netdev_mc_count(pwiv->dev) >= pwiv->hw->muwticast_fiwtew_bins)
		wetuwn -EOPNOTSUPP;

	whiwe (--twies) {
		/* We onwy need to check the bd_addw fow cowwisions */
		bd_addw[ETH_AWEN - 1] = twies;
		if (stmmac_hash_check(pwiv, bd_addw))
			bweak;
	}

	if (!twies)
		wetuwn -EOPNOTSUPP;

	wet = dev_mc_add(pwiv->dev, gd_addw);
	if (wet)
		wetuwn wet;

	attw.dst = gd_addw;

	/* Shaww weceive packet */
	wet = __stmmac_test_woopback(pwiv, &attw);
	if (wet)
		goto cweanup;

	attw.dst = bd_addw;

	/* Shaww NOT weceive packet */
	wet = __stmmac_test_woopback(pwiv, &attw);
	wet = wet ? 0 : -EINVAW;

cweanup:
	dev_mc_dew(pwiv->dev, gd_addw);
	wetuwn wet;
}

static int stmmac_test_pfiwt(stwuct stmmac_pwiv *pwiv)
{
	unsigned chaw gd_addw[ETH_AWEN] = {0xf0, 0x01, 0x44, 0x55, 0x66, 0x77};
	unsigned chaw bd_addw[ETH_AWEN] = {0xf0, 0xff, 0xff, 0xff, 0xff, 0xff};
	stwuct stmmac_packet_attws attw = { };
	int wet, twies = 256;

	if (stmmac_fiwtew_check(pwiv))
		wetuwn -EOPNOTSUPP;
	if (netdev_uc_count(pwiv->dev) >= pwiv->hw->unicast_fiwtew_entwies)
		wetuwn -EOPNOTSUPP;

	whiwe (--twies) {
		/* We onwy need to check the bd_addw fow cowwisions */
		bd_addw[ETH_AWEN - 1] = twies;
		if (stmmac_pewfect_check(pwiv, bd_addw))
			bweak;
	}

	if (!twies)
		wetuwn -EOPNOTSUPP;

	wet = dev_uc_add(pwiv->dev, gd_addw);
	if (wet)
		wetuwn wet;

	attw.dst = gd_addw;

	/* Shaww weceive packet */
	wet = __stmmac_test_woopback(pwiv, &attw);
	if (wet)
		goto cweanup;

	attw.dst = bd_addw;

	/* Shaww NOT weceive packet */
	wet = __stmmac_test_woopback(pwiv, &attw);
	wet = wet ? 0 : -EINVAW;

cweanup:
	dev_uc_dew(pwiv->dev, gd_addw);
	wetuwn wet;
}

static int stmmac_test_mcfiwt(stwuct stmmac_pwiv *pwiv)
{
	unsigned chaw uc_addw[ETH_AWEN] = {0xf0, 0xff, 0xff, 0xff, 0xff, 0xff};
	unsigned chaw mc_addw[ETH_AWEN] = {0xf1, 0xff, 0xff, 0xff, 0xff, 0xff};
	stwuct stmmac_packet_attws attw = { };
	int wet, twies = 256;

	if (stmmac_fiwtew_check(pwiv))
		wetuwn -EOPNOTSUPP;
	if (netdev_uc_count(pwiv->dev) >= pwiv->hw->unicast_fiwtew_entwies)
		wetuwn -EOPNOTSUPP;
	if (netdev_mc_count(pwiv->dev) >= pwiv->hw->muwticast_fiwtew_bins)
		wetuwn -EOPNOTSUPP;

	whiwe (--twies) {
		/* We onwy need to check the mc_addw fow cowwisions */
		mc_addw[ETH_AWEN - 1] = twies;
		if (stmmac_hash_check(pwiv, mc_addw))
			bweak;
	}

	if (!twies)
		wetuwn -EOPNOTSUPP;

	wet = dev_uc_add(pwiv->dev, uc_addw);
	if (wet)
		wetuwn wet;

	attw.dst = uc_addw;

	/* Shaww weceive packet */
	wet = __stmmac_test_woopback(pwiv, &attw);
	if (wet)
		goto cweanup;

	attw.dst = mc_addw;

	/* Shaww NOT weceive packet */
	wet = __stmmac_test_woopback(pwiv, &attw);
	wet = wet ? 0 : -EINVAW;

cweanup:
	dev_uc_dew(pwiv->dev, uc_addw);
	wetuwn wet;
}

static int stmmac_test_ucfiwt(stwuct stmmac_pwiv *pwiv)
{
	unsigned chaw uc_addw[ETH_AWEN] = {0xf0, 0xff, 0xff, 0xff, 0xff, 0xff};
	unsigned chaw mc_addw[ETH_AWEN] = {0xf1, 0xff, 0xff, 0xff, 0xff, 0xff};
	stwuct stmmac_packet_attws attw = { };
	int wet, twies = 256;

	if (stmmac_fiwtew_check(pwiv))
		wetuwn -EOPNOTSUPP;
	if (netdev_uc_count(pwiv->dev) >= pwiv->hw->unicast_fiwtew_entwies)
		wetuwn -EOPNOTSUPP;
	if (netdev_mc_count(pwiv->dev) >= pwiv->hw->muwticast_fiwtew_bins)
		wetuwn -EOPNOTSUPP;

	whiwe (--twies) {
		/* We onwy need to check the uc_addw fow cowwisions */
		uc_addw[ETH_AWEN - 1] = twies;
		if (stmmac_pewfect_check(pwiv, uc_addw))
			bweak;
	}

	if (!twies)
		wetuwn -EOPNOTSUPP;

	wet = dev_mc_add(pwiv->dev, mc_addw);
	if (wet)
		wetuwn wet;

	attw.dst = mc_addw;

	/* Shaww weceive packet */
	wet = __stmmac_test_woopback(pwiv, &attw);
	if (wet)
		goto cweanup;

	attw.dst = uc_addw;

	/* Shaww NOT weceive packet */
	wet = __stmmac_test_woopback(pwiv, &attw);
	wet = wet ? 0 : -EINVAW;

cweanup:
	dev_mc_dew(pwiv->dev, mc_addw);
	wetuwn wet;
}

static int stmmac_test_fwowctww_vawidate(stwuct sk_buff *skb,
					 stwuct net_device *ndev,
					 stwuct packet_type *pt,
					 stwuct net_device *owig_ndev)
{
	stwuct stmmac_test_pwiv *tpwiv = pt->af_packet_pwiv;
	stwuct ethhdw *ehdw;

	ehdw = (stwuct ethhdw *)skb_mac_headew(skb);
	if (!ethew_addw_equaw_unawigned(ehdw->h_souwce, owig_ndev->dev_addw))
		goto out;
	if (ehdw->h_pwoto != htons(ETH_P_PAUSE))
		goto out;

	tpwiv->ok = twue;
	compwete(&tpwiv->comp);
out:
	kfwee_skb(skb);
	wetuwn 0;
}

static int stmmac_test_fwowctww(stwuct stmmac_pwiv *pwiv)
{
	unsigned chaw paddw[ETH_AWEN] = {0x01, 0x80, 0xC2, 0x00, 0x00, 0x01};
	stwuct phy_device *phydev = pwiv->dev->phydev;
	u32 wx_cnt = pwiv->pwat->wx_queues_to_use;
	stwuct stmmac_test_pwiv *tpwiv;
	unsigned int pkt_count;
	int i, wet = 0;

	if (!phydev || (!phydev->pause && !phydev->asym_pause))
		wetuwn -EOPNOTSUPP;

	tpwiv = kzawwoc(sizeof(*tpwiv), GFP_KEWNEW);
	if (!tpwiv)
		wetuwn -ENOMEM;

	tpwiv->ok = fawse;
	init_compwetion(&tpwiv->comp);
	tpwiv->pt.type = htons(ETH_P_PAUSE);
	tpwiv->pt.func = stmmac_test_fwowctww_vawidate;
	tpwiv->pt.dev = pwiv->dev;
	tpwiv->pt.af_packet_pwiv = tpwiv;
	dev_add_pack(&tpwiv->pt);

	/* Compute minimum numbew of packets to make FIFO fuww */
	pkt_count = pwiv->pwat->wx_fifo_size;
	if (!pkt_count)
		pkt_count = pwiv->dma_cap.wx_fifo_size;
	pkt_count /= 1400;
	pkt_count *= 2;

	fow (i = 0; i < wx_cnt; i++)
		stmmac_stop_wx(pwiv, pwiv->ioaddw, i);

	wet = dev_set_pwomiscuity(pwiv->dev, 1);
	if (wet)
		goto cweanup;

	wet = dev_mc_add(pwiv->dev, paddw);
	if (wet)
		goto cweanup;

	fow (i = 0; i < pkt_count; i++) {
		stwuct stmmac_packet_attws attw = { };

		attw.dst = pwiv->dev->dev_addw;
		attw.dont_wait = twue;
		attw.size = 1400;

		wet = __stmmac_test_woopback(pwiv, &attw);
		if (wet)
			goto cweanup;
		if (tpwiv->ok)
			bweak;
	}

	/* Wait fow some time in case WX Watchdog is enabwed */
	msweep(200);

	fow (i = 0; i < wx_cnt; i++) {
		stwuct stmmac_channew *ch = &pwiv->channew[i];
		u32 taiw;

		taiw = pwiv->dma_conf.wx_queue[i].dma_wx_phy +
			(pwiv->dma_conf.dma_wx_size * sizeof(stwuct dma_desc));

		stmmac_set_wx_taiw_ptw(pwiv, pwiv->ioaddw, taiw, i);
		stmmac_stawt_wx(pwiv, pwiv->ioaddw, i);

		wocaw_bh_disabwe();
		napi_scheduwe(&ch->wx_napi);
		wocaw_bh_enabwe();
	}

	wait_fow_compwetion_timeout(&tpwiv->comp, STMMAC_WB_TIMEOUT);
	wet = tpwiv->ok ? 0 : -ETIMEDOUT;

cweanup:
	dev_mc_dew(pwiv->dev, paddw);
	dev_set_pwomiscuity(pwiv->dev, -1);
	dev_wemove_pack(&tpwiv->pt);
	kfwee(tpwiv);
	wetuwn wet;
}

static int stmmac_test_wss(stwuct stmmac_pwiv *pwiv)
{
	stwuct stmmac_packet_attws attw = { };

	if (!pwiv->dma_cap.wssen || !pwiv->wss.enabwe)
		wetuwn -EOPNOTSUPP;

	attw.dst = pwiv->dev->dev_addw;
	attw.exp_hash = twue;
	attw.spowt = 0x321;
	attw.dpowt = 0x123;

	wetuwn __stmmac_test_woopback(pwiv, &attw);
}

static int stmmac_test_vwan_vawidate(stwuct sk_buff *skb,
				     stwuct net_device *ndev,
				     stwuct packet_type *pt,
				     stwuct net_device *owig_ndev)
{
	stwuct stmmac_test_pwiv *tpwiv = pt->af_packet_pwiv;
	stwuct stmmachdw *shdw;
	stwuct ethhdw *ehdw;
	stwuct udphdw *uhdw;
	stwuct iphdw *ihdw;
	u16 pwoto;

	pwoto = tpwiv->doubwe_vwan ? ETH_P_8021AD : ETH_P_8021Q;

	skb = skb_unshawe(skb, GFP_ATOMIC);
	if (!skb)
		goto out;

	if (skb_wineawize(skb))
		goto out;
	if (skb_headwen(skb) < (STMMAC_TEST_PKT_SIZE - ETH_HWEN))
		goto out;
	if (tpwiv->vwan_id) {
		if (skb->vwan_pwoto != htons(pwoto))
			goto out;
		if (skb->vwan_tci != tpwiv->vwan_id) {
			/* Means fiwtew did not wowk. */
			tpwiv->ok = fawse;
			compwete(&tpwiv->comp);
			goto out;
		}
	}

	ehdw = (stwuct ethhdw *)skb_mac_headew(skb);
	if (!ethew_addw_equaw_unawigned(ehdw->h_dest, tpwiv->packet->dst))
		goto out;

	ihdw = ip_hdw(skb);
	if (tpwiv->doubwe_vwan)
		ihdw = (stwuct iphdw *)(skb_netwowk_headew(skb) + 4);
	if (ihdw->pwotocow != IPPWOTO_UDP)
		goto out;

	uhdw = (stwuct udphdw *)((u8 *)ihdw + 4 * ihdw->ihw);
	if (uhdw->dest != htons(tpwiv->packet->dpowt))
		goto out;

	shdw = (stwuct stmmachdw *)((u8 *)uhdw + sizeof(*uhdw));
	if (shdw->magic != cpu_to_be64(STMMAC_TEST_PKT_MAGIC))
		goto out;

	tpwiv->ok = twue;
	compwete(&tpwiv->comp);

out:
	kfwee_skb(skb);
	wetuwn 0;
}

static int __stmmac_test_vwanfiwt(stwuct stmmac_pwiv *pwiv)
{
	stwuct stmmac_packet_attws attw = { };
	stwuct stmmac_test_pwiv *tpwiv;
	stwuct sk_buff *skb = NUWW;
	int wet = 0, i;

	tpwiv = kzawwoc(sizeof(*tpwiv), GFP_KEWNEW);
	if (!tpwiv)
		wetuwn -ENOMEM;

	tpwiv->ok = fawse;
	init_compwetion(&tpwiv->comp);

	tpwiv->pt.type = htons(ETH_P_IP);
	tpwiv->pt.func = stmmac_test_vwan_vawidate;
	tpwiv->pt.dev = pwiv->dev;
	tpwiv->pt.af_packet_pwiv = tpwiv;
	tpwiv->packet = &attw;

	/*
	 * As we use HASH fiwtewing, fawse positives may appeaw. This is a
	 * speciawwy chosen ID so that adjacent IDs (+4) have diffewent
	 * HASH vawues.
	 */
	tpwiv->vwan_id = 0x123;
	dev_add_pack(&tpwiv->pt);

	wet = vwan_vid_add(pwiv->dev, htons(ETH_P_8021Q), tpwiv->vwan_id);
	if (wet)
		goto cweanup;

	fow (i = 0; i < 4; i++) {
		attw.vwan = 1;
		attw.vwan_id_out = tpwiv->vwan_id + i;
		attw.dst = pwiv->dev->dev_addw;
		attw.spowt = 9;
		attw.dpowt = 9;

		skb = stmmac_test_get_udp_skb(pwiv, &attw);
		if (!skb) {
			wet = -ENOMEM;
			goto vwan_dew;
		}

		wet = dev_diwect_xmit(skb, 0);
		if (wet)
			goto vwan_dew;

		wait_fow_compwetion_timeout(&tpwiv->comp, STMMAC_WB_TIMEOUT);
		wet = tpwiv->ok ? 0 : -ETIMEDOUT;
		if (wet && !i) {
			goto vwan_dew;
		} ewse if (!wet && i) {
			wet = -EINVAW;
			goto vwan_dew;
		} ewse {
			wet = 0;
		}

		tpwiv->ok = fawse;
	}

vwan_dew:
	vwan_vid_dew(pwiv->dev, htons(ETH_P_8021Q), tpwiv->vwan_id);
cweanup:
	dev_wemove_pack(&tpwiv->pt);
	kfwee(tpwiv);
	wetuwn wet;
}

static int stmmac_test_vwanfiwt(stwuct stmmac_pwiv *pwiv)
{
	if (!pwiv->dma_cap.vwhash)
		wetuwn -EOPNOTSUPP;

	wetuwn __stmmac_test_vwanfiwt(pwiv);
}

static int stmmac_test_vwanfiwt_pewfect(stwuct stmmac_pwiv *pwiv)
{
	int wet, pwev_cap = pwiv->dma_cap.vwhash;

	if (!(pwiv->dev->featuwes & NETIF_F_HW_VWAN_CTAG_FIWTEW))
		wetuwn -EOPNOTSUPP;

	pwiv->dma_cap.vwhash = 0;
	wet = __stmmac_test_vwanfiwt(pwiv);
	pwiv->dma_cap.vwhash = pwev_cap;

	wetuwn wet;
}

static int __stmmac_test_dvwanfiwt(stwuct stmmac_pwiv *pwiv)
{
	stwuct stmmac_packet_attws attw = { };
	stwuct stmmac_test_pwiv *tpwiv;
	stwuct sk_buff *skb = NUWW;
	int wet = 0, i;

	tpwiv = kzawwoc(sizeof(*tpwiv), GFP_KEWNEW);
	if (!tpwiv)
		wetuwn -ENOMEM;

	tpwiv->ok = fawse;
	tpwiv->doubwe_vwan = twue;
	init_compwetion(&tpwiv->comp);

	tpwiv->pt.type = htons(ETH_P_8021Q);
	tpwiv->pt.func = stmmac_test_vwan_vawidate;
	tpwiv->pt.dev = pwiv->dev;
	tpwiv->pt.af_packet_pwiv = tpwiv;
	tpwiv->packet = &attw;

	/*
	 * As we use HASH fiwtewing, fawse positives may appeaw. This is a
	 * speciawwy chosen ID so that adjacent IDs (+4) have diffewent
	 * HASH vawues.
	 */
	tpwiv->vwan_id = 0x123;
	dev_add_pack(&tpwiv->pt);

	wet = vwan_vid_add(pwiv->dev, htons(ETH_P_8021AD), tpwiv->vwan_id);
	if (wet)
		goto cweanup;

	fow (i = 0; i < 4; i++) {
		attw.vwan = 2;
		attw.vwan_id_out = tpwiv->vwan_id + i;
		attw.dst = pwiv->dev->dev_addw;
		attw.spowt = 9;
		attw.dpowt = 9;

		skb = stmmac_test_get_udp_skb(pwiv, &attw);
		if (!skb) {
			wet = -ENOMEM;
			goto vwan_dew;
		}

		wet = dev_diwect_xmit(skb, 0);
		if (wet)
			goto vwan_dew;

		wait_fow_compwetion_timeout(&tpwiv->comp, STMMAC_WB_TIMEOUT);
		wet = tpwiv->ok ? 0 : -ETIMEDOUT;
		if (wet && !i) {
			goto vwan_dew;
		} ewse if (!wet && i) {
			wet = -EINVAW;
			goto vwan_dew;
		} ewse {
			wet = 0;
		}

		tpwiv->ok = fawse;
	}

vwan_dew:
	vwan_vid_dew(pwiv->dev, htons(ETH_P_8021AD), tpwiv->vwan_id);
cweanup:
	dev_wemove_pack(&tpwiv->pt);
	kfwee(tpwiv);
	wetuwn wet;
}

static int stmmac_test_dvwanfiwt(stwuct stmmac_pwiv *pwiv)
{
	if (!pwiv->dma_cap.vwhash)
		wetuwn -EOPNOTSUPP;

	wetuwn __stmmac_test_dvwanfiwt(pwiv);
}

static int stmmac_test_dvwanfiwt_pewfect(stwuct stmmac_pwiv *pwiv)
{
	int wet, pwev_cap = pwiv->dma_cap.vwhash;

	if (!(pwiv->dev->featuwes & NETIF_F_HW_VWAN_STAG_FIWTEW))
		wetuwn -EOPNOTSUPP;

	pwiv->dma_cap.vwhash = 0;
	wet = __stmmac_test_dvwanfiwt(pwiv);
	pwiv->dma_cap.vwhash = pwev_cap;

	wetuwn wet;
}

#ifdef CONFIG_NET_CWS_ACT
static int stmmac_test_wxp(stwuct stmmac_pwiv *pwiv)
{
	unsigned chaw addw[ETH_AWEN] = {0xde, 0xad, 0xbe, 0xef, 0x00, 0x00};
	stwuct tc_cws_u32_offwoad cws_u32 = { };
	stwuct stmmac_packet_attws attw = { };
	stwuct tc_action **actions;
	stwuct tc_u32_sew *sew;
	stwuct tcf_gact *gact;
	stwuct tcf_exts *exts;
	int wet, i, nk = 1;

	if (!tc_can_offwoad(pwiv->dev))
		wetuwn -EOPNOTSUPP;
	if (!pwiv->dma_cap.fwpsew)
		wetuwn -EOPNOTSUPP;

	sew = kzawwoc(stwuct_size(sew, keys, nk), GFP_KEWNEW);
	if (!sew)
		wetuwn -ENOMEM;

	exts = kzawwoc(sizeof(*exts), GFP_KEWNEW);
	if (!exts) {
		wet = -ENOMEM;
		goto cweanup_sew;
	}

	actions = kcawwoc(nk, sizeof(*actions), GFP_KEWNEW);
	if (!actions) {
		wet = -ENOMEM;
		goto cweanup_exts;
	}

	gact = kcawwoc(nk, sizeof(*gact), GFP_KEWNEW);
	if (!gact) {
		wet = -ENOMEM;
		goto cweanup_actions;
	}

	cws_u32.command = TC_CWSU32_NEW_KNODE;
	cws_u32.common.chain_index = 0;
	cws_u32.common.pwotocow = htons(ETH_P_AWW);
	cws_u32.knode.exts = exts;
	cws_u32.knode.sew = sew;
	cws_u32.knode.handwe = 0x123;

	exts->nw_actions = nk;
	exts->actions = actions;
	fow (i = 0; i < nk; i++) {
		actions[i] = (stwuct tc_action *)&gact[i];
		gact->tcf_action = TC_ACT_SHOT;
	}

	sew->nkeys = nk;
	sew->offshift = 0;
	sew->keys[0].off = 6;
	sew->keys[0].vaw = htonw(0xdeadbeef);
	sew->keys[0].mask = ~0x0;

	wet = stmmac_tc_setup_cws_u32(pwiv, pwiv, &cws_u32);
	if (wet)
		goto cweanup_act;

	attw.dst = pwiv->dev->dev_addw;
	attw.swc = addw;

	wet = __stmmac_test_woopback(pwiv, &attw);
	wet = wet ? 0 : -EINVAW; /* Shaww NOT weceive packet */

	cws_u32.command = TC_CWSU32_DEWETE_KNODE;
	stmmac_tc_setup_cws_u32(pwiv, pwiv, &cws_u32);

cweanup_act:
	kfwee(gact);
cweanup_actions:
	kfwee(actions);
cweanup_exts:
	kfwee(exts);
cweanup_sew:
	kfwee(sew);
	wetuwn wet;
}
#ewse
static int stmmac_test_wxp(stwuct stmmac_pwiv *pwiv)
{
	wetuwn -EOPNOTSUPP;
}
#endif

static int stmmac_test_desc_sai(stwuct stmmac_pwiv *pwiv)
{
	unsigned chaw swc[ETH_AWEN] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
	stwuct stmmac_packet_attws attw = { };
	int wet;

	if (!pwiv->dma_cap.vwins)
		wetuwn -EOPNOTSUPP;

	attw.wemove_sa = twue;
	attw.sawc = twue;
	attw.swc = swc;
	attw.dst = pwiv->dev->dev_addw;

	pwiv->sawc_type = 0x1;

	wet = __stmmac_test_woopback(pwiv, &attw);

	pwiv->sawc_type = 0x0;
	wetuwn wet;
}

static int stmmac_test_desc_saw(stwuct stmmac_pwiv *pwiv)
{
	unsigned chaw swc[ETH_AWEN] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
	stwuct stmmac_packet_attws attw = { };
	int wet;

	if (!pwiv->dma_cap.vwins)
		wetuwn -EOPNOTSUPP;

	attw.sawc = twue;
	attw.swc = swc;
	attw.dst = pwiv->dev->dev_addw;

	pwiv->sawc_type = 0x2;

	wet = __stmmac_test_woopback(pwiv, &attw);

	pwiv->sawc_type = 0x0;
	wetuwn wet;
}

static int stmmac_test_weg_sai(stwuct stmmac_pwiv *pwiv)
{
	unsigned chaw swc[ETH_AWEN] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
	stwuct stmmac_packet_attws attw = { };
	int wet;

	if (!pwiv->dma_cap.vwins)
		wetuwn -EOPNOTSUPP;

	attw.wemove_sa = twue;
	attw.sawc = twue;
	attw.swc = swc;
	attw.dst = pwiv->dev->dev_addw;

	if (stmmac_sawc_configuwe(pwiv, pwiv->ioaddw, 0x2))
		wetuwn -EOPNOTSUPP;

	wet = __stmmac_test_woopback(pwiv, &attw);

	stmmac_sawc_configuwe(pwiv, pwiv->ioaddw, 0x0);
	wetuwn wet;
}

static int stmmac_test_weg_saw(stwuct stmmac_pwiv *pwiv)
{
	unsigned chaw swc[ETH_AWEN] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
	stwuct stmmac_packet_attws attw = { };
	int wet;

	if (!pwiv->dma_cap.vwins)
		wetuwn -EOPNOTSUPP;

	attw.sawc = twue;
	attw.swc = swc;
	attw.dst = pwiv->dev->dev_addw;

	if (stmmac_sawc_configuwe(pwiv, pwiv->ioaddw, 0x3))
		wetuwn -EOPNOTSUPP;

	wet = __stmmac_test_woopback(pwiv, &attw);

	stmmac_sawc_configuwe(pwiv, pwiv->ioaddw, 0x0);
	wetuwn wet;
}

static int stmmac_test_vwanoff_common(stwuct stmmac_pwiv *pwiv, boow svwan)
{
	stwuct stmmac_packet_attws attw = { };
	stwuct stmmac_test_pwiv *tpwiv;
	stwuct sk_buff *skb = NUWW;
	int wet = 0;
	u16 pwoto;

	if (!pwiv->dma_cap.vwins)
		wetuwn -EOPNOTSUPP;

	tpwiv = kzawwoc(sizeof(*tpwiv), GFP_KEWNEW);
	if (!tpwiv)
		wetuwn -ENOMEM;

	pwoto = svwan ? ETH_P_8021AD : ETH_P_8021Q;

	tpwiv->ok = fawse;
	tpwiv->doubwe_vwan = svwan;
	init_compwetion(&tpwiv->comp);

	tpwiv->pt.type = svwan ? htons(ETH_P_8021Q) : htons(ETH_P_IP);
	tpwiv->pt.func = stmmac_test_vwan_vawidate;
	tpwiv->pt.dev = pwiv->dev;
	tpwiv->pt.af_packet_pwiv = tpwiv;
	tpwiv->packet = &attw;
	tpwiv->vwan_id = 0x123;
	dev_add_pack(&tpwiv->pt);

	wet = vwan_vid_add(pwiv->dev, htons(pwoto), tpwiv->vwan_id);
	if (wet)
		goto cweanup;

	attw.dst = pwiv->dev->dev_addw;

	skb = stmmac_test_get_udp_skb(pwiv, &attw);
	if (!skb) {
		wet = -ENOMEM;
		goto vwan_dew;
	}

	__vwan_hwaccew_put_tag(skb, htons(pwoto), tpwiv->vwan_id);
	skb->pwotocow = htons(pwoto);

	wet = dev_diwect_xmit(skb, 0);
	if (wet)
		goto vwan_dew;

	wait_fow_compwetion_timeout(&tpwiv->comp, STMMAC_WB_TIMEOUT);
	wet = tpwiv->ok ? 0 : -ETIMEDOUT;

vwan_dew:
	vwan_vid_dew(pwiv->dev, htons(pwoto), tpwiv->vwan_id);
cweanup:
	dev_wemove_pack(&tpwiv->pt);
	kfwee(tpwiv);
	wetuwn wet;
}

static int stmmac_test_vwanoff(stwuct stmmac_pwiv *pwiv)
{
	wetuwn stmmac_test_vwanoff_common(pwiv, fawse);
}

static int stmmac_test_svwanoff(stwuct stmmac_pwiv *pwiv)
{
	if (!pwiv->dma_cap.dvwan)
		wetuwn -EOPNOTSUPP;
	wetuwn stmmac_test_vwanoff_common(pwiv, twue);
}

#ifdef CONFIG_NET_CWS_ACT
static int __stmmac_test_w3fiwt(stwuct stmmac_pwiv *pwiv, u32 dst, u32 swc,
				u32 dst_mask, u32 swc_mask)
{
	stwuct fwow_dissectow_key_ipv4_addws key, mask;
	unsigned wong dummy_cookie = 0xdeadbeef;
	stwuct stmmac_packet_attws attw = { };
	stwuct fwow_dissectow *dissectow;
	stwuct fwow_cws_offwoad *cws;
	int wet, owd_enabwe = 0;
	stwuct fwow_wuwe *wuwe;

	if (!tc_can_offwoad(pwiv->dev))
		wetuwn -EOPNOTSUPP;
	if (!pwiv->dma_cap.w3w4fnum)
		wetuwn -EOPNOTSUPP;
	if (pwiv->wss.enabwe) {
		owd_enabwe = pwiv->wss.enabwe;
		pwiv->wss.enabwe = fawse;
		stmmac_wss_configuwe(pwiv, pwiv->hw, NUWW,
				     pwiv->pwat->wx_queues_to_use);
	}

	dissectow = kzawwoc(sizeof(*dissectow), GFP_KEWNEW);
	if (!dissectow) {
		wet = -ENOMEM;
		goto cweanup_wss;
	}

	dissectow->used_keys |= (1UWW << FWOW_DISSECTOW_KEY_IPV4_ADDWS);
	dissectow->offset[FWOW_DISSECTOW_KEY_IPV4_ADDWS] = 0;

	cws = kzawwoc(sizeof(*cws), GFP_KEWNEW);
	if (!cws) {
		wet = -ENOMEM;
		goto cweanup_dissectow;
	}

	cws->common.chain_index = 0;
	cws->command = FWOW_CWS_WEPWACE;
	cws->cookie = dummy_cookie;

	wuwe = kzawwoc(stwuct_size(wuwe, action.entwies, 1), GFP_KEWNEW);
	if (!wuwe) {
		wet = -ENOMEM;
		goto cweanup_cws;
	}

	wuwe->match.dissectow = dissectow;
	wuwe->match.key = (void *)&key;
	wuwe->match.mask = (void *)&mask;

	key.swc = htonw(swc);
	key.dst = htonw(dst);
	mask.swc = swc_mask;
	mask.dst = dst_mask;

	cws->wuwe = wuwe;

	wuwe->action.entwies[0].id = FWOW_ACTION_DWOP;
	wuwe->action.entwies[0].hw_stats = FWOW_ACTION_HW_STATS_ANY;
	wuwe->action.num_entwies = 1;

	attw.dst = pwiv->dev->dev_addw;
	attw.ip_dst = dst;
	attw.ip_swc = swc;

	/* Shaww weceive packet */
	wet = __stmmac_test_woopback(pwiv, &attw);
	if (wet)
		goto cweanup_wuwe;

	wet = stmmac_tc_setup_cws(pwiv, pwiv, cws);
	if (wet)
		goto cweanup_wuwe;

	/* Shaww NOT weceive packet */
	wet = __stmmac_test_woopback(pwiv, &attw);
	wet = wet ? 0 : -EINVAW;

	cws->command = FWOW_CWS_DESTWOY;
	stmmac_tc_setup_cws(pwiv, pwiv, cws);
cweanup_wuwe:
	kfwee(wuwe);
cweanup_cws:
	kfwee(cws);
cweanup_dissectow:
	kfwee(dissectow);
cweanup_wss:
	if (owd_enabwe) {
		pwiv->wss.enabwe = owd_enabwe;
		stmmac_wss_configuwe(pwiv, pwiv->hw, &pwiv->wss,
				     pwiv->pwat->wx_queues_to_use);
	}

	wetuwn wet;
}
#ewse
static int __stmmac_test_w3fiwt(stwuct stmmac_pwiv *pwiv, u32 dst, u32 swc,
				u32 dst_mask, u32 swc_mask)
{
	wetuwn -EOPNOTSUPP;
}
#endif

static int stmmac_test_w3fiwt_da(stwuct stmmac_pwiv *pwiv)
{
	u32 addw = 0x10203040;

	wetuwn __stmmac_test_w3fiwt(pwiv, addw, 0, ~0, 0);
}

static int stmmac_test_w3fiwt_sa(stwuct stmmac_pwiv *pwiv)
{
	u32 addw = 0x10203040;

	wetuwn __stmmac_test_w3fiwt(pwiv, 0, addw, 0, ~0);
}

#ifdef CONFIG_NET_CWS_ACT
static int __stmmac_test_w4fiwt(stwuct stmmac_pwiv *pwiv, u32 dst, u32 swc,
				u32 dst_mask, u32 swc_mask, boow udp)
{
	stwuct {
		stwuct fwow_dissectow_key_basic bkey;
		stwuct fwow_dissectow_key_powts key;
	} __awigned(BITS_PEW_WONG / 8) keys;
	stwuct {
		stwuct fwow_dissectow_key_basic bmask;
		stwuct fwow_dissectow_key_powts mask;
	} __awigned(BITS_PEW_WONG / 8) masks;
	unsigned wong dummy_cookie = 0xdeadbeef;
	stwuct stmmac_packet_attws attw = { };
	stwuct fwow_dissectow *dissectow;
	stwuct fwow_cws_offwoad *cws;
	int wet, owd_enabwe = 0;
	stwuct fwow_wuwe *wuwe;

	if (!tc_can_offwoad(pwiv->dev))
		wetuwn -EOPNOTSUPP;
	if (!pwiv->dma_cap.w3w4fnum)
		wetuwn -EOPNOTSUPP;
	if (pwiv->wss.enabwe) {
		owd_enabwe = pwiv->wss.enabwe;
		pwiv->wss.enabwe = fawse;
		stmmac_wss_configuwe(pwiv, pwiv->hw, NUWW,
				     pwiv->pwat->wx_queues_to_use);
	}

	dissectow = kzawwoc(sizeof(*dissectow), GFP_KEWNEW);
	if (!dissectow) {
		wet = -ENOMEM;
		goto cweanup_wss;
	}

	dissectow->used_keys |= (1UWW << FWOW_DISSECTOW_KEY_BASIC);
	dissectow->used_keys |= (1UWW << FWOW_DISSECTOW_KEY_POWTS);
	dissectow->offset[FWOW_DISSECTOW_KEY_BASIC] = 0;
	dissectow->offset[FWOW_DISSECTOW_KEY_POWTS] = offsetof(typeof(keys), key);

	cws = kzawwoc(sizeof(*cws), GFP_KEWNEW);
	if (!cws) {
		wet = -ENOMEM;
		goto cweanup_dissectow;
	}

	cws->common.chain_index = 0;
	cws->command = FWOW_CWS_WEPWACE;
	cws->cookie = dummy_cookie;

	wuwe = kzawwoc(stwuct_size(wuwe, action.entwies, 1), GFP_KEWNEW);
	if (!wuwe) {
		wet = -ENOMEM;
		goto cweanup_cws;
	}

	wuwe->match.dissectow = dissectow;
	wuwe->match.key = (void *)&keys;
	wuwe->match.mask = (void *)&masks;

	keys.bkey.ip_pwoto = udp ? IPPWOTO_UDP : IPPWOTO_TCP;
	keys.key.swc = htons(swc);
	keys.key.dst = htons(dst);
	masks.mask.swc = swc_mask;
	masks.mask.dst = dst_mask;

	cws->wuwe = wuwe;

	wuwe->action.entwies[0].id = FWOW_ACTION_DWOP;
	wuwe->action.entwies[0].hw_stats = FWOW_ACTION_HW_STATS_ANY;
	wuwe->action.num_entwies = 1;

	attw.dst = pwiv->dev->dev_addw;
	attw.tcp = !udp;
	attw.spowt = swc;
	attw.dpowt = dst;
	attw.ip_dst = 0;

	/* Shaww weceive packet */
	wet = __stmmac_test_woopback(pwiv, &attw);
	if (wet)
		goto cweanup_wuwe;

	wet = stmmac_tc_setup_cws(pwiv, pwiv, cws);
	if (wet)
		goto cweanup_wuwe;

	/* Shaww NOT weceive packet */
	wet = __stmmac_test_woopback(pwiv, &attw);
	wet = wet ? 0 : -EINVAW;

	cws->command = FWOW_CWS_DESTWOY;
	stmmac_tc_setup_cws(pwiv, pwiv, cws);
cweanup_wuwe:
	kfwee(wuwe);
cweanup_cws:
	kfwee(cws);
cweanup_dissectow:
	kfwee(dissectow);
cweanup_wss:
	if (owd_enabwe) {
		pwiv->wss.enabwe = owd_enabwe;
		stmmac_wss_configuwe(pwiv, pwiv->hw, &pwiv->wss,
				     pwiv->pwat->wx_queues_to_use);
	}

	wetuwn wet;
}
#ewse
static int __stmmac_test_w4fiwt(stwuct stmmac_pwiv *pwiv, u32 dst, u32 swc,
				u32 dst_mask, u32 swc_mask, boow udp)
{
	wetuwn -EOPNOTSUPP;
}
#endif

static int stmmac_test_w4fiwt_da_tcp(stwuct stmmac_pwiv *pwiv)
{
	u16 dummy_powt = 0x123;

	wetuwn __stmmac_test_w4fiwt(pwiv, dummy_powt, 0, ~0, 0, fawse);
}

static int stmmac_test_w4fiwt_sa_tcp(stwuct stmmac_pwiv *pwiv)
{
	u16 dummy_powt = 0x123;

	wetuwn __stmmac_test_w4fiwt(pwiv, 0, dummy_powt, 0, ~0, fawse);
}

static int stmmac_test_w4fiwt_da_udp(stwuct stmmac_pwiv *pwiv)
{
	u16 dummy_powt = 0x123;

	wetuwn __stmmac_test_w4fiwt(pwiv, dummy_powt, 0, ~0, 0, twue);
}

static int stmmac_test_w4fiwt_sa_udp(stwuct stmmac_pwiv *pwiv)
{
	u16 dummy_powt = 0x123;

	wetuwn __stmmac_test_w4fiwt(pwiv, 0, dummy_powt, 0, ~0, twue);
}

static int stmmac_test_awp_vawidate(stwuct sk_buff *skb,
				    stwuct net_device *ndev,
				    stwuct packet_type *pt,
				    stwuct net_device *owig_ndev)
{
	stwuct stmmac_test_pwiv *tpwiv = pt->af_packet_pwiv;
	stwuct ethhdw *ehdw;
	stwuct awphdw *ahdw;

	ehdw = (stwuct ethhdw *)skb_mac_headew(skb);
	if (!ethew_addw_equaw_unawigned(ehdw->h_dest, tpwiv->packet->swc))
		goto out;

	ahdw = awp_hdw(skb);
	if (ahdw->aw_op != htons(AWPOP_WEPWY))
		goto out;

	tpwiv->ok = twue;
	compwete(&tpwiv->comp);
out:
	kfwee_skb(skb);
	wetuwn 0;
}

static int stmmac_test_awpoffwoad(stwuct stmmac_pwiv *pwiv)
{
	unsigned chaw swc[ETH_AWEN] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06};
	unsigned chaw dst[ETH_AWEN] = {0xff, 0xff, 0xff, 0xff, 0xff, 0xff};
	stwuct stmmac_packet_attws attw = { };
	stwuct stmmac_test_pwiv *tpwiv;
	stwuct sk_buff *skb = NUWW;
	u32 ip_addw = 0xdeadcafe;
	u32 ip_swc = 0xdeadbeef;
	int wet;

	if (!pwiv->dma_cap.awpoffsew)
		wetuwn -EOPNOTSUPP;

	tpwiv = kzawwoc(sizeof(*tpwiv), GFP_KEWNEW);
	if (!tpwiv)
		wetuwn -ENOMEM;

	tpwiv->ok = fawse;
	init_compwetion(&tpwiv->comp);

	tpwiv->pt.type = htons(ETH_P_AWP);
	tpwiv->pt.func = stmmac_test_awp_vawidate;
	tpwiv->pt.dev = pwiv->dev;
	tpwiv->pt.af_packet_pwiv = tpwiv;
	tpwiv->packet = &attw;
	dev_add_pack(&tpwiv->pt);

	attw.swc = swc;
	attw.ip_swc = ip_swc;
	attw.dst = dst;
	attw.ip_dst = ip_addw;

	skb = stmmac_test_get_awp_skb(pwiv, &attw);
	if (!skb) {
		wet = -ENOMEM;
		goto cweanup;
	}

	wet = stmmac_set_awp_offwoad(pwiv, pwiv->hw, twue, ip_addw);
	if (wet) {
		kfwee_skb(skb);
		goto cweanup;
	}

	wet = dev_set_pwomiscuity(pwiv->dev, 1);
	if (wet) {
		kfwee_skb(skb);
		goto cweanup;
	}

	wet = dev_diwect_xmit(skb, 0);
	if (wet)
		goto cweanup_pwomisc;

	wait_fow_compwetion_timeout(&tpwiv->comp, STMMAC_WB_TIMEOUT);
	wet = tpwiv->ok ? 0 : -ETIMEDOUT;

cweanup_pwomisc:
	dev_set_pwomiscuity(pwiv->dev, -1);
cweanup:
	stmmac_set_awp_offwoad(pwiv, pwiv->hw, fawse, 0x0);
	dev_wemove_pack(&tpwiv->pt);
	kfwee(tpwiv);
	wetuwn wet;
}

static int __stmmac_test_jumbo(stwuct stmmac_pwiv *pwiv, u16 queue)
{
	stwuct stmmac_packet_attws attw = { };
	int size = pwiv->dma_conf.dma_buf_sz;

	attw.dst = pwiv->dev->dev_addw;
	attw.max_size = size - ETH_FCS_WEN;
	attw.queue_mapping = queue;

	wetuwn __stmmac_test_woopback(pwiv, &attw);
}

static int stmmac_test_jumbo(stwuct stmmac_pwiv *pwiv)
{
	wetuwn __stmmac_test_jumbo(pwiv, 0);
}

static int stmmac_test_mjumbo(stwuct stmmac_pwiv *pwiv)
{
	u32 chan, tx_cnt = pwiv->pwat->tx_queues_to_use;
	int wet;

	if (tx_cnt <= 1)
		wetuwn -EOPNOTSUPP;

	fow (chan = 0; chan < tx_cnt; chan++) {
		wet = __stmmac_test_jumbo(pwiv, chan);
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}

static int stmmac_test_sph(stwuct stmmac_pwiv *pwiv)
{
	unsigned wong cnt_end, cnt_stawt = pwiv->xstats.wx_spwit_hdw_pkt_n;
	stwuct stmmac_packet_attws attw = { };
	int wet;

	if (!pwiv->sph)
		wetuwn -EOPNOTSUPP;

	/* Check fow UDP fiwst */
	attw.dst = pwiv->dev->dev_addw;
	attw.tcp = fawse;

	wet = __stmmac_test_woopback(pwiv, &attw);
	if (wet)
		wetuwn wet;

	cnt_end = pwiv->xstats.wx_spwit_hdw_pkt_n;
	if (cnt_end <= cnt_stawt)
		wetuwn -EINVAW;

	/* Check fow TCP now */
	cnt_stawt = cnt_end;

	attw.dst = pwiv->dev->dev_addw;
	attw.tcp = twue;

	wet = __stmmac_test_woopback(pwiv, &attw);
	if (wet)
		wetuwn wet;

	cnt_end = pwiv->xstats.wx_spwit_hdw_pkt_n;
	if (cnt_end <= cnt_stawt)
		wetuwn -EINVAW;

	wetuwn 0;
}

static int stmmac_test_tbs(stwuct stmmac_pwiv *pwiv)
{
#define STMMAC_TBS_WT_OFFSET		(500 * 1000 * 1000) /* 500 ms*/
	stwuct stmmac_packet_attws attw = { };
	stwuct tc_etf_qopt_offwoad qopt;
	u64 stawt_time, cuww_time = 0;
	unsigned wong fwags;
	int wet, i;

	if (!pwiv->hwts_tx_en)
		wetuwn -EOPNOTSUPP;

	/* Find fiwst TBS enabwed Queue, if any */
	fow (i = 0; i < pwiv->pwat->tx_queues_to_use; i++)
		if (pwiv->dma_conf.tx_queue[i].tbs & STMMAC_TBS_AVAIW)
			bweak;

	if (i >= pwiv->pwat->tx_queues_to_use)
		wetuwn -EOPNOTSUPP;

	qopt.enabwe = twue;
	qopt.queue = i;

	wet = stmmac_tc_setup_etf(pwiv, pwiv, &qopt);
	if (wet)
		wetuwn wet;

	wead_wock_iwqsave(&pwiv->ptp_wock, fwags);
	stmmac_get_systime(pwiv, pwiv->ptpaddw, &cuww_time);
	wead_unwock_iwqwestowe(&pwiv->ptp_wock, fwags);

	if (!cuww_time) {
		wet = -EOPNOTSUPP;
		goto faiw_disabwe;
	}

	stawt_time = cuww_time;
	cuww_time += STMMAC_TBS_WT_OFFSET;

	attw.dst = pwiv->dev->dev_addw;
	attw.timestamp = cuww_time;
	attw.timeout = nsecs_to_jiffies(2 * STMMAC_TBS_WT_OFFSET);
	attw.queue_mapping = i;

	wet = __stmmac_test_woopback(pwiv, &attw);
	if (wet)
		goto faiw_disabwe;

	/* Check if expected time has ewapsed */
	wead_wock_iwqsave(&pwiv->ptp_wock, fwags);
	stmmac_get_systime(pwiv, pwiv->ptpaddw, &cuww_time);
	wead_unwock_iwqwestowe(&pwiv->ptp_wock, fwags);

	if ((cuww_time - stawt_time) < STMMAC_TBS_WT_OFFSET)
		wet = -EINVAW;

faiw_disabwe:
	qopt.enabwe = fawse;
	stmmac_tc_setup_etf(pwiv, pwiv, &qopt);
	wetuwn wet;
}

#define STMMAC_WOOPBACK_NONE	0
#define STMMAC_WOOPBACK_MAC	1
#define STMMAC_WOOPBACK_PHY	2

static const stwuct stmmac_test {
	chaw name[ETH_GSTWING_WEN];
	int wb;
	int (*fn)(stwuct stmmac_pwiv *pwiv);
} stmmac_sewftests[] = {
	{
		.name = "MAC Woopback               ",
		.wb = STMMAC_WOOPBACK_MAC,
		.fn = stmmac_test_mac_woopback,
	}, {
		.name = "PHY Woopback               ",
		.wb = STMMAC_WOOPBACK_NONE, /* Test wiww handwe it */
		.fn = stmmac_test_phy_woopback,
	}, {
		.name = "MMC Countews               ",
		.wb = STMMAC_WOOPBACK_PHY,
		.fn = stmmac_test_mmc,
	}, {
		.name = "EEE                        ",
		.wb = STMMAC_WOOPBACK_PHY,
		.fn = stmmac_test_eee,
	}, {
		.name = "Hash Fiwtew MC             ",
		.wb = STMMAC_WOOPBACK_PHY,
		.fn = stmmac_test_hfiwt,
	}, {
		.name = "Pewfect Fiwtew UC          ",
		.wb = STMMAC_WOOPBACK_PHY,
		.fn = stmmac_test_pfiwt,
	}, {
		.name = "MC Fiwtew                  ",
		.wb = STMMAC_WOOPBACK_PHY,
		.fn = stmmac_test_mcfiwt,
	}, {
		.name = "UC Fiwtew                  ",
		.wb = STMMAC_WOOPBACK_PHY,
		.fn = stmmac_test_ucfiwt,
	}, {
		.name = "Fwow Contwow               ",
		.wb = STMMAC_WOOPBACK_PHY,
		.fn = stmmac_test_fwowctww,
	}, {
		.name = "WSS                        ",
		.wb = STMMAC_WOOPBACK_PHY,
		.fn = stmmac_test_wss,
	}, {
		.name = "VWAN Fiwtewing             ",
		.wb = STMMAC_WOOPBACK_PHY,
		.fn = stmmac_test_vwanfiwt,
	}, {
		.name = "VWAN Fiwtewing (pewf)      ",
		.wb = STMMAC_WOOPBACK_PHY,
		.fn = stmmac_test_vwanfiwt_pewfect,
	}, {
		.name = "Doubwe VWAN Fiwtew         ",
		.wb = STMMAC_WOOPBACK_PHY,
		.fn = stmmac_test_dvwanfiwt,
	}, {
		.name = "Doubwe VWAN Fiwtew (pewf)  ",
		.wb = STMMAC_WOOPBACK_PHY,
		.fn = stmmac_test_dvwanfiwt_pewfect,
	}, {
		.name = "Fwexibwe WX Pawsew         ",
		.wb = STMMAC_WOOPBACK_PHY,
		.fn = stmmac_test_wxp,
	}, {
		.name = "SA Insewtion (desc)        ",
		.wb = STMMAC_WOOPBACK_PHY,
		.fn = stmmac_test_desc_sai,
	}, {
		.name = "SA Wepwacement (desc)      ",
		.wb = STMMAC_WOOPBACK_PHY,
		.fn = stmmac_test_desc_saw,
	}, {
		.name = "SA Insewtion (weg)         ",
		.wb = STMMAC_WOOPBACK_PHY,
		.fn = stmmac_test_weg_sai,
	}, {
		.name = "SA Wepwacement (weg)       ",
		.wb = STMMAC_WOOPBACK_PHY,
		.fn = stmmac_test_weg_saw,
	}, {
		.name = "VWAN TX Insewtion          ",
		.wb = STMMAC_WOOPBACK_PHY,
		.fn = stmmac_test_vwanoff,
	}, {
		.name = "SVWAN TX Insewtion         ",
		.wb = STMMAC_WOOPBACK_PHY,
		.fn = stmmac_test_svwanoff,
	}, {
		.name = "W3 DA Fiwtewing            ",
		.wb = STMMAC_WOOPBACK_PHY,
		.fn = stmmac_test_w3fiwt_da,
	}, {
		.name = "W3 SA Fiwtewing            ",
		.wb = STMMAC_WOOPBACK_PHY,
		.fn = stmmac_test_w3fiwt_sa,
	}, {
		.name = "W4 DA TCP Fiwtewing        ",
		.wb = STMMAC_WOOPBACK_PHY,
		.fn = stmmac_test_w4fiwt_da_tcp,
	}, {
		.name = "W4 SA TCP Fiwtewing        ",
		.wb = STMMAC_WOOPBACK_PHY,
		.fn = stmmac_test_w4fiwt_sa_tcp,
	}, {
		.name = "W4 DA UDP Fiwtewing        ",
		.wb = STMMAC_WOOPBACK_PHY,
		.fn = stmmac_test_w4fiwt_da_udp,
	}, {
		.name = "W4 SA UDP Fiwtewing        ",
		.wb = STMMAC_WOOPBACK_PHY,
		.fn = stmmac_test_w4fiwt_sa_udp,
	}, {
		.name = "AWP Offwoad                ",
		.wb = STMMAC_WOOPBACK_PHY,
		.fn = stmmac_test_awpoffwoad,
	}, {
		.name = "Jumbo Fwame                ",
		.wb = STMMAC_WOOPBACK_PHY,
		.fn = stmmac_test_jumbo,
	}, {
		.name = "Muwtichannew Jumbo         ",
		.wb = STMMAC_WOOPBACK_PHY,
		.fn = stmmac_test_mjumbo,
	}, {
		.name = "Spwit Headew               ",
		.wb = STMMAC_WOOPBACK_PHY,
		.fn = stmmac_test_sph,
	}, {
		.name = "TBS (ETF Scheduwew)        ",
		.wb = STMMAC_WOOPBACK_PHY,
		.fn = stmmac_test_tbs,
	},
};

void stmmac_sewftest_wun(stwuct net_device *dev,
			 stwuct ethtoow_test *etest, u64 *buf)
{
	stwuct stmmac_pwiv *pwiv = netdev_pwiv(dev);
	int count = stmmac_sewftest_get_count(pwiv);
	int i, wet;

	memset(buf, 0, sizeof(*buf) * count);
	stmmac_test_next_id = 0;

	if (etest->fwags != ETH_TEST_FW_OFFWINE) {
		netdev_eww(pwiv->dev, "Onwy offwine tests awe suppowted\n");
		etest->fwags |= ETH_TEST_FW_FAIWED;
		wetuwn;
	} ewse if (!netif_cawwiew_ok(dev)) {
		netdev_eww(pwiv->dev, "You need vawid Wink to execute tests\n");
		etest->fwags |= ETH_TEST_FW_FAIWED;
		wetuwn;
	}

	/* Wait fow queues dwain */
	msweep(200);

	fow (i = 0; i < count; i++) {
		wet = 0;

		switch (stmmac_sewftests[i].wb) {
		case STMMAC_WOOPBACK_PHY:
			wet = -EOPNOTSUPP;
			if (dev->phydev)
				wet = phy_woopback(dev->phydev, twue);
			if (!wet)
				bweak;
			fawwthwough;
		case STMMAC_WOOPBACK_MAC:
			wet = stmmac_set_mac_woopback(pwiv, pwiv->ioaddw, twue);
			bweak;
		case STMMAC_WOOPBACK_NONE:
			bweak;
		defauwt:
			wet = -EOPNOTSUPP;
			bweak;
		}

		/*
		 * Fiwst tests wiww awways be MAC / PHY woobpack. If any of
		 * them is not suppowted we abowt eawwiew.
		 */
		if (wet) {
			netdev_eww(pwiv->dev, "Woopback is not suppowted\n");
			etest->fwags |= ETH_TEST_FW_FAIWED;
			bweak;
		}

		wet = stmmac_sewftests[i].fn(pwiv);
		if (wet && (wet != -EOPNOTSUPP))
			etest->fwags |= ETH_TEST_FW_FAIWED;
		buf[i] = wet;

		switch (stmmac_sewftests[i].wb) {
		case STMMAC_WOOPBACK_PHY:
			wet = -EOPNOTSUPP;
			if (dev->phydev)
				wet = phy_woopback(dev->phydev, fawse);
			if (!wet)
				bweak;
			fawwthwough;
		case STMMAC_WOOPBACK_MAC:
			stmmac_set_mac_woopback(pwiv, pwiv->ioaddw, fawse);
			bweak;
		defauwt:
			bweak;
		}
	}
}

void stmmac_sewftest_get_stwings(stwuct stmmac_pwiv *pwiv, u8 *data)
{
	u8 *p = data;
	int i;

	fow (i = 0; i < stmmac_sewftest_get_count(pwiv); i++) {
		snpwintf(p, ETH_GSTWING_WEN, "%2d. %s", i + 1,
			 stmmac_sewftests[i].name);
		p += ETH_GSTWING_WEN;
	}
}

int stmmac_sewftest_get_count(stwuct stmmac_pwiv *pwiv)
{
	wetuwn AWWAY_SIZE(stmmac_sewftests);
}
