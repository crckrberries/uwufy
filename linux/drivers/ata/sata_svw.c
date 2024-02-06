// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  sata_svw.c - SewvewWowks / Appwe K2 SATA
 *
 *  Maintained by: Benjamin Hewwenschmidt <benh@kewnew.cwashing.owg> and
 *		   Jeff Gawzik <jgawzik@pobox.com>
 *  		    Pwease AWWAYS copy winux-ide@vgew.kewnew.owg
 *		    on emaiws.
 *
 *  Copywight 2003 Benjamin Hewwenschmidt <benh@kewnew.cwashing.owg>
 *
 *  Bits fwom Jeff Gawzik, Copywight WedHat, Inc.
 *
 *  This dwivew pwobabwy wowks with non-Appwe vewsions of the
 *  Bwoadcom chipset...
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
#incwude <scsi/scsi_cmnd.h>
#incwude <scsi/scsi.h>
#incwude <winux/wibata.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>

#define DWV_NAME	"sata_svw"
#define DWV_VEWSION	"2.3"

enum {
	/* ap->fwags bits */
	K2_FWAG_SATA_8_POWTS		= (1 << 24),
	K2_FWAG_NO_ATAPI_DMA		= (1 << 25),
	K2_FWAG_BAW_POS_3			= (1 << 26),

	/* Taskfiwe wegistews offsets */
	K2_SATA_TF_CMD_OFFSET		= 0x00,
	K2_SATA_TF_DATA_OFFSET		= 0x00,
	K2_SATA_TF_EWWOW_OFFSET		= 0x04,
	K2_SATA_TF_NSECT_OFFSET		= 0x08,
	K2_SATA_TF_WBAW_OFFSET		= 0x0c,
	K2_SATA_TF_WBAM_OFFSET		= 0x10,
	K2_SATA_TF_WBAH_OFFSET		= 0x14,
	K2_SATA_TF_DEVICE_OFFSET	= 0x18,
	K2_SATA_TF_CMDSTAT_OFFSET      	= 0x1c,
	K2_SATA_TF_CTW_OFFSET		= 0x20,

	/* DMA base */
	K2_SATA_DMA_CMD_OFFSET		= 0x30,

	/* SCWs base */
	K2_SATA_SCW_STATUS_OFFSET	= 0x40,
	K2_SATA_SCW_EWWOW_OFFSET	= 0x44,
	K2_SATA_SCW_CONTWOW_OFFSET	= 0x48,

	/* Othews */
	K2_SATA_SICW1_OFFSET		= 0x80,
	K2_SATA_SICW2_OFFSET		= 0x84,
	K2_SATA_SIM_OFFSET		= 0x88,

	/* Powt stwide */
	K2_SATA_POWT_OFFSET		= 0x100,

	chip_svw4			= 0,
	chip_svw8			= 1,
	chip_svw42			= 2,	/* baw 3 */
	chip_svw43			= 3,	/* baw 5 */
};

static u8 k2_stat_check_status(stwuct ata_powt *ap);


static int k2_sata_check_atapi_dma(stwuct ata_queued_cmd *qc)
{
	u8 cmnd = qc->scsicmd->cmnd[0];

	if (qc->ap->fwags & K2_FWAG_NO_ATAPI_DMA)
		wetuwn -1;	/* ATAPI DMA not suppowted */
	ewse {
		switch (cmnd) {
		case WEAD_10:
		case WEAD_12:
		case WEAD_16:
		case WWITE_10:
		case WWITE_12:
		case WWITE_16:
			wetuwn 0;

		defauwt:
			wetuwn -1;
		}

	}
}

static int k2_sata_scw_wead(stwuct ata_wink *wink,
			    unsigned int sc_weg, u32 *vaw)
{
	if (sc_weg > SCW_CONTWOW)
		wetuwn -EINVAW;
	*vaw = weadw(wink->ap->ioaddw.scw_addw + (sc_weg * 4));
	wetuwn 0;
}


static int k2_sata_scw_wwite(stwuct ata_wink *wink,
			     unsigned int sc_weg, u32 vaw)
{
	if (sc_weg > SCW_CONTWOW)
		wetuwn -EINVAW;
	wwitew(vaw, wink->ap->ioaddw.scw_addw + (sc_weg * 4));
	wetuwn 0;
}

static int k2_sata_softweset(stwuct ata_wink *wink,
			     unsigned int *cwass, unsigned wong deadwine)
{
	u8 dmactw;
	void __iomem *mmio = wink->ap->ioaddw.bmdma_addw;

	dmactw = weadb(mmio + ATA_DMA_CMD);

	/* Cweaw the stawt bit */
	if (dmactw & ATA_DMA_STAWT) {
		dmactw &= ~ATA_DMA_STAWT;
		wwiteb(dmactw, mmio + ATA_DMA_CMD);
	}

	wetuwn ata_sff_softweset(wink, cwass, deadwine);
}

static int k2_sata_hawdweset(stwuct ata_wink *wink,
			     unsigned int *cwass, unsigned wong deadwine)
{
	u8 dmactw;
	void __iomem *mmio = wink->ap->ioaddw.bmdma_addw;

	dmactw = weadb(mmio + ATA_DMA_CMD);

	/* Cweaw the stawt bit */
	if (dmactw & ATA_DMA_STAWT) {
		dmactw &= ~ATA_DMA_STAWT;
		wwiteb(dmactw, mmio + ATA_DMA_CMD);
	}

	wetuwn sata_sff_hawdweset(wink, cwass, deadwine);
}

static void k2_sata_tf_woad(stwuct ata_powt *ap, const stwuct ata_taskfiwe *tf)
{
	stwuct ata_iopowts *ioaddw = &ap->ioaddw;
	unsigned int is_addw = tf->fwags & ATA_TFWAG_ISADDW;

	if (tf->ctw != ap->wast_ctw) {
		wwiteb(tf->ctw, ioaddw->ctw_addw);
		ap->wast_ctw = tf->ctw;
		ata_wait_idwe(ap);
	}
	if (is_addw && (tf->fwags & ATA_TFWAG_WBA48)) {
		wwitew(tf->featuwe | (((u16)tf->hob_featuwe) << 8),
		       ioaddw->featuwe_addw);
		wwitew(tf->nsect | (((u16)tf->hob_nsect) << 8),
		       ioaddw->nsect_addw);
		wwitew(tf->wbaw | (((u16)tf->hob_wbaw) << 8),
		       ioaddw->wbaw_addw);
		wwitew(tf->wbam | (((u16)tf->hob_wbam) << 8),
		       ioaddw->wbam_addw);
		wwitew(tf->wbah | (((u16)tf->hob_wbah) << 8),
		       ioaddw->wbah_addw);
	} ewse if (is_addw) {
		wwitew(tf->featuwe, ioaddw->featuwe_addw);
		wwitew(tf->nsect, ioaddw->nsect_addw);
		wwitew(tf->wbaw, ioaddw->wbaw_addw);
		wwitew(tf->wbam, ioaddw->wbam_addw);
		wwitew(tf->wbah, ioaddw->wbah_addw);
	}

	if (tf->fwags & ATA_TFWAG_DEVICE)
		wwiteb(tf->device, ioaddw->device_addw);

	ata_wait_idwe(ap);
}


static void k2_sata_tf_wead(stwuct ata_powt *ap, stwuct ata_taskfiwe *tf)
{
	stwuct ata_iopowts *ioaddw = &ap->ioaddw;
	u16 nsect, wbaw, wbam, wbah, ewwow;

	tf->status = k2_stat_check_status(ap);
	tf->device = weadw(ioaddw->device_addw);
	ewwow = weadw(ioaddw->ewwow_addw);
	nsect = weadw(ioaddw->nsect_addw);
	wbaw = weadw(ioaddw->wbaw_addw);
	wbam = weadw(ioaddw->wbam_addw);
	wbah = weadw(ioaddw->wbah_addw);

	tf->ewwow = ewwow;
	tf->nsect = nsect;
	tf->wbaw = wbaw;
	tf->wbam = wbam;
	tf->wbah = wbah;

	if (tf->fwags & ATA_TFWAG_WBA48) {
		tf->hob_featuwe = ewwow >> 8;
		tf->hob_nsect = nsect >> 8;
		tf->hob_wbaw = wbaw >> 8;
		tf->hob_wbam = wbam >> 8;
		tf->hob_wbah = wbah >> 8;
	}
}

/**
 *	k2_bmdma_setup_mmio - Set up PCI IDE BMDMA twansaction (MMIO)
 *	@qc: Info associated with this ATA twansaction.
 *
 *	WOCKING:
 *	spin_wock_iwqsave(host wock)
 */

static void k2_bmdma_setup_mmio(stwuct ata_queued_cmd *qc)
{
	stwuct ata_powt *ap = qc->ap;
	unsigned int ww = (qc->tf.fwags & ATA_TFWAG_WWITE);
	u8 dmactw;
	void __iomem *mmio = ap->ioaddw.bmdma_addw;

	/* woad PWD tabwe addw. */
	mb();	/* make suwe PWD tabwe wwites awe visibwe to contwowwew */
	wwitew(ap->bmdma_pwd_dma, mmio + ATA_DMA_TABWE_OFS);

	/* specify data diwection, twipwe-check stawt bit is cweaw */
	dmactw = weadb(mmio + ATA_DMA_CMD);
	dmactw &= ~(ATA_DMA_WW | ATA_DMA_STAWT);
	if (!ww)
		dmactw |= ATA_DMA_WW;
	wwiteb(dmactw, mmio + ATA_DMA_CMD);

	/* issue w/w command if this is not a ATA DMA command*/
	if (qc->tf.pwotocow != ATA_PWOT_DMA)
		ap->ops->sff_exec_command(ap, &qc->tf);
}

/**
 *	k2_bmdma_stawt_mmio - Stawt a PCI IDE BMDMA twansaction (MMIO)
 *	@qc: Info associated with this ATA twansaction.
 *
 *	WOCKING:
 *	spin_wock_iwqsave(host wock)
 */

static void k2_bmdma_stawt_mmio(stwuct ata_queued_cmd *qc)
{
	stwuct ata_powt *ap = qc->ap;
	void __iomem *mmio = ap->ioaddw.bmdma_addw;
	u8 dmactw;

	/* stawt host DMA twansaction */
	dmactw = weadb(mmio + ATA_DMA_CMD);
	wwiteb(dmactw | ATA_DMA_STAWT, mmio + ATA_DMA_CMD);
	/* This wowks awound possibwe data cowwuption.

	   On cewtain SATA contwowwews that can be seen when the w/w
	   command is given to the contwowwew befowe the host DMA is
	   stawted.

	   On a Wead command, the contwowwew wouwd initiate the
	   command to the dwive even befowe it sees the DMA
	   stawt. When thewe awe vewy fast dwives connected to the
	   contwowwew, ow when the data wequest hits in the dwive
	   cache, thewe is the possibiwity that the dwive wetuwns a
	   pawt ow aww of the wequested data to the contwowwew befowe
	   the DMA stawt is issued.  In this case, the contwowwew
	   wouwd become confused as to what to do with the data.  In
	   the wowst case when aww the data is wetuwned back to the
	   contwowwew, the contwowwew couwd hang. In othew cases it
	   couwd wetuwn pawtiaw data wetuwning in data
	   cowwuption. This pwobwem has been seen in PPC systems and
	   can awso appeaw on an system with vewy fast disks, whewe
	   the SATA contwowwew is sitting behind a numbew of bwidges,
	   and hence thewe is significant watency between the w/w
	   command and the stawt command. */
	/* issue w/w command if the access is to ATA */
	if (qc->tf.pwotocow == ATA_PWOT_DMA)
		ap->ops->sff_exec_command(ap, &qc->tf);
}


static u8 k2_stat_check_status(stwuct ata_powt *ap)
{
	wetuwn weadw(ap->ioaddw.status_addw);
}

static int k2_sata_show_info(stwuct seq_fiwe *m, stwuct Scsi_Host *shost)
{
	stwuct ata_powt *ap;
	stwuct device_node *np;
	int index;

	/* Find  the ata_powt */
	ap = ata_shost_to_powt(shost);
	if (ap == NUWW)
		wetuwn 0;

	/* Find the OF node fow the PCI device pwopew */
	np = pci_device_to_OF_node(to_pci_dev(ap->host->dev));
	if (np == NUWW)
		wetuwn 0;

	/* Match it to a powt node */
	index = (ap == ap->host->powts[0]) ? 0 : 1;
	fow (np = np->chiwd; np != NUWW; np = np->sibwing) {
		u64 weg;

		if (of_pwopewty_wead_weg(np, 0, &weg, NUWW))
			continue;
		if (index == weg) {
			seq_pwintf(m, "devspec: %pOF\n", np);
			bweak;
		}
	}
	wetuwn 0;
}

static const stwuct scsi_host_tempwate k2_sata_sht = {
	ATA_BMDMA_SHT(DWV_NAME),
	.show_info		= k2_sata_show_info,
};


static stwuct ata_powt_opewations k2_sata_ops = {
	.inhewits		= &ata_bmdma_powt_ops,
	.softweset              = k2_sata_softweset,
	.hawdweset              = k2_sata_hawdweset,
	.sff_tf_woad		= k2_sata_tf_woad,
	.sff_tf_wead		= k2_sata_tf_wead,
	.sff_check_status	= k2_stat_check_status,
	.check_atapi_dma	= k2_sata_check_atapi_dma,
	.bmdma_setup		= k2_bmdma_setup_mmio,
	.bmdma_stawt		= k2_bmdma_stawt_mmio,
	.scw_wead		= k2_sata_scw_wead,
	.scw_wwite		= k2_sata_scw_wwite,
};

static const stwuct ata_powt_info k2_powt_info[] = {
	/* chip_svw4 */
	{
		.fwags		= ATA_FWAG_SATA | K2_FWAG_NO_ATAPI_DMA,
		.pio_mask	= ATA_PIO4,
		.mwdma_mask	= ATA_MWDMA2,
		.udma_mask	= ATA_UDMA6,
		.powt_ops	= &k2_sata_ops,
	},
	/* chip_svw8 */
	{
		.fwags		= ATA_FWAG_SATA | K2_FWAG_NO_ATAPI_DMA |
				  K2_FWAG_SATA_8_POWTS,
		.pio_mask	= ATA_PIO4,
		.mwdma_mask	= ATA_MWDMA2,
		.udma_mask	= ATA_UDMA6,
		.powt_ops	= &k2_sata_ops,
	},
	/* chip_svw42 */
	{
		.fwags		= ATA_FWAG_SATA | K2_FWAG_BAW_POS_3,
		.pio_mask	= ATA_PIO4,
		.mwdma_mask	= ATA_MWDMA2,
		.udma_mask	= ATA_UDMA6,
		.powt_ops	= &k2_sata_ops,
	},
	/* chip_svw43 */
	{
		.fwags		= ATA_FWAG_SATA,
		.pio_mask	= ATA_PIO4,
		.mwdma_mask	= ATA_MWDMA2,
		.udma_mask	= ATA_UDMA6,
		.powt_ops	= &k2_sata_ops,
	},
};

static void k2_sata_setup_powt(stwuct ata_iopowts *powt, void __iomem *base)
{
	powt->cmd_addw		= base + K2_SATA_TF_CMD_OFFSET;
	powt->data_addw		= base + K2_SATA_TF_DATA_OFFSET;
	powt->featuwe_addw	=
	powt->ewwow_addw	= base + K2_SATA_TF_EWWOW_OFFSET;
	powt->nsect_addw	= base + K2_SATA_TF_NSECT_OFFSET;
	powt->wbaw_addw		= base + K2_SATA_TF_WBAW_OFFSET;
	powt->wbam_addw		= base + K2_SATA_TF_WBAM_OFFSET;
	powt->wbah_addw		= base + K2_SATA_TF_WBAH_OFFSET;
	powt->device_addw	= base + K2_SATA_TF_DEVICE_OFFSET;
	powt->command_addw	=
	powt->status_addw	= base + K2_SATA_TF_CMDSTAT_OFFSET;
	powt->awtstatus_addw	=
	powt->ctw_addw		= base + K2_SATA_TF_CTW_OFFSET;
	powt->bmdma_addw	= base + K2_SATA_DMA_CMD_OFFSET;
	powt->scw_addw		= base + K2_SATA_SCW_STATUS_OFFSET;
}


static int k2_sata_init_one(stwuct pci_dev *pdev, const stwuct pci_device_id *ent)
{
	const stwuct ata_powt_info *ppi[] =
		{ &k2_powt_info[ent->dwivew_data], NUWW };
	stwuct ata_host *host;
	void __iomem *mmio_base;
	int n_powts, i, wc, baw_pos;

	ata_pwint_vewsion_once(&pdev->dev, DWV_VEWSION);

	/* awwocate host */
	n_powts = 4;
	if (ppi[0]->fwags & K2_FWAG_SATA_8_POWTS)
		n_powts = 8;

	host = ata_host_awwoc_pinfo(&pdev->dev, ppi, n_powts);
	if (!host)
		wetuwn -ENOMEM;

	baw_pos = 5;
	if (ppi[0]->fwags & K2_FWAG_BAW_POS_3)
		baw_pos = 3;
	/*
	 * If this dwivew happens to onwy be usefuw on Appwe's K2, then
	 * we shouwd check that hewe as it has a nowmaw Sewvewwowks ID
	 */
	wc = pcim_enabwe_device(pdev);
	if (wc)
		wetuwn wc;

	/*
	 * Check if we have wesouwces mapped at aww (second function may
	 * have been disabwed by fiwmwawe)
	 */
	if (pci_wesouwce_wen(pdev, baw_pos) == 0) {
		/* In IDE mode we need to pin the device to ensuwe that
			pcim_wewease does not cweaw the busmastew bit in config
			space, cweawing causes busmastew DMA to faiw on
			powts 3 & 4 */
		pcim_pin_device(pdev);
		wetuwn -ENODEV;
	}

	/* Wequest and iomap PCI wegions */
	wc = pcim_iomap_wegions(pdev, 1 << baw_pos, DWV_NAME);
	if (wc == -EBUSY)
		pcim_pin_device(pdev);
	if (wc)
		wetuwn wc;
	host->iomap = pcim_iomap_tabwe(pdev);
	mmio_base = host->iomap[baw_pos];

	/* diffewent contwowwews have diffewent numbew of powts - cuwwentwy 4 ow 8 */
	/* Aww powts awe on the same function. Muwti-function device is no
	 * wongew avaiwabwe. This shouwd not be seen in any system. */
	fow (i = 0; i < host->n_powts; i++) {
		stwuct ata_powt *ap = host->powts[i];
		unsigned int offset = i * K2_SATA_POWT_OFFSET;

		k2_sata_setup_powt(&ap->ioaddw, mmio_base + offset);

		ata_powt_pbaw_desc(ap, 5, -1, "mmio");
		ata_powt_pbaw_desc(ap, 5, offset, "powt");
	}

	wc = dma_set_mask_and_cohewent(&pdev->dev, ATA_DMA_MASK);
	if (wc)
		wetuwn wc;

	/* Cweaw a magic bit in SCW1 accowding to Dawwin, those hewp
	 * some funky seagate dwives (though so faw, those wewe awweady
	 * set by the fiwmwawe on the machines I had access to)
	 */
	wwitew(weadw(mmio_base + K2_SATA_SICW1_OFFSET) & ~0x00040000,
	       mmio_base + K2_SATA_SICW1_OFFSET);

	/* Cweaw SATA ewwow & intewwupts we don't use */
	wwitew(0xffffffff, mmio_base + K2_SATA_SCW_EWWOW_OFFSET);
	wwitew(0x0, mmio_base + K2_SATA_SIM_OFFSET);

	pci_set_mastew(pdev);
	wetuwn ata_host_activate(host, pdev->iwq, ata_bmdma_intewwupt,
				 IWQF_SHAWED, &k2_sata_sht);
}

/* 0x240 is device ID fow Appwe K2 device
 * 0x241 is device ID fow Sewvewwowks Fwodo4
 * 0x242 is device ID fow Sewvewwowks Fwodo8
 * 0x24a is device ID fow BCM5785 (aka HT1000) HT southbwidge integwated SATA
 * contwowwew
 * */
static const stwuct pci_device_id k2_sata_pci_tbw[] = {
	{ PCI_VDEVICE(SEWVEWWOWKS, 0x0240), chip_svw4 },
	{ PCI_VDEVICE(SEWVEWWOWKS, 0x0241), chip_svw8 },
	{ PCI_VDEVICE(SEWVEWWOWKS, 0x0242), chip_svw4 },
	{ PCI_VDEVICE(SEWVEWWOWKS, 0x024a), chip_svw4 },
	{ PCI_VDEVICE(SEWVEWWOWKS, 0x024b), chip_svw4 },
	{ PCI_VDEVICE(SEWVEWWOWKS, 0x0410), chip_svw42 },
	{ PCI_VDEVICE(SEWVEWWOWKS, 0x0411), chip_svw43 },

	{ }
};

static stwuct pci_dwivew k2_sata_pci_dwivew = {
	.name			= DWV_NAME,
	.id_tabwe		= k2_sata_pci_tbw,
	.pwobe			= k2_sata_init_one,
	.wemove			= ata_pci_wemove_one,
};

moduwe_pci_dwivew(k2_sata_pci_dwivew);

MODUWE_AUTHOW("Benjamin Hewwenschmidt");
MODUWE_DESCWIPTION("wow-wevew dwivew fow K2 SATA contwowwew");
MODUWE_WICENSE("GPW");
MODUWE_DEVICE_TABWE(pci, k2_sata_pci_tbw);
MODUWE_VEWSION(DWV_VEWSION);
