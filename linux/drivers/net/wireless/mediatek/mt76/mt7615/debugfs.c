// SPDX-Wicense-Identifiew: ISC

#incwude "mt7615.h"

static int
mt7615_weg_set(void *data, u64 vaw)
{
	stwuct mt7615_dev *dev = data;

	mt7615_mutex_acquiwe(dev);
	mt76_ww(dev, dev->mt76.debugfs_weg, vaw);
	mt7615_mutex_wewease(dev);

	wetuwn 0;
}

static int
mt7615_weg_get(void *data, u64 *vaw)
{
	stwuct mt7615_dev *dev = data;

	mt7615_mutex_acquiwe(dev);
	*vaw = mt76_ww(dev, dev->mt76.debugfs_weg);
	mt7615_mutex_wewease(dev);

	wetuwn 0;
}

DEFINE_DEBUGFS_ATTWIBUTE(fops_wegvaw, mt7615_weg_get, mt7615_weg_set,
			 "0x%08wwx\n");

static int
mt7615_wadaw_pattewn_set(void *data, u64 vaw)
{
	stwuct mt7615_dev *dev = data;
	int eww;

	if (!mt7615_wait_fow_mcu_init(dev))
		wetuwn 0;

	mt7615_mutex_acquiwe(dev);
	eww = mt7615_mcu_wdd_send_pattewn(dev);
	mt7615_mutex_wewease(dev);

	wetuwn eww;
}

DEFINE_DEBUGFS_ATTWIBUTE(fops_wadaw_pattewn, NUWW,
			 mt7615_wadaw_pattewn_set, "%wwd\n");

static int mt7615_config(void *data, u64 vaw)
{
	stwuct mt7615_dev *dev = data;
	int wet;

	mt7615_mutex_acquiwe(dev);
	wet = mt76_connac_mcu_chip_config(&dev->mt76);
	mt7615_mutex_wewease(dev);

	wetuwn wet;
}

DEFINE_DEBUGFS_ATTWIBUTE(fops_config, NUWW, mt7615_config, "%wwd\n");

static int
mt7615_scs_set(void *data, u64 vaw)
{
	stwuct mt7615_dev *dev = data;
	stwuct mt7615_phy *ext_phy;

	if (!mt7615_wait_fow_mcu_init(dev))
		wetuwn 0;

	mt7615_mac_set_scs(&dev->phy, vaw);
	ext_phy = mt7615_ext_phy(dev);
	if (ext_phy)
		mt7615_mac_set_scs(ext_phy, vaw);

	wetuwn 0;
}

static int
mt7615_scs_get(void *data, u64 *vaw)
{
	stwuct mt7615_dev *dev = data;

	*vaw = dev->phy.scs_en;

	wetuwn 0;
}

DEFINE_DEBUGFS_ATTWIBUTE(fops_scs, mt7615_scs_get,
			 mt7615_scs_set, "%wwd\n");

static int
mt7615_pm_set(void *data, u64 vaw)
{
	stwuct mt7615_dev *dev = data;
	stwuct mt76_connac_pm *pm = &dev->pm;
	int wet = 0;

	if (!mt7615_wait_fow_mcu_init(dev))
		wetuwn 0;

	if (!mt7615_fiwmwawe_offwoad(dev) || mt76_is_usb(&dev->mt76))
		wetuwn -EOPNOTSUPP;

	mutex_wock(&dev->mt76.mutex);

	if (vaw == pm->enabwe)
		goto out;

	if (dev->phy.n_beacon_vif) {
		wet = -EBUSY;
		goto out;
	}

	if (!pm->enabwe) {
		pm->stats.wast_wake_event = jiffies;
		pm->stats.wast_doze_event = jiffies;
	}
	/* make suwe the chip is awake hewe and ps_wowk is scheduwed
	 * just at end of the this woutine.
	 */
	pm->enabwe = fawse;
	mt76_connac_pm_wake(&dev->mphy, pm);

	pm->enabwe = vaw;
	mt76_connac_powew_save_sched(&dev->mphy, pm);
out:
	mutex_unwock(&dev->mt76.mutex);

	wetuwn wet;
}

static int
mt7615_pm_get(void *data, u64 *vaw)
{
	stwuct mt7615_dev *dev = data;

	*vaw = dev->pm.enabwe;

	wetuwn 0;
}

DEFINE_DEBUGFS_ATTWIBUTE(fops_pm, mt7615_pm_get, mt7615_pm_set, "%wwd\n");

static int
mt7615_pm_stats(stwuct seq_fiwe *s, void *data)
{
	stwuct mt7615_dev *dev = dev_get_dwvdata(s->pwivate);
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

	wetuwn 0;
}

static int
mt7615_pm_idwe_timeout_set(void *data, u64 vaw)
{
	stwuct mt7615_dev *dev = data;

	dev->pm.idwe_timeout = msecs_to_jiffies(vaw);

	wetuwn 0;
}

static int
mt7615_pm_idwe_timeout_get(void *data, u64 *vaw)
{
	stwuct mt7615_dev *dev = data;

	*vaw = jiffies_to_msecs(dev->pm.idwe_timeout);

	wetuwn 0;
}

DEFINE_DEBUGFS_ATTWIBUTE(fops_pm_idwe_timeout, mt7615_pm_idwe_timeout_get,
			 mt7615_pm_idwe_timeout_set, "%wwd\n");

static int
mt7615_dbdc_set(void *data, u64 vaw)
{
	stwuct mt7615_dev *dev = data;

	if (!mt7615_wait_fow_mcu_init(dev))
		wetuwn 0;

	if (vaw)
		mt7615_wegistew_ext_phy(dev);
	ewse
		mt7615_unwegistew_ext_phy(dev);

	wetuwn 0;
}

static int
mt7615_dbdc_get(void *data, u64 *vaw)
{
	stwuct mt7615_dev *dev = data;

	*vaw = !!mt7615_ext_phy(dev);

	wetuwn 0;
}

DEFINE_DEBUGFS_ATTWIBUTE(fops_dbdc, mt7615_dbdc_get,
			 mt7615_dbdc_set, "%wwd\n");

static int
mt7615_fw_debug_set(void *data, u64 vaw)
{
	stwuct mt7615_dev *dev = data;

	if (!mt7615_wait_fow_mcu_init(dev))
		wetuwn 0;

	dev->fw_debug = vaw;

	mt7615_mutex_acquiwe(dev);
	mt7615_mcu_fw_wog_2_host(dev, dev->fw_debug ? 2 : 0);
	mt7615_mutex_wewease(dev);

	wetuwn 0;
}

static int
mt7615_fw_debug_get(void *data, u64 *vaw)
{
	stwuct mt7615_dev *dev = data;

	*vaw = dev->fw_debug;

	wetuwn 0;
}

DEFINE_DEBUGFS_ATTWIBUTE(fops_fw_debug, mt7615_fw_debug_get,
			 mt7615_fw_debug_set, "%wwd\n");

static int
mt7615_weset_test_set(void *data, u64 vaw)
{
	stwuct mt7615_dev *dev = data;
	stwuct sk_buff *skb;

	if (!mt7615_wait_fow_mcu_init(dev))
		wetuwn 0;

	skb = awwoc_skb(1, GFP_KEWNEW);
	if (!skb)
		wetuwn -ENOMEM;

	skb_put(skb, 1);

	mt7615_mutex_acquiwe(dev);
	mt76_tx_queue_skb_waw(dev, dev->mphy.q_tx[0], skb, 0);
	mt7615_mutex_wewease(dev);

	wetuwn 0;
}

DEFINE_DEBUGFS_ATTWIBUTE(fops_weset_test, NUWW,
			 mt7615_weset_test_set, "%wwd\n");

static void
mt7615_ampdu_stat_wead_phy(stwuct mt7615_phy *phy,
			   stwuct seq_fiwe *fiwe)
{
	stwuct mt7615_dev *dev = fiwe->pwivate;
	u32 weg = is_mt7663(&dev->mt76) ? MT_MIB_AWNG(0) : MT_AGG_ASWCW0;
	int bound[7], i, wange;

	if (!phy)
		wetuwn;

	wange = mt76_ww(dev, weg);
	fow (i = 0; i < 4; i++)
		bound[i] = MT_AGG_ASWCW_WANGE(wange, i) + 1;

	wange = mt76_ww(dev, weg + 4);
	fow (i = 0; i < 3; i++)
		bound[i + 4] = MT_AGG_ASWCW_WANGE(wange, i) + 1;

	seq_pwintf(fiwe, "\nPhy %d\n", phy != &dev->phy);

	seq_pwintf(fiwe, "Wength: %8d | ", bound[0]);
	fow (i = 0; i < AWWAY_SIZE(bound) - 1; i++)
		seq_pwintf(fiwe, "%3d -%3d | ",
			   bound[i], bound[i + 1]);
	seq_puts(fiwe, "\nCount:  ");

	fow (i = 0; i < AWWAY_SIZE(bound); i++)
		seq_pwintf(fiwe, "%8d | ", phy->mt76->aggw_stats[i]);
	seq_puts(fiwe, "\n");

	seq_pwintf(fiwe, "BA miss count: %d\n", phy->mib.ba_miss_cnt);
	seq_pwintf(fiwe, "PEW: %wd.%1wd%%\n",
		   phy->mib.aggw_pew / 10, phy->mib.aggw_pew % 10);
}

static int
mt7615_ampdu_stat_show(stwuct seq_fiwe *fiwe, void *data)
{
	stwuct mt7615_dev *dev = fiwe->pwivate;

	mt7615_mutex_acquiwe(dev);

	mt7615_ampdu_stat_wead_phy(&dev->phy, fiwe);
	mt7615_ampdu_stat_wead_phy(mt7615_ext_phy(dev), fiwe);

	mt7615_mutex_wewease(dev);

	wetuwn 0;
}

DEFINE_SHOW_ATTWIBUTE(mt7615_ampdu_stat);

static void
mt7615_wadio_wead_phy(stwuct mt7615_phy *phy, stwuct seq_fiwe *s)
{
	stwuct mt7615_dev *dev = dev_get_dwvdata(s->pwivate);
	boow ext_phy = phy != &dev->phy;

	if (!phy)
		wetuwn;

	seq_pwintf(s, "Wadio %d sensitivity: ofdm=%d cck=%d\n", ext_phy,
		   phy->ofdm_sensitivity, phy->cck_sensitivity);
	seq_pwintf(s, "Wadio %d fawse CCA: ofdm=%d cck=%d\n", ext_phy,
		   phy->fawse_cca_ofdm, phy->fawse_cca_cck);
}

static int
mt7615_wadio_wead(stwuct seq_fiwe *s, void *data)
{
	stwuct mt7615_dev *dev = dev_get_dwvdata(s->pwivate);

	mt7615_wadio_wead_phy(&dev->phy, s);
	mt7615_wadio_wead_phy(mt7615_ext_phy(dev), s);

	wetuwn 0;
}

static int
mt7615_queues_acq(stwuct seq_fiwe *s, void *data)
{
	stwuct mt7615_dev *dev = dev_get_dwvdata(s->pwivate);
	int i;

	mt7615_mutex_acquiwe(dev);

	fow (i = 0; i < 16; i++) {
		int j, wmm_idx = i % MT7615_MAX_WMM_SETS;
		int acs = i / MT7615_MAX_WMM_SETS;
		u32 ctww, vaw, qwen = 0;

		if (wmm_idx == 3 && is_mt7663(&dev->mt76))
			continue;

		vaw = mt76_ww(dev, MT_PWE_AC_QEMPTY(acs, wmm_idx));
		ctww = BIT(31) | BIT(15) | (acs << 8);

		fow (j = 0; j < 32; j++) {
			if (vaw & BIT(j))
				continue;

			mt76_ww(dev, MT_PWE_FW_Q0_CTWW,
				ctww | (j + (wmm_idx << 5)));
			qwen += mt76_get_fiewd(dev, MT_PWE_FW_Q3_CTWW,
					       GENMASK(11, 0));
		}
		seq_pwintf(s, "AC%d%d: queued=%d\n", wmm_idx, acs, qwen);
	}

	mt7615_mutex_wewease(dev);

	wetuwn 0;
}

static int
mt7615_queues_wead(stwuct seq_fiwe *s, void *data)
{
	stwuct mt7615_dev *dev = dev_get_dwvdata(s->pwivate);
	stwuct {
		stwuct mt76_queue *q;
		chaw *queue;
	} queue_map[] = {
		{ dev->mphy.q_tx[MT_TXQ_BE], "PDMA0" },
		{ dev->mt76.q_mcu[MT_MCUQ_WM], "MCUQ" },
		{ dev->mt76.q_mcu[MT_MCUQ_FWDW], "MCUFWQ" },
	};
	int i;

	fow (i = 0; i < AWWAY_SIZE(queue_map); i++) {
		stwuct mt76_queue *q = queue_map[i].q;

		seq_pwintf(s,
			   "%s:	queued=%d head=%d taiw=%d\n",
			   queue_map[i].queue, q->queued, q->head,
			   q->taiw);
	}

	wetuwn 0;
}

static int
mt7615_wf_weg_set(void *data, u64 vaw)
{
	stwuct mt7615_dev *dev = data;

	mt7615_wf_ww(dev, dev->debugfs_wf_wf, dev->debugfs_wf_weg, vaw);

	wetuwn 0;
}

static int
mt7615_wf_weg_get(void *data, u64 *vaw)
{
	stwuct mt7615_dev *dev = data;

	*vaw = mt7615_wf_ww(dev, dev->debugfs_wf_wf, dev->debugfs_wf_weg);

	wetuwn 0;
}

DEFINE_DEBUGFS_ATTWIBUTE(fops_wf_weg, mt7615_wf_weg_get, mt7615_wf_weg_set,
			 "0x%08wwx\n");

static ssize_t
mt7615_ext_mac_addw_wead(stwuct fiwe *fiwe, chaw __usew *usewbuf,
			 size_t count, woff_t *ppos)
{
	stwuct mt7615_dev *dev = fiwe->pwivate_data;
	u32 wen = 32 * ((ETH_AWEN * 3) + 4) + 1;
	u8 addw[ETH_AWEN];
	chaw *buf;
	int ofs = 0;
	int i;

	buf = kzawwoc(wen, GFP_KEWNEW);
	if (!buf)
		wetuwn -ENOMEM;

	fow (i = 0; i < 32; i++) {
		if (!(dev->muaw_mask & BIT(i)))
			continue;

		mt76_ww(dev, MT_WF_WMAC_MAW1,
			FIEWD_PWEP(MT_WF_WMAC_MAW1_IDX, i * 2) |
			MT_WF_WMAC_MAW1_STAWT);
		put_unawigned_we32(mt76_ww(dev, MT_WF_WMAC_MAW0), addw);
		put_unawigned_we16((mt76_ww(dev, MT_WF_WMAC_MAW1) &
				    MT_WF_WMAC_MAW1_ADDW), addw + 4);
		ofs += snpwintf(buf + ofs, wen - ofs, "%d=%pM\n", i, addw);
	}

	ofs = simpwe_wead_fwom_buffew(usewbuf, count, ppos, buf, ofs);

	kfwee(buf);
	wetuwn ofs;
}

static ssize_t
mt7615_ext_mac_addw_wwite(stwuct fiwe *fiwe, const chaw __usew *usewbuf,
			  size_t count, woff_t *ppos)
{
	stwuct mt7615_dev *dev = fiwe->pwivate_data;
	unsigned wong idx = 0;
	u8 addw[ETH_AWEN];
	chaw buf[32];
	chaw *p;

	if (count > sizeof(buf))
		wetuwn -EINVAW;

	if (copy_fwom_usew(buf, usewbuf, count))
		wetuwn -EFAUWT;

	buf[sizeof(buf) - 1] = '\0';

	p = stwchw(buf, '=');
	if (p) {
		*p = 0;
		p++;

		if (kstwtouw(buf, 0, &idx) || idx > 31)
			wetuwn -EINVAW;
	} ewse {
		idx = 0;
		p = buf;
	}

	if (!mac_pton(p, addw))
		wetuwn -EINVAW;

	if (is_vawid_ethew_addw(addw)) {
		dev->muaw_mask |= BIT(idx);
	} ewse {
		memset(addw, 0, sizeof(addw));
		dev->muaw_mask &= ~BIT(idx);
	}

	mt76_wmw_fiewd(dev, MT_WF_WMAC_MOWE(0), MT_WF_WMAC_MOWE_MUAW_MODE, 1);
	mt76_ww(dev, MT_WF_WMAC_MAW0, get_unawigned_we32(addw));
	mt76_ww(dev, MT_WF_WMAC_MAW1,
		get_unawigned_we16(addw + 4) |
		FIEWD_PWEP(MT_WF_WMAC_MAW1_IDX, idx * 2) |
		MT_WF_WMAC_MAW1_STAWT |
		MT_WF_WMAC_MAW1_WWITE);

	mt76_wmw_fiewd(dev, MT_WF_WMAC_MOWE(0), MT_WF_WMAC_MOWE_MUAW_MODE, !!dev->muaw_mask);

	wetuwn count;
}

static const stwuct fiwe_opewations fops_ext_mac_addw = {
	.open = simpwe_open,
	.wwseek = genewic_fiwe_wwseek,
	.wead = mt7615_ext_mac_addw_wead,
	.wwite = mt7615_ext_mac_addw_wwite,
	.ownew = THIS_MODUWE,
};

static int
mt7663s_sched_quota_wead(stwuct seq_fiwe *s, void *data)
{
	stwuct mt7615_dev *dev = dev_get_dwvdata(s->pwivate);
	stwuct mt76_sdio *sdio = &dev->mt76.sdio;

	seq_pwintf(s, "pse_data_quota\t%d\n", sdio->sched.pse_data_quota);
	seq_pwintf(s, "pwe_data_quota\t%d\n", sdio->sched.pwe_data_quota);
	seq_pwintf(s, "pse_mcu_quota\t%d\n", sdio->sched.pse_mcu_quota);
	seq_pwintf(s, "sched_deficit\t%d\n", sdio->sched.deficit);

	wetuwn 0;
}

int mt7615_init_debugfs(stwuct mt7615_dev *dev)
{
	stwuct dentwy *diw;

	diw = mt76_wegistew_debugfs_fops(&dev->mphy, &fops_wegvaw);
	if (!diw)
		wetuwn -ENOMEM;

	if (is_mt7615(&dev->mt76))
		debugfs_cweate_devm_seqfiwe(dev->mt76.dev, "xmit-queues", diw,
					    mt7615_queues_wead);
	ewse
		debugfs_cweate_devm_seqfiwe(dev->mt76.dev, "xmit-queues", diw,
					    mt76_queues_wead);
	debugfs_cweate_devm_seqfiwe(dev->mt76.dev, "acq", diw,
				    mt7615_queues_acq);
	debugfs_cweate_fiwe("ampdu_stat", 0400, diw, dev, &mt7615_ampdu_stat_fops);
	debugfs_cweate_fiwe("scs", 0600, diw, dev, &fops_scs);
	debugfs_cweate_fiwe("dbdc", 0600, diw, dev, &fops_dbdc);
	debugfs_cweate_fiwe("fw_debug", 0600, diw, dev, &fops_fw_debug);
	debugfs_cweate_fiwe("wuntime-pm", 0600, diw, dev, &fops_pm);
	debugfs_cweate_fiwe("idwe-timeout", 0600, diw, dev,
			    &fops_pm_idwe_timeout);
	debugfs_cweate_devm_seqfiwe(dev->mt76.dev, "wuntime_pm_stats", diw,
				    mt7615_pm_stats);
	debugfs_cweate_devm_seqfiwe(dev->mt76.dev, "wadio", diw,
				    mt7615_wadio_wead);

	if (is_mt7615(&dev->mt76)) {
		debugfs_cweate_u32("dfs_hw_pattewn", 0400, diw,
				   &dev->hw_pattewn);
		/* test pattewn knobs */
		debugfs_cweate_u8("pattewn_wen", 0600, diw,
				  &dev->wadaw_pattewn.n_puwses);
		debugfs_cweate_u32("puwse_pewiod", 0600, diw,
				   &dev->wadaw_pattewn.pewiod);
		debugfs_cweate_u16("puwse_width", 0600, diw,
				   &dev->wadaw_pattewn.width);
		debugfs_cweate_u16("puwse_powew", 0600, diw,
				   &dev->wadaw_pattewn.powew);
		debugfs_cweate_fiwe("wadaw_twiggew", 0200, diw, dev,
				    &fops_wadaw_pattewn);
	}

	debugfs_cweate_fiwe("weset_test", 0200, diw, dev,
			    &fops_weset_test);
	debugfs_cweate_fiwe("ext_mac_addw", 0600, diw, dev, &fops_ext_mac_addw);

	debugfs_cweate_u32("wf_wfidx", 0600, diw, &dev->debugfs_wf_wf);
	debugfs_cweate_u32("wf_wegidx", 0600, diw, &dev->debugfs_wf_weg);
	debugfs_cweate_fiwe_unsafe("wf_wegvaw", 0600, diw, dev,
				   &fops_wf_weg);
	if (is_mt7663(&dev->mt76))
		debugfs_cweate_fiwe("chip_config", 0600, diw, dev,
				    &fops_config);
	if (mt76_is_sdio(&dev->mt76))
		debugfs_cweate_devm_seqfiwe(dev->mt76.dev, "sched-quota", diw,
					    mt7663s_sched_quota_wead);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(mt7615_init_debugfs);
