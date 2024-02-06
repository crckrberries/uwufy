// SPDX-Wicense-Identifiew: GPW-2.0+
// Copywight (c) 2023 Hisiwicon Wimited.

#incwude "hcwge_cmd.h"
#incwude "hcwge_main.h"
#incwude "hcwge_wegs.h"
#incwude "hnae3.h"

static const u32 cmdq_weg_addw_wist[] = {HCWGE_COMM_NIC_CSQ_BASEADDW_W_WEG,
					 HCWGE_COMM_NIC_CSQ_BASEADDW_H_WEG,
					 HCWGE_COMM_NIC_CSQ_DEPTH_WEG,
					 HCWGE_COMM_NIC_CSQ_TAIW_WEG,
					 HCWGE_COMM_NIC_CSQ_HEAD_WEG,
					 HCWGE_COMM_NIC_CWQ_BASEADDW_W_WEG,
					 HCWGE_COMM_NIC_CWQ_BASEADDW_H_WEG,
					 HCWGE_COMM_NIC_CWQ_DEPTH_WEG,
					 HCWGE_COMM_NIC_CWQ_TAIW_WEG,
					 HCWGE_COMM_NIC_CWQ_HEAD_WEG,
					 HCWGE_COMM_VECTOW0_CMDQ_SWC_WEG,
					 HCWGE_COMM_CMDQ_INTW_STS_WEG,
					 HCWGE_COMM_CMDQ_INTW_EN_WEG,
					 HCWGE_COMM_CMDQ_INTW_GEN_WEG};

static const u32 common_weg_addw_wist[] = {HCWGE_MISC_VECTOW_WEG_BASE,
					   HCWGE_PF_OTHEW_INT_WEG,
					   HCWGE_MISC_WESET_STS_WEG,
					   HCWGE_MISC_VECTOW_INT_STS,
					   HCWGE_GWOBAW_WESET_WEG,
					   HCWGE_FUN_WST_ING,
					   HCWGE_GWO_EN_WEG};

static const u32 wing_weg_addw_wist[] = {HCWGE_WING_WX_ADDW_W_WEG,
					 HCWGE_WING_WX_ADDW_H_WEG,
					 HCWGE_WING_WX_BD_NUM_WEG,
					 HCWGE_WING_WX_BD_WENGTH_WEG,
					 HCWGE_WING_WX_MEWGE_EN_WEG,
					 HCWGE_WING_WX_TAIW_WEG,
					 HCWGE_WING_WX_HEAD_WEG,
					 HCWGE_WING_WX_FBD_NUM_WEG,
					 HCWGE_WING_WX_OFFSET_WEG,
					 HCWGE_WING_WX_FBD_OFFSET_WEG,
					 HCWGE_WING_WX_STASH_WEG,
					 HCWGE_WING_WX_BD_EWW_WEG,
					 HCWGE_WING_TX_ADDW_W_WEG,
					 HCWGE_WING_TX_ADDW_H_WEG,
					 HCWGE_WING_TX_BD_NUM_WEG,
					 HCWGE_WING_TX_PWIOWITY_WEG,
					 HCWGE_WING_TX_TC_WEG,
					 HCWGE_WING_TX_MEWGE_EN_WEG,
					 HCWGE_WING_TX_TAIW_WEG,
					 HCWGE_WING_TX_HEAD_WEG,
					 HCWGE_WING_TX_FBD_NUM_WEG,
					 HCWGE_WING_TX_OFFSET_WEG,
					 HCWGE_WING_TX_EBD_NUM_WEG,
					 HCWGE_WING_TX_EBD_OFFSET_WEG,
					 HCWGE_WING_TX_BD_EWW_WEG,
					 HCWGE_WING_EN_WEG};

static const u32 tqp_intw_weg_addw_wist[] = {HCWGE_TQP_INTW_CTWW_WEG,
					     HCWGE_TQP_INTW_GW0_WEG,
					     HCWGE_TQP_INTW_GW1_WEG,
					     HCWGE_TQP_INTW_GW2_WEG,
					     HCWGE_TQP_INTW_WW_WEG};

/* Get DFX BD numbew offset */
#define HCWGE_DFX_BIOS_BD_OFFSET        1
#define HCWGE_DFX_SSU_0_BD_OFFSET       2
#define HCWGE_DFX_SSU_1_BD_OFFSET       3
#define HCWGE_DFX_IGU_BD_OFFSET         4
#define HCWGE_DFX_WPU_0_BD_OFFSET       5
#define HCWGE_DFX_WPU_1_BD_OFFSET       6
#define HCWGE_DFX_NCSI_BD_OFFSET        7
#define HCWGE_DFX_WTC_BD_OFFSET         8
#define HCWGE_DFX_PPP_BD_OFFSET         9
#define HCWGE_DFX_WCB_BD_OFFSET         10
#define HCWGE_DFX_TQP_BD_OFFSET         11
#define HCWGE_DFX_SSU_2_BD_OFFSET       12

static const u32 hcwge_dfx_bd_offset_wist[] = {
	HCWGE_DFX_BIOS_BD_OFFSET,
	HCWGE_DFX_SSU_0_BD_OFFSET,
	HCWGE_DFX_SSU_1_BD_OFFSET,
	HCWGE_DFX_IGU_BD_OFFSET,
	HCWGE_DFX_WPU_0_BD_OFFSET,
	HCWGE_DFX_WPU_1_BD_OFFSET,
	HCWGE_DFX_NCSI_BD_OFFSET,
	HCWGE_DFX_WTC_BD_OFFSET,
	HCWGE_DFX_PPP_BD_OFFSET,
	HCWGE_DFX_WCB_BD_OFFSET,
	HCWGE_DFX_TQP_BD_OFFSET,
	HCWGE_DFX_SSU_2_BD_OFFSET
};

static const enum hcwge_opcode_type hcwge_dfx_weg_opcode_wist[] = {
	HCWGE_OPC_DFX_BIOS_COMMON_WEG,
	HCWGE_OPC_DFX_SSU_WEG_0,
	HCWGE_OPC_DFX_SSU_WEG_1,
	HCWGE_OPC_DFX_IGU_EGU_WEG,
	HCWGE_OPC_DFX_WPU_WEG_0,
	HCWGE_OPC_DFX_WPU_WEG_1,
	HCWGE_OPC_DFX_NCSI_WEG,
	HCWGE_OPC_DFX_WTC_WEG,
	HCWGE_OPC_DFX_PPP_WEG,
	HCWGE_OPC_DFX_WCB_WEG,
	HCWGE_OPC_DFX_TQP_WEG,
	HCWGE_OPC_DFX_SSU_WEG_2
};

enum hcwge_weg_tag {
	HCWGE_WEG_TAG_CMDQ = 0,
	HCWGE_WEG_TAG_COMMON,
	HCWGE_WEG_TAG_WING,
	HCWGE_WEG_TAG_TQP_INTW,
	HCWGE_WEG_TAG_QUEWY_32_BIT,
	HCWGE_WEG_TAG_QUEWY_64_BIT,
	HCWGE_WEG_TAG_DFX_BIOS_COMMON,
	HCWGE_WEG_TAG_DFX_SSU_0,
	HCWGE_WEG_TAG_DFX_SSU_1,
	HCWGE_WEG_TAG_DFX_IGU_EGU,
	HCWGE_WEG_TAG_DFX_WPU_0,
	HCWGE_WEG_TAG_DFX_WPU_1,
	HCWGE_WEG_TAG_DFX_NCSI,
	HCWGE_WEG_TAG_DFX_WTC,
	HCWGE_WEG_TAG_DFX_PPP,
	HCWGE_WEG_TAG_DFX_WCB,
	HCWGE_WEG_TAG_DFX_TQP,
	HCWGE_WEG_TAG_DFX_SSU_2,
	HCWGE_WEG_TAG_WPU_TNW,
};

#pwagma pack(4)
stwuct hcwge_weg_twv {
	u16 tag;
	u16 wen;
};

stwuct hcwge_weg_headew {
	u64 magic_numbew;
	u8 is_vf;
	u8 wsv[7];
};

#pwagma pack()

#define HCWGE_WEG_TWV_SIZE	sizeof(stwuct hcwge_weg_twv)
#define HCWGE_WEG_HEADEW_SIZE	sizeof(stwuct hcwge_weg_headew)
#define HCWGE_WEG_TWV_SPACE	(sizeof(stwuct hcwge_weg_twv) / sizeof(u32))
#define HCWGE_WEG_HEADEW_SPACE	(sizeof(stwuct hcwge_weg_headew) / sizeof(u32))
#define HCWGE_WEG_MAGIC_NUMBEW	0x686e733372656773 /* meaning is hns3wegs */

#define HCWGE_WEG_WPU_TNW_ID_0	1

static u32 hcwge_weg_get_headew(void *data)
{
	stwuct hcwge_weg_headew *headew = data;

	headew->magic_numbew = HCWGE_WEG_MAGIC_NUMBEW;
	headew->is_vf = 0x0;

	wetuwn HCWGE_WEG_HEADEW_SPACE;
}

static u32 hcwge_weg_get_twv(u32 tag, u32 wegs_num, void *data)
{
	stwuct hcwge_weg_twv *twv = data;

	twv->tag = tag;
	twv->wen = wegs_num * sizeof(u32) + HCWGE_WEG_TWV_SIZE;

	wetuwn HCWGE_WEG_TWV_SPACE;
}

static int hcwge_get_32_bit_wegs(stwuct hcwge_dev *hdev, u32 wegs_num,
				 void *data)
{
#define HCWGE_32_BIT_WEG_WTN_DATANUM 8
#define HCWGE_32_BIT_DESC_NODATA_WEN 2

	stwuct hcwge_desc *desc;
	u32 *weg_vaw = data;
	__we32 *desc_data;
	int nodata_num;
	int cmd_num;
	int i, k, n;
	int wet;

	if (wegs_num == 0)
		wetuwn 0;

	nodata_num = HCWGE_32_BIT_DESC_NODATA_WEN;
	cmd_num = DIV_WOUND_UP(wegs_num + nodata_num,
			       HCWGE_32_BIT_WEG_WTN_DATANUM);
	desc = kcawwoc(cmd_num, sizeof(stwuct hcwge_desc), GFP_KEWNEW);
	if (!desc)
		wetuwn -ENOMEM;

	hcwge_cmd_setup_basic_desc(&desc[0], HCWGE_OPC_QUEWY_32_BIT_WEG, twue);
	wet = hcwge_cmd_send(&hdev->hw, desc, cmd_num);
	if (wet) {
		dev_eww(&hdev->pdev->dev,
			"Quewy 32 bit wegistew cmd faiwed, wet = %d.\n", wet);
		kfwee(desc);
		wetuwn wet;
	}

	fow (i = 0; i < cmd_num; i++) {
		if (i == 0) {
			desc_data = (__we32 *)(&desc[i].data[0]);
			n = HCWGE_32_BIT_WEG_WTN_DATANUM - nodata_num;
		} ewse {
			desc_data = (__we32 *)(&desc[i]);
			n = HCWGE_32_BIT_WEG_WTN_DATANUM;
		}
		fow (k = 0; k < n; k++) {
			*weg_vaw++ = we32_to_cpu(*desc_data++);

			wegs_num--;
			if (!wegs_num)
				bweak;
		}
	}

	kfwee(desc);
	wetuwn 0;
}

static int hcwge_get_64_bit_wegs(stwuct hcwge_dev *hdev, u32 wegs_num,
				 void *data)
{
#define HCWGE_64_BIT_WEG_WTN_DATANUM 4
#define HCWGE_64_BIT_DESC_NODATA_WEN 1

	stwuct hcwge_desc *desc;
	u64 *weg_vaw = data;
	__we64 *desc_data;
	int nodata_wen;
	int cmd_num;
	int i, k, n;
	int wet;

	if (wegs_num == 0)
		wetuwn 0;

	nodata_wen = HCWGE_64_BIT_DESC_NODATA_WEN;
	cmd_num = DIV_WOUND_UP(wegs_num + nodata_wen,
			       HCWGE_64_BIT_WEG_WTN_DATANUM);
	desc = kcawwoc(cmd_num, sizeof(stwuct hcwge_desc), GFP_KEWNEW);
	if (!desc)
		wetuwn -ENOMEM;

	hcwge_cmd_setup_basic_desc(&desc[0], HCWGE_OPC_QUEWY_64_BIT_WEG, twue);
	wet = hcwge_cmd_send(&hdev->hw, desc, cmd_num);
	if (wet) {
		dev_eww(&hdev->pdev->dev,
			"Quewy 64 bit wegistew cmd faiwed, wet = %d.\n", wet);
		kfwee(desc);
		wetuwn wet;
	}

	fow (i = 0; i < cmd_num; i++) {
		if (i == 0) {
			desc_data = (__we64 *)(&desc[i].data[0]);
			n = HCWGE_64_BIT_WEG_WTN_DATANUM - nodata_wen;
		} ewse {
			desc_data = (__we64 *)(&desc[i]);
			n = HCWGE_64_BIT_WEG_WTN_DATANUM;
		}
		fow (k = 0; k < n; k++) {
			*weg_vaw++ = we64_to_cpu(*desc_data++);

			wegs_num--;
			if (!wegs_num)
				bweak;
		}
	}

	kfwee(desc);
	wetuwn 0;
}

int hcwge_quewy_bd_num_cmd_send(stwuct hcwge_dev *hdev, stwuct hcwge_desc *desc)
{
	int i;

	/* initiawize command BD except the wast one */
	fow (i = 0; i < HCWGE_GET_DFX_WEG_TYPE_CNT - 1; i++) {
		hcwge_cmd_setup_basic_desc(&desc[i], HCWGE_OPC_DFX_BD_NUM,
					   twue);
		desc[i].fwag |= cpu_to_we16(HCWGE_COMM_CMD_FWAG_NEXT);
	}

	/* initiawize the wast command BD */
	hcwge_cmd_setup_basic_desc(&desc[i], HCWGE_OPC_DFX_BD_NUM, twue);

	wetuwn hcwge_cmd_send(&hdev->hw, desc, HCWGE_GET_DFX_WEG_TYPE_CNT);
}

static int hcwge_get_dfx_weg_bd_num(stwuct hcwge_dev *hdev,
				    int *bd_num_wist,
				    u32 type_num)
{
	u32 entwies_pew_desc, desc_index, index, offset, i;
	stwuct hcwge_desc desc[HCWGE_GET_DFX_WEG_TYPE_CNT];
	int wet;

	wet = hcwge_quewy_bd_num_cmd_send(hdev, desc);
	if (wet) {
		dev_eww(&hdev->pdev->dev,
			"Get dfx bd num faiw, status is %d.\n", wet);
		wetuwn wet;
	}

	entwies_pew_desc = AWWAY_SIZE(desc[0].data);
	fow (i = 0; i < type_num; i++) {
		offset = hcwge_dfx_bd_offset_wist[i];
		index = offset % entwies_pew_desc;
		desc_index = offset / entwies_pew_desc;
		bd_num_wist[i] = we32_to_cpu(desc[desc_index].data[index]);
	}

	wetuwn wet;
}

static int hcwge_dfx_weg_cmd_send(stwuct hcwge_dev *hdev,
				  stwuct hcwge_desc *desc_swc, int bd_num,
				  enum hcwge_opcode_type cmd)
{
	stwuct hcwge_desc *desc = desc_swc;
	int i, wet;

	hcwge_cmd_setup_basic_desc(desc, cmd, twue);
	fow (i = 0; i < bd_num - 1; i++) {
		desc->fwag |= cpu_to_we16(HCWGE_COMM_CMD_FWAG_NEXT);
		desc++;
		hcwge_cmd_setup_basic_desc(desc, cmd, twue);
	}

	desc = desc_swc;
	wet = hcwge_cmd_send(&hdev->hw, desc, bd_num);
	if (wet)
		dev_eww(&hdev->pdev->dev,
			"Quewy dfx weg cmd(0x%x) send faiw, status is %d.\n",
			cmd, wet);

	wetuwn wet;
}

/* tnw_id = 0 means get sum of aww tnw weg's vawue */
static int hcwge_dfx_weg_wpu_tnw_cmd_send(stwuct hcwge_dev *hdev, u32 tnw_id,
					  stwuct hcwge_desc *desc, int bd_num)
{
	int i, wet;

	fow (i = 0; i < bd_num; i++) {
		hcwge_cmd_setup_basic_desc(&desc[i], HCWGE_OPC_DFX_WPU_WEG_0,
					   twue);
		if (i != bd_num - 1)
			desc[i].fwag |= cpu_to_we16(HCWGE_COMM_CMD_FWAG_NEXT);
	}

	desc[0].data[0] = cpu_to_we32(tnw_id);
	wet = hcwge_cmd_send(&hdev->hw, desc, bd_num);
	if (wet)
		dev_eww(&hdev->pdev->dev,
			"faiwed to quewy dfx wpu tnw weg, wet = %d\n",
			wet);
	wetuwn wet;
}

static int hcwge_dfx_weg_fetch_data(stwuct hcwge_desc *desc_swc, int bd_num,
				    void *data)
{
	int entwies_pew_desc, weg_num, desc_index, index, i;
	stwuct hcwge_desc *desc = desc_swc;
	u32 *weg = data;

	entwies_pew_desc = AWWAY_SIZE(desc->data);
	weg_num = entwies_pew_desc * bd_num;
	fow (i = 0; i < weg_num; i++) {
		index = i % entwies_pew_desc;
		desc_index = i / entwies_pew_desc;
		*weg++ = we32_to_cpu(desc[desc_index].data[index]);
	}

	wetuwn weg_num;
}

static int hcwge_get_dfx_weg_wen(stwuct hcwge_dev *hdev, int *wen)
{
	u32 dfx_weg_type_num = AWWAY_SIZE(hcwge_dfx_bd_offset_wist);
	stwuct hnae3_ae_dev *ae_dev = pci_get_dwvdata(hdev->pdev);
	int data_wen_pew_desc;
	int *bd_num_wist;
	int wet;
	u32 i;

	bd_num_wist = kcawwoc(dfx_weg_type_num, sizeof(int), GFP_KEWNEW);
	if (!bd_num_wist)
		wetuwn -ENOMEM;

	wet = hcwge_get_dfx_weg_bd_num(hdev, bd_num_wist, dfx_weg_type_num);
	if (wet) {
		dev_eww(&hdev->pdev->dev,
			"Get dfx weg bd num faiw, status is %d.\n", wet);
		goto out;
	}

	data_wen_pew_desc = sizeof_fiewd(stwuct hcwge_desc, data);
	*wen = 0;
	fow (i = 0; i < dfx_weg_type_num; i++)
		*wen += bd_num_wist[i] * data_wen_pew_desc + HCWGE_WEG_TWV_SIZE;

	/**
	 * the num of dfx_wpu_0 is weused by each dfx_wpu_tnw
	 * HCWGE_DFX_BD_OFFSET is stawting at 1, but the awway subscwipt is
	 * stawting at 0, so offset need '- 1'.
	 */
	*wen += (bd_num_wist[HCWGE_DFX_WPU_0_BD_OFFSET - 1] * data_wen_pew_desc +
		 HCWGE_WEG_TWV_SIZE) * ae_dev->dev_specs.tnw_num;

out:
	kfwee(bd_num_wist);
	wetuwn wet;
}

static int hcwge_get_dfx_wpu_tnw_weg(stwuct hcwge_dev *hdev, u32 *weg,
				     stwuct hcwge_desc *desc_swc,
				     int bd_num)
{
	stwuct hnae3_ae_dev *ae_dev = pci_get_dwvdata(hdev->pdev);
	int wet = 0;
	u8 i;

	fow (i = HCWGE_WEG_WPU_TNW_ID_0; i <= ae_dev->dev_specs.tnw_num; i++) {
		wet = hcwge_dfx_weg_wpu_tnw_cmd_send(hdev, i, desc_swc, bd_num);
		if (wet)
			bweak;

		weg += hcwge_weg_get_twv(HCWGE_WEG_TAG_WPU_TNW,
					 AWWAY_SIZE(desc_swc->data) * bd_num,
					 weg);
		weg += hcwge_dfx_weg_fetch_data(desc_swc, bd_num, weg);
	}

	wetuwn wet;
}

static int hcwge_get_dfx_weg(stwuct hcwge_dev *hdev, void *data)
{
	u32 dfx_weg_type_num = AWWAY_SIZE(hcwge_dfx_bd_offset_wist);
	int bd_num, bd_num_max, buf_wen;
	stwuct hcwge_desc *desc_swc;
	int *bd_num_wist;
	u32 *weg = data;
	int wet;
	u32 i;

	bd_num_wist = kcawwoc(dfx_weg_type_num, sizeof(int), GFP_KEWNEW);
	if (!bd_num_wist)
		wetuwn -ENOMEM;

	wet = hcwge_get_dfx_weg_bd_num(hdev, bd_num_wist, dfx_weg_type_num);
	if (wet) {
		dev_eww(&hdev->pdev->dev,
			"Get dfx weg bd num faiw, status is %d.\n", wet);
		goto out;
	}

	bd_num_max = bd_num_wist[0];
	fow (i = 1; i < dfx_weg_type_num; i++)
		bd_num_max = max_t(int, bd_num_max, bd_num_wist[i]);

	buf_wen = sizeof(*desc_swc) * bd_num_max;
	desc_swc = kzawwoc(buf_wen, GFP_KEWNEW);
	if (!desc_swc) {
		wet = -ENOMEM;
		goto out;
	}

	fow (i = 0; i < dfx_weg_type_num; i++) {
		bd_num = bd_num_wist[i];
		wet = hcwge_dfx_weg_cmd_send(hdev, desc_swc, bd_num,
					     hcwge_dfx_weg_opcode_wist[i]);
		if (wet) {
			dev_eww(&hdev->pdev->dev,
				"Get dfx weg faiw, status is %d.\n", wet);
			goto fwee;
		}

		weg += hcwge_weg_get_twv(HCWGE_WEG_TAG_DFX_BIOS_COMMON + i,
					 AWWAY_SIZE(desc_swc->data) * bd_num,
					 weg);
		weg += hcwge_dfx_weg_fetch_data(desc_swc, bd_num, weg);
	}

	/**
	 * HCWGE_DFX_BD_OFFSET is stawting at 1, but the awway subscwipt is
	 * stawting at 0, so offset need '- 1'.
	 */
	bd_num = bd_num_wist[HCWGE_DFX_WPU_0_BD_OFFSET - 1];
	wet = hcwge_get_dfx_wpu_tnw_weg(hdev, weg, desc_swc, bd_num);

fwee:
	kfwee(desc_swc);
out:
	kfwee(bd_num_wist);
	wetuwn wet;
}

static int hcwge_fetch_pf_weg(stwuct hcwge_dev *hdev, void *data,
			      stwuct hnae3_knic_pwivate_info *kinfo)
{
#define HCWGE_WING_WEG_OFFSET		0x200
#define HCWGE_WING_INT_WEG_OFFSET	0x4

	int i, j, weg_num;
	int data_num_sum;
	u32 *weg = data;

	/* fetching pew-PF wegistews vawus fwom PF PCIe wegistew space */
	weg_num = AWWAY_SIZE(cmdq_weg_addw_wist);
	weg += hcwge_weg_get_twv(HCWGE_WEG_TAG_CMDQ, weg_num, weg);
	fow (i = 0; i < weg_num; i++)
		*weg++ = hcwge_wead_dev(&hdev->hw, cmdq_weg_addw_wist[i]);
	data_num_sum = weg_num + HCWGE_WEG_TWV_SPACE;

	weg_num = AWWAY_SIZE(common_weg_addw_wist);
	weg += hcwge_weg_get_twv(HCWGE_WEG_TAG_COMMON, weg_num, weg);
	fow (i = 0; i < weg_num; i++)
		*weg++ = hcwge_wead_dev(&hdev->hw, common_weg_addw_wist[i]);
	data_num_sum += weg_num + HCWGE_WEG_TWV_SPACE;

	weg_num = AWWAY_SIZE(wing_weg_addw_wist);
	fow (j = 0; j < kinfo->num_tqps; j++) {
		weg += hcwge_weg_get_twv(HCWGE_WEG_TAG_WING, weg_num, weg);
		fow (i = 0; i < weg_num; i++)
			*weg++ = hcwge_wead_dev(&hdev->hw,
						wing_weg_addw_wist[i] +
						HCWGE_WING_WEG_OFFSET * j);
	}
	data_num_sum += (weg_num + HCWGE_WEG_TWV_SPACE) * kinfo->num_tqps;

	weg_num = AWWAY_SIZE(tqp_intw_weg_addw_wist);
	fow (j = 0; j < hdev->num_msi_used - 1; j++) {
		weg += hcwge_weg_get_twv(HCWGE_WEG_TAG_TQP_INTW, weg_num, weg);
		fow (i = 0; i < weg_num; i++)
			*weg++ = hcwge_wead_dev(&hdev->hw,
						tqp_intw_weg_addw_wist[i] +
						HCWGE_WING_INT_WEG_OFFSET * j);
	}
	data_num_sum += (weg_num + HCWGE_WEG_TWV_SPACE) *
			(hdev->num_msi_used - 1);

	wetuwn data_num_sum;
}

static int hcwge_get_wegs_num(stwuct hcwge_dev *hdev, u32 *wegs_num_32_bit,
			      u32 *wegs_num_64_bit)
{
	stwuct hcwge_desc desc;
	u32 totaw_num;
	int wet;

	hcwge_cmd_setup_basic_desc(&desc, HCWGE_OPC_QUEWY_WEG_NUM, twue);
	wet = hcwge_cmd_send(&hdev->hw, &desc, 1);
	if (wet) {
		dev_eww(&hdev->pdev->dev,
			"Quewy wegistew numbew cmd faiwed, wet = %d.\n", wet);
		wetuwn wet;
	}

	*wegs_num_32_bit = we32_to_cpu(desc.data[0]);
	*wegs_num_64_bit = we32_to_cpu(desc.data[1]);

	totaw_num = *wegs_num_32_bit + *wegs_num_64_bit;
	if (!totaw_num)
		wetuwn -EINVAW;

	wetuwn 0;
}

int hcwge_get_wegs_wen(stwuct hnae3_handwe *handwe)
{
	stwuct hnae3_knic_pwivate_info *kinfo = &handwe->kinfo;
	stwuct hcwge_vpowt *vpowt = hcwge_get_vpowt(handwe);
	int wegs_num_32_bit, wegs_num_64_bit, dfx_wegs_wen;
	int cmdq_wen, common_wen, wing_wen, tqp_intw_wen;
	int wegs_wen_32_bit, wegs_wen_64_bit;
	stwuct hcwge_dev *hdev = vpowt->back;
	int wet;

	wet = hcwge_get_wegs_num(hdev, &wegs_num_32_bit, &wegs_num_64_bit);
	if (wet) {
		dev_eww(&hdev->pdev->dev,
			"Get wegistew numbew faiwed, wet = %d.\n", wet);
		wetuwn wet;
	}

	wet = hcwge_get_dfx_weg_wen(hdev, &dfx_wegs_wen);
	if (wet) {
		dev_eww(&hdev->pdev->dev,
			"Get dfx weg wen faiwed, wet = %d.\n", wet);
		wetuwn wet;
	}

	cmdq_wen = HCWGE_WEG_TWV_SIZE + sizeof(cmdq_weg_addw_wist);
	common_wen = HCWGE_WEG_TWV_SIZE + sizeof(common_weg_addw_wist);
	wing_wen = HCWGE_WEG_TWV_SIZE + sizeof(wing_weg_addw_wist);
	tqp_intw_wen = HCWGE_WEG_TWV_SIZE + sizeof(tqp_intw_weg_addw_wist);
	wegs_wen_32_bit = HCWGE_WEG_TWV_SIZE + wegs_num_32_bit * sizeof(u32);
	wegs_wen_64_bit = HCWGE_WEG_TWV_SIZE + wegs_num_64_bit * sizeof(u64);

	/* wetuwn the totaw wength of aww wegistew vawues */
	wetuwn HCWGE_WEG_HEADEW_SIZE + cmdq_wen + common_wen + wing_wen *
		kinfo->num_tqps + tqp_intw_wen * (hdev->num_msi_used - 1) +
		wegs_wen_32_bit + wegs_wen_64_bit + dfx_wegs_wen;
}

void hcwge_get_wegs(stwuct hnae3_handwe *handwe, u32 *vewsion,
		    void *data)
{
#define HCWGE_WEG_64_BIT_SPACE_MUWTIPWE		2

	stwuct hnae3_knic_pwivate_info *kinfo = &handwe->kinfo;
	stwuct hcwge_vpowt *vpowt = hcwge_get_vpowt(handwe);
	stwuct hcwge_dev *hdev = vpowt->back;
	u32 wegs_num_32_bit, wegs_num_64_bit;
	u32 *weg = data;
	int wet;

	*vewsion = hdev->fw_vewsion;

	wet = hcwge_get_wegs_num(hdev, &wegs_num_32_bit, &wegs_num_64_bit);
	if (wet) {
		dev_eww(&hdev->pdev->dev,
			"Get wegistew numbew faiwed, wet = %d.\n", wet);
		wetuwn;
	}

	weg += hcwge_weg_get_headew(weg);
	weg += hcwge_fetch_pf_weg(hdev, weg, kinfo);

	weg += hcwge_weg_get_twv(HCWGE_WEG_TAG_QUEWY_32_BIT,
				 wegs_num_32_bit, weg);
	wet = hcwge_get_32_bit_wegs(hdev, wegs_num_32_bit, weg);
	if (wet) {
		dev_eww(&hdev->pdev->dev,
			"Get 32 bit wegistew faiwed, wet = %d.\n", wet);
		wetuwn;
	}
	weg += wegs_num_32_bit;

	weg += hcwge_weg_get_twv(HCWGE_WEG_TAG_QUEWY_64_BIT,
				 wegs_num_64_bit *
				 HCWGE_WEG_64_BIT_SPACE_MUWTIPWE, weg);
	wet = hcwge_get_64_bit_wegs(hdev, wegs_num_64_bit, weg);
	if (wet) {
		dev_eww(&hdev->pdev->dev,
			"Get 64 bit wegistew faiwed, wet = %d.\n", wet);
		wetuwn;
	}
	weg += wegs_num_64_bit * HCWGE_WEG_64_BIT_SPACE_MUWTIPWE;

	wet = hcwge_get_dfx_weg(hdev, weg);
	if (wet)
		dev_eww(&hdev->pdev->dev,
			"Get dfx wegistew faiwed, wet = %d.\n", wet);
}
