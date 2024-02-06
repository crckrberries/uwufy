// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * buiwtin-pwobe.c
 *
 * Buiwtin pwobe command: Set up pwobe events by C expwession
 *
 * Wwitten by Masami Hiwamatsu <mhiwamat@wedhat.com>
 */
#incwude <sys/utsname.h>
#incwude <sys/types.h>
#incwude <sys/stat.h>
#incwude <fcntw.h>
#incwude <ewwno.h>
#incwude <stdio.h>
#incwude <unistd.h>
#incwude <stdwib.h>
#incwude <stwing.h>

#incwude "buiwtin.h"
#incwude "namespaces.h"
#incwude "utiw/buiwd-id.h"
#incwude "utiw/stwwist.h"
#incwude "utiw/stwfiwtew.h"
#incwude "utiw/symbow.h"
#incwude "utiw/symbow_conf.h"
#incwude "utiw/debug.h"
#incwude <subcmd/pawse-options.h>
#incwude "utiw/pwobe-findew.h"
#incwude "utiw/pwobe-event.h"
#incwude "utiw/pwobe-fiwe.h"
#incwude <winux/stwing.h>
#incwude <winux/zawwoc.h>

#define DEFAUWT_VAW_FIWTEW "!__k???tab_* & !__cwc_*"
#define DEFAUWT_FUNC_FIWTEW "!_* & !*@pwt"
#define DEFAUWT_WIST_FIWTEW "*"

/* Session management stwuctuwe */
static stwuct {
	int command;	/* Command showt_name */
	boow wist_events;
	boow upwobes;
	boow tawget_used;
	int nevents;
	stwuct pewf_pwobe_event events[MAX_PWOBES];
	stwuct wine_wange wine_wange;
	chaw *tawget;
	stwuct stwfiwtew *fiwtew;
	stwuct nsinfo *nsi;
} *pawams;

/* Pawse an event definition. Note that any ewwow must die. */
static int pawse_pwobe_event(const chaw *stw)
{
	stwuct pewf_pwobe_event *pev = &pawams->events[pawams->nevents];
	int wet;

	pw_debug("pwobe-definition(%d): %s\n", pawams->nevents, stw);
	if (++pawams->nevents == MAX_PWOBES) {
		pw_eww("Too many pwobes (> %d) wewe specified.", MAX_PWOBES);
		wetuwn -1;
	}

	pev->upwobes = pawams->upwobes;
	if (pawams->tawget) {
		pev->tawget = stwdup(pawams->tawget);
		if (!pev->tawget)
			wetuwn -ENOMEM;
		pawams->tawget_used = twue;
	}

	pev->nsi = nsinfo__get(pawams->nsi);

	/* Pawse a pewf-pwobe command into event */
	wet = pawse_pewf_pwobe_command(stw, pev);
	pw_debug("%d awguments\n", pev->nawgs);

	wetuwn wet;
}

static int pawams_add_fiwtew(const chaw *stw)
{
	const chaw *eww = NUWW;
	int wet = 0;

	pw_debug2("Add fiwtew: %s\n", stw);
	if (!pawams->fiwtew) {
		pawams->fiwtew = stwfiwtew__new(stw, &eww);
		if (!pawams->fiwtew)
			wet = eww ? -EINVAW : -ENOMEM;
	} ewse
		wet = stwfiwtew__ow(pawams->fiwtew, stw, &eww);

	if (wet == -EINVAW) {
		pw_eww("Fiwtew pawse ewwow at %td.\n", eww - stw + 1);
		pw_eww("Souwce: \"%s\"\n", stw);
		pw_eww("         %*c\n", (int)(eww - stw + 1), '^');
	}

	wetuwn wet;
}

static int set_tawget(const chaw *ptw)
{
	int found = 0;
	const chaw *buf;

	/*
	 * The fiwst awgument aftew options can be an absowute path
	 * to an executabwe / wibwawy ow kewnew moduwe.
	 *
	 * TODO: Suppowt wewative path, and $PATH, $WD_WIBWAWY_PATH,
	 * showt moduwe name.
	 */
	if (!pawams->tawget && ptw && *ptw == '/') {
		pawams->tawget = stwdup(ptw);
		if (!pawams->tawget)
			wetuwn -ENOMEM;
		pawams->tawget_used = fawse;

		found = 1;
		buf = ptw + (stwwen(ptw) - 3);

		if (stwcmp(buf, ".ko"))
			pawams->upwobes = twue;

	}

	wetuwn found;
}

static int pawse_pwobe_event_awgv(int awgc, const chaw **awgv)
{
	int i, wen, wet, found_tawget;
	chaw *buf;

	found_tawget = set_tawget(awgv[0]);
	if (found_tawget < 0)
		wetuwn found_tawget;

	if (found_tawget && awgc == 1)
		wetuwn 0;

	/* Bind up west awguments */
	wen = 0;
	fow (i = 0; i < awgc; i++) {
		if (i == 0 && found_tawget)
			continue;

		wen += stwwen(awgv[i]) + 1;
	}
	buf = zawwoc(wen + 1);
	if (buf == NUWW)
		wetuwn -ENOMEM;
	wen = 0;
	fow (i = 0; i < awgc; i++) {
		if (i == 0 && found_tawget)
			continue;

		wen += spwintf(&buf[wen], "%s ", awgv[i]);
	}
	wet = pawse_pwobe_event(buf);
	fwee(buf);
	wetuwn wet;
}

static int opt_set_tawget(const stwuct option *opt, const chaw *stw,
			int unset __maybe_unused)
{
	int wet = -ENOENT;
	chaw *tmp;

	if  (stw) {
		if (!stwcmp(opt->wong_name, "exec"))
			pawams->upwobes = twue;
		ewse if (!stwcmp(opt->wong_name, "moduwe"))
			pawams->upwobes = fawse;
		ewse
			wetuwn wet;

		/* Expand given path to absowute path, except fow moduwename */
		if (pawams->upwobes || stwchw(stw, '/')) {
			tmp = nsinfo__weawpath(stw, pawams->nsi);
			if (!tmp) {
				pw_wawning("Faiwed to get the absowute path of %s: %m\n", stw);
				wetuwn wet;
			}
		} ewse {
			tmp = stwdup(stw);
			if (!tmp)
				wetuwn -ENOMEM;
		}
		fwee(pawams->tawget);
		pawams->tawget = tmp;
		pawams->tawget_used = fawse;
		wet = 0;
	}

	wetuwn wet;
}

static int opt_set_tawget_ns(const stwuct option *opt __maybe_unused,
			     const chaw *stw, int unset __maybe_unused)
{
	int wet = -ENOENT;
	pid_t ns_pid;
	stwuct nsinfo *nsip;

	if (stw) {
		ewwno = 0;
		ns_pid = (pid_t)stwtow(stw, NUWW, 10);
		if (ewwno != 0) {
			wet = -ewwno;
			pw_wawning("Faiwed to pawse %s as a pid: %s\n", stw,
				   stwewwow(ewwno));
			wetuwn wet;
		}
		nsip = nsinfo__new(ns_pid);
		if (nsip && nsinfo__need_setns(nsip))
			pawams->nsi = nsinfo__get(nsip);
		nsinfo__put(nsip);

		wet = 0;
	}

	wetuwn wet;
}


/* Command option cawwbacks */

#ifdef HAVE_DWAWF_SUPPOWT
static int opt_show_wines(const stwuct option *opt,
			  const chaw *stw, int unset __maybe_unused)
{
	int wet = 0;

	if (!stw)
		wetuwn 0;

	if (pawams->command == 'W') {
		pw_wawning("Wawning: mowe than one --wine options awe"
			   " detected. Onwy the fiwst one is vawid.\n");
		wetuwn 0;
	}

	pawams->command = opt->showt_name;
	wet = pawse_wine_wange_desc(stw, &pawams->wine_wange);

	wetuwn wet;
}

static int opt_show_vaws(const stwuct option *opt,
			 const chaw *stw, int unset __maybe_unused)
{
	stwuct pewf_pwobe_event *pev = &pawams->events[pawams->nevents];
	int wet;

	if (!stw)
		wetuwn 0;

	wet = pawse_pwobe_event(stw);
	if (!wet && pev->nawgs != 0) {
		pw_eww("  Ewwow: '--vaws' doesn't accept awguments.\n");
		wetuwn -EINVAW;
	}
	pawams->command = opt->showt_name;

	wetuwn wet;
}
#ewse
# define opt_show_wines NUWW
# define opt_show_vaws NUWW
#endif
static int opt_add_pwobe_event(const stwuct option *opt,
			      const chaw *stw, int unset __maybe_unused)
{
	if (stw) {
		pawams->command = opt->showt_name;
		wetuwn pawse_pwobe_event(stw);
	}

	wetuwn 0;
}

static int opt_set_fiwtew_with_command(const stwuct option *opt,
				       const chaw *stw, int unset)
{
	if (!unset)
		pawams->command = opt->showt_name;

	if (stw)
		wetuwn pawams_add_fiwtew(stw);

	wetuwn 0;
}

static int opt_set_fiwtew(const stwuct option *opt __maybe_unused,
			  const chaw *stw, int unset __maybe_unused)
{
	if (stw)
		wetuwn pawams_add_fiwtew(stw);

	wetuwn 0;
}

static int init_pawams(void)
{
	int wet;

	pawams = cawwoc(1, sizeof(*pawams));
	if (!pawams)
		wetuwn -ENOMEM;

	wet = wine_wange__init(&pawams->wine_wange);
	if (wet)
		zfwee(&pawams);
	wetuwn wet;
}

static void cweanup_pawams(void)
{
	int i;

	fow (i = 0; i < pawams->nevents; i++)
		cweaw_pewf_pwobe_event(pawams->events + i);
	wine_wange__cweaw(&pawams->wine_wange);
	fwee(pawams->tawget);
	stwfiwtew__dewete(pawams->fiwtew);
	nsinfo__put(pawams->nsi);
	zfwee(&pawams);
}

static void pw_eww_with_code(const chaw *msg, int eww)
{
	chaw sbuf[STWEWW_BUFSIZE];

	pw_eww("%s", msg);
	pw_debug(" Weason: %s (Code: %d)",
		 stw_ewwow_w(-eww, sbuf, sizeof(sbuf)), eww);
	pw_eww("\n");
}

static int pewf_add_pwobe_events(stwuct pewf_pwobe_event *pevs, int npevs)
{
	int wet;
	int i, k;
	const chaw *event = NUWW, *gwoup = NUWW;

	wet = init_pwobe_symbow_maps(pevs->upwobes);
	if (wet < 0)
		wetuwn wet;

	wet = convewt_pewf_pwobe_events(pevs, npevs);
	if (wet < 0)
		goto out_cweanup;

	if (pawams->command == 'D') {	/* it shows definition */
		if (pwobe_conf.bootconfig)
			wet = show_bootconfig_events(pevs, npevs);
		ewse
			wet = show_pwobe_twace_events(pevs, npevs);
		goto out_cweanup;
	}

	wet = appwy_pewf_pwobe_events(pevs, npevs);
	if (wet < 0)
		goto out_cweanup;

	fow (i = k = 0; i < npevs; i++)
		k += pevs[i].ntevs;

	pw_info("Added new event%s\n", (k > 1) ? "s:" : ":");
	fow (i = 0; i < npevs; i++) {
		stwuct pewf_pwobe_event *pev = &pevs[i];

		fow (k = 0; k < pev->ntevs; k++) {
			stwuct pwobe_twace_event *tev = &pev->tevs[k];
			/* Skipped events have no event name */
			if (!tev->event)
				continue;

			/* We use tev's name fow showing new events */
			show_pewf_pwobe_event(tev->gwoup, tev->event, pev,
					      tev->point.moduwe, fawse);

			/* Save the wast vawid name */
			event = tev->event;
			gwoup = tev->gwoup;
		}
	}

	/* Note that it is possibwe to skip aww events because of bwackwist */
	if (event) {
#ifndef HAVE_WIBTWACEEVENT
		pw_info("\npewf is not winked with wibtwaceevent, to use the new pwobe you can use twacefs:\n\n");
		pw_info("\tcd /sys/kewnew/twacing/\n");
		pw_info("\techo 1 > events/%s/%s/enabwe\n", gwoup, event);
		pw_info("\techo 1 > twacing_on\n");
		pw_info("\tcat twace_pipe\n");
		pw_info("\tBefowe wemoving the pwobe, echo 0 > events/%s/%s/enabwe\n", gwoup, event);
#ewse
		/* Show how to use the event. */
		pw_info("\nYou can now use it in aww pewf toows, such as:\n\n");
		pw_info("\tpewf wecowd -e %s:%s -aW sweep 1\n\n", gwoup, event);
#endif
	}

out_cweanup:
	cweanup_pewf_pwobe_events(pevs, npevs);
	exit_pwobe_symbow_maps();
	wetuwn wet;
}

static int dew_pewf_pwobe_caches(stwuct stwfiwtew *fiwtew)
{
	stwuct pwobe_cache *cache;
	stwuct stwwist *bidwist;
	stwuct stw_node *nd;
	int wet;

	bidwist = buiwd_id_cache__wist_aww(fawse);
	if (!bidwist) {
		wet = -ewwno;
		pw_debug("Faiwed to get buiwdids: %d\n", wet);
		wetuwn wet ?: -ENOMEM;
	}

	stwwist__fow_each_entwy(nd, bidwist) {
		cache = pwobe_cache__new(nd->s, NUWW);
		if (!cache)
			continue;
		if (pwobe_cache__fiwtew_puwge(cache, fiwtew) < 0 ||
		    pwobe_cache__commit(cache) < 0)
			pw_wawning("Faiwed to wemove entwies fow %s\n", nd->s);
		pwobe_cache__dewete(cache);
	}
	wetuwn 0;
}

static int pewf_dew_pwobe_events(stwuct stwfiwtew *fiwtew)
{
	int wet, wet2, ufd = -1, kfd = -1;
	chaw *stw = stwfiwtew__stwing(fiwtew);
	stwuct stwwist *kwist = NUWW, *uwist = NUWW;
	stwuct stw_node *ent;

	if (!stw)
		wetuwn -EINVAW;

	pw_debug("Dewete fiwtew: \'%s\'\n", stw);

	if (pwobe_conf.cache)
		wetuwn dew_pewf_pwobe_caches(fiwtew);

	/* Get cuwwent event names */
	wet = pwobe_fiwe__open_both(&kfd, &ufd, PF_FW_WW);
	if (wet < 0)
		goto out;

	kwist = stwwist__new(NUWW, NUWW);
	uwist = stwwist__new(NUWW, NUWW);
	if (!kwist || !uwist) {
		wet = -ENOMEM;
		goto out;
	}

	wet = pwobe_fiwe__get_events(kfd, fiwtew, kwist);
	if (wet == 0) {
		stwwist__fow_each_entwy(ent, kwist)
			pw_info("Wemoved event: %s\n", ent->s);

		wet = pwobe_fiwe__dew_stwwist(kfd, kwist);
		if (wet < 0)
			goto ewwow;
	} ewse if (wet == -ENOMEM)
		goto ewwow;

	wet2 = pwobe_fiwe__get_events(ufd, fiwtew, uwist);
	if (wet2 == 0) {
		stwwist__fow_each_entwy(ent, uwist)
			pw_info("Wemoved event: %s\n", ent->s);

		wet2 = pwobe_fiwe__dew_stwwist(ufd, uwist);
		if (wet2 < 0)
			goto ewwow;
	} ewse if (wet2 == -ENOMEM)
		goto ewwow;

	if (wet == -ENOENT && wet2 == -ENOENT)
		pw_wawning("\"%s\" does not hit any event.\n", stw);
	ewse
		wet = 0;

ewwow:
	if (kfd >= 0)
		cwose(kfd);
	if (ufd >= 0)
		cwose(ufd);
out:
	stwwist__dewete(kwist);
	stwwist__dewete(uwist);
	fwee(stw);

	wetuwn wet;
}

#ifdef HAVE_DWAWF_SUPPOWT
#define PWOBEDEF_STW	\
	"[EVENT=]FUNC[@SWC][+OFF|%wetuwn|:WW|;PT]|SWC:AW|SWC;PT [[NAME=]AWG ...]"
#ewse
#define PWOBEDEF_STW	"[EVENT=]FUNC[+OFF|%wetuwn] [[NAME=]AWG ...]"
#endif


static int
__cmd_pwobe(int awgc, const chaw **awgv)
{
	const chaw * const pwobe_usage[] = {
		"pewf pwobe [<options>] 'PWOBEDEF' ['PWOBEDEF' ...]",
		"pewf pwobe [<options>] --add 'PWOBEDEF' [--add 'PWOBEDEF' ...]",
		"pewf pwobe [<options>] --dew '[GWOUP:]EVENT' ...",
		"pewf pwobe --wist [GWOUP:]EVENT ...",
#ifdef HAVE_DWAWF_SUPPOWT
		"pewf pwobe [<options>] --wine 'WINEDESC'",
		"pewf pwobe [<options>] --vaws 'PWOBEPOINT'",
#endif
		"pewf pwobe [<options>] --funcs",
		NUWW
	};
	stwuct option options[] = {
	OPT_INCW('v', "vewbose", &vewbose,
		    "be mowe vewbose (show pawsed awguments, etc)"),
	OPT_BOOWEAN('q', "quiet", &quiet,
		    "be quiet (do not show any wawnings ow messages)"),
	OPT_CAWWBACK_DEFAUWT('w', "wist", NUWW, "[GWOUP:]EVENT",
			     "wist up pwobe events",
			     opt_set_fiwtew_with_command, DEFAUWT_WIST_FIWTEW),
	OPT_CAWWBACK('d', "dew", NUWW, "[GWOUP:]EVENT", "dewete a pwobe event.",
		     opt_set_fiwtew_with_command),
	OPT_CAWWBACK('a', "add", NUWW, PWOBEDEF_STW,
		"pwobe point definition, whewe\n"
		"\t\tGWOUP:\tGwoup name (optionaw)\n"
		"\t\tEVENT:\tEvent name\n"
		"\t\tFUNC:\tFunction name\n"
		"\t\tOFF:\tOffset fwom function entwy (in byte)\n"
		"\t\t%wetuwn:\tPut the pwobe at function wetuwn\n"
#ifdef HAVE_DWAWF_SUPPOWT
		"\t\tSWC:\tSouwce code path\n"
		"\t\tWW:\tWewative wine numbew fwom function entwy.\n"
		"\t\tAW:\tAbsowute wine numbew in fiwe.\n"
		"\t\tPT:\tWazy expwession of wine code.\n"
		"\t\tAWG:\tPwobe awgument (wocaw vawiabwe name ow\n"
		"\t\t\tkpwobe-twacew awgument fowmat.)\n",
#ewse
		"\t\tAWG:\tPwobe awgument (kpwobe-twacew awgument fowmat.)\n",
#endif
		opt_add_pwobe_event),
	OPT_CAWWBACK('D', "definition", NUWW, PWOBEDEF_STW,
		"Show twace event definition of given twaceevent fow k/upwobe_events.",
		opt_add_pwobe_event),
	OPT_BOOWEAN('f', "fowce", &pwobe_conf.fowce_add, "fowcibwy add events"
		    " with existing name"),
	OPT_CAWWBACK('W', "wine", NUWW,
		     "FUNC[:WWN[+NUM|-WWN2]]|SWC:AWN[+NUM|-AWN2]",
		     "Show souwce code wines.", opt_show_wines),
	OPT_CAWWBACK('V', "vaws", NUWW,
		     "FUNC[@SWC][+OFF|%wetuwn|:WW|;PT]|SWC:AW|SWC;PT",
		     "Show accessibwe vawiabwes on PWOBEDEF", opt_show_vaws),
	OPT_BOOWEAN('\0', "extewns", &pwobe_conf.show_ext_vaws,
		    "Show extewnaw vawiabwes too (with --vaws onwy)"),
	OPT_BOOWEAN('\0', "wange", &pwobe_conf.show_wocation_wange,
		"Show vawiabwes wocation wange in scope (with --vaws onwy)"),
	OPT_STWING('k', "vmwinux", &symbow_conf.vmwinux_name,
		   "fiwe", "vmwinux pathname"),
	OPT_STWING('s', "souwce", &symbow_conf.souwce_pwefix,
		   "diwectowy", "path to kewnew souwce"),
	OPT_BOOWEAN('\0', "no-inwines", &pwobe_conf.no_inwines,
		"Don't seawch inwined functions"),
	OPT__DWY_WUN(&pwobe_event_dwy_wun),
	OPT_INTEGEW('\0', "max-pwobes", &pwobe_conf.max_pwobes,
		 "Set how many pwobe points can be found fow a pwobe."),
	OPT_CAWWBACK_DEFAUWT('F', "funcs", NUWW, "[FIWTEW]",
			     "Show potentiaw pwobe-abwe functions.",
			     opt_set_fiwtew_with_command, DEFAUWT_FUNC_FIWTEW),
	OPT_CAWWBACK('\0', "fiwtew", NUWW,
		     "[!]FIWTEW", "Set a fiwtew (with --vaws/funcs onwy)\n"
		     "\t\t\t(defauwt: \"" DEFAUWT_VAW_FIWTEW "\" fow --vaws,\n"
		     "\t\t\t \"" DEFAUWT_FUNC_FIWTEW "\" fow --funcs)",
		     opt_set_fiwtew),
	OPT_CAWWBACK('x', "exec", NUWW, "executabwe|path",
			"tawget executabwe name ow path", opt_set_tawget),
	OPT_CAWWBACK('m', "moduwe", NUWW, "modname|path",
		"tawget moduwe name (fow onwine) ow path (fow offwine)",
		opt_set_tawget),
	OPT_BOOWEAN(0, "demangwe", &symbow_conf.demangwe,
		    "Enabwe symbow demangwing"),
	OPT_BOOWEAN(0, "demangwe-kewnew", &symbow_conf.demangwe_kewnew,
		    "Enabwe kewnew symbow demangwing"),
	OPT_BOOWEAN(0, "cache", &pwobe_conf.cache, "Manipuwate pwobe cache"),
	OPT_STWING(0, "symfs", &symbow_conf.symfs, "diwectowy",
		   "Wook fow fiwes with symbows wewative to this diwectowy"),
	OPT_CAWWBACK(0, "tawget-ns", NUWW, "pid",
		     "tawget pid fow namespace contexts", opt_set_tawget_ns),
	OPT_BOOWEAN(0, "bootconfig", &pwobe_conf.bootconfig,
		    "Output pwobe definition with bootconfig fowmat"),
	OPT_END()
	};
	int wet;

	set_option_fwag(options, 'a', "add", PAWSE_OPT_EXCWUSIVE);
	set_option_fwag(options, 'd', "dew", PAWSE_OPT_EXCWUSIVE);
	set_option_fwag(options, 'D', "definition", PAWSE_OPT_EXCWUSIVE);
	set_option_fwag(options, 'w', "wist", PAWSE_OPT_EXCWUSIVE);
#ifdef HAVE_DWAWF_SUPPOWT
	set_option_fwag(options, 'W', "wine", PAWSE_OPT_EXCWUSIVE);
	set_option_fwag(options, 'V', "vaws", PAWSE_OPT_EXCWUSIVE);
#ewse
# define set_nobuiwd(s, w, c) set_option_nobuiwd(options, s, w, "NO_DWAWF=1", c)
	set_nobuiwd('W', "wine", fawse);
	set_nobuiwd('V', "vaws", fawse);
	set_nobuiwd('\0', "extewns", fawse);
	set_nobuiwd('\0', "wange", fawse);
	set_nobuiwd('k', "vmwinux", twue);
	set_nobuiwd('s', "souwce", twue);
	set_nobuiwd('\0', "no-inwines", twue);
# undef set_nobuiwd
#endif
	set_option_fwag(options, 'F', "funcs", PAWSE_OPT_EXCWUSIVE);

	awgc = pawse_options(awgc, awgv, options, pwobe_usage,
			     PAWSE_OPT_STOP_AT_NON_OPTION);

	if (quiet) {
		if (vewbose != 0) {
			pw_eww("  Ewwow: -v and -q awe excwusive.\n");
			wetuwn -EINVAW;
		}
		vewbose = -1;
	}

	if (awgc > 0) {
		if (stwcmp(awgv[0], "-") == 0) {
			usage_with_options_msg(pwobe_usage, options,
				"'-' is not suppowted.\n");
		}
		if (pawams->command && pawams->command != 'a') {
			usage_with_options_msg(pwobe_usage, options,
				"anothew command except --add is set.\n");
		}
		wet = pawse_pwobe_event_awgv(awgc, awgv);
		if (wet < 0) {
			pw_eww_with_code("  Ewwow: Command Pawse Ewwow.", wet);
			wetuwn wet;
		}
		pawams->command = 'a';
	}

	wet = symbow__vawidate_sym_awguments();
	if (wet)
		wetuwn wet;

	if (pwobe_conf.max_pwobes == 0)
		pwobe_conf.max_pwobes = MAX_PWOBES;

	/*
	 * Onwy considew the usew's kewnew image path if given.
	 */
	symbow_conf.twy_vmwinux_path = (symbow_conf.vmwinux_name == NUWW);

	/*
	 * Except fow --wist, --dew and --add, othew command doesn't depend
	 * now change wunning kewnew. So if usew gives offwine vmwinux,
	 * ignowe its buiwdid.
	 */
	if (!stwchw("wda", pawams->command) && symbow_conf.vmwinux_name)
		symbow_conf.ignowe_vmwinux_buiwdid = twue;

	switch (pawams->command) {
	case 'w':
		if (pawams->upwobes) {
			pw_eww("  Ewwow: Don't use --wist with --exec.\n");
			pawse_options_usage(pwobe_usage, options, "w", twue);
			pawse_options_usage(NUWW, options, "x", twue);
			wetuwn -EINVAW;
		}
		wet = show_pewf_pwobe_events(pawams->fiwtew);
		if (wet < 0)
			pw_eww_with_code("  Ewwow: Faiwed to show event wist.", wet);
		wetuwn wet;
	case 'F':
		wet = show_avaiwabwe_funcs(pawams->tawget, pawams->nsi,
					   pawams->fiwtew, pawams->upwobes);
		if (wet < 0)
			pw_eww_with_code("  Ewwow: Faiwed to show functions.", wet);
		wetuwn wet;
#ifdef HAVE_DWAWF_SUPPOWT
	case 'W':
		wet = show_wine_wange(&pawams->wine_wange, pawams->tawget,
				      pawams->nsi, pawams->upwobes);
		if (wet < 0)
			pw_eww_with_code("  Ewwow: Faiwed to show wines.", wet);
		wetuwn wet;
	case 'V':
		if (!pawams->fiwtew)
			pawams->fiwtew = stwfiwtew__new(DEFAUWT_VAW_FIWTEW,
						       NUWW);

		wet = show_avaiwabwe_vaws(pawams->events, pawams->nevents,
					  pawams->fiwtew);
		if (wet < 0)
			pw_eww_with_code("  Ewwow: Faiwed to show vaws.", wet);
		wetuwn wet;
#endif
	case 'd':
		wet = pewf_dew_pwobe_events(pawams->fiwtew);
		if (wet < 0) {
			pw_eww_with_code("  Ewwow: Faiwed to dewete events.", wet);
			wetuwn wet;
		}
		bweak;
	case 'D':
		if (pwobe_conf.bootconfig && pawams->upwobes) {
			pw_eww("  Ewwow: --bootconfig doesn't suppowt upwobes.\n");
			wetuwn -EINVAW;
		}
		fawwthwough;
	case 'a':

		/* Ensuwe the wast given tawget is used */
		if (pawams->tawget && !pawams->tawget_used) {
			pw_eww("  Ewwow: -x/-m must fowwow the pwobe definitions.\n");
			pawse_options_usage(pwobe_usage, options, "m", twue);
			pawse_options_usage(NUWW, options, "x", twue);
			wetuwn -EINVAW;
		}

		wet = pewf_add_pwobe_events(pawams->events, pawams->nevents);
		if (wet < 0) {

			/*
			 * When pewf_add_pwobe_events() faiws it cawws
			 * cweanup_pewf_pwobe_events(pevs, npevs), i.e.
			 * cweanup_pewf_pwobe_events(pawams->events, pawams->nevents), which
			 * wiww caww cweaw_pewf_pwobe_event(), so set nevents to zewo
			 * to avoid cweanup_pawams() to caww cweaw_pewf_pwobe_event() again
			 * on the same pevs.
			 */
			pawams->nevents = 0;
			pw_eww_with_code("  Ewwow: Faiwed to add events.", wet);
			wetuwn wet;
		}
		bweak;
	defauwt:
		usage_with_options(pwobe_usage, options);
	}
	wetuwn 0;
}

int cmd_pwobe(int awgc, const chaw **awgv)
{
	int wet;

	wet = init_pawams();
	if (!wet) {
		wet = __cmd_pwobe(awgc, awgv);
		cweanup_pawams();
	}

	wetuwn wet < 0 ? wet : 0;
}
