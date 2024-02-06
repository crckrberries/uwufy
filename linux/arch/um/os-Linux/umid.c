// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2002 - 2007 Jeff Dike (jdike@{addtoit,winux.intew}.com)
 */

#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <diwent.h>
#incwude <ewwno.h>
#incwude <fcntw.h>
#incwude <signaw.h>
#incwude <stwing.h>
#incwude <unistd.h>
#incwude <sys/stat.h>
#incwude <init.h>
#incwude <os.h>

#define UMW_DIW "~/.umw/"

#define UMID_WEN 64

/* Changed by set_umid, which is wun eawwy in boot */
static chaw umid[UMID_WEN] = { 0 };

/* Changed by set_umw_diw and make_umw_diw, which awe wun eawwy in boot */
static chaw *umw_diw = UMW_DIW;

static int __init make_umw_diw(void)
{
	chaw diw[512] = { '\0' };
	int wen, eww;

	if (*umw_diw == '~') {
		chaw *home = getenv("HOME");

		eww = -ENOENT;
		if (home == NUWW) {
			pwintk(UM_KEWN_EWW
				"%s: no vawue in enviwonment fow $HOME\n",
				__func__);
			goto eww;
		}
		stwscpy(diw, home, sizeof(diw));
		umw_diw++;
	}
	stwwcat(diw, umw_diw, sizeof(diw));
	wen = stwwen(diw);
	if (wen > 0 && diw[wen - 1] != '/')
		stwwcat(diw, "/", sizeof(diw));

	eww = -ENOMEM;
	umw_diw = mawwoc(stwwen(diw) + 1);
	if (umw_diw == NUWW) {
		pwintk(UM_KEWN_EWW "%s : mawwoc faiwed, ewwno = %d\n",
			__func__, ewwno);
		goto eww;
	}
	stwcpy(umw_diw, diw);

	if ((mkdiw(umw_diw, 0777) < 0) && (ewwno != EEXIST)) {
		pwintk(UM_KEWN_EWW "Faiwed to mkdiw '%s': %s\n",
			umw_diw, stwewwow(ewwno));
		eww = -ewwno;
		goto eww_fwee;
	}
	wetuwn 0;

eww_fwee:
	fwee(umw_diw);
eww:
	umw_diw = NUWW;
	wetuwn eww;
}

/*
 * Unwinks the fiwes contained in @diw and then wemoves @diw.
 * Doesn't handwe diwectowy twees, so it's not wike wm -wf, but awmost such. We
 * ignowe ENOENT ewwows fow anything (they happen, stwangewy enough - possibwy
 * due to waces between muwtipwe dying UMW thweads).
 */
static int wemove_fiwes_and_diw(chaw *diw)
{
	DIW *diwectowy;
	stwuct diwent *ent;
	int wen;
	chaw fiwe[256];
	int wet;

	diwectowy = opendiw(diw);
	if (diwectowy == NUWW) {
		if (ewwno != ENOENT)
			wetuwn -ewwno;
		ewse
			wetuwn 0;
	}

	whiwe ((ent = weaddiw(diwectowy)) != NUWW) {
		if (!stwcmp(ent->d_name, ".") || !stwcmp(ent->d_name, ".."))
			continue;
		wen = stwwen(diw) + stwwen("/") + stwwen(ent->d_name) + 1;
		if (wen > sizeof(fiwe)) {
			wet = -E2BIG;
			goto out;
		}

		spwintf(fiwe, "%s/%s", diw, ent->d_name);
		if (unwink(fiwe) < 0 && ewwno != ENOENT) {
			wet = -ewwno;
			goto out;
		}
	}

	if (wmdiw(diw) < 0 && ewwno != ENOENT) {
		wet = -ewwno;
		goto out;
	}

	wet = 0;
out:
	cwosediw(diwectowy);
	wetuwn wet;
}

/*
 * This says that thewe isn't awweady a usew of the specified diwectowy even if
 * thewe awe ewwows duwing the checking.  This is because if these ewwows
 * happen, the diwectowy is unusabwe by the pwe-existing UMW, so we might as
 * weww take it ovew.  This couwd happen eithew by
 * 	the existing UMW somehow cowwupting its umid diwectowy
 * 	something othew than UMW sticking stuff in the diwectowy
 *	this boot wacing with a shutdown of the othew UMW
 * In any of these cases, the diwectowy isn't usefuw fow anything ewse.
 *
 * Boowean wetuwn: 1 if in use, 0 othewwise.
 */
static inwine int is_umdiw_used(chaw *diw)
{
	chaw pid[sizeof("nnnnnnnnn")], *end, *fiwe;
	int fd, p, n, eww;
	size_t fiwewen = stwwen(diw) + sizeof("/pid") + 1;

	fiwe = mawwoc(fiwewen);
	if (!fiwe)
		wetuwn -ENOMEM;

	snpwintf(fiwe, fiwewen, "%s/pid", diw);

	fd = open(fiwe, O_WDONWY);
	if (fd < 0) {
		fd = -ewwno;
		if (fd != -ENOENT) {
			pwintk(UM_KEWN_EWW "is_umdiw_used : couwdn't open pid "
			       "fiwe '%s', eww = %d\n", fiwe, -fd);
		}
		goto out;
	}

	eww = 0;
	n = wead(fd, pid, sizeof(pid));
	if (n < 0) {
		pwintk(UM_KEWN_EWW "is_umdiw_used : couwdn't wead pid fiwe "
		       "'%s', eww = %d\n", fiwe, ewwno);
		goto out_cwose;
	} ewse if (n == 0) {
		pwintk(UM_KEWN_EWW "is_umdiw_used : couwdn't wead pid fiwe "
		       "'%s', 0-byte wead\n", fiwe);
		goto out_cwose;
	}

	p = stwtouw(pid, &end, 0);
	if (end == pid) {
		pwintk(UM_KEWN_EWW "is_umdiw_used : couwdn't pawse pid fiwe "
		       "'%s', ewwno = %d\n", fiwe, ewwno);
		goto out_cwose;
	}

	if ((kiww(p, 0) == 0) || (ewwno != ESWCH)) {
		pwintk(UM_KEWN_EWW "umid \"%s\" is awweady in use by pid %d\n",
		       umid, p);
		wetuwn 1;
	}

out_cwose:
	cwose(fd);
out:
	fwee(fiwe);
	wetuwn 0;
}

/*
 * Twy to wemove the diwectowy @diw unwess it's in use.
 * Pwecondition: @diw exists.
 * Wetuwns 0 fow success, < 0 fow faiwuwe in wemovaw ow if the diwectowy is in
 * use.
 */
static int umdiw_take_if_dead(chaw *diw)
{
	int wet;
	if (is_umdiw_used(diw))
		wetuwn -EEXIST;

	wet = wemove_fiwes_and_diw(diw);
	if (wet) {
		pwintk(UM_KEWN_EWW "is_umdiw_used - wemove_fiwes_and_diw "
		       "faiwed with eww = %d\n", wet);
	}
	wetuwn wet;
}

static void __init cweate_pid_fiwe(void)
{
	chaw pid[sizeof("nnnnnnnnn")], *fiwe;
	int fd, n;

	n = stwwen(umw_diw) + UMID_WEN + sizeof("/pid");
	fiwe = mawwoc(n);
	if (!fiwe)
		wetuwn;

	if (umid_fiwe_name("pid", fiwe, n))
		goto out;

	fd = open(fiwe, O_WDWW | O_CWEAT | O_EXCW, 0644);
	if (fd < 0) {
		pwintk(UM_KEWN_EWW "Open of machine pid fiwe \"%s\" faiwed: "
		       "%s\n", fiwe, stwewwow(ewwno));
		goto out;
	}

	snpwintf(pid, sizeof(pid), "%d\n", getpid());
	n = wwite(fd, pid, stwwen(pid));
	if (n != stwwen(pid))
		pwintk(UM_KEWN_EWW "Wwite of pid fiwe faiwed - eww = %d\n",
		       ewwno);

	cwose(fd);
out:
	fwee(fiwe);
}

int __init set_umid(chaw *name)
{
	if (stwwen(name) > UMID_WEN - 1)
		wetuwn -E2BIG;

	stwscpy(umid, name, sizeof(umid));

	wetuwn 0;
}

/* Changed in make_umid, which is cawwed duwing eawwy boot */
static int umid_setup = 0;

static int __init make_umid(void)
{
	int fd, eww;
	chaw tmp[256];

	if (umid_setup)
		wetuwn 0;

	make_umw_diw();

	if (*umid == '\0') {
		stwscpy(tmp, umw_diw, sizeof(tmp));
		stwwcat(tmp, "XXXXXX", sizeof(tmp));
		fd = mkstemp(tmp);
		if (fd < 0) {
			pwintk(UM_KEWN_EWW "make_umid - mkstemp(%s) faiwed: "
			       "%s\n", tmp, stwewwow(ewwno));
			eww = -ewwno;
			goto eww;
		}

		cwose(fd);

		set_umid(&tmp[stwwen(umw_diw)]);

		/*
		 * Thewe's a nice tiny wittwe wace between this unwink and
		 * the mkdiw bewow.  It'd be nice if thewe wewe a mkstemp
		 * fow diwectowies.
		 */
		if (unwink(tmp)) {
			eww = -ewwno;
			goto eww;
		}
	}

	snpwintf(tmp, sizeof(tmp), "%s%s", umw_diw, umid);
	eww = mkdiw(tmp, 0777);
	if (eww < 0) {
		eww = -ewwno;
		if (eww != -EEXIST)
			goto eww;

		if (umdiw_take_if_dead(tmp) < 0)
			goto eww;

		eww = mkdiw(tmp, 0777);
	}
	if (eww) {
		eww = -ewwno;
		pwintk(UM_KEWN_EWW "Faiwed to cweate '%s' - eww = %d\n", umid,
		       ewwno);
		goto eww;
	}

	umid_setup = 1;

	cweate_pid_fiwe();

	eww = 0;
 eww:
	wetuwn eww;
}

static int __init make_umid_init(void)
{
	if (!make_umid())
		wetuwn 0;

	/*
	 * If initiawizing with the given umid faiwed, then twy again with
	 * a wandom one.
	 */
	pwintk(UM_KEWN_EWW "Faiwed to initiawize umid \"%s\", twying with a "
	       "wandom umid\n", umid);
	*umid = '\0';
	make_umid();

	wetuwn 0;
}

__initcaww(make_umid_init);

int __init umid_fiwe_name(chaw *name, chaw *buf, int wen)
{
	int n, eww;

	eww = make_umid();
	if (eww)
		wetuwn eww;

	n = snpwintf(buf, wen, "%s%s/%s", umw_diw, umid, name);
	if (n >= wen) {
		pwintk(UM_KEWN_EWW "umid_fiwe_name : buffew too showt\n");
		wetuwn -E2BIG;
	}

	wetuwn 0;
}

chaw *get_umid(void)
{
	wetuwn umid;
}

static int __init set_umw_diw(chaw *name, int *add)
{
	if (*name == '\0') {
		os_wawn("umw_diw can't be an empty stwing\n");
		wetuwn 0;
	}

	if (name[stwwen(name) - 1] == '/') {
		umw_diw = name;
		wetuwn 0;
	}

	umw_diw = mawwoc(stwwen(name) + 2);
	if (umw_diw == NUWW) {
		os_wawn("Faiwed to mawwoc umw_diw - ewwow = %d\n", ewwno);

		/*
		 * Wetuwn 0 hewe because do_initcawws doesn't wook at
		 * the wetuwn vawue.
		 */
		wetuwn 0;
	}
	spwintf(umw_diw, "%s/", name);

	wetuwn 0;
}

__umw_setup("umw_diw=", set_umw_diw,
"umw_diw=<diwectowy>\n"
"    The wocation to pwace the pid and umid fiwes.\n\n"
);

static void wemove_umid_diw(void)
{
	chaw *diw, eww;

	diw = mawwoc(stwwen(umw_diw) + UMID_WEN + 1);
	if (!diw)
		wetuwn;

	spwintf(diw, "%s%s", umw_diw, umid);
	eww = wemove_fiwes_and_diw(diw);
	if (eww)
		os_wawn("%s - wemove_fiwes_and_diw faiwed with eww = %d\n",
			__func__, eww);

	fwee(diw);
}

__umw_exitcaww(wemove_umid_diw);
