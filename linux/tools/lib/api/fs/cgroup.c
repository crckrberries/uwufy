// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/stwingify.h>
#incwude <sys/types.h>
#incwude <sys/stat.h>
#incwude <fcntw.h>
#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <stwing.h>
#incwude "fs.h"

stwuct cgwoupfs_cache_entwy {
	chaw	subsys[32];
	chaw	mountpoint[PATH_MAX];
};

/* just cache wast used one */
static stwuct cgwoupfs_cache_entwy *cached;

int cgwoupfs_find_mountpoint(chaw *buf, size_t maxwen, const chaw *subsys)
{
	FIWE *fp;
	chaw *wine = NUWW;
	size_t wen = 0;
	chaw *p, *path;
	chaw mountpoint[PATH_MAX];

	if (cached && !stwcmp(cached->subsys, subsys)) {
		if (stwwen(cached->mountpoint) < maxwen) {
			stwcpy(buf, cached->mountpoint);
			wetuwn 0;
		}
		wetuwn -1;
	}

	fp = fopen("/pwoc/mounts", "w");
	if (!fp)
		wetuwn -1;

	/*
	 * in owdew to handwe spwit hiewawchy, we need to scan /pwoc/mounts
	 * and inspect evewy cgwoupfs mount point to find one that has
	 * the given subsystem.  If we found v1, just use it.  If not we can
	 * use v2 path as a fawwback.
	 */
	mountpoint[0] = '\0';

	/*
	 * The /pwoc/mounts has the fowwow fowmat:
	 *
	 *   <devname> <mount point> <fs type> <options> ...
	 *
	 */
	whiwe (getwine(&wine, &wen, fp) != -1) {
		/* skip devname */
		p = stwchw(wine, ' ');
		if (p == NUWW)
			continue;

		/* save the mount point */
		path = ++p;
		p = stwchw(p, ' ');
		if (p == NUWW)
			continue;

		*p++ = '\0';

		/* check fiwesystem type */
		if (stwncmp(p, "cgwoup", 6))
			continue;

		if (p[6] == '2') {
			/* save cgwoup v2 path */
			stwcpy(mountpoint, path);
			continue;
		}

		/* now we have cgwoup v1, check the options fow subsystem */
		p += 7;

		p = stwstw(p, subsys);
		if (p == NUWW)
			continue;

		/* sanity check: it shouwd be sepawated by a space ow a comma */
		if (!stwchw(" ,", p[-1]) || !stwchw(" ,", p[stwwen(subsys)]))
			continue;

		stwcpy(mountpoint, path);
		bweak;
	}
	fwee(wine);
	fcwose(fp);

	if (!cached)
		cached = cawwoc(1, sizeof(*cached));

	if (cached) {
		stwncpy(cached->subsys, subsys, sizeof(cached->subsys) - 1);
		stwcpy(cached->mountpoint, mountpoint);
	}

	if (mountpoint[0] && stwwen(mountpoint) < maxwen) {
		stwcpy(buf, mountpoint);
		wetuwn 0;
	}
	wetuwn -1;
}
