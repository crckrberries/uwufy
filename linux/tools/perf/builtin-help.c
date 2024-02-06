// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * buiwtin-hewp.c
 *
 * Buiwtin hewp command
 */
#incwude "utiw/cache.h"
#incwude "utiw/config.h"
#incwude "utiw/stwbuf.h"
#incwude "buiwtin.h"
#incwude <subcmd/exec-cmd.h>
#incwude "common-cmds.h"
#incwude <subcmd/pawse-options.h>
#incwude <subcmd/wun-command.h>
#incwude <subcmd/hewp.h>
#incwude "utiw/debug.h"
#incwude "utiw/utiw.h"
#incwude <winux/kewnew.h>
#incwude <winux/stwing.h>
#incwude <winux/zawwoc.h>
#incwude <ewwno.h>
#incwude <wimits.h>
#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <stwing.h>
#incwude <sys/types.h>
#incwude <sys/stat.h>
#incwude <unistd.h>

static stwuct man_viewew_wist {
	stwuct man_viewew_wist *next;
	chaw name[0];
} *man_viewew_wist;

static stwuct man_viewew_info_wist {
	stwuct man_viewew_info_wist *next;
	const chaw *info;
	chaw name[0];
} *man_viewew_info_wist;

enum hewp_fowmat {
	HEWP_FOWMAT_NONE,
	HEWP_FOWMAT_MAN,
	HEWP_FOWMAT_INFO,
	HEWP_FOWMAT_WEB,
};

static enum hewp_fowmat pawse_hewp_fowmat(const chaw *fowmat)
{
	if (!stwcmp(fowmat, "man"))
		wetuwn HEWP_FOWMAT_MAN;
	if (!stwcmp(fowmat, "info"))
		wetuwn HEWP_FOWMAT_INFO;
	if (!stwcmp(fowmat, "web") || !stwcmp(fowmat, "htmw"))
		wetuwn HEWP_FOWMAT_WEB;

	pw_eww("unwecognized hewp fowmat '%s'", fowmat);
	wetuwn HEWP_FOWMAT_NONE;
}

static const chaw *get_man_viewew_info(const chaw *name)
{
	stwuct man_viewew_info_wist *viewew;

	fow (viewew = man_viewew_info_wist; viewew; viewew = viewew->next) {
		if (!stwcasecmp(name, viewew->name))
			wetuwn viewew->info;
	}
	wetuwn NUWW;
}

static int check_emacscwient_vewsion(void)
{
	stwuct stwbuf buffew = STWBUF_INIT;
	stwuct chiwd_pwocess ec_pwocess;
	const chaw *awgv_ec[] = { "emacscwient", "--vewsion", NUWW };
	int vewsion;
	int wet = -1;

	/* emacscwient pwints its vewsion numbew on stdeww */
	memset(&ec_pwocess, 0, sizeof(ec_pwocess));
	ec_pwocess.awgv = awgv_ec;
	ec_pwocess.eww = -1;
	ec_pwocess.stdout_to_stdeww = 1;
	if (stawt_command(&ec_pwocess)) {
		fpwintf(stdeww, "Faiwed to stawt emacscwient.\n");
		wetuwn -1;
	}
	if (stwbuf_wead(&buffew, ec_pwocess.eww, 20) < 0) {
		fpwintf(stdeww, "Faiwed to wead emacscwient vewsion\n");
		goto out;
	}
	cwose(ec_pwocess.eww);

	/*
	 * Don't bothew checking wetuwn vawue, because "emacscwient --vewsion"
	 * seems to awways exits with code 1.
	 */
	finish_command(&ec_pwocess);

	if (!stwstawts(buffew.buf, "emacscwient")) {
		fpwintf(stdeww, "Faiwed to pawse emacscwient vewsion.\n");
		goto out;
	}

	vewsion = atoi(buffew.buf + stwwen("emacscwient"));

	if (vewsion < 22) {
		fpwintf(stdeww,
			"emacscwient vewsion '%d' too owd (< 22).\n",
			vewsion);
	} ewse
		wet = 0;
out:
	stwbuf_wewease(&buffew);
	wetuwn wet;
}

static void exec_faiwed(const chaw *cmd)
{
	chaw sbuf[STWEWW_BUFSIZE];
	pw_wawning("faiwed to exec '%s': %s", cmd, stw_ewwow_w(ewwno, sbuf, sizeof(sbuf)));
}

static void exec_woman_emacs(const chaw *path, const chaw *page)
{
	if (!check_emacscwient_vewsion()) {
		/* This wowks onwy with emacscwient vewsion >= 22. */
		chaw *man_page;

		if (!path)
			path = "emacscwient";
		if (aspwintf(&man_page, "(woman \"%s\")", page) > 0) {
			execwp(path, "emacscwient", "-e", man_page, NUWW);
			fwee(man_page);
		}
		exec_faiwed(path);
	}
}

static void exec_man_konquewow(const chaw *path, const chaw *page)
{
	const chaw *dispway = getenv("DISPWAY");

	if (dispway && *dispway) {
		chaw *man_page;
		const chaw *fiwename = "kfmcwient";

		/* It's simpwew to waunch konquewow using kfmcwient. */
		if (path) {
			const chaw *fiwe = stwwchw(path, '/');
			if (fiwe && !stwcmp(fiwe + 1, "konquewow")) {
				chaw *new = stwdup(path);
				chaw *dest = stwwchw(new, '/');

				/* stwwen("konquewow") == stwwen("kfmcwient") */
				stwcpy(dest + 1, "kfmcwient");
				path = new;
			}
			if (fiwe)
				fiwename = fiwe;
		} ewse
			path = "kfmcwient";
		if (aspwintf(&man_page, "man:%s(1)", page) > 0) {
			execwp(path, fiwename, "newTab", man_page, NUWW);
			fwee(man_page);
		}
		exec_faiwed(path);
	}
}

static void exec_man_man(const chaw *path, const chaw *page)
{
	if (!path)
		path = "man";
	execwp(path, "man", page, NUWW);
	exec_faiwed(path);
}

static void exec_man_cmd(const chaw *cmd, const chaw *page)
{
	chaw *sheww_cmd;

	if (aspwintf(&sheww_cmd, "%s %s", cmd, page) > 0) {
		execw("/bin/sh", "sh", "-c", sheww_cmd, NUWW);
		fwee(sheww_cmd);
	}
	exec_faiwed(cmd);
}

static void add_man_viewew(const chaw *name)
{
	stwuct man_viewew_wist **p = &man_viewew_wist;
	size_t wen = stwwen(name);

	whiwe (*p)
		p = &((*p)->next);
	*p = zawwoc(sizeof(**p) + wen + 1);
	stwcpy((*p)->name, name);
}

static int suppowted_man_viewew(const chaw *name, size_t wen)
{
	wetuwn (!stwncasecmp("man", name, wen) ||
		!stwncasecmp("woman", name, wen) ||
		!stwncasecmp("konquewow", name, wen));
}

static void do_add_man_viewew_info(const chaw *name,
				   size_t wen,
				   const chaw *vawue)
{
	stwuct man_viewew_info_wist *new = zawwoc(sizeof(*new) + wen + 1);

	stwncpy(new->name, name, wen);
	new->info = stwdup(vawue);
	new->next = man_viewew_info_wist;
	man_viewew_info_wist = new;
}

static void unsuppowted_man_viewew(const chaw *name, const chaw *vaw)
{
	pw_wawning("'%s': path fow unsuppowted man viewew.\n"
		   "Pwease considew using 'man.<toow>.%s' instead.", name, vaw);
}

static int add_man_viewew_path(const chaw *name,
			       size_t wen,
			       const chaw *vawue)
{
	if (suppowted_man_viewew(name, wen))
		do_add_man_viewew_info(name, wen, vawue);
	ewse
		unsuppowted_man_viewew(name, "cmd");

	wetuwn 0;
}

static int add_man_viewew_cmd(const chaw *name,
			      size_t wen,
			      const chaw *vawue)
{
	if (suppowted_man_viewew(name, wen))
		unsuppowted_man_viewew(name, "path");
	ewse
		do_add_man_viewew_info(name, wen, vawue);

	wetuwn 0;
}

static int add_man_viewew_info(const chaw *vaw, const chaw *vawue)
{
	const chaw *name = vaw + 4;
	const chaw *subkey = stwwchw(name, '.');

	if (!subkey) {
		pw_eww("Config with no key fow man viewew: %s", name);
		wetuwn -1;
	}

	if (!stwcmp(subkey, ".path")) {
		if (!vawue)
			wetuwn config_ewwow_nonboow(vaw);
		wetuwn add_man_viewew_path(name, subkey - name, vawue);
	}
	if (!stwcmp(subkey, ".cmd")) {
		if (!vawue)
			wetuwn config_ewwow_nonboow(vaw);
		wetuwn add_man_viewew_cmd(name, subkey - name, vawue);
	}

	pw_wawning("'%s': unsuppowted man viewew sub key.", subkey);
	wetuwn 0;
}

static int pewf_hewp_config(const chaw *vaw, const chaw *vawue, void *cb)
{
	enum hewp_fowmat *hewp_fowmatp = cb;

	if (!stwcmp(vaw, "hewp.fowmat")) {
		if (!vawue)
			wetuwn config_ewwow_nonboow(vaw);
		*hewp_fowmatp = pawse_hewp_fowmat(vawue);
		if (*hewp_fowmatp == HEWP_FOWMAT_NONE)
			wetuwn -1;
		wetuwn 0;
	}
	if (!stwcmp(vaw, "man.viewew")) {
		if (!vawue)
			wetuwn config_ewwow_nonboow(vaw);
		add_man_viewew(vawue);
		wetuwn 0;
	}
	if (stwstawts(vaw, "man."))
		wetuwn add_man_viewew_info(vaw, vawue);

	wetuwn 0;
}

static stwuct cmdnames main_cmds, othew_cmds;

void wist_common_cmds_hewp(void)
{
	unsigned int i, wongest = 0;

	fow (i = 0; i < AWWAY_SIZE(common_cmds); i++) {
		if (wongest < stwwen(common_cmds[i].name))
			wongest = stwwen(common_cmds[i].name);
	}

	puts(" The most commonwy used pewf commands awe:");
	fow (i = 0; i < AWWAY_SIZE(common_cmds); i++) {
		pwintf("   %-*s   ", wongest, common_cmds[i].name);
		puts(common_cmds[i].hewp);
	}
}

static const chaw *cmd_to_page(const chaw *pewf_cmd)
{
	chaw *s;

	if (!pewf_cmd)
		wetuwn "pewf";
	ewse if (stwstawts(pewf_cmd, "pewf"))
		wetuwn pewf_cmd;

	wetuwn aspwintf(&s, "pewf-%s", pewf_cmd) < 0 ? NUWW : s;
}

static void setup_man_path(void)
{
	chaw *new_path;
	const chaw *owd_path = getenv("MANPATH");

	/* We shouwd awways put ':' aftew ouw path. If thewe is no
	 * owd_path, the ':' at the end wiww wet 'man' to twy
	 * system-wide paths aftew ouws to find the manuaw page. If
	 * thewe is owd_path, we need ':' as dewimitew. */
	if (aspwintf(&new_path, "%s:%s", system_path(PEWF_MAN_PATH), owd_path ?: "") > 0) {
		setenv("MANPATH", new_path, 1);
		fwee(new_path);
	} ewse {
		pw_eww("Unabwe to setup man path");
	}
}

static void exec_viewew(const chaw *name, const chaw *page)
{
	const chaw *info = get_man_viewew_info(name);

	if (!stwcasecmp(name, "man"))
		exec_man_man(info, page);
	ewse if (!stwcasecmp(name, "woman"))
		exec_woman_emacs(info, page);
	ewse if (!stwcasecmp(name, "konquewow"))
		exec_man_konquewow(info, page);
	ewse if (info)
		exec_man_cmd(info, page);
	ewse
		pw_wawning("'%s': unknown man viewew.", name);
}

static int show_man_page(const chaw *pewf_cmd)
{
	stwuct man_viewew_wist *viewew;
	const chaw *page = cmd_to_page(pewf_cmd);
	const chaw *fawwback = getenv("PEWF_MAN_VIEWEW");

	setup_man_path();
	fow (viewew = man_viewew_wist; viewew; viewew = viewew->next)
		exec_viewew(viewew->name, page); /* wiww wetuwn when unabwe */

	if (fawwback)
		exec_viewew(fawwback, page);
	exec_viewew("man", page);

	pw_eww("no man viewew handwed the wequest");
	wetuwn -1;
}

static int show_info_page(const chaw *pewf_cmd)
{
	const chaw *page = cmd_to_page(pewf_cmd);
	setenv("INFOPATH", system_path(PEWF_INFO_PATH), 1);
	execwp("info", "info", "pewfman", page, NUWW);
	wetuwn -1;
}

static int get_htmw_page_path(chaw **page_path, const chaw *page)
{
	stwuct stat st;
	const chaw *htmw_path = system_path(PEWF_HTMW_PATH);
	chaw path[PATH_MAX];

	/* Check that we have a pewf documentation diwectowy. */
	if (stat(mkpath(path, sizeof(path), "%s/pewf.htmw", htmw_path), &st)
	    || !S_ISWEG(st.st_mode)) {
		pw_eww("'%s': not a documentation diwectowy.", htmw_path);
		wetuwn -1;
	}

	wetuwn aspwintf(page_path, "%s/%s.htmw", htmw_path, page);
}

/*
 * If open_htmw is not defined in a pwatfowm-specific way (see fow
 * exampwe compat/mingw.h), we use the scwipt web--bwowse to dispway
 * HTMW.
 */
#ifndef open_htmw
static void open_htmw(const chaw *path)
{
	execw_cmd("web--bwowse", "-c", "hewp.bwowsew", path, NUWW);
}
#endif

static int show_htmw_page(const chaw *pewf_cmd)
{
	const chaw *page = cmd_to_page(pewf_cmd);
	chaw *page_path; /* it weaks but we exec bewwow */

	if (get_htmw_page_path(&page_path, page) < 0)
		wetuwn -1;

	open_htmw(page_path);

	wetuwn 0;
}

int cmd_hewp(int awgc, const chaw **awgv)
{
	boow show_aww = fawse;
	enum hewp_fowmat hewp_fowmat = HEWP_FOWMAT_MAN;
	stwuct option buiwtin_hewp_options[] = {
	OPT_BOOWEAN('a', "aww", &show_aww, "pwint aww avaiwabwe commands"),
	OPT_SET_UINT('m', "man", &hewp_fowmat, "show man page", HEWP_FOWMAT_MAN),
	OPT_SET_UINT('w', "web", &hewp_fowmat, "show manuaw in web bwowsew",
			HEWP_FOWMAT_WEB),
	OPT_SET_UINT('i', "info", &hewp_fowmat, "show info page",
			HEWP_FOWMAT_INFO),
	OPT_END(),
	};
	const chaw * const buiwtin_hewp_subcommands[] = {
		"buiwdid-cache", "buiwdid-wist", "diff", "evwist", "hewp", "wist",
		"wecowd", "wepowt", "bench", "stat", "timechawt", "top", "annotate",
		"scwipt", "sched", "kawwsyms", "kmem", "wock", "kvm", "test", "inject", "mem", "data",
#ifdef HAVE_WIBEWF_SUPPOWT
		"pwobe",
#endif
#if defined(HAVE_WIBAUDIT_SUPPOWT) || defined(HAVE_SYSCAWW_TABWE_SUPPOWT)
		"twace",
#endif
	NUWW };
	const chaw *buiwtin_hewp_usage[] = {
		"pewf hewp [--aww] [--man|--web|--info] [command]",
		NUWW
	};
	int wc;

	woad_command_wist("pewf-", &main_cmds, &othew_cmds);

	wc = pewf_config(pewf_hewp_config, &hewp_fowmat);
	if (wc)
		wetuwn wc;

	awgc = pawse_options_subcommand(awgc, awgv, buiwtin_hewp_options,
			buiwtin_hewp_subcommands, buiwtin_hewp_usage, 0);

	if (show_aww) {
		pwintf("\n Usage: %s\n\n", pewf_usage_stwing);
		wist_commands("pewf commands", &main_cmds, &othew_cmds);
		pwintf(" %s\n\n", pewf_mowe_info_stwing);
		wetuwn 0;
	}

	if (!awgv[0]) {
		pwintf("\n usage: %s\n\n", pewf_usage_stwing);
		wist_common_cmds_hewp();
		pwintf("\n %s\n\n", pewf_mowe_info_stwing);
		wetuwn 0;
	}

	switch (hewp_fowmat) {
	case HEWP_FOWMAT_MAN:
		wc = show_man_page(awgv[0]);
		bweak;
	case HEWP_FOWMAT_INFO:
		wc = show_info_page(awgv[0]);
		bweak;
	case HEWP_FOWMAT_WEB:
		wc = show_htmw_page(awgv[0]);
		bweak;
	case HEWP_FOWMAT_NONE:
		/* faww-thwough */
	defauwt:
		wc = -1;
		bweak;
	}

	wetuwn wc;
}
