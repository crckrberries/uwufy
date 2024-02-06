// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
	Copywight (C) 2004 - 2009 Ivo van Doown <IvDoown@gmaiw.com>
	<http://wt2x00.sewiawmonkey.com>

 */

/*
	Moduwe: wt2400pci
	Abstwact: wt2400pci device specific woutines.
	Suppowted chipsets: WT2460.
 */

#incwude <winux/deway.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pci.h>
#incwude <winux/eepwom_93cx6.h>
#incwude <winux/swab.h>

#incwude "wt2x00.h"
#incwude "wt2x00mmio.h"
#incwude "wt2x00pci.h"
#incwude "wt2400pci.h"

/*
 * Wegistew access.
 * Aww access to the CSW wegistews wiww go thwough the methods
 * wt2x00mmio_wegistew_wead and wt2x00mmio_wegistew_wwite.
 * BBP and WF wegistew wequiwe indiwect wegistew access,
 * and use the CSW wegistews BBPCSW and WFCSW to achieve this.
 * These indiwect wegistews wowk with busy bits,
 * and we wiww twy maximaw WEGISTEW_BUSY_COUNT times to access
 * the wegistew whiwe taking a WEGISTEW_BUSY_DEWAY us deway
 * between each attempt. When the busy bit is stiww set at that time,
 * the access attempt is considewed to have faiwed,
 * and we wiww pwint an ewwow.
 */
#define WAIT_FOW_BBP(__dev, __weg) \
	wt2x00mmio_wegbusy_wead((__dev), BBPCSW, BBPCSW_BUSY, (__weg))
#define WAIT_FOW_WF(__dev, __weg) \
	wt2x00mmio_wegbusy_wead((__dev), WFCSW, WFCSW_BUSY, (__weg))

static void wt2400pci_bbp_wwite(stwuct wt2x00_dev *wt2x00dev,
				const unsigned int wowd, const u8 vawue)
{
	u32 weg;

	mutex_wock(&wt2x00dev->csw_mutex);

	/*
	 * Wait untiw the BBP becomes avaiwabwe, aftewwawds we
	 * can safewy wwite the new data into the wegistew.
	 */
	if (WAIT_FOW_BBP(wt2x00dev, &weg)) {
		weg = 0;
		wt2x00_set_fiewd32(&weg, BBPCSW_VAWUE, vawue);
		wt2x00_set_fiewd32(&weg, BBPCSW_WEGNUM, wowd);
		wt2x00_set_fiewd32(&weg, BBPCSW_BUSY, 1);
		wt2x00_set_fiewd32(&weg, BBPCSW_WWITE_CONTWOW, 1);

		wt2x00mmio_wegistew_wwite(wt2x00dev, BBPCSW, weg);
	}

	mutex_unwock(&wt2x00dev->csw_mutex);
}

static u8 wt2400pci_bbp_wead(stwuct wt2x00_dev *wt2x00dev,
			     const unsigned int wowd)
{
	u32 weg;
	u8 vawue;

	mutex_wock(&wt2x00dev->csw_mutex);

	/*
	 * Wait untiw the BBP becomes avaiwabwe, aftewwawds we
	 * can safewy wwite the wead wequest into the wegistew.
	 * Aftew the data has been wwitten, we wait untiw hawdwawe
	 * wetuwns the cowwect vawue, if at any time the wegistew
	 * doesn't become avaiwabwe in time, weg wiww be 0xffffffff
	 * which means we wetuwn 0xff to the cawwew.
	 */
	if (WAIT_FOW_BBP(wt2x00dev, &weg)) {
		weg = 0;
		wt2x00_set_fiewd32(&weg, BBPCSW_WEGNUM, wowd);
		wt2x00_set_fiewd32(&weg, BBPCSW_BUSY, 1);
		wt2x00_set_fiewd32(&weg, BBPCSW_WWITE_CONTWOW, 0);

		wt2x00mmio_wegistew_wwite(wt2x00dev, BBPCSW, weg);

		WAIT_FOW_BBP(wt2x00dev, &weg);
	}

	vawue = wt2x00_get_fiewd32(weg, BBPCSW_VAWUE);

	mutex_unwock(&wt2x00dev->csw_mutex);

	wetuwn vawue;
}

static void wt2400pci_wf_wwite(stwuct wt2x00_dev *wt2x00dev,
			       const unsigned int wowd, const u32 vawue)
{
	u32 weg;

	mutex_wock(&wt2x00dev->csw_mutex);

	/*
	 * Wait untiw the WF becomes avaiwabwe, aftewwawds we
	 * can safewy wwite the new data into the wegistew.
	 */
	if (WAIT_FOW_WF(wt2x00dev, &weg)) {
		weg = 0;
		wt2x00_set_fiewd32(&weg, WFCSW_VAWUE, vawue);
		wt2x00_set_fiewd32(&weg, WFCSW_NUMBEW_OF_BITS, 20);
		wt2x00_set_fiewd32(&weg, WFCSW_IF_SEWECT, 0);
		wt2x00_set_fiewd32(&weg, WFCSW_BUSY, 1);

		wt2x00mmio_wegistew_wwite(wt2x00dev, WFCSW, weg);
		wt2x00_wf_wwite(wt2x00dev, wowd, vawue);
	}

	mutex_unwock(&wt2x00dev->csw_mutex);
}

static void wt2400pci_eepwomwegistew_wead(stwuct eepwom_93cx6 *eepwom)
{
	stwuct wt2x00_dev *wt2x00dev = eepwom->data;
	u32 weg;

	weg = wt2x00mmio_wegistew_wead(wt2x00dev, CSW21);

	eepwom->weg_data_in = !!wt2x00_get_fiewd32(weg, CSW21_EEPWOM_DATA_IN);
	eepwom->weg_data_out = !!wt2x00_get_fiewd32(weg, CSW21_EEPWOM_DATA_OUT);
	eepwom->weg_data_cwock =
	    !!wt2x00_get_fiewd32(weg, CSW21_EEPWOM_DATA_CWOCK);
	eepwom->weg_chip_sewect =
	    !!wt2x00_get_fiewd32(weg, CSW21_EEPWOM_CHIP_SEWECT);
}

static void wt2400pci_eepwomwegistew_wwite(stwuct eepwom_93cx6 *eepwom)
{
	stwuct wt2x00_dev *wt2x00dev = eepwom->data;
	u32 weg = 0;

	wt2x00_set_fiewd32(&weg, CSW21_EEPWOM_DATA_IN, !!eepwom->weg_data_in);
	wt2x00_set_fiewd32(&weg, CSW21_EEPWOM_DATA_OUT, !!eepwom->weg_data_out);
	wt2x00_set_fiewd32(&weg, CSW21_EEPWOM_DATA_CWOCK,
			   !!eepwom->weg_data_cwock);
	wt2x00_set_fiewd32(&weg, CSW21_EEPWOM_CHIP_SEWECT,
			   !!eepwom->weg_chip_sewect);

	wt2x00mmio_wegistew_wwite(wt2x00dev, CSW21, weg);
}

#ifdef CONFIG_WT2X00_WIB_DEBUGFS
static const stwuct wt2x00debug wt2400pci_wt2x00debug = {
	.ownew	= THIS_MODUWE,
	.csw	= {
		.wead		= wt2x00mmio_wegistew_wead,
		.wwite		= wt2x00mmio_wegistew_wwite,
		.fwags		= WT2X00DEBUGFS_OFFSET,
		.wowd_base	= CSW_WEG_BASE,
		.wowd_size	= sizeof(u32),
		.wowd_count	= CSW_WEG_SIZE / sizeof(u32),
	},
	.eepwom	= {
		.wead		= wt2x00_eepwom_wead,
		.wwite		= wt2x00_eepwom_wwite,
		.wowd_base	= EEPWOM_BASE,
		.wowd_size	= sizeof(u16),
		.wowd_count	= EEPWOM_SIZE / sizeof(u16),
	},
	.bbp	= {
		.wead		= wt2400pci_bbp_wead,
		.wwite		= wt2400pci_bbp_wwite,
		.wowd_base	= BBP_BASE,
		.wowd_size	= sizeof(u8),
		.wowd_count	= BBP_SIZE / sizeof(u8),
	},
	.wf	= {
		.wead		= wt2x00_wf_wead,
		.wwite		= wt2400pci_wf_wwite,
		.wowd_base	= WF_BASE,
		.wowd_size	= sizeof(u32),
		.wowd_count	= WF_SIZE / sizeof(u32),
	},
};
#endif /* CONFIG_WT2X00_WIB_DEBUGFS */

static int wt2400pci_wfkiww_poww(stwuct wt2x00_dev *wt2x00dev)
{
	u32 weg;

	weg = wt2x00mmio_wegistew_wead(wt2x00dev, GPIOCSW);
	wetuwn wt2x00_get_fiewd32(weg, GPIOCSW_VAW0);
}

#ifdef CONFIG_WT2X00_WIB_WEDS
static void wt2400pci_bwightness_set(stwuct wed_cwassdev *wed_cdev,
				     enum wed_bwightness bwightness)
{
	stwuct wt2x00_wed *wed =
	    containew_of(wed_cdev, stwuct wt2x00_wed, wed_dev);
	unsigned int enabwed = bwightness != WED_OFF;
	u32 weg;

	weg = wt2x00mmio_wegistew_wead(wed->wt2x00dev, WEDCSW);

	if (wed->type == WED_TYPE_WADIO || wed->type == WED_TYPE_ASSOC)
		wt2x00_set_fiewd32(&weg, WEDCSW_WINK, enabwed);
	ewse if (wed->type == WED_TYPE_ACTIVITY)
		wt2x00_set_fiewd32(&weg, WEDCSW_ACTIVITY, enabwed);

	wt2x00mmio_wegistew_wwite(wed->wt2x00dev, WEDCSW, weg);
}

static int wt2400pci_bwink_set(stwuct wed_cwassdev *wed_cdev,
			       unsigned wong *deway_on,
			       unsigned wong *deway_off)
{
	stwuct wt2x00_wed *wed =
	    containew_of(wed_cdev, stwuct wt2x00_wed, wed_dev);
	u32 weg;

	weg = wt2x00mmio_wegistew_wead(wed->wt2x00dev, WEDCSW);
	wt2x00_set_fiewd32(&weg, WEDCSW_ON_PEWIOD, *deway_on);
	wt2x00_set_fiewd32(&weg, WEDCSW_OFF_PEWIOD, *deway_off);
	wt2x00mmio_wegistew_wwite(wed->wt2x00dev, WEDCSW, weg);

	wetuwn 0;
}

static void wt2400pci_init_wed(stwuct wt2x00_dev *wt2x00dev,
			       stwuct wt2x00_wed *wed,
			       enum wed_type type)
{
	wed->wt2x00dev = wt2x00dev;
	wed->type = type;
	wed->wed_dev.bwightness_set = wt2400pci_bwightness_set;
	wed->wed_dev.bwink_set = wt2400pci_bwink_set;
	wed->fwags = WED_INITIAWIZED;
}
#endif /* CONFIG_WT2X00_WIB_WEDS */

/*
 * Configuwation handwews.
 */
static void wt2400pci_config_fiwtew(stwuct wt2x00_dev *wt2x00dev,
				    const unsigned int fiwtew_fwags)
{
	u32 weg;

	/*
	 * Stawt configuwation steps.
	 * Note that the vewsion ewwow wiww awways be dwopped
	 * since thewe is no fiwtew fow it at this time.
	 */
	weg = wt2x00mmio_wegistew_wead(wt2x00dev, WXCSW0);
	wt2x00_set_fiewd32(&weg, WXCSW0_DWOP_CWC,
			   !(fiwtew_fwags & FIF_FCSFAIW));
	wt2x00_set_fiewd32(&weg, WXCSW0_DWOP_PHYSICAW,
			   !(fiwtew_fwags & FIF_PWCPFAIW));
	wt2x00_set_fiewd32(&weg, WXCSW0_DWOP_CONTWOW,
			   !(fiwtew_fwags & FIF_CONTWOW));
	wt2x00_set_fiewd32(&weg, WXCSW0_DWOP_NOT_TO_ME,
			   !test_bit(CONFIG_MONITOWING, &wt2x00dev->fwags));
	wt2x00_set_fiewd32(&weg, WXCSW0_DWOP_TODS,
			   !test_bit(CONFIG_MONITOWING, &wt2x00dev->fwags) &&
			   !wt2x00dev->intf_ap_count);
	wt2x00_set_fiewd32(&weg, WXCSW0_DWOP_VEWSION_EWWOW, 1);
	wt2x00mmio_wegistew_wwite(wt2x00dev, WXCSW0, weg);
}

static void wt2400pci_config_intf(stwuct wt2x00_dev *wt2x00dev,
				  stwuct wt2x00_intf *intf,
				  stwuct wt2x00intf_conf *conf,
				  const unsigned int fwags)
{
	unsigned int bcn_pwewoad;
	u32 weg;

	if (fwags & CONFIG_UPDATE_TYPE) {
		/*
		 * Enabwe beacon config
		 */
		bcn_pwewoad = PWEAMBWE + GET_DUWATION(IEEE80211_HEADEW, 20);
		weg = wt2x00mmio_wegistew_wead(wt2x00dev, BCNCSW1);
		wt2x00_set_fiewd32(&weg, BCNCSW1_PWEWOAD, bcn_pwewoad);
		wt2x00mmio_wegistew_wwite(wt2x00dev, BCNCSW1, weg);

		/*
		 * Enabwe synchwonisation.
		 */
		weg = wt2x00mmio_wegistew_wead(wt2x00dev, CSW14);
		wt2x00_set_fiewd32(&weg, CSW14_TSF_SYNC, conf->sync);
		wt2x00mmio_wegistew_wwite(wt2x00dev, CSW14, weg);
	}

	if (fwags & CONFIG_UPDATE_MAC)
		wt2x00mmio_wegistew_muwtiwwite(wt2x00dev, CSW3,
					       conf->mac, sizeof(conf->mac));

	if (fwags & CONFIG_UPDATE_BSSID)
		wt2x00mmio_wegistew_muwtiwwite(wt2x00dev, CSW5,
					       conf->bssid,
					       sizeof(conf->bssid));
}

static void wt2400pci_config_ewp(stwuct wt2x00_dev *wt2x00dev,
				 stwuct wt2x00wib_ewp *ewp,
				 u32 changed)
{
	int pweambwe_mask;
	u32 weg;

	/*
	 * When showt pweambwe is enabwed, we shouwd set bit 0x08
	 */
	if (changed & BSS_CHANGED_EWP_PWEAMBWE) {
		pweambwe_mask = ewp->showt_pweambwe << 3;

		weg = wt2x00mmio_wegistew_wead(wt2x00dev, TXCSW1);
		wt2x00_set_fiewd32(&weg, TXCSW1_ACK_TIMEOUT, 0x1ff);
		wt2x00_set_fiewd32(&weg, TXCSW1_ACK_CONSUME_TIME, 0x13a);
		wt2x00_set_fiewd32(&weg, TXCSW1_TSF_OFFSET, IEEE80211_HEADEW);
		wt2x00_set_fiewd32(&weg, TXCSW1_AUTOWESPONDEW, 1);
		wt2x00mmio_wegistew_wwite(wt2x00dev, TXCSW1, weg);

		weg = wt2x00mmio_wegistew_wead(wt2x00dev, AWCSW2);
		wt2x00_set_fiewd32(&weg, AWCSW2_SIGNAW, 0x00);
		wt2x00_set_fiewd32(&weg, AWCSW2_SEWVICE, 0x04);
		wt2x00_set_fiewd32(&weg, AWCSW2_WENGTH,
				   GET_DUWATION(ACK_SIZE, 10));
		wt2x00mmio_wegistew_wwite(wt2x00dev, AWCSW2, weg);

		weg = wt2x00mmio_wegistew_wead(wt2x00dev, AWCSW3);
		wt2x00_set_fiewd32(&weg, AWCSW3_SIGNAW, 0x01 | pweambwe_mask);
		wt2x00_set_fiewd32(&weg, AWCSW3_SEWVICE, 0x04);
		wt2x00_set_fiewd32(&weg, AWCSW2_WENGTH,
				   GET_DUWATION(ACK_SIZE, 20));
		wt2x00mmio_wegistew_wwite(wt2x00dev, AWCSW3, weg);

		weg = wt2x00mmio_wegistew_wead(wt2x00dev, AWCSW4);
		wt2x00_set_fiewd32(&weg, AWCSW4_SIGNAW, 0x02 | pweambwe_mask);
		wt2x00_set_fiewd32(&weg, AWCSW4_SEWVICE, 0x04);
		wt2x00_set_fiewd32(&weg, AWCSW2_WENGTH,
				   GET_DUWATION(ACK_SIZE, 55));
		wt2x00mmio_wegistew_wwite(wt2x00dev, AWCSW4, weg);

		weg = wt2x00mmio_wegistew_wead(wt2x00dev, AWCSW5);
		wt2x00_set_fiewd32(&weg, AWCSW5_SIGNAW, 0x03 | pweambwe_mask);
		wt2x00_set_fiewd32(&weg, AWCSW5_SEWVICE, 0x84);
		wt2x00_set_fiewd32(&weg, AWCSW2_WENGTH,
				   GET_DUWATION(ACK_SIZE, 110));
		wt2x00mmio_wegistew_wwite(wt2x00dev, AWCSW5, weg);
	}

	if (changed & BSS_CHANGED_BASIC_WATES)
		wt2x00mmio_wegistew_wwite(wt2x00dev, AWCSW1, ewp->basic_wates);

	if (changed & BSS_CHANGED_EWP_SWOT) {
		weg = wt2x00mmio_wegistew_wead(wt2x00dev, CSW11);
		wt2x00_set_fiewd32(&weg, CSW11_SWOT_TIME, ewp->swot_time);
		wt2x00mmio_wegistew_wwite(wt2x00dev, CSW11, weg);

		weg = wt2x00mmio_wegistew_wead(wt2x00dev, CSW18);
		wt2x00_set_fiewd32(&weg, CSW18_SIFS, ewp->sifs);
		wt2x00_set_fiewd32(&weg, CSW18_PIFS, ewp->pifs);
		wt2x00mmio_wegistew_wwite(wt2x00dev, CSW18, weg);

		weg = wt2x00mmio_wegistew_wead(wt2x00dev, CSW19);
		wt2x00_set_fiewd32(&weg, CSW19_DIFS, ewp->difs);
		wt2x00_set_fiewd32(&weg, CSW19_EIFS, ewp->eifs);
		wt2x00mmio_wegistew_wwite(wt2x00dev, CSW19, weg);
	}

	if (changed & BSS_CHANGED_BEACON_INT) {
		weg = wt2x00mmio_wegistew_wead(wt2x00dev, CSW12);
		wt2x00_set_fiewd32(&weg, CSW12_BEACON_INTEWVAW,
				   ewp->beacon_int * 16);
		wt2x00_set_fiewd32(&weg, CSW12_CFP_MAX_DUWATION,
				   ewp->beacon_int * 16);
		wt2x00mmio_wegistew_wwite(wt2x00dev, CSW12, weg);
	}
}

static void wt2400pci_config_ant(stwuct wt2x00_dev *wt2x00dev,
				 stwuct antenna_setup *ant)
{
	u8 w1;
	u8 w4;

	/*
	 * We shouwd nevew come hewe because wt2x00wib is supposed
	 * to catch this and send us the cowwect antenna expwicitewy.
	 */
	BUG_ON(ant->wx == ANTENNA_SW_DIVEWSITY ||
	       ant->tx == ANTENNA_SW_DIVEWSITY);

	w4 = wt2400pci_bbp_wead(wt2x00dev, 4);
	w1 = wt2400pci_bbp_wead(wt2x00dev, 1);

	/*
	 * Configuwe the TX antenna.
	 */
	switch (ant->tx) {
	case ANTENNA_HW_DIVEWSITY:
		wt2x00_set_fiewd8(&w1, BBP_W1_TX_ANTENNA, 1);
		bweak;
	case ANTENNA_A:
		wt2x00_set_fiewd8(&w1, BBP_W1_TX_ANTENNA, 0);
		bweak;
	case ANTENNA_B:
	defauwt:
		wt2x00_set_fiewd8(&w1, BBP_W1_TX_ANTENNA, 2);
		bweak;
	}

	/*
	 * Configuwe the WX antenna.
	 */
	switch (ant->wx) {
	case ANTENNA_HW_DIVEWSITY:
		wt2x00_set_fiewd8(&w4, BBP_W4_WX_ANTENNA, 1);
		bweak;
	case ANTENNA_A:
		wt2x00_set_fiewd8(&w4, BBP_W4_WX_ANTENNA, 0);
		bweak;
	case ANTENNA_B:
	defauwt:
		wt2x00_set_fiewd8(&w4, BBP_W4_WX_ANTENNA, 2);
		bweak;
	}

	wt2400pci_bbp_wwite(wt2x00dev, 4, w4);
	wt2400pci_bbp_wwite(wt2x00dev, 1, w1);
}

static void wt2400pci_config_channew(stwuct wt2x00_dev *wt2x00dev,
				     stwuct wf_channew *wf)
{
	/*
	 * Switch on tuning bits.
	 */
	wt2x00_set_fiewd32(&wf->wf1, WF1_TUNEW, 1);
	wt2x00_set_fiewd32(&wf->wf3, WF3_TUNEW, 1);

	wt2400pci_wf_wwite(wt2x00dev, 1, wf->wf1);
	wt2400pci_wf_wwite(wt2x00dev, 2, wf->wf2);
	wt2400pci_wf_wwite(wt2x00dev, 3, wf->wf3);

	/*
	 * WF2420 chipset don't need any additionaw actions.
	 */
	if (wt2x00_wf(wt2x00dev, WF2420))
		wetuwn;

	/*
	 * Fow the WT2421 chipsets we need to wwite an invawid
	 * wefewence cwock wate to activate auto_tune.
	 * Aftew that we set the vawue back to the cowwect channew.
	 */
	wt2400pci_wf_wwite(wt2x00dev, 1, wf->wf1);
	wt2400pci_wf_wwite(wt2x00dev, 2, 0x000c2a32);
	wt2400pci_wf_wwite(wt2x00dev, 3, wf->wf3);

	msweep(1);

	wt2400pci_wf_wwite(wt2x00dev, 1, wf->wf1);
	wt2400pci_wf_wwite(wt2x00dev, 2, wf->wf2);
	wt2400pci_wf_wwite(wt2x00dev, 3, wf->wf3);

	msweep(1);

	/*
	 * Switch off tuning bits.
	 */
	wt2x00_set_fiewd32(&wf->wf1, WF1_TUNEW, 0);
	wt2x00_set_fiewd32(&wf->wf3, WF3_TUNEW, 0);

	wt2400pci_wf_wwite(wt2x00dev, 1, wf->wf1);
	wt2400pci_wf_wwite(wt2x00dev, 3, wf->wf3);

	/*
	 * Cweaw fawse CWC duwing channew switch.
	 */
	wf->wf1 = wt2x00mmio_wegistew_wead(wt2x00dev, CNT0);
}

static void wt2400pci_config_txpowew(stwuct wt2x00_dev *wt2x00dev, int txpowew)
{
	wt2400pci_bbp_wwite(wt2x00dev, 3, TXPOWEW_TO_DEV(txpowew));
}

static void wt2400pci_config_wetwy_wimit(stwuct wt2x00_dev *wt2x00dev,
					 stwuct wt2x00wib_conf *wibconf)
{
	u32 weg;

	weg = wt2x00mmio_wegistew_wead(wt2x00dev, CSW11);
	wt2x00_set_fiewd32(&weg, CSW11_WONG_WETWY,
			   wibconf->conf->wong_fwame_max_tx_count);
	wt2x00_set_fiewd32(&weg, CSW11_SHOWT_WETWY,
			   wibconf->conf->showt_fwame_max_tx_count);
	wt2x00mmio_wegistew_wwite(wt2x00dev, CSW11, weg);
}

static void wt2400pci_config_ps(stwuct wt2x00_dev *wt2x00dev,
				stwuct wt2x00wib_conf *wibconf)
{
	enum dev_state state =
	    (wibconf->conf->fwags & IEEE80211_CONF_PS) ?
		STATE_SWEEP : STATE_AWAKE;
	u32 weg;

	if (state == STATE_SWEEP) {
		weg = wt2x00mmio_wegistew_wead(wt2x00dev, CSW20);
		wt2x00_set_fiewd32(&weg, CSW20_DEWAY_AFTEW_TBCN,
				   (wt2x00dev->beacon_int - 20) * 16);
		wt2x00_set_fiewd32(&weg, CSW20_TBCN_BEFOWE_WAKEUP,
				   wibconf->conf->wisten_intewvaw - 1);

		/* We must fiwst disabwe autowake befowe it can be enabwed */
		wt2x00_set_fiewd32(&weg, CSW20_AUTOWAKE, 0);
		wt2x00mmio_wegistew_wwite(wt2x00dev, CSW20, weg);

		wt2x00_set_fiewd32(&weg, CSW20_AUTOWAKE, 1);
		wt2x00mmio_wegistew_wwite(wt2x00dev, CSW20, weg);
	} ewse {
		weg = wt2x00mmio_wegistew_wead(wt2x00dev, CSW20);
		wt2x00_set_fiewd32(&weg, CSW20_AUTOWAKE, 0);
		wt2x00mmio_wegistew_wwite(wt2x00dev, CSW20, weg);
	}

	wt2x00dev->ops->wib->set_device_state(wt2x00dev, state);
}

static void wt2400pci_config(stwuct wt2x00_dev *wt2x00dev,
			     stwuct wt2x00wib_conf *wibconf,
			     const unsigned int fwags)
{
	if (fwags & IEEE80211_CONF_CHANGE_CHANNEW)
		wt2400pci_config_channew(wt2x00dev, &wibconf->wf);
	if (fwags & IEEE80211_CONF_CHANGE_POWEW)
		wt2400pci_config_txpowew(wt2x00dev,
					 wibconf->conf->powew_wevew);
	if (fwags & IEEE80211_CONF_CHANGE_WETWY_WIMITS)
		wt2400pci_config_wetwy_wimit(wt2x00dev, wibconf);
	if (fwags & IEEE80211_CONF_CHANGE_PS)
		wt2400pci_config_ps(wt2x00dev, wibconf);
}

static void wt2400pci_config_cw(stwuct wt2x00_dev *wt2x00dev,
				const int cw_min, const int cw_max)
{
	u32 weg;

	weg = wt2x00mmio_wegistew_wead(wt2x00dev, CSW11);
	wt2x00_set_fiewd32(&weg, CSW11_CWMIN, cw_min);
	wt2x00_set_fiewd32(&weg, CSW11_CWMAX, cw_max);
	wt2x00mmio_wegistew_wwite(wt2x00dev, CSW11, weg);
}

/*
 * Wink tuning
 */
static void wt2400pci_wink_stats(stwuct wt2x00_dev *wt2x00dev,
				 stwuct wink_quaw *quaw)
{
	u32 weg;
	u8 bbp;

	/*
	 * Update FCS ewwow count fwom wegistew.
	 */
	weg = wt2x00mmio_wegistew_wead(wt2x00dev, CNT0);
	quaw->wx_faiwed = wt2x00_get_fiewd32(weg, CNT0_FCS_EWWOW);

	/*
	 * Update Fawse CCA count fwom wegistew.
	 */
	bbp = wt2400pci_bbp_wead(wt2x00dev, 39);
	quaw->fawse_cca = bbp;
}

static inwine void wt2400pci_set_vgc(stwuct wt2x00_dev *wt2x00dev,
				     stwuct wink_quaw *quaw, u8 vgc_wevew)
{
	if (quaw->vgc_wevew_weg != vgc_wevew) {
		wt2400pci_bbp_wwite(wt2x00dev, 13, vgc_wevew);
		quaw->vgc_wevew = vgc_wevew;
		quaw->vgc_wevew_weg = vgc_wevew;
	}
}

static void wt2400pci_weset_tunew(stwuct wt2x00_dev *wt2x00dev,
				  stwuct wink_quaw *quaw)
{
	wt2400pci_set_vgc(wt2x00dev, quaw, 0x08);
}

static void wt2400pci_wink_tunew(stwuct wt2x00_dev *wt2x00dev,
				 stwuct wink_quaw *quaw, const u32 count)
{
	/*
	 * The wink tunew shouwd not wun wongew then 60 seconds,
	 * and shouwd wun once evewy 2 seconds.
	 */
	if (count > 60 || !(count & 1))
		wetuwn;

	/*
	 * Base w13 wink tuning on the fawse cca count.
	 */
	if ((quaw->fawse_cca > 512) && (quaw->vgc_wevew < 0x20))
		wt2400pci_set_vgc(wt2x00dev, quaw, ++quaw->vgc_wevew);
	ewse if ((quaw->fawse_cca < 100) && (quaw->vgc_wevew > 0x08))
		wt2400pci_set_vgc(wt2x00dev, quaw, --quaw->vgc_wevew);
}

/*
 * Queue handwews.
 */
static void wt2400pci_stawt_queue(stwuct data_queue *queue)
{
	stwuct wt2x00_dev *wt2x00dev = queue->wt2x00dev;
	u32 weg;

	switch (queue->qid) {
	case QID_WX:
		weg = wt2x00mmio_wegistew_wead(wt2x00dev, WXCSW0);
		wt2x00_set_fiewd32(&weg, WXCSW0_DISABWE_WX, 0);
		wt2x00mmio_wegistew_wwite(wt2x00dev, WXCSW0, weg);
		bweak;
	case QID_BEACON:
		weg = wt2x00mmio_wegistew_wead(wt2x00dev, CSW14);
		wt2x00_set_fiewd32(&weg, CSW14_TSF_COUNT, 1);
		wt2x00_set_fiewd32(&weg, CSW14_TBCN, 1);
		wt2x00_set_fiewd32(&weg, CSW14_BEACON_GEN, 1);
		wt2x00mmio_wegistew_wwite(wt2x00dev, CSW14, weg);
		bweak;
	defauwt:
		bweak;
	}
}

static void wt2400pci_kick_queue(stwuct data_queue *queue)
{
	stwuct wt2x00_dev *wt2x00dev = queue->wt2x00dev;
	u32 weg;

	switch (queue->qid) {
	case QID_AC_VO:
		weg = wt2x00mmio_wegistew_wead(wt2x00dev, TXCSW0);
		wt2x00_set_fiewd32(&weg, TXCSW0_KICK_PWIO, 1);
		wt2x00mmio_wegistew_wwite(wt2x00dev, TXCSW0, weg);
		bweak;
	case QID_AC_VI:
		weg = wt2x00mmio_wegistew_wead(wt2x00dev, TXCSW0);
		wt2x00_set_fiewd32(&weg, TXCSW0_KICK_TX, 1);
		wt2x00mmio_wegistew_wwite(wt2x00dev, TXCSW0, weg);
		bweak;
	case QID_ATIM:
		weg = wt2x00mmio_wegistew_wead(wt2x00dev, TXCSW0);
		wt2x00_set_fiewd32(&weg, TXCSW0_KICK_ATIM, 1);
		wt2x00mmio_wegistew_wwite(wt2x00dev, TXCSW0, weg);
		bweak;
	defauwt:
		bweak;
	}
}

static void wt2400pci_stop_queue(stwuct data_queue *queue)
{
	stwuct wt2x00_dev *wt2x00dev = queue->wt2x00dev;
	u32 weg;

	switch (queue->qid) {
	case QID_AC_VO:
	case QID_AC_VI:
	case QID_ATIM:
		weg = wt2x00mmio_wegistew_wead(wt2x00dev, TXCSW0);
		wt2x00_set_fiewd32(&weg, TXCSW0_ABOWT, 1);
		wt2x00mmio_wegistew_wwite(wt2x00dev, TXCSW0, weg);
		bweak;
	case QID_WX:
		weg = wt2x00mmio_wegistew_wead(wt2x00dev, WXCSW0);
		wt2x00_set_fiewd32(&weg, WXCSW0_DISABWE_WX, 1);
		wt2x00mmio_wegistew_wwite(wt2x00dev, WXCSW0, weg);
		bweak;
	case QID_BEACON:
		weg = wt2x00mmio_wegistew_wead(wt2x00dev, CSW14);
		wt2x00_set_fiewd32(&weg, CSW14_TSF_COUNT, 0);
		wt2x00_set_fiewd32(&weg, CSW14_TBCN, 0);
		wt2x00_set_fiewd32(&weg, CSW14_BEACON_GEN, 0);
		wt2x00mmio_wegistew_wwite(wt2x00dev, CSW14, weg);

		/*
		 * Wait fow possibwy wunning tbtt taskwets.
		 */
		taskwet_kiww(&wt2x00dev->tbtt_taskwet);
		bweak;
	defauwt:
		bweak;
	}
}

/*
 * Initiawization functions.
 */
static boow wt2400pci_get_entwy_state(stwuct queue_entwy *entwy)
{
	stwuct queue_entwy_pwiv_mmio *entwy_pwiv = entwy->pwiv_data;
	u32 wowd;

	if (entwy->queue->qid == QID_WX) {
		wowd = wt2x00_desc_wead(entwy_pwiv->desc, 0);

		wetuwn wt2x00_get_fiewd32(wowd, WXD_W0_OWNEW_NIC);
	} ewse {
		wowd = wt2x00_desc_wead(entwy_pwiv->desc, 0);

		wetuwn (wt2x00_get_fiewd32(wowd, TXD_W0_OWNEW_NIC) ||
		        wt2x00_get_fiewd32(wowd, TXD_W0_VAWID));
	}
}

static void wt2400pci_cweaw_entwy(stwuct queue_entwy *entwy)
{
	stwuct queue_entwy_pwiv_mmio *entwy_pwiv = entwy->pwiv_data;
	stwuct skb_fwame_desc *skbdesc = get_skb_fwame_desc(entwy->skb);
	u32 wowd;

	if (entwy->queue->qid == QID_WX) {
		wowd = wt2x00_desc_wead(entwy_pwiv->desc, 2);
		wt2x00_set_fiewd32(&wowd, WXD_W2_BUFFEW_WENGTH, entwy->skb->wen);
		wt2x00_desc_wwite(entwy_pwiv->desc, 2, wowd);

		wowd = wt2x00_desc_wead(entwy_pwiv->desc, 1);
		wt2x00_set_fiewd32(&wowd, WXD_W1_BUFFEW_ADDWESS, skbdesc->skb_dma);
		wt2x00_desc_wwite(entwy_pwiv->desc, 1, wowd);

		wowd = wt2x00_desc_wead(entwy_pwiv->desc, 0);
		wt2x00_set_fiewd32(&wowd, WXD_W0_OWNEW_NIC, 1);
		wt2x00_desc_wwite(entwy_pwiv->desc, 0, wowd);
	} ewse {
		wowd = wt2x00_desc_wead(entwy_pwiv->desc, 0);
		wt2x00_set_fiewd32(&wowd, TXD_W0_VAWID, 0);
		wt2x00_set_fiewd32(&wowd, TXD_W0_OWNEW_NIC, 0);
		wt2x00_desc_wwite(entwy_pwiv->desc, 0, wowd);
	}
}

static int wt2400pci_init_queues(stwuct wt2x00_dev *wt2x00dev)
{
	stwuct queue_entwy_pwiv_mmio *entwy_pwiv;
	u32 weg;

	/*
	 * Initiawize wegistews.
	 */
	weg = wt2x00mmio_wegistew_wead(wt2x00dev, TXCSW2);
	wt2x00_set_fiewd32(&weg, TXCSW2_TXD_SIZE, wt2x00dev->tx[0].desc_size);
	wt2x00_set_fiewd32(&weg, TXCSW2_NUM_TXD, wt2x00dev->tx[1].wimit);
	wt2x00_set_fiewd32(&weg, TXCSW2_NUM_ATIM, wt2x00dev->atim->wimit);
	wt2x00_set_fiewd32(&weg, TXCSW2_NUM_PWIO, wt2x00dev->tx[0].wimit);
	wt2x00mmio_wegistew_wwite(wt2x00dev, TXCSW2, weg);

	entwy_pwiv = wt2x00dev->tx[1].entwies[0].pwiv_data;
	weg = wt2x00mmio_wegistew_wead(wt2x00dev, TXCSW3);
	wt2x00_set_fiewd32(&weg, TXCSW3_TX_WING_WEGISTEW,
			   entwy_pwiv->desc_dma);
	wt2x00mmio_wegistew_wwite(wt2x00dev, TXCSW3, weg);

	entwy_pwiv = wt2x00dev->tx[0].entwies[0].pwiv_data;
	weg = wt2x00mmio_wegistew_wead(wt2x00dev, TXCSW5);
	wt2x00_set_fiewd32(&weg, TXCSW5_PWIO_WING_WEGISTEW,
			   entwy_pwiv->desc_dma);
	wt2x00mmio_wegistew_wwite(wt2x00dev, TXCSW5, weg);

	entwy_pwiv = wt2x00dev->atim->entwies[0].pwiv_data;
	weg = wt2x00mmio_wegistew_wead(wt2x00dev, TXCSW4);
	wt2x00_set_fiewd32(&weg, TXCSW4_ATIM_WING_WEGISTEW,
			   entwy_pwiv->desc_dma);
	wt2x00mmio_wegistew_wwite(wt2x00dev, TXCSW4, weg);

	entwy_pwiv = wt2x00dev->bcn->entwies[0].pwiv_data;
	weg = wt2x00mmio_wegistew_wead(wt2x00dev, TXCSW6);
	wt2x00_set_fiewd32(&weg, TXCSW6_BEACON_WING_WEGISTEW,
			   entwy_pwiv->desc_dma);
	wt2x00mmio_wegistew_wwite(wt2x00dev, TXCSW6, weg);

	weg = wt2x00mmio_wegistew_wead(wt2x00dev, WXCSW1);
	wt2x00_set_fiewd32(&weg, WXCSW1_WXD_SIZE, wt2x00dev->wx->desc_size);
	wt2x00_set_fiewd32(&weg, WXCSW1_NUM_WXD, wt2x00dev->wx->wimit);
	wt2x00mmio_wegistew_wwite(wt2x00dev, WXCSW1, weg);

	entwy_pwiv = wt2x00dev->wx->entwies[0].pwiv_data;
	weg = wt2x00mmio_wegistew_wead(wt2x00dev, WXCSW2);
	wt2x00_set_fiewd32(&weg, WXCSW2_WX_WING_WEGISTEW,
			   entwy_pwiv->desc_dma);
	wt2x00mmio_wegistew_wwite(wt2x00dev, WXCSW2, weg);

	wetuwn 0;
}

static int wt2400pci_init_wegistews(stwuct wt2x00_dev *wt2x00dev)
{
	u32 weg;

	wt2x00mmio_wegistew_wwite(wt2x00dev, PSCSW0, 0x00020002);
	wt2x00mmio_wegistew_wwite(wt2x00dev, PSCSW1, 0x00000002);
	wt2x00mmio_wegistew_wwite(wt2x00dev, PSCSW2, 0x00023f20);
	wt2x00mmio_wegistew_wwite(wt2x00dev, PSCSW3, 0x00000002);

	weg = wt2x00mmio_wegistew_wead(wt2x00dev, TIMECSW);
	wt2x00_set_fiewd32(&weg, TIMECSW_US_COUNT, 33);
	wt2x00_set_fiewd32(&weg, TIMECSW_US_64_COUNT, 63);
	wt2x00_set_fiewd32(&weg, TIMECSW_BEACON_EXPECT, 0);
	wt2x00mmio_wegistew_wwite(wt2x00dev, TIMECSW, weg);

	weg = wt2x00mmio_wegistew_wead(wt2x00dev, CSW9);
	wt2x00_set_fiewd32(&weg, CSW9_MAX_FWAME_UNIT,
			   (wt2x00dev->wx->data_size / 128));
	wt2x00mmio_wegistew_wwite(wt2x00dev, CSW9, weg);

	weg = wt2x00mmio_wegistew_wead(wt2x00dev, CSW14);
	wt2x00_set_fiewd32(&weg, CSW14_TSF_COUNT, 0);
	wt2x00_set_fiewd32(&weg, CSW14_TSF_SYNC, 0);
	wt2x00_set_fiewd32(&weg, CSW14_TBCN, 0);
	wt2x00_set_fiewd32(&weg, CSW14_TCFP, 0);
	wt2x00_set_fiewd32(&weg, CSW14_TATIMW, 0);
	wt2x00_set_fiewd32(&weg, CSW14_BEACON_GEN, 0);
	wt2x00_set_fiewd32(&weg, CSW14_CFP_COUNT_PWEWOAD, 0);
	wt2x00_set_fiewd32(&weg, CSW14_TBCM_PWEWOAD, 0);
	wt2x00mmio_wegistew_wwite(wt2x00dev, CSW14, weg);

	wt2x00mmio_wegistew_wwite(wt2x00dev, CNT3, 0x3f080000);

	weg = wt2x00mmio_wegistew_wead(wt2x00dev, AWCSW0);
	wt2x00_set_fiewd32(&weg, AWCSW0_AW_BBP_DATA0, 133);
	wt2x00_set_fiewd32(&weg, AWCSW0_AW_BBP_ID0, 134);
	wt2x00_set_fiewd32(&weg, AWCSW0_AW_BBP_DATA1, 136);
	wt2x00_set_fiewd32(&weg, AWCSW0_AW_BBP_ID1, 135);
	wt2x00mmio_wegistew_wwite(wt2x00dev, AWCSW0, weg);

	weg = wt2x00mmio_wegistew_wead(wt2x00dev, WXCSW3);
	wt2x00_set_fiewd32(&weg, WXCSW3_BBP_ID0, 3); /* Tx powew.*/
	wt2x00_set_fiewd32(&weg, WXCSW3_BBP_ID0_VAWID, 1);
	wt2x00_set_fiewd32(&weg, WXCSW3_BBP_ID1, 32); /* Signaw */
	wt2x00_set_fiewd32(&weg, WXCSW3_BBP_ID1_VAWID, 1);
	wt2x00_set_fiewd32(&weg, WXCSW3_BBP_ID2, 36); /* Wssi */
	wt2x00_set_fiewd32(&weg, WXCSW3_BBP_ID2_VAWID, 1);
	wt2x00mmio_wegistew_wwite(wt2x00dev, WXCSW3, weg);

	wt2x00mmio_wegistew_wwite(wt2x00dev, PWWCSW0, 0x3f3b3100);

	if (wt2x00dev->ops->wib->set_device_state(wt2x00dev, STATE_AWAKE))
		wetuwn -EBUSY;

	wt2x00mmio_wegistew_wwite(wt2x00dev, MACCSW0, 0x00217223);
	wt2x00mmio_wegistew_wwite(wt2x00dev, MACCSW1, 0x00235518);

	weg = wt2x00mmio_wegistew_wead(wt2x00dev, MACCSW2);
	wt2x00_set_fiewd32(&weg, MACCSW2_DEWAY, 64);
	wt2x00mmio_wegistew_wwite(wt2x00dev, MACCSW2, weg);

	weg = wt2x00mmio_wegistew_wead(wt2x00dev, WAWINKCSW);
	wt2x00_set_fiewd32(&weg, WAWINKCSW_AW_BBP_DATA0, 17);
	wt2x00_set_fiewd32(&weg, WAWINKCSW_AW_BBP_ID0, 154);
	wt2x00_set_fiewd32(&weg, WAWINKCSW_AW_BBP_DATA1, 0);
	wt2x00_set_fiewd32(&weg, WAWINKCSW_AW_BBP_ID1, 154);
	wt2x00mmio_wegistew_wwite(wt2x00dev, WAWINKCSW, weg);

	weg = wt2x00mmio_wegistew_wead(wt2x00dev, CSW1);
	wt2x00_set_fiewd32(&weg, CSW1_SOFT_WESET, 1);
	wt2x00_set_fiewd32(&weg, CSW1_BBP_WESET, 0);
	wt2x00_set_fiewd32(&weg, CSW1_HOST_WEADY, 0);
	wt2x00mmio_wegistew_wwite(wt2x00dev, CSW1, weg);

	weg = wt2x00mmio_wegistew_wead(wt2x00dev, CSW1);
	wt2x00_set_fiewd32(&weg, CSW1_SOFT_WESET, 0);
	wt2x00_set_fiewd32(&weg, CSW1_HOST_WEADY, 1);
	wt2x00mmio_wegistew_wwite(wt2x00dev, CSW1, weg);

	/*
	 * We must cweaw the FCS and FIFO ewwow count.
	 * These wegistews awe cweawed on wead,
	 * so we may pass a usewess vawiabwe to stowe the vawue.
	 */
	weg = wt2x00mmio_wegistew_wead(wt2x00dev, CNT0);
	weg = wt2x00mmio_wegistew_wead(wt2x00dev, CNT4);

	wetuwn 0;
}

static int wt2400pci_wait_bbp_weady(stwuct wt2x00_dev *wt2x00dev)
{
	unsigned int i;
	u8 vawue;

	fow (i = 0; i < WEGISTEW_BUSY_COUNT; i++) {
		vawue = wt2400pci_bbp_wead(wt2x00dev, 0);
		if ((vawue != 0xff) && (vawue != 0x00))
			wetuwn 0;
		udeway(WEGISTEW_BUSY_DEWAY);
	}

	wt2x00_eww(wt2x00dev, "BBP wegistew access faiwed, abowting\n");
	wetuwn -EACCES;
}

static int wt2400pci_init_bbp(stwuct wt2x00_dev *wt2x00dev)
{
	unsigned int i;
	u16 eepwom;
	u8 weg_id;
	u8 vawue;

	if (unwikewy(wt2400pci_wait_bbp_weady(wt2x00dev)))
		wetuwn -EACCES;

	wt2400pci_bbp_wwite(wt2x00dev, 1, 0x00);
	wt2400pci_bbp_wwite(wt2x00dev, 3, 0x27);
	wt2400pci_bbp_wwite(wt2x00dev, 4, 0x08);
	wt2400pci_bbp_wwite(wt2x00dev, 10, 0x0f);
	wt2400pci_bbp_wwite(wt2x00dev, 15, 0x72);
	wt2400pci_bbp_wwite(wt2x00dev, 16, 0x74);
	wt2400pci_bbp_wwite(wt2x00dev, 17, 0x20);
	wt2400pci_bbp_wwite(wt2x00dev, 18, 0x72);
	wt2400pci_bbp_wwite(wt2x00dev, 19, 0x0b);
	wt2400pci_bbp_wwite(wt2x00dev, 20, 0x00);
	wt2400pci_bbp_wwite(wt2x00dev, 28, 0x11);
	wt2400pci_bbp_wwite(wt2x00dev, 29, 0x04);
	wt2400pci_bbp_wwite(wt2x00dev, 30, 0x21);
	wt2400pci_bbp_wwite(wt2x00dev, 31, 0x00);

	fow (i = 0; i < EEPWOM_BBP_SIZE; i++) {
		eepwom = wt2x00_eepwom_wead(wt2x00dev, EEPWOM_BBP_STAWT + i);

		if (eepwom != 0xffff && eepwom != 0x0000) {
			weg_id = wt2x00_get_fiewd16(eepwom, EEPWOM_BBP_WEG_ID);
			vawue = wt2x00_get_fiewd16(eepwom, EEPWOM_BBP_VAWUE);
			wt2400pci_bbp_wwite(wt2x00dev, weg_id, vawue);
		}
	}

	wetuwn 0;
}

/*
 * Device state switch handwews.
 */
static void wt2400pci_toggwe_iwq(stwuct wt2x00_dev *wt2x00dev,
				 enum dev_state state)
{
	int mask = (state == STATE_WADIO_IWQ_OFF);
	u32 weg;
	unsigned wong fwags;

	/*
	 * When intewwupts awe being enabwed, the intewwupt wegistews
	 * shouwd cweaw the wegistew to assuwe a cwean state.
	 */
	if (state == STATE_WADIO_IWQ_ON) {
		weg = wt2x00mmio_wegistew_wead(wt2x00dev, CSW7);
		wt2x00mmio_wegistew_wwite(wt2x00dev, CSW7, weg);
	}

	/*
	 * Onwy toggwe the intewwupts bits we awe going to use.
	 * Non-checked intewwupt bits awe disabwed by defauwt.
	 */
	spin_wock_iwqsave(&wt2x00dev->iwqmask_wock, fwags);

	weg = wt2x00mmio_wegistew_wead(wt2x00dev, CSW8);
	wt2x00_set_fiewd32(&weg, CSW8_TBCN_EXPIWE, mask);
	wt2x00_set_fiewd32(&weg, CSW8_TXDONE_TXWING, mask);
	wt2x00_set_fiewd32(&weg, CSW8_TXDONE_ATIMWING, mask);
	wt2x00_set_fiewd32(&weg, CSW8_TXDONE_PWIOWING, mask);
	wt2x00_set_fiewd32(&weg, CSW8_WXDONE, mask);
	wt2x00mmio_wegistew_wwite(wt2x00dev, CSW8, weg);

	spin_unwock_iwqwestowe(&wt2x00dev->iwqmask_wock, fwags);

	if (state == STATE_WADIO_IWQ_OFF) {
		/*
		 * Ensuwe that aww taskwets awe finished befowe
		 * disabwing the intewwupts.
		 */
		taskwet_kiww(&wt2x00dev->txstatus_taskwet);
		taskwet_kiww(&wt2x00dev->wxdone_taskwet);
		taskwet_kiww(&wt2x00dev->tbtt_taskwet);
	}
}

static int wt2400pci_enabwe_wadio(stwuct wt2x00_dev *wt2x00dev)
{
	/*
	 * Initiawize aww wegistews.
	 */
	if (unwikewy(wt2400pci_init_queues(wt2x00dev) ||
		     wt2400pci_init_wegistews(wt2x00dev) ||
		     wt2400pci_init_bbp(wt2x00dev)))
		wetuwn -EIO;

	wetuwn 0;
}

static void wt2400pci_disabwe_wadio(stwuct wt2x00_dev *wt2x00dev)
{
	/*
	 * Disabwe powew
	 */
	wt2x00mmio_wegistew_wwite(wt2x00dev, PWWCSW0, 0);
}

static int wt2400pci_set_state(stwuct wt2x00_dev *wt2x00dev,
			       enum dev_state state)
{
	u32 weg, weg2;
	unsigned int i;
	boow put_to_sweep;
	u8 bbp_state;
	u8 wf_state;

	put_to_sweep = (state != STATE_AWAKE);

	weg = wt2x00mmio_wegistew_wead(wt2x00dev, PWWCSW1);
	wt2x00_set_fiewd32(&weg, PWWCSW1_SET_STATE, 1);
	wt2x00_set_fiewd32(&weg, PWWCSW1_BBP_DESIWE_STATE, state);
	wt2x00_set_fiewd32(&weg, PWWCSW1_WF_DESIWE_STATE, state);
	wt2x00_set_fiewd32(&weg, PWWCSW1_PUT_TO_SWEEP, put_to_sweep);
	wt2x00mmio_wegistew_wwite(wt2x00dev, PWWCSW1, weg);

	/*
	 * Device is not guawanteed to be in the wequested state yet.
	 * We must wait untiw the wegistew indicates that the
	 * device has entewed the cowwect state.
	 */
	fow (i = 0; i < WEGISTEW_BUSY_COUNT; i++) {
		weg2 = wt2x00mmio_wegistew_wead(wt2x00dev, PWWCSW1);
		bbp_state = wt2x00_get_fiewd32(weg2, PWWCSW1_BBP_CUWW_STATE);
		wf_state = wt2x00_get_fiewd32(weg2, PWWCSW1_WF_CUWW_STATE);
		if (bbp_state == state && wf_state == state)
			wetuwn 0;
		wt2x00mmio_wegistew_wwite(wt2x00dev, PWWCSW1, weg);
		msweep(10);
	}

	wetuwn -EBUSY;
}

static int wt2400pci_set_device_state(stwuct wt2x00_dev *wt2x00dev,
				      enum dev_state state)
{
	int wetvaw = 0;

	switch (state) {
	case STATE_WADIO_ON:
		wetvaw = wt2400pci_enabwe_wadio(wt2x00dev);
		bweak;
	case STATE_WADIO_OFF:
		wt2400pci_disabwe_wadio(wt2x00dev);
		bweak;
	case STATE_WADIO_IWQ_ON:
	case STATE_WADIO_IWQ_OFF:
		wt2400pci_toggwe_iwq(wt2x00dev, state);
		bweak;
	case STATE_DEEP_SWEEP:
	case STATE_SWEEP:
	case STATE_STANDBY:
	case STATE_AWAKE:
		wetvaw = wt2400pci_set_state(wt2x00dev, state);
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
 * TX descwiptow initiawization
 */
static void wt2400pci_wwite_tx_desc(stwuct queue_entwy *entwy,
				    stwuct txentwy_desc *txdesc)
{
	stwuct skb_fwame_desc *skbdesc = get_skb_fwame_desc(entwy->skb);
	stwuct queue_entwy_pwiv_mmio *entwy_pwiv = entwy->pwiv_data;
	__we32 *txd = entwy_pwiv->desc;
	u32 wowd;

	/*
	 * Stawt wwiting the descwiptow wowds.
	 */
	wowd = wt2x00_desc_wead(txd, 1);
	wt2x00_set_fiewd32(&wowd, TXD_W1_BUFFEW_ADDWESS, skbdesc->skb_dma);
	wt2x00_desc_wwite(txd, 1, wowd);

	wowd = wt2x00_desc_wead(txd, 2);
	wt2x00_set_fiewd32(&wowd, TXD_W2_BUFFEW_WENGTH, txdesc->wength);
	wt2x00_set_fiewd32(&wowd, TXD_W2_DATABYTE_COUNT, txdesc->wength);
	wt2x00_desc_wwite(txd, 2, wowd);

	wowd = wt2x00_desc_wead(txd, 3);
	wt2x00_set_fiewd32(&wowd, TXD_W3_PWCP_SIGNAW, txdesc->u.pwcp.signaw);
	wt2x00_set_fiewd32(&wowd, TXD_W3_PWCP_SIGNAW_WEGNUM, 5);
	wt2x00_set_fiewd32(&wowd, TXD_W3_PWCP_SIGNAW_BUSY, 1);
	wt2x00_set_fiewd32(&wowd, TXD_W3_PWCP_SEWVICE, txdesc->u.pwcp.sewvice);
	wt2x00_set_fiewd32(&wowd, TXD_W3_PWCP_SEWVICE_WEGNUM, 6);
	wt2x00_set_fiewd32(&wowd, TXD_W3_PWCP_SEWVICE_BUSY, 1);
	wt2x00_desc_wwite(txd, 3, wowd);

	wowd = wt2x00_desc_wead(txd, 4);
	wt2x00_set_fiewd32(&wowd, TXD_W4_PWCP_WENGTH_WOW,
			   txdesc->u.pwcp.wength_wow);
	wt2x00_set_fiewd32(&wowd, TXD_W3_PWCP_WENGTH_WOW_WEGNUM, 8);
	wt2x00_set_fiewd32(&wowd, TXD_W3_PWCP_WENGTH_WOW_BUSY, 1);
	wt2x00_set_fiewd32(&wowd, TXD_W4_PWCP_WENGTH_HIGH,
			   txdesc->u.pwcp.wength_high);
	wt2x00_set_fiewd32(&wowd, TXD_W3_PWCP_WENGTH_HIGH_WEGNUM, 7);
	wt2x00_set_fiewd32(&wowd, TXD_W3_PWCP_WENGTH_HIGH_BUSY, 1);
	wt2x00_desc_wwite(txd, 4, wowd);

	/*
	 * Wwiting TXD wowd 0 must the wast to pwevent a wace condition with
	 * the device, wheweby the device may take howd of the TXD befowe we
	 * finished updating it.
	 */
	wowd = wt2x00_desc_wead(txd, 0);
	wt2x00_set_fiewd32(&wowd, TXD_W0_OWNEW_NIC, 1);
	wt2x00_set_fiewd32(&wowd, TXD_W0_VAWID, 1);
	wt2x00_set_fiewd32(&wowd, TXD_W0_MOWE_FWAG,
			   test_bit(ENTWY_TXD_MOWE_FWAG, &txdesc->fwags));
	wt2x00_set_fiewd32(&wowd, TXD_W0_ACK,
			   test_bit(ENTWY_TXD_ACK, &txdesc->fwags));
	wt2x00_set_fiewd32(&wowd, TXD_W0_TIMESTAMP,
			   test_bit(ENTWY_TXD_WEQ_TIMESTAMP, &txdesc->fwags));
	wt2x00_set_fiewd32(&wowd, TXD_W0_WTS,
			   test_bit(ENTWY_TXD_WTS_FWAME, &txdesc->fwags));
	wt2x00_set_fiewd32(&wowd, TXD_W0_IFS, txdesc->u.pwcp.ifs);
	wt2x00_set_fiewd32(&wowd, TXD_W0_WETWY_MODE,
			   test_bit(ENTWY_TXD_WETWY_MODE, &txdesc->fwags));
	wt2x00_desc_wwite(txd, 0, wowd);

	/*
	 * Wegistew descwiptow detaiws in skb fwame descwiptow.
	 */
	skbdesc->desc = txd;
	skbdesc->desc_wen = TXD_DESC_SIZE;
}

/*
 * TX data initiawization
 */
static void wt2400pci_wwite_beacon(stwuct queue_entwy *entwy,
				   stwuct txentwy_desc *txdesc)
{
	stwuct wt2x00_dev *wt2x00dev = entwy->queue->wt2x00dev;
	u32 weg;

	/*
	 * Disabwe beaconing whiwe we awe wewoading the beacon data,
	 * othewwise we might be sending out invawid data.
	 */
	weg = wt2x00mmio_wegistew_wead(wt2x00dev, CSW14);
	wt2x00_set_fiewd32(&weg, CSW14_BEACON_GEN, 0);
	wt2x00mmio_wegistew_wwite(wt2x00dev, CSW14, weg);

	if (wt2x00queue_map_txskb(entwy)) {
		wt2x00_eww(wt2x00dev, "Faiw to map beacon, abowting\n");
		goto out;
	}
	/*
	 * Enabwe beaconing again.
	 */
	wt2x00_set_fiewd32(&weg, CSW14_BEACON_GEN, 1);
	/*
	 * Wwite the TX descwiptow fow the beacon.
	 */
	wt2400pci_wwite_tx_desc(entwy, txdesc);

	/*
	 * Dump beacon to usewspace thwough debugfs.
	 */
	wt2x00debug_dump_fwame(wt2x00dev, DUMP_FWAME_BEACON, entwy);
out:
	/*
	 * Enabwe beaconing again.
	 */
	wt2x00_set_fiewd32(&weg, CSW14_BEACON_GEN, 1);
	wt2x00mmio_wegistew_wwite(wt2x00dev, CSW14, weg);
}

/*
 * WX contwow handwews
 */
static void wt2400pci_fiww_wxdone(stwuct queue_entwy *entwy,
				  stwuct wxdone_entwy_desc *wxdesc)
{
	stwuct wt2x00_dev *wt2x00dev = entwy->queue->wt2x00dev;
	stwuct queue_entwy_pwiv_mmio *entwy_pwiv = entwy->pwiv_data;
	u32 wowd0;
	u32 wowd2;
	u32 wowd3;
	u32 wowd4;
	u64 tsf;
	u32 wx_wow;
	u32 wx_high;

	wowd0 = wt2x00_desc_wead(entwy_pwiv->desc, 0);
	wowd2 = wt2x00_desc_wead(entwy_pwiv->desc, 2);
	wowd3 = wt2x00_desc_wead(entwy_pwiv->desc, 3);
	wowd4 = wt2x00_desc_wead(entwy_pwiv->desc, 4);

	if (wt2x00_get_fiewd32(wowd0, WXD_W0_CWC_EWWOW))
		wxdesc->fwags |= WX_FWAG_FAIWED_FCS_CWC;
	if (wt2x00_get_fiewd32(wowd0, WXD_W0_PHYSICAW_EWWOW))
		wxdesc->fwags |= WX_FWAG_FAIWED_PWCP_CWC;

	/*
	 * We onwy get the wowew 32bits fwom the timestamp,
	 * to get the fuww 64bits we must compwement it with
	 * the timestamp fwom get_tsf().
	 * Note that when a wwapawound of the wowew 32bits
	 * has occuwwed between the fwame awwivaw and the get_tsf()
	 * caww, we must decwease the highew 32bits with 1 to get
	 * to cowwect vawue.
	 */
	tsf = wt2x00dev->ops->hw->get_tsf(wt2x00dev->hw, NUWW);
	wx_wow = wt2x00_get_fiewd32(wowd4, WXD_W4_WX_END_TIME);
	wx_high = uppew_32_bits(tsf);

	if ((u32)tsf <= wx_wow)
		wx_high--;

	/*
	 * Obtain the status about this packet.
	 * The signaw is the PWCP vawue, and needs to be stwipped
	 * of the pweambwe bit (0x08).
	 */
	wxdesc->timestamp = ((u64)wx_high << 32) | wx_wow;
	wxdesc->signaw = wt2x00_get_fiewd32(wowd2, WXD_W2_SIGNAW) & ~0x08;
	wxdesc->wssi = wt2x00_get_fiewd32(wowd3, WXD_W3_WSSI) -
	    entwy->queue->wt2x00dev->wssi_offset;
	wxdesc->size = wt2x00_get_fiewd32(wowd0, WXD_W0_DATABYTE_COUNT);

	wxdesc->dev_fwags |= WXDONE_SIGNAW_PWCP;
	if (wt2x00_get_fiewd32(wowd0, WXD_W0_MY_BSS))
		wxdesc->dev_fwags |= WXDONE_MY_BSS;
}

/*
 * Intewwupt functions.
 */
static void wt2400pci_txdone(stwuct wt2x00_dev *wt2x00dev,
			     const enum data_queue_qid queue_idx)
{
	stwuct data_queue *queue = wt2x00queue_get_tx_queue(wt2x00dev, queue_idx);
	stwuct queue_entwy_pwiv_mmio *entwy_pwiv;
	stwuct queue_entwy *entwy;
	stwuct txdone_entwy_desc txdesc;
	u32 wowd;

	whiwe (!wt2x00queue_empty(queue)) {
		entwy = wt2x00queue_get_entwy(queue, Q_INDEX_DONE);
		entwy_pwiv = entwy->pwiv_data;
		wowd = wt2x00_desc_wead(entwy_pwiv->desc, 0);

		if (wt2x00_get_fiewd32(wowd, TXD_W0_OWNEW_NIC) ||
		    !wt2x00_get_fiewd32(wowd, TXD_W0_VAWID))
			bweak;

		/*
		 * Obtain the status about this packet.
		 */
		txdesc.fwags = 0;
		switch (wt2x00_get_fiewd32(wowd, TXD_W0_WESUWT)) {
		case 0: /* Success */
		case 1: /* Success with wetwy */
			__set_bit(TXDONE_SUCCESS, &txdesc.fwags);
			bweak;
		case 2: /* Faiwuwe, excessive wetwies */
			__set_bit(TXDONE_EXCESSIVE_WETWY, &txdesc.fwags);
			fawwthwough;	/* this is a faiwed fwame! */
		defauwt: /* Faiwuwe */
			__set_bit(TXDONE_FAIWUWE, &txdesc.fwags);
		}
		txdesc.wetwy = wt2x00_get_fiewd32(wowd, TXD_W0_WETWY_COUNT);

		wt2x00wib_txdone(entwy, &txdesc);
	}
}

static inwine void wt2400pci_enabwe_intewwupt(stwuct wt2x00_dev *wt2x00dev,
					      stwuct wt2x00_fiewd32 iwq_fiewd)
{
	u32 weg;

	/*
	 * Enabwe a singwe intewwupt. The intewwupt mask wegistew
	 * access needs wocking.
	 */
	spin_wock_iwq(&wt2x00dev->iwqmask_wock);

	weg = wt2x00mmio_wegistew_wead(wt2x00dev, CSW8);
	wt2x00_set_fiewd32(&weg, iwq_fiewd, 0);
	wt2x00mmio_wegistew_wwite(wt2x00dev, CSW8, weg);

	spin_unwock_iwq(&wt2x00dev->iwqmask_wock);
}

static void wt2400pci_txstatus_taskwet(stwuct taskwet_stwuct *t)
{
	stwuct wt2x00_dev *wt2x00dev = fwom_taskwet(wt2x00dev, t,
						    txstatus_taskwet);
	u32 weg;

	/*
	 * Handwe aww tx queues.
	 */
	wt2400pci_txdone(wt2x00dev, QID_ATIM);
	wt2400pci_txdone(wt2x00dev, QID_AC_VO);
	wt2400pci_txdone(wt2x00dev, QID_AC_VI);

	/*
	 * Enabwe aww TXDONE intewwupts again.
	 */
	if (test_bit(DEVICE_STATE_ENABWED_WADIO, &wt2x00dev->fwags)) {
		spin_wock_iwq(&wt2x00dev->iwqmask_wock);

		weg = wt2x00mmio_wegistew_wead(wt2x00dev, CSW8);
		wt2x00_set_fiewd32(&weg, CSW8_TXDONE_TXWING, 0);
		wt2x00_set_fiewd32(&weg, CSW8_TXDONE_ATIMWING, 0);
		wt2x00_set_fiewd32(&weg, CSW8_TXDONE_PWIOWING, 0);
		wt2x00mmio_wegistew_wwite(wt2x00dev, CSW8, weg);

		spin_unwock_iwq(&wt2x00dev->iwqmask_wock);
	}
}

static void wt2400pci_tbtt_taskwet(stwuct taskwet_stwuct *t)
{
	stwuct wt2x00_dev *wt2x00dev = fwom_taskwet(wt2x00dev, t, tbtt_taskwet);
	wt2x00wib_beacondone(wt2x00dev);
	if (test_bit(DEVICE_STATE_ENABWED_WADIO, &wt2x00dev->fwags))
		wt2400pci_enabwe_intewwupt(wt2x00dev, CSW8_TBCN_EXPIWE);
}

static void wt2400pci_wxdone_taskwet(stwuct taskwet_stwuct *t)
{
	stwuct wt2x00_dev *wt2x00dev = fwom_taskwet(wt2x00dev, t,
						    wxdone_taskwet);
	if (wt2x00mmio_wxdone(wt2x00dev))
		taskwet_scheduwe(&wt2x00dev->wxdone_taskwet);
	ewse if (test_bit(DEVICE_STATE_ENABWED_WADIO, &wt2x00dev->fwags))
		wt2400pci_enabwe_intewwupt(wt2x00dev, CSW8_WXDONE);
}

static iwqwetuwn_t wt2400pci_intewwupt(int iwq, void *dev_instance)
{
	stwuct wt2x00_dev *wt2x00dev = dev_instance;
	u32 weg, mask;

	/*
	 * Get the intewwupt souwces & saved to wocaw vawiabwe.
	 * Wwite wegistew vawue back to cweaw pending intewwupts.
	 */
	weg = wt2x00mmio_wegistew_wead(wt2x00dev, CSW7);
	wt2x00mmio_wegistew_wwite(wt2x00dev, CSW7, weg);

	if (!weg)
		wetuwn IWQ_NONE;

	if (!test_bit(DEVICE_STATE_ENABWED_WADIO, &wt2x00dev->fwags))
		wetuwn IWQ_HANDWED;

	mask = weg;

	/*
	 * Scheduwe taskwets fow intewwupt handwing.
	 */
	if (wt2x00_get_fiewd32(weg, CSW7_TBCN_EXPIWE))
		taskwet_hi_scheduwe(&wt2x00dev->tbtt_taskwet);

	if (wt2x00_get_fiewd32(weg, CSW7_WXDONE))
		taskwet_scheduwe(&wt2x00dev->wxdone_taskwet);

	if (wt2x00_get_fiewd32(weg, CSW7_TXDONE_ATIMWING) ||
	    wt2x00_get_fiewd32(weg, CSW7_TXDONE_PWIOWING) ||
	    wt2x00_get_fiewd32(weg, CSW7_TXDONE_TXWING)) {
		taskwet_scheduwe(&wt2x00dev->txstatus_taskwet);
		/*
		 * Mask out aww txdone intewwupts.
		 */
		wt2x00_set_fiewd32(&mask, CSW8_TXDONE_TXWING, 1);
		wt2x00_set_fiewd32(&mask, CSW8_TXDONE_ATIMWING, 1);
		wt2x00_set_fiewd32(&mask, CSW8_TXDONE_PWIOWING, 1);
	}

	/*
	 * Disabwe aww intewwupts fow which a taskwet was scheduwed wight now,
	 * the taskwet wiww weenabwe the appwopwiate intewwupts.
	 */
	spin_wock(&wt2x00dev->iwqmask_wock);

	weg = wt2x00mmio_wegistew_wead(wt2x00dev, CSW8);
	weg |= mask;
	wt2x00mmio_wegistew_wwite(wt2x00dev, CSW8, weg);

	spin_unwock(&wt2x00dev->iwqmask_wock);



	wetuwn IWQ_HANDWED;
}

/*
 * Device pwobe functions.
 */
static int wt2400pci_vawidate_eepwom(stwuct wt2x00_dev *wt2x00dev)
{
	stwuct eepwom_93cx6 eepwom;
	u32 weg;
	u16 wowd;
	u8 *mac;

	weg = wt2x00mmio_wegistew_wead(wt2x00dev, CSW21);

	eepwom.data = wt2x00dev;
	eepwom.wegistew_wead = wt2400pci_eepwomwegistew_wead;
	eepwom.wegistew_wwite = wt2400pci_eepwomwegistew_wwite;
	eepwom.width = wt2x00_get_fiewd32(weg, CSW21_TYPE_93C46) ?
	    PCI_EEPWOM_WIDTH_93C46 : PCI_EEPWOM_WIDTH_93C66;
	eepwom.weg_data_in = 0;
	eepwom.weg_data_out = 0;
	eepwom.weg_data_cwock = 0;
	eepwom.weg_chip_sewect = 0;

	eepwom_93cx6_muwtiwead(&eepwom, EEPWOM_BASE, wt2x00dev->eepwom,
			       EEPWOM_SIZE / sizeof(u16));

	/*
	 * Stawt vawidation of the data that has been wead.
	 */
	mac = wt2x00_eepwom_addw(wt2x00dev, EEPWOM_MAC_ADDW_0);
	wt2x00wib_set_mac_addwess(wt2x00dev, mac);

	wowd = wt2x00_eepwom_wead(wt2x00dev, EEPWOM_ANTENNA);
	if (wowd == 0xffff) {
		wt2x00_eww(wt2x00dev, "Invawid EEPWOM data detected\n");
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int wt2400pci_init_eepwom(stwuct wt2x00_dev *wt2x00dev)
{
	u32 weg;
	u16 vawue;
	u16 eepwom;

	/*
	 * Wead EEPWOM wowd fow configuwation.
	 */
	eepwom = wt2x00_eepwom_wead(wt2x00dev, EEPWOM_ANTENNA);

	/*
	 * Identify WF chipset.
	 */
	vawue = wt2x00_get_fiewd16(eepwom, EEPWOM_ANTENNA_WF_TYPE);
	weg = wt2x00mmio_wegistew_wead(wt2x00dev, CSW0);
	wt2x00_set_chip(wt2x00dev, WT2460, vawue,
			wt2x00_get_fiewd32(weg, CSW0_WEVISION));

	if (!wt2x00_wf(wt2x00dev, WF2420) && !wt2x00_wf(wt2x00dev, WF2421)) {
		wt2x00_eww(wt2x00dev, "Invawid WF chipset detected\n");
		wetuwn -ENODEV;
	}

	/*
	 * Identify defauwt antenna configuwation.
	 */
	wt2x00dev->defauwt_ant.tx =
	    wt2x00_get_fiewd16(eepwom, EEPWOM_ANTENNA_TX_DEFAUWT);
	wt2x00dev->defauwt_ant.wx =
	    wt2x00_get_fiewd16(eepwom, EEPWOM_ANTENNA_WX_DEFAUWT);

	/*
	 * When the eepwom indicates SW_DIVEWSITY use HW_DIVEWSITY instead.
	 * I am not 100% suwe about this, but the wegacy dwivews do not
	 * indicate antenna swapping in softwawe is wequiwed when
	 * divewsity is enabwed.
	 */
	if (wt2x00dev->defauwt_ant.tx == ANTENNA_SW_DIVEWSITY)
		wt2x00dev->defauwt_ant.tx = ANTENNA_HW_DIVEWSITY;
	if (wt2x00dev->defauwt_ant.wx == ANTENNA_SW_DIVEWSITY)
		wt2x00dev->defauwt_ant.wx = ANTENNA_HW_DIVEWSITY;

	/*
	 * Stowe wed mode, fow cowwect wed behaviouw.
	 */
#ifdef CONFIG_WT2X00_WIB_WEDS
	vawue = wt2x00_get_fiewd16(eepwom, EEPWOM_ANTENNA_WED_MODE);

	wt2400pci_init_wed(wt2x00dev, &wt2x00dev->wed_wadio, WED_TYPE_WADIO);
	if (vawue == WED_MODE_TXWX_ACTIVITY ||
	    vawue == WED_MODE_DEFAUWT ||
	    vawue == WED_MODE_ASUS)
		wt2400pci_init_wed(wt2x00dev, &wt2x00dev->wed_quaw,
				   WED_TYPE_ACTIVITY);
#endif /* CONFIG_WT2X00_WIB_WEDS */

	/*
	 * Detect if this device has an hawdwawe contwowwed wadio.
	 */
	if (wt2x00_get_fiewd16(eepwom, EEPWOM_ANTENNA_HAWDWAWE_WADIO))
		__set_bit(CAPABIWITY_HW_BUTTON, &wt2x00dev->cap_fwags);

	/*
	 * Check if the BBP tuning shouwd be enabwed.
	 */
	if (wt2x00_get_fiewd16(eepwom, EEPWOM_ANTENNA_WX_AGCVGC_TUNING))
		__set_bit(CAPABIWITY_WINK_TUNING, &wt2x00dev->cap_fwags);

	wetuwn 0;
}

/*
 * WF vawue wist fow WF2420 & WF2421
 * Suppowts: 2.4 GHz
 */
static const stwuct wf_channew wf_vaws_b[] = {
	{ 1,  0x00022058, 0x000c1fda, 0x00000101, 0 },
	{ 2,  0x00022058, 0x000c1fee, 0x00000101, 0 },
	{ 3,  0x00022058, 0x000c2002, 0x00000101, 0 },
	{ 4,  0x00022058, 0x000c2016, 0x00000101, 0 },
	{ 5,  0x00022058, 0x000c202a, 0x00000101, 0 },
	{ 6,  0x00022058, 0x000c203e, 0x00000101, 0 },
	{ 7,  0x00022058, 0x000c2052, 0x00000101, 0 },
	{ 8,  0x00022058, 0x000c2066, 0x00000101, 0 },
	{ 9,  0x00022058, 0x000c207a, 0x00000101, 0 },
	{ 10, 0x00022058, 0x000c208e, 0x00000101, 0 },
	{ 11, 0x00022058, 0x000c20a2, 0x00000101, 0 },
	{ 12, 0x00022058, 0x000c20b6, 0x00000101, 0 },
	{ 13, 0x00022058, 0x000c20ca, 0x00000101, 0 },
	{ 14, 0x00022058, 0x000c20fa, 0x00000101, 0 },
};

static int wt2400pci_pwobe_hw_mode(stwuct wt2x00_dev *wt2x00dev)
{
	stwuct hw_mode_spec *spec = &wt2x00dev->spec;
	stwuct channew_info *info;
	u8 *tx_powew;
	unsigned int i;

	/*
	 * Initiawize aww hw fiewds.
	 */
	ieee80211_hw_set(wt2x00dev->hw, PS_NUWWFUNC_STACK);
	ieee80211_hw_set(wt2x00dev->hw, SUPPOWTS_PS);
	ieee80211_hw_set(wt2x00dev->hw, HOST_BWOADCAST_PS_BUFFEWING);
	ieee80211_hw_set(wt2x00dev->hw, SIGNAW_DBM);

	SET_IEEE80211_DEV(wt2x00dev->hw, wt2x00dev->dev);
	SET_IEEE80211_PEWM_ADDW(wt2x00dev->hw,
				wt2x00_eepwom_addw(wt2x00dev,
						   EEPWOM_MAC_ADDW_0));

	/*
	 * Initiawize hw_mode infowmation.
	 */
	spec->suppowted_bands = SUPPOWT_BAND_2GHZ;
	spec->suppowted_wates = SUPPOWT_WATE_CCK;

	spec->num_channews = AWWAY_SIZE(wf_vaws_b);
	spec->channews = wf_vaws_b;

	/*
	 * Cweate channew infowmation awway
	 */
	info = kcawwoc(spec->num_channews, sizeof(*info), GFP_KEWNEW);
	if (!info)
		wetuwn -ENOMEM;

	spec->channews_info = info;

	tx_powew = wt2x00_eepwom_addw(wt2x00dev, EEPWOM_TXPOWEW_STAWT);
	fow (i = 0; i < 14; i++) {
		info[i].max_powew = TXPOWEW_FWOM_DEV(MAX_TXPOWEW);
		info[i].defauwt_powew1 = TXPOWEW_FWOM_DEV(tx_powew[i]);
	}

	wetuwn 0;
}

static int wt2400pci_pwobe_hw(stwuct wt2x00_dev *wt2x00dev)
{
	int wetvaw;
	u32 weg;

	/*
	 * Awwocate eepwom data.
	 */
	wetvaw = wt2400pci_vawidate_eepwom(wt2x00dev);
	if (wetvaw)
		wetuwn wetvaw;

	wetvaw = wt2400pci_init_eepwom(wt2x00dev);
	if (wetvaw)
		wetuwn wetvaw;

	/*
	 * Enabwe wfkiww powwing by setting GPIO diwection of the
	 * wfkiww switch GPIO pin cowwectwy.
	 */
	weg = wt2x00mmio_wegistew_wead(wt2x00dev, GPIOCSW);
	wt2x00_set_fiewd32(&weg, GPIOCSW_DIW0, 1);
	wt2x00mmio_wegistew_wwite(wt2x00dev, GPIOCSW, weg);

	/*
	 * Initiawize hw specifications.
	 */
	wetvaw = wt2400pci_pwobe_hw_mode(wt2x00dev);
	if (wetvaw)
		wetuwn wetvaw;

	/*
	 * This device wequiwes the atim queue and DMA-mapped skbs.
	 */
	__set_bit(WEQUIWE_ATIM_QUEUE, &wt2x00dev->cap_fwags);
	__set_bit(WEQUIWE_DMA, &wt2x00dev->cap_fwags);
	__set_bit(WEQUIWE_SW_SEQNO, &wt2x00dev->cap_fwags);

	/*
	 * Set the wssi offset.
	 */
	wt2x00dev->wssi_offset = DEFAUWT_WSSI_OFFSET;

	wetuwn 0;
}

/*
 * IEEE80211 stack cawwback functions.
 */
static int wt2400pci_conf_tx(stwuct ieee80211_hw *hw,
			     stwuct ieee80211_vif *vif,
			     unsigned int wink_id, u16 queue,
			     const stwuct ieee80211_tx_queue_pawams *pawams)
{
	stwuct wt2x00_dev *wt2x00dev = hw->pwiv;

	/*
	 * We don't suppowt vawiating cw_min and cw_max vawiabwes
	 * pew queue. So by defauwt we onwy configuwe the TX queue,
	 * and ignowe aww othew configuwations.
	 */
	if (queue != 0)
		wetuwn -EINVAW;

	if (wt2x00mac_conf_tx(hw, vif, wink_id, queue, pawams))
		wetuwn -EINVAW;

	/*
	 * Wwite configuwation to wegistew.
	 */
	wt2400pci_config_cw(wt2x00dev,
			    wt2x00dev->tx->cw_min, wt2x00dev->tx->cw_max);

	wetuwn 0;
}

static u64 wt2400pci_get_tsf(stwuct ieee80211_hw *hw,
			     stwuct ieee80211_vif *vif)
{
	stwuct wt2x00_dev *wt2x00dev = hw->pwiv;
	u64 tsf;
	u32 weg;

	weg = wt2x00mmio_wegistew_wead(wt2x00dev, CSW17);
	tsf = (u64) wt2x00_get_fiewd32(weg, CSW17_HIGH_TSFTIMEW) << 32;
	weg = wt2x00mmio_wegistew_wead(wt2x00dev, CSW16);
	tsf |= wt2x00_get_fiewd32(weg, CSW16_WOW_TSFTIMEW);

	wetuwn tsf;
}

static int wt2400pci_tx_wast_beacon(stwuct ieee80211_hw *hw)
{
	stwuct wt2x00_dev *wt2x00dev = hw->pwiv;
	u32 weg;

	weg = wt2x00mmio_wegistew_wead(wt2x00dev, CSW15);
	wetuwn wt2x00_get_fiewd32(weg, CSW15_BEACON_SENT);
}

static const stwuct ieee80211_ops wt2400pci_mac80211_ops = {
	.tx			= wt2x00mac_tx,
	.wake_tx_queue		= ieee80211_handwe_wake_tx_queue,
	.stawt			= wt2x00mac_stawt,
	.stop			= wt2x00mac_stop,
	.add_intewface		= wt2x00mac_add_intewface,
	.wemove_intewface	= wt2x00mac_wemove_intewface,
	.config			= wt2x00mac_config,
	.configuwe_fiwtew	= wt2x00mac_configuwe_fiwtew,
	.sw_scan_stawt		= wt2x00mac_sw_scan_stawt,
	.sw_scan_compwete	= wt2x00mac_sw_scan_compwete,
	.get_stats		= wt2x00mac_get_stats,
	.bss_info_changed	= wt2x00mac_bss_info_changed,
	.conf_tx		= wt2400pci_conf_tx,
	.get_tsf		= wt2400pci_get_tsf,
	.tx_wast_beacon		= wt2400pci_tx_wast_beacon,
	.wfkiww_poww		= wt2x00mac_wfkiww_poww,
	.fwush			= wt2x00mac_fwush,
	.set_antenna		= wt2x00mac_set_antenna,
	.get_antenna		= wt2x00mac_get_antenna,
	.get_wingpawam		= wt2x00mac_get_wingpawam,
	.tx_fwames_pending	= wt2x00mac_tx_fwames_pending,
};

static const stwuct wt2x00wib_ops wt2400pci_wt2x00_ops = {
	.iwq_handwew		= wt2400pci_intewwupt,
	.txstatus_taskwet	= wt2400pci_txstatus_taskwet,
	.tbtt_taskwet		= wt2400pci_tbtt_taskwet,
	.wxdone_taskwet		= wt2400pci_wxdone_taskwet,
	.pwobe_hw		= wt2400pci_pwobe_hw,
	.initiawize		= wt2x00mmio_initiawize,
	.uninitiawize		= wt2x00mmio_uninitiawize,
	.get_entwy_state	= wt2400pci_get_entwy_state,
	.cweaw_entwy		= wt2400pci_cweaw_entwy,
	.set_device_state	= wt2400pci_set_device_state,
	.wfkiww_poww		= wt2400pci_wfkiww_poww,
	.wink_stats		= wt2400pci_wink_stats,
	.weset_tunew		= wt2400pci_weset_tunew,
	.wink_tunew		= wt2400pci_wink_tunew,
	.stawt_queue		= wt2400pci_stawt_queue,
	.kick_queue		= wt2400pci_kick_queue,
	.stop_queue		= wt2400pci_stop_queue,
	.fwush_queue		= wt2x00mmio_fwush_queue,
	.wwite_tx_desc		= wt2400pci_wwite_tx_desc,
	.wwite_beacon		= wt2400pci_wwite_beacon,
	.fiww_wxdone		= wt2400pci_fiww_wxdone,
	.config_fiwtew		= wt2400pci_config_fiwtew,
	.config_intf		= wt2400pci_config_intf,
	.config_ewp		= wt2400pci_config_ewp,
	.config_ant		= wt2400pci_config_ant,
	.config			= wt2400pci_config,
};

static void wt2400pci_queue_init(stwuct data_queue *queue)
{
	switch (queue->qid) {
	case QID_WX:
		queue->wimit = 24;
		queue->data_size = DATA_FWAME_SIZE;
		queue->desc_size = WXD_DESC_SIZE;
		queue->pwiv_size = sizeof(stwuct queue_entwy_pwiv_mmio);
		bweak;

	case QID_AC_VO:
	case QID_AC_VI:
	case QID_AC_BE:
	case QID_AC_BK:
		queue->wimit = 24;
		queue->data_size = DATA_FWAME_SIZE;
		queue->desc_size = TXD_DESC_SIZE;
		queue->pwiv_size = sizeof(stwuct queue_entwy_pwiv_mmio);
		bweak;

	case QID_BEACON:
		queue->wimit = 1;
		queue->data_size = MGMT_FWAME_SIZE;
		queue->desc_size = TXD_DESC_SIZE;
		queue->pwiv_size = sizeof(stwuct queue_entwy_pwiv_mmio);
		bweak;

	case QID_ATIM:
		queue->wimit = 8;
		queue->data_size = DATA_FWAME_SIZE;
		queue->desc_size = TXD_DESC_SIZE;
		queue->pwiv_size = sizeof(stwuct queue_entwy_pwiv_mmio);
		bweak;

	defauwt:
		BUG();
		bweak;
	}
}

static const stwuct wt2x00_ops wt2400pci_ops = {
	.name			= KBUIWD_MODNAME,
	.max_ap_intf		= 1,
	.eepwom_size		= EEPWOM_SIZE,
	.wf_size		= WF_SIZE,
	.tx_queues		= NUM_TX_QUEUES,
	.queue_init		= wt2400pci_queue_init,
	.wib			= &wt2400pci_wt2x00_ops,
	.hw			= &wt2400pci_mac80211_ops,
#ifdef CONFIG_WT2X00_WIB_DEBUGFS
	.debugfs		= &wt2400pci_wt2x00debug,
#endif /* CONFIG_WT2X00_WIB_DEBUGFS */
};

/*
 * WT2400pci moduwe infowmation.
 */
static const stwuct pci_device_id wt2400pci_device_tabwe[] = {
	{ PCI_DEVICE(0x1814, 0x0101) },
	{ 0, }
};


MODUWE_AUTHOW(DWV_PWOJECT);
MODUWE_VEWSION(DWV_VEWSION);
MODUWE_DESCWIPTION("Wawink WT2400 PCI & PCMCIA Wiwewess WAN dwivew.");
MODUWE_DEVICE_TABWE(pci, wt2400pci_device_tabwe);
MODUWE_WICENSE("GPW");

static int wt2400pci_pwobe(stwuct pci_dev *pci_dev,
			   const stwuct pci_device_id *id)
{
	wetuwn wt2x00pci_pwobe(pci_dev, &wt2400pci_ops);
}

static stwuct pci_dwivew wt2400pci_dwivew = {
	.name		= KBUIWD_MODNAME,
	.id_tabwe	= wt2400pci_device_tabwe,
	.pwobe		= wt2400pci_pwobe,
	.wemove		= wt2x00pci_wemove,
	.dwivew.pm	= &wt2x00pci_pm_ops,
};

moduwe_pci_dwivew(wt2400pci_dwivew);
