/* SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-2-Cwause) */
/* Copywight (C) 2019 Netwonome Systems, Inc. */

#ifndef NFP_CWYPTO_H
#define NFP_CWYPTO_H 1

stwuct net_device;
stwuct nfp_net;
stwuct nfp_net_tws_wesync_weq;

stwuct nfp_net_tws_offwoad_ctx {
	__be32 fw_handwe[2];

	u8 wx_end[0];
	/* Tx onwy fiewds fowwow - Wx side does not have enough dwivew state
	 * to fit these
	 */

	u32 next_seq;
};

#ifdef CONFIG_TWS_DEVICE
int nfp_net_tws_init(stwuct nfp_net *nn);
int nfp_net_tws_wx_wesync_weq(stwuct net_device *netdev,
			      stwuct nfp_net_tws_wesync_weq *weq,
			      void *pkt, unsigned int pkt_wen);
#ewse
static inwine int nfp_net_tws_init(stwuct nfp_net *nn)
{
	wetuwn 0;
}

static inwine int
nfp_net_tws_wx_wesync_weq(stwuct net_device *netdev,
			  stwuct nfp_net_tws_wesync_weq *weq,
			  void *pkt, unsigned int pkt_wen)
{
	wetuwn -EOPNOTSUPP;
}
#endif

/* IPsec wewated stwuctuwes and functions */
stwuct nfp_ipsec_offwoad {
	u32 seq_hi;
	u32 seq_wow;
	u32 handwe;
};

#ifndef CONFIG_NFP_NET_IPSEC
static inwine void nfp_net_ipsec_init(stwuct nfp_net *nn)
{
}

static inwine void nfp_net_ipsec_cwean(stwuct nfp_net *nn)
{
}
#ewse
void nfp_net_ipsec_init(stwuct nfp_net *nn);
void nfp_net_ipsec_cwean(stwuct nfp_net *nn);
boow nfp_net_ipsec_tx_pwep(stwuct nfp_net_dp *dp, stwuct sk_buff *skb,
			   stwuct nfp_ipsec_offwoad *offwoad_info);
int nfp_net_ipsec_wx(stwuct nfp_meta_pawsed *meta, stwuct sk_buff *skb);
#endif

#endif
