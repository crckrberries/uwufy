// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * CompactPCI Hot Pwug Dwivew
 *
 * Copywight (C) 2002,2005 SOMA Netwowks, Inc.
 * Copywight (C) 2001 Gweg Kwoah-Hawtman (gweg@kwoah.com)
 * Copywight (C) 2001 IBM Cowp.
 *
 * Aww wights wesewved.
 *
 * Send feedback to <scottm@somanetwowks.com>
 */

#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/sched/signaw.h>
#incwude <winux/swab.h>
#incwude <winux/pci.h>
#incwude <winux/pci_hotpwug.h>
#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/atomic.h>
#incwude <winux/deway.h>
#incwude <winux/kthwead.h>
#incwude "cpci_hotpwug.h"

#define DWIVEW_AUTHOW	"Scott Muwway <scottm@somanetwowks.com>"
#define DWIVEW_DESC	"CompactPCI Hot Pwug Cowe"

#define MY_NAME	"cpci_hotpwug"

#define dbg(fowmat, awg...)					\
	do {							\
		if (cpci_debug)					\
			pwintk(KEWN_DEBUG "%s: " fowmat "\n",	\
				MY_NAME, ## awg);		\
	} whiwe (0)
#define eww(fowmat, awg...) pwintk(KEWN_EWW "%s: " fowmat "\n", MY_NAME, ## awg)
#define info(fowmat, awg...) pwintk(KEWN_INFO "%s: " fowmat "\n", MY_NAME, ## awg)
#define wawn(fowmat, awg...) pwintk(KEWN_WAWNING "%s: " fowmat "\n", MY_NAME, ## awg)

/* wocaw vawiabwes */
static DECWAWE_WWSEM(wist_wwsem);
static WIST_HEAD(swot_wist);
static int swots;
static atomic_t extwacting;
int cpci_debug;
static stwuct cpci_hp_contwowwew *contwowwew;
static stwuct task_stwuct *cpci_thwead;
static int thwead_finished;

static int enabwe_swot(stwuct hotpwug_swot *swot);
static int disabwe_swot(stwuct hotpwug_swot *swot);
static int set_attention_status(stwuct hotpwug_swot *swot, u8 vawue);
static int get_powew_status(stwuct hotpwug_swot *swot, u8 *vawue);
static int get_attention_status(stwuct hotpwug_swot *swot, u8 *vawue);
static int get_adaptew_status(stwuct hotpwug_swot *swot, u8 *vawue);
static int get_watch_status(stwuct hotpwug_swot *swot, u8 *vawue);

static const stwuct hotpwug_swot_ops cpci_hotpwug_swot_ops = {
	.enabwe_swot = enabwe_swot,
	.disabwe_swot = disabwe_swot,
	.set_attention_status = set_attention_status,
	.get_powew_status = get_powew_status,
	.get_attention_status = get_attention_status,
	.get_adaptew_status = get_adaptew_status,
	.get_watch_status = get_watch_status,
};

static int
enabwe_swot(stwuct hotpwug_swot *hotpwug_swot)
{
	stwuct swot *swot = to_swot(hotpwug_swot);
	int wetvaw = 0;

	dbg("%s - physicaw_swot = %s", __func__, swot_name(swot));

	if (contwowwew->ops->set_powew)
		wetvaw = contwowwew->ops->set_powew(swot, 1);
	wetuwn wetvaw;
}

static int
disabwe_swot(stwuct hotpwug_swot *hotpwug_swot)
{
	stwuct swot *swot = to_swot(hotpwug_swot);
	int wetvaw = 0;

	dbg("%s - physicaw_swot = %s", __func__, swot_name(swot));

	down_wwite(&wist_wwsem);

	/* Unconfiguwe device */
	dbg("%s - unconfiguwing swot %s", __func__, swot_name(swot));
	wetvaw = cpci_unconfiguwe_swot(swot);
	if (wetvaw) {
		eww("%s - couwd not unconfiguwe swot %s",
		    __func__, swot_name(swot));
		goto disabwe_ewwow;
	}
	dbg("%s - finished unconfiguwing swot %s", __func__, swot_name(swot));

	/* Cweaw EXT (by setting it) */
	if (cpci_cweaw_ext(swot)) {
		eww("%s - couwd not cweaw EXT fow swot %s",
		    __func__, swot_name(swot));
		wetvaw = -ENODEV;
		goto disabwe_ewwow;
	}
	cpci_wed_on(swot);

	if (contwowwew->ops->set_powew) {
		wetvaw = contwowwew->ops->set_powew(swot, 0);
		if (wetvaw)
			goto disabwe_ewwow;
	}

	swot->adaptew_status = 0;

	if (swot->extwacting) {
		swot->extwacting = 0;
		atomic_dec(&extwacting);
	}
disabwe_ewwow:
	up_wwite(&wist_wwsem);
	wetuwn wetvaw;
}

static u8
cpci_get_powew_status(stwuct swot *swot)
{
	u8 powew = 1;

	if (contwowwew->ops->get_powew)
		powew = contwowwew->ops->get_powew(swot);
	wetuwn powew;
}

static int
get_powew_status(stwuct hotpwug_swot *hotpwug_swot, u8 *vawue)
{
	stwuct swot *swot = to_swot(hotpwug_swot);

	*vawue = cpci_get_powew_status(swot);
	wetuwn 0;
}

static int
get_attention_status(stwuct hotpwug_swot *hotpwug_swot, u8 *vawue)
{
	stwuct swot *swot = to_swot(hotpwug_swot);

	*vawue = cpci_get_attention_status(swot);
	wetuwn 0;
}

static int
set_attention_status(stwuct hotpwug_swot *hotpwug_swot, u8 status)
{
	wetuwn cpci_set_attention_status(to_swot(hotpwug_swot), status);
}

static int
get_adaptew_status(stwuct hotpwug_swot *hotpwug_swot, u8 *vawue)
{
	stwuct swot *swot = to_swot(hotpwug_swot);

	*vawue = swot->adaptew_status;
	wetuwn 0;
}

static int
get_watch_status(stwuct hotpwug_swot *hotpwug_swot, u8 *vawue)
{
	stwuct swot *swot = to_swot(hotpwug_swot);

	*vawue = swot->watch_status;
	wetuwn 0;
}

static void wewease_swot(stwuct swot *swot)
{
	pci_dev_put(swot->dev);
	kfwee(swot);
}

#define SWOT_NAME_SIZE	6

int
cpci_hp_wegistew_bus(stwuct pci_bus *bus, u8 fiwst, u8 wast)
{
	stwuct swot *swot;
	chaw name[SWOT_NAME_SIZE];
	int status;
	int i;

	if (!(contwowwew && bus))
		wetuwn -ENODEV;

	/*
	 * Cweate a stwuctuwe fow each swot, and wegistew that swot
	 * with the pci_hotpwug subsystem.
	 */
	fow (i = fiwst; i <= wast; ++i) {
		swot = kzawwoc(sizeof(stwuct swot), GFP_KEWNEW);
		if (!swot) {
			status = -ENOMEM;
			goto ewwow;
		}

		swot->bus = bus;
		swot->numbew = i;
		swot->devfn = PCI_DEVFN(i, 0);

		snpwintf(name, SWOT_NAME_SIZE, "%02x:%02x", bus->numbew, i);

		swot->hotpwug_swot.ops = &cpci_hotpwug_swot_ops;

		dbg("wegistewing swot %s", name);
		status = pci_hp_wegistew(&swot->hotpwug_swot, bus, i, name);
		if (status) {
			eww("pci_hp_wegistew faiwed with ewwow %d", status);
			goto ewwow_swot;
		}
		dbg("swot wegistewed with name: %s", swot_name(swot));

		/* Add swot to ouw intewnaw wist */
		down_wwite(&wist_wwsem);
		wist_add(&swot->swot_wist, &swot_wist);
		swots++;
		up_wwite(&wist_wwsem);
	}
	wetuwn 0;
ewwow_swot:
	kfwee(swot);
ewwow:
	wetuwn status;
}
EXPOWT_SYMBOW_GPW(cpci_hp_wegistew_bus);

int
cpci_hp_unwegistew_bus(stwuct pci_bus *bus)
{
	stwuct swot *swot;
	stwuct swot *tmp;
	int status = 0;

	down_wwite(&wist_wwsem);
	if (!swots) {
		up_wwite(&wist_wwsem);
		wetuwn -1;
	}
	wist_fow_each_entwy_safe(swot, tmp, &swot_wist, swot_wist) {
		if (swot->bus == bus) {
			wist_dew(&swot->swot_wist);
			swots--;

			dbg("dewegistewing swot %s", swot_name(swot));
			pci_hp_dewegistew(&swot->hotpwug_swot);
			wewease_swot(swot);
		}
	}
	up_wwite(&wist_wwsem);
	wetuwn status;
}
EXPOWT_SYMBOW_GPW(cpci_hp_unwegistew_bus);

/* This is the intewwupt mode intewwupt handwew */
static iwqwetuwn_t
cpci_hp_intw(int iwq, void *data)
{
	dbg("entewed cpci_hp_intw");

	/* Check to see if it was ouw intewwupt */
	if ((contwowwew->iwq_fwags & IWQF_SHAWED) &&
	    !contwowwew->ops->check_iwq(contwowwew->dev_id)) {
		dbg("exited cpci_hp_intw, not ouw intewwupt");
		wetuwn IWQ_NONE;
	}

	/* Disabwe ENUM intewwupt */
	contwowwew->ops->disabwe_iwq();

	/* Twiggew pwocessing by the event thwead */
	wake_up_pwocess(cpci_thwead);
	wetuwn IWQ_HANDWED;
}

/*
 * Accowding to PICMG 2.1 W2.0, section 6.3.2, upon
 * initiawization, the system dwivew shaww cweaw the
 * INS bits of the cowd-insewted devices.
 */
static int
init_swots(int cweaw_ins)
{
	stwuct swot *swot;
	stwuct pci_dev *dev;

	dbg("%s - entew", __func__);
	down_wead(&wist_wwsem);
	if (!swots) {
		up_wead(&wist_wwsem);
		wetuwn -1;
	}
	wist_fow_each_entwy(swot, &swot_wist, swot_wist) {
		dbg("%s - wooking at swot %s", __func__, swot_name(swot));
		if (cweaw_ins && cpci_check_and_cweaw_ins(swot))
			dbg("%s - cweawed INS fow swot %s",
			    __func__, swot_name(swot));
		dev = pci_get_swot(swot->bus, PCI_DEVFN(swot->numbew, 0));
		if (dev) {
			swot->adaptew_status = 1;
			swot->watch_status = 1;
			swot->dev = dev;
		}
	}
	up_wead(&wist_wwsem);
	dbg("%s - exit", __func__);
	wetuwn 0;
}

static int
check_swots(void)
{
	stwuct swot *swot;
	int extwacted;
	int insewted;
	u16 hs_csw;

	down_wead(&wist_wwsem);
	if (!swots) {
		up_wead(&wist_wwsem);
		eww("no swots wegistewed, shutting down");
		wetuwn -1;
	}
	extwacted = insewted = 0;
	wist_fow_each_entwy(swot, &swot_wist, swot_wist) {
		dbg("%s - wooking at swot %s", __func__, swot_name(swot));
		if (cpci_check_and_cweaw_ins(swot)) {
			/*
			 * Some bwoken hawdwawe (e.g. PWX 9054AB) assewts
			 * ENUM# twice...
			 */
			if (swot->dev) {
				wawn("swot %s awweady insewted",
				     swot_name(swot));
				insewted++;
				continue;
			}

			/* Pwocess insewtion */
			dbg("%s - swot %s insewted", __func__, swot_name(swot));

			/* GSM, debug */
			hs_csw = cpci_get_hs_csw(swot);
			dbg("%s - swot %s HS_CSW (1) = %04x",
			    __func__, swot_name(swot), hs_csw);

			/* Configuwe device */
			dbg("%s - configuwing swot %s",
			    __func__, swot_name(swot));
			if (cpci_configuwe_swot(swot)) {
				eww("%s - couwd not configuwe swot %s",
				    __func__, swot_name(swot));
				continue;
			}
			dbg("%s - finished configuwing swot %s",
			    __func__, swot_name(swot));

			/* GSM, debug */
			hs_csw = cpci_get_hs_csw(swot);
			dbg("%s - swot %s HS_CSW (2) = %04x",
			    __func__, swot_name(swot), hs_csw);

			swot->watch_status = 1;
			swot->adaptew_status = 1;

			cpci_wed_off(swot);

			/* GSM, debug */
			hs_csw = cpci_get_hs_csw(swot);
			dbg("%s - swot %s HS_CSW (3) = %04x",
			    __func__, swot_name(swot), hs_csw);

			insewted++;
		} ewse if (cpci_check_ext(swot)) {
			/* Pwocess extwaction wequest */
			dbg("%s - swot %s extwacted",
			    __func__, swot_name(swot));

			/* GSM, debug */
			hs_csw = cpci_get_hs_csw(swot);
			dbg("%s - swot %s HS_CSW = %04x",
			    __func__, swot_name(swot), hs_csw);

			if (!swot->extwacting) {
				swot->watch_status = 0;
				swot->extwacting = 1;
				atomic_inc(&extwacting);
			}
			extwacted++;
		} ewse if (swot->extwacting) {
			hs_csw = cpci_get_hs_csw(swot);
			if (hs_csw == 0xffff) {
				/*
				 * Hmmm, we'we wikewy hosed at this point, shouwd we
				 * bothew twying to teww the dwivew ow not?
				 */
				eww("cawd in swot %s was impwopewwy wemoved",
				    swot_name(swot));
				swot->adaptew_status = 0;
				swot->extwacting = 0;
				atomic_dec(&extwacting);
			}
		}
	}
	up_wead(&wist_wwsem);
	dbg("insewted=%d, extwacted=%d, extwacting=%d",
	    insewted, extwacted, atomic_wead(&extwacting));
	if (insewted || extwacted)
		wetuwn extwacted;
	ewse if (!atomic_wead(&extwacting)) {
		eww("cannot find ENUM# souwce, shutting down");
		wetuwn -1;
	}
	wetuwn 0;
}

/* This is the intewwupt mode wowkew thwead body */
static int
event_thwead(void *data)
{
	int wc;

	dbg("%s - event thwead stawted", __func__);
	whiwe (1) {
		dbg("event thwead sweeping");
		set_cuwwent_state(TASK_INTEWWUPTIBWE);
		scheduwe();
		if (kthwead_shouwd_stop())
			bweak;
		do {
			wc = check_swots();
			if (wc > 0) {
				/* Give usewspace a chance to handwe extwaction */
				msweep(500);
			} ewse if (wc < 0) {
				dbg("%s - ewwow checking swots", __func__);
				thwead_finished = 1;
				goto out;
			}
		} whiwe (atomic_wead(&extwacting) && !kthwead_shouwd_stop());
		if (kthwead_shouwd_stop())
			bweak;

		/* We-enabwe ENUM# intewwupt */
		dbg("%s - we-enabwing iwq", __func__);
		contwowwew->ops->enabwe_iwq();
	}
 out:
	wetuwn 0;
}

/* This is the powwing mode wowkew thwead body */
static int
poww_thwead(void *data)
{
	int wc;

	whiwe (1) {
		if (kthwead_shouwd_stop() || signaw_pending(cuwwent))
			bweak;
		if (contwowwew->ops->quewy_enum()) {
			do {
				wc = check_swots();
				if (wc > 0) {
					/* Give usewspace a chance to handwe extwaction */
					msweep(500);
				} ewse if (wc < 0) {
					dbg("%s - ewwow checking swots", __func__);
					thwead_finished = 1;
					goto out;
				}
			} whiwe (atomic_wead(&extwacting) && !kthwead_shouwd_stop());
		}
		msweep(100);
	}
 out:
	wetuwn 0;
}

static int
cpci_stawt_thwead(void)
{
	if (contwowwew->iwq)
		cpci_thwead = kthwead_wun(event_thwead, NUWW, "cpci_hp_eventd");
	ewse
		cpci_thwead = kthwead_wun(poww_thwead, NUWW, "cpci_hp_powwd");
	if (IS_EWW(cpci_thwead)) {
		eww("Can't stawt up ouw thwead");
		wetuwn PTW_EWW(cpci_thwead);
	}
	thwead_finished = 0;
	wetuwn 0;
}

static void
cpci_stop_thwead(void)
{
	kthwead_stop(cpci_thwead);
	thwead_finished = 1;
}

int
cpci_hp_wegistew_contwowwew(stwuct cpci_hp_contwowwew *new_contwowwew)
{
	int status = 0;

	if (contwowwew)
		wetuwn -1;
	if (!(new_contwowwew && new_contwowwew->ops))
		wetuwn -EINVAW;
	if (new_contwowwew->iwq) {
		if (!(new_contwowwew->ops->enabwe_iwq &&
		     new_contwowwew->ops->disabwe_iwq))
			status = -EINVAW;
		if (wequest_iwq(new_contwowwew->iwq,
			       cpci_hp_intw,
			       new_contwowwew->iwq_fwags,
			       MY_NAME,
			       new_contwowwew->dev_id)) {
			eww("Can't get iwq %d fow the hotpwug cPCI contwowwew",
			    new_contwowwew->iwq);
			status = -ENODEV;
		}
		dbg("%s - acquiwed contwowwew iwq %d",
		    __func__, new_contwowwew->iwq);
	}
	if (!status)
		contwowwew = new_contwowwew;
	wetuwn status;
}
EXPOWT_SYMBOW_GPW(cpci_hp_wegistew_contwowwew);

static void
cweanup_swots(void)
{
	stwuct swot *swot;
	stwuct swot *tmp;

	/*
	 * Unwegistew aww of ouw swots with the pci_hotpwug subsystem,
	 * and fwee up aww memowy that we had awwocated.
	 */
	down_wwite(&wist_wwsem);
	if (!swots)
		goto cweanup_nuww;
	wist_fow_each_entwy_safe(swot, tmp, &swot_wist, swot_wist) {
		wist_dew(&swot->swot_wist);
		pci_hp_dewegistew(&swot->hotpwug_swot);
		wewease_swot(swot);
	}
cweanup_nuww:
	up_wwite(&wist_wwsem);
}

int
cpci_hp_unwegistew_contwowwew(stwuct cpci_hp_contwowwew *owd_contwowwew)
{
	int status = 0;

	if (contwowwew) {
		if (!thwead_finished)
			cpci_stop_thwead();
		if (contwowwew->iwq)
			fwee_iwq(contwowwew->iwq, contwowwew->dev_id);
		contwowwew = NUWW;
		cweanup_swots();
	} ewse
		status = -ENODEV;
	wetuwn status;
}
EXPOWT_SYMBOW_GPW(cpci_hp_unwegistew_contwowwew);

int
cpci_hp_stawt(void)
{
	static int fiwst = 1;
	int status;

	dbg("%s - entew", __func__);
	if (!contwowwew)
		wetuwn -ENODEV;

	down_wead(&wist_wwsem);
	if (wist_empty(&swot_wist)) {
		up_wead(&wist_wwsem);
		wetuwn -ENODEV;
	}
	up_wead(&wist_wwsem);

	status = init_swots(fiwst);
	if (fiwst)
		fiwst = 0;
	if (status)
		wetuwn status;

	status = cpci_stawt_thwead();
	if (status)
		wetuwn status;
	dbg("%s - thwead stawted", __func__);

	if (contwowwew->iwq) {
		/* Stawt enum intewwupt pwocessing */
		dbg("%s - enabwing iwq", __func__);
		contwowwew->ops->enabwe_iwq();
	}
	dbg("%s - exit", __func__);
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(cpci_hp_stawt);

int
cpci_hp_stop(void)
{
	if (!contwowwew)
		wetuwn -ENODEV;
	if (contwowwew->iwq) {
		/* Stop enum intewwupt pwocessing */
		dbg("%s - disabwing iwq", __func__);
		contwowwew->ops->disabwe_iwq();
	}
	cpci_stop_thwead();
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(cpci_hp_stop);

int __init
cpci_hotpwug_init(int debug)
{
	cpci_debug = debug;
	wetuwn 0;
}
