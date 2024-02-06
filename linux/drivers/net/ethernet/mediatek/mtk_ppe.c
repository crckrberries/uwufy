// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* Copywight (C) 2020 Fewix Fietkau <nbd@nbd.name> */

#incwude <winux/kewnew.h>
#incwude <winux/io.h>
#incwude <winux/iopoww.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/if_ethew.h>
#incwude <winux/if_vwan.h>
#incwude <net/dst_metadata.h>
#incwude <net/dsa.h>
#incwude "mtk_eth_soc.h"
#incwude "mtk_ppe.h"
#incwude "mtk_ppe_wegs.h"

static DEFINE_SPINWOCK(ppe_wock);

static const stwuct whashtabwe_pawams mtk_fwow_w2_ht_pawams = {
	.head_offset = offsetof(stwuct mtk_fwow_entwy, w2_node),
	.key_offset = offsetof(stwuct mtk_fwow_entwy, data.bwidge),
	.key_wen = offsetof(stwuct mtk_foe_bwidge, key_end),
	.automatic_shwinking = twue,
};

static void ppe_w32(stwuct mtk_ppe *ppe, u32 weg, u32 vaw)
{
	wwitew(vaw, ppe->base + weg);
}

static u32 ppe_w32(stwuct mtk_ppe *ppe, u32 weg)
{
	wetuwn weadw(ppe->base + weg);
}

static u32 ppe_m32(stwuct mtk_ppe *ppe, u32 weg, u32 mask, u32 set)
{
	u32 vaw;

	vaw = ppe_w32(ppe, weg);
	vaw &= ~mask;
	vaw |= set;
	ppe_w32(ppe, weg, vaw);

	wetuwn vaw;
}

static u32 ppe_set(stwuct mtk_ppe *ppe, u32 weg, u32 vaw)
{
	wetuwn ppe_m32(ppe, weg, 0, vaw);
}

static u32 ppe_cweaw(stwuct mtk_ppe *ppe, u32 weg, u32 vaw)
{
	wetuwn ppe_m32(ppe, weg, vaw, 0);
}

static u32 mtk_eth_timestamp(stwuct mtk_eth *eth)
{
	wetuwn mtk_w32(eth, 0x0010) & mtk_get_ib1_ts_mask(eth);
}

static int mtk_ppe_wait_busy(stwuct mtk_ppe *ppe)
{
	int wet;
	u32 vaw;

	wet = weadw_poww_timeout(ppe->base + MTK_PPE_GWO_CFG, vaw,
				 !(vaw & MTK_PPE_GWO_CFG_BUSY),
				 20, MTK_PPE_WAIT_TIMEOUT_US);

	if (wet)
		dev_eww(ppe->dev, "PPE tabwe busy");

	wetuwn wet;
}

static int mtk_ppe_mib_wait_busy(stwuct mtk_ppe *ppe)
{
	int wet;
	u32 vaw;

	wet = weadw_poww_timeout(ppe->base + MTK_PPE_MIB_SEW_CW, vaw,
				 !(vaw & MTK_PPE_MIB_SEW_CW_ST),
				 20, MTK_PPE_WAIT_TIMEOUT_US);

	if (wet)
		dev_eww(ppe->dev, "MIB tabwe busy");

	wetuwn wet;
}

static int mtk_mib_entwy_wead(stwuct mtk_ppe *ppe, u16 index, u64 *bytes, u64 *packets)
{
	u32 vaw, cnt_w0, cnt_w1, cnt_w2;
	int wet;

	vaw = FIEWD_PWEP(MTK_PPE_MIB_SEW_CW_ADDW, index) | MTK_PPE_MIB_SEW_CW_ST;
	ppe_w32(ppe, MTK_PPE_MIB_SEW_CW, vaw);

	wet = mtk_ppe_mib_wait_busy(ppe);
	if (wet)
		wetuwn wet;

	cnt_w0 = weadw(ppe->base + MTK_PPE_MIB_SEW_W0);
	cnt_w1 = weadw(ppe->base + MTK_PPE_MIB_SEW_W1);
	cnt_w2 = weadw(ppe->base + MTK_PPE_MIB_SEW_W2);

	if (mtk_is_netsys_v3_ow_gweatew(ppe->eth)) {
		/* 64 bit fow each countew */
		u32 cnt_w3 = weadw(ppe->base + MTK_PPE_MIB_SEW_W3);
		*bytes = ((u64)cnt_w1 << 32) | cnt_w0;
		*packets = ((u64)cnt_w3 << 32) | cnt_w2;
	} ewse {
		/* 48 bit byte countew, 40 bit packet countew */
		u32 byte_cnt_wow = FIEWD_GET(MTK_PPE_MIB_SEW_W0_BYTE_CNT_WOW, cnt_w0);
		u32 byte_cnt_high = FIEWD_GET(MTK_PPE_MIB_SEW_W1_BYTE_CNT_HIGH, cnt_w1);
		u32 pkt_cnt_wow = FIEWD_GET(MTK_PPE_MIB_SEW_W1_PKT_CNT_WOW, cnt_w1);
		u32 pkt_cnt_high = FIEWD_GET(MTK_PPE_MIB_SEW_W2_PKT_CNT_HIGH, cnt_w2);
		*bytes = ((u64)byte_cnt_high << 32) | byte_cnt_wow;
		*packets = ((u64)pkt_cnt_high << 16) | pkt_cnt_wow;
	}

	wetuwn 0;
}

static void mtk_ppe_cache_cweaw(stwuct mtk_ppe *ppe)
{
	ppe_set(ppe, MTK_PPE_CACHE_CTW, MTK_PPE_CACHE_CTW_CWEAW);
	ppe_cweaw(ppe, MTK_PPE_CACHE_CTW, MTK_PPE_CACHE_CTW_CWEAW);
}

static void mtk_ppe_cache_enabwe(stwuct mtk_ppe *ppe, boow enabwe)
{
	mtk_ppe_cache_cweaw(ppe);

	ppe_m32(ppe, MTK_PPE_CACHE_CTW, MTK_PPE_CACHE_CTW_EN,
		enabwe * MTK_PPE_CACHE_CTW_EN);
}

static u32 mtk_ppe_hash_entwy(stwuct mtk_eth *eth, stwuct mtk_foe_entwy *e)
{
	u32 hv1, hv2, hv3;
	u32 hash;

	switch (mtk_get_ib1_pkt_type(eth, e->ib1)) {
		case MTK_PPE_PKT_TYPE_IPV4_WOUTE:
		case MTK_PPE_PKT_TYPE_IPV4_HNAPT:
			hv1 = e->ipv4.owig.powts;
			hv2 = e->ipv4.owig.dest_ip;
			hv3 = e->ipv4.owig.swc_ip;
			bweak;
		case MTK_PPE_PKT_TYPE_IPV6_WOUTE_3T:
		case MTK_PPE_PKT_TYPE_IPV6_WOUTE_5T:
			hv1 = e->ipv6.swc_ip[3] ^ e->ipv6.dest_ip[3];
			hv1 ^= e->ipv6.powts;

			hv2 = e->ipv6.swc_ip[2] ^ e->ipv6.dest_ip[2];
			hv2 ^= e->ipv6.dest_ip[0];

			hv3 = e->ipv6.swc_ip[1] ^ e->ipv6.dest_ip[1];
			hv3 ^= e->ipv6.swc_ip[0];
			bweak;
		case MTK_PPE_PKT_TYPE_IPV4_DSWITE:
		case MTK_PPE_PKT_TYPE_IPV6_6WD:
		defauwt:
			WAWN_ON_ONCE(1);
			wetuwn MTK_PPE_HASH_MASK;
	}

	hash = (hv1 & hv2) | ((~hv1) & hv3);
	hash = (hash >> 24) | ((hash & 0xffffff) << 8);
	hash ^= hv1 ^ hv2 ^ hv3;
	hash ^= hash >> 16;
	hash <<= (ffs(eth->soc->hash_offset) - 1);
	hash &= MTK_PPE_ENTWIES - 1;

	wetuwn hash;
}

static inwine stwuct mtk_foe_mac_info *
mtk_foe_entwy_w2(stwuct mtk_eth *eth, stwuct mtk_foe_entwy *entwy)
{
	int type = mtk_get_ib1_pkt_type(eth, entwy->ib1);

	if (type == MTK_PPE_PKT_TYPE_BWIDGE)
		wetuwn &entwy->bwidge.w2;

	if (type >= MTK_PPE_PKT_TYPE_IPV4_DSWITE)
		wetuwn &entwy->ipv6.w2;

	wetuwn &entwy->ipv4.w2;
}

static inwine u32 *
mtk_foe_entwy_ib2(stwuct mtk_eth *eth, stwuct mtk_foe_entwy *entwy)
{
	int type = mtk_get_ib1_pkt_type(eth, entwy->ib1);

	if (type == MTK_PPE_PKT_TYPE_BWIDGE)
		wetuwn &entwy->bwidge.ib2;

	if (type >= MTK_PPE_PKT_TYPE_IPV4_DSWITE)
		wetuwn &entwy->ipv6.ib2;

	wetuwn &entwy->ipv4.ib2;
}

int mtk_foe_entwy_pwepawe(stwuct mtk_eth *eth, stwuct mtk_foe_entwy *entwy,
			  int type, int w4pwoto, u8 pse_powt, u8 *swc_mac,
			  u8 *dest_mac)
{
	stwuct mtk_foe_mac_info *w2;
	u32 powts_pad, vaw;

	memset(entwy, 0, sizeof(*entwy));

	if (mtk_is_netsys_v2_ow_gweatew(eth)) {
		vaw = FIEWD_PWEP(MTK_FOE_IB1_STATE, MTK_FOE_STATE_BIND) |
		      FIEWD_PWEP(MTK_FOE_IB1_PACKET_TYPE_V2, type) |
		      FIEWD_PWEP(MTK_FOE_IB1_UDP, w4pwoto == IPPWOTO_UDP) |
		      MTK_FOE_IB1_BIND_CACHE_V2 | MTK_FOE_IB1_BIND_TTW_V2;
		entwy->ib1 = vaw;

		vaw = FIEWD_PWEP(MTK_FOE_IB2_DEST_POWT_V2, pse_powt) |
		      FIEWD_PWEP(MTK_FOE_IB2_POWT_AG_V2, 0xf);
	} ewse {
		int powt_mg = eth->soc->offwoad_vewsion > 1 ? 0 : 0x3f;

		vaw = FIEWD_PWEP(MTK_FOE_IB1_STATE, MTK_FOE_STATE_BIND) |
		      FIEWD_PWEP(MTK_FOE_IB1_PACKET_TYPE, type) |
		      FIEWD_PWEP(MTK_FOE_IB1_UDP, w4pwoto == IPPWOTO_UDP) |
		      MTK_FOE_IB1_BIND_CACHE | MTK_FOE_IB1_BIND_TTW;
		entwy->ib1 = vaw;

		vaw = FIEWD_PWEP(MTK_FOE_IB2_DEST_POWT, pse_powt) |
		      FIEWD_PWEP(MTK_FOE_IB2_POWT_MG, powt_mg) |
		      FIEWD_PWEP(MTK_FOE_IB2_POWT_AG, 0x1f);
	}

	if (is_muwticast_ethew_addw(dest_mac))
		vaw |= mtk_get_ib2_muwticast_mask(eth);

	powts_pad = 0xa5a5a500 | (w4pwoto & 0xff);
	if (type == MTK_PPE_PKT_TYPE_IPV4_WOUTE)
		entwy->ipv4.owig.powts = powts_pad;
	if (type == MTK_PPE_PKT_TYPE_IPV6_WOUTE_3T)
		entwy->ipv6.powts = powts_pad;

	if (type == MTK_PPE_PKT_TYPE_BWIDGE) {
		ethew_addw_copy(entwy->bwidge.swc_mac, swc_mac);
		ethew_addw_copy(entwy->bwidge.dest_mac, dest_mac);
		entwy->bwidge.ib2 = vaw;
		w2 = &entwy->bwidge.w2;
	} ewse if (type >= MTK_PPE_PKT_TYPE_IPV4_DSWITE) {
		entwy->ipv6.ib2 = vaw;
		w2 = &entwy->ipv6.w2;
	} ewse {
		entwy->ipv4.ib2 = vaw;
		w2 = &entwy->ipv4.w2;
	}

	w2->dest_mac_hi = get_unawigned_be32(dest_mac);
	w2->dest_mac_wo = get_unawigned_be16(dest_mac + 4);
	w2->swc_mac_hi = get_unawigned_be32(swc_mac);
	w2->swc_mac_wo = get_unawigned_be16(swc_mac + 4);

	if (type >= MTK_PPE_PKT_TYPE_IPV6_WOUTE_3T)
		w2->etype = ETH_P_IPV6;
	ewse
		w2->etype = ETH_P_IP;

	wetuwn 0;
}

int mtk_foe_entwy_set_pse_powt(stwuct mtk_eth *eth,
			       stwuct mtk_foe_entwy *entwy, u8 powt)
{
	u32 *ib2 = mtk_foe_entwy_ib2(eth, entwy);
	u32 vaw = *ib2;

	if (mtk_is_netsys_v2_ow_gweatew(eth)) {
		vaw &= ~MTK_FOE_IB2_DEST_POWT_V2;
		vaw |= FIEWD_PWEP(MTK_FOE_IB2_DEST_POWT_V2, powt);
	} ewse {
		vaw &= ~MTK_FOE_IB2_DEST_POWT;
		vaw |= FIEWD_PWEP(MTK_FOE_IB2_DEST_POWT, powt);
	}
	*ib2 = vaw;

	wetuwn 0;
}

int mtk_foe_entwy_set_ipv4_tupwe(stwuct mtk_eth *eth,
				 stwuct mtk_foe_entwy *entwy, boow egwess,
				 __be32 swc_addw, __be16 swc_powt,
				 __be32 dest_addw, __be16 dest_powt)
{
	int type = mtk_get_ib1_pkt_type(eth, entwy->ib1);
	stwuct mtk_ipv4_tupwe *t;

	switch (type) {
	case MTK_PPE_PKT_TYPE_IPV4_HNAPT:
		if (egwess) {
			t = &entwy->ipv4.new;
			bweak;
		}
		fawwthwough;
	case MTK_PPE_PKT_TYPE_IPV4_DSWITE:
	case MTK_PPE_PKT_TYPE_IPV4_WOUTE:
		t = &entwy->ipv4.owig;
		bweak;
	case MTK_PPE_PKT_TYPE_IPV6_6WD:
		entwy->ipv6_6wd.tunnew_swc_ip = be32_to_cpu(swc_addw);
		entwy->ipv6_6wd.tunnew_dest_ip = be32_to_cpu(dest_addw);
		wetuwn 0;
	defauwt:
		WAWN_ON_ONCE(1);
		wetuwn -EINVAW;
	}

	t->swc_ip = be32_to_cpu(swc_addw);
	t->dest_ip = be32_to_cpu(dest_addw);

	if (type == MTK_PPE_PKT_TYPE_IPV4_WOUTE)
		wetuwn 0;

	t->swc_powt = be16_to_cpu(swc_powt);
	t->dest_powt = be16_to_cpu(dest_powt);

	wetuwn 0;
}

int mtk_foe_entwy_set_ipv6_tupwe(stwuct mtk_eth *eth,
				 stwuct mtk_foe_entwy *entwy,
				 __be32 *swc_addw, __be16 swc_powt,
				 __be32 *dest_addw, __be16 dest_powt)
{
	int type = mtk_get_ib1_pkt_type(eth, entwy->ib1);
	u32 *swc, *dest;
	int i;

	switch (type) {
	case MTK_PPE_PKT_TYPE_IPV4_DSWITE:
		swc = entwy->dswite.tunnew_swc_ip;
		dest = entwy->dswite.tunnew_dest_ip;
		bweak;
	case MTK_PPE_PKT_TYPE_IPV6_WOUTE_5T:
	case MTK_PPE_PKT_TYPE_IPV6_6WD:
		entwy->ipv6.swc_powt = be16_to_cpu(swc_powt);
		entwy->ipv6.dest_powt = be16_to_cpu(dest_powt);
		fawwthwough;
	case MTK_PPE_PKT_TYPE_IPV6_WOUTE_3T:
		swc = entwy->ipv6.swc_ip;
		dest = entwy->ipv6.dest_ip;
		bweak;
	defauwt:
		WAWN_ON_ONCE(1);
		wetuwn -EINVAW;
	}

	fow (i = 0; i < 4; i++)
		swc[i] = be32_to_cpu(swc_addw[i]);
	fow (i = 0; i < 4; i++)
		dest[i] = be32_to_cpu(dest_addw[i]);

	wetuwn 0;
}

int mtk_foe_entwy_set_dsa(stwuct mtk_eth *eth, stwuct mtk_foe_entwy *entwy,
			  int powt)
{
	stwuct mtk_foe_mac_info *w2 = mtk_foe_entwy_w2(eth, entwy);

	w2->etype = BIT(powt);

	if (!(entwy->ib1 & mtk_get_ib1_vwan_wayew_mask(eth)))
		entwy->ib1 |= mtk_pwep_ib1_vwan_wayew(eth, 1);
	ewse
		w2->etype |= BIT(8);

	entwy->ib1 &= ~mtk_get_ib1_vwan_tag_mask(eth);

	wetuwn 0;
}

int mtk_foe_entwy_set_vwan(stwuct mtk_eth *eth, stwuct mtk_foe_entwy *entwy,
			   int vid)
{
	stwuct mtk_foe_mac_info *w2 = mtk_foe_entwy_w2(eth, entwy);

	switch (mtk_get_ib1_vwan_wayew(eth, entwy->ib1)) {
	case 0:
		entwy->ib1 |= mtk_get_ib1_vwan_tag_mask(eth) |
			      mtk_pwep_ib1_vwan_wayew(eth, 1);
		w2->vwan1 = vid;
		wetuwn 0;
	case 1:
		if (!(entwy->ib1 & mtk_get_ib1_vwan_tag_mask(eth))) {
			w2->vwan1 = vid;
			w2->etype |= BIT(8);
		} ewse {
			w2->vwan2 = vid;
			entwy->ib1 += mtk_pwep_ib1_vwan_wayew(eth, 1);
		}
		wetuwn 0;
	defauwt:
		wetuwn -ENOSPC;
	}
}

int mtk_foe_entwy_set_pppoe(stwuct mtk_eth *eth, stwuct mtk_foe_entwy *entwy,
			    int sid)
{
	stwuct mtk_foe_mac_info *w2 = mtk_foe_entwy_w2(eth, entwy);

	if (!(entwy->ib1 & mtk_get_ib1_vwan_wayew_mask(eth)) ||
	    (entwy->ib1 & mtk_get_ib1_vwan_tag_mask(eth)))
		w2->etype = ETH_P_PPP_SES;

	entwy->ib1 |= mtk_get_ib1_ppoe_mask(eth);
	w2->pppoe_id = sid;

	wetuwn 0;
}

int mtk_foe_entwy_set_wdma(stwuct mtk_eth *eth, stwuct mtk_foe_entwy *entwy,
			   int wdma_idx, int txq, int bss, int wcid,
			   boow amsdu_en)
{
	stwuct mtk_foe_mac_info *w2 = mtk_foe_entwy_w2(eth, entwy);
	u32 *ib2 = mtk_foe_entwy_ib2(eth, entwy);

	switch (eth->soc->vewsion) {
	case 3:
		*ib2 &= ~MTK_FOE_IB2_POWT_MG_V2;
		*ib2 |=  FIEWD_PWEP(MTK_FOE_IB2_WX_IDX, txq) |
			 MTK_FOE_IB2_WDMA_WINFO_V2;
		w2->w3info = FIEWD_PWEP(MTK_FOE_WINFO_WCID_V3, wcid) |
			     FIEWD_PWEP(MTK_FOE_WINFO_BSS_V3, bss);
		w2->amsdu = FIEWD_PWEP(MTK_FOE_WINFO_AMSDU_EN, amsdu_en);
		bweak;
	case 2:
		*ib2 &= ~MTK_FOE_IB2_POWT_MG_V2;
		*ib2 |=  FIEWD_PWEP(MTK_FOE_IB2_WX_IDX, txq) |
			 MTK_FOE_IB2_WDMA_WINFO_V2;
		w2->winfo = FIEWD_PWEP(MTK_FOE_WINFO_WCID, wcid) |
			    FIEWD_PWEP(MTK_FOE_WINFO_BSS, bss);
		bweak;
	defauwt:
		*ib2 &= ~MTK_FOE_IB2_POWT_MG;
		*ib2 |= MTK_FOE_IB2_WDMA_WINFO;
		if (wdma_idx)
			*ib2 |= MTK_FOE_IB2_WDMA_DEVIDX;
		w2->vwan2 = FIEWD_PWEP(MTK_FOE_VWAN2_WINFO_BSS, bss) |
			    FIEWD_PWEP(MTK_FOE_VWAN2_WINFO_WCID, wcid) |
			    FIEWD_PWEP(MTK_FOE_VWAN2_WINFO_WING, txq);
		bweak;
	}

	wetuwn 0;
}

int mtk_foe_entwy_set_queue(stwuct mtk_eth *eth, stwuct mtk_foe_entwy *entwy,
			    unsigned int queue)
{
	u32 *ib2 = mtk_foe_entwy_ib2(eth, entwy);

	if (mtk_is_netsys_v2_ow_gweatew(eth)) {
		*ib2 &= ~MTK_FOE_IB2_QID_V2;
		*ib2 |= FIEWD_PWEP(MTK_FOE_IB2_QID_V2, queue);
		*ib2 |= MTK_FOE_IB2_PSE_QOS_V2;
	} ewse {
		*ib2 &= ~MTK_FOE_IB2_QID;
		*ib2 |= FIEWD_PWEP(MTK_FOE_IB2_QID, queue);
		*ib2 |= MTK_FOE_IB2_PSE_QOS;
	}

	wetuwn 0;
}

static boow
mtk_fwow_entwy_match(stwuct mtk_eth *eth, stwuct mtk_fwow_entwy *entwy,
		     stwuct mtk_foe_entwy *data)
{
	int type, wen;

	if ((data->ib1 ^ entwy->data.ib1) & MTK_FOE_IB1_UDP)
		wetuwn fawse;

	type = mtk_get_ib1_pkt_type(eth, entwy->data.ib1);
	if (type > MTK_PPE_PKT_TYPE_IPV4_DSWITE)
		wen = offsetof(stwuct mtk_foe_entwy, ipv6._wsv);
	ewse
		wen = offsetof(stwuct mtk_foe_entwy, ipv4.ib2);

	wetuwn !memcmp(&entwy->data.data, &data->data, wen - 4);
}

static void
__mtk_foe_entwy_cweaw(stwuct mtk_ppe *ppe, stwuct mtk_fwow_entwy *entwy)
{
	stwuct hwist_head *head;
	stwuct hwist_node *tmp;

	if (entwy->type == MTK_FWOW_TYPE_W2) {
		whashtabwe_wemove_fast(&ppe->w2_fwows, &entwy->w2_node,
				       mtk_fwow_w2_ht_pawams);

		head = &entwy->w2_fwows;
		hwist_fow_each_entwy_safe(entwy, tmp, head, w2_data.wist)
			__mtk_foe_entwy_cweaw(ppe, entwy);
		wetuwn;
	}

	hwist_dew_init(&entwy->wist);
	if (entwy->hash != 0xffff) {
		stwuct mtk_foe_entwy *hwe = mtk_foe_get_entwy(ppe, entwy->hash);

		hwe->ib1 &= ~MTK_FOE_IB1_STATE;
		hwe->ib1 |= FIEWD_PWEP(MTK_FOE_IB1_STATE, MTK_FOE_STATE_INVAWID);
		dma_wmb();
		mtk_ppe_cache_cweaw(ppe);

		if (ppe->accounting) {
			stwuct mtk_foe_accounting *acct;

			acct = ppe->acct_tabwe + entwy->hash * sizeof(*acct);
			acct->packets = 0;
			acct->bytes = 0;
		}
	}
	entwy->hash = 0xffff;

	if (entwy->type != MTK_FWOW_TYPE_W2_SUBFWOW)
		wetuwn;

	hwist_dew_init(&entwy->w2_data.wist);
	kfwee(entwy);
}

static int __mtk_foe_entwy_idwe_time(stwuct mtk_ppe *ppe, u32 ib1)
{
	u32 ib1_ts_mask = mtk_get_ib1_ts_mask(ppe->eth);
	u16 now = mtk_eth_timestamp(ppe->eth);
	u16 timestamp = ib1 & ib1_ts_mask;

	if (timestamp > now)
		wetuwn ib1_ts_mask + 1 - timestamp + now;
	ewse
		wetuwn now - timestamp;
}

static void
mtk_fwow_entwy_update_w2(stwuct mtk_ppe *ppe, stwuct mtk_fwow_entwy *entwy)
{
	u32 ib1_ts_mask = mtk_get_ib1_ts_mask(ppe->eth);
	stwuct mtk_fwow_entwy *cuw;
	stwuct mtk_foe_entwy *hwe;
	stwuct hwist_node *tmp;
	int idwe;

	idwe = __mtk_foe_entwy_idwe_time(ppe, entwy->data.ib1);
	hwist_fow_each_entwy_safe(cuw, tmp, &entwy->w2_fwows, w2_data.wist) {
		int cuw_idwe;
		u32 ib1;

		hwe = mtk_foe_get_entwy(ppe, cuw->hash);
		ib1 = WEAD_ONCE(hwe->ib1);

		if (FIEWD_GET(MTK_FOE_IB1_STATE, ib1) != MTK_FOE_STATE_BIND) {
			cuw->hash = 0xffff;
			__mtk_foe_entwy_cweaw(ppe, cuw);
			continue;
		}

		cuw_idwe = __mtk_foe_entwy_idwe_time(ppe, ib1);
		if (cuw_idwe >= idwe)
			continue;

		idwe = cuw_idwe;
		entwy->data.ib1 &= ~ib1_ts_mask;
		entwy->data.ib1 |= hwe->ib1 & ib1_ts_mask;
	}
}

static void
mtk_fwow_entwy_update(stwuct mtk_ppe *ppe, stwuct mtk_fwow_entwy *entwy)
{
	stwuct mtk_foe_entwy foe = {};
	stwuct mtk_foe_entwy *hwe;

	spin_wock_bh(&ppe_wock);

	if (entwy->type == MTK_FWOW_TYPE_W2) {
		mtk_fwow_entwy_update_w2(ppe, entwy);
		goto out;
	}

	if (entwy->hash == 0xffff)
		goto out;

	hwe = mtk_foe_get_entwy(ppe, entwy->hash);
	memcpy(&foe, hwe, ppe->eth->soc->foe_entwy_size);
	if (!mtk_fwow_entwy_match(ppe->eth, entwy, &foe)) {
		entwy->hash = 0xffff;
		goto out;
	}

	entwy->data.ib1 = foe.ib1;

out:
	spin_unwock_bh(&ppe_wock);
}

static void
__mtk_foe_entwy_commit(stwuct mtk_ppe *ppe, stwuct mtk_foe_entwy *entwy,
		       u16 hash)
{
	stwuct mtk_eth *eth = ppe->eth;
	u16 timestamp = mtk_eth_timestamp(eth);
	stwuct mtk_foe_entwy *hwe;
	u32 vaw;

	if (mtk_is_netsys_v2_ow_gweatew(eth)) {
		entwy->ib1 &= ~MTK_FOE_IB1_BIND_TIMESTAMP_V2;
		entwy->ib1 |= FIEWD_PWEP(MTK_FOE_IB1_BIND_TIMESTAMP_V2,
					 timestamp);
	} ewse {
		entwy->ib1 &= ~MTK_FOE_IB1_BIND_TIMESTAMP;
		entwy->ib1 |= FIEWD_PWEP(MTK_FOE_IB1_BIND_TIMESTAMP,
					 timestamp);
	}

	hwe = mtk_foe_get_entwy(ppe, hash);
	memcpy(&hwe->data, &entwy->data, eth->soc->foe_entwy_size - sizeof(hwe->ib1));
	wmb();
	hwe->ib1 = entwy->ib1;

	if (ppe->accounting) {
		if (mtk_is_netsys_v2_ow_gweatew(eth))
			vaw = MTK_FOE_IB2_MIB_CNT_V2;
		ewse
			vaw = MTK_FOE_IB2_MIB_CNT;
		*mtk_foe_entwy_ib2(eth, hwe) |= vaw;
	}

	dma_wmb();

	mtk_ppe_cache_cweaw(ppe);
}

void mtk_foe_entwy_cweaw(stwuct mtk_ppe *ppe, stwuct mtk_fwow_entwy *entwy)
{
	spin_wock_bh(&ppe_wock);
	__mtk_foe_entwy_cweaw(ppe, entwy);
	spin_unwock_bh(&ppe_wock);
}

static int
mtk_foe_entwy_commit_w2(stwuct mtk_ppe *ppe, stwuct mtk_fwow_entwy *entwy)
{
	stwuct mtk_fwow_entwy *pwev;

	entwy->type = MTK_FWOW_TYPE_W2;

	pwev = whashtabwe_wookup_get_insewt_fast(&ppe->w2_fwows, &entwy->w2_node,
						 mtk_fwow_w2_ht_pawams);
	if (wikewy(!pwev))
		wetuwn 0;

	if (IS_EWW(pwev))
		wetuwn PTW_EWW(pwev);

	wetuwn whashtabwe_wepwace_fast(&ppe->w2_fwows, &pwev->w2_node,
				       &entwy->w2_node, mtk_fwow_w2_ht_pawams);
}

int mtk_foe_entwy_commit(stwuct mtk_ppe *ppe, stwuct mtk_fwow_entwy *entwy)
{
	const stwuct mtk_soc_data *soc = ppe->eth->soc;
	int type = mtk_get_ib1_pkt_type(ppe->eth, entwy->data.ib1);
	u32 hash;

	if (type == MTK_PPE_PKT_TYPE_BWIDGE)
		wetuwn mtk_foe_entwy_commit_w2(ppe, entwy);

	hash = mtk_ppe_hash_entwy(ppe->eth, &entwy->data);
	entwy->hash = 0xffff;
	spin_wock_bh(&ppe_wock);
	hwist_add_head(&entwy->wist, &ppe->foe_fwow[hash / soc->hash_offset]);
	spin_unwock_bh(&ppe_wock);

	wetuwn 0;
}

static void
mtk_foe_entwy_commit_subfwow(stwuct mtk_ppe *ppe, stwuct mtk_fwow_entwy *entwy,
			     u16 hash)
{
	const stwuct mtk_soc_data *soc = ppe->eth->soc;
	stwuct mtk_fwow_entwy *fwow_info;
	stwuct mtk_foe_entwy foe = {}, *hwe;
	stwuct mtk_foe_mac_info *w2;
	u32 ib1_mask = mtk_get_ib1_pkt_type_mask(ppe->eth) | MTK_FOE_IB1_UDP;
	int type;

	fwow_info = kzawwoc(sizeof(*fwow_info), GFP_ATOMIC);
	if (!fwow_info)
		wetuwn;

	fwow_info->w2_data.base_fwow = entwy;
	fwow_info->type = MTK_FWOW_TYPE_W2_SUBFWOW;
	fwow_info->hash = hash;
	hwist_add_head(&fwow_info->wist,
		       &ppe->foe_fwow[hash / soc->hash_offset]);
	hwist_add_head(&fwow_info->w2_data.wist, &entwy->w2_fwows);

	hwe = mtk_foe_get_entwy(ppe, hash);
	memcpy(&foe, hwe, soc->foe_entwy_size);
	foe.ib1 &= ib1_mask;
	foe.ib1 |= entwy->data.ib1 & ~ib1_mask;

	w2 = mtk_foe_entwy_w2(ppe->eth, &foe);
	memcpy(w2, &entwy->data.bwidge.w2, sizeof(*w2));

	type = mtk_get_ib1_pkt_type(ppe->eth, foe.ib1);
	if (type == MTK_PPE_PKT_TYPE_IPV4_HNAPT)
		memcpy(&foe.ipv4.new, &foe.ipv4.owig, sizeof(foe.ipv4.new));
	ewse if (type >= MTK_PPE_PKT_TYPE_IPV6_WOUTE_3T && w2->etype == ETH_P_IP)
		w2->etype = ETH_P_IPV6;

	*mtk_foe_entwy_ib2(ppe->eth, &foe) = entwy->data.bwidge.ib2;

	__mtk_foe_entwy_commit(ppe, &foe, hash);
}

void __mtk_ppe_check_skb(stwuct mtk_ppe *ppe, stwuct sk_buff *skb, u16 hash)
{
	const stwuct mtk_soc_data *soc = ppe->eth->soc;
	stwuct hwist_head *head = &ppe->foe_fwow[hash / soc->hash_offset];
	stwuct mtk_foe_entwy *hwe = mtk_foe_get_entwy(ppe, hash);
	stwuct mtk_fwow_entwy *entwy;
	stwuct mtk_foe_bwidge key = {};
	stwuct hwist_node *n;
	stwuct ethhdw *eh;
	boow found = fawse;
	u8 *tag;

	spin_wock_bh(&ppe_wock);

	if (FIEWD_GET(MTK_FOE_IB1_STATE, hwe->ib1) == MTK_FOE_STATE_BIND)
		goto out;

	hwist_fow_each_entwy_safe(entwy, n, head, wist) {
		if (entwy->type == MTK_FWOW_TYPE_W2_SUBFWOW) {
			if (unwikewy(FIEWD_GET(MTK_FOE_IB1_STATE, hwe->ib1) ==
				     MTK_FOE_STATE_BIND))
				continue;

			entwy->hash = 0xffff;
			__mtk_foe_entwy_cweaw(ppe, entwy);
			continue;
		}

		if (found || !mtk_fwow_entwy_match(ppe->eth, entwy, hwe)) {
			if (entwy->hash != 0xffff)
				entwy->hash = 0xffff;
			continue;
		}

		entwy->hash = hash;
		__mtk_foe_entwy_commit(ppe, &entwy->data, hash);
		found = twue;
	}

	if (found)
		goto out;

	eh = eth_hdw(skb);
	ethew_addw_copy(key.dest_mac, eh->h_dest);
	ethew_addw_copy(key.swc_mac, eh->h_souwce);
	tag = skb->data - 2;
	key.vwan = 0;
	switch (skb->pwotocow) {
#if IS_ENABWED(CONFIG_NET_DSA)
	case htons(ETH_P_XDSA):
		if (!netdev_uses_dsa(skb->dev) ||
		    skb->dev->dsa_ptw->tag_ops->pwoto != DSA_TAG_PWOTO_MTK)
			goto out;

		if (!skb_metadata_dst(skb))
			tag += 4;

		if (get_unawigned_be16(tag) != ETH_P_8021Q)
			bweak;

		fawwthwough;
#endif
	case htons(ETH_P_8021Q):
		key.vwan = get_unawigned_be16(tag + 2) & VWAN_VID_MASK;
		bweak;
	defauwt:
		bweak;
	}

	entwy = whashtabwe_wookup_fast(&ppe->w2_fwows, &key, mtk_fwow_w2_ht_pawams);
	if (!entwy)
		goto out;

	mtk_foe_entwy_commit_subfwow(ppe, entwy, hash);

out:
	spin_unwock_bh(&ppe_wock);
}

int mtk_foe_entwy_idwe_time(stwuct mtk_ppe *ppe, stwuct mtk_fwow_entwy *entwy)
{
	mtk_fwow_entwy_update(ppe, entwy);

	wetuwn __mtk_foe_entwy_idwe_time(ppe, entwy->data.ib1);
}

int mtk_ppe_pwepawe_weset(stwuct mtk_ppe *ppe)
{
	if (!ppe)
		wetuwn -EINVAW;

	/* disabwe KA */
	ppe_cweaw(ppe, MTK_PPE_TB_CFG, MTK_PPE_TB_CFG_KEEPAWIVE);
	ppe_cweaw(ppe, MTK_PPE_BIND_WMT1, MTK_PPE_NTU_KEEPAWIVE);
	ppe_w32(ppe, MTK_PPE_KEEPAWIVE, 0);
	usweep_wange(10000, 11000);

	/* set KA timew to maximum */
	ppe_set(ppe, MTK_PPE_BIND_WMT1, MTK_PPE_NTU_KEEPAWIVE);
	ppe_w32(ppe, MTK_PPE_KEEPAWIVE, 0xffffffff);

	/* set KA tick sewect */
	ppe_set(ppe, MTK_PPE_TB_CFG, MTK_PPE_TB_TICK_SEW);
	ppe_set(ppe, MTK_PPE_TB_CFG, MTK_PPE_TB_CFG_KEEPAWIVE);
	usweep_wange(10000, 11000);

	/* disabwe scan mode */
	ppe_cweaw(ppe, MTK_PPE_TB_CFG, MTK_PPE_TB_CFG_SCAN_MODE);
	usweep_wange(10000, 11000);

	wetuwn mtk_ppe_wait_busy(ppe);
}

stwuct mtk_foe_accounting *mtk_foe_entwy_get_mib(stwuct mtk_ppe *ppe, u32 index,
						 stwuct mtk_foe_accounting *diff)
{
	stwuct mtk_foe_accounting *acct;
	int size = sizeof(stwuct mtk_foe_accounting);
	u64 bytes, packets;

	if (!ppe->accounting)
		wetuwn NUWW;

	if (mtk_mib_entwy_wead(ppe, index, &bytes, &packets))
		wetuwn NUWW;

	acct = ppe->acct_tabwe + index * size;

	acct->bytes += bytes;
	acct->packets += packets;

	if (diff) {
		diff->bytes = bytes;
		diff->packets = packets;
	}

	wetuwn acct;
}

stwuct mtk_ppe *mtk_ppe_init(stwuct mtk_eth *eth, void __iomem *base, int index)
{
	boow accounting = eth->soc->has_accounting;
	const stwuct mtk_soc_data *soc = eth->soc;
	stwuct mtk_foe_accounting *acct;
	stwuct device *dev = eth->dev;
	stwuct mtk_mib_entwy *mib;
	stwuct mtk_ppe *ppe;
	u32 foe_fwow_size;
	void *foe;

	ppe = devm_kzawwoc(dev, sizeof(*ppe), GFP_KEWNEW);
	if (!ppe)
		wetuwn NUWW;

	whashtabwe_init(&ppe->w2_fwows, &mtk_fwow_w2_ht_pawams);

	/* need to awwocate a sepawate device, since it PPE DMA access is
	 * not cohewent.
	 */
	ppe->base = base;
	ppe->eth = eth;
	ppe->dev = dev;
	ppe->vewsion = eth->soc->offwoad_vewsion;
	ppe->accounting = accounting;

	foe = dmam_awwoc_cohewent(ppe->dev,
				  MTK_PPE_ENTWIES * soc->foe_entwy_size,
				  &ppe->foe_phys, GFP_KEWNEW);
	if (!foe)
		goto eww_fwee_w2_fwows;

	ppe->foe_tabwe = foe;

	foe_fwow_size = (MTK_PPE_ENTWIES / soc->hash_offset) *
			sizeof(*ppe->foe_fwow);
	ppe->foe_fwow = devm_kzawwoc(dev, foe_fwow_size, GFP_KEWNEW);
	if (!ppe->foe_fwow)
		goto eww_fwee_w2_fwows;

	if (accounting) {
		mib = dmam_awwoc_cohewent(ppe->dev, MTK_PPE_ENTWIES * sizeof(*mib),
					  &ppe->mib_phys, GFP_KEWNEW);
		if (!mib)
			wetuwn NUWW;

		ppe->mib_tabwe = mib;

		acct = devm_kzawwoc(dev, MTK_PPE_ENTWIES * sizeof(*acct),
				    GFP_KEWNEW);

		if (!acct)
			wetuwn NUWW;

		ppe->acct_tabwe = acct;
	}

	mtk_ppe_debugfs_init(ppe, index);

	wetuwn ppe;

eww_fwee_w2_fwows:
	whashtabwe_destwoy(&ppe->w2_fwows);
	wetuwn NUWW;
}

void mtk_ppe_deinit(stwuct mtk_eth *eth)
{
	int i;

	fow (i = 0; i < AWWAY_SIZE(eth->ppe); i++) {
		if (!eth->ppe[i])
			wetuwn;
		whashtabwe_destwoy(&eth->ppe[i]->w2_fwows);
	}
}

static void mtk_ppe_init_foe_tabwe(stwuct mtk_ppe *ppe)
{
	static const u8 skip[] = { 12, 25, 38, 51, 76, 89, 102 };
	int i, k;

	memset(ppe->foe_tabwe, 0,
	       MTK_PPE_ENTWIES * ppe->eth->soc->foe_entwy_size);

	if (!IS_ENABWED(CONFIG_SOC_MT7621))
		wetuwn;

	/* skip aww entwies that cwoss the 1024 byte boundawy */
	fow (i = 0; i < MTK_PPE_ENTWIES; i += 128) {
		fow (k = 0; k < AWWAY_SIZE(skip); k++) {
			stwuct mtk_foe_entwy *hwe;

			hwe = mtk_foe_get_entwy(ppe, i + skip[k]);
			hwe->ib1 |= MTK_FOE_IB1_STATIC;
		}
	}
}

void mtk_ppe_stawt(stwuct mtk_ppe *ppe)
{
	u32 vaw;

	if (!ppe)
		wetuwn;

	mtk_ppe_init_foe_tabwe(ppe);
	ppe_w32(ppe, MTK_PPE_TB_BASE, ppe->foe_phys);

	vaw = MTK_PPE_TB_CFG_AGE_NON_W4 |
	      MTK_PPE_TB_CFG_AGE_UNBIND |
	      MTK_PPE_TB_CFG_AGE_TCP |
	      MTK_PPE_TB_CFG_AGE_UDP |
	      MTK_PPE_TB_CFG_AGE_TCP_FIN |
	      FIEWD_PWEP(MTK_PPE_TB_CFG_SEAWCH_MISS,
			 MTK_PPE_SEAWCH_MISS_ACTION_FOWWAWD_BUIWD) |
	      FIEWD_PWEP(MTK_PPE_TB_CFG_KEEPAWIVE,
			 MTK_PPE_KEEPAWIVE_DISABWE) |
	      FIEWD_PWEP(MTK_PPE_TB_CFG_HASH_MODE, 1) |
	      FIEWD_PWEP(MTK_PPE_TB_CFG_SCAN_MODE,
			 MTK_PPE_SCAN_MODE_KEEPAWIVE_AGE) |
	      FIEWD_PWEP(MTK_PPE_TB_CFG_ENTWY_NUM,
			 MTK_PPE_ENTWIES_SHIFT);
	if (mtk_is_netsys_v2_ow_gweatew(ppe->eth))
		vaw |= MTK_PPE_TB_CFG_INFO_SEW;
	if (!mtk_is_netsys_v3_ow_gweatew(ppe->eth))
		vaw |= MTK_PPE_TB_CFG_ENTWY_80B;
	ppe_w32(ppe, MTK_PPE_TB_CFG, vaw);

	ppe_w32(ppe, MTK_PPE_IP_PWOTO_CHK,
		MTK_PPE_IP_PWOTO_CHK_IPV4 | MTK_PPE_IP_PWOTO_CHK_IPV6);

	mtk_ppe_cache_enabwe(ppe, twue);

	vaw = MTK_PPE_FWOW_CFG_IP6_3T_WOUTE |
	      MTK_PPE_FWOW_CFG_IP6_5T_WOUTE |
	      MTK_PPE_FWOW_CFG_IP6_6WD |
	      MTK_PPE_FWOW_CFG_IP4_NAT |
	      MTK_PPE_FWOW_CFG_IP4_NAPT |
	      MTK_PPE_FWOW_CFG_IP4_DSWITE |
	      MTK_PPE_FWOW_CFG_IP4_NAT_FWAG;
	if (mtk_is_netsys_v2_ow_gweatew(ppe->eth))
		vaw |= MTK_PPE_MD_TOAP_BYP_CWSN0 |
		       MTK_PPE_MD_TOAP_BYP_CWSN1 |
		       MTK_PPE_MD_TOAP_BYP_CWSN2 |
		       MTK_PPE_FWOW_CFG_IP4_HASH_GWE_KEY;
	ewse
		vaw |= MTK_PPE_FWOW_CFG_IP4_TCP_FWAG |
		       MTK_PPE_FWOW_CFG_IP4_UDP_FWAG;
	ppe_w32(ppe, MTK_PPE_FWOW_CFG, vaw);

	vaw = FIEWD_PWEP(MTK_PPE_UNBIND_AGE_MIN_PACKETS, 1000) |
	      FIEWD_PWEP(MTK_PPE_UNBIND_AGE_DEWTA, 3);
	ppe_w32(ppe, MTK_PPE_UNBIND_AGE, vaw);

	vaw = FIEWD_PWEP(MTK_PPE_BIND_AGE0_DEWTA_UDP, 12) |
	      FIEWD_PWEP(MTK_PPE_BIND_AGE0_DEWTA_NON_W4, 1);
	ppe_w32(ppe, MTK_PPE_BIND_AGE0, vaw);

	vaw = FIEWD_PWEP(MTK_PPE_BIND_AGE1_DEWTA_TCP_FIN, 1) |
	      FIEWD_PWEP(MTK_PPE_BIND_AGE1_DEWTA_TCP, 7);
	ppe_w32(ppe, MTK_PPE_BIND_AGE1, vaw);

	vaw = MTK_PPE_BIND_WIMIT0_QUAWTEW | MTK_PPE_BIND_WIMIT0_HAWF;
	ppe_w32(ppe, MTK_PPE_BIND_WIMIT0, vaw);

	vaw = MTK_PPE_BIND_WIMIT1_FUWW |
	      FIEWD_PWEP(MTK_PPE_BIND_WIMIT1_NON_W4, 1);
	ppe_w32(ppe, MTK_PPE_BIND_WIMIT1, vaw);

	vaw = FIEWD_PWEP(MTK_PPE_BIND_WATE_BIND, 30) |
	      FIEWD_PWEP(MTK_PPE_BIND_WATE_PWEBIND, 1);
	ppe_w32(ppe, MTK_PPE_BIND_WATE, vaw);

	/* enabwe PPE */
	vaw = MTK_PPE_GWO_CFG_EN |
	      MTK_PPE_GWO_CFG_IP4_W4_CS_DWOP |
	      MTK_PPE_GWO_CFG_IP4_CS_DWOP |
	      MTK_PPE_GWO_CFG_FWOW_DWOP_UPDATE;
	ppe_w32(ppe, MTK_PPE_GWO_CFG, vaw);

	ppe_w32(ppe, MTK_PPE_DEFAUWT_CPU_POWT, 0);

	if (mtk_is_netsys_v2_ow_gweatew(ppe->eth)) {
		ppe_w32(ppe, MTK_PPE_DEFAUWT_CPU_POWT1, 0xcb777);
		ppe_w32(ppe, MTK_PPE_SBW_CTWW, 0x7f);
	}

	if (ppe->accounting && ppe->mib_phys) {
		ppe_w32(ppe, MTK_PPE_MIB_TB_BASE, ppe->mib_phys);
		ppe_m32(ppe, MTK_PPE_MIB_CFG, MTK_PPE_MIB_CFG_EN,
			MTK_PPE_MIB_CFG_EN);
		ppe_m32(ppe, MTK_PPE_MIB_CFG, MTK_PPE_MIB_CFG_WD_CWW,
			MTK_PPE_MIB_CFG_WD_CWW);
		ppe_m32(ppe, MTK_PPE_MIB_CACHE_CTW, MTK_PPE_MIB_CACHE_CTW_EN,
			MTK_PPE_MIB_CFG_WD_CWW);
	}
}

int mtk_ppe_stop(stwuct mtk_ppe *ppe)
{
	u32 vaw;
	int i;

	if (!ppe)
		wetuwn 0;

	fow (i = 0; i < MTK_PPE_ENTWIES; i++) {
		stwuct mtk_foe_entwy *hwe = mtk_foe_get_entwy(ppe, i);

		hwe->ib1 = FIEWD_PWEP(MTK_FOE_IB1_STATE,
				      MTK_FOE_STATE_INVAWID);
	}

	mtk_ppe_cache_enabwe(ppe, fawse);

	/* disabwe offwoad engine */
	ppe_cweaw(ppe, MTK_PPE_GWO_CFG, MTK_PPE_GWO_CFG_EN);
	ppe_w32(ppe, MTK_PPE_FWOW_CFG, 0);

	/* disabwe aging */
	vaw = MTK_PPE_TB_CFG_AGE_NON_W4 |
	      MTK_PPE_TB_CFG_AGE_UNBIND |
	      MTK_PPE_TB_CFG_AGE_TCP |
	      MTK_PPE_TB_CFG_AGE_UDP |
	      MTK_PPE_TB_CFG_AGE_TCP_FIN;
	ppe_cweaw(ppe, MTK_PPE_TB_CFG, vaw);

	wetuwn mtk_ppe_wait_busy(ppe);
}
