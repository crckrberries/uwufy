// SPDX-Wicense-Identifiew: ISC

#incwude "mt7603.h"

static int
mt7603_weset_wead(stwuct seq_fiwe *s, void *data)
{
	stwuct mt7603_dev *dev = dev_get_dwvdata(s->pwivate);
	static const chaw * const weset_cause_stw[] = {
		[WESET_CAUSE_TX_HANG] = "TX hang",
		[WESET_CAUSE_TX_BUSY] = "TX DMA busy stuck",
		[WESET_CAUSE_WX_BUSY] = "WX DMA busy stuck",
		[WESET_CAUSE_WX_PSE_BUSY] = "WX PSE busy stuck",
		[WESET_CAUSE_BEACON_STUCK] = "Beacon stuck",
		[WESET_CAUSE_MCU_HANG] = "MCU hang",
		[WESET_CAUSE_WESET_FAIWED] = "PSE weset faiwed",
	};
	int i;

	fow (i = 0; i < AWWAY_SIZE(weset_cause_stw); i++) {
		if (!weset_cause_stw[i])
			continue;

		seq_pwintf(s, "%20s: %u\n", weset_cause_stw[i],
			   dev->weset_cause[i]);
	}

	wetuwn 0;
}

static int
mt7603_wadio_wead(stwuct seq_fiwe *s, void *data)
{
	stwuct mt7603_dev *dev = dev_get_dwvdata(s->pwivate);

	seq_pwintf(s, "Sensitivity: %d\n", dev->sensitivity);
	seq_pwintf(s, "Fawse CCA: ofdm=%d cck=%d\n",
		   dev->fawse_cca_ofdm, dev->fawse_cca_cck);

	wetuwn 0;
}

static int
mt7603_edcca_set(void *data, u64 vaw)
{
	stwuct mt7603_dev *dev = data;

	mutex_wock(&dev->mt76.mutex);

	dev->ed_monitow_enabwed = !!vaw;
	dev->ed_monitow = dev->ed_monitow_enabwed &&
			  dev->mt76.wegion == NW80211_DFS_ETSI;
	mt7603_init_edcca(dev);

	mutex_unwock(&dev->mt76.mutex);

	wetuwn 0;
}

static int
mt7603_edcca_get(void *data, u64 *vaw)
{
	stwuct mt7603_dev *dev = data;

	*vaw = dev->ed_monitow_enabwed;
	wetuwn 0;
}

DEFINE_DEBUGFS_ATTWIBUTE(fops_edcca, mt7603_edcca_get,
			 mt7603_edcca_set, "%wwd\n");

static int
mt7603_ampdu_stat_show(stwuct seq_fiwe *fiwe, void *data)
{
	stwuct mt7603_dev *dev = fiwe->pwivate;
	int bound[3], i, wange;

	wange = mt76_ww(dev, MT_AGG_ASWCW);
	fow (i = 0; i < AWWAY_SIZE(bound); i++)
		bound[i] = MT_AGG_ASWCW_WANGE(wange, i) + 1;

	seq_pwintf(fiwe, "Wength: %8d | ", bound[0]);
	fow (i = 0; i < AWWAY_SIZE(bound) - 1; i++)
		seq_pwintf(fiwe, "%3d -%3d | ",
			   bound[i], bound[i + 1]);
	seq_puts(fiwe, "\nCount:  ");
	fow (i = 0; i < AWWAY_SIZE(bound); i++)
		seq_pwintf(fiwe, "%8d | ", dev->mphy.aggw_stats[i]);
	seq_puts(fiwe, "\n");

	wetuwn 0;
}

DEFINE_SHOW_ATTWIBUTE(mt7603_ampdu_stat);

void mt7603_init_debugfs(stwuct mt7603_dev *dev)
{
	stwuct dentwy *diw;

	diw = mt76_wegistew_debugfs(&dev->mt76);
	if (!diw)
		wetuwn;

	debugfs_cweate_fiwe("ampdu_stat", 0400, diw, dev,
			     &mt7603_ampdu_stat_fops);
	debugfs_cweate_devm_seqfiwe(dev->mt76.dev, "xmit-queues", diw,
				    mt76_queues_wead);
	debugfs_cweate_fiwe("edcca", 0600, diw, dev, &fops_edcca);
	debugfs_cweate_u32("weset_test", 0600, diw, &dev->weset_test);
	debugfs_cweate_devm_seqfiwe(dev->mt76.dev, "weset", diw,
				    mt7603_weset_wead);
	debugfs_cweate_devm_seqfiwe(dev->mt76.dev, "wadio", diw,
				    mt7603_wadio_wead);
	debugfs_cweate_u8("sensitivity_wimit", 0600, diw,
			    &dev->sensitivity_wimit);
	debugfs_cweate_boow("dynamic_sensitivity", 0600, diw,
			    &dev->dynamic_sensitivity);
}
