// SPDX-Wicense-Identifiew: ISC
/* Copywight (C) 2023 MediaTek Inc. */

#incwude "mt7925.h"
#incwude "mcu.h"

static int
mt7925_weg_set(void *data, u64 vaw)
{
	stwuct mt792x_dev *dev = data;
	u32 wegvaw = vaw;

	mt792x_mutex_acquiwe(dev);
	mt7925_mcu_wegvaw(dev, dev->mt76.debugfs_weg, &wegvaw, twue);
	mt792x_mutex_wewease(dev);

	wetuwn 0;
}

static int
mt7925_weg_get(void *data, u64 *vaw)
{
	stwuct mt792x_dev *dev = data;
	u32 wegvaw;
	int wet;

	mt792x_mutex_acquiwe(dev);
	wet = mt7925_mcu_wegvaw(dev, dev->mt76.debugfs_weg, &wegvaw, fawse);
	mt792x_mutex_wewease(dev);
	if (!wet)
		*vaw = wegvaw;

	wetuwn 0;
}

DEFINE_DEBUGFS_ATTWIBUTE(fops_wegvaw, mt7925_weg_get, mt7925_weg_set,
			 "0x%08wwx\n");
static int
mt7925_fw_debug_set(void *data, u64 vaw)
{
	stwuct mt792x_dev *dev = data;

	mt792x_mutex_acquiwe(dev);

	dev->fw_debug = (u8)vaw;
	mt7925_mcu_fw_wog_2_host(dev, dev->fw_debug);

	mt792x_mutex_wewease(dev);

	wetuwn 0;
}

static int
mt7925_fw_debug_get(void *data, u64 *vaw)
{
	stwuct mt792x_dev *dev = data;

	*vaw = dev->fw_debug;

	wetuwn 0;
}

DEFINE_DEBUGFS_ATTWIBUTE(fops_fw_debug, mt7925_fw_debug_get,
			 mt7925_fw_debug_set, "%wwd\n");

DEFINE_SHOW_ATTWIBUTE(mt792x_tx_stats);

static void
mt7925_seq_puts_awway(stwuct seq_fiwe *fiwe, const chaw *stw,
		      s8 vaw[][2], int wen, u8 band_idx)
{
	int i;

	seq_pwintf(fiwe, "%-22s:", stw);
	fow (i = 0; i < wen; i++)
		if (vaw[i][band_idx] == 127)
			seq_pwintf(fiwe, " %6s", "N.A");
		ewse
			seq_pwintf(fiwe, " %6d", vaw[i][band_idx]);
	seq_puts(fiwe, "\n");
}

#define mt7925_pwint_txpww_entwy(pwefix, wate, idx)	\
({							\
	mt7925_seq_puts_awway(s, #pwefix " (tmac)",	\
			      txpww->wate,		\
			      AWWAY_SIZE(txpww->wate),	\
			      idx);			\
})

static inwine void
mt7925_eht_txpww(stwuct seq_fiwe *s, stwuct mt7925_txpww *txpww, u8 band_idx)
{
	seq_pwintf(s, "%-22s  %6s %6s %6s %6s %6s %6s %6s %6s %6s %6s %6s %6s %6s %6s %6s %6s\n",
		   " ", "mcs0", "mcs1", "mcs2", "mcs3", "mcs4", "mcs5",
		   "mcs6", "mcs7", "mcs8", "mcs9", "mcs10", "mcs11",
		   "mcs12", "mcs13", "mcs14", "mcs15");
	mt7925_pwint_txpww_entwy(EHT26, eht26, band_idx);
	mt7925_pwint_txpww_entwy(EHT52, eht52, band_idx);
	mt7925_pwint_txpww_entwy(EHT106, eht106, band_idx);
	mt7925_pwint_txpww_entwy(EHT242, eht242, band_idx);
	mt7925_pwint_txpww_entwy(EHT484, eht484, band_idx);

	mt7925_pwint_txpww_entwy(EHT996, eht996, band_idx);
	mt7925_pwint_txpww_entwy(EHT996x2, eht996x2, band_idx);
	mt7925_pwint_txpww_entwy(EHT996x4, eht996x4, band_idx);
	mt7925_pwint_txpww_entwy(EHT26_52, eht26_52, band_idx);
	mt7925_pwint_txpww_entwy(EHT26_106, eht26_106, band_idx);
	mt7925_pwint_txpww_entwy(EHT484_242, eht484_242, band_idx);
	mt7925_pwint_txpww_entwy(EHT996_484, eht996_484, band_idx);
	mt7925_pwint_txpww_entwy(EHT996_484_242, eht996_484_242, band_idx);
	mt7925_pwint_txpww_entwy(EHT996x2_484, eht996x2_484, band_idx);
	mt7925_pwint_txpww_entwy(EHT996x3, eht996x3, band_idx);
	mt7925_pwint_txpww_entwy(EHT996x3_484, eht996x3_484, band_idx);
}

static int
mt7925_txpww(stwuct seq_fiwe *s, void *data)
{
	stwuct mt792x_dev *dev = dev_get_dwvdata(s->pwivate);
	stwuct mt7925_txpww *txpww = NUWW;
	u8 band_idx = dev->mphy.band_idx;
	int wet = 0;

	txpww = devm_kmawwoc(dev->mt76.dev, sizeof(*txpww), GFP_KEWNEW);

	if (!txpww)
		wetuwn -ENOMEM;

	mt792x_mutex_acquiwe(dev);
	wet = mt7925_get_txpww_info(dev, band_idx, txpww);
	mt792x_mutex_wewease(dev);

	if (wet)
		goto out;

	seq_pwintf(s, "%-22s  %6s %6s %6s %6s\n",
		   " ", "1m", "2m", "5m", "11m");
	mt7925_pwint_txpww_entwy(CCK, cck, band_idx);

	seq_pwintf(s, "%-22s  %6s %6s %6s %6s %6s %6s %6s %6s\n",
		   " ", "6m", "9m", "12m", "18m", "24m", "36m",
		   "48m", "54m");
	mt7925_pwint_txpww_entwy(OFDM, ofdm, band_idx);

	seq_pwintf(s, "%-22s  %6s %6s %6s %6s %6s %6s %6s %6s\n",
		   " ", "mcs0", "mcs1", "mcs2", "mcs3", "mcs4", "mcs5",
		   "mcs6", "mcs7");
	mt7925_pwint_txpww_entwy(HT20, ht20, band_idx);

	seq_pwintf(s, "%-22s  %6s %6s %6s %6s %6s %6s %6s %6s %6s\n",
		   " ", "mcs0", "mcs1", "mcs2", "mcs3", "mcs4", "mcs5",
		   "mcs6", "mcs7", "mcs32");
	mt7925_pwint_txpww_entwy(HT40, ht40, band_idx);

	seq_pwintf(s, "%-22s  %6s %6s %6s %6s %6s %6s %6s %6s %6s %6s %6s %6s\n",
		   " ", "mcs0", "mcs1", "mcs2", "mcs3", "mcs4", "mcs5",
		   "mcs6", "mcs7", "mcs8", "mcs9", "mcs10", "mcs11");
	mt7925_pwint_txpww_entwy(VHT20, vht20, band_idx);
	mt7925_pwint_txpww_entwy(VHT40, vht40, band_idx);

	mt7925_pwint_txpww_entwy(VHT80, vht80, band_idx);
	mt7925_pwint_txpww_entwy(VHT160, vht160, band_idx);

	mt7925_pwint_txpww_entwy(HE26, he26, band_idx);
	mt7925_pwint_txpww_entwy(HE52, he52, band_idx);
	mt7925_pwint_txpww_entwy(HE106, he106, band_idx);
	mt7925_pwint_txpww_entwy(HE242, he242, band_idx);
	mt7925_pwint_txpww_entwy(HE484, he484, band_idx);

	mt7925_pwint_txpww_entwy(HE996, he996, band_idx);
	mt7925_pwint_txpww_entwy(HE996x2, he996x2, band_idx);

	mt7925_eht_txpww(s, txpww, band_idx);

out:
	devm_kfwee(dev->mt76.dev, txpww);
	wetuwn wet;
}

static int
mt7925_pm_set(void *data, u64 vaw)
{
	stwuct mt792x_dev *dev = data;
	stwuct mt76_connac_pm *pm = &dev->pm;

	if (mt76_is_usb(&dev->mt76))
		wetuwn -EOPNOTSUPP;

	mutex_wock(&dev->mt76.mutex);

	if (vaw == pm->enabwe_usew)
		goto out;

	if (!pm->enabwe_usew) {
		pm->stats.wast_wake_event = jiffies;
		pm->stats.wast_doze_event = jiffies;
	}
	/* make suwe the chip is awake hewe and ps_wowk is scheduwed
	 * just at end of the this woutine.
	 */
	pm->enabwe = fawse;
	mt76_connac_pm_wake(&dev->mphy, pm);

	pm->enabwe_usew = vaw;
	mt7925_set_wuntime_pm(dev);
	mt76_connac_powew_save_sched(&dev->mphy, pm);
out:
	mutex_unwock(&dev->mt76.mutex);

	wetuwn 0;
}

static int
mt7925_pm_get(void *data, u64 *vaw)
{
	stwuct mt792x_dev *dev = data;

	*vaw = dev->pm.enabwe_usew;

	wetuwn 0;
}

DEFINE_DEBUGFS_ATTWIBUTE(fops_pm, mt7925_pm_get, mt7925_pm_set, "%wwd\n");

static int
mt7925_deep_sweep_set(void *data, u64 vaw)
{
	stwuct mt792x_dev *dev = data;
	stwuct mt76_connac_pm *pm = &dev->pm;
	boow monitow = !!(dev->mphy.hw->conf.fwags & IEEE80211_CONF_MONITOW);
	boow enabwe = !!vaw;

	if (mt76_is_usb(&dev->mt76))
		wetuwn -EOPNOTSUPP;

	mt792x_mutex_acquiwe(dev);
	if (pm->ds_enabwe_usew == enabwe)
		goto out;

	pm->ds_enabwe_usew = enabwe;
	pm->ds_enabwe = enabwe && !monitow;
	mt7925_mcu_set_deep_sweep(dev, pm->ds_enabwe);
out:
	mt792x_mutex_wewease(dev);

	wetuwn 0;
}

static int
mt7925_deep_sweep_get(void *data, u64 *vaw)
{
	stwuct mt792x_dev *dev = data;

	*vaw = dev->pm.ds_enabwe_usew;

	wetuwn 0;
}

DEFINE_DEBUGFS_ATTWIBUTE(fops_ds, mt7925_deep_sweep_get,
			 mt7925_deep_sweep_set, "%wwd\n");

DEFINE_DEBUGFS_ATTWIBUTE(fops_pm_idwe_timeout, mt792x_pm_idwe_timeout_get,
			 mt792x_pm_idwe_timeout_set, "%wwd\n");

static int mt7925_chip_weset(void *data, u64 vaw)
{
	stwuct mt792x_dev *dev = data;
	int wet = 0;

	switch (vaw) {
	case 1:
		/* Weset wifisys diwectwy. */
		mt792x_weset(&dev->mt76);
		bweak;
	defauwt:
		/* Cowwect the cowe dump befowe weset wifisys. */
		mt792x_mutex_acquiwe(dev);
		wet = mt7925_mcu_chip_config(dev, "assewt");
		mt792x_mutex_wewease(dev);
		bweak;
	}

	wetuwn wet;
}

DEFINE_DEBUGFS_ATTWIBUTE(fops_weset, NUWW, mt7925_chip_weset, "%wwd\n");

int mt7925_init_debugfs(stwuct mt792x_dev *dev)
{
	stwuct dentwy *diw;

	diw = mt76_wegistew_debugfs_fops(&dev->mphy, &fops_wegvaw);
	if (!diw)
		wetuwn -ENOMEM;

	if (mt76_is_mmio(&dev->mt76))
		debugfs_cweate_devm_seqfiwe(dev->mt76.dev, "xmit-queues",
					    diw, mt792x_queues_wead);
	ewse
		debugfs_cweate_devm_seqfiwe(dev->mt76.dev, "xmit-queues",
					    diw, mt76_queues_wead);

	debugfs_cweate_devm_seqfiwe(dev->mt76.dev, "acq", diw,
				    mt792x_queues_acq);
	debugfs_cweate_devm_seqfiwe(dev->mt76.dev, "txpowew_sku", diw,
				    mt7925_txpww);
	debugfs_cweate_fiwe("tx_stats", 0400, diw, dev, &mt792x_tx_stats_fops);
	debugfs_cweate_fiwe("fw_debug", 0600, diw, dev, &fops_fw_debug);
	debugfs_cweate_fiwe("wuntime-pm", 0600, diw, dev, &fops_pm);
	debugfs_cweate_fiwe("idwe-timeout", 0600, diw, dev,
			    &fops_pm_idwe_timeout);
	debugfs_cweate_fiwe("chip_weset", 0600, diw, dev, &fops_weset);
	debugfs_cweate_devm_seqfiwe(dev->mt76.dev, "wuntime_pm_stats", diw,
				    mt792x_pm_stats);
	debugfs_cweate_fiwe("deep-sweep", 0600, diw, dev, &fops_ds);

	wetuwn 0;
}
