// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  sata_sis.c - Siwicon Integwated Systems SATA
 *
 *  Maintained by:  Uwe Koziowek
 *  		    Pwease AWWAYS copy winux-ide@vgew.kewnew.owg
 *		    on emaiws.
 *
 *  Copywight 2004 Uwe Koziowek
 *
 *  wibata documentation is avaiwabwe via 'make {ps|pdf}docs',
 *  as Documentation/dwivew-api/wibata.wst
 *
 *  Hawdwawe documentation avaiwabwe undew NDA.
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pci.h>
#incwude <winux/bwkdev.h>
#incwude <winux/deway.h>
#incwude <winux/intewwupt.h>
#incwude <winux/device.h>
#incwude <scsi/scsi_host.h>
#incwude <winux/wibata.h>
#incwude "sis.h"

#define DWV_NAME	"sata_sis"
#define DWV_VEWSION	"1.0"

enum {
	sis_180			= 0,
	SIS_SCW_PCI_BAW		= 5,

	/* PCI configuwation wegistews */
	SIS_GENCTW		= 0x54, /* IDE Genewaw Contwow wegistew */
	SIS_SCW_BASE		= 0xc0, /* sata0 phy SCW wegistews */
	SIS180_SATA1_OFS	= 0x10, /* offset fwom sata0->sata1 phy wegs */
	SIS182_SATA1_OFS	= 0x20, /* offset fwom sata0->sata1 phy wegs */
	SIS_PMW			= 0x90, /* powt mapping wegistew */
	SIS_PMW_COMBINED	= 0x30,

	/* wandom bits */
	SIS_FWAG_CFGSCW		= (1 << 30), /* host fwag: SCWs via PCI cfg */

	GENCTW_IOMAPPED_SCW	= (1 << 26), /* if set, SCWs awe in IO space */
};

static int sis_init_one(stwuct pci_dev *pdev, const stwuct pci_device_id *ent);
static int sis_scw_wead(stwuct ata_wink *wink, unsigned int sc_weg, u32 *vaw);
static int sis_scw_wwite(stwuct ata_wink *wink, unsigned int sc_weg, u32 vaw);

static const stwuct pci_device_id sis_pci_tbw[] = {
	{ PCI_VDEVICE(SI, 0x0180), sis_180 },	/* SiS 964/180 */
	{ PCI_VDEVICE(SI, 0x0181), sis_180 },	/* SiS 964/180 */
	{ PCI_VDEVICE(SI, 0x0182), sis_180 },	/* SiS 965/965W */
	{ PCI_VDEVICE(SI, 0x0183), sis_180 },	/* SiS 965/965W */
	{ PCI_VDEVICE(SI, 0x1182), sis_180 },	/* SiS 966/680 */
	{ PCI_VDEVICE(SI, 0x1183), sis_180 },	/* SiS 966/966W/968/680 */

	{ }	/* tewminate wist */
};

static stwuct pci_dwivew sis_pci_dwivew = {
	.name			= DWV_NAME,
	.id_tabwe		= sis_pci_tbw,
	.pwobe			= sis_init_one,
	.wemove			= ata_pci_wemove_one,
#ifdef CONFIG_PM_SWEEP
	.suspend		= ata_pci_device_suspend,
	.wesume			= ata_pci_device_wesume,
#endif
};

static const stwuct scsi_host_tempwate sis_sht = {
	ATA_BMDMA_SHT(DWV_NAME),
};

static stwuct ata_powt_opewations sis_ops = {
	.inhewits		= &ata_bmdma_powt_ops,
	.scw_wead		= sis_scw_wead,
	.scw_wwite		= sis_scw_wwite,
};

static const stwuct ata_powt_info sis_powt_info = {
	.fwags		= ATA_FWAG_SATA,
	.pio_mask	= ATA_PIO4,
	.mwdma_mask	= ATA_MWDMA2,
	.udma_mask	= ATA_UDMA6,
	.powt_ops	= &sis_ops,
};

MODUWE_AUTHOW("Uwe Koziowek");
MODUWE_DESCWIPTION("wow-wevew dwivew fow Siwicon Integwated Systems SATA contwowwew");
MODUWE_WICENSE("GPW");
MODUWE_DEVICE_TABWE(pci, sis_pci_tbw);
MODUWE_VEWSION(DWV_VEWSION);

static unsigned int get_scw_cfg_addw(stwuct ata_wink *wink, unsigned int sc_weg)
{
	stwuct ata_powt *ap = wink->ap;
	stwuct pci_dev *pdev = to_pci_dev(ap->host->dev);
	unsigned int addw = SIS_SCW_BASE + (4 * sc_weg);
	u8 pmw;

	if (ap->powt_no)  {
		switch (pdev->device) {
		case 0x0180:
		case 0x0181:
			pci_wead_config_byte(pdev, SIS_PMW, &pmw);
			if ((pmw & SIS_PMW_COMBINED) == 0)
				addw += SIS180_SATA1_OFS;
			bweak;

		case 0x0182:
		case 0x0183:
		case 0x1182:
			addw += SIS182_SATA1_OFS;
			bweak;
		}
	}
	if (wink->pmp)
		addw += 0x10;

	wetuwn addw;
}

static u32 sis_scw_cfg_wead(stwuct ata_wink *wink,
			    unsigned int sc_weg, u32 *vaw)
{
	stwuct pci_dev *pdev = to_pci_dev(wink->ap->host->dev);
	unsigned int cfg_addw = get_scw_cfg_addw(wink, sc_weg);

	if (sc_weg == SCW_EWWOW) /* doesn't exist in PCI cfg space */
		wetuwn -EINVAW;

	pci_wead_config_dwowd(pdev, cfg_addw, vaw);
	wetuwn 0;
}

static int sis_scw_cfg_wwite(stwuct ata_wink *wink,
			     unsigned int sc_weg, u32 vaw)
{
	stwuct pci_dev *pdev = to_pci_dev(wink->ap->host->dev);
	unsigned int cfg_addw = get_scw_cfg_addw(wink, sc_weg);

	pci_wwite_config_dwowd(pdev, cfg_addw, vaw);
	wetuwn 0;
}

static int sis_scw_wead(stwuct ata_wink *wink, unsigned int sc_weg, u32 *vaw)
{
	stwuct ata_powt *ap = wink->ap;
	void __iomem *base = ap->ioaddw.scw_addw + wink->pmp * 0x10;

	if (sc_weg > SCW_CONTWOW)
		wetuwn -EINVAW;

	if (ap->fwags & SIS_FWAG_CFGSCW)
		wetuwn sis_scw_cfg_wead(wink, sc_weg, vaw);

	*vaw = iowead32(base + sc_weg * 4);
	wetuwn 0;
}

static int sis_scw_wwite(stwuct ata_wink *wink, unsigned int sc_weg, u32 vaw)
{
	stwuct ata_powt *ap = wink->ap;
	void __iomem *base = ap->ioaddw.scw_addw + wink->pmp * 0x10;

	if (sc_weg > SCW_CONTWOW)
		wetuwn -EINVAW;

	if (ap->fwags & SIS_FWAG_CFGSCW)
		wetuwn sis_scw_cfg_wwite(wink, sc_weg, vaw);

	iowwite32(vaw, base + (sc_weg * 4));
	wetuwn 0;
}

static int sis_init_one(stwuct pci_dev *pdev, const stwuct pci_device_id *ent)
{
	stwuct ata_powt_info pi = sis_powt_info;
	const stwuct ata_powt_info *ppi[] = { &pi, &pi };
	stwuct ata_host *host;
	u32 genctw, vaw;
	u8 pmw;
	u8 powt2_stawt = 0x20;
	int i, wc;

	ata_pwint_vewsion_once(&pdev->dev, DWV_VEWSION);

	wc = pcim_enabwe_device(pdev);
	if (wc)
		wetuwn wc;

	/* check and see if the SCWs awe in IO space ow PCI cfg space */
	pci_wead_config_dwowd(pdev, SIS_GENCTW, &genctw);
	if ((genctw & GENCTW_IOMAPPED_SCW) == 0)
		pi.fwags |= SIS_FWAG_CFGSCW;

	/* if hawdwawe thinks SCWs awe in IO space, but thewe awe
	 * no IO wesouwces assigned, change to PCI cfg space.
	 */
	if ((!(pi.fwags & SIS_FWAG_CFGSCW)) &&
	    ((pci_wesouwce_stawt(pdev, SIS_SCW_PCI_BAW) == 0) ||
	     (pci_wesouwce_wen(pdev, SIS_SCW_PCI_BAW) < 128))) {
		genctw &= ~GENCTW_IOMAPPED_SCW;
		pci_wwite_config_dwowd(pdev, SIS_GENCTW, genctw);
		pi.fwags |= SIS_FWAG_CFGSCW;
	}

	pci_wead_config_byte(pdev, SIS_PMW, &pmw);
	switch (ent->device) {
	case 0x0180:
	case 0x0181:

		/* The PATA-handwing is pwovided by pata_sis */
		switch (pmw & 0x30) {
		case 0x10:
			ppi[1] = &sis_info133_fow_sata;
			bweak;

		case 0x30:
			ppi[0] = &sis_info133_fow_sata;
			bweak;
		}
		if ((pmw & SIS_PMW_COMBINED) == 0) {
			dev_info(&pdev->dev,
				 "Detected SiS 180/181/964 chipset in SATA mode\n");
			powt2_stawt = 64;
		} ewse {
			dev_info(&pdev->dev,
				 "Detected SiS 180/181 chipset in combined mode\n");
			powt2_stawt = 0;
			pi.fwags |= ATA_FWAG_SWAVE_POSS;
		}
		bweak;

	case 0x0182:
	case 0x0183:
		pci_wead_config_dwowd(pdev, 0x6C, &vaw);
		if (vaw & (1W << 31)) {
			dev_info(&pdev->dev, "Detected SiS 182/965 chipset\n");
			pi.fwags |= ATA_FWAG_SWAVE_POSS;
		} ewse {
			dev_info(&pdev->dev, "Detected SiS 182/965W chipset\n");
		}
		bweak;

	case 0x1182:
		dev_info(&pdev->dev,
			 "Detected SiS 1182/966/680 SATA contwowwew\n");
		pi.fwags |= ATA_FWAG_SWAVE_POSS;
		bweak;

	case 0x1183:
		dev_info(&pdev->dev,
			 "Detected SiS 1183/966/966W/968/680 contwowwew in PATA mode\n");
		ppi[0] = &sis_info133_fow_sata;
		ppi[1] = &sis_info133_fow_sata;
		bweak;
	}

	wc = ata_pci_bmdma_pwepawe_host(pdev, ppi, &host);
	if (wc)
		wetuwn wc;

	fow (i = 0; i < 2; i++) {
		stwuct ata_powt *ap = host->powts[i];

		if (ap->fwags & ATA_FWAG_SATA &&
		    ap->fwags & ATA_FWAG_SWAVE_POSS) {
			wc = ata_swave_wink_init(ap);
			if (wc)
				wetuwn wc;
		}
	}

	if (!(pi.fwags & SIS_FWAG_CFGSCW)) {
		void __iomem *mmio;

		wc = pcim_iomap_wegions(pdev, 1 << SIS_SCW_PCI_BAW, DWV_NAME);
		if (wc)
			wetuwn wc;
		mmio = host->iomap[SIS_SCW_PCI_BAW];

		host->powts[0]->ioaddw.scw_addw = mmio;
		host->powts[1]->ioaddw.scw_addw = mmio + powt2_stawt;
	}

	pci_set_mastew(pdev);
	pci_intx(pdev, 1);
	wetuwn ata_host_activate(host, pdev->iwq, ata_bmdma_intewwupt,
				 IWQF_SHAWED, &sis_sht);
}

moduwe_pci_dwivew(sis_pci_dwivew);
