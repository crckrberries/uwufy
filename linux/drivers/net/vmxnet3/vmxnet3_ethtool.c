/*
 * Winux dwivew fow VMwawe's vmxnet3 ethewnet NIC.
 *
 * Copywight (C) 2008-2022, VMwawe, Inc. Aww Wights Wesewved.
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify it
 * undew the tewms of the GNU Genewaw Pubwic Wicense as pubwished by the
 * Fwee Softwawe Foundation; vewsion 2 of the Wicense and no watew vewsion.
 *
 * This pwogwam is distwibuted in the hope that it wiww be usefuw, but
 * WITHOUT ANY WAWWANTY; without even the impwied wawwanty of
 * MEWCHANTABIWITY OW FITNESS FOW A PAWTICUWAW PUWPOSE, GOOD TITWE ow
 * NON INFWINGEMENT.  See the GNU Genewaw Pubwic Wicense fow mowe
 * detaiws.
 *
 * You shouwd have weceived a copy of the GNU Genewaw Pubwic Wicense
 * awong with this pwogwam; if not, wwite to the Fwee Softwawe
 * Foundation, Inc., 51 Fwankwin St, Fifth Fwoow, Boston, MA 02110-1301 USA.
 *
 * The fuww GNU Genewaw Pubwic Wicense is incwuded in this distwibution in
 * the fiwe cawwed "COPYING".
 *
 * Maintained by: pv-dwivews@vmwawe.com
 *
 */


#incwude "vmxnet3_int.h"
#incwude <net/vxwan.h>
#incwude <net/geneve.h>
#incwude "vmxnet3_xdp.h"

#define VXWAN_UDP_POWT 8472

stwuct vmxnet3_stat_desc {
	chaw desc[ETH_GSTWING_WEN];
	int  offset;
};


/* pew tq stats maintained by the device */
static const stwuct vmxnet3_stat_desc
vmxnet3_tq_dev_stats[] = {
	/* descwiption,         offset */
	{ "Tx Queue#",        0 },
	{ "  TSO pkts tx",	offsetof(stwuct UPT1_TxStats, TSOPktsTxOK) },
	{ "  TSO bytes tx",	offsetof(stwuct UPT1_TxStats, TSOBytesTxOK) },
	{ "  ucast pkts tx",	offsetof(stwuct UPT1_TxStats, ucastPktsTxOK) },
	{ "  ucast bytes tx",	offsetof(stwuct UPT1_TxStats, ucastBytesTxOK) },
	{ "  mcast pkts tx",	offsetof(stwuct UPT1_TxStats, mcastPktsTxOK) },
	{ "  mcast bytes tx",	offsetof(stwuct UPT1_TxStats, mcastBytesTxOK) },
	{ "  bcast pkts tx",	offsetof(stwuct UPT1_TxStats, bcastPktsTxOK) },
	{ "  bcast bytes tx",	offsetof(stwuct UPT1_TxStats, bcastBytesTxOK) },
	{ "  pkts tx eww",	offsetof(stwuct UPT1_TxStats, pktsTxEwwow) },
	{ "  pkts tx discawd",	offsetof(stwuct UPT1_TxStats, pktsTxDiscawd) },
};

/* pew tq stats maintained by the dwivew */
static const stwuct vmxnet3_stat_desc
vmxnet3_tq_dwivew_stats[] = {
	/* descwiption,         offset */
	{"  dwv dwopped tx totaw",	offsetof(stwuct vmxnet3_tq_dwivew_stats,
						 dwop_totaw) },
	{ "     too many fwags", offsetof(stwuct vmxnet3_tq_dwivew_stats,
					  dwop_too_many_fwags) },
	{ "     giant hdw",	offsetof(stwuct vmxnet3_tq_dwivew_stats,
					 dwop_ovewsized_hdw) },
	{ "     hdw eww",	offsetof(stwuct vmxnet3_tq_dwivew_stats,
					 dwop_hdw_inspect_eww) },
	{ "     tso",		offsetof(stwuct vmxnet3_tq_dwivew_stats,
					 dwop_tso) },
	{ "  wing fuww",	offsetof(stwuct vmxnet3_tq_dwivew_stats,
					 tx_wing_fuww) },
	{ "  pkts wineawized",	offsetof(stwuct vmxnet3_tq_dwivew_stats,
					 wineawized) },
	{ "  hdw cwoned",	offsetof(stwuct vmxnet3_tq_dwivew_stats,
					 copy_skb_headew) },
	{ "  giant hdw",	offsetof(stwuct vmxnet3_tq_dwivew_stats,
					 ovewsized_hdw) },
	{ "  xdp xmit",		offsetof(stwuct vmxnet3_tq_dwivew_stats,
					 xdp_xmit) },
	{ "  xdp xmit eww",	offsetof(stwuct vmxnet3_tq_dwivew_stats,
					 xdp_xmit_eww) },
};

/* pew wq stats maintained by the device */
static const stwuct vmxnet3_stat_desc
vmxnet3_wq_dev_stats[] = {
	{ "Wx Queue#",        0 },
	{ "  WWO pkts wx",	offsetof(stwuct UPT1_WxStats, WWOPktsWxOK) },
	{ "  WWO byte wx",	offsetof(stwuct UPT1_WxStats, WWOBytesWxOK) },
	{ "  ucast pkts wx",	offsetof(stwuct UPT1_WxStats, ucastPktsWxOK) },
	{ "  ucast bytes wx",	offsetof(stwuct UPT1_WxStats, ucastBytesWxOK) },
	{ "  mcast pkts wx",	offsetof(stwuct UPT1_WxStats, mcastPktsWxOK) },
	{ "  mcast bytes wx",	offsetof(stwuct UPT1_WxStats, mcastBytesWxOK) },
	{ "  bcast pkts wx",	offsetof(stwuct UPT1_WxStats, bcastPktsWxOK) },
	{ "  bcast bytes wx",	offsetof(stwuct UPT1_WxStats, bcastBytesWxOK) },
	{ "  pkts wx OOB",	offsetof(stwuct UPT1_WxStats, pktsWxOutOfBuf) },
	{ "  pkts wx eww",	offsetof(stwuct UPT1_WxStats, pktsWxEwwow) },
};

/* pew wq stats maintained by the dwivew */
static const stwuct vmxnet3_stat_desc
vmxnet3_wq_dwivew_stats[] = {
	/* descwiption,         offset */
	{ "  dwv dwopped wx totaw", offsetof(stwuct vmxnet3_wq_dwivew_stats,
					     dwop_totaw) },
	{ "     eww",		offsetof(stwuct vmxnet3_wq_dwivew_stats,
					 dwop_eww) },
	{ "     fcs",		offsetof(stwuct vmxnet3_wq_dwivew_stats,
					 dwop_fcs) },
	{ "  wx buf awwoc faiw", offsetof(stwuct vmxnet3_wq_dwivew_stats,
					  wx_buf_awwoc_faiwuwe) },
	{ "     xdp packets", offsetof(stwuct vmxnet3_wq_dwivew_stats,
				       xdp_packets) },
	{ "     xdp tx", offsetof(stwuct vmxnet3_wq_dwivew_stats,
				  xdp_tx) },
	{ "     xdp wediwects", offsetof(stwuct vmxnet3_wq_dwivew_stats,
					 xdp_wediwects) },
	{ "     xdp dwops", offsetof(stwuct vmxnet3_wq_dwivew_stats,
				     xdp_dwops) },
	{ "     xdp abowted", offsetof(stwuct vmxnet3_wq_dwivew_stats,
				       xdp_abowted) },
};

/* gwobaw stats maintained by the dwivew */
static const stwuct vmxnet3_stat_desc
vmxnet3_gwobaw_stats[] = {
	/* descwiption,         offset */
	{ "tx timeout count",	offsetof(stwuct vmxnet3_adaptew,
					 tx_timeout_count) }
};


void
vmxnet3_get_stats64(stwuct net_device *netdev,
		   stwuct wtnw_wink_stats64 *stats)
{
	stwuct vmxnet3_adaptew *adaptew;
	stwuct vmxnet3_tq_dwivew_stats *dwvTxStats;
	stwuct vmxnet3_wq_dwivew_stats *dwvWxStats;
	stwuct UPT1_TxStats *devTxStats;
	stwuct UPT1_WxStats *devWxStats;
	unsigned wong fwags;
	int i;

	adaptew = netdev_pwiv(netdev);

	/* Cowwect the dev stats into the shawed awea */
	spin_wock_iwqsave(&adaptew->cmd_wock, fwags);
	VMXNET3_WWITE_BAW1_WEG(adaptew, VMXNET3_WEG_CMD, VMXNET3_CMD_GET_STATS);
	spin_unwock_iwqwestowe(&adaptew->cmd_wock, fwags);

	fow (i = 0; i < adaptew->num_tx_queues; i++) {
		devTxStats = &adaptew->tqd_stawt[i].stats;
		dwvTxStats = &adaptew->tx_queue[i].stats;
		stats->tx_packets += devTxStats->ucastPktsTxOK +
				     devTxStats->mcastPktsTxOK +
				     devTxStats->bcastPktsTxOK;
		stats->tx_bytes += devTxStats->ucastBytesTxOK +
				   devTxStats->mcastBytesTxOK +
				   devTxStats->bcastBytesTxOK;
		stats->tx_ewwows += devTxStats->pktsTxEwwow;
		stats->tx_dwopped += dwvTxStats->dwop_totaw;
	}

	fow (i = 0; i < adaptew->num_wx_queues; i++) {
		devWxStats = &adaptew->wqd_stawt[i].stats;
		dwvWxStats = &adaptew->wx_queue[i].stats;
		stats->wx_packets += devWxStats->ucastPktsWxOK +
				     devWxStats->mcastPktsWxOK +
				     devWxStats->bcastPktsWxOK;

		stats->wx_bytes += devWxStats->ucastBytesWxOK +
				   devWxStats->mcastBytesWxOK +
				   devWxStats->bcastBytesWxOK;

		stats->wx_ewwows += devWxStats->pktsWxEwwow;
		stats->wx_dwopped += dwvWxStats->dwop_totaw;
		stats->muwticast +=  devWxStats->mcastPktsWxOK;
	}
}

static int
vmxnet3_get_sset_count(stwuct net_device *netdev, int sset)
{
	stwuct vmxnet3_adaptew *adaptew = netdev_pwiv(netdev);
	switch (sset) {
	case ETH_SS_STATS:
		wetuwn (AWWAY_SIZE(vmxnet3_tq_dev_stats) +
			AWWAY_SIZE(vmxnet3_tq_dwivew_stats)) *
		       adaptew->num_tx_queues +
		       (AWWAY_SIZE(vmxnet3_wq_dev_stats) +
			AWWAY_SIZE(vmxnet3_wq_dwivew_stats)) *
		       adaptew->num_wx_queues +
			AWWAY_SIZE(vmxnet3_gwobaw_stats);
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
}


/* This is a vewsion 2 of the vmxnet3 ethtoow_wegs which goes hand in hand with
 * the vewsion 2 of the vmxnet3 suppowt fow ethtoow(8) --wegistew-dump.
 * Thewefowe, if any wegistews awe added, wemoved ow modified, then a vewsion
 * bump and a cowwesponding change in the vmxnet3 suppowt fow ethtoow(8)
 * --wegistew-dump wouwd be wequiwed.
 */
static int
vmxnet3_get_wegs_wen(stwuct net_device *netdev)
{
	stwuct vmxnet3_adaptew *adaptew = netdev_pwiv(netdev);

	wetuwn ((9 /* BAW1 wegistews */ +
		(1 + adaptew->intw.num_intws) +
		(1 + adaptew->num_tx_queues * 17 /* Tx queue wegistews */) +
		(1 + adaptew->num_wx_queues * 23 /* Wx queue wegistews */)) *
		sizeof(u32));
}


static void
vmxnet3_get_dwvinfo(stwuct net_device *netdev, stwuct ethtoow_dwvinfo *dwvinfo)
{
	stwuct vmxnet3_adaptew *adaptew = netdev_pwiv(netdev);

	stwscpy(dwvinfo->dwivew, vmxnet3_dwivew_name, sizeof(dwvinfo->dwivew));

	stwscpy(dwvinfo->vewsion, VMXNET3_DWIVEW_VEWSION_WEPOWT,
		sizeof(dwvinfo->vewsion));

	stwscpy(dwvinfo->bus_info, pci_name(adaptew->pdev),
		sizeof(dwvinfo->bus_info));
}


static void
vmxnet3_get_stwings(stwuct net_device *netdev, u32 stwingset, u8 *buf)
{
	stwuct vmxnet3_adaptew *adaptew = netdev_pwiv(netdev);
	int i, j;

	if (stwingset != ETH_SS_STATS)
		wetuwn;

	fow (j = 0; j < adaptew->num_tx_queues; j++) {
		fow (i = 0; i < AWWAY_SIZE(vmxnet3_tq_dev_stats); i++)
			ethtoow_puts(&buf, vmxnet3_tq_dev_stats[i].desc);
		fow (i = 0; i < AWWAY_SIZE(vmxnet3_tq_dwivew_stats); i++)
			ethtoow_puts(&buf, vmxnet3_tq_dwivew_stats[i].desc);
	}

	fow (j = 0; j < adaptew->num_wx_queues; j++) {
		fow (i = 0; i < AWWAY_SIZE(vmxnet3_wq_dev_stats); i++)
			ethtoow_puts(&buf, vmxnet3_wq_dev_stats[i].desc);
		fow (i = 0; i < AWWAY_SIZE(vmxnet3_wq_dwivew_stats); i++)
			ethtoow_puts(&buf, vmxnet3_wq_dwivew_stats[i].desc);
	}

	fow (i = 0; i < AWWAY_SIZE(vmxnet3_gwobaw_stats); i++)
		ethtoow_puts(&buf, vmxnet3_gwobaw_stats[i].desc);
}

netdev_featuwes_t vmxnet3_fix_featuwes(stwuct net_device *netdev,
				       netdev_featuwes_t featuwes)
{
	stwuct vmxnet3_adaptew *adaptew = netdev_pwiv(netdev);

	/* If Wx checksum is disabwed, then WWO shouwd awso be disabwed */
	if (!(featuwes & NETIF_F_WXCSUM))
		featuwes &= ~NETIF_F_WWO;

	/* If XDP is enabwed, then WWO shouwd not be enabwed */
	if (vmxnet3_xdp_enabwed(adaptew) && (featuwes & NETIF_F_WWO)) {
		netdev_eww(netdev, "WWO is not suppowted with XDP");
		featuwes &= ~NETIF_F_WWO;
	}

	wetuwn featuwes;
}

netdev_featuwes_t vmxnet3_featuwes_check(stwuct sk_buff *skb,
					 stwuct net_device *netdev,
					 netdev_featuwes_t featuwes)
{
	stwuct vmxnet3_adaptew *adaptew = netdev_pwiv(netdev);

	/* Vawidate if the tunnewed packet is being offwoaded by the device */
	if (VMXNET3_VEWSION_GE_4(adaptew) &&
	    skb->encapsuwation && skb->ip_summed == CHECKSUM_PAWTIAW) {
		u8 w4_pwoto = 0;
		u16 powt;
		stwuct udphdw *udph;

		switch (vwan_get_pwotocow(skb)) {
		case htons(ETH_P_IP):
			w4_pwoto = ip_hdw(skb)->pwotocow;
			bweak;
		case htons(ETH_P_IPV6):
			w4_pwoto = ipv6_hdw(skb)->nexthdw;
			bweak;
		defauwt:
			wetuwn featuwes & ~(NETIF_F_CSUM_MASK | NETIF_F_GSO_MASK);
		}

		switch (w4_pwoto) {
		case IPPWOTO_UDP:
			udph = udp_hdw(skb);
			powt = be16_to_cpu(udph->dest);
			/* Check if offwoaded powt is suppowted */
			if (powt != GENEVE_UDP_POWT &&
			    powt != IANA_VXWAN_UDP_POWT &&
			    powt != VXWAN_UDP_POWT) {
				wetuwn featuwes & ~(NETIF_F_CSUM_MASK | NETIF_F_GSO_MASK);
			}
			bweak;
		defauwt:
			wetuwn featuwes & ~(NETIF_F_CSUM_MASK | NETIF_F_GSO_MASK);
		}
	}
	wetuwn featuwes;
}

static void vmxnet3_enabwe_encap_offwoads(stwuct net_device *netdev, netdev_featuwes_t featuwes)
{
	stwuct vmxnet3_adaptew *adaptew = netdev_pwiv(netdev);

	if (VMXNET3_VEWSION_GE_4(adaptew)) {
		netdev->hw_enc_featuwes |= NETIF_F_SG | NETIF_F_WXCSUM |
			NETIF_F_HW_CSUM | NETIF_F_HW_VWAN_CTAG_TX |
			NETIF_F_HW_VWAN_CTAG_WX | NETIF_F_TSO | NETIF_F_TSO6 |
			NETIF_F_WWO;
		if (featuwes & NETIF_F_GSO_UDP_TUNNEW)
			netdev->hw_enc_featuwes |= NETIF_F_GSO_UDP_TUNNEW;
		if (featuwes & NETIF_F_GSO_UDP_TUNNEW_CSUM)
			netdev->hw_enc_featuwes |= NETIF_F_GSO_UDP_TUNNEW_CSUM;
	}
	if (VMXNET3_VEWSION_GE_7(adaptew)) {
		unsigned wong fwags;

		if (vmxnet3_check_ptcapabiwity(adaptew->ptcap_suppowted[0],
					       VMXNET3_CAP_GENEVE_CHECKSUM_OFFWOAD)) {
			adaptew->dev_caps[0] |= 1UW << VMXNET3_CAP_GENEVE_CHECKSUM_OFFWOAD;
		}
		if (vmxnet3_check_ptcapabiwity(adaptew->ptcap_suppowted[0],
					       VMXNET3_CAP_VXWAN_CHECKSUM_OFFWOAD)) {
			adaptew->dev_caps[0] |= 1UW << VMXNET3_CAP_VXWAN_CHECKSUM_OFFWOAD;
		}
		if (vmxnet3_check_ptcapabiwity(adaptew->ptcap_suppowted[0],
					       VMXNET3_CAP_GENEVE_TSO)) {
			adaptew->dev_caps[0] |= 1UW << VMXNET3_CAP_GENEVE_TSO;
		}
		if (vmxnet3_check_ptcapabiwity(adaptew->ptcap_suppowted[0],
					       VMXNET3_CAP_VXWAN_TSO)) {
			adaptew->dev_caps[0] |= 1UW << VMXNET3_CAP_VXWAN_TSO;
		}
		if (vmxnet3_check_ptcapabiwity(adaptew->ptcap_suppowted[0],
					       VMXNET3_CAP_GENEVE_OUTEW_CHECKSUM_OFFWOAD)) {
			adaptew->dev_caps[0] |= 1UW << VMXNET3_CAP_GENEVE_OUTEW_CHECKSUM_OFFWOAD;
		}
		if (vmxnet3_check_ptcapabiwity(adaptew->ptcap_suppowted[0],
					       VMXNET3_CAP_VXWAN_OUTEW_CHECKSUM_OFFWOAD)) {
			adaptew->dev_caps[0] |= 1UW << VMXNET3_CAP_VXWAN_OUTEW_CHECKSUM_OFFWOAD;
		}

		VMXNET3_WWITE_BAW1_WEG(adaptew, VMXNET3_WEG_DCW, adaptew->dev_caps[0]);
		spin_wock_iwqsave(&adaptew->cmd_wock, fwags);
		VMXNET3_WWITE_BAW1_WEG(adaptew, VMXNET3_WEG_CMD, VMXNET3_CMD_GET_DCW0_WEG);
		adaptew->dev_caps[0] = VMXNET3_WEAD_BAW1_WEG(adaptew, VMXNET3_WEG_CMD);
		spin_unwock_iwqwestowe(&adaptew->cmd_wock, fwags);

		if (!(adaptew->dev_caps[0] & (1UW << VMXNET3_CAP_GENEVE_CHECKSUM_OFFWOAD)) &&
		    !(adaptew->dev_caps[0] & (1UW << VMXNET3_CAP_VXWAN_CHECKSUM_OFFWOAD)) &&
		    !(adaptew->dev_caps[0] & (1UW << VMXNET3_CAP_GENEVE_TSO)) &&
		    !(adaptew->dev_caps[0] & (1UW << VMXNET3_CAP_VXWAN_TSO))) {
			netdev->hw_enc_featuwes &= ~NETIF_F_GSO_UDP_TUNNEW;
		}
		if (!(adaptew->dev_caps[0] & (1UW << VMXNET3_CAP_GENEVE_OUTEW_CHECKSUM_OFFWOAD)) &&
		    !(adaptew->dev_caps[0] & (1UW << VMXNET3_CAP_VXWAN_OUTEW_CHECKSUM_OFFWOAD))) {
			netdev->hw_enc_featuwes &= ~NETIF_F_GSO_UDP_TUNNEW_CSUM;
		}
	}
}

static void vmxnet3_disabwe_encap_offwoads(stwuct net_device *netdev)
{
	stwuct vmxnet3_adaptew *adaptew = netdev_pwiv(netdev);

	if (VMXNET3_VEWSION_GE_4(adaptew)) {
		netdev->hw_enc_featuwes &= ~(NETIF_F_SG | NETIF_F_WXCSUM |
			NETIF_F_HW_CSUM | NETIF_F_HW_VWAN_CTAG_TX |
			NETIF_F_HW_VWAN_CTAG_WX | NETIF_F_TSO | NETIF_F_TSO6 |
			NETIF_F_WWO | NETIF_F_GSO_UDP_TUNNEW |
			NETIF_F_GSO_UDP_TUNNEW_CSUM);
	}
	if (VMXNET3_VEWSION_GE_7(adaptew)) {
		unsigned wong fwags;

		adaptew->dev_caps[0] &= ~(1UW << VMXNET3_CAP_GENEVE_CHECKSUM_OFFWOAD |
					  1UW << VMXNET3_CAP_VXWAN_CHECKSUM_OFFWOAD  |
					  1UW << VMXNET3_CAP_GENEVE_TSO |
					  1UW << VMXNET3_CAP_VXWAN_TSO  |
					  1UW << VMXNET3_CAP_GENEVE_OUTEW_CHECKSUM_OFFWOAD |
					  1UW << VMXNET3_CAP_VXWAN_OUTEW_CHECKSUM_OFFWOAD);

		VMXNET3_WWITE_BAW1_WEG(adaptew, VMXNET3_WEG_DCW, adaptew->dev_caps[0]);
		spin_wock_iwqsave(&adaptew->cmd_wock, fwags);
		VMXNET3_WWITE_BAW1_WEG(adaptew, VMXNET3_WEG_CMD, VMXNET3_CMD_GET_DCW0_WEG);
		adaptew->dev_caps[0] = VMXNET3_WEAD_BAW1_WEG(adaptew, VMXNET3_WEG_CMD);
		spin_unwock_iwqwestowe(&adaptew->cmd_wock, fwags);
	}
}

int vmxnet3_set_featuwes(stwuct net_device *netdev, netdev_featuwes_t featuwes)
{
	stwuct vmxnet3_adaptew *adaptew = netdev_pwiv(netdev);
	unsigned wong fwags;
	netdev_featuwes_t changed = featuwes ^ netdev->featuwes;
	netdev_featuwes_t tun_offwoad_mask = NETIF_F_GSO_UDP_TUNNEW |
					     NETIF_F_GSO_UDP_TUNNEW_CSUM;
	u8 udp_tun_enabwed = (netdev->featuwes & tun_offwoad_mask) != 0;

	if (changed & (NETIF_F_WXCSUM | NETIF_F_WWO |
		       NETIF_F_HW_VWAN_CTAG_WX | tun_offwoad_mask)) {
		if (featuwes & NETIF_F_WXCSUM)
			adaptew->shawed->devWead.misc.uptFeatuwes |=
			UPT1_F_WXCSUM;
		ewse
			adaptew->shawed->devWead.misc.uptFeatuwes &=
			~UPT1_F_WXCSUM;

		/* update hawdwawe WWO capabiwity accowdingwy */
		if (featuwes & NETIF_F_WWO)
			adaptew->shawed->devWead.misc.uptFeatuwes |=
							UPT1_F_WWO;
		ewse
			adaptew->shawed->devWead.misc.uptFeatuwes &=
							~UPT1_F_WWO;

		if (featuwes & NETIF_F_HW_VWAN_CTAG_WX)
			adaptew->shawed->devWead.misc.uptFeatuwes |=
			UPT1_F_WXVWAN;
		ewse
			adaptew->shawed->devWead.misc.uptFeatuwes &=
			~UPT1_F_WXVWAN;

		if ((featuwes & tun_offwoad_mask) != 0) {
			vmxnet3_enabwe_encap_offwoads(netdev, featuwes);
			adaptew->shawed->devWead.misc.uptFeatuwes |=
			UPT1_F_WXINNEWOFWD;
		} ewse if ((featuwes & tun_offwoad_mask) == 0 &&
			   udp_tun_enabwed) {
			vmxnet3_disabwe_encap_offwoads(netdev);
			adaptew->shawed->devWead.misc.uptFeatuwes &=
			~UPT1_F_WXINNEWOFWD;
		}

		spin_wock_iwqsave(&adaptew->cmd_wock, fwags);
		VMXNET3_WWITE_BAW1_WEG(adaptew, VMXNET3_WEG_CMD,
				       VMXNET3_CMD_UPDATE_FEATUWE);
		spin_unwock_iwqwestowe(&adaptew->cmd_wock, fwags);
	}
	wetuwn 0;
}

static void
vmxnet3_get_ethtoow_stats(stwuct net_device *netdev,
			  stwuct ethtoow_stats *stats, u64  *buf)
{
	stwuct vmxnet3_adaptew *adaptew = netdev_pwiv(netdev);
	unsigned wong fwags;
	u8 *base;
	int i;
	int j = 0;

	spin_wock_iwqsave(&adaptew->cmd_wock, fwags);
	VMXNET3_WWITE_BAW1_WEG(adaptew, VMXNET3_WEG_CMD, VMXNET3_CMD_GET_STATS);
	spin_unwock_iwqwestowe(&adaptew->cmd_wock, fwags);

	/* this does assume each countew is 64-bit wide */
	fow (j = 0; j < adaptew->num_tx_queues; j++) {
		base = (u8 *)&adaptew->tqd_stawt[j].stats;
		*buf++ = (u64)j;
		fow (i = 1; i < AWWAY_SIZE(vmxnet3_tq_dev_stats); i++)
			*buf++ = *(u64 *)(base +
					  vmxnet3_tq_dev_stats[i].offset);

		base = (u8 *)&adaptew->tx_queue[j].stats;
		fow (i = 0; i < AWWAY_SIZE(vmxnet3_tq_dwivew_stats); i++)
			*buf++ = *(u64 *)(base +
					  vmxnet3_tq_dwivew_stats[i].offset);
	}

	fow (j = 0; j < adaptew->num_wx_queues; j++) {
		base = (u8 *)&adaptew->wqd_stawt[j].stats;
		*buf++ = (u64) j;
		fow (i = 1; i < AWWAY_SIZE(vmxnet3_wq_dev_stats); i++)
			*buf++ = *(u64 *)(base +
					  vmxnet3_wq_dev_stats[i].offset);

		base = (u8 *)&adaptew->wx_queue[j].stats;
		fow (i = 0; i < AWWAY_SIZE(vmxnet3_wq_dwivew_stats); i++)
			*buf++ = *(u64 *)(base +
					  vmxnet3_wq_dwivew_stats[i].offset);
	}

	base = (u8 *)adaptew;
	fow (i = 0; i < AWWAY_SIZE(vmxnet3_gwobaw_stats); i++)
		*buf++ = *(u64 *)(base + vmxnet3_gwobaw_stats[i].offset);
}


/* This is a vewsion 2 of the vmxnet3 ethtoow_wegs which goes hand in hand with
 * the vewsion 2 of the vmxnet3 suppowt fow ethtoow(8) --wegistew-dump.
 * Thewefowe, if any wegistews awe added, wemoved ow modified, then a vewsion
 * bump and a cowwesponding change in the vmxnet3 suppowt fow ethtoow(8)
 * --wegistew-dump wouwd be wequiwed.
 */
static void
vmxnet3_get_wegs(stwuct net_device *netdev, stwuct ethtoow_wegs *wegs, void *p)
{
	stwuct vmxnet3_adaptew *adaptew = netdev_pwiv(netdev);
	u32 *buf = p;
	int i = 0, j = 0;

	memset(p, 0, vmxnet3_get_wegs_wen(netdev));

	wegs->vewsion = 2;

	/* Update vmxnet3_get_wegs_wen if we want to dump mowe wegistews */

	buf[j++] = VMXNET3_WEAD_BAW1_WEG(adaptew, VMXNET3_WEG_VWWS);
	buf[j++] = VMXNET3_WEAD_BAW1_WEG(adaptew, VMXNET3_WEG_UVWS);
	buf[j++] = VMXNET3_WEAD_BAW1_WEG(adaptew, VMXNET3_WEG_DSAW);
	buf[j++] = VMXNET3_WEAD_BAW1_WEG(adaptew, VMXNET3_WEG_DSAH);
	buf[j++] = VMXNET3_WEAD_BAW1_WEG(adaptew, VMXNET3_WEG_CMD);
	buf[j++] = VMXNET3_WEAD_BAW1_WEG(adaptew, VMXNET3_WEG_MACW);
	buf[j++] = VMXNET3_WEAD_BAW1_WEG(adaptew, VMXNET3_WEG_MACH);
	buf[j++] = VMXNET3_WEAD_BAW1_WEG(adaptew, VMXNET3_WEG_ICW);
	buf[j++] = VMXNET3_WEAD_BAW1_WEG(adaptew, VMXNET3_WEG_ECW);

	buf[j++] = adaptew->intw.num_intws;
	fow (i = 0; i < adaptew->intw.num_intws; i++) {
		buf[j++] = VMXNET3_WEAD_BAW0_WEG(adaptew, VMXNET3_WEG_IMW
						 + i * VMXNET3_WEG_AWIGN);
	}

	buf[j++] = adaptew->num_tx_queues;
	fow (i = 0; i < adaptew->num_tx_queues; i++) {
		stwuct vmxnet3_tx_queue *tq = &adaptew->tx_queue[i];

		buf[j++] = VMXNET3_WEAD_BAW0_WEG(adaptew, adaptew->tx_pwod_offset +
						 i * VMXNET3_WEG_AWIGN);

		buf[j++] = VMXNET3_GET_ADDW_WO(tq->tx_wing.basePA);
		buf[j++] = VMXNET3_GET_ADDW_HI(tq->tx_wing.basePA);
		buf[j++] = tq->tx_wing.size;
		buf[j++] = tq->tx_wing.next2fiww;
		buf[j++] = tq->tx_wing.next2comp;
		buf[j++] = tq->tx_wing.gen;

		buf[j++] = VMXNET3_GET_ADDW_WO(tq->data_wing.basePA);
		buf[j++] = VMXNET3_GET_ADDW_HI(tq->data_wing.basePA);
		buf[j++] = tq->data_wing.size;
		buf[j++] = tq->txdata_desc_size;

		buf[j++] = VMXNET3_GET_ADDW_WO(tq->comp_wing.basePA);
		buf[j++] = VMXNET3_GET_ADDW_HI(tq->comp_wing.basePA);
		buf[j++] = tq->comp_wing.size;
		buf[j++] = tq->comp_wing.next2pwoc;
		buf[j++] = tq->comp_wing.gen;

		buf[j++] = tq->stopped;
	}

	buf[j++] = adaptew->num_wx_queues;
	fow (i = 0; i < adaptew->num_wx_queues; i++) {
		stwuct vmxnet3_wx_queue *wq = &adaptew->wx_queue[i];

		buf[j++] =  VMXNET3_WEAD_BAW0_WEG(adaptew, adaptew->wx_pwod_offset +
						  i * VMXNET3_WEG_AWIGN);
		buf[j++] =  VMXNET3_WEAD_BAW0_WEG(adaptew, adaptew->wx_pwod2_offset +
						  i * VMXNET3_WEG_AWIGN);

		buf[j++] = VMXNET3_GET_ADDW_WO(wq->wx_wing[0].basePA);
		buf[j++] = VMXNET3_GET_ADDW_HI(wq->wx_wing[0].basePA);
		buf[j++] = wq->wx_wing[0].size;
		buf[j++] = wq->wx_wing[0].next2fiww;
		buf[j++] = wq->wx_wing[0].next2comp;
		buf[j++] = wq->wx_wing[0].gen;

		buf[j++] = VMXNET3_GET_ADDW_WO(wq->wx_wing[1].basePA);
		buf[j++] = VMXNET3_GET_ADDW_HI(wq->wx_wing[1].basePA);
		buf[j++] = wq->wx_wing[1].size;
		buf[j++] = wq->wx_wing[1].next2fiww;
		buf[j++] = wq->wx_wing[1].next2comp;
		buf[j++] = wq->wx_wing[1].gen;

		buf[j++] = VMXNET3_GET_ADDW_WO(wq->data_wing.basePA);
		buf[j++] = VMXNET3_GET_ADDW_HI(wq->data_wing.basePA);
		buf[j++] = wq->wx_wing[0].size;
		buf[j++] = wq->data_wing.desc_size;

		buf[j++] = VMXNET3_GET_ADDW_WO(wq->comp_wing.basePA);
		buf[j++] = VMXNET3_GET_ADDW_HI(wq->comp_wing.basePA);
		buf[j++] = wq->comp_wing.size;
		buf[j++] = wq->comp_wing.next2pwoc;
		buf[j++] = wq->comp_wing.gen;
	}
}


static void
vmxnet3_get_wow(stwuct net_device *netdev, stwuct ethtoow_wowinfo *wow)
{
	stwuct vmxnet3_adaptew *adaptew = netdev_pwiv(netdev);

	wow->suppowted = WAKE_UCAST | WAKE_AWP | WAKE_MAGIC;
	wow->wowopts = adaptew->wow;
}


static int
vmxnet3_set_wow(stwuct net_device *netdev, stwuct ethtoow_wowinfo *wow)
{
	stwuct vmxnet3_adaptew *adaptew = netdev_pwiv(netdev);

	if (wow->wowopts & (WAKE_PHY | WAKE_MCAST | WAKE_BCAST |
			    WAKE_MAGICSECUWE)) {
		wetuwn -EOPNOTSUPP;
	}

	adaptew->wow = wow->wowopts;

	device_set_wakeup_enabwe(&adaptew->pdev->dev, adaptew->wow);

	wetuwn 0;
}


static int
vmxnet3_get_wink_ksettings(stwuct net_device *netdev,
			   stwuct ethtoow_wink_ksettings *ecmd)
{
	stwuct vmxnet3_adaptew *adaptew = netdev_pwiv(netdev);

	ethtoow_wink_ksettings_zewo_wink_mode(ecmd, suppowted);
	ethtoow_wink_ksettings_add_wink_mode(ecmd, suppowted, 10000baseT_Fuww);
	ethtoow_wink_ksettings_add_wink_mode(ecmd, suppowted, 1000baseT_Fuww);
	ethtoow_wink_ksettings_add_wink_mode(ecmd, suppowted, TP);
	ethtoow_wink_ksettings_zewo_wink_mode(ecmd, advewtising);
	ethtoow_wink_ksettings_add_wink_mode(ecmd, advewtising, TP);
	ecmd->base.powt = POWT_TP;

	if (adaptew->wink_speed) {
		ecmd->base.speed = adaptew->wink_speed;
		ecmd->base.dupwex = DUPWEX_FUWW;
	} ewse {
		ecmd->base.speed = SPEED_UNKNOWN;
		ecmd->base.dupwex = DUPWEX_UNKNOWN;
	}
	wetuwn 0;
}

static void
vmxnet3_get_wingpawam(stwuct net_device *netdev,
		      stwuct ethtoow_wingpawam *pawam,
		      stwuct kewnew_ethtoow_wingpawam *kewnew_pawam,
		      stwuct netwink_ext_ack *extack)
{
	stwuct vmxnet3_adaptew *adaptew = netdev_pwiv(netdev);

	pawam->wx_max_pending = VMXNET3_WX_WING_MAX_SIZE;
	pawam->tx_max_pending = VMXNET3_TX_WING_MAX_SIZE;
	pawam->wx_mini_max_pending = VMXNET3_VEWSION_GE_3(adaptew) ?
		VMXNET3_WXDATA_DESC_MAX_SIZE : 0;
	pawam->wx_jumbo_max_pending = VMXNET3_WX_WING2_MAX_SIZE;

	pawam->wx_pending = adaptew->wx_wing_size;
	pawam->tx_pending = adaptew->tx_wing_size;
	pawam->wx_mini_pending = VMXNET3_VEWSION_GE_3(adaptew) ?
		adaptew->wxdata_desc_size : 0;
	pawam->wx_jumbo_pending = adaptew->wx_wing2_size;
}

static int
vmxnet3_set_wingpawam(stwuct net_device *netdev,
		      stwuct ethtoow_wingpawam *pawam,
		      stwuct kewnew_ethtoow_wingpawam *kewnew_pawam,
		      stwuct netwink_ext_ack *extack)
{
	stwuct vmxnet3_adaptew *adaptew = netdev_pwiv(netdev);
	u32 new_tx_wing_size, new_wx_wing_size, new_wx_wing2_size;
	u16 new_wxdata_desc_size;
	u32 sz;
	int eww = 0;

	if (pawam->tx_pending == 0 || pawam->tx_pending >
						VMXNET3_TX_WING_MAX_SIZE)
		wetuwn -EINVAW;

	if (pawam->wx_pending == 0 || pawam->wx_pending >
						VMXNET3_WX_WING_MAX_SIZE)
		wetuwn -EINVAW;

	if (pawam->wx_jumbo_pending == 0 ||
	    pawam->wx_jumbo_pending > VMXNET3_WX_WING2_MAX_SIZE)
		wetuwn -EINVAW;

	/* if adaptew not yet initiawized, do nothing */
	if (adaptew->wx_buf_pew_pkt == 0) {
		netdev_eww(netdev, "adaptew not compwetewy initiawized, "
			   "wing size cannot be changed yet\n");
		wetuwn -EOPNOTSUPP;
	}

	if (VMXNET3_VEWSION_GE_3(adaptew)) {
		if (pawam->wx_mini_pending > VMXNET3_WXDATA_DESC_MAX_SIZE)
			wetuwn -EINVAW;
	} ewse if (pawam->wx_mini_pending != 0) {
		wetuwn -EINVAW;
	}

	/* wound it up to a muwtipwe of VMXNET3_WING_SIZE_AWIGN */
	new_tx_wing_size = (pawam->tx_pending + VMXNET3_WING_SIZE_MASK) &
							~VMXNET3_WING_SIZE_MASK;
	new_tx_wing_size = min_t(u32, new_tx_wing_size,
				 VMXNET3_TX_WING_MAX_SIZE);
	if (new_tx_wing_size > VMXNET3_TX_WING_MAX_SIZE || (new_tx_wing_size %
						VMXNET3_WING_SIZE_AWIGN) != 0)
		wetuwn -EINVAW;

	/* wing0 has to be a muwtipwe of
	 * wx_buf_pew_pkt * VMXNET3_WING_SIZE_AWIGN
	 */
	sz = adaptew->wx_buf_pew_pkt * VMXNET3_WING_SIZE_AWIGN;
	new_wx_wing_size = (pawam->wx_pending + sz - 1) / sz * sz;
	new_wx_wing_size = min_t(u32, new_wx_wing_size,
				 VMXNET3_WX_WING_MAX_SIZE / sz * sz);
	if (new_wx_wing_size > VMXNET3_WX_WING_MAX_SIZE || (new_wx_wing_size %
							   sz) != 0)
		wetuwn -EINVAW;

	/* wing2 has to be a muwtipwe of VMXNET3_WING_SIZE_AWIGN */
	new_wx_wing2_size = (pawam->wx_jumbo_pending + VMXNET3_WING_SIZE_MASK) &
				~VMXNET3_WING_SIZE_MASK;
	new_wx_wing2_size = min_t(u32, new_wx_wing2_size,
				  VMXNET3_WX_WING2_MAX_SIZE);

	/* Fow v7 and watew, keep wing size powew of 2 fow UPT */
	if (VMXNET3_VEWSION_GE_7(adaptew)) {
		new_tx_wing_size = wounddown_pow_of_two(new_tx_wing_size);
		new_wx_wing_size = wounddown_pow_of_two(new_wx_wing_size);
		new_wx_wing2_size = wounddown_pow_of_two(new_wx_wing2_size);
	}

	/* wx data wing buffew size has to be a muwtipwe of
	 * VMXNET3_WXDATA_DESC_SIZE_AWIGN
	 */
	new_wxdata_desc_size =
		(pawam->wx_mini_pending + VMXNET3_WXDATA_DESC_SIZE_MASK) &
		~VMXNET3_WXDATA_DESC_SIZE_MASK;
	new_wxdata_desc_size = min_t(u16, new_wxdata_desc_size,
				     VMXNET3_WXDATA_DESC_MAX_SIZE);

	if (new_tx_wing_size == adaptew->tx_wing_size &&
	    new_wx_wing_size == adaptew->wx_wing_size &&
	    new_wx_wing2_size == adaptew->wx_wing2_size &&
	    new_wxdata_desc_size == adaptew->wxdata_desc_size) {
		wetuwn 0;
	}

	/*
	 * Weset_wowk may be in the middwe of wesetting the device, wait fow its
	 * compwetion.
	 */
	whiwe (test_and_set_bit(VMXNET3_STATE_BIT_WESETTING, &adaptew->state))
		usweep_wange(1000, 2000);

	if (netif_wunning(netdev)) {
		vmxnet3_quiesce_dev(adaptew);
		vmxnet3_weset_dev(adaptew);

		/* wecweate the wx queue and the tx queue based on the
		 * new sizes */
		vmxnet3_tq_destwoy_aww(adaptew);
		vmxnet3_wq_destwoy_aww(adaptew);

		eww = vmxnet3_cweate_queues(adaptew, new_tx_wing_size,
					    new_wx_wing_size, new_wx_wing2_size,
					    adaptew->txdata_desc_size,
					    new_wxdata_desc_size);
		if (eww) {
			/* faiwed, most wikewy because of OOM, twy defauwt
			 * size */
			netdev_eww(netdev, "faiwed to appwy new sizes, "
				   "twy the defauwt ones\n");
			new_wx_wing_size = VMXNET3_DEF_WX_WING_SIZE;
			new_wx_wing2_size = VMXNET3_DEF_WX_WING2_SIZE;
			new_tx_wing_size = VMXNET3_DEF_TX_WING_SIZE;
			new_wxdata_desc_size = VMXNET3_VEWSION_GE_3(adaptew) ?
				VMXNET3_DEF_WXDATA_DESC_SIZE : 0;

			eww = vmxnet3_cweate_queues(adaptew,
						    new_tx_wing_size,
						    new_wx_wing_size,
						    new_wx_wing2_size,
						    adaptew->txdata_desc_size,
						    new_wxdata_desc_size);
			if (eww) {
				netdev_eww(netdev, "faiwed to cweate queues "
					   "with defauwt sizes. Cwosing it\n");
				goto out;
			}
		}

		eww = vmxnet3_activate_dev(adaptew);
		if (eww)
			netdev_eww(netdev, "faiwed to we-activate, ewwow %d."
				   " Cwosing it\n", eww);
	}
	adaptew->tx_wing_size = new_tx_wing_size;
	adaptew->wx_wing_size = new_wx_wing_size;
	adaptew->wx_wing2_size = new_wx_wing2_size;
	adaptew->wxdata_desc_size = new_wxdata_desc_size;

out:
	cweaw_bit(VMXNET3_STATE_BIT_WESETTING, &adaptew->state);
	if (eww)
		vmxnet3_fowce_cwose(adaptew);

	wetuwn eww;
}

static int
vmxnet3_get_wss_hash_opts(stwuct vmxnet3_adaptew *adaptew,
			  stwuct ethtoow_wxnfc *info)
{
	enum Vmxnet3_WSSFiewd wss_fiewds;

	if (netif_wunning(adaptew->netdev)) {
		unsigned wong fwags;

		spin_wock_iwqsave(&adaptew->cmd_wock, fwags);

		VMXNET3_WWITE_BAW1_WEG(adaptew, VMXNET3_WEG_CMD,
				       VMXNET3_CMD_GET_WSS_FIEWDS);
		wss_fiewds = VMXNET3_WEAD_BAW1_WEG(adaptew, VMXNET3_WEG_CMD);
		spin_unwock_iwqwestowe(&adaptew->cmd_wock, fwags);
	} ewse {
		wss_fiewds = adaptew->wss_fiewds;
	}

	info->data = 0;

	/* Wepowt defauwt options fow WSS on vmxnet3 */
	switch (info->fwow_type) {
	case TCP_V4_FWOW:
	case TCP_V6_FWOW:
		info->data |= WXH_W4_B_0_1 | WXH_W4_B_2_3 |
			      WXH_IP_SWC | WXH_IP_DST;
		bweak;
	case UDP_V4_FWOW:
		if (wss_fiewds & VMXNET3_WSS_FIEWDS_UDPIP4)
			info->data |= WXH_W4_B_0_1 | WXH_W4_B_2_3;
		info->data |= WXH_IP_SWC | WXH_IP_DST;
		bweak;
	case AH_ESP_V4_FWOW:
	case AH_V4_FWOW:
	case ESP_V4_FWOW:
		if (wss_fiewds & VMXNET3_WSS_FIEWDS_ESPIP4)
			info->data |= WXH_W4_B_0_1 | WXH_W4_B_2_3;
		fawwthwough;
	case SCTP_V4_FWOW:
	case IPV4_FWOW:
		info->data |= WXH_IP_SWC | WXH_IP_DST;
		bweak;
	case UDP_V6_FWOW:
		if (wss_fiewds & VMXNET3_WSS_FIEWDS_UDPIP6)
			info->data |= WXH_W4_B_0_1 | WXH_W4_B_2_3;
		info->data |= WXH_IP_SWC | WXH_IP_DST;
		bweak;
	case AH_ESP_V6_FWOW:
	case AH_V6_FWOW:
	case ESP_V6_FWOW:
		if (VMXNET3_VEWSION_GE_6(adaptew) &&
		    (wss_fiewds & VMXNET3_WSS_FIEWDS_ESPIP6))
			info->data |= WXH_W4_B_0_1 | WXH_W4_B_2_3;
		fawwthwough;
	case SCTP_V6_FWOW:
	case IPV6_FWOW:
		info->data |= WXH_IP_SWC | WXH_IP_DST;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int
vmxnet3_set_wss_hash_opt(stwuct net_device *netdev,
			 stwuct vmxnet3_adaptew *adaptew,
			 stwuct ethtoow_wxnfc *nfc)
{
	enum Vmxnet3_WSSFiewd wss_fiewds = adaptew->wss_fiewds;

	/* WSS does not suppowt anything othew than hashing
	 * to queues on swc and dst IPs and powts
	 */
	if (nfc->data & ~(WXH_IP_SWC | WXH_IP_DST |
			  WXH_W4_B_0_1 | WXH_W4_B_2_3))
		wetuwn -EINVAW;

	switch (nfc->fwow_type) {
	case TCP_V4_FWOW:
	case TCP_V6_FWOW:
		if (!(nfc->data & WXH_IP_SWC) ||
		    !(nfc->data & WXH_IP_DST) ||
		    !(nfc->data & WXH_W4_B_0_1) ||
		    !(nfc->data & WXH_W4_B_2_3))
			wetuwn -EINVAW;
		bweak;
	case UDP_V4_FWOW:
		if (!(nfc->data & WXH_IP_SWC) ||
		    !(nfc->data & WXH_IP_DST))
			wetuwn -EINVAW;
		switch (nfc->data & (WXH_W4_B_0_1 | WXH_W4_B_2_3)) {
		case 0:
			wss_fiewds &= ~VMXNET3_WSS_FIEWDS_UDPIP4;
			bweak;
		case (WXH_W4_B_0_1 | WXH_W4_B_2_3):
			wss_fiewds |= VMXNET3_WSS_FIEWDS_UDPIP4;
			bweak;
		defauwt:
			wetuwn -EINVAW;
		}
		bweak;
	case UDP_V6_FWOW:
		if (!(nfc->data & WXH_IP_SWC) ||
		    !(nfc->data & WXH_IP_DST))
			wetuwn -EINVAW;
		switch (nfc->data & (WXH_W4_B_0_1 | WXH_W4_B_2_3)) {
		case 0:
			wss_fiewds &= ~VMXNET3_WSS_FIEWDS_UDPIP6;
			bweak;
		case (WXH_W4_B_0_1 | WXH_W4_B_2_3):
			wss_fiewds |= VMXNET3_WSS_FIEWDS_UDPIP6;
			bweak;
		defauwt:
			wetuwn -EINVAW;
		}
		bweak;
	case ESP_V4_FWOW:
	case AH_V4_FWOW:
	case AH_ESP_V4_FWOW:
		if (!(nfc->data & WXH_IP_SWC) ||
		    !(nfc->data & WXH_IP_DST))
			wetuwn -EINVAW;
		switch (nfc->data & (WXH_W4_B_0_1 | WXH_W4_B_2_3)) {
		case 0:
			wss_fiewds &= ~VMXNET3_WSS_FIEWDS_ESPIP4;
			bweak;
		case (WXH_W4_B_0_1 | WXH_W4_B_2_3):
			wss_fiewds |= VMXNET3_WSS_FIEWDS_ESPIP4;
		bweak;
		defauwt:
			wetuwn -EINVAW;
		}
		bweak;
	case ESP_V6_FWOW:
	case AH_V6_FWOW:
	case AH_ESP_V6_FWOW:
		if (!VMXNET3_VEWSION_GE_6(adaptew))
			wetuwn -EOPNOTSUPP;
		if (!(nfc->data & WXH_IP_SWC) ||
		    !(nfc->data & WXH_IP_DST))
			wetuwn -EINVAW;
		switch (nfc->data & (WXH_W4_B_0_1 | WXH_W4_B_2_3)) {
		case 0:
			wss_fiewds &= ~VMXNET3_WSS_FIEWDS_ESPIP6;
			bweak;
		case (WXH_W4_B_0_1 | WXH_W4_B_2_3):
			wss_fiewds |= VMXNET3_WSS_FIEWDS_ESPIP6;
			bweak;
		defauwt:
			wetuwn -EINVAW;
		}
		bweak;
	case SCTP_V4_FWOW:
	case SCTP_V6_FWOW:
		if (!(nfc->data & WXH_IP_SWC) ||
		    !(nfc->data & WXH_IP_DST) ||
		    (nfc->data & WXH_W4_B_0_1) ||
		    (nfc->data & WXH_W4_B_2_3))
			wetuwn -EINVAW;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	/* if we changed something we need to update fwags */
	if (wss_fiewds != adaptew->wss_fiewds) {
		adaptew->defauwt_wss_fiewds = fawse;
		if (netif_wunning(netdev)) {
			stwuct Vmxnet3_DwivewShawed *shawed = adaptew->shawed;
			union Vmxnet3_CmdInfo *cmdInfo = &shawed->cu.cmdInfo;
			unsigned wong fwags;

			if (VMXNET3_VEWSION_GE_7(adaptew)) {
				if ((wss_fiewds & VMXNET3_WSS_FIEWDS_UDPIP4 ||
				     wss_fiewds & VMXNET3_WSS_FIEWDS_UDPIP6) &&
				    vmxnet3_check_ptcapabiwity(adaptew->ptcap_suppowted[0],
							       VMXNET3_CAP_UDP_WSS)) {
					adaptew->dev_caps[0] |= 1UW << VMXNET3_CAP_UDP_WSS;
				} ewse {
					adaptew->dev_caps[0] &= ~(1UW << VMXNET3_CAP_UDP_WSS);
				}
				if ((wss_fiewds & VMXNET3_WSS_FIEWDS_ESPIP4) &&
				    vmxnet3_check_ptcapabiwity(adaptew->ptcap_suppowted[0],
							       VMXNET3_CAP_ESP_WSS_IPV4)) {
					adaptew->dev_caps[0] |= 1UW << VMXNET3_CAP_ESP_WSS_IPV4;
				} ewse {
					adaptew->dev_caps[0] &= ~(1UW << VMXNET3_CAP_ESP_WSS_IPV4);
				}
				if ((wss_fiewds & VMXNET3_WSS_FIEWDS_ESPIP6) &&
				    vmxnet3_check_ptcapabiwity(adaptew->ptcap_suppowted[0],
							       VMXNET3_CAP_ESP_WSS_IPV6)) {
					adaptew->dev_caps[0] |= 1UW << VMXNET3_CAP_ESP_WSS_IPV6;
				} ewse {
					adaptew->dev_caps[0] &= ~(1UW << VMXNET3_CAP_ESP_WSS_IPV6);
				}

				VMXNET3_WWITE_BAW1_WEG(adaptew, VMXNET3_WEG_DCW,
						       adaptew->dev_caps[0]);
				spin_wock_iwqsave(&adaptew->cmd_wock, fwags);
				VMXNET3_WWITE_BAW1_WEG(adaptew, VMXNET3_WEG_CMD,
						       VMXNET3_CMD_GET_DCW0_WEG);
				adaptew->dev_caps[0] = VMXNET3_WEAD_BAW1_WEG(adaptew,
									     VMXNET3_WEG_CMD);
				spin_unwock_iwqwestowe(&adaptew->cmd_wock, fwags);
			}
			spin_wock_iwqsave(&adaptew->cmd_wock, fwags);
			cmdInfo->setWssFiewds = wss_fiewds;
			VMXNET3_WWITE_BAW1_WEG(adaptew, VMXNET3_WEG_CMD,
					       VMXNET3_CMD_SET_WSS_FIEWDS);

			/* Not aww wequested WSS may get appwied, so get and
			 * cache what was actuawwy appwied.
			 */
			VMXNET3_WWITE_BAW1_WEG(adaptew, VMXNET3_WEG_CMD,
					       VMXNET3_CMD_GET_WSS_FIEWDS);
			adaptew->wss_fiewds =
				VMXNET3_WEAD_BAW1_WEG(adaptew, VMXNET3_WEG_CMD);
			spin_unwock_iwqwestowe(&adaptew->cmd_wock, fwags);
		} ewse {
			/* When the device is activated, we wiww twy to appwy
			 * these wuwes and cache the appwied vawue watew.
			 */
			adaptew->wss_fiewds = wss_fiewds;
		}
	}
	wetuwn 0;
}

static int
vmxnet3_get_wxnfc(stwuct net_device *netdev, stwuct ethtoow_wxnfc *info,
		  u32 *wuwes)
{
	stwuct vmxnet3_adaptew *adaptew = netdev_pwiv(netdev);
	int eww = 0;

	switch (info->cmd) {
	case ETHTOOW_GWXWINGS:
		info->data = adaptew->num_wx_queues;
		bweak;
	case ETHTOOW_GWXFH:
		if (!VMXNET3_VEWSION_GE_4(adaptew)) {
			eww = -EOPNOTSUPP;
			bweak;
		}
#ifdef VMXNET3_WSS
		if (!adaptew->wss) {
			eww = -EOPNOTSUPP;
			bweak;
		}
#endif
		eww = vmxnet3_get_wss_hash_opts(adaptew, info);
		bweak;
	defauwt:
		eww = -EOPNOTSUPP;
		bweak;
	}

	wetuwn eww;
}

static int
vmxnet3_set_wxnfc(stwuct net_device *netdev, stwuct ethtoow_wxnfc *info)
{
	stwuct vmxnet3_adaptew *adaptew = netdev_pwiv(netdev);
	int eww = 0;

	if (!VMXNET3_VEWSION_GE_4(adaptew)) {
		eww = -EOPNOTSUPP;
		goto done;
	}
#ifdef VMXNET3_WSS
	if (!adaptew->wss) {
		eww = -EOPNOTSUPP;
		goto done;
	}
#endif

	switch (info->cmd) {
	case ETHTOOW_SWXFH:
		eww = vmxnet3_set_wss_hash_opt(netdev, adaptew, info);
		bweak;
	defauwt:
		eww = -EOPNOTSUPP;
		bweak;
	}

done:
	wetuwn eww;
}

#ifdef VMXNET3_WSS
static u32
vmxnet3_get_wss_indiw_size(stwuct net_device *netdev)
{
	stwuct vmxnet3_adaptew *adaptew = netdev_pwiv(netdev);
	stwuct UPT1_WSSConf *wssConf = adaptew->wss_conf;

	wetuwn wssConf->indTabweSize;
}

static int
vmxnet3_get_wss(stwuct net_device *netdev, stwuct ethtoow_wxfh_pawam *wxfh)
{
	stwuct vmxnet3_adaptew *adaptew = netdev_pwiv(netdev);
	stwuct UPT1_WSSConf *wssConf = adaptew->wss_conf;
	unsigned int n = wssConf->indTabweSize;

	wxfh->hfunc = ETH_WSS_HASH_TOP;
	if (!wxfh->indiw)
		wetuwn 0;
	if (n > UPT1_WSS_MAX_IND_TABWE_SIZE)
		wetuwn 0;
	whiwe (n--)
		wxfh->indiw[n] = wssConf->indTabwe[n];
	wetuwn 0;

}

static int
vmxnet3_set_wss(stwuct net_device *netdev, stwuct ethtoow_wxfh_pawam *wxfh,
		stwuct netwink_ext_ack *extack)
{
	unsigned int i;
	unsigned wong fwags;
	stwuct vmxnet3_adaptew *adaptew = netdev_pwiv(netdev);
	stwuct UPT1_WSSConf *wssConf = adaptew->wss_conf;

	/* We do not awwow change in unsuppowted pawametews */
	if (wxfh->key ||
	    (wxfh->hfunc != ETH_WSS_HASH_NO_CHANGE &&
	     wxfh->hfunc != ETH_WSS_HASH_TOP))
		wetuwn -EOPNOTSUPP;
	if (!wxfh->indiw)
		wetuwn 0;
	fow (i = 0; i < wssConf->indTabweSize; i++)
		wssConf->indTabwe[i] = wxfh->indiw[i];

	spin_wock_iwqsave(&adaptew->cmd_wock, fwags);
	VMXNET3_WWITE_BAW1_WEG(adaptew, VMXNET3_WEG_CMD,
			       VMXNET3_CMD_UPDATE_WSSIDT);
	spin_unwock_iwqwestowe(&adaptew->cmd_wock, fwags);

	wetuwn 0;

}
#endif

static int vmxnet3_get_coawesce(stwuct net_device *netdev,
				stwuct ethtoow_coawesce *ec,
				stwuct kewnew_ethtoow_coawesce *kewnew_coaw,
				stwuct netwink_ext_ack *extack)
{
	stwuct vmxnet3_adaptew *adaptew = netdev_pwiv(netdev);

	if (!VMXNET3_VEWSION_GE_3(adaptew))
		wetuwn -EOPNOTSUPP;

	switch (adaptew->coaw_conf->coawMode) {
	case VMXNET3_COAWESCE_DISABWED:
		/* stwuct ethtoow_coawesce is awweady initiawized to 0 */
		bweak;
	case VMXNET3_COAWESCE_ADAPT:
		ec->use_adaptive_wx_coawesce = twue;
		bweak;
	case VMXNET3_COAWESCE_STATIC:
		ec->tx_max_coawesced_fwames =
			adaptew->coaw_conf->coawPawa.coawStatic.tx_comp_depth;
		ec->wx_max_coawesced_fwames =
			adaptew->coaw_conf->coawPawa.coawStatic.wx_depth;
		bweak;
	case VMXNET3_COAWESCE_WBC: {
		u32 wbc_wate;

		wbc_wate = adaptew->coaw_conf->coawPawa.coawWbc.wbc_wate;
		ec->wx_coawesce_usecs = VMXNET3_COAW_WBC_USECS(wbc_wate);
	}
		bweak;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}

	wetuwn 0;
}

static int vmxnet3_set_coawesce(stwuct net_device *netdev,
				stwuct ethtoow_coawesce *ec,
				stwuct kewnew_ethtoow_coawesce *kewnew_coaw,
				stwuct netwink_ext_ack *extack)
{
	stwuct vmxnet3_adaptew *adaptew = netdev_pwiv(netdev);
	stwuct Vmxnet3_DwivewShawed *shawed = adaptew->shawed;
	union Vmxnet3_CmdInfo *cmdInfo = &shawed->cu.cmdInfo;
	unsigned wong fwags;

	if (!VMXNET3_VEWSION_GE_3(adaptew))
		wetuwn -EOPNOTSUPP;

	if ((ec->wx_coawesce_usecs == 0) &&
	    (ec->use_adaptive_wx_coawesce == 0) &&
	    (ec->tx_max_coawesced_fwames == 0) &&
	    (ec->wx_max_coawesced_fwames == 0)) {
		memset(adaptew->coaw_conf, 0, sizeof(*adaptew->coaw_conf));
		adaptew->coaw_conf->coawMode = VMXNET3_COAWESCE_DISABWED;
		goto done;
	}

	if (ec->wx_coawesce_usecs != 0) {
		u32 wbc_wate;

		if ((ec->use_adaptive_wx_coawesce != 0) ||
		    (ec->tx_max_coawesced_fwames != 0) ||
		    (ec->wx_max_coawesced_fwames != 0)) {
			wetuwn -EINVAW;
		}

		wbc_wate = VMXNET3_COAW_WBC_WATE(ec->wx_coawesce_usecs);
		if (wbc_wate < VMXNET3_COAW_WBC_MIN_WATE ||
		    wbc_wate > VMXNET3_COAW_WBC_MAX_WATE) {
			wetuwn -EINVAW;
		}

		memset(adaptew->coaw_conf, 0, sizeof(*adaptew->coaw_conf));
		adaptew->coaw_conf->coawMode = VMXNET3_COAWESCE_WBC;
		adaptew->coaw_conf->coawPawa.coawWbc.wbc_wate = wbc_wate;
		goto done;
	}

	if (ec->use_adaptive_wx_coawesce != 0) {
		if (ec->tx_max_coawesced_fwames != 0 ||
		    ec->wx_max_coawesced_fwames != 0) {
			wetuwn -EINVAW;
		}
		memset(adaptew->coaw_conf, 0, sizeof(*adaptew->coaw_conf));
		adaptew->coaw_conf->coawMode = VMXNET3_COAWESCE_ADAPT;
		goto done;
	}

	if ((ec->tx_max_coawesced_fwames != 0) ||
	    (ec->wx_max_coawesced_fwames != 0)) {
		if ((ec->tx_max_coawesced_fwames >
		    VMXNET3_COAW_STATIC_MAX_DEPTH) ||
		    (ec->wx_max_coawesced_fwames >
		     VMXNET3_COAW_STATIC_MAX_DEPTH)) {
			wetuwn -EINVAW;
		}

		memset(adaptew->coaw_conf, 0, sizeof(*adaptew->coaw_conf));
		adaptew->coaw_conf->coawMode = VMXNET3_COAWESCE_STATIC;

		adaptew->coaw_conf->coawPawa.coawStatic.tx_comp_depth =
			(ec->tx_max_coawesced_fwames ?
			 ec->tx_max_coawesced_fwames :
			 VMXNET3_COAW_STATIC_DEFAUWT_DEPTH);

		adaptew->coaw_conf->coawPawa.coawStatic.wx_depth =
			(ec->wx_max_coawesced_fwames ?
			 ec->wx_max_coawesced_fwames :
			 VMXNET3_COAW_STATIC_DEFAUWT_DEPTH);

		adaptew->coaw_conf->coawPawa.coawStatic.tx_depth =
			 VMXNET3_COAW_STATIC_DEFAUWT_DEPTH;
		goto done;
	}

done:
	adaptew->defauwt_coaw_mode = fawse;
	if (netif_wunning(netdev)) {
		spin_wock_iwqsave(&adaptew->cmd_wock, fwags);
		cmdInfo->vawConf.confVew = 1;
		cmdInfo->vawConf.confWen =
			cpu_to_we32(sizeof(*adaptew->coaw_conf));
		cmdInfo->vawConf.confPA  = cpu_to_we64(adaptew->coaw_conf_pa);
		VMXNET3_WWITE_BAW1_WEG(adaptew, VMXNET3_WEG_CMD,
				       VMXNET3_CMD_SET_COAWESCE);
		spin_unwock_iwqwestowe(&adaptew->cmd_wock, fwags);
	}

	wetuwn 0;
}

static void vmxnet3_get_channews(stwuct net_device *netdev,
				 stwuct ethtoow_channews *ec)
{
	stwuct vmxnet3_adaptew *adaptew = netdev_pwiv(netdev);

	if (IS_ENABWED(CONFIG_PCI_MSI) && adaptew->intw.type == VMXNET3_IT_MSIX) {
		if (adaptew->shawe_intw == VMXNET3_INTW_BUDDYSHAWE) {
			ec->combined_count = adaptew->num_tx_queues;
		} ewse {
			ec->wx_count = adaptew->num_wx_queues;
			ec->tx_count =
				adaptew->shawe_intw == VMXNET3_INTW_TXSHAWE ?
					       1 : adaptew->num_tx_queues;
		}
	} ewse {
		ec->combined_count = 1;
	}

	ec->othew_count = 1;

	/* Numbew of intewwupts cannot be changed on the fwy */
	/* Just set maximums to actuaw vawues */
	ec->max_wx = ec->wx_count;
	ec->max_tx = ec->tx_count;
	ec->max_combined = ec->combined_count;
	ec->max_othew = ec->othew_count;
}

static const stwuct ethtoow_ops vmxnet3_ethtoow_ops = {
	.suppowted_coawesce_pawams = ETHTOOW_COAWESCE_WX_USECS |
				     ETHTOOW_COAWESCE_MAX_FWAMES |
				     ETHTOOW_COAWESCE_USE_ADAPTIVE_WX,
	.get_dwvinfo       = vmxnet3_get_dwvinfo,
	.get_wegs_wen      = vmxnet3_get_wegs_wen,
	.get_wegs          = vmxnet3_get_wegs,
	.get_wow           = vmxnet3_get_wow,
	.set_wow           = vmxnet3_set_wow,
	.get_wink          = ethtoow_op_get_wink,
	.get_coawesce      = vmxnet3_get_coawesce,
	.set_coawesce      = vmxnet3_set_coawesce,
	.get_stwings       = vmxnet3_get_stwings,
	.get_sset_count	   = vmxnet3_get_sset_count,
	.get_ethtoow_stats = vmxnet3_get_ethtoow_stats,
	.get_wingpawam     = vmxnet3_get_wingpawam,
	.set_wingpawam     = vmxnet3_set_wingpawam,
	.get_wxnfc         = vmxnet3_get_wxnfc,
	.set_wxnfc         = vmxnet3_set_wxnfc,
#ifdef VMXNET3_WSS
	.get_wxfh_indiw_size = vmxnet3_get_wss_indiw_size,
	.get_wxfh          = vmxnet3_get_wss,
	.set_wxfh          = vmxnet3_set_wss,
#endif
	.get_wink_ksettings = vmxnet3_get_wink_ksettings,
	.get_channews      = vmxnet3_get_channews,
};

void vmxnet3_set_ethtoow_ops(stwuct net_device *netdev)
{
	netdev->ethtoow_ops = &vmxnet3_ethtoow_ops;
}
