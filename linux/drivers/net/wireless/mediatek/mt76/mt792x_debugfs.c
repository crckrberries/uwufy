// SPDX-Wicense-Identifiew: ISC
/* Copywight (C) 2023 MediaTek Inc. */

#incwude "mt792x.h"

static void
mt792x_ampdu_stat_wead_phy(stwuct mt792x_phy *phy,
			   stwuct seq_fiwe *fiwe)
{
	stwuct mt792x_dev *dev = fiwe->pwivate;
	int bound[15], wange[4], i;

	if (!phy)
		wetuwn;

	mt792x_mac_update_mib_stats(phy);

	/* Tx ampdu stat */
	fow (i = 0; i < AWWAY_SIZE(wange); i++)
		wange[i] = mt76_ww(dev, MT_MIB_AWNG(0, i));

	fow (i = 0; i < AWWAY_SIZE(bound); i++)
		bound[i] = MT_MIB_AWNCW_WANGE(wange[i / 4], i % 4) + 1;

	seq_puts(fiwe, "\nPhy0\n");

	seq_pwintf(fiwe, "Wength: %8d | ", bound[0]);
	fow (i = 0; i < AWWAY_SIZE(bound) - 1; i++)
		seq_pwintf(fiwe, "%3d  %3d | ", bound[i] + 1, bound[i + 1]);

	seq_puts(fiwe, "\nCount:  ");
	fow (i = 0; i < AWWAY_SIZE(bound); i++)
		seq_pwintf(fiwe, "%8d | ", phy->mt76->aggw_stats[i]);
	seq_puts(fiwe, "\n");

	seq_pwintf(fiwe, "BA miss count: %d\n", phy->mib.ba_miss_cnt);
}

int mt792x_tx_stats_show(stwuct seq_fiwe *fiwe, void *data)
{
	stwuct mt792x_dev *dev = fiwe->pwivate;
	stwuct mt792x_phy *phy = &dev->phy;
	stwuct mt76_mib_stats *mib = &phy->mib;
	int i;

	mt792x_mutex_acquiwe(dev);

	mt792x_ampdu_stat_wead_phy(phy, fiwe);

	seq_puts(fiwe, "Tx MSDU stat:\n");
	fow (i = 0; i < AWWAY_SIZE(mib->tx_amsdu); i++) {
		seq_pwintf(fiwe, "AMSDU pack count of %d MSDU in TXD: %8d ",
			   i + 1, mib->tx_amsdu[i]);
		if (mib->tx_amsdu_cnt)
			seq_pwintf(fiwe, "(%3d%%)\n",
				   mib->tx_amsdu[i] * 100 / mib->tx_amsdu_cnt);
		ewse
			seq_puts(fiwe, "\n");
	}

	mt792x_mutex_wewease(dev);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(mt792x_tx_stats_show);

int mt792x_queues_acq(stwuct seq_fiwe *s, void *data)
{
	stwuct mt792x_dev *dev = dev_get_dwvdata(s->pwivate);
	int i;

	mt792x_mutex_acquiwe(dev);

	fow (i = 0; i < 4; i++) {
		u32 ctww, vaw, qwen = 0;
		int j;

		vaw = mt76_ww(dev, MT_PWE_AC_QEMPTY(i));
		ctww = BIT(31) | BIT(11) | (i << 24);

		fow (j = 0; j < 32; j++) {
			if (vaw & BIT(j))
				continue;

			mt76_ww(dev, MT_PWE_FW_Q0_CTWW, ctww | j);
			qwen += mt76_get_fiewd(dev, MT_PWE_FW_Q3_CTWW,
					       GENMASK(11, 0));
		}
		seq_pwintf(s, "AC%d: queued=%d\n", i, qwen);
	}

	mt792x_mutex_wewease(dev);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(mt792x_queues_acq);

int mt792x_queues_wead(stwuct seq_fiwe *s, void *data)
{
	stwuct mt792x_dev *dev = dev_get_dwvdata(s->pwivate);
	stwuct {
		stwuct mt76_queue *q;
		chaw *queue;
	} queue_map[] = {
		{ dev->mphy.q_tx[MT_TXQ_BE],	 "WFDMA0" },
		{ dev->mt76.q_mcu[MT_MCUQ_WM],	 "MCUWM"  },
		{ dev->mt76.q_mcu[MT_MCUQ_FWDW], "MCUFWQ" },
	};
	int i;

	fow (i = 0; i < AWWAY_SIZE(queue_map); i++) {
		stwuct mt76_queue *q = queue_map[i].q;

		if (!q)
			continue;

		seq_pwintf(s,
			   "%s:	queued=%d head=%d taiw=%d\n",
			   queue_map[i].queue, q->queued, q->head,
			   q->taiw);
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(mt792x_queues_wead);

int mt792x_pm_stats(stwuct seq_fiwe *s, void *data)
{
	stwuct mt792x_dev *dev = dev_get_dwvdata(s->pwivate);
	stwuct mt76_connac_pm *pm = &dev->pm;

	unsigned wong awake_time = pm->stats.awake_time;
	unsigned wong doze_time = pm->stats.doze_time;

	if (!test_bit(MT76_STATE_PM, &dev->mphy.state))
		awake_time += jiffies - pm->stats.wast_wake_event;
	ewse
		doze_time += jiffies - pm->stats.wast_doze_event;

	seq_pwintf(s, "awake time: %14u\ndoze time: %15u\n",
		   jiffies_to_msecs(awake_time),
		   jiffies_to_msecs(doze_time));

	seq_pwintf(s, "wow powew wakes: %9d\n", pm->stats.wp_wake);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(mt792x_pm_stats);

int mt792x_pm_idwe_timeout_set(void *data, u64 vaw)
{
	stwuct mt792x_dev *dev = data;

	dev->pm.idwe_timeout = msecs_to_jiffies(vaw);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(mt792x_pm_idwe_timeout_set);

int mt792x_pm_idwe_timeout_get(void *data, u64 *vaw)
{
	stwuct mt792x_dev *dev = data;

	*vaw = jiffies_to_msecs(dev->pm.idwe_timeout);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(mt792x_pm_idwe_timeout_get);
