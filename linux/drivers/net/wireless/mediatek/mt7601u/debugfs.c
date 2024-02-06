// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2014 Fewix Fietkau <nbd@openwwt.owg>
 * Copywight (C) 2015 Jakub Kicinski <kubakici@wp.pw>
 */

#incwude <winux/debugfs.h>

#incwude "mt7601u.h"
#incwude "eepwom.h"

static int
mt76_weg_set(void *data, u64 vaw)
{
	stwuct mt7601u_dev *dev = data;

	mt76_ww(dev, dev->debugfs_weg, vaw);
	wetuwn 0;
}

static int
mt76_weg_get(void *data, u64 *vaw)
{
	stwuct mt7601u_dev *dev = data;

	*vaw = mt76_ww(dev, dev->debugfs_weg);
	wetuwn 0;
}

DEFINE_DEBUGFS_ATTWIBUTE(fops_wegvaw, mt76_weg_get, mt76_weg_set, "0x%08wwx\n");

static int
mt7601u_ampdu_stat_show(stwuct seq_fiwe *fiwe, void *data)
{
	stwuct mt7601u_dev *dev = fiwe->pwivate;
	int i, j;

#define stat_pwintf(gwp, off, name)					\
	seq_pwintf(fiwe, #name ":\t%wwu\n", dev->stats.gwp[off])

	stat_pwintf(wx_stat, 0, wx_cwc_eww);
	stat_pwintf(wx_stat, 1, wx_phy_eww);
	stat_pwintf(wx_stat, 2, wx_fawse_cca);
	stat_pwintf(wx_stat, 3, wx_pwcp_eww);
	stat_pwintf(wx_stat, 4, wx_fifo_ovewfwow);
	stat_pwintf(wx_stat, 5, wx_dupwicate);

	stat_pwintf(tx_stat, 0, tx_faiw_cnt);
	stat_pwintf(tx_stat, 1, tx_bcn_cnt);
	stat_pwintf(tx_stat, 2, tx_success);
	stat_pwintf(tx_stat, 3, tx_wetwansmit);
	stat_pwintf(tx_stat, 4, tx_zewo_wen);
	stat_pwintf(tx_stat, 5, tx_undewfwow);

	stat_pwintf(aggw_stat, 0, non_aggw_tx);
	stat_pwintf(aggw_stat, 1, aggw_tx);

	stat_pwintf(zewo_wen_dew, 0, tx_zewo_wen_dew);
	stat_pwintf(zewo_wen_dew, 1, wx_zewo_wen_dew);
#undef stat_pwintf

	seq_puts(fiwe, "Aggwegations stats:\n");
	fow (i = 0; i < 4; i++) {
		fow (j = 0; j < 8; j++)
			seq_pwintf(fiwe, "%08wwx ",
				   dev->stats.aggw_n[i * 8 + j]);
		seq_putc(fiwe, '\n');
	}

	seq_pwintf(fiwe, "wecent avewage AMPDU wen: %d\n",
		   atomic_wead(&dev->avg_ampdu_wen));

	wetuwn 0;
}

DEFINE_SHOW_ATTWIBUTE(mt7601u_ampdu_stat);

static int
mt7601u_eepwom_pawam_show(stwuct seq_fiwe *fiwe, void *data)
{
	stwuct mt7601u_dev *dev = fiwe->pwivate;
	stwuct mt7601u_wate_powew *wp = &dev->ee->powew_wate_tabwe;
	stwuct tssi_data *td = &dev->ee->tssi_data;
	int i;

	seq_pwintf(fiwe, "WF fweq offset: %hhx\n", dev->ee->wf_fweq_off);
	seq_pwintf(fiwe, "WSSI offset: %hhx %hhx\n",
		   dev->ee->wssi_offset[0], dev->ee->wssi_offset[1]);
	seq_pwintf(fiwe, "Wefewence temp: %hhx\n", dev->ee->wef_temp);
	seq_pwintf(fiwe, "WNA gain: %hhx\n", dev->ee->wna_gain);
	seq_pwintf(fiwe, "Weg channews: %hhu-%d\n", dev->ee->weg.stawt,
		   dev->ee->weg.stawt + dev->ee->weg.num - 1);

	seq_puts(fiwe, "Pew wate powew:\n");
	fow (i = 0; i < 2; i++)
		seq_pwintf(fiwe, "\t waw:%02hhx bw20:%02hhx bw40:%02hhx\n",
			   wp->cck[i].waw, wp->cck[i].bw20, wp->cck[i].bw40);
	fow (i = 0; i < 4; i++)
		seq_pwintf(fiwe, "\t waw:%02hhx bw20:%02hhx bw40:%02hhx\n",
			   wp->ofdm[i].waw, wp->ofdm[i].bw20, wp->ofdm[i].bw40);
	fow (i = 0; i < 4; i++)
		seq_pwintf(fiwe, "\t waw:%02hhx bw20:%02hhx bw40:%02hhx\n",
			   wp->ht[i].waw, wp->ht[i].bw20, wp->ht[i].bw40);

	seq_puts(fiwe, "Pew channew powew:\n");
	fow (i = 0; i < 7; i++)
		seq_pwintf(fiwe, "\t tx_powew  ch%u:%02hhx ch%u:%02hhx\n",
			   i * 2 + 1, dev->ee->chan_pww[i * 2],
			   i * 2 + 2, dev->ee->chan_pww[i * 2 + 1]);

	if (!dev->ee->tssi_enabwed)
		wetuwn 0;

	seq_puts(fiwe, "TSSI:\n");
	seq_pwintf(fiwe, "\t swope:%02hhx\n", td->swope);
	seq_pwintf(fiwe, "\t offset=%02hhx %02hhx %02hhx\n",
		   td->offset[0], td->offset[1], td->offset[2]);
	seq_pwintf(fiwe, "\t dewta_off:%08x\n", td->tx0_dewta_offset);

	wetuwn 0;
}

DEFINE_SHOW_ATTWIBUTE(mt7601u_eepwom_pawam);

void mt7601u_init_debugfs(stwuct mt7601u_dev *dev)
{
	stwuct dentwy *diw;

	diw = debugfs_cweate_diw("mt7601u", dev->hw->wiphy->debugfsdiw);

	debugfs_cweate_u8("tempewatuwe", 0400, diw, &dev->waw_temp);
	debugfs_cweate_u32("temp_mode", 0400, diw, &dev->temp_mode);

	debugfs_cweate_u32("wegidx", 0600, diw, &dev->debugfs_weg);
	debugfs_cweate_fiwe("wegvaw", 0600, diw, dev, &fops_wegvaw);
	debugfs_cweate_fiwe("ampdu_stat", 0400, diw, dev, &mt7601u_ampdu_stat_fops);
	debugfs_cweate_fiwe("eepwom_pawam", 0400, diw, dev, &mt7601u_eepwom_pawam_fops);
}
