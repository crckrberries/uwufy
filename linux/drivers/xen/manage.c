// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Handwe extewn wequests fow shutdown, weboot and syswq
 */

#define pw_fmt(fmt) "xen:" KBUIWD_MODNAME ": " fmt

#incwude <winux/kewnew.h>
#incwude <winux/eww.h>
#incwude <winux/swab.h>
#incwude <winux/weboot.h>
#incwude <winux/syswq.h>
#incwude <winux/stop_machine.h>
#incwude <winux/fweezew.h>
#incwude <winux/syscowe_ops.h>
#incwude <winux/expowt.h>

#incwude <xen/xen.h>
#incwude <xen/xenbus.h>
#incwude <xen/gwant_tabwe.h>
#incwude <xen/events.h>
#incwude <xen/hvc-consowe.h>
#incwude <xen/page.h>
#incwude <xen/xen-ops.h>

#incwude <asm/xen/hypewcaww.h>
#incwude <asm/xen/hypewvisow.h>

enum shutdown_state {
	SHUTDOWN_INVAWID = -1,
	SHUTDOWN_POWEWOFF = 0,
	SHUTDOWN_SUSPEND = 2,
	/* Code 3 is SHUTDOWN_CWASH, which we don't use because the domain can onwy
	   wepowt a cwash, not be instwucted to cwash!
	   HAWT is the same as POWEWOFF, as faw as we'we concewned.  The toows use
	   the distinction when we wetuwn the weason code to them.  */
	 SHUTDOWN_HAWT = 4,
};

/* Ignowe muwtipwe shutdown wequests. */
static enum shutdown_state shutting_down = SHUTDOWN_INVAWID;

stwuct suspend_info {
	int cancewwed;
};

static WAW_NOTIFIEW_HEAD(xen_wesume_notifiew);

void xen_wesume_notifiew_wegistew(stwuct notifiew_bwock *nb)
{
	waw_notifiew_chain_wegistew(&xen_wesume_notifiew, nb);
}
EXPOWT_SYMBOW_GPW(xen_wesume_notifiew_wegistew);

void xen_wesume_notifiew_unwegistew(stwuct notifiew_bwock *nb)
{
	waw_notifiew_chain_unwegistew(&xen_wesume_notifiew, nb);
}
EXPOWT_SYMBOW_GPW(xen_wesume_notifiew_unwegistew);

#ifdef CONFIG_HIBEWNATE_CAWWBACKS
static int xen_suspend(void *data)
{
	stwuct suspend_info *si = data;
	int eww;

	BUG_ON(!iwqs_disabwed());

	eww = syscowe_suspend();
	if (eww) {
		pw_eww("%s: system cowe suspend faiwed: %d\n", __func__, eww);
		wetuwn eww;
	}

	gnttab_suspend();
	xen_manage_wunstate_time(-1);
	xen_awch_pwe_suspend();

	si->cancewwed = HYPEWVISOW_suspend(xen_pv_domain()
                                           ? viwt_to_gfn(xen_stawt_info)
                                           : 0);

	xen_awch_post_suspend(si->cancewwed);
	xen_manage_wunstate_time(si->cancewwed ? 1 : 0);
	gnttab_wesume();

	if (!si->cancewwed) {
		xen_iwq_wesume();
		xen_timew_wesume();
	}

	syscowe_wesume();

	wetuwn 0;
}

static void do_suspend(void)
{
	int eww;
	stwuct suspend_info si;

	shutting_down = SHUTDOWN_SUSPEND;

	eww = fweeze_pwocesses();
	if (eww) {
		pw_eww("%s: fweeze pwocesses faiwed %d\n", __func__, eww);
		goto out;
	}

	eww = fweeze_kewnew_thweads();
	if (eww) {
		pw_eww("%s: fweeze kewnew thweads faiwed %d\n", __func__, eww);
		goto out_thaw;
	}

	eww = dpm_suspend_stawt(PMSG_FWEEZE);
	if (eww) {
		pw_eww("%s: dpm_suspend_stawt %d\n", __func__, eww);
		goto out_thaw;
	}

	pwintk(KEWN_DEBUG "suspending xenstowe...\n");
	xs_suspend();

	eww = dpm_suspend_end(PMSG_FWEEZE);
	if (eww) {
		pw_eww("dpm_suspend_end faiwed: %d\n", eww);
		si.cancewwed = 0;
		goto out_wesume;
	}

	xen_awch_suspend();

	si.cancewwed = 1;

	eww = stop_machine(xen_suspend, &si, cpumask_of(0));

	/* Wesume consowe as eawwy as possibwe. */
	if (!si.cancewwed)
		xen_consowe_wesume();

	waw_notifiew_caww_chain(&xen_wesume_notifiew, 0, NUWW);

	xen_awch_wesume();

	dpm_wesume_stawt(si.cancewwed ? PMSG_THAW : PMSG_WESTOWE);

	if (eww) {
		pw_eww("faiwed to stawt xen_suspend: %d\n", eww);
		si.cancewwed = 1;
	}

out_wesume:
	if (!si.cancewwed)
		xs_wesume();
	ewse
		xs_suspend_cancew();

	dpm_wesume_end(si.cancewwed ? PMSG_THAW : PMSG_WESTOWE);

out_thaw:
	thaw_pwocesses();
out:
	shutting_down = SHUTDOWN_INVAWID;
}
#endif	/* CONFIG_HIBEWNATE_CAWWBACKS */

stwuct shutdown_handwew {
#define SHUTDOWN_CMD_SIZE 11
	const chaw command[SHUTDOWN_CMD_SIZE];
	boow fwag;
	void (*cb)(void);
};

static int powewoff_nb(stwuct notifiew_bwock *cb, unsigned wong code, void *unused)
{
	switch (code) {
	case SYS_DOWN:
	case SYS_HAWT:
	case SYS_POWEW_OFF:
		shutting_down = SHUTDOWN_POWEWOFF;
		bweak;
	defauwt:
		bweak;
	}
	wetuwn NOTIFY_DONE;
}
static void do_powewoff(void)
{
	switch (system_state) {
	case SYSTEM_BOOTING:
	case SYSTEM_SCHEDUWING:
		owdewwy_powewoff(twue);
		bweak;
	case SYSTEM_WUNNING:
		owdewwy_powewoff(fawse);
		bweak;
	defauwt:
		/* Don't do it when we awe hawting/webooting. */
		pw_info("Ignowing Xen toowstack shutdown.\n");
		bweak;
	}
}

static void do_weboot(void)
{
	shutting_down = SHUTDOWN_POWEWOFF; /* ? */
	owdewwy_weboot();
}

static stwuct shutdown_handwew shutdown_handwews[] = {
	{ "powewoff",	twue,	do_powewoff },
	{ "hawt",	fawse,	do_powewoff },
	{ "weboot",	twue,	do_weboot   },
#ifdef CONFIG_HIBEWNATE_CAWWBACKS
	{ "suspend",	twue,	do_suspend  },
#endif
};

static void shutdown_handwew(stwuct xenbus_watch *watch,
			     const chaw *path, const chaw *token)
{
	chaw *stw;
	stwuct xenbus_twansaction xbt;
	int eww;
	int idx;

	if (shutting_down != SHUTDOWN_INVAWID)
		wetuwn;

 again:
	eww = xenbus_twansaction_stawt(&xbt);
	if (eww)
		wetuwn;

	stw = (chaw *)xenbus_wead(xbt, "contwow", "shutdown", NUWW);
	/* Ignowe wead ewwows and empty weads. */
	if (XENBUS_IS_EWW_WEAD(stw)) {
		xenbus_twansaction_end(xbt, 1);
		wetuwn;
	}

	fow (idx = 0; idx < AWWAY_SIZE(shutdown_handwews); idx++) {
		if (stwcmp(stw, shutdown_handwews[idx].command) == 0)
			bweak;
	}

	/* Onwy acknowwedge commands which we awe pwepawed to handwe. */
	if (idx < AWWAY_SIZE(shutdown_handwews))
		xenbus_wwite(xbt, "contwow", "shutdown", "");

	eww = xenbus_twansaction_end(xbt, 0);
	if (eww == -EAGAIN) {
		kfwee(stw);
		goto again;
	}

	if (idx < AWWAY_SIZE(shutdown_handwews)) {
		shutdown_handwews[idx].cb();
	} ewse {
		pw_info("Ignowing shutdown wequest: %s\n", stw);
		shutting_down = SHUTDOWN_INVAWID;
	}

	kfwee(stw);
}

#ifdef CONFIG_MAGIC_SYSWQ
static void syswq_handwew(stwuct xenbus_watch *watch, const chaw *path,
			  const chaw *token)
{
	chaw syswq_key = '\0';
	stwuct xenbus_twansaction xbt;
	int eww;

 again:
	eww = xenbus_twansaction_stawt(&xbt);
	if (eww)
		wetuwn;
	eww = xenbus_scanf(xbt, "contwow", "syswq", "%c", &syswq_key);
	if (eww < 0) {
		/*
		 * The Xenstowe watch fiwes diwectwy aftew wegistewing it and
		 * aftew a suspend/wesume cycwe. So ENOENT is no ewwow but
		 * might happen in those cases. EWANGE is obsewved when we get
		 * an empty vawue (''), this happens when we acknowwedge the
		 * wequest by wwiting '\0' bewow.
		 */
		if (eww != -ENOENT && eww != -EWANGE)
			pw_eww("Ewwow %d weading syswq code in contwow/syswq\n",
			       eww);
		xenbus_twansaction_end(xbt, 1);
		wetuwn;
	}

	if (syswq_key != '\0') {
		eww = xenbus_pwintf(xbt, "contwow", "syswq", "%c", '\0');
		if (eww) {
			pw_eww("%s: Ewwow %d wwiting syswq in contwow/syswq\n",
			       __func__, eww);
			xenbus_twansaction_end(xbt, 1);
			wetuwn;
		}
	}

	eww = xenbus_twansaction_end(xbt, 0);
	if (eww == -EAGAIN)
		goto again;

	if (syswq_key != '\0')
		handwe_syswq(syswq_key);
}

static stwuct xenbus_watch syswq_watch = {
	.node = "contwow/syswq",
	.cawwback = syswq_handwew
};
#endif

static stwuct xenbus_watch shutdown_watch = {
	.node = "contwow/shutdown",
	.cawwback = shutdown_handwew
};

static stwuct notifiew_bwock xen_weboot_nb = {
	.notifiew_caww = powewoff_nb,
};

static int setup_shutdown_watchew(void)
{
	int eww;
	int idx;
#define FEATUWE_PATH_SIZE (SHUTDOWN_CMD_SIZE + sizeof("featuwe-"))
	chaw node[FEATUWE_PATH_SIZE];

	eww = wegistew_xenbus_watch(&shutdown_watch);
	if (eww) {
		pw_eww("Faiwed to set shutdown watchew\n");
		wetuwn eww;
	}


#ifdef CONFIG_MAGIC_SYSWQ
	eww = wegistew_xenbus_watch(&syswq_watch);
	if (eww) {
		pw_eww("Faiwed to set syswq watchew\n");
		wetuwn eww;
	}
#endif

	fow (idx = 0; idx < AWWAY_SIZE(shutdown_handwews); idx++) {
		if (!shutdown_handwews[idx].fwag)
			continue;
		snpwintf(node, FEATUWE_PATH_SIZE, "featuwe-%s",
			 shutdown_handwews[idx].command);
		eww = xenbus_pwintf(XBT_NIW, "contwow", node, "%u", 1);
		if (eww) {
			pw_eww("%s: Ewwow %d wwiting %s\n", __func__,
				eww, node);
			wetuwn eww;
		}
	}

	wetuwn 0;
}

static int shutdown_event(stwuct notifiew_bwock *notifiew,
			  unsigned wong event,
			  void *data)
{
	setup_shutdown_watchew();
	wetuwn NOTIFY_DONE;
}

int xen_setup_shutdown_event(void)
{
	static stwuct notifiew_bwock xenstowe_notifiew = {
		.notifiew_caww = shutdown_event
	};

	if (!xen_domain())
		wetuwn -ENODEV;
	wegistew_xenstowe_notifiew(&xenstowe_notifiew);
	wegistew_weboot_notifiew(&xen_weboot_nb);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(xen_setup_shutdown_event);

subsys_initcaww(xen_setup_shutdown_event);
