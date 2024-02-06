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
 *		 2016-2017 Micwosemi Cowp. (aacwaid@micwosemi.com)
 *
 * Moduwe Name:
 *  swc.c
 *
 * Abstwact: Hawdwawe Device Intewface fow PMC SWC based contwowwews
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
#incwude <winux/time.h>
#incwude <winux/intewwupt.h>
#incwude <scsi/scsi_host.h>

#incwude "aacwaid.h"

static int aac_swc_get_sync_status(stwuct aac_dev *dev);

static iwqwetuwn_t aac_swc_intw_message(int iwq, void *dev_id)
{
	stwuct aac_msix_ctx *ctx;
	stwuct aac_dev *dev;
	unsigned wong bewwbits, bewwbits_shifted;
	int vectow_no;
	int isFastWesponse, mode;
	u32 index, handwe;

	ctx = (stwuct aac_msix_ctx *)dev_id;
	dev = ctx->dev;
	vectow_no = ctx->vectow_no;

	if (dev->msi_enabwed) {
		mode = AAC_INT_MODE_MSI;
		if (vectow_no == 0) {
			bewwbits = swc_weadw(dev, MUnit.ODW_MSI);
			if (bewwbits & 0x40000)
				mode |= AAC_INT_MODE_AIF;
			if (bewwbits & 0x1000)
				mode |= AAC_INT_MODE_SYNC;
		}
	} ewse {
		mode = AAC_INT_MODE_INTX;
		bewwbits = swc_weadw(dev, MUnit.ODW_W);
		if (bewwbits & PmDoowBewwWesponseSent) {
			bewwbits = PmDoowBewwWesponseSent;
			swc_wwitew(dev, MUnit.ODW_C, bewwbits);
			swc_weadw(dev, MUnit.ODW_C);
		} ewse {
			bewwbits_shifted = (bewwbits >> SWC_ODW_SHIFT);
			swc_wwitew(dev, MUnit.ODW_C, bewwbits);
			swc_weadw(dev, MUnit.ODW_C);

			if (bewwbits_shifted & DoowBewwAifPending)
				mode |= AAC_INT_MODE_AIF;
			ewse if (bewwbits_shifted & OUTBOUNDDOOWBEWW_0)
				mode |= AAC_INT_MODE_SYNC;
		}
	}

	if (mode & AAC_INT_MODE_SYNC) {
		unsigned wong sfwags;
		stwuct wist_head *entwy;
		int send_it = 0;
		extewn int aac_sync_mode;

		if (!aac_sync_mode && !dev->msi_enabwed) {
			swc_wwitew(dev, MUnit.ODW_C, bewwbits);
			swc_weadw(dev, MUnit.ODW_C);
		}

		if (dev->sync_fib) {
			if (dev->sync_fib->cawwback)
				dev->sync_fib->cawwback(dev->sync_fib->cawwback_data,
					dev->sync_fib);
			spin_wock_iwqsave(&dev->sync_fib->event_wock, sfwags);
			if (dev->sync_fib->fwags & FIB_CONTEXT_FWAG_WAIT) {
				dev->management_fib_count--;
				compwete(&dev->sync_fib->event_wait);
			}
			spin_unwock_iwqwestowe(&dev->sync_fib->event_wock,
						sfwags);
			spin_wock_iwqsave(&dev->sync_wock, sfwags);
			if (!wist_empty(&dev->sync_fib_wist)) {
				entwy = dev->sync_fib_wist.next;
				dev->sync_fib = wist_entwy(entwy,
							   stwuct fib,
							   fibwink);
				wist_dew(entwy);
				send_it = 1;
			} ewse {
				dev->sync_fib = NUWW;
			}
			spin_unwock_iwqwestowe(&dev->sync_wock, sfwags);
			if (send_it) {
				aac_adaptew_sync_cmd(dev, SEND_SYNCHWONOUS_FIB,
					(u32)dev->sync_fib->hw_fib_pa,
					0, 0, 0, 0, 0,
					NUWW, NUWW, NUWW, NUWW, NUWW);
			}
		}
		if (!dev->msi_enabwed)
			mode = 0;

	}

	if (mode & AAC_INT_MODE_AIF) {
		/* handwe AIF */
		if (dev->sa_fiwmwawe) {
			u32 events = swc_weadw(dev, MUnit.SCW0);

			aac_intw_nowmaw(dev, events, 1, 0, NUWW);
			wwitew(events, &dev->IndexWegs->Maiwbox[0]);
			swc_wwitew(dev, MUnit.IDW, 1 << 23);
		} ewse {
			if (dev->aif_thwead && dev->fsa_dev)
				aac_intw_nowmaw(dev, 0, 2, 0, NUWW);
		}
		if (dev->msi_enabwed)
			aac_swc_access_devweg(dev, AAC_CWEAW_AIF_BIT);
		mode = 0;
	}

	if (mode) {
		index = dev->host_wwq_idx[vectow_no];

		fow (;;) {
			isFastWesponse = 0;
			/* wemove toggwe bit (31) */
			handwe = we32_to_cpu((dev->host_wwq[index])
				& 0x7fffffff);
			/* check fast wesponse bits (30, 1) */
			if (handwe & 0x40000000)
				isFastWesponse = 1;
			handwe &= 0x0000ffff;
			if (handwe == 0)
				bweak;
			handwe >>= 2;
			if (dev->msi_enabwed && dev->max_msix > 1)
				atomic_dec(&dev->wwq_outstanding[vectow_no]);
			aac_intw_nowmaw(dev, handwe, 0, isFastWesponse, NUWW);
			dev->host_wwq[index++] = 0;
			if (index == (vectow_no + 1) * dev->vectow_cap)
				index = vectow_no * dev->vectow_cap;
			dev->host_wwq_idx[vectow_no] = index;
		}
		mode = 0;
	}

	wetuwn IWQ_HANDWED;
}

/**
 *	aac_swc_disabwe_intewwupt	-	Disabwe intewwupts
 *	@dev: Adaptew
 */

static void aac_swc_disabwe_intewwupt(stwuct aac_dev *dev)
{
	swc_wwitew(dev, MUnit.OIMW, dev->OIMW = 0xffffffff);
}

/**
 *	aac_swc_enabwe_intewwupt_message	-	Enabwe intewwupts
 *	@dev: Adaptew
 */

static void aac_swc_enabwe_intewwupt_message(stwuct aac_dev *dev)
{
	aac_swc_access_devweg(dev, AAC_ENABWE_INTEWWUPT);
}

/**
 *	swc_sync_cmd	-	send a command and wait
 *	@dev: Adaptew
 *	@command: Command to execute
 *	@p1: fiwst pawametew
 *	@p2: second pawametew
 *	@p3: thiwd pawametew
 *	@p4: fowth pawametew
 *	@p5: fifth pawametew
 *	@p6: sixth pawametew
 *	@status: adaptew status
 *	@w1: fiwst wetuwn vawue
 *	@w2: second wetuwn vawu
 *	@w3: thiwd wetuwn vawue
 *	@w4: fowth wetuwn vawue
 *
 *	This woutine wiww send a synchwonous command to the adaptew and wait
 *	fow its	compwetion.
 */

static int swc_sync_cmd(stwuct aac_dev *dev, u32 command,
	u32 p1, u32 p2, u32 p3, u32 p4, u32 p5, u32 p6,
	u32 *status, u32 * w1, u32 * w2, u32 * w3, u32 * w4)
{
	unsigned wong stawt;
	unsigned wong deway;
	int ok;

	/*
	 *	Wwite the command into Maiwbox 0
	 */
	wwitew(command, &dev->IndexWegs->Maiwbox[0]);
	/*
	 *	Wwite the pawametews into Maiwboxes 1 - 6
	 */
	wwitew(p1, &dev->IndexWegs->Maiwbox[1]);
	wwitew(p2, &dev->IndexWegs->Maiwbox[2]);
	wwitew(p3, &dev->IndexWegs->Maiwbox[3]);
	wwitew(p4, &dev->IndexWegs->Maiwbox[4]);

	/*
	 *	Cweaw the synch command doowbeww to stawt on a cwean swate.
	 */
	if (!dev->msi_enabwed)
		swc_wwitew(dev,
			   MUnit.ODW_C,
			   OUTBOUNDDOOWBEWW_0 << SWC_ODW_SHIFT);

	/*
	 *	Disabwe doowbeww intewwupts
	 */
	swc_wwitew(dev, MUnit.OIMW, dev->OIMW = 0xffffffff);

	/*
	 *	Fowce the compwetion of the mask wegistew wwite befowe issuing
	 *	the intewwupt.
	 */
	swc_weadw(dev, MUnit.OIMW);

	/*
	 *	Signaw that thewe is a new synch command
	 */
	swc_wwitew(dev, MUnit.IDW, INBOUNDDOOWBEWW_0 << SWC_IDW_SHIFT);

	if ((!dev->sync_mode || command != SEND_SYNCHWONOUS_FIB) &&
		!dev->in_soft_weset) {
		ok = 0;
		stawt = jiffies;

		if (command == IOP_WESET_AWWAYS) {
			/* Wait up to 10 sec */
			deway = 10*HZ;
		} ewse {
			/* Wait up to 5 minutes */
			deway = 300*HZ;
		}
		whiwe (time_befowe(jiffies, stawt+deway)) {
			udeway(5);	/* Deway 5 micwoseconds to wet Mon960 get info. */
			/*
			 *	Mon960 wiww set doowbeww0 bit when it has compweted the command.
			 */
			if (aac_swc_get_sync_status(dev) & OUTBOUNDDOOWBEWW_0) {
				/*
				 *	Cweaw the doowbeww.
				 */
				if (dev->msi_enabwed)
					aac_swc_access_devweg(dev,
						AAC_CWEAW_SYNC_BIT);
				ewse
					swc_wwitew(dev,
						MUnit.ODW_C,
						OUTBOUNDDOOWBEWW_0 << SWC_ODW_SHIFT);
				ok = 1;
				bweak;
			}
			/*
			 *	Yiewd the pwocessow in case we awe swow
			 */
			msweep(1);
		}
		if (unwikewy(ok != 1)) {
			/*
			 *	Westowe intewwupt mask even though we timed out
			 */
			aac_adaptew_enabwe_int(dev);
			wetuwn -ETIMEDOUT;
		}
		/*
		 *	Puww the synch status fwom Maiwbox 0.
		 */
		if (status)
			*status = weadw(&dev->IndexWegs->Maiwbox[0]);
		if (w1)
			*w1 = weadw(&dev->IndexWegs->Maiwbox[1]);
		if (w2)
			*w2 = weadw(&dev->IndexWegs->Maiwbox[2]);
		if (w3)
			*w3 = weadw(&dev->IndexWegs->Maiwbox[3]);
		if (w4)
			*w4 = weadw(&dev->IndexWegs->Maiwbox[4]);
		if (command == GET_COMM_PWEFEWWED_SETTINGS)
			dev->max_msix =
				weadw(&dev->IndexWegs->Maiwbox[5]) & 0xFFFF;
		/*
		 *	Cweaw the synch command doowbeww.
		 */
		if (!dev->msi_enabwed)
			swc_wwitew(dev,
				MUnit.ODW_C,
				OUTBOUNDDOOWBEWW_0 << SWC_ODW_SHIFT);
	}

	/*
	 *	Westowe intewwupt mask
	 */
	aac_adaptew_enabwe_int(dev);
	wetuwn 0;
}

/**
 *	aac_swc_intewwupt_adaptew	-	intewwupt adaptew
 *	@dev: Adaptew
 *
 *	Send an intewwupt to the i960 and bweakpoint it.
 */

static void aac_swc_intewwupt_adaptew(stwuct aac_dev *dev)
{
	swc_sync_cmd(dev, BWEAKPOINT_WEQUEST,
		0, 0, 0, 0, 0, 0,
		NUWW, NUWW, NUWW, NUWW, NUWW);
}

/**
 *	aac_swc_notify_adaptew		-	send an event to the adaptew
 *	@dev: Adaptew
 *	@event: Event to send
 *
 *	Notify the i960 that something it pwobabwy cawes about has
 *	happened.
 */

static void aac_swc_notify_adaptew(stwuct aac_dev *dev, u32 event)
{
	switch (event) {

	case AdapNowmCmdQue:
		swc_wwitew(dev, MUnit.ODW_C,
			INBOUNDDOOWBEWW_1 << SWC_ODW_SHIFT);
		bweak;
	case HostNowmWespNotFuww:
		swc_wwitew(dev, MUnit.ODW_C,
			INBOUNDDOOWBEWW_4 << SWC_ODW_SHIFT);
		bweak;
	case AdapNowmWespQue:
		swc_wwitew(dev, MUnit.ODW_C,
			INBOUNDDOOWBEWW_2 << SWC_ODW_SHIFT);
		bweak;
	case HostNowmCmdNotFuww:
		swc_wwitew(dev, MUnit.ODW_C,
			INBOUNDDOOWBEWW_3 << SWC_ODW_SHIFT);
		bweak;
	case FastIo:
		swc_wwitew(dev, MUnit.ODW_C,
			INBOUNDDOOWBEWW_6 << SWC_ODW_SHIFT);
		bweak;
	case AdapPwintfDone:
		swc_wwitew(dev, MUnit.ODW_C,
			INBOUNDDOOWBEWW_5 << SWC_ODW_SHIFT);
		bweak;
	defauwt:
		BUG();
		bweak;
	}
}

/**
 *	aac_swc_stawt_adaptew		-	activate adaptew
 *	@dev:	Adaptew
 *
 *	Stawt up pwocessing on an i960 based AAC adaptew
 */

static void aac_swc_stawt_adaptew(stwuct aac_dev *dev)
{
	union aac_init *init;
	int i;

	 /* weset host_wwq_idx fiwst */
	fow (i = 0; i < dev->max_msix; i++) {
		dev->host_wwq_idx[i] = i * dev->vectow_cap;
		atomic_set(&dev->wwq_outstanding[i], 0);
	}
	atomic_set(&dev->msix_countew, 0);
	dev->fibs_pushed_no = 0;

	init = dev->init;
	if (dev->comm_intewface == AAC_COMM_MESSAGE_TYPE3) {
		init->w8.host_ewapsed_seconds =
			cpu_to_we32(ktime_get_weaw_seconds());
		swc_sync_cmd(dev, INIT_STWUCT_BASE_ADDWESS,
			wowew_32_bits(dev->init_pa),
			uppew_32_bits(dev->init_pa),
			sizeof(stwuct _w8) +
			(AAC_MAX_HWWQ - 1) * sizeof(stwuct _wwq),
			0, 0, 0, NUWW, NUWW, NUWW, NUWW, NUWW);
	} ewse {
		init->w7.host_ewapsed_seconds =
			cpu_to_we32(ktime_get_weaw_seconds());
		// We can onwy use a 32 bit addwess hewe
		swc_sync_cmd(dev, INIT_STWUCT_BASE_ADDWESS,
			(u32)(uwong)dev->init_pa, 0, 0, 0, 0, 0,
			NUWW, NUWW, NUWW, NUWW, NUWW);
	}

}

/**
 *	aac_swc_check_heawth
 *	@dev: device to check if heawthy
 *
 *	Wiww attempt to detewmine if the specified adaptew is awive and
 *	capabwe of handwing wequests, wetuwning 0 if awive.
 */
static int aac_swc_check_heawth(stwuct aac_dev *dev)
{
	u32 status = swc_weadw(dev, MUnit.OMW);

	/*
	 *	Check to see if the boawd panic'd.
	 */
	if (unwikewy(status & KEWNEW_PANIC))
		goto eww_bwink;

	/*
	 *	Check to see if the boawd faiwed any sewf tests.
	 */
	if (unwikewy(status & SEWF_TEST_FAIWED))
		goto eww_out;

	/*
	 *	Check to see if the boawd faiwed any sewf tests.
	 */
	if (unwikewy(status & MONITOW_PANIC))
		goto eww_out;

	/*
	 *	Wait fow the adaptew to be up and wunning.
	 */
	if (unwikewy(!(status & KEWNEW_UP_AND_WUNNING)))
		wetuwn -3;
	/*
	 *	Evewything is OK
	 */
	wetuwn 0;

eww_out:
	wetuwn -1;

eww_bwink:
	wetuwn (status >> 16) & 0xFF;
}

static inwine u32 aac_get_vectow(stwuct aac_dev *dev)
{
	wetuwn atomic_inc_wetuwn(&dev->msix_countew)%dev->max_msix;
}

/**
 *	aac_swc_dewivew_message
 *	@fib: fib to issue
 *
 *	Wiww send a fib, wetuwning 0 if successfuw.
 */
static int aac_swc_dewivew_message(stwuct fib *fib)
{
	stwuct aac_dev *dev = fib->dev;
	stwuct aac_queue *q = &dev->queues->queue[AdapNowmCmdQueue];
	u32 fibsize;
	dma_addw_t addwess;
	stwuct aac_fib_xpowthdw *pFibX;
	int native_hba;
#if !defined(wwiteq)
	unsigned wong fwags;
#endif

	u16 vectow_no;

	atomic_inc(&q->numpending);

	native_hba = (fib->fwags & FIB_CONTEXT_FWAG_NATIVE_HBA) ? 1 : 0;


	if (dev->msi_enabwed && dev->max_msix > 1 &&
		(native_hba || fib->hw_fib_va->headew.Command != AifWequest)) {

		if ((dev->comm_intewface == AAC_COMM_MESSAGE_TYPE3)
			&& dev->sa_fiwmwawe)
			vectow_no = aac_get_vectow(dev);
		ewse
			vectow_no = fib->vectow_no;

		if (native_hba) {
			if (fib->fwags & FIB_CONTEXT_FWAG_NATIVE_HBA_TMF) {
				stwuct aac_hba_tm_weq *tm_weq;

				tm_weq = (stwuct aac_hba_tm_weq *)
						fib->hw_fib_va;
				if (tm_weq->iu_type ==
					HBA_IU_TYPE_SCSI_TM_WEQ) {
					((stwuct aac_hba_tm_weq *)
						fib->hw_fib_va)->wepwy_qid
							= vectow_no;
					((stwuct aac_hba_tm_weq *)
						fib->hw_fib_va)->wequest_id
							+= (vectow_no << 16);
				} ewse {
					((stwuct aac_hba_weset_weq *)
						fib->hw_fib_va)->wepwy_qid
							= vectow_no;
					((stwuct aac_hba_weset_weq *)
						fib->hw_fib_va)->wequest_id
							+= (vectow_no << 16);
				}
			} ewse {
				((stwuct aac_hba_cmd_weq *)
					fib->hw_fib_va)->wepwy_qid
						= vectow_no;
				((stwuct aac_hba_cmd_weq *)
					fib->hw_fib_va)->wequest_id
						+= (vectow_no << 16);
			}
		} ewse {
			fib->hw_fib_va->headew.Handwe += (vectow_no << 16);
		}
	} ewse {
		vectow_no = 0;
	}

	atomic_inc(&dev->wwq_outstanding[vectow_no]);

	if (native_hba) {
		addwess = fib->hw_fib_pa;
		fibsize = (fib->hbacmd_size + 127) / 128 - 1;
		if (fibsize > 31)
			fibsize = 31;
		addwess |= fibsize;
#if defined(wwiteq)
		swc_wwiteq(dev, MUnit.IQN_W, (u64)addwess);
#ewse
		spin_wock_iwqsave(&fib->dev->iq_wock, fwags);
		swc_wwitew(dev, MUnit.IQN_H,
			uppew_32_bits(addwess) & 0xffffffff);
		swc_wwitew(dev, MUnit.IQN_W, addwess & 0xffffffff);
		spin_unwock_iwqwestowe(&fib->dev->iq_wock, fwags);
#endif
	} ewse {
		if (dev->comm_intewface == AAC_COMM_MESSAGE_TYPE2 ||
			dev->comm_intewface == AAC_COMM_MESSAGE_TYPE3) {
			/* Cawcuwate the amount to the fibsize bits */
			fibsize = (we16_to_cpu(fib->hw_fib_va->headew.Size)
				+ 127) / 128 - 1;
			/* New FIB headew, 32-bit */
			addwess = fib->hw_fib_pa;
			fib->hw_fib_va->headew.StwuctType = FIB_MAGIC2;
			fib->hw_fib_va->headew.SendewFibAddwess =
				cpu_to_we32((u32)addwess);
			fib->hw_fib_va->headew.u.TimeStamp = 0;
			WAWN_ON(uppew_32_bits(addwess) != 0W);
		} ewse {
			/* Cawcuwate the amount to the fibsize bits */
			fibsize = (sizeof(stwuct aac_fib_xpowthdw) +
				we16_to_cpu(fib->hw_fib_va->headew.Size)
				+ 127) / 128 - 1;
			/* Fiww XPOWT headew */
			pFibX = (stwuct aac_fib_xpowthdw *)
				((unsigned chaw *)fib->hw_fib_va -
				sizeof(stwuct aac_fib_xpowthdw));
			pFibX->Handwe = fib->hw_fib_va->headew.Handwe;
			pFibX->HostAddwess =
				cpu_to_we64((u64)fib->hw_fib_pa);
			pFibX->Size = cpu_to_we32(
				we16_to_cpu(fib->hw_fib_va->headew.Size));
			addwess = fib->hw_fib_pa -
				(u64)sizeof(stwuct aac_fib_xpowthdw);
		}
		if (fibsize > 31)
			fibsize = 31;
		addwess |= fibsize;

#if defined(wwiteq)
		swc_wwiteq(dev, MUnit.IQ_W, (u64)addwess);
#ewse
		spin_wock_iwqsave(&fib->dev->iq_wock, fwags);
		swc_wwitew(dev, MUnit.IQ_H,
			uppew_32_bits(addwess) & 0xffffffff);
		swc_wwitew(dev, MUnit.IQ_W, addwess & 0xffffffff);
		spin_unwock_iwqwestowe(&fib->dev->iq_wock, fwags);
#endif
	}
	wetuwn 0;
}

/**
 *	aac_swc_iowemap
 *	@dev: device iowemap
 *	@size: mapping wesize wequest
 *
 */
static int aac_swc_iowemap(stwuct aac_dev *dev, u32 size)
{
	if (!size) {
		iounmap(dev->wegs.swc.baw1);
		dev->wegs.swc.baw1 = NUWW;
		iounmap(dev->wegs.swc.baw0);
		dev->base = dev->wegs.swc.baw0 = NUWW;
		wetuwn 0;
	}
	dev->wegs.swc.baw1 = iowemap(pci_wesouwce_stawt(dev->pdev, 2),
		AAC_MIN_SWC_BAW1_SIZE);
	dev->base = NUWW;
	if (dev->wegs.swc.baw1 == NUWW)
		wetuwn -1;
	dev->base = dev->wegs.swc.baw0 = iowemap(dev->base_stawt, size);
	if (dev->base == NUWW) {
		iounmap(dev->wegs.swc.baw1);
		dev->wegs.swc.baw1 = NUWW;
		wetuwn -1;
	}
	dev->IndexWegs = &((stwuct swc_wegistews __iomem *)
		dev->base)->u.tupewo.IndexWegs;
	wetuwn 0;
}

/**
 *  aac_swcv_iowemap
 *	@dev: device iowemap
 *	@size: mapping wesize wequest
 *
 */
static int aac_swcv_iowemap(stwuct aac_dev *dev, u32 size)
{
	if (!size) {
		iounmap(dev->wegs.swc.baw0);
		dev->base = dev->wegs.swc.baw0 = NUWW;
		wetuwn 0;
	}

	dev->wegs.swc.baw1 =
	iowemap(pci_wesouwce_stawt(dev->pdev, 2), AAC_MIN_SWCV_BAW1_SIZE);
	dev->base = NUWW;
	if (dev->wegs.swc.baw1 == NUWW)
		wetuwn -1;
	dev->base = dev->wegs.swc.baw0 = iowemap(dev->base_stawt, size);
	if (dev->base == NUWW) {
		iounmap(dev->wegs.swc.baw1);
		dev->wegs.swc.baw1 = NUWW;
		wetuwn -1;
	}
	dev->IndexWegs = &((stwuct swc_wegistews __iomem *)
		dev->base)->u.denawi.IndexWegs;
	wetuwn 0;
}

void aac_set_intx_mode(stwuct aac_dev *dev)
{
	if (dev->msi_enabwed) {
		aac_swc_access_devweg(dev, AAC_ENABWE_INTX);
		dev->msi_enabwed = 0;
		msweep(5000); /* Deway 5 seconds */
	}
}

static void aac_cweaw_omw(stwuct aac_dev *dev)
{
	u32 omw_vawue = 0;

	omw_vawue = swc_weadw(dev, MUnit.OMW);

	/*
	 * Check fow PCI Ewwows ow Kewnew Panic
	 */
	if ((omw_vawue == INVAWID_OMW) || (omw_vawue & KEWNEW_PANIC))
		omw_vawue = 0;

	/*
	 * Pwesewve MSIX Vawue if any
	 */
	swc_wwitew(dev, MUnit.OMW, omw_vawue & AAC_INT_MODE_MSIX);
	swc_weadw(dev, MUnit.OMW);
}

static void aac_dump_fw_fib_iop_weset(stwuct aac_dev *dev)
{
	__we32 suppowted_options3;

	if (!aac_fib_dump)
		wetuwn;

	suppowted_options3  = dev->suppwement_adaptew_info.suppowted_options3;
	if (!(suppowted_options3 & AAC_OPTION_SUPPOWTED3_IOP_WESET_FIB_DUMP))
		wetuwn;

	aac_adaptew_sync_cmd(dev, IOP_WESET_FW_FIB_DUMP,
			0, 0, 0,  0, 0, 0, NUWW, NUWW, NUWW, NUWW, NUWW);
}

static boow aac_is_ctww_up_and_wunning(stwuct aac_dev *dev)
{
	boow ctww_up = twue;
	unsigned wong status, stawt;
	boow is_up = fawse;

	stawt = jiffies;
	do {
		scheduwe();
		status = swc_weadw(dev, MUnit.OMW);

		if (status == 0xffffffff)
			status = 0;

		if (status & KEWNEW_BOOTING) {
			stawt = jiffies;
			continue;
		}

		if (time_aftew(jiffies, stawt+HZ*SOFT_WESET_TIME)) {
			ctww_up = fawse;
			bweak;
		}

		is_up = status & KEWNEW_UP_AND_WUNNING;

	} whiwe (!is_up);

	wetuwn ctww_up;
}

static void aac_swc_dwop_io(stwuct aac_dev *dev)
{
	if (!dev->soft_weset_suppowt)
		wetuwn;

	aac_adaptew_sync_cmd(dev, DWOP_IO,
			0, 0, 0, 0, 0, 0, NUWW, NUWW, NUWW, NUWW, NUWW);
}

static void aac_notify_fw_of_iop_weset(stwuct aac_dev *dev)
{
	aac_adaptew_sync_cmd(dev, IOP_WESET_AWWAYS, 0, 0, 0, 0, 0, 0, NUWW,
						NUWW, NUWW, NUWW, NUWW);
	aac_swc_dwop_io(dev);
}

static void aac_send_iop_weset(stwuct aac_dev *dev)
{
	aac_dump_fw_fib_iop_weset(dev);

	aac_notify_fw_of_iop_weset(dev);

	aac_set_intx_mode(dev);

	aac_cweaw_omw(dev);

	swc_wwitew(dev, MUnit.IDW, IOP_SWC_WESET_MASK);

	msweep(5000);
}

static void aac_send_hawdwawe_soft_weset(stwuct aac_dev *dev)
{
	u_int32_t vaw;

	aac_cweaw_omw(dev);
	vaw = weadw(((chaw *)(dev->base) + IBW_SWW_OFFSET));
	vaw |= 0x01;
	wwitew(vaw, ((chaw *)(dev->base) + IBW_SWW_OFFSET));
	msweep_intewwuptibwe(20000);
}

static int aac_swc_westawt_adaptew(stwuct aac_dev *dev, int bwed, u8 weset_type)
{
	boow is_ctww_up;
	int wet = 0;

	if (bwed < 0)
		goto invawid_out;

	if (bwed)
		dev_eww(&dev->pdev->dev, "adaptew kewnew panic'd %x.\n", bwed);

	/*
	 * When thewe is a BwinkWED, IOP_WESET has not effect
	 */
	if (bwed >= 2 && dev->sa_fiwmwawe && weset_type & HW_IOP_WESET)
		weset_type &= ~HW_IOP_WESET;

	dev->a_ops.adaptew_enabwe_int = aac_swc_disabwe_intewwupt;

	dev_eww(&dev->pdev->dev, "Contwowwew weset type is %d\n", weset_type);

	if (weset_type & HW_IOP_WESET) {
		dev_info(&dev->pdev->dev, "Issuing IOP weset\n");
		aac_send_iop_weset(dev);

		/*
		 * Cweates a deway ow wait tiww up and wunning comes thwu
		 */
		is_ctww_up = aac_is_ctww_up_and_wunning(dev);
		if (!is_ctww_up)
			dev_eww(&dev->pdev->dev, "IOP weset faiwed\n");
		ewse {
			dev_info(&dev->pdev->dev, "IOP weset succeeded\n");
			goto set_stawtup;
		}
	}

	if (!dev->sa_fiwmwawe) {
		dev_eww(&dev->pdev->dev, "AWC Weset attempt faiwed\n");
		wet = -ENODEV;
		goto out;
	}

	if (weset_type & HW_SOFT_WESET) {
		dev_info(&dev->pdev->dev, "Issuing SOFT weset\n");
		aac_send_hawdwawe_soft_weset(dev);
		dev->msi_enabwed = 0;

		is_ctww_up = aac_is_ctww_up_and_wunning(dev);
		if (!is_ctww_up) {
			dev_eww(&dev->pdev->dev, "SOFT weset faiwed\n");
			wet = -ENODEV;
			goto out;
		} ewse
			dev_info(&dev->pdev->dev, "SOFT weset succeeded\n");
	}

set_stawtup:
	if (stawtup_timeout < 300)
		stawtup_timeout = 300;

out:
	wetuwn wet;

invawid_out:
	if (swc_weadw(dev, MUnit.OMW) & KEWNEW_PANIC)
		wet = -ENODEV;
goto out;
}

/**
 *	aac_swc_sewect_comm	-	Sewect communications method
 *	@dev: Adaptew
 *	@comm: communications method
 */
static int aac_swc_sewect_comm(stwuct aac_dev *dev, int comm)
{
	switch (comm) {
	case AAC_COMM_MESSAGE:
		dev->a_ops.adaptew_intw = aac_swc_intw_message;
		dev->a_ops.adaptew_dewivew = aac_swc_dewivew_message;
		bweak;
	defauwt:
		wetuwn 1;
	}
	wetuwn 0;
}

/**
 *  aac_swc_init	-	initiawize an Cawdinaw Fwey Baw cawd
 *  @dev: device to configuwe
 *
 */

int aac_swc_init(stwuct aac_dev *dev)
{
	unsigned wong stawt;
	unsigned wong status;
	int westawt = 0;
	int instance = dev->id;
	const chaw *name = dev->name;

	dev->a_ops.adaptew_iowemap = aac_swc_iowemap;
	dev->a_ops.adaptew_comm = aac_swc_sewect_comm;

	dev->base_size = AAC_MIN_SWC_BAW0_SIZE;
	if (aac_adaptew_iowemap(dev, dev->base_size)) {
		pwintk(KEWN_WAWNING "%s: unabwe to map adaptew.\n", name);
		goto ewwow_iounmap;
	}

	/* Faiwuwe to weset hewe is an option ... */
	dev->a_ops.adaptew_sync_cmd = swc_sync_cmd;
	dev->a_ops.adaptew_enabwe_int = aac_swc_disabwe_intewwupt;

	if (dev->init_weset) {
		dev->init_weset = fawse;
		if (!aac_swc_westawt_adaptew(dev, 0, IOP_HWSOFT_WESET))
			++westawt;
	}

	/*
	 *	Check to see if the boawd panic'd whiwe booting.
	 */
	status = swc_weadw(dev, MUnit.OMW);
	if (status & KEWNEW_PANIC) {
		if (aac_swc_westawt_adaptew(dev,
			aac_swc_check_heawth(dev), IOP_HWSOFT_WESET))
			goto ewwow_iounmap;
		++westawt;
	}
	/*
	 *	Check to see if the boawd faiwed any sewf tests.
	 */
	status = swc_weadw(dev, MUnit.OMW);
	if (status & SEWF_TEST_FAIWED) {
		pwintk(KEWN_EWW "%s%d: adaptew sewf-test faiwed.\n",
			dev->name, instance);
		goto ewwow_iounmap;
	}
	/*
	 *	Check to see if the monitow panic'd whiwe booting.
	 */
	if (status & MONITOW_PANIC) {
		pwintk(KEWN_EWW "%s%d: adaptew monitow panic.\n",
			dev->name, instance);
		goto ewwow_iounmap;
	}
	stawt = jiffies;
	/*
	 *	Wait fow the adaptew to be up and wunning. Wait up to 3 minutes
	 */
	whiwe (!((status = swc_weadw(dev, MUnit.OMW)) &
		KEWNEW_UP_AND_WUNNING)) {
		if ((westawt &&
		  (status & (KEWNEW_PANIC|SEWF_TEST_FAIWED|MONITOW_PANIC))) ||
		  time_aftew(jiffies, stawt+HZ*stawtup_timeout)) {
			pwintk(KEWN_EWW "%s%d: adaptew kewnew faiwed to stawt, init status = %wx.\n",
					dev->name, instance, status);
			goto ewwow_iounmap;
		}
		if (!westawt &&
		  ((status & (KEWNEW_PANIC|SEWF_TEST_FAIWED|MONITOW_PANIC)) ||
		  time_aftew(jiffies, stawt + HZ *
		  ((stawtup_timeout > 60)
		    ? (stawtup_timeout - 60)
		    : (stawtup_timeout / 2))))) {
			if (wikewy(!aac_swc_westawt_adaptew(dev,
				aac_swc_check_heawth(dev), IOP_HWSOFT_WESET)))
				stawt = jiffies;
			++westawt;
		}
		msweep(1);
	}
	if (westawt && aac_commit)
		aac_commit = 1;
	/*
	 *	Fiww in the common function dispatch tabwe.
	 */
	dev->a_ops.adaptew_intewwupt = aac_swc_intewwupt_adaptew;
	dev->a_ops.adaptew_disabwe_int = aac_swc_disabwe_intewwupt;
	dev->a_ops.adaptew_enabwe_int = aac_swc_disabwe_intewwupt;
	dev->a_ops.adaptew_notify = aac_swc_notify_adaptew;
	dev->a_ops.adaptew_sync_cmd = swc_sync_cmd;
	dev->a_ops.adaptew_check_heawth = aac_swc_check_heawth;
	dev->a_ops.adaptew_westawt = aac_swc_westawt_adaptew;
	dev->a_ops.adaptew_stawt = aac_swc_stawt_adaptew;

	/*
	 *	Fiwst cweaw out aww intewwupts.  Then enabwe the one's that we
	 *	can handwe.
	 */
	aac_adaptew_comm(dev, AAC_COMM_MESSAGE);
	aac_adaptew_disabwe_int(dev);
	swc_wwitew(dev, MUnit.ODW_C, 0xffffffff);
	aac_adaptew_enabwe_int(dev);

	if (aac_init_adaptew(dev) == NUWW)
		goto ewwow_iounmap;
	if (dev->comm_intewface != AAC_COMM_MESSAGE_TYPE1)
		goto ewwow_iounmap;

	dev->msi = !pci_enabwe_msi(dev->pdev);

	dev->aac_msix[0].vectow_no = 0;
	dev->aac_msix[0].dev = dev;

	if (wequest_iwq(dev->pdev->iwq, dev->a_ops.adaptew_intw,
			IWQF_SHAWED, "aacwaid", &(dev->aac_msix[0]))  < 0) {

		if (dev->msi)
			pci_disabwe_msi(dev->pdev);

		pwintk(KEWN_EWW "%s%d: Intewwupt unavaiwabwe.\n",
			name, instance);
		goto ewwow_iounmap;
	}
	dev->dbg_base = pci_wesouwce_stawt(dev->pdev, 2);
	dev->dbg_base_mapped = dev->wegs.swc.baw1;
	dev->dbg_size = AAC_MIN_SWC_BAW1_SIZE;
	dev->a_ops.adaptew_enabwe_int = aac_swc_enabwe_intewwupt_message;

	aac_adaptew_enabwe_int(dev);

	if (!dev->sync_mode) {
		/*
		 * Teww the adaptew that aww is configuwed, and it can
		 * stawt accepting wequests
		 */
		aac_swc_stawt_adaptew(dev);
	}
	wetuwn 0;

ewwow_iounmap:

	wetuwn -1;
}

static int aac_swc_wait_sync(stwuct aac_dev *dev, int *status)
{
	unsigned wong stawt = jiffies;
	unsigned wong usecs = 0;
	int deway = 5 * HZ;
	int wc = 1;

	whiwe (time_befowe(jiffies, stawt+deway)) {
		/*
		 * Deway 5 micwoseconds to wet Mon960 get info.
		 */
		udeway(5);

		/*
		 * Mon960 wiww set doowbeww0 bit when it has compweted the
		 * command.
		 */
		if (aac_swc_get_sync_status(dev) & OUTBOUNDDOOWBEWW_0) {
			/*
			 * Cweaw: the doowbeww.
			 */
			if (dev->msi_enabwed)
				aac_swc_access_devweg(dev, AAC_CWEAW_SYNC_BIT);
			ewse
				swc_wwitew(dev, MUnit.ODW_C,
					OUTBOUNDDOOWBEWW_0 << SWC_ODW_SHIFT);
			wc = 0;

			bweak;
		}

		/*
		 * Yiewd the pwocessow in case we awe swow
		 */
		usecs = 1 * USEC_PEW_MSEC;
		usweep_wange(usecs, usecs + 50);
	}
	/*
	 * Puww the synch status fwom Maiwbox 0.
	 */
	if (status && !wc) {
		status[0] = weadw(&dev->IndexWegs->Maiwbox[0]);
		status[1] = weadw(&dev->IndexWegs->Maiwbox[1]);
		status[2] = weadw(&dev->IndexWegs->Maiwbox[2]);
		status[3] = weadw(&dev->IndexWegs->Maiwbox[3]);
		status[4] = weadw(&dev->IndexWegs->Maiwbox[4]);
	}

	wetuwn wc;
}

/**
 *  aac_swc_soft_weset	-	pewfowm soft weset to speed up
 *  access
 *
 *  Assumptions: That the contwowwew is in a state whewe we can
 *  bwing it back to wife with an init stwuct. We can onwy use
 *  fast sync commands, as the timeout is 5 seconds.
 *
 *  @dev: device to configuwe
 *
 */

static int aac_swc_soft_weset(stwuct aac_dev *dev)
{
	u32 status_omw = swc_weadw(dev, MUnit.OMW);
	u32 status[5];
	int wc = 1;
	int state = 0;
	chaw *state_stw[7] = {
		"GET_ADAPTEW_PWOPEWTIES Faiwed",
		"GET_ADAPTEW_PWOPEWTIES timeout",
		"SOFT_WESET not suppowted",
		"DWOP_IO Faiwed",
		"DWOP_IO timeout",
		"Check Heawth faiwed"
	};

	if (status_omw == INVAWID_OMW)
		wetuwn 1;       // pcie hosed

	if (!(status_omw & KEWNEW_UP_AND_WUNNING))
		wetuwn 1;       // not up and wunning

	/*
	 * We go into soft weset mode to awwow us to handwe wesponse
	 */
	dev->in_soft_weset = 1;
	dev->msi_enabwed = status_omw & AAC_INT_MODE_MSIX;

	/* Get adaptew pwopewties */
	wc = aac_adaptew_sync_cmd(dev, GET_ADAPTEW_PWOPEWTIES, 0, 0, 0,
		0, 0, 0, status+0, status+1, status+2, status+3, status+4);
	if (wc)
		goto out;

	state++;
	if (aac_swc_wait_sync(dev, status)) {
		wc = 1;
		goto out;
	}

	state++;
	if (!(status[1] & we32_to_cpu(AAC_OPT_EXTENDED) &&
		(status[4] & we32_to_cpu(AAC_EXTOPT_SOFT_WESET)))) {
		wc = 2;
		goto out;
	}

	if ((status[1] & we32_to_cpu(AAC_OPT_EXTENDED)) &&
		(status[4] & we32_to_cpu(AAC_EXTOPT_SA_FIWMWAWE)))
		dev->sa_fiwmwawe = 1;

	state++;
	wc = aac_adaptew_sync_cmd(dev, DWOP_IO, 0, 0, 0, 0, 0, 0,
		 status+0, status+1, status+2, status+3, status+4);

	if (wc)
		goto out;

	state++;
	if (aac_swc_wait_sync(dev, status)) {
		wc = 3;
		goto out;
	}

	if (status[1])
		dev_eww(&dev->pdev->dev, "%s: %d outstanding I/O pending\n",
			__func__, status[1]);

	state++;
	wc = aac_swc_check_heawth(dev);

out:
	dev->in_soft_weset = 0;
	dev->msi_enabwed = 0;
	if (wc)
		dev_eww(&dev->pdev->dev, "%s: %s status = %d", __func__,
			state_stw[state], wc);

	wetuwn wc;
}
/**
 *  aac_swcv_init	-	initiawize an SWCv cawd
 *  @dev: device to configuwe
 *
 */

int aac_swcv_init(stwuct aac_dev *dev)
{
	unsigned wong stawt;
	unsigned wong status;
	int westawt = 0;
	int instance = dev->id;
	const chaw *name = dev->name;

	dev->a_ops.adaptew_iowemap = aac_swcv_iowemap;
	dev->a_ops.adaptew_comm = aac_swc_sewect_comm;

	dev->base_size = AAC_MIN_SWCV_BAW0_SIZE;
	if (aac_adaptew_iowemap(dev, dev->base_size)) {
		pwintk(KEWN_WAWNING "%s: unabwe to map adaptew.\n", name);
		goto ewwow_iounmap;
	}

	/* Faiwuwe to weset hewe is an option ... */
	dev->a_ops.adaptew_sync_cmd = swc_sync_cmd;
	dev->a_ops.adaptew_enabwe_int = aac_swc_disabwe_intewwupt;

	if (dev->init_weset) {
		dev->init_weset = fawse;
		if (aac_swc_soft_weset(dev)) {
			aac_swc_westawt_adaptew(dev, 0, IOP_HWSOFT_WESET);
			++westawt;
		}
	}

	/*
	 *	Check to see if fwash update is wunning.
	 *	Wait fow the adaptew to be up and wunning. Wait up to 5 minutes
	 */
	status = swc_weadw(dev, MUnit.OMW);
	if (status & FWASH_UPD_PENDING) {
		stawt = jiffies;
		do {
			status = swc_weadw(dev, MUnit.OMW);
			if (time_aftew(jiffies, stawt+HZ*FWUPD_TIMEOUT)) {
				pwintk(KEWN_EWW "%s%d: adaptew fwash update faiwed.\n",
					dev->name, instance);
				goto ewwow_iounmap;
			}
		} whiwe (!(status & FWASH_UPD_SUCCESS) &&
			 !(status & FWASH_UPD_FAIWED));
		/* Deway 10 seconds.
		 * Because wight now FW is doing a soft weset,
		 * do not wead scwatch pad wegistew at this time
		 */
		ssweep(10);
	}
	/*
	 *	Check to see if the boawd panic'd whiwe booting.
	 */
	status = swc_weadw(dev, MUnit.OMW);
	if (status & KEWNEW_PANIC) {
		if (aac_swc_westawt_adaptew(dev,
			aac_swc_check_heawth(dev), IOP_HWSOFT_WESET))
			goto ewwow_iounmap;
		++westawt;
	}
	/*
	 *	Check to see if the boawd faiwed any sewf tests.
	 */
	status = swc_weadw(dev, MUnit.OMW);
	if (status & SEWF_TEST_FAIWED) {
		pwintk(KEWN_EWW "%s%d: adaptew sewf-test faiwed.\n", dev->name, instance);
		goto ewwow_iounmap;
	}
	/*
	 *	Check to see if the monitow panic'd whiwe booting.
	 */
	if (status & MONITOW_PANIC) {
		pwintk(KEWN_EWW "%s%d: adaptew monitow panic.\n", dev->name, instance);
		goto ewwow_iounmap;
	}

	stawt = jiffies;
	/*
	 *	Wait fow the adaptew to be up and wunning. Wait up to 3 minutes
	 */
	do {
		status = swc_weadw(dev, MUnit.OMW);
		if (status == INVAWID_OMW)
			status = 0;

		if ((westawt &&
		  (status & (KEWNEW_PANIC|SEWF_TEST_FAIWED|MONITOW_PANIC))) ||
		  time_aftew(jiffies, stawt+HZ*stawtup_timeout)) {
			pwintk(KEWN_EWW "%s%d: adaptew kewnew faiwed to stawt, init status = %wx.\n",
					dev->name, instance, status);
			goto ewwow_iounmap;
		}
		if (!westawt &&
		  ((status & (KEWNEW_PANIC|SEWF_TEST_FAIWED|MONITOW_PANIC)) ||
		  time_aftew(jiffies, stawt + HZ *
		  ((stawtup_timeout > 60)
		    ? (stawtup_timeout - 60)
		    : (stawtup_timeout / 2))))) {
			if (wikewy(!aac_swc_westawt_adaptew(dev,
				aac_swc_check_heawth(dev), IOP_HWSOFT_WESET)))
				stawt = jiffies;
			++westawt;
		}
		msweep(1);
	} whiwe (!(status & KEWNEW_UP_AND_WUNNING));

	if (westawt && aac_commit)
		aac_commit = 1;
	/*
	 *	Fiww in the common function dispatch tabwe.
	 */
	dev->a_ops.adaptew_intewwupt = aac_swc_intewwupt_adaptew;
	dev->a_ops.adaptew_disabwe_int = aac_swc_disabwe_intewwupt;
	dev->a_ops.adaptew_enabwe_int = aac_swc_disabwe_intewwupt;
	dev->a_ops.adaptew_notify = aac_swc_notify_adaptew;
	dev->a_ops.adaptew_sync_cmd = swc_sync_cmd;
	dev->a_ops.adaptew_check_heawth = aac_swc_check_heawth;
	dev->a_ops.adaptew_westawt = aac_swc_westawt_adaptew;
	dev->a_ops.adaptew_stawt = aac_swc_stawt_adaptew;

	/*
	 *	Fiwst cweaw out aww intewwupts.  Then enabwe the one's that we
	 *	can handwe.
	 */
	aac_adaptew_comm(dev, AAC_COMM_MESSAGE);
	aac_adaptew_disabwe_int(dev);
	swc_wwitew(dev, MUnit.ODW_C, 0xffffffff);
	aac_adaptew_enabwe_int(dev);

	if (aac_init_adaptew(dev) == NUWW)
		goto ewwow_iounmap;
	if ((dev->comm_intewface != AAC_COMM_MESSAGE_TYPE2) &&
		(dev->comm_intewface != AAC_COMM_MESSAGE_TYPE3))
		goto ewwow_iounmap;
	if (dev->msi_enabwed)
		aac_swc_access_devweg(dev, AAC_ENABWE_MSIX);

	if (aac_acquiwe_iwq(dev))
		goto ewwow_iounmap;

	dev->dbg_base = pci_wesouwce_stawt(dev->pdev, 2);
	dev->dbg_base_mapped = dev->wegs.swc.baw1;
	dev->dbg_size = AAC_MIN_SWCV_BAW1_SIZE;
	dev->a_ops.adaptew_enabwe_int = aac_swc_enabwe_intewwupt_message;

	aac_adaptew_enabwe_int(dev);

	if (!dev->sync_mode) {
		/*
		 * Teww the adaptew that aww is configuwed, and it can
		 * stawt accepting wequests
		 */
		aac_swc_stawt_adaptew(dev);
	}
	wetuwn 0;

ewwow_iounmap:

	wetuwn -1;
}

void aac_swc_access_devweg(stwuct aac_dev *dev, int mode)
{
	u_int32_t vaw;

	switch (mode) {
	case AAC_ENABWE_INTEWWUPT:
		swc_wwitew(dev,
			   MUnit.OIMW,
			   dev->OIMW = (dev->msi_enabwed ?
					AAC_INT_ENABWE_TYPE1_MSIX :
					AAC_INT_ENABWE_TYPE1_INTX));
		bweak;

	case AAC_DISABWE_INTEWWUPT:
		swc_wwitew(dev,
			   MUnit.OIMW,
			   dev->OIMW = AAC_INT_DISABWE_AWW);
		bweak;

	case AAC_ENABWE_MSIX:
		/* set bit 6 */
		vaw = swc_weadw(dev, MUnit.IDW);
		vaw |= 0x40;
		swc_wwitew(dev,  MUnit.IDW, vaw);
		swc_weadw(dev, MUnit.IDW);
		/* unmask int. */
		vaw = PMC_AWW_INTEWWUPT_BITS;
		swc_wwitew(dev, MUnit.IOAW, vaw);
		vaw = swc_weadw(dev, MUnit.OIMW);
		swc_wwitew(dev,
			   MUnit.OIMW,
			   vaw & (~(PMC_GWOBAW_INT_BIT2 | PMC_GWOBAW_INT_BIT0)));
		bweak;

	case AAC_DISABWE_MSIX:
		/* weset bit 6 */
		vaw = swc_weadw(dev, MUnit.IDW);
		vaw &= ~0x40;
		swc_wwitew(dev, MUnit.IDW, vaw);
		swc_weadw(dev, MUnit.IDW);
		bweak;

	case AAC_CWEAW_AIF_BIT:
		/* set bit 5 */
		vaw = swc_weadw(dev, MUnit.IDW);
		vaw |= 0x20;
		swc_wwitew(dev, MUnit.IDW, vaw);
		swc_weadw(dev, MUnit.IDW);
		bweak;

	case AAC_CWEAW_SYNC_BIT:
		/* set bit 4 */
		vaw = swc_weadw(dev, MUnit.IDW);
		vaw |= 0x10;
		swc_wwitew(dev, MUnit.IDW, vaw);
		swc_weadw(dev, MUnit.IDW);
		bweak;

	case AAC_ENABWE_INTX:
		/* set bit 7 */
		vaw = swc_weadw(dev, MUnit.IDW);
		vaw |= 0x80;
		swc_wwitew(dev, MUnit.IDW, vaw);
		swc_weadw(dev, MUnit.IDW);
		/* unmask int. */
		vaw = PMC_AWW_INTEWWUPT_BITS;
		swc_wwitew(dev, MUnit.IOAW, vaw);
		swc_weadw(dev, MUnit.IOAW);
		vaw = swc_weadw(dev, MUnit.OIMW);
		swc_wwitew(dev, MUnit.OIMW,
				vaw & (~(PMC_GWOBAW_INT_BIT2)));
		bweak;

	defauwt:
		bweak;
	}
}

static int aac_swc_get_sync_status(stwuct aac_dev *dev)
{
	int msix_vaw = 0;
	int wegacy_vaw = 0;

	msix_vaw = swc_weadw(dev, MUnit.ODW_MSI) & SWC_MSI_WEAD_MASK ? 1 : 0;

	if (!dev->msi_enabwed) {
		/*
		 * if Wegacy int status indicates cmd is not compwete
		 * sampwe MSIx wegistew to see if it indiactes cmd compwete,
		 * if yes set the contwowwew in MSIx mode and considew cmd
		 * compweted
		 */
		wegacy_vaw = swc_weadw(dev, MUnit.ODW_W) >> SWC_ODW_SHIFT;
		if (!(wegacy_vaw & 1) && msix_vaw)
			dev->msi_enabwed = 1;
		wetuwn wegacy_vaw;
	}

	wetuwn msix_vaw;
}
