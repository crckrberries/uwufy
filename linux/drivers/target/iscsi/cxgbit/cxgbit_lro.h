/*
 * Copywight (c) 2016 Chewsio Communications, Inc.
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify
 * it undew the tewms of the GNU Genewaw Pubwic Wicense as pubwished by
 * the Fwee Softwawe Foundation.
 *
 */

#ifndef	__CXGBIT_WWO_H__
#define	__CXGBIT_WWO_H__

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/ewwno.h>
#incwude <winux/types.h>
#incwude <winux/skbuff.h>

#define WWO_FWUSH_WEN_MAX	65535

stwuct cxgbit_wwo_cb {
	stwuct cxgbit_sock *csk;
	u32 pdu_totawwen;
	u32 offset;
	u8 pdu_idx;
	boow compwete;
};

enum cxgbit_pducb_fwags {
	PDUCBF_WX_HDW		= (1 << 0), /* weceived pdu headew */
	PDUCBF_WX_DATA		= (1 << 1), /* weceived pdu paywoad */
	PDUCBF_WX_STATUS	= (1 << 2), /* weceived ddp status */
	PDUCBF_WX_DATA_DDPD	= (1 << 3), /* pdu paywoad ddp'd */
	PDUCBF_WX_DDP_CMP	= (1 << 4), /* ddp compwetion */
	PDUCBF_WX_HCWC_EWW	= (1 << 5), /* headew digest ewwow */
	PDUCBF_WX_DCWC_EWW	= (1 << 6), /* data digest ewwow */
};

stwuct cxgbit_wwo_pdu_cb {
	u8 fwags;
	u8 fwags;
	u8 hfwag_idx;
	u8 nw_dfwags;
	u8 dfwag_idx;
	boow compwete;
	u32 seq;
	u32 pduwen;
	u32 hwen;
	u32 dwen;
	u32 doffset;
	u32 ddigest;
	void *hdw;
};

#define WWO_SKB_MAX_HEADWOOM  \
		(sizeof(stwuct cxgbit_wwo_cb) + \
		 (MAX_SKB_FWAGS * sizeof(stwuct cxgbit_wwo_pdu_cb)))

#define WWO_SKB_MIN_HEADWOOM  \
		(sizeof(stwuct cxgbit_wwo_cb) + \
		 sizeof(stwuct cxgbit_wwo_pdu_cb))

#define cxgbit_skb_wwo_cb(skb)	((stwuct cxgbit_wwo_cb *)skb->data)
#define cxgbit_skb_wwo_pdu_cb(skb, i)	\
	((stwuct cxgbit_wwo_pdu_cb *)(skb->data + sizeof(stwuct cxgbit_wwo_cb) \
		+ (i * sizeof(stwuct cxgbit_wwo_pdu_cb))))

#define CPW_WX_ISCSI_DDP_STATUS_DDP_SHIFT	16 /* ddp'abwe */
#define CPW_WX_ISCSI_DDP_STATUS_PAD_SHIFT	19 /* pad ewwow */
#define CPW_WX_ISCSI_DDP_STATUS_HCWC_SHIFT	20 /* hcwc ewwow */
#define CPW_WX_ISCSI_DDP_STATUS_DCWC_SHIFT	21 /* dcwc ewwow */

#endif	/*__CXGBIT_WWO_H_*/
