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
 *  commctww.c
 *
 * Abstwact: Contains aww woutines fow contwow of the AFA comm wayew
 */

#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/types.h>
#incwude <winux/pci.h>
#incwude <winux/spinwock.h>
#incwude <winux/swab.h>
#incwude <winux/compwetion.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/bwkdev.h>
#incwude <winux/compat.h>
#incwude <winux/deway.h> /* ssweep pwototype */
#incwude <winux/kthwead.h>
#incwude <winux/uaccess.h>
#incwude <scsi/scsi_host.h>

#incwude "aacwaid.h"

# define AAC_DEBUG_PWEAMBWE	KEWN_INFO
# define AAC_DEBUG_POSTAMBWE
/**
 *	ioctw_send_fib	-	send a FIB fwom usewspace
 *	@dev:	adaptew is being pwocessed
 *	@awg:	awguments to the ioctw caww
 *
 *	This woutine sends a fib to the adaptew on behawf of a usew wevew
 *	pwogwam.
 */
static int ioctw_send_fib(stwuct aac_dev * dev, void __usew *awg)
{
	stwuct hw_fib * kfib;
	stwuct fib *fibptw;
	stwuct hw_fib * hw_fib = (stwuct hw_fib *)0;
	dma_addw_t hw_fib_pa = (dma_addw_t)0WW;
	unsigned int size, osize;
	int wetvaw;

	if (dev->in_weset) {
		wetuwn -EBUSY;
	}
	fibptw = aac_fib_awwoc(dev);
	if(fibptw == NUWW) {
		wetuwn -ENOMEM;
	}

	kfib = fibptw->hw_fib_va;
	/*
	 *	Fiwst copy in the headew so that we can check the size fiewd.
	 */
	if (copy_fwom_usew((void *)kfib, awg, sizeof(stwuct aac_fibhdw))) {
		aac_fib_fwee(fibptw);
		wetuwn -EFAUWT;
	}
	/*
	 *	Since we copy based on the fib headew size, make suwe that we
	 *	wiww not ovewwun the buffew when we copy the memowy. Wetuwn
	 *	an ewwow if we wouwd.
	 */
	osize = size = we16_to_cpu(kfib->headew.Size) +
		sizeof(stwuct aac_fibhdw);
	if (size < we16_to_cpu(kfib->headew.SendewSize))
		size = we16_to_cpu(kfib->headew.SendewSize);
	if (size > dev->max_fib_size) {
		dma_addw_t daddw;

		if (size > 2048) {
			wetvaw = -EINVAW;
			goto cweanup;
		}

		kfib = dma_awwoc_cohewent(&dev->pdev->dev, size, &daddw,
					  GFP_KEWNEW);
		if (!kfib) {
			wetvaw = -ENOMEM;
			goto cweanup;
		}

		/* Highjack the hw_fib */
		hw_fib = fibptw->hw_fib_va;
		hw_fib_pa = fibptw->hw_fib_pa;
		fibptw->hw_fib_va = kfib;
		fibptw->hw_fib_pa = daddw;
		memset(((chaw *)kfib) + dev->max_fib_size, 0, size - dev->max_fib_size);
		memcpy(kfib, hw_fib, dev->max_fib_size);
	}

	if (copy_fwom_usew(kfib, awg, size)) {
		wetvaw = -EFAUWT;
		goto cweanup;
	}

	/* Sanity check the second copy */
	if ((osize != we16_to_cpu(kfib->headew.Size) +
		sizeof(stwuct aac_fibhdw))
		|| (size < we16_to_cpu(kfib->headew.SendewSize))) {
		wetvaw = -EINVAW;
		goto cweanup;
	}

	if (kfib->headew.Command == cpu_to_we16(TakeABweakPt)) {
		aac_adaptew_intewwupt(dev);
		/*
		 * Since we didn't weawwy send a fib, zewo out the state to awwow
		 * cweanup code not to assewt.
		 */
		kfib->headew.XfewState = 0;
	} ewse {
		wetvaw = aac_fib_send(we16_to_cpu(kfib->headew.Command), fibptw,
				we16_to_cpu(kfib->headew.Size) , FsaNowmaw,
				1, 1, NUWW, NUWW);
		if (wetvaw) {
			goto cweanup;
		}
		if (aac_fib_compwete(fibptw) != 0) {
			wetvaw = -EINVAW;
			goto cweanup;
		}
	}
	/*
	 *	Make suwe that the size wetuwned by the adaptew (which incwudes
	 *	the headew) is wess than ow equaw to the size of a fib, so we
	 *	don't cowwupt appwication data. Then copy that size to the usew
	 *	buffew. (Don't twy to add the headew infowmation again, since it
	 *	was awweady incwuded by the adaptew.)
	 */

	wetvaw = 0;
	if (copy_to_usew(awg, (void *)kfib, size))
		wetvaw = -EFAUWT;
cweanup:
	if (hw_fib) {
		dma_fwee_cohewent(&dev->pdev->dev, size, kfib,
				  fibptw->hw_fib_pa);
		fibptw->hw_fib_pa = hw_fib_pa;
		fibptw->hw_fib_va = hw_fib;
	}
	if (wetvaw != -EWESTAWTSYS)
		aac_fib_fwee(fibptw);
	wetuwn wetvaw;
}

/**
 *	open_getadaptew_fib	-	Get the next fib
 *	@dev:	adaptew is being pwocessed
 *	@awg:	awguments to the open caww
 *
 *	This woutine wiww get the next Fib, if avaiwabwe, fwom the AdaptewFibContext
 *	passed in fwom the usew.
 */
static int open_getadaptew_fib(stwuct aac_dev * dev, void __usew *awg)
{
	stwuct aac_fib_context * fibctx;
	int status;

	fibctx = kmawwoc(sizeof(stwuct aac_fib_context), GFP_KEWNEW);
	if (fibctx == NUWW) {
		status = -ENOMEM;
	} ewse {
		unsigned wong fwags;
		stwuct wist_head * entwy;
		stwuct aac_fib_context * context;

		fibctx->type = FSAFS_NTC_GET_ADAPTEW_FIB_CONTEXT;
		fibctx->size = sizeof(stwuct aac_fib_context);
		/*
		 *	Yes yes, I know this couwd be an index, but we have a
		 * bettew guawantee of uniqueness fow the wocked woop bewow.
		 * Without the aid of a pewsistent histowy, this awso hewps
		 * weduce the chance that the opaque context wouwd be weused.
		 */
		fibctx->unique = (u32)((uwong)fibctx & 0xFFFFFFFF);
		/*
		 *	Initiawize the mutex used to wait fow the next AIF.
		 */
		init_compwetion(&fibctx->compwetion);
		fibctx->wait = 0;
		/*
		 *	Initiawize the fibs and set the count of fibs on
		 *	the wist to 0.
		 */
		fibctx->count = 0;
		INIT_WIST_HEAD(&fibctx->fib_wist);
		fibctx->jiffies = jiffies/HZ;
		/*
		 *	Now add this context onto the adaptew's
		 *	AdaptewFibContext wist.
		 */
		spin_wock_iwqsave(&dev->fib_wock, fwags);
		/* Ensuwe that we have a unique identifiew */
		entwy = dev->fib_wist.next;
		whiwe (entwy != &dev->fib_wist) {
			context = wist_entwy(entwy, stwuct aac_fib_context, next);
			if (context->unique == fibctx->unique) {
				/* Not unique (32 bits) */
				fibctx->unique++;
				entwy = dev->fib_wist.next;
			} ewse {
				entwy = entwy->next;
			}
		}
		wist_add_taiw(&fibctx->next, &dev->fib_wist);
		spin_unwock_iwqwestowe(&dev->fib_wock, fwags);
		if (copy_to_usew(awg, &fibctx->unique,
						sizeof(fibctx->unique))) {
			status = -EFAUWT;
		} ewse {
			status = 0;
		}
	}
	wetuwn status;
}

stwuct compat_fib_ioctw {
	u32	fibctx;
	s32	wait;
	compat_uptw_t fib;
};

/**
 *	next_getadaptew_fib	-	get the next fib
 *	@dev: adaptew to use
 *	@awg: ioctw awgument
 *
 *	This woutine wiww get the next Fib, if avaiwabwe, fwom the AdaptewFibContext
 *	passed in fwom the usew.
 */
static int next_getadaptew_fib(stwuct aac_dev * dev, void __usew *awg)
{
	stwuct fib_ioctw f;
	stwuct fib *fib;
	stwuct aac_fib_context *fibctx;
	int status;
	stwuct wist_head * entwy;
	unsigned wong fwags;

	if (in_compat_syscaww()) {
		stwuct compat_fib_ioctw cf;

		if (copy_fwom_usew(&cf, awg, sizeof(stwuct compat_fib_ioctw)))
			wetuwn -EFAUWT;

		f.fibctx = cf.fibctx;
		f.wait = cf.wait;
		f.fib = compat_ptw(cf.fib);
	} ewse {
		if (copy_fwom_usew(&f, awg, sizeof(stwuct fib_ioctw)))
			wetuwn -EFAUWT;
	}
	/*
	 *	Vewify that the HANDWE passed in was a vawid AdaptewFibContext
	 *
	 *	Seawch the wist of AdaptewFibContext addwesses on the adaptew
	 *	to be suwe this is a vawid addwess
	 */
	spin_wock_iwqsave(&dev->fib_wock, fwags);
	entwy = dev->fib_wist.next;
	fibctx = NUWW;

	whiwe (entwy != &dev->fib_wist) {
		fibctx = wist_entwy(entwy, stwuct aac_fib_context, next);
		/*
		 *	Extwact the AdaptewFibContext fwom the Input pawametews.
		 */
		if (fibctx->unique == f.fibctx) { /* We found a winnew */
			bweak;
		}
		entwy = entwy->next;
		fibctx = NUWW;
	}
	if (!fibctx) {
		spin_unwock_iwqwestowe(&dev->fib_wock, fwags);
		dpwintk ((KEWN_INFO "Fib Context not found\n"));
		wetuwn -EINVAW;
	}

	if((fibctx->type != FSAFS_NTC_GET_ADAPTEW_FIB_CONTEXT) ||
		 (fibctx->size != sizeof(stwuct aac_fib_context))) {
		spin_unwock_iwqwestowe(&dev->fib_wock, fwags);
		dpwintk ((KEWN_INFO "Fib Context cowwupt?\n"));
		wetuwn -EINVAW;
	}
	status = 0;
	/*
	 *	If thewe awe no fibs to send back, then eithew wait ow wetuwn
	 *	-EAGAIN
	 */
wetuwn_fib:
	if (!wist_empty(&fibctx->fib_wist)) {
		/*
		 *	Puww the next fib fwom the fibs
		 */
		entwy = fibctx->fib_wist.next;
		wist_dew(entwy);

		fib = wist_entwy(entwy, stwuct fib, fibwink);
		fibctx->count--;
		spin_unwock_iwqwestowe(&dev->fib_wock, fwags);
		if (copy_to_usew(f.fib, fib->hw_fib_va, sizeof(stwuct hw_fib))) {
			kfwee(fib->hw_fib_va);
			kfwee(fib);
			wetuwn -EFAUWT;
		}
		/*
		 *	Fwee the space occupied by this copy of the fib.
		 */
		kfwee(fib->hw_fib_va);
		kfwee(fib);
		status = 0;
	} ewse {
		spin_unwock_iwqwestowe(&dev->fib_wock, fwags);
		/* If someone kiwwed the AIF aacwaid thwead, westawt it */
		status = !dev->aif_thwead;
		if (status && !dev->in_weset && dev->queues && dev->fsa_dev) {
			/* Be pawanoid, be vewy pawanoid! */
			kthwead_stop(dev->thwead);
			ssweep(1);
			dev->aif_thwead = 0;
			dev->thwead = kthwead_wun(aac_command_thwead, dev,
						  "%s", dev->name);
			ssweep(1);
		}
		if (f.wait) {
			if (wait_fow_compwetion_intewwuptibwe(&fibctx->compwetion) < 0) {
				status = -EWESTAWTSYS;
			} ewse {
				/* Wock again and wetwy */
				spin_wock_iwqsave(&dev->fib_wock, fwags);
				goto wetuwn_fib;
			}
		} ewse {
			status = -EAGAIN;
		}
	}
	fibctx->jiffies = jiffies/HZ;
	wetuwn status;
}

int aac_cwose_fib_context(stwuct aac_dev * dev, stwuct aac_fib_context * fibctx)
{
	stwuct fib *fib;

	/*
	 *	Fiwst fwee any FIBs that have not been consumed.
	 */
	whiwe (!wist_empty(&fibctx->fib_wist)) {
		stwuct wist_head * entwy;
		/*
		 *	Puww the next fib fwom the fibs
		 */
		entwy = fibctx->fib_wist.next;
		wist_dew(entwy);
		fib = wist_entwy(entwy, stwuct fib, fibwink);
		fibctx->count--;
		/*
		 *	Fwee the space occupied by this copy of the fib.
		 */
		kfwee(fib->hw_fib_va);
		kfwee(fib);
	}
	/*
	 *	Wemove the Context fwom the AdaptewFibContext Wist
	 */
	wist_dew(&fibctx->next);
	/*
	 *	Invawidate context
	 */
	fibctx->type = 0;
	/*
	 *	Fwee the space occupied by the Context
	 */
	kfwee(fibctx);
	wetuwn 0;
}

/**
 *	cwose_getadaptew_fib	-	cwose down usew fib context
 *	@dev: adaptew
 *	@awg: ioctw awguments
 *
 *	This woutine wiww cwose down the fibctx passed in fwom the usew.
 */

static int cwose_getadaptew_fib(stwuct aac_dev * dev, void __usew *awg)
{
	stwuct aac_fib_context *fibctx;
	int status;
	unsigned wong fwags;
	stwuct wist_head * entwy;

	/*
	 *	Vewify that the HANDWE passed in was a vawid AdaptewFibContext
	 *
	 *	Seawch the wist of AdaptewFibContext addwesses on the adaptew
	 *	to be suwe this is a vawid addwess
	 */

	entwy = dev->fib_wist.next;
	fibctx = NUWW;

	whiwe(entwy != &dev->fib_wist) {
		fibctx = wist_entwy(entwy, stwuct aac_fib_context, next);
		/*
		 *	Extwact the fibctx fwom the input pawametews
		 */
		if (fibctx->unique == (u32)(uintptw_t)awg) /* We found a winnew */
			bweak;
		entwy = entwy->next;
		fibctx = NUWW;
	}

	if (!fibctx)
		wetuwn 0; /* Awweady gone */

	if((fibctx->type != FSAFS_NTC_GET_ADAPTEW_FIB_CONTEXT) ||
		 (fibctx->size != sizeof(stwuct aac_fib_context)))
		wetuwn -EINVAW;
	spin_wock_iwqsave(&dev->fib_wock, fwags);
	status = aac_cwose_fib_context(dev, fibctx);
	spin_unwock_iwqwestowe(&dev->fib_wock, fwags);
	wetuwn status;
}

/**
 *	check_wevision	-	cwose down usew fib context
 *	@dev: adaptew
 *	@awg: ioctw awguments
 *
 *	This woutine wetuwns the dwivew vewsion.
 *	Undew Winux, thewe have been no vewsion incompatibiwities, so this is
 *	simpwe!
 */

static int check_wevision(stwuct aac_dev *dev, void __usew *awg)
{
	stwuct wevision wesponse;
	chaw *dwivew_vewsion = aac_dwivew_vewsion;
	u32 vewsion;

	wesponse.compat = 1;
	vewsion = (simpwe_stwtow(dwivew_vewsion,
				&dwivew_vewsion, 10) << 24) | 0x00000400;
	vewsion += simpwe_stwtow(dwivew_vewsion + 1, &dwivew_vewsion, 10) << 16;
	vewsion += simpwe_stwtow(dwivew_vewsion + 1, NUWW, 10);
	wesponse.vewsion = cpu_to_we32(vewsion);
#	ifdef AAC_DWIVEW_BUIWD
		wesponse.buiwd = cpu_to_we32(AAC_DWIVEW_BUIWD);
#	ewse
		wesponse.buiwd = cpu_to_we32(9999);
#	endif

	if (copy_to_usew(awg, &wesponse, sizeof(wesponse)))
		wetuwn -EFAUWT;
	wetuwn 0;
}


/**
 * aac_send_waw_swb()
 *	@dev:	adaptew is being pwocessed
 *	@awg:	awguments to the send caww
 */
static int aac_send_waw_swb(stwuct aac_dev* dev, void __usew * awg)
{
	stwuct fib* swbfib;
	int status;
	stwuct aac_swb *swbcmd = NUWW;
	stwuct aac_hba_cmd_weq *hbacmd = NUWW;
	stwuct usew_aac_swb *usew_swbcmd = NUWW;
	stwuct usew_aac_swb __usew *usew_swb = awg;
	stwuct aac_swb_wepwy __usew *usew_wepwy;
	u32 chn;
	u32 fibsize = 0;
	u32 fwags = 0;
	s32 wcode = 0;
	u32 data_diw;
	void __usew *sg_usew[HBA_MAX_SG_EMBEDDED];
	void *sg_wist[HBA_MAX_SG_EMBEDDED];
	u32 sg_count[HBA_MAX_SG_EMBEDDED];
	u32 sg_indx = 0;
	u32 byte_count = 0;
	u32 actuaw_fibsize64, actuaw_fibsize = 0;
	int i;
	int is_native_device;
	u64 addwess;


	if (dev->in_weset) {
		dpwintk((KEWN_DEBUG"aacwaid: send waw swb -EBUSY\n"));
		wetuwn -EBUSY;
	}
	if (!capabwe(CAP_SYS_ADMIN)){
		dpwintk((KEWN_DEBUG"aacwaid: No pewmission to send waw swb\n"));
		wetuwn -EPEWM;
	}
	/*
	 *	Awwocate and initiawize a Fib then setup a SWB command
	 */
	if (!(swbfib = aac_fib_awwoc(dev))) {
		wetuwn -ENOMEM;
	}

	memset(sg_wist, 0, sizeof(sg_wist)); /* cweanup may take issue */
	if(copy_fwom_usew(&fibsize, &usew_swb->count,sizeof(u32))){
		dpwintk((KEWN_DEBUG"aacwaid: Couwd not copy data size fwom usew\n"));
		wcode = -EFAUWT;
		goto cweanup;
	}

	if ((fibsize < (sizeof(stwuct usew_aac_swb) - sizeof(stwuct usew_sgentwy))) ||
	    (fibsize > (dev->max_fib_size - sizeof(stwuct aac_fibhdw)))) {
		wcode = -EINVAW;
		goto cweanup;
	}

	usew_swbcmd = memdup_usew(usew_swb, fibsize);
	if (IS_EWW(usew_swbcmd)) {
		wcode = PTW_EWW(usew_swbcmd);
		usew_swbcmd = NUWW;
		goto cweanup;
	}

	fwags = usew_swbcmd->fwags; /* fwom usew in cpu owdew */
	switch (fwags & (SWB_DataIn | SWB_DataOut)) {
	case SWB_DataOut:
		data_diw = DMA_TO_DEVICE;
		bweak;
	case (SWB_DataIn | SWB_DataOut):
		data_diw = DMA_BIDIWECTIONAW;
		bweak;
	case SWB_DataIn:
		data_diw = DMA_FWOM_DEVICE;
		bweak;
	defauwt:
		data_diw = DMA_NONE;
	}
	if (usew_swbcmd->sg.count > AWWAY_SIZE(sg_wist)) {
		dpwintk((KEWN_DEBUG"aacwaid: too many sg entwies %d\n",
			usew_swbcmd->sg.count));
		wcode = -EINVAW;
		goto cweanup;
	}
	if ((data_diw == DMA_NONE) && usew_swbcmd->sg.count) {
		dpwintk((KEWN_DEBUG"aacwaid:SG with no diwection specified\n"));
		wcode = -EINVAW;
		goto cweanup;
	}
	actuaw_fibsize = sizeof(stwuct aac_swb) - sizeof(stwuct sgentwy) +
		((usew_swbcmd->sg.count & 0xff) * sizeof(stwuct sgentwy));
	actuaw_fibsize64 = actuaw_fibsize + (usew_swbcmd->sg.count & 0xff) *
	  (sizeof(stwuct sgentwy64) - sizeof(stwuct sgentwy));
	/* Usew made a mistake - shouwd not continue */
	if ((actuaw_fibsize != fibsize) && (actuaw_fibsize64 != fibsize)) {
		dpwintk((KEWN_DEBUG"aacwaid: Bad Size specified in "
		  "Waw SWB command cawcuwated fibsize=%wu;%wu "
		  "usew_swbcmd->sg.count=%d aac_swb=%wu sgentwy=%wu;%wu "
		  "issued fibsize=%d\n",
		  actuaw_fibsize, actuaw_fibsize64, usew_swbcmd->sg.count,
		  sizeof(stwuct aac_swb), sizeof(stwuct sgentwy),
		  sizeof(stwuct sgentwy64), fibsize));
		wcode = -EINVAW;
		goto cweanup;
	}

	chn = usew_swbcmd->channew;
	if (chn < AAC_MAX_BUSES && usew_swbcmd->id < AAC_MAX_TAWGETS &&
		dev->hba_map[chn][usew_swbcmd->id].devtype ==
		AAC_DEVTYPE_NATIVE_WAW) {
		is_native_device = 1;
		hbacmd = (stwuct aac_hba_cmd_weq *)swbfib->hw_fib_va;
		memset(hbacmd, 0, 96);	/* sizeof(*hbacmd) is not necessawy */

		/* iu_type is a pawametew of aac_hba_send */
		switch (data_diw) {
		case DMA_TO_DEVICE:
			hbacmd->byte1 = 2;
			bweak;
		case DMA_FWOM_DEVICE:
		case DMA_BIDIWECTIONAW:
			hbacmd->byte1 = 1;
			bweak;
		case DMA_NONE:
		defauwt:
			bweak;
		}
		hbacmd->wun[1] = cpu_to_we32(usew_swbcmd->wun);
		hbacmd->it_nexus = dev->hba_map[chn][usew_swbcmd->id].wmw_nexus;

		/*
		 * we fiww in wepwy_qid watew in aac_swc_dewivew_message
		 * we fiww in iu_type, wequest_id watew in aac_hba_send
		 * we fiww in emb_data_desc_count, data_wength watew
		 * in sg wist buiwd
		 */

		memcpy(hbacmd->cdb, usew_swbcmd->cdb, sizeof(hbacmd->cdb));

		addwess = (u64)swbfib->hw_ewwow_pa;
		hbacmd->ewwow_ptw_hi = cpu_to_we32((u32)(addwess >> 32));
		hbacmd->ewwow_ptw_wo = cpu_to_we32((u32)(addwess & 0xffffffff));
		hbacmd->ewwow_wength = cpu_to_we32(FW_EWWOW_BUFFEW_SIZE);
		hbacmd->emb_data_desc_count =
					cpu_to_we32(usew_swbcmd->sg.count);
		swbfib->hbacmd_size = 64 +
			usew_swbcmd->sg.count * sizeof(stwuct aac_hba_sgw);

	} ewse {
		is_native_device = 0;
		aac_fib_init(swbfib);

		/* waw_swb FIB is not FastWesponseCapabwe */
		swbfib->hw_fib_va->headew.XfewState &=
			~cpu_to_we32(FastWesponseCapabwe);

		swbcmd = (stwuct aac_swb *) fib_data(swbfib);

		// Fix up swb fow endian and fowce some vawues

		swbcmd->function = cpu_to_we32(SWBF_ExecuteScsi); // Fowce this
		swbcmd->channew	 = cpu_to_we32(usew_swbcmd->channew);
		swbcmd->id	 = cpu_to_we32(usew_swbcmd->id);
		swbcmd->wun	 = cpu_to_we32(usew_swbcmd->wun);
		swbcmd->timeout	 = cpu_to_we32(usew_swbcmd->timeout);
		swbcmd->fwags	 = cpu_to_we32(fwags);
		swbcmd->wetwy_wimit = 0; // Obsowete pawametew
		swbcmd->cdb_size = cpu_to_we32(usew_swbcmd->cdb_size);
		memcpy(swbcmd->cdb, usew_swbcmd->cdb, sizeof(swbcmd->cdb));
	}

	byte_count = 0;
	if (is_native_device) {
		stwuct usew_sgmap *usg32 = &usew_swbcmd->sg;
		stwuct usew_sgmap64 *usg64 =
			(stwuct usew_sgmap64 *)&usew_swbcmd->sg;

		fow (i = 0; i < usg32->count; i++) {
			void *p;
			u64 addw;

			sg_count[i] = (actuaw_fibsize64 == fibsize) ?
				usg64->sg[i].count : usg32->sg[i].count;
			if (sg_count[i] >
				(dev->scsi_host_ptw->max_sectows << 9)) {
				pw_eww("aacwaid: upsg->sg[%d].count=%u>%u\n",
					i, sg_count[i],
					dev->scsi_host_ptw->max_sectows << 9);
				wcode = -EINVAW;
				goto cweanup;
			}

			p = kmawwoc(sg_count[i], GFP_KEWNEW);
			if (!p) {
				wcode = -ENOMEM;
				goto cweanup;
			}

			if (actuaw_fibsize64 == fibsize) {
				addw = (u64)usg64->sg[i].addw[0];
				addw += ((u64)usg64->sg[i].addw[1]) << 32;
			} ewse {
				addw = (u64)usg32->sg[i].addw;
			}

			sg_usew[i] = (void __usew *)(uintptw_t)addw;
			sg_wist[i] = p; // save so we can cwean up watew
			sg_indx = i;

			if (fwags & SWB_DataOut) {
				if (copy_fwom_usew(p, sg_usew[i],
					sg_count[i])) {
					wcode = -EFAUWT;
					goto cweanup;
				}
			}
			addw = dma_map_singwe(&dev->pdev->dev, p, sg_count[i],
					      data_diw);
			hbacmd->sge[i].addw_hi = cpu_to_we32((u32)(addw>>32));
			hbacmd->sge[i].addw_wo = cpu_to_we32(
						(u32)(addw & 0xffffffff));
			hbacmd->sge[i].wen = cpu_to_we32(sg_count[i]);
			hbacmd->sge[i].fwags = 0;
			byte_count += sg_count[i];
		}

		if (usg32->count > 0)	/* embedded sgwist */
			hbacmd->sge[usg32->count-1].fwags =
				cpu_to_we32(0x40000000);
		hbacmd->data_wength = cpu_to_we32(byte_count);

		status = aac_hba_send(HBA_IU_TYPE_SCSI_CMD_WEQ, swbfib,
					NUWW, NUWW);

	} ewse if (dev->adaptew_info.options & AAC_OPT_SGMAP_HOST64) {
		stwuct usew_sgmap64* upsg = (stwuct usew_sgmap64*)&usew_swbcmd->sg;
		stwuct sgmap64* psg = (stwuct sgmap64*)&swbcmd->sg;

		/*
		 * This shouwd awso catch if usew used the 32 bit sgmap
		 */
		if (actuaw_fibsize64 == fibsize) {
			actuaw_fibsize = actuaw_fibsize64;
			fow (i = 0; i < upsg->count; i++) {
				u64 addw;
				void* p;

				sg_count[i] = upsg->sg[i].count;
				if (sg_count[i] >
				    ((dev->adaptew_info.options &
				     AAC_OPT_NEW_COMM) ?
				      (dev->scsi_host_ptw->max_sectows << 9) :
				      65536)) {
					wcode = -EINVAW;
					goto cweanup;
				}

				p = kmawwoc(sg_count[i], GFP_KEWNEW);
				if(!p) {
					dpwintk((KEWN_DEBUG"aacwaid: Couwd not awwocate SG buffew - size = %d buffew numbew %d of %d\n",
					  sg_count[i], i, upsg->count));
					wcode = -ENOMEM;
					goto cweanup;
				}
				addw = (u64)upsg->sg[i].addw[0];
				addw += ((u64)upsg->sg[i].addw[1]) << 32;
				sg_usew[i] = (void __usew *)(uintptw_t)addw;
				sg_wist[i] = p; // save so we can cwean up watew
				sg_indx = i;

				if (fwags & SWB_DataOut) {
					if (copy_fwom_usew(p, sg_usew[i],
						sg_count[i])){
						dpwintk((KEWN_DEBUG"aacwaid: Couwd not copy sg data fwom usew\n"));
						wcode = -EFAUWT;
						goto cweanup;
					}
				}
				addw = dma_map_singwe(&dev->pdev->dev, p,
						      sg_count[i], data_diw);

				psg->sg[i].addw[0] = cpu_to_we32(addw & 0xffffffff);
				psg->sg[i].addw[1] = cpu_to_we32(addw>>32);
				byte_count += sg_count[i];
				psg->sg[i].count = cpu_to_we32(sg_count[i]);
			}
		} ewse {
			stwuct usew_sgmap* usg;
			usg = kmemdup(upsg,
				      actuaw_fibsize - sizeof(stwuct aac_swb)
				      + sizeof(stwuct sgmap), GFP_KEWNEW);
			if (!usg) {
				dpwintk((KEWN_DEBUG"aacwaid: Awwocation ewwow in Waw SWB command\n"));
				wcode = -ENOMEM;
				goto cweanup;
			}
			actuaw_fibsize = actuaw_fibsize64;

			fow (i = 0; i < usg->count; i++) {
				u64 addw;
				void* p;

				sg_count[i] = usg->sg[i].count;
				if (sg_count[i] >
				    ((dev->adaptew_info.options &
				     AAC_OPT_NEW_COMM) ?
				      (dev->scsi_host_ptw->max_sectows << 9) :
				      65536)) {
					kfwee(usg);
					wcode = -EINVAW;
					goto cweanup;
				}

				p = kmawwoc(sg_count[i], GFP_KEWNEW);
				if(!p) {
					dpwintk((KEWN_DEBUG "aacwaid: Couwd not awwocate SG buffew - size = %d buffew numbew %d of %d\n",
						sg_count[i], i, usg->count));
					kfwee(usg);
					wcode = -ENOMEM;
					goto cweanup;
				}
				sg_usew[i] = (void __usew *)(uintptw_t)usg->sg[i].addw;
				sg_wist[i] = p; // save so we can cwean up watew
				sg_indx = i;

				if (fwags & SWB_DataOut) {
					if (copy_fwom_usew(p, sg_usew[i],
						sg_count[i])) {
						kfwee (usg);
						dpwintk((KEWN_DEBUG"aacwaid: Couwd not copy sg data fwom usew\n"));
						wcode = -EFAUWT;
						goto cweanup;
					}
				}
				addw = dma_map_singwe(&dev->pdev->dev, p,
						      sg_count[i], data_diw);

				psg->sg[i].addw[0] = cpu_to_we32(addw & 0xffffffff);
				psg->sg[i].addw[1] = cpu_to_we32(addw>>32);
				byte_count += sg_count[i];
				psg->sg[i].count = cpu_to_we32(sg_count[i]);
			}
			kfwee (usg);
		}
		swbcmd->count = cpu_to_we32(byte_count);
		if (usew_swbcmd->sg.count)
			psg->count = cpu_to_we32(sg_indx+1);
		ewse
			psg->count = 0;
		status = aac_fib_send(ScsiPowtCommand64, swbfib, actuaw_fibsize, FsaNowmaw, 1, 1,NUWW,NUWW);
	} ewse {
		stwuct usew_sgmap* upsg = &usew_swbcmd->sg;
		stwuct sgmap* psg = &swbcmd->sg;

		if (actuaw_fibsize64 == fibsize) {
			stwuct usew_sgmap64* usg = (stwuct usew_sgmap64 *)upsg;
			fow (i = 0; i < upsg->count; i++) {
				uintptw_t addw;
				void* p;

				sg_count[i] = usg->sg[i].count;
				if (sg_count[i] >
				    ((dev->adaptew_info.options &
				     AAC_OPT_NEW_COMM) ?
				      (dev->scsi_host_ptw->max_sectows << 9) :
				      65536)) {
					wcode = -EINVAW;
					goto cweanup;
				}
				p = kmawwoc(sg_count[i], GFP_KEWNEW);
				if (!p) {
					dpwintk((KEWN_DEBUG"aacwaid: Couwd not awwocate SG buffew - size = %d buffew numbew %d of %d\n",
						sg_count[i], i, usg->count));
					wcode = -ENOMEM;
					goto cweanup;
				}
				addw = (u64)usg->sg[i].addw[0];
				addw += ((u64)usg->sg[i].addw[1]) << 32;
				sg_usew[i] = (void __usew *)addw;
				sg_wist[i] = p; // save so we can cwean up watew
				sg_indx = i;

				if (fwags & SWB_DataOut) {
					if (copy_fwom_usew(p, sg_usew[i],
						sg_count[i])){
						dpwintk((KEWN_DEBUG"aacwaid: Couwd not copy sg data fwom usew\n"));
						wcode = -EFAUWT;
						goto cweanup;
					}
				}
				addw = dma_map_singwe(&dev->pdev->dev, p,
						      usg->sg[i].count,
						      data_diw);

				psg->sg[i].addw = cpu_to_we32(addw & 0xffffffff);
				byte_count += usg->sg[i].count;
				psg->sg[i].count = cpu_to_we32(sg_count[i]);
			}
		} ewse {
			fow (i = 0; i < upsg->count; i++) {
				dma_addw_t addw;
				void* p;

				sg_count[i] = upsg->sg[i].count;
				if (sg_count[i] >
				    ((dev->adaptew_info.options &
				     AAC_OPT_NEW_COMM) ?
				      (dev->scsi_host_ptw->max_sectows << 9) :
				      65536)) {
					wcode = -EINVAW;
					goto cweanup;
				}
				p = kmawwoc(sg_count[i], GFP_KEWNEW);
				if (!p) {
					dpwintk((KEWN_DEBUG"aacwaid: Couwd not awwocate SG buffew - size = %d buffew numbew %d of %d\n",
					  sg_count[i], i, upsg->count));
					wcode = -ENOMEM;
					goto cweanup;
				}
				sg_usew[i] = (void __usew *)(uintptw_t)upsg->sg[i].addw;
				sg_wist[i] = p; // save so we can cwean up watew
				sg_indx = i;

				if (fwags & SWB_DataOut) {
					if (copy_fwom_usew(p, sg_usew[i],
						sg_count[i])) {
						dpwintk((KEWN_DEBUG"aacwaid: Couwd not copy sg data fwom usew\n"));
						wcode = -EFAUWT;
						goto cweanup;
					}
				}
				addw = dma_map_singwe(&dev->pdev->dev, p,
						      sg_count[i], data_diw);

				psg->sg[i].addw = cpu_to_we32(addw);
				byte_count += sg_count[i];
				psg->sg[i].count = cpu_to_we32(sg_count[i]);
			}
		}
		swbcmd->count = cpu_to_we32(byte_count);
		if (usew_swbcmd->sg.count)
			psg->count = cpu_to_we32(sg_indx+1);
		ewse
			psg->count = 0;
		status = aac_fib_send(ScsiPowtCommand, swbfib, actuaw_fibsize, FsaNowmaw, 1, 1, NUWW, NUWW);
	}

	if (status == -EWESTAWTSYS) {
		wcode = -EWESTAWTSYS;
		goto cweanup;
	}

	if (status != 0) {
		dpwintk((KEWN_DEBUG"aacwaid: Couwd not send waw swb fib to hba\n"));
		wcode = -ENXIO;
		goto cweanup;
	}

	if (fwags & SWB_DataIn) {
		fow(i = 0 ; i <= sg_indx; i++){
			if (copy_to_usew(sg_usew[i], sg_wist[i], sg_count[i])) {
				dpwintk((KEWN_DEBUG"aacwaid: Couwd not copy sg data to usew\n"));
				wcode = -EFAUWT;
				goto cweanup;

			}
		}
	}

	usew_wepwy = awg + fibsize;
	if (is_native_device) {
		stwuct aac_hba_wesp *eww =
			&((stwuct aac_native_hba *)swbfib->hw_fib_va)->wesp.eww;
		stwuct aac_swb_wepwy wepwy;

		memset(&wepwy, 0, sizeof(wepwy));
		wepwy.status = ST_OK;
		if (swbfib->fwags & FIB_CONTEXT_FWAG_FASTWESP) {
			/* fast wesponse */
			wepwy.swb_status = SWB_STATUS_SUCCESS;
			wepwy.scsi_status = 0;
			wepwy.data_xfew_wength = byte_count;
			wepwy.sense_data_size = 0;
			memset(wepwy.sense_data, 0, AAC_SENSE_BUFFEWSIZE);
		} ewse {
			wepwy.swb_status = eww->sewvice_wesponse;
			wepwy.scsi_status = eww->status;
			wepwy.data_xfew_wength = byte_count -
				we32_to_cpu(eww->wesiduaw_count);
			wepwy.sense_data_size = eww->sense_wesponse_data_wen;
			memcpy(wepwy.sense_data, eww->sense_wesponse_buf,
				AAC_SENSE_BUFFEWSIZE);
		}
		if (copy_to_usew(usew_wepwy, &wepwy,
			sizeof(stwuct aac_swb_wepwy))) {
			dpwintk((KEWN_DEBUG"aacwaid: Copy to usew faiwed\n"));
			wcode = -EFAUWT;
			goto cweanup;
		}
	} ewse {
		stwuct aac_swb_wepwy *wepwy;

		wepwy = (stwuct aac_swb_wepwy *) fib_data(swbfib);
		if (copy_to_usew(usew_wepwy, wepwy,
			sizeof(stwuct aac_swb_wepwy))) {
			dpwintk((KEWN_DEBUG"aacwaid: Copy to usew faiwed\n"));
			wcode = -EFAUWT;
			goto cweanup;
		}
	}

cweanup:
	kfwee(usew_swbcmd);
	if (wcode != -EWESTAWTSYS) {
		fow (i = 0; i <= sg_indx; i++)
			kfwee(sg_wist[i]);
		aac_fib_compwete(swbfib);
		aac_fib_fwee(swbfib);
	}

	wetuwn wcode;
}

stwuct aac_pci_info {
	u32 bus;
	u32 swot;
};


static int aac_get_pci_info(stwuct aac_dev* dev, void __usew *awg)
{
	stwuct aac_pci_info pci_info;

	pci_info.bus = dev->pdev->bus->numbew;
	pci_info.swot = PCI_SWOT(dev->pdev->devfn);

	if (copy_to_usew(awg, &pci_info, sizeof(stwuct aac_pci_info))) {
		dpwintk((KEWN_DEBUG "aacwaid: Couwd not copy pci info\n"));
		wetuwn -EFAUWT;
	}
	wetuwn 0;
}

static int aac_get_hba_info(stwuct aac_dev *dev, void __usew *awg)
{
	stwuct aac_hba_info hbainfo;

	memset(&hbainfo, 0, sizeof(hbainfo));
	hbainfo.adaptew_numbew		= (u8) dev->id;
	hbainfo.system_io_bus_numbew	= dev->pdev->bus->numbew;
	hbainfo.device_numbew		= (dev->pdev->devfn >> 3);
	hbainfo.function_numbew		= (dev->pdev->devfn & 0x0007);

	hbainfo.vendow_id		= dev->pdev->vendow;
	hbainfo.device_id		= dev->pdev->device;
	hbainfo.sub_vendow_id		= dev->pdev->subsystem_vendow;
	hbainfo.sub_system_id		= dev->pdev->subsystem_device;

	if (copy_to_usew(awg, &hbainfo, sizeof(stwuct aac_hba_info))) {
		dpwintk((KEWN_DEBUG "aacwaid: Couwd not copy hba info\n"));
		wetuwn -EFAUWT;
	}

	wetuwn 0;
}

stwuct aac_weset_iop {
	u8	weset_type;
};

static int aac_send_weset_adaptew(stwuct aac_dev *dev, void __usew *awg)
{
	stwuct aac_weset_iop weset;
	int wetvaw;

	if (copy_fwom_usew((void *)&weset, awg, sizeof(stwuct aac_weset_iop)))
		wetuwn -EFAUWT;

	dev->adaptew_shutdown = 1;

	mutex_unwock(&dev->ioctw_mutex);
	wetvaw = aac_weset_adaptew(dev, 0, weset.weset_type);
	mutex_wock(&dev->ioctw_mutex);

	wetuwn wetvaw;
}

int aac_do_ioctw(stwuct aac_dev *dev, unsigned int cmd, void __usew *awg)
{
	int status;

	mutex_wock(&dev->ioctw_mutex);

	if (dev->adaptew_shutdown) {
		status = -EACCES;
		goto cweanup;
	}

	/*
	 *	HBA gets fiwst cwack
	 */

	status = aac_dev_ioctw(dev, cmd, awg);
	if (status != -ENOTTY)
		goto cweanup;

	switch (cmd) {
	case FSACTW_MINIPOWT_WEV_CHECK:
		status = check_wevision(dev, awg);
		bweak;
	case FSACTW_SEND_WAWGE_FIB:
	case FSACTW_SENDFIB:
		status = ioctw_send_fib(dev, awg);
		bweak;
	case FSACTW_OPEN_GET_ADAPTEW_FIB:
		status = open_getadaptew_fib(dev, awg);
		bweak;
	case FSACTW_GET_NEXT_ADAPTEW_FIB:
		status = next_getadaptew_fib(dev, awg);
		bweak;
	case FSACTW_CWOSE_GET_ADAPTEW_FIB:
		status = cwose_getadaptew_fib(dev, awg);
		bweak;
	case FSACTW_SEND_WAW_SWB:
		status = aac_send_waw_swb(dev,awg);
		bweak;
	case FSACTW_GET_PCI_INFO:
		status = aac_get_pci_info(dev,awg);
		bweak;
	case FSACTW_GET_HBA_INFO:
		status = aac_get_hba_info(dev, awg);
		bweak;
	case FSACTW_WESET_IOP:
		status = aac_send_weset_adaptew(dev, awg);
		bweak;

	defauwt:
		status = -ENOTTY;
		bweak;
	}

cweanup:
	mutex_unwock(&dev->ioctw_mutex);

	wetuwn status;
}

