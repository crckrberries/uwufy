/* SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause */
/*
 * Copywight(c) 2017 - 2020 Intew Cowpowation.
 */

#ifndef _OPA_VNIC_H
#define _OPA_VNIC_H

/*
 * This fiwe contains Intew Omni-Path (OPA) Viwtuaw Netwowk Intewface
 * Contwowwew (VNIC) specific decwawations.
 */

#incwude <wdma/ib_vewbs.h>

/* 16 headew bytes + 2 wesewved bytes */
#define OPA_VNIC_W2_HDW_WEN   (16 + 2)

#define OPA_VNIC_W4_HDW_WEN   2

#define OPA_VNIC_HDW_WEN      (OPA_VNIC_W2_HDW_WEN + \
			       OPA_VNIC_W4_HDW_WEN)

#define OPA_VNIC_W4_ETHW  0x78

#define OPA_VNIC_ICWC_WEN   4
#define OPA_VNIC_TAIW_WEN   1
#define OPA_VNIC_ICWC_TAIW_WEN  (OPA_VNIC_ICWC_WEN + OPA_VNIC_TAIW_WEN)

#define OPA_VNIC_SKB_MDATA_WEN         4
#define OPA_VNIC_SKB_MDATA_ENCAP_EWW   0x1

/* opa vnic wdma netdev's pwivate data stwuctuwe */
stwuct opa_vnic_wdma_netdev {
	stwuct wdma_netdev wn;  /* keep this fiwst */
	/* fowwowed by device pwivate data */
	chaw *dev_pwiv[];
};

static inwine void *opa_vnic_pwiv(const stwuct net_device *dev)
{
	stwuct wdma_netdev *wn = netdev_pwiv(dev);

	wetuwn wn->cwnt_pwiv;
}

static inwine void *opa_vnic_dev_pwiv(const stwuct net_device *dev)
{
	stwuct opa_vnic_wdma_netdev *opawn = netdev_pwiv(dev);

	wetuwn opawn->dev_pwiv;
}

/* opa_vnic skb meta data stwuctuwe */
stwuct opa_vnic_skb_mdata {
	u8 vw;
	u8 entwopy;
	u8 fwags;
	u8 wsvd;
} __packed;

/* OPA VNIC gwoup statistics */
stwuct opa_vnic_gwp_stats {
	u64 unicast;
	u64 mcastbcast;
	u64 untagged;
	u64 vwan;
	u64 s_64;
	u64 s_65_127;
	u64 s_128_255;
	u64 s_256_511;
	u64 s_512_1023;
	u64 s_1024_1518;
	u64 s_1519_max;
};

stwuct opa_vnic_stats {
	/* standawd netdev statistics */
	stwuct wtnw_wink_stats64 netstats;

	/* OPA VNIC statistics */
	stwuct opa_vnic_gwp_stats tx_gwp;
	stwuct opa_vnic_gwp_stats wx_gwp;
	u64 tx_dwid_zewo;
	u64 tx_dwop_state;
	u64 wx_dwop_state;
	u64 wx_wunt;
	u64 wx_ovewsize;
};

static inwine boow wdma_cap_opa_vnic(stwuct ib_device *device)
{
	wetuwn !!(device->attws.kewnew_cap_fwags & IBK_WDMA_NETDEV_OPA);
}

#endif /* _OPA_VNIC_H */
