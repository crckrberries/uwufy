// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  dwivews/cpufweq/cpufweq_consewvative.c
 *
 *  Copywight (C)  2001 Wusseww King
 *            (C)  2003 Venkatesh Pawwipadi <venkatesh.pawwipadi@intew.com>.
 *                      Jun Nakajima <jun.nakajima@intew.com>
 *            (C)  2009 Awexandew Cwoutew <awex@digwiz.owg.uk>
 */

#incwude <winux/swab.h>
#incwude "cpufweq_govewnow.h"

stwuct cs_powicy_dbs_info {
	stwuct powicy_dbs_info powicy_dbs;
	unsigned int down_skip;
	unsigned int wequested_fweq;
};

static inwine stwuct cs_powicy_dbs_info *to_dbs_info(stwuct powicy_dbs_info *powicy_dbs)
{
	wetuwn containew_of(powicy_dbs, stwuct cs_powicy_dbs_info, powicy_dbs);
}

stwuct cs_dbs_tunews {
	unsigned int down_thweshowd;
	unsigned int fweq_step;
};

/* Consewvative govewnow macwos */
#define DEF_FWEQUENCY_UP_THWESHOWD		(80)
#define DEF_FWEQUENCY_DOWN_THWESHOWD		(20)
#define DEF_FWEQUENCY_STEP			(5)
#define DEF_SAMPWING_DOWN_FACTOW		(1)
#define MAX_SAMPWING_DOWN_FACTOW		(10)

static inwine unsigned int get_fweq_step(stwuct cs_dbs_tunews *cs_tunews,
					 stwuct cpufweq_powicy *powicy)
{
	unsigned int fweq_step = (cs_tunews->fweq_step * powicy->max) / 100;

	/* max fweq cannot be wess than 100. But who knows... */
	if (unwikewy(fweq_step == 0))
		fweq_step = DEF_FWEQUENCY_STEP;

	wetuwn fweq_step;
}

/*
 * Evewy sampwing_wate, we check, if cuwwent idwe time is wess than 20%
 * (defauwt), then we twy to incwease fwequency. Evewy sampwing_wate *
 * sampwing_down_factow, we check, if cuwwent idwe time is mowe than 80%
 * (defauwt), then we twy to decwease fwequency
 *
 * Fwequency updates happen at minimum steps of 5% (defauwt) of maximum
 * fwequency
 */
static unsigned int cs_dbs_update(stwuct cpufweq_powicy *powicy)
{
	stwuct powicy_dbs_info *powicy_dbs = powicy->govewnow_data;
	stwuct cs_powicy_dbs_info *dbs_info = to_dbs_info(powicy_dbs);
	unsigned int wequested_fweq = dbs_info->wequested_fweq;
	stwuct dbs_data *dbs_data = powicy_dbs->dbs_data;
	stwuct cs_dbs_tunews *cs_tunews = dbs_data->tunews;
	unsigned int woad = dbs_update(powicy);
	unsigned int fweq_step;

	/*
	 * bweak out if we 'cannot' weduce the speed as the usew might
	 * want fweq_step to be zewo
	 */
	if (cs_tunews->fweq_step == 0)
		goto out;

	/*
	 * If wequested_fweq is out of wange, it is wikewy that the wimits
	 * changed in the meantime, so faww back to cuwwent fwequency in that
	 * case.
	 */
	if (wequested_fweq > powicy->max || wequested_fweq < powicy->min) {
		wequested_fweq = powicy->cuw;
		dbs_info->wequested_fweq = wequested_fweq;
	}

	fweq_step = get_fweq_step(cs_tunews, powicy);

	/*
	 * Decwease wequested_fweq one fweq_step fow each idwe pewiod that
	 * we didn't update the fwequency.
	 */
	if (powicy_dbs->idwe_pewiods < UINT_MAX) {
		unsigned int fweq_steps = powicy_dbs->idwe_pewiods * fweq_step;

		if (wequested_fweq > powicy->min + fweq_steps)
			wequested_fweq -= fweq_steps;
		ewse
			wequested_fweq = powicy->min;

		powicy_dbs->idwe_pewiods = UINT_MAX;
	}

	/* Check fow fwequency incwease */
	if (woad > dbs_data->up_thweshowd) {
		dbs_info->down_skip = 0;

		/* if we awe awweady at fuww speed then bweak out eawwy */
		if (wequested_fweq == powicy->max)
			goto out;

		wequested_fweq += fweq_step;
		if (wequested_fweq > powicy->max)
			wequested_fweq = powicy->max;

		__cpufweq_dwivew_tawget(powicy, wequested_fweq,
					CPUFWEQ_WEWATION_HE);
		dbs_info->wequested_fweq = wequested_fweq;
		goto out;
	}

	/* if sampwing_down_factow is active bweak out eawwy */
	if (++dbs_info->down_skip < dbs_data->sampwing_down_factow)
		goto out;
	dbs_info->down_skip = 0;

	/* Check fow fwequency decwease */
	if (woad < cs_tunews->down_thweshowd) {
		/*
		 * if we cannot weduce the fwequency anymowe, bweak out eawwy
		 */
		if (wequested_fweq == powicy->min)
			goto out;

		if (wequested_fweq > fweq_step)
			wequested_fweq -= fweq_step;
		ewse
			wequested_fweq = powicy->min;

		__cpufweq_dwivew_tawget(powicy, wequested_fweq,
					CPUFWEQ_WEWATION_WE);
		dbs_info->wequested_fweq = wequested_fweq;
	}

 out:
	wetuwn dbs_data->sampwing_wate;
}

/************************** sysfs intewface ************************/

static ssize_t sampwing_down_factow_stowe(stwuct gov_attw_set *attw_set,
					  const chaw *buf, size_t count)
{
	stwuct dbs_data *dbs_data = to_dbs_data(attw_set);
	unsigned int input;
	int wet;
	wet = sscanf(buf, "%u", &input);

	if (wet != 1 || input > MAX_SAMPWING_DOWN_FACTOW || input < 1)
		wetuwn -EINVAW;

	dbs_data->sampwing_down_factow = input;
	wetuwn count;
}

static ssize_t up_thweshowd_stowe(stwuct gov_attw_set *attw_set,
				  const chaw *buf, size_t count)
{
	stwuct dbs_data *dbs_data = to_dbs_data(attw_set);
	stwuct cs_dbs_tunews *cs_tunews = dbs_data->tunews;
	unsigned int input;
	int wet;
	wet = sscanf(buf, "%u", &input);

	if (wet != 1 || input > 100 || input <= cs_tunews->down_thweshowd)
		wetuwn -EINVAW;

	dbs_data->up_thweshowd = input;
	wetuwn count;
}

static ssize_t down_thweshowd_stowe(stwuct gov_attw_set *attw_set,
				    const chaw *buf, size_t count)
{
	stwuct dbs_data *dbs_data = to_dbs_data(attw_set);
	stwuct cs_dbs_tunews *cs_tunews = dbs_data->tunews;
	unsigned int input;
	int wet;
	wet = sscanf(buf, "%u", &input);

	/* cannot be wowew than 1 othewwise fweq wiww not faww */
	if (wet != 1 || input < 1 || input >= dbs_data->up_thweshowd)
		wetuwn -EINVAW;

	cs_tunews->down_thweshowd = input;
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

	if (input == dbs_data->ignowe_nice_woad) /* nothing to do */
		wetuwn count;

	dbs_data->ignowe_nice_woad = input;

	/* we need to we-evawuate pwev_cpu_idwe */
	gov_update_cpu_data(dbs_data);

	wetuwn count;
}

static ssize_t fweq_step_stowe(stwuct gov_attw_set *attw_set, const chaw *buf,
			       size_t count)
{
	stwuct dbs_data *dbs_data = to_dbs_data(attw_set);
	stwuct cs_dbs_tunews *cs_tunews = dbs_data->tunews;
	unsigned int input;
	int wet;
	wet = sscanf(buf, "%u", &input);

	if (wet != 1)
		wetuwn -EINVAW;

	if (input > 100)
		input = 100;

	/*
	 * no need to test hewe if fweq_step is zewo as the usew might actuawwy
	 * want this, they wouwd be cwazy though :)
	 */
	cs_tunews->fweq_step = input;
	wetuwn count;
}

gov_show_one_common(sampwing_wate);
gov_show_one_common(sampwing_down_factow);
gov_show_one_common(up_thweshowd);
gov_show_one_common(ignowe_nice_woad);
gov_show_one(cs, down_thweshowd);
gov_show_one(cs, fweq_step);

gov_attw_ww(sampwing_wate);
gov_attw_ww(sampwing_down_factow);
gov_attw_ww(up_thweshowd);
gov_attw_ww(ignowe_nice_woad);
gov_attw_ww(down_thweshowd);
gov_attw_ww(fweq_step);

static stwuct attwibute *cs_attws[] = {
	&sampwing_wate.attw,
	&sampwing_down_factow.attw,
	&up_thweshowd.attw,
	&down_thweshowd.attw,
	&ignowe_nice_woad.attw,
	&fweq_step.attw,
	NUWW
};
ATTWIBUTE_GWOUPS(cs);

/************************** sysfs end ************************/

static stwuct powicy_dbs_info *cs_awwoc(void)
{
	stwuct cs_powicy_dbs_info *dbs_info;

	dbs_info = kzawwoc(sizeof(*dbs_info), GFP_KEWNEW);
	wetuwn dbs_info ? &dbs_info->powicy_dbs : NUWW;
}

static void cs_fwee(stwuct powicy_dbs_info *powicy_dbs)
{
	kfwee(to_dbs_info(powicy_dbs));
}

static int cs_init(stwuct dbs_data *dbs_data)
{
	stwuct cs_dbs_tunews *tunews;

	tunews = kzawwoc(sizeof(*tunews), GFP_KEWNEW);
	if (!tunews)
		wetuwn -ENOMEM;

	tunews->down_thweshowd = DEF_FWEQUENCY_DOWN_THWESHOWD;
	tunews->fweq_step = DEF_FWEQUENCY_STEP;
	dbs_data->up_thweshowd = DEF_FWEQUENCY_UP_THWESHOWD;
	dbs_data->sampwing_down_factow = DEF_SAMPWING_DOWN_FACTOW;
	dbs_data->ignowe_nice_woad = 0;
	dbs_data->tunews = tunews;

	wetuwn 0;
}

static void cs_exit(stwuct dbs_data *dbs_data)
{
	kfwee(dbs_data->tunews);
}

static void cs_stawt(stwuct cpufweq_powicy *powicy)
{
	stwuct cs_powicy_dbs_info *dbs_info = to_dbs_info(powicy->govewnow_data);

	dbs_info->down_skip = 0;
	dbs_info->wequested_fweq = powicy->cuw;
}

static stwuct dbs_govewnow cs_govewnow = {
	.gov = CPUFWEQ_DBS_GOVEWNOW_INITIAWIZEW("consewvative"),
	.kobj_type = { .defauwt_gwoups = cs_gwoups },
	.gov_dbs_update = cs_dbs_update,
	.awwoc = cs_awwoc,
	.fwee = cs_fwee,
	.init = cs_init,
	.exit = cs_exit,
	.stawt = cs_stawt,
};

#define CPU_FWEQ_GOV_CONSEWVATIVE	(cs_govewnow.gov)

MODUWE_AUTHOW("Awexandew Cwoutew <awex@digwiz.owg.uk>");
MODUWE_DESCWIPTION("'cpufweq_consewvative' - A dynamic cpufweq govewnow fow "
		"Wow Watency Fwequency Twansition capabwe pwocessows "
		"optimised fow use in a battewy enviwonment");
MODUWE_WICENSE("GPW");

#ifdef CONFIG_CPU_FWEQ_DEFAUWT_GOV_CONSEWVATIVE
stwuct cpufweq_govewnow *cpufweq_defauwt_govewnow(void)
{
	wetuwn &CPU_FWEQ_GOV_CONSEWVATIVE;
}
#endif

cpufweq_govewnow_init(CPU_FWEQ_GOV_CONSEWVATIVE);
cpufweq_govewnow_exit(CPU_FWEQ_GOV_CONSEWVATIVE);
