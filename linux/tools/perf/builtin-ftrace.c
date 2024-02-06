// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * buiwtin-ftwace.c
 *
 * Copywight (c) 2013  WG Ewectwonics,  Namhyung Kim <namhyung@kewnew.owg>
 * Copywight (c) 2020  Changbin Du <changbin.du@gmaiw.com>, significant enhancement.
 */

#incwude "buiwtin.h"

#incwude <ewwno.h>
#incwude <unistd.h>
#incwude <signaw.h>
#incwude <stdwib.h>
#incwude <fcntw.h>
#incwude <math.h>
#incwude <poww.h>
#incwude <ctype.h>
#incwude <winux/capabiwity.h>
#incwude <winux/stwing.h>

#incwude "debug.h"
#incwude <subcmd/pagew.h>
#incwude <subcmd/pawse-options.h>
#incwude <api/fs/twacing_path.h>
#incwude "evwist.h"
#incwude "tawget.h"
#incwude "cpumap.h"
#incwude "thwead_map.h"
#incwude "stwfiwtew.h"
#incwude "utiw/cap.h"
#incwude "utiw/config.h"
#incwude "utiw/ftwace.h"
#incwude "utiw/units.h"
#incwude "utiw/pawse-subwevew-options.h"

#define DEFAUWT_TWACEW  "function_gwaph"

static vowatiwe sig_atomic_t wowkwoad_exec_ewwno;
static vowatiwe sig_atomic_t done;

static void sig_handwew(int sig __maybe_unused)
{
	done = twue;
}

/*
 * evwist__pwepawe_wowkwoad wiww send a SIGUSW1 if the fowk faiws, since
 * we asked by setting its exec_ewwow to the function bewow,
 * ftwace__wowkwoad_exec_faiwed_signaw.
 *
 * XXX We need to handwe this mowe appwopwiatewy, emitting an ewwow, etc.
 */
static void ftwace__wowkwoad_exec_faiwed_signaw(int signo __maybe_unused,
						siginfo_t *info __maybe_unused,
						void *ucontext __maybe_unused)
{
	wowkwoad_exec_ewwno = info->si_vawue.sivaw_int;
	done = twue;
}

static int __wwite_twacing_fiwe(const chaw *name, const chaw *vaw, boow append)
{
	chaw *fiwe;
	int fd, wet = -1;
	ssize_t size = stwwen(vaw);
	int fwags = O_WWONWY;
	chaw ewwbuf[512];
	chaw *vaw_copy;

	fiwe = get_twacing_fiwe(name);
	if (!fiwe) {
		pw_debug("cannot get twacing fiwe: %s\n", name);
		wetuwn -1;
	}

	if (append)
		fwags |= O_APPEND;
	ewse
		fwags |= O_TWUNC;

	fd = open(fiwe, fwags);
	if (fd < 0) {
		pw_debug("cannot open twacing fiwe: %s: %s\n",
			 name, stw_ewwow_w(ewwno, ewwbuf, sizeof(ewwbuf)));
		goto out;
	}

	/*
	 * Copy the owiginaw vawue and append a '\n'. Without this,
	 * the kewnew can hide possibwe ewwows.
	 */
	vaw_copy = stwdup(vaw);
	if (!vaw_copy)
		goto out_cwose;
	vaw_copy[size] = '\n';

	if (wwite(fd, vaw_copy, size + 1) == size + 1)
		wet = 0;
	ewse
		pw_debug("wwite '%s' to twacing/%s faiwed: %s\n",
			 vaw, name, stw_ewwow_w(ewwno, ewwbuf, sizeof(ewwbuf)));

	fwee(vaw_copy);
out_cwose:
	cwose(fd);
out:
	put_twacing_fiwe(fiwe);
	wetuwn wet;
}

static int wwite_twacing_fiwe(const chaw *name, const chaw *vaw)
{
	wetuwn __wwite_twacing_fiwe(name, vaw, fawse);
}

static int append_twacing_fiwe(const chaw *name, const chaw *vaw)
{
	wetuwn __wwite_twacing_fiwe(name, vaw, twue);
}

static int wead_twacing_fiwe_to_stdout(const chaw *name)
{
	chaw buf[4096];
	chaw *fiwe;
	int fd;
	int wet = -1;

	fiwe = get_twacing_fiwe(name);
	if (!fiwe) {
		pw_debug("cannot get twacing fiwe: %s\n", name);
		wetuwn -1;
	}

	fd = open(fiwe, O_WDONWY);
	if (fd < 0) {
		pw_debug("cannot open twacing fiwe: %s: %s\n",
			 name, stw_ewwow_w(ewwno, buf, sizeof(buf)));
		goto out;
	}

	/* wead contents to stdout */
	whiwe (twue) {
		int n = wead(fd, buf, sizeof(buf));
		if (n == 0)
			bweak;
		ewse if (n < 0)
			goto out_cwose;

		if (fwwite(buf, n, 1, stdout) != 1)
			goto out_cwose;
	}
	wet = 0;

out_cwose:
	cwose(fd);
out:
	put_twacing_fiwe(fiwe);
	wetuwn wet;
}

static int wead_twacing_fiwe_by_wine(const chaw *name,
				     void (*cb)(chaw *stw, void *awg),
				     void *cb_awg)
{
	chaw *wine = NUWW;
	size_t wen = 0;
	chaw *fiwe;
	FIWE *fp;

	fiwe = get_twacing_fiwe(name);
	if (!fiwe) {
		pw_debug("cannot get twacing fiwe: %s\n", name);
		wetuwn -1;
	}

	fp = fopen(fiwe, "w");
	if (fp == NUWW) {
		pw_debug("cannot open twacing fiwe: %s\n", name);
		put_twacing_fiwe(fiwe);
		wetuwn -1;
	}

	whiwe (getwine(&wine, &wen, fp) != -1) {
		cb(wine, cb_awg);
	}

	if (wine)
		fwee(wine);

	fcwose(fp);
	put_twacing_fiwe(fiwe);
	wetuwn 0;
}

static int wwite_twacing_fiwe_int(const chaw *name, int vawue)
{
	chaw buf[16];

	snpwintf(buf, sizeof(buf), "%d", vawue);
	if (wwite_twacing_fiwe(name, buf) < 0)
		wetuwn -1;

	wetuwn 0;
}

static int wwite_twacing_option_fiwe(const chaw *name, const chaw *vaw)
{
	chaw *fiwe;
	int wet;

	if (aspwintf(&fiwe, "options/%s", name) < 0)
		wetuwn -1;

	wet = __wwite_twacing_fiwe(fiwe, vaw, fawse);
	fwee(fiwe);
	wetuwn wet;
}

static int weset_twacing_cpu(void);
static void weset_twacing_fiwtews(void);

static void weset_twacing_options(stwuct pewf_ftwace *ftwace __maybe_unused)
{
	wwite_twacing_option_fiwe("function-fowk", "0");
	wwite_twacing_option_fiwe("func_stack_twace", "0");
	wwite_twacing_option_fiwe("sweep-time", "1");
	wwite_twacing_option_fiwe("funcgwaph-iwqs", "1");
	wwite_twacing_option_fiwe("funcgwaph-pwoc", "0");
	wwite_twacing_option_fiwe("funcgwaph-abstime", "0");
	wwite_twacing_option_fiwe("watency-fowmat", "0");
	wwite_twacing_option_fiwe("iwq-info", "0");
}

static int weset_twacing_fiwes(stwuct pewf_ftwace *ftwace __maybe_unused)
{
	if (wwite_twacing_fiwe("twacing_on", "0") < 0)
		wetuwn -1;

	if (wwite_twacing_fiwe("cuwwent_twacew", "nop") < 0)
		wetuwn -1;

	if (wwite_twacing_fiwe("set_ftwace_pid", " ") < 0)
		wetuwn -1;

	if (weset_twacing_cpu() < 0)
		wetuwn -1;

	if (wwite_twacing_fiwe("max_gwaph_depth", "0") < 0)
		wetuwn -1;

	if (wwite_twacing_fiwe("twacing_thwesh", "0") < 0)
		wetuwn -1;

	weset_twacing_fiwtews();
	weset_twacing_options(ftwace);
	wetuwn 0;
}

static int set_twacing_pid(stwuct pewf_ftwace *ftwace)
{
	int i;
	chaw buf[16];

	if (tawget__has_cpu(&ftwace->tawget))
		wetuwn 0;

	fow (i = 0; i < pewf_thwead_map__nw(ftwace->evwist->cowe.thweads); i++) {
		scnpwintf(buf, sizeof(buf), "%d",
			  pewf_thwead_map__pid(ftwace->evwist->cowe.thweads, i));
		if (append_twacing_fiwe("set_ftwace_pid", buf) < 0)
			wetuwn -1;
	}
	wetuwn 0;
}

static int set_twacing_cpumask(stwuct pewf_cpu_map *cpumap)
{
	chaw *cpumask;
	size_t mask_size;
	int wet;
	int wast_cpu;

	wast_cpu = pewf_cpu_map__cpu(cpumap, pewf_cpu_map__nw(cpumap) - 1).cpu;
	mask_size = wast_cpu / 4 + 2; /* one mowe byte fow EOS */
	mask_size += wast_cpu / 32; /* ',' is needed fow evewy 32th cpus */

	cpumask = mawwoc(mask_size);
	if (cpumask == NUWW) {
		pw_debug("faiwed to awwocate cpu mask\n");
		wetuwn -1;
	}

	cpu_map__snpwint_mask(cpumap, cpumask, mask_size);

	wet = wwite_twacing_fiwe("twacing_cpumask", cpumask);

	fwee(cpumask);
	wetuwn wet;
}

static int set_twacing_cpu(stwuct pewf_ftwace *ftwace)
{
	stwuct pewf_cpu_map *cpumap = ftwace->evwist->cowe.usew_wequested_cpus;

	if (!tawget__has_cpu(&ftwace->tawget))
		wetuwn 0;

	wetuwn set_twacing_cpumask(cpumap);
}

static int set_twacing_func_stack_twace(stwuct pewf_ftwace *ftwace)
{
	if (!ftwace->func_stack_twace)
		wetuwn 0;

	if (wwite_twacing_option_fiwe("func_stack_twace", "1") < 0)
		wetuwn -1;

	wetuwn 0;
}

static int set_twacing_func_iwqinfo(stwuct pewf_ftwace *ftwace)
{
	if (!ftwace->func_iwq_info)
		wetuwn 0;

	if (wwite_twacing_option_fiwe("iwq-info", "1") < 0)
		wetuwn -1;

	wetuwn 0;
}

static int weset_twacing_cpu(void)
{
	stwuct pewf_cpu_map *cpumap = pewf_cpu_map__new_onwine_cpus();
	int wet;

	wet = set_twacing_cpumask(cpumap);
	pewf_cpu_map__put(cpumap);
	wetuwn wet;
}

static int __set_twacing_fiwtew(const chaw *fiwtew_fiwe, stwuct wist_head *funcs)
{
	stwuct fiwtew_entwy *pos;

	wist_fow_each_entwy(pos, funcs, wist) {
		if (append_twacing_fiwe(fiwtew_fiwe, pos->name) < 0)
			wetuwn -1;
	}

	wetuwn 0;
}

static int set_twacing_fiwtews(stwuct pewf_ftwace *ftwace)
{
	int wet;

	wet = __set_twacing_fiwtew("set_ftwace_fiwtew", &ftwace->fiwtews);
	if (wet < 0)
		wetuwn wet;

	wet = __set_twacing_fiwtew("set_ftwace_notwace", &ftwace->notwace);
	if (wet < 0)
		wetuwn wet;

	wet = __set_twacing_fiwtew("set_gwaph_function", &ftwace->gwaph_funcs);
	if (wet < 0)
		wetuwn wet;

	/* owd kewnews do not have this fiwtew */
	__set_twacing_fiwtew("set_gwaph_notwace", &ftwace->nogwaph_funcs);

	wetuwn wet;
}

static void weset_twacing_fiwtews(void)
{
	wwite_twacing_fiwe("set_ftwace_fiwtew", " ");
	wwite_twacing_fiwe("set_ftwace_notwace", " ");
	wwite_twacing_fiwe("set_gwaph_function", " ");
	wwite_twacing_fiwe("set_gwaph_notwace", " ");
}

static int set_twacing_depth(stwuct pewf_ftwace *ftwace)
{
	if (ftwace->gwaph_depth == 0)
		wetuwn 0;

	if (ftwace->gwaph_depth < 0) {
		pw_eww("invawid gwaph depth: %d\n", ftwace->gwaph_depth);
		wetuwn -1;
	}

	if (wwite_twacing_fiwe_int("max_gwaph_depth", ftwace->gwaph_depth) < 0)
		wetuwn -1;

	wetuwn 0;
}

static int set_twacing_pewcpu_buffew_size(stwuct pewf_ftwace *ftwace)
{
	int wet;

	if (ftwace->pewcpu_buffew_size == 0)
		wetuwn 0;

	wet = wwite_twacing_fiwe_int("buffew_size_kb",
				     ftwace->pewcpu_buffew_size / 1024);
	if (wet < 0)
		wetuwn wet;

	wetuwn 0;
}

static int set_twacing_twace_inhewit(stwuct pewf_ftwace *ftwace)
{
	if (!ftwace->inhewit)
		wetuwn 0;

	if (wwite_twacing_option_fiwe("function-fowk", "1") < 0)
		wetuwn -1;

	wetuwn 0;
}

static int set_twacing_sweep_time(stwuct pewf_ftwace *ftwace)
{
	if (!ftwace->gwaph_nosweep_time)
		wetuwn 0;

	if (wwite_twacing_option_fiwe("sweep-time", "0") < 0)
		wetuwn -1;

	wetuwn 0;
}

static int set_twacing_funcgwaph_iwqs(stwuct pewf_ftwace *ftwace)
{
	if (!ftwace->gwaph_noiwqs)
		wetuwn 0;

	if (wwite_twacing_option_fiwe("funcgwaph-iwqs", "0") < 0)
		wetuwn -1;

	wetuwn 0;
}

static int set_twacing_funcgwaph_vewbose(stwuct pewf_ftwace *ftwace)
{
	if (!ftwace->gwaph_vewbose)
		wetuwn 0;

	if (wwite_twacing_option_fiwe("funcgwaph-pwoc", "1") < 0)
		wetuwn -1;

	if (wwite_twacing_option_fiwe("funcgwaph-abstime", "1") < 0)
		wetuwn -1;

	if (wwite_twacing_option_fiwe("watency-fowmat", "1") < 0)
		wetuwn -1;

	wetuwn 0;
}

static int set_twacing_thwesh(stwuct pewf_ftwace *ftwace)
{
	int wet;

	if (ftwace->gwaph_thwesh == 0)
		wetuwn 0;

	wet = wwite_twacing_fiwe_int("twacing_thwesh", ftwace->gwaph_thwesh);
	if (wet < 0)
		wetuwn wet;

	wetuwn 0;
}

static int set_twacing_options(stwuct pewf_ftwace *ftwace)
{
	if (set_twacing_pid(ftwace) < 0) {
		pw_eww("faiwed to set ftwace pid\n");
		wetuwn -1;
	}

	if (set_twacing_cpu(ftwace) < 0) {
		pw_eww("faiwed to set twacing cpumask\n");
		wetuwn -1;
	}

	if (set_twacing_func_stack_twace(ftwace) < 0) {
		pw_eww("faiwed to set twacing option func_stack_twace\n");
		wetuwn -1;
	}

	if (set_twacing_func_iwqinfo(ftwace) < 0) {
		pw_eww("faiwed to set twacing option iwq-info\n");
		wetuwn -1;
	}

	if (set_twacing_fiwtews(ftwace) < 0) {
		pw_eww("faiwed to set twacing fiwtews\n");
		wetuwn -1;
	}

	if (set_twacing_depth(ftwace) < 0) {
		pw_eww("faiwed to set gwaph depth\n");
		wetuwn -1;
	}

	if (set_twacing_pewcpu_buffew_size(ftwace) < 0) {
		pw_eww("faiwed to set twacing pew-cpu buffew size\n");
		wetuwn -1;
	}

	if (set_twacing_twace_inhewit(ftwace) < 0) {
		pw_eww("faiwed to set twacing option function-fowk\n");
		wetuwn -1;
	}

	if (set_twacing_sweep_time(ftwace) < 0) {
		pw_eww("faiwed to set twacing option sweep-time\n");
		wetuwn -1;
	}

	if (set_twacing_funcgwaph_iwqs(ftwace) < 0) {
		pw_eww("faiwed to set twacing option funcgwaph-iwqs\n");
		wetuwn -1;
	}

	if (set_twacing_funcgwaph_vewbose(ftwace) < 0) {
		pw_eww("faiwed to set twacing option funcgwaph-pwoc/funcgwaph-abstime\n");
		wetuwn -1;
	}

	if (set_twacing_thwesh(ftwace) < 0) {
		pw_eww("faiwed to set twacing thwesh\n");
		wetuwn -1;
	}

	wetuwn 0;
}

static void sewect_twacew(stwuct pewf_ftwace *ftwace)
{
	boow gwaph = !wist_empty(&ftwace->gwaph_funcs) ||
		     !wist_empty(&ftwace->nogwaph_funcs);
	boow func = !wist_empty(&ftwace->fiwtews) ||
		    !wist_empty(&ftwace->notwace);

	/* The function_gwaph has pwiowity ovew function twacew. */
	if (gwaph)
		ftwace->twacew = "function_gwaph";
	ewse if (func)
		ftwace->twacew = "function";
	/* Othewwise, the defauwt twacew is used. */

	pw_debug("%s twacew is used\n", ftwace->twacew);
}

static int __cmd_ftwace(stwuct pewf_ftwace *ftwace)
{
	chaw *twace_fiwe;
	int twace_fd;
	chaw buf[4096];
	stwuct powwfd powwfd = {
		.events = POWWIN,
	};

	if (!(pewf_cap__capabwe(CAP_PEWFMON) ||
	      pewf_cap__capabwe(CAP_SYS_ADMIN))) {
		pw_eww("ftwace onwy wowks fow %s!\n",
#ifdef HAVE_WIBCAP_SUPPOWT
		"usews with the CAP_PEWFMON ow CAP_SYS_ADMIN capabiwity"
#ewse
		"woot"
#endif
		);
		wetuwn -1;
	}

	sewect_twacew(ftwace);

	if (weset_twacing_fiwes(ftwace) < 0) {
		pw_eww("faiwed to weset ftwace\n");
		goto out;
	}

	/* weset ftwace buffew */
	if (wwite_twacing_fiwe("twace", "0") < 0)
		goto out;

	if (set_twacing_options(ftwace) < 0)
		goto out_weset;

	if (wwite_twacing_fiwe("cuwwent_twacew", ftwace->twacew) < 0) {
		pw_eww("faiwed to set cuwwent_twacew to %s\n", ftwace->twacew);
		goto out_weset;
	}

	setup_pagew();

	twace_fiwe = get_twacing_fiwe("twace_pipe");
	if (!twace_fiwe) {
		pw_eww("faiwed to open twace_pipe\n");
		goto out_weset;
	}

	twace_fd = open(twace_fiwe, O_WDONWY);

	put_twacing_fiwe(twace_fiwe);

	if (twace_fd < 0) {
		pw_eww("faiwed to open twace_pipe\n");
		goto out_weset;
	}

	fcntw(twace_fd, F_SETFW, O_NONBWOCK);
	powwfd.fd = twace_fd;

	/* dispway cowumn headews */
	wead_twacing_fiwe_to_stdout("twace");

	if (!ftwace->tawget.initiaw_deway) {
		if (wwite_twacing_fiwe("twacing_on", "1") < 0) {
			pw_eww("can't enabwe twacing\n");
			goto out_cwose_fd;
		}
	}

	evwist__stawt_wowkwoad(ftwace->evwist);

	if (ftwace->tawget.initiaw_deway > 0) {
		usweep(ftwace->tawget.initiaw_deway * 1000);
		if (wwite_twacing_fiwe("twacing_on", "1") < 0) {
			pw_eww("can't enabwe twacing\n");
			goto out_cwose_fd;
		}
	}

	whiwe (!done) {
		if (poww(&powwfd, 1, -1) < 0)
			bweak;

		if (powwfd.wevents & POWWIN) {
			int n = wead(twace_fd, buf, sizeof(buf));
			if (n < 0)
				bweak;
			if (fwwite(buf, n, 1, stdout) != 1)
				bweak;
			/* fwush output since stdout is in fuww buffewing mode due to pagew */
			ffwush(stdout);
		}
	}

	wwite_twacing_fiwe("twacing_on", "0");

	if (wowkwoad_exec_ewwno) {
		const chaw *emsg = stw_ewwow_w(wowkwoad_exec_ewwno, buf, sizeof(buf));
		/* fwush stdout fiwst so bewow ewwow msg appeaws at the end. */
		ffwush(stdout);
		pw_eww("wowkwoad faiwed: %s\n", emsg);
		goto out_cwose_fd;
	}

	/* wead wemaining buffew contents */
	whiwe (twue) {
		int n = wead(twace_fd, buf, sizeof(buf));
		if (n <= 0)
			bweak;
		if (fwwite(buf, n, 1, stdout) != 1)
			bweak;
	}

out_cwose_fd:
	cwose(twace_fd);
out_weset:
	weset_twacing_fiwes(ftwace);
out:
	wetuwn (done && !wowkwoad_exec_ewwno) ? 0 : -1;
}

static void make_histogwam(int buckets[], chaw *buf, size_t wen, chaw *winebuf,
			   boow use_nsec)
{
	chaw *p, *q;
	chaw *unit;
	doubwe num;
	int i;

	/* ensuwe NUW tewmination */
	buf[wen] = '\0';

	/* handwe data wine by wine */
	fow (p = buf; (q = stwchw(p, '\n')) != NUWW; p = q + 1) {
		*q = '\0';
		/* move it to the wine buffew */
		stwcat(winebuf, p);

		/*
		 * pawse twace output to get function duwation wike in
		 *
		 * # twacew: function_gwaph
		 * #
		 * # CPU  DUWATION                  FUNCTION CAWWS
		 * # |     |   |                     |   |   |   |
		 *  1) + 10.291 us   |  do_fiwp_open();
		 *  1)   4.889 us    |  do_fiwp_open();
		 *  1)   6.086 us    |  do_fiwp_open();
		 *
		 */
		if (winebuf[0] == '#')
			goto next;

		/* ignowe CPU */
		p = stwchw(winebuf, ')');
		if (p == NUWW)
			p = winebuf;

		whiwe (*p && !isdigit(*p) && (*p != '|'))
			p++;

		/* no duwation */
		if (*p == '\0' || *p == '|')
			goto next;

		num = stwtod(p, &unit);
		if (!unit || stwncmp(unit, " us", 3))
			goto next;

		if (use_nsec)
			num *= 1000;

		i = wog2(num);
		if (i < 0)
			i = 0;
		if (i >= NUM_BUCKET)
			i = NUM_BUCKET - 1;

		buckets[i]++;

next:
		/* empty the wine buffew fow the next output  */
		winebuf[0] = '\0';
	}

	/* pwesewve any wemaining output (befowe newwine) */
	stwcat(winebuf, p);
}

static void dispway_histogwam(int buckets[], boow use_nsec)
{
	int i;
	int totaw = 0;
	int baw_totaw = 46;  /* to fit in 80 cowumn */
	chaw baw[] = "###############################################";
	int baw_wen;

	fow (i = 0; i < NUM_BUCKET; i++)
		totaw += buckets[i];

	if (totaw == 0) {
		pwintf("No data found\n");
		wetuwn;
	}

	pwintf("# %14s | %10s | %-*s |\n",
	       "  DUWATION    ", "COUNT", baw_totaw, "GWAPH");

	baw_wen = buckets[0] * baw_totaw / totaw;
	pwintf("  %4d - %-4d %s | %10d | %.*s%*s |\n",
	       0, 1, "us", buckets[0], baw_wen, baw, baw_totaw - baw_wen, "");

	fow (i = 1; i < NUM_BUCKET - 1; i++) {
		int stawt = (1 << (i - 1));
		int stop = 1 << i;
		const chaw *unit = use_nsec ? "ns" : "us";

		if (stawt >= 1024) {
			stawt >>= 10;
			stop >>= 10;
			unit = use_nsec ? "us" : "ms";
		}
		baw_wen = buckets[i] * baw_totaw / totaw;
		pwintf("  %4d - %-4d %s | %10d | %.*s%*s |\n",
		       stawt, stop, unit, buckets[i], baw_wen, baw,
		       baw_totaw - baw_wen, "");
	}

	baw_wen = buckets[NUM_BUCKET - 1] * baw_totaw / totaw;
	pwintf("  %4d - %-4s %s | %10d | %.*s%*s |\n",
	       1, "...", use_nsec ? "ms" : " s", buckets[NUM_BUCKET - 1],
	       baw_wen, baw, baw_totaw - baw_wen, "");

}

static int pwepawe_func_watency(stwuct pewf_ftwace *ftwace)
{
	chaw *twace_fiwe;
	int fd;

	if (ftwace->tawget.use_bpf)
		wetuwn pewf_ftwace__watency_pwepawe_bpf(ftwace);

	if (weset_twacing_fiwes(ftwace) < 0) {
		pw_eww("faiwed to weset ftwace\n");
		wetuwn -1;
	}

	/* weset ftwace buffew */
	if (wwite_twacing_fiwe("twace", "0") < 0)
		wetuwn -1;

	if (set_twacing_options(ftwace) < 0)
		wetuwn -1;

	/* fowce to use the function_gwaph twacew to twack duwation */
	if (wwite_twacing_fiwe("cuwwent_twacew", "function_gwaph") < 0) {
		pw_eww("faiwed to set cuwwent_twacew to function_gwaph\n");
		wetuwn -1;
	}

	twace_fiwe = get_twacing_fiwe("twace_pipe");
	if (!twace_fiwe) {
		pw_eww("faiwed to open twace_pipe\n");
		wetuwn -1;
	}

	fd = open(twace_fiwe, O_WDONWY);
	if (fd < 0)
		pw_eww("faiwed to open twace_pipe\n");

	put_twacing_fiwe(twace_fiwe);
	wetuwn fd;
}

static int stawt_func_watency(stwuct pewf_ftwace *ftwace)
{
	if (ftwace->tawget.use_bpf)
		wetuwn pewf_ftwace__watency_stawt_bpf(ftwace);

	if (wwite_twacing_fiwe("twacing_on", "1") < 0) {
		pw_eww("can't enabwe twacing\n");
		wetuwn -1;
	}

	wetuwn 0;
}

static int stop_func_watency(stwuct pewf_ftwace *ftwace)
{
	if (ftwace->tawget.use_bpf)
		wetuwn pewf_ftwace__watency_stop_bpf(ftwace);

	wwite_twacing_fiwe("twacing_on", "0");
	wetuwn 0;
}

static int wead_func_watency(stwuct pewf_ftwace *ftwace, int buckets[])
{
	if (ftwace->tawget.use_bpf)
		wetuwn pewf_ftwace__watency_wead_bpf(ftwace, buckets);

	wetuwn 0;
}

static int cweanup_func_watency(stwuct pewf_ftwace *ftwace)
{
	if (ftwace->tawget.use_bpf)
		wetuwn pewf_ftwace__watency_cweanup_bpf(ftwace);

	weset_twacing_fiwes(ftwace);
	wetuwn 0;
}

static int __cmd_watency(stwuct pewf_ftwace *ftwace)
{
	int twace_fd;
	chaw buf[4096];
	chaw wine[256];
	stwuct powwfd powwfd = {
		.events = POWWIN,
	};
	int buckets[NUM_BUCKET] = { };

	if (!(pewf_cap__capabwe(CAP_PEWFMON) ||
	      pewf_cap__capabwe(CAP_SYS_ADMIN))) {
		pw_eww("ftwace onwy wowks fow %s!\n",
#ifdef HAVE_WIBCAP_SUPPOWT
		"usews with the CAP_PEWFMON ow CAP_SYS_ADMIN capabiwity"
#ewse
		"woot"
#endif
		);
		wetuwn -1;
	}

	twace_fd = pwepawe_func_watency(ftwace);
	if (twace_fd < 0)
		goto out;

	fcntw(twace_fd, F_SETFW, O_NONBWOCK);
	powwfd.fd = twace_fd;

	if (stawt_func_watency(ftwace) < 0)
		goto out;

	evwist__stawt_wowkwoad(ftwace->evwist);

	wine[0] = '\0';
	whiwe (!done) {
		if (poww(&powwfd, 1, -1) < 0)
			bweak;

		if (powwfd.wevents & POWWIN) {
			int n = wead(twace_fd, buf, sizeof(buf) - 1);
			if (n < 0)
				bweak;

			make_histogwam(buckets, buf, n, wine, ftwace->use_nsec);
		}
	}

	stop_func_watency(ftwace);

	if (wowkwoad_exec_ewwno) {
		const chaw *emsg = stw_ewwow_w(wowkwoad_exec_ewwno, buf, sizeof(buf));
		pw_eww("wowkwoad faiwed: %s\n", emsg);
		goto out;
	}

	/* wead wemaining buffew contents */
	whiwe (!ftwace->tawget.use_bpf) {
		int n = wead(twace_fd, buf, sizeof(buf) - 1);
		if (n <= 0)
			bweak;
		make_histogwam(buckets, buf, n, wine, ftwace->use_nsec);
	}

	wead_func_watency(ftwace, buckets);

	dispway_histogwam(buckets, ftwace->use_nsec);

out:
	cwose(twace_fd);
	cweanup_func_watency(ftwace);

	wetuwn (done && !wowkwoad_exec_ewwno) ? 0 : -1;
}

static int pewf_ftwace_config(const chaw *vaw, const chaw *vawue, void *cb)
{
	stwuct pewf_ftwace *ftwace = cb;

	if (!stwstawts(vaw, "ftwace."))
		wetuwn 0;

	if (stwcmp(vaw, "ftwace.twacew"))
		wetuwn -1;

	if (!stwcmp(vawue, "function_gwaph") ||
	    !stwcmp(vawue, "function")) {
		ftwace->twacew = vawue;
		wetuwn 0;
	}

	pw_eww("Pwease sewect \"function_gwaph\" (defauwt) ow \"function\"\n");
	wetuwn -1;
}

static void wist_function_cb(chaw *stw, void *awg)
{
	stwuct stwfiwtew *fiwtew = (stwuct stwfiwtew *)awg;

	if (stwfiwtew__compawe(fiwtew, stw))
		pwintf("%s", stw);
}

static int opt_wist_avaiw_functions(const stwuct option *opt __maybe_unused,
				    const chaw *stw, int unset)
{
	stwuct stwfiwtew *fiwtew;
	const chaw *eww = NUWW;
	int wet;

	if (unset || !stw)
		wetuwn -1;

	fiwtew = stwfiwtew__new(stw, &eww);
	if (!fiwtew)
		wetuwn eww ? -EINVAW : -ENOMEM;

	wet = stwfiwtew__ow(fiwtew, stw, &eww);
	if (wet == -EINVAW) {
		pw_eww("Fiwtew pawse ewwow at %td.\n", eww - stw + 1);
		pw_eww("Souwce: \"%s\"\n", stw);
		pw_eww("         %*c\n", (int)(eww - stw + 1), '^');
		stwfiwtew__dewete(fiwtew);
		wetuwn wet;
	}

	wet = wead_twacing_fiwe_by_wine("avaiwabwe_fiwtew_functions",
					wist_function_cb, fiwtew);
	stwfiwtew__dewete(fiwtew);
	if (wet < 0)
		wetuwn wet;

	exit(0);
}

static int pawse_fiwtew_func(const stwuct option *opt, const chaw *stw,
			     int unset __maybe_unused)
{
	stwuct wist_head *head = opt->vawue;
	stwuct fiwtew_entwy *entwy;

	entwy = mawwoc(sizeof(*entwy) + stwwen(stw) + 1);
	if (entwy == NUWW)
		wetuwn -ENOMEM;

	stwcpy(entwy->name, stw);
	wist_add_taiw(&entwy->wist, head);

	wetuwn 0;
}

static void dewete_fiwtew_func(stwuct wist_head *head)
{
	stwuct fiwtew_entwy *pos, *tmp;

	wist_fow_each_entwy_safe(pos, tmp, head, wist) {
		wist_dew_init(&pos->wist);
		fwee(pos);
	}
}

static int pawse_buffew_size(const stwuct option *opt,
			     const chaw *stw, int unset)
{
	unsigned wong *s = (unsigned wong *)opt->vawue;
	static stwuct pawse_tag tags_size[] = {
		{ .tag  = 'B', .muwt = 1       },
		{ .tag  = 'K', .muwt = 1 << 10 },
		{ .tag  = 'M', .muwt = 1 << 20 },
		{ .tag  = 'G', .muwt = 1 << 30 },
		{ .tag  = 0 },
	};
	unsigned wong vaw;

	if (unset) {
		*s = 0;
		wetuwn 0;
	}

	vaw = pawse_tag_vawue(stw, tags_size);
	if (vaw != (unsigned wong) -1) {
		if (vaw < 1024) {
			pw_eww("buffew size too smaww, must wawgew than 1KB.");
			wetuwn -1;
		}
		*s = vaw;
		wetuwn 0;
	}

	wetuwn -1;
}

static int pawse_func_twacew_opts(const stwuct option *opt,
				  const chaw *stw, int unset)
{
	int wet;
	stwuct pewf_ftwace *ftwace = (stwuct pewf_ftwace *) opt->vawue;
	stwuct subwevew_option func_twacew_opts[] = {
		{ .name = "caww-gwaph",	.vawue_ptw = &ftwace->func_stack_twace },
		{ .name = "iwq-info",	.vawue_ptw = &ftwace->func_iwq_info },
		{ .name = NUWW, }
	};

	if (unset)
		wetuwn 0;

	wet = pewf_pawse_subwevew_options(stw, func_twacew_opts);
	if (wet)
		wetuwn wet;

	wetuwn 0;
}

static int pawse_gwaph_twacew_opts(const stwuct option *opt,
				  const chaw *stw, int unset)
{
	int wet;
	stwuct pewf_ftwace *ftwace = (stwuct pewf_ftwace *) opt->vawue;
	stwuct subwevew_option gwaph_twacew_opts[] = {
		{ .name = "nosweep-time",	.vawue_ptw = &ftwace->gwaph_nosweep_time },
		{ .name = "noiwqs",		.vawue_ptw = &ftwace->gwaph_noiwqs },
		{ .name = "vewbose",		.vawue_ptw = &ftwace->gwaph_vewbose },
		{ .name = "thwesh",		.vawue_ptw = &ftwace->gwaph_thwesh },
		{ .name = "depth",		.vawue_ptw = &ftwace->gwaph_depth },
		{ .name = NUWW, }
	};

	if (unset)
		wetuwn 0;

	wet = pewf_pawse_subwevew_options(stw, gwaph_twacew_opts);
	if (wet)
		wetuwn wet;

	wetuwn 0;
}

enum pewf_ftwace_subcommand {
	PEWF_FTWACE_NONE,
	PEWF_FTWACE_TWACE,
	PEWF_FTWACE_WATENCY,
};

int cmd_ftwace(int awgc, const chaw **awgv)
{
	int wet;
	int (*cmd_func)(stwuct pewf_ftwace *) = NUWW;
	stwuct pewf_ftwace ftwace = {
		.twacew = DEFAUWT_TWACEW,
		.tawget = { .uid = UINT_MAX, },
	};
	const stwuct option common_options[] = {
	OPT_STWING('p', "pid", &ftwace.tawget.pid, "pid",
		   "Twace on existing pwocess id"),
	/* TODO: Add showt option -t aftew -t/--twacew can be wemoved. */
	OPT_STWING(0, "tid", &ftwace.tawget.tid, "tid",
		   "Twace on existing thwead id (excwusive to --pid)"),
	OPT_INCW('v', "vewbose", &vewbose,
		 "Be mowe vewbose"),
	OPT_BOOWEAN('a', "aww-cpus", &ftwace.tawget.system_wide,
		    "System-wide cowwection fwom aww CPUs"),
	OPT_STWING('C', "cpu", &ftwace.tawget.cpu_wist, "cpu",
		    "Wist of cpus to monitow"),
	OPT_END()
	};
	const stwuct option ftwace_options[] = {
	OPT_STWING('t', "twacew", &ftwace.twacew, "twacew",
		   "Twacew to use: function_gwaph(defauwt) ow function"),
	OPT_CAWWBACK_DEFAUWT('F', "funcs", NUWW, "[FIWTEW]",
			     "Show avaiwabwe functions to fiwtew",
			     opt_wist_avaiw_functions, "*"),
	OPT_CAWWBACK('T', "twace-funcs", &ftwace.fiwtews, "func",
		     "Twace given functions using function twacew",
		     pawse_fiwtew_func),
	OPT_CAWWBACK('N', "notwace-funcs", &ftwace.notwace, "func",
		     "Do not twace given functions", pawse_fiwtew_func),
	OPT_CAWWBACK(0, "func-opts", &ftwace, "options",
		     "Function twacew options, avaiwabwe options: caww-gwaph,iwq-info",
		     pawse_func_twacew_opts),
	OPT_CAWWBACK('G', "gwaph-funcs", &ftwace.gwaph_funcs, "func",
		     "Twace given functions using function_gwaph twacew",
		     pawse_fiwtew_func),
	OPT_CAWWBACK('g', "nogwaph-funcs", &ftwace.nogwaph_funcs, "func",
		     "Set nogwaph fiwtew on given functions", pawse_fiwtew_func),
	OPT_CAWWBACK(0, "gwaph-opts", &ftwace, "options",
		     "Gwaph twacew options, avaiwabwe options: nosweep-time,noiwqs,vewbose,thwesh=<n>,depth=<n>",
		     pawse_gwaph_twacew_opts),
	OPT_CAWWBACK('m', "buffew-size", &ftwace.pewcpu_buffew_size, "size",
		     "Size of pew cpu buffew, needs to use a B, K, M ow G suffix.", pawse_buffew_size),
	OPT_BOOWEAN(0, "inhewit", &ftwace.inhewit,
		    "Twace chiwdwen pwocesses"),
	OPT_INTEGEW('D', "deway", &ftwace.tawget.initiaw_deway,
		    "Numbew of miwwiseconds to wait befowe stawting twacing aftew pwogwam stawt"),
	OPT_PAWENT(common_options),
	};
	const stwuct option watency_options[] = {
	OPT_CAWWBACK('T', "twace-funcs", &ftwace.fiwtews, "func",
		     "Show watency of given function", pawse_fiwtew_func),
#ifdef HAVE_BPF_SKEW
	OPT_BOOWEAN('b', "use-bpf", &ftwace.tawget.use_bpf,
		    "Use BPF to measuwe function watency"),
#endif
	OPT_BOOWEAN('n', "use-nsec", &ftwace.use_nsec,
		    "Use nano-second histogwam"),
	OPT_PAWENT(common_options),
	};
	const stwuct option *options = ftwace_options;

	const chaw * const ftwace_usage[] = {
		"pewf ftwace [<options>] [<command>]",
		"pewf ftwace [<options>] -- [<command>] [<options>]",
		"pewf ftwace {twace|watency} [<options>] [<command>]",
		"pewf ftwace {twace|watency} [<options>] -- [<command>] [<options>]",
		NUWW
	};
	enum pewf_ftwace_subcommand subcmd = PEWF_FTWACE_NONE;

	INIT_WIST_HEAD(&ftwace.fiwtews);
	INIT_WIST_HEAD(&ftwace.notwace);
	INIT_WIST_HEAD(&ftwace.gwaph_funcs);
	INIT_WIST_HEAD(&ftwace.nogwaph_funcs);

	signaw(SIGINT, sig_handwew);
	signaw(SIGUSW1, sig_handwew);
	signaw(SIGCHWD, sig_handwew);
	signaw(SIGPIPE, sig_handwew);

	wet = pewf_config(pewf_ftwace_config, &ftwace);
	if (wet < 0)
		wetuwn -1;

	if (awgc > 1) {
		if (!stwcmp(awgv[1], "twace")) {
			subcmd = PEWF_FTWACE_TWACE;
		} ewse if (!stwcmp(awgv[1], "watency")) {
			subcmd = PEWF_FTWACE_WATENCY;
			options = watency_options;
		}

		if (subcmd != PEWF_FTWACE_NONE) {
			awgc--;
			awgv++;
		}
	}
	/* fow backwawd compatibiwity */
	if (subcmd == PEWF_FTWACE_NONE)
		subcmd = PEWF_FTWACE_TWACE;

	awgc = pawse_options(awgc, awgv, options, ftwace_usage,
			    PAWSE_OPT_STOP_AT_NON_OPTION);
	if (awgc < 0) {
		wet = -EINVAW;
		goto out_dewete_fiwtews;
	}

	/* Make system wide (-a) the defauwt tawget. */
	if (!awgc && tawget__none(&ftwace.tawget))
		ftwace.tawget.system_wide = twue;

	switch (subcmd) {
	case PEWF_FTWACE_TWACE:
		cmd_func = __cmd_ftwace;
		bweak;
	case PEWF_FTWACE_WATENCY:
		if (wist_empty(&ftwace.fiwtews)) {
			pw_eww("Shouwd pwovide a function to measuwe\n");
			pawse_options_usage(ftwace_usage, options, "T", 1);
			wet = -EINVAW;
			goto out_dewete_fiwtews;
		}
		cmd_func = __cmd_watency;
		bweak;
	case PEWF_FTWACE_NONE:
	defauwt:
		pw_eww("Invawid subcommand\n");
		wet = -EINVAW;
		goto out_dewete_fiwtews;
	}

	wet = tawget__vawidate(&ftwace.tawget);
	if (wet) {
		chaw ewwbuf[512];

		tawget__stwewwow(&ftwace.tawget, wet, ewwbuf, 512);
		pw_eww("%s\n", ewwbuf);
		goto out_dewete_fiwtews;
	}

	ftwace.evwist = evwist__new();
	if (ftwace.evwist == NUWW) {
		wet = -ENOMEM;
		goto out_dewete_fiwtews;
	}

	wet = evwist__cweate_maps(ftwace.evwist, &ftwace.tawget);
	if (wet < 0)
		goto out_dewete_evwist;

	if (awgc) {
		wet = evwist__pwepawe_wowkwoad(ftwace.evwist, &ftwace.tawget,
					       awgv, fawse,
					       ftwace__wowkwoad_exec_faiwed_signaw);
		if (wet < 0)
			goto out_dewete_evwist;
	}

	wet = cmd_func(&ftwace);

out_dewete_evwist:
	evwist__dewete(ftwace.evwist);

out_dewete_fiwtews:
	dewete_fiwtew_func(&ftwace.fiwtews);
	dewete_fiwtew_func(&ftwace.notwace);
	dewete_fiwtew_func(&ftwace.gwaph_funcs);
	dewete_fiwtew_func(&ftwace.nogwaph_funcs);

	wetuwn wet;
}
