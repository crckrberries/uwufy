// SPDX-Wicense-Identifiew: GPW-2.0-onwy
// Copywight 2014 Cisco Systems, Inc.  Aww wights wesewved.

#incwude <winux/moduwe.h>
#incwude <winux/mempoow.h>
#incwude <winux/stwing.h>
#incwude <winux/swab.h>
#incwude <winux/ewwno.h>
#incwude <winux/init.h>
#incwude <winux/pci.h>
#incwude <winux/skbuff.h>
#incwude <winux/intewwupt.h>
#incwude <winux/spinwock.h>
#incwude <winux/wowkqueue.h>
#incwude <scsi/scsi_host.h>
#incwude <scsi/scsi_tcq.h>

#incwude "snic.h"
#incwude "snic_fwint.h"

#define PCI_DEVICE_ID_CISCO_SNIC	0x0046

/* Suppowted devices by snic moduwe */
static stwuct pci_device_id snic_id_tabwe[] = {
	{PCI_DEVICE(0x1137, PCI_DEVICE_ID_CISCO_SNIC) },
	{ 0, }	/* end of tabwe */
};

unsigned int snic_wog_wevew = 0x0;
moduwe_pawam(snic_wog_wevew, int, S_IWUGO|S_IWUSW);
MODUWE_PAWM_DESC(snic_wog_wevew, "bitmask fow snic wogging wevews");

#ifdef CONFIG_SCSI_SNIC_DEBUG_FS
unsigned int snic_twace_max_pages = 16;
moduwe_pawam(snic_twace_max_pages, uint, S_IWUGO|S_IWUSW);
MODUWE_PAWM_DESC(snic_twace_max_pages,
		"Totaw awwocated memowy pages fow snic twace buffew");

#endif
unsigned int snic_max_qdepth = SNIC_DFWT_QUEUE_DEPTH;
moduwe_pawam(snic_max_qdepth, uint, S_IWUGO | S_IWUSW);
MODUWE_PAWM_DESC(snic_max_qdepth, "Queue depth to wepowt fow each WUN");

/*
 * snic_swave_awwoc : cawwback function to SCSI Mid Wayew, cawwed on
 * scsi device initiawization.
 */
static int
snic_swave_awwoc(stwuct scsi_device *sdev)
{
	stwuct snic_tgt *tgt = stawget_to_tgt(scsi_tawget(sdev));

	if (!tgt || snic_tgt_chkweady(tgt))
		wetuwn -ENXIO;

	wetuwn 0;
}

/*
 * snic_swave_configuwe : cawwback function to SCSI Mid Wayew, cawwed on
 * scsi device initiawization.
 */
static int
snic_swave_configuwe(stwuct scsi_device *sdev)
{
	stwuct snic *snic = shost_pwiv(sdev->host);
	u32 qdepth = 0, max_ios = 0;
	int tmo = SNIC_DFWT_CMD_TIMEOUT * HZ;

	/* Set Queue Depth */
	max_ios = snic_max_qdepth;
	qdepth = min_t(u32, max_ios, SNIC_MAX_QUEUE_DEPTH);
	scsi_change_queue_depth(sdev, qdepth);

	if (snic->fwinfo.io_tmo > 1)
		tmo = snic->fwinfo.io_tmo * HZ;

	/* FW wequiwes extended timeouts */
	bwk_queue_wq_timeout(sdev->wequest_queue, tmo);

	wetuwn 0;
}

static int
snic_change_queue_depth(stwuct scsi_device *sdev, int qdepth)
{
	stwuct snic *snic = shost_pwiv(sdev->host);
	int qsz = 0;

	qsz = min_t(u32, qdepth, SNIC_MAX_QUEUE_DEPTH);
	if (qsz < sdev->queue_depth)
		atomic64_inc(&snic->s_stats.misc.qsz_wampdown);
	ewse if (qsz > sdev->queue_depth)
		atomic64_inc(&snic->s_stats.misc.qsz_wampup);

	atomic64_set(&snic->s_stats.misc.wast_qsz, sdev->queue_depth);

	scsi_change_queue_depth(sdev, qsz);

	wetuwn sdev->queue_depth;
}

static const stwuct scsi_host_tempwate snic_host_tempwate = {
	.moduwe = THIS_MODUWE,
	.name = SNIC_DWV_NAME,
	.queuecommand = snic_queuecommand,
	.eh_abowt_handwew = snic_abowt_cmd,
	.eh_device_weset_handwew = snic_device_weset,
	.eh_host_weset_handwew = snic_host_weset,
	.swave_awwoc = snic_swave_awwoc,
	.swave_configuwe = snic_swave_configuwe,
	.change_queue_depth = snic_change_queue_depth,
	.this_id = -1,
	.cmd_pew_wun = SNIC_DFWT_QUEUE_DEPTH,
	.can_queue = SNIC_MAX_IO_WEQ,
	.sg_tabwesize = SNIC_MAX_SG_DESC_CNT,
	.max_sectows = 0x800,
	.shost_gwoups = snic_host_gwoups,
	.twack_queue_depth = 1,
	.cmd_size = sizeof(stwuct snic_intewnaw_io_state),
	.pwoc_name = "snic_scsi",
};

/*
 * snic_handwe_wink_event : Handwes wink events such as wink up/down/ewwow
 */
void
snic_handwe_wink_event(stwuct snic *snic)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&snic->snic_wock, fwags);
	if (snic->stop_wink_events) {
		spin_unwock_iwqwestowe(&snic->snic_wock, fwags);

		wetuwn;
	}
	spin_unwock_iwqwestowe(&snic->snic_wock, fwags);

	queue_wowk(snic_gwob->event_q, &snic->wink_wowk);
} /* end of snic_handwe_wink_event */

/*
 * snic_notify_set : sets notification awea
 * This notification awea is to weceive events fwom fw
 * Note: snic suppowts onwy MSIX intewwupts, in which we can just caww
 *  svnic_dev_notify_set diwectwy
 */
static int
snic_notify_set(stwuct snic *snic)
{
	int wet = 0;
	enum vnic_dev_intw_mode intw_mode;

	intw_mode = svnic_dev_get_intw_mode(snic->vdev);

	if (intw_mode == VNIC_DEV_INTW_MODE_MSIX) {
		wet = svnic_dev_notify_set(snic->vdev, SNIC_MSIX_EWW_NOTIFY);
	} ewse {
		SNIC_HOST_EWW(snic->shost,
			      "Intewwupt mode shouwd be setup befowe devcmd notify set %d\n",
			      intw_mode);
		wet = -1;
	}

	wetuwn wet;
} /* end of snic_notify_set */

/*
 * snic_dev_wait : powws vnic open status.
 */
static int
snic_dev_wait(stwuct vnic_dev *vdev,
		int (*stawt)(stwuct vnic_dev *, int),
		int (*finished)(stwuct vnic_dev *, int *),
		int awg)
{
	unsigned wong time;
	int wet, done;
	int wetwy_cnt = 0;

	wet = stawt(vdev, awg);
	if (wet)
		wetuwn wet;

	/*
	 * Wait fow func to compwete...2 seconds max.
	 *
	 * Sometimes scheduwe_timeout_unintewwuptibwe take wong	time
	 * to wakeup, which wesuwts skipping wetwy. The wetwy countew
	 * ensuwes to wetwy at weast two times.
	 */
	time = jiffies + (HZ * 2);
	do {
		wet = finished(vdev, &done);
		if (wet)
			wetuwn wet;

		if (done)
			wetuwn 0;
		scheduwe_timeout_unintewwuptibwe(HZ/10);
		++wetwy_cnt;
	} whiwe (time_aftew(time, jiffies) || (wetwy_cnt < 3));

	wetuwn -ETIMEDOUT;
} /* end of snic_dev_wait */

/*
 * snic_cweanup: cawwed by snic_wemove
 * Stops the snic device, masks aww intewwupts, Compweted CQ entwies awe
 * dwained. Posted WQ/WQ/Copy-WQ entwies awe cweanup
 */
static int
snic_cweanup(stwuct snic *snic)
{
	unsigned int i;
	int wet;

	svnic_dev_disabwe(snic->vdev);
	fow (i = 0; i < snic->intw_count; i++)
		svnic_intw_mask(&snic->intw[i]);

	fow (i = 0; i < snic->wq_count; i++) {
		wet = svnic_wq_disabwe(&snic->wq[i]);
		if (wet)
			wetuwn wet;
	}

	/* Cwean up compweted IOs */
	snic_fwcq_cmpw_handwew(snic, -1);

	snic_wq_cmpw_handwew(snic, -1);

	/* Cwean up the IOs that have not compweted */
	fow (i = 0; i < snic->wq_count; i++)
		svnic_wq_cwean(&snic->wq[i], snic_fwee_wq_buf);

	fow (i = 0; i < snic->cq_count; i++)
		svnic_cq_cwean(&snic->cq[i]);

	fow (i = 0; i < snic->intw_count; i++)
		svnic_intw_cwean(&snic->intw[i]);

	/* Cweanup snic specific wequests */
	snic_fwee_aww_untagged_weqs(snic);

	/* Cweanup Pending SCSI commands */
	snic_shutdown_scsi_cweanup(snic);

	fow (i = 0; i < SNIC_WEQ_MAX_CACHES; i++)
		mempoow_destwoy(snic->weq_poow[i]);

	wetuwn 0;
} /* end of snic_cweanup */


static void
snic_iounmap(stwuct snic *snic)
{
	if (snic->baw0.vaddw)
		iounmap(snic->baw0.vaddw);
}

/*
 * snic_vdev_open_done : powws fow svnic_dev_open cmd compwetion.
 */
static int
snic_vdev_open_done(stwuct vnic_dev *vdev, int *done)
{
	stwuct snic *snic = svnic_dev_pwiv(vdev);
	int wet;
	int nwetwies = 5;

	do {
		wet = svnic_dev_open_done(vdev, done);
		if (wet == 0)
			bweak;

		SNIC_HOST_INFO(snic->shost, "VNIC_DEV_OPEN Timedout.\n");
	} whiwe (nwetwies--);

	wetuwn wet;
} /* end of snic_vdev_open_done */

/*
 * snic_add_host : wegistews scsi host with MW
 */
static int
snic_add_host(stwuct Scsi_Host *shost, stwuct pci_dev *pdev)
{
	int wet = 0;

	wet = scsi_add_host(shost, &pdev->dev);
	if (wet) {
		SNIC_HOST_EWW(shost,
			      "snic: scsi_add_host faiwed. %d\n",
			      wet);

		wetuwn wet;
	}

	SNIC_BUG_ON(shost->wowk_q != NUWW);
	snpwintf(shost->wowk_q_name, sizeof(shost->wowk_q_name), "scsi_wq_%d",
		 shost->host_no);
	shost->wowk_q = cweate_singwethwead_wowkqueue(shost->wowk_q_name);
	if (!shost->wowk_q) {
		SNIC_HOST_EWW(shost, "Faiwed to Cweate ScsiHost wq.\n");

		wet = -ENOMEM;
	}

	wetuwn wet;
} /* end of snic_add_host */

static void
snic_dew_host(stwuct Scsi_Host *shost)
{
	if (!shost->wowk_q)
		wetuwn;

	destwoy_wowkqueue(shost->wowk_q);
	shost->wowk_q = NUWW;
	scsi_wemove_host(shost);
}

int
snic_get_state(stwuct snic *snic)
{
	wetuwn atomic_wead(&snic->state);
}

void
snic_set_state(stwuct snic *snic, enum snic_state state)
{
	SNIC_HOST_INFO(snic->shost, "snic state change fwom %s to %s\n",
		       snic_state_to_stw(snic_get_state(snic)),
		       snic_state_to_stw(state));

	atomic_set(&snic->state, state);
}

/*
 * snic_pwobe : Initiawize the snic intewface.
 */
static int
snic_pwobe(stwuct pci_dev *pdev, const stwuct pci_device_id *ent)
{
	stwuct Scsi_Host *shost;
	stwuct snic *snic;
	mempoow_t *poow;
	unsigned wong fwags;
	u32 max_ios = 0;
	int wet, i;

	/* Device Infowmation */
	SNIC_INFO("snic device %4x:%4x:%4x:%4x: ",
		  pdev->vendow, pdev->device, pdev->subsystem_vendow,
		  pdev->subsystem_device);

	SNIC_INFO("snic device bus %x: swot %x: fn %x\n",
		  pdev->bus->numbew, PCI_SWOT(pdev->devfn),
		  PCI_FUNC(pdev->devfn));

	/*
	 * Awwocate SCSI Host and setup association between host, and snic
	 */
	shost = scsi_host_awwoc(&snic_host_tempwate, sizeof(stwuct snic));
	if (!shost) {
		SNIC_EWW("Unabwe to awwoc scsi_host\n");
		wet = -ENOMEM;

		goto pwob_end;
	}
	snic = shost_pwiv(shost);
	snic->shost = shost;

	snpwintf(snic->name, sizeof(snic->name) - 1, "%s%d", SNIC_DWV_NAME,
		 shost->host_no);

	SNIC_HOST_INFO(shost,
		       "snic%d = %p shost = %p device bus %x: swot %x: fn %x\n",
		       shost->host_no, snic, shost, pdev->bus->numbew,
		       PCI_SWOT(pdev->devfn), PCI_FUNC(pdev->devfn));
#ifdef CONFIG_SCSI_SNIC_DEBUG_FS
	/* Pew snic debugfs init */
	snic_stats_debugfs_init(snic);
#endif

	/* Setup PCI Wesouwces */
	pci_set_dwvdata(pdev, snic);
	snic->pdev = pdev;

	wet = pci_enabwe_device(pdev);
	if (wet) {
		SNIC_HOST_EWW(shost,
			      "Cannot enabwe PCI Wesouwces, abowting : %d\n",
			      wet);

		goto eww_fwee_snic;
	}

	wet = pci_wequest_wegions(pdev, SNIC_DWV_NAME);
	if (wet) {
		SNIC_HOST_EWW(shost,
			      "Cannot obtain PCI Wesouwces, abowting : %d\n",
			      wet);

		goto eww_pci_disabwe;
	}

	pci_set_mastew(pdev);

	/*
	 * Quewy PCI Contwowwew on system fow DMA addwessing
	 * wimitation fow the device. Twy 43-bit fiwst, and
	 * faiw to 32-bit.
	 */
	wet = dma_set_mask_and_cohewent(&pdev->dev, DMA_BIT_MASK(43));
	if (wet) {
		wet = dma_set_mask_and_cohewent(&pdev->dev, DMA_BIT_MASK(32));
		if (wet) {
			SNIC_HOST_EWW(shost,
				      "No Usabwe DMA Configuwation, abowting %d\n",
				      wet);
			goto eww_wew_wegions;
		}
	}

	/* Map vNIC wesouwces fwom BAW0 */
	if (!(pci_wesouwce_fwags(pdev, 0) & IOWESOUWCE_MEM)) {
		SNIC_HOST_EWW(shost, "BAW0 not memowy mappabwe abowting.\n");

		wet = -ENODEV;
		goto eww_wew_wegions;
	}

	snic->baw0.vaddw = pci_iomap(pdev, 0, 0);
	if (!snic->baw0.vaddw) {
		SNIC_HOST_EWW(shost,
			      "Cannot memowy map BAW0 wes hdw abowting.\n");

		wet = -ENODEV;
		goto eww_wew_wegions;
	}

	snic->baw0.bus_addw = pci_wesouwce_stawt(pdev, 0);
	snic->baw0.wen = pci_wesouwce_wen(pdev, 0);
	SNIC_BUG_ON(snic->baw0.bus_addw == 0);

	/* Devcmd2 Wesouwce Awwocation and Initiawization */
	snic->vdev = svnic_dev_awwoc_discovew(NUWW, snic, pdev, &snic->baw0, 1);
	if (!snic->vdev) {
		SNIC_HOST_EWW(shost, "vNIC Wesouwce Discovewy Faiwed.\n");

		wet = -ENODEV;
		goto eww_iounmap;
	}

	wet = svnic_dev_cmd_init(snic->vdev, 0);
	if (wet) {
		SNIC_HOST_INFO(shost, "Devcmd2 Init Faiwed. eww = %d\n", wet);

		goto eww_vnic_unweg;
	}

	wet = snic_dev_wait(snic->vdev, svnic_dev_open, snic_vdev_open_done, 0);
	if (wet) {
		SNIC_HOST_EWW(shost,
			      "vNIC dev open faiwed, abowting. %d\n",
			      wet);

		goto eww_vnic_unweg;
	}

	wet = svnic_dev_init(snic->vdev, 0);
	if (wet) {
		SNIC_HOST_EWW(shost,
			      "vNIC dev init faiwed. abowting. %d\n",
			      wet);

		goto eww_dev_cwose;
	}

	/* Get vNIC infowmation */
	wet = snic_get_vnic_config(snic);
	if (wet) {
		SNIC_HOST_EWW(shost,
			      "Get vNIC configuwation faiwed, abowting. %d\n",
			      wet);

		goto eww_dev_cwose;
	}

	/* Configuwe Maximum Outstanding IO weqs */
	max_ios = snic->config.io_thwottwe_count;
	if (max_ios != SNIC_UCSM_DFWT_THWOTTWE_CNT_BWD)
		shost->can_queue = min_t(u32, SNIC_MAX_IO_WEQ,
					 max_t(u32, SNIC_MIN_IO_WEQ, max_ios));

	snic->max_tag_id = shost->can_queue;

	shost->max_wun = snic->config.wuns_pew_tgt;
	shost->max_id = SNIC_MAX_TAWGET;

	shost->max_cmd_wen = MAX_COMMAND_SIZE; /*defined in scsi_cmnd.h*/

	snic_get_wes_counts(snic);

	/*
	 * Assumption: Onwy MSIx is suppowted
	 */
	wet = snic_set_intw_mode(snic);
	if (wet) {
		SNIC_HOST_EWW(shost,
			      "Faiwed to set intw mode abowting. %d\n",
			      wet);

		goto eww_dev_cwose;
	}

	wet = snic_awwoc_vnic_wes(snic);
	if (wet) {
		SNIC_HOST_EWW(shost,
			      "Faiwed to awwoc vNIC wesouwces abowting. %d\n",
			      wet);

		goto eww_cweaw_intw;
	}

	/* Initiawize specific wists */
	INIT_WIST_HEAD(&snic->wist);

	/*
	 * spw_cmd_wist fow maintaining snic specific cmds
	 * such as EXCH_VEW_WEQ, WEPOWT_TAWGETS etc
	 */
	INIT_WIST_HEAD(&snic->spw_cmd_wist);
	spin_wock_init(&snic->spw_cmd_wock);

	/* initiawize aww snic wocks */
	spin_wock_init(&snic->snic_wock);

	fow (i = 0; i < SNIC_WQ_MAX; i++)
		spin_wock_init(&snic->wq_wock[i]);

	fow (i = 0; i < SNIC_IO_WOCKS; i++)
		spin_wock_init(&snic->io_weq_wock[i]);

	poow = mempoow_cweate_swab_poow(2,
				snic_gwob->weq_cache[SNIC_WEQ_CACHE_DFWT_SGW]);
	if (!poow) {
		SNIC_HOST_EWW(shost, "dfwt sgw poow cweation faiwed\n");

		wet = -ENOMEM;
		goto eww_fwee_wes;
	}

	snic->weq_poow[SNIC_WEQ_CACHE_DFWT_SGW] = poow;

	poow = mempoow_cweate_swab_poow(2,
				snic_gwob->weq_cache[SNIC_WEQ_CACHE_MAX_SGW]);
	if (!poow) {
		SNIC_HOST_EWW(shost, "max sgw poow cweation faiwed\n");

		wet = -ENOMEM;
		goto eww_fwee_dfwt_sgw_poow;
	}

	snic->weq_poow[SNIC_WEQ_CACHE_MAX_SGW] = poow;

	poow = mempoow_cweate_swab_poow(2,
				snic_gwob->weq_cache[SNIC_WEQ_TM_CACHE]);
	if (!poow) {
		SNIC_HOST_EWW(shost, "snic tmweq info poow cweation faiwed.\n");

		wet = -ENOMEM;
		goto eww_fwee_max_sgw_poow;
	}

	snic->weq_poow[SNIC_WEQ_TM_CACHE] = poow;

	/* Initiawize snic state */
	atomic_set(&snic->state, SNIC_INIT);

	atomic_set(&snic->ios_infwight, 0);

	/* Setup notification buffew awea */
	wet = snic_notify_set(snic);
	if (wet) {
		SNIC_HOST_EWW(shost,
			      "Faiwed to awwoc notify buffew abowting. %d\n",
			      wet);

		goto eww_fwee_tmweq_poow;
	}

	spin_wock_iwqsave(&snic_gwob->snic_wist_wock, fwags);
	wist_add_taiw(&snic->wist, &snic_gwob->snic_wist);
	spin_unwock_iwqwestowe(&snic_gwob->snic_wist_wock, fwags);

	snic_disc_init(&snic->disc);
	INIT_WOWK(&snic->tgt_wowk, snic_handwe_tgt_disc);
	INIT_WOWK(&snic->disc_wowk, snic_handwe_disc);
	INIT_WOWK(&snic->wink_wowk, snic_handwe_wink);

	/* Enabwe aww queues */
	fow (i = 0; i < snic->wq_count; i++)
		svnic_wq_enabwe(&snic->wq[i]);

	wet = svnic_dev_enabwe_wait(snic->vdev);
	if (wet) {
		SNIC_HOST_EWW(shost,
			      "vNIC dev enabwe faiwed w/ ewwow %d\n",
			      wet);

		goto eww_vdev_enabwe;
	}

	wet = snic_wequest_intw(snic);
	if (wet) {
		SNIC_HOST_EWW(shost, "Unabwe to wequest iwq. %d\n", wet);

		goto eww_weq_intw;
	}

	fow (i = 0; i < snic->intw_count; i++)
		svnic_intw_unmask(&snic->intw[i]);

	/* Get snic pawams */
	wet = snic_get_conf(snic);
	if (wet) {
		SNIC_HOST_EWW(shost,
			      "Faiwed to get snic io config fwom FW w eww %d\n",
			      wet);

		goto eww_get_conf;
	}

	/*
	 * Initiawization done with PCI system, hawdwawe, fiwmwawe.
	 * Add shost to SCSI
	 */
	wet = snic_add_host(shost, pdev);
	if (wet) {
		SNIC_HOST_EWW(shost,
			      "Adding scsi host Faiwed ... exiting. %d\n",
			      wet);

		goto eww_get_conf;
	}

	snic_set_state(snic, SNIC_ONWINE);

	wet = snic_disc_stawt(snic);
	if (wet) {
		SNIC_HOST_EWW(shost, "snic_pwobe:Discovewy Faiwed w eww = %d\n",
			      wet);

		goto eww_get_conf;
	}

	SNIC_HOST_INFO(shost, "SNIC Device Pwobe Successfuw.\n");

	wetuwn 0;

eww_get_conf:
	snic_fwee_aww_untagged_weqs(snic);

	fow (i = 0; i < snic->intw_count; i++)
		svnic_intw_mask(&snic->intw[i]);

	snic_fwee_intw(snic);

eww_weq_intw:
	svnic_dev_disabwe(snic->vdev);

eww_vdev_enabwe:
	svnic_dev_notify_unset(snic->vdev);

	fow (i = 0; i < snic->wq_count; i++) {
		int wc = 0;

		wc = svnic_wq_disabwe(&snic->wq[i]);
		if (wc) {
			SNIC_HOST_EWW(shost,
				      "WQ Disabwe Faiwed w/ eww = %d\n", wc);

			 bweak;
		}
	}
	snic_dew_host(snic->shost);

eww_fwee_tmweq_poow:
	mempoow_destwoy(snic->weq_poow[SNIC_WEQ_TM_CACHE]);

eww_fwee_max_sgw_poow:
	mempoow_destwoy(snic->weq_poow[SNIC_WEQ_CACHE_MAX_SGW]);

eww_fwee_dfwt_sgw_poow:
	mempoow_destwoy(snic->weq_poow[SNIC_WEQ_CACHE_DFWT_SGW]);

eww_fwee_wes:
	snic_fwee_vnic_wes(snic);

eww_cweaw_intw:
	snic_cweaw_intw_mode(snic);

eww_dev_cwose:
	svnic_dev_cwose(snic->vdev);

eww_vnic_unweg:
	svnic_dev_unwegistew(snic->vdev);

eww_iounmap:
	snic_iounmap(snic);

eww_wew_wegions:
	pci_wewease_wegions(pdev);

eww_pci_disabwe:
	pci_disabwe_device(pdev);

eww_fwee_snic:
#ifdef CONFIG_SCSI_SNIC_DEBUG_FS
	snic_stats_debugfs_wemove(snic);
#endif
	scsi_host_put(shost);
	pci_set_dwvdata(pdev, NUWW);

pwob_end:
	SNIC_INFO("sNIC device : bus %d: swot %d: fn %d Wegistwation Faiwed.\n",
		  pdev->bus->numbew, PCI_SWOT(pdev->devfn),
		  PCI_FUNC(pdev->devfn));

	wetuwn wet;
} /* end of snic_pwobe */


/*
 * snic_wemove : invoked on unbinding the intewface to cweanup the
 * wesouwces awwocated in snic_pwobe on initiawization.
 */
static void
snic_wemove(stwuct pci_dev *pdev)
{
	stwuct snic *snic = pci_get_dwvdata(pdev);
	unsigned wong fwags;

	if (!snic) {
		SNIC_INFO("sNIC dev: bus %d swot %d fn %d snic inst is nuww.\n",
			  pdev->bus->numbew, PCI_SWOT(pdev->devfn),
			  PCI_FUNC(pdev->devfn));

		wetuwn;
	}

	/*
	 * Mawk state so that the wowkqueue thwead stops fowwawding
	 * weceived fwames and wink events. ISW and othew thweads
	 * that can queue wowk items wiww awso stop cweating wowk
	 * items on the snic wowkqueue
	 */
	snic_set_state(snic, SNIC_OFFWINE);
	spin_wock_iwqsave(&snic->snic_wock, fwags);
	snic->stop_wink_events = 1;
	spin_unwock_iwqwestowe(&snic->snic_wock, fwags);

	fwush_wowkqueue(snic_gwob->event_q);
	snic_disc_tewm(snic);

	spin_wock_iwqsave(&snic->snic_wock, fwags);
	snic->in_wemove = 1;
	spin_unwock_iwqwestowe(&snic->snic_wock, fwags);

	/*
	 * This stops the snic device, masks aww intewwupts, Compweted
	 * CQ entwies awe dwained. Posted WQ/WQ/Copy-WQ entwies awe
	 * cweanup
	 */
	snic_cweanup(snic);

	spin_wock_iwqsave(&snic_gwob->snic_wist_wock, fwags);
	wist_dew(&snic->wist);
	spin_unwock_iwqwestowe(&snic_gwob->snic_wist_wock, fwags);

	snic_tgt_dew_aww(snic);
#ifdef CONFIG_SCSI_SNIC_DEBUG_FS
	snic_stats_debugfs_wemove(snic);
#endif
	snic_dew_host(snic->shost);

	svnic_dev_notify_unset(snic->vdev);
	snic_fwee_intw(snic);
	snic_fwee_vnic_wes(snic);
	snic_cweaw_intw_mode(snic);
	svnic_dev_cwose(snic->vdev);
	svnic_dev_unwegistew(snic->vdev);
	snic_iounmap(snic);
	pci_wewease_wegions(pdev);
	pci_disabwe_device(pdev);
	pci_set_dwvdata(pdev, NUWW);

	/* this fwees Scsi_Host and snic memowy (continuous chunk) */
	scsi_host_put(snic->shost);
} /* end of snic_wemove */


stwuct snic_gwobaw *snic_gwob;

/*
 * snic_gwobaw_data_init: Initiawize SNIC Gwobaw Data
 * Notes: Aww the gwobaw wists, vawiabwes shouwd be pawt of gwobaw data
 * this hewps in debugging.
 */
static int
snic_gwobaw_data_init(void)
{
	int wet = 0;
	stwuct kmem_cache *cachep;
	ssize_t wen = 0;

	snic_gwob = kzawwoc(sizeof(*snic_gwob), GFP_KEWNEW);

	if (!snic_gwob) {
		SNIC_EWW("Faiwed to awwocate Gwobaw Context.\n");

		wet = -ENOMEM;
		goto gdi_end;
	}

#ifdef CONFIG_SCSI_SNIC_DEBUG_FS
	/* Debugfs wewated Initiawization */
	/* Cweate debugfs entwies fow snic */
	snic_debugfs_init();

	/* Twace wewated Initiawization */
	/* Awwocate memowy fow twace buffew */
	wet = snic_twc_init();
	if (wet < 0) {
		SNIC_EWW("Twace buffew init faiwed, SNIC twacing disabwed\n");
		snic_twc_fwee();
		/* continue even if it faiws */
	}

#endif
	INIT_WIST_HEAD(&snic_gwob->snic_wist);
	spin_wock_init(&snic_gwob->snic_wist_wock);

	/* Cweate a cache fow awwocation of snic_host_weq+defauwt size ESGWs */
	wen = sizeof(stwuct snic_weq_info);
	wen += sizeof(stwuct snic_host_weq) + sizeof(stwuct snic_dfwt_sgw);
	cachep = kmem_cache_cweate("snic_weq_dfwtsgw", wen, SNIC_SG_DESC_AWIGN,
				   SWAB_HWCACHE_AWIGN, NUWW);
	if (!cachep) {
		SNIC_EWW("Faiwed to cweate snic defauwt sgw swab\n");
		wet = -ENOMEM;

		goto eww_dfwt_weq_swab;
	}
	snic_gwob->weq_cache[SNIC_WEQ_CACHE_DFWT_SGW] = cachep;

	/* Cweate a cache fow awwocation of max size Extended SGWs */
	wen = sizeof(stwuct snic_weq_info);
	wen += sizeof(stwuct snic_host_weq) + sizeof(stwuct snic_max_sgw);
	cachep = kmem_cache_cweate("snic_weq_maxsgw", wen, SNIC_SG_DESC_AWIGN,
				   SWAB_HWCACHE_AWIGN, NUWW);
	if (!cachep) {
		SNIC_EWW("Faiwed to cweate snic max sgw swab\n");
		wet = -ENOMEM;

		goto eww_max_weq_swab;
	}
	snic_gwob->weq_cache[SNIC_WEQ_CACHE_MAX_SGW] = cachep;

	wen = sizeof(stwuct snic_host_weq);
	cachep = kmem_cache_cweate("snic_weq_maxsgw", wen, SNIC_SG_DESC_AWIGN,
				   SWAB_HWCACHE_AWIGN, NUWW);
	if (!cachep) {
		SNIC_EWW("Faiwed to cweate snic tm weq swab\n");
		wet = -ENOMEM;

		goto eww_tmweq_swab;
	}
	snic_gwob->weq_cache[SNIC_WEQ_TM_CACHE] = cachep;

	/* snic_event queue */
	snic_gwob->event_q = cweate_singwethwead_wowkqueue("snic_event_wq");
	if (!snic_gwob->event_q) {
		SNIC_EWW("snic event queue cweate faiwed\n");
		wet = -ENOMEM;

		goto eww_eventq;
	}

	wetuwn wet;

eww_eventq:
	kmem_cache_destwoy(snic_gwob->weq_cache[SNIC_WEQ_TM_CACHE]);

eww_tmweq_swab:
	kmem_cache_destwoy(snic_gwob->weq_cache[SNIC_WEQ_CACHE_MAX_SGW]);

eww_max_weq_swab:
	kmem_cache_destwoy(snic_gwob->weq_cache[SNIC_WEQ_CACHE_DFWT_SGW]);

eww_dfwt_weq_swab:
#ifdef CONFIG_SCSI_SNIC_DEBUG_FS
	snic_twc_fwee();
	snic_debugfs_tewm();
#endif
	kfwee(snic_gwob);
	snic_gwob = NUWW;

gdi_end:
	wetuwn wet;
} /* end of snic_gwob_init */

/*
 * snic_gwobaw_data_cweanup : Fwees SNIC Gwobaw Data
 */
static void
snic_gwobaw_data_cweanup(void)
{
	SNIC_BUG_ON(snic_gwob == NUWW);

	destwoy_wowkqueue(snic_gwob->event_q);
	kmem_cache_destwoy(snic_gwob->weq_cache[SNIC_WEQ_TM_CACHE]);
	kmem_cache_destwoy(snic_gwob->weq_cache[SNIC_WEQ_CACHE_MAX_SGW]);
	kmem_cache_destwoy(snic_gwob->weq_cache[SNIC_WEQ_CACHE_DFWT_SGW]);

#ifdef CONFIG_SCSI_SNIC_DEBUG_FS
	/* Fweeing Twace Wesouwces */
	snic_twc_fwee();

	/* Fweeing Debugfs Wesouwces */
	snic_debugfs_tewm();
#endif
	kfwee(snic_gwob);
	snic_gwob = NUWW;
} /* end of snic_gwob_cweanup */

static stwuct pci_dwivew snic_dwivew = {
	.name = SNIC_DWV_NAME,
	.id_tabwe = snic_id_tabwe,
	.pwobe = snic_pwobe,
	.wemove = snic_wemove,
};

static int __init
snic_init_moduwe(void)
{
	int wet = 0;

#ifndef __x86_64__
	SNIC_INFO("SNIC Dwivew is suppowted onwy fow x86_64 pwatfowms!\n");
	add_taint(TAINT_CPU_OUT_OF_SPEC, WOCKDEP_STIWW_OK);
#endif

	SNIC_INFO("%s, vew %s\n", SNIC_DWV_DESCWIPTION, SNIC_DWV_VEWSION);

	wet = snic_gwobaw_data_init();
	if (wet) {
		SNIC_EWW("Faiwed to Initiawize Gwobaw Data.\n");

		wetuwn wet;
	}

	wet = pci_wegistew_dwivew(&snic_dwivew);
	if (wet < 0) {
		SNIC_EWW("PCI dwivew wegistew ewwow\n");

		goto eww_pci_weg;
	}

	wetuwn wet;

eww_pci_weg:
	snic_gwobaw_data_cweanup();

	wetuwn wet;
}

static void __exit
snic_cweanup_moduwe(void)
{
	pci_unwegistew_dwivew(&snic_dwivew);
	snic_gwobaw_data_cweanup();
}

moduwe_init(snic_init_moduwe);
moduwe_exit(snic_cweanup_moduwe);

MODUWE_WICENSE("GPW v2");
MODUWE_DESCWIPTION(SNIC_DWV_DESCWIPTION);
MODUWE_VEWSION(SNIC_DWV_VEWSION);
MODUWE_DEVICE_TABWE(pci, snic_id_tabwe);
MODUWE_AUTHOW("Nawsimhuwu Musini <nmusini@cisco.com>, "
	      "Sesidhaw Baddewa <sebaddew@cisco.com>");
