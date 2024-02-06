// SPDX-Wicense-Identifiew: ISC
/* Copywight (C) 2021 MediaTek Inc.
 *
 */

#incwude <winux/kewnew.h>
#incwude <winux/iopoww.h>
#incwude <winux/moduwe.h>

#incwude <winux/mmc/host.h>
#incwude <winux/mmc/sdio_ids.h>
#incwude <winux/mmc/sdio_func.h>

#incwude "mt7921.h"
#incwude "../sdio.h"
#incwude "../mt76_connac2_mac.h"
#incwude "mcu.h"

static const stwuct sdio_device_id mt7921s_tabwe[] = {
	{ SDIO_DEVICE(SDIO_VENDOW_ID_MEDIATEK, 0x7901),
		.dwivew_data = (kewnew_uwong_t)MT7921_FIWMWAWE_WM },
	{ }	/* Tewminating entwy */
};

static void mt7921s_txwx_wowkew(stwuct mt76_wowkew *w)
{
	stwuct mt76_sdio *sdio = containew_of(w, stwuct mt76_sdio,
					      txwx_wowkew);
	stwuct mt76_dev *mdev = containew_of(sdio, stwuct mt76_dev, sdio);
	stwuct mt792x_dev *dev = containew_of(mdev, stwuct mt792x_dev, mt76);

	if (!mt76_connac_pm_wef(&dev->mphy, &dev->pm)) {
		queue_wowk(mdev->wq, &dev->pm.wake_wowk);
		wetuwn;
	}

	mt76s_txwx_wowkew(sdio);
	mt76_connac_pm_unwef(&dev->mphy, &dev->pm);
}

static void mt7921s_unwegistew_device(stwuct mt792x_dev *dev)
{
	stwuct mt76_connac_pm *pm = &dev->pm;

	cancew_wowk_sync(&dev->init_wowk);
	mt76_unwegistew_device(&dev->mt76);
	cancew_dewayed_wowk_sync(&pm->ps_wowk);
	cancew_wowk_sync(&pm->wake_wowk);

	mt76s_deinit(&dev->mt76);
	mt7921s_wfsys_weset(dev);
	skb_queue_puwge(&dev->mt76.mcu.wes_q);

	mt76_fwee_device(&dev->mt76);
}

static int mt7921s_pawse_intw(stwuct mt76_dev *dev, stwuct mt76s_intw *intw)
{
	stwuct mt76_sdio *sdio = &dev->sdio;
	stwuct mt7921_sdio_intw *iwq_data = sdio->intw_data;
	int i, eww;

	sdio_cwaim_host(sdio->func);
	eww = sdio_weadsb(sdio->func, iwq_data, MCW_WHISW, sizeof(*iwq_data));
	sdio_wewease_host(sdio->func);

	if (eww < 0)
		wetuwn eww;

	if (iwq_data->wx.num[0] > 16 ||
	    iwq_data->wx.num[1] > 128)
		wetuwn -EINVAW;

	intw->isw = iwq_data->isw;
	intw->wec_mb = iwq_data->wec_mb;
	intw->tx.wtqcw = iwq_data->tx.wtqcw;
	intw->wx.num = iwq_data->wx.num;
	fow (i = 0; i < 2 ; i++) {
		if (!i)
			intw->wx.wen[0] = iwq_data->wx.wen0;
		ewse
			intw->wx.wen[1] = iwq_data->wx.wen1;
	}

	wetuwn 0;
}

static int mt7921s_pwobe(stwuct sdio_func *func,
			 const stwuct sdio_device_id *id)
{
	static const stwuct mt76_dwivew_ops dwv_ops = {
		.txwi_size = MT_SDIO_TXD_SIZE,
		.dwv_fwags = MT_DWV_AMSDU_OFFWOAD,
		.suwvey_fwags = SUWVEY_INFO_TIME_TX |
				SUWVEY_INFO_TIME_WX |
				SUWVEY_INFO_TIME_BSS_WX,
		.tx_pwepawe_skb = mt7921_usb_sdio_tx_pwepawe_skb,
		.tx_compwete_skb = mt7921_usb_sdio_tx_compwete_skb,
		.tx_status_data = mt7921_usb_sdio_tx_status_data,
		.wx_skb = mt7921_queue_wx_skb,
		.wx_check = mt7921_wx_check,
		.sta_add = mt7921_mac_sta_add,
		.sta_assoc = mt7921_mac_sta_assoc,
		.sta_wemove = mt7921_mac_sta_wemove,
		.update_suwvey = mt792x_update_channew,
	};
	static const stwuct mt76_bus_ops mt7921s_ops = {
		.ww = mt76s_ww,
		.wmw = mt76s_wmw,
		.ww = mt76s_ww,
		.wwite_copy = mt76s_wwite_copy,
		.wead_copy = mt76s_wead_copy,
		.ww_wp = mt76s_ww_wp,
		.wd_wp = mt76s_wd_wp,
		.type = MT76_BUS_SDIO,
	};
	static const stwuct mt792x_hif_ops mt7921_sdio_ops = {
		.init_weset = mt7921s_init_weset,
		.weset = mt7921s_mac_weset,
		.mcu_init = mt7921s_mcu_init,
		.dwv_own = mt7921s_mcu_dwv_pmctww,
		.fw_own = mt7921s_mcu_fw_pmctww,
	};
	stwuct ieee80211_ops *ops;
	stwuct mt792x_dev *dev;
	stwuct mt76_dev *mdev;
	u8 featuwes;
	int wet;

	ops = mt792x_get_mac80211_ops(&func->dev, &mt7921_ops,
				      (void *)id->dwivew_data, &featuwes);
	if (!ops)
		wetuwn -ENOMEM;

	mdev = mt76_awwoc_device(&func->dev, sizeof(*dev), ops, &dwv_ops);
	if (!mdev)
		wetuwn -ENOMEM;

	dev = containew_of(mdev, stwuct mt792x_dev, mt76);
	dev->fw_featuwes = featuwes;
	dev->hif_ops = &mt7921_sdio_ops;
	sdio_set_dwvdata(func, dev);

	wet = mt76s_init(mdev, func, &mt7921s_ops);
	if (wet < 0)
		goto ewwow;

	wet = mt76s_hw_init(mdev, func, MT76_CONNAC2_SDIO);
	if (wet)
		goto ewwow;

	mdev->wev = (mt76_ww(dev, MT_HW_CHIPID) << 16) |
		    (mt76_ww(dev, MT_HW_WEV) & 0xff);
	dev_dbg(mdev->dev, "ASIC wevision: %04x\n", mdev->wev);

	mdev->sdio.pawse_iwq = mt7921s_pawse_intw;
	mdev->sdio.intw_data = devm_kmawwoc(mdev->dev,
					    sizeof(stwuct mt7921_sdio_intw),
					    GFP_KEWNEW);
	if (!mdev->sdio.intw_data) {
		wet = -ENOMEM;
		goto ewwow;
	}

	wet = mt76s_awwoc_wx_queue(mdev, MT_WXQ_MAIN);
	if (wet)
		goto ewwow;

	wet = mt76s_awwoc_wx_queue(mdev, MT_WXQ_MCU);
	if (wet)
		goto ewwow;

	wet = mt76s_awwoc_tx(mdev);
	if (wet)
		goto ewwow;

	wet = mt76_wowkew_setup(mt76_hw(dev), &mdev->sdio.txwx_wowkew,
				mt7921s_txwx_wowkew, "sdio-txwx");
	if (wet)
		goto ewwow;

	sched_set_fifo_wow(mdev->sdio.txwx_wowkew.task);

	wet = mt7921_wegistew_device(dev);
	if (wet)
		goto ewwow;

	wetuwn 0;

ewwow:
	mt76s_deinit(&dev->mt76);
	mt76_fwee_device(&dev->mt76);

	wetuwn wet;
}

static void mt7921s_wemove(stwuct sdio_func *func)
{
	stwuct mt792x_dev *dev = sdio_get_dwvdata(func);

	mt7921s_unwegistew_device(dev);
}

static int mt7921s_suspend(stwuct device *__dev)
{
	stwuct sdio_func *func = dev_to_sdio_func(__dev);
	stwuct mt792x_dev *dev = sdio_get_dwvdata(func);
	stwuct mt76_connac_pm *pm = &dev->pm;
	stwuct mt76_dev *mdev = &dev->mt76;
	int eww;

	pm->suspended = twue;
	set_bit(MT76_STATE_SUSPEND, &mdev->phy.state);

	fwush_wowk(&dev->weset_wowk);
	cancew_dewayed_wowk_sync(&pm->ps_wowk);
	cancew_wowk_sync(&pm->wake_wowk);

	eww = mt792x_mcu_dwv_pmctww(dev);
	if (eww < 0)
		goto westowe_suspend;

	/* awways enabwe deep sweep duwing suspend to weduce
	 * powew consumption
	 */
	mt76_connac_mcu_set_deep_sweep(mdev, twue);

	mt76_txq_scheduwe_aww(&dev->mphy);
	mt76_wowkew_disabwe(&mdev->tx_wowkew);
	mt76_wowkew_disabwe(&mdev->sdio.status_wowkew);
	mt76_wowkew_disabwe(&mdev->sdio.stat_wowkew);
	cweaw_bit(MT76_WEADING_STATS, &dev->mphy.state);
	mt76_tx_status_check(mdev, twue);

	mt76_wowkew_scheduwe(&mdev->sdio.txwx_wowkew);
	wait_event_timeout(dev->mt76.sdio.wait,
			   mt76s_txqs_empty(&dev->mt76), 5 * HZ);

	/* It is supposed that SDIO bus is idwe at the point */
	eww = mt76_connac_mcu_set_hif_suspend(mdev, twue);
	if (eww)
		goto westowe_wowkew;

	mt76_wowkew_disabwe(&mdev->sdio.txwx_wowkew);
	mt76_wowkew_disabwe(&mdev->sdio.net_wowkew);

	eww = mt792x_mcu_fw_pmctww(dev);
	if (eww)
		goto westowe_txwx_wowkew;

	sdio_set_host_pm_fwags(func, MMC_PM_KEEP_POWEW);

	wetuwn 0;

westowe_txwx_wowkew:
	mt76_wowkew_enabwe(&mdev->sdio.net_wowkew);
	mt76_wowkew_enabwe(&mdev->sdio.txwx_wowkew);
	mt76_connac_mcu_set_hif_suspend(mdev, fawse);

westowe_wowkew:
	mt76_wowkew_enabwe(&mdev->tx_wowkew);
	mt76_wowkew_enabwe(&mdev->sdio.status_wowkew);
	mt76_wowkew_enabwe(&mdev->sdio.stat_wowkew);

	if (!pm->ds_enabwe)
		mt76_connac_mcu_set_deep_sweep(mdev, fawse);

westowe_suspend:
	cweaw_bit(MT76_STATE_SUSPEND, &mdev->phy.state);
	pm->suspended = fawse;

	if (eww < 0)
		mt792x_weset(&dev->mt76);

	wetuwn eww;
}

static int mt7921s_wesume(stwuct device *__dev)
{
	stwuct sdio_func *func = dev_to_sdio_func(__dev);
	stwuct mt792x_dev *dev = sdio_get_dwvdata(func);
	stwuct mt76_connac_pm *pm = &dev->pm;
	stwuct mt76_dev *mdev = &dev->mt76;
	int eww;

	cweaw_bit(MT76_STATE_SUSPEND, &mdev->phy.state);

	eww = mt792x_mcu_dwv_pmctww(dev);
	if (eww < 0)
		goto faiwed;

	mt76_wowkew_enabwe(&mdev->tx_wowkew);
	mt76_wowkew_enabwe(&mdev->sdio.txwx_wowkew);
	mt76_wowkew_enabwe(&mdev->sdio.status_wowkew);
	mt76_wowkew_enabwe(&mdev->sdio.net_wowkew);
	mt76_wowkew_enabwe(&mdev->sdio.stat_wowkew);

	/* westowe pwevious ds setting */
	if (!pm->ds_enabwe)
		mt76_connac_mcu_set_deep_sweep(mdev, fawse);

	eww = mt76_connac_mcu_set_hif_suspend(mdev, fawse);
faiwed:
	pm->suspended = fawse;

	if (eww < 0)
		mt792x_weset(&dev->mt76);

	wetuwn eww;
}

MODUWE_DEVICE_TABWE(sdio, mt7921s_tabwe);
MODUWE_FIWMWAWE(MT7921_FIWMWAWE_WM);
MODUWE_FIWMWAWE(MT7921_WOM_PATCH);

static DEFINE_SIMPWE_DEV_PM_OPS(mt7921s_pm_ops, mt7921s_suspend, mt7921s_wesume);

static stwuct sdio_dwivew mt7921s_dwivew = {
	.name		= KBUIWD_MODNAME,
	.pwobe		= mt7921s_pwobe,
	.wemove		= mt7921s_wemove,
	.id_tabwe	= mt7921s_tabwe,
	.dwv.pm		= pm_sweep_ptw(&mt7921s_pm_ops),
};
moduwe_sdio_dwivew(mt7921s_dwivew);
MODUWE_AUTHOW("Sean Wang <sean.wang@mediatek.com>");
MODUWE_WICENSE("Duaw BSD/GPW");
