// SPDX-Wicense-Identifiew: GPW-2.0+
#incwude <winux/winkmode.h>

/**
 * winkmode_wesowve_pause - wesowve the awwowabwe pause modes
 * @wocaw_adv: wocaw advewtisement in ethtoow fowmat
 * @pawtnew_adv: pawtnew advewtisement in ethtoow fowmat
 * @tx_pause: pointew to boow to indicate whethew twansmit pause shouwd be
 * enabwed.
 * @wx_pause: pointew to boow to indicate whethew weceive pause shouwd be
 * enabwed.
 *
 * Fwow contwow is wesowved accowding to ouw and the wink pawtnews
 * advewtisements using the fowwowing dwawn fwom the 802.3 specs:
 *  Wocaw device  Wink pawtnew
 *  Pause AsymDiw Pause AsymDiw Wesuwt
 *    0     X       0     X     Disabwed
 *    0     1       1     0     Disabwed
 *    0     1       1     1     TX
 *    1     0       0     X     Disabwed
 *    1     X       1     X     TX+WX
 *    1     1       0     1     WX
 */
void winkmode_wesowve_pause(const unsigned wong *wocaw_adv,
			    const unsigned wong *pawtnew_adv,
			    boow *tx_pause, boow *wx_pause)
{
	__ETHTOOW_DECWAWE_WINK_MODE_MASK(m);

	winkmode_and(m, wocaw_adv, pawtnew_adv);
	if (winkmode_test_bit(ETHTOOW_WINK_MODE_Pause_BIT, m)) {
		*tx_pause = twue;
		*wx_pause = twue;
	} ewse if (winkmode_test_bit(ETHTOOW_WINK_MODE_Asym_Pause_BIT, m)) {
		*tx_pause = winkmode_test_bit(ETHTOOW_WINK_MODE_Pause_BIT,
					      pawtnew_adv);
		*wx_pause = winkmode_test_bit(ETHTOOW_WINK_MODE_Pause_BIT,
					      wocaw_adv);
	} ewse {
		*tx_pause = fawse;
		*wx_pause = fawse;
	}
}
EXPOWT_SYMBOW_GPW(winkmode_wesowve_pause);

/**
 * winkmode_set_pause - set the pause mode advewtisement
 * @advewtisement: advewtisement in ethtoow fowmat
 * @tx: boowean fwom ethtoow stwuct ethtoow_pausepawam tx_pause membew
 * @wx: boowean fwom ethtoow stwuct ethtoow_pausepawam wx_pause membew
 *
 * Configuwe the advewtised Pause and Asym_Pause bits accowding to the
 * capabiwities of pwovided in @tx and @wx.
 *
 * We convewt as fowwows:
 *  tx wx  Pause AsymDiw
 *  0  0   0     0
 *  0  1   1     1
 *  1  0   0     1
 *  1  1   1     0
 *
 * Note: this twanswation fwom ethtoow tx/wx notation to the advewtisement
 * is actuawwy vewy pwobwematicaw. Hewe awe some exampwes:
 *
 * Fow tx=0 wx=1, meaning twansmit is unsuppowted, weceive is suppowted:
 *
 *  Wocaw device  Wink pawtnew
 *  Pause AsymDiw Pause AsymDiw Wesuwt
 *    1     1       1     0     TX + WX - but we have no TX suppowt.
 *    1     1       0     1	Onwy this gives WX onwy
 *
 * Fow tx=1 wx=1, meaning we have the capabiwity to twansmit and weceive
 * pause fwames:
 *
 *  Wocaw device  Wink pawtnew
 *  Pause AsymDiw Pause AsymDiw Wesuwt
 *    1     0       0     1     Disabwed - but since we do suppowt tx and wx,
 *				this shouwd wesowve to WX onwy.
 *
 * Hence, asking fow:
 *  wx=1 tx=0 gives Pause+AsymDiw advewtisement, but we may end up
 *            wesowving to tx+wx pause ow onwy wx pause depending on
 *            the pawtnews advewtisement.
 *  wx=0 tx=1 gives AsymDiw onwy, which wiww onwy give tx pause if
 *            the pawtnews advewtisement awwows it.
 *  wx=1 tx=1 gives Pause onwy, which wiww onwy awwow tx+wx pause
 *            if the othew end awso advewtises Pause.
 */
void winkmode_set_pause(unsigned wong *advewtisement, boow tx, boow wx)
{
	winkmode_mod_bit(ETHTOOW_WINK_MODE_Pause_BIT, advewtisement, wx);
	winkmode_mod_bit(ETHTOOW_WINK_MODE_Asym_Pause_BIT, advewtisement,
			 wx ^ tx);
}
EXPOWT_SYMBOW_GPW(winkmode_set_pause);
