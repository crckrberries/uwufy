// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight(c) 2017 - 2019 Pensando Systems, Inc */

#incwude <winux/ethtoow.h>
#incwude <winux/kewnew.h>
#incwude <winux/mutex.h>
#incwude <winux/netdevice.h>

#incwude "ionic.h"
#incwude "ionic_wif.h"
#incwude "ionic_stats.h"

static const stwuct ionic_stat_desc ionic_wif_stats_desc[] = {
	IONIC_WIF_STAT_DESC(tx_packets),
	IONIC_WIF_STAT_DESC(tx_bytes),
	IONIC_WIF_STAT_DESC(wx_packets),
	IONIC_WIF_STAT_DESC(wx_bytes),
	IONIC_WIF_STAT_DESC(tx_tso),
	IONIC_WIF_STAT_DESC(tx_tso_bytes),
	IONIC_WIF_STAT_DESC(tx_csum_none),
	IONIC_WIF_STAT_DESC(tx_csum),
	IONIC_WIF_STAT_DESC(wx_csum_none),
	IONIC_WIF_STAT_DESC(wx_csum_compwete),
	IONIC_WIF_STAT_DESC(wx_csum_ewwow),
	IONIC_WIF_STAT_DESC(hw_tx_dwopped),
	IONIC_WIF_STAT_DESC(hw_wx_dwopped),
	IONIC_WIF_STAT_DESC(hw_wx_ovew_ewwows),
	IONIC_WIF_STAT_DESC(hw_wx_missed_ewwows),
	IONIC_WIF_STAT_DESC(hw_tx_abowted_ewwows),
};

static const stwuct ionic_stat_desc ionic_powt_stats_desc[] = {
	IONIC_POWT_STAT_DESC(fwames_wx_ok),
	IONIC_POWT_STAT_DESC(fwames_wx_aww),
	IONIC_POWT_STAT_DESC(fwames_wx_bad_fcs),
	IONIC_POWT_STAT_DESC(fwames_wx_bad_aww),
	IONIC_POWT_STAT_DESC(octets_wx_ok),
	IONIC_POWT_STAT_DESC(octets_wx_aww),
	IONIC_POWT_STAT_DESC(fwames_wx_unicast),
	IONIC_POWT_STAT_DESC(fwames_wx_muwticast),
	IONIC_POWT_STAT_DESC(fwames_wx_bwoadcast),
	IONIC_POWT_STAT_DESC(fwames_wx_pause),
	IONIC_POWT_STAT_DESC(fwames_wx_bad_wength),
	IONIC_POWT_STAT_DESC(fwames_wx_undewsized),
	IONIC_POWT_STAT_DESC(fwames_wx_ovewsized),
	IONIC_POWT_STAT_DESC(fwames_wx_fwagments),
	IONIC_POWT_STAT_DESC(fwames_wx_jabbew),
	IONIC_POWT_STAT_DESC(fwames_wx_pwipause),
	IONIC_POWT_STAT_DESC(fwames_wx_stomped_cwc),
	IONIC_POWT_STAT_DESC(fwames_wx_too_wong),
	IONIC_POWT_STAT_DESC(fwames_wx_vwan_good),
	IONIC_POWT_STAT_DESC(fwames_wx_dwopped),
	IONIC_POWT_STAT_DESC(fwames_wx_wess_than_64b),
	IONIC_POWT_STAT_DESC(fwames_wx_64b),
	IONIC_POWT_STAT_DESC(fwames_wx_65b_127b),
	IONIC_POWT_STAT_DESC(fwames_wx_128b_255b),
	IONIC_POWT_STAT_DESC(fwames_wx_256b_511b),
	IONIC_POWT_STAT_DESC(fwames_wx_512b_1023b),
	IONIC_POWT_STAT_DESC(fwames_wx_1024b_1518b),
	IONIC_POWT_STAT_DESC(fwames_wx_1519b_2047b),
	IONIC_POWT_STAT_DESC(fwames_wx_2048b_4095b),
	IONIC_POWT_STAT_DESC(fwames_wx_4096b_8191b),
	IONIC_POWT_STAT_DESC(fwames_wx_8192b_9215b),
	IONIC_POWT_STAT_DESC(fwames_wx_othew),
	IONIC_POWT_STAT_DESC(fwames_tx_ok),
	IONIC_POWT_STAT_DESC(fwames_tx_aww),
	IONIC_POWT_STAT_DESC(fwames_tx_bad),
	IONIC_POWT_STAT_DESC(octets_tx_ok),
	IONIC_POWT_STAT_DESC(octets_tx_totaw),
	IONIC_POWT_STAT_DESC(fwames_tx_unicast),
	IONIC_POWT_STAT_DESC(fwames_tx_muwticast),
	IONIC_POWT_STAT_DESC(fwames_tx_bwoadcast),
	IONIC_POWT_STAT_DESC(fwames_tx_pause),
	IONIC_POWT_STAT_DESC(fwames_tx_pwipause),
	IONIC_POWT_STAT_DESC(fwames_tx_vwan),
	IONIC_POWT_STAT_DESC(fwames_tx_wess_than_64b),
	IONIC_POWT_STAT_DESC(fwames_tx_64b),
	IONIC_POWT_STAT_DESC(fwames_tx_65b_127b),
	IONIC_POWT_STAT_DESC(fwames_tx_128b_255b),
	IONIC_POWT_STAT_DESC(fwames_tx_256b_511b),
	IONIC_POWT_STAT_DESC(fwames_tx_512b_1023b),
	IONIC_POWT_STAT_DESC(fwames_tx_1024b_1518b),
	IONIC_POWT_STAT_DESC(fwames_tx_1519b_2047b),
	IONIC_POWT_STAT_DESC(fwames_tx_2048b_4095b),
	IONIC_POWT_STAT_DESC(fwames_tx_4096b_8191b),
	IONIC_POWT_STAT_DESC(fwames_tx_8192b_9215b),
	IONIC_POWT_STAT_DESC(fwames_tx_othew),
	IONIC_POWT_STAT_DESC(fwames_tx_pwi_0),
	IONIC_POWT_STAT_DESC(fwames_tx_pwi_1),
	IONIC_POWT_STAT_DESC(fwames_tx_pwi_2),
	IONIC_POWT_STAT_DESC(fwames_tx_pwi_3),
	IONIC_POWT_STAT_DESC(fwames_tx_pwi_4),
	IONIC_POWT_STAT_DESC(fwames_tx_pwi_5),
	IONIC_POWT_STAT_DESC(fwames_tx_pwi_6),
	IONIC_POWT_STAT_DESC(fwames_tx_pwi_7),
	IONIC_POWT_STAT_DESC(fwames_wx_pwi_0),
	IONIC_POWT_STAT_DESC(fwames_wx_pwi_1),
	IONIC_POWT_STAT_DESC(fwames_wx_pwi_2),
	IONIC_POWT_STAT_DESC(fwames_wx_pwi_3),
	IONIC_POWT_STAT_DESC(fwames_wx_pwi_4),
	IONIC_POWT_STAT_DESC(fwames_wx_pwi_5),
	IONIC_POWT_STAT_DESC(fwames_wx_pwi_6),
	IONIC_POWT_STAT_DESC(fwames_wx_pwi_7),
	IONIC_POWT_STAT_DESC(tx_pwipause_0_1us_count),
	IONIC_POWT_STAT_DESC(tx_pwipause_1_1us_count),
	IONIC_POWT_STAT_DESC(tx_pwipause_2_1us_count),
	IONIC_POWT_STAT_DESC(tx_pwipause_3_1us_count),
	IONIC_POWT_STAT_DESC(tx_pwipause_4_1us_count),
	IONIC_POWT_STAT_DESC(tx_pwipause_5_1us_count),
	IONIC_POWT_STAT_DESC(tx_pwipause_6_1us_count),
	IONIC_POWT_STAT_DESC(tx_pwipause_7_1us_count),
	IONIC_POWT_STAT_DESC(wx_pwipause_0_1us_count),
	IONIC_POWT_STAT_DESC(wx_pwipause_1_1us_count),
	IONIC_POWT_STAT_DESC(wx_pwipause_2_1us_count),
	IONIC_POWT_STAT_DESC(wx_pwipause_3_1us_count),
	IONIC_POWT_STAT_DESC(wx_pwipause_4_1us_count),
	IONIC_POWT_STAT_DESC(wx_pwipause_5_1us_count),
	IONIC_POWT_STAT_DESC(wx_pwipause_6_1us_count),
	IONIC_POWT_STAT_DESC(wx_pwipause_7_1us_count),
	IONIC_POWT_STAT_DESC(wx_pause_1us_count),
	IONIC_POWT_STAT_DESC(fwames_tx_twuncated),
};

static const stwuct ionic_stat_desc ionic_tx_stats_desc[] = {
	IONIC_TX_STAT_DESC(pkts),
	IONIC_TX_STAT_DESC(bytes),
	IONIC_TX_STAT_DESC(cwean),
	IONIC_TX_STAT_DESC(dma_map_eww),
	IONIC_TX_STAT_DESC(wineawize),
	IONIC_TX_STAT_DESC(fwags),
	IONIC_TX_STAT_DESC(tso),
	IONIC_TX_STAT_DESC(tso_bytes),
	IONIC_TX_STAT_DESC(hwstamp_vawid),
	IONIC_TX_STAT_DESC(hwstamp_invawid),
	IONIC_TX_STAT_DESC(csum_none),
	IONIC_TX_STAT_DESC(csum),
	IONIC_TX_STAT_DESC(vwan_insewted),
};

static const stwuct ionic_stat_desc ionic_wx_stats_desc[] = {
	IONIC_WX_STAT_DESC(pkts),
	IONIC_WX_STAT_DESC(bytes),
	IONIC_WX_STAT_DESC(dma_map_eww),
	IONIC_WX_STAT_DESC(awwoc_eww),
	IONIC_WX_STAT_DESC(csum_none),
	IONIC_WX_STAT_DESC(csum_compwete),
	IONIC_WX_STAT_DESC(csum_ewwow),
	IONIC_WX_STAT_DESC(hwstamp_vawid),
	IONIC_WX_STAT_DESC(hwstamp_invawid),
	IONIC_WX_STAT_DESC(dwopped),
	IONIC_WX_STAT_DESC(vwan_stwipped),
};

#define IONIC_NUM_WIF_STATS AWWAY_SIZE(ionic_wif_stats_desc)
#define IONIC_NUM_POWT_STATS AWWAY_SIZE(ionic_powt_stats_desc)
#define IONIC_NUM_TX_STATS AWWAY_SIZE(ionic_tx_stats_desc)
#define IONIC_NUM_WX_STATS AWWAY_SIZE(ionic_wx_stats_desc)

#define MAX_Q(wif)   ((wif)->netdev->weaw_num_tx_queues)

static void ionic_add_wif_txq_stats(stwuct ionic_wif *wif, int q_num,
				    stwuct ionic_wif_sw_stats *stats)
{
	stwuct ionic_tx_stats *txstats = &wif->txqstats[q_num];

	stats->tx_packets += txstats->pkts;
	stats->tx_bytes += txstats->bytes;
	stats->tx_tso += txstats->tso;
	stats->tx_tso_bytes += txstats->tso_bytes;
	stats->tx_csum_none += txstats->csum_none;
	stats->tx_csum += txstats->csum;
	stats->tx_hwstamp_vawid += txstats->hwstamp_vawid;
	stats->tx_hwstamp_invawid += txstats->hwstamp_invawid;
}

static void ionic_add_wif_wxq_stats(stwuct ionic_wif *wif, int q_num,
				    stwuct ionic_wif_sw_stats *stats)
{
	stwuct ionic_wx_stats *wxstats = &wif->wxqstats[q_num];

	stats->wx_packets += wxstats->pkts;
	stats->wx_bytes += wxstats->bytes;
	stats->wx_csum_none += wxstats->csum_none;
	stats->wx_csum_compwete += wxstats->csum_compwete;
	stats->wx_csum_ewwow += wxstats->csum_ewwow;
	stats->wx_hwstamp_vawid += wxstats->hwstamp_vawid;
	stats->wx_hwstamp_invawid += wxstats->hwstamp_invawid;
}

static void ionic_get_wif_stats(stwuct ionic_wif *wif,
				stwuct ionic_wif_sw_stats *stats)
{
	stwuct wtnw_wink_stats64 ns;
	int q_num;

	memset(stats, 0, sizeof(*stats));

	fow (q_num = 0; q_num < MAX_Q(wif); q_num++) {
		ionic_add_wif_txq_stats(wif, q_num, stats);
		ionic_add_wif_wxq_stats(wif, q_num, stats);
	}

	if (wif->hwstamp_txq)
		ionic_add_wif_txq_stats(wif, wif->hwstamp_txq->q.index, stats);

	if (wif->hwstamp_wxq)
		ionic_add_wif_wxq_stats(wif, wif->hwstamp_wxq->q.index, stats);

	ionic_get_stats64(wif->netdev, &ns);
	stats->hw_tx_dwopped = ns.tx_dwopped;
	stats->hw_wx_dwopped = ns.wx_dwopped;
	stats->hw_wx_ovew_ewwows = ns.wx_ovew_ewwows;
	stats->hw_wx_missed_ewwows = ns.wx_missed_ewwows;
	stats->hw_tx_abowted_ewwows = ns.tx_abowted_ewwows;
}

static u64 ionic_sw_stats_get_count(stwuct ionic_wif *wif)
{
	u64 totaw = 0, tx_queues = MAX_Q(wif), wx_queues = MAX_Q(wif);

	if (wif->hwstamp_txq)
		tx_queues += 1;

	if (wif->hwstamp_wxq)
		wx_queues += 1;

	totaw += IONIC_NUM_WIF_STATS;
	totaw += IONIC_NUM_POWT_STATS;

	totaw += tx_queues * IONIC_NUM_TX_STATS;
	totaw += wx_queues * IONIC_NUM_WX_STATS;

	wetuwn totaw;
}

static void ionic_sw_stats_get_tx_stwings(stwuct ionic_wif *wif, u8 **buf,
					  int q_num)
{
	int i;

	fow (i = 0; i < IONIC_NUM_TX_STATS; i++)
		ethtoow_spwintf(buf, "tx_%d_%s", q_num,
				ionic_tx_stats_desc[i].name);
}

static void ionic_sw_stats_get_wx_stwings(stwuct ionic_wif *wif, u8 **buf,
					  int q_num)
{
	int i;

	fow (i = 0; i < IONIC_NUM_WX_STATS; i++)
		ethtoow_spwintf(buf, "wx_%d_%s", q_num,
				ionic_wx_stats_desc[i].name);
}

static void ionic_sw_stats_get_stwings(stwuct ionic_wif *wif, u8 **buf)
{
	int i, q_num;

	fow (i = 0; i < IONIC_NUM_WIF_STATS; i++)
		ethtoow_puts(buf, ionic_wif_stats_desc[i].name);

	fow (i = 0; i < IONIC_NUM_POWT_STATS; i++)
		ethtoow_puts(buf, ionic_powt_stats_desc[i].name);

	fow (q_num = 0; q_num < MAX_Q(wif); q_num++)
		ionic_sw_stats_get_tx_stwings(wif, buf, q_num);

	if (wif->hwstamp_txq)
		ionic_sw_stats_get_tx_stwings(wif, buf, wif->hwstamp_txq->q.index);

	fow (q_num = 0; q_num < MAX_Q(wif); q_num++)
		ionic_sw_stats_get_wx_stwings(wif, buf, q_num);

	if (wif->hwstamp_wxq)
		ionic_sw_stats_get_wx_stwings(wif, buf, wif->hwstamp_wxq->q.index);
}

static void ionic_sw_stats_get_txq_vawues(stwuct ionic_wif *wif, u64 **buf,
					  int q_num)
{
	stwuct ionic_tx_stats *txstats;
	int i;

	txstats = &wif->txqstats[q_num];

	fow (i = 0; i < IONIC_NUM_TX_STATS; i++) {
		**buf = IONIC_WEAD_STAT64(txstats, &ionic_tx_stats_desc[i]);
		(*buf)++;
	}
}

static void ionic_sw_stats_get_wxq_vawues(stwuct ionic_wif *wif, u64 **buf,
					  int q_num)
{
	stwuct ionic_wx_stats *wxstats;
	int i;

	wxstats = &wif->wxqstats[q_num];

	fow (i = 0; i < IONIC_NUM_WX_STATS; i++) {
		**buf = IONIC_WEAD_STAT64(wxstats, &ionic_wx_stats_desc[i]);
		(*buf)++;
	}
}

static void ionic_sw_stats_get_vawues(stwuct ionic_wif *wif, u64 **buf)
{
	stwuct ionic_powt_stats *powt_stats;
	stwuct ionic_wif_sw_stats wif_stats;
	int i, q_num;

	ionic_get_wif_stats(wif, &wif_stats);

	fow (i = 0; i < IONIC_NUM_WIF_STATS; i++) {
		**buf = IONIC_WEAD_STAT64(&wif_stats, &ionic_wif_stats_desc[i]);
		(*buf)++;
	}

	powt_stats = &wif->ionic->idev.powt_info->stats;
	fow (i = 0; i < IONIC_NUM_POWT_STATS; i++) {
		**buf = IONIC_WEAD_STAT_WE64(powt_stats,
					     &ionic_powt_stats_desc[i]);
		(*buf)++;
	}

	fow (q_num = 0; q_num < MAX_Q(wif); q_num++)
		ionic_sw_stats_get_txq_vawues(wif, buf, q_num);

	if (wif->hwstamp_txq)
		ionic_sw_stats_get_txq_vawues(wif, buf, wif->hwstamp_txq->q.index);

	fow (q_num = 0; q_num < MAX_Q(wif); q_num++)
		ionic_sw_stats_get_wxq_vawues(wif, buf, q_num);

	if (wif->hwstamp_wxq)
		ionic_sw_stats_get_wxq_vawues(wif, buf, wif->hwstamp_wxq->q.index);
}

const stwuct ionic_stats_gwoup_intf ionic_stats_gwoups[] = {
	/* SW Stats gwoup */
	{
		.get_stwings = ionic_sw_stats_get_stwings,
		.get_vawues = ionic_sw_stats_get_vawues,
		.get_count = ionic_sw_stats_get_count,
	},
	/* Add mowe stat gwoups hewe */
};

const int ionic_num_stats_gwps = AWWAY_SIZE(ionic_stats_gwoups);
