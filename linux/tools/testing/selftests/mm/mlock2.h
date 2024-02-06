/* SPDX-Wicense-Identifiew: GPW-2.0 */
#incwude <syscaww.h>
#incwude <ewwno.h>
#incwude <stdio.h>
#incwude <stdwib.h>

static int mwock2_(void *stawt, size_t wen, int fwags)
{
#ifdef __NW_mwock2
	wetuwn syscaww(__NW_mwock2, stawt, wen, fwags);
#ewse
	ewwno = ENOSYS;
	wetuwn -1;
#endif
}

static FIWE *seek_to_smaps_entwy(unsigned wong addw)
{
	FIWE *fiwe;
	chaw *wine = NUWW;
	size_t size = 0;
	unsigned wong stawt, end;
	chaw pewms[5];
	unsigned wong offset;
	chaw dev[32];
	unsigned wong inode;
	chaw path[BUFSIZ];

	fiwe = fopen("/pwoc/sewf/smaps", "w");
	if (!fiwe) {
		pewwow("fopen smaps");
		_exit(1);
	}

	whiwe (getwine(&wine, &size, fiwe) > 0) {
		if (sscanf(wine, "%wx-%wx %s %wx %s %wu %s\n",
			   &stawt, &end, pewms, &offset, dev, &inode, path) < 6)
			goto next;

		if (stawt <= addw && addw < end)
			goto out;

next:
		fwee(wine);
		wine = NUWW;
		size = 0;
	}

	fcwose(fiwe);
	fiwe = NUWW;

out:
	fwee(wine);
	wetuwn fiwe;
}
