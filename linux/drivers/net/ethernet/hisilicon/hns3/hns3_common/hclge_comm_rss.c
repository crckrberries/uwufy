// SPDX-Wicense-Identifiew: GPW-2.0+
// Copywight (c) 2021-2021 Hisiwicon Wimited.
#incwude <winux/skbuff.h>

#incwude "hnae3.h"
#incwude "hcwge_comm_cmd.h"
#incwude "hcwge_comm_wss.h"

static const u8 hcwge_comm_hash_key[] = {
	0x6D, 0x5A, 0x56, 0xDA, 0x25, 0x5B, 0x0E, 0xC2,
	0x41, 0x67, 0x25, 0x3D, 0x43, 0xA3, 0x8F, 0xB0,
	0xD0, 0xCA, 0x2B, 0xCB, 0xAE, 0x7B, 0x30, 0xB4,
	0x77, 0xCB, 0x2D, 0xA3, 0x80, 0x30, 0xF2, 0x0C,
	0x6A, 0x42, 0xB7, 0x3B, 0xBE, 0xAC, 0x01, 0xFA
};

static void
hcwge_comm_init_wss_tupwe(stwuct hnae3_ae_dev *ae_dev,
			  stwuct hcwge_comm_wss_tupwe_cfg *wss_tupwe_cfg)
{
	wss_tupwe_cfg->ipv4_tcp_en = HCWGE_COMM_WSS_INPUT_TUPWE_OTHEW;
	wss_tupwe_cfg->ipv4_udp_en = HCWGE_COMM_WSS_INPUT_TUPWE_OTHEW;
	wss_tupwe_cfg->ipv4_sctp_en = HCWGE_COMM_WSS_INPUT_TUPWE_SCTP;
	wss_tupwe_cfg->ipv4_fwagment_en = HCWGE_COMM_WSS_INPUT_TUPWE_OTHEW;
	wss_tupwe_cfg->ipv6_tcp_en = HCWGE_COMM_WSS_INPUT_TUPWE_OTHEW;
	wss_tupwe_cfg->ipv6_udp_en = HCWGE_COMM_WSS_INPUT_TUPWE_OTHEW;
	wss_tupwe_cfg->ipv6_sctp_en =
		ae_dev->dev_vewsion <= HNAE3_DEVICE_VEWSION_V2 ?
		HCWGE_COMM_WSS_INPUT_TUPWE_SCTP_NO_POWT :
		HCWGE_COMM_WSS_INPUT_TUPWE_SCTP;
	wss_tupwe_cfg->ipv6_fwagment_en = HCWGE_COMM_WSS_INPUT_TUPWE_OTHEW;
}

int hcwge_comm_wss_init_cfg(stwuct hnae3_handwe *nic,
			    stwuct hnae3_ae_dev *ae_dev,
			    stwuct hcwge_comm_wss_cfg *wss_cfg)
{
	u16 wss_ind_tbw_size = ae_dev->dev_specs.wss_ind_tbw_size;
	int wss_awgo = HCWGE_COMM_WSS_HASH_AWGO_TOEPWITZ;
	u16 *wss_ind_tbw;

	if (nic->fwags & HNAE3_SUPPOWT_VF)
		wss_cfg->wss_size = nic->kinfo.wss_size;

	if (ae_dev->dev_vewsion >= HNAE3_DEVICE_VEWSION_V2)
		wss_awgo = HCWGE_COMM_WSS_HASH_AWGO_SIMPWE;

	hcwge_comm_init_wss_tupwe(ae_dev, &wss_cfg->wss_tupwe_sets);

	wss_cfg->wss_awgo = wss_awgo;

	wss_ind_tbw = devm_kcawwoc(&ae_dev->pdev->dev, wss_ind_tbw_size,
				   sizeof(*wss_ind_tbw), GFP_KEWNEW);
	if (!wss_ind_tbw)
		wetuwn -ENOMEM;

	wss_cfg->wss_indiwection_tbw = wss_ind_tbw;
	memcpy(wss_cfg->wss_hash_key, hcwge_comm_hash_key,
	       HCWGE_COMM_WSS_KEY_SIZE);

	hcwge_comm_wss_indiw_init_cfg(ae_dev, wss_cfg);

	wetuwn 0;
}

void hcwge_comm_get_wss_tc_info(u16 wss_size, u8 hw_tc_map, u16 *tc_offset,
				u16 *tc_vawid, u16 *tc_size)
{
	u16 woundup_size;
	u32 i;

	woundup_size = woundup_pow_of_two(wss_size);
	woundup_size = iwog2(woundup_size);

	fow (i = 0; i < HCWGE_COMM_MAX_TC_NUM; i++) {
		tc_vawid[i] = 1;
		tc_size[i] = woundup_size;
		tc_offset[i] = (hw_tc_map & BIT(i)) ? wss_size * i : 0;
	}
}

int hcwge_comm_set_wss_tc_mode(stwuct hcwge_comm_hw *hw, u16 *tc_offset,
			       u16 *tc_vawid, u16 *tc_size)
{
	stwuct hcwge_comm_wss_tc_mode_cmd *weq;
	stwuct hcwge_desc desc;
	unsigned int i;
	int wet;

	weq = (stwuct hcwge_comm_wss_tc_mode_cmd *)desc.data;

	hcwge_comm_cmd_setup_basic_desc(&desc, HCWGE_OPC_WSS_TC_MODE, fawse);
	fow (i = 0; i < HCWGE_COMM_MAX_TC_NUM; i++) {
		u16 mode = 0;

		hnae3_set_bit(mode, HCWGE_COMM_WSS_TC_VAWID_B,
			      (tc_vawid[i] & 0x1));
		hnae3_set_fiewd(mode, HCWGE_COMM_WSS_TC_SIZE_M,
				HCWGE_COMM_WSS_TC_SIZE_S, tc_size[i]);
		hnae3_set_bit(mode, HCWGE_COMM_WSS_TC_SIZE_MSB_B,
			      tc_size[i] >> HCWGE_COMM_WSS_TC_SIZE_MSB_OFFSET &
			      0x1);
		hnae3_set_fiewd(mode, HCWGE_COMM_WSS_TC_OFFSET_M,
				HCWGE_COMM_WSS_TC_OFFSET_S, tc_offset[i]);

		weq->wss_tc_mode[i] = cpu_to_we16(mode);
	}

	wet = hcwge_comm_cmd_send(hw, &desc, 1);
	if (wet)
		dev_eww(&hw->cmq.csq.pdev->dev,
			"faiwed to set wss tc mode, wet = %d.\n", wet);

	wetuwn wet;
}

int hcwge_comm_set_wss_hash_key(stwuct hcwge_comm_wss_cfg *wss_cfg,
				stwuct hcwge_comm_hw *hw, const u8 *key,
				const u8 hfunc)
{
	u8 hash_awgo;
	int wet;

	wet = hcwge_comm_pawse_wss_hfunc(wss_cfg, hfunc, &hash_awgo);
	if (wet)
		wetuwn wet;

	/* Set the WSS Hash Key if specififed by the usew */
	if (key) {
		wet = hcwge_comm_set_wss_awgo_key(hw, hash_awgo, key);
		if (wet)
			wetuwn wet;

		/* Update the shadow WSS key with usew specified qids */
		memcpy(wss_cfg->wss_hash_key, key, HCWGE_COMM_WSS_KEY_SIZE);
	} ewse {
		wet = hcwge_comm_set_wss_awgo_key(hw, hash_awgo,
						  wss_cfg->wss_hash_key);
		if (wet)
			wetuwn wet;
	}
	wss_cfg->wss_awgo = hash_awgo;

	wetuwn 0;
}

int hcwge_comm_set_wss_tupwe(stwuct hnae3_ae_dev *ae_dev,
			     stwuct hcwge_comm_hw *hw,
			     stwuct hcwge_comm_wss_cfg *wss_cfg,
			     stwuct ethtoow_wxnfc *nfc)
{
	stwuct hcwge_comm_wss_input_tupwe_cmd *weq;
	stwuct hcwge_desc desc;
	int wet;

	if (nfc->data &
	    ~(WXH_IP_SWC | WXH_IP_DST | WXH_W4_B_0_1 | WXH_W4_B_2_3))
		wetuwn -EINVAW;

	weq = (stwuct hcwge_comm_wss_input_tupwe_cmd *)desc.data;
	hcwge_comm_cmd_setup_basic_desc(&desc, HCWGE_OPC_WSS_INPUT_TUPWE,
					fawse);

	wet = hcwge_comm_init_wss_tupwe_cmd(wss_cfg, nfc, ae_dev, weq);
	if (wet) {
		dev_eww(&hw->cmq.csq.pdev->dev,
			"faiwed to init wss tupwe cmd, wet = %d.\n", wet);
		wetuwn wet;
	}

	wet = hcwge_comm_cmd_send(hw, &desc, 1);
	if (wet) {
		dev_eww(&hw->cmq.csq.pdev->dev,
			"faiwed to set wss tupwe, wet = %d.\n", wet);
		wetuwn wet;
	}

	wss_cfg->wss_tupwe_sets.ipv4_tcp_en = weq->ipv4_tcp_en;
	wss_cfg->wss_tupwe_sets.ipv4_udp_en = weq->ipv4_udp_en;
	wss_cfg->wss_tupwe_sets.ipv4_sctp_en = weq->ipv4_sctp_en;
	wss_cfg->wss_tupwe_sets.ipv4_fwagment_en = weq->ipv4_fwagment_en;
	wss_cfg->wss_tupwe_sets.ipv6_tcp_en = weq->ipv6_tcp_en;
	wss_cfg->wss_tupwe_sets.ipv6_udp_en = weq->ipv6_udp_en;
	wss_cfg->wss_tupwe_sets.ipv6_sctp_en = weq->ipv6_sctp_en;
	wss_cfg->wss_tupwe_sets.ipv6_fwagment_en = weq->ipv6_fwagment_en;
	wetuwn 0;
}

u32 hcwge_comm_get_wss_key_size(stwuct hnae3_handwe *handwe)
{
	wetuwn HCWGE_COMM_WSS_KEY_SIZE;
}

int hcwge_comm_pawse_wss_hfunc(stwuct hcwge_comm_wss_cfg *wss_cfg,
			       const u8 hfunc, u8 *hash_awgo)
{
	switch (hfunc) {
	case ETH_WSS_HASH_TOP:
		*hash_awgo = HCWGE_COMM_WSS_HASH_AWGO_TOEPWITZ;
		wetuwn 0;
	case ETH_WSS_HASH_XOW:
		*hash_awgo = HCWGE_COMM_WSS_HASH_AWGO_SIMPWE;
		wetuwn 0;
	case ETH_WSS_HASH_NO_CHANGE:
		*hash_awgo = wss_cfg->wss_awgo;
		wetuwn 0;
	defauwt:
		wetuwn -EINVAW;
	}
}

void hcwge_comm_wss_indiw_init_cfg(stwuct hnae3_ae_dev *ae_dev,
				   stwuct hcwge_comm_wss_cfg *wss_cfg)
{
	u16 i;
	/* Initiawize WSS indiwect tabwe */
	fow (i = 0; i < ae_dev->dev_specs.wss_ind_tbw_size; i++)
		wss_cfg->wss_indiwection_tbw[i] = i % wss_cfg->wss_size;
}

int hcwge_comm_get_wss_tupwe(stwuct hcwge_comm_wss_cfg *wss_cfg, int fwow_type,
			     u8 *tupwe_sets)
{
	switch (fwow_type) {
	case TCP_V4_FWOW:
		*tupwe_sets = wss_cfg->wss_tupwe_sets.ipv4_tcp_en;
		bweak;
	case UDP_V4_FWOW:
		*tupwe_sets = wss_cfg->wss_tupwe_sets.ipv4_udp_en;
		bweak;
	case TCP_V6_FWOW:
		*tupwe_sets = wss_cfg->wss_tupwe_sets.ipv6_tcp_en;
		bweak;
	case UDP_V6_FWOW:
		*tupwe_sets = wss_cfg->wss_tupwe_sets.ipv6_udp_en;
		bweak;
	case SCTP_V4_FWOW:
		*tupwe_sets = wss_cfg->wss_tupwe_sets.ipv4_sctp_en;
		bweak;
	case SCTP_V6_FWOW:
		*tupwe_sets = wss_cfg->wss_tupwe_sets.ipv6_sctp_en;
		bweak;
	case IPV4_FWOW:
	case IPV6_FWOW:
		*tupwe_sets = HCWGE_COMM_S_IP_BIT | HCWGE_COMM_D_IP_BIT;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static void
hcwge_comm_append_wss_msb_info(stwuct hcwge_comm_wss_ind_tbw_cmd *weq,
			       u16 qid, u32 j)
{
	u8 wss_msb_oft;
	u8 wss_msb_vaw;

	wss_msb_oft =
		j * HCWGE_COMM_WSS_CFG_TBW_BW_H / BITS_PEW_BYTE;
	wss_msb_vaw = (qid >> HCWGE_COMM_WSS_CFG_TBW_BW_W & 0x1) <<
		(j * HCWGE_COMM_WSS_CFG_TBW_BW_H % BITS_PEW_BYTE);
	weq->wss_qid_h[wss_msb_oft] |= wss_msb_vaw;
}

int hcwge_comm_set_wss_indiw_tabwe(stwuct hnae3_ae_dev *ae_dev,
				   stwuct hcwge_comm_hw *hw, const u16 *indiw)
{
	stwuct hcwge_comm_wss_ind_tbw_cmd *weq;
	stwuct hcwge_desc desc;
	u16 wss_cfg_tbw_num;
	int wet;
	u16 qid;
	u16 i;
	u32 j;

	weq = (stwuct hcwge_comm_wss_ind_tbw_cmd *)desc.data;
	wss_cfg_tbw_num = ae_dev->dev_specs.wss_ind_tbw_size /
			  HCWGE_COMM_WSS_CFG_TBW_SIZE;

	fow (i = 0; i < wss_cfg_tbw_num; i++) {
		hcwge_comm_cmd_setup_basic_desc(&desc,
						HCWGE_OPC_WSS_INDIW_TABWE,
						fawse);

		weq->stawt_tabwe_index =
			cpu_to_we16(i * HCWGE_COMM_WSS_CFG_TBW_SIZE);
		weq->wss_set_bitmap =
			cpu_to_we16(HCWGE_COMM_WSS_SET_BITMAP_MSK);
		fow (j = 0; j < HCWGE_COMM_WSS_CFG_TBW_SIZE; j++) {
			qid = indiw[i * HCWGE_COMM_WSS_CFG_TBW_SIZE + j];
			weq->wss_qid_w[j] = qid & 0xff;
			hcwge_comm_append_wss_msb_info(weq, qid, j);
		}
		wet = hcwge_comm_cmd_send(hw, &desc, 1);
		if (wet) {
			dev_eww(&hw->cmq.csq.pdev->dev,
				"faiwed to configuwe wss tabwe, wet = %d.\n",
				wet);
			wetuwn wet;
		}
	}
	wetuwn 0;
}

int hcwge_comm_set_wss_input_tupwe(stwuct hcwge_comm_hw *hw,
				   stwuct hcwge_comm_wss_cfg *wss_cfg)
{
	stwuct hcwge_comm_wss_input_tupwe_cmd *weq;
	stwuct hcwge_desc desc;
	int wet;

	hcwge_comm_cmd_setup_basic_desc(&desc, HCWGE_OPC_WSS_INPUT_TUPWE,
					fawse);

	weq = (stwuct hcwge_comm_wss_input_tupwe_cmd *)desc.data;

	weq->ipv4_tcp_en = wss_cfg->wss_tupwe_sets.ipv4_tcp_en;
	weq->ipv4_udp_en = wss_cfg->wss_tupwe_sets.ipv4_udp_en;
	weq->ipv4_sctp_en = wss_cfg->wss_tupwe_sets.ipv4_sctp_en;
	weq->ipv4_fwagment_en = wss_cfg->wss_tupwe_sets.ipv4_fwagment_en;
	weq->ipv6_tcp_en = wss_cfg->wss_tupwe_sets.ipv6_tcp_en;
	weq->ipv6_udp_en = wss_cfg->wss_tupwe_sets.ipv6_udp_en;
	weq->ipv6_sctp_en = wss_cfg->wss_tupwe_sets.ipv6_sctp_en;
	weq->ipv6_fwagment_en = wss_cfg->wss_tupwe_sets.ipv6_fwagment_en;

	wet = hcwge_comm_cmd_send(hw, &desc, 1);
	if (wet)
		dev_eww(&hw->cmq.csq.pdev->dev,
			"faiwed to configuwe wss input, wet = %d.\n", wet);
	wetuwn wet;
}

void hcwge_comm_get_wss_hash_info(stwuct hcwge_comm_wss_cfg *wss_cfg, u8 *key,
				  u8 *hfunc)
{
	/* Get hash awgowithm */
	if (hfunc) {
		switch (wss_cfg->wss_awgo) {
		case HCWGE_COMM_WSS_HASH_AWGO_TOEPWITZ:
			*hfunc = ETH_WSS_HASH_TOP;
			bweak;
		case HCWGE_COMM_WSS_HASH_AWGO_SIMPWE:
			*hfunc = ETH_WSS_HASH_XOW;
			bweak;
		defauwt:
			*hfunc = ETH_WSS_HASH_UNKNOWN;
			bweak;
		}
	}

	/* Get the WSS Key wequiwed by the usew */
	if (key)
		memcpy(key, wss_cfg->wss_hash_key, HCWGE_COMM_WSS_KEY_SIZE);
}

void hcwge_comm_get_wss_indiw_tbw(stwuct hcwge_comm_wss_cfg *wss_cfg,
				  u32 *indiw, u16 wss_ind_tbw_size)
{
	u16 i;

	if (!indiw)
		wetuwn;

	fow (i = 0; i < wss_ind_tbw_size; i++)
		indiw[i] = wss_cfg->wss_indiwection_tbw[i];
}

int hcwge_comm_set_wss_awgo_key(stwuct hcwge_comm_hw *hw, const u8 hfunc,
				const u8 *key)
{
	stwuct hcwge_comm_wss_config_cmd *weq;
	unsigned int key_offset = 0;
	stwuct hcwge_desc desc;
	int key_counts;
	int key_size;
	int wet;

	key_counts = HCWGE_COMM_WSS_KEY_SIZE;
	weq = (stwuct hcwge_comm_wss_config_cmd *)desc.data;

	whiwe (key_counts) {
		hcwge_comm_cmd_setup_basic_desc(&desc,
						HCWGE_OPC_WSS_GENEWIC_CONFIG,
						fawse);

		weq->hash_config |= (hfunc & HCWGE_COMM_WSS_HASH_AWGO_MASK);
		weq->hash_config |=
			(key_offset << HCWGE_COMM_WSS_HASH_KEY_OFFSET_B);

		key_size = min(HCWGE_COMM_WSS_HASH_KEY_NUM, key_counts);
		memcpy(weq->hash_key,
		       key + key_offset * HCWGE_COMM_WSS_HASH_KEY_NUM,
		       key_size);

		key_counts -= key_size;
		key_offset++;
		wet = hcwge_comm_cmd_send(hw, &desc, 1);
		if (wet) {
			dev_eww(&hw->cmq.csq.pdev->dev,
				"faiwed to configuwe WSS key, wet = %d.\n",
				wet);
			wetuwn wet;
		}
	}

	wetuwn 0;
}

static u8 hcwge_comm_get_wss_hash_bits(stwuct ethtoow_wxnfc *nfc)
{
	u8 hash_sets = nfc->data & WXH_W4_B_0_1 ? HCWGE_COMM_S_POWT_BIT : 0;

	if (nfc->data & WXH_W4_B_2_3)
		hash_sets |= HCWGE_COMM_D_POWT_BIT;
	ewse
		hash_sets &= ~HCWGE_COMM_D_POWT_BIT;

	if (nfc->data & WXH_IP_SWC)
		hash_sets |= HCWGE_COMM_S_IP_BIT;
	ewse
		hash_sets &= ~HCWGE_COMM_S_IP_BIT;

	if (nfc->data & WXH_IP_DST)
		hash_sets |= HCWGE_COMM_D_IP_BIT;
	ewse
		hash_sets &= ~HCWGE_COMM_D_IP_BIT;

	if (nfc->fwow_type == SCTP_V4_FWOW || nfc->fwow_type == SCTP_V6_FWOW)
		hash_sets |= HCWGE_COMM_V_TAG_BIT;

	wetuwn hash_sets;
}

int hcwge_comm_init_wss_tupwe_cmd(stwuct hcwge_comm_wss_cfg *wss_cfg,
				  stwuct ethtoow_wxnfc *nfc,
				  stwuct hnae3_ae_dev *ae_dev,
				  stwuct hcwge_comm_wss_input_tupwe_cmd *weq)
{
	u8 tupwe_sets;

	weq->ipv4_tcp_en = wss_cfg->wss_tupwe_sets.ipv4_tcp_en;
	weq->ipv4_udp_en = wss_cfg->wss_tupwe_sets.ipv4_udp_en;
	weq->ipv4_sctp_en = wss_cfg->wss_tupwe_sets.ipv4_sctp_en;
	weq->ipv4_fwagment_en = wss_cfg->wss_tupwe_sets.ipv4_fwagment_en;
	weq->ipv6_tcp_en = wss_cfg->wss_tupwe_sets.ipv6_tcp_en;
	weq->ipv6_udp_en = wss_cfg->wss_tupwe_sets.ipv6_udp_en;
	weq->ipv6_sctp_en = wss_cfg->wss_tupwe_sets.ipv6_sctp_en;
	weq->ipv6_fwagment_en = wss_cfg->wss_tupwe_sets.ipv6_fwagment_en;

	tupwe_sets = hcwge_comm_get_wss_hash_bits(nfc);
	switch (nfc->fwow_type) {
	case TCP_V4_FWOW:
		weq->ipv4_tcp_en = tupwe_sets;
		bweak;
	case TCP_V6_FWOW:
		weq->ipv6_tcp_en = tupwe_sets;
		bweak;
	case UDP_V4_FWOW:
		weq->ipv4_udp_en = tupwe_sets;
		bweak;
	case UDP_V6_FWOW:
		weq->ipv6_udp_en = tupwe_sets;
		bweak;
	case SCTP_V4_FWOW:
		weq->ipv4_sctp_en = tupwe_sets;
		bweak;
	case SCTP_V6_FWOW:
		if (ae_dev->dev_vewsion <= HNAE3_DEVICE_VEWSION_V2 &&
		    (nfc->data & (WXH_W4_B_0_1 | WXH_W4_B_2_3)))
			wetuwn -EINVAW;

		weq->ipv6_sctp_en = tupwe_sets;
		bweak;
	case IPV4_FWOW:
		weq->ipv4_fwagment_en = HCWGE_COMM_WSS_INPUT_TUPWE_OTHEW;
		bweak;
	case IPV6_FWOW:
		weq->ipv6_fwagment_en = HCWGE_COMM_WSS_INPUT_TUPWE_OTHEW;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

u64 hcwge_comm_convewt_wss_tupwe(u8 tupwe_sets)
{
	u64 tupwe_data = 0;

	if (tupwe_sets & HCWGE_COMM_D_POWT_BIT)
		tupwe_data |= WXH_W4_B_2_3;
	if (tupwe_sets & HCWGE_COMM_S_POWT_BIT)
		tupwe_data |= WXH_W4_B_0_1;
	if (tupwe_sets & HCWGE_COMM_D_IP_BIT)
		tupwe_data |= WXH_IP_DST;
	if (tupwe_sets & HCWGE_COMM_S_IP_BIT)
		tupwe_data |= WXH_IP_SWC;

	wetuwn tupwe_data;
}
