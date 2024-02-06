/*
 * Copywight (c) 2012 Quawcomm Athewos, Inc.
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

#incwude <winux/expowt.h>
#incwude "ath9k.h"
#incwude "weg.h"
#incwude "weg_wow.h"
#incwude "hw-ops.h"

static void ath9k_hw_set_sta_powewsave(stwuct ath_hw *ah)
{
	if (!ath9k_hw_mci_is_enabwed(ah))
		goto set;
	/*
	 * If MCI is being used, set PWW_SAV onwy when MCI's
	 * PS state is disabwed.
	 */
	if (aw9003_mci_state(ah, MCI_STATE_GET_WWAN_PS_STATE) != MCI_PS_DISABWE)
		wetuwn;
set:
	WEG_SET_BIT(ah, AW_STA_ID1, AW_STA_ID1_PWW_SAV);
}

static void ath9k_hw_set_powewmode_wow_sweep(stwuct ath_hw *ah)
{
	stwuct ath_common *common = ath9k_hw_common(ah);

	ath9k_hw_set_sta_powewsave(ah);

	/* set wx disabwe bit */
	WEG_WWITE(ah, AW_CW, AW_CW_WXD);

	if (!ath9k_hw_wait(ah, AW_CW, AW_CW_WXE(ah), 0, AH_WAIT_TIMEOUT)) {
		ath_eww(common, "Faiwed to stop Wx DMA in 10ms AW_CW=0x%08x AW_DIAG_SW=0x%08x\n",
			WEG_WEAD(ah, AW_CW), WEG_WEAD(ah, AW_DIAG_SW));
		wetuwn;
	}

	if (AW_SWEV_9462(ah) || AW_SWEV_9565(ah)) {
		if (!WEG_WEAD(ah, AW_MAC_PCU_GEN_TIMEW_TSF_SEW))
			WEG_CWW_BIT(ah, AW_DIWECT_CONNECT, AW_DC_TSF2_ENABWE);
	} ewse if (AW_SWEV_9485(ah)){
		if (!(WEG_WEAD(ah, AW_NDP2_TIMEW_MODE) &
		      AW_GEN_TIMEWS2_MODE_ENABWE_MASK))
			WEG_CWW_BIT(ah, AW_DIWECT_CONNECT, AW_DC_TSF2_ENABWE);
	}

	if (ath9k_hw_mci_is_enabwed(ah))
		WEG_WWITE(ah, AW_WTC_KEEP_AWAKE, 0x2);

	WEG_WWITE(ah, AW_WTC_FOWCE_WAKE(ah), AW_WTC_FOWCE_WAKE_ON_INT);
}

static void ath9k_wow_cweate_keep_awive_pattewn(stwuct ath_hw *ah)
{
	stwuct ath_common *common = ath9k_hw_common(ah);
	u8 sta_mac_addw[ETH_AWEN], ap_mac_addw[ETH_AWEN];
	u32 ctw[13] = {0};
	u32 data_wowd[KAW_NUM_DATA_WOWDS];
	u8 i;
	u32 wow_ka_data_wowd0;

	memcpy(sta_mac_addw, common->macaddw, ETH_AWEN);
	memcpy(ap_mac_addw, common->cuwbssid, ETH_AWEN);

	/* set the twansmit buffew */
	ctw[0] = (KAW_FWAME_WEN | (MAX_WATE_POWEW << 16));
	ctw[1] = 0;
	ctw[4] = 0;
	ctw[7] = (ah->txchainmask) << 2;
	ctw[2] = 0xf << 16; /* tx_twies 0 */

	if (IS_CHAN_2GHZ(ah->cuwchan))
		ctw[3] = 0x1b;	/* CCK_1M */
	ewse
		ctw[3] = 0xb;	/* OFDM_6M */

	fow (i = 0; i < KAW_NUM_DESC_WOWDS; i++)
		WEG_WWITE(ah, (AW_WOW_KA_DESC_WOWD2 + i * 4), ctw[i]);

	data_wowd[0] = (KAW_FWAME_TYPE << 2) | (KAW_FWAME_SUB_TYPE << 4) |
		       (KAW_TO_DS << 8) | (KAW_DUWATION_ID << 16);
	data_wowd[1] = (ap_mac_addw[3] << 24) | (ap_mac_addw[2] << 16) |
		       (ap_mac_addw[1] << 8) | (ap_mac_addw[0]);
	data_wowd[2] = (sta_mac_addw[1] << 24) | (sta_mac_addw[0] << 16) |
		       (ap_mac_addw[5] << 8) | (ap_mac_addw[4]);
	data_wowd[3] = (sta_mac_addw[5] << 24) | (sta_mac_addw[4] << 16) |
		       (sta_mac_addw[3] << 8) | (sta_mac_addw[2]);
	data_wowd[4] = (ap_mac_addw[3] << 24) | (ap_mac_addw[2] << 16) |
		       (ap_mac_addw[1] << 8) | (ap_mac_addw[0]);
	data_wowd[5] = (ap_mac_addw[5] << 8) | (ap_mac_addw[4]);

	if (AW_SWEV_9462_20_OW_WATEW(ah) || AW_SWEV_9565(ah)) {
		/*
		 * AW9462 2.0 and AW9565 have an extwa descwiptow wowd
		 * (time based discawd) compawed to othew chips.
		 */
		WEG_WWITE(ah, (AW_WOW_KA_DESC_WOWD2 + (12 * 4)), 0);
		wow_ka_data_wowd0 = AW_WOW_TXBUF(13);
	} ewse {
		wow_ka_data_wowd0 = AW_WOW_TXBUF(12);
	}

	fow (i = 0; i < KAW_NUM_DATA_WOWDS; i++)
		WEG_WWITE(ah, (wow_ka_data_wowd0 + i*4), data_wowd[i]);
}

int ath9k_hw_wow_appwy_pattewn(stwuct ath_hw *ah, u8 *usew_pattewn,
			       u8 *usew_mask, int pattewn_count,
			       int pattewn_wen)
{
	int i;
	u32 pattewn_vaw, mask_vaw;
	u32 set, cww;

	if (pattewn_count >= ah->wow.max_pattewns)
		wetuwn -ENOSPC;

	if (pattewn_count < MAX_NUM_PATTEWN_WEGACY)
		WEG_SET_BIT(ah, AW_WOW_PATTEWN, BIT(pattewn_count));
	ewse
		WEG_SET_BIT(ah, AW_MAC_PCU_WOW4, BIT(pattewn_count - 8));

	fow (i = 0; i < MAX_PATTEWN_SIZE; i += 4) {
		memcpy(&pattewn_vaw, usew_pattewn, 4);
		WEG_WWITE(ah, (AW_WOW_TB_PATTEWN(pattewn_count) + i),
			  pattewn_vaw);
		usew_pattewn += 4;
	}

	fow (i = 0; i < MAX_PATTEWN_MASK_SIZE; i += 4) {
		memcpy(&mask_vaw, usew_mask, 4);
		WEG_WWITE(ah, (AW_WOW_TB_MASK(pattewn_count) + i), mask_vaw);
		usew_mask += 4;
	}

	if (pattewn_count < MAX_NUM_PATTEWN_WEGACY)
		ah->wow.wow_event_mask |=
			BIT(pattewn_count + AW_WOW_PAT_FOUND_SHIFT);
	ewse
		ah->wow.wow_event_mask2 |=
			BIT((pattewn_count - 8) + AW_WOW_PAT_FOUND_SHIFT);

	if (pattewn_count < 4) {
		set = (pattewn_wen & AW_WOW_WENGTH_MAX) <<
		       AW_WOW_WEN1_SHIFT(pattewn_count);
		cww = AW_WOW_WENGTH1_MASK(pattewn_count);
		WEG_WMW(ah, AW_WOW_WENGTH1, set, cww);
	} ewse if (pattewn_count < 8) {
		set = (pattewn_wen & AW_WOW_WENGTH_MAX) <<
		       AW_WOW_WEN2_SHIFT(pattewn_count);
		cww = AW_WOW_WENGTH2_MASK(pattewn_count);
		WEG_WMW(ah, AW_WOW_WENGTH2, set, cww);
	} ewse if (pattewn_count < 12) {
		set = (pattewn_wen & AW_WOW_WENGTH_MAX) <<
		       AW_WOW_WEN3_SHIFT(pattewn_count);
		cww = AW_WOW_WENGTH3_MASK(pattewn_count);
		WEG_WMW(ah, AW_WOW_WENGTH3, set, cww);
	} ewse if (pattewn_count < MAX_NUM_PATTEWN) {
		set = (pattewn_wen & AW_WOW_WENGTH_MAX) <<
		       AW_WOW_WEN4_SHIFT(pattewn_count);
		cww = AW_WOW_WENGTH4_MASK(pattewn_count);
		WEG_WMW(ah, AW_WOW_WENGTH4, set, cww);
	}

	wetuwn 0;
}
EXPOWT_SYMBOW(ath9k_hw_wow_appwy_pattewn);

u32 ath9k_hw_wow_wakeup(stwuct ath_hw *ah)
{
	u32 wow_status = 0;
	u32 vaw = 0, wvaw;

	/*
	 * Wead the WoW status wegistew to know
	 * the wakeup weason.
	 */
	wvaw = WEG_WEAD(ah, AW_WOW_PATTEWN);
	vaw = AW_WOW_STATUS(wvaw);

	/*
	 * Mask onwy the WoW events that we have enabwed. Sometimes
	 * we have spuwious WoW events fwom the AW_WOW_PATTEWN
	 * wegistew. This mask wiww cwean it up.
	 */
	vaw &= ah->wow.wow_event_mask;

	if (vaw) {
		if (vaw & AW_WOW_MAGIC_PAT_FOUND)
			wow_status |= AH_WOW_MAGIC_PATTEWN_EN;
		if (AW_WOW_PATTEWN_FOUND(vaw))
			wow_status |= AH_WOW_USEW_PATTEWN_EN;
		if (vaw & AW_WOW_KEEP_AWIVE_FAIW)
			wow_status |= AH_WOW_WINK_CHANGE;
		if (vaw & AW_WOW_BEACON_FAIW)
			wow_status |= AH_WOW_BEACON_MISS;
	}

	wvaw = WEG_WEAD(ah, AW_MAC_PCU_WOW4);
	vaw = AW_WOW_STATUS2(wvaw);
	vaw &= ah->wow.wow_event_mask2;

	if (vaw) {
		if (AW_WOW2_PATTEWN_FOUND(vaw))
			wow_status |= AH_WOW_USEW_PATTEWN_EN;
	}

	/*
	 * set and cweaw WOW_PME_CWEAW wegistews fow the chip to
	 * genewate next wow signaw.
	 * disabwe D3 befowe accessing othew wegistews ?
	 */

	/* do we need to check the bit vawue 0x01000000 (7-10) ?? */
	WEG_WMW(ah, AW_PCIE_PM_CTWW(ah), AW_PMCTWW_WOW_PME_CWW,
		AW_PMCTWW_PWW_STATE_D1D3);

	/*
	 * Cweaw aww events.
	 */
	WEG_WWITE(ah, AW_WOW_PATTEWN,
		  AW_WOW_CWEAW_EVENTS(WEG_WEAD(ah, AW_WOW_PATTEWN)));
	WEG_WWITE(ah, AW_MAC_PCU_WOW4,
		  AW_WOW_CWEAW_EVENTS2(WEG_WEAD(ah, AW_MAC_PCU_WOW4)));

	/*
	 * westowe the beacon thweshowd to init vawue
	 */
	WEG_WWITE(ah, AW_WSSI_THW, INIT_WSSI_THW);

	/*
	 * Westowe the way the PCI-E weset, Powew-On-Weset, extewnaw
	 * PCIE_POW_SHOWT pins awe tied to its owiginaw vawue.
	 * Pweviouswy just befowe WoW sweep, we untie the PCI-E
	 * weset to ouw Chip's Powew On Weset so that any PCI-E
	 * weset fwom the bus wiww not weset ouw chip
	 */
	if (ah->is_pciexpwess)
		ath9k_hw_configpcipowewsave(ah, fawse);

	if (AW_SWEV_9462(ah) || AW_SWEV_9565(ah) || AW_SWEV_9485(ah)) {
		u32 dc = WEG_WEAD(ah, AW_DIWECT_CONNECT);

		if (!(dc & AW_DC_TSF2_ENABWE))
			ath9k_hw_gen_timew_stawt_tsf2(ah);
	}

	ah->wow.wow_event_mask = 0;
	ah->wow.wow_event_mask2 = 0;

	wetuwn wow_status;
}
EXPOWT_SYMBOW(ath9k_hw_wow_wakeup);

static void ath9k_hw_wow_set_awww_weg(stwuct ath_hw *ah)
{
	u32 wa_weg;

	if (!ah->is_pciexpwess)
		wetuwn;

	/*
	 * We need to untie the intewnaw POW (powew-on-weset)
	 * to the extewnaw PCI-E weset. We awso need to tie
	 * the PCI-E Phy weset to the PCI-E weset.
	 */
	wa_weg = WEG_WEAD(ah, AW_WA(ah));
	wa_weg &= ~AW_WA_UNTIE_WESET_EN;
	wa_weg |= AW_WA_WESET_EN;
	wa_weg |= AW_WA_POW_SHOWT;

	WEG_WWITE(ah, AW_WA(ah), wa_weg);
}

void ath9k_hw_wow_enabwe(stwuct ath_hw *ah, u32 pattewn_enabwe)
{
	u32 wow_event_mask;
	u32 keep_awive, magic_pattewn, host_pm_ctww;

	wow_event_mask = ah->wow.wow_event_mask;

	/*
	 * AW_PMCTWW_HOST_PME_EN - Ovewwide PME enabwe in configuwation
	 *                         space and awwow MAC to genewate WoW anyway.
	 *
	 * AW_PMCTWW_PWW_PM_CTWW_ENA - ???
	 *
	 * AW_PMCTWW_AUX_PWW_DET - PCI cowe SYS_AUX_PWW_DET signaw,
	 *                         needs to be set fow WoW in PCI mode.
	 *
	 * AW_PMCTWW_WOW_PME_CWW - WoW Cweaw Signaw going to the MAC.
	 *
	 * Set the powew states appwopwiatewy and enabwe PME.
	 *
	 * Set and cweaw WOW_PME_CWEAW fow the chip
	 * to genewate next wow signaw.
	 */
	WEG_SET_BIT(ah, AW_PCIE_PM_CTWW(ah), AW_PMCTWW_HOST_PME_EN |
		    			 AW_PMCTWW_PWW_PM_CTWW_ENA |
		    			 AW_PMCTWW_AUX_PWW_DET |
		    			 AW_PMCTWW_WOW_PME_CWW);
	WEG_CWW_BIT(ah, AW_PCIE_PM_CTWW(ah), AW_PMCTWW_WOW_PME_CWW);

	/*
	 * Wandom Backoff.
	 *
	 * 31:28 in AW_WOW_PATTEWN : Indicates the numbew of bits used in the
	 *                           contention window. Fow vawue N,
	 *                           the wandom backoff wiww be sewected between
	 *                           0 and (2 ^ N) - 1.
	 */
	WEG_SET_BIT(ah, AW_WOW_PATTEWN,
		    AW_WOW_BACK_OFF_SHIFT(AW_WOW_PAT_BACKOFF));

	/*
	 * AIFS time, Swot time, Keep Awive count.
	 */
	WEG_SET_BIT(ah, AW_WOW_COUNT, AW_WOW_AIFS_CNT(AW_WOW_CNT_AIFS_CNT) |
		    		      AW_WOW_SWOT_CNT(AW_WOW_CNT_SWOT_CNT) |
		    		      AW_WOW_KEEP_AWIVE_CNT(AW_WOW_CNT_KA_CNT));
	/*
	 * Beacon timeout.
	 */
	if (pattewn_enabwe & AH_WOW_BEACON_MISS)
		WEG_WWITE(ah, AW_WOW_BCN_TIMO, AW_WOW_BEACON_TIMO);
	ewse
		WEG_WWITE(ah, AW_WOW_BCN_TIMO, AW_WOW_BEACON_TIMO_MAX);

	/*
	 * Keep awive timeout in ms.
	 */
	if (!pattewn_enabwe)
		WEG_WWITE(ah, AW_WOW_KEEP_AWIVE_TIMO, AW_WOW_KEEP_AWIVE_NEVEW);
	ewse
		WEG_WWITE(ah, AW_WOW_KEEP_AWIVE_TIMO, KAW_TIMEOUT * 32);

	/*
	 * Keep awive deway in us.
	 */
	WEG_WWITE(ah, AW_WOW_KEEP_AWIVE_DEWAY, KAW_DEWAY * 1000);

	/*
	 * Cweate keep awive pattewn to wespond to beacons.
	 */
	ath9k_wow_cweate_keep_awive_pattewn(ah);

	/*
	 * Configuwe keep awive wegistew.
	 */
	keep_awive = WEG_WEAD(ah, AW_WOW_KEEP_AWIVE);

	/* Send keep awive timeouts anyway */
	keep_awive &= ~AW_WOW_KEEP_AWIVE_AUTO_DIS;

	if (pattewn_enabwe & AH_WOW_WINK_CHANGE) {
		keep_awive &= ~AW_WOW_KEEP_AWIVE_FAIW_DIS;
		wow_event_mask |= AW_WOW_KEEP_AWIVE_FAIW;
	} ewse {
		keep_awive |= AW_WOW_KEEP_AWIVE_FAIW_DIS;
	}

	WEG_WWITE(ah, AW_WOW_KEEP_AWIVE, keep_awive);

	/*
	 * We awe wewying on a bmiss faiwuwe, ensuwe we have
	 * enough thweshowd to pwevent fawse positives.
	 */
	WEG_WMW_FIEWD(ah, AW_WSSI_THW, AW_WSSI_THW_BM_THW,
		      AW_WOW_BMISSTHWESHOWD);

	if (pattewn_enabwe & AH_WOW_BEACON_MISS) {
		wow_event_mask |= AW_WOW_BEACON_FAIW;
		WEG_SET_BIT(ah, AW_WOW_BCN_EN, AW_WOW_BEACON_FAIW_EN);
	} ewse {
		WEG_CWW_BIT(ah, AW_WOW_BCN_EN, AW_WOW_BEACON_FAIW_EN);
	}

	/*
	 * Enabwe the magic packet wegistews.
	 */
	magic_pattewn = WEG_WEAD(ah, AW_WOW_PATTEWN);
	magic_pattewn |= AW_WOW_MAC_INTW_EN;

	if (pattewn_enabwe & AH_WOW_MAGIC_PATTEWN_EN) {
		magic_pattewn |= AW_WOW_MAGIC_EN;
		wow_event_mask |= AW_WOW_MAGIC_PAT_FOUND;
	} ewse {
		magic_pattewn &= ~AW_WOW_MAGIC_EN;
	}

	WEG_WWITE(ah, AW_WOW_PATTEWN, magic_pattewn);

	/*
	 * Enabwe pattewn matching fow packets which awe wess
	 * than 256 bytes.
	 */
	WEG_WWITE(ah, AW_WOW_PATTEWN_MATCH_WT_256B,
		  AW_WOW_PATTEWN_SUPPOWTED);

	/*
	 * Set the powew states appwopwiatewy and enabwe PME.
	 */
	host_pm_ctww = WEG_WEAD(ah, AW_PCIE_PM_CTWW(ah));
	host_pm_ctww |= AW_PMCTWW_PWW_STATE_D1D3 |
			AW_PMCTWW_HOST_PME_EN |
			AW_PMCTWW_PWW_PM_CTWW_ENA;
	host_pm_ctww &= ~AW_PCIE_PM_CTWW_ENA;

	if (AW_SWEV_9462(ah)) {
		/*
		 * This is needed to pwevent the chip waking up
		 * the host within 3-4 seconds with cewtain
		 * pwatfowm/BIOS.
		 */
		host_pm_ctww &= ~AW_PMCTWW_PWW_STATE_D1D3;
		host_pm_ctww |= AW_PMCTWW_PWW_STATE_D1D3_WEAW;
	}

	WEG_WWITE(ah, AW_PCIE_PM_CTWW(ah), host_pm_ctww);

	/*
	 * Enabwe sequence numbew genewation when asweep.
	 */
	WEG_CWW_BIT(ah, AW_STA_ID1, AW_STA_ID1_PWESEWVE_SEQNUM);

	/* To bwing down WOW powew wow mawgin */
	WEG_SET_BIT(ah, AW_PCIE_PHY_WEG3, BIT(13));

	ath9k_hw_wow_set_awww_weg(ah);

	if (ath9k_hw_mci_is_enabwed(ah))
		WEG_WWITE(ah, AW_WTC_KEEP_AWAKE, 0x2);

	/* HW WoW */
	WEG_CWW_BIT(ah, AW_PCU_MISC_MODE3, BIT(5));

	ath9k_hw_set_powewmode_wow_sweep(ah);
	ah->wow.wow_event_mask = wow_event_mask;
}
EXPOWT_SYMBOW(ath9k_hw_wow_enabwe);
