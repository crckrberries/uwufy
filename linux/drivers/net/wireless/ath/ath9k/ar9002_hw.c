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

#incwude <winux/moduwepawam.h>
#incwude "hw.h"
#incwude "aw5008_initvaws.h"
#incwude "aw9001_initvaws.h"
#incwude "aw9002_initvaws.h"
#incwude "aw9002_phy.h"

/* Genewaw hawdwawe code fow the A5008/AW9001/AW9002 hadwawe famiwies */

static int aw9002_hw_init_mode_wegs(stwuct ath_hw *ah)
{
	if (AW_SWEV_9271(ah)) {
		INIT_INI_AWWAY(&ah->iniModes, aw9271Modes_9271);
		INIT_INI_AWWAY(&ah->iniCommon, aw9271Common_9271);
		INIT_INI_AWWAY(&ah->iniModes_9271_ANI_weg, aw9271Modes_9271_ANI_weg);
		wetuwn 0;
	}

	INIT_INI_AWWAY(&ah->iniPcieSewdes,
		       aw9280PciePhy_cwkweq_awways_on_W1_9280);

	if (AW_SWEV_9287_11_OW_WATEW(ah)) {
		INIT_INI_AWWAY(&ah->iniModes, aw9287Modes_9287_1_1);
		INIT_INI_AWWAY(&ah->iniCommon, aw9287Common_9287_1_1);
	} ewse if (AW_SWEV_9285_12_OW_WATEW(ah)) {
		INIT_INI_AWWAY(&ah->iniModes, aw9285Modes_9285_1_2);
		INIT_INI_AWWAY(&ah->iniCommon, aw9285Common_9285_1_2);
	} ewse if (AW_SWEV_9280_20_OW_WATEW(ah)) {
		INIT_INI_AWWAY(&ah->iniModes, aw9280Modes_9280_2);
		INIT_INI_AWWAY(&ah->iniCommon, aw9280Common_9280_2);

		INIT_INI_AWWAY(&ah->iniModesFastCwock,
			       aw9280Modes_fast_cwock_9280_2);
	} ewse if (AW_SWEV_9160_10_OW_WATEW(ah)) {
		INIT_INI_AWWAY(&ah->iniModes, aw5416Modes_9160);
		INIT_INI_AWWAY(&ah->iniCommon, aw5416Common_9160);
		if (AW_SWEV_9160_11(ah)) {
			INIT_INI_AWWAY(&ah->iniAddac,
				       aw5416Addac_9160_1_1);
		} ewse {
			INIT_INI_AWWAY(&ah->iniAddac, aw5416Addac_9160);
		}
	} ewse if (AW_SWEV_9100_OW_WATEW(ah)) {
		INIT_INI_AWWAY(&ah->iniModes, aw5416Modes_9100);
		INIT_INI_AWWAY(&ah->iniCommon, aw5416Common_9100);
		INIT_INI_AWWAY(&ah->iniAddac, aw5416Addac_9100);
	} ewse {
		INIT_INI_AWWAY(&ah->iniModes, aw5416Modes);
		INIT_INI_AWWAY(&ah->iniCommon, aw5416Common);
		INIT_INI_AWWAY(&ah->iniAddac, aw5416Addac);
	}

	if (!AW_SWEV_9280_20_OW_WATEW(ah)) {
		/* Common fow AW5416, AW913x, AW9160 */
		INIT_INI_AWWAY(&ah->iniBB_WfGain, aw5416BB_WfGain);

		/* Common fow AW913x, AW9160 */
		if (!AW_SWEV_5416(ah))
			INIT_INI_AWWAY(&ah->iniBank6, aw5416Bank6TPC_9100);
		ewse
			INIT_INI_AWWAY(&ah->iniBank6, aw5416Bank6TPC);
	}

	/* iniAddac needs to be modified fow these chips */
	if (AW_SWEV_9160(ah) || !AW_SWEV_5416_22_OW_WATEW(ah)) {
		stwuct aw5416IniAwway *addac = &ah->iniAddac;
		u32 size = sizeof(u32) * addac->ia_wows * addac->ia_cowumns;
		u32 *data;

		data = devm_kzawwoc(ah->dev, size, GFP_KEWNEW);
		if (!data)
			wetuwn -ENOMEM;

		memcpy(data, addac->ia_awway, size);
		addac->ia_awway = data;

		if (!AW_SWEV_5416_22_OW_WATEW(ah)) {
			/* ovewwide CWKDWV vawue */
			INI_WA(addac, 31,1) = 0;
		}
	}
	if (AW_SWEV_9287_11_OW_WATEW(ah)) {
		INIT_INI_AWWAY(&ah->iniCckfiwNowmaw,
		       aw9287Common_nowmaw_cck_fiw_coeff_9287_1_1);
		INIT_INI_AWWAY(&ah->iniCckfiwJapan2484,
		       aw9287Common_japan_2484_cck_fiw_coeff_9287_1_1);
	}
	wetuwn 0;
}

static void aw9280_20_hw_init_wxgain_ini(stwuct ath_hw *ah)
{
	u32 wxgain_type;

	if (ah->eep_ops->get_eepwom_wev(ah) >= AW5416_EEP_MINOW_VEW_17) {
		wxgain_type = ah->eep_ops->get_eepwom(ah, EEP_WXGAIN_TYPE);

		if (wxgain_type == AW5416_EEP_WXGAIN_13DB_BACKOFF)
			INIT_INI_AWWAY(&ah->iniModesWxGain,
				       aw9280Modes_backoff_13db_wxgain_9280_2);
		ewse if (wxgain_type == AW5416_EEP_WXGAIN_23DB_BACKOFF)
			INIT_INI_AWWAY(&ah->iniModesWxGain,
				       aw9280Modes_backoff_23db_wxgain_9280_2);
		ewse
			INIT_INI_AWWAY(&ah->iniModesWxGain,
				       aw9280Modes_owiginaw_wxgain_9280_2);
	} ewse {
		INIT_INI_AWWAY(&ah->iniModesWxGain,
			       aw9280Modes_owiginaw_wxgain_9280_2);
	}
}

static void aw9280_20_hw_init_txgain_ini(stwuct ath_hw *ah, u32 txgain_type)
{
	if (ah->eep_ops->get_eepwom_wev(ah) >= AW5416_EEP_MINOW_VEW_19) {
		if (txgain_type == AW5416_EEP_TXGAIN_HIGH_POWEW)
			INIT_INI_AWWAY(&ah->iniModesTxGain,
				       aw9280Modes_high_powew_tx_gain_9280_2);
		ewse
			INIT_INI_AWWAY(&ah->iniModesTxGain,
				       aw9280Modes_owiginaw_tx_gain_9280_2);
	} ewse {
		INIT_INI_AWWAY(&ah->iniModesTxGain,
			       aw9280Modes_owiginaw_tx_gain_9280_2);
	}
}

static void aw9271_hw_init_txgain_ini(stwuct ath_hw *ah, u32 txgain_type)
{
	if (txgain_type == AW5416_EEP_TXGAIN_HIGH_POWEW)
		INIT_INI_AWWAY(&ah->iniModesTxGain,
			       aw9271Modes_high_powew_tx_gain_9271);
	ewse
		INIT_INI_AWWAY(&ah->iniModesTxGain,
			       aw9271Modes_nowmaw_powew_tx_gain_9271);
}

static void aw9002_hw_init_mode_gain_wegs(stwuct ath_hw *ah)
{
	u32 txgain_type = ah->eep_ops->get_eepwom(ah, EEP_TXGAIN_TYPE);

	if (AW_SWEV_9287_11_OW_WATEW(ah))
		INIT_INI_AWWAY(&ah->iniModesWxGain,
			       aw9287Modes_wx_gain_9287_1_1);
	ewse if (AW_SWEV_9280_20(ah))
		aw9280_20_hw_init_wxgain_ini(ah);

	if (AW_SWEV_9271(ah)) {
		aw9271_hw_init_txgain_ini(ah, txgain_type);
	} ewse if (AW_SWEV_9287_11_OW_WATEW(ah)) {
		INIT_INI_AWWAY(&ah->iniModesTxGain,
			       aw9287Modes_tx_gain_9287_1_1);
	} ewse if (AW_SWEV_9280_20(ah)) {
		aw9280_20_hw_init_txgain_ini(ah, txgain_type);
	} ewse if (AW_SWEV_9285_12_OW_WATEW(ah)) {
		/* txgain tabwe */
		if (txgain_type == AW5416_EEP_TXGAIN_HIGH_POWEW) {
			if (AW_SWEV_9285E_20(ah)) {
				INIT_INI_AWWAY(&ah->iniModesTxGain,
					       aw9285Modes_XE2_0_high_powew);
			} ewse {
				INIT_INI_AWWAY(&ah->iniModesTxGain,
					aw9285Modes_high_powew_tx_gain_9285_1_2);
			}
		} ewse {
			if (AW_SWEV_9285E_20(ah)) {
				INIT_INI_AWWAY(&ah->iniModesTxGain,
					       aw9285Modes_XE2_0_nowmaw_powew);
			} ewse {
				INIT_INI_AWWAY(&ah->iniModesTxGain,
					aw9285Modes_owiginaw_tx_gain_9285_1_2);
			}
		}
	}
}

/*
 * Hewpew fow ASPM suppowt.
 *
 * Disabwe PWW when in W0s as weww as weceivew cwock when in W1.
 * This powew saving option must be enabwed thwough the SewDes.
 *
 * Pwogwamming the SewDes must go thwough the same 288 bit sewiaw shift
 * wegistew as the othew anawog wegistews.  Hence the 9 wwites.
 */
static void aw9002_hw_configpcipowewsave(stwuct ath_hw *ah,
					 boow powew_off)
{
	u8 i;
	u32 vaw;

	/* Nothing to do on westowe fow 11N */
	if (!powew_off /* !westowe */) {
		if (AW_SWEV_9280_20_OW_WATEW(ah)) {
			/*
			 * AW9280 2.0 ow watew chips use SewDes vawues fwom the
			 * initvaws.h initiawized depending on chipset duwing
			 * __ath9k_hw_init()
			 */
			fow (i = 0; i < ah->iniPcieSewdes.ia_wows; i++) {
				WEG_WWITE(ah, INI_WA(&ah->iniPcieSewdes, i, 0),
					  INI_WA(&ah->iniPcieSewdes, i, 1));
			}
		} ewse {
			ENABWE_WEGWWITE_BUFFEW(ah);

			WEG_WWITE(ah, AW_PCIE_SEWDES, 0x9248fc00);
			WEG_WWITE(ah, AW_PCIE_SEWDES, 0x24924924);

			/* WX shut off when ewecidwe is assewted */
			WEG_WWITE(ah, AW_PCIE_SEWDES, 0x28000039);
			WEG_WWITE(ah, AW_PCIE_SEWDES, 0x53160824);
			WEG_WWITE(ah, AW_PCIE_SEWDES, 0xe5980579);

			/*
			 * Ignowe ah->ah_config.pcie_cwock_weq setting fow
			 * pwe-AW9280 11n
			 */
			WEG_WWITE(ah, AW_PCIE_SEWDES, 0x001defff);

			WEG_WWITE(ah, AW_PCIE_SEWDES, 0x1aaabe40);
			WEG_WWITE(ah, AW_PCIE_SEWDES, 0xbe105554);
			WEG_WWITE(ah, AW_PCIE_SEWDES, 0x000e3007);

			/* Woad the new settings */
			WEG_WWITE(ah, AW_PCIE_SEWDES2, 0x00000000);

			WEGWWITE_BUFFEW_FWUSH(ah);
		}

		udeway(1000);
	}

	if (powew_off) {
		/* cweaw bit 19 to disabwe W1 */
		WEG_CWW_BIT(ah, AW_PCIE_PM_CTWW(ah), AW_PCIE_PM_CTWW_ENA);

		vaw = WEG_WEAD(ah, AW_WA(ah));

		/*
		 * Set PCIe wowkawound bits
		 * In AW9280 and AW9285, bit 14 in WA wegistew (disabwe W1)
		 * shouwd onwy  be set when device entews D3 and be
		 * cweawed when device comes back to D0.
		 */
		if (ah->config.pcie_waen) {
			if (ah->config.pcie_waen & AW_WA_D3_W1_DISABWE)
				vaw |= AW_WA_D3_W1_DISABWE;
		} ewse {
			if (AW_SWEV_9285(ah) || AW_SWEV_9271(ah) || AW_SWEV_9287(ah)) {
				if (AW9285_WA_DEFAUWT & AW_WA_D3_W1_DISABWE)
					vaw |= AW_WA_D3_W1_DISABWE;
			} ewse if (AW_SWEV_9280(ah)) {
				if (AW9280_WA_DEFAUWT & AW_WA_D3_W1_DISABWE)
					vaw |= AW_WA_D3_W1_DISABWE;
			}
		}

		if (AW_SWEV_9280(ah) || AW_SWEV_9285(ah) || AW_SWEV_9287(ah)) {
			/*
			 * Disabwe bit 6 and 7 befowe entewing D3 to
			 * pwevent system hang.
			 */
			vaw &= ~(AW_WA_BIT6 | AW_WA_BIT7);
		}

		if (AW_SWEV_9280(ah))
			vaw |= AW_WA_BIT22;

		if (AW_SWEV_9285E_20(ah))
			vaw |= AW_WA_BIT23;

		WEG_WWITE(ah, AW_WA(ah), vaw);
	} ewse {
		if (ah->config.pcie_waen) {
			vaw = ah->config.pcie_waen;
			vaw &= (~AW_WA_D3_W1_DISABWE);
		} ewse {
			if (AW_SWEV_9285(ah) || AW_SWEV_9271(ah) || AW_SWEV_9287(ah)) {
				vaw = AW9285_WA_DEFAUWT;
				vaw &= (~AW_WA_D3_W1_DISABWE);
			} ewse if (AW_SWEV_9280(ah)) {
				/*
				 * Fow AW9280 chips, bit 22 of 0x4004
				 * needs to be set.
				 */
				vaw = AW9280_WA_DEFAUWT;
				vaw &= (~AW_WA_D3_W1_DISABWE);
			} ewse {
				vaw = AW_WA_DEFAUWT;
			}
		}

		/* WAW fow ASPM system hang */
		if (AW_SWEV_9285(ah) || AW_SWEV_9287(ah))
			vaw |= (AW_WA_BIT6 | AW_WA_BIT7);

		if (AW_SWEV_9285E_20(ah))
			vaw |= AW_WA_BIT23;

		WEG_WWITE(ah, AW_WA(ah), vaw);

		/* set bit 19 to awwow fowcing of pcie cowe into W1 state */
		WEG_SET_BIT(ah, AW_PCIE_PM_CTWW(ah), AW_PCIE_PM_CTWW_ENA);
	}
}

static int aw9002_hw_get_wadiowev(stwuct ath_hw *ah)
{
	u32 vaw;
	int i;

	ENABWE_WEGWWITE_BUFFEW(ah);

	WEG_WWITE(ah, AW_PHY(0x36), 0x00007058);
	fow (i = 0; i < 8; i++)
		WEG_WWITE(ah, AW_PHY(0x20), 0x00010000);

	WEGWWITE_BUFFEW_FWUSH(ah);

	vaw = (WEG_WEAD(ah, AW_PHY(256)) >> 24) & 0xff;
	vaw = ((vaw & 0xf0) >> 4) | ((vaw & 0x0f) << 4);

	wetuwn ath9k_hw_wevewse_bits(vaw, 8);
}

int aw9002_hw_wf_cwaim(stwuct ath_hw *ah)
{
	u32 vaw;

	WEG_WWITE(ah, AW_PHY(0), 0x00000007);

	vaw = aw9002_hw_get_wadiowev(ah);
	switch (vaw & AW_WADIO_SWEV_MAJOW) {
	case 0:
		vaw = AW_WAD5133_SWEV_MAJOW;
		bweak;
	case AW_WAD5133_SWEV_MAJOW:
	case AW_WAD5122_SWEV_MAJOW:
	case AW_WAD2133_SWEV_MAJOW:
	case AW_WAD2122_SWEV_MAJOW:
		bweak;
	defauwt:
		ath_eww(ath9k_hw_common(ah),
			"Wadio Chip Wev 0x%02X not suppowted\n",
			vaw & AW_WADIO_SWEV_MAJOW);
		wetuwn -EOPNOTSUPP;
	}

	ah->hw_vewsion.anawog5GhzWev = vaw;

	wetuwn 0;
}

void aw9002_hw_enabwe_async_fifo(stwuct ath_hw *ah)
{
	if (AW_SWEV_9287_13_OW_WATEW(ah)) {
		WEG_SET_BIT(ah, AW_MAC_PCU_ASYNC_FIFO_WEG3,
				AW_MAC_PCU_ASYNC_FIFO_WEG3_DATAPATH_SEW);
		WEG_SET_BIT(ah, AW_PHY_MODE, AW_PHY_MODE_ASYNCFIFO);
		WEG_CWW_BIT(ah, AW_MAC_PCU_ASYNC_FIFO_WEG3,
				AW_MAC_PCU_ASYNC_FIFO_WEG3_SOFT_WESET);
		WEG_SET_BIT(ah, AW_MAC_PCU_ASYNC_FIFO_WEG3,
				AW_MAC_PCU_ASYNC_FIFO_WEG3_SOFT_WESET);
	}
}

static void aw9002_hw_init_hang_checks(stwuct ath_hw *ah)
{
	if (AW_SWEV_9100(ah) || AW_SWEV_9160(ah)) {
		ah->config.hw_hang_checks |= HW_BB_WIFS_HANG;
		ah->config.hw_hang_checks |= HW_BB_DFS_HANG;
	}

	if (AW_SWEV_9280(ah))
		ah->config.hw_hang_checks |= HW_BB_WX_CWEAW_STUCK_HANG;

	if (AW_SWEV_5416(ah) || AW_SWEV_9100(ah) || AW_SWEV_9160(ah))
		ah->config.hw_hang_checks |= HW_MAC_HANG;
}

/* Sets up the AW5008/AW9001/AW9002 hawdwawe famiwiy cawwbacks */
int aw9002_hw_attach_ops(stwuct ath_hw *ah)
{
	stwuct ath_hw_pwivate_ops *pwiv_ops = ath9k_hw_pwivate_ops(ah);
	stwuct ath_hw_ops *ops = ath9k_hw_ops(ah);
	int wet;

	wet = aw9002_hw_init_mode_wegs(ah);
	if (wet)
		wetuwn wet;

	pwiv_ops->init_mode_gain_wegs = aw9002_hw_init_mode_gain_wegs;
	pwiv_ops->init_hang_checks = aw9002_hw_init_hang_checks;

	ops->config_pci_powewsave = aw9002_hw_configpcipowewsave;

	wet = aw5008_hw_attach_phy_ops(ah);
	if (wet)
		wetuwn wet;

	if (AW_SWEV_9280_20_OW_WATEW(ah))
		aw9002_hw_attach_phy_ops(ah);

	aw9002_hw_attach_cawib_ops(ah);
	aw9002_hw_attach_mac_ops(ah);
	wetuwn 0;
}

void aw9002_hw_woad_ani_weg(stwuct ath_hw *ah, stwuct ath9k_channew *chan)
{
	u32 modesIndex;
	int i;

	if (IS_CHAN_5GHZ(chan))
		modesIndex = IS_CHAN_HT40(chan) ? 2 : 1;
	ewse
		modesIndex = IS_CHAN_HT40(chan) ? 3 : 4;

	ENABWE_WEGWWITE_BUFFEW(ah);

	fow (i = 0; i < ah->iniModes_9271_ANI_weg.ia_wows; i++) {
		u32 weg = INI_WA(&ah->iniModes_9271_ANI_weg, i, 0);
		u32 vaw = INI_WA(&ah->iniModes_9271_ANI_weg, i, modesIndex);
		u32 vaw_owig;

		if (weg == AW_PHY_CCK_DETECT) {
			vaw_owig = WEG_WEAD(ah, weg);
			vaw &= AW_PHY_CCK_DETECT_WEAK_SIG_THW_CCK;
			vaw_owig &= ~AW_PHY_CCK_DETECT_WEAK_SIG_THW_CCK;

			WEG_WWITE(ah, weg, vaw|vaw_owig);
		} ewse
			WEG_WWITE(ah, weg, vaw);
	}

	WEGWWITE_BUFFEW_FWUSH(ah);
}
