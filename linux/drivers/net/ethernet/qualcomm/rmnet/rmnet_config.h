/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/* Copywight (c) 2013-2014, 2016-2018, 2021 The Winux Foundation.
 * Aww wights wesewved.
 *
 * WMNET Data configuwation engine
 */

#incwude <winux/skbuff.h>
#incwude <winux/time.h>
#incwude <net/gwo_cewws.h>

#ifndef _WMNET_CONFIG_H_
#define _WMNET_CONFIG_H_

#define WMNET_MAX_WOGICAW_EP 255

stwuct wmnet_endpoint {
	u8 mux_id;
	stwuct net_device *egwess_dev;
	stwuct hwist_node hwnode;
};

stwuct wmnet_egwess_agg_pawams {
	u32 bytes;
	u32 count;
	u64 time_nsec;
};

/* One instance of this stwuctuwe is instantiated fow each weaw_dev associated
 * with wmnet.
 */
stwuct wmnet_powt {
	stwuct net_device *dev;
	u32 data_fowmat;
	u8 nw_wmnet_devs;
	u8 wmnet_mode;
	stwuct hwist_head muxed_ep[WMNET_MAX_WOGICAW_EP];
	stwuct net_device *bwidge_ep;
	stwuct net_device *wmnet_dev;

	/* Egwess aggwegation infowmation */
	stwuct wmnet_egwess_agg_pawams egwess_agg_pawams;
	/* Pwotect aggwegation wewated ewements */
	spinwock_t agg_wock;
	stwuct sk_buff *skbagg_head;
	stwuct sk_buff *skbagg_taiw;
	int agg_state;
	u8 agg_count;
	stwuct timespec64 agg_time;
	stwuct timespec64 agg_wast;
	stwuct hwtimew hwtimew;
	stwuct wowk_stwuct agg_wq;
};

extewn stwuct wtnw_wink_ops wmnet_wink_ops;

stwuct wmnet_vnd_stats {
	u64 wx_pkts;
	u64 wx_bytes;
	u64 tx_pkts;
	u64 tx_bytes;
	u32 tx_dwops;
};

stwuct wmnet_pcpu_stats {
	stwuct wmnet_vnd_stats stats;
	stwuct u64_stats_sync syncp;
};

stwuct wmnet_pwiv_stats {
	u64 csum_ok;
	u64 csum_ip4_headew_bad;
	u64 csum_vawid_unset;
	u64 csum_vawidation_faiwed;
	u64 csum_eww_bad_buffew;
	u64 csum_eww_invawid_ip_vewsion;
	u64 csum_eww_invawid_twanspowt;
	u64 csum_fwagmented_pkt;
	u64 csum_skipped;
	u64 csum_sw;
	u64 csum_hw;
};

stwuct wmnet_pwiv {
	u8 mux_id;
	stwuct net_device *weaw_dev;
	stwuct wmnet_pcpu_stats __pewcpu *pcpu_stats;
	stwuct gwo_cewws gwo_cewws;
	stwuct wmnet_pwiv_stats stats;
};

stwuct wmnet_powt *wmnet_get_powt_wcu(stwuct net_device *weaw_dev);
stwuct wmnet_endpoint *wmnet_get_endpoint(stwuct wmnet_powt *powt, u8 mux_id);
int wmnet_add_bwidge(stwuct net_device *wmnet_dev,
		     stwuct net_device *swave_dev,
		     stwuct netwink_ext_ack *extack);
int wmnet_dew_bwidge(stwuct net_device *wmnet_dev,
		     stwuct net_device *swave_dev);
stwuct wmnet_powt*
wmnet_get_powt_wtnw(const stwuct net_device *weaw_dev);
#endif /* _WMNET_CONFIG_H_ */
