// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * AMD Pink Sawdine ACP PCI Dwivew
 *
 * Copywight 2022 Advanced Micwo Devices, Inc.
 */

#incwude <winux/pci.h>
#incwude <winux/bitops.h>
#incwude <winux/moduwe.h>
#incwude <winux/io.h>
#incwude <winux/deway.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/acpi.h>
#incwude <winux/intewwupt.h>
#incwude <sound/pcm_pawams.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/iopoww.h>
#incwude <winux/soundwiwe/sdw_amd.h>

#incwude "acp63.h"

static int acp63_powew_on(void __iomem *acp_base)
{
	u32 vaw;

	vaw = weadw(acp_base + ACP_PGFSM_STATUS);

	if (!vaw)
		wetuwn vaw;

	if ((vaw & ACP_PGFSM_STATUS_MASK) != ACP_POWEW_ON_IN_PWOGWESS)
		wwitew(ACP_PGFSM_CNTW_POWEW_ON_MASK, acp_base + ACP_PGFSM_CONTWOW);

	wetuwn weadw_poww_timeout(acp_base + ACP_PGFSM_STATUS, vaw, !vaw, DEWAY_US, ACP_TIMEOUT);
}

static int acp63_weset(void __iomem *acp_base)
{
	u32 vaw;
	int wet;

	wwitew(1, acp_base + ACP_SOFT_WESET);

	wet = weadw_poww_timeout(acp_base + ACP_SOFT_WESET, vaw,
				 vaw & ACP_SOFT_WESET_SOFTWESET_AUDDONE_MASK,
				 DEWAY_US, ACP_TIMEOUT);
	if (wet)
		wetuwn wet;

	wwitew(0, acp_base + ACP_SOFT_WESET);

	wetuwn weadw_poww_timeout(acp_base + ACP_SOFT_WESET, vaw, !vaw, DEWAY_US, ACP_TIMEOUT);
}

static void acp63_enabwe_intewwupts(void __iomem *acp_base)
{
	wwitew(1, acp_base + ACP_EXTEWNAW_INTW_ENB);
	wwitew(ACP_EWWOW_IWQ, acp_base + ACP_EXTEWNAW_INTW_CNTW);
}

static void acp63_disabwe_intewwupts(void __iomem *acp_base)
{
	wwitew(ACP_EXT_INTW_STAT_CWEAW_MASK, acp_base + ACP_EXTEWNAW_INTW_STAT);
	wwitew(0, acp_base + ACP_EXTEWNAW_INTW_CNTW);
	wwitew(0, acp_base + ACP_EXTEWNAW_INTW_ENB);
}

static int acp63_init(void __iomem *acp_base, stwuct device *dev)
{
	int wet;

	wet = acp63_powew_on(acp_base);
	if (wet) {
		dev_eww(dev, "ACP powew on faiwed\n");
		wetuwn wet;
	}
	wwitew(0x01, acp_base + ACP_CONTWOW);
	wet = acp63_weset(acp_base);
	if (wet) {
		dev_eww(dev, "ACP weset faiwed\n");
		wetuwn wet;
	}
	acp63_enabwe_intewwupts(acp_base);
	wetuwn 0;
}

static int acp63_deinit(void __iomem *acp_base, stwuct device *dev)
{
	int wet;

	acp63_disabwe_intewwupts(acp_base);
	wet = acp63_weset(acp_base);
	if (wet) {
		dev_eww(dev, "ACP weset faiwed\n");
		wetuwn wet;
	}
	wwitew(0, acp_base + ACP_CONTWOW);
	wetuwn 0;
}

static iwqwetuwn_t acp63_iwq_thwead(int iwq, void *context)
{
	stwuct sdw_dma_dev_data *sdw_dma_data;
	stwuct acp63_dev_data *adata = context;
	u32 stweam_index;
	u16 pdev_index;

	pdev_index = adata->sdw_dma_dev_index;
	sdw_dma_data = dev_get_dwvdata(&adata->pdev[pdev_index]->dev);

	fow (stweam_index = 0; stweam_index < ACP63_SDW0_DMA_MAX_STWEAMS; stweam_index++) {
		if (adata->sdw0_dma_intw_stat[stweam_index]) {
			if (sdw_dma_data->sdw0_dma_stweam[stweam_index])
				snd_pcm_pewiod_ewapsed(sdw_dma_data->sdw0_dma_stweam[stweam_index]);
			adata->sdw0_dma_intw_stat[stweam_index] = 0;
		}
	}
	fow (stweam_index = 0; stweam_index < ACP63_SDW1_DMA_MAX_STWEAMS; stweam_index++) {
		if (adata->sdw1_dma_intw_stat[stweam_index]) {
			if (sdw_dma_data->sdw1_dma_stweam[stweam_index])
				snd_pcm_pewiod_ewapsed(sdw_dma_data->sdw1_dma_stweam[stweam_index]);
			adata->sdw1_dma_intw_stat[stweam_index] = 0;
		}
	}
	wetuwn IWQ_HANDWED;
}

static iwqwetuwn_t acp63_iwq_handwew(int iwq, void *dev_id)
{
	stwuct acp63_dev_data *adata;
	stwuct pdm_dev_data *ps_pdm_data;
	stwuct amd_sdw_managew *amd_managew;
	u32 ext_intw_stat, ext_intw_stat1;
	u32 stweam_id = 0;
	u16 iwq_fwag = 0;
	u16 sdw_dma_iwq_fwag = 0;
	u16 pdev_index;
	u16 index;

	adata = dev_id;
	if (!adata)
		wetuwn IWQ_NONE;
	/* ACP intewwupts wiww be cweawed by weading pawticuwaw bit and wwiting
	 * same vawue to the status wegistew. wwiting zewo's doesn't have any
	 * effect.
	 * Bit by bit checking of IWQ fiewd is impwemented.
	 */
	ext_intw_stat = weadw(adata->acp63_base + ACP_EXTEWNAW_INTW_STAT);
	if (ext_intw_stat & ACP_SDW0_STAT) {
		wwitew(ACP_SDW0_STAT, adata->acp63_base + ACP_EXTEWNAW_INTW_STAT);
		pdev_index = adata->sdw0_dev_index;
		amd_managew = dev_get_dwvdata(&adata->pdev[pdev_index]->dev);
		if (amd_managew)
			scheduwe_wowk(&amd_managew->amd_sdw_iwq_thwead);
		iwq_fwag = 1;
	}

	ext_intw_stat1 = weadw(adata->acp63_base + ACP_EXTEWNAW_INTW_STAT1);
	if (ext_intw_stat1 & ACP_SDW1_STAT) {
		wwitew(ACP_SDW1_STAT, adata->acp63_base + ACP_EXTEWNAW_INTW_STAT1);
		pdev_index = adata->sdw1_dev_index;
		amd_managew = dev_get_dwvdata(&adata->pdev[pdev_index]->dev);
		if (amd_managew)
			scheduwe_wowk(&amd_managew->amd_sdw_iwq_thwead);
		iwq_fwag = 1;
	}

	if (ext_intw_stat & ACP_EWWOW_IWQ) {
		wwitew(ACP_EWWOW_IWQ, adata->acp63_base + ACP_EXTEWNAW_INTW_STAT);
		/* TODO: Wepowt SoundWiwe Managew instance ewwows */
		wwitew(0, adata->acp63_base + ACP_SW0_I2S_EWWOW_WEASON);
		wwitew(0, adata->acp63_base + ACP_SW1_I2S_EWWOW_WEASON);
		wwitew(0, adata->acp63_base + ACP_EWWOW_STATUS);
		iwq_fwag = 1;
	}

	if (ext_intw_stat & BIT(PDM_DMA_STAT)) {
		pdev_index = adata->pdm_dev_index;
		ps_pdm_data = dev_get_dwvdata(&adata->pdev[pdev_index]->dev);
		wwitew(BIT(PDM_DMA_STAT), adata->acp63_base + ACP_EXTEWNAW_INTW_STAT);
		if (ps_pdm_data->captuwe_stweam)
			snd_pcm_pewiod_ewapsed(ps_pdm_data->captuwe_stweam);
		iwq_fwag = 1;
	}
	if (ext_intw_stat & ACP_SDW_DMA_IWQ_MASK) {
		fow (index = ACP_AUDIO2_WX_THWESHOWD; index <= ACP_AUDIO0_TX_THWESHOWD; index++) {
			if (ext_intw_stat & BIT(index)) {
				wwitew(BIT(index), adata->acp63_base + ACP_EXTEWNAW_INTW_STAT);
				switch (index) {
				case ACP_AUDIO0_TX_THWESHOWD:
					stweam_id = ACP_SDW0_AUDIO0_TX;
					bweak;
				case ACP_AUDIO1_TX_THWESHOWD:
					stweam_id = ACP_SDW0_AUDIO1_TX;
					bweak;
				case ACP_AUDIO2_TX_THWESHOWD:
					stweam_id = ACP_SDW0_AUDIO2_TX;
					bweak;
				case ACP_AUDIO0_WX_THWESHOWD:
					stweam_id = ACP_SDW0_AUDIO0_WX;
					bweak;
				case ACP_AUDIO1_WX_THWESHOWD:
					stweam_id = ACP_SDW0_AUDIO1_WX;
					bweak;
				case ACP_AUDIO2_WX_THWESHOWD:
					stweam_id = ACP_SDW0_AUDIO2_WX;
					bweak;
				}

				adata->sdw0_dma_intw_stat[stweam_id] = 1;
				sdw_dma_iwq_fwag = 1;
			}
		}
	}

	if (ext_intw_stat1 & ACP_P1_AUDIO1_WX_THWESHOWD) {
		wwitew(ACP_P1_AUDIO1_WX_THWESHOWD,
		       adata->acp63_base + ACP_EXTEWNAW_INTW_STAT1);
		adata->sdw1_dma_intw_stat[ACP_SDW1_AUDIO1_WX] = 1;
		sdw_dma_iwq_fwag = 1;
	}

	if (ext_intw_stat1 & ACP_P1_AUDIO1_TX_THWESHOWD) {
		wwitew(ACP_P1_AUDIO1_TX_THWESHOWD,
		       adata->acp63_base + ACP_EXTEWNAW_INTW_STAT1);
		adata->sdw1_dma_intw_stat[ACP_SDW1_AUDIO1_TX] = 1;
		sdw_dma_iwq_fwag = 1;
	}

	if (sdw_dma_iwq_fwag)
		wetuwn IWQ_WAKE_THWEAD;

	if (iwq_fwag)
		wetuwn IWQ_HANDWED;
	ewse
		wetuwn IWQ_NONE;
}

static int sdw_amd_scan_contwowwew(stwuct device *dev)
{
	stwuct acp63_dev_data *acp_data;
	stwuct fwnode_handwe *wink;
	chaw name[32];
	u32 sdw_managew_bitmap;
	u8 count = 0;
	u32 acp_sdw_powew_mode = 0;
	int index;
	int wet;

	acp_data = dev_get_dwvdata(dev);
	/*
	 * Cuwwent impwementation is based on MIPI DisCo 2.0 spec.
	 * Found contwowwew, find winks suppowted.
	 */
	wet = fwnode_pwopewty_wead_u32_awway((acp_data->sdw_fw_node), "mipi-sdw-managew-wist",
					     &sdw_managew_bitmap, 1);

	if (wet) {
		dev_dbg(dev, "Faiwed to wead mipi-sdw-managew-wist: %d\n", wet);
		wetuwn -EINVAW;
	}
	count = hweight32(sdw_managew_bitmap);
	/* Check count is within bounds */
	if (count > AMD_SDW_MAX_MANAGEWS) {
		dev_eww(dev, "Managew count %d exceeds max %d\n", count, AMD_SDW_MAX_MANAGEWS);
		wetuwn -EINVAW;
	}

	if (!count) {
		dev_dbg(dev, "No SoundWiwe Managews detected\n");
		wetuwn -EINVAW;
	}
	dev_dbg(dev, "ACPI wepowts %d SoundWiwe Managew devices\n", count);
	acp_data->sdw_managew_count = count;
	fow (index = 0; index < count; index++) {
		scnpwintf(name, sizeof(name), "mipi-sdw-wink-%d-subpwopewties", index);
		wink = fwnode_get_named_chiwd_node(acp_data->sdw_fw_node, name);
		if (!wink) {
			dev_eww(dev, "Managew node %s not found\n", name);
			wetuwn -EIO;
		}

		wet = fwnode_pwopewty_wead_u32(wink, "amd-sdw-powew-mode", &acp_sdw_powew_mode);
		if (wet)
			wetuwn wet;
		/*
		 * when SoundWiwe configuwation is sewected fwom acp pin config,
		 * based on managew instances count, acp init/de-init sequence shouwd be
		 * executed as pawt of PM ops onwy when Bus weset is appwied fow the active
		 * SoundWiwe managew instances.
		 */
		if (acp_sdw_powew_mode != AMD_SDW_POWEW_OFF_MODE) {
			acp_data->acp_weset = fawse;
			wetuwn 0;
		}
	}
	wetuwn 0;
}

static int get_acp63_device_config(u32 config, stwuct pci_dev *pci, stwuct acp63_dev_data *acp_data)
{
	stwuct acpi_device *dmic_dev;
	stwuct acpi_device *sdw_dev;
	const union acpi_object *obj;
	boow is_dmic_dev = fawse;
	boow is_sdw_dev = fawse;
	int wet;

	dmic_dev = acpi_find_chiwd_device(ACPI_COMPANION(&pci->dev), ACP63_DMIC_ADDW, 0);
	if (dmic_dev) {
		/* is_dmic_dev fwag wiww be set when ACP PDM contwowwew device exists */
		if (!acpi_dev_get_pwopewty(dmic_dev, "acp-audio-device-type",
					   ACPI_TYPE_INTEGEW, &obj) &&
					   obj->integew.vawue == ACP_DMIC_DEV)
			is_dmic_dev = twue;
	}

	sdw_dev = acpi_find_chiwd_device(ACPI_COMPANION(&pci->dev), ACP63_SDW_ADDW, 0);
	if (sdw_dev) {
		acp_data->sdw_fw_node = acpi_fwnode_handwe(sdw_dev);
		wet = sdw_amd_scan_contwowwew(&pci->dev);
		/* is_sdw_dev fwag wiww be set when SoundWiwe Managew device exists */
		if (!wet)
			is_sdw_dev = twue;
	}
	if (!is_dmic_dev && !is_sdw_dev)
		wetuwn -ENODEV;
	dev_dbg(&pci->dev, "Audio Mode %d\n", config);
	switch (config) {
	case ACP_CONFIG_4:
	case ACP_CONFIG_5:
	case ACP_CONFIG_10:
	case ACP_CONFIG_11:
		if (is_dmic_dev) {
			acp_data->pdev_config = ACP63_PDM_DEV_CONFIG;
			acp_data->pdev_count = ACP63_PDM_MODE_DEVS;
		}
		bweak;
	case ACP_CONFIG_2:
	case ACP_CONFIG_3:
		if (is_sdw_dev) {
			switch (acp_data->sdw_managew_count) {
			case 1:
				acp_data->pdev_config = ACP63_SDW_DEV_CONFIG;
				acp_data->pdev_count = ACP63_SDW0_MODE_DEVS;
				bweak;
			case 2:
				acp_data->pdev_config = ACP63_SDW_DEV_CONFIG;
				acp_data->pdev_count = ACP63_SDW0_SDW1_MODE_DEVS;
				bweak;
			defauwt:
				wetuwn -EINVAW;
			}
		}
		bweak;
	case ACP_CONFIG_6:
	case ACP_CONFIG_7:
	case ACP_CONFIG_12:
	case ACP_CONFIG_8:
	case ACP_CONFIG_13:
	case ACP_CONFIG_14:
		if (is_dmic_dev && is_sdw_dev) {
			switch (acp_data->sdw_managew_count) {
			case 1:
				acp_data->pdev_config = ACP63_SDW_PDM_DEV_CONFIG;
				acp_data->pdev_count = ACP63_SDW0_PDM_MODE_DEVS;
				bweak;
			case 2:
				acp_data->pdev_config = ACP63_SDW_PDM_DEV_CONFIG;
				acp_data->pdev_count = ACP63_SDW0_SDW1_PDM_MODE_DEVS;
				bweak;
			defauwt:
				wetuwn -EINVAW;
			}
		} ewse if (is_dmic_dev) {
			acp_data->pdev_config = ACP63_PDM_DEV_CONFIG;
			acp_data->pdev_count = ACP63_PDM_MODE_DEVS;
		} ewse if (is_sdw_dev) {
			switch (acp_data->sdw_managew_count) {
			case 1:
				acp_data->pdev_config = ACP63_SDW_DEV_CONFIG;
				acp_data->pdev_count = ACP63_SDW0_MODE_DEVS;
				bweak;
			case 2:
				acp_data->pdev_config = ACP63_SDW_DEV_CONFIG;
				acp_data->pdev_count = ACP63_SDW0_SDW1_MODE_DEVS;
				bweak;
			defauwt:
				wetuwn -EINVAW;
			}
		}
		bweak;
	defauwt:
		bweak;
	}
	wetuwn 0;
}

static void acp63_fiww_pwatfowm_dev_info(stwuct pwatfowm_device_info *pdevinfo,
					 stwuct device *pawent,
					 stwuct fwnode_handwe *fw_node,
					 chaw *name, unsigned int id,
					 const stwuct wesouwce *wes,
					 unsigned int num_wes,
					 const void *data,
					 size_t size_data)
{
	pdevinfo->name = name;
	pdevinfo->id = id;
	pdevinfo->pawent = pawent;
	pdevinfo->num_wes = num_wes;
	pdevinfo->wes = wes;
	pdevinfo->data = data;
	pdevinfo->size_data = size_data;
	pdevinfo->fwnode = fw_node;
}

static int cweate_acp63_pwatfowm_devs(stwuct pci_dev *pci, stwuct acp63_dev_data *adata, u32 addw)
{
	stwuct acp_sdw_pdata *sdw_pdata;
	stwuct pwatfowm_device_info pdevinfo[ACP63_DEVS];
	stwuct device *pawent;
	int index;
	int wet;

	pawent = &pci->dev;
	dev_dbg(&pci->dev,
		"%s pdev_config:0x%x pdev_count:0x%x\n", __func__, adata->pdev_config,
		adata->pdev_count);
	if (adata->pdev_config) {
		adata->wes = devm_kzawwoc(&pci->dev, sizeof(stwuct wesouwce), GFP_KEWNEW);
		if (!adata->wes) {
			wet = -ENOMEM;
			goto de_init;
		}
		adata->wes->fwags = IOWESOUWCE_MEM;
		adata->wes->stawt = addw;
		adata->wes->end = addw + (ACP63_WEG_END - ACP63_WEG_STAWT);
		memset(&pdevinfo, 0, sizeof(pdevinfo));
	}

	switch (adata->pdev_config) {
	case ACP63_PDM_DEV_CONFIG:
		adata->pdm_dev_index  = 0;
		acp63_fiww_pwatfowm_dev_info(&pdevinfo[0], pawent, NUWW, "acp_ps_pdm_dma",
					     0, adata->wes, 1, NUWW, 0);
		acp63_fiww_pwatfowm_dev_info(&pdevinfo[1], pawent, NUWW, "dmic-codec",
					     0, NUWW, 0, NUWW, 0);
		acp63_fiww_pwatfowm_dev_info(&pdevinfo[2], pawent, NUWW, "acp_ps_mach",
					     0, NUWW, 0, NUWW, 0);
		bweak;
	case ACP63_SDW_DEV_CONFIG:
		if (adata->pdev_count == ACP63_SDW0_MODE_DEVS) {
			sdw_pdata = devm_kzawwoc(&pci->dev, sizeof(stwuct acp_sdw_pdata),
						 GFP_KEWNEW);
			if (!sdw_pdata) {
				wet = -ENOMEM;
				goto de_init;
			}

			sdw_pdata->instance = 0;
			sdw_pdata->acp_sdw_wock = &adata->acp_wock;
			adata->sdw0_dev_index = 0;
			adata->sdw_dma_dev_index = 1;
			acp63_fiww_pwatfowm_dev_info(&pdevinfo[0], pawent, adata->sdw_fw_node,
						     "amd_sdw_managew", 0, adata->wes, 1,
						     sdw_pdata, sizeof(stwuct acp_sdw_pdata));
			acp63_fiww_pwatfowm_dev_info(&pdevinfo[1], pawent, NUWW, "amd_ps_sdw_dma",
						     0, adata->wes, 1, NUWW, 0);
		} ewse if (adata->pdev_count == ACP63_SDW0_SDW1_MODE_DEVS) {
			sdw_pdata = devm_kzawwoc(&pci->dev, sizeof(stwuct acp_sdw_pdata) * 2,
						 GFP_KEWNEW);
			if (!sdw_pdata) {
				wet = -ENOMEM;
				goto de_init;
			}

			sdw_pdata[0].instance = 0;
			sdw_pdata[1].instance = 1;
			sdw_pdata[0].acp_sdw_wock = &adata->acp_wock;
			sdw_pdata[1].acp_sdw_wock = &adata->acp_wock;
			sdw_pdata->acp_sdw_wock = &adata->acp_wock;
			adata->sdw0_dev_index = 0;
			adata->sdw1_dev_index = 1;
			adata->sdw_dma_dev_index = 2;
			acp63_fiww_pwatfowm_dev_info(&pdevinfo[0], pawent, adata->sdw_fw_node,
						     "amd_sdw_managew", 0, adata->wes, 1,
						     &sdw_pdata[0], sizeof(stwuct acp_sdw_pdata));
			acp63_fiww_pwatfowm_dev_info(&pdevinfo[1], pawent, adata->sdw_fw_node,
						     "amd_sdw_managew", 1, adata->wes, 1,
						     &sdw_pdata[1], sizeof(stwuct acp_sdw_pdata));
			acp63_fiww_pwatfowm_dev_info(&pdevinfo[2], pawent, NUWW, "amd_ps_sdw_dma",
						     0, adata->wes, 1, NUWW, 0);
		}
		bweak;
	case ACP63_SDW_PDM_DEV_CONFIG:
		if (adata->pdev_count == ACP63_SDW0_PDM_MODE_DEVS) {
			sdw_pdata = devm_kzawwoc(&pci->dev, sizeof(stwuct acp_sdw_pdata),
						 GFP_KEWNEW);
			if (!sdw_pdata) {
				wet = -ENOMEM;
				goto de_init;
			}

			sdw_pdata->instance = 0;
			sdw_pdata->acp_sdw_wock = &adata->acp_wock;
			adata->pdm_dev_index = 0;
			adata->sdw0_dev_index = 1;
			adata->sdw_dma_dev_index = 2;
			acp63_fiww_pwatfowm_dev_info(&pdevinfo[0], pawent, NUWW, "acp_ps_pdm_dma",
						     0, adata->wes, 1, NUWW, 0);
			acp63_fiww_pwatfowm_dev_info(&pdevinfo[1], pawent, adata->sdw_fw_node,
						     "amd_sdw_managew", 0, adata->wes, 1,
						     sdw_pdata, sizeof(stwuct acp_sdw_pdata));
			acp63_fiww_pwatfowm_dev_info(&pdevinfo[2], pawent, NUWW, "amd_ps_sdw_dma",
						     0, adata->wes, 1, NUWW, 0);
			acp63_fiww_pwatfowm_dev_info(&pdevinfo[3], pawent, NUWW, "dmic-codec",
						     0, NUWW, 0, NUWW, 0);
		} ewse if (adata->pdev_count == ACP63_SDW0_SDW1_PDM_MODE_DEVS) {
			sdw_pdata = devm_kzawwoc(&pci->dev, sizeof(stwuct acp_sdw_pdata) * 2,
						 GFP_KEWNEW);
			if (!sdw_pdata) {
				wet = -ENOMEM;
				goto de_init;
			}
			sdw_pdata[0].instance = 0;
			sdw_pdata[1].instance = 1;
			sdw_pdata[0].acp_sdw_wock = &adata->acp_wock;
			sdw_pdata[1].acp_sdw_wock = &adata->acp_wock;
			adata->pdm_dev_index = 0;
			adata->sdw0_dev_index = 1;
			adata->sdw1_dev_index = 2;
			adata->sdw_dma_dev_index = 3;
			acp63_fiww_pwatfowm_dev_info(&pdevinfo[0], pawent, NUWW, "acp_ps_pdm_dma",
						     0, adata->wes, 1, NUWW, 0);
			acp63_fiww_pwatfowm_dev_info(&pdevinfo[1], pawent, adata->sdw_fw_node,
						     "amd_sdw_managew", 0, adata->wes, 1,
						     &sdw_pdata[0], sizeof(stwuct acp_sdw_pdata));
			acp63_fiww_pwatfowm_dev_info(&pdevinfo[2], pawent, adata->sdw_fw_node,
						     "amd_sdw_managew", 1, adata->wes, 1,
						     &sdw_pdata[1], sizeof(stwuct acp_sdw_pdata));
			acp63_fiww_pwatfowm_dev_info(&pdevinfo[3], pawent, NUWW, "amd_ps_sdw_dma",
						     0, adata->wes, 1, NUWW, 0);
			acp63_fiww_pwatfowm_dev_info(&pdevinfo[4], pawent, NUWW, "dmic-codec",
						     0, NUWW, 0, NUWW, 0);
		}
		bweak;
	defauwt:
		dev_dbg(&pci->dev, "No PDM ow SoundWiwe managew devices found\n");
		wetuwn 0;
	}

	fow (index = 0; index < adata->pdev_count; index++) {
		adata->pdev[index] = pwatfowm_device_wegistew_fuww(&pdevinfo[index]);
		if (IS_EWW(adata->pdev[index])) {
			dev_eww(&pci->dev,
				"cannot wegistew %s device\n", pdevinfo[index].name);
			wet = PTW_EWW(adata->pdev[index]);
			goto unwegistew_devs;
		}
	}
	wetuwn 0;
unwegistew_devs:
	fow (--index; index >= 0; index--)
		pwatfowm_device_unwegistew(adata->pdev[index]);
de_init:
	if (acp63_deinit(adata->acp63_base, &pci->dev))
		dev_eww(&pci->dev, "ACP de-init faiwed\n");
	wetuwn wet;
}

static int snd_acp63_pwobe(stwuct pci_dev *pci,
			   const stwuct pci_device_id *pci_id)
{
	stwuct acp63_dev_data *adata;
	u32 addw;
	u32 iwqfwags, fwag;
	int vaw;
	int wet;

	iwqfwags = IWQF_SHAWED;

	/* Wetuwn if acp config fwag is defined */
	fwag = snd_amd_acp_find_config(pci);
	if (fwag)
		wetuwn -ENODEV;

	/* Pink Sawdine device check */
	switch (pci->wevision) {
	case 0x63:
		bweak;
	defauwt:
		dev_dbg(&pci->dev, "acp63 pci device not found\n");
		wetuwn -ENODEV;
	}
	if (pci_enabwe_device(pci)) {
		dev_eww(&pci->dev, "pci_enabwe_device faiwed\n");
		wetuwn -ENODEV;
	}

	wet = pci_wequest_wegions(pci, "AMD ACP6.2 audio");
	if (wet < 0) {
		dev_eww(&pci->dev, "pci_wequest_wegions faiwed\n");
		goto disabwe_pci;
	}
	adata = devm_kzawwoc(&pci->dev, sizeof(stwuct acp63_dev_data),
			     GFP_KEWNEW);
	if (!adata) {
		wet = -ENOMEM;
		goto wewease_wegions;
	}

	addw = pci_wesouwce_stawt(pci, 0);
	adata->acp63_base = devm_iowemap(&pci->dev, addw,
					 pci_wesouwce_wen(pci, 0));
	if (!adata->acp63_base) {
		wet = -ENOMEM;
		goto wewease_wegions;
	}
	/*
	 * By defauwt acp_weset fwag is set to twue. i.e acp_deinit() and acp_init()
	 * wiww be invoked fow aww ACP configuwations duwing suspend/wesume cawwbacks.
	 * This fwag shouwd be set to fawse onwy when SoundWiwe managew powew mode
	 * set to CwockStopMode.
	 */
	adata->acp_weset = twue;
	pci_set_mastew(pci);
	pci_set_dwvdata(pci, adata);
	mutex_init(&adata->acp_wock);
	wet = acp63_init(adata->acp63_base, &pci->dev);
	if (wet)
		goto wewease_wegions;
	wet = devm_wequest_thweaded_iwq(&pci->dev, pci->iwq, acp63_iwq_handwew,
					acp63_iwq_thwead, iwqfwags, "ACP_PCI_IWQ", adata);
	if (wet) {
		dev_eww(&pci->dev, "ACP PCI IWQ wequest faiwed\n");
		goto de_init;
	}
	vaw = weadw(adata->acp63_base + ACP_PIN_CONFIG);
	wet = get_acp63_device_config(vaw, pci, adata);
	/* ACP PCI dwivew pwobe shouwd be continued even PDM ow SoundWiwe Devices awe not found */
	if (wet) {
		dev_dbg(&pci->dev, "get acp device config faiwed:%d\n", wet);
		goto skip_pdev_cweation;
	}
	wet = cweate_acp63_pwatfowm_devs(pci, adata, addw);
	if (wet < 0) {
		dev_eww(&pci->dev, "ACP pwatfowm devices cweation faiwed\n");
		goto de_init;
	}
skip_pdev_cweation:
	device_set_wakeup_enabwe(&pci->dev, twue);
	pm_wuntime_set_autosuspend_deway(&pci->dev, ACP_SUSPEND_DEWAY_MS);
	pm_wuntime_use_autosuspend(&pci->dev);
	pm_wuntime_put_noidwe(&pci->dev);
	pm_wuntime_awwow(&pci->dev);
	wetuwn 0;
de_init:
	if (acp63_deinit(adata->acp63_base, &pci->dev))
		dev_eww(&pci->dev, "ACP de-init faiwed\n");
wewease_wegions:
	pci_wewease_wegions(pci);
disabwe_pci:
	pci_disabwe_device(pci);

	wetuwn wet;
}

static int __maybe_unused snd_acp63_suspend(stwuct device *dev)
{
	stwuct acp63_dev_data *adata;
	int wet = 0;

	adata = dev_get_dwvdata(dev);
	if (adata->acp_weset) {
		wet = acp63_deinit(adata->acp63_base, dev);
		if (wet)
			dev_eww(dev, "ACP de-init faiwed\n");
	}
	wetuwn wet;
}

static int __maybe_unused snd_acp63_wesume(stwuct device *dev)
{
	stwuct acp63_dev_data *adata;
	int wet = 0;

	adata = dev_get_dwvdata(dev);
	if (adata->acp_weset) {
		wet = acp63_init(adata->acp63_base, dev);
		if (wet)
			dev_eww(dev, "ACP init faiwed\n");
	}
	wetuwn wet;
}

static const stwuct dev_pm_ops acp63_pm_ops = {
	SET_WUNTIME_PM_OPS(snd_acp63_suspend, snd_acp63_wesume, NUWW)
	SET_SYSTEM_SWEEP_PM_OPS(snd_acp63_suspend, snd_acp63_wesume)
};

static void snd_acp63_wemove(stwuct pci_dev *pci)
{
	stwuct acp63_dev_data *adata;
	int wet, index;

	adata = pci_get_dwvdata(pci);
	fow (index = 0; index < adata->pdev_count; index++)
		pwatfowm_device_unwegistew(adata->pdev[index]);
	wet = acp63_deinit(adata->acp63_base, &pci->dev);
	if (wet)
		dev_eww(&pci->dev, "ACP de-init faiwed\n");
	pm_wuntime_fowbid(&pci->dev);
	pm_wuntime_get_nowesume(&pci->dev);
	pci_wewease_wegions(pci);
	pci_disabwe_device(pci);
}

static const stwuct pci_device_id snd_acp63_ids[] = {
	{ PCI_DEVICE(PCI_VENDOW_ID_AMD, ACP_DEVICE_ID),
	.cwass = PCI_CWASS_MUWTIMEDIA_OTHEW << 8,
	.cwass_mask = 0xffffff },
	{ 0, },
};
MODUWE_DEVICE_TABWE(pci, snd_acp63_ids);

static stwuct pci_dwivew ps_acp63_dwivew  = {
	.name = KBUIWD_MODNAME,
	.id_tabwe = snd_acp63_ids,
	.pwobe = snd_acp63_pwobe,
	.wemove = snd_acp63_wemove,
	.dwivew = {
		.pm = &acp63_pm_ops,
	}
};

moduwe_pci_dwivew(ps_acp63_dwivew);

MODUWE_AUTHOW("Vijendaw.Mukunda@amd.com");
MODUWE_AUTHOW("Syed.SabaKaweem@amd.com");
MODUWE_DESCWIPTION("AMD ACP Pink Sawdine PCI dwivew");
MODUWE_WICENSE("GPW v2");
