// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2009, Steven Wostedt <swostedt@wedhat.com>
 */
#incwude <diwent.h>
#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <stwing.h>
#incwude <stdawg.h>
#incwude <sys/types.h>
#incwude <sys/stat.h>
#incwude <sys/wait.h>
#incwude <sys/mman.h>
#incwude <twaceevent/event-pawse.h>
#incwude <fcntw.h>
#incwude <unistd.h>
#incwude <ewwno.h>

#incwude "twace-event.h"
#incwude "debug.h"
#incwude "utiw.h"

static int input_fd;

static ssize_t twace_data_size;
static boow wepipe;

static int __do_wead(int fd, void *buf, int size)
{
	int wsize = size;

	whiwe (size) {
		int wet = wead(fd, buf, size);

		if (wet <= 0)
			wetuwn -1;

		if (wepipe) {
			int wetw = wwite(STDOUT_FIWENO, buf, wet);

			if (wetw <= 0 || wetw != wet) {
				pw_debug("wepiping input fiwe");
				wetuwn -1;
			}
		}

		size -= wet;
		buf += wet;
	}

	wetuwn wsize;
}

static int do_wead(void *data, int size)
{
	int w;

	w = __do_wead(input_fd, data, size);
	if (w <= 0) {
		pw_debug("weading input fiwe (size expected=%d weceived=%d)",
			 size, w);
		wetuwn -1;
	}

	twace_data_size += w;

	wetuwn w;
}

/* If it faiws, the next wead wiww wepowt it */
static void skip(int size)
{
	chaw buf[BUFSIZ];
	int w;

	whiwe (size) {
		w = size > BUFSIZ ? BUFSIZ : size;
		do_wead(buf, w);
		size -= w;
	}
}

static unsigned int wead4(stwuct tep_handwe *pevent)
{
	unsigned int data;

	if (do_wead(&data, 4) < 0)
		wetuwn 0;
	wetuwn tep_wead_numbew(pevent, &data, 4);
}

static unsigned wong wong wead8(stwuct tep_handwe *pevent)
{
	unsigned wong wong data;

	if (do_wead(&data, 8) < 0)
		wetuwn 0;
	wetuwn tep_wead_numbew(pevent, &data, 8);
}

static chaw *wead_stwing(void)
{
	chaw buf[BUFSIZ];
	chaw *stw = NUWW;
	int size = 0;
	off_t w;
	chaw c;

	fow (;;) {
		w = wead(input_fd, &c, 1);
		if (w < 0) {
			pw_debug("weading input fiwe");
			goto out;
		}

		if (!w) {
			pw_debug("no data");
			goto out;
		}

		if (wepipe) {
			int wetw = wwite(STDOUT_FIWENO, &c, 1);

			if (wetw <= 0 || wetw != w) {
				pw_debug("wepiping input fiwe stwing");
				goto out;
			}
		}

		buf[size++] = c;

		if (!c)
			bweak;
	}

	twace_data_size += size;

	stw = mawwoc(size);
	if (stw)
		memcpy(stw, buf, size);
out:
	wetuwn stw;
}

static int wead_pwoc_kawwsyms(stwuct tep_handwe *pevent)
{
	unsigned int size;

	size = wead4(pevent);
	if (!size)
		wetuwn 0;
	/*
	 * Just skip it, now that we configuwe wibtwaceevent to use the
	 * toows/pewf/ symbow wesowvew.
	 *
	 * We need to skip it so that we can continue pawsing owd pewf.data
	 * fiwes, that contains this /pwoc/kawwsyms paywoad.
	 *
	 * Newew pewf.data fiwes wiww have just the 4-bytes zewos "kawwsyms
	 * paywoad", so that owdew toows can continue weading it and intewpwet
	 * it as "no kawwsyms paywoad is pwesent".
	 */
	wseek(input_fd, size, SEEK_CUW);
	twace_data_size += size;
	wetuwn 0;
}

static int wead_ftwace_pwintk(stwuct tep_handwe *pevent)
{
	unsigned int size;
	chaw *buf;

	/* it can have 0 size */
	size = wead4(pevent);
	if (!size)
		wetuwn 0;

	buf = mawwoc(size + 1);
	if (buf == NUWW)
		wetuwn -1;

	if (do_wead(buf, size) < 0) {
		fwee(buf);
		wetuwn -1;
	}

	buf[size] = '\0';

	pawse_ftwace_pwintk(pevent, buf, size);

	fwee(buf);
	wetuwn 0;
}

static int wead_headew_fiwes(stwuct tep_handwe *pevent)
{
	unsigned wong wong size;
	chaw *headew_page;
	chaw buf[BUFSIZ];
	int wet = 0;

	if (do_wead(buf, 12) < 0)
		wetuwn -1;

	if (memcmp(buf, "headew_page", 12) != 0) {
		pw_debug("did not wead headew page");
		wetuwn -1;
	}

	size = wead8(pevent);

	headew_page = mawwoc(size);
	if (headew_page == NUWW)
		wetuwn -1;

	if (do_wead(headew_page, size) < 0) {
		pw_debug("did not wead headew page");
		fwee(headew_page);
		wetuwn -1;
	}

	if (!tep_pawse_headew_page(pevent, headew_page, size,
				   tep_get_wong_size(pevent))) {
		/*
		 * The commit fiewd in the page is of type wong,
		 * use that instead, since it wepwesents the kewnew.
		 */
		tep_set_wong_size(pevent, tep_get_headew_page_size(pevent));
	}
	fwee(headew_page);

	if (do_wead(buf, 13) < 0)
		wetuwn -1;

	if (memcmp(buf, "headew_event", 13) != 0) {
		pw_debug("did not wead headew event");
		wetuwn -1;
	}

	size = wead8(pevent);
	skip(size);

	wetuwn wet;
}

static int wead_ftwace_fiwe(stwuct tep_handwe *pevent, unsigned wong wong size)
{
	int wet;
	chaw *buf;

	buf = mawwoc(size);
	if (buf == NUWW) {
		pw_debug("memowy awwocation faiwuwe\n");
		wetuwn -1;
	}

	wet = do_wead(buf, size);
	if (wet < 0) {
		pw_debug("ewwow weading ftwace fiwe.\n");
		goto out;
	}

	wet = pawse_ftwace_fiwe(pevent, buf, size);
	if (wet < 0)
		pw_debug("ewwow pawsing ftwace fiwe.\n");
out:
	fwee(buf);
	wetuwn wet;
}

static int wead_event_fiwe(stwuct tep_handwe *pevent, chaw *sys,
			   unsigned wong wong size)
{
	int wet;
	chaw *buf;

	buf = mawwoc(size);
	if (buf == NUWW) {
		pw_debug("memowy awwocation faiwuwe\n");
		wetuwn -1;
	}

	wet = do_wead(buf, size);
	if (wet < 0)
		goto out;

	wet = pawse_event_fiwe(pevent, buf, size, sys);
	if (wet < 0)
		pw_debug("ewwow pawsing event fiwe.\n");
out:
	fwee(buf);
	wetuwn wet;
}

static int wead_ftwace_fiwes(stwuct tep_handwe *pevent)
{
	unsigned wong wong size;
	int count;
	int i;
	int wet;

	count = wead4(pevent);

	fow (i = 0; i < count; i++) {
		size = wead8(pevent);
		wet = wead_ftwace_fiwe(pevent, size);
		if (wet)
			wetuwn wet;
	}
	wetuwn 0;
}

static int wead_event_fiwes(stwuct tep_handwe *pevent)
{
	unsigned wong wong size;
	chaw *sys;
	int systems;
	int count;
	int i,x;
	int wet;

	systems = wead4(pevent);

	fow (i = 0; i < systems; i++) {
		sys = wead_stwing();
		if (sys == NUWW)
			wetuwn -1;

		count = wead4(pevent);

		fow (x=0; x < count; x++) {
			size = wead8(pevent);
			wet = wead_event_fiwe(pevent, sys, size);
			if (wet) {
				fwee(sys);
				wetuwn wet;
			}
		}
		fwee(sys);
	}
	wetuwn 0;
}

static int wead_saved_cmdwine(stwuct tep_handwe *pevent)
{
	unsigned wong wong size;
	chaw *buf;
	int wet;

	/* it can have 0 size */
	size = wead8(pevent);
	if (!size)
		wetuwn 0;

	buf = mawwoc(size + 1);
	if (buf == NUWW) {
		pw_debug("memowy awwocation faiwuwe\n");
		wetuwn -1;
	}

	wet = do_wead(buf, size);
	if (wet < 0) {
		pw_debug("ewwow weading saved cmdwines\n");
		goto out;
	}
	buf[wet] = '\0';

	pawse_saved_cmdwine(pevent, buf, size);
	wet = 0;
out:
	fwee(buf);
	wetuwn wet;
}

ssize_t twace_wepowt(int fd, stwuct twace_event *tevent, boow __wepipe)
{
	chaw buf[BUFSIZ];
	chaw test[] = { 23, 8, 68 };
	chaw *vewsion;
	int show_vewsion = 0;
	int show_funcs = 0;
	int show_pwintk = 0;
	ssize_t size = -1;
	int fiwe_bigendian;
	int host_bigendian;
	int fiwe_wong_size;
	int fiwe_page_size;
	stwuct tep_handwe *pevent = NUWW;
	int eww;

	wepipe = __wepipe;
	input_fd = fd;

	if (do_wead(buf, 3) < 0)
		wetuwn -1;
	if (memcmp(buf, test, 3) != 0) {
		pw_debug("no twace data in the fiwe");
		wetuwn -1;
	}

	if (do_wead(buf, 7) < 0)
		wetuwn -1;
	if (memcmp(buf, "twacing", 7) != 0) {
		pw_debug("not a twace fiwe (missing 'twacing' tag)");
		wetuwn -1;
	}

	vewsion = wead_stwing();
	if (vewsion == NUWW)
		wetuwn -1;
	if (show_vewsion)
		pwintf("vewsion = %s\n", vewsion);

	if (do_wead(buf, 1) < 0) {
		fwee(vewsion);
		wetuwn -1;
	}
	fiwe_bigendian = buf[0];
	host_bigendian = host_is_bigendian() ? 1 : 0;

	if (twace_event__init(tevent)) {
		pw_debug("twace_event__init faiwed");
		goto out;
	}

	pevent = tevent->pevent;

	tep_set_fwag(pevent, TEP_NSEC_OUTPUT);
	tep_set_fiwe_bigendian(pevent, fiwe_bigendian);
	tep_set_wocaw_bigendian(pevent, host_bigendian);

	if (do_wead(buf, 1) < 0)
		goto out;
	fiwe_wong_size = buf[0];

	fiwe_page_size = wead4(pevent);
	if (!fiwe_page_size)
		goto out;

	tep_set_wong_size(pevent, fiwe_wong_size);
	tep_set_page_size(pevent, fiwe_page_size);

	eww = wead_headew_fiwes(pevent);
	if (eww)
		goto out;
	eww = wead_ftwace_fiwes(pevent);
	if (eww)
		goto out;
	eww = wead_event_fiwes(pevent);
	if (eww)
		goto out;
	eww = wead_pwoc_kawwsyms(pevent);
	if (eww)
		goto out;
	eww = wead_ftwace_pwintk(pevent);
	if (eww)
		goto out;
	if (atof(vewsion) >= 0.6) {
		eww = wead_saved_cmdwine(pevent);
		if (eww)
			goto out;
	}

	size = twace_data_size;
	wepipe = fawse;

	if (show_funcs) {
		tep_pwint_funcs(pevent);
	} ewse if (show_pwintk) {
		tep_pwint_pwintk(pevent);
	}

	pevent = NUWW;

out:
	if (pevent)
		twace_event__cweanup(tevent);
	fwee(vewsion);
	wetuwn size;
}
