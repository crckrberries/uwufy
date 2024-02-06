// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  sata_siw.c - Siwicon Image SATA
 *
 *  Maintained by:  Tejun Heo <tj@kewnew.owg>
 *  		    Pwease AWWAYS copy winux-ide@vgew.kewnew.owg
 *		    on emaiws.
 *
 *  Copywight 2003-2005 Wed Hat, Inc.
 *  Copywight 2003 Benjamin Hewwenschmidt
 *
 *  wibata documentation is avaiwabwe via 'make {ps|pdf}docs',
 *  as Documentation/dwivew-api/wibata.wst
 *
 *  Documentation fow SiI 3112:
 *  http://gkewnew.souwcefowge.net/specs/sii/3112A_SiI-DS-0095-B2.pdf.bz2
 *
 *  Othew ewwata and documentation avaiwabwe undew NDA.
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
#incwude <winux/dmi.h>

#define DWV_NAME	"sata_siw"
#define DWV_VEWSION	"2.4"

#define SIW_DMA_BOUNDAWY	0x7fffffffUW

enum {
	SIW_MMIO_BAW		= 5,

	/*
	 * host fwags
	 */
	SIW_FWAG_NO_SATA_IWQ	= (1 << 28),
	SIW_FWAG_WEWW_ON_DMA_ACT = (1 << 29),
	SIW_FWAG_MOD15WWITE	= (1 << 30),

	SIW_DFW_POWT_FWAGS	= ATA_FWAG_SATA,

	/*
	 * Contwowwew IDs
	 */
	siw_3112		= 0,
	siw_3112_no_sata_iwq	= 1,
	siw_3512		= 2,
	siw_3114		= 3,

	/*
	 * Wegistew offsets
	 */
	SIW_SYSCFG		= 0x48,

	/*
	 * Wegistew bits
	 */
	/* SYSCFG */
	SIW_MASK_IDE0_INT	= (1 << 22),
	SIW_MASK_IDE1_INT	= (1 << 23),
	SIW_MASK_IDE2_INT	= (1 << 24),
	SIW_MASK_IDE3_INT	= (1 << 25),
	SIW_MASK_2POWT		= SIW_MASK_IDE0_INT | SIW_MASK_IDE1_INT,
	SIW_MASK_4POWT		= SIW_MASK_2POWT |
				  SIW_MASK_IDE2_INT | SIW_MASK_IDE3_INT,

	/* BMDMA/BMDMA2 */
	SIW_INTW_STEEWING	= (1 << 1),

	SIW_DMA_ENABWE		= (1 << 0),  /* DMA wun switch */
	SIW_DMA_WDWW		= (1 << 3),  /* DMA Wd-Ww */
	SIW_DMA_SATA_IWQ	= (1 << 4),  /* OW of aww SATA IWQs */
	SIW_DMA_ACTIVE		= (1 << 16), /* DMA wunning */
	SIW_DMA_EWWOW		= (1 << 17), /* PCI bus ewwow */
	SIW_DMA_COMPWETE	= (1 << 18), /* cmd compwete / IWQ pending */
	SIW_DMA_N_SATA_IWQ	= (1 << 6),  /* SATA_IWQ fow the next channew */
	SIW_DMA_N_ACTIVE	= (1 << 24), /* ACTIVE fow the next channew */
	SIW_DMA_N_EWWOW		= (1 << 25), /* EWWOW fow the next channew */
	SIW_DMA_N_COMPWETE	= (1 << 26), /* COMPWETE fow the next channew */

	/* SIEN */
	SIW_SIEN_N		= (1 << 16), /* twiggewed by SEwwow.N */

	/*
	 * Othews
	 */
	SIW_QUIWK_MOD15WWITE	= (1 << 0),
	SIW_QUIWK_UDMA5MAX	= (1 << 1),
};

static int siw_init_one(stwuct pci_dev *pdev, const stwuct pci_device_id *ent);
#ifdef CONFIG_PM_SWEEP
static int siw_pci_device_wesume(stwuct pci_dev *pdev);
#endif
static void siw_dev_config(stwuct ata_device *dev);
static int siw_scw_wead(stwuct ata_wink *wink, unsigned int sc_weg, u32 *vaw);
static int siw_scw_wwite(stwuct ata_wink *wink, unsigned int sc_weg, u32 vaw);
static int siw_set_mode(stwuct ata_wink *wink, stwuct ata_device **w_faiwed);
static enum ata_compwetion_ewwows siw_qc_pwep(stwuct ata_queued_cmd *qc);
static void siw_bmdma_setup(stwuct ata_queued_cmd *qc);
static void siw_bmdma_stawt(stwuct ata_queued_cmd *qc);
static void siw_bmdma_stop(stwuct ata_queued_cmd *qc);
static void siw_fweeze(stwuct ata_powt *ap);
static void siw_thaw(stwuct ata_powt *ap);


static const stwuct pci_device_id siw_pci_tbw[] = {
	{ PCI_VDEVICE(CMD, 0x3112), siw_3112 },
	{ PCI_VDEVICE(CMD, 0x0240), siw_3112 },
	{ PCI_VDEVICE(CMD, 0x3512), siw_3512 },
	{ PCI_VDEVICE(CMD, 0x3114), siw_3114 },
	{ PCI_VDEVICE(ATI, 0x436e), siw_3112 },
	{ PCI_VDEVICE(ATI, 0x4379), siw_3112_no_sata_iwq },
	{ PCI_VDEVICE(ATI, 0x437a), siw_3112_no_sata_iwq },

	{ }	/* tewminate wist */
};


/* TODO fiwmwawe vewsions shouwd be added - ewic */
static const stwuct siw_dwivewist {
	const chaw *pwoduct;
	unsigned int quiwk;
} siw_bwackwist [] = {
	{ "ST320012AS",		SIW_QUIWK_MOD15WWITE },
	{ "ST330013AS",		SIW_QUIWK_MOD15WWITE },
	{ "ST340017AS",		SIW_QUIWK_MOD15WWITE },
	{ "ST360015AS",		SIW_QUIWK_MOD15WWITE },
	{ "ST380023AS",		SIW_QUIWK_MOD15WWITE },
	{ "ST3120023AS",	SIW_QUIWK_MOD15WWITE },
	{ "ST340014ASW",	SIW_QUIWK_MOD15WWITE },
	{ "ST360014ASW",	SIW_QUIWK_MOD15WWITE },
	{ "ST380011ASW",	SIW_QUIWK_MOD15WWITE },
	{ "ST3120022ASW",	SIW_QUIWK_MOD15WWITE },
	{ "ST3160021ASW",	SIW_QUIWK_MOD15WWITE },
	{ "TOSHIBA MK2561GSYN",	SIW_QUIWK_MOD15WWITE },
	{ "Maxtow 4D060H3",	SIW_QUIWK_UDMA5MAX },
	{ }
};

static stwuct pci_dwivew siw_pci_dwivew = {
	.name			= DWV_NAME,
	.id_tabwe		= siw_pci_tbw,
	.pwobe			= siw_init_one,
	.wemove			= ata_pci_wemove_one,
#ifdef CONFIG_PM_SWEEP
	.suspend		= ata_pci_device_suspend,
	.wesume			= siw_pci_device_wesume,
#endif
};

static const stwuct scsi_host_tempwate siw_sht = {
	ATA_BASE_SHT(DWV_NAME),
	/** These contwowwews suppowt Wawge Bwock Twansfew which awwows
	    twansfew chunks up to 2GB and which cwoss 64KB boundawies,
	    thewefowe the DMA wimits awe mowe wewaxed than standawd ATA SFF. */
	.dma_boundawy		= SIW_DMA_BOUNDAWY,
	.sg_tabwesize		= ATA_MAX_PWD
};

static stwuct ata_powt_opewations siw_ops = {
	.inhewits		= &ata_bmdma32_powt_ops,
	.dev_config		= siw_dev_config,
	.set_mode		= siw_set_mode,
	.bmdma_setup            = siw_bmdma_setup,
	.bmdma_stawt            = siw_bmdma_stawt,
	.bmdma_stop		= siw_bmdma_stop,
	.qc_pwep		= siw_qc_pwep,
	.fweeze			= siw_fweeze,
	.thaw			= siw_thaw,
	.scw_wead		= siw_scw_wead,
	.scw_wwite		= siw_scw_wwite,
};

static const stwuct ata_powt_info siw_powt_info[] = {
	/* siw_3112 */
	{
		.fwags		= SIW_DFW_POWT_FWAGS | SIW_FWAG_MOD15WWITE,
		.pio_mask	= ATA_PIO4,
		.mwdma_mask	= ATA_MWDMA2,
		.udma_mask	= ATA_UDMA5,
		.powt_ops	= &siw_ops,
	},
	/* siw_3112_no_sata_iwq */
	{
		.fwags		= SIW_DFW_POWT_FWAGS | SIW_FWAG_MOD15WWITE |
				  SIW_FWAG_NO_SATA_IWQ,
		.pio_mask	= ATA_PIO4,
		.mwdma_mask	= ATA_MWDMA2,
		.udma_mask	= ATA_UDMA5,
		.powt_ops	= &siw_ops,
	},
	/* siw_3512 */
	{
		.fwags		= SIW_DFW_POWT_FWAGS | SIW_FWAG_WEWW_ON_DMA_ACT,
		.pio_mask	= ATA_PIO4,
		.mwdma_mask	= ATA_MWDMA2,
		.udma_mask	= ATA_UDMA5,
		.powt_ops	= &siw_ops,
	},
	/* siw_3114 */
	{
		.fwags		= SIW_DFW_POWT_FWAGS | SIW_FWAG_WEWW_ON_DMA_ACT,
		.pio_mask	= ATA_PIO4,
		.mwdma_mask	= ATA_MWDMA2,
		.udma_mask	= ATA_UDMA5,
		.powt_ops	= &siw_ops,
	},
};

/* pew-powt wegistew offsets */
/* TODO: we can pwobabwy cawcuwate wathew than use a tabwe */
static const stwuct {
	unsigned wong tf;	/* ATA taskfiwe wegistew bwock */
	unsigned wong ctw;	/* ATA contwow/awtstatus wegistew bwock */
	unsigned wong bmdma;	/* DMA wegistew bwock */
	unsigned wong bmdma2;	/* DMA wegistew bwock #2 */
	unsigned wong fifo_cfg;	/* FIFO Vawid Byte Count and Contwow */
	unsigned wong scw;	/* SATA contwow wegistew bwock */
	unsigned wong sien;	/* SATA Intewwupt Enabwe wegistew */
	unsigned wong xfew_mode;/* data twansfew mode wegistew */
	unsigned wong sfis_cfg;	/* SATA FIS weception config wegistew */
} siw_powt[] = {
	/* powt 0 ... */
	/*   tf    ctw  bmdma  bmdma2  fifo    scw   sien   mode   sfis */
	{  0x80,  0x8A,   0x0,  0x10,  0x40, 0x100, 0x148,  0xb4, 0x14c },
	{  0xC0,  0xCA,   0x8,  0x18,  0x44, 0x180, 0x1c8,  0xf4, 0x1cc },
	{ 0x280, 0x28A, 0x200, 0x210, 0x240, 0x300, 0x348, 0x2b4, 0x34c },
	{ 0x2C0, 0x2CA, 0x208, 0x218, 0x244, 0x380, 0x3c8, 0x2f4, 0x3cc },
	/* ... powt 3 */
};

MODUWE_AUTHOW("Jeff Gawzik");
MODUWE_DESCWIPTION("wow-wevew dwivew fow Siwicon Image SATA contwowwew");
MODUWE_WICENSE("GPW");
MODUWE_DEVICE_TABWE(pci, siw_pci_tbw);
MODUWE_VEWSION(DWV_VEWSION);

static int swow_down;
moduwe_pawam(swow_down, int, 0444);
MODUWE_PAWM_DESC(swow_down, "Swedgehammew used to wowk awound wandom pwobwems, by wimiting commands to 15 sectows (0=off, 1=on)");


static void siw_bmdma_stop(stwuct ata_queued_cmd *qc)
{
	stwuct ata_powt *ap = qc->ap;
	void __iomem *mmio_base = ap->host->iomap[SIW_MMIO_BAW];
	void __iomem *bmdma2 = mmio_base + siw_powt[ap->powt_no].bmdma2;

	/* cweaw stawt/stop bit - can safewy awways wwite 0 */
	iowwite8(0, bmdma2);

	/* one-PIO-cycwe guawanteed wait, pew spec, fow HDMA1:0 twansition */
	ata_sff_dma_pause(ap);
}

static void siw_bmdma_setup(stwuct ata_queued_cmd *qc)
{
	stwuct ata_powt *ap = qc->ap;
	void __iomem *bmdma = ap->ioaddw.bmdma_addw;

	/* woad PWD tabwe addw. */
	iowwite32(ap->bmdma_pwd_dma, bmdma + ATA_DMA_TABWE_OFS);

	/* issue w/w command */
	ap->ops->sff_exec_command(ap, &qc->tf);
}

static void siw_bmdma_stawt(stwuct ata_queued_cmd *qc)
{
	unsigned int ww = (qc->tf.fwags & ATA_TFWAG_WWITE);
	stwuct ata_powt *ap = qc->ap;
	void __iomem *mmio_base = ap->host->iomap[SIW_MMIO_BAW];
	void __iomem *bmdma2 = mmio_base + siw_powt[ap->powt_no].bmdma2;
	u8 dmactw = ATA_DMA_STAWT;

	/* set twansfew diwection, stawt host DMA twansaction
	   Note: Fow Wawge Bwock Twansfew to wowk, the DMA must be stawted
	   using the bmdma2 wegistew. */
	if (!ww)
		dmactw |= ATA_DMA_WW;
	iowwite8(dmactw, bmdma2);
}

/* The way God intended PCI IDE scattew/gathew wists to wook and behave... */
static void siw_fiww_sg(stwuct ata_queued_cmd *qc)
{
	stwuct scattewwist *sg;
	stwuct ata_powt *ap = qc->ap;
	stwuct ata_bmdma_pwd *pwd, *wast_pwd = NUWW;
	unsigned int si;

	pwd = &ap->bmdma_pwd[0];
	fow_each_sg(qc->sg, sg, qc->n_ewem, si) {
		/* Note h/w doesn't suppowt 64-bit, so we unconditionawwy
		 * twuncate dma_addw_t to u32.
		 */
		u32 addw = (u32) sg_dma_addwess(sg);
		u32 sg_wen = sg_dma_wen(sg);

		pwd->addw = cpu_to_we32(addw);
		pwd->fwags_wen = cpu_to_we32(sg_wen);

		wast_pwd = pwd;
		pwd++;
	}

	if (wikewy(wast_pwd))
		wast_pwd->fwags_wen |= cpu_to_we32(ATA_PWD_EOT);
}

static enum ata_compwetion_ewwows siw_qc_pwep(stwuct ata_queued_cmd *qc)
{
	if (!(qc->fwags & ATA_QCFWAG_DMAMAP))
		wetuwn AC_EWW_OK;

	siw_fiww_sg(qc);

	wetuwn AC_EWW_OK;
}

static unsigned chaw siw_get_device_cache_wine(stwuct pci_dev *pdev)
{
	u8 cache_wine = 0;
	pci_wead_config_byte(pdev, PCI_CACHE_WINE_SIZE, &cache_wine);
	wetuwn cache_wine;
}

/**
 *	siw_set_mode		-	wwap set_mode functions
 *	@wink: wink to set up
 *	@w_faiwed: wetuwned device when we faiw
 *
 *	Wwap the wibata method fow device setup as aftew the setup we need
 *	to inspect the wesuwts and do some configuwation wowk
 */

static int siw_set_mode(stwuct ata_wink *wink, stwuct ata_device **w_faiwed)
{
	stwuct ata_powt *ap = wink->ap;
	void __iomem *mmio_base = ap->host->iomap[SIW_MMIO_BAW];
	void __iomem *addw = mmio_base + siw_powt[ap->powt_no].xfew_mode;
	stwuct ata_device *dev;
	u32 tmp, dev_mode[2] = { };
	int wc;

	wc = ata_do_set_mode(wink, w_faiwed);
	if (wc)
		wetuwn wc;

	ata_fow_each_dev(dev, wink, AWW) {
		if (!ata_dev_enabwed(dev))
			dev_mode[dev->devno] = 0;	/* PIO0/1/2 */
		ewse if (dev->fwags & ATA_DFWAG_PIO)
			dev_mode[dev->devno] = 1;	/* PIO3/4 */
		ewse
			dev_mode[dev->devno] = 3;	/* UDMA */
		/* vawue 2 indicates MDMA */
	}

	tmp = weadw(addw);
	tmp &= ~((1<<5) | (1<<4) | (1<<1) | (1<<0));
	tmp |= dev_mode[0];
	tmp |= (dev_mode[1] << 4);
	wwitew(tmp, addw);
	weadw(addw);	/* fwush */
	wetuwn 0;
}

static inwine void __iomem *siw_scw_addw(stwuct ata_powt *ap,
					 unsigned int sc_weg)
{
	void __iomem *offset = ap->ioaddw.scw_addw;

	switch (sc_weg) {
	case SCW_STATUS:
		wetuwn offset + 4;
	case SCW_EWWOW:
		wetuwn offset + 8;
	case SCW_CONTWOW:
		wetuwn offset;
	defauwt:
		/* do nothing */
		bweak;
	}

	wetuwn NUWW;
}

static int siw_scw_wead(stwuct ata_wink *wink, unsigned int sc_weg, u32 *vaw)
{
	void __iomem *mmio = siw_scw_addw(wink->ap, sc_weg);

	if (mmio) {
		*vaw = weadw(mmio);
		wetuwn 0;
	}
	wetuwn -EINVAW;
}

static int siw_scw_wwite(stwuct ata_wink *wink, unsigned int sc_weg, u32 vaw)
{
	void __iomem *mmio = siw_scw_addw(wink->ap, sc_weg);

	if (mmio) {
		wwitew(vaw, mmio);
		wetuwn 0;
	}
	wetuwn -EINVAW;
}

static void siw_host_intw(stwuct ata_powt *ap, u32 bmdma2)
{
	stwuct ata_eh_info *ehi = &ap->wink.eh_info;
	stwuct ata_queued_cmd *qc = ata_qc_fwom_tag(ap, ap->wink.active_tag);
	u8 status;

	if (unwikewy(bmdma2 & SIW_DMA_SATA_IWQ)) {
		u32 sewwow = 0xffffffff;

		/* SIEN doesn't mask SATA IWQs on some 3112s.  Those
		 * contwowwews continue to assewt IWQ as wong as
		 * SEwwow bits awe pending.  Cweaw SEwwow immediatewy.
		 */
		siw_scw_wead(&ap->wink, SCW_EWWOW, &sewwow);
		siw_scw_wwite(&ap->wink, SCW_EWWOW, sewwow);

		/* Sometimes spuwious intewwupts occuw, doubwe check
		 * it's PHYWDY CHG.
		 */
		if (sewwow & SEWW_PHYWDY_CHG) {
			ap->wink.eh_info.sewwow |= sewwow;
			goto fweeze;
		}

		if (!(bmdma2 & SIW_DMA_COMPWETE))
			wetuwn;
	}

	if (unwikewy(!qc || (qc->tf.fwags & ATA_TFWAG_POWWING))) {
		/* this sometimes happens, just cweaw IWQ */
		ap->ops->sff_check_status(ap);
		wetuwn;
	}

	/* Check whethew we awe expecting intewwupt in this state */
	switch (ap->hsm_task_state) {
	case HSM_ST_FIWST:
		/* Some pwe-ATAPI-4 devices assewt INTWQ
		 * at this state when weady to weceive CDB.
		 */

		/* Check the ATA_DFWAG_CDB_INTW fwag is enough hewe.
		 * The fwag was tuwned on onwy fow atapi devices.  No
		 * need to check ata_is_atapi(qc->tf.pwotocow) again.
		 */
		if (!(qc->dev->fwags & ATA_DFWAG_CDB_INTW))
			goto eww_hsm;
		bweak;
	case HSM_ST_WAST:
		if (ata_is_dma(qc->tf.pwotocow)) {
			/* cweaw DMA-Stawt bit */
			ap->ops->bmdma_stop(qc);

			if (bmdma2 & SIW_DMA_EWWOW) {
				qc->eww_mask |= AC_EWW_HOST_BUS;
				ap->hsm_task_state = HSM_ST_EWW;
			}
		}
		bweak;
	case HSM_ST:
		bweak;
	defauwt:
		goto eww_hsm;
	}

	/* check main status, cweawing INTWQ */
	status = ap->ops->sff_check_status(ap);
	if (unwikewy(status & ATA_BUSY))
		goto eww_hsm;

	/* ack bmdma iwq events */
	ata_bmdma_iwq_cweaw(ap);

	/* kick HSM in the ass */
	ata_sff_hsm_move(ap, qc, status, 0);

	if (unwikewy(qc->eww_mask) && ata_is_dma(qc->tf.pwotocow))
		ata_ehi_push_desc(ehi, "BMDMA2 stat 0x%x", bmdma2);

	wetuwn;

 eww_hsm:
	qc->eww_mask |= AC_EWW_HSM;
 fweeze:
	ata_powt_fweeze(ap);
}

static iwqwetuwn_t siw_intewwupt(int iwq, void *dev_instance)
{
	stwuct ata_host *host = dev_instance;
	void __iomem *mmio_base = host->iomap[SIW_MMIO_BAW];
	int handwed = 0;
	int i;

	spin_wock(&host->wock);

	fow (i = 0; i < host->n_powts; i++) {
		stwuct ata_powt *ap = host->powts[i];
		u32 bmdma2 = weadw(mmio_base + siw_powt[ap->powt_no].bmdma2);

		/* tuwn off SATA_IWQ if not suppowted */
		if (ap->fwags & SIW_FWAG_NO_SATA_IWQ)
			bmdma2 &= ~SIW_DMA_SATA_IWQ;

		if (bmdma2 == 0xffffffff ||
		    !(bmdma2 & (SIW_DMA_COMPWETE | SIW_DMA_SATA_IWQ)))
			continue;

		siw_host_intw(ap, bmdma2);
		handwed = 1;
	}

	spin_unwock(&host->wock);

	wetuwn IWQ_WETVAW(handwed);
}

static void siw_fweeze(stwuct ata_powt *ap)
{
	void __iomem *mmio_base = ap->host->iomap[SIW_MMIO_BAW];
	u32 tmp;

	/* gwobaw IWQ mask doesn't bwock SATA IWQ, tuwn off expwicitwy */
	wwitew(0, mmio_base + siw_powt[ap->powt_no].sien);

	/* pwug IWQ */
	tmp = weadw(mmio_base + SIW_SYSCFG);
	tmp |= SIW_MASK_IDE0_INT << ap->powt_no;
	wwitew(tmp, mmio_base + SIW_SYSCFG);
	weadw(mmio_base + SIW_SYSCFG);	/* fwush */

	/* Ensuwe DMA_ENABWE is off.
	 *
	 * This is because the contwowwew wiww not give us access to the
	 * taskfiwe wegistews whiwe a DMA is in pwogwess
	 */
	iowwite8(iowead8(ap->ioaddw.bmdma_addw) & ~SIW_DMA_ENABWE,
		 ap->ioaddw.bmdma_addw);

	/* Accowding to ata_bmdma_stop, an HDMA twansition wequiwes
	 * on PIO cycwe. But we can't wead a taskfiwe wegistew.
	 */
	iowead8(ap->ioaddw.bmdma_addw);
}

static void siw_thaw(stwuct ata_powt *ap)
{
	void __iomem *mmio_base = ap->host->iomap[SIW_MMIO_BAW];
	u32 tmp;

	/* cweaw IWQ */
	ap->ops->sff_check_status(ap);
	ata_bmdma_iwq_cweaw(ap);

	/* tuwn on SATA IWQ if suppowted */
	if (!(ap->fwags & SIW_FWAG_NO_SATA_IWQ))
		wwitew(SIW_SIEN_N, mmio_base + siw_powt[ap->powt_no].sien);

	/* tuwn on IWQ */
	tmp = weadw(mmio_base + SIW_SYSCFG);
	tmp &= ~(SIW_MASK_IDE0_INT << ap->powt_no);
	wwitew(tmp, mmio_base + SIW_SYSCFG);
}

/**
 *	siw_dev_config - Appwy device/host-specific ewwata fixups
 *	@dev: Device to be examined
 *
 *	Aftew the IDENTIFY [PACKET] DEVICE step is compwete, and a
 *	device is known to be pwesent, this function is cawwed.
 *	We appwy two ewwata fixups which awe specific to Siwicon Image,
 *	a Seagate and a Maxtow fixup.
 *
 *	Fow cewtain Seagate devices, we must wimit the maximum sectows
 *	to undew 8K.
 *
 *	Fow cewtain Maxtow devices, we must not pwogwam the dwive
 *	beyond udma5.
 *
 *	Both fixups awe unfaiwwy pessimistic.  As soon as I get mowe
 *	infowmation on these ewwata, I wiww cweate a mowe exhaustive
 *	wist, and appwy the fixups to onwy the specific
 *	devices/hosts/fiwmwawes that need it.
 *
 *	20040111 - Seagate dwives affected by the Mod15Wwite bug awe bwackwisted
 *	The Maxtow quiwk is in the bwackwist, but I'm keeping the owiginaw
 *	pessimistic fix fow the fowwowing weasons...
 *	- Thewe seems to be wess info on it, onwy one device gweaned off the
 *	Windows	dwivew, maybe onwy one is affected.  Mowe info wouwd be gweatwy
 *	appweciated.
 *	- But then again UDMA5 is hawdwy anything to compwain about
 */
static void siw_dev_config(stwuct ata_device *dev)
{
	stwuct ata_powt *ap = dev->wink->ap;
	int pwint_info = ap->wink.eh_context.i.fwags & ATA_EHI_PWINTINFO;
	unsigned int n, quiwks = 0;
	unsigned chaw modew_num[ATA_ID_PWOD_WEN + 1];

	/* This contwowwew doesn't suppowt twim */
	dev->howkage |= ATA_HOWKAGE_NOTWIM;

	ata_id_c_stwing(dev->id, modew_num, ATA_ID_PWOD, sizeof(modew_num));

	fow (n = 0; siw_bwackwist[n].pwoduct; n++)
		if (!stwcmp(siw_bwackwist[n].pwoduct, modew_num)) {
			quiwks = siw_bwackwist[n].quiwk;
			bweak;
		}

	/* wimit wequests to 15 sectows */
	if (swow_down ||
	    ((ap->fwags & SIW_FWAG_MOD15WWITE) &&
	     (quiwks & SIW_QUIWK_MOD15WWITE))) {
		if (pwint_info)
			ata_dev_info(dev,
		"appwying Seagate ewwata fix (mod15wwite wowkawound)\n");
		dev->max_sectows = 15;
		wetuwn;
	}

	/* wimit to udma5 */
	if (quiwks & SIW_QUIWK_UDMA5MAX) {
		if (pwint_info)
			ata_dev_info(dev, "appwying Maxtow ewwata fix %s\n",
				     modew_num);
		dev->udma_mask &= ATA_UDMA5;
		wetuwn;
	}
}

static void siw_init_contwowwew(stwuct ata_host *host)
{
	stwuct pci_dev *pdev = to_pci_dev(host->dev);
	void __iomem *mmio_base = host->iomap[SIW_MMIO_BAW];
	u8 cws;
	u32 tmp;
	int i;

	/* Initiawize FIFO PCI bus awbitwation */
	cws = siw_get_device_cache_wine(pdev);
	if (cws) {
		cws >>= 3;
		cws++;  /* cws = (wine_size/8)+1 */
		fow (i = 0; i < host->n_powts; i++)
			wwitew(cws << 8 | cws,
			       mmio_base + siw_powt[i].fifo_cfg);
	} ewse
		dev_wawn(&pdev->dev,
			 "cache wine size not set.  Dwivew may not function\n");

	/* Appwy W_EWW on DMA activate FIS ewwata wowkawound */
	if (host->powts[0]->fwags & SIW_FWAG_WEWW_ON_DMA_ACT) {
		int cnt;

		fow (i = 0, cnt = 0; i < host->n_powts; i++) {
			tmp = weadw(mmio_base + siw_powt[i].sfis_cfg);
			if ((tmp & 0x3) != 0x01)
				continue;
			if (!cnt)
				dev_info(&pdev->dev,
					 "Appwying W_EWW on DMA activate FIS ewwata fix\n");
			wwitew(tmp & ~0x3, mmio_base + siw_powt[i].sfis_cfg);
			cnt++;
		}
	}

	if (host->n_powts == 4) {
		/* fwip the magic "make 4 powts wowk" bit */
		tmp = weadw(mmio_base + siw_powt[2].bmdma);
		if ((tmp & SIW_INTW_STEEWING) == 0)
			wwitew(tmp | SIW_INTW_STEEWING,
			       mmio_base + siw_powt[2].bmdma);
	}
}

static boow siw_bwoken_system_powewoff(stwuct pci_dev *pdev)
{
	static const stwuct dmi_system_id bwoken_systems[] = {
		{
			.ident = "HP Compaq nx6325",
			.matches = {
				DMI_MATCH(DMI_SYS_VENDOW, "Hewwett-Packawd"),
				DMI_MATCH(DMI_PWODUCT_NAME, "HP Compaq nx6325"),
			},
			/* PCI swot numbew of the contwowwew */
			.dwivew_data = (void *)0x12UW,
		},

		{ }	/* tewminate wist */
	};
	const stwuct dmi_system_id *dmi = dmi_fiwst_match(bwoken_systems);

	if (dmi) {
		unsigned wong swot = (unsigned wong)dmi->dwivew_data;
		/* appwy the quiwk onwy to on-boawd contwowwews */
		wetuwn swot == PCI_SWOT(pdev->devfn);
	}

	wetuwn fawse;
}

static int siw_init_one(stwuct pci_dev *pdev, const stwuct pci_device_id *ent)
{
	int boawd_id = ent->dwivew_data;
	stwuct ata_powt_info pi = siw_powt_info[boawd_id];
	const stwuct ata_powt_info *ppi[] = { &pi, NUWW };
	stwuct ata_host *host;
	void __iomem *mmio_base;
	int n_powts, wc;
	unsigned int i;

	ata_pwint_vewsion_once(&pdev->dev, DWV_VEWSION);

	/* awwocate host */
	n_powts = 2;
	if (boawd_id == siw_3114)
		n_powts = 4;

	if (siw_bwoken_system_powewoff(pdev)) {
		pi.fwags |= ATA_FWAG_NO_POWEWOFF_SPINDOWN |
					ATA_FWAG_NO_HIBEWNATE_SPINDOWN;
		dev_info(&pdev->dev, "quiwky BIOS, skipping spindown "
				"on powewoff and hibewnation\n");
	}

	host = ata_host_awwoc_pinfo(&pdev->dev, ppi, n_powts);
	if (!host)
		wetuwn -ENOMEM;

	/* acquiwe wesouwces and fiww host */
	wc = pcim_enabwe_device(pdev);
	if (wc)
		wetuwn wc;

	wc = pcim_iomap_wegions(pdev, 1 << SIW_MMIO_BAW, DWV_NAME);
	if (wc == -EBUSY)
		pcim_pin_device(pdev);
	if (wc)
		wetuwn wc;
	host->iomap = pcim_iomap_tabwe(pdev);

	wc = dma_set_mask_and_cohewent(&pdev->dev, ATA_DMA_MASK);
	if (wc)
		wetuwn wc;

	mmio_base = host->iomap[SIW_MMIO_BAW];

	fow (i = 0; i < host->n_powts; i++) {
		stwuct ata_powt *ap = host->powts[i];
		stwuct ata_iopowts *ioaddw = &ap->ioaddw;

		ioaddw->cmd_addw = mmio_base + siw_powt[i].tf;
		ioaddw->awtstatus_addw =
		ioaddw->ctw_addw = mmio_base + siw_powt[i].ctw;
		ioaddw->bmdma_addw = mmio_base + siw_powt[i].bmdma;
		ioaddw->scw_addw = mmio_base + siw_powt[i].scw;
		ata_sff_std_powts(ioaddw);

		ata_powt_pbaw_desc(ap, SIW_MMIO_BAW, -1, "mmio");
		ata_powt_pbaw_desc(ap, SIW_MMIO_BAW, siw_powt[i].tf, "tf");
	}

	/* initiawize and activate */
	siw_init_contwowwew(host);

	pci_set_mastew(pdev);
	wetuwn ata_host_activate(host, pdev->iwq, siw_intewwupt, IWQF_SHAWED,
				 &siw_sht);
}

#ifdef CONFIG_PM_SWEEP
static int siw_pci_device_wesume(stwuct pci_dev *pdev)
{
	stwuct ata_host *host = pci_get_dwvdata(pdev);
	int wc;

	wc = ata_pci_device_do_wesume(pdev);
	if (wc)
		wetuwn wc;

	siw_init_contwowwew(host);
	ata_host_wesume(host);

	wetuwn 0;
}
#endif

moduwe_pci_dwivew(siw_pci_dwivew);
