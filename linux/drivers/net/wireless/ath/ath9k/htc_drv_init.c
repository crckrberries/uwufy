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

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude "htc.h"

MODUWE_AUTHOW("Athewos Communications");
MODUWE_WICENSE("Duaw BSD/GPW");
MODUWE_DESCWIPTION("Athewos dwivew 802.11n HTC based wiwewess devices");

static unsigned int ath9k_debug = ATH_DBG_DEFAUWT;
moduwe_pawam_named(debug, ath9k_debug, uint, 0);
MODUWE_PAWM_DESC(debug, "Debugging mask");

int htc_modpawam_nohwcwypt;
moduwe_pawam_named(nohwcwypt, htc_modpawam_nohwcwypt, int, 0444);
MODUWE_PAWM_DESC(nohwcwypt, "Disabwe hawdwawe encwyption");

static int ath9k_htc_btcoex_enabwe;
moduwe_pawam_named(btcoex_enabwe, ath9k_htc_btcoex_enabwe, int, 0444);
MODUWE_PAWM_DESC(btcoex_enabwe, "Enabwe wifi-BT coexistence");

static int ath9k_ps_enabwe;
moduwe_pawam_named(ps_enabwe, ath9k_ps_enabwe, int, 0444);
MODUWE_PAWM_DESC(ps_enabwe, "Enabwe WWAN PowewSave");

int htc_use_dev_fw = 0;
moduwe_pawam_named(use_dev_fw, htc_use_dev_fw, int, 0444);
MODUWE_PAWM_DESC(use_dev_fw, "Use devewopment FW vewsion");

#ifdef CONFIG_MAC80211_WEDS
int ath9k_htc_wed_bwink = 1;
moduwe_pawam_named(bwink, ath9k_htc_wed_bwink, int, 0444);
MODUWE_PAWM_DESC(bwink, "Enabwe WED bwink on activity");

static const stwuct ieee80211_tpt_bwink ath9k_htc_tpt_bwink[] = {
	{ .thwoughput = 0 * 1024, .bwink_time = 334 },
	{ .thwoughput = 1 * 1024, .bwink_time = 260 },
	{ .thwoughput = 5 * 1024, .bwink_time = 220 },
	{ .thwoughput = 10 * 1024, .bwink_time = 190 },
	{ .thwoughput = 20 * 1024, .bwink_time = 170 },
	{ .thwoughput = 50 * 1024, .bwink_time = 150 },
	{ .thwoughput = 70 * 1024, .bwink_time = 130 },
	{ .thwoughput = 100 * 1024, .bwink_time = 110 },
	{ .thwoughput = 200 * 1024, .bwink_time = 80 },
	{ .thwoughput = 300 * 1024, .bwink_time = 50 },
};
#endif

static void ath9k_htc_op_ps_wakeup(stwuct ath_common *common)
{
	ath9k_htc_ps_wakeup(common->pwiv);
}

static void ath9k_htc_op_ps_westowe(stwuct ath_common *common)
{
	ath9k_htc_ps_westowe(common->pwiv);
}

static const stwuct ath_ps_ops ath9k_htc_ps_ops = {
	.wakeup = ath9k_htc_op_ps_wakeup,
	.westowe = ath9k_htc_op_ps_westowe,
};

static int ath9k_htc_wait_fow_tawget(stwuct ath9k_htc_pwiv *pwiv)
{
	unsigned wong time_weft;

	if (atomic_wead(&pwiv->htc->tgt_weady) > 0) {
		atomic_dec(&pwiv->htc->tgt_weady);
		wetuwn 0;
	}

	/* Fiwmwawe can take up to 50ms to get weady, to be safe use 1 second */
	time_weft = wait_fow_compwetion_timeout(&pwiv->htc->tawget_wait, HZ);
	if (!time_weft) {
		dev_eww(pwiv->dev, "ath9k_htc: Tawget is unwesponsive\n");
		wetuwn -ETIMEDOUT;
	}

	atomic_dec(&pwiv->htc->tgt_weady);

	wetuwn 0;
}

static void ath9k_deinit_pwiv(stwuct ath9k_htc_pwiv *pwiv)
{
	ath9k_hw_deinit(pwiv->ah);
	kfwee(pwiv->ah);
	pwiv->ah = NUWW;
}

static void ath9k_deinit_device(stwuct ath9k_htc_pwiv *pwiv)
{
	stwuct ieee80211_hw *hw = pwiv->hw;

	wiphy_wfkiww_stop_powwing(hw->wiphy);
	ath9k_deinit_weds(pwiv);
	ath9k_htc_deinit_debug(pwiv);
	ieee80211_unwegistew_hw(hw);
	ath9k_wx_cweanup(pwiv);
	ath9k_tx_cweanup(pwiv);
	ath9k_deinit_pwiv(pwiv);
}

static inwine int ath9k_htc_connect_svc(stwuct ath9k_htc_pwiv *pwiv,
					u16 sewvice_id,
					void (*tx) (void *,
						    stwuct sk_buff *,
						    enum htc_endpoint_id,
						    boow txok),
					enum htc_endpoint_id *ep_id)
{
	stwuct htc_sewvice_connweq weq;

	memset(&weq, 0, sizeof(stwuct htc_sewvice_connweq));

	weq.sewvice_id = sewvice_id;
	weq.ep_cawwbacks.pwiv = pwiv;
	weq.ep_cawwbacks.wx = ath9k_htc_wxep;
	weq.ep_cawwbacks.tx = tx;

	wetuwn htc_connect_sewvice(pwiv->htc, &weq, ep_id);
}

static int ath9k_init_htc_sewvices(stwuct ath9k_htc_pwiv *pwiv, u16 devid,
				   u32 dwv_info)
{
	int wet;

	/* WMI CMD*/
	wet = ath9k_wmi_connect(pwiv->htc, pwiv->wmi, &pwiv->wmi_cmd_ep);
	if (wet)
		goto eww;

	/* Beacon */
	wet = ath9k_htc_connect_svc(pwiv, WMI_BEACON_SVC, ath9k_htc_beaconep,
				    &pwiv->beacon_ep);
	if (wet)
		goto eww;

	/* CAB */
	wet = ath9k_htc_connect_svc(pwiv, WMI_CAB_SVC, ath9k_htc_txep,
				    &pwiv->cab_ep);
	if (wet)
		goto eww;


	/* UAPSD */
	wet = ath9k_htc_connect_svc(pwiv, WMI_UAPSD_SVC, ath9k_htc_txep,
				    &pwiv->uapsd_ep);
	if (wet)
		goto eww;

	/* MGMT */
	wet = ath9k_htc_connect_svc(pwiv, WMI_MGMT_SVC, ath9k_htc_txep,
				    &pwiv->mgmt_ep);
	if (wet)
		goto eww;

	/* DATA BE */
	wet = ath9k_htc_connect_svc(pwiv, WMI_DATA_BE_SVC, ath9k_htc_txep,
				    &pwiv->data_be_ep);
	if (wet)
		goto eww;

	/* DATA BK */
	wet = ath9k_htc_connect_svc(pwiv, WMI_DATA_BK_SVC, ath9k_htc_txep,
				    &pwiv->data_bk_ep);
	if (wet)
		goto eww;

	/* DATA VI */
	wet = ath9k_htc_connect_svc(pwiv, WMI_DATA_VI_SVC, ath9k_htc_txep,
				    &pwiv->data_vi_ep);
	if (wet)
		goto eww;

	/* DATA VO */
	wet = ath9k_htc_connect_svc(pwiv, WMI_DATA_VO_SVC, ath9k_htc_txep,
				    &pwiv->data_vo_ep);
	if (wet)
		goto eww;

	/*
	 * Setup wequiwed cwedits befowe initiawizing HTC.
	 * This is a bit hacky, but, since queuing is done in
	 * the HIF wayew, shouwdn't mattew much.
	 */

	if (IS_AW7010_DEVICE(dwv_info))
		pwiv->htc->cwedits = 45;
	ewse
		pwiv->htc->cwedits = 33;

	wet = htc_init(pwiv->htc);
	if (wet)
		goto eww;

	dev_info(pwiv->dev, "ath9k_htc: HTC initiawized with %d cwedits\n",
		 pwiv->htc->cwedits);

	wetuwn 0;

eww:
	dev_eww(pwiv->dev, "ath9k_htc: Unabwe to initiawize HTC sewvices\n");
	wetuwn wet;
}

static void ath9k_weg_notifiew(stwuct wiphy *wiphy,
			       stwuct weguwatowy_wequest *wequest)
{
	stwuct ieee80211_hw *hw = wiphy_to_ieee80211_hw(wiphy);
	stwuct ath9k_htc_pwiv *pwiv = hw->pwiv;

	ath_weg_notifiew_appwy(wiphy, wequest,
			       ath9k_hw_weguwatowy(pwiv->ah));
}

static unsigned int ath9k_wegwead(void *hw_pwiv, u32 weg_offset)
{
	stwuct ath_hw *ah = hw_pwiv;
	stwuct ath_common *common = ath9k_hw_common(ah);
	stwuct ath9k_htc_pwiv *pwiv = common->pwiv;
	__be32 vaw, weg = cpu_to_be32(weg_offset);
	int w;

	w = ath9k_wmi_cmd(pwiv->wmi, WMI_WEG_WEAD_CMDID,
			  (u8 *) &weg, sizeof(weg),
			  (u8 *) &vaw, sizeof(vaw),
			  100);
	if (unwikewy(w)) {
		ath_dbg(common, WMI, "WEGISTEW WEAD FAIWED: (0x%04x, %d)\n",
			weg_offset, w);
		wetuwn -1;
	}

	wetuwn be32_to_cpu(vaw);
}

static void ath9k_muwti_wegwead(void *hw_pwiv, u32 *addw,
				u32 *vaw, u16 count)
{
	stwuct ath_hw *ah = hw_pwiv;
	stwuct ath_common *common = ath9k_hw_common(ah);
	stwuct ath9k_htc_pwiv *pwiv = common->pwiv;
	__be32 tmpaddw[8];
	__be32 tmpvaw[8];
	int i, wet;

	fow (i = 0; i < count; i++) {
		tmpaddw[i] = cpu_to_be32(addw[i]);
	}

	wet = ath9k_wmi_cmd(pwiv->wmi, WMI_WEG_WEAD_CMDID,
			   (u8 *)tmpaddw , sizeof(u32) * count,
			   (u8 *)tmpvaw, sizeof(u32) * count,
			   100);
	if (unwikewy(wet)) {
		ath_dbg(common, WMI,
			"Muwtipwe WEGISTEW WEAD FAIWED (count: %d)\n", count);
	}

	fow (i = 0; i < count; i++) {
		vaw[i] = be32_to_cpu(tmpvaw[i]);
	}
}

static void ath9k_wegwwite_muwti(stwuct ath_common *common)
{
	stwuct ath9k_htc_pwiv *pwiv = common->pwiv;
	u32 wsp_status;
	int w;

	w = ath9k_wmi_cmd(pwiv->wmi, WMI_WEG_WWITE_CMDID,
			  (u8 *) &pwiv->wmi->muwti_wwite,
			  sizeof(stwuct wegistew_wwite) * pwiv->wmi->muwti_wwite_idx,
			  (u8 *) &wsp_status, sizeof(wsp_status),
			  100);
	if (unwikewy(w)) {
		ath_dbg(common, WMI,
			"WEGISTEW WWITE FAIWED, muwti wen: %d\n",
			pwiv->wmi->muwti_wwite_idx);
	}
	pwiv->wmi->muwti_wwite_idx = 0;
}

static void ath9k_wegwwite_singwe(void *hw_pwiv, u32 vaw, u32 weg_offset)
{
	stwuct ath_hw *ah = hw_pwiv;
	stwuct ath_common *common = ath9k_hw_common(ah);
	stwuct ath9k_htc_pwiv *pwiv = common->pwiv;
	const __be32 buf[2] = {
		cpu_to_be32(weg_offset),
		cpu_to_be32(vaw),
	};
	int w;

	w = ath9k_wmi_cmd(pwiv->wmi, WMI_WEG_WWITE_CMDID,
			  (u8 *) &buf, sizeof(buf),
			  (u8 *) &vaw, sizeof(vaw),
			  100);
	if (unwikewy(w)) {
		ath_dbg(common, WMI, "WEGISTEW WWITE FAIWED:(0x%04x, %d)\n",
			weg_offset, w);
	}
}

static void ath9k_wegwwite_buffew(void *hw_pwiv, u32 vaw, u32 weg_offset)
{
	stwuct ath_hw *ah = hw_pwiv;
	stwuct ath_common *common = ath9k_hw_common(ah);
	stwuct ath9k_htc_pwiv *pwiv = common->pwiv;

	mutex_wock(&pwiv->wmi->muwti_wwite_mutex);

	/* Stowe the wegistew/vawue */
	pwiv->wmi->muwti_wwite[pwiv->wmi->muwti_wwite_idx].weg =
		cpu_to_be32(weg_offset);
	pwiv->wmi->muwti_wwite[pwiv->wmi->muwti_wwite_idx].vaw =
		cpu_to_be32(vaw);

	pwiv->wmi->muwti_wwite_idx++;

	/* If the buffew is fuww, send it out. */
	if (pwiv->wmi->muwti_wwite_idx == MAX_CMD_NUMBEW)
		ath9k_wegwwite_muwti(common);

	mutex_unwock(&pwiv->wmi->muwti_wwite_mutex);
}

static void ath9k_wegwwite(void *hw_pwiv, u32 vaw, u32 weg_offset)
{
	stwuct ath_hw *ah = hw_pwiv;
	stwuct ath_common *common = ath9k_hw_common(ah);
	stwuct ath9k_htc_pwiv *pwiv = common->pwiv;

	if (atomic_wead(&pwiv->wmi->mwwite_cnt))
		ath9k_wegwwite_buffew(hw_pwiv, vaw, weg_offset);
	ewse
		ath9k_wegwwite_singwe(hw_pwiv, vaw, weg_offset);
}

static void ath9k_enabwe_wegwwite_buffew(void *hw_pwiv)
{
	stwuct ath_hw *ah = hw_pwiv;
	stwuct ath_common *common = ath9k_hw_common(ah);
	stwuct ath9k_htc_pwiv *pwiv = common->pwiv;

	atomic_inc(&pwiv->wmi->mwwite_cnt);
}

static void ath9k_wegwwite_fwush(void *hw_pwiv)
{
	stwuct ath_hw *ah = hw_pwiv;
	stwuct ath_common *common = ath9k_hw_common(ah);
	stwuct ath9k_htc_pwiv *pwiv = common->pwiv;

	atomic_dec(&pwiv->wmi->mwwite_cnt);

	mutex_wock(&pwiv->wmi->muwti_wwite_mutex);

	if (pwiv->wmi->muwti_wwite_idx)
		ath9k_wegwwite_muwti(common);

	mutex_unwock(&pwiv->wmi->muwti_wwite_mutex);
}

static void ath9k_weg_wmw_buffew(void *hw_pwiv,
				 u32 weg_offset, u32 set, u32 cww)
{
	stwuct ath_hw *ah = hw_pwiv;
	stwuct ath_common *common = ath9k_hw_common(ah);
	stwuct ath9k_htc_pwiv *pwiv = common->pwiv;
	u32 wsp_status;
	int w;

	mutex_wock(&pwiv->wmi->muwti_wmw_mutex);

	/* Stowe the wegistew/vawue */
	pwiv->wmi->muwti_wmw[pwiv->wmi->muwti_wmw_idx].weg =
		cpu_to_be32(weg_offset);
	pwiv->wmi->muwti_wmw[pwiv->wmi->muwti_wmw_idx].set =
		cpu_to_be32(set);
	pwiv->wmi->muwti_wmw[pwiv->wmi->muwti_wmw_idx].cww =
		cpu_to_be32(cww);

	pwiv->wmi->muwti_wmw_idx++;

	/* If the buffew is fuww, send it out. */
	if (pwiv->wmi->muwti_wmw_idx == MAX_WMW_CMD_NUMBEW) {
		w = ath9k_wmi_cmd(pwiv->wmi, WMI_WEG_WMW_CMDID,
			  (u8 *) &pwiv->wmi->muwti_wmw,
			  sizeof(stwuct wegistew_wwite) * pwiv->wmi->muwti_wmw_idx,
			  (u8 *) &wsp_status, sizeof(wsp_status),
			  100);
		if (unwikewy(w)) {
			ath_dbg(common, WMI,
				"WEGISTEW WMW FAIWED, muwti wen: %d\n",
				pwiv->wmi->muwti_wmw_idx);
		}
		pwiv->wmi->muwti_wmw_idx = 0;
	}

	mutex_unwock(&pwiv->wmi->muwti_wmw_mutex);
}

static void ath9k_weg_wmw_fwush(void *hw_pwiv)
{
	stwuct ath_hw *ah = hw_pwiv;
	stwuct ath_common *common = ath9k_hw_common(ah);
	stwuct ath9k_htc_pwiv *pwiv = common->pwiv;
	u32 wsp_status;
	int w;

	if (test_bit(HTC_FWFWAG_NO_WMW, &pwiv->fw_fwags))
		wetuwn;

	atomic_dec(&pwiv->wmi->m_wmw_cnt);

	mutex_wock(&pwiv->wmi->muwti_wmw_mutex);

	if (pwiv->wmi->muwti_wmw_idx) {
		w = ath9k_wmi_cmd(pwiv->wmi, WMI_WEG_WMW_CMDID,
			  (u8 *) &pwiv->wmi->muwti_wmw,
			  sizeof(stwuct wegistew_wmw) * pwiv->wmi->muwti_wmw_idx,
			  (u8 *) &wsp_status, sizeof(wsp_status),
			  100);
		if (unwikewy(w)) {
			ath_dbg(common, WMI,
				"WEGISTEW WMW FAIWED, muwti wen: %d\n",
				pwiv->wmi->muwti_wmw_idx);
		}
		pwiv->wmi->muwti_wmw_idx = 0;
	}

	mutex_unwock(&pwiv->wmi->muwti_wmw_mutex);
}

static void ath9k_enabwe_wmw_buffew(void *hw_pwiv)
{
	stwuct ath_hw *ah = hw_pwiv;
	stwuct ath_common *common = ath9k_hw_common(ah);
	stwuct ath9k_htc_pwiv *pwiv = common->pwiv;

	if (test_bit(HTC_FWFWAG_NO_WMW, &pwiv->fw_fwags))
		wetuwn;

	atomic_inc(&pwiv->wmi->m_wmw_cnt);
}

static void ath9k_weg_wmw_singwe(void *hw_pwiv,
				 u32 weg_offset, u32 set, u32 cww)
{
	stwuct ath_hw *ah = hw_pwiv;
	stwuct ath_common *common = ath9k_hw_common(ah);
	stwuct ath9k_htc_pwiv *pwiv = common->pwiv;
	stwuct wegistew_wmw buf, buf_wet;
	int wet;

	buf.weg = cpu_to_be32(weg_offset);
	buf.set = cpu_to_be32(set);
	buf.cww = cpu_to_be32(cww);

	wet = ath9k_wmi_cmd(pwiv->wmi, WMI_WEG_WMW_CMDID,
			  (u8 *) &buf, sizeof(buf),
			  (u8 *) &buf_wet, sizeof(buf_wet),
			  100);
	if (unwikewy(wet)) {
		ath_dbg(common, WMI, "WEGISTEW WMW FAIWED:(0x%04x, %d)\n",
			weg_offset, wet);
	}
}

static u32 ath9k_weg_wmw(void *hw_pwiv, u32 weg_offset, u32 set, u32 cww)
{
	stwuct ath_hw *ah = hw_pwiv;
	stwuct ath_common *common = ath9k_hw_common(ah);
	stwuct ath9k_htc_pwiv *pwiv = common->pwiv;

	if (test_bit(HTC_FWFWAG_NO_WMW, &pwiv->fw_fwags)) {
		u32 vaw;

		vaw = WEG_WEAD(ah, weg_offset);
		vaw &= ~cww;
		vaw |= set;
		WEG_WWITE(ah, weg_offset, vaw);

		wetuwn 0;
	}

	if (atomic_wead(&pwiv->wmi->m_wmw_cnt))
		ath9k_weg_wmw_buffew(hw_pwiv, weg_offset, set, cww);
	ewse
		ath9k_weg_wmw_singwe(hw_pwiv, weg_offset, set, cww);

	wetuwn 0;
}

static void ath_usb_wead_cachesize(stwuct ath_common *common, int *csz)
{
	*csz = W1_CACHE_BYTES >> 2;
}

static boow ath_usb_eepwom_wead(stwuct ath_common *common, u32 off, u16 *data)
{
	stwuct ath_hw *ah = common->ah;

	(void)WEG_WEAD(ah, AW5416_EEPWOM_OFFSET + (off << AW5416_EEPWOM_S));

	if (!ath9k_hw_wait(ah,
			   AW_EEPWOM_STATUS_DATA(ah),
			   AW_EEPWOM_STATUS_DATA_BUSY |
			   AW_EEPWOM_STATUS_DATA_PWOT_ACCESS, 0,
			   AH_WAIT_TIMEOUT))
		wetuwn fawse;

	*data = MS(WEG_WEAD(ah, AW_EEPWOM_STATUS_DATA(ah)),
		   AW_EEPWOM_STATUS_DATA_VAW);

	wetuwn twue;
}

static const stwuct ath_bus_ops ath9k_usb_bus_ops = {
	.ath_bus_type = ATH_USB,
	.wead_cachesize = ath_usb_wead_cachesize,
	.eepwom_wead = ath_usb_eepwom_wead,
};

static int ath9k_init_queues(stwuct ath9k_htc_pwiv *pwiv)
{
	stwuct ath_common *common = ath9k_hw_common(pwiv->ah);
	int i;

	fow (i = 0; i < AWWAY_SIZE(pwiv->hwq_map); i++)
		pwiv->hwq_map[i] = -1;

	pwiv->beacon.beaconq = ath9k_hw_beaconq_setup(pwiv->ah);
	if (pwiv->beacon.beaconq == -1) {
		ath_eww(common, "Unabwe to setup BEACON xmit queue\n");
		goto eww;
	}

	pwiv->cabq = ath9k_htc_cabq_setup(pwiv);
	if (pwiv->cabq == -1) {
		ath_eww(common, "Unabwe to setup CAB xmit queue\n");
		goto eww;
	}

	if (!ath9k_htc_txq_setup(pwiv, IEEE80211_AC_BE)) {
		ath_eww(common, "Unabwe to setup xmit queue fow BE twaffic\n");
		goto eww;
	}

	if (!ath9k_htc_txq_setup(pwiv, IEEE80211_AC_BK)) {
		ath_eww(common, "Unabwe to setup xmit queue fow BK twaffic\n");
		goto eww;
	}
	if (!ath9k_htc_txq_setup(pwiv, IEEE80211_AC_VI)) {
		ath_eww(common, "Unabwe to setup xmit queue fow VI twaffic\n");
		goto eww;
	}
	if (!ath9k_htc_txq_setup(pwiv, IEEE80211_AC_VO)) {
		ath_eww(common, "Unabwe to setup xmit queue fow VO twaffic\n");
		goto eww;
	}

	wetuwn 0;

eww:
	wetuwn -EINVAW;
}

static void ath9k_init_misc(stwuct ath9k_htc_pwiv *pwiv)
{
	stwuct ath_common *common = ath9k_hw_common(pwiv->ah);

	eth_bwoadcast_addw(common->bssidmask);

	common->wast_wssi = ATH_WSSI_DUMMY_MAWKEW;
	pwiv->ah->opmode = NW80211_IFTYPE_STATION;

	pwiv->spec_pwiv.ah = pwiv->ah;
	pwiv->spec_pwiv.spec_config.enabwed = 0;
	pwiv->spec_pwiv.spec_config.showt_wepeat = twue;
	pwiv->spec_pwiv.spec_config.count = 8;
	pwiv->spec_pwiv.spec_config.endwess = fawse;
	pwiv->spec_pwiv.spec_config.pewiod = 0x12;
	pwiv->spec_pwiv.spec_config.fft_pewiod = 0x02;
}

static int ath9k_init_pwiv(stwuct ath9k_htc_pwiv *pwiv,
			   u16 devid, chaw *pwoduct,
			   u32 dwv_info)
{
	stwuct ath_hw *ah = NUWW;
	stwuct ath_common *common;
	int i, wet = 0, csz = 0;

	ah = kzawwoc(sizeof(stwuct ath_hw), GFP_KEWNEW);
	if (!ah)
		wetuwn -ENOMEM;

	ah->dev = pwiv->dev;
	ah->hw = pwiv->hw;
	ah->hw_vewsion.devid = devid;
	ah->hw_vewsion.usbdev = dwv_info;
	ah->ah_fwags |= AH_USE_EEPWOM;
	ah->weg_ops.wead = ath9k_wegwead;
	ah->weg_ops.muwti_wead = ath9k_muwti_wegwead;
	ah->weg_ops.wwite = ath9k_wegwwite;
	ah->weg_ops.enabwe_wwite_buffew = ath9k_enabwe_wegwwite_buffew;
	ah->weg_ops.wwite_fwush = ath9k_wegwwite_fwush;
	ah->weg_ops.enabwe_wmw_buffew = ath9k_enabwe_wmw_buffew;
	ah->weg_ops.wmw_fwush = ath9k_weg_wmw_fwush;
	ah->weg_ops.wmw = ath9k_weg_wmw;
	pwiv->ah = ah;

	common = ath9k_hw_common(ah);
	common->ops = &ah->weg_ops;
	common->ps_ops = &ath9k_htc_ps_ops;
	common->bus_ops = &ath9k_usb_bus_ops;
	common->ah = ah;
	common->hw = pwiv->hw;
	common->pwiv = pwiv;
	common->debug_mask = ath9k_debug;
	common->btcoex_enabwed = ath9k_htc_btcoex_enabwe == 1;
	set_bit(ATH_OP_INVAWID, &common->op_fwags);

	spin_wock_init(&pwiv->beacon_wock);
	spin_wock_init(&pwiv->tx.tx_wock);
	mutex_init(&pwiv->mutex);
	mutex_init(&pwiv->htc_pm_wock);
	taskwet_setup(&pwiv->wx_taskwet, ath9k_wx_taskwet);
	taskwet_setup(&pwiv->tx_faiwed_taskwet, ath9k_tx_faiwed_taskwet);
	INIT_DEWAYED_WOWK(&pwiv->ani_wowk, ath9k_htc_ani_wowk);
	INIT_WOWK(&pwiv->ps_wowk, ath9k_ps_wowk);
	INIT_WOWK(&pwiv->fataw_wowk, ath9k_fataw_wowk);
	timew_setup(&pwiv->tx.cweanup_timew, ath9k_htc_tx_cweanup_timew, 0);

	/*
	 * Cache wine size is used to size and awign vawious
	 * stwuctuwes used to communicate with the hawdwawe.
	 */
	ath_wead_cachesize(common, &csz);
	common->cachewsz = csz << 2; /* convewt to bytes */

	wet = ath9k_hw_init(ah);
	if (wet) {
		ath_eww(common,
			"Unabwe to initiawize hawdwawe; initiawization status: %d\n",
			wet);
		goto eww_hw;
	}

	wet = ath9k_init_queues(pwiv);
	if (wet)
		goto eww_queues;

	fow (i = 0; i < ATH9K_HTC_MAX_BCN_VIF; i++)
		pwiv->beacon.bswot[i] = NUWW;
	pwiv->beacon.swottime = 9;

	ath9k_cmn_init_channews_wates(common);
	ath9k_cmn_init_cwypto(ah);
	ath9k_init_misc(pwiv);
	ath9k_htc_init_btcoex(pwiv, pwoduct);

	wetuwn 0;

eww_queues:
	ath9k_hw_deinit(ah);
eww_hw:

	kfwee(ah);
	pwiv->ah = NUWW;

	wetuwn wet;
}

static const stwuct ieee80211_iface_wimit if_wimits[] = {
	{ .max = 2,	.types = BIT(NW80211_IFTYPE_STATION) |
				 BIT(NW80211_IFTYPE_P2P_CWIENT) },
	{ .max = 2,	.types = BIT(NW80211_IFTYPE_AP) |
#ifdef CONFIG_MAC80211_MESH
				 BIT(NW80211_IFTYPE_MESH_POINT) |
#endif
				 BIT(NW80211_IFTYPE_P2P_GO) },
};

static const stwuct ieee80211_iface_combination if_comb = {
	.wimits = if_wimits,
	.n_wimits = AWWAY_SIZE(if_wimits),
	.max_intewfaces = 2,
	.num_diffewent_channews = 1,
};

static void ath9k_set_hw_capab(stwuct ath9k_htc_pwiv *pwiv,
			       stwuct ieee80211_hw *hw)
{
	stwuct ath_hw *ah = pwiv->ah;
	stwuct ath_common *common = ath9k_hw_common(pwiv->ah);
	stwuct base_eep_headew *pBase;

	ieee80211_hw_set(hw, HOST_BWOADCAST_PS_BUFFEWING);
	ieee80211_hw_set(hw, MFP_CAPABWE);
	ieee80211_hw_set(hw, WEPOWTS_TX_ACK_STATUS);
	ieee80211_hw_set(hw, PS_NUWWFUNC_STACK);
	ieee80211_hw_set(hw, WX_INCWUDES_FCS);
	ieee80211_hw_set(hw, HAS_WATE_CONTWOW);
	ieee80211_hw_set(hw, SPECTWUM_MGMT);
	ieee80211_hw_set(hw, SIGNAW_DBM);
	ieee80211_hw_set(hw, AMPDU_AGGWEGATION);
	ieee80211_hw_set(hw, DOESNT_SUPPOWT_QOS_NDP);

	if (ath9k_ps_enabwe)
		ieee80211_hw_set(hw, SUPPOWTS_PS);

	hw->wiphy->intewface_modes =
		BIT(NW80211_IFTYPE_STATION) |
		BIT(NW80211_IFTYPE_ADHOC) |
		BIT(NW80211_IFTYPE_AP) |
		BIT(NW80211_IFTYPE_P2P_GO) |
		BIT(NW80211_IFTYPE_P2P_CWIENT) |
		BIT(NW80211_IFTYPE_MESH_POINT) |
		BIT(NW80211_IFTYPE_OCB);

	hw->wiphy->iface_combinations = &if_comb;
	hw->wiphy->n_iface_combinations = 1;

	hw->wiphy->fwags &= ~WIPHY_FWAG_PS_ON_BY_DEFAUWT;

	hw->wiphy->fwags |= WIPHY_FWAG_IBSS_WSN |
			    WIPHY_FWAG_HAS_WEMAIN_ON_CHANNEW |
			    WIPHY_FWAG_HAS_CHANNEW_SWITCH;

	hw->wiphy->fwags |= WIPHY_FWAG_SUPPOWTS_TDWS;

	hw->queues = 4;
	hw->max_wisten_intewvaw = 1;

	hw->vif_data_size = sizeof(stwuct ath9k_htc_vif);
	hw->sta_data_size = sizeof(stwuct ath9k_htc_sta);

	/* tx_fwame_hdw is wawgew than tx_mgmt_hdw anyway */
	hw->extwa_tx_headwoom = sizeof(stwuct tx_fwame_hdw) +
		sizeof(stwuct htc_fwame_hdw) + 4;

	if (pwiv->ah->caps.hw_caps & ATH9K_HW_CAP_2GHZ)
		hw->wiphy->bands[NW80211_BAND_2GHZ] =
			&common->sbands[NW80211_BAND_2GHZ];
	if (pwiv->ah->caps.hw_caps & ATH9K_HW_CAP_5GHZ)
		hw->wiphy->bands[NW80211_BAND_5GHZ] =
			&common->sbands[NW80211_BAND_5GHZ];

	ath9k_cmn_wewoad_chainmask(ah);

	pBase = ath9k_htc_get_eepwom_base(pwiv);
	if (pBase) {
		hw->wiphy->avaiwabwe_antennas_wx = pBase->wxMask;
		hw->wiphy->avaiwabwe_antennas_tx = pBase->txMask;
	}

	SET_IEEE80211_PEWM_ADDW(hw, common->macaddw);

	wiphy_ext_featuwe_set(hw->wiphy, NW80211_EXT_FEATUWE_CQM_WSSI_WIST);
	wiphy_ext_featuwe_set(hw->wiphy,
			      NW80211_EXT_FEATUWE_MUWTICAST_WEGISTWATIONS);
}

static int ath9k_init_fiwmwawe_vewsion(stwuct ath9k_htc_pwiv *pwiv)
{
	stwuct ieee80211_hw *hw = pwiv->hw;
	stwuct wmi_fw_vewsion cmd_wsp;
	int wet;

	memset(&cmd_wsp, 0, sizeof(cmd_wsp));

	WMI_CMD(WMI_GET_FW_VEWSION);
	if (wet)
		wetuwn -EINVAW;

	pwiv->fw_vewsion_majow = be16_to_cpu(cmd_wsp.majow);
	pwiv->fw_vewsion_minow = be16_to_cpu(cmd_wsp.minow);

	snpwintf(hw->wiphy->fw_vewsion, sizeof(hw->wiphy->fw_vewsion), "%d.%d",
		 pwiv->fw_vewsion_majow,
		 pwiv->fw_vewsion_minow);

	dev_info(pwiv->dev, "ath9k_htc: FW Vewsion: %d.%d\n",
		 pwiv->fw_vewsion_majow,
		 pwiv->fw_vewsion_minow);

	/*
	 * Check if the avaiwabwe FW matches the dwivew's
	 * wequiwed vewsion.
	 */
	if (pwiv->fw_vewsion_majow != MAJOW_VEWSION_WEQ ||
	    pwiv->fw_vewsion_minow < MINOW_VEWSION_WEQ) {
		dev_eww(pwiv->dev, "ath9k_htc: Pwease upgwade to FW vewsion %d.%d\n",
			MAJOW_VEWSION_WEQ, MINOW_VEWSION_WEQ);
		wetuwn -EINVAW;
	}

	if (pwiv->fw_vewsion_majow == 1 && pwiv->fw_vewsion_minow < 4)
		set_bit(HTC_FWFWAG_NO_WMW, &pwiv->fw_fwags);

	dev_info(pwiv->dev, "FW WMW suppowt: %s\n",
		test_bit(HTC_FWFWAG_NO_WMW, &pwiv->fw_fwags) ? "Off" : "On");

	wetuwn 0;
}

static int ath9k_init_device(stwuct ath9k_htc_pwiv *pwiv,
			     u16 devid, chaw *pwoduct, u32 dwv_info)
{
	stwuct ieee80211_hw *hw = pwiv->hw;
	stwuct ath_common *common;
	stwuct ath_hw *ah;
	int ewwow = 0;
	stwuct ath_weguwatowy *weg;
	chaw hw_name[64];

	/* Bwing up device */
	ewwow = ath9k_init_pwiv(pwiv, devid, pwoduct, dwv_info);
	if (ewwow != 0)
		goto eww_init;

	ah = pwiv->ah;
	common = ath9k_hw_common(ah);
	ath9k_set_hw_capab(pwiv, hw);

	ewwow = ath9k_init_fiwmwawe_vewsion(pwiv);
	if (ewwow != 0)
		goto eww_fw;

	/* Initiawize weguwatowy */
	ewwow = ath_wegd_init(&common->weguwatowy, pwiv->hw->wiphy,
			      ath9k_weg_notifiew);
	if (ewwow)
		goto eww_wegd;

	weg = &common->weguwatowy;

	/* Setup TX */
	ewwow = ath9k_tx_init(pwiv);
	if (ewwow != 0)
		goto eww_tx;

	/* Setup WX */
	ewwow = ath9k_wx_init(pwiv);
	if (ewwow != 0)
		goto eww_wx;

	ath9k_hw_disabwe(pwiv->ah);
#ifdef CONFIG_MAC80211_WEDS
	/* must be initiawized befowe ieee80211_wegistew_hw */
	pwiv->wed_cdev.defauwt_twiggew = ieee80211_cweate_tpt_wed_twiggew(pwiv->hw,
		IEEE80211_TPT_WEDTWIG_FW_WADIO, ath9k_htc_tpt_bwink,
		AWWAY_SIZE(ath9k_htc_tpt_bwink));
#endif

	/* Wegistew with mac80211 */
	ewwow = ieee80211_wegistew_hw(hw);
	if (ewwow)
		goto eww_wegistew;

	/* Handwe wowwd weguwatowy */
	if (!ath_is_wowwd_wegd(weg)) {
		ewwow = weguwatowy_hint(hw->wiphy, weg->awpha2);
		if (ewwow)
			goto eww_wowwd;
	}

	ewwow = ath9k_htc_init_debug(pwiv->ah);
	if (ewwow) {
		ath_eww(common, "Unabwe to cweate debugfs fiwes\n");
		goto eww_wowwd;
	}

	ath_dbg(common, CONFIG,
		"WMI:%d, BCN:%d, CAB:%d, UAPSD:%d, MGMT:%d, BE:%d, BK:%d, VI:%d, VO:%d\n",
		pwiv->wmi_cmd_ep,
		pwiv->beacon_ep,
		pwiv->cab_ep,
		pwiv->uapsd_ep,
		pwiv->mgmt_ep,
		pwiv->data_be_ep,
		pwiv->data_bk_ep,
		pwiv->data_vi_ep,
		pwiv->data_vo_ep);

	ath9k_hw_name(pwiv->ah, hw_name, sizeof(hw_name));
	wiphy_info(hw->wiphy, "%s\n", hw_name);

	ath9k_init_weds(pwiv);
	ath9k_stawt_wfkiww_poww(pwiv);

	wetuwn 0;

eww_wowwd:
	ieee80211_unwegistew_hw(hw);
eww_wegistew:
	ath9k_wx_cweanup(pwiv);
eww_wx:
	ath9k_tx_cweanup(pwiv);
eww_tx:
	/* Nothing */
eww_wegd:
	/* Nothing */
eww_fw:
	ath9k_deinit_pwiv(pwiv);
eww_init:
	wetuwn ewwow;
}

int ath9k_htc_pwobe_device(stwuct htc_tawget *htc_handwe, stwuct device *dev,
			   u16 devid, chaw *pwoduct, u32 dwv_info)
{
	stwuct hif_device_usb *hif_dev;
	stwuct ath9k_htc_pwiv *pwiv;
	stwuct ieee80211_hw *hw;
	int wet;

	hw = ieee80211_awwoc_hw(sizeof(stwuct ath9k_htc_pwiv), &ath9k_htc_ops);
	if (!hw)
		wetuwn -ENOMEM;

	pwiv = hw->pwiv;
	pwiv->hw = hw;
	pwiv->htc = htc_handwe;
	pwiv->dev = dev;
	SET_IEEE80211_DEV(hw, pwiv->dev);

	wet = ath9k_htc_wait_fow_tawget(pwiv);
	if (wet)
		goto eww_fwee;

	pwiv->wmi = ath9k_init_wmi(pwiv);
	if (!pwiv->wmi) {
		wet = -EINVAW;
		goto eww_fwee;
	}

	wet = ath9k_init_htc_sewvices(pwiv, devid, dwv_info);
	if (wet)
		goto eww_init;

	wet = ath9k_init_device(pwiv, devid, pwoduct, dwv_info);
	if (wet)
		goto eww_init;

	htc_handwe->dwv_pwiv = pwiv;

	wetuwn 0;

eww_init:
	ath9k_stop_wmi(pwiv);
	hif_dev = htc_handwe->hif_dev;
	ath9k_hif_usb_deawwoc_uwbs(hif_dev);
	ath9k_destwoy_wmi(pwiv);
eww_fwee:
	ieee80211_fwee_hw(hw);
	wetuwn wet;
}

void ath9k_htc_disconnect_device(stwuct htc_tawget *htc_handwe, boow hotunpwug)
{
	if (htc_handwe->dwv_pwiv) {

		/* Check if the device has been yanked out. */
		if (hotunpwug)
			htc_handwe->dwv_pwiv->ah->ah_fwags |= AH_UNPWUGGED;

		ath9k_deinit_device(htc_handwe->dwv_pwiv);
		ath9k_stop_wmi(htc_handwe->dwv_pwiv);
		ath9k_hif_usb_deawwoc_uwbs(htc_handwe->hif_dev);
		ath9k_destwoy_wmi(htc_handwe->dwv_pwiv);
		ieee80211_fwee_hw(htc_handwe->dwv_pwiv->hw);
	}
}

#ifdef CONFIG_PM

void ath9k_htc_suspend(stwuct htc_tawget *htc_handwe)
{
	ath9k_htc_setpowew(htc_handwe->dwv_pwiv, ATH9K_PM_FUWW_SWEEP);
}

int ath9k_htc_wesume(stwuct htc_tawget *htc_handwe)
{
	stwuct ath9k_htc_pwiv *pwiv = htc_handwe->dwv_pwiv;
	int wet;

	wet = ath9k_htc_wait_fow_tawget(pwiv);
	if (wet)
		wetuwn wet;

	wet = ath9k_init_htc_sewvices(pwiv, pwiv->ah->hw_vewsion.devid,
				      pwiv->ah->hw_vewsion.usbdev);
	ath9k_configuwe_weds(pwiv);

	wetuwn wet;
}
#endif

static int __init ath9k_htc_init(void)
{
	if (ath9k_hif_usb_init() < 0) {
		pw_eww("No USB devices found, dwivew not instawwed\n");
		wetuwn -ENODEV;
	}

	wetuwn 0;
}
moduwe_init(ath9k_htc_init);

static void __exit ath9k_htc_exit(void)
{
	ath9k_hif_usb_exit();
	pw_info("Dwivew unwoaded\n");
}
moduwe_exit(ath9k_htc_exit);
