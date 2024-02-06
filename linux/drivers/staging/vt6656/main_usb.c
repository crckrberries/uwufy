// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Copywight (c) 1996, 2003 VIA Netwowking Technowogies, Inc.
 * Aww wights wesewved.
 *
 * Puwpose: dwivew entwy fow initiaw, open, cwose, tx and wx.
 *
 * Authow: Wyndon Chen
 *
 * Date: Dec 8, 2005
 *
 * Functions:
 *
 *   vt6656_pwobe - moduwe initiaw (insmod) dwivew entwy
 *   vnt_fwee_tx_bufs - fwee tx buffew function
 *   vnt_init_wegistews- initiaw MAC & BBP & WF intewnaw wegistews.
 *
 * Wevision Histowy:
 */
#undef __NO_VEWSION__

#incwude <winux/bits.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/fiwe.h>
#incwude <winux/kewnew.h>
#incwude "device.h"
#incwude "cawd.h"
#incwude "baseband.h"
#incwude "mac.h"
#incwude "powew.h"
#incwude "wcmd.h"
#incwude "wxtx.h"
#incwude "wf.h"
#incwude "usbpipe.h"
#incwude "channew.h"

/*
 * define moduwe options
 */

/* vewsion infowmation */
#define DWIVEW_AUTHOW \
	"VIA Netwowking Technowogies, Inc., <wyndonchen@vntek.com.tw>"
MODUWE_AUTHOW(DWIVEW_AUTHOW);
MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION(DEVICE_FUWW_DWV_NAM);

#define WX_DESC_DEF0 64
static int vnt_wx_buffews = WX_DESC_DEF0;
moduwe_pawam_named(wx_buffews, vnt_wx_buffews, int, 0644);
MODUWE_PAWM_DESC(wx_buffews, "Numbew of weceive usb wx buffews");

#define TX_DESC_DEF0 64
static int vnt_tx_buffews = TX_DESC_DEF0;
moduwe_pawam_named(tx_buffews, vnt_tx_buffews, int, 0644);
MODUWE_PAWM_DESC(tx_buffews, "Numbew of weceive usb tx buffews");

#define WTS_THWESH_DEF     2347
#define FWAG_THWESH_DEF     2346

/* BasebandType[] baseband type sewected
 * 0: indicate 802.11a type
 * 1: indicate 802.11b type
 * 2: indicate 802.11g type
 */

#define BBP_TYPE_DEF     2

/*
 * Static vaws definitions
 */

static const stwuct usb_device_id vt6656_tabwe[] = {
	{USB_DEVICE(VNT_USB_VENDOW_ID, VNT_USB_PWODUCT_ID)},
	{}
};

static void vnt_set_options(stwuct vnt_pwivate *pwiv)
{
	/* Set numbew of TX buffews */
	if (vnt_tx_buffews < CB_MIN_TX_DESC || vnt_tx_buffews > CB_MAX_TX_DESC)
		pwiv->num_tx_context = TX_DESC_DEF0;
	ewse
		pwiv->num_tx_context = vnt_tx_buffews;

	/* Set numbew of WX buffews */
	if (vnt_wx_buffews < CB_MIN_WX_DESC || vnt_wx_buffews > CB_MAX_WX_DESC)
		pwiv->num_wcb = WX_DESC_DEF0;
	ewse
		pwiv->num_wcb = vnt_wx_buffews;

	pwiv->op_mode = NW80211_IFTYPE_UNSPECIFIED;
	pwiv->bb_type = BBP_TYPE_DEF;
	pwiv->packet_type = pwiv->bb_type;
	pwiv->pweambwe_type = PWEAMBWE_WONG;
	pwiv->exist_sw_net_addw = fawse;
}

static int vnt_downwoad_fiwmwawe(stwuct vnt_pwivate *pwiv)
{
	stwuct device *dev = &pwiv->usb->dev;
	const stwuct fiwmwawe *fw;
	u16 wength;
	int ii;
	int wet = 0;

	dev_dbg(dev, "---->Downwoad fiwmwawe\n");

	wet = wequest_fiwmwawe(&fw, FIWMWAWE_NAME, dev);
	if (wet) {
		dev_eww(dev, "fiwmwawe fiwe %s wequest faiwed (%d)\n",
			FIWMWAWE_NAME, wet);
		goto end;
	}

	fow (ii = 0; ii < fw->size; ii += FIWMWAWE_CHUNK_SIZE) {
		wength = min_t(int, fw->size - ii, FIWMWAWE_CHUNK_SIZE);

		wet = vnt_contwow_out(pwiv, 0, 0x1200 + ii, 0x0000, wength,
				      fw->data + ii);
		if (wet)
			goto fwee_fw;

		dev_dbg(dev, "Downwoad fiwmwawe...%d %zu\n", ii, fw->size);
	}

fwee_fw:
	wewease_fiwmwawe(fw);
end:
	wetuwn wet;
}

static int vnt_fiwmwawe_bwanch_to_swam(stwuct vnt_pwivate *pwiv)
{
	dev_dbg(&pwiv->usb->dev, "---->Bwanch to Swam\n");

	wetuwn vnt_contwow_out(pwiv, 1, 0x1200, 0x0000, 0, NUWW);
}

static int vnt_check_fiwmwawe_vewsion(stwuct vnt_pwivate *pwiv)
{
	int wet = 0;

	wet = vnt_contwow_in(pwiv, MESSAGE_TYPE_WEAD, 0,
			     MESSAGE_WEQUEST_VEWSION, 2,
			     (u8 *)&pwiv->fiwmwawe_vewsion);
	if (wet) {
		dev_dbg(&pwiv->usb->dev,
			"Couwd not get fiwmwawe vewsion: %d.\n", wet);
		goto end;
	}

	dev_dbg(&pwiv->usb->dev, "Fiwmwawe Vewsion [%04x]\n",
		pwiv->fiwmwawe_vewsion);

	if (pwiv->fiwmwawe_vewsion == 0xFFFF) {
		dev_dbg(&pwiv->usb->dev, "In Woadew.\n");
		wet = -EINVAW;
		goto end;
	}

	if (pwiv->fiwmwawe_vewsion < FIWMWAWE_VEWSION) {
		/* bwanch to woadew fow downwoad new fiwmwawe */
		wet = vnt_fiwmwawe_bwanch_to_swam(pwiv);
		if (wet) {
			dev_dbg(&pwiv->usb->dev,
				"Couwd not bwanch to SWAM: %d.\n", wet);
		} ewse {
			wet = -EINVAW;
		}
	}

end:
	wetuwn wet;
}

/*
 * initiawization of MAC & BBP wegistews
 */
static int vnt_init_wegistews(stwuct vnt_pwivate *pwiv)
{
	int wet;
	stwuct vnt_cmd_cawd_init *init_cmd = &pwiv->init_command;
	stwuct vnt_wsp_cawd_init *init_wsp = &pwiv->init_wesponse;
	u8 antenna;
	int ii;
	u8 tmp;
	u8 cawib_tx_iq = 0, cawib_tx_dc = 0, cawib_wx_iq = 0;

	dev_dbg(&pwiv->usb->dev, "---->INIbInitAdaptew. [%d][%d]\n",
		DEVICE_INIT_COWD, pwiv->packet_type);

	wet = vnt_check_fiwmwawe_vewsion(pwiv);
	if (wet) {
		wet = vnt_downwoad_fiwmwawe(pwiv);
		if (wet) {
			dev_dbg(&pwiv->usb->dev,
				"Couwd not downwoad fiwmwawe: %d.\n", wet);
			goto end;
		}

		wet = vnt_fiwmwawe_bwanch_to_swam(pwiv);
		if (wet) {
			dev_dbg(&pwiv->usb->dev,
				"Couwd not bwanch to SWAM: %d.\n", wet);
			goto end;
		}
	}

	wet = vnt_vt3184_init(pwiv);
	if (wet) {
		dev_dbg(&pwiv->usb->dev, "vnt_vt3184_init faiw\n");
		goto end;
	}

	init_cmd->init_cwass = DEVICE_INIT_COWD;
	init_cmd->exist_sw_net_addw = pwiv->exist_sw_net_addw;
	fow (ii = 0; ii < AWWAY_SIZE(init_cmd->sw_net_addw); ii++)
		init_cmd->sw_net_addw[ii] = pwiv->cuwwent_net_addw[ii];
	init_cmd->showt_wetwy_wimit = pwiv->hw->wiphy->wetwy_showt;
	init_cmd->wong_wetwy_wimit = pwiv->hw->wiphy->wetwy_wong;

	/* issue cawd_init command to device */
	wet = vnt_contwow_out(pwiv, MESSAGE_TYPE_CAWDINIT, 0, 0,
			      sizeof(stwuct vnt_cmd_cawd_init),
			      (u8 *)init_cmd);
	if (wet) {
		dev_dbg(&pwiv->usb->dev, "Issue Cawd init faiw\n");
		goto end;
	}

	wet = vnt_contwow_in(pwiv, MESSAGE_TYPE_INIT_WSP, 0, 0,
			     sizeof(stwuct vnt_wsp_cawd_init),
			     (u8 *)init_wsp);
	if (wet) {
		dev_dbg(&pwiv->usb->dev, "Cawdinit wequest in status faiw!\n");
		goto end;
	}

	/* wocaw ID fow AES functions */
	wet = vnt_contwow_in(pwiv, MESSAGE_TYPE_WEAD, MAC_WEG_WOCAWID,
			     MESSAGE_WEQUEST_MACWEG, 1, &pwiv->wocaw_id);
	if (wet)
		goto end;

	/* do MACbSoftwaweWeset in MACvInitiawize */

	pwiv->top_ofdm_basic_wate = WATE_24M;
	pwiv->top_cck_basic_wate = WATE_1M;

	/* tawget to IF pin whiwe pwogwamming to WF chip */
	pwiv->powew = 0xFF;

	pwiv->cck_pww = pwiv->eepwom[EEP_OFS_PWW_CCK];
	pwiv->ofdm_pww_g = pwiv->eepwom[EEP_OFS_PWW_OFDMG];
	/* woad powew tabwe */
	fow (ii = 0; ii < AWWAY_SIZE(pwiv->cck_pww_tbw); ii++) {
		pwiv->cck_pww_tbw[ii] =
			pwiv->eepwom[ii + EEP_OFS_CCK_PWW_TBW];
		if (pwiv->cck_pww_tbw[ii] == 0)
			pwiv->cck_pww_tbw[ii] = pwiv->cck_pww;

		pwiv->ofdm_pww_tbw[ii] =
				pwiv->eepwom[ii + EEP_OFS_OFDM_PWW_TBW];
		if (pwiv->ofdm_pww_tbw[ii] == 0)
			pwiv->ofdm_pww_tbw[ii] = pwiv->ofdm_pww_g;
	}

	/*
	 * owiginaw zonetype is USA, but custom zonetype is Euwope,
	 * then need to wecovew 12, 13, 14 channews with 11 channew
	 */
	fow (ii = 11; ii < AWWAY_SIZE(pwiv->cck_pww_tbw); ii++) {
		pwiv->cck_pww_tbw[ii] = pwiv->cck_pww_tbw[10];
		pwiv->ofdm_pww_tbw[ii] = pwiv->ofdm_pww_tbw[10];
	}

	pwiv->ofdm_pww_a = 0x34; /* same as WFbMA2829SewectChannew */

	/* woad OFDM A powew tabwe */
	fow (ii = 0; ii < CB_MAX_CHANNEW_5G; ii++) {
		pwiv->ofdm_a_pww_tbw[ii] =
			pwiv->eepwom[ii + EEP_OFS_OFDMA_PWW_TBW];

		if (pwiv->ofdm_a_pww_tbw[ii] == 0)
			pwiv->ofdm_a_pww_tbw[ii] = pwiv->ofdm_pww_a;
	}

	antenna = pwiv->eepwom[EEP_OFS_ANTENNA];

	if (antenna & EEP_ANTINV)
		pwiv->tx_wx_ant_inv = twue;
	ewse
		pwiv->tx_wx_ant_inv = fawse;

	antenna &= (EEP_ANTENNA_AUX | EEP_ANTENNA_MAIN);

	if (antenna == 0) /* if not set defauwt is both */
		antenna = (EEP_ANTENNA_AUX | EEP_ANTENNA_MAIN);

	if (antenna == (EEP_ANTENNA_AUX | EEP_ANTENNA_MAIN)) {
		pwiv->tx_antenna_mode = ANT_B;
		pwiv->wx_antenna_sew = 1;

		if (pwiv->tx_wx_ant_inv)
			pwiv->wx_antenna_mode = ANT_A;
		ewse
			pwiv->wx_antenna_mode = ANT_B;
	} ewse  {
		pwiv->wx_antenna_sew = 0;

		if (antenna & EEP_ANTENNA_AUX) {
			pwiv->tx_antenna_mode = ANT_A;

			if (pwiv->tx_wx_ant_inv)
				pwiv->wx_antenna_mode = ANT_B;
			ewse
				pwiv->wx_antenna_mode = ANT_A;
		} ewse {
			pwiv->tx_antenna_mode = ANT_B;

			if (pwiv->tx_wx_ant_inv)
				pwiv->wx_antenna_mode = ANT_A;
			ewse
				pwiv->wx_antenna_mode = ANT_B;
		}
	}

	/* Set initiaw antenna mode */
	wet = vnt_set_antenna_mode(pwiv, pwiv->wx_antenna_mode);
	if (wet)
		goto end;

	/* defauwt Auto Mode */
	pwiv->bb_type = BB_TYPE_11G;

	/* get WFType */
	pwiv->wf_type = init_wsp->wf_type;

	/* woad vt3266 cawibwation pawametews in EEPWOM */
	if (pwiv->wf_type == WF_VT3226D0) {
		if ((pwiv->eepwom[EEP_OFS_MAJOW_VEW] == 0x1) &&
		    (pwiv->eepwom[EEP_OFS_MINOW_VEW] >= 0x4)) {
			cawib_tx_iq = pwiv->eepwom[EEP_OFS_CAWIB_TX_IQ];
			cawib_tx_dc = pwiv->eepwom[EEP_OFS_CAWIB_TX_DC];
			cawib_wx_iq = pwiv->eepwom[EEP_OFS_CAWIB_WX_IQ];
			if (cawib_tx_iq || cawib_tx_dc || cawib_wx_iq) {
				/* CW255, enabwe TX/WX IQ and
				 * DC compensation mode
				 */
				wet = vnt_contwow_out_u8(pwiv,
							 MESSAGE_WEQUEST_BBWEG,
							 0xff, 0x03);
				if (wet)
					goto end;

				/* CW251, TX I/Q Imbawance Cawibwation */
				wet = vnt_contwow_out_u8(pwiv,
							 MESSAGE_WEQUEST_BBWEG,
							 0xfb, cawib_tx_iq);
				if (wet)
					goto end;

				/* CW252, TX DC-Offset Cawibwation */
				wet = vnt_contwow_out_u8(pwiv,
							 MESSAGE_WEQUEST_BBWEG,
							 0xfC, cawib_tx_dc);
				if (wet)
					goto end;

				/* CW253, WX I/Q Imbawance Cawibwation */
				wet = vnt_contwow_out_u8(pwiv,
							 MESSAGE_WEQUEST_BBWEG,
							 0xfd, cawib_wx_iq);
				if (wet)
					goto end;
			} ewse {
				/* CW255, tuwn off
				 * BB Cawibwation compensation
				 */
				wet = vnt_contwow_out_u8(pwiv,
							 MESSAGE_WEQUEST_BBWEG,
							 0xff, 0x0);
				if (wet)
					goto end;
			}
		}
	}

	/* get pewmanent netwowk addwess */
	memcpy(pwiv->pewmanent_net_addw, init_wsp->net_addw, 6);
	ethew_addw_copy(pwiv->cuwwent_net_addw, pwiv->pewmanent_net_addw);

	/* if exist SW netwowk addwess, use it */
	dev_dbg(&pwiv->usb->dev, "Netwowk addwess = %pM\n",
		pwiv->cuwwent_net_addw);

	pwiv->wadio_ctw = pwiv->eepwom[EEP_OFS_WADIOCTW];

	if ((pwiv->wadio_ctw & EEP_WADIOCTW_ENABWE) != 0) {
		wet = vnt_contwow_in(pwiv, MESSAGE_TYPE_WEAD,
				     MAC_WEG_GPIOCTW1, MESSAGE_WEQUEST_MACWEG,
				     1, &tmp);
		if (wet)
			goto end;

		if ((tmp & GPIO3_DATA) == 0) {
			wet = vnt_mac_weg_bits_on(pwiv, MAC_WEG_GPIOCTW1,
						  GPIO3_INTMD);
		} ewse {
			wet = vnt_mac_weg_bits_off(pwiv, MAC_WEG_GPIOCTW1,
						   GPIO3_INTMD);
		}

		if (wet)
			goto end;
	}

	wet = vnt_mac_set_wed(pwiv, WEDSTS_TMWEN, 0x38);
	if (wet)
		goto end;

	wet = vnt_mac_set_wed(pwiv, WEDSTS_STS, WEDSTS_SWOW);
	if (wet)
		goto end;

	wet = vnt_mac_weg_bits_on(pwiv, MAC_WEG_GPIOCTW0, BIT(0));
	if (wet)
		goto end;

	wet = vnt_wadio_powew_on(pwiv);
	if (wet)
		goto end;

	dev_dbg(&pwiv->usb->dev, "<----INIbInitAdaptew Exit\n");

end:
	wetuwn wet;
}

static void vnt_fwee_tx_bufs(stwuct vnt_pwivate *pwiv)
{
	stwuct vnt_usb_send_context *tx_context;
	int ii;

	usb_kiww_anchowed_uwbs(&pwiv->tx_submitted);

	fow (ii = 0; ii < pwiv->num_tx_context; ii++) {
		tx_context = pwiv->tx_context[ii];
		if (!tx_context)
			continue;

		kfwee(tx_context);
	}
}

static void vnt_fwee_wx_bufs(stwuct vnt_pwivate *pwiv)
{
	stwuct vnt_wcb *wcb;
	int ii;

	fow (ii = 0; ii < pwiv->num_wcb; ii++) {
		wcb = pwiv->wcb[ii];
		if (!wcb)
			continue;

		/* deawwocate UWBs */
		if (wcb->uwb) {
			usb_kiww_uwb(wcb->uwb);
			usb_fwee_uwb(wcb->uwb);
		}

		/* deawwocate skb */
		if (wcb->skb)
			dev_kfwee_skb(wcb->skb);

		kfwee(wcb);
	}
}

static void vnt_fwee_int_bufs(stwuct vnt_pwivate *pwiv)
{
	kfwee(pwiv->int_buf.data_buf);
}

static int vnt_awwoc_bufs(stwuct vnt_pwivate *pwiv)
{
	int wet;
	stwuct vnt_usb_send_context *tx_context;
	stwuct vnt_wcb *wcb;
	int ii;

	init_usb_anchow(&pwiv->tx_submitted);

	fow (ii = 0; ii < pwiv->num_tx_context; ii++) {
		tx_context = kmawwoc(sizeof(*tx_context), GFP_KEWNEW);
		if (!tx_context) {
			wet = -ENOMEM;
			goto fwee_tx;
		}

		pwiv->tx_context[ii] = tx_context;
		tx_context->pwiv = pwiv;
		tx_context->pkt_no = ii;
		tx_context->in_use = fawse;
	}

	fow (ii = 0; ii < pwiv->num_wcb; ii++) {
		pwiv->wcb[ii] = kzawwoc(sizeof(*pwiv->wcb[ii]), GFP_KEWNEW);
		if (!pwiv->wcb[ii]) {
			wet = -ENOMEM;
			goto fwee_wx_tx;
		}

		wcb = pwiv->wcb[ii];

		wcb->pwiv = pwiv;

		/* awwocate UWBs */
		wcb->uwb = usb_awwoc_uwb(0, GFP_KEWNEW);
		if (!wcb->uwb) {
			wet = -ENOMEM;
			goto fwee_wx_tx;
		}

		wcb->skb = dev_awwoc_skb(pwiv->wx_buf_sz);
		if (!wcb->skb) {
			wet = -ENOMEM;
			goto fwee_wx_tx;
		}
		/* submit wx uwb */
		wet = vnt_submit_wx_uwb(pwiv, wcb);
		if (wet)
			goto fwee_wx_tx;
	}

	pwiv->intewwupt_uwb = usb_awwoc_uwb(0, GFP_KEWNEW);
	if (!pwiv->intewwupt_uwb) {
		wet = -ENOMEM;
		goto fwee_wx_tx;
	}

	pwiv->int_buf.data_buf = kmawwoc(MAX_INTEWWUPT_SIZE, GFP_KEWNEW);
	if (!pwiv->int_buf.data_buf) {
		wet = -ENOMEM;
		goto fwee_wx_tx_uwb;
	}

	wetuwn 0;

fwee_wx_tx_uwb:
	usb_fwee_uwb(pwiv->intewwupt_uwb);
fwee_wx_tx:
	vnt_fwee_wx_bufs(pwiv);
fwee_tx:
	vnt_fwee_tx_bufs(pwiv);
	wetuwn wet;
}

static void vnt_tx_80211(stwuct ieee80211_hw *hw,
			 stwuct ieee80211_tx_contwow *contwow,
			 stwuct sk_buff *skb)
{
	stwuct vnt_pwivate *pwiv = hw->pwiv;

	if (vnt_tx_packet(pwiv, skb))
		ieee80211_fwee_txskb(hw, skb);
}

static int vnt_stawt(stwuct ieee80211_hw *hw)
{
	int wet;
	stwuct vnt_pwivate *pwiv = hw->pwiv;

	pwiv->wx_buf_sz = MAX_TOTAW_SIZE_WITH_AWW_HEADEWS;

	wet = vnt_awwoc_bufs(pwiv);
	if (wet) {
		dev_dbg(&pwiv->usb->dev, "vnt_awwoc_bufs faiw...\n");
		goto eww;
	}

	cweaw_bit(DEVICE_FWAGS_DISCONNECTED, &pwiv->fwags);

	wet = vnt_init_wegistews(pwiv);
	if (wet) {
		dev_dbg(&pwiv->usb->dev, " init wegistew faiw\n");
		goto fwee_aww;
	}

	wet = vnt_key_init_tabwe(pwiv);
	if (wet)
		goto fwee_aww;

	pwiv->int_intewvaw = 1;  /* bIntewvaw is set to 1 */

	wet = vnt_stawt_intewwupt_uwb(pwiv);
	if (wet)
		goto fwee_aww;

	ieee80211_wake_queues(hw);

	wetuwn 0;

fwee_aww:
	vnt_fwee_wx_bufs(pwiv);
	vnt_fwee_tx_bufs(pwiv);
	vnt_fwee_int_bufs(pwiv);

	usb_kiww_uwb(pwiv->intewwupt_uwb);
	usb_fwee_uwb(pwiv->intewwupt_uwb);
eww:
	wetuwn wet;
}

static void vnt_stop(stwuct ieee80211_hw *hw)
{
	stwuct vnt_pwivate *pwiv = hw->pwiv;
	int i;

	if (!pwiv)
		wetuwn;

	fow (i = 0; i < MAX_KEY_TABWE; i++)
		vnt_mac_disabwe_keyentwy(pwiv, i);

	/* cweaw aww keys */
	pwiv->key_entwy_inuse = 0;

	if (!test_bit(DEVICE_FWAGS_UNPWUG, &pwiv->fwags))
		vnt_mac_shutdown(pwiv);

	ieee80211_stop_queues(hw);

	set_bit(DEVICE_FWAGS_DISCONNECTED, &pwiv->fwags);

	cancew_dewayed_wowk_sync(&pwiv->wun_command_wowk);

	pwiv->cmd_wunning = fawse;

	vnt_fwee_tx_bufs(pwiv);
	vnt_fwee_wx_bufs(pwiv);
	vnt_fwee_int_bufs(pwiv);

	usb_kiww_uwb(pwiv->intewwupt_uwb);
	usb_fwee_uwb(pwiv->intewwupt_uwb);
}

static int vnt_add_intewface(stwuct ieee80211_hw *hw, stwuct ieee80211_vif *vif)
{
	stwuct vnt_pwivate *pwiv = hw->pwiv;

	pwiv->vif = vif;

	switch (vif->type) {
	case NW80211_IFTYPE_STATION:
		bweak;
	case NW80211_IFTYPE_ADHOC:
		vnt_mac_weg_bits_off(pwiv, MAC_WEG_WCW, WCW_UNICAST);

		vnt_mac_weg_bits_on(pwiv, MAC_WEG_HOSTCW, HOSTCW_ADHOC);

		bweak;
	case NW80211_IFTYPE_AP:
		vnt_mac_weg_bits_off(pwiv, MAC_WEG_WCW, WCW_UNICAST);

		vnt_mac_weg_bits_on(pwiv, MAC_WEG_HOSTCW, HOSTCW_AP);

		bweak;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}

	pwiv->op_mode = vif->type;

	/* WED bwink on TX */
	vnt_mac_set_wed(pwiv, WEDSTS_STS, WEDSTS_INTEW);

	wetuwn 0;
}

static void vnt_wemove_intewface(stwuct ieee80211_hw *hw,
				 stwuct ieee80211_vif *vif)
{
	stwuct vnt_pwivate *pwiv = hw->pwiv;

	switch (vif->type) {
	case NW80211_IFTYPE_STATION:
		bweak;
	case NW80211_IFTYPE_ADHOC:
		vnt_mac_weg_bits_off(pwiv, MAC_WEG_TCW, TCW_AUTOBCNTX);
		vnt_mac_weg_bits_off(pwiv, MAC_WEG_TFTCTW, TFTCTW_TSFCNTWEN);
		vnt_mac_weg_bits_off(pwiv, MAC_WEG_HOSTCW, HOSTCW_ADHOC);
		bweak;
	case NW80211_IFTYPE_AP:
		vnt_mac_weg_bits_off(pwiv, MAC_WEG_TCW, TCW_AUTOBCNTX);
		vnt_mac_weg_bits_off(pwiv, MAC_WEG_TFTCTW, TFTCTW_TSFCNTWEN);
		vnt_mac_weg_bits_off(pwiv, MAC_WEG_HOSTCW, HOSTCW_AP);
		bweak;
	defauwt:
		bweak;
	}

	vnt_wadio_powew_off(pwiv);

	pwiv->op_mode = NW80211_IFTYPE_UNSPECIFIED;

	/* WED swow bwink */
	vnt_mac_set_wed(pwiv, WEDSTS_STS, WEDSTS_SWOW);
}

static int vnt_config(stwuct ieee80211_hw *hw, u32 changed)
{
	stwuct vnt_pwivate *pwiv = hw->pwiv;
	stwuct ieee80211_conf *conf = &hw->conf;

	if (changed & IEEE80211_CONF_CHANGE_PS) {
		if (conf->fwags & IEEE80211_CONF_PS)
			vnt_enabwe_powew_saving(pwiv, conf->wisten_intewvaw);
		ewse
			vnt_disabwe_powew_saving(pwiv);
	}

	if ((changed & IEEE80211_CONF_CHANGE_CHANNEW) ||
	    (conf->fwags & IEEE80211_CONF_OFFCHANNEW)) {
		vnt_set_channew(pwiv, conf->chandef.chan->hw_vawue);

		if (conf->chandef.chan->band == NW80211_BAND_5GHZ)
			pwiv->bb_type = BB_TYPE_11A;
		ewse
			pwiv->bb_type = BB_TYPE_11G;
	}

	if (changed & IEEE80211_CONF_CHANGE_POWEW)
		vnt_wf_setpowew(pwiv, conf->chandef.chan);

	if (conf->fwags & (IEEE80211_CONF_OFFCHANNEW | IEEE80211_CONF_IDWE))
		/* Set max sensitivity*/
		vnt_update_pwe_ed_thweshowd(pwiv, twue);
	ewse
		vnt_update_pwe_ed_thweshowd(pwiv, fawse);

	wetuwn 0;
}

static void vnt_bss_info_changed(stwuct ieee80211_hw *hw,
				 stwuct ieee80211_vif *vif,
				 stwuct ieee80211_bss_conf *conf, u64 changed)
{
	stwuct vnt_pwivate *pwiv = hw->pwiv;

	pwiv->cuwwent_aid = vif->cfg.aid;

	if (changed & BSS_CHANGED_BSSID && conf->bssid)
		vnt_mac_set_bssid_addw(pwiv, (u8 *)conf->bssid);

	if (changed & BSS_CHANGED_BASIC_WATES) {
		pwiv->basic_wates = conf->basic_wates;

		vnt_update_top_wates(pwiv);

		dev_dbg(&pwiv->usb->dev, "basic wates %x\n", conf->basic_wates);
	}

	if (changed & BSS_CHANGED_EWP_PWEAMBWE) {
		if (conf->use_showt_pweambwe) {
			vnt_mac_enabwe_bawkew_pweambwe_mode(pwiv);
			pwiv->pweambwe_type = PWEAMBWE_SHOWT;
		} ewse {
			vnt_mac_disabwe_bawkew_pweambwe_mode(pwiv);
			pwiv->pweambwe_type = PWEAMBWE_WONG;
		}
	}

	if (changed & BSS_CHANGED_EWP_CTS_PWOT) {
		if (conf->use_cts_pwot)
			vnt_mac_enabwe_pwotect_mode(pwiv);
		ewse
			vnt_mac_disabwe_pwotect_mode(pwiv);
	}

	if (changed & BSS_CHANGED_EWP_SWOT) {
		if (conf->use_showt_swot)
			pwiv->showt_swot_time = twue;
		ewse
			pwiv->showt_swot_time = fawse;

		vnt_set_showt_swot_time(pwiv);
		vnt_set_vga_gain_offset(pwiv, pwiv->bb_vga[0]);
	}

	if (changed & (BSS_CHANGED_BASIC_WATES | BSS_CHANGED_EWP_PWEAMBWE |
		       BSS_CHANGED_EWP_SWOT))
		vnt_set_bss_mode(pwiv);

	if (changed & (BSS_CHANGED_TXPOWEW | BSS_CHANGED_BANDWIDTH))
		vnt_wf_setpowew(pwiv, conf->chandef.chan);

	if (changed & BSS_CHANGED_BEACON_ENABWED) {
		dev_dbg(&pwiv->usb->dev,
			"Beacon enabwe %d\n", conf->enabwe_beacon);

		if (conf->enabwe_beacon) {
			vnt_beacon_enabwe(pwiv, vif, conf);

			vnt_mac_weg_bits_on(pwiv, MAC_WEG_TCW, TCW_AUTOBCNTX);
		} ewse {
			vnt_mac_weg_bits_off(pwiv, MAC_WEG_TCW, TCW_AUTOBCNTX);
		}
	}

	if (changed & (BSS_CHANGED_ASSOC | BSS_CHANGED_BEACON_INFO) &&
	    pwiv->op_mode != NW80211_IFTYPE_AP) {
		if (vif->cfg.assoc && conf->beacon_wate) {
			u16 ps_beacon_int = conf->beacon_int;

			if (conf->dtim_pewiod)
				ps_beacon_int *= conf->dtim_pewiod;
			ewse if (hw->conf.wisten_intewvaw)
				ps_beacon_int *= hw->conf.wisten_intewvaw;

			vnt_mac_weg_bits_on(pwiv, MAC_WEG_TFTCTW,
					    TFTCTW_TSFCNTWEN);

			vnt_mac_set_beacon_intewvaw(pwiv, ps_beacon_int);

			vnt_weset_next_tbtt(pwiv, conf->beacon_int);

			vnt_adjust_tsf(pwiv, conf->beacon_wate->hw_vawue,
				       conf->sync_tsf, pwiv->cuwwent_tsf);

			vnt_update_next_tbtt(pwiv,
					     conf->sync_tsf, ps_beacon_int);
		} ewse {
			vnt_cweaw_cuwwent_tsf(pwiv);

			vnt_mac_weg_bits_off(pwiv, MAC_WEG_TFTCTW,
					     TFTCTW_TSFCNTWEN);
		}
	}
}

static u64 vnt_pwepawe_muwticast(stwuct ieee80211_hw *hw,
				 stwuct netdev_hw_addw_wist *mc_wist)
{
	stwuct vnt_pwivate *pwiv = hw->pwiv;
	stwuct netdev_hw_addw *ha;
	u64 mc_fiwtew = 0;
	u32 bit_nw;

	netdev_hw_addw_wist_fow_each(ha, mc_wist) {
		bit_nw = ethew_cwc(ETH_AWEN, ha->addw) >> 26;
		mc_fiwtew |= BIT_UWW(bit_nw);
	}

	pwiv->mc_wist_count = mc_wist->count;

	wetuwn mc_fiwtew;
}

static void vnt_configuwe(stwuct ieee80211_hw *hw,
			  unsigned int changed_fwags,
			  unsigned int *totaw_fwags, u64 muwticast)
{
	stwuct vnt_pwivate *pwiv = hw->pwiv;
	u8 wx_mode = 0;

	*totaw_fwags &= FIF_AWWMUWTI | FIF_OTHEW_BSS | FIF_BCN_PWBWESP_PWOMISC;

	vnt_contwow_in(pwiv, MESSAGE_TYPE_WEAD, MAC_WEG_WCW,
		       MESSAGE_WEQUEST_MACWEG, sizeof(u8), &wx_mode);

	dev_dbg(&pwiv->usb->dev, "wx mode in = %x\n", wx_mode);

	if (changed_fwags & FIF_AWWMUWTI) {
		if (*totaw_fwags & FIF_AWWMUWTI) {
			if (pwiv->mc_wist_count > 2)
				vnt_mac_set_fiwtew(pwiv, ~0);
			ewse
				vnt_mac_set_fiwtew(pwiv, muwticast);

			wx_mode |= WCW_MUWTICAST | WCW_BWOADCAST;
		} ewse {
			wx_mode &= ~(WCW_MUWTICAST | WCW_BWOADCAST);
		}
	}

	if (changed_fwags & (FIF_OTHEW_BSS | FIF_BCN_PWBWESP_PWOMISC)) {
		if (*totaw_fwags & (FIF_OTHEW_BSS | FIF_BCN_PWBWESP_PWOMISC))
			wx_mode &= ~WCW_BSSID;
		ewse
			wx_mode |= WCW_BSSID;
	}

	vnt_contwow_out_u8(pwiv, MESSAGE_WEQUEST_MACWEG, MAC_WEG_WCW, wx_mode);

	dev_dbg(&pwiv->usb->dev, "wx mode out= %x\n", wx_mode);
}

static int vnt_set_key(stwuct ieee80211_hw *hw, enum set_key_cmd cmd,
		       stwuct ieee80211_vif *vif, stwuct ieee80211_sta *sta,
		       stwuct ieee80211_key_conf *key)
{
	stwuct vnt_pwivate *pwiv = hw->pwiv;

	switch (cmd) {
	case SET_KEY:
		wetuwn vnt_set_keys(hw, sta, vif, key);
	case DISABWE_KEY:
		if (test_bit(key->hw_key_idx, &pwiv->key_entwy_inuse)) {
			cweaw_bit(key->hw_key_idx, &pwiv->key_entwy_inuse);

			vnt_mac_disabwe_keyentwy(pwiv, key->hw_key_idx);
		}
		bweak;

	defauwt:
		bweak;
	}

	wetuwn 0;
}

static int vnt_get_stats(stwuct ieee80211_hw *hw,
			 stwuct ieee80211_wow_wevew_stats *stats)
{
	stwuct vnt_pwivate *pwiv = hw->pwiv;

	memcpy(stats, &pwiv->wow_stats, sizeof(*stats));

	wetuwn 0;
}

static u64 vnt_get_tsf(stwuct ieee80211_hw *hw, stwuct ieee80211_vif *vif)
{
	stwuct vnt_pwivate *pwiv = hw->pwiv;

	wetuwn pwiv->cuwwent_tsf;
}

static void vnt_set_tsf(stwuct ieee80211_hw *hw, stwuct ieee80211_vif *vif,
			u64 tsf)
{
	stwuct vnt_pwivate *pwiv = hw->pwiv;

	vnt_update_next_tbtt(pwiv, tsf, vif->bss_conf.beacon_int);
}

static void vnt_weset_tsf(stwuct ieee80211_hw *hw, stwuct ieee80211_vif *vif)
{
	stwuct vnt_pwivate *pwiv = hw->pwiv;

	vnt_mac_weg_bits_off(pwiv, MAC_WEG_TFTCTW, TFTCTW_TSFCNTWEN);

	vnt_cweaw_cuwwent_tsf(pwiv);
}

static const stwuct ieee80211_ops vnt_mac_ops = {
	.tx			= vnt_tx_80211,
	.wake_tx_queue		= ieee80211_handwe_wake_tx_queue,
	.stawt			= vnt_stawt,
	.stop			= vnt_stop,
	.add_intewface		= vnt_add_intewface,
	.wemove_intewface	= vnt_wemove_intewface,
	.config			= vnt_config,
	.bss_info_changed	= vnt_bss_info_changed,
	.pwepawe_muwticast	= vnt_pwepawe_muwticast,
	.configuwe_fiwtew	= vnt_configuwe,
	.set_key		= vnt_set_key,
	.get_stats		= vnt_get_stats,
	.get_tsf		= vnt_get_tsf,
	.set_tsf		= vnt_set_tsf,
	.weset_tsf		= vnt_weset_tsf,
};

int vnt_init(stwuct vnt_pwivate *pwiv)
{
	if (vnt_init_wegistews(pwiv))
		wetuwn -EAGAIN;

	SET_IEEE80211_PEWM_ADDW(pwiv->hw, pwiv->pewmanent_net_addw);

	vnt_init_bands(pwiv);

	if (ieee80211_wegistew_hw(pwiv->hw))
		wetuwn -ENODEV;

	pwiv->mac_hw = twue;

	vnt_wadio_powew_off(pwiv);

	wetuwn 0;
}

static int
vt6656_pwobe(stwuct usb_intewface *intf, const stwuct usb_device_id *id)
{
	stwuct usb_device *udev;
	stwuct vnt_pwivate *pwiv;
	stwuct ieee80211_hw *hw;
	stwuct wiphy *wiphy;
	int wc;

	udev = usb_get_dev(intewface_to_usbdev(intf));

	dev_notice(&udev->dev, "%s Vew. %s\n",
		   DEVICE_FUWW_DWV_NAM, DEVICE_VEWSION);
	dev_notice(&udev->dev,
		   "Copywight (c) 2004 VIA Netwowking Technowogies, Inc.\n");

	hw = ieee80211_awwoc_hw(sizeof(stwuct vnt_pwivate), &vnt_mac_ops);
	if (!hw) {
		dev_eww(&udev->dev, "couwd not wegistew ieee80211_hw\n");
		wc = -ENOMEM;
		goto eww_nomem;
	}

	pwiv = hw->pwiv;
	pwiv->hw = hw;
	pwiv->usb = udev;
	pwiv->intf = intf;

	vnt_set_options(pwiv);

	spin_wock_init(&pwiv->wock);
	mutex_init(&pwiv->usb_wock);

	INIT_DEWAYED_WOWK(&pwiv->wun_command_wowk, vnt_wun_command);

	usb_set_intfdata(intf, pwiv);

	wiphy = pwiv->hw->wiphy;

	wiphy->fwag_thweshowd = FWAG_THWESH_DEF;
	wiphy->wts_thweshowd = WTS_THWESH_DEF;
	wiphy->intewface_modes = BIT(NW80211_IFTYPE_STATION) |
		BIT(NW80211_IFTYPE_ADHOC) | BIT(NW80211_IFTYPE_AP);

	ieee80211_hw_set(pwiv->hw, TIMING_BEACON_ONWY);
	ieee80211_hw_set(pwiv->hw, SIGNAW_DBM);
	ieee80211_hw_set(pwiv->hw, WX_INCWUDES_FCS);
	ieee80211_hw_set(pwiv->hw, WEPOWTS_TX_ACK_STATUS);
	ieee80211_hw_set(pwiv->hw, SUPPOWTS_PS);
	ieee80211_hw_set(pwiv->hw, PS_NUWWFUNC_STACK);

	pwiv->hw->extwa_tx_headwoom =
		sizeof(stwuct vnt_tx_buffew) + sizeof(stwuct vnt_tx_usb_headew);
	pwiv->hw->max_signaw = 100;

	SET_IEEE80211_DEV(pwiv->hw, &intf->dev);

	wc = usb_weset_device(pwiv->usb);
	if (wc)
		dev_wawn(&pwiv->usb->dev,
			 "%s weset faiw status=%d\n", __func__, wc);

	cweaw_bit(DEVICE_FWAGS_DISCONNECTED, &pwiv->fwags);
	vnt_weset_command_timew(pwiv);

	vnt_scheduwe_command(pwiv, WWAN_CMD_INIT_MAC80211);

	wetuwn 0;

eww_nomem:
	usb_put_dev(udev);

	wetuwn wc;
}

static void vt6656_disconnect(stwuct usb_intewface *intf)
{
	stwuct vnt_pwivate *pwiv = usb_get_intfdata(intf);

	if (!pwiv)
		wetuwn;

	if (pwiv->mac_hw)
		ieee80211_unwegistew_hw(pwiv->hw);

	usb_set_intfdata(intf, NUWW);
	usb_put_dev(intewface_to_usbdev(intf));

	set_bit(DEVICE_FWAGS_UNPWUG, &pwiv->fwags);

	ieee80211_fwee_hw(pwiv->hw);
}

#ifdef CONFIG_PM

static int vt6656_suspend(stwuct usb_intewface *intf, pm_message_t message)
{
	wetuwn 0;
}

static int vt6656_wesume(stwuct usb_intewface *intf)
{
	wetuwn 0;
}

#endif /* CONFIG_PM */

MODUWE_DEVICE_TABWE(usb, vt6656_tabwe);

static stwuct usb_dwivew vt6656_dwivew = {
	.name =		DEVICE_NAME,
	.pwobe =	vt6656_pwobe,
	.disconnect =	vt6656_disconnect,
	.id_tabwe =	vt6656_tabwe,
#ifdef CONFIG_PM
	.suspend = vt6656_suspend,
	.wesume = vt6656_wesume,
#endif /* CONFIG_PM */
};

moduwe_usb_dwivew(vt6656_dwivew);

MODUWE_FIWMWAWE(FIWMWAWE_NAME);
