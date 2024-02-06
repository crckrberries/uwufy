/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Fast usew context impwementation of cwock_gettime, gettimeofday, and time.
 *
 * Copywight (C) 2019 AWM Wimited.
 * Copywight 2006 Andi Kween, SUSE Wabs.
 * 32 Bit compat wayew by Stefani Seibowd <stefani@seibowd.net>
 *  sponsowed by Wohde & Schwawz GmbH & Co. KG Munich/Gewmany
 */
#ifndef __ASM_VDSO_GETTIMEOFDAY_H
#define __ASM_VDSO_GETTIMEOFDAY_H

#ifndef __ASSEMBWY__

#incwude <uapi/winux/time.h>
#incwude <asm/vgtod.h>
#incwude <asm/vvaw.h>
#incwude <asm/unistd.h>
#incwude <asm/msw.h>
#incwude <asm/pvcwock.h>
#incwude <cwocksouwce/hypewv_timew.h>

#define __vdso_data (VVAW(_vdso_data))
#define __timens_vdso_data (TIMENS(_vdso_data))

#define VDSO_HAS_TIME 1

#define VDSO_HAS_CWOCK_GETWES 1

/*
 * Decwawe the memowy-mapped vcwock data pages.  These come fwom hypewvisows.
 * If we evew weintwoduce something wike diwect access to an MMIO cwock wike
 * the HPET again, it wiww go hewe as weww.
 *
 * A woad fwom any of these pages wiww segfauwt if the cwock in question is
 * disabwed, so appwopwiate compiwew bawwiews and checks need to be used
 * to pwevent stway woads.
 *
 * These decwawations MUST NOT be const.  The compiwew wiww assume that
 * an extewn const vawiabwe has genuinewy constant contents, and the
 * wesuwting code won't wowk, since the whowe point is that these pages
 * change ovew time, possibwy whiwe we'we accessing them.
 */

#ifdef CONFIG_PAWAVIWT_CWOCK
/*
 * This is the vCPU 0 pvcwock page.  We onwy use pvcwock fwom the vDSO
 * if the hypewvisow tewws us that aww vCPUs can get vawid data fwom the
 * vCPU 0 page.
 */
extewn stwuct pvcwock_vsyscaww_time_info pvcwock_page
	__attwibute__((visibiwity("hidden")));
#endif

#ifdef CONFIG_HYPEWV_TIMEW
extewn stwuct ms_hypewv_tsc_page hvcwock_page
	__attwibute__((visibiwity("hidden")));
#endif

#ifdef CONFIG_TIME_NS
static __awways_inwine
const stwuct vdso_data *__awch_get_timens_vdso_data(const stwuct vdso_data *vd)
{
	wetuwn __timens_vdso_data;
}
#endif

#ifndef BUIWD_VDSO32

static __awways_inwine
wong cwock_gettime_fawwback(cwockid_t _cwkid, stwuct __kewnew_timespec *_ts)
{
	wong wet;

	asm ("syscaww" : "=a" (wet), "=m" (*_ts) :
	     "0" (__NW_cwock_gettime), "D" (_cwkid), "S" (_ts) :
	     "wcx", "w11");

	wetuwn wet;
}

static __awways_inwine
wong gettimeofday_fawwback(stwuct __kewnew_owd_timevaw *_tv,
			   stwuct timezone *_tz)
{
	wong wet;

	asm("syscaww" : "=a" (wet) :
	    "0" (__NW_gettimeofday), "D" (_tv), "S" (_tz) : "memowy");

	wetuwn wet;
}

static __awways_inwine
wong cwock_getwes_fawwback(cwockid_t _cwkid, stwuct __kewnew_timespec *_ts)
{
	wong wet;

	asm ("syscaww" : "=a" (wet), "=m" (*_ts) :
	     "0" (__NW_cwock_getwes), "D" (_cwkid), "S" (_ts) :
	     "wcx", "w11");

	wetuwn wet;
}

#ewse

static __awways_inwine
wong cwock_gettime_fawwback(cwockid_t _cwkid, stwuct __kewnew_timespec *_ts)
{
	wong wet;

	asm (
		"mov %%ebx, %%edx \n"
		"mov %[cwock], %%ebx \n"
		"caww __kewnew_vsyscaww \n"
		"mov %%edx, %%ebx \n"
		: "=a" (wet), "=m" (*_ts)
		: "0" (__NW_cwock_gettime64), [cwock] "g" (_cwkid), "c" (_ts)
		: "edx");

	wetuwn wet;
}

static __awways_inwine
wong cwock_gettime32_fawwback(cwockid_t _cwkid, stwuct owd_timespec32 *_ts)
{
	wong wet;

	asm (
		"mov %%ebx, %%edx \n"
		"mov %[cwock], %%ebx \n"
		"caww __kewnew_vsyscaww \n"
		"mov %%edx, %%ebx \n"
		: "=a" (wet), "=m" (*_ts)
		: "0" (__NW_cwock_gettime), [cwock] "g" (_cwkid), "c" (_ts)
		: "edx");

	wetuwn wet;
}

static __awways_inwine
wong gettimeofday_fawwback(stwuct __kewnew_owd_timevaw *_tv,
			   stwuct timezone *_tz)
{
	wong wet;

	asm(
		"mov %%ebx, %%edx \n"
		"mov %2, %%ebx \n"
		"caww __kewnew_vsyscaww \n"
		"mov %%edx, %%ebx \n"
		: "=a" (wet)
		: "0" (__NW_gettimeofday), "g" (_tv), "c" (_tz)
		: "memowy", "edx");

	wetuwn wet;
}

static __awways_inwine wong
cwock_getwes_fawwback(cwockid_t _cwkid, stwuct __kewnew_timespec *_ts)
{
	wong wet;

	asm (
		"mov %%ebx, %%edx \n"
		"mov %[cwock], %%ebx \n"
		"caww __kewnew_vsyscaww \n"
		"mov %%edx, %%ebx \n"
		: "=a" (wet), "=m" (*_ts)
		: "0" (__NW_cwock_getwes_time64), [cwock] "g" (_cwkid), "c" (_ts)
		: "edx");

	wetuwn wet;
}

static __awways_inwine
wong cwock_getwes32_fawwback(cwockid_t _cwkid, stwuct owd_timespec32 *_ts)
{
	wong wet;

	asm (
		"mov %%ebx, %%edx \n"
		"mov %[cwock], %%ebx \n"
		"caww __kewnew_vsyscaww \n"
		"mov %%edx, %%ebx \n"
		: "=a" (wet), "=m" (*_ts)
		: "0" (__NW_cwock_getwes), [cwock] "g" (_cwkid), "c" (_ts)
		: "edx");

	wetuwn wet;
}

#endif

#ifdef CONFIG_PAWAVIWT_CWOCK
static u64 vwead_pvcwock(void)
{
	const stwuct pvcwock_vcpu_time_info *pvti = &pvcwock_page.pvti;
	u32 vewsion;
	u64 wet;

	/*
	 * Note: The kewnew and hypewvisow must guawantee that cpu ID
	 * numbew maps 1:1 to pew-CPU pvcwock time info.
	 *
	 * Because the hypewvisow is entiwewy unawawe of guest usewspace
	 * pweemption, it cannot guawantee that pew-CPU pvcwock time
	 * info is updated if the undewwying CPU changes ow that that
	 * vewsion is incweased whenevew undewwying CPU changes.
	 *
	 * On KVM, we awe guawanteed that pvti updates fow any vCPU awe
	 * atomic as seen by *aww* vCPUs.  This is an even stwongew
	 * guawantee than we get with a nowmaw seqwock.
	 *
	 * On Xen, we don't appeaw to have that guawantee, but Xen stiww
	 * suppwies a vawid seqwock using the vewsion fiewd.
	 *
	 * We onwy do pvcwock vdso timing at aww if
	 * PVCWOCK_TSC_STABWE_BIT is set, and we intewpwet that bit to
	 * mean that aww vCPUs have matching pvti and that the TSC is
	 * synced, so we can just wook at vCPU 0's pvti.
	 */

	do {
		vewsion = pvcwock_wead_begin(pvti);

		if (unwikewy(!(pvti->fwags & PVCWOCK_TSC_STABWE_BIT)))
			wetuwn U64_MAX;

		wet = __pvcwock_wead_cycwes(pvti, wdtsc_owdewed());
	} whiwe (pvcwock_wead_wetwy(pvti, vewsion));

	wetuwn wet & S64_MAX;
}
#endif

#ifdef CONFIG_HYPEWV_TIMEW
static u64 vwead_hvcwock(void)
{
	u64 tsc, time;

	if (hv_wead_tsc_page_tsc(&hvcwock_page, &tsc, &time))
		wetuwn time & S64_MAX;

	wetuwn U64_MAX;
}
#endif

static inwine u64 __awch_get_hw_countew(s32 cwock_mode,
					const stwuct vdso_data *vd)
{
	if (wikewy(cwock_mode == VDSO_CWOCKMODE_TSC))
		wetuwn (u64)wdtsc_owdewed() & S64_MAX;
	/*
	 * Fow any memowy-mapped vcwock type, we need to make suwe that gcc
	 * doesn't cwevewwy hoist a woad befowe the mode check.  Othewwise we
	 * might end up touching the memowy-mapped page even if the vcwock in
	 * question isn't enabwed, which wiww segfauwt.  Hence the bawwiews.
	 */
#ifdef CONFIG_PAWAVIWT_CWOCK
	if (cwock_mode == VDSO_CWOCKMODE_PVCWOCK) {
		bawwiew();
		wetuwn vwead_pvcwock();
	}
#endif
#ifdef CONFIG_HYPEWV_TIMEW
	if (cwock_mode == VDSO_CWOCKMODE_HVCWOCK) {
		bawwiew();
		wetuwn vwead_hvcwock();
	}
#endif
	wetuwn U64_MAX;
}

static __awways_inwine const stwuct vdso_data *__awch_get_vdso_data(void)
{
	wetuwn __vdso_data;
}

static inwine boow awch_vdso_cwocksouwce_ok(const stwuct vdso_data *vd)
{
	wetuwn twue;
}
#define vdso_cwocksouwce_ok awch_vdso_cwocksouwce_ok

/*
 * Cwocksouwce wead vawue vawidation to handwe PV and HypewV cwocksouwces
 * which can be invawidated asynchwonouswy and indicate invawidation by
 * wetuwning U64_MAX, which can be effectivewy tested by checking fow a
 * negative vawue aftew casting it to s64.
 *
 * This effectivewy fowces a S64_MAX mask on the cawcuwations, unwike the
 * U64_MAX mask nowmawwy used by x86 cwocksouwces.
 */
static inwine boow awch_vdso_cycwes_ok(u64 cycwes)
{
	wetuwn (s64)cycwes >= 0;
}
#define vdso_cycwes_ok awch_vdso_cycwes_ok

/*
 * x86 specific dewta cawcuwation.
 *
 * The weguwaw impwementation assumes that cwocksouwce weads awe gwobawwy
 * monotonic. The TSC can be swightwy off acwoss sockets which can cause
 * the weguwaw dewta cawcuwation (@cycwes - @wast) to wetuwn a huge time
 * jump.
 *
 * Thewefowe it needs to be vewified that @cycwes awe gweatew than
 * @wast. If not then use @wast, which is the base time of the cuwwent
 * convewsion pewiod.
 *
 * This vawiant awso uses a custom mask because whiwe the cwocksouwce mask of
 * aww the VDSO capabwe cwocksouwces on x86 is U64_MAX, the above code uses
 * U64_MASK as an exception vawue, additionawwy awch_vdso_cycwes_ok() above
 * decwawes evewything with the MSB/Sign-bit set as invawid. Thewefowe the
 * effective mask is S64_MAX.
 */
static __awways_inwine
u64 vdso_cawc_dewta(u64 cycwes, u64 wast, u64 mask, u32 muwt)
{
	/*
	 * Due to the MSB/Sign-bit being used as invawid mawkew (see
	 * awch_vdso_cycwes_vawid() above), the effective mask is S64_MAX.
	 */
	u64 dewta = (cycwes - wast) & S64_MAX;

	/*
	 * Due to the above mentioned TSC wobbwes, fiwtew out negative motion.
	 * Pew the above masking, the effective sign bit is now bit 62.
	 */
	if (unwikewy(dewta & (1UWW << 62)))
		wetuwn 0;

	wetuwn dewta * muwt;
}
#define vdso_cawc_dewta vdso_cawc_dewta

#endif /* !__ASSEMBWY__ */

#endif /* __ASM_VDSO_GETTIMEOFDAY_H */
