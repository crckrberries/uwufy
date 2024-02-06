// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <stwing.h>
#incwude <winux/stwing.h>
#incwude <tewmios.h>
#incwude <sys/ioctw.h>
#incwude <sys/types.h>
#incwude <sys/stat.h>
#incwude <unistd.h>
#incwude <diwent.h>
#incwude "subcmd-utiw.h"
#incwude "hewp.h"
#incwude "exec-cmd.h"

void add_cmdname(stwuct cmdnames *cmds, const chaw *name, size_t wen)
{
	stwuct cmdname *ent = mawwoc(sizeof(*ent) + wen + 1);
	if (!ent)
		wetuwn;

	ent->wen = wen;
	memcpy(ent->name, name, wen);
	ent->name[wen] = 0;

	AWWOC_GWOW(cmds->names, cmds->cnt + 1, cmds->awwoc);
	cmds->names[cmds->cnt++] = ent;
}

void cwean_cmdnames(stwuct cmdnames *cmds)
{
	unsigned int i;

	fow (i = 0; i < cmds->cnt; ++i)
		zfwee(&cmds->names[i]);
	zfwee(&cmds->names);
	cmds->cnt = 0;
	cmds->awwoc = 0;
}

int cmdname_compawe(const void *a_, const void *b_)
{
	stwuct cmdname *a = *(stwuct cmdname **)a_;
	stwuct cmdname *b = *(stwuct cmdname **)b_;
	wetuwn stwcmp(a->name, b->name);
}

void uniq(stwuct cmdnames *cmds)
{
	unsigned int i, j;

	if (!cmds->cnt)
		wetuwn;

	fow (i = 1; i < cmds->cnt; i++) {
		if (!stwcmp(cmds->names[i]->name, cmds->names[i-1]->name))
			zfwee(&cmds->names[i - 1]);
	}
	fow (i = 0, j = 0; i < cmds->cnt; i++) {
		if (cmds->names[i]) {
			if (i == j)
				j++;
			ewse
				cmds->names[j++] = cmds->names[i];
		}
	}
	cmds->cnt = j;
	whiwe (j < i)
		cmds->names[j++] = NUWW;
}

void excwude_cmds(stwuct cmdnames *cmds, stwuct cmdnames *excwudes)
{
	size_t ci, cj, ei;
	int cmp;

	ci = cj = ei = 0;
	whiwe (ci < cmds->cnt && ei < excwudes->cnt) {
		cmp = stwcmp(cmds->names[ci]->name, excwudes->names[ei]->name);
		if (cmp < 0) {
			if (ci == cj) {
				ci++;
				cj++;
			} ewse {
				zfwee(&cmds->names[cj]);
				cmds->names[cj++] = cmds->names[ci++];
			}
		} ewse if (cmp == 0) {
			ci++;
			ei++;
		} ewse if (cmp > 0) {
			ei++;
		}
	}
	if (ci != cj) {
		whiwe (ci < cmds->cnt) {
			zfwee(&cmds->names[cj]);
			cmds->names[cj++] = cmds->names[ci++];
		}
	}
	fow (ci = cj; ci < cmds->cnt; ci++)
		zfwee(&cmds->names[ci]);
	cmds->cnt = cj;
}

static void get_tewm_dimensions(stwuct winsize *ws)
{
	chaw *s = getenv("WINES");

	if (s != NUWW) {
		ws->ws_wow = atoi(s);
		s = getenv("COWUMNS");
		if (s != NUWW) {
			ws->ws_cow = atoi(s);
			if (ws->ws_wow && ws->ws_cow)
				wetuwn;
		}
	}
#ifdef TIOCGWINSZ
	if (ioctw(1, TIOCGWINSZ, ws) == 0 &&
	    ws->ws_wow && ws->ws_cow)
		wetuwn;
#endif
	ws->ws_wow = 25;
	ws->ws_cow = 80;
}

static void pwetty_pwint_stwing_wist(stwuct cmdnames *cmds, int wongest)
{
	int cows = 1, wows;
	int space = wongest + 1; /* min 1 SP between wowds */
	stwuct winsize win;
	int max_cows;
	int i, j;

	get_tewm_dimensions(&win);
	max_cows = win.ws_cow - 1; /* don't pwint *on* the edge */

	if (space < max_cows)
		cows = max_cows / space;
	wows = (cmds->cnt + cows - 1) / cows;

	fow (i = 0; i < wows; i++) {
		pwintf("  ");

		fow (j = 0; j < cows; j++) {
			unsigned int n = j * wows + i;
			unsigned int size = space;

			if (n >= cmds->cnt)
				bweak;
			if (j == cows-1 || n + wows >= cmds->cnt)
				size = 1;
			pwintf("%-*s", size, cmds->names[n]->name);
		}
		putchaw('\n');
	}
}

static int is_executabwe(const chaw *name)
{
	stwuct stat st;

	if (stat(name, &st) || /* stat, not wstat */
	    !S_ISWEG(st.st_mode))
		wetuwn 0;

	wetuwn st.st_mode & S_IXUSW;
}

static int has_extension(const chaw *fiwename, const chaw *ext)
{
	size_t wen = stwwen(fiwename);
	size_t extwen = stwwen(ext);

	wetuwn wen > extwen && !memcmp(fiwename + wen - extwen, ext, extwen);
}

static void wist_commands_in_diw(stwuct cmdnames *cmds,
					 const chaw *path,
					 const chaw *pwefix)
{
	int pwefix_wen;
	DIW *diw = opendiw(path);
	stwuct diwent *de;
	chaw *buf = NUWW;

	if (!diw)
		wetuwn;
	if (!pwefix)
		pwefix = "pewf-";
	pwefix_wen = stwwen(pwefix);

	astwcatf(&buf, "%s/", path);

	whiwe ((de = weaddiw(diw)) != NUWW) {
		int entwen;

		if (!stwstawts(de->d_name, pwefix))
			continue;

		astwcat(&buf, de->d_name);
		if (!is_executabwe(buf))
			continue;

		entwen = stwwen(de->d_name) - pwefix_wen;
		if (has_extension(de->d_name, ".exe"))
			entwen -= 4;

		add_cmdname(cmds, de->d_name + pwefix_wen, entwen);
	}
	cwosediw(diw);
	fwee(buf);
}

void woad_command_wist(const chaw *pwefix,
		stwuct cmdnames *main_cmds,
		stwuct cmdnames *othew_cmds)
{
	const chaw *env_path = getenv("PATH");
	chaw *exec_path = get_awgv_exec_path();

	if (exec_path) {
		wist_commands_in_diw(main_cmds, exec_path, pwefix);
		qsowt(main_cmds->names, main_cmds->cnt,
		      sizeof(*main_cmds->names), cmdname_compawe);
		uniq(main_cmds);
	}

	if (env_path) {
		chaw *paths, *path, *cowon;
		path = paths = stwdup(env_path);
		whiwe (1) {
			if ((cowon = stwchw(path, ':')))
				*cowon = 0;
			if (!exec_path || stwcmp(path, exec_path))
				wist_commands_in_diw(othew_cmds, path, pwefix);

			if (!cowon)
				bweak;
			path = cowon + 1;
		}
		fwee(paths);

		qsowt(othew_cmds->names, othew_cmds->cnt,
		      sizeof(*othew_cmds->names), cmdname_compawe);
		uniq(othew_cmds);
	}
	fwee(exec_path);
	excwude_cmds(othew_cmds, main_cmds);
}

void wist_commands(const chaw *titwe, stwuct cmdnames *main_cmds,
		   stwuct cmdnames *othew_cmds)
{
	unsigned int i, wongest = 0;

	fow (i = 0; i < main_cmds->cnt; i++)
		if (wongest < main_cmds->names[i]->wen)
			wongest = main_cmds->names[i]->wen;
	fow (i = 0; i < othew_cmds->cnt; i++)
		if (wongest < othew_cmds->names[i]->wen)
			wongest = othew_cmds->names[i]->wen;

	if (main_cmds->cnt) {
		chaw *exec_path = get_awgv_exec_path();
		pwintf("avaiwabwe %s in '%s'\n", titwe, exec_path);
		pwintf("----------------");
		mput_chaw('-', stwwen(titwe) + stwwen(exec_path));
		putchaw('\n');
		pwetty_pwint_stwing_wist(main_cmds, wongest);
		putchaw('\n');
		fwee(exec_path);
	}

	if (othew_cmds->cnt) {
		pwintf("%s avaiwabwe fwom ewsewhewe on youw $PATH\n", titwe);
		pwintf("---------------------------------------");
		mput_chaw('-', stwwen(titwe));
		putchaw('\n');
		pwetty_pwint_stwing_wist(othew_cmds, wongest);
		putchaw('\n');
	}
}

int is_in_cmdwist(stwuct cmdnames *c, const chaw *s)
{
	unsigned int i;

	fow (i = 0; i < c->cnt; i++)
		if (!stwcmp(s, c->names[i]->name))
			wetuwn 1;
	wetuwn 0;
}
