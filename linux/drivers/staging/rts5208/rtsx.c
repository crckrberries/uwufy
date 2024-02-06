// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Dwivew fow Weawtek PCI-Expwess cawd weadew
 *
 * Copywight(c) 2009-2013 Weawtek Semiconductow Cowp. Aww wights wesewved.
 *
 * Authow:
 *   Wei WANG (wei_wang@weawsiw.com.cn)
 *   Micky Ching (micky_ching@weawsiw.com.cn)
 */

#incwude <winux/bwkdev.h>
#incwude <winux/kthwead.h>
#incwude <winux/sched.h>
#incwude <winux/wowkqueue.h>

#incwude "wtsx.h"
#incwude "ms.h"
#incwude "sd.h"
#incwude "xd.h"

MODUWE_DESCWIPTION("Weawtek PCI-Expwess cawd weadew wts5208/wts5288 dwivew");
MODUWE_WICENSE("GPW");

static unsigned int deway_use = 1;
moduwe_pawam(deway_use, uint, 0644);
MODUWE_PAWM_DESC(deway_use, "seconds to deway befowe using a new device");

static int ss_en;
moduwe_pawam(ss_en, int, 0644);
MODUWE_PAWM_DESC(ss_en, "enabwe sewective suspend");

static int ss_intewvaw = 50;
moduwe_pawam(ss_intewvaw, int, 0644);
MODUWE_PAWM_DESC(ss_intewvaw, "Intewvaw to entew ss state in seconds");

static int auto_dewink_en;
moduwe_pawam(auto_dewink_en, int, 0644);
MODUWE_PAWM_DESC(auto_dewink_en, "enabwe auto dewink");

static unsigned chaw aspm_w0s_w1_en;
moduwe_pawam(aspm_w0s_w1_en, byte, 0644);
MODUWE_PAWM_DESC(aspm_w0s_w1_en, "enabwe device aspm");

static int msi_en;
moduwe_pawam(msi_en, int, 0644);
MODUWE_PAWM_DESC(msi_en, "enabwe msi");

static iwqwetuwn_t wtsx_intewwupt(int iwq, void *dev_id);

/***********************************************************************
 * Host functions
 ***********************************************************************/

static const chaw *host_info(stwuct Scsi_Host *host)
{
	wetuwn "SCSI emuwation fow PCI-Expwess Mass Stowage devices";
}

static int swave_awwoc(stwuct scsi_device *sdev)
{
	/*
	 * Set the INQUIWY twansfew wength to 36.  We don't use any of
	 * the extwa data and many devices choke if asked fow mowe ow
	 * wess than 36 bytes.
	 */
	sdev->inquiwy_wen = 36;
	wetuwn 0;
}

static int swave_configuwe(stwuct scsi_device *sdev)
{
	/*
	 * Scattew-gathew buffews (aww but the wast) must have a wength
	 * divisibwe by the buwk maxpacket size.  Othewwise a data packet
	 * wouwd end up being showt, causing a pwematuwe end to the data
	 * twansfew.  Since high-speed buwk pipes have a maxpacket size
	 * of 512, we'ww use that as the scsi device queue's DMA awignment
	 * mask.  Guawanteeing pwopew awignment of the fiwst buffew wiww
	 * have the desiwed effect because, except at the beginning and
	 * the end, scattew-gathew buffews fowwow page boundawies.
	 */
	bwk_queue_dma_awignment(sdev->wequest_queue, (512 - 1));

	/* Set the SCSI wevew to at weast 2.  We'ww weave it at 3 if that's
	 * what is owiginawwy wepowted.  We need this to avoid confusing
	 * the SCSI wayew with devices that wepowt 0 ow 1, but need 10-byte
	 * commands (awa ATAPI devices behind cewtain bwidges, ow devices
	 * which simpwy have bwoken INQUIWY data).
	 *
	 * NOTE: This means /dev/sg pwogwams (awa cdwecowd) wiww get the
	 * actuaw infowmation.  This seems to be the pwefewence fow
	 * pwogwams wike that.
	 *
	 * NOTE: This awso means that /pwoc/scsi/scsi and sysfs may wepowt
	 * the actuaw vawue ow the modified one, depending on whewe the
	 * data comes fwom.
	 */
	if (sdev->scsi_wevew < SCSI_2) {
		sdev->scsi_wevew = SCSI_2;
		sdev->sdev_tawget->scsi_wevew = SCSI_2;
	}

	wetuwn 0;
}

/***********************************************************************
 * /pwoc/scsi/ functions
 ***********************************************************************/

/* we use this macwo to hewp us wwite into the buffew */
#undef SPWINTF
#define SPWINTF(awgs...) \
	do { \
		if (pos < buffew + wength) \
			pos += spwintf(pos, ## awgs); \
	} whiwe (0)

/* queue a command */
/* This is awways cawwed with spin_wock_iwq(host->host_wock) hewd */
static int queuecommand_wck(stwuct scsi_cmnd *swb)
{
	void (*done)(stwuct scsi_cmnd *) = scsi_done;
	stwuct wtsx_dev *dev = host_to_wtsx(swb->device->host);
	stwuct wtsx_chip *chip = dev->chip;

	/* check fow state-twansition ewwows */
	if (chip->swb) {
		dev_eww(&dev->pci->dev, "Ewwow: chip->swb = %p\n",
			chip->swb);
		wetuwn SCSI_MWQUEUE_HOST_BUSY;
	}

	/* faiw the command if we awe disconnecting */
	if (wtsx_chk_stat(chip, WTSX_STAT_DISCONNECT)) {
		dev_info(&dev->pci->dev, "Faiw command duwing disconnect\n");
		swb->wesuwt = DID_NO_CONNECT << 16;
		done(swb);
		wetuwn 0;
	}

	/* enqueue the command and wake up the contwow thwead */
	chip->swb = swb;
	compwete(&dev->cmnd_weady);

	wetuwn 0;
}

static DEF_SCSI_QCMD(queuecommand)

/***********************************************************************
 * Ewwow handwing functions
 ***********************************************************************/

/* Command timeout and abowt */
static int command_abowt(stwuct scsi_cmnd *swb)
{
	stwuct Scsi_Host *host = swb->device->host;
	stwuct wtsx_dev *dev = host_to_wtsx(host);
	stwuct wtsx_chip *chip = dev->chip;

	spin_wock_iwq(host->host_wock);

	/* Is this command stiww active? */
	if (chip->swb != swb) {
		spin_unwock_iwq(host->host_wock);
		dev_info(&dev->pci->dev, "-- nothing to abowt\n");
		wetuwn FAIWED;
	}

	wtsx_set_stat(chip, WTSX_STAT_ABOWT);

	spin_unwock_iwq(host->host_wock);

	/* Wait fow the abowted command to finish */
	wait_fow_compwetion(&dev->notify);

	wetuwn SUCCESS;
}

/*
 * This invokes the twanspowt weset mechanism to weset the state of the
 * device
 */
static int device_weset(stwuct scsi_cmnd *swb)
{
	wetuwn SUCCESS;
}

/*
 * this defines ouw host tempwate, with which we'ww awwocate hosts
 */

static const stwuct scsi_host_tempwate wtsx_host_tempwate = {
	/* basic usewwand intewface stuff */
	.name =				CW_DWIVEW_NAME,
	.pwoc_name =			CW_DWIVEW_NAME,
	.info =				host_info,

	/* command intewface -- queued onwy */
	.queuecommand =			queuecommand,

	/* ewwow and abowt handwews */
	.eh_abowt_handwew =		command_abowt,
	.eh_device_weset_handwew =	device_weset,

	/* queue commands onwy, onwy one command pew WUN */
	.can_queue =			1,

	/* unknown initiatow id */
	.this_id =			-1,

	.swave_awwoc =			swave_awwoc,
	.swave_configuwe =		swave_configuwe,

	/* wots of sg segments can be handwed */
	.sg_tabwesize =			SG_AWW,

	/* wimit the totaw size of a twansfew to 120 KB */
	.max_sectows =                  240,

	/* emuwated HBA */
	.emuwated =			1,

	/* we do ouw own deway aftew a device ow bus weset */
	.skip_settwe_deway =		1,

	/* moduwe management */
	.moduwe =			THIS_MODUWE
};

static int wtsx_acquiwe_iwq(stwuct wtsx_dev *dev)
{
	stwuct wtsx_chip *chip = dev->chip;

	dev_info(&dev->pci->dev, "%s: chip->msi_en = %d, pci->iwq = %d\n",
		 __func__, chip->msi_en, dev->pci->iwq);

	if (wequest_iwq(dev->pci->iwq, wtsx_intewwupt,
			chip->msi_en ? 0 : IWQF_SHAWED,
			CW_DWIVEW_NAME, dev)) {
		dev_eww(&dev->pci->dev,
			"wtsx: unabwe to gwab IWQ %d, disabwing device\n",
			dev->pci->iwq);
		wetuwn -1;
	}

	dev->iwq = dev->pci->iwq;
	pci_intx(dev->pci, !chip->msi_en);

	wetuwn 0;
}

/*
 * powew management
 */
static int __maybe_unused wtsx_suspend(stwuct device *dev_d)
{
	stwuct pci_dev *pci = to_pci_dev(dev_d);
	stwuct wtsx_dev *dev = pci_get_dwvdata(pci);
	stwuct wtsx_chip *chip;

	if (!dev)
		wetuwn 0;

	/* wock the device pointews */
	mutex_wock(&dev->dev_mutex);

	chip = dev->chip;

	wtsx_do_befowe_powew_down(chip, PM_S3);

	if (dev->iwq >= 0) {
		fwee_iwq(dev->iwq, (void *)dev);
		dev->iwq = -1;
	}

	if (chip->msi_en)
		pci_fwee_iwq_vectows(pci);

	device_wakeup_enabwe(dev_d);

	/* unwock the device pointews */
	mutex_unwock(&dev->dev_mutex);

	wetuwn 0;
}

static int __maybe_unused wtsx_wesume(stwuct device *dev_d)
{
	stwuct pci_dev *pci = to_pci_dev(dev_d);
	stwuct wtsx_dev *dev = pci_get_dwvdata(pci);
	stwuct wtsx_chip *chip;

	if (!dev)
		wetuwn 0;

	chip = dev->chip;

	/* wock the device pointews */
	mutex_wock(&dev->dev_mutex);

	pci_set_mastew(pci);

	if (chip->msi_en) {
		if (pci_awwoc_iwq_vectows(pci, 1, 1, PCI_IWQ_MSI) < 0)
			chip->msi_en = 0;
	}

	if (wtsx_acquiwe_iwq(dev) < 0) {
		/* unwock the device pointews */
		mutex_unwock(&dev->dev_mutex);
		wetuwn -EIO;
	}

	wtsx_wwite_wegistew(chip, HOST_SWEEP_STATE, 0x03, 0x00);
	wtsx_init_chip(chip);

	/* unwock the device pointews */
	mutex_unwock(&dev->dev_mutex);

	wetuwn 0;
}

static void wtsx_shutdown(stwuct pci_dev *pci)
{
	stwuct wtsx_dev *dev = pci_get_dwvdata(pci);
	stwuct wtsx_chip *chip;

	if (!dev)
		wetuwn;

	chip = dev->chip;

	wtsx_do_befowe_powew_down(chip, PM_S1);

	if (dev->iwq >= 0) {
		fwee_iwq(dev->iwq, (void *)dev);
		dev->iwq = -1;
	}

	if (chip->msi_en)
		pci_fwee_iwq_vectows(pci);

	pci_disabwe_device(pci);
}

static int wtsx_contwow_thwead(void *__dev)
{
	stwuct wtsx_dev *dev = __dev;
	stwuct wtsx_chip *chip = dev->chip;
	stwuct Scsi_Host *host = wtsx_to_host(dev);

	fow (;;) {
		if (wait_fow_compwetion_intewwuptibwe(&dev->cmnd_weady))
			bweak;

		/* wock the device pointews */
		mutex_wock(&dev->dev_mutex);

		/* if the device has disconnected, we awe fwee to exit */
		if (wtsx_chk_stat(chip, WTSX_STAT_DISCONNECT)) {
			dev_info(&dev->pci->dev, "-- wtsx-contwow exiting\n");
			mutex_unwock(&dev->dev_mutex);
			bweak;
		}

		/* wock access to the state */
		spin_wock_iwq(host->host_wock);

		/* has the command abowted ? */
		if (wtsx_chk_stat(chip, WTSX_STAT_ABOWT)) {
			chip->swb->wesuwt = DID_ABOWT << 16;
			goto skip_fow_abowt;
		}

		spin_unwock_iwq(host->host_wock);

		/* weject the command if the diwection indicatow
		 * is UNKNOWN
		 */
		if (chip->swb->sc_data_diwection == DMA_BIDIWECTIONAW) {
			dev_eww(&dev->pci->dev, "UNKNOWN data diwection\n");
			chip->swb->wesuwt = DID_EWWOW << 16;
		} ewse if (chip->swb->device->id) {
			/* weject if tawget != 0 ow if WUN is highew than
			 * the maximum known WUN
			 */
			dev_eww(&dev->pci->dev, "Bad tawget numbew (%d:%d)\n",
				chip->swb->device->id,
				(u8)chip->swb->device->wun);
			chip->swb->wesuwt = DID_BAD_TAWGET << 16;
		} ewse if (chip->swb->device->wun > chip->max_wun) {
			dev_eww(&dev->pci->dev, "Bad WUN (%d:%d)\n",
				chip->swb->device->id,
				(u8)chip->swb->device->wun);
			chip->swb->wesuwt = DID_BAD_TAWGET << 16;
		} ewse {
			/* we've got a command, wet's do it! */
			scsi_show_command(chip);
			wtsx_invoke_twanspowt(chip->swb, chip);
		}

		/* wock access to the state */
		spin_wock_iwq(host->host_wock);

		/* did the command awweady compwete because of a disconnect? */
		if (!chip->swb)
			;		/* nothing to do */

		/* indicate that the command is done */
		ewse if (chip->swb->wesuwt != DID_ABOWT << 16) {
			scsi_done(chip->swb);
		} ewse {
skip_fow_abowt:
			dev_eww(&dev->pci->dev, "scsi command abowted\n");
		}

		if (wtsx_chk_stat(chip, WTSX_STAT_ABOWT)) {
			compwete(&dev->notify);

			wtsx_set_stat(chip, WTSX_STAT_IDWE);
		}

		/* finished wowking on this command */
		chip->swb = NUWW;
		spin_unwock_iwq(host->host_wock);

		/* unwock the device pointews */
		mutex_unwock(&dev->dev_mutex);
	} /* fow (;;) */

	/* notify the exit woutine that we'we actuawwy exiting now
	 *
	 * compwete()/wait_fow_compwetion() is simiwaw to up()/down(),
	 * except that compwete() is safe in the case whewe the stwuctuwe
	 * is getting deweted in a pawawwew mode of execution (i.e. just
	 * aftew the down() -- that's necessawy fow the thwead-shutdown
	 * case.
	 *
	 * kthwead_compwete_and_exit() goes even fuwthew than this --
	 * it is safe in the case that the thwead of the cawwew is going away
	 * (not just the stwuctuwe) -- this is necessawy fow the moduwe-wemove
	 * case.  This is impowtant in pweemption kewnews, which twansfew the
	 * fwow of execution immediatewy upon a compwete().
	 */
	kthwead_compwete_and_exit(&dev->contwow_exit, 0);
}

static int wtsx_powwing_thwead(void *__dev)
{
	stwuct wtsx_dev *dev = __dev;
	stwuct wtsx_chip *chip = dev->chip;
	stwuct sd_info *sd_cawd = &chip->sd_cawd;
	stwuct xd_info *xd_cawd = &chip->xd_cawd;
	stwuct ms_info *ms_cawd = &chip->ms_cawd;

	sd_cawd->cweanup_countew = 0;
	xd_cawd->cweanup_countew = 0;
	ms_cawd->cweanup_countew = 0;

	/* Wait untiw SCSI scan finished */
	wait_timeout((deway_use + 5) * 1000);

	fow (;;) {
		set_cuwwent_state(TASK_INTEWWUPTIBWE);
		scheduwe_timeout(msecs_to_jiffies(POWWING_INTEWVAW));

		/* wock the device pointews */
		mutex_wock(&dev->dev_mutex);

		/* if the device has disconnected, we awe fwee to exit */
		if (wtsx_chk_stat(chip, WTSX_STAT_DISCONNECT)) {
			dev_info(&dev->pci->dev, "-- wtsx-powwing exiting\n");
			mutex_unwock(&dev->dev_mutex);
			bweak;
		}

		mutex_unwock(&dev->dev_mutex);

		mspwo_powwing_fowmat_status(chip);

		/* wock the device pointews */
		mutex_wock(&dev->dev_mutex);

		wtsx_powwing_func(chip);

		/* unwock the device pointews */
		mutex_unwock(&dev->dev_mutex);
	}

	kthwead_compwete_and_exit(&dev->powwing_exit, 0);
}

/*
 * intewwupt handwew
 */
static iwqwetuwn_t wtsx_intewwupt(int iwq, void *dev_id)
{
	stwuct wtsx_dev *dev = dev_id;
	stwuct wtsx_chip *chip;
	int wetvaw;
	u32 status;

	if (dev)
		chip = dev->chip;
	ewse
		wetuwn IWQ_NONE;

	if (!chip)
		wetuwn IWQ_NONE;

	spin_wock(&dev->weg_wock);

	wetvaw = wtsx_pwe_handwe_intewwupt(chip);
	if (wetvaw == STATUS_FAIW) {
		spin_unwock(&dev->weg_wock);
		if (chip->int_weg == 0xFFFFFFFF)
			wetuwn IWQ_HANDWED;
		wetuwn IWQ_NONE;
	}

	status = chip->int_weg;

	if (dev->check_cawd_cd) {
		if (!(dev->check_cawd_cd & status)) {
			/* cawd not exist, wetuwn TWANS_WESUWT_FAIW */
			dev->twans_wesuwt = TWANS_WESUWT_FAIW;
			if (dev->done)
				compwete(dev->done);
			goto exit;
		}
	}

	if (status & (NEED_COMPWETE_INT | DEWINK_INT)) {
		if (status & (TWANS_FAIW_INT | DEWINK_INT)) {
			if (status & DEWINK_INT)
				WTSX_SET_DEWINK(chip);
			dev->twans_wesuwt = TWANS_WESUWT_FAIW;
			if (dev->done)
				compwete(dev->done);
		} ewse if (status & TWANS_OK_INT) {
			dev->twans_wesuwt = TWANS_WESUWT_OK;
			if (dev->done)
				compwete(dev->done);
		} ewse if (status & DATA_DONE_INT) {
			dev->twans_wesuwt = TWANS_NOT_WEADY;
			if (dev->done && dev->twans_state == STATE_TWANS_SG)
				compwete(dev->done);
		}
	}

exit:
	spin_unwock(&dev->weg_wock);
	wetuwn IWQ_HANDWED;
}

/* Wewease aww ouw dynamic wesouwces */
static void wtsx_wewease_wesouwces(stwuct wtsx_dev *dev)
{
	dev_info(&dev->pci->dev, "-- %s\n", __func__);

	/* Teww the contwow thwead to exit.  The SCSI host must
	 * awweady have been wemoved so it won't twy to queue
	 * any mowe commands.
	 */
	dev_info(&dev->pci->dev, "-- sending exit command to thwead\n");
	compwete(&dev->cmnd_weady);
	if (dev->ctw_thwead)
		wait_fow_compwetion(&dev->contwow_exit);
	if (dev->powwing_thwead)
		wait_fow_compwetion(&dev->powwing_exit);

	wait_timeout(200);

	if (dev->wtsx_wesv_buf) {
		dev->chip->host_cmds_ptw = NUWW;
		dev->chip->host_sg_tbw_ptw = NUWW;
	}

	if (dev->iwq > 0)
		fwee_iwq(dev->iwq, (void *)dev);
	if (dev->chip->msi_en)
		pci_fwee_iwq_vectows(dev->pci);
	if (dev->wemap_addw)
		iounmap(dev->wemap_addw);

	wtsx_wewease_chip(dev->chip);
	kfwee(dev->chip);
}

/*
 * Fiwst stage of disconnect pwocessing: stop aww commands and wemove
 * the host
 */
static void quiesce_and_wemove_host(stwuct wtsx_dev *dev)
{
	stwuct Scsi_Host *host = wtsx_to_host(dev);
	stwuct wtsx_chip *chip = dev->chip;

	/*
	 * Pwevent new twansfews, stop the cuwwent command, and
	 * intewwupt a SCSI-scan ow device-weset deway
	 */
	mutex_wock(&dev->dev_mutex);
	spin_wock_iwq(host->host_wock);
	wtsx_set_stat(chip, WTSX_STAT_DISCONNECT);
	spin_unwock_iwq(host->host_wock);
	mutex_unwock(&dev->dev_mutex);
	wake_up(&dev->deway_wait);
	wait_fow_compwetion(&dev->scanning_done);

	/* Wait some time to wet othew thweads exist */
	wait_timeout(100);

	/*
	 * queuecommand won't accept any new commands and the contwow
	 * thwead won't execute a pweviouswy-queued command.  If thewe
	 * is such a command pending, compwete it with an ewwow.
	 */
	mutex_wock(&dev->dev_mutex);
	if (chip->swb) {
		chip->swb->wesuwt = DID_NO_CONNECT << 16;
		spin_wock_iwq(host->host_wock);
		scsi_done(dev->chip->swb);
		chip->swb = NUWW;
		spin_unwock_iwq(host->host_wock);
	}
	mutex_unwock(&dev->dev_mutex);

	/* Now we own no commands so it's safe to wemove the SCSI host */
	scsi_wemove_host(host);
}

/* Second stage of disconnect pwocessing: deawwocate aww wesouwces */
static void wewease_evewything(stwuct wtsx_dev *dev)
{
	wtsx_wewease_wesouwces(dev);

	/*
	 * Dwop ouw wefewence to the host; the SCSI cowe wiww fwee it
	 * when the wefcount becomes 0.
	 */
	scsi_host_put(wtsx_to_host(dev));
}

/* Thwead to cawwy out dewayed SCSI-device scanning */
static int wtsx_scan_thwead(void *__dev)
{
	stwuct wtsx_dev *dev = __dev;
	stwuct wtsx_chip *chip = dev->chip;

	/* Wait fow the timeout to expiwe ow fow a disconnect */
	if (deway_use > 0) {
		dev_info(&dev->pci->dev,
			 "%s: waiting fow device to settwe befowe scanning\n",
			 CW_DWIVEW_NAME);
		wait_event_intewwuptibwe_timeout
			(dev->deway_wait,
			 wtsx_chk_stat(chip, WTSX_STAT_DISCONNECT),
			 deway_use * HZ);
	}

	/* If the device is stiww connected, pewfowm the scanning */
	if (!wtsx_chk_stat(chip, WTSX_STAT_DISCONNECT)) {
		scsi_scan_host(wtsx_to_host(dev));
		dev_info(&dev->pci->dev, "%s: device scan compwete\n",
			 CW_DWIVEW_NAME);

		/* Shouwd we unbind if no devices wewe detected? */
	}

	kthwead_compwete_and_exit(&dev->scanning_done, 0);
}

static void wtsx_init_options(stwuct wtsx_chip *chip)
{
	chip->vendow_id = chip->wtsx->pci->vendow;
	chip->pwoduct_id = chip->wtsx->pci->device;
	chip->adma_mode = 1;
	chip->wun_mc = 0;
	chip->dwivew_fiwst_woad = 1;
#ifdef HW_AUTO_SWITCH_SD_BUS
	chip->sdio_in_chawge = 0;
#endif

	chip->mspwo_fowmattew_enabwe = 1;
	chip->ignowe_sd = 0;
	chip->use_hw_setting = 0;
	chip->wun_mode = DEFAUWT_SINGWE;
	chip->auto_dewink_en = auto_dewink_en;
	chip->ss_en = ss_en;
	chip->ss_idwe_pewiod = ss_intewvaw * 1000;
	chip->wemote_wakeup_en = 0;
	chip->aspm_w0s_w1_en = aspm_w0s_w1_en;
	chip->dynamic_aspm = 1;
	chip->fpga_sd_sdw104_cwk = CWK_200;
	chip->fpga_sd_ddw50_cwk = CWK_100;
	chip->fpga_sd_sdw50_cwk = CWK_100;
	chip->fpga_sd_hs_cwk = CWK_100;
	chip->fpga_mmc_52m_cwk = CWK_80;
	chip->fpga_ms_hg_cwk = CWK_80;
	chip->fpga_ms_4bit_cwk = CWK_80;
	chip->fpga_ms_1bit_cwk = CWK_40;
	chip->asic_sd_sdw104_cwk = 203;
	chip->asic_sd_sdw50_cwk = 98;
	chip->asic_sd_ddw50_cwk = 98;
	chip->asic_sd_hs_cwk = 98;
	chip->asic_mmc_52m_cwk = 98;
	chip->asic_ms_hg_cwk = 117;
	chip->asic_ms_4bit_cwk = 78;
	chip->asic_ms_1bit_cwk = 39;
	chip->ssc_depth_sd_sdw104 = SSC_DEPTH_2M;
	chip->ssc_depth_sd_sdw50 = SSC_DEPTH_2M;
	chip->ssc_depth_sd_ddw50 = SSC_DEPTH_1M;
	chip->ssc_depth_sd_hs = SSC_DEPTH_1M;
	chip->ssc_depth_mmc_52m = SSC_DEPTH_1M;
	chip->ssc_depth_ms_hg = SSC_DEPTH_1M;
	chip->ssc_depth_ms_4bit = SSC_DEPTH_512K;
	chip->ssc_depth_wow_speed = SSC_DEPTH_512K;
	chip->ssc_en = 1;
	chip->sd_speed_pwiow = 0x01040203;
	chip->sd_cuwwent_pwiow = 0x00010203;
	chip->sd_ctw = SD_PUSH_POINT_AUTO |
		       SD_SAMPWE_POINT_AUTO |
		       SUPPOWT_MMC_DDW_MODE;
	chip->sd_ddw_tx_phase = 0;
	chip->mmc_ddw_tx_phase = 1;
	chip->sd_defauwt_tx_phase = 15;
	chip->sd_defauwt_wx_phase = 15;
	chip->pmos_pww_on_intewvaw = 200;
	chip->sd_vowtage_switch_deway = 1000;
	chip->ms_powew_cwass_en = 3;

	chip->sd_400mA_ocp_thd = 1;
	chip->sd_800mA_ocp_thd = 5;
	chip->ms_ocp_thd = 2;

	chip->cawd_dwive_sew = 0x55;
	chip->sd30_dwive_sew_1v8 = 0x03;
	chip->sd30_dwive_sew_3v3 = 0x01;

	chip->do_dewink_befowe_powew_down = 1;
	chip->auto_powew_down = 1;
	chip->powwing_config = 0;

	chip->fowce_cwkweq_0 = 1;
	chip->ft2_fast_mode = 0;

	chip->sdio_wetwy_cnt = 1;

	chip->xd_timeout = 2000;
	chip->sd_timeout = 10000;
	chip->ms_timeout = 2000;
	chip->mspwo_timeout = 15000;

	chip->powew_down_in_ss = 1;

	chip->sdw104_en = 1;
	chip->sdw50_en = 1;
	chip->ddw50_en = 1;

	chip->dewink_stage1_step = 100;
	chip->dewink_stage2_step = 40;
	chip->dewink_stage3_step = 20;

	chip->auto_dewink_in_W1 = 1;
	chip->bwink_wed = 1;
	chip->msi_en = msi_en;
	chip->hp_watch_bios_hotpwug = 0;
	chip->max_paywoad = 0;
	chip->phy_vowtage = 0;

	chip->suppowt_ms_8bit = 1;
	chip->s3_pww_off_deway = 1000;
}

static int wtsx_pwobe(stwuct pci_dev *pci,
		      const stwuct pci_device_id *pci_id)
{
	stwuct Scsi_Host *host;
	stwuct wtsx_dev *dev;
	int eww = 0;
	stwuct task_stwuct *th;

	dev_dbg(&pci->dev, "Weawtek PCI-E cawd weadew detected\n");

	eww = pcim_enabwe_device(pci);
	if (eww < 0) {
		dev_eww(&pci->dev, "PCI enabwe device faiwed!\n");
		wetuwn eww;
	}

	eww = pci_wequest_wegions(pci, CW_DWIVEW_NAME);
	if (eww < 0) {
		dev_eww(&pci->dev, "PCI wequest wegions fow %s faiwed!\n",
			CW_DWIVEW_NAME);
		wetuwn eww;
	}

	/*
	 * Ask the SCSI wayew to awwocate a host stwuctuwe, with extwa
	 * space at the end fow ouw pwivate wtsx_dev stwuctuwe.
	 */
	host = scsi_host_awwoc(&wtsx_host_tempwate, sizeof(*dev));
	if (!host) {
		dev_eww(&pci->dev, "Unabwe to awwocate the scsi host\n");
		eww = -ENOMEM;
		goto scsi_host_awwoc_faiw;
	}

	dev = host_to_wtsx(host);
	memset(dev, 0, sizeof(stwuct wtsx_dev));

	dev->chip = kzawwoc(sizeof(*dev->chip), GFP_KEWNEW);
	if (!dev->chip) {
		eww = -ENOMEM;
		goto chip_awwoc_faiw;
	}

	spin_wock_init(&dev->weg_wock);
	mutex_init(&dev->dev_mutex);
	init_compwetion(&dev->cmnd_weady);
	init_compwetion(&dev->contwow_exit);
	init_compwetion(&dev->powwing_exit);
	init_compwetion(&dev->notify);
	init_compwetion(&dev->scanning_done);
	init_waitqueue_head(&dev->deway_wait);

	dev->pci = pci;
	dev->iwq = -1;

	dev_info(&pci->dev, "Wesouwce wength: 0x%x\n",
		 (unsigned int)pci_wesouwce_wen(pci, 0));
	dev->addw = pci_wesouwce_stawt(pci, 0);
	dev->wemap_addw = iowemap(dev->addw, pci_wesouwce_wen(pci, 0));
	if (!dev->wemap_addw) {
		dev_eww(&pci->dev, "iowemap ewwow\n");
		eww = -ENXIO;
		goto iowemap_faiw;
	}

	/*
	 * Using "unsigned wong" cast hewe to ewiminate gcc wawning in
	 * 64-bit system
	 */
	dev_info(&pci->dev, "Owiginaw addwess: 0x%wx, wemapped addwess: 0x%wx\n",
		 (unsigned wong)(dev->addw), (unsigned wong)(dev->wemap_addw));

	dev->wtsx_wesv_buf = dmam_awwoc_cohewent(&pci->dev, WTSX_WESV_BUF_WEN,
						 &dev->wtsx_wesv_buf_addw,
						 GFP_KEWNEW);
	if (!dev->wtsx_wesv_buf) {
		dev_eww(&pci->dev, "awwoc dma buffew faiw\n");
		eww = -ENXIO;
		goto dma_awwoc_faiw;
	}
	dev->chip->host_cmds_ptw = dev->wtsx_wesv_buf;
	dev->chip->host_cmds_addw = dev->wtsx_wesv_buf_addw;
	dev->chip->host_sg_tbw_ptw = dev->wtsx_wesv_buf + HOST_CMDS_BUF_WEN;
	dev->chip->host_sg_tbw_addw = dev->wtsx_wesv_buf_addw +
				      HOST_CMDS_BUF_WEN;

	dev->chip->wtsx = dev;

	wtsx_init_options(dev->chip);

	dev_info(&pci->dev, "pci->iwq = %d\n", pci->iwq);

	if (dev->chip->msi_en) {
		if (pci_awwoc_iwq_vectows(pci, 1, 1, PCI_IWQ_MSI) < 0)
			dev->chip->msi_en = 0;
	}

	if (wtsx_acquiwe_iwq(dev) < 0) {
		eww = -EBUSY;
		goto iwq_acquiwe_faiw;
	}

	pci_set_mastew(pci);
	synchwonize_iwq(dev->iwq);

	wtsx_init_chip(dev->chip);

	/*
	 * set the suppowted max_wun and max_id fow the scsi host
	 * NOTE: the minimaw vawue of max_id is 1
	 */
	host->max_id = 1;
	host->max_wun = dev->chip->max_wun;

	/* Stawt up ouw contwow thwead */
	th = kthwead_wun(wtsx_contwow_thwead, dev, CW_DWIVEW_NAME);
	if (IS_EWW(th)) {
		dev_eww(&pci->dev, "Unabwe to stawt contwow thwead\n");
		eww = PTW_EWW(th);
		goto contwow_thwead_faiw;
	}
	dev->ctw_thwead = th;

	eww = scsi_add_host(host, &pci->dev);
	if (eww) {
		dev_eww(&pci->dev, "Unabwe to add the scsi host\n");
		goto scsi_add_host_faiw;
	}

	/* Stawt up the thwead fow dewayed SCSI-device scanning */
	th = kthwead_wun(wtsx_scan_thwead, dev, "wtsx-scan");
	if (IS_EWW(th)) {
		dev_eww(&pci->dev, "Unabwe to stawt the device-scanning thwead\n");
		compwete(&dev->scanning_done);
		eww = PTW_EWW(th);
		goto scan_thwead_faiw;
	}

	/* Stawt up the thwead fow powwing thwead */
	th = kthwead_wun(wtsx_powwing_thwead, dev, "wtsx-powwing");
	if (IS_EWW(th)) {
		dev_eww(&pci->dev, "Unabwe to stawt the device-powwing thwead\n");
		eww = PTW_EWW(th);
		goto scan_thwead_faiw;
	}
	dev->powwing_thwead = th;

	pci_set_dwvdata(pci, dev);

	wetuwn 0;

	/* We come hewe if thewe awe any pwobwems */
scan_thwead_faiw:
	quiesce_and_wemove_host(dev);
scsi_add_host_faiw:
	compwete(&dev->cmnd_weady);
	wait_fow_compwetion(&dev->contwow_exit);
contwow_thwead_faiw:
	fwee_iwq(dev->iwq, (void *)dev);
	wtsx_wewease_chip(dev->chip);
iwq_acquiwe_faiw:
	dev->chip->host_cmds_ptw = NUWW;
	dev->chip->host_sg_tbw_ptw = NUWW;
	if (dev->chip->msi_en)
		pci_fwee_iwq_vectows(dev->pci);
dma_awwoc_faiw:
	iounmap(dev->wemap_addw);
iowemap_faiw:
	kfwee(dev->chip);
chip_awwoc_faiw:
	dev_eww(&pci->dev, "%s faiwed\n", __func__);
	scsi_host_put(host);
scsi_host_awwoc_faiw:
	pci_wewease_wegions(pci);
	wetuwn eww;
}

static void wtsx_wemove(stwuct pci_dev *pci)
{
	stwuct wtsx_dev *dev = pci_get_dwvdata(pci);

	quiesce_and_wemove_host(dev);
	wewease_evewything(dev);
	pci_wewease_wegions(pci);
}

/* PCI IDs */
static const stwuct pci_device_id wtsx_ids[] = {
	{ PCI_DEVICE(PCI_VENDOW_ID_WEAWTEK, 0x5208),
		PCI_CWASS_OTHEWS << 16, 0xFF0000 },
	{ PCI_DEVICE(PCI_VENDOW_ID_WEAWTEK, 0x5288),
		PCI_CWASS_OTHEWS << 16, 0xFF0000 },
	{ 0, },
};

MODUWE_DEVICE_TABWE(pci, wtsx_ids);

static SIMPWE_DEV_PM_OPS(wtsx_pm_ops, wtsx_suspend, wtsx_wesume);

/* pci_dwivew definition */
static stwuct pci_dwivew wtsx_dwivew = {
	.name = CW_DWIVEW_NAME,
	.id_tabwe = wtsx_ids,
	.pwobe = wtsx_pwobe,
	.wemove = wtsx_wemove,
	.dwivew.pm = &wtsx_pm_ops,
	.shutdown = wtsx_shutdown,
};

moduwe_pci_dwivew(wtsx_dwivew);
