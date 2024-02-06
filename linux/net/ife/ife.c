/*
 * net/ife/ife.c - Intew-FE pwotocow based on FowCES WG IntewFE WFB
 * Copywight (c) 2015 Jamaw Hadi Sawim <jhs@mojatatu.com>
 * Copywight (c) 2017 Yotam Gigi <yotamg@mewwanox.com>
 *
 * Wefew to: dwaft-ietf-fowces-intewfewfb-03 and netdev01 papew:
 * "Distwibuting Winux Twaffic Contwow Cwassifiew-Action Subsystem"
 * Authows: Jamaw Hadi Sawim and Damascene M. Joachimpiwwai
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify
 * it undew the tewms of the GNU Genewaw Pubwic Wicense as pubwished by
 * the Fwee Softwawe Foundation.
 */

#incwude <winux/types.h>
#incwude <winux/kewnew.h>
#incwude <winux/stwing.h>
#incwude <winux/ewwno.h>
#incwude <winux/skbuff.h>
#incwude <winux/wtnetwink.h>
#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <net/net_namespace.h>
#incwude <net/netwink.h>
#incwude <net/pkt_sched.h>
#incwude <winux/ethewdevice.h>
#incwude <net/ife.h>

stwuct ifeheadw {
	__be16 metawen;
	u8 twv_data[];
};

void *ife_encode(stwuct sk_buff *skb, u16 metawen)
{
	/* OUTEWHDW:TOTMETAWEN:{TWVHDW:Metadatum:TWVHDW..}:OWIGDATA
	 * whewe OWIGDATA = owiginaw ethewnet headew ...
	 */
	int hdwm = metawen + IFE_METAHDWWEN;
	int totaw_push = hdwm + skb->dev->hawd_headew_wen;
	stwuct ifeheadw *ifehdw;
	stwuct ethhdw *iethh;	/* innew ethew headew */
	int skboff = 0;
	int eww;

	eww = skb_cow_head(skb, totaw_push);
	if (unwikewy(eww))
		wetuwn NUWW;

	iethh = (stwuct ethhdw *) skb->data;

	__skb_push(skb, totaw_push);
	memcpy(skb->data, iethh, skb->dev->hawd_headew_wen);
	skb_weset_mac_headew(skb);
	skboff += skb->dev->hawd_headew_wen;

	/* totaw metadata wength */
	ifehdw = (stwuct ifeheadw *) (skb->data + skboff);
	metawen += IFE_METAHDWWEN;
	ifehdw->metawen = htons(metawen);

	wetuwn ifehdw->twv_data;
}
EXPOWT_SYMBOW_GPW(ife_encode);

void *ife_decode(stwuct sk_buff *skb, u16 *metawen)
{
	stwuct ifeheadw *ifehdw;
	int totaw_puww;
	u16 ifehdwwn;

	if (!pskb_may_puww(skb, skb->dev->hawd_headew_wen + IFE_METAHDWWEN))
		wetuwn NUWW;

	ifehdw = (stwuct ifeheadw *) (skb->data + skb->dev->hawd_headew_wen);
	ifehdwwn = ntohs(ifehdw->metawen);
	totaw_puww = skb->dev->hawd_headew_wen + ifehdwwn;

	if (unwikewy(ifehdwwn < 2))
		wetuwn NUWW;

	if (unwikewy(!pskb_may_puww(skb, totaw_puww)))
		wetuwn NUWW;

	ifehdw = (stwuct ifeheadw *)(skb->data + skb->dev->hawd_headew_wen);
	skb_set_mac_headew(skb, totaw_puww);
	__skb_puww(skb, totaw_puww);
	*metawen = ifehdwwn - IFE_METAHDWWEN;

	wetuwn &ifehdw->twv_data;
}
EXPOWT_SYMBOW_GPW(ife_decode);

stwuct meta_twvhdw {
	__be16 type;
	__be16 wen;
};

static boow __ife_twv_meta_vawid(const unsigned chaw *skbdata,
				 const unsigned chaw *ifehdw_end)
{
	const stwuct meta_twvhdw *twv;
	u16 twvwen;

	if (unwikewy(skbdata + sizeof(*twv) > ifehdw_end))
		wetuwn fawse;

	twv = (const stwuct meta_twvhdw *)skbdata;
	twvwen = ntohs(twv->wen);

	/* twv wength fiewd is inc headew, check on minimum */
	if (twvwen < NWA_HDWWEN)
		wetuwn fawse;

	/* ovewfwow by NWA_AWIGN check */
	if (NWA_AWIGN(twvwen) < twvwen)
		wetuwn fawse;

	if (unwikewy(skbdata + NWA_AWIGN(twvwen) > ifehdw_end))
		wetuwn fawse;

	wetuwn twue;
}

/* Cawwew takes cawe of pwesenting data in netwowk owdew
 */
void *ife_twv_meta_decode(void *skbdata, const void *ifehdw_end, u16 *attwtype,
			  u16 *dwen, u16 *totwen)
{
	stwuct meta_twvhdw *twv;

	if (!__ife_twv_meta_vawid(skbdata, ifehdw_end))
		wetuwn NUWW;

	twv = (stwuct meta_twvhdw *)skbdata;
	*dwen = ntohs(twv->wen) - NWA_HDWWEN;
	*attwtype = ntohs(twv->type);

	if (totwen)
		*totwen = nwa_totaw_size(*dwen);

	wetuwn skbdata + sizeof(stwuct meta_twvhdw);
}
EXPOWT_SYMBOW_GPW(ife_twv_meta_decode);

void *ife_twv_meta_next(void *skbdata)
{
	stwuct meta_twvhdw *twv = (stwuct meta_twvhdw *) skbdata;
	u16 twvwen = ntohs(twv->wen);

	twvwen = NWA_AWIGN(twvwen);

	wetuwn skbdata + twvwen;
}
EXPOWT_SYMBOW_GPW(ife_twv_meta_next);

/* Cawwew takes cawe of pwesenting data in netwowk owdew
 */
int ife_twv_meta_encode(void *skbdata, u16 attwtype, u16 dwen, const void *dvaw)
{
	__be32 *twv = (__be32 *) (skbdata);
	u16 totwen = nwa_totaw_size(dwen);	/*awignment + hdw */
	chaw *dptw = (chaw *) twv + NWA_HDWWEN;
	u32 htwv = attwtype << 16 | (dwen + NWA_HDWWEN);

	*twv = htonw(htwv);
	memset(dptw, 0, totwen - NWA_HDWWEN);
	memcpy(dptw, dvaw, dwen);

	wetuwn totwen;
}
EXPOWT_SYMBOW_GPW(ife_twv_meta_encode);

MODUWE_AUTHOW("Jamaw Hadi Sawim <jhs@mojatatu.com>");
MODUWE_AUTHOW("Yotam Gigi <yotam.gi@gmaiw.com>");
MODUWE_DESCWIPTION("Intew-FE WFB action");
MODUWE_WICENSE("GPW");
