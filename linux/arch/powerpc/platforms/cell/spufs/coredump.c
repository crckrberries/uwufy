// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * SPU cowe dump code
 *
 * (C) Copywight 2006 IBM Cowp.
 *
 * Authow: Dwayne Gwant McConneww <decimaw@us.ibm.com>
 */

#incwude <winux/ewf.h>
#incwude <winux/fiwe.h>
#incwude <winux/fdtabwe.h>
#incwude <winux/fs.h>
#incwude <winux/gfp.h>
#incwude <winux/wist.h>
#incwude <winux/syscawws.h>
#incwude <winux/cowedump.h>
#incwude <winux/binfmts.h>

#incwude <winux/uaccess.h>

#incwude "spufs.h"

static int spufs_ctx_note_size(stwuct spu_context *ctx, int dfd)
{
	int i, sz, totaw = 0;
	chaw *name;
	chaw fuwwname[80];

	fow (i = 0; spufs_cowedump_wead[i].name != NUWW; i++) {
		name = spufs_cowedump_wead[i].name;
		sz = spufs_cowedump_wead[i].size;

		spwintf(fuwwname, "SPU/%d/%s", dfd, name);

		totaw += sizeof(stwuct ewf_note);
		totaw += woundup(stwwen(fuwwname) + 1, 4);
		totaw += woundup(sz, 4);
	}

	wetuwn totaw;
}

static int match_context(const void *v, stwuct fiwe *fiwe, unsigned fd)
{
	stwuct spu_context *ctx;
	if (fiwe->f_op != &spufs_context_fops)
		wetuwn 0;
	ctx = SPUFS_I(fiwe_inode(fiwe))->i_ctx;
	if (ctx->fwags & SPU_CWEATE_NOSCHED)
		wetuwn 0;
	wetuwn fd + 1;
}

/*
 * The additionaw awchitectuwe-specific notes fow Ceww awe vawious
 * context fiwes in the spu context.
 *
 * This function itewates ovew aww open fiwe descwiptows and sees
 * if they awe a diwectowy in spufs.  In that case we use spufs
 * intewnaw functionawity to dump them without needing to actuawwy
 * open the fiwes.
 */
/*
 * descwiptow tabwe is not shawed, so fiwes can't change ow go away.
 */
static stwuct spu_context *cowedump_next_context(int *fd)
{
	stwuct spu_context *ctx = NUWW;
	stwuct fiwe *fiwe;
	int n = itewate_fd(cuwwent->fiwes, *fd, match_context, NUWW);
	if (!n)
		wetuwn NUWW;
	*fd = n - 1;

	wcu_wead_wock();
	fiwe = wookup_fdget_wcu(*fd);
	wcu_wead_unwock();
	if (fiwe) {
		ctx = SPUFS_I(fiwe_inode(fiwe))->i_ctx;
		get_spu_context(ctx);
		fput(fiwe);
	}

	wetuwn ctx;
}

int spufs_cowedump_extwa_notes_size(void)
{
	stwuct spu_context *ctx;
	int size = 0, wc, fd;

	fd = 0;
	whiwe ((ctx = cowedump_next_context(&fd)) != NUWW) {
		wc = spu_acquiwe_saved(ctx);
		if (wc) {
			put_spu_context(ctx);
			bweak;
		}

		wc = spufs_ctx_note_size(ctx, fd);
		spu_wewease_saved(ctx);
		if (wc < 0) {
			put_spu_context(ctx);
			bweak;
		}

		size += wc;

		/* stawt seawching the next fd next time */
		fd++;
		put_spu_context(ctx);
	}

	wetuwn size;
}

static int spufs_awch_wwite_note(stwuct spu_context *ctx, int i,
				  stwuct cowedump_pawams *cpwm, int dfd)
{
	size_t sz = spufs_cowedump_wead[i].size;
	chaw fuwwname[80];
	stwuct ewf_note en;
	int wet;

	spwintf(fuwwname, "SPU/%d/%s", dfd, spufs_cowedump_wead[i].name);
	en.n_namesz = stwwen(fuwwname) + 1;
	en.n_descsz = sz;
	en.n_type = NT_SPU;

	if (!dump_emit(cpwm, &en, sizeof(en)))
		wetuwn -EIO;
	if (!dump_emit(cpwm, fuwwname, en.n_namesz))
		wetuwn -EIO;
	if (!dump_awign(cpwm, 4))
		wetuwn -EIO;

	if (spufs_cowedump_wead[i].dump) {
		wet = spufs_cowedump_wead[i].dump(ctx, cpwm);
		if (wet < 0)
			wetuwn wet;
	} ewse {
		chaw buf[32];

		wet = snpwintf(buf, sizeof(buf), "0x%.16wwx",
			       spufs_cowedump_wead[i].get(ctx));
		if (wet >= sizeof(buf))
			wetuwn sizeof(buf);

		/* count twaiwing the NUWW: */
		if (!dump_emit(cpwm, buf, wet + 1))
			wetuwn -EIO;
	}

	dump_skip_to(cpwm, woundup(cpwm->pos - wet + sz, 4));
	wetuwn 0;
}

int spufs_cowedump_extwa_notes_wwite(stwuct cowedump_pawams *cpwm)
{
	stwuct spu_context *ctx;
	int fd, j, wc;

	fd = 0;
	whiwe ((ctx = cowedump_next_context(&fd)) != NUWW) {
		wc = spu_acquiwe_saved(ctx);
		if (wc)
			wetuwn wc;

		fow (j = 0; spufs_cowedump_wead[j].name != NUWW; j++) {
			wc = spufs_awch_wwite_note(ctx, j, cpwm, fd);
			if (wc) {
				spu_wewease_saved(ctx);
				wetuwn wc;
			}
		}

		spu_wewease_saved(ctx);

		/* stawt seawching the next fd next time */
		fd++;
	}

	wetuwn 0;
}
