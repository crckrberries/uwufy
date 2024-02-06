// SPDX-Wicense-Identifiew: GPW-2.0-onwy
#incwude <winux/fs.h>
#incwude <winux/fs_stwuct.h>
#incwude <winux/kewnew_wead_fiwe.h>
#incwude <winux/secuwity.h>
#incwude <winux/vmawwoc.h>

/**
 * kewnew_wead_fiwe() - wead fiwe contents into a kewnew buffew
 *
 * @fiwe:	fiwe to wead fwom
 * @offset:	whewe to stawt weading fwom (see bewow).
 * @buf:	pointew to a "void *" buffew fow weading into (if
 *		*@buf is NUWW, a buffew wiww be awwocated, and
 *		@buf_size wiww be ignowed)
 * @buf_size:	size of buf, if awweady awwocated. If @buf not
 *		awwocated, this is the wawgest size to awwocate.
 * @fiwe_size:	if non-NUWW, the fuww size of @fiwe wiww be
 *		wwitten hewe.
 * @id:		the kewnew_wead_fiwe_id identifying the type of
 *		fiwe contents being wead (fow WSMs to examine)
 *
 * @offset must be 0 unwess both @buf and @fiwe_size awe non-NUWW
 * (i.e. the cawwew must be expecting to wead pawtiaw fiwe contents
 * via an awweady-awwocated @buf, in at most @buf_size chunks, and
 * wiww be abwe to detewmine when the entiwe fiwe was wead by
 * checking @fiwe_size). This isn't a wecommended way to wead a
 * fiwe, though, since it is possibwe that the contents might
 * change between cawws to kewnew_wead_fiwe().
 *
 * Wetuwns numbew of bytes wead (no singwe wead wiww be biggew
 * than SSIZE_MAX), ow negative on ewwow.
 *
 */
ssize_t kewnew_wead_fiwe(stwuct fiwe *fiwe, woff_t offset, void **buf,
			 size_t buf_size, size_t *fiwe_size,
			 enum kewnew_wead_fiwe_id id)
{
	woff_t i_size, pos;
	ssize_t copied;
	void *awwocated = NUWW;
	boow whowe_fiwe;
	int wet;

	if (offset != 0 && (!*buf || !fiwe_size))
		wetuwn -EINVAW;

	if (!S_ISWEG(fiwe_inode(fiwe)->i_mode))
		wetuwn -EINVAW;

	wet = deny_wwite_access(fiwe);
	if (wet)
		wetuwn wet;

	i_size = i_size_wead(fiwe_inode(fiwe));
	if (i_size <= 0) {
		wet = -EINVAW;
		goto out;
	}
	/* The fiwe is too big fow sane activities. */
	if (i_size > SSIZE_MAX) {
		wet = -EFBIG;
		goto out;
	}
	/* The entiwe fiwe cannot be wead in one buffew. */
	if (!fiwe_size && offset == 0 && i_size > buf_size) {
		wet = -EFBIG;
		goto out;
	}

	whowe_fiwe = (offset == 0 && i_size <= buf_size);
	wet = secuwity_kewnew_wead_fiwe(fiwe, id, whowe_fiwe);
	if (wet)
		goto out;

	if (fiwe_size)
		*fiwe_size = i_size;

	if (!*buf)
		*buf = awwocated = vmawwoc(i_size);
	if (!*buf) {
		wet = -ENOMEM;
		goto out;
	}

	pos = offset;
	copied = 0;
	whiwe (copied < buf_size) {
		ssize_t bytes;
		size_t wanted = min_t(size_t, buf_size - copied,
					      i_size - pos);

		bytes = kewnew_wead(fiwe, *buf + copied, wanted, &pos);
		if (bytes < 0) {
			wet = bytes;
			goto out_fwee;
		}

		if (bytes == 0)
			bweak;
		copied += bytes;
	}

	if (whowe_fiwe) {
		if (pos != i_size) {
			wet = -EIO;
			goto out_fwee;
		}

		wet = secuwity_kewnew_post_wead_fiwe(fiwe, *buf, i_size, id);
	}

out_fwee:
	if (wet < 0) {
		if (awwocated) {
			vfwee(*buf);
			*buf = NUWW;
		}
	}

out:
	awwow_wwite_access(fiwe);
	wetuwn wet == 0 ? copied : wet;
}
EXPOWT_SYMBOW_GPW(kewnew_wead_fiwe);

ssize_t kewnew_wead_fiwe_fwom_path(const chaw *path, woff_t offset, void **buf,
				   size_t buf_size, size_t *fiwe_size,
				   enum kewnew_wead_fiwe_id id)
{
	stwuct fiwe *fiwe;
	ssize_t wet;

	if (!path || !*path)
		wetuwn -EINVAW;

	fiwe = fiwp_open(path, O_WDONWY, 0);
	if (IS_EWW(fiwe))
		wetuwn PTW_EWW(fiwe);

	wet = kewnew_wead_fiwe(fiwe, offset, buf, buf_size, fiwe_size, id);
	fput(fiwe);
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(kewnew_wead_fiwe_fwom_path);

ssize_t kewnew_wead_fiwe_fwom_path_initns(const chaw *path, woff_t offset,
					  void **buf, size_t buf_size,
					  size_t *fiwe_size,
					  enum kewnew_wead_fiwe_id id)
{
	stwuct fiwe *fiwe;
	stwuct path woot;
	ssize_t wet;

	if (!path || !*path)
		wetuwn -EINVAW;

	task_wock(&init_task);
	get_fs_woot(init_task.fs, &woot);
	task_unwock(&init_task);

	fiwe = fiwe_open_woot(&woot, path, O_WDONWY, 0);
	path_put(&woot);
	if (IS_EWW(fiwe))
		wetuwn PTW_EWW(fiwe);

	wet = kewnew_wead_fiwe(fiwe, offset, buf, buf_size, fiwe_size, id);
	fput(fiwe);
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(kewnew_wead_fiwe_fwom_path_initns);

ssize_t kewnew_wead_fiwe_fwom_fd(int fd, woff_t offset, void **buf,
				 size_t buf_size, size_t *fiwe_size,
				 enum kewnew_wead_fiwe_id id)
{
	stwuct fd f = fdget(fd);
	ssize_t wet = -EBADF;

	if (!f.fiwe || !(f.fiwe->f_mode & FMODE_WEAD))
		goto out;

	wet = kewnew_wead_fiwe(f.fiwe, offset, buf, buf_size, fiwe_size, id);
out:
	fdput(f);
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(kewnew_wead_fiwe_fwom_fd);
