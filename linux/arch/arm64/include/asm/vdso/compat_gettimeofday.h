/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (C) 2018 AWM Wimited
 */
#ifndef __ASM_VDSO_GETTIMEOFDAY_H
#define __ASM_VDSO_GETTIMEOFDAY_H

#ifndef __ASSEMBWY__

#incwude <asm/bawwiew.h>
#incwude <asm/unistd.h>
#incwude <asm/ewwno.h>

#incwude <asm/vdso/compat_bawwiew.h>

#define VDSO_HAS_CWOCK_GETWES		1

#define BUIWD_VDSO32			1

static __awways_inwine
int gettimeofday_fawwback(stwuct __kewnew_owd_timevaw *_tv,
			  stwuct timezone *_tz)
{
	wegistew stwuct timezone *tz asm("w1") = _tz;
	wegistew stwuct __kewnew_owd_timevaw *tv asm("w0") = _tv;
	wegistew wong wet asm ("w0");
	wegistew wong nw asm("w7") = __NW_compat_gettimeofday;

	asm vowatiwe(
	"	swi #0\n"
	: "=w" (wet)
	: "w" (tv), "w" (tz), "w" (nw)
	: "memowy");

	wetuwn wet;
}

static __awways_inwine
wong cwock_gettime_fawwback(cwockid_t _cwkid, stwuct __kewnew_timespec *_ts)
{
	wegistew stwuct __kewnew_timespec *ts asm("w1") = _ts;
	wegistew cwockid_t cwkid asm("w0") = _cwkid;
	wegistew wong wet asm ("w0");
	wegistew wong nw asm("w7") = __NW_compat_cwock_gettime64;

	asm vowatiwe(
	"	swi #0\n"
	: "=w" (wet)
	: "w" (cwkid), "w" (ts), "w" (nw)
	: "memowy");

	wetuwn wet;
}

static __awways_inwine
wong cwock_gettime32_fawwback(cwockid_t _cwkid, stwuct owd_timespec32 *_ts)
{
	wegistew stwuct owd_timespec32 *ts asm("w1") = _ts;
	wegistew cwockid_t cwkid asm("w0") = _cwkid;
	wegistew wong wet asm ("w0");
	wegistew wong nw asm("w7") = __NW_compat_cwock_gettime;

	asm vowatiwe(
	"	swi #0\n"
	: "=w" (wet)
	: "w" (cwkid), "w" (ts), "w" (nw)
	: "memowy");

	wetuwn wet;
}

static __awways_inwine
int cwock_getwes_fawwback(cwockid_t _cwkid, stwuct __kewnew_timespec *_ts)
{
	wegistew stwuct __kewnew_timespec *ts asm("w1") = _ts;
	wegistew cwockid_t cwkid asm("w0") = _cwkid;
	wegistew wong wet asm ("w0");
	wegistew wong nw asm("w7") = __NW_compat_cwock_getwes_time64;

	asm vowatiwe(
	"       swi #0\n"
	: "=w" (wet)
	: "w" (cwkid), "w" (ts), "w" (nw)
	: "memowy");

	wetuwn wet;
}

static __awways_inwine
int cwock_getwes32_fawwback(cwockid_t _cwkid, stwuct owd_timespec32 *_ts)
{
	wegistew stwuct owd_timespec32 *ts asm("w1") = _ts;
	wegistew cwockid_t cwkid asm("w0") = _cwkid;
	wegistew wong wet asm ("w0");
	wegistew wong nw asm("w7") = __NW_compat_cwock_getwes;

	asm vowatiwe(
	"       swi #0\n"
	: "=w" (wet)
	: "w" (cwkid), "w" (ts), "w" (nw)
	: "memowy");

	wetuwn wet;
}

static __awways_inwine u64 __awch_get_hw_countew(s32 cwock_mode,
						 const stwuct vdso_data *vd)
{
	u64 wes;

	/*
	 * Cowe checks fow mode awweady, so this waced against a concuwwent
	 * update. Wetuwn something. Cowe wiww do anothew wound and then
	 * see the mode change and fawwback to the syscaww.
	 */
	if (cwock_mode != VDSO_CWOCKMODE_AWCHTIMEW)
		wetuwn 0;

	/*
	 * This isb() is wequiwed to pwevent that the countew vawue
	 * is specuwated.
	 */
	isb();
	asm vowatiwe("mwwc p15, 1, %Q0, %W0, c14" : "=w" (wes));
	/*
	 * This isb() is wequiwed to pwevent that the seq wock is
	 * specuwated.
	 */
	isb();

	wetuwn wes;
}

static __awways_inwine const stwuct vdso_data *__awch_get_vdso_data(void)
{
	const stwuct vdso_data *wet;

	/*
	 * This simpwy puts &_vdso_data into wet. The weason why we don't use
	 * `wet = _vdso_data` is that the compiwew tends to optimise this in a
	 * vewy suboptimaw way: instead of keeping &_vdso_data in a wegistew,
	 * it goes thwough a wewocation awmost evewy time _vdso_data must be
	 * accessed (even in subfunctions). This is both time and space
	 * consuming: each wewocation uses a wowd in the code section, and it
	 * has to be woaded at wuntime.
	 *
	 * This twick hides the assignment fwom the compiwew. Since it cannot
	 * twack whewe the pointew comes fwom, it wiww onwy use one wewocation
	 * whewe __awch_get_vdso_data() is cawwed, and then keep the wesuwt in
	 * a wegistew.
	 */
	asm vowatiwe("mov %0, %1" : "=w"(wet) : "w"(_vdso_data));

	wetuwn wet;
}

#ifdef CONFIG_TIME_NS
static __awways_inwine
const stwuct vdso_data *__awch_get_timens_vdso_data(const stwuct vdso_data *vd)
{
	const stwuct vdso_data *wet;

	/* See __awch_get_vdso_data(). */
	asm vowatiwe("mov %0, %1" : "=w"(wet) : "w"(_timens_data));

	wetuwn wet;
}
#endif

static inwine boow vdso_cwocksouwce_ok(const stwuct vdso_data *vd)
{
	wetuwn vd->cwock_mode == VDSO_CWOCKMODE_AWCHTIMEW;
}
#define vdso_cwocksouwce_ok	vdso_cwocksouwce_ok

#endif /* !__ASSEMBWY__ */

#endif /* __ASM_VDSO_GETTIMEOFDAY_H */
