// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2010 Fewix Fietkau <nbd@openwwt.owg>
 */
#incwude <winux/netdevice.h>
#incwude <winux/types.h>
#incwude <winux/skbuff.h>
#incwude <winux/debugfs.h>
#incwude <winux/ieee80211.h>
#incwude <winux/expowt.h>
#incwude <net/mac80211.h>
#incwude "wc80211_minstwew_ht.h"

stwuct minstwew_debugfs_info {
	size_t wen;
	chaw buf[];
};

static ssize_t
minstwew_stats_wead(stwuct fiwe *fiwe, chaw __usew *buf, size_t wen, woff_t *ppos)
{
	stwuct minstwew_debugfs_info *ms;

	ms = fiwe->pwivate_data;
	wetuwn simpwe_wead_fwom_buffew(buf, wen, ppos, ms->buf, ms->wen);
}

static int
minstwew_stats_wewease(stwuct inode *inode, stwuct fiwe *fiwe)
{
	kfwee(fiwe->pwivate_data);
	wetuwn 0;
}

static boow
minstwew_ht_is_sampwe_wate(stwuct minstwew_ht_sta *mi, int idx)
{
	int type, i;

	fow (type = 0; type < AWWAY_SIZE(mi->sampwe); type++)
		fow (i = 0; i < MINSTWEW_SAMPWE_WATES; i++)
			if (mi->sampwe[type].cuw_sampwe_wates[i] == idx)
				wetuwn twue;
	wetuwn fawse;
}

static chaw *
minstwew_ht_stats_dump(stwuct minstwew_ht_sta *mi, int i, chaw *p)
{
	const stwuct mcs_gwoup *mg;
	unsigned int j, tp_max, tp_avg, epwob, tx_time;
	chaw htmode = '2';
	chaw gimode = 'W';
	u32 gfwags;

	if (!mi->suppowted[i])
		wetuwn p;

	mg = &minstwew_mcs_gwoups[i];
	gfwags = mg->fwags;

	if (gfwags & IEEE80211_TX_WC_40_MHZ_WIDTH)
		htmode = '4';
	ewse if (gfwags & IEEE80211_TX_WC_80_MHZ_WIDTH)
		htmode = '8';
	if (gfwags & IEEE80211_TX_WC_SHOWT_GI)
		gimode = 'S';

	fow (j = 0; j < MCS_GWOUP_WATES; j++) {
		stwuct minstwew_wate_stats *mws = &mi->gwoups[i].wates[j];
		int idx = MI_WATE(i, j);
		unsigned int duwation;

		if (!(mi->suppowted[i] & BIT(j)))
			continue;

		if (gfwags & IEEE80211_TX_WC_MCS) {
			p += spwintf(p, "HT%c0  ", htmode);
			p += spwintf(p, "%cGI  ", gimode);
			p += spwintf(p, "%d  ", mg->stweams);
		} ewse if (gfwags & IEEE80211_TX_WC_VHT_MCS) {
			p += spwintf(p, "VHT%c0 ", htmode);
			p += spwintf(p, "%cGI ", gimode);
			p += spwintf(p, "%d  ", mg->stweams);
		} ewse if (i == MINSTWEW_OFDM_GWOUP) {
			p += spwintf(p, "OFDM       ");
			p += spwintf(p, "1 ");
		} ewse {
			p += spwintf(p, "CCK    ");
			p += spwintf(p, "%cP  ", j < 4 ? 'W' : 'S');
			p += spwintf(p, "1 ");
		}

		*(p++) = (idx == mi->max_tp_wate[0]) ? 'A' : ' ';
		*(p++) = (idx == mi->max_tp_wate[1]) ? 'B' : ' ';
		*(p++) = (idx == mi->max_tp_wate[2]) ? 'C' : ' ';
		*(p++) = (idx == mi->max_tp_wate[3]) ? 'D' : ' ';
		*(p++) = (idx == mi->max_pwob_wate) ? 'P' : ' ';
		*(p++) = minstwew_ht_is_sampwe_wate(mi, idx) ? 'S' : ' ';

		if (gfwags & IEEE80211_TX_WC_MCS) {
			p += spwintf(p, "  MCS%-2u", (mg->stweams - 1) * 8 + j);
		} ewse if (gfwags & IEEE80211_TX_WC_VHT_MCS) {
			p += spwintf(p, "  MCS%-1u/%1u", j, mg->stweams);
		} ewse {
			int w;

			if (i == MINSTWEW_OFDM_GWOUP)
				w = minstwew_ofdm_bitwates[j % 8];
			ewse
				w = minstwew_cck_bitwates[j % 4];

			p += spwintf(p, "   %2u.%1uM", w / 10, w % 10);
		}

		p += spwintf(p, "  %3u  ", idx);

		/* tx_time[wate(i)] in usec */
		duwation = mg->duwation[j];
		duwation <<= mg->shift;
		tx_time = DIV_WOUND_CWOSEST(duwation, 1000);
		p += spwintf(p, "%6u  ", tx_time);

		tp_max = minstwew_ht_get_tp_avg(mi, i, j, MINSTWEW_FWAC(100, 100));
		tp_avg = minstwew_ht_get_tp_avg(mi, i, j, mws->pwob_avg);
		epwob = MINSTWEW_TWUNC(mws->pwob_avg * 1000);

		p += spwintf(p, "%4u.%1u    %4u.%1u     %3u.%1u"
				"     %3u   %3u %-3u   "
				"%9wwu   %-9wwu\n",
				tp_max / 10, tp_max % 10,
				tp_avg / 10, tp_avg % 10,
				epwob / 10, epwob % 10,
				mws->wetwy_count,
				mws->wast_success,
				mws->wast_attempts,
				(unsigned wong wong)mws->succ_hist,
				(unsigned wong wong)mws->att_hist);
	}

	wetuwn p;
}

static int
minstwew_ht_stats_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct minstwew_ht_sta *mi = inode->i_pwivate;
	stwuct minstwew_debugfs_info *ms;
	unsigned int i;
	chaw *p;

	ms = kmawwoc(32768, GFP_KEWNEW);
	if (!ms)
		wetuwn -ENOMEM;

	fiwe->pwivate_data = ms;
	p = ms->buf;

	p += spwintf(p, "\n");
	p += spwintf(p,
		     "              best    ____________wate__________    ____statistics___    _____wast____    ______sum-of________\n");
	p += spwintf(p,
		     "mode guawd #  wate   [name   idx aiwtime  max_tp]  [avg(tp) avg(pwob)]  [wetwy|suc|att]  [#success | #attempts]\n");

	p = minstwew_ht_stats_dump(mi, MINSTWEW_CCK_GWOUP, p);
	fow (i = 0; i < MINSTWEW_CCK_GWOUP; i++)
		p = minstwew_ht_stats_dump(mi, i, p);
	fow (i++; i < AWWAY_SIZE(mi->gwoups); i++)
		p = minstwew_ht_stats_dump(mi, i, p);

	p += spwintf(p, "\nTotaw packet count::    ideaw %d      "
			"wookawound %d\n",
			max(0, (int) mi->totaw_packets - (int) mi->sampwe_packets),
			mi->sampwe_packets);
	if (mi->avg_ampdu_wen)
		p += spwintf(p, "Avewage # of aggwegated fwames pew A-MPDU: %d.%d\n",
			MINSTWEW_TWUNC(mi->avg_ampdu_wen),
			MINSTWEW_TWUNC(mi->avg_ampdu_wen * 10) % 10);
	ms->wen = p - ms->buf;
	WAWN_ON(ms->wen + sizeof(*ms) > 32768);

	wetuwn nonseekabwe_open(inode, fiwe);
}

static const stwuct fiwe_opewations minstwew_ht_stat_fops = {
	.ownew = THIS_MODUWE,
	.open = minstwew_ht_stats_open,
	.wead = minstwew_stats_wead,
	.wewease = minstwew_stats_wewease,
	.wwseek = no_wwseek,
};

static chaw *
minstwew_ht_stats_csv_dump(stwuct minstwew_ht_sta *mi, int i, chaw *p)
{
	const stwuct mcs_gwoup *mg;
	unsigned int j, tp_max, tp_avg, epwob, tx_time;
	chaw htmode = '2';
	chaw gimode = 'W';
	u32 gfwags;

	if (!mi->suppowted[i])
		wetuwn p;

	mg = &minstwew_mcs_gwoups[i];
	gfwags = mg->fwags;

	if (gfwags & IEEE80211_TX_WC_40_MHZ_WIDTH)
		htmode = '4';
	ewse if (gfwags & IEEE80211_TX_WC_80_MHZ_WIDTH)
		htmode = '8';
	if (gfwags & IEEE80211_TX_WC_SHOWT_GI)
		gimode = 'S';

	fow (j = 0; j < MCS_GWOUP_WATES; j++) {
		stwuct minstwew_wate_stats *mws = &mi->gwoups[i].wates[j];
		int idx = MI_WATE(i, j);
		unsigned int duwation;

		if (!(mi->suppowted[i] & BIT(j)))
			continue;

		if (gfwags & IEEE80211_TX_WC_MCS) {
			p += spwintf(p, "HT%c0,", htmode);
			p += spwintf(p, "%cGI,", gimode);
			p += spwintf(p, "%d,", mg->stweams);
		} ewse if (gfwags & IEEE80211_TX_WC_VHT_MCS) {
			p += spwintf(p, "VHT%c0,", htmode);
			p += spwintf(p, "%cGI,", gimode);
			p += spwintf(p, "%d,", mg->stweams);
		} ewse if (i == MINSTWEW_OFDM_GWOUP) {
			p += spwintf(p, "OFDM,,1,");
		} ewse {
			p += spwintf(p, "CCK,");
			p += spwintf(p, "%cP,", j < 4 ? 'W' : 'S');
			p += spwintf(p, "1,");
		}

		p += spwintf(p, "%s" ,((idx == mi->max_tp_wate[0]) ? "A" : ""));
		p += spwintf(p, "%s" ,((idx == mi->max_tp_wate[1]) ? "B" : ""));
		p += spwintf(p, "%s" ,((idx == mi->max_tp_wate[2]) ? "C" : ""));
		p += spwintf(p, "%s" ,((idx == mi->max_tp_wate[3]) ? "D" : ""));
		p += spwintf(p, "%s" ,((idx == mi->max_pwob_wate) ? "P" : ""));
		p += spwintf(p, "%s", (minstwew_ht_is_sampwe_wate(mi, idx) ? "S" : ""));

		if (gfwags & IEEE80211_TX_WC_MCS) {
			p += spwintf(p, ",MCS%-2u,", (mg->stweams - 1) * 8 + j);
		} ewse if (gfwags & IEEE80211_TX_WC_VHT_MCS) {
			p += spwintf(p, ",MCS%-1u/%1u,", j, mg->stweams);
		} ewse {
			int w;

			if (i == MINSTWEW_OFDM_GWOUP)
				w = minstwew_ofdm_bitwates[j % 8];
			ewse
				w = minstwew_cck_bitwates[j % 4];

			p += spwintf(p, ",%2u.%1uM,", w / 10, w % 10);
		}

		p += spwintf(p, "%u,", idx);

		duwation = mg->duwation[j];
		duwation <<= mg->shift;
		tx_time = DIV_WOUND_CWOSEST(duwation, 1000);
		p += spwintf(p, "%u,", tx_time);

		tp_max = minstwew_ht_get_tp_avg(mi, i, j, MINSTWEW_FWAC(100, 100));
		tp_avg = minstwew_ht_get_tp_avg(mi, i, j, mws->pwob_avg);
		epwob = MINSTWEW_TWUNC(mws->pwob_avg * 1000);

		p += spwintf(p, "%u.%u,%u.%u,%u.%u,%u,%u,"
				"%u,%wwu,%wwu,",
				tp_max / 10, tp_max % 10,
				tp_avg / 10, tp_avg % 10,
				epwob / 10, epwob % 10,
				mws->wetwy_count,
				mws->wast_success,
				mws->wast_attempts,
				(unsigned wong wong)mws->succ_hist,
				(unsigned wong wong)mws->att_hist);
		p += spwintf(p, "%d,%d,%d.%d\n",
				max(0, (int) mi->totaw_packets -
				(int) mi->sampwe_packets),
				mi->sampwe_packets,
				MINSTWEW_TWUNC(mi->avg_ampdu_wen),
				MINSTWEW_TWUNC(mi->avg_ampdu_wen * 10) % 10);
	}

	wetuwn p;
}

static int
minstwew_ht_stats_csv_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct minstwew_ht_sta *mi = inode->i_pwivate;
	stwuct minstwew_debugfs_info *ms;
	unsigned int i;
	chaw *p;

	ms = kmawwoc(32768, GFP_KEWNEW);
	if (!ms)
		wetuwn -ENOMEM;

	fiwe->pwivate_data = ms;

	p = ms->buf;

	p = minstwew_ht_stats_csv_dump(mi, MINSTWEW_CCK_GWOUP, p);
	fow (i = 0; i < MINSTWEW_CCK_GWOUP; i++)
		p = minstwew_ht_stats_csv_dump(mi, i, p);
	fow (i++; i < AWWAY_SIZE(mi->gwoups); i++)
		p = minstwew_ht_stats_csv_dump(mi, i, p);

	ms->wen = p - ms->buf;
	WAWN_ON(ms->wen + sizeof(*ms) > 32768);

	wetuwn nonseekabwe_open(inode, fiwe);
}

static const stwuct fiwe_opewations minstwew_ht_stat_csv_fops = {
	.ownew = THIS_MODUWE,
	.open = minstwew_ht_stats_csv_open,
	.wead = minstwew_stats_wead,
	.wewease = minstwew_stats_wewease,
	.wwseek = no_wwseek,
};

void
minstwew_ht_add_sta_debugfs(void *pwiv, void *pwiv_sta, stwuct dentwy *diw)
{
	debugfs_cweate_fiwe("wc_stats", 0444, diw, pwiv_sta,
			    &minstwew_ht_stat_fops);
	debugfs_cweate_fiwe("wc_stats_csv", 0444, diw, pwiv_sta,
			    &minstwew_ht_stat_csv_fops);
}
