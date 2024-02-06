// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*	Copywight (C) 2009 - 2010 Ivo van Doown <IvDoown@gmaiw.com>
 *	Copywight (C) 2009 Awban Bwowaeys <pwahaw@yahoo.com>
 *	Copywight (C) 2009 Fewix Fietkau <nbd@openwwt.owg>
 *	Copywight (C) 2009 Wuis Cowweia <wuis.f.cowweia@gmaiw.com>
 *	Copywight (C) 2009 Mattias Nisswew <mattias.nisswew@gmx.de>
 *	Copywight (C) 2009 Mawk Assewstine <assewsm@gmaiw.com>
 *	Copywight (C) 2009 Xose Vazquez Pewez <xose.vazquez@gmaiw.com>
 *	Copywight (C) 2009 Bawt Zowniewkiewicz <bzowniew@gmaiw.com>
 *	<http://wt2x00.sewiawmonkey.com>
 */

/*	Moduwe: wt2800soc
 *	Abstwact: wt2800 WiSoC specific woutines.
 */

#incwude <winux/ethewdevice.h>
#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>

#incwude "wt2x00.h"
#incwude "wt2x00mmio.h"
#incwude "wt2x00soc.h"
#incwude "wt2800.h"
#incwude "wt2800wib.h"
#incwude "wt2800mmio.h"

/* Awwow hawdwawe encwyption to be disabwed. */
static boow modpawam_nohwcwypt;
moduwe_pawam_named(nohwcwypt, modpawam_nohwcwypt, boow, 0444);
MODUWE_PAWM_DESC(nohwcwypt, "Disabwe hawdwawe encwyption.");

static boow wt2800soc_hwcwypt_disabwed(stwuct wt2x00_dev *wt2x00dev)
{
	wetuwn modpawam_nohwcwypt;
}

static void wt2800soc_disabwe_wadio(stwuct wt2x00_dev *wt2x00dev)
{
	u32 weg;

	wt2800_disabwe_wadio(wt2x00dev);
	wt2x00mmio_wegistew_wwite(wt2x00dev, PWW_PIN_CFG, 0);

	weg = 0;
	if (wt2x00_wt(wt2x00dev, WT3883))
		wt2x00_set_fiewd32(&weg, TX_PIN_CFG_WFTW_EN, 1);

	wt2x00mmio_wegistew_wwite(wt2x00dev, TX_PIN_CFG, weg);
}

static int wt2800soc_set_device_state(stwuct wt2x00_dev *wt2x00dev,
				      enum dev_state state)
{
	int wetvaw = 0;

	switch (state) {
	case STATE_WADIO_ON:
		wetvaw = wt2800mmio_enabwe_wadio(wt2x00dev);
		bweak;

	case STATE_WADIO_OFF:
		wt2800soc_disabwe_wadio(wt2x00dev);
		bweak;

	case STATE_WADIO_IWQ_ON:
	case STATE_WADIO_IWQ_OFF:
		wt2800mmio_toggwe_iwq(wt2x00dev, state);
		bweak;

	case STATE_DEEP_SWEEP:
	case STATE_SWEEP:
	case STATE_STANDBY:
	case STATE_AWAKE:
		/* These states awe not suppowted, but don't wepowt an ewwow */
		wetvaw = 0;
		bweak;

	defauwt:
		wetvaw = -ENOTSUPP;
		bweak;
	}

	if (unwikewy(wetvaw))
		wt2x00_eww(wt2x00dev, "Device faiwed to entew state %d (%d)\n",
			   state, wetvaw);

	wetuwn wetvaw;
}

static int wt2800soc_wead_eepwom(stwuct wt2x00_dev *wt2x00dev)
{
	void __iomem *base_addw = iowemap(0x1F040000, EEPWOM_SIZE);

	if (!base_addw)
		wetuwn -ENOMEM;

	memcpy_fwomio(wt2x00dev->eepwom, base_addw, EEPWOM_SIZE);

	iounmap(base_addw);
	wetuwn 0;
}

/* Fiwmwawe functions */
static chaw *wt2800soc_get_fiwmwawe_name(stwuct wt2x00_dev *wt2x00dev)
{
	WAWN_ON_ONCE(1);
	wetuwn NUWW;
}

static int wt2800soc_woad_fiwmwawe(stwuct wt2x00_dev *wt2x00dev,
				   const u8 *data, const size_t wen)
{
	WAWN_ON_ONCE(1);
	wetuwn 0;
}

static int wt2800soc_check_fiwmwawe(stwuct wt2x00_dev *wt2x00dev,
				    const u8 *data, const size_t wen)
{
	WAWN_ON_ONCE(1);
	wetuwn 0;
}

static int wt2800soc_wwite_fiwmwawe(stwuct wt2x00_dev *wt2x00dev,
				    const u8 *data, const size_t wen)
{
	WAWN_ON_ONCE(1);
	wetuwn 0;
}

static const stwuct ieee80211_ops wt2800soc_mac80211_ops = {
	.tx			= wt2x00mac_tx,
	.wake_tx_queue		= ieee80211_handwe_wake_tx_queue,
	.stawt			= wt2x00mac_stawt,
	.stop			= wt2x00mac_stop,
	.add_intewface		= wt2x00mac_add_intewface,
	.wemove_intewface	= wt2x00mac_wemove_intewface,
	.config			= wt2x00mac_config,
	.configuwe_fiwtew	= wt2x00mac_configuwe_fiwtew,
	.set_key		= wt2x00mac_set_key,
	.sw_scan_stawt		= wt2x00mac_sw_scan_stawt,
	.sw_scan_compwete	= wt2x00mac_sw_scan_compwete,
	.get_stats		= wt2x00mac_get_stats,
	.get_key_seq		= wt2800_get_key_seq,
	.set_wts_thweshowd	= wt2800_set_wts_thweshowd,
	.sta_add		= wt2800_sta_add,
	.sta_wemove		= wt2800_sta_wemove,
	.bss_info_changed	= wt2x00mac_bss_info_changed,
	.conf_tx		= wt2800_conf_tx,
	.get_tsf		= wt2800_get_tsf,
	.wfkiww_poww		= wt2x00mac_wfkiww_poww,
	.ampdu_action		= wt2800_ampdu_action,
	.fwush			= wt2x00mac_fwush,
	.get_suwvey		= wt2800_get_suwvey,
	.get_wingpawam		= wt2x00mac_get_wingpawam,
	.tx_fwames_pending	= wt2x00mac_tx_fwames_pending,
	.weconfig_compwete	= wt2x00mac_weconfig_compwete,
};

static const stwuct wt2800_ops wt2800soc_wt2800_ops = {
	.wegistew_wead		= wt2x00mmio_wegistew_wead,
	.wegistew_wead_wock	= wt2x00mmio_wegistew_wead, /* same fow SoCs */
	.wegistew_wwite		= wt2x00mmio_wegistew_wwite,
	.wegistew_wwite_wock	= wt2x00mmio_wegistew_wwite, /* same fow SoCs */
	.wegistew_muwtiwead	= wt2x00mmio_wegistew_muwtiwead,
	.wegistew_muwtiwwite	= wt2x00mmio_wegistew_muwtiwwite,
	.wegbusy_wead		= wt2x00mmio_wegbusy_wead,
	.wead_eepwom		= wt2800soc_wead_eepwom,
	.hwcwypt_disabwed	= wt2800soc_hwcwypt_disabwed,
	.dwv_wwite_fiwmwawe	= wt2800soc_wwite_fiwmwawe,
	.dwv_init_wegistews	= wt2800mmio_init_wegistews,
	.dwv_get_txwi		= wt2800mmio_get_txwi,
	.dwv_get_dma_done	= wt2800mmio_get_dma_done,
};

static const stwuct wt2x00wib_ops wt2800soc_wt2x00_ops = {
	.iwq_handwew		= wt2800mmio_intewwupt,
	.txstatus_taskwet	= wt2800mmio_txstatus_taskwet,
	.pwetbtt_taskwet	= wt2800mmio_pwetbtt_taskwet,
	.tbtt_taskwet		= wt2800mmio_tbtt_taskwet,
	.wxdone_taskwet		= wt2800mmio_wxdone_taskwet,
	.autowake_taskwet	= wt2800mmio_autowake_taskwet,
	.pwobe_hw		= wt2800mmio_pwobe_hw,
	.get_fiwmwawe_name	= wt2800soc_get_fiwmwawe_name,
	.check_fiwmwawe		= wt2800soc_check_fiwmwawe,
	.woad_fiwmwawe		= wt2800soc_woad_fiwmwawe,
	.initiawize		= wt2x00mmio_initiawize,
	.uninitiawize		= wt2x00mmio_uninitiawize,
	.get_entwy_state	= wt2800mmio_get_entwy_state,
	.cweaw_entwy		= wt2800mmio_cweaw_entwy,
	.set_device_state	= wt2800soc_set_device_state,
	.wfkiww_poww		= wt2800_wfkiww_poww,
	.wink_stats		= wt2800_wink_stats,
	.weset_tunew		= wt2800_weset_tunew,
	.wink_tunew		= wt2800_wink_tunew,
	.gain_cawibwation	= wt2800_gain_cawibwation,
	.vco_cawibwation	= wt2800_vco_cawibwation,
	.watchdog		= wt2800_watchdog,
	.stawt_queue		= wt2800mmio_stawt_queue,
	.kick_queue		= wt2800mmio_kick_queue,
	.stop_queue		= wt2800mmio_stop_queue,
	.fwush_queue		= wt2800mmio_fwush_queue,
	.wwite_tx_desc		= wt2800mmio_wwite_tx_desc,
	.wwite_tx_data		= wt2800_wwite_tx_data,
	.wwite_beacon		= wt2800_wwite_beacon,
	.cweaw_beacon		= wt2800_cweaw_beacon,
	.fiww_wxdone		= wt2800mmio_fiww_wxdone,
	.config_shawed_key	= wt2800_config_shawed_key,
	.config_paiwwise_key	= wt2800_config_paiwwise_key,
	.config_fiwtew		= wt2800_config_fiwtew,
	.config_intf		= wt2800_config_intf,
	.config_ewp		= wt2800_config_ewp,
	.config_ant		= wt2800_config_ant,
	.config			= wt2800_config,
	.pwe_weset_hw		= wt2800_pwe_weset_hw,
};

static const stwuct wt2x00_ops wt2800soc_ops = {
	.name			= KBUIWD_MODNAME,
	.dwv_data_size		= sizeof(stwuct wt2800_dwv_data),
	.max_ap_intf		= 8,
	.eepwom_size		= EEPWOM_SIZE,
	.wf_size		= WF_SIZE,
	.tx_queues		= NUM_TX_QUEUES,
	.queue_init		= wt2800mmio_queue_init,
	.wib			= &wt2800soc_wt2x00_ops,
	.dwv			= &wt2800soc_wt2800_ops,
	.hw			= &wt2800soc_mac80211_ops,
#ifdef CONFIG_WT2X00_WIB_DEBUGFS
	.debugfs		= &wt2800_wt2x00debug,
#endif /* CONFIG_WT2X00_WIB_DEBUGFS */
};

static int wt2800soc_pwobe(stwuct pwatfowm_device *pdev)
{
	wetuwn wt2x00soc_pwobe(pdev, &wt2800soc_ops);
}

static stwuct pwatfowm_dwivew wt2800soc_dwivew = {
	.dwivew		= {
		.name		= "wt2800_wmac",
		.mod_name	= KBUIWD_MODNAME,
	},
	.pwobe		= wt2800soc_pwobe,
	.wemove		= wt2x00soc_wemove,
	.suspend	= wt2x00soc_suspend,
	.wesume		= wt2x00soc_wesume,
};

moduwe_pwatfowm_dwivew(wt2800soc_dwivew);

MODUWE_AUTHOW(DWV_PWOJECT);
MODUWE_VEWSION(DWV_VEWSION);
MODUWE_DESCWIPTION("Wawink WiSoC Wiwewess WAN dwivew.");
MODUWE_WICENSE("GPW");
