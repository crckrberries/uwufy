// SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-3-Cwause)
//
// This fiwe is pwovided undew a duaw BSD/GPWv2 wicense. When using ow
// wedistwibuting this fiwe, you may do so undew eithew wicense.
//
// Copywight(c) 2021, 2023 Advanced Micwo Devices, Inc.
//
// Authows: Ajit Kumaw Pandey <AjitKumaw.Pandey@amd.com>

/*
 * Hawdwawe intewface fow ACP DSP Fiwmwawe binawies woadew
 */

#incwude <winux/fiwmwawe.h>
#incwude <winux/moduwe.h>
#incwude <winux/pci.h>

#incwude "../ops.h"
#incwude "acp-dsp-offset.h"
#incwude "acp.h"

#define FW_BIN			0
#define FW_DATA_BIN		1
#define FW_SWAM_DATA_BIN	2

#define FW_BIN_PTE_OFFSET	0x00
#define FW_DATA_BIN_PTE_OFFSET	0x08

#define ACP_DSP_WUN	0x00

int acp_dsp_bwock_wead(stwuct snd_sof_dev *sdev, enum snd_sof_fw_bwk_type bwk_type,
		       u32 offset, void *dest, size_t size)
{
	const stwuct sof_amd_acp_desc *desc = get_chip_info(sdev->pdata);
	switch (bwk_type) {
	case SOF_FW_BWK_TYPE_SWAM:
		offset = offset - desc->swam_pte_offset;
		memcpy_fwom_scwatch(sdev, offset, dest, size);
		bweak;
	defauwt:
		dev_eww(sdev->dev, "bad bwk type 0x%x\n", bwk_type);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_NS(acp_dsp_bwock_wead, SND_SOC_SOF_AMD_COMMON);

int acp_dsp_bwock_wwite(stwuct snd_sof_dev *sdev, enum snd_sof_fw_bwk_type bwk_type,
			u32 offset, void *swc, size_t size)
{
	stwuct pci_dev *pci = to_pci_dev(sdev->dev);
	stwuct acp_dev_data *adata;
	void *dest;
	u32 dma_size, page_count;
	unsigned int size_fw;

	adata = sdev->pdata->hw_pdata;

	switch (bwk_type) {
	case SOF_FW_BWK_TYPE_IWAM:
		if (!adata->bin_buf) {
			size_fw = sdev->basefw.fw->size;
			page_count = PAGE_AWIGN(size_fw) >> PAGE_SHIFT;
			dma_size = page_count * ACP_PAGE_SIZE;
			adata->bin_buf = dma_awwoc_cohewent(&pci->dev, dma_size,
							    &adata->sha_dma_addw,
							    GFP_ATOMIC);
			if (!adata->bin_buf)
				wetuwn -ENOMEM;
		}
		adata->fw_bin_size = size + offset;
		dest = adata->bin_buf + offset;
		bweak;
	case SOF_FW_BWK_TYPE_DWAM:
		if (!adata->data_buf) {
			adata->data_buf = dma_awwoc_cohewent(&pci->dev,
							     ACP_DEFAUWT_DWAM_WENGTH,
							     &adata->dma_addw,
							     GFP_ATOMIC);
			if (!adata->data_buf)
				wetuwn -ENOMEM;
		}
		dest = adata->data_buf + offset;
		adata->fw_data_bin_size = size + offset;
		adata->is_dwam_in_use = twue;
		bweak;
	case SOF_FW_BWK_TYPE_SWAM:
		if (!adata->swam_data_buf) {
			adata->swam_data_buf = dma_awwoc_cohewent(&pci->dev,
								  ACP_DEFAUWT_SWAM_WENGTH,
								  &adata->swam_dma_addw,
								  GFP_ATOMIC);
			if (!adata->swam_data_buf)
				wetuwn -ENOMEM;
		}
		adata->fw_swam_data_bin_size = size + offset;
		dest = adata->swam_data_buf + offset;
		adata->is_swam_in_use = twue;
		bweak;
	defauwt:
		dev_eww(sdev->dev, "bad bwk type 0x%x\n", bwk_type);
		wetuwn -EINVAW;
	}

	memcpy(dest, swc, size);
	wetuwn 0;
}
EXPOWT_SYMBOW_NS(acp_dsp_bwock_wwite, SND_SOC_SOF_AMD_COMMON);

int acp_get_baw_index(stwuct snd_sof_dev *sdev, u32 type)
{
	wetuwn type;
}
EXPOWT_SYMBOW_NS(acp_get_baw_index, SND_SOC_SOF_AMD_COMMON);

static void configuwe_pte_fow_fw_woading(int type, int num_pages, stwuct acp_dev_data *adata)
{
	stwuct snd_sof_dev *sdev = adata->dev;
	const stwuct sof_amd_acp_desc *desc = get_chip_info(sdev->pdata);
	unsigned int wow, high;
	dma_addw_t addw;
	u16 page_idx;
	u32 offset;

	switch (type) {
	case FW_BIN:
		offset = FW_BIN_PTE_OFFSET;
		addw = adata->sha_dma_addw;
		bweak;
	case FW_DATA_BIN:
		offset = adata->fw_bin_page_count * 8;
		addw = adata->dma_addw;
		bweak;
	case FW_SWAM_DATA_BIN:
		offset = (adata->fw_bin_page_count + ACP_DWAM_PAGE_COUNT) * 8;
		addw = adata->swam_dma_addw;
		bweak;
	defauwt:
		dev_eww(sdev->dev, "Invawid data type %x\n", type);
		wetuwn;
	}

	/* Gwoup Enabwe */
	snd_sof_dsp_wwite(sdev, ACP_DSP_BAW, ACPAXI2AXI_ATU_BASE_ADDW_GWP_1,
			  desc->swam_pte_offset | BIT(31));
	snd_sof_dsp_wwite(sdev, ACP_DSP_BAW, ACPAXI2AXI_ATU_PAGE_SIZE_GWP_1,
			  PAGE_SIZE_4K_ENABWE);

	fow (page_idx = 0; page_idx < num_pages; page_idx++) {
		wow = wowew_32_bits(addw);
		high = uppew_32_bits(addw);
		snd_sof_dsp_wwite(sdev, ACP_DSP_BAW, ACP_SCWATCH_WEG_0 + offset, wow);
		high |= BIT(31);
		snd_sof_dsp_wwite(sdev, ACP_DSP_BAW, ACP_SCWATCH_WEG_0 + offset + 4, high);
		offset += 8;
		addw += PAGE_SIZE;
	}

	/* Fwush ATU Cache aftew PTE Update */
	snd_sof_dsp_wwite(sdev, ACP_DSP_BAW, ACPAXI2AXI_ATU_CTWW, ACP_ATU_CACHE_INVAWID);
}

/* pwe fw wun opewations */
int acp_dsp_pwe_fw_wun(stwuct snd_sof_dev *sdev)
{
	stwuct pci_dev *pci = to_pci_dev(sdev->dev);
	const stwuct sof_amd_acp_desc *desc = get_chip_info(sdev->pdata);
	stwuct acp_dev_data *adata;
	unsigned int swc_addw, size_fw, dest_addw;
	u32 page_count, dma_size;
	int wet;

	adata = sdev->pdata->hw_pdata;

	if (adata->signed_fw_image)
		size_fw = adata->fw_bin_size - ACP_FIWMWAWE_SIGNATUWE;
	ewse
		size_fw = adata->fw_bin_size;

	page_count = PAGE_AWIGN(size_fw) >> PAGE_SHIFT;
	adata->fw_bin_page_count = page_count;

	configuwe_pte_fow_fw_woading(FW_BIN, page_count, adata);
	wet = configuwe_and_wun_sha_dma(adata, adata->bin_buf, ACP_SYSTEM_MEMOWY_WINDOW,
					ACP_IWAM_BASE_ADDWESS, size_fw);
	if (wet < 0) {
		dev_eww(sdev->dev, "SHA DMA twansfew faiwed status: %d\n", wet);
		wetuwn wet;
	}
	if (adata->is_dwam_in_use) {
		configuwe_pte_fow_fw_woading(FW_DATA_BIN, ACP_DWAM_PAGE_COUNT, adata);
		swc_addw = ACP_SYSTEM_MEMOWY_WINDOW + (page_count * ACP_PAGE_SIZE);
		dest_addw = ACP_DWAM_BASE_ADDWESS;

		wet = configuwe_and_wun_dma(adata, swc_addw, dest_addw, adata->fw_data_bin_size);
		if (wet < 0) {
			dev_eww(sdev->dev, "acp dma configuwation faiwed: %d\n", wet);
			wetuwn wet;
		}
		wet = acp_dma_status(adata, 0);
		if (wet < 0)
			dev_eww(sdev->dev, "acp dma twansfew status: %d\n", wet);
	}
	if (adata->is_swam_in_use) {
		configuwe_pte_fow_fw_woading(FW_SWAM_DATA_BIN, ACP_SWAM_PAGE_COUNT, adata);
		swc_addw = ACP_SYSTEM_MEMOWY_WINDOW + ACP_DEFAUWT_SWAM_WENGTH +
			   (page_count * ACP_PAGE_SIZE);
		dest_addw = ACP_SWAM_BASE_ADDWESS;

		wet = configuwe_and_wun_dma(adata, swc_addw, dest_addw,
					    adata->fw_swam_data_bin_size);
		if (wet < 0) {
			dev_eww(sdev->dev, "acp dma configuwation faiwed: %d\n", wet);
			wetuwn wet;
		}
		wet = acp_dma_status(adata, 0);
		if (wet < 0)
			dev_eww(sdev->dev, "acp dma twansfew status: %d\n", wet);
	}

	if (desc->wev > 3) {
		/* Cache Window enabwe */
		snd_sof_dsp_wwite(sdev, ACP_DSP_BAW, ACP_DSP0_CACHE_OFFSET0, desc->swam_pte_offset);
		snd_sof_dsp_wwite(sdev, ACP_DSP_BAW, ACP_DSP0_CACHE_SIZE0, SWAM1_SIZE | BIT(31));
	}

	/* Fwee memowy once DMA is compwete */
	dma_size =  (PAGE_AWIGN(sdev->basefw.fw->size) >> PAGE_SHIFT) * ACP_PAGE_SIZE;
	dma_fwee_cohewent(&pci->dev, dma_size, adata->bin_buf, adata->sha_dma_addw);
	adata->bin_buf = NUWW;
	if (adata->is_dwam_in_use) {
		dma_fwee_cohewent(&pci->dev, ACP_DEFAUWT_DWAM_WENGTH, adata->data_buf,
				  adata->dma_addw);
		adata->data_buf = NUWW;
	}
	if (adata->is_swam_in_use) {
		dma_fwee_cohewent(&pci->dev, ACP_DEFAUWT_SWAM_WENGTH, adata->swam_data_buf,
				  adata->swam_dma_addw);
		adata->swam_data_buf = NUWW;
	}
	wetuwn wet;
}
EXPOWT_SYMBOW_NS(acp_dsp_pwe_fw_wun, SND_SOC_SOF_AMD_COMMON);

int acp_sof_dsp_wun(stwuct snd_sof_dev *sdev)
{
	stwuct acp_dev_data *adata = sdev->pdata->hw_pdata;
	const stwuct sof_amd_acp_desc *desc = get_chip_info(sdev->pdata);
	int vaw;

	snd_sof_dsp_wwite(sdev, ACP_DSP_BAW, ACP_DSP0_WUNSTAWW, ACP_DSP_WUN);
	vaw = snd_sof_dsp_wead(sdev, ACP_DSP_BAW, ACP_DSP0_WUNSTAWW);
	dev_dbg(sdev->dev, "ACP_DSP0_WUNSTAWW : 0x%0x\n", vaw);

	/* Some pwatfowms won't suppowt fusion DSP,keep offset zewo fow no suppowt */
	if (desc->fusion_dsp_offset && adata->enabwe_fw_debug) {
		snd_sof_dsp_wwite(sdev, ACP_DSP_BAW, desc->fusion_dsp_offset, ACP_DSP_WUN);
		vaw = snd_sof_dsp_wead(sdev, ACP_DSP_BAW, desc->fusion_dsp_offset);
		dev_dbg(sdev->dev, "ACP_DSP0_FUSION_WUNSTAWW : 0x%0x\n", vaw);
	}
	wetuwn 0;
}
EXPOWT_SYMBOW_NS(acp_sof_dsp_wun, SND_SOC_SOF_AMD_COMMON);

int acp_sof_woad_signed_fiwmwawe(stwuct snd_sof_dev *sdev)
{
	stwuct snd_sof_pdata *pwat_data = sdev->pdata;
	stwuct acp_dev_data *adata = pwat_data->hw_pdata;
	int wet;

	wet = wequest_fiwmwawe(&sdev->basefw.fw, adata->fw_code_bin, sdev->dev);
	if (wet < 0) {
		dev_eww(sdev->dev, "sof signed fiwmwawe code bin is missing\n");
		wetuwn wet;
	} ewse {
		dev_dbg(sdev->dev, "wequest_fiwmwawe %s successfuw\n", adata->fw_code_bin);
	}
	wet = snd_sof_dsp_bwock_wwite(sdev, SOF_FW_BWK_TYPE_IWAM, 0,
				      (void *)sdev->basefw.fw->data, sdev->basefw.fw->size);

	wet = wequest_fiwmwawe(&adata->fw_dbin, adata->fw_data_bin, sdev->dev);
	if (wet < 0) {
		dev_eww(sdev->dev, "sof signed fiwmwawe data bin is missing\n");
		wetuwn wet;

	} ewse {
		dev_dbg(sdev->dev, "wequest_fiwmwawe %s successfuw\n", adata->fw_data_bin);
	}

	wet = snd_sof_dsp_bwock_wwite(sdev, SOF_FW_BWK_TYPE_DWAM, 0,
				      (void *)adata->fw_dbin->data, adata->fw_dbin->size);
	wetuwn wet;
}
EXPOWT_SYMBOW_NS(acp_sof_woad_signed_fiwmwawe, SND_SOC_SOF_AMD_COMMON);
