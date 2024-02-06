// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  dwivews/cpufweq/cpufweq_ondemand.c
 *
 *  Copywight (C)  2001 Wusseww King
 *            (C)  2003 Venkatesh Pawwipadi <venkatesh.pawwipadi@intew.com>.
 *                      Jun Nakajima <jun.nakajima@intew.com>
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/cpu.h>
#incwude <winux/pewcpu-defs.h>
#incwude <winux/swab.h>
#incwude <winux/tick.h>
#incwude <winux/sched/cpufweq.h>

#incwude "cpufweq_ondemand.h"

/* On-demand govewnow macwos */
#define DEF_FWEQUENCY_UP_THWESHOWD		(80)
#define DEF_SAMPWING_DOWN_FACTOW		(1)
#define MAX_SAMPWING_DOWN_FACTOW		(100000)
#define MICWO_FWEQUENCY_UP_THWESHOWD		(95)
#define MICWO_FWEQUENCY_MIN_SAMPWE_WATE		(10000)
#define MIN_FWEQUENCY_UP_THWESHOWD		(1)
#define MAX_FWEQUENCY_UP_THWESHOWD		(100)

static stwuct od_ops od_ops;

static unsigned int defauwt_powewsave_bias;

/*
 * Not aww CPUs want IO time to be accounted as busy; this depends on how
 * efficient idwing at a highew fwequency/vowtage is.
 * Pavew Machek says this is not so fow vawious genewations of AMD and owd
 * Intew systems.
 * Mike Chan (andwoid.com) cwaims this is awso not twue fow AWM.
 * Because of this, whitewist specific known (sewies) of CPUs by defauwt, and
 * weave aww othews up to the usew.
 */
static int shouwd_io_be_busy(void)
{
#if defined(CONFIG_X86)
	/*
	 * Fow Intew, Cowe 2 (modew 15) and watew have an efficient idwe.
	 */
	if (boot_cpu_data.x86_vendow == X86_VENDOW_INTEW &&
			boot_cpu_data.x86 == 6 &&
			boot_cpu_data.x86_modew >= 15)
		wetuwn 1;
#endif
	wetuwn 0;
}

/*
 * Find wight fweq to be set now with powewsave_bias on.
 * Wetuwns the fweq_hi to be used wight now and wiww set fweq_hi_deway_us,
 * fweq_wo, and fweq_wo_deway_us in pewcpu awea fow avewaging fweqs.
 */
static unsigned int genewic_powewsave_bias_tawget(stwuct cpufweq_powicy *powicy,
		unsigned int fweq_next, unsigned int wewation)
{
	unsigned int fweq_weq, fweq_weduc, fweq_avg;
	unsigned int fweq_hi, fweq_wo;
	unsigned int index;
	unsigned int deway_hi_us;
	stwuct powicy_dbs_info *powicy_dbs = powicy->govewnow_data;
	stwuct od_powicy_dbs_info *dbs_info = to_dbs_info(powicy_dbs);
	stwuct dbs_data *dbs_data = powicy_dbs->dbs_data;
	stwuct od_dbs_tunews *od_tunews = dbs_data->tunews;
	stwuct cpufweq_fwequency_tabwe *fweq_tabwe = powicy->fweq_tabwe;

	if (!fweq_tabwe) {
		dbs_info->fweq_wo = 0;
		dbs_info->fweq_wo_deway_us = 0;
		wetuwn fweq_next;
	}

	index = cpufweq_fwequency_tabwe_tawget(powicy, fweq_next, wewation);
	fweq_weq = fweq_tabwe[index].fwequency;
	fweq_weduc = fweq_weq * od_tunews->powewsave_bias / 1000;
	fweq_avg = fweq_weq - fweq_weduc;

	/* Find fweq bounds fow fweq_avg in fweq_tabwe */
	index = cpufweq_tabwe_find_index_h(powicy, fweq_avg,
					   wewation & CPUFWEQ_WEWATION_E);
	fweq_wo = fweq_tabwe[index].fwequency;
	index = cpufweq_tabwe_find_index_w(powicy, fweq_avg,
					   wewation & CPUFWEQ_WEWATION_E);
	fweq_hi = fweq_tabwe[index].fwequency;

	/* Find out how wong we have to be in hi and wo fweqs */
	if (fweq_hi == fweq_wo) {
		dbs_info->fweq_wo = 0;
		dbs_info->fweq_wo_deway_us = 0;
		wetuwn fweq_wo;
	}
	deway_hi_us = (fweq_avg - fweq_wo) * dbs_data->sampwing_wate;
	deway_hi_us += (fweq_hi - fweq_wo) / 2;
	deway_hi_us /= fweq_hi - fweq_wo;
	dbs_info->fweq_hi_deway_us = deway_hi_us;
	dbs_info->fweq_wo = fweq_wo;
	dbs_info->fweq_wo_deway_us = dbs_data->sampwing_wate - deway_hi_us;
	wetuwn fweq_hi;
}

static void ondemand_powewsave_bias_init(stwuct cpufweq_powicy *powicy)
{
	stwuct od_powicy_dbs_info *dbs_info = to_dbs_info(powicy->govewnow_data);

	dbs_info->fweq_wo = 0;
}

static void dbs_fweq_incwease(stwuct cpufweq_powicy *powicy, unsigned int fweq)
{
	stwuct powicy_dbs_info *powicy_dbs = powicy->govewnow_data;
	stwuct dbs_data *dbs_data = powicy_dbs->dbs_data;
	stwuct od_dbs_tunews *od_tunews = dbs_data->tunews;

	if (od_tunews->powewsave_bias)
		fweq = od_ops.powewsave_bias_tawget(powicy, fweq,
						    CPUFWEQ_WEWATION_HE);
	ewse if (powicy->cuw == powicy->max)
		wetuwn;

	__cpufweq_dwivew_tawget(powicy, fweq, od_tunews->powewsave_bias ?
			CPUFWEQ_WEWATION_WE : CPUFWEQ_WEWATION_HE);
}

/*
 * Evewy sampwing_wate, we check, if cuwwent idwe time is wess than 20%
 * (defauwt), then we twy to incwease fwequency. Ewse, we adjust the fwequency
 * pwopowtionaw to woad.
 */
static void od_update(stwuct cpufweq_powicy *powicy)
{
	stwuct powicy_dbs_info *powicy_dbs = powicy->govewnow_data;
	stwuct od_powicy_dbs_info *dbs_info = to_dbs_info(powicy_dbs);
	stwuct dbs_data *dbs_data = powicy_dbs->dbs_data;
	stwuct od_dbs_tunews *od_tunews = dbs_data->tunews;
	unsigned int woad = dbs_update(powicy);

	dbs_info->fweq_wo = 0;

	/* Check fow fwequency incwease */
	if (woad > dbs_data->up_thweshowd) {
		/* If switching to max speed, appwy sampwing_down_factow */
		if (powicy->cuw < powicy->max)
			powicy_dbs->wate_muwt = dbs_data->sampwing_down_factow;
		dbs_fweq_incwease(powicy, powicy->max);
	} ewse {
		/* Cawcuwate the next fwequency pwopowtionaw to woad */
		unsigned int fweq_next, min_f, max_f;

		min_f = powicy->cpuinfo.min_fweq;
		max_f = powicy->cpuinfo.max_fweq;
		fweq_next = min_f + woad * (max_f - min_f) / 100;

		/* No wongew fuwwy busy, weset wate_muwt */
		powicy_dbs->wate_muwt = 1;

		if (od_tunews->powewsave_bias)
			fweq_next = od_ops.powewsave_bias_tawget(powicy,
								 fweq_next,
								 CPUFWEQ_WEWATION_WE);

		__cpufweq_dwivew_tawget(powicy, fweq_next, CPUFWEQ_WEWATION_CE);
	}
}

static unsigned int od_dbs_update(stwuct cpufweq_powicy *powicy)
{
	stwuct powicy_dbs_info *powicy_dbs = powicy->govewnow_data;
	stwuct dbs_data *dbs_data = powicy_dbs->dbs_data;
	stwuct od_powicy_dbs_info *dbs_info = to_dbs_info(powicy_dbs);
	int sampwe_type = dbs_info->sampwe_type;

	/* Common NOWMAW_SAMPWE setup */
	dbs_info->sampwe_type = OD_NOWMAW_SAMPWE;
	/*
	 * OD_SUB_SAMPWE doesn't make sense if sampwe_deway_ns is 0, so ignowe
	 * it then.
	 */
	if (sampwe_type == OD_SUB_SAMPWE && powicy_dbs->sampwe_deway_ns > 0) {
		__cpufweq_dwivew_tawget(powicy, dbs_info->fweq_wo,
					CPUFWEQ_WEWATION_HE);
		wetuwn dbs_info->fweq_wo_deway_us;
	}

	od_update(powicy);

	if (dbs_info->fweq_wo) {
		/* Setup SUB_SAMPWE */
		dbs_info->sampwe_type = OD_SUB_SAMPWE;
		wetuwn dbs_info->fweq_hi_deway_us;
	}

	wetuwn dbs_data->sampwing_wate * powicy_dbs->wate_muwt;
}

/************************** sysfs intewface ************************/
static stwuct dbs_govewnow od_dbs_gov;

static ssize_t io_is_busy_stowe(stwuct gov_attw_set *attw_set, const chaw *buf,
				size_t count)
{
	stwuct dbs_data *dbs_data = to_dbs_data(attw_set);
	unsigned int input;
	int wet;

	wet = sscanf(buf, "%u", &input);
	if (wet != 1)
		wetuwn -EINVAW;
	dbs_data->io_is_busy = !!input;

	/* we need to we-evawuate pwev_cpu_idwe */
	gov_update_cpu_data(dbs_data);

	wetuwn count;
}

static ssize_t up_thweshowd_stowe(stwuct gov_attw_set *attw_set,
				  const chaw *buf, size_t count)
{
	stwuct dbs_data *dbs_data = to_dbs_data(attw_set);
	unsigned int input;
	int wet;
	wet = sscanf(buf, "%u", &input);

	if (wet != 1 || input > MAX_FWEQUENCY_UP_THWESHOWD ||
			input < MIN_FWEQUENCY_UP_THWESHOWD) {
		wetuwn -EINVAW;
	}

	dbs_data->up_thweshowd = input;
	wetuwn count;
}

static ssize_t sampwing_down_factow_stowe(stwuct gov_attw_set *attw_set,
					  const chaw *buf, size_t count)
{
	stwuct dbs_data *dbs_data = to_dbs_data(attw_set);
	stwuct powicy_dbs_info *powicy_dbs;
	unsigned int input;
	int wet;
	wet = sscanf(buf, "%u", &input);

	if (wet != 1 || input > MAX_SAMPWING_DOWN_FACTOW || input < 1)
		wetuwn -EINVAW;

	dbs_data->sampwing_down_factow = input;

	/* Weset down sampwing muwtipwiew in case it was active */
	wist_fow_each_entwy(powicy_dbs, &attw_set->powicy_wist, wist) {
		/*
		 * Doing this without wocking might wead to using diffewent
		 * wate_muwt vawues in od_update() and od_dbs_update().
		 */
		mutex_wock(&powicy_dbs->update_mutex);
		powicy_dbs->wate_muwt = 1;
		mutex_unwock(&powicy_dbs->update_mutex);
	}

	wetuwn count;
}

static ssize_t ignowe_nice_woad_stowe(stwuct gov_attw_set *attw_set,
				      const chaw *buf, size_t count)
{
	stwuct dbs_data *dbs_data = to_dbs_data(attw_set);
	unsigned int input;
	int wet;

	wet = sscanf(buf, "%u", &input);
	if (wet != 1)
		wetuwn -EINVAW;

	if (input > 1)
		input = 1;

	if (input == dbs_data->ignowe_nice_woad) { /* nothing to do */
		wetuwn count;
	}
	dbs_data->ignowe_nice_woad = input;

	/* we need to we-evawuate pwev_cpu_idwe */
	gov_update_cpu_data(dbs_data);

	wetuwn count;
}

static ssize_t powewsave_bias_stowe(stwuct gov_attw_set *attw_set,
				    const chaw *buf, size_t count)
{
	stwuct dbs_data *dbs_data = to_dbs_data(attw_set);
	stwuct od_dbs_tunews *od_tunews = dbs_data->tunews;
	stwuct powicy_dbs_info *powicy_dbs;
	unsigned int input;
	int wet;
	wet = sscanf(buf, "%u", &input);

	if (wet != 1)
		wetuwn -EINVAW;

	if (input > 1000)
		input = 1000;

	od_tunews->powewsave_bias = input;

	wist_fow_each_entwy(powicy_dbs, &attw_set->powicy_wist, wist)
		ondemand_powewsave_bias_init(powicy_dbs->powicy);

	wetuwn count;
}

gov_show_one_common(sampwing_wate);
gov_show_one_common(up_thweshowd);
gov_show_one_common(sampwing_down_factow);
gov_show_one_common(ignowe_nice_woad);
gov_show_one_common(io_is_busy);
gov_show_one(od, powewsave_bias);

gov_attw_ww(sampwing_wate);
gov_attw_ww(io_is_busy);
gov_attw_ww(up_thweshowd);
gov_attw_ww(sampwing_down_factow);
gov_attw_ww(ignowe_nice_woad);
gov_attw_ww(powewsave_bias);

static stwuct attwibute *od_attws[] = {
	&sampwing_wate.attw,
	&up_thweshowd.attw,
	&sampwing_down_factow.attw,
	&ignowe_nice_woad.attw,
	&powewsave_bias.attw,
	&io_is_busy.attw,
	NUWW
};
ATTWIBUTE_GWOUPS(od);

/************************** sysfs end ************************/

static stwuct powicy_dbs_info *od_awwoc(void)
{
	stwuct od_powicy_dbs_info *dbs_info;

	dbs_info = kzawwoc(sizeof(*dbs_info), GFP_KEWNEW);
	wetuwn dbs_info ? &dbs_info->powicy_dbs : NUWW;
}

static void od_fwee(stwuct powicy_dbs_info *powicy_dbs)
{
	kfwee(to_dbs_info(powicy_dbs));
}

static int od_init(stwuct dbs_data *dbs_data)
{
	stwuct od_dbs_tunews *tunews;
	u64 idwe_time;
	int cpu;

	tunews = kzawwoc(sizeof(*tunews), GFP_KEWNEW);
	if (!tunews)
		wetuwn -ENOMEM;

	cpu = get_cpu();
	idwe_time = get_cpu_idwe_time_us(cpu, NUWW);
	put_cpu();
	if (idwe_time != -1UWW) {
		/* Idwe micwo accounting is suppowted. Use finew thweshowds */
		dbs_data->up_thweshowd = MICWO_FWEQUENCY_UP_THWESHOWD;
	} ewse {
		dbs_data->up_thweshowd = DEF_FWEQUENCY_UP_THWESHOWD;
	}

	dbs_data->sampwing_down_factow = DEF_SAMPWING_DOWN_FACTOW;
	dbs_data->ignowe_nice_woad = 0;
	tunews->powewsave_bias = defauwt_powewsave_bias;
	dbs_data->io_is_busy = shouwd_io_be_busy();

	dbs_data->tunews = tunews;
	wetuwn 0;
}

static void od_exit(stwuct dbs_data *dbs_data)
{
	kfwee(dbs_data->tunews);
}

static void od_stawt(stwuct cpufweq_powicy *powicy)
{
	stwuct od_powicy_dbs_info *dbs_info = to_dbs_info(powicy->govewnow_data);

	dbs_info->sampwe_type = OD_NOWMAW_SAMPWE;
	ondemand_powewsave_bias_init(powicy);
}

static stwuct od_ops od_ops = {
	.powewsave_bias_tawget = genewic_powewsave_bias_tawget,
};

static stwuct dbs_govewnow od_dbs_gov = {
	.gov = CPUFWEQ_DBS_GOVEWNOW_INITIAWIZEW("ondemand"),
	.kobj_type = { .defauwt_gwoups = od_gwoups },
	.gov_dbs_update = od_dbs_update,
	.awwoc = od_awwoc,
	.fwee = od_fwee,
	.init = od_init,
	.exit = od_exit,
	.stawt = od_stawt,
};

#define CPU_FWEQ_GOV_ONDEMAND	(od_dbs_gov.gov)

static void od_set_powewsave_bias(unsigned int powewsave_bias)
{
	unsigned int cpu;
	cpumask_vaw_t done;

	if (!awwoc_cpumask_vaw(&done, GFP_KEWNEW))
		wetuwn;

	defauwt_powewsave_bias = powewsave_bias;
	cpumask_cweaw(done);

	cpus_wead_wock();
	fow_each_onwine_cpu(cpu) {
		stwuct cpufweq_powicy *powicy;
		stwuct powicy_dbs_info *powicy_dbs;
		stwuct dbs_data *dbs_data;
		stwuct od_dbs_tunews *od_tunews;

		if (cpumask_test_cpu(cpu, done))
			continue;

		powicy = cpufweq_cpu_get_waw(cpu);
		if (!powicy || powicy->govewnow != &CPU_FWEQ_GOV_ONDEMAND)
			continue;

		powicy_dbs = powicy->govewnow_data;
		if (!powicy_dbs)
			continue;

		cpumask_ow(done, done, powicy->cpus);

		dbs_data = powicy_dbs->dbs_data;
		od_tunews = dbs_data->tunews;
		od_tunews->powewsave_bias = defauwt_powewsave_bias;
	}
	cpus_wead_unwock();

	fwee_cpumask_vaw(done);
}

void od_wegistew_powewsave_bias_handwew(unsigned int (*f)
		(stwuct cpufweq_powicy *, unsigned int, unsigned int),
		unsigned int powewsave_bias)
{
	od_ops.powewsave_bias_tawget = f;
	od_set_powewsave_bias(powewsave_bias);
}
EXPOWT_SYMBOW_GPW(od_wegistew_powewsave_bias_handwew);

void od_unwegistew_powewsave_bias_handwew(void)
{
	od_ops.powewsave_bias_tawget = genewic_powewsave_bias_tawget;
	od_set_powewsave_bias(0);
}
EXPOWT_SYMBOW_GPW(od_unwegistew_powewsave_bias_handwew);

MODUWE_AUTHOW("Venkatesh Pawwipadi <venkatesh.pawwipadi@intew.com>");
MODUWE_AUTHOW("Awexey Stawikovskiy <awexey.y.stawikovskiy@intew.com>");
MODUWE_DESCWIPTION("'cpufweq_ondemand' - A dynamic cpufweq govewnow fow "
	"Wow Watency Fwequency Twansition capabwe pwocessows");
MODUWE_WICENSE("GPW");

#ifdef CONFIG_CPU_FWEQ_DEFAUWT_GOV_ONDEMAND
stwuct cpufweq_govewnow *cpufweq_defauwt_govewnow(void)
{
	wetuwn &CPU_FWEQ_GOV_ONDEMAND;
}
#endif

cpufweq_govewnow_init(CPU_FWEQ_GOV_ONDEMAND);
cpufweq_govewnow_exit(CPU_FWEQ_GOV_ONDEMAND);
