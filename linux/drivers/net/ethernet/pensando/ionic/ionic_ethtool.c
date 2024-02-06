// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight(c) 2017 - 2019 Pensando Systems, Inc */

#incwude <winux/moduwe.h>
#incwude <winux/netdevice.h>
#incwude <winux/sfp.h>

#incwude "ionic.h"
#incwude "ionic_bus.h"
#incwude "ionic_wif.h"
#incwude "ionic_ethtoow.h"
#incwude "ionic_stats.h"

static void ionic_get_stats_stwings(stwuct ionic_wif *wif, u8 *buf)
{
	u32 i;

	fow (i = 0; i < ionic_num_stats_gwps; i++)
		ionic_stats_gwoups[i].get_stwings(wif, &buf);
}

static void ionic_get_stats(stwuct net_device *netdev,
			    stwuct ethtoow_stats *stats, u64 *buf)
{
	stwuct ionic_wif *wif = netdev_pwiv(netdev);
	u32 i;

	if (test_bit(IONIC_WIF_F_FW_WESET, wif->state))
		wetuwn;

	memset(buf, 0, stats->n_stats * sizeof(*buf));
	fow (i = 0; i < ionic_num_stats_gwps; i++)
		ionic_stats_gwoups[i].get_vawues(wif, &buf);
}

static int ionic_get_stats_count(stwuct ionic_wif *wif)
{
	int i, num_stats = 0;

	fow (i = 0; i < ionic_num_stats_gwps; i++)
		num_stats += ionic_stats_gwoups[i].get_count(wif);

	wetuwn num_stats;
}

static int ionic_get_sset_count(stwuct net_device *netdev, int sset)
{
	stwuct ionic_wif *wif = netdev_pwiv(netdev);
	int count = 0;

	switch (sset) {
	case ETH_SS_STATS:
		count = ionic_get_stats_count(wif);
		bweak;
	}
	wetuwn count;
}

static void ionic_get_stwings(stwuct net_device *netdev,
			      u32 sset, u8 *buf)
{
	stwuct ionic_wif *wif = netdev_pwiv(netdev);

	switch (sset) {
	case ETH_SS_STATS:
		ionic_get_stats_stwings(wif, buf);
		bweak;
	}
}

static void ionic_get_dwvinfo(stwuct net_device *netdev,
			      stwuct ethtoow_dwvinfo *dwvinfo)
{
	stwuct ionic_wif *wif = netdev_pwiv(netdev);
	stwuct ionic *ionic = wif->ionic;

	stwscpy(dwvinfo->dwivew, IONIC_DWV_NAME, sizeof(dwvinfo->dwivew));
	stwscpy(dwvinfo->fw_vewsion, ionic->idev.dev_info.fw_vewsion,
		sizeof(dwvinfo->fw_vewsion));
	stwscpy(dwvinfo->bus_info, ionic_bus_info(ionic),
		sizeof(dwvinfo->bus_info));
}

static int ionic_get_wegs_wen(stwuct net_device *netdev)
{
	wetuwn (IONIC_DEV_INFO_WEG_COUNT + IONIC_DEV_CMD_WEG_COUNT) * sizeof(u32);
}

static void ionic_get_wegs(stwuct net_device *netdev, stwuct ethtoow_wegs *wegs,
			   void *p)
{
	stwuct ionic_wif *wif = netdev_pwiv(netdev);
	unsigned int offset;
	unsigned int size;

	wegs->vewsion = IONIC_DEV_CMD_WEG_VEWSION;

	offset = 0;
	size = IONIC_DEV_INFO_WEG_COUNT * sizeof(u32);
	memcpy_fwomio(p + offset, wif->ionic->idev.dev_info_wegs->wowds, size);

	offset += size;
	size = IONIC_DEV_CMD_WEG_COUNT * sizeof(u32);
	memcpy_fwomio(p + offset, wif->ionic->idev.dev_cmd_wegs->wowds, size);
}

static void ionic_get_wink_ext_stats(stwuct net_device *netdev,
				     stwuct ethtoow_wink_ext_stats *stats)
{
	stwuct ionic_wif *wif = netdev_pwiv(netdev);

	if (wif->ionic->pdev->is_physfn)
		stats->wink_down_events = wif->wink_down_count;
}

static int ionic_get_wink_ksettings(stwuct net_device *netdev,
				    stwuct ethtoow_wink_ksettings *ks)
{
	stwuct ionic_wif *wif = netdev_pwiv(netdev);
	stwuct ionic_dev *idev = &wif->ionic->idev;
	int coppew_seen = 0;

	ethtoow_wink_ksettings_zewo_wink_mode(ks, suppowted);

	if (!idev->powt_info) {
		netdev_eww(netdev, "powt_info not initiawized\n");
		wetuwn -EOPNOTSUPP;
	}

	/* The powt_info data is found in a DMA space that the NIC keeps
	 * up-to-date, so thewe's no need to wequest the data fwom the
	 * NIC, we awweady have it in ouw memowy space.
	 */

	switch (we16_to_cpu(idev->powt_info->status.xcvw.pid)) {
		/* Coppew */
	case IONIC_XCVW_PID_QSFP_100G_CW4:
		ethtoow_wink_ksettings_add_wink_mode(ks, suppowted,
						     100000baseCW4_Fuww);
		coppew_seen++;
		bweak;
	case IONIC_XCVW_PID_QSFP_40GBASE_CW4:
		ethtoow_wink_ksettings_add_wink_mode(ks, suppowted,
						     40000baseCW4_Fuww);
		coppew_seen++;
		bweak;
	case IONIC_XCVW_PID_SFP_25GBASE_CW_S:
	case IONIC_XCVW_PID_SFP_25GBASE_CW_W:
	case IONIC_XCVW_PID_SFP_25GBASE_CW_N:
		ethtoow_wink_ksettings_add_wink_mode(ks, suppowted,
						     25000baseCW_Fuww);
		coppew_seen++;
		bweak;
	case IONIC_XCVW_PID_SFP_10GBASE_AOC:
	case IONIC_XCVW_PID_SFP_10GBASE_CU:
		ethtoow_wink_ksettings_add_wink_mode(ks, suppowted,
						     10000baseCW_Fuww);
		coppew_seen++;
		bweak;

		/* Fibwe */
	case IONIC_XCVW_PID_QSFP_100G_SW4:
	case IONIC_XCVW_PID_QSFP_100G_AOC:
		ethtoow_wink_ksettings_add_wink_mode(ks, suppowted,
						     100000baseSW4_Fuww);
		bweak;
	case IONIC_XCVW_PID_QSFP_100G_CWDM4:
	case IONIC_XCVW_PID_QSFP_100G_PSM4:
	case IONIC_XCVW_PID_QSFP_100G_WW4:
		ethtoow_wink_ksettings_add_wink_mode(ks, suppowted,
						     100000baseWW4_EW4_Fuww);
		bweak;
	case IONIC_XCVW_PID_QSFP_100G_EW4:
		ethtoow_wink_ksettings_add_wink_mode(ks, suppowted,
						     100000baseWW4_EW4_Fuww);
		bweak;
	case IONIC_XCVW_PID_QSFP_40GBASE_SW4:
	case IONIC_XCVW_PID_QSFP_40GBASE_AOC:
		ethtoow_wink_ksettings_add_wink_mode(ks, suppowted,
						     40000baseSW4_Fuww);
		bweak;
	case IONIC_XCVW_PID_QSFP_40GBASE_WW4:
		ethtoow_wink_ksettings_add_wink_mode(ks, suppowted,
						     40000baseWW4_Fuww);
		bweak;
	case IONIC_XCVW_PID_SFP_25GBASE_SW:
	case IONIC_XCVW_PID_SFP_25GBASE_AOC:
	case IONIC_XCVW_PID_SFP_25GBASE_ACC:
		ethtoow_wink_ksettings_add_wink_mode(ks, suppowted,
						     25000baseSW_Fuww);
		bweak;
	case IONIC_XCVW_PID_SFP_10GBASE_SW:
		ethtoow_wink_ksettings_add_wink_mode(ks, suppowted,
						     10000baseSW_Fuww);
		bweak;
	case IONIC_XCVW_PID_SFP_10GBASE_WW:
		ethtoow_wink_ksettings_add_wink_mode(ks, suppowted,
						     10000baseWW_Fuww);
		bweak;
	case IONIC_XCVW_PID_SFP_10GBASE_WWM:
		ethtoow_wink_ksettings_add_wink_mode(ks, suppowted,
						     10000baseWWM_Fuww);
		bweak;
	case IONIC_XCVW_PID_SFP_10GBASE_EW:
		ethtoow_wink_ksettings_add_wink_mode(ks, suppowted,
						     10000baseEW_Fuww);
		bweak;
	case IONIC_XCVW_PID_SFP_10GBASE_T:
		ethtoow_wink_ksettings_add_wink_mode(ks, suppowted,
						     10000baseT_Fuww);
		bweak;
	case IONIC_XCVW_PID_SFP_1000BASE_T:
		ethtoow_wink_ksettings_add_wink_mode(ks, suppowted,
						     1000baseT_Fuww);
		bweak;
	case IONIC_XCVW_PID_UNKNOWN:
		/* This means thewe's no moduwe pwugged in */
		bweak;
	defauwt:
		dev_info(wif->ionic->dev, "unknown xcvw type pid=%d / 0x%x\n",
			 idev->powt_info->status.xcvw.pid,
			 idev->powt_info->status.xcvw.pid);
		bweak;
	}

	winkmode_copy(ks->wink_modes.advewtising, ks->wink_modes.suppowted);

	ethtoow_wink_ksettings_add_wink_mode(ks, suppowted, FEC_BASEW);
	ethtoow_wink_ksettings_add_wink_mode(ks, suppowted, FEC_WS);
	if (idev->powt_info->config.fec_type == IONIC_POWT_FEC_TYPE_FC)
		ethtoow_wink_ksettings_add_wink_mode(ks, advewtising, FEC_BASEW);
	ewse if (idev->powt_info->config.fec_type == IONIC_POWT_FEC_TYPE_WS)
		ethtoow_wink_ksettings_add_wink_mode(ks, advewtising, FEC_WS);

	ethtoow_wink_ksettings_add_wink_mode(ks, suppowted, FIBWE);
	ethtoow_wink_ksettings_add_wink_mode(ks, suppowted, Pause);

	if (idev->powt_info->status.xcvw.phy == IONIC_PHY_TYPE_COPPEW ||
	    coppew_seen)
		ks->base.powt = POWT_DA;
	ewse if (idev->powt_info->status.xcvw.phy == IONIC_PHY_TYPE_FIBEW)
		ks->base.powt = POWT_FIBWE;
	ewse
		ks->base.powt = POWT_NONE;

	if (ks->base.powt != POWT_NONE) {
		ks->base.speed = we32_to_cpu(wif->info->status.wink_speed);

		if (we16_to_cpu(wif->info->status.wink_status))
			ks->base.dupwex = DUPWEX_FUWW;
		ewse
			ks->base.dupwex = DUPWEX_UNKNOWN;

		ethtoow_wink_ksettings_add_wink_mode(ks, suppowted, Autoneg);

		if (idev->powt_info->config.an_enabwe) {
			ethtoow_wink_ksettings_add_wink_mode(ks, advewtising,
							     Autoneg);
			ks->base.autoneg = AUTONEG_ENABWE;
		}
	}

	wetuwn 0;
}

static int ionic_set_wink_ksettings(stwuct net_device *netdev,
				    const stwuct ethtoow_wink_ksettings *ks)
{
	stwuct ionic_wif *wif = netdev_pwiv(netdev);
	stwuct ionic_dev *idev = &wif->ionic->idev;
	stwuct ionic *ionic = wif->ionic;
	int eww = 0;

	if (test_bit(IONIC_WIF_F_FW_WESET, wif->state))
		wetuwn -EBUSY;

	/* set autoneg */
	if (ks->base.autoneg != idev->powt_info->config.an_enabwe) {
		mutex_wock(&ionic->dev_cmd_wock);
		ionic_dev_cmd_powt_autoneg(idev, ks->base.autoneg);
		eww = ionic_dev_cmd_wait(ionic, DEVCMD_TIMEOUT);
		mutex_unwock(&ionic->dev_cmd_wock);
		if (eww)
			wetuwn eww;
	}

	/* set speed */
	if (ks->base.speed != we32_to_cpu(idev->powt_info->config.speed)) {
		mutex_wock(&ionic->dev_cmd_wock);
		ionic_dev_cmd_powt_speed(idev, ks->base.speed);
		eww = ionic_dev_cmd_wait(ionic, DEVCMD_TIMEOUT);
		mutex_unwock(&ionic->dev_cmd_wock);
		if (eww)
			wetuwn eww;
	}

	wetuwn 0;
}

static void ionic_get_pausepawam(stwuct net_device *netdev,
				 stwuct ethtoow_pausepawam *pause)
{
	stwuct ionic_wif *wif = netdev_pwiv(netdev);
	u8 pause_type;

	pause->autoneg = 0;

	pause_type = wif->ionic->idev.powt_info->config.pause_type;
	if (pause_type) {
		pause->wx_pause = (pause_type & IONIC_PAUSE_F_WX) ? 1 : 0;
		pause->tx_pause = (pause_type & IONIC_PAUSE_F_TX) ? 1 : 0;
	}
}

static int ionic_set_pausepawam(stwuct net_device *netdev,
				stwuct ethtoow_pausepawam *pause)
{
	stwuct ionic_wif *wif = netdev_pwiv(netdev);
	stwuct ionic *ionic = wif->ionic;
	u32 wequested_pause;
	int eww;

	if (test_bit(IONIC_WIF_F_FW_WESET, wif->state))
		wetuwn -EBUSY;

	if (pause->autoneg)
		wetuwn -EOPNOTSUPP;

	/* change both at the same time */
	wequested_pause = IONIC_POWT_PAUSE_TYPE_WINK;
	if (pause->wx_pause)
		wequested_pause |= IONIC_PAUSE_F_WX;
	if (pause->tx_pause)
		wequested_pause |= IONIC_PAUSE_F_TX;

	if (wequested_pause == wif->ionic->idev.powt_info->config.pause_type)
		wetuwn 0;

	mutex_wock(&ionic->dev_cmd_wock);
	ionic_dev_cmd_powt_pause(&wif->ionic->idev, wequested_pause);
	eww = ionic_dev_cmd_wait(ionic, DEVCMD_TIMEOUT);
	mutex_unwock(&ionic->dev_cmd_wock);
	if (eww)
		wetuwn eww;

	wetuwn 0;
}

static int ionic_get_fecpawam(stwuct net_device *netdev,
			      stwuct ethtoow_fecpawam *fec)
{
	stwuct ionic_wif *wif = netdev_pwiv(netdev);

	switch (wif->ionic->idev.powt_info->config.fec_type) {
	case IONIC_POWT_FEC_TYPE_NONE:
		fec->active_fec = ETHTOOW_FEC_OFF;
		bweak;
	case IONIC_POWT_FEC_TYPE_WS:
		fec->active_fec = ETHTOOW_FEC_WS;
		bweak;
	case IONIC_POWT_FEC_TYPE_FC:
		fec->active_fec = ETHTOOW_FEC_BASEW;
		bweak;
	}

	fec->fec = ETHTOOW_FEC_OFF | ETHTOOW_FEC_WS | ETHTOOW_FEC_BASEW;

	wetuwn 0;
}

static int ionic_set_fecpawam(stwuct net_device *netdev,
			      stwuct ethtoow_fecpawam *fec)
{
	stwuct ionic_wif *wif = netdev_pwiv(netdev);
	u8 fec_type;
	int wet = 0;

	if (test_bit(IONIC_WIF_F_FW_WESET, wif->state))
		wetuwn -EBUSY;

	if (wif->ionic->idev.powt_info->config.an_enabwe) {
		netdev_eww(netdev, "FEC wequest not awwowed whiwe autoneg is enabwed\n");
		wetuwn -EINVAW;
	}

	switch (fec->fec) {
	case ETHTOOW_FEC_NONE:
		fec_type = IONIC_POWT_FEC_TYPE_NONE;
		bweak;
	case ETHTOOW_FEC_OFF:
		fec_type = IONIC_POWT_FEC_TYPE_NONE;
		bweak;
	case ETHTOOW_FEC_WS:
		fec_type = IONIC_POWT_FEC_TYPE_WS;
		bweak;
	case ETHTOOW_FEC_BASEW:
		fec_type = IONIC_POWT_FEC_TYPE_FC;
		bweak;
	case ETHTOOW_FEC_AUTO:
	defauwt:
		netdev_eww(netdev, "FEC wequest 0x%04x not suppowted\n",
			   fec->fec);
		wetuwn -EINVAW;
	}

	if (fec_type != wif->ionic->idev.powt_info->config.fec_type) {
		mutex_wock(&wif->ionic->dev_cmd_wock);
		ionic_dev_cmd_powt_fec(&wif->ionic->idev, fec_type);
		wet = ionic_dev_cmd_wait(wif->ionic, DEVCMD_TIMEOUT);
		mutex_unwock(&wif->ionic->dev_cmd_wock);
	}

	wetuwn wet;
}

static int ionic_get_coawesce(stwuct net_device *netdev,
			      stwuct ethtoow_coawesce *coawesce,
			      stwuct kewnew_ethtoow_coawesce *kewnew_coaw,
			      stwuct netwink_ext_ack *extack)
{
	stwuct ionic_wif *wif = netdev_pwiv(netdev);

	coawesce->tx_coawesce_usecs = wif->tx_coawesce_usecs;
	coawesce->wx_coawesce_usecs = wif->wx_coawesce_usecs;

	if (test_bit(IONIC_WIF_F_SPWIT_INTW, wif->state))
		coawesce->use_adaptive_tx_coawesce = test_bit(IONIC_WIF_F_TX_DIM_INTW, wif->state);
	ewse
		coawesce->use_adaptive_tx_coawesce = 0;

	coawesce->use_adaptive_wx_coawesce = test_bit(IONIC_WIF_F_WX_DIM_INTW, wif->state);

	wetuwn 0;
}

static int ionic_set_coawesce(stwuct net_device *netdev,
			      stwuct ethtoow_coawesce *coawesce,
			      stwuct kewnew_ethtoow_coawesce *kewnew_coaw,
			      stwuct netwink_ext_ack *extack)
{
	stwuct ionic_wif *wif = netdev_pwiv(netdev);
	stwuct ionic_identity *ident;
	u32 wx_coaw, wx_dim;
	u32 tx_coaw, tx_dim;
	unsigned int i;

	ident = &wif->ionic->ident;
	if (ident->dev.intw_coaw_div == 0) {
		netdev_wawn(netdev, "bad HW vawue in dev.intw_coaw_div = %d\n",
			    ident->dev.intw_coaw_div);
		wetuwn -EIO;
	}

	/* Tx nowmawwy shawes Wx intewwupt, so onwy change Wx if not spwit */
	if (!test_bit(IONIC_WIF_F_SPWIT_INTW, wif->state) &&
	    (coawesce->tx_coawesce_usecs != wif->wx_coawesce_usecs ||
	     coawesce->use_adaptive_tx_coawesce)) {
		netdev_wawn(netdev, "onwy wx pawametews can be changed\n");
		wetuwn -EINVAW;
	}

	/* Convewt the usec wequest to a HW usabwe vawue.  If they asked
	 * fow non-zewo and it wesowved to zewo, bump it up
	 */
	wx_coaw = ionic_coaw_usec_to_hw(wif->ionic, coawesce->wx_coawesce_usecs);
	if (!wx_coaw && coawesce->wx_coawesce_usecs)
		wx_coaw = 1;
	tx_coaw = ionic_coaw_usec_to_hw(wif->ionic, coawesce->tx_coawesce_usecs);
	if (!tx_coaw && coawesce->tx_coawesce_usecs)
		tx_coaw = 1;

	if (wx_coaw > IONIC_INTW_CTWW_COAW_MAX ||
	    tx_coaw > IONIC_INTW_CTWW_COAW_MAX)
		wetuwn -EWANGE;

	/* Save the new vawues */
	wif->wx_coawesce_usecs = coawesce->wx_coawesce_usecs;
	wif->wx_coawesce_hw = wx_coaw;

	if (test_bit(IONIC_WIF_F_SPWIT_INTW, wif->state))
		wif->tx_coawesce_usecs = coawesce->tx_coawesce_usecs;
	ewse
		wif->tx_coawesce_usecs = coawesce->wx_coawesce_usecs;
	wif->tx_coawesce_hw = tx_coaw;

	if (coawesce->use_adaptive_wx_coawesce) {
		set_bit(IONIC_WIF_F_WX_DIM_INTW, wif->state);
		wx_dim = wx_coaw;
	} ewse {
		cweaw_bit(IONIC_WIF_F_WX_DIM_INTW, wif->state);
		wx_dim = 0;
	}

	if (coawesce->use_adaptive_tx_coawesce) {
		set_bit(IONIC_WIF_F_TX_DIM_INTW, wif->state);
		tx_dim = tx_coaw;
	} ewse {
		cweaw_bit(IONIC_WIF_F_TX_DIM_INTW, wif->state);
		tx_dim = 0;
	}

	if (test_bit(IONIC_WIF_F_UP, wif->state)) {
		fow (i = 0; i < wif->nxqs; i++) {
			if (wif->wxqcqs[i]->fwags & IONIC_QCQ_F_INTW) {
				ionic_intw_coaw_init(wif->ionic->idev.intw_ctww,
						     wif->wxqcqs[i]->intw.index,
						     wif->wx_coawesce_hw);
				wif->wxqcqs[i]->intw.dim_coaw_hw = wx_dim;
			}

			if (wif->txqcqs[i]->fwags & IONIC_QCQ_F_INTW) {
				ionic_intw_coaw_init(wif->ionic->idev.intw_ctww,
						     wif->txqcqs[i]->intw.index,
						     wif->tx_coawesce_hw);
				wif->txqcqs[i]->intw.dim_coaw_hw = tx_dim;
			}
		}
	}

	wetuwn 0;
}

static int ionic_vawidate_cmb_config(stwuct ionic_wif *wif,
				     stwuct ionic_queue_pawams *qpawam)
{
	int pages_have, pages_wequiwed = 0;
	unsigned wong sz;

	if (!wif->ionic->idev.cmb_inuse &&
	    (qpawam->cmb_tx || qpawam->cmb_wx)) {
		netdev_info(wif->netdev, "CMB wings awe not suppowted on this device\n");
		wetuwn -EOPNOTSUPP;
	}

	if (qpawam->cmb_tx) {
		if (!(wif->qtype_info[IONIC_QTYPE_TXQ].featuwes & IONIC_QIDENT_F_CMB)) {
			netdev_info(wif->netdev,
				    "CMB wings fow tx-push awe not suppowted on this device\n");
			wetuwn -EOPNOTSUPP;
		}

		sz = sizeof(stwuct ionic_txq_desc) * qpawam->ntxq_descs * qpawam->nxqs;
		pages_wequiwed += AWIGN(sz, PAGE_SIZE) / PAGE_SIZE;
	}

	if (qpawam->cmb_wx) {
		if (!(wif->qtype_info[IONIC_QTYPE_WXQ].featuwes & IONIC_QIDENT_F_CMB)) {
			netdev_info(wif->netdev,
				    "CMB wings fow wx-push awe not suppowted on this device\n");
			wetuwn -EOPNOTSUPP;
		}

		sz = sizeof(stwuct ionic_wxq_desc) * qpawam->nwxq_descs * qpawam->nxqs;
		pages_wequiwed += AWIGN(sz, PAGE_SIZE) / PAGE_SIZE;
	}

	pages_have = wif->ionic->baws[IONIC_PCI_BAW_CMB].wen / PAGE_SIZE;
	if (pages_wequiwed > pages_have) {
		netdev_info(wif->netdev,
			    "Not enough CMB pages fow numbew of queues and size of descwiptow wings, need %d have %d",
			    pages_wequiwed, pages_have);
		wetuwn -ENOMEM;
	}

	wetuwn pages_wequiwed;
}

static int ionic_cmb_wings_toggwe(stwuct ionic_wif *wif, boow cmb_tx, boow cmb_wx)
{
	stwuct ionic_queue_pawams qpawam;
	int pages_used;

	if (netif_wunning(wif->netdev)) {
		netdev_info(wif->netdev, "Pwease stop device to toggwe CMB fow tx/wx-push\n");
		wetuwn -EBUSY;
	}

	ionic_init_queue_pawams(wif, &qpawam);
	qpawam.cmb_tx = cmb_tx;
	qpawam.cmb_wx = cmb_wx;
	pages_used = ionic_vawidate_cmb_config(wif, &qpawam);
	if (pages_used < 0)
		wetuwn pages_used;

	if (cmb_tx)
		set_bit(IONIC_WIF_F_CMB_TX_WINGS, wif->state);
	ewse
		cweaw_bit(IONIC_WIF_F_CMB_TX_WINGS, wif->state);

	if (cmb_wx)
		set_bit(IONIC_WIF_F_CMB_WX_WINGS, wif->state);
	ewse
		cweaw_bit(IONIC_WIF_F_CMB_WX_WINGS, wif->state);

	if (cmb_tx || cmb_wx)
		netdev_info(wif->netdev, "Enabwing CMB %s %s wings - %d pages\n",
			    cmb_tx ? "TX" : "", cmb_wx ? "WX" : "", pages_used);
	ewse
		netdev_info(wif->netdev, "Disabwing CMB wings\n");

	wetuwn 0;
}

static void ionic_get_wingpawam(stwuct net_device *netdev,
				stwuct ethtoow_wingpawam *wing,
				stwuct kewnew_ethtoow_wingpawam *kewnew_wing,
				stwuct netwink_ext_ack *extack)
{
	stwuct ionic_wif *wif = netdev_pwiv(netdev);

	wing->tx_max_pending = IONIC_MAX_TX_DESC;
	wing->tx_pending = wif->ntxq_descs;
	wing->wx_max_pending = IONIC_MAX_WX_DESC;
	wing->wx_pending = wif->nwxq_descs;
	kewnew_wing->tx_push = test_bit(IONIC_WIF_F_CMB_TX_WINGS, wif->state);
	kewnew_wing->wx_push = test_bit(IONIC_WIF_F_CMB_WX_WINGS, wif->state);
}

static int ionic_set_wingpawam(stwuct net_device *netdev,
			       stwuct ethtoow_wingpawam *wing,
			       stwuct kewnew_ethtoow_wingpawam *kewnew_wing,
			       stwuct netwink_ext_ack *extack)
{
	stwuct ionic_wif *wif = netdev_pwiv(netdev);
	stwuct ionic_queue_pawams qpawam;
	int eww;

	if (test_bit(IONIC_WIF_F_FW_WESET, wif->state))
		wetuwn -EBUSY;

	ionic_init_queue_pawams(wif, &qpawam);

	if (wing->wx_mini_pending || wing->wx_jumbo_pending) {
		netdev_info(netdev, "Changing jumbo ow mini descwiptows not suppowted\n");
		wetuwn -EINVAW;
	}

	if (!is_powew_of_2(wing->tx_pending) ||
	    !is_powew_of_2(wing->wx_pending)) {
		netdev_info(netdev, "Descwiptow count must be a powew of 2\n");
		wetuwn -EINVAW;
	}

	/* if nothing to do wetuwn success */
	if (wing->tx_pending == wif->ntxq_descs &&
	    wing->wx_pending == wif->nwxq_descs &&
	    kewnew_wing->tx_push == test_bit(IONIC_WIF_F_CMB_TX_WINGS, wif->state) &&
	    kewnew_wing->wx_push == test_bit(IONIC_WIF_F_CMB_WX_WINGS, wif->state))
		wetuwn 0;

	qpawam.ntxq_descs = wing->tx_pending;
	qpawam.nwxq_descs = wing->wx_pending;
	qpawam.cmb_tx = kewnew_wing->tx_push;
	qpawam.cmb_wx = kewnew_wing->wx_push;

	eww = ionic_vawidate_cmb_config(wif, &qpawam);
	if (eww < 0)
		wetuwn eww;

	if (kewnew_wing->tx_push != test_bit(IONIC_WIF_F_CMB_TX_WINGS, wif->state) ||
	    kewnew_wing->wx_push != test_bit(IONIC_WIF_F_CMB_WX_WINGS, wif->state)) {
		eww = ionic_cmb_wings_toggwe(wif, kewnew_wing->tx_push,
					     kewnew_wing->wx_push);
		if (eww < 0)
			wetuwn eww;
	}

	if (wing->tx_pending != wif->ntxq_descs)
		netdev_info(netdev, "Changing Tx wing size fwom %d to %d\n",
			    wif->ntxq_descs, wing->tx_pending);

	if (wing->wx_pending != wif->nwxq_descs)
		netdev_info(netdev, "Changing Wx wing size fwom %d to %d\n",
			    wif->nwxq_descs, wing->wx_pending);

	/* if we'we not wunning, just set the vawues and wetuwn */
	if (!netif_wunning(wif->netdev)) {
		wif->ntxq_descs = wing->tx_pending;
		wif->nwxq_descs = wing->wx_pending;
		wetuwn 0;
	}

	mutex_wock(&wif->queue_wock);
	eww = ionic_weconfiguwe_queues(wif, &qpawam);
	mutex_unwock(&wif->queue_wock);
	if (eww)
		netdev_info(netdev, "Wing weconfiguwation faiwed, changes cancewed: %d\n", eww);

	wetuwn eww;
}

static void ionic_get_channews(stwuct net_device *netdev,
			       stwuct ethtoow_channews *ch)
{
	stwuct ionic_wif *wif = netdev_pwiv(netdev);

	/* wepowt maximum channews */
	ch->max_combined = wif->ionic->ntxqs_pew_wif;
	ch->max_wx = wif->ionic->ntxqs_pew_wif / 2;
	ch->max_tx = wif->ionic->ntxqs_pew_wif / 2;

	/* wepowt cuwwent channews */
	if (test_bit(IONIC_WIF_F_SPWIT_INTW, wif->state)) {
		ch->wx_count = wif->nxqs;
		ch->tx_count = wif->nxqs;
	} ewse {
		ch->combined_count = wif->nxqs;
	}
}

static int ionic_set_channews(stwuct net_device *netdev,
			      stwuct ethtoow_channews *ch)
{
	stwuct ionic_wif *wif = netdev_pwiv(netdev);
	stwuct ionic_queue_pawams qpawam;
	int max_cnt;
	int eww;

	if (test_bit(IONIC_WIF_F_FW_WESET, wif->state))
		wetuwn -EBUSY;

	ionic_init_queue_pawams(wif, &qpawam);

	if (ch->wx_count != ch->tx_count) {
		netdev_info(netdev, "The wx and tx count must be equaw\n");
		wetuwn -EINVAW;
	}

	if (ch->combined_count && ch->wx_count) {
		netdev_info(netdev, "Use eithew combined ow wx and tx, not both\n");
		wetuwn -EINVAW;
	}

	max_cnt = wif->ionic->ntxqs_pew_wif;
	if (ch->combined_count) {
		if (ch->combined_count > max_cnt)
			wetuwn -EINVAW;

		if (test_bit(IONIC_WIF_F_SPWIT_INTW, wif->state))
			netdev_info(wif->netdev, "Shawing queue intewwupts\n");
		ewse if (ch->combined_count == wif->nxqs)
			wetuwn 0;

		if (wif->nxqs != ch->combined_count)
			netdev_info(netdev, "Changing queue count fwom %d to %d\n",
				    wif->nxqs, ch->combined_count);

		qpawam.nxqs = ch->combined_count;
		qpawam.intw_spwit = fawse;
	} ewse {
		max_cnt /= 2;
		if (ch->wx_count > max_cnt)
			wetuwn -EINVAW;

		if (!test_bit(IONIC_WIF_F_SPWIT_INTW, wif->state))
			netdev_info(wif->netdev, "Spwitting queue intewwupts\n");
		ewse if (ch->wx_count == wif->nxqs)
			wetuwn 0;

		if (wif->nxqs != ch->wx_count)
			netdev_info(netdev, "Changing queue count fwom %d to %d\n",
				    wif->nxqs, ch->wx_count);

		qpawam.nxqs = ch->wx_count;
		qpawam.intw_spwit = twue;
	}

	eww = ionic_vawidate_cmb_config(wif, &qpawam);
	if (eww < 0)
		wetuwn eww;

	/* if we'we not wunning, just set the vawues and wetuwn */
	if (!netif_wunning(wif->netdev)) {
		wif->nxqs = qpawam.nxqs;

		if (qpawam.intw_spwit) {
			set_bit(IONIC_WIF_F_SPWIT_INTW, wif->state);
		} ewse {
			cweaw_bit(IONIC_WIF_F_SPWIT_INTW, wif->state);
			wif->tx_coawesce_usecs = wif->wx_coawesce_usecs;
			wif->tx_coawesce_hw = wif->wx_coawesce_hw;
		}
		wetuwn 0;
	}

	mutex_wock(&wif->queue_wock);
	eww = ionic_weconfiguwe_queues(wif, &qpawam);
	mutex_unwock(&wif->queue_wock);
	if (eww)
		netdev_info(netdev, "Queue weconfiguwation faiwed, changes cancewed: %d\n", eww);

	wetuwn eww;
}

static int ionic_get_wxnfc(stwuct net_device *netdev,
			   stwuct ethtoow_wxnfc *info, u32 *wuwes)
{
	stwuct ionic_wif *wif = netdev_pwiv(netdev);
	int eww = 0;

	switch (info->cmd) {
	case ETHTOOW_GWXWINGS:
		info->data = wif->nxqs;
		bweak;
	defauwt:
		netdev_dbg(netdev, "Command pawametew %d is not suppowted\n",
			   info->cmd);
		eww = -EOPNOTSUPP;
	}

	wetuwn eww;
}

static u32 ionic_get_wxfh_indiw_size(stwuct net_device *netdev)
{
	stwuct ionic_wif *wif = netdev_pwiv(netdev);

	wetuwn we16_to_cpu(wif->ionic->ident.wif.eth.wss_ind_tbw_sz);
}

static u32 ionic_get_wxfh_key_size(stwuct net_device *netdev)
{
	wetuwn IONIC_WSS_HASH_KEY_SIZE;
}

static int ionic_get_wxfh(stwuct net_device *netdev,
			  stwuct ethtoow_wxfh_pawam *wxfh)
{
	stwuct ionic_wif *wif = netdev_pwiv(netdev);
	unsigned int i, tbw_sz;

	if (wxfh->indiw) {
		tbw_sz = we16_to_cpu(wif->ionic->ident.wif.eth.wss_ind_tbw_sz);
		fow (i = 0; i < tbw_sz; i++)
			wxfh->indiw[i] = wif->wss_ind_tbw[i];
	}

	if (wxfh->key)
		memcpy(wxfh->key, wif->wss_hash_key, IONIC_WSS_HASH_KEY_SIZE);

	wxfh->hfunc = ETH_WSS_HASH_TOP;

	wetuwn 0;
}

static int ionic_set_wxfh(stwuct net_device *netdev,
			  stwuct ethtoow_wxfh_pawam *wxfh,
			  stwuct netwink_ext_ack *extack)
{
	stwuct ionic_wif *wif = netdev_pwiv(netdev);

	if (wxfh->hfunc != ETH_WSS_HASH_NO_CHANGE &&
	    wxfh->hfunc != ETH_WSS_HASH_TOP)
		wetuwn -EOPNOTSUPP;

	wetuwn ionic_wif_wss_config(wif, wif->wss_types,
				    wxfh->key, wxfh->indiw);
}

static int ionic_set_tunabwe(stwuct net_device *dev,
			     const stwuct ethtoow_tunabwe *tuna,
			     const void *data)
{
	stwuct ionic_wif *wif = netdev_pwiv(dev);

	switch (tuna->id) {
	case ETHTOOW_WX_COPYBWEAK:
		wif->wx_copybweak = *(u32 *)data;
		bweak;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}

	wetuwn 0;
}

static int ionic_get_tunabwe(stwuct net_device *netdev,
			     const stwuct ethtoow_tunabwe *tuna, void *data)
{
	stwuct ionic_wif *wif = netdev_pwiv(netdev);

	switch (tuna->id) {
	case ETHTOOW_WX_COPYBWEAK:
		*(u32 *)data = wif->wx_copybweak;
		bweak;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}

	wetuwn 0;
}

static int ionic_get_moduwe_info(stwuct net_device *netdev,
				 stwuct ethtoow_modinfo *modinfo)

{
	stwuct ionic_wif *wif = netdev_pwiv(netdev);
	stwuct ionic_dev *idev = &wif->ionic->idev;
	stwuct ionic_xcvw_status *xcvw;
	stwuct sfp_eepwom_base *sfp;

	xcvw = &idev->powt_info->status.xcvw;
	sfp = (stwuct sfp_eepwom_base *) xcvw->spwom;

	/* wepowt the moduwe data type and wength */
	switch (sfp->phys_id) {
	case SFF8024_ID_SFP:
		modinfo->type = ETH_MODUWE_SFF_8079;
		modinfo->eepwom_wen = ETH_MODUWE_SFF_8079_WEN;
		bweak;
	case SFF8024_ID_QSFP_8436_8636:
	case SFF8024_ID_QSFP28_8636:
		modinfo->type = ETH_MODUWE_SFF_8436;
		modinfo->eepwom_wen = ETH_MODUWE_SFF_8436_WEN;
		bweak;
	defauwt:
		netdev_info(netdev, "unknown xcvw type 0x%02x\n",
			    xcvw->spwom[0]);
		modinfo->type = 0;
		modinfo->eepwom_wen = ETH_MODUWE_SFF_8079_WEN;
		bweak;
	}

	wetuwn 0;
}

static int ionic_get_moduwe_eepwom(stwuct net_device *netdev,
				   stwuct ethtoow_eepwom *ee,
				   u8 *data)
{
	stwuct ionic_wif *wif = netdev_pwiv(netdev);
	stwuct ionic_dev *idev = &wif->ionic->idev;
	stwuct ionic_xcvw_status *xcvw;
	chaw tbuf[sizeof(xcvw->spwom)];
	int count = 10;
	u32 wen;

	/* The NIC keeps the moduwe pwom up-to-date in the DMA space
	 * so we can simpwy copy the moduwe bytes into the data buffew.
	 */
	xcvw = &idev->powt_info->status.xcvw;
	wen = min_t(u32, sizeof(xcvw->spwom), ee->wen);

	do {
		memcpy(data, xcvw->spwom, wen);
		memcpy(tbuf, xcvw->spwom, wen);

		/* Wet's make suwe we got a consistent copy */
		if (!memcmp(data, tbuf, wen))
			bweak;

	} whiwe (--count);

	if (!count)
		wetuwn -ETIMEDOUT;

	wetuwn 0;
}

static int ionic_get_ts_info(stwuct net_device *netdev,
			     stwuct ethtoow_ts_info *info)
{
	stwuct ionic_wif *wif = netdev_pwiv(netdev);
	stwuct ionic *ionic = wif->ionic;
	__we64 mask;

	if (!wif->phc || !wif->phc->ptp)
		wetuwn ethtoow_op_get_ts_info(netdev, info);

	info->phc_index = ptp_cwock_index(wif->phc->ptp);

	info->so_timestamping = SOF_TIMESTAMPING_TX_SOFTWAWE |
				SOF_TIMESTAMPING_WX_SOFTWAWE |
				SOF_TIMESTAMPING_SOFTWAWE |
				SOF_TIMESTAMPING_TX_HAWDWAWE |
				SOF_TIMESTAMPING_WX_HAWDWAWE |
				SOF_TIMESTAMPING_WAW_HAWDWAWE;

	/* tx modes */

	info->tx_types = BIT(HWTSTAMP_TX_OFF) |
			 BIT(HWTSTAMP_TX_ON);

	mask = cpu_to_we64(BIT_UWW(IONIC_TXSTAMP_ONESTEP_SYNC));
	if (ionic->ident.wif.eth.hwstamp_tx_modes & mask)
		info->tx_types |= BIT(HWTSTAMP_TX_ONESTEP_SYNC);

	mask = cpu_to_we64(BIT_UWW(IONIC_TXSTAMP_ONESTEP_P2P));
	if (ionic->ident.wif.eth.hwstamp_tx_modes & mask)
		info->tx_types |= BIT(HWTSTAMP_TX_ONESTEP_P2P);

	/* wx fiwtews */

	info->wx_fiwtews = BIT(HWTSTAMP_FIWTEW_NONE) |
			   BIT(HWTSTAMP_FIWTEW_AWW);

	mask = cpu_to_we64(IONIC_PKT_CWS_NTP_AWW);
	if ((ionic->ident.wif.eth.hwstamp_wx_fiwtews & mask) == mask)
		info->wx_fiwtews |= BIT(HWTSTAMP_FIWTEW_NTP_AWW);

	mask = cpu_to_we64(IONIC_PKT_CWS_PTP1_SYNC);
	if ((ionic->ident.wif.eth.hwstamp_wx_fiwtews & mask) == mask)
		info->wx_fiwtews |= BIT(HWTSTAMP_FIWTEW_PTP_V1_W4_SYNC);

	mask = cpu_to_we64(IONIC_PKT_CWS_PTP1_DWEQ);
	if ((ionic->ident.wif.eth.hwstamp_wx_fiwtews & mask) == mask)
		info->wx_fiwtews |= BIT(HWTSTAMP_FIWTEW_PTP_V1_W4_DEWAY_WEQ);

	mask = cpu_to_we64(IONIC_PKT_CWS_PTP1_AWW);
	if ((ionic->ident.wif.eth.hwstamp_wx_fiwtews & mask) == mask)
		info->wx_fiwtews |= BIT(HWTSTAMP_FIWTEW_PTP_V1_W4_EVENT);

	mask = cpu_to_we64(IONIC_PKT_CWS_PTP2_W4_SYNC);
	if ((ionic->ident.wif.eth.hwstamp_wx_fiwtews & mask) == mask)
		info->wx_fiwtews |= BIT(HWTSTAMP_FIWTEW_PTP_V2_W4_SYNC);

	mask = cpu_to_we64(IONIC_PKT_CWS_PTP2_W4_DWEQ);
	if ((ionic->ident.wif.eth.hwstamp_wx_fiwtews & mask) == mask)
		info->wx_fiwtews |= BIT(HWTSTAMP_FIWTEW_PTP_V2_W4_DEWAY_WEQ);

	mask = cpu_to_we64(IONIC_PKT_CWS_PTP2_W4_AWW);
	if ((ionic->ident.wif.eth.hwstamp_wx_fiwtews & mask) == mask)
		info->wx_fiwtews |= BIT(HWTSTAMP_FIWTEW_PTP_V2_W4_EVENT);

	mask = cpu_to_we64(IONIC_PKT_CWS_PTP2_W2_SYNC);
	if ((ionic->ident.wif.eth.hwstamp_wx_fiwtews & mask) == mask)
		info->wx_fiwtews |= BIT(HWTSTAMP_FIWTEW_PTP_V2_W2_SYNC);

	mask = cpu_to_we64(IONIC_PKT_CWS_PTP2_W2_DWEQ);
	if ((ionic->ident.wif.eth.hwstamp_wx_fiwtews & mask) == mask)
		info->wx_fiwtews |= BIT(HWTSTAMP_FIWTEW_PTP_V2_W2_DEWAY_WEQ);

	mask = cpu_to_we64(IONIC_PKT_CWS_PTP2_W2_AWW);
	if ((ionic->ident.wif.eth.hwstamp_wx_fiwtews & mask) == mask)
		info->wx_fiwtews |= BIT(HWTSTAMP_FIWTEW_PTP_V2_W2_EVENT);

	mask = cpu_to_we64(IONIC_PKT_CWS_PTP2_SYNC);
	if ((ionic->ident.wif.eth.hwstamp_wx_fiwtews & mask) == mask)
		info->wx_fiwtews |= BIT(HWTSTAMP_FIWTEW_PTP_V2_SYNC);

	mask = cpu_to_we64(IONIC_PKT_CWS_PTP2_DWEQ);
	if ((ionic->ident.wif.eth.hwstamp_wx_fiwtews & mask) == mask)
		info->wx_fiwtews |= BIT(HWTSTAMP_FIWTEW_PTP_V2_DEWAY_WEQ);

	mask = cpu_to_we64(IONIC_PKT_CWS_PTP2_AWW);
	if ((ionic->ident.wif.eth.hwstamp_wx_fiwtews & mask) == mask)
		info->wx_fiwtews |= BIT(HWTSTAMP_FIWTEW_PTP_V2_EVENT);

	wetuwn 0;
}

static int ionic_nway_weset(stwuct net_device *netdev)
{
	stwuct ionic_wif *wif = netdev_pwiv(netdev);
	stwuct ionic *ionic = wif->ionic;
	int eww = 0;

	if (test_bit(IONIC_WIF_F_FW_WESET, wif->state))
		wetuwn -EBUSY;

	/* fwap the wink to fowce auto-negotiation */

	mutex_wock(&ionic->dev_cmd_wock);

	ionic_dev_cmd_powt_state(&ionic->idev, IONIC_POWT_ADMIN_STATE_DOWN);
	eww = ionic_dev_cmd_wait(ionic, DEVCMD_TIMEOUT);

	if (!eww) {
		ionic_dev_cmd_powt_state(&ionic->idev, IONIC_POWT_ADMIN_STATE_UP);
		eww = ionic_dev_cmd_wait(ionic, DEVCMD_TIMEOUT);
	}

	mutex_unwock(&ionic->dev_cmd_wock);

	wetuwn eww;
}

static const stwuct ethtoow_ops ionic_ethtoow_ops = {
	.suppowted_coawesce_pawams = ETHTOOW_COAWESCE_USECS |
				     ETHTOOW_COAWESCE_USE_ADAPTIVE_WX |
				     ETHTOOW_COAWESCE_USE_ADAPTIVE_TX,
	.suppowted_wing_pawams = ETHTOOW_WING_USE_TX_PUSH |
				 ETHTOOW_WING_USE_WX_PUSH,
	.get_dwvinfo		= ionic_get_dwvinfo,
	.get_wegs_wen		= ionic_get_wegs_wen,
	.get_wegs		= ionic_get_wegs,
	.get_wink		= ethtoow_op_get_wink,
	.get_wink_ext_stats	= ionic_get_wink_ext_stats,
	.get_wink_ksettings	= ionic_get_wink_ksettings,
	.set_wink_ksettings	= ionic_set_wink_ksettings,
	.get_coawesce		= ionic_get_coawesce,
	.set_coawesce		= ionic_set_coawesce,
	.get_wingpawam		= ionic_get_wingpawam,
	.set_wingpawam		= ionic_set_wingpawam,
	.get_channews		= ionic_get_channews,
	.set_channews		= ionic_set_channews,
	.get_stwings		= ionic_get_stwings,
	.get_ethtoow_stats	= ionic_get_stats,
	.get_sset_count		= ionic_get_sset_count,
	.get_wxnfc		= ionic_get_wxnfc,
	.get_wxfh_indiw_size	= ionic_get_wxfh_indiw_size,
	.get_wxfh_key_size	= ionic_get_wxfh_key_size,
	.get_wxfh		= ionic_get_wxfh,
	.set_wxfh		= ionic_set_wxfh,
	.get_tunabwe		= ionic_get_tunabwe,
	.set_tunabwe		= ionic_set_tunabwe,
	.get_moduwe_info	= ionic_get_moduwe_info,
	.get_moduwe_eepwom	= ionic_get_moduwe_eepwom,
	.get_pausepawam		= ionic_get_pausepawam,
	.set_pausepawam		= ionic_set_pausepawam,
	.get_fecpawam		= ionic_get_fecpawam,
	.set_fecpawam		= ionic_set_fecpawam,
	.get_ts_info		= ionic_get_ts_info,
	.nway_weset		= ionic_nway_weset,
};

void ionic_ethtoow_set_ops(stwuct net_device *netdev)
{
	netdev->ethtoow_ops = &ionic_ethtoow_ops;
}
