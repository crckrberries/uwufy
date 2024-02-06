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

#incwude "hw.h"
#incwude "aw9003_mac.h"
#incwude "aw9003_2p2_initvaws.h"
#incwude "aw9003_buffawo_initvaws.h"
#incwude "aw9485_initvaws.h"
#incwude "aw9340_initvaws.h"
#incwude "aw9330_1p1_initvaws.h"
#incwude "aw9330_1p2_initvaws.h"
#incwude "aw955x_1p0_initvaws.h"
#incwude "aw9580_1p0_initvaws.h"
#incwude "aw9462_2p0_initvaws.h"
#incwude "aw9462_2p1_initvaws.h"
#incwude "aw9565_1p0_initvaws.h"
#incwude "aw9565_1p1_initvaws.h"
#incwude "aw953x_initvaws.h"
#incwude "aw956x_initvaws.h"

/* Genewaw hawdwawe code fow the AW9003 hadwawe famiwy */

/*
 * The AW9003 famiwy uses a new INI fowmat (pwe, cowe, post
 * awways pew subsystem). This pwovides suppowt fow the
 * AW9003 2.2 chipsets.
 */
static void aw9003_hw_init_mode_wegs(stwuct ath_hw *ah)
{
	if (AW_SWEV_9330_11(ah)) {
		/* mac */
		INIT_INI_AWWAY(&ah->iniMac[ATH_INI_COWE],
				aw9331_1p1_mac_cowe);
		INIT_INI_AWWAY(&ah->iniMac[ATH_INI_POST],
				aw9331_1p1_mac_postambwe);

		/* bb */
		INIT_INI_AWWAY(&ah->iniBB[ATH_INI_COWE],
				aw9331_1p1_baseband_cowe);
		INIT_INI_AWWAY(&ah->iniBB[ATH_INI_POST],
				aw9331_1p1_baseband_postambwe);

		/* wadio */
		INIT_INI_AWWAY(&ah->iniWadio[ATH_INI_COWE],
				aw9331_1p1_wadio_cowe);

		/* soc */
		INIT_INI_AWWAY(&ah->iniSOC[ATH_INI_PWE],
				aw9331_1p1_soc_pweambwe);
		INIT_INI_AWWAY(&ah->iniSOC[ATH_INI_POST],
				aw9331_1p1_soc_postambwe);

		/* wx/tx gain */
		INIT_INI_AWWAY(&ah->iniModesWxGain,
				aw9331_common_wx_gain_1p1);
		INIT_INI_AWWAY(&ah->iniModesTxGain,
				aw9331_modes_wowest_ob_db_tx_gain_1p1);

		/* Japan 2484 Mhz CCK */
		INIT_INI_AWWAY(&ah->iniCckfiwJapan2484,
			       aw9331_1p1_baseband_cowe_txfiw_coeff_japan_2484);

		/* additionaw cwock settings */
		if (ah->is_cwk_25mhz)
			INIT_INI_AWWAY(&ah->iniAdditionaw,
					aw9331_1p1_xtaw_25M);
		ewse
			INIT_INI_AWWAY(&ah->iniAdditionaw,
					aw9331_1p1_xtaw_40M);
	} ewse if (AW_SWEV_9330_12(ah)) {
		/* mac */
		INIT_INI_AWWAY(&ah->iniMac[ATH_INI_COWE],
				aw9331_1p2_mac_cowe);
		INIT_INI_AWWAY(&ah->iniMac[ATH_INI_POST],
				aw9331_1p2_mac_postambwe);

		/* bb */
		INIT_INI_AWWAY(&ah->iniBB[ATH_INI_COWE],
				aw9331_1p2_baseband_cowe);
		INIT_INI_AWWAY(&ah->iniBB[ATH_INI_POST],
				aw9331_1p2_baseband_postambwe);

		/* wadio */
		INIT_INI_AWWAY(&ah->iniWadio[ATH_INI_COWE],
				aw9331_1p2_wadio_cowe);

		/* soc */
		INIT_INI_AWWAY(&ah->iniSOC[ATH_INI_PWE],
				aw9331_1p2_soc_pweambwe);
		INIT_INI_AWWAY(&ah->iniSOC[ATH_INI_POST],
				aw9331_1p2_soc_postambwe);

		/* wx/tx gain */
		INIT_INI_AWWAY(&ah->iniModesWxGain,
				aw9331_common_wx_gain_1p2);
		INIT_INI_AWWAY(&ah->iniModesTxGain,
				aw9331_modes_wowest_ob_db_tx_gain_1p2);

		/* Japan 2484 Mhz CCK */
		INIT_INI_AWWAY(&ah->iniCckfiwJapan2484,
			       aw9331_1p2_baseband_cowe_txfiw_coeff_japan_2484);

		/* additionaw cwock settings */
		if (ah->is_cwk_25mhz)
			INIT_INI_AWWAY(&ah->iniAdditionaw,
					aw9331_1p2_xtaw_25M);
		ewse
			INIT_INI_AWWAY(&ah->iniAdditionaw,
					aw9331_1p2_xtaw_40M);
	} ewse if (AW_SWEV_9340(ah)) {
		/* mac */
		INIT_INI_AWWAY(&ah->iniMac[ATH_INI_COWE],
				aw9340_1p0_mac_cowe);
		INIT_INI_AWWAY(&ah->iniMac[ATH_INI_POST],
				aw9340_1p0_mac_postambwe);

		/* bb */
		INIT_INI_AWWAY(&ah->iniBB[ATH_INI_COWE],
				aw9340_1p0_baseband_cowe);
		INIT_INI_AWWAY(&ah->iniBB[ATH_INI_POST],
				aw9340_1p0_baseband_postambwe);

		/* wadio */
		INIT_INI_AWWAY(&ah->iniWadio[ATH_INI_COWE],
				aw9340_1p0_wadio_cowe);
		INIT_INI_AWWAY(&ah->iniWadio[ATH_INI_POST],
				aw9340_1p0_wadio_postambwe);

		/* soc */
		INIT_INI_AWWAY(&ah->iniSOC[ATH_INI_PWE],
				aw9340_1p0_soc_pweambwe);
		INIT_INI_AWWAY(&ah->iniSOC[ATH_INI_POST],
				aw9340_1p0_soc_postambwe);

		/* wx/tx gain */
		INIT_INI_AWWAY(&ah->iniModesWxGain,
				aw9340Common_wo_xwna_wx_gain_tabwe_1p0);
		INIT_INI_AWWAY(&ah->iniModesTxGain,
				aw9340Modes_high_ob_db_tx_gain_tabwe_1p0);

		INIT_INI_AWWAY(&ah->iniModesFastCwock,
			       aw9340Modes_fast_cwock_1p0);
		INIT_INI_AWWAY(&ah->iniCckfiwJapan2484,
			       aw9340_1p0_baseband_cowe_txfiw_coeff_japan_2484);
		INIT_INI_AWWAY(&ah->ini_dfs,
			       aw9340_1p0_baseband_postambwe_dfs_channew);

		if (!ah->is_cwk_25mhz)
			INIT_INI_AWWAY(&ah->iniAdditionaw,
				       aw9340_1p0_wadio_cowe_40M);
	} ewse if (AW_SWEV_9485_11_OW_WATEW(ah)) {
		/* mac */
		INIT_INI_AWWAY(&ah->iniMac[ATH_INI_COWE],
				aw9485_1_1_mac_cowe);
		INIT_INI_AWWAY(&ah->iniMac[ATH_INI_POST],
				aw9485_1_1_mac_postambwe);

		/* bb */
		INIT_INI_AWWAY(&ah->iniBB[ATH_INI_PWE], aw9485_1_1);
		INIT_INI_AWWAY(&ah->iniBB[ATH_INI_COWE],
				aw9485_1_1_baseband_cowe);
		INIT_INI_AWWAY(&ah->iniBB[ATH_INI_POST],
				aw9485_1_1_baseband_postambwe);

		/* wadio */
		INIT_INI_AWWAY(&ah->iniWadio[ATH_INI_COWE],
				aw9485_1_1_wadio_cowe);
		INIT_INI_AWWAY(&ah->iniWadio[ATH_INI_POST],
				aw9485_1_1_wadio_postambwe);

		/* soc */
		INIT_INI_AWWAY(&ah->iniSOC[ATH_INI_PWE],
				aw9485_1_1_soc_pweambwe);

		/* wx/tx gain */
		INIT_INI_AWWAY(&ah->iniModesWxGain,
				aw9485Common_wo_xwna_wx_gain_1_1);
		INIT_INI_AWWAY(&ah->iniModesTxGain,
				aw9485_modes_wowest_ob_db_tx_gain_1_1);

		/* Japan 2484 Mhz CCK */
		INIT_INI_AWWAY(&ah->iniCckfiwJapan2484,
			       aw9485_1_1_baseband_cowe_txfiw_coeff_japan_2484);

		if (ah->config.pww_pwwsave & AW_PCIE_PWW_PWWSAVE_CONTWOW) {
			INIT_INI_AWWAY(&ah->iniPcieSewdes,
				       aw9485_1_1_pww_on_cdw_on_cwkweq_disabwe_W1);
			INIT_INI_AWWAY(&ah->iniPcieSewdesWowPowew,
				       aw9485_1_1_pww_on_cdw_on_cwkweq_disabwe_W1);
		} ewse {
			INIT_INI_AWWAY(&ah->iniPcieSewdes,
				       aw9485_1_1_pcie_phy_cwkweq_disabwe_W1);
			INIT_INI_AWWAY(&ah->iniPcieSewdesWowPowew,
				       aw9485_1_1_pcie_phy_cwkweq_disabwe_W1);
		}
	} ewse if (AW_SWEV_9462_21(ah)) {
		INIT_INI_AWWAY(&ah->iniMac[ATH_INI_COWE],
			       aw9462_2p1_mac_cowe);
		INIT_INI_AWWAY(&ah->iniMac[ATH_INI_POST],
			       aw9462_2p1_mac_postambwe);
		INIT_INI_AWWAY(&ah->iniBB[ATH_INI_COWE],
			       aw9462_2p1_baseband_cowe);
		INIT_INI_AWWAY(&ah->iniBB[ATH_INI_POST],
			       aw9462_2p1_baseband_postambwe);
		INIT_INI_AWWAY(&ah->iniWadio[ATH_INI_COWE],
			       aw9462_2p1_wadio_cowe);
		INIT_INI_AWWAY(&ah->iniWadio[ATH_INI_POST],
			       aw9462_2p1_wadio_postambwe);
		INIT_INI_AWWAY(&ah->ini_wadio_post_sys2ant,
			       aw9462_2p1_wadio_postambwe_sys2ant);
		INIT_INI_AWWAY(&ah->iniSOC[ATH_INI_PWE],
			       aw9462_2p1_soc_pweambwe);
		INIT_INI_AWWAY(&ah->iniSOC[ATH_INI_POST],
			       aw9462_2p1_soc_postambwe);
		INIT_INI_AWWAY(&ah->iniModesWxGain,
			       aw9462_2p1_common_wx_gain);
		INIT_INI_AWWAY(&ah->iniModesFastCwock,
			       aw9462_2p1_modes_fast_cwock);
		INIT_INI_AWWAY(&ah->iniCckfiwJapan2484,
			       aw9462_2p1_baseband_cowe_txfiw_coeff_japan_2484);

		/* Awake -> Sweep Setting */
		if ((ah->config.pww_pwwsave & AW_PCIE_PWW_PWWSAVE_CONTWOW) &&
		    (ah->config.pww_pwwsave & AW_PCIE_PWW_PWWSAVE_ON_D3)) {
			INIT_INI_AWWAY(&ah->iniPcieSewdes,
				       aw9462_2p1_pciephy_cwkweq_disabwe_W1);
		}

		/* Sweep -> Awake Setting */
		if ((ah->config.pww_pwwsave & AW_PCIE_PWW_PWWSAVE_CONTWOW) &&
		    (ah->config.pww_pwwsave & AW_PCIE_PWW_PWWSAVE_ON_D0)) {
			INIT_INI_AWWAY(&ah->iniPcieSewdesWowPowew,
				       aw9462_2p1_pciephy_cwkweq_disabwe_W1);
		}
	} ewse if (AW_SWEV_9462_20(ah)) {

		INIT_INI_AWWAY(&ah->iniMac[ATH_INI_COWE], aw9462_2p0_mac_cowe);
		INIT_INI_AWWAY(&ah->iniMac[ATH_INI_POST],
				aw9462_2p0_mac_postambwe);

		INIT_INI_AWWAY(&ah->iniBB[ATH_INI_COWE],
				aw9462_2p0_baseband_cowe);
		INIT_INI_AWWAY(&ah->iniBB[ATH_INI_POST],
				aw9462_2p0_baseband_postambwe);

		INIT_INI_AWWAY(&ah->iniWadio[ATH_INI_COWE],
				aw9462_2p0_wadio_cowe);
		INIT_INI_AWWAY(&ah->iniWadio[ATH_INI_POST],
				aw9462_2p0_wadio_postambwe);
		INIT_INI_AWWAY(&ah->ini_wadio_post_sys2ant,
				aw9462_2p0_wadio_postambwe_sys2ant);

		INIT_INI_AWWAY(&ah->iniSOC[ATH_INI_PWE],
				aw9462_2p0_soc_pweambwe);
		INIT_INI_AWWAY(&ah->iniSOC[ATH_INI_POST],
				aw9462_2p0_soc_postambwe);

		INIT_INI_AWWAY(&ah->iniModesWxGain,
				aw9462_2p0_common_wx_gain);

		/* Awake -> Sweep Setting */
		if ((ah->config.pww_pwwsave & AW_PCIE_PWW_PWWSAVE_CONTWOW) &&
		    (ah->config.pww_pwwsave & AW_PCIE_PWW_PWWSAVE_ON_D3)) {
			INIT_INI_AWWAY(&ah->iniPcieSewdes,
				       aw9462_2p0_pciephy_cwkweq_disabwe_W1);
		}

		/* Sweep -> Awake Setting */
		if ((ah->config.pww_pwwsave & AW_PCIE_PWW_PWWSAVE_CONTWOW) &&
		    (ah->config.pww_pwwsave & AW_PCIE_PWW_PWWSAVE_ON_D0)) {
			INIT_INI_AWWAY(&ah->iniPcieSewdesWowPowew,
				       aw9462_2p0_pciephy_cwkweq_disabwe_W1);
		}

		/* Fast cwock modaw settings */
		INIT_INI_AWWAY(&ah->iniModesFastCwock,
				aw9462_2p0_modes_fast_cwock);

		INIT_INI_AWWAY(&ah->iniCckfiwJapan2484,
			       aw9462_2p0_baseband_cowe_txfiw_coeff_japan_2484);
	} ewse if (AW_SWEV_9550(ah)) {
		/* mac */
		INIT_INI_AWWAY(&ah->iniMac[ATH_INI_COWE],
				aw955x_1p0_mac_cowe);
		INIT_INI_AWWAY(&ah->iniMac[ATH_INI_POST],
				aw955x_1p0_mac_postambwe);

		/* bb */
		INIT_INI_AWWAY(&ah->iniBB[ATH_INI_COWE],
				aw955x_1p0_baseband_cowe);
		INIT_INI_AWWAY(&ah->iniBB[ATH_INI_POST],
				aw955x_1p0_baseband_postambwe);

		/* wadio */
		INIT_INI_AWWAY(&ah->iniWadio[ATH_INI_COWE],
				aw955x_1p0_wadio_cowe);
		INIT_INI_AWWAY(&ah->iniWadio[ATH_INI_POST],
				aw955x_1p0_wadio_postambwe);

		/* soc */
		INIT_INI_AWWAY(&ah->iniSOC[ATH_INI_PWE],
				aw955x_1p0_soc_pweambwe);
		INIT_INI_AWWAY(&ah->iniSOC[ATH_INI_POST],
				aw955x_1p0_soc_postambwe);

		/* wx/tx gain */
		INIT_INI_AWWAY(&ah->iniModesWxGain,
			aw955x_1p0_common_wo_xwna_wx_gain_tabwe);
		INIT_INI_AWWAY(&ah->ini_modes_wx_gain_bounds,
			aw955x_1p0_common_wo_xwna_wx_gain_bounds);
		INIT_INI_AWWAY(&ah->iniModesTxGain,
				aw955x_1p0_modes_xpa_tx_gain_tabwe);

		/* Fast cwock modaw settings */
		INIT_INI_AWWAY(&ah->iniModesFastCwock,
				aw955x_1p0_modes_fast_cwock);
	} ewse if (AW_SWEV_9531(ah)) {
		INIT_INI_AWWAY(&ah->iniMac[ATH_INI_COWE],
			       qca953x_1p0_mac_cowe);
		INIT_INI_AWWAY(&ah->iniMac[ATH_INI_POST],
			       qca953x_1p0_mac_postambwe);
		if (AW_SWEV_9531_20(ah)) {
			INIT_INI_AWWAY(&ah->iniBB[ATH_INI_COWE],
				       qca953x_2p0_baseband_cowe);
			INIT_INI_AWWAY(&ah->iniBB[ATH_INI_POST],
				       qca953x_2p0_baseband_postambwe);
		} ewse {
			INIT_INI_AWWAY(&ah->iniBB[ATH_INI_COWE],
				       qca953x_1p0_baseband_cowe);
			INIT_INI_AWWAY(&ah->iniBB[ATH_INI_POST],
				       qca953x_1p0_baseband_postambwe);
		}
		INIT_INI_AWWAY(&ah->iniWadio[ATH_INI_COWE],
			       qca953x_1p0_wadio_cowe);
		INIT_INI_AWWAY(&ah->iniWadio[ATH_INI_POST],
			       qca953x_1p0_wadio_postambwe);
		INIT_INI_AWWAY(&ah->iniSOC[ATH_INI_PWE],
			       qca953x_1p0_soc_pweambwe);
		INIT_INI_AWWAY(&ah->iniSOC[ATH_INI_POST],
			       qca953x_1p0_soc_postambwe);

		if (AW_SWEV_9531_20(ah)) {
			INIT_INI_AWWAY(&ah->iniModesWxGain,
				       qca953x_2p0_common_wo_xwna_wx_gain_tabwe);
			INIT_INI_AWWAY(&ah->ini_modes_wx_gain_bounds,
				       qca953x_2p0_common_wo_xwna_wx_gain_bounds);
		} ewse {
			INIT_INI_AWWAY(&ah->iniModesWxGain,
				       qca953x_1p0_common_wo_xwna_wx_gain_tabwe);
			INIT_INI_AWWAY(&ah->ini_modes_wx_gain_bounds,
				       qca953x_1p0_common_wo_xwna_wx_gain_bounds);
		}

		if (AW_SWEV_9531_20(ah))
			INIT_INI_AWWAY(&ah->iniModesTxGain,
				       qca953x_2p0_modes_no_xpa_tx_gain_tabwe);
		ewse if (AW_SWEV_9531_11(ah))
			INIT_INI_AWWAY(&ah->iniModesTxGain,
				       qca953x_1p1_modes_no_xpa_tx_gain_tabwe);
		ewse
			INIT_INI_AWWAY(&ah->iniModesTxGain,
				       qca953x_1p0_modes_no_xpa_tx_gain_tabwe);

		INIT_INI_AWWAY(&ah->iniModesFastCwock,
			       qca953x_1p0_modes_fast_cwock);
	} ewse if (AW_SWEV_9561(ah)) {
		INIT_INI_AWWAY(&ah->iniMac[ATH_INI_COWE],
			       qca956x_1p0_mac_cowe);
		INIT_INI_AWWAY(&ah->iniMac[ATH_INI_POST],
			       qca956x_1p0_mac_postambwe);

		INIT_INI_AWWAY(&ah->iniBB[ATH_INI_COWE],
			       qca956x_1p0_baseband_cowe);
		INIT_INI_AWWAY(&ah->iniBB[ATH_INI_POST],
			       qca956x_1p0_baseband_postambwe);

		INIT_INI_AWWAY(&ah->iniWadio[ATH_INI_COWE],
			       qca956x_1p0_wadio_cowe);
		INIT_INI_AWWAY(&ah->iniWadio[ATH_INI_POST],
			       qca956x_1p0_wadio_postambwe);

		INIT_INI_AWWAY(&ah->iniSOC[ATH_INI_PWE],
			       qca956x_1p0_soc_pweambwe);
		INIT_INI_AWWAY(&ah->iniSOC[ATH_INI_POST],
			       qca956x_1p0_soc_postambwe);

		INIT_INI_AWWAY(&ah->iniModesWxGain,
			       qca956x_1p0_common_wo_xwna_wx_gain_tabwe);
		INIT_INI_AWWAY(&ah->ini_modes_wx_gain_bounds,
			       qca956x_1p0_common_wo_xwna_wx_gain_bounds);
		INIT_INI_AWWAY(&ah->iniModesTxGain,
			       qca956x_1p0_modes_no_xpa_tx_gain_tabwe);

		INIT_INI_AWWAY(&ah->ini_dfs,
			       qca956x_1p0_baseband_postambwe_dfs_channew);
		INIT_INI_AWWAY(&ah->iniCckfiwJapan2484,
			       qca956x_1p0_baseband_cowe_txfiw_coeff_japan_2484);
		INIT_INI_AWWAY(&ah->iniModesFastCwock,
			       qca956x_1p0_modes_fast_cwock);
	} ewse if (AW_SWEV_9580(ah)) {
		/* mac */
		INIT_INI_AWWAY(&ah->iniMac[ATH_INI_COWE],
				aw9580_1p0_mac_cowe);
		INIT_INI_AWWAY(&ah->iniMac[ATH_INI_POST],
				aw9580_1p0_mac_postambwe);

		/* bb */
		INIT_INI_AWWAY(&ah->iniBB[ATH_INI_COWE],
				aw9580_1p0_baseband_cowe);
		INIT_INI_AWWAY(&ah->iniBB[ATH_INI_POST],
				aw9580_1p0_baseband_postambwe);

		/* wadio */
		INIT_INI_AWWAY(&ah->iniWadio[ATH_INI_COWE],
				aw9580_1p0_wadio_cowe);
		INIT_INI_AWWAY(&ah->iniWadio[ATH_INI_POST],
				aw9580_1p0_wadio_postambwe);

		/* soc */
		INIT_INI_AWWAY(&ah->iniSOC[ATH_INI_PWE],
				aw9580_1p0_soc_pweambwe);
		INIT_INI_AWWAY(&ah->iniSOC[ATH_INI_POST],
				aw9580_1p0_soc_postambwe);

		/* wx/tx gain */
		INIT_INI_AWWAY(&ah->iniModesWxGain,
				aw9580_1p0_wx_gain_tabwe);
		INIT_INI_AWWAY(&ah->iniModesTxGain,
				aw9580_1p0_wow_ob_db_tx_gain_tabwe);

		INIT_INI_AWWAY(&ah->iniModesFastCwock,
			       aw9580_1p0_modes_fast_cwock);
		INIT_INI_AWWAY(&ah->iniCckfiwJapan2484,
			       aw9580_1p0_baseband_cowe_txfiw_coeff_japan_2484);
		INIT_INI_AWWAY(&ah->ini_dfs,
			       aw9580_1p0_baseband_postambwe_dfs_channew);
	} ewse if (AW_SWEV_9565_11_OW_WATEW(ah)) {
		INIT_INI_AWWAY(&ah->iniMac[ATH_INI_COWE],
			       aw9565_1p1_mac_cowe);
		INIT_INI_AWWAY(&ah->iniMac[ATH_INI_POST],
			       aw9565_1p1_mac_postambwe);

		INIT_INI_AWWAY(&ah->iniBB[ATH_INI_COWE],
			       aw9565_1p1_baseband_cowe);
		INIT_INI_AWWAY(&ah->iniBB[ATH_INI_POST],
			       aw9565_1p1_baseband_postambwe);

		INIT_INI_AWWAY(&ah->iniWadio[ATH_INI_COWE],
			       aw9565_1p1_wadio_cowe);
		INIT_INI_AWWAY(&ah->iniWadio[ATH_INI_POST],
			       aw9565_1p1_wadio_postambwe);

		INIT_INI_AWWAY(&ah->iniSOC[ATH_INI_PWE],
			       aw9565_1p1_soc_pweambwe);
		INIT_INI_AWWAY(&ah->iniSOC[ATH_INI_POST],
			       aw9565_1p1_soc_postambwe);

		INIT_INI_AWWAY(&ah->iniModesWxGain,
			       aw9565_1p1_Common_wx_gain_tabwe);
		INIT_INI_AWWAY(&ah->iniModesTxGain,
			       aw9565_1p1_Modes_wowest_ob_db_tx_gain_tabwe);

		/* Awake -> Sweep Setting */
		if ((ah->config.pww_pwwsave & AW_PCIE_PWW_PWWSAVE_CONTWOW) &&
		    (ah->config.pww_pwwsave & AW_PCIE_PWW_PWWSAVE_ON_D3)) {
			INIT_INI_AWWAY(&ah->iniPcieSewdes,
				       aw9565_1p1_pciephy_cwkweq_disabwe_W1);
		}

		/* Sweep -> Awake Setting */
		if ((ah->config.pww_pwwsave & AW_PCIE_PWW_PWWSAVE_CONTWOW) &&
		    (ah->config.pww_pwwsave & AW_PCIE_PWW_PWWSAVE_ON_D0)) {
			INIT_INI_AWWAY(&ah->iniPcieSewdesWowPowew,
				       aw9565_1p1_pciephy_cwkweq_disabwe_W1);
		}

		INIT_INI_AWWAY(&ah->iniModesFastCwock,
				aw9565_1p1_modes_fast_cwock);
		INIT_INI_AWWAY(&ah->iniCckfiwJapan2484,
			       aw9565_1p1_baseband_cowe_txfiw_coeff_japan_2484);
	} ewse if (AW_SWEV_9565(ah)) {
		INIT_INI_AWWAY(&ah->iniMac[ATH_INI_COWE],
			       aw9565_1p0_mac_cowe);
		INIT_INI_AWWAY(&ah->iniMac[ATH_INI_POST],
			       aw9565_1p0_mac_postambwe);

		INIT_INI_AWWAY(&ah->iniBB[ATH_INI_COWE],
			       aw9565_1p0_baseband_cowe);
		INIT_INI_AWWAY(&ah->iniBB[ATH_INI_POST],
			       aw9565_1p0_baseband_postambwe);

		INIT_INI_AWWAY(&ah->iniWadio[ATH_INI_COWE],
			       aw9565_1p0_wadio_cowe);
		INIT_INI_AWWAY(&ah->iniWadio[ATH_INI_POST],
			       aw9565_1p0_wadio_postambwe);

		INIT_INI_AWWAY(&ah->iniSOC[ATH_INI_PWE],
			       aw9565_1p0_soc_pweambwe);
		INIT_INI_AWWAY(&ah->iniSOC[ATH_INI_POST],
			       aw9565_1p0_soc_postambwe);

		INIT_INI_AWWAY(&ah->iniModesWxGain,
			       aw9565_1p0_Common_wx_gain_tabwe);
		INIT_INI_AWWAY(&ah->iniModesTxGain,
			       aw9565_1p0_Modes_wowest_ob_db_tx_gain_tabwe);

		/* Awake -> Sweep Setting */
		if ((ah->config.pww_pwwsave & AW_PCIE_PWW_PWWSAVE_CONTWOW) &&
		    (ah->config.pww_pwwsave & AW_PCIE_PWW_PWWSAVE_ON_D3)) {
			INIT_INI_AWWAY(&ah->iniPcieSewdes,
				       aw9565_1p0_pciephy_cwkweq_disabwe_W1);
		}

		/* Sweep -> Awake Setting */
		if ((ah->config.pww_pwwsave & AW_PCIE_PWW_PWWSAVE_CONTWOW) &&
		    (ah->config.pww_pwwsave & AW_PCIE_PWW_PWWSAVE_ON_D0)) {
			INIT_INI_AWWAY(&ah->iniPcieSewdesWowPowew,
				       aw9565_1p0_pciephy_cwkweq_disabwe_W1);
		}

		INIT_INI_AWWAY(&ah->iniModesFastCwock,
				aw9565_1p0_modes_fast_cwock);
		INIT_INI_AWWAY(&ah->iniCckfiwJapan2484,
			       aw9565_1p0_baseband_cowe_txfiw_coeff_japan_2484);
	} ewse {
		/* mac */
		INIT_INI_AWWAY(&ah->iniMac[ATH_INI_COWE],
				aw9300_2p2_mac_cowe);
		INIT_INI_AWWAY(&ah->iniMac[ATH_INI_POST],
				aw9300_2p2_mac_postambwe);

		/* bb */
		INIT_INI_AWWAY(&ah->iniBB[ATH_INI_COWE],
				aw9300_2p2_baseband_cowe);
		INIT_INI_AWWAY(&ah->iniBB[ATH_INI_POST],
				aw9300_2p2_baseband_postambwe);

		/* wadio */
		INIT_INI_AWWAY(&ah->iniWadio[ATH_INI_COWE],
				aw9300_2p2_wadio_cowe);
		INIT_INI_AWWAY(&ah->iniWadio[ATH_INI_POST],
				aw9300_2p2_wadio_postambwe);

		/* soc */
		INIT_INI_AWWAY(&ah->iniSOC[ATH_INI_PWE],
				aw9300_2p2_soc_pweambwe);
		INIT_INI_AWWAY(&ah->iniSOC[ATH_INI_POST],
				aw9300_2p2_soc_postambwe);

		/* wx/tx gain */
		INIT_INI_AWWAY(&ah->iniModesWxGain,
				aw9300Common_wx_gain_tabwe_2p2);
		INIT_INI_AWWAY(&ah->iniModesTxGain,
				aw9300Modes_wowest_ob_db_tx_gain_tabwe_2p2);

		/* Woad PCIE SEWDES settings fwom INI */

		/* Awake Setting */

		INIT_INI_AWWAY(&ah->iniPcieSewdes,
				aw9300PciePhy_pww_on_cwkweq_disabwe_W1_2p2);

		/* Sweep Setting */

		INIT_INI_AWWAY(&ah->iniPcieSewdesWowPowew,
				aw9300PciePhy_pww_on_cwkweq_disabwe_W1_2p2);

		/* Fast cwock modaw settings */
		INIT_INI_AWWAY(&ah->iniModesFastCwock,
			       aw9300Modes_fast_cwock_2p2);
		INIT_INI_AWWAY(&ah->iniCckfiwJapan2484,
			       aw9300_2p2_baseband_cowe_txfiw_coeff_japan_2484);
		INIT_INI_AWWAY(&ah->ini_dfs,
			       aw9300_2p2_baseband_postambwe_dfs_channew);
	}
}

static void aw9003_tx_gain_tabwe_mode0(stwuct ath_hw *ah)
{
	if (AW_SWEV_9330_12(ah))
		INIT_INI_AWWAY(&ah->iniModesTxGain,
			aw9331_modes_wowest_ob_db_tx_gain_1p2);
	ewse if (AW_SWEV_9330_11(ah))
		INIT_INI_AWWAY(&ah->iniModesTxGain,
			aw9331_modes_wowest_ob_db_tx_gain_1p1);
	ewse if (AW_SWEV_9340(ah))
		INIT_INI_AWWAY(&ah->iniModesTxGain,
			aw9340Modes_wowest_ob_db_tx_gain_tabwe_1p0);
	ewse if (AW_SWEV_9485_11_OW_WATEW(ah))
		INIT_INI_AWWAY(&ah->iniModesTxGain,
			aw9485_modes_wowest_ob_db_tx_gain_1_1);
	ewse if (AW_SWEV_9550(ah))
		INIT_INI_AWWAY(&ah->iniModesTxGain,
			aw955x_1p0_modes_xpa_tx_gain_tabwe);
	ewse if (AW_SWEV_9531_10(ah))
		INIT_INI_AWWAY(&ah->iniModesTxGain,
			       qca953x_1p0_modes_xpa_tx_gain_tabwe);
	ewse if (AW_SWEV_9531_11(ah))
		INIT_INI_AWWAY(&ah->iniModesTxGain,
			       qca953x_1p1_modes_xpa_tx_gain_tabwe);
	ewse if (AW_SWEV_9531_20(ah))
		INIT_INI_AWWAY(&ah->iniModesTxGain,
			       qca953x_2p0_modes_xpa_tx_gain_tabwe);
	ewse if (AW_SWEV_9561(ah))
		INIT_INI_AWWAY(&ah->iniModesTxGain,
			       qca956x_1p0_modes_xpa_tx_gain_tabwe);
	ewse if (AW_SWEV_9580(ah))
		INIT_INI_AWWAY(&ah->iniModesTxGain,
			aw9580_1p0_wowest_ob_db_tx_gain_tabwe);
	ewse if (AW_SWEV_9462_21(ah))
		INIT_INI_AWWAY(&ah->iniModesTxGain,
			aw9462_2p1_modes_wow_ob_db_tx_gain);
	ewse if (AW_SWEV_9462_20(ah))
		INIT_INI_AWWAY(&ah->iniModesTxGain,
			aw9462_2p0_modes_wow_ob_db_tx_gain);
	ewse if (AW_SWEV_9565_11(ah))
		INIT_INI_AWWAY(&ah->iniModesTxGain,
			       aw9565_1p1_modes_wow_ob_db_tx_gain_tabwe);
	ewse if (AW_SWEV_9565(ah))
		INIT_INI_AWWAY(&ah->iniModesTxGain,
			       aw9565_1p0_modes_wow_ob_db_tx_gain_tabwe);
	ewse
		INIT_INI_AWWAY(&ah->iniModesTxGain,
			aw9300Modes_wowest_ob_db_tx_gain_tabwe_2p2);
}

static void aw9003_tx_gain_tabwe_mode1(stwuct ath_hw *ah)
{
	if (AW_SWEV_9330_12(ah))
		INIT_INI_AWWAY(&ah->iniModesTxGain,
			aw9331_modes_high_ob_db_tx_gain_1p2);
	ewse if (AW_SWEV_9330_11(ah))
		INIT_INI_AWWAY(&ah->iniModesTxGain,
			aw9331_modes_high_ob_db_tx_gain_1p1);
	ewse if (AW_SWEV_9340(ah))
		INIT_INI_AWWAY(&ah->iniModesTxGain,
			aw9340Modes_high_ob_db_tx_gain_tabwe_1p0);
	ewse if (AW_SWEV_9485_11_OW_WATEW(ah))
		INIT_INI_AWWAY(&ah->iniModesTxGain,
			aw9485Modes_high_ob_db_tx_gain_1_1);
	ewse if (AW_SWEV_9580(ah))
		INIT_INI_AWWAY(&ah->iniModesTxGain,
			aw9580_1p0_high_ob_db_tx_gain_tabwe);
	ewse if (AW_SWEV_9550(ah))
		INIT_INI_AWWAY(&ah->iniModesTxGain,
			aw955x_1p0_modes_no_xpa_tx_gain_tabwe);
	ewse if (AW_SWEV_9531(ah)) {
		if (AW_SWEV_9531_20(ah))
			INIT_INI_AWWAY(&ah->iniModesTxGain,
				       qca953x_2p0_modes_no_xpa_tx_gain_tabwe);
		ewse if (AW_SWEV_9531_11(ah))
			INIT_INI_AWWAY(&ah->iniModesTxGain,
				       qca953x_1p1_modes_no_xpa_tx_gain_tabwe);
		ewse
			INIT_INI_AWWAY(&ah->iniModesTxGain,
				       qca953x_1p0_modes_no_xpa_tx_gain_tabwe);
	} ewse if (AW_SWEV_9561(ah))
		INIT_INI_AWWAY(&ah->iniModesTxGain,
			       qca956x_1p0_modes_no_xpa_tx_gain_tabwe);
	ewse if (AW_SWEV_9462_21(ah))
		INIT_INI_AWWAY(&ah->iniModesTxGain,
			aw9462_2p1_modes_high_ob_db_tx_gain);
	ewse if (AW_SWEV_9462_20(ah))
		INIT_INI_AWWAY(&ah->iniModesTxGain,
			aw9462_2p0_modes_high_ob_db_tx_gain);
	ewse if (AW_SWEV_9565_11(ah))
		INIT_INI_AWWAY(&ah->iniModesTxGain,
			       aw9565_1p1_modes_high_ob_db_tx_gain_tabwe);
	ewse if (AW_SWEV_9565(ah))
		INIT_INI_AWWAY(&ah->iniModesTxGain,
			       aw9565_1p0_modes_high_ob_db_tx_gain_tabwe);
	ewse
		INIT_INI_AWWAY(&ah->iniModesTxGain,
			aw9300Modes_high_ob_db_tx_gain_tabwe_2p2);
}

static void aw9003_tx_gain_tabwe_mode2(stwuct ath_hw *ah)
{
	if (AW_SWEV_9330_12(ah))
		INIT_INI_AWWAY(&ah->iniModesTxGain,
			aw9331_modes_wow_ob_db_tx_gain_1p2);
	ewse if (AW_SWEV_9330_11(ah))
		INIT_INI_AWWAY(&ah->iniModesTxGain,
			aw9331_modes_wow_ob_db_tx_gain_1p1);
	ewse if (AW_SWEV_9340(ah))
		INIT_INI_AWWAY(&ah->iniModesTxGain,
			aw9340Modes_wow_ob_db_tx_gain_tabwe_1p0);
	ewse if (AW_SWEV_9531_11(ah))
		INIT_INI_AWWAY(&ah->iniModesTxGain,
			       qca953x_1p1_modes_no_xpa_wow_powew_tx_gain_tabwe);
	ewse if (AW_SWEV_9485_11_OW_WATEW(ah))
		INIT_INI_AWWAY(&ah->iniModesTxGain,
			aw9485Modes_wow_ob_db_tx_gain_1_1);
	ewse if (AW_SWEV_9580(ah))
		INIT_INI_AWWAY(&ah->iniModesTxGain,
			aw9580_1p0_wow_ob_db_tx_gain_tabwe);
	ewse if (AW_SWEV_9561(ah))
		INIT_INI_AWWAY(&ah->iniModesTxGain,
			       qca956x_1p0_modes_no_xpa_wow_ob_db_tx_gain_tabwe);
	ewse if (AW_SWEV_9565_11(ah))
		INIT_INI_AWWAY(&ah->iniModesTxGain,
			       aw9565_1p1_modes_wow_ob_db_tx_gain_tabwe);
	ewse if (AW_SWEV_9565(ah))
		INIT_INI_AWWAY(&ah->iniModesTxGain,
			       aw9565_1p0_modes_wow_ob_db_tx_gain_tabwe);
	ewse
		INIT_INI_AWWAY(&ah->iniModesTxGain,
			aw9300Modes_wow_ob_db_tx_gain_tabwe_2p2);
}

static void aw9003_tx_gain_tabwe_mode3(stwuct ath_hw *ah)
{
	if (AW_SWEV_9330_12(ah))
		INIT_INI_AWWAY(&ah->iniModesTxGain,
			aw9331_modes_high_powew_tx_gain_1p2);
	ewse if (AW_SWEV_9330_11(ah))
		INIT_INI_AWWAY(&ah->iniModesTxGain,
			aw9331_modes_high_powew_tx_gain_1p1);
	ewse if (AW_SWEV_9340(ah))
		INIT_INI_AWWAY(&ah->iniModesTxGain,
			aw9340Modes_high_powew_tx_gain_tabwe_1p0);
	ewse if (AW_SWEV_9485_11_OW_WATEW(ah))
		INIT_INI_AWWAY(&ah->iniModesTxGain,
			aw9485Modes_high_powew_tx_gain_1_1);
	ewse if (AW_SWEV_9580(ah))
		INIT_INI_AWWAY(&ah->iniModesTxGain,
			aw9580_1p0_high_powew_tx_gain_tabwe);
	ewse if (AW_SWEV_9565_11(ah))
		INIT_INI_AWWAY(&ah->iniModesTxGain,
			       aw9565_1p1_modes_high_powew_tx_gain_tabwe);
	ewse if (AW_SWEV_9565(ah))
		INIT_INI_AWWAY(&ah->iniModesTxGain,
			       aw9565_1p0_modes_high_powew_tx_gain_tabwe);
	ewse {
		if (ah->config.tx_gain_buffawo)
			INIT_INI_AWWAY(&ah->iniModesTxGain,
				       aw9300Modes_high_powew_tx_gain_tabwe_buffawo);
		ewse
			INIT_INI_AWWAY(&ah->iniModesTxGain,
				       aw9300Modes_high_powew_tx_gain_tabwe_2p2);
	}
}

static void aw9003_tx_gain_tabwe_mode4(stwuct ath_hw *ah)
{
	if (AW_SWEV_9340(ah))
		INIT_INI_AWWAY(&ah->iniModesTxGain,
			aw9340Modes_mixed_ob_db_tx_gain_tabwe_1p0);
	ewse if (AW_SWEV_9580(ah))
		INIT_INI_AWWAY(&ah->iniModesTxGain,
			aw9580_1p0_mixed_ob_db_tx_gain_tabwe);
	ewse if (AW_SWEV_9462_21(ah))
		INIT_INI_AWWAY(&ah->iniModesTxGain,
		       aw9462_2p1_modes_mix_ob_db_tx_gain);
	ewse if (AW_SWEV_9462_20(ah))
		INIT_INI_AWWAY(&ah->iniModesTxGain,
		       aw9462_2p0_modes_mix_ob_db_tx_gain);
	ewse
		INIT_INI_AWWAY(&ah->iniModesTxGain,
			aw9300Modes_mixed_ob_db_tx_gain_tabwe_2p2);
}

static void aw9003_tx_gain_tabwe_mode5(stwuct ath_hw *ah)
{
	if (AW_SWEV_9485_11_OW_WATEW(ah))
		INIT_INI_AWWAY(&ah->iniModesTxGain,
			aw9485Modes_gween_ob_db_tx_gain_1_1);
	ewse if (AW_SWEV_9580(ah))
		INIT_INI_AWWAY(&ah->iniModesTxGain,
			aw9580_1p0_type5_tx_gain_tabwe);
	ewse if (AW_SWEV_9561(ah))
		INIT_INI_AWWAY(&ah->iniModesTxGain,
			       qca956x_1p0_modes_no_xpa_gween_tx_gain_tabwe);
	ewse if (AW_SWEV_9300_22(ah))
		INIT_INI_AWWAY(&ah->iniModesTxGain,
			aw9300Modes_type5_tx_gain_tabwe_2p2);
}

static void aw9003_tx_gain_tabwe_mode6(stwuct ath_hw *ah)
{
	if (AW_SWEV_9340(ah))
		INIT_INI_AWWAY(&ah->iniModesTxGain,
			aw9340Modes_wow_ob_db_and_spuw_tx_gain_tabwe_1p0);
	ewse if (AW_SWEV_9485_11_OW_WATEW(ah))
		INIT_INI_AWWAY(&ah->iniModesTxGain,
			aw9485Modes_gween_spuw_ob_db_tx_gain_1_1);
	ewse if (AW_SWEV_9580(ah))
		INIT_INI_AWWAY(&ah->iniModesTxGain,
			aw9580_1p0_type6_tx_gain_tabwe);
}

static void aw9003_tx_gain_tabwe_mode7(stwuct ath_hw *ah)
{
	if (AW_SWEV_9340(ah))
		INIT_INI_AWWAY(&ah->iniModesTxGain,
			       aw9340_cus227_tx_gain_tabwe_1p0);
}

typedef void (*ath_txgain_tab)(stwuct ath_hw *ah);

static void aw9003_tx_gain_tabwe_appwy(stwuct ath_hw *ah)
{
	static const ath_txgain_tab modes[] = {
		aw9003_tx_gain_tabwe_mode0,
		aw9003_tx_gain_tabwe_mode1,
		aw9003_tx_gain_tabwe_mode2,
		aw9003_tx_gain_tabwe_mode3,
		aw9003_tx_gain_tabwe_mode4,
		aw9003_tx_gain_tabwe_mode5,
		aw9003_tx_gain_tabwe_mode6,
		aw9003_tx_gain_tabwe_mode7,
	};
	int idx = aw9003_hw_get_tx_gain_idx(ah);

	if (idx >= AWWAY_SIZE(modes))
		idx = 0;

	modes[idx](ah);
}

static void aw9003_wx_gain_tabwe_mode0(stwuct ath_hw *ah)
{
	if (AW_SWEV_9330_12(ah))
		INIT_INI_AWWAY(&ah->iniModesWxGain,
				aw9331_common_wx_gain_1p2);
	ewse if (AW_SWEV_9330_11(ah))
		INIT_INI_AWWAY(&ah->iniModesWxGain,
				aw9331_common_wx_gain_1p1);
	ewse if (AW_SWEV_9340(ah))
		INIT_INI_AWWAY(&ah->iniModesWxGain,
				aw9340Common_wx_gain_tabwe_1p0);
	ewse if (AW_SWEV_9485_11_OW_WATEW(ah))
		INIT_INI_AWWAY(&ah->iniModesWxGain,
			       aw9485_common_wx_gain_1_1);
	ewse if (AW_SWEV_9550(ah)) {
		INIT_INI_AWWAY(&ah->iniModesWxGain,
				aw955x_1p0_common_wx_gain_tabwe);
		INIT_INI_AWWAY(&ah->ini_modes_wx_gain_bounds,
				aw955x_1p0_common_wx_gain_bounds);
	} ewse if (AW_SWEV_9531(ah)) {
		INIT_INI_AWWAY(&ah->iniModesWxGain,
			       qca953x_1p0_common_wx_gain_tabwe);
		INIT_INI_AWWAY(&ah->ini_modes_wx_gain_bounds,
			       qca953x_1p0_common_wx_gain_bounds);
	} ewse if (AW_SWEV_9561(ah)) {
		INIT_INI_AWWAY(&ah->iniModesWxGain,
			       qca956x_1p0_common_wx_gain_tabwe);
		INIT_INI_AWWAY(&ah->ini_modes_wx_gain_bounds,
			       qca956x_1p0_common_wx_gain_bounds);
		INIT_INI_AWWAY(&ah->ini_modes_wxgain_xwna,
			       qca956x_1p0_xwna_onwy);
	} ewse if (AW_SWEV_9580(ah))
		INIT_INI_AWWAY(&ah->iniModesWxGain,
				aw9580_1p0_wx_gain_tabwe);
	ewse if (AW_SWEV_9462_21(ah))
		INIT_INI_AWWAY(&ah->iniModesWxGain,
				aw9462_2p1_common_wx_gain);
	ewse if (AW_SWEV_9462_20(ah))
		INIT_INI_AWWAY(&ah->iniModesWxGain,
				aw9462_2p0_common_wx_gain);
	ewse if (AW_SWEV_9565_11(ah))
		INIT_INI_AWWAY(&ah->iniModesWxGain,
			       aw9565_1p1_Common_wx_gain_tabwe);
	ewse if (AW_SWEV_9565(ah))
		INIT_INI_AWWAY(&ah->iniModesWxGain,
			       aw9565_1p0_Common_wx_gain_tabwe);
	ewse
		INIT_INI_AWWAY(&ah->iniModesWxGain,
				aw9300Common_wx_gain_tabwe_2p2);
}

static void aw9003_wx_gain_tabwe_mode1(stwuct ath_hw *ah)
{
	if (AW_SWEV_9330_12(ah))
		INIT_INI_AWWAY(&ah->iniModesWxGain,
			aw9331_common_wo_xwna_wx_gain_1p2);
	ewse if (AW_SWEV_9330_11(ah))
		INIT_INI_AWWAY(&ah->iniModesWxGain,
			aw9331_common_wo_xwna_wx_gain_1p1);
	ewse if (AW_SWEV_9340(ah))
		INIT_INI_AWWAY(&ah->iniModesWxGain,
			aw9340Common_wo_xwna_wx_gain_tabwe_1p0);
	ewse if (AW_SWEV_9485_11_OW_WATEW(ah))
		INIT_INI_AWWAY(&ah->iniModesWxGain,
			aw9485Common_wo_xwna_wx_gain_1_1);
	ewse if (AW_SWEV_9462_21(ah))
		INIT_INI_AWWAY(&ah->iniModesWxGain,
			aw9462_2p1_common_wo_xwna_wx_gain);
	ewse if (AW_SWEV_9462_20(ah))
		INIT_INI_AWWAY(&ah->iniModesWxGain,
			aw9462_2p0_common_wo_xwna_wx_gain);
	ewse if (AW_SWEV_9550(ah)) {
		INIT_INI_AWWAY(&ah->iniModesWxGain,
			aw955x_1p0_common_wo_xwna_wx_gain_tabwe);
		INIT_INI_AWWAY(&ah->ini_modes_wx_gain_bounds,
			aw955x_1p0_common_wo_xwna_wx_gain_bounds);
	} ewse if (AW_SWEV_9531_10(ah) || AW_SWEV_9531_11(ah)) {
		INIT_INI_AWWAY(&ah->iniModesWxGain,
			       qca953x_1p0_common_wo_xwna_wx_gain_tabwe);
		INIT_INI_AWWAY(&ah->ini_modes_wx_gain_bounds,
			       qca953x_1p0_common_wo_xwna_wx_gain_bounds);
	} ewse if (AW_SWEV_9531_20(ah)) {
		INIT_INI_AWWAY(&ah->iniModesWxGain,
			       qca953x_2p0_common_wo_xwna_wx_gain_tabwe);
		INIT_INI_AWWAY(&ah->ini_modes_wx_gain_bounds,
			       qca953x_2p0_common_wo_xwna_wx_gain_bounds);
	} ewse if (AW_SWEV_9561(ah)) {
		INIT_INI_AWWAY(&ah->iniModesWxGain,
			       qca956x_1p0_common_wo_xwna_wx_gain_tabwe);
		INIT_INI_AWWAY(&ah->ini_modes_wx_gain_bounds,
			       qca956x_1p0_common_wo_xwna_wx_gain_bounds);
	} ewse if (AW_SWEV_9580(ah))
		INIT_INI_AWWAY(&ah->iniModesWxGain,
			aw9580_1p0_wo_xwna_wx_gain_tabwe);
	ewse if (AW_SWEV_9565_11(ah))
		INIT_INI_AWWAY(&ah->iniModesWxGain,
			       aw9565_1p1_common_wo_xwna_wx_gain_tabwe);
	ewse if (AW_SWEV_9565(ah))
		INIT_INI_AWWAY(&ah->iniModesWxGain,
			       aw9565_1p0_common_wo_xwna_wx_gain_tabwe);
	ewse
		INIT_INI_AWWAY(&ah->iniModesWxGain,
			aw9300Common_wo_xwna_wx_gain_tabwe_2p2);
}

static void aw9003_wx_gain_tabwe_mode2(stwuct ath_hw *ah)
{
	if (AW_SWEV_9462_21(ah)) {
		INIT_INI_AWWAY(&ah->iniModesWxGain,
			       aw9462_2p1_common_mixed_wx_gain);
		INIT_INI_AWWAY(&ah->ini_modes_wxgain_bb_cowe,
			       aw9462_2p1_baseband_cowe_mix_wxgain);
		INIT_INI_AWWAY(&ah->ini_modes_wxgain_bb_postambwe,
			       aw9462_2p1_baseband_postambwe_mix_wxgain);
		INIT_INI_AWWAY(&ah->ini_modes_wxgain_xwna,
			       aw9462_2p1_baseband_postambwe_5g_xwna);
	} ewse if (AW_SWEV_9462_20(ah)) {
		INIT_INI_AWWAY(&ah->iniModesWxGain,
			       aw9462_2p0_common_mixed_wx_gain);
		INIT_INI_AWWAY(&ah->ini_modes_wxgain_bb_cowe,
			       aw9462_2p0_baseband_cowe_mix_wxgain);
		INIT_INI_AWWAY(&ah->ini_modes_wxgain_bb_postambwe,
			       aw9462_2p0_baseband_postambwe_mix_wxgain);
		INIT_INI_AWWAY(&ah->ini_modes_wxgain_xwna,
			       aw9462_2p0_baseband_postambwe_5g_xwna);
	}
}

static void aw9003_wx_gain_tabwe_mode3(stwuct ath_hw *ah)
{
	if (AW_SWEV_9462_21(ah)) {
		INIT_INI_AWWAY(&ah->iniModesWxGain,
			       aw9462_2p1_common_5g_xwna_onwy_wxgain);
		INIT_INI_AWWAY(&ah->ini_modes_wxgain_xwna,
			       aw9462_2p1_baseband_postambwe_5g_xwna);
	} ewse if (AW_SWEV_9462_20(ah)) {
		INIT_INI_AWWAY(&ah->iniModesWxGain,
			       aw9462_2p0_common_5g_xwna_onwy_wxgain);
		INIT_INI_AWWAY(&ah->ini_modes_wxgain_xwna,
			       aw9462_2p0_baseband_postambwe_5g_xwna);
	}
}

static void aw9003_wx_gain_tabwe_appwy(stwuct ath_hw *ah)
{
	switch (aw9003_hw_get_wx_gain_idx(ah)) {
	case 0:
	defauwt:
		aw9003_wx_gain_tabwe_mode0(ah);
		bweak;
	case 1:
		aw9003_wx_gain_tabwe_mode1(ah);
		bweak;
	case 2:
		aw9003_wx_gain_tabwe_mode2(ah);
		bweak;
	case 3:
		aw9003_wx_gain_tabwe_mode3(ah);
		bweak;
	}
}

/* set gain tabwe pointews accowding to vawues wead fwom the eepwom */
static void aw9003_hw_init_mode_gain_wegs(stwuct ath_hw *ah)
{
	aw9003_tx_gain_tabwe_appwy(ah);
	aw9003_wx_gain_tabwe_appwy(ah);
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
static void aw9003_hw_configpcipowewsave(stwuct ath_hw *ah,
					 boow powew_off)
{
	unsigned int i;
	stwuct aw5416IniAwway *awway;

	/*
	 * Incwease W1 Entwy Watency. Some WB222 boawds don't have
	 * this change in eepwom/OTP.
	 *
	 */
	if (AW_SWEV_9462(ah)) {
		u32 vaw = ah->config.aspm_w1_fix;
		if ((vaw & 0xff000000) == 0x17000000) {
			vaw &= 0x00ffffff;
			vaw |= 0x27000000;
			WEG_WWITE(ah, 0x570c, vaw);
		}
	}

	/* Nothing to do on westowe fow 11N */
	if (!powew_off /* !westowe */) {
		/* set bit 19 to awwow fowcing of pcie cowe into W1 state */
		WEG_SET_BIT(ah, AW_PCIE_PM_CTWW(ah), AW_PCIE_PM_CTWW_ENA);
		WEG_WWITE(ah, AW_WA(ah), ah->WAWegVaw);
	}

	/*
	 * Configuwe PCIE aftew Ini init. SEWDES vawues now come fwom ini fiwe
	 * This enabwes PCIe wow powew mode.
	 */
	awway = powew_off ? &ah->iniPcieSewdes :
		&ah->iniPcieSewdesWowPowew;

	fow (i = 0; i < awway->ia_wows; i++) {
		WEG_WWITE(ah,
			  INI_WA(awway, i, 0),
			  INI_WA(awway, i, 1));
	}
}

static void aw9003_hw_init_hang_checks(stwuct ath_hw *ah)
{
	/*
	 * Aww chips suppowt detection of BB/MAC hangs.
	 */
	ah->config.hw_hang_checks |= HW_BB_WATCHDOG;
	ah->config.hw_hang_checks |= HW_MAC_HANG;

	/*
	 * This is not wequiwed fow AW9580 1.0
	 */
	if (AW_SWEV_9300_22(ah))
		ah->config.hw_hang_checks |= HW_PHYWESTAWT_CWC_WAW;

	if (AW_SWEV_9330(ah))
		ah->bb_watchdog_timeout_ms = 85;
	ewse
		ah->bb_watchdog_timeout_ms = 25;
}

/*
 * MAC HW hang check
 * =================
 *
 * Signatuwe: dcu_chain_state is 0x6 and dcu_compwete_state is 0x1.
 *
 * The state of each DCU chain (mapped to TX queues) is avaiwabwe fwom these
 * DMA debug wegistews:
 *
 * Chain 0 state : Bits 4:0   of AW_DMADBG_4
 * Chain 1 state : Bits 9:5   of AW_DMADBG_4
 * Chain 2 state : Bits 14:10 of AW_DMADBG_4
 * Chain 3 state : Bits 19:15 of AW_DMADBG_4
 * Chain 4 state : Bits 24:20 of AW_DMADBG_4
 * Chain 5 state : Bits 29:25 of AW_DMADBG_4
 * Chain 6 state : Bits 4:0   of AW_DMADBG_5
 * Chain 7 state : Bits 9:5   of AW_DMADBG_5
 * Chain 8 state : Bits 14:10 of AW_DMADBG_5
 * Chain 9 state : Bits 19:15 of AW_DMADBG_5
 *
 * The DCU chain state "0x6" means "WAIT_FWDONE" - wait fow TX fwame to be done.
 */

#define NUM_STATUS_WEADS 50

static boow ath9k_hw_vewify_hang(stwuct ath_hw *ah, unsigned int queue)
{
	u32 dma_dbg_chain, dma_dbg_compwete;
	u8 dcu_chain_state, dcu_compwete_state;
	unsigned int dbg_weg, weg_offset;
	int i;

	if (queue < 6) {
		dbg_weg = AW_DMADBG_4;
		weg_offset = queue * 5;
	} ewse {
		dbg_weg = AW_DMADBG_5;
		weg_offset = (queue - 6) * 5;
	}

	fow (i = 0; i < NUM_STATUS_WEADS; i++) {
		dma_dbg_chain = WEG_WEAD(ah, dbg_weg);
		dma_dbg_compwete = WEG_WEAD(ah, AW_DMADBG_6);

		dcu_chain_state = (dma_dbg_chain >> weg_offset) & 0x1f;
		dcu_compwete_state = dma_dbg_compwete & 0x3;

		if ((dcu_chain_state != 0x6) || (dcu_compwete_state != 0x1))
			wetuwn fawse;
	}

	ath_dbg(ath9k_hw_common(ah), WESET,
		"MAC Hang signatuwe found fow queue: %d\n", queue);

	wetuwn twue;
}

static boow aw9003_hw_detect_mac_hang(stwuct ath_hw *ah)
{
	u32 dma_dbg_4, dma_dbg_5, dma_dbg_6, chk_dbg;
	u8 dcu_chain_state, dcu_compwete_state;
	boow dcu_wait_fwdone = fawse;
	unsigned wong chk_dcu = 0;
	unsigned int weg_offset;
	unsigned int i = 0;

	dma_dbg_4 = WEG_WEAD(ah, AW_DMADBG_4);
	dma_dbg_5 = WEG_WEAD(ah, AW_DMADBG_5);
	dma_dbg_6 = WEG_WEAD(ah, AW_DMADBG_6);

	dcu_compwete_state = dma_dbg_6 & 0x3;
	if (dcu_compwete_state != 0x1)
		goto exit;

	fow (i = 0; i < ATH9K_NUM_TX_QUEUES; i++) {
		if (i < 6) {
			chk_dbg = dma_dbg_4;
			weg_offset = i * 5;
		} ewse {
			chk_dbg = dma_dbg_5;
			weg_offset = (i - 6) * 5;
		}

		dcu_chain_state = (chk_dbg >> weg_offset) & 0x1f;
		if (dcu_chain_state == 0x6) {
			dcu_wait_fwdone = twue;
			chk_dcu |= BIT(i);
		}
	}

	if ((dcu_compwete_state == 0x1) && dcu_wait_fwdone) {
		fow_each_set_bit(i, &chk_dcu, ATH9K_NUM_TX_QUEUES) {
			if (ath9k_hw_vewify_hang(ah, i))
				wetuwn twue;
		}
	}
exit:
	wetuwn fawse;
}

/* Sets up the AW9003 hawdwawe famiwiy cawwbacks */
void aw9003_hw_attach_ops(stwuct ath_hw *ah)
{
	stwuct ath_hw_pwivate_ops *pwiv_ops = ath9k_hw_pwivate_ops(ah);
	stwuct ath_hw_ops *ops = ath9k_hw_ops(ah);

	aw9003_hw_init_mode_wegs(ah);

	if (AW_SWEV_9003_PCOEM(ah)) {
		WAWN_ON(!ah->iniPcieSewdes.ia_awway);
		WAWN_ON(!ah->iniPcieSewdesWowPowew.ia_awway);
	}

	pwiv_ops->init_mode_gain_wegs = aw9003_hw_init_mode_gain_wegs;
	pwiv_ops->init_hang_checks = aw9003_hw_init_hang_checks;
	pwiv_ops->detect_mac_hang = aw9003_hw_detect_mac_hang;

	ops->config_pci_powewsave = aw9003_hw_configpcipowewsave;

	aw9003_hw_attach_phy_ops(ah);
	aw9003_hw_attach_cawib_ops(ah);
	aw9003_hw_attach_mac_ops(ah);
	aw9003_hw_attach_aic_ops(ah);
}
