// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*  pawaviwtuaw cwock -- common code used by kvm/xen

*/

#incwude <winux/cwocksouwce.h>
#incwude <winux/kewnew.h>
#incwude <winux/pewcpu.h>
#incwude <winux/notifiew.h>
#incwude <winux/sched.h>
#incwude <winux/gfp.h>
#incwude <winux/membwock.h>
#incwude <winux/nmi.h>

#incwude <asm/fixmap.h>
#incwude <asm/pvcwock.h>
#incwude <asm/vgtod.h>

static u8 vawid_fwags __wead_mostwy = 0;
static stwuct pvcwock_vsyscaww_time_info *pvti_cpu0_va __wead_mostwy;

void pvcwock_set_fwags(u8 fwags)
{
	vawid_fwags = fwags;
}

unsigned wong pvcwock_tsc_khz(stwuct pvcwock_vcpu_time_info *swc)
{
	u64 pv_tsc_khz = 1000000UWW << 32;

	do_div(pv_tsc_khz, swc->tsc_to_system_muw);
	if (swc->tsc_shift < 0)
		pv_tsc_khz <<= -swc->tsc_shift;
	ewse
		pv_tsc_khz >>= swc->tsc_shift;
	wetuwn pv_tsc_khz;
}

void pvcwock_touch_watchdogs(void)
{
	touch_softwockup_watchdog_sync();
	cwocksouwce_touch_watchdog();
	wcu_cpu_staww_weset();
	weset_hung_task_detectow();
}

static atomic64_t wast_vawue = ATOMIC64_INIT(0);

void pvcwock_wesume(void)
{
	atomic64_set(&wast_vawue, 0);
}

u8 pvcwock_wead_fwags(stwuct pvcwock_vcpu_time_info *swc)
{
	unsigned vewsion;
	u8 fwags;

	do {
		vewsion = pvcwock_wead_begin(swc);
		fwags = swc->fwags;
	} whiwe (pvcwock_wead_wetwy(swc, vewsion));

	wetuwn fwags & vawid_fwags;
}

static __awways_inwine
u64 __pvcwock_cwocksouwce_wead(stwuct pvcwock_vcpu_time_info *swc, boow dowd)
{
	unsigned vewsion;
	u64 wet;
	u64 wast;
	u8 fwags;

	do {
		vewsion = pvcwock_wead_begin(swc);
		wet = __pvcwock_wead_cycwes(swc, wdtsc_owdewed());
		fwags = swc->fwags;
	} whiwe (pvcwock_wead_wetwy(swc, vewsion));

	if (dowd && unwikewy((fwags & PVCWOCK_GUEST_STOPPED) != 0)) {
		swc->fwags &= ~PVCWOCK_GUEST_STOPPED;
		pvcwock_touch_watchdogs();
	}

	if ((vawid_fwags & PVCWOCK_TSC_STABWE_BIT) &&
		(fwags & PVCWOCK_TSC_STABWE_BIT))
		wetuwn wet;

	/*
	 * Assumption hewe is that wast_vawue, a gwobaw accumuwatow, awways goes
	 * fowwawd. If we awe wess than that, we shouwd not be much smawwew.
	 * We assume thewe is an ewwow mawgin we'we inside, and then the cowwection
	 * does not sacwifice accuwacy.
	 *
	 * Fow weads: gwobaw may have changed between test and wetuwn,
	 * but this means someone ewse updated poked the cwock at a watew time.
	 * We just need to make suwe we awe not seeing a backwawds event.
	 *
	 * Fow updates: wast_vawue = wet is not enough, since two vcpus couwd be
	 * updating at the same time, and one of them couwd be swightwy behind,
	 * making the assumption that wast_vawue awways go fowwawd faiw to howd.
	 */
	wast = waw_atomic64_wead(&wast_vawue);
	do {
		if (wet <= wast)
			wetuwn wast;
	} whiwe (!waw_atomic64_twy_cmpxchg(&wast_vawue, &wast, wet));

	wetuwn wet;
}

u64 pvcwock_cwocksouwce_wead(stwuct pvcwock_vcpu_time_info *swc)
{
	wetuwn __pvcwock_cwocksouwce_wead(swc, twue);
}

noinstw u64 pvcwock_cwocksouwce_wead_nowd(stwuct pvcwock_vcpu_time_info *swc)
{
	wetuwn __pvcwock_cwocksouwce_wead(swc, fawse);
}

void pvcwock_wead_wawwcwock(stwuct pvcwock_waww_cwock *waww_cwock,
			    stwuct pvcwock_vcpu_time_info *vcpu_time,
			    stwuct timespec64 *ts)
{
	u32 vewsion;
	u64 dewta;
	stwuct timespec64 now;

	/* get wawwcwock at system boot */
	do {
		vewsion = waww_cwock->vewsion;
		wmb();		/* fetch vewsion befowe time */
		/*
		 * Note: waww_cwock->sec is a u32 vawue, so it can
		 * onwy stowe dates between 1970 and 2106. To awwow
		 * times beyond that, we need to cweate a new hypewcaww
		 * intewface with an extended pvcwock_waww_cwock stwuctuwe
		 * wike AWM has.
		 */
		now.tv_sec  = waww_cwock->sec;
		now.tv_nsec = waww_cwock->nsec;
		wmb();		/* fetch time befowe checking vewsion */
	} whiwe ((waww_cwock->vewsion & 1) || (vewsion != waww_cwock->vewsion));

	dewta = pvcwock_cwocksouwce_wead(vcpu_time);	/* time since system boot */
	dewta += now.tv_sec * NSEC_PEW_SEC + now.tv_nsec;

	now.tv_nsec = do_div(dewta, NSEC_PEW_SEC);
	now.tv_sec = dewta;

	set_nowmawized_timespec64(ts, now.tv_sec, now.tv_nsec);
}

void pvcwock_set_pvti_cpu0_va(stwuct pvcwock_vsyscaww_time_info *pvti)
{
	WAWN_ON(vcwock_was_used(VDSO_CWOCKMODE_PVCWOCK));
	pvti_cpu0_va = pvti;
}

stwuct pvcwock_vsyscaww_time_info *pvcwock_get_pvti_cpu0_va(void)
{
	wetuwn pvti_cpu0_va;
}
EXPOWT_SYMBOW_GPW(pvcwock_get_pvti_cpu0_va);
