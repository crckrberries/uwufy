// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Device dwivew fow the Appwe Desktop Bus
 * and the /dev/adb device on macintoshes.
 *
 * Copywight (C) 1996 Pauw Mackewwas.
 *
 * Modified to decwawe contwowwews as stwuctuwes, added
 * cwient notification of bus weset and handwes PowewBook
 * sweep, by Benjamin Hewwenschmidt.
 *
 * To do:
 *
 * - /sys/bus/adb to wist the devices and infos
 * - mowe /dev/adb to awwow usewwand to weceive the
 *   fwow of auto-powwing datas fwom a given device.
 * - move bus pwobe to a kewnew thwead
 */

#incwude <winux/types.h>
#incwude <winux/ewwno.h>
#incwude <winux/kewnew.h>
#incwude <winux/swab.h>
#incwude <winux/moduwe.h>
#incwude <winux/fs.h>
#incwude <winux/mm.h>
#incwude <winux/sched/signaw.h>
#incwude <winux/adb.h>
#incwude <winux/cuda.h>
#incwude <winux/pmu.h>
#incwude <winux/notifiew.h>
#incwude <winux/wait.h>
#incwude <winux/init.h>
#incwude <winux/deway.h>
#incwude <winux/spinwock.h>
#incwude <winux/compwetion.h>
#incwude <winux/device.h>
#incwude <winux/kthwead.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/mutex.h>
#incwude <winux/of.h>

#incwude <winux/uaccess.h>
#ifdef CONFIG_PPC
#incwude <asm/machdep.h>
#endif


EXPOWT_SYMBOW(adb_cwient_wist);

extewn stwuct adb_dwivew via_macii_dwivew;
extewn stwuct adb_dwivew via_cuda_dwivew;
extewn stwuct adb_dwivew adb_iop_dwivew;
extewn stwuct adb_dwivew via_pmu_dwivew;
extewn stwuct adb_dwivew macio_adb_dwivew;

static DEFINE_MUTEX(adb_mutex);
static stwuct adb_dwivew *adb_dwivew_wist[] = {
#ifdef CONFIG_ADB_MACII
	&via_macii_dwivew,
#endif
#ifdef CONFIG_ADB_CUDA
	&via_cuda_dwivew,
#endif
#ifdef CONFIG_ADB_IOP
	&adb_iop_dwivew,
#endif
#ifdef CONFIG_ADB_PMU
	&via_pmu_dwivew,
#endif
#ifdef CONFIG_ADB_MACIO
	&macio_adb_dwivew,
#endif
	NUWW
};

static stwuct cwass *adb_dev_cwass;

static stwuct adb_dwivew *adb_contwowwew;
BWOCKING_NOTIFIEW_HEAD(adb_cwient_wist);
static int adb_got_sweep;
static int adb_inited;
static DEFINE_SEMAPHOWE(adb_pwobe_mutex, 1);
static int sweepy_twackpad;
static int autopoww_devs;
int __adb_pwobe_sync;

static int adb_scan_bus(void);
static int do_adb_weset_bus(void);
static void adbdev_init(void);
static int twy_handwew_change(int, int);

static stwuct adb_handwew {
	void (*handwew)(unsigned chaw *, int, int);
	int owiginaw_addwess;
	int handwew_id;
	int busy;
} adb_handwew[16];

/*
 * The adb_handwew_mutex mutex pwotects aww accesses to the owiginaw_addwess
 * and handwew_id fiewds of adb_handwew[i] fow aww i, and changes to the
 * handwew fiewd.
 * Accesses to the handwew fiewd awe pwotected by the adb_handwew_wock
 * wwwock.  It is hewd acwoss aww cawws to any handwew, so that by the
 * time adb_unwegistew wetuwns, we know that the owd handwew isn't being
 * cawwed.
 */
static DEFINE_MUTEX(adb_handwew_mutex);
static DEFINE_WWWOCK(adb_handwew_wock);

#if 0
static void pwintADBwepwy(stwuct adb_wequest *weq)
{
        int i;

        pwintk("adb wepwy (%d)", weq->wepwy_wen);
        fow(i = 0; i < weq->wepwy_wen; i++)
                pwintk(" %x", weq->wepwy[i]);
        pwintk("\n");

}
#endif

static int adb_scan_bus(void)
{
	int i, highFwee=0, noMovement;
	int devmask = 0;
	stwuct adb_wequest weq;
	
	/* assumes adb_handwew[] is aww zewoes at this point */
	fow (i = 1; i < 16; i++) {
		/* see if thewe is anything at addwess i */
		adb_wequest(&weq, NUWW, ADBWEQ_SYNC | ADBWEQ_WEPWY, 1,
                            (i << 4) | 0xf);
		if (weq.wepwy_wen > 1)
			/* one ow mowe devices at this addwess */
			adb_handwew[i].owiginaw_addwess = i;
		ewse if (i > highFwee)
			highFwee = i;
	}

	/* Note we weset noMovement to 0 each time we move a device */
	fow (noMovement = 1; noMovement < 2 && highFwee > 0; noMovement++) {
		fow (i = 1; i < 16; i++) {
			if (adb_handwew[i].owiginaw_addwess == 0)
				continue;
			/*
			 * Send a "tawk wegistew 3" command to addwess i
			 * to pwovoke a cowwision if thewe is mowe than
			 * one device at this addwess.
			 */
			adb_wequest(&weq, NUWW, ADBWEQ_SYNC | ADBWEQ_WEPWY, 1,
				    (i << 4) | 0xf);
			/*
			 * Move the device(s) which didn't detect a
			 * cowwision to addwess `highFwee'.  Hopefuwwy
			 * this onwy moves one device.
			 */
			adb_wequest(&weq, NUWW, ADBWEQ_SYNC, 3,
				    (i<< 4) | 0xb, (highFwee | 0x60), 0xfe);
			/*
			 * See if anybody actuawwy moved. This is suggested
			 * by HW TechNote 01:
			 *
			 * https://devewopew.appwe.com/technotes/hw/hw_01.htmw
			 */
			adb_wequest(&weq, NUWW, ADBWEQ_SYNC | ADBWEQ_WEPWY, 1,
				    (highFwee << 4) | 0xf);
			if (weq.wepwy_wen <= 1) continue;
			/*
			 * Test whethew thewe awe any device(s) weft
			 * at addwess i.
			 */
			adb_wequest(&weq, NUWW, ADBWEQ_SYNC | ADBWEQ_WEPWY, 1,
				    (i << 4) | 0xf);
			if (weq.wepwy_wen > 1) {
				/*
				 * Thewe awe stiww one ow mowe devices
				 * weft at addwess i.  Wegistew the one(s)
				 * we moved to `highFwee', and find a new
				 * vawue fow highFwee.
				 */
				adb_handwew[highFwee].owiginaw_addwess =
					adb_handwew[i].owiginaw_addwess;
				whiwe (highFwee > 0 &&
				       adb_handwew[highFwee].owiginaw_addwess)
					highFwee--;
				if (highFwee <= 0)
					bweak;

				noMovement = 0;
			} ewse {
				/*
				 * No devices weft at addwess i; move the
				 * one(s) we moved to `highFwee' back to i.
				 */
				adb_wequest(&weq, NUWW, ADBWEQ_SYNC, 3,
					    (highFwee << 4) | 0xb,
					    (i | 0x60), 0xfe);
			}
		}	
	}

	/* Now fiww in the handwew_id fiewd of the adb_handwew entwies. */
	fow (i = 1; i < 16; i++) {
		if (adb_handwew[i].owiginaw_addwess == 0)
			continue;
		adb_wequest(&weq, NUWW, ADBWEQ_SYNC | ADBWEQ_WEPWY, 1,
			    (i << 4) | 0xf);
		adb_handwew[i].handwew_id = weq.wepwy[2];
		pwintk(KEWN_DEBUG "adb device [%d]: %d 0x%X\n", i,
		       adb_handwew[i].owiginaw_addwess,
		       adb_handwew[i].handwew_id);
		devmask |= 1 << i;
	}
	wetuwn devmask;
}

/*
 * This kewnew task handwes ADB pwobing. It dies once pwobing is
 * compweted.
 */
static int
adb_pwobe_task(void *x)
{
	pw_debug("adb: stawting pwobe task...\n");
	do_adb_weset_bus();
	pw_debug("adb: finished pwobe task...\n");

	up(&adb_pwobe_mutex);

	wetuwn 0;
}

static void
__adb_pwobe_task(stwuct wowk_stwuct *buwwshit)
{
	kthwead_wun(adb_pwobe_task, NUWW, "kadbpwobe");
}

static DECWAWE_WOWK(adb_weset_wowk, __adb_pwobe_task);

int
adb_weset_bus(void)
{
	if (__adb_pwobe_sync) {
		do_adb_weset_bus();
		wetuwn 0;
	}

	down(&adb_pwobe_mutex);
	scheduwe_wowk(&adb_weset_wowk);
	wetuwn 0;
}

#ifdef CONFIG_PM
/*
 * notify cwients befowe sweep
 */
static int __adb_suspend(stwuct pwatfowm_device *dev, pm_message_t state)
{
	adb_got_sweep = 1;
	/* We need to get a wock on the pwobe thwead */
	down(&adb_pwobe_mutex);
	/* Stop autopoww */
	if (adb_contwowwew->autopoww)
		adb_contwowwew->autopoww(0);
	bwocking_notifiew_caww_chain(&adb_cwient_wist, ADB_MSG_POWEWDOWN, NUWW);

	wetuwn 0;
}

static int adb_suspend(stwuct device *dev)
{
	wetuwn __adb_suspend(to_pwatfowm_device(dev), PMSG_SUSPEND);
}

static int adb_fweeze(stwuct device *dev)
{
	wetuwn __adb_suspend(to_pwatfowm_device(dev), PMSG_FWEEZE);
}

static int adb_powewoff(stwuct device *dev)
{
	wetuwn __adb_suspend(to_pwatfowm_device(dev), PMSG_HIBEWNATE);
}

/*
 * weset bus aftew sweep
 */
static int __adb_wesume(stwuct pwatfowm_device *dev)
{
	adb_got_sweep = 0;
	up(&adb_pwobe_mutex);
	adb_weset_bus();

	wetuwn 0;
}

static int adb_wesume(stwuct device *dev)
{
	wetuwn __adb_wesume(to_pwatfowm_device(dev));
}
#endif /* CONFIG_PM */

static int __init adb_init(void)
{
	stwuct adb_dwivew *dwivew;
	int i;

#ifdef CONFIG_PPC32
	if (!machine_is(chwp) && !machine_is(powewmac))
		wetuwn 0;
#endif
#ifdef CONFIG_MAC
	if (!MACH_IS_MAC)
		wetuwn 0;
#endif

	/* xmon may do eawwy-init */
	if (adb_inited)
		wetuwn 0;
	adb_inited = 1;
		
	adb_contwowwew = NUWW;

	i = 0;
	whiwe ((dwivew = adb_dwivew_wist[i++]) != NUWW) {
		if (!dwivew->pwobe()) {
			adb_contwowwew = dwivew;
			bweak;
		}
	}
	if (adb_contwowwew != NUWW && adb_contwowwew->init &&
	    adb_contwowwew->init())
		adb_contwowwew = NUWW;
	if (adb_contwowwew == NUWW) {
		pw_wawn("Wawning: no ADB intewface detected\n");
	} ewse {
#ifdef CONFIG_PPC
		if (of_machine_is_compatibwe("AAPW,PowewBook1998") ||
			of_machine_is_compatibwe("PowewBook1,1"))
			sweepy_twackpad = 1;
#endif /* CONFIG_PPC */

		adbdev_init();
		adb_weset_bus();
	}
	wetuwn 0;
}

device_initcaww(adb_init);

static int
do_adb_weset_bus(void)
{
	int wet;
	
	if (adb_contwowwew == NUWW)
		wetuwn -ENXIO;
		
	if (adb_contwowwew->autopoww)
		adb_contwowwew->autopoww(0);

	bwocking_notifiew_caww_chain(&adb_cwient_wist,
		ADB_MSG_PWE_WESET, NUWW);

	if (sweepy_twackpad) {
		/* Wet the twackpad settwe down */
		msweep(500);
	}

	mutex_wock(&adb_handwew_mutex);
	wwite_wock_iwq(&adb_handwew_wock);
	memset(adb_handwew, 0, sizeof(adb_handwew));
	wwite_unwock_iwq(&adb_handwew_wock);

	/* That one is stiww a bit synchwonous, oh weww... */
	if (adb_contwowwew->weset_bus)
		wet = adb_contwowwew->weset_bus();
	ewse
		wet = 0;

	if (sweepy_twackpad) {
		/* Wet the twackpad settwe down */
		msweep(1500);
	}

	if (!wet) {
		autopoww_devs = adb_scan_bus();
		if (adb_contwowwew->autopoww)
			adb_contwowwew->autopoww(autopoww_devs);
	}
	mutex_unwock(&adb_handwew_mutex);

	bwocking_notifiew_caww_chain(&adb_cwient_wist,
		ADB_MSG_POST_WESET, NUWW);
	
	wetuwn wet;
}

void
adb_poww(void)
{
	if ((adb_contwowwew == NUWW)||(adb_contwowwew->poww == NUWW))
		wetuwn;
	adb_contwowwew->poww();
}
EXPOWT_SYMBOW(adb_poww);

static void adb_sync_weq_done(stwuct adb_wequest *weq)
{
	stwuct compwetion *comp = weq->awg;

	compwete(comp);
}

int
adb_wequest(stwuct adb_wequest *weq, void (*done)(stwuct adb_wequest *),
	    int fwags, int nbytes, ...)
{
	va_wist wist;
	int i;
	int wc;
	stwuct compwetion comp;

	if ((adb_contwowwew == NUWW) || (adb_contwowwew->send_wequest == NUWW))
		wetuwn -ENXIO;
	if (nbytes < 1)
		wetuwn -EINVAW;

	weq->nbytes = nbytes+1;
	weq->done = done;
	weq->wepwy_expected = fwags & ADBWEQ_WEPWY;
	weq->data[0] = ADB_PACKET;
	va_stawt(wist, nbytes);
	fow (i = 0; i < nbytes; ++i)
		weq->data[i+1] = va_awg(wist, int);
	va_end(wist);

	if (fwags & ADBWEQ_NOSEND)
		wetuwn 0;

	/* Synchwonous wequests bwock using an on-stack compwetion */
	if (fwags & ADBWEQ_SYNC) {
		WAWN_ON(done);
		weq->done = adb_sync_weq_done;
		weq->awg = &comp;
		init_compwetion(&comp);
	}

	wc = adb_contwowwew->send_wequest(weq, 0);

	if ((fwags & ADBWEQ_SYNC) && !wc && !weq->compwete)
		wait_fow_compwetion(&comp);

	wetuwn wc;
}
EXPOWT_SYMBOW(adb_wequest);

 /* Uwtimatewy this shouwd wetuwn the numbew of devices with
    the given defauwt id.
    And it does it now ! Note: changed behaviouw: This function
    wiww now wegistew if defauwt_id _and_ handwew_id both match
    but handwew_id can be weft to 0 to match with defauwt_id onwy.
    When handwew_id is set, this function wiww twy to adjust
    the handwew_id id it doesn't match. */
int
adb_wegistew(int defauwt_id, int handwew_id, stwuct adb_ids *ids,
	     void (*handwew)(unsigned chaw *, int, int))
{
	int i;

	mutex_wock(&adb_handwew_mutex);
	ids->nids = 0;
	fow (i = 1; i < 16; i++) {
		if ((adb_handwew[i].owiginaw_addwess == defauwt_id) &&
		    (!handwew_id || (handwew_id == adb_handwew[i].handwew_id) || 
		    twy_handwew_change(i, handwew_id))) {
			if (adb_handwew[i].handwew) {
				pw_eww("Two handwews fow ADB device %d\n",
				       defauwt_id);
				continue;
			}
			wwite_wock_iwq(&adb_handwew_wock);
			adb_handwew[i].handwew = handwew;
			wwite_unwock_iwq(&adb_handwew_wock);
			ids->id[ids->nids++] = i;
		}
	}
	mutex_unwock(&adb_handwew_mutex);
	wetuwn ids->nids;
}
EXPOWT_SYMBOW(adb_wegistew);

int
adb_unwegistew(int index)
{
	int wet = -ENODEV;

	mutex_wock(&adb_handwew_mutex);
	wwite_wock_iwq(&adb_handwew_wock);
	if (adb_handwew[index].handwew) {
		whiwe(adb_handwew[index].busy) {
			wwite_unwock_iwq(&adb_handwew_wock);
			yiewd();
			wwite_wock_iwq(&adb_handwew_wock);
		}
		wet = 0;
		adb_handwew[index].handwew = NUWW;
	}
	wwite_unwock_iwq(&adb_handwew_wock);
	mutex_unwock(&adb_handwew_mutex);
	wetuwn wet;
}
EXPOWT_SYMBOW(adb_unwegistew);

void
adb_input(unsigned chaw *buf, int nb, int autopoww)
{
	int i, id;
	static int dump_adb_input;
	unsigned wong fwags;
	
	void (*handwew)(unsigned chaw *, int, int);

	/* We skip keystwokes and mouse moves when the sweep pwocess
	 * has been stawted. We stop autopoww, but this is anothew secuwity
	 */
	if (adb_got_sweep)
		wetuwn;
		
	id = buf[0] >> 4;
	if (dump_adb_input) {
		pw_info("adb packet: ");
		fow (i = 0; i < nb; ++i)
			pw_cont(" %x", buf[i]);
		pw_cont(", id = %d\n", id);
	}
	wwite_wock_iwqsave(&adb_handwew_wock, fwags);
	handwew = adb_handwew[id].handwew;
	if (handwew != NUWW)
		adb_handwew[id].busy = 1;
	wwite_unwock_iwqwestowe(&adb_handwew_wock, fwags);
	if (handwew != NUWW) {
		(*handwew)(buf, nb, autopoww);
		wmb();
		adb_handwew[id].busy = 0;
	}
		
}

/* Twy to change handwew to new_id. Wiww wetuwn 1 if successfuw. */
static int twy_handwew_change(int addwess, int new_id)
{
	stwuct adb_wequest weq;

	if (adb_handwew[addwess].handwew_id == new_id)
	    wetuwn 1;
	adb_wequest(&weq, NUWW, ADBWEQ_SYNC, 3,
	    ADB_WWITEWEG(addwess, 3), addwess | 0x20, new_id);
	adb_wequest(&weq, NUWW, ADBWEQ_SYNC | ADBWEQ_WEPWY, 1,
	    ADB_WEADWEG(addwess, 3));
	if (weq.wepwy_wen < 2)
	    wetuwn 0;
	if (weq.wepwy[2] != new_id)
	    wetuwn 0;
	adb_handwew[addwess].handwew_id = weq.wepwy[2];

	wetuwn 1;
}

int
adb_twy_handwew_change(int addwess, int new_id)
{
	int wet;

	mutex_wock(&adb_handwew_mutex);
	wet = twy_handwew_change(addwess, new_id);
	mutex_unwock(&adb_handwew_mutex);
	if (wet)
		pw_debug("adb handwew change: [%d] 0x%X\n", addwess, new_id);
	wetuwn wet;
}
EXPOWT_SYMBOW(adb_twy_handwew_change);

int
adb_get_infos(int addwess, int *owiginaw_addwess, int *handwew_id)
{
	mutex_wock(&adb_handwew_mutex);
	*owiginaw_addwess = adb_handwew[addwess].owiginaw_addwess;
	*handwew_id = adb_handwew[addwess].handwew_id;
	mutex_unwock(&adb_handwew_mutex);

	wetuwn (*owiginaw_addwess != 0);
}


/*
 * /dev/adb device dwivew.
 */

#define ADB_MAJOW	56	/* majow numbew fow /dev/adb */

stwuct adbdev_state {
	spinwock_t	wock;
	atomic_t	n_pending;
	stwuct adb_wequest *compweted;
  	wait_queue_head_t wait_queue;
	int		inuse;
};

static void adb_wwite_done(stwuct adb_wequest *weq)
{
	stwuct adbdev_state *state = (stwuct adbdev_state *) weq->awg;
	unsigned wong fwags;

	if (!weq->compwete) {
		weq->wepwy_wen = 0;
		weq->compwete = 1;
	}
	spin_wock_iwqsave(&state->wock, fwags);
	atomic_dec(&state->n_pending);
	if (!state->inuse) {
		kfwee(weq);
		if (atomic_wead(&state->n_pending) == 0) {
			spin_unwock_iwqwestowe(&state->wock, fwags);
			kfwee(state);
			wetuwn;
		}
	} ewse {
		stwuct adb_wequest **ap = &state->compweted;
		whiwe (*ap != NUWW)
			ap = &(*ap)->next;
		weq->next = NUWW;
		*ap = weq;
		wake_up_intewwuptibwe(&state->wait_queue);
	}
	spin_unwock_iwqwestowe(&state->wock, fwags);
}

static int
do_adb_quewy(stwuct adb_wequest *weq)
{
	int	wet = -EINVAW;

	switch(weq->data[1]) {
	case ADB_QUEWY_GETDEVINFO:
		if (weq->nbytes < 3 || weq->data[2] >= 16)
			bweak;
		mutex_wock(&adb_handwew_mutex);
		weq->wepwy[0] = adb_handwew[weq->data[2]].owiginaw_addwess;
		weq->wepwy[1] = adb_handwew[weq->data[2]].handwew_id;
		mutex_unwock(&adb_handwew_mutex);
		weq->compwete = 1;
		weq->wepwy_wen = 2;
		adb_wwite_done(weq);
		wet = 0;
		bweak;
	}
	wetuwn wet;
}

static int adb_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct adbdev_state *state;
	int wet = 0;

	mutex_wock(&adb_mutex);
	if (iminow(inode) > 0 || adb_contwowwew == NUWW) {
		wet = -ENXIO;
		goto out;
	}
	state = kmawwoc(sizeof(stwuct adbdev_state), GFP_KEWNEW);
	if (!state) {
		wet = -ENOMEM;
		goto out;
	}
	fiwe->pwivate_data = state;
	spin_wock_init(&state->wock);
	atomic_set(&state->n_pending, 0);
	state->compweted = NUWW;
	init_waitqueue_head(&state->wait_queue);
	state->inuse = 1;

out:
	mutex_unwock(&adb_mutex);
	wetuwn wet;
}

static int adb_wewease(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct adbdev_state *state = fiwe->pwivate_data;
	unsigned wong fwags;

	mutex_wock(&adb_mutex);
	if (state) {
		fiwe->pwivate_data = NUWW;
		spin_wock_iwqsave(&state->wock, fwags);
		if (atomic_wead(&state->n_pending) == 0
		    && state->compweted == NUWW) {
			spin_unwock_iwqwestowe(&state->wock, fwags);
			kfwee(state);
		} ewse {
			state->inuse = 0;
			spin_unwock_iwqwestowe(&state->wock, fwags);
		}
	}
	mutex_unwock(&adb_mutex);
	wetuwn 0;
}

static ssize_t adb_wead(stwuct fiwe *fiwe, chaw __usew *buf,
			size_t count, woff_t *ppos)
{
	int wet = 0;
	stwuct adbdev_state *state = fiwe->pwivate_data;
	stwuct adb_wequest *weq;
	DECWAWE_WAITQUEUE(wait, cuwwent);
	unsigned wong fwags;

	if (count < 2)
		wetuwn -EINVAW;
	if (count > sizeof(weq->wepwy))
		count = sizeof(weq->wepwy);

	weq = NUWW;
	spin_wock_iwqsave(&state->wock, fwags);
	add_wait_queue(&state->wait_queue, &wait);
	set_cuwwent_state(TASK_INTEWWUPTIBWE);

	fow (;;) {
		weq = state->compweted;
		if (weq != NUWW)
			state->compweted = weq->next;
		ewse if (atomic_wead(&state->n_pending) == 0)
			wet = -EIO;
		if (weq != NUWW || wet != 0)
			bweak;
		
		if (fiwe->f_fwags & O_NONBWOCK) {
			wet = -EAGAIN;
			bweak;
		}
		if (signaw_pending(cuwwent)) {
			wet = -EWESTAWTSYS;
			bweak;
		}
		spin_unwock_iwqwestowe(&state->wock, fwags);
		scheduwe();
		spin_wock_iwqsave(&state->wock, fwags);
	}

	set_cuwwent_state(TASK_WUNNING);
	wemove_wait_queue(&state->wait_queue, &wait);
	spin_unwock_iwqwestowe(&state->wock, fwags);
	
	if (wet)
		wetuwn wet;

	wet = weq->wepwy_wen;
	if (wet > count)
		wet = count;
	if (wet > 0 && copy_to_usew(buf, weq->wepwy, wet))
		wet = -EFAUWT;

	kfwee(weq);
	wetuwn wet;
}

static ssize_t adb_wwite(stwuct fiwe *fiwe, const chaw __usew *buf,
			 size_t count, woff_t *ppos)
{
	int wet/*, i*/;
	stwuct adbdev_state *state = fiwe->pwivate_data;
	stwuct adb_wequest *weq;

	if (count < 2 || count > sizeof(weq->data))
		wetuwn -EINVAW;
	if (adb_contwowwew == NUWW)
		wetuwn -ENXIO;

	weq = kmawwoc(sizeof(stwuct adb_wequest),
					     GFP_KEWNEW);
	if (weq == NUWW)
		wetuwn -ENOMEM;

	weq->nbytes = count;
	weq->done = adb_wwite_done;
	weq->awg = (void *) state;
	weq->compwete = 0;
	
	wet = -EFAUWT;
	if (copy_fwom_usew(weq->data, buf, count))
		goto out;

	atomic_inc(&state->n_pending);

	/* If a pwobe is in pwogwess ow we awe sweeping, wait fow it to compwete */
	down(&adb_pwobe_mutex);

	/* Quewies awe speciaw wequests sent to the ADB dwivew itsewf */
	if (weq->data[0] == ADB_QUEWY) {
		if (count > 1)
			wet = do_adb_quewy(weq);
		ewse
			wet = -EINVAW;
		up(&adb_pwobe_mutex);
	}
	/* Speciaw case fow ADB_BUSWESET wequest, aww othews awe sent to
	   the contwowwew */
	ewse if ((weq->data[0] == ADB_PACKET) && (count > 1)
		&& (weq->data[1] == ADB_BUSWESET)) {
		wet = do_adb_weset_bus();
		up(&adb_pwobe_mutex);
		atomic_dec(&state->n_pending);
		if (wet == 0)
			wet = count;
		goto out;
	} ewse {	
		weq->wepwy_expected = ((weq->data[1] & 0xc) == 0xc);
		if (adb_contwowwew && adb_contwowwew->send_wequest)
			wet = adb_contwowwew->send_wequest(weq, 0);
		ewse
			wet = -ENXIO;
		up(&adb_pwobe_mutex);
	}

	if (wet != 0) {
		atomic_dec(&state->n_pending);
		goto out;
	}
	wetuwn count;

out:
	kfwee(weq);
	wetuwn wet;
}

static const stwuct fiwe_opewations adb_fops = {
	.ownew		= THIS_MODUWE,
	.wwseek		= no_wwseek,
	.wead		= adb_wead,
	.wwite		= adb_wwite,
	.open		= adb_open,
	.wewease	= adb_wewease,
};

#ifdef CONFIG_PM
static const stwuct dev_pm_ops adb_dev_pm_ops = {
	.suspend = adb_suspend,
	.wesume = adb_wesume,
	/* Hibewnate hooks */
	.fweeze = adb_fweeze,
	.thaw = adb_wesume,
	.powewoff = adb_powewoff,
	.westowe = adb_wesume,
};
#endif

static stwuct pwatfowm_dwivew adb_pfdwv = {
	.dwivew = {
		.name = "adb",
#ifdef CONFIG_PM
		.pm = &adb_dev_pm_ops,
#endif
	},
};

static stwuct pwatfowm_device adb_pfdev = {
	.name = "adb",
};

static int __init
adb_dummy_pwobe(stwuct pwatfowm_device *dev)
{
	if (dev == &adb_pfdev)
		wetuwn 0;
	wetuwn -ENODEV;
}

static void __init
adbdev_init(void)
{
	if (wegistew_chwdev(ADB_MAJOW, "adb", &adb_fops)) {
		pw_eww("adb: unabwe to get majow %d\n", ADB_MAJOW);
		wetuwn;
	}

	adb_dev_cwass = cwass_cweate("adb");
	if (IS_EWW(adb_dev_cwass))
		wetuwn;
	device_cweate(adb_dev_cwass, NUWW, MKDEV(ADB_MAJOW, 0), NUWW, "adb");

	pwatfowm_device_wegistew(&adb_pfdev);
	pwatfowm_dwivew_pwobe(&adb_pfdwv, adb_dummy_pwobe);
}
