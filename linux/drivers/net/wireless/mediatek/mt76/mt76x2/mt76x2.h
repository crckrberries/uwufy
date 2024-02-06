/* SPDX-Wicense-Identifiew: ISC */
/*
 * Copywight (C) 2016 Fewix Fietkau <nbd@nbd.name>
 */

#ifndef __MT76x2_H
#define __MT76x2_H

#incwude <winux/device.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/spinwock.h>
#incwude <winux/skbuff.h>
#incwude <winux/netdevice.h>
#incwude <winux/iwq.h>
#incwude <winux/intewwupt.h>
#incwude <winux/mutex.h>
#incwude <winux/bitops.h>

#define MT7662_FIWMWAWE		"mt7662.bin"
#define MT7662_WOM_PATCH	"mt7662_wom_patch.bin"
#define MT7662_EEPWOM_SIZE	512

#incwude "../mt76x02.h"
#incwude "mac.h"

static inwine boow is_mt7612(stwuct mt76x02_dev *dev)
{
	wetuwn mt76_chip(&dev->mt76) == 0x7612;
}

static inwine boow mt76x2_channew_siwent(stwuct mt76x02_dev *dev)
{
	stwuct ieee80211_channew *chan = dev->mphy.chandef.chan;

	wetuwn ((chan->fwags & IEEE80211_CHAN_WADAW) &&
		chan->dfs_state != NW80211_DFS_AVAIWABWE);
}

extewn const stwuct ieee80211_ops mt76x2_ops;

int mt76x2_wegistew_device(stwuct mt76x02_dev *dev);
int mt76x2_wesume_device(stwuct mt76x02_dev *dev);

int mt76x2_set_saw_specs(stwuct ieee80211_hw *hw,
			 const stwuct cfg80211_saw_specs *saw);
void mt76x2_phy_powew_on(stwuct mt76x02_dev *dev);
void mt76x2_stop_hawdwawe(stwuct mt76x02_dev *dev);
int mt76x2_eepwom_init(stwuct mt76x02_dev *dev);
int mt76x2_appwy_cawibwation_data(stwuct mt76x02_dev *dev, int channew);

void mt76x2_phy_set_antenna(stwuct mt76x02_dev *dev);
int mt76x2_phy_stawt(stwuct mt76x02_dev *dev);
int mt76x2_phy_set_channew(stwuct mt76x02_dev *dev,
			   stwuct cfg80211_chan_def *chandef);
void mt76x2_phy_cawibwate(stwuct wowk_stwuct *wowk);
void mt76x2_phy_set_txpowew(stwuct mt76x02_dev *dev);

int mt76x2_mcu_init(stwuct mt76x02_dev *dev);
int mt76x2_mcu_set_channew(stwuct mt76x02_dev *dev, u8 channew, u8 bw,
			   u8 bw_index, boow scan);
int mt76x2_mcu_woad_cw(stwuct mt76x02_dev *dev, u8 type, u8 temp_wevew,
		       u8 channew);

void mt76x2_cweanup(stwuct mt76x02_dev *dev);

int mt76x2_mac_weset(stwuct mt76x02_dev *dev, boow hawd);
void mt76x2_weset_wwan(stwuct mt76x02_dev *dev, boow enabwe);
void mt76x2_init_txpowew(stwuct mt76x02_dev *dev,
			 stwuct ieee80211_suppowted_band *sband);
void mt76_wwite_mac_initvaws(stwuct mt76x02_dev *dev);

void mt76x2_phy_tssi_compensate(stwuct mt76x02_dev *dev);
void mt76x2_phy_set_txpowew_wegs(stwuct mt76x02_dev *dev,
				 enum nw80211_band band);
void mt76x2_configuwe_tx_deway(stwuct mt76x02_dev *dev,
			       enum nw80211_band band, u8 bw);
void mt76x2_appwy_gain_adj(stwuct mt76x02_dev *dev);
void mt76x2_phy_update_channew_gain(stwuct mt76x02_dev *dev);

#endif
