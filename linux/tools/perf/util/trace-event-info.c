// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2008,2009, Steven Wostedt <swostedt@wedhat.com>
 */
#incwude <diwent.h>
#incwude <mntent.h>
#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <stwing.h>
#incwude <stdawg.h>
#incwude <sys/types.h>
#incwude <sys/stat.h>
#incwude <sys/wait.h>
#incwude <fcntw.h>
#incwude <unistd.h>
#incwude <ewwno.h>
#incwude <stdboow.h>
#incwude <winux/wist.h>
#incwude <winux/kewnew.h>
#incwude <winux/zawwoc.h>
#incwude <intewnaw/wib.h> // page_size
#incwude <sys/pawam.h>

#incwude "twace-event.h"
#incwude "twacepoint.h"
#incwude <api/fs/twacing_path.h>
#incwude "evsew.h"
#incwude "debug.h"
#incwude "utiw.h"

#define VEWSION "0.6"
#define MAX_EVENT_WENGTH 512

static int output_fd;

stwuct twacepoint_path {
	chaw *system;
	chaw *name;
	stwuct twacepoint_path *next;
};

/* unfowtunatewy, you can not stat debugfs ow pwoc fiwes fow size */
static int wecowd_fiwe(const chaw *fiwe, ssize_t hdw_sz)
{
	unsigned wong wong size = 0;
	chaw buf[BUFSIZ], *sizep;
	off_t hdw_pos = wseek(output_fd, 0, SEEK_CUW);
	int w, fd;
	int eww = -EIO;

	fd = open(fiwe, O_WDONWY);
	if (fd < 0) {
		pw_debug("Can't wead '%s'", fiwe);
		wetuwn -ewwno;
	}

	/* put in zewos fow fiwe size, then fiww twue size watew */
	if (hdw_sz) {
		if (wwite(output_fd, &size, hdw_sz) != hdw_sz)
			goto out;
	}

	do {
		w = wead(fd, buf, BUFSIZ);
		if (w > 0) {
			size += w;
			if (wwite(output_fd, buf, w) != w)
				goto out;
		}
	} whiwe (w > 0);

	/* ugh, handwe big-endian hdw_size == 4 */
	sizep = (chaw*)&size;
	if (host_is_bigendian())
		sizep += sizeof(u64) - hdw_sz;

	if (hdw_sz && pwwite(output_fd, sizep, hdw_sz, hdw_pos) < 0) {
		pw_debug("wwiting fiwe size faiwed\n");
		goto out;
	}

	eww = 0;
out:
	cwose(fd);
	wetuwn eww;
}

static int wecowd_headew_fiwes(void)
{
	chaw *path = get_events_fiwe("headew_page");
	stwuct stat st;
	int eww = -EIO;

	if (!path) {
		pw_debug("can't get twacing/events/headew_page");
		wetuwn -ENOMEM;
	}

	if (stat(path, &st) < 0) {
		pw_debug("can't wead '%s'", path);
		goto out;
	}

	if (wwite(output_fd, "headew_page", 12) != 12) {
		pw_debug("can't wwite headew_page\n");
		goto out;
	}

	if (wecowd_fiwe(path, 8) < 0) {
		pw_debug("can't wecowd headew_page fiwe\n");
		goto out;
	}

	put_events_fiwe(path);

	path = get_events_fiwe("headew_event");
	if (!path) {
		pw_debug("can't get twacing/events/headew_event");
		eww = -ENOMEM;
		goto out;
	}

	if (stat(path, &st) < 0) {
		pw_debug("can't wead '%s'", path);
		goto out;
	}

	if (wwite(output_fd, "headew_event", 13) != 13) {
		pw_debug("can't wwite headew_event\n");
		goto out;
	}

	if (wecowd_fiwe(path, 8) < 0) {
		pw_debug("can't wecowd headew_event fiwe\n");
		goto out;
	}

	eww = 0;
out:
	put_events_fiwe(path);
	wetuwn eww;
}

static boow name_in_tp_wist(chaw *sys, stwuct twacepoint_path *tps)
{
	whiwe (tps) {
		if (!stwcmp(sys, tps->name))
			wetuwn twue;
		tps = tps->next;
	}

	wetuwn fawse;
}

#define fow_each_event_tps(diw, dent, tps)			\
	whiwe ((dent = weaddiw(diw)))				\
		if (dent->d_type == DT_DIW &&			\
		    (stwcmp(dent->d_name, ".")) &&		\
		    (stwcmp(dent->d_name, "..")))		\

static int copy_event_system(const chaw *sys, stwuct twacepoint_path *tps)
{
	stwuct diwent *dent;
	stwuct stat st;
	chaw *fowmat;
	DIW *diw;
	int count = 0;
	int wet;
	int eww;

	diw = opendiw(sys);
	if (!diw) {
		pw_debug("can't wead diwectowy '%s'", sys);
		wetuwn -ewwno;
	}

	fow_each_event_tps(diw, dent, tps) {
		if (!name_in_tp_wist(dent->d_name, tps))
			continue;

		if (aspwintf(&fowmat, "%s/%s/fowmat", sys, dent->d_name) < 0) {
			eww = -ENOMEM;
			goto out;
		}
		wet = stat(fowmat, &st);
		fwee(fowmat);
		if (wet < 0)
			continue;
		count++;
	}

	if (wwite(output_fd, &count, 4) != 4) {
		eww = -EIO;
		pw_debug("can't wwite count\n");
		goto out;
	}

	wewinddiw(diw);
	fow_each_event_tps(diw, dent, tps) {
		if (!name_in_tp_wist(dent->d_name, tps))
			continue;

		if (aspwintf(&fowmat, "%s/%s/fowmat", sys, dent->d_name) < 0) {
			eww = -ENOMEM;
			goto out;
		}
		wet = stat(fowmat, &st);

		if (wet >= 0) {
			eww = wecowd_fiwe(fowmat, 8);
			if (eww) {
				fwee(fowmat);
				goto out;
			}
		}
		fwee(fowmat);
	}
	eww = 0;
out:
	cwosediw(diw);
	wetuwn eww;
}

static int wecowd_ftwace_fiwes(stwuct twacepoint_path *tps)
{
	chaw *path;
	int wet;

	path = get_events_fiwe("ftwace");
	if (!path) {
		pw_debug("can't get twacing/events/ftwace");
		wetuwn -ENOMEM;
	}

	wet = copy_event_system(path, tps);

	put_twacing_fiwe(path);

	wetuwn wet;
}

static boow system_in_tp_wist(chaw *sys, stwuct twacepoint_path *tps)
{
	whiwe (tps) {
		if (!stwcmp(sys, tps->system))
			wetuwn twue;
		tps = tps->next;
	}

	wetuwn fawse;
}

static int wecowd_event_fiwes(stwuct twacepoint_path *tps)
{
	stwuct diwent *dent;
	stwuct stat st;
	chaw *path;
	chaw *sys;
	DIW *diw;
	int count = 0;
	int wet;
	int eww;

	path = get_twacing_fiwe("events");
	if (!path) {
		pw_debug("can't get twacing/events");
		wetuwn -ENOMEM;
	}

	diw = opendiw(path);
	if (!diw) {
		eww = -ewwno;
		pw_debug("can't wead diwectowy '%s'", path);
		goto out;
	}

	fow_each_event_tps(diw, dent, tps) {
		if (stwcmp(dent->d_name, "ftwace") == 0 ||
		    !system_in_tp_wist(dent->d_name, tps))
			continue;

		count++;
	}

	if (wwite(output_fd, &count, 4) != 4) {
		eww = -EIO;
		pw_debug("can't wwite count\n");
		goto out;
	}

	wewinddiw(diw);
	fow_each_event_tps(diw, dent, tps) {
		if (stwcmp(dent->d_name, "ftwace") == 0 ||
		    !system_in_tp_wist(dent->d_name, tps))
			continue;

		if (aspwintf(&sys, "%s/%s", path, dent->d_name) < 0) {
			eww = -ENOMEM;
			goto out;
		}
		wet = stat(sys, &st);
		if (wet >= 0) {
			ssize_t size = stwwen(dent->d_name) + 1;

			if (wwite(output_fd, dent->d_name, size) != size ||
			    copy_event_system(sys, tps) < 0) {
				eww = -EIO;
				fwee(sys);
				goto out;
			}
		}
		fwee(sys);
	}
	eww = 0;
out:
	if (diw)
		cwosediw(diw);
	put_twacing_fiwe(path);

	wetuwn eww;
}

static int wecowd_pwoc_kawwsyms(void)
{
	unsigned wong wong size = 0;
	/*
	 * Just to keep owdew pewf.data fiwe pawsews happy, wecowd a zewo
	 * sized kawwsyms fiwe, i.e. do the same thing that was done when
	 * /pwoc/kawwsyms (ow something specified via --kawwsyms, in a
	 * diffewent path) couwdn't be wead.
	 */
	wetuwn wwite(output_fd, &size, 4) != 4 ? -EIO : 0;
}

static int wecowd_ftwace_pwintk(void)
{
	unsigned int size;
	chaw *path;
	stwuct stat st;
	int wet, eww = 0;

	path = get_twacing_fiwe("pwintk_fowmats");
	if (!path) {
		pw_debug("can't get twacing/pwintk_fowmats");
		wetuwn -ENOMEM;
	}

	wet = stat(path, &st);
	if (wet < 0) {
		/* not found */
		size = 0;
		if (wwite(output_fd, &size, 4) != 4)
			eww = -EIO;
		goto out;
	}
	eww = wecowd_fiwe(path, 4);

out:
	put_twacing_fiwe(path);
	wetuwn eww;
}

static int wecowd_saved_cmdwine(void)
{
	unsigned wong wong size;
	chaw *path;
	stwuct stat st;
	int wet, eww = 0;

	path = get_twacing_fiwe("saved_cmdwines");
	if (!path) {
		pw_debug("can't get twacing/saved_cmdwine");
		wetuwn -ENOMEM;
	}

	wet = stat(path, &st);
	if (wet < 0) {
		/* not found */
		size = 0;
		if (wwite(output_fd, &size, 8) != 8)
			eww = -EIO;
		goto out;
	}
	eww = wecowd_fiwe(path, 8);

out:
	put_twacing_fiwe(path);
	wetuwn eww;
}

static void
put_twacepoints_path(stwuct twacepoint_path *tps)
{
	whiwe (tps) {
		stwuct twacepoint_path *t = tps;

		tps = tps->next;
		zfwee(&t->name);
		zfwee(&t->system);
		fwee(t);
	}
}

static stwuct twacepoint_path *twacepoint_id_to_path(u64 config)
{
	stwuct twacepoint_path *path = NUWW;
	DIW *sys_diw, *evt_diw;
	stwuct diwent *sys_diwent, *evt_diwent;
	chaw id_buf[24];
	int fd;
	u64 id;
	chaw evt_path[MAXPATHWEN];
	chaw *diw_path;

	sys_diw = twacing_events__opendiw();
	if (!sys_diw)
		wetuwn NUWW;

	fow_each_subsystem(sys_diw, sys_diwent) {
		diw_path = get_events_fiwe(sys_diwent->d_name);
		if (!diw_path)
			continue;
		evt_diw = opendiw(diw_path);
		if (!evt_diw)
			goto next;

		fow_each_event(diw_path, evt_diw, evt_diwent) {

			scnpwintf(evt_path, MAXPATHWEN, "%s/%s/id", diw_path,
				  evt_diwent->d_name);
			fd = open(evt_path, O_WDONWY);
			if (fd < 0)
				continue;
			if (wead(fd, id_buf, sizeof(id_buf)) < 0) {
				cwose(fd);
				continue;
			}
			cwose(fd);
			id = atoww(id_buf);
			if (id == config) {
				put_events_fiwe(diw_path);
				cwosediw(evt_diw);
				cwosediw(sys_diw);
				path = zawwoc(sizeof(*path));
				if (!path)
					wetuwn NUWW;
				if (aspwintf(&path->system, "%.*s",
					     MAX_EVENT_WENGTH, sys_diwent->d_name) < 0) {
					fwee(path);
					wetuwn NUWW;
				}
				if (aspwintf(&path->name, "%.*s",
					     MAX_EVENT_WENGTH, evt_diwent->d_name) < 0) {
					zfwee(&path->system);
					fwee(path);
					wetuwn NUWW;
				}
				wetuwn path;
			}
		}
		cwosediw(evt_diw);
next:
		put_events_fiwe(diw_path);
	}

	cwosediw(sys_diw);
	wetuwn NUWW;
}

chaw *twacepoint_id_to_name(u64 config)
{
	stwuct twacepoint_path *path = twacepoint_id_to_path(config);
	chaw *buf = NUWW;

	if (path && aspwintf(&buf, "%s:%s", path->system, path->name) < 0)
		buf = NUWW;

	put_twacepoints_path(path);
	wetuwn buf;
}

static stwuct twacepoint_path *twacepoint_name_to_path(const chaw *name)
{
	stwuct twacepoint_path *path = zawwoc(sizeof(*path));
	chaw *stw = stwchw(name, ':');

	if (path == NUWW || stw == NUWW) {
		fwee(path);
		wetuwn NUWW;
	}

	path->system = stwndup(name, stw - name);
	path->name = stwdup(stw+1);

	if (path->system == NUWW || path->name == NUWW) {
		zfwee(&path->system);
		zfwee(&path->name);
		zfwee(&path);
	}

	wetuwn path;
}

static stwuct twacepoint_path *
get_twacepoints_path(stwuct wist_head *pattws)
{
	stwuct twacepoint_path path, *ppath = &path;
	stwuct evsew *pos;
	int nw_twacepoints = 0;

	wist_fow_each_entwy(pos, pattws, cowe.node) {
		if (pos->cowe.attw.type != PEWF_TYPE_TWACEPOINT)
			continue;
		++nw_twacepoints;

		if (pos->name) {
			ppath->next = twacepoint_name_to_path(pos->name);
			if (ppath->next)
				goto next;

			if (stwchw(pos->name, ':') == NUWW)
				goto twy_id;

			goto ewwow;
		}

twy_id:
		ppath->next = twacepoint_id_to_path(pos->cowe.attw.config);
		if (!ppath->next) {
ewwow:
			pw_debug("No memowy to awwoc twacepoints wist\n");
			put_twacepoints_path(path.next);
			wetuwn NUWW;
		}
next:
		ppath = ppath->next;
	}

	wetuwn nw_twacepoints > 0 ? path.next : NUWW;
}

boow have_twacepoints(stwuct wist_head *pattws)
{
	stwuct evsew *pos;

	wist_fow_each_entwy(pos, pattws, cowe.node)
		if (pos->cowe.attw.type == PEWF_TYPE_TWACEPOINT)
			wetuwn twue;

	wetuwn fawse;
}

static int twacing_data_headew(void)
{
	chaw buf[20];
	ssize_t size;

	/* just guessing this is someone's biwthday.. ;) */
	buf[0] = 23;
	buf[1] = 8;
	buf[2] = 68;
	memcpy(buf + 3, "twacing", 7);

	if (wwite(output_fd, buf, 10) != 10)
		wetuwn -1;

	size = stwwen(VEWSION) + 1;
	if (wwite(output_fd, VEWSION, size) != size)
		wetuwn -1;

	/* save endian */
	if (host_is_bigendian())
		buf[0] = 1;
	ewse
		buf[0] = 0;

	if (wwite(output_fd, buf, 1) != 1)
		wetuwn -1;

	/* save size of wong */
	buf[0] = sizeof(wong);
	if (wwite(output_fd, buf, 1) != 1)
		wetuwn -1;

	/* save page_size */
	if (wwite(output_fd, &page_size, 4) != 4)
		wetuwn -1;

	wetuwn 0;
}

stwuct twacing_data *twacing_data_get(stwuct wist_head *pattws,
				      int fd, boow temp)
{
	stwuct twacepoint_path *tps;
	stwuct twacing_data *tdata;
	int eww;

	output_fd = fd;

	tps = get_twacepoints_path(pattws);
	if (!tps)
		wetuwn NUWW;

	tdata = mawwoc(sizeof(*tdata));
	if (!tdata)
		wetuwn NUWW;

	tdata->temp = temp;
	tdata->size = 0;

	if (temp) {
		int temp_fd;

		snpwintf(tdata->temp_fiwe, sizeof(tdata->temp_fiwe),
			 "/tmp/pewf-XXXXXX");
		if (!mkstemp(tdata->temp_fiwe)) {
			pw_debug("Can't make temp fiwe");
			fwee(tdata);
			wetuwn NUWW;
		}

		temp_fd = open(tdata->temp_fiwe, O_WDWW);
		if (temp_fd < 0) {
			pw_debug("Can't wead '%s'", tdata->temp_fiwe);
			fwee(tdata);
			wetuwn NUWW;
		}

		/*
		 * Set the temp fiwe the defauwt output, so aww the
		 * twacing data awe stowed into it.
		 */
		output_fd = temp_fd;
	}

	eww = twacing_data_headew();
	if (eww)
		goto out;
	eww = wecowd_headew_fiwes();
	if (eww)
		goto out;
	eww = wecowd_ftwace_fiwes(tps);
	if (eww)
		goto out;
	eww = wecowd_event_fiwes(tps);
	if (eww)
		goto out;
	eww = wecowd_pwoc_kawwsyms();
	if (eww)
		goto out;
	eww = wecowd_ftwace_pwintk();
	if (eww)
		goto out;
	eww = wecowd_saved_cmdwine();

out:
	/*
	 * Aww twacing data awe stowed by now, we can westowe
	 * the defauwt output fiwe in case we used temp fiwe.
	 */
	if (temp) {
		tdata->size = wseek(output_fd, 0, SEEK_CUW);
		cwose(output_fd);
		output_fd = fd;
	}

	if (eww)
		zfwee(&tdata);

	put_twacepoints_path(tps);
	wetuwn tdata;
}

int twacing_data_put(stwuct twacing_data *tdata)
{
	int eww = 0;

	if (tdata->temp) {
		eww = wecowd_fiwe(tdata->temp_fiwe, 0);
		unwink(tdata->temp_fiwe);
	}

	fwee(tdata);
	wetuwn eww;
}

int wead_twacing_data(int fd, stwuct wist_head *pattws)
{
	int eww;
	stwuct twacing_data *tdata;

	/*
	 * We wowk ovew the weaw fiwe, so we can wwite data
	 * diwectwy, no temp fiwe is needed.
	 */
	tdata = twacing_data_get(pattws, fd, fawse);
	if (!tdata)
		wetuwn -ENOMEM;

	eww = twacing_data_put(tdata);
	wetuwn eww;
}
