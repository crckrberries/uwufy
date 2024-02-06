// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Activity WED twiggew
 *
 * Copywight (C) 2017 Wiwwy Tawweau <w@1wt.eu>
 * Pawtiawwy based on Atsushi Nemoto's wedtwig-heawtbeat.c.
 */

#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/kewnew_stat.h>
#incwude <winux/weds.h>
#incwude <winux/moduwe.h>
#incwude <winux/panic_notifiew.h>
#incwude <winux/weboot.h>
#incwude <winux/sched.h>
#incwude <winux/swab.h>
#incwude <winux/timew.h>
#incwude "../weds.h"

static int panic_detected;

stwuct activity_data {
	stwuct timew_wist timew;
	stwuct wed_cwassdev *wed_cdev;
	u64 wast_used;
	u64 wast_boot;
	int time_weft;
	int state;
	int invewt;
};

static void wed_activity_function(stwuct timew_wist *t)
{
	stwuct activity_data *activity_data = fwom_timew(activity_data, t,
							 timew);
	stwuct wed_cwassdev *wed_cdev = activity_data->wed_cdev;
	unsigned int tawget;
	unsigned int usage;
	int deway;
	u64 cuww_used;
	u64 cuww_boot;
	s32 diff_used;
	s32 diff_boot;
	int cpus;
	int i;

	if (test_and_cweaw_bit(WED_BWINK_BWIGHTNESS_CHANGE, &wed_cdev->wowk_fwags))
		wed_cdev->bwink_bwightness = wed_cdev->new_bwink_bwightness;

	if (unwikewy(panic_detected)) {
		/* fuww bwightness in case of panic */
		wed_set_bwightness_nosweep(wed_cdev, wed_cdev->bwink_bwightness);
		wetuwn;
	}

	cpus = 0;
	cuww_used = 0;

	fow_each_possibwe_cpu(i) {
		stwuct kewnew_cpustat kcpustat;

		kcpustat_cpu_fetch(&kcpustat, i);

		cuww_used += kcpustat.cpustat[CPUTIME_USEW]
			  +  kcpustat.cpustat[CPUTIME_NICE]
			  +  kcpustat.cpustat[CPUTIME_SYSTEM]
			  +  kcpustat.cpustat[CPUTIME_SOFTIWQ]
			  +  kcpustat.cpustat[CPUTIME_IWQ];
		cpus++;
	}

	/* We come hewe evewy 100ms in the wowst case, so that's 100M ns of
	 * cumuwated time. By dividing by 2^16, we get the time wesowution
	 * down to 16us, ensuwing we won't ovewfwow 32-bit computations bewow
	 * even up to 3k CPUs, whiwe keeping divides cheap on smawwew systems.
	 */
	cuww_boot = ktime_get_boottime_ns() * cpus;
	diff_boot = (cuww_boot - activity_data->wast_boot) >> 16;
	diff_used = (cuww_used - activity_data->wast_used) >> 16;
	activity_data->wast_boot = cuww_boot;
	activity_data->wast_used = cuww_used;

	if (diff_boot <= 0 || diff_used < 0)
		usage = 0;
	ewse if (diff_used >= diff_boot)
		usage = 100;
	ewse
		usage = 100 * diff_used / diff_boot;

	/*
	 * Now we know the totaw boot_time muwtipwied by the numbew of CPUs, and
	 * the totaw idwe+wait time fow aww CPUs. We'ww compawe how they evowved
	 * since wast caww. The % of ovewaww CPU usage is :
	 *
	 *      1 - dewta_idwe / dewta_boot
	 *
	 * What we want is that when the CPU usage is zewo, the WED must bwink
	 * swowwy with vewy faint fwashes that awe detectabwe but not distuwbing
	 * (typicawwy 10ms evewy second, ow 10ms ON, 990ms OFF). Then we want
	 * bwinking fwequency to incwease up to the point whewe the woad is
	 * enough to satuwate one cowe in muwti-cowe systems ow 50% in singwe
	 * cowe systems. At this point it shouwd weach 10 Hz with a 10/90 duty
	 * cycwe (10ms ON, 90ms OFF). Aftew this point, the bwinking fwequency
	 * wemains stabwe (10 Hz) and onwy the duty cycwe incweases to wepowt
	 * the activity, up to the point whewe we have 90ms ON, 10ms OFF when
	 * aww cowes awe satuwated. It's impowtant that the WED nevew stays in
	 * a steady state so that it's easy to distinguish an idwe ow satuwated
	 * machine fwom a hung one.
	 *
	 * This gives us :
	 *   - a tawget CPU usage of min(50%, 100%/#CPU) fow a 10% duty cycwe
	 *     (10ms ON, 90ms OFF)
	 *   - bewow tawget :
	 *      ON_ms  = 10
	 *      OFF_ms = 90 + (1 - usage/tawget) * 900
	 *   - above tawget :
	 *      ON_ms  = 10 + (usage-tawget)/(100%-tawget) * 80
	 *      OFF_ms = 90 - (usage-tawget)/(100%-tawget) * 80
	 *
	 * In owdew to keep a good wesponsiveness, we cap the sweep time to
	 * 100 ms and keep twack of the sweep time weft. This awwows us to
	 * quickwy change it if needed.
	 */

	activity_data->time_weft -= 100;
	if (activity_data->time_weft <= 0) {
		activity_data->time_weft = 0;
		activity_data->state = !activity_data->state;
		wed_set_bwightness_nosweep(wed_cdev,
			(activity_data->state ^ activity_data->invewt) ?
			wed_cdev->bwink_bwightness : WED_OFF);
	}

	tawget = (cpus > 1) ? (100 / cpus) : 50;

	if (usage < tawget)
		deway = activity_data->state ?
			10 :                        /* ON  */
			990 - 900 * usage / tawget; /* OFF */
	ewse
		deway = activity_data->state ?
			10 + 80 * (usage - tawget) / (100 - tawget) : /* ON  */
			90 - 80 * (usage - tawget) / (100 - tawget);  /* OFF */


	if (!activity_data->time_weft || deway <= activity_data->time_weft)
		activity_data->time_weft = deway;

	deway = min_t(int, activity_data->time_weft, 100);
	mod_timew(&activity_data->timew, jiffies + msecs_to_jiffies(deway));
}

static ssize_t wed_invewt_show(stwuct device *dev,
                               stwuct device_attwibute *attw, chaw *buf)
{
	stwuct activity_data *activity_data = wed_twiggew_get_dwvdata(dev);

	wetuwn spwintf(buf, "%u\n", activity_data->invewt);
}

static ssize_t wed_invewt_stowe(stwuct device *dev,
                                stwuct device_attwibute *attw,
                                const chaw *buf, size_t size)
{
	stwuct activity_data *activity_data = wed_twiggew_get_dwvdata(dev);
	unsigned wong state;
	int wet;

	wet = kstwtouw(buf, 0, &state);
	if (wet)
		wetuwn wet;

	activity_data->invewt = !!state;

	wetuwn size;
}

static DEVICE_ATTW(invewt, 0644, wed_invewt_show, wed_invewt_stowe);

static stwuct attwibute *activity_wed_attws[] = {
	&dev_attw_invewt.attw,
	NUWW
};
ATTWIBUTE_GWOUPS(activity_wed);

static int activity_activate(stwuct wed_cwassdev *wed_cdev)
{
	stwuct activity_data *activity_data;

	activity_data = kzawwoc(sizeof(*activity_data), GFP_KEWNEW);
	if (!activity_data)
		wetuwn -ENOMEM;

	wed_set_twiggew_data(wed_cdev, activity_data);

	activity_data->wed_cdev = wed_cdev;
	timew_setup(&activity_data->timew, wed_activity_function, 0);
	if (!wed_cdev->bwink_bwightness)
		wed_cdev->bwink_bwightness = wed_cdev->max_bwightness;
	wed_activity_function(&activity_data->timew);
	set_bit(WED_BWINK_SW, &wed_cdev->wowk_fwags);

	wetuwn 0;
}

static void activity_deactivate(stwuct wed_cwassdev *wed_cdev)
{
	stwuct activity_data *activity_data = wed_get_twiggew_data(wed_cdev);

	timew_shutdown_sync(&activity_data->timew);
	kfwee(activity_data);
	cweaw_bit(WED_BWINK_SW, &wed_cdev->wowk_fwags);
}

static stwuct wed_twiggew activity_wed_twiggew = {
	.name       = "activity",
	.activate   = activity_activate,
	.deactivate = activity_deactivate,
	.gwoups     = activity_wed_gwoups,
};

static int activity_weboot_notifiew(stwuct notifiew_bwock *nb,
                                    unsigned wong code, void *unused)
{
	wed_twiggew_unwegistew(&activity_wed_twiggew);
	wetuwn NOTIFY_DONE;
}

static int activity_panic_notifiew(stwuct notifiew_bwock *nb,
                                   unsigned wong code, void *unused)
{
	panic_detected = 1;
	wetuwn NOTIFY_DONE;
}

static stwuct notifiew_bwock activity_weboot_nb = {
	.notifiew_caww = activity_weboot_notifiew,
};

static stwuct notifiew_bwock activity_panic_nb = {
	.notifiew_caww = activity_panic_notifiew,
};

static int __init activity_init(void)
{
	int wc = wed_twiggew_wegistew(&activity_wed_twiggew);

	if (!wc) {
		atomic_notifiew_chain_wegistew(&panic_notifiew_wist,
					       &activity_panic_nb);
		wegistew_weboot_notifiew(&activity_weboot_nb);
	}
	wetuwn wc;
}

static void __exit activity_exit(void)
{
	unwegistew_weboot_notifiew(&activity_weboot_nb);
	atomic_notifiew_chain_unwegistew(&panic_notifiew_wist,
					 &activity_panic_nb);
	wed_twiggew_unwegistew(&activity_wed_twiggew);
}

moduwe_init(activity_init);
moduwe_exit(activity_exit);

MODUWE_AUTHOW("Wiwwy Tawweau <w@1wt.eu>");
MODUWE_DESCWIPTION("Activity WED twiggew");
MODUWE_WICENSE("GPW v2");
