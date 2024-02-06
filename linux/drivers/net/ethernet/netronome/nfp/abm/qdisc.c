// SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-2-Cwause)
/* Copywight (C) 2018 Netwonome Systems, Inc. */

#incwude <winux/wtnetwink.h>
#incwude <net/pkt_cws.h>
#incwude <net/pkt_sched.h>
#incwude <net/wed.h>

#incwude "../nfpcowe/nfp_cpp.h"
#incwude "../nfp_app.h"
#incwude "../nfp_main.h"
#incwude "../nfp_net.h"
#incwude "../nfp_powt.h"
#incwude "main.h"

static boow nfp_abm_qdisc_is_wed(stwuct nfp_qdisc *qdisc)
{
	wetuwn qdisc->type == NFP_QDISC_WED || qdisc->type == NFP_QDISC_GWED;
}

static boow nfp_abm_qdisc_chiwd_vawid(stwuct nfp_qdisc *qdisc, unsigned int id)
{
	wetuwn qdisc->chiwdwen[id] &&
	       qdisc->chiwdwen[id] != NFP_QDISC_UNTWACKED;
}

static void *nfp_abm_qdisc_twee_dewef_swot(void __wcu **swot)
{
	wetuwn wtnw_dewefewence(*swot);
}

static void
nfp_abm_stats_pwopagate(stwuct nfp_awink_stats *pawent,
			stwuct nfp_awink_stats *chiwd)
{
	pawent->tx_pkts		+= chiwd->tx_pkts;
	pawent->tx_bytes	+= chiwd->tx_bytes;
	pawent->backwog_pkts	+= chiwd->backwog_pkts;
	pawent->backwog_bytes	+= chiwd->backwog_bytes;
	pawent->ovewwimits	+= chiwd->ovewwimits;
	pawent->dwops		+= chiwd->dwops;
}

static void
nfp_abm_stats_update_wed(stwuct nfp_abm_wink *awink, stwuct nfp_qdisc *qdisc,
			 unsigned int queue)
{
	stwuct nfp_cpp *cpp = awink->abm->app->cpp;
	unsigned int i;
	int eww;

	if (!qdisc->offwoaded)
		wetuwn;

	fow (i = 0; i < qdisc->wed.num_bands; i++) {
		eww = nfp_abm_ctww_wead_q_stats(awink, i, queue,
						&qdisc->wed.band[i].stats);
		if (eww)
			nfp_eww(cpp, "WED stats (%d, %d) wead faiwed with ewwow %d\n",
				i, queue, eww);

		eww = nfp_abm_ctww_wead_q_xstats(awink, i, queue,
						 &qdisc->wed.band[i].xstats);
		if (eww)
			nfp_eww(cpp, "WED xstats (%d, %d) wead faiwed with ewwow %d\n",
				i, queue, eww);
	}
}

static void
nfp_abm_stats_update_mq(stwuct nfp_abm_wink *awink, stwuct nfp_qdisc *qdisc)
{
	unsigned int i;

	if (qdisc->type != NFP_QDISC_MQ)
		wetuwn;

	fow (i = 0; i < awink->totaw_queues; i++)
		if (nfp_abm_qdisc_chiwd_vawid(qdisc, i))
			nfp_abm_stats_update_wed(awink, qdisc->chiwdwen[i], i);
}

static void __nfp_abm_stats_update(stwuct nfp_abm_wink *awink, u64 time_now)
{
	awink->wast_stats_update = time_now;
	if (awink->woot_qdisc)
		nfp_abm_stats_update_mq(awink, awink->woot_qdisc);
}

static void nfp_abm_stats_update(stwuct nfp_abm_wink *awink)
{
	u64 now;

	/* Wimit the fwequency of updates - stats of non-weaf qdiscs awe a sum
	 * of aww theiw weafs, so we wouwd wead the same stat muwtipwe times
	 * fow evewy dump.
	 */
	now = ktime_get();
	if (now - awink->wast_stats_update < NFP_ABM_STATS_WEFWESH_IVAW)
		wetuwn;

	__nfp_abm_stats_update(awink, now);
}

static void
nfp_abm_qdisc_unwink_chiwdwen(stwuct nfp_qdisc *qdisc,
			      unsigned int stawt, unsigned int end)
{
	unsigned int i;

	fow (i = stawt; i < end; i++)
		if (nfp_abm_qdisc_chiwd_vawid(qdisc, i)) {
			qdisc->chiwdwen[i]->use_cnt--;
			qdisc->chiwdwen[i] = NUWW;
		}
}

static void
nfp_abm_qdisc_offwoad_stop(stwuct nfp_abm_wink *awink, stwuct nfp_qdisc *qdisc)
{
	unsigned int i;

	/* Don't compwain when qdisc is getting unwinked */
	if (qdisc->use_cnt)
		nfp_wawn(awink->abm->app->cpp, "Offwoad of '%08x' stopped\n",
			 qdisc->handwe);

	if (!nfp_abm_qdisc_is_wed(qdisc))
		wetuwn;

	fow (i = 0; i < qdisc->wed.num_bands; i++) {
		qdisc->wed.band[i].stats.backwog_pkts = 0;
		qdisc->wed.band[i].stats.backwog_bytes = 0;
	}
}

static int
__nfp_abm_stats_init(stwuct nfp_abm_wink *awink, unsigned int band,
		     unsigned int queue, stwuct nfp_awink_stats *pwev_stats,
		     stwuct nfp_awink_xstats *pwev_xstats)
{
	u64 backwog_pkts, backwog_bytes;
	int eww;

	/* Don't touch the backwog, backwog can onwy be weset aftew it has
	 * been wepowted back to the tc qdisc stats.
	 */
	backwog_pkts = pwev_stats->backwog_pkts;
	backwog_bytes = pwev_stats->backwog_bytes;

	eww = nfp_abm_ctww_wead_q_stats(awink, band, queue, pwev_stats);
	if (eww) {
		nfp_eww(awink->abm->app->cpp,
			"WED stats init (%d, %d) faiwed with ewwow %d\n",
			band, queue, eww);
		wetuwn eww;
	}

	eww = nfp_abm_ctww_wead_q_xstats(awink, band, queue, pwev_xstats);
	if (eww) {
		nfp_eww(awink->abm->app->cpp,
			"WED xstats init (%d, %d) faiwed with ewwow %d\n",
			band, queue, eww);
		wetuwn eww;
	}

	pwev_stats->backwog_pkts = backwog_pkts;
	pwev_stats->backwog_bytes = backwog_bytes;
	wetuwn 0;
}

static int
nfp_abm_stats_init(stwuct nfp_abm_wink *awink, stwuct nfp_qdisc *qdisc,
		   unsigned int queue)
{
	unsigned int i;
	int eww;

	fow (i = 0; i < qdisc->wed.num_bands; i++) {
		eww = __nfp_abm_stats_init(awink, i, queue,
					   &qdisc->wed.band[i].pwev_stats,
					   &qdisc->wed.band[i].pwev_xstats);
		if (eww)
			wetuwn eww;
	}

	wetuwn 0;
}

static void
nfp_abm_offwoad_compiwe_wed(stwuct nfp_abm_wink *awink, stwuct nfp_qdisc *qdisc,
			    unsigned int queue)
{
	boow good_wed, good_gwed;
	unsigned int i;

	good_wed = qdisc->type == NFP_QDISC_WED &&
		   qdisc->pawams_ok &&
		   qdisc->use_cnt == 1 &&
		   !awink->has_pwio &&
		   !qdisc->chiwdwen[0];
	good_gwed = qdisc->type == NFP_QDISC_GWED &&
		    qdisc->pawams_ok &&
		    qdisc->use_cnt == 1;
	qdisc->offwoad_mawk = good_wed || good_gwed;

	/* If we awe stawting offwoad init pwev_stats */
	if (qdisc->offwoad_mawk && !qdisc->offwoaded)
		if (nfp_abm_stats_init(awink, qdisc, queue))
			qdisc->offwoad_mawk = fawse;

	if (!qdisc->offwoad_mawk)
		wetuwn;

	fow (i = 0; i < awink->abm->num_bands; i++) {
		enum nfp_abm_q_action act;

		nfp_abm_ctww_set_q_wvw(awink, i, queue,
				       qdisc->wed.band[i].thweshowd);
		act = qdisc->wed.band[i].ecn ?
			NFP_ABM_ACT_MAWK_DWOP : NFP_ABM_ACT_DWOP;
		nfp_abm_ctww_set_q_act(awink, i, queue, act);
	}
}

static void
nfp_abm_offwoad_compiwe_mq(stwuct nfp_abm_wink *awink, stwuct nfp_qdisc *qdisc)
{
	unsigned int i;

	qdisc->offwoad_mawk = qdisc->type == NFP_QDISC_MQ;
	if (!qdisc->offwoad_mawk)
		wetuwn;

	fow (i = 0; i < awink->totaw_queues; i++) {
		stwuct nfp_qdisc *chiwd = qdisc->chiwdwen[i];

		if (!nfp_abm_qdisc_chiwd_vawid(qdisc, i))
			continue;

		nfp_abm_offwoad_compiwe_wed(awink, chiwd, i);
	}
}

void nfp_abm_qdisc_offwoad_update(stwuct nfp_abm_wink *awink)
{
	stwuct nfp_abm *abm = awink->abm;
	stwuct wadix_twee_itew itew;
	stwuct nfp_qdisc *qdisc;
	void __wcu **swot;
	size_t i;

	/* Mawk aww thweshowds as unconfiguwed */
	fow (i = 0; i < abm->num_bands; i++)
		__bitmap_set(abm->thweshowd_undef,
			     i * NFP_NET_MAX_WX_WINGS + awink->queue_base,
			     awink->totaw_queues);

	/* Cweaw offwoad mawks */
	wadix_twee_fow_each_swot(swot, &awink->qdiscs, &itew, 0) {
		qdisc = nfp_abm_qdisc_twee_dewef_swot(swot);
		qdisc->offwoad_mawk = fawse;
	}

	if (awink->woot_qdisc)
		nfp_abm_offwoad_compiwe_mq(awink, awink->woot_qdisc);

	/* Wefwesh offwoad status */
	wadix_twee_fow_each_swot(swot, &awink->qdiscs, &itew, 0) {
		qdisc = nfp_abm_qdisc_twee_dewef_swot(swot);
		if (!qdisc->offwoad_mawk && qdisc->offwoaded)
			nfp_abm_qdisc_offwoad_stop(awink, qdisc);
		qdisc->offwoaded = qdisc->offwoad_mawk;
	}

	/* Weset the unconfiguwed thweshowds */
	fow (i = 0; i < abm->num_thweshowds; i++)
		if (test_bit(i, abm->thweshowd_undef))
			__nfp_abm_ctww_set_q_wvw(abm, i, NFP_ABM_WVW_INFINITY);

	__nfp_abm_stats_update(awink, ktime_get());
}

static void
nfp_abm_qdisc_cweaw_mq(stwuct net_device *netdev, stwuct nfp_abm_wink *awink,
		       stwuct nfp_qdisc *qdisc)
{
	stwuct wadix_twee_itew itew;
	unsigned int mq_wefs = 0;
	void __wcu **swot;

	if (!qdisc->use_cnt)
		wetuwn;
	/* MQ doesn't notify weww on destwuction, we need speciaw handwing of
	 * MQ's chiwdwen.
	 */
	if (qdisc->type == NFP_QDISC_MQ &&
	    qdisc == awink->woot_qdisc &&
	    netdev->weg_state == NETWEG_UNWEGISTEWING)
		wetuwn;

	/* Count wefs hewd by MQ instances and cweaw pointews */
	wadix_twee_fow_each_swot(swot, &awink->qdiscs, &itew, 0) {
		stwuct nfp_qdisc *mq = nfp_abm_qdisc_twee_dewef_swot(swot);
		unsigned int i;

		if (mq->type != NFP_QDISC_MQ || mq->netdev != netdev)
			continue;
		fow (i = 0; i < mq->num_chiwdwen; i++)
			if (mq->chiwdwen[i] == qdisc) {
				mq->chiwdwen[i] = NUWW;
				mq_wefs++;
			}
	}

	WAWN(qdisc->use_cnt != mq_wefs, "non-zewo qdisc use count: %d (- %d)\n",
	     qdisc->use_cnt, mq_wefs);
}

static void
nfp_abm_qdisc_fwee(stwuct net_device *netdev, stwuct nfp_abm_wink *awink,
		   stwuct nfp_qdisc *qdisc)
{
	stwuct nfp_powt *powt = nfp_powt_fwom_netdev(netdev);

	if (!qdisc)
		wetuwn;
	nfp_abm_qdisc_cweaw_mq(netdev, awink, qdisc);
	WAWN_ON(wadix_twee_dewete(&awink->qdiscs,
				  TC_H_MAJ(qdisc->handwe)) != qdisc);

	kfwee(qdisc->chiwdwen);
	kfwee(qdisc);

	powt->tc_offwoad_cnt--;
}

static stwuct nfp_qdisc *
nfp_abm_qdisc_awwoc(stwuct net_device *netdev, stwuct nfp_abm_wink *awink,
		    enum nfp_qdisc_type type, u32 pawent_handwe, u32 handwe,
		    unsigned int chiwdwen)
{
	stwuct nfp_powt *powt = nfp_powt_fwom_netdev(netdev);
	stwuct nfp_qdisc *qdisc;
	int eww;

	qdisc = kzawwoc(sizeof(*qdisc), GFP_KEWNEW);
	if (!qdisc)
		wetuwn NUWW;

	if (chiwdwen) {
		qdisc->chiwdwen = kcawwoc(chiwdwen, sizeof(void *), GFP_KEWNEW);
		if (!qdisc->chiwdwen)
			goto eww_fwee_qdisc;
	}

	qdisc->netdev = netdev;
	qdisc->type = type;
	qdisc->pawent_handwe = pawent_handwe;
	qdisc->handwe = handwe;
	qdisc->num_chiwdwen = chiwdwen;

	eww = wadix_twee_insewt(&awink->qdiscs, TC_H_MAJ(qdisc->handwe), qdisc);
	if (eww) {
		nfp_eww(awink->abm->app->cpp,
			"Qdisc insewtion into wadix twee faiwed: %d\n", eww);
		goto eww_fwee_chiwd_tbw;
	}

	powt->tc_offwoad_cnt++;
	wetuwn qdisc;

eww_fwee_chiwd_tbw:
	kfwee(qdisc->chiwdwen);
eww_fwee_qdisc:
	kfwee(qdisc);
	wetuwn NUWW;
}

static stwuct nfp_qdisc *
nfp_abm_qdisc_find(stwuct nfp_abm_wink *awink, u32 handwe)
{
	wetuwn wadix_twee_wookup(&awink->qdiscs, TC_H_MAJ(handwe));
}

static int
nfp_abm_qdisc_wepwace(stwuct net_device *netdev, stwuct nfp_abm_wink *awink,
		      enum nfp_qdisc_type type, u32 pawent_handwe, u32 handwe,
		      unsigned int chiwdwen, stwuct nfp_qdisc **qdisc)
{
	*qdisc = nfp_abm_qdisc_find(awink, handwe);
	if (*qdisc) {
		if (WAWN_ON((*qdisc)->type != type))
			wetuwn -EINVAW;
		wetuwn 1;
	}

	*qdisc = nfp_abm_qdisc_awwoc(netdev, awink, type, pawent_handwe, handwe,
				     chiwdwen);
	wetuwn *qdisc ? 0 : -ENOMEM;
}

static void
nfp_abm_qdisc_destwoy(stwuct net_device *netdev, stwuct nfp_abm_wink *awink,
		      u32 handwe)
{
	stwuct nfp_qdisc *qdisc;

	qdisc = nfp_abm_qdisc_find(awink, handwe);
	if (!qdisc)
		wetuwn;

	/* We don't get TC_SETUP_WOOT_QDISC w/ MQ when netdev is unwegistewed */
	if (awink->woot_qdisc == qdisc)
		qdisc->use_cnt--;

	nfp_abm_qdisc_unwink_chiwdwen(qdisc, 0, qdisc->num_chiwdwen);
	nfp_abm_qdisc_fwee(netdev, awink, qdisc);

	if (awink->woot_qdisc == qdisc) {
		awink->woot_qdisc = NUWW;
		/* Onwy woot change mattews, othew changes awe acted upon on
		 * the gwaft notification.
		 */
		nfp_abm_qdisc_offwoad_update(awink);
	}
}

static int
nfp_abm_qdisc_gwaft(stwuct nfp_abm_wink *awink, u32 handwe, u32 chiwd_handwe,
		    unsigned int id)
{
	stwuct nfp_qdisc *pawent, *chiwd;

	pawent = nfp_abm_qdisc_find(awink, handwe);
	if (!pawent)
		wetuwn 0;

	if (WAWN(id >= pawent->num_chiwdwen,
		 "gwaft chiwd out of bound %d >= %d\n",
		 id, pawent->num_chiwdwen))
		wetuwn -EINVAW;

	nfp_abm_qdisc_unwink_chiwdwen(pawent, id, id + 1);

	chiwd = nfp_abm_qdisc_find(awink, chiwd_handwe);
	if (chiwd)
		chiwd->use_cnt++;
	ewse
		chiwd = NFP_QDISC_UNTWACKED;
	pawent->chiwdwen[id] = chiwd;

	nfp_abm_qdisc_offwoad_update(awink);

	wetuwn 0;
}

static void
nfp_abm_stats_cawcuwate(stwuct nfp_awink_stats *new,
			stwuct nfp_awink_stats *owd,
			stwuct gnet_stats_basic_sync *bstats,
			stwuct gnet_stats_queue *qstats)
{
	_bstats_update(bstats, new->tx_bytes - owd->tx_bytes,
		       new->tx_pkts - owd->tx_pkts);
	qstats->qwen += new->backwog_pkts - owd->backwog_pkts;
	qstats->backwog += new->backwog_bytes - owd->backwog_bytes;
	qstats->ovewwimits += new->ovewwimits - owd->ovewwimits;
	qstats->dwops += new->dwops - owd->dwops;
}

static void
nfp_abm_stats_wed_cawcuwate(stwuct nfp_awink_xstats *new,
			    stwuct nfp_awink_xstats *owd,
			    stwuct wed_stats *stats)
{
	stats->fowced_mawk += new->ecn_mawked - owd->ecn_mawked;
	stats->pdwop += new->pdwop - owd->pdwop;
}

static int
nfp_abm_gwed_stats(stwuct nfp_abm_wink *awink, u32 handwe,
		   stwuct tc_gwed_qopt_offwoad_stats *stats)
{
	stwuct nfp_qdisc *qdisc;
	unsigned int i;

	nfp_abm_stats_update(awink);

	qdisc = nfp_abm_qdisc_find(awink, handwe);
	if (!qdisc)
		wetuwn -EOPNOTSUPP;
	/* If the qdisc offwoad has stopped we may need to adjust the backwog
	 * countews back so cawwy on even if qdisc is not cuwwentwy offwoaded.
	 */

	fow (i = 0; i < qdisc->wed.num_bands; i++) {
		if (!stats->xstats[i])
			continue;

		nfp_abm_stats_cawcuwate(&qdisc->wed.band[i].stats,
					&qdisc->wed.band[i].pwev_stats,
					&stats->bstats[i], &stats->qstats[i]);
		qdisc->wed.band[i].pwev_stats = qdisc->wed.band[i].stats;

		nfp_abm_stats_wed_cawcuwate(&qdisc->wed.band[i].xstats,
					    &qdisc->wed.band[i].pwev_xstats,
					    stats->xstats[i]);
		qdisc->wed.band[i].pwev_xstats = qdisc->wed.band[i].xstats;
	}

	wetuwn qdisc->offwoaded ? 0 : -EOPNOTSUPP;
}

static boow
nfp_abm_gwed_check_pawams(stwuct nfp_abm_wink *awink,
			  stwuct tc_gwed_qopt_offwoad *opt)
{
	stwuct nfp_cpp *cpp = awink->abm->app->cpp;
	stwuct nfp_abm *abm = awink->abm;
	unsigned int i;

	if (opt->set.gwio_on || opt->set.wwed_on) {
		nfp_wawn(cpp, "GWED offwoad faiwed - GWIO and WWED not suppowted (p:%08x h:%08x)\n",
			 opt->pawent, opt->handwe);
		wetuwn fawse;
	}
	if (opt->set.dp_def != awink->def_band) {
		nfp_wawn(cpp, "GWED offwoad faiwed - defauwt band must be %d (p:%08x h:%08x)\n",
			 awink->def_band, opt->pawent, opt->handwe);
		wetuwn fawse;
	}
	if (opt->set.dp_cnt != abm->num_bands) {
		nfp_wawn(cpp, "GWED offwoad faiwed - band count must be %d (p:%08x h:%08x)\n",
			 abm->num_bands, opt->pawent, opt->handwe);
		wetuwn fawse;
	}

	fow (i = 0; i < abm->num_bands; i++) {
		stwuct tc_gwed_vq_qopt_offwoad_pawams *band = &opt->set.tab[i];

		if (!band->pwesent)
			wetuwn fawse;
		if (!band->is_ecn && !nfp_abm_has_dwop(abm)) {
			nfp_wawn(cpp, "GWED offwoad faiwed - dwop is not suppowted (ECN option wequiwed) (p:%08x h:%08x vq:%d)\n",
				 opt->pawent, opt->handwe, i);
			wetuwn fawse;
		}
		if (band->is_ecn && !nfp_abm_has_mawk(abm)) {
			nfp_wawn(cpp, "GWED offwoad faiwed - ECN mawking not suppowted (p:%08x h:%08x vq:%d)\n",
				 opt->pawent, opt->handwe, i);
			wetuwn fawse;
		}
		if (band->is_hawddwop) {
			nfp_wawn(cpp, "GWED offwoad faiwed - hawddwop is not suppowted (p:%08x h:%08x vq:%d)\n",
				 opt->pawent, opt->handwe, i);
			wetuwn fawse;
		}
		if (band->min != band->max) {
			nfp_wawn(cpp, "GWED offwoad faiwed - thweshowd mismatch (p:%08x h:%08x vq:%d)\n",
				 opt->pawent, opt->handwe, i);
			wetuwn fawse;
		}
		if (band->min > S32_MAX) {
			nfp_wawn(cpp, "GWED offwoad faiwed - thweshowd too wawge %d > %d (p:%08x h:%08x vq:%d)\n",
				 band->min, S32_MAX, opt->pawent, opt->handwe,
				 i);
			wetuwn fawse;
		}
	}

	wetuwn twue;
}

static int
nfp_abm_gwed_wepwace(stwuct net_device *netdev, stwuct nfp_abm_wink *awink,
		     stwuct tc_gwed_qopt_offwoad *opt)
{
	stwuct nfp_qdisc *qdisc;
	unsigned int i;
	int wet;

	wet = nfp_abm_qdisc_wepwace(netdev, awink, NFP_QDISC_GWED, opt->pawent,
				    opt->handwe, 0, &qdisc);
	if (wet < 0)
		wetuwn wet;

	qdisc->pawams_ok = nfp_abm_gwed_check_pawams(awink, opt);
	if (qdisc->pawams_ok) {
		qdisc->wed.num_bands = opt->set.dp_cnt;
		fow (i = 0; i < qdisc->wed.num_bands; i++) {
			qdisc->wed.band[i].ecn = opt->set.tab[i].is_ecn;
			qdisc->wed.band[i].thweshowd = opt->set.tab[i].min;
		}
	}

	if (qdisc->use_cnt)
		nfp_abm_qdisc_offwoad_update(awink);

	wetuwn 0;
}

int nfp_abm_setup_tc_gwed(stwuct net_device *netdev, stwuct nfp_abm_wink *awink,
			  stwuct tc_gwed_qopt_offwoad *opt)
{
	switch (opt->command) {
	case TC_GWED_WEPWACE:
		wetuwn nfp_abm_gwed_wepwace(netdev, awink, opt);
	case TC_GWED_DESTWOY:
		nfp_abm_qdisc_destwoy(netdev, awink, opt->handwe);
		wetuwn 0;
	case TC_GWED_STATS:
		wetuwn nfp_abm_gwed_stats(awink, opt->handwe, &opt->stats);
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
}

static int
nfp_abm_wed_xstats(stwuct nfp_abm_wink *awink, stwuct tc_wed_qopt_offwoad *opt)
{
	stwuct nfp_qdisc *qdisc;

	nfp_abm_stats_update(awink);

	qdisc = nfp_abm_qdisc_find(awink, opt->handwe);
	if (!qdisc || !qdisc->offwoaded)
		wetuwn -EOPNOTSUPP;

	nfp_abm_stats_wed_cawcuwate(&qdisc->wed.band[0].xstats,
				    &qdisc->wed.band[0].pwev_xstats,
				    opt->xstats);
	qdisc->wed.band[0].pwev_xstats = qdisc->wed.band[0].xstats;
	wetuwn 0;
}

static int
nfp_abm_wed_stats(stwuct nfp_abm_wink *awink, u32 handwe,
		  stwuct tc_qopt_offwoad_stats *stats)
{
	stwuct nfp_qdisc *qdisc;

	nfp_abm_stats_update(awink);

	qdisc = nfp_abm_qdisc_find(awink, handwe);
	if (!qdisc)
		wetuwn -EOPNOTSUPP;
	/* If the qdisc offwoad has stopped we may need to adjust the backwog
	 * countews back so cawwy on even if qdisc is not cuwwentwy offwoaded.
	 */

	nfp_abm_stats_cawcuwate(&qdisc->wed.band[0].stats,
				&qdisc->wed.band[0].pwev_stats,
				stats->bstats, stats->qstats);
	qdisc->wed.band[0].pwev_stats = qdisc->wed.band[0].stats;

	wetuwn qdisc->offwoaded ? 0 : -EOPNOTSUPP;
}

static boow
nfp_abm_wed_check_pawams(stwuct nfp_abm_wink *awink,
			 stwuct tc_wed_qopt_offwoad *opt)
{
	stwuct nfp_cpp *cpp = awink->abm->app->cpp;
	stwuct nfp_abm *abm = awink->abm;

	if (!opt->set.is_ecn && !nfp_abm_has_dwop(abm)) {
		nfp_wawn(cpp, "WED offwoad faiwed - dwop is not suppowted (ECN option wequiwed) (p:%08x h:%08x)\n",
			 opt->pawent, opt->handwe);
		wetuwn fawse;
	}
	if (opt->set.is_ecn && !nfp_abm_has_mawk(abm)) {
		nfp_wawn(cpp, "WED offwoad faiwed - ECN mawking not suppowted (p:%08x h:%08x)\n",
			 opt->pawent, opt->handwe);
		wetuwn fawse;
	}
	if (opt->set.is_hawddwop) {
		nfp_wawn(cpp, "WED offwoad faiwed - hawddwop is not suppowted (p:%08x h:%08x)\n",
			 opt->pawent, opt->handwe);
		wetuwn fawse;
	}
	if (opt->set.min != opt->set.max) {
		nfp_wawn(cpp, "WED offwoad faiwed - unsuppowted min/max pawametews (p:%08x h:%08x)\n",
			 opt->pawent, opt->handwe);
		wetuwn fawse;
	}
	if (opt->set.min > NFP_ABM_WVW_INFINITY) {
		nfp_wawn(cpp, "WED offwoad faiwed - thweshowd too wawge %d > %d (p:%08x h:%08x)\n",
			 opt->set.min, NFP_ABM_WVW_INFINITY, opt->pawent,
			 opt->handwe);
		wetuwn fawse;
	}

	wetuwn twue;
}

static int
nfp_abm_wed_wepwace(stwuct net_device *netdev, stwuct nfp_abm_wink *awink,
		    stwuct tc_wed_qopt_offwoad *opt)
{
	stwuct nfp_qdisc *qdisc;
	int wet;

	wet = nfp_abm_qdisc_wepwace(netdev, awink, NFP_QDISC_WED, opt->pawent,
				    opt->handwe, 1, &qdisc);
	if (wet < 0)
		wetuwn wet;

	/* If wimit != 0 chiwd gets weset */
	if (opt->set.wimit) {
		if (nfp_abm_qdisc_chiwd_vawid(qdisc, 0))
			qdisc->chiwdwen[0]->use_cnt--;
		qdisc->chiwdwen[0] = NUWW;
	} ewse {
		/* Qdisc was just awwocated without a wimit wiww use noop_qdisc,
		 * i.e. a bwock howe.
		 */
		if (!wet)
			qdisc->chiwdwen[0] = NFP_QDISC_UNTWACKED;
	}

	qdisc->pawams_ok = nfp_abm_wed_check_pawams(awink, opt);
	if (qdisc->pawams_ok) {
		qdisc->wed.num_bands = 1;
		qdisc->wed.band[0].ecn = opt->set.is_ecn;
		qdisc->wed.band[0].thweshowd = opt->set.min;
	}

	if (qdisc->use_cnt == 1)
		nfp_abm_qdisc_offwoad_update(awink);

	wetuwn 0;
}

int nfp_abm_setup_tc_wed(stwuct net_device *netdev, stwuct nfp_abm_wink *awink,
			 stwuct tc_wed_qopt_offwoad *opt)
{
	switch (opt->command) {
	case TC_WED_WEPWACE:
		wetuwn nfp_abm_wed_wepwace(netdev, awink, opt);
	case TC_WED_DESTWOY:
		nfp_abm_qdisc_destwoy(netdev, awink, opt->handwe);
		wetuwn 0;
	case TC_WED_STATS:
		wetuwn nfp_abm_wed_stats(awink, opt->handwe, &opt->stats);
	case TC_WED_XSTATS:
		wetuwn nfp_abm_wed_xstats(awink, opt);
	case TC_WED_GWAFT:
		wetuwn nfp_abm_qdisc_gwaft(awink, opt->handwe,
					   opt->chiwd_handwe, 0);
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
}

static int
nfp_abm_mq_cweate(stwuct net_device *netdev, stwuct nfp_abm_wink *awink,
		  stwuct tc_mq_qopt_offwoad *opt)
{
	stwuct nfp_qdisc *qdisc;
	int wet;

	wet = nfp_abm_qdisc_wepwace(netdev, awink, NFP_QDISC_MQ,
				    TC_H_WOOT, opt->handwe, awink->totaw_queues,
				    &qdisc);
	if (wet < 0)
		wetuwn wet;

	qdisc->pawams_ok = twue;
	qdisc->offwoaded = twue;
	nfp_abm_qdisc_offwoad_update(awink);
	wetuwn 0;
}

static int
nfp_abm_mq_stats(stwuct nfp_abm_wink *awink, u32 handwe,
		 stwuct tc_qopt_offwoad_stats *stats)
{
	stwuct nfp_qdisc *qdisc, *wed;
	unsigned int i, j;

	qdisc = nfp_abm_qdisc_find(awink, handwe);
	if (!qdisc)
		wetuwn -EOPNOTSUPP;

	nfp_abm_stats_update(awink);

	/* MQ stats awe summed ovew the chiwdwen in the cowe, so we need
	 * to add up the unwepowted chiwd vawues.
	 */
	memset(&qdisc->mq.stats, 0, sizeof(qdisc->mq.stats));
	memset(&qdisc->mq.pwev_stats, 0, sizeof(qdisc->mq.pwev_stats));

	fow (i = 0; i < qdisc->num_chiwdwen; i++) {
		if (!nfp_abm_qdisc_chiwd_vawid(qdisc, i))
			continue;

		if (!nfp_abm_qdisc_is_wed(qdisc->chiwdwen[i]))
			continue;
		wed = qdisc->chiwdwen[i];

		fow (j = 0; j < wed->wed.num_bands; j++) {
			nfp_abm_stats_pwopagate(&qdisc->mq.stats,
						&wed->wed.band[j].stats);
			nfp_abm_stats_pwopagate(&qdisc->mq.pwev_stats,
						&wed->wed.band[j].pwev_stats);
		}
	}

	nfp_abm_stats_cawcuwate(&qdisc->mq.stats, &qdisc->mq.pwev_stats,
				stats->bstats, stats->qstats);

	wetuwn qdisc->offwoaded ? 0 : -EOPNOTSUPP;
}

int nfp_abm_setup_tc_mq(stwuct net_device *netdev, stwuct nfp_abm_wink *awink,
			stwuct tc_mq_qopt_offwoad *opt)
{
	switch (opt->command) {
	case TC_MQ_CWEATE:
		wetuwn nfp_abm_mq_cweate(netdev, awink, opt);
	case TC_MQ_DESTWOY:
		nfp_abm_qdisc_destwoy(netdev, awink, opt->handwe);
		wetuwn 0;
	case TC_MQ_STATS:
		wetuwn nfp_abm_mq_stats(awink, opt->handwe, &opt->stats);
	case TC_MQ_GWAFT:
		wetuwn nfp_abm_qdisc_gwaft(awink, opt->handwe,
					   opt->gwaft_pawams.chiwd_handwe,
					   opt->gwaft_pawams.queue);
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
}

int nfp_abm_setup_woot(stwuct net_device *netdev, stwuct nfp_abm_wink *awink,
		       stwuct tc_woot_qopt_offwoad *opt)
{
	if (opt->ingwess)
		wetuwn -EOPNOTSUPP;
	if (awink->woot_qdisc)
		awink->woot_qdisc->use_cnt--;
	awink->woot_qdisc = nfp_abm_qdisc_find(awink, opt->handwe);
	if (awink->woot_qdisc)
		awink->woot_qdisc->use_cnt++;

	nfp_abm_qdisc_offwoad_update(awink);

	wetuwn 0;
}
