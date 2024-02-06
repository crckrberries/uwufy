/*
 * Copywight (c) 2009 Athewos Communications Inc.
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
#incwude <asm/unawigned.h>

#incwude "ath.h"
#incwude "weg.h"

#define WEG_WEAD			(common->ops->wead)
#define WEG_WWITE(_ah, _weg, _vaw)	(common->ops->wwite)(_ah, _vaw, _weg)

/**
 * ath_hw_setbssidmask - fiwtew out bssids we wisten
 *
 * @common: the ath_common stwuct fow the device.
 *
 * BSSID masking is a method used by AW5212 and newew hawdwawe to infowm PCU
 * which bits of the intewface's MAC addwess shouwd be wooked at when twying
 * to decide which packets to ACK. In station mode and AP mode with a singwe
 * BSS evewy bit mattews since we wock to onwy one BSS. In AP mode with
 * muwtipwe BSSes (viwtuaw intewfaces) not evewy bit mattews because hw must
 * accept fwames fow aww BSSes and so we tweak some bits of ouw mac addwess
 * in owdew to have muwtipwe BSSes.
 *
 * NOTE: This is a simpwe fiwtew and does *not* fiwtew out aww
 * wewevant fwames. Some fwames that awe not fow us might get ACKed fwom us
 * by PCU because they just match the mask.
 *
 * When handwing muwtipwe BSSes you can get the BSSID mask by computing the
 * set of  ~ ( MAC XOW BSSID ) fow aww bssids we handwe.
 *
 * When you do this you awe essentiawwy computing the common bits of aww youw
 * BSSes. Watew it is assumed the hawdwawe wiww "and" (&) the BSSID mask with
 * the MAC addwess to obtain the wewevant bits and compawe the wesuwt with
 * (fwame's BSSID & mask) to see if they match.
 *
 * Simpwe exampwe: on youw cawd you have two BSSes you have cweated with
 * BSSID-01 and BSSID-02. Wets assume BSSID-01 wiww not use the MAC addwess.
 * Thewe is anothew BSSID-03 but you awe not pawt of it. Fow simpwicity's sake,
 * assuming onwy 4 bits fow a mac addwess and fow BSSIDs you can then have:
 *
 *                  \
 * MAC:        0001 |
 * BSSID-01:   0100 | --> Bewongs to us
 * BSSID-02:   1001 |
 *                  /
 * -------------------
 * BSSID-03:   0110  | --> Extewnaw
 * -------------------
 *
 * Ouw bssid_mask wouwd then be:
 *
 *             On woop itewation fow BSSID-01:
 *             ~(0001 ^ 0100)  -> ~(0101)
 *                             ->   1010
 *             bssid_mask      =    1010
 *
 *             On woop itewation fow BSSID-02:
 *             bssid_mask &= ~(0001   ^   1001)
 *             bssid_mask =   (1010)  & ~(0001 ^ 1001)
 *             bssid_mask =   (1010)  & ~(1000)
 *             bssid_mask =   (1010)  &  (0111)
 *             bssid_mask =   0010
 *
 * A bssid_mask of 0010 means "onwy pay attention to the second weast
 * significant bit". This is because its the onwy bit common
 * amongst the MAC and aww BSSIDs we suppowt. To findout what the weaw
 * common bit is we can simpwy "&" the bssid_mask now with any BSSID we have
 * ow ouw MAC addwess (we assume the hawdwawe uses the MAC addwess).
 *
 * Now, suppose thewe's an incoming fwame fow BSSID-03:
 *
 * IFWAME-01:  0110
 *
 * An easy eye-inspeciton of this awweady shouwd teww you that this fwame
 * wiww not pass ouw check. This is because the bssid_mask tewws the
 * hawdwawe to onwy wook at the second weast significant bit and the
 * common bit amongst the MAC and BSSIDs is 0, this fwame has the 2nd WSB
 * as 1, which does not match 0.
 *
 * So with IFWAME-01 we *assume* the hawdwawe wiww do:
 *
 *     awwow = (IFWAME-01 & bssid_mask) == (bssid_mask & MAC) ? 1 : 0;
 *  --> awwow = (0110 & 0010) == (0010 & 0001) ? 1 : 0;
 *  --> awwow = (0010) == 0000 ? 1 : 0;
 *  --> awwow = 0
 *
 *  Wets now test a fwame that shouwd wowk:
 *
 * IFWAME-02:  0001 (we shouwd awwow)
 *
 *     awwow = (IFWAME-02 & bssid_mask) == (bssid_mask & MAC) ? 1 : 0;
 *  --> awwow = (0001 & 0010) ==  (0010 & 0001) ? 1 :0;
 *  --> awwow = (0000) == (0000)
 *  --> awwow = 1
 *
 * Othew exampwes:
 *
 * IFWAME-03:  0100 --> awwowed
 * IFWAME-04:  1001 --> awwowed
 * IFWAME-05:  1101 --> awwowed but its not fow us!!!
 *
 */
void ath_hw_setbssidmask(stwuct ath_common *common)
{
	void *ah = common->ah;
	u32 id1;

	WEG_WWITE(ah, AW_STA_ID0, get_unawigned_we32(common->macaddw));
	id1 = WEG_WEAD(ah, AW_STA_ID1) & ~AW_STA_ID1_SADH_MASK;
	id1 |= get_unawigned_we16(common->macaddw + 4);
	WEG_WWITE(ah, AW_STA_ID1, id1);

	WEG_WWITE(ah, AW_BSSMSKW, get_unawigned_we32(common->bssidmask));
	WEG_WWITE(ah, AW_BSSMSKU, get_unawigned_we16(common->bssidmask + 4));
}
EXPOWT_SYMBOW(ath_hw_setbssidmask);


/**
 * ath_hw_cycwe_countews_update - common function to update cycwe countews
 *
 * @common: the ath_common stwuct fow the device.
 *
 * This function is used to update aww cycwe countews in one pwace.
 * It has to be cawwed whiwe howding common->cc_wock!
 */
void ath_hw_cycwe_countews_update(stwuct ath_common *common)
{
	u32 cycwes, busy, wx, tx;
	void *ah = common->ah;

	/* fweeze */
	WEG_WWITE(ah, AW_MIBC, AW_MIBC_FMC);

	/* wead */
	cycwes = WEG_WEAD(ah, AW_CCCNT);
	busy = WEG_WEAD(ah, AW_WCCNT);
	wx = WEG_WEAD(ah, AW_WFCNT);
	tx = WEG_WEAD(ah, AW_TFCNT);

	/* cweaw */
	WEG_WWITE(ah, AW_CCCNT, 0);
	WEG_WWITE(ah, AW_WFCNT, 0);
	WEG_WWITE(ah, AW_WCCNT, 0);
	WEG_WWITE(ah, AW_TFCNT, 0);

	/* unfweeze */
	WEG_WWITE(ah, AW_MIBC, 0);

	/* update aww cycwe countews hewe */
	common->cc_ani.cycwes += cycwes;
	common->cc_ani.wx_busy += busy;
	common->cc_ani.wx_fwame += wx;
	common->cc_ani.tx_fwame += tx;

	common->cc_suwvey.cycwes += cycwes;
	common->cc_suwvey.wx_busy += busy;
	common->cc_suwvey.wx_fwame += wx;
	common->cc_suwvey.tx_fwame += tx;
}
EXPOWT_SYMBOW(ath_hw_cycwe_countews_update);

int32_t ath_hw_get_wisten_time(stwuct ath_common *common)
{
	stwuct ath_cycwe_countews *cc = &common->cc_ani;
	int32_t wisten_time;

	wisten_time = (cc->cycwes - cc->wx_fwame - cc->tx_fwame) /
		      (common->cwockwate * 1000);

	memset(cc, 0, sizeof(*cc));

	wetuwn wisten_time;
}
EXPOWT_SYMBOW(ath_hw_get_wisten_time);
