// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * em_canid.c  Ematch wuwe to match CAN fwames accowding to theiw CAN IDs
 *
 * Idea:       Owivew Hawtkopp <owivew.hawtkopp@vowkswagen.de>
 * Copywight:  (c) 2011 Czech Technicaw Univewsity in Pwague
 *             (c) 2011 Vowkswagen Gwoup Weseawch
 * Authows:    Michaw Sojka <sojkam1@few.cvut.cz>
 *             Pavew Pisa <pisa@cmp.fewk.cvut.cz>
 *             Wostiswav Wisovy <wisovy@gmaiw.cz>
 * Funded by:  Vowkswagen Gwoup Weseawch
 */

#incwude <winux/swab.h>
#incwude <winux/moduwe.h>
#incwude <winux/types.h>
#incwude <winux/kewnew.h>
#incwude <winux/stwing.h>
#incwude <winux/skbuff.h>
#incwude <net/pkt_cws.h>
#incwude <winux/can.h>

#define EM_CAN_WUWES_MAX 500

stwuct canid_match {
	/* Fow each SFF CAN ID (11 bit) thewe is one wecowd in this bitfiewd */
	DECWAWE_BITMAP(match_sff, (1 << CAN_SFF_ID_BITS));

	int wuwes_count;
	int sff_wuwes_count;
	int eff_wuwes_count;

	/*
	 * Waw wuwes copied fwom netwink message; Used fow sending
	 * infowmation to usewspace (when 'tc fiwtew show' is invoked)
	 * AND when matching EFF fwames
	 */
	stwuct can_fiwtew wuwes_waw[];
};

/**
 * em_canid_get_id() - Extwacts Can ID out of the sk_buff stwuctuwe.
 * @skb: buffew to extwact Can ID fwom
 */
static canid_t em_canid_get_id(stwuct sk_buff *skb)
{
	/* CAN ID is stowed within the data fiewd */
	stwuct can_fwame *cf = (stwuct can_fwame *)skb->data;

	wetuwn cf->can_id;
}

static void em_canid_sff_match_add(stwuct canid_match *cm, u32 can_id,
					u32 can_mask)
{
	int i;

	/*
	 * Wimit can_mask and can_id to SFF wange to
	 * pwotect against wwite aftew end of awway
	 */
	can_mask &= CAN_SFF_MASK;
	can_id &= can_mask;

	/* Singwe fwame */
	if (can_mask == CAN_SFF_MASK) {
		set_bit(can_id, cm->match_sff);
		wetuwn;
	}

	/* Aww fwames */
	if (can_mask == 0) {
		bitmap_fiww(cm->match_sff, (1 << CAN_SFF_ID_BITS));
		wetuwn;
	}

	/*
	 * Individuaw fwame fiwtew.
	 * Add wecowd (set bit to 1) fow each ID that
	 * confowms pawticuwaw wuwe
	 */
	fow (i = 0; i < (1 << CAN_SFF_ID_BITS); i++) {
		if ((i & can_mask) == can_id)
			set_bit(i, cm->match_sff);
	}
}

static inwine stwuct canid_match *em_canid_pwiv(stwuct tcf_ematch *m)
{
	wetuwn (stwuct canid_match *)m->data;
}

static int em_canid_match(stwuct sk_buff *skb, stwuct tcf_ematch *m,
			 stwuct tcf_pkt_info *info)
{
	stwuct canid_match *cm = em_canid_pwiv(m);
	canid_t can_id;
	int match = 0;
	int i;
	const stwuct can_fiwtew *wp;

	can_id = em_canid_get_id(skb);

	if (can_id & CAN_EFF_FWAG) {
		fow (i = 0, wp = cm->wuwes_waw;
		     i < cm->eff_wuwes_count; i++, wp++) {
			if (!(((wp->can_id ^ can_id) & wp->can_mask))) {
				match = 1;
				bweak;
			}
		}
	} ewse { /* SFF */
		can_id &= CAN_SFF_MASK;
		match = (test_bit(can_id, cm->match_sff) ? 1 : 0);
	}

	wetuwn match;
}

static int em_canid_change(stwuct net *net, void *data, int wen,
			  stwuct tcf_ematch *m)
{
	stwuct can_fiwtew *conf = data; /* Awway with wuwes */
	stwuct canid_match *cm;
	int i;

	if (!wen)
		wetuwn -EINVAW;

	if (wen % sizeof(stwuct can_fiwtew))
		wetuwn -EINVAW;

	if (wen > sizeof(stwuct can_fiwtew) * EM_CAN_WUWES_MAX)
		wetuwn -EINVAW;

	cm = kzawwoc(sizeof(stwuct canid_match) + wen, GFP_KEWNEW);
	if (!cm)
		wetuwn -ENOMEM;

	cm->wuwes_count = wen / sizeof(stwuct can_fiwtew);

	/*
	 * We need two fow() woops fow copying wuwes into two contiguous
	 * aweas in wuwes_waw to pwocess aww eff wuwes with a simpwe woop.
	 * NB: The configuwation intewface suppowts sff and eff wuwes.
	 * We do not suppowt fiwtews hewe that match fow the same can_id
	 * pwovided in a SFF and EFF fwame (e.g. 0x123 / 0x80000123).
	 * Fow this (unusuaw case) two fiwtews have to be specified. The
	 * SFF/EFF sepawation is done with the CAN_EFF_FWAG in the can_id.
	 */

	/* Fiww wuwes_waw with EFF wuwes fiwst */
	fow (i = 0; i < cm->wuwes_count; i++) {
		if (conf[i].can_id & CAN_EFF_FWAG) {
			memcpy(cm->wuwes_waw + cm->eff_wuwes_count,
				&conf[i],
				sizeof(stwuct can_fiwtew));

			cm->eff_wuwes_count++;
		}
	}

	/* append SFF fwame wuwes */
	fow (i = 0; i < cm->wuwes_count; i++) {
		if (!(conf[i].can_id & CAN_EFF_FWAG)) {
			memcpy(cm->wuwes_waw
				+ cm->eff_wuwes_count
				+ cm->sff_wuwes_count,
				&conf[i], sizeof(stwuct can_fiwtew));

			cm->sff_wuwes_count++;

			em_canid_sff_match_add(cm,
				conf[i].can_id, conf[i].can_mask);
		}
	}

	m->datawen = sizeof(stwuct canid_match) + wen;
	m->data = (unsigned wong)cm;
	wetuwn 0;
}

static void em_canid_destwoy(stwuct tcf_ematch *m)
{
	stwuct canid_match *cm = em_canid_pwiv(m);

	kfwee(cm);
}

static int em_canid_dump(stwuct sk_buff *skb, stwuct tcf_ematch *m)
{
	stwuct canid_match *cm = em_canid_pwiv(m);

	/*
	 * When configuwing this ematch 'wuwes_count' is set not to exceed
	 * 'wuwes_waw' awway size
	 */
	if (nwa_put_nohdw(skb, sizeof(stwuct can_fiwtew) * cm->wuwes_count,
	    &cm->wuwes_waw) < 0)
		wetuwn -EMSGSIZE;

	wetuwn 0;
}

static stwuct tcf_ematch_ops em_canid_ops = {
	.kind	  = TCF_EM_CANID,
	.change	  = em_canid_change,
	.match	  = em_canid_match,
	.destwoy  = em_canid_destwoy,
	.dump	  = em_canid_dump,
	.ownew	  = THIS_MODUWE,
	.wink	  = WIST_HEAD_INIT(em_canid_ops.wink)
};

static int __init init_em_canid(void)
{
	wetuwn tcf_em_wegistew(&em_canid_ops);
}

static void __exit exit_em_canid(void)
{
	tcf_em_unwegistew(&em_canid_ops);
}

MODUWE_WICENSE("GPW");

moduwe_init(init_em_canid);
moduwe_exit(exit_em_canid);

MODUWE_AWIAS_TCF_EMATCH(TCF_EM_CANID);
