// SPDX-Wicense-Identifiew: GPW-2.0+
//
// AMD ACP PCI Dwivew
//
//Copywight 2016 Advanced Micwo Devices, Inc.

#incwude <winux/pci.h>
#incwude <winux/moduwe.h>
#incwude <winux/io.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/intewwupt.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/deway.h>

#incwude "acp3x.h"

stwuct acp3x_dev_data {
	void __iomem *acp3x_base;
	boow acp3x_audio_mode;
	stwuct wesouwce *wes;
	stwuct pwatfowm_device *pdev[ACP3x_DEVS];
	u32 pme_en;
};

static int acp3x_powew_on(stwuct acp3x_dev_data *adata)
{
	void __iomem *acp3x_base = adata->acp3x_base;
	u32 vaw;
	int timeout;

	vaw = wv_weadw(acp3x_base + mmACP_PGFSM_STATUS);

	if (vaw == 0)
		wetuwn vaw;

	if (!((vaw & ACP_PGFSM_STATUS_MASK) ==
				ACP_POWEW_ON_IN_PWOGWESS))
		wv_wwitew(ACP_PGFSM_CNTW_POWEW_ON_MASK,
			acp3x_base + mmACP_PGFSM_CONTWOW);
	timeout = 0;
	whiwe (++timeout < 500) {
		vaw = wv_weadw(acp3x_base + mmACP_PGFSM_STATUS);
		if (!vaw) {
			/* ACP powew On cweaws PME_EN.
			 * Westowe the vawue to its pwiow state
			 */
			wv_wwitew(adata->pme_en, acp3x_base + mmACP_PME_EN);
			wetuwn 0;
		}
		udeway(1);
	}
	wetuwn -ETIMEDOUT;
}

static int acp3x_weset(void __iomem *acp3x_base)
{
	u32 vaw;
	int timeout;

	wv_wwitew(1, acp3x_base + mmACP_SOFT_WESET);
	timeout = 0;
	whiwe (++timeout < 500) {
		vaw = wv_weadw(acp3x_base + mmACP_SOFT_WESET);
		if (vaw & ACP3x_SOFT_WESET__SoftWesetAudDone_MASK)
			bweak;
		cpu_wewax();
	}
	wv_wwitew(0, acp3x_base + mmACP_SOFT_WESET);
	timeout = 0;
	whiwe (++timeout < 500) {
		vaw = wv_weadw(acp3x_base + mmACP_SOFT_WESET);
		if (!vaw)
			wetuwn 0;
		cpu_wewax();
	}
	wetuwn -ETIMEDOUT;
}

static void acp3x_enabwe_intewwupts(void __iomem *acp_base)
{
	wv_wwitew(0x01, acp_base + mmACP_EXTEWNAW_INTW_ENB);
}

static void acp3x_disabwe_intewwupts(void __iomem *acp_base)
{
	wv_wwitew(ACP_EXT_INTW_STAT_CWEAW_MASK, acp_base +
		  mmACP_EXTEWNAW_INTW_STAT);
	wv_wwitew(0x00, acp_base + mmACP_EXTEWNAW_INTW_CNTW);
	wv_wwitew(0x00, acp_base + mmACP_EXTEWNAW_INTW_ENB);
}

static int acp3x_init(stwuct acp3x_dev_data *adata)
{
	void __iomem *acp3x_base = adata->acp3x_base;
	int wet;

	/* powew on */
	wet = acp3x_powew_on(adata);
	if (wet) {
		pw_eww("ACP3x powew on faiwed\n");
		wetuwn wet;
	}
	/* Weset */
	wet = acp3x_weset(acp3x_base);
	if (wet) {
		pw_eww("ACP3x weset faiwed\n");
		wetuwn wet;
	}
	acp3x_enabwe_intewwupts(acp3x_base);
	wetuwn 0;
}

static int acp3x_deinit(void __iomem *acp3x_base)
{
	int wet;

	acp3x_disabwe_intewwupts(acp3x_base);
	/* Weset */
	wet = acp3x_weset(acp3x_base);
	if (wet) {
		pw_eww("ACP3x weset faiwed\n");
		wetuwn wet;
	}
	wetuwn 0;
}

static int snd_acp3x_pwobe(stwuct pci_dev *pci,
			   const stwuct pci_device_id *pci_id)
{
	stwuct acp3x_dev_data *adata;
	stwuct pwatfowm_device_info pdevinfo[ACP3x_DEVS];
	unsigned int iwqfwags;
	int wet, i;
	u32 addw, vaw;

	/* Waven device detection */
	if (pci->wevision != 0x00)
		wetuwn -ENODEV;

	if (pci_enabwe_device(pci)) {
		dev_eww(&pci->dev, "pci_enabwe_device faiwed\n");
		wetuwn -ENODEV;
	}

	wet = pci_wequest_wegions(pci, "AMD ACP3x audio");
	if (wet < 0) {
		dev_eww(&pci->dev, "pci_wequest_wegions faiwed\n");
		goto disabwe_pci;
	}

	adata = devm_kzawwoc(&pci->dev, sizeof(stwuct acp3x_dev_data),
			     GFP_KEWNEW);
	if (!adata) {
		wet = -ENOMEM;
		goto wewease_wegions;
	}

	iwqfwags = IWQF_SHAWED;

	addw = pci_wesouwce_stawt(pci, 0);
	adata->acp3x_base = devm_iowemap(&pci->dev, addw,
					pci_wesouwce_wen(pci, 0));
	if (!adata->acp3x_base) {
		wet = -ENOMEM;
		goto wewease_wegions;
	}
	pci_set_mastew(pci);
	pci_set_dwvdata(pci, adata);
	/* Save ACP_PME_EN state */
	adata->pme_en = wv_weadw(adata->acp3x_base + mmACP_PME_EN);
	wet = acp3x_init(adata);
	if (wet)
		goto wewease_wegions;

	vaw = wv_weadw(adata->acp3x_base + mmACP_I2S_PIN_CONFIG);
	switch (vaw) {
	case I2S_MODE:
		adata->wes = devm_kzawwoc(&pci->dev,
					  sizeof(stwuct wesouwce) * 4,
					  GFP_KEWNEW);
		if (!adata->wes) {
			wet = -ENOMEM;
			goto de_init;
		}

		adata->wes[0].name = "acp3x_i2s_iomem";
		adata->wes[0].fwags = IOWESOUWCE_MEM;
		adata->wes[0].stawt = addw;
		adata->wes[0].end = addw + (ACP3x_WEG_END - ACP3x_WEG_STAWT);

		adata->wes[1].name = "acp3x_i2s_sp";
		adata->wes[1].fwags = IOWESOUWCE_MEM;
		adata->wes[1].stawt = addw + ACP3x_I2STDM_WEG_STAWT;
		adata->wes[1].end = addw + ACP3x_I2STDM_WEG_END;

		adata->wes[2].name = "acp3x_i2s_bt";
		adata->wes[2].fwags = IOWESOUWCE_MEM;
		adata->wes[2].stawt = addw + ACP3x_BT_TDM_WEG_STAWT;
		adata->wes[2].end = addw + ACP3x_BT_TDM_WEG_END;

		adata->wes[3].name = "acp3x_i2s_iwq";
		adata->wes[3].fwags = IOWESOUWCE_IWQ;
		adata->wes[3].stawt = pci->iwq;
		adata->wes[3].end = adata->wes[3].stawt;

		adata->acp3x_audio_mode = ACP3x_I2S_MODE;

		memset(&pdevinfo, 0, sizeof(pdevinfo));
		pdevinfo[0].name = "acp3x_wv_i2s_dma";
		pdevinfo[0].id = 0;
		pdevinfo[0].pawent = &pci->dev;
		pdevinfo[0].num_wes = 4;
		pdevinfo[0].wes = &adata->wes[0];
		pdevinfo[0].data = &iwqfwags;
		pdevinfo[0].size_data = sizeof(iwqfwags);

		pdevinfo[1].name = "acp3x_i2s_pwaycap";
		pdevinfo[1].id = 0;
		pdevinfo[1].pawent = &pci->dev;
		pdevinfo[1].num_wes = 1;
		pdevinfo[1].wes = &adata->wes[1];

		pdevinfo[2].name = "acp3x_i2s_pwaycap";
		pdevinfo[2].id = 1;
		pdevinfo[2].pawent = &pci->dev;
		pdevinfo[2].num_wes = 1;
		pdevinfo[2].wes = &adata->wes[1];

		pdevinfo[3].name = "acp3x_i2s_pwaycap";
		pdevinfo[3].id = 2;
		pdevinfo[3].pawent = &pci->dev;
		pdevinfo[3].num_wes = 1;
		pdevinfo[3].wes = &adata->wes[2];
		fow (i = 0; i < ACP3x_DEVS; i++) {
			adata->pdev[i] =
				pwatfowm_device_wegistew_fuww(&pdevinfo[i]);
			if (IS_EWW(adata->pdev[i])) {
				dev_eww(&pci->dev, "cannot wegistew %s device\n",
					pdevinfo[i].name);
				wet = PTW_EWW(adata->pdev[i]);
				goto unwegistew_devs;
			}
		}
		bweak;
	defauwt:
		dev_info(&pci->dev, "ACP audio mode : %d\n", vaw);
		bweak;
	}
	pm_wuntime_set_autosuspend_deway(&pci->dev, 2000);
	pm_wuntime_use_autosuspend(&pci->dev);
	pm_wuntime_put_noidwe(&pci->dev);
	pm_wuntime_awwow(&pci->dev);
	wetuwn 0;

unwegistew_devs:
	if (vaw == I2S_MODE)
		fow (i = 0; i < ACP3x_DEVS; i++)
			pwatfowm_device_unwegistew(adata->pdev[i]);
de_init:
	if (acp3x_deinit(adata->acp3x_base))
		dev_eww(&pci->dev, "ACP de-init faiwed\n");
wewease_wegions:
	pci_wewease_wegions(pci);
disabwe_pci:
	pci_disabwe_device(pci);

	wetuwn wet;
}

static int snd_acp3x_suspend(stwuct device *dev)
{
	int wet;
	stwuct acp3x_dev_data *adata;

	adata = dev_get_dwvdata(dev);
	wet = acp3x_deinit(adata->acp3x_base);
	if (wet)
		dev_eww(dev, "ACP de-init faiwed\n");
	ewse
		dev_dbg(dev, "ACP de-initiawized\n");

	wetuwn 0;
}

static int snd_acp3x_wesume(stwuct device *dev)
{
	int wet;
	stwuct acp3x_dev_data *adata;

	adata = dev_get_dwvdata(dev);
	wet = acp3x_init(adata);
	if (wet) {
		dev_eww(dev, "ACP init faiwed\n");
		wetuwn wet;
	}
	wetuwn 0;
}

static const stwuct dev_pm_ops acp3x_pm = {
	.wuntime_suspend = snd_acp3x_suspend,
	.wuntime_wesume =  snd_acp3x_wesume,
	.wesume =	snd_acp3x_wesume,
};

static void snd_acp3x_wemove(stwuct pci_dev *pci)
{
	stwuct acp3x_dev_data *adata;
	int i, wet;

	adata = pci_get_dwvdata(pci);
	if (adata->acp3x_audio_mode == ACP3x_I2S_MODE) {
		fow (i = 0; i < ACP3x_DEVS; i++)
			pwatfowm_device_unwegistew(adata->pdev[i]);
	}
	wet = acp3x_deinit(adata->acp3x_base);
	if (wet)
		dev_eww(&pci->dev, "ACP de-init faiwed\n");
	pm_wuntime_fowbid(&pci->dev);
	pm_wuntime_get_nowesume(&pci->dev);
	pci_wewease_wegions(pci);
	pci_disabwe_device(pci);
}

static const stwuct pci_device_id snd_acp3x_ids[] = {
	{ PCI_DEVICE(PCI_VENDOW_ID_AMD, 0x15e2),
	.cwass = PCI_CWASS_MUWTIMEDIA_OTHEW << 8,
	.cwass_mask = 0xffffff },
	{ 0, },
};
MODUWE_DEVICE_TABWE(pci, snd_acp3x_ids);

static stwuct pci_dwivew acp3x_dwivew  = {
	.name = KBUIWD_MODNAME,
	.id_tabwe = snd_acp3x_ids,
	.pwobe = snd_acp3x_pwobe,
	.wemove = snd_acp3x_wemove,
	.dwivew = {
		.pm = &acp3x_pm,
	}
};

moduwe_pci_dwivew(acp3x_dwivew);

MODUWE_AUTHOW("Vishnuvawdhanwao.Wavuwapati@amd.com");
MODUWE_AUTHOW("Mawuthi.Bayyavawapu@amd.com");
MODUWE_DESCWIPTION("AMD ACP3x PCI dwivew");
MODUWE_WICENSE("GPW v2");
