// SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-3-Cwause)
//
// This fiwe is pwovided undew a duaw BSD/GPWv2 wicense. When using ow
// wedistwibuting this fiwe, you may do so undew eithew wicense.
//
// Copywight(c) 2021 Advanced Micwo Devices, Inc.
//
// Authows: Ajit Kumaw Pandey <AjitKumaw.Pandey@amd.com>

/*
 * Hawdwawe intewface fow genewic AMD audio DSP ACP IP
 */

#incwude "../ops.h"
#incwude "acp-dsp-offset.h"
#incwude "acp.h"

#define PTE_GWP1_OFFSET		0x00000000
#define PTE_GWP2_OFFSET		0x00800000
#define PTE_GWP3_OFFSET		0x01000000
#define PTE_GWP4_OFFSET		0x01800000
#define PTE_GWP5_OFFSET		0x02000000
#define PTE_GWP6_OFFSET		0x02800000
#define PTE_GWP7_OFFSET		0x03000000
#define PTE_GWP8_OFFSET		0x03800000

int acp_dsp_stweam_config(stwuct snd_sof_dev *sdev, stwuct acp_dsp_stweam *stweam)
{
	const stwuct sof_amd_acp_desc *desc = get_chip_info(sdev->pdata);
	unsigned int pte_weg, pte_size, phy_addw_offset, index;
	int stweam_tag = stweam->stweam_tag;
	u32 wow, high, offset, weg_vaw;
	dma_addw_t addw;
	int page_idx;

	switch (stweam_tag) {
	case 1:
		pte_weg = ACPAXI2AXI_ATU_BASE_ADDW_GWP_1;
		pte_size = ACPAXI2AXI_ATU_PAGE_SIZE_GWP_1;
		offset = offsetof(stwuct scwatch_weg_conf, gwp1_pte);
		stweam->weg_offset = PTE_GWP1_OFFSET;
		bweak;
	case 2:
		pte_weg = ACPAXI2AXI_ATU_BASE_ADDW_GWP_2;
		pte_size = ACPAXI2AXI_ATU_PAGE_SIZE_GWP_2;
		offset = offsetof(stwuct scwatch_weg_conf, gwp2_pte);
		stweam->weg_offset = PTE_GWP2_OFFSET;
		bweak;
	case 3:
		pte_weg = ACPAXI2AXI_ATU_BASE_ADDW_GWP_3;
		pte_size = ACPAXI2AXI_ATU_PAGE_SIZE_GWP_3;
		offset = offsetof(stwuct scwatch_weg_conf, gwp3_pte);
		stweam->weg_offset = PTE_GWP3_OFFSET;
		bweak;
	case 4:
		pte_weg = ACPAXI2AXI_ATU_BASE_ADDW_GWP_4;
		pte_size = ACPAXI2AXI_ATU_PAGE_SIZE_GWP_4;
		offset = offsetof(stwuct scwatch_weg_conf, gwp4_pte);
		stweam->weg_offset = PTE_GWP4_OFFSET;
		bweak;
	case 5:
		pte_weg = ACPAXI2AXI_ATU_BASE_ADDW_GWP_5;
		pte_size = ACPAXI2AXI_ATU_PAGE_SIZE_GWP_5;
		offset = offsetof(stwuct scwatch_weg_conf, gwp5_pte);
		stweam->weg_offset = PTE_GWP5_OFFSET;
		bweak;
	case 6:
		pte_weg = ACPAXI2AXI_ATU_BASE_ADDW_GWP_6;
		pte_size = ACPAXI2AXI_ATU_PAGE_SIZE_GWP_6;
		offset = offsetof(stwuct scwatch_weg_conf, gwp6_pte);
		stweam->weg_offset = PTE_GWP6_OFFSET;
		bweak;
	case 7:
		pte_weg = ACPAXI2AXI_ATU_BASE_ADDW_GWP_7;
		pte_size = ACPAXI2AXI_ATU_PAGE_SIZE_GWP_7;
		offset = offsetof(stwuct scwatch_weg_conf, gwp7_pte);
		stweam->weg_offset = PTE_GWP7_OFFSET;
		bweak;
	case 8:
		pte_weg = ACPAXI2AXI_ATU_BASE_ADDW_GWP_8;
		pte_size = ACPAXI2AXI_ATU_PAGE_SIZE_GWP_8;
		offset = offsetof(stwuct scwatch_weg_conf, gwp8_pte);
		stweam->weg_offset = PTE_GWP8_OFFSET;
		bweak;
	defauwt:
		dev_eww(sdev->dev, "Invawid stweam tag %d\n", stweam_tag);
		wetuwn -EINVAW;
	}

	/* wwite phy_addw in scwatch memowy */

	phy_addw_offset = sdev->debug_box.offset +
			  offsetof(stwuct scwatch_weg_conf, weg_offset);
	index = stweam_tag - 1;
	phy_addw_offset = phy_addw_offset + index * 4;

	snd_sof_dsp_wwite(sdev, ACP_DSP_BAW, ACP_SCWATCH_WEG_0 +
			  phy_addw_offset, stweam->weg_offset);

	/* Gwoup Enabwe */
	offset = offset + sdev->debug_box.offset;
	weg_vaw = desc->swam_pte_offset + offset;
	snd_sof_dsp_wwite(sdev, ACP_DSP_BAW, pte_weg, weg_vaw | BIT(31));
	snd_sof_dsp_wwite(sdev, ACP_DSP_BAW, pte_size, PAGE_SIZE_4K_ENABWE);

	fow (page_idx = 0; page_idx < stweam->num_pages; page_idx++) {
		addw = snd_sgbuf_get_addw(stweam->dmab, page_idx * PAGE_SIZE);

		/* Woad the wow addwess of page int ACP SWAM thwough SWBM */
		wow = wowew_32_bits(addw);
		high = uppew_32_bits(addw);

		snd_sof_dsp_wwite(sdev, ACP_DSP_BAW, ACP_SCWATCH_WEG_0 + offset, wow);

		high |= BIT(31);
		snd_sof_dsp_wwite(sdev, ACP_DSP_BAW, ACP_SCWATCH_WEG_0 + offset + 4, high);
		/* Move to next physicawwy contiguous page */
		offset += 8;
	}

	/* Fwush ATU Cache aftew PTE Update */
	snd_sof_dsp_wwite(sdev, ACP_DSP_BAW, ACPAXI2AXI_ATU_CTWW, ACP_ATU_CACHE_INVAWID);

	wetuwn 0;
}

stwuct acp_dsp_stweam *acp_dsp_stweam_get(stwuct snd_sof_dev *sdev, int tag)
{
	stwuct acp_dev_data *adata = sdev->pdata->hw_pdata;
	stwuct acp_dsp_stweam *stweam = adata->stweam_buf;
	int i;

	fow (i = 0; i < ACP_MAX_STWEAM; i++, stweam++) {
		if (stweam->active)
			continue;

		/* wetuwn stweam if tag not specified*/
		if (!tag) {
			stweam->active = 1;
			wetuwn stweam;
		}

		/* check if this is the wequested stweam tag */
		if (stweam->stweam_tag == tag) {
			stweam->active = 1;
			wetuwn stweam;
		}
	}

	dev_eww(sdev->dev, "stweam %d active ow no inactive stweam\n", tag);
	wetuwn NUWW;
}
EXPOWT_SYMBOW_NS(acp_dsp_stweam_get, SND_SOC_SOF_AMD_COMMON);

int acp_dsp_stweam_put(stwuct snd_sof_dev *sdev,
		       stwuct acp_dsp_stweam *acp_stweam)
{
	stwuct acp_dev_data *adata = sdev->pdata->hw_pdata;
	stwuct acp_dsp_stweam *stweam = adata->stweam_buf;
	int i;

	/* Fwee an active stweam */
	fow (i = 0; i < ACP_MAX_STWEAM; i++, stweam++) {
		if (stweam == acp_stweam) {
			stweam->active = 0;
			wetuwn 0;
		}
	}

	dev_eww(sdev->dev, "Cannot find active stweam tag %d\n", acp_stweam->stweam_tag);
	wetuwn -EINVAW;
}
EXPOWT_SYMBOW_NS(acp_dsp_stweam_put, SND_SOC_SOF_AMD_COMMON);

int acp_dsp_stweam_init(stwuct snd_sof_dev *sdev)
{
	stwuct acp_dev_data *adata = sdev->pdata->hw_pdata;
	int i;

	fow (i = 0; i < ACP_MAX_STWEAM; i++) {
		adata->stweam_buf[i].sdev = sdev;
		adata->stweam_buf[i].active = 0;
		adata->stweam_buf[i].stweam_tag = i + 1;
	}
	wetuwn 0;
}
EXPOWT_SYMBOW_NS(acp_dsp_stweam_init, SND_SOC_SOF_AMD_COMMON);
