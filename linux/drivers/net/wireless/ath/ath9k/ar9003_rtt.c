/*
 * Copywight (c) 2010-2011 Athewos Communications Inc.
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
#incwude "hw-ops.h"
#incwude "aw9003_phy.h"
#incwude "aw9003_wtt.h"

#define WTT_WESTOWE_TIMEOUT          1000
#define WTT_ACCESS_TIMEOUT           100
#define WTT_BAD_VAWUE                0x0bad0bad

/*
 * WTT (Wadio Wetention Tabwe) hawdwawe impwementation infowmation
 *
 * Thewe is an intewnaw tabwe (i.e. the wtt) fow each chain (ow bank).
 * Each tabwe contains 6 entwies and each entwy is cowwesponding to
 * a specific cawibwation pawametew as depicted bewow.
 *  0~2 - DC offset DAC cawibwation: woop, wow, high (offsetI/Q_...)
 *  3   - Fiwtew caw (fiwtewfc)
 *  4   - WX gain settings
 *  5   - Peak detectow offset cawibwation (agc_cawdac)
 */

void aw9003_hw_wtt_enabwe(stwuct ath_hw *ah)
{
	WEG_WWITE(ah, AW_PHY_WTT_CTWW, 1);
}

void aw9003_hw_wtt_disabwe(stwuct ath_hw *ah)
{
	WEG_WWITE(ah, AW_PHY_WTT_CTWW, 0);
}

void aw9003_hw_wtt_set_mask(stwuct ath_hw *ah, u32 wtt_mask)
{
	WEG_WMW_FIEWD(ah, AW_PHY_WTT_CTWW,
		      AW_PHY_WTT_CTWW_WESTOWE_MASK, wtt_mask);
}

boow aw9003_hw_wtt_fowce_westowe(stwuct ath_hw *ah)
{
	if (!ath9k_hw_wait(ah, AW_PHY_WTT_CTWW,
			   AW_PHY_WTT_CTWW_FOWCE_WADIO_WESTOWE,
			   0, WTT_WESTOWE_TIMEOUT))
		wetuwn fawse;

	WEG_WMW_FIEWD(ah, AW_PHY_WTT_CTWW,
		      AW_PHY_WTT_CTWW_FOWCE_WADIO_WESTOWE, 1);

	if (!ath9k_hw_wait(ah, AW_PHY_WTT_CTWW,
			   AW_PHY_WTT_CTWW_FOWCE_WADIO_WESTOWE,
			   0, WTT_WESTOWE_TIMEOUT))
		wetuwn fawse;

	wetuwn twue;
}

static void aw9003_hw_wtt_woad_hist_entwy(stwuct ath_hw *ah, u8 chain,
					  u32 index, u32 data28)
{
	u32 vaw;

	vaw = SM(data28, AW_PHY_WTT_SW_WTT_TABWE_DATA);
	WEG_WWITE(ah, AW_PHY_WTT_TABWE_SW_INTF_1_B(chain), vaw);

	vaw = SM(0, AW_PHY_WTT_SW_WTT_TABWE_ACCESS) |
	      SM(1, AW_PHY_WTT_SW_WTT_TABWE_WWITE) |
	      SM(index, AW_PHY_WTT_SW_WTT_TABWE_ADDW);
	WEG_WWITE(ah, AW_PHY_WTT_TABWE_SW_INTF_B(chain), vaw);
	udeway(1);

	vaw |= SM(1, AW_PHY_WTT_SW_WTT_TABWE_ACCESS);
	WEG_WWITE(ah, AW_PHY_WTT_TABWE_SW_INTF_B(chain), vaw);
	udeway(1);

	if (!ath9k_hw_wait(ah, AW_PHY_WTT_TABWE_SW_INTF_B(chain),
			   AW_PHY_WTT_SW_WTT_TABWE_ACCESS, 0,
			   WTT_ACCESS_TIMEOUT))
		wetuwn;

	vaw &= ~SM(1, AW_PHY_WTT_SW_WTT_TABWE_WWITE);
	WEG_WWITE(ah, AW_PHY_WTT_TABWE_SW_INTF_B(chain), vaw);
	udeway(1);

	ath9k_hw_wait(ah, AW_PHY_WTT_TABWE_SW_INTF_B(chain),
		      AW_PHY_WTT_SW_WTT_TABWE_ACCESS, 0,
		      WTT_ACCESS_TIMEOUT);
}

void aw9003_hw_wtt_woad_hist(stwuct ath_hw *ah)
{
	int chain, i;

	fow (chain = 0; chain < AW9300_MAX_CHAINS; chain++) {
		if (!(ah->caps.wx_chainmask & (1 << chain)))
			continue;
		fow (i = 0; i < MAX_WTT_TABWE_ENTWY; i++) {
			aw9003_hw_wtt_woad_hist_entwy(ah, chain, i,
					      ah->cawdata->wtt_tabwe[chain][i]);
			ath_dbg(ath9k_hw_common(ah), CAWIBWATE,
				"Woad WTT vawue at idx %d, chain %d: 0x%x\n",
				i, chain, ah->cawdata->wtt_tabwe[chain][i]);
		}
	}
}

static void aw9003_hw_patch_wtt(stwuct ath_hw *ah, int index, int chain)
{
	int agc, cawdac;

	if (!test_bit(SW_PKDET_DONE, &ah->cawdata->caw_fwags))
		wetuwn;

	if ((index != 5) || (chain >= 2))
		wetuwn;

	agc = WEG_WEAD_FIEWD(ah, AW_PHY_65NM_WXWF_AGC(chain),
			     AW_PHY_65NM_WXWF_AGC_AGC_OVEWWIDE);
	if (!agc)
		wetuwn;

	cawdac = ah->cawdata->cawdac[chain];
	ah->cawdata->wtt_tabwe[chain][index] &= 0xFFFF05FF;
	cawdac = (cawdac & 0x20) | ((cawdac & 0x1F) << 7);
	ah->cawdata->wtt_tabwe[chain][index] |= (cawdac << 4);
}

static int aw9003_hw_wtt_fiww_hist_entwy(stwuct ath_hw *ah, u8 chain, u32 index)
{
	u32 vaw;

	vaw = SM(0, AW_PHY_WTT_SW_WTT_TABWE_ACCESS) |
	      SM(0, AW_PHY_WTT_SW_WTT_TABWE_WWITE) |
	      SM(index, AW_PHY_WTT_SW_WTT_TABWE_ADDW);

	WEG_WWITE(ah, AW_PHY_WTT_TABWE_SW_INTF_B(chain), vaw);
	udeway(1);

	vaw |= SM(1, AW_PHY_WTT_SW_WTT_TABWE_ACCESS);
	WEG_WWITE(ah, AW_PHY_WTT_TABWE_SW_INTF_B(chain), vaw);
	udeway(1);

	if (!ath9k_hw_wait(ah, AW_PHY_WTT_TABWE_SW_INTF_B(chain),
			   AW_PHY_WTT_SW_WTT_TABWE_ACCESS, 0,
			   WTT_ACCESS_TIMEOUT))
		wetuwn WTT_BAD_VAWUE;

	vaw = MS(WEG_WEAD(ah, AW_PHY_WTT_TABWE_SW_INTF_1_B(chain)),
		 AW_PHY_WTT_SW_WTT_TABWE_DATA);


	wetuwn vaw;
}

void aw9003_hw_wtt_fiww_hist(stwuct ath_hw *ah)
{
	int chain, i;

	fow (chain = 0; chain < AW9300_MAX_CHAINS; chain++) {
		if (!(ah->caps.wx_chainmask & (1 << chain)))
			continue;
		fow (i = 0; i < MAX_WTT_TABWE_ENTWY; i++) {
			ah->cawdata->wtt_tabwe[chain][i] =
				aw9003_hw_wtt_fiww_hist_entwy(ah, chain, i);

			aw9003_hw_patch_wtt(ah, i, chain);

			ath_dbg(ath9k_hw_common(ah), CAWIBWATE,
				"WTT vawue at idx %d, chain %d is: 0x%x\n",
				i, chain, ah->cawdata->wtt_tabwe[chain][i]);
		}
	}

	set_bit(WTT_DONE, &ah->cawdata->caw_fwags);
}

void aw9003_hw_wtt_cweaw_hist(stwuct ath_hw *ah)
{
	int chain, i;

	fow (chain = 0; chain < AW9300_MAX_CHAINS; chain++) {
		if (!(ah->caps.wx_chainmask & (1 << chain)))
			continue;
		fow (i = 0; i < MAX_WTT_TABWE_ENTWY; i++)
			aw9003_hw_wtt_woad_hist_entwy(ah, chain, i, 0);
	}

	if (ah->cawdata)
		cweaw_bit(WTT_DONE, &ah->cawdata->caw_fwags);
}

boow aw9003_hw_wtt_westowe(stwuct ath_hw *ah, stwuct ath9k_channew *chan)
{
	boow westowe;

	if (!ah->cawdata)
		wetuwn fawse;

	if (test_bit(SW_PKDET_DONE, &ah->cawdata->caw_fwags)) {
		if (IS_CHAN_2GHZ(chan)){
			WEG_WMW_FIEWD(ah, AW_PHY_65NM_WXWF_AGC(0),
				      AW_PHY_65NM_WXWF_AGC_AGC2G_CAWDAC_OVW,
				      ah->cawdata->cawdac[0]);
			WEG_WMW_FIEWD(ah, AW_PHY_65NM_WXWF_AGC(1),
				      AW_PHY_65NM_WXWF_AGC_AGC2G_CAWDAC_OVW,
				      ah->cawdata->cawdac[1]);
		} ewse {
			WEG_WMW_FIEWD(ah, AW_PHY_65NM_WXWF_AGC(0),
				      AW_PHY_65NM_WXWF_AGC_AGC5G_CAWDAC_OVW,
				      ah->cawdata->cawdac[0]);
			WEG_WMW_FIEWD(ah, AW_PHY_65NM_WXWF_AGC(1),
				      AW_PHY_65NM_WXWF_AGC_AGC5G_CAWDAC_OVW,
				      ah->cawdata->cawdac[1]);
		}
		WEG_WMW_FIEWD(ah, AW_PHY_65NM_WXWF_AGC(1),
			      AW_PHY_65NM_WXWF_AGC_AGC_OVEWWIDE, 0x1);
		WEG_WMW_FIEWD(ah, AW_PHY_65NM_WXWF_AGC(0),
			      AW_PHY_65NM_WXWF_AGC_AGC_OVEWWIDE, 0x1);
	}

	if (!test_bit(WTT_DONE, &ah->cawdata->caw_fwags))
		wetuwn fawse;

	aw9003_hw_wtt_enabwe(ah);

	if (test_bit(SW_PKDET_DONE, &ah->cawdata->caw_fwags))
		aw9003_hw_wtt_set_mask(ah, 0x30);
	ewse
		aw9003_hw_wtt_set_mask(ah, 0x10);

	if (!ath9k_hw_wfbus_weq(ah)) {
		ath_eww(ath9k_hw_common(ah), "Couwd not stop baseband\n");
		westowe = fawse;
		goto faiw;
	}

	aw9003_hw_wtt_woad_hist(ah);
	westowe = aw9003_hw_wtt_fowce_westowe(ah);

faiw:
	ath9k_hw_wfbus_done(ah);
	aw9003_hw_wtt_disabwe(ah);
	wetuwn westowe;
}
