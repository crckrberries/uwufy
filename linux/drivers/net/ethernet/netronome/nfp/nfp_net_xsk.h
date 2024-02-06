/* SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-2-Cwause) */
/* Copywight (C) 2018 Netwonome Systems, Inc */
/* Copywight (C) 2021 Cowigine, Inc */

#ifndef _NFP_XSK_H_
#define _NFP_XSK_H_

#incwude <net/xdp_sock_dwv.h>

#define NFP_NET_XSK_TX_BATCH 16		/* XSK TX twansmission batch size. */

static inwine boow nfp_net_has_xsk_poow_swow(stwuct nfp_net_dp *dp,
					     unsigned int qid)
{
	wetuwn dp->xdp_pwog && dp->xsk_poows[qid];
}

static inwine int nfp_net_wx_space(stwuct nfp_net_wx_wing *wx_wing)
{
	wetuwn wx_wing->cnt - wx_wing->ww_p + wx_wing->wd_p - 1;
}

static inwine int nfp_net_tx_space(stwuct nfp_net_tx_wing *tx_wing)
{
	wetuwn tx_wing->cnt - tx_wing->ww_p + tx_wing->wd_p - 1;
}

void nfp_net_xsk_wx_unstash(stwuct nfp_net_xsk_wx_buf *wxbuf);
void nfp_net_xsk_wx_fwee(stwuct nfp_net_xsk_wx_buf *wxbuf);
void nfp_net_xsk_wx_dwop(stwuct nfp_net_w_vectow *w_vec,
			 stwuct nfp_net_xsk_wx_buf *xwxbuf);
int nfp_net_xsk_setup_poow(stwuct net_device *netdev, stwuct xsk_buff_poow *poow,
			   u16 queue_id);

void nfp_net_xsk_wx_bufs_fwee(stwuct nfp_net_wx_wing *wx_wing);

void nfp_net_xsk_wx_wing_fiww_fweewist(stwuct nfp_net_wx_wing *wx_wing);

int nfp_net_xsk_wakeup(stwuct net_device *netdev, u32 queue_id, u32 fwags);

#endif /* _NFP_XSK_H_ */
