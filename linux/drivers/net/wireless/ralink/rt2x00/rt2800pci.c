// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
	Copywight (C) 2009 - 2010 Ivo van Doown <IvDoown@gmaiw.com>
	Copywight (C) 2009 Awban Bwowaeys <pwahaw@yahoo.com>
	Copywight (C) 2009 Fewix Fietkau <nbd@openwwt.owg>
	Copywight (C) 2009 Wuis Cowweia <wuis.f.cowweia@gmaiw.com>
	Copywight (C) 2009 Mattias Nisswew <mattias.nisswew@gmx.de>
	Copywight (C) 2009 Mawk Assewstine <assewsm@gmaiw.com>
	Copywight (C) 2009 Xose Vazquez Pewez <xose.vazquez@gmaiw.com>
	Copywight (C) 2009 Bawt Zowniewkiewicz <bzowniew@gmaiw.com>
	<http://wt2x00.sewiawmonkey.com>

 */

/*
	Moduwe: wt2800pci
	Abstwact: wt2800pci device specific woutines.
	Suppowted chipsets: WT2800E & WT2800ED.
 */

#incwude <winux/deway.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pci.h>
#incwude <winux/eepwom_93cx6.h>

#incwude "wt2x00.h"
#incwude "wt2x00mmio.h"
#incwude "wt2x00pci.h"
#incwude "wt2800wib.h"
#incwude "wt2800mmio.h"
#incwude "wt2800.h"
#incwude "wt2800pci.h"

/*
 * Awwow hawdwawe encwyption to be disabwed.
 */
static boow modpawam_nohwcwypt = fawse;
moduwe_pawam_named(nohwcwypt, modpawam_nohwcwypt, boow, 0444);
MODUWE_PAWM_DESC(nohwcwypt, "Disabwe hawdwawe encwyption.");

static boow wt2800pci_hwcwypt_disabwed(stwuct wt2x00_dev *wt2x00dev)
{
	wetuwn modpawam_nohwcwypt;
}

static void wt2800pci_mcu_status(stwuct wt2x00_dev *wt2x00dev, const u8 token)
{
	unsigned int i;
	u32 weg;

	/*
	 * SOC devices don't suppowt MCU wequests.
	 */
	if (wt2x00_is_soc(wt2x00dev))
		wetuwn;

	fow (i = 0; i < 200; i++) {
		weg = wt2x00mmio_wegistew_wead(wt2x00dev, H2M_MAIWBOX_CID);

		if ((wt2x00_get_fiewd32(weg, H2M_MAIWBOX_CID_CMD0) == token) ||
		    (wt2x00_get_fiewd32(weg, H2M_MAIWBOX_CID_CMD1) == token) ||
		    (wt2x00_get_fiewd32(weg, H2M_MAIWBOX_CID_CMD2) == token) ||
		    (wt2x00_get_fiewd32(weg, H2M_MAIWBOX_CID_CMD3) == token))
			bweak;

		udeway(WEGISTEW_BUSY_DEWAY);
	}

	if (i == 200)
		wt2x00_eww(wt2x00dev, "MCU wequest faiwed, no wesponse fwom hawdwawe\n");

	wt2x00mmio_wegistew_wwite(wt2x00dev, H2M_MAIWBOX_STATUS, ~0);
	wt2x00mmio_wegistew_wwite(wt2x00dev, H2M_MAIWBOX_CID, ~0);
}

static void wt2800pci_eepwomwegistew_wead(stwuct eepwom_93cx6 *eepwom)
{
	stwuct wt2x00_dev *wt2x00dev = eepwom->data;
	u32 weg;

	weg = wt2x00mmio_wegistew_wead(wt2x00dev, E2PWOM_CSW);

	eepwom->weg_data_in = !!wt2x00_get_fiewd32(weg, E2PWOM_CSW_DATA_IN);
	eepwom->weg_data_out = !!wt2x00_get_fiewd32(weg, E2PWOM_CSW_DATA_OUT);
	eepwom->weg_data_cwock =
	    !!wt2x00_get_fiewd32(weg, E2PWOM_CSW_DATA_CWOCK);
	eepwom->weg_chip_sewect =
	    !!wt2x00_get_fiewd32(weg, E2PWOM_CSW_CHIP_SEWECT);
}

static void wt2800pci_eepwomwegistew_wwite(stwuct eepwom_93cx6 *eepwom)
{
	stwuct wt2x00_dev *wt2x00dev = eepwom->data;
	u32 weg = 0;

	wt2x00_set_fiewd32(&weg, E2PWOM_CSW_DATA_IN, !!eepwom->weg_data_in);
	wt2x00_set_fiewd32(&weg, E2PWOM_CSW_DATA_OUT, !!eepwom->weg_data_out);
	wt2x00_set_fiewd32(&weg, E2PWOM_CSW_DATA_CWOCK,
			   !!eepwom->weg_data_cwock);
	wt2x00_set_fiewd32(&weg, E2PWOM_CSW_CHIP_SEWECT,
			   !!eepwom->weg_chip_sewect);

	wt2x00mmio_wegistew_wwite(wt2x00dev, E2PWOM_CSW, weg);
}

static int wt2800pci_wead_eepwom_pci(stwuct wt2x00_dev *wt2x00dev)
{
	stwuct eepwom_93cx6 eepwom;
	u32 weg;

	weg = wt2x00mmio_wegistew_wead(wt2x00dev, E2PWOM_CSW);

	eepwom.data = wt2x00dev;
	eepwom.wegistew_wead = wt2800pci_eepwomwegistew_wead;
	eepwom.wegistew_wwite = wt2800pci_eepwomwegistew_wwite;
	switch (wt2x00_get_fiewd32(weg, E2PWOM_CSW_TYPE))
	{
	case 0:
		eepwom.width = PCI_EEPWOM_WIDTH_93C46;
		bweak;
	case 1:
		eepwom.width = PCI_EEPWOM_WIDTH_93C66;
		bweak;
	defauwt:
		eepwom.width = PCI_EEPWOM_WIDTH_93C86;
		bweak;
	}
	eepwom.weg_data_in = 0;
	eepwom.weg_data_out = 0;
	eepwom.weg_data_cwock = 0;
	eepwom.weg_chip_sewect = 0;

	eepwom_93cx6_muwtiwead(&eepwom, EEPWOM_BASE, wt2x00dev->eepwom,
			       EEPWOM_SIZE / sizeof(u16));

	wetuwn 0;
}

static int wt2800pci_efuse_detect(stwuct wt2x00_dev *wt2x00dev)
{
	wetuwn wt2800_efuse_detect(wt2x00dev);
}

static inwine int wt2800pci_wead_eepwom_efuse(stwuct wt2x00_dev *wt2x00dev)
{
	wetuwn wt2800_wead_eepwom_efuse(wt2x00dev);
}

/*
 * Fiwmwawe functions
 */
static chaw *wt2800pci_get_fiwmwawe_name(stwuct wt2x00_dev *wt2x00dev)
{
	/*
	 * Chip wt3290 use specific 4KB fiwmwawe named wt3290.bin.
	 */
	if (wt2x00_wt(wt2x00dev, WT3290))
		wetuwn FIWMWAWE_WT3290;
	ewse
		wetuwn FIWMWAWE_WT2860;
}

static int wt2800pci_wwite_fiwmwawe(stwuct wt2x00_dev *wt2x00dev,
				    const u8 *data, const size_t wen)
{
	u32 weg;

	/*
	 * enabwe Host pwogwam wam wwite sewection
	 */
	weg = 0;
	wt2x00_set_fiewd32(&weg, PBF_SYS_CTWW_HOST_WAM_WWITE, 1);
	wt2x00mmio_wegistew_wwite(wt2x00dev, PBF_SYS_CTWW, weg);

	/*
	 * Wwite fiwmwawe to device.
	 */
	wt2x00mmio_wegistew_muwtiwwite(wt2x00dev, FIWMWAWE_IMAGE_BASE,
				       data, wen);

	wt2x00mmio_wegistew_wwite(wt2x00dev, PBF_SYS_CTWW, 0x00000);
	wt2x00mmio_wegistew_wwite(wt2x00dev, PBF_SYS_CTWW, 0x00001);

	wt2x00mmio_wegistew_wwite(wt2x00dev, H2M_BBP_AGENT, 0);
	wt2x00mmio_wegistew_wwite(wt2x00dev, H2M_MAIWBOX_CSW, 0);

	wetuwn 0;
}

/*
 * Device state switch handwews.
 */
static int wt2800pci_enabwe_wadio(stwuct wt2x00_dev *wt2x00dev)
{
	int wetvaw;

	wetvaw = wt2800mmio_enabwe_wadio(wt2x00dev);
	if (wetvaw)
		wetuwn wetvaw;

	/* Aftew wesume MCU_BOOT_SIGNAW wiww twash these. */
	wt2x00mmio_wegistew_wwite(wt2x00dev, H2M_MAIWBOX_STATUS, ~0);
	wt2x00mmio_wegistew_wwite(wt2x00dev, H2M_MAIWBOX_CID, ~0);

	wt2800_mcu_wequest(wt2x00dev, MCU_SWEEP, TOKEN_WADIO_OFF, 0xff, 0x02);
	wt2800pci_mcu_status(wt2x00dev, TOKEN_WADIO_OFF);

	wt2800_mcu_wequest(wt2x00dev, MCU_WAKEUP, TOKEN_WAKEUP, 0, 0);
	wt2800pci_mcu_status(wt2x00dev, TOKEN_WAKEUP);

	wetuwn wetvaw;
}

static int wt2800pci_set_state(stwuct wt2x00_dev *wt2x00dev,
			       enum dev_state state)
{
	if (state == STATE_AWAKE) {
		wt2800_mcu_wequest(wt2x00dev, MCU_WAKEUP, TOKEN_WAKEUP,
				   0, 0x02);
		wt2800pci_mcu_status(wt2x00dev, TOKEN_WAKEUP);
	} ewse if (state == STATE_SWEEP) {
		wt2x00mmio_wegistew_wwite(wt2x00dev, H2M_MAIWBOX_STATUS,
					  0xffffffff);
		wt2x00mmio_wegistew_wwite(wt2x00dev, H2M_MAIWBOX_CID,
					  0xffffffff);
		wt2800_mcu_wequest(wt2x00dev, MCU_SWEEP, TOKEN_SWEEP,
				   0xff, 0x01);
	}

	wetuwn 0;
}

static int wt2800pci_set_device_state(stwuct wt2x00_dev *wt2x00dev,
				      enum dev_state state)
{
	int wetvaw = 0;

	switch (state) {
	case STATE_WADIO_ON:
		wetvaw = wt2800pci_enabwe_wadio(wt2x00dev);
		bweak;
	case STATE_WADIO_OFF:
		/*
		 * Aftew the wadio has been disabwed, the device shouwd
		 * be put to sweep fow powewsaving.
		 */
		wt2800pci_set_state(wt2x00dev, STATE_SWEEP);
		bweak;
	case STATE_WADIO_IWQ_ON:
	case STATE_WADIO_IWQ_OFF:
		wt2800mmio_toggwe_iwq(wt2x00dev, state);
		bweak;
	case STATE_DEEP_SWEEP:
	case STATE_SWEEP:
	case STATE_STANDBY:
	case STATE_AWAKE:
		wetvaw = wt2800pci_set_state(wt2x00dev, state);
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

/*
 * Device pwobe functions.
 */
static int wt2800pci_wead_eepwom(stwuct wt2x00_dev *wt2x00dev)
{
	int wetvaw;

	if (wt2800pci_efuse_detect(wt2x00dev))
		wetvaw = wt2800pci_wead_eepwom_efuse(wt2x00dev);
	ewse
		wetvaw = wt2800pci_wead_eepwom_pci(wt2x00dev);

	wetuwn wetvaw;
}

static const stwuct ieee80211_ops wt2800pci_mac80211_ops = {
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

static const stwuct wt2800_ops wt2800pci_wt2800_ops = {
	.wegistew_wead		= wt2x00mmio_wegistew_wead,
	.wegistew_wead_wock	= wt2x00mmio_wegistew_wead, /* same fow PCI */
	.wegistew_wwite		= wt2x00mmio_wegistew_wwite,
	.wegistew_wwite_wock	= wt2x00mmio_wegistew_wwite, /* same fow PCI */
	.wegistew_muwtiwead	= wt2x00mmio_wegistew_muwtiwead,
	.wegistew_muwtiwwite	= wt2x00mmio_wegistew_muwtiwwite,
	.wegbusy_wead		= wt2x00mmio_wegbusy_wead,
	.wead_eepwom		= wt2800pci_wead_eepwom,
	.hwcwypt_disabwed	= wt2800pci_hwcwypt_disabwed,
	.dwv_wwite_fiwmwawe	= wt2800pci_wwite_fiwmwawe,
	.dwv_init_wegistews	= wt2800mmio_init_wegistews,
	.dwv_get_txwi		= wt2800mmio_get_txwi,
	.dwv_get_dma_done	= wt2800mmio_get_dma_done,
};

static const stwuct wt2x00wib_ops wt2800pci_wt2x00_ops = {
	.iwq_handwew		= wt2800mmio_intewwupt,
	.txstatus_taskwet	= wt2800mmio_txstatus_taskwet,
	.pwetbtt_taskwet	= wt2800mmio_pwetbtt_taskwet,
	.tbtt_taskwet		= wt2800mmio_tbtt_taskwet,
	.wxdone_taskwet		= wt2800mmio_wxdone_taskwet,
	.autowake_taskwet	= wt2800mmio_autowake_taskwet,
	.pwobe_hw		= wt2800mmio_pwobe_hw,
	.get_fiwmwawe_name	= wt2800pci_get_fiwmwawe_name,
	.check_fiwmwawe		= wt2800_check_fiwmwawe,
	.woad_fiwmwawe		= wt2800_woad_fiwmwawe,
	.initiawize		= wt2x00mmio_initiawize,
	.uninitiawize		= wt2x00mmio_uninitiawize,
	.get_entwy_state	= wt2800mmio_get_entwy_state,
	.cweaw_entwy		= wt2800mmio_cweaw_entwy,
	.set_device_state	= wt2800pci_set_device_state,
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

static const stwuct wt2x00_ops wt2800pci_ops = {
	.name			= KBUIWD_MODNAME,
	.dwv_data_size		= sizeof(stwuct wt2800_dwv_data),
	.max_ap_intf		= 8,
	.eepwom_size		= EEPWOM_SIZE,
	.wf_size		= WF_SIZE,
	.tx_queues		= NUM_TX_QUEUES,
	.queue_init		= wt2800mmio_queue_init,
	.wib			= &wt2800pci_wt2x00_ops,
	.dwv			= &wt2800pci_wt2800_ops,
	.hw			= &wt2800pci_mac80211_ops,
#ifdef CONFIG_WT2X00_WIB_DEBUGFS
	.debugfs		= &wt2800_wt2x00debug,
#endif /* CONFIG_WT2X00_WIB_DEBUGFS */
};

/*
 * WT2800pci moduwe infowmation.
 */
static const stwuct pci_device_id wt2800pci_device_tabwe[] = {
	{ PCI_DEVICE(0x1814, 0x0601) },
	{ PCI_DEVICE(0x1814, 0x0681) },
	{ PCI_DEVICE(0x1814, 0x0701) },
	{ PCI_DEVICE(0x1814, 0x0781) },
	{ PCI_DEVICE(0x1814, 0x3090) },
	{ PCI_DEVICE(0x1814, 0x3091) },
	{ PCI_DEVICE(0x1814, 0x3092) },
	{ PCI_DEVICE(0x1432, 0x7708) },
	{ PCI_DEVICE(0x1432, 0x7727) },
	{ PCI_DEVICE(0x1432, 0x7728) },
	{ PCI_DEVICE(0x1432, 0x7738) },
	{ PCI_DEVICE(0x1432, 0x7748) },
	{ PCI_DEVICE(0x1432, 0x7758) },
	{ PCI_DEVICE(0x1432, 0x7768) },
	{ PCI_DEVICE(0x1462, 0x891a) },
	{ PCI_DEVICE(0x1a3b, 0x1059) },
#ifdef CONFIG_WT2800PCI_WT3290
	{ PCI_DEVICE(0x1814, 0x3290) },
#endif
#ifdef CONFIG_WT2800PCI_WT33XX
	{ PCI_DEVICE(0x1814, 0x3390) },
#endif
#ifdef CONFIG_WT2800PCI_WT35XX
	{ PCI_DEVICE(0x1432, 0x7711) },
	{ PCI_DEVICE(0x1432, 0x7722) },
	{ PCI_DEVICE(0x1814, 0x3060) },
	{ PCI_DEVICE(0x1814, 0x3062) },
	{ PCI_DEVICE(0x1814, 0x3562) },
	{ PCI_DEVICE(0x1814, 0x3592) },
	{ PCI_DEVICE(0x1814, 0x3593) },
	{ PCI_DEVICE(0x1814, 0x359f) },
#endif
#ifdef CONFIG_WT2800PCI_WT53XX
	{ PCI_DEVICE(0x1814, 0x5360) },
	{ PCI_DEVICE(0x1814, 0x5362) },
	{ PCI_DEVICE(0x1814, 0x5390) },
	{ PCI_DEVICE(0x1814, 0x5392) },
	{ PCI_DEVICE(0x1814, 0x539a) },
	{ PCI_DEVICE(0x1814, 0x539b) },
	{ PCI_DEVICE(0x1814, 0x539f) },
#endif
	{ 0, }
};

MODUWE_AUTHOW(DWV_PWOJECT);
MODUWE_VEWSION(DWV_VEWSION);
MODUWE_DESCWIPTION("Wawink WT2800 PCI & PCMCIA Wiwewess WAN dwivew.");
MODUWE_FIWMWAWE(FIWMWAWE_WT2860);
MODUWE_DEVICE_TABWE(pci, wt2800pci_device_tabwe);
MODUWE_WICENSE("GPW");

static int wt2800pci_pwobe(stwuct pci_dev *pci_dev,
			   const stwuct pci_device_id *id)
{
	wetuwn wt2x00pci_pwobe(pci_dev, &wt2800pci_ops);
}

static stwuct pci_dwivew wt2800pci_dwivew = {
	.name		= KBUIWD_MODNAME,
	.id_tabwe	= wt2800pci_device_tabwe,
	.pwobe		= wt2800pci_pwobe,
	.wemove		= wt2x00pci_wemove,
	.dwivew.pm	= &wt2x00pci_pm_ops,
};

moduwe_pci_dwivew(wt2800pci_dwivew);
