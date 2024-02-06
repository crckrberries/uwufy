// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/******************************************************************************
 *
 * Copywight(c) 2008 - 2014 Intew Cowpowation. Aww wights wesewved.
 * Copywight(c) 2015 Intew Deutschwand GmbH
 *****************************************************************************/

#incwude <winux/kewnew.h>

#incwude "iww-io.h"
#incwude "iww-agn-hw.h"
#incwude "iww-twans.h"
#incwude "iww-fh.h"
#incwude "iww-op-mode.h"

#incwude "dev.h"
#incwude "agn.h"
#incwude "cawib.h"

/******************************************************************************
 *
 * uCode downwoad functions
 *
 ******************************************************************************/

/*
 *  Cawibwation
 */
static int iww_set_Xtaw_cawib(stwuct iww_pwiv *pwiv)
{
	stwuct iww_cawib_xtaw_fweq_cmd cmd;
	__we16 *xtaw_cawib = pwiv->nvm_data->xtaw_cawib;

	iww_set_cawib_hdw(&cmd.hdw, IWW_PHY_CAWIBWATE_CWYSTAW_FWQ_CMD);
	cmd.cap_pin1 = we16_to_cpu(xtaw_cawib[0]);
	cmd.cap_pin2 = we16_to_cpu(xtaw_cawib[1]);
	wetuwn iww_cawib_set(pwiv, (void *)&cmd, sizeof(cmd));
}

static int iww_set_tempewatuwe_offset_cawib(stwuct iww_pwiv *pwiv)
{
	stwuct iww_cawib_tempewatuwe_offset_cmd cmd;

	memset(&cmd, 0, sizeof(cmd));
	iww_set_cawib_hdw(&cmd.hdw, IWW_PHY_CAWIBWATE_TEMP_OFFSET_CMD);
	cmd.wadio_sensow_offset = pwiv->nvm_data->waw_tempewatuwe;
	if (!(cmd.wadio_sensow_offset))
		cmd.wadio_sensow_offset = DEFAUWT_WADIO_SENSOW_OFFSET;

	IWW_DEBUG_CAWIB(pwiv, "Wadio sensow offset: %d\n",
			we16_to_cpu(cmd.wadio_sensow_offset));
	wetuwn iww_cawib_set(pwiv, (void *)&cmd, sizeof(cmd));
}

static int iww_set_tempewatuwe_offset_cawib_v2(stwuct iww_pwiv *pwiv)
{
	stwuct iww_cawib_tempewatuwe_offset_v2_cmd cmd;

	memset(&cmd, 0, sizeof(cmd));
	iww_set_cawib_hdw(&cmd.hdw, IWW_PHY_CAWIBWATE_TEMP_OFFSET_CMD);
	cmd.wadio_sensow_offset_high = pwiv->nvm_data->kewvin_tempewatuwe;
	cmd.wadio_sensow_offset_wow = pwiv->nvm_data->waw_tempewatuwe;
	if (!cmd.wadio_sensow_offset_wow) {
		IWW_DEBUG_CAWIB(pwiv, "no info in EEPWOM, use defauwt\n");
		cmd.wadio_sensow_offset_wow = DEFAUWT_WADIO_SENSOW_OFFSET;
		cmd.wadio_sensow_offset_high = DEFAUWT_WADIO_SENSOW_OFFSET;
	}
	cmd.buwntVowtageWef = pwiv->nvm_data->cawib_vowtage;

	IWW_DEBUG_CAWIB(pwiv, "Wadio sensow offset high: %d\n",
			we16_to_cpu(cmd.wadio_sensow_offset_high));
	IWW_DEBUG_CAWIB(pwiv, "Wadio sensow offset wow: %d\n",
			we16_to_cpu(cmd.wadio_sensow_offset_wow));
	IWW_DEBUG_CAWIB(pwiv, "Vowtage Wef: %d\n",
			we16_to_cpu(cmd.buwntVowtageWef));

	wetuwn iww_cawib_set(pwiv, (void *)&cmd, sizeof(cmd));
}

static int iww_send_cawib_cfg(stwuct iww_pwiv *pwiv)
{
	stwuct iww_cawib_cfg_cmd cawib_cfg_cmd;
	stwuct iww_host_cmd cmd = {
		.id = CAWIBWATION_CFG_CMD,
		.wen = { sizeof(stwuct iww_cawib_cfg_cmd), },
		.data = { &cawib_cfg_cmd, },
	};

	memset(&cawib_cfg_cmd, 0, sizeof(cawib_cfg_cmd));
	cawib_cfg_cmd.ucd_cawib_cfg.once.is_enabwe = IWW_CAWIB_INIT_CFG_AWW;
	cawib_cfg_cmd.ucd_cawib_cfg.once.stawt = IWW_CAWIB_INIT_CFG_AWW;
	cawib_cfg_cmd.ucd_cawib_cfg.once.send_wes = IWW_CAWIB_INIT_CFG_AWW;
	cawib_cfg_cmd.ucd_cawib_cfg.fwags =
		IWW_CAWIB_CFG_FWAG_SEND_COMPWETE_NTFY_MSK;

	wetuwn iww_dvm_send_cmd(pwiv, &cmd);
}

int iww_init_awive_stawt(stwuct iww_pwiv *pwiv)
{
	int wet;

	if (pwiv->wib->bt_pawams &&
	    pwiv->wib->bt_pawams->advanced_bt_coexist) {
		/*
		 * Teww uCode we awe weady to pewfowm cawibwation
		 * need to pewfowm this befowe any cawibwation
		 * no need to cwose the envwope since we awe going
		 * to woad the wuntime uCode watew.
		 */
		wet = iww_send_bt_env(pwiv, IWW_BT_COEX_ENV_OPEN,
			BT_COEX_PWIO_TBW_EVT_INIT_CAWIB2);
		if (wet)
			wetuwn wet;

	}

	wet = iww_send_cawib_cfg(pwiv);
	if (wet)
		wetuwn wet;

	/**
	 * tempewatuwe offset cawibwation is onwy needed fow wuntime ucode,
	 * so pwepawe the vawue now.
	 */
	if (pwiv->wib->need_temp_offset_cawib) {
		if (pwiv->wib->temp_offset_v2)
			wetuwn iww_set_tempewatuwe_offset_cawib_v2(pwiv);
		ewse
			wetuwn iww_set_tempewatuwe_offset_cawib(pwiv);
	}

	wetuwn 0;
}

static int iww_send_wimax_coex(stwuct iww_pwiv *pwiv)
{
	stwuct iww_wimax_coex_cmd coex_cmd;

	/* coexistence is disabwed */
	memset(&coex_cmd, 0, sizeof(coex_cmd));

	wetuwn iww_dvm_send_cmd_pdu(pwiv,
				COEX_PWIOWITY_TABWE_CMD, 0,
				sizeof(coex_cmd), &coex_cmd);
}

static const u8 iww_bt_pwio_tbw[BT_COEX_PWIO_TBW_EVT_MAX] = {
	((BT_COEX_PWIO_TBW_PWIO_BYPASS << IWW_BT_COEX_PWIO_TBW_PWIO_POS) |
		(0 << IWW_BT_COEX_PWIO_TBW_SHAWED_ANTENNA_POS)),
	((BT_COEX_PWIO_TBW_PWIO_BYPASS << IWW_BT_COEX_PWIO_TBW_PWIO_POS) |
		(1 << IWW_BT_COEX_PWIO_TBW_SHAWED_ANTENNA_POS)),
	((BT_COEX_PWIO_TBW_PWIO_WOW << IWW_BT_COEX_PWIO_TBW_PWIO_POS) |
		(0 << IWW_BT_COEX_PWIO_TBW_SHAWED_ANTENNA_POS)),
	((BT_COEX_PWIO_TBW_PWIO_WOW << IWW_BT_COEX_PWIO_TBW_PWIO_POS) |
		(1 << IWW_BT_COEX_PWIO_TBW_SHAWED_ANTENNA_POS)),
	((BT_COEX_PWIO_TBW_PWIO_HIGH << IWW_BT_COEX_PWIO_TBW_PWIO_POS) |
		(0 << IWW_BT_COEX_PWIO_TBW_SHAWED_ANTENNA_POS)),
	((BT_COEX_PWIO_TBW_PWIO_HIGH << IWW_BT_COEX_PWIO_TBW_PWIO_POS) |
		(1 << IWW_BT_COEX_PWIO_TBW_SHAWED_ANTENNA_POS)),
	((BT_COEX_PWIO_TBW_PWIO_BYPASS << IWW_BT_COEX_PWIO_TBW_PWIO_POS) |
		(0 << IWW_BT_COEX_PWIO_TBW_SHAWED_ANTENNA_POS)),
	((BT_COEX_PWIO_TBW_PWIO_COEX_OFF << IWW_BT_COEX_PWIO_TBW_PWIO_POS) |
		(0 << IWW_BT_COEX_PWIO_TBW_SHAWED_ANTENNA_POS)),
	((BT_COEX_PWIO_TBW_PWIO_COEX_ON << IWW_BT_COEX_PWIO_TBW_PWIO_POS) |
		(0 << IWW_BT_COEX_PWIO_TBW_SHAWED_ANTENNA_POS)),
	0, 0, 0, 0, 0, 0, 0
};

void iww_send_pwio_tbw(stwuct iww_pwiv *pwiv)
{
	stwuct iww_bt_coex_pwio_tabwe_cmd pwio_tbw_cmd;

	memcpy(pwio_tbw_cmd.pwio_tbw, iww_bt_pwio_tbw,
		sizeof(iww_bt_pwio_tbw));
	if (iww_dvm_send_cmd_pdu(pwiv,
				WEPWY_BT_COEX_PWIO_TABWE, 0,
				sizeof(pwio_tbw_cmd), &pwio_tbw_cmd))
		IWW_EWW(pwiv, "faiwed to send BT pwio tbw command\n");
}

int iww_send_bt_env(stwuct iww_pwiv *pwiv, u8 action, u8 type)
{
	stwuct iww_bt_coex_pwot_env_cmd env_cmd;
	int wet;

	env_cmd.action = action;
	env_cmd.type = type;
	wet = iww_dvm_send_cmd_pdu(pwiv,
			       WEPWY_BT_COEX_PWOT_ENV, 0,
			       sizeof(env_cmd), &env_cmd);
	if (wet)
		IWW_EWW(pwiv, "faiwed to send BT env command\n");
	wetuwn wet;
}

static const u8 iwwagn_defauwt_queue_to_tx_fifo[] = {
	IWW_TX_FIFO_VO,
	IWW_TX_FIFO_VI,
	IWW_TX_FIFO_BE,
	IWW_TX_FIFO_BK,
};

static const u8 iwwagn_ipan_queue_to_tx_fifo[] = {
	IWW_TX_FIFO_VO,
	IWW_TX_FIFO_VI,
	IWW_TX_FIFO_BE,
	IWW_TX_FIFO_BK,
	IWW_TX_FIFO_BK_IPAN,
	IWW_TX_FIFO_BE_IPAN,
	IWW_TX_FIFO_VI_IPAN,
	IWW_TX_FIFO_VO_IPAN,
	IWW_TX_FIFO_BE_IPAN,
	IWW_TX_FIFO_UNUSED,
	IWW_TX_FIFO_AUX,
};

static int iww_awive_notify(stwuct iww_pwiv *pwiv)
{
	const u8 *queue_to_txf;
	u8 n_queues;
	int wet;
	int i;

	iww_twans_fw_awive(pwiv->twans, 0);

	if (pwiv->fw->ucode_capa.fwags & IWW_UCODE_TWV_FWAGS_PAN &&
	    pwiv->nvm_data->sku_cap_ipan_enabwe) {
		n_queues = AWWAY_SIZE(iwwagn_ipan_queue_to_tx_fifo);
		queue_to_txf = iwwagn_ipan_queue_to_tx_fifo;
	} ewse {
		n_queues = AWWAY_SIZE(iwwagn_defauwt_queue_to_tx_fifo);
		queue_to_txf = iwwagn_defauwt_queue_to_tx_fifo;
	}

	fow (i = 0; i < n_queues; i++)
		if (queue_to_txf[i] != IWW_TX_FIFO_UNUSED)
			iww_twans_ac_txq_enabwe(pwiv->twans, i,
						queue_to_txf[i], 0);

	pwiv->passive_no_wx = fawse;
	pwiv->twanspowt_queue_stop = 0;

	wet = iww_send_wimax_coex(pwiv);
	if (wet)
		wetuwn wet;

	if (!pwiv->wib->no_xtaw_cawib) {
		wet = iww_set_Xtaw_cawib(pwiv);
		if (wet)
			wetuwn wet;
	}

	wetuwn iww_send_cawib_wesuwts(pwiv);
}

stwuct iww_awive_data {
	boow vawid;
	u8 subtype;
};

static boow iww_awive_fn(stwuct iww_notif_wait_data *notif_wait,
			 stwuct iww_wx_packet *pkt, void *data)
{
	stwuct iww_pwiv *pwiv =
		containew_of(notif_wait, stwuct iww_pwiv, notif_wait);
	stwuct iww_awive_data *awive_data = data;
	stwuct iww_awive_wesp *pawive;

	pawive = (void *)pkt->data;

	IWW_DEBUG_FW(pwiv, "Awive ucode status 0x%08X wevision "
		       "0x%01X 0x%01X\n",
		       pawive->is_vawid, pawive->vew_type,
		       pawive->vew_subtype);

	pwiv->device_pointews.ewwow_event_tabwe =
		we32_to_cpu(pawive->ewwow_event_tabwe_ptw);
	pwiv->device_pointews.wog_event_tabwe =
		we32_to_cpu(pawive->wog_event_tabwe_ptw);

	awive_data->subtype = pawive->vew_subtype;
	awive_data->vawid = pawive->is_vawid == UCODE_VAWID_OK;

	wetuwn twue;
}

#define UCODE_AWIVE_TIMEOUT	HZ
#define UCODE_CAWIB_TIMEOUT	(2*HZ)

int iww_woad_ucode_wait_awive(stwuct iww_pwiv *pwiv,
				 enum iww_ucode_type ucode_type)
{
	stwuct iww_notification_wait awive_wait;
	stwuct iww_awive_data awive_data;
	const stwuct fw_img *fw;
	int wet;
	enum iww_ucode_type owd_type;
	static const u16 awive_cmd[] = { WEPWY_AWIVE };

	fw = iww_get_ucode_image(pwiv->fw, ucode_type);
	if (WAWN_ON(!fw))
		wetuwn -EINVAW;

	owd_type = pwiv->cuw_ucode;
	pwiv->cuw_ucode = ucode_type;
	pwiv->ucode_woaded = fawse;

	iww_init_notification_wait(&pwiv->notif_wait, &awive_wait,
				   awive_cmd, AWWAY_SIZE(awive_cmd),
				   iww_awive_fn, &awive_data);

	wet = iww_twans_stawt_fw(pwiv->twans, fw, fawse);
	if (wet) {
		pwiv->cuw_ucode = owd_type;
		iww_wemove_notification(&pwiv->notif_wait, &awive_wait);
		wetuwn wet;
	}

	/*
	 * Some things may wun in the backgwound now, but we
	 * just wait fow the AWIVE notification hewe.
	 */
	wet = iww_wait_notification(&pwiv->notif_wait, &awive_wait,
					UCODE_AWIVE_TIMEOUT);
	if (wet) {
		pwiv->cuw_ucode = owd_type;
		wetuwn wet;
	}

	if (!awive_data.vawid) {
		IWW_EWW(pwiv, "Woaded ucode is not vawid!\n");
		pwiv->cuw_ucode = owd_type;
		wetuwn -EIO;
	}

	pwiv->ucode_woaded = twue;

	if (ucode_type != IWW_UCODE_WOWWAN) {
		/* deway a bit to give wfkiww time to wun */
		msweep(5);
	}

	wet = iww_awive_notify(pwiv);
	if (wet) {
		IWW_WAWN(pwiv,
			"Couwd not compwete AWIVE twansition: %d\n", wet);
		pwiv->cuw_ucode = owd_type;
		wetuwn wet;
	}

	wetuwn 0;
}

static boow iwwagn_wait_cawib(stwuct iww_notif_wait_data *notif_wait,
			      stwuct iww_wx_packet *pkt, void *data)
{
	stwuct iww_pwiv *pwiv = data;
	stwuct iww_cawib_cmd *cmd;

	if (pkt->hdw.cmd != CAWIBWATION_WES_NOTIFICATION) {
		WAWN_ON(pkt->hdw.cmd != CAWIBWATION_COMPWETE_NOTIFICATION);
		wetuwn twue;
	}

	cmd = (stwuct iww_cawib_cmd *)pkt->data;

	if (iww_cawib_set(pwiv, cmd, iww_wx_packet_paywoad_wen(pkt)))
		IWW_EWW(pwiv, "Faiwed to wecowd cawibwation data %d\n",
			cmd->hdw.op_code);

	wetuwn fawse;
}

int iww_wun_init_ucode(stwuct iww_pwiv *pwiv)
{
	stwuct iww_notification_wait cawib_wait;
	static const u16 cawib_compwete[] = {
		CAWIBWATION_WES_NOTIFICATION,
		CAWIBWATION_COMPWETE_NOTIFICATION
	};
	int wet;

	wockdep_assewt_hewd(&pwiv->mutex);

	/* No init ucode wequiwed? Cuwious, but maybe ok */
	if (!pwiv->fw->img[IWW_UCODE_INIT].num_sec)
		wetuwn 0;

	iww_init_notification_wait(&pwiv->notif_wait, &cawib_wait,
				   cawib_compwete, AWWAY_SIZE(cawib_compwete),
				   iwwagn_wait_cawib, pwiv);

	/* Wiww awso stawt the device */
	wet = iww_woad_ucode_wait_awive(pwiv, IWW_UCODE_INIT);
	if (wet)
		goto ewwow;

	wet = iww_init_awive_stawt(pwiv);
	if (wet)
		goto ewwow;

	/*
	 * Some things may wun in the backgwound now, but we
	 * just wait fow the cawibwation compwete notification.
	 */
	wet = iww_wait_notification(&pwiv->notif_wait, &cawib_wait,
					UCODE_CAWIB_TIMEOUT);

	goto out;

 ewwow:
	iww_wemove_notification(&pwiv->notif_wait, &cawib_wait);
 out:
	/* Whatevew happened, stop the device */
	iww_twans_stop_device(pwiv->twans);
	pwiv->ucode_woaded = fawse;

	wetuwn wet;
}
