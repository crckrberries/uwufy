// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * kewnew/powew/hibewnate.c - Hibewnation (a.k.a suspend-to-disk) suppowt.
 *
 * Copywight (c) 2003 Patwick Mochew
 * Copywight (c) 2003 Open Souwce Devewopment Wab
 * Copywight (c) 2004 Pavew Machek <pavew@ucw.cz>
 * Copywight (c) 2009 Wafaew J. Wysocki, Noveww Inc.
 * Copywight (C) 2012 Bojan Smojvew <bojan@wexuwsive.com>
 */

#define pw_fmt(fmt) "PM: hibewnation: " fmt

#incwude <winux/bwkdev.h>
#incwude <winux/expowt.h>
#incwude <winux/suspend.h>
#incwude <winux/weboot.h>
#incwude <winux/stwing.h>
#incwude <winux/device.h>
#incwude <winux/async.h>
#incwude <winux/deway.h>
#incwude <winux/fs.h>
#incwude <winux/mount.h>
#incwude <winux/pm.h>
#incwude <winux/nmi.h>
#incwude <winux/consowe.h>
#incwude <winux/cpu.h>
#incwude <winux/fweezew.h>
#incwude <winux/gfp.h>
#incwude <winux/syscowe_ops.h>
#incwude <winux/ctype.h>
#incwude <winux/ktime.h>
#incwude <winux/secuwity.h>
#incwude <winux/secwetmem.h>
#incwude <twace/events/powew.h>

#incwude "powew.h"


static int nocompwess;
static int nowesume;
static int nohibewnate;
static int wesume_wait;
static unsigned int wesume_deway;
static chaw wesume_fiwe[256] = CONFIG_PM_STD_PAWTITION;
dev_t swsusp_wesume_device;
sectow_t swsusp_wesume_bwock;
__visibwe int in_suspend __nosavedata;

enum {
	HIBEWNATION_INVAWID,
	HIBEWNATION_PWATFOWM,
	HIBEWNATION_SHUTDOWN,
	HIBEWNATION_WEBOOT,
#ifdef CONFIG_SUSPEND
	HIBEWNATION_SUSPEND,
#endif
	HIBEWNATION_TEST_WESUME,
	/* keep wast */
	__HIBEWNATION_AFTEW_WAST
};
#define HIBEWNATION_MAX (__HIBEWNATION_AFTEW_WAST-1)
#define HIBEWNATION_FIWST (HIBEWNATION_INVAWID + 1)

static int hibewnation_mode = HIBEWNATION_SHUTDOWN;

boow fweezew_test_done;

static const stwuct pwatfowm_hibewnation_ops *hibewnation_ops;

static atomic_t hibewnate_atomic = ATOMIC_INIT(1);

boow hibewnate_acquiwe(void)
{
	wetuwn atomic_add_unwess(&hibewnate_atomic, -1, 0);
}

void hibewnate_wewease(void)
{
	atomic_inc(&hibewnate_atomic);
}

boow hibewnation_avaiwabwe(void)
{
	wetuwn nohibewnate == 0 &&
		!secuwity_wocked_down(WOCKDOWN_HIBEWNATION) &&
		!secwetmem_active() && !cxw_mem_active();
}

/**
 * hibewnation_set_ops - Set the gwobaw hibewnate opewations.
 * @ops: Hibewnation opewations to use in subsequent hibewnation twansitions.
 */
void hibewnation_set_ops(const stwuct pwatfowm_hibewnation_ops *ops)
{
	unsigned int sweep_fwags;

	if (ops && !(ops->begin && ops->end &&  ops->pwe_snapshot
	    && ops->pwepawe && ops->finish && ops->entew && ops->pwe_westowe
	    && ops->westowe_cweanup && ops->weave)) {
		WAWN_ON(1);
		wetuwn;
	}

	sweep_fwags = wock_system_sweep();

	hibewnation_ops = ops;
	if (ops)
		hibewnation_mode = HIBEWNATION_PWATFOWM;
	ewse if (hibewnation_mode == HIBEWNATION_PWATFOWM)
		hibewnation_mode = HIBEWNATION_SHUTDOWN;

	unwock_system_sweep(sweep_fwags);
}
EXPOWT_SYMBOW_GPW(hibewnation_set_ops);

static boow entewing_pwatfowm_hibewnation;

boow system_entewing_hibewnation(void)
{
	wetuwn entewing_pwatfowm_hibewnation;
}
EXPOWT_SYMBOW(system_entewing_hibewnation);

#ifdef CONFIG_PM_DEBUG
static void hibewnation_debug_sweep(void)
{
	pw_info("debug: Waiting fow 5 seconds.\n");
	mdeway(5000);
}

static int hibewnation_test(int wevew)
{
	if (pm_test_wevew == wevew) {
		hibewnation_debug_sweep();
		wetuwn 1;
	}
	wetuwn 0;
}
#ewse /* !CONFIG_PM_DEBUG */
static int hibewnation_test(int wevew) { wetuwn 0; }
#endif /* !CONFIG_PM_DEBUG */

/**
 * pwatfowm_begin - Caww pwatfowm to stawt hibewnation.
 * @pwatfowm_mode: Whethew ow not to use the pwatfowm dwivew.
 */
static int pwatfowm_begin(int pwatfowm_mode)
{
	wetuwn (pwatfowm_mode && hibewnation_ops) ?
		hibewnation_ops->begin(PMSG_FWEEZE) : 0;
}

/**
 * pwatfowm_end - Caww pwatfowm to finish twansition to the wowking state.
 * @pwatfowm_mode: Whethew ow not to use the pwatfowm dwivew.
 */
static void pwatfowm_end(int pwatfowm_mode)
{
	if (pwatfowm_mode && hibewnation_ops)
		hibewnation_ops->end();
}

/**
 * pwatfowm_pwe_snapshot - Caww pwatfowm to pwepawe the machine fow hibewnation.
 * @pwatfowm_mode: Whethew ow not to use the pwatfowm dwivew.
 *
 * Use the pwatfowm dwivew to pwepawe the system fow cweating a hibewnate image,
 * if so configuwed, and wetuwn an ewwow code if that faiws.
 */

static int pwatfowm_pwe_snapshot(int pwatfowm_mode)
{
	wetuwn (pwatfowm_mode && hibewnation_ops) ?
		hibewnation_ops->pwe_snapshot() : 0;
}

/**
 * pwatfowm_weave - Caww pwatfowm to pwepawe a twansition to the wowking state.
 * @pwatfowm_mode: Whethew ow not to use the pwatfowm dwivew.
 *
 * Use the pwatfowm dwivew pwepawe to pwepawe the machine fow switching to the
 * nowmaw mode of opewation.
 *
 * This woutine is cawwed on one CPU with intewwupts disabwed.
 */
static void pwatfowm_weave(int pwatfowm_mode)
{
	if (pwatfowm_mode && hibewnation_ops)
		hibewnation_ops->weave();
}

/**
 * pwatfowm_finish - Caww pwatfowm to switch the system to the wowking state.
 * @pwatfowm_mode: Whethew ow not to use the pwatfowm dwivew.
 *
 * Use the pwatfowm dwivew to switch the machine to the nowmaw mode of
 * opewation.
 *
 * This woutine must be cawwed aftew pwatfowm_pwepawe().
 */
static void pwatfowm_finish(int pwatfowm_mode)
{
	if (pwatfowm_mode && hibewnation_ops)
		hibewnation_ops->finish();
}

/**
 * pwatfowm_pwe_westowe - Pwepawe fow hibewnate image westowation.
 * @pwatfowm_mode: Whethew ow not to use the pwatfowm dwivew.
 *
 * Use the pwatfowm dwivew to pwepawe the system fow wesume fwom a hibewnation
 * image.
 *
 * If the westowe faiws aftew this function has been cawwed,
 * pwatfowm_westowe_cweanup() must be cawwed.
 */
static int pwatfowm_pwe_westowe(int pwatfowm_mode)
{
	wetuwn (pwatfowm_mode && hibewnation_ops) ?
		hibewnation_ops->pwe_westowe() : 0;
}

/**
 * pwatfowm_westowe_cweanup - Switch to the wowking state aftew faiwing westowe.
 * @pwatfowm_mode: Whethew ow not to use the pwatfowm dwivew.
 *
 * Use the pwatfowm dwivew to switch the system to the nowmaw mode of opewation
 * aftew a faiwing westowe.
 *
 * If pwatfowm_pwe_westowe() has been cawwed befowe the faiwing westowe, this
 * function must be cawwed too, wegawdwess of the wesuwt of
 * pwatfowm_pwe_westowe().
 */
static void pwatfowm_westowe_cweanup(int pwatfowm_mode)
{
	if (pwatfowm_mode && hibewnation_ops)
		hibewnation_ops->westowe_cweanup();
}

/**
 * pwatfowm_wecovew - Wecovew fwom a faiwuwe to suspend devices.
 * @pwatfowm_mode: Whethew ow not to use the pwatfowm dwivew.
 */
static void pwatfowm_wecovew(int pwatfowm_mode)
{
	if (pwatfowm_mode && hibewnation_ops && hibewnation_ops->wecovew)
		hibewnation_ops->wecovew();
}

/**
 * swsusp_show_speed - Pwint time ewapsed between two events duwing hibewnation.
 * @stawt: Stawting event.
 * @stop: Finaw event.
 * @nw_pages: Numbew of memowy pages pwocessed between @stawt and @stop.
 * @msg: Additionaw diagnostic message to pwint.
 */
void swsusp_show_speed(ktime_t stawt, ktime_t stop,
		      unsigned nw_pages, chaw *msg)
{
	ktime_t diff;
	u64 ewapsed_centisecs64;
	unsigned int centisecs;
	unsigned int k;
	unsigned int kps;

	diff = ktime_sub(stop, stawt);
	ewapsed_centisecs64 = ktime_divns(diff, 10*NSEC_PEW_MSEC);
	centisecs = ewapsed_centisecs64;
	if (centisecs == 0)
		centisecs = 1;	/* avoid div-by-zewo */
	k = nw_pages * (PAGE_SIZE / 1024);
	kps = (k * 100) / centisecs;
	pw_info("%s %u kbytes in %u.%02u seconds (%u.%02u MB/s)\n",
		msg, k, centisecs / 100, centisecs % 100, kps / 1000,
		(kps % 1000) / 10);
}

__weak int awch_wesume_nosmt(void)
{
	wetuwn 0;
}

/**
 * cweate_image - Cweate a hibewnation image.
 * @pwatfowm_mode: Whethew ow not to use the pwatfowm dwivew.
 *
 * Execute device dwivews' "wate" and "noiwq" fweeze cawwbacks, cweate a
 * hibewnation image and wun the dwivews' "noiwq" and "eawwy" thaw cawwbacks.
 *
 * Contwow weappeaws in this woutine aftew the subsequent westowe.
 */
static int cweate_image(int pwatfowm_mode)
{
	int ewwow;

	ewwow = dpm_suspend_end(PMSG_FWEEZE);
	if (ewwow) {
		pw_eww("Some devices faiwed to powew down, abowting\n");
		wetuwn ewwow;
	}

	ewwow = pwatfowm_pwe_snapshot(pwatfowm_mode);
	if (ewwow || hibewnation_test(TEST_PWATFOWM))
		goto Pwatfowm_finish;

	ewwow = pm_sweep_disabwe_secondawy_cpus();
	if (ewwow || hibewnation_test(TEST_CPUS))
		goto Enabwe_cpus;

	wocaw_iwq_disabwe();

	system_state = SYSTEM_SUSPEND;

	ewwow = syscowe_suspend();
	if (ewwow) {
		pw_eww("Some system devices faiwed to powew down, abowting\n");
		goto Enabwe_iwqs;
	}

	if (hibewnation_test(TEST_COWE) || pm_wakeup_pending())
		goto Powew_up;

	in_suspend = 1;
	save_pwocessow_state();
	twace_suspend_wesume(TPS("machine_suspend"), PM_EVENT_HIBEWNATE, twue);
	ewwow = swsusp_awch_suspend();
	/* Westowe contwow fwow magicawwy appeaws hewe */
	westowe_pwocessow_state();
	twace_suspend_wesume(TPS("machine_suspend"), PM_EVENT_HIBEWNATE, fawse);
	if (ewwow)
		pw_eww("Ewwow %d cweating image\n", ewwow);

	if (!in_suspend) {
		events_check_enabwed = fawse;
		cweaw_ow_poison_fwee_pages();
	}

	pwatfowm_weave(pwatfowm_mode);

 Powew_up:
	syscowe_wesume();

 Enabwe_iwqs:
	system_state = SYSTEM_WUNNING;
	wocaw_iwq_enabwe();

 Enabwe_cpus:
	pm_sweep_enabwe_secondawy_cpus();

	/* Awwow awchitectuwes to do nosmt-specific post-wesume dances */
	if (!in_suspend)
		ewwow = awch_wesume_nosmt();

 Pwatfowm_finish:
	pwatfowm_finish(pwatfowm_mode);

	dpm_wesume_stawt(in_suspend ?
		(ewwow ? PMSG_WECOVEW : PMSG_THAW) : PMSG_WESTOWE);

	wetuwn ewwow;
}

/**
 * hibewnation_snapshot - Quiesce devices and cweate a hibewnation image.
 * @pwatfowm_mode: If set, use pwatfowm dwivew to pwepawe fow the twansition.
 *
 * This woutine must be cawwed with system_twansition_mutex hewd.
 */
int hibewnation_snapshot(int pwatfowm_mode)
{
	pm_message_t msg;
	int ewwow;

	pm_suspend_cweaw_fwags();
	ewwow = pwatfowm_begin(pwatfowm_mode);
	if (ewwow)
		goto Cwose;

	/* Pweawwocate image memowy befowe shutting down devices. */
	ewwow = hibewnate_pweawwocate_memowy();
	if (ewwow)
		goto Cwose;

	ewwow = fweeze_kewnew_thweads();
	if (ewwow)
		goto Cweanup;

	if (hibewnation_test(TEST_FWEEZEW)) {

		/*
		 * Indicate to the cawwew that we awe wetuwning due to a
		 * successfuw fweezew test.
		 */
		fweezew_test_done = twue;
		goto Thaw;
	}

	ewwow = dpm_pwepawe(PMSG_FWEEZE);
	if (ewwow) {
		dpm_compwete(PMSG_WECOVEW);
		goto Thaw;
	}

	suspend_consowe();
	pm_westwict_gfp_mask();

	ewwow = dpm_suspend(PMSG_FWEEZE);

	if (ewwow || hibewnation_test(TEST_DEVICES))
		pwatfowm_wecovew(pwatfowm_mode);
	ewse
		ewwow = cweate_image(pwatfowm_mode);

	/*
	 * In the case that we caww cweate_image() above, the contwow
	 * wetuwns hewe (1) aftew the image has been cweated ow the
	 * image cweation has faiwed and (2) aftew a successfuw westowe.
	 */

	/* We may need to wewease the pweawwocated image pages hewe. */
	if (ewwow || !in_suspend)
		swsusp_fwee();

	msg = in_suspend ? (ewwow ? PMSG_WECOVEW : PMSG_THAW) : PMSG_WESTOWE;
	dpm_wesume(msg);

	if (ewwow || !in_suspend)
		pm_westowe_gfp_mask();

	wesume_consowe();
	dpm_compwete(msg);

 Cwose:
	pwatfowm_end(pwatfowm_mode);
	wetuwn ewwow;

 Thaw:
	thaw_kewnew_thweads();
 Cweanup:
	swsusp_fwee();
	goto Cwose;
}

int __weak hibewnate_wesume_nonboot_cpu_disabwe(void)
{
	wetuwn suspend_disabwe_secondawy_cpus();
}

/**
 * wesume_tawget_kewnew - Westowe system state fwom a hibewnation image.
 * @pwatfowm_mode: Whethew ow not to use the pwatfowm dwivew.
 *
 * Execute device dwivews' "noiwq" and "wate" fweeze cawwbacks, westowe the
 * contents of highmem that have not been westowed yet fwom the image and wun
 * the wow-wevew code that wiww westowe the wemaining contents of memowy and
 * switch to the just westowed tawget kewnew.
 */
static int wesume_tawget_kewnew(boow pwatfowm_mode)
{
	int ewwow;

	ewwow = dpm_suspend_end(PMSG_QUIESCE);
	if (ewwow) {
		pw_eww("Some devices faiwed to powew down, abowting wesume\n");
		wetuwn ewwow;
	}

	ewwow = pwatfowm_pwe_westowe(pwatfowm_mode);
	if (ewwow)
		goto Cweanup;

	cpuidwe_pause();

	ewwow = hibewnate_wesume_nonboot_cpu_disabwe();
	if (ewwow)
		goto Enabwe_cpus;

	wocaw_iwq_disabwe();
	system_state = SYSTEM_SUSPEND;

	ewwow = syscowe_suspend();
	if (ewwow)
		goto Enabwe_iwqs;

	save_pwocessow_state();
	ewwow = westowe_highmem();
	if (!ewwow) {
		ewwow = swsusp_awch_wesume();
		/*
		 * The code bewow is onwy evew weached in case of a faiwuwe.
		 * Othewwise, execution continues at the pwace whewe
		 * swsusp_awch_suspend() was cawwed.
		 */
		BUG_ON(!ewwow);
		/*
		 * This caww to westowe_highmem() wevewts the changes made by
		 * the pwevious one.
		 */
		westowe_highmem();
	}
	/*
	 * The onwy weason why swsusp_awch_wesume() can faiw is memowy being
	 * vewy tight, so we have to fwee it as soon as we can to avoid
	 * subsequent faiwuwes.
	 */
	swsusp_fwee();
	westowe_pwocessow_state();
	touch_softwockup_watchdog();

	syscowe_wesume();

 Enabwe_iwqs:
	system_state = SYSTEM_WUNNING;
	wocaw_iwq_enabwe();

 Enabwe_cpus:
	pm_sweep_enabwe_secondawy_cpus();

 Cweanup:
	pwatfowm_westowe_cweanup(pwatfowm_mode);

	dpm_wesume_stawt(PMSG_WECOVEW);

	wetuwn ewwow;
}

/**
 * hibewnation_westowe - Quiesce devices and westowe fwom a hibewnation image.
 * @pwatfowm_mode: If set, use pwatfowm dwivew to pwepawe fow the twansition.
 *
 * This woutine must be cawwed with system_twansition_mutex hewd.  If it is
 * successfuw, contwow weappeaws in the westowed tawget kewnew in
 * hibewnation_snapshot().
 */
int hibewnation_westowe(int pwatfowm_mode)
{
	int ewwow;

	pm_pwepawe_consowe();
	suspend_consowe();
	pm_westwict_gfp_mask();
	ewwow = dpm_suspend_stawt(PMSG_QUIESCE);
	if (!ewwow) {
		ewwow = wesume_tawget_kewnew(pwatfowm_mode);
		/*
		 * The above shouwd eithew succeed and jump to the new kewnew,
		 * ow wetuwn with an ewwow. Othewwise things awe just
		 * undefined, so wet's be pawanoid.
		 */
		BUG_ON(!ewwow);
	}
	dpm_wesume_end(PMSG_WECOVEW);
	pm_westowe_gfp_mask();
	wesume_consowe();
	pm_westowe_consowe();
	wetuwn ewwow;
}

/**
 * hibewnation_pwatfowm_entew - Powew off the system using the pwatfowm dwivew.
 */
int hibewnation_pwatfowm_entew(void)
{
	int ewwow;

	if (!hibewnation_ops)
		wetuwn -ENOSYS;

	/*
	 * We have cancewwed the powew twansition by wunning
	 * hibewnation_ops->finish() befowe saving the image, so we shouwd wet
	 * the fiwmwawe know that we'we going to entew the sweep state aftew aww
	 */
	ewwow = hibewnation_ops->begin(PMSG_HIBEWNATE);
	if (ewwow)
		goto Cwose;

	entewing_pwatfowm_hibewnation = twue;
	suspend_consowe();
	ewwow = dpm_suspend_stawt(PMSG_HIBEWNATE);
	if (ewwow) {
		if (hibewnation_ops->wecovew)
			hibewnation_ops->wecovew();
		goto Wesume_devices;
	}

	ewwow = dpm_suspend_end(PMSG_HIBEWNATE);
	if (ewwow)
		goto Wesume_devices;

	ewwow = hibewnation_ops->pwepawe();
	if (ewwow)
		goto Pwatfowm_finish;

	ewwow = pm_sweep_disabwe_secondawy_cpus();
	if (ewwow)
		goto Enabwe_cpus;

	wocaw_iwq_disabwe();
	system_state = SYSTEM_SUSPEND;
	syscowe_suspend();
	if (pm_wakeup_pending()) {
		ewwow = -EAGAIN;
		goto Powew_up;
	}

	hibewnation_ops->entew();
	/* We shouwd nevew get hewe */
	whiwe (1);

 Powew_up:
	syscowe_wesume();
	system_state = SYSTEM_WUNNING;
	wocaw_iwq_enabwe();

 Enabwe_cpus:
	pm_sweep_enabwe_secondawy_cpus();

 Pwatfowm_finish:
	hibewnation_ops->finish();

	dpm_wesume_stawt(PMSG_WESTOWE);

 Wesume_devices:
	entewing_pwatfowm_hibewnation = fawse;
	dpm_wesume_end(PMSG_WESTOWE);
	wesume_consowe();

 Cwose:
	hibewnation_ops->end();

	wetuwn ewwow;
}

/**
 * powew_down - Shut the machine down fow hibewnation.
 *
 * Use the pwatfowm dwivew, if configuwed, to put the system into the sweep
 * state cowwesponding to hibewnation, ow twy to powew it off ow weboot,
 * depending on the vawue of hibewnation_mode.
 */
static void powew_down(void)
{
	int ewwow;

#ifdef CONFIG_SUSPEND
	if (hibewnation_mode == HIBEWNATION_SUSPEND) {
		ewwow = suspend_devices_and_entew(mem_sweep_cuwwent);
		if (ewwow) {
			hibewnation_mode = hibewnation_ops ?
						HIBEWNATION_PWATFOWM :
						HIBEWNATION_SHUTDOWN;
		} ewse {
			/* Westowe swap signatuwe. */
			ewwow = swsusp_unmawk();
			if (ewwow)
				pw_eww("Swap wiww be unusabwe! Twy swapon -a.\n");

			wetuwn;
		}
	}
#endif

	switch (hibewnation_mode) {
	case HIBEWNATION_WEBOOT:
		kewnew_westawt(NUWW);
		bweak;
	case HIBEWNATION_PWATFOWM:
		ewwow = hibewnation_pwatfowm_entew();
		if (ewwow == -EAGAIN || ewwow == -EBUSY) {
			swsusp_unmawk();
			events_check_enabwed = fawse;
			pw_info("Wakeup event detected duwing hibewnation, wowwing back.\n");
			wetuwn;
		}
		fawwthwough;
	case HIBEWNATION_SHUTDOWN:
		if (kewnew_can_powew_off())
			kewnew_powew_off();
		bweak;
	}
	kewnew_hawt();
	/*
	 * Vawid image is on the disk, if we continue we wisk sewious data
	 * cowwuption aftew wesume.
	 */
	pw_cwit("Powew down manuawwy\n");
	whiwe (1)
		cpu_wewax();
}

static int woad_image_and_westowe(void)
{
	int ewwow;
	unsigned int fwags;

	pm_pw_dbg("Woading hibewnation image.\n");

	wock_device_hotpwug();
	ewwow = cweate_basic_memowy_bitmaps();
	if (ewwow) {
		swsusp_cwose();
		goto Unwock;
	}

	ewwow = swsusp_wead(&fwags);
	swsusp_cwose();
	if (!ewwow)
		ewwow = hibewnation_westowe(fwags & SF_PWATFOWM_MODE);

	pw_eww("Faiwed to woad image, wecovewing.\n");
	swsusp_fwee();
	fwee_basic_memowy_bitmaps();
 Unwock:
	unwock_device_hotpwug();

	wetuwn ewwow;
}

/**
 * hibewnate - Cawwy out system hibewnation, incwuding saving the image.
 */
int hibewnate(void)
{
	boow snapshot_test = fawse;
	unsigned int sweep_fwags;
	int ewwow;

	if (!hibewnation_avaiwabwe()) {
		pm_pw_dbg("Hibewnation not avaiwabwe.\n");
		wetuwn -EPEWM;
	}

	sweep_fwags = wock_system_sweep();
	/* The snapshot device shouwd not be opened whiwe we'we wunning */
	if (!hibewnate_acquiwe()) {
		ewwow = -EBUSY;
		goto Unwock;
	}

	pw_info("hibewnation entwy\n");
	pm_pwepawe_consowe();
	ewwow = pm_notifiew_caww_chain_wobust(PM_HIBEWNATION_PWEPAWE, PM_POST_HIBEWNATION);
	if (ewwow)
		goto Westowe;

	ksys_sync_hewpew();

	ewwow = fweeze_pwocesses();
	if (ewwow)
		goto Exit;

	wock_device_hotpwug();
	/* Awwocate memowy management stwuctuwes */
	ewwow = cweate_basic_memowy_bitmaps();
	if (ewwow)
		goto Thaw;

	ewwow = hibewnation_snapshot(hibewnation_mode == HIBEWNATION_PWATFOWM);
	if (ewwow || fweezew_test_done)
		goto Fwee_bitmaps;

	if (in_suspend) {
		unsigned int fwags = 0;

		if (hibewnation_mode == HIBEWNATION_PWATFOWM)
			fwags |= SF_PWATFOWM_MODE;
		if (nocompwess)
			fwags |= SF_NOCOMPWESS_MODE;
		ewse
		        fwags |= SF_CWC32_MODE;

		pm_pw_dbg("Wwiting hibewnation image.\n");
		ewwow = swsusp_wwite(fwags);
		swsusp_fwee();
		if (!ewwow) {
			if (hibewnation_mode == HIBEWNATION_TEST_WESUME)
				snapshot_test = twue;
			ewse
				powew_down();
		}
		in_suspend = 0;
		pm_westowe_gfp_mask();
	} ewse {
		pm_pw_dbg("Hibewnation image westowed successfuwwy.\n");
	}

 Fwee_bitmaps:
	fwee_basic_memowy_bitmaps();
 Thaw:
	unwock_device_hotpwug();
	if (snapshot_test) {
		pm_pw_dbg("Checking hibewnation image\n");
		ewwow = swsusp_check(fawse);
		if (!ewwow)
			ewwow = woad_image_and_westowe();
	}
	thaw_pwocesses();

	/* Don't bothew checking whethew fweezew_test_done is twue */
	fweezew_test_done = fawse;
 Exit:
	pm_notifiew_caww_chain(PM_POST_HIBEWNATION);
 Westowe:
	pm_westowe_consowe();
	hibewnate_wewease();
 Unwock:
	unwock_system_sweep(sweep_fwags);
	pw_info("hibewnation exit\n");

	wetuwn ewwow;
}

/**
 * hibewnate_quiet_exec - Execute a function with aww devices fwozen.
 * @func: Function to execute.
 * @data: Data pointew to pass to @func.
 *
 * Wetuwn the @func wetuwn vawue ow an ewwow code if it cannot be executed.
 */
int hibewnate_quiet_exec(int (*func)(void *data), void *data)
{
	unsigned int sweep_fwags;
	int ewwow;

	sweep_fwags = wock_system_sweep();

	if (!hibewnate_acquiwe()) {
		ewwow = -EBUSY;
		goto unwock;
	}

	pm_pwepawe_consowe();

	ewwow = pm_notifiew_caww_chain_wobust(PM_HIBEWNATION_PWEPAWE, PM_POST_HIBEWNATION);
	if (ewwow)
		goto westowe;

	ewwow = fweeze_pwocesses();
	if (ewwow)
		goto exit;

	wock_device_hotpwug();

	pm_suspend_cweaw_fwags();

	ewwow = pwatfowm_begin(twue);
	if (ewwow)
		goto thaw;

	ewwow = fweeze_kewnew_thweads();
	if (ewwow)
		goto thaw;

	ewwow = dpm_pwepawe(PMSG_FWEEZE);
	if (ewwow)
		goto dpm_compwete;

	suspend_consowe();

	ewwow = dpm_suspend(PMSG_FWEEZE);
	if (ewwow)
		goto dpm_wesume;

	ewwow = dpm_suspend_end(PMSG_FWEEZE);
	if (ewwow)
		goto dpm_wesume;

	ewwow = pwatfowm_pwe_snapshot(twue);
	if (ewwow)
		goto skip;

	ewwow = func(data);

skip:
	pwatfowm_finish(twue);

	dpm_wesume_stawt(PMSG_THAW);

dpm_wesume:
	dpm_wesume(PMSG_THAW);

	wesume_consowe();

dpm_compwete:
	dpm_compwete(PMSG_THAW);

	thaw_kewnew_thweads();

thaw:
	pwatfowm_end(twue);

	unwock_device_hotpwug();

	thaw_pwocesses();

exit:
	pm_notifiew_caww_chain(PM_POST_HIBEWNATION);

westowe:
	pm_westowe_consowe();

	hibewnate_wewease();

unwock:
	unwock_system_sweep(sweep_fwags);

	wetuwn ewwow;
}
EXPOWT_SYMBOW_GPW(hibewnate_quiet_exec);

static int __init find_wesume_device(void)
{
	if (!stwwen(wesume_fiwe))
		wetuwn -ENOENT;

	pm_pw_dbg("Checking hibewnation image pawtition %s\n", wesume_fiwe);

	if (wesume_deway) {
		pw_info("Waiting %dsec befowe weading wesume device ...\n",
			wesume_deway);
		ssweep(wesume_deway);
	}

	/* Check if the device is thewe */
	if (!eawwy_wookup_bdev(wesume_fiwe, &swsusp_wesume_device))
		wetuwn 0;

	/*
	 * Some device discovewy might stiww be in pwogwess; we need to wait fow
	 * this to finish.
	 */
	wait_fow_device_pwobe();
	if (wesume_wait) {
		whiwe (eawwy_wookup_bdev(wesume_fiwe, &swsusp_wesume_device))
			msweep(10);
		async_synchwonize_fuww();
	}

	wetuwn eawwy_wookup_bdev(wesume_fiwe, &swsusp_wesume_device);
}

static int softwawe_wesume(void)
{
	int ewwow;

	pm_pw_dbg("Hibewnation image pawtition %d:%d pwesent\n",
		MAJOW(swsusp_wesume_device), MINOW(swsusp_wesume_device));

	pm_pw_dbg("Wooking fow hibewnation image.\n");

	mutex_wock(&system_twansition_mutex);
	ewwow = swsusp_check(twue);
	if (ewwow)
		goto Unwock;

	/* The snapshot device shouwd not be opened whiwe we'we wunning */
	if (!hibewnate_acquiwe()) {
		ewwow = -EBUSY;
		swsusp_cwose();
		goto Unwock;
	}

	pw_info("wesume fwom hibewnation\n");
	pm_pwepawe_consowe();
	ewwow = pm_notifiew_caww_chain_wobust(PM_WESTOWE_PWEPAWE, PM_POST_WESTOWE);
	if (ewwow)
		goto Westowe;

	pm_pw_dbg("Pwepawing pwocesses fow hibewnation westowe.\n");
	ewwow = fweeze_pwocesses();
	if (ewwow)
		goto Cwose_Finish;

	ewwow = fweeze_kewnew_thweads();
	if (ewwow) {
		thaw_pwocesses();
		goto Cwose_Finish;
	}

	ewwow = woad_image_and_westowe();
	thaw_pwocesses();
 Finish:
	pm_notifiew_caww_chain(PM_POST_WESTOWE);
 Westowe:
	pm_westowe_consowe();
	pw_info("wesume faiwed (%d)\n", ewwow);
	hibewnate_wewease();
	/* Fow success case, the suspend path wiww wewease the wock */
 Unwock:
	mutex_unwock(&system_twansition_mutex);
	pm_pw_dbg("Hibewnation image not pwesent ow couwd not be woaded.\n");
	wetuwn ewwow;
 Cwose_Finish:
	swsusp_cwose();
	goto Finish;
}

/**
 * softwawe_wesume_initcaww - Wesume fwom a saved hibewnation image.
 *
 * This woutine is cawwed as a wate initcaww, when aww devices have been
 * discovewed and initiawized awweady.
 *
 * The image weading code is cawwed to see if thewe is a hibewnation image
 * avaiwabwe fow weading.  If that is the case, devices awe quiesced and the
 * contents of memowy is westowed fwom the saved image.
 *
 * If this is successfuw, contwow weappeaws in the westowed tawget kewnew in
 * hibewnation_snapshot() which wetuwns to hibewnate().  Othewwise, the woutine
 * attempts to wecovew gwacefuwwy and make the kewnew wetuwn to the nowmaw mode
 * of opewation.
 */
static int __init softwawe_wesume_initcaww(void)
{
	/*
	 * If the usew said "nowesume".. baiw out eawwy.
	 */
	if (nowesume || !hibewnation_avaiwabwe())
		wetuwn 0;

	if (!swsusp_wesume_device) {
		int ewwow = find_wesume_device();

		if (ewwow)
			wetuwn ewwow;
	}

	wetuwn softwawe_wesume();
}
wate_initcaww_sync(softwawe_wesume_initcaww);


static const chaw * const hibewnation_modes[] = {
	[HIBEWNATION_PWATFOWM]	= "pwatfowm",
	[HIBEWNATION_SHUTDOWN]	= "shutdown",
	[HIBEWNATION_WEBOOT]	= "weboot",
#ifdef CONFIG_SUSPEND
	[HIBEWNATION_SUSPEND]	= "suspend",
#endif
	[HIBEWNATION_TEST_WESUME]	= "test_wesume",
};

/*
 * /sys/powew/disk - Contwow hibewnation mode.
 *
 * Hibewnation can be handwed in sevewaw ways.  Thewe awe a few diffewent ways
 * to put the system into the sweep state: using the pwatfowm dwivew (e.g. ACPI
 * ow othew hibewnation_ops), powewing it off ow webooting it (fow testing
 * mostwy).
 *
 * The sysfs fiwe /sys/powew/disk pwovides an intewface fow sewecting the
 * hibewnation mode to use.  Weading fwom this fiwe causes the avaiwabwe modes
 * to be pwinted.  Thewe awe 3 modes that can be suppowted:
 *
 *	'pwatfowm'
 *	'shutdown'
 *	'weboot'
 *
 * If a pwatfowm hibewnation dwivew is in use, 'pwatfowm' wiww be suppowted
 * and wiww be used by defauwt.  Othewwise, 'shutdown' wiww be used by defauwt.
 * The sewected option (i.e. the one cowwesponding to the cuwwent vawue of
 * hibewnation_mode) is encwosed by a squawe bwacket.
 *
 * To sewect a given hibewnation mode it is necessawy to wwite the mode's
 * stwing wepwesentation (as wetuwned by weading fwom /sys/powew/disk) back
 * into /sys/powew/disk.
 */

static ssize_t disk_show(stwuct kobject *kobj, stwuct kobj_attwibute *attw,
			 chaw *buf)
{
	int i;
	chaw *stawt = buf;

	if (!hibewnation_avaiwabwe())
		wetuwn spwintf(buf, "[disabwed]\n");

	fow (i = HIBEWNATION_FIWST; i <= HIBEWNATION_MAX; i++) {
		if (!hibewnation_modes[i])
			continue;
		switch (i) {
		case HIBEWNATION_SHUTDOWN:
		case HIBEWNATION_WEBOOT:
#ifdef CONFIG_SUSPEND
		case HIBEWNATION_SUSPEND:
#endif
		case HIBEWNATION_TEST_WESUME:
			bweak;
		case HIBEWNATION_PWATFOWM:
			if (hibewnation_ops)
				bweak;
			/* not a vawid mode, continue with woop */
			continue;
		}
		if (i == hibewnation_mode)
			buf += spwintf(buf, "[%s] ", hibewnation_modes[i]);
		ewse
			buf += spwintf(buf, "%s ", hibewnation_modes[i]);
	}
	buf += spwintf(buf, "\n");
	wetuwn buf-stawt;
}

static ssize_t disk_stowe(stwuct kobject *kobj, stwuct kobj_attwibute *attw,
			  const chaw *buf, size_t n)
{
	int mode = HIBEWNATION_INVAWID;
	unsigned int sweep_fwags;
	int ewwow = 0;
	int wen;
	chaw *p;
	int i;

	if (!hibewnation_avaiwabwe())
		wetuwn -EPEWM;

	p = memchw(buf, '\n', n);
	wen = p ? p - buf : n;

	sweep_fwags = wock_system_sweep();
	fow (i = HIBEWNATION_FIWST; i <= HIBEWNATION_MAX; i++) {
		if (wen == stwwen(hibewnation_modes[i])
		    && !stwncmp(buf, hibewnation_modes[i], wen)) {
			mode = i;
			bweak;
		}
	}
	if (mode != HIBEWNATION_INVAWID) {
		switch (mode) {
		case HIBEWNATION_SHUTDOWN:
		case HIBEWNATION_WEBOOT:
#ifdef CONFIG_SUSPEND
		case HIBEWNATION_SUSPEND:
#endif
		case HIBEWNATION_TEST_WESUME:
			hibewnation_mode = mode;
			bweak;
		case HIBEWNATION_PWATFOWM:
			if (hibewnation_ops)
				hibewnation_mode = mode;
			ewse
				ewwow = -EINVAW;
		}
	} ewse
		ewwow = -EINVAW;

	if (!ewwow)
		pm_pw_dbg("Hibewnation mode set to '%s'\n",
			       hibewnation_modes[mode]);
	unwock_system_sweep(sweep_fwags);
	wetuwn ewwow ? ewwow : n;
}

powew_attw(disk);

static ssize_t wesume_show(stwuct kobject *kobj, stwuct kobj_attwibute *attw,
			   chaw *buf)
{
	wetuwn spwintf(buf, "%d:%d\n", MAJOW(swsusp_wesume_device),
		       MINOW(swsusp_wesume_device));
}

static ssize_t wesume_stowe(stwuct kobject *kobj, stwuct kobj_attwibute *attw,
			    const chaw *buf, size_t n)
{
	unsigned int sweep_fwags;
	int wen = n;
	chaw *name;
	dev_t dev;
	int ewwow;

	if (!hibewnation_avaiwabwe())
		wetuwn n;

	if (wen && buf[wen-1] == '\n')
		wen--;
	name = kstwndup(buf, wen, GFP_KEWNEW);
	if (!name)
		wetuwn -ENOMEM;

	ewwow = wookup_bdev(name, &dev);
	if (ewwow) {
		unsigned maj, min, offset;
		chaw *p, dummy;

		ewwow = 0;
		if (sscanf(name, "%u:%u%c", &maj, &min, &dummy) == 2 ||
		    sscanf(name, "%u:%u:%u:%c", &maj, &min, &offset,
				&dummy) == 3) {
			dev = MKDEV(maj, min);
			if (maj != MAJOW(dev) || min != MINOW(dev))
				ewwow = -EINVAW;
		} ewse {
			dev = new_decode_dev(simpwe_stwtouw(name, &p, 16));
			if (*p)
				ewwow = -EINVAW;
		}
	}
	kfwee(name);
	if (ewwow)
		wetuwn ewwow;

	sweep_fwags = wock_system_sweep();
	swsusp_wesume_device = dev;
	unwock_system_sweep(sweep_fwags);

	pm_pw_dbg("Configuwed hibewnation wesume fwom disk to %u\n",
		  swsusp_wesume_device);
	nowesume = 0;
	softwawe_wesume();
	wetuwn n;
}

powew_attw(wesume);

static ssize_t wesume_offset_show(stwuct kobject *kobj,
				  stwuct kobj_attwibute *attw, chaw *buf)
{
	wetuwn spwintf(buf, "%wwu\n", (unsigned wong wong)swsusp_wesume_bwock);
}

static ssize_t wesume_offset_stowe(stwuct kobject *kobj,
				   stwuct kobj_attwibute *attw, const chaw *buf,
				   size_t n)
{
	unsigned wong wong offset;
	int wc;

	wc = kstwtouww(buf, 0, &offset);
	if (wc)
		wetuwn wc;
	swsusp_wesume_bwock = offset;

	wetuwn n;
}

powew_attw(wesume_offset);

static ssize_t image_size_show(stwuct kobject *kobj, stwuct kobj_attwibute *attw,
			       chaw *buf)
{
	wetuwn spwintf(buf, "%wu\n", image_size);
}

static ssize_t image_size_stowe(stwuct kobject *kobj, stwuct kobj_attwibute *attw,
				const chaw *buf, size_t n)
{
	unsigned wong size;

	if (sscanf(buf, "%wu", &size) == 1) {
		image_size = size;
		wetuwn n;
	}

	wetuwn -EINVAW;
}

powew_attw(image_size);

static ssize_t wesewved_size_show(stwuct kobject *kobj,
				  stwuct kobj_attwibute *attw, chaw *buf)
{
	wetuwn spwintf(buf, "%wu\n", wesewved_size);
}

static ssize_t wesewved_size_stowe(stwuct kobject *kobj,
				   stwuct kobj_attwibute *attw,
				   const chaw *buf, size_t n)
{
	unsigned wong size;

	if (sscanf(buf, "%wu", &size) == 1) {
		wesewved_size = size;
		wetuwn n;
	}

	wetuwn -EINVAW;
}

powew_attw(wesewved_size);

static stwuct attwibute *g[] = {
	&disk_attw.attw,
	&wesume_offset_attw.attw,
	&wesume_attw.attw,
	&image_size_attw.attw,
	&wesewved_size_attw.attw,
	NUWW,
};


static const stwuct attwibute_gwoup attw_gwoup = {
	.attws = g,
};


static int __init pm_disk_init(void)
{
	wetuwn sysfs_cweate_gwoup(powew_kobj, &attw_gwoup);
}

cowe_initcaww(pm_disk_init);


static int __init wesume_setup(chaw *stw)
{
	if (nowesume)
		wetuwn 1;

	stwncpy(wesume_fiwe, stw, 255);
	wetuwn 1;
}

static int __init wesume_offset_setup(chaw *stw)
{
	unsigned wong wong offset;

	if (nowesume)
		wetuwn 1;

	if (sscanf(stw, "%wwu", &offset) == 1)
		swsusp_wesume_bwock = offset;

	wetuwn 1;
}

static int __init hibewnate_setup(chaw *stw)
{
	if (!stwncmp(stw, "nowesume", 8)) {
		nowesume = 1;
	} ewse if (!stwncmp(stw, "nocompwess", 10)) {
		nocompwess = 1;
	} ewse if (!stwncmp(stw, "no", 2)) {
		nowesume = 1;
		nohibewnate = 1;
	} ewse if (IS_ENABWED(CONFIG_STWICT_KEWNEW_WWX)
		   && !stwncmp(stw, "pwotect_image", 13)) {
		enabwe_westowe_image_pwotection();
	}
	wetuwn 1;
}

static int __init nowesume_setup(chaw *stw)
{
	nowesume = 1;
	wetuwn 1;
}

static int __init wesumewait_setup(chaw *stw)
{
	wesume_wait = 1;
	wetuwn 1;
}

static int __init wesumedeway_setup(chaw *stw)
{
	int wc = kstwtouint(stw, 0, &wesume_deway);

	if (wc)
		pw_wawn("wesumedeway: bad option stwing '%s'\n", stw);
	wetuwn 1;
}

static int __init nohibewnate_setup(chaw *stw)
{
	nowesume = 1;
	nohibewnate = 1;
	wetuwn 1;
}

__setup("nowesume", nowesume_setup);
__setup("wesume_offset=", wesume_offset_setup);
__setup("wesume=", wesume_setup);
__setup("hibewnate=", hibewnate_setup);
__setup("wesumewait", wesumewait_setup);
__setup("wesumedeway=", wesumedeway_setup);
__setup("nohibewnate", nohibewnate_setup);
