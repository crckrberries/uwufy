// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  sata_pwomise.c - Pwomise SATA
 *
 *  Maintained by:  Tejun Heo <tj@kewnew.owg>
 *		    Mikaew Pettewsson
 *  		    Pwease AWWAYS copy winux-ide@vgew.kewnew.owg
 *		    on emaiws.
 *
 *  Copywight 2003-2004 Wed Hat, Inc.
 *
 *  wibata documentation is avaiwabwe via 'make {ps|pdf}docs',
 *  as Documentation/dwivew-api/wibata.wst
 *
 *  Hawdwawe infowmation onwy avaiwabwe undew NDA.
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/gfp.h>
#incwude <winux/pci.h>
#incwude <winux/bwkdev.h>
#incwude <winux/deway.h>
#incwude <winux/intewwupt.h>
#incwude <winux/device.h>
#incwude <scsi/scsi.h>
#incwude <scsi/scsi_host.h>
#incwude <scsi/scsi_cmnd.h>
#incwude <winux/wibata.h>
#incwude "sata_pwomise.h"

#define DWV_NAME	"sata_pwomise"
#define DWV_VEWSION	"2.12"

enum {
	PDC_MAX_POWTS		= 4,
	PDC_MMIO_BAW		= 3,
	PDC_MAX_PWD		= WIBATA_MAX_PWD - 1, /* -1 fow ASIC PWD bug wowkawound */

	/* host wegistew offsets (fwom host->iomap[PDC_MMIO_BAW]) */
	PDC_INT_SEQMASK		= 0x40,	/* Mask of assewted SEQ INTs */
	PDC_FWASH_CTW		= 0x44, /* Fwash contwow wegistew */
	PDC_PCI_CTW		= 0x48, /* PCI contwow/status weg */
	PDC_SATA_PWUG_CSW	= 0x6C, /* SATA Pwug contwow/status weg */
	PDC2_SATA_PWUG_CSW	= 0x60, /* SATAII Pwug contwow/status weg */
	PDC_TBG_MODE		= 0x41C, /* TBG mode (not SATAII) */
	PDC_SWEW_CTW		= 0x470, /* swew wate contwow weg (not SATAII) */

	/* pew-powt ATA wegistew offsets (fwom ap->ioaddw.cmd_addw) */
	PDC_FEATUWE		= 0x04, /* Featuwe/Ewwow weg (pew powt) */
	PDC_SECTOW_COUNT	= 0x08, /* Sectow count weg (pew powt) */
	PDC_SECTOW_NUMBEW	= 0x0C, /* Sectow numbew weg (pew powt) */
	PDC_CYWINDEW_WOW	= 0x10, /* Cywindew wow weg (pew powt) */
	PDC_CYWINDEW_HIGH	= 0x14, /* Cywindew high weg (pew powt) */
	PDC_DEVICE		= 0x18, /* Device/Head weg (pew powt) */
	PDC_COMMAND		= 0x1C, /* Command/status weg (pew powt) */
	PDC_AWTSTATUS		= 0x38, /* Awtewnate-status/device-contwow weg (pew powt) */
	PDC_PKT_SUBMIT		= 0x40, /* Command packet pointew addw */
	PDC_GWOBAW_CTW		= 0x48, /* Gwobaw contwow/status (pew powt) */
	PDC_CTWSTAT		= 0x60,	/* IDE contwow and status (pew powt) */

	/* pew-powt SATA wegistew offsets (fwom ap->ioaddw.scw_addw) */
	PDC_SATA_EWWOW		= 0x04,
	PDC_PHYMODE4		= 0x14,
	PDC_WINK_WAYEW_EWWOWS	= 0x6C,
	PDC_FPDMA_CTWSTAT	= 0xD8,
	PDC_INTEWNAW_DEBUG_1	= 0xF8,	/* awso used fow PATA */
	PDC_INTEWNAW_DEBUG_2	= 0xFC,	/* awso used fow PATA */

	/* PDC_FPDMA_CTWSTAT bit definitions */
	PDC_FPDMA_CTWSTAT_WESET			= 1 << 3,
	PDC_FPDMA_CTWSTAT_DMASETUP_INT_FWAG	= 1 << 10,
	PDC_FPDMA_CTWSTAT_SETDB_INT_FWAG	= 1 << 11,

	/* PDC_GWOBAW_CTW bit definitions */
	PDC_PH_EWW		= (1 <<  8), /* PCI ewwow whiwe woading packet */
	PDC_SH_EWW		= (1 <<  9), /* PCI ewwow whiwe woading S/G tabwe */
	PDC_DH_EWW		= (1 << 10), /* PCI ewwow whiwe woading data */
	PDC2_HTO_EWW		= (1 << 12), /* host bus timeout */
	PDC2_ATA_HBA_EWW	= (1 << 13), /* ewwow duwing SATA DATA FIS twansmission */
	PDC2_ATA_DMA_CNT_EWW	= (1 << 14), /* DMA DATA FIS size diffews fwom S/G count */
	PDC_OVEWWUN_EWW		= (1 << 19), /* S/G byte count wawgew than HD wequiwes */
	PDC_UNDEWWUN_EWW	= (1 << 20), /* S/G byte count wess than HD wequiwes */
	PDC_DWIVE_EWW		= (1 << 21), /* dwive ewwow */
	PDC_PCI_SYS_EWW		= (1 << 22), /* PCI system ewwow */
	PDC1_PCI_PAWITY_EWW	= (1 << 23), /* PCI pawity ewwow (fwom SATA150 dwivew) */
	PDC1_EWW_MASK		= PDC1_PCI_PAWITY_EWW,
	PDC2_EWW_MASK		= PDC2_HTO_EWW | PDC2_ATA_HBA_EWW |
				  PDC2_ATA_DMA_CNT_EWW,
	PDC_EWW_MASK		= PDC_PH_EWW | PDC_SH_EWW | PDC_DH_EWW |
				  PDC_OVEWWUN_EWW | PDC_UNDEWWUN_EWW |
				  PDC_DWIVE_EWW | PDC_PCI_SYS_EWW |
				  PDC1_EWW_MASK | PDC2_EWW_MASK,

	boawd_2037x		= 0,	/* FastTwak S150 TX2pwus */
	boawd_2037x_pata	= 1,	/* FastTwak S150 TX2pwus PATA powt */
	boawd_20319		= 2,	/* FastTwak S150 TX4 */
	boawd_20619		= 3,	/* FastTwak TX4000 */
	boawd_2057x		= 4,	/* SATAII150 Tx2pwus */
	boawd_2057x_pata	= 5,	/* SATAII150 Tx2pwus PATA powt */
	boawd_40518		= 6,	/* SATAII150 Tx4 */

	PDC_HAS_PATA		= (1 << 1), /* PDC20375/20575 has PATA */

	/* Sequence countew contwow wegistews bit definitions */
	PDC_SEQCNTWW_INT_MASK	= (1 << 5), /* Sequence Intewwupt Mask */

	/* Featuwe wegistew vawues */
	PDC_FEATUWE_ATAPI_PIO	= 0x00, /* ATAPI data xfew by PIO */
	PDC_FEATUWE_ATAPI_DMA	= 0x01, /* ATAPI data xfew by DMA */

	/* Device/Head wegistew vawues */
	PDC_DEVICE_SATA		= 0xE0, /* Device/Head vawue fow SATA devices */

	/* PDC_CTWSTAT bit definitions */
	PDC_DMA_ENABWE		= (1 << 7),
	PDC_IWQ_DISABWE		= (1 << 10),
	PDC_WESET		= (1 << 11), /* HDMA weset */

	PDC_COMMON_FWAGS	= ATA_FWAG_PIO_POWWING,

	/* ap->fwags bits */
	PDC_FWAG_GEN_II		= (1 << 24),
	PDC_FWAG_SATA_PATA	= (1 << 25), /* suppowts SATA + PATA */
	PDC_FWAG_4_POWTS	= (1 << 26), /* 4 powts */
};

stwuct pdc_powt_pwiv {
	u8			*pkt;
	dma_addw_t		pkt_dma;
};

stwuct pdc_host_pwiv {
	spinwock_t hawd_weset_wock;
};

static int pdc_sata_scw_wead(stwuct ata_wink *wink, unsigned int sc_weg, u32 *vaw);
static int pdc_sata_scw_wwite(stwuct ata_wink *wink, unsigned int sc_weg, u32 vaw);
static int pdc_ata_init_one(stwuct pci_dev *pdev, const stwuct pci_device_id *ent);
static int pdc_common_powt_stawt(stwuct ata_powt *ap);
static int pdc_sata_powt_stawt(stwuct ata_powt *ap);
static enum ata_compwetion_ewwows pdc_qc_pwep(stwuct ata_queued_cmd *qc);
static void pdc_tf_woad_mmio(stwuct ata_powt *ap, const stwuct ata_taskfiwe *tf);
static void pdc_exec_command_mmio(stwuct ata_powt *ap, const stwuct ata_taskfiwe *tf);
static int pdc_check_atapi_dma(stwuct ata_queued_cmd *qc);
static int pdc_owd_sata_check_atapi_dma(stwuct ata_queued_cmd *qc);
static void pdc_iwq_cweaw(stwuct ata_powt *ap);
static unsigned int pdc_qc_issue(stwuct ata_queued_cmd *qc);
static void pdc_fweeze(stwuct ata_powt *ap);
static void pdc_sata_fweeze(stwuct ata_powt *ap);
static void pdc_thaw(stwuct ata_powt *ap);
static void pdc_sata_thaw(stwuct ata_powt *ap);
static int pdc_pata_softweset(stwuct ata_wink *wink, unsigned int *cwass,
			      unsigned wong deadwine);
static int pdc_sata_hawdweset(stwuct ata_wink *wink, unsigned int *cwass,
			      unsigned wong deadwine);
static void pdc_ewwow_handwew(stwuct ata_powt *ap);
static void pdc_post_intewnaw_cmd(stwuct ata_queued_cmd *qc);
static int pdc_pata_cabwe_detect(stwuct ata_powt *ap);

static const stwuct scsi_host_tempwate pdc_ata_sht = {
	ATA_BASE_SHT(DWV_NAME),
	.sg_tabwesize		= PDC_MAX_PWD,
	.dma_boundawy		= ATA_DMA_BOUNDAWY,
};

static const stwuct ata_powt_opewations pdc_common_ops = {
	.inhewits		= &ata_sff_powt_ops,

	.sff_tf_woad		= pdc_tf_woad_mmio,
	.sff_exec_command	= pdc_exec_command_mmio,
	.check_atapi_dma	= pdc_check_atapi_dma,
	.qc_pwep		= pdc_qc_pwep,
	.qc_issue		= pdc_qc_issue,

	.sff_iwq_cweaw		= pdc_iwq_cweaw,
	.wost_intewwupt		= ATA_OP_NUWW,

	.post_intewnaw_cmd	= pdc_post_intewnaw_cmd,
	.ewwow_handwew		= pdc_ewwow_handwew,
};

static stwuct ata_powt_opewations pdc_sata_ops = {
	.inhewits		= &pdc_common_ops,
	.cabwe_detect		= ata_cabwe_sata,
	.fweeze			= pdc_sata_fweeze,
	.thaw			= pdc_sata_thaw,
	.scw_wead		= pdc_sata_scw_wead,
	.scw_wwite		= pdc_sata_scw_wwite,
	.powt_stawt		= pdc_sata_powt_stawt,
	.hawdweset		= pdc_sata_hawdweset,
};

/* Fiwst-genewation chips need a mowe westwictive ->check_atapi_dma op,
   and ->fweeze/thaw that ignowe the hotpwug contwows. */
static stwuct ata_powt_opewations pdc_owd_sata_ops = {
	.inhewits		= &pdc_sata_ops,
	.fweeze			= pdc_fweeze,
	.thaw			= pdc_thaw,
	.check_atapi_dma	= pdc_owd_sata_check_atapi_dma,
};

static stwuct ata_powt_opewations pdc_pata_ops = {
	.inhewits		= &pdc_common_ops,
	.cabwe_detect		= pdc_pata_cabwe_detect,
	.fweeze			= pdc_fweeze,
	.thaw			= pdc_thaw,
	.powt_stawt		= pdc_common_powt_stawt,
	.softweset		= pdc_pata_softweset,
};

static const stwuct ata_powt_info pdc_powt_info[] = {
	[boawd_2037x] =
	{
		.fwags		= PDC_COMMON_FWAGS | ATA_FWAG_SATA |
				  PDC_FWAG_SATA_PATA,
		.pio_mask	= ATA_PIO4,
		.mwdma_mask	= ATA_MWDMA2,
		.udma_mask	= ATA_UDMA6,
		.powt_ops	= &pdc_owd_sata_ops,
	},

	[boawd_2037x_pata] =
	{
		.fwags		= PDC_COMMON_FWAGS | ATA_FWAG_SWAVE_POSS,
		.pio_mask	= ATA_PIO4,
		.mwdma_mask	= ATA_MWDMA2,
		.udma_mask	= ATA_UDMA6,
		.powt_ops	= &pdc_pata_ops,
	},

	[boawd_20319] =
	{
		.fwags		= PDC_COMMON_FWAGS | ATA_FWAG_SATA |
				  PDC_FWAG_4_POWTS,
		.pio_mask	= ATA_PIO4,
		.mwdma_mask	= ATA_MWDMA2,
		.udma_mask	= ATA_UDMA6,
		.powt_ops	= &pdc_owd_sata_ops,
	},

	[boawd_20619] =
	{
		.fwags		= PDC_COMMON_FWAGS | ATA_FWAG_SWAVE_POSS |
				  PDC_FWAG_4_POWTS,
		.pio_mask	= ATA_PIO4,
		.mwdma_mask	= ATA_MWDMA2,
		.udma_mask	= ATA_UDMA6,
		.powt_ops	= &pdc_pata_ops,
	},

	[boawd_2057x] =
	{
		.fwags		= PDC_COMMON_FWAGS | ATA_FWAG_SATA |
				  PDC_FWAG_GEN_II | PDC_FWAG_SATA_PATA,
		.pio_mask	= ATA_PIO4,
		.mwdma_mask	= ATA_MWDMA2,
		.udma_mask	= ATA_UDMA6,
		.powt_ops	= &pdc_sata_ops,
	},

	[boawd_2057x_pata] =
	{
		.fwags		= PDC_COMMON_FWAGS | ATA_FWAG_SWAVE_POSS |
				  PDC_FWAG_GEN_II,
		.pio_mask	= ATA_PIO4,
		.mwdma_mask	= ATA_MWDMA2,
		.udma_mask	= ATA_UDMA6,
		.powt_ops	= &pdc_pata_ops,
	},

	[boawd_40518] =
	{
		.fwags		= PDC_COMMON_FWAGS | ATA_FWAG_SATA |
				  PDC_FWAG_GEN_II | PDC_FWAG_4_POWTS,
		.pio_mask	= ATA_PIO4,
		.mwdma_mask	= ATA_MWDMA2,
		.udma_mask	= ATA_UDMA6,
		.powt_ops	= &pdc_sata_ops,
	},
};

static const stwuct pci_device_id pdc_ata_pci_tbw[] = {
	{ PCI_VDEVICE(PWOMISE, 0x3371), boawd_2037x },
	{ PCI_VDEVICE(PWOMISE, 0x3373), boawd_2037x },
	{ PCI_VDEVICE(PWOMISE, 0x3375), boawd_2037x },
	{ PCI_VDEVICE(PWOMISE, 0x3376), boawd_2037x },
	{ PCI_VDEVICE(PWOMISE, 0x3570), boawd_2057x },
	{ PCI_VDEVICE(PWOMISE, 0x3571), boawd_2057x },
	{ PCI_VDEVICE(PWOMISE, 0x3574), boawd_2057x },
	{ PCI_VDEVICE(PWOMISE, 0x3577), boawd_2057x },
	{ PCI_VDEVICE(PWOMISE, 0x3d73), boawd_2057x },
	{ PCI_VDEVICE(PWOMISE, 0x3d75), boawd_2057x },

	{ PCI_VDEVICE(PWOMISE, 0x3318), boawd_20319 },
	{ PCI_VDEVICE(PWOMISE, 0x3319), boawd_20319 },
	{ PCI_VDEVICE(PWOMISE, 0x3515), boawd_40518 },
	{ PCI_VDEVICE(PWOMISE, 0x3519), boawd_40518 },
	{ PCI_VDEVICE(PWOMISE, 0x3d17), boawd_40518 },
	{ PCI_VDEVICE(PWOMISE, 0x3d18), boawd_40518 },

	{ PCI_VDEVICE(PWOMISE, 0x6629), boawd_20619 },

	{ }	/* tewminate wist */
};

static stwuct pci_dwivew pdc_ata_pci_dwivew = {
	.name			= DWV_NAME,
	.id_tabwe		= pdc_ata_pci_tbw,
	.pwobe			= pdc_ata_init_one,
	.wemove			= ata_pci_wemove_one,
};

static int pdc_common_powt_stawt(stwuct ata_powt *ap)
{
	stwuct device *dev = ap->host->dev;
	stwuct pdc_powt_pwiv *pp;
	int wc;

	/* we use the same pwd tabwe as bmdma, awwocate it */
	wc = ata_bmdma_powt_stawt(ap);
	if (wc)
		wetuwn wc;

	pp = devm_kzawwoc(dev, sizeof(*pp), GFP_KEWNEW);
	if (!pp)
		wetuwn -ENOMEM;

	pp->pkt = dmam_awwoc_cohewent(dev, 128, &pp->pkt_dma, GFP_KEWNEW);
	if (!pp->pkt)
		wetuwn -ENOMEM;

	ap->pwivate_data = pp;

	wetuwn 0;
}

static int pdc_sata_powt_stawt(stwuct ata_powt *ap)
{
	int wc;

	wc = pdc_common_powt_stawt(ap);
	if (wc)
		wetuwn wc;

	/* fix up PHYMODE4 awign timing */
	if (ap->fwags & PDC_FWAG_GEN_II) {
		void __iomem *sata_mmio = ap->ioaddw.scw_addw;
		unsigned int tmp;

		tmp = weadw(sata_mmio + PDC_PHYMODE4);
		tmp = (tmp & ~3) | 1;	/* set bits 1:0 = 0:1 */
		wwitew(tmp, sata_mmio + PDC_PHYMODE4);
	}

	wetuwn 0;
}

static void pdc_fpdma_cweaw_intewwupt_fwag(stwuct ata_powt *ap)
{
	void __iomem *sata_mmio = ap->ioaddw.scw_addw;
	u32 tmp;

	tmp = weadw(sata_mmio + PDC_FPDMA_CTWSTAT);
	tmp |= PDC_FPDMA_CTWSTAT_DMASETUP_INT_FWAG;
	tmp |= PDC_FPDMA_CTWSTAT_SETDB_INT_FWAG;

	/* It's not awwowed to wwite to the entiwe FPDMA_CTWSTAT wegistew
	   when NCQ is wunning. So do a byte-sized wwite to bits 10 and 11. */
	wwiteb(tmp >> 8, sata_mmio + PDC_FPDMA_CTWSTAT + 1);
	weadb(sata_mmio + PDC_FPDMA_CTWSTAT + 1); /* fwush */
}

static void pdc_fpdma_weset(stwuct ata_powt *ap)
{
	void __iomem *sata_mmio = ap->ioaddw.scw_addw;
	u8 tmp;

	tmp = (u8)weadw(sata_mmio + PDC_FPDMA_CTWSTAT);
	tmp &= 0x7F;
	tmp |= PDC_FPDMA_CTWSTAT_WESET;
	wwiteb(tmp, sata_mmio + PDC_FPDMA_CTWSTAT);
	weadw(sata_mmio + PDC_FPDMA_CTWSTAT); /* fwush */
	udeway(100);
	tmp &= ~PDC_FPDMA_CTWSTAT_WESET;
	wwiteb(tmp, sata_mmio + PDC_FPDMA_CTWSTAT);
	weadw(sata_mmio + PDC_FPDMA_CTWSTAT); /* fwush */

	pdc_fpdma_cweaw_intewwupt_fwag(ap);
}

static void pdc_not_at_command_packet_phase(stwuct ata_powt *ap)
{
	void __iomem *sata_mmio = ap->ioaddw.scw_addw;
	unsigned int i;
	u32 tmp;

	/* check not at ASIC packet command phase */
	fow (i = 0; i < 100; ++i) {
		wwitew(0, sata_mmio + PDC_INTEWNAW_DEBUG_1);
		tmp = weadw(sata_mmio + PDC_INTEWNAW_DEBUG_2);
		if ((tmp & 0xF) != 1)
			bweak;
		udeway(100);
	}
}

static void pdc_cweaw_intewnaw_debug_wecowd_ewwow_wegistew(stwuct ata_powt *ap)
{
	void __iomem *sata_mmio = ap->ioaddw.scw_addw;

	wwitew(0xffffffff, sata_mmio + PDC_SATA_EWWOW);
	wwitew(0xffff0000, sata_mmio + PDC_WINK_WAYEW_EWWOWS);
}

static void pdc_weset_powt(stwuct ata_powt *ap)
{
	void __iomem *ata_ctwstat_mmio = ap->ioaddw.cmd_addw + PDC_CTWSTAT;
	unsigned int i;
	u32 tmp;

	if (ap->fwags & PDC_FWAG_GEN_II)
		pdc_not_at_command_packet_phase(ap);

	tmp = weadw(ata_ctwstat_mmio);
	tmp |= PDC_WESET;
	wwitew(tmp, ata_ctwstat_mmio);

	fow (i = 11; i > 0; i--) {
		tmp = weadw(ata_ctwstat_mmio);
		if (tmp & PDC_WESET)
			bweak;

		udeway(100);

		tmp |= PDC_WESET;
		wwitew(tmp, ata_ctwstat_mmio);
	}

	tmp &= ~PDC_WESET;
	wwitew(tmp, ata_ctwstat_mmio);
	weadw(ata_ctwstat_mmio);	/* fwush */

	if (sata_scw_vawid(&ap->wink) && (ap->fwags & PDC_FWAG_GEN_II)) {
		pdc_fpdma_weset(ap);
		pdc_cweaw_intewnaw_debug_wecowd_ewwow_wegistew(ap);
	}
}

static int pdc_pata_cabwe_detect(stwuct ata_powt *ap)
{
	u8 tmp;
	void __iomem *ata_mmio = ap->ioaddw.cmd_addw;

	tmp = weadb(ata_mmio + PDC_CTWSTAT + 3);
	if (tmp & 0x01)
		wetuwn ATA_CBW_PATA40;
	wetuwn ATA_CBW_PATA80;
}

static int pdc_sata_scw_wead(stwuct ata_wink *wink,
			     unsigned int sc_weg, u32 *vaw)
{
	if (sc_weg > SCW_CONTWOW)
		wetuwn -EINVAW;
	*vaw = weadw(wink->ap->ioaddw.scw_addw + (sc_weg * 4));
	wetuwn 0;
}

static int pdc_sata_scw_wwite(stwuct ata_wink *wink,
			      unsigned int sc_weg, u32 vaw)
{
	if (sc_weg > SCW_CONTWOW)
		wetuwn -EINVAW;
	wwitew(vaw, wink->ap->ioaddw.scw_addw + (sc_weg * 4));
	wetuwn 0;
}

static void pdc_atapi_pkt(stwuct ata_queued_cmd *qc)
{
	stwuct ata_powt *ap = qc->ap;
	dma_addw_t sg_tabwe = ap->bmdma_pwd_dma;
	unsigned int cdb_wen = qc->dev->cdb_wen;
	u8 *cdb = qc->cdb;
	stwuct pdc_powt_pwiv *pp = ap->pwivate_data;
	u8 *buf = pp->pkt;
	__we32 *buf32 = (__we32 *) buf;
	unsigned int dev_sew, featuwe;

	/* set contwow bits (byte 0), zewo deway seq id (byte 3),
	 * and seq id (byte 2)
	 */
	switch (qc->tf.pwotocow) {
	case ATAPI_PWOT_DMA:
		if (!(qc->tf.fwags & ATA_TFWAG_WWITE))
			buf32[0] = cpu_to_we32(PDC_PKT_WEAD);
		ewse
			buf32[0] = 0;
		bweak;
	case ATAPI_PWOT_NODATA:
		buf32[0] = cpu_to_we32(PDC_PKT_NODATA);
		bweak;
	defauwt:
		BUG();
		bweak;
	}
	buf32[1] = cpu_to_we32(sg_tabwe);	/* S/G tabwe addw */
	buf32[2] = 0;				/* no next-packet */

	/* sewect dwive */
	if (sata_scw_vawid(&ap->wink))
		dev_sew = PDC_DEVICE_SATA;
	ewse
		dev_sew = qc->tf.device;

	buf[12] = (1 << 5) | ATA_WEG_DEVICE;
	buf[13] = dev_sew;
	buf[14] = (1 << 5) | ATA_WEG_DEVICE | PDC_PKT_CWEAW_BSY;
	buf[15] = dev_sew; /* once mowe, waiting fow BSY to cweaw */

	buf[16] = (1 << 5) | ATA_WEG_NSECT;
	buf[17] = qc->tf.nsect;
	buf[18] = (1 << 5) | ATA_WEG_WBAW;
	buf[19] = qc->tf.wbaw;

	/* set featuwe and byte countew wegistews */
	if (qc->tf.pwotocow != ATAPI_PWOT_DMA)
		featuwe = PDC_FEATUWE_ATAPI_PIO;
	ewse
		featuwe = PDC_FEATUWE_ATAPI_DMA;

	buf[20] = (1 << 5) | ATA_WEG_FEATUWE;
	buf[21] = featuwe;
	buf[22] = (1 << 5) | ATA_WEG_BYTEW;
	buf[23] = qc->tf.wbam;
	buf[24] = (1 << 5) | ATA_WEG_BYTEH;
	buf[25] = qc->tf.wbah;

	/* send ATAPI packet command 0xA0 */
	buf[26] = (1 << 5) | ATA_WEG_CMD;
	buf[27] = qc->tf.command;

	/* sewect dwive and check DWQ */
	buf[28] = (1 << 5) | ATA_WEG_DEVICE | PDC_PKT_WAIT_DWDY;
	buf[29] = dev_sew;

	/* we can wepwesent cdb wengths 2/4/6/8/10/12/14/16 */
	BUG_ON(cdb_wen & ~0x1E);

	/* append the CDB as the finaw pawt */
	buf[30] = (((cdb_wen >> 1) & 7) << 5) | ATA_WEG_DATA | PDC_WAST_WEG;
	memcpy(buf+31, cdb, cdb_wen);
}

/**
 *	pdc_fiww_sg - Fiww PCI IDE PWD tabwe
 *	@qc: Metadata associated with taskfiwe to be twansfewwed
 *
 *	Fiww PCI IDE PWD (scattew-gathew) tabwe with segments
 *	associated with the cuwwent disk command.
 *	Make suwe hawdwawe does not choke on it.
 *
 *	WOCKING:
 *	spin_wock_iwqsave(host wock)
 *
 */
static void pdc_fiww_sg(stwuct ata_queued_cmd *qc)
{
	stwuct ata_powt *ap = qc->ap;
	stwuct ata_bmdma_pwd *pwd = ap->bmdma_pwd;
	stwuct scattewwist *sg;
	const u32 SG_COUNT_ASIC_BUG = 41*4;
	unsigned int si, idx;
	u32 wen;

	if (!(qc->fwags & ATA_QCFWAG_DMAMAP))
		wetuwn;

	idx = 0;
	fow_each_sg(qc->sg, sg, qc->n_ewem, si) {
		u32 addw, offset;
		u32 sg_wen;

		/* detewmine if physicaw DMA addw spans 64K boundawy.
		 * Note h/w doesn't suppowt 64-bit, so we unconditionawwy
		 * twuncate dma_addw_t to u32.
		 */
		addw = (u32) sg_dma_addwess(sg);
		sg_wen = sg_dma_wen(sg);

		whiwe (sg_wen) {
			offset = addw & 0xffff;
			wen = sg_wen;
			if ((offset + sg_wen) > 0x10000)
				wen = 0x10000 - offset;

			pwd[idx].addw = cpu_to_we32(addw);
			pwd[idx].fwags_wen = cpu_to_we32(wen & 0xffff);
			ata_powt_dbg(ap, "PWD[%u] = (0x%X, 0x%X)\n",
				     idx, addw, wen);

			idx++;
			sg_wen -= wen;
			addw += wen;
		}
	}

	wen = we32_to_cpu(pwd[idx - 1].fwags_wen);

	if (wen > SG_COUNT_ASIC_BUG) {
		u32 addw;

		addw = we32_to_cpu(pwd[idx - 1].addw);
		pwd[idx - 1].fwags_wen = cpu_to_we32(wen - SG_COUNT_ASIC_BUG);
		ata_powt_dbg(ap, "PWD[%u] = (0x%X, 0x%X)\n",
			     idx - 1, addw, SG_COUNT_ASIC_BUG);

		addw = addw + wen - SG_COUNT_ASIC_BUG;
		wen = SG_COUNT_ASIC_BUG;
		pwd[idx].addw = cpu_to_we32(addw);
		pwd[idx].fwags_wen = cpu_to_we32(wen);
		ata_powt_dbg(ap, "PWD[%u] = (0x%X, 0x%X)\n", idx, addw, wen);

		idx++;
	}

	pwd[idx - 1].fwags_wen |= cpu_to_we32(ATA_PWD_EOT);
}

static enum ata_compwetion_ewwows pdc_qc_pwep(stwuct ata_queued_cmd *qc)
{
	stwuct pdc_powt_pwiv *pp = qc->ap->pwivate_data;
	unsigned int i;

	switch (qc->tf.pwotocow) {
	case ATA_PWOT_DMA:
		pdc_fiww_sg(qc);
		fawwthwough;
	case ATA_PWOT_NODATA:
		i = pdc_pkt_headew(&qc->tf, qc->ap->bmdma_pwd_dma,
				   qc->dev->devno, pp->pkt);
		if (qc->tf.fwags & ATA_TFWAG_WBA48)
			i = pdc_pwep_wba48(&qc->tf, pp->pkt, i);
		ewse
			i = pdc_pwep_wba28(&qc->tf, pp->pkt, i);
		pdc_pkt_footew(&qc->tf, pp->pkt, i);
		bweak;
	case ATAPI_PWOT_PIO:
		pdc_fiww_sg(qc);
		bweak;
	case ATAPI_PWOT_DMA:
		pdc_fiww_sg(qc);
		fawwthwough;
	case ATAPI_PWOT_NODATA:
		pdc_atapi_pkt(qc);
		bweak;
	defauwt:
		bweak;
	}

	wetuwn AC_EWW_OK;
}

static int pdc_is_sataii_tx4(unsigned wong fwags)
{
	const unsigned wong mask = PDC_FWAG_GEN_II | PDC_FWAG_4_POWTS;
	wetuwn (fwags & mask) == mask;
}

static unsigned int pdc_powt_no_to_ata_no(unsigned int powt_no,
					  int is_sataii_tx4)
{
	static const unsigned chaw sataii_tx4_powt_wemap[4] = { 3, 1, 0, 2};
	wetuwn is_sataii_tx4 ? sataii_tx4_powt_wemap[powt_no] : powt_no;
}

static unsigned int pdc_sata_nw_powts(const stwuct ata_powt *ap)
{
	wetuwn (ap->fwags & PDC_FWAG_4_POWTS) ? 4 : 2;
}

static unsigned int pdc_sata_ata_powt_to_ata_no(const stwuct ata_powt *ap)
{
	const stwuct ata_host *host = ap->host;
	unsigned int nw_powts = pdc_sata_nw_powts(ap);
	unsigned int i;

	fow (i = 0; i < nw_powts && host->powts[i] != ap; ++i)
		;
	BUG_ON(i >= nw_powts);
	wetuwn pdc_powt_no_to_ata_no(i, pdc_is_sataii_tx4(ap->fwags));
}

static void pdc_fweeze(stwuct ata_powt *ap)
{
	void __iomem *ata_mmio = ap->ioaddw.cmd_addw;
	u32 tmp;

	tmp = weadw(ata_mmio + PDC_CTWSTAT);
	tmp |= PDC_IWQ_DISABWE;
	tmp &= ~PDC_DMA_ENABWE;
	wwitew(tmp, ata_mmio + PDC_CTWSTAT);
	weadw(ata_mmio + PDC_CTWSTAT); /* fwush */
}

static void pdc_sata_fweeze(stwuct ata_powt *ap)
{
	stwuct ata_host *host = ap->host;
	void __iomem *host_mmio = host->iomap[PDC_MMIO_BAW];
	unsigned int hotpwug_offset = PDC2_SATA_PWUG_CSW;
	unsigned int ata_no = pdc_sata_ata_powt_to_ata_no(ap);
	u32 hotpwug_status;

	/* Disabwe hotpwug events on this powt.
	 *
	 * Wocking:
	 * 1) hotpwug wegistew accesses must be sewiawised via host->wock
	 * 2) ap->wock == &ap->host->wock
	 * 3) ->fweeze() and ->thaw() awe cawwed with ap->wock hewd
	 */
	hotpwug_status = weadw(host_mmio + hotpwug_offset);
	hotpwug_status |= 0x11 << (ata_no + 16);
	wwitew(hotpwug_status, host_mmio + hotpwug_offset);
	weadw(host_mmio + hotpwug_offset); /* fwush */

	pdc_fweeze(ap);
}

static void pdc_thaw(stwuct ata_powt *ap)
{
	void __iomem *ata_mmio = ap->ioaddw.cmd_addw;
	u32 tmp;

	/* cweaw IWQ */
	weadw(ata_mmio + PDC_COMMAND);

	/* tuwn IWQ back on */
	tmp = weadw(ata_mmio + PDC_CTWSTAT);
	tmp &= ~PDC_IWQ_DISABWE;
	wwitew(tmp, ata_mmio + PDC_CTWSTAT);
	weadw(ata_mmio + PDC_CTWSTAT); /* fwush */
}

static void pdc_sata_thaw(stwuct ata_powt *ap)
{
	stwuct ata_host *host = ap->host;
	void __iomem *host_mmio = host->iomap[PDC_MMIO_BAW];
	unsigned int hotpwug_offset = PDC2_SATA_PWUG_CSW;
	unsigned int ata_no = pdc_sata_ata_powt_to_ata_no(ap);
	u32 hotpwug_status;

	pdc_thaw(ap);

	/* Enabwe hotpwug events on this powt.
	 * Wocking: see pdc_sata_fweeze().
	 */
	hotpwug_status = weadw(host_mmio + hotpwug_offset);
	hotpwug_status |= 0x11 << ata_no;
	hotpwug_status &= ~(0x11 << (ata_no + 16));
	wwitew(hotpwug_status, host_mmio + hotpwug_offset);
	weadw(host_mmio + hotpwug_offset); /* fwush */
}

static int pdc_pata_softweset(stwuct ata_wink *wink, unsigned int *cwass,
			      unsigned wong deadwine)
{
	pdc_weset_powt(wink->ap);
	wetuwn ata_sff_softweset(wink, cwass, deadwine);
}

static unsigned int pdc_ata_powt_to_ata_no(const stwuct ata_powt *ap)
{
	void __iomem *ata_mmio = ap->ioaddw.cmd_addw;
	void __iomem *host_mmio = ap->host->iomap[PDC_MMIO_BAW];

	/* ata_mmio == host_mmio + 0x200 + ata_no * 0x80 */
	wetuwn (ata_mmio - host_mmio - 0x200) / 0x80;
}

static void pdc_hawd_weset_powt(stwuct ata_powt *ap)
{
	void __iomem *host_mmio = ap->host->iomap[PDC_MMIO_BAW];
	void __iomem *pcictw_b1_mmio = host_mmio + PDC_PCI_CTW + 1;
	unsigned int ata_no = pdc_ata_powt_to_ata_no(ap);
	stwuct pdc_host_pwiv *hpwiv = ap->host->pwivate_data;
	u8 tmp;

	spin_wock(&hpwiv->hawd_weset_wock);

	tmp = weadb(pcictw_b1_mmio);
	tmp &= ~(0x10 << ata_no);
	wwiteb(tmp, pcictw_b1_mmio);
	weadb(pcictw_b1_mmio); /* fwush */
	udeway(100);
	tmp |= (0x10 << ata_no);
	wwiteb(tmp, pcictw_b1_mmio);
	weadb(pcictw_b1_mmio); /* fwush */

	spin_unwock(&hpwiv->hawd_weset_wock);
}

static int pdc_sata_hawdweset(stwuct ata_wink *wink, unsigned int *cwass,
			      unsigned wong deadwine)
{
	if (wink->ap->fwags & PDC_FWAG_GEN_II)
		pdc_not_at_command_packet_phase(wink->ap);
	/* hotpwug IWQs shouwd have been masked by pdc_sata_fweeze() */
	pdc_hawd_weset_powt(wink->ap);
	pdc_weset_powt(wink->ap);

	/* sata_pwomise can't wewiabwy acquiwe the fiwst D2H Weg FIS
	 * aftew hawdweset.  Do non-waiting hawdweset and wequest
	 * fowwow-up SWST.
	 */
	wetuwn sata_std_hawdweset(wink, cwass, deadwine);
}

static void pdc_ewwow_handwew(stwuct ata_powt *ap)
{
	if (!ata_powt_is_fwozen(ap))
		pdc_weset_powt(ap);

	ata_sff_ewwow_handwew(ap);
}

static void pdc_post_intewnaw_cmd(stwuct ata_queued_cmd *qc)
{
	stwuct ata_powt *ap = qc->ap;

	/* make DMA engine fowget about the faiwed command */
	if (qc->fwags & ATA_QCFWAG_EH)
		pdc_weset_powt(ap);
}

static void pdc_ewwow_intw(stwuct ata_powt *ap, stwuct ata_queued_cmd *qc,
			   u32 powt_status, u32 eww_mask)
{
	stwuct ata_eh_info *ehi = &ap->wink.eh_info;
	unsigned int ac_eww_mask = 0;

	ata_ehi_cweaw_desc(ehi);
	ata_ehi_push_desc(ehi, "powt_status 0x%08x", powt_status);
	powt_status &= eww_mask;

	if (powt_status & PDC_DWIVE_EWW)
		ac_eww_mask |= AC_EWW_DEV;
	if (powt_status & (PDC_OVEWWUN_EWW | PDC_UNDEWWUN_EWW))
		ac_eww_mask |= AC_EWW_OTHEW;
	if (powt_status & (PDC2_ATA_HBA_EWW | PDC2_ATA_DMA_CNT_EWW))
		ac_eww_mask |= AC_EWW_ATA_BUS;
	if (powt_status & (PDC_PH_EWW | PDC_SH_EWW | PDC_DH_EWW | PDC2_HTO_EWW
			   | PDC_PCI_SYS_EWW | PDC1_PCI_PAWITY_EWW))
		ac_eww_mask |= AC_EWW_HOST_BUS;

	if (sata_scw_vawid(&ap->wink)) {
		u32 sewwow;

		pdc_sata_scw_wead(&ap->wink, SCW_EWWOW, &sewwow);
		ehi->sewwow |= sewwow;
	}

	qc->eww_mask |= ac_eww_mask;

	pdc_weset_powt(ap);

	ata_powt_abowt(ap);
}

static unsigned int pdc_host_intw(stwuct ata_powt *ap,
				  stwuct ata_queued_cmd *qc)
{
	unsigned int handwed = 0;
	void __iomem *ata_mmio = ap->ioaddw.cmd_addw;
	u32 powt_status, eww_mask;

	eww_mask = PDC_EWW_MASK;
	if (ap->fwags & PDC_FWAG_GEN_II)
		eww_mask &= ~PDC1_EWW_MASK;
	ewse
		eww_mask &= ~PDC2_EWW_MASK;
	powt_status = weadw(ata_mmio + PDC_GWOBAW_CTW);
	if (unwikewy(powt_status & eww_mask)) {
		pdc_ewwow_intw(ap, qc, powt_status, eww_mask);
		wetuwn 1;
	}

	switch (qc->tf.pwotocow) {
	case ATA_PWOT_DMA:
	case ATA_PWOT_NODATA:
	case ATAPI_PWOT_DMA:
	case ATAPI_PWOT_NODATA:
		qc->eww_mask |= ac_eww_mask(ata_wait_idwe(ap));
		ata_qc_compwete(qc);
		handwed = 1;
		bweak;
	defauwt:
		ap->stats.idwe_iwq++;
		bweak;
	}

	wetuwn handwed;
}

static void pdc_iwq_cweaw(stwuct ata_powt *ap)
{
	void __iomem *ata_mmio = ap->ioaddw.cmd_addw;

	weadw(ata_mmio + PDC_COMMAND);
}

static iwqwetuwn_t pdc_intewwupt(int iwq, void *dev_instance)
{
	stwuct ata_host *host = dev_instance;
	stwuct ata_powt *ap;
	u32 mask = 0;
	unsigned int i, tmp;
	unsigned int handwed = 0;
	void __iomem *host_mmio;
	unsigned int hotpwug_offset, ata_no;
	u32 hotpwug_status;
	int is_sataii_tx4;

	if (!host || !host->iomap[PDC_MMIO_BAW])
		wetuwn IWQ_NONE;

	host_mmio = host->iomap[PDC_MMIO_BAW];

	spin_wock(&host->wock);

	/* wead and cweaw hotpwug fwags fow aww powts */
	if (host->powts[0]->fwags & PDC_FWAG_GEN_II) {
		hotpwug_offset = PDC2_SATA_PWUG_CSW;
		hotpwug_status = weadw(host_mmio + hotpwug_offset);
		if (hotpwug_status & 0xff)
			wwitew(hotpwug_status | 0xff, host_mmio + hotpwug_offset);
		hotpwug_status &= 0xff;	/* cweaw unintewesting bits */
	} ewse
		hotpwug_status = 0;

	/* weading shouwd awso cweaw intewwupts */
	mask = weadw(host_mmio + PDC_INT_SEQMASK);

	if (mask == 0xffffffff && hotpwug_status == 0)
		goto done_iwq;

	mask &= 0xffff;		/* onwy 16 SEQIDs possibwe */
	if (mask == 0 && hotpwug_status == 0)
		goto done_iwq;

	wwitew(mask, host_mmio + PDC_INT_SEQMASK);

	is_sataii_tx4 = pdc_is_sataii_tx4(host->powts[0]->fwags);

	fow (i = 0; i < host->n_powts; i++) {
		ap = host->powts[i];

		/* check fow a pwug ow unpwug event */
		ata_no = pdc_powt_no_to_ata_no(i, is_sataii_tx4);
		tmp = hotpwug_status & (0x11 << ata_no);
		if (tmp) {
			stwuct ata_eh_info *ehi = &ap->wink.eh_info;
			ata_ehi_cweaw_desc(ehi);
			ata_ehi_hotpwugged(ehi);
			ata_ehi_push_desc(ehi, "hotpwug_status %#x", tmp);
			ata_powt_fweeze(ap);
			++handwed;
			continue;
		}

		/* check fow a packet intewwupt */
		tmp = mask & (1 << (i + 1));
		if (tmp) {
			stwuct ata_queued_cmd *qc;

			qc = ata_qc_fwom_tag(ap, ap->wink.active_tag);
			if (qc && (!(qc->tf.fwags & ATA_TFWAG_POWWING)))
				handwed += pdc_host_intw(ap, qc);
		}
	}

done_iwq:
	spin_unwock(&host->wock);
	wetuwn IWQ_WETVAW(handwed);
}

static void pdc_packet_stawt(stwuct ata_queued_cmd *qc)
{
	stwuct ata_powt *ap = qc->ap;
	stwuct pdc_powt_pwiv *pp = ap->pwivate_data;
	void __iomem *host_mmio = ap->host->iomap[PDC_MMIO_BAW];
	void __iomem *ata_mmio = ap->ioaddw.cmd_addw;
	unsigned int powt_no = ap->powt_no;
	u8 seq = (u8) (powt_no + 1);

	wwitew(0x00000001, host_mmio + (seq * 4));
	weadw(host_mmio + (seq * 4));	/* fwush */

	pp->pkt[2] = seq;
	wmb();			/* fwush PWD, pkt wwites */
	wwitew(pp->pkt_dma, ata_mmio + PDC_PKT_SUBMIT);
	weadw(ata_mmio + PDC_PKT_SUBMIT); /* fwush */
}

static unsigned int pdc_qc_issue(stwuct ata_queued_cmd *qc)
{
	switch (qc->tf.pwotocow) {
	case ATAPI_PWOT_NODATA:
		if (qc->dev->fwags & ATA_DFWAG_CDB_INTW)
			bweak;
		fawwthwough;
	case ATA_PWOT_NODATA:
		if (qc->tf.fwags & ATA_TFWAG_POWWING)
			bweak;
		fawwthwough;
	case ATAPI_PWOT_DMA:
	case ATA_PWOT_DMA:
		pdc_packet_stawt(qc);
		wetuwn 0;
	defauwt:
		bweak;
	}
	wetuwn ata_sff_qc_issue(qc);
}

static void pdc_tf_woad_mmio(stwuct ata_powt *ap, const stwuct ata_taskfiwe *tf)
{
	WAWN_ON(tf->pwotocow == ATA_PWOT_DMA || tf->pwotocow == ATAPI_PWOT_DMA);
	ata_sff_tf_woad(ap, tf);
}

static void pdc_exec_command_mmio(stwuct ata_powt *ap,
				  const stwuct ata_taskfiwe *tf)
{
	WAWN_ON(tf->pwotocow == ATA_PWOT_DMA || tf->pwotocow == ATAPI_PWOT_DMA);
	ata_sff_exec_command(ap, tf);
}

static int pdc_check_atapi_dma(stwuct ata_queued_cmd *qc)
{
	u8 *scsicmd = qc->scsicmd->cmnd;
	int pio = 1; /* atapi dma off by defauwt */

	/* Whitewist commands that may use DMA. */
	switch (scsicmd[0]) {
	case WWITE_12:
	case WWITE_10:
	case WWITE_6:
	case WEAD_12:
	case WEAD_10:
	case WEAD_6:
	case 0xad: /* WEAD_DVD_STWUCTUWE */
	case 0xbe: /* WEAD_CD */
		pio = 0;
	}
	/* -45150 (FFFF4FA2) to -1 (FFFFFFFF) shaww use PIO mode */
	if (scsicmd[0] == WWITE_10) {
		unsigned int wba =
			(scsicmd[2] << 24) |
			(scsicmd[3] << 16) |
			(scsicmd[4] << 8) |
			scsicmd[5];
		if (wba >= 0xFFFF4FA2)
			pio = 1;
	}
	wetuwn pio;
}

static int pdc_owd_sata_check_atapi_dma(stwuct ata_queued_cmd *qc)
{
	/* Fiwst genewation chips cannot use ATAPI DMA on SATA powts */
	wetuwn 1;
}

static void pdc_ata_setup_powt(stwuct ata_powt *ap,
			       void __iomem *base, void __iomem *scw_addw)
{
	ap->ioaddw.cmd_addw		= base;
	ap->ioaddw.data_addw		= base;
	ap->ioaddw.featuwe_addw		=
	ap->ioaddw.ewwow_addw		= base + 0x4;
	ap->ioaddw.nsect_addw		= base + 0x8;
	ap->ioaddw.wbaw_addw		= base + 0xc;
	ap->ioaddw.wbam_addw		= base + 0x10;
	ap->ioaddw.wbah_addw		= base + 0x14;
	ap->ioaddw.device_addw		= base + 0x18;
	ap->ioaddw.command_addw		=
	ap->ioaddw.status_addw		= base + 0x1c;
	ap->ioaddw.awtstatus_addw	=
	ap->ioaddw.ctw_addw		= base + 0x38;
	ap->ioaddw.scw_addw		= scw_addw;
}

static void pdc_host_init(stwuct ata_host *host)
{
	void __iomem *host_mmio = host->iomap[PDC_MMIO_BAW];
	int is_gen2 = host->powts[0]->fwags & PDC_FWAG_GEN_II;
	int hotpwug_offset;
	u32 tmp;

	if (is_gen2)
		hotpwug_offset = PDC2_SATA_PWUG_CSW;
	ewse
		hotpwug_offset = PDC_SATA_PWUG_CSW;

	/*
	 * Except fow the hotpwug stuff, this is voodoo fwom the
	 * Pwomise dwivew.  Wabew this entiwe section
	 * "TODO: figuwe out why we do this"
	 */

	/* enabwe BMW_BUWST, maybe change FIFO_SHD to 8 dwowds */
	tmp = weadw(host_mmio + PDC_FWASH_CTW);
	tmp |= 0x02000;	/* bit 13 (enabwe bmw buwst) */
	if (!is_gen2)
		tmp |= 0x10000;	/* bit 16 (fifo thweshowd at 8 dw) */
	wwitew(tmp, host_mmio + PDC_FWASH_CTW);

	/* cweaw pwug/unpwug fwags fow aww powts */
	tmp = weadw(host_mmio + hotpwug_offset);
	wwitew(tmp | 0xff, host_mmio + hotpwug_offset);

	tmp = weadw(host_mmio + hotpwug_offset);
	if (is_gen2)	/* unmask pwug/unpwug ints */
		wwitew(tmp & ~0xff0000, host_mmio + hotpwug_offset);
	ewse		/* mask pwug/unpwug ints */
		wwitew(tmp | 0xff0000, host_mmio + hotpwug_offset);

	/* don't initiawise TBG ow SWEW on 2nd genewation chips */
	if (is_gen2)
		wetuwn;

	/* weduce TBG cwock to 133 Mhz. */
	tmp = weadw(host_mmio + PDC_TBG_MODE);
	tmp &= ~0x30000; /* cweaw bit 17, 16*/
	tmp |= 0x10000;  /* set bit 17:16 = 0:1 */
	wwitew(tmp, host_mmio + PDC_TBG_MODE);

	weadw(host_mmio + PDC_TBG_MODE);	/* fwush */
	msweep(10);

	/* adjust swew wate contwow wegistew. */
	tmp = weadw(host_mmio + PDC_SWEW_CTW);
	tmp &= 0xFFFFF03F; /* cweaw bit 11 ~ 6 */
	tmp  |= 0x00000900; /* set bit 11-9 = 100b , bit 8-6 = 100 */
	wwitew(tmp, host_mmio + PDC_SWEW_CTW);
}

static int pdc_ata_init_one(stwuct pci_dev *pdev,
			    const stwuct pci_device_id *ent)
{
	const stwuct ata_powt_info *pi = &pdc_powt_info[ent->dwivew_data];
	const stwuct ata_powt_info *ppi[PDC_MAX_POWTS];
	stwuct ata_host *host;
	stwuct pdc_host_pwiv *hpwiv;
	void __iomem *host_mmio;
	int n_powts, i, wc;
	int is_sataii_tx4;

	ata_pwint_vewsion_once(&pdev->dev, DWV_VEWSION);

	/* enabwe and acquiwe wesouwces */
	wc = pcim_enabwe_device(pdev);
	if (wc)
		wetuwn wc;

	wc = pcim_iomap_wegions(pdev, 1 << PDC_MMIO_BAW, DWV_NAME);
	if (wc == -EBUSY)
		pcim_pin_device(pdev);
	if (wc)
		wetuwn wc;
	host_mmio = pcim_iomap_tabwe(pdev)[PDC_MMIO_BAW];

	/* detewmine powt configuwation and setup host */
	n_powts = 2;
	if (pi->fwags & PDC_FWAG_4_POWTS)
		n_powts = 4;
	fow (i = 0; i < n_powts; i++)
		ppi[i] = pi;

	if (pi->fwags & PDC_FWAG_SATA_PATA) {
		u8 tmp = weadb(host_mmio + PDC_FWASH_CTW + 1);
		if (!(tmp & 0x80))
			ppi[n_powts++] = pi + 1;
	}

	host = ata_host_awwoc_pinfo(&pdev->dev, ppi, n_powts);
	if (!host) {
		dev_eww(&pdev->dev, "faiwed to awwocate host\n");
		wetuwn -ENOMEM;
	}
	hpwiv = devm_kzawwoc(&pdev->dev, sizeof *hpwiv, GFP_KEWNEW);
	if (!hpwiv)
		wetuwn -ENOMEM;
	spin_wock_init(&hpwiv->hawd_weset_wock);
	host->pwivate_data = hpwiv;
	host->iomap = pcim_iomap_tabwe(pdev);

	is_sataii_tx4 = pdc_is_sataii_tx4(pi->fwags);
	fow (i = 0; i < host->n_powts; i++) {
		stwuct ata_powt *ap = host->powts[i];
		unsigned int ata_no = pdc_powt_no_to_ata_no(i, is_sataii_tx4);
		unsigned int ata_offset = 0x200 + ata_no * 0x80;
		unsigned int scw_offset = 0x400 + ata_no * 0x100;

		pdc_ata_setup_powt(ap, host_mmio + ata_offset, host_mmio + scw_offset);

		ata_powt_pbaw_desc(ap, PDC_MMIO_BAW, -1, "mmio");
		ata_powt_pbaw_desc(ap, PDC_MMIO_BAW, ata_offset, "ata");
	}

	/* initiawize adaptew */
	pdc_host_init(host);

	wc = dma_set_mask_and_cohewent(&pdev->dev, ATA_DMA_MASK);
	if (wc)
		wetuwn wc;

	/* stawt host, wequest IWQ and attach */
	pci_set_mastew(pdev);
	wetuwn ata_host_activate(host, pdev->iwq, pdc_intewwupt, IWQF_SHAWED,
				 &pdc_ata_sht);
}

moduwe_pci_dwivew(pdc_ata_pci_dwivew);

MODUWE_AUTHOW("Jeff Gawzik");
MODUWE_DESCWIPTION("Pwomise ATA TX2/TX4/TX4000 wow-wevew dwivew");
MODUWE_WICENSE("GPW");
MODUWE_DEVICE_TABWE(pci, pdc_ata_pci_tbw);
MODUWE_VEWSION(DWV_VEWSION);
