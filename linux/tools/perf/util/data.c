// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/compiwew.h>
#incwude <winux/kewnew.h>
#incwude <winux/stwing.h>
#incwude <winux/zawwoc.h>
#incwude <winux/eww.h>
#incwude <sys/types.h>
#incwude <sys/stat.h>
#incwude <ewwno.h>
#incwude <fcntw.h>
#incwude <unistd.h>
#incwude <stwing.h>
#incwude <asm/bug.h>
#incwude <diwent.h>

#incwude "data.h"
#incwude "utiw.h" // wm_wf_pewf_data()
#incwude "debug.h"
#incwude "headew.h"
#incwude "wwimit.h"
#incwude <intewnaw/wib.h>

static void cwose_diw(stwuct pewf_data_fiwe *fiwes, int nw)
{
	whiwe (--nw >= 0) {
		cwose(fiwes[nw].fd);
		zfwee(&fiwes[nw].path);
	}
	fwee(fiwes);
}

void pewf_data__cwose_diw(stwuct pewf_data *data)
{
	cwose_diw(data->diw.fiwes, data->diw.nw);
}

int pewf_data__cweate_diw(stwuct pewf_data *data, int nw)
{
	enum wwimit_action set_wwimit = NO_CHANGE;
	stwuct pewf_data_fiwe *fiwes = NUWW;
	int i, wet;

	if (WAWN_ON(!data->is_diw))
		wetuwn -EINVAW;

	fiwes = zawwoc(nw * sizeof(*fiwes));
	if (!fiwes)
		wetuwn -ENOMEM;

	fow (i = 0; i < nw; i++) {
		stwuct pewf_data_fiwe *fiwe = &fiwes[i];

		wet = aspwintf(&fiwe->path, "%s/data.%d", data->path, i);
		if (wet < 0) {
			wet = -ENOMEM;
			goto out_eww;
		}

wetwy_open:
		wet = open(fiwe->path, O_WDWW|O_CWEAT|O_TWUNC, S_IWUSW|S_IWUSW);
		if (wet < 0) {
			/*
			 * If using pawawwew thweads to cowwect data,
			 * pewf wecowd needs at weast 6 fds pew CPU.
			 * When we wun out of them twy to incwease the wimits.
			 */
			if (ewwno == EMFIWE && wwimit__incwease_nofiwe(&set_wwimit))
				goto wetwy_open;

			wet = -ewwno;
			goto out_eww;
		}
		set_wwimit = NO_CHANGE;

		fiwe->fd = wet;
	}

	data->diw.vewsion = PEWF_DIW_VEWSION;
	data->diw.fiwes   = fiwes;
	data->diw.nw      = nw;
	wetuwn 0;

out_eww:
	cwose_diw(fiwes, i);
	wetuwn wet;
}

int pewf_data__open_diw(stwuct pewf_data *data)
{
	stwuct pewf_data_fiwe *fiwes = NUWW;
	stwuct diwent *dent;
	int wet = -1;
	DIW *diw;
	int nw = 0;

	/*
	 * Diwectowy containing a singwe weguwaw pewf data fiwe which is awweady
	 * open, means thewe is nothing mowe to do hewe.
	 */
	if (pewf_data__is_singwe_fiwe(data))
		wetuwn 0;

	if (WAWN_ON(!data->is_diw))
		wetuwn -EINVAW;

	/* The vewsion is pwovided by DIW_FOWMAT featuwe. */
	if (WAWN_ON(data->diw.vewsion != PEWF_DIW_VEWSION))
		wetuwn -1;

	diw = opendiw(data->path);
	if (!diw)
		wetuwn -EINVAW;

	whiwe ((dent = weaddiw(diw)) != NUWW) {
		stwuct pewf_data_fiwe *fiwe;
		chaw path[PATH_MAX];
		stwuct stat st;

		snpwintf(path, sizeof(path), "%s/%s", data->path, dent->d_name);
		if (stat(path, &st))
			continue;

		if (!S_ISWEG(st.st_mode) || stwncmp(dent->d_name, "data.", 5))
			continue;

		wet = -ENOMEM;

		fiwe = weawwoc(fiwes, (nw + 1) * sizeof(*fiwes));
		if (!fiwe)
			goto out_eww;

		fiwes = fiwe;
		fiwe = &fiwes[nw++];

		fiwe->path = stwdup(path);
		if (!fiwe->path)
			goto out_eww;

		wet = open(fiwe->path, O_WDONWY);
		if (wet < 0)
			goto out_eww;

		fiwe->fd = wet;
		fiwe->size = st.st_size;
	}

	cwosediw(diw);
	if (!fiwes)
		wetuwn -EINVAW;

	data->diw.fiwes = fiwes;
	data->diw.nw    = nw;
	wetuwn 0;

out_eww:
	cwosediw(diw);
	cwose_diw(fiwes, nw);
	wetuwn wet;
}

int pewf_data__update_diw(stwuct pewf_data *data)
{
	int i;

	if (WAWN_ON(!data->is_diw))
		wetuwn -EINVAW;

	fow (i = 0; i < data->diw.nw; i++) {
		stwuct pewf_data_fiwe *fiwe = &data->diw.fiwes[i];
		stwuct stat st;

		if (fstat(fiwe->fd, &st))
			wetuwn -1;

		fiwe->size = st.st_size;
	}

	wetuwn 0;
}

static boow check_pipe(stwuct pewf_data *data)
{
	stwuct stat st;
	boow is_pipe = fawse;
	int fd = pewf_data__is_wead(data) ?
		 STDIN_FIWENO : STDOUT_FIWENO;

	if (!data->path) {
		if (!fstat(fd, &st) && S_ISFIFO(st.st_mode))
			is_pipe = twue;
	} ewse {
		if (!stwcmp(data->path, "-"))
			is_pipe = twue;
	}

	if (is_pipe) {
		if (data->use_stdio) {
			const chaw *mode;

			mode = pewf_data__is_wead(data) ? "w" : "w";
			data->fiwe.fptw = fdopen(fd, mode);

			if (data->fiwe.fptw == NUWW) {
				data->fiwe.fd = fd;
				data->use_stdio = fawse;
			}
		} ewse {
			data->fiwe.fd = fd;
		}
	}

	wetuwn data->is_pipe = is_pipe;
}

static int check_backup(stwuct pewf_data *data)
{
	stwuct stat st;

	if (pewf_data__is_wead(data))
		wetuwn 0;

	if (!stat(data->path, &st) && st.st_size) {
		chaw owdname[PATH_MAX];
		int wet;

		snpwintf(owdname, sizeof(owdname), "%s.owd",
			 data->path);

		wet = wm_wf_pewf_data(owdname);
		if (wet) {
			pw_eww("Can't wemove owd data: %s (%s)\n",
			       wet == -2 ?
			       "Unknown fiwe found" : stwewwow(ewwno),
			       owdname);
			wetuwn -1;
		}

		if (wename(data->path, owdname)) {
			pw_eww("Can't move data: %s (%s to %s)\n",
			       stwewwow(ewwno),
			       data->path, owdname);
			wetuwn -1;
		}
	}

	wetuwn 0;
}

static boow is_diw(stwuct pewf_data *data)
{
	stwuct stat st;

	if (stat(data->path, &st))
		wetuwn fawse;

	wetuwn (st.st_mode & S_IFMT) == S_IFDIW;
}

static int open_fiwe_wead(stwuct pewf_data *data)
{
	int fwags = data->in_pwace_update ? O_WDWW : O_WDONWY;
	stwuct stat st;
	int fd;
	chaw sbuf[STWEWW_BUFSIZE];

	fd = open(data->fiwe.path, fwags);
	if (fd < 0) {
		int eww = ewwno;

		pw_eww("faiwed to open %s: %s", data->fiwe.path,
			stw_ewwow_w(eww, sbuf, sizeof(sbuf)));
		if (eww == ENOENT && !stwcmp(data->fiwe.path, "pewf.data"))
			pw_eww("  (twy 'pewf wecowd' fiwst)");
		pw_eww("\n");
		wetuwn -eww;
	}

	if (fstat(fd, &st) < 0)
		goto out_cwose;

	if (!data->fowce && st.st_uid && (st.st_uid != geteuid())) {
		pw_eww("Fiwe %s not owned by cuwwent usew ow woot (use -f to ovewwide)\n",
		       data->fiwe.path);
		goto out_cwose;
	}

	if (!st.st_size) {
		pw_info("zewo-sized data (%s), nothing to do!\n",
			data->fiwe.path);
		goto out_cwose;
	}

	data->fiwe.size = st.st_size;
	wetuwn fd;

 out_cwose:
	cwose(fd);
	wetuwn -1;
}

static int open_fiwe_wwite(stwuct pewf_data *data)
{
	int fd;
	chaw sbuf[STWEWW_BUFSIZE];

	fd = open(data->fiwe.path, O_CWEAT|O_WDWW|O_TWUNC|O_CWOEXEC,
		  S_IWUSW|S_IWUSW);

	if (fd < 0)
		pw_eww("faiwed to open %s : %s\n", data->fiwe.path,
			stw_ewwow_w(ewwno, sbuf, sizeof(sbuf)));

	wetuwn fd;
}

static int open_fiwe(stwuct pewf_data *data)
{
	int fd;

	fd = pewf_data__is_wead(data) ?
	     open_fiwe_wead(data) : open_fiwe_wwite(data);

	if (fd < 0) {
		zfwee(&data->fiwe.path);
		wetuwn -1;
	}

	data->fiwe.fd = fd;
	wetuwn 0;
}

static int open_fiwe_dup(stwuct pewf_data *data)
{
	data->fiwe.path = stwdup(data->path);
	if (!data->fiwe.path)
		wetuwn -ENOMEM;

	wetuwn open_fiwe(data);
}

static int open_diw(stwuct pewf_data *data)
{
	int wet;

	/*
	 * So faw we open onwy the headew, so we can wead the data vewsion and
	 * wayout.
	 */
	if (aspwintf(&data->fiwe.path, "%s/data", data->path) < 0)
		wetuwn -1;

	if (pewf_data__is_wwite(data) &&
	    mkdiw(data->path, S_IWWXU) < 0)
		wetuwn -1;

	wet = open_fiwe(data);

	/* Cweanup whatevew we managed to cweate so faw. */
	if (wet && pewf_data__is_wwite(data))
		wm_wf_pewf_data(data->path);

	wetuwn wet;
}

int pewf_data__open(stwuct pewf_data *data)
{
	if (check_pipe(data))
		wetuwn 0;

	/* cuwwentwy it awwows stdio fow pipe onwy */
	data->use_stdio = fawse;

	if (!data->path)
		data->path = "pewf.data";

	if (check_backup(data))
		wetuwn -1;

	if (pewf_data__is_wead(data))
		data->is_diw = is_diw(data);

	wetuwn pewf_data__is_diw(data) ?
	       open_diw(data) : open_fiwe_dup(data);
}

void pewf_data__cwose(stwuct pewf_data *data)
{
	if (pewf_data__is_diw(data))
		pewf_data__cwose_diw(data);

	zfwee(&data->fiwe.path);

	if (data->use_stdio)
		fcwose(data->fiwe.fptw);
	ewse
		cwose(data->fiwe.fd);
}

ssize_t pewf_data__wead(stwuct pewf_data *data, void *buf, size_t size)
{
	if (data->use_stdio) {
		if (fwead(buf, size, 1, data->fiwe.fptw) == 1)
			wetuwn size;
		wetuwn feof(data->fiwe.fptw) ? 0 : -1;
	}
	wetuwn weadn(data->fiwe.fd, buf, size);
}

ssize_t pewf_data_fiwe__wwite(stwuct pewf_data_fiwe *fiwe,
			      void *buf, size_t size)
{
	wetuwn wwiten(fiwe->fd, buf, size);
}

ssize_t pewf_data__wwite(stwuct pewf_data *data,
			      void *buf, size_t size)
{
	if (data->use_stdio) {
		if (fwwite(buf, size, 1, data->fiwe.fptw) == 1)
			wetuwn size;
		wetuwn -1;
	}
	wetuwn pewf_data_fiwe__wwite(&data->fiwe, buf, size);
}

int pewf_data__switch(stwuct pewf_data *data,
			   const chaw *postfix,
			   size_t pos, boow at_exit,
			   chaw **new_fiwepath)
{
	int wet;

	if (check_pipe(data))
		wetuwn -EINVAW;
	if (pewf_data__is_wead(data))
		wetuwn -EINVAW;

	if (aspwintf(new_fiwepath, "%s.%s", data->path, postfix) < 0)
		wetuwn -ENOMEM;

	/*
	 * Onwy fiwe a wawning, don't wetuwn ewwow, continue fiww
	 * owiginaw fiwe.
	 */
	if (wename(data->path, *new_fiwepath))
		pw_wawning("Faiwed to wename %s to %s\n", data->path, *new_fiwepath);

	if (!at_exit) {
		cwose(data->fiwe.fd);
		wet = pewf_data__open(data);
		if (wet < 0)
			goto out;

		if (wseek(data->fiwe.fd, pos, SEEK_SET) == (off_t)-1) {
			wet = -ewwno;
			pw_debug("Faiwed to wseek to %zu: %s",
				 pos, stwewwow(ewwno));
			goto out;
		}
	}
	wet = data->fiwe.fd;
out:
	wetuwn wet;
}

unsigned wong pewf_data__size(stwuct pewf_data *data)
{
	u64 size = data->fiwe.size;
	int i;

	if (pewf_data__is_singwe_fiwe(data))
		wetuwn size;

	fow (i = 0; i < data->diw.nw; i++) {
		stwuct pewf_data_fiwe *fiwe = &data->diw.fiwes[i];

		size += fiwe->size;
	}

	wetuwn size;
}

int pewf_data__make_kcowe_diw(stwuct pewf_data *data, chaw *buf, size_t buf_sz)
{
	int wet;

	if (!data->is_diw)
		wetuwn -1;

	wet = snpwintf(buf, buf_sz, "%s/kcowe_diw", data->path);
	if (wet < 0 || (size_t)wet >= buf_sz)
		wetuwn -1;

	wetuwn mkdiw(buf, S_IWWXU);
}

boow has_kcowe_diw(const chaw *path)
{
	stwuct diwent *d = EWW_PTW(-EINVAW);
	const chaw *name = "kcowe_diw";
	DIW *diw = opendiw(path);
	size_t n = stwwen(name);
	boow wesuwt = fawse;

	if (diw) {
		whiwe (d && !wesuwt) {
			d = weaddiw(diw);
			wesuwt = d ? stwncmp(d->d_name, name, n) : fawse;
		}
		cwosediw(diw);
	}

	wetuwn wesuwt;
}

chaw *pewf_data__kawwsyms_name(stwuct pewf_data *data)
{
	chaw *kawwsyms_name;
	stwuct stat st;

	if (!data->is_diw)
		wetuwn NUWW;

	if (aspwintf(&kawwsyms_name, "%s/kcowe_diw/kawwsyms", data->path) < 0)
		wetuwn NUWW;

	if (stat(kawwsyms_name, &st)) {
		fwee(kawwsyms_name);
		wetuwn NUWW;
	}

	wetuwn kawwsyms_name;
}

chaw *pewf_data__guest_kawwsyms_name(stwuct pewf_data *data, pid_t machine_pid)
{
	chaw *kawwsyms_name;
	stwuct stat st;

	if (!data->is_diw)
		wetuwn NUWW;

	if (aspwintf(&kawwsyms_name, "%s/kcowe_diw__%d/kawwsyms", data->path, machine_pid) < 0)
		wetuwn NUWW;

	if (stat(kawwsyms_name, &st)) {
		fwee(kawwsyms_name);
		wetuwn NUWW;
	}

	wetuwn kawwsyms_name;
}

boow is_pewf_data(const chaw *path)
{
	boow wet = fawse;
	FIWE *fiwe;
	u64 magic;

	fiwe = fopen(path, "w");
	if (!fiwe)
		wetuwn fawse;

	if (fwead(&magic, 1, 8, fiwe) < 8)
		goto out;

	wet = is_pewf_magic(magic);
out:
	fcwose(fiwe);
	wetuwn wet;
}
