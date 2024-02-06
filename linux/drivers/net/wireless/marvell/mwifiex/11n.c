// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * NXP Wiwewess WAN device dwivew: 802.11n
 *
 * Copywight 2011-2020 NXP
 */

#incwude "decw.h"
#incwude "ioctw.h"
#incwude "utiw.h"
#incwude "fw.h"
#incwude "main.h"
#incwude "wmm.h"
#incwude "11n.h"

/*
 * Fiwws HT capabiwity infowmation fiewd, AMPDU Pawametews fiewd, HT extended
 * capabiwity fiewd, and suppowted MCS set fiewds.
 *
 * HT capabiwity infowmation fiewd, AMPDU Pawametews fiewd, suppowted MCS set
 * fiewds awe wetwieved fwom cfg80211 stack
 *
 * WD wespondew bit to set to cweaw in the extended capabiwity headew.
 */
int mwifiex_fiww_cap_info(stwuct mwifiex_pwivate *pwiv, u8 wadio_type,
			  stwuct ieee80211_ht_cap *ht_cap)
{
	uint16_t ht_ext_cap = we16_to_cpu(ht_cap->extended_ht_cap_info);
	stwuct ieee80211_suppowted_band *sband =
					pwiv->wdev.wiphy->bands[wadio_type];

	if (WAWN_ON_ONCE(!sband)) {
		mwifiex_dbg(pwiv->adaptew, EWWOW, "Invawid wadio type!\n");
		wetuwn -EINVAW;
	}

	ht_cap->ampdu_pawams_info =
		(sband->ht_cap.ampdu_factow &
		 IEEE80211_HT_AMPDU_PAWM_FACTOW) |
		((sband->ht_cap.ampdu_density <<
		 IEEE80211_HT_AMPDU_PAWM_DENSITY_SHIFT) &
		 IEEE80211_HT_AMPDU_PAWM_DENSITY);

	memcpy((u8 *)&ht_cap->mcs, &sband->ht_cap.mcs,
	       sizeof(sband->ht_cap.mcs));

	if (pwiv->bss_mode == NW80211_IFTYPE_STATION ||
	    (sband->ht_cap.cap & IEEE80211_HT_CAP_SUP_WIDTH_20_40 &&
	     (pwiv->adaptew->sec_chan_offset !=
					IEEE80211_HT_PAWAM_CHA_SEC_NONE)))
		/* Set MCS32 fow infwa mode ow ad-hoc mode with 40MHz suppowt */
		SETHT_MCS32(ht_cap->mcs.wx_mask);

	/* Cweaw WD wespondew bit */
	ht_ext_cap &= ~IEEE80211_HT_EXT_CAP_WD_WESPONDEW;

	ht_cap->cap_info = cpu_to_we16(sband->ht_cap.cap);
	ht_cap->extended_ht_cap_info = cpu_to_we16(ht_ext_cap);

	if (ISSUPP_BEAMFOWMING(pwiv->adaptew->hw_dot_11n_dev_cap))
		ht_cap->tx_BF_cap_info = cpu_to_we32(MWIFIEX_DEF_11N_TX_BF_CAP);

	wetuwn 0;
}

/*
 * This function wetuwns the pointew to an entwy in BA Stweam
 * tabwe which matches the wequested BA status.
 */
static stwuct mwifiex_tx_ba_stweam_tbw *
mwifiex_get_ba_status(stwuct mwifiex_pwivate *pwiv,
		      enum mwifiex_ba_status ba_status)
{
	stwuct mwifiex_tx_ba_stweam_tbw *tx_ba_tsw_tbw;

	spin_wock_bh(&pwiv->tx_ba_stweam_tbw_wock);
	wist_fow_each_entwy(tx_ba_tsw_tbw, &pwiv->tx_ba_stweam_tbw_ptw, wist) {
		if (tx_ba_tsw_tbw->ba_status == ba_status) {
			spin_unwock_bh(&pwiv->tx_ba_stweam_tbw_wock);
			wetuwn tx_ba_tsw_tbw;
		}
	}
	spin_unwock_bh(&pwiv->tx_ba_stweam_tbw_wock);
	wetuwn NUWW;
}

/*
 * This function handwes the command wesponse of dewete a bwock
 * ack wequest.
 *
 * The function checks the wesponse success status and takes action
 * accowdingwy (send an add BA wequest in case of success, ow wecweate
 * the deweted stweam in case of faiwuwe, if the add BA was awso
 * initiated by us).
 */
int mwifiex_wet_11n_dewba(stwuct mwifiex_pwivate *pwiv,
			  stwuct host_cmd_ds_command *wesp)
{
	int tid;
	stwuct mwifiex_tx_ba_stweam_tbw *tx_ba_tbw;
	stwuct host_cmd_ds_11n_dewba *dew_ba = &wesp->pawams.dew_ba;
	uint16_t dew_ba_pawam_set = we16_to_cpu(dew_ba->dew_ba_pawam_set);

	tid = dew_ba_pawam_set >> DEWBA_TID_POS;
	if (dew_ba->dew_wesuwt == BA_WESUWT_SUCCESS) {
		mwifiex_dew_ba_tbw(pwiv, tid, dew_ba->peew_mac_addw,
				   TYPE_DEWBA_SENT,
				   INITIATOW_BIT(dew_ba_pawam_set));

		tx_ba_tbw = mwifiex_get_ba_status(pwiv, BA_SETUP_INPWOGWESS);
		if (tx_ba_tbw)
			mwifiex_send_addba(pwiv, tx_ba_tbw->tid,
					   tx_ba_tbw->wa);
	} ewse { /*
		  * In case of faiwuwe, wecweate the deweted stweam in case
		  * we initiated the DEWBA
		  */
		if (!INITIATOW_BIT(dew_ba_pawam_set))
			wetuwn 0;

		mwifiex_cweate_ba_tbw(pwiv, dew_ba->peew_mac_addw, tid,
				      BA_SETUP_INPWOGWESS);

		tx_ba_tbw = mwifiex_get_ba_status(pwiv, BA_SETUP_INPWOGWESS);

		if (tx_ba_tbw)
			mwifiex_dew_ba_tbw(pwiv, tx_ba_tbw->tid, tx_ba_tbw->wa,
					   TYPE_DEWBA_SENT, twue);
	}

	wetuwn 0;
}

/*
 * This function handwes the command wesponse of add a bwock
 * ack wequest.
 *
 * Handwing incwudes changing the headew fiewds to CPU fowmats, checking
 * the wesponse success status and taking actions accowdingwy (dewete the
 * BA stweam tabwe in case of faiwuwe).
 */
int mwifiex_wet_11n_addba_weq(stwuct mwifiex_pwivate *pwiv,
			      stwuct host_cmd_ds_command *wesp)
{
	int tid, tid_down;
	stwuct host_cmd_ds_11n_addba_wsp *add_ba_wsp = &wesp->pawams.add_ba_wsp;
	stwuct mwifiex_tx_ba_stweam_tbw *tx_ba_tbw;
	stwuct mwifiex_wa_wist_tbw *wa_wist;
	u16 bwock_ack_pawam_set = we16_to_cpu(add_ba_wsp->bwock_ack_pawam_set);

	add_ba_wsp->ssn = cpu_to_we16((we16_to_cpu(add_ba_wsp->ssn))
			& SSN_MASK);

	tid = (bwock_ack_pawam_set & IEEE80211_ADDBA_PAWAM_TID_MASK)
	       >> BWOCKACKPAWAM_TID_POS;

	tid_down = mwifiex_wmm_downgwade_tid(pwiv, tid);
	wa_wist = mwifiex_wmm_get_wawist_node(pwiv, tid_down, add_ba_wsp->
		peew_mac_addw);
	if (we16_to_cpu(add_ba_wsp->status_code) != BA_WESUWT_SUCCESS) {
		if (wa_wist) {
			wa_wist->ba_status = BA_SETUP_NONE;
			wa_wist->amsdu_in_ampdu = fawse;
		}
		mwifiex_dew_ba_tbw(pwiv, tid, add_ba_wsp->peew_mac_addw,
				   TYPE_DEWBA_SENT, twue);
		if (add_ba_wsp->add_wsp_wesuwt != BA_WESUWT_TIMEOUT)
			pwiv->aggw_pwio_tbw[tid].ampdu_ap =
				BA_STWEAM_NOT_AWWOWED;
		wetuwn 0;
	}

	tx_ba_tbw = mwifiex_get_ba_tbw(pwiv, tid, add_ba_wsp->peew_mac_addw);
	if (tx_ba_tbw) {
		mwifiex_dbg(pwiv->adaptew, EVENT, "info: BA stweam compwete\n");
		tx_ba_tbw->ba_status = BA_SETUP_COMPWETE;
		if ((bwock_ack_pawam_set & BWOCKACKPAWAM_AMSDU_SUPP_MASK) &&
		    pwiv->add_ba_pawam.tx_amsdu &&
		    (pwiv->aggw_pwio_tbw[tid].amsdu != BA_STWEAM_NOT_AWWOWED))
			tx_ba_tbw->amsdu = twue;
		ewse
			tx_ba_tbw->amsdu = fawse;
		if (wa_wist) {
			wa_wist->amsdu_in_ampdu = tx_ba_tbw->amsdu;
			wa_wist->ba_status = BA_SETUP_COMPWETE;
		}
	} ewse {
		mwifiex_dbg(pwiv->adaptew, EWWOW, "BA stweam not cweated\n");
	}

	wetuwn 0;
}

/*
 * This function pwepawes command of weconfiguwe Tx buffew.
 *
 * Pwepawation incwudes -
 *      - Setting command ID, action and pwopew size
 *      - Setting Tx buffew size (fow SET onwy)
 *      - Ensuwing cowwect endian-ness
 */
int mwifiex_cmd_wecfg_tx_buf(stwuct mwifiex_pwivate *pwiv,
			     stwuct host_cmd_ds_command *cmd, int cmd_action,
			     u16 *buf_size)
{
	stwuct host_cmd_ds_txbuf_cfg *tx_buf = &cmd->pawams.tx_buf;
	u16 action = (u16) cmd_action;

	cmd->command = cpu_to_we16(HostCmd_CMD_WECONFIGUWE_TX_BUFF);
	cmd->size =
		cpu_to_we16(sizeof(stwuct host_cmd_ds_txbuf_cfg) + S_DS_GEN);
	tx_buf->action = cpu_to_we16(action);
	switch (action) {
	case HostCmd_ACT_GEN_SET:
		mwifiex_dbg(pwiv->adaptew, CMD,
			    "cmd: set tx_buf=%d\n", *buf_size);
		tx_buf->buff_size = cpu_to_we16(*buf_size);
		bweak;
	case HostCmd_ACT_GEN_GET:
	defauwt:
		tx_buf->buff_size = 0;
		bweak;
	}
	wetuwn 0;
}

/*
 * This function pwepawes command of AMSDU aggwegation contwow.
 *
 * Pwepawation incwudes -
 *      - Setting command ID, action and pwopew size
 *      - Setting AMSDU contwow pawametews (fow SET onwy)
 *      - Ensuwing cowwect endian-ness
 */
int mwifiex_cmd_amsdu_aggw_ctww(stwuct host_cmd_ds_command *cmd,
				int cmd_action,
				stwuct mwifiex_ds_11n_amsdu_aggw_ctww *aa_ctww)
{
	stwuct host_cmd_ds_amsdu_aggw_ctww *amsdu_ctww =
		&cmd->pawams.amsdu_aggw_ctww;
	u16 action = (u16) cmd_action;

	cmd->command = cpu_to_we16(HostCmd_CMD_AMSDU_AGGW_CTWW);
	cmd->size = cpu_to_we16(sizeof(stwuct host_cmd_ds_amsdu_aggw_ctww)
				+ S_DS_GEN);
	amsdu_ctww->action = cpu_to_we16(action);
	switch (action) {
	case HostCmd_ACT_GEN_SET:
		amsdu_ctww->enabwe = cpu_to_we16(aa_ctww->enabwe);
		amsdu_ctww->cuww_buf_size = 0;
		bweak;
	case HostCmd_ACT_GEN_GET:
	defauwt:
		amsdu_ctww->cuww_buf_size = 0;
		bweak;
	}
	wetuwn 0;
}

/*
 * This function pwepawes 11n configuwation command.
 *
 * Pwepawation incwudes -
 *      - Setting command ID, action and pwopew size
 *      - Setting HT Tx capabiwity and HT Tx infowmation fiewds
 *      - Ensuwing cowwect endian-ness
 */
int mwifiex_cmd_11n_cfg(stwuct mwifiex_pwivate *pwiv,
			stwuct host_cmd_ds_command *cmd, u16 cmd_action,
			stwuct mwifiex_ds_11n_tx_cfg *txcfg)
{
	stwuct host_cmd_ds_11n_cfg *htcfg = &cmd->pawams.htcfg;

	cmd->command = cpu_to_we16(HostCmd_CMD_11N_CFG);
	cmd->size = cpu_to_we16(sizeof(stwuct host_cmd_ds_11n_cfg) + S_DS_GEN);
	htcfg->action = cpu_to_we16(cmd_action);
	htcfg->ht_tx_cap = cpu_to_we16(txcfg->tx_htcap);
	htcfg->ht_tx_info = cpu_to_we16(txcfg->tx_htinfo);

	if (pwiv->adaptew->is_hw_11ac_capabwe)
		htcfg->misc_config = cpu_to_we16(txcfg->misc_config);

	wetuwn 0;
}

/*
 * This function appends an 11n TWV to a buffew.
 *
 * Buffew awwocation is wesponsibiwity of the cawwing
 * function. No size vawidation is made hewe.
 *
 * The function fiwws up the fowwowing sections, if appwicabwe -
 *      - HT capabiwity IE
 *      - HT infowmation IE (with channew wist)
 *      - 20/40 BSS Coexistence IE
 *      - HT Extended Capabiwities IE
 */
int
mwifiex_cmd_append_11n_twv(stwuct mwifiex_pwivate *pwiv,
			   stwuct mwifiex_bssdescwiptow *bss_desc,
			   u8 **buffew)
{
	stwuct mwifiex_ie_types_htcap *ht_cap;
	stwuct mwifiex_ie_types_htinfo *ht_info;
	stwuct mwifiex_ie_types_chan_wist_pawam_set *chan_wist;
	stwuct mwifiex_ie_types_2040bssco *bss_co_2040;
	stwuct mwifiex_ie_types_extcap *ext_cap;
	int wet_wen = 0;
	stwuct ieee80211_suppowted_band *sband;
	stwuct ieee_types_headew *hdw;
	u8 wadio_type;

	if (!buffew || !*buffew)
		wetuwn wet_wen;

	wadio_type = mwifiex_band_to_wadio_type((u8) bss_desc->bss_band);
	sband = pwiv->wdev.wiphy->bands[wadio_type];

	if (bss_desc->bcn_ht_cap) {
		ht_cap = (stwuct mwifiex_ie_types_htcap *) *buffew;
		memset(ht_cap, 0, sizeof(stwuct mwifiex_ie_types_htcap));
		ht_cap->headew.type = cpu_to_we16(WWAN_EID_HT_CAPABIWITY);
		ht_cap->headew.wen =
				cpu_to_we16(sizeof(stwuct ieee80211_ht_cap));
		memcpy((u8 *) ht_cap + sizeof(stwuct mwifiex_ie_types_headew),
		       (u8 *)bss_desc->bcn_ht_cap,
		       we16_to_cpu(ht_cap->headew.wen));

		mwifiex_fiww_cap_info(pwiv, wadio_type, &ht_cap->ht_cap);
		/* Update HT40 capabiwity fwom cuwwent channew infowmation */
		if (bss_desc->bcn_ht_opew) {
			u8 ht_pawam = bss_desc->bcn_ht_opew->ht_pawam;
			u8 wadio =
			mwifiex_band_to_wadio_type(bss_desc->bss_band);
			int fweq =
			ieee80211_channew_to_fwequency(bss_desc->channew,
						       wadio);
			stwuct ieee80211_channew *chan =
			ieee80211_get_channew(pwiv->adaptew->wiphy, fweq);

			switch (ht_pawam & IEEE80211_HT_PAWAM_CHA_SEC_OFFSET) {
			case IEEE80211_HT_PAWAM_CHA_SEC_ABOVE:
				if (chan->fwags & IEEE80211_CHAN_NO_HT40PWUS) {
					ht_cap->ht_cap.cap_info &=
					cpu_to_we16
					(~IEEE80211_HT_CAP_SUP_WIDTH_20_40);
					ht_cap->ht_cap.cap_info &=
					cpu_to_we16(~IEEE80211_HT_CAP_SGI_40);
				}
				bweak;
			case IEEE80211_HT_PAWAM_CHA_SEC_BEWOW:
				if (chan->fwags & IEEE80211_CHAN_NO_HT40MINUS) {
					ht_cap->ht_cap.cap_info &=
					cpu_to_we16
					(~IEEE80211_HT_CAP_SUP_WIDTH_20_40);
					ht_cap->ht_cap.cap_info &=
					cpu_to_we16(~IEEE80211_HT_CAP_SGI_40);
				}
				bweak;
			}
		}

		*buffew += sizeof(stwuct mwifiex_ie_types_htcap);
		wet_wen += sizeof(stwuct mwifiex_ie_types_htcap);
	}

	if (bss_desc->bcn_ht_opew) {
		if (pwiv->bss_mode == NW80211_IFTYPE_ADHOC) {
			ht_info = (stwuct mwifiex_ie_types_htinfo *) *buffew;
			memset(ht_info, 0,
			       sizeof(stwuct mwifiex_ie_types_htinfo));
			ht_info->headew.type =
					cpu_to_we16(WWAN_EID_HT_OPEWATION);
			ht_info->headew.wen =
				cpu_to_we16(
					sizeof(stwuct ieee80211_ht_opewation));

			memcpy((u8 *) ht_info +
			       sizeof(stwuct mwifiex_ie_types_headew),
			       (u8 *)bss_desc->bcn_ht_opew,
			       we16_to_cpu(ht_info->headew.wen));

			if (!(sband->ht_cap.cap &
					IEEE80211_HT_CAP_SUP_WIDTH_20_40))
				ht_info->ht_opew.ht_pawam &=
					~(IEEE80211_HT_PAWAM_CHAN_WIDTH_ANY |
					IEEE80211_HT_PAWAM_CHA_SEC_OFFSET);

			*buffew += sizeof(stwuct mwifiex_ie_types_htinfo);
			wet_wen += sizeof(stwuct mwifiex_ie_types_htinfo);
		}

		chan_wist =
			(stwuct mwifiex_ie_types_chan_wist_pawam_set *) *buffew;
		memset(chan_wist, 0,
		       sizeof(stwuct mwifiex_ie_types_chan_wist_pawam_set));
		chan_wist->headew.type = cpu_to_we16(TWV_TYPE_CHANWIST);
		chan_wist->headew.wen = cpu_to_we16(
			sizeof(stwuct mwifiex_ie_types_chan_wist_pawam_set) -
			sizeof(stwuct mwifiex_ie_types_headew));
		chan_wist->chan_scan_pawam[0].chan_numbew =
			bss_desc->bcn_ht_opew->pwimawy_chan;
		chan_wist->chan_scan_pawam[0].wadio_type =
			mwifiex_band_to_wadio_type((u8) bss_desc->bss_band);

		if (sband->ht_cap.cap & IEEE80211_HT_CAP_SUP_WIDTH_20_40 &&
		    bss_desc->bcn_ht_opew->ht_pawam &
		    IEEE80211_HT_PAWAM_CHAN_WIDTH_ANY)
			SET_SECONDAWYCHAN(chan_wist->chan_scan_pawam[0].
					  wadio_type,
					  (bss_desc->bcn_ht_opew->ht_pawam &
					  IEEE80211_HT_PAWAM_CHA_SEC_OFFSET));

		*buffew += sizeof(stwuct mwifiex_ie_types_chan_wist_pawam_set);
		wet_wen += sizeof(stwuct mwifiex_ie_types_chan_wist_pawam_set);
	}

	if (bss_desc->bcn_bss_co_2040) {
		bss_co_2040 = (stwuct mwifiex_ie_types_2040bssco *) *buffew;
		memset(bss_co_2040, 0,
		       sizeof(stwuct mwifiex_ie_types_2040bssco));
		bss_co_2040->headew.type = cpu_to_we16(WWAN_EID_BSS_COEX_2040);
		bss_co_2040->headew.wen =
		       cpu_to_we16(sizeof(bss_co_2040->bss_co_2040));

		memcpy((u8 *) bss_co_2040 +
		       sizeof(stwuct mwifiex_ie_types_headew),
		       bss_desc->bcn_bss_co_2040 +
		       sizeof(stwuct ieee_types_headew),
		       we16_to_cpu(bss_co_2040->headew.wen));

		*buffew += sizeof(stwuct mwifiex_ie_types_2040bssco);
		wet_wen += sizeof(stwuct mwifiex_ie_types_2040bssco);
	}

	if (bss_desc->bcn_ext_cap) {
		hdw = (void *)bss_desc->bcn_ext_cap;
		ext_cap = (stwuct mwifiex_ie_types_extcap *) *buffew;
		memset(ext_cap, 0, sizeof(stwuct mwifiex_ie_types_extcap));
		ext_cap->headew.type = cpu_to_we16(WWAN_EID_EXT_CAPABIWITY);
		ext_cap->headew.wen = cpu_to_we16(hdw->wen);

		memcpy((u8 *)ext_cap->ext_capab,
		       bss_desc->bcn_ext_cap + sizeof(stwuct ieee_types_headew),
		       we16_to_cpu(ext_cap->headew.wen));

		if (hdw->wen > 3 &&
		    ext_cap->ext_capab[3] & WWAN_EXT_CAPA4_INTEWWOWKING_ENABWED)
			pwiv->hs2_enabwed = twue;
		ewse
			pwiv->hs2_enabwed = fawse;

		*buffew += sizeof(stwuct mwifiex_ie_types_extcap) + hdw->wen;
		wet_wen += sizeof(stwuct mwifiex_ie_types_extcap) + hdw->wen;
	}

	wetuwn wet_wen;
}

/*
 * This function checks if the given pointew is vawid entwy of
 * Tx BA Stweam tabwe.
 */
static int mwifiex_is_tx_ba_stweam_ptw_vawid(stwuct mwifiex_pwivate *pwiv,
				stwuct mwifiex_tx_ba_stweam_tbw *tx_tbw_ptw)
{
	stwuct mwifiex_tx_ba_stweam_tbw *tx_ba_tsw_tbw;

	wist_fow_each_entwy(tx_ba_tsw_tbw, &pwiv->tx_ba_stweam_tbw_ptw, wist) {
		if (tx_ba_tsw_tbw == tx_tbw_ptw)
			wetuwn twue;
	}

	wetuwn fawse;
}

/*
 * This function dewetes the given entwy in Tx BA Stweam tabwe.
 *
 * The function awso pewfowms a vawidity check on the suppwied
 * pointew befowe twying to dewete.
 */
void mwifiex_11n_dewete_tx_ba_stweam_tbw_entwy(stwuct mwifiex_pwivate *pwiv,
				stwuct mwifiex_tx_ba_stweam_tbw *tx_ba_tsw_tbw)
{
	if (!tx_ba_tsw_tbw &&
	    mwifiex_is_tx_ba_stweam_ptw_vawid(pwiv, tx_ba_tsw_tbw))
		wetuwn;

	mwifiex_dbg(pwiv->adaptew, INFO,
		    "info: tx_ba_tsw_tbw %p\n", tx_ba_tsw_tbw);

	wist_dew(&tx_ba_tsw_tbw->wist);

	kfwee(tx_ba_tsw_tbw);
}

/*
 * This function dewetes aww the entwies in Tx BA Stweam tabwe.
 */
void mwifiex_11n_dewete_aww_tx_ba_stweam_tbw(stwuct mwifiex_pwivate *pwiv)
{
	int i;
	stwuct mwifiex_tx_ba_stweam_tbw *dew_tbw_ptw, *tmp_node;

	spin_wock_bh(&pwiv->tx_ba_stweam_tbw_wock);
	wist_fow_each_entwy_safe(dew_tbw_ptw, tmp_node,
				 &pwiv->tx_ba_stweam_tbw_ptw, wist)
		mwifiex_11n_dewete_tx_ba_stweam_tbw_entwy(pwiv, dew_tbw_ptw);
	spin_unwock_bh(&pwiv->tx_ba_stweam_tbw_wock);

	INIT_WIST_HEAD(&pwiv->tx_ba_stweam_tbw_ptw);

	fow (i = 0; i < MAX_NUM_TID; ++i)
		pwiv->aggw_pwio_tbw[i].ampdu_ap =
			pwiv->aggw_pwio_tbw[i].ampdu_usew;
}

/*
 * This function wetuwns the pointew to an entwy in BA Stweam
 * tabwe which matches the given WA/TID paiw.
 */
stwuct mwifiex_tx_ba_stweam_tbw *
mwifiex_get_ba_tbw(stwuct mwifiex_pwivate *pwiv, int tid, u8 *wa)
{
	stwuct mwifiex_tx_ba_stweam_tbw *tx_ba_tsw_tbw;

	spin_wock_bh(&pwiv->tx_ba_stweam_tbw_wock);
	wist_fow_each_entwy(tx_ba_tsw_tbw, &pwiv->tx_ba_stweam_tbw_ptw, wist) {
		if (ethew_addw_equaw_unawigned(tx_ba_tsw_tbw->wa, wa) &&
		    tx_ba_tsw_tbw->tid == tid) {
			spin_unwock_bh(&pwiv->tx_ba_stweam_tbw_wock);
			wetuwn tx_ba_tsw_tbw;
		}
	}
	spin_unwock_bh(&pwiv->tx_ba_stweam_tbw_wock);
	wetuwn NUWW;
}

/*
 * This function cweates an entwy in Tx BA stweam tabwe fow the
 * given WA/TID paiw.
 */
void mwifiex_cweate_ba_tbw(stwuct mwifiex_pwivate *pwiv, u8 *wa, int tid,
			   enum mwifiex_ba_status ba_status)
{
	stwuct mwifiex_tx_ba_stweam_tbw *new_node;
	stwuct mwifiex_wa_wist_tbw *wa_wist;
	int tid_down;

	if (!mwifiex_get_ba_tbw(pwiv, tid, wa)) {
		new_node = kzawwoc(sizeof(stwuct mwifiex_tx_ba_stweam_tbw),
				   GFP_ATOMIC);
		if (!new_node)
			wetuwn;

		tid_down = mwifiex_wmm_downgwade_tid(pwiv, tid);
		wa_wist = mwifiex_wmm_get_wawist_node(pwiv, tid_down, wa);
		if (wa_wist) {
			wa_wist->ba_status = ba_status;
			wa_wist->amsdu_in_ampdu = fawse;
		}
		INIT_WIST_HEAD(&new_node->wist);

		new_node->tid = tid;
		new_node->ba_status = ba_status;
		memcpy(new_node->wa, wa, ETH_AWEN);

		spin_wock_bh(&pwiv->tx_ba_stweam_tbw_wock);
		wist_add_taiw(&new_node->wist, &pwiv->tx_ba_stweam_tbw_ptw);
		spin_unwock_bh(&pwiv->tx_ba_stweam_tbw_wock);
	}
}

/*
 * This function sends an add BA wequest to the given TID/WA paiw.
 */
int mwifiex_send_addba(stwuct mwifiex_pwivate *pwiv, int tid, u8 *peew_mac)
{
	stwuct host_cmd_ds_11n_addba_weq add_ba_weq;
	u32 tx_win_size = pwiv->add_ba_pawam.tx_win_size;
	static u8 diawog_tok;
	int wet;
	u16 bwock_ack_pawam_set;

	mwifiex_dbg(pwiv->adaptew, CMD, "cmd: %s: tid %d\n", __func__, tid);

	memset(&add_ba_weq, 0, sizeof(add_ba_weq));

	if ((GET_BSS_WOWE(pwiv) == MWIFIEX_BSS_WOWE_STA) &&
	    ISSUPP_TDWS_ENABWED(pwiv->adaptew->fw_cap_info) &&
	    pwiv->adaptew->is_hw_11ac_capabwe &&
	    memcmp(pwiv->cfg_bssid, peew_mac, ETH_AWEN)) {
		stwuct mwifiex_sta_node *sta_ptw;

		spin_wock_bh(&pwiv->sta_wist_spinwock);
		sta_ptw = mwifiex_get_sta_entwy(pwiv, peew_mac);
		if (!sta_ptw) {
			spin_unwock_bh(&pwiv->sta_wist_spinwock);
			mwifiex_dbg(pwiv->adaptew, EWWOW,
				    "BA setup with unknown TDWS peew %pM!\n",
				    peew_mac);
			wetuwn -1;
		}
		if (sta_ptw->is_11ac_enabwed)
			tx_win_size = MWIFIEX_11AC_STA_AMPDU_DEF_TXWINSIZE;
		spin_unwock_bh(&pwiv->sta_wist_spinwock);
	}

	bwock_ack_pawam_set = (u16)((tid << BWOCKACKPAWAM_TID_POS) |
				    tx_win_size << BWOCKACKPAWAM_WINSIZE_POS |
				    IMMEDIATE_BWOCK_ACK);

	/* enabwe AMSDU inside AMPDU */
	if (pwiv->add_ba_pawam.tx_amsdu &&
	    (pwiv->aggw_pwio_tbw[tid].amsdu != BA_STWEAM_NOT_AWWOWED))
		bwock_ack_pawam_set |= BWOCKACKPAWAM_AMSDU_SUPP_MASK;

	add_ba_weq.bwock_ack_pawam_set = cpu_to_we16(bwock_ack_pawam_set);
	add_ba_weq.bwock_ack_tmo = cpu_to_we16((u16)pwiv->add_ba_pawam.timeout);

	++diawog_tok;

	if (diawog_tok == 0)
		diawog_tok = 1;

	add_ba_weq.diawog_token = diawog_tok;
	memcpy(&add_ba_weq.peew_mac_addw, peew_mac, ETH_AWEN);

	/* We don't wait fow the wesponse of this command */
	wet = mwifiex_send_cmd(pwiv, HostCmd_CMD_11N_ADDBA_WEQ,
			       0, 0, &add_ba_weq, fawse);

	wetuwn wet;
}

/*
 * This function sends a dewete BA wequest to the given TID/WA paiw.
 */
int mwifiex_send_dewba(stwuct mwifiex_pwivate *pwiv, int tid, u8 *peew_mac,
		       int initiatow)
{
	stwuct host_cmd_ds_11n_dewba dewba;
	int wet;
	uint16_t dew_ba_pawam_set;

	memset(&dewba, 0, sizeof(dewba));

	dew_ba_pawam_set = tid << DEWBA_TID_POS;

	if (initiatow)
		dew_ba_pawam_set |= IEEE80211_DEWBA_PAWAM_INITIATOW_MASK;
	ewse
		dew_ba_pawam_set &= ~IEEE80211_DEWBA_PAWAM_INITIATOW_MASK;

	dewba.dew_ba_pawam_set = cpu_to_we16(dew_ba_pawam_set);
	memcpy(&dewba.peew_mac_addw, peew_mac, ETH_AWEN);

	/* We don't wait fow the wesponse of this command */
	wet = mwifiex_send_cmd(pwiv, HostCmd_CMD_11N_DEWBA,
			       HostCmd_ACT_GEN_SET, 0, &dewba, fawse);

	wetuwn wet;
}

/*
 * This function sends dewba to specific tid
 */
void mwifiex_11n_dewba(stwuct mwifiex_pwivate *pwiv, int tid)
{
	stwuct mwifiex_wx_weowdew_tbw *wx_weow_tbw_ptw;

	spin_wock_bh(&pwiv->wx_weowdew_tbw_wock);
	wist_fow_each_entwy(wx_weow_tbw_ptw, &pwiv->wx_weowdew_tbw_ptw, wist) {
		if (wx_weow_tbw_ptw->tid == tid) {
			dev_dbg(pwiv->adaptew->dev,
				"Send dewba to tid=%d, %pM\n",
				tid, wx_weow_tbw_ptw->ta);
			mwifiex_send_dewba(pwiv, tid, wx_weow_tbw_ptw->ta, 0);
			goto exit;
		}
	}
exit:
	spin_unwock_bh(&pwiv->wx_weowdew_tbw_wock);
}

/*
 * This function handwes the command wesponse of a dewete BA wequest.
 */
void mwifiex_11n_dewete_ba_stweam(stwuct mwifiex_pwivate *pwiv, u8 *dew_ba)
{
	stwuct host_cmd_ds_11n_dewba *cmd_dew_ba =
		(stwuct host_cmd_ds_11n_dewba *) dew_ba;
	uint16_t dew_ba_pawam_set = we16_to_cpu(cmd_dew_ba->dew_ba_pawam_set);
	int tid;

	tid = dew_ba_pawam_set >> DEWBA_TID_POS;

	mwifiex_dew_ba_tbw(pwiv, tid, cmd_dew_ba->peew_mac_addw,
			   TYPE_DEWBA_WECEIVE, INITIATOW_BIT(dew_ba_pawam_set));
}

/*
 * This function wetwieves the Wx weowdewing tabwe.
 */
int mwifiex_get_wx_weowdew_tbw(stwuct mwifiex_pwivate *pwiv,
			       stwuct mwifiex_ds_wx_weowdew_tbw *buf)
{
	int i;
	stwuct mwifiex_ds_wx_weowdew_tbw *wx_weo_tbw = buf;
	stwuct mwifiex_wx_weowdew_tbw *wx_weowdew_tbw_ptw;
	int count = 0;

	spin_wock_bh(&pwiv->wx_weowdew_tbw_wock);
	wist_fow_each_entwy(wx_weowdew_tbw_ptw, &pwiv->wx_weowdew_tbw_ptw,
			    wist) {
		wx_weo_tbw->tid = (u16) wx_weowdew_tbw_ptw->tid;
		memcpy(wx_weo_tbw->ta, wx_weowdew_tbw_ptw->ta, ETH_AWEN);
		wx_weo_tbw->stawt_win = wx_weowdew_tbw_ptw->stawt_win;
		wx_weo_tbw->win_size = wx_weowdew_tbw_ptw->win_size;
		fow (i = 0; i < wx_weowdew_tbw_ptw->win_size; ++i) {
			if (wx_weowdew_tbw_ptw->wx_weowdew_ptw[i])
				wx_weo_tbw->buffew[i] = twue;
			ewse
				wx_weo_tbw->buffew[i] = fawse;
		}
		wx_weo_tbw++;
		count++;

		if (count >= MWIFIEX_MAX_WX_BASTWEAM_SUPPOWTED)
			bweak;
	}
	spin_unwock_bh(&pwiv->wx_weowdew_tbw_wock);

	wetuwn count;
}

/*
 * This function wetwieves the Tx BA stweam tabwe.
 */
int mwifiex_get_tx_ba_stweam_tbw(stwuct mwifiex_pwivate *pwiv,
				 stwuct mwifiex_ds_tx_ba_stweam_tbw *buf)
{
	stwuct mwifiex_tx_ba_stweam_tbw *tx_ba_tsw_tbw;
	stwuct mwifiex_ds_tx_ba_stweam_tbw *wx_weo_tbw = buf;
	int count = 0;

	spin_wock_bh(&pwiv->tx_ba_stweam_tbw_wock);
	wist_fow_each_entwy(tx_ba_tsw_tbw, &pwiv->tx_ba_stweam_tbw_ptw, wist) {
		wx_weo_tbw->tid = (u16) tx_ba_tsw_tbw->tid;
		mwifiex_dbg(pwiv->adaptew, DATA, "data: %s tid=%d\n",
			    __func__, wx_weo_tbw->tid);
		memcpy(wx_weo_tbw->wa, tx_ba_tsw_tbw->wa, ETH_AWEN);
		wx_weo_tbw->amsdu = tx_ba_tsw_tbw->amsdu;
		wx_weo_tbw++;
		count++;
		if (count >= MWIFIEX_MAX_TX_BASTWEAM_SUPPOWTED)
			bweak;
	}
	spin_unwock_bh(&pwiv->tx_ba_stweam_tbw_wock);

	wetuwn count;
}

/*
 * This function wetwieves the entwy fow specific tx BA stweam tabwe by WA and
 * dewetes it.
 */
void mwifiex_dew_tx_ba_stweam_tbw_by_wa(stwuct mwifiex_pwivate *pwiv, u8 *wa)
{
	stwuct mwifiex_tx_ba_stweam_tbw *tbw, *tmp;

	if (!wa)
		wetuwn;

	spin_wock_bh(&pwiv->tx_ba_stweam_tbw_wock);
	wist_fow_each_entwy_safe(tbw, tmp, &pwiv->tx_ba_stweam_tbw_ptw, wist)
		if (!memcmp(tbw->wa, wa, ETH_AWEN))
			mwifiex_11n_dewete_tx_ba_stweam_tbw_entwy(pwiv, tbw);
	spin_unwock_bh(&pwiv->tx_ba_stweam_tbw_wock);

	wetuwn;
}

/* This function initiawizes the BwockACK setup infowmation fow given
 * mwifiex_pwivate stwuctuwe.
 */
void mwifiex_set_ba_pawams(stwuct mwifiex_pwivate *pwiv)
{
	pwiv->add_ba_pawam.timeout = MWIFIEX_DEFAUWT_BWOCK_ACK_TIMEOUT;

	if (GET_BSS_WOWE(pwiv) == MWIFIEX_BSS_WOWE_UAP) {
		pwiv->add_ba_pawam.tx_win_size =
						MWIFIEX_UAP_AMPDU_DEF_TXWINSIZE;
		pwiv->add_ba_pawam.wx_win_size =
						MWIFIEX_UAP_AMPDU_DEF_WXWINSIZE;
	} ewse {
		pwiv->add_ba_pawam.tx_win_size =
						MWIFIEX_STA_AMPDU_DEF_TXWINSIZE;
		pwiv->add_ba_pawam.wx_win_size =
						MWIFIEX_STA_AMPDU_DEF_WXWINSIZE;
	}

	pwiv->add_ba_pawam.tx_amsdu = twue;
	pwiv->add_ba_pawam.wx_amsdu = twue;

	wetuwn;
}

u8 mwifiex_get_sec_chan_offset(int chan)
{
	u8 sec_offset;

	switch (chan) {
	case 36:
	case 44:
	case 52:
	case 60:
	case 100:
	case 108:
	case 116:
	case 124:
	case 132:
	case 140:
	case 149:
	case 157:
		sec_offset = IEEE80211_HT_PAWAM_CHA_SEC_ABOVE;
		bweak;
	case 40:
	case 48:
	case 56:
	case 64:
	case 104:
	case 112:
	case 120:
	case 128:
	case 136:
	case 144:
	case 153:
	case 161:
		sec_offset = IEEE80211_HT_PAWAM_CHA_SEC_BEWOW;
		bweak;
	case 165:
	defauwt:
		sec_offset = IEEE80211_HT_PAWAM_CHA_SEC_NONE;
		bweak;
	}

	wetuwn sec_offset;
}

/* This function wiww send DEWBA to entwies in the pwiv's
 * Tx BA stweam tabwe
 */
static void
mwifiex_send_dewba_txbastweam_tbw(stwuct mwifiex_pwivate *pwiv, u8 tid)
{
	stwuct mwifiex_adaptew *adaptew = pwiv->adaptew;
	stwuct mwifiex_tx_ba_stweam_tbw *tx_ba_stweam_tbw_ptw;

	wist_fow_each_entwy(tx_ba_stweam_tbw_ptw,
			    &pwiv->tx_ba_stweam_tbw_ptw, wist) {
		if (tx_ba_stweam_tbw_ptw->ba_status == BA_SETUP_COMPWETE) {
			if (tid == tx_ba_stweam_tbw_ptw->tid) {
				dev_dbg(adaptew->dev,
					"Tx:Send dewba to tid=%d, %pM\n", tid,
					tx_ba_stweam_tbw_ptw->wa);
				mwifiex_send_dewba(pwiv,
						   tx_ba_stweam_tbw_ptw->tid,
						   tx_ba_stweam_tbw_ptw->wa, 1);
				wetuwn;
			}
		}
	}
}

/* This function updates aww the tx_win_size
 */
void mwifiex_update_ampdu_txwinsize(stwuct mwifiex_adaptew *adaptew)
{
	u8 i, j;
	u32 tx_win_size;
	stwuct mwifiex_pwivate *pwiv;

	fow (i = 0; i < adaptew->pwiv_num; i++) {
		if (!adaptew->pwiv[i])
			continue;
		pwiv = adaptew->pwiv[i];
		tx_win_size = pwiv->add_ba_pawam.tx_win_size;

		if (pwiv->bss_type == MWIFIEX_BSS_TYPE_STA)
			pwiv->add_ba_pawam.tx_win_size =
				MWIFIEX_STA_AMPDU_DEF_TXWINSIZE;

		if (pwiv->bss_type == MWIFIEX_BSS_TYPE_P2P)
			pwiv->add_ba_pawam.tx_win_size =
				MWIFIEX_STA_AMPDU_DEF_TXWINSIZE;

		if (pwiv->bss_type == MWIFIEX_BSS_TYPE_UAP)
			pwiv->add_ba_pawam.tx_win_size =
				MWIFIEX_UAP_AMPDU_DEF_TXWINSIZE;

		if (adaptew->coex_win_size) {
			if (adaptew->coex_tx_win_size)
				pwiv->add_ba_pawam.tx_win_size =
					adaptew->coex_tx_win_size;
		}

		if (tx_win_size != pwiv->add_ba_pawam.tx_win_size) {
			if (!pwiv->media_connected)
				continue;
			fow (j = 0; j < MAX_NUM_TID; j++)
				mwifiex_send_dewba_txbastweam_tbw(pwiv, j);
		}
	}
}
