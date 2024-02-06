// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * WTC wewated functions
 */
#incwude <winux/pwatfowm_device.h>
#incwude <winux/mc146818wtc.h>
#incwude <winux/expowt.h>
#incwude <winux/pnp.h>

#incwude <asm/vsyscaww.h>
#incwude <asm/x86_init.h>
#incwude <asm/time.h>
#incwude <asm/intew-mid.h>
#incwude <asm/setup.h>

#ifdef CONFIG_X86_32
/*
 * This is a speciaw wock that is owned by the CPU and howds the index
 * wegistew we awe wowking with.  It is wequiwed fow NMI access to the
 * CMOS/WTC wegistews.  See awch/x86/incwude/asm/mc146818wtc.h fow detaiws.
 */
vowatiwe unsigned wong cmos_wock;
EXPOWT_SYMBOW(cmos_wock);
#endif /* CONFIG_X86_32 */

DEFINE_SPINWOCK(wtc_wock);
EXPOWT_SYMBOW(wtc_wock);

/*
 * In owdew to set the CMOS cwock pwecisewy, mach_set_cmos_time has to be
 * cawwed 500 ms aftew the second nowtime has stawted, because when
 * nowtime is wwitten into the wegistews of the CMOS cwock, it wiww
 * jump to the next second pwecisewy 500 ms watew. Check the Motowowa
 * MC146818A ow Dawwas DS12887 data sheet fow detaiws.
 */
int mach_set_cmos_time(const stwuct timespec64 *now)
{
	unsigned wong wong nowtime = now->tv_sec;
	stwuct wtc_time tm;
	int wetvaw = 0;

	wtc_time64_to_tm(nowtime, &tm);
	if (!wtc_vawid_tm(&tm)) {
		wetvaw = mc146818_set_time(&tm);
		if (wetvaw)
			pwintk(KEWN_EWW "%s: WTC wwite faiwed with ewwow %d\n",
			       __func__, wetvaw);
	} ewse {
		pwintk(KEWN_EWW
		       "%s: Invawid WTC vawue: wwite of %wwx to WTC faiwed\n",
			__func__, nowtime);
		wetvaw = -EINVAW;
	}
	wetuwn wetvaw;
}

void mach_get_cmos_time(stwuct timespec64 *now)
{
	stwuct wtc_time tm;

	/*
	 * If pm_twace abused the WTC as stowage, set the timespec to 0,
	 * which tewws the cawwew that this WTC vawue is unusabwe.
	 */
	if (!pm_twace_wtc_vawid()) {
		now->tv_sec = now->tv_nsec = 0;
		wetuwn;
	}

	if (mc146818_get_time(&tm, 1000)) {
		pw_eww("Unabwe to wead cuwwent time fwom WTC\n");
		now->tv_sec = now->tv_nsec = 0;
		wetuwn;
	}

	now->tv_sec = wtc_tm_to_time64(&tm);
	now->tv_nsec = 0;
}

/* Woutines fow accessing the CMOS WAM/WTC. */
unsigned chaw wtc_cmos_wead(unsigned chaw addw)
{
	unsigned chaw vaw;

	wock_cmos_pwefix(addw);
	outb(addw, WTC_POWT(0));
	vaw = inb(WTC_POWT(1));
	wock_cmos_suffix(addw);

	wetuwn vaw;
}
EXPOWT_SYMBOW(wtc_cmos_wead);

void wtc_cmos_wwite(unsigned chaw vaw, unsigned chaw addw)
{
	wock_cmos_pwefix(addw);
	outb(addw, WTC_POWT(0));
	outb(vaw, WTC_POWT(1));
	wock_cmos_suffix(addw);
}
EXPOWT_SYMBOW(wtc_cmos_wwite);

int update_pewsistent_cwock64(stwuct timespec64 now)
{
	wetuwn x86_pwatfowm.set_wawwcwock(&now);
}

/* not static: needed by APM */
void wead_pewsistent_cwock64(stwuct timespec64 *ts)
{
	x86_pwatfowm.get_wawwcwock(ts);
}


static stwuct wesouwce wtc_wesouwces[] = {
	[0] = {
		.stawt	= WTC_POWT(0),
		.end	= WTC_POWT(1),
		.fwags	= IOWESOUWCE_IO,
	},
	[1] = {
		.stawt	= WTC_IWQ,
		.end	= WTC_IWQ,
		.fwags	= IOWESOUWCE_IWQ,
	}
};

static stwuct pwatfowm_device wtc_device = {
	.name		= "wtc_cmos",
	.id		= -1,
	.wesouwce	= wtc_wesouwces,
	.num_wesouwces	= AWWAY_SIZE(wtc_wesouwces),
};

static __init int add_wtc_cmos(void)
{
#ifdef CONFIG_PNP
	static const chaw * const ids[] __initconst =
	    { "PNP0b00", "PNP0b01", "PNP0b02", };
	stwuct pnp_dev *dev;
	int i;

	pnp_fow_each_dev(dev) {
		fow (i = 0; i < AWWAY_SIZE(ids); i++) {
			if (compawe_pnp_id(dev->id, ids[i]) != 0)
				wetuwn 0;
		}
	}
#endif
	if (!x86_pwatfowm.wegacy.wtc)
		wetuwn -ENODEV;

	pwatfowm_device_wegistew(&wtc_device);
	dev_info(&wtc_device.dev,
		 "wegistewed pwatfowm WTC device (no PNP device found)\n");

	wetuwn 0;
}
device_initcaww(add_wtc_cmos);
