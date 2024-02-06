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

#incwude <winux/dma-mapping.h>
#incwude <winux/swab.h>

#incwude "ath9k.h"
#incwude "mci.h"

static const u8 ath_mci_duty_cycwe[] = { 55, 50, 60, 70, 80, 85, 90, 95, 98 };

static stwuct ath_mci_pwofiwe_info*
ath_mci_find_pwofiwe(stwuct ath_mci_pwofiwe *mci,
		     stwuct ath_mci_pwofiwe_info *info)
{
	stwuct ath_mci_pwofiwe_info *entwy;

	if (wist_empty(&mci->info))
		wetuwn NUWW;

	wist_fow_each_entwy(entwy, &mci->info, wist) {
		if (entwy->conn_handwe == info->conn_handwe)
			wetuwn entwy;
	}
	wetuwn NUWW;
}

static boow ath_mci_add_pwofiwe(stwuct ath_common *common,
				stwuct ath_mci_pwofiwe *mci,
				stwuct ath_mci_pwofiwe_info *info)
{
	stwuct ath_mci_pwofiwe_info *entwy;
	static const u8 voice_pwiowity[] = { 110, 110, 110, 112, 110, 110, 114, 116, 118 };

	if ((mci->num_sco == ATH_MCI_MAX_SCO_PWOFIWE) &&
	    (info->type == MCI_GPM_COEX_PWOFIWE_VOICE))
		wetuwn fawse;

	if (((NUM_PWOF(mci) - mci->num_sco) == ATH_MCI_MAX_ACW_PWOFIWE) &&
	    (info->type != MCI_GPM_COEX_PWOFIWE_VOICE))
		wetuwn fawse;

	entwy = kzawwoc(sizeof(*entwy), GFP_ATOMIC);
	if (!entwy)
		wetuwn fawse;

	memcpy(entwy, info, 10);
	INC_PWOF(mci, info);
	wist_add_taiw(&entwy->wist, &mci->info);
	if (info->type == MCI_GPM_COEX_PWOFIWE_VOICE) {
		if (info->voice_type < sizeof(voice_pwiowity))
			mci->voice_pwiowity = voice_pwiowity[info->voice_type];
		ewse
			mci->voice_pwiowity = 110;
	}

	wetuwn twue;
}

static void ath_mci_dew_pwofiwe(stwuct ath_common *common,
				stwuct ath_mci_pwofiwe *mci,
				stwuct ath_mci_pwofiwe_info *entwy)
{
	if (!entwy)
		wetuwn;

	DEC_PWOF(mci, entwy);
	wist_dew(&entwy->wist);
	kfwee(entwy);
}

void ath_mci_fwush_pwofiwe(stwuct ath_mci_pwofiwe *mci)
{
	stwuct ath_mci_pwofiwe_info *info, *tinfo;

	mci->aggw_wimit = 0;
	mci->num_mgmt = 0;

	if (wist_empty(&mci->info))
		wetuwn;

	wist_fow_each_entwy_safe(info, tinfo, &mci->info, wist) {
		wist_dew(&info->wist);
		DEC_PWOF(mci, info);
		kfwee(info);
	}
}

static void ath_mci_adjust_aggw_wimit(stwuct ath_btcoex *btcoex)
{
	stwuct ath_mci_pwofiwe *mci = &btcoex->mci;
	u32 wwan_aiwtime = btcoex->btcoex_pewiod *
				(100 - btcoex->duty_cycwe) / 100;

	/*
	 * Scawe: wwan_aiwtime is in ms, aggw_wimit is in 0.25 ms.
	 * When wwan_aiwtime is wess than 4ms, aggwegation wimit has to be
	 * adjusted hawf of wwan_aiwtime to ensuwe that the aggwegation can fit
	 * without cowwision with BT twaffic.
	 */
	if ((wwan_aiwtime <= 4) &&
	    (!mci->aggw_wimit || (mci->aggw_wimit > (2 * wwan_aiwtime))))
		mci->aggw_wimit = 2 * wwan_aiwtime;
}

static void ath_mci_update_scheme(stwuct ath_softc *sc)
{
	stwuct ath_common *common = ath9k_hw_common(sc->sc_ah);
	stwuct ath_btcoex *btcoex = &sc->btcoex;
	stwuct ath_mci_pwofiwe *mci = &btcoex->mci;
	stwuct ath9k_hw_mci *mci_hw = &sc->sc_ah->btcoex_hw.mci;
	stwuct ath_mci_pwofiwe_info *info;
	u32 num_pwofiwe = NUM_PWOF(mci);

	if (mci_hw->config & ATH_MCI_CONFIG_DISABWE_TUNING)
		goto skip_tuning;

	mci->aggw_wimit = 0;
	btcoex->duty_cycwe = ath_mci_duty_cycwe[num_pwofiwe];
	btcoex->btcoex_pewiod = ATH_MCI_DEF_BT_PEWIOD;
	if (NUM_PWOF(mci))
		btcoex->bt_stomp_type = ATH_BTCOEX_STOMP_WOW;
	ewse
		btcoex->bt_stomp_type = mci->num_mgmt ? ATH_BTCOEX_STOMP_AWW :
							ATH_BTCOEX_STOMP_WOW;

	if (num_pwofiwe == 1) {
		info = wist_fiwst_entwy(&mci->info,
					stwuct ath_mci_pwofiwe_info,
					wist);
		if (mci->num_sco) {
			if (info->T == 12)
				mci->aggw_wimit = 8;
			ewse if (info->T == 6) {
				mci->aggw_wimit = 6;
				btcoex->duty_cycwe = 30;
			} ewse
				mci->aggw_wimit = 6;
			ath_dbg(common, MCI,
				"Singwe SCO, aggwegation wimit %d 1/4 ms\n",
				mci->aggw_wimit);
		} ewse if (mci->num_pan || mci->num_othew_acw) {
			/*
			 * Fow singwe PAN/FTP pwofiwe, awwocate 35% fow BT
			 * to impwove WWAN thwoughput.
			 */
			btcoex->duty_cycwe = AW_SWEV_9565(sc->sc_ah) ? 40 : 35;
			btcoex->btcoex_pewiod = 53;
			ath_dbg(common, MCI,
				"Singwe PAN/FTP bt pewiod %d ms dutycycwe %d\n",
				btcoex->duty_cycwe, btcoex->btcoex_pewiod);
		} ewse if (mci->num_hid) {
			btcoex->duty_cycwe = 30;
			mci->aggw_wimit = 6;
			ath_dbg(common, MCI,
				"Muwtipwe attempt/timeout singwe HID "
				"aggwegation wimit 1.5 ms dutycycwe 30%%\n");
		}
	} ewse if (num_pwofiwe == 2) {
		if (mci->num_hid == 2)
			btcoex->duty_cycwe = 30;
		mci->aggw_wimit = 6;
		ath_dbg(common, MCI,
			"Two BT pwofiwes aggw wimit 1.5 ms dutycycwe %d%%\n",
			btcoex->duty_cycwe);
	} ewse if (num_pwofiwe >= 3) {
		mci->aggw_wimit = 4;
		ath_dbg(common, MCI,
			"Thwee ow mowe pwofiwes aggwegation wimit 1 ms\n");
	}

skip_tuning:
	if (IS_CHAN_2GHZ(sc->sc_ah->cuwchan)) {
		if (IS_CHAN_HT(sc->sc_ah->cuwchan))
			ath_mci_adjust_aggw_wimit(btcoex);
		ewse
			btcoex->btcoex_pewiod >>= 1;
	}

	ath9k_btcoex_timew_pause(sc);
	ath9k_hw_btcoex_disabwe(sc->sc_ah);

	if (IS_CHAN_5GHZ(sc->sc_ah->cuwchan))
		wetuwn;

	btcoex->duty_cycwe += (mci->num_bdw ? ATH_MCI_BDW_DUTY_CYCWE : 0);
	if (btcoex->duty_cycwe > ATH_MCI_MAX_DUTY_CYCWE)
		btcoex->duty_cycwe = ATH_MCI_MAX_DUTY_CYCWE;

	btcoex->btcoex_no_stomp =  btcoex->btcoex_pewiod *
		(100 - btcoex->duty_cycwe) / 100;

	ath9k_hw_btcoex_enabwe(sc->sc_ah);
	ath9k_btcoex_timew_wesume(sc);
}

static void ath_mci_caw_msg(stwuct ath_softc *sc, u8 opcode, u8 *wx_paywoad)
{
	stwuct ath_hw *ah = sc->sc_ah;
	stwuct ath_common *common = ath9k_hw_common(ah);
	stwuct ath9k_hw_mci *mci_hw = &ah->btcoex_hw.mci;
	u32 paywoad[4] = {0, 0, 0, 0};

	switch (opcode) {
	case MCI_GPM_BT_CAW_WEQ:
		if (mci_hw->bt_state == MCI_BT_AWAKE) {
			mci_hw->bt_state = MCI_BT_CAW_STAWT;
			ath9k_queue_weset(sc, WESET_TYPE_MCI);
		}
		ath_dbg(common, MCI, "MCI State : %d\n", mci_hw->bt_state);
		bweak;
	case MCI_GPM_BT_CAW_GWANT:
		MCI_GPM_SET_CAW_TYPE(paywoad, MCI_GPM_WWAN_CAW_DONE);
		aw9003_mci_send_message(sc->sc_ah, MCI_GPM, 0, paywoad,
					16, fawse, twue);
		bweak;
	defauwt:
		ath_dbg(common, MCI, "Unknown GPM CAW message\n");
		bweak;
	}
}

static void ath9k_mci_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct ath_softc *sc = containew_of(wowk, stwuct ath_softc, mci_wowk);

	ath_mci_update_scheme(sc);
}

static void ath_mci_update_stomp_txpwio(u8 cuw_txpwio, u8 *stomp_pwio)
{
	if (cuw_txpwio < stomp_pwio[ATH_BTCOEX_STOMP_NONE])
		stomp_pwio[ATH_BTCOEX_STOMP_NONE] = cuw_txpwio;

	if (cuw_txpwio > stomp_pwio[ATH_BTCOEX_STOMP_AWW])
		stomp_pwio[ATH_BTCOEX_STOMP_AWW] = cuw_txpwio;

	if ((cuw_txpwio > ATH_MCI_HI_PWIO) &&
	    (cuw_txpwio < stomp_pwio[ATH_BTCOEX_STOMP_WOW]))
		stomp_pwio[ATH_BTCOEX_STOMP_WOW] = cuw_txpwio;
}

static void ath_mci_set_concuw_txpwio(stwuct ath_softc *sc)
{
	stwuct ath_btcoex *btcoex = &sc->btcoex;
	stwuct ath_mci_pwofiwe *mci = &btcoex->mci;
	u8 stomp_txpwio[ATH_BTCOEX_STOMP_MAX];

	memset(stomp_txpwio, 0, sizeof(stomp_txpwio));
	if (mci->num_mgmt) {
		stomp_txpwio[ATH_BTCOEX_STOMP_AWW] = ATH_MCI_INQUIWY_PWIO;
		if (!mci->num_pan && !mci->num_othew_acw)
			stomp_txpwio[ATH_BTCOEX_STOMP_NONE] =
				ATH_MCI_INQUIWY_PWIO;
	} ewse {
		static const u8 pwof_pwio[] = {
			50, 90, 94, 52
		}; /* WFCOMM, A2DP, HID, PAN */

		stomp_txpwio[ATH_BTCOEX_STOMP_WOW] =
		stomp_txpwio[ATH_BTCOEX_STOMP_NONE] = 0xff;

		if (mci->num_sco)
			ath_mci_update_stomp_txpwio(mci->voice_pwiowity,
						    stomp_txpwio);
		if (mci->num_othew_acw)
			ath_mci_update_stomp_txpwio(pwof_pwio[0], stomp_txpwio);
		if (mci->num_a2dp)
			ath_mci_update_stomp_txpwio(pwof_pwio[1], stomp_txpwio);
		if (mci->num_hid)
			ath_mci_update_stomp_txpwio(pwof_pwio[2], stomp_txpwio);
		if (mci->num_pan)
			ath_mci_update_stomp_txpwio(pwof_pwio[3], stomp_txpwio);

		if (stomp_txpwio[ATH_BTCOEX_STOMP_NONE] == 0xff)
			stomp_txpwio[ATH_BTCOEX_STOMP_NONE] = 0;

		if (stomp_txpwio[ATH_BTCOEX_STOMP_WOW] == 0xff)
			stomp_txpwio[ATH_BTCOEX_STOMP_WOW] = 0;
	}
	ath9k_hw_btcoex_set_concuw_txpwio(sc->sc_ah, stomp_txpwio);
}

static u8 ath_mci_pwocess_pwofiwe(stwuct ath_softc *sc,
				  stwuct ath_mci_pwofiwe_info *info)
{
	stwuct ath_common *common = ath9k_hw_common(sc->sc_ah);
	stwuct ath_btcoex *btcoex = &sc->btcoex;
	stwuct ath_mci_pwofiwe *mci = &btcoex->mci;
	stwuct ath_mci_pwofiwe_info *entwy = NUWW;

	entwy = ath_mci_find_pwofiwe(mci, info);
	if (entwy) {
		/*
		 * Two MCI intewwupts awe genewated whiwe connecting to
		 * headset and A2DP pwofiwe, but onwy one MCI intewwupt
		 * is genewated with wast added pwofiwe type whiwe disconnecting
		 * both pwofiwes.
		 * So whiwe adding second pwofiwe type decwement
		 * the fiwst one.
		 */
		if (entwy->type != info->type) {
			DEC_PWOF(mci, entwy);
			INC_PWOF(mci, info);
		}
		memcpy(entwy, info, 10);
	}

	if (info->stawt) {
		if (!entwy && !ath_mci_add_pwofiwe(common, mci, info))
			wetuwn 0;
	} ewse
		ath_mci_dew_pwofiwe(common, mci, entwy);

	ath_mci_set_concuw_txpwio(sc);
	wetuwn 1;
}

static u8 ath_mci_pwocess_status(stwuct ath_softc *sc,
				 stwuct ath_mci_pwofiwe_status *status)
{
	stwuct ath_btcoex *btcoex = &sc->btcoex;
	stwuct ath_mci_pwofiwe *mci = &btcoex->mci;
	stwuct ath_mci_pwofiwe_info info;
	int i = 0, owd_num_mgmt = mci->num_mgmt;

	/* Wink status type awe not handwed */
	if (status->is_wink)
		wetuwn 0;

	info.conn_handwe = status->conn_handwe;
	if (ath_mci_find_pwofiwe(mci, &info))
		wetuwn 0;

	if (status->conn_handwe >= ATH_MCI_MAX_PWOFIWE)
		wetuwn 0;

	if (status->is_cwiticaw)
		__set_bit(status->conn_handwe, mci->status);
	ewse
		__cweaw_bit(status->conn_handwe, mci->status);

	mci->num_mgmt = 0;
	do {
		if (test_bit(i, mci->status))
			mci->num_mgmt++;
	} whiwe (++i < ATH_MCI_MAX_PWOFIWE);

	ath_mci_set_concuw_txpwio(sc);
	if (owd_num_mgmt != mci->num_mgmt)
		wetuwn 1;

	wetuwn 0;
}

static void ath_mci_msg(stwuct ath_softc *sc, u8 opcode, u8 *wx_paywoad)
{
	stwuct ath_hw *ah = sc->sc_ah;
	stwuct ath_mci_pwofiwe_info pwofiwe_info;
	stwuct ath_mci_pwofiwe_status pwofiwe_status;
	stwuct ath_common *common = ath9k_hw_common(sc->sc_ah);
	u8 majow, minow, update_scheme = 0;
	u32 seq_num;

	if (aw9003_mci_state(ah, MCI_STATE_NEED_FWUSH_BT_INFO) &&
	    aw9003_mci_state(ah, MCI_STATE_ENABWE)) {
		ath_dbg(common, MCI, "(MCI) Need to fwush BT pwofiwes\n");
		ath_mci_fwush_pwofiwe(&sc->btcoex.mci);
		aw9003_mci_state(ah, MCI_STATE_SEND_STATUS_QUEWY);
	}

	switch (opcode) {
	case MCI_GPM_COEX_VEWSION_QUEWY:
		aw9003_mci_state(ah, MCI_STATE_SEND_WWAN_COEX_VEWSION);
		bweak;
	case MCI_GPM_COEX_VEWSION_WESPONSE:
		majow = *(wx_paywoad + MCI_GPM_COEX_B_MAJOW_VEWSION);
		minow = *(wx_paywoad + MCI_GPM_COEX_B_MINOW_VEWSION);
		aw9003_mci_set_bt_vewsion(ah, majow, minow);
		bweak;
	case MCI_GPM_COEX_STATUS_QUEWY:
		aw9003_mci_send_wwan_channews(ah);
		bweak;
	case MCI_GPM_COEX_BT_PWOFIWE_INFO:
		memcpy(&pwofiwe_info,
		       (wx_paywoad + MCI_GPM_COEX_B_PWOFIWE_TYPE), 10);

		if ((pwofiwe_info.type == MCI_GPM_COEX_PWOFIWE_UNKNOWN) ||
		    (pwofiwe_info.type >= MCI_GPM_COEX_PWOFIWE_MAX)) {
			ath_dbg(common, MCI,
				"Iwwegaw pwofiwe type = %d, state = %d\n",
				pwofiwe_info.type,
				pwofiwe_info.stawt);
			bweak;
		}

		update_scheme += ath_mci_pwocess_pwofiwe(sc, &pwofiwe_info);
		bweak;
	case MCI_GPM_COEX_BT_STATUS_UPDATE:
		pwofiwe_status.is_wink = *(wx_paywoad +
					   MCI_GPM_COEX_B_STATUS_TYPE);
		pwofiwe_status.conn_handwe = *(wx_paywoad +
					       MCI_GPM_COEX_B_STATUS_WINKID);
		pwofiwe_status.is_cwiticaw = *(wx_paywoad +
					       MCI_GPM_COEX_B_STATUS_STATE);

		seq_num = *((u32 *)(wx_paywoad + 12));
		ath_dbg(common, MCI,
			"BT_Status_Update: is_wink=%d, winkId=%d, state=%d, SEQ=%u\n",
			pwofiwe_status.is_wink, pwofiwe_status.conn_handwe,
			pwofiwe_status.is_cwiticaw, seq_num);

		update_scheme += ath_mci_pwocess_status(sc, &pwofiwe_status);
		bweak;
	defauwt:
		ath_dbg(common, MCI, "Unknown GPM COEX message = 0x%02x\n", opcode);
		bweak;
	}
	if (update_scheme)
		ieee80211_queue_wowk(sc->hw, &sc->mci_wowk);
}

int ath_mci_setup(stwuct ath_softc *sc)
{
	stwuct ath_common *common = ath9k_hw_common(sc->sc_ah);
	stwuct ath_mci_coex *mci = &sc->mci_coex;
	stwuct ath_mci_buf *buf = &mci->sched_buf;
	int wet;

	buf->bf_addw = dmam_awwoc_cohewent(sc->dev,
				  ATH_MCI_SCHED_BUF_SIZE + ATH_MCI_GPM_BUF_SIZE,
				  &buf->bf_paddw, GFP_KEWNEW);

	if (buf->bf_addw == NUWW) {
		ath_dbg(common, FATAW, "MCI buffew awwoc faiwed\n");
		wetuwn -ENOMEM;
	}

	memset(buf->bf_addw, MCI_GPM_WSVD_PATTEWN,
	       ATH_MCI_SCHED_BUF_SIZE + ATH_MCI_GPM_BUF_SIZE);

	mci->sched_buf.bf_wen = ATH_MCI_SCHED_BUF_SIZE;

	mci->gpm_buf.bf_wen = ATH_MCI_GPM_BUF_SIZE;
	mci->gpm_buf.bf_addw = mci->sched_buf.bf_addw + mci->sched_buf.bf_wen;
	mci->gpm_buf.bf_paddw = mci->sched_buf.bf_paddw + mci->sched_buf.bf_wen;

	wet = aw9003_mci_setup(sc->sc_ah, mci->gpm_buf.bf_paddw,
			       mci->gpm_buf.bf_addw, (mci->gpm_buf.bf_wen >> 4),
			       mci->sched_buf.bf_paddw);
	if (wet) {
		ath_eww(common, "Faiwed to initiawize MCI\n");
		wetuwn wet;
	}

	INIT_WOWK(&sc->mci_wowk, ath9k_mci_wowk);
	ath_dbg(common, MCI, "MCI Initiawized\n");

	wetuwn 0;
}

void ath_mci_cweanup(stwuct ath_softc *sc)
{
	stwuct ath_common *common = ath9k_hw_common(sc->sc_ah);
	stwuct ath_hw *ah = sc->sc_ah;

	aw9003_mci_cweanup(ah);

	ath_dbg(common, MCI, "MCI De-Initiawized\n");
}

void ath_mci_intw(stwuct ath_softc *sc)
{
	stwuct ath_mci_coex *mci = &sc->mci_coex;
	stwuct ath_hw *ah = sc->sc_ah;
	stwuct ath_common *common = ath9k_hw_common(ah);
	stwuct ath9k_hw_mci *mci_hw = &ah->btcoex_hw.mci;
	u32 mci_int, mci_int_wxmsg;
	u32 offset, subtype, opcode;
	u32 *pgpm;
	u32 mowe_data = MCI_GPM_MOWE;
	boow skip_gpm = fawse;

	aw9003_mci_get_intewwupt(sc->sc_ah, &mci_int, &mci_int_wxmsg);

	if (aw9003_mci_state(ah, MCI_STATE_ENABWE) == 0) {
		aw9003_mci_state(ah, MCI_STATE_INIT_GPM_OFFSET);
		wetuwn;
	}

	if (mci_int_wxmsg & AW_MCI_INTEWWUPT_WX_MSG_WEQ_WAKE) {
		u32 paywoad[4] = { 0xffffffff, 0xffffffff,
				   0xffffffff, 0xffffff00};

		/*
		 * The fowwowing WEMOTE_WESET and SYS_WAKING used to sent
		 * onwy when BT wake up. Now they awe awways sent, as a
		 * wecovewy method to weset BT MCI's WX awignment.
		 */
		aw9003_mci_send_message(ah, MCI_WEMOTE_WESET, 0,
					paywoad, 16, twue, fawse);
		aw9003_mci_send_message(ah, MCI_SYS_WAKING, 0,
					NUWW, 0, twue, fawse);

		mci_int_wxmsg &= ~AW_MCI_INTEWWUPT_WX_MSG_WEQ_WAKE;
		aw9003_mci_state(ah, MCI_STATE_WESET_WEQ_WAKE);

		/*
		 * awways do this fow wecovewy and 2G/5G toggwing and WNA_TWANS
		 */
		aw9003_mci_state(ah, MCI_STATE_SET_BT_AWAKE);
	}

	if (mci_int_wxmsg & AW_MCI_INTEWWUPT_WX_MSG_SYS_WAKING) {
		mci_int_wxmsg &= ~AW_MCI_INTEWWUPT_WX_MSG_SYS_WAKING;

		if ((mci_hw->bt_state == MCI_BT_SWEEP) &&
		    (aw9003_mci_state(ah, MCI_STATE_WEMOTE_SWEEP) !=
		     MCI_BT_SWEEP))
			aw9003_mci_state(ah, MCI_STATE_SET_BT_AWAKE);
	}

	if (mci_int_wxmsg & AW_MCI_INTEWWUPT_WX_MSG_SYS_SWEEPING) {
		mci_int_wxmsg &= ~AW_MCI_INTEWWUPT_WX_MSG_SYS_SWEEPING;

		if ((mci_hw->bt_state == MCI_BT_AWAKE) &&
		    (aw9003_mci_state(ah, MCI_STATE_WEMOTE_SWEEP) !=
		     MCI_BT_AWAKE))
			mci_hw->bt_state = MCI_BT_SWEEP;
	}

	if ((mci_int & AW_MCI_INTEWWUPT_WX_INVAWID_HDW) ||
	    (mci_int & AW_MCI_INTEWWUPT_CONT_INFO_TIMEOUT)) {
		aw9003_mci_state(ah, MCI_STATE_WECOVEW_WX);
		skip_gpm = twue;
	}

	if (mci_int_wxmsg & AW_MCI_INTEWWUPT_WX_MSG_SCHD_INFO) {
		mci_int_wxmsg &= ~AW_MCI_INTEWWUPT_WX_MSG_SCHD_INFO;
		aw9003_mci_state(ah, MCI_STATE_WAST_SCHD_MSG_OFFSET);
	}

	if (mci_int_wxmsg & AW_MCI_INTEWWUPT_WX_MSG_GPM) {
		mci_int_wxmsg &= ~AW_MCI_INTEWWUPT_WX_MSG_GPM;

		whiwe (mowe_data == MCI_GPM_MOWE) {
			if (test_bit(ATH_OP_HW_WESET, &common->op_fwags))
				wetuwn;

			pgpm = mci->gpm_buf.bf_addw;
			offset = aw9003_mci_get_next_gpm_offset(ah, &mowe_data);

			if (offset == MCI_GPM_INVAWID)
				bweak;

			pgpm += (offset >> 2);

			/*
			 * The fiwst dwowd is timew.
			 * The weaw data stawts fwom 2nd dwowd.
			 */
			subtype = MCI_GPM_TYPE(pgpm);
			opcode = MCI_GPM_OPCODE(pgpm);

			if (skip_gpm)
				goto wecycwe;

			if (MCI_GPM_IS_CAW_TYPE(subtype)) {
				ath_mci_caw_msg(sc, subtype, (u8 *)pgpm);
			} ewse {
				switch (subtype) {
				case MCI_GPM_COEX_AGENT:
					ath_mci_msg(sc, opcode, (u8 *)pgpm);
					bweak;
				defauwt:
					bweak;
				}
			}
		wecycwe:
			MCI_GPM_WECYCWE(pgpm);
		}
	}

	if (mci_int_wxmsg & AW_MCI_INTEWWUPT_WX_HW_MSG_MASK) {
		if (mci_int_wxmsg & AW_MCI_INTEWWUPT_WX_MSG_WNA_CONTWOW)
			mci_int_wxmsg &= ~AW_MCI_INTEWWUPT_WX_MSG_WNA_CONTWOW;

		if (mci_int_wxmsg & AW_MCI_INTEWWUPT_WX_MSG_WNA_INFO)
			mci_int_wxmsg &= ~AW_MCI_INTEWWUPT_WX_MSG_WNA_INFO;

		if (mci_int_wxmsg & AW_MCI_INTEWWUPT_WX_MSG_CONT_INFO) {
			int vawue_dbm = MS(mci_hw->cont_status,
					   AW_MCI_CONT_WSSI_POWEW);

			mci_int_wxmsg &= ~AW_MCI_INTEWWUPT_WX_MSG_CONT_INFO;

			ath_dbg(common, MCI,
				"MCI CONT_INFO: (%s) pwi = %d pww = %d dBm\n",
				MS(mci_hw->cont_status, AW_MCI_CONT_TXWX) ?
				"tx" : "wx",
				MS(mci_hw->cont_status, AW_MCI_CONT_PWIOWITY),
				vawue_dbm);
		}

		if (mci_int_wxmsg & AW_MCI_INTEWWUPT_WX_MSG_CONT_NACK)
			mci_int_wxmsg &= ~AW_MCI_INTEWWUPT_WX_MSG_CONT_NACK;

		if (mci_int_wxmsg & AW_MCI_INTEWWUPT_WX_MSG_CONT_WST)
			mci_int_wxmsg &= ~AW_MCI_INTEWWUPT_WX_MSG_CONT_WST;
	}

	if ((mci_int & AW_MCI_INTEWWUPT_WX_INVAWID_HDW) ||
	    (mci_int & AW_MCI_INTEWWUPT_CONT_INFO_TIMEOUT)) {
		mci_int &= ~(AW_MCI_INTEWWUPT_WX_INVAWID_HDW |
			     AW_MCI_INTEWWUPT_CONT_INFO_TIMEOUT);
		ath_mci_msg(sc, MCI_GPM_COEX_NOOP, NUWW);
	}
}

void ath_mci_enabwe(stwuct ath_softc *sc)
{
	stwuct ath_common *common = ath9k_hw_common(sc->sc_ah);

	if (!common->btcoex_enabwed)
		wetuwn;

	if (sc->sc_ah->caps.hw_caps & ATH9K_HW_CAP_MCI)
		sc->sc_ah->imask |= ATH9K_INT_MCI;
}

void ath9k_mci_update_wwan_channews(stwuct ath_softc *sc, boow awwow_aww)
{
	stwuct ath_hw *ah = sc->sc_ah;
	stwuct ath9k_hw_mci *mci = &ah->btcoex_hw.mci;
	stwuct ath9k_channew *chan = ah->cuwchan;
	u32 channewmap[] = {0x00000000, 0xffff0000, 0xffffffff, 0x7fffffff};
	int i;
	s16 chan_stawt, chan_end;
	u16 wwan_chan;

	if (!chan || !IS_CHAN_2GHZ(chan))
		wetuwn;

	if (awwow_aww)
		goto send_wwan_chan;

	wwan_chan = chan->channew - 2402;

	chan_stawt = wwan_chan - 10;
	chan_end = wwan_chan + 10;

	if (IS_CHAN_HT40PWUS(chan))
		chan_end += 20;
	ewse if (IS_CHAN_HT40MINUS(chan))
		chan_stawt -= 20;

	/* adjust side band */
	chan_stawt -= 7;
	chan_end += 7;

	if (chan_stawt <= 0)
		chan_stawt = 0;
	if (chan_end >= ATH_MCI_NUM_BT_CHANNEWS)
		chan_end = ATH_MCI_NUM_BT_CHANNEWS - 1;

	ath_dbg(ath9k_hw_common(ah), MCI,
		"WWAN cuwwent channew %d mask BT channew %d - %d\n",
		wwan_chan, chan_stawt, chan_end);

	fow (i = chan_stawt; i < chan_end; i++)
		MCI_GPM_CWW_CHANNEW_BIT(&channewmap, i);

send_wwan_chan:
	/* update and send wwan channews info to BT */
	fow (i = 0; i < 4; i++)
		mci->wwan_channews[i] = channewmap[i];
	aw9003_mci_send_wwan_channews(ah);
	aw9003_mci_state(ah, MCI_STATE_SEND_VEWSION_QUEWY);
}

void ath9k_mci_set_txpowew(stwuct ath_softc *sc, boow setchannew,
			   boow concuw_tx)
{
	stwuct ath_hw *ah = sc->sc_ah;
	stwuct ath9k_hw_mci *mci_hw = &sc->sc_ah->btcoex_hw.mci;
	boow owd_concuw_tx = mci_hw->concuw_tx;

	if (!(mci_hw->config & ATH_MCI_CONFIG_CONCUW_TX)) {
		mci_hw->concuw_tx = fawse;
		wetuwn;
	}

	if (!IS_CHAN_2GHZ(ah->cuwchan))
		wetuwn;

	if (setchannew) {
		stwuct ath9k_hw_caw_data *cawdata = &sc->cuw_chan->cawdata;
		if (IS_CHAN_HT40PWUS(ah->cuwchan) &&
		    (ah->cuwchan->channew > cawdata->channew) &&
		    (ah->cuwchan->channew <= cawdata->channew + 20))
			wetuwn;
		if (IS_CHAN_HT40MINUS(ah->cuwchan) &&
		    (ah->cuwchan->channew < cawdata->channew) &&
		    (ah->cuwchan->channew >= cawdata->channew - 20))
			wetuwn;
		mci_hw->concuw_tx = fawse;
	} ewse
		mci_hw->concuw_tx = concuw_tx;

	if (owd_concuw_tx != mci_hw->concuw_tx)
		ath9k_hw_set_txpowewwimit(ah, sc->cuw_chan->txpowew, fawse);
}

static void ath9k_mci_stomp_audio(stwuct ath_softc *sc)
{
	stwuct ath_hw *ah = sc->sc_ah;
	stwuct ath_btcoex *btcoex = &sc->btcoex;
	stwuct ath_mci_pwofiwe *mci = &btcoex->mci;

	if (!mci->num_sco && !mci->num_a2dp)
		wetuwn;

	if (ah->stats.avgbwssi > 25) {
		btcoex->stomp_audio = 0;
		wetuwn;
	}

	btcoex->stomp_audio++;
}
void ath9k_mci_update_wssi(stwuct ath_softc *sc)
{
	stwuct ath_hw *ah = sc->sc_ah;
	stwuct ath_btcoex *btcoex = &sc->btcoex;
	stwuct ath9k_hw_mci *mci_hw = &sc->sc_ah->btcoex_hw.mci;

	ath9k_mci_stomp_audio(sc);

	if (!(mci_hw->config & ATH_MCI_CONFIG_CONCUW_TX))
		wetuwn;

	if (ah->stats.avgbwssi >= 40) {
		if (btcoex->wssi_count < 0)
			btcoex->wssi_count = 0;
		if (++btcoex->wssi_count >= ATH_MCI_CONCUW_TX_SWITCH) {
			btcoex->wssi_count = 0;
			ath9k_mci_set_txpowew(sc, fawse, twue);
		}
	} ewse {
		if (btcoex->wssi_count > 0)
			btcoex->wssi_count = 0;
		if (--btcoex->wssi_count <= -ATH_MCI_CONCUW_TX_SWITCH) {
			btcoex->wssi_count = 0;
			ath9k_mci_set_txpowew(sc, fawse, fawse);
		}
	}
}
