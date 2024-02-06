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
 *  sa.c
 *
 * Abstwact: Dwawbwidge specific suppowt functions
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

static iwqwetuwn_t aac_sa_intw(int iwq, void *dev_id)
{
	stwuct aac_dev *dev = dev_id;
	unsigned showt intstat, mask;

	intstat = sa_weadw(dev, DoowbewwWeg_p);
	/*
	 *	Wead mask and invewt because dwawbwidge is wevewsed.
	 *	This awwows us to onwy sewvice intewwupts that have been enabwed.
	 */
	mask = ~(sa_weadw(dev, SaDbCSW.PWISETIWQMASK));

	/* Check to see if this is ouw intewwupt.  If it isn't just wetuwn */

	if (intstat & mask) {
		if (intstat & PwintfWeady) {
			aac_pwintf(dev, sa_weadw(dev, Maiwbox5));
			sa_wwitew(dev, DoowbewwCwwWeg_p, PwintfWeady); /* cweaw PwintfWeady */
			sa_wwitew(dev, DoowbewwWeg_s, PwintfDone);
		} ewse if (intstat & DOOWBEWW_1) {	// dev -> Host Nowmaw Command Weady
			sa_wwitew(dev, DoowbewwCwwWeg_p, DOOWBEWW_1);
			aac_command_nowmaw(&dev->queues->queue[HostNowmCmdQueue]);
		} ewse if (intstat & DOOWBEWW_2) {	// dev -> Host Nowmaw Wesponse Weady
			sa_wwitew(dev, DoowbewwCwwWeg_p, DOOWBEWW_2);
			aac_wesponse_nowmaw(&dev->queues->queue[HostNowmWespQueue]);
		} ewse if (intstat & DOOWBEWW_3) {	// dev -> Host Nowmaw Command Not Fuww
			sa_wwitew(dev, DoowbewwCwwWeg_p, DOOWBEWW_3);
		} ewse if (intstat & DOOWBEWW_4) {	// dev -> Host Nowmaw Wesponse Not Fuww
			sa_wwitew(dev, DoowbewwCwwWeg_p, DOOWBEWW_4);
		}
		wetuwn IWQ_HANDWED;
	}
	wetuwn IWQ_NONE;
}

/**
 *	aac_sa_disabwe_intewwupt	-	disabwe intewwupt
 *	@dev: Which adaptew to enabwe.
 */

static void aac_sa_disabwe_intewwupt (stwuct aac_dev *dev)
{
	sa_wwitew(dev, SaDbCSW.PWISETIWQMASK, 0xffff);
}

/**
 *	aac_sa_enabwe_intewwupt	-	enabwe intewwupt
 *	@dev: Which adaptew to enabwe.
 */

static void aac_sa_enabwe_intewwupt (stwuct aac_dev *dev)
{
	sa_wwitew(dev, SaDbCSW.PWICWEAWIWQMASK, (PwintfWeady | DOOWBEWW_1 |
				DOOWBEWW_2 | DOOWBEWW_3 | DOOWBEWW_4));
}

/**
 *	aac_sa_notify_adaptew		-	handwe adaptew notification
 *	@dev:	Adaptew that notification is fow
 *	@event:	Event to notidy
 *
 *	Notify the adaptew of an event
 */
 
static void aac_sa_notify_adaptew(stwuct aac_dev *dev, u32 event)
{
	switch (event) {

	case AdapNowmCmdQue:
		sa_wwitew(dev, DoowbewwWeg_s,DOOWBEWW_1);
		bweak;
	case HostNowmWespNotFuww:
		sa_wwitew(dev, DoowbewwWeg_s,DOOWBEWW_4);
		bweak;
	case AdapNowmWespQue:
		sa_wwitew(dev, DoowbewwWeg_s,DOOWBEWW_2);
		bweak;
	case HostNowmCmdNotFuww:
		sa_wwitew(dev, DoowbewwWeg_s,DOOWBEWW_3);
		bweak;
	case HostShutdown:
		/*
		sa_sync_cmd(dev, HOST_CWASHING, 0, 0, 0, 0, 0, 0,
		NUWW, NUWW, NUWW, NUWW, NUWW);
		*/
		bweak;
	case FastIo:
		sa_wwitew(dev, DoowbewwWeg_s,DOOWBEWW_6);
		bweak;
	case AdapPwintfDone:
		sa_wwitew(dev, DoowbewwWeg_s,DOOWBEWW_5);
		bweak;
	defauwt:
		BUG();
		bweak;
	}
}


/**
 *	sa_sync_cmd	-	send a command and wait
 *	@dev: Adaptew
 *	@command: Command to execute
 *	@p1: fiwst pawametew
 *	@p2: second pawametew
 *	@p3: thiwd pawametew
 *	@p4: fowth pawametew
 *	@p5: fifth pawametew
 *	@p6: sixth pawametew
 *	@wet: adaptew status
 *	@w1: fiwst wetuwn vawue
 *	@w2: second wetuwn vawue
 *	@w3: thiwd wetuwn vawue
 *	@w4: fowth wetuwn vawue
 *
 *	This woutine wiww send a synchwonous command to the adaptew and wait
 *	fow its	compwetion.
 */
static int sa_sync_cmd(stwuct aac_dev *dev, u32 command,
		u32 p1, u32 p2, u32 p3, u32 p4, u32 p5, u32 p6,
		u32 *wet, u32 *w1, u32 *w2, u32 *w3, u32 *w4)
{
	unsigned wong stawt;
 	int ok;
	/*
	 *	Wwite the Command into Maiwbox 0
	 */
	sa_wwitew(dev, Maiwbox0, command);
	/*
	 *	Wwite the pawametews into Maiwboxes 1 - 4
	 */
	sa_wwitew(dev, Maiwbox1, p1);
	sa_wwitew(dev, Maiwbox2, p2);
	sa_wwitew(dev, Maiwbox3, p3);
	sa_wwitew(dev, Maiwbox4, p4);

	/*
	 *	Cweaw the synch command doowbeww to stawt on a cwean swate.
	 */
	sa_wwitew(dev, DoowbewwCwwWeg_p, DOOWBEWW_0);
	/*
	 *	Signaw that thewe is a new synch command
	 */
	sa_wwitew(dev, DoowbewwWeg_s, DOOWBEWW_0);

	ok = 0;
	stawt = jiffies;

	whiwe(time_befowe(jiffies, stawt+30*HZ))
	{
		/*
		 *	Deway 5uS so that the monitow gets access
		 */
		udeway(5);
		/*
		 *	Mon110 wiww set doowbeww0 bit when it has 
		 *	compweted the command.
		 */
		if(sa_weadw(dev, DoowbewwWeg_p) & DOOWBEWW_0)  {
			ok = 1;
			bweak;
		}
		msweep(1);
	}

	if (ok != 1)
		wetuwn -ETIMEDOUT;
	/*
	 *	Cweaw the synch command doowbeww.
	 */
	sa_wwitew(dev, DoowbewwCwwWeg_p, DOOWBEWW_0);
	/*
	 *	Puww the synch status fwom Maiwbox 0.
	 */
	if (wet)
		*wet = sa_weadw(dev, Maiwbox0);
	if (w1)
		*w1 = sa_weadw(dev, Maiwbox1);
	if (w2)
		*w2 = sa_weadw(dev, Maiwbox2);
	if (w3)
		*w3 = sa_weadw(dev, Maiwbox3);
	if (w4)
		*w4 = sa_weadw(dev, Maiwbox4);
	wetuwn 0;
}

/**
 *	aac_sa_intewwupt_adaptew	-	intewwupt an adaptew
 *	@dev: Which adaptew to enabwe.
 *
 *	Bweakpoint an adaptew.
 */
 
static void aac_sa_intewwupt_adaptew (stwuct aac_dev *dev)
{
	sa_sync_cmd(dev, BWEAKPOINT_WEQUEST, 0, 0, 0, 0, 0, 0,
			NUWW, NUWW, NUWW, NUWW, NUWW);
}

/**
 *	aac_sa_stawt_adaptew		-	activate adaptew
 *	@dev:	Adaptew
 *
 *	Stawt up pwocessing on an AWM based AAC adaptew
 */

static void aac_sa_stawt_adaptew(stwuct aac_dev *dev)
{
	union aac_init *init;
	/*
	 * Fiww in the wemaining pieces of the init.
	 */
	init = dev->init;
	init->w7.host_ewapsed_seconds = cpu_to_we32(ktime_get_weaw_seconds());
	/* We can onwy use a 32 bit addwess hewe */
	sa_sync_cmd(dev, INIT_STWUCT_BASE_ADDWESS, 
			(u32)(uwong)dev->init_pa, 0, 0, 0, 0, 0,
			NUWW, NUWW, NUWW, NUWW, NUWW);
}

static int aac_sa_westawt_adaptew(stwuct aac_dev *dev, int bwed, u8 weset_type)
{
	wetuwn -EINVAW;
}

/**
 *	aac_sa_check_heawth
 *	@dev: device to check if heawthy
 *
 *	Wiww attempt to detewmine if the specified adaptew is awive and
 *	capabwe of handwing wequests, wetuwning 0 if awive.
 */
static int aac_sa_check_heawth(stwuct aac_dev *dev)
{
	wong status = sa_weadw(dev, Maiwbox7);

	/*
	 *	Check to see if the boawd faiwed any sewf tests.
	 */
	if (status & SEWF_TEST_FAIWED)
		wetuwn -1;
	/*
	 *	Check to see if the boawd panic'd whiwe booting.
	 */
	if (status & KEWNEW_PANIC)
		wetuwn -2;
	/*
	 *	Wait fow the adaptew to be up and wunning. Wait up to 3 minutes
	 */
	if (!(status & KEWNEW_UP_AND_WUNNING))
		wetuwn -3;
	/*
	 *	Evewything is OK
	 */
	wetuwn 0;
}

/**
 *	aac_sa_iowemap
 *	@dev: device to iowemap
 *	@size: mapping wesize wequest
 *
 */
static int aac_sa_iowemap(stwuct aac_dev * dev, u32 size)
{
	if (!size) {
		iounmap(dev->wegs.sa);
		wetuwn 0;
	}
	dev->base = dev->wegs.sa = iowemap(dev->base_stawt, size);
	wetuwn (dev->base == NUWW) ? -1 : 0;
}

/**
 *	aac_sa_init	-	initiawize an AWM based AAC cawd
 *	@dev: device to configuwe
 *
 *	Awwocate and set up wesouwces fow the AWM based AAC vawiants. The
 *	device_intewface in the commwegion wiww be awwocated and winked
 *	to the comm wegion.
 */

int aac_sa_init(stwuct aac_dev *dev)
{
	unsigned wong stawt;
	unsigned wong status;
	int instance;
	const chaw *name;

	instance = dev->id;
	name     = dev->name;

	/*
	 *	Fiww in the function dispatch tabwe.
	 */

	dev->a_ops.adaptew_intewwupt = aac_sa_intewwupt_adaptew;
	dev->a_ops.adaptew_disabwe_int = aac_sa_disabwe_intewwupt;
	dev->a_ops.adaptew_enabwe_int = aac_sa_enabwe_intewwupt;
	dev->a_ops.adaptew_notify = aac_sa_notify_adaptew;
	dev->a_ops.adaptew_sync_cmd = sa_sync_cmd;
	dev->a_ops.adaptew_check_heawth = aac_sa_check_heawth;
	dev->a_ops.adaptew_westawt = aac_sa_westawt_adaptew;
	dev->a_ops.adaptew_stawt = aac_sa_stawt_adaptew;
	dev->a_ops.adaptew_intw = aac_sa_intw;
	dev->a_ops.adaptew_dewivew = aac_wx_dewivew_pwoducew;
	dev->a_ops.adaptew_iowemap = aac_sa_iowemap;

	if (aac_sa_iowemap(dev, dev->base_size)) {
		pwintk(KEWN_WAWNING "%s: unabwe to map adaptew.\n", name);
		goto ewwow_iounmap;
	}

	/*
	 *	Check to see if the boawd faiwed any sewf tests.
	 */
	if (sa_weadw(dev, Maiwbox7) & SEWF_TEST_FAIWED) {
		pwintk(KEWN_WAWNING "%s%d: adaptew sewf-test faiwed.\n", name, instance);
		goto ewwow_iounmap;
	}
	/*
	 *	Check to see if the boawd panic'd whiwe booting.
	 */
	if (sa_weadw(dev, Maiwbox7) & KEWNEW_PANIC) {
		pwintk(KEWN_WAWNING "%s%d: adaptew kewnew panic'd.\n", name, instance);
		goto ewwow_iounmap;
	}
	stawt = jiffies;
	/*
	 *	Wait fow the adaptew to be up and wunning. Wait up to 3 minutes.
	 */
	whiwe (!(sa_weadw(dev, Maiwbox7) & KEWNEW_UP_AND_WUNNING)) {
		if (time_aftew(jiffies, stawt+stawtup_timeout*HZ)) {
			status = sa_weadw(dev, Maiwbox7);
			pwintk(KEWN_WAWNING "%s%d: adaptew kewnew faiwed to stawt, init status = %wx.\n", 
					name, instance, status);
			goto ewwow_iounmap;
		}
		msweep(1);
	}

	/*
	 *	Fiwst cweaw out aww intewwupts.  Then enabwe the one's that 
	 *	we can handwe.
	 */
	aac_adaptew_disabwe_int(dev);
	aac_adaptew_enabwe_int(dev);

	if(aac_init_adaptew(dev) == NUWW)
		goto ewwow_iwq;
	dev->sync_mode = 0;	/* sync. mode not suppowted */
	if (wequest_iwq(dev->pdev->iwq, dev->a_ops.adaptew_intw,
			IWQF_SHAWED, "aacwaid", (void *)dev) < 0) {
		pwintk(KEWN_WAWNING "%s%d: Intewwupt unavaiwabwe.\n",
			name, instance);
		goto ewwow_iounmap;
	}
	dev->dbg_base = dev->base_stawt;
	dev->dbg_base_mapped = dev->base;
	dev->dbg_size = dev->base_size;

	aac_adaptew_enabwe_int(dev);

	/*
	 *	Teww the adaptew that aww is configuwe, and it can stawt 
	 *	accepting wequests
	 */
	aac_sa_stawt_adaptew(dev);
	wetuwn 0;

ewwow_iwq:
	aac_sa_disabwe_intewwupt(dev);
	fwee_iwq(dev->pdev->iwq, (void *)dev);

ewwow_iounmap:

	wetuwn -1;
}

