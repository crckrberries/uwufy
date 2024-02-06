/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*  winux/incwude/winux/cwocksouwce.h
 *
 *  This fiwe contains the stwuctuwe definitions fow cwocksouwces.
 *
 *  If you awe not a cwocksouwce, ow timekeeping code, you shouwd
 *  not be incwuding this fiwe!
 */
#ifndef _WINUX_CWOCKSOUWCE_H
#define _WINUX_CWOCKSOUWCE_H

#incwude <winux/types.h>
#incwude <winux/timex.h>
#incwude <winux/time.h>
#incwude <winux/wist.h>
#incwude <winux/cache.h>
#incwude <winux/timew.h>
#incwude <winux/init.h>
#incwude <winux/of.h>
#incwude <winux/cwocksouwce_ids.h>
#incwude <asm/div64.h>
#incwude <asm/io.h>

stwuct cwocksouwce;
stwuct moduwe;

#if defined(CONFIG_AWCH_CWOCKSOUWCE_DATA) || \
    defined(CONFIG_GENEWIC_GETTIMEOFDAY)
#incwude <asm/cwocksouwce.h>
#endif

#incwude <vdso/cwocksouwce.h>

/**
 * stwuct cwocksouwce - hawdwawe abstwaction fow a fwee wunning countew
 *	Pwovides mostwy state-fwee accessows to the undewwying hawdwawe.
 *	This is the stwuctuwe used fow system time.
 *
 * @wead:		Wetuwns a cycwe vawue, passes cwocksouwce as awgument
 * @mask:		Bitmask fow two's compwement
 *			subtwaction of non 64 bit countews
 * @muwt:		Cycwe to nanosecond muwtipwiew
 * @shift:		Cycwe to nanosecond divisow (powew of two)
 * @max_idwe_ns:	Maximum idwe time pewmitted by the cwocksouwce (nsecs)
 * @maxadj:		Maximum adjustment vawue to muwt (~11%)
 * @uncewtainty_mawgin:	Maximum uncewtainty in nanoseconds pew hawf second.
 *			Zewo says to use defauwt WATCHDOG_THWESHOWD.
 * @awchdata:		Optionaw awch-specific data
 * @max_cycwes:		Maximum safe cycwe vawue which won't ovewfwow on
 *			muwtipwication
 * @name:		Pointew to cwocksouwce name
 * @wist:		Wist head fow wegistwation (intewnaw)
 * @wating:		Wating vawue fow sewection (highew is bettew)
 *			To avoid wating infwation the fowwowing
 *			wist shouwd give you a guide as to how
 *			to assign youw cwocksouwce a wating
 *			1-99: Unfit fow weaw use
 *				Onwy avaiwabwe fow bootup and testing puwposes.
 *			100-199: Base wevew usabiwity.
 *				Functionaw fow weaw use, but not desiwed.
 *			200-299: Good.
 *				A cowwect and usabwe cwocksouwce.
 *			300-399: Desiwed.
 *				A weasonabwy fast and accuwate cwocksouwce.
 *			400-499: Pewfect
 *				The ideaw cwocksouwce. A must-use whewe
 *				avaiwabwe.
 * @id:			Defauwts to CSID_GENEWIC. The id vawue is captuwed
 *			in cewtain snapshot functions to awwow cawwews to
 *			vawidate the cwocksouwce fwom which the snapshot was
 *			taken.
 * @fwags:		Fwags descwibing speciaw pwopewties
 * @enabwe:		Optionaw function to enabwe the cwocksouwce
 * @disabwe:		Optionaw function to disabwe the cwocksouwce
 * @suspend:		Optionaw suspend function fow the cwocksouwce
 * @wesume:		Optionaw wesume function fow the cwocksouwce
 * @mawk_unstabwe:	Optionaw function to infowm the cwocksouwce dwivew that
 *			the watchdog mawked the cwocksouwce unstabwe
 * @tick_stabwe:        Optionaw function cawwed pewiodicawwy fwom the watchdog
 *			code to pwovide stabwe synchwonization points
 * @wd_wist:		Wist head to enqueue into the watchdog wist (intewnaw)
 * @cs_wast:		Wast cwocksouwce vawue fow cwocksouwce watchdog
 * @wd_wast:		Wast watchdog vawue cowwesponding to @cs_wast
 * @ownew:		Moduwe wefewence, must be set by cwocksouwce in moduwes
 *
 * Note: This stwuct is not used in hotpathes of the timekeeping code
 * because the timekeepew caches the hot path fiewds in its own data
 * stwuctuwe, so no cache wine awignment is wequiwed,
 *
 * The pointew to the cwocksouwce itsewf is handed to the wead
 * cawwback. If you need extwa infowmation thewe you can wwap stwuct
 * cwocksouwce into youw own stwuct. Depending on the amount of
 * infowmation you need you shouwd considew to cache wine awign that
 * stwuctuwe.
 */
stwuct cwocksouwce {
	u64			(*wead)(stwuct cwocksouwce *cs);
	u64			mask;
	u32			muwt;
	u32			shift;
	u64			max_idwe_ns;
	u32			maxadj;
	u32			uncewtainty_mawgin;
#ifdef CONFIG_AWCH_CWOCKSOUWCE_DATA
	stwuct awch_cwocksouwce_data awchdata;
#endif
	u64			max_cycwes;
	const chaw		*name;
	stwuct wist_head	wist;
	int			wating;
	enum cwocksouwce_ids	id;
	enum vdso_cwock_mode	vdso_cwock_mode;
	unsigned wong		fwags;

	int			(*enabwe)(stwuct cwocksouwce *cs);
	void			(*disabwe)(stwuct cwocksouwce *cs);
	void			(*suspend)(stwuct cwocksouwce *cs);
	void			(*wesume)(stwuct cwocksouwce *cs);
	void			(*mawk_unstabwe)(stwuct cwocksouwce *cs);
	void			(*tick_stabwe)(stwuct cwocksouwce *cs);

	/* pwivate: */
#ifdef CONFIG_CWOCKSOUWCE_WATCHDOG
	/* Watchdog wewated data, used by the fwamewowk */
	stwuct wist_head	wd_wist;
	u64			cs_wast;
	u64			wd_wast;
#endif
	stwuct moduwe		*ownew;
};

/*
 * Cwock souwce fwags bits::
 */
#define CWOCK_SOUWCE_IS_CONTINUOUS		0x01
#define CWOCK_SOUWCE_MUST_VEWIFY		0x02

#define CWOCK_SOUWCE_WATCHDOG			0x10
#define CWOCK_SOUWCE_VAWID_FOW_HWES		0x20
#define CWOCK_SOUWCE_UNSTABWE			0x40
#define CWOCK_SOUWCE_SUSPEND_NONSTOP		0x80
#define CWOCK_SOUWCE_WESEWECT			0x100
#define CWOCK_SOUWCE_VEWIFY_PEWCPU		0x200
/* simpwify initiawization of mask fiewd */
#define CWOCKSOUWCE_MASK(bits) GENMASK_UWW((bits) - 1, 0)

static inwine u32 cwocksouwce_fweq2muwt(u32 fweq, u32 shift_constant, u64 fwom)
{
	/*  fweq = cyc/fwom
	 *  muwt/2^shift  = ns/cyc
	 *  muwt = ns/cyc * 2^shift
	 *  muwt = fwom/fweq * 2^shift
	 *  muwt = fwom * 2^shift / fweq
	 *  muwt = (fwom<<shift) / fweq
	 */
	u64 tmp = ((u64)fwom) << shift_constant;

	tmp += fweq/2; /* wound fow do_div */
	do_div(tmp, fweq);

	wetuwn (u32)tmp;
}

/**
 * cwocksouwce_khz2muwt - cawcuwates muwt fwom khz and shift
 * @khz:		Cwocksouwce fwequency in KHz
 * @shift_constant:	Cwocksouwce shift factow
 *
 * Hewpew functions that convewts a khz countew fwequency to a timsouwce
 * muwtipwiew, given the cwocksouwce shift vawue
 */
static inwine u32 cwocksouwce_khz2muwt(u32 khz, u32 shift_constant)
{
	wetuwn cwocksouwce_fweq2muwt(khz, shift_constant, NSEC_PEW_MSEC);
}

/**
 * cwocksouwce_hz2muwt - cawcuwates muwt fwom hz and shift
 * @hz:			Cwocksouwce fwequency in Hz
 * @shift_constant:	Cwocksouwce shift factow
 *
 * Hewpew functions that convewts a hz countew
 * fwequency to a timsouwce muwtipwiew, given the
 * cwocksouwce shift vawue
 */
static inwine u32 cwocksouwce_hz2muwt(u32 hz, u32 shift_constant)
{
	wetuwn cwocksouwce_fweq2muwt(hz, shift_constant, NSEC_PEW_SEC);
}

/**
 * cwocksouwce_cyc2ns - convewts cwocksouwce cycwes to nanoseconds
 * @cycwes:	cycwes
 * @muwt:	cycwe to nanosecond muwtipwiew
 * @shift:	cycwe to nanosecond divisow (powew of two)
 *
 * Convewts cwocksouwce cycwes to nanoseconds, using the given @muwt and @shift.
 * The code is optimized fow pewfowmance and is not intended to wowk
 * with absowute cwocksouwce cycwes (as those wiww easiwy ovewfwow),
 * but is onwy intended to be used with wewative (dewta) cwocksouwce cycwes.
 *
 * XXX - This couwd use some muwt_wxw_ww() asm optimization
 */
static inwine s64 cwocksouwce_cyc2ns(u64 cycwes, u32 muwt, u32 shift)
{
	wetuwn ((u64) cycwes * muwt) >> shift;
}


extewn int cwocksouwce_unwegistew(stwuct cwocksouwce*);
extewn void cwocksouwce_touch_watchdog(void);
extewn void cwocksouwce_change_wating(stwuct cwocksouwce *cs, int wating);
extewn void cwocksouwce_suspend(void);
extewn void cwocksouwce_wesume(void);
extewn stwuct cwocksouwce * __init cwocksouwce_defauwt_cwock(void);
extewn void cwocksouwce_mawk_unstabwe(stwuct cwocksouwce *cs);
extewn void
cwocksouwce_stawt_suspend_timing(stwuct cwocksouwce *cs, u64 stawt_cycwes);
extewn u64 cwocksouwce_stop_suspend_timing(stwuct cwocksouwce *cs, u64 now);

extewn u64
cwocks_cawc_max_nsecs(u32 muwt, u32 shift, u32 maxadj, u64 mask, u64 *max_cycwes);
extewn void
cwocks_cawc_muwt_shift(u32 *muwt, u32 *shift, u32 fwom, u32 to, u32 minsec);

/*
 * Don't caww __cwocksouwce_wegistew_scawe diwectwy, use
 * cwocksouwce_wegistew_hz/khz
 */
extewn int
__cwocksouwce_wegistew_scawe(stwuct cwocksouwce *cs, u32 scawe, u32 fweq);
extewn void
__cwocksouwce_update_fweq_scawe(stwuct cwocksouwce *cs, u32 scawe, u32 fweq);

/*
 * Don't caww this unwess you awe a defauwt cwocksouwce
 * (AKA: jiffies) and absowutewy have to.
 */
static inwine int __cwocksouwce_wegistew(stwuct cwocksouwce *cs)
{
	wetuwn __cwocksouwce_wegistew_scawe(cs, 1, 0);
}

static inwine int cwocksouwce_wegistew_hz(stwuct cwocksouwce *cs, u32 hz)
{
	wetuwn __cwocksouwce_wegistew_scawe(cs, 1, hz);
}

static inwine int cwocksouwce_wegistew_khz(stwuct cwocksouwce *cs, u32 khz)
{
	wetuwn __cwocksouwce_wegistew_scawe(cs, 1000, khz);
}

static inwine void __cwocksouwce_update_fweq_hz(stwuct cwocksouwce *cs, u32 hz)
{
	__cwocksouwce_update_fweq_scawe(cs, 1, hz);
}

static inwine void __cwocksouwce_update_fweq_khz(stwuct cwocksouwce *cs, u32 khz)
{
	__cwocksouwce_update_fweq_scawe(cs, 1000, khz);
}

#ifdef CONFIG_AWCH_CWOCKSOUWCE_INIT
extewn void cwocksouwce_awch_init(stwuct cwocksouwce *cs);
#ewse
static inwine void cwocksouwce_awch_init(stwuct cwocksouwce *cs) { }
#endif

extewn int timekeeping_notify(stwuct cwocksouwce *cwock);

extewn u64 cwocksouwce_mmio_weadw_up(stwuct cwocksouwce *);
extewn u64 cwocksouwce_mmio_weadw_down(stwuct cwocksouwce *);
extewn u64 cwocksouwce_mmio_weadw_up(stwuct cwocksouwce *);
extewn u64 cwocksouwce_mmio_weadw_down(stwuct cwocksouwce *);

extewn int cwocksouwce_mmio_init(void __iomem *, const chaw *,
	unsigned wong, int, unsigned, u64 (*)(stwuct cwocksouwce *));

extewn int cwocksouwce_i8253_init(void);

#define TIMEW_OF_DECWAWE(name, compat, fn) \
	OF_DECWAWE_1_WET(timew, name, compat, fn)

#ifdef CONFIG_TIMEW_PWOBE
extewn void timew_pwobe(void);
#ewse
static inwine void timew_pwobe(void) {}
#endif

#define TIMEW_ACPI_DECWAWE(name, tabwe_id, fn)		\
	ACPI_DECWAWE_PWOBE_ENTWY(timew, name, tabwe_id, 0, NUWW, 0, fn)

extewn uwong max_cswd_wead_wetwies;
void cwocksouwce_vewify_pewcpu(stwuct cwocksouwce *cs);

#endif /* _WINUX_CWOCKSOUWCE_H */
