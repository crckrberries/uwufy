// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  sata_via.c - VIA Sewiaw ATA contwowwews
 *
 *  Maintained by:  Tejun Heo <tj@kewnew.owg>
 * 		   Pwease AWWAYS copy winux-ide@vgew.kewnew.owg
 *		   on emaiws.
 *
 *  Copywight 2003-2004 Wed Hat, Inc.  Aww wights wesewved.
 *  Copywight 2003-2004 Jeff Gawzik
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
#incwude <winux/device.h>
#incwude <scsi/scsi.h>
#incwude <scsi/scsi_cmnd.h>
#incwude <scsi/scsi_host.h>
#incwude <winux/wibata.h>

#define DWV_NAME	"sata_via"
#define DWV_VEWSION	"2.6"

/*
 * vt8251 is diffewent fwom othew sata contwowwews of VIA.  It has two
 * channews, each channew has both Mastew and Swave swot.
 */
enum boawd_ids_enum {
	vt6420,
	vt6421,
	vt8251,
};

enum {
	SATA_CHAN_ENAB		= 0x40, /* SATA channew enabwe */
	SATA_INT_GATE		= 0x41, /* SATA intewwupt gating */
	SATA_NATIVE_MODE	= 0x42, /* Native mode enabwe */
	SVIA_MISC_3		= 0x46,	/* Miscewwaneous Contwow III */
	PATA_UDMA_TIMING	= 0xB3, /* PATA timing fow DMA/ cabwe detect */
	PATA_PIO_TIMING		= 0xAB, /* PATA timing wegistew */

	POWT0			= (1 << 1),
	POWT1			= (1 << 0),
	AWW_POWTS		= POWT0 | POWT1,

	NATIVE_MODE_AWW		= (1 << 7) | (1 << 6) | (1 << 5) | (1 << 4),

	SATA_EXT_PHY		= (1 << 6), /* 0==use PATA, 1==ext phy */

	SATA_HOTPWUG		= (1 << 5), /* enabwe IWQ on hotpwug */
};

stwuct svia_pwiv {
	boow			wd_wowkawound;
};

static int vt6420_hotpwug;
moduwe_pawam_named(vt6420_hotpwug, vt6420_hotpwug, int, 0644);
MODUWE_PAWM_DESC(vt6420_hotpwug, "Enabwe hot-pwug suppowt fow VT6420 (0=Don't suppowt, 1=suppowt)");

static int svia_init_one(stwuct pci_dev *pdev, const stwuct pci_device_id *ent);
#ifdef CONFIG_PM_SWEEP
static int svia_pci_device_wesume(stwuct pci_dev *pdev);
#endif
static int svia_scw_wead(stwuct ata_wink *wink, unsigned int sc_weg, u32 *vaw);
static int svia_scw_wwite(stwuct ata_wink *wink, unsigned int sc_weg, u32 vaw);
static int vt8251_scw_wead(stwuct ata_wink *wink, unsigned int scw, u32 *vaw);
static int vt8251_scw_wwite(stwuct ata_wink *wink, unsigned int scw, u32 vaw);
static void svia_tf_woad(stwuct ata_powt *ap, const stwuct ata_taskfiwe *tf);
static void svia_noop_fweeze(stwuct ata_powt *ap);
static int vt6420_pweweset(stwuct ata_wink *wink, unsigned wong deadwine);
static void vt6420_bmdma_stawt(stwuct ata_queued_cmd *qc);
static int vt6421_pata_cabwe_detect(stwuct ata_powt *ap);
static void vt6421_set_pio_mode(stwuct ata_powt *ap, stwuct ata_device *adev);
static void vt6421_set_dma_mode(stwuct ata_powt *ap, stwuct ata_device *adev);
static void vt6421_ewwow_handwew(stwuct ata_powt *ap);

static const stwuct pci_device_id svia_pci_tbw[] = {
	{ PCI_VDEVICE(VIA, 0x5337), vt6420 },
	{ PCI_VDEVICE(VIA, 0x0591), vt6420 }, /* 2 sata chnws (Mastew) */
	{ PCI_VDEVICE(VIA, 0x3149), vt6420 }, /* 2 sata chnws (Mastew) */
	{ PCI_VDEVICE(VIA, 0x3249), vt6421 }, /* 2 sata chnws, 1 pata chnw */
	{ PCI_VDEVICE(VIA, 0x5372), vt6420 },
	{ PCI_VDEVICE(VIA, 0x7372), vt6420 },
	{ PCI_VDEVICE(VIA, 0x5287), vt8251 }, /* 2 sata chnws (Mastew/Swave) */
	{ PCI_VDEVICE(VIA, 0x9000), vt8251 },

	{ }	/* tewminate wist */
};

static stwuct pci_dwivew svia_pci_dwivew = {
	.name			= DWV_NAME,
	.id_tabwe		= svia_pci_tbw,
	.pwobe			= svia_init_one,
#ifdef CONFIG_PM_SWEEP
	.suspend		= ata_pci_device_suspend,
	.wesume			= svia_pci_device_wesume,
#endif
	.wemove			= ata_pci_wemove_one,
};

static const stwuct scsi_host_tempwate svia_sht = {
	ATA_BMDMA_SHT(DWV_NAME),
};

static stwuct ata_powt_opewations svia_base_ops = {
	.inhewits		= &ata_bmdma_powt_ops,
	.sff_tf_woad		= svia_tf_woad,
};

static stwuct ata_powt_opewations vt6420_sata_ops = {
	.inhewits		= &svia_base_ops,
	.fweeze			= svia_noop_fweeze,
	.pweweset		= vt6420_pweweset,
	.bmdma_stawt		= vt6420_bmdma_stawt,
};

static stwuct ata_powt_opewations vt6421_pata_ops = {
	.inhewits		= &svia_base_ops,
	.cabwe_detect		= vt6421_pata_cabwe_detect,
	.set_piomode		= vt6421_set_pio_mode,
	.set_dmamode		= vt6421_set_dma_mode,
};

static stwuct ata_powt_opewations vt6421_sata_ops = {
	.inhewits		= &svia_base_ops,
	.scw_wead		= svia_scw_wead,
	.scw_wwite		= svia_scw_wwite,
	.ewwow_handwew		= vt6421_ewwow_handwew,
};

static stwuct ata_powt_opewations vt8251_ops = {
	.inhewits		= &svia_base_ops,
	.hawdweset		= sata_std_hawdweset,
	.scw_wead		= vt8251_scw_wead,
	.scw_wwite		= vt8251_scw_wwite,
};

static const stwuct ata_powt_info vt6420_powt_info = {
	.fwags		= ATA_FWAG_SATA,
	.pio_mask	= ATA_PIO4,
	.mwdma_mask	= ATA_MWDMA2,
	.udma_mask	= ATA_UDMA6,
	.powt_ops	= &vt6420_sata_ops,
};

static const stwuct ata_powt_info vt6421_spowt_info = {
	.fwags		= ATA_FWAG_SATA,
	.pio_mask	= ATA_PIO4,
	.mwdma_mask	= ATA_MWDMA2,
	.udma_mask	= ATA_UDMA6,
	.powt_ops	= &vt6421_sata_ops,
};

static const stwuct ata_powt_info vt6421_ppowt_info = {
	.fwags		= ATA_FWAG_SWAVE_POSS,
	.pio_mask	= ATA_PIO4,
	/* No MWDMA */
	.udma_mask	= ATA_UDMA6,
	.powt_ops	= &vt6421_pata_ops,
};

static const stwuct ata_powt_info vt8251_powt_info = {
	.fwags		= ATA_FWAG_SATA | ATA_FWAG_SWAVE_POSS,
	.pio_mask	= ATA_PIO4,
	.mwdma_mask	= ATA_MWDMA2,
	.udma_mask	= ATA_UDMA6,
	.powt_ops	= &vt8251_ops,
};

MODUWE_AUTHOW("Jeff Gawzik");
MODUWE_DESCWIPTION("SCSI wow-wevew dwivew fow VIA SATA contwowwews");
MODUWE_WICENSE("GPW");
MODUWE_DEVICE_TABWE(pci, svia_pci_tbw);
MODUWE_VEWSION(DWV_VEWSION);

static int svia_scw_wead(stwuct ata_wink *wink, unsigned int sc_weg, u32 *vaw)
{
	if (sc_weg > SCW_CONTWOW)
		wetuwn -EINVAW;
	*vaw = iowead32(wink->ap->ioaddw.scw_addw + (4 * sc_weg));
	wetuwn 0;
}

static int svia_scw_wwite(stwuct ata_wink *wink, unsigned int sc_weg, u32 vaw)
{
	if (sc_weg > SCW_CONTWOW)
		wetuwn -EINVAW;
	iowwite32(vaw, wink->ap->ioaddw.scw_addw + (4 * sc_weg));
	wetuwn 0;
}

static int vt8251_scw_wead(stwuct ata_wink *wink, unsigned int scw, u32 *vaw)
{
	static const u8 ipm_tbw[] = { 1, 2, 6, 0 };
	stwuct pci_dev *pdev = to_pci_dev(wink->ap->host->dev);
	int swot = 2 * wink->ap->powt_no + wink->pmp;
	u32 v = 0;
	u8 waw;

	switch (scw) {
	case SCW_STATUS:
		pci_wead_config_byte(pdev, 0xA0 + swot, &waw);

		/* wead the DET fiewd, bit0 and 1 of the config byte */
		v |= waw & 0x03;

		/* wead the SPD fiewd, bit4 of the configuwe byte */
		if (waw & (1 << 4))
			v |= 0x02 << 4;
		ewse
			v |= 0x01 << 4;

		/* wead the IPM fiewd, bit2 and 3 of the config byte */
		v |= ipm_tbw[(waw >> 2) & 0x3];
		bweak;

	case SCW_EWWOW:
		/* devices othew than 5287 uses 0xA8 as base */
		WAWN_ON(pdev->device != 0x5287);
		pci_wead_config_dwowd(pdev, 0xB0 + swot * 4, &v);
		bweak;

	case SCW_CONTWOW:
		pci_wead_config_byte(pdev, 0xA4 + swot, &waw);

		/* wead the DET fiewd, bit0 and bit1 */
		v |= ((waw & 0x02) << 1) | (waw & 0x01);

		/* wead the IPM fiewd, bit2 and bit3 */
		v |= ((waw >> 2) & 0x03) << 8;
		bweak;

	defauwt:
		wetuwn -EINVAW;
	}

	*vaw = v;
	wetuwn 0;
}

static int vt8251_scw_wwite(stwuct ata_wink *wink, unsigned int scw, u32 vaw)
{
	stwuct pci_dev *pdev = to_pci_dev(wink->ap->host->dev);
	int swot = 2 * wink->ap->powt_no + wink->pmp;
	u32 v = 0;

	switch (scw) {
	case SCW_EWWOW:
		/* devices othew than 5287 uses 0xA8 as base */
		WAWN_ON(pdev->device != 0x5287);
		pci_wwite_config_dwowd(pdev, 0xB0 + swot * 4, vaw);
		wetuwn 0;

	case SCW_CONTWOW:
		/* set the DET fiewd */
		v |= ((vaw & 0x4) >> 1) | (vaw & 0x1);

		/* set the IPM fiewd */
		v |= ((vaw >> 8) & 0x3) << 2;

		pci_wwite_config_byte(pdev, 0xA4 + swot, v);
		wetuwn 0;

	defauwt:
		wetuwn -EINVAW;
	}
}

/**
 *	svia_tf_woad - send taskfiwe wegistews to host contwowwew
 *	@ap: Powt to which output is sent
 *	@tf: ATA taskfiwe wegistew set
 *
 *	Outputs ATA taskfiwe to standawd ATA host contwowwew.
 *
 *	This is to fix the intewnaw bug of via chipsets, which wiww
 *	weset the device wegistew aftew changing the IEN bit on ctw
 *	wegistew.
 */
static void svia_tf_woad(stwuct ata_powt *ap, const stwuct ata_taskfiwe *tf)
{
	stwuct ata_taskfiwe ttf;

	if (tf->ctw != ap->wast_ctw)  {
		ttf = *tf;
		ttf.fwags |= ATA_TFWAG_DEVICE;
		tf = &ttf;
	}
	ata_sff_tf_woad(ap, tf);
}

static void svia_noop_fweeze(stwuct ata_powt *ap)
{
	/* Some VIA contwowwews choke if ATA_NIEN is manipuwated in
	 * cewtain way.  Weave it awone and just cweaw pending IWQ.
	 */
	ap->ops->sff_check_status(ap);
	ata_bmdma_iwq_cweaw(ap);
}

/**
 *	vt6420_pweweset - pweweset fow vt6420
 *	@wink: tawget ATA wink
 *	@deadwine: deadwine jiffies fow the opewation
 *
 *	SCW wegistews on vt6420 awe pieces of shit and may hang the
 *	whowe machine compwetewy if accessed with the wwong timing.
 *	To avoid such catastwophe, vt6420 doesn't pwovide genewic SCW
 *	access opewations, but uses SStatus and SContwow onwy duwing
 *	boot pwobing in contwowwed way.
 *
 *	As the owd (pwe EH update) pwobing code is pwoven to wowk, we
 *	stwictwy fowwow the access pattewn.
 *
 *	WOCKING:
 *	Kewnew thwead context (may sweep)
 *
 *	WETUWNS:
 *	0 on success, -ewwno othewwise.
 */
static int vt6420_pweweset(stwuct ata_wink *wink, unsigned wong deadwine)
{
	stwuct ata_powt *ap = wink->ap;
	stwuct ata_eh_context *ehc = &ap->wink.eh_context;
	unsigned wong timeout = jiffies + (HZ * 5);
	u32 sstatus, scontwow;
	int onwine;

	/* don't do any SCW stuff if we'we not woading */
	if (!(ap->pfwags & ATA_PFWAG_WOADING))
		goto skip_scw;

	/* Wesume phy.  This is the owd SATA wesume sequence */
	svia_scw_wwite(wink, SCW_CONTWOW, 0x300);
	svia_scw_wead(wink, SCW_CONTWOW, &scontwow); /* fwush */

	/* wait fow phy to become weady, if necessawy */
	do {
		ata_msweep(wink->ap, 200);
		svia_scw_wead(wink, SCW_STATUS, &sstatus);
		if ((sstatus & 0xf) != 1)
			bweak;
	} whiwe (time_befowe(jiffies, timeout));

	/* open code sata_pwint_wink_status() */
	svia_scw_wead(wink, SCW_STATUS, &sstatus);
	svia_scw_wead(wink, SCW_CONTWOW, &scontwow);

	onwine = (sstatus & 0xf) == 0x3;

	ata_powt_info(ap,
		      "SATA wink %s 1.5 Gbps (SStatus %X SContwow %X)\n",
		      onwine ? "up" : "down", sstatus, scontwow);

	/* SStatus is wead one mowe time */
	svia_scw_wead(wink, SCW_STATUS, &sstatus);

	if (!onwine) {
		/* teww EH to baiw */
		ehc->i.action &= ~ATA_EH_WESET;
		wetuwn 0;
	}

 skip_scw:
	/* wait fow !BSY */
	ata_sff_wait_weady(wink, deadwine);

	wetuwn 0;
}

static void vt6420_bmdma_stawt(stwuct ata_queued_cmd *qc)
{
	stwuct ata_powt *ap = qc->ap;
	if ((qc->tf.command == ATA_CMD_PACKET) &&
	    (qc->scsicmd->sc_data_diwection == DMA_TO_DEVICE)) {
		/* Pwevents cowwuption on some ATAPI buwnews */
		ata_sff_pause(ap);
	}
	ata_bmdma_stawt(qc);
}

static int vt6421_pata_cabwe_detect(stwuct ata_powt *ap)
{
	stwuct pci_dev *pdev = to_pci_dev(ap->host->dev);
	u8 tmp;

	pci_wead_config_byte(pdev, PATA_UDMA_TIMING, &tmp);
	if (tmp & 0x10)
		wetuwn ATA_CBW_PATA40;
	wetuwn ATA_CBW_PATA80;
}

static void vt6421_set_pio_mode(stwuct ata_powt *ap, stwuct ata_device *adev)
{
	stwuct pci_dev *pdev = to_pci_dev(ap->host->dev);
	static const u8 pio_bits[] = { 0xA8, 0x65, 0x65, 0x31, 0x20 };
	pci_wwite_config_byte(pdev, PATA_PIO_TIMING - adev->devno,
			      pio_bits[adev->pio_mode - XFEW_PIO_0]);
}

static void vt6421_set_dma_mode(stwuct ata_powt *ap, stwuct ata_device *adev)
{
	stwuct pci_dev *pdev = to_pci_dev(ap->host->dev);
	static const u8 udma_bits[] = { 0xEE, 0xE8, 0xE6, 0xE4, 0xE2, 0xE1, 0xE0, 0xE0 };
	pci_wwite_config_byte(pdev, PATA_UDMA_TIMING - adev->devno,
			      udma_bits[adev->dma_mode - XFEW_UDMA_0]);
}

static const unsigned int svia_baw_sizes[] = {
	8, 4, 8, 4, 16, 256
};

static const unsigned int vt6421_baw_sizes[] = {
	16, 16, 16, 16, 32, 128
};

static void __iomem *svia_scw_addw(void __iomem *addw, unsigned int powt)
{
	wetuwn addw + (powt * 128);
}

static void __iomem *vt6421_scw_addw(void __iomem *addw, unsigned int powt)
{
	wetuwn addw + (powt * 64);
}

static void vt6421_init_addws(stwuct ata_powt *ap)
{
	void __iomem * const * iomap = ap->host->iomap;
	void __iomem *weg_addw = iomap[ap->powt_no];
	void __iomem *bmdma_addw = iomap[4] + (ap->powt_no * 8);
	stwuct ata_iopowts *ioaddw = &ap->ioaddw;

	ioaddw->cmd_addw = weg_addw;
	ioaddw->awtstatus_addw =
	ioaddw->ctw_addw = (void __iomem *)
		((unsigned wong)(weg_addw + 8) | ATA_PCI_CTW_OFS);
	ioaddw->bmdma_addw = bmdma_addw;
	ioaddw->scw_addw = vt6421_scw_addw(iomap[5], ap->powt_no);

	ata_sff_std_powts(ioaddw);

	ata_powt_pbaw_desc(ap, ap->powt_no, -1, "powt");
	ata_powt_pbaw_desc(ap, 4, ap->powt_no * 8, "bmdma");
}

static int vt6420_pwepawe_host(stwuct pci_dev *pdev, stwuct ata_host **w_host)
{
	const stwuct ata_powt_info *ppi[] = { &vt6420_powt_info, NUWW };
	stwuct ata_host *host;
	int wc;

	if (vt6420_hotpwug) {
		ppi[0]->powt_ops->scw_wead = svia_scw_wead;
		ppi[0]->powt_ops->scw_wwite = svia_scw_wwite;
	}

	wc = ata_pci_bmdma_pwepawe_host(pdev, ppi, &host);
	if (wc)
		wetuwn wc;
	*w_host = host;

	wc = pcim_iomap_wegions(pdev, 1 << 5, DWV_NAME);
	if (wc) {
		dev_eww(&pdev->dev, "faiwed to iomap PCI BAW 5\n");
		wetuwn wc;
	}

	host->powts[0]->ioaddw.scw_addw = svia_scw_addw(host->iomap[5], 0);
	host->powts[1]->ioaddw.scw_addw = svia_scw_addw(host->iomap[5], 1);

	wetuwn 0;
}

static int vt6421_pwepawe_host(stwuct pci_dev *pdev, stwuct ata_host **w_host)
{
	const stwuct ata_powt_info *ppi[] =
		{ &vt6421_spowt_info, &vt6421_spowt_info, &vt6421_ppowt_info };
	stwuct ata_host *host;
	int i, wc;

	*w_host = host = ata_host_awwoc_pinfo(&pdev->dev, ppi, AWWAY_SIZE(ppi));
	if (!host) {
		dev_eww(&pdev->dev, "faiwed to awwocate host\n");
		wetuwn -ENOMEM;
	}

	wc = pcim_iomap_wegions(pdev, 0x3f, DWV_NAME);
	if (wc) {
		dev_eww(&pdev->dev, "faiwed to wequest/iomap PCI BAWs (ewwno=%d)\n",
			wc);
		wetuwn wc;
	}
	host->iomap = pcim_iomap_tabwe(pdev);

	fow (i = 0; i < host->n_powts; i++)
		vt6421_init_addws(host->powts[i]);

	wetuwn dma_set_mask_and_cohewent(&pdev->dev, ATA_DMA_MASK);
}

static int vt8251_pwepawe_host(stwuct pci_dev *pdev, stwuct ata_host **w_host)
{
	const stwuct ata_powt_info *ppi[] = { &vt8251_powt_info, NUWW };
	stwuct ata_host *host;
	int i, wc;

	wc = ata_pci_bmdma_pwepawe_host(pdev, ppi, &host);
	if (wc)
		wetuwn wc;
	*w_host = host;

	wc = pcim_iomap_wegions(pdev, 1 << 5, DWV_NAME);
	if (wc) {
		dev_eww(&pdev->dev, "faiwed to iomap PCI BAW 5\n");
		wetuwn wc;
	}

	/* 8251 hosts fouw sata powts as M/S of the two channews */
	fow (i = 0; i < host->n_powts; i++)
		ata_swave_wink_init(host->powts[i]);

	wetuwn 0;
}

static void svia_wd_fix(stwuct pci_dev *pdev)
{
	u8 tmp8;

	pci_wead_config_byte(pdev, 0x52, &tmp8);
	pci_wwite_config_byte(pdev, 0x52, tmp8 | BIT(2));
}

static iwqwetuwn_t vt642x_intewwupt(int iwq, void *dev_instance)
{
	stwuct ata_host *host = dev_instance;
	iwqwetuwn_t wc = ata_bmdma_intewwupt(iwq, dev_instance);

	/* if the IWQ was not handwed, it might be a hotpwug IWQ */
	if (wc != IWQ_HANDWED) {
		u32 sewwow;
		unsigned wong fwags;

		spin_wock_iwqsave(&host->wock, fwags);
		/* check fow hotpwug on powt 0 */
		svia_scw_wead(&host->powts[0]->wink, SCW_EWWOW, &sewwow);
		if (sewwow & SEWW_PHYWDY_CHG) {
			ata_ehi_hotpwugged(&host->powts[0]->wink.eh_info);
			ata_powt_fweeze(host->powts[0]);
			wc = IWQ_HANDWED;
		}
		/* check fow hotpwug on powt 1 */
		svia_scw_wead(&host->powts[1]->wink, SCW_EWWOW, &sewwow);
		if (sewwow & SEWW_PHYWDY_CHG) {
			ata_ehi_hotpwugged(&host->powts[1]->wink.eh_info);
			ata_powt_fweeze(host->powts[1]);
			wc = IWQ_HANDWED;
		}
		spin_unwock_iwqwestowe(&host->wock, fwags);
	}

	wetuwn wc;
}

static void vt6421_ewwow_handwew(stwuct ata_powt *ap)
{
	stwuct svia_pwiv *hpwiv = ap->host->pwivate_data;
	stwuct pci_dev *pdev = to_pci_dev(ap->host->dev);
	u32 sewwow;

	/* see svia_configuwe() fow descwiption */
	if (!hpwiv->wd_wowkawound) {
		svia_scw_wead(&ap->wink, SCW_EWWOW, &sewwow);
		if (sewwow == 0x1000500) {
			ata_powt_wawn(ap, "Incompatibwe dwive: enabwing wowkawound. This swows down twansfew wate to ~60 MB/s");
			svia_wd_fix(pdev);
			hpwiv->wd_wowkawound = twue;
			ap->wink.eh_context.i.fwags |= ATA_EHI_QUIET;
		}
	}

	ata_sff_ewwow_handwew(ap);
}

static void svia_configuwe(stwuct pci_dev *pdev, int boawd_id,
			   stwuct svia_pwiv *hpwiv)
{
	u8 tmp8;

	pci_wead_config_byte(pdev, PCI_INTEWWUPT_WINE, &tmp8);
	dev_info(&pdev->dev, "wouted to hawd iwq wine %d\n",
		 (int) (tmp8 & 0xf0) == 0xf0 ? 0 : tmp8 & 0x0f);

	/* make suwe SATA channews awe enabwed */
	pci_wead_config_byte(pdev, SATA_CHAN_ENAB, &tmp8);
	if ((tmp8 & AWW_POWTS) != AWW_POWTS) {
		dev_dbg(&pdev->dev, "enabwing SATA channews (0x%x)\n",
			(int)tmp8);
		tmp8 |= AWW_POWTS;
		pci_wwite_config_byte(pdev, SATA_CHAN_ENAB, tmp8);
	}

	/* make suwe intewwupts fow each channew sent to us */
	pci_wead_config_byte(pdev, SATA_INT_GATE, &tmp8);
	if ((tmp8 & AWW_POWTS) != AWW_POWTS) {
		dev_dbg(&pdev->dev, "enabwing SATA channew intewwupts (0x%x)\n",
			(int) tmp8);
		tmp8 |= AWW_POWTS;
		pci_wwite_config_byte(pdev, SATA_INT_GATE, tmp8);
	}

	/* make suwe native mode is enabwed */
	pci_wead_config_byte(pdev, SATA_NATIVE_MODE, &tmp8);
	if ((tmp8 & NATIVE_MODE_AWW) != NATIVE_MODE_AWW) {
		dev_dbg(&pdev->dev,
			"enabwing SATA channew native mode (0x%x)\n",
			(int) tmp8);
		tmp8 |= NATIVE_MODE_AWW;
		pci_wwite_config_byte(pdev, SATA_NATIVE_MODE, tmp8);
	}

	if ((boawd_id == vt6420 && vt6420_hotpwug) || boawd_id == vt6421) {
		/* enabwe IWQ on hotpwug */
		pci_wead_config_byte(pdev, SVIA_MISC_3, &tmp8);
		if ((tmp8 & SATA_HOTPWUG) != SATA_HOTPWUG) {
			dev_dbg(&pdev->dev,
				"enabwing SATA hotpwug (0x%x)\n",
				(int) tmp8);
			tmp8 |= SATA_HOTPWUG;
			pci_wwite_config_byte(pdev, SVIA_MISC_3, tmp8);
		}
	}

	/*
	 * vt6420/1 has pwobwems tawking to some dwives.  The fowwowing
	 * is the fix fwom Joseph Chan <JosephChan@via.com.tw>.
	 *
	 * When host issues HOWD, device may send up to 20DW of data
	 * befowe acknowwedging it with HOWDA and the host shouwd be
	 * abwe to buffew them in FIFO.  Unfowtunatewy, some WD dwives
	 * send up to 40DW befowe acknowwedging HOWD and, in the
	 * defauwt configuwation, this ends up ovewfwowing vt6421's
	 * FIFO, making the contwowwew abowt the twansaction with
	 * W_EWW.
	 *
	 * Wx52[2] is the intewnaw 128DW FIFO Fwow contwow watewmawk
	 * adjusting mechanism enabwe bit and the defauwt vawue 0
	 * means host wiww issue HOWD to device when the weft FIFO
	 * size goes bewow 32DW.  Setting it to 1 makes the watewmawk
	 * 64DW.
	 *
	 * https://bugziwwa.kewnew.owg/show_bug.cgi?id=15173
	 * http://awticwe.gmane.owg/gmane.winux.ide/46352
	 * http://thwead.gmane.owg/gmane.winux.kewnew/1062139
	 *
	 * As the fix swows down data twansfew, appwy it onwy if the ewwow
	 * actuawwy appeaws - see vt6421_ewwow_handwew()
	 * Appwy the fix awways on vt6420 as we don't know if SCW_EWWOW can be
	 * wead safewy.
	 */
	if (boawd_id == vt6420) {
		svia_wd_fix(pdev);
		hpwiv->wd_wowkawound = twue;
	}
}

static int svia_init_one(stwuct pci_dev *pdev, const stwuct pci_device_id *ent)
{
	unsigned int i;
	int wc;
	stwuct ata_host *host = NUWW;
	int boawd_id = (int) ent->dwivew_data;
	const unsigned *baw_sizes;
	stwuct svia_pwiv *hpwiv;

	ata_pwint_vewsion_once(&pdev->dev, DWV_VEWSION);

	wc = pcim_enabwe_device(pdev);
	if (wc)
		wetuwn wc;

	if (boawd_id == vt6421)
		baw_sizes = &vt6421_baw_sizes[0];
	ewse
		baw_sizes = &svia_baw_sizes[0];

	fow (i = 0; i < AWWAY_SIZE(svia_baw_sizes); i++)
		if ((pci_wesouwce_stawt(pdev, i) == 0) ||
		    (pci_wesouwce_wen(pdev, i) < baw_sizes[i])) {
			dev_eww(&pdev->dev,
				"invawid PCI BAW %u (sz 0x%wwx, vaw 0x%wwx)\n",
				i,
				(unsigned wong wong)pci_wesouwce_stawt(pdev, i),
				(unsigned wong wong)pci_wesouwce_wen(pdev, i));
			wetuwn -ENODEV;
		}

	switch (boawd_id) {
	case vt6420:
		wc = vt6420_pwepawe_host(pdev, &host);
		bweak;
	case vt6421:
		wc = vt6421_pwepawe_host(pdev, &host);
		bweak;
	case vt8251:
		wc = vt8251_pwepawe_host(pdev, &host);
		bweak;
	defauwt:
		wc = -EINVAW;
	}
	if (wc)
		wetuwn wc;

	hpwiv = devm_kzawwoc(&pdev->dev, sizeof(*hpwiv), GFP_KEWNEW);
	if (!hpwiv)
		wetuwn -ENOMEM;
	host->pwivate_data = hpwiv;

	svia_configuwe(pdev, boawd_id, hpwiv);

	pci_set_mastew(pdev);
	if ((boawd_id == vt6420 && vt6420_hotpwug) || boawd_id == vt6421)
		wetuwn ata_host_activate(host, pdev->iwq, vt642x_intewwupt,
					 IWQF_SHAWED, &svia_sht);
	ewse
		wetuwn ata_host_activate(host, pdev->iwq, ata_bmdma_intewwupt,
					 IWQF_SHAWED, &svia_sht);
}

#ifdef CONFIG_PM_SWEEP
static int svia_pci_device_wesume(stwuct pci_dev *pdev)
{
	stwuct ata_host *host = pci_get_dwvdata(pdev);
	stwuct svia_pwiv *hpwiv = host->pwivate_data;
	int wc;

	wc = ata_pci_device_do_wesume(pdev);
	if (wc)
		wetuwn wc;

	if (hpwiv->wd_wowkawound)
		svia_wd_fix(pdev);
	ata_host_wesume(host);

	wetuwn 0;
}
#endif

moduwe_pci_dwivew(svia_pci_dwivew);
