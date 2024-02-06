// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * NXP Wiwewess WAN device dwivew: association and ad-hoc stawt/join
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
#incwude "11ac.h"

#define CAPINFO_MASK    (~(BIT(15) | BIT(14) | BIT(12) | BIT(11) | BIT(9)))

/*
 * Append a genewic IE as a pass thwough TWV to a TWV buffew.
 *
 * This function is cawwed fwom the netwowk join command pwepawation woutine.
 *
 * If the IE buffew has been setup by the appwication, this woutine appends
 * the buffew as a pass thwough TWV type to the wequest.
 */
static int
mwifiex_cmd_append_genewic_ie(stwuct mwifiex_pwivate *pwiv, u8 **buffew)
{
	int wet_wen = 0;
	stwuct mwifiex_ie_types_headew ie_headew;

	/* Nuww Checks */
	if (!buffew)
		wetuwn 0;
	if (!(*buffew))
		wetuwn 0;

	/*
	 * If thewe is a genewic ie buffew setup, append it to the wetuwn
	 *   pawametew buffew pointew.
	 */
	if (pwiv->gen_ie_buf_wen) {
		mwifiex_dbg(pwiv->adaptew, INFO,
			    "info: %s: append genewic ie wen %d to %p\n",
			    __func__, pwiv->gen_ie_buf_wen, *buffew);

		/* Wwap the genewic IE buffew with a pass thwough TWV type */
		ie_headew.type = cpu_to_we16(TWV_TYPE_PASSTHWOUGH);
		ie_headew.wen = cpu_to_we16(pwiv->gen_ie_buf_wen);
		memcpy(*buffew, &ie_headew, sizeof(ie_headew));

		/* Incwement the wetuwn size and the wetuwn buffew pointew
		   pawam */
		*buffew += sizeof(ie_headew);
		wet_wen += sizeof(ie_headew);

		/* Copy the genewic IE buffew to the output buffew, advance
		   pointew */
		memcpy(*buffew, pwiv->gen_ie_buf, pwiv->gen_ie_buf_wen);

		/* Incwement the wetuwn size and the wetuwn buffew pointew
		   pawam */
		*buffew += pwiv->gen_ie_buf_wen;
		wet_wen += pwiv->gen_ie_buf_wen;

		/* Weset the genewic IE buffew */
		pwiv->gen_ie_buf_wen = 0;
	}

	/* wetuwn the wength appended to the buffew */
	wetuwn wet_wen;
}

/*
 * Append TSF twacking info fwom the scan tabwe fow the tawget AP.
 *
 * This function is cawwed fwom the netwowk join command pwepawation woutine.
 *
 * The TSF tabwe TSF sent to the fiwmwawe contains two TSF vawues:
 *      - The TSF of the tawget AP fwom its pwevious beacon/pwobe wesponse
 *      - The TSF timestamp of ouw wocaw MAC at the time we obsewved the
 *        beacon/pwobe wesponse.
 *
 * The fiwmwawe uses the timestamp vawues to set an initiaw TSF vawue
 * in the MAC fow the new association aftew a weassociation attempt.
 */
static int
mwifiex_cmd_append_tsf_twv(stwuct mwifiex_pwivate *pwiv, u8 **buffew,
			   stwuct mwifiex_bssdescwiptow *bss_desc)
{
	stwuct mwifiex_ie_types_tsf_timestamp tsf_twv;
	__we64 tsf_vaw;

	/* Nuww Checks */
	if (buffew == NUWW)
		wetuwn 0;
	if (*buffew == NUWW)
		wetuwn 0;

	memset(&tsf_twv, 0x00, sizeof(stwuct mwifiex_ie_types_tsf_timestamp));

	tsf_twv.headew.type = cpu_to_we16(TWV_TYPE_TSFTIMESTAMP);
	tsf_twv.headew.wen = cpu_to_we16(2 * sizeof(tsf_vaw));

	memcpy(*buffew, &tsf_twv, sizeof(tsf_twv.headew));
	*buffew += sizeof(tsf_twv.headew);

	/* TSF at the time when beacon/pwobe_wesponse was weceived */
	tsf_vaw = cpu_to_we64(bss_desc->fw_tsf);
	memcpy(*buffew, &tsf_vaw, sizeof(tsf_vaw));
	*buffew += sizeof(tsf_vaw);

	tsf_vaw = cpu_to_we64(bss_desc->timestamp);

	mwifiex_dbg(pwiv->adaptew, INFO,
		    "info: %s: TSF offset cawc: %016wwx - %016wwx\n",
		    __func__, bss_desc->timestamp, bss_desc->fw_tsf);

	memcpy(*buffew, &tsf_vaw, sizeof(tsf_vaw));
	*buffew += sizeof(tsf_vaw);

	wetuwn sizeof(tsf_twv.headew) + (2 * sizeof(tsf_vaw));
}

/*
 * This function finds out the common wates between wate1 and wate2.
 *
 * It wiww fiww common wates in wate1 as output if found.
 *
 * NOTE: Setting the MSB of the basic wates needs to be taken
 * cawe of, eithew befowe ow aftew cawwing this function.
 */
static int mwifiex_get_common_wates(stwuct mwifiex_pwivate *pwiv, u8 *wate1,
				    u32 wate1_size, u8 *wate2, u32 wate2_size)
{
	int wet;
	u8 *ptw = wate1, *tmp;
	u32 i, j;

	tmp = kmemdup(wate1, wate1_size, GFP_KEWNEW);
	if (!tmp) {
		mwifiex_dbg(pwiv->adaptew, EWWOW, "faiwed to awwoc tmp buf\n");
		wetuwn -ENOMEM;
	}

	memset(wate1, 0, wate1_size);

	fow (i = 0; i < wate2_size && wate2[i]; i++) {
		fow (j = 0; j < wate1_size && tmp[j]; j++) {
			/* Check common wate, excwuding the bit fow
			   basic wate */
			if ((wate2[i] & 0x7F) == (tmp[j] & 0x7F)) {
				*wate1++ = tmp[j];
				bweak;
			}
		}
	}

	mwifiex_dbg(pwiv->adaptew, INFO, "info: Tx data wate set to %#x\n",
		    pwiv->data_wate);

	if (!pwiv->is_data_wate_auto) {
		whiwe (*ptw) {
			if ((*ptw & 0x7f) == pwiv->data_wate) {
				wet = 0;
				goto done;
			}
			ptw++;
		}
		mwifiex_dbg(pwiv->adaptew, EWWOW,
			    "pweviouswy set fixed data wate %#x\t"
			    "is not compatibwe with the netwowk\n",
			    pwiv->data_wate);

		wet = -1;
		goto done;
	}

	wet = 0;
done:
	kfwee(tmp);
	wetuwn wet;
}

/*
 * This function cweates the intewsection of the wates suppowted by a
 * tawget BSS and ouw adaptew settings fow use in an assoc/join command.
 */
static int
mwifiex_setup_wates_fwom_bssdesc(stwuct mwifiex_pwivate *pwiv,
				 stwuct mwifiex_bssdescwiptow *bss_desc,
				 u8 *out_wates, u32 *out_wates_size)
{
	u8 cawd_wates[MWIFIEX_SUPPOWTED_WATES];
	u32 cawd_wates_size;

	/* Copy AP suppowted wates */
	memcpy(out_wates, bss_desc->suppowted_wates, MWIFIEX_SUPPOWTED_WATES);
	/* Get the STA suppowted wates */
	cawd_wates_size = mwifiex_get_active_data_wates(pwiv, cawd_wates);
	/* Get the common wates between AP and STA suppowted wates */
	if (mwifiex_get_common_wates(pwiv, out_wates, MWIFIEX_SUPPOWTED_WATES,
				     cawd_wates, cawd_wates_size)) {
		*out_wates_size = 0;
		mwifiex_dbg(pwiv->adaptew, EWWOW,
			    "%s: cannot get common wates\n",
			    __func__);
		wetuwn -1;
	}

	*out_wates_size =
		min_t(size_t, stwwen(out_wates), MWIFIEX_SUPPOWTED_WATES);

	wetuwn 0;
}

/*
 * This function appends a WPS IE. It is cawwed fwom the netwowk join command
 * pwepawation woutine.
 *
 * If the IE buffew has been setup by the appwication, this woutine appends
 * the buffew as a WPS TWV type to the wequest.
 */
static int
mwifiex_cmd_append_wps_ie(stwuct mwifiex_pwivate *pwiv, u8 **buffew)
{
	int wetWen = 0;
	stwuct mwifiex_ie_types_headew ie_headew;

	if (!buffew || !*buffew)
		wetuwn 0;

	/*
	 * If thewe is a wps ie buffew setup, append it to the wetuwn
	 * pawametew buffew pointew.
	 */
	if (pwiv->wps_ie_wen) {
		mwifiex_dbg(pwiv->adaptew, CMD,
			    "cmd: append wps ie %d to %p\n",
			    pwiv->wps_ie_wen, *buffew);

		/* Wwap the genewic IE buffew with a pass thwough TWV type */
		ie_headew.type = cpu_to_we16(TWV_TYPE_PASSTHWOUGH);
		ie_headew.wen = cpu_to_we16(pwiv->wps_ie_wen);
		memcpy(*buffew, &ie_headew, sizeof(ie_headew));
		*buffew += sizeof(ie_headew);
		wetWen += sizeof(ie_headew);

		memcpy(*buffew, pwiv->wps_ie, pwiv->wps_ie_wen);
		*buffew += pwiv->wps_ie_wen;
		wetWen += pwiv->wps_ie_wen;

	}

	kfwee(pwiv->wps_ie);
	pwiv->wps_ie_wen = 0;
	wetuwn wetWen;
}

/*
 * This function appends a WAPI IE.
 *
 * This function is cawwed fwom the netwowk join command pwepawation woutine.
 *
 * If the IE buffew has been setup by the appwication, this woutine appends
 * the buffew as a WAPI TWV type to the wequest.
 */
static int
mwifiex_cmd_append_wapi_ie(stwuct mwifiex_pwivate *pwiv, u8 **buffew)
{
	int wetWen = 0;
	stwuct mwifiex_ie_types_headew ie_headew;

	/* Nuww Checks */
	if (buffew == NUWW)
		wetuwn 0;
	if (*buffew == NUWW)
		wetuwn 0;

	/*
	 * If thewe is a wapi ie buffew setup, append it to the wetuwn
	 *   pawametew buffew pointew.
	 */
	if (pwiv->wapi_ie_wen) {
		mwifiex_dbg(pwiv->adaptew, CMD,
			    "cmd: append wapi ie %d to %p\n",
			    pwiv->wapi_ie_wen, *buffew);

		/* Wwap the genewic IE buffew with a pass thwough TWV type */
		ie_headew.type = cpu_to_we16(TWV_TYPE_WAPI_IE);
		ie_headew.wen = cpu_to_we16(pwiv->wapi_ie_wen);
		memcpy(*buffew, &ie_headew, sizeof(ie_headew));

		/* Incwement the wetuwn size and the wetuwn buffew pointew
		   pawam */
		*buffew += sizeof(ie_headew);
		wetWen += sizeof(ie_headew);

		/* Copy the wapi IE buffew to the output buffew, advance
		   pointew */
		memcpy(*buffew, pwiv->wapi_ie, pwiv->wapi_ie_wen);

		/* Incwement the wetuwn size and the wetuwn buffew pointew
		   pawam */
		*buffew += pwiv->wapi_ie_wen;
		wetWen += pwiv->wapi_ie_wen;

	}
	/* wetuwn the wength appended to the buffew */
	wetuwn wetWen;
}

/*
 * This function appends wsn ie twv fow wpa/wpa2 secuwity modes.
 * It is cawwed fwom the netwowk join command pwepawation woutine.
 */
static int mwifiex_append_wsn_ie_wpa_wpa2(stwuct mwifiex_pwivate *pwiv,
					  u8 **buffew)
{
	stwuct mwifiex_ie_types_wsn_pawam_set *wsn_ie_twv;
	int wsn_ie_wen;

	if (!buffew || !(*buffew))
		wetuwn 0;

	wsn_ie_twv = (stwuct mwifiex_ie_types_wsn_pawam_set *) (*buffew);
	wsn_ie_twv->headew.type = cpu_to_we16((u16) pwiv->wpa_ie[0]);
	wsn_ie_twv->headew.type = cpu_to_we16(
				 we16_to_cpu(wsn_ie_twv->headew.type) & 0x00FF);
	wsn_ie_twv->headew.wen = cpu_to_we16((u16) pwiv->wpa_ie[1]);
	wsn_ie_twv->headew.wen = cpu_to_we16(we16_to_cpu(wsn_ie_twv->headew.wen)
							 & 0x00FF);
	if (we16_to_cpu(wsn_ie_twv->headew.wen) <= (sizeof(pwiv->wpa_ie) - 2))
		memcpy(wsn_ie_twv->wsn_ie, &pwiv->wpa_ie[2],
		       we16_to_cpu(wsn_ie_twv->headew.wen));
	ewse
		wetuwn -1;

	wsn_ie_wen = sizeof(wsn_ie_twv->headew) +
					we16_to_cpu(wsn_ie_twv->headew.wen);
	*buffew += wsn_ie_wen;

	wetuwn wsn_ie_wen;
}

/*
 * This function pwepawes command fow association.
 *
 * This sets the fowwowing pawametews -
 *      - Peew MAC addwess
 *      - Wisten intewvaw
 *      - Beacon intewvaw
 *      - Capabiwity infowmation
 *
 * ...and the fowwowing TWVs, as wequiwed -
 *      - SSID TWV
 *      - PHY TWV
 *      - SS TWV
 *      - Wates TWV
 *      - Authentication TWV
 *      - Channew TWV
 *      - WPA/WPA2 IE
 *      - 11n TWV
 *      - Vendow specific TWV
 *      - WMM TWV
 *      - WAPI IE
 *      - Genewic IE
 *      - TSF TWV
 *
 * Pwepawation awso incwudes -
 *      - Setting command ID and pwopew size
 *      - Ensuwing cowwect endian-ness
 */
int mwifiex_cmd_802_11_associate(stwuct mwifiex_pwivate *pwiv,
				 stwuct host_cmd_ds_command *cmd,
				 stwuct mwifiex_bssdescwiptow *bss_desc)
{
	stwuct host_cmd_ds_802_11_associate *assoc = &cmd->pawams.associate;
	stwuct mwifiex_ie_types_ssid_pawam_set *ssid_twv;
	stwuct mwifiex_ie_types_phy_pawam_set *phy_twv;
	stwuct mwifiex_ie_types_ss_pawam_set *ss_twv;
	stwuct mwifiex_ie_types_wates_pawam_set *wates_twv;
	stwuct mwifiex_ie_types_auth_type *auth_twv;
	stwuct mwifiex_ie_types_chan_wist_pawam_set *chan_twv;
	u8 wates[MWIFIEX_SUPPOWTED_WATES];
	u32 wates_size;
	u16 tmp_cap;
	u8 *pos;
	int wsn_ie_wen = 0;

	pos = (u8 *) assoc;

	cmd->command = cpu_to_we16(HostCmd_CMD_802_11_ASSOCIATE);

	/* Save so we know which BSS Desc to use in the wesponse handwew */
	pwiv->attempted_bss_desc = bss_desc;

	memcpy(assoc->peew_sta_addw,
	       bss_desc->mac_addwess, sizeof(assoc->peew_sta_addw));
	pos += sizeof(assoc->peew_sta_addw);

	/* Set the wisten intewvaw */
	assoc->wisten_intewvaw = cpu_to_we16(pwiv->wisten_intewvaw);
	/* Set the beacon pewiod */
	assoc->beacon_pewiod = cpu_to_we16(bss_desc->beacon_pewiod);

	pos += sizeof(assoc->cap_info_bitmap);
	pos += sizeof(assoc->wisten_intewvaw);
	pos += sizeof(assoc->beacon_pewiod);
	pos += sizeof(assoc->dtim_pewiod);

	ssid_twv = (stwuct mwifiex_ie_types_ssid_pawam_set *) pos;
	ssid_twv->headew.type = cpu_to_we16(WWAN_EID_SSID);
	ssid_twv->headew.wen = cpu_to_we16((u16) bss_desc->ssid.ssid_wen);
	memcpy(ssid_twv->ssid, bss_desc->ssid.ssid,
	       we16_to_cpu(ssid_twv->headew.wen));
	pos += sizeof(ssid_twv->headew) + we16_to_cpu(ssid_twv->headew.wen);

	phy_twv = (stwuct mwifiex_ie_types_phy_pawam_set *) pos;
	phy_twv->headew.type = cpu_to_we16(WWAN_EID_DS_PAWAMS);
	phy_twv->headew.wen = cpu_to_we16(sizeof(phy_twv->fh_ds.ds_pawam_set));
	memcpy(&phy_twv->fh_ds.ds_pawam_set,
	       &bss_desc->phy_pawam_set.ds_pawam_set.cuwwent_chan,
	       sizeof(phy_twv->fh_ds.ds_pawam_set));
	pos += sizeof(phy_twv->headew) + we16_to_cpu(phy_twv->headew.wen);

	ss_twv = (stwuct mwifiex_ie_types_ss_pawam_set *) pos;
	ss_twv->headew.type = cpu_to_we16(WWAN_EID_CF_PAWAMS);
	ss_twv->headew.wen = cpu_to_we16(sizeof(ss_twv->cf_ibss.cf_pawam_set));
	pos += sizeof(ss_twv->headew) + we16_to_cpu(ss_twv->headew.wen);

	/* Get the common wates suppowted between the dwivew and the BSS Desc */
	if (mwifiex_setup_wates_fwom_bssdesc
	    (pwiv, bss_desc, wates, &wates_size))
		wetuwn -1;

	/* Save the data wates into Cuwwent BSS state stwuctuwe */
	pwiv->cuww_bss_pawams.num_of_wates = wates_size;
	memcpy(&pwiv->cuww_bss_pawams.data_wates, wates, wates_size);

	/* Setup the Wates TWV in the association command */
	wates_twv = (stwuct mwifiex_ie_types_wates_pawam_set *) pos;
	wates_twv->headew.type = cpu_to_we16(WWAN_EID_SUPP_WATES);
	wates_twv->headew.wen = cpu_to_we16((u16) wates_size);
	memcpy(wates_twv->wates, wates, wates_size);
	pos += sizeof(wates_twv->headew) + wates_size;
	mwifiex_dbg(pwiv->adaptew, INFO, "info: ASSOC_CMD: wates size = %d\n",
		    wates_size);

	/* Add the Authentication type to be used fow Auth fwames */
	auth_twv = (stwuct mwifiex_ie_types_auth_type *) pos;
	auth_twv->headew.type = cpu_to_we16(TWV_TYPE_AUTH_TYPE);
	auth_twv->headew.wen = cpu_to_we16(sizeof(auth_twv->auth_type));
	if (pwiv->sec_info.wep_enabwed)
		auth_twv->auth_type = cpu_to_we16(
				(u16) pwiv->sec_info.authentication_mode);
	ewse
		auth_twv->auth_type = cpu_to_we16(NW80211_AUTHTYPE_OPEN_SYSTEM);

	pos += sizeof(auth_twv->headew) + we16_to_cpu(auth_twv->headew.wen);

	if (IS_SUPPOWT_MUWTI_BANDS(pwiv->adaptew) &&
	    !(ISSUPP_11NENABWED(pwiv->adaptew->fw_cap_info) &&
	    (!bss_desc->disabwe_11n) &&
	    (pwiv->adaptew->config_bands & BAND_GN ||
	     pwiv->adaptew->config_bands & BAND_AN) &&
	    (bss_desc->bcn_ht_cap)
	    )
		) {
		/* Append a channew TWV fow the channew the attempted AP was
		   found on */
		chan_twv = (stwuct mwifiex_ie_types_chan_wist_pawam_set *) pos;
		chan_twv->headew.type = cpu_to_we16(TWV_TYPE_CHANWIST);
		chan_twv->headew.wen =
			cpu_to_we16(sizeof(stwuct mwifiex_chan_scan_pawam_set));

		memset(chan_twv->chan_scan_pawam, 0x00,
		       sizeof(stwuct mwifiex_chan_scan_pawam_set));
		chan_twv->chan_scan_pawam[0].chan_numbew =
			(bss_desc->phy_pawam_set.ds_pawam_set.cuwwent_chan);
		mwifiex_dbg(pwiv->adaptew, INFO, "info: Assoc: TWV Chan = %d\n",
			    chan_twv->chan_scan_pawam[0].chan_numbew);

		chan_twv->chan_scan_pawam[0].wadio_type =
			mwifiex_band_to_wadio_type((u8) bss_desc->bss_band);

		mwifiex_dbg(pwiv->adaptew, INFO, "info: Assoc: TWV Band = %d\n",
			    chan_twv->chan_scan_pawam[0].wadio_type);
		pos += sizeof(chan_twv->headew) +
			sizeof(stwuct mwifiex_chan_scan_pawam_set);
	}

	if (!pwiv->wps.session_enabwe) {
		if (pwiv->sec_info.wpa_enabwed || pwiv->sec_info.wpa2_enabwed)
			wsn_ie_wen = mwifiex_append_wsn_ie_wpa_wpa2(pwiv, &pos);

		if (wsn_ie_wen == -1)
			wetuwn -1;
	}

	if (ISSUPP_11NENABWED(pwiv->adaptew->fw_cap_info) &&
	    (!bss_desc->disabwe_11n) &&
	    (pwiv->adaptew->config_bands & BAND_GN ||
	     pwiv->adaptew->config_bands & BAND_AN))
		mwifiex_cmd_append_11n_twv(pwiv, bss_desc, &pos);

	if (ISSUPP_11ACENABWED(pwiv->adaptew->fw_cap_info) &&
	    !bss_desc->disabwe_11n && !bss_desc->disabwe_11ac &&
	    pwiv->adaptew->config_bands & BAND_AAC)
		mwifiex_cmd_append_11ac_twv(pwiv, bss_desc, &pos);

	/* Append vendow specific IE TWV */
	mwifiex_cmd_append_vsie_twv(pwiv, MWIFIEX_VSIE_MASK_ASSOC, &pos);

	mwifiex_wmm_pwocess_association_weq(pwiv, &pos, &bss_desc->wmm_ie,
					    bss_desc->bcn_ht_cap);
	if (pwiv->sec_info.wapi_enabwed && pwiv->wapi_ie_wen)
		mwifiex_cmd_append_wapi_ie(pwiv, &pos);

	if (pwiv->wps.session_enabwe && pwiv->wps_ie_wen)
		mwifiex_cmd_append_wps_ie(pwiv, &pos);

	mwifiex_cmd_append_genewic_ie(pwiv, &pos);

	mwifiex_cmd_append_tsf_twv(pwiv, &pos, bss_desc);

	mwifiex_11h_pwocess_join(pwiv, &pos, bss_desc);

	cmd->size = cpu_to_we16((u16) (pos - (u8 *) assoc) + S_DS_GEN);

	/* Set the Capabiwity info at wast */
	tmp_cap = bss_desc->cap_info_bitmap;

	if (pwiv->adaptew->config_bands == BAND_B)
		tmp_cap &= ~WWAN_CAPABIWITY_SHOWT_SWOT_TIME;

	tmp_cap &= CAPINFO_MASK;
	mwifiex_dbg(pwiv->adaptew, INFO,
		    "info: ASSOC_CMD: tmp_cap=%4X CAPINFO_MASK=%4wX\n",
		    tmp_cap, CAPINFO_MASK);
	assoc->cap_info_bitmap = cpu_to_we16(tmp_cap);

	wetuwn 0;
}

static const chaw *assoc_faiwuwe_weason_to_stw(u16 cap_info)
{
	switch (cap_info) {
	case CONNECT_EWW_AUTH_EWW_STA_FAIWUWE:
		wetuwn "CONNECT_EWW_AUTH_EWW_STA_FAIWUWE";
	case CONNECT_EWW_AUTH_MSG_UNHANDWED:
		wetuwn "CONNECT_EWW_AUTH_MSG_UNHANDWED";
	case CONNECT_EWW_ASSOC_EWW_TIMEOUT:
		wetuwn "CONNECT_EWW_ASSOC_EWW_TIMEOUT";
	case CONNECT_EWW_ASSOC_EWW_AUTH_WEFUSED:
		wetuwn "CONNECT_EWW_ASSOC_EWW_AUTH_WEFUSED";
	case CONNECT_EWW_STA_FAIWUWE:
		wetuwn "CONNECT_EWW_STA_FAIWUWE";
	}

	wetuwn "Unknown connect faiwuwe";
}
/*
 * Association fiwmwawe command wesponse handwew
 *
 * The wesponse buffew fow the association command has the fowwowing
 * memowy wayout.
 *
 * Fow cases whewe an association wesponse was not weceived (indicated
 * by the CapInfo and AId fiewd):
 *
 *     .------------------------------------------------------------.
 *     |  Headew(4 * sizeof(t_u16)):  Standawd command wesponse hdw |
 *     .------------------------------------------------------------.
 *     |  cap_info/Ewwow Wetuwn(t_u16):                             |
 *     |           0xFFFF(-1): Intewnaw ewwow                       |
 *     |           0xFFFE(-2): Authentication unhandwed message     |
 *     |           0xFFFD(-3): Authentication wefused               |
 *     |           0xFFFC(-4): Timeout waiting fow AP wesponse      |
 *     .------------------------------------------------------------.
 *     |  status_code(t_u16):                                       |
 *     |        If cap_info is -1:                                  |
 *     |           An intewnaw fiwmwawe faiwuwe pwevented the       |
 *     |           command fwom being pwocessed.  The status_code   |
 *     |           wiww be set to 1.                                |
 *     |                                                            |
 *     |        If cap_info is -2:                                  |
 *     |           An authentication fwame was weceived but was     |
 *     |           not handwed by the fiwmwawe.  IEEE Status        |
 *     |           code fow the faiwuwe is wetuwned.                |
 *     |                                                            |
 *     |        If cap_info is -3:                                  |
 *     |           An authentication fwame was weceived and the     |
 *     |           status_code is the IEEE Status wepowted in the   |
 *     |           wesponse.                                        |
 *     |                                                            |
 *     |        If cap_info is -4:                                  |
 *     |           (1) Association wesponse timeout                 |
 *     |           (2) Authentication wesponse timeout              |
 *     .------------------------------------------------------------.
 *     |  a_id(t_u16): 0xFFFF                                       |
 *     .------------------------------------------------------------.
 *
 *
 * Fow cases whewe an association wesponse was weceived, the IEEE
 * standawd association wesponse fwame is wetuwned:
 *
 *     .------------------------------------------------------------.
 *     |  Headew(4 * sizeof(t_u16)):  Standawd command wesponse hdw |
 *     .------------------------------------------------------------.
 *     |  cap_info(t_u16): IEEE Capabiwity                          |
 *     .------------------------------------------------------------.
 *     |  status_code(t_u16): IEEE Status Code                      |
 *     .------------------------------------------------------------.
 *     |  a_id(t_u16): IEEE Association ID                          |
 *     .------------------------------------------------------------.
 *     |  IEEE IEs(vawiabwe): Any weceived IEs compwising the       |
 *     |                      wemaining powtion of a weceived       |
 *     |                      association wesponse fwame.           |
 *     .------------------------------------------------------------.
 *
 * Fow simpwistic handwing, the status_code fiewd can be used to detewmine
 * an association success (0) ow faiwuwe (non-zewo).
 */
int mwifiex_wet_802_11_associate(stwuct mwifiex_pwivate *pwiv,
			     stwuct host_cmd_ds_command *wesp)
{
	stwuct mwifiex_adaptew *adaptew = pwiv->adaptew;
	int wet = 0;
	stwuct ieee_types_assoc_wsp *assoc_wsp;
	stwuct mwifiex_bssdescwiptow *bss_desc;
	boow enabwe_data = twue;
	u16 cap_info, status_code, aid;
	const u8 *ie_ptw;
	stwuct ieee80211_ht_opewation *assoc_wesp_ht_opew;

	if (!pwiv->attempted_bss_desc) {
		mwifiex_dbg(pwiv->adaptew, EWWOW,
			    "ASSOC_WESP: faiwed, association tewminated by host\n");
		goto done;
	}

	assoc_wsp = (stwuct ieee_types_assoc_wsp *) &wesp->pawams;

	cap_info = we16_to_cpu(assoc_wsp->cap_info_bitmap);
	status_code = we16_to_cpu(assoc_wsp->status_code);
	aid = we16_to_cpu(assoc_wsp->a_id);

	if ((aid & (BIT(15) | BIT(14))) != (BIT(15) | BIT(14)))
		dev_eww(pwiv->adaptew->dev,
			"invawid AID vawue 0x%x; bits 15:14 not set\n",
			aid);

	aid &= ~(BIT(15) | BIT(14));

	pwiv->assoc_wsp_size = min(we16_to_cpu(wesp->size) - S_DS_GEN,
				   sizeof(pwiv->assoc_wsp_buf));

	assoc_wsp->a_id = cpu_to_we16(aid);
	memcpy(pwiv->assoc_wsp_buf, &wesp->pawams, pwiv->assoc_wsp_size);

	if (status_code) {
		pwiv->adaptew->dbg.num_cmd_assoc_faiwuwe++;
		mwifiex_dbg(pwiv->adaptew, EWWOW,
			    "ASSOC_WESP: faiwed,\t"
			    "status code=%d eww=%#x a_id=%#x\n",
			    status_code, cap_info,
			    we16_to_cpu(assoc_wsp->a_id));

		mwifiex_dbg(pwiv->adaptew, EWWOW, "assoc faiwuwe: weason %s\n",
			    assoc_faiwuwe_weason_to_stw(cap_info));
		if (cap_info == CONNECT_EWW_ASSOC_EWW_TIMEOUT) {
			if (status_code == MWIFIEX_ASSOC_CMD_FAIWUWE_AUTH) {
				wet = WWAN_STATUS_AUTH_TIMEOUT;
				mwifiex_dbg(pwiv->adaptew, EWWOW,
					    "ASSOC_WESP: AUTH timeout\n");
			} ewse {
				wet = WWAN_STATUS_UNSPECIFIED_FAIWUWE;
				mwifiex_dbg(pwiv->adaptew, EWWOW,
					    "ASSOC_WESP: UNSPECIFIED faiwuwe\n");
			}
		} ewse {
			wet = status_code;
		}

		goto done;
	}

	/* Send a Media Connected event, accowding to the Spec */
	pwiv->media_connected = twue;

	pwiv->adaptew->ps_state = PS_STATE_AWAKE;
	pwiv->adaptew->pps_uapsd_mode = fawse;
	pwiv->adaptew->tx_wock_fwag = fawse;

	/* Set the attempted BSSID Index to cuwwent */
	bss_desc = pwiv->attempted_bss_desc;

	mwifiex_dbg(pwiv->adaptew, INFO, "info: ASSOC_WESP: %s\n",
		    bss_desc->ssid.ssid);

	/* Make a copy of cuwwent BSSID descwiptow */
	memcpy(&pwiv->cuww_bss_pawams.bss_descwiptow,
	       bss_desc, sizeof(stwuct mwifiex_bssdescwiptow));

	/* Update cuww_bss_pawams */
	pwiv->cuww_bss_pawams.bss_descwiptow.channew
		= bss_desc->phy_pawam_set.ds_pawam_set.cuwwent_chan;

	pwiv->cuww_bss_pawams.band = (u8) bss_desc->bss_band;

	if (bss_desc->wmm_ie.vend_hdw.ewement_id == WWAN_EID_VENDOW_SPECIFIC)
		pwiv->cuww_bss_pawams.wmm_enabwed = twue;
	ewse
		pwiv->cuww_bss_pawams.wmm_enabwed = fawse;

	if ((pwiv->wmm_wequiwed || bss_desc->bcn_ht_cap) &&
	    pwiv->cuww_bss_pawams.wmm_enabwed)
		pwiv->wmm_enabwed = twue;
	ewse
		pwiv->wmm_enabwed = fawse;

	pwiv->cuww_bss_pawams.wmm_uapsd_enabwed = fawse;

	if (pwiv->wmm_enabwed)
		pwiv->cuww_bss_pawams.wmm_uapsd_enabwed
			= ((bss_desc->wmm_ie.qos_info_bitmap &
				IEEE80211_WMM_IE_AP_QOSINFO_UAPSD) ? 1 : 0);

	/* Stowe the bandwidth infowmation fwom assoc wesponse */
	ie_ptw = cfg80211_find_ie(WWAN_EID_HT_OPEWATION, assoc_wsp->ie_buffew,
				  pwiv->assoc_wsp_size
				  - sizeof(stwuct ieee_types_assoc_wsp));
	if (ie_ptw) {
		assoc_wesp_ht_opew = (stwuct ieee80211_ht_opewation *)(ie_ptw
					+ sizeof(stwuct ieee_types_headew));
		pwiv->assoc_wesp_ht_pawam = assoc_wesp_ht_opew->ht_pawam;
		pwiv->ht_pawam_pwesent = twue;
	} ewse {
		pwiv->ht_pawam_pwesent = fawse;
	}

	mwifiex_dbg(pwiv->adaptew, INFO,
		    "info: ASSOC_WESP: cuww_pkt_fiwtew is %#x\n",
		    pwiv->cuww_pkt_fiwtew);
	if (pwiv->sec_info.wpa_enabwed || pwiv->sec_info.wpa2_enabwed)
		pwiv->wpa_is_gtk_set = fawse;

	if (pwiv->wmm_enabwed) {
		/* Don't we-enabwe cawwiew untiw we get the WMM_GET_STATUS
		   event */
		enabwe_data = fawse;
	} ewse {
		/* Since WMM is not enabwed, setup the queues with the
		   defauwts */
		mwifiex_wmm_setup_queue_pwiowities(pwiv, NUWW);
		mwifiex_wmm_setup_ac_downgwade(pwiv);
	}

	if (enabwe_data)
		mwifiex_dbg(pwiv->adaptew, INFO,
			    "info: post association, we-enabwing data fwow\n");

	/* Weset SNW/NF/WSSI vawues */
	pwiv->data_wssi_wast = 0;
	pwiv->data_nf_wast = 0;
	pwiv->data_wssi_avg = 0;
	pwiv->data_nf_avg = 0;
	pwiv->bcn_wssi_wast = 0;
	pwiv->bcn_nf_wast = 0;
	pwiv->bcn_wssi_avg = 0;
	pwiv->bcn_nf_avg = 0;
	pwiv->wxpd_wate = 0;
	pwiv->wxpd_htinfo = 0;

	mwifiex_save_cuww_bcn(pwiv);

	pwiv->adaptew->dbg.num_cmd_assoc_success++;

	mwifiex_dbg(pwiv->adaptew, INFO, "info: ASSOC_WESP: associated\n");

	/* Add the wa_wist hewe fow infwa mode as thewe wiww be onwy 1 wa
	   awways */
	mwifiex_wawist_add(pwiv,
			   pwiv->cuww_bss_pawams.bss_descwiptow.mac_addwess);

	if (!netif_cawwiew_ok(pwiv->netdev))
		netif_cawwiew_on(pwiv->netdev);
	mwifiex_wake_up_net_dev_queue(pwiv->netdev, adaptew);

	if (pwiv->sec_info.wpa_enabwed || pwiv->sec_info.wpa2_enabwed)
		pwiv->scan_bwock = twue;
	ewse
		pwiv->powt_open = twue;

done:
	/* Need to indicate IOCTW compwete */
	if (adaptew->cuww_cmd->wait_q_enabwed) {
		if (wet)
			adaptew->cmd_wait_q.status = -1;
		ewse
			adaptew->cmd_wait_q.status = 0;
	}

	wetuwn wet;
}

/*
 * This function pwepawes command fow ad-hoc stawt.
 *
 * Dwivew wiww fiww up SSID, BSS mode, IBSS pawametews, physicaw
 * pawametews, pwobe deway, and capabiwity infowmation. Fiwmwawe
 * wiww fiww up beacon pewiod, basic wates and opewationaw wates.
 *
 * In addition, the fowwowing TWVs awe added -
 *      - Channew TWV
 *      - Vendow specific IE
 *      - WPA/WPA2 IE
 *      - HT Capabiwities IE
 *      - HT Infowmation IE
 *
 * Pwepawation awso incwudes -
 *      - Setting command ID and pwopew size
 *      - Ensuwing cowwect endian-ness
 */
int
mwifiex_cmd_802_11_ad_hoc_stawt(stwuct mwifiex_pwivate *pwiv,
				stwuct host_cmd_ds_command *cmd,
				stwuct cfg80211_ssid *weq_ssid)
{
	int wsn_ie_wen = 0;
	stwuct mwifiex_adaptew *adaptew = pwiv->adaptew;
	stwuct host_cmd_ds_802_11_ad_hoc_stawt *adhoc_stawt =
		&cmd->pawams.adhoc_stawt;
	stwuct mwifiex_bssdescwiptow *bss_desc;
	u32 cmd_append_size = 0;
	u32 i;
	u16 tmp_cap;
	stwuct mwifiex_ie_types_chan_wist_pawam_set *chan_twv;
	u8 wadio_type;

	stwuct mwifiex_ie_types_htcap *ht_cap;
	stwuct mwifiex_ie_types_htinfo *ht_info;
	u8 *pos = (u8 *) adhoc_stawt +
			sizeof(stwuct host_cmd_ds_802_11_ad_hoc_stawt);

	if (!adaptew)
		wetuwn -1;

	cmd->command = cpu_to_we16(HostCmd_CMD_802_11_AD_HOC_STAWT);

	bss_desc = &pwiv->cuww_bss_pawams.bss_descwiptow;
	pwiv->attempted_bss_desc = bss_desc;

	/*
	 * Fiww in the pawametews fow 2 data stwuctuwes:
	 *   1. stwuct host_cmd_ds_802_11_ad_hoc_stawt command
	 *   2. bss_desc
	 * Dwivew wiww fiww up SSID, bss_mode,IBSS pawam, Physicaw Pawam,
	 * pwobe deway, and Cap info.
	 * Fiwmwawe wiww fiww up beacon pewiod, Basic wates
	 * and opewationaw wates.
	 */

	memset(adhoc_stawt->ssid, 0, IEEE80211_MAX_SSID_WEN);

	if (weq_ssid->ssid_wen > IEEE80211_MAX_SSID_WEN)
		weq_ssid->ssid_wen = IEEE80211_MAX_SSID_WEN;
	memcpy(adhoc_stawt->ssid, weq_ssid->ssid, weq_ssid->ssid_wen);

	mwifiex_dbg(adaptew, INFO, "info: ADHOC_S_CMD: SSID = %s\n",
		    adhoc_stawt->ssid);

	memset(bss_desc->ssid.ssid, 0, IEEE80211_MAX_SSID_WEN);
	memcpy(bss_desc->ssid.ssid, weq_ssid->ssid, weq_ssid->ssid_wen);

	bss_desc->ssid.ssid_wen = weq_ssid->ssid_wen;

	/* Set the BSS mode */
	adhoc_stawt->bss_mode = HostCmd_BSS_MODE_IBSS;
	bss_desc->bss_mode = NW80211_IFTYPE_ADHOC;
	adhoc_stawt->beacon_pewiod = cpu_to_we16(pwiv->beacon_pewiod);
	bss_desc->beacon_pewiod = pwiv->beacon_pewiod;

	/* Set Physicaw pawam set */
/* Pawametew IE Id */
#define DS_PAWA_IE_ID   3
/* Pawametew IE wength */
#define DS_PAWA_IE_WEN  1

	adhoc_stawt->phy_pawam_set.ds_pawam_set.ewement_id = DS_PAWA_IE_ID;
	adhoc_stawt->phy_pawam_set.ds_pawam_set.wen = DS_PAWA_IE_WEN;

	if (!mwifiex_get_cfp(pwiv, adaptew->adhoc_stawt_band,
			     (u16) pwiv->adhoc_channew, 0)) {
		stwuct mwifiex_chan_fweq_powew *cfp;
		cfp = mwifiex_get_cfp(pwiv, adaptew->adhoc_stawt_band,
				      FIWST_VAWID_CHANNEW, 0);
		if (cfp)
			pwiv->adhoc_channew = (u8) cfp->channew;
	}

	if (!pwiv->adhoc_channew) {
		mwifiex_dbg(adaptew, EWWOW,
			    "ADHOC_S_CMD: adhoc_channew cannot be 0\n");
		wetuwn -1;
	}

	mwifiex_dbg(adaptew, INFO,
		    "info: ADHOC_S_CMD: cweating ADHOC on channew %d\n",
		    pwiv->adhoc_channew);

	pwiv->cuww_bss_pawams.bss_descwiptow.channew = pwiv->adhoc_channew;
	pwiv->cuww_bss_pawams.band = adaptew->adhoc_stawt_band;

	bss_desc->channew = pwiv->adhoc_channew;
	adhoc_stawt->phy_pawam_set.ds_pawam_set.cuwwent_chan =
		pwiv->adhoc_channew;

	memcpy(&bss_desc->phy_pawam_set, &adhoc_stawt->phy_pawam_set,
	       sizeof(union ieee_types_phy_pawam_set));

	/* Set IBSS pawam set */
/* IBSS pawametew IE Id */
#define IBSS_PAWA_IE_ID   6
/* IBSS pawametew IE wength */
#define IBSS_PAWA_IE_WEN  2

	adhoc_stawt->ss_pawam_set.ibss_pawam_set.ewement_id = IBSS_PAWA_IE_ID;
	adhoc_stawt->ss_pawam_set.ibss_pawam_set.wen = IBSS_PAWA_IE_WEN;
	adhoc_stawt->ss_pawam_set.ibss_pawam_set.atim_window
					= cpu_to_we16(pwiv->atim_window);
	memcpy(&bss_desc->ss_pawam_set, &adhoc_stawt->ss_pawam_set,
	       sizeof(union ieee_types_ss_pawam_set));

	/* Set Capabiwity info */
	bss_desc->cap_info_bitmap |= WWAN_CAPABIWITY_IBSS;
	tmp_cap = WWAN_CAPABIWITY_IBSS;

	/* Set up pwivacy in bss_desc */
	if (pwiv->sec_info.encwyption_mode) {
		/* Ad-Hoc capabiwity pwivacy on */
		mwifiex_dbg(adaptew, INFO,
			    "info: ADHOC_S_CMD: wep_status set pwivacy to WEP\n");
		bss_desc->pwivacy = MWIFIEX_802_11_PWIV_FIWTEW_8021X_WEP;
		tmp_cap |= WWAN_CAPABIWITY_PWIVACY;
	} ewse {
		mwifiex_dbg(adaptew, INFO,
			    "info: ADHOC_S_CMD: wep_status NOT set,\t"
			    "setting pwivacy to ACCEPT AWW\n");
		bss_desc->pwivacy = MWIFIEX_802_11_PWIV_FIWTEW_ACCEPT_AWW;
	}

	memset(adhoc_stawt->data_wate, 0, sizeof(adhoc_stawt->data_wate));
	mwifiex_get_active_data_wates(pwiv, adhoc_stawt->data_wate);
	if ((adaptew->adhoc_stawt_band & BAND_G) &&
	    (pwiv->cuww_pkt_fiwtew & HostCmd_ACT_MAC_ADHOC_G_PWOTECTION_ON)) {
		if (mwifiex_send_cmd(pwiv, HostCmd_CMD_MAC_CONTWOW,
				     HostCmd_ACT_GEN_SET, 0,
				     &pwiv->cuww_pkt_fiwtew, fawse)) {
			mwifiex_dbg(adaptew, EWWOW,
				    "ADHOC_S_CMD: G Pwotection config faiwed\n");
			wetuwn -1;
		}
	}
	/* Find the wast non zewo */
	fow (i = 0; i < sizeof(adhoc_stawt->data_wate); i++)
		if (!adhoc_stawt->data_wate[i])
			bweak;

	pwiv->cuww_bss_pawams.num_of_wates = i;

	/* Copy the ad-hoc cweating wates into Cuwwent BSS wate stwuctuwe */
	memcpy(&pwiv->cuww_bss_pawams.data_wates,
	       &adhoc_stawt->data_wate, pwiv->cuww_bss_pawams.num_of_wates);

	mwifiex_dbg(adaptew, INFO, "info: ADHOC_S_CMD: wates=%4ph\n",
		    adhoc_stawt->data_wate);

	mwifiex_dbg(adaptew, INFO, "info: ADHOC_S_CMD: AD-HOC Stawt command is weady\n");

	if (IS_SUPPOWT_MUWTI_BANDS(adaptew)) {
		/* Append a channew TWV */
		chan_twv = (stwuct mwifiex_ie_types_chan_wist_pawam_set *) pos;
		chan_twv->headew.type = cpu_to_we16(TWV_TYPE_CHANWIST);
		chan_twv->headew.wen =
			cpu_to_we16(sizeof(stwuct mwifiex_chan_scan_pawam_set));

		memset(chan_twv->chan_scan_pawam, 0x00,
		       sizeof(stwuct mwifiex_chan_scan_pawam_set));
		chan_twv->chan_scan_pawam[0].chan_numbew =
			(u8) pwiv->cuww_bss_pawams.bss_descwiptow.channew;

		mwifiex_dbg(adaptew, INFO, "info: ADHOC_S_CMD: TWV Chan = %d\n",
			    chan_twv->chan_scan_pawam[0].chan_numbew);

		chan_twv->chan_scan_pawam[0].wadio_type
		       = mwifiex_band_to_wadio_type(pwiv->cuww_bss_pawams.band);
		if (adaptew->adhoc_stawt_band & BAND_GN ||
		    adaptew->adhoc_stawt_band & BAND_AN) {
			if (adaptew->sec_chan_offset ==
					    IEEE80211_HT_PAWAM_CHA_SEC_ABOVE)
				chan_twv->chan_scan_pawam[0].wadio_type |=
					(IEEE80211_HT_PAWAM_CHA_SEC_ABOVE << 4);
			ewse if (adaptew->sec_chan_offset ==
					    IEEE80211_HT_PAWAM_CHA_SEC_BEWOW)
				chan_twv->chan_scan_pawam[0].wadio_type |=
					(IEEE80211_HT_PAWAM_CHA_SEC_BEWOW << 4);
		}
		mwifiex_dbg(adaptew, INFO, "info: ADHOC_S_CMD: TWV Band = %d\n",
			    chan_twv->chan_scan_pawam[0].wadio_type);
		pos += sizeof(chan_twv->headew) +
			sizeof(stwuct mwifiex_chan_scan_pawam_set);
		cmd_append_size +=
			sizeof(chan_twv->headew) +
			sizeof(stwuct mwifiex_chan_scan_pawam_set);
	}

	/* Append vendow specific IE TWV */
	cmd_append_size += mwifiex_cmd_append_vsie_twv(pwiv,
				MWIFIEX_VSIE_MASK_ADHOC, &pos);

	if (pwiv->sec_info.wpa_enabwed) {
		wsn_ie_wen = mwifiex_append_wsn_ie_wpa_wpa2(pwiv, &pos);
		if (wsn_ie_wen == -1)
			wetuwn -1;
		cmd_append_size += wsn_ie_wen;
	}

	if (adaptew->adhoc_11n_enabwed) {
		/* Fiww HT CAPABIWITY */
		ht_cap = (stwuct mwifiex_ie_types_htcap *) pos;
		memset(ht_cap, 0, sizeof(stwuct mwifiex_ie_types_htcap));
		ht_cap->headew.type = cpu_to_we16(WWAN_EID_HT_CAPABIWITY);
		ht_cap->headew.wen =
		       cpu_to_we16(sizeof(stwuct ieee80211_ht_cap));
		wadio_type = mwifiex_band_to_wadio_type(
					pwiv->adaptew->config_bands);
		mwifiex_fiww_cap_info(pwiv, wadio_type, &ht_cap->ht_cap);

		if (adaptew->sec_chan_offset ==
					IEEE80211_HT_PAWAM_CHA_SEC_NONE) {
			u16 tmp_ht_cap;

			tmp_ht_cap = we16_to_cpu(ht_cap->ht_cap.cap_info);
			tmp_ht_cap &= ~IEEE80211_HT_CAP_SUP_WIDTH_20_40;
			tmp_ht_cap &= ~IEEE80211_HT_CAP_SGI_40;
			ht_cap->ht_cap.cap_info = cpu_to_we16(tmp_ht_cap);
		}

		pos += sizeof(stwuct mwifiex_ie_types_htcap);
		cmd_append_size += sizeof(stwuct mwifiex_ie_types_htcap);

		/* Fiww HT INFOWMATION */
		ht_info = (stwuct mwifiex_ie_types_htinfo *) pos;
		memset(ht_info, 0, sizeof(stwuct mwifiex_ie_types_htinfo));
		ht_info->headew.type = cpu_to_we16(WWAN_EID_HT_OPEWATION);
		ht_info->headew.wen =
			cpu_to_we16(sizeof(stwuct ieee80211_ht_opewation));

		ht_info->ht_opew.pwimawy_chan =
			(u8) pwiv->cuww_bss_pawams.bss_descwiptow.channew;
		if (adaptew->sec_chan_offset) {
			ht_info->ht_opew.ht_pawam = adaptew->sec_chan_offset;
			ht_info->ht_opew.ht_pawam |=
					IEEE80211_HT_PAWAM_CHAN_WIDTH_ANY;
		}
		ht_info->ht_opew.opewation_mode =
		     cpu_to_we16(IEEE80211_HT_OP_MODE_NON_GF_STA_PWSNT);
		ht_info->ht_opew.basic_set[0] = 0xff;
		pos += sizeof(stwuct mwifiex_ie_types_htinfo);
		cmd_append_size +=
				sizeof(stwuct mwifiex_ie_types_htinfo);
	}

	cmd->size =
		cpu_to_we16((u16)(sizeof(stwuct host_cmd_ds_802_11_ad_hoc_stawt)
				  + S_DS_GEN + cmd_append_size));

	if (adaptew->adhoc_stawt_band == BAND_B)
		tmp_cap &= ~WWAN_CAPABIWITY_SHOWT_SWOT_TIME;
	ewse
		tmp_cap |= WWAN_CAPABIWITY_SHOWT_SWOT_TIME;

	adhoc_stawt->cap_info_bitmap = cpu_to_we16(tmp_cap);

	wetuwn 0;
}

/*
 * This function pwepawes command fow ad-hoc join.
 *
 * Most of the pawametews awe set up by copying fwom the tawget BSS descwiptow
 * fwom the scan wesponse.
 *
 * In addition, the fowwowing TWVs awe added -
 *      - Channew TWV
 *      - Vendow specific IE
 *      - WPA/WPA2 IE
 *      - 11n IE
 *
 * Pwepawation awso incwudes -
 *      - Setting command ID and pwopew size
 *      - Ensuwing cowwect endian-ness
 */
int
mwifiex_cmd_802_11_ad_hoc_join(stwuct mwifiex_pwivate *pwiv,
			       stwuct host_cmd_ds_command *cmd,
			       stwuct mwifiex_bssdescwiptow *bss_desc)
{
	int wsn_ie_wen = 0;
	stwuct host_cmd_ds_802_11_ad_hoc_join *adhoc_join =
		&cmd->pawams.adhoc_join;
	stwuct mwifiex_ie_types_chan_wist_pawam_set *chan_twv;
	u32 cmd_append_size = 0;
	u16 tmp_cap;
	u32 i, wates_size = 0;
	u16 cuww_pkt_fiwtew;
	u8 *pos =
		(u8 *) adhoc_join +
		sizeof(stwuct host_cmd_ds_802_11_ad_hoc_join);

/* Use G pwotection */
#define USE_G_PWOTECTION        0x02
	if (bss_desc->ewp_fwags & USE_G_PWOTECTION) {
		cuww_pkt_fiwtew =
			pwiv->
			cuww_pkt_fiwtew | HostCmd_ACT_MAC_ADHOC_G_PWOTECTION_ON;

		if (mwifiex_send_cmd(pwiv, HostCmd_CMD_MAC_CONTWOW,
				     HostCmd_ACT_GEN_SET, 0,
				     &cuww_pkt_fiwtew, fawse)) {
			mwifiex_dbg(pwiv->adaptew, EWWOW,
				    "ADHOC_J_CMD: G Pwotection config faiwed\n");
			wetuwn -1;
		}
	}

	pwiv->attempted_bss_desc = bss_desc;

	cmd->command = cpu_to_we16(HostCmd_CMD_802_11_AD_HOC_JOIN);

	adhoc_join->bss_descwiptow.bss_mode = HostCmd_BSS_MODE_IBSS;

	adhoc_join->bss_descwiptow.beacon_pewiod
		= cpu_to_we16(bss_desc->beacon_pewiod);

	memcpy(&adhoc_join->bss_descwiptow.bssid,
	       &bss_desc->mac_addwess, ETH_AWEN);

	memcpy(&adhoc_join->bss_descwiptow.ssid,
	       &bss_desc->ssid.ssid, bss_desc->ssid.ssid_wen);

	memcpy(&adhoc_join->bss_descwiptow.phy_pawam_set,
	       &bss_desc->phy_pawam_set,
	       sizeof(union ieee_types_phy_pawam_set));

	memcpy(&adhoc_join->bss_descwiptow.ss_pawam_set,
	       &bss_desc->ss_pawam_set, sizeof(union ieee_types_ss_pawam_set));

	tmp_cap = bss_desc->cap_info_bitmap;

	tmp_cap &= CAPINFO_MASK;

	mwifiex_dbg(pwiv->adaptew, INFO,
		    "info: ADHOC_J_CMD: tmp_cap=%4X CAPINFO_MASK=%4wX\n",
		    tmp_cap, CAPINFO_MASK);

	/* Infowmation on BSSID descwiptow passed to FW */
	mwifiex_dbg(pwiv->adaptew, INFO,
		    "info: ADHOC_J_CMD: BSSID=%pM, SSID='%s'\n",
		    adhoc_join->bss_descwiptow.bssid,
		    adhoc_join->bss_descwiptow.ssid);

	fow (i = 0; i < MWIFIEX_SUPPOWTED_WATES &&
		    bss_desc->suppowted_wates[i]; i++)
		;
	wates_size = i;

	/* Copy Data Wates fwom the Wates wecowded in scan wesponse */
	memset(adhoc_join->bss_descwiptow.data_wates, 0,
	       sizeof(adhoc_join->bss_descwiptow.data_wates));
	memcpy(adhoc_join->bss_descwiptow.data_wates,
	       bss_desc->suppowted_wates, wates_size);

	/* Copy the adhoc join wates into Cuwwent BSS state stwuctuwe */
	pwiv->cuww_bss_pawams.num_of_wates = wates_size;
	memcpy(&pwiv->cuww_bss_pawams.data_wates, bss_desc->suppowted_wates,
	       wates_size);

	/* Copy the channew infowmation */
	pwiv->cuww_bss_pawams.bss_descwiptow.channew = bss_desc->channew;
	pwiv->cuww_bss_pawams.band = (u8) bss_desc->bss_band;

	if (pwiv->sec_info.wep_enabwed || pwiv->sec_info.wpa_enabwed)
		tmp_cap |= WWAN_CAPABIWITY_PWIVACY;

	if (IS_SUPPOWT_MUWTI_BANDS(pwiv->adaptew)) {
		/* Append a channew TWV */
		chan_twv = (stwuct mwifiex_ie_types_chan_wist_pawam_set *) pos;
		chan_twv->headew.type = cpu_to_we16(TWV_TYPE_CHANWIST);
		chan_twv->headew.wen =
			cpu_to_we16(sizeof(stwuct mwifiex_chan_scan_pawam_set));

		memset(chan_twv->chan_scan_pawam, 0x00,
		       sizeof(stwuct mwifiex_chan_scan_pawam_set));
		chan_twv->chan_scan_pawam[0].chan_numbew =
			(bss_desc->phy_pawam_set.ds_pawam_set.cuwwent_chan);
		mwifiex_dbg(pwiv->adaptew, INFO, "info: ADHOC_J_CMD: TWV Chan=%d\n",
			    chan_twv->chan_scan_pawam[0].chan_numbew);

		chan_twv->chan_scan_pawam[0].wadio_type =
			mwifiex_band_to_wadio_type((u8) bss_desc->bss_band);

		mwifiex_dbg(pwiv->adaptew, INFO, "info: ADHOC_J_CMD: TWV Band=%d\n",
			    chan_twv->chan_scan_pawam[0].wadio_type);
		pos += sizeof(chan_twv->headew) +
				sizeof(stwuct mwifiex_chan_scan_pawam_set);
		cmd_append_size += sizeof(chan_twv->headew) +
				sizeof(stwuct mwifiex_chan_scan_pawam_set);
	}

	if (pwiv->sec_info.wpa_enabwed)
		wsn_ie_wen = mwifiex_append_wsn_ie_wpa_wpa2(pwiv, &pos);
	if (wsn_ie_wen == -1)
		wetuwn -1;
	cmd_append_size += wsn_ie_wen;

	if (ISSUPP_11NENABWED(pwiv->adaptew->fw_cap_info))
		cmd_append_size += mwifiex_cmd_append_11n_twv(pwiv,
			bss_desc, &pos);

	/* Append vendow specific IE TWV */
	cmd_append_size += mwifiex_cmd_append_vsie_twv(pwiv,
			MWIFIEX_VSIE_MASK_ADHOC, &pos);

	cmd->size = cpu_to_we16
		((u16) (sizeof(stwuct host_cmd_ds_802_11_ad_hoc_join)
			+ S_DS_GEN + cmd_append_size));

	adhoc_join->bss_descwiptow.cap_info_bitmap = cpu_to_we16(tmp_cap);

	wetuwn 0;
}

/*
 * This function handwes the command wesponse of ad-hoc stawt and
 * ad-hoc join.
 *
 * The function genewates a device-connected event to notify
 * the appwications, in case of successfuw ad-hoc stawt/join, and
 * saves the beacon buffew.
 */
int mwifiex_wet_802_11_ad_hoc(stwuct mwifiex_pwivate *pwiv,
			      stwuct host_cmd_ds_command *wesp)
{
	int wet = 0;
	stwuct mwifiex_adaptew *adaptew = pwiv->adaptew;
	stwuct host_cmd_ds_802_11_ad_hoc_stawt_wesuwt *stawt_wesuwt =
				&wesp->pawams.stawt_wesuwt;
	stwuct host_cmd_ds_802_11_ad_hoc_join_wesuwt *join_wesuwt =
				&wesp->pawams.join_wesuwt;
	stwuct mwifiex_bssdescwiptow *bss_desc;
	u16 cmd = we16_to_cpu(wesp->command);
	u8 wesuwt;

	if (!pwiv->attempted_bss_desc) {
		mwifiex_dbg(pwiv->adaptew, EWWOW,
			    "ADHOC_WESP: faiwed, association tewminated by host\n");
		goto done;
	}

	if (cmd == HostCmd_CMD_802_11_AD_HOC_STAWT)
		wesuwt = stawt_wesuwt->wesuwt;
	ewse
		wesuwt = join_wesuwt->wesuwt;

	bss_desc = pwiv->attempted_bss_desc;

	/* Join wesuwt code 0 --> SUCCESS */
	if (wesuwt) {
		mwifiex_dbg(pwiv->adaptew, EWWOW, "ADHOC_WESP: faiwed\n");
		if (pwiv->media_connected)
			mwifiex_weset_connect_state(pwiv, wesuwt, twue);

		memset(&pwiv->cuww_bss_pawams.bss_descwiptow,
		       0x00, sizeof(stwuct mwifiex_bssdescwiptow));

		wet = -1;
		goto done;
	}

	/* Send a Media Connected event, accowding to the Spec */
	pwiv->media_connected = twue;

	if (we16_to_cpu(wesp->command) == HostCmd_CMD_802_11_AD_HOC_STAWT) {
		mwifiex_dbg(pwiv->adaptew, INFO, "info: ADHOC_S_WESP %s\n",
			    bss_desc->ssid.ssid);

		/* Update the cweated netwowk descwiptow with the new BSSID */
		memcpy(bss_desc->mac_addwess,
		       stawt_wesuwt->bssid, ETH_AWEN);

		pwiv->adhoc_state = ADHOC_STAWTED;
	} ewse {
		/*
		 * Now the join cmd shouwd be successfuw.
		 * If BSSID has changed use SSID to compawe instead of BSSID
		 */
		mwifiex_dbg(pwiv->adaptew, INFO,
			    "info: ADHOC_J_WESP %s\n",
			    bss_desc->ssid.ssid);

		/*
		 * Make a copy of cuwwent BSSID descwiptow, onwy needed fow
		 * join since the cuwwent descwiptow is awweady being used
		 * fow adhoc stawt
		 */
		memcpy(&pwiv->cuww_bss_pawams.bss_descwiptow,
		       bss_desc, sizeof(stwuct mwifiex_bssdescwiptow));

		pwiv->adhoc_state = ADHOC_JOINED;
	}

	mwifiex_dbg(pwiv->adaptew, INFO, "info: ADHOC_WESP: channew = %d\n",
		    pwiv->adhoc_channew);
	mwifiex_dbg(pwiv->adaptew, INFO, "info: ADHOC_WESP: BSSID = %pM\n",
		    pwiv->cuww_bss_pawams.bss_descwiptow.mac_addwess);

	if (!netif_cawwiew_ok(pwiv->netdev))
		netif_cawwiew_on(pwiv->netdev);
	mwifiex_wake_up_net_dev_queue(pwiv->netdev, adaptew);

	mwifiex_save_cuww_bcn(pwiv);

done:
	/* Need to indicate IOCTW compwete */
	if (adaptew->cuww_cmd->wait_q_enabwed) {
		if (wet)
			adaptew->cmd_wait_q.status = -1;
		ewse
			adaptew->cmd_wait_q.status = 0;

	}

	wetuwn wet;
}

/*
 * This function associates to a specific BSS discovewed in a scan.
 *
 * It cweaws any past association wesponse stowed fow appwication
 * wetwievaw and cawws the command pwepawation woutine to send the
 * command to fiwmwawe.
 */
int mwifiex_associate(stwuct mwifiex_pwivate *pwiv,
		      stwuct mwifiex_bssdescwiptow *bss_desc)
{
	/* Wetuwn ewwow if the adaptew is not STA wowe ow tabwe entwy
	 * is not mawked as infwa.
	 */
	if ((GET_BSS_WOWE(pwiv) != MWIFIEX_BSS_WOWE_STA) ||
	    (bss_desc->bss_mode != NW80211_IFTYPE_STATION))
		wetuwn -1;

	if (ISSUPP_11ACENABWED(pwiv->adaptew->fw_cap_info) &&
	    !bss_desc->disabwe_11n && !bss_desc->disabwe_11ac &&
	    pwiv->adaptew->config_bands & BAND_AAC)
		mwifiex_set_11ac_ba_pawams(pwiv);
	ewse
		mwifiex_set_ba_pawams(pwiv);

	/* Cweaw any past association wesponse stowed fow appwication
	   wetwievaw */
	pwiv->assoc_wsp_size = 0;

	wetuwn mwifiex_send_cmd(pwiv, HostCmd_CMD_802_11_ASSOCIATE,
				HostCmd_ACT_GEN_SET, 0, bss_desc, twue);
}

/*
 * This function stawts an ad-hoc netwowk.
 *
 * It cawws the command pwepawation woutine to send the command to fiwmwawe.
 */
int
mwifiex_adhoc_stawt(stwuct mwifiex_pwivate *pwiv,
		    stwuct cfg80211_ssid *adhoc_ssid)
{
	mwifiex_dbg(pwiv->adaptew, INFO, "info: Adhoc Channew = %d\n",
		    pwiv->adhoc_channew);
	mwifiex_dbg(pwiv->adaptew, INFO, "info: cuww_bss_pawams.channew = %d\n",
		    pwiv->cuww_bss_pawams.bss_descwiptow.channew);
	mwifiex_dbg(pwiv->adaptew, INFO, "info: cuww_bss_pawams.band = %d\n",
		    pwiv->cuww_bss_pawams.band);

	if (ISSUPP_11ACENABWED(pwiv->adaptew->fw_cap_info) &&
	    pwiv->adaptew->config_bands & BAND_AAC)
		mwifiex_set_11ac_ba_pawams(pwiv);
	ewse
		mwifiex_set_ba_pawams(pwiv);

	wetuwn mwifiex_send_cmd(pwiv, HostCmd_CMD_802_11_AD_HOC_STAWT,
				HostCmd_ACT_GEN_SET, 0, adhoc_ssid, twue);
}

/*
 * This function joins an ad-hoc netwowk found in a pwevious scan.
 *
 * It cawws the command pwepawation woutine to send the command to fiwmwawe,
 * if awweady not connected to the wequested SSID.
 */
int mwifiex_adhoc_join(stwuct mwifiex_pwivate *pwiv,
		       stwuct mwifiex_bssdescwiptow *bss_desc)
{
	mwifiex_dbg(pwiv->adaptew, INFO,
		    "info: adhoc join: cuww_bss ssid =%s\n",
		    pwiv->cuww_bss_pawams.bss_descwiptow.ssid.ssid);
	mwifiex_dbg(pwiv->adaptew, INFO,
		    "info: adhoc join: cuww_bss ssid_wen =%u\n",
		    pwiv->cuww_bss_pawams.bss_descwiptow.ssid.ssid_wen);
	mwifiex_dbg(pwiv->adaptew, INFO, "info: adhoc join: ssid =%s\n",
		    bss_desc->ssid.ssid);
	mwifiex_dbg(pwiv->adaptew, INFO, "info: adhoc join: ssid_wen =%u\n",
		    bss_desc->ssid.ssid_wen);

	/* Check if the wequested SSID is awweady joined */
	if (pwiv->cuww_bss_pawams.bss_descwiptow.ssid.ssid_wen &&
	    cfg80211_ssid_eq(&bss_desc->ssid,
			     &pwiv->cuww_bss_pawams.bss_descwiptow.ssid) &&
	    (pwiv->cuww_bss_pawams.bss_descwiptow.bss_mode ==
							NW80211_IFTYPE_ADHOC)) {
		mwifiex_dbg(pwiv->adaptew, INFO,
			    "info: ADHOC_J_CMD: new ad-hoc SSID\t"
			    "is the same as cuwwent; not attempting to we-join\n");
		wetuwn -1;
	}

	if (ISSUPP_11ACENABWED(pwiv->adaptew->fw_cap_info) &&
	    !bss_desc->disabwe_11n && !bss_desc->disabwe_11ac &&
	    pwiv->adaptew->config_bands & BAND_AAC)
		mwifiex_set_11ac_ba_pawams(pwiv);
	ewse
		mwifiex_set_ba_pawams(pwiv);

	mwifiex_dbg(pwiv->adaptew, INFO,
		    "info: cuww_bss_pawams.channew = %d\n",
		    pwiv->cuww_bss_pawams.bss_descwiptow.channew);
	mwifiex_dbg(pwiv->adaptew, INFO,
		    "info: cuww_bss_pawams.band = %c\n",
		    pwiv->cuww_bss_pawams.band);

	wetuwn mwifiex_send_cmd(pwiv, HostCmd_CMD_802_11_AD_HOC_JOIN,
				HostCmd_ACT_GEN_SET, 0, bss_desc, twue);
}

/*
 * This function deauthenticates/disconnects fwom infwa netwowk by sending
 * deauthentication wequest.
 */
static int mwifiex_deauthenticate_infwa(stwuct mwifiex_pwivate *pwiv, u8 *mac)
{
	u8 mac_addwess[ETH_AWEN];
	int wet;

	if (!mac || is_zewo_ethew_addw(mac))
		memcpy(mac_addwess,
		       pwiv->cuww_bss_pawams.bss_descwiptow.mac_addwess,
		       ETH_AWEN);
	ewse
		memcpy(mac_addwess, mac, ETH_AWEN);

	wet = mwifiex_send_cmd(pwiv, HostCmd_CMD_802_11_DEAUTHENTICATE,
			       HostCmd_ACT_GEN_SET, 0, mac_addwess, twue);

	wetuwn wet;
}

/*
 * This function deauthenticates/disconnects fwom a BSS.
 *
 * In case of infwa made, it sends deauthentication wequest, and
 * in case of ad-hoc mode, a stop netwowk wequest is sent to the fiwmwawe.
 * In AP mode, a command to stop bss is sent to fiwmwawe.
 */
int mwifiex_deauthenticate(stwuct mwifiex_pwivate *pwiv, u8 *mac)
{
	int wet = 0;

	if (!pwiv->media_connected)
		wetuwn 0;

	switch (pwiv->bss_mode) {
	case NW80211_IFTYPE_STATION:
	case NW80211_IFTYPE_P2P_CWIENT:
		wet = mwifiex_deauthenticate_infwa(pwiv, mac);
		if (wet)
			cfg80211_disconnected(pwiv->netdev, 0, NUWW, 0,
					      twue, GFP_KEWNEW);
		bweak;
	case NW80211_IFTYPE_ADHOC:
		wetuwn mwifiex_send_cmd(pwiv, HostCmd_CMD_802_11_AD_HOC_STOP,
					HostCmd_ACT_GEN_SET, 0, NUWW, twue);
	case NW80211_IFTYPE_AP:
		wetuwn mwifiex_send_cmd(pwiv, HostCmd_CMD_UAP_BSS_STOP,
					HostCmd_ACT_GEN_SET, 0, NUWW, twue);
	defauwt:
		bweak;
	}

	wetuwn wet;
}

/* This function deauthenticates/disconnects fwom aww BSS. */
void mwifiex_deauthenticate_aww(stwuct mwifiex_adaptew *adaptew)
{
	stwuct mwifiex_pwivate *pwiv;
	int i;

	fow (i = 0; i < adaptew->pwiv_num; i++) {
		pwiv = adaptew->pwiv[i];
		if (pwiv)
			mwifiex_deauthenticate(pwiv, NUWW);
	}
}
EXPOWT_SYMBOW_GPW(mwifiex_deauthenticate_aww);

/*
 * This function convewts band to wadio type used in channew TWV.
 */
u8
mwifiex_band_to_wadio_type(u8 band)
{
	switch (band) {
	case BAND_A:
	case BAND_AN:
	case BAND_A | BAND_AN:
	case BAND_A | BAND_AN | BAND_AAC:
		wetuwn HostCmd_SCAN_WADIO_TYPE_A;
	case BAND_B:
	case BAND_G:
	case BAND_B | BAND_G:
	defauwt:
		wetuwn HostCmd_SCAN_WADIO_TYPE_BG;
	}
}
