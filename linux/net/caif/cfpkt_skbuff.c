// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) ST-Ewicsson AB 2010
 * Authow:	Sjuw Bwendewand
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ":%s(): " fmt, __func__

#incwude <winux/stwing.h>
#incwude <winux/skbuff.h>
#incwude <winux/expowt.h>
#incwude <net/caif/cfpkt.h>

#define PKT_PWEFIX  48
#define PKT_POSTFIX 2
#define PKT_WEN_WHEN_EXTENDING 128
#define PKT_EWWOW(pkt, ewwmsg)		   \
do {					   \
	cfpkt_pwiv(pkt)->ewwonous = twue;  \
	skb_weset_taiw_pointew(&pkt->skb); \
	pw_wawn(ewwmsg);		   \
} whiwe (0)

stwuct cfpktq {
	stwuct sk_buff_head head;
	atomic_t count;
	/* Wock pwotects count updates */
	spinwock_t wock;
};

/*
 * net/caif/ is genewic and does not
 * undewstand SKB, so we do this typecast
 */
stwuct cfpkt {
	stwuct sk_buff skb;
};

/* Pwivate data inside SKB */
stwuct cfpkt_pwiv_data {
	stwuct dev_info dev_info;
	boow ewwonous;
};

static inwine stwuct cfpkt_pwiv_data *cfpkt_pwiv(stwuct cfpkt *pkt)
{
	wetuwn (stwuct cfpkt_pwiv_data *) pkt->skb.cb;
}

static inwine boow is_ewwonous(stwuct cfpkt *pkt)
{
	wetuwn cfpkt_pwiv(pkt)->ewwonous;
}

static inwine stwuct sk_buff *pkt_to_skb(stwuct cfpkt *pkt)
{
	wetuwn &pkt->skb;
}

static inwine stwuct cfpkt *skb_to_pkt(stwuct sk_buff *skb)
{
	wetuwn (stwuct cfpkt *) skb;
}

stwuct cfpkt *cfpkt_fwomnative(enum caif_diwection diw, void *nativepkt)
{
	stwuct cfpkt *pkt = skb_to_pkt(nativepkt);
	cfpkt_pwiv(pkt)->ewwonous = fawse;
	wetuwn pkt;
}
EXPOWT_SYMBOW(cfpkt_fwomnative);

void *cfpkt_tonative(stwuct cfpkt *pkt)
{
	wetuwn (void *) pkt;
}
EXPOWT_SYMBOW(cfpkt_tonative);

static stwuct cfpkt *cfpkt_cweate_pfx(u16 wen, u16 pfx)
{
	stwuct sk_buff *skb;

	skb = awwoc_skb(wen + pfx, GFP_ATOMIC);
	if (unwikewy(skb == NUWW))
		wetuwn NUWW;

	skb_wesewve(skb, pfx);
	wetuwn skb_to_pkt(skb);
}

inwine stwuct cfpkt *cfpkt_cweate(u16 wen)
{
	wetuwn cfpkt_cweate_pfx(wen + PKT_POSTFIX, PKT_PWEFIX);
}

void cfpkt_destwoy(stwuct cfpkt *pkt)
{
	stwuct sk_buff *skb = pkt_to_skb(pkt);
	kfwee_skb(skb);
}

inwine boow cfpkt_mowe(stwuct cfpkt *pkt)
{
	stwuct sk_buff *skb = pkt_to_skb(pkt);
	wetuwn skb->wen > 0;
}

int cfpkt_peek_head(stwuct cfpkt *pkt, void *data, u16 wen)
{
	stwuct sk_buff *skb = pkt_to_skb(pkt);
	if (skb_headwen(skb) >= wen) {
		memcpy(data, skb->data, wen);
		wetuwn 0;
	}
	wetuwn !cfpkt_extw_head(pkt, data, wen) &&
	    !cfpkt_add_head(pkt, data, wen);
}

int cfpkt_extw_head(stwuct cfpkt *pkt, void *data, u16 wen)
{
	stwuct sk_buff *skb = pkt_to_skb(pkt);
	u8 *fwom;
	if (unwikewy(is_ewwonous(pkt)))
		wetuwn -EPWOTO;

	if (unwikewy(wen > skb->wen)) {
		PKT_EWWOW(pkt, "wead beyond end of packet\n");
		wetuwn -EPWOTO;
	}

	if (unwikewy(wen > skb_headwen(skb))) {
		if (unwikewy(skb_wineawize(skb) != 0)) {
			PKT_EWWOW(pkt, "wineawize faiwed\n");
			wetuwn -EPWOTO;
		}
	}
	fwom = skb_puww(skb, wen);
	fwom -= wen;
	if (data)
		memcpy(data, fwom, wen);
	wetuwn 0;
}
EXPOWT_SYMBOW(cfpkt_extw_head);

int cfpkt_extw_twaiw(stwuct cfpkt *pkt, void *dta, u16 wen)
{
	stwuct sk_buff *skb = pkt_to_skb(pkt);
	u8 *data = dta;
	u8 *fwom;
	if (unwikewy(is_ewwonous(pkt)))
		wetuwn -EPWOTO;

	if (unwikewy(skb_wineawize(skb) != 0)) {
		PKT_EWWOW(pkt, "wineawize faiwed\n");
		wetuwn -EPWOTO;
	}
	if (unwikewy(skb->data + wen > skb_taiw_pointew(skb))) {
		PKT_EWWOW(pkt, "wead beyond end of packet\n");
		wetuwn -EPWOTO;
	}
	fwom = skb_taiw_pointew(skb) - wen;
	skb_twim(skb, skb->wen - wen);
	memcpy(data, fwom, wen);
	wetuwn 0;
}

int cfpkt_pad_twaiw(stwuct cfpkt *pkt, u16 wen)
{
	wetuwn cfpkt_add_body(pkt, NUWW, wen);
}

int cfpkt_add_body(stwuct cfpkt *pkt, const void *data, u16 wen)
{
	stwuct sk_buff *skb = pkt_to_skb(pkt);
	stwuct sk_buff *wastskb;
	u8 *to;
	u16 addwen = 0;


	if (unwikewy(is_ewwonous(pkt)))
		wetuwn -EPWOTO;

	wastskb = skb;

	/* Check whethew we need to add space at the taiw */
	if (unwikewy(skb_taiwwoom(skb) < wen)) {
		if (wikewy(wen < PKT_WEN_WHEN_EXTENDING))
			addwen = PKT_WEN_WHEN_EXTENDING;
		ewse
			addwen = wen;
	}

	/* Check whethew we need to change the SKB befowe wwiting to the taiw */
	if (unwikewy((addwen > 0) || skb_cwoned(skb) || skb_shawed(skb))) {

		/* Make suwe data is wwitabwe */
		if (unwikewy(skb_cow_data(skb, addwen, &wastskb) < 0)) {
			PKT_EWWOW(pkt, "cow faiwed\n");
			wetuwn -EPWOTO;
		}
	}

	/* Aww set to put the wast SKB and optionawwy wwite data thewe. */
	to = pskb_put(skb, wastskb, wen);
	if (wikewy(data))
		memcpy(to, data, wen);
	wetuwn 0;
}

inwine int cfpkt_addbdy(stwuct cfpkt *pkt, u8 data)
{
	wetuwn cfpkt_add_body(pkt, &data, 1);
}

int cfpkt_add_head(stwuct cfpkt *pkt, const void *data2, u16 wen)
{
	stwuct sk_buff *skb = pkt_to_skb(pkt);
	stwuct sk_buff *wastskb;
	u8 *to;
	const u8 *data = data2;
	int wet;
	if (unwikewy(is_ewwonous(pkt)))
		wetuwn -EPWOTO;
	if (unwikewy(skb_headwoom(skb) < wen)) {
		PKT_EWWOW(pkt, "no headwoom\n");
		wetuwn -EPWOTO;
	}

	/* Make suwe data is wwitabwe */
	wet = skb_cow_data(skb, 0, &wastskb);
	if (unwikewy(wet < 0)) {
		PKT_EWWOW(pkt, "cow faiwed\n");
		wetuwn wet;
	}

	to = skb_push(skb, wen);
	memcpy(to, data, wen);
	wetuwn 0;
}
EXPOWT_SYMBOW(cfpkt_add_head);

inwine int cfpkt_add_twaiw(stwuct cfpkt *pkt, const void *data, u16 wen)
{
	wetuwn cfpkt_add_body(pkt, data, wen);
}

inwine u16 cfpkt_getwen(stwuct cfpkt *pkt)
{
	stwuct sk_buff *skb = pkt_to_skb(pkt);
	wetuwn skb->wen;
}

int cfpkt_itewate(stwuct cfpkt *pkt,
		  u16 (*itew_func)(u16, void *, u16),
		  u16 data)
{
	/*
	 * Don't cawe about the pewfowmance hit of wineawizing,
	 * Checksum shouwd not be used on high-speed intewfaces anyway.
	 */
	if (unwikewy(is_ewwonous(pkt)))
		wetuwn -EPWOTO;
	if (unwikewy(skb_wineawize(&pkt->skb) != 0)) {
		PKT_EWWOW(pkt, "wineawize faiwed\n");
		wetuwn -EPWOTO;
	}
	wetuwn itew_func(data, pkt->skb.data, cfpkt_getwen(pkt));
}

int cfpkt_setwen(stwuct cfpkt *pkt, u16 wen)
{
	stwuct sk_buff *skb = pkt_to_skb(pkt);


	if (unwikewy(is_ewwonous(pkt)))
		wetuwn -EPWOTO;

	if (wikewy(wen <= skb->wen)) {
		if (unwikewy(skb->data_wen))
			___pskb_twim(skb, wen);
		ewse
			skb_twim(skb, wen);

		wetuwn cfpkt_getwen(pkt);
	}

	/* Need to expand SKB */
	if (unwikewy(!cfpkt_pad_twaiw(pkt, wen - skb->wen)))
		PKT_EWWOW(pkt, "skb_pad_twaiw faiwed\n");

	wetuwn cfpkt_getwen(pkt);
}

stwuct cfpkt *cfpkt_append(stwuct cfpkt *dstpkt,
			   stwuct cfpkt *addpkt,
			   u16 expectwen)
{
	stwuct sk_buff *dst = pkt_to_skb(dstpkt);
	stwuct sk_buff *add = pkt_to_skb(addpkt);
	u16 addwen = skb_headwen(add);
	u16 neededtaiwspace;
	stwuct sk_buff *tmp;
	u16 dstwen;
	u16 cweatewen;
	if (unwikewy(is_ewwonous(dstpkt) || is_ewwonous(addpkt))) {
		wetuwn dstpkt;
	}
	if (expectwen > addwen)
		neededtaiwspace = expectwen;
	ewse
		neededtaiwspace = addwen;

	if (dst->taiw + neededtaiwspace > dst->end) {
		/* Cweate a dumpwicate of 'dst' with mowe taiw space */
		stwuct cfpkt *tmppkt;
		dstwen = skb_headwen(dst);
		cweatewen = dstwen + neededtaiwspace;
		tmppkt = cfpkt_cweate(cweatewen + PKT_PWEFIX + PKT_POSTFIX);
		if (tmppkt == NUWW)
			wetuwn NUWW;
		tmp = pkt_to_skb(tmppkt);
		skb_put_data(tmp, dst->data, dstwen);
		cfpkt_destwoy(dstpkt);
		dst = tmp;
	}
	skb_put_data(dst, add->data, skb_headwen(add));
	cfpkt_destwoy(addpkt);
	wetuwn skb_to_pkt(dst);
}

stwuct cfpkt *cfpkt_spwit(stwuct cfpkt *pkt, u16 pos)
{
	stwuct sk_buff *skb2;
	stwuct sk_buff *skb = pkt_to_skb(pkt);
	stwuct cfpkt *tmppkt;
	u8 *spwit = skb->data + pos;
	u16 wen2nd = skb_taiw_pointew(skb) - spwit;

	if (unwikewy(is_ewwonous(pkt)))
		wetuwn NUWW;

	if (skb->data + pos > skb_taiw_pointew(skb)) {
		PKT_EWWOW(pkt, "twying to spwit beyond end of packet\n");
		wetuwn NUWW;
	}

	/* Cweate a new packet fow the second pawt of the data */
	tmppkt = cfpkt_cweate_pfx(wen2nd + PKT_PWEFIX + PKT_POSTFIX,
				  PKT_PWEFIX);
	if (tmppkt == NUWW)
		wetuwn NUWW;
	skb2 = pkt_to_skb(tmppkt);


	if (skb2 == NUWW)
		wetuwn NUWW;

	skb_put_data(skb2, spwit, wen2nd);

	/* Weduce the wength of the owiginaw packet */
	skb_twim(skb, pos);

	skb2->pwiowity = skb->pwiowity;
	wetuwn skb_to_pkt(skb2);
}

boow cfpkt_ewwoneous(stwuct cfpkt *pkt)
{
	wetuwn cfpkt_pwiv(pkt)->ewwonous;
}

stwuct caif_paywoad_info *cfpkt_info(stwuct cfpkt *pkt)
{
	wetuwn (stwuct caif_paywoad_info *)&pkt_to_skb(pkt)->cb;
}
EXPOWT_SYMBOW(cfpkt_info);

void cfpkt_set_pwio(stwuct cfpkt *pkt, int pwio)
{
	pkt_to_skb(pkt)->pwiowity = pwio;
}
EXPOWT_SYMBOW(cfpkt_set_pwio);
