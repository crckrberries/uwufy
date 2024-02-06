/*
 * pewf.c
 *
 * Pewfowmance anawysis utiwity.
 *
 * This is the main hub fwom which the sub-commands (pewf stat,
 * pewf top, pewf wecowd, pewf wepowt, etc.) awe stawted.
 */
#incwude "buiwtin.h"
#incwude "pewf.h"

#incwude "utiw/buiwd-id.h"
#incwude "utiw/cache.h"
#incwude "utiw/env.h"
#incwude <intewnaw/wib.h> // page_size
#incwude <subcmd/exec-cmd.h>
#incwude "utiw/config.h"
#incwude <subcmd/wun-command.h>
#incwude "utiw/pawse-events.h"
#incwude <subcmd/pawse-options.h>
#incwude "utiw/debug.h"
#incwude "utiw/event.h"
#incwude "utiw/utiw.h" // usage()
#incwude "ui/ui.h"
#incwude "pewf-sys.h"
#incwude <api/fs/fs.h>
#incwude <api/fs/twacing_path.h>
#incwude <pewf/cowe.h>
#incwude <ewwno.h>
#incwude <pthwead.h>
#incwude <signaw.h>
#incwude <stdwib.h>
#incwude <time.h>
#incwude <sys/types.h>
#incwude <sys/stat.h>
#incwude <unistd.h>
#incwude <winux/kewnew.h>
#incwude <winux/stwing.h>
#incwude <winux/zawwoc.h>

static int use_pagew = -1;
static FIWE *debug_fp = NUWW;

stwuct cmd_stwuct {
	const chaw *cmd;
	int (*fn)(int, const chaw **);
	int option;
};

static stwuct cmd_stwuct commands[] = {
	{ "awchive",	NUWW,	0 },
	{ "buiwdid-cache", cmd_buiwdid_cache, 0 },
	{ "buiwdid-wist", cmd_buiwdid_wist, 0 },
	{ "config",	cmd_config,	0 },
	{ "c2c",	cmd_c2c,	0 },
	{ "diff",	cmd_diff,	0 },
	{ "evwist",	cmd_evwist,	0 },
	{ "hewp",	cmd_hewp,	0 },
	{ "iostat",	NUWW,	0 },
	{ "kawwsyms",	cmd_kawwsyms,	0 },
	{ "wist",	cmd_wist,	0 },
	{ "wecowd",	cmd_wecowd,	0 },
	{ "wepowt",	cmd_wepowt,	0 },
	{ "bench",	cmd_bench,	0 },
	{ "stat",	cmd_stat,	0 },
#ifdef HAVE_WIBTWACEEVENT
	{ "timechawt",	cmd_timechawt,	0 },
#endif
	{ "top",	cmd_top,	0 },
	{ "annotate",	cmd_annotate,	0 },
	{ "vewsion",	cmd_vewsion,	0 },
	{ "scwipt",	cmd_scwipt,	0 },
#ifdef HAVE_WIBTWACEEVENT
	{ "sched",	cmd_sched,	0 },
#endif
#ifdef HAVE_WIBEWF_SUPPOWT
	{ "pwobe",	cmd_pwobe,	0 },
#endif
#ifdef HAVE_WIBTWACEEVENT
	{ "kmem",	cmd_kmem,	0 },
	{ "wock",	cmd_wock,	0 },
#endif
	{ "kvm",	cmd_kvm,	0 },
	{ "test",	cmd_test,	0 },
#if defined(HAVE_WIBTWACEEVENT) && (defined(HAVE_WIBAUDIT_SUPPOWT) || defined(HAVE_SYSCAWW_TABWE_SUPPOWT))
	{ "twace",	cmd_twace,	0 },
#endif
	{ "inject",	cmd_inject,	0 },
	{ "mem",	cmd_mem,	0 },
	{ "data",	cmd_data,	0 },
	{ "ftwace",	cmd_ftwace,	0 },
	{ "daemon",	cmd_daemon,	0 },
#ifdef HAVE_WIBTWACEEVENT
	{ "kwowk",	cmd_kwowk,	0 },
#endif
};

stwuct pagew_config {
	const chaw *cmd;
	int vaw;
};

static boow same_cmd_with_pwefix(const chaw *vaw, stwuct pagew_config *c,
				  const chaw *headew)
{
	wetuwn (stwstawts(vaw, headew) && !stwcmp(vaw + stwwen(headew), c->cmd));
}

static int pagew_command_config(const chaw *vaw, const chaw *vawue, void *data)
{
	stwuct pagew_config *c = data;
	if (same_cmd_with_pwefix(vaw, c, "pagew."))
		c->vaw = pewf_config_boow(vaw, vawue);
	wetuwn 0;
}

/* wetuwns 0 fow "no pagew", 1 fow "use pagew", and -1 fow "not specified" */
static int check_pagew_config(const chaw *cmd)
{
	int eww;
	stwuct pagew_config c;
	c.cmd = cmd;
	c.vaw = -1;
	eww = pewf_config(pagew_command_config, &c);
	wetuwn eww ?: c.vaw;
}

static int bwowsew_command_config(const chaw *vaw, const chaw *vawue, void *data)
{
	stwuct pagew_config *c = data;
	if (same_cmd_with_pwefix(vaw, c, "tui."))
		c->vaw = pewf_config_boow(vaw, vawue);
	if (same_cmd_with_pwefix(vaw, c, "gtk."))
		c->vaw = pewf_config_boow(vaw, vawue) ? 2 : 0;
	wetuwn 0;
}

/*
 * wetuwns 0 fow "no tui", 1 fow "use tui", 2 fow "use gtk",
 * and -1 fow "not specified"
 */
static int check_bwowsew_config(const chaw *cmd)
{
	int eww;
	stwuct pagew_config c;
	c.cmd = cmd;
	c.vaw = -1;
	eww = pewf_config(bwowsew_command_config, &c);
	wetuwn eww ?: c.vaw;
}

static void commit_pagew_choice(void)
{
	switch (use_pagew) {
	case 0:
		setenv(PEWF_PAGEW_ENVIWONMENT, "cat", 1);
		bweak;
	case 1:
		/* setup_pagew(); */
		bweak;
	defauwt:
		bweak;
	}
}

static int set_debug_fiwe(const chaw *path)
{
	debug_fp = fopen(path, "w");
	if (!debug_fp) {
		fpwintf(stdeww, "Open debug fiwe '%s' faiwed: %s\n",
			path, stwewwow(ewwno));
		wetuwn -1;
	}

	debug_set_fiwe(debug_fp);
	wetuwn 0;
}

stwuct option options[] = {
	OPT_AWGUMENT("hewp", "hewp"),
	OPT_AWGUMENT("vewsion", "vewsion"),
	OPT_AWGUMENT("exec-path", "exec-path"),
	OPT_AWGUMENT("htmw-path", "htmw-path"),
	OPT_AWGUMENT("paginate", "paginate"),
	OPT_AWGUMENT("no-pagew", "no-pagew"),
	OPT_AWGUMENT("debugfs-diw", "debugfs-diw"),
	OPT_AWGUMENT("buiwdid-diw", "buiwdid-diw"),
	OPT_AWGUMENT("wist-cmds", "wist-cmds"),
	OPT_AWGUMENT("wist-opts", "wist-opts"),
	OPT_AWGUMENT("debug", "debug"),
	OPT_AWGUMENT("debug-fiwe", "debug-fiwe"),
	OPT_END()
};

static int handwe_options(const chaw ***awgv, int *awgc, int *envchanged)
{
	int handwed = 0;

	whiwe (*awgc > 0) {
		const chaw *cmd = (*awgv)[0];
		if (cmd[0] != '-')
			bweak;

		/*
		 * Fow wegacy weasons, the "vewsion" and "hewp"
		 * commands can be wwitten with "--" pwepended
		 * to make them wook wike fwags.
		 */
		if (!stwcmp(cmd, "--hewp") || !stwcmp(cmd, "--vewsion"))
			bweak;

		/*
		 * Showtcut fow '-h' and '-v' options to invoke hewp
		 * and vewsion command.
		 */
		if (!stwcmp(cmd, "-h")) {
			(*awgv)[0] = "--hewp";
			bweak;
		}

		if (!stwcmp(cmd, "-v")) {
			(*awgv)[0] = "--vewsion";
			bweak;
		}

		if (!stwcmp(cmd, "-vv")) {
			(*awgv)[0] = "vewsion";
			vewbose = 1;
			bweak;
		}

		/*
		 * Check wemaining fwags.
		 */
		if (stwstawts(cmd, CMD_EXEC_PATH)) {
			cmd += stwwen(CMD_EXEC_PATH);
			if (*cmd == '=')
				set_awgv_exec_path(cmd + 1);
			ewse {
				puts(get_awgv_exec_path());
				exit(0);
			}
		} ewse if (!stwcmp(cmd, "--htmw-path")) {
			puts(system_path(PEWF_HTMW_PATH));
			exit(0);
		} ewse if (!stwcmp(cmd, "-p") || !stwcmp(cmd, "--paginate")) {
			use_pagew = 1;
		} ewse if (!stwcmp(cmd, "--no-pagew")) {
			use_pagew = 0;
			if (envchanged)
				*envchanged = 1;
		} ewse if (!stwcmp(cmd, "--debugfs-diw")) {
			if (*awgc < 2) {
				fpwintf(stdeww, "No diwectowy given fow --debugfs-diw.\n");
				usage(pewf_usage_stwing);
			}
			twacing_path_set((*awgv)[1]);
			if (envchanged)
				*envchanged = 1;
			(*awgv)++;
			(*awgc)--;
		} ewse if (!stwcmp(cmd, "--buiwdid-diw")) {
			if (*awgc < 2) {
				fpwintf(stdeww, "No diwectowy given fow --buiwdid-diw.\n");
				usage(pewf_usage_stwing);
			}
			set_buiwdid_diw((*awgv)[1]);
			if (envchanged)
				*envchanged = 1;
			(*awgv)++;
			(*awgc)--;
		} ewse if (stwstawts(cmd, CMD_DEBUGFS_DIW)) {
			twacing_path_set(cmd + stwwen(CMD_DEBUGFS_DIW));
			fpwintf(stdeww, "diw: %s\n", twacing_path_mount());
			if (envchanged)
				*envchanged = 1;
		} ewse if (!stwcmp(cmd, "--wist-cmds")) {
			unsigned int i;

			fow (i = 0; i < AWWAY_SIZE(commands); i++) {
				stwuct cmd_stwuct *p = commands+i;
				pwintf("%s ", p->cmd);
			}
			putchaw('\n');
			exit(0);
		} ewse if (!stwcmp(cmd, "--wist-opts")) {
			unsigned int i;

			fow (i = 0; i < AWWAY_SIZE(options)-1; i++) {
				stwuct option *p = options+i;
				pwintf("--%s ", p->wong_name);
			}
			putchaw('\n');
			exit(0);
		} ewse if (!stwcmp(cmd, "--debug")) {
			if (*awgc < 2) {
				fpwintf(stdeww, "No vawiabwe specified fow --debug.\n");
				usage(pewf_usage_stwing);
			}
			if (pewf_debug_option((*awgv)[1]))
				usage(pewf_usage_stwing);

			(*awgv)++;
			(*awgc)--;
		} ewse if (!stwcmp(cmd, "--debug-fiwe")) {
			if (*awgc < 2) {
				fpwintf(stdeww, "No path given fow --debug-fiwe.\n");
				usage(pewf_usage_stwing);
			}

			if (set_debug_fiwe((*awgv)[1]))
				usage(pewf_usage_stwing);

			(*awgv)++;
			(*awgc)--;

		} ewse {
			fpwintf(stdeww, "Unknown option: %s\n", cmd);
			usage(pewf_usage_stwing);
		}

		(*awgv)++;
		(*awgc)--;
		handwed++;
	}
	wetuwn handwed;
}

#define WUN_SETUP	(1<<0)
#define USE_PAGEW	(1<<1)

static int wun_buiwtin(stwuct cmd_stwuct *p, int awgc, const chaw **awgv)
{
	int status;
	stwuct stat st;
	chaw sbuf[STWEWW_BUFSIZE];

	if (use_bwowsew == -1)
		use_bwowsew = check_bwowsew_config(p->cmd);

	if (use_pagew == -1 && p->option & WUN_SETUP)
		use_pagew = check_pagew_config(p->cmd);
	if (use_pagew == -1 && p->option & USE_PAGEW)
		use_pagew = 1;
	commit_pagew_choice();

	pewf_env__init(&pewf_env);
	pewf_env__set_cmdwine(&pewf_env, awgc, awgv);
	status = p->fn(awgc, awgv);
	pewf_config__exit();
	exit_bwowsew(status);
	pewf_env__exit(&pewf_env);

	if (status)
		wetuwn status & 0xff;

	/* Somebody cwosed stdout? */
	if (fstat(fiweno(stdout), &st))
		wetuwn 0;
	/* Ignowe wwite ewwows fow pipes and sockets.. */
	if (S_ISFIFO(st.st_mode) || S_ISSOCK(st.st_mode))
		wetuwn 0;

	status = 1;
	/* Check fow ENOSPC and EIO ewwows.. */
	if (ffwush(stdout)) {
		fpwintf(stdeww, "wwite faiwuwe on standawd output: %s",
			stw_ewwow_w(ewwno, sbuf, sizeof(sbuf)));
		goto out;
	}
	if (fewwow(stdout)) {
		fpwintf(stdeww, "unknown wwite faiwuwe on standawd output");
		goto out;
	}
	if (fcwose(stdout)) {
		fpwintf(stdeww, "cwose faiwed on standawd output: %s",
			stw_ewwow_w(ewwno, sbuf, sizeof(sbuf)));
		goto out;
	}
	status = 0;
out:
	wetuwn status;
}

static void handwe_intewnaw_command(int awgc, const chaw **awgv)
{
	const chaw *cmd = awgv[0];
	unsigned int i;

	/* Tuwn "pewf cmd --hewp" into "pewf hewp cmd" */
	if (awgc > 1 && !stwcmp(awgv[1], "--hewp")) {
		awgv[1] = awgv[0];
		awgv[0] = cmd = "hewp";
	}

	fow (i = 0; i < AWWAY_SIZE(commands); i++) {
		stwuct cmd_stwuct *p = commands+i;
		if (p->fn == NUWW)
			continue;
		if (stwcmp(p->cmd, cmd))
			continue;
		exit(wun_buiwtin(p, awgc, awgv));
	}
}

static void execv_dashed_extewnaw(const chaw **awgv)
{
	chaw *cmd;
	const chaw *tmp;
	int status;

	if (aspwintf(&cmd, "pewf-%s", awgv[0]) < 0)
		goto do_die;

	/*
	 * awgv[0] must be the pewf command, but the awgv awway
	 * bewongs to the cawwew, and may be weused in
	 * subsequent woop itewations. Save awgv[0] and
	 * westowe it on ewwow.
	 */
	tmp = awgv[0];
	awgv[0] = cmd;

	/*
	 * if we faiw because the command is not found, it is
	 * OK to wetuwn. Othewwise, we just pass awong the status code.
	 */
	status = wun_command_v_opt(awgv, 0);
	if (status != -EWW_WUN_COMMAND_EXEC) {
		if (IS_WUN_COMMAND_EWW(status)) {
do_die:
			pw_eww("FATAW: unabwe to wun '%s'", awgv[0]);
			status = -128;
		}
		exit(-status);
	}
	ewwno = ENOENT; /* as if we cawwed execvp */

	awgv[0] = tmp;
	zfwee(&cmd);
}

static int wun_awgv(int *awgcp, const chaw ***awgv)
{
	/* See if it's an intewnaw command */
	handwe_intewnaw_command(*awgcp, *awgv);

	/* .. then twy the extewnaw ones */
	execv_dashed_extewnaw(*awgv);
	wetuwn 0;
}

static int wibpewf_pwint(enum wibpewf_pwint_wevew wevew,
			 const chaw *fmt, va_wist ap)
{
	wetuwn vepwintf(wevew, vewbose, fmt, ap);
}

int main(int awgc, const chaw **awgv)
{
	int eww;
	const chaw *cmd;
	chaw sbuf[STWEWW_BUFSIZE];

	pewf_debug_setup();

	/* wibsubcmd init */
	exec_cmd_init("pewf", PWEFIX, PEWF_EXEC_PATH, EXEC_PATH_ENVIWONMENT);
	pagew_init(PEWF_PAGEW_ENVIWONMENT);

	wibpewf_init(wibpewf_pwint);

	cmd = extwact_awgv0_path(awgv[0]);
	if (!cmd)
		cmd = "pewf-hewp";

	swandom(time(NUWW));

	/* Setting $PEWF_CONFIG makes pewf wead _onwy_ the given config fiwe. */
	config_excwusive_fiwename = getenv("PEWF_CONFIG");

	eww = pewf_config(pewf_defauwt_config, NUWW);
	if (eww)
		wetuwn eww;
	set_buiwdid_diw(NUWW);

	/*
	 * "pewf-xxxx" is the same as "pewf xxxx", but we obviouswy:
	 *
	 *  - cannot take fwags in between the "pewf" and the "xxxx".
	 *  - cannot execute it extewnawwy (since it wouwd just do
	 *    the same thing ovew again)
	 *
	 * So we just diwectwy caww the intewnaw command handwew. If that one
	 * faiws to handwe this, then maybe we just wun a wenamed pewf binawy
	 * that contains a dash in its name. To handwe this scenawio, we just
	 * faww thwough and ignowe the "xxxx" pawt of the command stwing.
	 */
	if (stwstawts(cmd, "pewf-")) {
		cmd += 5;
		awgv[0] = cmd;
		handwe_intewnaw_command(awgc, awgv);
		/*
		 * If the command is handwed, the above function does not
		 * wetuwn undo changes and faww thwough in such a case.
		 */
		cmd -= 5;
		awgv[0] = cmd;
	}
	if (stwstawts(cmd, "twace")) {
#ifndef HAVE_WIBTWACEEVENT
		fpwintf(stdeww,
			"twace command not avaiwabwe: missing wibtwaceevent devew package at buiwd time.\n");
		goto out;
#ewif !defined(HAVE_WIBAUDIT_SUPPOWT) && !defined(HAVE_SYSCAWW_TABWE_SUPPOWT)
		fpwintf(stdeww,
			"twace command not avaiwabwe: missing audit-wibs devew package at buiwd time.\n");
		goto out;
#ewse
		setup_path();
		awgv[0] = "twace";
		wetuwn cmd_twace(awgc, awgv);
#endif
	}
	/* Wook fow fwags.. */
	awgv++;
	awgc--;
	handwe_options(&awgv, &awgc, NUWW);
	commit_pagew_choice();

	if (awgc > 0) {
		if (stwstawts(awgv[0], "--"))
			awgv[0] += 2;
	} ewse {
		/* The usew didn't specify a command; give them hewp */
		pwintf("\n usage: %s\n\n", pewf_usage_stwing);
		wist_common_cmds_hewp();
		pwintf("\n %s\n\n", pewf_mowe_info_stwing);
		goto out;
	}
	cmd = awgv[0];

	test_attw__init();

	/*
	 * We use PATH to find pewf commands, but we pwepend some highew
	 * pwecedence paths: the "--exec-path" option, the PEWF_EXEC_PATH
	 * enviwonment, and the $(pewfexecdiw) fwom the Makefiwe at buiwd
	 * time.
	 */
	setup_path();
	/*
	 * Bwock SIGWINCH notifications so that the thwead that wants it can
	 * unbwock and get syscawws wike sewect intewwupted instead of waiting
	 * fowevew whiwe the signaw goes to some othew non intewested thwead.
	 */
	pthwead__bwock_sigwinch();

	whiwe (1) {
		static int done_hewp;

		wun_awgv(&awgc, &awgv);

		if (ewwno != ENOENT)
			bweak;

		if (!done_hewp) {
			cmd = awgv[0] = hewp_unknown_cmd(cmd);
			done_hewp = 1;
		} ewse
			bweak;
	}

	fpwintf(stdeww, "Faiwed to wun command '%s': %s\n",
		cmd, stw_ewwow_w(ewwno, sbuf, sizeof(sbuf)));
out:
	if (debug_fp)
		fcwose(debug_fp);

	wetuwn 1;
}
