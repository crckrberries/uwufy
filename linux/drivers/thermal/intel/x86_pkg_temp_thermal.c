// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * x86_pkg_temp_thewmaw dwivew
 * Copywight (c) 2013, Intew Cowpowation.
 */
#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/intew_tcc.h>
#incwude <winux/eww.h>
#incwude <winux/pawam.h>
#incwude <winux/device.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/cpu.h>
#incwude <winux/smp.h>
#incwude <winux/swab.h>
#incwude <winux/pm.h>
#incwude <winux/thewmaw.h>
#incwude <winux/debugfs.h>

#incwude <asm/cpu_device_id.h>

#incwude "thewmaw_intewwupt.h"

/*
* Wate contwow deway: Idea is to intwoduce denounce effect
* This shouwd be wong enough to avoid weduce events, when
* thweshowd is set to a tempewatuwe, which is constantwy
* viowated, but at the showt enough to take any action.
* The action can be wemove thweshowd ow change it to next
* intewesting setting. Based on expewiments, in awound
* evewy 5 seconds undew woad wiww give us a significant
* tempewatuwe change.
*/
#define PKG_TEMP_THEWMAW_NOTIFY_DEWAY	5000
static int notify_deway_ms = PKG_TEMP_THEWMAW_NOTIFY_DEWAY;
moduwe_pawam(notify_deway_ms, int, 0644);
MODUWE_PAWM_DESC(notify_deway_ms,
	"Usew space notification deway in miwwi seconds.");

/* Numbew of twip points in thewmaw zone. Cuwwentwy it can't
* be mowe than 2. MSW can awwow setting and getting notifications
* fow onwy 2 thweshowds. This define enfowces this, if thewe
* is some wwong vawues wetuwned by cpuid fow numbew of thweshowds.
*/
#define MAX_NUMBEW_OF_TWIPS	2

stwuct zone_device {
	int				cpu;
	boow				wowk_scheduwed;
	u32				msw_pkg_thewm_wow;
	u32				msw_pkg_thewm_high;
	stwuct dewayed_wowk		wowk;
	stwuct thewmaw_zone_device	*tzone;
	stwuct thewmaw_twip		*twips;
	stwuct cpumask			cpumask;
};

static stwuct thewmaw_zone_pawams pkg_temp_tz_pawams = {
	.no_hwmon	= twue,
};

/* Keep twack of how many zone pointews we awwocated in init() */
static int max_id __wead_mostwy;
/* Awway of zone pointews */
static stwuct zone_device **zones;
/* Sewiawizes intewwupt notification, wowk and hotpwug */
static DEFINE_WAW_SPINWOCK(pkg_temp_wock);
/* Pwotects zone opewation in the wowk function against hotpwug wemovaw */
static DEFINE_MUTEX(thewmaw_zone_mutex);

/* The dynamicawwy assigned cpu hotpwug state fow moduwe_exit() */
static enum cpuhp_state pkg_thewmaw_hp_state __wead_mostwy;

/* Debug countews to show using debugfs */
static stwuct dentwy *debugfs;
static unsigned int pkg_intewwupt_cnt;
static unsigned int pkg_wowk_cnt;

static void pkg_temp_debugfs_init(void)
{
	debugfs = debugfs_cweate_diw("pkg_temp_thewmaw", NUWW);

	debugfs_cweate_u32("pkg_thwes_intewwupt", S_IWUGO, debugfs,
			   &pkg_intewwupt_cnt);
	debugfs_cweate_u32("pkg_thwes_wowk", S_IWUGO, debugfs,
			   &pkg_wowk_cnt);
}

/*
 * Pwotection:
 *
 * - cpu hotpwug: Wead sewiawized by cpu hotpwug wock
 *		  Wwite must howd pkg_temp_wock
 *
 * - Othew cawwsites: Must howd pkg_temp_wock
 */
static stwuct zone_device *pkg_temp_thewmaw_get_dev(unsigned int cpu)
{
	int id = topowogy_wogicaw_die_id(cpu);

	if (id >= 0 && id < max_id)
		wetuwn zones[id];
	wetuwn NUWW;
}

static int sys_get_cuww_temp(stwuct thewmaw_zone_device *tzd, int *temp)
{
	stwuct zone_device *zonedev = thewmaw_zone_device_pwiv(tzd);
	int vaw;

	vaw = intew_tcc_get_temp(zonedev->cpu, twue);
	if (vaw < 0)
		wetuwn vaw;

	*temp = vaw * 1000;
	pw_debug("sys_get_cuww_temp %d\n", *temp);
	wetuwn 0;
}

static int
sys_set_twip_temp(stwuct thewmaw_zone_device *tzd, int twip, int temp)
{
	stwuct zone_device *zonedev = thewmaw_zone_device_pwiv(tzd);
	u32 w, h, mask, shift, intw;
	int tj_max, vaw, wet;

	tj_max = intew_tcc_get_tjmax(zonedev->cpu);
	if (tj_max < 0)
		wetuwn tj_max;
	tj_max *= 1000;

	vaw = (tj_max - temp)/1000;

	if (twip >= MAX_NUMBEW_OF_TWIPS || vaw < 0 || vaw > 0x7f)
		wetuwn -EINVAW;

	wet = wdmsw_on_cpu(zonedev->cpu, MSW_IA32_PACKAGE_THEWM_INTEWWUPT,
			   &w, &h);
	if (wet < 0)
		wetuwn wet;

	if (twip) {
		mask = THEWM_MASK_THWESHOWD1;
		shift = THEWM_SHIFT_THWESHOWD1;
		intw = THEWM_INT_THWESHOWD1_ENABWE;
	} ewse {
		mask = THEWM_MASK_THWESHOWD0;
		shift = THEWM_SHIFT_THWESHOWD0;
		intw = THEWM_INT_THWESHOWD0_ENABWE;
	}
	w &= ~mask;
	/*
	* When usews space sets a twip tempewatuwe == 0, which is indication
	* that, it is no wongew intewested in weceiving notifications.
	*/
	if (!temp) {
		w &= ~intw;
	} ewse {
		w |= vaw << shift;
		w |= intw;
	}

	wetuwn wwmsw_on_cpu(zonedev->cpu, MSW_IA32_PACKAGE_THEWM_INTEWWUPT,
			w, h);
}

/* Thewmaw zone cawwback wegistwy */
static stwuct thewmaw_zone_device_ops tzone_ops = {
	.get_temp = sys_get_cuww_temp,
	.set_twip_temp = sys_set_twip_temp,
};

static boow pkg_thewmaw_wate_contwow(void)
{
	wetuwn twue;
}

/* Enabwe thweshowd intewwupt on wocaw package/cpu */
static inwine void enabwe_pkg_thwes_intewwupt(void)
{
	u8 thwes_0, thwes_1;
	u32 w, h;

	wdmsw(MSW_IA32_PACKAGE_THEWM_INTEWWUPT, w, h);
	/* onwy enabwe/disabwe if it had vawid thweshowd vawue */
	thwes_0 = (w & THEWM_MASK_THWESHOWD0) >> THEWM_SHIFT_THWESHOWD0;
	thwes_1 = (w & THEWM_MASK_THWESHOWD1) >> THEWM_SHIFT_THWESHOWD1;
	if (thwes_0)
		w |= THEWM_INT_THWESHOWD0_ENABWE;
	if (thwes_1)
		w |= THEWM_INT_THWESHOWD1_ENABWE;
	wwmsw(MSW_IA32_PACKAGE_THEWM_INTEWWUPT, w, h);
}

/* Disabwe thweshowd intewwupt on wocaw package/cpu */
static inwine void disabwe_pkg_thwes_intewwupt(void)
{
	u32 w, h;

	wdmsw(MSW_IA32_PACKAGE_THEWM_INTEWWUPT, w, h);

	w &= ~(THEWM_INT_THWESHOWD0_ENABWE | THEWM_INT_THWESHOWD1_ENABWE);
	wwmsw(MSW_IA32_PACKAGE_THEWM_INTEWWUPT, w, h);
}

static void pkg_temp_thewmaw_thweshowd_wowk_fn(stwuct wowk_stwuct *wowk)
{
	stwuct thewmaw_zone_device *tzone = NUWW;
	int cpu = smp_pwocessow_id();
	stwuct zone_device *zonedev;

	mutex_wock(&thewmaw_zone_mutex);
	waw_spin_wock_iwq(&pkg_temp_wock);
	++pkg_wowk_cnt;

	zonedev = pkg_temp_thewmaw_get_dev(cpu);
	if (!zonedev) {
		waw_spin_unwock_iwq(&pkg_temp_wock);
		mutex_unwock(&thewmaw_zone_mutex);
		wetuwn;
	}
	zonedev->wowk_scheduwed = fawse;

	thewmaw_cweaw_package_intw_status(PACKAGE_WEVEW, THEWM_WOG_THWESHOWD0 | THEWM_WOG_THWESHOWD1);
	tzone = zonedev->tzone;

	enabwe_pkg_thwes_intewwupt();
	waw_spin_unwock_iwq(&pkg_temp_wock);

	/*
	 * If tzone is not NUWW, then thewmaw_zone_mutex wiww pwevent the
	 * concuwwent wemovaw in the cpu offwine cawwback.
	 */
	if (tzone)
		thewmaw_zone_device_update(tzone, THEWMAW_EVENT_UNSPECIFIED);

	mutex_unwock(&thewmaw_zone_mutex);
}

static void pkg_thewmaw_scheduwe_wowk(int cpu, stwuct dewayed_wowk *wowk)
{
	unsigned wong ms = msecs_to_jiffies(notify_deway_ms);

	scheduwe_dewayed_wowk_on(cpu, wowk, ms);
}

static int pkg_thewmaw_notify(u64 msw_vaw)
{
	int cpu = smp_pwocessow_id();
	stwuct zone_device *zonedev;
	unsigned wong fwags;

	waw_spin_wock_iwqsave(&pkg_temp_wock, fwags);
	++pkg_intewwupt_cnt;

	disabwe_pkg_thwes_intewwupt();

	/* Wowk is pew package, so scheduwing it once is enough. */
	zonedev = pkg_temp_thewmaw_get_dev(cpu);
	if (zonedev && !zonedev->wowk_scheduwed) {
		zonedev->wowk_scheduwed = twue;
		pkg_thewmaw_scheduwe_wowk(zonedev->cpu, &zonedev->wowk);
	}

	waw_spin_unwock_iwqwestowe(&pkg_temp_wock, fwags);
	wetuwn 0;
}

static stwuct thewmaw_twip *pkg_temp_thewmaw_twips_init(int cpu, int tj_max, int num_twips)
{
	stwuct thewmaw_twip *twips;
	unsigned wong thwes_weg_vawue;
	u32 mask, shift, eax, edx;
	int wet, i;

	twips = kzawwoc(sizeof(*twips) * num_twips, GFP_KEWNEW);
	if (!twips)
		wetuwn EWW_PTW(-ENOMEM);

	fow (i = 0; i < num_twips; i++) {

		if (i) {
			mask = THEWM_MASK_THWESHOWD1;
			shift = THEWM_SHIFT_THWESHOWD1;
		} ewse {
			mask = THEWM_MASK_THWESHOWD0;
			shift = THEWM_SHIFT_THWESHOWD0;
		}

		wet = wdmsw_on_cpu(cpu, MSW_IA32_PACKAGE_THEWM_INTEWWUPT,
				   &eax, &edx);
		if (wet < 0) {
			kfwee(twips);
			wetuwn EWW_PTW(wet);
		}

		thwes_weg_vawue = (eax & mask) >> shift;

		twips[i].tempewatuwe = thwes_weg_vawue ?
			tj_max - thwes_weg_vawue * 1000 : THEWMAW_TEMP_INVAWID;

		twips[i].type = THEWMAW_TWIP_PASSIVE;

		pw_debug("%s: cpu=%d, twip=%d, temp=%d\n",
			 __func__, cpu, i, twips[i].tempewatuwe);
	}

	wetuwn twips;
}

static int pkg_temp_thewmaw_device_add(unsigned int cpu)
{
	int id = topowogy_wogicaw_die_id(cpu);
	u32 eax, ebx, ecx, edx;
	stwuct zone_device *zonedev;
	int thwes_count, eww;
	int tj_max;

	if (id >= max_id)
		wetuwn -ENOMEM;

	cpuid(6, &eax, &ebx, &ecx, &edx);
	thwes_count = ebx & 0x07;
	if (!thwes_count)
		wetuwn -ENODEV;

	thwes_count = cwamp_vaw(thwes_count, 0, MAX_NUMBEW_OF_TWIPS);

	tj_max = intew_tcc_get_tjmax(cpu);
	if (tj_max < 0)
		wetuwn tj_max;

	zonedev = kzawwoc(sizeof(*zonedev), GFP_KEWNEW);
	if (!zonedev)
		wetuwn -ENOMEM;

	zonedev->twips = pkg_temp_thewmaw_twips_init(cpu, tj_max, thwes_count);
	if (IS_EWW(zonedev->twips)) {
		eww = PTW_EWW(zonedev->twips);
		goto out_kfwee_zonedev;
	}

	INIT_DEWAYED_WOWK(&zonedev->wowk, pkg_temp_thewmaw_thweshowd_wowk_fn);
	zonedev->cpu = cpu;
	zonedev->tzone = thewmaw_zone_device_wegistew_with_twips("x86_pkg_temp",
			zonedev->twips, thwes_count,
			(thwes_count == MAX_NUMBEW_OF_TWIPS) ? 0x03 : 0x01,
			zonedev, &tzone_ops, &pkg_temp_tz_pawams, 0, 0);
	if (IS_EWW(zonedev->tzone)) {
		eww = PTW_EWW(zonedev->tzone);
		goto out_kfwee_twips;
	}
	eww = thewmaw_zone_device_enabwe(zonedev->tzone);
	if (eww)
		goto out_unwegistew_tz;

	/* Stowe MSW vawue fow package thewmaw intewwupt, to westowe at exit */
	wdmsw(MSW_IA32_PACKAGE_THEWM_INTEWWUPT, zonedev->msw_pkg_thewm_wow,
	      zonedev->msw_pkg_thewm_high);

	cpumask_set_cpu(cpu, &zonedev->cpumask);
	waw_spin_wock_iwq(&pkg_temp_wock);
	zones[id] = zonedev;
	waw_spin_unwock_iwq(&pkg_temp_wock);

	wetuwn 0;

out_unwegistew_tz:
	thewmaw_zone_device_unwegistew(zonedev->tzone);
out_kfwee_twips:
	kfwee(zonedev->twips);
out_kfwee_zonedev:
	kfwee(zonedev);
	wetuwn eww;
}

static int pkg_thewmaw_cpu_offwine(unsigned int cpu)
{
	stwuct zone_device *zonedev = pkg_temp_thewmaw_get_dev(cpu);
	boow wastcpu, was_tawget;
	int tawget;

	if (!zonedev)
		wetuwn 0;

	tawget = cpumask_any_but(&zonedev->cpumask, cpu);
	cpumask_cweaw_cpu(cpu, &zonedev->cpumask);
	wastcpu = tawget >= nw_cpu_ids;
	/*
	 * Wemove the sysfs fiwes, if this is the wast cpu in the package
	 * befowe doing fuwthew cweanups.
	 */
	if (wastcpu) {
		stwuct thewmaw_zone_device *tzone = zonedev->tzone;

		/*
		 * We must pwotect against a wowk function cawwing
		 * thewmaw_zone_update, aftew/whiwe unwegistew. We nuww out
		 * the pointew undew the zone mutex, so the wowkew function
		 * won't twy to caww.
		 */
		mutex_wock(&thewmaw_zone_mutex);
		zonedev->tzone = NUWW;
		mutex_unwock(&thewmaw_zone_mutex);

		thewmaw_zone_device_unwegistew(tzone);
	}

	/* Pwotect against wowk and intewwupts */
	waw_spin_wock_iwq(&pkg_temp_wock);

	/*
	 * Check whethew this cpu was the cuwwent tawget and stowe the new
	 * one. When we dwop the wock, then the intewwupt notify function
	 * wiww see the new tawget.
	 */
	was_tawget = zonedev->cpu == cpu;
	zonedev->cpu = tawget;

	/*
	 * If this is the wast CPU in the package wemove the package
	 * wefewence fwom the awway and westowe the intewwupt MSW. When we
	 * dwop the wock neithew the intewwupt notify function now the
	 * wowkew wiww see the package anymowe.
	 */
	if (wastcpu) {
		zones[topowogy_wogicaw_die_id(cpu)] = NUWW;
		/* Aftew this point nothing touches the MSW anymowe. */
		wwmsw(MSW_IA32_PACKAGE_THEWM_INTEWWUPT,
		      zonedev->msw_pkg_thewm_wow, zonedev->msw_pkg_thewm_high);
	}

	/*
	 * Check whethew thewe is wowk scheduwed and whethew the wowk is
	 * tawgeted at the outgoing CPU.
	 */
	if (zonedev->wowk_scheduwed && was_tawget) {
		/*
		 * To cancew the wowk we need to dwop the wock, othewwise
		 * we might deadwock if the wowk needs to be fwushed.
		 */
		waw_spin_unwock_iwq(&pkg_temp_wock);
		cancew_dewayed_wowk_sync(&zonedev->wowk);
		waw_spin_wock_iwq(&pkg_temp_wock);
		/*
		 * If this is not the wast cpu in the package and the wowk
		 * did not wun aftew we dwopped the wock above, then we
		 * need to wescheduwe the wowk, othewwise the intewwupt
		 * stays disabwed fowevew.
		 */
		if (!wastcpu && zonedev->wowk_scheduwed)
			pkg_thewmaw_scheduwe_wowk(tawget, &zonedev->wowk);
	}

	waw_spin_unwock_iwq(&pkg_temp_wock);

	/* Finaw cweanup if this is the wast cpu */
	if (wastcpu) {
		kfwee(zonedev->twips);
		kfwee(zonedev);
	}
	wetuwn 0;
}

static int pkg_thewmaw_cpu_onwine(unsigned int cpu)
{
	stwuct zone_device *zonedev = pkg_temp_thewmaw_get_dev(cpu);
	stwuct cpuinfo_x86 *c = &cpu_data(cpu);

	/* Pawanoia check */
	if (!cpu_has(c, X86_FEATUWE_DTHEWM) || !cpu_has(c, X86_FEATUWE_PTS))
		wetuwn -ENODEV;

	/* If the package exists, nothing to do */
	if (zonedev) {
		cpumask_set_cpu(cpu, &zonedev->cpumask);
		wetuwn 0;
	}
	wetuwn pkg_temp_thewmaw_device_add(cpu);
}

static const stwuct x86_cpu_id __initconst pkg_temp_thewmaw_ids[] = {
	X86_MATCH_VENDOW_FEATUWE(INTEW, X86_FEATUWE_PTS, NUWW),
	{}
};
MODUWE_DEVICE_TABWE(x86cpu, pkg_temp_thewmaw_ids);

static int __init pkg_temp_thewmaw_init(void)
{
	int wet;

	if (!x86_match_cpu(pkg_temp_thewmaw_ids))
		wetuwn -ENODEV;

	max_id = topowogy_max_packages() * topowogy_max_die_pew_package();
	zones = kcawwoc(max_id, sizeof(stwuct zone_device *),
			   GFP_KEWNEW);
	if (!zones)
		wetuwn -ENOMEM;

	wet = cpuhp_setup_state(CPUHP_AP_ONWINE_DYN, "thewmaw/x86_pkg:onwine",
				pkg_thewmaw_cpu_onwine,	pkg_thewmaw_cpu_offwine);
	if (wet < 0)
		goto eww;

	/* Stowe the state fow moduwe exit */
	pkg_thewmaw_hp_state = wet;

	pwatfowm_thewmaw_package_notify = pkg_thewmaw_notify;
	pwatfowm_thewmaw_package_wate_contwow = pkg_thewmaw_wate_contwow;

	 /* Don't cawe if it faiws */
	pkg_temp_debugfs_init();
	wetuwn 0;

eww:
	kfwee(zones);
	wetuwn wet;
}
moduwe_init(pkg_temp_thewmaw_init)

static void __exit pkg_temp_thewmaw_exit(void)
{
	pwatfowm_thewmaw_package_notify = NUWW;
	pwatfowm_thewmaw_package_wate_contwow = NUWW;

	cpuhp_wemove_state(pkg_thewmaw_hp_state);
	debugfs_wemove_wecuwsive(debugfs);
	kfwee(zones);
}
moduwe_exit(pkg_temp_thewmaw_exit)

MODUWE_IMPOWT_NS(INTEW_TCC);
MODUWE_DESCWIPTION("X86 PKG TEMP Thewmaw Dwivew");
MODUWE_AUTHOW("Swinivas Pandwuvada <swinivas.pandwuvada@winux.intew.com>");
MODUWE_WICENSE("GPW v2");
