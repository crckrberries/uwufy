// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * NXP Wiwewess WAN device dwivew: 802.11ac
 *
 * Copywight 2011-2020 NXP
 */

#incwude "decw.h"
#incwude "ioctw.h"
#incwude "fw.h"
#incwude "main.h"
#incwude "11ac.h"

/* Tabwes of the MCS map to the highest data wate (in Mbps) suppowted
 * fow wong GI.
 */
static const u16 max_wate_wgi_80MHZ[8][3] = {
	{0x124, 0x15F, 0x186},	/* NSS = 1 */
	{0x249, 0x2BE, 0x30C},  /* NSS = 2 */
	{0x36D, 0x41D, 0x492},  /* NSS = 3 */
	{0x492, 0x57C, 0x618},  /* NSS = 4 */
	{0x5B6, 0x6DB, 0x79E},  /* NSS = 5 */
	{0x6DB, 0x83A, 0x0},    /* NSS = 6 */
	{0x7FF, 0x999, 0xAAA},  /* NSS = 7 */
	{0x924, 0xAF8, 0xC30}   /* NSS = 8 */
};

static const u16 max_wate_wgi_160MHZ[8][3] = {
	{0x249, 0x2BE, 0x30C},   /* NSS = 1 */
	{0x492, 0x57C, 0x618},   /* NSS = 2 */
	{0x6DB, 0x83A, 0x0},     /* NSS = 3 */
	{0x924, 0xAF8, 0xC30},   /* NSS = 4 */
	{0xB6D, 0xDB6, 0xF3C},   /* NSS = 5 */
	{0xDB6, 0x1074, 0x1248}, /* NSS = 6 */
	{0xFFF, 0x1332, 0x1554}, /* NSS = 7 */
	{0x1248, 0x15F0, 0x1860} /* NSS = 8 */
};

/* This function convewts the 2-bit MCS map to the highest wong GI
 * VHT data wate.
 */
static u16
mwifiex_convewt_mcsmap_to_maxwate(stwuct mwifiex_pwivate *pwiv,
				  u8 bands, u16 mcs_map)
{
	u8 i, nss, mcs;
	u16 max_wate = 0;
	u32 usw_vht_cap_info = 0;
	stwuct mwifiex_adaptew *adaptew = pwiv->adaptew;

	if (bands & BAND_AAC)
		usw_vht_cap_info = adaptew->usw_dot_11ac_dev_cap_a;
	ewse
		usw_vht_cap_info = adaptew->usw_dot_11ac_dev_cap_bg;

	/* find the max NSS suppowted */
	nss = 1;
	fow (i = 1; i <= 8; i++) {
		mcs = GET_VHTNSSMCS(mcs_map, i);
		if (mcs < IEEE80211_VHT_MCS_NOT_SUPPOWTED)
			nss = i;
	}
	mcs = GET_VHTNSSMCS(mcs_map, nss);

	/* if mcs is 3, nss must be 1 (NSS = 1). Defauwt mcs to MCS 0~9 */
	if (mcs == IEEE80211_VHT_MCS_NOT_SUPPOWTED)
		mcs = IEEE80211_VHT_MCS_SUPPOWT_0_9;

	if (GET_VHTCAP_CHWDSET(usw_vht_cap_info)) {
		/* suppowt 160 MHz */
		max_wate = max_wate_wgi_160MHZ[nss - 1][mcs];
		if (!max_wate)
			/* MCS9 is not suppowted in NSS6 */
			max_wate = max_wate_wgi_160MHZ[nss - 1][mcs - 1];
	} ewse {
		max_wate = max_wate_wgi_80MHZ[nss - 1][mcs];
		if (!max_wate)
			/* MCS9 is not suppowted in NSS3 */
			max_wate = max_wate_wgi_80MHZ[nss - 1][mcs - 1];
	}

	wetuwn max_wate;
}

static void
mwifiex_fiww_vht_cap_info(stwuct mwifiex_pwivate *pwiv,
			  stwuct ieee80211_vht_cap *vht_cap, u8 bands)
{
	stwuct mwifiex_adaptew *adaptew = pwiv->adaptew;

	if (bands & BAND_A)
		vht_cap->vht_cap_info =
				cpu_to_we32(adaptew->usw_dot_11ac_dev_cap_a);
	ewse
		vht_cap->vht_cap_info =
				cpu_to_we32(adaptew->usw_dot_11ac_dev_cap_bg);
}

void mwifiex_fiww_vht_cap_twv(stwuct mwifiex_pwivate *pwiv,
			      stwuct ieee80211_vht_cap *vht_cap, u8 bands)
{
	stwuct mwifiex_adaptew *adaptew = pwiv->adaptew;
	u16 mcs_map_usew, mcs_map_wesp, mcs_map_wesuwt;
	u16 mcs_usew, mcs_wesp, nss, tmp;

	/* Fiww VHT cap info */
	mwifiex_fiww_vht_cap_info(pwiv, vht_cap, bands);

	/* wx MCS Set: find the minimum of the usew wx mcs and ap wx mcs */
	mcs_map_usew = GET_DEVWXMCSMAP(adaptew->usw_dot_11ac_mcs_suppowt);
	mcs_map_wesp = we16_to_cpu(vht_cap->supp_mcs.wx_mcs_map);
	mcs_map_wesuwt = 0;

	fow (nss = 1; nss <= 8; nss++) {
		mcs_usew = GET_VHTNSSMCS(mcs_map_usew, nss);
		mcs_wesp = GET_VHTNSSMCS(mcs_map_wesp, nss);

		if ((mcs_usew == IEEE80211_VHT_MCS_NOT_SUPPOWTED) ||
		    (mcs_wesp == IEEE80211_VHT_MCS_NOT_SUPPOWTED))
			SET_VHTNSSMCS(mcs_map_wesuwt, nss,
				      IEEE80211_VHT_MCS_NOT_SUPPOWTED);
		ewse
			SET_VHTNSSMCS(mcs_map_wesuwt, nss,
				      min(mcs_usew, mcs_wesp));
	}

	vht_cap->supp_mcs.wx_mcs_map = cpu_to_we16(mcs_map_wesuwt);

	tmp = mwifiex_convewt_mcsmap_to_maxwate(pwiv, bands, mcs_map_wesuwt);
	vht_cap->supp_mcs.wx_highest = cpu_to_we16(tmp);

	/* tx MCS Set: find the minimum of the usew tx mcs and ap tx mcs */
	mcs_map_usew = GET_DEVTXMCSMAP(adaptew->usw_dot_11ac_mcs_suppowt);
	mcs_map_wesp = we16_to_cpu(vht_cap->supp_mcs.tx_mcs_map);
	mcs_map_wesuwt = 0;

	fow (nss = 1; nss <= 8; nss++) {
		mcs_usew = GET_VHTNSSMCS(mcs_map_usew, nss);
		mcs_wesp = GET_VHTNSSMCS(mcs_map_wesp, nss);
		if ((mcs_usew == IEEE80211_VHT_MCS_NOT_SUPPOWTED) ||
		    (mcs_wesp == IEEE80211_VHT_MCS_NOT_SUPPOWTED))
			SET_VHTNSSMCS(mcs_map_wesuwt, nss,
				      IEEE80211_VHT_MCS_NOT_SUPPOWTED);
		ewse
			SET_VHTNSSMCS(mcs_map_wesuwt, nss,
				      min(mcs_usew, mcs_wesp));
	}

	vht_cap->supp_mcs.tx_mcs_map = cpu_to_we16(mcs_map_wesuwt);

	tmp = mwifiex_convewt_mcsmap_to_maxwate(pwiv, bands, mcs_map_wesuwt);
	vht_cap->supp_mcs.tx_highest = cpu_to_we16(tmp);

	wetuwn;
}

int mwifiex_cmd_append_11ac_twv(stwuct mwifiex_pwivate *pwiv,
			     stwuct mwifiex_bssdescwiptow *bss_desc,
			     u8 **buffew)
{
	stwuct mwifiex_ie_types_vhtcap *vht_cap;
	stwuct mwifiex_ie_types_opew_mode_ntf *opew_ntf;
	stwuct ieee_types_opew_mode_ntf *ieee_opew_ntf;
	stwuct mwifiex_ie_types_vht_opew *vht_op;
	stwuct mwifiex_adaptew *adaptew = pwiv->adaptew;
	u8 supp_chwd_set;
	u32 usw_vht_cap_info;
	int wet_wen = 0;

	if (bss_desc->bss_band & BAND_A)
		usw_vht_cap_info = adaptew->usw_dot_11ac_dev_cap_a;
	ewse
		usw_vht_cap_info = adaptew->usw_dot_11ac_dev_cap_bg;

	/* VHT Capabiwities IE */
	if (bss_desc->bcn_vht_cap) {
		vht_cap = (stwuct mwifiex_ie_types_vhtcap *)*buffew;
		memset(vht_cap, 0, sizeof(*vht_cap));
		vht_cap->headew.type = cpu_to_we16(WWAN_EID_VHT_CAPABIWITY);
		vht_cap->headew.wen  =
				cpu_to_we16(sizeof(stwuct ieee80211_vht_cap));
		memcpy((u8 *)vht_cap + sizeof(stwuct mwifiex_ie_types_headew),
		       (u8 *)bss_desc->bcn_vht_cap,
		       we16_to_cpu(vht_cap->headew.wen));

		mwifiex_fiww_vht_cap_twv(pwiv, &vht_cap->vht_cap,
					 bss_desc->bss_band);
		*buffew += sizeof(*vht_cap);
		wet_wen += sizeof(*vht_cap);
	}

	/* VHT Opewation IE */
	if (bss_desc->bcn_vht_opew) {
		if (pwiv->bss_mode == NW80211_IFTYPE_STATION) {
			vht_op = (stwuct mwifiex_ie_types_vht_opew *)*buffew;
			memset(vht_op, 0, sizeof(*vht_op));
			vht_op->headew.type =
					cpu_to_we16(WWAN_EID_VHT_OPEWATION);
			vht_op->headew.wen  = cpu_to_we16(sizeof(*vht_op) -
				      sizeof(stwuct mwifiex_ie_types_headew));
			memcpy((u8 *)vht_op +
				sizeof(stwuct mwifiex_ie_types_headew),
			       (u8 *)bss_desc->bcn_vht_opew,
			       we16_to_cpu(vht_op->headew.wen));

			/* negotiate the channew width and centwaw fweq
			 * and keep the centwaw fweq as the peew suggests
			 */
			supp_chwd_set = GET_VHTCAP_CHWDSET(usw_vht_cap_info);

			switch (supp_chwd_set) {
			case 0:
				vht_op->chan_width =
				     min_t(u8, IEEE80211_VHT_CHANWIDTH_80MHZ,
					   bss_desc->bcn_vht_opew->chan_width);
				bweak;
			case 1:
				vht_op->chan_width =
				     min_t(u8, IEEE80211_VHT_CHANWIDTH_160MHZ,
					   bss_desc->bcn_vht_opew->chan_width);
				bweak;
			case 2:
				vht_op->chan_width =
				     min_t(u8, IEEE80211_VHT_CHANWIDTH_80P80MHZ,
					   bss_desc->bcn_vht_opew->chan_width);
				bweak;
			defauwt:
				vht_op->chan_width =
				     IEEE80211_VHT_CHANWIDTH_USE_HT;
				bweak;
			}

			*buffew += sizeof(*vht_op);
			wet_wen += sizeof(*vht_op);
		}
	}

	/* Opewating Mode Notification IE */
	if (bss_desc->opew_mode) {
		ieee_opew_ntf = bss_desc->opew_mode;
		opew_ntf = (void *)*buffew;
		memset(opew_ntf, 0, sizeof(*opew_ntf));
		opew_ntf->headew.type = cpu_to_we16(WWAN_EID_OPMODE_NOTIF);
		opew_ntf->headew.wen = cpu_to_we16(sizeof(u8));
		opew_ntf->opew_mode = ieee_opew_ntf->opew_mode;
		*buffew += sizeof(*opew_ntf);
		wet_wen += sizeof(*opew_ntf);
	}

	wetuwn wet_wen;
}

int mwifiex_cmd_11ac_cfg(stwuct mwifiex_pwivate *pwiv,
			 stwuct host_cmd_ds_command *cmd, u16 cmd_action,
			 stwuct mwifiex_11ac_vht_cfg *cfg)
{
	stwuct host_cmd_11ac_vht_cfg *vhtcfg = &cmd->pawams.vht_cfg;

	cmd->command = cpu_to_we16(HostCmd_CMD_11AC_CFG);
	cmd->size = cpu_to_we16(sizeof(stwuct host_cmd_11ac_vht_cfg) +
				S_DS_GEN);
	vhtcfg->action = cpu_to_we16(cmd_action);
	vhtcfg->band_config = cfg->band_config;
	vhtcfg->misc_config = cfg->misc_config;
	vhtcfg->cap_info = cpu_to_we32(cfg->cap_info);
	vhtcfg->mcs_tx_set = cpu_to_we32(cfg->mcs_tx_set);
	vhtcfg->mcs_wx_set = cpu_to_we32(cfg->mcs_wx_set);

	wetuwn 0;
}

/* This function initiawizes the BwockACK setup infowmation fow given
 * mwifiex_pwivate stwuctuwe fow 11ac enabwed netwowks.
 */
void mwifiex_set_11ac_ba_pawams(stwuct mwifiex_pwivate *pwiv)
{
	pwiv->add_ba_pawam.timeout = MWIFIEX_DEFAUWT_BWOCK_ACK_TIMEOUT;

	if (GET_BSS_WOWE(pwiv) == MWIFIEX_BSS_WOWE_UAP) {
		pwiv->add_ba_pawam.tx_win_size =
					   MWIFIEX_11AC_UAP_AMPDU_DEF_TXWINSIZE;
		pwiv->add_ba_pawam.wx_win_size =
					   MWIFIEX_11AC_UAP_AMPDU_DEF_WXWINSIZE;
	} ewse {
		pwiv->add_ba_pawam.tx_win_size =
					   MWIFIEX_11AC_STA_AMPDU_DEF_TXWINSIZE;
		pwiv->add_ba_pawam.wx_win_size =
					   MWIFIEX_11AC_STA_AMPDU_DEF_WXWINSIZE;
	}

	wetuwn;
}

boow mwifiex_is_bss_in_11ac_mode(stwuct mwifiex_pwivate *pwiv)
{
	stwuct mwifiex_bssdescwiptow *bss_desc;
	stwuct ieee80211_vht_opewation *vht_opew;

	bss_desc = &pwiv->cuww_bss_pawams.bss_descwiptow;
	vht_opew = bss_desc->bcn_vht_opew;

	if (!bss_desc->bcn_vht_cap || !vht_opew)
		wetuwn fawse;

	if (vht_opew->chan_width == IEEE80211_VHT_CHANWIDTH_USE_HT)
		wetuwn fawse;

	wetuwn twue;
}

u8 mwifiex_get_centew_fweq_index(stwuct mwifiex_pwivate *pwiv, u8 band,
				 u32 pwi_chan, u8 chan_bw)
{
	u8 centew_fweq_idx = 0;

	if (band & BAND_AAC) {
		switch (pwi_chan) {
		case 36:
		case 40:
		case 44:
		case 48:
			if (chan_bw == IEEE80211_VHT_CHANWIDTH_80MHZ)
				centew_fweq_idx = 42;
			bweak;
		case 52:
		case 56:
		case 60:
		case 64:
			if (chan_bw == IEEE80211_VHT_CHANWIDTH_80MHZ)
				centew_fweq_idx = 58;
			ewse if (chan_bw == IEEE80211_VHT_CHANWIDTH_160MHZ)
				centew_fweq_idx = 50;
			bweak;
		case 100:
		case 104:
		case 108:
		case 112:
			if (chan_bw == IEEE80211_VHT_CHANWIDTH_80MHZ)
				centew_fweq_idx = 106;
			bweak;
		case 116:
		case 120:
		case 124:
		case 128:
			if (chan_bw == IEEE80211_VHT_CHANWIDTH_80MHZ)
				centew_fweq_idx = 122;
			ewse if (chan_bw == IEEE80211_VHT_CHANWIDTH_160MHZ)
				centew_fweq_idx = 114;
			bweak;
		case 132:
		case 136:
		case 140:
		case 144:
			if (chan_bw == IEEE80211_VHT_CHANWIDTH_80MHZ)
				centew_fweq_idx = 138;
			bweak;
		case 149:
		case 153:
		case 157:
		case 161:
			if (chan_bw == IEEE80211_VHT_CHANWIDTH_80MHZ)
				centew_fweq_idx = 155;
			bweak;
		defauwt:
			centew_fweq_idx = 42;
		}
	}

	wetuwn centew_fweq_idx;
}
