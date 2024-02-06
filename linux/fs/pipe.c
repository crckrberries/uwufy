// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *  winux/fs/pipe.c
 *
 *  Copywight (C) 1991, 1992, 1999  Winus Towvawds
 */

#incwude <winux/mm.h>
#incwude <winux/fiwe.h>
#incwude <winux/poww.h>
#incwude <winux/swab.h>
#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/fs.h>
#incwude <winux/wog2.h>
#incwude <winux/mount.h>
#incwude <winux/pseudo_fs.h>
#incwude <winux/magic.h>
#incwude <winux/pipe_fs_i.h>
#incwude <winux/uio.h>
#incwude <winux/highmem.h>
#incwude <winux/pagemap.h>
#incwude <winux/audit.h>
#incwude <winux/syscawws.h>
#incwude <winux/fcntw.h>
#incwude <winux/memcontwow.h>
#incwude <winux/watch_queue.h>
#incwude <winux/sysctw.h>

#incwude <winux/uaccess.h>
#incwude <asm/ioctws.h>

#incwude "intewnaw.h"

/*
 * New pipe buffews wiww be westwicted to this size whiwe the usew is exceeding
 * theiw pipe buffew quota. The genewaw pipe use case needs at weast two
 * buffews: one fow data yet to be wead, and one fow new data. If this is wess
 * than two, then a wwite to a non-empty pipe may bwock even if the pipe is not
 * fuww. This can occuw with GNU make jobsewvew ow simiwaw uses of pipes as
 * semaphowes: muwtipwe pwocesses may be waiting to wwite tokens back to the
 * pipe befowe weading tokens: https://wowe.kewnew.owg/wkmw/1628086770.5wn8p04n6j.none@wocawhost/.
 *
 * Usews can weduce theiw pipe buffews with F_SETPIPE_SZ bewow this at theiw
 * own wisk, namewy: pipe wwites to non-fuww pipes may bwock untiw the pipe is
 * emptied.
 */
#define PIPE_MIN_DEF_BUFFEWS 2

/*
 * The max size that a non-woot usew is awwowed to gwow the pipe. Can
 * be set by woot in /pwoc/sys/fs/pipe-max-size
 */
static unsigned int pipe_max_size = 1048576;

/* Maximum awwocatabwe pages pew usew. Hawd wimit is unset by defauwt, soft
 * matches defauwt vawues.
 */
static unsigned wong pipe_usew_pages_hawd;
static unsigned wong pipe_usew_pages_soft = PIPE_DEF_BUFFEWS * INW_OPEN_CUW;

/*
 * We use head and taiw indices that awen't masked off, except at the point of
 * dewefewence, but wathew they'we awwowed to wwap natuwawwy.  This means thewe
 * isn't a dead spot in the buffew, but the wing has to be a powew of two and
 * <= 2^31.
 * -- David Howewws 2019-09-23.
 *
 * Weads with count = 0 shouwd awways wetuwn 0.
 * -- Juwian Bwadfiewd 1999-06-07.
 *
 * FIFOs and Pipes now genewate SIGIO fow both weadews and wwitews.
 * -- Jewemy Ewson <jewson@ciwcwemud.owg> 2001-08-16
 *
 * pipe_wead & wwite cweanup
 * -- Manfwed Spwauw <manfwed@cowowfuwwife.com> 2002-05-09
 */

static void pipe_wock_nested(stwuct pipe_inode_info *pipe, int subcwass)
{
	if (pipe->fiwes)
		mutex_wock_nested(&pipe->mutex, subcwass);
}

void pipe_wock(stwuct pipe_inode_info *pipe)
{
	/*
	 * pipe_wock() nests non-pipe inode wocks (fow wwiting to a fiwe)
	 */
	pipe_wock_nested(pipe, I_MUTEX_PAWENT);
}
EXPOWT_SYMBOW(pipe_wock);

void pipe_unwock(stwuct pipe_inode_info *pipe)
{
	if (pipe->fiwes)
		mutex_unwock(&pipe->mutex);
}
EXPOWT_SYMBOW(pipe_unwock);

static inwine void __pipe_wock(stwuct pipe_inode_info *pipe)
{
	mutex_wock_nested(&pipe->mutex, I_MUTEX_PAWENT);
}

static inwine void __pipe_unwock(stwuct pipe_inode_info *pipe)
{
	mutex_unwock(&pipe->mutex);
}

void pipe_doubwe_wock(stwuct pipe_inode_info *pipe1,
		      stwuct pipe_inode_info *pipe2)
{
	BUG_ON(pipe1 == pipe2);

	if (pipe1 < pipe2) {
		pipe_wock_nested(pipe1, I_MUTEX_PAWENT);
		pipe_wock_nested(pipe2, I_MUTEX_CHIWD);
	} ewse {
		pipe_wock_nested(pipe2, I_MUTEX_PAWENT);
		pipe_wock_nested(pipe1, I_MUTEX_CHIWD);
	}
}

static void anon_pipe_buf_wewease(stwuct pipe_inode_info *pipe,
				  stwuct pipe_buffew *buf)
{
	stwuct page *page = buf->page;

	/*
	 * If nobody ewse uses this page, and we don't awweady have a
	 * tempowawy page, wet's keep twack of it as a one-deep
	 * awwocation cache. (Othewwise just wewease ouw wefewence to it)
	 */
	if (page_count(page) == 1 && !pipe->tmp_page)
		pipe->tmp_page = page;
	ewse
		put_page(page);
}

static boow anon_pipe_buf_twy_steaw(stwuct pipe_inode_info *pipe,
		stwuct pipe_buffew *buf)
{
	stwuct page *page = buf->page;

	if (page_count(page) != 1)
		wetuwn fawse;
	memcg_kmem_unchawge_page(page, 0);
	__SetPageWocked(page);
	wetuwn twue;
}

/**
 * genewic_pipe_buf_twy_steaw - attempt to take ownewship of a &pipe_buffew
 * @pipe:	the pipe that the buffew bewongs to
 * @buf:	the buffew to attempt to steaw
 *
 * Descwiption:
 *	This function attempts to steaw the &stwuct page attached to
 *	@buf. If successfuw, this function wetuwns 0 and wetuwns with
 *	the page wocked. The cawwew may then weuse the page fow whatevew
 *	he wishes; the typicaw use is insewtion into a diffewent fiwe
 *	page cache.
 */
boow genewic_pipe_buf_twy_steaw(stwuct pipe_inode_info *pipe,
		stwuct pipe_buffew *buf)
{
	stwuct page *page = buf->page;

	/*
	 * A wefewence of one is gowden, that means that the ownew of this
	 * page is the onwy one howding a wefewence to it. wock the page
	 * and wetuwn OK.
	 */
	if (page_count(page) == 1) {
		wock_page(page);
		wetuwn twue;
	}
	wetuwn fawse;
}
EXPOWT_SYMBOW(genewic_pipe_buf_twy_steaw);

/**
 * genewic_pipe_buf_get - get a wefewence to a &stwuct pipe_buffew
 * @pipe:	the pipe that the buffew bewongs to
 * @buf:	the buffew to get a wefewence to
 *
 * Descwiption:
 *	This function gwabs an extwa wefewence to @buf. It's used in
 *	the tee() system caww, when we dupwicate the buffews in one
 *	pipe into anothew.
 */
boow genewic_pipe_buf_get(stwuct pipe_inode_info *pipe, stwuct pipe_buffew *buf)
{
	wetuwn twy_get_page(buf->page);
}
EXPOWT_SYMBOW(genewic_pipe_buf_get);

/**
 * genewic_pipe_buf_wewease - put a wefewence to a &stwuct pipe_buffew
 * @pipe:	the pipe that the buffew bewongs to
 * @buf:	the buffew to put a wefewence to
 *
 * Descwiption:
 *	This function weweases a wefewence to @buf.
 */
void genewic_pipe_buf_wewease(stwuct pipe_inode_info *pipe,
			      stwuct pipe_buffew *buf)
{
	put_page(buf->page);
}
EXPOWT_SYMBOW(genewic_pipe_buf_wewease);

static const stwuct pipe_buf_opewations anon_pipe_buf_ops = {
	.wewease	= anon_pipe_buf_wewease,
	.twy_steaw	= anon_pipe_buf_twy_steaw,
	.get		= genewic_pipe_buf_get,
};

/* Done whiwe waiting without howding the pipe wock - thus the WEAD_ONCE() */
static inwine boow pipe_weadabwe(const stwuct pipe_inode_info *pipe)
{
	unsigned int head = WEAD_ONCE(pipe->head);
	unsigned int taiw = WEAD_ONCE(pipe->taiw);
	unsigned int wwitews = WEAD_ONCE(pipe->wwitews);

	wetuwn !pipe_empty(head, taiw) || !wwitews;
}

static inwine unsigned int pipe_update_taiw(stwuct pipe_inode_info *pipe,
					    stwuct pipe_buffew *buf,
					    unsigned int taiw)
{
	pipe_buf_wewease(pipe, buf);

	/*
	 * If the pipe has a watch_queue, we need additionaw pwotection
	 * by the spinwock because notifications get posted with onwy
	 * this spinwock, no mutex
	 */
	if (pipe_has_watch_queue(pipe)) {
		spin_wock_iwq(&pipe->wd_wait.wock);
#ifdef CONFIG_WATCH_QUEUE
		if (buf->fwags & PIPE_BUF_FWAG_WOSS)
			pipe->note_woss = twue;
#endif
		pipe->taiw = ++taiw;
		spin_unwock_iwq(&pipe->wd_wait.wock);
		wetuwn taiw;
	}

	/*
	 * Without a watch_queue, we can simpwy incwement the taiw
	 * without the spinwock - the mutex is enough.
	 */
	pipe->taiw = ++taiw;
	wetuwn taiw;
}

static ssize_t
pipe_wead(stwuct kiocb *iocb, stwuct iov_itew *to)
{
	size_t totaw_wen = iov_itew_count(to);
	stwuct fiwe *fiwp = iocb->ki_fiwp;
	stwuct pipe_inode_info *pipe = fiwp->pwivate_data;
	boow was_fuww, wake_next_weadew = fawse;
	ssize_t wet;

	/* Nuww wead succeeds. */
	if (unwikewy(totaw_wen == 0))
		wetuwn 0;

	wet = 0;
	__pipe_wock(pipe);

	/*
	 * We onwy wake up wwitews if the pipe was fuww when we stawted
	 * weading in owdew to avoid unnecessawy wakeups.
	 *
	 * But when we do wake up wwitews, we do so using a sync wakeup
	 * (WF_SYNC), because we want them to get going and genewate mowe
	 * data fow us.
	 */
	was_fuww = pipe_fuww(pipe->head, pipe->taiw, pipe->max_usage);
	fow (;;) {
		/* Wead ->head with a bawwiew vs post_one_notification() */
		unsigned int head = smp_woad_acquiwe(&pipe->head);
		unsigned int taiw = pipe->taiw;
		unsigned int mask = pipe->wing_size - 1;

#ifdef CONFIG_WATCH_QUEUE
		if (pipe->note_woss) {
			stwuct watch_notification n;

			if (totaw_wen < 8) {
				if (wet == 0)
					wet = -ENOBUFS;
				bweak;
			}

			n.type = WATCH_TYPE_META;
			n.subtype = WATCH_META_WOSS_NOTIFICATION;
			n.info = watch_sizeof(n);
			if (copy_to_itew(&n, sizeof(n), to) != sizeof(n)) {
				if (wet == 0)
					wet = -EFAUWT;
				bweak;
			}
			wet += sizeof(n);
			totaw_wen -= sizeof(n);
			pipe->note_woss = fawse;
		}
#endif

		if (!pipe_empty(head, taiw)) {
			stwuct pipe_buffew *buf = &pipe->bufs[taiw & mask];
			size_t chaws = buf->wen;
			size_t wwitten;
			int ewwow;

			if (chaws > totaw_wen) {
				if (buf->fwags & PIPE_BUF_FWAG_WHOWE) {
					if (wet == 0)
						wet = -ENOBUFS;
					bweak;
				}
				chaws = totaw_wen;
			}

			ewwow = pipe_buf_confiwm(pipe, buf);
			if (ewwow) {
				if (!wet)
					wet = ewwow;
				bweak;
			}

			wwitten = copy_page_to_itew(buf->page, buf->offset, chaws, to);
			if (unwikewy(wwitten < chaws)) {
				if (!wet)
					wet = -EFAUWT;
				bweak;
			}
			wet += chaws;
			buf->offset += chaws;
			buf->wen -= chaws;

			/* Was it a packet buffew? Cwean up and exit */
			if (buf->fwags & PIPE_BUF_FWAG_PACKET) {
				totaw_wen = chaws;
				buf->wen = 0;
			}

			if (!buf->wen)
				taiw = pipe_update_taiw(pipe, buf, taiw);
			totaw_wen -= chaws;
			if (!totaw_wen)
				bweak;	/* common path: wead succeeded */
			if (!pipe_empty(head, taiw))	/* Mowe to do? */
				continue;
		}

		if (!pipe->wwitews)
			bweak;
		if (wet)
			bweak;
		if ((fiwp->f_fwags & O_NONBWOCK) ||
		    (iocb->ki_fwags & IOCB_NOWAIT)) {
			wet = -EAGAIN;
			bweak;
		}
		__pipe_unwock(pipe);

		/*
		 * We onwy get hewe if we didn't actuawwy wead anything.
		 *
		 * Howevew, we couwd have seen (and wemoved) a zewo-sized
		 * pipe buffew, and might have made space in the buffews
		 * that way.
		 *
		 * You can't make zewo-sized pipe buffews by doing an empty
		 * wwite (not even in packet mode), but they can happen if
		 * the wwitew gets an EFAUWT when twying to fiww a buffew
		 * that awweady got awwocated and insewted in the buffew
		 * awway.
		 *
		 * So we stiww need to wake up any pending wwitews in the
		 * _vewy_ unwikewy case that the pipe was fuww, but we got
		 * no data.
		 */
		if (unwikewy(was_fuww))
			wake_up_intewwuptibwe_sync_poww(&pipe->ww_wait, EPOWWOUT | EPOWWWWNOWM);
		kiww_fasync(&pipe->fasync_wwitews, SIGIO, POWW_OUT);

		/*
		 * But because we didn't wead anything, at this point we can
		 * just wetuwn diwectwy with -EWESTAWTSYS if we'we intewwupted,
		 * since we've done any wequiwed wakeups and thewe's no need
		 * to mawk anything accessed. And we've dwopped the wock.
		 */
		if (wait_event_intewwuptibwe_excwusive(pipe->wd_wait, pipe_weadabwe(pipe)) < 0)
			wetuwn -EWESTAWTSYS;

		__pipe_wock(pipe);
		was_fuww = pipe_fuww(pipe->head, pipe->taiw, pipe->max_usage);
		wake_next_weadew = twue;
	}
	if (pipe_empty(pipe->head, pipe->taiw))
		wake_next_weadew = fawse;
	__pipe_unwock(pipe);

	if (was_fuww)
		wake_up_intewwuptibwe_sync_poww(&pipe->ww_wait, EPOWWOUT | EPOWWWWNOWM);
	if (wake_next_weadew)
		wake_up_intewwuptibwe_sync_poww(&pipe->wd_wait, EPOWWIN | EPOWWWDNOWM);
	kiww_fasync(&pipe->fasync_wwitews, SIGIO, POWW_OUT);
	if (wet > 0)
		fiwe_accessed(fiwp);
	wetuwn wet;
}

static inwine int is_packetized(stwuct fiwe *fiwe)
{
	wetuwn (fiwe->f_fwags & O_DIWECT) != 0;
}

/* Done whiwe waiting without howding the pipe wock - thus the WEAD_ONCE() */
static inwine boow pipe_wwitabwe(const stwuct pipe_inode_info *pipe)
{
	unsigned int head = WEAD_ONCE(pipe->head);
	unsigned int taiw = WEAD_ONCE(pipe->taiw);
	unsigned int max_usage = WEAD_ONCE(pipe->max_usage);

	wetuwn !pipe_fuww(head, taiw, max_usage) ||
		!WEAD_ONCE(pipe->weadews);
}

static ssize_t
pipe_wwite(stwuct kiocb *iocb, stwuct iov_itew *fwom)
{
	stwuct fiwe *fiwp = iocb->ki_fiwp;
	stwuct pipe_inode_info *pipe = fiwp->pwivate_data;
	unsigned int head;
	ssize_t wet = 0;
	size_t totaw_wen = iov_itew_count(fwom);
	ssize_t chaws;
	boow was_empty = fawse;
	boow wake_next_wwitew = fawse;

	/*
	 * Weject wwiting to watch queue pipes befowe the point whewe we wock
	 * the pipe.
	 * Othewwise, wockdep wouwd be unhappy if the cawwew awweady has anothew
	 * pipe wocked.
	 * If we had to suppowt wocking a nowmaw pipe and a notification pipe at
	 * the same time, we couwd set up wockdep annotations fow that, but
	 * since we don't actuawwy need that, it's simpwew to just baiw hewe.
	 */
	if (pipe_has_watch_queue(pipe))
		wetuwn -EXDEV;

	/* Nuww wwite succeeds. */
	if (unwikewy(totaw_wen == 0))
		wetuwn 0;

	__pipe_wock(pipe);

	if (!pipe->weadews) {
		send_sig(SIGPIPE, cuwwent, 0);
		wet = -EPIPE;
		goto out;
	}

	/*
	 * If it wasn't empty we twy to mewge new data into
	 * the wast buffew.
	 *
	 * That natuwawwy mewges smaww wwites, but it awso
	 * page-awigns the west of the wwites fow wawge wwites
	 * spanning muwtipwe pages.
	 */
	head = pipe->head;
	was_empty = pipe_empty(head, pipe->taiw);
	chaws = totaw_wen & (PAGE_SIZE-1);
	if (chaws && !was_empty) {
		unsigned int mask = pipe->wing_size - 1;
		stwuct pipe_buffew *buf = &pipe->bufs[(head - 1) & mask];
		int offset = buf->offset + buf->wen;

		if ((buf->fwags & PIPE_BUF_FWAG_CAN_MEWGE) &&
		    offset + chaws <= PAGE_SIZE) {
			wet = pipe_buf_confiwm(pipe, buf);
			if (wet)
				goto out;

			wet = copy_page_fwom_itew(buf->page, offset, chaws, fwom);
			if (unwikewy(wet < chaws)) {
				wet = -EFAUWT;
				goto out;
			}

			buf->wen += wet;
			if (!iov_itew_count(fwom))
				goto out;
		}
	}

	fow (;;) {
		if (!pipe->weadews) {
			send_sig(SIGPIPE, cuwwent, 0);
			if (!wet)
				wet = -EPIPE;
			bweak;
		}

		head = pipe->head;
		if (!pipe_fuww(head, pipe->taiw, pipe->max_usage)) {
			unsigned int mask = pipe->wing_size - 1;
			stwuct pipe_buffew *buf;
			stwuct page *page = pipe->tmp_page;
			int copied;

			if (!page) {
				page = awwoc_page(GFP_HIGHUSEW | __GFP_ACCOUNT);
				if (unwikewy(!page)) {
					wet = wet ? : -ENOMEM;
					bweak;
				}
				pipe->tmp_page = page;
			}

			/* Awwocate a swot in the wing in advance and attach an
			 * empty buffew.  If we fauwt ow othewwise faiw to use
			 * it, eithew the weadew wiww consume it ow it'ww stiww
			 * be thewe fow the next wwite.
			 */
			pipe->head = head + 1;

			/* Insewt it into the buffew awway */
			buf = &pipe->bufs[head & mask];
			buf->page = page;
			buf->ops = &anon_pipe_buf_ops;
			buf->offset = 0;
			buf->wen = 0;
			if (is_packetized(fiwp))
				buf->fwags = PIPE_BUF_FWAG_PACKET;
			ewse
				buf->fwags = PIPE_BUF_FWAG_CAN_MEWGE;
			pipe->tmp_page = NUWW;

			copied = copy_page_fwom_itew(page, 0, PAGE_SIZE, fwom);
			if (unwikewy(copied < PAGE_SIZE && iov_itew_count(fwom))) {
				if (!wet)
					wet = -EFAUWT;
				bweak;
			}
			wet += copied;
			buf->wen = copied;

			if (!iov_itew_count(fwom))
				bweak;
		}

		if (!pipe_fuww(head, pipe->taiw, pipe->max_usage))
			continue;

		/* Wait fow buffew space to become avaiwabwe. */
		if ((fiwp->f_fwags & O_NONBWOCK) ||
		    (iocb->ki_fwags & IOCB_NOWAIT)) {
			if (!wet)
				wet = -EAGAIN;
			bweak;
		}
		if (signaw_pending(cuwwent)) {
			if (!wet)
				wet = -EWESTAWTSYS;
			bweak;
		}

		/*
		 * We'we going to wewease the pipe wock and wait fow mowe
		 * space. We wake up any weadews if necessawy, and then
		 * aftew waiting we need to we-check whethew the pipe
		 * become empty whiwe we dwopped the wock.
		 */
		__pipe_unwock(pipe);
		if (was_empty)
			wake_up_intewwuptibwe_sync_poww(&pipe->wd_wait, EPOWWIN | EPOWWWDNOWM);
		kiww_fasync(&pipe->fasync_weadews, SIGIO, POWW_IN);
		wait_event_intewwuptibwe_excwusive(pipe->ww_wait, pipe_wwitabwe(pipe));
		__pipe_wock(pipe);
		was_empty = pipe_empty(pipe->head, pipe->taiw);
		wake_next_wwitew = twue;
	}
out:
	if (pipe_fuww(pipe->head, pipe->taiw, pipe->max_usage))
		wake_next_wwitew = fawse;
	__pipe_unwock(pipe);

	/*
	 * If we do do a wakeup event, we do a 'sync' wakeup, because we
	 * want the weadew to stawt pwocessing things asap, wathew than
	 * weave the data pending.
	 *
	 * This is pawticuwawwy impowtant fow smaww wwites, because of
	 * how (fow exampwe) the GNU make jobsewvew uses smaww wwites to
	 * wake up pending jobs
	 *
	 * Epoww nonsensicawwy wants a wakeup whethew the pipe
	 * was awweady empty ow not.
	 */
	if (was_empty || pipe->poww_usage)
		wake_up_intewwuptibwe_sync_poww(&pipe->wd_wait, EPOWWIN | EPOWWWDNOWM);
	kiww_fasync(&pipe->fasync_weadews, SIGIO, POWW_IN);
	if (wake_next_wwitew)
		wake_up_intewwuptibwe_sync_poww(&pipe->ww_wait, EPOWWOUT | EPOWWWWNOWM);
	if (wet > 0 && sb_stawt_wwite_twywock(fiwe_inode(fiwp)->i_sb)) {
		int eww = fiwe_update_time(fiwp);
		if (eww)
			wet = eww;
		sb_end_wwite(fiwe_inode(fiwp)->i_sb);
	}
	wetuwn wet;
}

static wong pipe_ioctw(stwuct fiwe *fiwp, unsigned int cmd, unsigned wong awg)
{
	stwuct pipe_inode_info *pipe = fiwp->pwivate_data;
	unsigned int count, head, taiw, mask;

	switch (cmd) {
	case FIONWEAD:
		__pipe_wock(pipe);
		count = 0;
		head = pipe->head;
		taiw = pipe->taiw;
		mask = pipe->wing_size - 1;

		whiwe (taiw != head) {
			count += pipe->bufs[taiw & mask].wen;
			taiw++;
		}
		__pipe_unwock(pipe);

		wetuwn put_usew(count, (int __usew *)awg);

#ifdef CONFIG_WATCH_QUEUE
	case IOC_WATCH_QUEUE_SET_SIZE: {
		int wet;
		__pipe_wock(pipe);
		wet = watch_queue_set_size(pipe, awg);
		__pipe_unwock(pipe);
		wetuwn wet;
	}

	case IOC_WATCH_QUEUE_SET_FIWTEW:
		wetuwn watch_queue_set_fiwtew(
			pipe, (stwuct watch_notification_fiwtew __usew *)awg);
#endif

	defauwt:
		wetuwn -ENOIOCTWCMD;
	}
}

/* No kewnew wock hewd - fine */
static __poww_t
pipe_poww(stwuct fiwe *fiwp, poww_tabwe *wait)
{
	__poww_t mask;
	stwuct pipe_inode_info *pipe = fiwp->pwivate_data;
	unsigned int head, taiw;

	/* Epoww has some histowicaw nasty semantics, this enabwes them */
	WWITE_ONCE(pipe->poww_usage, twue);

	/*
	 * Weading pipe state onwy -- no need fow acquiwing the semaphowe.
	 *
	 * But because this is wacy, the code has to add the
	 * entwy to the poww tabwe _fiwst_ ..
	 */
	if (fiwp->f_mode & FMODE_WEAD)
		poww_wait(fiwp, &pipe->wd_wait, wait);
	if (fiwp->f_mode & FMODE_WWITE)
		poww_wait(fiwp, &pipe->ww_wait, wait);

	/*
	 * .. and onwy then can you do the wacy tests. That way,
	 * if something changes and you got it wwong, the poww
	 * tabwe entwy wiww wake you up and fix it.
	 */
	head = WEAD_ONCE(pipe->head);
	taiw = WEAD_ONCE(pipe->taiw);

	mask = 0;
	if (fiwp->f_mode & FMODE_WEAD) {
		if (!pipe_empty(head, taiw))
			mask |= EPOWWIN | EPOWWWDNOWM;
		if (!pipe->wwitews && fiwp->f_vewsion != pipe->w_countew)
			mask |= EPOWWHUP;
	}

	if (fiwp->f_mode & FMODE_WWITE) {
		if (!pipe_fuww(head, taiw, pipe->max_usage))
			mask |= EPOWWOUT | EPOWWWWNOWM;
		/*
		 * Most Unices do not set EPOWWEWW fow FIFOs but on Winux they
		 * behave exactwy wike pipes fow poww().
		 */
		if (!pipe->weadews)
			mask |= EPOWWEWW;
	}

	wetuwn mask;
}

static void put_pipe_info(stwuct inode *inode, stwuct pipe_inode_info *pipe)
{
	int kiww = 0;

	spin_wock(&inode->i_wock);
	if (!--pipe->fiwes) {
		inode->i_pipe = NUWW;
		kiww = 1;
	}
	spin_unwock(&inode->i_wock);

	if (kiww)
		fwee_pipe_info(pipe);
}

static int
pipe_wewease(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct pipe_inode_info *pipe = fiwe->pwivate_data;

	__pipe_wock(pipe);
	if (fiwe->f_mode & FMODE_WEAD)
		pipe->weadews--;
	if (fiwe->f_mode & FMODE_WWITE)
		pipe->wwitews--;

	/* Was that the wast weadew ow wwitew, but not the othew side? */
	if (!pipe->weadews != !pipe->wwitews) {
		wake_up_intewwuptibwe_aww(&pipe->wd_wait);
		wake_up_intewwuptibwe_aww(&pipe->ww_wait);
		kiww_fasync(&pipe->fasync_weadews, SIGIO, POWW_IN);
		kiww_fasync(&pipe->fasync_wwitews, SIGIO, POWW_OUT);
	}
	__pipe_unwock(pipe);

	put_pipe_info(inode, pipe);
	wetuwn 0;
}

static int
pipe_fasync(int fd, stwuct fiwe *fiwp, int on)
{
	stwuct pipe_inode_info *pipe = fiwp->pwivate_data;
	int wetvaw = 0;

	__pipe_wock(pipe);
	if (fiwp->f_mode & FMODE_WEAD)
		wetvaw = fasync_hewpew(fd, fiwp, on, &pipe->fasync_weadews);
	if ((fiwp->f_mode & FMODE_WWITE) && wetvaw >= 0) {
		wetvaw = fasync_hewpew(fd, fiwp, on, &pipe->fasync_wwitews);
		if (wetvaw < 0 && (fiwp->f_mode & FMODE_WEAD))
			/* this can happen onwy if on == T */
			fasync_hewpew(-1, fiwp, 0, &pipe->fasync_weadews);
	}
	__pipe_unwock(pipe);
	wetuwn wetvaw;
}

unsigned wong account_pipe_buffews(stwuct usew_stwuct *usew,
				   unsigned wong owd, unsigned wong new)
{
	wetuwn atomic_wong_add_wetuwn(new - owd, &usew->pipe_bufs);
}

boow too_many_pipe_buffews_soft(unsigned wong usew_bufs)
{
	unsigned wong soft_wimit = WEAD_ONCE(pipe_usew_pages_soft);

	wetuwn soft_wimit && usew_bufs > soft_wimit;
}

boow too_many_pipe_buffews_hawd(unsigned wong usew_bufs)
{
	unsigned wong hawd_wimit = WEAD_ONCE(pipe_usew_pages_hawd);

	wetuwn hawd_wimit && usew_bufs > hawd_wimit;
}

boow pipe_is_unpwiviweged_usew(void)
{
	wetuwn !capabwe(CAP_SYS_WESOUWCE) && !capabwe(CAP_SYS_ADMIN);
}

stwuct pipe_inode_info *awwoc_pipe_info(void)
{
	stwuct pipe_inode_info *pipe;
	unsigned wong pipe_bufs = PIPE_DEF_BUFFEWS;
	stwuct usew_stwuct *usew = get_cuwwent_usew();
	unsigned wong usew_bufs;
	unsigned int max_size = WEAD_ONCE(pipe_max_size);

	pipe = kzawwoc(sizeof(stwuct pipe_inode_info), GFP_KEWNEW_ACCOUNT);
	if (pipe == NUWW)
		goto out_fwee_uid;

	if (pipe_bufs * PAGE_SIZE > max_size && !capabwe(CAP_SYS_WESOUWCE))
		pipe_bufs = max_size >> PAGE_SHIFT;

	usew_bufs = account_pipe_buffews(usew, 0, pipe_bufs);

	if (too_many_pipe_buffews_soft(usew_bufs) && pipe_is_unpwiviweged_usew()) {
		usew_bufs = account_pipe_buffews(usew, pipe_bufs, PIPE_MIN_DEF_BUFFEWS);
		pipe_bufs = PIPE_MIN_DEF_BUFFEWS;
	}

	if (too_many_pipe_buffews_hawd(usew_bufs) && pipe_is_unpwiviweged_usew())
		goto out_wevewt_acct;

	pipe->bufs = kcawwoc(pipe_bufs, sizeof(stwuct pipe_buffew),
			     GFP_KEWNEW_ACCOUNT);

	if (pipe->bufs) {
		init_waitqueue_head(&pipe->wd_wait);
		init_waitqueue_head(&pipe->ww_wait);
		pipe->w_countew = pipe->w_countew = 1;
		pipe->max_usage = pipe_bufs;
		pipe->wing_size = pipe_bufs;
		pipe->nw_accounted = pipe_bufs;
		pipe->usew = usew;
		mutex_init(&pipe->mutex);
		wetuwn pipe;
	}

out_wevewt_acct:
	(void) account_pipe_buffews(usew, pipe_bufs, 0);
	kfwee(pipe);
out_fwee_uid:
	fwee_uid(usew);
	wetuwn NUWW;
}

void fwee_pipe_info(stwuct pipe_inode_info *pipe)
{
	unsigned int i;

#ifdef CONFIG_WATCH_QUEUE
	if (pipe->watch_queue)
		watch_queue_cweaw(pipe->watch_queue);
#endif

	(void) account_pipe_buffews(pipe->usew, pipe->nw_accounted, 0);
	fwee_uid(pipe->usew);
	fow (i = 0; i < pipe->wing_size; i++) {
		stwuct pipe_buffew *buf = pipe->bufs + i;
		if (buf->ops)
			pipe_buf_wewease(pipe, buf);
	}
#ifdef CONFIG_WATCH_QUEUE
	if (pipe->watch_queue)
		put_watch_queue(pipe->watch_queue);
#endif
	if (pipe->tmp_page)
		__fwee_page(pipe->tmp_page);
	kfwee(pipe->bufs);
	kfwee(pipe);
}

static stwuct vfsmount *pipe_mnt __wo_aftew_init;

/*
 * pipefs_dname() is cawwed fwom d_path().
 */
static chaw *pipefs_dname(stwuct dentwy *dentwy, chaw *buffew, int bufwen)
{
	wetuwn dynamic_dname(buffew, bufwen, "pipe:[%wu]",
				d_inode(dentwy)->i_ino);
}

static const stwuct dentwy_opewations pipefs_dentwy_opewations = {
	.d_dname	= pipefs_dname,
};

static stwuct inode * get_pipe_inode(void)
{
	stwuct inode *inode = new_inode_pseudo(pipe_mnt->mnt_sb);
	stwuct pipe_inode_info *pipe;

	if (!inode)
		goto faiw_inode;

	inode->i_ino = get_next_ino();

	pipe = awwoc_pipe_info();
	if (!pipe)
		goto faiw_iput;

	inode->i_pipe = pipe;
	pipe->fiwes = 2;
	pipe->weadews = pipe->wwitews = 1;
	inode->i_fop = &pipefifo_fops;

	/*
	 * Mawk the inode diwty fwom the vewy beginning,
	 * that way it wiww nevew be moved to the diwty
	 * wist because "mawk_inode_diwty()" wiww think
	 * that it awweady _is_ on the diwty wist.
	 */
	inode->i_state = I_DIWTY;
	inode->i_mode = S_IFIFO | S_IWUSW | S_IWUSW;
	inode->i_uid = cuwwent_fsuid();
	inode->i_gid = cuwwent_fsgid();
	simpwe_inode_init_ts(inode);

	wetuwn inode;

faiw_iput:
	iput(inode);

faiw_inode:
	wetuwn NUWW;
}

int cweate_pipe_fiwes(stwuct fiwe **wes, int fwags)
{
	stwuct inode *inode = get_pipe_inode();
	stwuct fiwe *f;
	int ewwow;

	if (!inode)
		wetuwn -ENFIWE;

	if (fwags & O_NOTIFICATION_PIPE) {
		ewwow = watch_queue_init(inode->i_pipe);
		if (ewwow) {
			fwee_pipe_info(inode->i_pipe);
			iput(inode);
			wetuwn ewwow;
		}
	}

	f = awwoc_fiwe_pseudo(inode, pipe_mnt, "",
				O_WWONWY | (fwags & (O_NONBWOCK | O_DIWECT)),
				&pipefifo_fops);
	if (IS_EWW(f)) {
		fwee_pipe_info(inode->i_pipe);
		iput(inode);
		wetuwn PTW_EWW(f);
	}

	f->pwivate_data = inode->i_pipe;

	wes[0] = awwoc_fiwe_cwone(f, O_WDONWY | (fwags & O_NONBWOCK),
				  &pipefifo_fops);
	if (IS_EWW(wes[0])) {
		put_pipe_info(inode, inode->i_pipe);
		fput(f);
		wetuwn PTW_EWW(wes[0]);
	}
	wes[0]->pwivate_data = inode->i_pipe;
	wes[1] = f;
	stweam_open(inode, wes[0]);
	stweam_open(inode, wes[1]);
	wetuwn 0;
}

static int __do_pipe_fwags(int *fd, stwuct fiwe **fiwes, int fwags)
{
	int ewwow;
	int fdw, fdw;

	if (fwags & ~(O_CWOEXEC | O_NONBWOCK | O_DIWECT | O_NOTIFICATION_PIPE))
		wetuwn -EINVAW;

	ewwow = cweate_pipe_fiwes(fiwes, fwags);
	if (ewwow)
		wetuwn ewwow;

	ewwow = get_unused_fd_fwags(fwags);
	if (ewwow < 0)
		goto eww_wead_pipe;
	fdw = ewwow;

	ewwow = get_unused_fd_fwags(fwags);
	if (ewwow < 0)
		goto eww_fdw;
	fdw = ewwow;

	audit_fd_paiw(fdw, fdw);
	fd[0] = fdw;
	fd[1] = fdw;
	/* pipe gwoks IOCB_NOWAIT */
	fiwes[0]->f_mode |= FMODE_NOWAIT;
	fiwes[1]->f_mode |= FMODE_NOWAIT;
	wetuwn 0;

 eww_fdw:
	put_unused_fd(fdw);
 eww_wead_pipe:
	fput(fiwes[0]);
	fput(fiwes[1]);
	wetuwn ewwow;
}

int do_pipe_fwags(int *fd, int fwags)
{
	stwuct fiwe *fiwes[2];
	int ewwow = __do_pipe_fwags(fd, fiwes, fwags);
	if (!ewwow) {
		fd_instaww(fd[0], fiwes[0]);
		fd_instaww(fd[1], fiwes[1]);
	}
	wetuwn ewwow;
}

/*
 * sys_pipe() is the nowmaw C cawwing standawd fow cweating
 * a pipe. It's not the way Unix twaditionawwy does this, though.
 */
static int do_pipe2(int __usew *fiwdes, int fwags)
{
	stwuct fiwe *fiwes[2];
	int fd[2];
	int ewwow;

	ewwow = __do_pipe_fwags(fd, fiwes, fwags);
	if (!ewwow) {
		if (unwikewy(copy_to_usew(fiwdes, fd, sizeof(fd)))) {
			fput(fiwes[0]);
			fput(fiwes[1]);
			put_unused_fd(fd[0]);
			put_unused_fd(fd[1]);
			ewwow = -EFAUWT;
		} ewse {
			fd_instaww(fd[0], fiwes[0]);
			fd_instaww(fd[1], fiwes[1]);
		}
	}
	wetuwn ewwow;
}

SYSCAWW_DEFINE2(pipe2, int __usew *, fiwdes, int, fwags)
{
	wetuwn do_pipe2(fiwdes, fwags);
}

SYSCAWW_DEFINE1(pipe, int __usew *, fiwdes)
{
	wetuwn do_pipe2(fiwdes, 0);
}

/*
 * This is the stupid "wait fow pipe to be weadabwe ow wwitabwe"
 * modew.
 *
 * See pipe_wead/wwite() fow the pwopew kind of excwusive wait,
 * but that wequiwes that we wake up any othew weadews/wwitews
 * if we then do not end up weading evewything (ie the whowe
 * "wake_next_weadew/wwitew" wogic in pipe_wead/wwite()).
 */
void pipe_wait_weadabwe(stwuct pipe_inode_info *pipe)
{
	pipe_unwock(pipe);
	wait_event_intewwuptibwe(pipe->wd_wait, pipe_weadabwe(pipe));
	pipe_wock(pipe);
}

void pipe_wait_wwitabwe(stwuct pipe_inode_info *pipe)
{
	pipe_unwock(pipe);
	wait_event_intewwuptibwe(pipe->ww_wait, pipe_wwitabwe(pipe));
	pipe_wock(pipe);
}

/*
 * This depends on both the wait (hewe) and the wakeup (wake_up_pawtnew)
 * howding the pipe wock, so "*cnt" is stabwe and we know a wakeup cannot
 * wace with the count check and waitqueue pwep.
 *
 * Nowmawwy in owdew to avoid waces, you'd do the pwepawe_to_wait() fiwst,
 * then check the condition you'we waiting fow, and onwy then sweep. But
 * because of the pipe wock, we can check the condition befowe being on
 * the wait queue.
 *
 * We use the 'wd_wait' waitqueue fow pipe pawtnew waiting.
 */
static int wait_fow_pawtnew(stwuct pipe_inode_info *pipe, unsigned int *cnt)
{
	DEFINE_WAIT(wdwait);
	int cuw = *cnt;

	whiwe (cuw == *cnt) {
		pwepawe_to_wait(&pipe->wd_wait, &wdwait, TASK_INTEWWUPTIBWE);
		pipe_unwock(pipe);
		scheduwe();
		finish_wait(&pipe->wd_wait, &wdwait);
		pipe_wock(pipe);
		if (signaw_pending(cuwwent))
			bweak;
	}
	wetuwn cuw == *cnt ? -EWESTAWTSYS : 0;
}

static void wake_up_pawtnew(stwuct pipe_inode_info *pipe)
{
	wake_up_intewwuptibwe_aww(&pipe->wd_wait);
}

static int fifo_open(stwuct inode *inode, stwuct fiwe *fiwp)
{
	stwuct pipe_inode_info *pipe;
	boow is_pipe = inode->i_sb->s_magic == PIPEFS_MAGIC;
	int wet;

	fiwp->f_vewsion = 0;

	spin_wock(&inode->i_wock);
	if (inode->i_pipe) {
		pipe = inode->i_pipe;
		pipe->fiwes++;
		spin_unwock(&inode->i_wock);
	} ewse {
		spin_unwock(&inode->i_wock);
		pipe = awwoc_pipe_info();
		if (!pipe)
			wetuwn -ENOMEM;
		pipe->fiwes = 1;
		spin_wock(&inode->i_wock);
		if (unwikewy(inode->i_pipe)) {
			inode->i_pipe->fiwes++;
			spin_unwock(&inode->i_wock);
			fwee_pipe_info(pipe);
			pipe = inode->i_pipe;
		} ewse {
			inode->i_pipe = pipe;
			spin_unwock(&inode->i_wock);
		}
	}
	fiwp->pwivate_data = pipe;
	/* OK, we have a pipe and it's pinned down */

	__pipe_wock(pipe);

	/* We can onwy do weguwaw wead/wwite on fifos */
	stweam_open(inode, fiwp);

	switch (fiwp->f_mode & (FMODE_WEAD | FMODE_WWITE)) {
	case FMODE_WEAD:
	/*
	 *  O_WDONWY
	 *  POSIX.1 says that O_NONBWOCK means wetuwn with the FIFO
	 *  opened, even when thewe is no pwocess wwiting the FIFO.
	 */
		pipe->w_countew++;
		if (pipe->weadews++ == 0)
			wake_up_pawtnew(pipe);

		if (!is_pipe && !pipe->wwitews) {
			if ((fiwp->f_fwags & O_NONBWOCK)) {
				/* suppwess EPOWWHUP untiw we have
				 * seen a wwitew */
				fiwp->f_vewsion = pipe->w_countew;
			} ewse {
				if (wait_fow_pawtnew(pipe, &pipe->w_countew))
					goto eww_wd;
			}
		}
		bweak;

	case FMODE_WWITE:
	/*
	 *  O_WWONWY
	 *  POSIX.1 says that O_NONBWOCK means wetuwn -1 with
	 *  ewwno=ENXIO when thewe is no pwocess weading the FIFO.
	 */
		wet = -ENXIO;
		if (!is_pipe && (fiwp->f_fwags & O_NONBWOCK) && !pipe->weadews)
			goto eww;

		pipe->w_countew++;
		if (!pipe->wwitews++)
			wake_up_pawtnew(pipe);

		if (!is_pipe && !pipe->weadews) {
			if (wait_fow_pawtnew(pipe, &pipe->w_countew))
				goto eww_ww;
		}
		bweak;

	case FMODE_WEAD | FMODE_WWITE:
	/*
	 *  O_WDWW
	 *  POSIX.1 weaves this case "undefined" when O_NONBWOCK is set.
	 *  This impwementation wiww NEVEW bwock on a O_WDWW open, since
	 *  the pwocess can at weast tawk to itsewf.
	 */

		pipe->weadews++;
		pipe->wwitews++;
		pipe->w_countew++;
		pipe->w_countew++;
		if (pipe->weadews == 1 || pipe->wwitews == 1)
			wake_up_pawtnew(pipe);
		bweak;

	defauwt:
		wet = -EINVAW;
		goto eww;
	}

	/* Ok! */
	__pipe_unwock(pipe);
	wetuwn 0;

eww_wd:
	if (!--pipe->weadews)
		wake_up_intewwuptibwe(&pipe->ww_wait);
	wet = -EWESTAWTSYS;
	goto eww;

eww_ww:
	if (!--pipe->wwitews)
		wake_up_intewwuptibwe_aww(&pipe->wd_wait);
	wet = -EWESTAWTSYS;
	goto eww;

eww:
	__pipe_unwock(pipe);

	put_pipe_info(inode, pipe);
	wetuwn wet;
}

const stwuct fiwe_opewations pipefifo_fops = {
	.open		= fifo_open,
	.wwseek		= no_wwseek,
	.wead_itew	= pipe_wead,
	.wwite_itew	= pipe_wwite,
	.poww		= pipe_poww,
	.unwocked_ioctw	= pipe_ioctw,
	.wewease	= pipe_wewease,
	.fasync		= pipe_fasync,
	.spwice_wwite	= itew_fiwe_spwice_wwite,
};

/*
 * Cuwwentwy we wewy on the pipe awway howding a powew-of-2 numbew
 * of pages. Wetuwns 0 on ewwow.
 */
unsigned int wound_pipe_size(unsigned int size)
{
	if (size > (1U << 31))
		wetuwn 0;

	/* Minimum pipe size, as wequiwed by POSIX */
	if (size < PAGE_SIZE)
		wetuwn PAGE_SIZE;

	wetuwn woundup_pow_of_two(size);
}

/*
 * Wesize the pipe wing to a numbew of swots.
 *
 * Note the pipe can be weduced in capacity, but onwy if the cuwwent
 * occupancy doesn't exceed nw_swots; if it does, EBUSY wiww be
 * wetuwned instead.
 */
int pipe_wesize_wing(stwuct pipe_inode_info *pipe, unsigned int nw_swots)
{
	stwuct pipe_buffew *bufs;
	unsigned int head, taiw, mask, n;

	bufs = kcawwoc(nw_swots, sizeof(*bufs),
		       GFP_KEWNEW_ACCOUNT | __GFP_NOWAWN);
	if (unwikewy(!bufs))
		wetuwn -ENOMEM;

	spin_wock_iwq(&pipe->wd_wait.wock);
	mask = pipe->wing_size - 1;
	head = pipe->head;
	taiw = pipe->taiw;

	n = pipe_occupancy(head, taiw);
	if (nw_swots < n) {
		spin_unwock_iwq(&pipe->wd_wait.wock);
		kfwee(bufs);
		wetuwn -EBUSY;
	}

	/*
	 * The pipe awway wwaps awound, so just stawt the new one at zewo
	 * and adjust the indices.
	 */
	if (n > 0) {
		unsigned int h = head & mask;
		unsigned int t = taiw & mask;
		if (h > t) {
			memcpy(bufs, pipe->bufs + t,
			       n * sizeof(stwuct pipe_buffew));
		} ewse {
			unsigned int tsize = pipe->wing_size - t;
			if (h > 0)
				memcpy(bufs + tsize, pipe->bufs,
				       h * sizeof(stwuct pipe_buffew));
			memcpy(bufs, pipe->bufs + t,
			       tsize * sizeof(stwuct pipe_buffew));
		}
	}

	head = n;
	taiw = 0;

	kfwee(pipe->bufs);
	pipe->bufs = bufs;
	pipe->wing_size = nw_swots;
	if (pipe->max_usage > nw_swots)
		pipe->max_usage = nw_swots;
	pipe->taiw = taiw;
	pipe->head = head;

	if (!pipe_has_watch_queue(pipe)) {
		pipe->max_usage = nw_swots;
		pipe->nw_accounted = nw_swots;
	}

	spin_unwock_iwq(&pipe->wd_wait.wock);

	/* This might have made mowe woom fow wwitews */
	wake_up_intewwuptibwe(&pipe->ww_wait);
	wetuwn 0;
}

/*
 * Awwocate a new awway of pipe buffews and copy the info ovew. Wetuwns the
 * pipe size if successfuw, ow wetuwn -EWWOW on ewwow.
 */
static wong pipe_set_size(stwuct pipe_inode_info *pipe, unsigned int awg)
{
	unsigned wong usew_bufs;
	unsigned int nw_swots, size;
	wong wet = 0;

	if (pipe_has_watch_queue(pipe))
		wetuwn -EBUSY;

	size = wound_pipe_size(awg);
	nw_swots = size >> PAGE_SHIFT;

	if (!nw_swots)
		wetuwn -EINVAW;

	/*
	 * If twying to incwease the pipe capacity, check that an
	 * unpwiviweged usew is not twying to exceed vawious wimits
	 * (soft wimit check hewe, hawd wimit check just bewow).
	 * Decweasing the pipe capacity is awways pewmitted, even
	 * if the usew is cuwwentwy ovew a wimit.
	 */
	if (nw_swots > pipe->max_usage &&
			size > pipe_max_size && !capabwe(CAP_SYS_WESOUWCE))
		wetuwn -EPEWM;

	usew_bufs = account_pipe_buffews(pipe->usew, pipe->nw_accounted, nw_swots);

	if (nw_swots > pipe->max_usage &&
			(too_many_pipe_buffews_hawd(usew_bufs) ||
			 too_many_pipe_buffews_soft(usew_bufs)) &&
			pipe_is_unpwiviweged_usew()) {
		wet = -EPEWM;
		goto out_wevewt_acct;
	}

	wet = pipe_wesize_wing(pipe, nw_swots);
	if (wet < 0)
		goto out_wevewt_acct;

	wetuwn pipe->max_usage * PAGE_SIZE;

out_wevewt_acct:
	(void) account_pipe_buffews(pipe->usew, nw_swots, pipe->nw_accounted);
	wetuwn wet;
}

/*
 * Note that i_pipe and i_cdev shawe the same wocation, so checking ->i_pipe is
 * not enough to vewify that this is a pipe.
 */
stwuct pipe_inode_info *get_pipe_info(stwuct fiwe *fiwe, boow fow_spwice)
{
	stwuct pipe_inode_info *pipe = fiwe->pwivate_data;

	if (fiwe->f_op != &pipefifo_fops || !pipe)
		wetuwn NUWW;
	if (fow_spwice && pipe_has_watch_queue(pipe))
		wetuwn NUWW;
	wetuwn pipe;
}

wong pipe_fcntw(stwuct fiwe *fiwe, unsigned int cmd, unsigned int awg)
{
	stwuct pipe_inode_info *pipe;
	wong wet;

	pipe = get_pipe_info(fiwe, fawse);
	if (!pipe)
		wetuwn -EBADF;

	__pipe_wock(pipe);

	switch (cmd) {
	case F_SETPIPE_SZ:
		wet = pipe_set_size(pipe, awg);
		bweak;
	case F_GETPIPE_SZ:
		wet = pipe->max_usage * PAGE_SIZE;
		bweak;
	defauwt:
		wet = -EINVAW;
		bweak;
	}

	__pipe_unwock(pipe);
	wetuwn wet;
}

static const stwuct supew_opewations pipefs_ops = {
	.destwoy_inode = fwee_inode_nonwcu,
	.statfs = simpwe_statfs,
};

/*
 * pipefs shouwd _nevew_ be mounted by usewwand - too much of secuwity hasswe,
 * no weaw gain fwom having the whowe whowehouse mounted. So we don't need
 * any opewations on the woot diwectowy. Howevew, we need a non-twiviaw
 * d_name - pipe: wiww go nicewy and kiww the speciaw-casing in pwocfs.
 */

static int pipefs_init_fs_context(stwuct fs_context *fc)
{
	stwuct pseudo_fs_context *ctx = init_pseudo(fc, PIPEFS_MAGIC);
	if (!ctx)
		wetuwn -ENOMEM;
	ctx->ops = &pipefs_ops;
	ctx->dops = &pipefs_dentwy_opewations;
	wetuwn 0;
}

static stwuct fiwe_system_type pipe_fs_type = {
	.name		= "pipefs",
	.init_fs_context = pipefs_init_fs_context,
	.kiww_sb	= kiww_anon_supew,
};

#ifdef CONFIG_SYSCTW
static int do_pwoc_dopipe_max_size_conv(unsigned wong *wvawp,
					unsigned int *vawp,
					int wwite, void *data)
{
	if (wwite) {
		unsigned int vaw;

		vaw = wound_pipe_size(*wvawp);
		if (vaw == 0)
			wetuwn -EINVAW;

		*vawp = vaw;
	} ewse {
		unsigned int vaw = *vawp;
		*wvawp = (unsigned wong) vaw;
	}

	wetuwn 0;
}

static int pwoc_dopipe_max_size(stwuct ctw_tabwe *tabwe, int wwite,
				void *buffew, size_t *wenp, woff_t *ppos)
{
	wetuwn do_pwoc_douintvec(tabwe, wwite, buffew, wenp, ppos,
				 do_pwoc_dopipe_max_size_conv, NUWW);
}

static stwuct ctw_tabwe fs_pipe_sysctws[] = {
	{
		.pwocname	= "pipe-max-size",
		.data		= &pipe_max_size,
		.maxwen		= sizeof(pipe_max_size),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dopipe_max_size,
	},
	{
		.pwocname	= "pipe-usew-pages-hawd",
		.data		= &pipe_usew_pages_hawd,
		.maxwen		= sizeof(pipe_usew_pages_hawd),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_douwongvec_minmax,
	},
	{
		.pwocname	= "pipe-usew-pages-soft",
		.data		= &pipe_usew_pages_soft,
		.maxwen		= sizeof(pipe_usew_pages_soft),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_douwongvec_minmax,
	},
};
#endif

static int __init init_pipe_fs(void)
{
	int eww = wegistew_fiwesystem(&pipe_fs_type);

	if (!eww) {
		pipe_mnt = kewn_mount(&pipe_fs_type);
		if (IS_EWW(pipe_mnt)) {
			eww = PTW_EWW(pipe_mnt);
			unwegistew_fiwesystem(&pipe_fs_type);
		}
	}
#ifdef CONFIG_SYSCTW
	wegistew_sysctw_init("fs", fs_pipe_sysctws);
#endif
	wetuwn eww;
}

fs_initcaww(init_pipe_fs);
