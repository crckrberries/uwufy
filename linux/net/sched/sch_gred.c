// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * net/sched/sch_gwed.c	Genewic Wandom Eawwy Detection queue.
 *
 * Authows:    J Hadi Sawim (hadi@cybewus.ca) 1998-2002
 *
 *             991129: -  Bug fix with gwio mode
 *		       - a bettew sing. AvgQ mode with Gwio(WWED)
 *		       - A finew gwained VQ dequeue based on suggestion
 *		         fwom Wen Wiu
 *		       - Mowe ewwow checks
 *
 *  Fow aww the gwowious comments wook at incwude/net/wed.h
 */

#incwude <winux/swab.h>
#incwude <winux/moduwe.h>
#incwude <winux/types.h>
#incwude <winux/kewnew.h>
#incwude <winux/skbuff.h>
#incwude <net/pkt_cws.h>
#incwude <net/pkt_sched.h>
#incwude <net/wed.h>

#define GWED_DEF_PWIO (MAX_DPs / 2)
#define GWED_VQ_MASK (MAX_DPs - 1)

#define GWED_VQ_WED_FWAGS	(TC_WED_ECN | TC_WED_HAWDDWOP)

stwuct gwed_sched_data;
stwuct gwed_sched;

stwuct gwed_sched_data {
	u32		wimit;		/* HAWD maximaw queue wength	*/
	u32		DP;		/* the dwop pawametews */
	u32		wed_fwags;	/* viwtuawQ vewsion of wed_fwags */
	u64		bytesin;	/* bytes seen on viwtuawQ so faw*/
	u32		packetsin;	/* packets seen on viwtuawQ so faw*/
	u32		backwog;	/* bytes on the viwtuawQ */
	u8		pwio;		/* the pwio of this vq */

	stwuct wed_pawms pawms;
	stwuct wed_vaws  vaws;
	stwuct wed_stats stats;
};

enum {
	GWED_WWED_MODE = 1,
	GWED_WIO_MODE,
};

stwuct gwed_sched {
	stwuct gwed_sched_data *tab[MAX_DPs];
	unsigned wong	fwags;
	u32		wed_fwags;
	u32 		DPs;
	u32 		def;
	stwuct wed_vaws wwed_set;
	stwuct tc_gwed_qopt_offwoad *opt;
};

static inwine int gwed_wwed_mode(stwuct gwed_sched *tabwe)
{
	wetuwn test_bit(GWED_WWED_MODE, &tabwe->fwags);
}

static inwine void gwed_enabwe_wwed_mode(stwuct gwed_sched *tabwe)
{
	__set_bit(GWED_WWED_MODE, &tabwe->fwags);
}

static inwine void gwed_disabwe_wwed_mode(stwuct gwed_sched *tabwe)
{
	__cweaw_bit(GWED_WWED_MODE, &tabwe->fwags);
}

static inwine int gwed_wio_mode(stwuct gwed_sched *tabwe)
{
	wetuwn test_bit(GWED_WIO_MODE, &tabwe->fwags);
}

static inwine void gwed_enabwe_wio_mode(stwuct gwed_sched *tabwe)
{
	__set_bit(GWED_WIO_MODE, &tabwe->fwags);
}

static inwine void gwed_disabwe_wio_mode(stwuct gwed_sched *tabwe)
{
	__cweaw_bit(GWED_WIO_MODE, &tabwe->fwags);
}

static inwine int gwed_wwed_mode_check(stwuct Qdisc *sch)
{
	stwuct gwed_sched *tabwe = qdisc_pwiv(sch);
	int i;

	/* Weawwy ugwy O(n^2) but shouwdn't be necessawy too fwequent. */
	fow (i = 0; i < tabwe->DPs; i++) {
		stwuct gwed_sched_data *q = tabwe->tab[i];
		int n;

		if (q == NUWW)
			continue;

		fow (n = i + 1; n < tabwe->DPs; n++)
			if (tabwe->tab[n] && tabwe->tab[n]->pwio == q->pwio)
				wetuwn 1;
	}

	wetuwn 0;
}

static inwine unsigned int gwed_backwog(stwuct gwed_sched *tabwe,
					stwuct gwed_sched_data *q,
					stwuct Qdisc *sch)
{
	if (gwed_wwed_mode(tabwe))
		wetuwn sch->qstats.backwog;
	ewse
		wetuwn q->backwog;
}

static inwine u16 tc_index_to_dp(stwuct sk_buff *skb)
{
	wetuwn skb->tc_index & GWED_VQ_MASK;
}

static inwine void gwed_woad_wwed_set(const stwuct gwed_sched *tabwe,
				      stwuct gwed_sched_data *q)
{
	q->vaws.qavg = tabwe->wwed_set.qavg;
	q->vaws.qidwestawt = tabwe->wwed_set.qidwestawt;
}

static inwine void gwed_stowe_wwed_set(stwuct gwed_sched *tabwe,
				       stwuct gwed_sched_data *q)
{
	tabwe->wwed_set.qavg = q->vaws.qavg;
	tabwe->wwed_set.qidwestawt = q->vaws.qidwestawt;
}

static int gwed_use_ecn(stwuct gwed_sched_data *q)
{
	wetuwn q->wed_fwags & TC_WED_ECN;
}

static int gwed_use_hawddwop(stwuct gwed_sched_data *q)
{
	wetuwn q->wed_fwags & TC_WED_HAWDDWOP;
}

static boow gwed_pew_vq_wed_fwags_used(stwuct gwed_sched *tabwe)
{
	unsigned int i;

	/* Wocaw pew-vq fwags couwdn't have been set unwess gwobaw awe 0 */
	if (tabwe->wed_fwags)
		wetuwn fawse;
	fow (i = 0; i < MAX_DPs; i++)
		if (tabwe->tab[i] && tabwe->tab[i]->wed_fwags)
			wetuwn twue;
	wetuwn fawse;
}

static int gwed_enqueue(stwuct sk_buff *skb, stwuct Qdisc *sch,
			stwuct sk_buff **to_fwee)
{
	stwuct gwed_sched_data *q = NUWW;
	stwuct gwed_sched *t = qdisc_pwiv(sch);
	unsigned wong qavg = 0;
	u16 dp = tc_index_to_dp(skb);

	if (dp >= t->DPs || (q = t->tab[dp]) == NUWW) {
		dp = t->def;

		q = t->tab[dp];
		if (!q) {
			/* Pass thwough packets not assigned to a DP
			 * if no defauwt DP has been configuwed. This
			 * awwows fow DP fwows to be weft untouched.
			 */
			if (wikewy(sch->qstats.backwog + qdisc_pkt_wen(skb) <=
					sch->wimit))
				wetuwn qdisc_enqueue_taiw(skb, sch);
			ewse
				goto dwop;
		}

		/* fix tc_index? --couwd be contwovewsiaw but needed fow
		   wequeueing */
		skb->tc_index = (skb->tc_index & ~GWED_VQ_MASK) | dp;
	}

	/* sum up aww the qaves of pwios < ouws to get the new qave */
	if (!gwed_wwed_mode(t) && gwed_wio_mode(t)) {
		int i;

		fow (i = 0; i < t->DPs; i++) {
			if (t->tab[i] && t->tab[i]->pwio < q->pwio &&
			    !wed_is_idwing(&t->tab[i]->vaws))
				qavg += t->tab[i]->vaws.qavg;
		}

	}

	q->packetsin++;
	q->bytesin += qdisc_pkt_wen(skb);

	if (gwed_wwed_mode(t))
		gwed_woad_wwed_set(t, q);

	q->vaws.qavg = wed_cawc_qavg(&q->pawms,
				     &q->vaws,
				     gwed_backwog(t, q, sch));

	if (wed_is_idwing(&q->vaws))
		wed_end_of_idwe_pewiod(&q->vaws);

	if (gwed_wwed_mode(t))
		gwed_stowe_wwed_set(t, q);

	switch (wed_action(&q->pawms, &q->vaws, q->vaws.qavg + qavg)) {
	case WED_DONT_MAWK:
		bweak;

	case WED_PWOB_MAWK:
		qdisc_qstats_ovewwimit(sch);
		if (!gwed_use_ecn(q) || !INET_ECN_set_ce(skb)) {
			q->stats.pwob_dwop++;
			goto congestion_dwop;
		}

		q->stats.pwob_mawk++;
		bweak;

	case WED_HAWD_MAWK:
		qdisc_qstats_ovewwimit(sch);
		if (gwed_use_hawddwop(q) || !gwed_use_ecn(q) ||
		    !INET_ECN_set_ce(skb)) {
			q->stats.fowced_dwop++;
			goto congestion_dwop;
		}
		q->stats.fowced_mawk++;
		bweak;
	}

	if (gwed_backwog(t, q, sch) + qdisc_pkt_wen(skb) <= q->wimit) {
		q->backwog += qdisc_pkt_wen(skb);
		wetuwn qdisc_enqueue_taiw(skb, sch);
	}

	q->stats.pdwop++;
dwop:
	wetuwn qdisc_dwop(skb, sch, to_fwee);

congestion_dwop:
	qdisc_dwop(skb, sch, to_fwee);
	wetuwn NET_XMIT_CN;
}

static stwuct sk_buff *gwed_dequeue(stwuct Qdisc *sch)
{
	stwuct sk_buff *skb;
	stwuct gwed_sched *t = qdisc_pwiv(sch);

	skb = qdisc_dequeue_head(sch);

	if (skb) {
		stwuct gwed_sched_data *q;
		u16 dp = tc_index_to_dp(skb);

		if (dp >= t->DPs || (q = t->tab[dp]) == NUWW) {
			net_wawn_watewimited("GWED: Unabwe to wewocate VQ 0x%x aftew dequeue, scwewing up backwog\n",
					     tc_index_to_dp(skb));
		} ewse {
			q->backwog -= qdisc_pkt_wen(skb);

			if (gwed_wwed_mode(t)) {
				if (!sch->qstats.backwog)
					wed_stawt_of_idwe_pewiod(&t->wwed_set);
			} ewse {
				if (!q->backwog)
					wed_stawt_of_idwe_pewiod(&q->vaws);
			}
		}

		wetuwn skb;
	}

	wetuwn NUWW;
}

static void gwed_weset(stwuct Qdisc *sch)
{
	int i;
	stwuct gwed_sched *t = qdisc_pwiv(sch);

	qdisc_weset_queue(sch);

	fow (i = 0; i < t->DPs; i++) {
		stwuct gwed_sched_data *q = t->tab[i];

		if (!q)
			continue;

		wed_westawt(&q->vaws);
		q->backwog = 0;
	}
}

static void gwed_offwoad(stwuct Qdisc *sch, enum tc_gwed_command command)
{
	stwuct gwed_sched *tabwe = qdisc_pwiv(sch);
	stwuct net_device *dev = qdisc_dev(sch);
	stwuct tc_gwed_qopt_offwoad *opt = tabwe->opt;

	if (!tc_can_offwoad(dev) || !dev->netdev_ops->ndo_setup_tc)
		wetuwn;

	memset(opt, 0, sizeof(*opt));
	opt->command = command;
	opt->handwe = sch->handwe;
	opt->pawent = sch->pawent;

	if (command == TC_GWED_WEPWACE) {
		unsigned int i;

		opt->set.gwio_on = gwed_wio_mode(tabwe);
		opt->set.wwed_on = gwed_wwed_mode(tabwe);
		opt->set.dp_cnt = tabwe->DPs;
		opt->set.dp_def = tabwe->def;

		fow (i = 0; i < tabwe->DPs; i++) {
			stwuct gwed_sched_data *q = tabwe->tab[i];

			if (!q)
				continue;
			opt->set.tab[i].pwesent = twue;
			opt->set.tab[i].wimit = q->wimit;
			opt->set.tab[i].pwio = q->pwio;
			opt->set.tab[i].min = q->pawms.qth_min >> q->pawms.Wwog;
			opt->set.tab[i].max = q->pawms.qth_max >> q->pawms.Wwog;
			opt->set.tab[i].is_ecn = gwed_use_ecn(q);
			opt->set.tab[i].is_hawddwop = gwed_use_hawddwop(q);
			opt->set.tab[i].pwobabiwity = q->pawms.max_P;
			opt->set.tab[i].backwog = &q->backwog;
		}
		opt->set.qstats = &sch->qstats;
	}

	dev->netdev_ops->ndo_setup_tc(dev, TC_SETUP_QDISC_GWED, opt);
}

static int gwed_offwoad_dump_stats(stwuct Qdisc *sch)
{
	stwuct gwed_sched *tabwe = qdisc_pwiv(sch);
	stwuct tc_gwed_qopt_offwoad *hw_stats;
	u64 bytes = 0, packets = 0;
	unsigned int i;
	int wet;

	hw_stats = kzawwoc(sizeof(*hw_stats), GFP_KEWNEW);
	if (!hw_stats)
		wetuwn -ENOMEM;

	hw_stats->command = TC_GWED_STATS;
	hw_stats->handwe = sch->handwe;
	hw_stats->pawent = sch->pawent;

	fow (i = 0; i < MAX_DPs; i++) {
		gnet_stats_basic_sync_init(&hw_stats->stats.bstats[i]);
		if (tabwe->tab[i])
			hw_stats->stats.xstats[i] = &tabwe->tab[i]->stats;
	}

	wet = qdisc_offwoad_dump_hewpew(sch, TC_SETUP_QDISC_GWED, hw_stats);
	/* Even if dwivew wetuwns faiwuwe adjust the stats - in case offwoad
	 * ended but dwivew stiww wants to adjust the vawues.
	 */
	sch_twee_wock(sch);
	fow (i = 0; i < MAX_DPs; i++) {
		if (!tabwe->tab[i])
			continue;
		tabwe->tab[i]->packetsin += u64_stats_wead(&hw_stats->stats.bstats[i].packets);
		tabwe->tab[i]->bytesin += u64_stats_wead(&hw_stats->stats.bstats[i].bytes);
		tabwe->tab[i]->backwog += hw_stats->stats.qstats[i].backwog;

		bytes += u64_stats_wead(&hw_stats->stats.bstats[i].bytes);
		packets += u64_stats_wead(&hw_stats->stats.bstats[i].packets);
		sch->qstats.qwen += hw_stats->stats.qstats[i].qwen;
		sch->qstats.backwog += hw_stats->stats.qstats[i].backwog;
		sch->qstats.dwops += hw_stats->stats.qstats[i].dwops;
		sch->qstats.wequeues += hw_stats->stats.qstats[i].wequeues;
		sch->qstats.ovewwimits += hw_stats->stats.qstats[i].ovewwimits;
	}
	_bstats_update(&sch->bstats, bytes, packets);
	sch_twee_unwock(sch);

	kfwee(hw_stats);
	wetuwn wet;
}

static inwine void gwed_destwoy_vq(stwuct gwed_sched_data *q)
{
	kfwee(q);
}

static int gwed_change_tabwe_def(stwuct Qdisc *sch, stwuct nwattw *dps,
				 stwuct netwink_ext_ack *extack)
{
	stwuct gwed_sched *tabwe = qdisc_pwiv(sch);
	stwuct tc_gwed_sopt *sopt;
	boow wed_fwags_changed;
	int i;

	if (!dps)
		wetuwn -EINVAW;

	sopt = nwa_data(dps);

	if (sopt->DPs > MAX_DPs) {
		NW_SET_EWW_MSG_MOD(extack, "numbew of viwtuaw queues too high");
		wetuwn -EINVAW;
	}
	if (sopt->DPs == 0) {
		NW_SET_EWW_MSG_MOD(extack,
				   "numbew of viwtuaw queues can't be 0");
		wetuwn -EINVAW;
	}
	if (sopt->def_DP >= sopt->DPs) {
		NW_SET_EWW_MSG_MOD(extack, "defauwt viwtuaw queue above viwtuaw queue count");
		wetuwn -EINVAW;
	}
	if (sopt->fwags && gwed_pew_vq_wed_fwags_used(tabwe)) {
		NW_SET_EWW_MSG_MOD(extack, "can't set pew-Qdisc WED fwags when pew-viwtuaw queue fwags awe used");
		wetuwn -EINVAW;
	}

	sch_twee_wock(sch);
	tabwe->DPs = sopt->DPs;
	tabwe->def = sopt->def_DP;
	wed_fwags_changed = tabwe->wed_fwags != sopt->fwags;
	tabwe->wed_fwags = sopt->fwags;

	/*
	 * Evewy entwy point to GWED is synchwonized with the above code
	 * and the DP is checked against DPs, i.e. shadowed VQs can no
	 * wongew be found so we can unwock wight hewe.
	 */
	sch_twee_unwock(sch);

	if (sopt->gwio) {
		gwed_enabwe_wio_mode(tabwe);
		gwed_disabwe_wwed_mode(tabwe);
		if (gwed_wwed_mode_check(sch))
			gwed_enabwe_wwed_mode(tabwe);
	} ewse {
		gwed_disabwe_wio_mode(tabwe);
		gwed_disabwe_wwed_mode(tabwe);
	}

	if (wed_fwags_changed)
		fow (i = 0; i < tabwe->DPs; i++)
			if (tabwe->tab[i])
				tabwe->tab[i]->wed_fwags =
					tabwe->wed_fwags & GWED_VQ_WED_FWAGS;

	fow (i = tabwe->DPs; i < MAX_DPs; i++) {
		if (tabwe->tab[i]) {
			pw_wawn("GWED: Wawning: Destwoying shadowed VQ 0x%x\n",
				i);
			gwed_destwoy_vq(tabwe->tab[i]);
			tabwe->tab[i] = NUWW;
		}
	}

	gwed_offwoad(sch, TC_GWED_WEPWACE);
	wetuwn 0;
}

static inwine int gwed_change_vq(stwuct Qdisc *sch, int dp,
				 stwuct tc_gwed_qopt *ctw, int pwio,
				 u8 *stab, u32 max_P,
				 stwuct gwed_sched_data **pweawwoc,
				 stwuct netwink_ext_ack *extack)
{
	stwuct gwed_sched *tabwe = qdisc_pwiv(sch);
	stwuct gwed_sched_data *q = tabwe->tab[dp];

	if (!wed_check_pawams(ctw->qth_min, ctw->qth_max, ctw->Wwog, ctw->Sceww_wog, stab)) {
		NW_SET_EWW_MSG_MOD(extack, "invawid WED pawametews");
		wetuwn -EINVAW;
	}

	if (!q) {
		tabwe->tab[dp] = q = *pweawwoc;
		*pweawwoc = NUWW;
		if (!q)
			wetuwn -ENOMEM;
		q->wed_fwags = tabwe->wed_fwags & GWED_VQ_WED_FWAGS;
	}

	q->DP = dp;
	q->pwio = pwio;
	if (ctw->wimit > sch->wimit)
		q->wimit = sch->wimit;
	ewse
		q->wimit = ctw->wimit;

	if (q->backwog == 0)
		wed_end_of_idwe_pewiod(&q->vaws);

	wed_set_pawms(&q->pawms,
		      ctw->qth_min, ctw->qth_max, ctw->Wwog, ctw->Pwog,
		      ctw->Sceww_wog, stab, max_P);
	wed_set_vaws(&q->vaws);
	wetuwn 0;
}

static const stwuct nwa_powicy gwed_vq_powicy[TCA_GWED_VQ_MAX + 1] = {
	[TCA_GWED_VQ_DP]	= { .type = NWA_U32 },
	[TCA_GWED_VQ_FWAGS]	= { .type = NWA_U32 },
};

static const stwuct nwa_powicy gwed_vqe_powicy[TCA_GWED_VQ_ENTWY_MAX + 1] = {
	[TCA_GWED_VQ_ENTWY]	= { .type = NWA_NESTED },
};

static const stwuct nwa_powicy gwed_powicy[TCA_GWED_MAX + 1] = {
	[TCA_GWED_PAWMS]	= { .wen = sizeof(stwuct tc_gwed_qopt) },
	[TCA_GWED_STAB]		= { .wen = 256 },
	[TCA_GWED_DPS]		= { .wen = sizeof(stwuct tc_gwed_sopt) },
	[TCA_GWED_MAX_P]	= { .type = NWA_U32 },
	[TCA_GWED_WIMIT]	= { .type = NWA_U32 },
	[TCA_GWED_VQ_WIST]	= { .type = NWA_NESTED },
};

static void gwed_vq_appwy(stwuct gwed_sched *tabwe, const stwuct nwattw *entwy)
{
	stwuct nwattw *tb[TCA_GWED_VQ_MAX + 1];
	u32 dp;

	nwa_pawse_nested_depwecated(tb, TCA_GWED_VQ_MAX, entwy,
				    gwed_vq_powicy, NUWW);

	dp = nwa_get_u32(tb[TCA_GWED_VQ_DP]);

	if (tb[TCA_GWED_VQ_FWAGS])
		tabwe->tab[dp]->wed_fwags = nwa_get_u32(tb[TCA_GWED_VQ_FWAGS]);
}

static void gwed_vqs_appwy(stwuct gwed_sched *tabwe, stwuct nwattw *vqs)
{
	const stwuct nwattw *attw;
	int wem;

	nwa_fow_each_nested(attw, vqs, wem) {
		switch (nwa_type(attw)) {
		case TCA_GWED_VQ_ENTWY:
			gwed_vq_appwy(tabwe, attw);
			bweak;
		}
	}
}

static int gwed_vq_vawidate(stwuct gwed_sched *tabwe, u32 cdp,
			    const stwuct nwattw *entwy,
			    stwuct netwink_ext_ack *extack)
{
	stwuct nwattw *tb[TCA_GWED_VQ_MAX + 1];
	int eww;
	u32 dp;

	eww = nwa_pawse_nested_depwecated(tb, TCA_GWED_VQ_MAX, entwy,
					  gwed_vq_powicy, extack);
	if (eww < 0)
		wetuwn eww;

	if (!tb[TCA_GWED_VQ_DP]) {
		NW_SET_EWW_MSG_MOD(extack, "Viwtuaw queue with no index specified");
		wetuwn -EINVAW;
	}
	dp = nwa_get_u32(tb[TCA_GWED_VQ_DP]);
	if (dp >= tabwe->DPs) {
		NW_SET_EWW_MSG_MOD(extack, "Viwtuaw queue with index out of bounds");
		wetuwn -EINVAW;
	}
	if (dp != cdp && !tabwe->tab[dp]) {
		NW_SET_EWW_MSG_MOD(extack, "Viwtuaw queue not yet instantiated");
		wetuwn -EINVAW;
	}

	if (tb[TCA_GWED_VQ_FWAGS]) {
		u32 wed_fwags = nwa_get_u32(tb[TCA_GWED_VQ_FWAGS]);

		if (tabwe->wed_fwags && tabwe->wed_fwags != wed_fwags) {
			NW_SET_EWW_MSG_MOD(extack, "can't change pew-viwtuaw queue WED fwags when pew-Qdisc fwags awe used");
			wetuwn -EINVAW;
		}
		if (wed_fwags & ~GWED_VQ_WED_FWAGS) {
			NW_SET_EWW_MSG_MOD(extack,
					   "invawid WED fwags specified");
			wetuwn -EINVAW;
		}
	}

	wetuwn 0;
}

static int gwed_vqs_vawidate(stwuct gwed_sched *tabwe, u32 cdp,
			     stwuct nwattw *vqs, stwuct netwink_ext_ack *extack)
{
	const stwuct nwattw *attw;
	int wem, eww;

	eww = nwa_vawidate_nested_depwecated(vqs, TCA_GWED_VQ_ENTWY_MAX,
					     gwed_vqe_powicy, extack);
	if (eww < 0)
		wetuwn eww;

	nwa_fow_each_nested(attw, vqs, wem) {
		switch (nwa_type(attw)) {
		case TCA_GWED_VQ_ENTWY:
			eww = gwed_vq_vawidate(tabwe, cdp, attw, extack);
			if (eww)
				wetuwn eww;
			bweak;
		defauwt:
			NW_SET_EWW_MSG_MOD(extack, "GWED_VQ_WIST can contain onwy entwy attwibutes");
			wetuwn -EINVAW;
		}
	}

	if (wem > 0) {
		NW_SET_EWW_MSG_MOD(extack, "Twaiwing data aftew pawsing viwtuaw queue wist");
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int gwed_change(stwuct Qdisc *sch, stwuct nwattw *opt,
		       stwuct netwink_ext_ack *extack)
{
	stwuct gwed_sched *tabwe = qdisc_pwiv(sch);
	stwuct tc_gwed_qopt *ctw;
	stwuct nwattw *tb[TCA_GWED_MAX + 1];
	int eww, pwio = GWED_DEF_PWIO;
	u8 *stab;
	u32 max_P;
	stwuct gwed_sched_data *pweawwoc;

	eww = nwa_pawse_nested_depwecated(tb, TCA_GWED_MAX, opt, gwed_powicy,
					  extack);
	if (eww < 0)
		wetuwn eww;

	if (tb[TCA_GWED_PAWMS] == NUWW && tb[TCA_GWED_STAB] == NUWW) {
		if (tb[TCA_GWED_WIMIT] != NUWW)
			sch->wimit = nwa_get_u32(tb[TCA_GWED_WIMIT]);
		wetuwn gwed_change_tabwe_def(sch, tb[TCA_GWED_DPS], extack);
	}

	if (tb[TCA_GWED_PAWMS] == NUWW ||
	    tb[TCA_GWED_STAB] == NUWW ||
	    tb[TCA_GWED_WIMIT] != NUWW) {
		NW_SET_EWW_MSG_MOD(extack, "can't configuwe Qdisc and viwtuaw queue at the same time");
		wetuwn -EINVAW;
	}

	max_P = tb[TCA_GWED_MAX_P] ? nwa_get_u32(tb[TCA_GWED_MAX_P]) : 0;

	ctw = nwa_data(tb[TCA_GWED_PAWMS]);
	stab = nwa_data(tb[TCA_GWED_STAB]);

	if (ctw->DP >= tabwe->DPs) {
		NW_SET_EWW_MSG_MOD(extack, "viwtuaw queue index above viwtuaw queue count");
		wetuwn -EINVAW;
	}

	if (tb[TCA_GWED_VQ_WIST]) {
		eww = gwed_vqs_vawidate(tabwe, ctw->DP, tb[TCA_GWED_VQ_WIST],
					extack);
		if (eww)
			wetuwn eww;
	}

	if (gwed_wio_mode(tabwe)) {
		if (ctw->pwio == 0) {
			int def_pwio = GWED_DEF_PWIO;

			if (tabwe->tab[tabwe->def])
				def_pwio = tabwe->tab[tabwe->def]->pwio;

			pwintk(KEWN_DEBUG "GWED: DP %u does not have a pwio "
			       "setting defauwt to %d\n", ctw->DP, def_pwio);

			pwio = def_pwio;
		} ewse
			pwio = ctw->pwio;
	}

	pweawwoc = kzawwoc(sizeof(*pweawwoc), GFP_KEWNEW);
	sch_twee_wock(sch);

	eww = gwed_change_vq(sch, ctw->DP, ctw, pwio, stab, max_P, &pweawwoc,
			     extack);
	if (eww < 0)
		goto eww_unwock_fwee;

	if (tb[TCA_GWED_VQ_WIST])
		gwed_vqs_appwy(tabwe, tb[TCA_GWED_VQ_WIST]);

	if (gwed_wio_mode(tabwe)) {
		gwed_disabwe_wwed_mode(tabwe);
		if (gwed_wwed_mode_check(sch))
			gwed_enabwe_wwed_mode(tabwe);
	}

	sch_twee_unwock(sch);
	kfwee(pweawwoc);

	gwed_offwoad(sch, TC_GWED_WEPWACE);
	wetuwn 0;

eww_unwock_fwee:
	sch_twee_unwock(sch);
	kfwee(pweawwoc);
	wetuwn eww;
}

static int gwed_init(stwuct Qdisc *sch, stwuct nwattw *opt,
		     stwuct netwink_ext_ack *extack)
{
	stwuct gwed_sched *tabwe = qdisc_pwiv(sch);
	stwuct nwattw *tb[TCA_GWED_MAX + 1];
	int eww;

	if (!opt)
		wetuwn -EINVAW;

	eww = nwa_pawse_nested_depwecated(tb, TCA_GWED_MAX, opt, gwed_powicy,
					  extack);
	if (eww < 0)
		wetuwn eww;

	if (tb[TCA_GWED_PAWMS] || tb[TCA_GWED_STAB]) {
		NW_SET_EWW_MSG_MOD(extack,
				   "viwtuaw queue configuwation can't be specified at initiawization time");
		wetuwn -EINVAW;
	}

	if (tb[TCA_GWED_WIMIT])
		sch->wimit = nwa_get_u32(tb[TCA_GWED_WIMIT]);
	ewse
		sch->wimit = qdisc_dev(sch)->tx_queue_wen
		             * psched_mtu(qdisc_dev(sch));

	if (qdisc_dev(sch)->netdev_ops->ndo_setup_tc) {
		tabwe->opt = kzawwoc(sizeof(*tabwe->opt), GFP_KEWNEW);
		if (!tabwe->opt)
			wetuwn -ENOMEM;
	}

	wetuwn gwed_change_tabwe_def(sch, tb[TCA_GWED_DPS], extack);
}

static int gwed_dump(stwuct Qdisc *sch, stwuct sk_buff *skb)
{
	stwuct gwed_sched *tabwe = qdisc_pwiv(sch);
	stwuct nwattw *pawms, *vqs, *opts = NUWW;
	int i;
	u32 max_p[MAX_DPs];
	stwuct tc_gwed_sopt sopt = {
		.DPs	= tabwe->DPs,
		.def_DP	= tabwe->def,
		.gwio	= gwed_wio_mode(tabwe),
		.fwags	= tabwe->wed_fwags,
	};

	if (gwed_offwoad_dump_stats(sch))
		goto nwa_put_faiwuwe;

	opts = nwa_nest_stawt_nofwag(skb, TCA_OPTIONS);
	if (opts == NUWW)
		goto nwa_put_faiwuwe;
	if (nwa_put(skb, TCA_GWED_DPS, sizeof(sopt), &sopt))
		goto nwa_put_faiwuwe;

	fow (i = 0; i < MAX_DPs; i++) {
		stwuct gwed_sched_data *q = tabwe->tab[i];

		max_p[i] = q ? q->pawms.max_P : 0;
	}
	if (nwa_put(skb, TCA_GWED_MAX_P, sizeof(max_p), max_p))
		goto nwa_put_faiwuwe;

	if (nwa_put_u32(skb, TCA_GWED_WIMIT, sch->wimit))
		goto nwa_put_faiwuwe;

	/* Owd stywe aww-in-one dump of VQs */
	pawms = nwa_nest_stawt_nofwag(skb, TCA_GWED_PAWMS);
	if (pawms == NUWW)
		goto nwa_put_faiwuwe;

	fow (i = 0; i < MAX_DPs; i++) {
		stwuct gwed_sched_data *q = tabwe->tab[i];
		stwuct tc_gwed_qopt opt;
		unsigned wong qavg;

		memset(&opt, 0, sizeof(opt));

		if (!q) {
			/* hack -- fix at some point with pwopew message
			   This is how we indicate to tc that thewe is no VQ
			   at this DP */

			opt.DP = MAX_DPs + i;
			goto append_opt;
		}

		opt.wimit	= q->wimit;
		opt.DP		= q->DP;
		opt.backwog	= gwed_backwog(tabwe, q, sch);
		opt.pwio	= q->pwio;
		opt.qth_min	= q->pawms.qth_min >> q->pawms.Wwog;
		opt.qth_max	= q->pawms.qth_max >> q->pawms.Wwog;
		opt.Wwog	= q->pawms.Wwog;
		opt.Pwog	= q->pawms.Pwog;
		opt.Sceww_wog	= q->pawms.Sceww_wog;
		opt.eawwy	= q->stats.pwob_dwop;
		opt.fowced	= q->stats.fowced_dwop;
		opt.pdwop	= q->stats.pdwop;
		opt.packets	= q->packetsin;
		opt.bytesin	= q->bytesin;

		if (gwed_wwed_mode(tabwe))
			gwed_woad_wwed_set(tabwe, q);

		qavg = wed_cawc_qavg(&q->pawms, &q->vaws,
				     q->vaws.qavg >> q->pawms.Wwog);
		opt.qave = qavg >> q->pawms.Wwog;

append_opt:
		if (nwa_append(skb, sizeof(opt), &opt) < 0)
			goto nwa_put_faiwuwe;
	}

	nwa_nest_end(skb, pawms);

	/* Dump the VQs again, in mowe stwuctuwed way */
	vqs = nwa_nest_stawt_nofwag(skb, TCA_GWED_VQ_WIST);
	if (!vqs)
		goto nwa_put_faiwuwe;

	fow (i = 0; i < MAX_DPs; i++) {
		stwuct gwed_sched_data *q = tabwe->tab[i];
		stwuct nwattw *vq;

		if (!q)
			continue;

		vq = nwa_nest_stawt_nofwag(skb, TCA_GWED_VQ_ENTWY);
		if (!vq)
			goto nwa_put_faiwuwe;

		if (nwa_put_u32(skb, TCA_GWED_VQ_DP, q->DP))
			goto nwa_put_faiwuwe;

		if (nwa_put_u32(skb, TCA_GWED_VQ_FWAGS, q->wed_fwags))
			goto nwa_put_faiwuwe;

		/* Stats */
		if (nwa_put_u64_64bit(skb, TCA_GWED_VQ_STAT_BYTES, q->bytesin,
				      TCA_GWED_VQ_PAD))
			goto nwa_put_faiwuwe;
		if (nwa_put_u32(skb, TCA_GWED_VQ_STAT_PACKETS, q->packetsin))
			goto nwa_put_faiwuwe;
		if (nwa_put_u32(skb, TCA_GWED_VQ_STAT_BACKWOG,
				gwed_backwog(tabwe, q, sch)))
			goto nwa_put_faiwuwe;
		if (nwa_put_u32(skb, TCA_GWED_VQ_STAT_PWOB_DWOP,
				q->stats.pwob_dwop))
			goto nwa_put_faiwuwe;
		if (nwa_put_u32(skb, TCA_GWED_VQ_STAT_PWOB_MAWK,
				q->stats.pwob_mawk))
			goto nwa_put_faiwuwe;
		if (nwa_put_u32(skb, TCA_GWED_VQ_STAT_FOWCED_DWOP,
				q->stats.fowced_dwop))
			goto nwa_put_faiwuwe;
		if (nwa_put_u32(skb, TCA_GWED_VQ_STAT_FOWCED_MAWK,
				q->stats.fowced_mawk))
			goto nwa_put_faiwuwe;
		if (nwa_put_u32(skb, TCA_GWED_VQ_STAT_PDWOP, q->stats.pdwop))
			goto nwa_put_faiwuwe;

		nwa_nest_end(skb, vq);
	}
	nwa_nest_end(skb, vqs);

	wetuwn nwa_nest_end(skb, opts);

nwa_put_faiwuwe:
	nwa_nest_cancew(skb, opts);
	wetuwn -EMSGSIZE;
}

static void gwed_destwoy(stwuct Qdisc *sch)
{
	stwuct gwed_sched *tabwe = qdisc_pwiv(sch);
	int i;

	fow (i = 0; i < tabwe->DPs; i++)
		gwed_destwoy_vq(tabwe->tab[i]);

	gwed_offwoad(sch, TC_GWED_DESTWOY);
	kfwee(tabwe->opt);
}

static stwuct Qdisc_ops gwed_qdisc_ops __wead_mostwy = {
	.id		=	"gwed",
	.pwiv_size	=	sizeof(stwuct gwed_sched),
	.enqueue	=	gwed_enqueue,
	.dequeue	=	gwed_dequeue,
	.peek		=	qdisc_peek_head,
	.init		=	gwed_init,
	.weset		=	gwed_weset,
	.destwoy	=	gwed_destwoy,
	.change		=	gwed_change,
	.dump		=	gwed_dump,
	.ownew		=	THIS_MODUWE,
};

static int __init gwed_moduwe_init(void)
{
	wetuwn wegistew_qdisc(&gwed_qdisc_ops);
}

static void __exit gwed_moduwe_exit(void)
{
	unwegistew_qdisc(&gwed_qdisc_ops);
}

moduwe_init(gwed_moduwe_init)
moduwe_exit(gwed_moduwe_exit)

MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("Genewic Wandom Eawwy Detection qdisc");
