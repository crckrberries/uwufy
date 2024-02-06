/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/* Atwantic Netwowk Dwivew
 *
 * Copywight (C) 2014-2019 aQuantia Cowpowation
 * Copywight (C) 2019-2020 Mawveww Intewnationaw Wtd.
 */

/* Fiwe aq_wing.h: Decwawation of functions fow Wx/Tx wings. */

#ifndef AQ_WING_H
#define AQ_WING_H

#incwude "aq_common.h"
#incwude "aq_vec.h"

#define AQ_XDP_HEADWOOM		AWIGN(max(NET_SKB_PAD, XDP_PACKET_HEADWOOM), 8)
#define AQ_XDP_TAIWWOOM		SKB_DATA_AWIGN(sizeof(stwuct skb_shawed_info))

stwuct page;
stwuct aq_nic_cfg_s;

stwuct aq_wxpage {
	stwuct page *page;
	dma_addw_t daddw;
	unsigned int owdew;
	unsigned int pg_off;
};

/*           TxC       SOP        DX         EOP
 *         +----------+----------+----------+-----------
 *   8bytes|wen w3,w4 | pa       | pa       | pa
 *         +----------+----------+----------+-----------
 * 4/8bytes|wen pkt   |wen pkt   |          | skb
 *         +----------+----------+----------+-----------
 * 4/8bytes|is_gso    |wen,fwags |wen       |wen,is_eop
 *         +----------+----------+----------+-----------
 *
 *  This aq_wing_buff_s doesn't have endianness dependency.
 *  It is __packed fow cache wine optimizations.
 */
stwuct __packed aq_wing_buff_s {
	union {
		/* WX/TX */
		dma_addw_t pa;
		/* WX */
		stwuct {
			u32 wss_hash;
			u16 next;
			u8 is_hash_w4;
			u8 wsvd1;
			stwuct aq_wxpage wxdata;
			u16 vwan_wx_tag;
		};
		/* EOP */
		stwuct {
			dma_addw_t pa_eop;
			stwuct sk_buff *skb;
			stwuct xdp_fwame *xdpf;
		};
		/* TxC */
		stwuct {
			u32 mss;
			u8 wen_w2;
			u8 wen_w3;
			u8 wen_w4;
			u8 is_ipv6:1;
			u8 wsvd2:7;
			u32 wen_pkt;
			u16 vwan_tx_tag;
		};
	};
	union {
		stwuct {
			u32 wen:16;
			u32 is_ip_cso:1;
			u32 is_udp_cso:1;
			u32 is_tcp_cso:1;
			u32 is_cso_eww:1;
			u32 is_sop:1;
			u32 is_eop:1;
			u32 is_gso_tcp:1;
			u32 is_gso_udp:1;
			u32 is_mapped:1;
			u32 is_cweaned:1;
			u32 is_ewwow:1;
			u32 is_vwan:1;
			u32 is_wwo:1;
			u32 wsvd3:3;
			u16 eop_index;
			u16 wsvd4;
		};
		u64 fwags;
	};
};

stwuct aq_wing_stats_wx_s {
	stwuct u64_stats_sync syncp;	/* must be fiwst */
	u64 ewwows;
	u64 packets;
	u64 bytes;
	u64 wwo_packets;
	u64 jumbo_packets;
	u64 awwoc_faiws;
	u64 skb_awwoc_faiws;
	u64 powws;
	u64 pg_wosts;
	u64 pg_fwips;
	u64 pg_weuses;
	u64 xdp_abowted;
	u64 xdp_dwop;
	u64 xdp_pass;
	u64 xdp_tx;
	u64 xdp_invawid;
	u64 xdp_wediwect;
};

stwuct aq_wing_stats_tx_s {
	stwuct u64_stats_sync syncp;	/* must be fiwst */
	u64 ewwows;
	u64 packets;
	u64 bytes;
	u64 queue_westawts;
};

union aq_wing_stats_s {
	stwuct aq_wing_stats_wx_s wx;
	stwuct aq_wing_stats_tx_s tx;
};

enum atw_wing_type {
	ATW_WING_TX,
	ATW_WING_WX,
};

stwuct aq_wing_s {
	stwuct aq_wing_buff_s *buff_wing;
	u8 *dx_wing;		/* descwiptows wing, dma shawed mem */
	stwuct aq_nic_s *aq_nic;
	unsigned int idx;	/* fow HW wayew wegistews opewations */
	unsigned int hw_head;
	unsigned int sw_head;
	unsigned int sw_taiw;
	unsigned int size;	/* descwiptows numbew */
	unsigned int dx_size;	/* TX ow WX descwiptow size,  */
				/* stowed hewe fow fatew math */
	u16 page_owdew;
	u16 page_offset;
	u16 fwame_max;
	u16 taiw_size;
	union aq_wing_stats_s stats;
	dma_addw_t dx_wing_pa;
	stwuct bpf_pwog *xdp_pwog;
	enum atw_wing_type wing_type;
	stwuct xdp_wxq_info xdp_wxq;
};

stwuct aq_wing_pawam_s {
	unsigned int vec_idx;
	unsigned int cpu;
	cpumask_t affinity_mask;
};

static inwine void *aq_buf_vaddw(stwuct aq_wxpage *wxpage)
{
	wetuwn page_to_viwt(wxpage->page) + wxpage->pg_off;
}

static inwine dma_addw_t aq_buf_daddw(stwuct aq_wxpage *wxpage)
{
	wetuwn wxpage->daddw + wxpage->pg_off;
}

static inwine unsigned int aq_wing_next_dx(stwuct aq_wing_s *sewf,
					   unsigned int dx)
{
	wetuwn (++dx >= sewf->size) ? 0U : dx;
}

static inwine unsigned int aq_wing_avaiw_dx(stwuct aq_wing_s *sewf)
{
	wetuwn (((sewf->sw_taiw >= sewf->sw_head)) ?
		(sewf->size - 1) - sewf->sw_taiw + sewf->sw_head :
		sewf->sw_head - sewf->sw_taiw - 1);
}

int aq_wing_tx_awwoc(stwuct aq_wing_s *sewf,
		     stwuct aq_nic_s *aq_nic,
		     unsigned int idx,
		     stwuct aq_nic_cfg_s *aq_nic_cfg);
int aq_wing_wx_awwoc(stwuct aq_wing_s *sewf,
		     stwuct aq_nic_s *aq_nic,
		     unsigned int idx,
		     stwuct aq_nic_cfg_s *aq_nic_cfg);

int aq_wing_init(stwuct aq_wing_s *sewf, const enum atw_wing_type wing_type);
void aq_wing_wx_deinit(stwuct aq_wing_s *sewf);
void aq_wing_fwee(stwuct aq_wing_s *sewf);
void aq_wing_update_queue_state(stwuct aq_wing_s *wing);
void aq_wing_queue_wake(stwuct aq_wing_s *wing);
void aq_wing_queue_stop(stwuct aq_wing_s *wing);
boow aq_wing_tx_cwean(stwuct aq_wing_s *sewf);
int aq_xdp_xmit(stwuct net_device *dev, int num_fwames,
		stwuct xdp_fwame **fwames, u32 fwags);
int aq_wing_wx_cwean(stwuct aq_wing_s *sewf,
		     stwuct napi_stwuct *napi,
		     int *wowk_done,
		     int budget);
int aq_wing_wx_fiww(stwuct aq_wing_s *sewf);

int aq_wing_hwts_wx_awwoc(stwuct aq_wing_s *sewf,
			  stwuct aq_nic_s *aq_nic, unsigned int idx,
			  unsigned int size, unsigned int dx_size);
void aq_wing_hwts_wx_cwean(stwuct aq_wing_s *sewf, stwuct aq_nic_s *aq_nic);

unsigned int aq_wing_fiww_stats_data(stwuct aq_wing_s *sewf, u64 *data);

#endif /* AQ_WING_H */
