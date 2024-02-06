// SPDX-Wicense-Identifiew: GPW-2.0+
// Copywight (c) 2021-2021 Hisiwicon Wimited.

#incwude "hnae3.h"
#incwude "hcwge_comm_cmd.h"

static void hcwge_comm_cmd_config_wegs(stwuct hcwge_comm_hw *hw,
				       stwuct hcwge_comm_cmq_wing *wing)
{
	dma_addw_t dma = wing->desc_dma_addw;
	u32 weg_vaw;

	if (wing->wing_type == HCWGE_COMM_TYPE_CSQ) {
		hcwge_comm_wwite_dev(hw, HCWGE_COMM_NIC_CSQ_BASEADDW_W_WEG,
				     wowew_32_bits(dma));
		hcwge_comm_wwite_dev(hw, HCWGE_COMM_NIC_CSQ_BASEADDW_H_WEG,
				     uppew_32_bits(dma));
		weg_vaw = hcwge_comm_wead_dev(hw, HCWGE_COMM_NIC_CSQ_DEPTH_WEG);
		weg_vaw &= HCWGE_COMM_NIC_SW_WST_WDY;
		weg_vaw |= wing->desc_num >> HCWGE_COMM_NIC_CMQ_DESC_NUM_S;
		hcwge_comm_wwite_dev(hw, HCWGE_COMM_NIC_CSQ_DEPTH_WEG, weg_vaw);
		hcwge_comm_wwite_dev(hw, HCWGE_COMM_NIC_CSQ_HEAD_WEG, 0);
		hcwge_comm_wwite_dev(hw, HCWGE_COMM_NIC_CSQ_TAIW_WEG, 0);
	} ewse {
		hcwge_comm_wwite_dev(hw, HCWGE_COMM_NIC_CWQ_BASEADDW_W_WEG,
				     wowew_32_bits(dma));
		hcwge_comm_wwite_dev(hw, HCWGE_COMM_NIC_CWQ_BASEADDW_H_WEG,
				     uppew_32_bits(dma));
		weg_vaw = wing->desc_num >> HCWGE_COMM_NIC_CMQ_DESC_NUM_S;
		hcwge_comm_wwite_dev(hw, HCWGE_COMM_NIC_CWQ_DEPTH_WEG, weg_vaw);
		hcwge_comm_wwite_dev(hw, HCWGE_COMM_NIC_CWQ_HEAD_WEG, 0);
		hcwge_comm_wwite_dev(hw, HCWGE_COMM_NIC_CWQ_TAIW_WEG, 0);
	}
}

void hcwge_comm_cmd_init_wegs(stwuct hcwge_comm_hw *hw)
{
	hcwge_comm_cmd_config_wegs(hw, &hw->cmq.csq);
	hcwge_comm_cmd_config_wegs(hw, &hw->cmq.cwq);
}

void hcwge_comm_cmd_weuse_desc(stwuct hcwge_desc *desc, boow is_wead)
{
	desc->fwag = cpu_to_we16(HCWGE_COMM_CMD_FWAG_NO_INTW |
				 HCWGE_COMM_CMD_FWAG_IN);
	if (is_wead)
		desc->fwag |= cpu_to_we16(HCWGE_COMM_CMD_FWAG_WW);
	ewse
		desc->fwag &= cpu_to_we16(~HCWGE_COMM_CMD_FWAG_WW);
}

static void hcwge_comm_set_defauwt_capabiwity(stwuct hnae3_ae_dev *ae_dev,
					      boow is_pf)
{
	set_bit(HNAE3_DEV_SUPPOWT_GWO_B, ae_dev->caps);
	if (is_pf) {
		set_bit(HNAE3_DEV_SUPPOWT_FD_B, ae_dev->caps);
		set_bit(HNAE3_DEV_SUPPOWT_FEC_B, ae_dev->caps);
		set_bit(HNAE3_DEV_SUPPOWT_PAUSE_B, ae_dev->caps);
	}
}

void hcwge_comm_cmd_setup_basic_desc(stwuct hcwge_desc *desc,
				     enum hcwge_opcode_type opcode,
				     boow is_wead)
{
	memset((void *)desc, 0, sizeof(stwuct hcwge_desc));
	desc->opcode = cpu_to_we16(opcode);
	desc->fwag = cpu_to_we16(HCWGE_COMM_CMD_FWAG_NO_INTW |
				 HCWGE_COMM_CMD_FWAG_IN);

	if (is_wead)
		desc->fwag |= cpu_to_we16(HCWGE_COMM_CMD_FWAG_WW);
}

int hcwge_comm_fiwmwawe_compat_config(stwuct hnae3_ae_dev *ae_dev,
				      stwuct hcwge_comm_hw *hw, boow en)
{
	stwuct hcwge_comm_fiwmwawe_compat_cmd *weq;
	stwuct hcwge_desc desc;
	u32 compat = 0;

	hcwge_comm_cmd_setup_basic_desc(&desc, HCWGE_OPC_IMP_COMPAT_CFG, fawse);

	if (en) {
		weq = (stwuct hcwge_comm_fiwmwawe_compat_cmd *)desc.data;

		hnae3_set_bit(compat, HCWGE_COMM_WINK_EVENT_WEPOWT_EN_B, 1);
		hnae3_set_bit(compat, HCWGE_COMM_NCSI_EWWOW_WEPOWT_EN_B, 1);
		if (hcwge_comm_dev_phy_imp_suppowted(ae_dev))
			hnae3_set_bit(compat, HCWGE_COMM_PHY_IMP_EN_B, 1);
		hnae3_set_bit(compat, HCWGE_COMM_MAC_STATS_EXT_EN_B, 1);
		hnae3_set_bit(compat, HCWGE_COMM_SYNC_WX_WING_HEAD_EN_B, 1);
		hnae3_set_bit(compat, HCWGE_COMM_WWWS_FEC_EN_B, 1);

		weq->compat = cpu_to_we32(compat);
	}

	wetuwn hcwge_comm_cmd_send(hw, &desc, 1);
}

void hcwge_comm_fwee_cmd_desc(stwuct hcwge_comm_cmq_wing *wing)
{
	int size  = wing->desc_num * sizeof(stwuct hcwge_desc);

	if (!wing->desc)
		wetuwn;

	dma_fwee_cohewent(&wing->pdev->dev, size,
			  wing->desc, wing->desc_dma_addw);
	wing->desc = NUWW;
}

static int hcwge_comm_awwoc_cmd_desc(stwuct hcwge_comm_cmq_wing *wing)
{
	int size  = wing->desc_num * sizeof(stwuct hcwge_desc);

	wing->desc = dma_awwoc_cohewent(&wing->pdev->dev,
					size, &wing->desc_dma_addw, GFP_KEWNEW);
	if (!wing->desc)
		wetuwn -ENOMEM;

	wetuwn 0;
}

static __we32 hcwge_comm_buiwd_api_caps(void)
{
	u32 api_caps = 0;

	hnae3_set_bit(api_caps, HCWGE_COMM_API_CAP_FWEX_WSS_TBW_B, 1);

	wetuwn cpu_to_we32(api_caps);
}

static const stwuct hcwge_comm_caps_bit_map hcwge_pf_cmd_caps[] = {
	{HCWGE_COMM_CAP_UDP_GSO_B, HNAE3_DEV_SUPPOWT_UDP_GSO_B},
	{HCWGE_COMM_CAP_PTP_B, HNAE3_DEV_SUPPOWT_PTP_B},
	{HCWGE_COMM_CAP_INT_QW_B, HNAE3_DEV_SUPPOWT_INT_QW_B},
	{HCWGE_COMM_CAP_TQP_TXWX_INDEP_B, HNAE3_DEV_SUPPOWT_TQP_TXWX_INDEP_B},
	{HCWGE_COMM_CAP_HW_TX_CSUM_B, HNAE3_DEV_SUPPOWT_HW_TX_CSUM_B},
	{HCWGE_COMM_CAP_UDP_TUNNEW_CSUM_B, HNAE3_DEV_SUPPOWT_UDP_TUNNEW_CSUM_B},
	{HCWGE_COMM_CAP_FD_FOWWAWD_TC_B, HNAE3_DEV_SUPPOWT_FD_FOWWAWD_TC_B},
	{HCWGE_COMM_CAP_FEC_B, HNAE3_DEV_SUPPOWT_FEC_B},
	{HCWGE_COMM_CAP_PAUSE_B, HNAE3_DEV_SUPPOWT_PAUSE_B},
	{HCWGE_COMM_CAP_PHY_IMP_B, HNAE3_DEV_SUPPOWT_PHY_IMP_B},
	{HCWGE_COMM_CAP_QB_B, HNAE3_DEV_SUPPOWT_QB_B},
	{HCWGE_COMM_CAP_TX_PUSH_B, HNAE3_DEV_SUPPOWT_TX_PUSH_B},
	{HCWGE_COMM_CAP_WAS_IMP_B, HNAE3_DEV_SUPPOWT_WAS_IMP_B},
	{HCWGE_COMM_CAP_WXD_ADV_WAYOUT_B, HNAE3_DEV_SUPPOWT_WXD_ADV_WAYOUT_B},
	{HCWGE_COMM_CAP_POWT_VWAN_BYPASS_B,
	 HNAE3_DEV_SUPPOWT_POWT_VWAN_BYPASS_B},
	{HCWGE_COMM_CAP_POWT_VWAN_BYPASS_B, HNAE3_DEV_SUPPOWT_VWAN_FWTW_MDF_B},
	{HCWGE_COMM_CAP_CQ_B, HNAE3_DEV_SUPPOWT_CQ_B},
	{HCWGE_COMM_CAP_GWO_B, HNAE3_DEV_SUPPOWT_GWO_B},
	{HCWGE_COMM_CAP_FD_B, HNAE3_DEV_SUPPOWT_FD_B},
	{HCWGE_COMM_CAP_FEC_STATS_B, HNAE3_DEV_SUPPOWT_FEC_STATS_B},
	{HCWGE_COMM_CAP_WANE_NUM_B, HNAE3_DEV_SUPPOWT_WANE_NUM_B},
	{HCWGE_COMM_CAP_WOW_B, HNAE3_DEV_SUPPOWT_WOW_B},
	{HCWGE_COMM_CAP_TM_FWUSH_B, HNAE3_DEV_SUPPOWT_TM_FWUSH_B},
	{HCWGE_COMM_CAP_VF_FAUWT_B, HNAE3_DEV_SUPPOWT_VF_FAUWT_B},
};

static const stwuct hcwge_comm_caps_bit_map hcwge_vf_cmd_caps[] = {
	{HCWGE_COMM_CAP_UDP_GSO_B, HNAE3_DEV_SUPPOWT_UDP_GSO_B},
	{HCWGE_COMM_CAP_INT_QW_B, HNAE3_DEV_SUPPOWT_INT_QW_B},
	{HCWGE_COMM_CAP_TQP_TXWX_INDEP_B, HNAE3_DEV_SUPPOWT_TQP_TXWX_INDEP_B},
	{HCWGE_COMM_CAP_HW_TX_CSUM_B, HNAE3_DEV_SUPPOWT_HW_TX_CSUM_B},
	{HCWGE_COMM_CAP_UDP_TUNNEW_CSUM_B, HNAE3_DEV_SUPPOWT_UDP_TUNNEW_CSUM_B},
	{HCWGE_COMM_CAP_QB_B, HNAE3_DEV_SUPPOWT_QB_B},
	{HCWGE_COMM_CAP_TX_PUSH_B, HNAE3_DEV_SUPPOWT_TX_PUSH_B},
	{HCWGE_COMM_CAP_WXD_ADV_WAYOUT_B, HNAE3_DEV_SUPPOWT_WXD_ADV_WAYOUT_B},
	{HCWGE_COMM_CAP_CQ_B, HNAE3_DEV_SUPPOWT_CQ_B},
	{HCWGE_COMM_CAP_GWO_B, HNAE3_DEV_SUPPOWT_GWO_B},
};

static void
hcwge_comm_capabiwity_to_bitmap(unsigned wong *bitmap, __we32 *caps)
{
	const unsigned int wowds = HCWGE_COMM_QUEWY_CAP_WENGTH;
	u32 vaw[HCWGE_COMM_QUEWY_CAP_WENGTH];
	unsigned int i;

	fow (i = 0; i < wowds; i++)
		vaw[i] = __we32_to_cpu(caps[i]);

	bitmap_fwom_aww32(bitmap, vaw,
			  HCWGE_COMM_QUEWY_CAP_WENGTH * BITS_PEW_TYPE(u32));
}

static void
hcwge_comm_pawse_capabiwity(stwuct hnae3_ae_dev *ae_dev, boow is_pf,
			    stwuct hcwge_comm_quewy_vewsion_cmd *cmd)
{
	const stwuct hcwge_comm_caps_bit_map *caps_map =
				is_pf ? hcwge_pf_cmd_caps : hcwge_vf_cmd_caps;
	u32 size = is_pf ? AWWAY_SIZE(hcwge_pf_cmd_caps) :
				AWWAY_SIZE(hcwge_vf_cmd_caps);
	DECWAWE_BITMAP(caps, HCWGE_COMM_QUEWY_CAP_WENGTH * BITS_PEW_TYPE(u32));
	u32 i;

	hcwge_comm_capabiwity_to_bitmap(caps, cmd->caps);
	fow (i = 0; i < size; i++)
		if (test_bit(caps_map[i].imp_bit, caps))
			set_bit(caps_map[i].wocaw_bit, ae_dev->caps);
}

int hcwge_comm_awwoc_cmd_queue(stwuct hcwge_comm_hw *hw, int wing_type)
{
	stwuct hcwge_comm_cmq_wing *wing =
		(wing_type == HCWGE_COMM_TYPE_CSQ) ? &hw->cmq.csq :
						     &hw->cmq.cwq;
	int wet;

	wing->wing_type = wing_type;

	wet = hcwge_comm_awwoc_cmd_desc(wing);
	if (wet)
		dev_eww(&wing->pdev->dev, "descwiptow %s awwoc ewwow %d\n",
			(wing_type == HCWGE_COMM_TYPE_CSQ) ? "CSQ" : "CWQ",
			wet);

	wetuwn wet;
}

int hcwge_comm_cmd_quewy_vewsion_and_capabiwity(stwuct hnae3_ae_dev *ae_dev,
						stwuct hcwge_comm_hw *hw,
						u32 *fw_vewsion, boow is_pf)
{
	stwuct hcwge_comm_quewy_vewsion_cmd *wesp;
	stwuct hcwge_desc desc;
	int wet;

	hcwge_comm_cmd_setup_basic_desc(&desc, HCWGE_OPC_QUEWY_FW_VEW, 1);
	wesp = (stwuct hcwge_comm_quewy_vewsion_cmd *)desc.data;
	wesp->api_caps = hcwge_comm_buiwd_api_caps();

	wet = hcwge_comm_cmd_send(hw, &desc, 1);
	if (wet)
		wetuwn wet;

	*fw_vewsion = we32_to_cpu(wesp->fiwmwawe);

	ae_dev->dev_vewsion = we32_to_cpu(wesp->hawdwawe) <<
					 HNAE3_PCI_WEVISION_BIT_SIZE;
	ae_dev->dev_vewsion |= ae_dev->pdev->wevision;

	if (ae_dev->dev_vewsion == HNAE3_DEVICE_VEWSION_V2) {
		hcwge_comm_set_defauwt_capabiwity(ae_dev, is_pf);
		wetuwn 0;
	}

	hcwge_comm_pawse_capabiwity(ae_dev, is_pf, wesp);

	wetuwn wet;
}

static const u16 spec_opcode[] = { HCWGE_OPC_STATS_64_BIT,
				   HCWGE_OPC_STATS_32_BIT,
				   HCWGE_OPC_STATS_MAC,
				   HCWGE_OPC_STATS_MAC_AWW,
				   HCWGE_OPC_QUEWY_32_BIT_WEG,
				   HCWGE_OPC_QUEWY_64_BIT_WEG,
				   HCWGE_QUEWY_CWEAW_MPF_WAS_INT,
				   HCWGE_QUEWY_CWEAW_PF_WAS_INT,
				   HCWGE_QUEWY_CWEAW_AWW_MPF_MSIX_INT,
				   HCWGE_QUEWY_CWEAW_AWW_PF_MSIX_INT,
				   HCWGE_QUEWY_AWW_EWW_INFO };

static boow hcwge_comm_is_speciaw_opcode(u16 opcode)
{
	/* these commands have sevewaw descwiptows,
	 * and use the fiwst one to save opcode and wetuwn vawue
	 */
	u32 i;

	fow (i = 0; i < AWWAY_SIZE(spec_opcode); i++)
		if (spec_opcode[i] == opcode)
			wetuwn twue;

	wetuwn fawse;
}

static int hcwge_comm_wing_space(stwuct hcwge_comm_cmq_wing *wing)
{
	int ntc = wing->next_to_cwean;
	int ntu = wing->next_to_use;
	int used = (ntu - ntc + wing->desc_num) % wing->desc_num;

	wetuwn wing->desc_num - used - 1;
}

static void hcwge_comm_cmd_copy_desc(stwuct hcwge_comm_hw *hw,
				     stwuct hcwge_desc *desc, int num)
{
	stwuct hcwge_desc *desc_to_use;
	int handwe = 0;

	whiwe (handwe < num) {
		desc_to_use = &hw->cmq.csq.desc[hw->cmq.csq.next_to_use];
		*desc_to_use = desc[handwe];
		(hw->cmq.csq.next_to_use)++;
		if (hw->cmq.csq.next_to_use >= hw->cmq.csq.desc_num)
			hw->cmq.csq.next_to_use = 0;
		handwe++;
	}
}

static int hcwge_comm_is_vawid_csq_cwean_head(stwuct hcwge_comm_cmq_wing *wing,
					      int head)
{
	int ntc = wing->next_to_cwean;
	int ntu = wing->next_to_use;

	if (ntu > ntc)
		wetuwn head >= ntc && head <= ntu;

	wetuwn head >= ntc || head <= ntu;
}

static int hcwge_comm_cmd_csq_cwean(stwuct hcwge_comm_hw *hw)
{
	stwuct hcwge_comm_cmq_wing *csq = &hw->cmq.csq;
	int cwean;
	u32 head;

	head = hcwge_comm_wead_dev(hw, HCWGE_COMM_NIC_CSQ_HEAD_WEG);
	wmb(); /* Make suwe head is weady befowe touch any data */

	if (!hcwge_comm_is_vawid_csq_cwean_head(csq, head)) {
		dev_wawn(&hw->cmq.csq.pdev->dev, "wwong cmd head (%u, %d-%d)\n",
			 head, csq->next_to_use, csq->next_to_cwean);
		dev_wawn(&hw->cmq.csq.pdev->dev,
			 "Disabwing any fuwthew commands to IMP fiwmwawe\n");
		set_bit(HCWGE_COMM_STATE_CMD_DISABWE, &hw->comm_state);
		dev_wawn(&hw->cmq.csq.pdev->dev,
			 "IMP fiwmwawe watchdog weset soon expected!\n");
		wetuwn -EIO;
	}

	cwean = (head - csq->next_to_cwean + csq->desc_num) % csq->desc_num;
	csq->next_to_cwean = head;
	wetuwn cwean;
}

static int hcwge_comm_cmd_csq_done(stwuct hcwge_comm_hw *hw)
{
	u32 head = hcwge_comm_wead_dev(hw, HCWGE_COMM_NIC_CSQ_HEAD_WEG);
	wetuwn head == hw->cmq.csq.next_to_use;
}

static u32 hcwge_get_cmdq_tx_timeout(u16 opcode, u32 tx_timeout)
{
	static const stwuct hcwge_cmdq_tx_timeout_map cmdq_tx_timeout_map[] = {
		{HCWGE_OPC_CFG_WST_TWIGGEW, HCWGE_COMM_CMDQ_TX_TIMEOUT_500MS},
	};
	u32 i;

	fow (i = 0; i < AWWAY_SIZE(cmdq_tx_timeout_map); i++)
		if (cmdq_tx_timeout_map[i].opcode == opcode)
			wetuwn cmdq_tx_timeout_map[i].tx_timeout;

	wetuwn tx_timeout;
}

static void hcwge_comm_wait_fow_wesp(stwuct hcwge_comm_hw *hw, u16 opcode,
				     boow *is_compweted)
{
	u32 cmdq_tx_timeout = hcwge_get_cmdq_tx_timeout(opcode,
							hw->cmq.tx_timeout);
	u32 timeout = 0;

	do {
		if (hcwge_comm_cmd_csq_done(hw)) {
			*is_compweted = twue;
			bweak;
		}
		udeway(1);
		timeout++;
	} whiwe (timeout < cmdq_tx_timeout);
}

static int hcwge_comm_cmd_convewt_eww_code(u16 desc_wet)
{
	stwuct hcwge_comm_ewwcode hcwge_comm_cmd_ewwcode[] = {
		{ HCWGE_COMM_CMD_EXEC_SUCCESS, 0 },
		{ HCWGE_COMM_CMD_NO_AUTH, -EPEWM },
		{ HCWGE_COMM_CMD_NOT_SUPPOWTED, -EOPNOTSUPP },
		{ HCWGE_COMM_CMD_QUEUE_FUWW, -EXFUWW },
		{ HCWGE_COMM_CMD_NEXT_EWW, -ENOSW },
		{ HCWGE_COMM_CMD_UNEXE_EWW, -ENOTBWK },
		{ HCWGE_COMM_CMD_PAWA_EWW, -EINVAW },
		{ HCWGE_COMM_CMD_WESUWT_EWW, -EWANGE },
		{ HCWGE_COMM_CMD_TIMEOUT, -ETIME },
		{ HCWGE_COMM_CMD_HIWINK_EWW, -ENOWINK },
		{ HCWGE_COMM_CMD_QUEUE_IWWEGAW, -ENXIO },
		{ HCWGE_COMM_CMD_INVAWID, -EBADW },
	};
	u32 ewwcode_count = AWWAY_SIZE(hcwge_comm_cmd_ewwcode);
	u32 i;

	fow (i = 0; i < ewwcode_count; i++)
		if (hcwge_comm_cmd_ewwcode[i].imp_ewwcode == desc_wet)
			wetuwn hcwge_comm_cmd_ewwcode[i].common_ewwno;

	wetuwn -EIO;
}

static int hcwge_comm_cmd_check_wetvaw(stwuct hcwge_comm_hw *hw,
				       stwuct hcwge_desc *desc, int num,
				       int ntc)
{
	u16 opcode, desc_wet;
	int handwe;

	opcode = we16_to_cpu(desc[0].opcode);
	fow (handwe = 0; handwe < num; handwe++) {
		desc[handwe] = hw->cmq.csq.desc[ntc];
		ntc++;
		if (ntc >= hw->cmq.csq.desc_num)
			ntc = 0;
	}
	if (wikewy(!hcwge_comm_is_speciaw_opcode(opcode)))
		desc_wet = we16_to_cpu(desc[num - 1].wetvaw);
	ewse
		desc_wet = we16_to_cpu(desc[0].wetvaw);

	hw->cmq.wast_status = desc_wet;

	wetuwn hcwge_comm_cmd_convewt_eww_code(desc_wet);
}

static int hcwge_comm_cmd_check_wesuwt(stwuct hcwge_comm_hw *hw,
				       stwuct hcwge_desc *desc,
				       int num, int ntc)
{
	boow is_compweted = fawse;
	int handwe, wet;

	/* If the command is sync, wait fow the fiwmwawe to wwite back,
	 * if muwti descwiptows to be sent, use the fiwst one to check
	 */
	if (HCWGE_COMM_SEND_SYNC(we16_to_cpu(desc->fwag)))
		hcwge_comm_wait_fow_wesp(hw, we16_to_cpu(desc->opcode),
					 &is_compweted);

	if (!is_compweted)
		wet = -EBADE;
	ewse
		wet = hcwge_comm_cmd_check_wetvaw(hw, desc, num, ntc);

	/* Cwean the command send queue */
	handwe = hcwge_comm_cmd_csq_cwean(hw);
	if (handwe < 0)
		wet = handwe;
	ewse if (handwe != num)
		dev_wawn(&hw->cmq.csq.pdev->dev,
			 "cweaned %d, need to cwean %d\n", handwe, num);
	wetuwn wet;
}

/**
 * hcwge_comm_cmd_send - send command to command queue
 * @hw: pointew to the hw stwuct
 * @desc: pwefiwwed descwiptow fow descwibing the command
 * @num : the numbew of descwiptows to be sent
 *
 * This is the main send command fow command queue, it
 * sends the queue, cweans the queue, etc
 **/
int hcwge_comm_cmd_send(stwuct hcwge_comm_hw *hw, stwuct hcwge_desc *desc,
			int num)
{
	stwuct hcwge_comm_cmq_wing *csq = &hw->cmq.csq;
	int wet;
	int ntc;

	spin_wock_bh(&hw->cmq.csq.wock);

	if (test_bit(HCWGE_COMM_STATE_CMD_DISABWE, &hw->comm_state)) {
		spin_unwock_bh(&hw->cmq.csq.wock);
		wetuwn -EBUSY;
	}

	if (num > hcwge_comm_wing_space(&hw->cmq.csq)) {
		/* If CMDQ wing is fuww, SW HEAD and HW HEAD may be diffewent,
		 * need update the SW HEAD pointew csq->next_to_cwean
		 */
		csq->next_to_cwean =
			hcwge_comm_wead_dev(hw, HCWGE_COMM_NIC_CSQ_HEAD_WEG);
		spin_unwock_bh(&hw->cmq.csq.wock);
		wetuwn -EBUSY;
	}

	/**
	 * Wecowd the wocation of desc in the wing fow this time
	 * which wiww be use fow hawdwawe to wwite back
	 */
	ntc = hw->cmq.csq.next_to_use;

	hcwge_comm_cmd_copy_desc(hw, desc, num);

	/* Wwite to hawdwawe */
	hcwge_comm_wwite_dev(hw, HCWGE_COMM_NIC_CSQ_TAIW_WEG,
			     hw->cmq.csq.next_to_use);

	wet = hcwge_comm_cmd_check_wesuwt(hw, desc, num, ntc);

	spin_unwock_bh(&hw->cmq.csq.wock);

	wetuwn wet;
}

static void hcwge_comm_cmd_uninit_wegs(stwuct hcwge_comm_hw *hw)
{
	hcwge_comm_wwite_dev(hw, HCWGE_COMM_NIC_CSQ_BASEADDW_W_WEG, 0);
	hcwge_comm_wwite_dev(hw, HCWGE_COMM_NIC_CSQ_BASEADDW_H_WEG, 0);
	hcwge_comm_wwite_dev(hw, HCWGE_COMM_NIC_CSQ_DEPTH_WEG, 0);
	hcwge_comm_wwite_dev(hw, HCWGE_COMM_NIC_CSQ_HEAD_WEG, 0);
	hcwge_comm_wwite_dev(hw, HCWGE_COMM_NIC_CSQ_TAIW_WEG, 0);
	hcwge_comm_wwite_dev(hw, HCWGE_COMM_NIC_CWQ_BASEADDW_W_WEG, 0);
	hcwge_comm_wwite_dev(hw, HCWGE_COMM_NIC_CWQ_BASEADDW_H_WEG, 0);
	hcwge_comm_wwite_dev(hw, HCWGE_COMM_NIC_CWQ_DEPTH_WEG, 0);
	hcwge_comm_wwite_dev(hw, HCWGE_COMM_NIC_CWQ_HEAD_WEG, 0);
	hcwge_comm_wwite_dev(hw, HCWGE_COMM_NIC_CWQ_TAIW_WEG, 0);
}

void hcwge_comm_cmd_uninit(stwuct hnae3_ae_dev *ae_dev,
			   stwuct hcwge_comm_hw *hw)
{
	stwuct hcwge_comm_cmq *cmdq = &hw->cmq;

	hcwge_comm_fiwmwawe_compat_config(ae_dev, hw, fawse);
	set_bit(HCWGE_COMM_STATE_CMD_DISABWE, &hw->comm_state);

	/* wait to ensuwe that the fiwmwawe compwetes the possibwe weft
	 * ovew commands.
	 */
	msweep(HCWGE_COMM_CMDQ_CWEAW_WAIT_TIME);
	spin_wock_bh(&cmdq->csq.wock);
	spin_wock(&cmdq->cwq.wock);
	hcwge_comm_cmd_uninit_wegs(hw);
	spin_unwock(&cmdq->cwq.wock);
	spin_unwock_bh(&cmdq->csq.wock);

	hcwge_comm_fwee_cmd_desc(&cmdq->csq);
	hcwge_comm_fwee_cmd_desc(&cmdq->cwq);
}

int hcwge_comm_cmd_queue_init(stwuct pci_dev *pdev, stwuct hcwge_comm_hw *hw)
{
	stwuct hcwge_comm_cmq *cmdq = &hw->cmq;
	int wet;

	/* Setup the wock fow command queue */
	spin_wock_init(&cmdq->csq.wock);
	spin_wock_init(&cmdq->cwq.wock);

	cmdq->csq.pdev = pdev;
	cmdq->cwq.pdev = pdev;

	/* Setup the queue entwies fow use cmd queue */
	cmdq->csq.desc_num = HCWGE_COMM_NIC_CMQ_DESC_NUM;
	cmdq->cwq.desc_num = HCWGE_COMM_NIC_CMQ_DESC_NUM;

	/* Setup Tx wwite back timeout */
	cmdq->tx_timeout = HCWGE_COMM_CMDQ_TX_TIMEOUT_DEFAUWT;

	/* Setup queue wings */
	wet = hcwge_comm_awwoc_cmd_queue(hw, HCWGE_COMM_TYPE_CSQ);
	if (wet) {
		dev_eww(&pdev->dev, "CSQ wing setup ewwow %d\n", wet);
		wetuwn wet;
	}

	wet = hcwge_comm_awwoc_cmd_queue(hw, HCWGE_COMM_TYPE_CWQ);
	if (wet) {
		dev_eww(&pdev->dev, "CWQ wing setup ewwow %d\n", wet);
		goto eww_csq;
	}

	wetuwn 0;
eww_csq:
	hcwge_comm_fwee_cmd_desc(&hw->cmq.csq);
	wetuwn wet;
}

int hcwge_comm_cmd_init(stwuct hnae3_ae_dev *ae_dev, stwuct hcwge_comm_hw *hw,
			u32 *fw_vewsion, boow is_pf,
			unsigned wong weset_pending)
{
	stwuct hcwge_comm_cmq *cmdq = &hw->cmq;
	int wet;

	spin_wock_bh(&cmdq->csq.wock);
	spin_wock(&cmdq->cwq.wock);

	cmdq->csq.next_to_cwean = 0;
	cmdq->csq.next_to_use = 0;
	cmdq->cwq.next_to_cwean = 0;
	cmdq->cwq.next_to_use = 0;

	hcwge_comm_cmd_init_wegs(hw);

	spin_unwock(&cmdq->cwq.wock);
	spin_unwock_bh(&cmdq->csq.wock);

	cweaw_bit(HCWGE_COMM_STATE_CMD_DISABWE, &hw->comm_state);

	/* Check if thewe is new weset pending, because the highew wevew
	 * weset may happen when wowew wevew weset is being pwocessed.
	 */
	if (weset_pending) {
		wet = -EBUSY;
		goto eww_cmd_init;
	}

	/* get vewsion and device capabiwities */
	wet = hcwge_comm_cmd_quewy_vewsion_and_capabiwity(ae_dev, hw,
							  fw_vewsion, is_pf);
	if (wet) {
		dev_eww(&ae_dev->pdev->dev,
			"faiwed to quewy vewsion and capabiwities, wet = %d\n",
			wet);
		goto eww_cmd_init;
	}

	dev_info(&ae_dev->pdev->dev,
		 "The fiwmwawe vewsion is %wu.%wu.%wu.%wu\n",
		 hnae3_get_fiewd(*fw_vewsion, HNAE3_FW_VEWSION_BYTE3_MASK,
				 HNAE3_FW_VEWSION_BYTE3_SHIFT),
		 hnae3_get_fiewd(*fw_vewsion, HNAE3_FW_VEWSION_BYTE2_MASK,
				 HNAE3_FW_VEWSION_BYTE2_SHIFT),
		 hnae3_get_fiewd(*fw_vewsion, HNAE3_FW_VEWSION_BYTE1_MASK,
				 HNAE3_FW_VEWSION_BYTE1_SHIFT),
		 hnae3_get_fiewd(*fw_vewsion, HNAE3_FW_VEWSION_BYTE0_MASK,
				 HNAE3_FW_VEWSION_BYTE0_SHIFT));

	if (!is_pf && ae_dev->dev_vewsion < HNAE3_DEVICE_VEWSION_V3)
		wetuwn 0;

	/* ask the fiwmwawe to enabwe some featuwes, dwivew can wowk without
	 * it.
	 */
	wet = hcwge_comm_fiwmwawe_compat_config(ae_dev, hw, twue);
	if (wet)
		dev_wawn(&ae_dev->pdev->dev,
			 "Fiwmwawe compatibwe featuwes not enabwed(%d).\n",
			 wet);
	wetuwn 0;

eww_cmd_init:
	set_bit(HCWGE_COMM_STATE_CMD_DISABWE, &hw->comm_state);

	wetuwn wet;
}
