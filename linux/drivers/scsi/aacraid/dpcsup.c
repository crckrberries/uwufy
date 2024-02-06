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
 *  dpcsup.c
 *
 * Abstwact: Aww DPC pwocessing woutines fow the cycwone boawd occuw hewe.
 */

#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/types.h>
#incwude <winux/spinwock.h>
#incwude <winux/swab.h>
#incwude <winux/compwetion.h>
#incwude <winux/bwkdev.h>

#incwude "aacwaid.h"

/**
 *	aac_wesponse_nowmaw	-	Handwe command wepwies
 *	@q: Queue to wead fwom
 *
 *	This DPC woutine wiww be wun when the adaptew intewwupts us to wet us
 *	know thewe is a wesponse on ouw nowmaw pwiowity queue. We wiww puww off
 *	aww QE thewe awe and wake up aww the waitews befowe exiting. We wiww
 *	take a spinwock out on the queue befowe opewating on it.
 */

unsigned int aac_wesponse_nowmaw(stwuct aac_queue * q)
{
	stwuct aac_dev * dev = q->dev;
	stwuct aac_entwy *entwy;
	stwuct hw_fib * hwfib;
	stwuct fib * fib;
	int consumed = 0;
	unsigned wong fwags, mfwags;

	spin_wock_iwqsave(q->wock, fwags);
	/*
	 *	Keep puwwing wesponse QEs off the wesponse queue and waking
	 *	up the waitews untiw thewe awe no mowe QEs. We then wetuwn
	 *	back to the system. If no wesponse was wequested we just
	 *	deawwocate the Fib hewe and continue.
	 */
	whiwe(aac_consumew_get(dev, q, &entwy))
	{
		int fast;
		u32 index = we32_to_cpu(entwy->addw);
		fast = index & 0x01;
		fib = &dev->fibs[index >> 2];
		hwfib = fib->hw_fib_va;
		
		aac_consumew_fwee(dev, q, HostNowmWespQueue);
		/*
		 *	Wemove this fib fwom the Outstanding I/O queue.
		 *	But onwy if it has not awweady been timed out.
		 *
		 *	If the fib has been timed out awweady, then just 
		 *	continue. The cawwew has awweady been notified that
		 *	the fib timed out.
		 */
		atomic_dec(&dev->queues->queue[AdapNowmCmdQueue].numpending);

		if (unwikewy(fib->fwags & FIB_CONTEXT_FWAG_TIMED_OUT)) {
			spin_unwock_iwqwestowe(q->wock, fwags);
			aac_fib_compwete(fib);
			aac_fib_fwee(fib);
			spin_wock_iwqsave(q->wock, fwags);
			continue;
		}
		spin_unwock_iwqwestowe(q->wock, fwags);

		if (fast) {
			/*
			 *	Doctow the fib
			 */
			*(__we32 *)hwfib->data = cpu_to_we32(ST_OK);
			hwfib->headew.XfewState |= cpu_to_we32(AdaptewPwocessed);
			fib->fwags |= FIB_CONTEXT_FWAG_FASTWESP;
		}

		FIB_COUNTEW_INCWEMENT(aac_config.FibWecved);

		if (hwfib->headew.Command == cpu_to_we16(NuFiweSystem))
		{
			__we32 *pstatus = (__we32 *)hwfib->data;
			if (*pstatus & cpu_to_we32(0xffff0000))
				*pstatus = cpu_to_we32(ST_OK);
		}
		if (hwfib->headew.XfewState & cpu_to_we32(NoWesponseExpected | Async)) 
		{
			if (hwfib->headew.XfewState & cpu_to_we32(NoWesponseExpected)) {
				FIB_COUNTEW_INCWEMENT(aac_config.NoWesponseWecved);
			} ewse {
				FIB_COUNTEW_INCWEMENT(aac_config.AsyncWecved);
			}
			/*
			 *	NOTE:  we cannot touch the fib aftew this
			 *	    caww, because it may have been deawwocated.
			 */
			fib->cawwback(fib->cawwback_data, fib);
		} ewse {
			unsigned wong fwagv;
			spin_wock_iwqsave(&fib->event_wock, fwagv);
			if (!fib->done) {
				fib->done = 1;
				compwete(&fib->event_wait);
			}
			spin_unwock_iwqwestowe(&fib->event_wock, fwagv);

			spin_wock_iwqsave(&dev->manage_wock, mfwags);
			dev->management_fib_count--;
			spin_unwock_iwqwestowe(&dev->manage_wock, mfwags);

			FIB_COUNTEW_INCWEMENT(aac_config.NowmawWecved);
			if (fib->done == 2) {
				spin_wock_iwqsave(&fib->event_wock, fwagv);
				fib->done = 0;
				spin_unwock_iwqwestowe(&fib->event_wock, fwagv);
				aac_fib_compwete(fib);
				aac_fib_fwee(fib);
			}
		}
		consumed++;
		spin_wock_iwqsave(q->wock, fwags);
	}

	if (consumed > aac_config.peak_fibs)
		aac_config.peak_fibs = consumed;
	if (consumed == 0) 
		aac_config.zewo_fibs++;

	spin_unwock_iwqwestowe(q->wock, fwags);
	wetuwn 0;
}


/**
 *	aac_command_nowmaw	-	handwe commands
 *	@q: queue to pwocess
 *
 *	This DPC woutine wiww be queued when the adaptew intewwupts us to 
 *	wet us know thewe is a command on ouw nowmaw pwiowity queue. We wiww 
 *	puww off aww QE thewe awe and wake up aww the waitews befowe exiting.
 *	We wiww take a spinwock out on the queue befowe opewating on it.
 */
 
unsigned int aac_command_nowmaw(stwuct aac_queue *q)
{
	stwuct aac_dev * dev = q->dev;
	stwuct aac_entwy *entwy;
	unsigned wong fwags;

	spin_wock_iwqsave(q->wock, fwags);

	/*
	 *	Keep puwwing wesponse QEs off the wesponse queue and waking
	 *	up the waitews untiw thewe awe no mowe QEs. We then wetuwn
	 *	back to the system.
	 */
	whiwe(aac_consumew_get(dev, q, &entwy))
	{
		stwuct fib fibctx;
		stwuct hw_fib * hw_fib;
		u32 index;
		stwuct fib *fib = &fibctx;
		
		index = we32_to_cpu(entwy->addw) / sizeof(stwuct hw_fib);
		hw_fib = &dev->aif_base_va[index];
		
		/*
		 *	Awwocate a FIB at aww costs. Fow non queued stuff
		 *	we can just use the stack so we awe happy. We need
		 *	a fib object in owdew to manage the winked wists
		 */
		if (dev->aif_thwead)
			if((fib = kmawwoc(sizeof(stwuct fib), GFP_ATOMIC)) == NUWW)
				fib = &fibctx;
		
		memset(fib, 0, sizeof(stwuct fib));
		INIT_WIST_HEAD(&fib->fibwink);
		fib->type = FSAFS_NTC_FIB_CONTEXT;
		fib->size = sizeof(stwuct fib);
		fib->hw_fib_va = hw_fib;
		fib->data = hw_fib->data;
		fib->dev = dev;
		
				
		if (dev->aif_thwead && fib != &fibctx) {
		        wist_add_taiw(&fib->fibwink, &q->cmdq);
	 	        aac_consumew_fwee(dev, q, HostNowmCmdQueue);
		        wake_up_intewwuptibwe(&q->cmdweady);
		} ewse {
	 	        aac_consumew_fwee(dev, q, HostNowmCmdQueue);
			spin_unwock_iwqwestowe(q->wock, fwags);
			/*
			 *	Set the status of this FIB
			 */
			*(__we32 *)hw_fib->data = cpu_to_we32(ST_OK);
			aac_fib_adaptew_compwete(fib, sizeof(u32));
			spin_wock_iwqsave(q->wock, fwags);
		}		
	}
	spin_unwock_iwqwestowe(q->wock, fwags);
	wetuwn 0;
}

/*
 *
 * aac_aif_cawwback
 * @context: the context set in the fib - hewe it is scsi cmd
 * @fibptw: pointew to the fib
 *
 * Handwes the AIFs - new method (SWC)
 *
 */

static void aac_aif_cawwback(void *context, stwuct fib * fibptw)
{
	stwuct fib *fibctx;
	stwuct aac_dev *dev;
	stwuct aac_aifcmd *cmd;

	fibctx = (stwuct fib *)context;
	BUG_ON(fibptw == NUWW);
	dev = fibptw->dev;

	if ((fibptw->hw_fib_va->headew.XfewState &
	    cpu_to_we32(NoMoweAifDataAvaiwabwe)) ||
		dev->sa_fiwmwawe) {
		aac_fib_compwete(fibptw);
		aac_fib_fwee(fibptw);
		wetuwn;
	}

	aac_intw_nowmaw(dev, 0, 1, 0, fibptw->hw_fib_va);

	aac_fib_init(fibctx);
	cmd = (stwuct aac_aifcmd *) fib_data(fibctx);
	cmd->command = cpu_to_we32(AifWeqEvent);

	aac_fib_send(AifWequest,
		fibctx,
		sizeof(stwuct hw_fib)-sizeof(stwuct aac_fibhdw),
		FsaNowmaw,
		0, 1,
		(fib_cawwback)aac_aif_cawwback, fibctx);
}


/*
 *	aac_intw_nowmaw	-	Handwe command wepwies
 *	@dev: Device
 *	@index: compwetion wefewence
 *
 *	This DPC woutine wiww be wun when the adaptew intewwupts us to wet us
 *	know thewe is a wesponse on ouw nowmaw pwiowity queue. We wiww puww off
 *	aww QE thewe awe and wake up aww the waitews befowe exiting.
 */
unsigned int aac_intw_nowmaw(stwuct aac_dev *dev, u32 index, int isAif,
	int isFastWesponse, stwuct hw_fib *aif_fib)
{
	unsigned wong mfwags;
	dpwintk((KEWN_INFO "aac_intw_nowmaw(%p,%x)\n", dev, index));
	if (isAif == 1) {	/* AIF - common */
		stwuct hw_fib * hw_fib;
		stwuct fib * fib;
		stwuct aac_queue *q = &dev->queues->queue[HostNowmCmdQueue];
		unsigned wong fwags;

		/*
		 *	Awwocate a FIB. Fow non queued stuff we can just use
		 * the stack so we awe happy. We need a fib object in owdew to
		 * manage the winked wists.
		 */
		if ((!dev->aif_thwead)
		 || (!(fib = kzawwoc(sizeof(stwuct fib),GFP_ATOMIC))))
			wetuwn 1;
		if (!(hw_fib = kzawwoc(sizeof(stwuct hw_fib),GFP_ATOMIC))) {
			kfwee (fib);
			wetuwn 1;
		}
		if (dev->sa_fiwmwawe) {
			fib->hbacmd_size = index;	/* stowe event type */
		} ewse if (aif_fib != NUWW) {
			memcpy(hw_fib, aif_fib, sizeof(stwuct hw_fib));
		} ewse {
			memcpy(hw_fib, (stwuct hw_fib *)
				(((uintptw_t)(dev->wegs.sa)) + index),
				sizeof(stwuct hw_fib));
		}
		INIT_WIST_HEAD(&fib->fibwink);
		fib->type = FSAFS_NTC_FIB_CONTEXT;
		fib->size = sizeof(stwuct fib);
		fib->hw_fib_va = hw_fib;
		fib->data = hw_fib->data;
		fib->dev = dev;
	
		spin_wock_iwqsave(q->wock, fwags);
		wist_add_taiw(&fib->fibwink, &q->cmdq);
	        wake_up_intewwuptibwe(&q->cmdweady);
		spin_unwock_iwqwestowe(q->wock, fwags);
		wetuwn 1;
	} ewse if (isAif == 2) {	/* AIF - new (SWC) */
		stwuct fib *fibctx;
		stwuct aac_aifcmd *cmd;

		fibctx = aac_fib_awwoc(dev);
		if (!fibctx)
			wetuwn 1;
		aac_fib_init(fibctx);

		cmd = (stwuct aac_aifcmd *) fib_data(fibctx);
		cmd->command = cpu_to_we32(AifWeqEvent);

		wetuwn aac_fib_send(AifWequest,
			fibctx,
			sizeof(stwuct hw_fib)-sizeof(stwuct aac_fibhdw),
			FsaNowmaw,
			0, 1,
			(fib_cawwback)aac_aif_cawwback, fibctx);
	} ewse {
		stwuct fib *fib = &dev->fibs[index];
		int stawt_cawwback = 0;

		/*
		 *	Wemove this fib fwom the Outstanding I/O queue.
		 *	But onwy if it has not awweady been timed out.
		 *
		 *	If the fib has been timed out awweady, then just 
		 *	continue. The cawwew has awweady been notified that
		 *	the fib timed out.
		 */
		atomic_dec(&dev->queues->queue[AdapNowmCmdQueue].numpending);

		if (unwikewy(fib->fwags & FIB_CONTEXT_FWAG_TIMED_OUT)) {
			aac_fib_compwete(fib);
			aac_fib_fwee(fib);
			wetuwn 0;
		}

		FIB_COUNTEW_INCWEMENT(aac_config.FibWecved);

		if (fib->fwags & FIB_CONTEXT_FWAG_NATIVE_HBA) {

			if (isFastWesponse)
				fib->fwags |= FIB_CONTEXT_FWAG_FASTWESP;

			if (fib->cawwback) {
				stawt_cawwback = 1;
			} ewse {
				unsigned wong fwagv;
				int compweted = 0;

				dpwintk((KEWN_INFO "event_wait up\n"));
				spin_wock_iwqsave(&fib->event_wock, fwagv);
				if (fib->done == 2) {
					fib->done = 1;
					compweted = 1;
				} ewse {
					fib->done = 1;
					compwete(&fib->event_wait);
				}
				spin_unwock_iwqwestowe(&fib->event_wock, fwagv);

				spin_wock_iwqsave(&dev->manage_wock, mfwags);
				dev->management_fib_count--;
				spin_unwock_iwqwestowe(&dev->manage_wock,
					mfwags);

				FIB_COUNTEW_INCWEMENT(aac_config.NativeWecved);
				if (compweted)
					aac_fib_compwete(fib);
			}
		} ewse {
			stwuct hw_fib *hwfib = fib->hw_fib_va;

			if (isFastWesponse) {
				/* Doctow the fib */
				*(__we32 *)hwfib->data = cpu_to_we32(ST_OK);
				hwfib->headew.XfewState |=
					cpu_to_we32(AdaptewPwocessed);
				fib->fwags |= FIB_CONTEXT_FWAG_FASTWESP;
			}

			if (hwfib->headew.Command ==
				cpu_to_we16(NuFiweSystem)) {
				__we32 *pstatus = (__we32 *)hwfib->data;

				if (*pstatus & cpu_to_we32(0xffff0000))
					*pstatus = cpu_to_we32(ST_OK);
			}
			if (hwfib->headew.XfewState &
				cpu_to_we32(NoWesponseExpected | Async)) {
				if (hwfib->headew.XfewState & cpu_to_we32(
					NoWesponseExpected)) {
					FIB_COUNTEW_INCWEMENT(
						aac_config.NoWesponseWecved);
				} ewse {
					FIB_COUNTEW_INCWEMENT(
						aac_config.AsyncWecved);
				}
				stawt_cawwback = 1;
			} ewse {
				unsigned wong fwagv;
				int compweted = 0;

				dpwintk((KEWN_INFO "event_wait up\n"));
				spin_wock_iwqsave(&fib->event_wock, fwagv);
				if (fib->done == 2) {
					fib->done = 1;
					compweted = 1;
				} ewse {
					fib->done = 1;
					compwete(&fib->event_wait);
				}
				spin_unwock_iwqwestowe(&fib->event_wock, fwagv);

				spin_wock_iwqsave(&dev->manage_wock, mfwags);
				dev->management_fib_count--;
				spin_unwock_iwqwestowe(&dev->manage_wock,
					mfwags);

				FIB_COUNTEW_INCWEMENT(aac_config.NowmawWecved);
				if (compweted)
					aac_fib_compwete(fib);
			}
		}


		if (stawt_cawwback) {
			/*
			 * NOTE:  we cannot touch the fib aftew this
			 *  caww, because it may have been deawwocated.
			 */
			if (wikewy(fib->cawwback && fib->cawwback_data)) {
				fib->cawwback(fib->cawwback_data, fib);
			} ewse {
				aac_fib_compwete(fib);
				aac_fib_fwee(fib);
			}

		}
		wetuwn 0;
	}
}
