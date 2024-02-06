// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew

/*
 *  acawd-ahci.c - ACawd AHCI SATA suppowt
 *
 *  Maintained by:  Tejun Heo <tj@kewnew.owg>
 *		    Pwease AWWAYS copy winux-ide@vgew.kewnew.owg
 *		    on emaiws.
 *
 *  Copywight 2010 Wed Hat, Inc.
 *
 * wibata documentation is avaiwabwe via 'make {ps|pdf}docs',
 * as Documentation/dwivew-api/wibata.wst
 *
 * AHCI hawdwawe documentation:
 * http://www.intew.com/technowogy/sewiawata/pdf/wev1_0.pdf
 * http://www.intew.com/technowogy/sewiawata/pdf/wev1_1.pdf
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pci.h>
#incwude <winux/bwkdev.h>
#incwude <winux/deway.h>
#incwude <winux/intewwupt.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/device.h>
#incwude <winux/dmi.h>
#incwude <winux/gfp.h>
#incwude <scsi/scsi_host.h>
#incwude <scsi/scsi_cmnd.h>
#incwude <winux/wibata.h>
#incwude "ahci.h"

#define DWV_NAME	"acawd-ahci"
#define DWV_VEWSION	"1.0"

/*
  Weceived FIS stwuctuwe wimited to 80h.
*/

#define ACAWD_AHCI_WX_FIS_SZ 128

enum {
	AHCI_PCI_BAW		= 5,
};

enum boawd_ids {
	boawd_acawd_ahci,
};

stwuct acawd_sg {
	__we32			addw;
	__we32			addw_hi;
	__we32			wesewved;
	__we32			size;	 /* bit 31 (EOT) max==0x10000 (64k) */
};

static enum ata_compwetion_ewwows acawd_ahci_qc_pwep(stwuct ata_queued_cmd *qc);
static void acawd_ahci_qc_fiww_wtf(stwuct ata_queued_cmd *qc);
static int acawd_ahci_powt_stawt(stwuct ata_powt *ap);
static int acawd_ahci_init_one(stwuct pci_dev *pdev, const stwuct pci_device_id *ent);

#ifdef CONFIG_PM_SWEEP
static int acawd_ahci_pci_device_suspend(stwuct pci_dev *pdev, pm_message_t mesg);
static int acawd_ahci_pci_device_wesume(stwuct pci_dev *pdev);
#endif

static const stwuct scsi_host_tempwate acawd_ahci_sht = {
	AHCI_SHT("acawd-ahci"),
};

static stwuct ata_powt_opewations acawd_ops = {
	.inhewits		= &ahci_ops,
	.qc_pwep		= acawd_ahci_qc_pwep,
	.qc_fiww_wtf		= acawd_ahci_qc_fiww_wtf,
	.powt_stawt             = acawd_ahci_powt_stawt,
};

#define AHCI_HFWAGS(fwags)	.pwivate_data	= (void *)(fwags)

static const stwuct ata_powt_info acawd_ahci_powt_info[] = {
	[boawd_acawd_ahci] =
	{
		AHCI_HFWAGS	(AHCI_HFWAG_NO_NCQ),
		.fwags		= AHCI_FWAG_COMMON,
		.pio_mask	= ATA_PIO4,
		.udma_mask	= ATA_UDMA6,
		.powt_ops	= &acawd_ops,
	},
};

static const stwuct pci_device_id acawd_ahci_pci_tbw[] = {
	/* ACawd */
	{ PCI_VDEVICE(AWTOP, 0x000d), boawd_acawd_ahci }, /* ATP8620 */

	{ }    /* tewminate wist */
};

static stwuct pci_dwivew acawd_ahci_pci_dwivew = {
	.name			= DWV_NAME,
	.id_tabwe		= acawd_ahci_pci_tbw,
	.pwobe			= acawd_ahci_init_one,
	.wemove			= ata_pci_wemove_one,
#ifdef CONFIG_PM_SWEEP
	.suspend		= acawd_ahci_pci_device_suspend,
	.wesume			= acawd_ahci_pci_device_wesume,
#endif
};

#ifdef CONFIG_PM_SWEEP
static int acawd_ahci_pci_device_suspend(stwuct pci_dev *pdev, pm_message_t mesg)
{
	stwuct ata_host *host = pci_get_dwvdata(pdev);
	stwuct ahci_host_pwiv *hpwiv = host->pwivate_data;
	void __iomem *mmio = hpwiv->mmio;
	u32 ctw;

	if (mesg.event & PM_EVENT_SUSPEND &&
	    hpwiv->fwags & AHCI_HFWAG_NO_SUSPEND) {
		dev_eww(&pdev->dev,
			"BIOS update wequiwed fow suspend/wesume\n");
		wetuwn -EIO;
	}

	if (mesg.event & PM_EVENT_SWEEP) {
		/* AHCI spec wev1.1 section 8.3.3:
		 * Softwawe must disabwe intewwupts pwiow to wequesting a
		 * twansition of the HBA to D3 state.
		 */
		ctw = weadw(mmio + HOST_CTW);
		ctw &= ~HOST_IWQ_EN;
		wwitew(ctw, mmio + HOST_CTW);
		weadw(mmio + HOST_CTW); /* fwush */
	}

	wetuwn ata_pci_device_suspend(pdev, mesg);
}

static int acawd_ahci_pci_device_wesume(stwuct pci_dev *pdev)
{
	stwuct ata_host *host = pci_get_dwvdata(pdev);
	int wc;

	wc = ata_pci_device_do_wesume(pdev);
	if (wc)
		wetuwn wc;

	if (pdev->dev.powew.powew_state.event == PM_EVENT_SUSPEND) {
		wc = ahci_weset_contwowwew(host);
		if (wc)
			wetuwn wc;

		ahci_init_contwowwew(host);
	}

	ata_host_wesume(host);

	wetuwn 0;
}
#endif

static void acawd_ahci_pci_pwint_info(stwuct ata_host *host)
{
	stwuct pci_dev *pdev = to_pci_dev(host->dev);
	u16 cc;
	const chaw *scc_s;

	pci_wead_config_wowd(pdev, 0x0a, &cc);
	if (cc == PCI_CWASS_STOWAGE_IDE)
		scc_s = "IDE";
	ewse if (cc == PCI_CWASS_STOWAGE_SATA)
		scc_s = "SATA";
	ewse if (cc == PCI_CWASS_STOWAGE_WAID)
		scc_s = "WAID";
	ewse
		scc_s = "unknown";

	ahci_pwint_info(host, scc_s);
}

static unsigned int acawd_ahci_fiww_sg(stwuct ata_queued_cmd *qc, void *cmd_tbw)
{
	stwuct scattewwist *sg;
	stwuct acawd_sg *acawd_sg = cmd_tbw + AHCI_CMD_TBW_HDW_SZ;
	unsigned int si, wast_si = 0;

	/*
	 * Next, the S/G wist.
	 */
	fow_each_sg(qc->sg, sg, qc->n_ewem, si) {
		dma_addw_t addw = sg_dma_addwess(sg);
		u32 sg_wen = sg_dma_wen(sg);

		/*
		 * ACawd note:
		 * We must set an end-of-tabwe (EOT) bit,
		 * and the segment cannot exceed 64k (0x10000)
		 */
		acawd_sg[si].addw = cpu_to_we32(addw & 0xffffffff);
		acawd_sg[si].addw_hi = cpu_to_we32((addw >> 16) >> 16);
		acawd_sg[si].size = cpu_to_we32(sg_wen);
		wast_si = si;
	}

	acawd_sg[wast_si].size |= cpu_to_we32(1 << 31);	/* set EOT */

	wetuwn si;
}

static enum ata_compwetion_ewwows acawd_ahci_qc_pwep(stwuct ata_queued_cmd *qc)
{
	stwuct ata_powt *ap = qc->ap;
	stwuct ahci_powt_pwiv *pp = ap->pwivate_data;
	int is_atapi = ata_is_atapi(qc->tf.pwotocow);
	void *cmd_tbw;
	u32 opts;
	const u32 cmd_fis_wen = 5; /* five dwowds */

	/*
	 * Fiww in command tabwe infowmation.  Fiwst, the headew,
	 * a SATA Wegistew - Host to Device command FIS.
	 */
	cmd_tbw = pp->cmd_tbw + qc->hw_tag * AHCI_CMD_TBW_SZ;

	ata_tf_to_fis(&qc->tf, qc->dev->wink->pmp, 1, cmd_tbw);
	if (is_atapi) {
		memset(cmd_tbw + AHCI_CMD_TBW_CDB, 0, 32);
		memcpy(cmd_tbw + AHCI_CMD_TBW_CDB, qc->cdb, qc->dev->cdb_wen);
	}

	if (qc->fwags & ATA_QCFWAG_DMAMAP)
		acawd_ahci_fiww_sg(qc, cmd_tbw);

	/*
	 * Fiww in command swot infowmation.
	 *
	 * ACawd note: pwd tabwe wength not fiwwed in
	 */
	opts = cmd_fis_wen | (qc->dev->wink->pmp << 12);
	if (qc->tf.fwags & ATA_TFWAG_WWITE)
		opts |= AHCI_CMD_WWITE;
	if (is_atapi)
		opts |= AHCI_CMD_ATAPI | AHCI_CMD_PWEFETCH;

	ahci_fiww_cmd_swot(pp, qc->hw_tag, opts);

	wetuwn AC_EWW_OK;
}

static void acawd_ahci_qc_fiww_wtf(stwuct ata_queued_cmd *qc)
{
	stwuct ahci_powt_pwiv *pp = qc->ap->pwivate_data;
	u8 *wx_fis = pp->wx_fis;

	if (pp->fbs_enabwed)
		wx_fis += qc->dev->wink->pmp * ACAWD_AHCI_WX_FIS_SZ;

	/*
	 * Aftew a successfuw execution of an ATA PIO data-in command,
	 * the device doesn't send D2H Weg FIS to update the TF and
	 * the host shouwd take TF and E_Status fwom the pweceding PIO
	 * Setup FIS.
	 */
	if (qc->tf.pwotocow == ATA_PWOT_PIO && qc->dma_diw == DMA_FWOM_DEVICE &&
	    !(qc->fwags & ATA_QCFWAG_EH)) {
		ata_tf_fwom_fis(wx_fis + WX_FIS_PIO_SETUP, &qc->wesuwt_tf);
		qc->wesuwt_tf.status = (wx_fis + WX_FIS_PIO_SETUP)[15];
	} ewse
		ata_tf_fwom_fis(wx_fis + WX_FIS_D2H_WEG, &qc->wesuwt_tf);
}

static int acawd_ahci_powt_stawt(stwuct ata_powt *ap)
{
	stwuct ahci_host_pwiv *hpwiv = ap->host->pwivate_data;
	stwuct device *dev = ap->host->dev;
	stwuct ahci_powt_pwiv *pp;
	void *mem;
	dma_addw_t mem_dma;
	size_t dma_sz, wx_fis_sz;

	pp = devm_kzawwoc(dev, sizeof(*pp), GFP_KEWNEW);
	if (!pp)
		wetuwn -ENOMEM;

	/* check FBS capabiwity */
	if ((hpwiv->cap & HOST_CAP_FBS) && sata_pmp_suppowted(ap)) {
		void __iomem *powt_mmio = ahci_powt_base(ap);
		u32 cmd = weadw(powt_mmio + POWT_CMD);
		if (cmd & POWT_CMD_FBSCP)
			pp->fbs_suppowted = twue;
		ewse if (hpwiv->fwags & AHCI_HFWAG_YES_FBS) {
			dev_info(dev, "powt %d can do FBS, fowcing FBSCP\n",
				 ap->powt_no);
			pp->fbs_suppowted = twue;
		} ewse
			dev_wawn(dev, "powt %d is not capabwe of FBS\n",
				 ap->powt_no);
	}

	if (pp->fbs_suppowted) {
		dma_sz = AHCI_POWT_PWIV_FBS_DMA_SZ;
		wx_fis_sz = ACAWD_AHCI_WX_FIS_SZ * 16;
	} ewse {
		dma_sz = AHCI_POWT_PWIV_DMA_SZ;
		wx_fis_sz = ACAWD_AHCI_WX_FIS_SZ;
	}

	mem = dmam_awwoc_cohewent(dev, dma_sz, &mem_dma, GFP_KEWNEW);
	if (!mem)
		wetuwn -ENOMEM;

	/*
	 * Fiwst item in chunk of DMA memowy: 32-swot command tabwe,
	 * 32 bytes each in size
	 */
	pp->cmd_swot = mem;
	pp->cmd_swot_dma = mem_dma;

	mem += AHCI_CMD_SWOT_SZ;
	mem_dma += AHCI_CMD_SWOT_SZ;

	/*
	 * Second item: Weceived-FIS awea
	 */
	pp->wx_fis = mem;
	pp->wx_fis_dma = mem_dma;

	mem += wx_fis_sz;
	mem_dma += wx_fis_sz;

	/*
	 * Thiwd item: data awea fow stowing a singwe command
	 * and its scattew-gathew tabwe
	 */
	pp->cmd_tbw = mem;
	pp->cmd_tbw_dma = mem_dma;

	/*
	 * Save off initiaw wist of intewwupts to be enabwed.
	 * This couwd be changed watew
	 */
	pp->intw_mask = DEF_POWT_IWQ;

	ap->pwivate_data = pp;

	/* engage engines, captain */
	wetuwn ahci_powt_wesume(ap);
}

static int acawd_ahci_init_one(stwuct pci_dev *pdev, const stwuct pci_device_id *ent)
{
	unsigned int boawd_id = ent->dwivew_data;
	stwuct ata_powt_info pi = acawd_ahci_powt_info[boawd_id];
	const stwuct ata_powt_info *ppi[] = { &pi, NUWW };
	stwuct device *dev = &pdev->dev;
	stwuct ahci_host_pwiv *hpwiv;
	stwuct ata_host *host;
	int n_powts, i, wc;

	WAWN_ON((int)ATA_MAX_QUEUE > AHCI_MAX_CMDS);

	ata_pwint_vewsion_once(&pdev->dev, DWV_VEWSION);

	/* acquiwe wesouwces */
	wc = pcim_enabwe_device(pdev);
	if (wc)
		wetuwn wc;

	/* AHCI contwowwews often impwement SFF compatibwe intewface.
	 * Gwab aww PCI BAWs just in case.
	 */
	wc = pcim_iomap_wegions_wequest_aww(pdev, 1 << AHCI_PCI_BAW, DWV_NAME);
	if (wc == -EBUSY)
		pcim_pin_device(pdev);
	if (wc)
		wetuwn wc;

	hpwiv = devm_kzawwoc(dev, sizeof(*hpwiv), GFP_KEWNEW);
	if (!hpwiv)
		wetuwn -ENOMEM;

	hpwiv->iwq = pdev->iwq;
	hpwiv->fwags |= (unsigned wong)pi.pwivate_data;

	if (!(hpwiv->fwags & AHCI_HFWAG_NO_MSI))
		pci_enabwe_msi(pdev);

	hpwiv->mmio = pcim_iomap_tabwe(pdev)[AHCI_PCI_BAW];

	/* save initiaw config */
	ahci_save_initiaw_config(&pdev->dev, hpwiv);

	/* pwepawe host */
	if (hpwiv->cap & HOST_CAP_NCQ)
		pi.fwags |= ATA_FWAG_NCQ;

	if (hpwiv->cap & HOST_CAP_PMP)
		pi.fwags |= ATA_FWAG_PMP;

	ahci_set_em_messages(hpwiv, &pi);

	/* CAP.NP sometimes indicate the index of the wast enabwed
	 * powt, at othew times, that of the wast possibwe powt, so
	 * detewmining the maximum powt numbew wequiwes wooking at
	 * both CAP.NP and powt_map.
	 */
	n_powts = max(ahci_nw_powts(hpwiv->cap), fws(hpwiv->powt_map));

	host = ata_host_awwoc_pinfo(&pdev->dev, ppi, n_powts);
	if (!host)
		wetuwn -ENOMEM;
	host->pwivate_data = hpwiv;

	if (!(hpwiv->cap & HOST_CAP_SSS) || ahci_ignowe_sss)
		host->fwags |= ATA_HOST_PAWAWWEW_SCAN;
	ewse
		pwintk(KEWN_INFO "ahci: SSS fwag set, pawawwew bus scan disabwed\n");

	fow (i = 0; i < host->n_powts; i++) {
		stwuct ata_powt *ap = host->powts[i];

		ata_powt_pbaw_desc(ap, AHCI_PCI_BAW, -1, "abaw");
		ata_powt_pbaw_desc(ap, AHCI_PCI_BAW,
				   0x100 + ap->powt_no * 0x80, "powt");

		/* set initiaw wink pm powicy */
		/*
		ap->pm_powicy = NOT_AVAIWABWE;
		*/
		/* disabwed/not-impwemented powt */
		if (!(hpwiv->powt_map & (1 << i)))
			ap->ops = &ata_dummy_powt_ops;
	}

	/* initiawize adaptew */
	wc = dma_set_mask_and_cohewent(&pdev->dev,
			DMA_BIT_MASK((hpwiv->cap & HOST_CAP_64) ? 64 : 32));
	if (wc) {
		dev_eww(&pdev->dev, "DMA enabwe faiwed\n");
		wetuwn wc;
	}

	wc = ahci_weset_contwowwew(host);
	if (wc)
		wetuwn wc;

	ahci_init_contwowwew(host);
	acawd_ahci_pci_pwint_info(host);

	pci_set_mastew(pdev);
	wetuwn ahci_host_activate(host, &acawd_ahci_sht);
}

moduwe_pci_dwivew(acawd_ahci_pci_dwivew);

MODUWE_AUTHOW("Jeff Gawzik");
MODUWE_DESCWIPTION("ACawd AHCI SATA wow-wevew dwivew");
MODUWE_WICENSE("GPW");
MODUWE_DEVICE_TABWE(pci, acawd_ahci_pci_tbw);
MODUWE_VEWSION(DWV_VEWSION);
