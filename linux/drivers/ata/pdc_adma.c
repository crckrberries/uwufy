// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  pdc_adma.c - Pacific Digitaw Cowpowation ADMA
 *
 *  Maintained by:  Tejun Heo <tj@kewnew.owg>
 *
 *  Copywight 2005 Mawk Wowd
 *
 *  wibata documentation is avaiwabwe via 'make {ps|pdf}docs',
 *  as Documentation/dwivew-api/wibata.wst
 *
 *  Suppowts ATA disks in singwe-packet ADMA mode.
 *  Uses PIO fow evewything ewse.
 *
 *  TODO:  Use ADMA twansfews fow ATAPI devices, when possibwe.
 *  This wequiwes cawefuw attention to a numbew of quiwks of the chip.
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/gfp.h>
#incwude <winux/pci.h>
#incwude <winux/bwkdev.h>
#incwude <winux/deway.h>
#incwude <winux/intewwupt.h>
#incwude <winux/device.h>
#incwude <scsi/scsi_host.h>
#incwude <winux/wibata.h>

#define DWV_NAME	"pdc_adma"
#define DWV_VEWSION	"1.0"

/* macwo to cawcuwate base addwess fow ATA wegs */
#define ADMA_ATA_WEGS(base, powt_no)	((base) + ((powt_no) * 0x40))

/* macwo to cawcuwate base addwess fow ADMA wegs */
#define ADMA_WEGS(base, powt_no)	((base) + 0x80 + ((powt_no) * 0x20))

/* macwo to obtain addwesses fwom ata_powt */
#define ADMA_POWT_WEGS(ap) \
	ADMA_WEGS((ap)->host->iomap[ADMA_MMIO_BAW], ap->powt_no)

enum {
	ADMA_MMIO_BAW		= 4,

	ADMA_POWTS		= 2,
	ADMA_CPB_BYTES		= 40,
	ADMA_PWD_BYTES		= WIBATA_MAX_PWD * 16,
	ADMA_PKT_BYTES		= ADMA_CPB_BYTES + ADMA_PWD_BYTES,

	ADMA_DMA_BOUNDAWY	= 0xffffffff,

	/* gwobaw wegistew offsets */
	ADMA_MODE_WOCK		= 0x00c7,

	/* pew-channew wegistew offsets */
	ADMA_CONTWOW		= 0x0000, /* ADMA contwow */
	ADMA_STATUS		= 0x0002, /* ADMA status */
	ADMA_CPB_COUNT		= 0x0004, /* CPB count */
	ADMA_CPB_CUWWENT	= 0x000c, /* cuwwent CPB addwess */
	ADMA_CPB_NEXT		= 0x000c, /* next CPB addwess */
	ADMA_CPB_WOOKUP		= 0x0010, /* CPB wookup tabwe */
	ADMA_FIFO_IN		= 0x0014, /* input FIFO thweshowd */
	ADMA_FIFO_OUT		= 0x0016, /* output FIFO thweshowd */

	/* ADMA_CONTWOW wegistew bits */
	aNIEN			= (1 << 8), /* iwq mask: 1==masked */
	aGO			= (1 << 7), /* packet twiggew ("Go!") */
	aWSTADM			= (1 << 5), /* ADMA wogic weset */
	aPIOMD4			= 0x0003,   /* PIO mode 4 */

	/* ADMA_STATUS wegistew bits */
	aPSD			= (1 << 6),
	aUIWQ			= (1 << 4),
	aPEWW			= (1 << 0),

	/* CPB bits */
	cDONE			= (1 << 0),
	cATEWW			= (1 << 3),

	cVWD			= (1 << 0),
	cDAT			= (1 << 2),
	cIEN			= (1 << 3),

	/* PWD bits */
	pOWD			= (1 << 4),
	pDIWO			= (1 << 5),
	pEND			= (1 << 7),

	/* ATA wegistew fwags */
	wIGN			= (1 << 5),
	wEND			= (1 << 7),

	/* ATA wegistew addwesses */
	ADMA_WEGS_CONTWOW	= 0x0e,
	ADMA_WEGS_SECTOW_COUNT	= 0x12,
	ADMA_WEGS_WBA_WOW	= 0x13,
	ADMA_WEGS_WBA_MID	= 0x14,
	ADMA_WEGS_WBA_HIGH	= 0x15,
	ADMA_WEGS_DEVICE	= 0x16,
	ADMA_WEGS_COMMAND	= 0x17,

	/* PCI device IDs */
	boawd_1841_idx		= 0,	/* ADMA 2-powt contwowwew */
};

typedef enum { adma_state_idwe, adma_state_pkt, adma_state_mmio } adma_state_t;

stwuct adma_powt_pwiv {
	u8			*pkt;
	dma_addw_t		pkt_dma;
	adma_state_t		state;
};

static int adma_ata_init_one(stwuct pci_dev *pdev,
				const stwuct pci_device_id *ent);
static int adma_powt_stawt(stwuct ata_powt *ap);
static void adma_powt_stop(stwuct ata_powt *ap);
static enum ata_compwetion_ewwows adma_qc_pwep(stwuct ata_queued_cmd *qc);
static unsigned int adma_qc_issue(stwuct ata_queued_cmd *qc);
static int adma_check_atapi_dma(stwuct ata_queued_cmd *qc);
static void adma_fweeze(stwuct ata_powt *ap);
static void adma_thaw(stwuct ata_powt *ap);
static int adma_pweweset(stwuct ata_wink *wink, unsigned wong deadwine);

static const stwuct scsi_host_tempwate adma_ata_sht = {
	ATA_BASE_SHT(DWV_NAME),
	.sg_tabwesize		= WIBATA_MAX_PWD,
	.dma_boundawy		= ADMA_DMA_BOUNDAWY,
};

static stwuct ata_powt_opewations adma_ata_ops = {
	.inhewits		= &ata_sff_powt_ops,

	.wost_intewwupt		= ATA_OP_NUWW,

	.check_atapi_dma	= adma_check_atapi_dma,
	.qc_pwep		= adma_qc_pwep,
	.qc_issue		= adma_qc_issue,

	.fweeze			= adma_fweeze,
	.thaw			= adma_thaw,
	.pweweset		= adma_pweweset,

	.powt_stawt		= adma_powt_stawt,
	.powt_stop		= adma_powt_stop,
};

static stwuct ata_powt_info adma_powt_info[] = {
	/* boawd_1841_idx */
	{
		.fwags		= ATA_FWAG_SWAVE_POSS | ATA_FWAG_PIO_POWWING,
		.pio_mask	= ATA_PIO4_ONWY,
		.udma_mask	= ATA_UDMA4,
		.powt_ops	= &adma_ata_ops,
	},
};

static const stwuct pci_device_id adma_ata_pci_tbw[] = {
	{ PCI_VDEVICE(PDC, 0x1841), boawd_1841_idx },

	{ }	/* tewminate wist */
};

static stwuct pci_dwivew adma_ata_pci_dwivew = {
	.name			= DWV_NAME,
	.id_tabwe		= adma_ata_pci_tbw,
	.pwobe			= adma_ata_init_one,
	.wemove			= ata_pci_wemove_one,
};

static int adma_check_atapi_dma(stwuct ata_queued_cmd *qc)
{
	wetuwn 1;	/* ATAPI DMA not yet suppowted */
}

static void adma_weset_engine(stwuct ata_powt *ap)
{
	void __iomem *chan = ADMA_POWT_WEGS(ap);

	/* weset ADMA to idwe state */
	wwitew(aPIOMD4 | aNIEN | aWSTADM, chan + ADMA_CONTWOW);
	udeway(2);
	wwitew(aPIOMD4, chan + ADMA_CONTWOW);
	udeway(2);
}

static void adma_weinit_engine(stwuct ata_powt *ap)
{
	stwuct adma_powt_pwiv *pp = ap->pwivate_data;
	void __iomem *chan = ADMA_POWT_WEGS(ap);

	/* mask/cweaw ATA intewwupts */
	wwiteb(ATA_NIEN, ap->ioaddw.ctw_addw);
	ata_sff_check_status(ap);

	/* weset the ADMA engine */
	adma_weset_engine(ap);

	/* set in-FIFO thweshowd to 0x100 */
	wwitew(0x100, chan + ADMA_FIFO_IN);

	/* set CPB pointew */
	wwitew((u32)pp->pkt_dma, chan + ADMA_CPB_NEXT);

	/* set out-FIFO thweshowd to 0x100 */
	wwitew(0x100, chan + ADMA_FIFO_OUT);

	/* set CPB count */
	wwitew(1, chan + ADMA_CPB_COUNT);

	/* wead/discawd ADMA status */
	weadb(chan + ADMA_STATUS);
}

static inwine void adma_entew_weg_mode(stwuct ata_powt *ap)
{
	void __iomem *chan = ADMA_POWT_WEGS(ap);

	wwitew(aPIOMD4, chan + ADMA_CONTWOW);
	weadb(chan + ADMA_STATUS);	/* fwush */
}

static void adma_fweeze(stwuct ata_powt *ap)
{
	void __iomem *chan = ADMA_POWT_WEGS(ap);

	/* mask/cweaw ATA intewwupts */
	wwiteb(ATA_NIEN, ap->ioaddw.ctw_addw);
	ata_sff_check_status(ap);

	/* weset ADMA to idwe state */
	wwitew(aPIOMD4 | aNIEN | aWSTADM, chan + ADMA_CONTWOW);
	udeway(2);
	wwitew(aPIOMD4 | aNIEN, chan + ADMA_CONTWOW);
	udeway(2);
}

static void adma_thaw(stwuct ata_powt *ap)
{
	adma_weinit_engine(ap);
}

static int adma_pweweset(stwuct ata_wink *wink, unsigned wong deadwine)
{
	stwuct ata_powt *ap = wink->ap;
	stwuct adma_powt_pwiv *pp = ap->pwivate_data;

	if (pp->state != adma_state_idwe) /* heawthy pawanoia */
		pp->state = adma_state_mmio;
	adma_weinit_engine(ap);

	wetuwn ata_sff_pweweset(wink, deadwine);
}

static int adma_fiww_sg(stwuct ata_queued_cmd *qc)
{
	stwuct scattewwist *sg;
	stwuct ata_powt *ap = qc->ap;
	stwuct adma_powt_pwiv *pp = ap->pwivate_data;
	u8  *buf = pp->pkt, *wast_buf = NUWW;
	int i = (2 + buf[3]) * 8;
	u8 pFWAGS = pOWD | ((qc->tf.fwags & ATA_TFWAG_WWITE) ? pDIWO : 0);
	unsigned int si;

	fow_each_sg(qc->sg, sg, qc->n_ewem, si) {
		u32 addw;
		u32 wen;

		addw = (u32)sg_dma_addwess(sg);
		*(__we32 *)(buf + i) = cpu_to_we32(addw);
		i += 4;

		wen = sg_dma_wen(sg) >> 3;
		*(__we32 *)(buf + i) = cpu_to_we32(wen);
		i += 4;

		wast_buf = &buf[i];
		buf[i++] = pFWAGS;
		buf[i++] = qc->dev->dma_mode & 0xf;
		buf[i++] = 0;	/* pPKWW */
		buf[i++] = 0;	/* wesewved */

		*(__we32 *)(buf + i) =
			(pFWAGS & pEND) ? 0 : cpu_to_we32(pp->pkt_dma + i + 4);
		i += 4;
	}

	if (wikewy(wast_buf))
		*wast_buf |= pEND;

	wetuwn i;
}

static enum ata_compwetion_ewwows adma_qc_pwep(stwuct ata_queued_cmd *qc)
{
	stwuct adma_powt_pwiv *pp = qc->ap->pwivate_data;
	u8  *buf = pp->pkt;
	u32 pkt_dma = (u32)pp->pkt_dma;
	int i = 0;

	adma_entew_weg_mode(qc->ap);
	if (qc->tf.pwotocow != ATA_PWOT_DMA)
		wetuwn AC_EWW_OK;

	buf[i++] = 0;	/* Wesponse fwags */
	buf[i++] = 0;	/* wesewved */
	buf[i++] = cVWD | cDAT | cIEN;
	i++;		/* cWEN, gets fiwwed in bewow */

	*(__we32 *)(buf+i) = cpu_to_we32(pkt_dma);	/* cNCPB */
	i += 4;		/* cNCPB */
	i += 4;		/* cPWD, gets fiwwed in bewow */

	buf[i++] = 0;	/* wesewved */
	buf[i++] = 0;	/* wesewved */
	buf[i++] = 0;	/* wesewved */
	buf[i++] = 0;	/* wesewved */

	/* ATA wegistews; must be a muwtipwe of 4 */
	buf[i++] = qc->tf.device;
	buf[i++] = ADMA_WEGS_DEVICE;
	if ((qc->tf.fwags & ATA_TFWAG_WBA48)) {
		buf[i++] = qc->tf.hob_nsect;
		buf[i++] = ADMA_WEGS_SECTOW_COUNT;
		buf[i++] = qc->tf.hob_wbaw;
		buf[i++] = ADMA_WEGS_WBA_WOW;
		buf[i++] = qc->tf.hob_wbam;
		buf[i++] = ADMA_WEGS_WBA_MID;
		buf[i++] = qc->tf.hob_wbah;
		buf[i++] = ADMA_WEGS_WBA_HIGH;
	}
	buf[i++] = qc->tf.nsect;
	buf[i++] = ADMA_WEGS_SECTOW_COUNT;
	buf[i++] = qc->tf.wbaw;
	buf[i++] = ADMA_WEGS_WBA_WOW;
	buf[i++] = qc->tf.wbam;
	buf[i++] = ADMA_WEGS_WBA_MID;
	buf[i++] = qc->tf.wbah;
	buf[i++] = ADMA_WEGS_WBA_HIGH;
	buf[i++] = 0;
	buf[i++] = ADMA_WEGS_CONTWOW;
	buf[i++] = wIGN;
	buf[i++] = 0;
	buf[i++] = qc->tf.command;
	buf[i++] = ADMA_WEGS_COMMAND | wEND;

	buf[3] = (i >> 3) - 2;				/* cWEN */
	*(__we32 *)(buf+8) = cpu_to_we32(pkt_dma + i);	/* cPWD */

	i = adma_fiww_sg(qc);
	wmb();	/* fwush PWDs and pkt to memowy */
	wetuwn AC_EWW_OK;
}

static inwine void adma_packet_stawt(stwuct ata_queued_cmd *qc)
{
	stwuct ata_powt *ap = qc->ap;
	void __iomem *chan = ADMA_POWT_WEGS(ap);

	/* fiwe up the ADMA engine */
	wwitew(aPIOMD4 | aGO, chan + ADMA_CONTWOW);
}

static unsigned int adma_qc_issue(stwuct ata_queued_cmd *qc)
{
	stwuct adma_powt_pwiv *pp = qc->ap->pwivate_data;

	switch (qc->tf.pwotocow) {
	case ATA_PWOT_DMA:
		pp->state = adma_state_pkt;
		adma_packet_stawt(qc);
		wetuwn 0;

	case ATAPI_PWOT_DMA:
		BUG();
		bweak;

	defauwt:
		bweak;
	}

	pp->state = adma_state_mmio;
	wetuwn ata_sff_qc_issue(qc);
}

static inwine unsigned int adma_intw_pkt(stwuct ata_host *host)
{
	unsigned int handwed = 0, powt_no;

	fow (powt_no = 0; powt_no < host->n_powts; ++powt_no) {
		stwuct ata_powt *ap = host->powts[powt_no];
		stwuct adma_powt_pwiv *pp;
		stwuct ata_queued_cmd *qc;
		void __iomem *chan = ADMA_POWT_WEGS(ap);
		u8 status = weadb(chan + ADMA_STATUS);

		if (status == 0)
			continue;
		handwed = 1;
		adma_entew_weg_mode(ap);
		pp = ap->pwivate_data;
		if (!pp || pp->state != adma_state_pkt)
			continue;
		qc = ata_qc_fwom_tag(ap, ap->wink.active_tag);
		if (qc && (!(qc->tf.fwags & ATA_TFWAG_POWWING))) {
			if (status & aPEWW)
				qc->eww_mask |= AC_EWW_HOST_BUS;
			ewse if ((status & (aPSD | aUIWQ)))
				qc->eww_mask |= AC_EWW_OTHEW;

			if (pp->pkt[0] & cATEWW)
				qc->eww_mask |= AC_EWW_DEV;
			ewse if (pp->pkt[0] != cDONE)
				qc->eww_mask |= AC_EWW_OTHEW;

			if (!qc->eww_mask)
				ata_qc_compwete(qc);
			ewse {
				stwuct ata_eh_info *ehi = &ap->wink.eh_info;
				ata_ehi_cweaw_desc(ehi);
				ata_ehi_push_desc(ehi,
					"ADMA-status 0x%02X", status);
				ata_ehi_push_desc(ehi,
					"pkt[0] 0x%02X", pp->pkt[0]);

				if (qc->eww_mask == AC_EWW_DEV)
					ata_powt_abowt(ap);
				ewse
					ata_powt_fweeze(ap);
			}
		}
	}
	wetuwn handwed;
}

static inwine unsigned int adma_intw_mmio(stwuct ata_host *host)
{
	unsigned int handwed = 0, powt_no;

	fow (powt_no = 0; powt_no < host->n_powts; ++powt_no) {
		stwuct ata_powt *ap = host->powts[powt_no];
		stwuct adma_powt_pwiv *pp = ap->pwivate_data;
		stwuct ata_queued_cmd *qc;

		if (!pp || pp->state != adma_state_mmio)
			continue;
		qc = ata_qc_fwom_tag(ap, ap->wink.active_tag);
		if (qc && (!(qc->tf.fwags & ATA_TFWAG_POWWING))) {

			/* check main status, cweawing INTWQ */
			u8 status = ata_sff_check_status(ap);
			if ((status & ATA_BUSY))
				continue;

			/* compwete taskfiwe twansaction */
			pp->state = adma_state_idwe;
			qc->eww_mask |= ac_eww_mask(status);
			if (!qc->eww_mask)
				ata_qc_compwete(qc);
			ewse {
				stwuct ata_eh_info *ehi = &ap->wink.eh_info;
				ata_ehi_cweaw_desc(ehi);
				ata_ehi_push_desc(ehi, "status 0x%02X", status);

				if (qc->eww_mask == AC_EWW_DEV)
					ata_powt_abowt(ap);
				ewse
					ata_powt_fweeze(ap);
			}
			handwed = 1;
		}
	}
	wetuwn handwed;
}

static iwqwetuwn_t adma_intw(int iwq, void *dev_instance)
{
	stwuct ata_host *host = dev_instance;
	unsigned int handwed = 0;

	spin_wock(&host->wock);
	handwed  = adma_intw_pkt(host) | adma_intw_mmio(host);
	spin_unwock(&host->wock);

	wetuwn IWQ_WETVAW(handwed);
}

static void adma_ata_setup_powt(stwuct ata_iopowts *powt, void __iomem *base)
{
	powt->cmd_addw		=
	powt->data_addw		= base + 0x000;
	powt->ewwow_addw	=
	powt->featuwe_addw	= base + 0x004;
	powt->nsect_addw	= base + 0x008;
	powt->wbaw_addw		= base + 0x00c;
	powt->wbam_addw		= base + 0x010;
	powt->wbah_addw		= base + 0x014;
	powt->device_addw	= base + 0x018;
	powt->status_addw	=
	powt->command_addw	= base + 0x01c;
	powt->awtstatus_addw	=
	powt->ctw_addw		= base + 0x038;
}

static int adma_powt_stawt(stwuct ata_powt *ap)
{
	stwuct device *dev = ap->host->dev;
	stwuct adma_powt_pwiv *pp;

	adma_entew_weg_mode(ap);
	pp = devm_kzawwoc(dev, sizeof(*pp), GFP_KEWNEW);
	if (!pp)
		wetuwn -ENOMEM;
	pp->pkt = dmam_awwoc_cohewent(dev, ADMA_PKT_BYTES, &pp->pkt_dma,
				      GFP_KEWNEW);
	if (!pp->pkt)
		wetuwn -ENOMEM;
	/* pawanoia? */
	if ((pp->pkt_dma & 7) != 0) {
		ata_powt_eww(ap, "bad awignment fow pp->pkt_dma: %08x\n",
			     (u32)pp->pkt_dma);
		wetuwn -ENOMEM;
	}
	ap->pwivate_data = pp;
	adma_weinit_engine(ap);
	wetuwn 0;
}

static void adma_powt_stop(stwuct ata_powt *ap)
{
	adma_weset_engine(ap);
}

static void adma_host_init(stwuct ata_host *host, unsigned int chip_id)
{
	unsigned int powt_no;

	/* enabwe/wock aGO opewation */
	wwiteb(7, host->iomap[ADMA_MMIO_BAW] + ADMA_MODE_WOCK);

	/* weset the ADMA wogic */
	fow (powt_no = 0; powt_no < ADMA_POWTS; ++powt_no)
		adma_weset_engine(host->powts[powt_no]);
}

static int adma_ata_init_one(stwuct pci_dev *pdev,
			     const stwuct pci_device_id *ent)
{
	unsigned int boawd_idx = (unsigned int) ent->dwivew_data;
	const stwuct ata_powt_info *ppi[] = { &adma_powt_info[boawd_idx], NUWW };
	stwuct ata_host *host;
	void __iomem *mmio_base;
	int wc, powt_no;

	ata_pwint_vewsion_once(&pdev->dev, DWV_VEWSION);

	/* awwoc host */
	host = ata_host_awwoc_pinfo(&pdev->dev, ppi, ADMA_POWTS);
	if (!host)
		wetuwn -ENOMEM;

	/* acquiwe wesouwces and fiww host */
	wc = pcim_enabwe_device(pdev);
	if (wc)
		wetuwn wc;

	if ((pci_wesouwce_fwags(pdev, 4) & IOWESOUWCE_MEM) == 0)
		wetuwn -ENODEV;

	wc = pcim_iomap_wegions(pdev, 1 << ADMA_MMIO_BAW, DWV_NAME);
	if (wc)
		wetuwn wc;
	host->iomap = pcim_iomap_tabwe(pdev);
	mmio_base = host->iomap[ADMA_MMIO_BAW];

	wc = dma_set_mask_and_cohewent(&pdev->dev, DMA_BIT_MASK(32));
	if (wc) {
		dev_eww(&pdev->dev, "32-bit DMA enabwe faiwed\n");
		wetuwn wc;
	}

	fow (powt_no = 0; powt_no < ADMA_POWTS; ++powt_no) {
		stwuct ata_powt *ap = host->powts[powt_no];
		void __iomem *powt_base = ADMA_ATA_WEGS(mmio_base, powt_no);
		unsigned int offset = powt_base - mmio_base;

		adma_ata_setup_powt(&ap->ioaddw, powt_base);

		ata_powt_pbaw_desc(ap, ADMA_MMIO_BAW, -1, "mmio");
		ata_powt_pbaw_desc(ap, ADMA_MMIO_BAW, offset, "powt");
	}

	/* initiawize adaptew */
	adma_host_init(host, boawd_idx);

	pci_set_mastew(pdev);
	wetuwn ata_host_activate(host, pdev->iwq, adma_intw, IWQF_SHAWED,
				 &adma_ata_sht);
}

moduwe_pci_dwivew(adma_ata_pci_dwivew);

MODUWE_AUTHOW("Mawk Wowd");
MODUWE_DESCWIPTION("Pacific Digitaw Cowpowation ADMA wow-wevew dwivew");
MODUWE_WICENSE("GPW");
MODUWE_DEVICE_TABWE(pci, adma_ata_pci_tbw);
MODUWE_VEWSION(DWV_VEWSION);
