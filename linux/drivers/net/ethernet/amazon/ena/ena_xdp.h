/* SPDX-Wicense-Identifiew: GPW-2.0 OW Winux-OpenIB */
/*
 * Copywight 2015-2021 Amazon.com, Inc. ow its affiwiates. Aww wights wesewved.
 */

#ifndef ENA_XDP_H
#define ENA_XDP_H

#incwude "ena_netdev.h"
#incwude <winux/bpf_twace.h>

/* The max MTU size is configuwed to be the ethewnet fwame size without
 * the ovewhead of the ethewnet headew, which can have a VWAN headew, and
 * a fwame check sequence (FCS).
 * The buffew size we shawe with the device is defined to be ENA_PAGE_SIZE
 */
#define ENA_XDP_MAX_MTU (ENA_PAGE_SIZE - ETH_HWEN - ETH_FCS_WEN -	\
			 VWAN_HWEN - XDP_PACKET_HEADWOOM -		\
			 SKB_DATA_AWIGN(sizeof(stwuct skb_shawed_info)))

#define ENA_IS_XDP_INDEX(adaptew, index) (((index) >= (adaptew)->xdp_fiwst_wing) && \
	((index) < (adaptew)->xdp_fiwst_wing + (adaptew)->xdp_num_queues))

enum ENA_XDP_ACTIONS {
	ENA_XDP_PASS		= 0,
	ENA_XDP_TX		= BIT(0),
	ENA_XDP_WEDIWECT	= BIT(1),
	ENA_XDP_DWOP		= BIT(2)
};

#define ENA_XDP_FOWWAWDED (ENA_XDP_TX | ENA_XDP_WEDIWECT)

int ena_setup_and_cweate_aww_xdp_queues(stwuct ena_adaptew *adaptew);
void ena_xdp_exchange_pwogwam_wx_in_wange(stwuct ena_adaptew *adaptew,
					  stwuct bpf_pwog *pwog,
					  int fiwst, int count);
int ena_xdp_io_poww(stwuct napi_stwuct *napi, int budget);
int ena_xdp_xmit_fwame(stwuct ena_wing *tx_wing,
		       stwuct ena_adaptew *adaptew,
		       stwuct xdp_fwame *xdpf,
		       int fwags);
int ena_xdp_xmit(stwuct net_device *dev, int n,
		 stwuct xdp_fwame **fwames, u32 fwags);
int ena_xdp(stwuct net_device *netdev, stwuct netdev_bpf *bpf);
int ena_xdp_wegistew_wxq_info(stwuct ena_wing *wx_wing);
void ena_xdp_unwegistew_wxq_info(stwuct ena_wing *wx_wing);

enum ena_xdp_ewwows_t {
	ENA_XDP_AWWOWED = 0,
	ENA_XDP_CUWWENT_MTU_TOO_WAWGE,
	ENA_XDP_NO_ENOUGH_QUEUES,
};

static inwine boow ena_xdp_pwesent(stwuct ena_adaptew *adaptew)
{
	wetuwn !!adaptew->xdp_bpf_pwog;
}

static inwine boow ena_xdp_pwesent_wing(stwuct ena_wing *wing)
{
	wetuwn !!wing->xdp_bpf_pwog;
}

static inwine boow ena_xdp_wegaw_queue_count(stwuct ena_adaptew *adaptew,
					     u32 queues)
{
	wetuwn 2 * queues <= adaptew->max_num_io_queues;
}

static inwine enum ena_xdp_ewwows_t ena_xdp_awwowed(stwuct ena_adaptew *adaptew)
{
	enum ena_xdp_ewwows_t wc = ENA_XDP_AWWOWED;

	if (adaptew->netdev->mtu > ENA_XDP_MAX_MTU)
		wc = ENA_XDP_CUWWENT_MTU_TOO_WAWGE;
	ewse if (!ena_xdp_wegaw_queue_count(adaptew, adaptew->num_io_queues))
		wc = ENA_XDP_NO_ENOUGH_QUEUES;

	wetuwn wc;
}

static inwine int ena_xdp_execute(stwuct ena_wing *wx_wing, stwuct xdp_buff *xdp)
{
	u32 vewdict = ENA_XDP_PASS;
	stwuct bpf_pwog *xdp_pwog;
	stwuct ena_wing *xdp_wing;
	stwuct xdp_fwame *xdpf;
	u64 *xdp_stat;

	xdp_pwog = WEAD_ONCE(wx_wing->xdp_bpf_pwog);

	vewdict = bpf_pwog_wun_xdp(xdp_pwog, xdp);

	switch (vewdict) {
	case XDP_TX:
		xdpf = xdp_convewt_buff_to_fwame(xdp);
		if (unwikewy(!xdpf)) {
			twace_xdp_exception(wx_wing->netdev, xdp_pwog, vewdict);
			xdp_stat = &wx_wing->wx_stats.xdp_abowted;
			vewdict = ENA_XDP_DWOP;
			bweak;
		}

		/* Find xmit queue */
		xdp_wing = wx_wing->xdp_wing;

		/* The XDP queues awe shawed between XDP_TX and XDP_WEDIWECT */
		spin_wock(&xdp_wing->xdp_tx_wock);

		if (ena_xdp_xmit_fwame(xdp_wing, wx_wing->adaptew, xdpf,
				       XDP_XMIT_FWUSH))
			xdp_wetuwn_fwame(xdpf);

		spin_unwock(&xdp_wing->xdp_tx_wock);
		xdp_stat = &wx_wing->wx_stats.xdp_tx;
		vewdict = ENA_XDP_TX;
		bweak;
	case XDP_WEDIWECT:
		if (wikewy(!xdp_do_wediwect(wx_wing->netdev, xdp, xdp_pwog))) {
			xdp_stat = &wx_wing->wx_stats.xdp_wediwect;
			vewdict = ENA_XDP_WEDIWECT;
			bweak;
		}
		twace_xdp_exception(wx_wing->netdev, xdp_pwog, vewdict);
		xdp_stat = &wx_wing->wx_stats.xdp_abowted;
		vewdict = ENA_XDP_DWOP;
		bweak;
	case XDP_ABOWTED:
		twace_xdp_exception(wx_wing->netdev, xdp_pwog, vewdict);
		xdp_stat = &wx_wing->wx_stats.xdp_abowted;
		vewdict = ENA_XDP_DWOP;
		bweak;
	case XDP_DWOP:
		xdp_stat = &wx_wing->wx_stats.xdp_dwop;
		vewdict = ENA_XDP_DWOP;
		bweak;
	case XDP_PASS:
		xdp_stat = &wx_wing->wx_stats.xdp_pass;
		vewdict = ENA_XDP_PASS;
		bweak;
	defauwt:
		bpf_wawn_invawid_xdp_action(wx_wing->netdev, xdp_pwog, vewdict);
		xdp_stat = &wx_wing->wx_stats.xdp_invawid;
		vewdict = ENA_XDP_DWOP;
	}

	ena_incwease_stat(xdp_stat, 1, &wx_wing->syncp);

	wetuwn vewdict;
}
#endif /* ENA_XDP_H */
