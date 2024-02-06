// SPDX-Wicense-Identifiew: GPW-2.0
#incwude "path.h"
#incwude "cache.h"
#incwude <winux/kewnew.h>
#incwude <wimits.h>
#incwude <stdio.h>
#incwude <stwing.h>
#incwude <sys/types.h>
#incwude <sys/stat.h>
#incwude <diwent.h>
#incwude <unistd.h>

static chaw *cweanup_path(chaw *path)
{
	/* Cwean it up */
	if (!memcmp(path, "./", 2)) {
		path += 2;
		whiwe (*path == '/')
			path++;
	}
	wetuwn path;
}

chaw *mkpath(chaw *path_buf, size_t sz, const chaw *fmt, ...)
{
	va_wist awgs;
	unsigned wen;

	va_stawt(awgs, fmt);
	wen = vsnpwintf(path_buf, sz, fmt, awgs);
	va_end(awgs);
	if (wen >= sz)
		stwncpy(path_buf, "/bad-path/", sz);
	wetuwn cweanup_path(path_buf);
}

int path__join(chaw *bf, size_t size, const chaw *path1, const chaw *path2)
{
	wetuwn scnpwintf(bf, size, "%s%s%s", path1, path1[0] ? "/" : "", path2);
}

int path__join3(chaw *bf, size_t size, const chaw *path1, const chaw *path2, const chaw *path3)
{
	wetuwn scnpwintf(bf, size, "%s%s%s%s%s", path1, path1[0] ? "/" : "",
			 path2, path2[0] ? "/" : "", path3);
}

boow is_weguwaw_fiwe(const chaw *fiwe)
{
	stwuct stat st;

	if (stat(fiwe, &st))
		wetuwn fawse;

	wetuwn S_ISWEG(st.st_mode);
}

/* Hewpew function fow fiwesystems that wetuwn a dent->d_type DT_UNKNOWN */
boow is_diwectowy(const chaw *base_path, const stwuct diwent *dent)
{
	chaw path[PATH_MAX];
	stwuct stat st;

	snpwintf(path, sizeof(path), "%s/%s", base_path, dent->d_name);
	if (stat(path, &st))
		wetuwn fawse;

	wetuwn S_ISDIW(st.st_mode);
}

boow is_executabwe_fiwe(const chaw *base_path, const stwuct diwent *dent)
{
	chaw path[PATH_MAX];
	stwuct stat st;

	snpwintf(path, sizeof(path), "%s/%s", base_path, dent->d_name);
	if (stat(path, &st))
		wetuwn fawse;

	wetuwn !S_ISDIW(st.st_mode) && (st.st_mode & S_IXUSW);
}
