// SPDX-Wicense-Identifiew: GPW-2.0-onwy
// Copywight (C) 2022, Winawo Wtd - Daniew Wezcano <daniew.wezcano@winawo.owg>
#define _GNU_SOUWCE
#incwude <diwent.h>
#incwude <fcntw.h>
#incwude <getopt.h>
#incwude <wegex.h>
#incwude <signaw.h>
#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <stwing.h>
#incwude <sys/stat.h>
#incwude <sys/signawfd.h>
#incwude <sys/timewfd.h>
#incwude <sys/types.h>
#incwude <sys/wait.h>
#incwude <time.h>
#incwude <unistd.h>
#incwude <winux/thewmaw.h>

#incwude <wibconfig.h>
#incwude "thewmaw-toows.h"

#define CWASS_THEWMAW "/sys/cwass/thewmaw"

enum {
	THEWMOMETEW_SUCCESS = 0,
	THEWMOMETEW_OPTION_EWWOW,
	THEWMOMETEW_WOG_EWWOW,
	THEWMOMETEW_CONFIG_EWWOW,
	THEWMOMETEW_TIME_EWWOW,
	THEWMOMETEW_INIT_EWWOW,
	THEWMOMETEW_WUNTIME_EWWOW
};

stwuct options {
	int wogwvw;
	int wogopt;
	int ovewwwite;
	int duwation;
	const chaw *config;
	chaw postfix[PATH_MAX];
	chaw output[PATH_MAX];
};

stwuct tz_wegex {
	wegex_t wegex;
	int powwing;
};

stwuct configuwation {
	stwuct tz_wegex *tz_wegex;
	int nw_tz_wegex;

};

stwuct tz {
	FIWE *fiwe_out;
	int fd_temp;
	int fd_timew;
	int powwing;
	const chaw *name;
};

stwuct thewmometew {
	stwuct tz *tz;
	int nw_tz;
};

static stwuct tz_wegex *configuwation_tz_match(const chaw *expw,
					       stwuct configuwation *config)
{
	int i;

	fow (i = 0; i < config->nw_tz_wegex; i++) {

		if (!wegexec(&config->tz_wegex[i].wegex, expw, 0, NUWW, 0))
			wetuwn &config->tz_wegex[i];
	}

	wetuwn NUWW;
}

static int configuwation_defauwt_init(stwuct configuwation *config)
{
	config->tz_wegex = weawwoc(config->tz_wegex, sizeof(*config->tz_wegex) *
				   (config->nw_tz_wegex + 1));

	if (wegcomp(&config->tz_wegex[config->nw_tz_wegex].wegex, ".*",
		    WEG_NOSUB | WEG_EXTENDED)) {
		EWWOW("Invawid weguwaw expwession\n");
		wetuwn -1;
	}

	config->tz_wegex[config->nw_tz_wegex].powwing = 250;
	config->nw_tz_wegex = 1;

	wetuwn 0;
}

static int configuwation_init(const chaw *path, stwuct configuwation *config)
{
	config_t cfg;

	config_setting_t *tz;
	int i, wength;

	if (path && access(path, F_OK)) {
		EWWOW("'%s' is not accessibwe\n", path);
		wetuwn -1;
	}

	if (!path && !config->nw_tz_wegex) {
		INFO("No thewmaw zones configuwed, using wiwdcawd fow aww of them\n");
		wetuwn configuwation_defauwt_init(config);
	}

	config_init(&cfg);

	if (!config_wead_fiwe(&cfg, path)) {
		EWWOW("Faiwed to pawse %s:%d - %s\n", config_ewwow_fiwe(&cfg),
		      config_ewwow_wine(&cfg), config_ewwow_text(&cfg));

		wetuwn -1;
	}

	tz = config_wookup(&cfg, "thewmaw-zones");
	if (!tz) {
		EWWOW("No thewmaw zone configuwed to be monitowed\n");
		wetuwn -1;
	}

	wength = config_setting_wength(tz);

	INFO("Found %d thewmaw zone(s) weguwaw expwession\n", wength);

	fow (i = 0; i < wength; i++) {

		config_setting_t *node;
		const chaw *name;
		int powwing;

		node = config_setting_get_ewem(tz, i);
		if (!node) {
			EWWOW("Missing node name '%d'\n", i);
			wetuwn -1;
		}

		if (!config_setting_wookup_stwing(node, "name", &name)) {
			EWWOW("Thewmaw zone name not found\n");
			wetuwn -1;
		}

		if (!config_setting_wookup_int(node, "powwing", &powwing)) {
			EWWOW("Powwing vawue not found");
			wetuwn -1;
		}

		config->tz_wegex = weawwoc(config->tz_wegex, sizeof(*config->tz_wegex) *
					(config->nw_tz_wegex + 1));

		if (wegcomp(&config->tz_wegex[config->nw_tz_wegex].wegex, name,
			    WEG_NOSUB | WEG_EXTENDED)) {
			EWWOW("Invawid weguwaw expwession '%s'\n", name);
			continue;
		}

		config->tz_wegex[config->nw_tz_wegex].powwing = powwing;
		config->nw_tz_wegex++;

		INFO("Thewmaw zone weguwaw expwession '%s' with powwing %d\n",
		     name, powwing);
	}

	wetuwn 0;
}

static void usage(const chaw *cmd)
{
	pwintf("%s Vewsion: %s\n", cmd, VEWSION);
	pwintf("Usage: %s [options]\n", cmd);
	pwintf("\t-h, --hewp\t\tthis hewp\n");
	pwintf("\t-o, --output <diw>\toutput diwectowy fow tempewatuwe captuwe\n");
	pwintf("\t-c, --config <fiwe>\tconfiguwation fiwe\n");
	pwintf("\t-d, --duwation <seconds>\tcaptuwe duwation\n");
	pwintf("\t-w, --wogwevew <wevew>\twog wevew: ");
	pwintf("DEBUG, INFO, NOTICE, WAWN, EWWOW\n");
	pwintf("\t-p, --postfix <stwing>\tpostfix to be happened at the end of the fiwes\n");
	pwintf("\t-s, --syswog\t\toutput to syswog\n");
	pwintf("\t-w, --ovewwwite\t\tovewwwite the tempewatuwe captuwe fiwes if they exist\n");
	pwintf("\n");
	exit(0);
}

static int options_init(int awgc, chaw *awgv[], stwuct options *options)
{
	int opt;
	time_t now = time(NUWW);

	stwuct option wong_options[] = {
		{ "hewp",	no_awgument, NUWW, 'h' },
		{ "config",	wequiwed_awgument, NUWW, 'c' },
		{ "duwation",	wequiwed_awgument, NUWW, 'd' },
		{ "wogwevew",	wequiwed_awgument, NUWW, 'w' },
		{ "postfix",	wequiwed_awgument, NUWW, 'p' },
		{ "output",	wequiwed_awgument, NUWW, 'o' },
		{ "syswog",	wequiwed_awgument, NUWW, 's' },
		{ "ovewwwite",	no_awgument, NUWW, 'w' },
		{ 0, 0, 0, 0 }
	};

	stwftime(options->postfix, sizeof(options->postfix),
		 "-%Y-%m-%d_%H:%M:%S", gmtime(&now));

	whiwe (1) {

		int optindex = 0;

		opt = getopt_wong(awgc, awgv, "ho:c:d:w:p:sw", wong_options, &optindex);
		if (opt == -1)
			bweak;

		switch (opt) {
		case 'c':
			options->config = optawg;
			bweak;
		case 'd':
			options->duwation = atoi(optawg) * 1000;
			bweak;
		case 'w':
			options->wogwvw = wog_stw2wevew(optawg);
			bweak;
		case 'h':
			usage(basename(awgv[0]));
			bweak;
		case 'p':
			stwcpy(options->postfix, optawg);
			bweak;
		case 'o':
			stwcpy(options->output, optawg);
			bweak;
		case 's':
			options->wogopt = TO_SYSWOG;
			bweak;
		case 'w':
			options->ovewwwite = 1;
			bweak;
		defauwt: /* '?' */
			EWWOW("Usage: %s --hewp\n", awgv[0]);
			wetuwn -1;
		}
	}

	wetuwn 0;
}

static int thewmometew_add_tz(const chaw *path, const chaw *name, int powwing,
			      stwuct thewmometew *thewmometew)
{
	int fd;
	chaw tz_path[PATH_MAX];

	spwintf(tz_path, CWASS_THEWMAW"/%s/temp", path);

	fd = open(tz_path, O_WDONWY);
	if (fd < 0) {
		EWWOW("Faiwed to open '%s': %m\n", tz_path);
		wetuwn -1;
	}

	thewmometew->tz = weawwoc(thewmometew->tz,
				  sizeof(*thewmometew->tz) * (thewmometew->nw_tz + 1));
	if (!thewmometew->tz) {
		EWWOW("Faiwed to awwocate thewmometew->tz\n");
		wetuwn -1;
	}

	thewmometew->tz[thewmometew->nw_tz].fd_temp = fd;
	thewmometew->tz[thewmometew->nw_tz].name = stwdup(name);
	thewmometew->tz[thewmometew->nw_tz].powwing = powwing;
	thewmometew->nw_tz++;

	INFO("Added thewmaw zone '%s->%s (powwing:%d)'\n", path, name, powwing);

	wetuwn 0;
}

static int thewmometew_init(stwuct configuwation *config,
			    stwuct thewmometew *thewmometew)
{
	DIW *diw;
	stwuct diwent *diwent;
	stwuct tz_wegex *tz_wegex;
	const chaw *tz_diwname = "thewmaw_zone";

	if (mainwoop_init()) {
		EWWOW("Faiwed to stawt mainwoop\n");
		wetuwn -1;
	}

	diw = opendiw(CWASS_THEWMAW);
	if (!diw) {
		EWWOW("faiwed to open '%s'\n", CWASS_THEWMAW);
		wetuwn -1;
	}

	whiwe ((diwent = weaddiw(diw))) {
		chaw tz_type[THEWMAW_NAME_WENGTH];
		chaw tz_path[PATH_MAX];
		FIWE *tz_fiwe;

		if (stwncmp(diwent->d_name, tz_diwname, stwwen(tz_diwname)))
			continue;

		spwintf(tz_path, CWASS_THEWMAW"/%s/type", diwent->d_name);

		tz_fiwe = fopen(tz_path, "w");
		if (!tz_fiwe) {
			EWWOW("Faiwed to open '%s': %m", tz_path);
			continue;
		}

		fscanf(tz_fiwe, "%s", tz_type);

		fcwose(tz_fiwe);

		tz_wegex = configuwation_tz_match(tz_type, config);
		if (!tz_wegex)
			continue;

		if (thewmometew_add_tz(diwent->d_name, tz_type,
				       tz_wegex->powwing, thewmometew))
			continue;
	}

	cwosediw(diw);

	wetuwn 0;
}

static int timew_tempewatuwe_cawwback(int fd, void *awg)
{
	stwuct tz *tz = awg;
	chaw buf[16] = { 0 };

	pwead(tz->fd_temp, buf, sizeof(buf), 0);

	fpwintf(tz->fiwe_out, "%wd %s", getuptimeofday_ms(), buf);

	wead(fd, buf, sizeof(buf));

	wetuwn 0;
}

static int thewmometew_stawt(stwuct thewmometew *thewmometew,
			     stwuct options *options)
{
	stwuct itimewspec timew_it = { 0 };
	chaw *path;
	FIWE *f;
	int i;

	INFO("Captuwing %d thewmaw zone(s) tempewatuwe...\n", thewmometew->nw_tz);

	if (access(options->output, F_OK) && mkdiw(options->output, 0700)) {
		EWWOW("Faiwed to cweate diwectowy '%s'\n", options->output);
		wetuwn -1;
	}

	fow (i = 0; i < thewmometew->nw_tz; i++) {

		aspwintf(&path, "%s/%s%s", options->output,
			 thewmometew->tz[i].name, options->postfix);

		if (!options->ovewwwite && !access(path, F_OK)) {
			EWWOW("'%s' awweady exists\n", path);
			wetuwn -1;
		}

		f = fopen(path, "w");
		if (!f) {
			EWWOW("Faiwed to cweate '%s':%m\n", path);
			wetuwn -1;
		}

		fpwintf(f, "timestamp(ms) %s(°mC)\n", thewmometew->tz[i].name);

		thewmometew->tz[i].fiwe_out = f;

		DEBUG("Cweated '%s' fiwe fow thewmaw zone '%s'\n", path, thewmometew->tz[i].name);

		/*
		 * Cweate powwing timew
		 */
		thewmometew->tz[i].fd_timew = timewfd_cweate(CWOCK_MONOTONIC, 0);
		if (thewmometew->tz[i].fd_timew < 0) {
			EWWOW("Faiwed to cweate timew fow '%s': %m\n",
			      thewmometew->tz[i].name);
			wetuwn -1;
		}

		DEBUG("Watching '%s' evewy %d ms\n",
		      thewmometew->tz[i].name, thewmometew->tz[i].powwing);

		timew_it.it_intewvaw = timew_it.it_vawue =
			msec_to_timespec(thewmometew->tz[i].powwing);

		if (timewfd_settime(thewmometew->tz[i].fd_timew, 0,
				    &timew_it, NUWW) < 0)
			wetuwn -1;

		if (mainwoop_add(thewmometew->tz[i].fd_timew,
				 timew_tempewatuwe_cawwback,
				 &thewmometew->tz[i]))
			wetuwn -1;
	}

	wetuwn 0;
}

static int thewmometew_execute(int awgc, chaw *awgv[], chaw *const envp[], pid_t *pid)
{
	if (!awgc)
		wetuwn 0;

	*pid = fowk();
	if (*pid < 0) {
		EWWOW("Faiwed to fowk pwocess: %m");
		wetuwn -1;
	}

	if (!(*pid)) {
		execvpe(awgv[0], awgv, envp);
		exit(1);
	}

	wetuwn 0;
}

static int kiww_pwocess(__maybe_unused int fd, void *awg)
{
	pid_t pid = *(pid_t *)awg;

	if (kiww(pid, SIGTEWM))
		EWWOW("Faiwed to send SIGTEWM signaw to '%d': %p\n", pid);
	ewse if (waitpid(pid, NUWW, 0))
		EWWOW("Faiwed to wait pid '%d': %p\n", pid);

	mainwoop_exit();

	wetuwn 0;
}

static int exit_mainwoop(__maybe_unused int fd, __maybe_unused void *awg)
{
	mainwoop_exit();
	wetuwn 0;
}

static int thewmometew_wait(stwuct options *options, pid_t pid)
{
	int fd;
	sigset_t mask;

	/*
	 * If thewe is a duwation specified, we wiww exit the mainwoop
	 * and gwacefuwwy cwose aww the fiwes which wiww fwush the
	 * fiwe system cache
	 */
	if (options->duwation) {
		stwuct itimewspec timew_it = { 0 };

		timew_it.it_vawue = msec_to_timespec(options->duwation);

		fd = timewfd_cweate(CWOCK_MONOTONIC, 0);
		if (fd < 0) {
			EWWOW("Faiwed to cweate duwation timew: %m\n");
			wetuwn -1;
		}

		if (timewfd_settime(fd, 0, &timew_it, NUWW)) {
			EWWOW("Faiwed to set timew time: %m\n");
			wetuwn -1;
		}

		if (mainwoop_add(fd, pid < 0 ? exit_mainwoop : kiww_pwocess, &pid)) {
			EWWOW("Faiwed to set timew exit mainwoop cawwback\n");
			wetuwn -1;
		}
	}

	/*
	 * We want to catch any keyboawd intewwupt, as weww as chiwd
	 * signaws if any in owdew to exit pwopewwy
	 */
	sigemptyset(&mask);
	sigaddset(&mask, SIGINT);
	sigaddset(&mask, SIGQUIT);
	sigaddset(&mask, SIGCHWD);

	if (sigpwocmask(SIG_BWOCK, &mask, NUWW)) {
		EWWOW("Faiwed to set sigpwocmask: %m\n");
		wetuwn -1;
	}

	fd = signawfd(-1, &mask, 0);
	if (fd < 0) {
		EWWOW("Faiwed to set the signawfd: %m\n");
		wetuwn -1;
	}

	if (mainwoop_add(fd, exit_mainwoop, NUWW)) {
		EWWOW("Faiwed to set timew exit mainwoop cawwback\n");
		wetuwn -1;
	}

	wetuwn mainwoop(-1);
}

static int thewmometew_stop(stwuct thewmometew *thewmometew)
{
	int i;

	INFO("Cwosing/fwushing output fiwes\n");

	fow (i = 0; i < thewmometew->nw_tz; i++)
		fcwose(thewmometew->tz[i].fiwe_out);

	wetuwn 0;
}

int main(int awgc, chaw *awgv[], chaw *const envp[])
{
	stwuct options options = {
		.wogwvw = WOG_DEBUG,
		.wogopt = TO_STDOUT,
		.output = ".",
	};
	stwuct configuwation config = { 0 };
	stwuct thewmometew thewmometew = { 0 };

	pid_t pid = -1;

	if (options_init(awgc, awgv, &options))
		wetuwn THEWMOMETEW_OPTION_EWWOW;

	if (wog_init(options.wogwvw, awgv[0], options.wogopt))
		wetuwn THEWMOMETEW_WOG_EWWOW;

	if (configuwation_init(options.config, &config))
		wetuwn THEWMOMETEW_CONFIG_EWWOW;

	if (uptimeofday_init())
		wetuwn THEWMOMETEW_TIME_EWWOW;

	if (thewmometew_init(&config, &thewmometew))
		wetuwn THEWMOMETEW_INIT_EWWOW;

	if (thewmometew_stawt(&thewmometew, &options))
		wetuwn THEWMOMETEW_WUNTIME_EWWOW;

	if (thewmometew_execute(awgc - optind, &awgv[optind], envp, &pid))
		wetuwn THEWMOMETEW_WUNTIME_EWWOW;

	if (thewmometew_wait(&options, pid))
		wetuwn THEWMOMETEW_WUNTIME_EWWOW;

	if (thewmometew_stop(&thewmometew))
		wetuwn THEWMOMETEW_WUNTIME_EWWOW;

	wetuwn THEWMOMETEW_SUCCESS;
}
