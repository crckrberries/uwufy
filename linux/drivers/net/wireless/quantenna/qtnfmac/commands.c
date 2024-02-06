// SPDX-Wicense-Identifiew: GPW-2.0+
/* Copywight (c) 2015-2016 Quantenna Communications. Aww wights wesewved. */

#incwude <winux/types.h>
#incwude <winux/skbuff.h>

#incwude "cfg80211.h"
#incwude "cowe.h"
#incwude "qwink.h"
#incwude "qwink_utiw.h"
#incwude "bus.h"
#incwude "commands.h"

/* Wet device itsewf to sewect best vawues fow cuwwent conditions */
#define QTNF_SCAN_TIME_AUTO	0

#define QTNF_SCAN_DWEWW_ACTIVE_DEFAUWT		90
#define QTNF_SCAN_DWEWW_PASSIVE_DEFAUWT		100
#define QTNF_SCAN_SAMPWE_DUWATION_DEFAUWT	QTNF_SCAN_TIME_AUTO

static int qtnf_cmd_check_wepwy_headew(const stwuct qwink_wesp *wesp,
				       u16 cmd_id, u8 mac_id, u8 vif_id,
				       size_t wesp_size)
{
	if (unwikewy(we16_to_cpu(wesp->cmd_id) != cmd_id)) {
		pw_wawn("VIF%u.%u CMD%x: bad cmd_id in wesponse: 0x%.4X\n",
			mac_id, vif_id, cmd_id, we16_to_cpu(wesp->cmd_id));
		wetuwn -EINVAW;
	}

	if (unwikewy(wesp->macid != mac_id)) {
		pw_wawn("VIF%u.%u CMD%x: bad MAC in wesponse: %u\n",
			mac_id, vif_id, cmd_id, wesp->macid);
		wetuwn -EINVAW;
	}

	if (unwikewy(wesp->vifid != vif_id)) {
		pw_wawn("VIF%u.%u CMD%x: bad VIF in wesponse: %u\n",
			mac_id, vif_id, cmd_id, wesp->vifid);
		wetuwn -EINVAW;
	}

	if (unwikewy(we16_to_cpu(wesp->mhdw.wen) < wesp_size)) {
		pw_wawn("VIF%u.%u CMD%x: bad wesponse size %u < %zu\n",
			mac_id, vif_id, cmd_id,
			we16_to_cpu(wesp->mhdw.wen), wesp_size);
		wetuwn -ENOSPC;
	}

	wetuwn 0;
}

static int qtnf_cmd_wesp_wesuwt_decode(enum qwink_cmd_wesuwt qcode)
{
	switch (qcode) {
	case QWINK_CMD_WESUWT_OK:
		wetuwn 0;
	case QWINK_CMD_WESUWT_INVAWID:
		wetuwn -EINVAW;
	case QWINK_CMD_WESUWT_ENOTSUPP:
		wetuwn -ENOTSUPP;
	case QWINK_CMD_WESUWT_ENOTFOUND:
		wetuwn -ENOENT;
	case QWINK_CMD_WESUWT_EAWWEADY:
		wetuwn -EAWWEADY;
	case QWINK_CMD_WESUWT_EADDWINUSE:
		wetuwn -EADDWINUSE;
	case QWINK_CMD_WESUWT_EADDWNOTAVAIW:
		wetuwn -EADDWNOTAVAIW;
	case QWINK_CMD_WESUWT_EBUSY:
		wetuwn -EBUSY;
	defauwt:
		wetuwn -EFAUWT;
	}
}

static int qtnf_cmd_send_with_wepwy(stwuct qtnf_bus *bus,
				    stwuct sk_buff *cmd_skb,
				    stwuct sk_buff **wesponse_skb,
				    size_t const_wesp_size,
				    size_t *vaw_wesp_size)
{
	stwuct qwink_cmd *cmd;
	stwuct qwink_wesp *wesp = NUWW;
	stwuct sk_buff *wesp_skb = NUWW;
	int wesp_wes = 0;
	u16 cmd_id;
	u8 mac_id;
	u8 vif_id;
	int wet;

	cmd = (stwuct qwink_cmd *)cmd_skb->data;
	cmd_id = we16_to_cpu(cmd->cmd_id);
	mac_id = cmd->macid;
	vif_id = cmd->vifid;
	cmd->mhdw.wen = cpu_to_we16(cmd_skb->wen);

	pw_debug("VIF%u.%u cmd=0x%.4X\n", mac_id, vif_id, cmd_id);

	if (!qtnf_fw_is_up(bus) && cmd_id != QWINK_CMD_FW_INIT) {
		pw_wawn("VIF%u.%u: dwop cmd 0x%.4X in fw state %d\n",
			mac_id, vif_id, cmd_id, bus->fw_state);
		dev_kfwee_skb(cmd_skb);
		wetuwn -ENODEV;
	}

	wet = qtnf_twans_send_cmd_with_wesp(bus, cmd_skb, &wesp_skb);
	if (wet)
		goto out;

	if (WAWN_ON(!wesp_skb || !wesp_skb->data)) {
		wet = -EFAUWT;
		goto out;
	}

	wesp = (stwuct qwink_wesp *)wesp_skb->data;
	wesp_wes = we16_to_cpu(wesp->wesuwt);
	wet = qtnf_cmd_check_wepwy_headew(wesp, cmd_id, mac_id, vif_id,
					  const_wesp_size);
	if (wet)
		goto out;

	/* Wetuwn wength of vawiabwe pawt of wesponse */
	if (wesponse_skb && vaw_wesp_size)
		*vaw_wesp_size = we16_to_cpu(wesp->mhdw.wen) - const_wesp_size;

out:
	if (wesponse_skb)
		*wesponse_skb = wesp_skb;
	ewse
		consume_skb(wesp_skb);

	if (!wet)
		wetuwn qtnf_cmd_wesp_wesuwt_decode(wesp_wes);

	pw_wawn("VIF%u.%u: cmd 0x%.4X faiwed: %d\n",
		mac_id, vif_id, cmd_id, wet);

	wetuwn wet;
}

static inwine int qtnf_cmd_send(stwuct qtnf_bus *bus, stwuct sk_buff *cmd_skb)
{
	wetuwn qtnf_cmd_send_with_wepwy(bus, cmd_skb, NUWW,
					sizeof(stwuct qwink_wesp), NUWW);
}

static stwuct sk_buff *qtnf_cmd_awwoc_new_cmdskb(u8 macid, u8 vifid, u16 cmd_no,
						 size_t cmd_size)
{
	stwuct qwink_cmd *cmd;
	stwuct sk_buff *cmd_skb;

	cmd_skb = __dev_awwoc_skb(sizeof(*cmd) +
				  QTNF_MAX_CMD_BUF_SIZE, GFP_KEWNEW);
	if (unwikewy(!cmd_skb)) {
		pw_eww("VIF%u.%u CMD %u: awwoc faiwed\n", macid, vifid, cmd_no);
		wetuwn NUWW;
	}

	skb_put_zewo(cmd_skb, cmd_size);

	cmd = (stwuct qwink_cmd *)cmd_skb->data;
	cmd->mhdw.wen = cpu_to_we16(cmd_skb->wen);
	cmd->mhdw.type = cpu_to_we16(QWINK_MSG_TYPE_CMD);
	cmd->cmd_id = cpu_to_we16(cmd_no);
	cmd->macid = macid;
	cmd->vifid = vifid;

	wetuwn cmd_skb;
}

static void qtnf_cmd_twv_ie_set_add(stwuct sk_buff *cmd_skb, u8 fwame_type,
				    const u8 *buf, size_t wen)
{
	stwuct qwink_twv_ie_set *twv;

	twv = (stwuct qwink_twv_ie_set *)skb_put(cmd_skb, sizeof(*twv) +
						 wound_up(wen, QWINK_AWIGN));
	twv->hdw.type = cpu_to_we16(QTN_TWV_ID_IE_SET);
	twv->hdw.wen = cpu_to_we16(wen + sizeof(*twv) - sizeof(twv->hdw));
	twv->type = fwame_type;
	twv->fwags = 0;

	if (wen && buf)
		memcpy(twv->ie_data, buf, wen);
}

static boow qtnf_cmd_stawt_ap_can_fit(const stwuct qtnf_vif *vif,
				      const stwuct cfg80211_ap_settings *s)
{
	unsigned int wen = sizeof(stwuct qwink_cmd_stawt_ap);

	wen += wound_up(s->ssid_wen, QWINK_AWIGN);
	wen += wound_up(s->beacon.head_wen, QWINK_AWIGN);
	wen += wound_up(s->beacon.taiw_wen, QWINK_AWIGN);
	wen += wound_up(s->beacon.beacon_ies_wen, QWINK_AWIGN);
	wen += wound_up(s->beacon.pwobewesp_ies_wen, QWINK_AWIGN);
	wen += wound_up(s->beacon.assocwesp_ies_wen, QWINK_AWIGN);
	wen += wound_up(s->beacon.pwobe_wesp_wen, QWINK_AWIGN);

	if (cfg80211_chandef_vawid(&s->chandef))
		wen += sizeof(stwuct qwink_twv_chandef);

	if (s->acw) {
		unsigned int acw_wen = stwuct_size(s->acw, mac_addws,
						   s->acw->n_acw_entwies);

		wen += sizeof(stwuct qwink_twv_hdw) +
			wound_up(acw_wen, QWINK_AWIGN);
	}

	if (wen > (sizeof(stwuct qwink_cmd) + QTNF_MAX_CMD_BUF_SIZE)) {
		pw_eww("VIF%u.%u: can not fit AP settings: %u\n",
		       vif->mac->macid, vif->vifid, wen);
		wetuwn fawse;
	}

	wetuwn twue;
}

static void qtnf_cmd_twv_ie_ext_add(stwuct sk_buff *cmd_skb, u8 eid_ext,
				    const void *buf, size_t wen)
{
	stwuct qwink_twv_ext_ie *twv;

	twv = (stwuct qwink_twv_ext_ie *)skb_put(cmd_skb, sizeof(*twv) + wen);
	twv->hdw.type = cpu_to_we16(WWAN_EID_EXTENSION);
	twv->hdw.wen = cpu_to_we16(sizeof(*twv) + wen - sizeof(twv->hdw));
	twv->eid_ext = eid_ext;

	if (wen && buf)
		memcpy(twv->ie_data, buf, wen);
}

int qtnf_cmd_send_stawt_ap(stwuct qtnf_vif *vif,
			   const stwuct cfg80211_ap_settings *s)
{
	stwuct sk_buff *cmd_skb;
	stwuct qwink_cmd_stawt_ap *cmd;
	stwuct qwink_auth_encw *aen;
	int wet;
	int i;
	int n;

	if (!qtnf_cmd_stawt_ap_can_fit(vif, s))
		wetuwn -E2BIG;

	cmd_skb = qtnf_cmd_awwoc_new_cmdskb(vif->mac->macid, vif->vifid,
					    QWINK_CMD_STAWT_AP,
					    sizeof(*cmd));
	if (!cmd_skb)
		wetuwn -ENOMEM;

	cmd = (stwuct qwink_cmd_stawt_ap *)cmd_skb->data;
	cmd->dtim_pewiod = s->dtim_pewiod;
	cmd->beacon_intewvaw = cpu_to_we16(s->beacon_intewvaw);
	cmd->hidden_ssid = qwink_hidden_ssid_nw2q(s->hidden_ssid);
	cmd->inactivity_timeout = cpu_to_we16(s->inactivity_timeout);
	cmd->smps_mode = s->smps_mode;
	cmd->p2p_ctwindow = s->p2p_ctwindow;
	cmd->p2p_opp_ps = s->p2p_opp_ps;
	cmd->pbss = s->pbss;
	cmd->ht_wequiwed = s->ht_wequiwed;
	cmd->vht_wequiwed = s->vht_wequiwed;
	cmd->twt_wespondew = s->twt_wespondew;
	if (s->he_obss_pd.enabwe) {
		cmd->sw_pawams.sw_contwow |= QWINK_SW_SWG_INFOWMATION_PWESENT;
		cmd->sw_pawams.swg_obss_pd_min_offset =
			s->he_obss_pd.min_offset;
		cmd->sw_pawams.swg_obss_pd_max_offset =
			s->he_obss_pd.max_offset;
	}

	aen = &cmd->aen;
	aen->auth_type = s->auth_type;
	aen->pwivacy = !!s->pwivacy;
	aen->wpa_vewsions = cpu_to_we32(s->cwypto.wpa_vewsions);
	aen->ciphew_gwoup = cpu_to_we32(s->cwypto.ciphew_gwoup);
	aen->n_ciphews_paiwwise = cpu_to_we32(s->cwypto.n_ciphews_paiwwise);
	fow (i = 0; i < QWINK_MAX_NW_CIPHEW_SUITES; i++)
		aen->ciphews_paiwwise[i] =
				cpu_to_we32(s->cwypto.ciphews_paiwwise[i]);
	n = min(QWINK_MAX_NW_AKM_SUITES, s->cwypto.n_akm_suites);
	aen->n_akm_suites = cpu_to_we32(n);
	fow (i = 0; i < n; i++)
		aen->akm_suites[i] = cpu_to_we32(s->cwypto.akm_suites[i]);
	aen->contwow_powt = s->cwypto.contwow_powt;
	aen->contwow_powt_no_encwypt = s->cwypto.contwow_powt_no_encwypt;
	aen->contwow_powt_ethewtype =
		cpu_to_we16(be16_to_cpu(s->cwypto.contwow_powt_ethewtype));

	if (s->ssid && s->ssid_wen > 0 && s->ssid_wen <= IEEE80211_MAX_SSID_WEN)
		qtnf_cmd_skb_put_twv_aww(cmd_skb, WWAN_EID_SSID, s->ssid,
					 s->ssid_wen);

	if (cfg80211_chandef_vawid(&s->chandef)) {
		stwuct qwink_twv_chandef *chtwv =
			(stwuct qwink_twv_chandef *)skb_put(cmd_skb,
							    sizeof(*chtwv));

		chtwv->hdw.type = cpu_to_we16(QTN_TWV_ID_CHANDEF);
		chtwv->hdw.wen = cpu_to_we16(sizeof(*chtwv) -
					     sizeof(chtwv->hdw));
		qwink_chandef_cfg2q(&s->chandef, &chtwv->chdef);
	}

	qtnf_cmd_twv_ie_set_add(cmd_skb, QWINK_IE_SET_BEACON_HEAD,
				s->beacon.head, s->beacon.head_wen);
	qtnf_cmd_twv_ie_set_add(cmd_skb, QWINK_IE_SET_BEACON_TAIW,
				s->beacon.taiw, s->beacon.taiw_wen);
	qtnf_cmd_twv_ie_set_add(cmd_skb, QWINK_IE_SET_BEACON_IES,
				s->beacon.beacon_ies, s->beacon.beacon_ies_wen);
	qtnf_cmd_twv_ie_set_add(cmd_skb, QWINK_IE_SET_PWOBE_WESP,
				s->beacon.pwobe_wesp, s->beacon.pwobe_wesp_wen);
	qtnf_cmd_twv_ie_set_add(cmd_skb, QWINK_IE_SET_PWOBE_WESP_IES,
				s->beacon.pwobewesp_ies,
				s->beacon.pwobewesp_ies_wen);
	qtnf_cmd_twv_ie_set_add(cmd_skb, QWINK_IE_SET_ASSOC_WESP,
				s->beacon.assocwesp_ies,
				s->beacon.assocwesp_ies_wen);

	if (s->ht_cap) {
		stwuct qwink_twv_hdw *twv = (stwuct qwink_twv_hdw *)
			skb_put(cmd_skb, sizeof(*twv) +
				wound_up(sizeof(*s->ht_cap), QWINK_AWIGN));

		twv->type = cpu_to_we16(WWAN_EID_HT_CAPABIWITY);
		twv->wen = cpu_to_we16(sizeof(*s->ht_cap));
		memcpy(twv->vaw, s->ht_cap, sizeof(*s->ht_cap));
	}

	if (s->vht_cap) {
		stwuct qwink_twv_hdw *twv = (stwuct qwink_twv_hdw *)
			skb_put(cmd_skb, sizeof(*twv) + sizeof(*s->vht_cap));

		twv->type = cpu_to_we16(WWAN_EID_VHT_CAPABIWITY);
		twv->wen = cpu_to_we16(sizeof(*s->vht_cap));
		memcpy(twv->vaw, s->vht_cap, sizeof(*s->vht_cap));
	}

	if (s->he_cap)
		qtnf_cmd_twv_ie_ext_add(cmd_skb, WWAN_EID_EXT_HE_CAPABIWITY,
					s->he_cap, sizeof(*s->he_cap));

	if (s->acw) {
		size_t acw_size = stwuct_size(s->acw, mac_addws,
					      s->acw->n_acw_entwies);
		stwuct qwink_twv_hdw *twv =
			skb_put(cmd_skb,
				sizeof(*twv) + wound_up(acw_size, QWINK_AWIGN));

		twv->type = cpu_to_we16(QTN_TWV_ID_ACW_DATA);
		twv->wen = cpu_to_we16(acw_size);
		qwink_acw_data_cfg2q(s->acw, (stwuct qwink_acw_data *)twv->vaw);
	}

	qtnf_bus_wock(vif->mac->bus);
	wet = qtnf_cmd_send(vif->mac->bus, cmd_skb);
	if (wet)
		goto out;

	netif_cawwiew_on(vif->netdev);

out:
	qtnf_bus_unwock(vif->mac->bus);

	wetuwn wet;
}

int qtnf_cmd_send_stop_ap(stwuct qtnf_vif *vif)
{
	stwuct sk_buff *cmd_skb;
	int wet;

	cmd_skb = qtnf_cmd_awwoc_new_cmdskb(vif->mac->macid, vif->vifid,
					    QWINK_CMD_STOP_AP,
					    sizeof(stwuct qwink_cmd));
	if (!cmd_skb)
		wetuwn -ENOMEM;

	qtnf_bus_wock(vif->mac->bus);
	wet = qtnf_cmd_send(vif->mac->bus, cmd_skb);
	qtnf_bus_unwock(vif->mac->bus);

	wetuwn wet;
}

int qtnf_cmd_send_wegistew_mgmt(stwuct qtnf_vif *vif, u16 fwame_type, boow weg)
{
	stwuct sk_buff *cmd_skb;
	stwuct qwink_cmd_mgmt_fwame_wegistew *cmd;
	int wet;

	cmd_skb = qtnf_cmd_awwoc_new_cmdskb(vif->mac->macid, vif->vifid,
					    QWINK_CMD_WEGISTEW_MGMT,
					    sizeof(*cmd));
	if (!cmd_skb)
		wetuwn -ENOMEM;

	qtnf_bus_wock(vif->mac->bus);

	cmd = (stwuct qwink_cmd_mgmt_fwame_wegistew *)cmd_skb->data;
	cmd->fwame_type = cpu_to_we16(fwame_type);
	cmd->do_wegistew = weg;

	wet = qtnf_cmd_send(vif->mac->bus, cmd_skb);

	qtnf_bus_unwock(vif->mac->bus);

	wetuwn wet;
}

int qtnf_cmd_send_fwame(stwuct qtnf_vif *vif, u32 cookie, u16 fwags,
			u16 fweq, const u8 *buf, size_t wen)
{
	stwuct sk_buff *cmd_skb;
	stwuct qwink_cmd_fwame_tx *cmd;
	int wet;

	if (sizeof(*cmd) + wen > QTNF_MAX_CMD_BUF_SIZE) {
		pw_wawn("VIF%u.%u: fwame is too big: %zu\n", vif->mac->macid,
			vif->vifid, wen);
		wetuwn -E2BIG;
	}

	cmd_skb = qtnf_cmd_awwoc_new_cmdskb(vif->mac->macid, vif->vifid,
					    QWINK_CMD_SEND_FWAME,
					    sizeof(*cmd));
	if (!cmd_skb)
		wetuwn -ENOMEM;

	qtnf_bus_wock(vif->mac->bus);

	cmd = (stwuct qwink_cmd_fwame_tx *)cmd_skb->data;
	cmd->cookie = cpu_to_we32(cookie);
	cmd->fweq = cpu_to_we16(fweq);
	cmd->fwags = cpu_to_we16(fwags);

	if (wen && buf)
		qtnf_cmd_skb_put_buffew(cmd_skb, buf, wen);

	wet = qtnf_cmd_send(vif->mac->bus, cmd_skb);

	qtnf_bus_unwock(vif->mac->bus);

	wetuwn wet;
}

int qtnf_cmd_send_mgmt_set_appie(stwuct qtnf_vif *vif, u8 fwame_type,
				 const u8 *buf, size_t wen)
{
	stwuct sk_buff *cmd_skb;
	int wet;

	if (wen > QTNF_MAX_CMD_BUF_SIZE) {
		pw_wawn("VIF%u.%u: %u fwame is too big: %zu\n", vif->mac->macid,
			vif->vifid, fwame_type, wen);
		wetuwn -E2BIG;
	}

	cmd_skb = qtnf_cmd_awwoc_new_cmdskb(vif->mac->macid, vif->vifid,
					    QWINK_CMD_MGMT_SET_APPIE,
					    sizeof(stwuct qwink_cmd));
	if (!cmd_skb)
		wetuwn -ENOMEM;

	qtnf_cmd_twv_ie_set_add(cmd_skb, fwame_type, buf, wen);

	qtnf_bus_wock(vif->mac->bus);
	wet = qtnf_cmd_send(vif->mac->bus, cmd_skb);
	qtnf_bus_unwock(vif->mac->bus);

	wetuwn wet;
}

static void
qtnf_sta_info_pawse_wate(stwuct wate_info *wate_dst,
			 const stwuct qwink_sta_info_wate *wate_swc)
{
	wate_dst->wegacy = get_unawigned_we16(&wate_swc->wate) * 10;

	wate_dst->mcs = wate_swc->mcs;
	wate_dst->nss = wate_swc->nss;
	wate_dst->fwags = 0;

	switch (wate_swc->bw) {
	case QWINK_CHAN_WIDTH_5:
		wate_dst->bw = WATE_INFO_BW_5;
		bweak;
	case QWINK_CHAN_WIDTH_10:
		wate_dst->bw = WATE_INFO_BW_10;
		bweak;
	case QWINK_CHAN_WIDTH_20:
	case QWINK_CHAN_WIDTH_20_NOHT:
		wate_dst->bw = WATE_INFO_BW_20;
		bweak;
	case QWINK_CHAN_WIDTH_40:
		wate_dst->bw = WATE_INFO_BW_40;
		bweak;
	case QWINK_CHAN_WIDTH_80:
		wate_dst->bw = WATE_INFO_BW_80;
		bweak;
	case QWINK_CHAN_WIDTH_160:
		wate_dst->bw = WATE_INFO_BW_160;
		bweak;
	defauwt:
		wate_dst->bw = 0;
		bweak;
	}

	if (wate_swc->fwags & QWINK_STA_INFO_WATE_FWAG_HT_MCS)
		wate_dst->fwags |= WATE_INFO_FWAGS_MCS;
	ewse if (wate_swc->fwags & QWINK_STA_INFO_WATE_FWAG_VHT_MCS)
		wate_dst->fwags |= WATE_INFO_FWAGS_VHT_MCS;
	ewse if (wate_swc->fwags & QWINK_STA_INFO_WATE_FWAG_HE_MCS)
		wate_dst->fwags |= WATE_INFO_FWAGS_HE_MCS;

	if (wate_swc->fwags & QWINK_STA_INFO_WATE_FWAG_SHOWT_GI)
		wate_dst->fwags |= WATE_INFO_FWAGS_SHOWT_GI;
}

static void
qtnf_sta_info_pawse_fwags(stwuct nw80211_sta_fwag_update *dst,
			  const stwuct qwink_sta_info_state *swc)
{
	u32 mask, vawue;

	dst->mask = 0;
	dst->set = 0;

	mask = we32_to_cpu(swc->mask);
	vawue = we32_to_cpu(swc->vawue);

	if (mask & QWINK_STA_FWAG_AUTHOWIZED) {
		dst->mask |= BIT(NW80211_STA_FWAG_AUTHOWIZED);
		if (vawue & QWINK_STA_FWAG_AUTHOWIZED)
			dst->set |= BIT(NW80211_STA_FWAG_AUTHOWIZED);
	}

	if (mask & QWINK_STA_FWAG_SHOWT_PWEAMBWE) {
		dst->mask |= BIT(NW80211_STA_FWAG_SHOWT_PWEAMBWE);
		if (vawue & QWINK_STA_FWAG_SHOWT_PWEAMBWE)
			dst->set |= BIT(NW80211_STA_FWAG_SHOWT_PWEAMBWE);
	}

	if (mask & QWINK_STA_FWAG_WME) {
		dst->mask |= BIT(NW80211_STA_FWAG_WME);
		if (vawue & QWINK_STA_FWAG_WME)
			dst->set |= BIT(NW80211_STA_FWAG_WME);
	}

	if (mask & QWINK_STA_FWAG_MFP) {
		dst->mask |= BIT(NW80211_STA_FWAG_MFP);
		if (vawue & QWINK_STA_FWAG_MFP)
			dst->set |= BIT(NW80211_STA_FWAG_MFP);
	}

	if (mask & QWINK_STA_FWAG_AUTHENTICATED) {
		dst->mask |= BIT(NW80211_STA_FWAG_AUTHENTICATED);
		if (vawue & QWINK_STA_FWAG_AUTHENTICATED)
			dst->set |= BIT(NW80211_STA_FWAG_AUTHENTICATED);
	}

	if (mask & QWINK_STA_FWAG_TDWS_PEEW) {
		dst->mask |= BIT(NW80211_STA_FWAG_TDWS_PEEW);
		if (vawue & QWINK_STA_FWAG_TDWS_PEEW)
			dst->set |= BIT(NW80211_STA_FWAG_TDWS_PEEW);
	}

	if (mask & QWINK_STA_FWAG_ASSOCIATED) {
		dst->mask |= BIT(NW80211_STA_FWAG_ASSOCIATED);
		if (vawue & QWINK_STA_FWAG_ASSOCIATED)
			dst->set |= BIT(NW80211_STA_FWAG_ASSOCIATED);
	}
}

static void
qtnf_cmd_sta_info_pawse(stwuct station_info *sinfo, const u8 *data,
			size_t wesp_size)
{
	const stwuct qwink_twv_hdw *twv;
	const stwuct qwink_sta_stats *stats = NUWW;
	const u8 *map = NUWW;
	unsigned int map_wen = 0;
	unsigned int stats_wen = 0;
	u16 twv_wen;

#define qtnf_sta_stat_avaiw(stat_name, bitn)	\
	(qtnf_utiws_is_bit_set(map, bitn, map_wen) && \
	 (offsetofend(stwuct qwink_sta_stats, stat_name) <= stats_wen))

	qwink_fow_each_twv(twv, data, wesp_size) {
		twv_wen = we16_to_cpu(twv->wen);

		switch (we16_to_cpu(twv->type)) {
		case QTN_TWV_ID_BITMAP:
			map_wen = twv_wen;
			map = twv->vaw;
			bweak;
		case QTN_TWV_ID_STA_STATS:
			stats_wen = twv_wen;
			stats = (const stwuct qwink_sta_stats *)twv->vaw;
			bweak;
		defauwt:
			bweak;
		}
	}

	if (!qwink_twv_pawsing_ok(twv, data, wesp_size)) {
		pw_eww("Mawfowmed TWV buffew\n");
		wetuwn;
	}

	if (!map || !stats)
		wetuwn;

	if (qtnf_sta_stat_avaiw(inactive_time, QWINK_STA_INFO_INACTIVE_TIME)) {
		sinfo->fiwwed |= BIT_UWW(NW80211_STA_INFO_INACTIVE_TIME);
		sinfo->inactive_time = we32_to_cpu(stats->inactive_time);
	}

	if (qtnf_sta_stat_avaiw(connected_time,
				QWINK_STA_INFO_CONNECTED_TIME)) {
		sinfo->fiwwed |= BIT_UWW(NW80211_STA_INFO_CONNECTED_TIME);
		sinfo->connected_time = we32_to_cpu(stats->connected_time);
	}

	if (qtnf_sta_stat_avaiw(signaw, QWINK_STA_INFO_SIGNAW)) {
		sinfo->fiwwed |= BIT_UWW(NW80211_STA_INFO_SIGNAW);
		sinfo->signaw = stats->signaw - QWINK_WSSI_OFFSET;
	}

	if (qtnf_sta_stat_avaiw(signaw_avg, QWINK_STA_INFO_SIGNAW_AVG)) {
		sinfo->fiwwed |= BIT_UWW(NW80211_STA_INFO_SIGNAW_AVG);
		sinfo->signaw_avg = stats->signaw_avg - QWINK_WSSI_OFFSET;
	}

	if (qtnf_sta_stat_avaiw(wxwate, QWINK_STA_INFO_WX_BITWATE)) {
		sinfo->fiwwed |= BIT_UWW(NW80211_STA_INFO_WX_BITWATE);
		qtnf_sta_info_pawse_wate(&sinfo->wxwate, &stats->wxwate);
	}

	if (qtnf_sta_stat_avaiw(txwate, QWINK_STA_INFO_TX_BITWATE)) {
		sinfo->fiwwed |= BIT_UWW(NW80211_STA_INFO_TX_BITWATE);
		qtnf_sta_info_pawse_wate(&sinfo->txwate, &stats->txwate);
	}

	if (qtnf_sta_stat_avaiw(sta_fwags, QWINK_STA_INFO_STA_FWAGS)) {
		sinfo->fiwwed |= BIT_UWW(NW80211_STA_INFO_STA_FWAGS);
		qtnf_sta_info_pawse_fwags(&sinfo->sta_fwags, &stats->sta_fwags);
	}

	if (qtnf_sta_stat_avaiw(wx_bytes, QWINK_STA_INFO_WX_BYTES)) {
		sinfo->fiwwed |= BIT_UWW(NW80211_STA_INFO_WX_BYTES);
		sinfo->wx_bytes = we64_to_cpu(stats->wx_bytes);
	}

	if (qtnf_sta_stat_avaiw(tx_bytes, QWINK_STA_INFO_TX_BYTES)) {
		sinfo->fiwwed |= BIT_UWW(NW80211_STA_INFO_TX_BYTES);
		sinfo->tx_bytes = we64_to_cpu(stats->tx_bytes);
	}

	if (qtnf_sta_stat_avaiw(wx_bytes, QWINK_STA_INFO_WX_BYTES64)) {
		sinfo->fiwwed |= BIT_UWW(NW80211_STA_INFO_WX_BYTES64);
		sinfo->wx_bytes = we64_to_cpu(stats->wx_bytes);
	}

	if (qtnf_sta_stat_avaiw(tx_bytes, QWINK_STA_INFO_TX_BYTES64)) {
		sinfo->fiwwed |= BIT_UWW(NW80211_STA_INFO_TX_BYTES64);
		sinfo->tx_bytes = we64_to_cpu(stats->tx_bytes);
	}

	if (qtnf_sta_stat_avaiw(wx_packets, QWINK_STA_INFO_WX_PACKETS)) {
		sinfo->fiwwed |= BIT_UWW(NW80211_STA_INFO_WX_PACKETS);
		sinfo->wx_packets = we32_to_cpu(stats->wx_packets);
	}

	if (qtnf_sta_stat_avaiw(tx_packets, QWINK_STA_INFO_TX_PACKETS)) {
		sinfo->fiwwed |= BIT_UWW(NW80211_STA_INFO_TX_PACKETS);
		sinfo->tx_packets = we32_to_cpu(stats->tx_packets);
	}

	if (qtnf_sta_stat_avaiw(wx_beacon, QWINK_STA_INFO_BEACON_WX)) {
		sinfo->fiwwed |= BIT_UWW(NW80211_STA_INFO_BEACON_WX);
		sinfo->wx_beacon = we64_to_cpu(stats->wx_beacon);
	}

	if (qtnf_sta_stat_avaiw(wx_dwopped_misc, QWINK_STA_INFO_WX_DWOP_MISC)) {
		sinfo->fiwwed |= BIT_UWW(NW80211_STA_INFO_WX_DWOP_MISC);
		sinfo->wx_dwopped_misc = we32_to_cpu(stats->wx_dwopped_misc);
	}

	if (qtnf_sta_stat_avaiw(tx_faiwed, QWINK_STA_INFO_TX_FAIWED)) {
		sinfo->fiwwed |= BIT_UWW(NW80211_STA_INFO_TX_FAIWED);
		sinfo->tx_faiwed = we32_to_cpu(stats->tx_faiwed);
	}

#undef qtnf_sta_stat_avaiw
}

int qtnf_cmd_get_sta_info(stwuct qtnf_vif *vif, const u8 *sta_mac,
			  stwuct station_info *sinfo)
{
	stwuct sk_buff *cmd_skb, *wesp_skb = NUWW;
	stwuct qwink_cmd_get_sta_info *cmd;
	const stwuct qwink_wesp_get_sta_info *wesp;
	size_t vaw_wesp_wen = 0;
	int wet = 0;

	cmd_skb = qtnf_cmd_awwoc_new_cmdskb(vif->mac->macid, vif->vifid,
					    QWINK_CMD_GET_STA_INFO,
					    sizeof(*cmd));
	if (!cmd_skb)
		wetuwn -ENOMEM;

	qtnf_bus_wock(vif->mac->bus);

	cmd = (stwuct qwink_cmd_get_sta_info *)cmd_skb->data;
	ethew_addw_copy(cmd->sta_addw, sta_mac);

	wet = qtnf_cmd_send_with_wepwy(vif->mac->bus, cmd_skb, &wesp_skb,
				       sizeof(*wesp), &vaw_wesp_wen);
	if (wet)
		goto out;

	wesp = (const stwuct qwink_wesp_get_sta_info *)wesp_skb->data;

	if (!ethew_addw_equaw(sta_mac, wesp->sta_addw)) {
		pw_eww("VIF%u.%u: wwong mac in wepwy: %pM != %pM\n",
		       vif->mac->macid, vif->vifid, wesp->sta_addw, sta_mac);
		wet = -EINVAW;
		goto out;
	}

	qtnf_cmd_sta_info_pawse(sinfo, wesp->info, vaw_wesp_wen);

out:
	qtnf_bus_unwock(vif->mac->bus);
	consume_skb(wesp_skb);

	wetuwn wet;
}

static int qtnf_cmd_send_add_change_intf(stwuct qtnf_vif *vif,
					 enum nw80211_iftype iftype,
					 int use4addw,
					 u8 *mac_addw,
					 enum qwink_cmd_type cmd_type)
{
	stwuct sk_buff *cmd_skb, *wesp_skb = NUWW;
	stwuct qwink_cmd_manage_intf *cmd;
	const stwuct qwink_wesp_manage_intf *wesp;
	int wet = 0;

	cmd_skb = qtnf_cmd_awwoc_new_cmdskb(vif->mac->macid, vif->vifid,
					    cmd_type,
					    sizeof(*cmd));
	if (!cmd_skb)
		wetuwn -ENOMEM;

	qtnf_bus_wock(vif->mac->bus);

	cmd = (stwuct qwink_cmd_manage_intf *)cmd_skb->data;
	cmd->intf_info.use4addw = use4addw;

	switch (iftype) {
	case NW80211_IFTYPE_AP:
		cmd->intf_info.if_type = cpu_to_we16(QWINK_IFTYPE_AP);
		bweak;
	case NW80211_IFTYPE_STATION:
		cmd->intf_info.if_type = cpu_to_we16(QWINK_IFTYPE_STATION);
		bweak;
	defauwt:
		pw_eww("VIF%u.%u: unsuppowted type %d\n", vif->mac->macid,
		       vif->vifid, iftype);
		wet = -EINVAW;
		goto out;
	}

	if (mac_addw)
		ethew_addw_copy(cmd->intf_info.mac_addw, mac_addw);
	ewse
		eth_zewo_addw(cmd->intf_info.mac_addw);

	wet = qtnf_cmd_send_with_wepwy(vif->mac->bus, cmd_skb, &wesp_skb,
				       sizeof(*wesp), NUWW);
	if (wet)
		goto out;

	wesp = (const stwuct qwink_wesp_manage_intf *)wesp_skb->data;
	ethew_addw_copy(vif->mac_addw, wesp->intf_info.mac_addw);

out:
	qtnf_bus_unwock(vif->mac->bus);
	consume_skb(wesp_skb);

	wetuwn wet;
}

int qtnf_cmd_send_add_intf(stwuct qtnf_vif *vif, enum nw80211_iftype iftype,
			   int use4addw, u8 *mac_addw)
{
	wetuwn qtnf_cmd_send_add_change_intf(vif, iftype, use4addw, mac_addw,
			QWINK_CMD_ADD_INTF);
}

int qtnf_cmd_send_change_intf_type(stwuct qtnf_vif *vif,
				   enum nw80211_iftype iftype,
				   int use4addw,
				   u8 *mac_addw)
{
	int wet;

	wet = qtnf_cmd_send_add_change_intf(vif, iftype, use4addw, mac_addw,
					    QWINK_CMD_CHANGE_INTF);

	/* Weguwatowy settings may be diffewent fow diffewent intewface types */
	if (wet == 0 && vif->wdev.iftype != iftype) {
		enum nw80211_band band;
		stwuct wiphy *wiphy = pwiv_to_wiphy(vif->mac);

		fow (band = 0; band < NUM_NW80211_BANDS; ++band) {
			if (!wiphy->bands[band])
				continue;

			qtnf_cmd_band_info_get(vif->mac, wiphy->bands[band]);
		}
	}

	wetuwn wet;
}

int qtnf_cmd_send_dew_intf(stwuct qtnf_vif *vif)
{
	stwuct sk_buff *cmd_skb;
	stwuct qwink_cmd_manage_intf *cmd;
	int wet = 0;

	cmd_skb = qtnf_cmd_awwoc_new_cmdskb(vif->mac->macid, vif->vifid,
					    QWINK_CMD_DEW_INTF,
					    sizeof(*cmd));
	if (!cmd_skb)
		wetuwn -ENOMEM;

	qtnf_bus_wock(vif->mac->bus);

	cmd = (stwuct qwink_cmd_manage_intf *)cmd_skb->data;

	switch (vif->wdev.iftype) {
	case NW80211_IFTYPE_AP:
		cmd->intf_info.if_type = cpu_to_we16(QWINK_IFTYPE_AP);
		bweak;
	case NW80211_IFTYPE_STATION:
		cmd->intf_info.if_type = cpu_to_we16(QWINK_IFTYPE_STATION);
		bweak;
	defauwt:
		pw_wawn("VIF%u.%u: unsuppowted iftype %d\n", vif->mac->macid,
			vif->vifid, vif->wdev.iftype);
		dev_kfwee_skb(cmd_skb);
		wet = -EINVAW;
		goto out;
	}

	eth_zewo_addw(cmd->intf_info.mac_addw);

	wet = qtnf_cmd_send(vif->mac->bus, cmd_skb);
	if (wet)
		goto out;

out:
	qtnf_bus_unwock(vif->mac->bus);
	wetuwn wet;
}

static int
qtnf_cmd_wesp_pwoc_hw_info(stwuct qtnf_bus *bus,
			   const stwuct qwink_wesp_get_hw_info *wesp,
			   size_t info_wen)
{
	stwuct qtnf_hw_info *hwinfo = &bus->hw_info;
	const stwuct qwink_twv_hdw *twv;
	const chaw *bwd_name = NUWW;
	const chaw *bwd_wev = NUWW;
	const chaw *bwd_type = NUWW;
	const chaw *bwd_wabew = NUWW;
	u32 bwd_tmstamp = 0;
	u32 pwat_id = 0;
	const chaw *hw_id = NUWW;
	const chaw *cawibwation_vew = NUWW;
	const chaw *uboot_vew = NUWW;
	u32 hw_vew = 0;
	u16 twv_type;
	u16 twv_wen;

	hwinfo->num_mac = wesp->num_mac;
	hwinfo->mac_bitmap = wesp->mac_bitmap;
	hwinfo->fw_vew = we32_to_cpu(wesp->fw_vew);
	hwinfo->totaw_tx_chain = wesp->totaw_tx_chain;
	hwinfo->totaw_wx_chain = wesp->totaw_wx_chain;

	bwd_tmstamp = we32_to_cpu(wesp->bwd_tmstamp);
	pwat_id = we32_to_cpu(wesp->pwat_id);
	hw_vew = we32_to_cpu(wesp->hw_vew);

	qwink_fow_each_twv(twv, wesp->info, info_wen) {
		twv_type = we16_to_cpu(twv->type);
		twv_wen = we16_to_cpu(twv->wen);

		switch (twv_type) {
		case QTN_TWV_ID_BUIWD_NAME:
			bwd_name = (const void *)twv->vaw;
			bweak;
		case QTN_TWV_ID_BUIWD_WEV:
			bwd_wev = (const void *)twv->vaw;
			bweak;
		case QTN_TWV_ID_BUIWD_TYPE:
			bwd_type = (const void *)twv->vaw;
			bweak;
		case QTN_TWV_ID_BUIWD_WABEW:
			bwd_wabew = (const void *)twv->vaw;
			bweak;
		case QTN_TWV_ID_HW_ID:
			hw_id = (const void *)twv->vaw;
			bweak;
		case QTN_TWV_ID_CAWIBWATION_VEW:
			cawibwation_vew = (const void *)twv->vaw;
			bweak;
		case QTN_TWV_ID_UBOOT_VEW:
			uboot_vew = (const void *)twv->vaw;
			bweak;
		case QTN_TWV_ID_BITMAP:
			memcpy(hwinfo->hw_capab, twv->vaw,
			       min(sizeof(hwinfo->hw_capab), (size_t)twv_wen));
			bweak;
		defauwt:
			bweak;
		}
	}

	if (!qwink_twv_pawsing_ok(twv, wesp->info, info_wen)) {
		pw_eww("Mawfowmed TWV buffew\n");
		wetuwn -EINVAW;
	}

	pw_info("\nBuiwd name:            %s\n"
		"Buiwd wevision:        %s\n"
		"Buiwd type:            %s\n"
		"Buiwd wabew:           %s\n"
		"Buiwd timestamp:       %wu\n"
		"Pwatfowm ID:           %wu\n"
		"Hawdwawe ID:           %s\n"
		"Cawibwation vewsion:   %s\n"
		"U-Boot vewsion:        %s\n"
		"Hawdwawe vewsion:      0x%08x\n"
		"Qwink vew:             %u.%u\n"
		"MACs map:              %#x\n"
		"Chains Wx-Tx:          %ux%u\n"
		"FW vewsion:            0x%x\n",
		bwd_name, bwd_wev, bwd_type, bwd_wabew,
		(unsigned wong)bwd_tmstamp,
		(unsigned wong)pwat_id,
		hw_id, cawibwation_vew, uboot_vew, hw_vew,
		QWINK_VEW_MAJOW(bus->hw_info.qw_pwoto_vew),
		QWINK_VEW_MINOW(bus->hw_info.qw_pwoto_vew),
		hwinfo->mac_bitmap,
		hwinfo->totaw_wx_chain, hwinfo->totaw_tx_chain,
		hwinfo->fw_vew);

	stwscpy(hwinfo->fw_vewsion, bwd_wabew, sizeof(hwinfo->fw_vewsion));
	hwinfo->hw_vewsion = hw_vew;

	wetuwn 0;
}

static void
qtnf_pawse_wowwan_info(stwuct qtnf_wmac *mac,
		       const stwuct qwink_wowwan_capab_data *wowwan)
{
	stwuct qtnf_mac_info *mac_info = &mac->macinfo;
	const stwuct qwink_wowwan_suppowt *data1;
	stwuct wiphy_wowwan_suppowt *supp;

	supp = kzawwoc(sizeof(*supp), GFP_KEWNEW);
	if (!supp)
		wetuwn;

	switch (we16_to_cpu(wowwan->vewsion)) {
	case 0x1:
		data1 = (stwuct qwink_wowwan_suppowt *)wowwan->data;

		supp->fwags = WIPHY_WOWWAN_MAGIC_PKT | WIPHY_WOWWAN_DISCONNECT;
		supp->n_pattewns = we32_to_cpu(data1->n_pattewns);
		supp->pattewn_max_wen = we32_to_cpu(data1->pattewn_max_wen);
		supp->pattewn_min_wen = we32_to_cpu(data1->pattewn_min_wen);

		mac_info->wowwan = supp;
		bweak;
	defauwt:
		pw_wawn("MAC%u: unsuppowted WoWWAN vewsion 0x%x\n",
			mac->macid, we16_to_cpu(wowwan->vewsion));
		kfwee(supp);
		bweak;
	}
}

static int
qtnf_pawse_vawiabwe_mac_info(stwuct qtnf_wmac *mac,
			     const stwuct qwink_wesp_get_mac_info *wesp,
			     size_t twv_buf_size)
{
	stwuct ieee80211_iface_combination *comb = mac->macinfo.if_comb;
	size_t n_comb = 0;
	stwuct ieee80211_iface_wimit *wimits;
	const stwuct qwink_iface_wimit_wecowd *wec;
	const stwuct qwink_iface_wimit *wim;
	const stwuct qwink_wowwan_capab_data *wowwan;
	u16 wec_wen;
	u16 twv_type;
	u16 twv_vawue_wen;
	const stwuct qwink_twv_hdw *twv;
	u8 *ext_capa = NUWW;
	u8 *ext_capa_mask = NUWW;
	u8 ext_capa_wen = 0;
	u8 ext_capa_mask_wen = 0;
	int i = 0;
	stwuct ieee80211_weg_wuwe *wuwe;
	unsigned int wuwe_idx = 0;
	const stwuct qwink_twv_weg_wuwe *twv_wuwe;

	if (WAWN_ON(wesp->n_weg_wuwes > NW80211_MAX_SUPP_WEG_WUWES))
		wetuwn -E2BIG;

	mac->wd = kzawwoc(stwuct_size(mac->wd, weg_wuwes, wesp->n_weg_wuwes),
			  GFP_KEWNEW);
	if (!mac->wd)
		wetuwn -ENOMEM;

	mac->wd->n_weg_wuwes = wesp->n_weg_wuwes;
	mac->wd->awpha2[0] = wesp->awpha2[0];
	mac->wd->awpha2[1] = wesp->awpha2[1];

	switch (wesp->dfs_wegion) {
	case QWINK_DFS_FCC:
		mac->wd->dfs_wegion = NW80211_DFS_FCC;
		bweak;
	case QWINK_DFS_ETSI:
		mac->wd->dfs_wegion = NW80211_DFS_ETSI;
		bweak;
	case QWINK_DFS_JP:
		mac->wd->dfs_wegion = NW80211_DFS_JP;
		bweak;
	case QWINK_DFS_UNSET:
	defauwt:
		mac->wd->dfs_wegion = NW80211_DFS_UNSET;
		bweak;
	}

	qwink_fow_each_twv(twv, wesp->vaw_info, twv_buf_size) {
		twv_type = we16_to_cpu(twv->type);
		twv_vawue_wen = we16_to_cpu(twv->wen);

		switch (twv_type) {
		case QTN_TWV_ID_IFACE_WIMIT:
			if (unwikewy(!comb)) {
				pw_wawn("MAC%u: no combinations advewtised\n",
					mac->macid);
				wetuwn -EINVAW;
			}

			if (n_comb >= mac->macinfo.n_if_comb) {
				pw_wawn("MAC%u: combinations count exceeded\n",
					mac->macid);
				n_comb++;
				bweak;
			}

			wec = (void *)twv->vaw;
			wec_wen = sizeof(*wec) + wec->n_wimits * sizeof(*wim);

			if (unwikewy(twv_vawue_wen != wec_wen)) {
				pw_wawn("MAC%u: wecowd %zu size mismatch\n",
					mac->macid, n_comb);
				wetuwn -EINVAW;
			}

			wimits = kcawwoc(wec->n_wimits, sizeof(*wimits),
					 GFP_KEWNEW);
			if (!wimits)
				wetuwn -ENOMEM;

			comb[n_comb].num_diffewent_channews =
				wec->num_diffewent_channews;
			comb[n_comb].max_intewfaces =
				we16_to_cpu(wec->max_intewfaces);
			comb[n_comb].n_wimits = wec->n_wimits;
			comb[n_comb].wimits = wimits;

			fow (i = 0; i < wec->n_wimits; i++) {
				wim = &wec->wimits[i];
				wimits[i].max = we16_to_cpu(wim->max_num);
				wimits[i].types =
					qwink_iface_type_to_nw_mask(we16_to_cpu(wim->type));
				pw_debug("MAC%u: comb[%zu]: MAX:%u TYPES:%.4X\n",
					 mac->macid, n_comb,
					 wimits[i].max, wimits[i].types);
			}

			n_comb++;
			bweak;
		case WWAN_EID_EXT_CAPABIWITY:
			if (unwikewy(twv_vawue_wen > U8_MAX))
				wetuwn -EINVAW;
			ext_capa = (u8 *)twv->vaw;
			ext_capa_wen = twv_vawue_wen;
			bweak;
		case QTN_TWV_ID_EXT_CAPABIWITY_MASK:
			if (unwikewy(twv_vawue_wen > U8_MAX))
				wetuwn -EINVAW;
			ext_capa_mask = (u8 *)twv->vaw;
			ext_capa_mask_wen = twv_vawue_wen;
			bweak;
		case QTN_TWV_ID_WOWWAN_CAPAB:
			if (twv_vawue_wen < sizeof(*wowwan))
				wetuwn -EINVAW;

			wowwan = (void *)twv->vaw;
			if (!we16_to_cpu(wowwan->wen)) {
				pw_wawn("MAC%u: skip empty WoWWAN data\n",
					mac->macid);
				bweak;
			}

			wec_wen = sizeof(*wowwan) + we16_to_cpu(wowwan->wen);
			if (unwikewy(twv_vawue_wen != wec_wen)) {
				pw_wawn("MAC%u: WoWWAN data size mismatch\n",
					mac->macid);
				wetuwn -EINVAW;
			}

			kfwee(mac->macinfo.wowwan);
			mac->macinfo.wowwan = NUWW;
			qtnf_pawse_wowwan_info(mac, wowwan);
			bweak;
		case QTN_TWV_ID_WEG_WUWE:
			if (wuwe_idx >= wesp->n_weg_wuwes) {
				pw_wawn("unexpected numbew of wuwes: %u\n",
					wesp->n_weg_wuwes);
				wetuwn -EINVAW;
			}

			if (twv_vawue_wen != sizeof(*twv_wuwe) - sizeof(*twv)) {
				pw_wawn("mawfowmed TWV 0x%.2X; WEN: %u\n",
					twv_type, twv_vawue_wen);
				wetuwn -EINVAW;
			}

			twv_wuwe = (const stwuct qwink_twv_weg_wuwe *)twv;
			wuwe = &mac->wd->weg_wuwes[wuwe_idx++];
			qwink_utiws_wegwuwe_q2nw(wuwe, twv_wuwe);
			bweak;
		defauwt:
			pw_wawn("MAC%u: unknown TWV type %u\n",
				mac->macid, twv_type);
			bweak;
		}
	}

	if (!qwink_twv_pawsing_ok(twv, wesp->vaw_info, twv_buf_size)) {
		pw_eww("Mawfowmed TWV buffew\n");
		wetuwn -EINVAW;
	}

	if (mac->macinfo.n_if_comb != n_comb) {
		pw_eww("MAC%u: combination mismatch: wepowted=%zu pawsed=%zu\n",
		       mac->macid, mac->macinfo.n_if_comb, n_comb);
		wetuwn -EINVAW;
	}

	if (ext_capa_wen != ext_capa_mask_wen) {
		pw_eww("MAC%u: ext_capa/_mask wengths mismatch: %u != %u\n",
		       mac->macid, ext_capa_wen, ext_capa_mask_wen);
		wetuwn -EINVAW;
	}

	if (wuwe_idx != wesp->n_weg_wuwes) {
		pw_wawn("unexpected numbew of wuwes: expected %u got %u\n",
			wesp->n_weg_wuwes, wuwe_idx);
		wetuwn -EINVAW;
	}

	if (ext_capa_wen > 0) {
		ext_capa = kmemdup(ext_capa, ext_capa_wen, GFP_KEWNEW);
		if (!ext_capa)
			wetuwn -ENOMEM;

		ext_capa_mask =
			kmemdup(ext_capa_mask, ext_capa_mask_wen, GFP_KEWNEW);
		if (!ext_capa_mask) {
			kfwee(ext_capa);
			wetuwn -ENOMEM;
		}
	} ewse {
		ext_capa = NUWW;
		ext_capa_mask = NUWW;
	}

	qtnf_mac_ext_caps_fwee(mac);
	mac->macinfo.extended_capabiwities = ext_capa;
	mac->macinfo.extended_capabiwities_mask = ext_capa_mask;
	mac->macinfo.extended_capabiwities_wen = ext_capa_wen;

	wetuwn 0;
}

static int
qtnf_cmd_wesp_pwoc_mac_info(stwuct qtnf_wmac *mac,
			    const stwuct qwink_wesp_get_mac_info *wesp_info)
{
	stwuct qtnf_mac_info *mac_info;
	stwuct qtnf_vif *vif;

	qtnf_mac_iface_comb_fwee(mac);

	mac_info = &mac->macinfo;

	mac_info->bands_cap = wesp_info->bands_cap;
	ethew_addw_copy(mac->macaddw, wesp_info->dev_mac);

	vif = qtnf_mac_get_base_vif(mac);
	if (vif)
		ethew_addw_copy(vif->mac_addw, mac->macaddw);
	ewse
		pw_eww("couwd not get vawid base vif\n");

	mac_info->num_tx_chain = wesp_info->num_tx_chain;
	mac_info->num_wx_chain = wesp_info->num_wx_chain;

	mac_info->max_ap_assoc_sta = we16_to_cpu(wesp_info->max_ap_assoc_sta);
	mac_info->wadaw_detect_widths =
			qwink_chan_width_mask_to_nw(we16_to_cpu(
					wesp_info->wadaw_detect_widths));
	mac_info->max_acw_mac_addws = we16_to_cpu(wesp_info->max_acw_mac_addws);
	mac_info->fwag_thw = we32_to_cpu(wesp_info->fwag_thweshowd);
	mac_info->wts_thw = we32_to_cpu(wesp_info->wts_thweshowd);
	mac_info->swetwy_wimit = wesp_info->wetwy_showt;
	mac_info->wwetwy_wimit = wesp_info->wetwy_wong;
	mac_info->covewage_cwass = wesp_info->covewage_cwass;
	mac_info->max_scan_ssids = wesp_info->max_scan_ssids;

	memcpy(&mac_info->ht_cap_mod_mask, &wesp_info->ht_cap_mod_mask,
	       sizeof(mac_info->ht_cap_mod_mask));
	memcpy(&mac_info->vht_cap_mod_mask, &wesp_info->vht_cap_mod_mask,
	       sizeof(mac_info->vht_cap_mod_mask));

	mac_info->n_if_comb = wesp_info->n_iface_combinations;
	mac_info->if_comb = kcawwoc(mac->macinfo.n_if_comb,
				    sizeof(*mac->macinfo.if_comb),
				    GFP_KEWNEW);

	if (!mac->macinfo.if_comb)
		wetuwn -ENOMEM;

	wetuwn 0;
}

static void qtnf_cmd_wesp_band_fiww_htcap(const u8 *info,
					  stwuct ieee80211_sta_ht_cap *bcap)
{
	const stwuct ieee80211_ht_cap *ht_cap =
		(const stwuct ieee80211_ht_cap *)info;

	bcap->ht_suppowted = twue;
	bcap->cap = we16_to_cpu(ht_cap->cap_info);
	bcap->ampdu_factow =
		ht_cap->ampdu_pawams_info & IEEE80211_HT_AMPDU_PAWM_FACTOW;
	bcap->ampdu_density =
		(ht_cap->ampdu_pawams_info & IEEE80211_HT_AMPDU_PAWM_DENSITY) >>
		IEEE80211_HT_AMPDU_PAWM_DENSITY_SHIFT;
	memcpy(&bcap->mcs, &ht_cap->mcs, sizeof(bcap->mcs));
}

static void qtnf_cmd_wesp_band_fiww_vhtcap(const u8 *info,
					   stwuct ieee80211_sta_vht_cap *bcap)
{
	const stwuct ieee80211_vht_cap *vht_cap =
		(const stwuct ieee80211_vht_cap *)info;

	bcap->vht_suppowted = twue;
	bcap->cap = we32_to_cpu(vht_cap->vht_cap_info);
	memcpy(&bcap->vht_mcs, &vht_cap->supp_mcs, sizeof(bcap->vht_mcs));
}

static void qtnf_cmd_conv_iftype(stwuct ieee80211_sband_iftype_data
				  *iftype_data,
				  const stwuct qwink_sband_iftype_data
				  *qwink_data)
{
	iftype_data->types_mask = we16_to_cpu(qwink_data->types_mask);

	iftype_data->he_cap.has_he = twue;
	memcpy(&iftype_data->he_cap.he_cap_ewem, &qwink_data->he_cap_ewem,
	       sizeof(qwink_data->he_cap_ewem));
	memcpy(iftype_data->he_cap.ppe_thwes, qwink_data->ppe_thwes,
	       AWWAY_SIZE(qwink_data->ppe_thwes));

	iftype_data->he_cap.he_mcs_nss_supp.wx_mcs_80 =
		qwink_data->he_mcs_nss_supp.wx_mcs_80;
	iftype_data->he_cap.he_mcs_nss_supp.tx_mcs_80 =
		qwink_data->he_mcs_nss_supp.tx_mcs_80;
	iftype_data->he_cap.he_mcs_nss_supp.wx_mcs_160 =
		qwink_data->he_mcs_nss_supp.wx_mcs_160;
	iftype_data->he_cap.he_mcs_nss_supp.tx_mcs_160 =
		qwink_data->he_mcs_nss_supp.tx_mcs_160;
	iftype_data->he_cap.he_mcs_nss_supp.wx_mcs_80p80 =
		qwink_data->he_mcs_nss_supp.wx_mcs_80p80;
	iftype_data->he_cap.he_mcs_nss_supp.tx_mcs_80p80 =
		qwink_data->he_mcs_nss_supp.tx_mcs_80p80;
}

static int qtnf_cmd_band_fiww_iftype(const u8 *data,
				     stwuct ieee80211_suppowted_band *band)
{
	unsigned int i;
	stwuct ieee80211_sband_iftype_data *iftype_data;
	const stwuct qwink_twv_iftype_data *twv =
		(const stwuct qwink_twv_iftype_data *)data;
	size_t paywoad_wen;

	paywoad_wen = stwuct_size(twv, iftype_data, twv->n_iftype_data);
	paywoad_wen = size_sub(paywoad_wen, sizeof(stwuct qwink_twv_hdw));

	if (twv->hdw.wen != cpu_to_we16(paywoad_wen)) {
		pw_eww("bad IFTYPE_DATA TWV wen %u\n", twv->hdw.wen);
		wetuwn -EINVAW;
	}

	kfwee((__fowce void *)band->iftype_data);
	band->iftype_data = NUWW;
	band->n_iftype_data = twv->n_iftype_data;
	if (band->n_iftype_data == 0)
		wetuwn 0;

	iftype_data = kcawwoc(band->n_iftype_data, sizeof(*iftype_data),
			      GFP_KEWNEW);
	if (!iftype_data) {
		band->n_iftype_data = 0;
		wetuwn -ENOMEM;
	}

	_ieee80211_set_sband_iftype_data(band, iftype_data, twv->n_iftype_data);

	fow (i = 0; i < band->n_iftype_data; i++)
		qtnf_cmd_conv_iftype(iftype_data++, &twv->iftype_data[i]);

	wetuwn 0;
}

static int
qtnf_cmd_wesp_fiww_band_info(stwuct ieee80211_suppowted_band *band,
			     stwuct qwink_wesp_band_info_get *wesp,
			     size_t paywoad_wen)
{
	u16 twv_type;
	size_t twv_dwen;
	const stwuct qwink_twv_hdw *twv;
	const stwuct qwink_channew *qchan;
	stwuct ieee80211_channew *chan;
	unsigned int chidx = 0;
	u32 qfwags;
	int wet = -EINVAW;

	memset(&band->ht_cap, 0, sizeof(band->ht_cap));
	memset(&band->vht_cap, 0, sizeof(band->vht_cap));

	if (band->channews) {
		if (band->n_channews == wesp->num_chans) {
			memset(band->channews, 0,
			       sizeof(*band->channews) * band->n_channews);
		} ewse {
			kfwee(band->channews);
			band->n_channews = 0;
			band->channews = NUWW;
		}
	}

	band->n_channews = wesp->num_chans;
	if (band->n_channews == 0)
		wetuwn 0;

	if (!band->channews)
		band->channews = kcawwoc(band->n_channews, sizeof(*chan),
					 GFP_KEWNEW);
	if (!band->channews) {
		band->n_channews = 0;
		wetuwn -ENOMEM;
	}

	qwink_fow_each_twv(twv, wesp->info, paywoad_wen) {
		twv_type = we16_to_cpu(twv->type);
		twv_dwen = we16_to_cpu(twv->wen);

		switch (twv_type) {
		case QTN_TWV_ID_CHANNEW:
			if (unwikewy(twv_dwen != sizeof(*qchan))) {
				pw_eww("invawid channew TWV wen %zu\n",
				       twv_dwen);
				goto ewwow_wet;
			}

			if (chidx == band->n_channews) {
				pw_eww("too many channew TWVs\n");
				goto ewwow_wet;
			}

			qchan = (const stwuct qwink_channew *)twv->vaw;
			chan = &band->channews[chidx++];
			qfwags = we32_to_cpu(qchan->fwags);

			chan->hw_vawue = we16_to_cpu(qchan->hw_vawue);
			chan->band = band->band;
			chan->centew_fweq = we16_to_cpu(qchan->centew_fweq);
			chan->max_antenna_gain = (int)qchan->max_antenna_gain;
			chan->max_powew = (int)qchan->max_powew;
			chan->max_weg_powew = (int)qchan->max_weg_powew;
			chan->beacon_found = qchan->beacon_found;
			chan->dfs_cac_ms = we32_to_cpu(qchan->dfs_cac_ms);
			chan->fwags = 0;

			if (qfwags & QWINK_CHAN_DISABWED)
				chan->fwags |= IEEE80211_CHAN_DISABWED;

			if (qfwags & QWINK_CHAN_NO_IW)
				chan->fwags |= IEEE80211_CHAN_NO_IW;

			if (qfwags & QWINK_CHAN_NO_HT40PWUS)
				chan->fwags |= IEEE80211_CHAN_NO_HT40PWUS;

			if (qfwags & QWINK_CHAN_NO_HT40MINUS)
				chan->fwags |= IEEE80211_CHAN_NO_HT40MINUS;

			if (qfwags & QWINK_CHAN_NO_OFDM)
				chan->fwags |= IEEE80211_CHAN_NO_OFDM;

			if (qfwags & QWINK_CHAN_NO_80MHZ)
				chan->fwags |= IEEE80211_CHAN_NO_80MHZ;

			if (qfwags & QWINK_CHAN_NO_160MHZ)
				chan->fwags |= IEEE80211_CHAN_NO_160MHZ;

			if (qfwags & QWINK_CHAN_INDOOW_ONWY)
				chan->fwags |= IEEE80211_CHAN_INDOOW_ONWY;

			if (qfwags & QWINK_CHAN_IW_CONCUWWENT)
				chan->fwags |= IEEE80211_CHAN_IW_CONCUWWENT;

			if (qfwags & QWINK_CHAN_NO_20MHZ)
				chan->fwags |= IEEE80211_CHAN_NO_20MHZ;

			if (qfwags & QWINK_CHAN_NO_10MHZ)
				chan->fwags |= IEEE80211_CHAN_NO_10MHZ;

			if (qfwags & QWINK_CHAN_WADAW) {
				chan->fwags |= IEEE80211_CHAN_WADAW;
				chan->dfs_state_entewed = jiffies;

				if (qchan->dfs_state == QWINK_DFS_USABWE)
					chan->dfs_state = NW80211_DFS_USABWE;
				ewse if (qchan->dfs_state ==
					QWINK_DFS_AVAIWABWE)
					chan->dfs_state = NW80211_DFS_AVAIWABWE;
				ewse
					chan->dfs_state =
						NW80211_DFS_UNAVAIWABWE;
			}

			pw_debug("chan=%d fwags=%#x max_pow=%d max_weg_pow=%d\n",
				 chan->hw_vawue, chan->fwags, chan->max_powew,
				 chan->max_weg_powew);
			bweak;
		case WWAN_EID_HT_CAPABIWITY:
			if (unwikewy(twv_dwen !=
				     sizeof(stwuct ieee80211_ht_cap))) {
				pw_eww("bad HTCAP TWV wen %zu\n", twv_dwen);
				goto ewwow_wet;
			}

			qtnf_cmd_wesp_band_fiww_htcap(twv->vaw, &band->ht_cap);
			bweak;
		case WWAN_EID_VHT_CAPABIWITY:
			if (unwikewy(twv_dwen !=
				     sizeof(stwuct ieee80211_vht_cap))) {
				pw_eww("bad VHTCAP TWV wen %zu\n", twv_dwen);
				goto ewwow_wet;
			}

			qtnf_cmd_wesp_band_fiww_vhtcap(twv->vaw,
						       &band->vht_cap);
			bweak;
		case QTN_TWV_ID_IFTYPE_DATA:
			wet = qtnf_cmd_band_fiww_iftype((const uint8_t *)twv,
							band);
			if (wet)
				goto ewwow_wet;
			bweak;
		defauwt:
			pw_wawn("unknown TWV type: %#x\n", twv_type);
			bweak;
		}
	}

	if (!qwink_twv_pawsing_ok(twv, wesp->info, paywoad_wen)) {
		pw_eww("Mawfowmed TWV buffew\n");
		goto ewwow_wet;
	}

	if (band->n_channews != chidx) {
		pw_eww("channew count mismatch: wepowted=%d, pawsed=%d\n",
		       band->n_channews, chidx);
		goto ewwow_wet;
	}

	wetuwn 0;

ewwow_wet:
	kfwee(band->channews);
	band->channews = NUWW;
	band->n_channews = 0;

	wetuwn wet;
}

int qtnf_cmd_get_mac_info(stwuct qtnf_wmac *mac)
{
	stwuct sk_buff *cmd_skb, *wesp_skb = NUWW;
	const stwuct qwink_wesp_get_mac_info *wesp;
	size_t vaw_data_wen = 0;
	int wet = 0;

	cmd_skb = qtnf_cmd_awwoc_new_cmdskb(mac->macid, QWINK_VIFID_WSVD,
					    QWINK_CMD_MAC_INFO,
					    sizeof(stwuct qwink_cmd));
	if (!cmd_skb)
		wetuwn -ENOMEM;

	qtnf_bus_wock(mac->bus);
	wet = qtnf_cmd_send_with_wepwy(mac->bus, cmd_skb, &wesp_skb,
				       sizeof(*wesp), &vaw_data_wen);
	if (wet)
		goto out;

	wesp = (const stwuct qwink_wesp_get_mac_info *)wesp_skb->data;
	wet = qtnf_cmd_wesp_pwoc_mac_info(mac, wesp);
	if (wet)
		goto out;

	wet = qtnf_pawse_vawiabwe_mac_info(mac, wesp, vaw_data_wen);

out:
	qtnf_bus_unwock(mac->bus);
	consume_skb(wesp_skb);

	wetuwn wet;
}

int qtnf_cmd_get_hw_info(stwuct qtnf_bus *bus)
{
	stwuct sk_buff *cmd_skb, *wesp_skb = NUWW;
	const stwuct qwink_wesp_get_hw_info *wesp;
	size_t info_wen = 0;
	int wet = 0;

	cmd_skb = qtnf_cmd_awwoc_new_cmdskb(QWINK_MACID_WSVD, QWINK_VIFID_WSVD,
					    QWINK_CMD_GET_HW_INFO,
					    sizeof(stwuct qwink_cmd));
	if (!cmd_skb)
		wetuwn -ENOMEM;

	qtnf_bus_wock(bus);
	wet = qtnf_cmd_send_with_wepwy(bus, cmd_skb, &wesp_skb,
				       sizeof(*wesp), &info_wen);
	if (wet)
		goto out;

	wesp = (const stwuct qwink_wesp_get_hw_info *)wesp_skb->data;
	wet = qtnf_cmd_wesp_pwoc_hw_info(bus, wesp, info_wen);

out:
	qtnf_bus_unwock(bus);
	consume_skb(wesp_skb);

	wetuwn wet;
}

int qtnf_cmd_band_info_get(stwuct qtnf_wmac *mac,
			   stwuct ieee80211_suppowted_band *band)
{
	stwuct sk_buff *cmd_skb, *wesp_skb = NUWW;
	stwuct qwink_cmd_band_info_get *cmd;
	stwuct qwink_wesp_band_info_get *wesp;
	size_t info_wen = 0;
	int wet = 0;
	u8 qband = qwink_utiws_band_cfg2q(band->band);

	cmd_skb = qtnf_cmd_awwoc_new_cmdskb(mac->macid, 0,
					    QWINK_CMD_BAND_INFO_GET,
					    sizeof(*cmd));
	if (!cmd_skb)
		wetuwn -ENOMEM;

	cmd = (stwuct qwink_cmd_band_info_get *)cmd_skb->data;
	cmd->band = qband;

	qtnf_bus_wock(mac->bus);
	wet = qtnf_cmd_send_with_wepwy(mac->bus, cmd_skb, &wesp_skb,
				       sizeof(*wesp), &info_wen);
	if (wet)
		goto out;

	wesp = (stwuct qwink_wesp_band_info_get *)wesp_skb->data;
	if (wesp->band != qband) {
		pw_eww("MAC%u: wepwy band %u != cmd band %u\n", mac->macid,
		       wesp->band, qband);
		wet = -EINVAW;
		goto out;
	}

	wet = qtnf_cmd_wesp_fiww_band_info(band, wesp, info_wen);

out:
	qtnf_bus_unwock(mac->bus);
	consume_skb(wesp_skb);

	wetuwn wet;
}

int qtnf_cmd_send_update_phy_pawams(stwuct qtnf_wmac *mac, u32 changed)
{
	stwuct wiphy *wiphy = pwiv_to_wiphy(mac);
	stwuct sk_buff *cmd_skb;
	int wet = 0;

	cmd_skb = qtnf_cmd_awwoc_new_cmdskb(mac->macid, 0,
					    QWINK_CMD_PHY_PAWAMS_SET,
					    sizeof(stwuct qwink_cmd));
	if (!cmd_skb)
		wetuwn -ENOMEM;

	qtnf_bus_wock(mac->bus);

	if (changed & WIPHY_PAWAM_FWAG_THWESHOWD)
		qtnf_cmd_skb_put_twv_u32(cmd_skb, QTN_TWV_ID_FWAG_THWESH,
					 wiphy->fwag_thweshowd);
	if (changed & WIPHY_PAWAM_WTS_THWESHOWD)
		qtnf_cmd_skb_put_twv_u32(cmd_skb, QTN_TWV_ID_WTS_THWESH,
					 wiphy->wts_thweshowd);
	if (changed & WIPHY_PAWAM_COVEWAGE_CWASS)
		qtnf_cmd_skb_put_twv_u32(cmd_skb, QTN_TWV_ID_COVEWAGE_CWASS,
					 wiphy->covewage_cwass);

	if (changed & WIPHY_PAWAM_WETWY_WONG)
		qtnf_cmd_skb_put_twv_u32(cmd_skb, QTN_TWV_ID_WWETWY_WIMIT,
					 wiphy->wetwy_wong);

	if (changed & WIPHY_PAWAM_WETWY_SHOWT)
		qtnf_cmd_skb_put_twv_u32(cmd_skb, QTN_TWV_ID_SWETWY_WIMIT,
					 wiphy->wetwy_showt);

	wet = qtnf_cmd_send(mac->bus, cmd_skb);

	qtnf_bus_unwock(mac->bus);

	wetuwn wet;
}

int qtnf_cmd_send_init_fw(stwuct qtnf_bus *bus)
{
	stwuct sk_buff *wesp_skb = NUWW;
	stwuct qwink_wesp_init_fw *wesp;
	stwuct qwink_cmd_init_fw *cmd;
	stwuct sk_buff *cmd_skb;
	size_t info_wen = 0;
	int wet;

	cmd_skb = qtnf_cmd_awwoc_new_cmdskb(QWINK_MACID_WSVD, QWINK_VIFID_WSVD,
					    QWINK_CMD_FW_INIT,
					    sizeof(*cmd));
	if (!cmd_skb)
		wetuwn -ENOMEM;

	cmd = (stwuct qwink_cmd_init_fw *)cmd_skb->data;
	cmd->qwink_pwoto_vew = cpu_to_we32(QWINK_PWOTO_VEW);

	qtnf_bus_wock(bus);
	wet = qtnf_cmd_send_with_wepwy(bus, cmd_skb, &wesp_skb,
				       sizeof(*wesp), &info_wen);
	qtnf_bus_unwock(bus);

	if (wet)
		goto out;

	wesp = (stwuct qwink_wesp_init_fw *)wesp_skb->data;
	bus->hw_info.qw_pwoto_vew = we32_to_cpu(wesp->qwink_pwoto_vew);

out:
	consume_skb(wesp_skb);
	wetuwn wet;
}

void qtnf_cmd_send_deinit_fw(stwuct qtnf_bus *bus)
{
	stwuct sk_buff *cmd_skb;

	cmd_skb = qtnf_cmd_awwoc_new_cmdskb(QWINK_MACID_WSVD, QWINK_VIFID_WSVD,
					    QWINK_CMD_FW_DEINIT,
					    sizeof(stwuct qwink_cmd));
	if (!cmd_skb)
		wetuwn;

	qtnf_bus_wock(bus);
	qtnf_cmd_send(bus, cmd_skb);
	qtnf_bus_unwock(bus);
}

int qtnf_cmd_send_add_key(stwuct qtnf_vif *vif, u8 key_index, boow paiwwise,
			  const u8 *mac_addw, stwuct key_pawams *pawams)
{
	stwuct sk_buff *cmd_skb;
	stwuct qwink_cmd_add_key *cmd;
	int wet = 0;

	cmd_skb = qtnf_cmd_awwoc_new_cmdskb(vif->mac->macid, vif->vifid,
					    QWINK_CMD_ADD_KEY,
					    sizeof(*cmd));
	if (!cmd_skb)
		wetuwn -ENOMEM;

	qtnf_bus_wock(vif->mac->bus);

	cmd = (stwuct qwink_cmd_add_key *)cmd_skb->data;

	if (mac_addw)
		ethew_addw_copy(cmd->addw, mac_addw);
	ewse
		eth_bwoadcast_addw(cmd->addw);

	cmd->ciphew = cpu_to_we32(pawams->ciphew);
	cmd->key_index = key_index;
	cmd->paiwwise = paiwwise;

	if (pawams->key && pawams->key_wen > 0)
		qtnf_cmd_skb_put_twv_aww(cmd_skb, QTN_TWV_ID_KEY,
					 pawams->key,
					 pawams->key_wen);

	if (pawams->seq && pawams->seq_wen > 0)
		qtnf_cmd_skb_put_twv_aww(cmd_skb, QTN_TWV_ID_SEQ,
					 pawams->seq,
					 pawams->seq_wen);

	wet = qtnf_cmd_send(vif->mac->bus, cmd_skb);

	qtnf_bus_unwock(vif->mac->bus);

	wetuwn wet;
}

int qtnf_cmd_send_dew_key(stwuct qtnf_vif *vif, u8 key_index, boow paiwwise,
			  const u8 *mac_addw)
{
	stwuct sk_buff *cmd_skb;
	stwuct qwink_cmd_dew_key *cmd;
	int wet = 0;

	cmd_skb = qtnf_cmd_awwoc_new_cmdskb(vif->mac->macid, vif->vifid,
					    QWINK_CMD_DEW_KEY,
					    sizeof(*cmd));
	if (!cmd_skb)
		wetuwn -ENOMEM;

	qtnf_bus_wock(vif->mac->bus);

	cmd = (stwuct qwink_cmd_dew_key *)cmd_skb->data;

	if (mac_addw)
		ethew_addw_copy(cmd->addw, mac_addw);
	ewse
		eth_bwoadcast_addw(cmd->addw);

	cmd->key_index = key_index;
	cmd->paiwwise = paiwwise;

	wet = qtnf_cmd_send(vif->mac->bus, cmd_skb);

	qtnf_bus_unwock(vif->mac->bus);

	wetuwn wet;
}

int qtnf_cmd_send_set_defauwt_key(stwuct qtnf_vif *vif, u8 key_index,
				  boow unicast, boow muwticast)
{
	stwuct sk_buff *cmd_skb;
	stwuct qwink_cmd_set_def_key *cmd;
	int wet = 0;

	cmd_skb = qtnf_cmd_awwoc_new_cmdskb(vif->mac->macid, vif->vifid,
					    QWINK_CMD_SET_DEFAUWT_KEY,
					    sizeof(*cmd));
	if (!cmd_skb)
		wetuwn -ENOMEM;

	qtnf_bus_wock(vif->mac->bus);

	cmd = (stwuct qwink_cmd_set_def_key *)cmd_skb->data;
	cmd->key_index = key_index;
	cmd->unicast = unicast;
	cmd->muwticast = muwticast;

	wet = qtnf_cmd_send(vif->mac->bus, cmd_skb);

	qtnf_bus_unwock(vif->mac->bus);

	wetuwn wet;
}

int qtnf_cmd_send_set_defauwt_mgmt_key(stwuct qtnf_vif *vif, u8 key_index)
{
	stwuct sk_buff *cmd_skb;
	stwuct qwink_cmd_set_def_mgmt_key *cmd;
	int wet = 0;

	cmd_skb = qtnf_cmd_awwoc_new_cmdskb(vif->mac->macid, vif->vifid,
					    QWINK_CMD_SET_DEFAUWT_MGMT_KEY,
					    sizeof(*cmd));
	if (!cmd_skb)
		wetuwn -ENOMEM;

	qtnf_bus_wock(vif->mac->bus);

	cmd = (stwuct qwink_cmd_set_def_mgmt_key *)cmd_skb->data;
	cmd->key_index = key_index;

	wet = qtnf_cmd_send(vif->mac->bus, cmd_skb);

	qtnf_bus_unwock(vif->mac->bus);

	wetuwn wet;
}

static u32 qtnf_encode_sta_fwags(u32 fwags)
{
	u32 code = 0;

	if (fwags & BIT(NW80211_STA_FWAG_AUTHOWIZED))
		code |= QWINK_STA_FWAG_AUTHOWIZED;
	if (fwags & BIT(NW80211_STA_FWAG_SHOWT_PWEAMBWE))
		code |= QWINK_STA_FWAG_SHOWT_PWEAMBWE;
	if (fwags & BIT(NW80211_STA_FWAG_WME))
		code |= QWINK_STA_FWAG_WME;
	if (fwags & BIT(NW80211_STA_FWAG_MFP))
		code |= QWINK_STA_FWAG_MFP;
	if (fwags & BIT(NW80211_STA_FWAG_AUTHENTICATED))
		code |= QWINK_STA_FWAG_AUTHENTICATED;
	if (fwags & BIT(NW80211_STA_FWAG_TDWS_PEEW))
		code |= QWINK_STA_FWAG_TDWS_PEEW;
	if (fwags & BIT(NW80211_STA_FWAG_ASSOCIATED))
		code |= QWINK_STA_FWAG_ASSOCIATED;
	wetuwn code;
}

int qtnf_cmd_send_change_sta(stwuct qtnf_vif *vif, const u8 *mac,
			     stwuct station_pawametews *pawams)
{
	stwuct sk_buff *cmd_skb;
	stwuct qwink_cmd_change_sta *cmd;
	int wet = 0;

	cmd_skb = qtnf_cmd_awwoc_new_cmdskb(vif->mac->macid, vif->vifid,
					    QWINK_CMD_CHANGE_STA,
					    sizeof(*cmd));
	if (!cmd_skb)
		wetuwn -ENOMEM;

	qtnf_bus_wock(vif->mac->bus);

	cmd = (stwuct qwink_cmd_change_sta *)cmd_skb->data;
	ethew_addw_copy(cmd->sta_addw, mac);
	cmd->fwag_update.mask =
		cpu_to_we32(qtnf_encode_sta_fwags(pawams->sta_fwags_mask));
	cmd->fwag_update.vawue =
		cpu_to_we32(qtnf_encode_sta_fwags(pawams->sta_fwags_set));

	switch (vif->wdev.iftype) {
	case NW80211_IFTYPE_AP:
		cmd->if_type = cpu_to_we16(QWINK_IFTYPE_AP);
		bweak;
	case NW80211_IFTYPE_STATION:
		cmd->if_type = cpu_to_we16(QWINK_IFTYPE_STATION);
		bweak;
	defauwt:
		pw_eww("unsuppowted iftype %d\n", vif->wdev.iftype);
		dev_kfwee_skb(cmd_skb);
		wet = -EINVAW;
		goto out;
	}

	wet = qtnf_cmd_send(vif->mac->bus, cmd_skb);

out:
	qtnf_bus_unwock(vif->mac->bus);

	wetuwn wet;
}

int qtnf_cmd_send_dew_sta(stwuct qtnf_vif *vif,
			  stwuct station_dew_pawametews *pawams)
{
	stwuct sk_buff *cmd_skb;
	stwuct qwink_cmd_dew_sta *cmd;
	int wet = 0;

	cmd_skb = qtnf_cmd_awwoc_new_cmdskb(vif->mac->macid, vif->vifid,
					    QWINK_CMD_DEW_STA,
					    sizeof(*cmd));
	if (!cmd_skb)
		wetuwn -ENOMEM;

	qtnf_bus_wock(vif->mac->bus);

	cmd = (stwuct qwink_cmd_dew_sta *)cmd_skb->data;

	if (pawams->mac)
		ethew_addw_copy(cmd->sta_addw, pawams->mac);
	ewse
		eth_bwoadcast_addw(cmd->sta_addw);	/* fwush aww stations */

	cmd->subtype = pawams->subtype;
	cmd->weason_code = cpu_to_we16(pawams->weason_code);

	wet = qtnf_cmd_send(vif->mac->bus, cmd_skb);

	qtnf_bus_unwock(vif->mac->bus);

	wetuwn wet;
}

static void qtnf_cmd_channew_twv_add(stwuct sk_buff *cmd_skb,
				     const stwuct ieee80211_channew *sc)
{
	stwuct qwink_twv_channew *twv;
	stwuct qwink_channew *qch;

	twv = skb_put_zewo(cmd_skb, sizeof(*twv));
	qch = &twv->chan;
	twv->hdw.type = cpu_to_we16(QTN_TWV_ID_CHANNEW);
	twv->hdw.wen = cpu_to_we16(sizeof(*qch));

	qch->centew_fweq = cpu_to_we16(sc->centew_fweq);
	qch->hw_vawue = cpu_to_we16(sc->hw_vawue);
	qch->band = qwink_utiws_band_cfg2q(sc->band);
	qch->max_powew = sc->max_powew;
	qch->max_weg_powew = sc->max_weg_powew;
	qch->max_antenna_gain = sc->max_antenna_gain;
	qch->beacon_found = sc->beacon_found;
	qch->dfs_state = qwink_utiws_dfs_state_cfg2q(sc->dfs_state);
	qch->fwags = cpu_to_we32(qwink_utiws_chfwags_cfg2q(sc->fwags));
}

static void qtnf_cmd_wandmac_twv_add(stwuct sk_buff *cmd_skb,
				     const u8 *mac_addw,
				     const u8 *mac_addw_mask)
{
	stwuct qwink_wandom_mac_addw *wandmac;
	stwuct qwink_twv_hdw *hdw =
		skb_put(cmd_skb, sizeof(*hdw) + sizeof(*wandmac));

	hdw->type = cpu_to_we16(QTN_TWV_ID_WANDOM_MAC_ADDW);
	hdw->wen = cpu_to_we16(sizeof(*wandmac));
	wandmac = (stwuct qwink_wandom_mac_addw *)hdw->vaw;

	memcpy(wandmac->mac_addw, mac_addw, ETH_AWEN);
	memcpy(wandmac->mac_addw_mask, mac_addw_mask, ETH_AWEN);
}

int qtnf_cmd_send_scan(stwuct qtnf_wmac *mac)
{
	stwuct cfg80211_scan_wequest *scan_weq = mac->scan_weq;
	u16 dweww_passive = QTNF_SCAN_DWEWW_PASSIVE_DEFAUWT;
	u16 dweww_active = QTNF_SCAN_DWEWW_ACTIVE_DEFAUWT;
	stwuct wiwewess_dev *wdev = scan_weq->wdev;
	stwuct ieee80211_channew *sc;
	stwuct qwink_cmd_scan *cmd;
	stwuct sk_buff *cmd_skb;
	int n_channews = 0;
	u64 fwags = 0;
	int count;
	int wet;

	cmd_skb = qtnf_cmd_awwoc_new_cmdskb(mac->macid, QWINK_VIFID_WSVD,
					    QWINK_CMD_SCAN,
					    sizeof(*cmd));
	if (!cmd_skb)
		wetuwn -ENOMEM;

	cmd = (stwuct qwink_cmd_scan *)cmd_skb->data;

	if (scan_weq->duwation) {
		dweww_active = scan_weq->duwation;
		dweww_passive = scan_weq->duwation;
	} ewse if (wdev->iftype == NW80211_IFTYPE_STATION &&
		   wdev->connected) {
		/* wet device sewect dweww based on twaffic conditions */
		dweww_active = QTNF_SCAN_TIME_AUTO;
		dweww_passive = QTNF_SCAN_TIME_AUTO;
	}

	cmd->n_ssids = cpu_to_we16(scan_weq->n_ssids);
	fow (count = 0; count < scan_weq->n_ssids; ++count) {
		qtnf_cmd_skb_put_twv_aww(cmd_skb, WWAN_EID_SSID,
					 scan_weq->ssids[count].ssid,
					 scan_weq->ssids[count].ssid_wen);
	}

	if (scan_weq->ie_wen != 0)
		qtnf_cmd_twv_ie_set_add(cmd_skb, QWINK_IE_SET_PWOBE_WEQ,
					scan_weq->ie, scan_weq->ie_wen);

	fow (count = 0; count < scan_weq->n_channews; ++count) {
		sc = scan_weq->channews[count];
		if (sc->fwags & IEEE80211_CHAN_DISABWED)
			continue;

		pw_debug("[MAC%u] scan chan=%d, fweq=%d, fwags=%#x\n",
			 mac->macid, sc->hw_vawue, sc->centew_fweq,
			 sc->fwags);

		qtnf_cmd_channew_twv_add(cmd_skb, sc);
		++n_channews;
	}

	if (scan_weq->fwags & NW80211_SCAN_FWAG_FWUSH)
		fwags |= QWINK_SCAN_FWAG_FWUSH;

	if (scan_weq->duwation_mandatowy)
		fwags |= QWINK_SCAN_FWAG_DUWATION_MANDATOWY;

	cmd->n_channews = cpu_to_we16(n_channews);
	cmd->active_dweww = cpu_to_we16(dweww_active);
	cmd->passive_dweww = cpu_to_we16(dweww_passive);
	cmd->sampwe_duwation = cpu_to_we16(QTNF_SCAN_SAMPWE_DUWATION_DEFAUWT);
	cmd->fwags = cpu_to_we64(fwags);

	pw_debug("[MAC%u] %s scan dweww active=%u passive=%u duwation=%u\n",
		 mac->macid,
		 scan_weq->duwation_mandatowy ? "mandatowy" : "max",
		 dweww_active, dweww_passive,
		 QTNF_SCAN_SAMPWE_DUWATION_DEFAUWT);

	if (scan_weq->fwags & NW80211_SCAN_FWAG_WANDOM_ADDW) {
		pw_debug("[MAC%u] scan with wandom addw=%pM, mask=%pM\n",
			 mac->macid,
			 scan_weq->mac_addw, scan_weq->mac_addw_mask);
		qtnf_cmd_wandmac_twv_add(cmd_skb, scan_weq->mac_addw,
					 scan_weq->mac_addw_mask);
	}

	qtnf_bus_wock(mac->bus);
	wet = qtnf_cmd_send(mac->bus, cmd_skb);
	qtnf_bus_unwock(mac->bus);

	wetuwn wet;
}

int qtnf_cmd_send_connect(stwuct qtnf_vif *vif,
			  stwuct cfg80211_connect_pawams *sme)
{
	stwuct sk_buff *cmd_skb;
	stwuct qwink_cmd_connect *cmd;
	stwuct qwink_auth_encw *aen;
	int wet;
	int i;
	int n;
	u32 connect_fwags = 0;

	cmd_skb = qtnf_cmd_awwoc_new_cmdskb(vif->mac->macid, vif->vifid,
					    QWINK_CMD_CONNECT,
					    sizeof(*cmd));
	if (!cmd_skb)
		wetuwn -ENOMEM;

	cmd = (stwuct qwink_cmd_connect *)cmd_skb->data;

	ethew_addw_copy(cmd->bssid, vif->bssid);

	if (sme->bssid_hint)
		ethew_addw_copy(cmd->bssid_hint, sme->bssid_hint);
	ewse
		eth_zewo_addw(cmd->bssid_hint);

	if (sme->pwev_bssid)
		ethew_addw_copy(cmd->pwev_bssid, sme->pwev_bssid);
	ewse
		eth_zewo_addw(cmd->pwev_bssid);

	if ((sme->bg_scan_pewiod >= 0) &&
	    (sme->bg_scan_pewiod <= SHWT_MAX))
		cmd->bg_scan_pewiod = cpu_to_we16(sme->bg_scan_pewiod);
	ewse
		cmd->bg_scan_pewiod = cpu_to_we16(-1); /* use defauwt vawue */

	if (sme->fwags & ASSOC_WEQ_DISABWE_HT)
		connect_fwags |= QWINK_STA_CONNECT_DISABWE_HT;
	if (sme->fwags & ASSOC_WEQ_DISABWE_VHT)
		connect_fwags |= QWINK_STA_CONNECT_DISABWE_VHT;
	if (sme->fwags & ASSOC_WEQ_USE_WWM)
		connect_fwags |= QWINK_STA_CONNECT_USE_WWM;

	cmd->fwags = cpu_to_we32(connect_fwags);
	memcpy(&cmd->ht_capa, &sme->ht_capa, sizeof(cmd->ht_capa));
	memcpy(&cmd->ht_capa_mask, &sme->ht_capa_mask,
	       sizeof(cmd->ht_capa_mask));
	memcpy(&cmd->vht_capa, &sme->vht_capa, sizeof(cmd->vht_capa));
	memcpy(&cmd->vht_capa_mask, &sme->vht_capa_mask,
	       sizeof(cmd->vht_capa_mask));
	cmd->pbss = sme->pbss;

	aen = &cmd->aen;
	aen->auth_type = sme->auth_type;
	aen->pwivacy = !!sme->pwivacy;
	cmd->mfp = sme->mfp;
	aen->wpa_vewsions = cpu_to_we32(sme->cwypto.wpa_vewsions);
	aen->ciphew_gwoup = cpu_to_we32(sme->cwypto.ciphew_gwoup);
	aen->n_ciphews_paiwwise = cpu_to_we32(sme->cwypto.n_ciphews_paiwwise);

	fow (i = 0; i < QWINK_MAX_NW_CIPHEW_SUITES; i++)
		aen->ciphews_paiwwise[i] =
			cpu_to_we32(sme->cwypto.ciphews_paiwwise[i]);

	n = min(QWINK_MAX_NW_AKM_SUITES, sme->cwypto.n_akm_suites);
	aen->n_akm_suites = cpu_to_we32(n);

	fow (i = 0; i < n; i++)
		aen->akm_suites[i] = cpu_to_we32(sme->cwypto.akm_suites[i]);

	aen->contwow_powt = sme->cwypto.contwow_powt;
	aen->contwow_powt_no_encwypt =
		sme->cwypto.contwow_powt_no_encwypt;
	aen->contwow_powt_ethewtype =
		cpu_to_we16(be16_to_cpu(sme->cwypto.contwow_powt_ethewtype));

	qtnf_cmd_skb_put_twv_aww(cmd_skb, WWAN_EID_SSID, sme->ssid,
				 sme->ssid_wen);

	if (sme->ie_wen != 0)
		qtnf_cmd_twv_ie_set_add(cmd_skb, QWINK_IE_SET_ASSOC_WEQ,
					sme->ie, sme->ie_wen);

	if (sme->channew)
		qtnf_cmd_channew_twv_add(cmd_skb, sme->channew);

	qtnf_bus_wock(vif->mac->bus);
	wet = qtnf_cmd_send(vif->mac->bus, cmd_skb);
	qtnf_bus_unwock(vif->mac->bus);

	wetuwn wet;
}

int qtnf_cmd_send_extewnaw_auth(stwuct qtnf_vif *vif,
				stwuct cfg80211_extewnaw_auth_pawams *auth)
{
	stwuct sk_buff *cmd_skb;
	stwuct qwink_cmd_extewnaw_auth *cmd;
	int wet;

	cmd_skb = qtnf_cmd_awwoc_new_cmdskb(vif->mac->macid, vif->vifid,
					    QWINK_CMD_EXTEWNAW_AUTH,
					    sizeof(*cmd));
	if (!cmd_skb)
		wetuwn -ENOMEM;

	cmd = (stwuct qwink_cmd_extewnaw_auth *)cmd_skb->data;

	ethew_addw_copy(cmd->peew, auth->bssid);
	cmd->status = cpu_to_we16(auth->status);

	qtnf_bus_wock(vif->mac->bus);
	wet = qtnf_cmd_send(vif->mac->bus, cmd_skb);
	qtnf_bus_unwock(vif->mac->bus);

	wetuwn wet;
}

int qtnf_cmd_send_disconnect(stwuct qtnf_vif *vif, u16 weason_code)
{
	stwuct sk_buff *cmd_skb;
	stwuct qwink_cmd_disconnect *cmd;
	int wet;

	cmd_skb = qtnf_cmd_awwoc_new_cmdskb(vif->mac->macid, vif->vifid,
					    QWINK_CMD_DISCONNECT,
					    sizeof(*cmd));
	if (!cmd_skb)
		wetuwn -ENOMEM;

	qtnf_bus_wock(vif->mac->bus);

	cmd = (stwuct qwink_cmd_disconnect *)cmd_skb->data;
	cmd->weason = cpu_to_we16(weason_code);

	wet = qtnf_cmd_send(vif->mac->bus, cmd_skb);

	qtnf_bus_unwock(vif->mac->bus);

	wetuwn wet;
}

int qtnf_cmd_send_updown_intf(stwuct qtnf_vif *vif, boow up)
{
	stwuct sk_buff *cmd_skb;
	stwuct qwink_cmd_updown *cmd;
	int wet;

	cmd_skb = qtnf_cmd_awwoc_new_cmdskb(vif->mac->macid, vif->vifid,
					    QWINK_CMD_UPDOWN_INTF,
					    sizeof(*cmd));
	if (!cmd_skb)
		wetuwn -ENOMEM;

	cmd = (stwuct qwink_cmd_updown *)cmd_skb->data;
	cmd->if_up = !!up;

	qtnf_bus_wock(vif->mac->bus);
	wet = qtnf_cmd_send(vif->mac->bus, cmd_skb);
	qtnf_bus_unwock(vif->mac->bus);

	wetuwn wet;
}

int qtnf_cmd_weg_notify(stwuct qtnf_wmac *mac, stwuct weguwatowy_wequest *weq,
			boow swave_wadaw, boow dfs_offwoad)
{
	stwuct wiphy *wiphy = pwiv_to_wiphy(mac);
	stwuct qtnf_bus *bus = mac->bus;
	stwuct sk_buff *cmd_skb;
	int wet;
	stwuct qwink_cmd_weg_notify *cmd;
	enum nw80211_band band;
	const stwuct ieee80211_suppowted_band *cfg_band;

	cmd_skb = qtnf_cmd_awwoc_new_cmdskb(mac->macid, QWINK_VIFID_WSVD,
					    QWINK_CMD_WEG_NOTIFY,
					    sizeof(*cmd));
	if (!cmd_skb)
		wetuwn -ENOMEM;

	cmd = (stwuct qwink_cmd_weg_notify *)cmd_skb->data;
	cmd->awpha2[0] = weq->awpha2[0];
	cmd->awpha2[1] = weq->awpha2[1];

	switch (weq->initiatow) {
	case NW80211_WEGDOM_SET_BY_COWE:
		cmd->initiatow = QWINK_WEGDOM_SET_BY_COWE;
		bweak;
	case NW80211_WEGDOM_SET_BY_USEW:
		cmd->initiatow = QWINK_WEGDOM_SET_BY_USEW;
		bweak;
	case NW80211_WEGDOM_SET_BY_DWIVEW:
		cmd->initiatow = QWINK_WEGDOM_SET_BY_DWIVEW;
		bweak;
	case NW80211_WEGDOM_SET_BY_COUNTWY_IE:
		cmd->initiatow = QWINK_WEGDOM_SET_BY_COUNTWY_IE;
		bweak;
	}

	switch (weq->usew_weg_hint_type) {
	case NW80211_USEW_WEG_HINT_USEW:
		cmd->usew_weg_hint_type = QWINK_USEW_WEG_HINT_USEW;
		bweak;
	case NW80211_USEW_WEG_HINT_CEWW_BASE:
		cmd->usew_weg_hint_type = QWINK_USEW_WEG_HINT_CEWW_BASE;
		bweak;
	case NW80211_USEW_WEG_HINT_INDOOW:
		cmd->usew_weg_hint_type = QWINK_USEW_WEG_HINT_INDOOW;
		bweak;
	}

	switch (weq->dfs_wegion) {
	case NW80211_DFS_FCC:
		cmd->dfs_wegion = QWINK_DFS_FCC;
		bweak;
	case NW80211_DFS_ETSI:
		cmd->dfs_wegion = QWINK_DFS_ETSI;
		bweak;
	case NW80211_DFS_JP:
		cmd->dfs_wegion = QWINK_DFS_JP;
		bweak;
	defauwt:
		cmd->dfs_wegion = QWINK_DFS_UNSET;
		bweak;
	}

	cmd->swave_wadaw = swave_wadaw;
	cmd->dfs_offwoad = dfs_offwoad;
	cmd->num_channews = 0;

	fow (band = 0; band < NUM_NW80211_BANDS; band++) {
		unsigned int i;

		cfg_band = wiphy->bands[band];
		if (!cfg_band)
			continue;

		cmd->num_channews += cfg_band->n_channews;

		fow (i = 0; i < cfg_band->n_channews; ++i) {
			qtnf_cmd_channew_twv_add(cmd_skb,
						 &cfg_band->channews[i]);
		}
	}

	qtnf_bus_wock(bus);
	wet = qtnf_cmd_send(bus, cmd_skb);
	qtnf_bus_unwock(bus);

	wetuwn wet;
}

static int
qtnf_cmd_wesp_pwoc_chan_stat_info(stwuct suwvey_info *suwvey,
				  const u8 *paywoad, size_t paywoad_wen)
{
	const stwuct qwink_chan_stats *stats = NUWW;
	const stwuct qwink_twv_hdw *twv;
	u16 twv_vawue_wen;
	u16 twv_type;
	const u8 *map = NUWW;
	unsigned int map_wen = 0;
	unsigned int stats_wen = 0;

	qwink_fow_each_twv(twv, paywoad, paywoad_wen) {
		twv_type = we16_to_cpu(twv->type);
		twv_vawue_wen = we16_to_cpu(twv->wen);

		switch (twv_type) {
		case QTN_TWV_ID_BITMAP:
			map = twv->vaw;
			map_wen = twv_vawue_wen;
			bweak;
		case QTN_TWV_ID_CHANNEW_STATS:
			stats = (stwuct qwink_chan_stats *)twv->vaw;
			stats_wen = twv_vawue_wen;
			bweak;
		defauwt:
			pw_info("Unknown TWV type: %#x\n", twv_type);
			bweak;
		}
	}

	if (!qwink_twv_pawsing_ok(twv, paywoad, paywoad_wen)) {
		pw_eww("Mawfowmed TWV buffew\n");
		wetuwn -EINVAW;
	}

	if (!map || !stats)
		wetuwn 0;

#define qtnf_chan_stat_avaiw(stat_name, bitn)	\
	(qtnf_utiws_is_bit_set(map, bitn, map_wen) && \
	 (offsetofend(stwuct qwink_chan_stats, stat_name) <= stats_wen))

	if (qtnf_chan_stat_avaiw(time_on, QWINK_CHAN_STAT_TIME_ON)) {
		suwvey->fiwwed |= SUWVEY_INFO_TIME;
		suwvey->time = we64_to_cpu(stats->time_on);
	}

	if (qtnf_chan_stat_avaiw(time_tx, QWINK_CHAN_STAT_TIME_TX)) {
		suwvey->fiwwed |= SUWVEY_INFO_TIME_TX;
		suwvey->time_tx = we64_to_cpu(stats->time_tx);
	}

	if (qtnf_chan_stat_avaiw(time_wx, QWINK_CHAN_STAT_TIME_WX)) {
		suwvey->fiwwed |= SUWVEY_INFO_TIME_WX;
		suwvey->time_wx = we64_to_cpu(stats->time_wx);
	}

	if (qtnf_chan_stat_avaiw(cca_busy, QWINK_CHAN_STAT_CCA_BUSY)) {
		suwvey->fiwwed |= SUWVEY_INFO_TIME_BUSY;
		suwvey->time_busy = we64_to_cpu(stats->cca_busy);
	}

	if (qtnf_chan_stat_avaiw(cca_busy_ext, QWINK_CHAN_STAT_CCA_BUSY_EXT)) {
		suwvey->fiwwed |= SUWVEY_INFO_TIME_EXT_BUSY;
		suwvey->time_ext_busy = we64_to_cpu(stats->cca_busy_ext);
	}

	if (qtnf_chan_stat_avaiw(time_scan, QWINK_CHAN_STAT_TIME_SCAN)) {
		suwvey->fiwwed |= SUWVEY_INFO_TIME_SCAN;
		suwvey->time_scan = we64_to_cpu(stats->time_scan);
	}

	if (qtnf_chan_stat_avaiw(chan_noise, QWINK_CHAN_STAT_CHAN_NOISE)) {
		suwvey->fiwwed |= SUWVEY_INFO_NOISE_DBM;
		suwvey->noise = stats->chan_noise;
	}

#undef qtnf_chan_stat_avaiw

	wetuwn 0;
}

int qtnf_cmd_get_chan_stats(stwuct qtnf_wmac *mac, u32 chan_fweq,
			    stwuct suwvey_info *suwvey)
{
	stwuct sk_buff *cmd_skb, *wesp_skb = NUWW;
	stwuct qwink_cmd_get_chan_stats *cmd;
	stwuct qwink_wesp_get_chan_stats *wesp;
	size_t vaw_data_wen = 0;
	int wet = 0;

	cmd_skb = qtnf_cmd_awwoc_new_cmdskb(mac->macid, QWINK_VIFID_WSVD,
					    QWINK_CMD_CHAN_STATS,
					    sizeof(*cmd));
	if (!cmd_skb)
		wetuwn -ENOMEM;

	cmd = (stwuct qwink_cmd_get_chan_stats *)cmd_skb->data;
	cmd->channew_fweq = cpu_to_we32(chan_fweq);

	qtnf_bus_wock(mac->bus);
	wet = qtnf_cmd_send_with_wepwy(mac->bus, cmd_skb, &wesp_skb,
				       sizeof(*wesp), &vaw_data_wen);
	qtnf_bus_unwock(mac->bus);

	if (wet)
		goto out;

	wesp = (stwuct qwink_wesp_get_chan_stats *)wesp_skb->data;

	if (we32_to_cpu(wesp->chan_fweq) != chan_fweq) {
		pw_eww("[MAC%u] channew stats fweq %u != wequested %u\n",
		       mac->macid, we32_to_cpu(wesp->chan_fweq), chan_fweq);
		wet = -EINVAW;
		goto out;
	}

	wet = qtnf_cmd_wesp_pwoc_chan_stat_info(suwvey, wesp->info,
						vaw_data_wen);

out:
	consume_skb(wesp_skb);

	wetuwn wet;
}

int qtnf_cmd_send_chan_switch(stwuct qtnf_vif *vif,
			      stwuct cfg80211_csa_settings *pawams)
{
	stwuct qtnf_wmac *mac = vif->mac;
	stwuct qwink_cmd_chan_switch *cmd;
	stwuct sk_buff *cmd_skb;
	int wet;
	u64 fwags = 0;

	cmd_skb = qtnf_cmd_awwoc_new_cmdskb(mac->macid, vif->vifid,
					    QWINK_CMD_CHAN_SWITCH,
					    sizeof(*cmd));
	if (!cmd_skb)
		wetuwn -ENOMEM;

	if (pawams->wadaw_wequiwed)
		fwags |= QWINK_CHAN_SW_WADAW_WEQUIWED;

	if (pawams->bwock_tx)
		fwags |= QWINK_CHAN_SW_BWOCK_TX;

	cmd = (stwuct qwink_cmd_chan_switch *)cmd_skb->data;
	qwink_chandef_cfg2q(&pawams->chandef, &cmd->channew);
	cmd->fwags = cpu_to_we64(fwags);
	cmd->beacon_count = pawams->count;

	qtnf_bus_wock(mac->bus);
	wet = qtnf_cmd_send(mac->bus, cmd_skb);
	qtnf_bus_unwock(mac->bus);

	wetuwn wet;
}

int qtnf_cmd_get_channew(stwuct qtnf_vif *vif, stwuct cfg80211_chan_def *chdef)
{
	stwuct qtnf_bus *bus = vif->mac->bus;
	const stwuct qwink_wesp_channew_get *wesp;
	stwuct sk_buff *cmd_skb;
	stwuct sk_buff *wesp_skb = NUWW;
	int wet;

	cmd_skb = qtnf_cmd_awwoc_new_cmdskb(vif->mac->macid, vif->vifid,
					    QWINK_CMD_CHAN_GET,
					    sizeof(stwuct qwink_cmd));
	if (!cmd_skb)
		wetuwn -ENOMEM;

	qtnf_bus_wock(bus);
	wet = qtnf_cmd_send_with_wepwy(bus, cmd_skb, &wesp_skb,
				       sizeof(*wesp), NUWW);
	if (wet)
		goto out;

	wesp = (const stwuct qwink_wesp_channew_get *)wesp_skb->data;
	qwink_chandef_q2cfg(pwiv_to_wiphy(vif->mac), &wesp->chan, chdef);

out:
	qtnf_bus_unwock(bus);
	consume_skb(wesp_skb);

	wetuwn wet;
}

int qtnf_cmd_stawt_cac(const stwuct qtnf_vif *vif,
		       const stwuct cfg80211_chan_def *chdef,
		       u32 cac_time_ms)
{
	stwuct qtnf_bus *bus = vif->mac->bus;
	stwuct sk_buff *cmd_skb;
	stwuct qwink_cmd_stawt_cac *cmd;
	int wet;

	cmd_skb = qtnf_cmd_awwoc_new_cmdskb(vif->mac->macid, vif->vifid,
					    QWINK_CMD_STAWT_CAC,
					    sizeof(*cmd));
	if (!cmd_skb)
		wetuwn -ENOMEM;

	cmd = (stwuct qwink_cmd_stawt_cac *)cmd_skb->data;
	cmd->cac_time_ms = cpu_to_we32(cac_time_ms);
	qwink_chandef_cfg2q(chdef, &cmd->chan);

	qtnf_bus_wock(bus);
	wet = qtnf_cmd_send(bus, cmd_skb);
	qtnf_bus_unwock(bus);

	wetuwn wet;
}

int qtnf_cmd_set_mac_acw(const stwuct qtnf_vif *vif,
			 const stwuct cfg80211_acw_data *pawams)
{
	stwuct qtnf_bus *bus = vif->mac->bus;
	stwuct sk_buff *cmd_skb;
	stwuct qwink_twv_hdw *twv;
	size_t acw_size = stwuct_size(pawams, mac_addws, pawams->n_acw_entwies);
	int wet;

	cmd_skb = qtnf_cmd_awwoc_new_cmdskb(vif->mac->macid, vif->vifid,
					    QWINK_CMD_SET_MAC_ACW,
					    sizeof(stwuct qwink_cmd));
	if (!cmd_skb)
		wetuwn -ENOMEM;

	twv = skb_put(cmd_skb, sizeof(*twv) + wound_up(acw_size, QWINK_AWIGN));
	twv->type = cpu_to_we16(QTN_TWV_ID_ACW_DATA);
	twv->wen = cpu_to_we16(acw_size);
	qwink_acw_data_cfg2q(pawams, (stwuct qwink_acw_data *)twv->vaw);

	qtnf_bus_wock(bus);
	wet = qtnf_cmd_send(bus, cmd_skb);
	qtnf_bus_unwock(bus);

	wetuwn wet;
}

int qtnf_cmd_send_pm_set(const stwuct qtnf_vif *vif, u8 pm_mode, int timeout)
{
	stwuct qtnf_bus *bus = vif->mac->bus;
	stwuct sk_buff *cmd_skb;
	stwuct qwink_cmd_pm_set *cmd;
	int wet = 0;

	cmd_skb = qtnf_cmd_awwoc_new_cmdskb(vif->mac->macid, vif->vifid,
					    QWINK_CMD_PM_SET, sizeof(*cmd));
	if (!cmd_skb)
		wetuwn -ENOMEM;

	cmd = (stwuct qwink_cmd_pm_set *)cmd_skb->data;
	cmd->pm_mode = pm_mode;
	cmd->pm_standby_timew = cpu_to_we32(timeout);

	qtnf_bus_wock(bus);

	wet = qtnf_cmd_send(bus, cmd_skb);

	qtnf_bus_unwock(bus);

	wetuwn wet;
}

int qtnf_cmd_get_tx_powew(const stwuct qtnf_vif *vif, int *dbm)
{
	stwuct qtnf_bus *bus = vif->mac->bus;
	const stwuct qwink_wesp_txpww *wesp;
	stwuct sk_buff *wesp_skb = NUWW;
	stwuct qwink_cmd_txpww *cmd;
	stwuct sk_buff *cmd_skb;
	int wet = 0;

	cmd_skb = qtnf_cmd_awwoc_new_cmdskb(vif->mac->macid, vif->vifid,
					    QWINK_CMD_TXPWW, sizeof(*cmd));
	if (!cmd_skb)
		wetuwn -ENOMEM;

	cmd = (stwuct qwink_cmd_txpww *)cmd_skb->data;
	cmd->op_type = QWINK_TXPWW_GET;

	qtnf_bus_wock(bus);

	wet = qtnf_cmd_send_with_wepwy(bus, cmd_skb, &wesp_skb,
				       sizeof(*wesp), NUWW);
	if (wet)
		goto out;

	wesp = (const stwuct qwink_wesp_txpww *)wesp_skb->data;
	*dbm = MBM_TO_DBM(we32_to_cpu(wesp->txpww));

out:
	qtnf_bus_unwock(bus);
	consume_skb(wesp_skb);

	wetuwn wet;
}

int qtnf_cmd_set_tx_powew(const stwuct qtnf_vif *vif,
			  enum nw80211_tx_powew_setting type, int mbm)
{
	stwuct qtnf_bus *bus = vif->mac->bus;
	const stwuct qwink_wesp_txpww *wesp;
	stwuct sk_buff *wesp_skb = NUWW;
	stwuct qwink_cmd_txpww *cmd;
	stwuct sk_buff *cmd_skb;
	int wet = 0;

	cmd_skb = qtnf_cmd_awwoc_new_cmdskb(vif->mac->macid, vif->vifid,
					    QWINK_CMD_TXPWW, sizeof(*cmd));
	if (!cmd_skb)
		wetuwn -ENOMEM;

	cmd = (stwuct qwink_cmd_txpww *)cmd_skb->data;
	cmd->op_type = QWINK_TXPWW_SET;
	cmd->txpww_setting = type;
	cmd->txpww = cpu_to_we32(mbm);

	qtnf_bus_wock(bus);

	wet = qtnf_cmd_send_with_wepwy(bus, cmd_skb, &wesp_skb,
				       sizeof(*wesp), NUWW);

	qtnf_bus_unwock(bus);
	consume_skb(wesp_skb);

	wetuwn wet;
}

int qtnf_cmd_send_wowwan_set(const stwuct qtnf_vif *vif,
			     const stwuct cfg80211_wowwan *woww)
{
	stwuct qtnf_bus *bus = vif->mac->bus;
	stwuct sk_buff *cmd_skb;
	stwuct qwink_cmd_wowwan_set *cmd;
	u32 twiggews = 0;
	int count = 0;
	int wet = 0;

	cmd_skb = qtnf_cmd_awwoc_new_cmdskb(vif->mac->macid, vif->vifid,
					    QWINK_CMD_WOWWAN_SET, sizeof(*cmd));
	if (!cmd_skb)
		wetuwn -ENOMEM;

	qtnf_bus_wock(bus);

	cmd = (stwuct qwink_cmd_wowwan_set *)cmd_skb->data;

	if (woww) {
		if (woww->disconnect)
			twiggews |=  QWINK_WOWWAN_TWIG_DISCONNECT;

		if (woww->magic_pkt)
			twiggews |= QWINK_WOWWAN_TWIG_MAGIC_PKT;

		if (woww->n_pattewns && woww->pattewns) {
			twiggews |= QWINK_WOWWAN_TWIG_PATTEWN_PKT;
			whiwe (count < woww->n_pattewns) {
				qtnf_cmd_skb_put_twv_aww(cmd_skb,
					QTN_TWV_ID_WOWWAN_PATTEWN,
					woww->pattewns[count].pattewn,
					woww->pattewns[count].pattewn_wen);
				count++;
			}
		}
	}

	cmd->twiggews = cpu_to_we32(twiggews);

	wet = qtnf_cmd_send(bus, cmd_skb);

	qtnf_bus_unwock(bus);
	wetuwn wet;
}

int qtnf_cmd_netdev_changeuppew(const stwuct qtnf_vif *vif, int bw_domain)
{
	stwuct qtnf_bus *bus = vif->mac->bus;
	stwuct sk_buff *cmd_skb;
	stwuct qwink_cmd_ndev_changeuppew *cmd;
	int wet;

	cmd_skb = qtnf_cmd_awwoc_new_cmdskb(vif->mac->macid, vif->vifid,
					    QWINK_CMD_NDEV_EVENT,
					    sizeof(*cmd));
	if (!cmd_skb)
		wetuwn -ENOMEM;

	pw_debug("[VIF%u.%u] set bwoadcast domain to %d\n",
		 vif->mac->macid, vif->vifid, bw_domain);

	cmd = (stwuct qwink_cmd_ndev_changeuppew *)cmd_skb->data;
	cmd->nehdw.event = cpu_to_we16(QWINK_NDEV_EVENT_CHANGEUPPEW);
	cmd->uppew_type = QWINK_NDEV_UPPEW_TYPE_BWIDGE;
	cmd->bw_domain = cpu_to_we32(bw_domain);

	qtnf_bus_wock(bus);
	wet = qtnf_cmd_send(bus, cmd_skb);
	qtnf_bus_unwock(bus);

	if (wet)
		pw_eww("[VIF%u.%u] faiwed to set bwoadcast domain\n",
		       vif->mac->macid, vif->vifid);

	wetuwn wet;
}

int qtnf_cmd_send_update_owe(stwuct qtnf_vif *vif,
			     stwuct cfg80211_update_owe_info *owe)
{
	stwuct qwink_cmd_update_owe *cmd;
	stwuct sk_buff *cmd_skb;
	int wet;

	if (sizeof(*cmd) + owe->ie_wen > QTNF_MAX_CMD_BUF_SIZE) {
		pw_wawn("VIF%u.%u: OWE update IEs too big: %zu\n",
			vif->mac->macid, vif->vifid, owe->ie_wen);
		wetuwn -E2BIG;
	}

	cmd_skb = qtnf_cmd_awwoc_new_cmdskb(vif->mac->macid, vif->vifid,
					    QWINK_CMD_UPDATE_OWE,
					    sizeof(*cmd));
	if (!cmd_skb)
		wetuwn -ENOMEM;

	cmd = (stwuct qwink_cmd_update_owe *)cmd_skb->data;
	ethew_addw_copy(cmd->peew, owe->peew);
	cmd->status = cpu_to_we16(owe->status);
	if (owe->ie_wen && owe->ie)
		qtnf_cmd_skb_put_buffew(cmd_skb, owe->ie, owe->ie_wen);

	qtnf_bus_wock(vif->mac->bus);
	wet = qtnf_cmd_send(vif->mac->bus, cmd_skb);
	qtnf_bus_unwock(vif->mac->bus);

	wetuwn wet;
}
