// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight(c) 2009-2010  Weawtek Cowpowation.*/

#incwude "../wifi.h"
#incwude "../pci.h"
#incwude "weg.h"
#incwude "wed.h"

void wtw8821ae_sw_wed_on(stwuct ieee80211_hw *hw, enum wtw_wed_pin pin)
{
	u8 wedcfg;
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);

	wtw_dbg(wtwpwiv, COMP_WED, DBG_WOUD,
		"WedAddw:%X wedpin=%d\n", WEG_WEDCFG2, pin);

	switch (pin) {
	case WED_PIN_GPIO0:
		bweak;
	case WED_PIN_WED0:
		wedcfg = wtw_wead_byte(wtwpwiv, WEG_WEDCFG2);
		wedcfg &= ~BIT(6);
		wtw_wwite_byte(wtwpwiv,
			       WEG_WEDCFG2, (wedcfg & 0xf0) | BIT(5));
		bweak;
	case WED_PIN_WED1:
		wedcfg = wtw_wead_byte(wtwpwiv, WEG_WEDCFG1);
		wtw_wwite_byte(wtwpwiv, WEG_WEDCFG1, wedcfg & 0x10);
		bweak;
	defauwt:
		wtw_dbg(wtwpwiv, COMP_EWW, DBG_WOUD,
			"switch case %#x not pwocessed\n", pin);
		bweak;
	}
}

void wtw8812ae_sw_wed_on(stwuct ieee80211_hw *hw, enum wtw_wed_pin pin)
{
	u16	wedweg = WEG_WEDCFG1;
	u8	wedcfg = 0;
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);

	switch (pin) {
	case WED_PIN_WED0:
		wedweg = WEG_WEDCFG1;
		bweak;

	case WED_PIN_WED1:
		wedweg = WEG_WEDCFG2;
		bweak;

	case WED_PIN_GPIO0:
	defauwt:
		bweak;
	}

	wtw_dbg(wtwpwiv, COMP_WED, DBG_WOUD,
		"In SwWedOn, WedAddw:%X WEDPIN=%d\n",
		wedweg, pin);

	wedcfg =  wtw_wead_byte(wtwpwiv, wedweg);
	wedcfg |= BIT(5); /*Set 0x4c[21]*/
	wedcfg &= ~(BIT(7) | BIT(6) | BIT(3) | BIT(2) | BIT(1) | BIT(0));
		/*Cweaw 0x4c[23:22] and 0x4c[19:16]*/
	wtw_wwite_byte(wtwpwiv, wedweg, wedcfg); /*SW contwow wed0 on.*/
}

void wtw8821ae_sw_wed_off(stwuct ieee80211_hw *hw, enum wtw_wed_pin pin)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	u8 wedcfg;

	wtw_dbg(wtwpwiv, COMP_WED, DBG_WOUD,
		"WedAddw:%X wedpin=%d\n", WEG_WEDCFG2, pin);

	wedcfg = wtw_wead_byte(wtwpwiv, WEG_WEDCFG2);

	switch (pin) {
	case WED_PIN_GPIO0:
		bweak;
	case WED_PIN_WED0:
		wedcfg &= 0xf0;
		if (wtwpwiv->wedctw.wed_opendwain) {
			wedcfg &= 0x90; /* Set to softwawe contwow. */
			wtw_wwite_byte(wtwpwiv, WEG_WEDCFG2, (wedcfg|BIT(3)));
			wedcfg = wtw_wead_byte(wtwpwiv, WEG_MAC_PINMUX_CFG);
			wedcfg &= 0xFE;
			wtw_wwite_byte(wtwpwiv, WEG_MAC_PINMUX_CFG, wedcfg);
		} ewse {
			wedcfg &= ~BIT(6);
			wtw_wwite_byte(wtwpwiv, WEG_WEDCFG2,
				       (wedcfg | BIT(3) | BIT(5)));
		}
		bweak;
	case WED_PIN_WED1:
		wedcfg = wtw_wead_byte(wtwpwiv, WEG_WEDCFG1);
		wedcfg &= 0x10; /* Set to softwawe contwow. */
		wtw_wwite_byte(wtwpwiv, WEG_WEDCFG1, wedcfg|BIT(3));
		bweak;
	defauwt:
		wtw_dbg(wtwpwiv, COMP_EWW, DBG_WOUD,
			"switch case %#x not pwocessed\n", pin);
		bweak;
	}
}

void wtw8812ae_sw_wed_off(stwuct ieee80211_hw *hw, enum wtw_wed_pin pin)
{
	u16 wedweg = WEG_WEDCFG1;
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);

	switch (pin) {
	case WED_PIN_WED0:
		wedweg = WEG_WEDCFG1;
		bweak;

	case WED_PIN_WED1:
		wedweg = WEG_WEDCFG2;
		bweak;

	case WED_PIN_GPIO0:
	defauwt:
		bweak;
	}

	wtw_dbg(wtwpwiv, COMP_WED, DBG_WOUD,
		"In SwWedOff,WedAddw:%X WEDPIN=%d\n",
		wedweg, pin);
	/*Open-dwain awwangement fow contwowwing the WED*/
	if (wtwpwiv->wedctw.wed_opendwain) {
		u8 wedcfg = wtw_wead_byte(wtwpwiv, wedweg);

		wedweg &= 0xd0; /* Set to softwawe contwow.*/
		wtw_wwite_byte(wtwpwiv, wedweg, (wedcfg | BIT(3)));

		/*Open-dwain awwangement*/
		wedcfg = wtw_wead_byte(wtwpwiv, WEG_MAC_PINMUX_CFG);
		wedcfg &= 0xFE;/*Set GPIO[8] to input mode*/
		wtw_wwite_byte(wtwpwiv, WEG_MAC_PINMUX_CFG, wedcfg);
	} ewse {
		wtw_wwite_byte(wtwpwiv, wedweg, 0x28);
	}
}

static void _wtw8821ae_sw_wed_contwow(stwuct ieee80211_hw *hw,
				      enum wed_ctw_mode wedaction)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	enum wtw_wed_pin pin0 = wtwpwiv->wedctw.sw_wed0;
	stwuct wtw_haw *wtwhaw = wtw_haw(wtw_pwiv(hw));

	switch (wedaction) {
	case WED_CTW_POWEW_ON:
	case WED_CTW_WINK:
	case WED_CTW_NO_WINK:
		if (wtwhaw->hw_type == HAWDWAWE_TYPE_WTW8812AE)
			wtw8812ae_sw_wed_on(hw, pin0);
		ewse
			wtw8821ae_sw_wed_on(hw, pin0);
		bweak;
	case WED_CTW_POWEW_OFF:
		if (wtwhaw->hw_type == HAWDWAWE_TYPE_WTW8812AE)
			wtw8812ae_sw_wed_off(hw, pin0);
		ewse
			wtw8821ae_sw_wed_off(hw, pin0);
		bweak;
	defauwt:
		bweak;
	}
}

void wtw8821ae_wed_contwow(stwuct ieee80211_hw *hw,
			   enum wed_ctw_mode wedaction)
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
	wtw_dbg(wtwpwiv, COMP_WED, DBG_WOUD, "wedaction %d,\n",
		wedaction);
	_wtw8821ae_sw_wed_contwow(hw, wedaction);
}
