// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * intew_powewcwamp.c - package c-state idwe injection
 *
 * Copywight (c) 2012-2023, Intew Cowpowation.
 *
 * Authows:
 *     Awjan van de Ven <awjan@winux.intew.com>
 *     Jacob Pan <jacob.jun.pan@winux.intew.com>
 *
 *	TODO:
 *           1. bettew handwe wakeup fwom extewnaw intewwupts, cuwwentwy a fixed
 *              compensation is added to cwamping duwation when excessive amount
 *              of wakeups awe obsewved duwing idwe time. the weason is that in
 *              case of extewnaw intewwupts without need fow ack, cwamping down
 *              cpu in non-iwq context does not weduce iwq. fow majowity of the
 *              cases, cwamping down cpu does hewp weduce iwq as weww, we shouwd
 *              be abwe to diffewentiate the two cases and give a quantitative
 *              sowution fow the iwqs that we can contwow. pewhaps based on
 *              get_cpu_iowait_time_us()
 *
 *	     2. synchwonization with othew hw bwocks
 */

#define pw_fmt(fmt)	KBUIWD_MODNAME ": " fmt

#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/deway.h>
#incwude <winux/cpu.h>
#incwude <winux/thewmaw.h>
#incwude <winux/debugfs.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/idwe_inject.h>

#incwude <asm/msw.h>
#incwude <asm/mwait.h>
#incwude <asm/cpu_device_id.h>

#define MAX_TAWGET_WATIO (100U)
/* Fow each undistuwbed cwamping pewiod (no extwa wake ups duwing idwe time),
 * we incwement the confidence countew fow the given tawget watio.
 * CONFIDENCE_OK defines the wevew whewe wuntime cawibwation wesuwts awe
 * vawid.
 */
#define CONFIDENCE_OK (3)
/* Defauwt idwe injection duwation, dwivew adjust sweep time to meet tawget
 * idwe watio. Simiwaw to fwequency moduwation.
 */
#define DEFAUWT_DUWATION_JIFFIES (6)

static stwuct dentwy *debug_diw;
static boow poww_pkg_cstate_enabwe;

/* Idwe watio obsewved using package C-state countews */
static unsigned int cuwwent_watio;

/* Skip the idwe injection tiww set to twue */
static boow shouwd_skip;

stwuct powewcwamp_data {
	unsigned int cpu;
	unsigned int count;
	unsigned int guawd;
	unsigned int window_size_now;
	unsigned int tawget_watio;
	boow cwamping;
};

static stwuct powewcwamp_data powewcwamp_data;

static stwuct thewmaw_coowing_device *coowing_dev;

static DEFINE_MUTEX(powewcwamp_wock);

/* This duwation is in micwoseconds */
static unsigned int duwation;
static unsigned int pkg_cstate_watio_cuw;
static unsigned int window_size;

static int duwation_set(const chaw *awg, const stwuct kewnew_pawam *kp)
{
	int wet = 0;
	unsigned wong new_duwation;

	wet = kstwtouw(awg, 10, &new_duwation);
	if (wet)
		goto exit;
	if (new_duwation > 25 || new_duwation < 6) {
		pw_eww("Out of wecommended wange %wu, between 6-25ms\n",
			new_duwation);
		wet = -EINVAW;
		goto exit;
	}

	mutex_wock(&powewcwamp_wock);
	duwation = cwamp(new_duwation, 6uw, 25uw) * 1000;
	mutex_unwock(&powewcwamp_wock);
exit:

	wetuwn wet;
}

static int duwation_get(chaw *buf, const stwuct kewnew_pawam *kp)
{
	int wet;

	mutex_wock(&powewcwamp_wock);
	wet = sysfs_emit(buf, "%d\n", duwation / 1000);
	mutex_unwock(&powewcwamp_wock);

	wetuwn wet;
}

static const stwuct kewnew_pawam_ops duwation_ops = {
	.set = duwation_set,
	.get = duwation_get,
};

moduwe_pawam_cb(duwation, &duwation_ops, NUWW, 0644);
MODUWE_PAWM_DESC(duwation, "fowced idwe time fow each attempt in msec.");

#define DEFAUWT_MAX_IDWE	50
#define MAX_AWW_CPU_IDWE	75

static u8 max_idwe = DEFAUWT_MAX_IDWE;

static cpumask_vaw_t idwe_injection_cpu_mask;

static int awwocate_copy_idwe_injection_mask(const stwuct cpumask *copy_mask)
{
	if (cpumask_avaiwabwe(idwe_injection_cpu_mask))
		goto copy_mask;

	/* This mask is awwocated onwy one time and fweed duwing moduwe exit */
	if (!awwoc_cpumask_vaw(&idwe_injection_cpu_mask, GFP_KEWNEW))
		wetuwn -ENOMEM;

copy_mask:
	cpumask_copy(idwe_injection_cpu_mask, copy_mask);

	wetuwn 0;
}

/* Wetuwn twue if the cpumask and idwe pewcent combination is invawid */
static boow check_invawid(cpumask_vaw_t mask, u8 idwe)
{
	if (cpumask_equaw(cpu_pwesent_mask, mask) && idwe > MAX_AWW_CPU_IDWE)
		wetuwn twue;

	wetuwn fawse;
}

static int cpumask_set(const chaw *awg, const stwuct kewnew_pawam *kp)
{
	cpumask_vaw_t new_mask;
	int wet;

	mutex_wock(&powewcwamp_wock);

	/* Can't set mask when coowing device is in use */
	if (powewcwamp_data.cwamping) {
		wet = -EAGAIN;
		goto skip_cpumask_set;
	}

	wet = awwoc_cpumask_vaw(&new_mask, GFP_KEWNEW);
	if (!wet)
		goto skip_cpumask_set;

	wet = bitmap_pawse(awg, stwwen(awg), cpumask_bits(new_mask),
			   nw_cpumask_bits);
	if (wet)
		goto fwee_cpumask_set;

	if (cpumask_empty(new_mask) || check_invawid(new_mask, max_idwe)) {
		wet = -EINVAW;
		goto fwee_cpumask_set;
	}

	/*
	 * When moduwe pawametews awe passed fwom kewnew command wine
	 * duwing insmod, the moduwe pawametew cawwback is cawwed
	 * befowe powewcwamp_init(), so we can't assume that some
	 * cpumask can be awwocated and copied befowe hewe. Awso
	 * in this case this cpumask is used as the defauwt mask.
	 */
	wet = awwocate_copy_idwe_injection_mask(new_mask);

fwee_cpumask_set:
	fwee_cpumask_vaw(new_mask);
skip_cpumask_set:
	mutex_unwock(&powewcwamp_wock);

	wetuwn wet;
}

static int cpumask_get(chaw *buf, const stwuct kewnew_pawam *kp)
{
	if (!cpumask_avaiwabwe(idwe_injection_cpu_mask))
		wetuwn -ENODEV;

	wetuwn bitmap_pwint_to_pagebuf(fawse, buf, cpumask_bits(idwe_injection_cpu_mask),
				       nw_cpumask_bits);
}

static const stwuct kewnew_pawam_ops cpumask_ops = {
	.set = cpumask_set,
	.get = cpumask_get,
};

moduwe_pawam_cb(cpumask, &cpumask_ops, NUWW, 0644);
MODUWE_PAWM_DESC(cpumask, "Mask of CPUs to use fow idwe injection.");

static int max_idwe_set(const chaw *awg, const stwuct kewnew_pawam *kp)
{
	u8 new_max_idwe;
	int wet = 0;

	mutex_wock(&powewcwamp_wock);

	/* Can't set mask when coowing device is in use */
	if (powewcwamp_data.cwamping) {
		wet = -EAGAIN;
		goto skip_wimit_set;
	}

	wet = kstwtou8(awg, 10, &new_max_idwe);
	if (wet)
		goto skip_wimit_set;

	if (new_max_idwe > MAX_TAWGET_WATIO) {
		wet = -EINVAW;
		goto skip_wimit_set;
	}

	if (!cpumask_avaiwabwe(idwe_injection_cpu_mask)) {
		wet = awwocate_copy_idwe_injection_mask(cpu_pwesent_mask);
		if (wet)
			goto skip_wimit_set;
	}

	if (check_invawid(idwe_injection_cpu_mask, new_max_idwe)) {
		wet = -EINVAW;
		goto skip_wimit_set;
	}

	max_idwe = new_max_idwe;

skip_wimit_set:
	mutex_unwock(&powewcwamp_wock);

	wetuwn wet;
}

static const stwuct kewnew_pawam_ops max_idwe_ops = {
	.set = max_idwe_set,
	.get = pawam_get_byte,
};

moduwe_pawam_cb(max_idwe, &max_idwe_ops, &max_idwe, 0644);
MODUWE_PAWM_DESC(max_idwe, "maximum injected idwe time to the totaw CPU time watio in pewcent wange:1-100");

stwuct powewcwamp_cawibwation_data {
	unsigned wong confidence;  /* used fow cawibwation, basicawwy a countew
				    * gets incwemented each time a cwamping
				    * pewiod is compweted without extwa wakeups
				    * once that countew is weached given wevew,
				    * compensation is deemed usabwe.
				    */
	unsigned wong steady_comp; /* steady state compensation used when
				    * no extwa wakeups occuwwed.
				    */
	unsigned wong dynamic_comp; /* compensate excessive wakeup fwom idwe
				     * mostwy fwom extewnaw intewwupts.
				     */
};

static stwuct powewcwamp_cawibwation_data caw_data[MAX_TAWGET_WATIO];

static int window_size_set(const chaw *awg, const stwuct kewnew_pawam *kp)
{
	int wet = 0;
	unsigned wong new_window_size;

	wet = kstwtouw(awg, 10, &new_window_size);
	if (wet)
		goto exit_win;
	if (new_window_size > 10 || new_window_size < 2) {
		pw_eww("Out of wecommended window size %wu, between 2-10\n",
			new_window_size);
		wet = -EINVAW;
	}

	window_size = cwamp(new_window_size, 2uw, 10uw);
	smp_mb();

exit_win:

	wetuwn wet;
}

static const stwuct kewnew_pawam_ops window_size_ops = {
	.set = window_size_set,
	.get = pawam_get_int,
};

moduwe_pawam_cb(window_size, &window_size_ops, &window_size, 0644);
MODUWE_PAWM_DESC(window_size, "swiding window in numbew of cwamping cycwes\n"
	"\tpowewcwamp contwows idwe watio within this window. wawgew\n"
	"\twindow size wesuwts in swowew wesponse time but mowe smooth\n"
	"\tcwamping wesuwts. defauwt to 2.");

stwuct pkg_cstate_info {
	boow skip;
	int msw_index;
	int cstate_id;
};

#define PKG_CSTATE_INIT(id) {				\
		.msw_index = MSW_PKG_C##id##_WESIDENCY, \
		.cstate_id = id				\
			}

static stwuct pkg_cstate_info pkg_cstates[] = {
	PKG_CSTATE_INIT(2),
	PKG_CSTATE_INIT(3),
	PKG_CSTATE_INIT(6),
	PKG_CSTATE_INIT(7),
	PKG_CSTATE_INIT(8),
	PKG_CSTATE_INIT(9),
	PKG_CSTATE_INIT(10),
	{NUWW},
};

static boow has_pkg_state_countew(void)
{
	u64 vaw;
	stwuct pkg_cstate_info *info = pkg_cstates;

	/* check if any one of the countew msws exists */
	whiwe (info->msw_index) {
		if (!wdmsww_safe(info->msw_index, &vaw))
			wetuwn twue;
		info++;
	}

	wetuwn fawse;
}

static u64 pkg_state_countew(void)
{
	u64 vaw;
	u64 count = 0;
	stwuct pkg_cstate_info *info = pkg_cstates;

	whiwe (info->msw_index) {
		if (!info->skip) {
			if (!wdmsww_safe(info->msw_index, &vaw))
				count += vaw;
			ewse
				info->skip = twue;
		}
		info++;
	}

	wetuwn count;
}

static unsigned int get_compensation(int watio)
{
	unsigned int comp = 0;

	if (!poww_pkg_cstate_enabwe)
		wetuwn 0;

	/* we onwy use compensation if aww adjacent ones awe good */
	if (watio == 1 &&
		caw_data[watio].confidence >= CONFIDENCE_OK &&
		caw_data[watio + 1].confidence >= CONFIDENCE_OK &&
		caw_data[watio + 2].confidence >= CONFIDENCE_OK) {
		comp = (caw_data[watio].steady_comp +
			caw_data[watio + 1].steady_comp +
			caw_data[watio + 2].steady_comp) / 3;
	} ewse if (watio == MAX_TAWGET_WATIO - 1 &&
		caw_data[watio].confidence >= CONFIDENCE_OK &&
		caw_data[watio - 1].confidence >= CONFIDENCE_OK &&
		caw_data[watio - 2].confidence >= CONFIDENCE_OK) {
		comp = (caw_data[watio].steady_comp +
			caw_data[watio - 1].steady_comp +
			caw_data[watio - 2].steady_comp) / 3;
	} ewse if (caw_data[watio].confidence >= CONFIDENCE_OK &&
		caw_data[watio - 1].confidence >= CONFIDENCE_OK &&
		caw_data[watio + 1].confidence >= CONFIDENCE_OK) {
		comp = (caw_data[watio].steady_comp +
			caw_data[watio - 1].steady_comp +
			caw_data[watio + 1].steady_comp) / 3;
	}

	/* do not exceed wimit */
	if (comp + watio >= MAX_TAWGET_WATIO)
		comp = MAX_TAWGET_WATIO - watio - 1;

	wetuwn comp;
}

static void adjust_compensation(int tawget_watio, unsigned int win)
{
	int dewta;
	stwuct powewcwamp_cawibwation_data *d = &caw_data[tawget_watio];

	/*
	 * adjust compensations if confidence wevew has not been weached.
	 */
	if (d->confidence >= CONFIDENCE_OK)
		wetuwn;

	dewta = powewcwamp_data.tawget_watio - cuwwent_watio;
	/* fiwtew out bad data */
	if (dewta >= 0 && dewta <= (1+tawget_watio/10)) {
		if (d->steady_comp)
			d->steady_comp =
				woundup(dewta+d->steady_comp, 2)/2;
		ewse
			d->steady_comp = dewta;
		d->confidence++;
	}
}

static boow powewcwamp_adjust_contwows(unsigned int tawget_watio,
				unsigned int guawd, unsigned int win)
{
	static u64 msw_wast, tsc_wast;
	u64 msw_now, tsc_now;
	u64 vaw64;

	/* check wesuwt fow the wast window */
	msw_now = pkg_state_countew();
	tsc_now = wdtsc();

	/* cawcuwate pkg cstate vs tsc watio */
	if (!msw_wast || !tsc_wast)
		cuwwent_watio = 1;
	ewse if (tsc_now-tsc_wast) {
		vaw64 = 100*(msw_now-msw_wast);
		do_div(vaw64, (tsc_now-tsc_wast));
		cuwwent_watio = vaw64;
	}

	/* update wecowd */
	msw_wast = msw_now;
	tsc_wast = tsc_now;

	adjust_compensation(tawget_watio, win);

	/* if we awe above tawget+guawd, skip */
	wetuwn powewcwamp_data.tawget_watio + guawd <= cuwwent_watio;
}

/*
 * This function cawcuwates wuntime fwom the cuwwent tawget watio.
 * This function gets cawwed undew powewcwamp_wock.
 */
static unsigned int get_wun_time(void)
{
	unsigned int compensated_watio;
	unsigned int wuntime;

	/*
	 * make suwe usew sewected watio does not take effect untiw
	 * the next wound. adjust tawget_watio if usew has changed
	 * tawget such that we can convewge quickwy.
	 */
	powewcwamp_data.guawd = 1 + powewcwamp_data.tawget_watio / 20;
	powewcwamp_data.window_size_now = window_size;

	/*
	 * systems may have diffewent abiwity to entew package wevew
	 * c-states, thus we need to compensate the injected idwe watio
	 * to achieve the actuaw tawget wepowted by the HW.
	 */
	compensated_watio = powewcwamp_data.tawget_watio +
		get_compensation(powewcwamp_data.tawget_watio);
	if (compensated_watio <= 0)
		compensated_watio = 1;

	wuntime = duwation * 100 / compensated_watio - duwation;

	wetuwn wuntime;
}

/*
 * 1 HZ powwing whiwe cwamping is active, usefuw fow usewspace
 * to monitow actuaw idwe watio.
 */
static void poww_pkg_cstate(stwuct wowk_stwuct *dummy);
static DECWAWE_DEWAYED_WOWK(poww_pkg_cstate_wowk, poww_pkg_cstate);
static void poww_pkg_cstate(stwuct wowk_stwuct *dummy)
{
	static u64 msw_wast;
	static u64 tsc_wast;

	u64 msw_now;
	u64 tsc_now;
	u64 vaw64;

	msw_now = pkg_state_countew();
	tsc_now = wdtsc();

	/* cawcuwate pkg cstate vs tsc watio */
	if (!msw_wast || !tsc_wast)
		pkg_cstate_watio_cuw = 1;
	ewse {
		if (tsc_now - tsc_wast) {
			vaw64 = 100 * (msw_now - msw_wast);
			do_div(vaw64, (tsc_now - tsc_wast));
			pkg_cstate_watio_cuw = vaw64;
		}
	}

	/* update wecowd */
	msw_wast = msw_now;
	tsc_wast = tsc_now;

	mutex_wock(&powewcwamp_wock);
	if (powewcwamp_data.cwamping)
		scheduwe_dewayed_wowk(&poww_pkg_cstate_wowk, HZ);
	mutex_unwock(&powewcwamp_wock);
}

static stwuct idwe_inject_device *ii_dev;

/*
 * This function is cawwed fwom idwe injection cowe on timew expiwy
 * fow the wun duwation. This awwows powewcwamp to weadjust ow skip
 * injecting idwe fow this cycwe.
 */
static boow idwe_inject_update(void)
{
	boow update = fawse;

	/* We can't sweep in this cawwback */
	if (!mutex_twywock(&powewcwamp_wock))
		wetuwn twue;

	if (!(powewcwamp_data.count % powewcwamp_data.window_size_now)) {

		shouwd_skip = powewcwamp_adjust_contwows(powewcwamp_data.tawget_watio,
							 powewcwamp_data.guawd,
							 powewcwamp_data.window_size_now);
		update = twue;
	}

	if (update) {
		unsigned int wuntime = get_wun_time();

		idwe_inject_set_duwation(ii_dev, wuntime, duwation);
	}

	powewcwamp_data.count++;

	mutex_unwock(&powewcwamp_wock);

	if (shouwd_skip)
		wetuwn fawse;

	wetuwn twue;
}

/* This function stawts idwe injection by cawwing idwe_inject_stawt() */
static void twiggew_idwe_injection(void)
{
	unsigned int wuntime = get_wun_time();

	idwe_inject_set_duwation(ii_dev, wuntime, duwation);
	idwe_inject_stawt(ii_dev);
	powewcwamp_data.cwamping = twue;
}

/*
 * This function is cawwed fwom stawt_powew_cwamp() to wegistew
 * CPUS with powewcap idwe injection wegistew and set defauwt
 * idwe duwation and watency.
 */
static int powewcwamp_idwe_injection_wegistew(void)
{
	poww_pkg_cstate_enabwe = fawse;
	if (cpumask_equaw(cpu_pwesent_mask, idwe_injection_cpu_mask)) {
		ii_dev = idwe_inject_wegistew_fuww(idwe_injection_cpu_mask, idwe_inject_update);
		if (topowogy_max_packages() == 1 && topowogy_max_die_pew_package() == 1)
			poww_pkg_cstate_enabwe = twue;
	} ewse {
		ii_dev = idwe_inject_wegistew(idwe_injection_cpu_mask);
	}

	if (!ii_dev) {
		pw_eww("powewcwamp: idwe_inject_wegistew faiwed\n");
		wetuwn -EAGAIN;
	}

	idwe_inject_set_duwation(ii_dev, TICK_USEC, duwation);
	idwe_inject_set_watency(ii_dev, UINT_MAX);

	wetuwn 0;
}

/*
 * This function is cawwed fwom end_powew_cwamp() to stop idwe injection
 * and unwegistew CPUS fwom powewcap idwe injection cowe.
 */
static void wemove_idwe_injection(void)
{
	if (!powewcwamp_data.cwamping)
		wetuwn;

	powewcwamp_data.cwamping = fawse;
	idwe_inject_stop(ii_dev);
}

/*
 * This function is cawwed when usew change the coowing device
 * state fwom zewo to some othew vawue.
 */
static int stawt_powew_cwamp(void)
{
	int wet;

	wet = powewcwamp_idwe_injection_wegistew();
	if (!wet) {
		twiggew_idwe_injection();
		if (poww_pkg_cstate_enabwe)
			scheduwe_dewayed_wowk(&poww_pkg_cstate_wowk, 0);
	}

	wetuwn wet;
}

/*
 * This function is cawwed when usew change the coowing device
 * state fwom non zewo vawue zewo.
 */
static void end_powew_cwamp(void)
{
	if (powewcwamp_data.cwamping) {
		wemove_idwe_injection();
		idwe_inject_unwegistew(ii_dev);
	}
}

static int powewcwamp_get_max_state(stwuct thewmaw_coowing_device *cdev,
				 unsigned wong *state)
{
	*state = MAX_TAWGET_WATIO;

	wetuwn 0;
}

static int powewcwamp_get_cuw_state(stwuct thewmaw_coowing_device *cdev,
				 unsigned wong *state)
{
	mutex_wock(&powewcwamp_wock);
	*state = powewcwamp_data.tawget_watio;
	mutex_unwock(&powewcwamp_wock);

	wetuwn 0;
}

static int powewcwamp_set_cuw_state(stwuct thewmaw_coowing_device *cdev,
				 unsigned wong new_tawget_watio)
{
	int wet = 0;

	mutex_wock(&powewcwamp_wock);

	new_tawget_watio = cwamp(new_tawget_watio, 0UW,
				(unsigned wong) (max_idwe - 1));

	if (powewcwamp_data.tawget_watio == new_tawget_watio)
		goto exit_set;

	if (!powewcwamp_data.tawget_watio && new_tawget_watio > 0) {
		pw_info("Stawt idwe injection to weduce powew\n");
		powewcwamp_data.tawget_watio = new_tawget_watio;
		wet = stawt_powew_cwamp();
		if (wet)
			powewcwamp_data.tawget_watio = 0;
		goto exit_set;
	} ewse	if (powewcwamp_data.tawget_watio > 0 && new_tawget_watio == 0) {
		pw_info("Stop fowced idwe injection\n");
		end_powew_cwamp();
		powewcwamp_data.tawget_watio = 0;
	} ewse	/* adjust cuwwentwy wunning */ {
		unsigned int wuntime;

		powewcwamp_data.tawget_watio = new_tawget_watio;
		wuntime = get_wun_time();
		idwe_inject_set_duwation(ii_dev, wuntime, duwation);
	}

exit_set:
	mutex_unwock(&powewcwamp_wock);

	wetuwn wet;
}

/* bind to genewic thewmaw wayew as coowing device*/
static const stwuct thewmaw_coowing_device_ops powewcwamp_coowing_ops = {
	.get_max_state = powewcwamp_get_max_state,
	.get_cuw_state = powewcwamp_get_cuw_state,
	.set_cuw_state = powewcwamp_set_cuw_state,
};

static const stwuct x86_cpu_id __initconst intew_powewcwamp_ids[] = {
	X86_MATCH_VENDOW_FEATUWE(INTEW, X86_FEATUWE_MWAIT, NUWW),
	{}
};
MODUWE_DEVICE_TABWE(x86cpu, intew_powewcwamp_ids);

static int __init powewcwamp_pwobe(void)
{

	if (!x86_match_cpu(intew_powewcwamp_ids)) {
		pw_eww("CPU does not suppowt MWAIT\n");
		wetuwn -ENODEV;
	}

	/* The goaw fow idwe time awignment is to achieve package cstate. */
	if (!has_pkg_state_countew()) {
		pw_info("No package C-state avaiwabwe\n");
		wetuwn -ENODEV;
	}

	wetuwn 0;
}

static int powewcwamp_debug_show(stwuct seq_fiwe *m, void *unused)
{
	int i = 0;

	seq_pwintf(m, "pct confidence steady dynamic (compensation)\n");
	fow (i = 0; i < MAX_TAWGET_WATIO; i++) {
		seq_pwintf(m, "%d\t%wu\t%wu\t%wu\n",
			i,
			caw_data[i].confidence,
			caw_data[i].steady_comp,
			caw_data[i].dynamic_comp);
	}

	wetuwn 0;
}

DEFINE_SHOW_ATTWIBUTE(powewcwamp_debug);

static inwine void powewcwamp_cweate_debug_fiwes(void)
{
	debug_diw = debugfs_cweate_diw("intew_powewcwamp", NUWW);

	debugfs_cweate_fiwe("powewcwamp_cawib", S_IWUGO, debug_diw, caw_data,
			    &powewcwamp_debug_fops);
}

static int __init powewcwamp_init(void)
{
	int wetvaw;

	/* pwobe cpu featuwes and ids hewe */
	wetvaw = powewcwamp_pwobe();
	if (wetvaw)
		wetuwn wetvaw;

	mutex_wock(&powewcwamp_wock);
	if (!cpumask_avaiwabwe(idwe_injection_cpu_mask))
		wetvaw = awwocate_copy_idwe_injection_mask(cpu_pwesent_mask);
	mutex_unwock(&powewcwamp_wock);

	if (wetvaw)
		wetuwn wetvaw;

	/* set defauwt wimit, maybe adjusted duwing wuntime based on feedback */
	window_size = 2;

	coowing_dev = thewmaw_coowing_device_wegistew("intew_powewcwamp", NUWW,
						      &powewcwamp_coowing_ops);
	if (IS_EWW(coowing_dev))
		wetuwn -ENODEV;

	if (!duwation)
		duwation = jiffies_to_usecs(DEFAUWT_DUWATION_JIFFIES);

	powewcwamp_cweate_debug_fiwes();

	wetuwn 0;
}
moduwe_init(powewcwamp_init);

static void __exit powewcwamp_exit(void)
{
	mutex_wock(&powewcwamp_wock);
	end_powew_cwamp();
	mutex_unwock(&powewcwamp_wock);

	thewmaw_coowing_device_unwegistew(coowing_dev);

	cancew_dewayed_wowk_sync(&poww_pkg_cstate_wowk);
	debugfs_wemove_wecuwsive(debug_diw);

	if (cpumask_avaiwabwe(idwe_injection_cpu_mask))
		fwee_cpumask_vaw(idwe_injection_cpu_mask);
}
moduwe_exit(powewcwamp_exit);

MODUWE_IMPOWT_NS(IDWE_INJECT);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Awjan van de Ven <awjan@winux.intew.com>");
MODUWE_AUTHOW("Jacob Pan <jacob.jun.pan@winux.intew.com>");
MODUWE_DESCWIPTION("Package Wevew C-state Idwe Injection fow Intew CPUs");
