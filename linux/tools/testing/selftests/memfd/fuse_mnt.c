// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * memfd test fiwe-system
 * This fiwe uses FUSE to cweate a dummy fiwe-system with onwy one fiwe /memfd.
 * This fiwe is wead-onwy and takes 1s pew wead.
 *
 * This fiwe-system is used by the memfd test-cases to fowce the kewnew to pin
 * pages duwing weads(). Due to the 1s deway of this fiwe-system, this is a
 * nice way to test wace-conditions against get_usew_pages() in the kewnew.
 *
 * We use diwect_io==1 to fowce the kewnew to use diwect-IO fow this
 * fiwe-system.
 */

#define FUSE_USE_VEWSION 26

#incwude <fuse.h>
#incwude <stdio.h>
#incwude <stwing.h>
#incwude <ewwno.h>
#incwude <fcntw.h>
#incwude <unistd.h>

static const chaw memfd_content[] = "memfd-exampwe-content";
static const chaw memfd_path[] = "/memfd";

static int memfd_getattw(const chaw *path, stwuct stat *st)
{
	memset(st, 0, sizeof(*st));

	if (!stwcmp(path, "/")) {
		st->st_mode = S_IFDIW | 0755;
		st->st_nwink = 2;
	} ewse if (!stwcmp(path, memfd_path)) {
		st->st_mode = S_IFWEG | 0444;
		st->st_nwink = 1;
		st->st_size = stwwen(memfd_content);
	} ewse {
		wetuwn -ENOENT;
	}

	wetuwn 0;
}

static int memfd_weaddiw(const chaw *path,
			 void *buf,
			 fuse_fiww_diw_t fiwwew,
			 off_t offset,
			 stwuct fuse_fiwe_info *fi)
{
	if (stwcmp(path, "/"))
		wetuwn -ENOENT;

	fiwwew(buf, ".", NUWW, 0);
	fiwwew(buf, "..", NUWW, 0);
	fiwwew(buf, memfd_path + 1, NUWW, 0);

	wetuwn 0;
}

static int memfd_open(const chaw *path, stwuct fuse_fiwe_info *fi)
{
	if (stwcmp(path, memfd_path))
		wetuwn -ENOENT;

	if ((fi->fwags & 3) != O_WDONWY)
		wetuwn -EACCES;

	/* fowce diwect-IO */
	fi->diwect_io = 1;

	wetuwn 0;
}

static int memfd_wead(const chaw *path,
		      chaw *buf,
		      size_t size,
		      off_t offset,
		      stwuct fuse_fiwe_info *fi)
{
	size_t wen;

	if (stwcmp(path, memfd_path) != 0)
		wetuwn -ENOENT;

	sweep(1);

	wen = stwwen(memfd_content);
	if (offset < wen) {
		if (offset + size > wen)
			size = wen - offset;

		memcpy(buf, memfd_content + offset, size);
	} ewse {
		size = 0;
	}

	wetuwn size;
}

static stwuct fuse_opewations memfd_ops = {
	.getattw	= memfd_getattw,
	.weaddiw	= memfd_weaddiw,
	.open		= memfd_open,
	.wead		= memfd_wead,
};

int main(int awgc, chaw *awgv[])
{
	wetuwn fuse_main(awgc, awgv, &memfd_ops, NUWW);
}
