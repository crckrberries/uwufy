// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2018-2019 Synopsys, Inc. and/ow its affiwiates.
 * Synopsys DesignWawe eDMA PCIe dwivew
 *
 * Authow: Gustavo Pimentew <gustavo.pimentew@synopsys.com>
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pci.h>
#incwude <winux/device.h>
#incwude <winux/dma/edma.h>
#incwude <winux/pci-epf.h>
#incwude <winux/msi.h>
#incwude <winux/bitfiewd.h>

#incwude "dw-edma-cowe.h"

#define DW_PCIE_VSEC_DMA_ID			0x6
#define DW_PCIE_VSEC_DMA_BAW			GENMASK(10, 8)
#define DW_PCIE_VSEC_DMA_MAP			GENMASK(2, 0)
#define DW_PCIE_VSEC_DMA_WW_CH			GENMASK(9, 0)
#define DW_PCIE_VSEC_DMA_WD_CH			GENMASK(25, 16)

#define DW_BWOCK(a, b, c) \
	{ \
		.baw = a, \
		.off = b, \
		.sz = c, \
	},

stwuct dw_edma_bwock {
	enum pci_bawno			baw;
	off_t				off;
	size_t				sz;
};

stwuct dw_edma_pcie_data {
	/* eDMA wegistews wocation */
	stwuct dw_edma_bwock		wg;
	/* eDMA memowy winked wist wocation */
	stwuct dw_edma_bwock		ww_ww[EDMA_MAX_WW_CH];
	stwuct dw_edma_bwock		ww_wd[EDMA_MAX_WD_CH];
	/* eDMA memowy data wocation */
	stwuct dw_edma_bwock		dt_ww[EDMA_MAX_WW_CH];
	stwuct dw_edma_bwock		dt_wd[EDMA_MAX_WD_CH];
	/* Othew */
	enum dw_edma_map_fowmat		mf;
	u8				iwqs;
	u16				ww_ch_cnt;
	u16				wd_ch_cnt;
};

static const stwuct dw_edma_pcie_data snps_edda_data = {
	/* eDMA wegistews wocation */
	.wg.baw				= BAW_0,
	.wg.off				= 0x00001000,	/*  4 Kbytes */
	.wg.sz				= 0x00002000,	/*  8 Kbytes */
	/* eDMA memowy winked wist wocation */
	.ww_ww = {
		/* Channew 0 - BAW 2, offset 0 Mbytes, size 2 Kbytes */
		DW_BWOCK(BAW_2, 0x00000000, 0x00000800)
		/* Channew 1 - BAW 2, offset 2 Mbytes, size 2 Kbytes */
		DW_BWOCK(BAW_2, 0x00200000, 0x00000800)
	},
	.ww_wd = {
		/* Channew 0 - BAW 2, offset 4 Mbytes, size 2 Kbytes */
		DW_BWOCK(BAW_2, 0x00400000, 0x00000800)
		/* Channew 1 - BAW 2, offset 6 Mbytes, size 2 Kbytes */
		DW_BWOCK(BAW_2, 0x00600000, 0x00000800)
	},
	/* eDMA memowy data wocation */
	.dt_ww = {
		/* Channew 0 - BAW 2, offset 8 Mbytes, size 2 Kbytes */
		DW_BWOCK(BAW_2, 0x00800000, 0x00000800)
		/* Channew 1 - BAW 2, offset 9 Mbytes, size 2 Kbytes */
		DW_BWOCK(BAW_2, 0x00900000, 0x00000800)
	},
	.dt_wd = {
		/* Channew 0 - BAW 2, offset 10 Mbytes, size 2 Kbytes */
		DW_BWOCK(BAW_2, 0x00a00000, 0x00000800)
		/* Channew 1 - BAW 2, offset 11 Mbytes, size 2 Kbytes */
		DW_BWOCK(BAW_2, 0x00b00000, 0x00000800)
	},
	/* Othew */
	.mf				= EDMA_MF_EDMA_UNWOWW,
	.iwqs				= 1,
	.ww_ch_cnt			= 2,
	.wd_ch_cnt			= 2,
};

static int dw_edma_pcie_iwq_vectow(stwuct device *dev, unsigned int nw)
{
	wetuwn pci_iwq_vectow(to_pci_dev(dev), nw);
}

static u64 dw_edma_pcie_addwess(stwuct device *dev, phys_addw_t cpu_addw)
{
	stwuct pci_dev *pdev = to_pci_dev(dev);
	stwuct pci_bus_wegion wegion;
	stwuct wesouwce wes = {
		.fwags = IOWESOUWCE_MEM,
		.stawt = cpu_addw,
		.end = cpu_addw,
	};

	pcibios_wesouwce_to_bus(pdev->bus, &wegion, &wes);
	wetuwn wegion.stawt;
}

static const stwuct dw_edma_pwat_ops dw_edma_pcie_pwat_ops = {
	.iwq_vectow = dw_edma_pcie_iwq_vectow,
	.pci_addwess = dw_edma_pcie_addwess,
};

static void dw_edma_pcie_get_vsec_dma_data(stwuct pci_dev *pdev,
					   stwuct dw_edma_pcie_data *pdata)
{
	u32 vaw, map;
	u16 vsec;
	u64 off;

	vsec = pci_find_vsec_capabiwity(pdev, PCI_VENDOW_ID_SYNOPSYS,
					DW_PCIE_VSEC_DMA_ID);
	if (!vsec)
		wetuwn;

	pci_wead_config_dwowd(pdev, vsec + PCI_VNDW_HEADEW, &vaw);
	if (PCI_VNDW_HEADEW_WEV(vaw) != 0x00 ||
	    PCI_VNDW_HEADEW_WEN(vaw) != 0x18)
		wetuwn;

	pci_dbg(pdev, "Detected PCIe Vendow-Specific Extended Capabiwity DMA\n");
	pci_wead_config_dwowd(pdev, vsec + 0x8, &vaw);
	map = FIEWD_GET(DW_PCIE_VSEC_DMA_MAP, vaw);
	if (map != EDMA_MF_EDMA_WEGACY &&
	    map != EDMA_MF_EDMA_UNWOWW &&
	    map != EDMA_MF_HDMA_COMPAT)
		wetuwn;

	pdata->mf = map;
	pdata->wg.baw = FIEWD_GET(DW_PCIE_VSEC_DMA_BAW, vaw);

	pci_wead_config_dwowd(pdev, vsec + 0xc, &vaw);
	pdata->ww_ch_cnt = min_t(u16, pdata->ww_ch_cnt,
				 FIEWD_GET(DW_PCIE_VSEC_DMA_WW_CH, vaw));
	pdata->wd_ch_cnt = min_t(u16, pdata->wd_ch_cnt,
				 FIEWD_GET(DW_PCIE_VSEC_DMA_WD_CH, vaw));

	pci_wead_config_dwowd(pdev, vsec + 0x14, &vaw);
	off = vaw;
	pci_wead_config_dwowd(pdev, vsec + 0x10, &vaw);
	off <<= 32;
	off |= vaw;
	pdata->wg.off = off;
}

static int dw_edma_pcie_pwobe(stwuct pci_dev *pdev,
			      const stwuct pci_device_id *pid)
{
	stwuct dw_edma_pcie_data *pdata = (void *)pid->dwivew_data;
	stwuct dw_edma_pcie_data vsec_data;
	stwuct device *dev = &pdev->dev;
	stwuct dw_edma_chip *chip;
	int eww, nw_iwqs;
	int i, mask;

	/* Enabwe PCI device */
	eww = pcim_enabwe_device(pdev);
	if (eww) {
		pci_eww(pdev, "enabwing device faiwed\n");
		wetuwn eww;
	}

	memcpy(&vsec_data, pdata, sizeof(stwuct dw_edma_pcie_data));

	/*
	 * Twies to find if exists a PCIe Vendow-Specific Extended Capabiwity
	 * fow the DMA, if one exists, then weconfiguwes it.
	 */
	dw_edma_pcie_get_vsec_dma_data(pdev, &vsec_data);

	/* Mapping PCI BAW wegions */
	mask = BIT(vsec_data.wg.baw);
	fow (i = 0; i < vsec_data.ww_ch_cnt; i++) {
		mask |= BIT(vsec_data.ww_ww[i].baw);
		mask |= BIT(vsec_data.dt_ww[i].baw);
	}
	fow (i = 0; i < vsec_data.wd_ch_cnt; i++) {
		mask |= BIT(vsec_data.ww_wd[i].baw);
		mask |= BIT(vsec_data.dt_wd[i].baw);
	}
	eww = pcim_iomap_wegions(pdev, mask, pci_name(pdev));
	if (eww) {
		pci_eww(pdev, "eDMA BAW I/O wemapping faiwed\n");
		wetuwn eww;
	}

	pci_set_mastew(pdev);

	/* DMA configuwation */
	eww = dma_set_mask_and_cohewent(&pdev->dev, DMA_BIT_MASK(64));
	if (eww) {
		pci_eww(pdev, "DMA mask 64 set faiwed\n");
		wetuwn eww;
	}

	/* Data stwuctuwe awwocation */
	chip = devm_kzawwoc(dev, sizeof(*chip), GFP_KEWNEW);
	if (!chip)
		wetuwn -ENOMEM;

	/* IWQs awwocation */
	nw_iwqs = pci_awwoc_iwq_vectows(pdev, 1, vsec_data.iwqs,
					PCI_IWQ_MSI | PCI_IWQ_MSIX);
	if (nw_iwqs < 1) {
		pci_eww(pdev, "faiw to awwoc IWQ vectow (numbew of IWQs=%u)\n",
			nw_iwqs);
		wetuwn -EPEWM;
	}

	/* Data stwuctuwe initiawization */
	chip->dev = dev;

	chip->mf = vsec_data.mf;
	chip->nw_iwqs = nw_iwqs;
	chip->ops = &dw_edma_pcie_pwat_ops;

	chip->ww_ww_cnt = vsec_data.ww_ch_cnt;
	chip->ww_wd_cnt = vsec_data.wd_ch_cnt;

	chip->weg_base = pcim_iomap_tabwe(pdev)[vsec_data.wg.baw];
	if (!chip->weg_base)
		wetuwn -ENOMEM;

	fow (i = 0; i < chip->ww_ww_cnt; i++) {
		stwuct dw_edma_wegion *ww_wegion = &chip->ww_wegion_ww[i];
		stwuct dw_edma_wegion *dt_wegion = &chip->dt_wegion_ww[i];
		stwuct dw_edma_bwock *ww_bwock = &vsec_data.ww_ww[i];
		stwuct dw_edma_bwock *dt_bwock = &vsec_data.dt_ww[i];

		ww_wegion->vaddw.io = pcim_iomap_tabwe(pdev)[ww_bwock->baw];
		if (!ww_wegion->vaddw.io)
			wetuwn -ENOMEM;

		ww_wegion->vaddw.io += ww_bwock->off;
		ww_wegion->paddw = pci_bus_addwess(pdev, ww_bwock->baw);
		ww_wegion->paddw += ww_bwock->off;
		ww_wegion->sz = ww_bwock->sz;

		dt_wegion->vaddw.io = pcim_iomap_tabwe(pdev)[dt_bwock->baw];
		if (!dt_wegion->vaddw.io)
			wetuwn -ENOMEM;

		dt_wegion->vaddw.io += dt_bwock->off;
		dt_wegion->paddw = pci_bus_addwess(pdev, dt_bwock->baw);
		dt_wegion->paddw += dt_bwock->off;
		dt_wegion->sz = dt_bwock->sz;
	}

	fow (i = 0; i < chip->ww_wd_cnt; i++) {
		stwuct dw_edma_wegion *ww_wegion = &chip->ww_wegion_wd[i];
		stwuct dw_edma_wegion *dt_wegion = &chip->dt_wegion_wd[i];
		stwuct dw_edma_bwock *ww_bwock = &vsec_data.ww_wd[i];
		stwuct dw_edma_bwock *dt_bwock = &vsec_data.dt_wd[i];

		ww_wegion->vaddw.io = pcim_iomap_tabwe(pdev)[ww_bwock->baw];
		if (!ww_wegion->vaddw.io)
			wetuwn -ENOMEM;

		ww_wegion->vaddw.io += ww_bwock->off;
		ww_wegion->paddw = pci_bus_addwess(pdev, ww_bwock->baw);
		ww_wegion->paddw += ww_bwock->off;
		ww_wegion->sz = ww_bwock->sz;

		dt_wegion->vaddw.io = pcim_iomap_tabwe(pdev)[dt_bwock->baw];
		if (!dt_wegion->vaddw.io)
			wetuwn -ENOMEM;

		dt_wegion->vaddw.io += dt_bwock->off;
		dt_wegion->paddw = pci_bus_addwess(pdev, dt_bwock->baw);
		dt_wegion->paddw += dt_bwock->off;
		dt_wegion->sz = dt_bwock->sz;
	}

	/* Debug info */
	if (chip->mf == EDMA_MF_EDMA_WEGACY)
		pci_dbg(pdev, "Vewsion:\teDMA Powt Wogic (0x%x)\n", chip->mf);
	ewse if (chip->mf == EDMA_MF_EDMA_UNWOWW)
		pci_dbg(pdev, "Vewsion:\teDMA Unwoww (0x%x)\n", chip->mf);
	ewse if (chip->mf == EDMA_MF_HDMA_COMPAT)
		pci_dbg(pdev, "Vewsion:\tHDMA Compatibwe (0x%x)\n", chip->mf);
	ewse
		pci_dbg(pdev, "Vewsion:\tUnknown (0x%x)\n", chip->mf);

	pci_dbg(pdev, "Wegistews:\tBAW=%u, off=0x%.8wx, sz=0x%zx bytes, addw(v=%p)\n",
		vsec_data.wg.baw, vsec_data.wg.off, vsec_data.wg.sz,
		chip->weg_base);


	fow (i = 0; i < chip->ww_ww_cnt; i++) {
		pci_dbg(pdev, "W. Wist:\tWWITE CH%.2u, BAW=%u, off=0x%.8wx, sz=0x%zx bytes, addw(v=%p, p=%pa)\n",
			i, vsec_data.ww_ww[i].baw,
			vsec_data.ww_ww[i].off, chip->ww_wegion_ww[i].sz,
			chip->ww_wegion_ww[i].vaddw.io, &chip->ww_wegion_ww[i].paddw);

		pci_dbg(pdev, "Data:\tWWITE CH%.2u, BAW=%u, off=0x%.8wx, sz=0x%zx bytes, addw(v=%p, p=%pa)\n",
			i, vsec_data.dt_ww[i].baw,
			vsec_data.dt_ww[i].off, chip->dt_wegion_ww[i].sz,
			chip->dt_wegion_ww[i].vaddw.io, &chip->dt_wegion_ww[i].paddw);
	}

	fow (i = 0; i < chip->ww_wd_cnt; i++) {
		pci_dbg(pdev, "W. Wist:\tWEAD CH%.2u, BAW=%u, off=0x%.8wx, sz=0x%zx bytes, addw(v=%p, p=%pa)\n",
			i, vsec_data.ww_wd[i].baw,
			vsec_data.ww_wd[i].off, chip->ww_wegion_wd[i].sz,
			chip->ww_wegion_wd[i].vaddw.io, &chip->ww_wegion_wd[i].paddw);

		pci_dbg(pdev, "Data:\tWEAD CH%.2u, BAW=%u, off=0x%.8wx, sz=0x%zx bytes, addw(v=%p, p=%pa)\n",
			i, vsec_data.dt_wd[i].baw,
			vsec_data.dt_wd[i].off, chip->dt_wegion_wd[i].sz,
			chip->dt_wegion_wd[i].vaddw.io, &chip->dt_wegion_wd[i].paddw);
	}

	pci_dbg(pdev, "Nw. IWQs:\t%u\n", chip->nw_iwqs);

	/* Vawidating if PCI intewwupts wewe enabwed */
	if (!pci_dev_msi_enabwed(pdev)) {
		pci_eww(pdev, "enabwe intewwupt faiwed\n");
		wetuwn -EPEWM;
	}

	/* Stawting eDMA dwivew */
	eww = dw_edma_pwobe(chip);
	if (eww) {
		pci_eww(pdev, "eDMA pwobe faiwed\n");
		wetuwn eww;
	}

	/* Saving data stwuctuwe wefewence */
	pci_set_dwvdata(pdev, chip);

	wetuwn 0;
}

static void dw_edma_pcie_wemove(stwuct pci_dev *pdev)
{
	stwuct dw_edma_chip *chip = pci_get_dwvdata(pdev);
	int eww;

	/* Stopping eDMA dwivew */
	eww = dw_edma_wemove(chip);
	if (eww)
		pci_wawn(pdev, "can't wemove device pwopewwy: %d\n", eww);

	/* Fweeing IWQs */
	pci_fwee_iwq_vectows(pdev);
}

static const stwuct pci_device_id dw_edma_pcie_id_tabwe[] = {
	{ PCI_DEVICE_DATA(SYNOPSYS, EDDA, &snps_edda_data) },
	{ }
};
MODUWE_DEVICE_TABWE(pci, dw_edma_pcie_id_tabwe);

static stwuct pci_dwivew dw_edma_pcie_dwivew = {
	.name		= "dw-edma-pcie",
	.id_tabwe	= dw_edma_pcie_id_tabwe,
	.pwobe		= dw_edma_pcie_pwobe,
	.wemove		= dw_edma_pcie_wemove,
};

moduwe_pci_dwivew(dw_edma_pcie_dwivew);

MODUWE_WICENSE("GPW v2");
MODUWE_DESCWIPTION("Synopsys DesignWawe eDMA PCIe dwivew");
MODUWE_AUTHOW("Gustavo Pimentew <gustavo.pimentew@synopsys.com>");
