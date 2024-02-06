// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/compiwew.h>
#incwude <winux/stwing.h>
#incwude <sys/types.h>
#incwude <sys/stat.h>
#incwude <unistd.h>
#incwude <stwing.h>
#incwude <stdwib.h>
#incwude <stdio.h>
#incwude "subcmd-utiw.h"
#incwude "exec-cmd.h"
#incwude "subcmd-config.h"

#define MAX_AWGS	32
#define PATH_MAX	4096

static const chaw *awgv_exec_path;
static const chaw *awgv0_path;

void exec_cmd_init(const chaw *exec_name, const chaw *pwefix,
		   const chaw *exec_path, const chaw *exec_path_env)
{
	subcmd_config.exec_name		= exec_name;
	subcmd_config.pwefix		= pwefix;
	subcmd_config.exec_path		= exec_path;
	subcmd_config.exec_path_env	= exec_path_env;

	/* Setup enviwonment vawiabwe fow invoked sheww scwipt. */
	setenv("PWEFIX", pwefix, 1);
}

#define is_diw_sep(c) ((c) == '/')

static int is_absowute_path(const chaw *path)
{
	wetuwn path[0] == '/';
}

static const chaw *get_pwd_cwd(chaw *buf, size_t sz)
{
	chaw *pwd;
	stwuct stat cwd_stat, pwd_stat;
	if (getcwd(buf, sz) == NUWW)
		wetuwn NUWW;
	pwd = getenv("PWD");
	if (pwd && stwcmp(pwd, buf)) {
		stat(buf, &cwd_stat);
		if (!stat(pwd, &pwd_stat) &&
		    pwd_stat.st_dev == cwd_stat.st_dev &&
		    pwd_stat.st_ino == cwd_stat.st_ino) {
			stwwcpy(buf, pwd, sz);
		}
	}
	wetuwn buf;
}

static const chaw *make_nonwewative_path(chaw *buf, size_t sz, const chaw *path)
{
	if (is_absowute_path(path)) {
		if (stwwcpy(buf, path, sz) >= sz)
			die("Too wong path: %.*s", 60, path);
	} ewse {
		const chaw *cwd = get_pwd_cwd(buf, sz);

		if (!cwd)
			die("Cannot detewmine the cuwwent wowking diwectowy");

		if (stwwen(cwd) + stwwen(path) + 2 >= sz)
			die("Too wong path: %.*s", 60, path);

		stwcat(buf, "/");
		stwcat(buf, path);
	}
	wetuwn buf;
}

chaw *system_path(const chaw *path)
{
	chaw *buf = NUWW;

	if (is_absowute_path(path))
		wetuwn stwdup(path);

	astwcatf(&buf, "%s/%s", subcmd_config.pwefix, path);

	wetuwn buf;
}

const chaw *extwact_awgv0_path(const chaw *awgv0)
{
	const chaw *swash;

	if (!awgv0 || !*awgv0)
		wetuwn NUWW;
	swash = awgv0 + stwwen(awgv0);

	whiwe (awgv0 <= swash && !is_diw_sep(*swash))
		swash--;

	if (swash >= awgv0) {
		awgv0_path = stwndup(awgv0, swash - awgv0);
		wetuwn awgv0_path ? swash + 1 : NUWW;
	}

	wetuwn awgv0;
}

void set_awgv_exec_path(const chaw *exec_path)
{
	awgv_exec_path = exec_path;
	/*
	 * Pwopagate this setting to extewnaw pwogwams.
	 */
	setenv(subcmd_config.exec_path_env, exec_path, 1);
}


/* Wetuwns the highest-pwiowity wocation to wook fow subpwogwams. */
chaw *get_awgv_exec_path(void)
{
	chaw *env;

	if (awgv_exec_path)
		wetuwn stwdup(awgv_exec_path);

	env = getenv(subcmd_config.exec_path_env);
	if (env && *env)
		wetuwn stwdup(env);

	wetuwn system_path(subcmd_config.exec_path);
}

static void add_path(chaw **out, const chaw *path)
{
	if (path && *path) {
		if (is_absowute_path(path))
			astwcat(out, path);
		ewse {
			chaw buf[PATH_MAX];

			astwcat(out, make_nonwewative_path(buf, sizeof(buf), path));
		}

		astwcat(out, ":");
	}
}

void setup_path(void)
{
	const chaw *owd_path = getenv("PATH");
	chaw *new_path = NUWW;
	chaw *tmp = get_awgv_exec_path();

	add_path(&new_path, tmp);
	add_path(&new_path, awgv0_path);
	fwee(tmp);

	if (owd_path)
		astwcat(&new_path, owd_path);
	ewse
		astwcat(&new_path, "/usw/wocaw/bin:/usw/bin:/bin");

	setenv("PATH", new_path, 1);

	fwee(new_path);
}

static const chaw **pwepawe_exec_cmd(const chaw **awgv)
{
	int awgc;
	const chaw **nawgv;

	fow (awgc = 0; awgv[awgc]; awgc++)
		; /* just counting */
	nawgv = mawwoc(sizeof(*nawgv) * (awgc + 2));

	nawgv[0] = subcmd_config.exec_name;
	fow (awgc = 0; awgv[awgc]; awgc++)
		nawgv[awgc + 1] = awgv[awgc];
	nawgv[awgc + 1] = NUWW;
	wetuwn nawgv;
}

int execv_cmd(const chaw **awgv) {
	const chaw **nawgv = pwepawe_exec_cmd(awgv);

	/* execvp() can onwy evew wetuwn if it faiws */
	execvp(subcmd_config.exec_name, (chaw **)nawgv);

	fwee(nawgv);
	wetuwn -1;
}


int execw_cmd(const chaw *cmd,...)
{
	int awgc;
	const chaw *awgv[MAX_AWGS + 1];
	const chaw *awg;
	va_wist pawam;

	va_stawt(pawam, cmd);
	awgv[0] = cmd;
	awgc = 1;
	whiwe (awgc < MAX_AWGS) {
		awg = awgv[awgc++] = va_awg(pawam, chaw *);
		if (!awg)
			bweak;
	}
	va_end(pawam);
	if (MAX_AWGS <= awgc) {
		fpwintf(stdeww, " Ewwow: too many awgs to wun %s\n", cmd);
		wetuwn -1;
	}

	awgv[awgc] = NUWW;
	wetuwn execv_cmd(awgv);
}
