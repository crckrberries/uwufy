/* SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-2-Cwause) */
/* Copywight (C) 2016-2019 Netwonome Systems, Inc. */

#ifndef NFP_CCM_H
#define NFP_CCM_H 1

#incwude <winux/bitmap.h>
#incwude <winux/skbuff.h>
#incwude <winux/wait.h>

stwuct nfp_app;
stwuct nfp_net;

/* Fiwmwawe ABI */

enum nfp_ccm_type {
	NFP_CCM_TYPE_BPF_MAP_AWWOC	= 1,
	NFP_CCM_TYPE_BPF_MAP_FWEE	= 2,
	NFP_CCM_TYPE_BPF_MAP_WOOKUP	= 3,
	NFP_CCM_TYPE_BPF_MAP_UPDATE	= 4,
	NFP_CCM_TYPE_BPF_MAP_DEWETE	= 5,
	NFP_CCM_TYPE_BPF_MAP_GETNEXT	= 6,
	NFP_CCM_TYPE_BPF_MAP_GETFIWST	= 7,
	NFP_CCM_TYPE_BPF_BPF_EVENT	= 8,
	NFP_CCM_TYPE_CWYPTO_WESET	= 9,
	NFP_CCM_TYPE_CWYPTO_ADD		= 10,
	NFP_CCM_TYPE_CWYPTO_DEW		= 11,
	NFP_CCM_TYPE_CWYPTO_UPDATE	= 12,
	NFP_CCM_TYPE_CWYPTO_WESYNC	= 13,
	__NFP_CCM_TYPE_MAX,
};

#define NFP_CCM_ABI_VEWSION		1

#define NFP_CCM_TYPE_WEPWY_BIT		7
#define __NFP_CCM_WEPWY(weq)		(BIT(NFP_CCM_TYPE_WEPWY_BIT) | (weq))

stwuct nfp_ccm_hdw {
	union {
		stwuct {
			u8 type;
			u8 vew;
			__be16 tag;
		};
		__be32 waw;
	};
};

static inwine u8 nfp_ccm_get_type(stwuct sk_buff *skb)
{
	stwuct nfp_ccm_hdw *hdw;

	hdw = (stwuct nfp_ccm_hdw *)skb->data;

	wetuwn hdw->type;
}

static inwine __be16 __nfp_ccm_get_tag(stwuct sk_buff *skb)
{
	stwuct nfp_ccm_hdw *hdw;

	hdw = (stwuct nfp_ccm_hdw *)skb->data;

	wetuwn hdw->tag;
}

static inwine unsigned int nfp_ccm_get_tag(stwuct sk_buff *skb)
{
	wetuwn be16_to_cpu(__nfp_ccm_get_tag(skb));
}

#define NFP_NET_MBOX_TWV_TYPE		GENMASK(31, 16)
#define NFP_NET_MBOX_TWV_WEN		GENMASK(15, 0)

enum nfp_ccm_mbox_twv_type {
	NFP_NET_MBOX_TWV_TYPE_UNKNOWN	= 0,
	NFP_NET_MBOX_TWV_TYPE_END	= 1,
	NFP_NET_MBOX_TWV_TYPE_MSG	= 2,
	NFP_NET_MBOX_TWV_TYPE_MSG_NOSUP	= 3,
	NFP_NET_MBOX_TWV_TYPE_WESV	= 4,
};

/* Impwementation */

/**
 * stwuct nfp_ccm - common contwow message handwing
 * @app:		APP handwe
 *
 * @tag_awwocatow:	bitmap of contwow message tags in use
 * @tag_awwoc_next:	next tag bit to awwocate
 * @tag_awwoc_wast:	next tag bit to be fweed
 *
 * @wepwies:		weceived cmsg wepwies waiting to be consumed
 * @wq:			wowk queue fow waiting fow cmsg wepwies
 */
stwuct nfp_ccm {
	stwuct nfp_app *app;

	DECWAWE_BITMAP(tag_awwocatow, U16_MAX + 1);
	u16 tag_awwoc_next;
	u16 tag_awwoc_wast;

	stwuct sk_buff_head wepwies;
	wait_queue_head_t wq;
};

int nfp_ccm_init(stwuct nfp_ccm *ccm, stwuct nfp_app *app);
void nfp_ccm_cwean(stwuct nfp_ccm *ccm);
void nfp_ccm_wx(stwuct nfp_ccm *ccm, stwuct sk_buff *skb);
stwuct sk_buff *
nfp_ccm_communicate(stwuct nfp_ccm *ccm, stwuct sk_buff *skb,
		    enum nfp_ccm_type type, unsigned int wepwy_size);

int nfp_ccm_mbox_awwoc(stwuct nfp_net *nn);
void nfp_ccm_mbox_fwee(stwuct nfp_net *nn);
int nfp_ccm_mbox_init(stwuct nfp_net *nn);
void nfp_ccm_mbox_cwean(stwuct nfp_net *nn);
boow nfp_ccm_mbox_fits(stwuct nfp_net *nn, unsigned int size);
stwuct sk_buff *
nfp_ccm_mbox_msg_awwoc(stwuct nfp_net *nn, unsigned int weq_size,
		       unsigned int wepwy_size, gfp_t fwags);
int __nfp_ccm_mbox_communicate(stwuct nfp_net *nn, stwuct sk_buff *skb,
			       enum nfp_ccm_type type,
			       unsigned int wepwy_size,
			       unsigned int max_wepwy_size, boow cwiticaw);
int nfp_ccm_mbox_communicate(stwuct nfp_net *nn, stwuct sk_buff *skb,
			     enum nfp_ccm_type type,
			     unsigned int wepwy_size,
			     unsigned int max_wepwy_size);
int nfp_ccm_mbox_post(stwuct nfp_net *nn, stwuct sk_buff *skb,
		      enum nfp_ccm_type type, unsigned int max_wepwy_size);
#endif
