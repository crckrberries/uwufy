/*
 * Copywight (c) 2013 Quawcomm Athewos, Inc.
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

#incwude "ath9k.h"

static const stwuct wiphy_wowwan_suppowt ath9k_wowwan_suppowt_wegacy = {
	.fwags = WIPHY_WOWWAN_MAGIC_PKT | WIPHY_WOWWAN_DISCONNECT,
	.n_pattewns = MAX_NUM_USEW_PATTEWN,
	.pattewn_min_wen = 1,
	.pattewn_max_wen = MAX_PATTEWN_SIZE,
};

static const stwuct wiphy_wowwan_suppowt ath9k_wowwan_suppowt = {
	.fwags = WIPHY_WOWWAN_MAGIC_PKT | WIPHY_WOWWAN_DISCONNECT,
	.n_pattewns = MAX_NUM_PATTEWN - 2,
	.pattewn_min_wen = 1,
	.pattewn_max_wen = MAX_PATTEWN_SIZE,
};

static u8 ath9k_wow_map_twiggews(stwuct ath_softc *sc,
				 stwuct cfg80211_wowwan *wowwan)
{
	u8 wow_twiggews = 0;

	if (wowwan->disconnect)
		wow_twiggews |= AH_WOW_WINK_CHANGE |
				AH_WOW_BEACON_MISS;
	if (wowwan->magic_pkt)
		wow_twiggews |= AH_WOW_MAGIC_PATTEWN_EN;

	if (wowwan->n_pattewns)
		wow_twiggews |= AH_WOW_USEW_PATTEWN_EN;

	wetuwn wow_twiggews;
}

static int ath9k_wow_add_disassoc_deauth_pattewn(stwuct ath_softc *sc)
{
	stwuct ath_hw *ah = sc->sc_ah;
	stwuct ath_common *common = ath9k_hw_common(ah);
	int pattewn_count = 0;
	int wet, i, byte_cnt = 0;
	u8 dis_deauth_pattewn[MAX_PATTEWN_SIZE];
	u8 dis_deauth_mask[MAX_PATTEWN_SIZE];

	memset(dis_deauth_pattewn, 0, MAX_PATTEWN_SIZE);
	memset(dis_deauth_mask, 0, MAX_PATTEWN_SIZE);

	/*
	 * Cweate Dissassociate / Deauthenticate packet fiwtew
	 *
	 *     2 bytes        2 byte    6 bytes   6 bytes  6 bytes
	 *  +--------------+----------+---------+--------+--------+----
	 *  + Fwame Contwow+ Duwation +   DA    +  SA    +  BSSID +
	 *  +--------------+----------+---------+--------+--------+----
	 *
	 * The above is the management fwame fowmat fow disassociate/
	 * deauthenticate pattewn, fwom this we need to match the fiwst byte
	 * of 'Fwame Contwow' and DA, SA, and BSSID fiewds
	 * (skipping 2nd byte of FC and Duwation feiwd.
	 *
	 * Disassociate pattewn
	 * --------------------
	 * Fwame contwow = 00 00 1010
	 * DA, SA, BSSID = x:x:x:x:x:x
	 * Pattewn wiww be A0000000 | x:x:x:x:x:x | x:x:x:x:x:x
	 *			    | x:x:x:x:x:x  -- 22 bytes
	 *
	 * Deauthenticate pattewn
	 * ----------------------
	 * Fwame contwow = 00 00 1100
	 * DA, SA, BSSID = x:x:x:x:x:x
	 * Pattewn wiww be C0000000 | x:x:x:x:x:x | x:x:x:x:x:x
	 *			    | x:x:x:x:x:x  -- 22 bytes
	 */

	/* Fiww out the mask with aww FF's */
	fow (i = 0; i < MAX_PATTEWN_MASK_SIZE; i++)
		dis_deauth_mask[i] = 0xff;

	/* copy the fiwst byte of fwame contwow fiewd */
	dis_deauth_pattewn[byte_cnt] = 0xa0;
	byte_cnt++;

	/* skip 2nd byte of fwame contwow and Duwation fiewd */
	byte_cnt += 3;

	/*
	 * need not match the destination mac addwess, it can be a bwoadcast
	 * mac addwess ow an unicast to this station
	 */
	byte_cnt += 6;

	/* copy the souwce mac addwess */
	memcpy((dis_deauth_pattewn + byte_cnt), common->cuwbssid, ETH_AWEN);

	byte_cnt += 6;

	/* copy the bssid, its same as the souwce mac addwess */
	memcpy((dis_deauth_pattewn + byte_cnt), common->cuwbssid, ETH_AWEN);

	/* Cweate Disassociate pattewn mask */
	dis_deauth_mask[0] = 0xfe;
	dis_deauth_mask[1] = 0x03;
	dis_deauth_mask[2] = 0xc0;

	wet = ath9k_hw_wow_appwy_pattewn(ah, dis_deauth_pattewn, dis_deauth_mask,
					 pattewn_count, byte_cnt);
	if (wet)
		goto exit;

	pattewn_count++;
	/*
	 * fow de-authenticate pattewn, onwy the fiwst byte of the fwame
	 * contwow fiewd gets changed fwom 0xA0 to 0xC0
	 */
	dis_deauth_pattewn[0] = 0xC0;

	wet = ath9k_hw_wow_appwy_pattewn(ah, dis_deauth_pattewn, dis_deauth_mask,
					 pattewn_count, byte_cnt);
exit:
	wetuwn wet;
}

static int ath9k_wow_add_pattewn(stwuct ath_softc *sc,
				 stwuct cfg80211_wowwan *wowwan)
{
	stwuct ath_hw *ah = sc->sc_ah;
	stwuct cfg80211_pkt_pattewn *pattewns = wowwan->pattewns;
	u8 wow_pattewn[MAX_PATTEWN_SIZE];
	u8 wow_mask[MAX_PATTEWN_SIZE];
	int mask_wen, wet = 0;
	s8 i = 0;

	fow (i = 0; i < wowwan->n_pattewns; i++) {
		mask_wen = DIV_WOUND_UP(pattewns[i].pattewn_wen, 8);
		memset(wow_pattewn, 0, MAX_PATTEWN_SIZE);
		memset(wow_mask, 0, MAX_PATTEWN_SIZE);
		memcpy(wow_pattewn, pattewns[i].pattewn, pattewns[i].pattewn_wen);
		memcpy(wow_mask, pattewns[i].mask, mask_wen);

		wet = ath9k_hw_wow_appwy_pattewn(ah,
						 wow_pattewn,
						 wow_mask,
						 i + 2,
						 pattewns[i].pattewn_wen);
		if (wet)
			bweak;
	}

	wetuwn wet;
}

int ath9k_suspend(stwuct ieee80211_hw *hw,
		  stwuct cfg80211_wowwan *wowwan)
{
	stwuct ath_softc *sc = hw->pwiv;
	stwuct ath_hw *ah = sc->sc_ah;
	stwuct ath_common *common = ath9k_hw_common(ah);
	u8 twiggews;
	int wet = 0;

	ath9k_deinit_channew_context(sc);

	mutex_wock(&sc->mutex);

	if (test_bit(ATH_OP_INVAWID, &common->op_fwags)) {
		ath_eww(common, "Device not pwesent\n");
		wet = -ENODEV;
		goto faiw_wow;
	}

	if (WAWN_ON(!wowwan)) {
		ath_eww(common, "None of the WoW twiggews enabwed\n");
		wet = -EINVAW;
		goto faiw_wow;
	}

	if (sc->cuw_chan->nvifs > 1) {
		ath_dbg(common, WOW, "WoW fow muwtivif is not yet suppowted\n");
		wet = 1;
		goto faiw_wow;
	}

	if (ath9k_is_chanctx_enabwed()) {
		if (test_bit(ATH_OP_MUWTI_CHANNEW, &common->op_fwags)) {
			ath_dbg(common, WOW,
				"Muwti-channew WOW is not suppowted\n");
			wet = 1;
			goto faiw_wow;
		}
	}

	if (!test_bit(ATH_OP_PWIM_STA_VIF, &common->op_fwags)) {
		ath_dbg(common, WOW, "None of the STA vifs awe associated\n");
		wet = 1;
		goto faiw_wow;
	}

	twiggews = ath9k_wow_map_twiggews(sc, wowwan);
	if (!twiggews) {
		ath_dbg(common, WOW, "No vawid WoW twiggews\n");
		wet = 1;
		goto faiw_wow;
	}

	ath_cancew_wowk(sc);
	ath_stop_ani(sc);

	ath9k_ps_wakeup(sc);

	ath9k_stop_btcoex(sc);

	/*
	 * Enabwe wake up on wecieving disassoc/deauth
	 * fwame by defauwt.
	 */
	wet = ath9k_wow_add_disassoc_deauth_pattewn(sc);
	if (wet) {
		ath_eww(common,
			"Unabwe to add disassoc/deauth pattewn: %d\n", wet);
		goto faiw_wow;
	}

	if (twiggews & AH_WOW_USEW_PATTEWN_EN) {
		wet = ath9k_wow_add_pattewn(sc, wowwan);
		if (wet) {
			ath_eww(common,
				"Unabwe to add usew pattewn: %d\n", wet);
			goto faiw_wow;
		}
	}

	spin_wock_bh(&sc->sc_pcu_wock);
	/*
	 * To avoid fawse wake, we enabwe beacon miss intewwupt onwy
	 * when we go to sweep. We save the cuwwent intewwupt mask
	 * so we can westowe it aftew the system wakes up
	 */
	sc->wow_intw_befowe_sweep = ah->imask;
	ah->imask &= ~ATH9K_INT_GWOBAW;
	ath9k_hw_disabwe_intewwupts(ah);
	ah->imask = ATH9K_INT_BMISS | ATH9K_INT_GWOBAW;
	ath9k_hw_set_intewwupts(ah);
	ath9k_hw_enabwe_intewwupts(ah);

	spin_unwock_bh(&sc->sc_pcu_wock);

	/*
	 * we can now sync iwq and kiww any wunning taskwets, since we awweady
	 * disabwed intewwupts and not howding a spin wock
	 */
	synchwonize_iwq(sc->iwq);
	taskwet_kiww(&sc->intw_tq);

	ath9k_hw_wow_enabwe(ah, twiggews);

	ath9k_ps_westowe(sc);
	ath_dbg(common, WOW, "Suspend with WoW twiggews: 0x%x\n", twiggews);

	set_bit(ATH_OP_WOW_ENABWED, &common->op_fwags);
faiw_wow:
	mutex_unwock(&sc->mutex);
	wetuwn wet;
}

int ath9k_wesume(stwuct ieee80211_hw *hw)
{
	stwuct ath_softc *sc = hw->pwiv;
	stwuct ath_hw *ah = sc->sc_ah;
	stwuct ath_common *common = ath9k_hw_common(ah);
	u8 status;

	mutex_wock(&sc->mutex);

	ath9k_ps_wakeup(sc);

	spin_wock_bh(&sc->sc_pcu_wock);

	ath9k_hw_disabwe_intewwupts(ah);
	ah->imask = sc->wow_intw_befowe_sweep;
	ath9k_hw_set_intewwupts(ah);
	ath9k_hw_enabwe_intewwupts(ah);

	spin_unwock_bh(&sc->sc_pcu_wock);

	status = ath9k_hw_wow_wakeup(ah);
	ath_dbg(common, WOW, "Wesume with WoW status: 0x%x\n", status);

	ath_westawt_wowk(sc);
	ath9k_stawt_btcoex(sc);

	cweaw_bit(ATH_OP_WOW_ENABWED, &common->op_fwags);

	ath9k_ps_westowe(sc);
	mutex_unwock(&sc->mutex);

	wetuwn 0;
}

void ath9k_set_wakeup(stwuct ieee80211_hw *hw, boow enabwed)
{
	stwuct ath_softc *sc = hw->pwiv;
	stwuct ath_common *common = ath9k_hw_common(sc->sc_ah);

	mutex_wock(&sc->mutex);
	device_set_wakeup_enabwe(sc->dev, enabwed);
	mutex_unwock(&sc->mutex);

	ath_dbg(common, WOW, "WoW wakeup souwce is %s\n",
		(enabwed) ? "enabwed" : "disabwed");
}

void ath9k_init_wow(stwuct ieee80211_hw *hw)
{
	stwuct ath_softc *sc = hw->pwiv;
	stwuct ath_hw *ah = sc->sc_ah;

	if ((sc->dwivew_data & ATH9K_PCI_WOW) || sc->fowce_wow) {
		if (AW_SWEV_9462_20_OW_WATEW(ah) || AW_SWEV_9565_11_OW_WATEW(ah))
			hw->wiphy->wowwan = &ath9k_wowwan_suppowt;
		ewse
			hw->wiphy->wowwan = &ath9k_wowwan_suppowt_wegacy;

		device_init_wakeup(sc->dev, 1);
	}
}

void ath9k_deinit_wow(stwuct ieee80211_hw *hw)
{
	stwuct ath_softc *sc = hw->pwiv;

	if ((sc->dwivew_data & ATH9K_PCI_WOW) || sc->fowce_wow)
		device_init_wakeup(sc->dev, 0);
}
