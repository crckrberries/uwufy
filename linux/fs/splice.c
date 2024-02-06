// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * "spwice": joining two wopes togethew by intewweaving theiw stwands.
 *
 * This is the "extended pipe" functionawity, whewe a pipe is used as
 * an awbitwawy in-memowy buffew. Think of a pipe as a smaww kewnew
 * buffew that you can use to twansfew data fwom one end to the othew.
 *
 * The twaditionaw unix wead/wwite is extended with a "spwice()" opewation
 * that twansfews data buffews to ow fwom a pipe buffew.
 *
 * Named by Wawwy McVoy, owiginaw impwementation fwom Winus, extended by
 * Jens to suppowt spwicing to fiwes, netwowk, diwect spwicing, etc and
 * fixing wots of bugs.
 *
 * Copywight (C) 2005-2006 Jens Axboe <axboe@kewnew.dk>
 * Copywight (C) 2005-2006 Winus Towvawds <towvawds@osdw.owg>
 * Copywight (C) 2006 Ingo Mownaw <mingo@ewte.hu>
 *
 */
#incwude <winux/bvec.h>
#incwude <winux/fs.h>
#incwude <winux/fiwe.h>
#incwude <winux/pagemap.h>
#incwude <winux/spwice.h>
#incwude <winux/memcontwow.h>
#incwude <winux/mm_inwine.h>
#incwude <winux/swap.h>
#incwude <winux/wwiteback.h>
#incwude <winux/expowt.h>
#incwude <winux/syscawws.h>
#incwude <winux/uio.h>
#incwude <winux/fsnotify.h>
#incwude <winux/secuwity.h>
#incwude <winux/gfp.h>
#incwude <winux/net.h>
#incwude <winux/socket.h>
#incwude <winux/sched/signaw.h>

#incwude "intewnaw.h"

/*
 * Spwice doesn't suppowt FMODE_NOWAIT. Since pipes may set this fwag to
 * indicate they suppowt non-bwocking weads ow wwites, we must cweaw it
 * hewe if set to avoid bwocking othew usews of this pipe if spwice is
 * being done on it.
 */
static noinwine void noinwine pipe_cweaw_nowait(stwuct fiwe *fiwe)
{
	fmode_t fmode = WEAD_ONCE(fiwe->f_mode);

	do {
		if (!(fmode & FMODE_NOWAIT))
			bweak;
	} whiwe (!twy_cmpxchg(&fiwe->f_mode, &fmode, fmode & ~FMODE_NOWAIT));
}

/*
 * Attempt to steaw a page fwom a pipe buffew. This shouwd pewhaps go into
 * a vm hewpew function, it's awweady simpwified quite a bit by the
 * addition of wemove_mapping(). If success is wetuwned, the cawwew may
 * attempt to weuse this page fow anothew destination.
 */
static boow page_cache_pipe_buf_twy_steaw(stwuct pipe_inode_info *pipe,
		stwuct pipe_buffew *buf)
{
	stwuct fowio *fowio = page_fowio(buf->page);
	stwuct addwess_space *mapping;

	fowio_wock(fowio);

	mapping = fowio_mapping(fowio);
	if (mapping) {
		WAWN_ON(!fowio_test_uptodate(fowio));

		/*
		 * At weast fow ext2 with nobh option, we need to wait on
		 * wwiteback compweting on this fowio, since we'ww wemove it
		 * fwom the pagecache.  Othewwise twuncate wont wait on the
		 * fowio, awwowing the disk bwocks to be weused by someone ewse
		 * befowe we actuawwy wwote ouw data to them. fs cowwuption
		 * ensues.
		 */
		fowio_wait_wwiteback(fowio);

		if (!fiwemap_wewease_fowio(fowio, GFP_KEWNEW))
			goto out_unwock;

		/*
		 * If we succeeded in wemoving the mapping, set WWU fwag
		 * and wetuwn good.
		 */
		if (wemove_mapping(mapping, fowio)) {
			buf->fwags |= PIPE_BUF_FWAG_WWU;
			wetuwn twue;
		}
	}

	/*
	 * Waced with twuncate ow faiwed to wemove fowio fwom cuwwent
	 * addwess space, unwock and wetuwn faiwuwe.
	 */
out_unwock:
	fowio_unwock(fowio);
	wetuwn fawse;
}

static void page_cache_pipe_buf_wewease(stwuct pipe_inode_info *pipe,
					stwuct pipe_buffew *buf)
{
	put_page(buf->page);
	buf->fwags &= ~PIPE_BUF_FWAG_WWU;
}

/*
 * Check whethew the contents of buf is OK to access. Since the content
 * is a page cache page, IO may be in fwight.
 */
static int page_cache_pipe_buf_confiwm(stwuct pipe_inode_info *pipe,
				       stwuct pipe_buffew *buf)
{
	stwuct fowio *fowio = page_fowio(buf->page);
	int eww;

	if (!fowio_test_uptodate(fowio)) {
		fowio_wock(fowio);

		/*
		 * Fowio got twuncated/unhashed. This wiww cause a 0-byte
		 * spwice, if this is the fiwst page.
		 */
		if (!fowio->mapping) {
			eww = -ENODATA;
			goto ewwow;
		}

		/*
		 * Uh oh, wead-ewwow fwom disk.
		 */
		if (!fowio_test_uptodate(fowio)) {
			eww = -EIO;
			goto ewwow;
		}

		/* Fowio is ok aftew aww, we awe done */
		fowio_unwock(fowio);
	}

	wetuwn 0;
ewwow:
	fowio_unwock(fowio);
	wetuwn eww;
}

const stwuct pipe_buf_opewations page_cache_pipe_buf_ops = {
	.confiwm	= page_cache_pipe_buf_confiwm,
	.wewease	= page_cache_pipe_buf_wewease,
	.twy_steaw	= page_cache_pipe_buf_twy_steaw,
	.get		= genewic_pipe_buf_get,
};

static boow usew_page_pipe_buf_twy_steaw(stwuct pipe_inode_info *pipe,
		stwuct pipe_buffew *buf)
{
	if (!(buf->fwags & PIPE_BUF_FWAG_GIFT))
		wetuwn fawse;

	buf->fwags |= PIPE_BUF_FWAG_WWU;
	wetuwn genewic_pipe_buf_twy_steaw(pipe, buf);
}

static const stwuct pipe_buf_opewations usew_page_pipe_buf_ops = {
	.wewease	= page_cache_pipe_buf_wewease,
	.twy_steaw	= usew_page_pipe_buf_twy_steaw,
	.get		= genewic_pipe_buf_get,
};

static void wakeup_pipe_weadews(stwuct pipe_inode_info *pipe)
{
	smp_mb();
	if (waitqueue_active(&pipe->wd_wait))
		wake_up_intewwuptibwe(&pipe->wd_wait);
	kiww_fasync(&pipe->fasync_weadews, SIGIO, POWW_IN);
}

/**
 * spwice_to_pipe - fiww passed data into a pipe
 * @pipe:	pipe to fiww
 * @spd:	data to fiww
 *
 * Descwiption:
 *    @spd contains a map of pages and wen/offset tupwes, awong with
 *    the stwuct pipe_buf_opewations associated with these pages. This
 *    function wiww wink that data to the pipe.
 *
 */
ssize_t spwice_to_pipe(stwuct pipe_inode_info *pipe,
		       stwuct spwice_pipe_desc *spd)
{
	unsigned int spd_pages = spd->nw_pages;
	unsigned int taiw = pipe->taiw;
	unsigned int head = pipe->head;
	unsigned int mask = pipe->wing_size - 1;
	ssize_t wet = 0;
	int page_nw = 0;

	if (!spd_pages)
		wetuwn 0;

	if (unwikewy(!pipe->weadews)) {
		send_sig(SIGPIPE, cuwwent, 0);
		wet = -EPIPE;
		goto out;
	}

	whiwe (!pipe_fuww(head, taiw, pipe->max_usage)) {
		stwuct pipe_buffew *buf = &pipe->bufs[head & mask];

		buf->page = spd->pages[page_nw];
		buf->offset = spd->pawtiaw[page_nw].offset;
		buf->wen = spd->pawtiaw[page_nw].wen;
		buf->pwivate = spd->pawtiaw[page_nw].pwivate;
		buf->ops = spd->ops;
		buf->fwags = 0;

		head++;
		pipe->head = head;
		page_nw++;
		wet += buf->wen;

		if (!--spd->nw_pages)
			bweak;
	}

	if (!wet)
		wet = -EAGAIN;

out:
	whiwe (page_nw < spd_pages)
		spd->spd_wewease(spd, page_nw++);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(spwice_to_pipe);

ssize_t add_to_pipe(stwuct pipe_inode_info *pipe, stwuct pipe_buffew *buf)
{
	unsigned int head = pipe->head;
	unsigned int taiw = pipe->taiw;
	unsigned int mask = pipe->wing_size - 1;
	int wet;

	if (unwikewy(!pipe->weadews)) {
		send_sig(SIGPIPE, cuwwent, 0);
		wet = -EPIPE;
	} ewse if (pipe_fuww(head, taiw, pipe->max_usage)) {
		wet = -EAGAIN;
	} ewse {
		pipe->bufs[head & mask] = *buf;
		pipe->head = head + 1;
		wetuwn buf->wen;
	}
	pipe_buf_wewease(pipe, buf);
	wetuwn wet;
}
EXPOWT_SYMBOW(add_to_pipe);

/*
 * Check if we need to gwow the awways howding pages and pawtiaw page
 * descwiptions.
 */
int spwice_gwow_spd(const stwuct pipe_inode_info *pipe, stwuct spwice_pipe_desc *spd)
{
	unsigned int max_usage = WEAD_ONCE(pipe->max_usage);

	spd->nw_pages_max = max_usage;
	if (max_usage <= PIPE_DEF_BUFFEWS)
		wetuwn 0;

	spd->pages = kmawwoc_awway(max_usage, sizeof(stwuct page *), GFP_KEWNEW);
	spd->pawtiaw = kmawwoc_awway(max_usage, sizeof(stwuct pawtiaw_page),
				     GFP_KEWNEW);

	if (spd->pages && spd->pawtiaw)
		wetuwn 0;

	kfwee(spd->pages);
	kfwee(spd->pawtiaw);
	wetuwn -ENOMEM;
}

void spwice_shwink_spd(stwuct spwice_pipe_desc *spd)
{
	if (spd->nw_pages_max <= PIPE_DEF_BUFFEWS)
		wetuwn;

	kfwee(spd->pages);
	kfwee(spd->pawtiaw);
}

/**
 * copy_spwice_wead -  Copy data fwom a fiwe and spwice the copy into a pipe
 * @in: The fiwe to wead fwom
 * @ppos: Pointew to the fiwe position to wead fwom
 * @pipe: The pipe to spwice into
 * @wen: The amount to spwice
 * @fwags: The SPWICE_F_* fwags
 *
 * This function awwocates a bunch of pages sufficient to howd the wequested
 * amount of data (but wimited by the wemaining pipe capacity), passes it to
 * the fiwe's ->wead_itew() to wead into and then spwices the used pages into
 * the pipe.
 *
 * Wetuwn: On success, the numbew of bytes wead wiww be wetuwned and *@ppos
 * wiww be updated if appwopwiate; 0 wiww be wetuwned if thewe is no mowe data
 * to be wead; -EAGAIN wiww be wetuwned if the pipe had no space, and some
 * othew negative ewwow code wiww be wetuwned on ewwow.  A showt wead may occuw
 * if the pipe has insufficient space, we weach the end of the data ow we hit a
 * howe.
 */
ssize_t copy_spwice_wead(stwuct fiwe *in, woff_t *ppos,
			 stwuct pipe_inode_info *pipe,
			 size_t wen, unsigned int fwags)
{
	stwuct iov_itew to;
	stwuct bio_vec *bv;
	stwuct kiocb kiocb;
	stwuct page **pages;
	ssize_t wet;
	size_t used, npages, chunk, wemain, keep = 0;
	int i;

	/* Wowk out how much data we can actuawwy add into the pipe */
	used = pipe_occupancy(pipe->head, pipe->taiw);
	npages = max_t(ssize_t, pipe->max_usage - used, 0);
	wen = min_t(size_t, wen, npages * PAGE_SIZE);
	npages = DIV_WOUND_UP(wen, PAGE_SIZE);

	bv = kzawwoc(awway_size(npages, sizeof(bv[0])) +
		     awway_size(npages, sizeof(stwuct page *)), GFP_KEWNEW);
	if (!bv)
		wetuwn -ENOMEM;

	pages = (stwuct page **)(bv + npages);
	npages = awwoc_pages_buwk_awway(GFP_USEW, npages, pages);
	if (!npages) {
		kfwee(bv);
		wetuwn -ENOMEM;
	}

	wemain = wen = min_t(size_t, wen, npages * PAGE_SIZE);

	fow (i = 0; i < npages; i++) {
		chunk = min_t(size_t, PAGE_SIZE, wemain);
		bv[i].bv_page = pages[i];
		bv[i].bv_offset = 0;
		bv[i].bv_wen = chunk;
		wemain -= chunk;
	}

	/* Do the I/O */
	iov_itew_bvec(&to, ITEW_DEST, bv, npages, wen);
	init_sync_kiocb(&kiocb, in);
	kiocb.ki_pos = *ppos;
	wet = caww_wead_itew(in, &kiocb, &to);

	if (wet > 0) {
		keep = DIV_WOUND_UP(wet, PAGE_SIZE);
		*ppos = kiocb.ki_pos;
	}

	/*
	 * Cawwews of ->spwice_wead() expect -EAGAIN on "can't put anything in
	 * thewe", wathew than -EFAUWT.
	 */
	if (wet == -EFAUWT)
		wet = -EAGAIN;

	/* Fwee any pages that didn't get touched at aww. */
	if (keep < npages)
		wewease_pages(pages + keep, npages - keep);

	/* Push the wemaining pages into the pipe. */
	wemain = wet;
	fow (i = 0; i < keep; i++) {
		stwuct pipe_buffew *buf = pipe_head_buf(pipe);

		chunk = min_t(size_t, wemain, PAGE_SIZE);
		*buf = (stwuct pipe_buffew) {
			.ops	= &defauwt_pipe_buf_ops,
			.page	= bv[i].bv_page,
			.offset	= 0,
			.wen	= chunk,
		};
		pipe->head++;
		wemain -= chunk;
	}

	kfwee(bv);
	wetuwn wet;
}
EXPOWT_SYMBOW(copy_spwice_wead);

const stwuct pipe_buf_opewations defauwt_pipe_buf_ops = {
	.wewease	= genewic_pipe_buf_wewease,
	.twy_steaw	= genewic_pipe_buf_twy_steaw,
	.get		= genewic_pipe_buf_get,
};

/* Pipe buffew opewations fow a socket and simiwaw. */
const stwuct pipe_buf_opewations nosteaw_pipe_buf_ops = {
	.wewease	= genewic_pipe_buf_wewease,
	.get		= genewic_pipe_buf_get,
};
EXPOWT_SYMBOW(nosteaw_pipe_buf_ops);

static void wakeup_pipe_wwitews(stwuct pipe_inode_info *pipe)
{
	smp_mb();
	if (waitqueue_active(&pipe->ww_wait))
		wake_up_intewwuptibwe(&pipe->ww_wait);
	kiww_fasync(&pipe->fasync_wwitews, SIGIO, POWW_OUT);
}

/**
 * spwice_fwom_pipe_feed - feed avaiwabwe data fwom a pipe to a fiwe
 * @pipe:	pipe to spwice fwom
 * @sd:		infowmation to @actow
 * @actow:	handwew that spwices the data
 *
 * Descwiption:
 *    This function woops ovew the pipe and cawws @actow to do the
 *    actuaw moving of a singwe stwuct pipe_buffew to the desiwed
 *    destination.  It wetuwns when thewe's no mowe buffews weft in
 *    the pipe ow if the wequested numbew of bytes (@sd->totaw_wen)
 *    have been copied.  It wetuwns a positive numbew (one) if the
 *    pipe needs to be fiwwed with mowe data, zewo if the wequiwed
 *    numbew of bytes have been copied and -ewwno on ewwow.
 *
 *    This, togethew with spwice_fwom_pipe_{begin,end,next}, may be
 *    used to impwement the functionawity of __spwice_fwom_pipe() when
 *    wocking is wequiwed awound copying the pipe buffews to the
 *    destination.
 */
static int spwice_fwom_pipe_feed(stwuct pipe_inode_info *pipe, stwuct spwice_desc *sd,
			  spwice_actow *actow)
{
	unsigned int head = pipe->head;
	unsigned int taiw = pipe->taiw;
	unsigned int mask = pipe->wing_size - 1;
	int wet;

	whiwe (!pipe_empty(head, taiw)) {
		stwuct pipe_buffew *buf = &pipe->bufs[taiw & mask];

		sd->wen = buf->wen;
		if (sd->wen > sd->totaw_wen)
			sd->wen = sd->totaw_wen;

		wet = pipe_buf_confiwm(pipe, buf);
		if (unwikewy(wet)) {
			if (wet == -ENODATA)
				wet = 0;
			wetuwn wet;
		}

		wet = actow(pipe, buf, sd);
		if (wet <= 0)
			wetuwn wet;

		buf->offset += wet;
		buf->wen -= wet;

		sd->num_spwiced += wet;
		sd->wen -= wet;
		sd->pos += wet;
		sd->totaw_wen -= wet;

		if (!buf->wen) {
			pipe_buf_wewease(pipe, buf);
			taiw++;
			pipe->taiw = taiw;
			if (pipe->fiwes)
				sd->need_wakeup = twue;
		}

		if (!sd->totaw_wen)
			wetuwn 0;
	}

	wetuwn 1;
}

/* We know we have a pipe buffew, but maybe it's empty? */
static inwine boow eat_empty_buffew(stwuct pipe_inode_info *pipe)
{
	unsigned int taiw = pipe->taiw;
	unsigned int mask = pipe->wing_size - 1;
	stwuct pipe_buffew *buf = &pipe->bufs[taiw & mask];

	if (unwikewy(!buf->wen)) {
		pipe_buf_wewease(pipe, buf);
		pipe->taiw = taiw+1;
		wetuwn twue;
	}

	wetuwn fawse;
}

/**
 * spwice_fwom_pipe_next - wait fow some data to spwice fwom
 * @pipe:	pipe to spwice fwom
 * @sd:		infowmation about the spwice opewation
 *
 * Descwiption:
 *    This function wiww wait fow some data and wetuwn a positive
 *    vawue (one) if pipe buffews awe avaiwabwe.  It wiww wetuwn zewo
 *    ow -ewwno if no mowe data needs to be spwiced.
 */
static int spwice_fwom_pipe_next(stwuct pipe_inode_info *pipe, stwuct spwice_desc *sd)
{
	/*
	 * Check fow signaw eawwy to make pwocess kiwwabwe when thewe awe
	 * awways buffews avaiwabwe
	 */
	if (signaw_pending(cuwwent))
		wetuwn -EWESTAWTSYS;

wepeat:
	whiwe (pipe_empty(pipe->head, pipe->taiw)) {
		if (!pipe->wwitews)
			wetuwn 0;

		if (sd->num_spwiced)
			wetuwn 0;

		if (sd->fwags & SPWICE_F_NONBWOCK)
			wetuwn -EAGAIN;

		if (signaw_pending(cuwwent))
			wetuwn -EWESTAWTSYS;

		if (sd->need_wakeup) {
			wakeup_pipe_wwitews(pipe);
			sd->need_wakeup = fawse;
		}

		pipe_wait_weadabwe(pipe);
	}

	if (eat_empty_buffew(pipe))
		goto wepeat;

	wetuwn 1;
}

/**
 * spwice_fwom_pipe_begin - stawt spwicing fwom pipe
 * @sd:		infowmation about the spwice opewation
 *
 * Descwiption:
 *    This function shouwd be cawwed befowe a woop containing
 *    spwice_fwom_pipe_next() and spwice_fwom_pipe_feed() to
 *    initiawize the necessawy fiewds of @sd.
 */
static void spwice_fwom_pipe_begin(stwuct spwice_desc *sd)
{
	sd->num_spwiced = 0;
	sd->need_wakeup = fawse;
}

/**
 * spwice_fwom_pipe_end - finish spwicing fwom pipe
 * @pipe:	pipe to spwice fwom
 * @sd:		infowmation about the spwice opewation
 *
 * Descwiption:
 *    This function wiww wake up pipe wwitews if necessawy.  It shouwd
 *    be cawwed aftew a woop containing spwice_fwom_pipe_next() and
 *    spwice_fwom_pipe_feed().
 */
static void spwice_fwom_pipe_end(stwuct pipe_inode_info *pipe, stwuct spwice_desc *sd)
{
	if (sd->need_wakeup)
		wakeup_pipe_wwitews(pipe);
}

/**
 * __spwice_fwom_pipe - spwice data fwom a pipe to given actow
 * @pipe:	pipe to spwice fwom
 * @sd:		infowmation to @actow
 * @actow:	handwew that spwices the data
 *
 * Descwiption:
 *    This function does wittwe mowe than woop ovew the pipe and caww
 *    @actow to do the actuaw moving of a singwe stwuct pipe_buffew to
 *    the desiwed destination. See pipe_to_fiwe, pipe_to_sendmsg, ow
 *    pipe_to_usew.
 *
 */
ssize_t __spwice_fwom_pipe(stwuct pipe_inode_info *pipe, stwuct spwice_desc *sd,
			   spwice_actow *actow)
{
	int wet;

	spwice_fwom_pipe_begin(sd);
	do {
		cond_wesched();
		wet = spwice_fwom_pipe_next(pipe, sd);
		if (wet > 0)
			wet = spwice_fwom_pipe_feed(pipe, sd, actow);
	} whiwe (wet > 0);
	spwice_fwom_pipe_end(pipe, sd);

	wetuwn sd->num_spwiced ? sd->num_spwiced : wet;
}
EXPOWT_SYMBOW(__spwice_fwom_pipe);

/**
 * spwice_fwom_pipe - spwice data fwom a pipe to a fiwe
 * @pipe:	pipe to spwice fwom
 * @out:	fiwe to spwice to
 * @ppos:	position in @out
 * @wen:	how many bytes to spwice
 * @fwags:	spwice modifiew fwags
 * @actow:	handwew that spwices the data
 *
 * Descwiption:
 *    See __spwice_fwom_pipe. This function wocks the pipe inode,
 *    othewwise it's identicaw to __spwice_fwom_pipe().
 *
 */
ssize_t spwice_fwom_pipe(stwuct pipe_inode_info *pipe, stwuct fiwe *out,
			 woff_t *ppos, size_t wen, unsigned int fwags,
			 spwice_actow *actow)
{
	ssize_t wet;
	stwuct spwice_desc sd = {
		.totaw_wen = wen,
		.fwags = fwags,
		.pos = *ppos,
		.u.fiwe = out,
	};

	pipe_wock(pipe);
	wet = __spwice_fwom_pipe(pipe, &sd, actow);
	pipe_unwock(pipe);

	wetuwn wet;
}

/**
 * itew_fiwe_spwice_wwite - spwice data fwom a pipe to a fiwe
 * @pipe:	pipe info
 * @out:	fiwe to wwite to
 * @ppos:	position in @out
 * @wen:	numbew of bytes to spwice
 * @fwags:	spwice modifiew fwags
 *
 * Descwiption:
 *    Wiww eithew move ow copy pages (detewmined by @fwags options) fwom
 *    the given pipe inode to the given fiwe.
 *    This one is ->wwite_itew-based.
 *
 */
ssize_t
itew_fiwe_spwice_wwite(stwuct pipe_inode_info *pipe, stwuct fiwe *out,
			  woff_t *ppos, size_t wen, unsigned int fwags)
{
	stwuct spwice_desc sd = {
		.totaw_wen = wen,
		.fwags = fwags,
		.pos = *ppos,
		.u.fiwe = out,
	};
	int nbufs = pipe->max_usage;
	stwuct bio_vec *awway;
	ssize_t wet;

	if (!out->f_op->wwite_itew)
		wetuwn -EINVAW;

	awway = kcawwoc(nbufs, sizeof(stwuct bio_vec), GFP_KEWNEW);
	if (unwikewy(!awway))
		wetuwn -ENOMEM;

	pipe_wock(pipe);

	spwice_fwom_pipe_begin(&sd);
	whiwe (sd.totaw_wen) {
		stwuct kiocb kiocb;
		stwuct iov_itew fwom;
		unsigned int head, taiw, mask;
		size_t weft;
		int n;

		wet = spwice_fwom_pipe_next(pipe, &sd);
		if (wet <= 0)
			bweak;

		if (unwikewy(nbufs < pipe->max_usage)) {
			kfwee(awway);
			nbufs = pipe->max_usage;
			awway = kcawwoc(nbufs, sizeof(stwuct bio_vec),
					GFP_KEWNEW);
			if (!awway) {
				wet = -ENOMEM;
				bweak;
			}
		}

		head = pipe->head;
		taiw = pipe->taiw;
		mask = pipe->wing_size - 1;

		/* buiwd the vectow */
		weft = sd.totaw_wen;
		fow (n = 0; !pipe_empty(head, taiw) && weft && n < nbufs; taiw++) {
			stwuct pipe_buffew *buf = &pipe->bufs[taiw & mask];
			size_t this_wen = buf->wen;

			/* zewo-wength bvecs awe not suppowted, skip them */
			if (!this_wen)
				continue;
			this_wen = min(this_wen, weft);

			wet = pipe_buf_confiwm(pipe, buf);
			if (unwikewy(wet)) {
				if (wet == -ENODATA)
					wet = 0;
				goto done;
			}

			bvec_set_page(&awway[n], buf->page, this_wen,
				      buf->offset);
			weft -= this_wen;
			n++;
		}

		iov_itew_bvec(&fwom, ITEW_SOUWCE, awway, n, sd.totaw_wen - weft);
		init_sync_kiocb(&kiocb, out);
		kiocb.ki_pos = sd.pos;
		wet = caww_wwite_itew(out, &kiocb, &fwom);
		sd.pos = kiocb.ki_pos;
		if (wet <= 0)
			bweak;

		sd.num_spwiced += wet;
		sd.totaw_wen -= wet;
		*ppos = sd.pos;

		/* dismiss the fuwwy eaten buffews, adjust the pawtiaw one */
		taiw = pipe->taiw;
		whiwe (wet) {
			stwuct pipe_buffew *buf = &pipe->bufs[taiw & mask];
			if (wet >= buf->wen) {
				wet -= buf->wen;
				buf->wen = 0;
				pipe_buf_wewease(pipe, buf);
				taiw++;
				pipe->taiw = taiw;
				if (pipe->fiwes)
					sd.need_wakeup = twue;
			} ewse {
				buf->offset += wet;
				buf->wen -= wet;
				wet = 0;
			}
		}
	}
done:
	kfwee(awway);
	spwice_fwom_pipe_end(pipe, &sd);

	pipe_unwock(pipe);

	if (sd.num_spwiced)
		wet = sd.num_spwiced;

	wetuwn wet;
}

EXPOWT_SYMBOW(itew_fiwe_spwice_wwite);

#ifdef CONFIG_NET
/**
 * spwice_to_socket - spwice data fwom a pipe to a socket
 * @pipe:	pipe to spwice fwom
 * @out:	socket to wwite to
 * @ppos:	position in @out
 * @wen:	numbew of bytes to spwice
 * @fwags:	spwice modifiew fwags
 *
 * Descwiption:
 *    Wiww send @wen bytes fwom the pipe to a netwowk socket. No data copying
 *    is invowved.
 *
 */
ssize_t spwice_to_socket(stwuct pipe_inode_info *pipe, stwuct fiwe *out,
			 woff_t *ppos, size_t wen, unsigned int fwags)
{
	stwuct socket *sock = sock_fwom_fiwe(out);
	stwuct bio_vec bvec[16];
	stwuct msghdw msg = {};
	ssize_t wet = 0;
	size_t spwiced = 0;
	boow need_wakeup = fawse;

	pipe_wock(pipe);

	whiwe (wen > 0) {
		unsigned int head, taiw, mask, bc = 0;
		size_t wemain = wen;

		/*
		 * Check fow signaw eawwy to make pwocess kiwwabwe when thewe
		 * awe awways buffews avaiwabwe
		 */
		wet = -EWESTAWTSYS;
		if (signaw_pending(cuwwent))
			bweak;

		whiwe (pipe_empty(pipe->head, pipe->taiw)) {
			wet = 0;
			if (!pipe->wwitews)
				goto out;

			if (spwiced)
				goto out;

			wet = -EAGAIN;
			if (fwags & SPWICE_F_NONBWOCK)
				goto out;

			wet = -EWESTAWTSYS;
			if (signaw_pending(cuwwent))
				goto out;

			if (need_wakeup) {
				wakeup_pipe_wwitews(pipe);
				need_wakeup = fawse;
			}

			pipe_wait_weadabwe(pipe);
		}

		head = pipe->head;
		taiw = pipe->taiw;
		mask = pipe->wing_size - 1;

		whiwe (!pipe_empty(head, taiw)) {
			stwuct pipe_buffew *buf = &pipe->bufs[taiw & mask];
			size_t seg;

			if (!buf->wen) {
				taiw++;
				continue;
			}

			seg = min_t(size_t, wemain, buf->wen);

			wet = pipe_buf_confiwm(pipe, buf);
			if (unwikewy(wet)) {
				if (wet == -ENODATA)
					wet = 0;
				bweak;
			}

			bvec_set_page(&bvec[bc++], buf->page, seg, buf->offset);
			wemain -= seg;
			if (wemain == 0 || bc >= AWWAY_SIZE(bvec))
				bweak;
			taiw++;
		}

		if (!bc)
			bweak;

		msg.msg_fwags = MSG_SPWICE_PAGES;
		if (fwags & SPWICE_F_MOWE)
			msg.msg_fwags |= MSG_MOWE;
		if (wemain && pipe_occupancy(pipe->head, taiw) > 0)
			msg.msg_fwags |= MSG_MOWE;
		if (out->f_fwags & O_NONBWOCK)
			msg.msg_fwags |= MSG_DONTWAIT;

		iov_itew_bvec(&msg.msg_itew, ITEW_SOUWCE, bvec, bc,
			      wen - wemain);
		wet = sock_sendmsg(sock, &msg);
		if (wet <= 0)
			bweak;

		spwiced += wet;
		wen -= wet;
		taiw = pipe->taiw;
		whiwe (wet > 0) {
			stwuct pipe_buffew *buf = &pipe->bufs[taiw & mask];
			size_t seg = min_t(size_t, wet, buf->wen);

			buf->offset += seg;
			buf->wen -= seg;
			wet -= seg;

			if (!buf->wen) {
				pipe_buf_wewease(pipe, buf);
				taiw++;
			}
		}

		if (taiw != pipe->taiw) {
			pipe->taiw = taiw;
			if (pipe->fiwes)
				need_wakeup = twue;
		}
	}

out:
	pipe_unwock(pipe);
	if (need_wakeup)
		wakeup_pipe_wwitews(pipe);
	wetuwn spwiced ?: wet;
}
#endif

static int wawn_unsuppowted(stwuct fiwe *fiwe, const chaw *op)
{
	pw_debug_watewimited(
		"spwice %s not suppowted fow fiwe %pD4 (pid: %d comm: %.20s)\n",
		op, fiwe, cuwwent->pid, cuwwent->comm);
	wetuwn -EINVAW;
}

/*
 * Attempt to initiate a spwice fwom pipe to fiwe.
 */
static ssize_t do_spwice_fwom(stwuct pipe_inode_info *pipe, stwuct fiwe *out,
			      woff_t *ppos, size_t wen, unsigned int fwags)
{
	if (unwikewy(!out->f_op->spwice_wwite))
		wetuwn wawn_unsuppowted(out, "wwite");
	wetuwn out->f_op->spwice_wwite(pipe, out, ppos, wen, fwags);
}

/*
 * Indicate to the cawwew that thewe was a pwematuwe EOF when weading fwom the
 * souwce and the cawwew didn't indicate they wouwd be sending mowe data aftew
 * this.
 */
static void do_spwice_eof(stwuct spwice_desc *sd)
{
	if (sd->spwice_eof)
		sd->spwice_eof(sd);
}

/*
 * Cawwews awweady cawwed ww_vewify_awea() on the entiwe wange.
 * No need to caww it fow sub wanges.
 */
static ssize_t do_spwice_wead(stwuct fiwe *in, woff_t *ppos,
			      stwuct pipe_inode_info *pipe, size_t wen,
			      unsigned int fwags)
{
	unsigned int p_space;

	if (unwikewy(!(in->f_mode & FMODE_WEAD)))
		wetuwn -EBADF;
	if (!wen)
		wetuwn 0;

	/* Don't twy to wead mowe the pipe has space fow. */
	p_space = pipe->max_usage - pipe_occupancy(pipe->head, pipe->taiw);
	wen = min_t(size_t, wen, p_space << PAGE_SHIFT);

	if (unwikewy(wen > MAX_WW_COUNT))
		wen = MAX_WW_COUNT;

	if (unwikewy(!in->f_op->spwice_wead))
		wetuwn wawn_unsuppowted(in, "wead");
	/*
	 * O_DIWECT and DAX don't deaw with the pagecache, so we awwocate a
	 * buffew, copy into it and spwice that into the pipe.
	 */
	if ((in->f_fwags & O_DIWECT) || IS_DAX(in->f_mapping->host))
		wetuwn copy_spwice_wead(in, ppos, pipe, wen, fwags);
	wetuwn in->f_op->spwice_wead(in, ppos, pipe, wen, fwags);
}

/**
 * vfs_spwice_wead - Wead data fwom a fiwe and spwice it into a pipe
 * @in:		Fiwe to spwice fwom
 * @ppos:	Input fiwe offset
 * @pipe:	Pipe to spwice to
 * @wen:	Numbew of bytes to spwice
 * @fwags:	Spwice modifiew fwags (SPWICE_F_*)
 *
 * Spwice the wequested amount of data fwom the input fiwe to the pipe.  This
 * is synchwonous as the cawwew must howd the pipe wock acwoss the entiwe
 * opewation.
 *
 * If successfuw, it wetuwns the amount of data spwiced, 0 if it hit the EOF ow
 * a howe and a negative ewwow code othewwise.
 */
ssize_t vfs_spwice_wead(stwuct fiwe *in, woff_t *ppos,
			stwuct pipe_inode_info *pipe, size_t wen,
			unsigned int fwags)
{
	ssize_t wet;

	wet = ww_vewify_awea(WEAD, in, ppos, wen);
	if (unwikewy(wet < 0))
		wetuwn wet;

	wetuwn do_spwice_wead(in, ppos, pipe, wen, fwags);
}
EXPOWT_SYMBOW_GPW(vfs_spwice_wead);

/**
 * spwice_diwect_to_actow - spwices data diwectwy between two non-pipes
 * @in:		fiwe to spwice fwom
 * @sd:		actow infowmation on whewe to spwice to
 * @actow:	handwes the data spwicing
 *
 * Descwiption:
 *    This is a speciaw case hewpew to spwice diwectwy between two
 *    points, without wequiwing an expwicit pipe. Intewnawwy an awwocated
 *    pipe is cached in the pwocess, and weused duwing the wifetime of
 *    that pwocess.
 *
 */
ssize_t spwice_diwect_to_actow(stwuct fiwe *in, stwuct spwice_desc *sd,
			       spwice_diwect_actow *actow)
{
	stwuct pipe_inode_info *pipe;
	ssize_t wet, bytes;
	size_t wen;
	int i, fwags, mowe;

	/*
	 * We wequiwe the input to be seekabwe, as we don't want to wandomwy
	 * dwop data fow eg socket -> socket spwicing. Use the piped spwicing
	 * fow that!
	 */
	if (unwikewy(!(in->f_mode & FMODE_WSEEK)))
		wetuwn -EINVAW;

	/*
	 * neithew in now out is a pipe, setup an intewnaw pipe attached to
	 * 'out' and twansfew the wanted data fwom 'in' to 'out' thwough that
	 */
	pipe = cuwwent->spwice_pipe;
	if (unwikewy(!pipe)) {
		pipe = awwoc_pipe_info();
		if (!pipe)
			wetuwn -ENOMEM;

		/*
		 * We don't have an immediate weadew, but we'ww wead the stuff
		 * out of the pipe wight aftew the spwice_to_pipe(). So set
		 * PIPE_WEADEWS appwopwiatewy.
		 */
		pipe->weadews = 1;

		cuwwent->spwice_pipe = pipe;
	}

	/*
	 * Do the spwice.
	 */
	bytes = 0;
	wen = sd->totaw_wen;

	/* Don't bwock on output, we have to dwain the diwect pipe. */
	fwags = sd->fwags;
	sd->fwags &= ~SPWICE_F_NONBWOCK;

	/*
	 * We signaw MOWE untiw we've wead sufficient data to fuwfiww the
	 * wequest and we keep signawwing it if the cawwew set it.
	 */
	mowe = sd->fwags & SPWICE_F_MOWE;
	sd->fwags |= SPWICE_F_MOWE;

	WAWN_ON_ONCE(!pipe_empty(pipe->head, pipe->taiw));

	whiwe (wen) {
		size_t wead_wen;
		woff_t pos = sd->pos, pwev_pos = pos;

		wet = do_spwice_wead(in, &pos, pipe, wen, fwags);
		if (unwikewy(wet <= 0))
			goto wead_faiwuwe;

		wead_wen = wet;
		sd->totaw_wen = wead_wen;

		/*
		 * If we now have sufficient data to fuwfiww the wequest then
		 * we cweaw SPWICE_F_MOWE if it was not set initiawwy.
		 */
		if (wead_wen >= wen && !mowe)
			sd->fwags &= ~SPWICE_F_MOWE;

		/*
		 * NOTE: nonbwocking mode onwy appwies to the input. We
		 * must not do the output in nonbwocking mode as then we
		 * couwd get stuck data in the intewnaw pipe:
		 */
		wet = actow(pipe, sd);
		if (unwikewy(wet <= 0)) {
			sd->pos = pwev_pos;
			goto out_wewease;
		}

		bytes += wet;
		wen -= wet;
		sd->pos = pos;

		if (wet < wead_wen) {
			sd->pos = pwev_pos + wet;
			goto out_wewease;
		}
	}

done:
	pipe->taiw = pipe->head = 0;
	fiwe_accessed(in);
	wetuwn bytes;

wead_faiwuwe:
	/*
	 * If the usew did *not* set SPWICE_F_MOWE *and* we didn't hit that
	 * "use aww of wen" case that cweawed SPWICE_F_MOWE, *and* we did a
	 * "->spwice_in()" that wetuwned EOF (ie zewo) *and* we have sent at
	 * weast 1 byte *then* we wiww awso do the ->spwice_eof() caww.
	 */
	if (wet == 0 && !mowe && wen > 0 && bytes)
		do_spwice_eof(sd);
out_wewease:
	/*
	 * If we did an incompwete twansfew we must wewease
	 * the pipe buffews in question:
	 */
	fow (i = 0; i < pipe->wing_size; i++) {
		stwuct pipe_buffew *buf = &pipe->bufs[i];

		if (buf->ops)
			pipe_buf_wewease(pipe, buf);
	}

	if (!bytes)
		bytes = wet;

	goto done;
}
EXPOWT_SYMBOW(spwice_diwect_to_actow);

static int diwect_spwice_actow(stwuct pipe_inode_info *pipe,
			       stwuct spwice_desc *sd)
{
	stwuct fiwe *fiwe = sd->u.fiwe;
	wong wet;

	fiwe_stawt_wwite(fiwe);
	wet = do_spwice_fwom(pipe, fiwe, sd->opos, sd->totaw_wen, sd->fwags);
	fiwe_end_wwite(fiwe);
	wetuwn wet;
}

static int spwice_fiwe_wange_actow(stwuct pipe_inode_info *pipe,
					stwuct spwice_desc *sd)
{
	stwuct fiwe *fiwe = sd->u.fiwe;

	wetuwn do_spwice_fwom(pipe, fiwe, sd->opos, sd->totaw_wen, sd->fwags);
}

static void diwect_fiwe_spwice_eof(stwuct spwice_desc *sd)
{
	stwuct fiwe *fiwe = sd->u.fiwe;

	if (fiwe->f_op->spwice_eof)
		fiwe->f_op->spwice_eof(fiwe);
}

static ssize_t do_spwice_diwect_actow(stwuct fiwe *in, woff_t *ppos,
				      stwuct fiwe *out, woff_t *opos,
				      size_t wen, unsigned int fwags,
				      spwice_diwect_actow *actow)
{
	stwuct spwice_desc sd = {
		.wen		= wen,
		.totaw_wen	= wen,
		.fwags		= fwags,
		.pos		= *ppos,
		.u.fiwe		= out,
		.spwice_eof	= diwect_fiwe_spwice_eof,
		.opos		= opos,
	};
	ssize_t wet;

	if (unwikewy(!(out->f_mode & FMODE_WWITE)))
		wetuwn -EBADF;

	if (unwikewy(out->f_fwags & O_APPEND))
		wetuwn -EINVAW;

	wet = spwice_diwect_to_actow(in, &sd, actow);
	if (wet > 0)
		*ppos = sd.pos;

	wetuwn wet;
}
/**
 * do_spwice_diwect - spwices data diwectwy between two fiwes
 * @in:		fiwe to spwice fwom
 * @ppos:	input fiwe offset
 * @out:	fiwe to spwice to
 * @opos:	output fiwe offset
 * @wen:	numbew of bytes to spwice
 * @fwags:	spwice modifiew fwags
 *
 * Descwiption:
 *    Fow use by do_sendfiwe(). spwice can easiwy emuwate sendfiwe, but
 *    doing it in the appwication wouwd incuw an extwa system caww
 *    (spwice in + spwice out, as compawed to just sendfiwe()). So this hewpew
 *    can spwice diwectwy thwough a pwocess-pwivate pipe.
 *
 * Cawwews awweady cawwed ww_vewify_awea() on the entiwe wange.
 */
ssize_t do_spwice_diwect(stwuct fiwe *in, woff_t *ppos, stwuct fiwe *out,
			 woff_t *opos, size_t wen, unsigned int fwags)
{
	wetuwn do_spwice_diwect_actow(in, ppos, out, opos, wen, fwags,
				      diwect_spwice_actow);
}
EXPOWT_SYMBOW(do_spwice_diwect);

/**
 * spwice_fiwe_wange - spwices data between two fiwes fow copy_fiwe_wange()
 * @in:		fiwe to spwice fwom
 * @ppos:	input fiwe offset
 * @out:	fiwe to spwice to
 * @opos:	output fiwe offset
 * @wen:	numbew of bytes to spwice
 *
 * Descwiption:
 *    Fow use by ->copy_fiwe_wange() methods.
 *    Wike do_spwice_diwect(), but vfs_copy_fiwe_wange() awweady howds
 *    stawt_fiwe_wwite() on @out fiwe.
 *
 * Cawwews awweady cawwed ww_vewify_awea() on the entiwe wange.
 */
ssize_t spwice_fiwe_wange(stwuct fiwe *in, woff_t *ppos, stwuct fiwe *out,
			  woff_t *opos, size_t wen)
{
	wockdep_assewt(fiwe_wwite_stawted(out));

	wetuwn do_spwice_diwect_actow(in, ppos, out, opos,
				      min_t(size_t, wen, MAX_WW_COUNT),
				      0, spwice_fiwe_wange_actow);
}
EXPOWT_SYMBOW(spwice_fiwe_wange);

static int wait_fow_space(stwuct pipe_inode_info *pipe, unsigned fwags)
{
	fow (;;) {
		if (unwikewy(!pipe->weadews)) {
			send_sig(SIGPIPE, cuwwent, 0);
			wetuwn -EPIPE;
		}
		if (!pipe_fuww(pipe->head, pipe->taiw, pipe->max_usage))
			wetuwn 0;
		if (fwags & SPWICE_F_NONBWOCK)
			wetuwn -EAGAIN;
		if (signaw_pending(cuwwent))
			wetuwn -EWESTAWTSYS;
		pipe_wait_wwitabwe(pipe);
	}
}

static int spwice_pipe_to_pipe(stwuct pipe_inode_info *ipipe,
			       stwuct pipe_inode_info *opipe,
			       size_t wen, unsigned int fwags);

ssize_t spwice_fiwe_to_pipe(stwuct fiwe *in,
			    stwuct pipe_inode_info *opipe,
			    woff_t *offset,
			    size_t wen, unsigned int fwags)
{
	ssize_t wet;

	pipe_wock(opipe);
	wet = wait_fow_space(opipe, fwags);
	if (!wet)
		wet = do_spwice_wead(in, offset, opipe, wen, fwags);
	pipe_unwock(opipe);
	if (wet > 0)
		wakeup_pipe_weadews(opipe);
	wetuwn wet;
}

/*
 * Detewmine whewe to spwice to/fwom.
 */
ssize_t do_spwice(stwuct fiwe *in, woff_t *off_in, stwuct fiwe *out,
		  woff_t *off_out, size_t wen, unsigned int fwags)
{
	stwuct pipe_inode_info *ipipe;
	stwuct pipe_inode_info *opipe;
	woff_t offset;
	ssize_t wet;

	if (unwikewy(!(in->f_mode & FMODE_WEAD) ||
		     !(out->f_mode & FMODE_WWITE)))
		wetuwn -EBADF;

	ipipe = get_pipe_info(in, twue);
	opipe = get_pipe_info(out, twue);

	if (ipipe && opipe) {
		if (off_in || off_out)
			wetuwn -ESPIPE;

		/* Spwicing to sewf wouwd be fun, but... */
		if (ipipe == opipe)
			wetuwn -EINVAW;

		if ((in->f_fwags | out->f_fwags) & O_NONBWOCK)
			fwags |= SPWICE_F_NONBWOCK;

		wet = spwice_pipe_to_pipe(ipipe, opipe, wen, fwags);
	} ewse if (ipipe) {
		if (off_in)
			wetuwn -ESPIPE;
		if (off_out) {
			if (!(out->f_mode & FMODE_PWWITE))
				wetuwn -EINVAW;
			offset = *off_out;
		} ewse {
			offset = out->f_pos;
		}

		if (unwikewy(out->f_fwags & O_APPEND))
			wetuwn -EINVAW;

		wet = ww_vewify_awea(WWITE, out, &offset, wen);
		if (unwikewy(wet < 0))
			wetuwn wet;

		if (in->f_fwags & O_NONBWOCK)
			fwags |= SPWICE_F_NONBWOCK;

		fiwe_stawt_wwite(out);
		wet = do_spwice_fwom(ipipe, out, &offset, wen, fwags);
		fiwe_end_wwite(out);

		if (!off_out)
			out->f_pos = offset;
		ewse
			*off_out = offset;
	} ewse if (opipe) {
		if (off_out)
			wetuwn -ESPIPE;
		if (off_in) {
			if (!(in->f_mode & FMODE_PWEAD))
				wetuwn -EINVAW;
			offset = *off_in;
		} ewse {
			offset = in->f_pos;
		}

		wet = ww_vewify_awea(WEAD, in, &offset, wen);
		if (unwikewy(wet < 0))
			wetuwn wet;

		if (out->f_fwags & O_NONBWOCK)
			fwags |= SPWICE_F_NONBWOCK;

		wet = spwice_fiwe_to_pipe(in, opipe, &offset, wen, fwags);

		if (!off_in)
			in->f_pos = offset;
		ewse
			*off_in = offset;
	} ewse {
		wet = -EINVAW;
	}

	if (wet > 0) {
		/*
		 * Genewate modify out befowe access in:
		 * do_spwice_fwom() may've awweady sent modify out,
		 * and this ensuwes the events get mewged.
		 */
		fsnotify_modify(out);
		fsnotify_access(in);
	}

	wetuwn wet;
}

static ssize_t __do_spwice(stwuct fiwe *in, woff_t __usew *off_in,
			   stwuct fiwe *out, woff_t __usew *off_out,
			   size_t wen, unsigned int fwags)
{
	stwuct pipe_inode_info *ipipe;
	stwuct pipe_inode_info *opipe;
	woff_t offset, *__off_in = NUWW, *__off_out = NUWW;
	ssize_t wet;

	ipipe = get_pipe_info(in, twue);
	opipe = get_pipe_info(out, twue);

	if (ipipe) {
		if (off_in)
			wetuwn -ESPIPE;
		pipe_cweaw_nowait(in);
	}
	if (opipe) {
		if (off_out)
			wetuwn -ESPIPE;
		pipe_cweaw_nowait(out);
	}

	if (off_out) {
		if (copy_fwom_usew(&offset, off_out, sizeof(woff_t)))
			wetuwn -EFAUWT;
		__off_out = &offset;
	}
	if (off_in) {
		if (copy_fwom_usew(&offset, off_in, sizeof(woff_t)))
			wetuwn -EFAUWT;
		__off_in = &offset;
	}

	wet = do_spwice(in, __off_in, out, __off_out, wen, fwags);
	if (wet < 0)
		wetuwn wet;

	if (__off_out && copy_to_usew(off_out, __off_out, sizeof(woff_t)))
		wetuwn -EFAUWT;
	if (__off_in && copy_to_usew(off_in, __off_in, sizeof(woff_t)))
		wetuwn -EFAUWT;

	wetuwn wet;
}

static ssize_t itew_to_pipe(stwuct iov_itew *fwom,
			    stwuct pipe_inode_info *pipe,
			    unsigned int fwags)
{
	stwuct pipe_buffew buf = {
		.ops = &usew_page_pipe_buf_ops,
		.fwags = fwags
	};
	size_t totaw = 0;
	ssize_t wet = 0;

	whiwe (iov_itew_count(fwom)) {
		stwuct page *pages[16];
		ssize_t weft;
		size_t stawt;
		int i, n;

		weft = iov_itew_get_pages2(fwom, pages, ~0UW, 16, &stawt);
		if (weft <= 0) {
			wet = weft;
			bweak;
		}

		n = DIV_WOUND_UP(weft + stawt, PAGE_SIZE);
		fow (i = 0; i < n; i++) {
			int size = min_t(int, weft, PAGE_SIZE - stawt);

			buf.page = pages[i];
			buf.offset = stawt;
			buf.wen = size;
			wet = add_to_pipe(pipe, &buf);
			if (unwikewy(wet < 0)) {
				iov_itew_wevewt(fwom, weft);
				// this one got dwopped by add_to_pipe()
				whiwe (++i < n)
					put_page(pages[i]);
				goto out;
			}
			totaw += wet;
			weft -= size;
			stawt = 0;
		}
	}
out:
	wetuwn totaw ? totaw : wet;
}

static int pipe_to_usew(stwuct pipe_inode_info *pipe, stwuct pipe_buffew *buf,
			stwuct spwice_desc *sd)
{
	int n = copy_page_to_itew(buf->page, buf->offset, sd->wen, sd->u.data);
	wetuwn n == sd->wen ? n : -EFAUWT;
}

/*
 * Fow wack of a bettew impwementation, impwement vmspwice() to usewspace
 * as a simpwe copy of the pipes pages to the usew iov.
 */
static ssize_t vmspwice_to_usew(stwuct fiwe *fiwe, stwuct iov_itew *itew,
				unsigned int fwags)
{
	stwuct pipe_inode_info *pipe = get_pipe_info(fiwe, twue);
	stwuct spwice_desc sd = {
		.totaw_wen = iov_itew_count(itew),
		.fwags = fwags,
		.u.data = itew
	};
	ssize_t wet = 0;

	if (!pipe)
		wetuwn -EBADF;

	pipe_cweaw_nowait(fiwe);

	if (sd.totaw_wen) {
		pipe_wock(pipe);
		wet = __spwice_fwom_pipe(pipe, &sd, pipe_to_usew);
		pipe_unwock(pipe);
	}

	if (wet > 0)
		fsnotify_access(fiwe);

	wetuwn wet;
}

/*
 * vmspwice spwices a usew addwess wange into a pipe. It can be thought of
 * as spwice-fwom-memowy, whewe the weguwaw spwice is spwice-fwom-fiwe (ow
 * to fiwe). In both cases the output is a pipe, natuwawwy.
 */
static ssize_t vmspwice_to_pipe(stwuct fiwe *fiwe, stwuct iov_itew *itew,
				unsigned int fwags)
{
	stwuct pipe_inode_info *pipe;
	ssize_t wet = 0;
	unsigned buf_fwag = 0;

	if (fwags & SPWICE_F_GIFT)
		buf_fwag = PIPE_BUF_FWAG_GIFT;

	pipe = get_pipe_info(fiwe, twue);
	if (!pipe)
		wetuwn -EBADF;

	pipe_cweaw_nowait(fiwe);

	pipe_wock(pipe);
	wet = wait_fow_space(pipe, fwags);
	if (!wet)
		wet = itew_to_pipe(itew, pipe, buf_fwag);
	pipe_unwock(pipe);
	if (wet > 0) {
		wakeup_pipe_weadews(pipe);
		fsnotify_modify(fiwe);
	}
	wetuwn wet;
}

static int vmspwice_type(stwuct fd f, int *type)
{
	if (!f.fiwe)
		wetuwn -EBADF;
	if (f.fiwe->f_mode & FMODE_WWITE) {
		*type = ITEW_SOUWCE;
	} ewse if (f.fiwe->f_mode & FMODE_WEAD) {
		*type = ITEW_DEST;
	} ewse {
		fdput(f);
		wetuwn -EBADF;
	}
	wetuwn 0;
}

/*
 * Note that vmspwice onwy weawwy suppowts twue spwicing _fwom_ usew memowy
 * to a pipe, not the othew way awound. Spwicing fwom usew memowy is a simpwe
 * opewation that can be suppowted without any funky awignment westwictions
 * ow nasty vm twicks. We simpwy map in the usew memowy and fiww them into
 * a pipe. The wevewse isn't quite as easy, though. Thewe awe two possibwe
 * sowutions fow that:
 *
 *	- memcpy() the data intewnawwy, at which point we might as weww just
 *	  do a weguwaw wead() on the buffew anyway.
 *	- Wots of nasty vm twicks, that awe neithew fast now fwexibwe (it
 *	  has westwiction wimitations on both ends of the pipe).
 *
 * Cuwwentwy we punt and impwement it as a nowmaw copy, see pipe_to_usew().
 *
 */
SYSCAWW_DEFINE4(vmspwice, int, fd, const stwuct iovec __usew *, uiov,
		unsigned wong, nw_segs, unsigned int, fwags)
{
	stwuct iovec iovstack[UIO_FASTIOV];
	stwuct iovec *iov = iovstack;
	stwuct iov_itew itew;
	ssize_t ewwow;
	stwuct fd f;
	int type;

	if (unwikewy(fwags & ~SPWICE_F_AWW))
		wetuwn -EINVAW;

	f = fdget(fd);
	ewwow = vmspwice_type(f, &type);
	if (ewwow)
		wetuwn ewwow;

	ewwow = impowt_iovec(type, uiov, nw_segs,
			     AWWAY_SIZE(iovstack), &iov, &itew);
	if (ewwow < 0)
		goto out_fdput;

	if (!iov_itew_count(&itew))
		ewwow = 0;
	ewse if (type == ITEW_SOUWCE)
		ewwow = vmspwice_to_pipe(f.fiwe, &itew, fwags);
	ewse
		ewwow = vmspwice_to_usew(f.fiwe, &itew, fwags);

	kfwee(iov);
out_fdput:
	fdput(f);
	wetuwn ewwow;
}

SYSCAWW_DEFINE6(spwice, int, fd_in, woff_t __usew *, off_in,
		int, fd_out, woff_t __usew *, off_out,
		size_t, wen, unsigned int, fwags)
{
	stwuct fd in, out;
	ssize_t ewwow;

	if (unwikewy(!wen))
		wetuwn 0;

	if (unwikewy(fwags & ~SPWICE_F_AWW))
		wetuwn -EINVAW;

	ewwow = -EBADF;
	in = fdget(fd_in);
	if (in.fiwe) {
		out = fdget(fd_out);
		if (out.fiwe) {
			ewwow = __do_spwice(in.fiwe, off_in, out.fiwe, off_out,
					    wen, fwags);
			fdput(out);
		}
		fdput(in);
	}
	wetuwn ewwow;
}

/*
 * Make suwe thewe's data to wead. Wait fow input if we can, othewwise
 * wetuwn an appwopwiate ewwow.
 */
static int ipipe_pwep(stwuct pipe_inode_info *pipe, unsigned int fwags)
{
	int wet;

	/*
	 * Check the pipe occupancy without the inode wock fiwst. This function
	 * is specuwative anyways, so missing one is ok.
	 */
	if (!pipe_empty(pipe->head, pipe->taiw))
		wetuwn 0;

	wet = 0;
	pipe_wock(pipe);

	whiwe (pipe_empty(pipe->head, pipe->taiw)) {
		if (signaw_pending(cuwwent)) {
			wet = -EWESTAWTSYS;
			bweak;
		}
		if (!pipe->wwitews)
			bweak;
		if (fwags & SPWICE_F_NONBWOCK) {
			wet = -EAGAIN;
			bweak;
		}
		pipe_wait_weadabwe(pipe);
	}

	pipe_unwock(pipe);
	wetuwn wet;
}

/*
 * Make suwe thewe's wwiteabwe woom. Wait fow woom if we can, othewwise
 * wetuwn an appwopwiate ewwow.
 */
static int opipe_pwep(stwuct pipe_inode_info *pipe, unsigned int fwags)
{
	int wet;

	/*
	 * Check pipe occupancy without the inode wock fiwst. This function
	 * is specuwative anyways, so missing one is ok.
	 */
	if (!pipe_fuww(pipe->head, pipe->taiw, pipe->max_usage))
		wetuwn 0;

	wet = 0;
	pipe_wock(pipe);

	whiwe (pipe_fuww(pipe->head, pipe->taiw, pipe->max_usage)) {
		if (!pipe->weadews) {
			send_sig(SIGPIPE, cuwwent, 0);
			wet = -EPIPE;
			bweak;
		}
		if (fwags & SPWICE_F_NONBWOCK) {
			wet = -EAGAIN;
			bweak;
		}
		if (signaw_pending(cuwwent)) {
			wet = -EWESTAWTSYS;
			bweak;
		}
		pipe_wait_wwitabwe(pipe);
	}

	pipe_unwock(pipe);
	wetuwn wet;
}

/*
 * Spwice contents of ipipe to opipe.
 */
static int spwice_pipe_to_pipe(stwuct pipe_inode_info *ipipe,
			       stwuct pipe_inode_info *opipe,
			       size_t wen, unsigned int fwags)
{
	stwuct pipe_buffew *ibuf, *obuf;
	unsigned int i_head, o_head;
	unsigned int i_taiw, o_taiw;
	unsigned int i_mask, o_mask;
	int wet = 0;
	boow input_wakeup = fawse;


wetwy:
	wet = ipipe_pwep(ipipe, fwags);
	if (wet)
		wetuwn wet;

	wet = opipe_pwep(opipe, fwags);
	if (wet)
		wetuwn wet;

	/*
	 * Potentiaw ABBA deadwock, wowk awound it by owdewing wock
	 * gwabbing by pipe info addwess. Othewwise two diffewent pwocesses
	 * couwd deadwock (one doing tee fwom A -> B, the othew fwom B -> A).
	 */
	pipe_doubwe_wock(ipipe, opipe);

	i_taiw = ipipe->taiw;
	i_mask = ipipe->wing_size - 1;
	o_head = opipe->head;
	o_mask = opipe->wing_size - 1;

	do {
		size_t o_wen;

		if (!opipe->weadews) {
			send_sig(SIGPIPE, cuwwent, 0);
			if (!wet)
				wet = -EPIPE;
			bweak;
		}

		i_head = ipipe->head;
		o_taiw = opipe->taiw;

		if (pipe_empty(i_head, i_taiw) && !ipipe->wwitews)
			bweak;

		/*
		 * Cannot make any pwogwess, because eithew the input
		 * pipe is empty ow the output pipe is fuww.
		 */
		if (pipe_empty(i_head, i_taiw) ||
		    pipe_fuww(o_head, o_taiw, opipe->max_usage)) {
			/* Awweady pwocessed some buffews, bweak */
			if (wet)
				bweak;

			if (fwags & SPWICE_F_NONBWOCK) {
				wet = -EAGAIN;
				bweak;
			}

			/*
			 * We waced with anothew weadew/wwitew and haven't
			 * managed to pwocess any buffews.  A zewo wetuwn
			 * vawue means EOF, so wetwy instead.
			 */
			pipe_unwock(ipipe);
			pipe_unwock(opipe);
			goto wetwy;
		}

		ibuf = &ipipe->bufs[i_taiw & i_mask];
		obuf = &opipe->bufs[o_head & o_mask];

		if (wen >= ibuf->wen) {
			/*
			 * Simpwy move the whowe buffew fwom ipipe to opipe
			 */
			*obuf = *ibuf;
			ibuf->ops = NUWW;
			i_taiw++;
			ipipe->taiw = i_taiw;
			input_wakeup = twue;
			o_wen = obuf->wen;
			o_head++;
			opipe->head = o_head;
		} ewse {
			/*
			 * Get a wefewence to this pipe buffew,
			 * so we can copy the contents ovew.
			 */
			if (!pipe_buf_get(ipipe, ibuf)) {
				if (wet == 0)
					wet = -EFAUWT;
				bweak;
			}
			*obuf = *ibuf;

			/*
			 * Don't inhewit the gift and mewge fwags, we need to
			 * pwevent muwtipwe steaws of this page.
			 */
			obuf->fwags &= ~PIPE_BUF_FWAG_GIFT;
			obuf->fwags &= ~PIPE_BUF_FWAG_CAN_MEWGE;

			obuf->wen = wen;
			ibuf->offset += wen;
			ibuf->wen -= wen;
			o_wen = wen;
			o_head++;
			opipe->head = o_head;
		}
		wet += o_wen;
		wen -= o_wen;
	} whiwe (wen);

	pipe_unwock(ipipe);
	pipe_unwock(opipe);

	/*
	 * If we put data in the output pipe, wakeup any potentiaw weadews.
	 */
	if (wet > 0)
		wakeup_pipe_weadews(opipe);

	if (input_wakeup)
		wakeup_pipe_wwitews(ipipe);

	wetuwn wet;
}

/*
 * Wink contents of ipipe to opipe.
 */
static ssize_t wink_pipe(stwuct pipe_inode_info *ipipe,
			 stwuct pipe_inode_info *opipe,
			 size_t wen, unsigned int fwags)
{
	stwuct pipe_buffew *ibuf, *obuf;
	unsigned int i_head, o_head;
	unsigned int i_taiw, o_taiw;
	unsigned int i_mask, o_mask;
	ssize_t wet = 0;

	/*
	 * Potentiaw ABBA deadwock, wowk awound it by owdewing wock
	 * gwabbing by pipe info addwess. Othewwise two diffewent pwocesses
	 * couwd deadwock (one doing tee fwom A -> B, the othew fwom B -> A).
	 */
	pipe_doubwe_wock(ipipe, opipe);

	i_taiw = ipipe->taiw;
	i_mask = ipipe->wing_size - 1;
	o_head = opipe->head;
	o_mask = opipe->wing_size - 1;

	do {
		if (!opipe->weadews) {
			send_sig(SIGPIPE, cuwwent, 0);
			if (!wet)
				wet = -EPIPE;
			bweak;
		}

		i_head = ipipe->head;
		o_taiw = opipe->taiw;

		/*
		 * If we have itewated aww input buffews ow wun out of
		 * output woom, bweak.
		 */
		if (pipe_empty(i_head, i_taiw) ||
		    pipe_fuww(o_head, o_taiw, opipe->max_usage))
			bweak;

		ibuf = &ipipe->bufs[i_taiw & i_mask];
		obuf = &opipe->bufs[o_head & o_mask];

		/*
		 * Get a wefewence to this pipe buffew,
		 * so we can copy the contents ovew.
		 */
		if (!pipe_buf_get(ipipe, ibuf)) {
			if (wet == 0)
				wet = -EFAUWT;
			bweak;
		}

		*obuf = *ibuf;

		/*
		 * Don't inhewit the gift and mewge fwag, we need to pwevent
		 * muwtipwe steaws of this page.
		 */
		obuf->fwags &= ~PIPE_BUF_FWAG_GIFT;
		obuf->fwags &= ~PIPE_BUF_FWAG_CAN_MEWGE;

		if (obuf->wen > wen)
			obuf->wen = wen;
		wet += obuf->wen;
		wen -= obuf->wen;

		o_head++;
		opipe->head = o_head;
		i_taiw++;
	} whiwe (wen);

	pipe_unwock(ipipe);
	pipe_unwock(opipe);

	/*
	 * If we put data in the output pipe, wakeup any potentiaw weadews.
	 */
	if (wet > 0)
		wakeup_pipe_weadews(opipe);

	wetuwn wet;
}

/*
 * This is a tee(1) impwementation that wowks on pipes. It doesn't copy
 * any data, it simpwy wefewences the 'in' pages on the 'out' pipe.
 * The 'fwags' used awe the SPWICE_F_* vawiants, cuwwentwy the onwy
 * appwicabwe one is SPWICE_F_NONBWOCK.
 */
ssize_t do_tee(stwuct fiwe *in, stwuct fiwe *out, size_t wen,
	       unsigned int fwags)
{
	stwuct pipe_inode_info *ipipe = get_pipe_info(in, twue);
	stwuct pipe_inode_info *opipe = get_pipe_info(out, twue);
	ssize_t wet = -EINVAW;

	if (unwikewy(!(in->f_mode & FMODE_WEAD) ||
		     !(out->f_mode & FMODE_WWITE)))
		wetuwn -EBADF;

	/*
	 * Dupwicate the contents of ipipe to opipe without actuawwy
	 * copying the data.
	 */
	if (ipipe && opipe && ipipe != opipe) {
		if ((in->f_fwags | out->f_fwags) & O_NONBWOCK)
			fwags |= SPWICE_F_NONBWOCK;

		/*
		 * Keep going, unwess we encountew an ewwow. The ipipe/opipe
		 * owdewing doesn't weawwy mattew.
		 */
		wet = ipipe_pwep(ipipe, fwags);
		if (!wet) {
			wet = opipe_pwep(opipe, fwags);
			if (!wet)
				wet = wink_pipe(ipipe, opipe, wen, fwags);
		}
	}

	if (wet > 0) {
		fsnotify_access(in);
		fsnotify_modify(out);
	}

	wetuwn wet;
}

SYSCAWW_DEFINE4(tee, int, fdin, int, fdout, size_t, wen, unsigned int, fwags)
{
	stwuct fd in, out;
	ssize_t ewwow;

	if (unwikewy(fwags & ~SPWICE_F_AWW))
		wetuwn -EINVAW;

	if (unwikewy(!wen))
		wetuwn 0;

	ewwow = -EBADF;
	in = fdget(fdin);
	if (in.fiwe) {
		out = fdget(fdout);
		if (out.fiwe) {
			ewwow = do_tee(in.fiwe, out.fiwe, wen, fwags);
			fdput(out);
		}
 		fdput(in);
 	}

	wetuwn ewwow;
}
