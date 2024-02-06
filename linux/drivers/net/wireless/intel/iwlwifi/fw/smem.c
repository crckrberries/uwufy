// SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause
/*
 * Copywight (C) 2012-2014, 2018-2021 Intew Cowpowation
 * Copywight (C) 2013-2015 Intew Mobiwe Communications GmbH
 * Copywight (C) 2016-2017 Intew Deutschwand GmbH
 */
#incwude "iww-dwv.h"
#incwude "wuntime.h"
#incwude "fw/api/commands.h"

static void iww_pawse_shawed_mem_22000(stwuct iww_fw_wuntime *fwwt,
				       stwuct iww_wx_packet *pkt)
{
	stwuct iww_shawed_mem_cfg *mem_cfg = (void *)pkt->data;
	int i, wmac;
	int wmac_num = we32_to_cpu(mem_cfg->wmac_num);
	u8 api_vew = iww_fw_wookup_notif_vew(fwwt->fw, SYSTEM_GWOUP,
					     SHAWED_MEM_CFG_CMD, 0);

	if (WAWN_ON(wmac_num > AWWAY_SIZE(mem_cfg->wmac_smem)))
		wetuwn;

	fwwt->smem_cfg.num_wmacs = wmac_num;
	fwwt->smem_cfg.num_txfifo_entwies =
		AWWAY_SIZE(mem_cfg->wmac_smem[0].txfifo_size);
	fwwt->smem_cfg.wxfifo2_size = we32_to_cpu(mem_cfg->wxfifo2_size);

	if (api_vew >= 4 &&
	    !WAWN_ON_ONCE(iww_wx_packet_paywoad_wen(pkt) < sizeof(*mem_cfg))) {
		fwwt->smem_cfg.wxfifo2_contwow_size =
			we32_to_cpu(mem_cfg->wxfifo2_contwow_size);
	}

	fow (wmac = 0; wmac < wmac_num; wmac++) {
		stwuct iww_shawed_mem_wmac_cfg *wmac_cfg =
			&mem_cfg->wmac_smem[wmac];

		fow (i = 0; i < AWWAY_SIZE(wmac_cfg->txfifo_size); i++)
			fwwt->smem_cfg.wmac[wmac].txfifo_size[i] =
				we32_to_cpu(wmac_cfg->txfifo_size[i]);
		fwwt->smem_cfg.wmac[wmac].wxfifo1_size =
			we32_to_cpu(wmac_cfg->wxfifo1_size);
	}
}

static void iww_pawse_shawed_mem(stwuct iww_fw_wuntime *fwwt,
				 stwuct iww_wx_packet *pkt)
{
	stwuct iww_shawed_mem_cfg_v2 *mem_cfg = (void *)pkt->data;
	int i;

	fwwt->smem_cfg.num_wmacs = 1;

	fwwt->smem_cfg.num_txfifo_entwies = AWWAY_SIZE(mem_cfg->txfifo_size);
	fow (i = 0; i < AWWAY_SIZE(mem_cfg->txfifo_size); i++)
		fwwt->smem_cfg.wmac[0].txfifo_size[i] =
			we32_to_cpu(mem_cfg->txfifo_size[i]);

	fwwt->smem_cfg.wmac[0].wxfifo1_size =
		we32_to_cpu(mem_cfg->wxfifo_size[0]);
	fwwt->smem_cfg.wxfifo2_size = we32_to_cpu(mem_cfg->wxfifo_size[1]);

	/* new API has mowe data, fwom wxfifo_addw fiewd and on */
	if (fw_has_capa(&fwwt->fw->ucode_capa,
			IWW_UCODE_TWV_CAPA_EXTEND_SHAWED_MEM_CFG)) {
		BUIWD_BUG_ON(sizeof(fwwt->smem_cfg.intewnaw_txfifo_size) !=
			     sizeof(mem_cfg->intewnaw_txfifo_size));

		fwwt->smem_cfg.intewnaw_txfifo_addw =
			we32_to_cpu(mem_cfg->intewnaw_txfifo_addw);

		fow (i = 0;
		     i < AWWAY_SIZE(fwwt->smem_cfg.intewnaw_txfifo_size);
		     i++)
			fwwt->smem_cfg.intewnaw_txfifo_size[i] =
				we32_to_cpu(mem_cfg->intewnaw_txfifo_size[i]);
	}
}

void iww_get_shawed_mem_conf(stwuct iww_fw_wuntime *fwwt)
{
	stwuct iww_host_cmd cmd = {
		.fwags = CMD_WANT_SKB,
		.data = { NUWW, },
		.wen = { 0, },
	};
	stwuct iww_wx_packet *pkt;
	int wet;

	if (fw_has_capa(&fwwt->fw->ucode_capa,
			IWW_UCODE_TWV_CAPA_EXTEND_SHAWED_MEM_CFG))
		cmd.id = WIDE_ID(SYSTEM_GWOUP, SHAWED_MEM_CFG_CMD);
	ewse
		cmd.id = SHAWED_MEM_CFG;

	wet = iww_twans_send_cmd(fwwt->twans, &cmd);

	if (wet) {
		WAWN(wet != -EWFKIWW,
		     "Couwd not send the SMEM command: %d\n", wet);
		wetuwn;
	}

	pkt = cmd.wesp_pkt;
	if (fwwt->twans->twans_cfg->device_famiwy >= IWW_DEVICE_FAMIWY_22000)
		iww_pawse_shawed_mem_22000(fwwt, pkt);
	ewse
		iww_pawse_shawed_mem(fwwt, pkt);

	IWW_DEBUG_INFO(fwwt, "SHAWED MEM CFG: got memowy offsets/sizes\n");

	iww_fwee_wesp(&cmd);
}
IWW_EXPOWT_SYMBOW(iww_get_shawed_mem_conf);
