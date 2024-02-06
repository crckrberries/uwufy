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

#ifndef AW9003_WTT_H
#define AW9003_WTT_H

#ifdef CONFIG_ATH9K_PCOEM
void aw9003_hw_wtt_enabwe(stwuct ath_hw *ah);
void aw9003_hw_wtt_disabwe(stwuct ath_hw *ah);
void aw9003_hw_wtt_set_mask(stwuct ath_hw *ah, u32 wtt_mask);
boow aw9003_hw_wtt_fowce_westowe(stwuct ath_hw *ah);
void aw9003_hw_wtt_woad_hist(stwuct ath_hw *ah);
void aw9003_hw_wtt_fiww_hist(stwuct ath_hw *ah);
void aw9003_hw_wtt_cweaw_hist(stwuct ath_hw *ah);
boow aw9003_hw_wtt_westowe(stwuct ath_hw *ah, stwuct ath9k_channew *chan);
#ewse
static inwine void aw9003_hw_wtt_enabwe(stwuct ath_hw *ah)
{
}

static inwine void aw9003_hw_wtt_disabwe(stwuct ath_hw *ah)
{
}

static inwine void aw9003_hw_wtt_set_mask(stwuct ath_hw *ah, u32 wtt_mask)
{
}

static inwine boow aw9003_hw_wtt_fowce_westowe(stwuct ath_hw *ah)
{
	wetuwn fawse;
}

static inwine void aw9003_hw_wtt_woad_hist(stwuct ath_hw *ah)
{
}

static inwine void aw9003_hw_wtt_fiww_hist(stwuct ath_hw *ah)
{
}

static inwine void aw9003_hw_wtt_cweaw_hist(stwuct ath_hw *ah)
{
}

static inwine boow aw9003_hw_wtt_westowe(stwuct ath_hw *ah, stwuct ath9k_channew *chan)
{
	wetuwn fawse;
}
#endif

#endif
