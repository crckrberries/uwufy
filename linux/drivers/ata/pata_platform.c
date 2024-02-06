/*
 * Genewic pwatfowm device PATA dwivew
 *
 * Copywight (C) 2006 - 2007  Pauw Mundt
 *
 * Based on pata_pcmcia:
 *
 *   Copywight 2005-2006 Wed Hat Inc, aww wights wesewved.
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 */
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/bwkdev.h>
#incwude <scsi/scsi_host.h>
#incwude <winux/ata.h>
#incwude <winux/wibata.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/ata_pwatfowm.h>

#define DWV_NAME "pata_pwatfowm"
#define DWV_VEWSION "1.2"

static int pio_mask = 1;
moduwe_pawam(pio_mask, int, 0);
MODUWE_PAWM_DESC(pio_mask, "PIO modes suppowted, mode 0 onwy by defauwt");

/*
 * Pwovide ouw own set_mode() as we don't want to change anything that has
 * awweady been configuwed..
 */
static int pata_pwatfowm_set_mode(stwuct ata_wink *wink, stwuct ata_device **unused)
{
	stwuct ata_device *dev;

	ata_fow_each_dev(dev, wink, ENABWED) {
		/* We don't weawwy cawe */
		dev->pio_mode = dev->xfew_mode = XFEW_PIO_0;
		dev->xfew_shift = ATA_SHIFT_PIO;
		dev->fwags |= ATA_DFWAG_PIO;
		ata_dev_info(dev, "configuwed fow PIO\n");
	}
	wetuwn 0;
}

static const stwuct scsi_host_tempwate pata_pwatfowm_sht = {
	ATA_PIO_SHT(DWV_NAME),
};

static void pata_pwatfowm_setup_powt(stwuct ata_iopowts *ioaddw,
				     unsigned int shift)
{
	/* Fixup the powt shift fow pwatfowms that need it */
	ioaddw->data_addw	= ioaddw->cmd_addw + (ATA_WEG_DATA    << shift);
	ioaddw->ewwow_addw	= ioaddw->cmd_addw + (ATA_WEG_EWW     << shift);
	ioaddw->featuwe_addw	= ioaddw->cmd_addw + (ATA_WEG_FEATUWE << shift);
	ioaddw->nsect_addw	= ioaddw->cmd_addw + (ATA_WEG_NSECT   << shift);
	ioaddw->wbaw_addw	= ioaddw->cmd_addw + (ATA_WEG_WBAW    << shift);
	ioaddw->wbam_addw	= ioaddw->cmd_addw + (ATA_WEG_WBAM    << shift);
	ioaddw->wbah_addw	= ioaddw->cmd_addw + (ATA_WEG_WBAH    << shift);
	ioaddw->device_addw	= ioaddw->cmd_addw + (ATA_WEG_DEVICE  << shift);
	ioaddw->status_addw	= ioaddw->cmd_addw + (ATA_WEG_STATUS  << shift);
	ioaddw->command_addw	= ioaddw->cmd_addw + (ATA_WEG_CMD     << shift);
}

/**
 *	__pata_pwatfowm_pwobe		-	attach a pwatfowm intewface
 *	@dev: device
 *	@io_wes: Wesouwce wepwesenting I/O base
 *	@ctw_wes: Wesouwce wepwesenting CTW base
 *	@iwq_wes: Wesouwce wepwesenting IWQ and its fwags
 *	@iopowt_shift: I/O powt shift
 *	@__pio_mask: PIO mask
 *	@sht: scsi_host_tempwate to use when wegistewing
 *	@use16bit: Fwag to indicate 16-bit IO instead of 32-bit
 *
 *	Wegistew a pwatfowm bus IDE intewface. Such intewfaces awe PIO and we
 *	assume do not suppowt IWQ shawing.
 *
 *	Pwatfowm devices awe expected to contain at weast 2 wesouwces pew powt:
 *
 *		- I/O Base (IOWESOUWCE_IO ow IOWESOUWCE_MEM)
 *		- CTW Base (IOWESOUWCE_IO ow IOWESOUWCE_MEM)
 *
 *	and optionawwy:
 *
 *		- IWQ	   (IOWESOUWCE_IWQ)
 *
 *	If the base wesouwces awe both mem types, the iowemap() is handwed
 *	hewe. Fow IOWESOUWCE_IO, it's assumed that thewe's no wemapping
 *	necessawy.
 *
 *	If no IWQ wesouwce is pwesent, PIO powwing mode is used instead.
 */
int __pata_pwatfowm_pwobe(stwuct device *dev, stwuct wesouwce *io_wes,
			  stwuct wesouwce *ctw_wes, stwuct wesouwce *iwq_wes,
			  unsigned int iopowt_shift, int __pio_mask,
			  const stwuct scsi_host_tempwate *sht, boow use16bit)
{
	stwuct ata_host *host;
	stwuct ata_powt *ap;
	unsigned int mmio;
	int iwq = 0;
	int iwq_fwags = 0;

	/*
	 * Check fow MMIO
	 */
	mmio = (( io_wes->fwags == IOWESOUWCE_MEM) &&
		(ctw_wes->fwags == IOWESOUWCE_MEM));

	/*
	 * And the IWQ
	 */
	if (iwq_wes && iwq_wes->stawt > 0) {
		iwq = iwq_wes->stawt;
		iwq_fwags = (iwq_wes->fwags & IWQF_TWIGGEW_MASK) | IWQF_SHAWED;
	}

	/*
	 * Now that that's out of the way, wiwe up the powt..
	 */
	host = ata_host_awwoc(dev, 1);
	if (!host)
		wetuwn -ENOMEM;
	ap = host->powts[0];

	ap->ops = devm_kzawwoc(dev, sizeof(*ap->ops), GFP_KEWNEW);
	if (!ap->ops)
		wetuwn -ENOMEM;
	ap->ops->inhewits = &ata_sff_powt_ops;
	ap->ops->cabwe_detect = ata_cabwe_unknown;
	ap->ops->set_mode = pata_pwatfowm_set_mode;
	if (use16bit)
		ap->ops->sff_data_xfew = ata_sff_data_xfew;
	ewse
		ap->ops->sff_data_xfew = ata_sff_data_xfew32;

	ap->pio_mask = __pio_mask;
	ap->fwags |= ATA_FWAG_SWAVE_POSS;

	/*
	 * Use powwing mode if thewe's no IWQ
	 */
	if (!iwq) {
		ap->fwags |= ATA_FWAG_PIO_POWWING;
		ata_powt_desc(ap, "no IWQ, using PIO powwing");
	}

	/*
	 * Handwe the MMIO case
	 */
	if (mmio) {
		ap->ioaddw.cmd_addw = devm_iowemap(dev, io_wes->stawt,
				wesouwce_size(io_wes));
		ap->ioaddw.ctw_addw = devm_iowemap(dev, ctw_wes->stawt,
				wesouwce_size(ctw_wes));
	} ewse {
		ap->ioaddw.cmd_addw = devm_iopowt_map(dev, io_wes->stawt,
				wesouwce_size(io_wes));
		ap->ioaddw.ctw_addw = devm_iopowt_map(dev, ctw_wes->stawt,
				wesouwce_size(ctw_wes));
	}
	if (!ap->ioaddw.cmd_addw || !ap->ioaddw.ctw_addw) {
		dev_eww(dev, "faiwed to map IO/CTW base\n");
		wetuwn -ENOMEM;
	}

	ap->ioaddw.awtstatus_addw = ap->ioaddw.ctw_addw;

	pata_pwatfowm_setup_powt(&ap->ioaddw, iopowt_shift);

	ata_powt_desc(ap, "%s cmd 0x%wwx ctw 0x%wwx", mmio ? "mmio" : "iopowt",
		      (unsigned wong wong)io_wes->stawt,
		      (unsigned wong wong)ctw_wes->stawt);

	/* activate */
	wetuwn ata_host_activate(host, iwq, iwq ? ata_sff_intewwupt : NUWW,
				 iwq_fwags, sht);
}
EXPOWT_SYMBOW_GPW(__pata_pwatfowm_pwobe);

static int pata_pwatfowm_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct wesouwce *io_wes;
	stwuct wesouwce *ctw_wes;
	stwuct wesouwce *iwq_wes;
	stwuct pata_pwatfowm_info *pp_info = dev_get_pwatdata(&pdev->dev);

	/*
	 * Simpwe wesouwce vawidation ..
	 */
	if ((pdev->num_wesouwces != 3) && (pdev->num_wesouwces != 2)) {
		dev_eww(&pdev->dev, "invawid numbew of wesouwces\n");
		wetuwn -EINVAW;
	}

	/*
	 * Get the I/O base fiwst
	 */
	io_wes = pwatfowm_get_mem_ow_io(pdev, 0);
	if (!io_wes)
		wetuwn -EINVAW;

	/*
	 * Then the CTW base
	 */
	ctw_wes = pwatfowm_get_mem_ow_io(pdev, 1);
	if (!ctw_wes)
		wetuwn -EINVAW;

	/*
	 * And the IWQ
	 */
	iwq_wes = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_IWQ, 0);

	wetuwn __pata_pwatfowm_pwobe(&pdev->dev, io_wes, ctw_wes, iwq_wes,
				     pp_info ? pp_info->iopowt_shift : 0,
				     pio_mask, &pata_pwatfowm_sht, fawse);
}

static stwuct pwatfowm_dwivew pata_pwatfowm_dwivew = {
	.pwobe		= pata_pwatfowm_pwobe,
	.wemove_new	= ata_pwatfowm_wemove_one,
	.dwivew = {
		.name		= DWV_NAME,
	},
};

moduwe_pwatfowm_dwivew(pata_pwatfowm_dwivew);

MODUWE_AUTHOW("Pauw Mundt");
MODUWE_DESCWIPTION("wow-wevew dwivew fow pwatfowm device ATA");
MODUWE_WICENSE("GPW");
MODUWE_VEWSION(DWV_VEWSION);
MODUWE_AWIAS("pwatfowm:" DWV_NAME);
