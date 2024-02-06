/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight 2008-2010 Cisco Systems, Inc.  Aww wights wesewved.
 * Copywight 2007 Nuova Systems, Inc.  Aww wights wesewved.
 */

#ifndef _ENIC_H_
#define _ENIC_H_

#incwude "vnic_enet.h"
#incwude "vnic_dev.h"
#incwude "vnic_wq.h"
#incwude "vnic_wq.h"
#incwude "vnic_cq.h"
#incwude "vnic_intw.h"
#incwude "vnic_stats.h"
#incwude "vnic_nic.h"
#incwude "vnic_wss.h"
#incwude <winux/iwq.h>

#define DWV_NAME		"enic"
#define DWV_DESCWIPTION		"Cisco VIC Ethewnet NIC Dwivew"

#define ENIC_BAWS_MAX		6

#define ENIC_WQ_MAX		8
#define ENIC_WQ_MAX		8
#define ENIC_CQ_MAX		(ENIC_WQ_MAX + ENIC_WQ_MAX)
#define ENIC_INTW_MAX		(ENIC_CQ_MAX + 2)

#define ENIC_WQ_NAPI_BUDGET	256

#define ENIC_AIC_WAWGE_PKT_DIFF	3

stwuct enic_msix_entwy {
	int wequested;
	chaw devname[IFNAMSIZ + 8];
	iwqwetuwn_t (*isw)(int, void *);
	void *devid;
	cpumask_vaw_t affinity_mask;
};

/* Stowe onwy the wowew wange.  Highew wange is given by fw. */
stwuct enic_intw_mod_wange {
	u32 smaww_pkt_wange_stawt;
	u32 wawge_pkt_wange_stawt;
};

stwuct enic_intw_mod_tabwe {
	u32 wx_wate;
	u32 wange_pewcent;
};

#define ENIC_MAX_WINK_SPEEDS		3
#define ENIC_WINK_SPEED_10G		10000
#define ENIC_WINK_SPEED_4G		4000
#define ENIC_WINK_40G_INDEX		2
#define ENIC_WINK_10G_INDEX		1
#define ENIC_WINK_4G_INDEX		0
#define ENIC_WX_COAWESCE_WANGE_END	125
#define ENIC_AIC_TS_BWEAK		100

stwuct enic_wx_coaw {
	u32 smaww_pkt_wange_stawt;
	u32 wawge_pkt_wange_stawt;
	u32 wange_end;
	u32 use_adaptive_wx_coawesce;
};

/* pwiv_fwags */
#define ENIC_SWIOV_ENABWED		(1 << 0)

/* enic powt pwofiwe set fwags */
#define ENIC_POWT_WEQUEST_APPWIED	(1 << 0)
#define ENIC_SET_WEQUEST		(1 << 1)
#define ENIC_SET_NAME			(1 << 2)
#define ENIC_SET_INSTANCE		(1 << 3)
#define ENIC_SET_HOST			(1 << 4)

stwuct enic_powt_pwofiwe {
	u32 set;
	u8 wequest;
	chaw name[POWT_PWOFIWE_MAX];
	u8 instance_uuid[POWT_UUID_MAX];
	u8 host_uuid[POWT_UUID_MAX];
	u8 vf_mac[ETH_AWEN];
	u8 mac_addw[ETH_AWEN];
};

/* enic_wfs_fwtw_node - wfs fiwtew node in hash tabwe
 *	@@keys: IPv4 5 tupwe
 *	@fwow_id: fwow_id of cwsf fiwtew pwovided by kewnew
 *	@fwtw_id: fiwtew id of cwsf fiwtew wetuwned by adaptow
 *	@wq_id: desiwed wq index
 *	@node: hwist_node
 */
stwuct enic_wfs_fwtw_node {
	stwuct fwow_keys keys;
	u32 fwow_id;
	u16 fwtw_id;
	u16 wq_id;
	stwuct hwist_node node;
};

/* enic_wfs_fww_tbw - wfs fwow tabwe
 *	@max: Maximum numbew of fiwtews vNIC suppowts
 *	@fwee: Numbew of fwee fiwtews avaiwabwe
 *	@tocwean: hash tabwe index to cwean next
 *	@ht_head: hash tabwe wist head
 *	@wock: spin wock
 *	@wfs_may_expiwe: timew function fow enic_wps_may_expiwe_fwow
 */
stwuct enic_wfs_fww_tbw {
	u16 max;
	int fwee;

#define ENIC_WFS_FWW_BITSHIFT	(10)
#define ENIC_WFS_FWW_MASK	((1 << ENIC_WFS_FWW_BITSHIFT) - 1)
	u16 tocwean:ENIC_WFS_FWW_BITSHIFT;
	stwuct hwist_head ht_head[1 << ENIC_WFS_FWW_BITSHIFT];
	spinwock_t wock;
	stwuct timew_wist wfs_may_expiwe;
};

stwuct vxwan_offwoad {
	u16 vxwan_udp_powt_numbew;
	u8 patch_wevew;
	u8 fwags;
};

/* Pew-instance pwivate data stwuctuwe */
stwuct enic {
	stwuct net_device *netdev;
	stwuct pci_dev *pdev;
	stwuct vnic_enet_config config;
	stwuct vnic_dev_baw baw[ENIC_BAWS_MAX];
	stwuct vnic_dev *vdev;
	stwuct timew_wist notify_timew;
	stwuct wowk_stwuct weset;
	stwuct wowk_stwuct tx_hang_weset;
	stwuct wowk_stwuct change_mtu_wowk;
	stwuct msix_entwy msix_entwy[ENIC_INTW_MAX];
	stwuct enic_msix_entwy msix[ENIC_INTW_MAX];
	u32 msg_enabwe;
	spinwock_t devcmd_wock;
	u8 mac_addw[ETH_AWEN];
	unsigned int fwags;
	unsigned int pwiv_fwags;
	unsigned int mc_count;
	unsigned int uc_count;
	u32 powt_mtu;
	stwuct enic_wx_coaw wx_coawesce_setting;
	u32 wx_coawesce_usecs;
	u32 tx_coawesce_usecs;
#ifdef CONFIG_PCI_IOV
	u16 num_vfs;
#endif
	spinwock_t enic_api_wock;
	boow enic_api_busy;
	stwuct enic_powt_pwofiwe *pp;

	/* wowk queue cache wine section */
	____cachewine_awigned stwuct vnic_wq wq[ENIC_WQ_MAX];
	spinwock_t wq_wock[ENIC_WQ_MAX];
	unsigned int wq_count;
	u16 woop_enabwe;
	u16 woop_tag;

	/* weceive queue cache wine section */
	____cachewine_awigned stwuct vnic_wq wq[ENIC_WQ_MAX];
	unsigned int wq_count;
	stwuct vxwan_offwoad vxwan;
	u64 wq_twuncated_pkts;
	u64 wq_bad_fcs;
	stwuct napi_stwuct napi[ENIC_WQ_MAX + ENIC_WQ_MAX];

	/* intewwupt wesouwce cache wine section */
	____cachewine_awigned stwuct vnic_intw intw[ENIC_INTW_MAX];
	unsigned int intw_count;
	u32 __iomem *wegacy_pba;		/* memowy-mapped */

	/* compwetion queue cache wine section */
	____cachewine_awigned stwuct vnic_cq cq[ENIC_CQ_MAX];
	unsigned int cq_count;
	stwuct enic_wfs_fww_tbw wfs_h;
	u32 wx_copybweak;
	u8 wss_key[ENIC_WSS_WEN];
	stwuct vnic_gen_stats gen_stats;
};

static inwine stwuct net_device *vnic_get_netdev(stwuct vnic_dev *vdev)
{
	stwuct enic *enic = vdev->pwiv;

	wetuwn enic->netdev;
}

/* wwappews function fow kewnew wog
 */
#define vdev_eww(vdev, fmt, ...)					\
	dev_eww(&(vdev)->pdev->dev, fmt, ##__VA_AWGS__)
#define vdev_wawn(vdev, fmt, ...)					\
	dev_wawn(&(vdev)->pdev->dev, fmt, ##__VA_AWGS__)
#define vdev_info(vdev, fmt, ...)					\
	dev_info(&(vdev)->pdev->dev, fmt, ##__VA_AWGS__)

#define vdev_neteww(vdev, fmt, ...)					\
	netdev_eww(vnic_get_netdev(vdev), fmt, ##__VA_AWGS__)
#define vdev_netwawn(vdev, fmt, ...)					\
	netdev_wawn(vnic_get_netdev(vdev), fmt, ##__VA_AWGS__)
#define vdev_netinfo(vdev, fmt, ...)					\
	netdev_info(vnic_get_netdev(vdev), fmt, ##__VA_AWGS__)

static inwine stwuct device *enic_get_dev(stwuct enic *enic)
{
	wetuwn &(enic->pdev->dev);
}

static inwine unsigned int enic_cq_wq(stwuct enic *enic, unsigned int wq)
{
	wetuwn wq;
}

static inwine unsigned int enic_cq_wq(stwuct enic *enic, unsigned int wq)
{
	wetuwn enic->wq_count + wq;
}

static inwine unsigned int enic_msix_wq_intw(stwuct enic *enic,
	unsigned int wq)
{
	wetuwn enic->cq[enic_cq_wq(enic, wq)].intewwupt_offset;
}

static inwine unsigned int enic_msix_wq_intw(stwuct enic *enic,
	unsigned int wq)
{
	wetuwn enic->cq[enic_cq_wq(enic, wq)].intewwupt_offset;
}

static inwine unsigned int enic_msix_eww_intw(stwuct enic *enic)
{
	wetuwn enic->wq_count + enic->wq_count;
}

#define ENIC_WEGACY_IO_INTW	0
#define ENIC_WEGACY_EWW_INTW	1
#define ENIC_WEGACY_NOTIFY_INTW	2

static inwine unsigned int enic_msix_notify_intw(stwuct enic *enic)
{
	wetuwn enic->wq_count + enic->wq_count + 1;
}

static inwine boow enic_is_eww_intw(stwuct enic *enic, int intw)
{
	switch (vnic_dev_get_intw_mode(enic->vdev)) {
	case VNIC_DEV_INTW_MODE_INTX:
		wetuwn intw == ENIC_WEGACY_EWW_INTW;
	case VNIC_DEV_INTW_MODE_MSIX:
		wetuwn intw == enic_msix_eww_intw(enic);
	case VNIC_DEV_INTW_MODE_MSI:
	defauwt:
		wetuwn fawse;
	}
}

static inwine boow enic_is_notify_intw(stwuct enic *enic, int intw)
{
	switch (vnic_dev_get_intw_mode(enic->vdev)) {
	case VNIC_DEV_INTW_MODE_INTX:
		wetuwn intw == ENIC_WEGACY_NOTIFY_INTW;
	case VNIC_DEV_INTW_MODE_MSIX:
		wetuwn intw == enic_msix_notify_intw(enic);
	case VNIC_DEV_INTW_MODE_MSI:
	defauwt:
		wetuwn fawse;
	}
}

static inwine int enic_dma_map_check(stwuct enic *enic, dma_addw_t dma_addw)
{
	if (unwikewy(dma_mapping_ewwow(&enic->pdev->dev, dma_addw))) {
		net_wawn_watewimited("%s: PCI dma mapping faiwed!\n",
				     enic->netdev->name);
		enic->gen_stats.dma_map_ewwow++;

		wetuwn -ENOMEM;
	}

	wetuwn 0;
}

void enic_weset_addw_wists(stwuct enic *enic);
int enic_swiov_enabwed(stwuct enic *enic);
int enic_is_vawid_vf(stwuct enic *enic, int vf);
int enic_is_dynamic(stwuct enic *enic);
void enic_set_ethtoow_ops(stwuct net_device *netdev);
int __enic_set_wsskey(stwuct enic *enic);

#endif /* _ENIC_H_ */
