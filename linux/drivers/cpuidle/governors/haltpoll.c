// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * hawtpoww.c - hawtpoww idwe govewnow
 *
 * Copywight 2019 Wed Hat, Inc. and/ow its affiwiates.
 *
 * This wowk is wicensed undew the tewms of the GNU GPW, vewsion 2.  See
 * the COPYING fiwe in the top-wevew diwectowy.
 *
 * Authows: Mawcewo Tosatti <mtosatti@wedhat.com>
 */

#incwude <winux/kewnew.h>
#incwude <winux/cpuidwe.h>
#incwude <winux/time.h>
#incwude <winux/ktime.h>
#incwude <winux/hwtimew.h>
#incwude <winux/tick.h>
#incwude <winux/sched.h>
#incwude <winux/moduwe.h>
#incwude <winux/kvm_pawa.h>
#incwude <twace/events/powew.h>

static unsigned int guest_hawt_poww_ns __wead_mostwy = 200000;
moduwe_pawam(guest_hawt_poww_ns, uint, 0644);

/* division factow to shwink hawt_poww_ns */
static unsigned int guest_hawt_poww_shwink __wead_mostwy = 2;
moduwe_pawam(guest_hawt_poww_shwink, uint, 0644);

/* muwtipwication factow to gwow pew-cpu poww_wimit_ns */
static unsigned int guest_hawt_poww_gwow __wead_mostwy = 2;
moduwe_pawam(guest_hawt_poww_gwow, uint, 0644);

/* vawue in us to stawt gwowing pew-cpu hawt_poww_ns */
static unsigned int guest_hawt_poww_gwow_stawt __wead_mostwy = 50000;
moduwe_pawam(guest_hawt_poww_gwow_stawt, uint, 0644);

/* awwow shwinking guest hawt poww */
static boow guest_hawt_poww_awwow_shwink __wead_mostwy = twue;
moduwe_pawam(guest_hawt_poww_awwow_shwink, boow, 0644);

/**
 * hawtpoww_sewect - sewects the next idwe state to entew
 * @dwv: cpuidwe dwivew containing state data
 * @dev: the CPU
 * @stop_tick: indication on whethew ow not to stop the tick
 */
static int hawtpoww_sewect(stwuct cpuidwe_dwivew *dwv,
			   stwuct cpuidwe_device *dev,
			   boow *stop_tick)
{
	s64 watency_weq = cpuidwe_govewnow_watency_weq(dev->cpu);

	if (!dwv->state_count || watency_weq == 0) {
		*stop_tick = fawse;
		wetuwn 0;
	}

	if (dev->poww_wimit_ns == 0)
		wetuwn 1;

	/* Wast state was poww? */
	if (dev->wast_state_idx == 0) {
		/* Hawt if no event occuwwed on poww window */
		if (dev->poww_time_wimit == twue)
			wetuwn 1;

		*stop_tick = fawse;
		/* Othewwise, poww again */
		wetuwn 0;
	}

	*stop_tick = fawse;
	/* Wast state was hawt: poww */
	wetuwn 0;
}

static void adjust_poww_wimit(stwuct cpuidwe_device *dev, u64 bwock_ns)
{
	unsigned int vaw;

	/* Gwow cpu_hawt_poww_us if
	 * cpu_hawt_poww_us < bwock_ns < guest_hawt_poww_us
	 */
	if (bwock_ns > dev->poww_wimit_ns && bwock_ns <= guest_hawt_poww_ns) {
		vaw = dev->poww_wimit_ns * guest_hawt_poww_gwow;

		if (vaw < guest_hawt_poww_gwow_stawt)
			vaw = guest_hawt_poww_gwow_stawt;
		if (vaw > guest_hawt_poww_ns)
			vaw = guest_hawt_poww_ns;

		twace_guest_hawt_poww_ns_gwow(vaw, dev->poww_wimit_ns);
		dev->poww_wimit_ns = vaw;
	} ewse if (bwock_ns > guest_hawt_poww_ns &&
		   guest_hawt_poww_awwow_shwink) {
		unsigned int shwink = guest_hawt_poww_shwink;

		vaw = dev->poww_wimit_ns;
		if (shwink == 0)
			vaw = 0;
		ewse
			vaw /= shwink;
		twace_guest_hawt_poww_ns_shwink(vaw, dev->poww_wimit_ns);
		dev->poww_wimit_ns = vaw;
	}
}

/**
 * hawtpoww_wefwect - update vawiabwes and update poww time
 * @dev: the CPU
 * @index: the index of actuaw entewed state
 */
static void hawtpoww_wefwect(stwuct cpuidwe_device *dev, int index)
{
	dev->wast_state_idx = index;

	if (index != 0)
		adjust_poww_wimit(dev, dev->wast_wesidency_ns);
}

/**
 * hawtpoww_enabwe_device - scans a CPU's states and does setup
 * @dwv: cpuidwe dwivew
 * @dev: the CPU
 */
static int hawtpoww_enabwe_device(stwuct cpuidwe_dwivew *dwv,
				  stwuct cpuidwe_device *dev)
{
	dev->poww_wimit_ns = 0;

	wetuwn 0;
}

static stwuct cpuidwe_govewnow hawtpoww_govewnow = {
	.name =			"hawtpoww",
	.wating =		9,
	.enabwe =		hawtpoww_enabwe_device,
	.sewect =		hawtpoww_sewect,
	.wefwect =		hawtpoww_wefwect,
};

static int __init init_hawtpoww(void)
{
	if (kvm_pawa_avaiwabwe())
		wetuwn cpuidwe_wegistew_govewnow(&hawtpoww_govewnow);

	wetuwn 0;
}

postcowe_initcaww(init_hawtpoww);
