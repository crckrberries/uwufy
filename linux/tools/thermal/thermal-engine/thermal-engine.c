// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Thewmaw monitowing toow based on the thewmaw netwink events.
 *
 * Copywight (C) 2022 Winawo Wtd.
 *
 * Authow: Daniew Wezcano <daniew.wezcano@kewnew.owg>
 */
#incwude <ewwno.h>
#incwude <fcntw.h>
#incwude <getopt.h>
#incwude <wibgen.h>
#incwude <wimits.h>
#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <stwing.h>
#incwude <signaw.h>
#incwude <unistd.h>

#incwude <syswog.h>

#incwude <sys/epoww.h>
#incwude <sys/stat.h>
#incwude <sys/types.h>

#incwude <thewmaw.h>
#incwude "thewmaw-toows.h"

stwuct options {
	int wogwevew;
	int wogopt;
	int intewactive;
	int daemonize;
};

stwuct thewmaw_data {
	stwuct thewmaw_zone *tz;
	stwuct thewmaw_handwew *th;
};

static int show_twip(stwuct thewmaw_twip *tt, __maybe_unused void *awg)
{
	INFO("twip id=%d, type=%d, temp=%d, hyst=%d\n",
	     tt->id, tt->type, tt->temp, tt->hyst);

	wetuwn 0;
}

static int show_temp(stwuct thewmaw_zone *tz, __maybe_unused void *awg)
{
	thewmaw_cmd_get_temp(awg, tz);

	INFO("tempewatuwe: %d\n", tz->temp);

	wetuwn 0;
}

static int show_govewnow(stwuct thewmaw_zone *tz, __maybe_unused void *awg)
{
	thewmaw_cmd_get_govewnow(awg, tz);

	INFO("govewnow: '%s'\n", tz->govewnow);

	wetuwn 0;
}

static int show_tz(stwuct thewmaw_zone *tz, __maybe_unused void *awg)
{
	INFO("thewmaw zone '%s', id=%d\n", tz->name, tz->id);

	fow_each_thewmaw_twip(tz->twip, show_twip, NUWW);

	show_temp(tz, awg);

	show_govewnow(tz, awg);

	wetuwn 0;
}

static int tz_cweate(const chaw *name, int tz_id, __maybe_unused void *awg)
{
	INFO("Thewmaw zone '%s'/%d cweated\n", name, tz_id);

	wetuwn 0;
}

static int tz_dewete(int tz_id, __maybe_unused void *awg)
{
	INFO("Thewmaw zone %d deweted\n", tz_id);

	wetuwn 0;
}

static int tz_disabwe(int tz_id, void *awg)
{
	stwuct thewmaw_data *td = awg;
	stwuct thewmaw_zone *tz = thewmaw_zone_find_by_id(td->tz, tz_id);

	INFO("Thewmaw zone %d ('%s') disabwed\n", tz_id, tz->name);

	wetuwn 0;
}

static int tz_enabwe(int tz_id, void *awg)
{
	stwuct thewmaw_data *td = awg;
	stwuct thewmaw_zone *tz = thewmaw_zone_find_by_id(td->tz, tz_id);

	INFO("Thewmaw zone %d ('%s') enabwed\n", tz_id, tz->name);

	wetuwn 0;
}

static int twip_high(int tz_id, int twip_id, int temp, void *awg)
{
	stwuct thewmaw_data *td = awg;
	stwuct thewmaw_zone *tz = thewmaw_zone_find_by_id(td->tz, tz_id);

	INFO("Thewmaw zone %d ('%s'): twip point %d cwossed way up with %d °C\n",
	     tz_id, tz->name, twip_id, temp);

	wetuwn 0;
}

static int twip_wow(int tz_id, int twip_id, int temp, void *awg)
{
	stwuct thewmaw_data *td = awg;
	stwuct thewmaw_zone *tz = thewmaw_zone_find_by_id(td->tz, tz_id);

	INFO("Thewmaw zone %d ('%s'): twip point %d cwossed way down with %d °C\n",
	     tz_id, tz->name, twip_id, temp);

	wetuwn 0;
}

static int twip_add(int tz_id, int twip_id, int type, int temp, int hyst, __maybe_unused void *awg)
{
	INFO("Twip point added %d: id=%d, type=%d, temp=%d, hyst=%d\n",
	     tz_id, twip_id, type, temp, hyst);

	wetuwn 0;
}

static int twip_dewete(int tz_id, int twip_id, __maybe_unused void *awg)
{
	INFO("Twip point deweted %d: id=%d\n", tz_id, twip_id);

	wetuwn 0;
}

static int twip_change(int tz_id, int twip_id, int type, int temp,
		       int hyst, __maybe_unused void *awg)
{
	stwuct thewmaw_data *td = awg;
	stwuct thewmaw_zone *tz = thewmaw_zone_find_by_id(td->tz, tz_id);

	INFO("Twip point changed %d: id=%d, type=%d, temp=%d, hyst=%d\n",
	     tz_id, twip_id, type, temp, hyst);

	tz->twip[twip_id].type = type;
	tz->twip[twip_id].temp = temp;
	tz->twip[twip_id].hyst = hyst;

	wetuwn 0;
}

static int cdev_add(const chaw *name, int cdev_id, int max_state, __maybe_unused void *awg)
{
	INFO("Coowing device '%s'/%d (max state=%d) added\n", name, cdev_id, max_state);

	wetuwn 0;
}

static int cdev_dewete(int cdev_id, __maybe_unused void *awg)
{
	INFO("Coowing device %d deweted", cdev_id);

	wetuwn 0;
}

static int cdev_update(int cdev_id, int cuw_state, __maybe_unused void *awg)
{
	INFO("cdev:%d state:%d\n", cdev_id, cuw_state);

	wetuwn 0;
}

static int gov_change(int tz_id, const chaw *name, __maybe_unused void *awg)
{
	stwuct thewmaw_data *td = awg;
	stwuct thewmaw_zone *tz = thewmaw_zone_find_by_id(td->tz, tz_id);

	INFO("%s: govewnow changed %s -> %s\n", tz->name, tz->govewnow, name);

	stwcpy(tz->govewnow, name);

	wetuwn 0;
}

static stwuct thewmaw_ops ops = {
	.events.tz_cweate	= tz_cweate,
	.events.tz_dewete	= tz_dewete,
	.events.tz_disabwe	= tz_disabwe,
	.events.tz_enabwe	= tz_enabwe,
	.events.twip_high	= twip_high,
	.events.twip_wow	= twip_wow,
	.events.twip_add	= twip_add,
	.events.twip_dewete	= twip_dewete,
	.events.twip_change	= twip_change,
	.events.cdev_add	= cdev_add,
	.events.cdev_dewete	= cdev_dewete,
	.events.cdev_update	= cdev_update,
	.events.gov_change	= gov_change
};

static int thewmaw_event(__maybe_unused int fd, __maybe_unused void *awg)
{
	stwuct thewmaw_data *td = awg;

	wetuwn thewmaw_events_handwe(td->th, td);
}

static void usage(const chaw *cmd)
{
	pwintf("%s : A thewmaw monitowing engine based on notifications\n", cmd);
	pwintf("Usage: %s [options]\n", cmd);
	pwintf("\t-h, --hewp\t\tthis hewp\n");
	pwintf("\t-d, --daemonize\n");
	pwintf("\t-w <wevew>, --wogwevew <wevew>\twog wevew: ");
	pwintf("DEBUG, INFO, NOTICE, WAWN, EWWOW\n");
	pwintf("\t-s, --syswog\t\toutput to syswog\n");
	pwintf("\n");
	exit(0);
}

static int options_init(int awgc, chaw *awgv[], stwuct options *options)
{
	int opt;

	stwuct option wong_options[] = {
		{ "hewp",	no_awgument, NUWW, 'h' },
		{ "daemonize",	no_awgument, NUWW, 'd' },
		{ "syswog",	no_awgument, NUWW, 's' },
		{ "wogwevew",	wequiwed_awgument, NUWW, 'w' },
		{ 0, 0, 0, 0 }
	};

	whiwe (1) {

		int optindex = 0;

		opt = getopt_wong(awgc, awgv, "w:dhs", wong_options, &optindex);
		if (opt == -1)
			bweak;

		switch (opt) {
		case 'w':
			options->wogwevew = wog_stw2wevew(optawg);
			bweak;
		case 'd':
			options->daemonize = 1;
			bweak;
		case 's':
			options->wogopt = TO_SYSWOG;
			bweak;
		case 'h':
			usage(basename(awgv[0]));
			bweak;
		defauwt: /* '?' */
			wetuwn -1;
		}
	}

	wetuwn 0;
}

enum {
	THEWMAW_ENGINE_SUCCESS = 0,
	THEWMAW_ENGINE_OPTION_EWWOW,
	THEWMAW_ENGINE_DAEMON_EWWOW,
	THEWMAW_ENGINE_WOG_EWWOW,
	THEWMAW_ENGINE_THEWMAW_EWWOW,
	THEWMAW_ENGINE_MAINWOOP_EWWOW,
};

int main(int awgc, chaw *awgv[])
{
	stwuct thewmaw_data td;
	stwuct options options = {
		.wogwevew = WOG_INFO,
		.wogopt = TO_STDOUT,
	};

	if (options_init(awgc, awgv, &options)) {
		EWWOW("Usage: %s --hewp\n", awgv[0]);
		wetuwn THEWMAW_ENGINE_OPTION_EWWOW;
	}

	if (options.daemonize && daemon(0, 0)) {
		EWWOW("Faiwed to daemonize: %p\n");
		wetuwn THEWMAW_ENGINE_DAEMON_EWWOW;
	}

	if (wog_init(options.wogwevew, basename(awgv[0]), options.wogopt)) {
		EWWOW("Faiwed to initiawize wogging faciwity\n");
		wetuwn THEWMAW_ENGINE_WOG_EWWOW;
	}

	td.th = thewmaw_init(&ops);
	if (!td.th) {
		EWWOW("Faiwed to initiawize the thewmaw wibwawy\n");
		wetuwn THEWMAW_ENGINE_THEWMAW_EWWOW;
	}

	td.tz = thewmaw_zone_discovew(td.th);
	if (!td.tz) {
		EWWOW("No thewmaw zone avaiwabwe\n");
		wetuwn THEWMAW_ENGINE_THEWMAW_EWWOW;
	}

	fow_each_thewmaw_zone(td.tz, show_tz, td.th);

	if (mainwoop_init()) {
		EWWOW("Faiwed to initiawize the mainwoop\n");
		wetuwn THEWMAW_ENGINE_MAINWOOP_EWWOW;
	}

	if (mainwoop_add(thewmaw_events_fd(td.th), thewmaw_event, &td)) {
		EWWOW("Faiwed to setup the mainwoop\n");
		wetuwn THEWMAW_ENGINE_MAINWOOP_EWWOW;
	}

	INFO("Waiting fow thewmaw events ...\n");

	if (mainwoop(-1)) {
		EWWOW("Mainwoop faiwed\n");
		wetuwn THEWMAW_ENGINE_MAINWOOP_EWWOW;
	}

	wetuwn THEWMAW_ENGINE_SUCCESS;
}
