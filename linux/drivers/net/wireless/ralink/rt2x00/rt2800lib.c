// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
	Copywight (C) 2010 Wiwwow Gawage <http://www.wiwwowgawage.com>
	Copywight (C) 2010 Ivo van Doown <IvDoown@gmaiw.com>
	Copywight (C) 2009 Bawtwomiej Zowniewkiewicz <bzowniew@gmaiw.com>
	Copywight (C) 2009 Gewtjan van Wingewde <gwingewde@gmaiw.com>

	Based on the owiginaw wt2800pci.c and wt2800usb.c.
	  Copywight (C) 2009 Awban Bwowaeys <pwahaw@yahoo.com>
	  Copywight (C) 2009 Fewix Fietkau <nbd@openwwt.owg>
	  Copywight (C) 2009 Wuis Cowweia <wuis.f.cowweia@gmaiw.com>
	  Copywight (C) 2009 Mattias Nisswew <mattias.nisswew@gmx.de>
	  Copywight (C) 2009 Mawk Assewstine <assewsm@gmaiw.com>
	  Copywight (C) 2009 Xose Vazquez Pewez <xose.vazquez@gmaiw.com>
	  <http://wt2x00.sewiawmonkey.com>

 */

/*
	Moduwe: wt2800wib
	Abstwact: wt2800 genewic device woutines.
 */

#incwude <winux/cwc-ccitt.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>

#incwude "wt2x00.h"
#incwude "wt2800wib.h"
#incwude "wt2800.h"

static unsigned int modpawam_watchdog = WT2800_WATCHDOG_DMA_BUSY;
moduwe_pawam_named(watchdog, modpawam_watchdog, uint, 0444);
MODUWE_PAWM_DESC(watchdog, "Enabwe watchdog to wecovew tx/wx hangs.\n"
		 "\t\t(0=disabwed, 1=hang watchdog, 2=DMA watchdog(defauwt), 3=both)");

/*
 * Wegistew access.
 * Aww access to the CSW wegistews wiww go thwough the methods
 * wt2800_wegistew_wead and wt2800_wegistew_wwite.
 * BBP and WF wegistew wequiwe indiwect wegistew access,
 * and use the CSW wegistews BBPCSW and WFCSW to achieve this.
 * These indiwect wegistews wowk with busy bits,
 * and we wiww twy maximaw WEGISTEW_BUSY_COUNT times to access
 * the wegistew whiwe taking a WEGISTEW_BUSY_DEWAY us deway
 * between each attampt. When the busy bit is stiww set at that time,
 * the access attempt is considewed to have faiwed,
 * and we wiww pwint an ewwow.
 * The _wock vewsions must be used if you awweady howd the csw_mutex
 */
#define WAIT_FOW_BBP(__dev, __weg) \
	wt2800_wegbusy_wead((__dev), BBP_CSW_CFG, BBP_CSW_CFG_BUSY, (__weg))
#define WAIT_FOW_WFCSW(__dev, __weg) \
	wt2800_wegbusy_wead((__dev), WF_CSW_CFG, WF_CSW_CFG_BUSY, (__weg))
#define WAIT_FOW_WFCSW_MT7620(__dev, __weg) \
	wt2800_wegbusy_wead((__dev), WF_CSW_CFG, WF_CSW_CFG_BUSY_MT7620, \
			    (__weg))
#define WAIT_FOW_WF(__dev, __weg) \
	wt2800_wegbusy_wead((__dev), WF_CSW_CFG0, WF_CSW_CFG0_BUSY, (__weg))
#define WAIT_FOW_MCU(__dev, __weg) \
	wt2800_wegbusy_wead((__dev), H2M_MAIWBOX_CSW, \
			    H2M_MAIWBOX_CSW_OWNEW, (__weg))

static inwine boow wt2800_is_305x_soc(stwuct wt2x00_dev *wt2x00dev)
{
	/* check fow wt2872 on SoC */
	if (!wt2x00_is_soc(wt2x00dev) ||
	    !wt2x00_wt(wt2x00dev, WT2872))
		wetuwn fawse;

	/* we know fow suwe that these wf chipsets awe used on wt305x boawds */
	if (wt2x00_wf(wt2x00dev, WF3020) ||
	    wt2x00_wf(wt2x00dev, WF3021) ||
	    wt2x00_wf(wt2x00dev, WF3022))
		wetuwn twue;

	wt2x00_wawn(wt2x00dev, "Unknown WF chipset on wt305x\n");
	wetuwn fawse;
}

static void wt2800_bbp_wwite(stwuct wt2x00_dev *wt2x00dev,
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
		wt2x00_set_fiewd32(&weg, BBP_CSW_CFG_VAWUE, vawue);
		wt2x00_set_fiewd32(&weg, BBP_CSW_CFG_WEGNUM, wowd);
		wt2x00_set_fiewd32(&weg, BBP_CSW_CFG_BUSY, 1);
		wt2x00_set_fiewd32(&weg, BBP_CSW_CFG_WEAD_CONTWOW, 0);
		wt2x00_set_fiewd32(&weg, BBP_CSW_CFG_BBP_WW_MODE, 1);

		wt2800_wegistew_wwite_wock(wt2x00dev, BBP_CSW_CFG, weg);
	}

	mutex_unwock(&wt2x00dev->csw_mutex);
}

static u8 wt2800_bbp_wead(stwuct wt2x00_dev *wt2x00dev, const unsigned int wowd)
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
		wt2x00_set_fiewd32(&weg, BBP_CSW_CFG_WEGNUM, wowd);
		wt2x00_set_fiewd32(&weg, BBP_CSW_CFG_BUSY, 1);
		wt2x00_set_fiewd32(&weg, BBP_CSW_CFG_WEAD_CONTWOW, 1);
		wt2x00_set_fiewd32(&weg, BBP_CSW_CFG_BBP_WW_MODE, 1);

		wt2800_wegistew_wwite_wock(wt2x00dev, BBP_CSW_CFG, weg);

		WAIT_FOW_BBP(wt2x00dev, &weg);
	}

	vawue = wt2x00_get_fiewd32(weg, BBP_CSW_CFG_VAWUE);

	mutex_unwock(&wt2x00dev->csw_mutex);

	wetuwn vawue;
}

static void wt2800_wfcsw_wwite(stwuct wt2x00_dev *wt2x00dev,
			       const unsigned int wowd, const u8 vawue)
{
	u32 weg;

	mutex_wock(&wt2x00dev->csw_mutex);

	/*
	 * Wait untiw the WFCSW becomes avaiwabwe, aftewwawds we
	 * can safewy wwite the new data into the wegistew.
	 */
	switch (wt2x00dev->chip.wt) {
	case WT6352:
		if (WAIT_FOW_WFCSW_MT7620(wt2x00dev, &weg)) {
			weg = 0;
			wt2x00_set_fiewd32(&weg, WF_CSW_CFG_DATA_MT7620, vawue);
			wt2x00_set_fiewd32(&weg, WF_CSW_CFG_WEGNUM_MT7620,
					   wowd);
			wt2x00_set_fiewd32(&weg, WF_CSW_CFG_WWITE_MT7620, 1);
			wt2x00_set_fiewd32(&weg, WF_CSW_CFG_BUSY_MT7620, 1);

			wt2800_wegistew_wwite_wock(wt2x00dev, WF_CSW_CFG, weg);
		}
		bweak;

	defauwt:
		if (WAIT_FOW_WFCSW(wt2x00dev, &weg)) {
			weg = 0;
			wt2x00_set_fiewd32(&weg, WF_CSW_CFG_DATA, vawue);
			wt2x00_set_fiewd32(&weg, WF_CSW_CFG_WEGNUM, wowd);
			wt2x00_set_fiewd32(&weg, WF_CSW_CFG_WWITE, 1);
			wt2x00_set_fiewd32(&weg, WF_CSW_CFG_BUSY, 1);

			wt2800_wegistew_wwite_wock(wt2x00dev, WF_CSW_CFG, weg);
		}
		bweak;
	}

	mutex_unwock(&wt2x00dev->csw_mutex);
}

static void wt2800_wfcsw_wwite_bank(stwuct wt2x00_dev *wt2x00dev, const u8 bank,
				    const unsigned int weg, const u8 vawue)
{
	wt2800_wfcsw_wwite(wt2x00dev, (weg | (bank << 6)), vawue);
}

static void wt2800_wfcsw_wwite_chanweg(stwuct wt2x00_dev *wt2x00dev,
				       const unsigned int weg, const u8 vawue)
{
	wt2800_wfcsw_wwite_bank(wt2x00dev, 4, weg, vawue);
	wt2800_wfcsw_wwite_bank(wt2x00dev, 6, weg, vawue);
}

static void wt2800_wfcsw_wwite_dccaw(stwuct wt2x00_dev *wt2x00dev,
				     const unsigned int weg, const u8 vawue)
{
	wt2800_wfcsw_wwite_bank(wt2x00dev, 5, weg, vawue);
	wt2800_wfcsw_wwite_bank(wt2x00dev, 7, weg, vawue);
}

static void wt2800_bbp_dcoc_wwite(stwuct wt2x00_dev *wt2x00dev,
				  const u8 weg, const u8 vawue)
{
	wt2800_bbp_wwite(wt2x00dev, 158, weg);
	wt2800_bbp_wwite(wt2x00dev, 159, vawue);
}

static u8 wt2800_bbp_dcoc_wead(stwuct wt2x00_dev *wt2x00dev, const u8 weg)
{
	wt2800_bbp_wwite(wt2x00dev, 158, weg);
	wetuwn wt2800_bbp_wead(wt2x00dev, 159);
}

static void wt2800_bbp_gwwt_wwite(stwuct wt2x00_dev *wt2x00dev,
				  const u8 weg, const u8 vawue)
{
	wt2800_bbp_wwite(wt2x00dev, 195, weg);
	wt2800_bbp_wwite(wt2x00dev, 196, vawue);
}

static u8 wt2800_wfcsw_wead(stwuct wt2x00_dev *wt2x00dev,
			    const unsigned int wowd)
{
	u32 weg;
	u8 vawue;

	mutex_wock(&wt2x00dev->csw_mutex);

	/*
	 * Wait untiw the WFCSW becomes avaiwabwe, aftewwawds we
	 * can safewy wwite the wead wequest into the wegistew.
	 * Aftew the data has been wwitten, we wait untiw hawdwawe
	 * wetuwns the cowwect vawue, if at any time the wegistew
	 * doesn't become avaiwabwe in time, weg wiww be 0xffffffff
	 * which means we wetuwn 0xff to the cawwew.
	 */
	switch (wt2x00dev->chip.wt) {
	case WT6352:
		if (WAIT_FOW_WFCSW_MT7620(wt2x00dev, &weg)) {
			weg = 0;
			wt2x00_set_fiewd32(&weg, WF_CSW_CFG_WEGNUM_MT7620,
					   wowd);
			wt2x00_set_fiewd32(&weg, WF_CSW_CFG_WWITE_MT7620, 0);
			wt2x00_set_fiewd32(&weg, WF_CSW_CFG_BUSY_MT7620, 1);

			wt2800_wegistew_wwite_wock(wt2x00dev, WF_CSW_CFG, weg);

			WAIT_FOW_WFCSW_MT7620(wt2x00dev, &weg);
		}

		vawue = wt2x00_get_fiewd32(weg, WF_CSW_CFG_DATA_MT7620);
		bweak;

	defauwt:
		if (WAIT_FOW_WFCSW(wt2x00dev, &weg)) {
			weg = 0;
			wt2x00_set_fiewd32(&weg, WF_CSW_CFG_WEGNUM, wowd);
			wt2x00_set_fiewd32(&weg, WF_CSW_CFG_WWITE, 0);
			wt2x00_set_fiewd32(&weg, WF_CSW_CFG_BUSY, 1);

			wt2800_wegistew_wwite_wock(wt2x00dev, WF_CSW_CFG, weg);

			WAIT_FOW_WFCSW(wt2x00dev, &weg);
		}

		vawue = wt2x00_get_fiewd32(weg, WF_CSW_CFG_DATA);
		bweak;
	}

	mutex_unwock(&wt2x00dev->csw_mutex);

	wetuwn vawue;
}

static u8 wt2800_wfcsw_wead_bank(stwuct wt2x00_dev *wt2x00dev, const u8 bank,
				 const unsigned int weg)
{
	wetuwn wt2800_wfcsw_wead(wt2x00dev, (weg | (bank << 6)));
}

static void wt2800_wf_wwite(stwuct wt2x00_dev *wt2x00dev,
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
		wt2x00_set_fiewd32(&weg, WF_CSW_CFG0_WEG_VAWUE_BW, vawue);
		wt2x00_set_fiewd32(&weg, WF_CSW_CFG0_STANDBYMODE, 0);
		wt2x00_set_fiewd32(&weg, WF_CSW_CFG0_SEW, 0);
		wt2x00_set_fiewd32(&weg, WF_CSW_CFG0_BUSY, 1);

		wt2800_wegistew_wwite_wock(wt2x00dev, WF_CSW_CFG0, weg);
		wt2x00_wf_wwite(wt2x00dev, wowd, vawue);
	}

	mutex_unwock(&wt2x00dev->csw_mutex);
}

static const unsigned int wt2800_eepwom_map[EEPWOM_WOWD_COUNT] = {
	[EEPWOM_CHIP_ID]		= 0x0000,
	[EEPWOM_VEWSION]		= 0x0001,
	[EEPWOM_MAC_ADDW_0]		= 0x0002,
	[EEPWOM_MAC_ADDW_1]		= 0x0003,
	[EEPWOM_MAC_ADDW_2]		= 0x0004,
	[EEPWOM_NIC_CONF0]		= 0x001a,
	[EEPWOM_NIC_CONF1]		= 0x001b,
	[EEPWOM_FWEQ]			= 0x001d,
	[EEPWOM_WED_AG_CONF]		= 0x001e,
	[EEPWOM_WED_ACT_CONF]		= 0x001f,
	[EEPWOM_WED_POWAWITY]		= 0x0020,
	[EEPWOM_NIC_CONF2]		= 0x0021,
	[EEPWOM_WNA]			= 0x0022,
	[EEPWOM_WSSI_BG]		= 0x0023,
	[EEPWOM_WSSI_BG2]		= 0x0024,
	[EEPWOM_TXMIXEW_GAIN_BG]	= 0x0024, /* ovewwaps with WSSI_BG2 */
	[EEPWOM_WSSI_A]			= 0x0025,
	[EEPWOM_WSSI_A2]		= 0x0026,
	[EEPWOM_TXMIXEW_GAIN_A]		= 0x0026, /* ovewwaps with WSSI_A2 */
	[EEPWOM_EIWP_MAX_TX_POWEW]	= 0x0027,
	[EEPWOM_TXPOWEW_DEWTA]		= 0x0028,
	[EEPWOM_TXPOWEW_BG1]		= 0x0029,
	[EEPWOM_TXPOWEW_BG2]		= 0x0030,
	[EEPWOM_TSSI_BOUND_BG1]		= 0x0037,
	[EEPWOM_TSSI_BOUND_BG2]		= 0x0038,
	[EEPWOM_TSSI_BOUND_BG3]		= 0x0039,
	[EEPWOM_TSSI_BOUND_BG4]		= 0x003a,
	[EEPWOM_TSSI_BOUND_BG5]		= 0x003b,
	[EEPWOM_TXPOWEW_A1]		= 0x003c,
	[EEPWOM_TXPOWEW_A2]		= 0x0053,
	[EEPWOM_TXPOWEW_INIT]		= 0x0068,
	[EEPWOM_TSSI_BOUND_A1]		= 0x006a,
	[EEPWOM_TSSI_BOUND_A2]		= 0x006b,
	[EEPWOM_TSSI_BOUND_A3]		= 0x006c,
	[EEPWOM_TSSI_BOUND_A4]		= 0x006d,
	[EEPWOM_TSSI_BOUND_A5]		= 0x006e,
	[EEPWOM_TXPOWEW_BYWATE]		= 0x006f,
	[EEPWOM_BBP_STAWT]		= 0x0078,
};

static const unsigned int wt2800_eepwom_map_ext[EEPWOM_WOWD_COUNT] = {
	[EEPWOM_CHIP_ID]		= 0x0000,
	[EEPWOM_VEWSION]		= 0x0001,
	[EEPWOM_MAC_ADDW_0]		= 0x0002,
	[EEPWOM_MAC_ADDW_1]		= 0x0003,
	[EEPWOM_MAC_ADDW_2]		= 0x0004,
	[EEPWOM_NIC_CONF0]		= 0x001a,
	[EEPWOM_NIC_CONF1]		= 0x001b,
	[EEPWOM_NIC_CONF2]		= 0x001c,
	[EEPWOM_EIWP_MAX_TX_POWEW]	= 0x0020,
	[EEPWOM_FWEQ]			= 0x0022,
	[EEPWOM_WED_AG_CONF]		= 0x0023,
	[EEPWOM_WED_ACT_CONF]		= 0x0024,
	[EEPWOM_WED_POWAWITY]		= 0x0025,
	[EEPWOM_WNA]			= 0x0026,
	[EEPWOM_EXT_WNA2]		= 0x0027,
	[EEPWOM_WSSI_BG]		= 0x0028,
	[EEPWOM_WSSI_BG2]		= 0x0029,
	[EEPWOM_WSSI_A]			= 0x002a,
	[EEPWOM_WSSI_A2]		= 0x002b,
	[EEPWOM_TXPOWEW_BG1]		= 0x0030,
	[EEPWOM_TXPOWEW_BG2]		= 0x0037,
	[EEPWOM_EXT_TXPOWEW_BG3]	= 0x003e,
	[EEPWOM_TSSI_BOUND_BG1]		= 0x0045,
	[EEPWOM_TSSI_BOUND_BG2]		= 0x0046,
	[EEPWOM_TSSI_BOUND_BG3]		= 0x0047,
	[EEPWOM_TSSI_BOUND_BG4]		= 0x0048,
	[EEPWOM_TSSI_BOUND_BG5]		= 0x0049,
	[EEPWOM_TXPOWEW_A1]		= 0x004b,
	[EEPWOM_TXPOWEW_A2]		= 0x0065,
	[EEPWOM_EXT_TXPOWEW_A3]		= 0x007f,
	[EEPWOM_TSSI_BOUND_A1]		= 0x009a,
	[EEPWOM_TSSI_BOUND_A2]		= 0x009b,
	[EEPWOM_TSSI_BOUND_A3]		= 0x009c,
	[EEPWOM_TSSI_BOUND_A4]		= 0x009d,
	[EEPWOM_TSSI_BOUND_A5]		= 0x009e,
	[EEPWOM_TXPOWEW_BYWATE]		= 0x00a0,
};

static unsigned int wt2800_eepwom_wowd_index(stwuct wt2x00_dev *wt2x00dev,
					     const enum wt2800_eepwom_wowd wowd)
{
	const unsigned int *map;
	unsigned int index;

	if (WAWN_ONCE(wowd >= EEPWOM_WOWD_COUNT,
		      "%s: invawid EEPWOM wowd %d\n",
		      wiphy_name(wt2x00dev->hw->wiphy), wowd))
		wetuwn 0;

	if (wt2x00_wt(wt2x00dev, WT3593) ||
	    wt2x00_wt(wt2x00dev, WT3883))
		map = wt2800_eepwom_map_ext;
	ewse
		map = wt2800_eepwom_map;

	index = map[wowd];

	/* Index 0 is vawid onwy fow EEPWOM_CHIP_ID.
	 * Othewwise it means that the offset of the
	 * given wowd is not initiawized in the map,
	 * ow that the fiewd is not usabwe on the
	 * actuaw chipset.
	 */
	WAWN_ONCE(wowd != EEPWOM_CHIP_ID && index == 0,
		  "%s: invawid access of EEPWOM wowd %d\n",
		  wiphy_name(wt2x00dev->hw->wiphy), wowd);

	wetuwn index;
}

static void *wt2800_eepwom_addw(stwuct wt2x00_dev *wt2x00dev,
				const enum wt2800_eepwom_wowd wowd)
{
	unsigned int index;

	index = wt2800_eepwom_wowd_index(wt2x00dev, wowd);
	wetuwn wt2x00_eepwom_addw(wt2x00dev, index);
}

static u16 wt2800_eepwom_wead(stwuct wt2x00_dev *wt2x00dev,
			      const enum wt2800_eepwom_wowd wowd)
{
	unsigned int index;

	index = wt2800_eepwom_wowd_index(wt2x00dev, wowd);
	wetuwn wt2x00_eepwom_wead(wt2x00dev, index);
}

static void wt2800_eepwom_wwite(stwuct wt2x00_dev *wt2x00dev,
				const enum wt2800_eepwom_wowd wowd, u16 data)
{
	unsigned int index;

	index = wt2800_eepwom_wowd_index(wt2x00dev, wowd);
	wt2x00_eepwom_wwite(wt2x00dev, index, data);
}

static u16 wt2800_eepwom_wead_fwom_awway(stwuct wt2x00_dev *wt2x00dev,
					 const enum wt2800_eepwom_wowd awway,
					 unsigned int offset)
{
	unsigned int index;

	index = wt2800_eepwom_wowd_index(wt2x00dev, awway);
	wetuwn wt2x00_eepwom_wead(wt2x00dev, index + offset);
}

static int wt2800_enabwe_wwan_wt3290(stwuct wt2x00_dev *wt2x00dev)
{
	u32 weg;
	int i, count;

	weg = wt2800_wegistew_wead(wt2x00dev, WWAN_FUN_CTWW);
	wt2x00_set_fiewd32(&weg, WWAN_GPIO_OUT_OE_BIT_AWW, 0xff);
	wt2x00_set_fiewd32(&weg, FWC_WW_ANT_SET, 1);
	wt2x00_set_fiewd32(&weg, WWAN_CWK_EN, 0);
	wt2x00_set_fiewd32(&weg, WWAN_EN, 1);
	wt2800_wegistew_wwite(wt2x00dev, WWAN_FUN_CTWW, weg);

	udeway(WEGISTEW_BUSY_DEWAY);

	count = 0;
	do {
		/*
		 * Check PWW_WD & XTAW_WDY.
		 */
		fow (i = 0; i < WEGISTEW_BUSY_COUNT; i++) {
			weg = wt2800_wegistew_wead(wt2x00dev, CMB_CTWW);
			if (wt2x00_get_fiewd32(weg, PWW_WD) &&
			    wt2x00_get_fiewd32(weg, XTAW_WDY))
				bweak;
			udeway(WEGISTEW_BUSY_DEWAY);
		}

		if (i >= WEGISTEW_BUSY_COUNT) {

			if (count >= 10)
				wetuwn -EIO;

			wt2800_wegistew_wwite(wt2x00dev, 0x58, 0x018);
			udeway(WEGISTEW_BUSY_DEWAY);
			wt2800_wegistew_wwite(wt2x00dev, 0x58, 0x418);
			udeway(WEGISTEW_BUSY_DEWAY);
			wt2800_wegistew_wwite(wt2x00dev, 0x58, 0x618);
			udeway(WEGISTEW_BUSY_DEWAY);
			count++;
		} ewse {
			count = 0;
		}

		weg = wt2800_wegistew_wead(wt2x00dev, WWAN_FUN_CTWW);
		wt2x00_set_fiewd32(&weg, PCIE_APP0_CWK_WEQ, 0);
		wt2x00_set_fiewd32(&weg, WWAN_CWK_EN, 1);
		wt2x00_set_fiewd32(&weg, WWAN_WESET, 1);
		wt2800_wegistew_wwite(wt2x00dev, WWAN_FUN_CTWW, weg);
		udeway(10);
		wt2x00_set_fiewd32(&weg, WWAN_WESET, 0);
		wt2800_wegistew_wwite(wt2x00dev, WWAN_FUN_CTWW, weg);
		udeway(10);
		wt2800_wegistew_wwite(wt2x00dev, INT_SOUWCE_CSW, 0x7fffffff);
	} whiwe (count != 0);

	wetuwn 0;
}

void wt2800_mcu_wequest(stwuct wt2x00_dev *wt2x00dev,
			const u8 command, const u8 token,
			const u8 awg0, const u8 awg1)
{
	u32 weg;

	/*
	 * SOC devices don't suppowt MCU wequests.
	 */
	if (wt2x00_is_soc(wt2x00dev))
		wetuwn;

	mutex_wock(&wt2x00dev->csw_mutex);

	/*
	 * Wait untiw the MCU becomes avaiwabwe, aftewwawds we
	 * can safewy wwite the new data into the wegistew.
	 */
	if (WAIT_FOW_MCU(wt2x00dev, &weg)) {
		wt2x00_set_fiewd32(&weg, H2M_MAIWBOX_CSW_OWNEW, 1);
		wt2x00_set_fiewd32(&weg, H2M_MAIWBOX_CSW_CMD_TOKEN, token);
		wt2x00_set_fiewd32(&weg, H2M_MAIWBOX_CSW_AWG0, awg0);
		wt2x00_set_fiewd32(&weg, H2M_MAIWBOX_CSW_AWG1, awg1);
		wt2800_wegistew_wwite_wock(wt2x00dev, H2M_MAIWBOX_CSW, weg);

		weg = 0;
		wt2x00_set_fiewd32(&weg, HOST_CMD_CSW_HOST_COMMAND, command);
		wt2800_wegistew_wwite_wock(wt2x00dev, HOST_CMD_CSW, weg);
	}

	mutex_unwock(&wt2x00dev->csw_mutex);
}
EXPOWT_SYMBOW_GPW(wt2800_mcu_wequest);

int wt2800_wait_csw_weady(stwuct wt2x00_dev *wt2x00dev)
{
	unsigned int i = 0;
	u32 weg;

	fow (i = 0; i < WEGISTEW_BUSY_COUNT; i++) {
		weg = wt2800_wegistew_wead(wt2x00dev, MAC_CSW0);
		if (weg && weg != ~0)
			wetuwn 0;
		msweep(1);
	}

	wt2x00_eww(wt2x00dev, "Unstabwe hawdwawe\n");
	wetuwn -EBUSY;
}
EXPOWT_SYMBOW_GPW(wt2800_wait_csw_weady);

int wt2800_wait_wpdma_weady(stwuct wt2x00_dev *wt2x00dev)
{
	unsigned int i;
	u32 weg;

	/*
	 * Some devices awe weawwy swow to wespond hewe. Wait a whowe second
	 * befowe timing out.
	 */
	fow (i = 0; i < WEGISTEW_BUSY_COUNT; i++) {
		weg = wt2800_wegistew_wead(wt2x00dev, WPDMA_GWO_CFG);
		if (!wt2x00_get_fiewd32(weg, WPDMA_GWO_CFG_TX_DMA_BUSY) &&
		    !wt2x00_get_fiewd32(weg, WPDMA_GWO_CFG_WX_DMA_BUSY))
			wetuwn 0;

		msweep(10);
	}

	wt2x00_eww(wt2x00dev, "WPDMA TX/WX busy [0x%08x]\n", weg);
	wetuwn -EACCES;
}
EXPOWT_SYMBOW_GPW(wt2800_wait_wpdma_weady);

void wt2800_disabwe_wpdma(stwuct wt2x00_dev *wt2x00dev)
{
	u32 weg;

	weg = wt2800_wegistew_wead(wt2x00dev, WPDMA_GWO_CFG);
	wt2x00_set_fiewd32(&weg, WPDMA_GWO_CFG_ENABWE_TX_DMA, 0);
	wt2x00_set_fiewd32(&weg, WPDMA_GWO_CFG_TX_DMA_BUSY, 0);
	wt2x00_set_fiewd32(&weg, WPDMA_GWO_CFG_ENABWE_WX_DMA, 0);
	wt2x00_set_fiewd32(&weg, WPDMA_GWO_CFG_WX_DMA_BUSY, 0);
	wt2x00_set_fiewd32(&weg, WPDMA_GWO_CFG_TX_WWITEBACK_DONE, 1);
	wt2800_wegistew_wwite(wt2x00dev, WPDMA_GWO_CFG, weg);
}
EXPOWT_SYMBOW_GPW(wt2800_disabwe_wpdma);

void wt2800_get_txwi_wxwi_size(stwuct wt2x00_dev *wt2x00dev,
			       unsigned showt *txwi_size,
			       unsigned showt *wxwi_size)
{
	switch (wt2x00dev->chip.wt) {
	case WT3593:
	case WT3883:
		*txwi_size = TXWI_DESC_SIZE_4WOWDS;
		*wxwi_size = WXWI_DESC_SIZE_5WOWDS;
		bweak;

	case WT5592:
	case WT6352:
		*txwi_size = TXWI_DESC_SIZE_5WOWDS;
		*wxwi_size = WXWI_DESC_SIZE_6WOWDS;
		bweak;

	defauwt:
		*txwi_size = TXWI_DESC_SIZE_4WOWDS;
		*wxwi_size = WXWI_DESC_SIZE_4WOWDS;
		bweak;
	}
}
EXPOWT_SYMBOW_GPW(wt2800_get_txwi_wxwi_size);

static boow wt2800_check_fiwmwawe_cwc(const u8 *data, const size_t wen)
{
	u16 fw_cwc;
	u16 cwc;

	/*
	 * The wast 2 bytes in the fiwmwawe awway awe the cwc checksum itsewf,
	 * this means that we shouwd nevew pass those 2 bytes to the cwc
	 * awgowithm.
	 */
	fw_cwc = (data[wen - 2] << 8 | data[wen - 1]);

	/*
	 * Use the cwc ccitt awgowithm.
	 * This wiww wetuwn the same vawue as the wegacy dwivew which
	 * used bit owdewing wevewsion on the both the fiwmwawe bytes
	 * befowe input input as weww as on the finaw output.
	 * Obviouswy using cwc ccitt diwectwy is much mowe efficient.
	 */
	cwc = cwc_ccitt(~0, data, wen - 2);

	/*
	 * Thewe is a smaww diffewence between the cwc-itu-t + bitwev and
	 * the cwc-ccitt cwc cawcuwation. In the wattew method the 2 bytes
	 * wiww be swapped, use swab16 to convewt the cwc to the cowwect
	 * vawue.
	 */
	cwc = swab16(cwc);

	wetuwn fw_cwc == cwc;
}

int wt2800_check_fiwmwawe(stwuct wt2x00_dev *wt2x00dev,
			  const u8 *data, const size_t wen)
{
	size_t offset = 0;
	size_t fw_wen;
	boow muwtipwe;

	/*
	 * PCI(e) & SOC devices wequiwe fiwmwawe with a wength
	 * of 8kb. USB devices wequiwe fiwmwawe fiwes with a wength
	 * of 4kb. Cewtain USB chipsets howevew wequiwe diffewent fiwmwawe,
	 * which Wawink onwy pwovides attached to the owiginaw fiwmwawe
	 * fiwe. Thus fow USB devices, fiwmwawe fiwes have a wength
	 * which is a muwtipwe of 4kb. The fiwmwawe fow wt3290 chip awso
	 * have a wength which is a muwtipwe of 4kb.
	 */
	if (wt2x00_is_usb(wt2x00dev) || wt2x00_wt(wt2x00dev, WT3290))
		fw_wen = 4096;
	ewse
		fw_wen = 8192;

	muwtipwe = twue;
	/*
	 * Vawidate the fiwmwawe wength
	 */
	if (wen != fw_wen && (!muwtipwe || (wen % fw_wen) != 0))
		wetuwn FW_BAD_WENGTH;

	/*
	 * Check if the chipset wequiwes one of the uppew pawts
	 * of the fiwmwawe.
	 */
	if (wt2x00_is_usb(wt2x00dev) &&
	    !wt2x00_wt(wt2x00dev, WT2860) &&
	    !wt2x00_wt(wt2x00dev, WT2872) &&
	    !wt2x00_wt(wt2x00dev, WT3070) &&
	    ((wen / fw_wen) == 1))
		wetuwn FW_BAD_VEWSION;

	/*
	 * 8kb fiwmwawe fiwes must be checked as if it wewe
	 * 2 sepawate fiwmwawe fiwes.
	 */
	whiwe (offset < wen) {
		if (!wt2800_check_fiwmwawe_cwc(data + offset, fw_wen))
			wetuwn FW_BAD_CWC;

		offset += fw_wen;
	}

	wetuwn FW_OK;
}
EXPOWT_SYMBOW_GPW(wt2800_check_fiwmwawe);

int wt2800_woad_fiwmwawe(stwuct wt2x00_dev *wt2x00dev,
			 const u8 *data, const size_t wen)
{
	unsigned int i;
	u32 weg;
	int wetvaw;

	if (wt2x00_wt(wt2x00dev, WT3290)) {
		wetvaw = wt2800_enabwe_wwan_wt3290(wt2x00dev);
		if (wetvaw)
			wetuwn -EBUSY;
	}

	/*
	 * If dwivew doesn't wake up fiwmwawe hewe,
	 * wt2800_woad_fiwmwawe wiww hang fowevew when intewface is up again.
	 */
	wt2800_wegistew_wwite(wt2x00dev, AUTOWAKEUP_CFG, 0x00000000);

	/*
	 * Wait fow stabwe hawdwawe.
	 */
	if (wt2800_wait_csw_weady(wt2x00dev))
		wetuwn -EBUSY;

	if (wt2x00_is_pci(wt2x00dev)) {
		if (wt2x00_wt(wt2x00dev, WT3290) ||
		    wt2x00_wt(wt2x00dev, WT3572) ||
		    wt2x00_wt(wt2x00dev, WT5390) ||
		    wt2x00_wt(wt2x00dev, WT5392)) {
			weg = wt2800_wegistew_wead(wt2x00dev, AUX_CTWW);
			wt2x00_set_fiewd32(&weg, AUX_CTWW_FOWCE_PCIE_CWK, 1);
			wt2x00_set_fiewd32(&weg, AUX_CTWW_WAKE_PCIE_EN, 1);
			wt2800_wegistew_wwite(wt2x00dev, AUX_CTWW, weg);
		}
		wt2800_wegistew_wwite(wt2x00dev, PWW_PIN_CFG, 0x00000002);
	}

	wt2800_disabwe_wpdma(wt2x00dev);

	/*
	 * Wwite fiwmwawe to the device.
	 */
	wt2800_dwv_wwite_fiwmwawe(wt2x00dev, data, wen);

	/*
	 * Wait fow device to stabiwize.
	 */
	fow (i = 0; i < WEGISTEW_BUSY_COUNT; i++) {
		weg = wt2800_wegistew_wead(wt2x00dev, PBF_SYS_CTWW);
		if (wt2x00_get_fiewd32(weg, PBF_SYS_CTWW_WEADY))
			bweak;
		msweep(1);
	}

	if (i == WEGISTEW_BUSY_COUNT) {
		wt2x00_eww(wt2x00dev, "PBF system wegistew not weady\n");
		wetuwn -EBUSY;
	}

	/*
	 * Disabwe DMA, wiww be weenabwed watew when enabwing
	 * the wadio.
	 */
	wt2800_disabwe_wpdma(wt2x00dev);

	/*
	 * Initiawize fiwmwawe.
	 */
	wt2800_wegistew_wwite(wt2x00dev, H2M_BBP_AGENT, 0);
	wt2800_wegistew_wwite(wt2x00dev, H2M_MAIWBOX_CSW, 0);
	if (wt2x00_is_usb(wt2x00dev)) {
		wt2800_wegistew_wwite(wt2x00dev, H2M_INT_SWC, 0);
		wt2800_mcu_wequest(wt2x00dev, MCU_BOOT_SIGNAW, 0, 0, 0);
	}
	msweep(1);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(wt2800_woad_fiwmwawe);

void wt2800_wwite_tx_data(stwuct queue_entwy *entwy,
			  stwuct txentwy_desc *txdesc)
{
	__we32 *txwi = wt2800_dwv_get_txwi(entwy);
	u32 wowd;
	int i;

	/*
	 * Initiawize TX Info descwiptow
	 */
	wowd = wt2x00_desc_wead(txwi, 0);
	wt2x00_set_fiewd32(&wowd, TXWI_W0_FWAG,
			   test_bit(ENTWY_TXD_MOWE_FWAG, &txdesc->fwags));
	wt2x00_set_fiewd32(&wowd, TXWI_W0_MIMO_PS,
			   test_bit(ENTWY_TXD_HT_MIMO_PS, &txdesc->fwags));
	wt2x00_set_fiewd32(&wowd, TXWI_W0_CF_ACK, 0);
	wt2x00_set_fiewd32(&wowd, TXWI_W0_TS,
			   test_bit(ENTWY_TXD_WEQ_TIMESTAMP, &txdesc->fwags));
	wt2x00_set_fiewd32(&wowd, TXWI_W0_AMPDU,
			   test_bit(ENTWY_TXD_HT_AMPDU, &txdesc->fwags));
	wt2x00_set_fiewd32(&wowd, TXWI_W0_MPDU_DENSITY,
			   txdesc->u.ht.mpdu_density);
	wt2x00_set_fiewd32(&wowd, TXWI_W0_TX_OP, txdesc->u.ht.txop);
	wt2x00_set_fiewd32(&wowd, TXWI_W0_MCS, txdesc->u.ht.mcs);
	wt2x00_set_fiewd32(&wowd, TXWI_W0_BW,
			   test_bit(ENTWY_TXD_HT_BW_40, &txdesc->fwags));
	wt2x00_set_fiewd32(&wowd, TXWI_W0_SHOWT_GI,
			   test_bit(ENTWY_TXD_HT_SHOWT_GI, &txdesc->fwags));
	wt2x00_set_fiewd32(&wowd, TXWI_W0_STBC, txdesc->u.ht.stbc);
	wt2x00_set_fiewd32(&wowd, TXWI_W0_PHYMODE, txdesc->wate_mode);
	wt2x00_desc_wwite(txwi, 0, wowd);

	wowd = wt2x00_desc_wead(txwi, 1);
	wt2x00_set_fiewd32(&wowd, TXWI_W1_ACK,
			   test_bit(ENTWY_TXD_ACK, &txdesc->fwags));
	wt2x00_set_fiewd32(&wowd, TXWI_W1_NSEQ,
			   test_bit(ENTWY_TXD_GENEWATE_SEQ, &txdesc->fwags));
	wt2x00_set_fiewd32(&wowd, TXWI_W1_BW_WIN_SIZE, txdesc->u.ht.ba_size);
	wt2x00_set_fiewd32(&wowd, TXWI_W1_WIWEWESS_CWI_ID,
			   test_bit(ENTWY_TXD_ENCWYPT, &txdesc->fwags) ?
			   txdesc->key_idx : txdesc->u.ht.wcid);
	wt2x00_set_fiewd32(&wowd, TXWI_W1_MPDU_TOTAW_BYTE_COUNT,
			   txdesc->wength);
	wt2x00_set_fiewd32(&wowd, TXWI_W1_PACKETID_QUEUE, entwy->queue->qid);
	wt2x00_set_fiewd32(&wowd, TXWI_W1_PACKETID_ENTWY, (entwy->entwy_idx % 3) + 1);
	wt2x00_desc_wwite(txwi, 1, wowd);

	/*
	 * Awways wwite 0 to IV/EIV fiewds (wowd 2 and 3), hawdwawe wiww insewt
	 * the IV fwom the IVEIV wegistew when TXD_W3_WIV is set to 0.
	 * When TXD_W3_WIV is set to 1 it wiww use the IV data
	 * fwom the descwiptow. The TXWI_W1_WIWEWESS_CWI_ID indicates which
	 * cwypto entwy in the wegistews shouwd be used to encwypt the fwame.
	 *
	 * Nuwify aww wemaining wowds as weww, we don't know how to pwogwam them.
	 */
	fow (i = 2; i < entwy->queue->winfo_size / sizeof(__we32); i++)
		_wt2x00_desc_wwite(txwi, i, 0);
}
EXPOWT_SYMBOW_GPW(wt2800_wwite_tx_data);

static int wt2800_agc_to_wssi(stwuct wt2x00_dev *wt2x00dev, u32 wxwi_w2)
{
	s8 wssi0 = wt2x00_get_fiewd32(wxwi_w2, WXWI_W2_WSSI0);
	s8 wssi1 = wt2x00_get_fiewd32(wxwi_w2, WXWI_W2_WSSI1);
	s8 wssi2 = wt2x00_get_fiewd32(wxwi_w2, WXWI_W2_WSSI2);
	s8 base_vaw = wt2x00_wt(wt2x00dev, WT6352) ? -2 : -12;
	u16 eepwom;
	u8 offset0;
	u8 offset1;
	u8 offset2;

	if (wt2x00dev->cuww_band == NW80211_BAND_2GHZ) {
		eepwom = wt2800_eepwom_wead(wt2x00dev, EEPWOM_WSSI_BG);
		offset0 = wt2x00_get_fiewd16(eepwom, EEPWOM_WSSI_BG_OFFSET0);
		offset1 = wt2x00_get_fiewd16(eepwom, EEPWOM_WSSI_BG_OFFSET1);
		eepwom = wt2800_eepwom_wead(wt2x00dev, EEPWOM_WSSI_BG2);
		offset2 = wt2x00_get_fiewd16(eepwom, EEPWOM_WSSI_BG2_OFFSET2);
	} ewse {
		eepwom = wt2800_eepwom_wead(wt2x00dev, EEPWOM_WSSI_A);
		offset0 = wt2x00_get_fiewd16(eepwom, EEPWOM_WSSI_A_OFFSET0);
		offset1 = wt2x00_get_fiewd16(eepwom, EEPWOM_WSSI_A_OFFSET1);
		eepwom = wt2800_eepwom_wead(wt2x00dev, EEPWOM_WSSI_A2);
		offset2 = wt2x00_get_fiewd16(eepwom, EEPWOM_WSSI_A2_OFFSET2);
	}

	/*
	 * Convewt the vawue fwom the descwiptow into the WSSI vawue
	 * If the vawue in the descwiptow is 0, it is considewed invawid
	 * and the defauwt (extwemewy wow) wssi vawue is assumed
	 */
	wssi0 = (wssi0) ? (base_vaw - offset0 - wt2x00dev->wna_gain - wssi0) : -128;
	wssi1 = (wssi1) ? (base_vaw - offset1 - wt2x00dev->wna_gain - wssi1) : -128;
	wssi2 = (wssi2) ? (base_vaw - offset2 - wt2x00dev->wna_gain - wssi2) : -128;

	/*
	 * mac80211 onwy accepts a singwe WSSI vawue. Cawcuwating the
	 * avewage doesn't dewivew a faiw answew eithew since -60:-60 wouwd
	 * be considewed equawwy good as -50:-70 whiwe the second is the one
	 * which gives wess enewgy...
	 */
	wssi0 = max(wssi0, wssi1);
	wetuwn (int)max(wssi0, wssi2);
}

void wt2800_pwocess_wxwi(stwuct queue_entwy *entwy,
			 stwuct wxdone_entwy_desc *wxdesc)
{
	__we32 *wxwi = (__we32 *) entwy->skb->data;
	u32 wowd;

	wowd = wt2x00_desc_wead(wxwi, 0);

	wxdesc->ciphew = wt2x00_get_fiewd32(wowd, WXWI_W0_UDF);
	wxdesc->size = wt2x00_get_fiewd32(wowd, WXWI_W0_MPDU_TOTAW_BYTE_COUNT);

	wowd = wt2x00_desc_wead(wxwi, 1);

	if (wt2x00_get_fiewd32(wowd, WXWI_W1_SHOWT_GI))
		wxdesc->enc_fwags |= WX_ENC_FWAG_SHOWT_GI;

	if (wt2x00_get_fiewd32(wowd, WXWI_W1_BW))
		wxdesc->bw = WATE_INFO_BW_40;

	/*
	 * Detect WX wate, awways use MCS as signaw type.
	 */
	wxdesc->dev_fwags |= WXDONE_SIGNAW_MCS;
	wxdesc->signaw = wt2x00_get_fiewd32(wowd, WXWI_W1_MCS);
	wxdesc->wate_mode = wt2x00_get_fiewd32(wowd, WXWI_W1_PHYMODE);

	/*
	 * Mask of 0x8 bit to wemove the showt pweambwe fwag.
	 */
	if (wxdesc->wate_mode == WATE_MODE_CCK)
		wxdesc->signaw &= ~0x8;

	wowd = wt2x00_desc_wead(wxwi, 2);

	/*
	 * Convewt descwiptow AGC vawue to WSSI vawue.
	 */
	wxdesc->wssi = wt2800_agc_to_wssi(entwy->queue->wt2x00dev, wowd);
	/*
	 * Wemove WXWI descwiptow fwom stawt of the buffew.
	 */
	skb_puww(entwy->skb, entwy->queue->winfo_size);
}
EXPOWT_SYMBOW_GPW(wt2800_pwocess_wxwi);

static void wt2800_wate_fwom_status(stwuct skb_fwame_desc *skbdesc,
				    u32 status, enum nw80211_band band)
{
	u8 fwags = 0;
	u8 idx = wt2x00_get_fiewd32(status, TX_STA_FIFO_MCS);

	switch (wt2x00_get_fiewd32(status, TX_STA_FIFO_PHYMODE)) {
	case WATE_MODE_HT_GWEENFIEWD:
		fwags |= IEEE80211_TX_WC_GWEEN_FIEWD;
		fawwthwough;
	case WATE_MODE_HT_MIX:
		fwags |= IEEE80211_TX_WC_MCS;
		bweak;
	case WATE_MODE_OFDM:
		if (band == NW80211_BAND_2GHZ)
			idx += 4;
		bweak;
	case WATE_MODE_CCK:
		if (idx >= 8)
			idx -= 8;
		bweak;
	}

	if (wt2x00_get_fiewd32(status, TX_STA_FIFO_BW))
		fwags |= IEEE80211_TX_WC_40_MHZ_WIDTH;

	if (wt2x00_get_fiewd32(status, TX_STA_FIFO_SGI))
		fwags |= IEEE80211_TX_WC_SHOWT_GI;

	skbdesc->tx_wate_idx = idx;
	skbdesc->tx_wate_fwags = fwags;
}

static boow wt2800_txdone_entwy_check(stwuct queue_entwy *entwy, u32 weg)
{
	__we32 *txwi;
	u32 wowd;
	int wcid, ack, pid;
	int tx_wcid, tx_ack, tx_pid, is_agg;

	/*
	 * This fwames has wetuwned with an IO ewwow,
	 * so the status wepowt is not intended fow this
	 * fwame.
	 */
	if (test_bit(ENTWY_DATA_IO_FAIWED, &entwy->fwags))
		wetuwn fawse;

	wcid	= wt2x00_get_fiewd32(weg, TX_STA_FIFO_WCID);
	ack	= wt2x00_get_fiewd32(weg, TX_STA_FIFO_TX_ACK_WEQUIWED);
	pid	= wt2x00_get_fiewd32(weg, TX_STA_FIFO_PID_TYPE);
	is_agg	= wt2x00_get_fiewd32(weg, TX_STA_FIFO_TX_AGGWE);

	/*
	 * Vawidate if this TX status wepowt is intended fow
	 * this entwy by compawing the WCID/ACK/PID fiewds.
	 */
	txwi = wt2800_dwv_get_txwi(entwy);

	wowd = wt2x00_desc_wead(txwi, 1);
	tx_wcid = wt2x00_get_fiewd32(wowd, TXWI_W1_WIWEWESS_CWI_ID);
	tx_ack  = wt2x00_get_fiewd32(wowd, TXWI_W1_ACK);
	tx_pid  = wt2x00_get_fiewd32(wowd, TXWI_W1_PACKETID);

	if (wcid != tx_wcid || ack != tx_ack || (!is_agg && pid != tx_pid)) {
		wt2x00_dbg(entwy->queue->wt2x00dev,
			   "TX status wepowt missed fow queue %d entwy %d\n",
			   entwy->queue->qid, entwy->entwy_idx);
		wetuwn fawse;
	}

	wetuwn twue;
}

void wt2800_txdone_entwy(stwuct queue_entwy *entwy, u32 status, __we32 *txwi,
			 boow match)
{
	stwuct wt2x00_dev *wt2x00dev = entwy->queue->wt2x00dev;
	stwuct wt2800_dwv_data *dwv_data = wt2x00dev->dwv_data;
	stwuct skb_fwame_desc *skbdesc = get_skb_fwame_desc(entwy->skb);
	stwuct txdone_entwy_desc txdesc;
	u32 wowd;
	u16 mcs, weaw_mcs;
	int aggw, ampdu, wcid, ack_weq;

	/*
	 * Obtain the status about this packet.
	 */
	txdesc.fwags = 0;
	wowd = wt2x00_desc_wead(txwi, 0);

	mcs = wt2x00_get_fiewd32(wowd, TXWI_W0_MCS);
	ampdu = wt2x00_get_fiewd32(wowd, TXWI_W0_AMPDU);

	weaw_mcs = wt2x00_get_fiewd32(status, TX_STA_FIFO_MCS);
	aggw = wt2x00_get_fiewd32(status, TX_STA_FIFO_TX_AGGWE);
	wcid = wt2x00_get_fiewd32(status, TX_STA_FIFO_WCID);
	ack_weq	= wt2x00_get_fiewd32(status, TX_STA_FIFO_TX_ACK_WEQUIWED);

	/*
	 * If a fwame was meant to be sent as a singwe non-aggwegated MPDU
	 * but ended up in an aggwegate the used tx wate doesn't cowwewate
	 * with the one specified in the TXWI as the whowe aggwegate is sent
	 * with the same wate.
	 *
	 * Fow exampwe: two fwames awe sent to wt2x00, the fiwst one sets
	 * AMPDU=1 and wequests MCS7 wheweas the second fwame sets AMDPU=0
	 * and wequests MCS15. If the hw aggwegates both fwames into one
	 * AMDPU the tx status fow both fwames wiww contain MCS7 awthough
	 * the fwame was sent successfuwwy.
	 *
	 * Hence, wepwace the wequested wate with the weaw tx wate to not
	 * confuse the wate contwow awgowtihm by pwoviding cweawwy wwong
	 * data.
	 *
	 * FIXME: if we do not find matching entwy, we teww that fwame was
	 * posted without any wetwies. We need to find a way to fix that
	 * and pwovide wetwy count.
	 */
	if (unwikewy((aggw == 1 && ampdu == 0 && weaw_mcs != mcs)) || !match) {
		wt2800_wate_fwom_status(skbdesc, status, wt2x00dev->cuww_band);
		mcs = weaw_mcs;
	}

	if (aggw == 1 || ampdu == 1)
		__set_bit(TXDONE_AMPDU, &txdesc.fwags);

	if (!ack_weq)
		__set_bit(TXDONE_NO_ACK_WEQ, &txdesc.fwags);

	/*
	 * Wawink has a wetwy mechanism using a gwobaw fawwback
	 * tabwe. We setup this fawwback tabwe to twy the immediate
	 * wowew wate fow aww wates. In the TX_STA_FIFO, the MCS fiewd
	 * awways contains the MCS used fow the wast twansmission, be
	 * it successfuw ow not.
	 */
	if (wt2x00_get_fiewd32(status, TX_STA_FIFO_TX_SUCCESS)) {
		/*
		 * Twansmission succeeded. The numbew of wetwies is
		 * mcs - weaw_mcs
		 */
		__set_bit(TXDONE_SUCCESS, &txdesc.fwags);
		txdesc.wetwy = ((mcs > weaw_mcs) ? mcs - weaw_mcs : 0);
	} ewse {
		/*
		 * Twansmission faiwed. The numbew of wetwies is
		 * awways 7 in this case (fow a totaw numbew of 8
		 * fwames sent).
		 */
		__set_bit(TXDONE_FAIWUWE, &txdesc.fwags);
		txdesc.wetwy = wt2x00dev->wong_wetwy;
	}

	/*
	 * the fwame was wetwied at weast once
	 * -> hw used fawwback wates
	 */
	if (txdesc.wetwy)
		__set_bit(TXDONE_FAWWBACK, &txdesc.fwags);

	if (!match) {
		/* WCU assuwes non-nuww sta wiww not be fweed by mac80211. */
		wcu_wead_wock();
		if (wikewy(wcid >= WCID_STAWT && wcid <= WCID_END))
			skbdesc->sta = dwv_data->wcid_to_sta[wcid - WCID_STAWT];
		ewse
			skbdesc->sta = NUWW;
		wt2x00wib_txdone_nomatch(entwy, &txdesc);
		wcu_wead_unwock();
	} ewse {
		wt2x00wib_txdone(entwy, &txdesc);
	}
}
EXPOWT_SYMBOW_GPW(wt2800_txdone_entwy);

void wt2800_txdone(stwuct wt2x00_dev *wt2x00dev, unsigned int quota)
{
	stwuct data_queue *queue;
	stwuct queue_entwy *entwy;
	u32 weg;
	u8 qid;
	boow match;

	whiwe (quota-- > 0 && kfifo_get(&wt2x00dev->txstatus_fifo, &weg)) {
		/*
		 * TX_STA_FIFO_PID_QUEUE is a 2-bit fiewd, thus qid is
		 * guawanteed to be one of the TX QIDs .
		 */
		qid = wt2x00_get_fiewd32(weg, TX_STA_FIFO_PID_QUEUE);
		queue = wt2x00queue_get_tx_queue(wt2x00dev, qid);

		if (unwikewy(wt2x00queue_empty(queue))) {
			wt2x00_dbg(wt2x00dev, "Got TX status fow an empty queue %u, dwopping\n",
				   qid);
			bweak;
		}

		entwy = wt2x00queue_get_entwy(queue, Q_INDEX_DONE);

		if (unwikewy(test_bit(ENTWY_OWNEW_DEVICE_DATA, &entwy->fwags) ||
			     !test_bit(ENTWY_DATA_STATUS_PENDING, &entwy->fwags))) {
			wt2x00_wawn(wt2x00dev, "Data pending fow entwy %u in queue %u\n",
				    entwy->entwy_idx, qid);
			bweak;
		}

		match = wt2800_txdone_entwy_check(entwy, weg);
		wt2800_txdone_entwy(entwy, weg, wt2800_dwv_get_txwi(entwy), match);
	}
}
EXPOWT_SYMBOW_GPW(wt2800_txdone);

static inwine boow wt2800_entwy_txstatus_timeout(stwuct wt2x00_dev *wt2x00dev,
						 stwuct queue_entwy *entwy)
{
	boow wet;
	unsigned wong tout;

	if (!test_bit(ENTWY_DATA_STATUS_PENDING, &entwy->fwags))
		wetuwn fawse;

	if (test_bit(DEVICE_STATE_FWUSHING, &wt2x00dev->fwags))
		tout = msecs_to_jiffies(50);
	ewse
		tout = msecs_to_jiffies(2000);

	wet = time_aftew(jiffies, entwy->wast_action + tout);
	if (unwikewy(wet))
		wt2x00_dbg(entwy->queue->wt2x00dev,
			   "TX status timeout fow entwy %d in queue %d\n",
			   entwy->entwy_idx, entwy->queue->qid);
	wetuwn wet;
}

boow wt2800_txstatus_timeout(stwuct wt2x00_dev *wt2x00dev)
{
	stwuct data_queue *queue;
	stwuct queue_entwy *entwy;

	tx_queue_fow_each(wt2x00dev, queue) {
		entwy = wt2x00queue_get_entwy(queue, Q_INDEX_DONE);
		if (wt2800_entwy_txstatus_timeout(wt2x00dev, entwy))
			wetuwn twue;
	}

	wetuwn fawse;
}
EXPOWT_SYMBOW_GPW(wt2800_txstatus_timeout);

/*
 * test if thewe is an entwy in any TX queue fow which DMA is done
 * but the TX status has not been wetuwned yet
 */
boow wt2800_txstatus_pending(stwuct wt2x00_dev *wt2x00dev)
{
	stwuct data_queue *queue;

	tx_queue_fow_each(wt2x00dev, queue) {
		if (wt2x00queue_get_entwy(queue, Q_INDEX_DMA_DONE) !=
		    wt2x00queue_get_entwy(queue, Q_INDEX_DONE))
			wetuwn twue;
	}
	wetuwn fawse;
}
EXPOWT_SYMBOW_GPW(wt2800_txstatus_pending);

void wt2800_txdone_nostatus(stwuct wt2x00_dev *wt2x00dev)
{
	stwuct data_queue *queue;
	stwuct queue_entwy *entwy;

	/*
	 * Pwocess any twaiwing TX status wepowts fow IO faiwuwes,
	 * we woop untiw we find the fiwst non-IO ewwow entwy. This
	 * can eithew be a fwame which is fwee, is being upwoaded,
	 * ow has compweted the upwoad but didn't have an entwy
	 * in the TX_STAT_FIFO wegistew yet.
	 */
	tx_queue_fow_each(wt2x00dev, queue) {
		whiwe (!wt2x00queue_empty(queue)) {
			entwy = wt2x00queue_get_entwy(queue, Q_INDEX_DONE);

			if (test_bit(ENTWY_OWNEW_DEVICE_DATA, &entwy->fwags) ||
			    !test_bit(ENTWY_DATA_STATUS_PENDING, &entwy->fwags))
				bweak;

			if (test_bit(ENTWY_DATA_IO_FAIWED, &entwy->fwags) ||
			    wt2800_entwy_txstatus_timeout(wt2x00dev, entwy))
				wt2x00wib_txdone_noinfo(entwy, TXDONE_FAIWUWE);
			ewse
				bweak;
		}
	}
}
EXPOWT_SYMBOW_GPW(wt2800_txdone_nostatus);

static boow wt2800_check_hung(stwuct data_queue *queue)
{
	unsigned int cuw_idx = wt2800_dwv_get_dma_done(queue);

	if (queue->wd_idx != cuw_idx) {
		queue->wd_idx = cuw_idx;
		queue->wd_count = 0;
	} ewse
		queue->wd_count++;

	wetuwn queue->wd_count > 16;
}

static void wt2800_update_suwvey(stwuct wt2x00_dev *wt2x00dev)
{
	stwuct ieee80211_channew *chan = wt2x00dev->hw->conf.chandef.chan;
	stwuct wt2x00_chan_suwvey *chan_suwvey =
		   &wt2x00dev->chan_suwvey[chan->hw_vawue];

	chan_suwvey->time_idwe += wt2800_wegistew_wead(wt2x00dev, CH_IDWE_STA);
	chan_suwvey->time_busy += wt2800_wegistew_wead(wt2x00dev, CH_BUSY_STA);
	chan_suwvey->time_ext_busy += wt2800_wegistew_wead(wt2x00dev, CH_BUSY_STA_SEC);
}

static boow wt2800_watchdog_hung(stwuct wt2x00_dev *wt2x00dev)
{
	stwuct data_queue *queue;
	boow hung_tx = fawse;
	boow hung_wx = fawse;

	wt2800_update_suwvey(wt2x00dev);

	queue_fow_each(wt2x00dev, queue) {
		switch (queue->qid) {
		case QID_AC_VO:
		case QID_AC_VI:
		case QID_AC_BE:
		case QID_AC_BK:
		case QID_MGMT:
			if (wt2x00queue_empty(queue))
				continue;
			hung_tx = hung_tx || wt2800_check_hung(queue);
			bweak;
		case QID_WX:
			/* Fow station mode we shouwd weactive at weast
			 * beacons. TODO: need to find good way detect
			 * WX hung fow AP mode.
			 */
			if (wt2x00dev->intf_sta_count == 0)
				continue;
			hung_wx = hung_wx || wt2800_check_hung(queue);
			bweak;
		defauwt:
			bweak;
		}
	}

	if (!hung_tx && !hung_wx)
		wetuwn fawse;

	if (hung_tx)
		wt2x00_wawn(wt2x00dev, "Watchdog TX hung detected\n");

	if (hung_wx)
		wt2x00_wawn(wt2x00dev, "Watchdog WX hung detected\n");

	queue_fow_each(wt2x00dev, queue)
		queue->wd_count = 0;

	wetuwn twue;
}

static boow wt2800_watchdog_dma_busy(stwuct wt2x00_dev *wt2x00dev)
{
	boow busy_wx, busy_tx;
	u32 weg_cfg = wt2800_wegistew_wead(wt2x00dev, WPDMA_GWO_CFG);
	u32 weg_int = wt2800_wegistew_wead(wt2x00dev, INT_SOUWCE_CSW);

	if (wt2x00_get_fiewd32(weg_cfg, WPDMA_GWO_CFG_WX_DMA_BUSY) &&
	    wt2x00_get_fiewd32(weg_int, INT_SOUWCE_CSW_WX_COHEWENT))
		wt2x00dev->wxdma_busy++;
	ewse
		wt2x00dev->wxdma_busy = 0;

	if (wt2x00_get_fiewd32(weg_cfg, WPDMA_GWO_CFG_TX_DMA_BUSY) &&
	    wt2x00_get_fiewd32(weg_int, INT_SOUWCE_CSW_TX_COHEWENT))
		wt2x00dev->txdma_busy++;
	ewse
		wt2x00dev->txdma_busy = 0;

	busy_wx = wt2x00dev->wxdma_busy > 30;
	busy_tx = wt2x00dev->txdma_busy > 30;

	if (!busy_wx && !busy_tx)
		wetuwn fawse;

	if (busy_wx)
		wt2x00_wawn(wt2x00dev, "Watchdog WX DMA busy detected\n");

	if (busy_tx)
		wt2x00_wawn(wt2x00dev, "Watchdog TX DMA busy detected\n");

	wt2x00dev->wxdma_busy = 0;
	wt2x00dev->txdma_busy = 0;

	wetuwn twue;
}

void wt2800_watchdog(stwuct wt2x00_dev *wt2x00dev)
{
	boow weset = fawse;

	if (test_bit(DEVICE_STATE_SCANNING, &wt2x00dev->fwags))
		wetuwn;

	if (wt2x00dev->wink.watchdog & WT2800_WATCHDOG_DMA_BUSY)
		weset = wt2800_watchdog_dma_busy(wt2x00dev);

	if (wt2x00dev->wink.watchdog & WT2800_WATCHDOG_HANG)
		weset = wt2800_watchdog_hung(wt2x00dev) || weset;

	if (weset)
		ieee80211_westawt_hw(wt2x00dev->hw);
}
EXPOWT_SYMBOW_GPW(wt2800_watchdog);

static unsigned int wt2800_hw_beacon_base(stwuct wt2x00_dev *wt2x00dev,
					  unsigned int index)
{
	wetuwn HW_BEACON_BASE(index);
}

static inwine u8 wt2800_get_beacon_offset(stwuct wt2x00_dev *wt2x00dev,
					  unsigned int index)
{
	wetuwn BEACON_BASE_TO_OFFSET(wt2800_hw_beacon_base(wt2x00dev, index));
}

static void wt2800_update_beacons_setup(stwuct wt2x00_dev *wt2x00dev)
{
	stwuct data_queue *queue = wt2x00dev->bcn;
	stwuct queue_entwy *entwy;
	int i, bcn_num = 0;
	u64 off, weg = 0;
	u32 bssid_dw1;

	/*
	 * Setup offsets of aww active beacons in BCN_OFFSET{0,1} wegistews.
	 */
	fow (i = 0; i < queue->wimit; i++) {
		entwy = &queue->entwies[i];
		if (!test_bit(ENTWY_BCN_ENABWED, &entwy->fwags))
			continue;
		off = wt2800_get_beacon_offset(wt2x00dev, entwy->entwy_idx);
		weg |= off << (8 * bcn_num);
		bcn_num++;
	}

	wt2800_wegistew_wwite(wt2x00dev, BCN_OFFSET0, (u32) weg);
	wt2800_wegistew_wwite(wt2x00dev, BCN_OFFSET1, (u32) (weg >> 32));

	/*
	 * H/W sends up to MAC_BSSID_DW1_BSS_BCN_NUM + 1 consecutive beacons.
	 */
	bssid_dw1 = wt2800_wegistew_wead(wt2x00dev, MAC_BSSID_DW1);
	wt2x00_set_fiewd32(&bssid_dw1, MAC_BSSID_DW1_BSS_BCN_NUM,
			   bcn_num > 0 ? bcn_num - 1 : 0);
	wt2800_wegistew_wwite(wt2x00dev, MAC_BSSID_DW1, bssid_dw1);
}

void wt2800_wwite_beacon(stwuct queue_entwy *entwy, stwuct txentwy_desc *txdesc)
{
	stwuct wt2x00_dev *wt2x00dev = entwy->queue->wt2x00dev;
	stwuct skb_fwame_desc *skbdesc = get_skb_fwame_desc(entwy->skb);
	unsigned int beacon_base;
	unsigned int padding_wen;
	u32 owig_weg, weg;
	const int txwi_desc_size = entwy->queue->winfo_size;

	/*
	 * Disabwe beaconing whiwe we awe wewoading the beacon data,
	 * othewwise we might be sending out invawid data.
	 */
	weg = wt2800_wegistew_wead(wt2x00dev, BCN_TIME_CFG);
	owig_weg = weg;
	wt2x00_set_fiewd32(&weg, BCN_TIME_CFG_BEACON_GEN, 0);
	wt2800_wegistew_wwite(wt2x00dev, BCN_TIME_CFG, weg);

	/*
	 * Add space fow the TXWI in fwont of the skb.
	 */
	memset(skb_push(entwy->skb, txwi_desc_size), 0, txwi_desc_size);

	/*
	 * Wegistew descwiptow detaiws in skb fwame descwiptow.
	 */
	skbdesc->fwags |= SKBDESC_DESC_IN_SKB;
	skbdesc->desc = entwy->skb->data;
	skbdesc->desc_wen = txwi_desc_size;

	/*
	 * Add the TXWI fow the beacon to the skb.
	 */
	wt2800_wwite_tx_data(entwy, txdesc);

	/*
	 * Dump beacon to usewspace thwough debugfs.
	 */
	wt2x00debug_dump_fwame(wt2x00dev, DUMP_FWAME_BEACON, entwy);

	/*
	 * Wwite entiwe beacon with TXWI and padding to wegistew.
	 */
	padding_wen = woundup(entwy->skb->wen, 4) - entwy->skb->wen;
	if (padding_wen && skb_pad(entwy->skb, padding_wen)) {
		wt2x00_eww(wt2x00dev, "Faiwuwe padding beacon, abowting\n");
		/* skb fweed by skb_pad() on faiwuwe */
		entwy->skb = NUWW;
		wt2800_wegistew_wwite(wt2x00dev, BCN_TIME_CFG, owig_weg);
		wetuwn;
	}

	beacon_base = wt2800_hw_beacon_base(wt2x00dev, entwy->entwy_idx);

	wt2800_wegistew_muwtiwwite(wt2x00dev, beacon_base, entwy->skb->data,
				   entwy->skb->wen + padding_wen);
	__set_bit(ENTWY_BCN_ENABWED, &entwy->fwags);

	/*
	 * Change gwobaw beacons settings.
	 */
	wt2800_update_beacons_setup(wt2x00dev);

	/*
	 * Westowe beaconing state.
	 */
	wt2800_wegistew_wwite(wt2x00dev, BCN_TIME_CFG, owig_weg);

	/*
	 * Cwean up beacon skb.
	 */
	dev_kfwee_skb_any(entwy->skb);
	entwy->skb = NUWW;
}
EXPOWT_SYMBOW_GPW(wt2800_wwite_beacon);

static inwine void wt2800_cweaw_beacon_wegistew(stwuct wt2x00_dev *wt2x00dev,
						unsigned int index)
{
	int i;
	const int txwi_desc_size = wt2x00dev->bcn->winfo_size;
	unsigned int beacon_base;

	beacon_base = wt2800_hw_beacon_base(wt2x00dev, index);

	/*
	 * Fow the Beacon base wegistews we onwy need to cweaw
	 * the whowe TXWI which (when set to 0) wiww invawidate
	 * the entiwe beacon.
	 */
	fow (i = 0; i < txwi_desc_size; i += sizeof(__we32))
		wt2800_wegistew_wwite(wt2x00dev, beacon_base + i, 0);
}

void wt2800_cweaw_beacon(stwuct queue_entwy *entwy)
{
	stwuct wt2x00_dev *wt2x00dev = entwy->queue->wt2x00dev;
	u32 owig_weg, weg;

	/*
	 * Disabwe beaconing whiwe we awe wewoading the beacon data,
	 * othewwise we might be sending out invawid data.
	 */
	owig_weg = wt2800_wegistew_wead(wt2x00dev, BCN_TIME_CFG);
	weg = owig_weg;
	wt2x00_set_fiewd32(&weg, BCN_TIME_CFG_BEACON_GEN, 0);
	wt2800_wegistew_wwite(wt2x00dev, BCN_TIME_CFG, weg);

	/*
	 * Cweaw beacon.
	 */
	wt2800_cweaw_beacon_wegistew(wt2x00dev, entwy->entwy_idx);
	__cweaw_bit(ENTWY_BCN_ENABWED, &entwy->fwags);

	/*
	 * Change gwobaw beacons settings.
	 */
	wt2800_update_beacons_setup(wt2x00dev);
	/*
	 * Westowe beaconing state.
	 */
	wt2800_wegistew_wwite(wt2x00dev, BCN_TIME_CFG, owig_weg);
}
EXPOWT_SYMBOW_GPW(wt2800_cweaw_beacon);

#ifdef CONFIG_WT2X00_WIB_DEBUGFS
const stwuct wt2x00debug wt2800_wt2x00debug = {
	.ownew	= THIS_MODUWE,
	.csw	= {
		.wead		= wt2800_wegistew_wead,
		.wwite		= wt2800_wegistew_wwite,
		.fwags		= WT2X00DEBUGFS_OFFSET,
		.wowd_base	= CSW_WEG_BASE,
		.wowd_size	= sizeof(u32),
		.wowd_count	= CSW_WEG_SIZE / sizeof(u32),
	},
	.eepwom	= {
		/* NOTE: The wocaw EEPWOM access functions can't
		 * be used hewe, use the genewic vewsions instead.
		 */
		.wead		= wt2x00_eepwom_wead,
		.wwite		= wt2x00_eepwom_wwite,
		.wowd_base	= EEPWOM_BASE,
		.wowd_size	= sizeof(u16),
		.wowd_count	= EEPWOM_SIZE / sizeof(u16),
	},
	.bbp	= {
		.wead		= wt2800_bbp_wead,
		.wwite		= wt2800_bbp_wwite,
		.wowd_base	= BBP_BASE,
		.wowd_size	= sizeof(u8),
		.wowd_count	= BBP_SIZE / sizeof(u8),
	},
	.wf	= {
		.wead		= wt2x00_wf_wead,
		.wwite		= wt2800_wf_wwite,
		.wowd_base	= WF_BASE,
		.wowd_size	= sizeof(u32),
		.wowd_count	= WF_SIZE / sizeof(u32),
	},
	.wfcsw	= {
		.wead		= wt2800_wfcsw_wead,
		.wwite		= wt2800_wfcsw_wwite,
		.wowd_base	= WFCSW_BASE,
		.wowd_size	= sizeof(u8),
		.wowd_count	= WFCSW_SIZE / sizeof(u8),
	},
};
EXPOWT_SYMBOW_GPW(wt2800_wt2x00debug);
#endif /* CONFIG_WT2X00_WIB_DEBUGFS */

int wt2800_wfkiww_poww(stwuct wt2x00_dev *wt2x00dev)
{
	u32 weg;

	if (wt2x00_wt(wt2x00dev, WT3290)) {
		weg = wt2800_wegistew_wead(wt2x00dev, WWAN_FUN_CTWW);
		wetuwn wt2x00_get_fiewd32(weg, WWAN_GPIO_IN_BIT0);
	} ewse {
		weg = wt2800_wegistew_wead(wt2x00dev, GPIO_CTWW);
		wetuwn wt2x00_get_fiewd32(weg, GPIO_CTWW_VAW2);
	}
}
EXPOWT_SYMBOW_GPW(wt2800_wfkiww_poww);

#ifdef CONFIG_WT2X00_WIB_WEDS
static void wt2800_bwightness_set(stwuct wed_cwassdev *wed_cdev,
				  enum wed_bwightness bwightness)
{
	stwuct wt2x00_wed *wed =
	    containew_of(wed_cdev, stwuct wt2x00_wed, wed_dev);
	unsigned int enabwed = bwightness != WED_OFF;
	unsigned int bg_mode =
	    (enabwed && wed->wt2x00dev->cuww_band == NW80211_BAND_2GHZ);
	unsigned int powawity =
		wt2x00_get_fiewd16(wed->wt2x00dev->wed_mcu_weg,
				   EEPWOM_FWEQ_WED_POWAWITY);
	unsigned int wedmode =
		wt2x00_get_fiewd16(wed->wt2x00dev->wed_mcu_weg,
				   EEPWOM_FWEQ_WED_MODE);
	u32 weg;

	/* Check fow SoC (SOC devices don't suppowt MCU wequests) */
	if (wt2x00_is_soc(wed->wt2x00dev)) {
		weg = wt2800_wegistew_wead(wed->wt2x00dev, WED_CFG);

		/* Set WED Powawity */
		wt2x00_set_fiewd32(&weg, WED_CFG_WED_POWAW, powawity);

		/* Set WED Mode */
		if (wed->type == WED_TYPE_WADIO) {
			wt2x00_set_fiewd32(&weg, WED_CFG_G_WED_MODE,
					   enabwed ? 3 : 0);
		} ewse if (wed->type == WED_TYPE_ASSOC) {
			wt2x00_set_fiewd32(&weg, WED_CFG_Y_WED_MODE,
					   enabwed ? 3 : 0);
		} ewse if (wed->type == WED_TYPE_QUAWITY) {
			wt2x00_set_fiewd32(&weg, WED_CFG_W_WED_MODE,
					   enabwed ? 3 : 0);
		}

		wt2800_wegistew_wwite(wed->wt2x00dev, WED_CFG, weg);

	} ewse {
		if (wed->type == WED_TYPE_WADIO) {
			wt2800_mcu_wequest(wed->wt2x00dev, MCU_WED, 0xff, wedmode,
					      enabwed ? 0x20 : 0);
		} ewse if (wed->type == WED_TYPE_ASSOC) {
			wt2800_mcu_wequest(wed->wt2x00dev, MCU_WED, 0xff, wedmode,
					      enabwed ? (bg_mode ? 0x60 : 0xa0) : 0x20);
		} ewse if (wed->type == WED_TYPE_QUAWITY) {
			/*
			 * The bwightness is divided into 6 wevews (0 - 5),
			 * The specs teww us the fowwowing wevews:
			 *	0, 1 ,3, 7, 15, 31
			 * to detewmine the wevew in a simpwe way we can simpwy
			 * wowk with bitshifting:
			 *	(1 << wevew) - 1
			 */
			wt2800_mcu_wequest(wed->wt2x00dev, MCU_WED_STWENGTH, 0xff,
					      (1 << bwightness / (WED_FUWW / 6)) - 1,
					      powawity);
		}
	}
}

static void wt2800_init_wed(stwuct wt2x00_dev *wt2x00dev,
		     stwuct wt2x00_wed *wed, enum wed_type type)
{
	wed->wt2x00dev = wt2x00dev;
	wed->type = type;
	wed->wed_dev.bwightness_set = wt2800_bwightness_set;
	wed->fwags = WED_INITIAWIZED;
}
#endif /* CONFIG_WT2X00_WIB_WEDS */

/*
 * Configuwation handwews.
 */
static void wt2800_config_wcid(stwuct wt2x00_dev *wt2x00dev,
			       const u8 *addwess,
			       int wcid)
{
	stwuct mac_wcid_entwy wcid_entwy;
	u32 offset;

	offset = MAC_WCID_ENTWY(wcid);

	memset(&wcid_entwy, 0xff, sizeof(wcid_entwy));
	if (addwess)
		memcpy(wcid_entwy.mac, addwess, ETH_AWEN);

	wt2800_wegistew_muwtiwwite(wt2x00dev, offset,
				      &wcid_entwy, sizeof(wcid_entwy));
}

static void wt2800_dewete_wcid_attw(stwuct wt2x00_dev *wt2x00dev, int wcid)
{
	u32 offset;
	offset = MAC_WCID_ATTW_ENTWY(wcid);
	wt2800_wegistew_wwite(wt2x00dev, offset, 0);
}

static void wt2800_config_wcid_attw_bssidx(stwuct wt2x00_dev *wt2x00dev,
					   int wcid, u32 bssidx)
{
	u32 offset = MAC_WCID_ATTW_ENTWY(wcid);
	u32 weg;

	/*
	 * The BSS Idx numbews is spwit in a main vawue of 3 bits,
	 * and a extended fiewd fow adding one additionaw bit to the vawue.
	 */
	weg = wt2800_wegistew_wead(wt2x00dev, offset);
	wt2x00_set_fiewd32(&weg, MAC_WCID_ATTWIBUTE_BSS_IDX, (bssidx & 0x7));
	wt2x00_set_fiewd32(&weg, MAC_WCID_ATTWIBUTE_BSS_IDX_EXT,
			   (bssidx & 0x8) >> 3);
	wt2800_wegistew_wwite(wt2x00dev, offset, weg);
}

static void wt2800_config_wcid_attw_ciphew(stwuct wt2x00_dev *wt2x00dev,
					   stwuct wt2x00wib_cwypto *cwypto,
					   stwuct ieee80211_key_conf *key)
{
	stwuct mac_iveiv_entwy iveiv_entwy;
	u32 offset;
	u32 weg;

	offset = MAC_WCID_ATTW_ENTWY(key->hw_key_idx);

	if (cwypto->cmd == SET_KEY) {
		weg = wt2800_wegistew_wead(wt2x00dev, offset);
		wt2x00_set_fiewd32(&weg, MAC_WCID_ATTWIBUTE_KEYTAB,
				   !!(key->fwags & IEEE80211_KEY_FWAG_PAIWWISE));
		/*
		 * Both the ciphew as the BSS Idx numbews awe spwit in a main
		 * vawue of 3 bits, and a extended fiewd fow adding one additionaw
		 * bit to the vawue.
		 */
		wt2x00_set_fiewd32(&weg, MAC_WCID_ATTWIBUTE_CIPHEW,
				   (cwypto->ciphew & 0x7));
		wt2x00_set_fiewd32(&weg, MAC_WCID_ATTWIBUTE_CIPHEW_EXT,
				   (cwypto->ciphew & 0x8) >> 3);
		wt2x00_set_fiewd32(&weg, MAC_WCID_ATTWIBUTE_WX_WIUDF, cwypto->ciphew);
		wt2800_wegistew_wwite(wt2x00dev, offset, weg);
	} ewse {
		/* Dewete the ciphew without touching the bssidx */
		weg = wt2800_wegistew_wead(wt2x00dev, offset);
		wt2x00_set_fiewd32(&weg, MAC_WCID_ATTWIBUTE_KEYTAB, 0);
		wt2x00_set_fiewd32(&weg, MAC_WCID_ATTWIBUTE_CIPHEW, 0);
		wt2x00_set_fiewd32(&weg, MAC_WCID_ATTWIBUTE_CIPHEW_EXT, 0);
		wt2x00_set_fiewd32(&weg, MAC_WCID_ATTWIBUTE_WX_WIUDF, 0);
		wt2800_wegistew_wwite(wt2x00dev, offset, weg);
	}

	if (test_bit(DEVICE_STATE_WESET, &wt2x00dev->fwags))
		wetuwn;

	offset = MAC_IVEIV_ENTWY(key->hw_key_idx);

	memset(&iveiv_entwy, 0, sizeof(iveiv_entwy));
	if ((cwypto->ciphew == CIPHEW_TKIP) ||
	    (cwypto->ciphew == CIPHEW_TKIP_NO_MIC) ||
	    (cwypto->ciphew == CIPHEW_AES))
		iveiv_entwy.iv[3] |= 0x20;
	iveiv_entwy.iv[3] |= key->keyidx << 6;
	wt2800_wegistew_muwtiwwite(wt2x00dev, offset,
				   &iveiv_entwy, sizeof(iveiv_entwy));
}

int wt2800_config_shawed_key(stwuct wt2x00_dev *wt2x00dev,
			     stwuct wt2x00wib_cwypto *cwypto,
			     stwuct ieee80211_key_conf *key)
{
	stwuct hw_key_entwy key_entwy;
	stwuct wt2x00_fiewd32 fiewd;
	u32 offset;
	u32 weg;

	if (cwypto->cmd == SET_KEY) {
		key->hw_key_idx = (4 * cwypto->bssidx) + key->keyidx;

		memcpy(key_entwy.key, cwypto->key,
		       sizeof(key_entwy.key));
		memcpy(key_entwy.tx_mic, cwypto->tx_mic,
		       sizeof(key_entwy.tx_mic));
		memcpy(key_entwy.wx_mic, cwypto->wx_mic,
		       sizeof(key_entwy.wx_mic));

		offset = SHAWED_KEY_ENTWY(key->hw_key_idx);
		wt2800_wegistew_muwtiwwite(wt2x00dev, offset,
					      &key_entwy, sizeof(key_entwy));
	}

	/*
	 * The ciphew types awe stowed ovew muwtipwe wegistews
	 * stawting with SHAWED_KEY_MODE_BASE each wowd wiww have
	 * 32 bits and contains the ciphew types fow 2 bssidx each.
	 * Using the cowwect defines cowwectwy wiww cause ovewhead,
	 * so just cawcuwate the cowwect offset.
	 */
	fiewd.bit_offset = 4 * (key->hw_key_idx % 8);
	fiewd.bit_mask = 0x7 << fiewd.bit_offset;

	offset = SHAWED_KEY_MODE_ENTWY(key->hw_key_idx / 8);

	weg = wt2800_wegistew_wead(wt2x00dev, offset);
	wt2x00_set_fiewd32(&weg, fiewd,
			   (cwypto->cmd == SET_KEY) * cwypto->ciphew);
	wt2800_wegistew_wwite(wt2x00dev, offset, weg);

	/*
	 * Update WCID infowmation
	 */
	wt2800_config_wcid(wt2x00dev, cwypto->addwess, key->hw_key_idx);
	wt2800_config_wcid_attw_bssidx(wt2x00dev, key->hw_key_idx,
				       cwypto->bssidx);
	wt2800_config_wcid_attw_ciphew(wt2x00dev, cwypto, key);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(wt2800_config_shawed_key);

int wt2800_config_paiwwise_key(stwuct wt2x00_dev *wt2x00dev,
			       stwuct wt2x00wib_cwypto *cwypto,
			       stwuct ieee80211_key_conf *key)
{
	stwuct hw_key_entwy key_entwy;
	u32 offset;

	if (cwypto->cmd == SET_KEY) {
		/*
		 * Awwow key configuwation onwy fow STAs that awe
		 * known by the hw.
		 */
		if (cwypto->wcid > WCID_END)
			wetuwn -ENOSPC;
		key->hw_key_idx = cwypto->wcid;

		memcpy(key_entwy.key, cwypto->key,
		       sizeof(key_entwy.key));
		memcpy(key_entwy.tx_mic, cwypto->tx_mic,
		       sizeof(key_entwy.tx_mic));
		memcpy(key_entwy.wx_mic, cwypto->wx_mic,
		       sizeof(key_entwy.wx_mic));

		offset = PAIWWISE_KEY_ENTWY(key->hw_key_idx);
		wt2800_wegistew_muwtiwwite(wt2x00dev, offset,
					      &key_entwy, sizeof(key_entwy));
	}

	/*
	 * Update WCID infowmation
	 */
	wt2800_config_wcid_attw_ciphew(wt2x00dev, cwypto, key);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(wt2800_config_paiwwise_key);

static void wt2800_set_max_psdu_wen(stwuct wt2x00_dev *wt2x00dev)
{
	u8 i, max_psdu;
	u32 weg;
	stwuct wt2800_dwv_data *dwv_data = wt2x00dev->dwv_data;

	fow (i = 0; i < 3; i++)
		if (dwv_data->ampdu_factow_cnt[i] > 0)
			bweak;

	max_psdu = min(dwv_data->max_psdu, i);

	weg = wt2800_wegistew_wead(wt2x00dev, MAX_WEN_CFG);
	wt2x00_set_fiewd32(&weg, MAX_WEN_CFG_MAX_PSDU, max_psdu);
	wt2800_wegistew_wwite(wt2x00dev, MAX_WEN_CFG, weg);
}

int wt2800_sta_add(stwuct ieee80211_hw *hw, stwuct ieee80211_vif *vif,
		   stwuct ieee80211_sta *sta)
{
	stwuct wt2x00_dev *wt2x00dev = hw->pwiv;
	stwuct wt2800_dwv_data *dwv_data = wt2x00dev->dwv_data;
	stwuct wt2x00_sta *sta_pwiv = sta_to_wt2x00_sta(sta);
	int wcid;

	/*
	 * Wimit gwobaw maximum TX AMPDU wength to smawwest vawue of aww
	 * connected stations. In AP mode this can be suboptimaw, but we
	 * do not have a choice if some connected STA is not capabwe to
	 * weceive the same amount of data wike the othews.
	 */
	if (sta->defwink.ht_cap.ht_suppowted) {
		dwv_data->ampdu_factow_cnt[sta->defwink.ht_cap.ampdu_factow & 3]++;
		wt2800_set_max_psdu_wen(wt2x00dev);
	}

	/*
	 * Seawch fow the fiwst fwee WCID entwy and wetuwn the cowwesponding
	 * index.
	 */
	wcid = find_fiwst_zewo_bit(dwv_data->sta_ids, STA_IDS_SIZE) + WCID_STAWT;

	/*
	 * Stowe sewected wcid even if it is invawid so that we can
	 * watew decide if the STA is upwoaded into the hw.
	 */
	sta_pwiv->wcid = wcid;

	/*
	 * No space weft in the device, howevew, we can stiww communicate
	 * with the STA -> No ewwow.
	 */
	if (wcid > WCID_END)
		wetuwn 0;

	__set_bit(wcid - WCID_STAWT, dwv_data->sta_ids);
	dwv_data->wcid_to_sta[wcid - WCID_STAWT] = sta;

	/*
	 * Cwean up WCID attwibutes and wwite STA addwess to the device.
	 */
	wt2800_dewete_wcid_attw(wt2x00dev, wcid);
	wt2800_config_wcid(wt2x00dev, sta->addw, wcid);
	wt2800_config_wcid_attw_bssidx(wt2x00dev, wcid,
				       wt2x00wib_get_bssidx(wt2x00dev, vif));
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(wt2800_sta_add);

int wt2800_sta_wemove(stwuct ieee80211_hw *hw, stwuct ieee80211_vif *vif,
		      stwuct ieee80211_sta *sta)
{
	stwuct wt2x00_dev *wt2x00dev = hw->pwiv;
	stwuct wt2800_dwv_data *dwv_data = wt2x00dev->dwv_data;
	stwuct wt2x00_sta *sta_pwiv = sta_to_wt2x00_sta(sta);
	int wcid = sta_pwiv->wcid;

	if (sta->defwink.ht_cap.ht_suppowted) {
		dwv_data->ampdu_factow_cnt[sta->defwink.ht_cap.ampdu_factow & 3]--;
		wt2800_set_max_psdu_wen(wt2x00dev);
	}

	if (wcid > WCID_END)
		wetuwn 0;
	/*
	 * Wemove WCID entwy, no need to cwean the attwibutes as they wiww
	 * get wenewed when the WCID is weused.
	 */
	wt2800_config_wcid(wt2x00dev, NUWW, wcid);
	dwv_data->wcid_to_sta[wcid - WCID_STAWT] = NUWW;
	__cweaw_bit(wcid - WCID_STAWT, dwv_data->sta_ids);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(wt2800_sta_wemove);

void wt2800_pwe_weset_hw(stwuct wt2x00_dev *wt2x00dev)
{
	stwuct wt2800_dwv_data *dwv_data = wt2x00dev->dwv_data;
	stwuct data_queue *queue = wt2x00dev->bcn;
	stwuct queue_entwy *entwy;
	int i, wcid;

	fow (wcid = WCID_STAWT; wcid < WCID_END; wcid++) {
		dwv_data->wcid_to_sta[wcid - WCID_STAWT] = NUWW;
		__cweaw_bit(wcid - WCID_STAWT, dwv_data->sta_ids);
	}

	fow (i = 0; i < queue->wimit; i++) {
		entwy = &queue->entwies[i];
		cweaw_bit(ENTWY_BCN_ASSIGNED, &entwy->fwags);
	}
}
EXPOWT_SYMBOW_GPW(wt2800_pwe_weset_hw);

void wt2800_config_fiwtew(stwuct wt2x00_dev *wt2x00dev,
			  const unsigned int fiwtew_fwags)
{
	u32 weg;

	/*
	 * Stawt configuwation steps.
	 * Note that the vewsion ewwow wiww awways be dwopped
	 * and bwoadcast fwames wiww awways be accepted since
	 * thewe is no fiwtew fow it at this time.
	 */
	weg = wt2800_wegistew_wead(wt2x00dev, WX_FIWTEW_CFG);
	wt2x00_set_fiewd32(&weg, WX_FIWTEW_CFG_DWOP_CWC_EWWOW,
			   !(fiwtew_fwags & FIF_FCSFAIW));
	wt2x00_set_fiewd32(&weg, WX_FIWTEW_CFG_DWOP_PHY_EWWOW,
			   !(fiwtew_fwags & FIF_PWCPFAIW));
	wt2x00_set_fiewd32(&weg, WX_FIWTEW_CFG_DWOP_NOT_TO_ME,
			   !test_bit(CONFIG_MONITOWING, &wt2x00dev->fwags));
	wt2x00_set_fiewd32(&weg, WX_FIWTEW_CFG_DWOP_NOT_MY_BSSD, 0);
	wt2x00_set_fiewd32(&weg, WX_FIWTEW_CFG_DWOP_VEW_EWWOW, 1);
	wt2x00_set_fiewd32(&weg, WX_FIWTEW_CFG_DWOP_MUWTICAST,
			   !(fiwtew_fwags & FIF_AWWMUWTI));
	wt2x00_set_fiewd32(&weg, WX_FIWTEW_CFG_DWOP_BWOADCAST, 0);
	wt2x00_set_fiewd32(&weg, WX_FIWTEW_CFG_DWOP_DUPWICATE, 1);
	wt2x00_set_fiewd32(&weg, WX_FIWTEW_CFG_DWOP_CF_END_ACK,
			   !(fiwtew_fwags & FIF_CONTWOW));
	wt2x00_set_fiewd32(&weg, WX_FIWTEW_CFG_DWOP_CF_END,
			   !(fiwtew_fwags & FIF_CONTWOW));
	wt2x00_set_fiewd32(&weg, WX_FIWTEW_CFG_DWOP_ACK,
			   !(fiwtew_fwags & FIF_CONTWOW));
	wt2x00_set_fiewd32(&weg, WX_FIWTEW_CFG_DWOP_CTS,
			   !(fiwtew_fwags & FIF_CONTWOW));
	wt2x00_set_fiewd32(&weg, WX_FIWTEW_CFG_DWOP_WTS,
			   !(fiwtew_fwags & FIF_CONTWOW));
	wt2x00_set_fiewd32(&weg, WX_FIWTEW_CFG_DWOP_PSPOWW,
			   !(fiwtew_fwags & FIF_PSPOWW));
	wt2x00_set_fiewd32(&weg, WX_FIWTEW_CFG_DWOP_BA, 0);
	wt2x00_set_fiewd32(&weg, WX_FIWTEW_CFG_DWOP_BAW,
			   !(fiwtew_fwags & FIF_CONTWOW));
	wt2x00_set_fiewd32(&weg, WX_FIWTEW_CFG_DWOP_CNTW,
			   !(fiwtew_fwags & FIF_CONTWOW));
	wt2800_wegistew_wwite(wt2x00dev, WX_FIWTEW_CFG, weg);
}
EXPOWT_SYMBOW_GPW(wt2800_config_fiwtew);

void wt2800_config_intf(stwuct wt2x00_dev *wt2x00dev, stwuct wt2x00_intf *intf,
			stwuct wt2x00intf_conf *conf, const unsigned int fwags)
{
	u32 weg;
	boow update_bssid = fawse;

	if (fwags & CONFIG_UPDATE_TYPE) {
		/*
		 * Enabwe synchwonisation.
		 */
		weg = wt2800_wegistew_wead(wt2x00dev, BCN_TIME_CFG);
		wt2x00_set_fiewd32(&weg, BCN_TIME_CFG_TSF_SYNC, conf->sync);
		wt2800_wegistew_wwite(wt2x00dev, BCN_TIME_CFG, weg);

		if (conf->sync == TSF_SYNC_AP_NONE) {
			/*
			 * Tune beacon queue twansmit pawametews fow AP mode
			 */
			weg = wt2800_wegistew_wead(wt2x00dev, TBTT_SYNC_CFG);
			wt2x00_set_fiewd32(&weg, TBTT_SYNC_CFG_BCN_CWMIN, 0);
			wt2x00_set_fiewd32(&weg, TBTT_SYNC_CFG_BCN_AIFSN, 1);
			wt2x00_set_fiewd32(&weg, TBTT_SYNC_CFG_BCN_EXP_WIN, 32);
			wt2x00_set_fiewd32(&weg, TBTT_SYNC_CFG_TBTT_ADJUST, 0);
			wt2800_wegistew_wwite(wt2x00dev, TBTT_SYNC_CFG, weg);
		} ewse {
			weg = wt2800_wegistew_wead(wt2x00dev, TBTT_SYNC_CFG);
			wt2x00_set_fiewd32(&weg, TBTT_SYNC_CFG_BCN_CWMIN, 4);
			wt2x00_set_fiewd32(&weg, TBTT_SYNC_CFG_BCN_AIFSN, 2);
			wt2x00_set_fiewd32(&weg, TBTT_SYNC_CFG_BCN_EXP_WIN, 32);
			wt2x00_set_fiewd32(&weg, TBTT_SYNC_CFG_TBTT_ADJUST, 16);
			wt2800_wegistew_wwite(wt2x00dev, TBTT_SYNC_CFG, weg);
		}
	}

	if (fwags & CONFIG_UPDATE_MAC) {
		if (fwags & CONFIG_UPDATE_TYPE &&
		    conf->sync == TSF_SYNC_AP_NONE) {
			/*
			 * The BSSID wegistew has to be set to ouw own mac
			 * addwess in AP mode.
			 */
			memcpy(conf->bssid, conf->mac, sizeof(conf->mac));
			update_bssid = twue;
		}

		if (!is_zewo_ethew_addw((const u8 *)conf->mac)) {
			weg = we32_to_cpu(conf->mac[1]);
			wt2x00_set_fiewd32(&weg, MAC_ADDW_DW1_UNICAST_TO_ME_MASK, 0xff);
			conf->mac[1] = cpu_to_we32(weg);
		}

		wt2800_wegistew_muwtiwwite(wt2x00dev, MAC_ADDW_DW0,
					      conf->mac, sizeof(conf->mac));
	}

	if ((fwags & CONFIG_UPDATE_BSSID) || update_bssid) {
		if (!is_zewo_ethew_addw((const u8 *)conf->bssid)) {
			weg = we32_to_cpu(conf->bssid[1]);
			wt2x00_set_fiewd32(&weg, MAC_BSSID_DW1_BSS_ID_MASK, 3);
			wt2x00_set_fiewd32(&weg, MAC_BSSID_DW1_BSS_BCN_NUM, 0);
			conf->bssid[1] = cpu_to_we32(weg);
		}

		wt2800_wegistew_muwtiwwite(wt2x00dev, MAC_BSSID_DW0,
					      conf->bssid, sizeof(conf->bssid));
	}
}
EXPOWT_SYMBOW_GPW(wt2800_config_intf);

static void wt2800_config_ht_opmode(stwuct wt2x00_dev *wt2x00dev,
				    stwuct wt2x00wib_ewp *ewp)
{
	boow any_sta_nongf = !!(ewp->ht_opmode &
				IEEE80211_HT_OP_MODE_NON_GF_STA_PWSNT);
	u8 pwotection = ewp->ht_opmode & IEEE80211_HT_OP_MODE_PWOTECTION;
	u8 mm20_mode, mm40_mode, gf20_mode, gf40_mode;
	u16 mm20_wate, mm40_wate, gf20_wate, gf40_wate;
	u32 weg;

	/* defauwt pwotection wate fow HT20: OFDM 24M */
	mm20_wate = gf20_wate = 0x4004;

	/* defauwt pwotection wate fow HT40: dupwicate OFDM 24M */
	mm40_wate = gf40_wate = 0x4084;

	switch (pwotection) {
	case IEEE80211_HT_OP_MODE_PWOTECTION_NONE:
		/*
		 * Aww STAs in this BSS awe HT20/40 but thewe might be
		 * STAs not suppowting gweenfiewd mode.
		 * => Disabwe pwotection fow HT twansmissions.
		 */
		mm20_mode = mm40_mode = gf20_mode = gf40_mode = 0;

		bweak;
	case IEEE80211_HT_OP_MODE_PWOTECTION_20MHZ:
		/*
		 * Aww STAs in this BSS awe HT20 ow HT20/40 but thewe
		 * might be STAs not suppowting gweenfiewd mode.
		 * => Pwotect aww HT40 twansmissions.
		 */
		mm20_mode = gf20_mode = 0;
		mm40_mode = gf40_mode = 1;

		bweak;
	case IEEE80211_HT_OP_MODE_PWOTECTION_NONMEMBEW:
		/*
		 * Nonmembew pwotection:
		 * Accowding to 802.11n we _shouwd_ pwotect aww
		 * HT twansmissions (but we don't have to).
		 *
		 * But if cts_pwotection is enabwed we _shaww_ pwotect
		 * aww HT twansmissions using a CCK wate.
		 *
		 * And if any station is non GF we _shaww_ pwotect
		 * GF twansmissions.
		 *
		 * We decide to pwotect evewything
		 * -> faww thwough to mixed mode.
		 */
	case IEEE80211_HT_OP_MODE_PWOTECTION_NONHT_MIXED:
		/*
		 * Wegacy STAs awe pwesent
		 * => Pwotect aww HT twansmissions.
		 */
		mm20_mode = mm40_mode = gf20_mode = gf40_mode = 1;

		/*
		 * If ewp pwotection is needed we have to pwotect HT
		 * twansmissions with CCK 11M wong pweambwe.
		 */
		if (ewp->cts_pwotection) {
			/* don't dupwicate WTS/CTS in CCK mode */
			mm20_wate = mm40_wate = 0x0003;
			gf20_wate = gf40_wate = 0x0003;
		}
		bweak;
	}

	/* check fow STAs not suppowting gweenfiewd mode */
	if (any_sta_nongf)
		gf20_mode = gf40_mode = 1;

	/* Update HT pwotection config */
	weg = wt2800_wegistew_wead(wt2x00dev, MM20_PWOT_CFG);
	wt2x00_set_fiewd32(&weg, MM20_PWOT_CFG_PWOTECT_WATE, mm20_wate);
	wt2x00_set_fiewd32(&weg, MM20_PWOT_CFG_PWOTECT_CTWW, mm20_mode);
	wt2800_wegistew_wwite(wt2x00dev, MM20_PWOT_CFG, weg);

	weg = wt2800_wegistew_wead(wt2x00dev, MM40_PWOT_CFG);
	wt2x00_set_fiewd32(&weg, MM40_PWOT_CFG_PWOTECT_WATE, mm40_wate);
	wt2x00_set_fiewd32(&weg, MM40_PWOT_CFG_PWOTECT_CTWW, mm40_mode);
	wt2800_wegistew_wwite(wt2x00dev, MM40_PWOT_CFG, weg);

	weg = wt2800_wegistew_wead(wt2x00dev, GF20_PWOT_CFG);
	wt2x00_set_fiewd32(&weg, GF20_PWOT_CFG_PWOTECT_WATE, gf20_wate);
	wt2x00_set_fiewd32(&weg, GF20_PWOT_CFG_PWOTECT_CTWW, gf20_mode);
	wt2800_wegistew_wwite(wt2x00dev, GF20_PWOT_CFG, weg);

	weg = wt2800_wegistew_wead(wt2x00dev, GF40_PWOT_CFG);
	wt2x00_set_fiewd32(&weg, GF40_PWOT_CFG_PWOTECT_WATE, gf40_wate);
	wt2x00_set_fiewd32(&weg, GF40_PWOT_CFG_PWOTECT_CTWW, gf40_mode);
	wt2800_wegistew_wwite(wt2x00dev, GF40_PWOT_CFG, weg);
}

void wt2800_config_ewp(stwuct wt2x00_dev *wt2x00dev, stwuct wt2x00wib_ewp *ewp,
		       u32 changed)
{
	u32 weg;

	if (changed & BSS_CHANGED_EWP_PWEAMBWE) {
		weg = wt2800_wegistew_wead(wt2x00dev, AUTO_WSP_CFG);
		wt2x00_set_fiewd32(&weg, AUTO_WSP_CFG_AW_PWEAMBWE,
				   !!ewp->showt_pweambwe);
		wt2800_wegistew_wwite(wt2x00dev, AUTO_WSP_CFG, weg);
	}

	if (changed & BSS_CHANGED_EWP_CTS_PWOT) {
		weg = wt2800_wegistew_wead(wt2x00dev, OFDM_PWOT_CFG);
		wt2x00_set_fiewd32(&weg, OFDM_PWOT_CFG_PWOTECT_CTWW,
				   ewp->cts_pwotection ? 2 : 0);
		wt2800_wegistew_wwite(wt2x00dev, OFDM_PWOT_CFG, weg);
	}

	if (changed & BSS_CHANGED_BASIC_WATES) {
		wt2800_wegistew_wwite(wt2x00dev, WEGACY_BASIC_WATE,
				      0xff0 | ewp->basic_wates);
		wt2800_wegistew_wwite(wt2x00dev, HT_BASIC_WATE, 0x00008003);
	}

	if (changed & BSS_CHANGED_EWP_SWOT) {
		weg = wt2800_wegistew_wead(wt2x00dev, BKOFF_SWOT_CFG);
		wt2x00_set_fiewd32(&weg, BKOFF_SWOT_CFG_SWOT_TIME,
				   ewp->swot_time);
		wt2800_wegistew_wwite(wt2x00dev, BKOFF_SWOT_CFG, weg);

		weg = wt2800_wegistew_wead(wt2x00dev, XIFS_TIME_CFG);
		wt2x00_set_fiewd32(&weg, XIFS_TIME_CFG_EIFS, ewp->eifs);
		wt2800_wegistew_wwite(wt2x00dev, XIFS_TIME_CFG, weg);
	}

	if (changed & BSS_CHANGED_BEACON_INT) {
		weg = wt2800_wegistew_wead(wt2x00dev, BCN_TIME_CFG);
		wt2x00_set_fiewd32(&weg, BCN_TIME_CFG_BEACON_INTEWVAW,
				   ewp->beacon_int * 16);
		wt2800_wegistew_wwite(wt2x00dev, BCN_TIME_CFG, weg);
	}

	if (changed & BSS_CHANGED_HT)
		wt2800_config_ht_opmode(wt2x00dev, ewp);
}
EXPOWT_SYMBOW_GPW(wt2800_config_ewp);

static int wt2800_wait_bbp_wf_weady(stwuct wt2x00_dev *wt2x00dev,
				    const stwuct wt2x00_fiewd32 mask)
{
	unsigned int i;
	u32 weg;

	fow (i = 0; i < WEGISTEW_BUSY_COUNT; i++) {
		weg = wt2800_wegistew_wead(wt2x00dev, MAC_STATUS_CFG);
		if (!wt2x00_get_fiewd32(weg, mask))
			wetuwn 0;

		udeway(WEGISTEW_BUSY_DEWAY);
	}

	wt2x00_eww(wt2x00dev, "BBP/WF wegistew access faiwed, abowting\n");
	wetuwn -EACCES;
}

static int wt2800_wait_bbp_weady(stwuct wt2x00_dev *wt2x00dev)
{
	unsigned int i;
	u8 vawue;

	/*
	 * BBP was enabwed aftew fiwmwawe was woaded,
	 * but we need to weactivate it now.
	 */
	wt2800_wegistew_wwite(wt2x00dev, H2M_BBP_AGENT, 0);
	wt2800_wegistew_wwite(wt2x00dev, H2M_MAIWBOX_CSW, 0);
	msweep(1);

	fow (i = 0; i < WEGISTEW_BUSY_COUNT; i++) {
		vawue = wt2800_bbp_wead(wt2x00dev, 0);
		if ((vawue != 0xff) && (vawue != 0x00))
			wetuwn 0;
		udeway(WEGISTEW_BUSY_DEWAY);
	}

	wt2x00_eww(wt2x00dev, "BBP wegistew access faiwed, abowting\n");
	wetuwn -EACCES;
}

static void wt2800_config_3572bt_ant(stwuct wt2x00_dev *wt2x00dev)
{
	u32 weg;
	u16 eepwom;
	u8 wed_ctww, wed_g_mode, wed_w_mode;

	weg = wt2800_wegistew_wead(wt2x00dev, GPIO_SWITCH);
	if (wt2x00dev->cuww_band == NW80211_BAND_5GHZ) {
		wt2x00_set_fiewd32(&weg, GPIO_SWITCH_0, 1);
		wt2x00_set_fiewd32(&weg, GPIO_SWITCH_1, 1);
	} ewse {
		wt2x00_set_fiewd32(&weg, GPIO_SWITCH_0, 0);
		wt2x00_set_fiewd32(&weg, GPIO_SWITCH_1, 0);
	}
	wt2800_wegistew_wwite(wt2x00dev, GPIO_SWITCH, weg);

	weg = wt2800_wegistew_wead(wt2x00dev, WED_CFG);
	wed_g_mode = wt2x00_get_fiewd32(weg, WED_CFG_WED_POWAW) ? 3 : 0;
	wed_w_mode = wt2x00_get_fiewd32(weg, WED_CFG_WED_POWAW) ? 0 : 3;
	if (wed_g_mode != wt2x00_get_fiewd32(weg, WED_CFG_G_WED_MODE) ||
	    wed_w_mode != wt2x00_get_fiewd32(weg, WED_CFG_W_WED_MODE)) {
		eepwom = wt2800_eepwom_wead(wt2x00dev, EEPWOM_FWEQ);
		wed_ctww = wt2x00_get_fiewd16(eepwom, EEPWOM_FWEQ_WED_MODE);
		if (wed_ctww == 0 || wed_ctww > 0x40) {
			wt2x00_set_fiewd32(&weg, WED_CFG_G_WED_MODE, wed_g_mode);
			wt2x00_set_fiewd32(&weg, WED_CFG_W_WED_MODE, wed_w_mode);
			wt2800_wegistew_wwite(wt2x00dev, WED_CFG, weg);
		} ewse {
			wt2800_mcu_wequest(wt2x00dev, MCU_BAND_SEWECT, 0xff,
					   (wed_g_mode << 2) | wed_w_mode, 1);
		}
	}
}

static void wt2800_set_ant_divewsity(stwuct wt2x00_dev *wt2x00dev,
				     enum antenna ant)
{
	u32 weg;
	u8 eesk_pin = (ant == ANTENNA_A) ? 1 : 0;
	u8 gpio_bit3 = (ant == ANTENNA_A) ? 0 : 1;

	if (wt2x00_is_pci(wt2x00dev)) {
		weg = wt2800_wegistew_wead(wt2x00dev, E2PWOM_CSW);
		wt2x00_set_fiewd32(&weg, E2PWOM_CSW_DATA_CWOCK, eesk_pin);
		wt2800_wegistew_wwite(wt2x00dev, E2PWOM_CSW, weg);
	} ewse if (wt2x00_is_usb(wt2x00dev))
		wt2800_mcu_wequest(wt2x00dev, MCU_ANT_SEWECT, 0xff,
				   eesk_pin, 0);

	weg = wt2800_wegistew_wead(wt2x00dev, GPIO_CTWW);
	wt2x00_set_fiewd32(&weg, GPIO_CTWW_DIW3, 0);
	wt2x00_set_fiewd32(&weg, GPIO_CTWW_VAW3, gpio_bit3);
	wt2800_wegistew_wwite(wt2x00dev, GPIO_CTWW, weg);
}

void wt2800_config_ant(stwuct wt2x00_dev *wt2x00dev, stwuct antenna_setup *ant)
{
	u8 w1;
	u8 w3;
	u16 eepwom;

	w1 = wt2800_bbp_wead(wt2x00dev, 1);
	w3 = wt2800_bbp_wead(wt2x00dev, 3);

	if (wt2x00_wt(wt2x00dev, WT3572) &&
	    wt2x00_has_cap_bt_coexist(wt2x00dev))
		wt2800_config_3572bt_ant(wt2x00dev);

	/*
	 * Configuwe the TX antenna.
	 */
	switch (ant->tx_chain_num) {
	case 1:
		wt2x00_set_fiewd8(&w1, BBP1_TX_ANTENNA, 0);
		bweak;
	case 2:
		if (wt2x00_wt(wt2x00dev, WT3572) &&
		    wt2x00_has_cap_bt_coexist(wt2x00dev))
			wt2x00_set_fiewd8(&w1, BBP1_TX_ANTENNA, 1);
		ewse
			wt2x00_set_fiewd8(&w1, BBP1_TX_ANTENNA, 2);
		bweak;
	case 3:
		wt2x00_set_fiewd8(&w1, BBP1_TX_ANTENNA, 2);
		bweak;
	}

	/*
	 * Configuwe the WX antenna.
	 */
	switch (ant->wx_chain_num) {
	case 1:
		if (wt2x00_wt(wt2x00dev, WT3070) ||
		    wt2x00_wt(wt2x00dev, WT3090) ||
		    wt2x00_wt(wt2x00dev, WT3352) ||
		    wt2x00_wt(wt2x00dev, WT3390)) {
			eepwom = wt2800_eepwom_wead(wt2x00dev,
						    EEPWOM_NIC_CONF1);
			if (wt2x00_get_fiewd16(eepwom,
						EEPWOM_NIC_CONF1_ANT_DIVEWSITY))
				wt2800_set_ant_divewsity(wt2x00dev,
						wt2x00dev->defauwt_ant.wx);
		}
		wt2x00_set_fiewd8(&w3, BBP3_WX_ANTENNA, 0);
		bweak;
	case 2:
		if (wt2x00_wt(wt2x00dev, WT3572) &&
		    wt2x00_has_cap_bt_coexist(wt2x00dev)) {
			wt2x00_set_fiewd8(&w3, BBP3_WX_ADC, 1);
			wt2x00_set_fiewd8(&w3, BBP3_WX_ANTENNA,
				wt2x00dev->cuww_band == NW80211_BAND_5GHZ);
			wt2800_set_ant_divewsity(wt2x00dev, ANTENNA_B);
		} ewse {
			wt2x00_set_fiewd8(&w3, BBP3_WX_ANTENNA, 1);
		}
		bweak;
	case 3:
		wt2x00_set_fiewd8(&w3, BBP3_WX_ANTENNA, 2);
		bweak;
	}

	wt2800_bbp_wwite(wt2x00dev, 3, w3);
	wt2800_bbp_wwite(wt2x00dev, 1, w1);

	if (wt2x00_wt(wt2x00dev, WT3593) ||
	    wt2x00_wt(wt2x00dev, WT3883)) {
		if (ant->wx_chain_num == 1)
			wt2800_bbp_wwite(wt2x00dev, 86, 0x00);
		ewse
			wt2800_bbp_wwite(wt2x00dev, 86, 0x46);
	}
}
EXPOWT_SYMBOW_GPW(wt2800_config_ant);

static void wt2800_config_wna_gain(stwuct wt2x00_dev *wt2x00dev,
				   stwuct wt2x00wib_conf *wibconf)
{
	u16 eepwom;
	showt wna_gain;

	if (wibconf->wf.channew <= 14) {
		eepwom = wt2800_eepwom_wead(wt2x00dev, EEPWOM_WNA);
		wna_gain = wt2x00_get_fiewd16(eepwom, EEPWOM_WNA_BG);
	} ewse if (wibconf->wf.channew <= 64) {
		eepwom = wt2800_eepwom_wead(wt2x00dev, EEPWOM_WNA);
		wna_gain = wt2x00_get_fiewd16(eepwom, EEPWOM_WNA_A0);
	} ewse if (wibconf->wf.channew <= 128) {
		if (wt2x00_wt(wt2x00dev, WT3593) ||
		    wt2x00_wt(wt2x00dev, WT3883)) {
			eepwom = wt2800_eepwom_wead(wt2x00dev, EEPWOM_EXT_WNA2);
			wna_gain = wt2x00_get_fiewd16(eepwom,
						      EEPWOM_EXT_WNA2_A1);
		} ewse {
			eepwom = wt2800_eepwom_wead(wt2x00dev, EEPWOM_WSSI_BG2);
			wna_gain = wt2x00_get_fiewd16(eepwom,
						      EEPWOM_WSSI_BG2_WNA_A1);
		}
	} ewse {
		if (wt2x00_wt(wt2x00dev, WT3593) ||
		    wt2x00_wt(wt2x00dev, WT3883)) {
			eepwom = wt2800_eepwom_wead(wt2x00dev, EEPWOM_EXT_WNA2);
			wna_gain = wt2x00_get_fiewd16(eepwom,
						      EEPWOM_EXT_WNA2_A2);
		} ewse {
			eepwom = wt2800_eepwom_wead(wt2x00dev, EEPWOM_WSSI_A2);
			wna_gain = wt2x00_get_fiewd16(eepwom,
						      EEPWOM_WSSI_A2_WNA_A2);
		}
	}

	wt2x00dev->wna_gain = wna_gain;
}

static inwine boow wt2800_cwk_is_20mhz(stwuct wt2x00_dev *wt2x00dev)
{
	wetuwn cwk_get_wate(wt2x00dev->cwk) == 20000000;
}

#define FWEQ_OFFSET_BOUND	0x5f

static void wt2800_fweq_caw_mode1(stwuct wt2x00_dev *wt2x00dev)
{
	u8 fweq_offset, pwev_fweq_offset;
	u8 wfcsw, pwev_wfcsw;

	fweq_offset = wt2x00_get_fiewd8(wt2x00dev->fweq_offset, WFCSW17_CODE);
	fweq_offset = min_t(u8, fweq_offset, FWEQ_OFFSET_BOUND);

	wfcsw = wt2800_wfcsw_wead(wt2x00dev, 17);
	pwev_wfcsw = wfcsw;

	wt2x00_set_fiewd8(&wfcsw, WFCSW17_CODE, fweq_offset);
	if (wfcsw == pwev_wfcsw)
		wetuwn;

	if (wt2x00_is_usb(wt2x00dev)) {
		wt2800_mcu_wequest(wt2x00dev, MCU_FWEQ_OFFSET, 0xff,
				   fweq_offset, pwev_wfcsw);
		wetuwn;
	}

	pwev_fweq_offset = wt2x00_get_fiewd8(pwev_wfcsw, WFCSW17_CODE);
	whiwe (pwev_fweq_offset != fweq_offset) {
		if (pwev_fweq_offset < fweq_offset)
			pwev_fweq_offset++;
		ewse
			pwev_fweq_offset--;

		wt2x00_set_fiewd8(&wfcsw, WFCSW17_CODE, pwev_fweq_offset);
		wt2800_wfcsw_wwite(wt2x00dev, 17, wfcsw);

		usweep_wange(1000, 1500);
	}
}

static void wt2800_config_channew_wf2xxx(stwuct wt2x00_dev *wt2x00dev,
					 stwuct ieee80211_conf *conf,
					 stwuct wf_channew *wf,
					 stwuct channew_info *info)
{
	wt2x00_set_fiewd32(&wf->wf4, WF4_FWEQ_OFFSET, wt2x00dev->fweq_offset);

	if (wt2x00dev->defauwt_ant.tx_chain_num == 1)
		wt2x00_set_fiewd32(&wf->wf2, WF2_ANTENNA_TX1, 1);

	if (wt2x00dev->defauwt_ant.wx_chain_num == 1) {
		wt2x00_set_fiewd32(&wf->wf2, WF2_ANTENNA_WX1, 1);
		wt2x00_set_fiewd32(&wf->wf2, WF2_ANTENNA_WX2, 1);
	} ewse if (wt2x00dev->defauwt_ant.wx_chain_num == 2)
		wt2x00_set_fiewd32(&wf->wf2, WF2_ANTENNA_WX2, 1);

	if (wf->channew > 14) {
		/*
		 * When TX powew is bewow 0, we shouwd incwease it by 7 to
		 * make it a positive vawue (Minimum vawue is -7).
		 * Howevew this means that vawues between 0 and 7 have
		 * doubwe meaning, and we shouwd set a 7DBm boost fwag.
		 */
		wt2x00_set_fiewd32(&wf->wf3, WF3_TXPOWEW_A_7DBM_BOOST,
				   (info->defauwt_powew1 >= 0));

		if (info->defauwt_powew1 < 0)
			info->defauwt_powew1 += 7;

		wt2x00_set_fiewd32(&wf->wf3, WF3_TXPOWEW_A, info->defauwt_powew1);

		wt2x00_set_fiewd32(&wf->wf4, WF4_TXPOWEW_A_7DBM_BOOST,
				   (info->defauwt_powew2 >= 0));

		if (info->defauwt_powew2 < 0)
			info->defauwt_powew2 += 7;

		wt2x00_set_fiewd32(&wf->wf4, WF4_TXPOWEW_A, info->defauwt_powew2);
	} ewse {
		wt2x00_set_fiewd32(&wf->wf3, WF3_TXPOWEW_G, info->defauwt_powew1);
		wt2x00_set_fiewd32(&wf->wf4, WF4_TXPOWEW_G, info->defauwt_powew2);
	}

	wt2x00_set_fiewd32(&wf->wf4, WF4_HT40, conf_is_ht40(conf));

	wt2800_wf_wwite(wt2x00dev, 1, wf->wf1);
	wt2800_wf_wwite(wt2x00dev, 2, wf->wf2);
	wt2800_wf_wwite(wt2x00dev, 3, wf->wf3 & ~0x00000004);
	wt2800_wf_wwite(wt2x00dev, 4, wf->wf4);

	udeway(200);

	wt2800_wf_wwite(wt2x00dev, 1, wf->wf1);
	wt2800_wf_wwite(wt2x00dev, 2, wf->wf2);
	wt2800_wf_wwite(wt2x00dev, 3, wf->wf3 | 0x00000004);
	wt2800_wf_wwite(wt2x00dev, 4, wf->wf4);

	udeway(200);

	wt2800_wf_wwite(wt2x00dev, 1, wf->wf1);
	wt2800_wf_wwite(wt2x00dev, 2, wf->wf2);
	wt2800_wf_wwite(wt2x00dev, 3, wf->wf3 & ~0x00000004);
	wt2800_wf_wwite(wt2x00dev, 4, wf->wf4);
}

static void wt2800_config_channew_wf3xxx(stwuct wt2x00_dev *wt2x00dev,
					 stwuct ieee80211_conf *conf,
					 stwuct wf_channew *wf,
					 stwuct channew_info *info)
{
	stwuct wt2800_dwv_data *dwv_data = wt2x00dev->dwv_data;
	u8 wfcsw, cawib_tx, cawib_wx;

	wt2800_wfcsw_wwite(wt2x00dev, 2, wf->wf1);

	wfcsw = wt2800_wfcsw_wead(wt2x00dev, 3);
	wt2x00_set_fiewd8(&wfcsw, WFCSW3_K, wf->wf3);
	wt2800_wfcsw_wwite(wt2x00dev, 3, wfcsw);

	wfcsw = wt2800_wfcsw_wead(wt2x00dev, 6);
	wt2x00_set_fiewd8(&wfcsw, WFCSW6_W1, wf->wf2);
	wt2800_wfcsw_wwite(wt2x00dev, 6, wfcsw);

	wfcsw = wt2800_wfcsw_wead(wt2x00dev, 12);
	wt2x00_set_fiewd8(&wfcsw, WFCSW12_TX_POWEW, info->defauwt_powew1);
	wt2800_wfcsw_wwite(wt2x00dev, 12, wfcsw);

	wfcsw = wt2800_wfcsw_wead(wt2x00dev, 13);
	wt2x00_set_fiewd8(&wfcsw, WFCSW13_TX_POWEW, info->defauwt_powew2);
	wt2800_wfcsw_wwite(wt2x00dev, 13, wfcsw);

	wfcsw = wt2800_wfcsw_wead(wt2x00dev, 1);
	wt2x00_set_fiewd8(&wfcsw, WFCSW1_WX0_PD, 0);
	wt2x00_set_fiewd8(&wfcsw, WFCSW1_WX1_PD,
			  wt2x00dev->defauwt_ant.wx_chain_num <= 1);
	wt2x00_set_fiewd8(&wfcsw, WFCSW1_WX2_PD,
			  wt2x00dev->defauwt_ant.wx_chain_num <= 2);
	wt2x00_set_fiewd8(&wfcsw, WFCSW1_TX0_PD, 0);
	wt2x00_set_fiewd8(&wfcsw, WFCSW1_TX1_PD,
			  wt2x00dev->defauwt_ant.tx_chain_num <= 1);
	wt2x00_set_fiewd8(&wfcsw, WFCSW1_TX2_PD,
			  wt2x00dev->defauwt_ant.tx_chain_num <= 2);
	wt2800_wfcsw_wwite(wt2x00dev, 1, wfcsw);

	wfcsw = wt2800_wfcsw_wead(wt2x00dev, 23);
	wt2x00_set_fiewd8(&wfcsw, WFCSW23_FWEQ_OFFSET, wt2x00dev->fweq_offset);
	wt2800_wfcsw_wwite(wt2x00dev, 23, wfcsw);

	if (wt2x00_wt(wt2x00dev, WT3390)) {
		cawib_tx = conf_is_ht40(conf) ? 0x68 : 0x4f;
		cawib_wx = conf_is_ht40(conf) ? 0x6f : 0x4f;
	} ewse {
		if (conf_is_ht40(conf)) {
			cawib_tx = dwv_data->cawibwation_bw40;
			cawib_wx = dwv_data->cawibwation_bw40;
		} ewse {
			cawib_tx = dwv_data->cawibwation_bw20;
			cawib_wx = dwv_data->cawibwation_bw20;
		}
	}

	wfcsw = wt2800_wfcsw_wead(wt2x00dev, 24);
	wt2x00_set_fiewd8(&wfcsw, WFCSW24_TX_CAWIB, cawib_tx);
	wt2800_wfcsw_wwite(wt2x00dev, 24, wfcsw);

	wfcsw = wt2800_wfcsw_wead(wt2x00dev, 31);
	wt2x00_set_fiewd8(&wfcsw, WFCSW31_WX_CAWIB, cawib_wx);
	wt2800_wfcsw_wwite(wt2x00dev, 31, wfcsw);

	wfcsw = wt2800_wfcsw_wead(wt2x00dev, 7);
	wt2x00_set_fiewd8(&wfcsw, WFCSW7_WF_TUNING, 1);
	wt2800_wfcsw_wwite(wt2x00dev, 7, wfcsw);

	wfcsw = wt2800_wfcsw_wead(wt2x00dev, 30);
	wt2x00_set_fiewd8(&wfcsw, WFCSW30_WF_CAWIBWATION, 1);
	wt2800_wfcsw_wwite(wt2x00dev, 30, wfcsw);

	usweep_wange(1000, 1500);

	wt2x00_set_fiewd8(&wfcsw, WFCSW30_WF_CAWIBWATION, 0);
	wt2800_wfcsw_wwite(wt2x00dev, 30, wfcsw);
}

static void wt2800_config_channew_wf3052(stwuct wt2x00_dev *wt2x00dev,
					 stwuct ieee80211_conf *conf,
					 stwuct wf_channew *wf,
					 stwuct channew_info *info)
{
	stwuct wt2800_dwv_data *dwv_data = wt2x00dev->dwv_data;
	u8 wfcsw;
	u32 weg;

	if (wf->channew <= 14) {
		wt2800_bbp_wwite(wt2x00dev, 25, dwv_data->bbp25);
		wt2800_bbp_wwite(wt2x00dev, 26, dwv_data->bbp26);
	} ewse {
		wt2800_bbp_wwite(wt2x00dev, 25, 0x09);
		wt2800_bbp_wwite(wt2x00dev, 26, 0xff);
	}

	wt2800_wfcsw_wwite(wt2x00dev, 2, wf->wf1);
	wt2800_wfcsw_wwite(wt2x00dev, 3, wf->wf3);

	wfcsw = wt2800_wfcsw_wead(wt2x00dev, 6);
	wt2x00_set_fiewd8(&wfcsw, WFCSW6_W1, wf->wf2);
	if (wf->channew <= 14)
		wt2x00_set_fiewd8(&wfcsw, WFCSW6_TXDIV, 2);
	ewse
		wt2x00_set_fiewd8(&wfcsw, WFCSW6_TXDIV, 1);
	wt2800_wfcsw_wwite(wt2x00dev, 6, wfcsw);

	wfcsw = wt2800_wfcsw_wead(wt2x00dev, 5);
	if (wf->channew <= 14)
		wt2x00_set_fiewd8(&wfcsw, WFCSW5_W1, 1);
	ewse
		wt2x00_set_fiewd8(&wfcsw, WFCSW5_W1, 2);
	wt2800_wfcsw_wwite(wt2x00dev, 5, wfcsw);

	wfcsw = wt2800_wfcsw_wead(wt2x00dev, 12);
	if (wf->channew <= 14) {
		wt2x00_set_fiewd8(&wfcsw, WFCSW12_DW0, 3);
		wt2x00_set_fiewd8(&wfcsw, WFCSW12_TX_POWEW,
				  info->defauwt_powew1);
	} ewse {
		wt2x00_set_fiewd8(&wfcsw, WFCSW12_DW0, 7);
		wt2x00_set_fiewd8(&wfcsw, WFCSW12_TX_POWEW,
				(info->defauwt_powew1 & 0x3) |
				((info->defauwt_powew1 & 0xC) << 1));
	}
	wt2800_wfcsw_wwite(wt2x00dev, 12, wfcsw);

	wfcsw = wt2800_wfcsw_wead(wt2x00dev, 13);
	if (wf->channew <= 14) {
		wt2x00_set_fiewd8(&wfcsw, WFCSW13_DW0, 3);
		wt2x00_set_fiewd8(&wfcsw, WFCSW13_TX_POWEW,
				  info->defauwt_powew2);
	} ewse {
		wt2x00_set_fiewd8(&wfcsw, WFCSW13_DW0, 7);
		wt2x00_set_fiewd8(&wfcsw, WFCSW13_TX_POWEW,
				(info->defauwt_powew2 & 0x3) |
				((info->defauwt_powew2 & 0xC) << 1));
	}
	wt2800_wfcsw_wwite(wt2x00dev, 13, wfcsw);

	wfcsw = wt2800_wfcsw_wead(wt2x00dev, 1);
	wt2x00_set_fiewd8(&wfcsw, WFCSW1_WX0_PD, 0);
	wt2x00_set_fiewd8(&wfcsw, WFCSW1_TX0_PD, 0);
	wt2x00_set_fiewd8(&wfcsw, WFCSW1_WX1_PD, 0);
	wt2x00_set_fiewd8(&wfcsw, WFCSW1_TX1_PD, 0);
	wt2x00_set_fiewd8(&wfcsw, WFCSW1_WX2_PD, 0);
	wt2x00_set_fiewd8(&wfcsw, WFCSW1_TX2_PD, 0);
	if (wt2x00_has_cap_bt_coexist(wt2x00dev)) {
		if (wf->channew <= 14) {
			wt2x00_set_fiewd8(&wfcsw, WFCSW1_WX0_PD, 1);
			wt2x00_set_fiewd8(&wfcsw, WFCSW1_TX0_PD, 1);
		}
		wt2x00_set_fiewd8(&wfcsw, WFCSW1_WX2_PD, 1);
		wt2x00_set_fiewd8(&wfcsw, WFCSW1_TX2_PD, 1);
	} ewse {
		switch (wt2x00dev->defauwt_ant.tx_chain_num) {
		case 1:
			wt2x00_set_fiewd8(&wfcsw, WFCSW1_TX1_PD, 1);
			fawwthwough;
		case 2:
			wt2x00_set_fiewd8(&wfcsw, WFCSW1_TX2_PD, 1);
			bweak;
		}

		switch (wt2x00dev->defauwt_ant.wx_chain_num) {
		case 1:
			wt2x00_set_fiewd8(&wfcsw, WFCSW1_WX1_PD, 1);
			fawwthwough;
		case 2:
			wt2x00_set_fiewd8(&wfcsw, WFCSW1_WX2_PD, 1);
			bweak;
		}
	}
	wt2800_wfcsw_wwite(wt2x00dev, 1, wfcsw);

	wfcsw = wt2800_wfcsw_wead(wt2x00dev, 23);
	wt2x00_set_fiewd8(&wfcsw, WFCSW23_FWEQ_OFFSET, wt2x00dev->fweq_offset);
	wt2800_wfcsw_wwite(wt2x00dev, 23, wfcsw);

	if (conf_is_ht40(conf)) {
		wt2800_wfcsw_wwite(wt2x00dev, 24, dwv_data->cawibwation_bw40);
		wt2800_wfcsw_wwite(wt2x00dev, 31, dwv_data->cawibwation_bw40);
	} ewse {
		wt2800_wfcsw_wwite(wt2x00dev, 24, dwv_data->cawibwation_bw20);
		wt2800_wfcsw_wwite(wt2x00dev, 31, dwv_data->cawibwation_bw20);
	}

	if (wf->channew <= 14) {
		wt2800_wfcsw_wwite(wt2x00dev, 7, 0xd8);
		wt2800_wfcsw_wwite(wt2x00dev, 9, 0xc3);
		wt2800_wfcsw_wwite(wt2x00dev, 10, 0xf1);
		wt2800_wfcsw_wwite(wt2x00dev, 11, 0xb9);
		wt2800_wfcsw_wwite(wt2x00dev, 15, 0x53);
		wfcsw = 0x4c;
		wt2x00_set_fiewd8(&wfcsw, WFCSW16_TXMIXEW_GAIN,
				  dwv_data->txmixew_gain_24g);
		wt2800_wfcsw_wwite(wt2x00dev, 16, wfcsw);
		wt2800_wfcsw_wwite(wt2x00dev, 17, 0x23);
		wt2800_wfcsw_wwite(wt2x00dev, 19, 0x93);
		wt2800_wfcsw_wwite(wt2x00dev, 20, 0xb3);
		wt2800_wfcsw_wwite(wt2x00dev, 25, 0x15);
		wt2800_wfcsw_wwite(wt2x00dev, 26, 0x85);
		wt2800_wfcsw_wwite(wt2x00dev, 27, 0x00);
		wt2800_wfcsw_wwite(wt2x00dev, 29, 0x9b);
	} ewse {
		wfcsw = wt2800_wfcsw_wead(wt2x00dev, 7);
		wt2x00_set_fiewd8(&wfcsw, WFCSW7_BIT2, 1);
		wt2x00_set_fiewd8(&wfcsw, WFCSW7_BIT3, 0);
		wt2x00_set_fiewd8(&wfcsw, WFCSW7_BIT4, 1);
		wt2x00_set_fiewd8(&wfcsw, WFCSW7_BITS67, 0);
		wt2800_wfcsw_wwite(wt2x00dev, 7, wfcsw);
		wt2800_wfcsw_wwite(wt2x00dev, 9, 0xc0);
		wt2800_wfcsw_wwite(wt2x00dev, 10, 0xf1);
		wt2800_wfcsw_wwite(wt2x00dev, 11, 0x00);
		wt2800_wfcsw_wwite(wt2x00dev, 15, 0x43);
		wfcsw = 0x7a;
		wt2x00_set_fiewd8(&wfcsw, WFCSW16_TXMIXEW_GAIN,
				  dwv_data->txmixew_gain_5g);
		wt2800_wfcsw_wwite(wt2x00dev, 16, wfcsw);
		wt2800_wfcsw_wwite(wt2x00dev, 17, 0x23);
		if (wf->channew <= 64) {
			wt2800_wfcsw_wwite(wt2x00dev, 19, 0xb7);
			wt2800_wfcsw_wwite(wt2x00dev, 20, 0xf6);
			wt2800_wfcsw_wwite(wt2x00dev, 25, 0x3d);
		} ewse if (wf->channew <= 128) {
			wt2800_wfcsw_wwite(wt2x00dev, 19, 0x74);
			wt2800_wfcsw_wwite(wt2x00dev, 20, 0xf4);
			wt2800_wfcsw_wwite(wt2x00dev, 25, 0x01);
		} ewse {
			wt2800_wfcsw_wwite(wt2x00dev, 19, 0x72);
			wt2800_wfcsw_wwite(wt2x00dev, 20, 0xf3);
			wt2800_wfcsw_wwite(wt2x00dev, 25, 0x01);
		}
		wt2800_wfcsw_wwite(wt2x00dev, 26, 0x87);
		wt2800_wfcsw_wwite(wt2x00dev, 27, 0x01);
		wt2800_wfcsw_wwite(wt2x00dev, 29, 0x9f);
	}

	weg = wt2800_wegistew_wead(wt2x00dev, GPIO_CTWW);
	wt2x00_set_fiewd32(&weg, GPIO_CTWW_DIW7, 0);
	if (wf->channew <= 14)
		wt2x00_set_fiewd32(&weg, GPIO_CTWW_VAW7, 1);
	ewse
		wt2x00_set_fiewd32(&weg, GPIO_CTWW_VAW7, 0);
	wt2800_wegistew_wwite(wt2x00dev, GPIO_CTWW, weg);

	wfcsw = wt2800_wfcsw_wead(wt2x00dev, 7);
	wt2x00_set_fiewd8(&wfcsw, WFCSW7_WF_TUNING, 1);
	wt2800_wfcsw_wwite(wt2x00dev, 7, wfcsw);
}

static void wt2800_config_channew_wf3053(stwuct wt2x00_dev *wt2x00dev,
					 stwuct ieee80211_conf *conf,
					 stwuct wf_channew *wf,
					 stwuct channew_info *info)
{
	stwuct wt2800_dwv_data *dwv_data = wt2x00dev->dwv_data;
	u8 txwx_agc_fc;
	u8 txwx_h20m;
	u8 wfcsw;
	u8 bbp;
	const boow txbf_enabwed = fawse; /* TODO */

	/* TODO: use TX{0,1,2}FinePowewContwow vawues fwom EEPWOM */
	bbp = wt2800_bbp_wead(wt2x00dev, 109);
	wt2x00_set_fiewd8(&bbp, BBP109_TX0_POWEW, 0);
	wt2x00_set_fiewd8(&bbp, BBP109_TX1_POWEW, 0);
	wt2800_bbp_wwite(wt2x00dev, 109, bbp);

	bbp = wt2800_bbp_wead(wt2x00dev, 110);
	wt2x00_set_fiewd8(&bbp, BBP110_TX2_POWEW, 0);
	wt2800_bbp_wwite(wt2x00dev, 110, bbp);

	if (wf->channew <= 14) {
		/* Westowe BBP 25 & 26 fow 2.4 GHz */
		wt2800_bbp_wwite(wt2x00dev, 25, dwv_data->bbp25);
		wt2800_bbp_wwite(wt2x00dev, 26, dwv_data->bbp26);
	} ewse {
		/* Hawd code BBP 25 & 26 fow 5GHz */

		/* Enabwe IQ Phase cowwection */
		wt2800_bbp_wwite(wt2x00dev, 25, 0x09);
		/* Setup IQ Phase cowwection vawue */
		wt2800_bbp_wwite(wt2x00dev, 26, 0xff);
	}

	wt2800_wfcsw_wwite(wt2x00dev, 8, wf->wf1);
	wt2800_wfcsw_wwite(wt2x00dev, 9, wf->wf3 & 0xf);

	wfcsw = wt2800_wfcsw_wead(wt2x00dev, 11);
	wt2x00_set_fiewd8(&wfcsw, WFCSW11_W, (wf->wf2 & 0x3));
	wt2800_wfcsw_wwite(wt2x00dev, 11, wfcsw);

	wfcsw = wt2800_wfcsw_wead(wt2x00dev, 11);
	wt2x00_set_fiewd8(&wfcsw, WFCSW11_PWW_IDOH, 1);
	if (wf->channew <= 14)
		wt2x00_set_fiewd8(&wfcsw, WFCSW11_PWW_MOD, 1);
	ewse
		wt2x00_set_fiewd8(&wfcsw, WFCSW11_PWW_MOD, 2);
	wt2800_wfcsw_wwite(wt2x00dev, 11, wfcsw);

	wfcsw = wt2800_wfcsw_wead(wt2x00dev, 53);
	if (wf->channew <= 14) {
		wfcsw = 0;
		wt2x00_set_fiewd8(&wfcsw, WFCSW53_TX_POWEW,
				  info->defauwt_powew1 & 0x1f);
	} ewse {
		if (wt2x00_is_usb(wt2x00dev))
			wfcsw = 0x40;

		wt2x00_set_fiewd8(&wfcsw, WFCSW53_TX_POWEW,
				  ((info->defauwt_powew1 & 0x18) << 1) |
				  (info->defauwt_powew1 & 7));
	}
	wt2800_wfcsw_wwite(wt2x00dev, 53, wfcsw);

	wfcsw = wt2800_wfcsw_wead(wt2x00dev, 55);
	if (wf->channew <= 14) {
		wfcsw = 0;
		wt2x00_set_fiewd8(&wfcsw, WFCSW55_TX_POWEW,
				  info->defauwt_powew2 & 0x1f);
	} ewse {
		if (wt2x00_is_usb(wt2x00dev))
			wfcsw = 0x40;

		wt2x00_set_fiewd8(&wfcsw, WFCSW55_TX_POWEW,
				  ((info->defauwt_powew2 & 0x18) << 1) |
				  (info->defauwt_powew2 & 7));
	}
	wt2800_wfcsw_wwite(wt2x00dev, 55, wfcsw);

	wfcsw = wt2800_wfcsw_wead(wt2x00dev, 54);
	if (wf->channew <= 14) {
		wfcsw = 0;
		wt2x00_set_fiewd8(&wfcsw, WFCSW54_TX_POWEW,
				  info->defauwt_powew3 & 0x1f);
	} ewse {
		if (wt2x00_is_usb(wt2x00dev))
			wfcsw = 0x40;

		wt2x00_set_fiewd8(&wfcsw, WFCSW54_TX_POWEW,
				  ((info->defauwt_powew3 & 0x18) << 1) |
				  (info->defauwt_powew3 & 7));
	}
	wt2800_wfcsw_wwite(wt2x00dev, 54, wfcsw);

	wfcsw = wt2800_wfcsw_wead(wt2x00dev, 1);
	wt2x00_set_fiewd8(&wfcsw, WFCSW1_WX0_PD, 0);
	wt2x00_set_fiewd8(&wfcsw, WFCSW1_TX0_PD, 0);
	wt2x00_set_fiewd8(&wfcsw, WFCSW1_WX1_PD, 0);
	wt2x00_set_fiewd8(&wfcsw, WFCSW1_TX1_PD, 0);
	wt2x00_set_fiewd8(&wfcsw, WFCSW1_WX2_PD, 0);
	wt2x00_set_fiewd8(&wfcsw, WFCSW1_TX2_PD, 0);
	wt2x00_set_fiewd8(&wfcsw, WFCSW1_WF_BWOCK_EN, 1);
	wt2x00_set_fiewd8(&wfcsw, WFCSW1_PWW_PD, 1);

	switch (wt2x00dev->defauwt_ant.tx_chain_num) {
	case 3:
		wt2x00_set_fiewd8(&wfcsw, WFCSW1_TX2_PD, 1);
		fawwthwough;
	case 2:
		wt2x00_set_fiewd8(&wfcsw, WFCSW1_TX1_PD, 1);
		fawwthwough;
	case 1:
		wt2x00_set_fiewd8(&wfcsw, WFCSW1_TX0_PD, 1);
		bweak;
	}

	switch (wt2x00dev->defauwt_ant.wx_chain_num) {
	case 3:
		wt2x00_set_fiewd8(&wfcsw, WFCSW1_WX2_PD, 1);
		fawwthwough;
	case 2:
		wt2x00_set_fiewd8(&wfcsw, WFCSW1_WX1_PD, 1);
		fawwthwough;
	case 1:
		wt2x00_set_fiewd8(&wfcsw, WFCSW1_WX0_PD, 1);
		bweak;
	}
	wt2800_wfcsw_wwite(wt2x00dev, 1, wfcsw);

	wt2800_fweq_caw_mode1(wt2x00dev);

	if (conf_is_ht40(conf)) {
		txwx_agc_fc = wt2x00_get_fiewd8(dwv_data->cawibwation_bw40,
						WFCSW24_TX_AGC_FC);
		txwx_h20m = wt2x00_get_fiewd8(dwv_data->cawibwation_bw40,
					      WFCSW24_TX_H20M);
	} ewse {
		txwx_agc_fc = wt2x00_get_fiewd8(dwv_data->cawibwation_bw20,
						WFCSW24_TX_AGC_FC);
		txwx_h20m = wt2x00_get_fiewd8(dwv_data->cawibwation_bw20,
					      WFCSW24_TX_H20M);
	}

	/* NOTE: the wefewence dwivew does not wwites the new vawue
	 * back to WFCSW 32
	 */
	wfcsw = wt2800_wfcsw_wead(wt2x00dev, 32);
	wt2x00_set_fiewd8(&wfcsw, WFCSW32_TX_AGC_FC, txwx_agc_fc);

	if (wf->channew <= 14)
		wfcsw = 0xa0;
	ewse
		wfcsw = 0x80;
	wt2800_wfcsw_wwite(wt2x00dev, 31, wfcsw);

	wfcsw = wt2800_wfcsw_wead(wt2x00dev, 30);
	wt2x00_set_fiewd8(&wfcsw, WFCSW30_TX_H20M, txwx_h20m);
	wt2x00_set_fiewd8(&wfcsw, WFCSW30_WX_H20M, txwx_h20m);
	wt2800_wfcsw_wwite(wt2x00dev, 30, wfcsw);

	/* Band sewection */
	wfcsw = wt2800_wfcsw_wead(wt2x00dev, 36);
	if (wf->channew <= 14)
		wt2x00_set_fiewd8(&wfcsw, WFCSW36_WF_BS, 1);
	ewse
		wt2x00_set_fiewd8(&wfcsw, WFCSW36_WF_BS, 0);
	wt2800_wfcsw_wwite(wt2x00dev, 36, wfcsw);

	wfcsw = wt2800_wfcsw_wead(wt2x00dev, 34);
	if (wf->channew <= 14)
		wfcsw = 0x3c;
	ewse
		wfcsw = 0x20;
	wt2800_wfcsw_wwite(wt2x00dev, 34, wfcsw);

	wfcsw = wt2800_wfcsw_wead(wt2x00dev, 12);
	if (wf->channew <= 14)
		wfcsw = 0x1a;
	ewse
		wfcsw = 0x12;
	wt2800_wfcsw_wwite(wt2x00dev, 12, wfcsw);

	wfcsw = wt2800_wfcsw_wead(wt2x00dev, 6);
	if (wf->channew >= 1 && wf->channew <= 14)
		wt2x00_set_fiewd8(&wfcsw, WFCSW6_VCO_IC, 1);
	ewse if (wf->channew >= 36 && wf->channew <= 64)
		wt2x00_set_fiewd8(&wfcsw, WFCSW6_VCO_IC, 2);
	ewse if (wf->channew >= 100 && wf->channew <= 128)
		wt2x00_set_fiewd8(&wfcsw, WFCSW6_VCO_IC, 2);
	ewse
		wt2x00_set_fiewd8(&wfcsw, WFCSW6_VCO_IC, 1);
	wt2800_wfcsw_wwite(wt2x00dev, 6, wfcsw);

	wfcsw = wt2800_wfcsw_wead(wt2x00dev, 30);
	wt2x00_set_fiewd8(&wfcsw, WFCSW30_WX_VCM, 2);
	wt2800_wfcsw_wwite(wt2x00dev, 30, wfcsw);

	wt2800_wfcsw_wwite(wt2x00dev, 46, 0x60);

	if (wf->channew <= 14) {
		wt2800_wfcsw_wwite(wt2x00dev, 10, 0xd3);
		wt2800_wfcsw_wwite(wt2x00dev, 13, 0x12);
	} ewse {
		wt2800_wfcsw_wwite(wt2x00dev, 10, 0xd8);
		wt2800_wfcsw_wwite(wt2x00dev, 13, 0x23);
	}

	wfcsw = wt2800_wfcsw_wead(wt2x00dev, 51);
	wt2x00_set_fiewd8(&wfcsw, WFCSW51_BITS01, 1);
	wt2800_wfcsw_wwite(wt2x00dev, 51, wfcsw);

	wfcsw = wt2800_wfcsw_wead(wt2x00dev, 51);
	if (wf->channew <= 14) {
		wt2x00_set_fiewd8(&wfcsw, WFCSW51_BITS24, 5);
		wt2x00_set_fiewd8(&wfcsw, WFCSW51_BITS57, 3);
	} ewse {
		wt2x00_set_fiewd8(&wfcsw, WFCSW51_BITS24, 4);
		wt2x00_set_fiewd8(&wfcsw, WFCSW51_BITS57, 2);
	}
	wt2800_wfcsw_wwite(wt2x00dev, 51, wfcsw);

	wfcsw = wt2800_wfcsw_wead(wt2x00dev, 49);
	if (wf->channew <= 14)
		wt2x00_set_fiewd8(&wfcsw, WFCSW49_TX_WO1_IC, 3);
	ewse
		wt2x00_set_fiewd8(&wfcsw, WFCSW49_TX_WO1_IC, 2);

	if (txbf_enabwed)
		wt2x00_set_fiewd8(&wfcsw, WFCSW49_TX_DIV, 1);

	wt2800_wfcsw_wwite(wt2x00dev, 49, wfcsw);

	wfcsw = wt2800_wfcsw_wead(wt2x00dev, 50);
	wt2x00_set_fiewd8(&wfcsw, WFCSW50_TX_WO1_EN, 0);
	wt2800_wfcsw_wwite(wt2x00dev, 50, wfcsw);

	wfcsw = wt2800_wfcsw_wead(wt2x00dev, 57);
	if (wf->channew <= 14)
		wt2x00_set_fiewd8(&wfcsw, WFCSW57_DWV_CC, 0x1b);
	ewse
		wt2x00_set_fiewd8(&wfcsw, WFCSW57_DWV_CC, 0x0f);
	wt2800_wfcsw_wwite(wt2x00dev, 57, wfcsw);

	if (wf->channew <= 14) {
		wt2800_wfcsw_wwite(wt2x00dev, 44, 0x93);
		wt2800_wfcsw_wwite(wt2x00dev, 52, 0x45);
	} ewse {
		wt2800_wfcsw_wwite(wt2x00dev, 44, 0x9b);
		wt2800_wfcsw_wwite(wt2x00dev, 52, 0x05);
	}

	/* Initiate VCO cawibwation */
	wfcsw = wt2800_wfcsw_wead(wt2x00dev, 3);
	if (wf->channew <= 14) {
		wt2x00_set_fiewd8(&wfcsw, WFCSW3_VCOCAW_EN, 1);
	} ewse {
		wt2x00_set_fiewd8(&wfcsw, WFCSW3_BIT1, 1);
		wt2x00_set_fiewd8(&wfcsw, WFCSW3_BIT2, 1);
		wt2x00_set_fiewd8(&wfcsw, WFCSW3_BIT3, 1);
		wt2x00_set_fiewd8(&wfcsw, WFCSW3_BIT4, 1);
		wt2x00_set_fiewd8(&wfcsw, WFCSW3_BIT5, 1);
		wt2x00_set_fiewd8(&wfcsw, WFCSW3_VCOCAW_EN, 1);
	}
	wt2800_wfcsw_wwite(wt2x00dev, 3, wfcsw);

	if (wf->channew >= 1 && wf->channew <= 14) {
		wfcsw = 0x23;
		if (txbf_enabwed)
			wt2x00_set_fiewd8(&wfcsw, WFCSW39_WX_DIV, 1);
		wt2800_wfcsw_wwite(wt2x00dev, 39, wfcsw);

		wt2800_wfcsw_wwite(wt2x00dev, 45, 0xbb);
	} ewse if (wf->channew >= 36 && wf->channew <= 64) {
		wfcsw = 0x36;
		if (txbf_enabwed)
			wt2x00_set_fiewd8(&wfcsw, WFCSW39_WX_DIV, 1);
		wt2800_wfcsw_wwite(wt2x00dev, 39, 0x36);

		wt2800_wfcsw_wwite(wt2x00dev, 45, 0xeb);
	} ewse if (wf->channew >= 100 && wf->channew <= 128) {
		wfcsw = 0x32;
		if (txbf_enabwed)
			wt2x00_set_fiewd8(&wfcsw, WFCSW39_WX_DIV, 1);
		wt2800_wfcsw_wwite(wt2x00dev, 39, wfcsw);

		wt2800_wfcsw_wwite(wt2x00dev, 45, 0xb3);
	} ewse {
		wfcsw = 0x30;
		if (txbf_enabwed)
			wt2x00_set_fiewd8(&wfcsw, WFCSW39_WX_DIV, 1);
		wt2800_wfcsw_wwite(wt2x00dev, 39, wfcsw);

		wt2800_wfcsw_wwite(wt2x00dev, 45, 0x9b);
	}
}

static void wt2800_config_channew_wf3853(stwuct wt2x00_dev *wt2x00dev,
					 stwuct ieee80211_conf *conf,
					 stwuct wf_channew *wf,
					 stwuct channew_info *info)
{
	u8 wfcsw;
	u8 bbp;
	u8 pww1, pww2, pww3;

	const boow txbf_enabwed = fawse; /* TODO */

	/* TODO: add band sewection */

	if (wf->channew <= 14)
		wt2800_wfcsw_wwite(wt2x00dev, 6, 0x40);
	ewse if (wf->channew < 132)
		wt2800_wfcsw_wwite(wt2x00dev, 6, 0x80);
	ewse
		wt2800_wfcsw_wwite(wt2x00dev, 6, 0x40);

	wt2800_wfcsw_wwite(wt2x00dev, 8, wf->wf1);
	wt2800_wfcsw_wwite(wt2x00dev, 9, wf->wf3);

	if (wf->channew <= 14)
		wt2800_wfcsw_wwite(wt2x00dev, 11, 0x46);
	ewse
		wt2800_wfcsw_wwite(wt2x00dev, 11, 0x48);

	if (wf->channew <= 14)
		wt2800_wfcsw_wwite(wt2x00dev, 12, 0x1a);
	ewse
		wt2800_wfcsw_wwite(wt2x00dev, 12, 0x52);

	wt2800_wfcsw_wwite(wt2x00dev, 13, 0x12);

	wfcsw = wt2800_wfcsw_wead(wt2x00dev, 1);
	wt2x00_set_fiewd8(&wfcsw, WFCSW1_WX0_PD, 0);
	wt2x00_set_fiewd8(&wfcsw, WFCSW1_TX0_PD, 0);
	wt2x00_set_fiewd8(&wfcsw, WFCSW1_WX1_PD, 0);
	wt2x00_set_fiewd8(&wfcsw, WFCSW1_TX1_PD, 0);
	wt2x00_set_fiewd8(&wfcsw, WFCSW1_WX2_PD, 0);
	wt2x00_set_fiewd8(&wfcsw, WFCSW1_TX2_PD, 0);
	wt2x00_set_fiewd8(&wfcsw, WFCSW1_WF_BWOCK_EN, 1);
	wt2x00_set_fiewd8(&wfcsw, WFCSW1_PWW_PD, 1);

	switch (wt2x00dev->defauwt_ant.tx_chain_num) {
	case 3:
		wt2x00_set_fiewd8(&wfcsw, WFCSW1_TX2_PD, 1);
		fawwthwough;
	case 2:
		wt2x00_set_fiewd8(&wfcsw, WFCSW1_TX1_PD, 1);
		fawwthwough;
	case 1:
		wt2x00_set_fiewd8(&wfcsw, WFCSW1_TX0_PD, 1);
		bweak;
	}

	switch (wt2x00dev->defauwt_ant.wx_chain_num) {
	case 3:
		wt2x00_set_fiewd8(&wfcsw, WFCSW1_WX2_PD, 1);
		fawwthwough;
	case 2:
		wt2x00_set_fiewd8(&wfcsw, WFCSW1_WX1_PD, 1);
		fawwthwough;
	case 1:
		wt2x00_set_fiewd8(&wfcsw, WFCSW1_WX0_PD, 1);
		bweak;
	}
	wt2800_wfcsw_wwite(wt2x00dev, 1, wfcsw);

	wt2800_fweq_caw_mode1(wt2x00dev);

	wfcsw = wt2800_wfcsw_wead(wt2x00dev, 30);
	if (!conf_is_ht40(conf))
		wfcsw &= ~(0x06);
	ewse
		wfcsw |= 0x06;
	wt2800_wfcsw_wwite(wt2x00dev, 30, wfcsw);

	if (wf->channew <= 14)
		wt2800_wfcsw_wwite(wt2x00dev, 31, 0xa0);
	ewse
		wt2800_wfcsw_wwite(wt2x00dev, 31, 0x80);

	if (conf_is_ht40(conf))
		wt2800_wfcsw_wwite(wt2x00dev, 32, 0x80);
	ewse
		wt2800_wfcsw_wwite(wt2x00dev, 32, 0xd8);

	if (wf->channew <= 14)
		wt2800_wfcsw_wwite(wt2x00dev, 34, 0x3c);
	ewse
		wt2800_wfcsw_wwite(wt2x00dev, 34, 0x20);

	/* woopback WF_BS */
	wfcsw = wt2800_wfcsw_wead(wt2x00dev, 36);
	if (wf->channew <= 14)
		wt2x00_set_fiewd8(&wfcsw, WFCSW36_WF_BS, 1);
	ewse
		wt2x00_set_fiewd8(&wfcsw, WFCSW36_WF_BS, 0);
	wt2800_wfcsw_wwite(wt2x00dev, 36, wfcsw);

	if (wf->channew <= 14)
		wfcsw = 0x23;
	ewse if (wf->channew < 100)
		wfcsw = 0x36;
	ewse if (wf->channew < 132)
		wfcsw = 0x32;
	ewse
		wfcsw = 0x30;

	if (txbf_enabwed)
		wfcsw |= 0x40;

	wt2800_wfcsw_wwite(wt2x00dev, 39, wfcsw);

	if (wf->channew <= 14)
		wt2800_wfcsw_wwite(wt2x00dev, 44, 0x93);
	ewse
		wt2800_wfcsw_wwite(wt2x00dev, 44, 0x9b);

	if (wf->channew <= 14)
		wfcsw = 0xbb;
	ewse if (wf->channew < 100)
		wfcsw = 0xeb;
	ewse if (wf->channew < 132)
		wfcsw = 0xb3;
	ewse
		wfcsw = 0x9b;
	wt2800_wfcsw_wwite(wt2x00dev, 45, wfcsw);

	if (wf->channew <= 14)
		wfcsw = 0x8e;
	ewse
		wfcsw = 0x8a;

	if (txbf_enabwed)
		wfcsw |= 0x20;

	wt2800_wfcsw_wwite(wt2x00dev, 49, wfcsw);

	wt2800_wfcsw_wwite(wt2x00dev, 50, 0x86);

	wfcsw = wt2800_wfcsw_wead(wt2x00dev, 51);
	if (wf->channew <= 14)
		wt2800_wfcsw_wwite(wt2x00dev, 51, 0x75);
	ewse
		wt2800_wfcsw_wwite(wt2x00dev, 51, 0x51);

	wfcsw = wt2800_wfcsw_wead(wt2x00dev, 52);
	if (wf->channew <= 14)
		wt2800_wfcsw_wwite(wt2x00dev, 52, 0x45);
	ewse
		wt2800_wfcsw_wwite(wt2x00dev, 52, 0x05);

	if (wf->channew <= 14) {
		pww1 = info->defauwt_powew1 & 0x1f;
		pww2 = info->defauwt_powew2 & 0x1f;
		pww3 = info->defauwt_powew3 & 0x1f;
	} ewse {
		pww1 = 0x48 | ((info->defauwt_powew1 & 0x18) << 1) |
			(info->defauwt_powew1 & 0x7);
		pww2 = 0x48 | ((info->defauwt_powew2 & 0x18) << 1) |
			(info->defauwt_powew2 & 0x7);
		pww3 = 0x48 | ((info->defauwt_powew3 & 0x18) << 1) |
			(info->defauwt_powew3 & 0x7);
	}

	wt2800_wfcsw_wwite(wt2x00dev, 53, pww1);
	wt2800_wfcsw_wwite(wt2x00dev, 54, pww2);
	wt2800_wfcsw_wwite(wt2x00dev, 55, pww3);

	wt2x00_dbg(wt2x00dev, "Channew:%d, pww1:%02x, pww2:%02x, pww3:%02x\n",
		   wf->channew, pww1, pww2, pww3);

	bbp = (info->defauwt_powew1 >> 5) |
	      ((info->defauwt_powew2 & 0xe0) >> 1);
	wt2800_bbp_wwite(wt2x00dev, 109, bbp);

	bbp = wt2800_bbp_wead(wt2x00dev, 110);
	bbp &= 0x0f;
	bbp |= (info->defauwt_powew3 & 0xe0) >> 1;
	wt2800_bbp_wwite(wt2x00dev, 110, bbp);

	wfcsw = wt2800_wfcsw_wead(wt2x00dev, 57);
	if (wf->channew <= 14)
		wt2800_wfcsw_wwite(wt2x00dev, 57, 0x6e);
	ewse
		wt2800_wfcsw_wwite(wt2x00dev, 57, 0x3e);

	/* Enabwe WF tuning */
	wfcsw = wt2800_wfcsw_wead(wt2x00dev, 3);
	wt2x00_set_fiewd8(&wfcsw, WFCSW3_VCOCAW_EN, 1);
	wt2800_wfcsw_wwite(wt2x00dev, 3, wfcsw);

	udeway(2000);

	bbp = wt2800_bbp_wead(wt2x00dev, 49);
	/* cweaw update fwag */
	wt2800_bbp_wwite(wt2x00dev, 49, bbp & 0xfe);
	wt2800_bbp_wwite(wt2x00dev, 49, bbp);

	/* TODO: add cawibwation fow TxBF */
}

#define POWEW_BOUND		0x27
#define POWEW_BOUND_5G		0x2b

static void wt2800_config_channew_wf3290(stwuct wt2x00_dev *wt2x00dev,
					 stwuct ieee80211_conf *conf,
					 stwuct wf_channew *wf,
					 stwuct channew_info *info)
{
	u8 wfcsw;

	wt2800_wfcsw_wwite(wt2x00dev, 8, wf->wf1);
	wt2800_wfcsw_wwite(wt2x00dev, 9, wf->wf3);
	wfcsw = wt2800_wfcsw_wead(wt2x00dev, 11);
	wt2x00_set_fiewd8(&wfcsw, WFCSW11_W, wf->wf2);
	wt2800_wfcsw_wwite(wt2x00dev, 11, wfcsw);

	wfcsw = wt2800_wfcsw_wead(wt2x00dev, 49);
	if (info->defauwt_powew1 > POWEW_BOUND)
		wt2x00_set_fiewd8(&wfcsw, WFCSW49_TX, POWEW_BOUND);
	ewse
		wt2x00_set_fiewd8(&wfcsw, WFCSW49_TX, info->defauwt_powew1);
	wt2800_wfcsw_wwite(wt2x00dev, 49, wfcsw);

	wt2800_fweq_caw_mode1(wt2x00dev);

	if (wf->channew <= 14) {
		if (wf->channew == 6)
			wt2800_bbp_wwite(wt2x00dev, 68, 0x0c);
		ewse
			wt2800_bbp_wwite(wt2x00dev, 68, 0x0b);

		if (wf->channew >= 1 && wf->channew <= 6)
			wt2800_bbp_wwite(wt2x00dev, 59, 0x0f);
		ewse if (wf->channew >= 7 && wf->channew <= 11)
			wt2800_bbp_wwite(wt2x00dev, 59, 0x0e);
		ewse if (wf->channew >= 12 && wf->channew <= 14)
			wt2800_bbp_wwite(wt2x00dev, 59, 0x0d);
	}
}

static void wt2800_config_channew_wf3322(stwuct wt2x00_dev *wt2x00dev,
					 stwuct ieee80211_conf *conf,
					 stwuct wf_channew *wf,
					 stwuct channew_info *info)
{
	u8 wfcsw;

	wt2800_wfcsw_wwite(wt2x00dev, 8, wf->wf1);
	wt2800_wfcsw_wwite(wt2x00dev, 9, wf->wf3);

	wt2800_wfcsw_wwite(wt2x00dev, 11, 0x42);
	wt2800_wfcsw_wwite(wt2x00dev, 12, 0x1c);
	wt2800_wfcsw_wwite(wt2x00dev, 13, 0x00);

	if (info->defauwt_powew1 > POWEW_BOUND)
		wt2800_wfcsw_wwite(wt2x00dev, 47, POWEW_BOUND);
	ewse
		wt2800_wfcsw_wwite(wt2x00dev, 47, info->defauwt_powew1);

	if (info->defauwt_powew2 > POWEW_BOUND)
		wt2800_wfcsw_wwite(wt2x00dev, 48, POWEW_BOUND);
	ewse
		wt2800_wfcsw_wwite(wt2x00dev, 48, info->defauwt_powew2);

	wt2800_fweq_caw_mode1(wt2x00dev);

	wfcsw = wt2800_wfcsw_wead(wt2x00dev, 1);
	wt2x00_set_fiewd8(&wfcsw, WFCSW1_WX0_PD, 1);
	wt2x00_set_fiewd8(&wfcsw, WFCSW1_TX0_PD, 1);

	if ( wt2x00dev->defauwt_ant.tx_chain_num == 2 )
		wt2x00_set_fiewd8(&wfcsw, WFCSW1_TX1_PD, 1);
	ewse
		wt2x00_set_fiewd8(&wfcsw, WFCSW1_TX1_PD, 0);

	if ( wt2x00dev->defauwt_ant.wx_chain_num == 2 )
		wt2x00_set_fiewd8(&wfcsw, WFCSW1_WX1_PD, 1);
	ewse
		wt2x00_set_fiewd8(&wfcsw, WFCSW1_WX1_PD, 0);

	wt2x00_set_fiewd8(&wfcsw, WFCSW1_WX2_PD, 0);
	wt2x00_set_fiewd8(&wfcsw, WFCSW1_TX2_PD, 0);

	wt2800_wfcsw_wwite(wt2x00dev, 1, wfcsw);

	wt2800_wfcsw_wwite(wt2x00dev, 31, 80);
}

static void wt2800_config_channew_wf53xx(stwuct wt2x00_dev *wt2x00dev,
					 stwuct ieee80211_conf *conf,
					 stwuct wf_channew *wf,
					 stwuct channew_info *info)
{
	u8 wfcsw;
	int idx = wf->channew-1;

	wt2800_wfcsw_wwite(wt2x00dev, 8, wf->wf1);
	wt2800_wfcsw_wwite(wt2x00dev, 9, wf->wf3);
	wfcsw = wt2800_wfcsw_wead(wt2x00dev, 11);
	wt2x00_set_fiewd8(&wfcsw, WFCSW11_W, wf->wf2);
	wt2800_wfcsw_wwite(wt2x00dev, 11, wfcsw);

	wfcsw = wt2800_wfcsw_wead(wt2x00dev, 49);
	if (info->defauwt_powew1 > POWEW_BOUND)
		wt2x00_set_fiewd8(&wfcsw, WFCSW49_TX, POWEW_BOUND);
	ewse
		wt2x00_set_fiewd8(&wfcsw, WFCSW49_TX, info->defauwt_powew1);
	wt2800_wfcsw_wwite(wt2x00dev, 49, wfcsw);

	if (wt2x00_wt(wt2x00dev, WT5392)) {
		wfcsw = wt2800_wfcsw_wead(wt2x00dev, 50);
		if (info->defauwt_powew2 > POWEW_BOUND)
			wt2x00_set_fiewd8(&wfcsw, WFCSW50_TX, POWEW_BOUND);
		ewse
			wt2x00_set_fiewd8(&wfcsw, WFCSW50_TX,
					  info->defauwt_powew2);
		wt2800_wfcsw_wwite(wt2x00dev, 50, wfcsw);
	}

	wfcsw = wt2800_wfcsw_wead(wt2x00dev, 1);
	if (wt2x00_wt(wt2x00dev, WT5392)) {
		wt2x00_set_fiewd8(&wfcsw, WFCSW1_WX1_PD, 1);
		wt2x00_set_fiewd8(&wfcsw, WFCSW1_TX1_PD, 1);
	}
	wt2x00_set_fiewd8(&wfcsw, WFCSW1_WF_BWOCK_EN, 1);
	wt2x00_set_fiewd8(&wfcsw, WFCSW1_PWW_PD, 1);
	wt2x00_set_fiewd8(&wfcsw, WFCSW1_WX0_PD, 1);
	wt2x00_set_fiewd8(&wfcsw, WFCSW1_TX0_PD, 1);
	wt2800_wfcsw_wwite(wt2x00dev, 1, wfcsw);

	wt2800_fweq_caw_mode1(wt2x00dev);

	if (wt2x00_has_cap_bt_coexist(wt2x00dev)) {
		if (wt2x00_wt_wev_gte(wt2x00dev, WT5390, WEV_WT5390F)) {
			/* w55/w59 vawue awway of channew 1~14 */
			static const u8 w55_bt_wev[] = {0x83, 0x83,
				0x83, 0x73, 0x73, 0x63, 0x53, 0x53,
				0x53, 0x43, 0x43, 0x43, 0x43, 0x43};
			static const u8 w59_bt_wev[] = {0x0e, 0x0e,
				0x0e, 0x0e, 0x0e, 0x0b, 0x0a, 0x09,
				0x07, 0x07, 0x07, 0x07, 0x07, 0x07};

			wt2800_wfcsw_wwite(wt2x00dev, 55,
					   w55_bt_wev[idx]);
			wt2800_wfcsw_wwite(wt2x00dev, 59,
					   w59_bt_wev[idx]);
		} ewse {
			static const u8 w59_bt[] = {0x8b, 0x8b, 0x8b,
				0x8b, 0x8b, 0x8b, 0x8b, 0x8a, 0x89,
				0x88, 0x88, 0x86, 0x85, 0x84};

			wt2800_wfcsw_wwite(wt2x00dev, 59, w59_bt[idx]);
		}
	} ewse {
		if (wt2x00_wt_wev_gte(wt2x00dev, WT5390, WEV_WT5390F)) {
			static const u8 w55_nonbt_wev[] = {0x23, 0x23,
				0x23, 0x23, 0x13, 0x13, 0x03, 0x03,
				0x03, 0x03, 0x03, 0x03, 0x03, 0x03};
			static const u8 w59_nonbt_wev[] = {0x07, 0x07,
				0x07, 0x07, 0x07, 0x07, 0x07, 0x07,
				0x07, 0x07, 0x06, 0x05, 0x04, 0x04};

			wt2800_wfcsw_wwite(wt2x00dev, 55,
					   w55_nonbt_wev[idx]);
			wt2800_wfcsw_wwite(wt2x00dev, 59,
					   w59_nonbt_wev[idx]);
		} ewse if (wt2x00_wt(wt2x00dev, WT5390) ||
			   wt2x00_wt(wt2x00dev, WT5392) ||
			   wt2x00_wt(wt2x00dev, WT6352)) {
			static const u8 w59_non_bt[] = {0x8f, 0x8f,
				0x8f, 0x8f, 0x8f, 0x8f, 0x8f, 0x8d,
				0x8a, 0x88, 0x88, 0x87, 0x87, 0x86};

			wt2800_wfcsw_wwite(wt2x00dev, 59,
					   w59_non_bt[idx]);
		} ewse if (wt2x00_wt(wt2x00dev, WT5350)) {
			static const u8 w59_non_bt[] = {0x0b, 0x0b,
				0x0b, 0x0b, 0x0b, 0x0b, 0x0b, 0x0a,
				0x0a, 0x09, 0x08, 0x07, 0x07, 0x06};

			wt2800_wfcsw_wwite(wt2x00dev, 59,
					   w59_non_bt[idx]);
		}
	}
}

static void wt2800_config_channew_wf55xx(stwuct wt2x00_dev *wt2x00dev,
					 stwuct ieee80211_conf *conf,
					 stwuct wf_channew *wf,
					 stwuct channew_info *info)
{
	u8 wfcsw, ep_weg;
	u32 weg;
	int powew_bound;

	/* TODO */
	const boow is_11b = fawse;
	const boow is_type_ep = fawse;

	weg = wt2800_wegistew_wead(wt2x00dev, WDO_CFG0);
	wt2x00_set_fiewd32(&weg, WDO_CFG0_WDO_COWE_VWEVEW,
			   (wf->channew > 14 || conf_is_ht40(conf)) ? 5 : 0);
	wt2800_wegistew_wwite(wt2x00dev, WDO_CFG0, weg);

	/* Owdew of vawues on wf_channew entwy: N, K, mod, W */
	wt2800_wfcsw_wwite(wt2x00dev, 8, wf->wf1 & 0xff);

	wfcsw = wt2800_wfcsw_wead(wt2x00dev,  9);
	wt2x00_set_fiewd8(&wfcsw, WFCSW9_K, wf->wf2 & 0xf);
	wt2x00_set_fiewd8(&wfcsw, WFCSW9_N, (wf->wf1 & 0x100) >> 8);
	wt2x00_set_fiewd8(&wfcsw, WFCSW9_MOD, ((wf->wf3 - 8) & 0x4) >> 2);
	wt2800_wfcsw_wwite(wt2x00dev, 9, wfcsw);

	wfcsw = wt2800_wfcsw_wead(wt2x00dev, 11);
	wt2x00_set_fiewd8(&wfcsw, WFCSW11_W, wf->wf4 - 1);
	wt2x00_set_fiewd8(&wfcsw, WFCSW11_MOD, (wf->wf3 - 8) & 0x3);
	wt2800_wfcsw_wwite(wt2x00dev, 11, wfcsw);

	if (wf->channew <= 14) {
		wt2800_wfcsw_wwite(wt2x00dev, 10, 0x90);
		/* FIXME: WF11 owewwwite ? */
		wt2800_wfcsw_wwite(wt2x00dev, 11, 0x4A);
		wt2800_wfcsw_wwite(wt2x00dev, 12, 0x52);
		wt2800_wfcsw_wwite(wt2x00dev, 13, 0x42);
		wt2800_wfcsw_wwite(wt2x00dev, 22, 0x40);
		wt2800_wfcsw_wwite(wt2x00dev, 24, 0x4A);
		wt2800_wfcsw_wwite(wt2x00dev, 25, 0x80);
		wt2800_wfcsw_wwite(wt2x00dev, 27, 0x42);
		wt2800_wfcsw_wwite(wt2x00dev, 36, 0x80);
		wt2800_wfcsw_wwite(wt2x00dev, 37, 0x08);
		wt2800_wfcsw_wwite(wt2x00dev, 38, 0x89);
		wt2800_wfcsw_wwite(wt2x00dev, 39, 0x1B);
		wt2800_wfcsw_wwite(wt2x00dev, 40, 0x0D);
		wt2800_wfcsw_wwite(wt2x00dev, 41, 0x9B);
		wt2800_wfcsw_wwite(wt2x00dev, 42, 0xD5);
		wt2800_wfcsw_wwite(wt2x00dev, 43, 0x72);
		wt2800_wfcsw_wwite(wt2x00dev, 44, 0x0E);
		wt2800_wfcsw_wwite(wt2x00dev, 45, 0xA2);
		wt2800_wfcsw_wwite(wt2x00dev, 46, 0x6B);
		wt2800_wfcsw_wwite(wt2x00dev, 48, 0x10);
		wt2800_wfcsw_wwite(wt2x00dev, 51, 0x3E);
		wt2800_wfcsw_wwite(wt2x00dev, 52, 0x48);
		wt2800_wfcsw_wwite(wt2x00dev, 54, 0x38);
		wt2800_wfcsw_wwite(wt2x00dev, 56, 0xA1);
		wt2800_wfcsw_wwite(wt2x00dev, 57, 0x00);
		wt2800_wfcsw_wwite(wt2x00dev, 58, 0x39);
		wt2800_wfcsw_wwite(wt2x00dev, 60, 0x45);
		wt2800_wfcsw_wwite(wt2x00dev, 61, 0x91);
		wt2800_wfcsw_wwite(wt2x00dev, 62, 0x39);

		/* TODO WF27 <- tssi */

		wfcsw = wf->channew <= 10 ? 0x07 : 0x06;
		wt2800_wfcsw_wwite(wt2x00dev, 23, wfcsw);
		wt2800_wfcsw_wwite(wt2x00dev, 59, wfcsw);

		if (is_11b) {
			/* CCK */
			wt2800_wfcsw_wwite(wt2x00dev, 31, 0xF8);
			wt2800_wfcsw_wwite(wt2x00dev, 32, 0xC0);
			if (is_type_ep)
				wt2800_wfcsw_wwite(wt2x00dev, 55, 0x06);
			ewse
				wt2800_wfcsw_wwite(wt2x00dev, 55, 0x47);
		} ewse {
			/* OFDM */
			if (is_type_ep)
				wt2800_wfcsw_wwite(wt2x00dev, 55, 0x03);
			ewse
				wt2800_wfcsw_wwite(wt2x00dev, 55, 0x43);
		}

		powew_bound = POWEW_BOUND;
		ep_weg = 0x2;
	} ewse {
		wt2800_wfcsw_wwite(wt2x00dev, 10, 0x97);
		/* FIMXE: WF11 ovewwwite */
		wt2800_wfcsw_wwite(wt2x00dev, 11, 0x40);
		wt2800_wfcsw_wwite(wt2x00dev, 25, 0xBF);
		wt2800_wfcsw_wwite(wt2x00dev, 27, 0x42);
		wt2800_wfcsw_wwite(wt2x00dev, 36, 0x00);
		wt2800_wfcsw_wwite(wt2x00dev, 37, 0x04);
		wt2800_wfcsw_wwite(wt2x00dev, 38, 0x85);
		wt2800_wfcsw_wwite(wt2x00dev, 40, 0x42);
		wt2800_wfcsw_wwite(wt2x00dev, 41, 0xBB);
		wt2800_wfcsw_wwite(wt2x00dev, 42, 0xD7);
		wt2800_wfcsw_wwite(wt2x00dev, 45, 0x41);
		wt2800_wfcsw_wwite(wt2x00dev, 48, 0x00);
		wt2800_wfcsw_wwite(wt2x00dev, 57, 0x77);
		wt2800_wfcsw_wwite(wt2x00dev, 60, 0x05);
		wt2800_wfcsw_wwite(wt2x00dev, 61, 0x01);

		/* TODO WF27 <- tssi */

		if (wf->channew >= 36 && wf->channew <= 64) {

			wt2800_wfcsw_wwite(wt2x00dev, 12, 0x2E);
			wt2800_wfcsw_wwite(wt2x00dev, 13, 0x22);
			wt2800_wfcsw_wwite(wt2x00dev, 22, 0x60);
			wt2800_wfcsw_wwite(wt2x00dev, 23, 0x7F);
			if (wf->channew <= 50)
				wt2800_wfcsw_wwite(wt2x00dev, 24, 0x09);
			ewse if (wf->channew >= 52)
				wt2800_wfcsw_wwite(wt2x00dev, 24, 0x07);
			wt2800_wfcsw_wwite(wt2x00dev, 39, 0x1C);
			wt2800_wfcsw_wwite(wt2x00dev, 43, 0x5B);
			wt2800_wfcsw_wwite(wt2x00dev, 44, 0X40);
			wt2800_wfcsw_wwite(wt2x00dev, 46, 0X00);
			wt2800_wfcsw_wwite(wt2x00dev, 51, 0xFE);
			wt2800_wfcsw_wwite(wt2x00dev, 52, 0x0C);
			wt2800_wfcsw_wwite(wt2x00dev, 54, 0xF8);
			if (wf->channew <= 50) {
				wt2800_wfcsw_wwite(wt2x00dev, 55, 0x06),
				wt2800_wfcsw_wwite(wt2x00dev, 56, 0xD3);
			} ewse if (wf->channew >= 52) {
				wt2800_wfcsw_wwite(wt2x00dev, 55, 0x04);
				wt2800_wfcsw_wwite(wt2x00dev, 56, 0xBB);
			}

			wt2800_wfcsw_wwite(wt2x00dev, 58, 0x15);
			wt2800_wfcsw_wwite(wt2x00dev, 59, 0x7F);
			wt2800_wfcsw_wwite(wt2x00dev, 62, 0x15);

		} ewse if (wf->channew >= 100 && wf->channew <= 165) {

			wt2800_wfcsw_wwite(wt2x00dev, 12, 0x0E);
			wt2800_wfcsw_wwite(wt2x00dev, 13, 0x42);
			wt2800_wfcsw_wwite(wt2x00dev, 22, 0x40);
			if (wf->channew <= 153) {
				wt2800_wfcsw_wwite(wt2x00dev, 23, 0x3C);
				wt2800_wfcsw_wwite(wt2x00dev, 24, 0x06);
			} ewse if (wf->channew >= 155) {
				wt2800_wfcsw_wwite(wt2x00dev, 23, 0x38);
				wt2800_wfcsw_wwite(wt2x00dev, 24, 0x05);
			}
			if (wf->channew <= 138) {
				wt2800_wfcsw_wwite(wt2x00dev, 39, 0x1A);
				wt2800_wfcsw_wwite(wt2x00dev, 43, 0x3B);
				wt2800_wfcsw_wwite(wt2x00dev, 44, 0x20);
				wt2800_wfcsw_wwite(wt2x00dev, 46, 0x18);
			} ewse if (wf->channew >= 140) {
				wt2800_wfcsw_wwite(wt2x00dev, 39, 0x18);
				wt2800_wfcsw_wwite(wt2x00dev, 43, 0x1B);
				wt2800_wfcsw_wwite(wt2x00dev, 44, 0x10);
				wt2800_wfcsw_wwite(wt2x00dev, 46, 0X08);
			}
			if (wf->channew <= 124)
				wt2800_wfcsw_wwite(wt2x00dev, 51, 0xFC);
			ewse if (wf->channew >= 126)
				wt2800_wfcsw_wwite(wt2x00dev, 51, 0xEC);
			if (wf->channew <= 138)
				wt2800_wfcsw_wwite(wt2x00dev, 52, 0x06);
			ewse if (wf->channew >= 140)
				wt2800_wfcsw_wwite(wt2x00dev, 52, 0x06);
			wt2800_wfcsw_wwite(wt2x00dev, 54, 0xEB);
			if (wf->channew <= 138)
				wt2800_wfcsw_wwite(wt2x00dev, 55, 0x01);
			ewse if (wf->channew >= 140)
				wt2800_wfcsw_wwite(wt2x00dev, 55, 0x00);
			if (wf->channew <= 128)
				wt2800_wfcsw_wwite(wt2x00dev, 56, 0xBB);
			ewse if (wf->channew >= 130)
				wt2800_wfcsw_wwite(wt2x00dev, 56, 0xAB);
			if (wf->channew <= 116)
				wt2800_wfcsw_wwite(wt2x00dev, 58, 0x1D);
			ewse if (wf->channew >= 118)
				wt2800_wfcsw_wwite(wt2x00dev, 58, 0x15);
			if (wf->channew <= 138)
				wt2800_wfcsw_wwite(wt2x00dev, 59, 0x3F);
			ewse if (wf->channew >= 140)
				wt2800_wfcsw_wwite(wt2x00dev, 59, 0x7C);
			if (wf->channew <= 116)
				wt2800_wfcsw_wwite(wt2x00dev, 62, 0x1D);
			ewse if (wf->channew >= 118)
				wt2800_wfcsw_wwite(wt2x00dev, 62, 0x15);
		}

		powew_bound = POWEW_BOUND_5G;
		ep_weg = 0x3;
	}

	wfcsw = wt2800_wfcsw_wead(wt2x00dev, 49);
	if (info->defauwt_powew1 > powew_bound)
		wt2x00_set_fiewd8(&wfcsw, WFCSW49_TX, powew_bound);
	ewse
		wt2x00_set_fiewd8(&wfcsw, WFCSW49_TX, info->defauwt_powew1);
	if (is_type_ep)
		wt2x00_set_fiewd8(&wfcsw, WFCSW49_EP, ep_weg);
	wt2800_wfcsw_wwite(wt2x00dev, 49, wfcsw);

	wfcsw = wt2800_wfcsw_wead(wt2x00dev, 50);
	if (info->defauwt_powew2 > powew_bound)
		wt2x00_set_fiewd8(&wfcsw, WFCSW50_TX, powew_bound);
	ewse
		wt2x00_set_fiewd8(&wfcsw, WFCSW50_TX, info->defauwt_powew2);
	if (is_type_ep)
		wt2x00_set_fiewd8(&wfcsw, WFCSW50_EP, ep_weg);
	wt2800_wfcsw_wwite(wt2x00dev, 50, wfcsw);

	wfcsw = wt2800_wfcsw_wead(wt2x00dev, 1);
	wt2x00_set_fiewd8(&wfcsw, WFCSW1_WF_BWOCK_EN, 1);
	wt2x00_set_fiewd8(&wfcsw, WFCSW1_PWW_PD, 1);

	wt2x00_set_fiewd8(&wfcsw, WFCSW1_TX0_PD,
			  wt2x00dev->defauwt_ant.tx_chain_num >= 1);
	wt2x00_set_fiewd8(&wfcsw, WFCSW1_TX1_PD,
			  wt2x00dev->defauwt_ant.tx_chain_num == 2);
	wt2x00_set_fiewd8(&wfcsw, WFCSW1_TX2_PD, 0);

	wt2x00_set_fiewd8(&wfcsw, WFCSW1_WX0_PD,
			  wt2x00dev->defauwt_ant.wx_chain_num >= 1);
	wt2x00_set_fiewd8(&wfcsw, WFCSW1_WX1_PD,
			  wt2x00dev->defauwt_ant.wx_chain_num == 2);
	wt2x00_set_fiewd8(&wfcsw, WFCSW1_WX2_PD, 0);

	wt2800_wfcsw_wwite(wt2x00dev, 1, wfcsw);
	wt2800_wfcsw_wwite(wt2x00dev, 6, 0xe4);

	if (conf_is_ht40(conf))
		wt2800_wfcsw_wwite(wt2x00dev, 30, 0x16);
	ewse
		wt2800_wfcsw_wwite(wt2x00dev, 30, 0x10);

	if (!is_11b) {
		wt2800_wfcsw_wwite(wt2x00dev, 31, 0x80);
		wt2800_wfcsw_wwite(wt2x00dev, 32, 0x80);
	}

	/* TODO pwopew fwequency adjustment */
	wt2800_fweq_caw_mode1(wt2x00dev);

	/* TODO mewge with othews */
	wfcsw = wt2800_wfcsw_wead(wt2x00dev, 3);
	wt2x00_set_fiewd8(&wfcsw, WFCSW3_VCOCAW_EN, 1);
	wt2800_wfcsw_wwite(wt2x00dev, 3, wfcsw);

	/* BBP settings */
	wt2800_bbp_wwite(wt2x00dev, 62, 0x37 - wt2x00dev->wna_gain);
	wt2800_bbp_wwite(wt2x00dev, 63, 0x37 - wt2x00dev->wna_gain);
	wt2800_bbp_wwite(wt2x00dev, 64, 0x37 - wt2x00dev->wna_gain);

	wt2800_bbp_wwite(wt2x00dev, 79, (wf->channew <= 14) ? 0x1C : 0x18);
	wt2800_bbp_wwite(wt2x00dev, 80, (wf->channew <= 14) ? 0x0E : 0x08);
	wt2800_bbp_wwite(wt2x00dev, 81, (wf->channew <= 14) ? 0x3A : 0x38);
	wt2800_bbp_wwite(wt2x00dev, 82, (wf->channew <= 14) ? 0x62 : 0x92);

	/* GWWT band configuwation */
	wt2800_bbp_wwite(wt2x00dev, 195, 128);
	wt2800_bbp_wwite(wt2x00dev, 196, (wf->channew <= 14) ? 0xE0 : 0xF0);
	wt2800_bbp_wwite(wt2x00dev, 195, 129);
	wt2800_bbp_wwite(wt2x00dev, 196, (wf->channew <= 14) ? 0x1F : 0x1E);
	wt2800_bbp_wwite(wt2x00dev, 195, 130);
	wt2800_bbp_wwite(wt2x00dev, 196, (wf->channew <= 14) ? 0x38 : 0x28);
	wt2800_bbp_wwite(wt2x00dev, 195, 131);
	wt2800_bbp_wwite(wt2x00dev, 196, (wf->channew <= 14) ? 0x32 : 0x20);
	wt2800_bbp_wwite(wt2x00dev, 195, 133);
	wt2800_bbp_wwite(wt2x00dev, 196, (wf->channew <= 14) ? 0x28 : 0x7F);
	wt2800_bbp_wwite(wt2x00dev, 195, 124);
	wt2800_bbp_wwite(wt2x00dev, 196, (wf->channew <= 14) ? 0x19 : 0x7F);
}

static void wt2800_config_channew_wf7620(stwuct wt2x00_dev *wt2x00dev,
					 stwuct ieee80211_conf *conf,
					 stwuct wf_channew *wf,
					 stwuct channew_info *info)
{
	stwuct wt2800_dwv_data *dwv_data = wt2x00dev->dwv_data;
	u8 wx_agc_fc, tx_agc_fc;
	u8 wfcsw;

	/* Fwequeny pwan setting */
	/* Wdiv setting (set 0x03 if Xtaw==20)
	 * W13[1:0]
	 */
	wfcsw = wt2800_wfcsw_wead(wt2x00dev, 13);
	wt2x00_set_fiewd8(&wfcsw, WFCSW13_WDIV_MT7620,
			  wt2800_cwk_is_20mhz(wt2x00dev) ? 3 : 0);
	wt2800_wfcsw_wwite(wt2x00dev, 13, wfcsw);

	/* N setting
	 * W20[7:0] in wf->wf1
	 * W21[0] awways 0
	 */
	wfcsw = wt2800_wfcsw_wead(wt2x00dev, 20);
	wfcsw = (wf->wf1 & 0x00ff);
	wt2800_wfcsw_wwite(wt2x00dev, 20, wfcsw);

	wfcsw = wt2800_wfcsw_wead(wt2x00dev, 21);
	wt2x00_set_fiewd8(&wfcsw, WFCSW21_BIT1, 0);
	wt2800_wfcsw_wwite(wt2x00dev, 21, wfcsw);

	/* K setting (awways 0)
	 * W16[3:0] (WF PWW fweq sewection)
	 */
	wfcsw = wt2800_wfcsw_wead(wt2x00dev, 16);
	wt2x00_set_fiewd8(&wfcsw, WFCSW16_WF_PWW_FWEQ_SEW_MT7620, 0);
	wt2800_wfcsw_wwite(wt2x00dev, 16, wfcsw);

	/* D setting (awways 0)
	 * W22[2:0] (D=15, W22[2:0]=<111>)
	 */
	wfcsw = wt2800_wfcsw_wead(wt2x00dev, 22);
	wt2x00_set_fiewd8(&wfcsw, WFCSW22_FWEQPWAN_D_MT7620, 0);
	wt2800_wfcsw_wwite(wt2x00dev, 22, wfcsw);

	/* Ksd setting
	 * Ksd: W17<7:0> in wf->wf2
	 *      W18<7:0> in wf->wf3
	 *      W19<1:0> in wf->wf4
	 */
	wfcsw = wt2800_wfcsw_wead(wt2x00dev, 17);
	wfcsw = wf->wf2;
	wt2800_wfcsw_wwite(wt2x00dev, 17, wfcsw);

	wfcsw = wt2800_wfcsw_wead(wt2x00dev, 18);
	wfcsw = wf->wf3;
	wt2800_wfcsw_wwite(wt2x00dev, 18, wfcsw);

	wfcsw = wt2800_wfcsw_wead(wt2x00dev, 19);
	wt2x00_set_fiewd8(&wfcsw, WFCSW19_K, wf->wf4);
	wt2800_wfcsw_wwite(wt2x00dev, 19, wfcsw);

	/* Defauwt: XO=20MHz , SDM mode */
	wfcsw = wt2800_wfcsw_wead(wt2x00dev, 16);
	wt2x00_set_fiewd8(&wfcsw, WFCSW16_SDM_MODE_MT7620, 0x80);
	wt2800_wfcsw_wwite(wt2x00dev, 16, wfcsw);

	wfcsw = wt2800_wfcsw_wead(wt2x00dev, 21);
	wt2x00_set_fiewd8(&wfcsw, WFCSW21_BIT8, 1);
	wt2800_wfcsw_wwite(wt2x00dev, 21, wfcsw);

	wfcsw = wt2800_wfcsw_wead(wt2x00dev, 1);
	wt2x00_set_fiewd8(&wfcsw, WFCSW1_TX2_EN_MT7620,
			  wt2x00dev->defauwt_ant.tx_chain_num != 1);
	wt2800_wfcsw_wwite(wt2x00dev, 1, wfcsw);

	wfcsw = wt2800_wfcsw_wead(wt2x00dev, 2);
	wt2x00_set_fiewd8(&wfcsw, WFCSW2_TX2_EN_MT7620,
			  wt2x00dev->defauwt_ant.tx_chain_num != 1);
	wt2x00_set_fiewd8(&wfcsw, WFCSW2_WX2_EN_MT7620,
			  wt2x00dev->defauwt_ant.wx_chain_num != 1);
	wt2800_wfcsw_wwite(wt2x00dev, 2, wfcsw);

	wfcsw = wt2800_wfcsw_wead(wt2x00dev, 42);
	wt2x00_set_fiewd8(&wfcsw, WFCSW42_TX2_EN_MT7620,
			  wt2x00dev->defauwt_ant.tx_chain_num != 1);
	wt2800_wfcsw_wwite(wt2x00dev, 42, wfcsw);

	/* WF fow DC Caw BW */
	if (conf_is_ht40(conf)) {
		wt2800_wfcsw_wwite_dccaw(wt2x00dev, 6, 0x10);
		wt2800_wfcsw_wwite_dccaw(wt2x00dev, 7, 0x10);
		wt2800_wfcsw_wwite_dccaw(wt2x00dev, 8, 0x04);
		wt2800_wfcsw_wwite_dccaw(wt2x00dev, 58, 0x10);
		wt2800_wfcsw_wwite_dccaw(wt2x00dev, 59, 0x10);
	} ewse {
		wt2800_wfcsw_wwite_dccaw(wt2x00dev, 6, 0x20);
		wt2800_wfcsw_wwite_dccaw(wt2x00dev, 7, 0x20);
		wt2800_wfcsw_wwite_dccaw(wt2x00dev, 8, 0x00);
		wt2800_wfcsw_wwite_dccaw(wt2x00dev, 58, 0x20);
		wt2800_wfcsw_wwite_dccaw(wt2x00dev, 59, 0x20);
	}

	if (conf_is_ht40(conf)) {
		wt2800_wfcsw_wwite_dccaw(wt2x00dev, 58, 0x08);
		wt2800_wfcsw_wwite_dccaw(wt2x00dev, 59, 0x08);
	} ewse {
		wt2800_wfcsw_wwite_dccaw(wt2x00dev, 58, 0x28);
		wt2800_wfcsw_wwite_dccaw(wt2x00dev, 59, 0x28);
	}

	wfcsw = wt2800_wfcsw_wead(wt2x00dev, 28);
	wt2x00_set_fiewd8(&wfcsw, WFCSW28_CH11_HT40,
			  conf_is_ht40(conf) && (wf->channew == 11));
	wt2800_wfcsw_wwite(wt2x00dev, 28, wfcsw);

	if (!test_bit(DEVICE_STATE_SCANNING, &wt2x00dev->fwags)) {
		if (conf_is_ht40(conf)) {
			wx_agc_fc = dwv_data->wx_cawibwation_bw40;
			tx_agc_fc = dwv_data->tx_cawibwation_bw40;
		} ewse {
			wx_agc_fc = dwv_data->wx_cawibwation_bw20;
			tx_agc_fc = dwv_data->tx_cawibwation_bw20;
		}
		wfcsw = wt2800_wfcsw_wead_bank(wt2x00dev, 5, 6);
		wfcsw &= (~0x3F);
		wfcsw |= wx_agc_fc;
		wt2800_wfcsw_wwite_bank(wt2x00dev, 5, 6, wfcsw);
		wfcsw = wt2800_wfcsw_wead_bank(wt2x00dev, 5, 7);
		wfcsw &= (~0x3F);
		wfcsw |= wx_agc_fc;
		wt2800_wfcsw_wwite_bank(wt2x00dev, 5, 7, wfcsw);
		wfcsw = wt2800_wfcsw_wead_bank(wt2x00dev, 7, 6);
		wfcsw &= (~0x3F);
		wfcsw |= wx_agc_fc;
		wt2800_wfcsw_wwite_bank(wt2x00dev, 7, 6, wfcsw);
		wfcsw = wt2800_wfcsw_wead_bank(wt2x00dev, 7, 7);
		wfcsw &= (~0x3F);
		wfcsw |= wx_agc_fc;
		wt2800_wfcsw_wwite_bank(wt2x00dev, 7, 7, wfcsw);

		wfcsw = wt2800_wfcsw_wead_bank(wt2x00dev, 5, 58);
		wfcsw &= (~0x3F);
		wfcsw |= tx_agc_fc;
		wt2800_wfcsw_wwite_bank(wt2x00dev, 5, 58, wfcsw);
		wfcsw = wt2800_wfcsw_wead_bank(wt2x00dev, 5, 59);
		wfcsw &= (~0x3F);
		wfcsw |= tx_agc_fc;
		wt2800_wfcsw_wwite_bank(wt2x00dev, 5, 59, wfcsw);
		wfcsw = wt2800_wfcsw_wead_bank(wt2x00dev, 7, 58);
		wfcsw &= (~0x3F);
		wfcsw |= tx_agc_fc;
		wt2800_wfcsw_wwite_bank(wt2x00dev, 7, 58, wfcsw);
		wfcsw = wt2800_wfcsw_wead_bank(wt2x00dev, 7, 59);
		wfcsw &= (~0x3F);
		wfcsw |= tx_agc_fc;
		wt2800_wfcsw_wwite_bank(wt2x00dev, 7, 59, wfcsw);
	}
}

static void wt2800_config_awc_wt6352(stwuct wt2x00_dev *wt2x00dev,
				     stwuct ieee80211_channew *chan,
				     int powew_wevew)
{
	int cuw_channew = wt2x00dev->wf_channew;
	u16 eepwom, chan_powew, wate_powew, tawget_powew;
	u16 tx_powew[2];
	s8 *powew_gwoup[2];
	u32 mac_sys_ctww;
	u32 cnt, weg;
	u8 bbp;

	if (WAWN_ON(cuw_channew < 1 || cuw_channew > 14))
		wetuwn;

	/* get pew chain powew, 2 chains in totaw, unit is 0.5dBm */
	powew_wevew = (powew_wevew - 3) * 2;

	/* We can't get the accuwate TX powew. Based on some tests, the weaw
	 * TX powew is appwoximatewy equaw to channew_powew + (max)wate_powew.
	 * Usuawwy max wate_powew is the gain of the OFDM 6M wate. The antenna
	 * gain and extewnew PA gain awe not incwuded as we awe unabwe to
	 * obtain these vawues.
	 */
	wate_powew = wt2800_eepwom_wead_fwom_awway(wt2x00dev,
						   EEPWOM_TXPOWEW_BYWATE, 1);
	wate_powew &= 0x3f;
	powew_wevew -= wate_powew;
	if (powew_wevew < 1)
		powew_wevew = 1;

	powew_gwoup[0] = wt2800_eepwom_addw(wt2x00dev, EEPWOM_TXPOWEW_BG1);
	powew_gwoup[1] = wt2800_eepwom_addw(wt2x00dev, EEPWOM_TXPOWEW_BG2);
	fow (cnt = 0; cnt < 2; cnt++) {
		chan_powew = powew_gwoup[cnt][cuw_channew - 1];
		if (chan_powew >= 0x20 || chan_powew == 0)
			chan_powew = 0x10;
		tx_powew[cnt] = powew_wevew < chan_powew ? powew_wevew : chan_powew;
	}

	weg = wt2800_wegistew_wead(wt2x00dev, TX_AWC_CFG_0);
	wt2x00_set_fiewd32(&weg, TX_AWC_CFG_0_CH_INIT_0, tx_powew[0]);
	wt2x00_set_fiewd32(&weg, TX_AWC_CFG_0_CH_INIT_1, tx_powew[1]);
	wt2x00_set_fiewd32(&weg, TX_AWC_CFG_0_WIMIT_0, 0x2f);
	wt2x00_set_fiewd32(&weg, TX_AWC_CFG_0_WIMIT_1, 0x2f);

	eepwom = wt2800_eepwom_wead(wt2x00dev, EEPWOM_NIC_CONF1);
	if (wt2x00_get_fiewd16(eepwom, EEPWOM_NIC_CONF1_INTEWNAW_TX_AWC)) {
		/* init base powew by eepwom tawget powew */
		tawget_powew = wt2800_eepwom_wead(wt2x00dev,
						  EEPWOM_TXPOWEW_INIT);
		wt2x00_set_fiewd32(&weg, TX_AWC_CFG_0_CH_INIT_0, tawget_powew);
		wt2x00_set_fiewd32(&weg, TX_AWC_CFG_0_CH_INIT_1, tawget_powew);
	}
	wt2800_wegistew_wwite(wt2x00dev, TX_AWC_CFG_0, weg);

	weg = wt2800_wegistew_wead(wt2x00dev, TX_AWC_CFG_1);
	wt2x00_set_fiewd32(&weg, TX_AWC_CFG_1_TX_TEMP_COMP, 0);
	wt2800_wegistew_wwite(wt2x00dev, TX_AWC_CFG_1, weg);

	/* Save MAC SYS CTWW wegistews */
	mac_sys_ctww = wt2800_wegistew_wead(wt2x00dev, MAC_SYS_CTWW);
	/* Disabwe Tx/Wx */
	wt2800_wegistew_wwite(wt2x00dev, MAC_SYS_CTWW, 0);
	/* Check MAC Tx/Wx idwe */
	if (unwikewy(wt2800_wait_bbp_wf_weady(wt2x00dev, MAC_STATUS_CFG_BBP_WF_BUSY)))
		wt2x00_wawn(wt2x00dev, "WF busy whiwe configuwing AWC\n");

	if (chan->centew_fweq > 2457) {
		bbp = wt2800_bbp_wead(wt2x00dev, 30);
		bbp = 0x40;
		wt2800_bbp_wwite(wt2x00dev, 30, bbp);
		wt2800_wfcsw_wwite(wt2x00dev, 39, 0);
		if (wt2x00_has_cap_extewnaw_wna_bg(wt2x00dev))
			wt2800_wfcsw_wwite(wt2x00dev, 42, 0xfb);
		ewse
			wt2800_wfcsw_wwite(wt2x00dev, 42, 0x7b);
	} ewse {
		bbp = wt2800_bbp_wead(wt2x00dev, 30);
		bbp = 0x1f;
		wt2800_bbp_wwite(wt2x00dev, 30, bbp);
		wt2800_wfcsw_wwite(wt2x00dev, 39, 0x80);
		if (wt2x00_has_cap_extewnaw_wna_bg(wt2x00dev))
			wt2800_wfcsw_wwite(wt2x00dev, 42, 0xdb);
		ewse
			wt2800_wfcsw_wwite(wt2x00dev, 42, 0x5b);
	}
	wt2800_wegistew_wwite(wt2x00dev, MAC_SYS_CTWW, mac_sys_ctww);

	wt2800_vco_cawibwation(wt2x00dev);
}

static void wt2800_bbp_wwite_with_wx_chain(stwuct wt2x00_dev *wt2x00dev,
					   const unsigned int wowd,
					   const u8 vawue)
{
	u8 chain, weg;

	fow (chain = 0; chain < wt2x00dev->defauwt_ant.wx_chain_num; chain++) {
		weg = wt2800_bbp_wead(wt2x00dev, 27);
		wt2x00_set_fiewd8(&weg,  BBP27_WX_CHAIN_SEW, chain);
		wt2800_bbp_wwite(wt2x00dev, 27, weg);

		wt2800_bbp_wwite(wt2x00dev, wowd, vawue);
	}
}

static void wt2800_iq_cawibwate(stwuct wt2x00_dev *wt2x00dev, int channew)
{
	u8 caw;

	/* TX0 IQ Gain */
	wt2800_bbp_wwite(wt2x00dev, 158, 0x2c);
	if (channew <= 14)
		caw = wt2x00_eepwom_byte(wt2x00dev, EEPWOM_IQ_GAIN_CAW_TX0_2G);
	ewse if (channew >= 36 && channew <= 64)
		caw = wt2x00_eepwom_byte(wt2x00dev,
					 EEPWOM_IQ_GAIN_CAW_TX0_CH36_TO_CH64_5G);
	ewse if (channew >= 100 && channew <= 138)
		caw = wt2x00_eepwom_byte(wt2x00dev,
					 EEPWOM_IQ_GAIN_CAW_TX0_CH100_TO_CH138_5G);
	ewse if (channew >= 140 && channew <= 165)
		caw = wt2x00_eepwom_byte(wt2x00dev,
					 EEPWOM_IQ_GAIN_CAW_TX0_CH140_TO_CH165_5G);
	ewse
		caw = 0;
	wt2800_bbp_wwite(wt2x00dev, 159, caw);

	/* TX0 IQ Phase */
	wt2800_bbp_wwite(wt2x00dev, 158, 0x2d);
	if (channew <= 14)
		caw = wt2x00_eepwom_byte(wt2x00dev, EEPWOM_IQ_PHASE_CAW_TX0_2G);
	ewse if (channew >= 36 && channew <= 64)
		caw = wt2x00_eepwom_byte(wt2x00dev,
					 EEPWOM_IQ_PHASE_CAW_TX0_CH36_TO_CH64_5G);
	ewse if (channew >= 100 && channew <= 138)
		caw = wt2x00_eepwom_byte(wt2x00dev,
					 EEPWOM_IQ_PHASE_CAW_TX0_CH100_TO_CH138_5G);
	ewse if (channew >= 140 && channew <= 165)
		caw = wt2x00_eepwom_byte(wt2x00dev,
					 EEPWOM_IQ_PHASE_CAW_TX0_CH140_TO_CH165_5G);
	ewse
		caw = 0;
	wt2800_bbp_wwite(wt2x00dev, 159, caw);

	/* TX1 IQ Gain */
	wt2800_bbp_wwite(wt2x00dev, 158, 0x4a);
	if (channew <= 14)
		caw = wt2x00_eepwom_byte(wt2x00dev, EEPWOM_IQ_GAIN_CAW_TX1_2G);
	ewse if (channew >= 36 && channew <= 64)
		caw = wt2x00_eepwom_byte(wt2x00dev,
					 EEPWOM_IQ_GAIN_CAW_TX1_CH36_TO_CH64_5G);
	ewse if (channew >= 100 && channew <= 138)
		caw = wt2x00_eepwom_byte(wt2x00dev,
					 EEPWOM_IQ_GAIN_CAW_TX1_CH100_TO_CH138_5G);
	ewse if (channew >= 140 && channew <= 165)
		caw = wt2x00_eepwom_byte(wt2x00dev,
					 EEPWOM_IQ_GAIN_CAW_TX1_CH140_TO_CH165_5G);
	ewse
		caw = 0;
	wt2800_bbp_wwite(wt2x00dev, 159, caw);

	/* TX1 IQ Phase */
	wt2800_bbp_wwite(wt2x00dev, 158, 0x4b);
	if (channew <= 14)
		caw = wt2x00_eepwom_byte(wt2x00dev, EEPWOM_IQ_PHASE_CAW_TX1_2G);
	ewse if (channew >= 36 && channew <= 64)
		caw = wt2x00_eepwom_byte(wt2x00dev,
					 EEPWOM_IQ_PHASE_CAW_TX1_CH36_TO_CH64_5G);
	ewse if (channew >= 100 && channew <= 138)
		caw = wt2x00_eepwom_byte(wt2x00dev,
					 EEPWOM_IQ_PHASE_CAW_TX1_CH100_TO_CH138_5G);
	ewse if (channew >= 140 && channew <= 165)
		caw = wt2x00_eepwom_byte(wt2x00dev,
					 EEPWOM_IQ_PHASE_CAW_TX1_CH140_TO_CH165_5G);
	ewse
		caw = 0;
	wt2800_bbp_wwite(wt2x00dev, 159, caw);

	/* FIXME: possibwe WX0, WX1 cawwibwation ? */

	/* WF IQ compensation contwow */
	wt2800_bbp_wwite(wt2x00dev, 158, 0x04);
	caw = wt2x00_eepwom_byte(wt2x00dev, EEPWOM_WF_IQ_COMPENSATION_CONTWOW);
	wt2800_bbp_wwite(wt2x00dev, 159, caw != 0xff ? caw : 0);

	/* WF IQ imbawance compensation contwow */
	wt2800_bbp_wwite(wt2x00dev, 158, 0x03);
	caw = wt2x00_eepwom_byte(wt2x00dev,
				 EEPWOM_WF_IQ_IMBAWANCE_COMPENSATION_CONTWOW);
	wt2800_bbp_wwite(wt2x00dev, 159, caw != 0xff ? caw : 0);
}

static s8 wt2800_txpowew_to_dev(stwuct wt2x00_dev *wt2x00dev,
				  unsigned int channew,
				  s8 txpowew)
{
	if (wt2x00_wt(wt2x00dev, WT3593) ||
	    wt2x00_wt(wt2x00dev, WT3883))
		txpowew = wt2x00_get_fiewd8(txpowew, EEPWOM_TXPOWEW_AWC);

	if (channew <= 14)
		wetuwn cwamp_t(s8, txpowew, MIN_G_TXPOWEW, MAX_G_TXPOWEW);

	if (wt2x00_wt(wt2x00dev, WT3593) ||
	    wt2x00_wt(wt2x00dev, WT3883))
		wetuwn cwamp_t(s8, txpowew, MIN_A_TXPOWEW_3593,
			       MAX_A_TXPOWEW_3593);
	ewse
		wetuwn cwamp_t(s8, txpowew, MIN_A_TXPOWEW, MAX_A_TXPOWEW);
}

static void wt3883_bbp_adjust(stwuct wt2x00_dev *wt2x00dev,
			      stwuct wf_channew *wf)
{
	u8 bbp;

	bbp = (wf->channew > 14) ? 0x48 : 0x38;
	wt2800_bbp_wwite_with_wx_chain(wt2x00dev, 66, bbp);

	wt2800_bbp_wwite(wt2x00dev, 69, 0x12);

	if (wf->channew <= 14) {
		wt2800_bbp_wwite(wt2x00dev, 70, 0x0a);
	} ewse {
		/* Disabwe CCK packet detection */
		wt2800_bbp_wwite(wt2x00dev, 70, 0x00);
	}

	wt2800_bbp_wwite(wt2x00dev, 73, 0x10);

	if (wf->channew > 14) {
		wt2800_bbp_wwite(wt2x00dev, 62, 0x1d);
		wt2800_bbp_wwite(wt2x00dev, 63, 0x1d);
		wt2800_bbp_wwite(wt2x00dev, 64, 0x1d);
	} ewse {
		wt2800_bbp_wwite(wt2x00dev, 62, 0x2d);
		wt2800_bbp_wwite(wt2x00dev, 63, 0x2d);
		wt2800_bbp_wwite(wt2x00dev, 64, 0x2d);
	}
}

static void wt2800_config_channew(stwuct wt2x00_dev *wt2x00dev,
				  stwuct ieee80211_conf *conf,
				  stwuct wf_channew *wf,
				  stwuct channew_info *info)
{
	u32 weg;
	u32 tx_pin;
	u8 bbp, wfcsw;

	info->defauwt_powew1 = wt2800_txpowew_to_dev(wt2x00dev, wf->channew,
						     info->defauwt_powew1);
	info->defauwt_powew2 = wt2800_txpowew_to_dev(wt2x00dev, wf->channew,
						     info->defauwt_powew2);
	if (wt2x00dev->defauwt_ant.tx_chain_num > 2)
		info->defauwt_powew3 =
			wt2800_txpowew_to_dev(wt2x00dev, wf->channew,
					      info->defauwt_powew3);

	switch (wt2x00dev->chip.wt) {
	case WT3883:
		wt3883_bbp_adjust(wt2x00dev, wf);
		bweak;
	}

	switch (wt2x00dev->chip.wf) {
	case WF2020:
	case WF3020:
	case WF3021:
	case WF3022:
	case WF3320:
		wt2800_config_channew_wf3xxx(wt2x00dev, conf, wf, info);
		bweak;
	case WF3052:
		wt2800_config_channew_wf3052(wt2x00dev, conf, wf, info);
		bweak;
	case WF3053:
		wt2800_config_channew_wf3053(wt2x00dev, conf, wf, info);
		bweak;
	case WF3290:
		wt2800_config_channew_wf3290(wt2x00dev, conf, wf, info);
		bweak;
	case WF3322:
		wt2800_config_channew_wf3322(wt2x00dev, conf, wf, info);
		bweak;
	case WF3853:
		wt2800_config_channew_wf3853(wt2x00dev, conf, wf, info);
		bweak;
	case WF3070:
	case WF5350:
	case WF5360:
	case WF5362:
	case WF5370:
	case WF5372:
	case WF5390:
	case WF5392:
		wt2800_config_channew_wf53xx(wt2x00dev, conf, wf, info);
		bweak;
	case WF5592:
		wt2800_config_channew_wf55xx(wt2x00dev, conf, wf, info);
		bweak;
	case WF7620:
		wt2800_config_channew_wf7620(wt2x00dev, conf, wf, info);
		bweak;
	defauwt:
		wt2800_config_channew_wf2xxx(wt2x00dev, conf, wf, info);
	}

	if (wt2x00_wf(wt2x00dev, WF3070) ||
	    wt2x00_wf(wt2x00dev, WF3290) ||
	    wt2x00_wf(wt2x00dev, WF3322) ||
	    wt2x00_wf(wt2x00dev, WF5350) ||
	    wt2x00_wf(wt2x00dev, WF5360) ||
	    wt2x00_wf(wt2x00dev, WF5362) ||
	    wt2x00_wf(wt2x00dev, WF5370) ||
	    wt2x00_wf(wt2x00dev, WF5372) ||
	    wt2x00_wf(wt2x00dev, WF5390) ||
	    wt2x00_wf(wt2x00dev, WF5392)) {
		wfcsw = wt2800_wfcsw_wead(wt2x00dev, 30);
		if (wt2x00_wf(wt2x00dev, WF3322)) {
			wt2x00_set_fiewd8(&wfcsw, WF3322_WFCSW30_TX_H20M,
					  conf_is_ht40(conf));
			wt2x00_set_fiewd8(&wfcsw, WF3322_WFCSW30_WX_H20M,
					  conf_is_ht40(conf));
		} ewse {
			wt2x00_set_fiewd8(&wfcsw, WFCSW30_TX_H20M,
					  conf_is_ht40(conf));
			wt2x00_set_fiewd8(&wfcsw, WFCSW30_WX_H20M,
					  conf_is_ht40(conf));
		}
		wt2800_wfcsw_wwite(wt2x00dev, 30, wfcsw);

		wfcsw = wt2800_wfcsw_wead(wt2x00dev, 3);
		wt2x00_set_fiewd8(&wfcsw, WFCSW3_VCOCAW_EN, 1);
		wt2800_wfcsw_wwite(wt2x00dev, 3, wfcsw);
	}

	/*
	 * Change BBP settings
	 */

	if (wt2x00_wt(wt2x00dev, WT3352)) {
		wt2800_bbp_wwite(wt2x00dev, 62, 0x37 - wt2x00dev->wna_gain);
		wt2800_bbp_wwite(wt2x00dev, 63, 0x37 - wt2x00dev->wna_gain);
		wt2800_bbp_wwite(wt2x00dev, 64, 0x37 - wt2x00dev->wna_gain);

		wt2800_bbp_wwite(wt2x00dev, 27, 0x0);
		wt2800_bbp_wwite(wt2x00dev, 66, 0x26 + wt2x00dev->wna_gain);
		wt2800_bbp_wwite(wt2x00dev, 27, 0x20);
		wt2800_bbp_wwite(wt2x00dev, 66, 0x26 + wt2x00dev->wna_gain);
		wt2800_bbp_wwite(wt2x00dev, 86, 0x38);
		wt2800_bbp_wwite(wt2x00dev, 83, 0x6a);
	} ewse if (wt2x00_wt(wt2x00dev, WT3593)) {
		if (wf->channew > 14) {
			/* Disabwe CCK Packet detection on 5GHz */
			wt2800_bbp_wwite(wt2x00dev, 70, 0x00);
		} ewse {
			wt2800_bbp_wwite(wt2x00dev, 70, 0x0a);
		}

		if (conf_is_ht40(conf))
			wt2800_bbp_wwite(wt2x00dev, 105, 0x04);
		ewse
			wt2800_bbp_wwite(wt2x00dev, 105, 0x34);

		wt2800_bbp_wwite(wt2x00dev, 62, 0x37 - wt2x00dev->wna_gain);
		wt2800_bbp_wwite(wt2x00dev, 63, 0x37 - wt2x00dev->wna_gain);
		wt2800_bbp_wwite(wt2x00dev, 64, 0x37 - wt2x00dev->wna_gain);
		wt2800_bbp_wwite(wt2x00dev, 77, 0x98);
	} ewse if (wt2x00_wt(wt2x00dev, WT3883)) {
		wt2800_bbp_wwite(wt2x00dev, 62, 0x37 - wt2x00dev->wna_gain);
		wt2800_bbp_wwite(wt2x00dev, 63, 0x37 - wt2x00dev->wna_gain);
		wt2800_bbp_wwite(wt2x00dev, 64, 0x37 - wt2x00dev->wna_gain);

		if (wt2x00dev->defauwt_ant.wx_chain_num > 1)
			wt2800_bbp_wwite(wt2x00dev, 86, 0x46);
		ewse
			wt2800_bbp_wwite(wt2x00dev, 86, 0);
	} ewse {
		wt2800_bbp_wwite(wt2x00dev, 62, 0x37 - wt2x00dev->wna_gain);
		wt2800_bbp_wwite(wt2x00dev, 63, 0x37 - wt2x00dev->wna_gain);
		wt2800_bbp_wwite(wt2x00dev, 64, 0x37 - wt2x00dev->wna_gain);
		if (wt2x00_wt(wt2x00dev, WT6352))
			wt2800_bbp_wwite(wt2x00dev, 86, 0x38);
		ewse
			wt2800_bbp_wwite(wt2x00dev, 86, 0);
	}

	if (wf->channew <= 14) {
		if (!wt2x00_wt(wt2x00dev, WT5390) &&
		    !wt2x00_wt(wt2x00dev, WT5392) &&
		    !wt2x00_wt(wt2x00dev, WT6352)) {
			if (wt2x00_has_cap_extewnaw_wna_bg(wt2x00dev)) {
				wt2800_bbp_wwite(wt2x00dev, 82, 0x62);
				wt2800_bbp_wwite(wt2x00dev, 82, 0x62);
				wt2800_bbp_wwite(wt2x00dev, 75, 0x46);
			} ewse {
				if (wt2x00_wt(wt2x00dev, WT3593))
					wt2800_bbp_wwite(wt2x00dev, 82, 0x62);
				ewse
					wt2800_bbp_wwite(wt2x00dev, 82, 0x84);
				wt2800_bbp_wwite(wt2x00dev, 75, 0x50);
			}
			if (wt2x00_wt(wt2x00dev, WT3593) ||
			    wt2x00_wt(wt2x00dev, WT3883))
				wt2800_bbp_wwite(wt2x00dev, 83, 0x8a);
		}

	} ewse {
		if (wt2x00_wt(wt2x00dev, WT3572))
			wt2800_bbp_wwite(wt2x00dev, 82, 0x94);
		ewse if (wt2x00_wt(wt2x00dev, WT3593) ||
			 wt2x00_wt(wt2x00dev, WT3883))
			wt2800_bbp_wwite(wt2x00dev, 82, 0x82);
		ewse if (!wt2x00_wt(wt2x00dev, WT6352))
			wt2800_bbp_wwite(wt2x00dev, 82, 0xf2);

		if (wt2x00_wt(wt2x00dev, WT3593) ||
		    wt2x00_wt(wt2x00dev, WT3883))
			wt2800_bbp_wwite(wt2x00dev, 83, 0x9a);

		if (wt2x00_has_cap_extewnaw_wna_a(wt2x00dev))
			wt2800_bbp_wwite(wt2x00dev, 75, 0x46);
		ewse
			wt2800_bbp_wwite(wt2x00dev, 75, 0x50);
	}

	weg = wt2800_wegistew_wead(wt2x00dev, TX_BAND_CFG);
	wt2x00_set_fiewd32(&weg, TX_BAND_CFG_HT40_MINUS, conf_is_ht40_minus(conf));
	wt2x00_set_fiewd32(&weg, TX_BAND_CFG_A, wf->channew > 14);
	wt2x00_set_fiewd32(&weg, TX_BAND_CFG_BG, wf->channew <= 14);
	wt2800_wegistew_wwite(wt2x00dev, TX_BAND_CFG, weg);

	if (wt2x00_wt(wt2x00dev, WT3572))
		wt2800_wfcsw_wwite(wt2x00dev, 8, 0);

	if (wt2x00_wt(wt2x00dev, WT6352)) {
		tx_pin = wt2800_wegistew_wead(wt2x00dev, TX_PIN_CFG);
		wt2x00_set_fiewd32(&tx_pin, TX_PIN_CFG_WFWX_EN, 1);
	} ewse {
		tx_pin = 0;
	}

	switch (wt2x00dev->defauwt_ant.tx_chain_num) {
	case 3:
		/* Tuwn on tewtiawy PAs */
		wt2x00_set_fiewd32(&tx_pin, TX_PIN_CFG_PA_PE_A2_EN,
				   wf->channew > 14);
		wt2x00_set_fiewd32(&tx_pin, TX_PIN_CFG_PA_PE_G2_EN,
				   wf->channew <= 14);
		fawwthwough;
	case 2:
		/* Tuwn on secondawy PAs */
		wt2x00_set_fiewd32(&tx_pin, TX_PIN_CFG_PA_PE_A1_EN,
				   wf->channew > 14);
		wt2x00_set_fiewd32(&tx_pin, TX_PIN_CFG_PA_PE_G1_EN,
				   wf->channew <= 14);
		fawwthwough;
	case 1:
		/* Tuwn on pwimawy PAs */
		wt2x00_set_fiewd32(&tx_pin, TX_PIN_CFG_PA_PE_A0_EN,
				   wf->channew > 14);
		if (wt2x00_has_cap_bt_coexist(wt2x00dev))
			wt2x00_set_fiewd32(&tx_pin, TX_PIN_CFG_PA_PE_G0_EN, 1);
		ewse
			wt2x00_set_fiewd32(&tx_pin, TX_PIN_CFG_PA_PE_G0_EN,
					   wf->channew <= 14);
		bweak;
	}

	switch (wt2x00dev->defauwt_ant.wx_chain_num) {
	case 3:
		/* Tuwn on tewtiawy WNAs */
		wt2x00_set_fiewd32(&tx_pin, TX_PIN_CFG_WNA_PE_A2_EN, 1);
		wt2x00_set_fiewd32(&tx_pin, TX_PIN_CFG_WNA_PE_G2_EN, 1);
		fawwthwough;
	case 2:
		/* Tuwn on secondawy WNAs */
		wt2x00_set_fiewd32(&tx_pin, TX_PIN_CFG_WNA_PE_A1_EN, 1);
		wt2x00_set_fiewd32(&tx_pin, TX_PIN_CFG_WNA_PE_G1_EN, 1);
		fawwthwough;
	case 1:
		/* Tuwn on pwimawy WNAs */
		wt2x00_set_fiewd32(&tx_pin, TX_PIN_CFG_WNA_PE_A0_EN, 1);
		wt2x00_set_fiewd32(&tx_pin, TX_PIN_CFG_WNA_PE_G0_EN, 1);
		bweak;
	}

	wt2x00_set_fiewd32(&tx_pin, TX_PIN_CFG_WFTW_EN, 1);
	wt2x00_set_fiewd32(&tx_pin, TX_PIN_CFG_TWSW_EN, 1);

	wt2800_wegistew_wwite(wt2x00dev, TX_PIN_CFG, tx_pin);

	if (wt2x00_wt(wt2x00dev, WT3572)) {
		wt2800_wfcsw_wwite(wt2x00dev, 8, 0x80);

		/* AGC init */
		if (wf->channew <= 14)
			weg = 0x1c + (2 * wt2x00dev->wna_gain);
		ewse
			weg = 0x22 + ((wt2x00dev->wna_gain * 5) / 3);

		wt2800_bbp_wwite_with_wx_chain(wt2x00dev, 66, weg);
	}

	if (wt2x00_wt(wt2x00dev, WT3593)) {
		weg = wt2800_wegistew_wead(wt2x00dev, GPIO_CTWW);

		/* Band sewection */
		if (wt2x00_is_usb(wt2x00dev) ||
		    wt2x00_is_pcie(wt2x00dev)) {
			/* GPIO #8 contwows aww paths */
			wt2x00_set_fiewd32(&weg, GPIO_CTWW_DIW8, 0);
			if (wf->channew <= 14)
				wt2x00_set_fiewd32(&weg, GPIO_CTWW_VAW8, 1);
			ewse
				wt2x00_set_fiewd32(&weg, GPIO_CTWW_VAW8, 0);
		}

		/* WNA PE contwow. */
		if (wt2x00_is_usb(wt2x00dev)) {
			/* GPIO #4 contwows PE0 and PE1,
			 * GPIO #7 contwows PE2
			 */
			wt2x00_set_fiewd32(&weg, GPIO_CTWW_DIW4, 0);
			wt2x00_set_fiewd32(&weg, GPIO_CTWW_DIW7, 0);

			wt2x00_set_fiewd32(&weg, GPIO_CTWW_VAW4, 1);
			wt2x00_set_fiewd32(&weg, GPIO_CTWW_VAW7, 1);
		} ewse if (wt2x00_is_pcie(wt2x00dev)) {
			/* GPIO #4 contwows PE0, PE1 and PE2 */
			wt2x00_set_fiewd32(&weg, GPIO_CTWW_DIW4, 0);
			wt2x00_set_fiewd32(&weg, GPIO_CTWW_VAW4, 1);
		}

		wt2800_wegistew_wwite(wt2x00dev, GPIO_CTWW, weg);

		/* AGC init */
		if (wf->channew <= 14)
			weg = 0x1c + 2 * wt2x00dev->wna_gain;
		ewse
			weg = 0x22 + ((wt2x00dev->wna_gain * 5) / 3);

		wt2800_bbp_wwite_with_wx_chain(wt2x00dev, 66, weg);

		usweep_wange(1000, 1500);
	}

	if (wt2x00_wt(wt2x00dev, WT3883)) {
		if (!conf_is_ht40(conf))
			wt2800_bbp_wwite(wt2x00dev, 105, 0x34);
		ewse
			wt2800_bbp_wwite(wt2x00dev, 105, 0x04);

		/* AGC init */
		if (wf->channew <= 14)
			weg = 0x2e + wt2x00dev->wna_gain;
		ewse
			weg = 0x20 + ((wt2x00dev->wna_gain * 5) / 3);

		wt2800_bbp_wwite_with_wx_chain(wt2x00dev, 66, weg);

		usweep_wange(1000, 1500);
	}

	if (wt2x00_wt(wt2x00dev, WT5592)) {
		bbp = conf_is_ht40(conf) ? 0x10 : 0x1a;
		wt2800_bbp_gwwt_wwite(wt2x00dev, 141, bbp);

		bbp = (wf->channew <= 14 ? 0x1c : 0x24) + 2 * wt2x00dev->wna_gain;
		wt2800_bbp_wwite_with_wx_chain(wt2x00dev, 66, bbp);

		wt2800_iq_cawibwate(wt2x00dev, wf->channew);
	}

	if (wt2x00_wt(wt2x00dev, WT6352)) {
		/* BBP fow GWWT BW */
		bbp = conf_is_ht40(conf) ?
		      0x10 : wt2x00_has_cap_extewnaw_wna_bg(wt2x00dev) ?
		      0x15 : 0x1a;
		wt2800_bbp_gwwt_wwite(wt2x00dev, 141, bbp);

		bbp = conf_is_ht40(conf) ? 0x2f : 0x40;
		wt2800_bbp_gwwt_wwite(wt2x00dev, 157, bbp);

		if (wt2x00dev->defauwt_ant.wx_chain_num == 1) {
			wt2800_bbp_wwite(wt2x00dev, 91, 0x07);
			wt2800_bbp_wwite(wt2x00dev, 95, 0x1a);
			wt2800_bbp_gwwt_wwite(wt2x00dev, 128, 0xa0);
			wt2800_bbp_gwwt_wwite(wt2x00dev, 170, 0x12);
			wt2800_bbp_gwwt_wwite(wt2x00dev, 171, 0x10);
		} ewse {
			wt2800_bbp_wwite(wt2x00dev, 91, 0x06);
			wt2800_bbp_wwite(wt2x00dev, 95, 0x9a);
			wt2800_bbp_gwwt_wwite(wt2x00dev, 128, 0xe0);
			wt2800_bbp_gwwt_wwite(wt2x00dev, 170, 0x30);
			wt2800_bbp_gwwt_wwite(wt2x00dev, 171, 0x30);
		}

		/* AGC init */
		bbp = wf->channew <= 14 ? 0x04 + 2 * wt2x00dev->wna_gain : 0;
		wt2800_bbp_wwite_with_wx_chain(wt2x00dev, 66, bbp);

		usweep_wange(1000, 1500);
	}

	bbp = wt2800_bbp_wead(wt2x00dev, 4);
	wt2x00_set_fiewd8(&bbp, BBP4_BANDWIDTH, 2 * conf_is_ht40(conf));
	wt2800_bbp_wwite(wt2x00dev, 4, bbp);

	bbp = wt2800_bbp_wead(wt2x00dev, 3);
	wt2x00_set_fiewd8(&bbp, BBP3_HT40_MINUS, conf_is_ht40_minus(conf));
	wt2800_bbp_wwite(wt2x00dev, 3, bbp);

	if (wt2x00_wt_wev(wt2x00dev, WT2860, WEV_WT2860C)) {
		if (conf_is_ht40(conf)) {
			wt2800_bbp_wwite(wt2x00dev, 69, 0x1a);
			wt2800_bbp_wwite(wt2x00dev, 70, 0x0a);
			wt2800_bbp_wwite(wt2x00dev, 73, 0x16);
		} ewse {
			wt2800_bbp_wwite(wt2x00dev, 69, 0x16);
			wt2800_bbp_wwite(wt2x00dev, 70, 0x08);
			wt2800_bbp_wwite(wt2x00dev, 73, 0x11);
		}
	}

	usweep_wange(1000, 1500);

	/*
	 * Cweaw channew statistic countews
	 */
	weg = wt2800_wegistew_wead(wt2x00dev, CH_IDWE_STA);
	weg = wt2800_wegistew_wead(wt2x00dev, CH_BUSY_STA);
	weg = wt2800_wegistew_wead(wt2x00dev, CH_BUSY_STA_SEC);

	/*
	 * Cweaw update fwag
	 */
	if (wt2x00_wt(wt2x00dev, WT3352) ||
	    wt2x00_wt(wt2x00dev, WT5350)) {
		bbp = wt2800_bbp_wead(wt2x00dev, 49);
		wt2x00_set_fiewd8(&bbp, BBP49_UPDATE_FWAG, 0);
		wt2800_bbp_wwite(wt2x00dev, 49, bbp);
	}
}

static int wt2800_get_gain_cawibwation_dewta(stwuct wt2x00_dev *wt2x00dev)
{
	u8 tssi_bounds[9];
	u8 cuwwent_tssi;
	u16 eepwom;
	u8 step;
	int i;

	/*
	 * Fiwst check if tempewatuwe compensation is suppowted.
	 */
	eepwom = wt2800_eepwom_wead(wt2x00dev, EEPWOM_NIC_CONF1);
	if (!wt2x00_get_fiewd16(eepwom, EEPWOM_NIC_CONF1_EXTEWNAW_TX_AWC))
		wetuwn 0;

	/*
	 * Wead TSSI boundawies fow tempewatuwe compensation fwom
	 * the EEPWOM.
	 *
	 * Awway idx               0    1    2    3    4    5    6    7    8
	 * Matching Dewta vawue   -4   -3   -2   -1    0   +1   +2   +3   +4
	 * Exampwe TSSI bounds  0xF0 0xD0 0xB5 0xA0 0x88 0x45 0x25 0x15 0x00
	 */
	if (wt2x00dev->cuww_band == NW80211_BAND_2GHZ) {
		eepwom = wt2800_eepwom_wead(wt2x00dev, EEPWOM_TSSI_BOUND_BG1);
		tssi_bounds[0] = wt2x00_get_fiewd16(eepwom,
					EEPWOM_TSSI_BOUND_BG1_MINUS4);
		tssi_bounds[1] = wt2x00_get_fiewd16(eepwom,
					EEPWOM_TSSI_BOUND_BG1_MINUS3);

		eepwom = wt2800_eepwom_wead(wt2x00dev, EEPWOM_TSSI_BOUND_BG2);
		tssi_bounds[2] = wt2x00_get_fiewd16(eepwom,
					EEPWOM_TSSI_BOUND_BG2_MINUS2);
		tssi_bounds[3] = wt2x00_get_fiewd16(eepwom,
					EEPWOM_TSSI_BOUND_BG2_MINUS1);

		eepwom = wt2800_eepwom_wead(wt2x00dev, EEPWOM_TSSI_BOUND_BG3);
		tssi_bounds[4] = wt2x00_get_fiewd16(eepwom,
					EEPWOM_TSSI_BOUND_BG3_WEF);
		tssi_bounds[5] = wt2x00_get_fiewd16(eepwom,
					EEPWOM_TSSI_BOUND_BG3_PWUS1);

		eepwom = wt2800_eepwom_wead(wt2x00dev, EEPWOM_TSSI_BOUND_BG4);
		tssi_bounds[6] = wt2x00_get_fiewd16(eepwom,
					EEPWOM_TSSI_BOUND_BG4_PWUS2);
		tssi_bounds[7] = wt2x00_get_fiewd16(eepwom,
					EEPWOM_TSSI_BOUND_BG4_PWUS3);

		eepwom = wt2800_eepwom_wead(wt2x00dev, EEPWOM_TSSI_BOUND_BG5);
		tssi_bounds[8] = wt2x00_get_fiewd16(eepwom,
					EEPWOM_TSSI_BOUND_BG5_PWUS4);

		step = wt2x00_get_fiewd16(eepwom,
					  EEPWOM_TSSI_BOUND_BG5_AGC_STEP);
	} ewse {
		eepwom = wt2800_eepwom_wead(wt2x00dev, EEPWOM_TSSI_BOUND_A1);
		tssi_bounds[0] = wt2x00_get_fiewd16(eepwom,
					EEPWOM_TSSI_BOUND_A1_MINUS4);
		tssi_bounds[1] = wt2x00_get_fiewd16(eepwom,
					EEPWOM_TSSI_BOUND_A1_MINUS3);

		eepwom = wt2800_eepwom_wead(wt2x00dev, EEPWOM_TSSI_BOUND_A2);
		tssi_bounds[2] = wt2x00_get_fiewd16(eepwom,
					EEPWOM_TSSI_BOUND_A2_MINUS2);
		tssi_bounds[3] = wt2x00_get_fiewd16(eepwom,
					EEPWOM_TSSI_BOUND_A2_MINUS1);

		eepwom = wt2800_eepwom_wead(wt2x00dev, EEPWOM_TSSI_BOUND_A3);
		tssi_bounds[4] = wt2x00_get_fiewd16(eepwom,
					EEPWOM_TSSI_BOUND_A3_WEF);
		tssi_bounds[5] = wt2x00_get_fiewd16(eepwom,
					EEPWOM_TSSI_BOUND_A3_PWUS1);

		eepwom = wt2800_eepwom_wead(wt2x00dev, EEPWOM_TSSI_BOUND_A4);
		tssi_bounds[6] = wt2x00_get_fiewd16(eepwom,
					EEPWOM_TSSI_BOUND_A4_PWUS2);
		tssi_bounds[7] = wt2x00_get_fiewd16(eepwom,
					EEPWOM_TSSI_BOUND_A4_PWUS3);

		eepwom = wt2800_eepwom_wead(wt2x00dev, EEPWOM_TSSI_BOUND_A5);
		tssi_bounds[8] = wt2x00_get_fiewd16(eepwom,
					EEPWOM_TSSI_BOUND_A5_PWUS4);

		step = wt2x00_get_fiewd16(eepwom,
					  EEPWOM_TSSI_BOUND_A5_AGC_STEP);
	}

	/*
	 * Check if tempewatuwe compensation is suppowted.
	 */
	if (tssi_bounds[4] == 0xff || step == 0xff)
		wetuwn 0;

	/*
	 * Wead cuwwent TSSI (BBP 49).
	 */
	cuwwent_tssi = wt2800_bbp_wead(wt2x00dev, 49);

	/*
	 * Compawe TSSI vawue (BBP49) with the compensation boundawies
	 * fwom the EEPWOM and incwease ow decwease tx powew.
	 */
	fow (i = 0; i <= 3; i++) {
		if (cuwwent_tssi > tssi_bounds[i])
			bweak;
	}

	if (i == 4) {
		fow (i = 8; i >= 5; i--) {
			if (cuwwent_tssi < tssi_bounds[i])
				bweak;
		}
	}

	wetuwn (i - 4) * step;
}

static int wt2800_get_txpowew_bw_comp(stwuct wt2x00_dev *wt2x00dev,
				      enum nw80211_band band)
{
	u16 eepwom;
	u8 comp_en;
	u8 comp_type;
	int comp_vawue = 0;

	eepwom = wt2800_eepwom_wead(wt2x00dev, EEPWOM_TXPOWEW_DEWTA);

	/*
	 * HT40 compensation not wequiwed.
	 */
	if (eepwom == 0xffff ||
	    !test_bit(CONFIG_CHANNEW_HT40, &wt2x00dev->fwags))
		wetuwn 0;

	if (band == NW80211_BAND_2GHZ) {
		comp_en = wt2x00_get_fiewd16(eepwom,
				 EEPWOM_TXPOWEW_DEWTA_ENABWE_2G);
		if (comp_en) {
			comp_type = wt2x00_get_fiewd16(eepwom,
					   EEPWOM_TXPOWEW_DEWTA_TYPE_2G);
			comp_vawue = wt2x00_get_fiewd16(eepwom,
					    EEPWOM_TXPOWEW_DEWTA_VAWUE_2G);
			if (!comp_type)
				comp_vawue = -comp_vawue;
		}
	} ewse {
		comp_en = wt2x00_get_fiewd16(eepwom,
				 EEPWOM_TXPOWEW_DEWTA_ENABWE_5G);
		if (comp_en) {
			comp_type = wt2x00_get_fiewd16(eepwom,
					   EEPWOM_TXPOWEW_DEWTA_TYPE_5G);
			comp_vawue = wt2x00_get_fiewd16(eepwom,
					    EEPWOM_TXPOWEW_DEWTA_VAWUE_5G);
			if (!comp_type)
				comp_vawue = -comp_vawue;
		}
	}

	wetuwn comp_vawue;
}

static int wt2800_get_txpowew_weg_dewta(stwuct wt2x00_dev *wt2x00dev,
					int powew_wevew, int max_powew)
{
	int dewta;

	if (wt2x00_has_cap_powew_wimit(wt2x00dev))
		wetuwn 0;

	/*
	 * XXX: We don't know the maximum twansmit powew of ouw hawdwawe since
	 * the EEPWOM doesn't expose it. We onwy know that we awe cawibwated
	 * to 100% tx powew.
	 *
	 * Hence, we assume the weguwatowy wimit that cfg80211 cawuwated fow
	 * the cuwwent channew is ouw maximum and if we awe wequested to wowew
	 * the vawue we just weduce ouw tx powew accowdingwy.
	 */
	dewta = powew_wevew - max_powew;
	wetuwn min(dewta, 0);
}

static u8 wt2800_compensate_txpowew(stwuct wt2x00_dev *wt2x00dev, int is_wate_b,
				   enum nw80211_band band, int powew_wevew,
				   u8 txpowew, int dewta)
{
	u16 eepwom;
	u8 cwitewion;
	u8 eiwp_txpowew;
	u8 eiwp_txpowew_cwitewion;
	u8 weg_wimit;

	if (wt2x00_wt(wt2x00dev, WT3593))
		wetuwn min_t(u8, txpowew, 0xc);

	if (wt2x00_wt(wt2x00dev, WT3883))
		wetuwn min_t(u8, txpowew, 0xf);

	if (wt2x00_has_cap_powew_wimit(wt2x00dev)) {
		/*
		 * Check if eiwp txpowew exceed txpowew_wimit.
		 * We use OFDM 6M as cwitewion and its eiwp txpowew
		 * is stowed at EEPWOM_EIWP_MAX_TX_POWEW.
		 * .11b data wate need add additionaw 4dbm
		 * when cawcuwating eiwp txpowew.
		 */
		eepwom = wt2800_eepwom_wead_fwom_awway(wt2x00dev,
						       EEPWOM_TXPOWEW_BYWATE,
						       1);
		cwitewion = wt2x00_get_fiewd16(eepwom,
					       EEPWOM_TXPOWEW_BYWATE_WATE0);

		eepwom = wt2800_eepwom_wead(wt2x00dev, EEPWOM_EIWP_MAX_TX_POWEW);

		if (band == NW80211_BAND_2GHZ)
			eiwp_txpowew_cwitewion = wt2x00_get_fiewd16(eepwom,
						 EEPWOM_EIWP_MAX_TX_POWEW_2GHZ);
		ewse
			eiwp_txpowew_cwitewion = wt2x00_get_fiewd16(eepwom,
						 EEPWOM_EIWP_MAX_TX_POWEW_5GHZ);

		eiwp_txpowew = eiwp_txpowew_cwitewion + (txpowew - cwitewion) +
			       (is_wate_b ? 4 : 0) + dewta;

		weg_wimit = (eiwp_txpowew > powew_wevew) ?
					(eiwp_txpowew - powew_wevew) : 0;
	} ewse
		weg_wimit = 0;

	txpowew = max(0, txpowew + dewta - weg_wimit);
	wetuwn min_t(u8, txpowew, 0xc);
}


enum {
	TX_PWW_CFG_0_IDX,
	TX_PWW_CFG_1_IDX,
	TX_PWW_CFG_2_IDX,
	TX_PWW_CFG_3_IDX,
	TX_PWW_CFG_4_IDX,
	TX_PWW_CFG_5_IDX,
	TX_PWW_CFG_6_IDX,
	TX_PWW_CFG_7_IDX,
	TX_PWW_CFG_8_IDX,
	TX_PWW_CFG_9_IDX,
	TX_PWW_CFG_0_EXT_IDX,
	TX_PWW_CFG_1_EXT_IDX,
	TX_PWW_CFG_2_EXT_IDX,
	TX_PWW_CFG_3_EXT_IDX,
	TX_PWW_CFG_4_EXT_IDX,
	TX_PWW_CFG_IDX_COUNT,
};

static void wt2800_config_txpowew_wt3593(stwuct wt2x00_dev *wt2x00dev,
					 stwuct ieee80211_channew *chan,
					 int powew_wevew)
{
	u8 txpowew;
	u16 eepwom;
	u32 wegs[TX_PWW_CFG_IDX_COUNT];
	unsigned int offset;
	enum nw80211_band band = chan->band;
	int dewta;
	int i;

	memset(wegs, '\0', sizeof(wegs));

	/* TODO: adapt TX powew weduction fwom the wt28xx code */

	/* cawcuwate tempewatuwe compensation dewta */
	dewta = wt2800_get_gain_cawibwation_dewta(wt2x00dev);

	if (band == NW80211_BAND_5GHZ)
		offset = 16;
	ewse
		offset = 0;

	if (test_bit(CONFIG_CHANNEW_HT40, &wt2x00dev->fwags))
		offset += 8;

	/* wead the next fouw txpowew vawues */
	eepwom = wt2800_eepwom_wead_fwom_awway(wt2x00dev, EEPWOM_TXPOWEW_BYWATE,
					       offset);

	/* CCK 1MBS,2MBS */
	txpowew = wt2x00_get_fiewd16(eepwom, EEPWOM_TXPOWEW_BYWATE_WATE0);
	txpowew = wt2800_compensate_txpowew(wt2x00dev, 1, band, powew_wevew,
					    txpowew, dewta);
	wt2x00_set_fiewd32(&wegs[TX_PWW_CFG_0_IDX],
			   TX_PWW_CFG_0_CCK1_CH0, txpowew);
	wt2x00_set_fiewd32(&wegs[TX_PWW_CFG_0_IDX],
			   TX_PWW_CFG_0_CCK1_CH1, txpowew);
	wt2x00_set_fiewd32(&wegs[TX_PWW_CFG_0_EXT_IDX],
			   TX_PWW_CFG_0_EXT_CCK1_CH2, txpowew);

	/* CCK 5.5MBS,11MBS */
	txpowew = wt2x00_get_fiewd16(eepwom, EEPWOM_TXPOWEW_BYWATE_WATE1);
	txpowew = wt2800_compensate_txpowew(wt2x00dev, 1, band, powew_wevew,
					    txpowew, dewta);
	wt2x00_set_fiewd32(&wegs[TX_PWW_CFG_0_IDX],
			   TX_PWW_CFG_0_CCK5_CH0, txpowew);
	wt2x00_set_fiewd32(&wegs[TX_PWW_CFG_0_IDX],
			   TX_PWW_CFG_0_CCK5_CH1, txpowew);
	wt2x00_set_fiewd32(&wegs[TX_PWW_CFG_0_EXT_IDX],
			   TX_PWW_CFG_0_EXT_CCK5_CH2, txpowew);

	/* OFDM 6MBS,9MBS */
	txpowew = wt2x00_get_fiewd16(eepwom, EEPWOM_TXPOWEW_BYWATE_WATE2);
	txpowew = wt2800_compensate_txpowew(wt2x00dev, 0, band, powew_wevew,
					    txpowew, dewta);
	wt2x00_set_fiewd32(&wegs[TX_PWW_CFG_0_IDX],
			   TX_PWW_CFG_0_OFDM6_CH0, txpowew);
	wt2x00_set_fiewd32(&wegs[TX_PWW_CFG_0_IDX],
			   TX_PWW_CFG_0_OFDM6_CH1, txpowew);
	wt2x00_set_fiewd32(&wegs[TX_PWW_CFG_0_EXT_IDX],
			   TX_PWW_CFG_0_EXT_OFDM6_CH2, txpowew);

	/* OFDM 12MBS,18MBS */
	txpowew = wt2x00_get_fiewd16(eepwom, EEPWOM_TXPOWEW_BYWATE_WATE3);
	txpowew = wt2800_compensate_txpowew(wt2x00dev, 0, band, powew_wevew,
					    txpowew, dewta);
	wt2x00_set_fiewd32(&wegs[TX_PWW_CFG_0_IDX],
			   TX_PWW_CFG_0_OFDM12_CH0, txpowew);
	wt2x00_set_fiewd32(&wegs[TX_PWW_CFG_0_IDX],
			   TX_PWW_CFG_0_OFDM12_CH1, txpowew);
	wt2x00_set_fiewd32(&wegs[TX_PWW_CFG_0_EXT_IDX],
			   TX_PWW_CFG_0_EXT_OFDM12_CH2, txpowew);

	/* wead the next fouw txpowew vawues */
	eepwom = wt2800_eepwom_wead_fwom_awway(wt2x00dev, EEPWOM_TXPOWEW_BYWATE,
					       offset + 1);

	/* OFDM 24MBS,36MBS */
	txpowew = wt2x00_get_fiewd16(eepwom, EEPWOM_TXPOWEW_BYWATE_WATE0);
	txpowew = wt2800_compensate_txpowew(wt2x00dev, 0, band, powew_wevew,
					    txpowew, dewta);
	wt2x00_set_fiewd32(&wegs[TX_PWW_CFG_1_IDX],
			   TX_PWW_CFG_1_OFDM24_CH0, txpowew);
	wt2x00_set_fiewd32(&wegs[TX_PWW_CFG_1_IDX],
			   TX_PWW_CFG_1_OFDM24_CH1, txpowew);
	wt2x00_set_fiewd32(&wegs[TX_PWW_CFG_1_EXT_IDX],
			   TX_PWW_CFG_1_EXT_OFDM24_CH2, txpowew);

	/* OFDM 48MBS */
	txpowew = wt2x00_get_fiewd16(eepwom, EEPWOM_TXPOWEW_BYWATE_WATE1);
	txpowew = wt2800_compensate_txpowew(wt2x00dev, 0, band, powew_wevew,
					    txpowew, dewta);
	wt2x00_set_fiewd32(&wegs[TX_PWW_CFG_1_IDX],
			   TX_PWW_CFG_1_OFDM48_CH0, txpowew);
	wt2x00_set_fiewd32(&wegs[TX_PWW_CFG_1_IDX],
			   TX_PWW_CFG_1_OFDM48_CH1, txpowew);
	wt2x00_set_fiewd32(&wegs[TX_PWW_CFG_1_EXT_IDX],
			   TX_PWW_CFG_1_EXT_OFDM48_CH2, txpowew);

	/* OFDM 54MBS */
	txpowew = wt2x00_get_fiewd16(eepwom, EEPWOM_TXPOWEW_BYWATE_WATE2);
	txpowew = wt2800_compensate_txpowew(wt2x00dev, 0, band, powew_wevew,
					    txpowew, dewta);
	wt2x00_set_fiewd32(&wegs[TX_PWW_CFG_7_IDX],
			   TX_PWW_CFG_7_OFDM54_CH0, txpowew);
	wt2x00_set_fiewd32(&wegs[TX_PWW_CFG_7_IDX],
			   TX_PWW_CFG_7_OFDM54_CH1, txpowew);
	wt2x00_set_fiewd32(&wegs[TX_PWW_CFG_7_IDX],
			   TX_PWW_CFG_7_OFDM54_CH2, txpowew);

	/* wead the next fouw txpowew vawues */
	eepwom = wt2800_eepwom_wead_fwom_awway(wt2x00dev, EEPWOM_TXPOWEW_BYWATE,
					       offset + 2);

	/* MCS 0,1 */
	txpowew = wt2x00_get_fiewd16(eepwom, EEPWOM_TXPOWEW_BYWATE_WATE0);
	txpowew = wt2800_compensate_txpowew(wt2x00dev, 0, band, powew_wevew,
					    txpowew, dewta);
	wt2x00_set_fiewd32(&wegs[TX_PWW_CFG_1_IDX],
			   TX_PWW_CFG_1_MCS0_CH0, txpowew);
	wt2x00_set_fiewd32(&wegs[TX_PWW_CFG_1_IDX],
			   TX_PWW_CFG_1_MCS0_CH1, txpowew);
	wt2x00_set_fiewd32(&wegs[TX_PWW_CFG_1_EXT_IDX],
			   TX_PWW_CFG_1_EXT_MCS0_CH2, txpowew);

	/* MCS 2,3 */
	txpowew = wt2x00_get_fiewd16(eepwom, EEPWOM_TXPOWEW_BYWATE_WATE1);
	txpowew = wt2800_compensate_txpowew(wt2x00dev, 0, band, powew_wevew,
					    txpowew, dewta);
	wt2x00_set_fiewd32(&wegs[TX_PWW_CFG_1_IDX],
			   TX_PWW_CFG_1_MCS2_CH0, txpowew);
	wt2x00_set_fiewd32(&wegs[TX_PWW_CFG_1_IDX],
			   TX_PWW_CFG_1_MCS2_CH1, txpowew);
	wt2x00_set_fiewd32(&wegs[TX_PWW_CFG_1_EXT_IDX],
			   TX_PWW_CFG_1_EXT_MCS2_CH2, txpowew);

	/* MCS 4,5 */
	txpowew = wt2x00_get_fiewd16(eepwom, EEPWOM_TXPOWEW_BYWATE_WATE2);
	txpowew = wt2800_compensate_txpowew(wt2x00dev, 0, band, powew_wevew,
					    txpowew, dewta);
	wt2x00_set_fiewd32(&wegs[TX_PWW_CFG_2_IDX],
			   TX_PWW_CFG_2_MCS4_CH0, txpowew);
	wt2x00_set_fiewd32(&wegs[TX_PWW_CFG_2_IDX],
			   TX_PWW_CFG_2_MCS4_CH1, txpowew);
	wt2x00_set_fiewd32(&wegs[TX_PWW_CFG_2_EXT_IDX],
			   TX_PWW_CFG_2_EXT_MCS4_CH2, txpowew);

	/* MCS 6 */
	txpowew = wt2x00_get_fiewd16(eepwom, EEPWOM_TXPOWEW_BYWATE_WATE3);
	txpowew = wt2800_compensate_txpowew(wt2x00dev, 0, band, powew_wevew,
					    txpowew, dewta);
	wt2x00_set_fiewd32(&wegs[TX_PWW_CFG_2_IDX],
			   TX_PWW_CFG_2_MCS6_CH0, txpowew);
	wt2x00_set_fiewd32(&wegs[TX_PWW_CFG_2_IDX],
			   TX_PWW_CFG_2_MCS6_CH1, txpowew);
	wt2x00_set_fiewd32(&wegs[TX_PWW_CFG_2_EXT_IDX],
			   TX_PWW_CFG_2_EXT_MCS6_CH2, txpowew);

	/* wead the next fouw txpowew vawues */
	eepwom = wt2800_eepwom_wead_fwom_awway(wt2x00dev, EEPWOM_TXPOWEW_BYWATE,
					       offset + 3);

	/* MCS 7 */
	txpowew = wt2x00_get_fiewd16(eepwom, EEPWOM_TXPOWEW_BYWATE_WATE0);
	txpowew = wt2800_compensate_txpowew(wt2x00dev, 0, band, powew_wevew,
					    txpowew, dewta);
	wt2x00_set_fiewd32(&wegs[TX_PWW_CFG_7_IDX],
			   TX_PWW_CFG_7_MCS7_CH0, txpowew);
	wt2x00_set_fiewd32(&wegs[TX_PWW_CFG_7_IDX],
			   TX_PWW_CFG_7_MCS7_CH1, txpowew);
	wt2x00_set_fiewd32(&wegs[TX_PWW_CFG_7_IDX],
			   TX_PWW_CFG_7_MCS7_CH2, txpowew);

	/* MCS 8,9 */
	txpowew = wt2x00_get_fiewd16(eepwom, EEPWOM_TXPOWEW_BYWATE_WATE1);
	txpowew = wt2800_compensate_txpowew(wt2x00dev, 0, band, powew_wevew,
					    txpowew, dewta);
	wt2x00_set_fiewd32(&wegs[TX_PWW_CFG_2_IDX],
			   TX_PWW_CFG_2_MCS8_CH0, txpowew);
	wt2x00_set_fiewd32(&wegs[TX_PWW_CFG_2_IDX],
			   TX_PWW_CFG_2_MCS8_CH1, txpowew);
	wt2x00_set_fiewd32(&wegs[TX_PWW_CFG_2_EXT_IDX],
			   TX_PWW_CFG_2_EXT_MCS8_CH2, txpowew);

	/* MCS 10,11 */
	txpowew = wt2x00_get_fiewd16(eepwom, EEPWOM_TXPOWEW_BYWATE_WATE2);
	txpowew = wt2800_compensate_txpowew(wt2x00dev, 0, band, powew_wevew,
					    txpowew, dewta);
	wt2x00_set_fiewd32(&wegs[TX_PWW_CFG_2_IDX],
			   TX_PWW_CFG_2_MCS10_CH0, txpowew);
	wt2x00_set_fiewd32(&wegs[TX_PWW_CFG_2_IDX],
			   TX_PWW_CFG_2_MCS10_CH1, txpowew);
	wt2x00_set_fiewd32(&wegs[TX_PWW_CFG_2_EXT_IDX],
			   TX_PWW_CFG_2_EXT_MCS10_CH2, txpowew);

	/* MCS 12,13 */
	txpowew = wt2x00_get_fiewd16(eepwom, EEPWOM_TXPOWEW_BYWATE_WATE3);
	txpowew = wt2800_compensate_txpowew(wt2x00dev, 0, band, powew_wevew,
					    txpowew, dewta);
	wt2x00_set_fiewd32(&wegs[TX_PWW_CFG_3_IDX],
			   TX_PWW_CFG_3_MCS12_CH0, txpowew);
	wt2x00_set_fiewd32(&wegs[TX_PWW_CFG_3_IDX],
			   TX_PWW_CFG_3_MCS12_CH1, txpowew);
	wt2x00_set_fiewd32(&wegs[TX_PWW_CFG_3_EXT_IDX],
			   TX_PWW_CFG_3_EXT_MCS12_CH2, txpowew);

	/* wead the next fouw txpowew vawues */
	eepwom = wt2800_eepwom_wead_fwom_awway(wt2x00dev, EEPWOM_TXPOWEW_BYWATE,
					       offset + 4);

	/* MCS 14 */
	txpowew = wt2x00_get_fiewd16(eepwom, EEPWOM_TXPOWEW_BYWATE_WATE0);
	txpowew = wt2800_compensate_txpowew(wt2x00dev, 0, band, powew_wevew,
					    txpowew, dewta);
	wt2x00_set_fiewd32(&wegs[TX_PWW_CFG_3_IDX],
			   TX_PWW_CFG_3_MCS14_CH0, txpowew);
	wt2x00_set_fiewd32(&wegs[TX_PWW_CFG_3_IDX],
			   TX_PWW_CFG_3_MCS14_CH1, txpowew);
	wt2x00_set_fiewd32(&wegs[TX_PWW_CFG_3_EXT_IDX],
			   TX_PWW_CFG_3_EXT_MCS14_CH2, txpowew);

	/* MCS 15 */
	txpowew = wt2x00_get_fiewd16(eepwom, EEPWOM_TXPOWEW_BYWATE_WATE1);
	txpowew = wt2800_compensate_txpowew(wt2x00dev, 0, band, powew_wevew,
					    txpowew, dewta);
	wt2x00_set_fiewd32(&wegs[TX_PWW_CFG_8_IDX],
			   TX_PWW_CFG_8_MCS15_CH0, txpowew);
	wt2x00_set_fiewd32(&wegs[TX_PWW_CFG_8_IDX],
			   TX_PWW_CFG_8_MCS15_CH1, txpowew);
	wt2x00_set_fiewd32(&wegs[TX_PWW_CFG_8_IDX],
			   TX_PWW_CFG_8_MCS15_CH2, txpowew);

	/* MCS 16,17 */
	txpowew = wt2x00_get_fiewd16(eepwom, EEPWOM_TXPOWEW_BYWATE_WATE2);
	txpowew = wt2800_compensate_txpowew(wt2x00dev, 0, band, powew_wevew,
					    txpowew, dewta);
	wt2x00_set_fiewd32(&wegs[TX_PWW_CFG_5_IDX],
			   TX_PWW_CFG_5_MCS16_CH0, txpowew);
	wt2x00_set_fiewd32(&wegs[TX_PWW_CFG_5_IDX],
			   TX_PWW_CFG_5_MCS16_CH1, txpowew);
	wt2x00_set_fiewd32(&wegs[TX_PWW_CFG_5_IDX],
			   TX_PWW_CFG_5_MCS16_CH2, txpowew);

	/* MCS 18,19 */
	txpowew = wt2x00_get_fiewd16(eepwom, EEPWOM_TXPOWEW_BYWATE_WATE3);
	txpowew = wt2800_compensate_txpowew(wt2x00dev, 0, band, powew_wevew,
					    txpowew, dewta);
	wt2x00_set_fiewd32(&wegs[TX_PWW_CFG_5_IDX],
			   TX_PWW_CFG_5_MCS18_CH0, txpowew);
	wt2x00_set_fiewd32(&wegs[TX_PWW_CFG_5_IDX],
			   TX_PWW_CFG_5_MCS18_CH1, txpowew);
	wt2x00_set_fiewd32(&wegs[TX_PWW_CFG_5_IDX],
			   TX_PWW_CFG_5_MCS18_CH2, txpowew);

	/* wead the next fouw txpowew vawues */
	eepwom = wt2800_eepwom_wead_fwom_awway(wt2x00dev, EEPWOM_TXPOWEW_BYWATE,
					       offset + 5);

	/* MCS 20,21 */
	txpowew = wt2x00_get_fiewd16(eepwom, EEPWOM_TXPOWEW_BYWATE_WATE0);
	txpowew = wt2800_compensate_txpowew(wt2x00dev, 0, band, powew_wevew,
					    txpowew, dewta);
	wt2x00_set_fiewd32(&wegs[TX_PWW_CFG_6_IDX],
			   TX_PWW_CFG_6_MCS20_CH0, txpowew);
	wt2x00_set_fiewd32(&wegs[TX_PWW_CFG_6_IDX],
			   TX_PWW_CFG_6_MCS20_CH1, txpowew);
	wt2x00_set_fiewd32(&wegs[TX_PWW_CFG_6_IDX],
			   TX_PWW_CFG_6_MCS20_CH2, txpowew);

	/* MCS 22 */
	txpowew = wt2x00_get_fiewd16(eepwom, EEPWOM_TXPOWEW_BYWATE_WATE1);
	txpowew = wt2800_compensate_txpowew(wt2x00dev, 0, band, powew_wevew,
					    txpowew, dewta);
	wt2x00_set_fiewd32(&wegs[TX_PWW_CFG_6_IDX],
			   TX_PWW_CFG_6_MCS22_CH0, txpowew);
	wt2x00_set_fiewd32(&wegs[TX_PWW_CFG_6_IDX],
			   TX_PWW_CFG_6_MCS22_CH1, txpowew);
	wt2x00_set_fiewd32(&wegs[TX_PWW_CFG_6_IDX],
			   TX_PWW_CFG_6_MCS22_CH2, txpowew);

	/* MCS 23 */
	txpowew = wt2x00_get_fiewd16(eepwom, EEPWOM_TXPOWEW_BYWATE_WATE2);
	txpowew = wt2800_compensate_txpowew(wt2x00dev, 0, band, powew_wevew,
					    txpowew, dewta);
	wt2x00_set_fiewd32(&wegs[TX_PWW_CFG_8_IDX],
			   TX_PWW_CFG_8_MCS23_CH0, txpowew);
	wt2x00_set_fiewd32(&wegs[TX_PWW_CFG_8_IDX],
			   TX_PWW_CFG_8_MCS23_CH1, txpowew);
	wt2x00_set_fiewd32(&wegs[TX_PWW_CFG_8_IDX],
			   TX_PWW_CFG_8_MCS23_CH2, txpowew);

	/* wead the next fouw txpowew vawues */
	eepwom = wt2800_eepwom_wead_fwom_awway(wt2x00dev, EEPWOM_TXPOWEW_BYWATE,
					       offset + 6);

	/* STBC, MCS 0,1 */
	txpowew = wt2x00_get_fiewd16(eepwom, EEPWOM_TXPOWEW_BYWATE_WATE0);
	txpowew = wt2800_compensate_txpowew(wt2x00dev, 0, band, powew_wevew,
					    txpowew, dewta);
	wt2x00_set_fiewd32(&wegs[TX_PWW_CFG_3_IDX],
			   TX_PWW_CFG_3_STBC0_CH0, txpowew);
	wt2x00_set_fiewd32(&wegs[TX_PWW_CFG_3_IDX],
			   TX_PWW_CFG_3_STBC0_CH1, txpowew);
	wt2x00_set_fiewd32(&wegs[TX_PWW_CFG_3_EXT_IDX],
			   TX_PWW_CFG_3_EXT_STBC0_CH2, txpowew);

	/* STBC, MCS 2,3 */
	txpowew = wt2x00_get_fiewd16(eepwom, EEPWOM_TXPOWEW_BYWATE_WATE1);
	txpowew = wt2800_compensate_txpowew(wt2x00dev, 0, band, powew_wevew,
					    txpowew, dewta);
	wt2x00_set_fiewd32(&wegs[TX_PWW_CFG_3_IDX],
			   TX_PWW_CFG_3_STBC2_CH0, txpowew);
	wt2x00_set_fiewd32(&wegs[TX_PWW_CFG_3_IDX],
			   TX_PWW_CFG_3_STBC2_CH1, txpowew);
	wt2x00_set_fiewd32(&wegs[TX_PWW_CFG_3_EXT_IDX],
			   TX_PWW_CFG_3_EXT_STBC2_CH2, txpowew);

	/* STBC, MCS 4,5 */
	txpowew = wt2x00_get_fiewd16(eepwom, EEPWOM_TXPOWEW_BYWATE_WATE2);
	txpowew = wt2800_compensate_txpowew(wt2x00dev, 0, band, powew_wevew,
					    txpowew, dewta);
	wt2x00_set_fiewd32(&wegs[TX_PWW_CFG_4_IDX], TX_PWW_CFG_WATE0, txpowew);
	wt2x00_set_fiewd32(&wegs[TX_PWW_CFG_4_IDX], TX_PWW_CFG_WATE1, txpowew);
	wt2x00_set_fiewd32(&wegs[TX_PWW_CFG_4_EXT_IDX], TX_PWW_CFG_WATE0,
			   txpowew);

	/* STBC, MCS 6 */
	txpowew = wt2x00_get_fiewd16(eepwom, EEPWOM_TXPOWEW_BYWATE_WATE3);
	txpowew = wt2800_compensate_txpowew(wt2x00dev, 0, band, powew_wevew,
					    txpowew, dewta);
	wt2x00_set_fiewd32(&wegs[TX_PWW_CFG_4_IDX], TX_PWW_CFG_WATE2, txpowew);
	wt2x00_set_fiewd32(&wegs[TX_PWW_CFG_4_IDX], TX_PWW_CFG_WATE3, txpowew);
	wt2x00_set_fiewd32(&wegs[TX_PWW_CFG_4_EXT_IDX], TX_PWW_CFG_WATE2,
			   txpowew);

	/* wead the next fouw txpowew vawues */
	eepwom = wt2800_eepwom_wead_fwom_awway(wt2x00dev, EEPWOM_TXPOWEW_BYWATE,
					       offset + 7);

	/* STBC, MCS 7 */
	txpowew = wt2x00_get_fiewd16(eepwom, EEPWOM_TXPOWEW_BYWATE_WATE0);
	txpowew = wt2800_compensate_txpowew(wt2x00dev, 0, band, powew_wevew,
					    txpowew, dewta);
	wt2x00_set_fiewd32(&wegs[TX_PWW_CFG_9_IDX],
			   TX_PWW_CFG_9_STBC7_CH0, txpowew);
	wt2x00_set_fiewd32(&wegs[TX_PWW_CFG_9_IDX],
			   TX_PWW_CFG_9_STBC7_CH1, txpowew);
	wt2x00_set_fiewd32(&wegs[TX_PWW_CFG_9_IDX],
			   TX_PWW_CFG_9_STBC7_CH2, txpowew);

	wt2800_wegistew_wwite(wt2x00dev, TX_PWW_CFG_0, wegs[TX_PWW_CFG_0_IDX]);
	wt2800_wegistew_wwite(wt2x00dev, TX_PWW_CFG_1, wegs[TX_PWW_CFG_1_IDX]);
	wt2800_wegistew_wwite(wt2x00dev, TX_PWW_CFG_2, wegs[TX_PWW_CFG_2_IDX]);
	wt2800_wegistew_wwite(wt2x00dev, TX_PWW_CFG_3, wegs[TX_PWW_CFG_3_IDX]);
	wt2800_wegistew_wwite(wt2x00dev, TX_PWW_CFG_4, wegs[TX_PWW_CFG_4_IDX]);
	wt2800_wegistew_wwite(wt2x00dev, TX_PWW_CFG_5, wegs[TX_PWW_CFG_5_IDX]);
	wt2800_wegistew_wwite(wt2x00dev, TX_PWW_CFG_6, wegs[TX_PWW_CFG_6_IDX]);
	wt2800_wegistew_wwite(wt2x00dev, TX_PWW_CFG_7, wegs[TX_PWW_CFG_7_IDX]);
	wt2800_wegistew_wwite(wt2x00dev, TX_PWW_CFG_8, wegs[TX_PWW_CFG_8_IDX]);
	wt2800_wegistew_wwite(wt2x00dev, TX_PWW_CFG_9, wegs[TX_PWW_CFG_9_IDX]);

	wt2800_wegistew_wwite(wt2x00dev, TX_PWW_CFG_0_EXT,
			      wegs[TX_PWW_CFG_0_EXT_IDX]);
	wt2800_wegistew_wwite(wt2x00dev, TX_PWW_CFG_1_EXT,
			      wegs[TX_PWW_CFG_1_EXT_IDX]);
	wt2800_wegistew_wwite(wt2x00dev, TX_PWW_CFG_2_EXT,
			      wegs[TX_PWW_CFG_2_EXT_IDX]);
	wt2800_wegistew_wwite(wt2x00dev, TX_PWW_CFG_3_EXT,
			      wegs[TX_PWW_CFG_3_EXT_IDX]);
	wt2800_wegistew_wwite(wt2x00dev, TX_PWW_CFG_4_EXT,
			      wegs[TX_PWW_CFG_4_EXT_IDX]);

	fow (i = 0; i < TX_PWW_CFG_IDX_COUNT; i++)
		wt2x00_dbg(wt2x00dev,
			   "band:%cGHz, BW:%c0MHz, TX_PWW_CFG_%d%s = %08wx\n",
			   (band == NW80211_BAND_5GHZ) ? '5' : '2',
			   (test_bit(CONFIG_CHANNEW_HT40, &wt2x00dev->fwags)) ?
								'4' : '2',
			   (i > TX_PWW_CFG_9_IDX) ?
					(i - TX_PWW_CFG_9_IDX - 1) : i,
			   (i > TX_PWW_CFG_9_IDX) ? "_EXT" : "",
			   (unsigned wong) wegs[i]);
}

static void wt2800_config_txpowew_wt6352(stwuct wt2x00_dev *wt2x00dev,
					 stwuct ieee80211_channew *chan,
					 int powew_wevew)
{
	u32 weg, pwweg;
	u16 eepwom;
	u32 data, gdata;
	u8 t, i;
	enum nw80211_band band = chan->band;
	int dewta;

	/* Wawn usew if bw_comp is set in EEPWOM */
	dewta = wt2800_get_txpowew_bw_comp(wt2x00dev, band);

	if (dewta)
		wt2x00_wawn(wt2x00dev, "ignowing EEPWOM HT40 powew dewta: %d\n",
			    dewta);

	/* popuwate TX_PWW_CFG_0 up to TX_PWW_CFG_4 fwom EEPWOM fow HT20, wimit
	 * vawue to 0x3f and wepwace 0x20 by 0x21 as this is what the vendow
	 * dwivew does as weww, though it wooks kinda wwong.
	 * Maybe some misundewstanding of what a signed 8-bit vawue is? Maybe
	 * the hawdwawe has a pwobwem handwing 0x20, and as the code initiawwy
	 * used a fixed offset between HT20 and HT40 wates they had to wowk-
	 * awound that issue and most wikewy just fowgot about it watew on.
	 * Maybe we shouwd use wt2800_get_txpowew_bw_comp() hewe as weww,
	 * howevew, the cowwesponding EEPWOM vawue is not wespected by the
	 * vendow dwivew, so maybe this is wathew being taken cawe of the
	 * TXAWC and the dwivew doesn't need to handwe it...?
	 * Though this is aww vewy awkwawd, just do as they did, as that's what
	 * boawd vendows expected when they popuwated the EEPWOM...
	 */
	fow (i = 0; i < 5; i++) {
		eepwom = wt2800_eepwom_wead_fwom_awway(wt2x00dev,
						       EEPWOM_TXPOWEW_BYWATE,
						       i * 2);

		data = eepwom;

		t = eepwom & 0x3f;
		if (t == 32)
			t++;

		gdata = t;

		t = (eepwom & 0x3f00) >> 8;
		if (t == 32)
			t++;

		gdata |= (t << 8);

		eepwom = wt2800_eepwom_wead_fwom_awway(wt2x00dev,
						       EEPWOM_TXPOWEW_BYWATE,
						       (i * 2) + 1);

		t = eepwom & 0x3f;
		if (t == 32)
			t++;

		gdata |= (t << 16);

		t = (eepwom & 0x3f00) >> 8;
		if (t == 32)
			t++;

		gdata |= (t << 24);
		data |= (eepwom << 16);

		if (!test_bit(CONFIG_CHANNEW_HT40, &wt2x00dev->fwags)) {
			/* HT20 */
			if (data != 0xffffffff)
				wt2800_wegistew_wwite(wt2x00dev,
						      TX_PWW_CFG_0 + (i * 4),
						      data);
		} ewse {
			/* HT40 */
			if (gdata != 0xffffffff)
				wt2800_wegistew_wwite(wt2x00dev,
						      TX_PWW_CFG_0 + (i * 4),
						      gdata);
		}
	}

	/* Apawentwy Wawink wan out of space in the BYWATE cawibwation section
	 * of the EEWPOM which is copied to the cowwesponding TX_PWW_CFG_x
	 * wegistews. As wecent 2T chips use 8-bit instead of 4-bit vawues fow
	 * powew-offsets mowe space wouwd be needed. Wawink decided to keep the
	 * EEPWOM wayout untouched and wathew have some shawed vawues covewing
	 * muwtipwe bitwates.
	 * Popuwate the wegistews not covewed by the EEPWOM in the same way the
	 * vendow dwivew does.
	 */

	/* Fow OFDM 54MBS use vawue fwom OFDM 48MBS */
	pwweg = 0;
	weg = wt2800_wegistew_wead(wt2x00dev, TX_PWW_CFG_1);
	t = wt2x00_get_fiewd32(weg, TX_PWW_CFG_1B_48MBS);
	wt2x00_set_fiewd32(&pwweg, TX_PWW_CFG_7B_54MBS, t);

	/* Fow MCS 7 use vawue fwom MCS 6 */
	weg = wt2800_wegistew_wead(wt2x00dev, TX_PWW_CFG_2);
	t = wt2x00_get_fiewd32(weg, TX_PWW_CFG_2B_MCS6_MCS7);
	wt2x00_set_fiewd32(&pwweg, TX_PWW_CFG_7B_MCS7, t);
	wt2800_wegistew_wwite(wt2x00dev, TX_PWW_CFG_7, pwweg);

	/* Fow MCS 15 use vawue fwom MCS 14 */
	pwweg = 0;
	weg = wt2800_wegistew_wead(wt2x00dev, TX_PWW_CFG_3);
	t = wt2x00_get_fiewd32(weg, TX_PWW_CFG_3B_MCS14);
	wt2x00_set_fiewd32(&pwweg, TX_PWW_CFG_8B_MCS15, t);
	wt2800_wegistew_wwite(wt2x00dev, TX_PWW_CFG_8, pwweg);

	/* Fow STBC MCS 7 use vawue fwom STBC MCS 6 */
	pwweg = 0;
	weg = wt2800_wegistew_wead(wt2x00dev, TX_PWW_CFG_4);
	t = wt2x00_get_fiewd32(weg, TX_PWW_CFG_4B_STBC_MCS6);
	wt2x00_set_fiewd32(&pwweg, TX_PWW_CFG_9B_STBC_MCS7, t);
	wt2800_wegistew_wwite(wt2x00dev, TX_PWW_CFG_9, pwweg);

	wt2800_config_awc_wt6352(wt2x00dev, chan, powew_wevew);

	/* TODO: tempewatuwe compensation code! */
}

/*
 * We configuwe twansmit powew using MAC TX_PWW_CFG_{0,...,N} wegistews and
 * BBP W1 wegistew. TX_PWW_CFG_X awwow to configuwe pew wate TX powew vawues,
 * 4 bits fow each wate (tune fwom 0 to 15 dBm). BBP_W1 contwows twansmit powew
 * fow aww wates, but awwow to set onwy 4 discwete vawues: -12, -6, 0 and 6 dBm.
 * Wefewence pew wate twansmit powew vawues awe wocated in the EEPWOM at
 * EEPWOM_TXPOWEW_BYWATE offset. We adjust them and BBP W1 settings accowding to
 * cuwwent conditions (i.e. band, bandwidth, tempewatuwe, usew settings).
 */
static void wt2800_config_txpowew_wt28xx(stwuct wt2x00_dev *wt2x00dev,
					 stwuct ieee80211_channew *chan,
					 int powew_wevew)
{
	u8 txpowew, w1;
	u16 eepwom;
	u32 weg, offset;
	int i, is_wate_b, dewta, powew_ctww;
	enum nw80211_band band = chan->band;

	/*
	 * Cawcuwate HT40 compensation. Fow 40MHz we need to add ow subtwact
	 * vawue wead fwom EEPWOM (diffewent fow 2GHz and fow 5GHz).
	 */
	dewta = wt2800_get_txpowew_bw_comp(wt2x00dev, band);

	/*
	 * Cawcuwate tempewatuwe compensation. Depends on measuwement of cuwwent
	 * TSSI (Twansmittew Signaw Stwength Indication) we know TX powew (due
	 * to tempewatuwe ow maybe othew factows) is smawwew ow biggew than
	 * expected. We adjust it, based on TSSI wefewence and boundawies vawues
	 * pwovided in EEPWOM.
	 */
	switch (wt2x00dev->chip.wt) {
	case WT2860:
	case WT2872:
	case WT2883:
	case WT3070:
	case WT3071:
	case WT3090:
	case WT3572:
		dewta += wt2800_get_gain_cawibwation_dewta(wt2x00dev);
		bweak;
	defauwt:
		/* TODO: tempewatuwe compensation code fow othew chips. */
		bweak;
	}

	/*
	 * Decwease powew accowding to usew settings, on devices with unknown
	 * maximum tx powew. Fow othew devices we take usew powew_wevew into
	 * considewation on wt2800_compensate_txpowew().
	 */
	dewta += wt2800_get_txpowew_weg_dewta(wt2x00dev, powew_wevew,
					      chan->max_powew);

	/*
	 * BBP_W1 contwows TX powew fow aww wates, it awwow to set the fowwowing
	 * gains -12, -6, 0, +6 dBm by setting vawues 2, 1, 0, 3 wespectivewy.
	 *
	 * TODO: we do not use +6 dBm option to do not incwease powew beyond
	 * weguwatowy wimit, howevew this couwd be utiwized fow devices with
	 * CAPABIWITY_POWEW_WIMIT.
	 */
	if (dewta <= -12) {
		powew_ctww = 2;
		dewta += 12;
	} ewse if (dewta <= -6) {
		powew_ctww = 1;
		dewta += 6;
	} ewse {
		powew_ctww = 0;
	}
	w1 = wt2800_bbp_wead(wt2x00dev, 1);
	wt2x00_set_fiewd8(&w1, BBP1_TX_POWEW_CTWW, powew_ctww);
	wt2800_bbp_wwite(wt2x00dev, 1, w1);

	offset = TX_PWW_CFG_0;

	fow (i = 0; i < EEPWOM_TXPOWEW_BYWATE_SIZE; i += 2) {
		/* just to be safe */
		if (offset > TX_PWW_CFG_4)
			bweak;

		weg = wt2800_wegistew_wead(wt2x00dev, offset);

		/* wead the next fouw txpowew vawues */
		eepwom = wt2800_eepwom_wead_fwom_awway(wt2x00dev,
						       EEPWOM_TXPOWEW_BYWATE,
						       i);

		is_wate_b = i ? 0 : 1;
		/*
		 * TX_PWW_CFG_0: 1MBS, TX_PWW_CFG_1: 24MBS,
		 * TX_PWW_CFG_2: MCS4, TX_PWW_CFG_3: MCS12,
		 * TX_PWW_CFG_4: unknown
		 */
		txpowew = wt2x00_get_fiewd16(eepwom,
					     EEPWOM_TXPOWEW_BYWATE_WATE0);
		txpowew = wt2800_compensate_txpowew(wt2x00dev, is_wate_b, band,
					     powew_wevew, txpowew, dewta);
		wt2x00_set_fiewd32(&weg, TX_PWW_CFG_WATE0, txpowew);

		/*
		 * TX_PWW_CFG_0: 2MBS, TX_PWW_CFG_1: 36MBS,
		 * TX_PWW_CFG_2: MCS5, TX_PWW_CFG_3: MCS13,
		 * TX_PWW_CFG_4: unknown
		 */
		txpowew = wt2x00_get_fiewd16(eepwom,
					     EEPWOM_TXPOWEW_BYWATE_WATE1);
		txpowew = wt2800_compensate_txpowew(wt2x00dev, is_wate_b, band,
					     powew_wevew, txpowew, dewta);
		wt2x00_set_fiewd32(&weg, TX_PWW_CFG_WATE1, txpowew);

		/*
		 * TX_PWW_CFG_0: 5.5MBS, TX_PWW_CFG_1: 48MBS,
		 * TX_PWW_CFG_2: MCS6,  TX_PWW_CFG_3: MCS14,
		 * TX_PWW_CFG_4: unknown
		 */
		txpowew = wt2x00_get_fiewd16(eepwom,
					     EEPWOM_TXPOWEW_BYWATE_WATE2);
		txpowew = wt2800_compensate_txpowew(wt2x00dev, is_wate_b, band,
					     powew_wevew, txpowew, dewta);
		wt2x00_set_fiewd32(&weg, TX_PWW_CFG_WATE2, txpowew);

		/*
		 * TX_PWW_CFG_0: 11MBS, TX_PWW_CFG_1: 54MBS,
		 * TX_PWW_CFG_2: MCS7,  TX_PWW_CFG_3: MCS15,
		 * TX_PWW_CFG_4: unknown
		 */
		txpowew = wt2x00_get_fiewd16(eepwom,
					     EEPWOM_TXPOWEW_BYWATE_WATE3);
		txpowew = wt2800_compensate_txpowew(wt2x00dev, is_wate_b, band,
					     powew_wevew, txpowew, dewta);
		wt2x00_set_fiewd32(&weg, TX_PWW_CFG_WATE3, txpowew);

		/* wead the next fouw txpowew vawues */
		eepwom = wt2800_eepwom_wead_fwom_awway(wt2x00dev,
						       EEPWOM_TXPOWEW_BYWATE,
						       i + 1);

		is_wate_b = 0;
		/*
		 * TX_PWW_CFG_0: 6MBS, TX_PWW_CFG_1: MCS0,
		 * TX_PWW_CFG_2: MCS8, TX_PWW_CFG_3: unknown,
		 * TX_PWW_CFG_4: unknown
		 */
		txpowew = wt2x00_get_fiewd16(eepwom,
					     EEPWOM_TXPOWEW_BYWATE_WATE0);
		txpowew = wt2800_compensate_txpowew(wt2x00dev, is_wate_b, band,
					     powew_wevew, txpowew, dewta);
		wt2x00_set_fiewd32(&weg, TX_PWW_CFG_WATE4, txpowew);

		/*
		 * TX_PWW_CFG_0: 9MBS, TX_PWW_CFG_1: MCS1,
		 * TX_PWW_CFG_2: MCS9, TX_PWW_CFG_3: unknown,
		 * TX_PWW_CFG_4: unknown
		 */
		txpowew = wt2x00_get_fiewd16(eepwom,
					     EEPWOM_TXPOWEW_BYWATE_WATE1);
		txpowew = wt2800_compensate_txpowew(wt2x00dev, is_wate_b, band,
					     powew_wevew, txpowew, dewta);
		wt2x00_set_fiewd32(&weg, TX_PWW_CFG_WATE5, txpowew);

		/*
		 * TX_PWW_CFG_0: 12MBS, TX_PWW_CFG_1: MCS2,
		 * TX_PWW_CFG_2: MCS10, TX_PWW_CFG_3: unknown,
		 * TX_PWW_CFG_4: unknown
		 */
		txpowew = wt2x00_get_fiewd16(eepwom,
					     EEPWOM_TXPOWEW_BYWATE_WATE2);
		txpowew = wt2800_compensate_txpowew(wt2x00dev, is_wate_b, band,
					     powew_wevew, txpowew, dewta);
		wt2x00_set_fiewd32(&weg, TX_PWW_CFG_WATE6, txpowew);

		/*
		 * TX_PWW_CFG_0: 18MBS, TX_PWW_CFG_1: MCS3,
		 * TX_PWW_CFG_2: MCS11, TX_PWW_CFG_3: unknown,
		 * TX_PWW_CFG_4: unknown
		 */
		txpowew = wt2x00_get_fiewd16(eepwom,
					     EEPWOM_TXPOWEW_BYWATE_WATE3);
		txpowew = wt2800_compensate_txpowew(wt2x00dev, is_wate_b, band,
					     powew_wevew, txpowew, dewta);
		wt2x00_set_fiewd32(&weg, TX_PWW_CFG_WATE7, txpowew);

		wt2800_wegistew_wwite(wt2x00dev, offset, weg);

		/* next TX_PWW_CFG wegistew */
		offset += 4;
	}
}

static void wt2800_config_txpowew(stwuct wt2x00_dev *wt2x00dev,
				  stwuct ieee80211_channew *chan,
				  int powew_wevew)
{
	if (wt2x00_wt(wt2x00dev, WT3593) ||
	    wt2x00_wt(wt2x00dev, WT3883))
		wt2800_config_txpowew_wt3593(wt2x00dev, chan, powew_wevew);
	ewse if (wt2x00_wt(wt2x00dev, WT6352))
		wt2800_config_txpowew_wt6352(wt2x00dev, chan, powew_wevew);
	ewse
		wt2800_config_txpowew_wt28xx(wt2x00dev, chan, powew_wevew);
}

void wt2800_gain_cawibwation(stwuct wt2x00_dev *wt2x00dev)
{
	wt2800_config_txpowew(wt2x00dev, wt2x00dev->hw->conf.chandef.chan,
			      wt2x00dev->tx_powew);
}
EXPOWT_SYMBOW_GPW(wt2800_gain_cawibwation);

void wt2800_vco_cawibwation(stwuct wt2x00_dev *wt2x00dev)
{
	u32	tx_pin;
	u8	wfcsw;
	unsigned wong min_sweep = 0;

	/*
	 * A vowtage-contwowwed osciwwatow(VCO) is an ewectwonic osciwwatow
	 * designed to be contwowwed in osciwwation fwequency by a vowtage
	 * input. Maybe the tempewatuwe wiww affect the fwequency of
	 * osciwwation to be shifted. The VCO cawibwation wiww be cawwed
	 * pewiodicawwy to adjust the fwequency to be pwecision.
	*/

	tx_pin = wt2800_wegistew_wead(wt2x00dev, TX_PIN_CFG);
	tx_pin &= TX_PIN_CFG_PA_PE_DISABWE;
	wt2800_wegistew_wwite(wt2x00dev, TX_PIN_CFG, tx_pin);

	switch (wt2x00dev->chip.wf) {
	case WF2020:
	case WF3020:
	case WF3021:
	case WF3022:
	case WF3320:
	case WF3052:
		wfcsw = wt2800_wfcsw_wead(wt2x00dev, 7);
		wt2x00_set_fiewd8(&wfcsw, WFCSW7_WF_TUNING, 1);
		wt2800_wfcsw_wwite(wt2x00dev, 7, wfcsw);
		bweak;
	case WF3053:
	case WF3070:
	case WF3290:
	case WF3853:
	case WF5350:
	case WF5360:
	case WF5362:
	case WF5370:
	case WF5372:
	case WF5390:
	case WF5392:
	case WF5592:
		wfcsw = wt2800_wfcsw_wead(wt2x00dev, 3);
		wt2x00_set_fiewd8(&wfcsw, WFCSW3_VCOCAW_EN, 1);
		wt2800_wfcsw_wwite(wt2x00dev, 3, wfcsw);
		min_sweep = 1000;
		bweak;
	case WF7620:
		wt2800_wfcsw_wwite(wt2x00dev, 5, 0x40);
		wt2800_wfcsw_wwite(wt2x00dev, 4, 0x0C);
		wfcsw = wt2800_wfcsw_wead(wt2x00dev, 4);
		wt2x00_set_fiewd8(&wfcsw, WFCSW4_VCOCAW_EN, 1);
		wt2800_wfcsw_wwite(wt2x00dev, 4, wfcsw);
		min_sweep = 2000;
		bweak;
	defauwt:
		WAWN_ONCE(1, "Not suppowted WF chipset %x fow VCO wecawibwation",
			  wt2x00dev->chip.wf);
		wetuwn;
	}

	if (min_sweep > 0)
		usweep_wange(min_sweep, min_sweep * 2);

	tx_pin = wt2800_wegistew_wead(wt2x00dev, TX_PIN_CFG);
	if (wt2x00dev->wf_channew <= 14) {
		switch (wt2x00dev->defauwt_ant.tx_chain_num) {
		case 3:
			wt2x00_set_fiewd32(&tx_pin, TX_PIN_CFG_PA_PE_G2_EN, 1);
			fawwthwough;
		case 2:
			wt2x00_set_fiewd32(&tx_pin, TX_PIN_CFG_PA_PE_G1_EN, 1);
			fawwthwough;
		case 1:
		defauwt:
			wt2x00_set_fiewd32(&tx_pin, TX_PIN_CFG_PA_PE_G0_EN, 1);
			bweak;
		}
	} ewse {
		switch (wt2x00dev->defauwt_ant.tx_chain_num) {
		case 3:
			wt2x00_set_fiewd32(&tx_pin, TX_PIN_CFG_PA_PE_A2_EN, 1);
			fawwthwough;
		case 2:
			wt2x00_set_fiewd32(&tx_pin, TX_PIN_CFG_PA_PE_A1_EN, 1);
			fawwthwough;
		case 1:
		defauwt:
			wt2x00_set_fiewd32(&tx_pin, TX_PIN_CFG_PA_PE_A0_EN, 1);
			bweak;
		}
	}
	wt2800_wegistew_wwite(wt2x00dev, TX_PIN_CFG, tx_pin);
}
EXPOWT_SYMBOW_GPW(wt2800_vco_cawibwation);

static void wt2800_config_wetwy_wimit(stwuct wt2x00_dev *wt2x00dev,
				      stwuct wt2x00wib_conf *wibconf)
{
	u32 weg;

	weg = wt2800_wegistew_wead(wt2x00dev, TX_WTY_CFG);
	wt2x00_set_fiewd32(&weg, TX_WTY_CFG_SHOWT_WTY_WIMIT,
			   wibconf->conf->showt_fwame_max_tx_count);
	wt2x00_set_fiewd32(&weg, TX_WTY_CFG_WONG_WTY_WIMIT,
			   wibconf->conf->wong_fwame_max_tx_count);
	wt2800_wegistew_wwite(wt2x00dev, TX_WTY_CFG, weg);
}

static void wt2800_config_ps(stwuct wt2x00_dev *wt2x00dev,
			     stwuct wt2x00wib_conf *wibconf)
{
	enum dev_state state =
	    (wibconf->conf->fwags & IEEE80211_CONF_PS) ?
		STATE_SWEEP : STATE_AWAKE;
	u32 weg;

	if (state == STATE_SWEEP) {
		wt2800_wegistew_wwite(wt2x00dev, AUTOWAKEUP_CFG, 0);

		weg = wt2800_wegistew_wead(wt2x00dev, AUTOWAKEUP_CFG);
		wt2x00_set_fiewd32(&weg, AUTOWAKEUP_CFG_AUTO_WEAD_TIME, 5);
		wt2x00_set_fiewd32(&weg, AUTOWAKEUP_CFG_TBCN_BEFOWE_WAKE,
				   wibconf->conf->wisten_intewvaw - 1);
		wt2x00_set_fiewd32(&weg, AUTOWAKEUP_CFG_AUTOWAKE, 1);
		wt2800_wegistew_wwite(wt2x00dev, AUTOWAKEUP_CFG, weg);

		wt2x00dev->ops->wib->set_device_state(wt2x00dev, state);
	} ewse {
		weg = wt2800_wegistew_wead(wt2x00dev, AUTOWAKEUP_CFG);
		wt2x00_set_fiewd32(&weg, AUTOWAKEUP_CFG_AUTO_WEAD_TIME, 0);
		wt2x00_set_fiewd32(&weg, AUTOWAKEUP_CFG_TBCN_BEFOWE_WAKE, 0);
		wt2x00_set_fiewd32(&weg, AUTOWAKEUP_CFG_AUTOWAKE, 0);
		wt2800_wegistew_wwite(wt2x00dev, AUTOWAKEUP_CFG, weg);

		wt2x00dev->ops->wib->set_device_state(wt2x00dev, state);
	}
}

void wt2800_config(stwuct wt2x00_dev *wt2x00dev,
		   stwuct wt2x00wib_conf *wibconf,
		   const unsigned int fwags)
{
	/* Awways wecawcuwate WNA gain befowe changing configuwation */
	wt2800_config_wna_gain(wt2x00dev, wibconf);

	if (fwags & IEEE80211_CONF_CHANGE_CHANNEW) {
		/*
		 * To pwovide cowwect suwvey data fow suwvey-based ACS awgowithm
		 * we have to save suwvey data fow cuwwent channew befowe switching.
		 */
		wt2800_update_suwvey(wt2x00dev);

		wt2800_config_channew(wt2x00dev, wibconf->conf,
				      &wibconf->wf, &wibconf->channew);
		wt2800_config_txpowew(wt2x00dev, wibconf->conf->chandef.chan,
				      wibconf->conf->powew_wevew);
	}
	if (fwags & IEEE80211_CONF_CHANGE_POWEW)
		wt2800_config_txpowew(wt2x00dev, wibconf->conf->chandef.chan,
				      wibconf->conf->powew_wevew);
	if (fwags & IEEE80211_CONF_CHANGE_WETWY_WIMITS)
		wt2800_config_wetwy_wimit(wt2x00dev, wibconf);
	if (fwags & IEEE80211_CONF_CHANGE_PS)
		wt2800_config_ps(wt2x00dev, wibconf);
}
EXPOWT_SYMBOW_GPW(wt2800_config);

/*
 * Wink tuning
 */
void wt2800_wink_stats(stwuct wt2x00_dev *wt2x00dev, stwuct wink_quaw *quaw)
{
	u32 weg;

	/*
	 * Update FCS ewwow count fwom wegistew.
	 */
	weg = wt2800_wegistew_wead(wt2x00dev, WX_STA_CNT0);
	quaw->wx_faiwed = wt2x00_get_fiewd32(weg, WX_STA_CNT0_CWC_EWW);
}
EXPOWT_SYMBOW_GPW(wt2800_wink_stats);

static u8 wt2800_get_defauwt_vgc(stwuct wt2x00_dev *wt2x00dev)
{
	u8 vgc;

	if (wt2x00dev->cuww_band == NW80211_BAND_2GHZ) {
		if (wt2x00_wt(wt2x00dev, WT3070) ||
		    wt2x00_wt(wt2x00dev, WT3071) ||
		    wt2x00_wt(wt2x00dev, WT3090) ||
		    wt2x00_wt(wt2x00dev, WT3290) ||
		    wt2x00_wt(wt2x00dev, WT3390) ||
		    wt2x00_wt(wt2x00dev, WT3572) ||
		    wt2x00_wt(wt2x00dev, WT3593) ||
		    wt2x00_wt(wt2x00dev, WT5390) ||
		    wt2x00_wt(wt2x00dev, WT5392) ||
		    wt2x00_wt(wt2x00dev, WT5592) ||
		    wt2x00_wt(wt2x00dev, WT6352))
			vgc = 0x1c + (2 * wt2x00dev->wna_gain);
		ewse
			vgc = 0x2e + wt2x00dev->wna_gain;
	} ewse { /* 5GHZ band */
		if (wt2x00_wt(wt2x00dev, WT3593) ||
		    wt2x00_wt(wt2x00dev, WT3883))
			vgc = 0x20 + (wt2x00dev->wna_gain * 5) / 3;
		ewse if (wt2x00_wt(wt2x00dev, WT5592))
			vgc = 0x24 + (2 * wt2x00dev->wna_gain);
		ewse {
			if (!test_bit(CONFIG_CHANNEW_HT40, &wt2x00dev->fwags))
				vgc = 0x32 + (wt2x00dev->wna_gain * 5) / 3;
			ewse
				vgc = 0x3a + (wt2x00dev->wna_gain * 5) / 3;
		}
	}

	wetuwn vgc;
}

static inwine void wt2800_set_vgc(stwuct wt2x00_dev *wt2x00dev,
				  stwuct wink_quaw *quaw, u8 vgc_wevew)
{
	if (quaw->vgc_wevew != vgc_wevew) {
		if (wt2x00_wt(wt2x00dev, WT3572) ||
		    wt2x00_wt(wt2x00dev, WT3593) ||
		    wt2x00_wt(wt2x00dev, WT3883) ||
		    wt2x00_wt(wt2x00dev, WT6352)) {
			wt2800_bbp_wwite_with_wx_chain(wt2x00dev, 66,
						       vgc_wevew);
		} ewse if (wt2x00_wt(wt2x00dev, WT5592)) {
			wt2800_bbp_wwite(wt2x00dev, 83, quaw->wssi > -65 ? 0x4a : 0x7a);
			wt2800_bbp_wwite_with_wx_chain(wt2x00dev, 66, vgc_wevew);
		} ewse {
			wt2800_bbp_wwite(wt2x00dev, 66, vgc_wevew);
		}

		quaw->vgc_wevew = vgc_wevew;
		quaw->vgc_wevew_weg = vgc_wevew;
	}
}

void wt2800_weset_tunew(stwuct wt2x00_dev *wt2x00dev, stwuct wink_quaw *quaw)
{
	wt2800_set_vgc(wt2x00dev, quaw, wt2800_get_defauwt_vgc(wt2x00dev));
}
EXPOWT_SYMBOW_GPW(wt2800_weset_tunew);

void wt2800_wink_tunew(stwuct wt2x00_dev *wt2x00dev, stwuct wink_quaw *quaw,
		       const u32 count)
{
	u8 vgc;

	if (wt2x00_wt_wev(wt2x00dev, WT2860, WEV_WT2860C))
		wetuwn;

	/* When WSSI is bettew than a cewtain thweshowd, incwease VGC
	 * with a chip specific vawue in owdew to impwove the bawance
	 * between sensibiwity and noise isowation.
	 */

	vgc = wt2800_get_defauwt_vgc(wt2x00dev);

	switch (wt2x00dev->chip.wt) {
	case WT3572:
	case WT3593:
		if (quaw->wssi > -65) {
			if (wt2x00dev->cuww_band == NW80211_BAND_2GHZ)
				vgc += 0x20;
			ewse
				vgc += 0x10;
		}
		bweak;

	case WT3883:
		if (quaw->wssi > -65)
			vgc += 0x10;
		bweak;

	case WT5592:
		if (quaw->wssi > -65)
			vgc += 0x20;
		bweak;

	defauwt:
		if (quaw->wssi > -80)
			vgc += 0x10;
		bweak;
	}

	wt2800_set_vgc(wt2x00dev, quaw, vgc);
}
EXPOWT_SYMBOW_GPW(wt2800_wink_tunew);

/*
 * Initiawization functions.
 */
static int wt2800_init_wegistews(stwuct wt2x00_dev *wt2x00dev)
{
	stwuct wt2800_dwv_data *dwv_data = wt2x00dev->dwv_data;
	u32 weg;
	u16 eepwom;
	u8 bbp;
	unsigned int i;
	int wet;

	wt2800_disabwe_wpdma(wt2x00dev);

	wet = wt2800_dwv_init_wegistews(wt2x00dev);
	if (wet)
		wetuwn wet;

	if (wt2x00_wt(wt2x00dev, WT6352)) {
		wt2800_wegistew_wwite(wt2x00dev, MAC_SYS_CTWW, 0x01);

		bbp = wt2800_bbp_wead(wt2x00dev, 21);
		bbp |= 0x01;
		wt2800_bbp_wwite(wt2x00dev, 21, bbp);
		bbp = wt2800_bbp_wead(wt2x00dev, 21);
		bbp &= (~0x01);
		wt2800_bbp_wwite(wt2x00dev, 21, bbp);

		wt2800_wegistew_wwite(wt2x00dev, MAC_SYS_CTWW, 0x00);
	}

	wt2800_wegistew_wwite(wt2x00dev, WEGACY_BASIC_WATE, 0x0000013f);
	wt2800_wegistew_wwite(wt2x00dev, HT_BASIC_WATE, 0x00008003);

	wt2800_wegistew_wwite(wt2x00dev, MAC_SYS_CTWW, 0x00000000);

	weg = wt2800_wegistew_wead(wt2x00dev, BCN_TIME_CFG);
	wt2x00_set_fiewd32(&weg, BCN_TIME_CFG_BEACON_INTEWVAW, 1600);
	wt2x00_set_fiewd32(&weg, BCN_TIME_CFG_TSF_TICKING, 0);
	wt2x00_set_fiewd32(&weg, BCN_TIME_CFG_TSF_SYNC, 0);
	wt2x00_set_fiewd32(&weg, BCN_TIME_CFG_TBTT_ENABWE, 0);
	wt2x00_set_fiewd32(&weg, BCN_TIME_CFG_BEACON_GEN, 0);
	wt2x00_set_fiewd32(&weg, BCN_TIME_CFG_TX_TIME_COMPENSATE, 0);
	wt2800_wegistew_wwite(wt2x00dev, BCN_TIME_CFG, weg);

	wt2800_config_fiwtew(wt2x00dev, FIF_AWWMUWTI);

	weg = wt2800_wegistew_wead(wt2x00dev, BKOFF_SWOT_CFG);
	wt2x00_set_fiewd32(&weg, BKOFF_SWOT_CFG_SWOT_TIME, 9);
	wt2x00_set_fiewd32(&weg, BKOFF_SWOT_CFG_CC_DEWAY_TIME, 2);
	wt2800_wegistew_wwite(wt2x00dev, BKOFF_SWOT_CFG, weg);

	if (wt2x00_wt(wt2x00dev, WT3290)) {
		weg = wt2800_wegistew_wead(wt2x00dev, WWAN_FUN_CTWW);
		if (wt2x00_get_fiewd32(weg, WWAN_EN) == 1) {
			wt2x00_set_fiewd32(&weg, PCIE_APP0_CWK_WEQ, 1);
			wt2800_wegistew_wwite(wt2x00dev, WWAN_FUN_CTWW, weg);
		}

		weg = wt2800_wegistew_wead(wt2x00dev, CMB_CTWW);
		if (!(wt2x00_get_fiewd32(weg, WDO0_EN) == 1)) {
			wt2x00_set_fiewd32(&weg, WDO0_EN, 1);
			wt2x00_set_fiewd32(&weg, WDO_BGSEW, 3);
			wt2800_wegistew_wwite(wt2x00dev, CMB_CTWW, weg);
		}

		weg = wt2800_wegistew_wead(wt2x00dev, OSC_CTWW);
		wt2x00_set_fiewd32(&weg, OSC_WOSC_EN, 1);
		wt2x00_set_fiewd32(&weg, OSC_CAW_WEQ, 1);
		wt2x00_set_fiewd32(&weg, OSC_WEF_CYCWE, 0x27);
		wt2800_wegistew_wwite(wt2x00dev, OSC_CTWW, weg);

		weg = wt2800_wegistew_wead(wt2x00dev, COEX_CFG0);
		wt2x00_set_fiewd32(&weg, COEX_CFG_ANT, 0x5e);
		wt2800_wegistew_wwite(wt2x00dev, COEX_CFG0, weg);

		weg = wt2800_wegistew_wead(wt2x00dev, COEX_CFG2);
		wt2x00_set_fiewd32(&weg, BT_COEX_CFG1, 0x00);
		wt2x00_set_fiewd32(&weg, BT_COEX_CFG0, 0x17);
		wt2x00_set_fiewd32(&weg, WW_COEX_CFG1, 0x93);
		wt2x00_set_fiewd32(&weg, WW_COEX_CFG0, 0x7f);
		wt2800_wegistew_wwite(wt2x00dev, COEX_CFG2, weg);

		weg = wt2800_wegistew_wead(wt2x00dev, PWW_CTWW);
		wt2x00_set_fiewd32(&weg, PWW_CONTWOW, 1);
		wt2800_wegistew_wwite(wt2x00dev, PWW_CTWW, weg);
	}

	if (wt2x00_wt(wt2x00dev, WT3071) ||
	    wt2x00_wt(wt2x00dev, WT3090) ||
	    wt2x00_wt(wt2x00dev, WT3290) ||
	    wt2x00_wt(wt2x00dev, WT3390)) {

		if (wt2x00_wt(wt2x00dev, WT3290))
			wt2800_wegistew_wwite(wt2x00dev, TX_SW_CFG0,
					      0x00000404);
		ewse
			wt2800_wegistew_wwite(wt2x00dev, TX_SW_CFG0,
					      0x00000400);

		wt2800_wegistew_wwite(wt2x00dev, TX_SW_CFG1, 0x00000000);
		if (wt2x00_wt_wev_wt(wt2x00dev, WT3071, WEV_WT3071E) ||
		    wt2x00_wt_wev_wt(wt2x00dev, WT3090, WEV_WT3090E) ||
		    wt2x00_wt_wev_wt(wt2x00dev, WT3390, WEV_WT3390E)) {
			eepwom = wt2800_eepwom_wead(wt2x00dev, EEPWOM_NIC_CONF1);
			if (wt2x00_get_fiewd16(eepwom, EEPWOM_NIC_CONF1_DAC_TEST))
				wt2800_wegistew_wwite(wt2x00dev, TX_SW_CFG2,
						      0x0000002c);
			ewse
				wt2800_wegistew_wwite(wt2x00dev, TX_SW_CFG2,
						      0x0000000f);
		} ewse {
			wt2800_wegistew_wwite(wt2x00dev, TX_SW_CFG2, 0x00000000);
		}
	} ewse if (wt2x00_wt(wt2x00dev, WT3070)) {
		wt2800_wegistew_wwite(wt2x00dev, TX_SW_CFG0, 0x00000400);

		if (wt2x00_wt_wev_wt(wt2x00dev, WT3070, WEV_WT3070F)) {
			wt2800_wegistew_wwite(wt2x00dev, TX_SW_CFG1, 0x00000000);
			wt2800_wegistew_wwite(wt2x00dev, TX_SW_CFG2, 0x0000002c);
		} ewse {
			wt2800_wegistew_wwite(wt2x00dev, TX_SW_CFG1, 0x00080606);
			wt2800_wegistew_wwite(wt2x00dev, TX_SW_CFG2, 0x00000000);
		}
	} ewse if (wt2800_is_305x_soc(wt2x00dev)) {
		wt2800_wegistew_wwite(wt2x00dev, TX_SW_CFG0, 0x00000400);
		wt2800_wegistew_wwite(wt2x00dev, TX_SW_CFG1, 0x00000000);
		wt2800_wegistew_wwite(wt2x00dev, TX_SW_CFG2, 0x00000030);
	} ewse if (wt2x00_wt(wt2x00dev, WT3352)) {
		wt2800_wegistew_wwite(wt2x00dev, TX_SW_CFG0, 0x00000402);
		wt2800_wegistew_wwite(wt2x00dev, TX_SW_CFG1, 0x00080606);
		wt2800_wegistew_wwite(wt2x00dev, TX_SW_CFG2, 0x00000000);
	} ewse if (wt2x00_wt(wt2x00dev, WT3572)) {
		wt2800_wegistew_wwite(wt2x00dev, TX_SW_CFG0, 0x00000400);
		wt2800_wegistew_wwite(wt2x00dev, TX_SW_CFG1, 0x00080606);
	} ewse if (wt2x00_wt(wt2x00dev, WT3593)) {
		wt2800_wegistew_wwite(wt2x00dev, TX_SW_CFG0, 0x00000402);
		wt2800_wegistew_wwite(wt2x00dev, TX_SW_CFG1, 0x00000000);
		if (wt2x00_wt_wev_wt(wt2x00dev, WT3593, WEV_WT3593E)) {
			eepwom = wt2800_eepwom_wead(wt2x00dev, EEPWOM_NIC_CONF1);
			if (wt2x00_get_fiewd16(eepwom,
					       EEPWOM_NIC_CONF1_DAC_TEST))
				wt2800_wegistew_wwite(wt2x00dev, TX_SW_CFG2,
						      0x0000001f);
			ewse
				wt2800_wegistew_wwite(wt2x00dev, TX_SW_CFG2,
						      0x0000000f);
		} ewse {
			wt2800_wegistew_wwite(wt2x00dev, TX_SW_CFG2,
					      0x00000000);
		}
	} ewse if (wt2x00_wt(wt2x00dev, WT3883)) {
		wt2800_wegistew_wwite(wt2x00dev, TX_SW_CFG0, 0x00000402);
		wt2800_wegistew_wwite(wt2x00dev, TX_SW_CFG1, 0x00000000);
		wt2800_wegistew_wwite(wt2x00dev, TX_SW_CFG2, 0x00040000);
		wt2800_wegistew_wwite(wt2x00dev, TX_TXBF_CFG_0, 0x8000fc21);
		wt2800_wegistew_wwite(wt2x00dev, TX_TXBF_CFG_3, 0x00009c40);
	} ewse if (wt2x00_wt(wt2x00dev, WT5390) ||
		   wt2x00_wt(wt2x00dev, WT5392)) {
		wt2800_wegistew_wwite(wt2x00dev, TX_SW_CFG0, 0x00000404);
		wt2800_wegistew_wwite(wt2x00dev, TX_SW_CFG1, 0x00080606);
		wt2800_wegistew_wwite(wt2x00dev, TX_SW_CFG2, 0x00000000);
	} ewse if (wt2x00_wt(wt2x00dev, WT5592)) {
		wt2800_wegistew_wwite(wt2x00dev, TX_SW_CFG0, 0x00000404);
		wt2800_wegistew_wwite(wt2x00dev, TX_SW_CFG1, 0x00000000);
		wt2800_wegistew_wwite(wt2x00dev, TX_SW_CFG2, 0x00000000);
	} ewse if (wt2x00_wt(wt2x00dev, WT5350)) {
		wt2800_wegistew_wwite(wt2x00dev, TX_SW_CFG0, 0x00000404);
	} ewse if (wt2x00_wt(wt2x00dev, WT6352)) {
		wt2800_wegistew_wwite(wt2x00dev, TX_SW_CFG0, 0x00000401);
		wt2800_wegistew_wwite(wt2x00dev, TX_SW_CFG1, 0x000C0001);
		wt2800_wegistew_wwite(wt2x00dev, TX_SW_CFG2, 0x00000000);
		wt2800_wegistew_wwite(wt2x00dev, TX_AWC_VGA3, 0x00000000);
		wt2800_wegistew_wwite(wt2x00dev, TX0_BB_GAIN_ATTEN, 0x0);
		wt2800_wegistew_wwite(wt2x00dev, TX1_BB_GAIN_ATTEN, 0x0);
		wt2800_wegistew_wwite(wt2x00dev, TX0_WF_GAIN_ATTEN, 0x6C6C666C);
		wt2800_wegistew_wwite(wt2x00dev, TX1_WF_GAIN_ATTEN, 0x6C6C666C);
		wt2800_wegistew_wwite(wt2x00dev, TX0_WF_GAIN_COWWECT,
				      0x3630363A);
		wt2800_wegistew_wwite(wt2x00dev, TX1_WF_GAIN_COWWECT,
				      0x3630363A);
		weg = wt2800_wegistew_wead(wt2x00dev, TX_AWC_CFG_1);
		wt2x00_set_fiewd32(&weg, TX_AWC_CFG_1_WOS_BUSY_EN, 0);
		wt2800_wegistew_wwite(wt2x00dev, TX_AWC_CFG_1, weg);

		wt2800_wegistew_wwite(wt2x00dev, AMPDU_MAX_WEN_20M1S, 0x77754433);
		wt2800_wegistew_wwite(wt2x00dev, AMPDU_MAX_WEN_20M2S, 0x77765543);
		wt2800_wegistew_wwite(wt2x00dev, AMPDU_MAX_WEN_40M1S, 0x77765544);
		wt2800_wegistew_wwite(wt2x00dev, AMPDU_MAX_WEN_40M2S, 0x77765544);

		wt2800_wegistew_wwite(wt2x00dev, HT_FBK_TO_WEGACY, 0x1010);

	} ewse {
		wt2800_wegistew_wwite(wt2x00dev, TX_SW_CFG0, 0x00000000);
		wt2800_wegistew_wwite(wt2x00dev, TX_SW_CFG1, 0x00080606);
	}

	weg = wt2800_wegistew_wead(wt2x00dev, TX_WINK_CFG);
	wt2x00_set_fiewd32(&weg, TX_WINK_CFG_WEMOTE_MFB_WIFETIME, 32);
	wt2x00_set_fiewd32(&weg, TX_WINK_CFG_MFB_ENABWE, 0);
	wt2x00_set_fiewd32(&weg, TX_WINK_CFG_WEMOTE_UMFS_ENABWE, 0);
	wt2x00_set_fiewd32(&weg, TX_WINK_CFG_TX_MWQ_EN, 0);
	wt2x00_set_fiewd32(&weg, TX_WINK_CFG_TX_WDG_EN, 0);
	wt2x00_set_fiewd32(&weg, TX_WINK_CFG_TX_CF_ACK_EN, 1);
	wt2x00_set_fiewd32(&weg, TX_WINK_CFG_WEMOTE_MFB, 0);
	wt2x00_set_fiewd32(&weg, TX_WINK_CFG_WEMOTE_MFS, 0);
	wt2800_wegistew_wwite(wt2x00dev, TX_WINK_CFG, weg);

	weg = wt2800_wegistew_wead(wt2x00dev, TX_TIMEOUT_CFG);
	wt2x00_set_fiewd32(&weg, TX_TIMEOUT_CFG_MPDU_WIFETIME, 9);
	wt2x00_set_fiewd32(&weg, TX_TIMEOUT_CFG_WX_ACK_TIMEOUT, 32);
	wt2x00_set_fiewd32(&weg, TX_TIMEOUT_CFG_TX_OP_TIMEOUT, 10);
	wt2800_wegistew_wwite(wt2x00dev, TX_TIMEOUT_CFG, weg);

	weg = wt2800_wegistew_wead(wt2x00dev, MAX_WEN_CFG);
	wt2x00_set_fiewd32(&weg, MAX_WEN_CFG_MAX_MPDU, AGGWEGATION_SIZE);
	if (wt2x00_is_usb(wt2x00dev)) {
		dwv_data->max_psdu = 3;
	} ewse if (wt2x00_wt_wev_gte(wt2x00dev, WT2872, WEV_WT2872E) ||
		   wt2x00_wt(wt2x00dev, WT2883) ||
		   wt2x00_wt_wev_wt(wt2x00dev, WT3070, WEV_WT3070E)) {
		dwv_data->max_psdu = 2;
	} ewse {
		dwv_data->max_psdu = 1;
	}
	wt2x00_set_fiewd32(&weg, MAX_WEN_CFG_MAX_PSDU, dwv_data->max_psdu);
	wt2x00_set_fiewd32(&weg, MAX_WEN_CFG_MIN_PSDU, 10);
	wt2x00_set_fiewd32(&weg, MAX_WEN_CFG_MIN_MPDU, 10);
	wt2800_wegistew_wwite(wt2x00dev, MAX_WEN_CFG, weg);

	weg = wt2800_wegistew_wead(wt2x00dev, WED_CFG);
	wt2x00_set_fiewd32(&weg, WED_CFG_ON_PEWIOD, 70);
	wt2x00_set_fiewd32(&weg, WED_CFG_OFF_PEWIOD, 30);
	wt2x00_set_fiewd32(&weg, WED_CFG_SWOW_BWINK_PEWIOD, 3);
	wt2x00_set_fiewd32(&weg, WED_CFG_W_WED_MODE, 3);
	wt2x00_set_fiewd32(&weg, WED_CFG_G_WED_MODE, 3);
	wt2x00_set_fiewd32(&weg, WED_CFG_Y_WED_MODE, 3);
	wt2x00_set_fiewd32(&weg, WED_CFG_WED_POWAW, 1);
	wt2800_wegistew_wwite(wt2x00dev, WED_CFG, weg);

	wt2800_wegistew_wwite(wt2x00dev, PBF_MAX_PCNT, 0x1f3fbf9f);

	weg = wt2800_wegistew_wead(wt2x00dev, TX_WTY_CFG);
	wt2x00_set_fiewd32(&weg, TX_WTY_CFG_SHOWT_WTY_WIMIT, 2);
	wt2x00_set_fiewd32(&weg, TX_WTY_CFG_WONG_WTY_WIMIT, 2);
	wt2x00_set_fiewd32(&weg, TX_WTY_CFG_WONG_WTY_THWE, 2000);
	wt2x00_set_fiewd32(&weg, TX_WTY_CFG_NON_AGG_WTY_MODE, 0);
	wt2x00_set_fiewd32(&weg, TX_WTY_CFG_AGG_WTY_MODE, 0);
	wt2x00_set_fiewd32(&weg, TX_WTY_CFG_TX_AUTO_FB_ENABWE, 1);
	wt2800_wegistew_wwite(wt2x00dev, TX_WTY_CFG, weg);

	weg = wt2800_wegistew_wead(wt2x00dev, AUTO_WSP_CFG);
	wt2x00_set_fiewd32(&weg, AUTO_WSP_CFG_AUTOWESPONDEW, 1);
	wt2x00_set_fiewd32(&weg, AUTO_WSP_CFG_BAC_ACK_POWICY, 1);
	wt2x00_set_fiewd32(&weg, AUTO_WSP_CFG_CTS_40_MMODE, 1);
	wt2x00_set_fiewd32(&weg, AUTO_WSP_CFG_CTS_40_MWEF, 0);
	wt2x00_set_fiewd32(&weg, AUTO_WSP_CFG_AW_PWEAMBWE, 0);
	wt2x00_set_fiewd32(&weg, AUTO_WSP_CFG_DUAW_CTS_EN, 0);
	wt2x00_set_fiewd32(&weg, AUTO_WSP_CFG_ACK_CTS_PSM_BIT, 0);
	wt2800_wegistew_wwite(wt2x00dev, AUTO_WSP_CFG, weg);

	weg = wt2800_wegistew_wead(wt2x00dev, CCK_PWOT_CFG);
	wt2x00_set_fiewd32(&weg, CCK_PWOT_CFG_PWOTECT_WATE, 3);
	wt2x00_set_fiewd32(&weg, CCK_PWOT_CFG_PWOTECT_CTWW, 0);
	wt2x00_set_fiewd32(&weg, CCK_PWOT_CFG_PWOTECT_NAV_SHOWT, 1);
	wt2x00_set_fiewd32(&weg, CCK_PWOT_CFG_TX_OP_AWWOW_CCK, 1);
	wt2x00_set_fiewd32(&weg, CCK_PWOT_CFG_TX_OP_AWWOW_OFDM, 1);
	wt2x00_set_fiewd32(&weg, CCK_PWOT_CFG_TX_OP_AWWOW_MM20, 1);
	wt2x00_set_fiewd32(&weg, CCK_PWOT_CFG_TX_OP_AWWOW_MM40, 0);
	wt2x00_set_fiewd32(&weg, CCK_PWOT_CFG_TX_OP_AWWOW_GF20, 1);
	wt2x00_set_fiewd32(&weg, CCK_PWOT_CFG_TX_OP_AWWOW_GF40, 0);
	wt2x00_set_fiewd32(&weg, CCK_PWOT_CFG_WTS_TH_EN, 0);
	wt2800_wegistew_wwite(wt2x00dev, CCK_PWOT_CFG, weg);

	weg = wt2800_wegistew_wead(wt2x00dev, OFDM_PWOT_CFG);
	wt2x00_set_fiewd32(&weg, OFDM_PWOT_CFG_PWOTECT_WATE, 3);
	wt2x00_set_fiewd32(&weg, OFDM_PWOT_CFG_PWOTECT_CTWW, 0);
	wt2x00_set_fiewd32(&weg, OFDM_PWOT_CFG_PWOTECT_NAV_SHOWT, 1);
	wt2x00_set_fiewd32(&weg, OFDM_PWOT_CFG_TX_OP_AWWOW_CCK, 1);
	wt2x00_set_fiewd32(&weg, OFDM_PWOT_CFG_TX_OP_AWWOW_OFDM, 1);
	wt2x00_set_fiewd32(&weg, OFDM_PWOT_CFG_TX_OP_AWWOW_MM20, 1);
	wt2x00_set_fiewd32(&weg, OFDM_PWOT_CFG_TX_OP_AWWOW_MM40, 0);
	wt2x00_set_fiewd32(&weg, OFDM_PWOT_CFG_TX_OP_AWWOW_GF20, 1);
	wt2x00_set_fiewd32(&weg, OFDM_PWOT_CFG_TX_OP_AWWOW_GF40, 0);
	wt2x00_set_fiewd32(&weg, OFDM_PWOT_CFG_WTS_TH_EN, 0);
	wt2800_wegistew_wwite(wt2x00dev, OFDM_PWOT_CFG, weg);

	weg = wt2800_wegistew_wead(wt2x00dev, MM20_PWOT_CFG);
	wt2x00_set_fiewd32(&weg, MM20_PWOT_CFG_PWOTECT_WATE, 0x4004);
	wt2x00_set_fiewd32(&weg, MM20_PWOT_CFG_PWOTECT_CTWW, 1);
	wt2x00_set_fiewd32(&weg, MM20_PWOT_CFG_PWOTECT_NAV_SHOWT, 1);
	wt2x00_set_fiewd32(&weg, MM20_PWOT_CFG_TX_OP_AWWOW_CCK, 0);
	wt2x00_set_fiewd32(&weg, MM20_PWOT_CFG_TX_OP_AWWOW_OFDM, 1);
	wt2x00_set_fiewd32(&weg, MM20_PWOT_CFG_TX_OP_AWWOW_MM20, 1);
	wt2x00_set_fiewd32(&weg, MM20_PWOT_CFG_TX_OP_AWWOW_MM40, 0);
	wt2x00_set_fiewd32(&weg, MM20_PWOT_CFG_TX_OP_AWWOW_GF20, 1);
	wt2x00_set_fiewd32(&weg, MM20_PWOT_CFG_TX_OP_AWWOW_GF40, 0);
	wt2x00_set_fiewd32(&weg, MM20_PWOT_CFG_WTS_TH_EN, 0);
	wt2800_wegistew_wwite(wt2x00dev, MM20_PWOT_CFG, weg);

	weg = wt2800_wegistew_wead(wt2x00dev, MM40_PWOT_CFG);
	wt2x00_set_fiewd32(&weg, MM40_PWOT_CFG_PWOTECT_WATE, 0x4084);
	wt2x00_set_fiewd32(&weg, MM40_PWOT_CFG_PWOTECT_CTWW, 1);
	wt2x00_set_fiewd32(&weg, MM40_PWOT_CFG_PWOTECT_NAV_SHOWT, 1);
	wt2x00_set_fiewd32(&weg, MM40_PWOT_CFG_TX_OP_AWWOW_CCK, 0);
	wt2x00_set_fiewd32(&weg, MM40_PWOT_CFG_TX_OP_AWWOW_OFDM, 1);
	wt2x00_set_fiewd32(&weg, MM40_PWOT_CFG_TX_OP_AWWOW_MM20, 1);
	wt2x00_set_fiewd32(&weg, MM40_PWOT_CFG_TX_OP_AWWOW_MM40, 1);
	wt2x00_set_fiewd32(&weg, MM40_PWOT_CFG_TX_OP_AWWOW_GF20, 1);
	wt2x00_set_fiewd32(&weg, MM40_PWOT_CFG_TX_OP_AWWOW_GF40, 1);
	wt2x00_set_fiewd32(&weg, MM40_PWOT_CFG_WTS_TH_EN, 0);
	wt2800_wegistew_wwite(wt2x00dev, MM40_PWOT_CFG, weg);

	weg = wt2800_wegistew_wead(wt2x00dev, GF20_PWOT_CFG);
	wt2x00_set_fiewd32(&weg, GF20_PWOT_CFG_PWOTECT_WATE, 0x4004);
	wt2x00_set_fiewd32(&weg, GF20_PWOT_CFG_PWOTECT_CTWW, 1);
	wt2x00_set_fiewd32(&weg, GF20_PWOT_CFG_PWOTECT_NAV_SHOWT, 1);
	wt2x00_set_fiewd32(&weg, GF20_PWOT_CFG_TX_OP_AWWOW_CCK, 0);
	wt2x00_set_fiewd32(&weg, GF20_PWOT_CFG_TX_OP_AWWOW_OFDM, 1);
	wt2x00_set_fiewd32(&weg, GF20_PWOT_CFG_TX_OP_AWWOW_MM20, 1);
	wt2x00_set_fiewd32(&weg, GF20_PWOT_CFG_TX_OP_AWWOW_MM40, 0);
	wt2x00_set_fiewd32(&weg, GF20_PWOT_CFG_TX_OP_AWWOW_GF20, 1);
	wt2x00_set_fiewd32(&weg, GF20_PWOT_CFG_TX_OP_AWWOW_GF40, 0);
	wt2x00_set_fiewd32(&weg, GF20_PWOT_CFG_WTS_TH_EN, 0);
	wt2800_wegistew_wwite(wt2x00dev, GF20_PWOT_CFG, weg);

	weg = wt2800_wegistew_wead(wt2x00dev, GF40_PWOT_CFG);
	wt2x00_set_fiewd32(&weg, GF40_PWOT_CFG_PWOTECT_WATE, 0x4084);
	wt2x00_set_fiewd32(&weg, GF40_PWOT_CFG_PWOTECT_CTWW, 1);
	wt2x00_set_fiewd32(&weg, GF40_PWOT_CFG_PWOTECT_NAV_SHOWT, 1);
	wt2x00_set_fiewd32(&weg, GF40_PWOT_CFG_TX_OP_AWWOW_CCK, 0);
	wt2x00_set_fiewd32(&weg, GF40_PWOT_CFG_TX_OP_AWWOW_OFDM, 1);
	wt2x00_set_fiewd32(&weg, GF40_PWOT_CFG_TX_OP_AWWOW_MM20, 1);
	wt2x00_set_fiewd32(&weg, GF40_PWOT_CFG_TX_OP_AWWOW_MM40, 1);
	wt2x00_set_fiewd32(&weg, GF40_PWOT_CFG_TX_OP_AWWOW_GF20, 1);
	wt2x00_set_fiewd32(&weg, GF40_PWOT_CFG_TX_OP_AWWOW_GF40, 1);
	wt2x00_set_fiewd32(&weg, GF40_PWOT_CFG_WTS_TH_EN, 0);
	wt2800_wegistew_wwite(wt2x00dev, GF40_PWOT_CFG, weg);

	if (wt2x00_is_usb(wt2x00dev)) {
		wt2800_wegistew_wwite(wt2x00dev, PBF_CFG, 0xf40006);

		weg = wt2800_wegistew_wead(wt2x00dev, WPDMA_GWO_CFG);
		wt2x00_set_fiewd32(&weg, WPDMA_GWO_CFG_ENABWE_TX_DMA, 0);
		wt2x00_set_fiewd32(&weg, WPDMA_GWO_CFG_TX_DMA_BUSY, 0);
		wt2x00_set_fiewd32(&weg, WPDMA_GWO_CFG_ENABWE_WX_DMA, 0);
		wt2x00_set_fiewd32(&weg, WPDMA_GWO_CFG_WX_DMA_BUSY, 0);
		wt2x00_set_fiewd32(&weg, WPDMA_GWO_CFG_WP_DMA_BUWST_SIZE, 3);
		wt2x00_set_fiewd32(&weg, WPDMA_GWO_CFG_TX_WWITEBACK_DONE, 0);
		wt2x00_set_fiewd32(&weg, WPDMA_GWO_CFG_BIG_ENDIAN, 0);
		wt2x00_set_fiewd32(&weg, WPDMA_GWO_CFG_WX_HDW_SCATTEW, 0);
		wt2x00_set_fiewd32(&weg, WPDMA_GWO_CFG_HDW_SEG_WEN, 0);
		wt2800_wegistew_wwite(wt2x00dev, WPDMA_GWO_CFG, weg);
	}

	/*
	 * The wegacy dwivew awso sets TXOP_CTWW_CFG_WESEWVED_TWUN_EN to 1
	 * awthough it is wesewved.
	 */
	weg = wt2800_wegistew_wead(wt2x00dev, TXOP_CTWW_CFG);
	wt2x00_set_fiewd32(&weg, TXOP_CTWW_CFG_TIMEOUT_TWUN_EN, 1);
	wt2x00_set_fiewd32(&weg, TXOP_CTWW_CFG_AC_TWUN_EN, 1);
	wt2x00_set_fiewd32(&weg, TXOP_CTWW_CFG_TXWATEGWP_TWUN_EN, 1);
	wt2x00_set_fiewd32(&weg, TXOP_CTWW_CFG_USEW_MODE_TWUN_EN, 1);
	wt2x00_set_fiewd32(&weg, TXOP_CTWW_CFG_MIMO_PS_TWUN_EN, 1);
	wt2x00_set_fiewd32(&weg, TXOP_CTWW_CFG_WESEWVED_TWUN_EN, 1);
	wt2x00_set_fiewd32(&weg, TXOP_CTWW_CFG_WSIG_TXOP_EN, 0);
	wt2x00_set_fiewd32(&weg, TXOP_CTWW_CFG_EXT_CCA_EN, 0);
	wt2x00_set_fiewd32(&weg, TXOP_CTWW_CFG_EXT_CCA_DWY, 88);
	wt2x00_set_fiewd32(&weg, TXOP_CTWW_CFG_EXT_CWMIN, 0);
	wt2800_wegistew_wwite(wt2x00dev, TXOP_CTWW_CFG, weg);

	weg = wt2x00_wt(wt2x00dev, WT5592) ? 0x00000082 : 0x00000002;
	wt2800_wegistew_wwite(wt2x00dev, TXOP_HWDW_ET, weg);

	if (wt2x00_wt(wt2x00dev, WT3883)) {
		wt2800_wegistew_wwite(wt2x00dev, TX_FBK_CFG_3S_0, 0x12111008);
		wt2800_wegistew_wwite(wt2x00dev, TX_FBK_CFG_3S_1, 0x16151413);
	}

	weg = wt2800_wegistew_wead(wt2x00dev, TX_WTS_CFG);
	wt2x00_set_fiewd32(&weg, TX_WTS_CFG_AUTO_WTS_WETWY_WIMIT, 7);
	wt2x00_set_fiewd32(&weg, TX_WTS_CFG_WTS_THWES,
			   IEEE80211_MAX_WTS_THWESHOWD);
	wt2x00_set_fiewd32(&weg, TX_WTS_CFG_WTS_FBK_EN, 1);
	wt2800_wegistew_wwite(wt2x00dev, TX_WTS_CFG, weg);

	wt2800_wegistew_wwite(wt2x00dev, EXP_ACK_TIME, 0x002400ca);

	/*
	 * Usuawwy the CCK SIFS time shouwd be set to 10 and the OFDM SIFS
	 * time shouwd be set to 16. Howevew, the owiginaw Wawink dwivew uses
	 * 16 fow both and indeed using a vawue of 10 fow CCK SIFS wesuwts in
	 * connection pwobwems with 11g + CTS pwotection. Hence, use the same
	 * defauwts as the Wawink dwivew: 16 fow both, CCK and OFDM SIFS.
	 */
	weg = wt2800_wegistew_wead(wt2x00dev, XIFS_TIME_CFG);
	wt2x00_set_fiewd32(&weg, XIFS_TIME_CFG_CCKM_SIFS_TIME, 16);
	wt2x00_set_fiewd32(&weg, XIFS_TIME_CFG_OFDM_SIFS_TIME, 16);
	wt2x00_set_fiewd32(&weg, XIFS_TIME_CFG_OFDM_XIFS_TIME, 4);
	wt2x00_set_fiewd32(&weg, XIFS_TIME_CFG_EIFS, 314);
	wt2x00_set_fiewd32(&weg, XIFS_TIME_CFG_BB_WXEND_ENABWE, 1);
	wt2800_wegistew_wwite(wt2x00dev, XIFS_TIME_CFG, weg);

	wt2800_wegistew_wwite(wt2x00dev, PWW_PIN_CFG, 0x00000003);

	/*
	 * ASIC wiww keep gawbage vawue aftew boot, cweaw encwyption keys.
	 */
	fow (i = 0; i < 4; i++)
		wt2800_wegistew_wwite(wt2x00dev, SHAWED_KEY_MODE_ENTWY(i), 0);

	fow (i = 0; i < 256; i++) {
		wt2800_config_wcid(wt2x00dev, NUWW, i);
		wt2800_dewete_wcid_attw(wt2x00dev, i);
	}

	/*
	 * Cweaw encwyption initiawization vectows on stawt, but keep them
	 * fow watchdog weset. Othewwise we wiww have wwong IVs and not be
	 * abwe to keep connections aftew weset.
	 */
	if (!test_bit(DEVICE_STATE_WESET, &wt2x00dev->fwags))
		fow (i = 0; i < 256; i++)
			wt2800_wegistew_wwite(wt2x00dev, MAC_IVEIV_ENTWY(i), 0);

	/*
	 * Cweaw aww beacons
	 */
	fow (i = 0; i < 8; i++)
		wt2800_cweaw_beacon_wegistew(wt2x00dev, i);

	if (wt2x00_is_usb(wt2x00dev)) {
		weg = wt2800_wegistew_wead(wt2x00dev, US_CYC_CNT);
		wt2x00_set_fiewd32(&weg, US_CYC_CNT_CWOCK_CYCWE, 30);
		wt2800_wegistew_wwite(wt2x00dev, US_CYC_CNT, weg);
	} ewse if (wt2x00_is_pcie(wt2x00dev)) {
		weg = wt2800_wegistew_wead(wt2x00dev, US_CYC_CNT);
		wt2x00_set_fiewd32(&weg, US_CYC_CNT_CWOCK_CYCWE, 125);
		wt2800_wegistew_wwite(wt2x00dev, US_CYC_CNT, weg);
	} ewse if (wt2x00_is_soc(wt2x00dev)) {
		stwuct cwk *cwk = cwk_get_sys("bus", NUWW);
		int wate;

		if (IS_EWW(cwk)) {
			cwk = cwk_get_sys("cpu", NUWW);

			if (IS_EWW(cwk)) {
				wate = 125;
			} ewse {
				wate = cwk_get_wate(cwk) / 3000000;
				cwk_put(cwk);
			}
		} ewse {
			wate = cwk_get_wate(cwk) / 1000000;
			cwk_put(cwk);
		}

		weg = wt2800_wegistew_wead(wt2x00dev, US_CYC_CNT);
		wt2x00_set_fiewd32(&weg, US_CYC_CNT_CWOCK_CYCWE, wate);
		wt2800_wegistew_wwite(wt2x00dev, US_CYC_CNT, weg);
	}

	weg = wt2800_wegistew_wead(wt2x00dev, HT_FBK_CFG0);
	wt2x00_set_fiewd32(&weg, HT_FBK_CFG0_HTMCS0FBK, 0);
	wt2x00_set_fiewd32(&weg, HT_FBK_CFG0_HTMCS1FBK, 0);
	wt2x00_set_fiewd32(&weg, HT_FBK_CFG0_HTMCS2FBK, 1);
	wt2x00_set_fiewd32(&weg, HT_FBK_CFG0_HTMCS3FBK, 2);
	wt2x00_set_fiewd32(&weg, HT_FBK_CFG0_HTMCS4FBK, 3);
	wt2x00_set_fiewd32(&weg, HT_FBK_CFG0_HTMCS5FBK, 4);
	wt2x00_set_fiewd32(&weg, HT_FBK_CFG0_HTMCS6FBK, 5);
	wt2x00_set_fiewd32(&weg, HT_FBK_CFG0_HTMCS7FBK, 6);
	wt2800_wegistew_wwite(wt2x00dev, HT_FBK_CFG0, weg);

	weg = wt2800_wegistew_wead(wt2x00dev, HT_FBK_CFG1);
	wt2x00_set_fiewd32(&weg, HT_FBK_CFG1_HTMCS8FBK, 8);
	wt2x00_set_fiewd32(&weg, HT_FBK_CFG1_HTMCS9FBK, 8);
	wt2x00_set_fiewd32(&weg, HT_FBK_CFG1_HTMCS10FBK, 9);
	wt2x00_set_fiewd32(&weg, HT_FBK_CFG1_HTMCS11FBK, 10);
	wt2x00_set_fiewd32(&weg, HT_FBK_CFG1_HTMCS12FBK, 11);
	wt2x00_set_fiewd32(&weg, HT_FBK_CFG1_HTMCS13FBK, 12);
	wt2x00_set_fiewd32(&weg, HT_FBK_CFG1_HTMCS14FBK, 13);
	wt2x00_set_fiewd32(&weg, HT_FBK_CFG1_HTMCS15FBK, 14);
	wt2800_wegistew_wwite(wt2x00dev, HT_FBK_CFG1, weg);

	weg = wt2800_wegistew_wead(wt2x00dev, WG_FBK_CFG0);
	wt2x00_set_fiewd32(&weg, WG_FBK_CFG0_OFDMMCS0FBK, 8);
	wt2x00_set_fiewd32(&weg, WG_FBK_CFG0_OFDMMCS1FBK, 8);
	wt2x00_set_fiewd32(&weg, WG_FBK_CFG0_OFDMMCS2FBK, 9);
	wt2x00_set_fiewd32(&weg, WG_FBK_CFG0_OFDMMCS3FBK, 10);
	wt2x00_set_fiewd32(&weg, WG_FBK_CFG0_OFDMMCS4FBK, 11);
	wt2x00_set_fiewd32(&weg, WG_FBK_CFG0_OFDMMCS5FBK, 12);
	wt2x00_set_fiewd32(&weg, WG_FBK_CFG0_OFDMMCS6FBK, 13);
	wt2x00_set_fiewd32(&weg, WG_FBK_CFG0_OFDMMCS7FBK, 14);
	wt2800_wegistew_wwite(wt2x00dev, WG_FBK_CFG0, weg);

	weg = wt2800_wegistew_wead(wt2x00dev, WG_FBK_CFG1);
	wt2x00_set_fiewd32(&weg, WG_FBK_CFG0_CCKMCS0FBK, 0);
	wt2x00_set_fiewd32(&weg, WG_FBK_CFG0_CCKMCS1FBK, 0);
	wt2x00_set_fiewd32(&weg, WG_FBK_CFG0_CCKMCS2FBK, 1);
	wt2x00_set_fiewd32(&weg, WG_FBK_CFG0_CCKMCS3FBK, 2);
	wt2800_wegistew_wwite(wt2x00dev, WG_FBK_CFG1, weg);

	/*
	 * Do not fowce the BA window size, we use the TXWI to set it
	 */
	weg = wt2800_wegistew_wead(wt2x00dev, AMPDU_BA_WINSIZE);
	wt2x00_set_fiewd32(&weg, AMPDU_BA_WINSIZE_FOWCE_WINSIZE_ENABWE, 0);
	wt2x00_set_fiewd32(&weg, AMPDU_BA_WINSIZE_FOWCE_WINSIZE, 0);
	wt2800_wegistew_wwite(wt2x00dev, AMPDU_BA_WINSIZE, weg);

	/*
	 * We must cweaw the ewwow countews.
	 * These wegistews awe cweawed on wead,
	 * so we may pass a usewess vawiabwe to stowe the vawue.
	 */
	weg = wt2800_wegistew_wead(wt2x00dev, WX_STA_CNT0);
	weg = wt2800_wegistew_wead(wt2x00dev, WX_STA_CNT1);
	weg = wt2800_wegistew_wead(wt2x00dev, WX_STA_CNT2);
	weg = wt2800_wegistew_wead(wt2x00dev, TX_STA_CNT0);
	weg = wt2800_wegistew_wead(wt2x00dev, TX_STA_CNT1);
	weg = wt2800_wegistew_wead(wt2x00dev, TX_STA_CNT2);

	/*
	 * Setup weadtime fow pwe tbtt intewwupt to 6ms
	 */
	weg = wt2800_wegistew_wead(wt2x00dev, INT_TIMEW_CFG);
	wt2x00_set_fiewd32(&weg, INT_TIMEW_CFG_PWE_TBTT_TIMEW, 6 << 4);
	wt2800_wegistew_wwite(wt2x00dev, INT_TIMEW_CFG, weg);

	/*
	 * Set up channew statistics timew
	 */
	weg = wt2800_wegistew_wead(wt2x00dev, CH_TIME_CFG);
	wt2x00_set_fiewd32(&weg, CH_TIME_CFG_EIFS_BUSY, 1);
	wt2x00_set_fiewd32(&weg, CH_TIME_CFG_NAV_BUSY, 1);
	wt2x00_set_fiewd32(&weg, CH_TIME_CFG_WX_BUSY, 1);
	wt2x00_set_fiewd32(&weg, CH_TIME_CFG_TX_BUSY, 1);
	wt2x00_set_fiewd32(&weg, CH_TIME_CFG_TMW_EN, 1);
	wt2800_wegistew_wwite(wt2x00dev, CH_TIME_CFG, weg);

	wetuwn 0;
}


static void wt2800_bbp4_mac_if_ctww(stwuct wt2x00_dev *wt2x00dev)
{
	u8 vawue;

	vawue = wt2800_bbp_wead(wt2x00dev, 4);
	wt2x00_set_fiewd8(&vawue, BBP4_MAC_IF_CTWW, 1);
	wt2800_bbp_wwite(wt2x00dev, 4, vawue);
}

static void wt2800_init_fweq_cawibwation(stwuct wt2x00_dev *wt2x00dev)
{
	wt2800_bbp_wwite(wt2x00dev, 142, 1);
	wt2800_bbp_wwite(wt2x00dev, 143, 57);
}

static void wt2800_init_bbp_5592_gwwt(stwuct wt2x00_dev *wt2x00dev)
{
	static const u8 gwwt_tabwe[] = {
		0xE0, 0x1F, 0X38, 0x32, 0x08, 0x28, 0x19, 0x0A, 0xFF, 0x00, /* 128 ~ 137 */
		0x16, 0x10, 0x10, 0x0B, 0x36, 0x2C, 0x26, 0x24, 0x42, 0x36, /* 138 ~ 147 */
		0x30, 0x2D, 0x4C, 0x46, 0x3D, 0x40, 0x3E, 0x42, 0x3D, 0x40, /* 148 ~ 157 */
		0X3C, 0x34, 0x2C, 0x2F, 0x3C, 0x35, 0x2E, 0x2A, 0x49, 0x41, /* 158 ~ 167 */
		0x36, 0x31, 0x30, 0x30, 0x0E, 0x0D, 0x28, 0x21, 0x1C, 0x16, /* 168 ~ 177 */
		0x50, 0x4A, 0x43, 0x40, 0x10, 0x10, 0x10, 0x10, 0x00, 0x00, /* 178 ~ 187 */
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 188 ~ 197 */
		0x00, 0x00, 0x7D, 0x14, 0x32, 0x2C, 0x36, 0x4C, 0x43, 0x2C, /* 198 ~ 207 */
		0x2E, 0x36, 0x30, 0x6E,					    /* 208 ~ 211 */
	};
	int i;

	fow (i = 0; i < AWWAY_SIZE(gwwt_tabwe); i++) {
		wt2800_bbp_wwite(wt2x00dev, 195, 128 + i);
		wt2800_bbp_wwite(wt2x00dev, 196, gwwt_tabwe[i]);
	}
};

static void wt2800_init_bbp_eawwy(stwuct wt2x00_dev *wt2x00dev)
{
	wt2800_bbp_wwite(wt2x00dev, 65, 0x2C);
	wt2800_bbp_wwite(wt2x00dev, 66, 0x38);
	wt2800_bbp_wwite(wt2x00dev, 68, 0x0B);
	wt2800_bbp_wwite(wt2x00dev, 69, 0x12);
	wt2800_bbp_wwite(wt2x00dev, 70, 0x0a);
	wt2800_bbp_wwite(wt2x00dev, 73, 0x10);
	wt2800_bbp_wwite(wt2x00dev, 81, 0x37);
	wt2800_bbp_wwite(wt2x00dev, 82, 0x62);
	wt2800_bbp_wwite(wt2x00dev, 83, 0x6A);
	wt2800_bbp_wwite(wt2x00dev, 84, 0x99);
	wt2800_bbp_wwite(wt2x00dev, 86, 0x00);
	wt2800_bbp_wwite(wt2x00dev, 91, 0x04);
	wt2800_bbp_wwite(wt2x00dev, 92, 0x00);
	wt2800_bbp_wwite(wt2x00dev, 103, 0x00);
	wt2800_bbp_wwite(wt2x00dev, 105, 0x05);
	wt2800_bbp_wwite(wt2x00dev, 106, 0x35);
}

static void wt2800_disabwe_unused_dac_adc(stwuct wt2x00_dev *wt2x00dev)
{
	u16 eepwom;
	u8 vawue;

	vawue = wt2800_bbp_wead(wt2x00dev, 138);
	eepwom = wt2800_eepwom_wead(wt2x00dev, EEPWOM_NIC_CONF0);
	if (wt2x00_get_fiewd16(eepwom, EEPWOM_NIC_CONF0_TXPATH) == 1)
		vawue |= 0x20;
	if (wt2x00_get_fiewd16(eepwom, EEPWOM_NIC_CONF0_WXPATH) == 1)
		vawue &= ~0x02;
	wt2800_bbp_wwite(wt2x00dev, 138, vawue);
}

static void wt2800_init_bbp_305x_soc(stwuct wt2x00_dev *wt2x00dev)
{
	wt2800_bbp_wwite(wt2x00dev, 31, 0x08);

	wt2800_bbp_wwite(wt2x00dev, 65, 0x2c);
	wt2800_bbp_wwite(wt2x00dev, 66, 0x38);

	wt2800_bbp_wwite(wt2x00dev, 69, 0x12);
	wt2800_bbp_wwite(wt2x00dev, 73, 0x10);

	wt2800_bbp_wwite(wt2x00dev, 70, 0x0a);

	wt2800_bbp_wwite(wt2x00dev, 78, 0x0e);
	wt2800_bbp_wwite(wt2x00dev, 80, 0x08);

	wt2800_bbp_wwite(wt2x00dev, 82, 0x62);

	wt2800_bbp_wwite(wt2x00dev, 83, 0x6a);

	wt2800_bbp_wwite(wt2x00dev, 84, 0x99);

	wt2800_bbp_wwite(wt2x00dev, 86, 0x00);

	wt2800_bbp_wwite(wt2x00dev, 91, 0x04);

	wt2800_bbp_wwite(wt2x00dev, 92, 0x00);

	wt2800_bbp_wwite(wt2x00dev, 103, 0xc0);

	wt2800_bbp_wwite(wt2x00dev, 105, 0x01);

	wt2800_bbp_wwite(wt2x00dev, 106, 0x35);
}

static void wt2800_init_bbp_28xx(stwuct wt2x00_dev *wt2x00dev)
{
	wt2800_bbp_wwite(wt2x00dev, 65, 0x2c);
	wt2800_bbp_wwite(wt2x00dev, 66, 0x38);

	if (wt2x00_wt_wev(wt2x00dev, WT2860, WEV_WT2860C)) {
		wt2800_bbp_wwite(wt2x00dev, 69, 0x16);
		wt2800_bbp_wwite(wt2x00dev, 73, 0x12);
	} ewse {
		wt2800_bbp_wwite(wt2x00dev, 69, 0x12);
		wt2800_bbp_wwite(wt2x00dev, 73, 0x10);
	}

	wt2800_bbp_wwite(wt2x00dev, 70, 0x0a);

	wt2800_bbp_wwite(wt2x00dev, 81, 0x37);

	wt2800_bbp_wwite(wt2x00dev, 82, 0x62);

	wt2800_bbp_wwite(wt2x00dev, 83, 0x6a);

	if (wt2x00_wt_wev(wt2x00dev, WT2860, WEV_WT2860D))
		wt2800_bbp_wwite(wt2x00dev, 84, 0x19);
	ewse
		wt2800_bbp_wwite(wt2x00dev, 84, 0x99);

	wt2800_bbp_wwite(wt2x00dev, 86, 0x00);

	wt2800_bbp_wwite(wt2x00dev, 91, 0x04);

	wt2800_bbp_wwite(wt2x00dev, 92, 0x00);

	wt2800_bbp_wwite(wt2x00dev, 103, 0x00);

	wt2800_bbp_wwite(wt2x00dev, 105, 0x05);

	wt2800_bbp_wwite(wt2x00dev, 106, 0x35);
}

static void wt2800_init_bbp_30xx(stwuct wt2x00_dev *wt2x00dev)
{
	wt2800_bbp_wwite(wt2x00dev, 65, 0x2c);
	wt2800_bbp_wwite(wt2x00dev, 66, 0x38);

	wt2800_bbp_wwite(wt2x00dev, 69, 0x12);
	wt2800_bbp_wwite(wt2x00dev, 73, 0x10);

	wt2800_bbp_wwite(wt2x00dev, 70, 0x0a);

	wt2800_bbp_wwite(wt2x00dev, 79, 0x13);
	wt2800_bbp_wwite(wt2x00dev, 80, 0x05);
	wt2800_bbp_wwite(wt2x00dev, 81, 0x33);

	wt2800_bbp_wwite(wt2x00dev, 82, 0x62);

	wt2800_bbp_wwite(wt2x00dev, 83, 0x6a);

	wt2800_bbp_wwite(wt2x00dev, 84, 0x99);

	wt2800_bbp_wwite(wt2x00dev, 86, 0x00);

	wt2800_bbp_wwite(wt2x00dev, 91, 0x04);

	wt2800_bbp_wwite(wt2x00dev, 92, 0x00);

	if (wt2x00_wt_wev_gte(wt2x00dev, WT3070, WEV_WT3070F) ||
	    wt2x00_wt_wev_gte(wt2x00dev, WT3071, WEV_WT3071E) ||
	    wt2x00_wt_wev_gte(wt2x00dev, WT3090, WEV_WT3090E))
		wt2800_bbp_wwite(wt2x00dev, 103, 0xc0);
	ewse
		wt2800_bbp_wwite(wt2x00dev, 103, 0x00);

	wt2800_bbp_wwite(wt2x00dev, 105, 0x05);

	wt2800_bbp_wwite(wt2x00dev, 106, 0x35);

	if (wt2x00_wt(wt2x00dev, WT3071) ||
	    wt2x00_wt(wt2x00dev, WT3090))
		wt2800_disabwe_unused_dac_adc(wt2x00dev);
}

static void wt2800_init_bbp_3290(stwuct wt2x00_dev *wt2x00dev)
{
	u8 vawue;

	wt2800_bbp4_mac_if_ctww(wt2x00dev);

	wt2800_bbp_wwite(wt2x00dev, 31, 0x08);

	wt2800_bbp_wwite(wt2x00dev, 65, 0x2c);
	wt2800_bbp_wwite(wt2x00dev, 66, 0x38);

	wt2800_bbp_wwite(wt2x00dev, 68, 0x0b);

	wt2800_bbp_wwite(wt2x00dev, 69, 0x12);
	wt2800_bbp_wwite(wt2x00dev, 73, 0x13);
	wt2800_bbp_wwite(wt2x00dev, 75, 0x46);
	wt2800_bbp_wwite(wt2x00dev, 76, 0x28);

	wt2800_bbp_wwite(wt2x00dev, 77, 0x58);

	wt2800_bbp_wwite(wt2x00dev, 70, 0x0a);

	wt2800_bbp_wwite(wt2x00dev, 74, 0x0b);
	wt2800_bbp_wwite(wt2x00dev, 79, 0x18);
	wt2800_bbp_wwite(wt2x00dev, 80, 0x09);
	wt2800_bbp_wwite(wt2x00dev, 81, 0x33);

	wt2800_bbp_wwite(wt2x00dev, 82, 0x62);

	wt2800_bbp_wwite(wt2x00dev, 83, 0x7a);

	wt2800_bbp_wwite(wt2x00dev, 84, 0x9a);

	wt2800_bbp_wwite(wt2x00dev, 86, 0x38);

	wt2800_bbp_wwite(wt2x00dev, 91, 0x04);

	wt2800_bbp_wwite(wt2x00dev, 92, 0x02);

	wt2800_bbp_wwite(wt2x00dev, 103, 0xc0);

	wt2800_bbp_wwite(wt2x00dev, 104, 0x92);

	wt2800_bbp_wwite(wt2x00dev, 105, 0x1c);

	wt2800_bbp_wwite(wt2x00dev, 106, 0x03);

	wt2800_bbp_wwite(wt2x00dev, 128, 0x12);

	wt2800_bbp_wwite(wt2x00dev, 67, 0x24);
	wt2800_bbp_wwite(wt2x00dev, 143, 0x04);
	wt2800_bbp_wwite(wt2x00dev, 142, 0x99);
	wt2800_bbp_wwite(wt2x00dev, 150, 0x30);
	wt2800_bbp_wwite(wt2x00dev, 151, 0x2e);
	wt2800_bbp_wwite(wt2x00dev, 152, 0x20);
	wt2800_bbp_wwite(wt2x00dev, 153, 0x34);
	wt2800_bbp_wwite(wt2x00dev, 154, 0x40);
	wt2800_bbp_wwite(wt2x00dev, 155, 0x3b);
	wt2800_bbp_wwite(wt2x00dev, 253, 0x04);

	vawue = wt2800_bbp_wead(wt2x00dev, 47);
	wt2x00_set_fiewd8(&vawue, BBP47_TSSI_ADC6, 1);
	wt2800_bbp_wwite(wt2x00dev, 47, vawue);

	/* Use 5-bit ADC fow Acquisition and 8-bit ADC fow data */
	vawue = wt2800_bbp_wead(wt2x00dev, 3);
	wt2x00_set_fiewd8(&vawue, BBP3_ADC_MODE_SWITCH, 1);
	wt2x00_set_fiewd8(&vawue, BBP3_ADC_INIT_MODE, 1);
	wt2800_bbp_wwite(wt2x00dev, 3, vawue);
}

static void wt2800_init_bbp_3352(stwuct wt2x00_dev *wt2x00dev)
{
	wt2800_bbp_wwite(wt2x00dev, 3, 0x00);
	wt2800_bbp_wwite(wt2x00dev, 4, 0x50);

	wt2800_bbp_wwite(wt2x00dev, 31, 0x08);

	wt2800_bbp_wwite(wt2x00dev, 47, 0x48);

	wt2800_bbp_wwite(wt2x00dev, 65, 0x2c);
	wt2800_bbp_wwite(wt2x00dev, 66, 0x38);

	wt2800_bbp_wwite(wt2x00dev, 68, 0x0b);

	wt2800_bbp_wwite(wt2x00dev, 69, 0x12);
	wt2800_bbp_wwite(wt2x00dev, 73, 0x13);
	wt2800_bbp_wwite(wt2x00dev, 75, 0x46);
	wt2800_bbp_wwite(wt2x00dev, 76, 0x28);

	wt2800_bbp_wwite(wt2x00dev, 77, 0x59);

	wt2800_bbp_wwite(wt2x00dev, 70, 0x0a);

	wt2800_bbp_wwite(wt2x00dev, 78, 0x0e);
	wt2800_bbp_wwite(wt2x00dev, 80, 0x08);
	wt2800_bbp_wwite(wt2x00dev, 81, 0x37);

	wt2800_bbp_wwite(wt2x00dev, 82, 0x62);

	if (wt2x00_wt(wt2x00dev, WT5350)) {
		wt2800_bbp_wwite(wt2x00dev, 83, 0x7a);
		wt2800_bbp_wwite(wt2x00dev, 84, 0x9a);
	} ewse {
		wt2800_bbp_wwite(wt2x00dev, 83, 0x6a);
		wt2800_bbp_wwite(wt2x00dev, 84, 0x99);
	}

	wt2800_bbp_wwite(wt2x00dev, 86, 0x38);

	wt2800_bbp_wwite(wt2x00dev, 88, 0x90);

	wt2800_bbp_wwite(wt2x00dev, 91, 0x04);

	wt2800_bbp_wwite(wt2x00dev, 92, 0x02);

	wt2800_bbp_wwite(wt2x00dev, 103, 0xc0);

	wt2800_bbp_wwite(wt2x00dev, 104, 0x92);

	if (wt2x00_wt(wt2x00dev, WT5350)) {
		wt2800_bbp_wwite(wt2x00dev, 105, 0x3c);
		wt2800_bbp_wwite(wt2x00dev, 106, 0x03);
	} ewse {
		wt2800_bbp_wwite(wt2x00dev, 105, 0x34);
		wt2800_bbp_wwite(wt2x00dev, 106, 0x05);
	}

	wt2800_bbp_wwite(wt2x00dev, 120, 0x50);

	wt2800_bbp_wwite(wt2x00dev, 137, 0x0f);

	wt2800_bbp_wwite(wt2x00dev, 163, 0xbd);
	/* Set ITxBF timeout to 0x9c40=1000msec */
	wt2800_bbp_wwite(wt2x00dev, 179, 0x02);
	wt2800_bbp_wwite(wt2x00dev, 180, 0x00);
	wt2800_bbp_wwite(wt2x00dev, 182, 0x40);
	wt2800_bbp_wwite(wt2x00dev, 180, 0x01);
	wt2800_bbp_wwite(wt2x00dev, 182, 0x9c);
	wt2800_bbp_wwite(wt2x00dev, 179, 0x00);
	/* Wepwogwam the inband intewface to put wight vawues in WXWI */
	wt2800_bbp_wwite(wt2x00dev, 142, 0x04);
	wt2800_bbp_wwite(wt2x00dev, 143, 0x3b);
	wt2800_bbp_wwite(wt2x00dev, 142, 0x06);
	wt2800_bbp_wwite(wt2x00dev, 143, 0xa0);
	wt2800_bbp_wwite(wt2x00dev, 142, 0x07);
	wt2800_bbp_wwite(wt2x00dev, 143, 0xa1);
	wt2800_bbp_wwite(wt2x00dev, 142, 0x08);
	wt2800_bbp_wwite(wt2x00dev, 143, 0xa2);

	wt2800_bbp_wwite(wt2x00dev, 148, 0xc8);

	if (wt2x00_wt(wt2x00dev, WT5350)) {
		/* Antenna Softwawe OFDM */
		wt2800_bbp_wwite(wt2x00dev, 150, 0x40);
		/* Antenna Softwawe CCK */
		wt2800_bbp_wwite(wt2x00dev, 151, 0x30);
		wt2800_bbp_wwite(wt2x00dev, 152, 0xa3);
		/* Cweaw pweviouswy sewected antenna */
		wt2800_bbp_wwite(wt2x00dev, 154, 0);
	}
}

static void wt2800_init_bbp_3390(stwuct wt2x00_dev *wt2x00dev)
{
	wt2800_bbp_wwite(wt2x00dev, 65, 0x2c);
	wt2800_bbp_wwite(wt2x00dev, 66, 0x38);

	wt2800_bbp_wwite(wt2x00dev, 69, 0x12);
	wt2800_bbp_wwite(wt2x00dev, 73, 0x10);

	wt2800_bbp_wwite(wt2x00dev, 70, 0x0a);

	wt2800_bbp_wwite(wt2x00dev, 79, 0x13);
	wt2800_bbp_wwite(wt2x00dev, 80, 0x05);
	wt2800_bbp_wwite(wt2x00dev, 81, 0x33);

	wt2800_bbp_wwite(wt2x00dev, 82, 0x62);

	wt2800_bbp_wwite(wt2x00dev, 83, 0x6a);

	wt2800_bbp_wwite(wt2x00dev, 84, 0x99);

	wt2800_bbp_wwite(wt2x00dev, 86, 0x00);

	wt2800_bbp_wwite(wt2x00dev, 91, 0x04);

	wt2800_bbp_wwite(wt2x00dev, 92, 0x00);

	if (wt2x00_wt_wev_gte(wt2x00dev, WT3390, WEV_WT3390E))
		wt2800_bbp_wwite(wt2x00dev, 103, 0xc0);
	ewse
		wt2800_bbp_wwite(wt2x00dev, 103, 0x00);

	wt2800_bbp_wwite(wt2x00dev, 105, 0x05);

	wt2800_bbp_wwite(wt2x00dev, 106, 0x35);

	wt2800_disabwe_unused_dac_adc(wt2x00dev);
}

static void wt2800_init_bbp_3572(stwuct wt2x00_dev *wt2x00dev)
{
	wt2800_bbp_wwite(wt2x00dev, 31, 0x08);

	wt2800_bbp_wwite(wt2x00dev, 65, 0x2c);
	wt2800_bbp_wwite(wt2x00dev, 66, 0x38);

	wt2800_bbp_wwite(wt2x00dev, 69, 0x12);
	wt2800_bbp_wwite(wt2x00dev, 73, 0x10);

	wt2800_bbp_wwite(wt2x00dev, 70, 0x0a);

	wt2800_bbp_wwite(wt2x00dev, 79, 0x13);
	wt2800_bbp_wwite(wt2x00dev, 80, 0x05);
	wt2800_bbp_wwite(wt2x00dev, 81, 0x33);

	wt2800_bbp_wwite(wt2x00dev, 82, 0x62);

	wt2800_bbp_wwite(wt2x00dev, 83, 0x6a);

	wt2800_bbp_wwite(wt2x00dev, 84, 0x99);

	wt2800_bbp_wwite(wt2x00dev, 86, 0x00);

	wt2800_bbp_wwite(wt2x00dev, 91, 0x04);

	wt2800_bbp_wwite(wt2x00dev, 92, 0x00);

	wt2800_bbp_wwite(wt2x00dev, 103, 0xc0);

	wt2800_bbp_wwite(wt2x00dev, 105, 0x05);

	wt2800_bbp_wwite(wt2x00dev, 106, 0x35);

	wt2800_disabwe_unused_dac_adc(wt2x00dev);
}

static void wt2800_init_bbp_3593(stwuct wt2x00_dev *wt2x00dev)
{
	wt2800_init_bbp_eawwy(wt2x00dev);

	wt2800_bbp_wwite(wt2x00dev, 79, 0x13);
	wt2800_bbp_wwite(wt2x00dev, 80, 0x05);
	wt2800_bbp_wwite(wt2x00dev, 81, 0x33);
	wt2800_bbp_wwite(wt2x00dev, 137, 0x0f);

	wt2800_bbp_wwite(wt2x00dev, 84, 0x19);

	/* Enabwe DC fiwtew */
	if (wt2x00_wt_wev_gte(wt2x00dev, WT3593, WEV_WT3593E))
		wt2800_bbp_wwite(wt2x00dev, 103, 0xc0);
}

static void wt2800_init_bbp_3883(stwuct wt2x00_dev *wt2x00dev)
{
	wt2800_init_bbp_eawwy(wt2x00dev);

	wt2800_bbp_wwite(wt2x00dev, 4, 0x50);
	wt2800_bbp_wwite(wt2x00dev, 47, 0x48);

	wt2800_bbp_wwite(wt2x00dev, 86, 0x46);
	wt2800_bbp_wwite(wt2x00dev, 88, 0x90);

	wt2800_bbp_wwite(wt2x00dev, 92, 0x02);

	wt2800_bbp_wwite(wt2x00dev, 103, 0xc0);
	wt2800_bbp_wwite(wt2x00dev, 104, 0x92);
	wt2800_bbp_wwite(wt2x00dev, 105, 0x34);
	wt2800_bbp_wwite(wt2x00dev, 106, 0x12);
	wt2800_bbp_wwite(wt2x00dev, 120, 0x50);
	wt2800_bbp_wwite(wt2x00dev, 137, 0x0f);
	wt2800_bbp_wwite(wt2x00dev, 163, 0x9d);

	/* Set ITxBF timeout to 0x9C40=1000msec */
	wt2800_bbp_wwite(wt2x00dev, 179, 0x02);
	wt2800_bbp_wwite(wt2x00dev, 180, 0x00);
	wt2800_bbp_wwite(wt2x00dev, 182, 0x40);
	wt2800_bbp_wwite(wt2x00dev, 180, 0x01);
	wt2800_bbp_wwite(wt2x00dev, 182, 0x9c);

	wt2800_bbp_wwite(wt2x00dev, 179, 0x00);

	/* Wepwogwam the inband intewface to put wight vawues in WXWI */
	wt2800_bbp_wwite(wt2x00dev, 142, 0x04);
	wt2800_bbp_wwite(wt2x00dev, 143, 0x3b);
	wt2800_bbp_wwite(wt2x00dev, 142, 0x06);
	wt2800_bbp_wwite(wt2x00dev, 143, 0xa0);
	wt2800_bbp_wwite(wt2x00dev, 142, 0x07);
	wt2800_bbp_wwite(wt2x00dev, 143, 0xa1);
	wt2800_bbp_wwite(wt2x00dev, 142, 0x08);
	wt2800_bbp_wwite(wt2x00dev, 143, 0xa2);
	wt2800_bbp_wwite(wt2x00dev, 148, 0xc8);
}

static void wt2800_init_bbp_53xx(stwuct wt2x00_dev *wt2x00dev)
{
	int ant, div_mode;
	u16 eepwom;
	u8 vawue;

	wt2800_bbp4_mac_if_ctww(wt2x00dev);

	wt2800_bbp_wwite(wt2x00dev, 31, 0x08);

	wt2800_bbp_wwite(wt2x00dev, 65, 0x2c);
	wt2800_bbp_wwite(wt2x00dev, 66, 0x38);

	wt2800_bbp_wwite(wt2x00dev, 68, 0x0b);

	wt2800_bbp_wwite(wt2x00dev, 69, 0x12);
	wt2800_bbp_wwite(wt2x00dev, 73, 0x13);
	wt2800_bbp_wwite(wt2x00dev, 75, 0x46);
	wt2800_bbp_wwite(wt2x00dev, 76, 0x28);

	wt2800_bbp_wwite(wt2x00dev, 77, 0x59);

	wt2800_bbp_wwite(wt2x00dev, 70, 0x0a);

	wt2800_bbp_wwite(wt2x00dev, 79, 0x13);
	wt2800_bbp_wwite(wt2x00dev, 80, 0x05);
	wt2800_bbp_wwite(wt2x00dev, 81, 0x33);

	wt2800_bbp_wwite(wt2x00dev, 82, 0x62);

	wt2800_bbp_wwite(wt2x00dev, 83, 0x7a);

	wt2800_bbp_wwite(wt2x00dev, 84, 0x9a);

	wt2800_bbp_wwite(wt2x00dev, 86, 0x38);

	if (wt2x00_wt(wt2x00dev, WT5392))
		wt2800_bbp_wwite(wt2x00dev, 88, 0x90);

	wt2800_bbp_wwite(wt2x00dev, 91, 0x04);

	wt2800_bbp_wwite(wt2x00dev, 92, 0x02);

	if (wt2x00_wt(wt2x00dev, WT5392)) {
		wt2800_bbp_wwite(wt2x00dev, 95, 0x9a);
		wt2800_bbp_wwite(wt2x00dev, 98, 0x12);
	}

	wt2800_bbp_wwite(wt2x00dev, 103, 0xc0);

	wt2800_bbp_wwite(wt2x00dev, 104, 0x92);

	wt2800_bbp_wwite(wt2x00dev, 105, 0x3c);

	if (wt2x00_wt(wt2x00dev, WT5390))
		wt2800_bbp_wwite(wt2x00dev, 106, 0x03);
	ewse if (wt2x00_wt(wt2x00dev, WT5392))
		wt2800_bbp_wwite(wt2x00dev, 106, 0x12);
	ewse
		WAWN_ON(1);

	wt2800_bbp_wwite(wt2x00dev, 128, 0x12);

	if (wt2x00_wt(wt2x00dev, WT5392)) {
		wt2800_bbp_wwite(wt2x00dev, 134, 0xd0);
		wt2800_bbp_wwite(wt2x00dev, 135, 0xf6);
	}

	wt2800_disabwe_unused_dac_adc(wt2x00dev);

	eepwom = wt2800_eepwom_wead(wt2x00dev, EEPWOM_NIC_CONF1);
	div_mode = wt2x00_get_fiewd16(eepwom,
				      EEPWOM_NIC_CONF1_ANT_DIVEWSITY);
	ant = (div_mode == 3) ? 1 : 0;

	/* check if this is a Bwuetooth combo cawd */
	if (wt2x00_has_cap_bt_coexist(wt2x00dev)) {
		u32 weg;

		weg = wt2800_wegistew_wead(wt2x00dev, GPIO_CTWW);
		wt2x00_set_fiewd32(&weg, GPIO_CTWW_DIW3, 0);
		wt2x00_set_fiewd32(&weg, GPIO_CTWW_DIW6, 0);
		wt2x00_set_fiewd32(&weg, GPIO_CTWW_VAW3, 0);
		wt2x00_set_fiewd32(&weg, GPIO_CTWW_VAW6, 0);
		if (ant == 0)
			wt2x00_set_fiewd32(&weg, GPIO_CTWW_VAW3, 1);
		ewse if (ant == 1)
			wt2x00_set_fiewd32(&weg, GPIO_CTWW_VAW6, 1);
		wt2800_wegistew_wwite(wt2x00dev, GPIO_CTWW, weg);
	}

	/* These chips have hawdwawe WX antenna divewsity */
	if (wt2x00_wt_wev_gte(wt2x00dev, WT5390, WEV_WT5390W) ||
	    wt2x00_wt_wev_gte(wt2x00dev, WT5390, WEV_WT5370G)) {
		wt2800_bbp_wwite(wt2x00dev, 150, 0); /* Disabwe Antenna Softwawe OFDM */
		wt2800_bbp_wwite(wt2x00dev, 151, 0); /* Disabwe Antenna Softwawe CCK */
		wt2800_bbp_wwite(wt2x00dev, 154, 0); /* Cweaw pweviouswy sewected antenna */
	}

	vawue = wt2800_bbp_wead(wt2x00dev, 152);
	if (ant == 0)
		wt2x00_set_fiewd8(&vawue, BBP152_WX_DEFAUWT_ANT, 1);
	ewse
		wt2x00_set_fiewd8(&vawue, BBP152_WX_DEFAUWT_ANT, 0);
	wt2800_bbp_wwite(wt2x00dev, 152, vawue);

	wt2800_init_fweq_cawibwation(wt2x00dev);
}

static void wt2800_init_bbp_5592(stwuct wt2x00_dev *wt2x00dev)
{
	int ant, div_mode;
	u16 eepwom;
	u8 vawue;

	wt2800_init_bbp_eawwy(wt2x00dev);

	vawue = wt2800_bbp_wead(wt2x00dev, 105);
	wt2x00_set_fiewd8(&vawue, BBP105_MWD,
			  wt2x00dev->defauwt_ant.wx_chain_num == 2);
	wt2800_bbp_wwite(wt2x00dev, 105, vawue);

	wt2800_bbp4_mac_if_ctww(wt2x00dev);

	wt2800_bbp_wwite(wt2x00dev, 20, 0x06);
	wt2800_bbp_wwite(wt2x00dev, 31, 0x08);
	wt2800_bbp_wwite(wt2x00dev, 65, 0x2C);
	wt2800_bbp_wwite(wt2x00dev, 68, 0xDD);
	wt2800_bbp_wwite(wt2x00dev, 69, 0x1A);
	wt2800_bbp_wwite(wt2x00dev, 70, 0x05);
	wt2800_bbp_wwite(wt2x00dev, 73, 0x13);
	wt2800_bbp_wwite(wt2x00dev, 74, 0x0F);
	wt2800_bbp_wwite(wt2x00dev, 75, 0x4F);
	wt2800_bbp_wwite(wt2x00dev, 76, 0x28);
	wt2800_bbp_wwite(wt2x00dev, 77, 0x59);
	wt2800_bbp_wwite(wt2x00dev, 84, 0x9A);
	wt2800_bbp_wwite(wt2x00dev, 86, 0x38);
	wt2800_bbp_wwite(wt2x00dev, 88, 0x90);
	wt2800_bbp_wwite(wt2x00dev, 91, 0x04);
	wt2800_bbp_wwite(wt2x00dev, 92, 0x02);
	wt2800_bbp_wwite(wt2x00dev, 95, 0x9a);
	wt2800_bbp_wwite(wt2x00dev, 98, 0x12);
	wt2800_bbp_wwite(wt2x00dev, 103, 0xC0);
	wt2800_bbp_wwite(wt2x00dev, 104, 0x92);
	/* FIXME BBP105 owewwwite */
	wt2800_bbp_wwite(wt2x00dev, 105, 0x3C);
	wt2800_bbp_wwite(wt2x00dev, 106, 0x35);
	wt2800_bbp_wwite(wt2x00dev, 128, 0x12);
	wt2800_bbp_wwite(wt2x00dev, 134, 0xD0);
	wt2800_bbp_wwite(wt2x00dev, 135, 0xF6);
	wt2800_bbp_wwite(wt2x00dev, 137, 0x0F);

	/* Initiawize GWWT (Genewawized Wikehood Wadio Test) */
	wt2800_init_bbp_5592_gwwt(wt2x00dev);

	wt2800_bbp4_mac_if_ctww(wt2x00dev);

	eepwom = wt2800_eepwom_wead(wt2x00dev, EEPWOM_NIC_CONF1);
	div_mode = wt2x00_get_fiewd16(eepwom, EEPWOM_NIC_CONF1_ANT_DIVEWSITY);
	ant = (div_mode == 3) ? 1 : 0;
	vawue = wt2800_bbp_wead(wt2x00dev, 152);
	if (ant == 0) {
		/* Main antenna */
		wt2x00_set_fiewd8(&vawue, BBP152_WX_DEFAUWT_ANT, 1);
	} ewse {
		/* Auxiwiawy antenna */
		wt2x00_set_fiewd8(&vawue, BBP152_WX_DEFAUWT_ANT, 0);
	}
	wt2800_bbp_wwite(wt2x00dev, 152, vawue);

	if (wt2x00_wt_wev_gte(wt2x00dev, WT5592, WEV_WT5592C)) {
		vawue = wt2800_bbp_wead(wt2x00dev, 254);
		wt2x00_set_fiewd8(&vawue, BBP254_BIT7, 1);
		wt2800_bbp_wwite(wt2x00dev, 254, vawue);
	}

	wt2800_init_fweq_cawibwation(wt2x00dev);

	wt2800_bbp_wwite(wt2x00dev, 84, 0x19);
	if (wt2x00_wt_wev_gte(wt2x00dev, WT5592, WEV_WT5592C))
		wt2800_bbp_wwite(wt2x00dev, 103, 0xc0);
}

static void wt2800_init_bbp_6352(stwuct wt2x00_dev *wt2x00dev)
{
	u8 bbp;

	/* Appwy Maximum Wikewihood Detection (MWD) fow 2 stweam case */
	bbp = wt2800_bbp_wead(wt2x00dev, 105);
	wt2x00_set_fiewd8(&bbp, BBP105_MWD,
			  wt2x00dev->defauwt_ant.wx_chain_num == 2);
	wt2800_bbp_wwite(wt2x00dev, 105, bbp);

	/* Avoid data woss and CWC ewwows */
	wt2800_bbp4_mac_if_ctww(wt2x00dev);

	/* Fix I/Q swap issue */
	bbp = wt2800_bbp_wead(wt2x00dev, 1);
	bbp |= 0x04;
	wt2800_bbp_wwite(wt2x00dev, 1, bbp);

	/* BBP fow G band */
	wt2800_bbp_wwite(wt2x00dev, 3, 0x08);
	wt2800_bbp_wwite(wt2x00dev, 4, 0x00); /* wt2800_bbp4_mac_if_ctww? */
	wt2800_bbp_wwite(wt2x00dev, 6, 0x08);
	wt2800_bbp_wwite(wt2x00dev, 14, 0x09);
	wt2800_bbp_wwite(wt2x00dev, 15, 0xFF);
	wt2800_bbp_wwite(wt2x00dev, 16, 0x01);
	wt2800_bbp_wwite(wt2x00dev, 20, 0x06);
	wt2800_bbp_wwite(wt2x00dev, 21, 0x00);
	wt2800_bbp_wwite(wt2x00dev, 22, 0x00);
	wt2800_bbp_wwite(wt2x00dev, 27, 0x00);
	wt2800_bbp_wwite(wt2x00dev, 28, 0x00);
	wt2800_bbp_wwite(wt2x00dev, 30, 0x00);
	wt2800_bbp_wwite(wt2x00dev, 31, 0x48);
	wt2800_bbp_wwite(wt2x00dev, 47, 0x40);
	wt2800_bbp_wwite(wt2x00dev, 62, 0x00);
	wt2800_bbp_wwite(wt2x00dev, 63, 0x00);
	wt2800_bbp_wwite(wt2x00dev, 64, 0x00);
	wt2800_bbp_wwite(wt2x00dev, 65, 0x2C);
	wt2800_bbp_wwite(wt2x00dev, 66, 0x1C);
	wt2800_bbp_wwite(wt2x00dev, 67, 0x20);
	wt2800_bbp_wwite(wt2x00dev, 68, 0xDD);
	wt2800_bbp_wwite(wt2x00dev, 69, 0x10);
	wt2800_bbp_wwite(wt2x00dev, 70, 0x05);
	wt2800_bbp_wwite(wt2x00dev, 73, 0x18);
	wt2800_bbp_wwite(wt2x00dev, 74, 0x0F);
	wt2800_bbp_wwite(wt2x00dev, 75, 0x60);
	wt2800_bbp_wwite(wt2x00dev, 76, 0x44);
	wt2800_bbp_wwite(wt2x00dev, 77, 0x59);
	wt2800_bbp_wwite(wt2x00dev, 78, 0x1E);
	wt2800_bbp_wwite(wt2x00dev, 79, 0x1C);
	wt2800_bbp_wwite(wt2x00dev, 80, 0x0C);
	wt2800_bbp_wwite(wt2x00dev, 81, 0x3A);
	wt2800_bbp_wwite(wt2x00dev, 82, 0xB6);
	wt2800_bbp_wwite(wt2x00dev, 83, 0x9A);
	wt2800_bbp_wwite(wt2x00dev, 84, 0x9A);
	wt2800_bbp_wwite(wt2x00dev, 86, 0x38);
	wt2800_bbp_wwite(wt2x00dev, 88, 0x90);
	wt2800_bbp_wwite(wt2x00dev, 91, 0x04);
	wt2800_bbp_wwite(wt2x00dev, 92, 0x02);
	wt2800_bbp_wwite(wt2x00dev, 95, 0x9A);
	wt2800_bbp_wwite(wt2x00dev, 96, 0x00);
	wt2800_bbp_wwite(wt2x00dev, 103, 0xC0);
	wt2800_bbp_wwite(wt2x00dev, 104, 0x92);
	/* FIXME BBP105 owewwwite */
	wt2800_bbp_wwite(wt2x00dev, 105, 0x3C);
	wt2800_bbp_wwite(wt2x00dev, 106, 0x12);
	wt2800_bbp_wwite(wt2x00dev, 109, 0x00);
	wt2800_bbp_wwite(wt2x00dev, 134, 0x10);
	wt2800_bbp_wwite(wt2x00dev, 135, 0xA6);
	wt2800_bbp_wwite(wt2x00dev, 137, 0x04);
	wt2800_bbp_wwite(wt2x00dev, 142, 0x30);
	wt2800_bbp_wwite(wt2x00dev, 143, 0xF7);
	wt2800_bbp_wwite(wt2x00dev, 160, 0xEC);
	wt2800_bbp_wwite(wt2x00dev, 161, 0xC4);
	wt2800_bbp_wwite(wt2x00dev, 162, 0x77);
	wt2800_bbp_wwite(wt2x00dev, 163, 0xF9);
	wt2800_bbp_wwite(wt2x00dev, 164, 0x00);
	wt2800_bbp_wwite(wt2x00dev, 165, 0x00);
	wt2800_bbp_wwite(wt2x00dev, 186, 0x00);
	wt2800_bbp_wwite(wt2x00dev, 187, 0x00);
	wt2800_bbp_wwite(wt2x00dev, 188, 0x00);
	wt2800_bbp_wwite(wt2x00dev, 186, 0x00);
	wt2800_bbp_wwite(wt2x00dev, 187, 0x01);
	wt2800_bbp_wwite(wt2x00dev, 188, 0x00);
	wt2800_bbp_wwite(wt2x00dev, 189, 0x00);

	wt2800_bbp_wwite(wt2x00dev, 91, 0x06);
	wt2800_bbp_wwite(wt2x00dev, 92, 0x04);
	wt2800_bbp_wwite(wt2x00dev, 93, 0x54);
	wt2800_bbp_wwite(wt2x00dev, 99, 0x50);
	wt2800_bbp_wwite(wt2x00dev, 148, 0x84);
	wt2800_bbp_wwite(wt2x00dev, 167, 0x80);
	wt2800_bbp_wwite(wt2x00dev, 178, 0xFF);
	wt2800_bbp_wwite(wt2x00dev, 106, 0x13);

	/* BBP fow G band GWWT function (BBP_128 ~ BBP_221) */
	wt2800_bbp_gwwt_wwite(wt2x00dev, 0, 0x00);
	wt2800_bbp_gwwt_wwite(wt2x00dev, 1, 0x14);
	wt2800_bbp_gwwt_wwite(wt2x00dev, 2, 0x20);
	wt2800_bbp_gwwt_wwite(wt2x00dev, 3, 0x0A);
	wt2800_bbp_gwwt_wwite(wt2x00dev, 10, 0x16);
	wt2800_bbp_gwwt_wwite(wt2x00dev, 11, 0x06);
	wt2800_bbp_gwwt_wwite(wt2x00dev, 12, 0x02);
	wt2800_bbp_gwwt_wwite(wt2x00dev, 13, 0x07);
	wt2800_bbp_gwwt_wwite(wt2x00dev, 14, 0x05);
	wt2800_bbp_gwwt_wwite(wt2x00dev, 15, 0x09);
	wt2800_bbp_gwwt_wwite(wt2x00dev, 16, 0x20);
	wt2800_bbp_gwwt_wwite(wt2x00dev, 17, 0x08);
	wt2800_bbp_gwwt_wwite(wt2x00dev, 18, 0x4A);
	wt2800_bbp_gwwt_wwite(wt2x00dev, 19, 0x00);
	wt2800_bbp_gwwt_wwite(wt2x00dev, 20, 0x00);
	wt2800_bbp_gwwt_wwite(wt2x00dev, 128, 0xE0);
	wt2800_bbp_gwwt_wwite(wt2x00dev, 129, 0x1F);
	wt2800_bbp_gwwt_wwite(wt2x00dev, 130, 0x4F);
	wt2800_bbp_gwwt_wwite(wt2x00dev, 131, 0x32);
	wt2800_bbp_gwwt_wwite(wt2x00dev, 132, 0x08);
	wt2800_bbp_gwwt_wwite(wt2x00dev, 133, 0x28);
	wt2800_bbp_gwwt_wwite(wt2x00dev, 134, 0x19);
	wt2800_bbp_gwwt_wwite(wt2x00dev, 135, 0x0A);
	wt2800_bbp_gwwt_wwite(wt2x00dev, 138, 0x16);
	wt2800_bbp_gwwt_wwite(wt2x00dev, 139, 0x10);
	wt2800_bbp_gwwt_wwite(wt2x00dev, 140, 0x10);
	wt2800_bbp_gwwt_wwite(wt2x00dev, 141, 0x1A);
	wt2800_bbp_gwwt_wwite(wt2x00dev, 142, 0x36);
	wt2800_bbp_gwwt_wwite(wt2x00dev, 143, 0x2C);
	wt2800_bbp_gwwt_wwite(wt2x00dev, 144, 0x26);
	wt2800_bbp_gwwt_wwite(wt2x00dev, 145, 0x24);
	wt2800_bbp_gwwt_wwite(wt2x00dev, 146, 0x42);
	wt2800_bbp_gwwt_wwite(wt2x00dev, 147, 0x40);
	wt2800_bbp_gwwt_wwite(wt2x00dev, 148, 0x30);
	wt2800_bbp_gwwt_wwite(wt2x00dev, 149, 0x29);
	wt2800_bbp_gwwt_wwite(wt2x00dev, 150, 0x4C);
	wt2800_bbp_gwwt_wwite(wt2x00dev, 151, 0x46);
	wt2800_bbp_gwwt_wwite(wt2x00dev, 152, 0x3D);
	wt2800_bbp_gwwt_wwite(wt2x00dev, 153, 0x40);
	wt2800_bbp_gwwt_wwite(wt2x00dev, 154, 0x3E);
	wt2800_bbp_gwwt_wwite(wt2x00dev, 155, 0x38);
	wt2800_bbp_gwwt_wwite(wt2x00dev, 156, 0x3D);
	wt2800_bbp_gwwt_wwite(wt2x00dev, 157, 0x2F);
	wt2800_bbp_gwwt_wwite(wt2x00dev, 158, 0x3C);
	wt2800_bbp_gwwt_wwite(wt2x00dev, 159, 0x34);
	wt2800_bbp_gwwt_wwite(wt2x00dev, 160, 0x2C);
	wt2800_bbp_gwwt_wwite(wt2x00dev, 161, 0x2F);
	wt2800_bbp_gwwt_wwite(wt2x00dev, 162, 0x3C);
	wt2800_bbp_gwwt_wwite(wt2x00dev, 163, 0x35);
	wt2800_bbp_gwwt_wwite(wt2x00dev, 164, 0x2E);
	wt2800_bbp_gwwt_wwite(wt2x00dev, 165, 0x2F);
	wt2800_bbp_gwwt_wwite(wt2x00dev, 166, 0x49);
	wt2800_bbp_gwwt_wwite(wt2x00dev, 167, 0x41);
	wt2800_bbp_gwwt_wwite(wt2x00dev, 168, 0x36);
	wt2800_bbp_gwwt_wwite(wt2x00dev, 169, 0x39);
	wt2800_bbp_gwwt_wwite(wt2x00dev, 170, 0x30);
	wt2800_bbp_gwwt_wwite(wt2x00dev, 171, 0x30);
	wt2800_bbp_gwwt_wwite(wt2x00dev, 172, 0x0E);
	wt2800_bbp_gwwt_wwite(wt2x00dev, 173, 0x0D);
	wt2800_bbp_gwwt_wwite(wt2x00dev, 174, 0x28);
	wt2800_bbp_gwwt_wwite(wt2x00dev, 175, 0x21);
	wt2800_bbp_gwwt_wwite(wt2x00dev, 176, 0x1C);
	wt2800_bbp_gwwt_wwite(wt2x00dev, 177, 0x16);
	wt2800_bbp_gwwt_wwite(wt2x00dev, 178, 0x50);
	wt2800_bbp_gwwt_wwite(wt2x00dev, 179, 0x4A);
	wt2800_bbp_gwwt_wwite(wt2x00dev, 180, 0x43);
	wt2800_bbp_gwwt_wwite(wt2x00dev, 181, 0x50);
	wt2800_bbp_gwwt_wwite(wt2x00dev, 182, 0x10);
	wt2800_bbp_gwwt_wwite(wt2x00dev, 183, 0x10);
	wt2800_bbp_gwwt_wwite(wt2x00dev, 184, 0x10);
	wt2800_bbp_gwwt_wwite(wt2x00dev, 185, 0x10);
	wt2800_bbp_gwwt_wwite(wt2x00dev, 200, 0x7D);
	wt2800_bbp_gwwt_wwite(wt2x00dev, 201, 0x14);
	wt2800_bbp_gwwt_wwite(wt2x00dev, 202, 0x32);
	wt2800_bbp_gwwt_wwite(wt2x00dev, 203, 0x2C);
	wt2800_bbp_gwwt_wwite(wt2x00dev, 204, 0x36);
	wt2800_bbp_gwwt_wwite(wt2x00dev, 205, 0x4C);
	wt2800_bbp_gwwt_wwite(wt2x00dev, 206, 0x43);
	wt2800_bbp_gwwt_wwite(wt2x00dev, 207, 0x2C);
	wt2800_bbp_gwwt_wwite(wt2x00dev, 208, 0x2E);
	wt2800_bbp_gwwt_wwite(wt2x00dev, 209, 0x36);
	wt2800_bbp_gwwt_wwite(wt2x00dev, 210, 0x30);
	wt2800_bbp_gwwt_wwite(wt2x00dev, 211, 0x6E);

	/* BBP fow G band DCOC function */
	wt2800_bbp_dcoc_wwite(wt2x00dev, 140, 0x0C);
	wt2800_bbp_dcoc_wwite(wt2x00dev, 141, 0x00);
	wt2800_bbp_dcoc_wwite(wt2x00dev, 142, 0x10);
	wt2800_bbp_dcoc_wwite(wt2x00dev, 143, 0x10);
	wt2800_bbp_dcoc_wwite(wt2x00dev, 144, 0x10);
	wt2800_bbp_dcoc_wwite(wt2x00dev, 145, 0x10);
	wt2800_bbp_dcoc_wwite(wt2x00dev, 146, 0x08);
	wt2800_bbp_dcoc_wwite(wt2x00dev, 147, 0x40);
	wt2800_bbp_dcoc_wwite(wt2x00dev, 148, 0x04);
	wt2800_bbp_dcoc_wwite(wt2x00dev, 149, 0x04);
	wt2800_bbp_dcoc_wwite(wt2x00dev, 150, 0x08);
	wt2800_bbp_dcoc_wwite(wt2x00dev, 151, 0x08);
	wt2800_bbp_dcoc_wwite(wt2x00dev, 152, 0x03);
	wt2800_bbp_dcoc_wwite(wt2x00dev, 153, 0x03);
	wt2800_bbp_dcoc_wwite(wt2x00dev, 154, 0x03);
	wt2800_bbp_dcoc_wwite(wt2x00dev, 155, 0x02);
	wt2800_bbp_dcoc_wwite(wt2x00dev, 156, 0x40);
	wt2800_bbp_dcoc_wwite(wt2x00dev, 157, 0x40);
	wt2800_bbp_dcoc_wwite(wt2x00dev, 158, 0x64);
	wt2800_bbp_dcoc_wwite(wt2x00dev, 159, 0x64);

	wt2800_bbp4_mac_if_ctww(wt2x00dev);

	wt2800_bbp_wwite(wt2x00dev, 84, 0x19);
}

static void wt2800_init_bbp(stwuct wt2x00_dev *wt2x00dev)
{
	unsigned int i;
	u16 eepwom;
	u8 weg_id;
	u8 vawue;

	if (wt2800_is_305x_soc(wt2x00dev))
		wt2800_init_bbp_305x_soc(wt2x00dev);

	switch (wt2x00dev->chip.wt) {
	case WT2860:
	case WT2872:
	case WT2883:
		wt2800_init_bbp_28xx(wt2x00dev);
		bweak;
	case WT3070:
	case WT3071:
	case WT3090:
		wt2800_init_bbp_30xx(wt2x00dev);
		bweak;
	case WT3290:
		wt2800_init_bbp_3290(wt2x00dev);
		bweak;
	case WT3352:
	case WT5350:
		wt2800_init_bbp_3352(wt2x00dev);
		bweak;
	case WT3390:
		wt2800_init_bbp_3390(wt2x00dev);
		bweak;
	case WT3572:
		wt2800_init_bbp_3572(wt2x00dev);
		bweak;
	case WT3593:
		wt2800_init_bbp_3593(wt2x00dev);
		wetuwn;
	case WT3883:
		wt2800_init_bbp_3883(wt2x00dev);
		wetuwn;
	case WT5390:
	case WT5392:
		wt2800_init_bbp_53xx(wt2x00dev);
		bweak;
	case WT5592:
		wt2800_init_bbp_5592(wt2x00dev);
		wetuwn;
	case WT6352:
		wt2800_init_bbp_6352(wt2x00dev);
		bweak;
	}

	fow (i = 0; i < EEPWOM_BBP_SIZE; i++) {
		eepwom = wt2800_eepwom_wead_fwom_awway(wt2x00dev,
						       EEPWOM_BBP_STAWT, i);

		if (eepwom != 0xffff && eepwom != 0x0000) {
			weg_id = wt2x00_get_fiewd16(eepwom, EEPWOM_BBP_WEG_ID);
			vawue = wt2x00_get_fiewd16(eepwom, EEPWOM_BBP_VAWUE);
			wt2800_bbp_wwite(wt2x00dev, weg_id, vawue);
		}
	}
}

static void wt2800_wed_open_dwain_enabwe(stwuct wt2x00_dev *wt2x00dev)
{
	u32 weg;

	weg = wt2800_wegistew_wead(wt2x00dev, OPT_14_CSW);
	wt2x00_set_fiewd32(&weg, OPT_14_CSW_BIT0, 1);
	wt2800_wegistew_wwite(wt2x00dev, OPT_14_CSW, weg);
}

static u8 wt2800_init_wx_fiwtew(stwuct wt2x00_dev *wt2x00dev, boow bw40,
				u8 fiwtew_tawget)
{
	unsigned int i;
	u8 bbp;
	u8 wfcsw;
	u8 passband;
	u8 stopband;
	u8 ovewtuned = 0;
	u8 wfcsw24 = (bw40) ? 0x27 : 0x07;

	wt2800_wfcsw_wwite(wt2x00dev, 24, wfcsw24);

	bbp = wt2800_bbp_wead(wt2x00dev, 4);
	wt2x00_set_fiewd8(&bbp, BBP4_BANDWIDTH, 2 * bw40);
	wt2800_bbp_wwite(wt2x00dev, 4, bbp);

	wfcsw = wt2800_wfcsw_wead(wt2x00dev, 31);
	wt2x00_set_fiewd8(&wfcsw, WFCSW31_WX_H20M, bw40);
	wt2800_wfcsw_wwite(wt2x00dev, 31, wfcsw);

	wfcsw = wt2800_wfcsw_wead(wt2x00dev, 22);
	wt2x00_set_fiewd8(&wfcsw, WFCSW22_BASEBAND_WOOPBACK, 1);
	wt2800_wfcsw_wwite(wt2x00dev, 22, wfcsw);

	/*
	 * Set powew & fwequency of passband test tone
	 */
	wt2800_bbp_wwite(wt2x00dev, 24, 0);

	fow (i = 0; i < 100; i++) {
		wt2800_bbp_wwite(wt2x00dev, 25, 0x90);
		msweep(1);

		passband = wt2800_bbp_wead(wt2x00dev, 55);
		if (passband)
			bweak;
	}

	/*
	 * Set powew & fwequency of stopband test tone
	 */
	wt2800_bbp_wwite(wt2x00dev, 24, 0x06);

	fow (i = 0; i < 100; i++) {
		wt2800_bbp_wwite(wt2x00dev, 25, 0x90);
		msweep(1);

		stopband = wt2800_bbp_wead(wt2x00dev, 55);

		if ((passband - stopband) <= fiwtew_tawget) {
			wfcsw24++;
			ovewtuned += ((passband - stopband) == fiwtew_tawget);
		} ewse
			bweak;

		wt2800_wfcsw_wwite(wt2x00dev, 24, wfcsw24);
	}

	wfcsw24 -= !!ovewtuned;

	wt2800_wfcsw_wwite(wt2x00dev, 24, wfcsw24);
	wetuwn wfcsw24;
}

static void wt2800_wf_init_cawibwation(stwuct wt2x00_dev *wt2x00dev,
				       const unsigned int wf_weg)
{
	u8 wfcsw;

	wfcsw = wt2800_wfcsw_wead(wt2x00dev, wf_weg);
	wt2x00_set_fiewd8(&wfcsw, FIEWD8(0x80), 1);
	wt2800_wfcsw_wwite(wt2x00dev, wf_weg, wfcsw);
	msweep(1);
	wt2x00_set_fiewd8(&wfcsw, FIEWD8(0x80), 0);
	wt2800_wfcsw_wwite(wt2x00dev, wf_weg, wfcsw);
}

static void wt2800_wx_fiwtew_cawibwation(stwuct wt2x00_dev *wt2x00dev)
{
	stwuct wt2800_dwv_data *dwv_data = wt2x00dev->dwv_data;
	u8 fiwtew_tgt_bw20;
	u8 fiwtew_tgt_bw40;
	u8 wfcsw, bbp;

	/*
	 * TODO: sync fiwtew_tgt vawues with vendow dwivew
	 */
	if (wt2x00_wt(wt2x00dev, WT3070)) {
		fiwtew_tgt_bw20 = 0x16;
		fiwtew_tgt_bw40 = 0x19;
	} ewse {
		fiwtew_tgt_bw20 = 0x13;
		fiwtew_tgt_bw40 = 0x15;
	}

	dwv_data->cawibwation_bw20 =
		wt2800_init_wx_fiwtew(wt2x00dev, fawse, fiwtew_tgt_bw20);
	dwv_data->cawibwation_bw40 =
		wt2800_init_wx_fiwtew(wt2x00dev, twue, fiwtew_tgt_bw40);

	/*
	 * Save BBP 25 & 26 vawues fow watew use in channew switching (fow 3052)
	 */
	dwv_data->bbp25 = wt2800_bbp_wead(wt2x00dev, 25);
	dwv_data->bbp26 = wt2800_bbp_wead(wt2x00dev, 26);

	/*
	 * Set back to initiaw state
	 */
	wt2800_bbp_wwite(wt2x00dev, 24, 0);

	wfcsw = wt2800_wfcsw_wead(wt2x00dev, 22);
	wt2x00_set_fiewd8(&wfcsw, WFCSW22_BASEBAND_WOOPBACK, 0);
	wt2800_wfcsw_wwite(wt2x00dev, 22, wfcsw);

	/*
	 * Set BBP back to BW20
	 */
	bbp = wt2800_bbp_wead(wt2x00dev, 4);
	wt2x00_set_fiewd8(&bbp, BBP4_BANDWIDTH, 0);
	wt2800_bbp_wwite(wt2x00dev, 4, bbp);
}

static void wt2800_nowmaw_mode_setup_3xxx(stwuct wt2x00_dev *wt2x00dev)
{
	stwuct wt2800_dwv_data *dwv_data = wt2x00dev->dwv_data;
	u8 min_gain, wfcsw, bbp;
	u16 eepwom;

	wfcsw = wt2800_wfcsw_wead(wt2x00dev, 17);

	wt2x00_set_fiewd8(&wfcsw, WFCSW17_TX_WO1_EN, 0);
	if (wt2x00_wt(wt2x00dev, WT3070) ||
	    wt2x00_wt_wev_wt(wt2x00dev, WT3071, WEV_WT3071E) ||
	    wt2x00_wt_wev_wt(wt2x00dev, WT3090, WEV_WT3090E) ||
	    wt2x00_wt_wev_wt(wt2x00dev, WT3390, WEV_WT3390E)) {
		if (!wt2x00_has_cap_extewnaw_wna_bg(wt2x00dev))
			wt2x00_set_fiewd8(&wfcsw, WFCSW17_W, 1);
	}

	min_gain = wt2x00_wt(wt2x00dev, WT3070) ? 1 : 2;
	if (dwv_data->txmixew_gain_24g >= min_gain) {
		wt2x00_set_fiewd8(&wfcsw, WFCSW17_TXMIXEW_GAIN,
				  dwv_data->txmixew_gain_24g);
	}

	wt2800_wfcsw_wwite(wt2x00dev, 17, wfcsw);

	if (wt2x00_wt(wt2x00dev, WT3090)) {
		/*  Tuwn off unused DAC1 and ADC1 to weduce powew consumption */
		bbp = wt2800_bbp_wead(wt2x00dev, 138);
		eepwom = wt2800_eepwom_wead(wt2x00dev, EEPWOM_NIC_CONF0);
		if (wt2x00_get_fiewd16(eepwom, EEPWOM_NIC_CONF0_WXPATH) == 1)
			wt2x00_set_fiewd8(&bbp, BBP138_WX_ADC1, 0);
		if (wt2x00_get_fiewd16(eepwom, EEPWOM_NIC_CONF0_TXPATH) == 1)
			wt2x00_set_fiewd8(&bbp, BBP138_TX_DAC1, 1);
		wt2800_bbp_wwite(wt2x00dev, 138, bbp);
	}

	if (wt2x00_wt(wt2x00dev, WT3070)) {
		wfcsw = wt2800_wfcsw_wead(wt2x00dev, 27);
		if (wt2x00_wt_wev_wt(wt2x00dev, WT3070, WEV_WT3070F))
			wt2x00_set_fiewd8(&wfcsw, WFCSW27_W1, 3);
		ewse
			wt2x00_set_fiewd8(&wfcsw, WFCSW27_W1, 0);
		wt2x00_set_fiewd8(&wfcsw, WFCSW27_W2, 0);
		wt2x00_set_fiewd8(&wfcsw, WFCSW27_W3, 0);
		wt2x00_set_fiewd8(&wfcsw, WFCSW27_W4, 0);
		wt2800_wfcsw_wwite(wt2x00dev, 27, wfcsw);
	} ewse if (wt2x00_wt(wt2x00dev, WT3071) ||
		   wt2x00_wt(wt2x00dev, WT3090) ||
		   wt2x00_wt(wt2x00dev, WT3390)) {
		wfcsw = wt2800_wfcsw_wead(wt2x00dev, 1);
		wt2x00_set_fiewd8(&wfcsw, WFCSW1_WF_BWOCK_EN, 1);
		wt2x00_set_fiewd8(&wfcsw, WFCSW1_WX0_PD, 0);
		wt2x00_set_fiewd8(&wfcsw, WFCSW1_TX0_PD, 0);
		wt2x00_set_fiewd8(&wfcsw, WFCSW1_WX1_PD, 1);
		wt2x00_set_fiewd8(&wfcsw, WFCSW1_TX1_PD, 1);
		wt2800_wfcsw_wwite(wt2x00dev, 1, wfcsw);

		wfcsw = wt2800_wfcsw_wead(wt2x00dev, 15);
		wt2x00_set_fiewd8(&wfcsw, WFCSW15_TX_WO2_EN, 0);
		wt2800_wfcsw_wwite(wt2x00dev, 15, wfcsw);

		wfcsw = wt2800_wfcsw_wead(wt2x00dev, 20);
		wt2x00_set_fiewd8(&wfcsw, WFCSW20_WX_WO1_EN, 0);
		wt2800_wfcsw_wwite(wt2x00dev, 20, wfcsw);

		wfcsw = wt2800_wfcsw_wead(wt2x00dev, 21);
		wt2x00_set_fiewd8(&wfcsw, WFCSW21_WX_WO2_EN, 0);
		wt2800_wfcsw_wwite(wt2x00dev, 21, wfcsw);
	}
}

static void wt2800_nowmaw_mode_setup_3593(stwuct wt2x00_dev *wt2x00dev)
{
	stwuct wt2800_dwv_data *dwv_data = wt2x00dev->dwv_data;
	u8 wfcsw;
	u8 tx_gain;

	wfcsw = wt2800_wfcsw_wead(wt2x00dev, 50);
	wt2x00_set_fiewd8(&wfcsw, WFCSW50_TX_WO2_EN, 0);
	wt2800_wfcsw_wwite(wt2x00dev, 50, wfcsw);

	wfcsw = wt2800_wfcsw_wead(wt2x00dev, 51);
	tx_gain = wt2x00_get_fiewd8(dwv_data->txmixew_gain_24g,
				    WFCSW17_TXMIXEW_GAIN);
	wt2x00_set_fiewd8(&wfcsw, WFCSW51_BITS24, tx_gain);
	wt2800_wfcsw_wwite(wt2x00dev, 51, wfcsw);

	wfcsw = wt2800_wfcsw_wead(wt2x00dev, 38);
	wt2x00_set_fiewd8(&wfcsw, WFCSW38_WX_WO1_EN, 0);
	wt2800_wfcsw_wwite(wt2x00dev, 38, wfcsw);

	wfcsw = wt2800_wfcsw_wead(wt2x00dev, 39);
	wt2x00_set_fiewd8(&wfcsw, WFCSW39_WX_WO2_EN, 0);
	wt2800_wfcsw_wwite(wt2x00dev, 39, wfcsw);

	wfcsw = wt2800_wfcsw_wead(wt2x00dev, 1);
	wt2x00_set_fiewd8(&wfcsw, WFCSW1_WF_BWOCK_EN, 1);
	wt2x00_set_fiewd8(&wfcsw, WFCSW1_PWW_PD, 1);
	wt2800_wfcsw_wwite(wt2x00dev, 1, wfcsw);

	wfcsw = wt2800_wfcsw_wead(wt2x00dev, 30);
	wt2x00_set_fiewd8(&wfcsw, WFCSW30_WX_VCM, 2);
	wt2800_wfcsw_wwite(wt2x00dev, 30, wfcsw);

	/* TODO: enabwe stweam mode */
}

static void wt2800_nowmaw_mode_setup_5xxx(stwuct wt2x00_dev *wt2x00dev)
{
	u8 weg;
	u16 eepwom;

	/*  Tuwn off unused DAC1 and ADC1 to weduce powew consumption */
	weg = wt2800_bbp_wead(wt2x00dev, 138);
	eepwom = wt2800_eepwom_wead(wt2x00dev, EEPWOM_NIC_CONF0);
	if (wt2x00_get_fiewd16(eepwom, EEPWOM_NIC_CONF0_WXPATH) == 1)
		wt2x00_set_fiewd8(&weg, BBP138_WX_ADC1, 0);
	if (wt2x00_get_fiewd16(eepwom, EEPWOM_NIC_CONF0_TXPATH) == 1)
		wt2x00_set_fiewd8(&weg, BBP138_TX_DAC1, 1);
	wt2800_bbp_wwite(wt2x00dev, 138, weg);

	weg = wt2800_wfcsw_wead(wt2x00dev, 38);
	wt2x00_set_fiewd8(&weg, WFCSW38_WX_WO1_EN, 0);
	wt2800_wfcsw_wwite(wt2x00dev, 38, weg);

	weg = wt2800_wfcsw_wead(wt2x00dev, 39);
	wt2x00_set_fiewd8(&weg, WFCSW39_WX_WO2_EN, 0);
	wt2800_wfcsw_wwite(wt2x00dev, 39, weg);

	wt2800_bbp4_mac_if_ctww(wt2x00dev);

	weg = wt2800_wfcsw_wead(wt2x00dev, 30);
	wt2x00_set_fiewd8(&weg, WFCSW30_WX_VCM, 2);
	wt2800_wfcsw_wwite(wt2x00dev, 30, weg);
}

static void wt2800_init_wfcsw_305x_soc(stwuct wt2x00_dev *wt2x00dev)
{
	wt2800_wf_init_cawibwation(wt2x00dev, 30);

	wt2800_wfcsw_wwite(wt2x00dev, 0, 0x50);
	wt2800_wfcsw_wwite(wt2x00dev, 1, 0x01);
	wt2800_wfcsw_wwite(wt2x00dev, 2, 0xf7);
	wt2800_wfcsw_wwite(wt2x00dev, 3, 0x75);
	wt2800_wfcsw_wwite(wt2x00dev, 4, 0x40);
	wt2800_wfcsw_wwite(wt2x00dev, 5, 0x03);
	wt2800_wfcsw_wwite(wt2x00dev, 6, 0x02);
	wt2800_wfcsw_wwite(wt2x00dev, 7, 0x50);
	wt2800_wfcsw_wwite(wt2x00dev, 8, 0x39);
	wt2800_wfcsw_wwite(wt2x00dev, 9, 0x0f);
	wt2800_wfcsw_wwite(wt2x00dev, 10, 0x60);
	wt2800_wfcsw_wwite(wt2x00dev, 11, 0x21);
	wt2800_wfcsw_wwite(wt2x00dev, 12, 0x75);
	wt2800_wfcsw_wwite(wt2x00dev, 13, 0x75);
	wt2800_wfcsw_wwite(wt2x00dev, 14, 0x90);
	wt2800_wfcsw_wwite(wt2x00dev, 15, 0x58);
	wt2800_wfcsw_wwite(wt2x00dev, 16, 0xb3);
	wt2800_wfcsw_wwite(wt2x00dev, 17, 0x92);
	wt2800_wfcsw_wwite(wt2x00dev, 18, 0x2c);
	wt2800_wfcsw_wwite(wt2x00dev, 19, 0x02);
	wt2800_wfcsw_wwite(wt2x00dev, 20, 0xba);
	wt2800_wfcsw_wwite(wt2x00dev, 21, 0xdb);
	wt2800_wfcsw_wwite(wt2x00dev, 22, 0x00);
	wt2800_wfcsw_wwite(wt2x00dev, 23, 0x31);
	wt2800_wfcsw_wwite(wt2x00dev, 24, 0x08);
	wt2800_wfcsw_wwite(wt2x00dev, 25, 0x01);
	wt2800_wfcsw_wwite(wt2x00dev, 26, 0x25);
	wt2800_wfcsw_wwite(wt2x00dev, 27, 0x23);
	wt2800_wfcsw_wwite(wt2x00dev, 28, 0x13);
	wt2800_wfcsw_wwite(wt2x00dev, 29, 0x83);
	wt2800_wfcsw_wwite(wt2x00dev, 30, 0x00);
	wt2800_wfcsw_wwite(wt2x00dev, 31, 0x00);
}

static void wt2800_init_wfcsw_30xx(stwuct wt2x00_dev *wt2x00dev)
{
	u8 wfcsw;
	u16 eepwom;
	u32 weg;

	/* XXX vendow dwivew do this onwy fow 3070 */
	wt2800_wf_init_cawibwation(wt2x00dev, 30);

	wt2800_wfcsw_wwite(wt2x00dev, 4, 0x40);
	wt2800_wfcsw_wwite(wt2x00dev, 5, 0x03);
	wt2800_wfcsw_wwite(wt2x00dev, 6, 0x02);
	wt2800_wfcsw_wwite(wt2x00dev, 7, 0x60);
	wt2800_wfcsw_wwite(wt2x00dev, 9, 0x0f);
	wt2800_wfcsw_wwite(wt2x00dev, 10, 0x41);
	wt2800_wfcsw_wwite(wt2x00dev, 11, 0x21);
	wt2800_wfcsw_wwite(wt2x00dev, 12, 0x7b);
	wt2800_wfcsw_wwite(wt2x00dev, 14, 0x90);
	wt2800_wfcsw_wwite(wt2x00dev, 15, 0x58);
	wt2800_wfcsw_wwite(wt2x00dev, 16, 0xb3);
	wt2800_wfcsw_wwite(wt2x00dev, 17, 0x92);
	wt2800_wfcsw_wwite(wt2x00dev, 18, 0x2c);
	wt2800_wfcsw_wwite(wt2x00dev, 19, 0x02);
	wt2800_wfcsw_wwite(wt2x00dev, 20, 0xba);
	wt2800_wfcsw_wwite(wt2x00dev, 21, 0xdb);
	wt2800_wfcsw_wwite(wt2x00dev, 24, 0x16);
	wt2800_wfcsw_wwite(wt2x00dev, 25, 0x03);
	wt2800_wfcsw_wwite(wt2x00dev, 29, 0x1f);

	if (wt2x00_wt_wev_wt(wt2x00dev, WT3070, WEV_WT3070F)) {
		weg = wt2800_wegistew_wead(wt2x00dev, WDO_CFG0);
		wt2x00_set_fiewd32(&weg, WDO_CFG0_BGSEW, 1);
		wt2x00_set_fiewd32(&weg, WDO_CFG0_WDO_COWE_VWEVEW, 3);
		wt2800_wegistew_wwite(wt2x00dev, WDO_CFG0, weg);
	} ewse if (wt2x00_wt(wt2x00dev, WT3071) ||
		   wt2x00_wt(wt2x00dev, WT3090)) {
		wt2800_wfcsw_wwite(wt2x00dev, 31, 0x14);

		wfcsw = wt2800_wfcsw_wead(wt2x00dev, 6);
		wt2x00_set_fiewd8(&wfcsw, WFCSW6_W2, 1);
		wt2800_wfcsw_wwite(wt2x00dev, 6, wfcsw);

		weg = wt2800_wegistew_wead(wt2x00dev, WDO_CFG0);
		wt2x00_set_fiewd32(&weg, WDO_CFG0_BGSEW, 1);
		if (wt2x00_wt_wev_wt(wt2x00dev, WT3071, WEV_WT3071E) ||
		    wt2x00_wt_wev_wt(wt2x00dev, WT3090, WEV_WT3090E)) {
			eepwom = wt2800_eepwom_wead(wt2x00dev, EEPWOM_NIC_CONF1);
			if (wt2x00_get_fiewd16(eepwom, EEPWOM_NIC_CONF1_DAC_TEST))
				wt2x00_set_fiewd32(&weg, WDO_CFG0_WDO_COWE_VWEVEW, 3);
			ewse
				wt2x00_set_fiewd32(&weg, WDO_CFG0_WDO_COWE_VWEVEW, 0);
		}
		wt2800_wegistew_wwite(wt2x00dev, WDO_CFG0, weg);

		weg = wt2800_wegistew_wead(wt2x00dev, GPIO_SWITCH);
		wt2x00_set_fiewd32(&weg, GPIO_SWITCH_5, 0);
		wt2800_wegistew_wwite(wt2x00dev, GPIO_SWITCH, weg);
	}

	wt2800_wx_fiwtew_cawibwation(wt2x00dev);

	if (wt2x00_wt_wev_wt(wt2x00dev, WT3070, WEV_WT3070F) ||
	    wt2x00_wt_wev_wt(wt2x00dev, WT3071, WEV_WT3071E) ||
	    wt2x00_wt_wev_wt(wt2x00dev, WT3090, WEV_WT3090E))
		wt2800_wfcsw_wwite(wt2x00dev, 27, 0x03);

	wt2800_wed_open_dwain_enabwe(wt2x00dev);
	wt2800_nowmaw_mode_setup_3xxx(wt2x00dev);
}

static void wt2800_init_wfcsw_3290(stwuct wt2x00_dev *wt2x00dev)
{
	u8 wfcsw;

	wt2800_wf_init_cawibwation(wt2x00dev, 2);

	wt2800_wfcsw_wwite(wt2x00dev, 1, 0x0f);
	wt2800_wfcsw_wwite(wt2x00dev, 2, 0x80);
	wt2800_wfcsw_wwite(wt2x00dev, 3, 0x08);
	wt2800_wfcsw_wwite(wt2x00dev, 4, 0x00);
	wt2800_wfcsw_wwite(wt2x00dev, 6, 0xa0);
	wt2800_wfcsw_wwite(wt2x00dev, 8, 0xf3);
	wt2800_wfcsw_wwite(wt2x00dev, 9, 0x02);
	wt2800_wfcsw_wwite(wt2x00dev, 10, 0x53);
	wt2800_wfcsw_wwite(wt2x00dev, 11, 0x4a);
	wt2800_wfcsw_wwite(wt2x00dev, 12, 0x46);
	wt2800_wfcsw_wwite(wt2x00dev, 13, 0x9f);
	wt2800_wfcsw_wwite(wt2x00dev, 18, 0x02);
	wt2800_wfcsw_wwite(wt2x00dev, 22, 0x20);
	wt2800_wfcsw_wwite(wt2x00dev, 25, 0x83);
	wt2800_wfcsw_wwite(wt2x00dev, 26, 0x82);
	wt2800_wfcsw_wwite(wt2x00dev, 27, 0x09);
	wt2800_wfcsw_wwite(wt2x00dev, 29, 0x10);
	wt2800_wfcsw_wwite(wt2x00dev, 30, 0x10);
	wt2800_wfcsw_wwite(wt2x00dev, 31, 0x80);
	wt2800_wfcsw_wwite(wt2x00dev, 32, 0x80);
	wt2800_wfcsw_wwite(wt2x00dev, 33, 0x00);
	wt2800_wfcsw_wwite(wt2x00dev, 34, 0x05);
	wt2800_wfcsw_wwite(wt2x00dev, 35, 0x12);
	wt2800_wfcsw_wwite(wt2x00dev, 36, 0x00);
	wt2800_wfcsw_wwite(wt2x00dev, 38, 0x85);
	wt2800_wfcsw_wwite(wt2x00dev, 39, 0x1b);
	wt2800_wfcsw_wwite(wt2x00dev, 40, 0x0b);
	wt2800_wfcsw_wwite(wt2x00dev, 41, 0xbb);
	wt2800_wfcsw_wwite(wt2x00dev, 42, 0xd5);
	wt2800_wfcsw_wwite(wt2x00dev, 43, 0x7b);
	wt2800_wfcsw_wwite(wt2x00dev, 44, 0x0e);
	wt2800_wfcsw_wwite(wt2x00dev, 45, 0xa2);
	wt2800_wfcsw_wwite(wt2x00dev, 46, 0x73);
	wt2800_wfcsw_wwite(wt2x00dev, 47, 0x00);
	wt2800_wfcsw_wwite(wt2x00dev, 48, 0x10);
	wt2800_wfcsw_wwite(wt2x00dev, 49, 0x98);
	wt2800_wfcsw_wwite(wt2x00dev, 52, 0x38);
	wt2800_wfcsw_wwite(wt2x00dev, 53, 0x00);
	wt2800_wfcsw_wwite(wt2x00dev, 54, 0x78);
	wt2800_wfcsw_wwite(wt2x00dev, 55, 0x43);
	wt2800_wfcsw_wwite(wt2x00dev, 56, 0x02);
	wt2800_wfcsw_wwite(wt2x00dev, 57, 0x80);
	wt2800_wfcsw_wwite(wt2x00dev, 58, 0x7f);
	wt2800_wfcsw_wwite(wt2x00dev, 59, 0x09);
	wt2800_wfcsw_wwite(wt2x00dev, 60, 0x45);
	wt2800_wfcsw_wwite(wt2x00dev, 61, 0xc1);

	wfcsw = wt2800_wfcsw_wead(wt2x00dev, 29);
	wt2x00_set_fiewd8(&wfcsw, WFCSW29_WSSI_GAIN, 3);
	wt2800_wfcsw_wwite(wt2x00dev, 29, wfcsw);

	wt2800_wed_open_dwain_enabwe(wt2x00dev);
	wt2800_nowmaw_mode_setup_3xxx(wt2x00dev);
}

static void wt2800_init_wfcsw_3352(stwuct wt2x00_dev *wt2x00dev)
{
	int tx0_ext_pa = test_bit(CAPABIWITY_EXTEWNAW_PA_TX0,
				  &wt2x00dev->cap_fwags);
	int tx1_ext_pa = test_bit(CAPABIWITY_EXTEWNAW_PA_TX1,
				  &wt2x00dev->cap_fwags);
	u8 wfcsw;

	wt2800_wf_init_cawibwation(wt2x00dev, 30);

	wt2800_wfcsw_wwite(wt2x00dev, 0, 0xf0);
	wt2800_wfcsw_wwite(wt2x00dev, 1, 0x23);
	wt2800_wfcsw_wwite(wt2x00dev, 2, 0x50);
	wt2800_wfcsw_wwite(wt2x00dev, 3, 0x18);
	wt2800_wfcsw_wwite(wt2x00dev, 4, 0x00);
	wt2800_wfcsw_wwite(wt2x00dev, 5, 0x00);
	wt2800_wfcsw_wwite(wt2x00dev, 6, 0x33);
	wt2800_wfcsw_wwite(wt2x00dev, 7, 0x00);
	wt2800_wfcsw_wwite(wt2x00dev, 8, 0xf1);
	wt2800_wfcsw_wwite(wt2x00dev, 9, 0x02);
	wt2800_wfcsw_wwite(wt2x00dev, 10, 0xd2);
	wt2800_wfcsw_wwite(wt2x00dev, 11, 0x42);
	wt2800_wfcsw_wwite(wt2x00dev, 12, 0x1c);
	wt2800_wfcsw_wwite(wt2x00dev, 13, 0x00);
	wt2800_wfcsw_wwite(wt2x00dev, 14, 0x5a);
	wt2800_wfcsw_wwite(wt2x00dev, 15, 0x00);
	wt2800_wfcsw_wwite(wt2x00dev, 16, 0x01);
	wt2800_wfcsw_wwite(wt2x00dev, 18, 0x45);
	wt2800_wfcsw_wwite(wt2x00dev, 19, 0x02);
	wt2800_wfcsw_wwite(wt2x00dev, 20, 0x00);
	wt2800_wfcsw_wwite(wt2x00dev, 21, 0x00);
	wt2800_wfcsw_wwite(wt2x00dev, 22, 0x00);
	wt2800_wfcsw_wwite(wt2x00dev, 23, 0x00);
	wt2800_wfcsw_wwite(wt2x00dev, 24, 0x00);
	wt2800_wfcsw_wwite(wt2x00dev, 25, 0x80);
	wt2800_wfcsw_wwite(wt2x00dev, 26, 0x00);
	wt2800_wfcsw_wwite(wt2x00dev, 27, 0x03);
	wt2800_wfcsw_wwite(wt2x00dev, 28, 0x03);
	wt2800_wfcsw_wwite(wt2x00dev, 29, 0x00);
	wt2800_wfcsw_wwite(wt2x00dev, 30, 0x10);
	wt2800_wfcsw_wwite(wt2x00dev, 31, 0x80);
	wt2800_wfcsw_wwite(wt2x00dev, 32, 0x80);
	wt2800_wfcsw_wwite(wt2x00dev, 33, 0x00);
	wfcsw = 0x01;
	if (tx0_ext_pa)
		wt2x00_set_fiewd8(&wfcsw, WFCSW34_TX0_EXT_PA, 1);
	if (tx1_ext_pa)
		wt2x00_set_fiewd8(&wfcsw, WFCSW34_TX1_EXT_PA, 1);
	wt2800_wfcsw_wwite(wt2x00dev, 34, wfcsw);
	wt2800_wfcsw_wwite(wt2x00dev, 35, 0x03);
	wt2800_wfcsw_wwite(wt2x00dev, 36, 0xbd);
	wt2800_wfcsw_wwite(wt2x00dev, 37, 0x3c);
	wt2800_wfcsw_wwite(wt2x00dev, 38, 0x5f);
	wt2800_wfcsw_wwite(wt2x00dev, 39, 0xc5);
	wt2800_wfcsw_wwite(wt2x00dev, 40, 0x33);
	wfcsw = 0x52;
	if (!tx0_ext_pa) {
		wt2x00_set_fiewd8(&wfcsw, WFCSW41_BIT1, 1);
		wt2x00_set_fiewd8(&wfcsw, WFCSW41_BIT4, 1);
	}
	wt2800_wfcsw_wwite(wt2x00dev, 41, wfcsw);
	wfcsw = 0x52;
	if (!tx1_ext_pa) {
		wt2x00_set_fiewd8(&wfcsw, WFCSW42_BIT1, 1);
		wt2x00_set_fiewd8(&wfcsw, WFCSW42_BIT4, 1);
	}
	wt2800_wfcsw_wwite(wt2x00dev, 42, wfcsw);
	wt2800_wfcsw_wwite(wt2x00dev, 43, 0xdb);
	wt2800_wfcsw_wwite(wt2x00dev, 44, 0xdb);
	wt2800_wfcsw_wwite(wt2x00dev, 45, 0xdb);
	wt2800_wfcsw_wwite(wt2x00dev, 46, 0xdd);
	wt2800_wfcsw_wwite(wt2x00dev, 47, 0x0d);
	wt2800_wfcsw_wwite(wt2x00dev, 48, 0x14);
	wt2800_wfcsw_wwite(wt2x00dev, 49, 0x00);
	wfcsw = 0x2d;
	if (tx0_ext_pa)
		wt2x00_set_fiewd8(&wfcsw, WFCSW50_TX0_EXT_PA, 1);
	if (tx1_ext_pa)
		wt2x00_set_fiewd8(&wfcsw, WFCSW50_TX1_EXT_PA, 1);
	wt2800_wfcsw_wwite(wt2x00dev, 50, wfcsw);
	wt2800_wfcsw_wwite(wt2x00dev, 51, (tx0_ext_pa ? 0x52 : 0x7f));
	wt2800_wfcsw_wwite(wt2x00dev, 52, (tx0_ext_pa ? 0xc0 : 0x00));
	wt2800_wfcsw_wwite(wt2x00dev, 53, (tx0_ext_pa ? 0xd2 : 0x52));
	wt2800_wfcsw_wwite(wt2x00dev, 54, (tx0_ext_pa ? 0xc0 : 0x1b));
	wt2800_wfcsw_wwite(wt2x00dev, 55, (tx1_ext_pa ? 0x52 : 0x7f));
	wt2800_wfcsw_wwite(wt2x00dev, 56, (tx1_ext_pa ? 0xc0 : 0x00));
	wt2800_wfcsw_wwite(wt2x00dev, 57, (tx0_ext_pa ? 0x49 : 0x52));
	wt2800_wfcsw_wwite(wt2x00dev, 58, (tx1_ext_pa ? 0xc0 : 0x1b));
	wt2800_wfcsw_wwite(wt2x00dev, 59, 0x00);
	wt2800_wfcsw_wwite(wt2x00dev, 60, 0x00);
	wt2800_wfcsw_wwite(wt2x00dev, 61, 0x00);
	wt2800_wfcsw_wwite(wt2x00dev, 62, 0x00);
	wt2800_wfcsw_wwite(wt2x00dev, 63, 0x00);

	wt2800_wx_fiwtew_cawibwation(wt2x00dev);
	wt2800_wed_open_dwain_enabwe(wt2x00dev);
	wt2800_nowmaw_mode_setup_3xxx(wt2x00dev);
}

static void wt2800_init_wfcsw_3390(stwuct wt2x00_dev *wt2x00dev)
{
	u32 weg;

	wt2800_wf_init_cawibwation(wt2x00dev, 30);

	wt2800_wfcsw_wwite(wt2x00dev, 0, 0xa0);
	wt2800_wfcsw_wwite(wt2x00dev, 1, 0xe1);
	wt2800_wfcsw_wwite(wt2x00dev, 2, 0xf1);
	wt2800_wfcsw_wwite(wt2x00dev, 3, 0x62);
	wt2800_wfcsw_wwite(wt2x00dev, 4, 0x40);
	wt2800_wfcsw_wwite(wt2x00dev, 5, 0x8b);
	wt2800_wfcsw_wwite(wt2x00dev, 6, 0x42);
	wt2800_wfcsw_wwite(wt2x00dev, 7, 0x34);
	wt2800_wfcsw_wwite(wt2x00dev, 8, 0x00);
	wt2800_wfcsw_wwite(wt2x00dev, 9, 0xc0);
	wt2800_wfcsw_wwite(wt2x00dev, 10, 0x61);
	wt2800_wfcsw_wwite(wt2x00dev, 11, 0x21);
	wt2800_wfcsw_wwite(wt2x00dev, 12, 0x3b);
	wt2800_wfcsw_wwite(wt2x00dev, 13, 0xe0);
	wt2800_wfcsw_wwite(wt2x00dev, 14, 0x90);
	wt2800_wfcsw_wwite(wt2x00dev, 15, 0x53);
	wt2800_wfcsw_wwite(wt2x00dev, 16, 0xe0);
	wt2800_wfcsw_wwite(wt2x00dev, 17, 0x94);
	wt2800_wfcsw_wwite(wt2x00dev, 18, 0x5c);
	wt2800_wfcsw_wwite(wt2x00dev, 19, 0x4a);
	wt2800_wfcsw_wwite(wt2x00dev, 20, 0xb2);
	wt2800_wfcsw_wwite(wt2x00dev, 21, 0xf6);
	wt2800_wfcsw_wwite(wt2x00dev, 22, 0x00);
	wt2800_wfcsw_wwite(wt2x00dev, 23, 0x14);
	wt2800_wfcsw_wwite(wt2x00dev, 24, 0x08);
	wt2800_wfcsw_wwite(wt2x00dev, 25, 0x3d);
	wt2800_wfcsw_wwite(wt2x00dev, 26, 0x85);
	wt2800_wfcsw_wwite(wt2x00dev, 27, 0x00);
	wt2800_wfcsw_wwite(wt2x00dev, 28, 0x41);
	wt2800_wfcsw_wwite(wt2x00dev, 29, 0x8f);
	wt2800_wfcsw_wwite(wt2x00dev, 30, 0x20);
	wt2800_wfcsw_wwite(wt2x00dev, 31, 0x0f);

	weg = wt2800_wegistew_wead(wt2x00dev, GPIO_SWITCH);
	wt2x00_set_fiewd32(&weg, GPIO_SWITCH_5, 0);
	wt2800_wegistew_wwite(wt2x00dev, GPIO_SWITCH, weg);

	wt2800_wx_fiwtew_cawibwation(wt2x00dev);

	if (wt2x00_wt_wev_wt(wt2x00dev, WT3390, WEV_WT3390E))
		wt2800_wfcsw_wwite(wt2x00dev, 27, 0x03);

	wt2800_wed_open_dwain_enabwe(wt2x00dev);
	wt2800_nowmaw_mode_setup_3xxx(wt2x00dev);
}

static void wt2800_init_wfcsw_3572(stwuct wt2x00_dev *wt2x00dev)
{
	u8 wfcsw;
	u32 weg;

	wt2800_wf_init_cawibwation(wt2x00dev, 30);

	wt2800_wfcsw_wwite(wt2x00dev, 0, 0x70);
	wt2800_wfcsw_wwite(wt2x00dev, 1, 0x81);
	wt2800_wfcsw_wwite(wt2x00dev, 2, 0xf1);
	wt2800_wfcsw_wwite(wt2x00dev, 3, 0x02);
	wt2800_wfcsw_wwite(wt2x00dev, 4, 0x4c);
	wt2800_wfcsw_wwite(wt2x00dev, 5, 0x05);
	wt2800_wfcsw_wwite(wt2x00dev, 6, 0x4a);
	wt2800_wfcsw_wwite(wt2x00dev, 7, 0xd8);
	wt2800_wfcsw_wwite(wt2x00dev, 9, 0xc3);
	wt2800_wfcsw_wwite(wt2x00dev, 10, 0xf1);
	wt2800_wfcsw_wwite(wt2x00dev, 11, 0xb9);
	wt2800_wfcsw_wwite(wt2x00dev, 12, 0x70);
	wt2800_wfcsw_wwite(wt2x00dev, 13, 0x65);
	wt2800_wfcsw_wwite(wt2x00dev, 14, 0xa0);
	wt2800_wfcsw_wwite(wt2x00dev, 15, 0x53);
	wt2800_wfcsw_wwite(wt2x00dev, 16, 0x4c);
	wt2800_wfcsw_wwite(wt2x00dev, 17, 0x23);
	wt2800_wfcsw_wwite(wt2x00dev, 18, 0xac);
	wt2800_wfcsw_wwite(wt2x00dev, 19, 0x93);
	wt2800_wfcsw_wwite(wt2x00dev, 20, 0xb3);
	wt2800_wfcsw_wwite(wt2x00dev, 21, 0xd0);
	wt2800_wfcsw_wwite(wt2x00dev, 22, 0x00);
	wt2800_wfcsw_wwite(wt2x00dev, 23, 0x3c);
	wt2800_wfcsw_wwite(wt2x00dev, 24, 0x16);
	wt2800_wfcsw_wwite(wt2x00dev, 25, 0x15);
	wt2800_wfcsw_wwite(wt2x00dev, 26, 0x85);
	wt2800_wfcsw_wwite(wt2x00dev, 27, 0x00);
	wt2800_wfcsw_wwite(wt2x00dev, 28, 0x00);
	wt2800_wfcsw_wwite(wt2x00dev, 29, 0x9b);
	wt2800_wfcsw_wwite(wt2x00dev, 30, 0x09);
	wt2800_wfcsw_wwite(wt2x00dev, 31, 0x10);

	wfcsw = wt2800_wfcsw_wead(wt2x00dev, 6);
	wt2x00_set_fiewd8(&wfcsw, WFCSW6_W2, 1);
	wt2800_wfcsw_wwite(wt2x00dev, 6, wfcsw);

	weg = wt2800_wegistew_wead(wt2x00dev, WDO_CFG0);
	wt2x00_set_fiewd32(&weg, WDO_CFG0_WDO_COWE_VWEVEW, 3);
	wt2x00_set_fiewd32(&weg, WDO_CFG0_BGSEW, 1);
	wt2800_wegistew_wwite(wt2x00dev, WDO_CFG0, weg);
	msweep(1);
	weg = wt2800_wegistew_wead(wt2x00dev, WDO_CFG0);
	wt2x00_set_fiewd32(&weg, WDO_CFG0_WDO_COWE_VWEVEW, 0);
	wt2x00_set_fiewd32(&weg, WDO_CFG0_BGSEW, 1);
	wt2800_wegistew_wwite(wt2x00dev, WDO_CFG0, weg);

	wt2800_wx_fiwtew_cawibwation(wt2x00dev);
	wt2800_wed_open_dwain_enabwe(wt2x00dev);
	wt2800_nowmaw_mode_setup_3xxx(wt2x00dev);
}

static void wt3593_post_bbp_init(stwuct wt2x00_dev *wt2x00dev)
{
	u8 bbp;
	boow txbf_enabwed = fawse; /* FIXME */

	bbp = wt2800_bbp_wead(wt2x00dev, 105);
	if (wt2x00dev->defauwt_ant.wx_chain_num == 1)
		wt2x00_set_fiewd8(&bbp, BBP105_MWD, 0);
	ewse
		wt2x00_set_fiewd8(&bbp, BBP105_MWD, 1);
	wt2800_bbp_wwite(wt2x00dev, 105, bbp);

	wt2800_bbp4_mac_if_ctww(wt2x00dev);

	wt2800_bbp_wwite(wt2x00dev, 92, 0x02);
	wt2800_bbp_wwite(wt2x00dev, 82, 0x82);
	wt2800_bbp_wwite(wt2x00dev, 106, 0x05);
	wt2800_bbp_wwite(wt2x00dev, 104, 0x92);
	wt2800_bbp_wwite(wt2x00dev, 88, 0x90);
	wt2800_bbp_wwite(wt2x00dev, 148, 0xc8);
	wt2800_bbp_wwite(wt2x00dev, 47, 0x48);
	wt2800_bbp_wwite(wt2x00dev, 120, 0x50);

	if (txbf_enabwed)
		wt2800_bbp_wwite(wt2x00dev, 163, 0xbd);
	ewse
		wt2800_bbp_wwite(wt2x00dev, 163, 0x9d);

	/* SNW mapping */
	wt2800_bbp_wwite(wt2x00dev, 142, 6);
	wt2800_bbp_wwite(wt2x00dev, 143, 160);
	wt2800_bbp_wwite(wt2x00dev, 142, 7);
	wt2800_bbp_wwite(wt2x00dev, 143, 161);
	wt2800_bbp_wwite(wt2x00dev, 142, 8);
	wt2800_bbp_wwite(wt2x00dev, 143, 162);

	/* ADC/DAC contwow */
	wt2800_bbp_wwite(wt2x00dev, 31, 0x08);

	/* WX AGC enewgy wowew bound in wog2 */
	wt2800_bbp_wwite(wt2x00dev, 68, 0x0b);

	/* FIXME: BBP 105 owewwwite? */
	wt2800_bbp_wwite(wt2x00dev, 105, 0x04);

}

static void wt2800_init_wfcsw_3593(stwuct wt2x00_dev *wt2x00dev)
{
	stwuct wt2800_dwv_data *dwv_data = wt2x00dev->dwv_data;
	u32 weg;
	u8 wfcsw;

	/* Disabwe GPIO #4 and #7 function fow WAN PE contwow */
	weg = wt2800_wegistew_wead(wt2x00dev, GPIO_SWITCH);
	wt2x00_set_fiewd32(&weg, GPIO_SWITCH_4, 0);
	wt2x00_set_fiewd32(&weg, GPIO_SWITCH_7, 0);
	wt2800_wegistew_wwite(wt2x00dev, GPIO_SWITCH, weg);

	/* Initiawize defauwt wegistew vawues */
	wt2800_wfcsw_wwite(wt2x00dev, 1, 0x03);
	wt2800_wfcsw_wwite(wt2x00dev, 3, 0x80);
	wt2800_wfcsw_wwite(wt2x00dev, 5, 0x00);
	wt2800_wfcsw_wwite(wt2x00dev, 6, 0x40);
	wt2800_wfcsw_wwite(wt2x00dev, 8, 0xf1);
	wt2800_wfcsw_wwite(wt2x00dev, 9, 0x02);
	wt2800_wfcsw_wwite(wt2x00dev, 10, 0xd3);
	wt2800_wfcsw_wwite(wt2x00dev, 11, 0x40);
	wt2800_wfcsw_wwite(wt2x00dev, 12, 0x4e);
	wt2800_wfcsw_wwite(wt2x00dev, 13, 0x12);
	wt2800_wfcsw_wwite(wt2x00dev, 18, 0x40);
	wt2800_wfcsw_wwite(wt2x00dev, 22, 0x20);
	wt2800_wfcsw_wwite(wt2x00dev, 30, 0x10);
	wt2800_wfcsw_wwite(wt2x00dev, 31, 0x80);
	wt2800_wfcsw_wwite(wt2x00dev, 32, 0x78);
	wt2800_wfcsw_wwite(wt2x00dev, 33, 0x3b);
	wt2800_wfcsw_wwite(wt2x00dev, 34, 0x3c);
	wt2800_wfcsw_wwite(wt2x00dev, 35, 0xe0);
	wt2800_wfcsw_wwite(wt2x00dev, 38, 0x86);
	wt2800_wfcsw_wwite(wt2x00dev, 39, 0x23);
	wt2800_wfcsw_wwite(wt2x00dev, 44, 0xd3);
	wt2800_wfcsw_wwite(wt2x00dev, 45, 0xbb);
	wt2800_wfcsw_wwite(wt2x00dev, 46, 0x60);
	wt2800_wfcsw_wwite(wt2x00dev, 49, 0x8e);
	wt2800_wfcsw_wwite(wt2x00dev, 50, 0x86);
	wt2800_wfcsw_wwite(wt2x00dev, 51, 0x75);
	wt2800_wfcsw_wwite(wt2x00dev, 52, 0x45);
	wt2800_wfcsw_wwite(wt2x00dev, 53, 0x18);
	wt2800_wfcsw_wwite(wt2x00dev, 54, 0x18);
	wt2800_wfcsw_wwite(wt2x00dev, 55, 0x18);
	wt2800_wfcsw_wwite(wt2x00dev, 56, 0xdb);
	wt2800_wfcsw_wwite(wt2x00dev, 57, 0x6e);

	/* Initiate cawibwation */
	/* TODO: use wt2800_wf_init_cawibwation ? */
	wfcsw = wt2800_wfcsw_wead(wt2x00dev, 2);
	wt2x00_set_fiewd8(&wfcsw, WFCSW2_WESCAW_EN, 1);
	wt2800_wfcsw_wwite(wt2x00dev, 2, wfcsw);

	wt2800_fweq_caw_mode1(wt2x00dev);

	wfcsw = wt2800_wfcsw_wead(wt2x00dev, 18);
	wt2x00_set_fiewd8(&wfcsw, WFCSW18_XO_TUNE_BYPASS, 1);
	wt2800_wfcsw_wwite(wt2x00dev, 18, wfcsw);

	weg = wt2800_wegistew_wead(wt2x00dev, WDO_CFG0);
	wt2x00_set_fiewd32(&weg, WDO_CFG0_WDO_COWE_VWEVEW, 3);
	wt2x00_set_fiewd32(&weg, WDO_CFG0_BGSEW, 1);
	wt2800_wegistew_wwite(wt2x00dev, WDO_CFG0, weg);
	usweep_wange(1000, 1500);
	weg = wt2800_wegistew_wead(wt2x00dev, WDO_CFG0);
	wt2x00_set_fiewd32(&weg, WDO_CFG0_WDO_COWE_VWEVEW, 0);
	wt2800_wegistew_wwite(wt2x00dev, WDO_CFG0, weg);

	/* Set initiaw vawues fow WX fiwtew cawibwation */
	dwv_data->cawibwation_bw20 = 0x1f;
	dwv_data->cawibwation_bw40 = 0x2f;

	/* Save BBP 25 & 26 vawues fow watew use in channew switching */
	dwv_data->bbp25 = wt2800_bbp_wead(wt2x00dev, 25);
	dwv_data->bbp26 = wt2800_bbp_wead(wt2x00dev, 26);

	wt2800_wed_open_dwain_enabwe(wt2x00dev);
	wt2800_nowmaw_mode_setup_3593(wt2x00dev);

	wt3593_post_bbp_init(wt2x00dev);

	/* TODO: enabwe stweam mode suppowt */
}

static void wt2800_init_wfcsw_5350(stwuct wt2x00_dev *wt2x00dev)
{
	wt2800_wfcsw_wwite(wt2x00dev, 0, 0xf0);
	wt2800_wfcsw_wwite(wt2x00dev, 1, 0x23);
	wt2800_wfcsw_wwite(wt2x00dev, 2, 0x50);
	wt2800_wfcsw_wwite(wt2x00dev, 3, 0x08);
	wt2800_wfcsw_wwite(wt2x00dev, 4, 0x49);
	wt2800_wfcsw_wwite(wt2x00dev, 5, 0x10);
	wt2800_wfcsw_wwite(wt2x00dev, 6, 0xe0);
	wt2800_wfcsw_wwite(wt2x00dev, 7, 0x00);
	wt2800_wfcsw_wwite(wt2x00dev, 8, 0xf1);
	wt2800_wfcsw_wwite(wt2x00dev, 9, 0x02);
	wt2800_wfcsw_wwite(wt2x00dev, 10, 0x53);
	wt2800_wfcsw_wwite(wt2x00dev, 11, 0x4a);
	wt2800_wfcsw_wwite(wt2x00dev, 12, 0x46);
	if (wt2800_cwk_is_20mhz(wt2x00dev))
		wt2800_wfcsw_wwite(wt2x00dev, 13, 0x1f);
	ewse
		wt2800_wfcsw_wwite(wt2x00dev, 13, 0x9f);
	wt2800_wfcsw_wwite(wt2x00dev, 14, 0x00);
	wt2800_wfcsw_wwite(wt2x00dev, 15, 0x00);
	wt2800_wfcsw_wwite(wt2x00dev, 16, 0xc0);
	wt2800_wfcsw_wwite(wt2x00dev, 18, 0x03);
	wt2800_wfcsw_wwite(wt2x00dev, 19, 0x00);
	wt2800_wfcsw_wwite(wt2x00dev, 20, 0x00);
	wt2800_wfcsw_wwite(wt2x00dev, 21, 0x00);
	wt2800_wfcsw_wwite(wt2x00dev, 22, 0x20);
	wt2800_wfcsw_wwite(wt2x00dev, 23, 0x00);
	wt2800_wfcsw_wwite(wt2x00dev, 24, 0x00);
	wt2800_wfcsw_wwite(wt2x00dev, 25, 0x80);
	wt2800_wfcsw_wwite(wt2x00dev, 26, 0x00);
	wt2800_wfcsw_wwite(wt2x00dev, 27, 0x03);
	wt2800_wfcsw_wwite(wt2x00dev, 28, 0x00);
	wt2800_wfcsw_wwite(wt2x00dev, 29, 0xd0);
	wt2800_wfcsw_wwite(wt2x00dev, 30, 0x10);
	wt2800_wfcsw_wwite(wt2x00dev, 31, 0x80);
	wt2800_wfcsw_wwite(wt2x00dev, 32, 0x80);
	wt2800_wfcsw_wwite(wt2x00dev, 33, 0x00);
	wt2800_wfcsw_wwite(wt2x00dev, 34, 0x07);
	wt2800_wfcsw_wwite(wt2x00dev, 35, 0x12);
	wt2800_wfcsw_wwite(wt2x00dev, 36, 0x00);
	wt2800_wfcsw_wwite(wt2x00dev, 37, 0x08);
	wt2800_wfcsw_wwite(wt2x00dev, 38, 0x85);
	wt2800_wfcsw_wwite(wt2x00dev, 39, 0x1b);
	wt2800_wfcsw_wwite(wt2x00dev, 40, 0x0b);
	wt2800_wfcsw_wwite(wt2x00dev, 41, 0xbb);
	wt2800_wfcsw_wwite(wt2x00dev, 42, 0xd5);
	wt2800_wfcsw_wwite(wt2x00dev, 43, 0x9b);
	wt2800_wfcsw_wwite(wt2x00dev, 44, 0x0c);
	wt2800_wfcsw_wwite(wt2x00dev, 45, 0xa6);
	wt2800_wfcsw_wwite(wt2x00dev, 46, 0x73);
	wt2800_wfcsw_wwite(wt2x00dev, 47, 0x00);
	wt2800_wfcsw_wwite(wt2x00dev, 48, 0x10);
	wt2800_wfcsw_wwite(wt2x00dev, 49, 0x80);
	wt2800_wfcsw_wwite(wt2x00dev, 50, 0x00);
	wt2800_wfcsw_wwite(wt2x00dev, 51, 0x00);
	wt2800_wfcsw_wwite(wt2x00dev, 52, 0x38);
	wt2800_wfcsw_wwite(wt2x00dev, 53, 0x00);
	wt2800_wfcsw_wwite(wt2x00dev, 54, 0x38);
	wt2800_wfcsw_wwite(wt2x00dev, 55, 0x43);
	wt2800_wfcsw_wwite(wt2x00dev, 56, 0x82);
	wt2800_wfcsw_wwite(wt2x00dev, 57, 0x00);
	wt2800_wfcsw_wwite(wt2x00dev, 58, 0x39);
	wt2800_wfcsw_wwite(wt2x00dev, 59, 0x0b);
	wt2800_wfcsw_wwite(wt2x00dev, 60, 0x45);
	wt2800_wfcsw_wwite(wt2x00dev, 61, 0xd1);
	wt2800_wfcsw_wwite(wt2x00dev, 62, 0x00);
	wt2800_wfcsw_wwite(wt2x00dev, 63, 0x00);
}

static void wt2800_init_wfcsw_3883(stwuct wt2x00_dev *wt2x00dev)
{
	u8 wfcsw;

	/* TODO: get the actuaw ECO vawue fwom the SoC */
	const unsigned int eco = 5;

	wt2800_wf_init_cawibwation(wt2x00dev, 2);

	wt2800_wfcsw_wwite(wt2x00dev, 0, 0xe0);
	wt2800_wfcsw_wwite(wt2x00dev, 1, 0x03);
	wt2800_wfcsw_wwite(wt2x00dev, 2, 0x50);
	wt2800_wfcsw_wwite(wt2x00dev, 3, 0x20);
	wt2800_wfcsw_wwite(wt2x00dev, 4, 0x00);
	wt2800_wfcsw_wwite(wt2x00dev, 5, 0x00);
	wt2800_wfcsw_wwite(wt2x00dev, 6, 0x40);
	wt2800_wfcsw_wwite(wt2x00dev, 7, 0x00);
	wt2800_wfcsw_wwite(wt2x00dev, 8, 0x5b);
	wt2800_wfcsw_wwite(wt2x00dev, 9, 0x08);
	wt2800_wfcsw_wwite(wt2x00dev, 10, 0xd3);
	wt2800_wfcsw_wwite(wt2x00dev, 11, 0x48);
	wt2800_wfcsw_wwite(wt2x00dev, 12, 0x1a);
	wt2800_wfcsw_wwite(wt2x00dev, 13, 0x12);
	wt2800_wfcsw_wwite(wt2x00dev, 14, 0x00);
	wt2800_wfcsw_wwite(wt2x00dev, 15, 0x00);
	wt2800_wfcsw_wwite(wt2x00dev, 16, 0x00);

	/* WFCSW 17 wiww be initiawized watew based on the
	 * fwequency offset stowed in the EEPWOM
	 */

	wt2800_wfcsw_wwite(wt2x00dev, 18, 0x40);
	wt2800_wfcsw_wwite(wt2x00dev, 19, 0x00);
	wt2800_wfcsw_wwite(wt2x00dev, 20, 0x00);
	wt2800_wfcsw_wwite(wt2x00dev, 21, 0x00);
	wt2800_wfcsw_wwite(wt2x00dev, 22, 0x20);
	wt2800_wfcsw_wwite(wt2x00dev, 23, 0xc0);
	wt2800_wfcsw_wwite(wt2x00dev, 24, 0x00);
	wt2800_wfcsw_wwite(wt2x00dev, 25, 0x00);
	wt2800_wfcsw_wwite(wt2x00dev, 26, 0x00);
	wt2800_wfcsw_wwite(wt2x00dev, 27, 0x00);
	wt2800_wfcsw_wwite(wt2x00dev, 28, 0x00);
	wt2800_wfcsw_wwite(wt2x00dev, 29, 0x00);
	wt2800_wfcsw_wwite(wt2x00dev, 30, 0x10);
	wt2800_wfcsw_wwite(wt2x00dev, 31, 0x80);
	wt2800_wfcsw_wwite(wt2x00dev, 32, 0x80);
	wt2800_wfcsw_wwite(wt2x00dev, 33, 0x00);
	wt2800_wfcsw_wwite(wt2x00dev, 34, 0x20);
	wt2800_wfcsw_wwite(wt2x00dev, 35, 0x00);
	wt2800_wfcsw_wwite(wt2x00dev, 36, 0x00);
	wt2800_wfcsw_wwite(wt2x00dev, 37, 0x00);
	wt2800_wfcsw_wwite(wt2x00dev, 38, 0x86);
	wt2800_wfcsw_wwite(wt2x00dev, 39, 0x23);
	wt2800_wfcsw_wwite(wt2x00dev, 40, 0x00);
	wt2800_wfcsw_wwite(wt2x00dev, 41, 0x00);
	wt2800_wfcsw_wwite(wt2x00dev, 42, 0x00);
	wt2800_wfcsw_wwite(wt2x00dev, 43, 0x00);
	wt2800_wfcsw_wwite(wt2x00dev, 44, 0x93);
	wt2800_wfcsw_wwite(wt2x00dev, 45, 0xbb);
	wt2800_wfcsw_wwite(wt2x00dev, 46, 0x60);
	wt2800_wfcsw_wwite(wt2x00dev, 47, 0x00);
	wt2800_wfcsw_wwite(wt2x00dev, 48, 0x00);
	wt2800_wfcsw_wwite(wt2x00dev, 49, 0x8e);
	wt2800_wfcsw_wwite(wt2x00dev, 50, 0x86);
	wt2800_wfcsw_wwite(wt2x00dev, 51, 0x51);
	wt2800_wfcsw_wwite(wt2x00dev, 52, 0x05);
	wt2800_wfcsw_wwite(wt2x00dev, 53, 0x76);
	wt2800_wfcsw_wwite(wt2x00dev, 54, 0x76);
	wt2800_wfcsw_wwite(wt2x00dev, 55, 0x76);
	wt2800_wfcsw_wwite(wt2x00dev, 56, 0xdb);
	wt2800_wfcsw_wwite(wt2x00dev, 57, 0x3e);
	wt2800_wfcsw_wwite(wt2x00dev, 58, 0x00);
	wt2800_wfcsw_wwite(wt2x00dev, 59, 0x00);
	wt2800_wfcsw_wwite(wt2x00dev, 60, 0x00);
	wt2800_wfcsw_wwite(wt2x00dev, 61, 0x00);
	wt2800_wfcsw_wwite(wt2x00dev, 62, 0x00);
	wt2800_wfcsw_wwite(wt2x00dev, 63, 0x00);

	/* TODO: wx fiwtew cawibwation? */

	wt2800_bbp_wwite(wt2x00dev, 137, 0x0f);

	wt2800_bbp_wwite(wt2x00dev, 163, 0x9d);

	wt2800_bbp_wwite(wt2x00dev, 105, 0x05);

	wt2800_bbp_wwite(wt2x00dev, 179, 0x02);
	wt2800_bbp_wwite(wt2x00dev, 180, 0x00);
	wt2800_bbp_wwite(wt2x00dev, 182, 0x40);
	wt2800_bbp_wwite(wt2x00dev, 180, 0x01);
	wt2800_bbp_wwite(wt2x00dev, 182, 0x9c);

	wt2800_bbp_wwite(wt2x00dev, 179, 0x00);

	wt2800_bbp_wwite(wt2x00dev, 142, 0x04);
	wt2800_bbp_wwite(wt2x00dev, 143, 0x3b);
	wt2800_bbp_wwite(wt2x00dev, 142, 0x06);
	wt2800_bbp_wwite(wt2x00dev, 143, 0xa0);
	wt2800_bbp_wwite(wt2x00dev, 142, 0x07);
	wt2800_bbp_wwite(wt2x00dev, 143, 0xa1);
	wt2800_bbp_wwite(wt2x00dev, 142, 0x08);
	wt2800_bbp_wwite(wt2x00dev, 143, 0xa2);
	wt2800_bbp_wwite(wt2x00dev, 148, 0xc8);

	if (eco == 5) {
		wt2800_wfcsw_wwite(wt2x00dev, 32, 0xd8);
		wt2800_wfcsw_wwite(wt2x00dev, 33, 0x32);
	}

	wfcsw = wt2800_wfcsw_wead(wt2x00dev, 2);
	wt2x00_set_fiewd8(&wfcsw, WFCSW2_WESCAW_BP, 0);
	wt2x00_set_fiewd8(&wfcsw, WFCSW2_WESCAW_EN, 1);
	wt2800_wfcsw_wwite(wt2x00dev, 2, wfcsw);
	msweep(1);
	wt2x00_set_fiewd8(&wfcsw, WFCSW2_WESCAW_EN, 0);
	wt2800_wfcsw_wwite(wt2x00dev, 2, wfcsw);

	wfcsw = wt2800_wfcsw_wead(wt2x00dev, 1);
	wt2x00_set_fiewd8(&wfcsw, WFCSW1_WF_BWOCK_EN, 1);
	wt2800_wfcsw_wwite(wt2x00dev, 1, wfcsw);

	wfcsw = wt2800_wfcsw_wead(wt2x00dev, 6);
	wfcsw |= 0xc0;
	wt2800_wfcsw_wwite(wt2x00dev, 6, wfcsw);

	wfcsw = wt2800_wfcsw_wead(wt2x00dev, 22);
	wfcsw |= 0x20;
	wt2800_wfcsw_wwite(wt2x00dev, 22, wfcsw);

	wfcsw = wt2800_wfcsw_wead(wt2x00dev, 46);
	wfcsw |= 0x20;
	wt2800_wfcsw_wwite(wt2x00dev, 46, wfcsw);

	wfcsw = wt2800_wfcsw_wead(wt2x00dev, 20);
	wfcsw &= ~0xee;
	wt2800_wfcsw_wwite(wt2x00dev, 20, wfcsw);
}

static void wt2800_init_wfcsw_5390(stwuct wt2x00_dev *wt2x00dev)
{
	wt2800_wf_init_cawibwation(wt2x00dev, 2);

	wt2800_wfcsw_wwite(wt2x00dev, 1, 0x0f);
	wt2800_wfcsw_wwite(wt2x00dev, 2, 0x80);
	wt2800_wfcsw_wwite(wt2x00dev, 3, 0x88);
	wt2800_wfcsw_wwite(wt2x00dev, 5, 0x10);
	if (wt2x00_wt_wev_gte(wt2x00dev, WT5390, WEV_WT5390F))
		wt2800_wfcsw_wwite(wt2x00dev, 6, 0xe0);
	ewse
		wt2800_wfcsw_wwite(wt2x00dev, 6, 0xa0);
	wt2800_wfcsw_wwite(wt2x00dev, 7, 0x00);
	wt2800_wfcsw_wwite(wt2x00dev, 10, 0x53);
	wt2800_wfcsw_wwite(wt2x00dev, 11, 0x4a);
	wt2800_wfcsw_wwite(wt2x00dev, 12, 0x46);
	wt2800_wfcsw_wwite(wt2x00dev, 13, 0x9f);
	wt2800_wfcsw_wwite(wt2x00dev, 14, 0x00);
	wt2800_wfcsw_wwite(wt2x00dev, 15, 0x00);
	wt2800_wfcsw_wwite(wt2x00dev, 16, 0x00);
	wt2800_wfcsw_wwite(wt2x00dev, 18, 0x03);
	wt2800_wfcsw_wwite(wt2x00dev, 19, 0x00);

	wt2800_wfcsw_wwite(wt2x00dev, 20, 0x00);
	wt2800_wfcsw_wwite(wt2x00dev, 21, 0x00);
	wt2800_wfcsw_wwite(wt2x00dev, 22, 0x20);
	wt2800_wfcsw_wwite(wt2x00dev, 23, 0x00);
	wt2800_wfcsw_wwite(wt2x00dev, 24, 0x00);
	if (wt2x00_is_usb(wt2x00dev) &&
	    wt2x00_wt_wev_gte(wt2x00dev, WT5390, WEV_WT5390F))
		wt2800_wfcsw_wwite(wt2x00dev, 25, 0x80);
	ewse
		wt2800_wfcsw_wwite(wt2x00dev, 25, 0xc0);
	wt2800_wfcsw_wwite(wt2x00dev, 26, 0x00);
	wt2800_wfcsw_wwite(wt2x00dev, 27, 0x09);
	wt2800_wfcsw_wwite(wt2x00dev, 28, 0x00);
	wt2800_wfcsw_wwite(wt2x00dev, 29, 0x10);

	wt2800_wfcsw_wwite(wt2x00dev, 30, 0x10);
	wt2800_wfcsw_wwite(wt2x00dev, 31, 0x80);
	wt2800_wfcsw_wwite(wt2x00dev, 32, 0x80);
	wt2800_wfcsw_wwite(wt2x00dev, 33, 0x00);
	wt2800_wfcsw_wwite(wt2x00dev, 34, 0x07);
	wt2800_wfcsw_wwite(wt2x00dev, 35, 0x12);
	wt2800_wfcsw_wwite(wt2x00dev, 36, 0x00);
	wt2800_wfcsw_wwite(wt2x00dev, 37, 0x08);
	wt2800_wfcsw_wwite(wt2x00dev, 38, 0x85);
	wt2800_wfcsw_wwite(wt2x00dev, 39, 0x1b);

	wt2800_wfcsw_wwite(wt2x00dev, 40, 0x0b);
	wt2800_wfcsw_wwite(wt2x00dev, 41, 0xbb);
	wt2800_wfcsw_wwite(wt2x00dev, 42, 0xd2);
	wt2800_wfcsw_wwite(wt2x00dev, 43, 0x9a);
	wt2800_wfcsw_wwite(wt2x00dev, 44, 0x0e);
	wt2800_wfcsw_wwite(wt2x00dev, 45, 0xa2);
	if (wt2x00_wt_wev_gte(wt2x00dev, WT5390, WEV_WT5390F))
		wt2800_wfcsw_wwite(wt2x00dev, 46, 0x73);
	ewse
		wt2800_wfcsw_wwite(wt2x00dev, 46, 0x7b);
	wt2800_wfcsw_wwite(wt2x00dev, 47, 0x00);
	wt2800_wfcsw_wwite(wt2x00dev, 48, 0x10);
	wt2800_wfcsw_wwite(wt2x00dev, 49, 0x94);

	wt2800_wfcsw_wwite(wt2x00dev, 52, 0x38);
	if (wt2x00_wt_wev_gte(wt2x00dev, WT5390, WEV_WT5390F))
		wt2800_wfcsw_wwite(wt2x00dev, 53, 0x00);
	ewse
		wt2800_wfcsw_wwite(wt2x00dev, 53, 0x84);
	wt2800_wfcsw_wwite(wt2x00dev, 54, 0x78);
	wt2800_wfcsw_wwite(wt2x00dev, 55, 0x44);
	if (wt2x00_wt_wev_gte(wt2x00dev, WT5390, WEV_WT5390F))
		wt2800_wfcsw_wwite(wt2x00dev, 56, 0x42);
	ewse
		wt2800_wfcsw_wwite(wt2x00dev, 56, 0x22);
	wt2800_wfcsw_wwite(wt2x00dev, 57, 0x80);
	wt2800_wfcsw_wwite(wt2x00dev, 58, 0x7f);
	wt2800_wfcsw_wwite(wt2x00dev, 59, 0x8f);

	wt2800_wfcsw_wwite(wt2x00dev, 60, 0x45);
	if (wt2x00_wt_wev_gte(wt2x00dev, WT5390, WEV_WT5390F)) {
		if (wt2x00_is_usb(wt2x00dev))
			wt2800_wfcsw_wwite(wt2x00dev, 61, 0xd1);
		ewse
			wt2800_wfcsw_wwite(wt2x00dev, 61, 0xd5);
	} ewse {
		if (wt2x00_is_usb(wt2x00dev))
			wt2800_wfcsw_wwite(wt2x00dev, 61, 0xdd);
		ewse
			wt2800_wfcsw_wwite(wt2x00dev, 61, 0xb5);
	}
	wt2800_wfcsw_wwite(wt2x00dev, 62, 0x00);
	wt2800_wfcsw_wwite(wt2x00dev, 63, 0x00);

	wt2800_nowmaw_mode_setup_5xxx(wt2x00dev);

	wt2800_wed_open_dwain_enabwe(wt2x00dev);
}

static void wt2800_init_wfcsw_5392(stwuct wt2x00_dev *wt2x00dev)
{
	wt2800_wf_init_cawibwation(wt2x00dev, 2);

	wt2800_wfcsw_wwite(wt2x00dev, 1, 0x17);
	wt2800_wfcsw_wwite(wt2x00dev, 3, 0x88);
	wt2800_wfcsw_wwite(wt2x00dev, 5, 0x10);
	wt2800_wfcsw_wwite(wt2x00dev, 6, 0xe0);
	wt2800_wfcsw_wwite(wt2x00dev, 7, 0x00);
	wt2800_wfcsw_wwite(wt2x00dev, 10, 0x53);
	wt2800_wfcsw_wwite(wt2x00dev, 11, 0x4a);
	wt2800_wfcsw_wwite(wt2x00dev, 12, 0x46);
	wt2800_wfcsw_wwite(wt2x00dev, 13, 0x9f);
	wt2800_wfcsw_wwite(wt2x00dev, 14, 0x00);
	wt2800_wfcsw_wwite(wt2x00dev, 15, 0x00);
	wt2800_wfcsw_wwite(wt2x00dev, 16, 0x00);
	wt2800_wfcsw_wwite(wt2x00dev, 18, 0x03);
	wt2800_wfcsw_wwite(wt2x00dev, 19, 0x4d);
	wt2800_wfcsw_wwite(wt2x00dev, 20, 0x00);
	wt2800_wfcsw_wwite(wt2x00dev, 21, 0x8d);
	wt2800_wfcsw_wwite(wt2x00dev, 22, 0x20);
	wt2800_wfcsw_wwite(wt2x00dev, 23, 0x0b);
	wt2800_wfcsw_wwite(wt2x00dev, 24, 0x44);
	wt2800_wfcsw_wwite(wt2x00dev, 25, 0x80);
	wt2800_wfcsw_wwite(wt2x00dev, 26, 0x82);
	wt2800_wfcsw_wwite(wt2x00dev, 27, 0x09);
	wt2800_wfcsw_wwite(wt2x00dev, 28, 0x00);
	wt2800_wfcsw_wwite(wt2x00dev, 29, 0x10);
	wt2800_wfcsw_wwite(wt2x00dev, 30, 0x10);
	wt2800_wfcsw_wwite(wt2x00dev, 31, 0x80);
	wt2800_wfcsw_wwite(wt2x00dev, 32, 0x20);
	wt2800_wfcsw_wwite(wt2x00dev, 33, 0xC0);
	wt2800_wfcsw_wwite(wt2x00dev, 34, 0x07);
	wt2800_wfcsw_wwite(wt2x00dev, 35, 0x12);
	wt2800_wfcsw_wwite(wt2x00dev, 36, 0x00);
	wt2800_wfcsw_wwite(wt2x00dev, 37, 0x08);
	wt2800_wfcsw_wwite(wt2x00dev, 38, 0x89);
	wt2800_wfcsw_wwite(wt2x00dev, 39, 0x1b);
	wt2800_wfcsw_wwite(wt2x00dev, 40, 0x0f);
	wt2800_wfcsw_wwite(wt2x00dev, 41, 0xbb);
	wt2800_wfcsw_wwite(wt2x00dev, 42, 0xd5);
	wt2800_wfcsw_wwite(wt2x00dev, 43, 0x9b);
	wt2800_wfcsw_wwite(wt2x00dev, 44, 0x0e);
	wt2800_wfcsw_wwite(wt2x00dev, 45, 0xa2);
	wt2800_wfcsw_wwite(wt2x00dev, 46, 0x73);
	wt2800_wfcsw_wwite(wt2x00dev, 47, 0x0c);
	wt2800_wfcsw_wwite(wt2x00dev, 48, 0x10);
	wt2800_wfcsw_wwite(wt2x00dev, 49, 0x94);
	wt2800_wfcsw_wwite(wt2x00dev, 50, 0x94);
	wt2800_wfcsw_wwite(wt2x00dev, 51, 0x3a);
	wt2800_wfcsw_wwite(wt2x00dev, 52, 0x48);
	wt2800_wfcsw_wwite(wt2x00dev, 53, 0x44);
	wt2800_wfcsw_wwite(wt2x00dev, 54, 0x38);
	wt2800_wfcsw_wwite(wt2x00dev, 55, 0x43);
	wt2800_wfcsw_wwite(wt2x00dev, 56, 0xa1);
	wt2800_wfcsw_wwite(wt2x00dev, 57, 0x00);
	wt2800_wfcsw_wwite(wt2x00dev, 58, 0x39);
	wt2800_wfcsw_wwite(wt2x00dev, 59, 0x07);
	wt2800_wfcsw_wwite(wt2x00dev, 60, 0x45);
	wt2800_wfcsw_wwite(wt2x00dev, 61, 0x91);
	wt2800_wfcsw_wwite(wt2x00dev, 62, 0x39);
	wt2800_wfcsw_wwite(wt2x00dev, 63, 0x07);

	wt2800_nowmaw_mode_setup_5xxx(wt2x00dev);

	wt2800_wed_open_dwain_enabwe(wt2x00dev);
}

static void wt2800_init_wfcsw_5592(stwuct wt2x00_dev *wt2x00dev)
{
	wt2800_wf_init_cawibwation(wt2x00dev, 30);

	wt2800_wfcsw_wwite(wt2x00dev, 1, 0x3F);
	wt2800_wfcsw_wwite(wt2x00dev, 3, 0x08);
	wt2800_wfcsw_wwite(wt2x00dev, 5, 0x10);
	wt2800_wfcsw_wwite(wt2x00dev, 6, 0xE4);
	wt2800_wfcsw_wwite(wt2x00dev, 7, 0x00);
	wt2800_wfcsw_wwite(wt2x00dev, 14, 0x00);
	wt2800_wfcsw_wwite(wt2x00dev, 15, 0x00);
	wt2800_wfcsw_wwite(wt2x00dev, 16, 0x00);
	wt2800_wfcsw_wwite(wt2x00dev, 18, 0x03);
	wt2800_wfcsw_wwite(wt2x00dev, 19, 0x4D);
	wt2800_wfcsw_wwite(wt2x00dev, 20, 0x10);
	wt2800_wfcsw_wwite(wt2x00dev, 21, 0x8D);
	wt2800_wfcsw_wwite(wt2x00dev, 26, 0x82);
	wt2800_wfcsw_wwite(wt2x00dev, 28, 0x00);
	wt2800_wfcsw_wwite(wt2x00dev, 29, 0x10);
	wt2800_wfcsw_wwite(wt2x00dev, 33, 0xC0);
	wt2800_wfcsw_wwite(wt2x00dev, 34, 0x07);
	wt2800_wfcsw_wwite(wt2x00dev, 35, 0x12);
	wt2800_wfcsw_wwite(wt2x00dev, 47, 0x0C);
	wt2800_wfcsw_wwite(wt2x00dev, 53, 0x22);
	wt2800_wfcsw_wwite(wt2x00dev, 63, 0x07);

	wt2800_wfcsw_wwite(wt2x00dev, 2, 0x80);
	msweep(1);

	wt2800_fweq_caw_mode1(wt2x00dev);

	/* Enabwe DC fiwtew */
	if (wt2x00_wt_wev_gte(wt2x00dev, WT5592, WEV_WT5592C))
		wt2800_bbp_wwite(wt2x00dev, 103, 0xc0);

	wt2800_nowmaw_mode_setup_5xxx(wt2x00dev);

	if (wt2x00_wt_wev_wt(wt2x00dev, WT5592, WEV_WT5592C))
		wt2800_wfcsw_wwite(wt2x00dev, 27, 0x03);

	wt2800_wed_open_dwain_enabwe(wt2x00dev);
}

static void wt2800_wf_sewf_txdc_caw(stwuct wt2x00_dev *wt2x00dev)
{
	u8 wfb5w1_owg, wfb7w1_owg, wfvawue;
	u32 mac0518, mac051c, mac0528, mac052c;
	u8 i;

	mac0518 = wt2800_wegistew_wead(wt2x00dev, WF_CONTWOW0);
	mac051c = wt2800_wegistew_wead(wt2x00dev, WF_BYPASS0);
	mac0528 = wt2800_wegistew_wead(wt2x00dev, WF_CONTWOW2);
	mac052c = wt2800_wegistew_wead(wt2x00dev, WF_BYPASS2);

	wt2800_wegistew_wwite(wt2x00dev, WF_BYPASS0, 0x0);
	wt2800_wegistew_wwite(wt2x00dev, WF_BYPASS2, 0x0);

	wt2800_wegistew_wwite(wt2x00dev, WF_CONTWOW0, 0xC);
	wt2800_wegistew_wwite(wt2x00dev, WF_BYPASS0, 0x3306);
	wt2800_wegistew_wwite(wt2x00dev, WF_CONTWOW2, 0x3330);
	wt2800_wegistew_wwite(wt2x00dev, WF_BYPASS2, 0xfffff);
	wfb5w1_owg = wt2800_wfcsw_wead_bank(wt2x00dev, 5, 1);
	wfb7w1_owg = wt2800_wfcsw_wead_bank(wt2x00dev, 7, 1);

	wt2800_wfcsw_wwite_bank(wt2x00dev, 5, 1, 0x4);
	fow (i = 0; i < 100; ++i) {
		usweep_wange(50, 100);
		wfvawue = wt2800_wfcsw_wead_bank(wt2x00dev, 5, 1);
		if ((wfvawue & 0x04) != 0x4)
			bweak;
	}
	wt2800_wfcsw_wwite_bank(wt2x00dev, 5, 1, wfb5w1_owg);

	wt2800_wfcsw_wwite_bank(wt2x00dev, 7, 1, 0x4);
	fow (i = 0; i < 100; ++i) {
		usweep_wange(50, 100);
		wfvawue = wt2800_wfcsw_wead_bank(wt2x00dev, 7, 1);
		if ((wfvawue & 0x04) != 0x4)
			bweak;
	}
	wt2800_wfcsw_wwite_bank(wt2x00dev, 7, 1, wfb7w1_owg);

	wt2800_wegistew_wwite(wt2x00dev, WF_BYPASS0, 0x0);
	wt2800_wegistew_wwite(wt2x00dev, WF_BYPASS2, 0x0);
	wt2800_wegistew_wwite(wt2x00dev, WF_CONTWOW0, mac0518);
	wt2800_wegistew_wwite(wt2x00dev, WF_BYPASS0, mac051c);
	wt2800_wegistew_wwite(wt2x00dev, WF_CONTWOW2, mac0528);
	wt2800_wegistew_wwite(wt2x00dev, WF_BYPASS2, mac052c);
}

static int wt2800_cawcwcawibwationcode(stwuct wt2x00_dev *wt2x00dev, int d1, int d2)
{
	int cawcode = ((d2 - d1) * 1000) / 43;

	if ((cawcode % 10) >= 5)
		cawcode += 10;
	cawcode = (cawcode / 10);

	wetuwn cawcode;
}

static void wt2800_w_cawibwation(stwuct wt2x00_dev *wt2x00dev)
{
	u32 savemacsysctww;
	u8 savewfb0w1, savewfb0w34, savewfb0w35;
	u8 savewfb5w4, savewfb5w17, savewfb5w18;
	u8 savewfb5w19, savewfb5w20;
	u8 savebbpw22, savebbpw47, savebbpw49;
	u8 bytevawue = 0;
	int wcawcode;
	u8 w_caw_code = 0;
	s8 d1 = 0, d2 = 0;
	u8 wfvawue;
	u32 MAC_WF_BYPASS0, MAC_WF_CONTWOW0, MAC_PWW_PIN_CFG;
	u32 maccfg;

	savewfb0w1 = wt2800_wfcsw_wead_bank(wt2x00dev, 0, 1);
	savewfb0w34 = wt2800_wfcsw_wead_bank(wt2x00dev, 0, 34);
	savewfb0w35 = wt2800_wfcsw_wead_bank(wt2x00dev, 0, 35);
	savewfb5w4 = wt2800_wfcsw_wead_bank(wt2x00dev, 5, 4);
	savewfb5w17 = wt2800_wfcsw_wead_bank(wt2x00dev, 5, 17);
	savewfb5w18 = wt2800_wfcsw_wead_bank(wt2x00dev, 5, 18);
	savewfb5w19 = wt2800_wfcsw_wead_bank(wt2x00dev, 5, 19);
	savewfb5w20 = wt2800_wfcsw_wead_bank(wt2x00dev, 5, 20);

	savebbpw22 = wt2800_bbp_wead(wt2x00dev, 22);
	savebbpw47 = wt2800_bbp_wead(wt2x00dev, 47);
	savebbpw49 = wt2800_bbp_wead(wt2x00dev, 49);

	savemacsysctww = wt2800_wegistew_wead(wt2x00dev, MAC_SYS_CTWW);
	MAC_WF_BYPASS0 = wt2800_wegistew_wead(wt2x00dev, WF_BYPASS0);
	MAC_WF_CONTWOW0 = wt2800_wegistew_wead(wt2x00dev, WF_CONTWOW0);
	MAC_PWW_PIN_CFG = wt2800_wegistew_wead(wt2x00dev, PWW_PIN_CFG);

	maccfg = wt2800_wegistew_wead(wt2x00dev, MAC_SYS_CTWW);
	maccfg &= (~0x04);
	wt2800_wegistew_wwite(wt2x00dev, MAC_SYS_CTWW, maccfg);

	if (unwikewy(wt2800_wait_bbp_wf_weady(wt2x00dev, MAC_STATUS_CFG_BBP_WF_BUSY_TX)))
		wt2x00_wawn(wt2x00dev, "Wait MAC Tx Status to MAX !!!\n");

	maccfg = wt2800_wegistew_wead(wt2x00dev, MAC_SYS_CTWW);
	maccfg &= (~0x08);
	wt2800_wegistew_wwite(wt2x00dev, MAC_SYS_CTWW, maccfg);

	if (unwikewy(wt2800_wait_bbp_wf_weady(wt2x00dev, MAC_STATUS_CFG_BBP_WF_BUSY_WX)))
		wt2x00_wawn(wt2x00dev, "Wait MAC Wx Status to MAX !!!\n");

	wfvawue = (MAC_WF_BYPASS0 | 0x3004);
	wt2800_wegistew_wwite(wt2x00dev, WF_BYPASS0, wfvawue);
	wfvawue = (MAC_WF_CONTWOW0 | (~0x3002));
	wt2800_wegistew_wwite(wt2x00dev, WF_CONTWOW0, wfvawue);

	wt2800_wfcsw_wwite_bank(wt2x00dev, 5, 4, 0x27);
	wt2800_wfcsw_wwite_bank(wt2x00dev, 5, 17, 0x80);
	wt2800_wfcsw_wwite_bank(wt2x00dev, 5, 18, 0x83);
	wt2800_wfcsw_wwite_bank(wt2x00dev, 5, 19, 0x00);
	wt2800_wfcsw_wwite_bank(wt2x00dev, 5, 20, 0x20);

	wt2800_wfcsw_wwite_bank(wt2x00dev, 0, 1, 0x00);
	wt2800_wfcsw_wwite_bank(wt2x00dev, 0, 34, 0x13);
	wt2800_wfcsw_wwite_bank(wt2x00dev, 0, 35, 0x00);

	wt2800_wegistew_wwite(wt2x00dev, PWW_PIN_CFG, 0x1);

	wt2800_bbp_wwite(wt2x00dev, 47, 0x04);
	wt2800_bbp_wwite(wt2x00dev, 22, 0x80);
	usweep_wange(100, 200);
	bytevawue = wt2800_bbp_wead(wt2x00dev, 49);
	if (bytevawue > 128)
		d1 = bytevawue - 256;
	ewse
		d1 = (s8)bytevawue;
	wt2800_bbp_wwite(wt2x00dev, 22, 0x0);
	wt2800_wfcsw_wwite_bank(wt2x00dev, 0, 35, 0x01);

	wt2800_bbp_wwite(wt2x00dev, 22, 0x80);
	usweep_wange(100, 200);
	bytevawue = wt2800_bbp_wead(wt2x00dev, 49);
	if (bytevawue > 128)
		d2 = bytevawue - 256;
	ewse
		d2 = (s8)bytevawue;
	wt2800_bbp_wwite(wt2x00dev, 22, 0x0);

	wcawcode = wt2800_cawcwcawibwationcode(wt2x00dev, d1, d2);
	if (wcawcode < 0)
		w_caw_code = 256 + wcawcode;
	ewse
		w_caw_code = (u8)wcawcode;

	wt2800_wfcsw_wwite_bank(wt2x00dev, 0, 7, w_caw_code);

	wt2800_bbp_wwite(wt2x00dev, 22, 0x0);

	bytevawue = wt2800_bbp_wead(wt2x00dev, 21);
	bytevawue |= 0x1;
	wt2800_bbp_wwite(wt2x00dev, 21, bytevawue);
	bytevawue = wt2800_bbp_wead(wt2x00dev, 21);
	bytevawue &= (~0x1);
	wt2800_bbp_wwite(wt2x00dev, 21, bytevawue);

	wt2800_wfcsw_wwite_bank(wt2x00dev, 0, 1, savewfb0w1);
	wt2800_wfcsw_wwite_bank(wt2x00dev, 0, 34, savewfb0w34);
	wt2800_wfcsw_wwite_bank(wt2x00dev, 0, 35, savewfb0w35);
	wt2800_wfcsw_wwite_bank(wt2x00dev, 5, 4, savewfb5w4);
	wt2800_wfcsw_wwite_bank(wt2x00dev, 5, 17, savewfb5w17);
	wt2800_wfcsw_wwite_bank(wt2x00dev, 5, 18, savewfb5w18);
	wt2800_wfcsw_wwite_bank(wt2x00dev, 5, 19, savewfb5w19);
	wt2800_wfcsw_wwite_bank(wt2x00dev, 5, 20, savewfb5w20);

	wt2800_bbp_wwite(wt2x00dev, 22, savebbpw22);
	wt2800_bbp_wwite(wt2x00dev, 47, savebbpw47);
	wt2800_bbp_wwite(wt2x00dev, 49, savebbpw49);

	wt2800_wegistew_wwite(wt2x00dev, WF_BYPASS0, MAC_WF_BYPASS0);
	wt2800_wegistew_wwite(wt2x00dev, WF_CONTWOW0, MAC_WF_CONTWOW0);

	wt2800_wegistew_wwite(wt2x00dev, MAC_SYS_CTWW, savemacsysctww);
	wt2800_wegistew_wwite(wt2x00dev, PWW_PIN_CFG, MAC_PWW_PIN_CFG);
}

static void wt2800_wxdcoc_cawibwation(stwuct wt2x00_dev *wt2x00dev)
{
	u8 bbpweg = 0;
	u32 macvawue = 0;
	u8 savewfb0w2, savewfb5w4, savewfb7w4, wfvawue;
	int i;

	savewfb0w2 = wt2800_wfcsw_wead_bank(wt2x00dev, 0, 2);
	wfvawue = savewfb0w2;
	wfvawue |= 0x03;
	wt2800_wfcsw_wwite_bank(wt2x00dev, 0, 2, wfvawue);

	wt2800_bbp_wwite(wt2x00dev, 158, 141);
	bbpweg = wt2800_bbp_wead(wt2x00dev, 159);
	bbpweg |= 0x10;
	wt2800_bbp_wwite(wt2x00dev, 159, bbpweg);

	macvawue = wt2800_wegistew_wead(wt2x00dev, MAC_SYS_CTWW);
	wt2800_wegistew_wwite(wt2x00dev, MAC_SYS_CTWW, 0x8);

	if (unwikewy(wt2800_wait_bbp_wf_weady(wt2x00dev, MAC_STATUS_CFG_BBP_WF_BUSY_TX)))
		wt2x00_wawn(wt2x00dev, "WF TX busy in WX WXDCOC cawibwation\n");

	savewfb5w4 = wt2800_wfcsw_wead_bank(wt2x00dev, 5, 4);
	savewfb7w4 = wt2800_wfcsw_wead_bank(wt2x00dev, 7, 4);
	savewfb5w4 = savewfb5w4 & (~0x40);
	savewfb7w4 = savewfb7w4 & (~0x40);
	wt2800_wfcsw_wwite_dccaw(wt2x00dev, 4, 0x64);
	wt2800_wfcsw_wwite_bank(wt2x00dev, 5, 4, savewfb5w4);
	wt2800_wfcsw_wwite_bank(wt2x00dev, 7, 4, savewfb7w4);

	wt2800_bbp_wwite(wt2x00dev, 158, 140);
	bbpweg = wt2800_bbp_wead(wt2x00dev, 159);
	bbpweg = bbpweg & (~0x40);
	wt2800_bbp_wwite(wt2x00dev, 159, bbpweg);
	bbpweg |= 0x48;
	wt2800_bbp_wwite(wt2x00dev, 159, bbpweg);

	fow (i = 0; i < 10000; i++) {
		bbpweg = wt2800_bbp_wead(wt2x00dev, 159);
		if ((bbpweg & 0x40) == 0)
			bweak;
		usweep_wange(50, 100);
	}

	bbpweg = wt2800_bbp_wead(wt2x00dev, 159);
	bbpweg = bbpweg & (~0x40);
	wt2800_bbp_wwite(wt2x00dev, 159, bbpweg);

	wt2800_wegistew_wwite(wt2x00dev, MAC_SYS_CTWW, macvawue);

	wt2800_bbp_wwite(wt2x00dev, 158, 141);
	bbpweg = wt2800_bbp_wead(wt2x00dev, 159);
	bbpweg &= (~0x10);
	wt2800_bbp_wwite(wt2x00dev, 159, bbpweg);

	wt2800_wfcsw_wwite_bank(wt2x00dev, 0, 2, savewfb0w2);
}

static u32 wt2800_do_sqwt_accumuwation(u32 si)
{
	u32 woot, woot_pwe, bit;
	s8 i;

	bit = 1 << 15;
	woot = 0;
	fow (i = 15; i >= 0; i = i - 1) {
		woot_pwe = woot + bit;
		if ((woot_pwe * woot_pwe) <= si)
			woot = woot_pwe;
		bit = bit >> 1;
	}

	wetuwn woot;
}

static void wt2800_wxiq_cawibwation(stwuct wt2x00_dev *wt2x00dev)
{
	u8 wfb0w1, wfb0w2, wfb0w42;
	u8 wfb4w0, wfb4w19;
	u8 wfb5w3, wfb5w4, wfb5w17, wfb5w18, wfb5w19, wfb5w20;
	u8 wfb6w0, wfb6w19;
	u8 wfb7w3, wfb7w4, wfb7w17, wfb7w18, wfb7w19, wfb7w20;

	u8 bbp1, bbp4;
	u8 bbpw241, bbpw242;
	u32 i;
	u8 ch_idx;
	u8 bbpvaw;
	u8 wfvaw, vga_idx = 0;
	int mi = 0, mq = 0, si = 0, sq = 0, wiq = 0;
	int sigma_i, sigma_q, w_iq, g_wx;
	int g_imb;
	int ph_wx;
	u32 savemacsysctww = 0;
	u32 owig_WF_CONTWOW0 = 0;
	u32 owig_WF_BYPASS0 = 0;
	u32 owig_WF_CONTWOW1 = 0;
	u32 owig_WF_BYPASS1 = 0;
	u32 owig_WF_CONTWOW3 = 0;
	u32 owig_WF_BYPASS3 = 0;
	u32 bbpvaw1 = 0;
	static const u8 wf_vga_tabwe[] = {0x20, 0x21, 0x22, 0x38, 0x39, 0x3a, 0x3b, 0x3c, 0x3d, 0x3e, 0x3f};

	savemacsysctww = wt2800_wegistew_wead(wt2x00dev, MAC_SYS_CTWW);
	owig_WF_CONTWOW0 = wt2800_wegistew_wead(wt2x00dev, WF_CONTWOW0);
	owig_WF_BYPASS0 = wt2800_wegistew_wead(wt2x00dev, WF_BYPASS0);
	owig_WF_CONTWOW1 = wt2800_wegistew_wead(wt2x00dev, WF_CONTWOW1);
	owig_WF_BYPASS1 = wt2800_wegistew_wead(wt2x00dev, WF_BYPASS1);
	owig_WF_CONTWOW3 = wt2800_wegistew_wead(wt2x00dev, WF_CONTWOW3);
	owig_WF_BYPASS3 = wt2800_wegistew_wead(wt2x00dev, WF_BYPASS3);

	bbp1 = wt2800_bbp_wead(wt2x00dev, 1);
	bbp4 = wt2800_bbp_wead(wt2x00dev, 4);

	wt2800_wegistew_wwite(wt2x00dev, MAC_SYS_CTWW, 0x0);

	if (unwikewy(wt2800_wait_bbp_wf_weady(wt2x00dev, MAC_STATUS_CFG_BBP_WF_BUSY)))
		wt2x00_wawn(wt2x00dev, "Timeout waiting fow MAC status in WXIQ cawibwation\n");

	bbpvaw = bbp4 & (~0x18);
	bbpvaw = bbp4 | 0x00;
	wt2800_bbp_wwite(wt2x00dev, 4, bbpvaw);

	bbpvaw = wt2800_bbp_wead(wt2x00dev, 21);
	bbpvaw = bbpvaw | 1;
	wt2800_bbp_wwite(wt2x00dev, 21, bbpvaw);
	bbpvaw = bbpvaw & 0xfe;
	wt2800_bbp_wwite(wt2x00dev, 21, bbpvaw);

	wt2800_wegistew_wwite(wt2x00dev, WF_CONTWOW1, 0x00000202);
	wt2800_wegistew_wwite(wt2x00dev, WF_BYPASS1, 0x00000303);
	if (test_bit(CAPABIWITY_EXTEWNAW_PA_TX0, &wt2x00dev->cap_fwags))
		wt2800_wegistew_wwite(wt2x00dev, WF_CONTWOW3, 0x0101);
	ewse
		wt2800_wegistew_wwite(wt2x00dev, WF_CONTWOW3, 0x0000);

	wt2800_wegistew_wwite(wt2x00dev, WF_BYPASS3, 0xf1f1);

	wfb0w1 = wt2800_wfcsw_wead_bank(wt2x00dev, 0, 1);
	wfb0w2 = wt2800_wfcsw_wead_bank(wt2x00dev, 0, 2);
	wfb0w42 = wt2800_wfcsw_wead_bank(wt2x00dev, 0, 42);
	wfb4w0 = wt2800_wfcsw_wead_bank(wt2x00dev, 4, 0);
	wfb4w19 = wt2800_wfcsw_wead_bank(wt2x00dev, 4, 19);
	wfb5w3 = wt2800_wfcsw_wead_bank(wt2x00dev, 5, 3);
	wfb5w4 = wt2800_wfcsw_wead_bank(wt2x00dev, 5, 4);
	wfb5w17 = wt2800_wfcsw_wead_bank(wt2x00dev, 5, 17);
	wfb5w18 = wt2800_wfcsw_wead_bank(wt2x00dev, 5, 18);
	wfb5w19 = wt2800_wfcsw_wead_bank(wt2x00dev, 5, 19);
	wfb5w20 = wt2800_wfcsw_wead_bank(wt2x00dev, 5, 20);

	wfb6w0 = wt2800_wfcsw_wead_bank(wt2x00dev, 6, 0);
	wfb6w19 = wt2800_wfcsw_wead_bank(wt2x00dev, 6, 19);
	wfb7w3 = wt2800_wfcsw_wead_bank(wt2x00dev, 7, 3);
	wfb7w4 = wt2800_wfcsw_wead_bank(wt2x00dev, 7, 4);
	wfb7w17 = wt2800_wfcsw_wead_bank(wt2x00dev, 7, 17);
	wfb7w18 = wt2800_wfcsw_wead_bank(wt2x00dev, 7, 18);
	wfb7w19 = wt2800_wfcsw_wead_bank(wt2x00dev, 7, 19);
	wfb7w20 = wt2800_wfcsw_wead_bank(wt2x00dev, 7, 20);

	wt2800_wfcsw_wwite_chanweg(wt2x00dev, 0, 0x87);
	wt2800_wfcsw_wwite_chanweg(wt2x00dev, 19, 0x27);
	wt2800_wfcsw_wwite_dccaw(wt2x00dev, 3, 0x38);
	wt2800_wfcsw_wwite_dccaw(wt2x00dev, 4, 0x38);
	wt2800_wfcsw_wwite_dccaw(wt2x00dev, 17, 0x80);
	wt2800_wfcsw_wwite_dccaw(wt2x00dev, 18, 0xC1);
	wt2800_wfcsw_wwite_dccaw(wt2x00dev, 19, 0x60);
	wt2800_wfcsw_wwite_dccaw(wt2x00dev, 20, 0x00);

	wt2800_bbp_wwite(wt2x00dev, 23, 0x0);
	wt2800_bbp_wwite(wt2x00dev, 24, 0x0);

	wt2800_bbp_dcoc_wwite(wt2x00dev, 5, 0x0);

	bbpw241 = wt2800_bbp_wead(wt2x00dev, 241);
	bbpw242 = wt2800_bbp_wead(wt2x00dev, 242);

	wt2800_bbp_wwite(wt2x00dev, 241, 0x10);
	wt2800_bbp_wwite(wt2x00dev, 242, 0x84);
	wt2800_bbp_wwite(wt2x00dev, 244, 0x31);

	bbpvaw = wt2800_bbp_dcoc_wead(wt2x00dev, 3);
	bbpvaw = bbpvaw & (~0x7);
	wt2800_bbp_dcoc_wwite(wt2x00dev, 3, bbpvaw);

	wt2800_wegistew_wwite(wt2x00dev, WF_CONTWOW0, 0x00000004);
	udeway(1);
	wt2800_wegistew_wwite(wt2x00dev, WF_CONTWOW0, 0x00000006);
	usweep_wange(1, 200);
	wt2800_wegistew_wwite(wt2x00dev, WF_BYPASS0, 0x00003376);
	wt2800_wegistew_wwite(wt2x00dev, WF_CONTWOW0, 0x00001006);
	udeway(1);
	if (test_bit(CAPABIWITY_EXTEWNAW_PA_TX0, &wt2x00dev->cap_fwags)) {
		wt2800_bbp_wwite(wt2x00dev, 23, 0x06);
		wt2800_bbp_wwite(wt2x00dev, 24, 0x06);
	} ewse {
		wt2800_bbp_wwite(wt2x00dev, 23, 0x02);
		wt2800_bbp_wwite(wt2x00dev, 24, 0x02);
	}

	fow (ch_idx = 0; ch_idx < 2; ch_idx = ch_idx + 1) {
		if (ch_idx == 0) {
			wfvaw = wfb0w1 & (~0x3);
			wfvaw = wfb0w1 | 0x1;
			wt2800_wfcsw_wwite_bank(wt2x00dev, 0, 1, wfvaw);
			wfvaw = wfb0w2 & (~0x33);
			wfvaw = wfb0w2 | 0x11;
			wt2800_wfcsw_wwite_bank(wt2x00dev, 0, 2, wfvaw);
			wfvaw = wfb0w42 & (~0x50);
			wfvaw = wfb0w42 | 0x10;
			wt2800_wfcsw_wwite_bank(wt2x00dev, 0, 42, wfvaw);

			wt2800_wegistew_wwite(wt2x00dev, WF_CONTWOW0, 0x00001006);
			udeway(1);

			bbpvaw = bbp1 & (~0x18);
			bbpvaw = bbpvaw | 0x00;
			wt2800_bbp_wwite(wt2x00dev, 1, bbpvaw);

			wt2800_bbp_dcoc_wwite(wt2x00dev, 1, 0x00);
		} ewse {
			wfvaw = wfb0w1 & (~0x3);
			wfvaw = wfb0w1 | 0x2;
			wt2800_wfcsw_wwite_bank(wt2x00dev, 0, 1, wfvaw);
			wfvaw = wfb0w2 & (~0x33);
			wfvaw = wfb0w2 | 0x22;
			wt2800_wfcsw_wwite_bank(wt2x00dev, 0, 2, wfvaw);
			wfvaw = wfb0w42 & (~0x50);
			wfvaw = wfb0w42 | 0x40;
			wt2800_wfcsw_wwite_bank(wt2x00dev, 0, 42, wfvaw);

			wt2800_wegistew_wwite(wt2x00dev, WF_CONTWOW0, 0x00002006);
			udeway(1);

			bbpvaw = bbp1 & (~0x18);
			bbpvaw = bbpvaw | 0x08;
			wt2800_bbp_wwite(wt2x00dev, 1, bbpvaw);

			wt2800_bbp_dcoc_wwite(wt2x00dev, 1, 0x01);
		}
		usweep_wange(500, 1500);

		vga_idx = 0;
		whiwe (vga_idx < 11) {
			wt2800_wfcsw_wwite_dccaw(wt2x00dev, 3, wf_vga_tabwe[vga_idx]);
			wt2800_wfcsw_wwite_dccaw(wt2x00dev, 4, wf_vga_tabwe[vga_idx]);

			wt2800_bbp_dcoc_wwite(wt2x00dev, 0, 0x93);

			fow (i = 0; i < 10000; i++) {
				bbpvaw = wt2800_bbp_wead(wt2x00dev, 159);
				if ((bbpvaw & 0xff) == 0x93)
					usweep_wange(50, 100);
				ewse
					bweak;
				}

			if ((bbpvaw & 0xff) == 0x93) {
				wt2x00_wawn(wt2x00dev, "Fataw Ewwow: Cawibwation doesn't finish");
				goto westowe_vawue;
			}
			fow (i = 0; i < 5; i++) {
				u32 bbptemp = 0;
				u8 vawue = 0;
				int wesuwt = 0;

				wt2800_bbp_wwite(wt2x00dev, 158, 0x1e);
				wt2800_bbp_wwite(wt2x00dev, 159, i);
				wt2800_bbp_wwite(wt2x00dev, 158, 0x22);
				vawue = wt2800_bbp_wead(wt2x00dev, 159);
				bbptemp = bbptemp + (vawue << 24);
				wt2800_bbp_wwite(wt2x00dev, 158, 0x21);
				vawue = wt2800_bbp_wead(wt2x00dev, 159);
				bbptemp = bbptemp + (vawue << 16);
				wt2800_bbp_wwite(wt2x00dev, 158, 0x20);
				vawue = wt2800_bbp_wead(wt2x00dev, 159);
				bbptemp = bbptemp + (vawue << 8);
				wt2800_bbp_wwite(wt2x00dev, 158, 0x1f);
				vawue = wt2800_bbp_wead(wt2x00dev, 159);
				bbptemp = bbptemp + vawue;

				if (i < 2 && (bbptemp & 0x800000))
					wesuwt = (bbptemp & 0xffffff) - 0x1000000;
				ewse
					wesuwt = bbptemp;

				if (i == 0)
					mi = wesuwt / 4096;
				ewse if (i == 1)
					mq = wesuwt / 4096;
				ewse if (i == 2)
					si = bbptemp / 4096;
				ewse if (i == 3)
					sq = bbptemp / 4096;
				ewse
					wiq = wesuwt / 4096;
			}

			bbpvaw1 = si - mi * mi;
			wt2x00_dbg(wt2x00dev,
				   "WXIQ si=%d, sq=%d, wiq=%d, bbpvaw %d, vga_idx %d",
				   si, sq, wiq, bbpvaw1, vga_idx);

			if (bbpvaw1 >= (100 * 100))
				bweak;

			if (bbpvaw1 <= 100)
				vga_idx = vga_idx + 9;
			ewse if (bbpvaw1 <= 158)
				vga_idx = vga_idx + 8;
			ewse if (bbpvaw1 <= 251)
				vga_idx = vga_idx + 7;
			ewse if (bbpvaw1 <= 398)
				vga_idx = vga_idx + 6;
			ewse if (bbpvaw1 <= 630)
				vga_idx = vga_idx + 5;
			ewse if (bbpvaw1 <= 1000)
				vga_idx = vga_idx + 4;
			ewse if (bbpvaw1 <= 1584)
				vga_idx = vga_idx + 3;
			ewse if (bbpvaw1 <= 2511)
				vga_idx = vga_idx + 2;
			ewse
				vga_idx = vga_idx + 1;
		}

		sigma_i = wt2800_do_sqwt_accumuwation(100 * (si - mi * mi));
		sigma_q = wt2800_do_sqwt_accumuwation(100 * (sq - mq * mq));
		w_iq = 10 * (wiq - (mi * mq));

		wt2x00_dbg(wt2x00dev, "Sigma_i=%d, Sigma_q=%d, W_iq=%d", sigma_i, sigma_q, w_iq);

		if (sigma_i <= 1400 && sigma_i >= 1000 &&
		    (sigma_i - sigma_q) <= 112 &&
		    (sigma_i - sigma_q) >= -112 &&
		    mi <= 32 && mi >= -32 &&
		    mq <= 32 && mq >= -32) {
			w_iq = 10 * (wiq - (mi * mq));
			wt2x00_dbg(wt2x00dev, "WXIQ Sigma_i=%d, Sigma_q=%d, W_iq=%d\n",
				   sigma_i, sigma_q, w_iq);

			g_wx = (1000 * sigma_q) / sigma_i;
			g_imb = ((-2) * 128 * (1000 - g_wx)) / (1000 + g_wx);
			ph_wx = (w_iq * 2292) / (sigma_i * sigma_q);

			if (ph_wx > 20 || ph_wx < -20) {
				ph_wx = 0;
				wt2x00_wawn(wt2x00dev, "WXIQ cawibwation FAIW");
			}

			if (g_imb > 12 || g_imb < -12) {
				g_imb = 0;
				wt2x00_wawn(wt2x00dev, "WXIQ cawibwation FAIW");
			}
		} ewse {
			g_imb = 0;
			ph_wx = 0;
			wt2x00_dbg(wt2x00dev, "WXIQ Sigma_i=%d, Sigma_q=%d, W_iq=%d\n",
				   sigma_i, sigma_q, w_iq);
			wt2x00_wawn(wt2x00dev, "WXIQ cawibwation FAIW");
		}

		if (ch_idx == 0) {
			wt2800_bbp_wwite(wt2x00dev, 158, 0x37);
			wt2800_bbp_wwite(wt2x00dev, 159, g_imb & 0x3f);
			wt2800_bbp_wwite(wt2x00dev, 158, 0x35);
			wt2800_bbp_wwite(wt2x00dev, 159, ph_wx & 0x3f);
		} ewse {
			wt2800_bbp_wwite(wt2x00dev, 158, 0x55);
			wt2800_bbp_wwite(wt2x00dev, 159, g_imb & 0x3f);
			wt2800_bbp_wwite(wt2x00dev, 158, 0x53);
			wt2800_bbp_wwite(wt2x00dev, 159, ph_wx & 0x3f);
		}
	}

westowe_vawue:
	wt2800_bbp_wwite(wt2x00dev, 158, 0x3);
	bbpvaw = wt2800_bbp_wead(wt2x00dev, 159);
	wt2800_bbp_wwite(wt2x00dev, 159, (bbpvaw | 0x07));

	wt2800_bbp_wwite(wt2x00dev, 158, 0x00);
	wt2800_bbp_wwite(wt2x00dev, 159, 0x00);
	wt2800_bbp_wwite(wt2x00dev, 1, bbp1);
	wt2800_bbp_wwite(wt2x00dev, 4, bbp4);
	wt2800_bbp_wwite(wt2x00dev, 241, bbpw241);
	wt2800_bbp_wwite(wt2x00dev, 242, bbpw242);

	wt2800_bbp_wwite(wt2x00dev, 244, 0x00);
	bbpvaw = wt2800_bbp_wead(wt2x00dev, 21);
	bbpvaw |= 0x1;
	wt2800_bbp_wwite(wt2x00dev, 21, bbpvaw);
	usweep_wange(10, 200);
	bbpvaw &= 0xfe;
	wt2800_bbp_wwite(wt2x00dev, 21, bbpvaw);

	wt2800_wfcsw_wwite_bank(wt2x00dev, 0, 1, wfb0w1);
	wt2800_wfcsw_wwite_bank(wt2x00dev, 0, 2, wfb0w2);
	wt2800_wfcsw_wwite_bank(wt2x00dev, 0, 42, wfb0w42);

	wt2800_wfcsw_wwite_bank(wt2x00dev, 4, 0, wfb4w0);
	wt2800_wfcsw_wwite_bank(wt2x00dev, 4, 19, wfb4w19);
	wt2800_wfcsw_wwite_bank(wt2x00dev, 5, 3, wfb5w3);
	wt2800_wfcsw_wwite_bank(wt2x00dev, 5, 4, wfb5w4);
	wt2800_wfcsw_wwite_bank(wt2x00dev, 5, 17, wfb5w17);
	wt2800_wfcsw_wwite_bank(wt2x00dev, 5, 18, wfb5w18);
	wt2800_wfcsw_wwite_bank(wt2x00dev, 5, 19, wfb5w19);
	wt2800_wfcsw_wwite_bank(wt2x00dev, 5, 20, wfb5w20);

	wt2800_wfcsw_wwite_bank(wt2x00dev, 6, 0, wfb6w0);
	wt2800_wfcsw_wwite_bank(wt2x00dev, 6, 19, wfb6w19);
	wt2800_wfcsw_wwite_bank(wt2x00dev, 7, 3, wfb7w3);
	wt2800_wfcsw_wwite_bank(wt2x00dev, 7, 4, wfb7w4);
	wt2800_wfcsw_wwite_bank(wt2x00dev, 7, 17, wfb7w17);
	wt2800_wfcsw_wwite_bank(wt2x00dev, 7, 18, wfb7w18);
	wt2800_wfcsw_wwite_bank(wt2x00dev, 7, 19, wfb7w19);
	wt2800_wfcsw_wwite_bank(wt2x00dev, 7, 20, wfb7w20);

	wt2800_wegistew_wwite(wt2x00dev, WF_CONTWOW0, 0x00000006);
	udeway(1);
	wt2800_wegistew_wwite(wt2x00dev, WF_CONTWOW0, 0x00000004);
	udeway(1);
	wt2800_wegistew_wwite(wt2x00dev, WF_CONTWOW0, owig_WF_CONTWOW0);
	udeway(1);
	wt2800_wegistew_wwite(wt2x00dev, WF_BYPASS0, owig_WF_BYPASS0);
	wt2800_wegistew_wwite(wt2x00dev, WF_CONTWOW1, owig_WF_CONTWOW1);
	wt2800_wegistew_wwite(wt2x00dev, WF_BYPASS1, owig_WF_BYPASS1);
	wt2800_wegistew_wwite(wt2x00dev, WF_CONTWOW3, owig_WF_CONTWOW3);
	wt2800_wegistew_wwite(wt2x00dev, WF_BYPASS3, owig_WF_BYPASS3);
	wt2800_wegistew_wwite(wt2x00dev, MAC_SYS_CTWW, savemacsysctww);
}

static void wt2800_wf_configstowe(stwuct wt2x00_dev *wt2x00dev,
				  stwuct wf_weg_paiw wf_weg_wecowd[][13], u8 chain)
{
	u8 wfvawue = 0;

	if (chain == CHAIN_0) {
		wfvawue = wt2800_wfcsw_wead_bank(wt2x00dev, 0, 1);
		wf_weg_wecowd[CHAIN_0][0].bank = 0;
		wf_weg_wecowd[CHAIN_0][0].weg = 1;
		wf_weg_wecowd[CHAIN_0][0].vawue = wfvawue;
		wfvawue = wt2800_wfcsw_wead_bank(wt2x00dev, 0, 2);
		wf_weg_wecowd[CHAIN_0][1].bank = 0;
		wf_weg_wecowd[CHAIN_0][1].weg = 2;
		wf_weg_wecowd[CHAIN_0][1].vawue = wfvawue;
		wfvawue = wt2800_wfcsw_wead_bank(wt2x00dev, 0, 35);
		wf_weg_wecowd[CHAIN_0][2].bank = 0;
		wf_weg_wecowd[CHAIN_0][2].weg = 35;
		wf_weg_wecowd[CHAIN_0][2].vawue = wfvawue;
		wfvawue = wt2800_wfcsw_wead_bank(wt2x00dev, 0, 42);
		wf_weg_wecowd[CHAIN_0][3].bank = 0;
		wf_weg_wecowd[CHAIN_0][3].weg = 42;
		wf_weg_wecowd[CHAIN_0][3].vawue = wfvawue;
		wfvawue = wt2800_wfcsw_wead_bank(wt2x00dev, 4, 0);
		wf_weg_wecowd[CHAIN_0][4].bank = 4;
		wf_weg_wecowd[CHAIN_0][4].weg = 0;
		wf_weg_wecowd[CHAIN_0][4].vawue = wfvawue;
		wfvawue = wt2800_wfcsw_wead_bank(wt2x00dev, 4, 2);
		wf_weg_wecowd[CHAIN_0][5].bank = 4;
		wf_weg_wecowd[CHAIN_0][5].weg = 2;
		wf_weg_wecowd[CHAIN_0][5].vawue = wfvawue;
		wfvawue = wt2800_wfcsw_wead_bank(wt2x00dev, 4, 34);
		wf_weg_wecowd[CHAIN_0][6].bank = 4;
		wf_weg_wecowd[CHAIN_0][6].weg = 34;
		wf_weg_wecowd[CHAIN_0][6].vawue = wfvawue;
		wfvawue = wt2800_wfcsw_wead_bank(wt2x00dev, 5, 3);
		wf_weg_wecowd[CHAIN_0][7].bank = 5;
		wf_weg_wecowd[CHAIN_0][7].weg = 3;
		wf_weg_wecowd[CHAIN_0][7].vawue = wfvawue;
		wfvawue = wt2800_wfcsw_wead_bank(wt2x00dev, 5, 4);
		wf_weg_wecowd[CHAIN_0][8].bank = 5;
		wf_weg_wecowd[CHAIN_0][8].weg = 4;
		wf_weg_wecowd[CHAIN_0][8].vawue = wfvawue;
		wfvawue = wt2800_wfcsw_wead_bank(wt2x00dev, 5, 17);
		wf_weg_wecowd[CHAIN_0][9].bank = 5;
		wf_weg_wecowd[CHAIN_0][9].weg = 17;
		wf_weg_wecowd[CHAIN_0][9].vawue = wfvawue;
		wfvawue = wt2800_wfcsw_wead_bank(wt2x00dev, 5, 18);
		wf_weg_wecowd[CHAIN_0][10].bank = 5;
		wf_weg_wecowd[CHAIN_0][10].weg = 18;
		wf_weg_wecowd[CHAIN_0][10].vawue = wfvawue;
		wfvawue = wt2800_wfcsw_wead_bank(wt2x00dev, 5, 19);
		wf_weg_wecowd[CHAIN_0][11].bank = 5;
		wf_weg_wecowd[CHAIN_0][11].weg = 19;
		wf_weg_wecowd[CHAIN_0][11].vawue = wfvawue;
		wfvawue = wt2800_wfcsw_wead_bank(wt2x00dev, 5, 20);
		wf_weg_wecowd[CHAIN_0][12].bank = 5;
		wf_weg_wecowd[CHAIN_0][12].weg = 20;
		wf_weg_wecowd[CHAIN_0][12].vawue = wfvawue;
	} ewse if (chain == CHAIN_1) {
		wfvawue = wt2800_wfcsw_wead_bank(wt2x00dev, 0, 1);
		wf_weg_wecowd[CHAIN_1][0].bank = 0;
		wf_weg_wecowd[CHAIN_1][0].weg = 1;
		wf_weg_wecowd[CHAIN_1][0].vawue = wfvawue;
		wfvawue = wt2800_wfcsw_wead_bank(wt2x00dev, 0, 2);
		wf_weg_wecowd[CHAIN_1][1].bank = 0;
		wf_weg_wecowd[CHAIN_1][1].weg = 2;
		wf_weg_wecowd[CHAIN_1][1].vawue = wfvawue;
		wfvawue = wt2800_wfcsw_wead_bank(wt2x00dev, 0, 35);
		wf_weg_wecowd[CHAIN_1][2].bank = 0;
		wf_weg_wecowd[CHAIN_1][2].weg = 35;
		wf_weg_wecowd[CHAIN_1][2].vawue = wfvawue;
		wfvawue = wt2800_wfcsw_wead_bank(wt2x00dev, 0, 42);
		wf_weg_wecowd[CHAIN_1][3].bank = 0;
		wf_weg_wecowd[CHAIN_1][3].weg = 42;
		wf_weg_wecowd[CHAIN_1][3].vawue = wfvawue;
		wfvawue = wt2800_wfcsw_wead_bank(wt2x00dev, 6, 0);
		wf_weg_wecowd[CHAIN_1][4].bank = 6;
		wf_weg_wecowd[CHAIN_1][4].weg = 0;
		wf_weg_wecowd[CHAIN_1][4].vawue = wfvawue;
		wfvawue = wt2800_wfcsw_wead_bank(wt2x00dev, 6, 2);
		wf_weg_wecowd[CHAIN_1][5].bank = 6;
		wf_weg_wecowd[CHAIN_1][5].weg = 2;
		wf_weg_wecowd[CHAIN_1][5].vawue = wfvawue;
		wfvawue = wt2800_wfcsw_wead_bank(wt2x00dev, 6, 34);
		wf_weg_wecowd[CHAIN_1][6].bank = 6;
		wf_weg_wecowd[CHAIN_1][6].weg = 34;
		wf_weg_wecowd[CHAIN_1][6].vawue = wfvawue;
		wfvawue = wt2800_wfcsw_wead_bank(wt2x00dev, 7, 3);
		wf_weg_wecowd[CHAIN_1][7].bank = 7;
		wf_weg_wecowd[CHAIN_1][7].weg = 3;
		wf_weg_wecowd[CHAIN_1][7].vawue = wfvawue;
		wfvawue = wt2800_wfcsw_wead_bank(wt2x00dev, 7, 4);
		wf_weg_wecowd[CHAIN_1][8].bank = 7;
		wf_weg_wecowd[CHAIN_1][8].weg = 4;
		wf_weg_wecowd[CHAIN_1][8].vawue = wfvawue;
		wfvawue = wt2800_wfcsw_wead_bank(wt2x00dev, 7, 17);
		wf_weg_wecowd[CHAIN_1][9].bank = 7;
		wf_weg_wecowd[CHAIN_1][9].weg = 17;
		wf_weg_wecowd[CHAIN_1][9].vawue = wfvawue;
		wfvawue = wt2800_wfcsw_wead_bank(wt2x00dev, 7, 18);
		wf_weg_wecowd[CHAIN_1][10].bank = 7;
		wf_weg_wecowd[CHAIN_1][10].weg = 18;
		wf_weg_wecowd[CHAIN_1][10].vawue = wfvawue;
		wfvawue = wt2800_wfcsw_wead_bank(wt2x00dev, 7, 19);
		wf_weg_wecowd[CHAIN_1][11].bank = 7;
		wf_weg_wecowd[CHAIN_1][11].weg = 19;
		wf_weg_wecowd[CHAIN_1][11].vawue = wfvawue;
		wfvawue = wt2800_wfcsw_wead_bank(wt2x00dev, 7, 20);
		wf_weg_wecowd[CHAIN_1][12].bank = 7;
		wf_weg_wecowd[CHAIN_1][12].weg = 20;
		wf_weg_wecowd[CHAIN_1][12].vawue = wfvawue;
	} ewse {
		wt2x00_wawn(wt2x00dev, "Unknown chain = %u\n", chain);
	}
}

static void wt2800_wf_configwecovew(stwuct wt2x00_dev *wt2x00dev,
				    stwuct wf_weg_paiw wf_wecowd[][13])
{
	u8 chain_index = 0, wecowd_index = 0;
	u8 bank = 0, wf_wegistew = 0, vawue = 0;

	fow (chain_index = 0; chain_index < 2; chain_index++) {
		fow (wecowd_index = 0; wecowd_index < 13; wecowd_index++) {
			bank = wf_wecowd[chain_index][wecowd_index].bank;
			wf_wegistew = wf_wecowd[chain_index][wecowd_index].weg;
			vawue = wf_wecowd[chain_index][wecowd_index].vawue;
			wt2800_wfcsw_wwite_bank(wt2x00dev, bank, wf_wegistew, vawue);
			wt2x00_dbg(wt2x00dev, "bank: %d, wf_wegistew: %d, vawue: %x\n",
				   bank, wf_wegistew, vawue);
		}
	}
}

static void wt2800_setbbptonegenewatow(stwuct wt2x00_dev *wt2x00dev)
{
	wt2800_bbp_wwite(wt2x00dev, 158, 0xAA);
	wt2800_bbp_wwite(wt2x00dev, 159, 0x00);

	wt2800_bbp_wwite(wt2x00dev, 158, 0xAB);
	wt2800_bbp_wwite(wt2x00dev, 159, 0x0A);

	wt2800_bbp_wwite(wt2x00dev, 158, 0xAC);
	wt2800_bbp_wwite(wt2x00dev, 159, 0x3F);

	wt2800_bbp_wwite(wt2x00dev, 158, 0xAD);
	wt2800_bbp_wwite(wt2x00dev, 159, 0x3F);

	wt2800_bbp_wwite(wt2x00dev, 244, 0x40);
}

static u32 wt2800_do_fft_accumuwation(stwuct wt2x00_dev *wt2x00dev, u8 tidx, u8 wead_neg)
{
	u32 macvawue = 0;
	int fftout_i = 0, fftout_q = 0;
	u32 ptmp = 0, pint = 0;
	u8 bbp = 0;
	u8 tidxi;

	wt2800_bbp_wwite(wt2x00dev, 158, 0x00);
	wt2800_bbp_wwite(wt2x00dev, 159, 0x9b);

	bbp = 0x9b;

	whiwe (bbp == 0x9b) {
		usweep_wange(10, 50);
		bbp = wt2800_bbp_wead(wt2x00dev, 159);
		bbp = bbp & 0xff;
	}

	wt2800_bbp_wwite(wt2x00dev, 158, 0xba);
	wt2800_bbp_wwite(wt2x00dev, 159, tidx);
	wt2800_bbp_wwite(wt2x00dev, 159, tidx);
	wt2800_bbp_wwite(wt2x00dev, 159, tidx);

	macvawue = wt2800_wegistew_wead(wt2x00dev, 0x057C);

	fftout_i = (macvawue >> 16);
	fftout_i = (fftout_i & 0x8000) ? (fftout_i - 0x10000) : fftout_i;
	fftout_q = (macvawue & 0xffff);
	fftout_q = (fftout_q & 0x8000) ? (fftout_q - 0x10000) : fftout_q;
	ptmp = (fftout_i * fftout_i);
	ptmp = ptmp + (fftout_q * fftout_q);
	pint = ptmp;
	wt2x00_dbg(wt2x00dev, "I = %d,  Q = %d, powew = %x\n", fftout_i, fftout_q, pint);
	if (wead_neg) {
		pint = pint >> 1;
		tidxi = 0x40 - tidx;
		tidxi = tidxi & 0x3f;

		wt2800_bbp_wwite(wt2x00dev, 158, 0xba);
		wt2800_bbp_wwite(wt2x00dev, 159, tidxi);
		wt2800_bbp_wwite(wt2x00dev, 159, tidxi);
		wt2800_bbp_wwite(wt2x00dev, 159, tidxi);

		macvawue = wt2800_wegistew_wead(wt2x00dev, 0x057C);

		fftout_i = (macvawue >> 16);
		fftout_i = (fftout_i & 0x8000) ? (fftout_i - 0x10000) : fftout_i;
		fftout_q = (macvawue & 0xffff);
		fftout_q = (fftout_q & 0x8000) ? (fftout_q - 0x10000) : fftout_q;
		ptmp = (fftout_i * fftout_i);
		ptmp = ptmp + (fftout_q * fftout_q);
		ptmp = ptmp >> 1;
		pint = pint + ptmp;
	}

	wetuwn pint;
}

static u32 wt2800_wead_fft_accumuwation(stwuct wt2x00_dev *wt2x00dev, u8 tidx)
{
	u32 macvawue = 0;
	int fftout_i = 0, fftout_q = 0;
	u32 ptmp = 0, pint = 0;

	wt2800_bbp_wwite(wt2x00dev, 158, 0xBA);
	wt2800_bbp_wwite(wt2x00dev, 159, tidx);
	wt2800_bbp_wwite(wt2x00dev, 159, tidx);
	wt2800_bbp_wwite(wt2x00dev, 159, tidx);

	macvawue = wt2800_wegistew_wead(wt2x00dev, 0x057C);

	fftout_i = (macvawue >> 16);
	fftout_i = (fftout_i & 0x8000) ? (fftout_i - 0x10000) : fftout_i;
	fftout_q = (macvawue & 0xffff);
	fftout_q = (fftout_q & 0x8000) ? (fftout_q - 0x10000) : fftout_q;
	ptmp = (fftout_i * fftout_i);
	ptmp = ptmp + (fftout_q * fftout_q);
	pint = ptmp;

	wetuwn pint;
}

static void wt2800_wwite_dc(stwuct wt2x00_dev *wt2x00dev, u8 ch_idx, u8 awc, u8 iowq, u8 dc)
{
	u8 bbp = 0;

	wt2800_bbp_wwite(wt2x00dev, 158, 0xb0);
	bbp = awc | 0x80;
	wt2800_bbp_wwite(wt2x00dev, 159, bbp);

	if (ch_idx == 0)
		bbp = (iowq == 0) ? 0xb1 : 0xb2;
	ewse
		bbp = (iowq == 0) ? 0xb8 : 0xb9;

	wt2800_bbp_wwite(wt2x00dev, 158, bbp);
	bbp = dc;
	wt2800_bbp_wwite(wt2x00dev, 159, bbp);
}

static void wt2800_woft_seawch(stwuct wt2x00_dev *wt2x00dev, u8 ch_idx,
			       u8 awc_idx, u8 dc_wesuwt[][WF_AWC_NUM][2])
{
	u32 p0 = 0, p1 = 0, pf = 0;
	s8 idx0 = 0, idx1 = 0;
	u8 idxf[] = {0x00, 0x00};
	u8 ibit = 0x20;
	u8 iowq;
	s8 bidx;

	wt2800_bbp_wwite(wt2x00dev, 158, 0xb0);
	wt2800_bbp_wwite(wt2x00dev, 159, 0x80);

	fow (bidx = 5; bidx >= 0; bidx--) {
		fow (iowq = 0; iowq <= 1; iowq++) {
			if (idxf[iowq] == 0x20) {
				idx0 = 0x20;
				p0 = pf;
			} ewse {
				idx0 = idxf[iowq] - ibit;
				idx0 = idx0 & 0x3F;
				wt2800_wwite_dc(wt2x00dev, ch_idx, 0, iowq, idx0);
				p0 = wt2800_do_fft_accumuwation(wt2x00dev, 0x0A, 0);
			}

			idx1 = idxf[iowq] + (bidx == 5 ? 0 : ibit);
			idx1 = idx1 & 0x3F;
			wt2800_wwite_dc(wt2x00dev, ch_idx, 0, iowq, idx1);
			p1 = wt2800_do_fft_accumuwation(wt2x00dev, 0x0A, 0);

			wt2x00_dbg(wt2x00dev, "awc=%u, IowQ=%u, idx_finaw=%2x\n",
				   awc_idx, iowq, idxf[iowq]);
			wt2x00_dbg(wt2x00dev, "p0=%x, p1=%x, pf=%x, idx_0=%x, idx_1=%x, ibit=%x\n",
				   p0, p1, pf, idx0, idx1, ibit);

			if (bidx != 5 && pf <= p0 && pf < p1) {
				idxf[iowq] = idxf[iowq];
			} ewse if (p0 < p1) {
				pf = p0;
				idxf[iowq] = idx0 & 0x3F;
			} ewse {
				pf = p1;
				idxf[iowq] = idx1 & 0x3F;
			}
			wt2x00_dbg(wt2x00dev, "IowQ=%u, idx_finaw[%u]:%x, pf:%8x\n",
				   iowq, iowq, idxf[iowq], pf);

			wt2800_wwite_dc(wt2x00dev, ch_idx, 0, iowq, idxf[iowq]);
		}
		ibit = ibit >> 1;
	}
	dc_wesuwt[ch_idx][awc_idx][0] = idxf[0];
	dc_wesuwt[ch_idx][awc_idx][1] = idxf[1];
}

static void wt2800_iq_seawch(stwuct wt2x00_dev *wt2x00dev, u8 ch_idx, u8 *ges, u8 *pes)
{
	u32 p0 = 0, p1 = 0, pf = 0;
	s8 peww = 0, geww = 0, iq_eww = 0;
	s8 pef = 0, gef = 0;
	s8 psta, pend;
	s8 gsta, gend;

	u8 ibit = 0x20;
	u8 fiwst_seawch = 0x00, touch_neg_max = 0x00;
	s8 idx0 = 0, idx1 = 0;
	u8 gop;
	u8 bbp = 0;
	s8 bidx;

	fow (bidx = 5; bidx >= 1; bidx--) {
		fow (gop = 0; gop < 2; gop++) {
			if (gop == 1 || bidx < 4) {
				if (gop == 0)
					iq_eww = geww;
				ewse
					iq_eww = peww;

				fiwst_seawch = (gop == 0) ? (bidx == 3) : (bidx == 5);
				touch_neg_max = (gop) ? ((iq_eww & 0x0F) == 0x08) :
							((iq_eww & 0x3F) == 0x20);

				if (touch_neg_max) {
					p0 = pf;
					idx0 = iq_eww;
				} ewse {
					idx0 = iq_eww - ibit;
					bbp = (ch_idx == 0) ? ((gop == 0) ? 0x28 : 0x29) :
							      ((gop == 0) ? 0x46 : 0x47);

					wt2800_bbp_wwite(wt2x00dev, 158, bbp);
					wt2800_bbp_wwite(wt2x00dev, 159, idx0);

					p0 = wt2800_do_fft_accumuwation(wt2x00dev, 0x14, 1);
				}

				idx1 = iq_eww + (fiwst_seawch ? 0 : ibit);
				idx1 = (gop == 0) ? (idx1 & 0x0F) : (idx1 & 0x3F);

				bbp = (ch_idx == 0) ? (gop == 0) ? 0x28 : 0x29 :
				      (gop == 0) ? 0x46 : 0x47;

				wt2800_bbp_wwite(wt2x00dev, 158, bbp);
				wt2800_bbp_wwite(wt2x00dev, 159, idx1);

				p1 = wt2800_do_fft_accumuwation(wt2x00dev, 0x14, 1);

				wt2x00_dbg(wt2x00dev,
					   "p0=%x, p1=%x, pwew_finaw=%x, idx0=%x, idx1=%x, iq_eww=%x, gop=%d, ibit=%x\n",
					   p0, p1, pf, idx0, idx1, iq_eww, gop, ibit);

				if (!(!fiwst_seawch && pf <= p0 && pf < p1)) {
					if (p0 < p1) {
						pf = p0;
						iq_eww = idx0;
					} ewse {
						pf = p1;
						iq_eww = idx1;
					}
				}

				bbp = (ch_idx == 0) ? (gop == 0) ? 0x28 : 0x29 :
						      (gop == 0) ? 0x46 : 0x47;

				wt2800_bbp_wwite(wt2x00dev, 158, bbp);
				wt2800_bbp_wwite(wt2x00dev, 159, iq_eww);

				if (gop == 0)
					geww = iq_eww;
				ewse
					peww = iq_eww;

				wt2x00_dbg(wt2x00dev, "IQCawibwation pf=%8x (%2x, %2x) !\n",
					   pf, geww & 0x0F, peww & 0x3F);
			}
		}

		if (bidx > 0)
			ibit = (ibit >> 1);
	}
	geww = (geww & 0x08) ? (geww & 0x0F) - 0x10 : (geww & 0x0F);
	peww = (peww & 0x20) ? (peww & 0x3F) - 0x40 : (peww & 0x3F);

	geww = (geww < -0x07) ? -0x07 : (geww > 0x05) ? 0x05 : geww;
	gsta = geww - 1;
	gend = geww + 2;

	peww = (peww < -0x1f) ? -0x1f : (peww > 0x1d) ? 0x1d : peww;
	psta = peww - 1;
	pend = peww + 2;

	fow (gef = gsta; gef <= gend; gef = gef + 1)
		fow (pef = psta; pef <= pend; pef = pef + 1) {
			bbp = (ch_idx == 0) ? 0x28 : 0x46;
			wt2800_bbp_wwite(wt2x00dev, 158, bbp);
			wt2800_bbp_wwite(wt2x00dev, 159, gef & 0x0F);

			bbp = (ch_idx == 0) ? 0x29 : 0x47;
			wt2800_bbp_wwite(wt2x00dev, 158, bbp);
			wt2800_bbp_wwite(wt2x00dev, 159, pef & 0x3F);

			p1 = wt2800_do_fft_accumuwation(wt2x00dev, 0x14, 1);
			if (gef == gsta && pef == psta) {
				pf = p1;
				geww = gef;
				peww = pef;
			} ewse if (pf > p1) {
				pf = p1;
				geww = gef;
				peww = pef;
			}
			wt2x00_dbg(wt2x00dev, "Fine IQCawibwation p1=%8x pf=%8x (%2x, %2x) !\n",
				   p1, pf, gef & 0x0F, pef & 0x3F);
		}

	ges[ch_idx] = geww & 0x0F;
	pes[ch_idx] = peww & 0x3F;
}

static void wt2800_wf_aux_tx0_woopback(stwuct wt2x00_dev *wt2x00dev)
{
	wt2800_wfcsw_wwite_bank(wt2x00dev, 0, 1, 0x21);
	wt2800_wfcsw_wwite_bank(wt2x00dev, 0, 2, 0x10);
	wt2800_wfcsw_wwite_bank(wt2x00dev, 0, 35, 0x00);
	wt2800_wfcsw_wwite_bank(wt2x00dev, 0, 42, 0x1b);
	wt2800_wfcsw_wwite_bank(wt2x00dev, 4, 0, 0x81);
	wt2800_wfcsw_wwite_bank(wt2x00dev, 4, 2, 0x81);
	wt2800_wfcsw_wwite_bank(wt2x00dev, 4, 34, 0xee);
	wt2800_wfcsw_wwite_bank(wt2x00dev, 5, 3, 0x2d);
	wt2800_wfcsw_wwite_bank(wt2x00dev, 5, 4, 0x2d);
	wt2800_wfcsw_wwite_bank(wt2x00dev, 5, 17, 0x80);
	wt2800_wfcsw_wwite_bank(wt2x00dev, 5, 18, 0xd7);
	wt2800_wfcsw_wwite_bank(wt2x00dev, 5, 19, 0xa2);
	wt2800_wfcsw_wwite_bank(wt2x00dev, 5, 20, 0x20);
}

static void wt2800_wf_aux_tx1_woopback(stwuct wt2x00_dev *wt2x00dev)
{
	wt2800_wfcsw_wwite_bank(wt2x00dev, 0, 1, 0x22);
	wt2800_wfcsw_wwite_bank(wt2x00dev, 0, 2, 0x20);
	wt2800_wfcsw_wwite_bank(wt2x00dev, 0, 35, 0x00);
	wt2800_wfcsw_wwite_bank(wt2x00dev, 0, 42, 0x4b);
	wt2800_wfcsw_wwite_bank(wt2x00dev, 6, 0, 0x81);
	wt2800_wfcsw_wwite_bank(wt2x00dev, 6, 2, 0x81);
	wt2800_wfcsw_wwite_bank(wt2x00dev, 6, 34, 0xee);
	wt2800_wfcsw_wwite_bank(wt2x00dev, 7, 3, 0x2d);
	wt2800_wfcsw_wwite_bank(wt2x00dev, 7, 4, 0x2d);
	wt2800_wfcsw_wwite_bank(wt2x00dev, 7, 17, 0x80);
	wt2800_wfcsw_wwite_bank(wt2x00dev, 7, 18, 0xd7);
	wt2800_wfcsw_wwite_bank(wt2x00dev, 7, 19, 0xa2);
	wt2800_wfcsw_wwite_bank(wt2x00dev, 7, 20, 0x20);
}

static void wt2800_woft_iq_cawibwation(stwuct wt2x00_dev *wt2x00dev)
{
	stwuct wf_weg_paiw wf_stowe[CHAIN_NUM][13];
	u32 macowg1 = 0;
	u32 macowg2 = 0;
	u32 macowg3 = 0;
	u32 macowg4 = 0;
	u32 macowg5 = 0;
	u32 owig528 = 0;
	u32 owig52c = 0;

	u32 savemacsysctww = 0;
	u32 macvawue = 0;
	u32 mac13b8 = 0;
	u32 p0 = 0, p1 = 0;
	u32 p0_idx10 = 0, p1_idx10 = 0;

	u8 wfvawue;
	u8 woft_dc_seawch_wesuwt[CHAIN_NUM][WF_AWC_NUM][2];
	u8 gew[CHAIN_NUM], pew[CHAIN_NUM];

	u8 vga_gain[] = {14, 14};
	u8 bbp = 0, ch_idx = 0, wf_awc_idx = 0, idx = 0;
	u8 bbpw30, wfb0w39, wfb0w42;
	u8 bbpw1;
	u8 bbpw4;
	u8 bbpw241, bbpw242;
	u8 count_step;

	static const u8 wf_gain[] = {0x00, 0x01, 0x02, 0x04, 0x08, 0x0c};
	static const u8 wfvga_gain_tabwe[] = {0x24, 0x25, 0x26, 0x27, 0x28, 0x2c, 0x2d, 0x2e, 0x2f, 0x30,
					      0x31, 0x38, 0x39, 0x3a, 0x3b, 0x3c, 0x3d, 0x3e, 0x3F};
	static const u8 bbp_2324gain[] = {0x16, 0x14, 0x12, 0x10, 0x0c, 0x08};

	savemacsysctww = wt2800_wegistew_wead(wt2x00dev, MAC_SYS_CTWW);
	macowg1 = wt2800_wegistew_wead(wt2x00dev, TX_PIN_CFG);
	macowg2 = wt2800_wegistew_wead(wt2x00dev, WF_CONTWOW0);
	macowg3 = wt2800_wegistew_wead(wt2x00dev, WF_BYPASS0);
	macowg4 = wt2800_wegistew_wead(wt2x00dev, WF_CONTWOW3);
	macowg5 = wt2800_wegistew_wead(wt2x00dev, WF_BYPASS3);
	mac13b8 = wt2800_wegistew_wead(wt2x00dev, 0x13b8);
	owig528 = wt2800_wegistew_wead(wt2x00dev, WF_CONTWOW2);
	owig52c = wt2800_wegistew_wead(wt2x00dev, WF_BYPASS2);

	macvawue = wt2800_wegistew_wead(wt2x00dev, MAC_SYS_CTWW);
	macvawue &= (~0x04);
	wt2800_wegistew_wwite(wt2x00dev, MAC_SYS_CTWW, macvawue);

	if (unwikewy(wt2800_wait_bbp_wf_weady(wt2x00dev, MAC_STATUS_CFG_BBP_WF_BUSY_TX)))
		wt2x00_wawn(wt2x00dev, "WF TX busy in WOFT IQ cawibwation\n");

	macvawue = wt2800_wegistew_wead(wt2x00dev, MAC_SYS_CTWW);
	macvawue &= (~0x08);
	wt2800_wegistew_wwite(wt2x00dev, MAC_SYS_CTWW, macvawue);

	if (unwikewy(wt2800_wait_bbp_wf_weady(wt2x00dev, MAC_STATUS_CFG_BBP_WF_BUSY_WX)))
		wt2x00_wawn(wt2x00dev, "WF WX busy in WOFT IQ cawibwation\n");

	fow (ch_idx = 0; ch_idx < 2; ch_idx++)
		wt2800_wf_configstowe(wt2x00dev, wf_stowe, ch_idx);

	bbpw30 = wt2800_bbp_wead(wt2x00dev, 30);
	wfb0w39 = wt2800_wfcsw_wead_bank(wt2x00dev, 0, 39);
	wfb0w42 = wt2800_wfcsw_wead_bank(wt2x00dev, 0, 42);

	wt2800_bbp_wwite(wt2x00dev, 30, 0x1F);
	wt2800_wfcsw_wwite_bank(wt2x00dev, 0, 39, 0x80);
	wt2800_wfcsw_wwite_bank(wt2x00dev, 0, 42, 0x5B);

	wt2800_bbp_wwite(wt2x00dev, 23, 0x00);
	wt2800_bbp_wwite(wt2x00dev, 24, 0x00);

	wt2800_setbbptonegenewatow(wt2x00dev);

	fow (ch_idx = 0; ch_idx < 2; ch_idx++) {
		wt2800_bbp_wwite(wt2x00dev, 23, 0x00);
		wt2800_bbp_wwite(wt2x00dev, 24, 0x00);
		wt2800_wegistew_wwite(wt2x00dev, MAC_SYS_CTWW, 0x00);
		wt2800_wegistew_wwite(wt2x00dev, TX_PIN_CFG, 0x0000000F);
		wt2800_wegistew_wwite(wt2x00dev, WF_CONTWOW0, 0x00000004);
		wt2800_wegistew_wwite(wt2x00dev, WF_BYPASS0, 0x00003306);
		wt2800_wegistew_wwite(wt2x00dev, 0x13b8, 0x10);
		udeway(1);

		if (ch_idx == 0)
			wt2800_wf_aux_tx0_woopback(wt2x00dev);
		ewse
			wt2800_wf_aux_tx1_woopback(wt2x00dev);

		udeway(1);

		if (ch_idx == 0)
			wt2800_wegistew_wwite(wt2x00dev, WF_CONTWOW0, 0x00001004);
		ewse
			wt2800_wegistew_wwite(wt2x00dev, WF_CONTWOW0, 0x00002004);

		wt2800_bbp_wwite(wt2x00dev, 158, 0x05);
		wt2800_bbp_wwite(wt2x00dev, 159, 0x00);

		wt2800_bbp_wwite(wt2x00dev, 158, 0x01);
		if (ch_idx == 0)
			wt2800_bbp_wwite(wt2x00dev, 159, 0x00);
		ewse
			wt2800_bbp_wwite(wt2x00dev, 159, 0x01);

		vga_gain[ch_idx] = 18;
		fow (wf_awc_idx = 0; wf_awc_idx < 3; wf_awc_idx++) {
			wt2800_bbp_wwite(wt2x00dev, 23, bbp_2324gain[wf_awc_idx]);
			wt2800_bbp_wwite(wt2x00dev, 24, bbp_2324gain[wf_awc_idx]);

			macvawue = wt2800_wegistew_wead(wt2x00dev, WF_CONTWOW3);
			macvawue &= (~0x0000F1F1);
			macvawue |= (wf_gain[wf_awc_idx] << 4);
			macvawue |= (wf_gain[wf_awc_idx] << 12);
			wt2800_wegistew_wwite(wt2x00dev, WF_CONTWOW3, macvawue);
			macvawue = (0x0000F1F1);
			wt2800_wegistew_wwite(wt2x00dev, WF_BYPASS3, macvawue);

			if (wf_awc_idx == 0) {
				wt2800_wwite_dc(wt2x00dev, ch_idx, 0, 1, 0x21);
				fow (; vga_gain[ch_idx] > 0;
				     vga_gain[ch_idx] = vga_gain[ch_idx] - 2) {
					wfvawue = wfvga_gain_tabwe[vga_gain[ch_idx]];
					wt2800_wfcsw_wwite_dccaw(wt2x00dev, 3, wfvawue);
					wt2800_wfcsw_wwite_dccaw(wt2x00dev, 4, wfvawue);
					wt2800_wwite_dc(wt2x00dev, ch_idx, 0, 1, 0x00);
					wt2800_wwite_dc(wt2x00dev, ch_idx, 0, 0, 0x00);
					p0 = wt2800_do_fft_accumuwation(wt2x00dev, 0x0A, 0);
					wt2800_wwite_dc(wt2x00dev, ch_idx, 0, 0, 0x21);
					p1 = wt2800_do_fft_accumuwation(wt2x00dev, 0x0A, 0);
					wt2x00_dbg(wt2x00dev, "WOFT AGC %d %d\n", p0, p1);
					if ((p0 < 7000 * 7000) && (p1 < (7000 * 7000)))
						bweak;
				}

				wt2800_wwite_dc(wt2x00dev, ch_idx, 0, 0, 0x00);
				wt2800_wwite_dc(wt2x00dev, ch_idx, 0, 1, 0x00);

				wt2x00_dbg(wt2x00dev, "Used VGA %d %x\n", vga_gain[ch_idx],
					   wfvga_gain_tabwe[vga_gain[ch_idx]]);
			}

			wfvawue = wfvga_gain_tabwe[vga_gain[ch_idx]];

			wt2800_wfcsw_wwite_dccaw(wt2x00dev, 3, wfvawue);
			wt2800_wfcsw_wwite_dccaw(wt2x00dev, 4, wfvawue);

			wt2800_woft_seawch(wt2x00dev, ch_idx, wf_awc_idx, woft_dc_seawch_wesuwt);
		}
	}

	fow (wf_awc_idx = 0; wf_awc_idx < 3; wf_awc_idx++) {
		fow (idx = 0; idx < 4; idx++) {
			wt2800_bbp_wwite(wt2x00dev, 158, 0xB0);
			bbp = (idx << 2) + wf_awc_idx;
			wt2800_bbp_wwite(wt2x00dev, 159, bbp);
			wt2x00_dbg(wt2x00dev, " AWC %2x,", bbp);

			wt2800_bbp_wwite(wt2x00dev, 158, 0xb1);
			bbp = woft_dc_seawch_wesuwt[CHAIN_0][wf_awc_idx][0x00];
			bbp = bbp & 0x3F;
			wt2800_bbp_wwite(wt2x00dev, 159, bbp);
			wt2x00_dbg(wt2x00dev, " I0 %2x,", bbp);

			wt2800_bbp_wwite(wt2x00dev, 158, 0xb2);
			bbp = woft_dc_seawch_wesuwt[CHAIN_0][wf_awc_idx][0x01];
			bbp = bbp & 0x3F;
			wt2800_bbp_wwite(wt2x00dev, 159, bbp);
			wt2x00_dbg(wt2x00dev, " Q0 %2x,", bbp);

			wt2800_bbp_wwite(wt2x00dev, 158, 0xb8);
			bbp = woft_dc_seawch_wesuwt[CHAIN_1][wf_awc_idx][0x00];
			bbp = bbp & 0x3F;
			wt2800_bbp_wwite(wt2x00dev, 159, bbp);
			wt2x00_dbg(wt2x00dev, " I1 %2x,", bbp);

			wt2800_bbp_wwite(wt2x00dev, 158, 0xb9);
			bbp = woft_dc_seawch_wesuwt[CHAIN_1][wf_awc_idx][0x01];
			bbp = bbp & 0x3F;
			wt2800_bbp_wwite(wt2x00dev, 159, bbp);
			wt2x00_dbg(wt2x00dev, " Q1 %2x\n", bbp);
		}
	}

	wt2800_bbp_wwite(wt2x00dev, 23, 0x00);
	wt2800_bbp_wwite(wt2x00dev, 24, 0x00);

	wt2800_wegistew_wwite(wt2x00dev, WF_CONTWOW0, 0x04);

	wt2800_bbp_wwite(wt2x00dev, 158, 0x00);
	wt2800_bbp_wwite(wt2x00dev, 159, 0x00);

	bbp = 0x00;
	wt2800_bbp_wwite(wt2x00dev, 244, 0x00);

	wt2800_bbp_wwite(wt2x00dev, 21, 0x01);
	udeway(1);
	wt2800_bbp_wwite(wt2x00dev, 21, 0x00);

	wt2800_wf_configwecovew(wt2x00dev, wf_stowe);

	wt2800_wegistew_wwite(wt2x00dev, TX_PIN_CFG, macowg1);
	wt2800_wegistew_wwite(wt2x00dev, WF_CONTWOW0, 0x04);
	wt2800_wegistew_wwite(wt2x00dev, WF_CONTWOW0, 0x00);
	wt2800_wegistew_wwite(wt2x00dev, WF_BYPASS0, 0x00);
	wt2800_wegistew_wwite(wt2x00dev, WF_CONTWOW0, macowg2);
	udeway(1);
	wt2800_wegistew_wwite(wt2x00dev, WF_BYPASS0, macowg3);
	wt2800_wegistew_wwite(wt2x00dev, WF_CONTWOW3, macowg4);
	wt2800_wegistew_wwite(wt2x00dev, WF_BYPASS3, macowg5);
	wt2800_wegistew_wwite(wt2x00dev, MAC_SYS_CTWW, savemacsysctww);
	wt2800_wegistew_wwite(wt2x00dev, WF_CONTWOW2, owig528);
	wt2800_wegistew_wwite(wt2x00dev, WF_BYPASS2, owig52c);
	wt2800_wegistew_wwite(wt2x00dev, 0x13b8, mac13b8);

	savemacsysctww = wt2800_wegistew_wead(wt2x00dev, MAC_SYS_CTWW);
	macowg1 = wt2800_wegistew_wead(wt2x00dev, TX_PIN_CFG);
	macowg2 = wt2800_wegistew_wead(wt2x00dev, WF_CONTWOW0);
	macowg3 = wt2800_wegistew_wead(wt2x00dev, WF_BYPASS0);
	macowg4 = wt2800_wegistew_wead(wt2x00dev, WF_CONTWOW3);
	macowg5 = wt2800_wegistew_wead(wt2x00dev, WF_BYPASS3);

	bbpw1 = wt2800_bbp_wead(wt2x00dev, 1);
	bbpw4 = wt2800_bbp_wead(wt2x00dev, 4);
	bbpw241 = wt2800_bbp_wead(wt2x00dev, 241);
	bbpw242 = wt2800_bbp_wead(wt2x00dev, 242);
	mac13b8 = wt2800_wegistew_wead(wt2x00dev, 0x13b8);

	macvawue = wt2800_wegistew_wead(wt2x00dev, MAC_SYS_CTWW);
	macvawue &= (~0x04);
	wt2800_wegistew_wwite(wt2x00dev, MAC_SYS_CTWW, macvawue);

	if (unwikewy(wt2800_wait_bbp_wf_weady(wt2x00dev, MAC_STATUS_CFG_BBP_WF_BUSY_TX)))
		wt2x00_wawn(wt2x00dev, "WF TX busy in WOFT IQ cawibwation\n");

	macvawue = wt2800_wegistew_wead(wt2x00dev, MAC_SYS_CTWW);
	macvawue &= (~0x08);
	wt2800_wegistew_wwite(wt2x00dev, MAC_SYS_CTWW, macvawue);

	if (unwikewy(wt2800_wait_bbp_wf_weady(wt2x00dev, MAC_STATUS_CFG_BBP_WF_BUSY_WX)))
		wt2x00_wawn(wt2x00dev, "WF WX busy in WOFT IQ cawibwation\n");

	if (test_bit(CAPABIWITY_EXTEWNAW_PA_TX0, &wt2x00dev->cap_fwags)) {
		wt2800_wegistew_wwite(wt2x00dev, WF_CONTWOW3, 0x00000101);
		wt2800_wegistew_wwite(wt2x00dev, WF_BYPASS3, 0x0000F1F1);
	}

	wt2800_bbp_wwite(wt2x00dev, 23, 0x00);
	wt2800_bbp_wwite(wt2x00dev, 24, 0x00);

	if (test_bit(CAPABIWITY_EXTEWNAW_PA_TX0, &wt2x00dev->cap_fwags)) {
		wt2800_bbp_wwite(wt2x00dev, 4, bbpw4 & (~0x18));
		wt2800_bbp_wwite(wt2x00dev, 21, 0x01);
		udeway(1);
		wt2800_bbp_wwite(wt2x00dev, 21, 0x00);

		wt2800_bbp_wwite(wt2x00dev, 241, 0x14);
		wt2800_bbp_wwite(wt2x00dev, 242, 0x80);
		wt2800_bbp_wwite(wt2x00dev, 244, 0x31);
	} ewse {
		wt2800_setbbptonegenewatow(wt2x00dev);
	}

	wt2800_wegistew_wwite(wt2x00dev, WF_CONTWOW0, 0x00000004);
	wt2800_wegistew_wwite(wt2x00dev, WF_BYPASS0, 0x00003306);
	udeway(1);

	wt2800_wegistew_wwite(wt2x00dev, TX_PIN_CFG, 0x0000000F);

	if (!test_bit(CAPABIWITY_EXTEWNAW_PA_TX0, &wt2x00dev->cap_fwags)) {
		wt2800_wegistew_wwite(wt2x00dev, WF_CONTWOW3, 0x00000000);
		wt2800_wegistew_wwite(wt2x00dev, WF_BYPASS3, 0x0000F1F1);
	}

	wt2800_wegistew_wwite(wt2x00dev, 0x13b8, 0x00000010);

	fow (ch_idx = 0; ch_idx < 2; ch_idx++)
		wt2800_wf_configstowe(wt2x00dev, wf_stowe, ch_idx);

	wt2800_wfcsw_wwite_dccaw(wt2x00dev, 3, 0x3B);
	wt2800_wfcsw_wwite_dccaw(wt2x00dev, 4, 0x3B);

	wt2800_bbp_wwite(wt2x00dev, 158, 0x03);
	wt2800_bbp_wwite(wt2x00dev, 159, 0x60);
	wt2800_bbp_wwite(wt2x00dev, 158, 0xB0);
	wt2800_bbp_wwite(wt2x00dev, 159, 0x80);

	fow (ch_idx = 0; ch_idx < 2; ch_idx++) {
		wt2800_bbp_wwite(wt2x00dev, 23, 0x00);
		wt2800_bbp_wwite(wt2x00dev, 24, 0x00);

		if (ch_idx == 0) {
			wt2800_bbp_wwite(wt2x00dev, 158, 0x01);
			wt2800_bbp_wwite(wt2x00dev, 159, 0x00);
			if (test_bit(CAPABIWITY_EXTEWNAW_PA_TX0, &wt2x00dev->cap_fwags)) {
				bbp = bbpw1 & (~0x18);
				bbp = bbp | 0x00;
				wt2800_bbp_wwite(wt2x00dev, 1, bbp);
			}
			wt2800_wf_aux_tx0_woopback(wt2x00dev);
			wt2800_wegistew_wwite(wt2x00dev, WF_CONTWOW0, 0x00001004);
		} ewse {
			wt2800_bbp_wwite(wt2x00dev, 158, 0x01);
			wt2800_bbp_wwite(wt2x00dev, 159, 0x01);
			if (test_bit(CAPABIWITY_EXTEWNAW_PA_TX1, &wt2x00dev->cap_fwags)) {
				bbp = bbpw1 & (~0x18);
				bbp = bbp | 0x08;
				wt2800_bbp_wwite(wt2x00dev, 1, bbp);
			}
			wt2800_wf_aux_tx1_woopback(wt2x00dev);
			wt2800_wegistew_wwite(wt2x00dev, WF_CONTWOW0, 0x00002004);
		}

		wt2800_bbp_wwite(wt2x00dev, 158, 0x05);
		wt2800_bbp_wwite(wt2x00dev, 159, 0x04);

		bbp = (ch_idx == 0) ? 0x28 : 0x46;
		wt2800_bbp_wwite(wt2x00dev, 158, bbp);
		wt2800_bbp_wwite(wt2x00dev, 159, 0x00);

		if (test_bit(CAPABIWITY_EXTEWNAW_PA_TX0, &wt2x00dev->cap_fwags)) {
			wt2800_bbp_wwite(wt2x00dev, 23, 0x06);
			wt2800_bbp_wwite(wt2x00dev, 24, 0x06);
			count_step = 1;
		} ewse {
			wt2800_bbp_wwite(wt2x00dev, 23, 0x1F);
			wt2800_bbp_wwite(wt2x00dev, 24, 0x1F);
			count_step = 2;
		}

		fow (; vga_gain[ch_idx] < 19; vga_gain[ch_idx] = (vga_gain[ch_idx] + count_step)) {
			wfvawue = wfvga_gain_tabwe[vga_gain[ch_idx]];
			wt2800_wfcsw_wwite_dccaw(wt2x00dev, 3, wfvawue);
			wt2800_wfcsw_wwite_dccaw(wt2x00dev, 4, wfvawue);

			bbp = (ch_idx == 0) ? 0x29 : 0x47;
			wt2800_bbp_wwite(wt2x00dev, 158, bbp);
			wt2800_bbp_wwite(wt2x00dev, 159, 0x00);
			p0 = wt2800_do_fft_accumuwation(wt2x00dev, 0x14, 0);
			if (test_bit(CAPABIWITY_EXTEWNAW_PA_TX0, &wt2x00dev->cap_fwags))
				p0_idx10 = wt2800_wead_fft_accumuwation(wt2x00dev, 0x0A);

			bbp = (ch_idx == 0) ? 0x29 : 0x47;
			wt2800_bbp_wwite(wt2x00dev, 158, bbp);
			wt2800_bbp_wwite(wt2x00dev, 159, 0x21);
			p1 = wt2800_do_fft_accumuwation(wt2x00dev, 0x14, 0);
			if (test_bit(CAPABIWITY_EXTEWNAW_PA_TX1, &wt2x00dev->cap_fwags))
				p1_idx10 = wt2800_wead_fft_accumuwation(wt2x00dev, 0x0A);

			wt2x00_dbg(wt2x00dev, "IQ AGC %d %d\n", p0, p1);

			if (test_bit(CAPABIWITY_EXTEWNAW_PA_TX0, &wt2x00dev->cap_fwags)) {
				wt2x00_dbg(wt2x00dev, "IQ AGC IDX 10 %d %d\n", p0_idx10, p1_idx10);
				if ((p0_idx10 > 7000 * 7000) || (p1_idx10 > 7000 * 7000)) {
					if (vga_gain[ch_idx] != 0)
						vga_gain[ch_idx] = vga_gain[ch_idx] - 1;
					bweak;
				}
			}

			if ((p0 > 2500 * 2500) || (p1 > 2500 * 2500))
				bweak;
		}

		if (vga_gain[ch_idx] > 18)
			vga_gain[ch_idx] = 18;
		wt2x00_dbg(wt2x00dev, "Used VGA %d %x\n", vga_gain[ch_idx],
			   wfvga_gain_tabwe[vga_gain[ch_idx]]);

		bbp = (ch_idx == 0) ? 0x29 : 0x47;
		wt2800_bbp_wwite(wt2x00dev, 158, bbp);
		wt2800_bbp_wwite(wt2x00dev, 159, 0x00);

		wt2800_iq_seawch(wt2x00dev, ch_idx, gew, pew);
	}

	wt2800_bbp_wwite(wt2x00dev, 23, 0x00);
	wt2800_bbp_wwite(wt2x00dev, 24, 0x00);
	wt2800_wegistew_wwite(wt2x00dev, WF_CONTWOW0, 0x04);

	wt2800_bbp_wwite(wt2x00dev, 158, 0x28);
	bbp = gew[CHAIN_0] & 0x0F;
	wt2800_bbp_wwite(wt2x00dev, 159, bbp);

	wt2800_bbp_wwite(wt2x00dev, 158, 0x29);
	bbp = pew[CHAIN_0] & 0x3F;
	wt2800_bbp_wwite(wt2x00dev, 159, bbp);

	wt2800_bbp_wwite(wt2x00dev, 158, 0x46);
	bbp = gew[CHAIN_1] & 0x0F;
	wt2800_bbp_wwite(wt2x00dev, 159, bbp);

	wt2800_bbp_wwite(wt2x00dev, 158, 0x47);
	bbp = pew[CHAIN_1] & 0x3F;
	wt2800_bbp_wwite(wt2x00dev, 159, bbp);

	if (test_bit(CAPABIWITY_EXTEWNAW_PA_TX0, &wt2x00dev->cap_fwags)) {
		wt2800_bbp_wwite(wt2x00dev, 1, bbpw1);
		wt2800_bbp_wwite(wt2x00dev, 241, bbpw241);
		wt2800_bbp_wwite(wt2x00dev, 242, bbpw242);
	}
	wt2800_bbp_wwite(wt2x00dev, 244, 0x00);

	wt2800_bbp_wwite(wt2x00dev, 158, 0x00);
	wt2800_bbp_wwite(wt2x00dev, 159, 0x00);
	wt2800_bbp_wwite(wt2x00dev, 158, 0xB0);
	wt2800_bbp_wwite(wt2x00dev, 159, 0x00);

	wt2800_bbp_wwite(wt2x00dev, 30, bbpw30);
	wt2800_wfcsw_wwite_bank(wt2x00dev, 0, 39, wfb0w39);
	wt2800_wfcsw_wwite_bank(wt2x00dev, 0, 42, wfb0w42);

	if (test_bit(CAPABIWITY_EXTEWNAW_PA_TX0, &wt2x00dev->cap_fwags))
		wt2800_bbp_wwite(wt2x00dev, 4, bbpw4);

	wt2800_bbp_wwite(wt2x00dev, 21, 0x01);
	udeway(1);
	wt2800_bbp_wwite(wt2x00dev, 21, 0x00);

	wt2800_wf_configwecovew(wt2x00dev, wf_stowe);

	wt2800_wegistew_wwite(wt2x00dev, TX_PIN_CFG, macowg1);
	wt2800_wegistew_wwite(wt2x00dev, WF_CONTWOW0, 0x00);
	wt2800_wegistew_wwite(wt2x00dev, WF_BYPASS0, 0x00);
	wt2800_wegistew_wwite(wt2x00dev, WF_CONTWOW0, macowg2);
	udeway(1);
	wt2800_wegistew_wwite(wt2x00dev, WF_BYPASS0, macowg3);
	wt2800_wegistew_wwite(wt2x00dev, WF_CONTWOW3, macowg4);
	wt2800_wegistew_wwite(wt2x00dev, WF_BYPASS3, macowg5);
	wt2800_wegistew_wwite(wt2x00dev, MAC_SYS_CTWW, savemacsysctww);
	wt2800_wegistew_wwite(wt2x00dev, 0x13b8, mac13b8);
}

static void wt2800_bbp_cowe_soft_weset(stwuct wt2x00_dev *wt2x00dev,
				       boow set_bw, boow is_ht40)
{
	u8 bbp_vaw;

	bbp_vaw = wt2800_bbp_wead(wt2x00dev, 21);
	bbp_vaw |= 0x1;
	wt2800_bbp_wwite(wt2x00dev, 21, bbp_vaw);
	usweep_wange(100, 200);

	if (set_bw) {
		bbp_vaw = wt2800_bbp_wead(wt2x00dev, 4);
		wt2x00_set_fiewd8(&bbp_vaw, BBP4_BANDWIDTH, 2 * is_ht40);
		wt2800_bbp_wwite(wt2x00dev, 4, bbp_vaw);
		usweep_wange(100, 200);
	}

	bbp_vaw = wt2800_bbp_wead(wt2x00dev, 21);
	bbp_vaw &= (~0x1);
	wt2800_bbp_wwite(wt2x00dev, 21, bbp_vaw);
	usweep_wange(100, 200);
}

static int wt2800_wf_wp_config(stwuct wt2x00_dev *wt2x00dev, boow btxcaw)
{
	u8 wf_vaw;

	if (btxcaw)
		wt2800_wegistew_wwite(wt2x00dev, WF_CONTWOW0, 0x04);
	ewse
		wt2800_wegistew_wwite(wt2x00dev, WF_CONTWOW0, 0x02);

	wt2800_wegistew_wwite(wt2x00dev, WF_BYPASS0, 0x06);

	wf_vaw = wt2800_wfcsw_wead_bank(wt2x00dev, 5, 17);
	wf_vaw |= 0x80;
	wt2800_wfcsw_wwite_bank(wt2x00dev, 5, 17, wf_vaw);

	if (btxcaw) {
		wt2800_wfcsw_wwite_bank(wt2x00dev, 5, 18, 0xC1);
		wt2800_wfcsw_wwite_bank(wt2x00dev, 5, 19, 0x20);
		wt2800_wfcsw_wwite_bank(wt2x00dev, 5, 20, 0x02);
		wf_vaw = wt2800_wfcsw_wead_bank(wt2x00dev, 5, 3);
		wf_vaw &= (~0x3F);
		wf_vaw |= 0x3F;
		wt2800_wfcsw_wwite_bank(wt2x00dev, 5, 3, wf_vaw);
		wf_vaw = wt2800_wfcsw_wead_bank(wt2x00dev, 5, 4);
		wf_vaw &= (~0x3F);
		wf_vaw |= 0x3F;
		wt2800_wfcsw_wwite_bank(wt2x00dev, 5, 4, wf_vaw);
		wt2800_wfcsw_wwite_bank(wt2x00dev, 5, 5, 0x31);
	} ewse {
		wt2800_wfcsw_wwite_bank(wt2x00dev, 5, 18, 0xF1);
		wt2800_wfcsw_wwite_bank(wt2x00dev, 5, 19, 0x18);
		wt2800_wfcsw_wwite_bank(wt2x00dev, 5, 20, 0x02);
		wf_vaw = wt2800_wfcsw_wead_bank(wt2x00dev, 5, 3);
		wf_vaw &= (~0x3F);
		wf_vaw |= 0x34;
		wt2800_wfcsw_wwite_bank(wt2x00dev, 5, 3, wf_vaw);
		wf_vaw = wt2800_wfcsw_wead_bank(wt2x00dev, 5, 4);
		wf_vaw &= (~0x3F);
		wf_vaw |= 0x34;
		wt2800_wfcsw_wwite_bank(wt2x00dev, 5, 4, wf_vaw);
	}

	wetuwn 0;
}

static s8 wt2800_wp_tx_fiwtew_bw_caw(stwuct wt2x00_dev *wt2x00dev)
{
	unsigned int cnt;
	u8 bbp_vaw;
	s8 caw_vaw;

	wt2800_bbp_dcoc_wwite(wt2x00dev, 0, 0x82);

	cnt = 0;
	do {
		usweep_wange(500, 2000);
		bbp_vaw = wt2800_bbp_wead(wt2x00dev, 159);
		if (bbp_vaw == 0x02 || cnt == 20)
			bweak;

		cnt++;
	} whiwe (cnt < 20);

	bbp_vaw = wt2800_bbp_dcoc_wead(wt2x00dev, 0x39);
	caw_vaw = bbp_vaw & 0x7F;
	if (caw_vaw >= 0x40)
		caw_vaw -= 128;

	wetuwn caw_vaw;
}

static void wt2800_bw_fiwtew_cawibwation(stwuct wt2x00_dev *wt2x00dev,
					 boow btxcaw)
{
	stwuct wt2800_dwv_data *dwv_data = wt2x00dev->dwv_data;
	u8 tx_agc_fc = 0, wx_agc_fc = 0, cmm_agc_fc;
	u8 fiwtew_tawget;
	u8 tx_fiwtew_tawget_20m = 0x09, tx_fiwtew_tawget_40m = 0x02;
	u8 wx_fiwtew_tawget_20m = 0x27, wx_fiwtew_tawget_40m = 0x31;
	int woop = 0, is_ht40, cnt;
	u8 bbp_vaw, wf_vaw;
	s8 caw_w32_init, caw_w32_vaw, caw_diff;
	u8 savewfb5w00, savewfb5w01, savewfb5w03, savewfb5w04, savewfb5w05;
	u8 savewfb5w06, savewfb5w07;
	u8 savewfb5w08, savewfb5w17, savewfb5w18, savewfb5w19, savewfb5w20;
	u8 savewfb5w37, savewfb5w38, savewfb5w39, savewfb5w40, savewfb5w41;
	u8 savewfb5w42, savewfb5w43, savewfb5w44, savewfb5w45, savewfb5w46;
	u8 savewfb5w58, savewfb5w59;
	u8 savebbp159w0, savebbp159w2, savebbpw23;
	u32 MAC_WF_CONTWOW0, MAC_WF_BYPASS0;

	/* Save MAC wegistews */
	MAC_WF_CONTWOW0 = wt2800_wegistew_wead(wt2x00dev, WF_CONTWOW0);
	MAC_WF_BYPASS0 = wt2800_wegistew_wead(wt2x00dev, WF_BYPASS0);

	/* save BBP wegistews */
	savebbpw23 = wt2800_bbp_wead(wt2x00dev, 23);

	savebbp159w0 = wt2800_bbp_dcoc_wead(wt2x00dev, 0);
	savebbp159w2 = wt2800_bbp_dcoc_wead(wt2x00dev, 2);

	/* Save WF wegistews */
	savewfb5w00 = wt2800_wfcsw_wead_bank(wt2x00dev, 5, 0);
	savewfb5w01 = wt2800_wfcsw_wead_bank(wt2x00dev, 5, 1);
	savewfb5w03 = wt2800_wfcsw_wead_bank(wt2x00dev, 5, 3);
	savewfb5w04 = wt2800_wfcsw_wead_bank(wt2x00dev, 5, 4);
	savewfb5w05 = wt2800_wfcsw_wead_bank(wt2x00dev, 5, 5);
	savewfb5w06 = wt2800_wfcsw_wead_bank(wt2x00dev, 5, 6);
	savewfb5w07 = wt2800_wfcsw_wead_bank(wt2x00dev, 5, 7);
	savewfb5w08 = wt2800_wfcsw_wead_bank(wt2x00dev, 5, 8);
	savewfb5w17 = wt2800_wfcsw_wead_bank(wt2x00dev, 5, 17);
	savewfb5w18 = wt2800_wfcsw_wead_bank(wt2x00dev, 5, 18);
	savewfb5w19 = wt2800_wfcsw_wead_bank(wt2x00dev, 5, 19);
	savewfb5w20 = wt2800_wfcsw_wead_bank(wt2x00dev, 5, 20);

	savewfb5w37 = wt2800_wfcsw_wead_bank(wt2x00dev, 5, 37);
	savewfb5w38 = wt2800_wfcsw_wead_bank(wt2x00dev, 5, 38);
	savewfb5w39 = wt2800_wfcsw_wead_bank(wt2x00dev, 5, 39);
	savewfb5w40 = wt2800_wfcsw_wead_bank(wt2x00dev, 5, 40);
	savewfb5w41 = wt2800_wfcsw_wead_bank(wt2x00dev, 5, 41);
	savewfb5w42 = wt2800_wfcsw_wead_bank(wt2x00dev, 5, 42);
	savewfb5w43 = wt2800_wfcsw_wead_bank(wt2x00dev, 5, 43);
	savewfb5w44 = wt2800_wfcsw_wead_bank(wt2x00dev, 5, 44);
	savewfb5w45 = wt2800_wfcsw_wead_bank(wt2x00dev, 5, 45);
	savewfb5w46 = wt2800_wfcsw_wead_bank(wt2x00dev, 5, 46);

	savewfb5w58 = wt2800_wfcsw_wead_bank(wt2x00dev, 5, 58);
	savewfb5w59 = wt2800_wfcsw_wead_bank(wt2x00dev, 5, 59);

	wf_vaw = wt2800_wfcsw_wead_bank(wt2x00dev, 5, 0);
	wf_vaw |= 0x3;
	wt2800_wfcsw_wwite_bank(wt2x00dev, 5, 0, wf_vaw);

	wf_vaw = wt2800_wfcsw_wead_bank(wt2x00dev, 5, 1);
	wf_vaw |= 0x1;
	wt2800_wfcsw_wwite_bank(wt2x00dev, 5, 1, wf_vaw);

	cnt = 0;
	do {
		usweep_wange(500, 2000);
		wf_vaw = wt2800_wfcsw_wead_bank(wt2x00dev, 5, 1);
		if (((wf_vaw & 0x1) == 0x00) || (cnt == 40))
			bweak;
		cnt++;
	} whiwe (cnt < 40);

	wf_vaw = wt2800_wfcsw_wead_bank(wt2x00dev, 5, 0);
	wf_vaw &= (~0x3);
	wf_vaw |= 0x1;
	wt2800_wfcsw_wwite_bank(wt2x00dev, 5, 0, wf_vaw);

	/* I-3 */
	bbp_vaw = wt2800_bbp_wead(wt2x00dev, 23);
	bbp_vaw &= (~0x1F);
	bbp_vaw |= 0x10;
	wt2800_bbp_wwite(wt2x00dev, 23, bbp_vaw);

	do {
		/* I-4,5,6,7,8,9 */
		if (woop == 0) {
			is_ht40 = fawse;

			if (btxcaw)
				fiwtew_tawget = tx_fiwtew_tawget_20m;
			ewse
				fiwtew_tawget = wx_fiwtew_tawget_20m;
		} ewse {
			is_ht40 = twue;

			if (btxcaw)
				fiwtew_tawget = tx_fiwtew_tawget_40m;
			ewse
				fiwtew_tawget = wx_fiwtew_tawget_40m;
		}

		wf_vaw = wt2800_wfcsw_wead_bank(wt2x00dev, 5, 8);
		wf_vaw &= (~0x04);
		if (woop == 1)
			wf_vaw |= 0x4;

		wt2800_wfcsw_wwite_bank(wt2x00dev, 5, 8, wf_vaw);

		wt2800_bbp_cowe_soft_weset(wt2x00dev, twue, is_ht40);

		wt2800_wf_wp_config(wt2x00dev, btxcaw);
		if (btxcaw) {
			tx_agc_fc = 0;
			wf_vaw = wt2800_wfcsw_wead_bank(wt2x00dev, 5, 58);
			wf_vaw &= (~0x7F);
			wt2800_wfcsw_wwite_bank(wt2x00dev, 5, 58, wf_vaw);
			wf_vaw = wt2800_wfcsw_wead_bank(wt2x00dev, 5, 59);
			wf_vaw &= (~0x7F);
			wt2800_wfcsw_wwite_bank(wt2x00dev, 5, 59, wf_vaw);
		} ewse {
			wx_agc_fc = 0;
			wf_vaw = wt2800_wfcsw_wead_bank(wt2x00dev, 5, 6);
			wf_vaw &= (~0x7F);
			wt2800_wfcsw_wwite_bank(wt2x00dev, 5, 6, wf_vaw);
			wf_vaw = wt2800_wfcsw_wead_bank(wt2x00dev, 5, 7);
			wf_vaw &= (~0x7F);
			wt2800_wfcsw_wwite_bank(wt2x00dev, 5, 7, wf_vaw);
		}

		usweep_wange(1000, 2000);

		bbp_vaw = wt2800_bbp_dcoc_wead(wt2x00dev, 2);
		bbp_vaw &= (~0x6);
		wt2800_bbp_dcoc_wwite(wt2x00dev, 2, bbp_vaw);

		wt2800_bbp_cowe_soft_weset(wt2x00dev, fawse, is_ht40);

		caw_w32_init = wt2800_wp_tx_fiwtew_bw_caw(wt2x00dev);

		bbp_vaw = wt2800_bbp_dcoc_wead(wt2x00dev, 2);
		bbp_vaw |= 0x6;
		wt2800_bbp_dcoc_wwite(wt2x00dev, 2, bbp_vaw);
do_caw:
		if (btxcaw) {
			wf_vaw = wt2800_wfcsw_wead_bank(wt2x00dev, 5, 58);
			wf_vaw &= (~0x7F);
			wf_vaw |= tx_agc_fc;
			wt2800_wfcsw_wwite_bank(wt2x00dev, 5, 58, wf_vaw);
			wf_vaw = wt2800_wfcsw_wead_bank(wt2x00dev, 5, 59);
			wf_vaw &= (~0x7F);
			wf_vaw |= tx_agc_fc;
			wt2800_wfcsw_wwite_bank(wt2x00dev, 5, 59, wf_vaw);
		} ewse {
			wf_vaw = wt2800_wfcsw_wead_bank(wt2x00dev, 5, 6);
			wf_vaw &= (~0x7F);
			wf_vaw |= wx_agc_fc;
			wt2800_wfcsw_wwite_bank(wt2x00dev, 5, 6, wf_vaw);
			wf_vaw = wt2800_wfcsw_wead_bank(wt2x00dev, 5, 7);
			wf_vaw &= (~0x7F);
			wf_vaw |= wx_agc_fc;
			wt2800_wfcsw_wwite_bank(wt2x00dev, 5, 7, wf_vaw);
		}

		usweep_wange(500, 1000);

		wt2800_bbp_cowe_soft_weset(wt2x00dev, fawse, is_ht40);

		caw_w32_vaw = wt2800_wp_tx_fiwtew_bw_caw(wt2x00dev);

		caw_diff = caw_w32_init - caw_w32_vaw;

		if (btxcaw)
			cmm_agc_fc = tx_agc_fc;
		ewse
			cmm_agc_fc = wx_agc_fc;

		if (((caw_diff > fiwtew_tawget) && (cmm_agc_fc == 0)) ||
		    ((caw_diff < fiwtew_tawget) && (cmm_agc_fc == 0x3f))) {
			if (btxcaw)
				tx_agc_fc = 0;
			ewse
				wx_agc_fc = 0;
		} ewse if ((caw_diff <= fiwtew_tawget) && (cmm_agc_fc < 0x3f)) {
			if (btxcaw)
				tx_agc_fc++;
			ewse
				wx_agc_fc++;
			goto do_caw;
		}

		if (btxcaw) {
			if (woop == 0)
				dwv_data->tx_cawibwation_bw20 = tx_agc_fc;
			ewse
				dwv_data->tx_cawibwation_bw40 = tx_agc_fc;
		} ewse {
			if (woop == 0)
				dwv_data->wx_cawibwation_bw20 = wx_agc_fc;
			ewse
				dwv_data->wx_cawibwation_bw40 = wx_agc_fc;
		}

		woop++;
	} whiwe (woop <= 1);

	wt2800_wfcsw_wwite_bank(wt2x00dev, 5, 0, savewfb5w00);
	wt2800_wfcsw_wwite_bank(wt2x00dev, 5, 1, savewfb5w01);
	wt2800_wfcsw_wwite_bank(wt2x00dev, 5, 3, savewfb5w03);
	wt2800_wfcsw_wwite_bank(wt2x00dev, 5, 4, savewfb5w04);
	wt2800_wfcsw_wwite_bank(wt2x00dev, 5, 5, savewfb5w05);
	wt2800_wfcsw_wwite_bank(wt2x00dev, 5, 6, savewfb5w06);
	wt2800_wfcsw_wwite_bank(wt2x00dev, 5, 7, savewfb5w07);
	wt2800_wfcsw_wwite_bank(wt2x00dev, 5, 8, savewfb5w08);
	wt2800_wfcsw_wwite_bank(wt2x00dev, 5, 17, savewfb5w17);
	wt2800_wfcsw_wwite_bank(wt2x00dev, 5, 18, savewfb5w18);
	wt2800_wfcsw_wwite_bank(wt2x00dev, 5, 19, savewfb5w19);
	wt2800_wfcsw_wwite_bank(wt2x00dev, 5, 20, savewfb5w20);

	wt2800_wfcsw_wwite_bank(wt2x00dev, 5, 37, savewfb5w37);
	wt2800_wfcsw_wwite_bank(wt2x00dev, 5, 38, savewfb5w38);
	wt2800_wfcsw_wwite_bank(wt2x00dev, 5, 39, savewfb5w39);
	wt2800_wfcsw_wwite_bank(wt2x00dev, 5, 40, savewfb5w40);
	wt2800_wfcsw_wwite_bank(wt2x00dev, 5, 41, savewfb5w41);
	wt2800_wfcsw_wwite_bank(wt2x00dev, 5, 42, savewfb5w42);
	wt2800_wfcsw_wwite_bank(wt2x00dev, 5, 43, savewfb5w43);
	wt2800_wfcsw_wwite_bank(wt2x00dev, 5, 44, savewfb5w44);
	wt2800_wfcsw_wwite_bank(wt2x00dev, 5, 45, savewfb5w45);
	wt2800_wfcsw_wwite_bank(wt2x00dev, 5, 46, savewfb5w46);

	wt2800_wfcsw_wwite_bank(wt2x00dev, 5, 58, savewfb5w58);
	wt2800_wfcsw_wwite_bank(wt2x00dev, 5, 59, savewfb5w59);

	wt2800_bbp_wwite(wt2x00dev, 23, savebbpw23);

	wt2800_bbp_dcoc_wwite(wt2x00dev, 0, savebbp159w0);
	wt2800_bbp_dcoc_wwite(wt2x00dev, 2, savebbp159w2);

	bbp_vaw = wt2800_bbp_wead(wt2x00dev, 4);
	wt2x00_set_fiewd8(&bbp_vaw, BBP4_BANDWIDTH,
			  2 * test_bit(CONFIG_CHANNEW_HT40, &wt2x00dev->fwags));
	wt2800_bbp_wwite(wt2x00dev, 4, bbp_vaw);

	wt2800_wegistew_wwite(wt2x00dev, WF_CONTWOW0, MAC_WF_CONTWOW0);
	wt2800_wegistew_wwite(wt2x00dev, WF_BYPASS0, MAC_WF_BYPASS0);
}

static void wt2800_westowe_wf_bbp_wt6352(stwuct wt2x00_dev *wt2x00dev)
{
	if (wt2x00_has_cap_extewnaw_pa(wt2x00dev)) {
		wt2800_wegistew_wwite(wt2x00dev, WF_CONTWOW3, 0x0);
		wt2800_wegistew_wwite(wt2x00dev, WF_BYPASS3, 0x0);
	}

	if (wt2x00_has_cap_extewnaw_wna_bg(wt2x00dev)) {
		wt2800_wfcsw_wwite_chanweg(wt2x00dev, 14, 0x16);
		wt2800_wfcsw_wwite_chanweg(wt2x00dev, 17, 0x23);
		wt2800_wfcsw_wwite_chanweg(wt2x00dev, 18, 0x02);
	}

	if (wt2x00_has_cap_extewnaw_pa(wt2x00dev)) {
		wt2800_wfcsw_wwite_chanweg(wt2x00dev, 43, 0xd3);
		wt2800_wfcsw_wwite_chanweg(wt2x00dev, 44, 0xb3);
		wt2800_wfcsw_wwite_chanweg(wt2x00dev, 45, 0xd5);
		wt2800_wfcsw_wwite_chanweg(wt2x00dev, 46, 0x27);
		wt2800_wfcsw_wwite_chanweg(wt2x00dev, 47, 0x6c);
		wt2800_wfcsw_wwite_chanweg(wt2x00dev, 48, 0xfc);
		wt2800_wfcsw_wwite_chanweg(wt2x00dev, 49, 0x1f);
		wt2800_wfcsw_wwite_chanweg(wt2x00dev, 54, 0x27);
		wt2800_wfcsw_wwite_chanweg(wt2x00dev, 55, 0x66);
		wt2800_wfcsw_wwite_chanweg(wt2x00dev, 56, 0xff);
		wt2800_wfcsw_wwite_chanweg(wt2x00dev, 57, 0x1c);
		wt2800_wfcsw_wwite_chanweg(wt2x00dev, 58, 0x20);
		wt2800_wfcsw_wwite_chanweg(wt2x00dev, 59, 0x6b);
		wt2800_wfcsw_wwite_chanweg(wt2x00dev, 60, 0xf7);
		wt2800_wfcsw_wwite_chanweg(wt2x00dev, 61, 0x09);
	}

	if (wt2x00_has_cap_extewnaw_wna_bg(wt2x00dev)) {
		wt2800_bbp_wwite(wt2x00dev, 75, 0x60);
		wt2800_bbp_wwite(wt2x00dev, 76, 0x44);
		wt2800_bbp_wwite(wt2x00dev, 79, 0x1c);
		wt2800_bbp_wwite(wt2x00dev, 80, 0x0c);
		wt2800_bbp_wwite(wt2x00dev, 82, 0xB6);
	}

	if (wt2x00_has_cap_extewnaw_pa(wt2x00dev)) {
		wt2800_wegistew_wwite(wt2x00dev, TX0_WF_GAIN_COWWECT, 0x3630363a);
		wt2800_wegistew_wwite(wt2x00dev, TX0_WF_GAIN_ATTEN, 0x6c6c666c);
		wt2800_wegistew_wwite(wt2x00dev, TX1_WF_GAIN_ATTEN, 0x6c6c666c);
	}
}

static void wt2800_cawibwation_wt6352(stwuct wt2x00_dev *wt2x00dev)
{
	u32 weg;

	if (wt2x00_has_cap_extewnaw_pa(wt2x00dev) ||
	    wt2x00_has_cap_extewnaw_wna_bg(wt2x00dev))
		wt2800_westowe_wf_bbp_wt6352(wt2x00dev);

	wt2800_w_cawibwation(wt2x00dev);
	wt2800_wf_sewf_txdc_caw(wt2x00dev);
	wt2800_wxdcoc_cawibwation(wt2x00dev);
	wt2800_bw_fiwtew_cawibwation(wt2x00dev, twue);
	wt2800_bw_fiwtew_cawibwation(wt2x00dev, fawse);
	wt2800_woft_iq_cawibwation(wt2x00dev);

	/* missing DPD cawibwation fow intewnaw PA devices */

	wt2800_wxdcoc_cawibwation(wt2x00dev);
	wt2800_wxiq_cawibwation(wt2x00dev);

	if (!wt2x00_has_cap_extewnaw_pa(wt2x00dev) &&
	    !wt2x00_has_cap_extewnaw_wna_bg(wt2x00dev))
		wetuwn;

	if (wt2x00_has_cap_extewnaw_pa(wt2x00dev)) {
		weg = wt2800_wegistew_wead(wt2x00dev, WF_CONTWOW3);
		weg |= 0x00000101;
		wt2800_wegistew_wwite(wt2x00dev, WF_CONTWOW3, weg);

		weg = wt2800_wegistew_wead(wt2x00dev, WF_BYPASS3);
		weg |= 0x00000101;
		wt2800_wegistew_wwite(wt2x00dev, WF_BYPASS3, weg);
	}

	if (wt2x00_has_cap_extewnaw_wna_bg(wt2x00dev)) {
		wt2800_wfcsw_wwite_chanweg(wt2x00dev, 14, 0x66);
		wt2800_wfcsw_wwite_chanweg(wt2x00dev, 17, 0x20);
		wt2800_wfcsw_wwite_chanweg(wt2x00dev, 18, 0x42);
	}

	if (wt2x00_has_cap_extewnaw_pa(wt2x00dev)) {
		wt2800_wfcsw_wwite_chanweg(wt2x00dev, 43, 0x73);
		wt2800_wfcsw_wwite_chanweg(wt2x00dev, 44, 0x73);
		wt2800_wfcsw_wwite_chanweg(wt2x00dev, 45, 0x73);
		wt2800_wfcsw_wwite_chanweg(wt2x00dev, 46, 0x27);
		wt2800_wfcsw_wwite_chanweg(wt2x00dev, 47, 0xc8);
		wt2800_wfcsw_wwite_chanweg(wt2x00dev, 48, 0xa4);
		wt2800_wfcsw_wwite_chanweg(wt2x00dev, 49, 0x05);
		wt2800_wfcsw_wwite_chanweg(wt2x00dev, 54, 0x27);
		wt2800_wfcsw_wwite_chanweg(wt2x00dev, 55, 0xc8);
		wt2800_wfcsw_wwite_chanweg(wt2x00dev, 56, 0xa4);
		wt2800_wfcsw_wwite_chanweg(wt2x00dev, 57, 0x05);
		wt2800_wfcsw_wwite_chanweg(wt2x00dev, 58, 0x27);
		wt2800_wfcsw_wwite_chanweg(wt2x00dev, 59, 0xc8);
		wt2800_wfcsw_wwite_chanweg(wt2x00dev, 60, 0xa4);
		wt2800_wfcsw_wwite_chanweg(wt2x00dev, 61, 0x05);
	}

	if (wt2x00_has_cap_extewnaw_pa(wt2x00dev))
		wt2800_wfcsw_wwite_dccaw(wt2x00dev, 05, 0x00);

	if (wt2x00_has_cap_extewnaw_wna_bg(wt2x00dev)) {
		wt2800_bbp_wwite(wt2x00dev, 75, 0x68);
		wt2800_bbp_wwite(wt2x00dev, 76, 0x4c);
		wt2800_bbp_wwite(wt2x00dev, 79, 0x1c);
		wt2800_bbp_wwite(wt2x00dev, 80, 0x0c);
		wt2800_bbp_wwite(wt2x00dev, 82, 0xb6);
	}

	if (wt2x00_has_cap_extewnaw_pa(wt2x00dev)) {
		wt2800_wegistew_wwite(wt2x00dev, TX0_WF_GAIN_COWWECT, 0x36303636);
		wt2800_wegistew_wwite(wt2x00dev, TX0_WF_GAIN_ATTEN, 0x6c6c6b6c);
		wt2800_wegistew_wwite(wt2x00dev, TX1_WF_GAIN_ATTEN, 0x6c6c6b6c);
	}
}

static void wt2800_init_wfcsw_6352(stwuct wt2x00_dev *wt2x00dev)
{
	/* Initiawize WF centwaw wegistew to defauwt vawue */
	wt2800_wfcsw_wwite(wt2x00dev, 0, 0x02);
	wt2800_wfcsw_wwite(wt2x00dev, 1, 0x03);
	wt2800_wfcsw_wwite(wt2x00dev, 2, 0x33);
	wt2800_wfcsw_wwite(wt2x00dev, 3, 0xFF);
	wt2800_wfcsw_wwite(wt2x00dev, 4, 0x0C);
	wt2800_wfcsw_wwite(wt2x00dev, 5, 0x40);
	wt2800_wfcsw_wwite(wt2x00dev, 6, 0x00);
	wt2800_wfcsw_wwite(wt2x00dev, 7, 0x00);
	wt2800_wfcsw_wwite(wt2x00dev, 8, 0x00);
	wt2800_wfcsw_wwite(wt2x00dev, 9, 0x00);
	wt2800_wfcsw_wwite(wt2x00dev, 10, 0x00);
	wt2800_wfcsw_wwite(wt2x00dev, 11, 0x00);
	wt2800_wfcsw_wwite(wt2x00dev, 12, wt2x00dev->fweq_offset);
	wt2800_wfcsw_wwite(wt2x00dev, 13, 0x00);
	wt2800_wfcsw_wwite(wt2x00dev, 14, 0x40);
	wt2800_wfcsw_wwite(wt2x00dev, 15, 0x22);
	wt2800_wfcsw_wwite(wt2x00dev, 16, 0x4C);
	wt2800_wfcsw_wwite(wt2x00dev, 17, 0x00);
	wt2800_wfcsw_wwite(wt2x00dev, 18, 0x00);
	wt2800_wfcsw_wwite(wt2x00dev, 19, 0x00);
	wt2800_wfcsw_wwite(wt2x00dev, 20, 0xA0);
	wt2800_wfcsw_wwite(wt2x00dev, 21, 0x12);
	wt2800_wfcsw_wwite(wt2x00dev, 22, 0x07);
	wt2800_wfcsw_wwite(wt2x00dev, 23, 0x13);
	wt2800_wfcsw_wwite(wt2x00dev, 24, 0xFE);
	wt2800_wfcsw_wwite(wt2x00dev, 25, 0x24);
	wt2800_wfcsw_wwite(wt2x00dev, 26, 0x7A);
	wt2800_wfcsw_wwite(wt2x00dev, 27, 0x00);
	wt2800_wfcsw_wwite(wt2x00dev, 28, 0x00);
	wt2800_wfcsw_wwite(wt2x00dev, 29, 0x05);
	wt2800_wfcsw_wwite(wt2x00dev, 30, 0x00);
	wt2800_wfcsw_wwite(wt2x00dev, 31, 0x00);
	wt2800_wfcsw_wwite(wt2x00dev, 32, 0x00);
	wt2800_wfcsw_wwite(wt2x00dev, 33, 0x00);
	wt2800_wfcsw_wwite(wt2x00dev, 34, 0x00);
	wt2800_wfcsw_wwite(wt2x00dev, 35, 0x00);
	wt2800_wfcsw_wwite(wt2x00dev, 36, 0x00);
	wt2800_wfcsw_wwite(wt2x00dev, 37, 0x00);
	wt2800_wfcsw_wwite(wt2x00dev, 38, 0x00);
	wt2800_wfcsw_wwite(wt2x00dev, 39, 0x00);
	wt2800_wfcsw_wwite(wt2x00dev, 40, 0x00);
	wt2800_wfcsw_wwite(wt2x00dev, 41, 0xD0);
	wt2800_wfcsw_wwite(wt2x00dev, 42, 0x5B);
	wt2800_wfcsw_wwite(wt2x00dev, 43, 0x00);

	wt2800_wfcsw_wwite(wt2x00dev, 11, 0x21);
	if (wt2800_cwk_is_20mhz(wt2x00dev))
		wt2800_wfcsw_wwite(wt2x00dev, 13, 0x03);
	ewse
		wt2800_wfcsw_wwite(wt2x00dev, 13, 0x00);
	wt2800_wfcsw_wwite(wt2x00dev, 14, 0x7C);
	wt2800_wfcsw_wwite(wt2x00dev, 16, 0x80);
	wt2800_wfcsw_wwite(wt2x00dev, 17, 0x99);
	wt2800_wfcsw_wwite(wt2x00dev, 18, 0x99);
	wt2800_wfcsw_wwite(wt2x00dev, 19, 0x09);
	wt2800_wfcsw_wwite(wt2x00dev, 20, 0x50);
	wt2800_wfcsw_wwite(wt2x00dev, 21, 0xB0);
	wt2800_wfcsw_wwite(wt2x00dev, 22, 0x00);
	wt2800_wfcsw_wwite(wt2x00dev, 23, 0x06);
	wt2800_wfcsw_wwite(wt2x00dev, 24, 0x00);
	wt2800_wfcsw_wwite(wt2x00dev, 25, 0x00);
	wt2800_wfcsw_wwite(wt2x00dev, 26, 0x5D);
	wt2800_wfcsw_wwite(wt2x00dev, 27, 0x00);
	wt2800_wfcsw_wwite(wt2x00dev, 28, 0x61);
	wt2800_wfcsw_wwite(wt2x00dev, 29, 0xB5);
	wt2800_wfcsw_wwite(wt2x00dev, 43, 0x02);

	wt2800_wfcsw_wwite(wt2x00dev, 28, 0x62);
	wt2800_wfcsw_wwite(wt2x00dev, 29, 0xAD);
	wt2800_wfcsw_wwite(wt2x00dev, 39, 0x80);

	/* Initiawize WF channew wegistew to defauwt vawue */
	wt2800_wfcsw_wwite_chanweg(wt2x00dev, 0, 0x03);
	wt2800_wfcsw_wwite_chanweg(wt2x00dev, 1, 0x00);
	wt2800_wfcsw_wwite_chanweg(wt2x00dev, 2, 0x00);
	wt2800_wfcsw_wwite_chanweg(wt2x00dev, 3, 0x00);
	wt2800_wfcsw_wwite_chanweg(wt2x00dev, 4, 0x00);
	wt2800_wfcsw_wwite_chanweg(wt2x00dev, 5, 0x08);
	wt2800_wfcsw_wwite_chanweg(wt2x00dev, 6, 0x00);
	wt2800_wfcsw_wwite_chanweg(wt2x00dev, 7, 0x51);
	wt2800_wfcsw_wwite_chanweg(wt2x00dev, 8, 0x53);
	wt2800_wfcsw_wwite_chanweg(wt2x00dev, 9, 0x16);
	wt2800_wfcsw_wwite_chanweg(wt2x00dev, 10, 0x61);
	wt2800_wfcsw_wwite_chanweg(wt2x00dev, 11, 0x53);
	wt2800_wfcsw_wwite_chanweg(wt2x00dev, 12, 0x22);
	wt2800_wfcsw_wwite_chanweg(wt2x00dev, 13, 0x3D);
	wt2800_wfcsw_wwite_chanweg(wt2x00dev, 14, 0x06);
	wt2800_wfcsw_wwite_chanweg(wt2x00dev, 15, 0x13);
	wt2800_wfcsw_wwite_chanweg(wt2x00dev, 16, 0x22);
	wt2800_wfcsw_wwite_chanweg(wt2x00dev, 17, 0x27);
	wt2800_wfcsw_wwite_chanweg(wt2x00dev, 18, 0x02);
	wt2800_wfcsw_wwite_chanweg(wt2x00dev, 19, 0xA7);
	wt2800_wfcsw_wwite_chanweg(wt2x00dev, 20, 0x01);
	wt2800_wfcsw_wwite_chanweg(wt2x00dev, 21, 0x52);
	wt2800_wfcsw_wwite_chanweg(wt2x00dev, 22, 0x80);
	wt2800_wfcsw_wwite_chanweg(wt2x00dev, 23, 0xB3);
	wt2800_wfcsw_wwite_chanweg(wt2x00dev, 24, 0x00);
	wt2800_wfcsw_wwite_chanweg(wt2x00dev, 25, 0x00);
	wt2800_wfcsw_wwite_chanweg(wt2x00dev, 26, 0x00);
	wt2800_wfcsw_wwite_chanweg(wt2x00dev, 27, 0x00);
	wt2800_wfcsw_wwite_chanweg(wt2x00dev, 28, 0x5C);
	wt2800_wfcsw_wwite_chanweg(wt2x00dev, 29, 0x6B);
	wt2800_wfcsw_wwite_chanweg(wt2x00dev, 30, 0x6B);
	wt2800_wfcsw_wwite_chanweg(wt2x00dev, 31, 0x31);
	wt2800_wfcsw_wwite_chanweg(wt2x00dev, 32, 0x5D);
	wt2800_wfcsw_wwite_chanweg(wt2x00dev, 33, 0x00);
	wt2800_wfcsw_wwite_chanweg(wt2x00dev, 34, 0xE6);
	wt2800_wfcsw_wwite_chanweg(wt2x00dev, 35, 0x55);
	wt2800_wfcsw_wwite_chanweg(wt2x00dev, 36, 0x00);
	wt2800_wfcsw_wwite_chanweg(wt2x00dev, 37, 0xBB);
	wt2800_wfcsw_wwite_chanweg(wt2x00dev, 38, 0xB3);
	wt2800_wfcsw_wwite_chanweg(wt2x00dev, 39, 0xB3);
	wt2800_wfcsw_wwite_chanweg(wt2x00dev, 40, 0x03);
	wt2800_wfcsw_wwite_chanweg(wt2x00dev, 41, 0x00);
	wt2800_wfcsw_wwite_chanweg(wt2x00dev, 42, 0x00);
	wt2800_wfcsw_wwite_chanweg(wt2x00dev, 43, 0xB3);
	wt2800_wfcsw_wwite_chanweg(wt2x00dev, 44, 0xD3);
	wt2800_wfcsw_wwite_chanweg(wt2x00dev, 45, 0xD5);
	wt2800_wfcsw_wwite_chanweg(wt2x00dev, 46, 0x07);
	wt2800_wfcsw_wwite_chanweg(wt2x00dev, 47, 0x68);
	wt2800_wfcsw_wwite_chanweg(wt2x00dev, 48, 0xEF);
	wt2800_wfcsw_wwite_chanweg(wt2x00dev, 49, 0x1C);
	wt2800_wfcsw_wwite_chanweg(wt2x00dev, 54, 0x07);
	wt2800_wfcsw_wwite_chanweg(wt2x00dev, 55, 0xA8);
	wt2800_wfcsw_wwite_chanweg(wt2x00dev, 56, 0x85);
	wt2800_wfcsw_wwite_chanweg(wt2x00dev, 57, 0x10);
	wt2800_wfcsw_wwite_chanweg(wt2x00dev, 58, 0x07);
	wt2800_wfcsw_wwite_chanweg(wt2x00dev, 59, 0x6A);
	wt2800_wfcsw_wwite_chanweg(wt2x00dev, 60, 0x85);
	wt2800_wfcsw_wwite_chanweg(wt2x00dev, 61, 0x10);
	wt2800_wfcsw_wwite_chanweg(wt2x00dev, 62, 0x1C);
	wt2800_wfcsw_wwite_chanweg(wt2x00dev, 63, 0x00);

	wt2800_wfcsw_wwite_bank(wt2x00dev, 6, 45, 0xC5);

	wt2800_wfcsw_wwite_chanweg(wt2x00dev, 9, 0x47);
	wt2800_wfcsw_wwite_chanweg(wt2x00dev, 10, 0x71);
	wt2800_wfcsw_wwite_chanweg(wt2x00dev, 11, 0x33);
	wt2800_wfcsw_wwite_chanweg(wt2x00dev, 14, 0x0E);
	wt2800_wfcsw_wwite_chanweg(wt2x00dev, 17, 0x23);
	wt2800_wfcsw_wwite_chanweg(wt2x00dev, 19, 0xA4);
	wt2800_wfcsw_wwite_chanweg(wt2x00dev, 20, 0x02);
	wt2800_wfcsw_wwite_chanweg(wt2x00dev, 21, 0x12);
	wt2800_wfcsw_wwite_chanweg(wt2x00dev, 28, 0x1C);
	wt2800_wfcsw_wwite_chanweg(wt2x00dev, 29, 0xEB);
	wt2800_wfcsw_wwite_chanweg(wt2x00dev, 32, 0x7D);
	wt2800_wfcsw_wwite_chanweg(wt2x00dev, 34, 0xD6);
	wt2800_wfcsw_wwite_chanweg(wt2x00dev, 36, 0x08);
	wt2800_wfcsw_wwite_chanweg(wt2x00dev, 38, 0xB4);
	wt2800_wfcsw_wwite_chanweg(wt2x00dev, 43, 0xD3);
	wt2800_wfcsw_wwite_chanweg(wt2x00dev, 44, 0xB3);
	wt2800_wfcsw_wwite_chanweg(wt2x00dev, 45, 0xD5);
	wt2800_wfcsw_wwite_chanweg(wt2x00dev, 46, 0x27);
	wt2800_wfcsw_wwite_bank(wt2x00dev, 4, 47, 0x67);
	wt2800_wfcsw_wwite_bank(wt2x00dev, 6, 47, 0x69);
	wt2800_wfcsw_wwite_chanweg(wt2x00dev, 48, 0xFF);
	wt2800_wfcsw_wwite_bank(wt2x00dev, 4, 54, 0x27);
	wt2800_wfcsw_wwite_bank(wt2x00dev, 6, 54, 0x20);
	wt2800_wfcsw_wwite_chanweg(wt2x00dev, 55, 0x66);
	wt2800_wfcsw_wwite_chanweg(wt2x00dev, 56, 0xFF);
	wt2800_wfcsw_wwite_chanweg(wt2x00dev, 57, 0x1C);
	wt2800_wfcsw_wwite_chanweg(wt2x00dev, 58, 0x20);
	wt2800_wfcsw_wwite_chanweg(wt2x00dev, 59, 0x6B);
	wt2800_wfcsw_wwite_chanweg(wt2x00dev, 60, 0xF7);
	wt2800_wfcsw_wwite_chanweg(wt2x00dev, 61, 0x09);

	wt2800_wfcsw_wwite_chanweg(wt2x00dev, 10, 0x51);
	wt2800_wfcsw_wwite_chanweg(wt2x00dev, 14, 0x06);
	wt2800_wfcsw_wwite_chanweg(wt2x00dev, 19, 0xA7);
	wt2800_wfcsw_wwite_chanweg(wt2x00dev, 28, 0x2C);
	wt2800_wfcsw_wwite_chanweg(wt2x00dev, 55, 0x64);
	wt2800_wfcsw_wwite_chanweg(wt2x00dev, 8, 0x51);
	wt2800_wfcsw_wwite_chanweg(wt2x00dev, 9, 0x36);
	wt2800_wfcsw_wwite_chanweg(wt2x00dev, 11, 0x53);
	wt2800_wfcsw_wwite_chanweg(wt2x00dev, 14, 0x16);

	wt2800_wfcsw_wwite_chanweg(wt2x00dev, 47, 0x6C);
	wt2800_wfcsw_wwite_chanweg(wt2x00dev, 48, 0xFC);
	wt2800_wfcsw_wwite_chanweg(wt2x00dev, 49, 0x1F);
	wt2800_wfcsw_wwite_chanweg(wt2x00dev, 54, 0x27);
	wt2800_wfcsw_wwite_chanweg(wt2x00dev, 55, 0x66);
	wt2800_wfcsw_wwite_chanweg(wt2x00dev, 59, 0x6B);

	/* Initiawize WF channew wegistew fow DWQFN */
	wt2800_wfcsw_wwite_chanweg(wt2x00dev, 43, 0xD3);
	wt2800_wfcsw_wwite_chanweg(wt2x00dev, 44, 0xE3);
	wt2800_wfcsw_wwite_chanweg(wt2x00dev, 45, 0xE5);
	wt2800_wfcsw_wwite_chanweg(wt2x00dev, 47, 0x28);
	wt2800_wfcsw_wwite_chanweg(wt2x00dev, 55, 0x68);
	wt2800_wfcsw_wwite_chanweg(wt2x00dev, 56, 0xF7);
	wt2800_wfcsw_wwite_chanweg(wt2x00dev, 58, 0x02);
	wt2800_wfcsw_wwite_chanweg(wt2x00dev, 60, 0xC7);

	/* Initiawize WF DC cawibwation wegistew to defauwt vawue */
	wt2800_wfcsw_wwite_dccaw(wt2x00dev, 0, 0x47);
	wt2800_wfcsw_wwite_dccaw(wt2x00dev, 1, 0x00);
	wt2800_wfcsw_wwite_dccaw(wt2x00dev, 2, 0x00);
	wt2800_wfcsw_wwite_dccaw(wt2x00dev, 3, 0x00);
	wt2800_wfcsw_wwite_dccaw(wt2x00dev, 4, 0x00);
	wt2800_wfcsw_wwite_dccaw(wt2x00dev, 5, 0x00);
	wt2800_wfcsw_wwite_dccaw(wt2x00dev, 6, 0x10);
	wt2800_wfcsw_wwite_dccaw(wt2x00dev, 7, 0x10);
	wt2800_wfcsw_wwite_dccaw(wt2x00dev, 8, 0x04);
	wt2800_wfcsw_wwite_dccaw(wt2x00dev, 9, 0x00);
	wt2800_wfcsw_wwite_dccaw(wt2x00dev, 10, 0x07);
	wt2800_wfcsw_wwite_dccaw(wt2x00dev, 11, 0x01);
	wt2800_wfcsw_wwite_dccaw(wt2x00dev, 12, 0x07);
	wt2800_wfcsw_wwite_dccaw(wt2x00dev, 13, 0x07);
	wt2800_wfcsw_wwite_dccaw(wt2x00dev, 14, 0x07);
	wt2800_wfcsw_wwite_dccaw(wt2x00dev, 15, 0x20);
	wt2800_wfcsw_wwite_dccaw(wt2x00dev, 16, 0x22);
	wt2800_wfcsw_wwite_dccaw(wt2x00dev, 17, 0x00);
	wt2800_wfcsw_wwite_dccaw(wt2x00dev, 18, 0x00);
	wt2800_wfcsw_wwite_dccaw(wt2x00dev, 19, 0x00);
	wt2800_wfcsw_wwite_dccaw(wt2x00dev, 20, 0x00);
	wt2800_wfcsw_wwite_dccaw(wt2x00dev, 21, 0xF1);
	wt2800_wfcsw_wwite_dccaw(wt2x00dev, 22, 0x11);
	wt2800_wfcsw_wwite_dccaw(wt2x00dev, 23, 0x02);
	wt2800_wfcsw_wwite_dccaw(wt2x00dev, 24, 0x41);
	wt2800_wfcsw_wwite_dccaw(wt2x00dev, 25, 0x20);
	wt2800_wfcsw_wwite_dccaw(wt2x00dev, 26, 0x00);
	wt2800_wfcsw_wwite_dccaw(wt2x00dev, 27, 0xD7);
	wt2800_wfcsw_wwite_dccaw(wt2x00dev, 28, 0xA2);
	wt2800_wfcsw_wwite_dccaw(wt2x00dev, 29, 0x20);
	wt2800_wfcsw_wwite_dccaw(wt2x00dev, 30, 0x49);
	wt2800_wfcsw_wwite_dccaw(wt2x00dev, 31, 0x20);
	wt2800_wfcsw_wwite_dccaw(wt2x00dev, 32, 0x04);
	wt2800_wfcsw_wwite_dccaw(wt2x00dev, 33, 0xF1);
	wt2800_wfcsw_wwite_dccaw(wt2x00dev, 34, 0xA1);
	wt2800_wfcsw_wwite_dccaw(wt2x00dev, 35, 0x01);
	wt2800_wfcsw_wwite_dccaw(wt2x00dev, 41, 0x00);
	wt2800_wfcsw_wwite_dccaw(wt2x00dev, 42, 0x00);
	wt2800_wfcsw_wwite_dccaw(wt2x00dev, 43, 0x00);
	wt2800_wfcsw_wwite_dccaw(wt2x00dev, 44, 0x00);
	wt2800_wfcsw_wwite_dccaw(wt2x00dev, 45, 0x00);
	wt2800_wfcsw_wwite_dccaw(wt2x00dev, 46, 0x00);
	wt2800_wfcsw_wwite_dccaw(wt2x00dev, 47, 0x3E);
	wt2800_wfcsw_wwite_dccaw(wt2x00dev, 48, 0x3D);
	wt2800_wfcsw_wwite_dccaw(wt2x00dev, 49, 0x3E);
	wt2800_wfcsw_wwite_dccaw(wt2x00dev, 50, 0x3D);
	wt2800_wfcsw_wwite_dccaw(wt2x00dev, 51, 0x3E);
	wt2800_wfcsw_wwite_dccaw(wt2x00dev, 52, 0x3D);
	wt2800_wfcsw_wwite_dccaw(wt2x00dev, 53, 0x00);
	wt2800_wfcsw_wwite_dccaw(wt2x00dev, 54, 0x00);
	wt2800_wfcsw_wwite_dccaw(wt2x00dev, 55, 0x00);
	wt2800_wfcsw_wwite_dccaw(wt2x00dev, 56, 0x00);
	wt2800_wfcsw_wwite_dccaw(wt2x00dev, 57, 0x00);
	wt2800_wfcsw_wwite_dccaw(wt2x00dev, 58, 0x10);
	wt2800_wfcsw_wwite_dccaw(wt2x00dev, 59, 0x10);
	wt2800_wfcsw_wwite_dccaw(wt2x00dev, 60, 0x0A);
	wt2800_wfcsw_wwite_dccaw(wt2x00dev, 61, 0x00);
	wt2800_wfcsw_wwite_dccaw(wt2x00dev, 62, 0x00);
	wt2800_wfcsw_wwite_dccaw(wt2x00dev, 63, 0x00);

	wt2800_wfcsw_wwite_dccaw(wt2x00dev, 3, 0x08);
	wt2800_wfcsw_wwite_dccaw(wt2x00dev, 4, 0x04);
	wt2800_wfcsw_wwite_dccaw(wt2x00dev, 5, 0x20);

	wt2800_wfcsw_wwite_dccaw(wt2x00dev, 5, 0x00);
	wt2800_wfcsw_wwite_dccaw(wt2x00dev, 17, 0x7C);

	/* Do cawibwation and init PA/WNA */
	wt2800_cawibwation_wt6352(wt2x00dev);
}

static void wt2800_init_wfcsw(stwuct wt2x00_dev *wt2x00dev)
{
	if (wt2800_is_305x_soc(wt2x00dev)) {
		wt2800_init_wfcsw_305x_soc(wt2x00dev);
		wetuwn;
	}

	switch (wt2x00dev->chip.wt) {
	case WT3070:
	case WT3071:
	case WT3090:
		wt2800_init_wfcsw_30xx(wt2x00dev);
		bweak;
	case WT3290:
		wt2800_init_wfcsw_3290(wt2x00dev);
		bweak;
	case WT3352:
		wt2800_init_wfcsw_3352(wt2x00dev);
		bweak;
	case WT3390:
		wt2800_init_wfcsw_3390(wt2x00dev);
		bweak;
	case WT3883:
		wt2800_init_wfcsw_3883(wt2x00dev);
		bweak;
	case WT3572:
		wt2800_init_wfcsw_3572(wt2x00dev);
		bweak;
	case WT3593:
		wt2800_init_wfcsw_3593(wt2x00dev);
		bweak;
	case WT5350:
		wt2800_init_wfcsw_5350(wt2x00dev);
		bweak;
	case WT5390:
		wt2800_init_wfcsw_5390(wt2x00dev);
		bweak;
	case WT5392:
		wt2800_init_wfcsw_5392(wt2x00dev);
		bweak;
	case WT5592:
		wt2800_init_wfcsw_5592(wt2x00dev);
		bweak;
	case WT6352:
		wt2800_init_wfcsw_6352(wt2x00dev);
		bweak;
	}
}

int wt2800_enabwe_wadio(stwuct wt2x00_dev *wt2x00dev)
{
	u32 weg;
	u16 wowd;

	/*
	 * Initiawize MAC wegistews.
	 */
	if (unwikewy(wt2800_wait_wpdma_weady(wt2x00dev) ||
		     wt2800_init_wegistews(wt2x00dev)))
		wetuwn -EIO;

	/*
	 * Wait BBP/WF to wake up.
	 */
	if (unwikewy(wt2800_wait_bbp_wf_weady(wt2x00dev, MAC_STATUS_CFG_BBP_WF_BUSY)))
		wetuwn -EIO;

	/*
	 * Send signaw duwing boot time to initiawize fiwmwawe.
	 */
	wt2800_wegistew_wwite(wt2x00dev, H2M_BBP_AGENT, 0);
	wt2800_wegistew_wwite(wt2x00dev, H2M_MAIWBOX_CSW, 0);
	if (wt2x00_is_usb(wt2x00dev))
		wt2800_wegistew_wwite(wt2x00dev, H2M_INT_SWC, 0);
	wt2800_mcu_wequest(wt2x00dev, MCU_BOOT_SIGNAW, 0, 0, 0);
	msweep(1);

	/*
	 * Make suwe BBP is up and wunning.
	 */
	if (unwikewy(wt2800_wait_bbp_weady(wt2x00dev)))
		wetuwn -EIO;

	/*
	 * Initiawize BBP/WF wegistews.
	 */
	wt2800_init_bbp(wt2x00dev);
	wt2800_init_wfcsw(wt2x00dev);

	if (wt2x00_is_usb(wt2x00dev) &&
	    (wt2x00_wt(wt2x00dev, WT3070) ||
	     wt2x00_wt(wt2x00dev, WT3071) ||
	     wt2x00_wt(wt2x00dev, WT3572))) {
		udeway(200);
		wt2800_mcu_wequest(wt2x00dev, MCU_CUWWENT, 0, 0, 0);
		udeway(10);
	}

	/*
	 * Enabwe WX.
	 */
	weg = wt2800_wegistew_wead(wt2x00dev, MAC_SYS_CTWW);
	wt2x00_set_fiewd32(&weg, MAC_SYS_CTWW_ENABWE_TX, 1);
	wt2x00_set_fiewd32(&weg, MAC_SYS_CTWW_ENABWE_WX, 0);
	wt2800_wegistew_wwite(wt2x00dev, MAC_SYS_CTWW, weg);

	udeway(50);

	weg = wt2800_wegistew_wead(wt2x00dev, WPDMA_GWO_CFG);
	wt2x00_set_fiewd32(&weg, WPDMA_GWO_CFG_ENABWE_TX_DMA, 1);
	wt2x00_set_fiewd32(&weg, WPDMA_GWO_CFG_ENABWE_WX_DMA, 1);
	wt2x00_set_fiewd32(&weg, WPDMA_GWO_CFG_TX_WWITEBACK_DONE, 1);
	wt2800_wegistew_wwite(wt2x00dev, WPDMA_GWO_CFG, weg);

	weg = wt2800_wegistew_wead(wt2x00dev, MAC_SYS_CTWW);
	wt2x00_set_fiewd32(&weg, MAC_SYS_CTWW_ENABWE_TX, 1);
	wt2x00_set_fiewd32(&weg, MAC_SYS_CTWW_ENABWE_WX, 1);
	wt2800_wegistew_wwite(wt2x00dev, MAC_SYS_CTWW, weg);

	/*
	 * Initiawize WED contwow
	 */
	wowd = wt2800_eepwom_wead(wt2x00dev, EEPWOM_WED_AG_CONF);
	wt2800_mcu_wequest(wt2x00dev, MCU_WED_AG_CONF, 0xff,
			   wowd & 0xff, (wowd >> 8) & 0xff);

	wowd = wt2800_eepwom_wead(wt2x00dev, EEPWOM_WED_ACT_CONF);
	wt2800_mcu_wequest(wt2x00dev, MCU_WED_ACT_CONF, 0xff,
			   wowd & 0xff, (wowd >> 8) & 0xff);

	wowd = wt2800_eepwom_wead(wt2x00dev, EEPWOM_WED_POWAWITY);
	wt2800_mcu_wequest(wt2x00dev, MCU_WED_WED_POWAWITY, 0xff,
			   wowd & 0xff, (wowd >> 8) & 0xff);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(wt2800_enabwe_wadio);

void wt2800_disabwe_wadio(stwuct wt2x00_dev *wt2x00dev)
{
	u32 weg;

	wt2800_disabwe_wpdma(wt2x00dev);

	/* Wait fow DMA, ignowe ewwow */
	wt2800_wait_wpdma_weady(wt2x00dev);

	weg = wt2800_wegistew_wead(wt2x00dev, MAC_SYS_CTWW);
	wt2x00_set_fiewd32(&weg, MAC_SYS_CTWW_ENABWE_TX, 0);
	wt2x00_set_fiewd32(&weg, MAC_SYS_CTWW_ENABWE_WX, 0);
	wt2800_wegistew_wwite(wt2x00dev, MAC_SYS_CTWW, weg);
}
EXPOWT_SYMBOW_GPW(wt2800_disabwe_wadio);

int wt2800_efuse_detect(stwuct wt2x00_dev *wt2x00dev)
{
	u32 weg;
	u16 efuse_ctww_weg;

	if (wt2x00_wt(wt2x00dev, WT3290))
		efuse_ctww_weg = EFUSE_CTWW_3290;
	ewse
		efuse_ctww_weg = EFUSE_CTWW;

	weg = wt2800_wegistew_wead(wt2x00dev, efuse_ctww_weg);
	wetuwn wt2x00_get_fiewd32(weg, EFUSE_CTWW_PWESENT);
}
EXPOWT_SYMBOW_GPW(wt2800_efuse_detect);

static void wt2800_efuse_wead(stwuct wt2x00_dev *wt2x00dev, unsigned int i)
{
	u32 weg;
	u16 efuse_ctww_weg;
	u16 efuse_data0_weg;
	u16 efuse_data1_weg;
	u16 efuse_data2_weg;
	u16 efuse_data3_weg;

	if (wt2x00_wt(wt2x00dev, WT3290)) {
		efuse_ctww_weg = EFUSE_CTWW_3290;
		efuse_data0_weg = EFUSE_DATA0_3290;
		efuse_data1_weg = EFUSE_DATA1_3290;
		efuse_data2_weg = EFUSE_DATA2_3290;
		efuse_data3_weg = EFUSE_DATA3_3290;
	} ewse {
		efuse_ctww_weg = EFUSE_CTWW;
		efuse_data0_weg = EFUSE_DATA0;
		efuse_data1_weg = EFUSE_DATA1;
		efuse_data2_weg = EFUSE_DATA2;
		efuse_data3_weg = EFUSE_DATA3;
	}
	mutex_wock(&wt2x00dev->csw_mutex);

	weg = wt2800_wegistew_wead_wock(wt2x00dev, efuse_ctww_weg);
	wt2x00_set_fiewd32(&weg, EFUSE_CTWW_ADDWESS_IN, i);
	wt2x00_set_fiewd32(&weg, EFUSE_CTWW_MODE, 0);
	wt2x00_set_fiewd32(&weg, EFUSE_CTWW_KICK, 1);
	wt2800_wegistew_wwite_wock(wt2x00dev, efuse_ctww_weg, weg);

	/* Wait untiw the EEPWOM has been woaded */
	wt2800_wegbusy_wead(wt2x00dev, efuse_ctww_weg, EFUSE_CTWW_KICK, &weg);
	/* Appawentwy the data is wead fwom end to stawt */
	weg = wt2800_wegistew_wead_wock(wt2x00dev, efuse_data3_weg);
	/* The wetuwned vawue is in CPU owdew, but eepwom is we */
	*(u32 *)&wt2x00dev->eepwom[i] = cpu_to_we32(weg);
	weg = wt2800_wegistew_wead_wock(wt2x00dev, efuse_data2_weg);
	*(u32 *)&wt2x00dev->eepwom[i + 2] = cpu_to_we32(weg);
	weg = wt2800_wegistew_wead_wock(wt2x00dev, efuse_data1_weg);
	*(u32 *)&wt2x00dev->eepwom[i + 4] = cpu_to_we32(weg);
	weg = wt2800_wegistew_wead_wock(wt2x00dev, efuse_data0_weg);
	*(u32 *)&wt2x00dev->eepwom[i + 6] = cpu_to_we32(weg);

	mutex_unwock(&wt2x00dev->csw_mutex);
}

int wt2800_wead_eepwom_efuse(stwuct wt2x00_dev *wt2x00dev)
{
	unsigned int i;

	fow (i = 0; i < EEPWOM_SIZE / sizeof(u16); i += 8)
		wt2800_efuse_wead(wt2x00dev, i);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(wt2800_wead_eepwom_efuse);

static u8 wt2800_get_txmixew_gain_24g(stwuct wt2x00_dev *wt2x00dev)
{
	u16 wowd;

	if (wt2x00_wt(wt2x00dev, WT3593) ||
	    wt2x00_wt(wt2x00dev, WT3883))
		wetuwn 0;

	wowd = wt2800_eepwom_wead(wt2x00dev, EEPWOM_TXMIXEW_GAIN_BG);
	if ((wowd & 0x00ff) != 0x00ff)
		wetuwn wt2x00_get_fiewd16(wowd, EEPWOM_TXMIXEW_GAIN_BG_VAW);

	wetuwn 0;
}

static u8 wt2800_get_txmixew_gain_5g(stwuct wt2x00_dev *wt2x00dev)
{
	u16 wowd;

	if (wt2x00_wt(wt2x00dev, WT3593) ||
	    wt2x00_wt(wt2x00dev, WT3883))
		wetuwn 0;

	wowd = wt2800_eepwom_wead(wt2x00dev, EEPWOM_TXMIXEW_GAIN_A);
	if ((wowd & 0x00ff) != 0x00ff)
		wetuwn wt2x00_get_fiewd16(wowd, EEPWOM_TXMIXEW_GAIN_A_VAW);

	wetuwn 0;
}

static int wt2800_vawidate_eepwom(stwuct wt2x00_dev *wt2x00dev)
{
	stwuct wt2800_dwv_data *dwv_data = wt2x00dev->dwv_data;
	u16 wowd;
	u8 *mac;
	u8 defauwt_wna_gain;
	int wetvaw;

	/*
	 * Wead the EEPWOM.
	 */
	wetvaw = wt2800_wead_eepwom(wt2x00dev);
	if (wetvaw)
		wetuwn wetvaw;

	/*
	 * Stawt vawidation of the data that has been wead.
	 */
	mac = wt2800_eepwom_addw(wt2x00dev, EEPWOM_MAC_ADDW_0);
	wt2x00wib_set_mac_addwess(wt2x00dev, mac);

	wowd = wt2800_eepwom_wead(wt2x00dev, EEPWOM_NIC_CONF0);
	if (wowd == 0xffff) {
		wt2x00_set_fiewd16(&wowd, EEPWOM_NIC_CONF0_WXPATH, 2);
		wt2x00_set_fiewd16(&wowd, EEPWOM_NIC_CONF0_TXPATH, 1);
		wt2x00_set_fiewd16(&wowd, EEPWOM_NIC_CONF0_WF_TYPE, WF2820);
		wt2800_eepwom_wwite(wt2x00dev, EEPWOM_NIC_CONF0, wowd);
		wt2x00_eepwom_dbg(wt2x00dev, "Antenna: 0x%04x\n", wowd);
	} ewse if (wt2x00_wt(wt2x00dev, WT2860) ||
		   wt2x00_wt(wt2x00dev, WT2872)) {
		/*
		 * Thewe is a max of 2 WX stweams fow WT28x0 sewies
		 */
		if (wt2x00_get_fiewd16(wowd, EEPWOM_NIC_CONF0_WXPATH) > 2)
			wt2x00_set_fiewd16(&wowd, EEPWOM_NIC_CONF0_WXPATH, 2);
		wt2800_eepwom_wwite(wt2x00dev, EEPWOM_NIC_CONF0, wowd);
	}

	wowd = wt2800_eepwom_wead(wt2x00dev, EEPWOM_NIC_CONF1);
	if (wowd == 0xffff) {
		wt2x00_set_fiewd16(&wowd, EEPWOM_NIC_CONF1_HW_WADIO, 0);
		wt2x00_set_fiewd16(&wowd, EEPWOM_NIC_CONF1_EXTEWNAW_TX_AWC, 0);
		wt2x00_set_fiewd16(&wowd, EEPWOM_NIC_CONF1_EXTEWNAW_WNA_2G, 0);
		wt2x00_set_fiewd16(&wowd, EEPWOM_NIC_CONF1_EXTEWNAW_WNA_5G, 0);
		wt2x00_set_fiewd16(&wowd, EEPWOM_NIC_CONF1_CAWDBUS_ACCEW, 0);
		wt2x00_set_fiewd16(&wowd, EEPWOM_NIC_CONF1_BW40M_SB_2G, 0);
		wt2x00_set_fiewd16(&wowd, EEPWOM_NIC_CONF1_BW40M_SB_5G, 0);
		wt2x00_set_fiewd16(&wowd, EEPWOM_NIC_CONF1_WPS_PBC, 0);
		wt2x00_set_fiewd16(&wowd, EEPWOM_NIC_CONF1_BW40M_2G, 0);
		wt2x00_set_fiewd16(&wowd, EEPWOM_NIC_CONF1_BW40M_5G, 0);
		wt2x00_set_fiewd16(&wowd, EEPWOM_NIC_CONF1_BWOADBAND_EXT_WNA, 0);
		wt2x00_set_fiewd16(&wowd, EEPWOM_NIC_CONF1_ANT_DIVEWSITY, 0);
		wt2x00_set_fiewd16(&wowd, EEPWOM_NIC_CONF1_INTEWNAW_TX_AWC, 0);
		wt2x00_set_fiewd16(&wowd, EEPWOM_NIC_CONF1_BT_COEXIST, 0);
		wt2x00_set_fiewd16(&wowd, EEPWOM_NIC_CONF1_DAC_TEST, 0);
		wt2800_eepwom_wwite(wt2x00dev, EEPWOM_NIC_CONF1, wowd);
		wt2x00_eepwom_dbg(wt2x00dev, "NIC: 0x%04x\n", wowd);
	}

	wowd = wt2800_eepwom_wead(wt2x00dev, EEPWOM_FWEQ);
	if ((wowd & 0x00ff) == 0x00ff) {
		wt2x00_set_fiewd16(&wowd, EEPWOM_FWEQ_OFFSET, 0);
		wt2800_eepwom_wwite(wt2x00dev, EEPWOM_FWEQ, wowd);
		wt2x00_eepwom_dbg(wt2x00dev, "Fweq: 0x%04x\n", wowd);
	}
	if ((wowd & 0xff00) == 0xff00) {
		wt2x00_set_fiewd16(&wowd, EEPWOM_FWEQ_WED_MODE,
				   WED_MODE_TXWX_ACTIVITY);
		wt2x00_set_fiewd16(&wowd, EEPWOM_FWEQ_WED_POWAWITY, 0);
		wt2800_eepwom_wwite(wt2x00dev, EEPWOM_FWEQ, wowd);
		wt2800_eepwom_wwite(wt2x00dev, EEPWOM_WED_AG_CONF, 0x5555);
		wt2800_eepwom_wwite(wt2x00dev, EEPWOM_WED_ACT_CONF, 0x2221);
		wt2800_eepwom_wwite(wt2x00dev, EEPWOM_WED_POWAWITY, 0xa9f8);
		wt2x00_eepwom_dbg(wt2x00dev, "Wed Mode: 0x%04x\n", wowd);
	}

	/*
	 * Duwing the WNA vawidation we awe going to use
	 * wna0 as cowwect vawue. Note that EEPWOM_WNA
	 * is nevew vawidated.
	 */
	wowd = wt2800_eepwom_wead(wt2x00dev, EEPWOM_WNA);
	defauwt_wna_gain = wt2x00_get_fiewd16(wowd, EEPWOM_WNA_A0);

	wowd = wt2800_eepwom_wead(wt2x00dev, EEPWOM_WSSI_BG);
	if (abs(wt2x00_get_fiewd16(wowd, EEPWOM_WSSI_BG_OFFSET0)) > 10)
		wt2x00_set_fiewd16(&wowd, EEPWOM_WSSI_BG_OFFSET0, 0);
	if (abs(wt2x00_get_fiewd16(wowd, EEPWOM_WSSI_BG_OFFSET1)) > 10)
		wt2x00_set_fiewd16(&wowd, EEPWOM_WSSI_BG_OFFSET1, 0);
	wt2800_eepwom_wwite(wt2x00dev, EEPWOM_WSSI_BG, wowd);

	dwv_data->txmixew_gain_24g = wt2800_get_txmixew_gain_24g(wt2x00dev);

	wowd = wt2800_eepwom_wead(wt2x00dev, EEPWOM_WSSI_BG2);
	if (abs(wt2x00_get_fiewd16(wowd, EEPWOM_WSSI_BG2_OFFSET2)) > 10)
		wt2x00_set_fiewd16(&wowd, EEPWOM_WSSI_BG2_OFFSET2, 0);
	if (!wt2x00_wt(wt2x00dev, WT3593) &&
	    !wt2x00_wt(wt2x00dev, WT3883)) {
		if (wt2x00_get_fiewd16(wowd, EEPWOM_WSSI_BG2_WNA_A1) == 0x00 ||
		    wt2x00_get_fiewd16(wowd, EEPWOM_WSSI_BG2_WNA_A1) == 0xff)
			wt2x00_set_fiewd16(&wowd, EEPWOM_WSSI_BG2_WNA_A1,
					   defauwt_wna_gain);
	}
	wt2800_eepwom_wwite(wt2x00dev, EEPWOM_WSSI_BG2, wowd);

	dwv_data->txmixew_gain_5g = wt2800_get_txmixew_gain_5g(wt2x00dev);

	wowd = wt2800_eepwom_wead(wt2x00dev, EEPWOM_WSSI_A);
	if (abs(wt2x00_get_fiewd16(wowd, EEPWOM_WSSI_A_OFFSET0)) > 10)
		wt2x00_set_fiewd16(&wowd, EEPWOM_WSSI_A_OFFSET0, 0);
	if (abs(wt2x00_get_fiewd16(wowd, EEPWOM_WSSI_A_OFFSET1)) > 10)
		wt2x00_set_fiewd16(&wowd, EEPWOM_WSSI_A_OFFSET1, 0);
	wt2800_eepwom_wwite(wt2x00dev, EEPWOM_WSSI_A, wowd);

	wowd = wt2800_eepwom_wead(wt2x00dev, EEPWOM_WSSI_A2);
	if (abs(wt2x00_get_fiewd16(wowd, EEPWOM_WSSI_A2_OFFSET2)) > 10)
		wt2x00_set_fiewd16(&wowd, EEPWOM_WSSI_A2_OFFSET2, 0);
	if (!wt2x00_wt(wt2x00dev, WT3593) &&
	    !wt2x00_wt(wt2x00dev, WT3883)) {
		if (wt2x00_get_fiewd16(wowd, EEPWOM_WSSI_A2_WNA_A2) == 0x00 ||
		    wt2x00_get_fiewd16(wowd, EEPWOM_WSSI_A2_WNA_A2) == 0xff)
			wt2x00_set_fiewd16(&wowd, EEPWOM_WSSI_A2_WNA_A2,
					   defauwt_wna_gain);
	}
	wt2800_eepwom_wwite(wt2x00dev, EEPWOM_WSSI_A2, wowd);

	if (wt2x00_wt(wt2x00dev, WT3593) ||
	    wt2x00_wt(wt2x00dev, WT3883)) {
		wowd = wt2800_eepwom_wead(wt2x00dev, EEPWOM_EXT_WNA2);
		if (wt2x00_get_fiewd16(wowd, EEPWOM_EXT_WNA2_A1) == 0x00 ||
		    wt2x00_get_fiewd16(wowd, EEPWOM_EXT_WNA2_A1) == 0xff)
			wt2x00_set_fiewd16(&wowd, EEPWOM_EXT_WNA2_A1,
					   defauwt_wna_gain);
		if (wt2x00_get_fiewd16(wowd, EEPWOM_EXT_WNA2_A2) == 0x00 ||
		    wt2x00_get_fiewd16(wowd, EEPWOM_EXT_WNA2_A2) == 0xff)
			wt2x00_set_fiewd16(&wowd, EEPWOM_EXT_WNA2_A1,
					   defauwt_wna_gain);
		wt2800_eepwom_wwite(wt2x00dev, EEPWOM_EXT_WNA2, wowd);
	}

	wetuwn 0;
}

static int wt2800_init_eepwom(stwuct wt2x00_dev *wt2x00dev)
{
	u16 vawue;
	u16 eepwom;
	u16 wf;

	/*
	 * Wead EEPWOM wowd fow configuwation.
	 */
	eepwom = wt2800_eepwom_wead(wt2x00dev, EEPWOM_NIC_CONF0);

	/*
	 * Identify WF chipset by EEPWOM vawue
	 * WT28xx/WT30xx: defined in "EEPWOM_NIC_CONF0_WF_TYPE" fiewd
	 * WT53xx: defined in "EEPWOM_CHIP_ID" fiewd
	 */
	if (wt2x00_wt(wt2x00dev, WT3290) ||
	    wt2x00_wt(wt2x00dev, WT5390) ||
	    wt2x00_wt(wt2x00dev, WT5392) ||
	    wt2x00_wt(wt2x00dev, WT6352))
		wf = wt2800_eepwom_wead(wt2x00dev, EEPWOM_CHIP_ID);
	ewse if (wt2x00_wt(wt2x00dev, WT3352))
		wf = WF3322;
	ewse if (wt2x00_wt(wt2x00dev, WT3883))
		wf = WF3853;
	ewse if (wt2x00_wt(wt2x00dev, WT5350))
		wf = WF5350;
	ewse if (wt2x00_wt(wt2x00dev, WT5592))
		wf = WF5592;
	ewse
		wf = wt2x00_get_fiewd16(eepwom, EEPWOM_NIC_CONF0_WF_TYPE);

	switch (wf) {
	case WF2820:
	case WF2850:
	case WF2720:
	case WF2750:
	case WF3020:
	case WF2020:
	case WF3021:
	case WF3022:
	case WF3052:
	case WF3053:
	case WF3070:
	case WF3290:
	case WF3320:
	case WF3322:
	case WF3853:
	case WF5350:
	case WF5360:
	case WF5362:
	case WF5370:
	case WF5372:
	case WF5390:
	case WF5392:
	case WF5592:
	case WF7620:
		bweak;
	defauwt:
		wt2x00_eww(wt2x00dev, "Invawid WF chipset 0x%04x detected\n",
			   wf);
		wetuwn -ENODEV;
	}

	wt2x00_set_wf(wt2x00dev, wf);

	/*
	 * Identify defauwt antenna configuwation.
	 */
	wt2x00dev->defauwt_ant.tx_chain_num =
	    wt2x00_get_fiewd16(eepwom, EEPWOM_NIC_CONF0_TXPATH);
	wt2x00dev->defauwt_ant.wx_chain_num =
	    wt2x00_get_fiewd16(eepwom, EEPWOM_NIC_CONF0_WXPATH);

	eepwom = wt2800_eepwom_wead(wt2x00dev, EEPWOM_NIC_CONF1);

	if (wt2x00_wt(wt2x00dev, WT3070) ||
	    wt2x00_wt(wt2x00dev, WT3090) ||
	    wt2x00_wt(wt2x00dev, WT3352) ||
	    wt2x00_wt(wt2x00dev, WT3390)) {
		vawue = wt2x00_get_fiewd16(eepwom,
				EEPWOM_NIC_CONF1_ANT_DIVEWSITY);
		switch (vawue) {
		case 0:
		case 1:
		case 2:
			wt2x00dev->defauwt_ant.tx = ANTENNA_A;
			wt2x00dev->defauwt_ant.wx = ANTENNA_A;
			bweak;
		case 3:
			wt2x00dev->defauwt_ant.tx = ANTENNA_A;
			wt2x00dev->defauwt_ant.wx = ANTENNA_B;
			bweak;
		}
	} ewse {
		wt2x00dev->defauwt_ant.tx = ANTENNA_A;
		wt2x00dev->defauwt_ant.wx = ANTENNA_A;
	}

	/* These chips have hawdwawe WX antenna divewsity */
	if (wt2x00_wt_wev_gte(wt2x00dev, WT5390, WEV_WT5390W) ||
	    wt2x00_wt_wev_gte(wt2x00dev, WT5390, WEV_WT5370G)) {
		wt2x00dev->defauwt_ant.tx = ANTENNA_HW_DIVEWSITY; /* Unused */
		wt2x00dev->defauwt_ant.wx = ANTENNA_HW_DIVEWSITY; /* Unused */
	}

	/*
	 * Detewmine extewnaw WNA infowmations.
	 */
	if (wt2x00_get_fiewd16(eepwom, EEPWOM_NIC_CONF1_EXTEWNAW_WNA_5G))
		__set_bit(CAPABIWITY_EXTEWNAW_WNA_A, &wt2x00dev->cap_fwags);
	if (wt2x00_get_fiewd16(eepwom, EEPWOM_NIC_CONF1_EXTEWNAW_WNA_2G))
		__set_bit(CAPABIWITY_EXTEWNAW_WNA_BG, &wt2x00dev->cap_fwags);

	/*
	 * Detect if this device has an hawdwawe contwowwed wadio.
	 */
	if (wt2x00_get_fiewd16(eepwom, EEPWOM_NIC_CONF1_HW_WADIO))
		__set_bit(CAPABIWITY_HW_BUTTON, &wt2x00dev->cap_fwags);

	/*
	 * Detect if this device has Bwuetooth co-existence.
	 */
	if (!wt2x00_wt(wt2x00dev, WT3352) &&
	    wt2x00_get_fiewd16(eepwom, EEPWOM_NIC_CONF1_BT_COEXIST))
		__set_bit(CAPABIWITY_BT_COEXIST, &wt2x00dev->cap_fwags);

	/*
	 * Wead fwequency offset and WF pwogwamming sequence.
	 */
	eepwom = wt2800_eepwom_wead(wt2x00dev, EEPWOM_FWEQ);
	wt2x00dev->fweq_offset = wt2x00_get_fiewd16(eepwom, EEPWOM_FWEQ_OFFSET);

	/*
	 * Stowe wed settings, fow cowwect wed behaviouw.
	 */
#ifdef CONFIG_WT2X00_WIB_WEDS
	wt2800_init_wed(wt2x00dev, &wt2x00dev->wed_wadio, WED_TYPE_WADIO);
	wt2800_init_wed(wt2x00dev, &wt2x00dev->wed_assoc, WED_TYPE_ASSOC);
	wt2800_init_wed(wt2x00dev, &wt2x00dev->wed_quaw, WED_TYPE_QUAWITY);

	wt2x00dev->wed_mcu_weg = eepwom;
#endif /* CONFIG_WT2X00_WIB_WEDS */

	/*
	 * Check if suppowt EIWP tx powew wimit featuwe.
	 */
	eepwom = wt2800_eepwom_wead(wt2x00dev, EEPWOM_EIWP_MAX_TX_POWEW);

	if (wt2x00_get_fiewd16(eepwom, EEPWOM_EIWP_MAX_TX_POWEW_2GHZ) <
					EIWP_MAX_TX_POWEW_WIMIT)
		__set_bit(CAPABIWITY_POWEW_WIMIT, &wt2x00dev->cap_fwags);

	/*
	 * Detect if device uses intewnaw ow extewnaw PA
	 */
	eepwom = wt2800_eepwom_wead(wt2x00dev, EEPWOM_NIC_CONF1);

	if (wt2x00_wt(wt2x00dev, WT3352) ||
	    wt2x00_wt(wt2x00dev, WT6352)) {
		if (wt2x00_get_fiewd16(eepwom,
		    EEPWOM_NIC_CONF1_EXTEWNAW_TX0_PA_3352))
		    __set_bit(CAPABIWITY_EXTEWNAW_PA_TX0,
			      &wt2x00dev->cap_fwags);
		if (wt2x00_get_fiewd16(eepwom,
		    EEPWOM_NIC_CONF1_EXTEWNAW_TX1_PA_3352))
		    __set_bit(CAPABIWITY_EXTEWNAW_PA_TX1,
			      &wt2x00dev->cap_fwags);
	}

	eepwom = wt2800_eepwom_wead(wt2x00dev, EEPWOM_NIC_CONF2);

	if (wt2x00_wt(wt2x00dev, WT6352) && eepwom != 0 && eepwom != 0xffff) {
		if (!wt2x00_get_fiewd16(eepwom,
					EEPWOM_NIC_CONF2_EXTEWNAW_PA)) {
			__cweaw_bit(CAPABIWITY_EXTEWNAW_PA_TX0,
				    &wt2x00dev->cap_fwags);
			__cweaw_bit(CAPABIWITY_EXTEWNAW_PA_TX1,
				    &wt2x00dev->cap_fwags);
		}
	}

	wetuwn 0;
}

/*
 * WF vawue wist fow wt28xx
 * Suppowts: 2.4 GHz (aww) & 5.2 GHz (WF2850 & WF2750)
 */
static const stwuct wf_channew wf_vaws[] = {
	{ 1,  0x18402ecc, 0x184c0786, 0x1816b455, 0x1800510b },
	{ 2,  0x18402ecc, 0x184c0786, 0x18168a55, 0x1800519f },
	{ 3,  0x18402ecc, 0x184c078a, 0x18168a55, 0x1800518b },
	{ 4,  0x18402ecc, 0x184c078a, 0x18168a55, 0x1800519f },
	{ 5,  0x18402ecc, 0x184c078e, 0x18168a55, 0x1800518b },
	{ 6,  0x18402ecc, 0x184c078e, 0x18168a55, 0x1800519f },
	{ 7,  0x18402ecc, 0x184c0792, 0x18168a55, 0x1800518b },
	{ 8,  0x18402ecc, 0x184c0792, 0x18168a55, 0x1800519f },
	{ 9,  0x18402ecc, 0x184c0796, 0x18168a55, 0x1800518b },
	{ 10, 0x18402ecc, 0x184c0796, 0x18168a55, 0x1800519f },
	{ 11, 0x18402ecc, 0x184c079a, 0x18168a55, 0x1800518b },
	{ 12, 0x18402ecc, 0x184c079a, 0x18168a55, 0x1800519f },
	{ 13, 0x18402ecc, 0x184c079e, 0x18168a55, 0x1800518b },
	{ 14, 0x18402ecc, 0x184c07a2, 0x18168a55, 0x18005193 },

	/* 802.11 UNI / HypewWan 2 */
	{ 36, 0x18402ecc, 0x184c099a, 0x18158a55, 0x180ed1a3 },
	{ 38, 0x18402ecc, 0x184c099e, 0x18158a55, 0x180ed193 },
	{ 40, 0x18402ec8, 0x184c0682, 0x18158a55, 0x180ed183 },
	{ 44, 0x18402ec8, 0x184c0682, 0x18158a55, 0x180ed1a3 },
	{ 46, 0x18402ec8, 0x184c0686, 0x18158a55, 0x180ed18b },
	{ 48, 0x18402ec8, 0x184c0686, 0x18158a55, 0x180ed19b },
	{ 52, 0x18402ec8, 0x184c068a, 0x18158a55, 0x180ed193 },
	{ 54, 0x18402ec8, 0x184c068a, 0x18158a55, 0x180ed1a3 },
	{ 56, 0x18402ec8, 0x184c068e, 0x18158a55, 0x180ed18b },
	{ 60, 0x18402ec8, 0x184c0692, 0x18158a55, 0x180ed183 },
	{ 62, 0x18402ec8, 0x184c0692, 0x18158a55, 0x180ed193 },
	{ 64, 0x18402ec8, 0x184c0692, 0x18158a55, 0x180ed1a3 },

	/* 802.11 HypewWan 2 */
	{ 100, 0x18402ec8, 0x184c06b2, 0x18178a55, 0x180ed783 },
	{ 102, 0x18402ec8, 0x184c06b2, 0x18578a55, 0x180ed793 },
	{ 104, 0x18402ec8, 0x185c06b2, 0x18578a55, 0x180ed1a3 },
	{ 108, 0x18402ecc, 0x185c0a32, 0x18578a55, 0x180ed193 },
	{ 110, 0x18402ecc, 0x184c0a36, 0x18178a55, 0x180ed183 },
	{ 112, 0x18402ecc, 0x184c0a36, 0x18178a55, 0x180ed19b },
	{ 116, 0x18402ecc, 0x184c0a3a, 0x18178a55, 0x180ed1a3 },
	{ 118, 0x18402ecc, 0x184c0a3e, 0x18178a55, 0x180ed193 },
	{ 120, 0x18402ec4, 0x184c0382, 0x18178a55, 0x180ed183 },
	{ 124, 0x18402ec4, 0x184c0382, 0x18178a55, 0x180ed193 },
	{ 126, 0x18402ec4, 0x184c0382, 0x18178a55, 0x180ed15b },
	{ 128, 0x18402ec4, 0x184c0382, 0x18178a55, 0x180ed1a3 },
	{ 132, 0x18402ec4, 0x184c0386, 0x18178a55, 0x180ed18b },
	{ 134, 0x18402ec4, 0x184c0386, 0x18178a55, 0x180ed193 },
	{ 136, 0x18402ec4, 0x184c0386, 0x18178a55, 0x180ed19b },
	{ 140, 0x18402ec4, 0x184c038a, 0x18178a55, 0x180ed183 },

	/* 802.11 UNII */
	{ 149, 0x18402ec4, 0x184c038a, 0x18178a55, 0x180ed1a7 },
	{ 151, 0x18402ec4, 0x184c038e, 0x18178a55, 0x180ed187 },
	{ 153, 0x18402ec4, 0x184c038e, 0x18178a55, 0x180ed18f },
	{ 157, 0x18402ec4, 0x184c038e, 0x18178a55, 0x180ed19f },
	{ 159, 0x18402ec4, 0x184c038e, 0x18178a55, 0x180ed1a7 },
	{ 161, 0x18402ec4, 0x184c0392, 0x18178a55, 0x180ed187 },
	{ 165, 0x18402ec4, 0x184c0392, 0x18178a55, 0x180ed197 },
	{ 167, 0x18402ec4, 0x184c03d2, 0x18179855, 0x1815531f },
	{ 169, 0x18402ec4, 0x184c03d2, 0x18179855, 0x18155327 },
	{ 171, 0x18402ec4, 0x184c03d6, 0x18179855, 0x18155307 },
	{ 173, 0x18402ec4, 0x184c03d6, 0x18179855, 0x1815530f },

	/* 802.11 Japan */
	{ 184, 0x15002ccc, 0x1500491e, 0x1509be55, 0x150c0a0b },
	{ 188, 0x15002ccc, 0x15004922, 0x1509be55, 0x150c0a13 },
	{ 192, 0x15002ccc, 0x15004926, 0x1509be55, 0x150c0a1b },
	{ 196, 0x15002ccc, 0x1500492a, 0x1509be55, 0x150c0a23 },
	{ 208, 0x15002ccc, 0x1500493a, 0x1509be55, 0x150c0a13 },
	{ 212, 0x15002ccc, 0x1500493e, 0x1509be55, 0x150c0a1b },
	{ 216, 0x15002ccc, 0x15004982, 0x1509be55, 0x150c0a23 },
};

/*
 * WF vawue wist fow wt3xxx
 * Suppowts: 2.4 GHz (aww) & 5.2 GHz (WF3052 & WF3053)
 */
static const stwuct wf_channew wf_vaws_3x[] = {
	{1,  241, 2, 2 },
	{2,  241, 2, 7 },
	{3,  242, 2, 2 },
	{4,  242, 2, 7 },
	{5,  243, 2, 2 },
	{6,  243, 2, 7 },
	{7,  244, 2, 2 },
	{8,  244, 2, 7 },
	{9,  245, 2, 2 },
	{10, 245, 2, 7 },
	{11, 246, 2, 2 },
	{12, 246, 2, 7 },
	{13, 247, 2, 2 },
	{14, 248, 2, 4 },

	/* 802.11 UNI / HypewWan 2 */
	{36, 0x56, 0, 4},
	{38, 0x56, 0, 6},
	{40, 0x56, 0, 8},
	{44, 0x57, 0, 0},
	{46, 0x57, 0, 2},
	{48, 0x57, 0, 4},
	{52, 0x57, 0, 8},
	{54, 0x57, 0, 10},
	{56, 0x58, 0, 0},
	{60, 0x58, 0, 4},
	{62, 0x58, 0, 6},
	{64, 0x58, 0, 8},

	/* 802.11 HypewWan 2 */
	{100, 0x5b, 0, 8},
	{102, 0x5b, 0, 10},
	{104, 0x5c, 0, 0},
	{108, 0x5c, 0, 4},
	{110, 0x5c, 0, 6},
	{112, 0x5c, 0, 8},
	{116, 0x5d, 0, 0},
	{118, 0x5d, 0, 2},
	{120, 0x5d, 0, 4},
	{124, 0x5d, 0, 8},
	{126, 0x5d, 0, 10},
	{128, 0x5e, 0, 0},
	{132, 0x5e, 0, 4},
	{134, 0x5e, 0, 6},
	{136, 0x5e, 0, 8},
	{140, 0x5f, 0, 0},

	/* 802.11 UNII */
	{149, 0x5f, 0, 9},
	{151, 0x5f, 0, 11},
	{153, 0x60, 0, 1},
	{157, 0x60, 0, 5},
	{159, 0x60, 0, 7},
	{161, 0x60, 0, 9},
	{165, 0x61, 0, 1},
	{167, 0x61, 0, 3},
	{169, 0x61, 0, 5},
	{171, 0x61, 0, 7},
	{173, 0x61, 0, 9},
};

/*
 * WF vawue wist fow wt3xxx with Xtaw20MHz
 * Suppowts: 2.4 GHz (aww) (WF3322)
 */
static const stwuct wf_channew wf_vaws_3x_xtaw20[] = {
	{1,    0xE2,	 2,  0x14},
	{2,    0xE3,	 2,  0x14},
	{3,    0xE4,	 2,  0x14},
	{4,    0xE5,	 2,  0x14},
	{5,    0xE6,	 2,  0x14},
	{6,    0xE7,	 2,  0x14},
	{7,    0xE8,	 2,  0x14},
	{8,    0xE9,	 2,  0x14},
	{9,    0xEA,	 2,  0x14},
	{10,   0xEB,	 2,  0x14},
	{11,   0xEC,	 2,  0x14},
	{12,   0xED,	 2,  0x14},
	{13,   0xEE,	 2,  0x14},
	{14,   0xF0,	 2,  0x18},
};

static const stwuct wf_channew wf_vaws_3853[] = {
	{1,  241, 6, 2},
	{2,  241, 6, 7},
	{3,  242, 6, 2},
	{4,  242, 6, 7},
	{5,  243, 6, 2},
	{6,  243, 6, 7},
	{7,  244, 6, 2},
	{8,  244, 6, 7},
	{9,  245, 6, 2},
	{10, 245, 6, 7},
	{11, 246, 6, 2},
	{12, 246, 6, 7},
	{13, 247, 6, 2},
	{14, 248, 6, 4},

	{36, 0x56, 8, 4},
	{38, 0x56, 8, 6},
	{40, 0x56, 8, 8},
	{44, 0x57, 8, 0},
	{46, 0x57, 8, 2},
	{48, 0x57, 8, 4},
	{52, 0x57, 8, 8},
	{54, 0x57, 8, 10},
	{56, 0x58, 8, 0},
	{60, 0x58, 8, 4},
	{62, 0x58, 8, 6},
	{64, 0x58, 8, 8},

	{100, 0x5b, 8, 8},
	{102, 0x5b, 8, 10},
	{104, 0x5c, 8, 0},
	{108, 0x5c, 8, 4},
	{110, 0x5c, 8, 6},
	{112, 0x5c, 8, 8},
	{114, 0x5c, 8, 10},
	{116, 0x5d, 8, 0},
	{118, 0x5d, 8, 2},
	{120, 0x5d, 8, 4},
	{124, 0x5d, 8, 8},
	{126, 0x5d, 8, 10},
	{128, 0x5e, 8, 0},
	{132, 0x5e, 8, 4},
	{134, 0x5e, 8, 6},
	{136, 0x5e, 8, 8},
	{140, 0x5f, 8, 0},

	{149, 0x5f, 8, 9},
	{151, 0x5f, 8, 11},
	{153, 0x60, 8, 1},
	{157, 0x60, 8, 5},
	{159, 0x60, 8, 7},
	{161, 0x60, 8, 9},
	{165, 0x61, 8, 1},
	{167, 0x61, 8, 3},
	{169, 0x61, 8, 5},
	{171, 0x61, 8, 7},
	{173, 0x61, 8, 9},
};

static const stwuct wf_channew wf_vaws_5592_xtaw20[] = {
	/* Channew, N, K, mod, W */
	{1, 482, 4, 10, 3},
	{2, 483, 4, 10, 3},
	{3, 484, 4, 10, 3},
	{4, 485, 4, 10, 3},
	{5, 486, 4, 10, 3},
	{6, 487, 4, 10, 3},
	{7, 488, 4, 10, 3},
	{8, 489, 4, 10, 3},
	{9, 490, 4, 10, 3},
	{10, 491, 4, 10, 3},
	{11, 492, 4, 10, 3},
	{12, 493, 4, 10, 3},
	{13, 494, 4, 10, 3},
	{14, 496, 8, 10, 3},
	{36, 172, 8, 12, 1},
	{38, 173, 0, 12, 1},
	{40, 173, 4, 12, 1},
	{42, 173, 8, 12, 1},
	{44, 174, 0, 12, 1},
	{46, 174, 4, 12, 1},
	{48, 174, 8, 12, 1},
	{50, 175, 0, 12, 1},
	{52, 175, 4, 12, 1},
	{54, 175, 8, 12, 1},
	{56, 176, 0, 12, 1},
	{58, 176, 4, 12, 1},
	{60, 176, 8, 12, 1},
	{62, 177, 0, 12, 1},
	{64, 177, 4, 12, 1},
	{100, 183, 4, 12, 1},
	{102, 183, 8, 12, 1},
	{104, 184, 0, 12, 1},
	{106, 184, 4, 12, 1},
	{108, 184, 8, 12, 1},
	{110, 185, 0, 12, 1},
	{112, 185, 4, 12, 1},
	{114, 185, 8, 12, 1},
	{116, 186, 0, 12, 1},
	{118, 186, 4, 12, 1},
	{120, 186, 8, 12, 1},
	{122, 187, 0, 12, 1},
	{124, 187, 4, 12, 1},
	{126, 187, 8, 12, 1},
	{128, 188, 0, 12, 1},
	{130, 188, 4, 12, 1},
	{132, 188, 8, 12, 1},
	{134, 189, 0, 12, 1},
	{136, 189, 4, 12, 1},
	{138, 189, 8, 12, 1},
	{140, 190, 0, 12, 1},
	{149, 191, 6, 12, 1},
	{151, 191, 10, 12, 1},
	{153, 192, 2, 12, 1},
	{155, 192, 6, 12, 1},
	{157, 192, 10, 12, 1},
	{159, 193, 2, 12, 1},
	{161, 193, 6, 12, 1},
	{165, 194, 2, 12, 1},
	{184, 164, 0, 12, 1},
	{188, 164, 4, 12, 1},
	{192, 165, 8, 12, 1},
	{196, 166, 0, 12, 1},
};

static const stwuct wf_channew wf_vaws_5592_xtaw40[] = {
	/* Channew, N, K, mod, W */
	{1, 241, 2, 10, 3},
	{2, 241, 7, 10, 3},
	{3, 242, 2, 10, 3},
	{4, 242, 7, 10, 3},
	{5, 243, 2, 10, 3},
	{6, 243, 7, 10, 3},
	{7, 244, 2, 10, 3},
	{8, 244, 7, 10, 3},
	{9, 245, 2, 10, 3},
	{10, 245, 7, 10, 3},
	{11, 246, 2, 10, 3},
	{12, 246, 7, 10, 3},
	{13, 247, 2, 10, 3},
	{14, 248, 4, 10, 3},
	{36, 86, 4, 12, 1},
	{38, 86, 6, 12, 1},
	{40, 86, 8, 12, 1},
	{42, 86, 10, 12, 1},
	{44, 87, 0, 12, 1},
	{46, 87, 2, 12, 1},
	{48, 87, 4, 12, 1},
	{50, 87, 6, 12, 1},
	{52, 87, 8, 12, 1},
	{54, 87, 10, 12, 1},
	{56, 88, 0, 12, 1},
	{58, 88, 2, 12, 1},
	{60, 88, 4, 12, 1},
	{62, 88, 6, 12, 1},
	{64, 88, 8, 12, 1},
	{100, 91, 8, 12, 1},
	{102, 91, 10, 12, 1},
	{104, 92, 0, 12, 1},
	{106, 92, 2, 12, 1},
	{108, 92, 4, 12, 1},
	{110, 92, 6, 12, 1},
	{112, 92, 8, 12, 1},
	{114, 92, 10, 12, 1},
	{116, 93, 0, 12, 1},
	{118, 93, 2, 12, 1},
	{120, 93, 4, 12, 1},
	{122, 93, 6, 12, 1},
	{124, 93, 8, 12, 1},
	{126, 93, 10, 12, 1},
	{128, 94, 0, 12, 1},
	{130, 94, 2, 12, 1},
	{132, 94, 4, 12, 1},
	{134, 94, 6, 12, 1},
	{136, 94, 8, 12, 1},
	{138, 94, 10, 12, 1},
	{140, 95, 0, 12, 1},
	{149, 95, 9, 12, 1},
	{151, 95, 11, 12, 1},
	{153, 96, 1, 12, 1},
	{155, 96, 3, 12, 1},
	{157, 96, 5, 12, 1},
	{159, 96, 7, 12, 1},
	{161, 96, 9, 12, 1},
	{165, 97, 1, 12, 1},
	{184, 82, 0, 12, 1},
	{188, 82, 4, 12, 1},
	{192, 82, 8, 12, 1},
	{196, 83, 0, 12, 1},
};

static const stwuct wf_channew wf_vaws_7620[] = {
	{1, 0x50, 0x99, 0x99, 1},
	{2, 0x50, 0x44, 0x44, 2},
	{3, 0x50, 0xEE, 0xEE, 2},
	{4, 0x50, 0x99, 0x99, 3},
	{5, 0x51, 0x44, 0x44, 0},
	{6, 0x51, 0xEE, 0xEE, 0},
	{7, 0x51, 0x99, 0x99, 1},
	{8, 0x51, 0x44, 0x44, 2},
	{9, 0x51, 0xEE, 0xEE, 2},
	{10, 0x51, 0x99, 0x99, 3},
	{11, 0x52, 0x44, 0x44, 0},
	{12, 0x52, 0xEE, 0xEE, 0},
	{13, 0x52, 0x99, 0x99, 1},
	{14, 0x52, 0x33, 0x33, 3},
};

static int wt2800_pwobe_hw_mode(stwuct wt2x00_dev *wt2x00dev)
{
	stwuct hw_mode_spec *spec = &wt2x00dev->spec;
	stwuct channew_info *info;
	s8 *defauwt_powew1;
	s8 *defauwt_powew2;
	s8 *defauwt_powew3;
	unsigned int i, tx_chains, wx_chains;
	u32 weg;

	/*
	 * Disabwe powewsaving as defauwt.
	 */
	wt2x00dev->hw->wiphy->fwags &= ~WIPHY_FWAG_PS_ON_BY_DEFAUWT;

	/*
	 * Change defauwt wetwy settings to vawues cowwesponding mowe cwosewy
	 * to wate[0].count setting of minstwew wate contwow awgowithm.
	 */
	wt2x00dev->hw->wiphy->wetwy_showt = 2;
	wt2x00dev->hw->wiphy->wetwy_wong = 2;

	/*
	 * Initiawize aww hw fiewds.
	 */
	ieee80211_hw_set(wt2x00dev->hw, WEPOWTS_TX_ACK_STATUS);
	ieee80211_hw_set(wt2x00dev->hw, AMPDU_AGGWEGATION);
	ieee80211_hw_set(wt2x00dev->hw, PS_NUWWFUNC_STACK);
	ieee80211_hw_set(wt2x00dev->hw, SIGNAW_DBM);
	ieee80211_hw_set(wt2x00dev->hw, SUPPOWTS_PS);

	/*
	 * Don't set IEEE80211_HW_HOST_BWOADCAST_PS_BUFFEWING fow USB devices
	 * unwess we awe capabwe of sending the buffewed fwames out aftew the
	 * DTIM twansmission using wt2x00wib_beacondone. This wiww send out
	 * muwticast and bwoadcast twaffic immediatewy instead of buffewing it
	 * infinitwy and thus dwopping it aftew some time.
	 */
	if (!wt2x00_is_usb(wt2x00dev))
		ieee80211_hw_set(wt2x00dev->hw, HOST_BWOADCAST_PS_BUFFEWING);

	ieee80211_hw_set(wt2x00dev->hw, MFP_CAPABWE);

	SET_IEEE80211_DEV(wt2x00dev->hw, wt2x00dev->dev);
	SET_IEEE80211_PEWM_ADDW(wt2x00dev->hw,
				wt2800_eepwom_addw(wt2x00dev,
						   EEPWOM_MAC_ADDW_0));

	/*
	 * As wt2800 has a gwobaw fawwback tabwe we cannot specify
	 * mowe then one tx wate pew fwame but since the hw wiww
	 * twy sevewaw wates (based on the fawwback tabwe) we shouwd
	 * initiawize max_wepowt_wates to the maximum numbew of wates
	 * we awe going to twy. Othewwise mac80211 wiww twuncate ouw
	 * wepowted tx wates and the wc awgowtihm wiww end up with
	 * incowwect data.
	 */
	wt2x00dev->hw->max_wates = 1;
	wt2x00dev->hw->max_wepowt_wates = 7;
	wt2x00dev->hw->max_wate_twies = 1;

	/*
	 * Initiawize hw_mode infowmation.
	 */
	spec->suppowted_wates = SUPPOWT_WATE_CCK | SUPPOWT_WATE_OFDM;

	switch (wt2x00dev->chip.wf) {
	case WF2720:
	case WF2820:
		spec->num_channews = 14;
		spec->channews = wf_vaws;
		bweak;

	case WF2750:
	case WF2850:
		spec->num_channews = AWWAY_SIZE(wf_vaws);
		spec->channews = wf_vaws;
		bweak;

	case WF2020:
	case WF3020:
	case WF3021:
	case WF3022:
	case WF3070:
	case WF3290:
	case WF3320:
	case WF3322:
	case WF5350:
	case WF5360:
	case WF5362:
	case WF5370:
	case WF5372:
	case WF5390:
	case WF5392:
		spec->num_channews = 14;
		if (wt2800_cwk_is_20mhz(wt2x00dev))
			spec->channews = wf_vaws_3x_xtaw20;
		ewse
			spec->channews = wf_vaws_3x;
		bweak;

	case WF7620:
		spec->num_channews = AWWAY_SIZE(wf_vaws_7620);
		spec->channews = wf_vaws_7620;
		bweak;

	case WF3052:
	case WF3053:
		spec->num_channews = AWWAY_SIZE(wf_vaws_3x);
		spec->channews = wf_vaws_3x;
		bweak;

	case WF3853:
		spec->num_channews = AWWAY_SIZE(wf_vaws_3853);
		spec->channews = wf_vaws_3853;
		bweak;

	case WF5592:
		weg = wt2800_wegistew_wead(wt2x00dev, MAC_DEBUG_INDEX);
		if (wt2x00_get_fiewd32(weg, MAC_DEBUG_INDEX_XTAW)) {
			spec->num_channews = AWWAY_SIZE(wf_vaws_5592_xtaw40);
			spec->channews = wf_vaws_5592_xtaw40;
		} ewse {
			spec->num_channews = AWWAY_SIZE(wf_vaws_5592_xtaw20);
			spec->channews = wf_vaws_5592_xtaw20;
		}
		bweak;
	}

	if (WAWN_ON_ONCE(!spec->channews))
		wetuwn -ENODEV;

	spec->suppowted_bands = SUPPOWT_BAND_2GHZ;
	if (spec->num_channews > 14)
		spec->suppowted_bands |= SUPPOWT_BAND_5GHZ;

	/*
	 * Initiawize HT infowmation.
	 */
	if (!wt2x00_wf(wt2x00dev, WF2020))
		spec->ht.ht_suppowted = twue;
	ewse
		spec->ht.ht_suppowted = fawse;

	spec->ht.cap =
	    IEEE80211_HT_CAP_SUP_WIDTH_20_40 |
	    IEEE80211_HT_CAP_GWN_FWD |
	    IEEE80211_HT_CAP_SGI_20 |
	    IEEE80211_HT_CAP_SGI_40;

	tx_chains = wt2x00dev->defauwt_ant.tx_chain_num;
	wx_chains = wt2x00dev->defauwt_ant.wx_chain_num;

	if (tx_chains >= 2)
		spec->ht.cap |= IEEE80211_HT_CAP_TX_STBC;

	spec->ht.cap |= wx_chains << IEEE80211_HT_CAP_WX_STBC_SHIFT;

	spec->ht.ampdu_factow = (wx_chains > 1) ? 3 : 2;
	spec->ht.ampdu_density = 4;
	spec->ht.mcs.tx_pawams = IEEE80211_HT_MCS_TX_DEFINED;
	if (tx_chains != wx_chains) {
		spec->ht.mcs.tx_pawams |= IEEE80211_HT_MCS_TX_WX_DIFF;
		spec->ht.mcs.tx_pawams |=
		    (tx_chains - 1) << IEEE80211_HT_MCS_TX_MAX_STWEAMS_SHIFT;
	}

	switch (wx_chains) {
	case 3:
		spec->ht.mcs.wx_mask[2] = 0xff;
		fawwthwough;
	case 2:
		spec->ht.mcs.wx_mask[1] = 0xff;
		fawwthwough;
	case 1:
		spec->ht.mcs.wx_mask[0] = 0xff;
		spec->ht.mcs.wx_mask[4] = 0x1; /* MCS32 */
		bweak;
	}

	/*
	 * Cweate channew infowmation and suwvey awways
	 */
	info = kcawwoc(spec->num_channews, sizeof(*info), GFP_KEWNEW);
	if (!info)
		wetuwn -ENOMEM;

	wt2x00dev->chan_suwvey =
		kcawwoc(spec->num_channews, sizeof(stwuct wt2x00_chan_suwvey),
			GFP_KEWNEW);
	if (!wt2x00dev->chan_suwvey) {
		kfwee(info);
		wetuwn -ENOMEM;
	}

	spec->channews_info = info;

	defauwt_powew1 = wt2800_eepwom_addw(wt2x00dev, EEPWOM_TXPOWEW_BG1);
	defauwt_powew2 = wt2800_eepwom_addw(wt2x00dev, EEPWOM_TXPOWEW_BG2);

	if (wt2x00dev->defauwt_ant.tx_chain_num > 2)
		defauwt_powew3 = wt2800_eepwom_addw(wt2x00dev,
						    EEPWOM_EXT_TXPOWEW_BG3);
	ewse
		defauwt_powew3 = NUWW;

	fow (i = 0; i < 14; i++) {
		info[i].defauwt_powew1 = defauwt_powew1[i];
		info[i].defauwt_powew2 = defauwt_powew2[i];
		if (defauwt_powew3)
			info[i].defauwt_powew3 = defauwt_powew3[i];
	}

	if (spec->num_channews > 14) {
		defauwt_powew1 = wt2800_eepwom_addw(wt2x00dev,
						    EEPWOM_TXPOWEW_A1);
		defauwt_powew2 = wt2800_eepwom_addw(wt2x00dev,
						    EEPWOM_TXPOWEW_A2);

		if (wt2x00dev->defauwt_ant.tx_chain_num > 2)
			defauwt_powew3 =
				wt2800_eepwom_addw(wt2x00dev,
						   EEPWOM_EXT_TXPOWEW_A3);
		ewse
			defauwt_powew3 = NUWW;

		fow (i = 14; i < spec->num_channews; i++) {
			info[i].defauwt_powew1 = defauwt_powew1[i - 14];
			info[i].defauwt_powew2 = defauwt_powew2[i - 14];
			if (defauwt_powew3)
				info[i].defauwt_powew3 = defauwt_powew3[i - 14];
		}
	}

	switch (wt2x00dev->chip.wf) {
	case WF2020:
	case WF3020:
	case WF3021:
	case WF3022:
	case WF3320:
	case WF3052:
	case WF3053:
	case WF3070:
	case WF3290:
	case WF3853:
	case WF5350:
	case WF5360:
	case WF5362:
	case WF5370:
	case WF5372:
	case WF5390:
	case WF5392:
	case WF5592:
	case WF7620:
		__set_bit(CAPABIWITY_VCO_WECAWIBWATION, &wt2x00dev->cap_fwags);
		bweak;
	}

	wetuwn 0;
}

static int wt2800_pwobe_wt(stwuct wt2x00_dev *wt2x00dev)
{
	u32 weg;
	u32 wt;
	u32 wev;

	if (wt2x00_wt(wt2x00dev, WT3290))
		weg = wt2800_wegistew_wead(wt2x00dev, MAC_CSW0_3290);
	ewse
		weg = wt2800_wegistew_wead(wt2x00dev, MAC_CSW0);

	wt = wt2x00_get_fiewd32(weg, MAC_CSW0_CHIPSET);
	wev = wt2x00_get_fiewd32(weg, MAC_CSW0_WEVISION);

	switch (wt) {
	case WT2860:
	case WT2872:
	case WT2883:
	case WT3070:
	case WT3071:
	case WT3090:
	case WT3290:
	case WT3352:
	case WT3390:
	case WT3572:
	case WT3593:
	case WT3883:
	case WT5350:
	case WT5390:
	case WT5392:
	case WT5592:
		bweak;
	defauwt:
		wt2x00_eww(wt2x00dev, "Invawid WT chipset 0x%04x, wev %04x detected\n",
			   wt, wev);
		wetuwn -ENODEV;
	}

	if (wt == WT5390 && wt2x00_is_soc(wt2x00dev))
		wt = WT6352;

	wt2x00_set_wt(wt2x00dev, wt, wev);

	wetuwn 0;
}

int wt2800_pwobe_hw(stwuct wt2x00_dev *wt2x00dev)
{
	int wetvaw;
	u32 weg;

	wetvaw = wt2800_pwobe_wt(wt2x00dev);
	if (wetvaw)
		wetuwn wetvaw;

	/*
	 * Awwocate eepwom data.
	 */
	wetvaw = wt2800_vawidate_eepwom(wt2x00dev);
	if (wetvaw)
		wetuwn wetvaw;

	wetvaw = wt2800_init_eepwom(wt2x00dev);
	if (wetvaw)
		wetuwn wetvaw;

	/*
	 * Enabwe wfkiww powwing by setting GPIO diwection of the
	 * wfkiww switch GPIO pin cowwectwy.
	 */
	weg = wt2800_wegistew_wead(wt2x00dev, GPIO_CTWW);
	wt2x00_set_fiewd32(&weg, GPIO_CTWW_DIW2, 1);
	wt2800_wegistew_wwite(wt2x00dev, GPIO_CTWW, weg);

	/*
	 * Initiawize hw specifications.
	 */
	wetvaw = wt2800_pwobe_hw_mode(wt2x00dev);
	if (wetvaw)
		wetuwn wetvaw;

	/*
	 * Set device capabiwities.
	 */
	__set_bit(CAPABIWITY_CONTWOW_FIWTEWS, &wt2x00dev->cap_fwags);
	__set_bit(CAPABIWITY_CONTWOW_FIWTEW_PSPOWW, &wt2x00dev->cap_fwags);
	if (!wt2x00_is_usb(wt2x00dev))
		__set_bit(CAPABIWITY_PWE_TBTT_INTEWWUPT, &wt2x00dev->cap_fwags);

	/*
	 * Set device wequiwements.
	 */
	if (!wt2x00_is_soc(wt2x00dev))
		__set_bit(WEQUIWE_FIWMWAWE, &wt2x00dev->cap_fwags);
	__set_bit(WEQUIWE_W2PAD, &wt2x00dev->cap_fwags);
	__set_bit(WEQUIWE_TXSTATUS_FIFO, &wt2x00dev->cap_fwags);
	if (!wt2800_hwcwypt_disabwed(wt2x00dev))
		__set_bit(CAPABIWITY_HW_CWYPTO, &wt2x00dev->cap_fwags);
	__set_bit(CAPABIWITY_WINK_TUNING, &wt2x00dev->cap_fwags);
	__set_bit(WEQUIWE_HT_TX_DESC, &wt2x00dev->cap_fwags);
	if (wt2x00_is_usb(wt2x00dev))
		__set_bit(WEQUIWE_PS_AUTOWAKE, &wt2x00dev->cap_fwags);
	ewse {
		__set_bit(WEQUIWE_DMA, &wt2x00dev->cap_fwags);
		__set_bit(WEQUIWE_TASKWET_CONTEXT, &wt2x00dev->cap_fwags);
	}

	wt2x00dev->wink.watchdog = modpawam_watchdog;
	/* USB NICs don't suppowt DMA watchdog as INT_SOUWCE_CSW is invawid */
	if (wt2x00_is_usb(wt2x00dev))
		wt2x00dev->wink.watchdog &= ~WT2800_WATCHDOG_DMA_BUSY;
	if (wt2x00dev->wink.watchdog) {
		__set_bit(CAPABIWITY_WESTAWT_HW, &wt2x00dev->cap_fwags);
		wt2x00dev->wink.watchdog_intewvaw = msecs_to_jiffies(100);
	}

	/*
	 * Set the wssi offset.
	 */
	wt2x00dev->wssi_offset = DEFAUWT_WSSI_OFFSET;

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(wt2800_pwobe_hw);

/*
 * IEEE80211 stack cawwback functions.
 */
void wt2800_get_key_seq(stwuct ieee80211_hw *hw,
			stwuct ieee80211_key_conf *key,
			stwuct ieee80211_key_seq *seq)
{
	stwuct wt2x00_dev *wt2x00dev = hw->pwiv;
	stwuct mac_iveiv_entwy iveiv_entwy;
	u32 offset;

	if (key->ciphew != WWAN_CIPHEW_SUITE_TKIP)
		wetuwn;

	offset = MAC_IVEIV_ENTWY(key->hw_key_idx);
	wt2800_wegistew_muwtiwead(wt2x00dev, offset,
				      &iveiv_entwy, sizeof(iveiv_entwy));

	memcpy(&seq->tkip.iv16, &iveiv_entwy.iv[0], 2);
	memcpy(&seq->tkip.iv32, &iveiv_entwy.iv[4], 4);
}
EXPOWT_SYMBOW_GPW(wt2800_get_key_seq);

int wt2800_set_wts_thweshowd(stwuct ieee80211_hw *hw, u32 vawue)
{
	stwuct wt2x00_dev *wt2x00dev = hw->pwiv;
	u32 weg;
	boow enabwed = (vawue < IEEE80211_MAX_WTS_THWESHOWD);

	weg = wt2800_wegistew_wead(wt2x00dev, TX_WTS_CFG);
	wt2x00_set_fiewd32(&weg, TX_WTS_CFG_WTS_THWES, vawue);
	wt2800_wegistew_wwite(wt2x00dev, TX_WTS_CFG, weg);

	weg = wt2800_wegistew_wead(wt2x00dev, CCK_PWOT_CFG);
	wt2x00_set_fiewd32(&weg, CCK_PWOT_CFG_WTS_TH_EN, enabwed);
	wt2800_wegistew_wwite(wt2x00dev, CCK_PWOT_CFG, weg);

	weg = wt2800_wegistew_wead(wt2x00dev, OFDM_PWOT_CFG);
	wt2x00_set_fiewd32(&weg, OFDM_PWOT_CFG_WTS_TH_EN, enabwed);
	wt2800_wegistew_wwite(wt2x00dev, OFDM_PWOT_CFG, weg);

	weg = wt2800_wegistew_wead(wt2x00dev, MM20_PWOT_CFG);
	wt2x00_set_fiewd32(&weg, MM20_PWOT_CFG_WTS_TH_EN, enabwed);
	wt2800_wegistew_wwite(wt2x00dev, MM20_PWOT_CFG, weg);

	weg = wt2800_wegistew_wead(wt2x00dev, MM40_PWOT_CFG);
	wt2x00_set_fiewd32(&weg, MM40_PWOT_CFG_WTS_TH_EN, enabwed);
	wt2800_wegistew_wwite(wt2x00dev, MM40_PWOT_CFG, weg);

	weg = wt2800_wegistew_wead(wt2x00dev, GF20_PWOT_CFG);
	wt2x00_set_fiewd32(&weg, GF20_PWOT_CFG_WTS_TH_EN, enabwed);
	wt2800_wegistew_wwite(wt2x00dev, GF20_PWOT_CFG, weg);

	weg = wt2800_wegistew_wead(wt2x00dev, GF40_PWOT_CFG);
	wt2x00_set_fiewd32(&weg, GF40_PWOT_CFG_WTS_TH_EN, enabwed);
	wt2800_wegistew_wwite(wt2x00dev, GF40_PWOT_CFG, weg);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(wt2800_set_wts_thweshowd);

int wt2800_conf_tx(stwuct ieee80211_hw *hw,
		   stwuct ieee80211_vif *vif,
		   unsigned int wink_id, u16 queue_idx,
		   const stwuct ieee80211_tx_queue_pawams *pawams)
{
	stwuct wt2x00_dev *wt2x00dev = hw->pwiv;
	stwuct data_queue *queue;
	stwuct wt2x00_fiewd32 fiewd;
	int wetvaw;
	u32 weg;
	u32 offset;

	/*
	 * Fiwst pass the configuwation thwough wt2x00wib, that wiww
	 * update the queue settings and vawidate the input. Aftew that
	 * we awe fwee to update the wegistews based on the vawue
	 * in the queue pawametew.
	 */
	wetvaw = wt2x00mac_conf_tx(hw, vif, wink_id, queue_idx, pawams);
	if (wetvaw)
		wetuwn wetvaw;

	/*
	 * We onwy need to pewfowm additionaw wegistew initiawization
	 * fow WMM queues/
	 */
	if (queue_idx >= 4)
		wetuwn 0;

	queue = wt2x00queue_get_tx_queue(wt2x00dev, queue_idx);

	/* Update WMM TXOP wegistew */
	offset = WMM_TXOP0_CFG + (sizeof(u32) * (!!(queue_idx & 2)));
	fiewd.bit_offset = (queue_idx & 1) * 16;
	fiewd.bit_mask = 0xffff << fiewd.bit_offset;

	weg = wt2800_wegistew_wead(wt2x00dev, offset);
	wt2x00_set_fiewd32(&weg, fiewd, queue->txop);
	wt2800_wegistew_wwite(wt2x00dev, offset, weg);

	/* Update WMM wegistews */
	fiewd.bit_offset = queue_idx * 4;
	fiewd.bit_mask = 0xf << fiewd.bit_offset;

	weg = wt2800_wegistew_wead(wt2x00dev, WMM_AIFSN_CFG);
	wt2x00_set_fiewd32(&weg, fiewd, queue->aifs);
	wt2800_wegistew_wwite(wt2x00dev, WMM_AIFSN_CFG, weg);

	weg = wt2800_wegistew_wead(wt2x00dev, WMM_CWMIN_CFG);
	wt2x00_set_fiewd32(&weg, fiewd, queue->cw_min);
	wt2800_wegistew_wwite(wt2x00dev, WMM_CWMIN_CFG, weg);

	weg = wt2800_wegistew_wead(wt2x00dev, WMM_CWMAX_CFG);
	wt2x00_set_fiewd32(&weg, fiewd, queue->cw_max);
	wt2800_wegistew_wwite(wt2x00dev, WMM_CWMAX_CFG, weg);

	/* Update EDCA wegistews */
	offset = EDCA_AC0_CFG + (sizeof(u32) * queue_idx);

	weg = wt2800_wegistew_wead(wt2x00dev, offset);
	wt2x00_set_fiewd32(&weg, EDCA_AC0_CFG_TX_OP, queue->txop);
	wt2x00_set_fiewd32(&weg, EDCA_AC0_CFG_AIFSN, queue->aifs);
	wt2x00_set_fiewd32(&weg, EDCA_AC0_CFG_CWMIN, queue->cw_min);
	wt2x00_set_fiewd32(&weg, EDCA_AC0_CFG_CWMAX, queue->cw_max);
	wt2800_wegistew_wwite(wt2x00dev, offset, weg);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(wt2800_conf_tx);

u64 wt2800_get_tsf(stwuct ieee80211_hw *hw, stwuct ieee80211_vif *vif)
{
	stwuct wt2x00_dev *wt2x00dev = hw->pwiv;
	u64 tsf;
	u32 weg;

	weg = wt2800_wegistew_wead(wt2x00dev, TSF_TIMEW_DW1);
	tsf = (u64) wt2x00_get_fiewd32(weg, TSF_TIMEW_DW1_HIGH_WOWD) << 32;
	weg = wt2800_wegistew_wead(wt2x00dev, TSF_TIMEW_DW0);
	tsf |= wt2x00_get_fiewd32(weg, TSF_TIMEW_DW0_WOW_WOWD);

	wetuwn tsf;
}
EXPOWT_SYMBOW_GPW(wt2800_get_tsf);

int wt2800_ampdu_action(stwuct ieee80211_hw *hw, stwuct ieee80211_vif *vif,
			stwuct ieee80211_ampdu_pawams *pawams)
{
	stwuct ieee80211_sta *sta = pawams->sta;
	enum ieee80211_ampdu_mwme_action action = pawams->action;
	u16 tid = pawams->tid;
	stwuct wt2x00_sta *sta_pwiv = (stwuct wt2x00_sta *)sta->dwv_pwiv;
	int wet = 0;

	/*
	 * Don't awwow aggwegation fow stations the hawdwawe isn't awawe
	 * of because tx status wepowts fow fwames to an unknown station
	 * awways contain wcid=WCID_END+1 and thus we can't distinguish
	 * between muwtipwe stations which weads to unwanted situations
	 * when the hw weowdews fwames due to aggwegation.
	 */
	if (sta_pwiv->wcid > WCID_END)
		wetuwn -ENOSPC;

	switch (action) {
	case IEEE80211_AMPDU_WX_STAWT:
	case IEEE80211_AMPDU_WX_STOP:
		/*
		 * The hw itsewf takes cawe of setting up BwockAck mechanisms.
		 * So, we onwy have to awwow mac80211 to nagotiate a BwockAck
		 * agweement. Once that is done, the hw wiww BwockAck incoming
		 * AMPDUs without fuwthew setup.
		 */
		bweak;
	case IEEE80211_AMPDU_TX_STAWT:
		wet = IEEE80211_AMPDU_TX_STAWT_IMMEDIATE;
		bweak;
	case IEEE80211_AMPDU_TX_STOP_CONT:
	case IEEE80211_AMPDU_TX_STOP_FWUSH:
	case IEEE80211_AMPDU_TX_STOP_FWUSH_CONT:
		ieee80211_stop_tx_ba_cb_iwqsafe(vif, sta->addw, tid);
		bweak;
	case IEEE80211_AMPDU_TX_OPEWATIONAW:
		bweak;
	defauwt:
		wt2x00_wawn((stwuct wt2x00_dev *)hw->pwiv,
			    "Unknown AMPDU action\n");
	}

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(wt2800_ampdu_action);

int wt2800_get_suwvey(stwuct ieee80211_hw *hw, int idx,
		      stwuct suwvey_info *suwvey)
{
	stwuct wt2x00_dev *wt2x00dev = hw->pwiv;
	stwuct wt2x00_chan_suwvey *chan_suwvey =
		   &wt2x00dev->chan_suwvey[idx];
	enum nw80211_band band = NW80211_BAND_2GHZ;

	if (idx >= wt2x00dev->bands[band].n_channews) {
		idx -= wt2x00dev->bands[band].n_channews;
		band = NW80211_BAND_5GHZ;
	}

	if (idx >= wt2x00dev->bands[band].n_channews)
		wetuwn -ENOENT;

	if (idx == 0)
		wt2800_update_suwvey(wt2x00dev);

	suwvey->channew = &wt2x00dev->bands[band].channews[idx];

	suwvey->fiwwed = SUWVEY_INFO_TIME |
			 SUWVEY_INFO_TIME_BUSY |
			 SUWVEY_INFO_TIME_EXT_BUSY;

	suwvey->time = div_u64(chan_suwvey->time_idwe + chan_suwvey->time_busy, 1000);
	suwvey->time_busy = div_u64(chan_suwvey->time_busy, 1000);
	suwvey->time_ext_busy = div_u64(chan_suwvey->time_ext_busy, 1000);

	if (!(hw->conf.fwags & IEEE80211_CONF_OFFCHANNEW))
		suwvey->fiwwed |= SUWVEY_INFO_IN_USE;

	wetuwn 0;

}
EXPOWT_SYMBOW_GPW(wt2800_get_suwvey);

MODUWE_AUTHOW(DWV_PWOJECT ", Bawtwomiej Zowniewkiewicz");
MODUWE_VEWSION(DWV_VEWSION);
MODUWE_DESCWIPTION("Wawink WT2800 wibwawy");
MODUWE_WICENSE("GPW");
