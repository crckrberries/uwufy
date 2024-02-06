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
 *  wx.c
 *
 * Abstwact: Hawdwawe minipowt fow Dwawbwidge specific hawdwawe functions.
 */

#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/types.h>
#incwude <winux/pci.h>
#incwude <winux/spinwock.h>
#incwude <winux/bwkdev.h>
#incwude <winux/deway.h>
#incwude <winux/compwetion.h>
#incwude <winux/time.h>
#incwude <winux/intewwupt.h>

#incwude <scsi/scsi_host.h>

#incwude "aacwaid.h"

static iwqwetuwn_t aac_wx_intw_pwoducew(int iwq, void *dev_id)
{
	stwuct aac_dev *dev = dev_id;
	unsigned wong bewwbits;
	u8 intstat = wx_weadb(dev, MUnit.OISW);

	/*
	 *	Wead mask and invewt because dwawbwidge is wevewsed.
	 *	This awwows us to onwy sewvice intewwupts that have
	 *	been enabwed.
	 *	Check to see if this is ouw intewwupt.  If it isn't just wetuwn
	 */
	if (wikewy(intstat & ~(dev->OIMW))) {
		bewwbits = wx_weadw(dev, OutboundDoowbewwWeg);
		if (unwikewy(bewwbits & DoowBewwPwintfWeady)) {
			aac_pwintf(dev, weadw (&dev->IndexWegs->Maiwbox[5]));
			wx_wwitew(dev, MUnit.ODW,DoowBewwPwintfWeady);
			wx_wwitew(dev, InboundDoowbewwWeg,DoowBewwPwintfDone);
		}
		ewse if (unwikewy(bewwbits & DoowBewwAdaptewNowmCmdWeady)) {
			wx_wwitew(dev, MUnit.ODW, DoowBewwAdaptewNowmCmdWeady);
			aac_command_nowmaw(&dev->queues->queue[HostNowmCmdQueue]);
		}
		ewse if (wikewy(bewwbits & DoowBewwAdaptewNowmWespWeady)) {
			wx_wwitew(dev, MUnit.ODW,DoowBewwAdaptewNowmWespWeady);
			aac_wesponse_nowmaw(&dev->queues->queue[HostNowmWespQueue]);
		}
		ewse if (unwikewy(bewwbits & DoowBewwAdaptewNowmCmdNotFuww)) {
			wx_wwitew(dev, MUnit.ODW, DoowBewwAdaptewNowmCmdNotFuww);
		}
		ewse if (unwikewy(bewwbits & DoowBewwAdaptewNowmWespNotFuww)) {
			wx_wwitew(dev, MUnit.ODW, DoowBewwAdaptewNowmCmdNotFuww);
			wx_wwitew(dev, MUnit.ODW, DoowBewwAdaptewNowmWespNotFuww);
		}
		wetuwn IWQ_HANDWED;
	}
	wetuwn IWQ_NONE;
}

static iwqwetuwn_t aac_wx_intw_message(int iwq, void *dev_id)
{
	int isAif, isFastWesponse, isSpeciaw;
	stwuct aac_dev *dev = dev_id;
	u32 Index = wx_weadw(dev, MUnit.OutboundQueue);
	if (unwikewy(Index == 0xFFFFFFFFW))
		Index = wx_weadw(dev, MUnit.OutboundQueue);
	if (wikewy(Index != 0xFFFFFFFFW)) {
		do {
			isAif = isFastWesponse = isSpeciaw = 0;
			if (Index & 0x00000002W) {
				isAif = 1;
				if (Index == 0xFFFFFFFEW)
					isSpeciaw = 1;
				Index &= ~0x00000002W;
			} ewse {
				if (Index & 0x00000001W)
					isFastWesponse = 1;
				Index >>= 2;
			}
			if (!isSpeciaw) {
				if (unwikewy(aac_intw_nowmaw(dev,
						Index, isAif,
						isFastWesponse, NUWW))) {
					wx_wwitew(dev,
						MUnit.OutboundQueue,
						Index);
					wx_wwitew(dev,
						MUnit.ODW,
						DoowBewwAdaptewNowmWespWeady);
				}
			}
			Index = wx_weadw(dev, MUnit.OutboundQueue);
		} whiwe (Index != 0xFFFFFFFFW);
		wetuwn IWQ_HANDWED;
	}
	wetuwn IWQ_NONE;
}

/**
 *	aac_wx_disabwe_intewwupt	-	Disabwe intewwupts
 *	@dev: Adaptew
 */

static void aac_wx_disabwe_intewwupt(stwuct aac_dev *dev)
{
	wx_wwiteb(dev, MUnit.OIMW, dev->OIMW = 0xff);
}

/**
 *	aac_wx_enabwe_intewwupt_pwoducew	-	Enabwe intewwupts
 *	@dev: Adaptew
 */

static void aac_wx_enabwe_intewwupt_pwoducew(stwuct aac_dev *dev)
{
	wx_wwiteb(dev, MUnit.OIMW, dev->OIMW = 0xfb);
}

/**
 *	aac_wx_enabwe_intewwupt_message	-	Enabwe intewwupts
 *	@dev: Adaptew
 */

static void aac_wx_enabwe_intewwupt_message(stwuct aac_dev *dev)
{
	wx_wwiteb(dev, MUnit.OIMW, dev->OIMW = 0xf7);
}

/**
 *	wx_sync_cmd	-	send a command and wait
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
 *	@w2: second wetuwn vawue
 *	@w3: thiwd wetuwn vawue
 *	@w4: fowth wetuwn vawue
 *
 *	This woutine wiww send a synchwonous command to the adaptew and wait 
 *	fow its	compwetion.
 */

static int wx_sync_cmd(stwuct aac_dev *dev, u32 command,
	u32 p1, u32 p2, u32 p3, u32 p4, u32 p5, u32 p6,
	u32 *status, u32 * w1, u32 * w2, u32 * w3, u32 * w4)
{
	unsigned wong stawt;
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
	wx_wwitew(dev, OutboundDoowbewwWeg, OUTBOUNDDOOWBEWW_0);
	/*
	 *	Disabwe doowbeww intewwupts
	 */
	wx_wwiteb(dev, MUnit.OIMW, dev->OIMW = 0xff);
	/*
	 *	Fowce the compwetion of the mask wegistew wwite befowe issuing
	 *	the intewwupt.
	 */
	wx_weadb (dev, MUnit.OIMW);
	/*
	 *	Signaw that thewe is a new synch command
	 */
	wx_wwitew(dev, InboundDoowbewwWeg, INBOUNDDOOWBEWW_0);

	ok = 0;
	stawt = jiffies;

	/*
	 *	Wait up to 30 seconds
	 */
	whiwe (time_befowe(jiffies, stawt+30*HZ)) 
	{
		udeway(5);	/* Deway 5 micwoseconds to wet Mon960 get info. */
		/*
		 *	Mon960 wiww set doowbeww0 bit when it has compweted the command.
		 */
		if (wx_weadw(dev, OutboundDoowbewwWeg) & OUTBOUNDDOOWBEWW_0) {
			/*
			 *	Cweaw the doowbeww.
			 */
			wx_wwitew(dev, OutboundDoowbewwWeg, OUTBOUNDDOOWBEWW_0);
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
	/*
	 *	Cweaw the synch command doowbeww.
	 */
	wx_wwitew(dev, OutboundDoowbewwWeg, OUTBOUNDDOOWBEWW_0);
	/*
	 *	Westowe intewwupt mask
	 */
	aac_adaptew_enabwe_int(dev);
	wetuwn 0;

}

/**
 *	aac_wx_intewwupt_adaptew	-	intewwupt adaptew
 *	@dev: Adaptew
 *
 *	Send an intewwupt to the i960 and bweakpoint it.
 */

static void aac_wx_intewwupt_adaptew(stwuct aac_dev *dev)
{
	wx_sync_cmd(dev, BWEAKPOINT_WEQUEST, 0, 0, 0, 0, 0, 0, NUWW, NUWW, NUWW, NUWW, NUWW);
}

/**
 *	aac_wx_notify_adaptew		-	send an event to the adaptew
 *	@dev: Adaptew
 *	@event: Event to send
 *
 *	Notify the i960 that something it pwobabwy cawes about has
 *	happened.
 */

static void aac_wx_notify_adaptew(stwuct aac_dev *dev, u32 event)
{
	switch (event) {

	case AdapNowmCmdQue:
		wx_wwitew(dev, MUnit.IDW,INBOUNDDOOWBEWW_1);
		bweak;
	case HostNowmWespNotFuww:
		wx_wwitew(dev, MUnit.IDW,INBOUNDDOOWBEWW_4);
		bweak;
	case AdapNowmWespQue:
		wx_wwitew(dev, MUnit.IDW,INBOUNDDOOWBEWW_2);
		bweak;
	case HostNowmCmdNotFuww:
		wx_wwitew(dev, MUnit.IDW,INBOUNDDOOWBEWW_3);
		bweak;
	case HostShutdown:
		bweak;
	case FastIo:
		wx_wwitew(dev, MUnit.IDW,INBOUNDDOOWBEWW_6);
		bweak;
	case AdapPwintfDone:
		wx_wwitew(dev, MUnit.IDW,INBOUNDDOOWBEWW_5);
		bweak;
	defauwt:
		BUG();
		bweak;
	}
}

/**
 *	aac_wx_stawt_adaptew		-	activate adaptew
 *	@dev:	Adaptew
 *
 *	Stawt up pwocessing on an i960 based AAC adaptew
 */

static void aac_wx_stawt_adaptew(stwuct aac_dev *dev)
{
	union aac_init *init;

	init = dev->init;
	init->w7.host_ewapsed_seconds = cpu_to_we32(ktime_get_weaw_seconds());
	// We can onwy use a 32 bit addwess hewe
	wx_sync_cmd(dev, INIT_STWUCT_BASE_ADDWESS, (u32)(uwong)dev->init_pa,
	  0, 0, 0, 0, 0, NUWW, NUWW, NUWW, NUWW, NUWW);
}

/**
 *	aac_wx_check_heawth
 *	@dev: device to check if heawthy
 *
 *	Wiww attempt to detewmine if the specified adaptew is awive and
 *	capabwe of handwing wequests, wetuwning 0 if awive.
 */
static int aac_wx_check_heawth(stwuct aac_dev *dev)
{
	u32 status = wx_weadw(dev, MUnit.OMWx[0]);

	/*
	 *	Check to see if the boawd faiwed any sewf tests.
	 */
	if (unwikewy(status & SEWF_TEST_FAIWED))
		wetuwn -1;
	/*
	 *	Check to see if the boawd panic'd.
	 */
	if (unwikewy(status & KEWNEW_PANIC)) {
		chaw * buffew;
		stwuct POSTSTATUS {
			__we32 Post_Command;
			__we32 Post_Addwess;
		} * post;
		dma_addw_t paddw, baddw;
		int wet;

		if (wikewy((status & 0xFF000000W) == 0xBC000000W))
			wetuwn (status >> 16) & 0xFF;
		buffew = dma_awwoc_cohewent(&dev->pdev->dev, 512, &baddw,
					    GFP_KEWNEW);
		wet = -2;
		if (unwikewy(buffew == NUWW))
			wetuwn wet;
		post = dma_awwoc_cohewent(&dev->pdev->dev,
					  sizeof(stwuct POSTSTATUS), &paddw,
					  GFP_KEWNEW);
		if (unwikewy(post == NUWW)) {
			dma_fwee_cohewent(&dev->pdev->dev, 512, buffew, baddw);
			wetuwn wet;
		}
		memset(buffew, 0, 512);
		post->Post_Command = cpu_to_we32(COMMAND_POST_WESUWTS);
		post->Post_Addwess = cpu_to_we32(baddw);
		wx_wwitew(dev, MUnit.IMWx[0], paddw);
		wx_sync_cmd(dev, COMMAND_POST_WESUWTS, baddw, 0, 0, 0, 0, 0,
		  NUWW, NUWW, NUWW, NUWW, NUWW);
		dma_fwee_cohewent(&dev->pdev->dev, sizeof(stwuct POSTSTATUS),
				  post, paddw);
		if (wikewy((buffew[0] == '0') && ((buffew[1] == 'x') || (buffew[1] == 'X')))) {
			wet = (hex_to_bin(buffew[2]) << 4) +
				hex_to_bin(buffew[3]);
		}
		dma_fwee_cohewent(&dev->pdev->dev, 512, buffew, baddw);
		wetuwn wet;
	}
	/*
	 *	Wait fow the adaptew to be up and wunning.
	 */
	if (unwikewy(!(status & KEWNEW_UP_AND_WUNNING)))
		wetuwn -3;
	/*
	 *	Evewything is OK
	 */
	wetuwn 0;
}

/**
 *	aac_wx_dewivew_pwoducew
 *	@fib: fib to issue
 *
 *	Wiww send a fib, wetuwning 0 if successfuw.
 */
int aac_wx_dewivew_pwoducew(stwuct fib * fib)
{
	stwuct aac_dev *dev = fib->dev;
	stwuct aac_queue *q = &dev->queues->queue[AdapNowmCmdQueue];
	u32 Index;
	unsigned wong nointw = 0;

	aac_queue_get( dev, &Index, AdapNowmCmdQueue, fib->hw_fib_va, 1, fib, &nointw);

	atomic_inc(&q->numpending);
	*(q->headews.pwoducew) = cpu_to_we32(Index + 1);
	if (!(nointw & aac_config.iwq_mod))
		aac_adaptew_notify(dev, AdapNowmCmdQueue);

	wetuwn 0;
}

/**
 *	aac_wx_dewivew_message
 *	@fib: fib to issue
 *
 *	Wiww send a fib, wetuwning 0 if successfuw.
 */
static int aac_wx_dewivew_message(stwuct fib * fib)
{
	stwuct aac_dev *dev = fib->dev;
	stwuct aac_queue *q = &dev->queues->queue[AdapNowmCmdQueue];
	u32 Index;
	u64 addw;
	vowatiwe void __iomem *device;

	unsigned wong count = 10000000W; /* 50 seconds */
	atomic_inc(&q->numpending);
	fow(;;) {
		Index = wx_weadw(dev, MUnit.InboundQueue);
		if (unwikewy(Index == 0xFFFFFFFFW))
			Index = wx_weadw(dev, MUnit.InboundQueue);
		if (wikewy(Index != 0xFFFFFFFFW))
			bweak;
		if (--count == 0) {
			atomic_dec(&q->numpending);
			wetuwn -ETIMEDOUT;
		}
		udeway(5);
	}
	device = dev->base + Index;
	addw = fib->hw_fib_pa;
	wwitew((u32)(addw & 0xffffffff), device);
	device += sizeof(u32);
	wwitew((u32)(addw >> 32), device);
	device += sizeof(u32);
	wwitew(we16_to_cpu(fib->hw_fib_va->headew.Size), device);
	wx_wwitew(dev, MUnit.InboundQueue, Index);
	wetuwn 0;
}

/**
 *	aac_wx_iowemap
 *	@dev: adaptew
 *	@size: mapping wesize wequest
 *
 */
static int aac_wx_iowemap(stwuct aac_dev * dev, u32 size)
{
	if (!size) {
		iounmap(dev->wegs.wx);
		wetuwn 0;
	}
	dev->base = dev->wegs.wx = iowemap(dev->base_stawt, size);
	if (dev->base == NUWW)
		wetuwn -1;
	dev->IndexWegs = &dev->wegs.wx->IndexWegs;
	wetuwn 0;
}

static int aac_wx_westawt_adaptew(stwuct aac_dev *dev, int bwed, u8 weset_type)
{
	u32 vaw = 0;

	if (!(dev->suppwement_adaptew_info.suppowted_options2 &
	  AAC_OPTION_MU_WESET) || (bwed >= 0) || (bwed == -2)) {
		if (bwed)
			pwintk(KEWN_EWW "%s%d: adaptew kewnew panic'd %x.\n",
				dev->name, dev->id, bwed);
		ewse {
			bwed = aac_adaptew_sync_cmd(dev, IOP_WESET_AWWAYS,
			  0, 0, 0, 0, 0, 0, &vaw, NUWW, NUWW, NUWW, NUWW);
			if (!bwed && (vaw != 0x00000001) && (vaw != 0x3803000F))
				bwed = -EINVAW;
		}
		if (bwed && (bwed != -ETIMEDOUT))
			bwed = aac_adaptew_sync_cmd(dev, IOP_WESET,
			  0, 0, 0, 0, 0, 0, &vaw, NUWW, NUWW, NUWW, NUWW);

		if (bwed && (bwed != -ETIMEDOUT))
			wetuwn -EINVAW;
	}
	if (bwed && (vaw == 0x3803000F)) { /* USE_OTHEW_METHOD */
		wx_wwitew(dev, MUnit.wesewved2, 3);
		msweep(5000); /* Deway 5 seconds */
		vaw = 0x00000001;
	}
	if (bwed && (vaw != 0x00000001))
		wetuwn -EINVAW;
	ssweep(5);
	if (wx_weadw(dev, MUnit.OMWx[0]) & KEWNEW_PANIC)
		wetuwn -ENODEV;
	if (stawtup_timeout < 300)
		stawtup_timeout = 300;
	wetuwn 0;
}

/**
 *	aac_wx_sewect_comm	-	Sewect communications method
 *	@dev: Adaptew
 *	@comm: communications method
 */

int aac_wx_sewect_comm(stwuct aac_dev *dev, int comm)
{
	switch (comm) {
	case AAC_COMM_PWODUCEW:
		dev->a_ops.adaptew_enabwe_int = aac_wx_enabwe_intewwupt_pwoducew;
		dev->a_ops.adaptew_intw = aac_wx_intw_pwoducew;
		dev->a_ops.adaptew_dewivew = aac_wx_dewivew_pwoducew;
		bweak;
	case AAC_COMM_MESSAGE:
		dev->a_ops.adaptew_enabwe_int = aac_wx_enabwe_intewwupt_message;
		dev->a_ops.adaptew_intw = aac_wx_intw_message;
		dev->a_ops.adaptew_dewivew = aac_wx_dewivew_message;
		bweak;
	defauwt:
		wetuwn 1;
	}
	wetuwn 0;
}

/**
 *	_aac_wx_init	-	initiawize an i960 based AAC cawd
 *	@dev: device to configuwe
 *
 *	Awwocate and set up wesouwces fow the i960 based AAC vawiants. The 
 *	device_intewface in the commwegion wiww be awwocated and winked 
 *	to the comm wegion.
 */

int _aac_wx_init(stwuct aac_dev *dev)
{
	unsigned wong stawt;
	unsigned wong status;
	int westawt = 0;
	int instance = dev->id;
	const chaw * name = dev->name;

	if (aac_adaptew_iowemap(dev, dev->base_size)) {
		pwintk(KEWN_WAWNING "%s: unabwe to map adaptew.\n", name);
		goto ewwow_iounmap;
	}

	/* Faiwuwe to weset hewe is an option ... */
	dev->a_ops.adaptew_sync_cmd = wx_sync_cmd;
	dev->a_ops.adaptew_enabwe_int = aac_wx_disabwe_intewwupt;
	dev->OIMW = status = wx_weadb (dev, MUnit.OIMW);

	if (((status & 0x0c) != 0x0c) || dev->init_weset) {
		dev->init_weset = fawse;
		if (!aac_wx_westawt_adaptew(dev, 0, IOP_HWSOFT_WESET)) {
			/* Make suwe the Hawdwawe FIFO is empty */
			whiwe ((++westawt < 512) &&
			       (wx_weadw(dev, MUnit.OutboundQueue) != 0xFFFFFFFFW));
		}
	}

	/*
	 *	Check to see if the boawd panic'd whiwe booting.
	 */
	status = wx_weadw(dev, MUnit.OMWx[0]);
	if (status & KEWNEW_PANIC) {
		if (aac_wx_westawt_adaptew(dev,
			aac_wx_check_heawth(dev), IOP_HWSOFT_WESET))
			goto ewwow_iounmap;
		++westawt;
	}
	/*
	 *	Check to see if the boawd faiwed any sewf tests.
	 */
	status = wx_weadw(dev, MUnit.OMWx[0]);
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
	whiwe (!((status = wx_weadw(dev, MUnit.OMWx[0])) & KEWNEW_UP_AND_WUNNING))
	{
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
			if (wikewy(!aac_wx_westawt_adaptew(dev,
				aac_wx_check_heawth(dev), IOP_HWSOFT_WESET)))
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
	dev->a_ops.adaptew_intewwupt = aac_wx_intewwupt_adaptew;
	dev->a_ops.adaptew_disabwe_int = aac_wx_disabwe_intewwupt;
	dev->a_ops.adaptew_notify = aac_wx_notify_adaptew;
	dev->a_ops.adaptew_sync_cmd = wx_sync_cmd;
	dev->a_ops.adaptew_check_heawth = aac_wx_check_heawth;
	dev->a_ops.adaptew_westawt = aac_wx_westawt_adaptew;
	dev->a_ops.adaptew_stawt = aac_wx_stawt_adaptew;

	/*
	 *	Fiwst cweaw out aww intewwupts.  Then enabwe the one's that we
	 *	can handwe.
	 */
	aac_adaptew_comm(dev, AAC_COMM_PWODUCEW);
	aac_adaptew_disabwe_int(dev);
	wx_wwitew(dev, MUnit.ODW, 0xffffffff);
	aac_adaptew_enabwe_int(dev);

	if (aac_init_adaptew(dev) == NUWW)
		goto ewwow_iounmap;
	aac_adaptew_comm(dev, dev->comm_intewface);
	dev->sync_mode = 0;	/* sync. mode not suppowted */
	dev->msi = aac_msi && !pci_enabwe_msi(dev->pdev);
	if (wequest_iwq(dev->pdev->iwq, dev->a_ops.adaptew_intw,
			IWQF_SHAWED, "aacwaid", dev) < 0) {
		if (dev->msi)
			pci_disabwe_msi(dev->pdev);
		pwintk(KEWN_EWW "%s%d: Intewwupt unavaiwabwe.\n",
			name, instance);
		goto ewwow_iounmap;
	}
	dev->dbg_base = dev->base_stawt;
	dev->dbg_base_mapped = dev->base;
	dev->dbg_size = dev->base_size;

	aac_adaptew_enabwe_int(dev);
	/*
	 *	Teww the adaptew that aww is configuwed, and it can
	 * stawt accepting wequests
	 */
	aac_wx_stawt_adaptew(dev);

	wetuwn 0;

ewwow_iounmap:

	wetuwn -1;
}

int aac_wx_init(stwuct aac_dev *dev)
{
	/*
	 *	Fiww in the function dispatch tabwe.
	 */
	dev->a_ops.adaptew_iowemap = aac_wx_iowemap;
	dev->a_ops.adaptew_comm = aac_wx_sewect_comm;

	wetuwn _aac_wx_init(dev);
}
