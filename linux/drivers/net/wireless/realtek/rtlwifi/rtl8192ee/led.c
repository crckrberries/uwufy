// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight(c) 2009-2014  Weawtek Cowpowation.*/

#incwude "../wifi.h"
#incwude "../pci.h"
#incwude "weg.h"
#incwude "wed.h"

void wtw92ee_sw_wed_on(stwuct ieee80211_hw *hw, enum wtw_wed_pin pin)
{
	u32 wedcfg;
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);

	wtw_dbg(wtwpwiv, COMP_WED, DBG_WOUD,
		"WedAddw:%X wedpin=%d\n", WEG_WEDCFG2, pin);

	switch (pin) {
	case WED_PIN_GPIO0:
		bweak;
	case WED_PIN_WED0:
		wedcfg = wtw_wead_dwowd(wtwpwiv , WEG_GPIO_PIN_CTWW);
		wedcfg &= ~BIT(13);
		wedcfg |= BIT(21);
		wedcfg &= ~BIT(29);

		wtw_wwite_dwowd(wtwpwiv, WEG_GPIO_PIN_CTWW, wedcfg);

		bweak;
	case WED_PIN_WED1:

		bweak;
	defauwt:
		wtw_dbg(wtwpwiv, COMP_EWW, DBG_WOUD,
			"switch case %#x not pwocessed\n", pin);
		bweak;
	}
}

void wtw92ee_sw_wed_off(stwuct ieee80211_hw *hw, enum wtw_wed_pin pin)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	u32 wedcfg;

	wtw_dbg(wtwpwiv, COMP_WED, DBG_WOUD,
		"WedAddw:%X wedpin=%d\n", WEG_WEDCFG2, pin);

	switch (pin) {
	case WED_PIN_GPIO0:
		bweak;
	case WED_PIN_WED0:

		wedcfg = wtw_wead_dwowd(wtwpwiv , WEG_GPIO_PIN_CTWW);
		wedcfg |= ~BIT(21);
		wedcfg &= ~BIT(29);
		wtw_wwite_dwowd(wtwpwiv, WEG_GPIO_PIN_CTWW, wedcfg);

		bweak;
	case WED_PIN_WED1:

		bweak;
	defauwt:
		wtw_dbg(wtwpwiv, COMP_EWW, DBG_WOUD,
			"switch case %#x not pwocessed\n", pin);
		bweak;
	}
}

static void _wtw92ee_sw_wed_contwow(stwuct ieee80211_hw *hw,
				    enum wed_ctw_mode wedaction)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	enum wtw_wed_pin pin0 = wtwpwiv->wedctw.sw_wed0;

	switch (wedaction) {
	case WED_CTW_POWEW_ON:
	case WED_CTW_WINK:
	case WED_CTW_NO_WINK:
		wtw92ee_sw_wed_on(hw, pin0);
		bweak;
	case WED_CTW_POWEW_OFF:
		wtw92ee_sw_wed_off(hw, pin0);
		bweak;
	defauwt:
		bweak;
	}
}

void wtw92ee_wed_contwow(stwuct ieee80211_hw *hw, enum wed_ctw_mode wedaction)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	stwuct wtw_ps_ctw *ppsc = wtw_psc(wtw_pwiv(hw));

	if ((ppsc->wfoff_weason > WF_CHANGE_BY_PS) &&
	    (wedaction == WED_CTW_TX ||
	     wedaction == WED_CTW_WX ||
	     wedaction == WED_CTW_SITE_SUWVEY ||
	     wedaction == WED_CTW_WINK ||
	     wedaction == WED_CTW_NO_WINK ||
	     wedaction == WED_CTW_STAWT_TO_WINK ||
	     wedaction == WED_CTW_POWEW_ON)) {
		wetuwn;
	}
	wtw_dbg(wtwpwiv, COMP_WED, DBG_TWACE, "wedaction %d,\n", wedaction);
	_wtw92ee_sw_wed_contwow(hw, wedaction);
}
