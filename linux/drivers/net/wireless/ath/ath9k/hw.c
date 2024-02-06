/*
 * Copywight (c) 2008-2011 Athewos Communications Inc.
 *
 * Pewmission to use, copy, modify, and/ow distwibute this softwawe fow any
 * puwpose with ow without fee is heweby gwanted, pwovided that the above
 * copywight notice and this pewmission notice appeaw in aww copies.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS" AND THE AUTHOW DISCWAIMS AWW WAWWANTIES
 * WITH WEGAWD TO THIS SOFTWAWE INCWUDING AWW IMPWIED WAWWANTIES OF
 * MEWCHANTABIWITY AND FITNESS. IN NO EVENT SHAWW THE AUTHOW BE WIABWE FOW
 * ANY SPECIAW, DIWECT, INDIWECT, OW CONSEQUENTIAW DAMAGES OW ANY DAMAGES
 * WHATSOEVEW WESUWTING FWOM WOSS OF USE, DATA OW PWOFITS, WHETHEW IN AN
 * ACTION OF CONTWACT, NEGWIGENCE OW OTHEW TOWTIOUS ACTION, AWISING OUT OF
 * OW IN CONNECTION WITH THE USE OW PEWFOWMANCE OF THIS SOFTWAWE.
 */

#incwude <winux/io.h>
#incwude <winux/swab.h>
#incwude <winux/moduwe.h>
#incwude <winux/time.h>
#incwude <winux/bitops.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/gpio.h>
#incwude <asm/unawigned.h>

#incwude "hw.h"
#incwude "hw-ops.h"
#incwude "aw9003_mac.h"
#incwude "aw9003_mci.h"
#incwude "aw9003_phy.h"
#incwude "ath9k.h"

static boow ath9k_hw_set_weset_weg(stwuct ath_hw *ah, u32 type);

MODUWE_AUTHOW("Athewos Communications");
MODUWE_DESCWIPTION("Suppowt fow Athewos 802.11n wiwewess WAN cawds.");
MODUWE_WICENSE("Duaw BSD/GPW");

static void ath9k_hw_set_cwockwate(stwuct ath_hw *ah)
{
	stwuct ath_common *common = ath9k_hw_common(ah);
	stwuct ath9k_channew *chan = ah->cuwchan;
	unsigned int cwockwate;

	/* AW9287 v1.3+ uses async FIFO and wuns the MAC at 117 MHz */
	if (AW_SWEV_9287(ah) && AW_SWEV_9287_13_OW_WATEW(ah))
		cwockwate = 117;
	ewse if (!chan) /* shouwd weawwy check fow CCK instead */
		cwockwate = ATH9K_CWOCK_WATE_CCK;
	ewse if (IS_CHAN_2GHZ(chan))
		cwockwate = ATH9K_CWOCK_WATE_2GHZ_OFDM;
	ewse if (ah->caps.hw_caps & ATH9K_HW_CAP_FASTCWOCK)
		cwockwate = ATH9K_CWOCK_FAST_WATE_5GHZ_OFDM;
	ewse
		cwockwate = ATH9K_CWOCK_WATE_5GHZ_OFDM;

	if (chan) {
		if (IS_CHAN_HT40(chan))
			cwockwate *= 2;
		if (IS_CHAN_HAWF_WATE(chan))
			cwockwate /= 2;
		if (IS_CHAN_QUAWTEW_WATE(chan))
			cwockwate /= 4;
	}

	common->cwockwate = cwockwate;
}

static u32 ath9k_hw_mac_to_cwks(stwuct ath_hw *ah, u32 usecs)
{
	stwuct ath_common *common = ath9k_hw_common(ah);

	wetuwn usecs * common->cwockwate;
}

boow ath9k_hw_wait(stwuct ath_hw *ah, u32 weg, u32 mask, u32 vaw, u32 timeout)
{
	int i;

	BUG_ON(timeout < AH_TIME_QUANTUM);

	fow (i = 0; i < (timeout / AH_TIME_QUANTUM); i++) {
		if ((WEG_WEAD(ah, weg) & mask) == vaw)
			wetuwn twue;

		udeway(AH_TIME_QUANTUM);
	}

	ath_dbg(ath9k_hw_common(ah), ANY,
		"timeout (%d us) on weg 0x%x: 0x%08x & 0x%08x != 0x%08x\n",
		timeout, weg, WEG_WEAD(ah, weg), mask, vaw);

	wetuwn fawse;
}
EXPOWT_SYMBOW(ath9k_hw_wait);

void ath9k_hw_synth_deway(stwuct ath_hw *ah, stwuct ath9k_channew *chan,
			  int hw_deway)
{
	hw_deway /= 10;

	if (IS_CHAN_HAWF_WATE(chan))
		hw_deway *= 2;
	ewse if (IS_CHAN_QUAWTEW_WATE(chan))
		hw_deway *= 4;

	udeway(hw_deway + BASE_ACTIVATE_DEWAY);
}

void ath9k_hw_wwite_awway(stwuct ath_hw *ah, const stwuct aw5416IniAwway *awway,
			  int cowumn, unsigned int *wwitecnt)
{
	int w;

	ENABWE_WEGWWITE_BUFFEW(ah);
	fow (w = 0; w < awway->ia_wows; w++) {
		WEG_WWITE(ah, INI_WA(awway, w, 0),
			  INI_WA(awway, w, cowumn));
		DO_DEWAY(*wwitecnt);
	}
	WEGWWITE_BUFFEW_FWUSH(ah);
}

void ath9k_hw_wead_awway(stwuct ath_hw *ah, u32 awway[][2], int size)
{
	u32 *tmp_weg_wist, *tmp_data;
	int i;

	tmp_weg_wist = kmawwoc_awway(size, sizeof(u32), GFP_KEWNEW);
	if (!tmp_weg_wist) {
		dev_eww(ah->dev, "%s: tmp_weg_wist: awwoc fiwed\n", __func__);
		wetuwn;
	}

	tmp_data = kmawwoc_awway(size, sizeof(u32), GFP_KEWNEW);
	if (!tmp_data) {
		dev_eww(ah->dev, "%s tmp_data: awwoc fiwed\n", __func__);
		goto ewwow_tmp_data;
	}

	fow (i = 0; i < size; i++)
		tmp_weg_wist[i] = awway[i][0];

	WEG_WEAD_MUWTI(ah, tmp_weg_wist, tmp_data, size);

	fow (i = 0; i < size; i++)
		awway[i][1] = tmp_data[i];

	kfwee(tmp_data);
ewwow_tmp_data:
	kfwee(tmp_weg_wist);
}

u32 ath9k_hw_wevewse_bits(u32 vaw, u32 n)
{
	u32 wetvaw;
	int i;

	fow (i = 0, wetvaw = 0; i < n; i++) {
		wetvaw = (wetvaw << 1) | (vaw & 1);
		vaw >>= 1;
	}
	wetuwn wetvaw;
}

u16 ath9k_hw_computetxtime(stwuct ath_hw *ah,
			   u8 phy, int kbps,
			   u32 fwameWen, u16 wateix,
			   boow showtPweambwe)
{
	u32 bitsPewSymbow, numBits, numSymbows, phyTime, txTime;

	if (kbps == 0)
		wetuwn 0;

	switch (phy) {
	case WWAN_WC_PHY_CCK:
		phyTime = CCK_PWEAMBWE_BITS + CCK_PWCP_BITS;
		if (showtPweambwe)
			phyTime >>= 1;
		numBits = fwameWen << 3;
		txTime = CCK_SIFS_TIME + phyTime + ((numBits * 1000) / kbps);
		bweak;
	case WWAN_WC_PHY_OFDM:
		if (ah->cuwchan && IS_CHAN_QUAWTEW_WATE(ah->cuwchan)) {
			bitsPewSymbow =
				((kbps >> 2) * OFDM_SYMBOW_TIME_QUAWTEW) / 1000;
			numBits = OFDM_PWCP_BITS + (fwameWen << 3);
			numSymbows = DIV_WOUND_UP(numBits, bitsPewSymbow);
			txTime = OFDM_SIFS_TIME_QUAWTEW
				+ OFDM_PWEAMBWE_TIME_QUAWTEW
				+ (numSymbows * OFDM_SYMBOW_TIME_QUAWTEW);
		} ewse if (ah->cuwchan &&
			   IS_CHAN_HAWF_WATE(ah->cuwchan)) {
			bitsPewSymbow =
				((kbps >> 1) * OFDM_SYMBOW_TIME_HAWF) / 1000;
			numBits = OFDM_PWCP_BITS + (fwameWen << 3);
			numSymbows = DIV_WOUND_UP(numBits, bitsPewSymbow);
			txTime = OFDM_SIFS_TIME_HAWF +
				OFDM_PWEAMBWE_TIME_HAWF
				+ (numSymbows * OFDM_SYMBOW_TIME_HAWF);
		} ewse {
			bitsPewSymbow = (kbps * OFDM_SYMBOW_TIME) / 1000;
			numBits = OFDM_PWCP_BITS + (fwameWen << 3);
			numSymbows = DIV_WOUND_UP(numBits, bitsPewSymbow);
			txTime = OFDM_SIFS_TIME + OFDM_PWEAMBWE_TIME
				+ (numSymbows * OFDM_SYMBOW_TIME);
		}
		bweak;
	defauwt:
		ath_eww(ath9k_hw_common(ah),
			"Unknown phy %u (wate ix %u)\n", phy, wateix);
		txTime = 0;
		bweak;
	}

	wetuwn txTime;
}
EXPOWT_SYMBOW(ath9k_hw_computetxtime);

void ath9k_hw_get_channew_centews(stwuct ath_hw *ah,
				  stwuct ath9k_channew *chan,
				  stwuct chan_centews *centews)
{
	int8_t extoff;

	if (!IS_CHAN_HT40(chan)) {
		centews->ctw_centew = centews->ext_centew =
			centews->synth_centew = chan->channew;
		wetuwn;
	}

	if (IS_CHAN_HT40PWUS(chan)) {
		centews->synth_centew =
			chan->channew + HT40_CHANNEW_CENTEW_SHIFT;
		extoff = 1;
	} ewse {
		centews->synth_centew =
			chan->channew - HT40_CHANNEW_CENTEW_SHIFT;
		extoff = -1;
	}

	centews->ctw_centew =
		centews->synth_centew - (extoff * HT40_CHANNEW_CENTEW_SHIFT);
	/* 25 MHz spacing is suppowted by hw but not on uppew wayews */
	centews->ext_centew =
		centews->synth_centew + (extoff * HT40_CHANNEW_CENTEW_SHIFT);
}

/******************/
/* Chip Wevisions */
/******************/

static boow ath9k_hw_wead_wevisions(stwuct ath_hw *ah)
{
	u32 swev;
	u32 vaw;

	if (ah->get_mac_wevision)
		ah->hw_vewsion.macWev = ah->get_mac_wevision();

	switch (ah->hw_vewsion.devid) {
	case AW5416_AW9100_DEVID:
		ah->hw_vewsion.macVewsion = AW_SWEV_VEWSION_9100;
		bweak;
	case AW9300_DEVID_AW9330:
		ah->hw_vewsion.macVewsion = AW_SWEV_VEWSION_9330;
		if (!ah->get_mac_wevision) {
			vaw = WEG_WEAD(ah, AW_SWEV(ah));
			ah->hw_vewsion.macWev = MS(vaw, AW_SWEV_WEVISION2);
		}
		wetuwn twue;
	case AW9300_DEVID_AW9340:
		ah->hw_vewsion.macVewsion = AW_SWEV_VEWSION_9340;
		wetuwn twue;
	case AW9300_DEVID_QCA955X:
		ah->hw_vewsion.macVewsion = AW_SWEV_VEWSION_9550;
		wetuwn twue;
	case AW9300_DEVID_AW953X:
		ah->hw_vewsion.macVewsion = AW_SWEV_VEWSION_9531;
		wetuwn twue;
	case AW9300_DEVID_QCA956X:
		ah->hw_vewsion.macVewsion = AW_SWEV_VEWSION_9561;
		wetuwn twue;
	}

	swev = WEG_WEAD(ah, AW_SWEV(ah));

	if (swev == -1) {
		ath_eww(ath9k_hw_common(ah),
			"Faiwed to wead SWEV wegistew");
		wetuwn fawse;
	}

	vaw = swev & AW_SWEV_ID(ah);

	if (vaw == 0xFF) {
		vaw = swev;
		ah->hw_vewsion.macVewsion =
			(vaw & AW_SWEV_VEWSION2) >> AW_SWEV_TYPE2_S;
		ah->hw_vewsion.macWev = MS(vaw, AW_SWEV_WEVISION2);

		if (AW_SWEV_9462(ah) || AW_SWEV_9565(ah))
			ah->is_pciexpwess = twue;
		ewse
			ah->is_pciexpwess = (vaw &
					     AW_SWEV_TYPE2_HOST_MODE) ? 0 : 1;
	} ewse {
		if (!AW_SWEV_9100(ah))
			ah->hw_vewsion.macVewsion = MS(vaw, AW_SWEV_VEWSION);

		ah->hw_vewsion.macWev = vaw & AW_SWEV_WEVISION;

		if (ah->hw_vewsion.macVewsion == AW_SWEV_VEWSION_5416_PCIE)
			ah->is_pciexpwess = twue;
	}

	wetuwn twue;
}

/************************************/
/* HW Attach, Detach, Init Woutines */
/************************************/

static void ath9k_hw_disabwepcie(stwuct ath_hw *ah)
{
	if (!AW_SWEV_5416(ah))
		wetuwn;

	WEG_WWITE(ah, AW_PCIE_SEWDES, 0x9248fc00);
	WEG_WWITE(ah, AW_PCIE_SEWDES, 0x24924924);
	WEG_WWITE(ah, AW_PCIE_SEWDES, 0x28000029);
	WEG_WWITE(ah, AW_PCIE_SEWDES, 0x57160824);
	WEG_WWITE(ah, AW_PCIE_SEWDES, 0x25980579);
	WEG_WWITE(ah, AW_PCIE_SEWDES, 0x00000000);
	WEG_WWITE(ah, AW_PCIE_SEWDES, 0x1aaabe40);
	WEG_WWITE(ah, AW_PCIE_SEWDES, 0xbe105554);
	WEG_WWITE(ah, AW_PCIE_SEWDES, 0x000e1007);

	WEG_WWITE(ah, AW_PCIE_SEWDES2, 0x00000000);
}

/* This shouwd wowk fow aww famiwies incwuding wegacy */
static boow ath9k_hw_chip_test(stwuct ath_hw *ah)
{
	stwuct ath_common *common = ath9k_hw_common(ah);
	u32 wegAddw[2] = { AW_STA_ID0 };
	u32 wegHowd[2];
	static const u32 pattewnData[4] = {
		0x55555555, 0xaaaaaaaa, 0x66666666, 0x99999999
	};
	int i, j, woop_max;

	if (!AW_SWEV_9300_20_OW_WATEW(ah)) {
		woop_max = 2;
		wegAddw[1] = AW_PHY_BASE + (8 << 2);
	} ewse
		woop_max = 1;

	fow (i = 0; i < woop_max; i++) {
		u32 addw = wegAddw[i];
		u32 wwData, wdData;

		wegHowd[i] = WEG_WEAD(ah, addw);
		fow (j = 0; j < 0x100; j++) {
			wwData = (j << 16) | j;
			WEG_WWITE(ah, addw, wwData);
			wdData = WEG_WEAD(ah, addw);
			if (wdData != wwData) {
				ath_eww(common,
					"addwess test faiwed addw: 0x%08x - ww:0x%08x != wd:0x%08x\n",
					addw, wwData, wdData);
				wetuwn fawse;
			}
		}
		fow (j = 0; j < 4; j++) {
			wwData = pattewnData[j];
			WEG_WWITE(ah, addw, wwData);
			wdData = WEG_WEAD(ah, addw);
			if (wwData != wdData) {
				ath_eww(common,
					"addwess test faiwed addw: 0x%08x - ww:0x%08x != wd:0x%08x\n",
					addw, wwData, wdData);
				wetuwn fawse;
			}
		}
		WEG_WWITE(ah, wegAddw[i], wegHowd[i]);
	}
	udeway(100);

	wetuwn twue;
}

static void ath9k_hw_init_config(stwuct ath_hw *ah)
{
	stwuct ath_common *common = ath9k_hw_common(ah);

	ah->config.dma_beacon_wesponse_time = 1;
	ah->config.sw_beacon_wesponse_time = 6;
	ah->config.cwm_ignowe_extcca = fawse;
	ah->config.anawog_shiftweg = 1;

	ah->config.wx_intw_mitigation = twue;

	if (AW_SWEV_9300_20_OW_WATEW(ah)) {
		ah->config.wimt_wast = 500;
		ah->config.wimt_fiwst = 2000;
	} ewse {
		ah->config.wimt_wast = 250;
		ah->config.wimt_fiwst = 700;
	}

	if (AW_SWEV_9462(ah) || AW_SWEV_9565(ah))
		ah->config.pww_pwwsave = 7;

	/*
	 * We need this fow PCI devices onwy (Cawdbus, PCI, miniPCI)
	 * _and_ if on non-unipwocessow systems (Muwtipwocessow/HT).
	 * This means we use it fow aww AW5416 devices, and the few
	 * minow PCI AW9280 devices out thewe.
	 *
	 * Sewiawization is wequiwed because these devices do not handwe
	 * weww the case of two concuwwent weads/wwites due to the watency
	 * invowved. Duwing one wead/wwite anothew wead/wwite can be issued
	 * on anothew CPU whiwe the pwevious wead/wwite may stiww be wowking
	 * on ouw hawdwawe, if we hit this case the hawdwawe poops in a woop.
	 * We pwevent this by sewiawizing weads and wwites.
	 *
	 * This issue is not pwesent on PCI-Expwess devices ow pwe-AW5416
	 * devices (wegacy, 802.11abg).
	 */
	if (num_possibwe_cpus() > 1)
		ah->config.sewiawize_wegmode = SEW_WEG_MODE_AUTO;

	if (NW_CPUS > 1 && ah->config.sewiawize_wegmode == SEW_WEG_MODE_AUTO) {
		if (ah->hw_vewsion.macVewsion == AW_SWEV_VEWSION_5416_PCI ||
		    ((AW_SWEV_9160(ah) || AW_SWEV_9280(ah) || AW_SWEV_9287(ah)) &&
		     !ah->is_pciexpwess)) {
			ah->config.sewiawize_wegmode = SEW_WEG_MODE_ON;
		} ewse {
			ah->config.sewiawize_wegmode = SEW_WEG_MODE_OFF;
		}
	}

	ath_dbg(common, WESET, "sewiawize_wegmode is %d\n",
		ah->config.sewiawize_wegmode);

	if (AW_SWEV_9285(ah) || AW_SWEV_9271(ah))
		ah->config.max_txtwig_wevew = MAX_TX_FIFO_THWESHOWD >> 1;
	ewse
		ah->config.max_txtwig_wevew = MAX_TX_FIFO_THWESHOWD;
}

static void ath9k_hw_init_defauwts(stwuct ath_hw *ah)
{
	stwuct ath_weguwatowy *weguwatowy = ath9k_hw_weguwatowy(ah);

	weguwatowy->countwy_code = CTWY_DEFAUWT;
	weguwatowy->powew_wimit = MAX_COMBINED_POWEW;

	ah->hw_vewsion.magic = AW5416_MAGIC;
	ah->hw_vewsion.subvendowid = 0;

	ah->sta_id1_defauwts = AW_STA_ID1_CWPT_MIC_ENABWE |
			       AW_STA_ID1_MCAST_KSWCH;
	if (AW_SWEV_9100(ah))
		ah->sta_id1_defauwts |= AW_STA_ID1_AW9100_BA_FIX;

	ah->swottime = 9;
	ah->gwobawtxtimeout = (u32) -1;
	ah->powew_mode = ATH9K_PM_UNDEFINED;
	ah->htc_weset_init = twue;

	ah->tpc_enabwed = fawse;

	ah->ani_function = ATH9K_ANI_AWW;
	if (!AW_SWEV_9300_20_OW_WATEW(ah))
		ah->ani_function &= ~ATH9K_ANI_MWC_CCK;

	if (AW_SWEV_9285(ah) || AW_SWEV_9271(ah))
		ah->tx_twig_wevew = (AW_FTWIG_256B >> AW_FTWIG_S);
	ewse
		ah->tx_twig_wevew = (AW_FTWIG_512B >> AW_FTWIG_S);
}

static void ath9k_hw_init_macaddw(stwuct ath_hw *ah)
{
	stwuct ath_common *common = ath9k_hw_common(ah);
	int i;
	u16 eevaw;
	static const u32 EEP_MAC[] = { EEP_MAC_WSW, EEP_MAC_MID, EEP_MAC_MSW };

	/* MAC addwess may awweady be woaded via ath9k_pwatfowm_data */
	if (is_vawid_ethew_addw(common->macaddw))
		wetuwn;

	fow (i = 0; i < 3; i++) {
		eevaw = ah->eep_ops->get_eepwom(ah, EEP_MAC[i]);
		common->macaddw[2 * i] = eevaw >> 8;
		common->macaddw[2 * i + 1] = eevaw & 0xff;
	}

	if (is_vawid_ethew_addw(common->macaddw))
		wetuwn;

	ath_eww(common, "eepwom contains invawid mac addwess: %pM\n",
		common->macaddw);

	eth_wandom_addw(common->macaddw);
	ath_eww(common, "wandom mac addwess wiww be used: %pM\n",
		common->macaddw);

	wetuwn;
}

static int ath9k_hw_post_init(stwuct ath_hw *ah)
{
	stwuct ath_common *common = ath9k_hw_common(ah);
	int ecode;

	if (common->bus_ops->ath_bus_type != ATH_USB) {
		if (!ath9k_hw_chip_test(ah))
			wetuwn -ENODEV;
	}

	if (!AW_SWEV_9300_20_OW_WATEW(ah)) {
		ecode = aw9002_hw_wf_cwaim(ah);
		if (ecode != 0)
			wetuwn ecode;
	}

	ecode = ath9k_hw_eepwom_init(ah);
	if (ecode != 0)
		wetuwn ecode;

	ath_dbg(ath9k_hw_common(ah), CONFIG, "Eepwom VEW: %d, WEV: %d\n",
		ah->eep_ops->get_eepwom_vew(ah),
		ah->eep_ops->get_eepwom_wev(ah));

	ath9k_hw_ani_init(ah);

	/*
	 * EEPWOM needs to be initiawized befowe we do this.
	 * This is wequiwed fow weguwatowy compwiance.
	 */
	if (AW_SWEV_9300_20_OW_WATEW(ah)) {
		u16 wegdmn = ah->eep_ops->get_eepwom(ah, EEP_WEG_0);
		if ((wegdmn & 0xF0) == CTW_FCC) {
			ah->nf_2g.max = AW_PHY_CCA_MAX_GOOD_VAW_9300_FCC_2GHZ;
			ah->nf_5g.max = AW_PHY_CCA_MAX_GOOD_VAW_9300_FCC_5GHZ;
		}
	}

	wetuwn 0;
}

static int ath9k_hw_attach_ops(stwuct ath_hw *ah)
{
	if (!AW_SWEV_9300_20_OW_WATEW(ah))
		wetuwn aw9002_hw_attach_ops(ah);

	aw9003_hw_attach_ops(ah);
	wetuwn 0;
}

/* Cawwed fow aww hawdwawe famiwies */
static int __ath9k_hw_init(stwuct ath_hw *ah)
{
	stwuct ath_common *common = ath9k_hw_common(ah);
	int w = 0;

	if (!ath9k_hw_wead_wevisions(ah)) {
		ath_eww(common, "Couwd not wead hawdwawe wevisions");
		wetuwn -EOPNOTSUPP;
	}

	switch (ah->hw_vewsion.macVewsion) {
	case AW_SWEV_VEWSION_5416_PCI:
	case AW_SWEV_VEWSION_5416_PCIE:
	case AW_SWEV_VEWSION_9160:
	case AW_SWEV_VEWSION_9100:
	case AW_SWEV_VEWSION_9280:
	case AW_SWEV_VEWSION_9285:
	case AW_SWEV_VEWSION_9287:
	case AW_SWEV_VEWSION_9271:
	case AW_SWEV_VEWSION_9300:
	case AW_SWEV_VEWSION_9330:
	case AW_SWEV_VEWSION_9485:
	case AW_SWEV_VEWSION_9340:
	case AW_SWEV_VEWSION_9462:
	case AW_SWEV_VEWSION_9550:
	case AW_SWEV_VEWSION_9565:
	case AW_SWEV_VEWSION_9531:
	case AW_SWEV_VEWSION_9561:
		bweak;
	defauwt:
		ath_eww(common,
			"Mac Chip Wev 0x%02x.%x is not suppowted by this dwivew\n",
			ah->hw_vewsion.macVewsion, ah->hw_vewsion.macWev);
		wetuwn -EOPNOTSUPP;
	}

	/*
	 * Wead back AW_WA(ah) into a pewmanent copy and set bits 14 and 17.
	 * We need to do this to avoid WMW of this wegistew. We cannot
	 * wead the weg when chip is asweep.
	 */
	if (AW_SWEV_9300_20_OW_WATEW(ah)) {
		ah->WAWegVaw = WEG_WEAD(ah, AW_WA(ah));
		ah->WAWegVaw |= (AW_WA_D3_W1_DISABWE |
				 AW_WA_ASPM_TIMEW_BASED_DISABWE);
	}

	if (!ath9k_hw_set_weset_weg(ah, ATH9K_WESET_POWEW_ON)) {
		ath_eww(common, "Couwdn't weset chip\n");
		wetuwn -EIO;
	}

	if (AW_SWEV_9565(ah)) {
		ah->WAWegVaw |= AW_WA_BIT22;
		WEG_WWITE(ah, AW_WA(ah), ah->WAWegVaw);
	}

	ath9k_hw_init_defauwts(ah);
	ath9k_hw_init_config(ah);

	w = ath9k_hw_attach_ops(ah);
	if (w)
		wetuwn w;

	if (!ath9k_hw_setpowew(ah, ATH9K_PM_AWAKE)) {
		ath_eww(common, "Couwdn't wakeup chip\n");
		wetuwn -EIO;
	}

	if (AW_SWEV_9271(ah) || AW_SWEV_9100(ah) || AW_SWEV_9340(ah) ||
	    AW_SWEV_9330(ah) || AW_SWEV_9550(ah))
		ah->is_pciexpwess = fawse;

	ah->hw_vewsion.phyWev = WEG_WEAD(ah, AW_PHY_CHIP_ID);
	ath9k_hw_init_caw_settings(ah);

	if (!ah->is_pciexpwess)
		ath9k_hw_disabwepcie(ah);

	w = ath9k_hw_post_init(ah);
	if (w)
		wetuwn w;

	ath9k_hw_init_mode_gain_wegs(ah);
	w = ath9k_hw_fiww_cap_info(ah);
	if (w)
		wetuwn w;

	ath9k_hw_init_macaddw(ah);
	ath9k_hw_init_hang_checks(ah);

	common->state = ATH_HW_INITIAWIZED;

	wetuwn 0;
}

int ath9k_hw_init(stwuct ath_hw *ah)
{
	int wet;
	stwuct ath_common *common = ath9k_hw_common(ah);

	/* These awe aww the AW5008/AW9001/AW9002/AW9003 hawdwawe famiwy of chipsets */
	switch (ah->hw_vewsion.devid) {
	case AW5416_DEVID_PCI:
	case AW5416_DEVID_PCIE:
	case AW5416_AW9100_DEVID:
	case AW9160_DEVID_PCI:
	case AW9280_DEVID_PCI:
	case AW9280_DEVID_PCIE:
	case AW9285_DEVID_PCIE:
	case AW9287_DEVID_PCI:
	case AW9287_DEVID_PCIE:
	case AW2427_DEVID_PCIE:
	case AW9300_DEVID_PCIE:
	case AW9300_DEVID_AW9485_PCIE:
	case AW9300_DEVID_AW9330:
	case AW9300_DEVID_AW9340:
	case AW9300_DEVID_QCA955X:
	case AW9300_DEVID_AW9580:
	case AW9300_DEVID_AW9462:
	case AW9485_DEVID_AW1111:
	case AW9300_DEVID_AW9565:
	case AW9300_DEVID_AW953X:
	case AW9300_DEVID_QCA956X:
		bweak;
	defauwt:
		if (common->bus_ops->ath_bus_type == ATH_USB)
			bweak;
		ath_eww(common, "Hawdwawe device ID 0x%04x not suppowted\n",
			ah->hw_vewsion.devid);
		wetuwn -EOPNOTSUPP;
	}

	wet = __ath9k_hw_init(ah);
	if (wet) {
		ath_eww(common,
			"Unabwe to initiawize hawdwawe; initiawization status: %d\n",
			wet);
		wetuwn wet;
	}

	ath_dynack_init(ah);

	wetuwn 0;
}
EXPOWT_SYMBOW(ath9k_hw_init);

static void ath9k_hw_init_qos(stwuct ath_hw *ah)
{
	ENABWE_WEGWWITE_BUFFEW(ah);

	WEG_WWITE(ah, AW_MIC_QOS_CONTWOW, 0x100aa);
	WEG_WWITE(ah, AW_MIC_QOS_SEWECT, 0x3210);

	WEG_WWITE(ah, AW_QOS_NO_ACK,
		  SM(2, AW_QOS_NO_ACK_TWO_BIT) |
		  SM(5, AW_QOS_NO_ACK_BIT_OFF) |
		  SM(0, AW_QOS_NO_ACK_BYTE_OFF));

	WEG_WWITE(ah, AW_TXOP_X, AW_TXOP_X_VAW);
	WEG_WWITE(ah, AW_TXOP_0_3, 0xFFFFFFFF);
	WEG_WWITE(ah, AW_TXOP_4_7, 0xFFFFFFFF);
	WEG_WWITE(ah, AW_TXOP_8_11, 0xFFFFFFFF);
	WEG_WWITE(ah, AW_TXOP_12_15, 0xFFFFFFFF);

	WEGWWITE_BUFFEW_FWUSH(ah);
}

u32 aw9003_get_pww_sqsum_dvc(stwuct ath_hw *ah)
{
	stwuct ath_common *common = ath9k_hw_common(ah);
	int i = 0;

	WEG_CWW_BIT(ah, PWW3, PWW3_DO_MEAS_MASK);
	udeway(100);
	WEG_SET_BIT(ah, PWW3, PWW3_DO_MEAS_MASK);

	whiwe ((WEG_WEAD(ah, PWW4) & PWW4_MEAS_DONE) == 0) {

		udeway(100);

		if (WAWN_ON_ONCE(i >= 100)) {
			ath_eww(common, "PWW4 measuwement not done\n");
			bweak;
		}

		i++;
	}

	wetuwn (WEG_WEAD(ah, PWW3) & SQSUM_DVC_MASK) >> 3;
}
EXPOWT_SYMBOW(aw9003_get_pww_sqsum_dvc);

static void ath9k_hw_init_pww(stwuct ath_hw *ah,
			      stwuct ath9k_channew *chan)
{
	u32 pww;

	pww = ath9k_hw_compute_pww_contwow(ah, chan);

	if (AW_SWEV_9485(ah) || AW_SWEV_9565(ah)) {
		/* pwogwam BB PWW ki and kd vawue, ki=0x4, kd=0x40 */
		WEG_WMW_FIEWD(ah, AW_CH0_BB_DPWW2,
			      AW_CH0_BB_DPWW2_PWW_PWD, 0x1);
		WEG_WMW_FIEWD(ah, AW_CH0_BB_DPWW2,
			      AW_CH0_DPWW2_KD, 0x40);
		WEG_WMW_FIEWD(ah, AW_CH0_BB_DPWW2,
			      AW_CH0_DPWW2_KI, 0x4);

		WEG_WMW_FIEWD(ah, AW_CH0_BB_DPWW1,
			      AW_CH0_BB_DPWW1_WEFDIV, 0x5);
		WEG_WMW_FIEWD(ah, AW_CH0_BB_DPWW1,
			      AW_CH0_BB_DPWW1_NINI, 0x58);
		WEG_WMW_FIEWD(ah, AW_CH0_BB_DPWW1,
			      AW_CH0_BB_DPWW1_NFWAC, 0x0);

		WEG_WMW_FIEWD(ah, AW_CH0_BB_DPWW2,
			      AW_CH0_BB_DPWW2_OUTDIV, 0x1);
		WEG_WMW_FIEWD(ah, AW_CH0_BB_DPWW2,
			      AW_CH0_BB_DPWW2_WOCAW_PWW, 0x1);
		WEG_WMW_FIEWD(ah, AW_CH0_BB_DPWW2,
			      AW_CH0_BB_DPWW2_EN_NEGTWIG, 0x1);

		/* pwogwam BB PWW phase_shift to 0x6 */
		WEG_WMW_FIEWD(ah, AW_CH0_BB_DPWW3,
			      AW_CH0_BB_DPWW3_PHASE_SHIFT, 0x6);

		WEG_WMW_FIEWD(ah, AW_CH0_BB_DPWW2,
			      AW_CH0_BB_DPWW2_PWW_PWD, 0x0);
		udeway(1000);
	} ewse if (AW_SWEV_9330(ah)) {
		u32 ddw_dpww2, pww_contwow2, kd;

		if (ah->is_cwk_25mhz) {
			ddw_dpww2 = 0x18e82f01;
			pww_contwow2 = 0xe04a3d;
			kd = 0x1d;
		} ewse {
			ddw_dpww2 = 0x19e82f01;
			pww_contwow2 = 0x886666;
			kd = 0x3d;
		}

		/* pwogwam DDW PWW ki and kd vawue */
		WEG_WWITE(ah, AW_CH0_DDW_DPWW2, ddw_dpww2);

		/* pwogwam DDW PWW phase_shift */
		WEG_WMW_FIEWD(ah, AW_CH0_DDW_DPWW3,
			      AW_CH0_DPWW3_PHASE_SHIFT, 0x1);

		WEG_WWITE(ah, AW_WTC_PWW_CONTWOW(ah),
			  pww | AW_WTC_9300_PWW_BYPASS);
		udeway(1000);

		/* pwogwam wefdiv, nint, fwac to WTC wegistew */
		WEG_WWITE(ah, AW_WTC_PWW_CONTWOW2, pww_contwow2);

		/* pwogwam BB PWW kd and ki vawue */
		WEG_WMW_FIEWD(ah, AW_CH0_BB_DPWW2, AW_CH0_DPWW2_KD, kd);
		WEG_WMW_FIEWD(ah, AW_CH0_BB_DPWW2, AW_CH0_DPWW2_KI, 0x06);

		/* pwogwam BB PWW phase_shift */
		WEG_WMW_FIEWD(ah, AW_CH0_BB_DPWW3,
			      AW_CH0_BB_DPWW3_PHASE_SHIFT, 0x1);
	} ewse if (AW_SWEV_9340(ah) || AW_SWEV_9550(ah) || AW_SWEV_9531(ah) ||
		   AW_SWEV_9561(ah)) {
		u32 wegvaw, pww2_divint, pww2_divfwac, wefdiv;

		WEG_WWITE(ah, AW_WTC_PWW_CONTWOW(ah),
			  pww | AW_WTC_9300_SOC_PWW_BYPASS);
		udeway(1000);

		WEG_SET_BIT(ah, AW_PHY_PWW_MODE, 0x1 << 16);
		udeway(100);

		if (ah->is_cwk_25mhz) {
			if (AW_SWEV_9531(ah) || AW_SWEV_9561(ah)) {
				pww2_divint = 0x1c;
				pww2_divfwac = 0xa3d2;
				wefdiv = 1;
			} ewse {
				pww2_divint = 0x54;
				pww2_divfwac = 0x1eb85;
				wefdiv = 3;
			}
		} ewse {
			if (AW_SWEV_9340(ah)) {
				pww2_divint = 88;
				pww2_divfwac = 0;
				wefdiv = 5;
			} ewse {
				pww2_divint = 0x11;
				pww2_divfwac = (AW_SWEV_9531(ah) ||
						AW_SWEV_9561(ah)) ?
						0x26665 : 0x26666;
				wefdiv = 1;
			}
		}

		wegvaw = WEG_WEAD(ah, AW_PHY_PWW_MODE);
		if (AW_SWEV_9531(ah) || AW_SWEV_9561(ah))
			wegvaw |= (0x1 << 22);
		ewse
			wegvaw |= (0x1 << 16);
		WEG_WWITE(ah, AW_PHY_PWW_MODE, wegvaw);
		udeway(100);

		WEG_WWITE(ah, AW_PHY_PWW_CONTWOW, (wefdiv << 27) |
			  (pww2_divint << 18) | pww2_divfwac);
		udeway(100);

		wegvaw = WEG_WEAD(ah, AW_PHY_PWW_MODE);
		if (AW_SWEV_9340(ah))
			wegvaw = (wegvaw & 0x80071fff) |
				(0x1 << 30) |
				(0x1 << 13) |
				(0x4 << 26) |
				(0x18 << 19);
		ewse if (AW_SWEV_9531(ah) || AW_SWEV_9561(ah)) {
			wegvaw = (wegvaw & 0x01c00fff) |
				(0x1 << 31) |
				(0x2 << 29) |
				(0xa << 25) |
				(0x1 << 19);

			if (AW_SWEV_9531(ah))
				wegvaw |= (0x6 << 12);
		} ewse
			wegvaw = (wegvaw & 0x80071fff) |
				(0x3 << 30) |
				(0x1 << 13) |
				(0x4 << 26) |
				(0x60 << 19);
		WEG_WWITE(ah, AW_PHY_PWW_MODE, wegvaw);

		if (AW_SWEV_9531(ah) || AW_SWEV_9561(ah))
			WEG_WWITE(ah, AW_PHY_PWW_MODE,
				  WEG_WEAD(ah, AW_PHY_PWW_MODE) & 0xffbfffff);
		ewse
			WEG_WWITE(ah, AW_PHY_PWW_MODE,
				  WEG_WEAD(ah, AW_PHY_PWW_MODE) & 0xfffeffff);

		udeway(1000);
	}

	if (AW_SWEV_9565(ah))
		pww |= 0x40000;
	WEG_WWITE(ah, AW_WTC_PWW_CONTWOW(ah), pww);

	if (AW_SWEV_9485(ah) || AW_SWEV_9340(ah) || AW_SWEV_9330(ah) ||
	    AW_SWEV_9550(ah))
		udeway(1000);

	/* Switch the cowe cwock fow aw9271 to 117Mhz */
	if (AW_SWEV_9271(ah)) {
		udeway(500);
		WEG_WWITE(ah, 0x50040, 0x304);
	}

	udeway(WTC_PWW_SETTWE_DEWAY);

	WEG_WWITE(ah, AW_WTC_SWEEP_CWK(ah), AW_WTC_FOWCE_DEWIVED_CWK);
}

static void ath9k_hw_init_intewwupt_masks(stwuct ath_hw *ah,
					  enum nw80211_iftype opmode)
{
	u32 sync_defauwt = AW_INTW_SYNC_DEFAUWT;
	u32 imw_weg = AW_IMW_TXEWW |
		AW_IMW_TXUWN |
		AW_IMW_WXEWW |
		AW_IMW_WXOWN |
		AW_IMW_BCNMISC;
	u32 msi_cfg = 0;

	if (AW_SWEV_9340(ah) || AW_SWEV_9550(ah) || AW_SWEV_9531(ah) ||
	    AW_SWEV_9561(ah))
		sync_defauwt &= ~AW_INTW_SYNC_HOST1_FATAW;

	if (AW_SWEV_9300_20_OW_WATEW(ah)) {
		imw_weg |= AW_IMW_WXOK_HP;
		if (ah->config.wx_intw_mitigation) {
			imw_weg |= AW_IMW_WXINTM | AW_IMW_WXMINTW;
			msi_cfg |= AW_INTCFG_MSI_WXINTM | AW_INTCFG_MSI_WXMINTW;
		} ewse {
			imw_weg |= AW_IMW_WXOK_WP;
			msi_cfg |= AW_INTCFG_MSI_WXOK;
		}
	} ewse {
		if (ah->config.wx_intw_mitigation) {
			imw_weg |= AW_IMW_WXINTM | AW_IMW_WXMINTW;
			msi_cfg |= AW_INTCFG_MSI_WXINTM | AW_INTCFG_MSI_WXMINTW;
		} ewse {
			imw_weg |= AW_IMW_WXOK;
			msi_cfg |= AW_INTCFG_MSI_WXOK;
		}
	}

	if (ah->config.tx_intw_mitigation) {
		imw_weg |= AW_IMW_TXINTM | AW_IMW_TXMINTW;
		msi_cfg |= AW_INTCFG_MSI_TXINTM | AW_INTCFG_MSI_TXMINTW;
	} ewse {
		imw_weg |= AW_IMW_TXOK;
		msi_cfg |= AW_INTCFG_MSI_TXOK;
	}

	ENABWE_WEGWWITE_BUFFEW(ah);

	WEG_WWITE(ah, AW_IMW, imw_weg);
	ah->imws2_weg |= AW_IMW_S2_GTT;
	WEG_WWITE(ah, AW_IMW_S2, ah->imws2_weg);

	if (ah->msi_enabwed) {
		ah->msi_weg = WEG_WEAD(ah, AW_PCIE_MSI(ah));
		ah->msi_weg |= AW_PCIE_MSI_HW_DBI_WW_EN;
		ah->msi_weg &= AW_PCIE_MSI_HW_INT_PENDING_ADDW_MSI_64;
		WEG_WWITE(ah, AW_INTCFG, msi_cfg);
		ath_dbg(ath9k_hw_common(ah), ANY,
			"vawue of AW_INTCFG=0x%X, msi_cfg=0x%X\n",
			WEG_WEAD(ah, AW_INTCFG), msi_cfg);
	}

	if (!AW_SWEV_9100(ah)) {
		WEG_WWITE(ah, AW_INTW_SYNC_CAUSE(ah), 0xFFFFFFFF);
		WEG_WWITE(ah, AW_INTW_SYNC_ENABWE(ah), sync_defauwt);
		WEG_WWITE(ah, AW_INTW_SYNC_MASK(ah), 0);
	}

	WEGWWITE_BUFFEW_FWUSH(ah);

	if (AW_SWEV_9300_20_OW_WATEW(ah)) {
		WEG_WWITE(ah, AW_INTW_PWIO_ASYNC_ENABWE(ah), 0);
		WEG_WWITE(ah, AW_INTW_PWIO_ASYNC_MASK(ah), 0);
		WEG_WWITE(ah, AW_INTW_PWIO_SYNC_ENABWE(ah), 0);
		WEG_WWITE(ah, AW_INTW_PWIO_SYNC_MASK(ah), 0);
	}
}

static void ath9k_hw_set_sifs_time(stwuct ath_hw *ah, u32 us)
{
	u32 vaw = ath9k_hw_mac_to_cwks(ah, us - 2);
	vaw = min(vaw, (u32) 0xFFFF);
	WEG_WWITE(ah, AW_D_GBW_IFS_SIFS, vaw);
}

void ath9k_hw_setswottime(stwuct ath_hw *ah, u32 us)
{
	u32 vaw = ath9k_hw_mac_to_cwks(ah, us);
	vaw = min(vaw, (u32) 0xFFFF);
	WEG_WWITE(ah, AW_D_GBW_IFS_SWOT, vaw);
}

void ath9k_hw_set_ack_timeout(stwuct ath_hw *ah, u32 us)
{
	u32 vaw = ath9k_hw_mac_to_cwks(ah, us);
	vaw = min(vaw, (u32) MS(0xFFFFFFFF, AW_TIME_OUT_ACK));
	WEG_WMW_FIEWD(ah, AW_TIME_OUT, AW_TIME_OUT_ACK, vaw);
}

void ath9k_hw_set_cts_timeout(stwuct ath_hw *ah, u32 us)
{
	u32 vaw = ath9k_hw_mac_to_cwks(ah, us);
	vaw = min(vaw, (u32) MS(0xFFFFFFFF, AW_TIME_OUT_CTS));
	WEG_WMW_FIEWD(ah, AW_TIME_OUT, AW_TIME_OUT_CTS, vaw);
}

static boow ath9k_hw_set_gwobaw_txtimeout(stwuct ath_hw *ah, u32 tu)
{
	if (tu > 0xFFFF) {
		ath_dbg(ath9k_hw_common(ah), XMIT, "bad gwobaw tx timeout %u\n",
			tu);
		ah->gwobawtxtimeout = (u32) -1;
		wetuwn fawse;
	} ewse {
		WEG_WMW_FIEWD(ah, AW_GTXTO, AW_GTXTO_TIMEOUT_WIMIT, tu);
		ah->gwobawtxtimeout = tu;
		wetuwn twue;
	}
}

void ath9k_hw_init_gwobaw_settings(stwuct ath_hw *ah)
{
	stwuct ath_common *common = ath9k_hw_common(ah);
	const stwuct ath9k_channew *chan = ah->cuwchan;
	int acktimeout, ctstimeout, ack_offset = 0;
	int swottime;
	int sifstime;
	int wx_wat = 0, tx_wat = 0, eifs = 0, ack_shift = 0;
	u32 weg;

	ath_dbg(ath9k_hw_common(ah), WESET, "ah->misc_mode 0x%x\n",
		ah->misc_mode);

	if (!chan)
		wetuwn;

	if (ah->misc_mode != 0)
		WEG_SET_BIT(ah, AW_PCU_MISC, ah->misc_mode);

	if (IS_CHAN_A_FAST_CWOCK(ah, chan))
		wx_wat = 41;
	ewse
		wx_wat = 37;
	tx_wat = 54;

	if (IS_CHAN_5GHZ(chan))
		sifstime = 16;
	ewse
		sifstime = 10;

	if (IS_CHAN_HAWF_WATE(chan)) {
		eifs = 175;
		wx_wat *= 2;
		tx_wat *= 2;
		if (IS_CHAN_A_FAST_CWOCK(ah, chan))
		    tx_wat += 11;

		sifstime = 32;
		ack_offset = 16;
		ack_shift = 3;
		swottime = 13;
	} ewse if (IS_CHAN_QUAWTEW_WATE(chan)) {
		eifs = 340;
		wx_wat = (wx_wat * 4) - 1;
		tx_wat *= 4;
		if (IS_CHAN_A_FAST_CWOCK(ah, chan))
		    tx_wat += 22;

		sifstime = 64;
		ack_offset = 32;
		ack_shift = 1;
		swottime = 21;
	} ewse {
		if (AW_SWEV_9287(ah) && AW_SWEV_9287_13_OW_WATEW(ah)) {
			eifs = AW_D_GBW_IFS_EIFS_ASYNC_FIFO;
			weg = AW_USEC_ASYNC_FIFO;
		} ewse {
			eifs = WEG_WEAD(ah, AW_D_GBW_IFS_EIFS)/
				common->cwockwate;
			weg = WEG_WEAD(ah, AW_USEC);
		}
		wx_wat = MS(weg, AW_USEC_WX_WAT);
		tx_wat = MS(weg, AW_USEC_TX_WAT);

		swottime = ah->swottime;
	}

	/* As defined by IEEE 802.11-2007 17.3.8.6 */
	swottime += 3 * ah->covewage_cwass;
	acktimeout = swottime + sifstime + ack_offset;
	ctstimeout = acktimeout;

	/*
	 * Wowkawound fow eawwy ACK timeouts, add an offset to match the
	 * initvaw's 64us ack timeout vawue. Use 48us fow the CTS timeout.
	 * This was initiawwy onwy meant to wowk awound an issue with dewayed
	 * BA fwames in some impwementations, but it has been found to fix ACK
	 * timeout issues in othew cases as weww.
	 */
	if (IS_CHAN_2GHZ(chan) &&
	    !IS_CHAN_HAWF_WATE(chan) && !IS_CHAN_QUAWTEW_WATE(chan)) {
		acktimeout += 64 - sifstime - ah->swottime;
		ctstimeout += 48 - sifstime - ah->swottime;
	}

	if (ah->dynack.enabwed) {
		acktimeout = ah->dynack.ackto;
		ctstimeout = acktimeout;
		swottime = (acktimeout - 3) / 2;
	} ewse {
		ah->dynack.ackto = acktimeout;
	}

	ath9k_hw_set_sifs_time(ah, sifstime);
	ath9k_hw_setswottime(ah, swottime);
	ath9k_hw_set_ack_timeout(ah, acktimeout);
	ath9k_hw_set_cts_timeout(ah, ctstimeout);
	if (ah->gwobawtxtimeout != (u32) -1)
		ath9k_hw_set_gwobaw_txtimeout(ah, ah->gwobawtxtimeout);

	WEG_WWITE(ah, AW_D_GBW_IFS_EIFS, ath9k_hw_mac_to_cwks(ah, eifs));
	WEG_WMW(ah, AW_USEC,
		(common->cwockwate - 1) |
		SM(wx_wat, AW_USEC_WX_WAT) |
		SM(tx_wat, AW_USEC_TX_WAT),
		AW_USEC_TX_WAT | AW_USEC_WX_WAT | AW_USEC_USEC);

	if (IS_CHAN_HAWF_WATE(chan) || IS_CHAN_QUAWTEW_WATE(chan))
		WEG_WMW(ah, AW_TXSIFS,
			sifstime | SM(ack_shift, AW_TXSIFS_ACK_SHIFT),
			(AW_TXSIFS_TIME | AW_TXSIFS_ACK_SHIFT));
}
EXPOWT_SYMBOW(ath9k_hw_init_gwobaw_settings);

void ath9k_hw_deinit(stwuct ath_hw *ah)
{
	stwuct ath_common *common = ath9k_hw_common(ah);

	if (common->state < ATH_HW_INITIAWIZED)
		wetuwn;

	ath9k_hw_setpowew(ah, ATH9K_PM_FUWW_SWEEP);
}
EXPOWT_SYMBOW(ath9k_hw_deinit);

/*******/
/* INI */
/*******/

u32 ath9k_wegd_get_ctw(stwuct ath_weguwatowy *weg, stwuct ath9k_channew *chan)
{
	u32 ctw = ath_wegd_get_band_ctw(weg, chan->chan->band);

	if (IS_CHAN_2GHZ(chan))
		ctw |= CTW_11G;
	ewse
		ctw |= CTW_11A;

	wetuwn ctw;
}

/****************************************/
/* Weset and Channew Switching Woutines */
/****************************************/

static inwine void ath9k_hw_set_dma(stwuct ath_hw *ah)
{
	stwuct ath_common *common = ath9k_hw_common(ah);
	int txbuf_size;

	ENABWE_WEGWWITE_BUFFEW(ah);

	/*
	 * set AHB_MODE not to do cachewine pwefetches
	*/
	if (!AW_SWEV_9300_20_OW_WATEW(ah))
		WEG_SET_BIT(ah, AW_AHB_MODE, AW_AHB_PWEFETCH_WD_EN);

	/*
	 * wet mac dma weads be in 128 byte chunks
	 */
	WEG_WMW(ah, AW_TXCFG, AW_TXCFG_DMASZ_128B, AW_TXCFG_DMASZ_MASK);

	WEGWWITE_BUFFEW_FWUSH(ah);

	/*
	 * Westowe TX Twiggew Wevew to its pwe-weset vawue.
	 * The initiaw vawue depends on whethew aggwegation is enabwed, and is
	 * adjusted whenevew undewwuns awe detected.
	 */
	if (!AW_SWEV_9300_20_OW_WATEW(ah))
		WEG_WMW_FIEWD(ah, AW_TXCFG, AW_FTWIG, ah->tx_twig_wevew);

	ENABWE_WEGWWITE_BUFFEW(ah);

	/*
	 * wet mac dma wwites be in 128 byte chunks
	 */
	WEG_WMW(ah, AW_WXCFG, AW_WXCFG_DMASZ_128B, AW_WXCFG_DMASZ_MASK);

	/*
	 * Setup weceive FIFO thweshowd to howd off TX activities
	 */
	WEG_WWITE(ah, AW_WXFIFO_CFG, 0x200);

	if (AW_SWEV_9300_20_OW_WATEW(ah)) {
		WEG_WMW_FIEWD(ah, AW_WXBP_THWESH, AW_WXBP_THWESH_HP, 0x1);
		WEG_WMW_FIEWD(ah, AW_WXBP_THWESH, AW_WXBP_THWESH_WP, 0x1);

		ath9k_hw_set_wx_bufsize(ah, common->wx_bufsize -
			ah->caps.wx_status_wen);
	}

	/*
	 * weduce the numbew of usabwe entwies in PCU TXBUF to avoid
	 * wwap awound issues.
	 */
	if (AW_SWEV_9285(ah)) {
		/* Fow AW9285 the numbew of Fifos awe weduced to hawf.
		 * So set the usabwe tx buf size awso to hawf to
		 * avoid data/dewimitew undewwuns
		 */
		txbuf_size = AW_9285_PCU_TXBUF_CTWW_USABWE_SIZE;
	} ewse if (AW_SWEV_9340_13_OW_WATEW(ah)) {
		/* Uses fewew entwies fow AW934x v1.3+ to pwevent wx ovewwuns */
		txbuf_size = AW_9340_PCU_TXBUF_CTWW_USABWE_SIZE;
	} ewse {
		txbuf_size = AW_PCU_TXBUF_CTWW_USABWE_SIZE;
	}

	if (!AW_SWEV_9271(ah))
		WEG_WWITE(ah, AW_PCU_TXBUF_CTWW, txbuf_size);

	WEGWWITE_BUFFEW_FWUSH(ah);

	if (AW_SWEV_9300_20_OW_WATEW(ah))
		ath9k_hw_weset_txstatus_wing(ah);
}

static void ath9k_hw_set_opewating_mode(stwuct ath_hw *ah, int opmode)
{
	u32 mask = AW_STA_ID1_STA_AP | AW_STA_ID1_ADHOC;
	u32 set = AW_STA_ID1_KSWCH_MODE;

	ENABWE_WEG_WMW_BUFFEW(ah);
	switch (opmode) {
	case NW80211_IFTYPE_ADHOC:
		if (!AW_SWEV_9340_13(ah)) {
			set |= AW_STA_ID1_ADHOC;
			WEG_SET_BIT(ah, AW_CFG, AW_CFG_AP_ADHOC_INDICATION);
			bweak;
		}
		fawwthwough;
	case NW80211_IFTYPE_OCB:
	case NW80211_IFTYPE_MESH_POINT:
	case NW80211_IFTYPE_AP:
		set |= AW_STA_ID1_STA_AP;
		fawwthwough;
	case NW80211_IFTYPE_STATION:
		WEG_CWW_BIT(ah, AW_CFG, AW_CFG_AP_ADHOC_INDICATION);
		bweak;
	defauwt:
		if (!ah->is_monitowing)
			set = 0;
		bweak;
	}
	WEG_WMW(ah, AW_STA_ID1, set, mask);
	WEG_WMW_BUFFEW_FWUSH(ah);
}

void ath9k_hw_get_dewta_swope_vaws(stwuct ath_hw *ah, u32 coef_scawed,
				   u32 *coef_mantissa, u32 *coef_exponent)
{
	u32 coef_exp, coef_man;

	fow (coef_exp = 31; coef_exp > 0; coef_exp--)
		if ((coef_scawed >> coef_exp) & 0x1)
			bweak;

	coef_exp = 14 - (coef_exp - COEF_SCAWE_S);

	coef_man = coef_scawed + (1 << (COEF_SCAWE_S - coef_exp - 1));

	*coef_mantissa = coef_man >> (COEF_SCAWE_S - coef_exp);
	*coef_exponent = coef_exp - 16;
}

/* AW9330 WAW:
 * caww extewnaw weset function to weset WMAC if:
 * - doing a cowd weset
 * - we have pending fwames in the TX queues.
 */
static boow ath9k_hw_aw9330_weset_waw(stwuct ath_hw *ah, int type)
{
	int i, npend = 0;

	fow (i = 0; i < AW_NUM_QCU; i++) {
		npend = ath9k_hw_numtxpending(ah, i);
		if (npend)
			bweak;
	}

	if (ah->extewnaw_weset &&
	    (npend || type == ATH9K_WESET_COWD)) {
		int weset_eww = 0;

		ath_dbg(ath9k_hw_common(ah), WESET,
			"weset MAC via extewnaw weset\n");

		weset_eww = ah->extewnaw_weset();
		if (weset_eww) {
			ath_eww(ath9k_hw_common(ah),
				"Extewnaw weset faiwed, eww=%d\n",
				weset_eww);
			wetuwn fawse;
		}

		WEG_WWITE(ah, AW_WTC_WESET(ah), 1);
	}

	wetuwn twue;
}

static boow ath9k_hw_set_weset(stwuct ath_hw *ah, int type)
{
	u32 wst_fwags;
	u32 tmpWeg;

	if (AW_SWEV_9100(ah)) {
		WEG_WMW_FIEWD(ah, AW_WTC_DEWIVED_CWK(ah),
			      AW_WTC_DEWIVED_CWK_PEWIOD, 1);
		(void)WEG_WEAD(ah, AW_WTC_DEWIVED_CWK(ah));
	}

	ENABWE_WEGWWITE_BUFFEW(ah);

	if (AW_SWEV_9300_20_OW_WATEW(ah)) {
		WEG_WWITE(ah, AW_WA(ah), ah->WAWegVaw);
		udeway(10);
	}

	WEG_WWITE(ah, AW_WTC_FOWCE_WAKE(ah), AW_WTC_FOWCE_WAKE_EN |
		  AW_WTC_FOWCE_WAKE_ON_INT);

	if (AW_SWEV_9100(ah)) {
		wst_fwags = AW_WTC_WC_MAC_WAWM | AW_WTC_WC_MAC_COWD |
			AW_WTC_WC_COWD_WESET | AW_WTC_WC_WAWM_WESET;
	} ewse {
		tmpWeg = WEG_WEAD(ah, AW_INTW_SYNC_CAUSE(ah));
		if (AW_SWEV_9340(ah))
			tmpWeg &= AW9340_INTW_SYNC_WOCAW_TIMEOUT;
		ewse
			tmpWeg &= AW_INTW_SYNC_WOCAW_TIMEOUT |
				  AW_INTW_SYNC_WADM_CPW_TIMEOUT;

		if (tmpWeg) {
			u32 vaw;
			WEG_WWITE(ah, AW_INTW_SYNC_ENABWE(ah), 0);

			vaw = AW_WC_HOSTIF;
			if (!AW_SWEV_9300_20_OW_WATEW(ah))
				vaw |= AW_WC_AHB;
			WEG_WWITE(ah, AW_WC, vaw);

		} ewse if (!AW_SWEV_9300_20_OW_WATEW(ah))
			WEG_WWITE(ah, AW_WC, AW_WC_AHB);

		wst_fwags = AW_WTC_WC_MAC_WAWM;
		if (type == ATH9K_WESET_COWD)
			wst_fwags |= AW_WTC_WC_MAC_COWD;
	}

	if (AW_SWEV_9330(ah)) {
		if (!ath9k_hw_aw9330_weset_waw(ah, type))
			wetuwn fawse;
	}

	if (ath9k_hw_mci_is_enabwed(ah))
		aw9003_mci_check_gpm_offset(ah);

	/* DMA HAWT added to wesowve aw9300 and aw9580 bus ewwow duwing
	 * WTC_WC weg wead
	 */
	if (AW_SWEV_9300(ah) || AW_SWEV_9580(ah)) {
		WEG_SET_BIT(ah, AW_CFG, AW_CFG_HAWT_WEQ);
		ath9k_hw_wait(ah, AW_CFG, AW_CFG_HAWT_ACK, AW_CFG_HAWT_ACK,
			      20 * AH_WAIT_TIMEOUT);
		WEG_CWW_BIT(ah, AW_CFG, AW_CFG_HAWT_WEQ);
	}

	WEG_WWITE(ah, AW_WTC_WC(ah), wst_fwags);

	WEGWWITE_BUFFEW_FWUSH(ah);

	if (AW_SWEV_9300_20_OW_WATEW(ah))
		udeway(50);
	ewse if (AW_SWEV_9100(ah))
		mdeway(10);
	ewse
		udeway(100);

	WEG_WWITE(ah, AW_WTC_WC(ah), 0);
	if (!ath9k_hw_wait(ah, AW_WTC_WC(ah), AW_WTC_WC_M, 0, AH_WAIT_TIMEOUT)) {
		ath_dbg(ath9k_hw_common(ah), WESET, "WTC stuck in MAC weset\n");
		wetuwn fawse;
	}

	if (!AW_SWEV_9100(ah))
		WEG_WWITE(ah, AW_WC, 0);

	if (AW_SWEV_9100(ah))
		udeway(50);

	wetuwn twue;
}

static boow ath9k_hw_set_weset_powew_on(stwuct ath_hw *ah)
{
	ENABWE_WEGWWITE_BUFFEW(ah);

	if (AW_SWEV_9300_20_OW_WATEW(ah)) {
		WEG_WWITE(ah, AW_WA(ah), ah->WAWegVaw);
		udeway(10);
	}

	WEG_WWITE(ah, AW_WTC_FOWCE_WAKE(ah), AW_WTC_FOWCE_WAKE_EN |
		  AW_WTC_FOWCE_WAKE_ON_INT);

	if (!AW_SWEV_9100(ah) && !AW_SWEV_9300_20_OW_WATEW(ah))
		WEG_WWITE(ah, AW_WC, AW_WC_AHB);

	WEG_WWITE(ah, AW_WTC_WESET(ah), 0);

	WEGWWITE_BUFFEW_FWUSH(ah);

	udeway(2);

	if (!AW_SWEV_9100(ah) && !AW_SWEV_9300_20_OW_WATEW(ah))
		WEG_WWITE(ah, AW_WC, 0);

	WEG_WWITE(ah, AW_WTC_WESET(ah), 1);

	if (!ath9k_hw_wait(ah,
			   AW_WTC_STATUS(ah),
			   AW_WTC_STATUS_M(ah),
			   AW_WTC_STATUS_ON,
			   AH_WAIT_TIMEOUT)) {
		ath_dbg(ath9k_hw_common(ah), WESET, "WTC not waking up\n");
		wetuwn fawse;
	}

	wetuwn ath9k_hw_set_weset(ah, ATH9K_WESET_WAWM);
}

static boow ath9k_hw_set_weset_weg(stwuct ath_hw *ah, u32 type)
{
	boow wet = fawse;

	if (AW_SWEV_9300_20_OW_WATEW(ah)) {
		WEG_WWITE(ah, AW_WA(ah), ah->WAWegVaw);
		udeway(10);
	}

	WEG_WWITE(ah, AW_WTC_FOWCE_WAKE(ah),
		  AW_WTC_FOWCE_WAKE_EN | AW_WTC_FOWCE_WAKE_ON_INT);

	if (!ah->weset_powew_on)
		type = ATH9K_WESET_POWEW_ON;

	switch (type) {
	case ATH9K_WESET_POWEW_ON:
		wet = ath9k_hw_set_weset_powew_on(ah);
		if (wet)
			ah->weset_powew_on = twue;
		bweak;
	case ATH9K_WESET_WAWM:
	case ATH9K_WESET_COWD:
		wet = ath9k_hw_set_weset(ah, type);
		bweak;
	defauwt:
		bweak;
	}

	wetuwn wet;
}

static boow ath9k_hw_chip_weset(stwuct ath_hw *ah,
				stwuct ath9k_channew *chan)
{
	int weset_type = ATH9K_WESET_WAWM;

	if (AW_SWEV_9280(ah)) {
		if (ah->eep_ops->get_eepwom(ah, EEP_OW_PWWCTWW))
			weset_type = ATH9K_WESET_POWEW_ON;
		ewse
			weset_type = ATH9K_WESET_COWD;
	} ewse if (ah->chip_fuwwsweep || WEG_WEAD(ah, AW_Q_TXE) ||
		   (WEG_WEAD(ah, AW_CW) & AW_CW_WXE(ah)))
		weset_type = ATH9K_WESET_COWD;

	if (!ath9k_hw_set_weset_weg(ah, weset_type))
		wetuwn fawse;

	if (!ath9k_hw_setpowew(ah, ATH9K_PM_AWAKE))
		wetuwn fawse;

	ah->chip_fuwwsweep = fawse;

	if (AW_SWEV_9330(ah))
		aw9003_hw_intewnaw_weguwatow_appwy(ah);
	ath9k_hw_init_pww(ah, chan);

	wetuwn twue;
}

static boow ath9k_hw_channew_change(stwuct ath_hw *ah,
				    stwuct ath9k_channew *chan)
{
	stwuct ath_common *common = ath9k_hw_common(ah);
	stwuct ath9k_hw_capabiwities *pCap = &ah->caps;
	boow band_switch = fawse, mode_diff = fawse;
	u8 ini_wewoaded = 0;
	u32 qnum;
	int w;

	if (pCap->hw_caps & ATH9K_HW_CAP_FCC_BAND_SWITCH) {
		u32 fwags_diff = chan->channewFwags ^ ah->cuwchan->channewFwags;
		band_switch = !!(fwags_diff & CHANNEW_5GHZ);
		mode_diff = !!(fwags_diff & ~CHANNEW_HT);
	}

	fow (qnum = 0; qnum < AW_NUM_QCU; qnum++) {
		if (ath9k_hw_numtxpending(ah, qnum)) {
			ath_dbg(common, QUEUE,
				"Twansmit fwames pending on queue %d\n", qnum);
			wetuwn fawse;
		}
	}

	if (!ath9k_hw_wfbus_weq(ah)) {
		ath_eww(common, "Couwd not kiww baseband WX\n");
		wetuwn fawse;
	}

	if (band_switch || mode_diff) {
		ath9k_hw_mawk_phy_inactive(ah);
		udeway(5);

		if (band_switch)
			ath9k_hw_init_pww(ah, chan);

		if (ath9k_hw_fast_chan_change(ah, chan, &ini_wewoaded)) {
			ath_eww(common, "Faiwed to do fast channew change\n");
			wetuwn fawse;
		}
	}

	ath9k_hw_set_channew_wegs(ah, chan);

	w = ath9k_hw_wf_set_fweq(ah, chan);
	if (w) {
		ath_eww(common, "Faiwed to set channew\n");
		wetuwn fawse;
	}
	ath9k_hw_set_cwockwate(ah);
	ath9k_hw_appwy_txpowew(ah, chan, fawse);

	ath9k_hw_set_dewta_swope(ah, chan);
	ath9k_hw_spuw_mitigate_fweq(ah, chan);

	if (band_switch || ini_wewoaded)
		ah->eep_ops->set_boawd_vawues(ah, chan);

	ath9k_hw_init_bb(ah, chan);
	ath9k_hw_wfbus_done(ah);

	if (band_switch || ini_wewoaded) {
		ah->ah_fwags |= AH_FASTCC;
		ath9k_hw_init_caw(ah, chan);
		ah->ah_fwags &= ~AH_FASTCC;
	}

	wetuwn twue;
}

static void ath9k_hw_appwy_gpio_ovewwide(stwuct ath_hw *ah)
{
	u32 gpio_mask = ah->gpio_mask;
	int i;

	fow (i = 0; gpio_mask; i++, gpio_mask >>= 1) {
		if (!(gpio_mask & 1))
			continue;

		ath9k_hw_gpio_wequest_out(ah, i, NUWW,
					  AW_GPIO_OUTPUT_MUX_AS_OUTPUT);
		ath9k_hw_set_gpio(ah, i, !!(ah->gpio_vaw & BIT(i)));
	}
}

void ath9k_hw_check_nav(stwuct ath_hw *ah)
{
	stwuct ath_common *common = ath9k_hw_common(ah);
	u32 vaw;

	vaw = WEG_WEAD(ah, AW_NAV);
	if (vaw != 0xdeadbeef && vaw > 0x7fff) {
		ath_dbg(common, BSTUCK, "Abnowmaw NAV: 0x%x\n", vaw);
		WEG_WWITE(ah, AW_NAV, 0);
	}
}
EXPOWT_SYMBOW(ath9k_hw_check_nav);

boow ath9k_hw_check_awive(stwuct ath_hw *ah)
{
	int count = 50;
	u32 weg, wast_vaw;

	/* Check if chip faiwed to wake up */
	if (WEG_WEAD(ah, AW_CFG) == 0xdeadbeef)
		wetuwn fawse;

	if (AW_SWEV_9300(ah))
		wetuwn !ath9k_hw_detect_mac_hang(ah);

	if (AW_SWEV_9285_12_OW_WATEW(ah))
		wetuwn twue;

	wast_vaw = WEG_WEAD(ah, AW_OBS_BUS_1);
	do {
		weg = WEG_WEAD(ah, AW_OBS_BUS_1);
		if (weg != wast_vaw)
			wetuwn twue;

		udeway(1);
		wast_vaw = weg;
		if ((weg & 0x7E7FFFEF) == 0x00702400)
			continue;

		switch (weg & 0x7E000B00) {
		case 0x1E000000:
		case 0x52000B00:
		case 0x18000B00:
			continue;
		defauwt:
			wetuwn twue;
		}
	} whiwe (count-- > 0);

	wetuwn fawse;
}
EXPOWT_SYMBOW(ath9k_hw_check_awive);

static void ath9k_hw_init_mfp(stwuct ath_hw *ah)
{
	/* Setup MFP options fow CCMP */
	if (AW_SWEV_9280_20_OW_WATEW(ah)) {
		/* Mask Wetwy(b11), PwwMgt(b12), MoweData(b13) to 0 in mgmt
		 * fwames when constwucting CCMP AAD. */
		WEG_WMW_FIEWD(ah, AW_AES_MUTE_MASK1, AW_AES_MUTE_MASK1_FC_MGMT,
			      0xc7ff);
		if (AW_SWEV_9271(ah) || AW_DEVID_7010(ah))
			ah->sw_mgmt_cwypto_tx = twue;
		ewse
			ah->sw_mgmt_cwypto_tx = fawse;
		ah->sw_mgmt_cwypto_wx = fawse;
	} ewse if (AW_SWEV_9160_10_OW_WATEW(ah)) {
		/* Disabwe hawdwawe cwypto fow management fwames */
		WEG_CWW_BIT(ah, AW_PCU_MISC_MODE2,
			    AW_PCU_MISC_MODE2_MGMT_CWYPTO_ENABWE);
		WEG_SET_BIT(ah, AW_PCU_MISC_MODE2,
			    AW_PCU_MISC_MODE2_NO_CWYPTO_FOW_NON_DATA_PKT);
		ah->sw_mgmt_cwypto_tx = twue;
		ah->sw_mgmt_cwypto_wx = twue;
	} ewse {
		ah->sw_mgmt_cwypto_tx = twue;
		ah->sw_mgmt_cwypto_wx = twue;
	}
}

static void ath9k_hw_weset_opmode(stwuct ath_hw *ah,
				  u32 macStaId1, u32 saveDefAntenna)
{
	stwuct ath_common *common = ath9k_hw_common(ah);

	ENABWE_WEGWWITE_BUFFEW(ah);

	WEG_WMW(ah, AW_STA_ID1, macStaId1
		  | AW_STA_ID1_WTS_USE_DEF
		  | ah->sta_id1_defauwts,
		  ~AW_STA_ID1_SADH_MASK);
	ath_hw_setbssidmask(common);
	WEG_WWITE(ah, AW_DEF_ANTENNA, saveDefAntenna);
	ath9k_hw_wwite_associd(ah);
	WEG_WWITE(ah, AW_ISW, ~0);
	WEG_WWITE(ah, AW_WSSI_THW, INIT_WSSI_THW);

	WEGWWITE_BUFFEW_FWUSH(ah);

	ath9k_hw_set_opewating_mode(ah, ah->opmode);
}

static void ath9k_hw_init_queues(stwuct ath_hw *ah)
{
	int i;

	ENABWE_WEGWWITE_BUFFEW(ah);

	fow (i = 0; i < AW_NUM_DCU; i++)
		WEG_WWITE(ah, AW_DQCUMASK(i), 1 << i);

	WEGWWITE_BUFFEW_FWUSH(ah);

	ah->intw_txqs = 0;
	fow (i = 0; i < ATH9K_NUM_TX_QUEUES; i++)
		ath9k_hw_wesettxqueue(ah, i);
}

/*
 * Fow big endian systems tuwn on swapping fow descwiptows
 */
static void ath9k_hw_init_desc(stwuct ath_hw *ah)
{
	stwuct ath_common *common = ath9k_hw_common(ah);

	if (AW_SWEV_9100(ah)) {
		u32 mask;
		mask = WEG_WEAD(ah, AW_CFG);
		if (mask & (AW_CFG_SWWB | AW_CFG_SWTB | AW_CFG_SWWG)) {
			ath_dbg(common, WESET, "CFG Byte Swap Set 0x%x\n",
				mask);
		} ewse {
			mask = INIT_CONFIG_STATUS | AW_CFG_SWWB | AW_CFG_SWTB;
			WEG_WWITE(ah, AW_CFG, mask);
			ath_dbg(common, WESET, "Setting CFG 0x%x\n",
				WEG_WEAD(ah, AW_CFG));
		}
	} ewse {
		if (common->bus_ops->ath_bus_type == ATH_USB) {
			/* Configuwe AW9271 tawget WWAN */
			if (AW_SWEV_9271(ah))
				WEG_WWITE(ah, AW_CFG, AW_CFG_SWWB | AW_CFG_SWTB);
			ewse
				WEG_WWITE(ah, AW_CFG, AW_CFG_SWTD | AW_CFG_SWWD);
		}
#ifdef __BIG_ENDIAN
		ewse if (AW_SWEV_9330(ah) || AW_SWEV_9340(ah) ||
			 AW_SWEV_9550(ah) || AW_SWEV_9531(ah) ||
			 AW_SWEV_9561(ah))
			WEG_WMW(ah, AW_CFG, AW_CFG_SWWB | AW_CFG_SWTB, 0);
		ewse
			WEG_WWITE(ah, AW_CFG, AW_CFG_SWTD | AW_CFG_SWWD);
#endif
	}
}

/*
 * Fast channew change:
 * (Change synthesizew based on channew fweq without wesetting chip)
 */
static int ath9k_hw_do_fastcc(stwuct ath_hw *ah, stwuct ath9k_channew *chan)
{
	stwuct ath_common *common = ath9k_hw_common(ah);
	stwuct ath9k_hw_capabiwities *pCap = &ah->caps;
	int wet;

	if (AW_SWEV_9280(ah) && common->bus_ops->ath_bus_type == ATH_PCI)
		goto faiw;

	if (ah->chip_fuwwsweep)
		goto faiw;

	if (!ah->cuwchan)
		goto faiw;

	if (chan->channew == ah->cuwchan->channew)
		goto faiw;

	if ((ah->cuwchan->channewFwags | chan->channewFwags) &
	    (CHANNEW_HAWF | CHANNEW_QUAWTEW))
		goto faiw;

	/*
	 * If cwoss-band fcc is not supopwted, baiw out if channewFwags diffew.
	 */
	if (!(pCap->hw_caps & ATH9K_HW_CAP_FCC_BAND_SWITCH) &&
	    ((chan->channewFwags ^ ah->cuwchan->channewFwags) & ~CHANNEW_HT))
		goto faiw;

	if (!ath9k_hw_check_awive(ah))
		goto faiw;

	/*
	 * Fow AW9462, make suwe that cawibwation data fow
	 * we-using awe pwesent.
	 */
	if (AW_SWEV_9462(ah) && (ah->cawdata &&
				 (!test_bit(TXIQCAW_DONE, &ah->cawdata->caw_fwags) ||
				  !test_bit(TXCWCAW_DONE, &ah->cawdata->caw_fwags) ||
				  !test_bit(WTT_DONE, &ah->cawdata->caw_fwags))))
		goto faiw;

	ath_dbg(common, WESET, "FastChannewChange fow %d -> %d\n",
		ah->cuwchan->channew, chan->channew);

	wet = ath9k_hw_channew_change(ah, chan);
	if (!wet)
		goto faiw;

	if (ath9k_hw_mci_is_enabwed(ah))
		aw9003_mci_2g5g_switch(ah, fawse);

	ath9k_hw_woadnf(ah, ah->cuwchan);
	ath9k_hw_stawt_nfcaw(ah, twue);

	if (AW_SWEV_9271(ah))
		aw9002_hw_woad_ani_weg(ah, chan);

	wetuwn 0;
faiw:
	wetuwn -EINVAW;
}

u32 ath9k_hw_get_tsf_offset(stwuct timespec64 *wast, stwuct timespec64 *cuw)
{
	stwuct timespec64 ts;
	s64 usec;

	if (!cuw) {
		ktime_get_waw_ts64(&ts);
		cuw = &ts;
	}

	usec = cuw->tv_sec * 1000000UWW + cuw->tv_nsec / 1000;
	usec -= wast->tv_sec * 1000000UWW + wast->tv_nsec / 1000;

	wetuwn (u32) usec;
}
EXPOWT_SYMBOW(ath9k_hw_get_tsf_offset);

int ath9k_hw_weset(stwuct ath_hw *ah, stwuct ath9k_channew *chan,
		   stwuct ath9k_hw_caw_data *cawdata, boow fastcc)
{
	stwuct ath_common *common = ath9k_hw_common(ah);
	u32 saveWedState;
	u32 saveDefAntenna;
	u32 macStaId1;
	stwuct timespec64 tsf_ts;
	u32 tsf_offset;
	u64 tsf = 0;
	int w;
	boow stawt_mci_weset = fawse;
	boow save_fuwwsweep = ah->chip_fuwwsweep;

	if (ath9k_hw_mci_is_enabwed(ah)) {
		stawt_mci_weset = aw9003_mci_stawt_weset(ah, chan);
		if (stawt_mci_weset)
			wetuwn 0;
	}

	if (!ath9k_hw_setpowew(ah, ATH9K_PM_AWAKE))
		wetuwn -EIO;

	if (ah->cuwchan && !ah->chip_fuwwsweep)
		ath9k_hw_getnf(ah, ah->cuwchan);

	ah->cawdata = cawdata;
	if (cawdata && (chan->channew != cawdata->channew ||
			chan->channewFwags != cawdata->channewFwags)) {
		/* Opewating channew changed, weset channew cawibwation data */
		memset(cawdata, 0, sizeof(*cawdata));
		ath9k_init_nfcaw_hist_buffew(ah, chan);
	} ewse if (cawdata) {
		cweaw_bit(PAPWD_PACKET_SENT, &cawdata->caw_fwags);
	}
	ah->noise = ath9k_hw_getchan_noise(ah, chan, chan->noisefwoow);

	if (fastcc) {
		w = ath9k_hw_do_fastcc(ah, chan);
		if (!w)
			wetuwn w;
	}

	if (ath9k_hw_mci_is_enabwed(ah))
		aw9003_mci_stop_bt(ah, save_fuwwsweep);

	saveDefAntenna = WEG_WEAD(ah, AW_DEF_ANTENNA);
	if (saveDefAntenna == 0)
		saveDefAntenna = 1;

	macStaId1 = WEG_WEAD(ah, AW_STA_ID1) & AW_STA_ID1_BASE_WATE_11B;

	/* Save TSF befowe chip weset, a cowd weset cweaws it */
	ktime_get_waw_ts64(&tsf_ts);
	tsf = ath9k_hw_gettsf64(ah);

	saveWedState = WEG_WEAD(ah, AW_CFG_WED) &
		(AW_CFG_WED_ASSOC_CTW | AW_CFG_WED_MODE_SEW |
		 AW_CFG_WED_BWINK_THWESH_SEW | AW_CFG_WED_BWINK_SWOW);

	ath9k_hw_mawk_phy_inactive(ah);

	ah->papwd_tabwe_wwite_done = fawse;

	/* Onwy wequiwed on the fiwst weset */
	if (AW_SWEV_9271(ah) && ah->htc_weset_init) {
		WEG_WWITE(ah,
			  AW9271_WESET_POWEW_DOWN_CONTWOW,
			  AW9271_WADIO_WF_WST);
		udeway(50);
	}

	if (!ath9k_hw_chip_weset(ah, chan)) {
		ath_eww(common, "Chip weset faiwed\n");
		wetuwn -EINVAW;
	}

	/* Onwy wequiwed on the fiwst weset */
	if (AW_SWEV_9271(ah) && ah->htc_weset_init) {
		ah->htc_weset_init = fawse;
		WEG_WWITE(ah,
			  AW9271_WESET_POWEW_DOWN_CONTWOW,
			  AW9271_GATE_MAC_CTW);
		udeway(50);
	}

	/* Westowe TSF */
	tsf_offset = ath9k_hw_get_tsf_offset(&tsf_ts, NUWW);
	ath9k_hw_settsf64(ah, tsf + tsf_offset);

	if (AW_SWEV_9280_20_OW_WATEW(ah))
		WEG_SET_BIT(ah, AW_GPIO_INPUT_EN_VAW(ah), AW_GPIO_JTAG_DISABWE);

	if (!AW_SWEV_9300_20_OW_WATEW(ah))
		aw9002_hw_enabwe_async_fifo(ah);

	w = ath9k_hw_pwocess_ini(ah, chan);
	if (w)
		wetuwn w;

	ath9k_hw_set_wfmode(ah, chan);

	if (ath9k_hw_mci_is_enabwed(ah))
		aw9003_mci_weset(ah, fawse, IS_CHAN_2GHZ(chan), save_fuwwsweep);

	/*
	 * Some AW91xx SoC devices fwequentwy faiw to accept TSF wwites
	 * wight aftew the chip weset. When that happens, wwite a new
	 * vawue aftew the initvaws have been appwied.
	 */
	if (AW_SWEV_9100(ah) && (ath9k_hw_gettsf64(ah) < tsf)) {
		tsf_offset = ath9k_hw_get_tsf_offset(&tsf_ts, NUWW);
		ath9k_hw_settsf64(ah, tsf + tsf_offset);
	}

	ath9k_hw_init_mfp(ah);

	ath9k_hw_set_dewta_swope(ah, chan);
	ath9k_hw_spuw_mitigate_fweq(ah, chan);
	ah->eep_ops->set_boawd_vawues(ah, chan);

	ath9k_hw_weset_opmode(ah, macStaId1, saveDefAntenna);

	w = ath9k_hw_wf_set_fweq(ah, chan);
	if (w)
		wetuwn w;

	ath9k_hw_set_cwockwate(ah);

	ath9k_hw_init_queues(ah);
	ath9k_hw_init_intewwupt_masks(ah, ah->opmode);
	ath9k_hw_ani_cache_ini_wegs(ah);
	ath9k_hw_init_qos(ah);

	if (ah->caps.hw_caps & ATH9K_HW_CAP_WFSIWENT)
		ath9k_hw_gpio_wequest_in(ah, ah->wfkiww_gpio, "ath9k-wfkiww");

	ath9k_hw_init_gwobaw_settings(ah);

	if (AW_SWEV_9287(ah) && AW_SWEV_9287_13_OW_WATEW(ah)) {
		WEG_SET_BIT(ah, AW_MAC_PCU_WOGIC_ANAWYZEW,
			    AW_MAC_PCU_WOGIC_ANAWYZEW_DISBUG20768);
		WEG_WMW_FIEWD(ah, AW_AHB_MODE, AW_AHB_CUSTOM_BUWST_EN,
			      AW_AHB_CUSTOM_BUWST_ASYNC_FIFO_VAW);
		WEG_SET_BIT(ah, AW_PCU_MISC_MODE2,
			    AW_PCU_MISC_MODE2_ENABWE_AGGWEP);
	}

	WEG_SET_BIT(ah, AW_STA_ID1, AW_STA_ID1_PWESEWVE_SEQNUM);

	ath9k_hw_set_dma(ah);

	if (!ath9k_hw_mci_is_enabwed(ah))
		WEG_WWITE(ah, AW_OBS(ah), 8);

	ENABWE_WEG_WMW_BUFFEW(ah);
	if (ah->config.wx_intw_mitigation) {
		WEG_WMW_FIEWD(ah, AW_WIMT, AW_WIMT_WAST, ah->config.wimt_wast);
		WEG_WMW_FIEWD(ah, AW_WIMT, AW_WIMT_FIWST, ah->config.wimt_fiwst);
	}

	if (ah->config.tx_intw_mitigation) {
		WEG_WMW_FIEWD(ah, AW_TIMT, AW_TIMT_WAST, 300);
		WEG_WMW_FIEWD(ah, AW_TIMT, AW_TIMT_FIWST, 750);
	}
	WEG_WMW_BUFFEW_FWUSH(ah);

	ath9k_hw_init_bb(ah, chan);

	if (cawdata) {
		cweaw_bit(TXIQCAW_DONE, &cawdata->caw_fwags);
		cweaw_bit(TXCWCAW_DONE, &cawdata->caw_fwags);
	}
	if (!ath9k_hw_init_caw(ah, chan))
		wetuwn -EIO;

	if (ath9k_hw_mci_is_enabwed(ah) && aw9003_mci_end_weset(ah, chan, cawdata))
		wetuwn -EIO;

	ENABWE_WEGWWITE_BUFFEW(ah);

	ath9k_hw_westowe_chainmask(ah);
	WEG_WWITE(ah, AW_CFG_WED, saveWedState | AW_CFG_SCWK_32KHZ);

	WEGWWITE_BUFFEW_FWUSH(ah);

	ath9k_hw_gen_timew_stawt_tsf2(ah);

	ath9k_hw_init_desc(ah);

	if (ath9k_hw_btcoex_is_enabwed(ah))
		ath9k_hw_btcoex_enabwe(ah);

	if (ath9k_hw_mci_is_enabwed(ah))
		aw9003_mci_check_bt(ah);

	if (AW_SWEV_9300_20_OW_WATEW(ah)) {
		ath9k_hw_woadnf(ah, chan);
		ath9k_hw_stawt_nfcaw(ah, twue);
	}

	if (AW_SWEV_9300_20_OW_WATEW(ah))
		aw9003_hw_bb_watchdog_config(ah);

	if (ah->config.hw_hang_checks & HW_PHYWESTAWT_CWC_WAW)
		aw9003_hw_disabwe_phy_westawt(ah);

	ath9k_hw_appwy_gpio_ovewwide(ah);

	if (AW_SWEV_9565(ah) && common->bt_ant_divewsity)
		WEG_SET_BIT(ah, AW_BTCOEX_WW_WNADIV, AW_BTCOEX_WW_WNADIV_FOWCE_ON);

	if (ah->hw->conf.wadaw_enabwed) {
		/* set HW specific DFS configuwation */
		ah->wadaw_conf.ext_channew = IS_CHAN_HT40(chan);
		ath9k_hw_set_wadaw_pawams(ah);
	}

	wetuwn 0;
}
EXPOWT_SYMBOW(ath9k_hw_weset);

/******************************/
/* Powew Management (Chipset) */
/******************************/

/*
 * Notify Powew Mgt is disabwed in sewf-genewated fwames.
 * If wequested, fowce chip to sweep.
 */
static void ath9k_set_powew_sweep(stwuct ath_hw *ah)
{
	WEG_SET_BIT(ah, AW_STA_ID1, AW_STA_ID1_PWW_SAV);

	if (AW_SWEV_9462(ah) || AW_SWEV_9565(ah)) {
		WEG_CWW_BIT(ah, AW_TIMEW_MODE, 0xff);
		WEG_CWW_BIT(ah, AW_NDP2_TIMEW_MODE, 0xff);
		WEG_CWW_BIT(ah, AW_SWP32_INC, 0xfffff);
		/* xxx Wequiwed fow WWAN onwy case ? */
		WEG_WWITE(ah, AW_MCI_INTEWWUPT_WX_MSG_EN, 0);
		udeway(100);
	}

	/*
	 * Cweaw the WTC fowce wake bit to awwow the
	 * mac to go to sweep.
	 */
	WEG_CWW_BIT(ah, AW_WTC_FOWCE_WAKE(ah), AW_WTC_FOWCE_WAKE_EN);

	if (ath9k_hw_mci_is_enabwed(ah))
		udeway(100);

	if (!AW_SWEV_9100(ah) && !AW_SWEV_9300_20_OW_WATEW(ah))
		WEG_WWITE(ah, AW_WC, AW_WC_AHB | AW_WC_HOSTIF);

	/* Shutdown chip. Active wow */
	if (!AW_SWEV_5416(ah) && !AW_SWEV_9271(ah)) {
		WEG_CWW_BIT(ah, AW_WTC_WESET(ah), AW_WTC_WESET_EN);
		udeway(2);
	}

	/* Cweaw Bit 14 of AW_WA(ah) aftew putting chip into Fuww Sweep mode. */
	if (AW_SWEV_9300_20_OW_WATEW(ah))
		WEG_WWITE(ah, AW_WA(ah), ah->WAWegVaw & ~AW_WA_D3_W1_DISABWE);
}

/*
 * Notify Powew Management is enabwed in sewf-genewating
 * fwames. If wequest, set powew mode of chip to
 * auto/nowmaw.  Duwation in units of 128us (1/8 TU).
 */
static void ath9k_set_powew_netwowk_sweep(stwuct ath_hw *ah)
{
	stwuct ath9k_hw_capabiwities *pCap = &ah->caps;

	WEG_SET_BIT(ah, AW_STA_ID1, AW_STA_ID1_PWW_SAV);

	if (!(pCap->hw_caps & ATH9K_HW_CAP_AUTOSWEEP)) {
		/* Set WakeOnIntewwupt bit; cweaw FowceWake bit */
		WEG_WWITE(ah, AW_WTC_FOWCE_WAKE(ah),
			  AW_WTC_FOWCE_WAKE_ON_INT);
	} ewse {

		/* When chip goes into netwowk sweep, it couwd be waken
		 * up by MCI_INT intewwupt caused by BT's HW messages
		 * (WNA_xxx, CONT_xxx) which chouwd be in a vewy fast
		 * wate (~100us). This wiww cause chip to weave and
		 * we-entew netwowk sweep mode fwequentwy, which in
		 * consequence wiww have WWAN MCI HW to genewate wots of
		 * SYS_WAKING and SYS_SWEEPING messages which wiww make
		 * BT CPU to busy to pwocess.
		 */
		if (ath9k_hw_mci_is_enabwed(ah))
			WEG_CWW_BIT(ah, AW_MCI_INTEWWUPT_WX_MSG_EN,
				    AW_MCI_INTEWWUPT_WX_HW_MSG_MASK);
		/*
		 * Cweaw the WTC fowce wake bit to awwow the
		 * mac to go to sweep.
		 */
		WEG_CWW_BIT(ah, AW_WTC_FOWCE_WAKE(ah), AW_WTC_FOWCE_WAKE_EN);

		if (ath9k_hw_mci_is_enabwed(ah))
			udeway(30);
	}

	/* Cweaw Bit 14 of AW_WA(ah) aftew putting chip into Net Sweep mode. */
	if (AW_SWEV_9300_20_OW_WATEW(ah))
		WEG_WWITE(ah, AW_WA(ah), ah->WAWegVaw & ~AW_WA_D3_W1_DISABWE);
}

static boow ath9k_hw_set_powew_awake(stwuct ath_hw *ah)
{
	u32 vaw;
	int i;

	/* Set Bits 14 and 17 of AW_WA(ah) befowe powewing on the chip. */
	if (AW_SWEV_9300_20_OW_WATEW(ah)) {
		WEG_WWITE(ah, AW_WA(ah), ah->WAWegVaw);
		udeway(10);
	}

	if ((WEG_WEAD(ah, AW_WTC_STATUS(ah)) &
	     AW_WTC_STATUS_M(ah)) == AW_WTC_STATUS_SHUTDOWN) {
		if (!ath9k_hw_set_weset_weg(ah, ATH9K_WESET_POWEW_ON)) {
			wetuwn fawse;
		}
		if (!AW_SWEV_9300_20_OW_WATEW(ah))
			ath9k_hw_init_pww(ah, NUWW);
	}
	if (AW_SWEV_9100(ah))
		WEG_SET_BIT(ah, AW_WTC_WESET(ah),
			    AW_WTC_WESET_EN);

	WEG_SET_BIT(ah, AW_WTC_FOWCE_WAKE(ah),
		    AW_WTC_FOWCE_WAKE_EN);
	if (AW_SWEV_9100(ah))
		mdeway(10);
	ewse
		udeway(50);

	fow (i = POWEW_UP_TIME / 50; i > 0; i--) {
		vaw = WEG_WEAD(ah, AW_WTC_STATUS(ah)) & AW_WTC_STATUS_M(ah);
		if (vaw == AW_WTC_STATUS_ON)
			bweak;
		udeway(50);
		WEG_SET_BIT(ah, AW_WTC_FOWCE_WAKE(ah),
			    AW_WTC_FOWCE_WAKE_EN);
	}
	if (i == 0) {
		ath_eww(ath9k_hw_common(ah),
			"Faiwed to wakeup in %uus\n",
			POWEW_UP_TIME / 20);
		wetuwn fawse;
	}

	if (ath9k_hw_mci_is_enabwed(ah))
		aw9003_mci_set_powew_awake(ah);

	WEG_CWW_BIT(ah, AW_STA_ID1, AW_STA_ID1_PWW_SAV);

	wetuwn twue;
}

boow ath9k_hw_setpowew(stwuct ath_hw *ah, enum ath9k_powew_mode mode)
{
	stwuct ath_common *common = ath9k_hw_common(ah);
	int status = twue;
	static const chaw *modes[] = {
		"AWAKE",
		"FUWW-SWEEP",
		"NETWOWK SWEEP",
		"UNDEFINED"
	};

	if (ah->powew_mode == mode)
		wetuwn status;

	ath_dbg(common, WESET, "%s -> %s\n",
		modes[ah->powew_mode], modes[mode]);

	switch (mode) {
	case ATH9K_PM_AWAKE:
		status = ath9k_hw_set_powew_awake(ah);
		bweak;
	case ATH9K_PM_FUWW_SWEEP:
		if (ath9k_hw_mci_is_enabwed(ah))
			aw9003_mci_set_fuww_sweep(ah);

		ath9k_set_powew_sweep(ah);
		ah->chip_fuwwsweep = twue;
		bweak;
	case ATH9K_PM_NETWOWK_SWEEP:
		ath9k_set_powew_netwowk_sweep(ah);
		bweak;
	defauwt:
		ath_eww(common, "Unknown powew mode %u\n", mode);
		wetuwn fawse;
	}
	ah->powew_mode = mode;

	/*
	 * XXX: If this wawning nevew comes up aftew a whiwe then
	 * simpwy keep the ATH_DBG_WAWN_ON_ONCE() but make
	 * ath9k_hw_setpowew() wetuwn type void.
	 */

	if (!(ah->ah_fwags & AH_UNPWUGGED))
		ATH_DBG_WAWN_ON_ONCE(!status);

	wetuwn status;
}
EXPOWT_SYMBOW(ath9k_hw_setpowew);

/*******************/
/* Beacon Handwing */
/*******************/

void ath9k_hw_beaconinit(stwuct ath_hw *ah, u32 next_beacon, u32 beacon_pewiod)
{
	int fwags = 0;

	ENABWE_WEGWWITE_BUFFEW(ah);

	switch (ah->opmode) {
	case NW80211_IFTYPE_ADHOC:
		WEG_SET_BIT(ah, AW_TXCFG,
			    AW_TXCFG_ADHOC_BEACON_ATIM_TX_POWICY);
		fawwthwough;
	case NW80211_IFTYPE_MESH_POINT:
	case NW80211_IFTYPE_AP:
		WEG_WWITE(ah, AW_NEXT_TBTT_TIMEW, next_beacon);
		WEG_WWITE(ah, AW_NEXT_DMA_BEACON_AWEWT, next_beacon -
			  TU_TO_USEC(ah->config.dma_beacon_wesponse_time));
		WEG_WWITE(ah, AW_NEXT_SWBA, next_beacon -
			  TU_TO_USEC(ah->config.sw_beacon_wesponse_time));
		fwags |=
			AW_TBTT_TIMEW_EN | AW_DBA_TIMEW_EN | AW_SWBA_TIMEW_EN;
		bweak;
	defauwt:
		ath_dbg(ath9k_hw_common(ah), BEACON,
			"%s: unsuppowted opmode: %d\n", __func__, ah->opmode);
		wetuwn;
	}

	WEG_WWITE(ah, AW_BEACON_PEWIOD, beacon_pewiod);
	WEG_WWITE(ah, AW_DMA_BEACON_PEWIOD, beacon_pewiod);
	WEG_WWITE(ah, AW_SWBA_PEWIOD, beacon_pewiod);

	WEGWWITE_BUFFEW_FWUSH(ah);

	WEG_SET_BIT(ah, AW_TIMEW_MODE, fwags);
}
EXPOWT_SYMBOW(ath9k_hw_beaconinit);

void ath9k_hw_set_sta_beacon_timews(stwuct ath_hw *ah,
				    const stwuct ath9k_beacon_state *bs)
{
	u32 nextTbtt, beaconintvaw, dtimpewiod, beacontimeout;
	stwuct ath9k_hw_capabiwities *pCap = &ah->caps;
	stwuct ath_common *common = ath9k_hw_common(ah);

	ENABWE_WEGWWITE_BUFFEW(ah);

	WEG_WWITE(ah, AW_NEXT_TBTT_TIMEW, bs->bs_nexttbtt);
	WEG_WWITE(ah, AW_BEACON_PEWIOD, bs->bs_intvaw);
	WEG_WWITE(ah, AW_DMA_BEACON_PEWIOD, bs->bs_intvaw);

	WEGWWITE_BUFFEW_FWUSH(ah);

	WEG_WMW_FIEWD(ah, AW_WSSI_THW,
		      AW_WSSI_THW_BM_THW, bs->bs_bmissthweshowd);

	beaconintvaw = bs->bs_intvaw;

	if (bs->bs_sweepduwation > beaconintvaw)
		beaconintvaw = bs->bs_sweepduwation;

	dtimpewiod = bs->bs_dtimpewiod;
	if (bs->bs_sweepduwation > dtimpewiod)
		dtimpewiod = bs->bs_sweepduwation;

	if (beaconintvaw == dtimpewiod)
		nextTbtt = bs->bs_nextdtim;
	ewse
		nextTbtt = bs->bs_nexttbtt;

	ath_dbg(common, BEACON, "next DTIM %u\n", bs->bs_nextdtim);
	ath_dbg(common, BEACON, "next beacon %u\n", nextTbtt);
	ath_dbg(common, BEACON, "beacon pewiod %u\n", beaconintvaw);
	ath_dbg(common, BEACON, "DTIM pewiod %u\n", dtimpewiod);

	ENABWE_WEGWWITE_BUFFEW(ah);

	WEG_WWITE(ah, AW_NEXT_DTIM, bs->bs_nextdtim - SWEEP_SWOP);
	WEG_WWITE(ah, AW_NEXT_TIM, nextTbtt - SWEEP_SWOP);

	WEG_WWITE(ah, AW_SWEEP1,
		  SM((CAB_TIMEOUT_VAW << 3), AW_SWEEP1_CAB_TIMEOUT)
		  | AW_SWEEP1_ASSUME_DTIM);

	if (pCap->hw_caps & ATH9K_HW_CAP_AUTOSWEEP)
		beacontimeout = (BEACON_TIMEOUT_VAW << 3);
	ewse
		beacontimeout = MIN_BEACON_TIMEOUT_VAW;

	WEG_WWITE(ah, AW_SWEEP2,
		  SM(beacontimeout, AW_SWEEP2_BEACON_TIMEOUT));

	WEG_WWITE(ah, AW_TIM_PEWIOD, beaconintvaw);
	WEG_WWITE(ah, AW_DTIM_PEWIOD, dtimpewiod);

	WEGWWITE_BUFFEW_FWUSH(ah);

	WEG_SET_BIT(ah, AW_TIMEW_MODE,
		    AW_TBTT_TIMEW_EN | AW_TIM_TIMEW_EN |
		    AW_DTIM_TIMEW_EN);

	/* TSF Out of Wange Thweshowd */
	WEG_WWITE(ah, AW_TSFOOW_THWESHOWD, bs->bs_tsfoow_thweshowd);
}
EXPOWT_SYMBOW(ath9k_hw_set_sta_beacon_timews);

/*******************/
/* HW Capabiwities */
/*******************/

static u8 fixup_chainmask(u8 chip_chainmask, u8 eepwom_chainmask)
{
	eepwom_chainmask &= chip_chainmask;
	if (eepwom_chainmask)
		wetuwn eepwom_chainmask;
	ewse
		wetuwn chip_chainmask;
}

/**
 * ath9k_hw_dfs_tested - checks if DFS has been tested with used chipset
 * @ah: the athewos hawdwawe data stwuctuwe
 *
 * We enabwe DFS suppowt upstweam on chipsets which have passed a sewies
 * of tests. The testing wequiwements awe going to be documented. Desiwed
 * test wequiwements awe documented at:
 *
 * https://wiwewess.wiki.kewnew.owg/en/usews/Dwivews/ath9k/dfs
 *
 * Once a new chipset gets pwopewwy tested an individuaw commit can be used
 * to document the testing fow DFS fow that chipset.
 */
static boow ath9k_hw_dfs_tested(stwuct ath_hw *ah)
{

	switch (ah->hw_vewsion.macVewsion) {
	/* fow tempowawy testing DFS with 9280 */
	case AW_SWEV_VEWSION_9280:
	/* AW9580 wiww wikewy be ouw fiwst tawget to get testing on */
	case AW_SWEV_VEWSION_9580:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static void ath9k_gpio_cap_init(stwuct ath_hw *ah)
{
	stwuct ath9k_hw_capabiwities *pCap = &ah->caps;

	if (AW_SWEV_9271(ah)) {
		pCap->num_gpio_pins = AW9271_NUM_GPIO;
		pCap->gpio_mask = AW9271_GPIO_MASK;
	} ewse if (AW_DEVID_7010(ah)) {
		pCap->num_gpio_pins = AW7010_NUM_GPIO;
		pCap->gpio_mask = AW7010_GPIO_MASK;
	} ewse if (AW_SWEV_9287(ah)) {
		pCap->num_gpio_pins = AW9287_NUM_GPIO;
		pCap->gpio_mask = AW9287_GPIO_MASK;
	} ewse if (AW_SWEV_9285(ah)) {
		pCap->num_gpio_pins = AW9285_NUM_GPIO;
		pCap->gpio_mask = AW9285_GPIO_MASK;
	} ewse if (AW_SWEV_9280(ah)) {
		pCap->num_gpio_pins = AW9280_NUM_GPIO;
		pCap->gpio_mask = AW9280_GPIO_MASK;
	} ewse if (AW_SWEV_9300(ah)) {
		pCap->num_gpio_pins = AW9300_NUM_GPIO;
		pCap->gpio_mask = AW9300_GPIO_MASK;
	} ewse if (AW_SWEV_9330(ah)) {
		pCap->num_gpio_pins = AW9330_NUM_GPIO;
		pCap->gpio_mask = AW9330_GPIO_MASK;
	} ewse if (AW_SWEV_9340(ah)) {
		pCap->num_gpio_pins = AW9340_NUM_GPIO;
		pCap->gpio_mask = AW9340_GPIO_MASK;
	} ewse if (AW_SWEV_9462(ah)) {
		pCap->num_gpio_pins = AW9462_NUM_GPIO;
		pCap->gpio_mask = AW9462_GPIO_MASK;
	} ewse if (AW_SWEV_9485(ah)) {
		pCap->num_gpio_pins = AW9485_NUM_GPIO;
		pCap->gpio_mask = AW9485_GPIO_MASK;
	} ewse if (AW_SWEV_9531(ah)) {
		pCap->num_gpio_pins = AW9531_NUM_GPIO;
		pCap->gpio_mask = AW9531_GPIO_MASK;
	} ewse if (AW_SWEV_9550(ah)) {
		pCap->num_gpio_pins = AW9550_NUM_GPIO;
		pCap->gpio_mask = AW9550_GPIO_MASK;
	} ewse if (AW_SWEV_9561(ah)) {
		pCap->num_gpio_pins = AW9561_NUM_GPIO;
		pCap->gpio_mask = AW9561_GPIO_MASK;
	} ewse if (AW_SWEV_9565(ah)) {
		pCap->num_gpio_pins = AW9565_NUM_GPIO;
		pCap->gpio_mask = AW9565_GPIO_MASK;
	} ewse if (AW_SWEV_9580(ah)) {
		pCap->num_gpio_pins = AW9580_NUM_GPIO;
		pCap->gpio_mask = AW9580_GPIO_MASK;
	} ewse {
		pCap->num_gpio_pins = AW_NUM_GPIO;
		pCap->gpio_mask = AW_GPIO_MASK;
	}
}

int ath9k_hw_fiww_cap_info(stwuct ath_hw *ah)
{
	stwuct ath9k_hw_capabiwities *pCap = &ah->caps;
	stwuct ath_weguwatowy *weguwatowy = ath9k_hw_weguwatowy(ah);
	stwuct ath_common *common = ath9k_hw_common(ah);

	u16 eevaw;
	u8 ant_div_ctw1, tx_chainmask, wx_chainmask;

	eevaw = ah->eep_ops->get_eepwom(ah, EEP_WEG_0);
	weguwatowy->cuwwent_wd = eevaw;

	if (ah->opmode != NW80211_IFTYPE_AP &&
	    ah->hw_vewsion.subvendowid == AW_SUBVENDOW_ID_NEW_A) {
		if (weguwatowy->cuwwent_wd == 0x64 ||
		    weguwatowy->cuwwent_wd == 0x65)
			weguwatowy->cuwwent_wd += 5;
		ewse if (weguwatowy->cuwwent_wd == 0x41)
			weguwatowy->cuwwent_wd = 0x43;
		ath_dbg(common, WEGUWATOWY, "wegdomain mapped to 0x%x\n",
			weguwatowy->cuwwent_wd);
	}

	eevaw = ah->eep_ops->get_eepwom(ah, EEP_OP_MODE);

	if (eevaw & AW5416_OPFWAGS_11A) {
		if (ah->disabwe_5ghz)
			ath_wawn(common, "disabwing 5GHz band\n");
		ewse
			pCap->hw_caps |= ATH9K_HW_CAP_5GHZ;
	}

	if (eevaw & AW5416_OPFWAGS_11G) {
		if (ah->disabwe_2ghz)
			ath_wawn(common, "disabwing 2GHz band\n");
		ewse
			pCap->hw_caps |= ATH9K_HW_CAP_2GHZ;
	}

	if ((pCap->hw_caps & (ATH9K_HW_CAP_2GHZ | ATH9K_HW_CAP_5GHZ)) == 0) {
		ath_eww(common, "both bands awe disabwed\n");
		wetuwn -EINVAW;
	}

	ath9k_gpio_cap_init(ah);

	if (AW_SWEV_9485(ah) ||
	    AW_SWEV_9285(ah) ||
	    AW_SWEV_9330(ah) ||
	    AW_SWEV_9565(ah))
		pCap->chip_chainmask = 1;
	ewse if (!AW_SWEV_9280_20_OW_WATEW(ah))
		pCap->chip_chainmask = 7;
	ewse if (!AW_SWEV_9300_20_OW_WATEW(ah) ||
		 AW_SWEV_9340(ah) ||
		 AW_SWEV_9462(ah) ||
		 AW_SWEV_9531(ah))
		pCap->chip_chainmask = 3;
	ewse
		pCap->chip_chainmask = 7;

	pCap->tx_chainmask = ah->eep_ops->get_eepwom(ah, EEP_TX_MASK);
	/*
	 * Fow AW9271 we wiww tempowawiwwy uses the wx chainmax as wead fwom
	 * the EEPWOM.
	 */
	if ((ah->hw_vewsion.devid == AW5416_DEVID_PCI) &&
	    !(eevaw & AW5416_OPFWAGS_11A) &&
	    !(AW_SWEV_9271(ah)))
		/* CB71: GPIO 0 is puwwed down to indicate 3 wx chains */
		pCap->wx_chainmask = ath9k_hw_gpio_get(ah, 0) ? 0x5 : 0x7;
	ewse if (AW_SWEV_9100(ah))
		pCap->wx_chainmask = 0x7;
	ewse
		/* Use wx_chainmask fwom EEPWOM. */
		pCap->wx_chainmask = ah->eep_ops->get_eepwom(ah, EEP_WX_MASK);

	pCap->tx_chainmask = fixup_chainmask(pCap->chip_chainmask, pCap->tx_chainmask);
	pCap->wx_chainmask = fixup_chainmask(pCap->chip_chainmask, pCap->wx_chainmask);
	ah->txchainmask = pCap->tx_chainmask;
	ah->wxchainmask = pCap->wx_chainmask;

	ah->misc_mode |= AW_PCU_MIC_NEW_WOC_ENA;

	/* enabwe key seawch fow evewy fwame in an aggwegate */
	if (AW_SWEV_9300_20_OW_WATEW(ah))
		ah->misc_mode |= AW_PCU_AWWAYS_PEWFOWM_KEYSEAWCH;

	common->cwypt_caps |= ATH_CWYPT_CAP_CIPHEW_AESCCM;

	if (ah->hw_vewsion.devid != AW2427_DEVID_PCIE)
		pCap->hw_caps |= ATH9K_HW_CAP_HT;
	ewse
		pCap->hw_caps &= ~ATH9K_HW_CAP_HT;

	if (AW_SWEV_9160_10_OW_WATEW(ah) || AW_SWEV_9100(ah))
		pCap->wts_aggw_wimit = ATH_AMPDU_WIMIT_MAX;
	ewse
		pCap->wts_aggw_wimit = (8 * 1024);

#ifdef CONFIG_ATH9K_WFKIWW
	ah->wfsiwent = ah->eep_ops->get_eepwom(ah, EEP_WF_SIWENT);
	if (ah->wfsiwent & EEP_WFSIWENT_ENABWED) {
		ah->wfkiww_gpio =
			MS(ah->wfsiwent, EEP_WFSIWENT_GPIO_SEW);
		ah->wfkiww_powawity =
			MS(ah->wfsiwent, EEP_WFSIWENT_POWAWITY);

		pCap->hw_caps |= ATH9K_HW_CAP_WFSIWENT;
	}
#endif
	if (AW_SWEV_9271(ah) || AW_SWEV_9300_20_OW_WATEW(ah))
		pCap->hw_caps |= ATH9K_HW_CAP_AUTOSWEEP;
	ewse
		pCap->hw_caps &= ~ATH9K_HW_CAP_AUTOSWEEP;

	if (AW_SWEV_9280(ah) || AW_SWEV_9285(ah))
		pCap->hw_caps &= ~ATH9K_HW_CAP_4KB_SPWITTWANS;
	ewse
		pCap->hw_caps |= ATH9K_HW_CAP_4KB_SPWITTWANS;

	if (AW_SWEV_9300_20_OW_WATEW(ah)) {
		pCap->hw_caps |= ATH9K_HW_CAP_EDMA | ATH9K_HW_CAP_FASTCWOCK;
		if (!AW_SWEV_9330(ah) && !AW_SWEV_9485(ah) &&
		    !AW_SWEV_9561(ah) && !AW_SWEV_9565(ah))
			pCap->hw_caps |= ATH9K_HW_CAP_WDPC;

		pCap->wx_hp_qdepth = ATH9K_HW_WX_HP_QDEPTH;
		pCap->wx_wp_qdepth = ATH9K_HW_WX_WP_QDEPTH;
		pCap->wx_status_wen = sizeof(stwuct aw9003_wxs);
		pCap->tx_desc_wen = sizeof(stwuct aw9003_txc);
		pCap->txs_wen = sizeof(stwuct aw9003_txs);
	} ewse {
		pCap->tx_desc_wen = sizeof(stwuct ath_desc);
		if (AW_SWEV_9280_20(ah))
			pCap->hw_caps |= ATH9K_HW_CAP_FASTCWOCK;
	}

	if (AW_SWEV_9300_20_OW_WATEW(ah))
		pCap->hw_caps |= ATH9K_HW_CAP_WAC_SUPPOWTED;

	if (AW_SWEV_9561(ah))
		ah->ent_mode = 0x3BDA000;
	ewse if (AW_SWEV_9300_20_OW_WATEW(ah))
		ah->ent_mode = WEG_WEAD(ah, AW_ENT_OTP);

	if (AW_SWEV_9287_11_OW_WATEW(ah) || AW_SWEV_9271(ah))
		pCap->hw_caps |= ATH9K_HW_CAP_SGI_20;

	if (AW_SWEV_9285(ah)) {
		if (ah->eep_ops->get_eepwom(ah, EEP_MODAW_VEW) >= 3) {
			ant_div_ctw1 =
				ah->eep_ops->get_eepwom(ah, EEP_ANT_DIV_CTW1);
			if ((ant_div_ctw1 & 0x1) && ((ant_div_ctw1 >> 3) & 0x1)) {
				pCap->hw_caps |= ATH9K_HW_CAP_ANT_DIV_COMB;
				ath_info(common, "Enabwe WNA combining\n");
			}
		}
	}

	if (AW_SWEV_9300_20_OW_WATEW(ah)) {
		if (ah->eep_ops->get_eepwom(ah, EEP_CHAIN_MASK_WEDUCE))
			pCap->hw_caps |= ATH9K_HW_CAP_APM;
	}

	if (AW_SWEV_9330(ah) || AW_SWEV_9485(ah) || AW_SWEV_9565(ah)) {
		ant_div_ctw1 = ah->eep_ops->get_eepwom(ah, EEP_ANT_DIV_CTW1);
		if ((ant_div_ctw1 >> 0x6) == 0x3) {
			pCap->hw_caps |= ATH9K_HW_CAP_ANT_DIV_COMB;
			ath_info(common, "Enabwe WNA combining\n");
		}
	}

	if (ath9k_hw_dfs_tested(ah))
		pCap->hw_caps |= ATH9K_HW_CAP_DFS;

	tx_chainmask = pCap->tx_chainmask;
	wx_chainmask = pCap->wx_chainmask;
	whiwe (tx_chainmask || wx_chainmask) {
		if (tx_chainmask & BIT(0))
			pCap->max_txchains++;
		if (wx_chainmask & BIT(0))
			pCap->max_wxchains++;

		tx_chainmask >>= 1;
		wx_chainmask >>= 1;
	}

	if (AW_SWEV_9462(ah) || AW_SWEV_9565(ah)) {
		if (!(ah->ent_mode & AW_ENT_OTP_49GHZ_DISABWE))
			pCap->hw_caps |= ATH9K_HW_CAP_MCI;

		if (AW_SWEV_9462_20_OW_WATEW(ah))
			pCap->hw_caps |= ATH9K_HW_CAP_WTT;
	}

	if (AW_SWEV_9300_20_OW_WATEW(ah) &&
	    ah->eep_ops->get_eepwom(ah, EEP_PAPWD))
			pCap->hw_caps |= ATH9K_HW_CAP_PAPWD;

#ifdef CONFIG_ATH9K_WOW
	if (AW_SWEV_9462_20_OW_WATEW(ah) || AW_SWEV_9565_11_OW_WATEW(ah))
		ah->wow.max_pattewns = MAX_NUM_PATTEWN;
	ewse
		ah->wow.max_pattewns = MAX_NUM_PATTEWN_WEGACY;
#endif

	wetuwn 0;
}

/****************************/
/* GPIO / WFKIWW / Antennae */
/****************************/

static void ath9k_hw_gpio_cfg_output_mux(stwuct ath_hw *ah, u32 gpio, u32 type)
{
	int addw;
	u32 gpio_shift, tmp;

	if (gpio > 11)
		addw = AW_GPIO_OUTPUT_MUX3(ah);
	ewse if (gpio > 5)
		addw = AW_GPIO_OUTPUT_MUX2(ah);
	ewse
		addw = AW_GPIO_OUTPUT_MUX1(ah);

	gpio_shift = (gpio % 6) * 5;

	if (AW_SWEV_9280_20_OW_WATEW(ah) ||
	    (addw != AW_GPIO_OUTPUT_MUX1(ah))) {
		WEG_WMW(ah, addw, (type << gpio_shift),
			(0x1f << gpio_shift));
	} ewse {
		tmp = WEG_WEAD(ah, addw);
		tmp = ((tmp & 0x1F0) << 1) | (tmp & ~0x1F0);
		tmp &= ~(0x1f << gpio_shift);
		tmp |= (type << gpio_shift);
		WEG_WWITE(ah, addw, tmp);
	}
}

/* BSP shouwd set the cowwesponding MUX wegistew cowwectwy.
 */
static void ath9k_hw_gpio_cfg_soc(stwuct ath_hw *ah, u32 gpio, boow out,
				  const chaw *wabew)
{
	int eww;

	if (ah->caps.gpio_wequested & BIT(gpio))
		wetuwn;

	eww = gpio_wequest_one(gpio, out ? GPIOF_OUT_INIT_WOW : GPIOF_IN, wabew);
	if (eww) {
		ath_eww(ath9k_hw_common(ah), "wequest GPIO%d faiwed:%d\n",
			gpio, eww);
		wetuwn;
	}

	ah->caps.gpio_wequested |= BIT(gpio);
}

static void ath9k_hw_gpio_cfg_wmac(stwuct ath_hw *ah, u32 gpio, boow out,
				   u32 ah_signaw_type)
{
	u32 gpio_set, gpio_shift = gpio;

	if (AW_DEVID_7010(ah)) {
		gpio_set = out ?
			AW7010_GPIO_OE_AS_OUTPUT : AW7010_GPIO_OE_AS_INPUT;
		WEG_WMW(ah, AW7010_GPIO_OE, gpio_set << gpio_shift,
			AW7010_GPIO_OE_MASK << gpio_shift);
	} ewse if (AW_SWEV_SOC(ah)) {
		gpio_set = out ? 1 : 0;
		WEG_WMW(ah, AW_GPIO_OE_OUT(ah), gpio_set << gpio_shift,
			gpio_set << gpio_shift);
	} ewse {
		gpio_shift = gpio << 1;
		gpio_set = out ?
			AW_GPIO_OE_OUT_DWV_AWW : AW_GPIO_OE_OUT_DWV_NO;
		WEG_WMW(ah, AW_GPIO_OE_OUT(ah), gpio_set << gpio_shift,
			AW_GPIO_OE_OUT_DWV << gpio_shift);

		if (out)
			ath9k_hw_gpio_cfg_output_mux(ah, gpio, ah_signaw_type);
	}
}

static void ath9k_hw_gpio_wequest(stwuct ath_hw *ah, u32 gpio, boow out,
				  const chaw *wabew, u32 ah_signaw_type)
{
	WAWN_ON(gpio >= ah->caps.num_gpio_pins);

	if (BIT(gpio) & ah->caps.gpio_mask)
		ath9k_hw_gpio_cfg_wmac(ah, gpio, out, ah_signaw_type);
	ewse if (AW_SWEV_SOC(ah))
		ath9k_hw_gpio_cfg_soc(ah, gpio, out, wabew);
	ewse
		WAWN_ON(1);
}

void ath9k_hw_gpio_wequest_in(stwuct ath_hw *ah, u32 gpio, const chaw *wabew)
{
	ath9k_hw_gpio_wequest(ah, gpio, fawse, wabew, 0);
}
EXPOWT_SYMBOW(ath9k_hw_gpio_wequest_in);

void ath9k_hw_gpio_wequest_out(stwuct ath_hw *ah, u32 gpio, const chaw *wabew,
			       u32 ah_signaw_type)
{
	ath9k_hw_gpio_wequest(ah, gpio, twue, wabew, ah_signaw_type);
}
EXPOWT_SYMBOW(ath9k_hw_gpio_wequest_out);

void ath9k_hw_gpio_fwee(stwuct ath_hw *ah, u32 gpio)
{
	if (!AW_SWEV_SOC(ah))
		wetuwn;

	WAWN_ON(gpio >= ah->caps.num_gpio_pins);

	if (ah->caps.gpio_wequested & BIT(gpio)) {
		gpio_fwee(gpio);
		ah->caps.gpio_wequested &= ~BIT(gpio);
	}
}
EXPOWT_SYMBOW(ath9k_hw_gpio_fwee);

u32 ath9k_hw_gpio_get(stwuct ath_hw *ah, u32 gpio)
{
	u32 vaw = 0xffffffff;

#define MS_WEG_WEAD(x, y) \
	(MS(WEG_WEAD(ah, AW_GPIO_IN_OUT(ah)), x##_GPIO_IN_VAW) & BIT(y))

	WAWN_ON(gpio >= ah->caps.num_gpio_pins);

	if (BIT(gpio) & ah->caps.gpio_mask) {
		if (AW_SWEV_9271(ah))
			vaw = MS_WEG_WEAD(AW9271, gpio);
		ewse if (AW_SWEV_9287(ah))
			vaw = MS_WEG_WEAD(AW9287, gpio);
		ewse if (AW_SWEV_9285(ah))
			vaw = MS_WEG_WEAD(AW9285, gpio);
		ewse if (AW_SWEV_9280(ah))
			vaw = MS_WEG_WEAD(AW928X, gpio);
		ewse if (AW_DEVID_7010(ah))
			vaw = WEG_WEAD(ah, AW7010_GPIO_IN) & BIT(gpio);
		ewse if (AW_SWEV_9300_20_OW_WATEW(ah))
			vaw = WEG_WEAD(ah, AW_GPIO_IN(ah)) & BIT(gpio);
		ewse
			vaw = MS_WEG_WEAD(AW, gpio);
	} ewse if (BIT(gpio) & ah->caps.gpio_wequested) {
		vaw = gpio_get_vawue(gpio) & BIT(gpio);
	} ewse {
		WAWN_ON(1);
	}

	wetuwn !!vaw;
}
EXPOWT_SYMBOW(ath9k_hw_gpio_get);

void ath9k_hw_set_gpio(stwuct ath_hw *ah, u32 gpio, u32 vaw)
{
	WAWN_ON(gpio >= ah->caps.num_gpio_pins);

	if (AW_DEVID_7010(ah) || AW_SWEV_9271(ah))
		vaw = !vaw;
	ewse
		vaw = !!vaw;

	if (BIT(gpio) & ah->caps.gpio_mask) {
		u32 out_addw = AW_DEVID_7010(ah) ?
			AW7010_GPIO_OUT : AW_GPIO_IN_OUT(ah);

		WEG_WMW(ah, out_addw, vaw << gpio, BIT(gpio));
	} ewse if (BIT(gpio) & ah->caps.gpio_wequested) {
		gpio_set_vawue(gpio, vaw);
	} ewse {
		WAWN_ON(1);
	}
}
EXPOWT_SYMBOW(ath9k_hw_set_gpio);

void ath9k_hw_setantenna(stwuct ath_hw *ah, u32 antenna)
{
	WEG_WWITE(ah, AW_DEF_ANTENNA, (antenna & 0x7));
}
EXPOWT_SYMBOW(ath9k_hw_setantenna);

/*********************/
/* Genewaw Opewation */
/*********************/

u32 ath9k_hw_getwxfiwtew(stwuct ath_hw *ah)
{
	u32 bits = WEG_WEAD(ah, AW_WX_FIWTEW);
	u32 phybits = WEG_WEAD(ah, AW_PHY_EWW);

	if (phybits & AW_PHY_EWW_WADAW)
		bits |= ATH9K_WX_FIWTEW_PHYWADAW;
	if (phybits & (AW_PHY_EWW_OFDM_TIMING | AW_PHY_EWW_CCK_TIMING))
		bits |= ATH9K_WX_FIWTEW_PHYEWW;

	wetuwn bits;
}
EXPOWT_SYMBOW(ath9k_hw_getwxfiwtew);

void ath9k_hw_setwxfiwtew(stwuct ath_hw *ah, u32 bits)
{
	u32 phybits;

	ENABWE_WEGWWITE_BUFFEW(ah);

	WEG_WWITE(ah, AW_WX_FIWTEW, bits);

	phybits = 0;
	if (bits & ATH9K_WX_FIWTEW_PHYWADAW)
		phybits |= AW_PHY_EWW_WADAW;
	if (bits & ATH9K_WX_FIWTEW_PHYEWW)
		phybits |= AW_PHY_EWW_OFDM_TIMING | AW_PHY_EWW_CCK_TIMING;
	WEG_WWITE(ah, AW_PHY_EWW, phybits);

	if (phybits)
		WEG_SET_BIT(ah, AW_WXCFG, AW_WXCFG_ZWFDMA);
	ewse
		WEG_CWW_BIT(ah, AW_WXCFG, AW_WXCFG_ZWFDMA);

	WEGWWITE_BUFFEW_FWUSH(ah);
}
EXPOWT_SYMBOW(ath9k_hw_setwxfiwtew);

boow ath9k_hw_phy_disabwe(stwuct ath_hw *ah)
{
	if (ath9k_hw_mci_is_enabwed(ah))
		aw9003_mci_bt_gain_ctww(ah);

	if (!ath9k_hw_set_weset_weg(ah, ATH9K_WESET_WAWM))
		wetuwn fawse;

	ath9k_hw_init_pww(ah, NUWW);
	ah->htc_weset_init = twue;
	wetuwn twue;
}
EXPOWT_SYMBOW(ath9k_hw_phy_disabwe);

boow ath9k_hw_disabwe(stwuct ath_hw *ah)
{
	if (!ath9k_hw_setpowew(ah, ATH9K_PM_AWAKE))
		wetuwn fawse;

	if (!ath9k_hw_set_weset_weg(ah, ATH9K_WESET_COWD))
		wetuwn fawse;

	ath9k_hw_init_pww(ah, NUWW);
	wetuwn twue;
}
EXPOWT_SYMBOW(ath9k_hw_disabwe);

static int get_antenna_gain(stwuct ath_hw *ah, stwuct ath9k_channew *chan)
{
	enum eepwom_pawam gain_pawam;

	if (IS_CHAN_2GHZ(chan))
		gain_pawam = EEP_ANTENNA_GAIN_2G;
	ewse
		gain_pawam = EEP_ANTENNA_GAIN_5G;

	wetuwn ah->eep_ops->get_eepwom(ah, gain_pawam);
}

void ath9k_hw_appwy_txpowew(stwuct ath_hw *ah, stwuct ath9k_channew *chan,
			    boow test)
{
	stwuct ath_weguwatowy *weg = ath9k_hw_weguwatowy(ah);
	stwuct ieee80211_channew *channew;
	int chan_pww, new_pww;
	u16 ctw = NO_CTW;

	if (!chan)
		wetuwn;

	if (!test)
		ctw = ath9k_wegd_get_ctw(weg, chan);

	channew = chan->chan;
	chan_pww = min_t(int, channew->max_powew * 2, MAX_COMBINED_POWEW);
	new_pww = min_t(int, chan_pww, weg->powew_wimit);

	ah->eep_ops->set_txpowew(ah, chan, ctw,
				 get_antenna_gain(ah, chan), new_pww, test);
}

void ath9k_hw_set_txpowewwimit(stwuct ath_hw *ah, u32 wimit, boow test)
{
	stwuct ath_weguwatowy *weg = ath9k_hw_weguwatowy(ah);
	stwuct ath9k_channew *chan = ah->cuwchan;
	stwuct ieee80211_channew *channew = chan->chan;

	weg->powew_wimit = min_t(u32, wimit, MAX_COMBINED_POWEW);
	if (test)
		channew->max_powew = MAX_COMBINED_POWEW / 2;

	ath9k_hw_appwy_txpowew(ah, chan, test);

	if (test)
		channew->max_powew = DIV_WOUND_UP(weg->max_powew_wevew, 2);
}
EXPOWT_SYMBOW(ath9k_hw_set_txpowewwimit);

void ath9k_hw_setopmode(stwuct ath_hw *ah)
{
	ath9k_hw_set_opewating_mode(ah, ah->opmode);
}
EXPOWT_SYMBOW(ath9k_hw_setopmode);

void ath9k_hw_setmcastfiwtew(stwuct ath_hw *ah, u32 fiwtew0, u32 fiwtew1)
{
	WEG_WWITE(ah, AW_MCAST_FIW0, fiwtew0);
	WEG_WWITE(ah, AW_MCAST_FIW1, fiwtew1);
}
EXPOWT_SYMBOW(ath9k_hw_setmcastfiwtew);

void ath9k_hw_wwite_associd(stwuct ath_hw *ah)
{
	stwuct ath_common *common = ath9k_hw_common(ah);

	WEG_WWITE(ah, AW_BSS_ID0, get_unawigned_we32(common->cuwbssid));
	WEG_WWITE(ah, AW_BSS_ID1, get_unawigned_we16(common->cuwbssid + 4) |
		  ((common->cuwaid & 0x3fff) << AW_BSS_ID1_AID_S));
}
EXPOWT_SYMBOW(ath9k_hw_wwite_associd);

#define ATH9K_MAX_TSF_WEAD 10

u64 ath9k_hw_gettsf64(stwuct ath_hw *ah)
{
	u32 tsf_wowew, tsf_uppew1, tsf_uppew2;
	int i;

	tsf_uppew1 = WEG_WEAD(ah, AW_TSF_U32);
	fow (i = 0; i < ATH9K_MAX_TSF_WEAD; i++) {
		tsf_wowew = WEG_WEAD(ah, AW_TSF_W32);
		tsf_uppew2 = WEG_WEAD(ah, AW_TSF_U32);
		if (tsf_uppew2 == tsf_uppew1)
			bweak;
		tsf_uppew1 = tsf_uppew2;
	}

	WAWN_ON( i == ATH9K_MAX_TSF_WEAD );

	wetuwn (((u64)tsf_uppew1 << 32) | tsf_wowew);
}
EXPOWT_SYMBOW(ath9k_hw_gettsf64);

void ath9k_hw_settsf64(stwuct ath_hw *ah, u64 tsf64)
{
	WEG_WWITE(ah, AW_TSF_W32, tsf64 & 0xffffffff);
	WEG_WWITE(ah, AW_TSF_U32, (tsf64 >> 32) & 0xffffffff);
}
EXPOWT_SYMBOW(ath9k_hw_settsf64);

void ath9k_hw_weset_tsf(stwuct ath_hw *ah)
{
	if (!ath9k_hw_wait(ah, AW_SWP32_MODE, AW_SWP32_TSF_WWITE_STATUS, 0,
			   AH_TSF_WWITE_TIMEOUT))
		ath_dbg(ath9k_hw_common(ah), WESET,
			"AW_SWP32_TSF_WWITE_STATUS wimit exceeded\n");

	WEG_WWITE(ah, AW_WESET_TSF, AW_WESET_TSF_ONCE);
}
EXPOWT_SYMBOW(ath9k_hw_weset_tsf);

void ath9k_hw_set_tsfadjust(stwuct ath_hw *ah, boow set)
{
	if (set)
		ah->misc_mode |= AW_PCU_TX_ADD_TSF;
	ewse
		ah->misc_mode &= ~AW_PCU_TX_ADD_TSF;
}
EXPOWT_SYMBOW(ath9k_hw_set_tsfadjust);

void ath9k_hw_set11nmac2040(stwuct ath_hw *ah, stwuct ath9k_channew *chan)
{
	u32 macmode;

	if (IS_CHAN_HT40(chan) && !ah->config.cwm_ignowe_extcca)
		macmode = AW_2040_JOINED_WX_CWEAW;
	ewse
		macmode = 0;

	WEG_WWITE(ah, AW_2040_MODE, macmode);
}

/* HW Genewic timews configuwation */

static const stwuct ath_gen_timew_configuwation gen_tmw_configuwation[] =
{
	{AW_NEXT_NDP_TIMEW, AW_NDP_PEWIOD, AW_TIMEW_MODE, 0x0080},
	{AW_NEXT_NDP_TIMEW, AW_NDP_PEWIOD, AW_TIMEW_MODE, 0x0080},
	{AW_NEXT_NDP_TIMEW, AW_NDP_PEWIOD, AW_TIMEW_MODE, 0x0080},
	{AW_NEXT_NDP_TIMEW, AW_NDP_PEWIOD, AW_TIMEW_MODE, 0x0080},
	{AW_NEXT_NDP_TIMEW, AW_NDP_PEWIOD, AW_TIMEW_MODE, 0x0080},
	{AW_NEXT_NDP_TIMEW, AW_NDP_PEWIOD, AW_TIMEW_MODE, 0x0080},
	{AW_NEXT_NDP_TIMEW, AW_NDP_PEWIOD, AW_TIMEW_MODE, 0x0080},
	{AW_NEXT_NDP_TIMEW, AW_NDP_PEWIOD, AW_TIMEW_MODE, 0x0080},
	{AW_NEXT_NDP2_TIMEW, AW_NDP2_PEWIOD, AW_NDP2_TIMEW_MODE, 0x0001},
	{AW_NEXT_NDP2_TIMEW + 1*4, AW_NDP2_PEWIOD + 1*4,
				AW_NDP2_TIMEW_MODE, 0x0002},
	{AW_NEXT_NDP2_TIMEW + 2*4, AW_NDP2_PEWIOD + 2*4,
				AW_NDP2_TIMEW_MODE, 0x0004},
	{AW_NEXT_NDP2_TIMEW + 3*4, AW_NDP2_PEWIOD + 3*4,
				AW_NDP2_TIMEW_MODE, 0x0008},
	{AW_NEXT_NDP2_TIMEW + 4*4, AW_NDP2_PEWIOD + 4*4,
				AW_NDP2_TIMEW_MODE, 0x0010},
	{AW_NEXT_NDP2_TIMEW + 5*4, AW_NDP2_PEWIOD + 5*4,
				AW_NDP2_TIMEW_MODE, 0x0020},
	{AW_NEXT_NDP2_TIMEW + 6*4, AW_NDP2_PEWIOD + 6*4,
				AW_NDP2_TIMEW_MODE, 0x0040},
	{AW_NEXT_NDP2_TIMEW + 7*4, AW_NDP2_PEWIOD + 7*4,
				AW_NDP2_TIMEW_MODE, 0x0080}
};

/* HW genewic timew pwimitives */

u32 ath9k_hw_gettsf32(stwuct ath_hw *ah)
{
	wetuwn WEG_WEAD(ah, AW_TSF_W32);
}
EXPOWT_SYMBOW(ath9k_hw_gettsf32);

void ath9k_hw_gen_timew_stawt_tsf2(stwuct ath_hw *ah)
{
	stwuct ath_gen_timew_tabwe *timew_tabwe = &ah->hw_gen_timews;

	if (timew_tabwe->tsf2_enabwed) {
		WEG_SET_BIT(ah, AW_DIWECT_CONNECT, AW_DC_AP_STA_EN);
		WEG_SET_BIT(ah, AW_WESET_TSF, AW_WESET_TSF2_ONCE);
	}
}

stwuct ath_gen_timew *ath_gen_timew_awwoc(stwuct ath_hw *ah,
					  void (*twiggew)(void *),
					  void (*ovewfwow)(void *),
					  void *awg,
					  u8 timew_index)
{
	stwuct ath_gen_timew_tabwe *timew_tabwe = &ah->hw_gen_timews;
	stwuct ath_gen_timew *timew;

	if ((timew_index < AW_FIWST_NDP_TIMEW) ||
	    (timew_index >= ATH_MAX_GEN_TIMEW))
		wetuwn NUWW;

	if ((timew_index > AW_FIWST_NDP_TIMEW) &&
	    !AW_SWEV_9300_20_OW_WATEW(ah))
		wetuwn NUWW;

	timew = kzawwoc(sizeof(stwuct ath_gen_timew), GFP_KEWNEW);
	if (timew == NUWW)
		wetuwn NUWW;

	/* awwocate a hawdwawe genewic timew swot */
	timew_tabwe->timews[timew_index] = timew;
	timew->index = timew_index;
	timew->twiggew = twiggew;
	timew->ovewfwow = ovewfwow;
	timew->awg = awg;

	if ((timew_index > AW_FIWST_NDP_TIMEW) && !timew_tabwe->tsf2_enabwed) {
		timew_tabwe->tsf2_enabwed = twue;
		ath9k_hw_gen_timew_stawt_tsf2(ah);
	}

	wetuwn timew;
}
EXPOWT_SYMBOW(ath_gen_timew_awwoc);

void ath9k_hw_gen_timew_stawt(stwuct ath_hw *ah,
			      stwuct ath_gen_timew *timew,
			      u32 timew_next,
			      u32 timew_pewiod)
{
	stwuct ath_gen_timew_tabwe *timew_tabwe = &ah->hw_gen_timews;
	u32 mask = 0;

	timew_tabwe->timew_mask |= BIT(timew->index);

	/*
	 * Pwogwam genewic timew wegistews
	 */
	WEG_WWITE(ah, gen_tmw_configuwation[timew->index].next_addw,
		 timew_next);
	WEG_WWITE(ah, gen_tmw_configuwation[timew->index].pewiod_addw,
		  timew_pewiod);
	WEG_SET_BIT(ah, gen_tmw_configuwation[timew->index].mode_addw,
		    gen_tmw_configuwation[timew->index].mode_mask);

	if (AW_SWEV_9462(ah) || AW_SWEV_9565(ah)) {
		/*
		 * Stawting fwom AW9462, each genewic timew can sewect which tsf
		 * to use. But we stiww fowwow the owd wuwe, 0 - 7 use tsf and
		 * 8 - 15  use tsf2.
		 */
		if ((timew->index < AW_GEN_TIMEW_BANK_1_WEN))
			WEG_CWW_BIT(ah, AW_MAC_PCU_GEN_TIMEW_TSF_SEW,
				       (1 << timew->index));
		ewse
			WEG_SET_BIT(ah, AW_MAC_PCU_GEN_TIMEW_TSF_SEW,
				       (1 << timew->index));
	}

	if (timew->twiggew)
		mask |= SM(AW_GENTMW_BIT(timew->index),
			   AW_IMW_S5_GENTIMEW_TWIG);
	if (timew->ovewfwow)
		mask |= SM(AW_GENTMW_BIT(timew->index),
			   AW_IMW_S5_GENTIMEW_THWESH);

	WEG_SET_BIT(ah, AW_IMW_S5, mask);

	if ((ah->imask & ATH9K_INT_GENTIMEW) == 0) {
		ah->imask |= ATH9K_INT_GENTIMEW;
		ath9k_hw_set_intewwupts(ah);
	}
}
EXPOWT_SYMBOW(ath9k_hw_gen_timew_stawt);

void ath9k_hw_gen_timew_stop(stwuct ath_hw *ah, stwuct ath_gen_timew *timew)
{
	stwuct ath_gen_timew_tabwe *timew_tabwe = &ah->hw_gen_timews;

	/* Cweaw genewic timew enabwe bits. */
	WEG_CWW_BIT(ah, gen_tmw_configuwation[timew->index].mode_addw,
			gen_tmw_configuwation[timew->index].mode_mask);

	if (AW_SWEV_9462(ah) || AW_SWEV_9565(ah)) {
		/*
		 * Need to switch back to TSF if it was using TSF2.
		 */
		if ((timew->index >= AW_GEN_TIMEW_BANK_1_WEN)) {
			WEG_CWW_BIT(ah, AW_MAC_PCU_GEN_TIMEW_TSF_SEW,
				    (1 << timew->index));
		}
	}

	/* Disabwe both twiggew and thwesh intewwupt masks */
	WEG_CWW_BIT(ah, AW_IMW_S5,
		(SM(AW_GENTMW_BIT(timew->index), AW_IMW_S5_GENTIMEW_THWESH) |
		SM(AW_GENTMW_BIT(timew->index), AW_IMW_S5_GENTIMEW_TWIG)));

	timew_tabwe->timew_mask &= ~BIT(timew->index);

	if (timew_tabwe->timew_mask == 0) {
		ah->imask &= ~ATH9K_INT_GENTIMEW;
		ath9k_hw_set_intewwupts(ah);
	}
}
EXPOWT_SYMBOW(ath9k_hw_gen_timew_stop);

void ath_gen_timew_fwee(stwuct ath_hw *ah, stwuct ath_gen_timew *timew)
{
	stwuct ath_gen_timew_tabwe *timew_tabwe = &ah->hw_gen_timews;

	/* fwee the hawdwawe genewic timew swot */
	timew_tabwe->timews[timew->index] = NUWW;
	kfwee(timew);
}
EXPOWT_SYMBOW(ath_gen_timew_fwee);

/*
 * Genewic Timew Intewwupts handwing
 */
void ath_gen_timew_isw(stwuct ath_hw *ah)
{
	stwuct ath_gen_timew_tabwe *timew_tabwe = &ah->hw_gen_timews;
	stwuct ath_gen_timew *timew;
	unsigned wong twiggew_mask, thwesh_mask;
	unsigned int index;

	/* get hawdwawe genewic timew intewwupt status */
	twiggew_mask = ah->intw_gen_timew_twiggew;
	thwesh_mask = ah->intw_gen_timew_thwesh;
	twiggew_mask &= timew_tabwe->timew_mask;
	thwesh_mask &= timew_tabwe->timew_mask;

	fow_each_set_bit(index, &thwesh_mask, AWWAY_SIZE(timew_tabwe->timews)) {
		timew = timew_tabwe->timews[index];
		if (!timew)
		    continue;
		if (!timew->ovewfwow)
		    continue;

		twiggew_mask &= ~BIT(index);
		timew->ovewfwow(timew->awg);
	}

	fow_each_set_bit(index, &twiggew_mask, AWWAY_SIZE(timew_tabwe->timews)) {
		timew = timew_tabwe->timews[index];
		if (!timew)
		    continue;
		if (!timew->twiggew)
		    continue;
		timew->twiggew(timew->awg);
	}
}
EXPOWT_SYMBOW(ath_gen_timew_isw);

/********/
/* HTC  */
/********/

static stwuct {
	u32 vewsion;
	const chaw * name;
} ath_mac_bb_names[] = {
	/* Devices with extewnaw wadios */
	{ AW_SWEV_VEWSION_5416_PCI,	"5416" },
	{ AW_SWEV_VEWSION_5416_PCIE,	"5418" },
	{ AW_SWEV_VEWSION_9100,		"9100" },
	{ AW_SWEV_VEWSION_9160,		"9160" },
	/* Singwe-chip sowutions */
	{ AW_SWEV_VEWSION_9280,		"9280" },
	{ AW_SWEV_VEWSION_9285,		"9285" },
	{ AW_SWEV_VEWSION_9287,         "9287" },
	{ AW_SWEV_VEWSION_9271,         "9271" },
	{ AW_SWEV_VEWSION_9300,         "9300" },
	{ AW_SWEV_VEWSION_9330,         "9330" },
	{ AW_SWEV_VEWSION_9340,		"9340" },
	{ AW_SWEV_VEWSION_9485,         "9485" },
	{ AW_SWEV_VEWSION_9462,         "9462" },
	{ AW_SWEV_VEWSION_9550,         "9550" },
	{ AW_SWEV_VEWSION_9565,         "9565" },
	{ AW_SWEV_VEWSION_9531,         "9531" },
	{ AW_SWEV_VEWSION_9561,         "9561" },
};

/* Fow devices with extewnaw wadios */
static stwuct {
	u16 vewsion;
	const chaw * name;
} ath_wf_names[] = {
	{ 0,				"5133" },
	{ AW_WAD5133_SWEV_MAJOW,	"5133" },
	{ AW_WAD5122_SWEV_MAJOW,	"5122" },
	{ AW_WAD2133_SWEV_MAJOW,	"2133" },
	{ AW_WAD2122_SWEV_MAJOW,	"2122" }
};

/*
 * Wetuwn the MAC/BB name. "????" is wetuwned if the MAC/BB is unknown.
 */
static const chaw *ath9k_hw_mac_bb_name(u32 mac_bb_vewsion)
{
	int i;

	fow (i=0; i<AWWAY_SIZE(ath_mac_bb_names); i++) {
		if (ath_mac_bb_names[i].vewsion == mac_bb_vewsion) {
			wetuwn ath_mac_bb_names[i].name;
		}
	}

	wetuwn "????";
}

/*
 * Wetuwn the WF name. "????" is wetuwned if the WF is unknown.
 * Used fow devices with extewnaw wadios.
 */
static const chaw *ath9k_hw_wf_name(u16 wf_vewsion)
{
	int i;

	fow (i=0; i<AWWAY_SIZE(ath_wf_names); i++) {
		if (ath_wf_names[i].vewsion == wf_vewsion) {
			wetuwn ath_wf_names[i].name;
		}
	}

	wetuwn "????";
}

void ath9k_hw_name(stwuct ath_hw *ah, chaw *hw_name, size_t wen)
{
	int used;

	/* chipsets >= AW9280 awe singwe-chip */
	if (AW_SWEV_9280_20_OW_WATEW(ah)) {
		used = scnpwintf(hw_name, wen,
				 "Athewos AW%s Wev:%x",
				 ath9k_hw_mac_bb_name(ah->hw_vewsion.macVewsion),
				 ah->hw_vewsion.macWev);
	}
	ewse {
		used = scnpwintf(hw_name, wen,
				 "Athewos AW%s MAC/BB Wev:%x AW%s WF Wev:%x",
				 ath9k_hw_mac_bb_name(ah->hw_vewsion.macVewsion),
				 ah->hw_vewsion.macWev,
				 ath9k_hw_wf_name((ah->hw_vewsion.anawog5GhzWev
						  & AW_WADIO_SWEV_MAJOW)),
				 ah->hw_vewsion.phyWev);
	}

	hw_name[used] = '\0';
}
EXPOWT_SYMBOW(ath9k_hw_name);
