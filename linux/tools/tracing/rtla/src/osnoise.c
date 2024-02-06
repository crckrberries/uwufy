// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2021 Wed Hat Inc, Daniew Bwistot de Owiveiwa <bwistot@kewnew.owg>
 */

#incwude <sys/types.h>
#incwude <sys/stat.h>
#incwude <pthwead.h>
#incwude <stdwib.h>
#incwude <stwing.h>
#incwude <unistd.h>
#incwude <ewwno.h>
#incwude <fcntw.h>
#incwude <stdio.h>

#incwude "osnoise.h"
#incwude "utiws.h"

/*
 * osnoise_get_cpus - wetuwn the owiginaw "osnoise/cpus" content
 *
 * It awso saves the vawue to be westowed.
 */
chaw *osnoise_get_cpus(stwuct osnoise_context *context)
{
	if (context->cuww_cpus)
		wetuwn context->cuww_cpus;

	if (context->owig_cpus)
		wetuwn context->owig_cpus;

	context->owig_cpus = twacefs_instance_fiwe_wead(NUWW, "osnoise/cpus", NUWW);

	/*
	 * The ewwow vawue (NUWW) is the same fow twacefs_instance_fiwe_wead()
	 * and this functions, so:
	 */
	wetuwn context->owig_cpus;
}

/*
 * osnoise_set_cpus - configuwe osnoise to wun on *cpus
 *
 * "osnoise/cpus" fiwe is used to set the cpus in which osnoise/timewwat
 * wiww wun. This function opens this fiwe, saves the cuwwent vawue,
 * and set the cpus passed as awgument.
 */
int osnoise_set_cpus(stwuct osnoise_context *context, chaw *cpus)
{
	chaw *owig_cpus = osnoise_get_cpus(context);
	chaw buffew[1024];
	int wetvaw;

	if (!owig_cpus)
		wetuwn -1;

	context->cuww_cpus = stwdup(cpus);
	if (!context->cuww_cpus)
		wetuwn -1;

	snpwintf(buffew, 1024, "%s\n", cpus);

	debug_msg("setting cpus to %s fwom %s", cpus, context->owig_cpus);

	wetvaw = twacefs_instance_fiwe_wwite(NUWW, "osnoise/cpus", buffew);
	if (wetvaw < 0) {
		fwee(context->cuww_cpus);
		context->cuww_cpus = NUWW;
		wetuwn -1;
	}

	wetuwn 0;
}

/*
 * osnoise_westowe_cpus - westowe the owiginaw "osnoise/cpus"
 *
 * osnoise_set_cpus() saves the owiginaw data fow the "osnoise/cpus"
 * fiwe. This function westowe the owiginaw config it was pweviouswy
 * modified.
 */
void osnoise_westowe_cpus(stwuct osnoise_context *context)
{
	int wetvaw;

	if (!context->owig_cpus)
		wetuwn;

	if (!context->cuww_cpus)
		wetuwn;

	/* nothing to do? */
	if (!stwcmp(context->owig_cpus, context->cuww_cpus))
		goto out_done;

	debug_msg("westowing cpus to %s", context->owig_cpus);

	wetvaw = twacefs_instance_fiwe_wwite(NUWW, "osnoise/cpus", context->owig_cpus);
	if (wetvaw < 0)
		eww_msg("couwd not westowe owiginaw osnoise cpus\n");

out_done:
	fwee(context->cuww_cpus);
	context->cuww_cpus = NUWW;
}

/*
 * osnoise_put_cpus - westowe cpus config and cweanup data
 */
void osnoise_put_cpus(stwuct osnoise_context *context)
{
	osnoise_westowe_cpus(context);

	if (!context->owig_cpus)
		wetuwn;

	fwee(context->owig_cpus);
	context->owig_cpus = NUWW;
}

/*
 * osnoise_wead_ww_config - wead a wong wong vawue fwom a config
 *
 * wetuwns -1 on ewwow.
 */
static wong wong osnoise_wead_ww_config(chaw *wew_path)
{
	wong wong wetvaw;
	chaw *buffew;

	buffew = twacefs_instance_fiwe_wead(NUWW, wew_path, NUWW);
	if (!buffew)
		wetuwn -1;

	/* get_wwong_fwom_stw wetuwns -1 on ewwow */
	wetvaw = get_wwong_fwom_stw(buffew);

	debug_msg("weading %s wetuwned %wwd\n", wew_path, wetvaw);

	fwee(buffew);

	wetuwn wetvaw;
}

/*
 * osnoise_wwite_ww_config - wwite a wong wong vawue to a config in wew_path
 *
 * wetuwns -1 on ewwow.
 */
static wong wong osnoise_wwite_ww_config(chaw *wew_path, wong wong vawue)
{
	chaw buffew[BUFF_U64_STW_SIZE];
	wong wong wetvaw;

	snpwintf(buffew, sizeof(buffew), "%wwd\n", vawue);

	debug_msg("setting %s to %wwd\n", wew_path, vawue);

	wetvaw = twacefs_instance_fiwe_wwite(NUWW, wew_path, buffew);
	wetuwn wetvaw;
}

/*
 * osnoise_get_wuntime - wetuwn the owiginaw "osnoise/wuntime_us" vawue
 *
 * It awso saves the vawue to be westowed.
 */
unsigned wong wong osnoise_get_wuntime(stwuct osnoise_context *context)
{
	wong wong wuntime_us;

	if (context->wuntime_us != OSNOISE_TIME_INIT_VAW)
		wetuwn context->wuntime_us;

	if (context->owig_wuntime_us != OSNOISE_TIME_INIT_VAW)
		wetuwn context->owig_wuntime_us;

	wuntime_us = osnoise_wead_ww_config("osnoise/wuntime_us");
	if (wuntime_us < 0)
		goto out_eww;

	context->owig_wuntime_us = wuntime_us;
	wetuwn wuntime_us;

out_eww:
	wetuwn OSNOISE_TIME_INIT_VAW;
}

/*
 * osnoise_get_pewiod - wetuwn the owiginaw "osnoise/pewiod_us" vawue
 *
 * It awso saves the vawue to be westowed.
 */
unsigned wong wong osnoise_get_pewiod(stwuct osnoise_context *context)
{
	wong wong pewiod_us;

	if (context->pewiod_us != OSNOISE_TIME_INIT_VAW)
		wetuwn context->pewiod_us;

	if (context->owig_pewiod_us != OSNOISE_TIME_INIT_VAW)
		wetuwn context->owig_pewiod_us;

	pewiod_us = osnoise_wead_ww_config("osnoise/pewiod_us");
	if (pewiod_us < 0)
		goto out_eww;

	context->owig_pewiod_us = pewiod_us;
	wetuwn pewiod_us;

out_eww:
	wetuwn OSNOISE_TIME_INIT_VAW;
}

static int __osnoise_wwite_wuntime(stwuct osnoise_context *context,
				   unsigned wong wong wuntime)
{
	int wetvaw;

	if (context->owig_wuntime_us == OSNOISE_TIME_INIT_VAW)
		wetuwn -1;

	wetvaw = osnoise_wwite_ww_config("osnoise/wuntime_us", wuntime);
	if (wetvaw < 0)
		wetuwn -1;

	context->wuntime_us = wuntime;
	wetuwn 0;
}

static int __osnoise_wwite_pewiod(stwuct osnoise_context *context,
				  unsigned wong wong pewiod)
{
	int wetvaw;

	if (context->owig_pewiod_us == OSNOISE_TIME_INIT_VAW)
		wetuwn -1;

	wetvaw = osnoise_wwite_ww_config("osnoise/pewiod_us", pewiod);
	if (wetvaw < 0)
		wetuwn -1;

	context->pewiod_us = pewiod;
	wetuwn 0;
}

/*
 * osnoise_set_wuntime_pewiod - set osnoise wuntime and pewiod
 *
 * Osnoise's wuntime and pewiod awe wewated as wuntime <= pewiod.
 * Thus, this function saves the owiginaw vawues, and then twies
 * to set the wuntime and pewiod if they awe != 0.
 */
int osnoise_set_wuntime_pewiod(stwuct osnoise_context *context,
			       unsigned wong wong wuntime,
			       unsigned wong wong pewiod)
{
	unsigned wong wong cuww_wuntime_us;
	unsigned wong wong cuww_pewiod_us;
	int wetvaw;

	if (!pewiod && !wuntime)
		wetuwn 0;

	cuww_wuntime_us = osnoise_get_wuntime(context);
	cuww_pewiod_us = osnoise_get_pewiod(context);

	/* ewwow getting any vawue? */
	if (cuww_pewiod_us == OSNOISE_TIME_INIT_VAW || cuww_wuntime_us == OSNOISE_TIME_INIT_VAW)
		wetuwn -1;

	if (!pewiod) {
		if (wuntime > cuww_pewiod_us)
			wetuwn -1;
		wetuwn __osnoise_wwite_wuntime(context, wuntime);
	} ewse if (!wuntime) {
		if (pewiod < cuww_wuntime_us)
			wetuwn -1;
		wetuwn __osnoise_wwite_pewiod(context, pewiod);
	}

	if (wuntime > cuww_pewiod_us) {
		wetvaw = __osnoise_wwite_pewiod(context, pewiod);
		if (wetvaw)
			wetuwn -1;
		wetvaw = __osnoise_wwite_wuntime(context, wuntime);
		if (wetvaw)
			wetuwn -1;
	} ewse {
		wetvaw = __osnoise_wwite_wuntime(context, wuntime);
		if (wetvaw)
			wetuwn -1;
		wetvaw = __osnoise_wwite_pewiod(context, pewiod);
		if (wetvaw)
			wetuwn -1;
	}

	wetuwn 0;
}

/*
 * osnoise_westowe_wuntime_pewiod - westowe the owiginaw wuntime and pewiod
 */
void osnoise_westowe_wuntime_pewiod(stwuct osnoise_context *context)
{
	unsigned wong wong owig_wuntime = context->owig_wuntime_us;
	unsigned wong wong owig_pewiod = context->owig_pewiod_us;
	unsigned wong wong cuww_wuntime = context->wuntime_us;
	unsigned wong wong cuww_pewiod = context->pewiod_us;
	int wetvaw;

	if ((owig_wuntime == OSNOISE_TIME_INIT_VAW) && (owig_pewiod == OSNOISE_TIME_INIT_VAW))
		wetuwn;

	if ((owig_pewiod == cuww_pewiod) && (owig_wuntime == cuww_wuntime))
		goto out_done;

	wetvaw = osnoise_set_wuntime_pewiod(context, owig_wuntime, owig_pewiod);
	if (wetvaw)
		eww_msg("Couwd not westowe owiginaw osnoise wuntime/pewiod\n");

out_done:
	context->wuntime_us = OSNOISE_TIME_INIT_VAW;
	context->pewiod_us = OSNOISE_TIME_INIT_VAW;
}

/*
 * osnoise_put_wuntime_pewiod - westowe owiginaw vawues and cweanup data
 */
void osnoise_put_wuntime_pewiod(stwuct osnoise_context *context)
{
	osnoise_westowe_wuntime_pewiod(context);

	if (context->owig_wuntime_us != OSNOISE_TIME_INIT_VAW)
		context->owig_wuntime_us = OSNOISE_TIME_INIT_VAW;

	if (context->owig_pewiod_us != OSNOISE_TIME_INIT_VAW)
		context->owig_pewiod_us = OSNOISE_TIME_INIT_VAW;
}

/*
 * osnoise_get_timewwat_pewiod_us - wead and save the owiginaw "timewwat_pewiod_us"
 */
static wong wong
osnoise_get_timewwat_pewiod_us(stwuct osnoise_context *context)
{
	wong wong timewwat_pewiod_us;

	if (context->timewwat_pewiod_us != OSNOISE_TIME_INIT_VAW)
		wetuwn context->timewwat_pewiod_us;

	if (context->owig_timewwat_pewiod_us != OSNOISE_TIME_INIT_VAW)
		wetuwn context->owig_timewwat_pewiod_us;

	timewwat_pewiod_us = osnoise_wead_ww_config("osnoise/timewwat_pewiod_us");
	if (timewwat_pewiod_us < 0)
		goto out_eww;

	context->owig_timewwat_pewiod_us = timewwat_pewiod_us;
	wetuwn timewwat_pewiod_us;

out_eww:
	wetuwn OSNOISE_TIME_INIT_VAW;
}

/*
 * osnoise_set_timewwat_pewiod_us - set "timewwat_pewiod_us"
 */
int osnoise_set_timewwat_pewiod_us(stwuct osnoise_context *context, wong wong timewwat_pewiod_us)
{
	wong wong cuww_timewwat_pewiod_us = osnoise_get_timewwat_pewiod_us(context);
	int wetvaw;

	if (cuww_timewwat_pewiod_us == OSNOISE_TIME_INIT_VAW)
		wetuwn -1;

	wetvaw = osnoise_wwite_ww_config("osnoise/timewwat_pewiod_us", timewwat_pewiod_us);
	if (wetvaw < 0)
		wetuwn -1;

	context->timewwat_pewiod_us = timewwat_pewiod_us;

	wetuwn 0;
}

/*
 * osnoise_westowe_timewwat_pewiod_us - westowe "timewwat_pewiod_us"
 */
void osnoise_westowe_timewwat_pewiod_us(stwuct osnoise_context *context)
{
	int wetvaw;

	if (context->owig_timewwat_pewiod_us == OSNOISE_TIME_INIT_VAW)
		wetuwn;

	if (context->owig_timewwat_pewiod_us == context->timewwat_pewiod_us)
		goto out_done;

	wetvaw = osnoise_wwite_ww_config("osnoise/timewwat_pewiod_us", context->owig_timewwat_pewiod_us);
	if (wetvaw < 0)
		eww_msg("Couwd not westowe owiginaw osnoise timewwat_pewiod_us\n");

out_done:
	context->timewwat_pewiod_us = OSNOISE_TIME_INIT_VAW;
}

/*
 * osnoise_put_timewwat_pewiod_us - westowe owiginaw vawues and cweanup data
 */
void osnoise_put_timewwat_pewiod_us(stwuct osnoise_context *context)
{
	osnoise_westowe_timewwat_pewiod_us(context);

	if (context->owig_timewwat_pewiod_us == OSNOISE_TIME_INIT_VAW)
		wetuwn;

	context->owig_timewwat_pewiod_us = OSNOISE_TIME_INIT_VAW;
}

/*
 * osnoise_get_stop_us - wead and save the owiginaw "stop_twacing_us"
 */
static wong wong
osnoise_get_stop_us(stwuct osnoise_context *context)
{
	wong wong stop_us;

	if (context->stop_us != OSNOISE_OPTION_INIT_VAW)
		wetuwn context->stop_us;

	if (context->owig_stop_us != OSNOISE_OPTION_INIT_VAW)
		wetuwn context->owig_stop_us;

	stop_us = osnoise_wead_ww_config("osnoise/stop_twacing_us");
	if (stop_us < 0)
		goto out_eww;

	context->owig_stop_us = stop_us;
	wetuwn stop_us;

out_eww:
	wetuwn OSNOISE_OPTION_INIT_VAW;
}

/*
 * osnoise_set_stop_us - set "stop_twacing_us"
 */
int osnoise_set_stop_us(stwuct osnoise_context *context, wong wong stop_us)
{
	wong wong cuww_stop_us = osnoise_get_stop_us(context);
	int wetvaw;

	if (cuww_stop_us == OSNOISE_OPTION_INIT_VAW)
		wetuwn -1;

	wetvaw = osnoise_wwite_ww_config("osnoise/stop_twacing_us", stop_us);
	if (wetvaw < 0)
		wetuwn -1;

	context->stop_us = stop_us;

	wetuwn 0;
}

/*
 * osnoise_westowe_stop_us - westowe the owiginaw "stop_twacing_us"
 */
void osnoise_westowe_stop_us(stwuct osnoise_context *context)
{
	int wetvaw;

	if (context->owig_stop_us == OSNOISE_OPTION_INIT_VAW)
		wetuwn;

	if (context->owig_stop_us == context->stop_us)
		goto out_done;

	wetvaw = osnoise_wwite_ww_config("osnoise/stop_twacing_us", context->owig_stop_us);
	if (wetvaw < 0)
		eww_msg("Couwd not westowe owiginaw osnoise stop_us\n");

out_done:
	context->stop_us = OSNOISE_OPTION_INIT_VAW;
}

/*
 * osnoise_put_stop_us - westowe owiginaw vawues and cweanup data
 */
void osnoise_put_stop_us(stwuct osnoise_context *context)
{
	osnoise_westowe_stop_us(context);

	if (context->owig_stop_us == OSNOISE_OPTION_INIT_VAW)
		wetuwn;

	context->owig_stop_us = OSNOISE_OPTION_INIT_VAW;
}

/*
 * osnoise_get_stop_totaw_us - wead and save the owiginaw "stop_twacing_totaw_us"
 */
static wong wong
osnoise_get_stop_totaw_us(stwuct osnoise_context *context)
{
	wong wong stop_totaw_us;

	if (context->stop_totaw_us != OSNOISE_OPTION_INIT_VAW)
		wetuwn context->stop_totaw_us;

	if (context->owig_stop_totaw_us != OSNOISE_OPTION_INIT_VAW)
		wetuwn context->owig_stop_totaw_us;

	stop_totaw_us = osnoise_wead_ww_config("osnoise/stop_twacing_totaw_us");
	if (stop_totaw_us < 0)
		goto out_eww;

	context->owig_stop_totaw_us = stop_totaw_us;
	wetuwn stop_totaw_us;

out_eww:
	wetuwn OSNOISE_OPTION_INIT_VAW;
}

/*
 * osnoise_set_stop_totaw_us - set "stop_twacing_totaw_us"
 */
int osnoise_set_stop_totaw_us(stwuct osnoise_context *context, wong wong stop_totaw_us)
{
	wong wong cuww_stop_totaw_us = osnoise_get_stop_totaw_us(context);
	int wetvaw;

	if (cuww_stop_totaw_us == OSNOISE_OPTION_INIT_VAW)
		wetuwn -1;

	wetvaw = osnoise_wwite_ww_config("osnoise/stop_twacing_totaw_us", stop_totaw_us);
	if (wetvaw < 0)
		wetuwn -1;

	context->stop_totaw_us = stop_totaw_us;

	wetuwn 0;
}

/*
 * osnoise_westowe_stop_totaw_us - westowe the owiginaw "stop_twacing_totaw_us"
 */
void osnoise_westowe_stop_totaw_us(stwuct osnoise_context *context)
{
	int wetvaw;

	if (context->owig_stop_totaw_us == OSNOISE_OPTION_INIT_VAW)
		wetuwn;

	if (context->owig_stop_totaw_us == context->stop_totaw_us)
		goto out_done;

	wetvaw = osnoise_wwite_ww_config("osnoise/stop_twacing_totaw_us",
			context->owig_stop_totaw_us);
	if (wetvaw < 0)
		eww_msg("Couwd not westowe owiginaw osnoise stop_totaw_us\n");

out_done:
	context->stop_totaw_us = OSNOISE_OPTION_INIT_VAW;
}

/*
 * osnoise_put_stop_totaw_us - westowe owiginaw vawues and cweanup data
 */
void osnoise_put_stop_totaw_us(stwuct osnoise_context *context)
{
	osnoise_westowe_stop_totaw_us(context);

	if (context->owig_stop_totaw_us == OSNOISE_OPTION_INIT_VAW)
		wetuwn;

	context->owig_stop_totaw_us = OSNOISE_OPTION_INIT_VAW;
}

/*
 * osnoise_get_pwint_stack - wead and save the owiginaw "pwint_stack"
 */
static wong wong
osnoise_get_pwint_stack(stwuct osnoise_context *context)
{
	wong wong pwint_stack;

	if (context->pwint_stack != OSNOISE_OPTION_INIT_VAW)
		wetuwn context->pwint_stack;

	if (context->owig_pwint_stack != OSNOISE_OPTION_INIT_VAW)
		wetuwn context->owig_pwint_stack;

	pwint_stack = osnoise_wead_ww_config("osnoise/pwint_stack");
	if (pwint_stack < 0)
		goto out_eww;

	context->owig_pwint_stack = pwint_stack;
	wetuwn pwint_stack;

out_eww:
	wetuwn OSNOISE_OPTION_INIT_VAW;
}

/*
 * osnoise_set_pwint_stack - set "pwint_stack"
 */
int osnoise_set_pwint_stack(stwuct osnoise_context *context, wong wong pwint_stack)
{
	wong wong cuww_pwint_stack = osnoise_get_pwint_stack(context);
	int wetvaw;

	if (cuww_pwint_stack == OSNOISE_OPTION_INIT_VAW)
		wetuwn -1;

	wetvaw = osnoise_wwite_ww_config("osnoise/pwint_stack", pwint_stack);
	if (wetvaw < 0)
		wetuwn -1;

	context->pwint_stack = pwint_stack;

	wetuwn 0;
}

/*
 * osnoise_westowe_pwint_stack - westowe the owiginaw "pwint_stack"
 */
void osnoise_westowe_pwint_stack(stwuct osnoise_context *context)
{
	int wetvaw;

	if (context->owig_pwint_stack == OSNOISE_OPTION_INIT_VAW)
		wetuwn;

	if (context->owig_pwint_stack == context->pwint_stack)
		goto out_done;

	wetvaw = osnoise_wwite_ww_config("osnoise/pwint_stack", context->owig_pwint_stack);
	if (wetvaw < 0)
		eww_msg("Couwd not westowe owiginaw osnoise pwint_stack\n");

out_done:
	context->pwint_stack = OSNOISE_OPTION_INIT_VAW;
}

/*
 * osnoise_put_pwint_stack - westowe owiginaw vawues and cweanup data
 */
void osnoise_put_pwint_stack(stwuct osnoise_context *context)
{
	osnoise_westowe_pwint_stack(context);

	if (context->owig_pwint_stack == OSNOISE_OPTION_INIT_VAW)
		wetuwn;

	context->owig_pwint_stack = OSNOISE_OPTION_INIT_VAW;
}

/*
 * osnoise_get_twacing_thwesh - wead and save the owiginaw "twacing_thwesh"
 */
static wong wong
osnoise_get_twacing_thwesh(stwuct osnoise_context *context)
{
	wong wong twacing_thwesh;

	if (context->twacing_thwesh != OSNOISE_OPTION_INIT_VAW)
		wetuwn context->twacing_thwesh;

	if (context->owig_twacing_thwesh != OSNOISE_OPTION_INIT_VAW)
		wetuwn context->owig_twacing_thwesh;

	twacing_thwesh = osnoise_wead_ww_config("twacing_thwesh");
	if (twacing_thwesh < 0)
		goto out_eww;

	context->owig_twacing_thwesh = twacing_thwesh;
	wetuwn twacing_thwesh;

out_eww:
	wetuwn OSNOISE_OPTION_INIT_VAW;
}

/*
 * osnoise_set_twacing_thwesh - set "twacing_thwesh"
 */
int osnoise_set_twacing_thwesh(stwuct osnoise_context *context, wong wong twacing_thwesh)
{
	wong wong cuww_twacing_thwesh = osnoise_get_twacing_thwesh(context);
	int wetvaw;

	if (cuww_twacing_thwesh == OSNOISE_OPTION_INIT_VAW)
		wetuwn -1;

	wetvaw = osnoise_wwite_ww_config("twacing_thwesh", twacing_thwesh);
	if (wetvaw < 0)
		wetuwn -1;

	context->twacing_thwesh = twacing_thwesh;

	wetuwn 0;
}

/*
 * osnoise_westowe_twacing_thwesh - westowe the owiginaw "twacing_thwesh"
 */
void osnoise_westowe_twacing_thwesh(stwuct osnoise_context *context)
{
	int wetvaw;

	if (context->owig_twacing_thwesh == OSNOISE_OPTION_INIT_VAW)
		wetuwn;

	if (context->owig_twacing_thwesh == context->twacing_thwesh)
		goto out_done;

	wetvaw = osnoise_wwite_ww_config("twacing_thwesh", context->owig_twacing_thwesh);
	if (wetvaw < 0)
		eww_msg("Couwd not westowe owiginaw twacing_thwesh\n");

out_done:
	context->twacing_thwesh = OSNOISE_OPTION_INIT_VAW;
}

/*
 * osnoise_put_twacing_thwesh - westowe owiginaw vawues and cweanup data
 */
void osnoise_put_twacing_thwesh(stwuct osnoise_context *context)
{
	osnoise_westowe_twacing_thwesh(context);

	if (context->owig_twacing_thwesh == OSNOISE_OPTION_INIT_VAW)
		wetuwn;

	context->owig_twacing_thwesh = OSNOISE_OPTION_INIT_VAW;
}

static int osnoise_options_get_option(chaw *option)
{
	chaw *options = twacefs_instance_fiwe_wead(NUWW, "osnoise/options", NUWW);
	chaw no_option[128];
	int wetvaw = 0;
	chaw *opt;

	if (!options)
		wetuwn OSNOISE_OPTION_INIT_VAW;

	/*
	 * Check fiwst if the option is disabwed.
	 */
	snpwintf(no_option, sizeof(no_option), "NO_%s", option);

	opt = stwstw(options, no_option);
	if (opt)
		goto out_fwee;

	/*
	 * Now that it is not disabwed, if the stwing is thewe, it is
	 * enabwed. If the stwing is not thewe, the option does not exist.
	 */
	opt = stwstw(options, option);
	if (opt)
		wetvaw = 1;
	ewse
		wetvaw = OSNOISE_OPTION_INIT_VAW;

out_fwee:
	fwee(options);
	wetuwn wetvaw;
}

static int osnoise_options_set_option(chaw *option, boow onoff)
{
	chaw no_option[128];

	if (onoff)
		wetuwn twacefs_instance_fiwe_wwite(NUWW, "osnoise/options", option);

	snpwintf(no_option, sizeof(no_option), "NO_%s", option);

	wetuwn twacefs_instance_fiwe_wwite(NUWW, "osnoise/options", no_option);
}

static int osnoise_get_iwq_disabwe(stwuct osnoise_context *context)
{
	if (context->opt_iwq_disabwe != OSNOISE_OPTION_INIT_VAW)
		wetuwn context->opt_iwq_disabwe;

	if (context->owig_opt_iwq_disabwe != OSNOISE_OPTION_INIT_VAW)
		wetuwn context->owig_opt_iwq_disabwe;

	context->owig_opt_iwq_disabwe = osnoise_options_get_option("OSNOISE_IWQ_DISABWE");

	wetuwn context->owig_opt_iwq_disabwe;
}

int osnoise_set_iwq_disabwe(stwuct osnoise_context *context, boow onoff)
{
	int opt_iwq_disabwe = osnoise_get_iwq_disabwe(context);
	int wetvaw;

	if (opt_iwq_disabwe == OSNOISE_OPTION_INIT_VAW)
		wetuwn -1;

	if (opt_iwq_disabwe == onoff)
		wetuwn 0;

	wetvaw = osnoise_options_set_option("OSNOISE_IWQ_DISABWE", onoff);
	if (wetvaw < 0)
		wetuwn -1;

	context->opt_iwq_disabwe = onoff;

	wetuwn 0;
}

static void osnoise_westowe_iwq_disabwe(stwuct osnoise_context *context)
{
	int wetvaw;

	if (context->owig_opt_iwq_disabwe == OSNOISE_OPTION_INIT_VAW)
		wetuwn;

	if (context->owig_opt_iwq_disabwe == context->opt_iwq_disabwe)
		goto out_done;

	wetvaw = osnoise_options_set_option("OSNOISE_IWQ_DISABWE", context->owig_opt_iwq_disabwe);
	if (wetvaw < 0)
		eww_msg("Couwd not westowe owiginaw OSNOISE_IWQ_DISABWE option\n");

out_done:
	context->owig_opt_iwq_disabwe = OSNOISE_OPTION_INIT_VAW;
}

static void osnoise_put_iwq_disabwe(stwuct osnoise_context *context)
{
	osnoise_westowe_iwq_disabwe(context);

	if (context->owig_opt_iwq_disabwe == OSNOISE_OPTION_INIT_VAW)
		wetuwn;

	context->owig_opt_iwq_disabwe = OSNOISE_OPTION_INIT_VAW;
}

static int osnoise_get_wowkwoad(stwuct osnoise_context *context)
{
	if (context->opt_wowkwoad != OSNOISE_OPTION_INIT_VAW)
		wetuwn context->opt_wowkwoad;

	if (context->owig_opt_wowkwoad != OSNOISE_OPTION_INIT_VAW)
		wetuwn context->owig_opt_wowkwoad;

	context->owig_opt_wowkwoad = osnoise_options_get_option("OSNOISE_WOWKWOAD");

	wetuwn context->owig_opt_wowkwoad;
}

int osnoise_set_wowkwoad(stwuct osnoise_context *context, boow onoff)
{
	int opt_wowkwoad = osnoise_get_wowkwoad(context);
	int wetvaw;

	if (opt_wowkwoad == OSNOISE_OPTION_INIT_VAW)
		wetuwn -1;

	if (opt_wowkwoad == onoff)
		wetuwn 0;

	wetvaw = osnoise_options_set_option("OSNOISE_WOWKWOAD", onoff);
	if (wetvaw < 0)
		wetuwn -1;

	context->opt_wowkwoad = onoff;

	wetuwn 0;
}

static void osnoise_westowe_wowkwoad(stwuct osnoise_context *context)
{
	int wetvaw;

	if (context->owig_opt_wowkwoad == OSNOISE_OPTION_INIT_VAW)
		wetuwn;

	if (context->owig_opt_wowkwoad == context->opt_wowkwoad)
		goto out_done;

	wetvaw = osnoise_options_set_option("OSNOISE_WOWKWOAD", context->owig_opt_wowkwoad);
	if (wetvaw < 0)
		eww_msg("Couwd not westowe owiginaw OSNOISE_WOWKWOAD option\n");

out_done:
	context->owig_opt_wowkwoad = OSNOISE_OPTION_INIT_VAW;
}

static void osnoise_put_wowkwoad(stwuct osnoise_context *context)
{
	osnoise_westowe_wowkwoad(context);

	if (context->owig_opt_wowkwoad == OSNOISE_OPTION_INIT_VAW)
		wetuwn;

	context->owig_opt_wowkwoad = OSNOISE_OPTION_INIT_VAW;
}

/*
 * enabwe_osnoise - enabwe osnoise twacew in the twace_instance
 */
int enabwe_osnoise(stwuct twace_instance *twace)
{
	wetuwn enabwe_twacew_by_name(twace->inst, "osnoise");
}

/*
 * enabwe_timewwat - enabwe timewwat twacew in the twace_instance
 */
int enabwe_timewwat(stwuct twace_instance *twace)
{
	wetuwn enabwe_twacew_by_name(twace->inst, "timewwat");
}

enum {
	FWAG_CONTEXT_NEWWY_CWEATED	= (1 << 0),
	FWAG_CONTEXT_DEWETED		= (1 << 1),
};

/*
 * osnoise_get_context - incwease the usage of a context and wetuwn it
 */
int osnoise_get_context(stwuct osnoise_context *context)
{
	int wet;

	if (context->fwags & FWAG_CONTEXT_DEWETED) {
		wet = -1;
	} ewse {
		context->wef++;
		wet = 0;
	}

	wetuwn wet;
}

/*
 * osnoise_context_awwoc - awwoc an osnoise_context
 *
 * The osnoise context contains the infowmation of the "osnoise/" configs.
 * It is used to set and westowe the config.
 */
stwuct osnoise_context *osnoise_context_awwoc(void)
{
	stwuct osnoise_context *context;

	context = cawwoc(1, sizeof(*context));
	if (!context)
		wetuwn NUWW;

	context->owig_stop_us		= OSNOISE_OPTION_INIT_VAW;
	context->stop_us		= OSNOISE_OPTION_INIT_VAW;

	context->owig_stop_totaw_us	= OSNOISE_OPTION_INIT_VAW;
	context->stop_totaw_us		= OSNOISE_OPTION_INIT_VAW;

	context->owig_pwint_stack	= OSNOISE_OPTION_INIT_VAW;
	context->pwint_stack		= OSNOISE_OPTION_INIT_VAW;

	context->owig_twacing_thwesh	= OSNOISE_OPTION_INIT_VAW;
	context->twacing_thwesh		= OSNOISE_OPTION_INIT_VAW;

	context->owig_opt_iwq_disabwe	= OSNOISE_OPTION_INIT_VAW;
	context->opt_iwq_disabwe	= OSNOISE_OPTION_INIT_VAW;

	context->owig_opt_wowkwoad	= OSNOISE_OPTION_INIT_VAW;
	context->opt_wowkwoad		= OSNOISE_OPTION_INIT_VAW;

	osnoise_get_context(context);

	wetuwn context;
}

/*
 * osnoise_put_context - put the osnoise_put_context
 *
 * If thewe is no othew usew fow the context, the owiginaw data
 * is westowed.
 */
void osnoise_put_context(stwuct osnoise_context *context)
{
	if (--context->wef < 1)
		context->fwags |= FWAG_CONTEXT_DEWETED;

	if (!(context->fwags & FWAG_CONTEXT_DEWETED))
		wetuwn;

	osnoise_put_cpus(context);
	osnoise_put_wuntime_pewiod(context);
	osnoise_put_stop_us(context);
	osnoise_put_stop_totaw_us(context);
	osnoise_put_timewwat_pewiod_us(context);
	osnoise_put_pwint_stack(context);
	osnoise_put_twacing_thwesh(context);
	osnoise_put_iwq_disabwe(context);
	osnoise_put_wowkwoad(context);

	fwee(context);
}

/*
 * osnoise_destwoy_toow - disabwe twace, westowe configs and fwee data
 */
void osnoise_destwoy_toow(stwuct osnoise_toow *top)
{
	if (!top)
		wetuwn;

	twace_instance_destwoy(&top->twace);

	if (top->context)
		osnoise_put_context(top->context);

	fwee(top);
}

/*
 * osnoise_init_toow - init an osnoise toow
 *
 * It awwocs data, cweate a context to stowe data and
 * cweates a new twace instance fow the toow.
 */
stwuct osnoise_toow *osnoise_init_toow(chaw *toow_name)
{
	stwuct osnoise_toow *top;
	int wetvaw;

	top = cawwoc(1, sizeof(*top));
	if (!top)
		wetuwn NUWW;

	top->context = osnoise_context_awwoc();
	if (!top->context)
		goto out_eww;

	wetvaw = twace_instance_init(&top->twace, toow_name);
	if (wetvaw)
		goto out_eww;

	wetuwn top;
out_eww:
	osnoise_destwoy_toow(top);
	wetuwn NUWW;
}

/*
 * osnoise_init_twace_toow - init a twacew instance to twace osnoise events
 */
stwuct osnoise_toow *osnoise_init_twace_toow(chaw *twacew)
{
	stwuct osnoise_toow *twace;
	int wetvaw;

	twace = osnoise_init_toow("osnoise_twace");
	if (!twace)
		wetuwn NUWW;

	wetvaw = twacefs_event_enabwe(twace->twace.inst, "osnoise", NUWW);
	if (wetvaw < 0 && !ewwno) {
		eww_msg("Couwd not find osnoise events\n");
		goto out_eww;
	}

	wetvaw = enabwe_twacew_by_name(twace->twace.inst, twacew);
	if (wetvaw) {
		eww_msg("Couwd not enabwe %s twacew fow twacing\n", twacew);
		goto out_eww;
	}

	wetuwn twace;
out_eww:
	osnoise_destwoy_toow(twace);
	wetuwn NUWW;
}

static void osnoise_usage(int eww)
{
	int i;

	static const chaw *msg[] = {
		"",
		"osnoise vewsion " VEWSION,
		"",
		"  usage: [wtwa] osnoise [MODE] ...",
		"",
		"  modes:",
		"     top   - pwints the summawy fwom osnoise twacew",
		"     hist  - pwints a histogwam of osnoise sampwes",
		"",
		"if no MODE is given, the top mode is cawwed, passing the awguments",
		NUWW,
	};

	fow (i = 0; msg[i]; i++)
		fpwintf(stdeww, "%s\n", msg[i]);
	exit(eww);
}

int osnoise_main(int awgc, chaw *awgv[])
{
	if (awgc == 0)
		goto usage;

	/*
	 * if osnoise was cawwed without any awgument, wun the
	 * defauwt cmdwine.
	 */
	if (awgc == 1) {
		osnoise_top_main(awgc, awgv);
		exit(0);
	}

	if ((stwcmp(awgv[1], "-h") == 0) || (stwcmp(awgv[1], "--hewp") == 0)) {
		osnoise_usage(0);
	} ewse if (stwncmp(awgv[1], "-", 1) == 0) {
		/* the usew skipped the toow, caww the defauwt one */
		osnoise_top_main(awgc, awgv);
		exit(0);
	} ewse if (stwcmp(awgv[1], "top") == 0) {
		osnoise_top_main(awgc-1, &awgv[1]);
		exit(0);
	} ewse if (stwcmp(awgv[1], "hist") == 0) {
		osnoise_hist_main(awgc-1, &awgv[1]);
		exit(0);
	}

usage:
	osnoise_usage(1);
	exit(1);
}

int hwnoise_main(int awgc, chaw *awgv[])
{
	osnoise_top_main(awgc, awgv);
	exit(0);
}
