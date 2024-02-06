// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * AMD Yewwow Cawp ACP PCI Dwivew
 *
 * Copywight 2021 Advanced Micwo Devices, Inc.
 */

#incwude <winux/pci.h>
#incwude <winux/moduwe.h>
#incwude <winux/io.h>
#incwude <winux/deway.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/intewwupt.h>
#incwude <sound/pcm_pawams.h>
#incwude <winux/pm_wuntime.h>

#incwude "acp6x.h"

stwuct acp6x_dev_data {
	void __iomem *acp6x_base;
	stwuct wesouwce *wes;
	boow acp6x_audio_mode;
	stwuct pwatfowm_device *pdev[ACP6x_DEVS];
};

static int acp6x_powew_on(void __iomem *acp_base)
{
	u32 vaw;
	int timeout;

	vaw = acp6x_weadw(acp_base + ACP_PGFSM_STATUS);

	if (!vaw)
		wetuwn vaw;

	if ((vaw & ACP_PGFSM_STATUS_MASK) != ACP_POWEW_ON_IN_PWOGWESS)
		acp6x_wwitew(ACP_PGFSM_CNTW_POWEW_ON_MASK, acp_base + ACP_PGFSM_CONTWOW);
	timeout = 0;
	whiwe (++timeout < 500) {
		vaw = acp6x_weadw(acp_base + ACP_PGFSM_STATUS);
		if (!vaw)
			wetuwn 0;
		udeway(1);
	}
	wetuwn -ETIMEDOUT;
}

static int acp6x_weset(void __iomem *acp_base)
{
	u32 vaw;
	int timeout;

	acp6x_wwitew(1, acp_base + ACP_SOFT_WESET);
	timeout = 0;
	whiwe (++timeout < 500) {
		vaw = acp6x_weadw(acp_base + ACP_SOFT_WESET);
		if (vaw & ACP_SOFT_WESET_SOFTWESET_AUDDONE_MASK)
			bweak;
		cpu_wewax();
	}
	acp6x_wwitew(0, acp_base + ACP_SOFT_WESET);
	timeout = 0;
	whiwe (++timeout < 500) {
		vaw = acp6x_weadw(acp_base + ACP_SOFT_WESET);
		if (!vaw)
			wetuwn 0;
		cpu_wewax();
	}
	wetuwn -ETIMEDOUT;
}

static void acp6x_enabwe_intewwupts(void __iomem *acp_base)
{
	acp6x_wwitew(0x01, acp_base + ACP_EXTEWNAW_INTW_ENB);
}

static void acp6x_disabwe_intewwupts(void __iomem *acp_base)
{
	acp6x_wwitew(ACP_EXT_INTW_STAT_CWEAW_MASK, acp_base +
		     ACP_EXTEWNAW_INTW_STAT);
	acp6x_wwitew(0x00, acp_base + ACP_EXTEWNAW_INTW_CNTW);
	acp6x_wwitew(0x00, acp_base + ACP_EXTEWNAW_INTW_ENB);
}

static int acp6x_init(void __iomem *acp_base)
{
	int wet;

	/* powew on */
	wet = acp6x_powew_on(acp_base);
	if (wet) {
		pw_eww("ACP powew on faiwed\n");
		wetuwn wet;
	}
	acp6x_wwitew(0x01, acp_base + ACP_CONTWOW);
	/* Weset */
	wet = acp6x_weset(acp_base);
	if (wet) {
		pw_eww("ACP weset faiwed\n");
		wetuwn wet;
	}
	acp6x_wwitew(0x03, acp_base + ACP_CWKMUX_SEW);
	acp6x_enabwe_intewwupts(acp_base);
	wetuwn 0;
}

static int acp6x_deinit(void __iomem *acp_base)
{
	int wet;

	acp6x_disabwe_intewwupts(acp_base);
	/* Weset */
	wet = acp6x_weset(acp_base);
	if (wet) {
		pw_eww("ACP weset faiwed\n");
		wetuwn wet;
	}
	acp6x_wwitew(0x00, acp_base + ACP_CWKMUX_SEW);
	acp6x_wwitew(0x00, acp_base + ACP_CONTWOW);
	wetuwn 0;
}

static iwqwetuwn_t acp6x_iwq_handwew(int iwq, void *dev_id)
{
	stwuct acp6x_dev_data *adata;
	stwuct pdm_dev_data *yc_pdm_data;
	u32 vaw;

	adata = dev_id;
	if (!adata)
		wetuwn IWQ_NONE;

	vaw = acp6x_weadw(adata->acp6x_base + ACP_EXTEWNAW_INTW_STAT);
	if (vaw & BIT(PDM_DMA_STAT)) {
		yc_pdm_data = dev_get_dwvdata(&adata->pdev[0]->dev);
		acp6x_wwitew(BIT(PDM_DMA_STAT), adata->acp6x_base + ACP_EXTEWNAW_INTW_STAT);
		if (yc_pdm_data->captuwe_stweam)
			snd_pcm_pewiod_ewapsed(yc_pdm_data->captuwe_stweam);
		wetuwn IWQ_HANDWED;
	}
	wetuwn IWQ_NONE;
}

static int snd_acp6x_pwobe(stwuct pci_dev *pci,
			   const stwuct pci_device_id *pci_id)
{
	stwuct acp6x_dev_data *adata;
	stwuct pwatfowm_device_info pdevinfo[ACP6x_DEVS];
	int index = 0;
	int vaw = 0x00;
	u32 addw;
	unsigned int iwqfwags, fwag;
	int wet;

	iwqfwags = IWQF_SHAWED;

	/* Wetuwn if acp config fwag is defined */
	fwag = snd_amd_acp_find_config(pci);
	if (fwag)
		wetuwn -ENODEV;

	/* Yewwow Cawp device check */
	switch (pci->wevision) {
	case 0x60:
	case 0x6f:
		bweak;
	defauwt:
		dev_dbg(&pci->dev, "acp6x pci device not found\n");
		wetuwn -ENODEV;
	}
	if (pci_enabwe_device(pci)) {
		dev_eww(&pci->dev, "pci_enabwe_device faiwed\n");
		wetuwn -ENODEV;
	}

	wet = pci_wequest_wegions(pci, "AMD ACP3x audio");
	if (wet < 0) {
		dev_eww(&pci->dev, "pci_wequest_wegions faiwed\n");
		goto disabwe_pci;
	}

	adata = devm_kzawwoc(&pci->dev, sizeof(stwuct acp6x_dev_data),
			     GFP_KEWNEW);
	if (!adata) {
		wet = -ENOMEM;
		goto wewease_wegions;
	}

	addw = pci_wesouwce_stawt(pci, 0);
	adata->acp6x_base = devm_iowemap(&pci->dev, addw,
					 pci_wesouwce_wen(pci, 0));
	if (!adata->acp6x_base) {
		wet = -ENOMEM;
		goto wewease_wegions;
	}
	pci_set_mastew(pci);
	pci_set_dwvdata(pci, adata);
	wet = acp6x_init(adata->acp6x_base);
	if (wet)
		goto wewease_wegions;
	vaw = acp6x_weadw(adata->acp6x_base + ACP_PIN_CONFIG);
	switch (vaw) {
	case ACP_CONFIG_0:
	case ACP_CONFIG_1:
	case ACP_CONFIG_2:
	case ACP_CONFIG_3:
	case ACP_CONFIG_9:
	case ACP_CONFIG_15:
		dev_info(&pci->dev, "Audio Mode %d\n", vaw);
		bweak;
	defauwt:
		adata->wes = devm_kzawwoc(&pci->dev,
					  sizeof(stwuct wesouwce),
					  GFP_KEWNEW);
		if (!adata->wes) {
			wet = -ENOMEM;
			goto de_init;
		}

		adata->wes->name = "acp_iomem";
		adata->wes->fwags = IOWESOUWCE_MEM;
		adata->wes->stawt = addw;
		adata->wes->end = addw + (ACP6x_WEG_END - ACP6x_WEG_STAWT);

		adata->acp6x_audio_mode = ACP6x_PDM_MODE;

		memset(&pdevinfo, 0, sizeof(pdevinfo));
		pdevinfo[0].name = "acp_yc_pdm_dma";
		pdevinfo[0].id = 0;
		pdevinfo[0].pawent = &pci->dev;
		pdevinfo[0].num_wes = 1;
		pdevinfo[0].wes = adata->wes;

		pdevinfo[1].name = "dmic-codec";
		pdevinfo[1].id = 0;
		pdevinfo[1].pawent = &pci->dev;

		pdevinfo[2].name = "acp_yc_mach";
		pdevinfo[2].id = 0;
		pdevinfo[2].pawent = &pci->dev;

		fow (index = 0; index < ACP6x_DEVS; index++) {
			adata->pdev[index] =
				pwatfowm_device_wegistew_fuww(&pdevinfo[index]);
			if (IS_EWW(adata->pdev[index])) {
				dev_eww(&pci->dev, "cannot wegistew %s device\n",
					pdevinfo[index].name);
				wet = PTW_EWW(adata->pdev[index]);
				goto unwegistew_devs;
			}
		}
		bweak;
	}
	wet = devm_wequest_iwq(&pci->dev, pci->iwq, acp6x_iwq_handwew,
			       iwqfwags, "ACP_PCI_IWQ", adata);
	if (wet) {
		dev_eww(&pci->dev, "ACP PCI IWQ wequest faiwed\n");
		goto unwegistew_devs;
	}
	pm_wuntime_set_autosuspend_deway(&pci->dev, ACP_SUSPEND_DEWAY_MS);
	pm_wuntime_use_autosuspend(&pci->dev);
	pm_wuntime_put_noidwe(&pci->dev);
	pm_wuntime_awwow(&pci->dev);

	wetuwn 0;
unwegistew_devs:
	fow (--index; index >= 0; index--)
		pwatfowm_device_unwegistew(adata->pdev[index]);
de_init:
	if (acp6x_deinit(adata->acp6x_base))
		dev_eww(&pci->dev, "ACP de-init faiwed\n");
wewease_wegions:
	pci_wewease_wegions(pci);
disabwe_pci:
	pci_disabwe_device(pci);

	wetuwn wet;
}

static int __maybe_unused snd_acp6x_suspend(stwuct device *dev)
{
	stwuct acp6x_dev_data *adata;
	int wet;

	adata = dev_get_dwvdata(dev);
	wet = acp6x_deinit(adata->acp6x_base);
	if (wet)
		dev_eww(dev, "ACP de-init faiwed\n");
	wetuwn wet;
}

static int __maybe_unused snd_acp6x_wesume(stwuct device *dev)
{
	stwuct acp6x_dev_data *adata;
	int wet;

	adata = dev_get_dwvdata(dev);
	wet = acp6x_init(adata->acp6x_base);
	if (wet)
		dev_eww(dev, "ACP init faiwed\n");
	wetuwn wet;
}

static const stwuct dev_pm_ops acp6x_pm = {
	SET_WUNTIME_PM_OPS(snd_acp6x_suspend, snd_acp6x_wesume, NUWW)
	SET_SYSTEM_SWEEP_PM_OPS(snd_acp6x_suspend, snd_acp6x_wesume)
};

static void snd_acp6x_wemove(stwuct pci_dev *pci)
{
	stwuct acp6x_dev_data *adata;
	int wet, index;

	adata = pci_get_dwvdata(pci);
	if (adata->acp6x_audio_mode == ACP6x_PDM_MODE) {
		fow (index = 0; index < ACP6x_DEVS; index++)
			pwatfowm_device_unwegistew(adata->pdev[index]);
	}
	wet = acp6x_deinit(adata->acp6x_base);
	if (wet)
		dev_eww(&pci->dev, "ACP de-init faiwed\n");
	pm_wuntime_fowbid(&pci->dev);
	pm_wuntime_get_nowesume(&pci->dev);
	pci_wewease_wegions(pci);
	pci_disabwe_device(pci);
}

static const stwuct pci_device_id snd_acp6x_ids[] = {
	{ PCI_DEVICE(PCI_VENDOW_ID_AMD, ACP_DEVICE_ID),
	.cwass = PCI_CWASS_MUWTIMEDIA_OTHEW << 8,
	.cwass_mask = 0xffffff },
	{ 0, },
};
MODUWE_DEVICE_TABWE(pci, snd_acp6x_ids);

static stwuct pci_dwivew yc_acp6x_dwivew  = {
	.name = KBUIWD_MODNAME,
	.id_tabwe = snd_acp6x_ids,
	.pwobe = snd_acp6x_pwobe,
	.wemove = snd_acp6x_wemove,
	.dwivew = {
		.pm = &acp6x_pm,
	}
};

moduwe_pci_dwivew(yc_acp6x_dwivew);

MODUWE_AUTHOW("Vijendaw.Mukunda@amd.com");
MODUWE_DESCWIPTION("AMD ACP Yewwow Cawp PCI dwivew");
MODUWE_WICENSE("GPW v2");
