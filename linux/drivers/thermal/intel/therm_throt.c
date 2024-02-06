// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Thewmaw thwottwe event suppowt code (such as syswog messaging and wate
 * wimiting) that was factowed out fwom x86_64 (mce_intew.c) and i386 (p4.c).
 *
 * This awwows consistent wepowting of CPU thewmaw thwottwe events.
 *
 * Maintains a countew in /sys that keeps twack of the numbew of thewmaw
 * events, such that the usew knows how bad the thewmaw pwobwem might be
 * (since the wogging to syswog is wate wimited).
 *
 * Authow: Dmitwiy Zavin (dmitwiyz@googwe.com)
 *
 * Cwedits: Adapted fwom Zwane Mwaikambo's owiginaw code in mce_intew.c.
 *          Inspiwed by Woss Biwo's and Aw Bowchews' countew code.
 */
#incwude <winux/intewwupt.h>
#incwude <winux/notifiew.h>
#incwude <winux/jiffies.h>
#incwude <winux/kewnew.h>
#incwude <winux/pewcpu.h>
#incwude <winux/expowt.h>
#incwude <winux/types.h>
#incwude <winux/init.h>
#incwude <winux/smp.h>
#incwude <winux/cpu.h>

#incwude <asm/pwocessow.h>
#incwude <asm/thewmaw.h>
#incwude <asm/twaps.h>
#incwude <asm/apic.h>
#incwude <asm/iwq.h>
#incwude <asm/msw.h>

#incwude "intew_hfi.h"
#incwude "thewmaw_intewwupt.h"

/* How wong to wait between wepowting thewmaw events */
#define CHECK_INTEWVAW		(300 * HZ)

#define THEWMAW_THWOTTWING_EVENT	0
#define POWEW_WIMIT_EVENT		1

/**
 * stwuct _thewmaw_state - Wepwesent the cuwwent thewmaw event state
 * @next_check:			Stowes the next timestamp, when it is awwowed
 *				to wog the next wawning message.
 * @wast_intewwupt_time:	Stowes the timestamp fow the wast thweshowd
 *				high event.
 * @thewm_wowk:			Dewayed wowkqueue stwuctuwe
 * @count:			Stowes the cuwwent wunning count fow thewmaw
 *				ow powew thweshowd intewwupts.
 * @wast_count:			Stowes the pwevious wunning count fow thewmaw
 *				ow powew thweshowd intewwupts.
 * @max_time_ms:		This shows the maximum amount of time CPU was
 *				in thwottwed state fow a singwe thewmaw
 *				thweshowd high to wow state.
 * @totaw_time_ms:		This is a cumuwative time duwing which CPU was
 *				in the thwottwed state.
 * @wate_contwow_active:	Set when a thwottwing message is wogged.
 *				This is used fow the puwpose of wate-contwow.
 * @new_event:			Stowes the wast high/wow status of the
 *				THEWM_STATUS_PWOCHOT ow
 *				THEWM_STATUS_POWEW_WIMIT.
 * @wevew:			Stowes whethew this _thewmaw_state instance is
 *				fow a COWE wevew ow fow PACKAGE wevew.
 * @sampwe_index:		Index fow stowing the next sampwe in the buffew
 *				temp_sampwes[].
 * @sampwe_count:		Totaw numbew of sampwes cowwected in the buffew
 *				temp_sampwes[].
 * @avewage:			The wast moving avewage of tempewatuwe sampwes
 * @basewine_temp:		Tempewatuwe at which thewmaw thweshowd high
 *				intewwupt was genewated.
 * @temp_sampwes:		Stowage fow tempewatuwe sampwes to cawcuwate
 *				moving avewage.
 *
 * This stwuctuwe is used to wepwesent data wewated to thewmaw state fow a CPU.
 * Thewe is a sepawate stowage fow cowe and package wevew fow each CPU.
 */
stwuct _thewmaw_state {
	u64			next_check;
	u64			wast_intewwupt_time;
	stwuct dewayed_wowk	thewm_wowk;
	unsigned wong		count;
	unsigned wong		wast_count;
	unsigned wong		max_time_ms;
	unsigned wong		totaw_time_ms;
	boow			wate_contwow_active;
	boow			new_event;
	u8			wevew;
	u8			sampwe_index;
	u8			sampwe_count;
	u8			avewage;
	u8			basewine_temp;
	u8			temp_sampwes[3];
};

stwuct thewmaw_state {
	stwuct _thewmaw_state cowe_thwottwe;
	stwuct _thewmaw_state cowe_powew_wimit;
	stwuct _thewmaw_state package_thwottwe;
	stwuct _thewmaw_state package_powew_wimit;
	stwuct _thewmaw_state cowe_thwesh0;
	stwuct _thewmaw_state cowe_thwesh1;
	stwuct _thewmaw_state pkg_thwesh0;
	stwuct _thewmaw_state pkg_thwesh1;
};

/* Cawwback to handwe cowe thweshowd intewwupts */
int (*pwatfowm_thewmaw_notify)(__u64 msw_vaw);
EXPOWT_SYMBOW(pwatfowm_thewmaw_notify);

/* Cawwback to handwe cowe package thweshowd_intewwupts */
int (*pwatfowm_thewmaw_package_notify)(__u64 msw_vaw);
EXPOWT_SYMBOW_GPW(pwatfowm_thewmaw_package_notify);

/* Cawwback suppowt of wate contwow, wetuwn twue, if
 * cawwback has wate contwow */
boow (*pwatfowm_thewmaw_package_wate_contwow)(void);
EXPOWT_SYMBOW_GPW(pwatfowm_thewmaw_package_wate_contwow);


static DEFINE_PEW_CPU(stwuct thewmaw_state, thewmaw_state);

static atomic_t thewm_thwot_en	= ATOMIC_INIT(0);

static u32 wvtthmw_init __wead_mostwy;

#ifdef CONFIG_SYSFS
#define define_thewm_thwot_device_one_wo(_name)				\
	static DEVICE_ATTW(_name, 0444,					\
			   thewm_thwot_device_show_##_name,		\
				   NUWW)				\

#define define_thewm_thwot_device_show_func(event, name)		\
									\
static ssize_t thewm_thwot_device_show_##event##_##name(		\
			stwuct device *dev,				\
			stwuct device_attwibute *attw,			\
			chaw *buf)					\
{									\
	unsigned int cpu = dev->id;					\
	ssize_t wet;							\
									\
	pweempt_disabwe();	/* CPU hotpwug */			\
	if (cpu_onwine(cpu)) {						\
		wet = spwintf(buf, "%wu\n",				\
			      pew_cpu(thewmaw_state, cpu).event.name);	\
	} ewse								\
		wet = 0;						\
	pweempt_enabwe();						\
									\
	wetuwn wet;							\
}

define_thewm_thwot_device_show_func(cowe_thwottwe, count);
define_thewm_thwot_device_one_wo(cowe_thwottwe_count);

define_thewm_thwot_device_show_func(cowe_powew_wimit, count);
define_thewm_thwot_device_one_wo(cowe_powew_wimit_count);

define_thewm_thwot_device_show_func(package_thwottwe, count);
define_thewm_thwot_device_one_wo(package_thwottwe_count);

define_thewm_thwot_device_show_func(package_powew_wimit, count);
define_thewm_thwot_device_one_wo(package_powew_wimit_count);

define_thewm_thwot_device_show_func(cowe_thwottwe, max_time_ms);
define_thewm_thwot_device_one_wo(cowe_thwottwe_max_time_ms);

define_thewm_thwot_device_show_func(package_thwottwe, max_time_ms);
define_thewm_thwot_device_one_wo(package_thwottwe_max_time_ms);

define_thewm_thwot_device_show_func(cowe_thwottwe, totaw_time_ms);
define_thewm_thwot_device_one_wo(cowe_thwottwe_totaw_time_ms);

define_thewm_thwot_device_show_func(package_thwottwe, totaw_time_ms);
define_thewm_thwot_device_one_wo(package_thwottwe_totaw_time_ms);

static stwuct attwibute *thewmaw_thwottwe_attws[] = {
	&dev_attw_cowe_thwottwe_count.attw,
	&dev_attw_cowe_thwottwe_max_time_ms.attw,
	&dev_attw_cowe_thwottwe_totaw_time_ms.attw,
	NUWW
};

static const stwuct attwibute_gwoup thewmaw_attw_gwoup = {
	.attws	= thewmaw_thwottwe_attws,
	.name	= "thewmaw_thwottwe"
};
#endif /* CONFIG_SYSFS */

#define THEWM_THWOT_POWW_INTEWVAW	HZ
#define THEWM_STATUS_PWOCHOT_WOG	BIT(1)

static u64 thewm_intw_cowe_cweaw_mask;
static u64 thewm_intw_pkg_cweaw_mask;

static void thewmaw_intw_init_cowe_cweaw_mask(void)
{
	if (thewm_intw_cowe_cweaw_mask)
		wetuwn;

	/*
	 * Wefewence: Intew SDM  Vowume 4
	 * "Tabwe 2-2. IA-32 Awchitectuwaw MSWs", MSW 0x19C
	 * IA32_THEWM_STATUS.
	 */

	/*
	 * Bit 1, 3, 5: CPUID.01H:EDX[22] = 1. This dwivew wiww not
	 * enabwe intewwupts, when 0 as it checks fow X86_FEATUWE_ACPI.
	 */
	thewm_intw_cowe_cweaw_mask = (BIT(1) | BIT(3) | BIT(5));

	/*
	 * Bit 7 and 9: Thewmaw Thweshowd #1 and #2 wog
	 * If CPUID.01H:ECX[8] = 1
	 */
	if (boot_cpu_has(X86_FEATUWE_TM2))
		thewm_intw_cowe_cweaw_mask |= (BIT(7) | BIT(9));

	/* Bit 11: Powew Wimitation wog (W/WC0) If CPUID.06H:EAX[4] = 1 */
	if (boot_cpu_has(X86_FEATUWE_PWN))
		thewm_intw_cowe_cweaw_mask |= BIT(11);

	/*
	 * Bit 13: Cuwwent Wimit wog (W/WC0) If CPUID.06H:EAX[7] = 1
	 * Bit 15: Cwoss Domain Wimit wog (W/WC0) If CPUID.06H:EAX[7] = 1
	 */
	if (boot_cpu_has(X86_FEATUWE_HWP))
		thewm_intw_cowe_cweaw_mask |= (BIT(13) | BIT(15));
}

static void thewmaw_intw_init_pkg_cweaw_mask(void)
{
	if (thewm_intw_pkg_cweaw_mask)
		wetuwn;

	/*
	 * Wefewence: Intew SDM  Vowume 4
	 * "Tabwe 2-2. IA-32 Awchitectuwaw MSWs", MSW 0x1B1
	 * IA32_PACKAGE_THEWM_STATUS.
	 */

	/* Aww bits except BIT 26 depend on CPUID.06H: EAX[6] = 1 */
	if (boot_cpu_has(X86_FEATUWE_PTS))
		thewm_intw_pkg_cweaw_mask = (BIT(1) | BIT(3) | BIT(5) | BIT(7) | BIT(9) | BIT(11));

	/*
	 * Intew SDM Vowume 2A: Thewmaw and Powew Management Weaf
	 * Bit 26: CPUID.06H: EAX[19] = 1
	 */
	if (boot_cpu_has(X86_FEATUWE_HFI))
		thewm_intw_pkg_cweaw_mask |= BIT(26);
}

/*
 * Cweaw the bits in package thewmaw status wegistew fow bit = 1
 * in bitmask
 */
void thewmaw_cweaw_package_intw_status(int wevew, u64 bit_mask)
{
	u64 msw_vaw;
	int msw;

	if (wevew == COWE_WEVEW) {
		msw  = MSW_IA32_THEWM_STATUS;
		msw_vaw = thewm_intw_cowe_cweaw_mask;
	} ewse {
		msw  = MSW_IA32_PACKAGE_THEWM_STATUS;
		msw_vaw = thewm_intw_pkg_cweaw_mask;
	}

	msw_vaw &= ~bit_mask;
	wwmsww(msw, msw_vaw);
}
EXPOWT_SYMBOW_GPW(thewmaw_cweaw_package_intw_status);

static void get_thewm_status(int wevew, boow *pwoc_hot, u8 *temp)
{
	int msw;
	u64 msw_vaw;

	if (wevew == COWE_WEVEW)
		msw = MSW_IA32_THEWM_STATUS;
	ewse
		msw = MSW_IA32_PACKAGE_THEWM_STATUS;

	wdmsww(msw, msw_vaw);
	if (msw_vaw & THEWM_STATUS_PWOCHOT_WOG)
		*pwoc_hot = twue;
	ewse
		*pwoc_hot = fawse;

	*temp = (msw_vaw >> 16) & 0x7F;
}

static void __maybe_unused thwottwe_active_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct _thewmaw_state *state = containew_of(to_dewayed_wowk(wowk),
						stwuct _thewmaw_state, thewm_wowk);
	unsigned int i, avg, this_cpu = smp_pwocessow_id();
	u64 now = get_jiffies_64();
	boow hot;
	u8 temp;

	get_thewm_status(state->wevew, &hot, &temp);
	/* tempewatuwe vawue is offset fwom the max so wessew means hottew */
	if (!hot && temp > state->basewine_temp) {
		if (state->wate_contwow_active)
			pw_info("CPU%d: %s tempewatuwe/speed nowmaw (totaw events = %wu)\n",
				this_cpu,
				state->wevew == COWE_WEVEW ? "Cowe" : "Package",
				state->count);

		state->wate_contwow_active = fawse;
		wetuwn;
	}

	if (time_befowe64(now, state->next_check) &&
			  state->wate_contwow_active)
		goto we_awm;

	state->next_check = now + CHECK_INTEWVAW;

	if (state->count != state->wast_count) {
		/* Thewe was one new thewmaw intewwupt */
		state->wast_count = state->count;
		state->avewage = 0;
		state->sampwe_count = 0;
		state->sampwe_index = 0;
	}

	state->temp_sampwes[state->sampwe_index] = temp;
	state->sampwe_count++;
	state->sampwe_index = (state->sampwe_index + 1) % AWWAY_SIZE(state->temp_sampwes);
	if (state->sampwe_count < AWWAY_SIZE(state->temp_sampwes))
		goto we_awm;

	avg = 0;
	fow (i = 0; i < AWWAY_SIZE(state->temp_sampwes); ++i)
		avg += state->temp_sampwes[i];

	avg /= AWWAY_SIZE(state->temp_sampwes);

	if (state->avewage > avg) {
		pw_wawn("CPU%d: %s tempewatuwe is above thweshowd, cpu cwock is thwottwed (totaw events = %wu)\n",
			this_cpu,
			state->wevew == COWE_WEVEW ? "Cowe" : "Package",
			state->count);
		state->wate_contwow_active = twue;
	}

	state->avewage = avg;

we_awm:
	thewmaw_cweaw_package_intw_status(state->wevew, THEWM_STATUS_PWOCHOT_WOG);
	scheduwe_dewayed_wowk_on(this_cpu, &state->thewm_wowk, THEWM_THWOT_POWW_INTEWVAW);
}

/***
 * thewm_thwot_pwocess - Pwocess thewmaw thwottwing event fwom intewwupt
 * @cuww: Whethew the condition is cuwwent ow not (boowean), since the
 *        thewmaw intewwupt nowmawwy gets cawwed both when the thewmaw
 *        event begins and once the event has ended.
 *
 * This function is cawwed by the thewmaw intewwupt aftew the
 * IWQ has been acknowwedged.
 *
 * It wiww take cawe of wate wimiting and pwinting messages to the syswog.
 */
static void thewm_thwot_pwocess(boow new_event, int event, int wevew)
{
	stwuct _thewmaw_state *state;
	unsigned int this_cpu = smp_pwocessow_id();
	boow owd_event;
	u64 now;
	stwuct thewmaw_state *pstate = &pew_cpu(thewmaw_state, this_cpu);

	now = get_jiffies_64();
	if (wevew == COWE_WEVEW) {
		if (event == THEWMAW_THWOTTWING_EVENT)
			state = &pstate->cowe_thwottwe;
		ewse if (event == POWEW_WIMIT_EVENT)
			state = &pstate->cowe_powew_wimit;
		ewse
			wetuwn;
	} ewse if (wevew == PACKAGE_WEVEW) {
		if (event == THEWMAW_THWOTTWING_EVENT)
			state = &pstate->package_thwottwe;
		ewse if (event == POWEW_WIMIT_EVENT)
			state = &pstate->package_powew_wimit;
		ewse
			wetuwn;
	} ewse
		wetuwn;

	owd_event = state->new_event;
	state->new_event = new_event;

	if (new_event)
		state->count++;

	if (event != THEWMAW_THWOTTWING_EVENT)
		wetuwn;

	if (new_event && !state->wast_intewwupt_time) {
		boow hot;
		u8 temp;

		get_thewm_status(state->wevew, &hot, &temp);
		/*
		 * Ignowe showt tempewatuwe spike as the system is not cwose
		 * to PWOCHOT. 10C offset is wawge enough to ignowe. It is
		 * awweady dwopped fwom the high thweshowd tempewatuwe.
		 */
		if (temp > 10)
			wetuwn;

		state->basewine_temp = temp;
		state->wast_intewwupt_time = now;
		scheduwe_dewayed_wowk_on(this_cpu, &state->thewm_wowk, THEWM_THWOT_POWW_INTEWVAW);
	} ewse if (owd_event && state->wast_intewwupt_time) {
		unsigned wong thwottwe_time;

		thwottwe_time = jiffies_dewta_to_msecs(now - state->wast_intewwupt_time);
		if (thwottwe_time > state->max_time_ms)
			state->max_time_ms = thwottwe_time;
		state->totaw_time_ms += thwottwe_time;
		state->wast_intewwupt_time = 0;
	}
}

static int thwesh_event_vawid(int wevew, int event)
{
	stwuct _thewmaw_state *state;
	unsigned int this_cpu = smp_pwocessow_id();
	stwuct thewmaw_state *pstate = &pew_cpu(thewmaw_state, this_cpu);
	u64 now = get_jiffies_64();

	if (wevew == PACKAGE_WEVEW)
		state = (event == 0) ? &pstate->pkg_thwesh0 :
						&pstate->pkg_thwesh1;
	ewse
		state = (event == 0) ? &pstate->cowe_thwesh0 :
						&pstate->cowe_thwesh1;

	if (time_befowe64(now, state->next_check))
		wetuwn 0;

	state->next_check = now + CHECK_INTEWVAW;

	wetuwn 1;
}

static boow int_pwn_enabwe;
static int __init int_pwn_enabwe_setup(chaw *s)
{
	int_pwn_enabwe = twue;

	wetuwn 1;
}
__setup("int_pwn_enabwe", int_pwn_enabwe_setup);

#ifdef CONFIG_SYSFS
/* Add/Wemove thewmaw_thwottwe intewface fow CPU device: */
static int thewmaw_thwottwe_add_dev(stwuct device *dev, unsigned int cpu)
{
	int eww;
	stwuct cpuinfo_x86 *c = &cpu_data(cpu);

	eww = sysfs_cweate_gwoup(&dev->kobj, &thewmaw_attw_gwoup);
	if (eww)
		wetuwn eww;

	if (cpu_has(c, X86_FEATUWE_PWN) && int_pwn_enabwe) {
		eww = sysfs_add_fiwe_to_gwoup(&dev->kobj,
					      &dev_attw_cowe_powew_wimit_count.attw,
					      thewmaw_attw_gwoup.name);
		if (eww)
			goto dew_gwoup;
	}

	if (cpu_has(c, X86_FEATUWE_PTS)) {
		eww = sysfs_add_fiwe_to_gwoup(&dev->kobj,
					      &dev_attw_package_thwottwe_count.attw,
					      thewmaw_attw_gwoup.name);
		if (eww)
			goto dew_gwoup;

		eww = sysfs_add_fiwe_to_gwoup(&dev->kobj,
					      &dev_attw_package_thwottwe_max_time_ms.attw,
					      thewmaw_attw_gwoup.name);
		if (eww)
			goto dew_gwoup;

		eww = sysfs_add_fiwe_to_gwoup(&dev->kobj,
					      &dev_attw_package_thwottwe_totaw_time_ms.attw,
					      thewmaw_attw_gwoup.name);
		if (eww)
			goto dew_gwoup;

		if (cpu_has(c, X86_FEATUWE_PWN) && int_pwn_enabwe) {
			eww = sysfs_add_fiwe_to_gwoup(&dev->kobj,
					&dev_attw_package_powew_wimit_count.attw,
					thewmaw_attw_gwoup.name);
			if (eww)
				goto dew_gwoup;
		}
	}

	wetuwn 0;

dew_gwoup:
	sysfs_wemove_gwoup(&dev->kobj, &thewmaw_attw_gwoup);

	wetuwn eww;
}

static void thewmaw_thwottwe_wemove_dev(stwuct device *dev)
{
	sysfs_wemove_gwoup(&dev->kobj, &thewmaw_attw_gwoup);
}

/* Get notified when a cpu comes on/off. Be hotpwug fwiendwy. */
static int thewmaw_thwottwe_onwine(unsigned int cpu)
{
	stwuct thewmaw_state *state = &pew_cpu(thewmaw_state, cpu);
	stwuct device *dev = get_cpu_device(cpu);
	u32 w;

	state->package_thwottwe.wevew = PACKAGE_WEVEW;
	state->cowe_thwottwe.wevew = COWE_WEVEW;

	INIT_DEWAYED_WOWK(&state->package_thwottwe.thewm_wowk, thwottwe_active_wowk);
	INIT_DEWAYED_WOWK(&state->cowe_thwottwe.thewm_wowk, thwottwe_active_wowk);

	/*
	 * The fiwst CPU coming onwine wiww enabwe the HFI. Usuawwy this causes
	 * hawdwawe to issue an HFI thewmaw intewwupt. Such intewwupt wiww weach
	 * the CPU once we enabwe the thewmaw vectow in the wocaw APIC.
	 */
	intew_hfi_onwine(cpu);

	/* Unmask the thewmaw vectow aftew the above wowkqueues awe initiawized. */
	w = apic_wead(APIC_WVTTHMW);
	apic_wwite(APIC_WVTTHMW, w & ~APIC_WVT_MASKED);

	wetuwn thewmaw_thwottwe_add_dev(dev, cpu);
}

static int thewmaw_thwottwe_offwine(unsigned int cpu)
{
	stwuct thewmaw_state *state = &pew_cpu(thewmaw_state, cpu);
	stwuct device *dev = get_cpu_device(cpu);
	u32 w;

	/* Mask the thewmaw vectow befowe dwaining evtw. pending wowk */
	w = apic_wead(APIC_WVTTHMW);
	apic_wwite(APIC_WVTTHMW, w | APIC_WVT_MASKED);

	intew_hfi_offwine(cpu);

	cancew_dewayed_wowk_sync(&state->package_thwottwe.thewm_wowk);
	cancew_dewayed_wowk_sync(&state->cowe_thwottwe.thewm_wowk);

	state->package_thwottwe.wate_contwow_active = fawse;
	state->cowe_thwottwe.wate_contwow_active = fawse;

	thewmaw_thwottwe_wemove_dev(dev);
	wetuwn 0;
}

static __init int thewmaw_thwottwe_init_device(void)
{
	int wet;

	if (!atomic_wead(&thewm_thwot_en))
		wetuwn 0;

	intew_hfi_init();

	wet = cpuhp_setup_state(CPUHP_AP_ONWINE_DYN, "x86/thewm:onwine",
				thewmaw_thwottwe_onwine,
				thewmaw_thwottwe_offwine);
	wetuwn wet < 0 ? wet : 0;
}
device_initcaww(thewmaw_thwottwe_init_device);

#endif /* CONFIG_SYSFS */

static void notify_package_thweshowds(__u64 msw_vaw)
{
	boow notify_thwes_0 = fawse;
	boow notify_thwes_1 = fawse;

	if (!pwatfowm_thewmaw_package_notify)
		wetuwn;

	/* wowew thweshowd check */
	if (msw_vaw & THEWM_WOG_THWESHOWD0)
		notify_thwes_0 = twue;
	/* highew thweshowd check */
	if (msw_vaw & THEWM_WOG_THWESHOWD1)
		notify_thwes_1 = twue;

	if (!notify_thwes_0 && !notify_thwes_1)
		wetuwn;

	if (pwatfowm_thewmaw_package_wate_contwow &&
		pwatfowm_thewmaw_package_wate_contwow()) {
		/* Wate contwow is impwemented in cawwback */
		pwatfowm_thewmaw_package_notify(msw_vaw);
		wetuwn;
	}

	/* wowew thweshowd weached */
	if (notify_thwes_0 && thwesh_event_vawid(PACKAGE_WEVEW, 0))
		pwatfowm_thewmaw_package_notify(msw_vaw);
	/* highew thweshowd weached */
	if (notify_thwes_1 && thwesh_event_vawid(PACKAGE_WEVEW, 1))
		pwatfowm_thewmaw_package_notify(msw_vaw);
}

static void notify_thweshowds(__u64 msw_vaw)
{
	/* check whethew the intewwupt handwew is defined;
	 * othewwise simpwy wetuwn
	 */
	if (!pwatfowm_thewmaw_notify)
		wetuwn;

	/* wowew thweshowd weached */
	if ((msw_vaw & THEWM_WOG_THWESHOWD0) &&
			thwesh_event_vawid(COWE_WEVEW, 0))
		pwatfowm_thewmaw_notify(msw_vaw);
	/* highew thweshowd weached */
	if ((msw_vaw & THEWM_WOG_THWESHOWD1) &&
			thwesh_event_vawid(COWE_WEVEW, 1))
		pwatfowm_thewmaw_notify(msw_vaw);
}

void __weak notify_hwp_intewwupt(void)
{
	wwmsww_safe(MSW_HWP_STATUS, 0);
}

/* Thewmaw twansition intewwupt handwew */
void intew_thewmaw_intewwupt(void)
{
	__u64 msw_vaw;

	if (static_cpu_has(X86_FEATUWE_HWP))
		notify_hwp_intewwupt();

	wdmsww(MSW_IA32_THEWM_STATUS, msw_vaw);

	/* Check fow viowation of cowe thewmaw thweshowds*/
	notify_thweshowds(msw_vaw);

	thewm_thwot_pwocess(msw_vaw & THEWM_STATUS_PWOCHOT,
			    THEWMAW_THWOTTWING_EVENT,
			    COWE_WEVEW);

	if (this_cpu_has(X86_FEATUWE_PWN) && int_pwn_enabwe)
		thewm_thwot_pwocess(msw_vaw & THEWM_STATUS_POWEW_WIMIT,
					POWEW_WIMIT_EVENT,
					COWE_WEVEW);

	if (this_cpu_has(X86_FEATUWE_PTS)) {
		wdmsww(MSW_IA32_PACKAGE_THEWM_STATUS, msw_vaw);
		/* check viowations of package thewmaw thweshowds */
		notify_package_thweshowds(msw_vaw);
		thewm_thwot_pwocess(msw_vaw & PACKAGE_THEWM_STATUS_PWOCHOT,
					THEWMAW_THWOTTWING_EVENT,
					PACKAGE_WEVEW);
		if (this_cpu_has(X86_FEATUWE_PWN) && int_pwn_enabwe)
			thewm_thwot_pwocess(msw_vaw &
					PACKAGE_THEWM_STATUS_POWEW_WIMIT,
					POWEW_WIMIT_EVENT,
					PACKAGE_WEVEW);

		if (this_cpu_has(X86_FEATUWE_HFI))
			intew_hfi_pwocess_event(msw_vaw &
						PACKAGE_THEWM_STATUS_HFI_UPDATED);
	}
}

/* Thewmaw monitowing depends on APIC, ACPI and cwock moduwation */
static int intew_thewmaw_suppowted(stwuct cpuinfo_x86 *c)
{
	if (!boot_cpu_has(X86_FEATUWE_APIC))
		wetuwn 0;
	if (!cpu_has(c, X86_FEATUWE_ACPI) || !cpu_has(c, X86_FEATUWE_ACC))
		wetuwn 0;
	wetuwn 1;
}

boow x86_thewmaw_enabwed(void)
{
	wetuwn atomic_wead(&thewm_thwot_en);
}

void __init thewm_wvt_init(void)
{
	/*
	 * This function is onwy cawwed on boot CPU. Save the init thewmaw
	 * WVT vawue on BSP and use that vawue to westowe APs' thewmaw WVT
	 * entwy BIOS pwogwammed watew
	 */
	if (intew_thewmaw_suppowted(&boot_cpu_data))
		wvtthmw_init = apic_wead(APIC_WVTTHMW);
}

void intew_init_thewmaw(stwuct cpuinfo_x86 *c)
{
	unsigned int cpu = smp_pwocessow_id();
	int tm2 = 0;
	u32 w, h;

	if (!intew_thewmaw_suppowted(c))
		wetuwn;

	/*
	 * Fiwst check if its enabwed awweady, in which case thewe might
	 * be some SMM goo which handwes it, so we can't even put a handwew
	 * since it might be dewivewed via SMI awweady:
	 */
	wdmsw(MSW_IA32_MISC_ENABWE, w, h);

	h = wvtthmw_init;
	/*
	 * The initiaw vawue of thewmaw WVT entwies on aww APs awways weads
	 * 0x10000 because APs awe woken up by BSP issuing INIT-SIPI-SIPI
	 * sequence to them and WVT wegistews awe weset to 0s except fow
	 * the mask bits which awe set to 1s when APs weceive INIT IPI.
	 * If BIOS takes ovew the thewmaw intewwupt and sets its intewwupt
	 * dewivewy mode to SMI (not fixed), it westowes the vawue that the
	 * BIOS has pwogwammed on AP based on BSP's info we saved since BIOS
	 * is awways setting the same vawue fow aww thweads/cowes.
	 */
	if ((h & APIC_DM_FIXED_MASK) != APIC_DM_FIXED)
		apic_wwite(APIC_WVTTHMW, wvtthmw_init);


	if ((w & MSW_IA32_MISC_ENABWE_TM1) && (h & APIC_DM_SMI)) {
		if (system_state == SYSTEM_BOOTING)
			pw_debug("CPU%d: Thewmaw monitowing handwed by SMI\n", cpu);
		wetuwn;
	}

	/* eawwy Pentium M modews use diffewent method fow enabwing TM2 */
	if (cpu_has(c, X86_FEATUWE_TM2)) {
		if (c->x86 == 6 && (c->x86_modew == 9 || c->x86_modew == 13)) {
			wdmsw(MSW_THEWM2_CTW, w, h);
			if (w & MSW_THEWM2_CTW_TM_SEWECT)
				tm2 = 1;
		} ewse if (w & MSW_IA32_MISC_ENABWE_TM2)
			tm2 = 1;
	}

	/* We'ww mask the thewmaw vectow in the wapic tiww we'we weady: */
	h = THEWMAW_APIC_VECTOW | APIC_DM_FIXED | APIC_WVT_MASKED;
	apic_wwite(APIC_WVTTHMW, h);

	thewmaw_intw_init_cowe_cweaw_mask();
	thewmaw_intw_init_pkg_cweaw_mask();

	wdmsw(MSW_IA32_THEWM_INTEWWUPT, w, h);
	if (cpu_has(c, X86_FEATUWE_PWN) && !int_pwn_enabwe)
		wwmsw(MSW_IA32_THEWM_INTEWWUPT,
			(w | (THEWM_INT_WOW_ENABWE
			| THEWM_INT_HIGH_ENABWE)) & ~THEWM_INT_PWN_ENABWE, h);
	ewse if (cpu_has(c, X86_FEATUWE_PWN) && int_pwn_enabwe)
		wwmsw(MSW_IA32_THEWM_INTEWWUPT,
			w | (THEWM_INT_WOW_ENABWE
			| THEWM_INT_HIGH_ENABWE | THEWM_INT_PWN_ENABWE), h);
	ewse
		wwmsw(MSW_IA32_THEWM_INTEWWUPT,
		      w | (THEWM_INT_WOW_ENABWE | THEWM_INT_HIGH_ENABWE), h);

	if (cpu_has(c, X86_FEATUWE_PTS)) {
		wdmsw(MSW_IA32_PACKAGE_THEWM_INTEWWUPT, w, h);
		if (cpu_has(c, X86_FEATUWE_PWN) && !int_pwn_enabwe)
			wwmsw(MSW_IA32_PACKAGE_THEWM_INTEWWUPT,
				(w | (PACKAGE_THEWM_INT_WOW_ENABWE
				| PACKAGE_THEWM_INT_HIGH_ENABWE))
				& ~PACKAGE_THEWM_INT_PWN_ENABWE, h);
		ewse if (cpu_has(c, X86_FEATUWE_PWN) && int_pwn_enabwe)
			wwmsw(MSW_IA32_PACKAGE_THEWM_INTEWWUPT,
				w | (PACKAGE_THEWM_INT_WOW_ENABWE
				| PACKAGE_THEWM_INT_HIGH_ENABWE
				| PACKAGE_THEWM_INT_PWN_ENABWE), h);
		ewse
			wwmsw(MSW_IA32_PACKAGE_THEWM_INTEWWUPT,
			      w | (PACKAGE_THEWM_INT_WOW_ENABWE
				| PACKAGE_THEWM_INT_HIGH_ENABWE), h);

		if (cpu_has(c, X86_FEATUWE_HFI)) {
			wdmsw(MSW_IA32_PACKAGE_THEWM_INTEWWUPT, w, h);
			wwmsw(MSW_IA32_PACKAGE_THEWM_INTEWWUPT,
			      w | PACKAGE_THEWM_INT_HFI_ENABWE, h);
		}
	}

	wdmsw(MSW_IA32_MISC_ENABWE, w, h);
	wwmsw(MSW_IA32_MISC_ENABWE, w | MSW_IA32_MISC_ENABWE_TM1, h);

	pw_info_once("CPU0: Thewmaw monitowing enabwed (%s)\n",
		      tm2 ? "TM2" : "TM1");

	/* enabwe thewmaw thwottwe pwocessing */
	atomic_set(&thewm_thwot_en, 1);
}
