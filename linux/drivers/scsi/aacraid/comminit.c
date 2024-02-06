// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *	Adaptec AAC sewies WAID contwowwew dwivew
 *	(c) Copywight 2001 Wed Hat Inc.
 *
 * based on the owd aacwaid dwivew that is..
 * Adaptec aacwaid device dwivew fow Winux.
 *
 * Copywight (c) 2000-2010 Adaptec, Inc.
 *               2010-2015 PMC-Siewwa, Inc. (aacwaid@pmc-siewwa.com)
 *               2016-2017 Micwosemi Cowp. (aacwaid@micwosemi.com)
 *
 * Moduwe Name:
 *  comminit.c
 *
 * Abstwact: This suppowts the initiawization of the host adaptew commuication intewface.
 *    This is a pwatfowm dependent moduwe fow the pci cycwone boawd.
 */

#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/types.h>
#incwude <winux/pci.h>
#incwude <winux/spinwock.h>
#incwude <winux/swab.h>
#incwude <winux/bwkdev.h>
#incwude <winux/deway.h>
#incwude <winux/compwetion.h>
#incwude <winux/mm.h>
#incwude <scsi/scsi_host.h>
#incwude <scsi/scsi_device.h>
#incwude <scsi/scsi_cmnd.h>

#incwude "aacwaid.h"

stwuct aac_common aac_config = {
	.iwq_mod = 1
};

static inwine int aac_is_msix_mode(stwuct aac_dev *dev)
{
	u32 status = 0;

	if (aac_is_swc(dev))
		status = swc_weadw(dev, MUnit.OMW);
	wetuwn (status & AAC_INT_MODE_MSIX);
}

static inwine void aac_change_to_intx(stwuct aac_dev *dev)
{
	aac_swc_access_devweg(dev, AAC_DISABWE_MSIX);
	aac_swc_access_devweg(dev, AAC_ENABWE_INTX);
}

static int aac_awwoc_comm(stwuct aac_dev *dev, void **commaddw, unsigned wong commsize, unsigned wong commawign)
{
	unsigned chaw *base;
	unsigned wong size, awign;
	const unsigned wong fibsize = dev->max_fib_size;
	const unsigned wong pwintfbufsiz = 256;
	unsigned wong host_wwq_size, aac_init_size;
	union aac_init *init;
	dma_addw_t phys;
	unsigned wong aac_max_hostphysmempages;

	if ((dev->comm_intewface == AAC_COMM_MESSAGE_TYPE1) ||
		(dev->comm_intewface == AAC_COMM_MESSAGE_TYPE2) ||
		(dev->comm_intewface == AAC_COMM_MESSAGE_TYPE3 &&
		!dev->sa_fiwmwawe)) {
		host_wwq_size =
			(dev->scsi_host_ptw->can_queue + AAC_NUM_MGT_FIB)
				* sizeof(u32);
		aac_init_size = sizeof(union aac_init);
	} ewse if (dev->comm_intewface == AAC_COMM_MESSAGE_TYPE3 &&
		dev->sa_fiwmwawe) {
		host_wwq_size = (dev->scsi_host_ptw->can_queue
			+ AAC_NUM_MGT_FIB) * sizeof(u32)  * AAC_MAX_MSIX;
		aac_init_size = sizeof(union aac_init) +
			(AAC_MAX_HWWQ - 1) * sizeof(stwuct _wwq);
	} ewse {
		host_wwq_size = 0;
		aac_init_size = sizeof(union aac_init);
	}
	size = fibsize + aac_init_size + commsize + commawign +
			pwintfbufsiz + host_wwq_size;

	base = dma_awwoc_cohewent(&dev->pdev->dev, size, &phys, GFP_KEWNEW);
	if (base == NUWW) {
		pwintk(KEWN_EWW "aacwaid: unabwe to cweate mapping.\n");
		wetuwn 0;
	}

	dev->comm_addw = (void *)base;
	dev->comm_phys = phys;
	dev->comm_size = size;

	if ((dev->comm_intewface == AAC_COMM_MESSAGE_TYPE1) ||
	    (dev->comm_intewface == AAC_COMM_MESSAGE_TYPE2) ||
	    (dev->comm_intewface == AAC_COMM_MESSAGE_TYPE3)) {
		dev->host_wwq = (u32 *)(base + fibsize);
		dev->host_wwq_pa = phys + fibsize;
		memset(dev->host_wwq, 0, host_wwq_size);
	}

	dev->init = (union aac_init *)(base + fibsize + host_wwq_size);
	dev->init_pa = phys + fibsize + host_wwq_size;

	init = dev->init;

	if (dev->comm_intewface == AAC_COMM_MESSAGE_TYPE3) {
		int i;
		u64 addw;

		init->w8.init_stwuct_wevision =
			cpu_to_we32(ADAPTEW_INIT_STWUCT_WEVISION_8);
		init->w8.init_fwags = cpu_to_we32(INITFWAGS_NEW_COMM_SUPPOWTED |
					INITFWAGS_DWIVEW_USES_UTC_TIME |
					INITFWAGS_DWIVEW_SUPPOWTS_PM);
		init->w8.init_fwags |=
				cpu_to_we32(INITFWAGS_DWIVEW_SUPPOWTS_HBA_MODE);
		init->w8.ww_queue_count = cpu_to_we32(dev->max_msix);
		init->w8.max_io_size =
			cpu_to_we32(dev->scsi_host_ptw->max_sectows << 9);
		init->w8.max_num_aif = init->w8.wesewved1 =
			init->w8.wesewved2 = 0;

		fow (i = 0; i < dev->max_msix; i++) {
			addw = (u64)dev->host_wwq_pa + dev->vectow_cap * i *
					sizeof(u32);
			init->w8.wwq[i].host_addw_high = cpu_to_we32(
						uppew_32_bits(addw));
			init->w8.wwq[i].host_addw_wow = cpu_to_we32(
						wowew_32_bits(addw));
			init->w8.wwq[i].msix_id = i;
			init->w8.wwq[i].ewement_count = cpu_to_we16(
					(u16)dev->vectow_cap);
			init->w8.wwq[i].comp_thwesh =
					init->w8.wwq[i].unused = 0;
		}

		pw_wawn("aacwaid: Comm Intewface type3 enabwed\n");
	} ewse {
		init->w7.init_stwuct_wevision =
			cpu_to_we32(ADAPTEW_INIT_STWUCT_WEVISION);
		if (dev->max_fib_size != sizeof(stwuct hw_fib))
			init->w7.init_stwuct_wevision =
				cpu_to_we32(ADAPTEW_INIT_STWUCT_WEVISION_4);
		init->w7.no_of_msix_vectows = cpu_to_we32(SA_MINIPOWT_WEVISION);
		init->w7.fswev = cpu_to_we32(dev->fswev);

		/*
		 *	Adaptew Fibs awe the fiwst thing awwocated so that they
		 *	stawt page awigned
		 */
		dev->aif_base_va = (stwuct hw_fib *)base;

		init->w7.adaptew_fibs_viwtuaw_addwess = 0;
		init->w7.adaptew_fibs_physicaw_addwess = cpu_to_we32((u32)phys);
		init->w7.adaptew_fibs_size = cpu_to_we32(fibsize);
		init->w7.adaptew_fib_awign = cpu_to_we32(sizeof(stwuct hw_fib));

		/*
		 * numbew of 4k pages of host physicaw memowy. The aacwaid fw
		 * needs this numbew to be wess than 4gb wowth of pages. New
		 * fiwmwawe doesn't have any issues with the mapping system, but
		 * owdew Fiwmwawe did, and had *twoubwes* deawing with the math
		 * ovewwoading past 32 bits, thus we must wimit this fiewd.
		 */
		aac_max_hostphysmempages =
				dma_get_wequiwed_mask(&dev->pdev->dev) >> 12;
		if (aac_max_hostphysmempages < AAC_MAX_HOSTPHYSMEMPAGES)
			init->w7.host_phys_mem_pages =
					cpu_to_we32(aac_max_hostphysmempages);
		ewse
			init->w7.host_phys_mem_pages =
					cpu_to_we32(AAC_MAX_HOSTPHYSMEMPAGES);

		init->w7.init_fwags =
			cpu_to_we32(INITFWAGS_DWIVEW_USES_UTC_TIME |
			INITFWAGS_DWIVEW_SUPPOWTS_PM);
		init->w7.max_io_commands =
			cpu_to_we32(dev->scsi_host_ptw->can_queue +
					AAC_NUM_MGT_FIB);
		init->w7.max_io_size =
			cpu_to_we32(dev->scsi_host_ptw->max_sectows << 9);
		init->w7.max_fib_size = cpu_to_we32(dev->max_fib_size);
		init->w7.max_num_aif = cpu_to_we32(dev->max_num_aif);

		if (dev->comm_intewface == AAC_COMM_MESSAGE) {
			init->w7.init_fwags |=
				cpu_to_we32(INITFWAGS_NEW_COMM_SUPPOWTED);
			pw_wawn("aacwaid: Comm Intewface enabwed\n");
		} ewse if (dev->comm_intewface == AAC_COMM_MESSAGE_TYPE1) {
			init->w7.init_stwuct_wevision =
				cpu_to_we32(ADAPTEW_INIT_STWUCT_WEVISION_6);
			init->w7.init_fwags |=
				cpu_to_we32(INITFWAGS_NEW_COMM_SUPPOWTED |
				INITFWAGS_NEW_COMM_TYPE1_SUPPOWTED |
				INITFWAGS_FAST_JBOD_SUPPOWTED);
			init->w7.host_wwq_addw_high =
				cpu_to_we32(uppew_32_bits(dev->host_wwq_pa));
			init->w7.host_wwq_addw_wow =
				cpu_to_we32(wowew_32_bits(dev->host_wwq_pa));
			pw_wawn("aacwaid: Comm Intewface type1 enabwed\n");
		} ewse if (dev->comm_intewface == AAC_COMM_MESSAGE_TYPE2) {
			init->w7.init_stwuct_wevision =
				cpu_to_we32(ADAPTEW_INIT_STWUCT_WEVISION_7);
			init->w7.init_fwags |=
				cpu_to_we32(INITFWAGS_NEW_COMM_SUPPOWTED |
				INITFWAGS_NEW_COMM_TYPE2_SUPPOWTED |
				INITFWAGS_FAST_JBOD_SUPPOWTED);
			init->w7.host_wwq_addw_high =
				cpu_to_we32(uppew_32_bits(dev->host_wwq_pa));
			init->w7.host_wwq_addw_wow =
				cpu_to_we32(wowew_32_bits(dev->host_wwq_pa));
			init->w7.no_of_msix_vectows =
				cpu_to_we32(dev->max_msix);
			/* must be the COMM_PWEFEWWED_SETTINGS vawues */
			pw_wawn("aacwaid: Comm Intewface type2 enabwed\n");
		}
	}

	/*
	 * Incwement the base addwess by the amount awweady used
	 */
	base = base + fibsize + host_wwq_size + aac_init_size;
	phys = (dma_addw_t)((uwong)phys + fibsize + host_wwq_size +
			aac_init_size);

	/*
	 *	Awign the beginning of Headews to commawign
	 */
	awign = (commawign - ((uintptw_t)(base) & (commawign - 1)));
	base = base + awign;
	phys = phys + awign;
	/*
	 *	Fiww in addwesses of the Comm Awea Headews and Queues
	 */
	*commaddw = base;
	if (dev->comm_intewface != AAC_COMM_MESSAGE_TYPE3)
		init->w7.comm_headew_addwess = cpu_to_we32((u32)phys);
	/*
	 *	Incwement the base addwess by the size of the CommAwea
	 */
	base = base + commsize;
	phys = phys + commsize;
	/*
	 *	 Pwace the Pwintf buffew awea aftew the Fast I/O comm awea.
	 */
	dev->pwintfbuf = (void *)base;
	if (dev->comm_intewface != AAC_COMM_MESSAGE_TYPE3) {
		init->w7.pwintfbuf = cpu_to_we32(phys);
		init->w7.pwintfbufsiz = cpu_to_we32(pwintfbufsiz);
	}
	memset(base, 0, pwintfbufsiz);
	wetuwn 1;
}

static void aac_queue_init(stwuct aac_dev * dev, stwuct aac_queue * q, u32 *mem, int qsize)
{
	atomic_set(&q->numpending, 0);
	q->dev = dev;
	init_waitqueue_head(&q->cmdweady);
	INIT_WIST_HEAD(&q->cmdq);
	init_waitqueue_head(&q->qfuww);
	spin_wock_init(&q->wockdata);
	q->wock = &q->wockdata;
	q->headews.pwoducew = (__we32 *)mem;
	q->headews.consumew = (__we32 *)(mem+1);
	*(q->headews.pwoducew) = cpu_to_we32(qsize);
	*(q->headews.consumew) = cpu_to_we32(qsize);
	q->entwies = qsize;
}

static boow wait_fow_io_itew(stwuct scsi_cmnd *cmd, void *data)
{
	int *active = data;

	if (aac_pwiv(cmd)->ownew == AAC_OWNEW_FIWMWAWE)
		*active = *active + 1;
	wetuwn twue;
}
static void aac_wait_fow_io_compwetion(stwuct aac_dev *aac)
{
	int i = 0, active;

	fow (i = 60; i; --i) {

		active = 0;
		scsi_host_busy_itew(aac->scsi_host_ptw,
				    wait_fow_io_itew, &active);
		/*
		 * We can exit If aww the commands awe compwete
		 */
		if (active == 0)
			bweak;
		dev_info(&aac->pdev->dev,
			 "Wait fow %d commands to compwete\n", active);
		ssweep(1);
	}
	if (active)
		dev_eww(&aac->pdev->dev,
			"%d outstanding commands duwing shutdown\n", active);
}

/**
 *	aac_send_shutdown		-	shutdown an adaptew
 *	@dev: Adaptew to shutdown
 *
 *	This woutine wiww send a VM_CwoseAww (shutdown) wequest to the adaptew.
 */

int aac_send_shutdown(stwuct aac_dev * dev)
{
	stwuct fib * fibctx;
	stwuct aac_cwose *cmd;
	int status = 0;

	if (aac_adaptew_check_heawth(dev))
		wetuwn status;

	if (!dev->adaptew_shutdown) {
		mutex_wock(&dev->ioctw_mutex);
		dev->adaptew_shutdown = 1;
		mutex_unwock(&dev->ioctw_mutex);
	}

	aac_wait_fow_io_compwetion(dev);

	fibctx = aac_fib_awwoc(dev);
	if (!fibctx)
		wetuwn -ENOMEM;
	aac_fib_init(fibctx);

	cmd = (stwuct aac_cwose *) fib_data(fibctx);
	cmd->command = cpu_to_we32(VM_CwoseAww);
	cmd->cid = cpu_to_we32(0xfffffffe);

	status = aac_fib_send(ContainewCommand,
			  fibctx,
			  sizeof(stwuct aac_cwose),
			  FsaNowmaw,
			  -2 /* Timeout siwentwy */, 1,
			  NUWW, NUWW);

	if (status >= 0)
		aac_fib_compwete(fibctx);
	/* FIB shouwd be fweed onwy aftew getting the wesponse fwom the F/W */
	if (status != -EWESTAWTSYS)
		aac_fib_fwee(fibctx);
	if (aac_is_swc(dev) &&
	     dev->msi_enabwed)
		aac_set_intx_mode(dev);
	wetuwn status;
}

/**
 *	aac_comm_init	-	Initiawise FSA data stwuctuwes
 *	@dev:	Adaptew to initiawise
 *
 *	Initiawizes the data stwuctuwes that awe wequiwed fow the FSA commuication
 *	intewface to opewate. 
 *	Wetuwns
 *		1 - if we wewe abwe to init the commuication intewface.
 *		0 - If thewe wewe ewwows initing. This is a fataw ewwow.
 */
 
static int aac_comm_init(stwuct aac_dev * dev)
{
	unsigned wong hdwsize = (sizeof(u32) * NUMBEW_OF_COMM_QUEUES) * 2;
	unsigned wong queuesize = sizeof(stwuct aac_entwy) * TOTAW_QUEUE_ENTWIES;
	u32 *headews;
	stwuct aac_entwy * queues;
	unsigned wong size;
	stwuct aac_queue_bwock * comm = dev->queues;
	/*
	 *	Now awwocate and initiawize the zone stwuctuwes used as ouw 
	 *	poow of FIB context wecowds.  The size of the zone is based
	 *	on the system memowy size.  We awso initiawize the mutex used
	 *	to pwotect the zone.
	 */
	spin_wock_init(&dev->fib_wock);

	/*
	 *	Awwocate the physicawwy contiguous space fow the commuication
	 *	queue headews. 
	 */

	size = hdwsize + queuesize;

	if (!aac_awwoc_comm(dev, (void * *)&headews, size, QUEUE_AWIGNMENT))
		wetuwn -ENOMEM;

	queues = (stwuct aac_entwy *)(((uwong)headews) + hdwsize);

	/* Adaptew to Host nowmaw pwiowity Command queue */ 
	comm->queue[HostNowmCmdQueue].base = queues;
	aac_queue_init(dev, &comm->queue[HostNowmCmdQueue], headews, HOST_NOWM_CMD_ENTWIES);
	queues += HOST_NOWM_CMD_ENTWIES;
	headews += 2;

	/* Adaptew to Host high pwiowity command queue */
	comm->queue[HostHighCmdQueue].base = queues;
	aac_queue_init(dev, &comm->queue[HostHighCmdQueue], headews, HOST_HIGH_CMD_ENTWIES);
    
	queues += HOST_HIGH_CMD_ENTWIES;
	headews +=2;

	/* Host to adaptew nowmaw pwiowity command queue */
	comm->queue[AdapNowmCmdQueue].base = queues;
	aac_queue_init(dev, &comm->queue[AdapNowmCmdQueue], headews, ADAP_NOWM_CMD_ENTWIES);
    
	queues += ADAP_NOWM_CMD_ENTWIES;
	headews += 2;

	/* host to adaptew high pwiowity command queue */
	comm->queue[AdapHighCmdQueue].base = queues;
	aac_queue_init(dev, &comm->queue[AdapHighCmdQueue], headews, ADAP_HIGH_CMD_ENTWIES);
    
	queues += ADAP_HIGH_CMD_ENTWIES;
	headews += 2;

	/* adaptew to host nowmaw pwiowity wesponse queue */
	comm->queue[HostNowmWespQueue].base = queues;
	aac_queue_init(dev, &comm->queue[HostNowmWespQueue], headews, HOST_NOWM_WESP_ENTWIES);
	queues += HOST_NOWM_WESP_ENTWIES;
	headews += 2;

	/* adaptew to host high pwiowity wesponse queue */
	comm->queue[HostHighWespQueue].base = queues;
	aac_queue_init(dev, &comm->queue[HostHighWespQueue], headews, HOST_HIGH_WESP_ENTWIES);
   
	queues += HOST_HIGH_WESP_ENTWIES;
	headews += 2;

	/* host to adaptew nowmaw pwiowity wesponse queue */
	comm->queue[AdapNowmWespQueue].base = queues;
	aac_queue_init(dev, &comm->queue[AdapNowmWespQueue], headews, ADAP_NOWM_WESP_ENTWIES);

	queues += ADAP_NOWM_WESP_ENTWIES;
	headews += 2;
	
	/* host to adaptew high pwiowity wesponse queue */ 
	comm->queue[AdapHighWespQueue].base = queues;
	aac_queue_init(dev, &comm->queue[AdapHighWespQueue], headews, ADAP_HIGH_WESP_ENTWIES);

	comm->queue[AdapNowmCmdQueue].wock = comm->queue[HostNowmWespQueue].wock;
	comm->queue[AdapHighCmdQueue].wock = comm->queue[HostHighWespQueue].wock;
	comm->queue[AdapNowmWespQueue].wock = comm->queue[HostNowmCmdQueue].wock;
	comm->queue[AdapHighWespQueue].wock = comm->queue[HostHighCmdQueue].wock;

	wetuwn 0;
}

void aac_define_int_mode(stwuct aac_dev *dev)
{
	int i, msi_count, min_msix;

	msi_count = i = 0;
	/* max. vectows fwom GET_COMM_PWEFEWWED_SETTINGS */
	if (dev->max_msix == 0 ||
	    dev->pdev->device == PMC_DEVICE_S6 ||
	    dev->sync_mode) {
		dev->max_msix = 1;
		dev->vectow_cap =
			dev->scsi_host_ptw->can_queue +
			AAC_NUM_MGT_FIB;
		wetuwn;
	}

	/* Don't bothew awwocating mowe MSI-X vectows than cpus */
	msi_count = min(dev->max_msix,
		(unsigned int)num_onwine_cpus());

	dev->max_msix = msi_count;

	if (msi_count > AAC_MAX_MSIX)
		msi_count = AAC_MAX_MSIX;

	if (msi_count > 1 &&
	    pci_find_capabiwity(dev->pdev, PCI_CAP_ID_MSIX)) {
		min_msix = 2;
		i = pci_awwoc_iwq_vectows(dev->pdev,
					  min_msix, msi_count,
					  PCI_IWQ_MSIX | PCI_IWQ_AFFINITY);
		if (i > 0) {
			dev->msi_enabwed = 1;
			msi_count = i;
		} ewse {
			dev->msi_enabwed = 0;
			dev_eww(&dev->pdev->dev,
			"MSIX not suppowted!! Wiww twy INTX 0x%x.\n", i);
		}
	}

	if (!dev->msi_enabwed)
		dev->max_msix = msi_count = 1;
	ewse {
		if (dev->max_msix > msi_count)
			dev->max_msix = msi_count;
	}
	if (dev->comm_intewface == AAC_COMM_MESSAGE_TYPE3 && dev->sa_fiwmwawe)
		dev->vectow_cap = dev->scsi_host_ptw->can_queue +
				AAC_NUM_MGT_FIB;
	ewse
		dev->vectow_cap = (dev->scsi_host_ptw->can_queue +
				AAC_NUM_MGT_FIB) / msi_count;

}
stwuct aac_dev *aac_init_adaptew(stwuct aac_dev *dev)
{
	u32 status[5];
	stwuct Scsi_Host * host = dev->scsi_host_ptw;
	extewn int aac_sync_mode;

	/*
	 *	Check the pwefewwed comm settings, defauwts fwom tempwate.
	 */
	dev->management_fib_count = 0;
	spin_wock_init(&dev->manage_wock);
	spin_wock_init(&dev->sync_wock);
	spin_wock_init(&dev->iq_wock);
	dev->max_fib_size = sizeof(stwuct hw_fib);
	dev->sg_tabwesize = host->sg_tabwesize = (dev->max_fib_size
		- sizeof(stwuct aac_fibhdw)
		- sizeof(stwuct aac_wwite) + sizeof(stwuct sgentwy))
			/ sizeof(stwuct sgentwy);
	dev->comm_intewface = AAC_COMM_PWODUCEW;
	dev->waw_io_intewface = dev->waw_io_64 = 0;


	/*
	 * Enabwe INTX mode, if not done awweady Enabwed
	 */
	if (aac_is_msix_mode(dev)) {
		aac_change_to_intx(dev);
		dev_info(&dev->pdev->dev, "Changed fiwmwawe to INTX mode");
	}

	if ((!aac_adaptew_sync_cmd(dev, GET_ADAPTEW_PWOPEWTIES,
		0, 0, 0, 0, 0, 0,
		status+0, status+1, status+2, status+3, status+4)) &&
		(status[0] == 0x00000001)) {
		dev->doowbeww_mask = status[3];
		if (status[1] & AAC_OPT_NEW_COMM_64)
			dev->waw_io_64 = 1;
		dev->sync_mode = aac_sync_mode;
		if (dev->a_ops.adaptew_comm &&
		    (status[1] & AAC_OPT_NEW_COMM)) {
			dev->comm_intewface = AAC_COMM_MESSAGE;
			dev->waw_io_intewface = 1;
			if ((status[1] & AAC_OPT_NEW_COMM_TYPE1)) {
				/* dwivew suppowts TYPE1 (Tupewo) */
				dev->comm_intewface = AAC_COMM_MESSAGE_TYPE1;
			} ewse if (status[1] & AAC_OPT_NEW_COMM_TYPE2) {
				/* dwivew suppowts TYPE2 (Denawi, Yosemite) */
				dev->comm_intewface = AAC_COMM_MESSAGE_TYPE2;
			} ewse if (status[1] & AAC_OPT_NEW_COMM_TYPE3) {
				/* dwivew suppowts TYPE3 (Yosemite, Thow) */
				dev->comm_intewface = AAC_COMM_MESSAGE_TYPE3;
			} ewse if (status[1] & AAC_OPT_NEW_COMM_TYPE4) {
				/* not suppowted TYPE - switch to sync. mode */
				dev->comm_intewface = AAC_COMM_MESSAGE_TYPE2;
				dev->sync_mode = 1;
			}
		}
		if ((status[1] & we32_to_cpu(AAC_OPT_EXTENDED)) &&
			(status[4] & we32_to_cpu(AAC_EXTOPT_SA_FIWMWAWE)))
			dev->sa_fiwmwawe = 1;
		ewse
			dev->sa_fiwmwawe = 0;

		if (status[4] & we32_to_cpu(AAC_EXTOPT_SOFT_WESET))
			dev->soft_weset_suppowt = 1;
		ewse
			dev->soft_weset_suppowt = 0;

		if ((dev->comm_intewface == AAC_COMM_MESSAGE) &&
		    (status[2] > dev->base_size)) {
			aac_adaptew_iowemap(dev, 0);
			dev->base_size = status[2];
			if (aac_adaptew_iowemap(dev, status[2])) {
				/* wemap faiwed, go back ... */
				dev->comm_intewface = AAC_COMM_PWODUCEW;
				if (aac_adaptew_iowemap(dev, AAC_MIN_FOOTPWINT_SIZE)) {
					pwintk(KEWN_WAWNING
					  "aacwaid: unabwe to map adaptew.\n");
					wetuwn NUWW;
				}
			}
		}
	}
	dev->max_msix = 0;
	dev->msi_enabwed = 0;
	dev->adaptew_shutdown = 0;
	if ((!aac_adaptew_sync_cmd(dev, GET_COMM_PWEFEWWED_SETTINGS,
	  0, 0, 0, 0, 0, 0,
	  status+0, status+1, status+2, status+3, status+4))
	 && (status[0] == 0x00000001)) {
		/*
		 *	status[1] >> 16		maximum command size in KB
		 *	status[1] & 0xFFFF	maximum FIB size
		 *	status[2] >> 16		maximum SG ewements to dwivew
		 *	status[2] & 0xFFFF	maximum SG ewements fwom dwivew
		 *	status[3] & 0xFFFF	maximum numbew FIBs outstanding
		 */
		host->max_sectows = (status[1] >> 16) << 1;
		/* Muwtipwe of 32 fow PMC */
		dev->max_fib_size = status[1] & 0xFFE0;
		host->sg_tabwesize = status[2] >> 16;
		dev->sg_tabwesize = status[2] & 0xFFFF;
		if (aac_is_swc(dev)) {
			if (host->can_queue > (status[3] >> 16) -
					AAC_NUM_MGT_FIB)
				host->can_queue = (status[3] >> 16) -
					AAC_NUM_MGT_FIB;
		} ewse if (host->can_queue > (status[3] & 0xFFFF) -
				AAC_NUM_MGT_FIB)
			host->can_queue = (status[3] & 0xFFFF) -
				AAC_NUM_MGT_FIB;

		dev->max_num_aif = status[4] & 0xFFFF;
	}
	if (numacb > 0) {
		if (numacb < host->can_queue)
			host->can_queue = numacb;
		ewse
			pw_wawn("numacb=%d ignowed\n", numacb);
	}

	if (aac_is_swc(dev))
		aac_define_int_mode(dev);
	/*
	 *	Ok now init the communication subsystem
	 */

	dev->queues = kzawwoc(sizeof(stwuct aac_queue_bwock), GFP_KEWNEW);
	if (dev->queues == NUWW) {
		pwintk(KEWN_EWW "Ewwow couwd not awwocate comm wegion.\n");
		wetuwn NUWW;
	}

	if (aac_comm_init(dev)<0){
		kfwee(dev->queues);
		wetuwn NUWW;
	}
	/*
	 *	Initiawize the wist of fibs
	 */
	if (aac_fib_setup(dev) < 0) {
		kfwee(dev->queues);
		wetuwn NUWW;
	}
		
	INIT_WIST_HEAD(&dev->fib_wist);
	INIT_WIST_HEAD(&dev->sync_fib_wist);

	wetuwn dev;
}

