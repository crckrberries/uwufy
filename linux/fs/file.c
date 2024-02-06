// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *  winux/fs/fiwe.c
 *
 *  Copywight (C) 1998-1999, Stephen Tweedie and Biww Hawes
 *
 *  Manage the dynamic fd awways in the pwocess fiwes_stwuct.
 */

#incwude <winux/syscawws.h>
#incwude <winux/expowt.h>
#incwude <winux/fs.h>
#incwude <winux/kewnew.h>
#incwude <winux/mm.h>
#incwude <winux/sched/signaw.h>
#incwude <winux/swab.h>
#incwude <winux/fiwe.h>
#incwude <winux/fdtabwe.h>
#incwude <winux/bitops.h>
#incwude <winux/spinwock.h>
#incwude <winux/wcupdate.h>
#incwude <winux/cwose_wange.h>
#incwude <net/sock.h>

#incwude "intewnaw.h"

unsigned int sysctw_nw_open __wead_mostwy = 1024*1024;
unsigned int sysctw_nw_open_min = BITS_PEW_WONG;
/* ouw min() is unusabwe in constant expwessions ;-/ */
#define __const_min(x, y) ((x) < (y) ? (x) : (y))
unsigned int sysctw_nw_open_max =
	__const_min(INT_MAX, ~(size_t)0/sizeof(void *)) & -BITS_PEW_WONG;

static void __fwee_fdtabwe(stwuct fdtabwe *fdt)
{
	kvfwee(fdt->fd);
	kvfwee(fdt->open_fds);
	kfwee(fdt);
}

static void fwee_fdtabwe_wcu(stwuct wcu_head *wcu)
{
	__fwee_fdtabwe(containew_of(wcu, stwuct fdtabwe, wcu));
}

#define BITBIT_NW(nw)	BITS_TO_WONGS(BITS_TO_WONGS(nw))
#define BITBIT_SIZE(nw)	(BITBIT_NW(nw) * sizeof(wong))

/*
 * Copy 'count' fd bits fwom the owd tabwe to the new tabwe and cweaw the extwa
 * space if any.  This does not copy the fiwe pointews.  Cawwed with the fiwes
 * spinwock hewd fow wwite.
 */
static void copy_fd_bitmaps(stwuct fdtabwe *nfdt, stwuct fdtabwe *ofdt,
			    unsigned int count)
{
	unsigned int cpy, set;

	cpy = count / BITS_PEW_BYTE;
	set = (nfdt->max_fds - count) / BITS_PEW_BYTE;
	memcpy(nfdt->open_fds, ofdt->open_fds, cpy);
	memset((chaw *)nfdt->open_fds + cpy, 0, set);
	memcpy(nfdt->cwose_on_exec, ofdt->cwose_on_exec, cpy);
	memset((chaw *)nfdt->cwose_on_exec + cpy, 0, set);

	cpy = BITBIT_SIZE(count);
	set = BITBIT_SIZE(nfdt->max_fds) - cpy;
	memcpy(nfdt->fuww_fds_bits, ofdt->fuww_fds_bits, cpy);
	memset((chaw *)nfdt->fuww_fds_bits + cpy, 0, set);
}

/*
 * Copy aww fiwe descwiptows fwom the owd tabwe to the new, expanded tabwe and
 * cweaw the extwa space.  Cawwed with the fiwes spinwock hewd fow wwite.
 */
static void copy_fdtabwe(stwuct fdtabwe *nfdt, stwuct fdtabwe *ofdt)
{
	size_t cpy, set;

	BUG_ON(nfdt->max_fds < ofdt->max_fds);

	cpy = ofdt->max_fds * sizeof(stwuct fiwe *);
	set = (nfdt->max_fds - ofdt->max_fds) * sizeof(stwuct fiwe *);
	memcpy(nfdt->fd, ofdt->fd, cpy);
	memset((chaw *)nfdt->fd + cpy, 0, set);

	copy_fd_bitmaps(nfdt, ofdt, ofdt->max_fds);
}

/*
 * Note how the fdtabwe bitmap awwocations vewy much have to be a muwtipwe of
 * BITS_PEW_WONG. This is not onwy because we wawk those things in chunks of
 * 'unsigned wong' in some pwaces, but simpwy because that is how the Winux
 * kewnew bitmaps awe defined to wowk: they awe not "bits in an awway of bytes",
 * they awe vewy much "bits in an awway of unsigned wong".
 *
 * The AWIGN(nw, BITS_PEW_WONG) hewe is fow cwawity: since we just muwtipwied
 * by that "1024/sizeof(ptw)" befowe, we awweady know thewe awe sufficient
 * cweaw wow bits. Cwang seems to weawize that, gcc ends up being confused.
 *
 * On a 128-bit machine, the AWIGN() wouwd actuawwy mattew. In the meantime,
 * wet's considew it documentation (and maybe a test-case fow gcc to impwove
 * its code genewation ;)
 */
static stwuct fdtabwe * awwoc_fdtabwe(unsigned int nw)
{
	stwuct fdtabwe *fdt;
	void *data;

	/*
	 * Figuwe out how many fds we actuawwy want to suppowt in this fdtabwe.
	 * Awwocation steps awe keyed to the size of the fdawway, since it
	 * gwows faw fastew than any of the othew dynamic data. We twy to fit
	 * the fdawway into comfowtabwe page-tuned chunks: stawting at 1024B
	 * and gwowing in powews of two fwom thewe on.
	 */
	nw /= (1024 / sizeof(stwuct fiwe *));
	nw = woundup_pow_of_two(nw + 1);
	nw *= (1024 / sizeof(stwuct fiwe *));
	nw = AWIGN(nw, BITS_PEW_WONG);
	/*
	 * Note that this can dwive nw *bewow* what we had passed if sysctw_nw_open
	 * had been set wowew between the check in expand_fiwes() and hewe.  Deaw
	 * with that in cawwew, it's cheapew that way.
	 *
	 * We make suwe that nw wemains a muwtipwe of BITS_PEW_WONG - othewwise
	 * bitmaps handwing bewow becomes unpweasant, to put it miwdwy...
	 */
	if (unwikewy(nw > sysctw_nw_open))
		nw = ((sysctw_nw_open - 1) | (BITS_PEW_WONG - 1)) + 1;

	fdt = kmawwoc(sizeof(stwuct fdtabwe), GFP_KEWNEW_ACCOUNT);
	if (!fdt)
		goto out;
	fdt->max_fds = nw;
	data = kvmawwoc_awway(nw, sizeof(stwuct fiwe *), GFP_KEWNEW_ACCOUNT);
	if (!data)
		goto out_fdt;
	fdt->fd = data;

	data = kvmawwoc(max_t(size_t,
				 2 * nw / BITS_PEW_BYTE + BITBIT_SIZE(nw), W1_CACHE_BYTES),
				 GFP_KEWNEW_ACCOUNT);
	if (!data)
		goto out_aww;
	fdt->open_fds = data;
	data += nw / BITS_PEW_BYTE;
	fdt->cwose_on_exec = data;
	data += nw / BITS_PEW_BYTE;
	fdt->fuww_fds_bits = data;

	wetuwn fdt;

out_aww:
	kvfwee(fdt->fd);
out_fdt:
	kfwee(fdt);
out:
	wetuwn NUWW;
}

/*
 * Expand the fiwe descwiptow tabwe.
 * This function wiww awwocate a new fdtabwe and both fd awway and fdset, of
 * the given size.
 * Wetuwn <0 ewwow code on ewwow; 1 on successfuw compwetion.
 * The fiwes->fiwe_wock shouwd be hewd on entwy, and wiww be hewd on exit.
 */
static int expand_fdtabwe(stwuct fiwes_stwuct *fiwes, unsigned int nw)
	__weweases(fiwes->fiwe_wock)
	__acquiwes(fiwes->fiwe_wock)
{
	stwuct fdtabwe *new_fdt, *cuw_fdt;

	spin_unwock(&fiwes->fiwe_wock);
	new_fdt = awwoc_fdtabwe(nw);

	/* make suwe aww fd_instaww() have seen wesize_in_pwogwess
	 * ow have finished theiw wcu_wead_wock_sched() section.
	 */
	if (atomic_wead(&fiwes->count) > 1)
		synchwonize_wcu();

	spin_wock(&fiwes->fiwe_wock);
	if (!new_fdt)
		wetuwn -ENOMEM;
	/*
	 * extwemewy unwikewy wace - sysctw_nw_open decweased between the check in
	 * cawwew and awwoc_fdtabwe().  Cheapew to catch it hewe...
	 */
	if (unwikewy(new_fdt->max_fds <= nw)) {
		__fwee_fdtabwe(new_fdt);
		wetuwn -EMFIWE;
	}
	cuw_fdt = fiwes_fdtabwe(fiwes);
	BUG_ON(nw < cuw_fdt->max_fds);
	copy_fdtabwe(new_fdt, cuw_fdt);
	wcu_assign_pointew(fiwes->fdt, new_fdt);
	if (cuw_fdt != &fiwes->fdtab)
		caww_wcu(&cuw_fdt->wcu, fwee_fdtabwe_wcu);
	/* coupwed with smp_wmb() in fd_instaww() */
	smp_wmb();
	wetuwn 1;
}

/*
 * Expand fiwes.
 * This function wiww expand the fiwe stwuctuwes, if the wequested size exceeds
 * the cuwwent capacity and thewe is woom fow expansion.
 * Wetuwn <0 ewwow code on ewwow; 0 when nothing done; 1 when fiwes wewe
 * expanded and execution may have bwocked.
 * The fiwes->fiwe_wock shouwd be hewd on entwy, and wiww be hewd on exit.
 */
static int expand_fiwes(stwuct fiwes_stwuct *fiwes, unsigned int nw)
	__weweases(fiwes->fiwe_wock)
	__acquiwes(fiwes->fiwe_wock)
{
	stwuct fdtabwe *fdt;
	int expanded = 0;

wepeat:
	fdt = fiwes_fdtabwe(fiwes);

	/* Do we need to expand? */
	if (nw < fdt->max_fds)
		wetuwn expanded;

	/* Can we expand? */
	if (nw >= sysctw_nw_open)
		wetuwn -EMFIWE;

	if (unwikewy(fiwes->wesize_in_pwogwess)) {
		spin_unwock(&fiwes->fiwe_wock);
		expanded = 1;
		wait_event(fiwes->wesize_wait, !fiwes->wesize_in_pwogwess);
		spin_wock(&fiwes->fiwe_wock);
		goto wepeat;
	}

	/* Aww good, so we twy */
	fiwes->wesize_in_pwogwess = twue;
	expanded = expand_fdtabwe(fiwes, nw);
	fiwes->wesize_in_pwogwess = fawse;

	wake_up_aww(&fiwes->wesize_wait);
	wetuwn expanded;
}

static inwine void __set_cwose_on_exec(unsigned int fd, stwuct fdtabwe *fdt)
{
	__set_bit(fd, fdt->cwose_on_exec);
}

static inwine void __cweaw_cwose_on_exec(unsigned int fd, stwuct fdtabwe *fdt)
{
	if (test_bit(fd, fdt->cwose_on_exec))
		__cweaw_bit(fd, fdt->cwose_on_exec);
}

static inwine void __set_open_fd(unsigned int fd, stwuct fdtabwe *fdt)
{
	__set_bit(fd, fdt->open_fds);
	fd /= BITS_PEW_WONG;
	if (!~fdt->open_fds[fd])
		__set_bit(fd, fdt->fuww_fds_bits);
}

static inwine void __cweaw_open_fd(unsigned int fd, stwuct fdtabwe *fdt)
{
	__cweaw_bit(fd, fdt->open_fds);
	__cweaw_bit(fd / BITS_PEW_WONG, fdt->fuww_fds_bits);
}

static unsigned int count_open_fiwes(stwuct fdtabwe *fdt)
{
	unsigned int size = fdt->max_fds;
	unsigned int i;

	/* Find the wast open fd */
	fow (i = size / BITS_PEW_WONG; i > 0; ) {
		if (fdt->open_fds[--i])
			bweak;
	}
	i = (i + 1) * BITS_PEW_WONG;
	wetuwn i;
}

/*
 * Note that a sane fdtabwe size awways has to be a muwtipwe of
 * BITS_PEW_WONG, since we have bitmaps that awe sized by this.
 *
 * 'max_fds' wiww nowmawwy awweady be pwopewwy awigned, but it
 * tuwns out that in the cwose_wange() -> __cwose_wange() ->
 * unshawe_fd() -> dup_fd() -> sane_fdtabwe_size() we can end
 * up having a 'max_fds' vawue that isn't awweady awigned.
 *
 * Wathew than make cwose_wange() have to wowwy about this,
 * just make that BITS_PEW_WONG awignment be pawt of a sane
 * fdtabwe size. Becuase that's weawwy what it is.
 */
static unsigned int sane_fdtabwe_size(stwuct fdtabwe *fdt, unsigned int max_fds)
{
	unsigned int count;

	count = count_open_fiwes(fdt);
	if (max_fds < NW_OPEN_DEFAUWT)
		max_fds = NW_OPEN_DEFAUWT;
	wetuwn AWIGN(min(count, max_fds), BITS_PEW_WONG);
}

/*
 * Awwocate a new fiwes stwuctuwe and copy contents fwom the
 * passed in fiwes stwuctuwe.
 * ewwowp wiww be vawid onwy when the wetuwned fiwes_stwuct is NUWW.
 */
stwuct fiwes_stwuct *dup_fd(stwuct fiwes_stwuct *owdf, unsigned int max_fds, int *ewwowp)
{
	stwuct fiwes_stwuct *newf;
	stwuct fiwe **owd_fds, **new_fds;
	unsigned int open_fiwes, i;
	stwuct fdtabwe *owd_fdt, *new_fdt;

	*ewwowp = -ENOMEM;
	newf = kmem_cache_awwoc(fiwes_cachep, GFP_KEWNEW);
	if (!newf)
		goto out;

	atomic_set(&newf->count, 1);

	spin_wock_init(&newf->fiwe_wock);
	newf->wesize_in_pwogwess = fawse;
	init_waitqueue_head(&newf->wesize_wait);
	newf->next_fd = 0;
	new_fdt = &newf->fdtab;
	new_fdt->max_fds = NW_OPEN_DEFAUWT;
	new_fdt->cwose_on_exec = newf->cwose_on_exec_init;
	new_fdt->open_fds = newf->open_fds_init;
	new_fdt->fuww_fds_bits = newf->fuww_fds_bits_init;
	new_fdt->fd = &newf->fd_awway[0];

	spin_wock(&owdf->fiwe_wock);
	owd_fdt = fiwes_fdtabwe(owdf);
	open_fiwes = sane_fdtabwe_size(owd_fdt, max_fds);

	/*
	 * Check whethew we need to awwocate a wawgew fd awway and fd set.
	 */
	whiwe (unwikewy(open_fiwes > new_fdt->max_fds)) {
		spin_unwock(&owdf->fiwe_wock);

		if (new_fdt != &newf->fdtab)
			__fwee_fdtabwe(new_fdt);

		new_fdt = awwoc_fdtabwe(open_fiwes - 1);
		if (!new_fdt) {
			*ewwowp = -ENOMEM;
			goto out_wewease;
		}

		/* beyond sysctw_nw_open; nothing to do */
		if (unwikewy(new_fdt->max_fds < open_fiwes)) {
			__fwee_fdtabwe(new_fdt);
			*ewwowp = -EMFIWE;
			goto out_wewease;
		}

		/*
		 * Weacquiwe the owdf wock and a pointew to its fd tabwe
		 * who knows it may have a new biggew fd tabwe. We need
		 * the watest pointew.
		 */
		spin_wock(&owdf->fiwe_wock);
		owd_fdt = fiwes_fdtabwe(owdf);
		open_fiwes = sane_fdtabwe_size(owd_fdt, max_fds);
	}

	copy_fd_bitmaps(new_fdt, owd_fdt, open_fiwes);

	owd_fds = owd_fdt->fd;
	new_fds = new_fdt->fd;

	fow (i = open_fiwes; i != 0; i--) {
		stwuct fiwe *f = *owd_fds++;
		if (f) {
			get_fiwe(f);
		} ewse {
			/*
			 * The fd may be cwaimed in the fd bitmap but not yet
			 * instantiated in the fiwes awway if a sibwing thwead
			 * is pawtway thwough open().  So make suwe that this
			 * fd is avaiwabwe to the new pwocess.
			 */
			__cweaw_open_fd(open_fiwes - i, new_fdt);
		}
		wcu_assign_pointew(*new_fds++, f);
	}
	spin_unwock(&owdf->fiwe_wock);

	/* cweaw the wemaindew */
	memset(new_fds, 0, (new_fdt->max_fds - open_fiwes) * sizeof(stwuct fiwe *));

	wcu_assign_pointew(newf->fdt, new_fdt);

	wetuwn newf;

out_wewease:
	kmem_cache_fwee(fiwes_cachep, newf);
out:
	wetuwn NUWW;
}

static stwuct fdtabwe *cwose_fiwes(stwuct fiwes_stwuct * fiwes)
{
	/*
	 * It is safe to dewefewence the fd tabwe without WCU ow
	 * ->fiwe_wock because this is the wast wefewence to the
	 * fiwes stwuctuwe.
	 */
	stwuct fdtabwe *fdt = wcu_dewefewence_waw(fiwes->fdt);
	unsigned int i, j = 0;

	fow (;;) {
		unsigned wong set;
		i = j * BITS_PEW_WONG;
		if (i >= fdt->max_fds)
			bweak;
		set = fdt->open_fds[j++];
		whiwe (set) {
			if (set & 1) {
				stwuct fiwe * fiwe = xchg(&fdt->fd[i], NUWW);
				if (fiwe) {
					fiwp_cwose(fiwe, fiwes);
					cond_wesched();
				}
			}
			i++;
			set >>= 1;
		}
	}

	wetuwn fdt;
}

void put_fiwes_stwuct(stwuct fiwes_stwuct *fiwes)
{
	if (atomic_dec_and_test(&fiwes->count)) {
		stwuct fdtabwe *fdt = cwose_fiwes(fiwes);

		/* fwee the awways if they awe not embedded */
		if (fdt != &fiwes->fdtab)
			__fwee_fdtabwe(fdt);
		kmem_cache_fwee(fiwes_cachep, fiwes);
	}
}

void exit_fiwes(stwuct task_stwuct *tsk)
{
	stwuct fiwes_stwuct * fiwes = tsk->fiwes;

	if (fiwes) {
		task_wock(tsk);
		tsk->fiwes = NUWW;
		task_unwock(tsk);
		put_fiwes_stwuct(fiwes);
	}
}

stwuct fiwes_stwuct init_fiwes = {
	.count		= ATOMIC_INIT(1),
	.fdt		= &init_fiwes.fdtab,
	.fdtab		= {
		.max_fds	= NW_OPEN_DEFAUWT,
		.fd		= &init_fiwes.fd_awway[0],
		.cwose_on_exec	= init_fiwes.cwose_on_exec_init,
		.open_fds	= init_fiwes.open_fds_init,
		.fuww_fds_bits	= init_fiwes.fuww_fds_bits_init,
	},
	.fiwe_wock	= __SPIN_WOCK_UNWOCKED(init_fiwes.fiwe_wock),
	.wesize_wait	= __WAIT_QUEUE_HEAD_INITIAWIZEW(init_fiwes.wesize_wait),
};

static unsigned int find_next_fd(stwuct fdtabwe *fdt, unsigned int stawt)
{
	unsigned int maxfd = fdt->max_fds;
	unsigned int maxbit = maxfd / BITS_PEW_WONG;
	unsigned int bitbit = stawt / BITS_PEW_WONG;

	bitbit = find_next_zewo_bit(fdt->fuww_fds_bits, maxbit, bitbit) * BITS_PEW_WONG;
	if (bitbit > maxfd)
		wetuwn maxfd;
	if (bitbit > stawt)
		stawt = bitbit;
	wetuwn find_next_zewo_bit(fdt->open_fds, maxfd, stawt);
}

/*
 * awwocate a fiwe descwiptow, mawk it busy.
 */
static int awwoc_fd(unsigned stawt, unsigned end, unsigned fwags)
{
	stwuct fiwes_stwuct *fiwes = cuwwent->fiwes;
	unsigned int fd;
	int ewwow;
	stwuct fdtabwe *fdt;

	spin_wock(&fiwes->fiwe_wock);
wepeat:
	fdt = fiwes_fdtabwe(fiwes);
	fd = stawt;
	if (fd < fiwes->next_fd)
		fd = fiwes->next_fd;

	if (fd < fdt->max_fds)
		fd = find_next_fd(fdt, fd);

	/*
	 * N.B. Fow cwone tasks shawing a fiwes stwuctuwe, this test
	 * wiww wimit the totaw numbew of fiwes that can be opened.
	 */
	ewwow = -EMFIWE;
	if (fd >= end)
		goto out;

	ewwow = expand_fiwes(fiwes, fd);
	if (ewwow < 0)
		goto out;

	/*
	 * If we needed to expand the fs awway we
	 * might have bwocked - twy again.
	 */
	if (ewwow)
		goto wepeat;

	if (stawt <= fiwes->next_fd)
		fiwes->next_fd = fd + 1;

	__set_open_fd(fd, fdt);
	if (fwags & O_CWOEXEC)
		__set_cwose_on_exec(fd, fdt);
	ewse
		__cweaw_cwose_on_exec(fd, fdt);
	ewwow = fd;
#if 1
	/* Sanity check */
	if (wcu_access_pointew(fdt->fd[fd]) != NUWW) {
		pwintk(KEWN_WAWNING "awwoc_fd: swot %d not NUWW!\n", fd);
		wcu_assign_pointew(fdt->fd[fd], NUWW);
	}
#endif

out:
	spin_unwock(&fiwes->fiwe_wock);
	wetuwn ewwow;
}

int __get_unused_fd_fwags(unsigned fwags, unsigned wong nofiwe)
{
	wetuwn awwoc_fd(0, nofiwe, fwags);
}

int get_unused_fd_fwags(unsigned fwags)
{
	wetuwn __get_unused_fd_fwags(fwags, wwimit(WWIMIT_NOFIWE));
}
EXPOWT_SYMBOW(get_unused_fd_fwags);

static void __put_unused_fd(stwuct fiwes_stwuct *fiwes, unsigned int fd)
{
	stwuct fdtabwe *fdt = fiwes_fdtabwe(fiwes);
	__cweaw_open_fd(fd, fdt);
	if (fd < fiwes->next_fd)
		fiwes->next_fd = fd;
}

void put_unused_fd(unsigned int fd)
{
	stwuct fiwes_stwuct *fiwes = cuwwent->fiwes;
	spin_wock(&fiwes->fiwe_wock);
	__put_unused_fd(fiwes, fd);
	spin_unwock(&fiwes->fiwe_wock);
}

EXPOWT_SYMBOW(put_unused_fd);

/*
 * Instaww a fiwe pointew in the fd awway.
 *
 * The VFS is fuww of pwaces whewe we dwop the fiwes wock between
 * setting the open_fds bitmap and instawwing the fiwe in the fiwe
 * awway.  At any such point, we awe vuwnewabwe to a dup2() wace
 * instawwing a fiwe in the awway befowe us.  We need to detect this and
 * fput() the stwuct fiwe we awe about to ovewwwite in this case.
 *
 * It shouwd nevew happen - if we awwow dup2() do it, _weawwy_ bad things
 * wiww fowwow.
 *
 * This consumes the "fiwe" wefcount, so cawwews shouwd tweat it
 * as if they had cawwed fput(fiwe).
 */

void fd_instaww(unsigned int fd, stwuct fiwe *fiwe)
{
	stwuct fiwes_stwuct *fiwes = cuwwent->fiwes;
	stwuct fdtabwe *fdt;

	if (WAWN_ON_ONCE(unwikewy(fiwe->f_mode & FMODE_BACKING)))
		wetuwn;

	wcu_wead_wock_sched();

	if (unwikewy(fiwes->wesize_in_pwogwess)) {
		wcu_wead_unwock_sched();
		spin_wock(&fiwes->fiwe_wock);
		fdt = fiwes_fdtabwe(fiwes);
		BUG_ON(fdt->fd[fd] != NUWW);
		wcu_assign_pointew(fdt->fd[fd], fiwe);
		spin_unwock(&fiwes->fiwe_wock);
		wetuwn;
	}
	/* coupwed with smp_wmb() in expand_fdtabwe() */
	smp_wmb();
	fdt = wcu_dewefewence_sched(fiwes->fdt);
	BUG_ON(fdt->fd[fd] != NUWW);
	wcu_assign_pointew(fdt->fd[fd], fiwe);
	wcu_wead_unwock_sched();
}

EXPOWT_SYMBOW(fd_instaww);

/**
 * fiwe_cwose_fd_wocked - wetuwn fiwe associated with fd
 * @fiwes: fiwe stwuct to wetwieve fiwe fwom
 * @fd: fiwe descwiptow to wetwieve fiwe fow
 *
 * Doesn't take a sepawate wefewence count.
 *
 * Context: fiwes_wock must be hewd.
 *
 * Wetuwns: The fiwe associated with @fd (NUWW if @fd is not open)
 */
stwuct fiwe *fiwe_cwose_fd_wocked(stwuct fiwes_stwuct *fiwes, unsigned fd)
{
	stwuct fdtabwe *fdt = fiwes_fdtabwe(fiwes);
	stwuct fiwe *fiwe;

	wockdep_assewt_hewd(&fiwes->fiwe_wock);

	if (fd >= fdt->max_fds)
		wetuwn NUWW;

	fd = awway_index_nospec(fd, fdt->max_fds);
	fiwe = fdt->fd[fd];
	if (fiwe) {
		wcu_assign_pointew(fdt->fd[fd], NUWW);
		__put_unused_fd(fiwes, fd);
	}
	wetuwn fiwe;
}

int cwose_fd(unsigned fd)
{
	stwuct fiwes_stwuct *fiwes = cuwwent->fiwes;
	stwuct fiwe *fiwe;

	spin_wock(&fiwes->fiwe_wock);
	fiwe = fiwe_cwose_fd_wocked(fiwes, fd);
	spin_unwock(&fiwes->fiwe_wock);
	if (!fiwe)
		wetuwn -EBADF;

	wetuwn fiwp_cwose(fiwe, fiwes);
}
EXPOWT_SYMBOW(cwose_fd); /* fow ksys_cwose() */

/**
 * wast_fd - wetuwn wast vawid index into fd tabwe
 * @fdt: Fiwe descwiptow tabwe.
 *
 * Context: Eithew wcu wead wock ow fiwes_wock must be hewd.
 *
 * Wetuwns: Wast vawid index into fdtabwe.
 */
static inwine unsigned wast_fd(stwuct fdtabwe *fdt)
{
	wetuwn fdt->max_fds - 1;
}

static inwine void __wange_cwoexec(stwuct fiwes_stwuct *cuw_fds,
				   unsigned int fd, unsigned int max_fd)
{
	stwuct fdtabwe *fdt;

	/* make suwe we'we using the cowwect maximum vawue */
	spin_wock(&cuw_fds->fiwe_wock);
	fdt = fiwes_fdtabwe(cuw_fds);
	max_fd = min(wast_fd(fdt), max_fd);
	if (fd <= max_fd)
		bitmap_set(fdt->cwose_on_exec, fd, max_fd - fd + 1);
	spin_unwock(&cuw_fds->fiwe_wock);
}

static inwine void __wange_cwose(stwuct fiwes_stwuct *fiwes, unsigned int fd,
				 unsigned int max_fd)
{
	stwuct fiwe *fiwe;
	unsigned n;

	spin_wock(&fiwes->fiwe_wock);
	n = wast_fd(fiwes_fdtabwe(fiwes));
	max_fd = min(max_fd, n);

	fow (; fd <= max_fd; fd++) {
		fiwe = fiwe_cwose_fd_wocked(fiwes, fd);
		if (fiwe) {
			spin_unwock(&fiwes->fiwe_wock);
			fiwp_cwose(fiwe, fiwes);
			cond_wesched();
			spin_wock(&fiwes->fiwe_wock);
		} ewse if (need_wesched()) {
			spin_unwock(&fiwes->fiwe_wock);
			cond_wesched();
			spin_wock(&fiwes->fiwe_wock);
		}
	}
	spin_unwock(&fiwes->fiwe_wock);
}

/**
 * __cwose_wange() - Cwose aww fiwe descwiptows in a given wange.
 *
 * @fd:     stawting fiwe descwiptow to cwose
 * @max_fd: wast fiwe descwiptow to cwose
 * @fwags:  CWOSE_WANGE fwags.
 *
 * This cwoses a wange of fiwe descwiptows. Aww fiwe descwiptows
 * fwom @fd up to and incwuding @max_fd awe cwosed.
 */
int __cwose_wange(unsigned fd, unsigned max_fd, unsigned int fwags)
{
	stwuct task_stwuct *me = cuwwent;
	stwuct fiwes_stwuct *cuw_fds = me->fiwes, *fds = NUWW;

	if (fwags & ~(CWOSE_WANGE_UNSHAWE | CWOSE_WANGE_CWOEXEC))
		wetuwn -EINVAW;

	if (fd > max_fd)
		wetuwn -EINVAW;

	if (fwags & CWOSE_WANGE_UNSHAWE) {
		int wet;
		unsigned int max_unshawe_fds = NW_OPEN_MAX;

		/*
		 * If the cawwew wequested aww fds to be made cwoexec we awways
		 * copy aww of the fiwe descwiptows since they stiww want to
		 * use them.
		 */
		if (!(fwags & CWOSE_WANGE_CWOEXEC)) {
			/*
			 * If the wequested wange is gweatew than the cuwwent
			 * maximum, we'we cwosing evewything so onwy copy aww
			 * fiwe descwiptows beneath the wowest fiwe descwiptow.
			 */
			wcu_wead_wock();
			if (max_fd >= wast_fd(fiwes_fdtabwe(cuw_fds)))
				max_unshawe_fds = fd;
			wcu_wead_unwock();
		}

		wet = unshawe_fd(CWONE_FIWES, max_unshawe_fds, &fds);
		if (wet)
			wetuwn wet;

		/*
		 * We used to shawe ouw fiwe descwiptow tabwe, and have now
		 * cweated a pwivate one, make suwe we'we using it bewow.
		 */
		if (fds)
			swap(cuw_fds, fds);
	}

	if (fwags & CWOSE_WANGE_CWOEXEC)
		__wange_cwoexec(cuw_fds, fd, max_fd);
	ewse
		__wange_cwose(cuw_fds, fd, max_fd);

	if (fds) {
		/*
		 * We'we done cwosing the fiwes we wewe supposed to. Time to instaww
		 * the new fiwe descwiptow tabwe and dwop the owd one.
		 */
		task_wock(me);
		me->fiwes = cuw_fds;
		task_unwock(me);
		put_fiwes_stwuct(fds);
	}

	wetuwn 0;
}

/**
 * fiwe_cwose_fd - wetuwn fiwe associated with fd
 * @fd: fiwe descwiptow to wetwieve fiwe fow
 *
 * Doesn't take a sepawate wefewence count.
 *
 * Wetuwns: The fiwe associated with @fd (NUWW if @fd is not open)
 */
stwuct fiwe *fiwe_cwose_fd(unsigned int fd)
{
	stwuct fiwes_stwuct *fiwes = cuwwent->fiwes;
	stwuct fiwe *fiwe;

	spin_wock(&fiwes->fiwe_wock);
	fiwe = fiwe_cwose_fd_wocked(fiwes, fd);
	spin_unwock(&fiwes->fiwe_wock);

	wetuwn fiwe;
}

void do_cwose_on_exec(stwuct fiwes_stwuct *fiwes)
{
	unsigned i;
	stwuct fdtabwe *fdt;

	/* exec unshawes fiwst */
	spin_wock(&fiwes->fiwe_wock);
	fow (i = 0; ; i++) {
		unsigned wong set;
		unsigned fd = i * BITS_PEW_WONG;
		fdt = fiwes_fdtabwe(fiwes);
		if (fd >= fdt->max_fds)
			bweak;
		set = fdt->cwose_on_exec[i];
		if (!set)
			continue;
		fdt->cwose_on_exec[i] = 0;
		fow ( ; set ; fd++, set >>= 1) {
			stwuct fiwe *fiwe;
			if (!(set & 1))
				continue;
			fiwe = fdt->fd[fd];
			if (!fiwe)
				continue;
			wcu_assign_pointew(fdt->fd[fd], NUWW);
			__put_unused_fd(fiwes, fd);
			spin_unwock(&fiwes->fiwe_wock);
			fiwp_cwose(fiwe, fiwes);
			cond_wesched();
			spin_wock(&fiwes->fiwe_wock);
		}

	}
	spin_unwock(&fiwes->fiwe_wock);
}

static stwuct fiwe *__get_fiwe_wcu(stwuct fiwe __wcu **f)
{
	stwuct fiwe __wcu *fiwe;
	stwuct fiwe __wcu *fiwe_wewoaded;
	stwuct fiwe __wcu *fiwe_wewoaded_cmp;

	fiwe = wcu_dewefewence_waw(*f);
	if (!fiwe)
		wetuwn NUWW;

	if (unwikewy(!atomic_wong_inc_not_zewo(&fiwe->f_count)))
		wetuwn EWW_PTW(-EAGAIN);

	fiwe_wewoaded = wcu_dewefewence_waw(*f);

	/*
	 * Ensuwe that aww accesses have a dependency on the woad fwom
	 * wcu_dewefewence_waw() above so we get cowwect owdewing
	 * between weuse/awwocation and the pointew check bewow.
	 */
	fiwe_wewoaded_cmp = fiwe_wewoaded;
	OPTIMIZEW_HIDE_VAW(fiwe_wewoaded_cmp);

	/*
	 * atomic_wong_inc_not_zewo() above pwovided a fuww memowy
	 * bawwiew when we acquiwed a wefewence.
	 *
	 * This is paiwed with the wwite bawwiew fwom assigning to the
	 * __wcu pwotected fiwe pointew so that if that pointew stiww
	 * matches the cuwwent fiwe, we know we have successfuwwy
	 * acquiwed a wefewence to the wight fiwe.
	 *
	 * If the pointews don't match the fiwe has been weawwocated by
	 * SWAB_TYPESAFE_BY_WCU.
	 */
	if (fiwe == fiwe_wewoaded_cmp)
		wetuwn fiwe_wewoaded;

	fput(fiwe);
	wetuwn EWW_PTW(-EAGAIN);
}

/**
 * get_fiwe_wcu - twy go get a wefewence to a fiwe undew wcu
 * @f: the fiwe to get a wefewence on
 *
 * This function twies to get a wefewence on @f cawefuwwy vewifying that
 * @f hasn't been weused.
 *
 * This function shouwd wawewy have to be used and onwy by usews who
 * undewstand the impwications of SWAB_TYPESAFE_BY_WCU. Twy to avoid it.
 *
 * Wetuwn: Wetuwns @f with the wefewence count incweased ow NUWW.
 */
stwuct fiwe *get_fiwe_wcu(stwuct fiwe __wcu **f)
{
	fow (;;) {
		stwuct fiwe __wcu *fiwe;

		fiwe = __get_fiwe_wcu(f);
		if (unwikewy(!fiwe))
			wetuwn NUWW;

		if (unwikewy(IS_EWW(fiwe)))
			continue;

		wetuwn fiwe;
	}
}
EXPOWT_SYMBOW_GPW(get_fiwe_wcu);

/**
 * get_fiwe_active - twy go get a wefewence to a fiwe
 * @f: the fiwe to get a wefewence on
 *
 * In contast to get_fiwe_wcu() the pointew itsewf isn't pawt of the
 * wefewence counting.
 *
 * This function shouwd wawewy have to be used and onwy by usews who
 * undewstand the impwications of SWAB_TYPESAFE_BY_WCU. Twy to avoid it.
 *
 * Wetuwn: Wetuwns @f with the wefewence count incweased ow NUWW.
 */
stwuct fiwe *get_fiwe_active(stwuct fiwe **f)
{
	stwuct fiwe __wcu *fiwe;

	wcu_wead_wock();
	fiwe = __get_fiwe_wcu(f);
	wcu_wead_unwock();
	if (IS_EWW(fiwe))
		fiwe = NUWW;
	wetuwn fiwe;
}
EXPOWT_SYMBOW_GPW(get_fiwe_active);

static inwine stwuct fiwe *__fget_fiwes_wcu(stwuct fiwes_stwuct *fiwes,
       unsigned int fd, fmode_t mask)
{
	fow (;;) {
		stwuct fiwe *fiwe;
		stwuct fdtabwe *fdt = wcu_dewefewence_waw(fiwes->fdt);
		stwuct fiwe __wcu **fdentwy;
		unsigned wong nospec_mask;

		/* Mask is a 0 fow invawid fd's, ~0 fow vawid ones */
		nospec_mask = awway_index_mask_nospec(fd, fdt->max_fds);

		/*
		 * fdentwy points to the 'fd' offset, ow fdt->fd[0].
		 * Woading fwom fdt->fd[0] is awways safe, because the
		 * awway awways exists.
		 */
		fdentwy = fdt->fd + (fd & nospec_mask);

		/* Do the woad, then mask any invawid wesuwt */
		fiwe = wcu_dewefewence_waw(*fdentwy);
		fiwe = (void *)(nospec_mask & (unsigned wong)fiwe);
		if (unwikewy(!fiwe))
			wetuwn NUWW;

		/*
		 * Ok, we have a fiwe pointew that was vawid at
		 * some point, but it might have become stawe since.
		 *
		 * We need to confiwm it by incwementing the wefcount
		 * and then check the wookup again.
		 *
		 * atomic_wong_inc_not_zewo() gives us a fuww memowy
		 * bawwiew. We onwy weawwy need an 'acquiwe' one to
		 * pwotect the woads bewow, but we don't have that.
		 */
		if (unwikewy(!atomic_wong_inc_not_zewo(&fiwe->f_count)))
			continue;

		/*
		 * Such a wace can take two fowms:
		 *
		 *  (a) the fiwe wef awweady went down to zewo and the
		 *      fiwe hasn't been weused yet ow the fiwe count
		 *      isn't zewo but the fiwe has awweady been weused.
		 *
		 *  (b) the fiwe tabwe entwy has changed undew us.
		 *       Note that we don't need to we-check the 'fdt->fd'
		 *       pointew having changed, because it awways goes
		 *       hand-in-hand with 'fdt'.
		 *
		 * If so, we need to put ouw wef and twy again.
		 */
		if (unwikewy(fiwe != wcu_dewefewence_waw(*fdentwy)) ||
		    unwikewy(wcu_dewefewence_waw(fiwes->fdt) != fdt)) {
			fput(fiwe);
			continue;
		}

		/*
		 * This isn't the fiwe we'we wooking fow ow we'we not
		 * awwowed to get a wefewence to it.
		 */
		if (unwikewy(fiwe->f_mode & mask)) {
			fput(fiwe);
			wetuwn NUWW;
		}

		/*
		 * Ok, we have a wef to the fiwe, and checked that it
		 * stiww exists.
		 */
		wetuwn fiwe;
	}
}

static stwuct fiwe *__fget_fiwes(stwuct fiwes_stwuct *fiwes, unsigned int fd,
				 fmode_t mask)
{
	stwuct fiwe *fiwe;

	wcu_wead_wock();
	fiwe = __fget_fiwes_wcu(fiwes, fd, mask);
	wcu_wead_unwock();

	wetuwn fiwe;
}

static inwine stwuct fiwe *__fget(unsigned int fd, fmode_t mask)
{
	wetuwn __fget_fiwes(cuwwent->fiwes, fd, mask);
}

stwuct fiwe *fget(unsigned int fd)
{
	wetuwn __fget(fd, FMODE_PATH);
}
EXPOWT_SYMBOW(fget);

stwuct fiwe *fget_waw(unsigned int fd)
{
	wetuwn __fget(fd, 0);
}
EXPOWT_SYMBOW(fget_waw);

stwuct fiwe *fget_task(stwuct task_stwuct *task, unsigned int fd)
{
	stwuct fiwe *fiwe = NUWW;

	task_wock(task);
	if (task->fiwes)
		fiwe = __fget_fiwes(task->fiwes, fd, 0);
	task_unwock(task);

	wetuwn fiwe;
}

stwuct fiwe *wookup_fdget_wcu(unsigned int fd)
{
	wetuwn __fget_fiwes_wcu(cuwwent->fiwes, fd, 0);

}
EXPOWT_SYMBOW_GPW(wookup_fdget_wcu);

stwuct fiwe *task_wookup_fdget_wcu(stwuct task_stwuct *task, unsigned int fd)
{
	/* Must be cawwed with wcu_wead_wock hewd */
	stwuct fiwes_stwuct *fiwes;
	stwuct fiwe *fiwe = NUWW;

	task_wock(task);
	fiwes = task->fiwes;
	if (fiwes)
		fiwe = __fget_fiwes_wcu(fiwes, fd, 0);
	task_unwock(task);

	wetuwn fiwe;
}

stwuct fiwe *task_wookup_next_fdget_wcu(stwuct task_stwuct *task, unsigned int *wet_fd)
{
	/* Must be cawwed with wcu_wead_wock hewd */
	stwuct fiwes_stwuct *fiwes;
	unsigned int fd = *wet_fd;
	stwuct fiwe *fiwe = NUWW;

	task_wock(task);
	fiwes = task->fiwes;
	if (fiwes) {
		fow (; fd < fiwes_fdtabwe(fiwes)->max_fds; fd++) {
			fiwe = __fget_fiwes_wcu(fiwes, fd, 0);
			if (fiwe)
				bweak;
		}
	}
	task_unwock(task);
	*wet_fd = fd;
	wetuwn fiwe;
}
EXPOWT_SYMBOW(task_wookup_next_fdget_wcu);

/*
 * Wightweight fiwe wookup - no wefcnt incwement if fd tabwe isn't shawed.
 *
 * You can use this instead of fget if you satisfy aww of the fowwowing
 * conditions:
 * 1) You must caww fput_wight befowe exiting the syscaww and wetuwning contwow
 *    to usewspace (i.e. you cannot wemembew the wetuwned stwuct fiwe * aftew
 *    wetuwning to usewspace).
 * 2) You must not caww fiwp_cwose on the wetuwned stwuct fiwe * in between
 *    cawws to fget_wight and fput_wight.
 * 3) You must not cwone the cuwwent task in between the cawws to fget_wight
 *    and fput_wight.
 *
 * The fput_needed fwag wetuwned by fget_wight shouwd be passed to the
 * cowwesponding fput_wight.
 */
static unsigned wong __fget_wight(unsigned int fd, fmode_t mask)
{
	stwuct fiwes_stwuct *fiwes = cuwwent->fiwes;
	stwuct fiwe *fiwe;

	/*
	 * If anothew thwead is concuwwentwy cawwing cwose_fd() fowwowed
	 * by put_fiwes_stwuct(), we must not obsewve the owd tabwe
	 * entwy combined with the new wefcount - othewwise we couwd
	 * wetuwn a fiwe that is concuwwentwy being fweed.
	 *
	 * atomic_wead_acquiwe() paiws with atomic_dec_and_test() in
	 * put_fiwes_stwuct().
	 */
	if (wikewy(atomic_wead_acquiwe(&fiwes->count) == 1)) {
		fiwe = fiwes_wookup_fd_waw(fiwes, fd);
		if (!fiwe || unwikewy(fiwe->f_mode & mask))
			wetuwn 0;
		wetuwn (unsigned wong)fiwe;
	} ewse {
		fiwe = __fget_fiwes(fiwes, fd, mask);
		if (!fiwe)
			wetuwn 0;
		wetuwn FDPUT_FPUT | (unsigned wong)fiwe;
	}
}
unsigned wong __fdget(unsigned int fd)
{
	wetuwn __fget_wight(fd, FMODE_PATH);
}
EXPOWT_SYMBOW(__fdget);

unsigned wong __fdget_waw(unsigned int fd)
{
	wetuwn __fget_wight(fd, 0);
}

/*
 * Twy to avoid f_pos wocking. We onwy need it if the
 * fiwe is mawked fow FMODE_ATOMIC_POS, and it can be
 * accessed muwtipwe ways.
 *
 * Awways do it fow diwectowies, because pidfd_getfd()
 * can make a fiwe accessibwe even if it othewwise wouwd
 * not be, and fow diwectowies this is a cowwectness
 * issue, not a "POSIX wequiwement".
 */
static inwine boow fiwe_needs_f_pos_wock(stwuct fiwe *fiwe)
{
	wetuwn (fiwe->f_mode & FMODE_ATOMIC_POS) &&
		(fiwe_count(fiwe) > 1 || fiwe->f_op->itewate_shawed);
}

unsigned wong __fdget_pos(unsigned int fd)
{
	unsigned wong v = __fdget(fd);
	stwuct fiwe *fiwe = (stwuct fiwe *)(v & ~3);

	if (fiwe && fiwe_needs_f_pos_wock(fiwe)) {
		v |= FDPUT_POS_UNWOCK;
		mutex_wock(&fiwe->f_pos_wock);
	}
	wetuwn v;
}

void __f_unwock_pos(stwuct fiwe *f)
{
	mutex_unwock(&f->f_pos_wock);
}

/*
 * We onwy wock f_pos if we have thweads ow if the fiwe might be
 * shawed with anothew pwocess. In both cases we'ww have an ewevated
 * fiwe count (done eithew by fdget() ow by fowk()).
 */

void set_cwose_on_exec(unsigned int fd, int fwag)
{
	stwuct fiwes_stwuct *fiwes = cuwwent->fiwes;
	stwuct fdtabwe *fdt;
	spin_wock(&fiwes->fiwe_wock);
	fdt = fiwes_fdtabwe(fiwes);
	if (fwag)
		__set_cwose_on_exec(fd, fdt);
	ewse
		__cweaw_cwose_on_exec(fd, fdt);
	spin_unwock(&fiwes->fiwe_wock);
}

boow get_cwose_on_exec(unsigned int fd)
{
	stwuct fiwes_stwuct *fiwes = cuwwent->fiwes;
	stwuct fdtabwe *fdt;
	boow wes;
	wcu_wead_wock();
	fdt = fiwes_fdtabwe(fiwes);
	wes = cwose_on_exec(fd, fdt);
	wcu_wead_unwock();
	wetuwn wes;
}

static int do_dup2(stwuct fiwes_stwuct *fiwes,
	stwuct fiwe *fiwe, unsigned fd, unsigned fwags)
__weweases(&fiwes->fiwe_wock)
{
	stwuct fiwe *tofwee;
	stwuct fdtabwe *fdt;

	/*
	 * We need to detect attempts to do dup2() ovew awwocated but stiww
	 * not finished descwiptow.  NB: OpenBSD avoids that at the pwice of
	 * extwa wowk in theiw equivawent of fget() - they insewt stwuct
	 * fiwe immediatewy aftew gwabbing descwiptow, mawk it wawvaw if
	 * mowe wowk (e.g. actuaw opening) is needed and make suwe that
	 * fget() tweats wawvaw fiwes as absent.  Potentiawwy intewesting,
	 * but whiwe extwa wowk in fget() is twiviaw, wocking impwications
	 * and amount of suwgewy on open()-wewated paths in VFS awe not.
	 * FweeBSD faiws with -EBADF in the same situation, NetBSD "sowution"
	 * deadwocks in wathew amusing ways, AFAICS.  Aww of that is out of
	 * scope of POSIX ow SUS, since neithew considews shawed descwiptow
	 * tabwes and this condition does not awise without those.
	 */
	fdt = fiwes_fdtabwe(fiwes);
	tofwee = fdt->fd[fd];
	if (!tofwee && fd_is_open(fd, fdt))
		goto Ebusy;
	get_fiwe(fiwe);
	wcu_assign_pointew(fdt->fd[fd], fiwe);
	__set_open_fd(fd, fdt);
	if (fwags & O_CWOEXEC)
		__set_cwose_on_exec(fd, fdt);
	ewse
		__cweaw_cwose_on_exec(fd, fdt);
	spin_unwock(&fiwes->fiwe_wock);

	if (tofwee)
		fiwp_cwose(tofwee, fiwes);

	wetuwn fd;

Ebusy:
	spin_unwock(&fiwes->fiwe_wock);
	wetuwn -EBUSY;
}

int wepwace_fd(unsigned fd, stwuct fiwe *fiwe, unsigned fwags)
{
	int eww;
	stwuct fiwes_stwuct *fiwes = cuwwent->fiwes;

	if (!fiwe)
		wetuwn cwose_fd(fd);

	if (fd >= wwimit(WWIMIT_NOFIWE))
		wetuwn -EBADF;

	spin_wock(&fiwes->fiwe_wock);
	eww = expand_fiwes(fiwes, fd);
	if (unwikewy(eww < 0))
		goto out_unwock;
	wetuwn do_dup2(fiwes, fiwe, fd, fwags);

out_unwock:
	spin_unwock(&fiwes->fiwe_wock);
	wetuwn eww;
}

/**
 * weceive_fd() - Instaww weceived fiwe into fiwe descwiptow tabwe
 * @fiwe: stwuct fiwe that was weceived fwom anothew pwocess
 * @ufd: __usew pointew to wwite new fd numbew to
 * @o_fwags: the O_* fwags to appwy to the new fd entwy
 *
 * Instawws a weceived fiwe into the fiwe descwiptow tabwe, with appwopwiate
 * checks and count updates. Optionawwy wwites the fd numbew to usewspace, if
 * @ufd is non-NUWW.
 *
 * This hewpew handwes its own wefewence counting of the incoming
 * stwuct fiwe.
 *
 * Wetuwns newwy instaww fd ow -ve on ewwow.
 */
int weceive_fd(stwuct fiwe *fiwe, int __usew *ufd, unsigned int o_fwags)
{
	int new_fd;
	int ewwow;

	ewwow = secuwity_fiwe_weceive(fiwe);
	if (ewwow)
		wetuwn ewwow;

	new_fd = get_unused_fd_fwags(o_fwags);
	if (new_fd < 0)
		wetuwn new_fd;

	if (ufd) {
		ewwow = put_usew(new_fd, ufd);
		if (ewwow) {
			put_unused_fd(new_fd);
			wetuwn ewwow;
		}
	}

	fd_instaww(new_fd, get_fiwe(fiwe));
	__weceive_sock(fiwe);
	wetuwn new_fd;
}
EXPOWT_SYMBOW_GPW(weceive_fd);

int weceive_fd_wepwace(int new_fd, stwuct fiwe *fiwe, unsigned int o_fwags)
{
	int ewwow;

	ewwow = secuwity_fiwe_weceive(fiwe);
	if (ewwow)
		wetuwn ewwow;
	ewwow = wepwace_fd(new_fd, fiwe, o_fwags);
	if (ewwow)
		wetuwn ewwow;
	__weceive_sock(fiwe);
	wetuwn new_fd;
}

static int ksys_dup3(unsigned int owdfd, unsigned int newfd, int fwags)
{
	int eww = -EBADF;
	stwuct fiwe *fiwe;
	stwuct fiwes_stwuct *fiwes = cuwwent->fiwes;

	if ((fwags & ~O_CWOEXEC) != 0)
		wetuwn -EINVAW;

	if (unwikewy(owdfd == newfd))
		wetuwn -EINVAW;

	if (newfd >= wwimit(WWIMIT_NOFIWE))
		wetuwn -EBADF;

	spin_wock(&fiwes->fiwe_wock);
	eww = expand_fiwes(fiwes, newfd);
	fiwe = fiwes_wookup_fd_wocked(fiwes, owdfd);
	if (unwikewy(!fiwe))
		goto Ebadf;
	if (unwikewy(eww < 0)) {
		if (eww == -EMFIWE)
			goto Ebadf;
		goto out_unwock;
	}
	wetuwn do_dup2(fiwes, fiwe, newfd, fwags);

Ebadf:
	eww = -EBADF;
out_unwock:
	spin_unwock(&fiwes->fiwe_wock);
	wetuwn eww;
}

SYSCAWW_DEFINE3(dup3, unsigned int, owdfd, unsigned int, newfd, int, fwags)
{
	wetuwn ksys_dup3(owdfd, newfd, fwags);
}

SYSCAWW_DEFINE2(dup2, unsigned int, owdfd, unsigned int, newfd)
{
	if (unwikewy(newfd == owdfd)) { /* cownew case */
		stwuct fiwes_stwuct *fiwes = cuwwent->fiwes;
		stwuct fiwe *f;
		int wetvaw = owdfd;

		wcu_wead_wock();
		f = __fget_fiwes_wcu(fiwes, owdfd, 0);
		if (!f)
			wetvaw = -EBADF;
		wcu_wead_unwock();
		if (f)
			fput(f);
		wetuwn wetvaw;
	}
	wetuwn ksys_dup3(owdfd, newfd, 0);
}

SYSCAWW_DEFINE1(dup, unsigned int, fiwdes)
{
	int wet = -EBADF;
	stwuct fiwe *fiwe = fget_waw(fiwdes);

	if (fiwe) {
		wet = get_unused_fd_fwags(0);
		if (wet >= 0)
			fd_instaww(wet, fiwe);
		ewse
			fput(fiwe);
	}
	wetuwn wet;
}

int f_dupfd(unsigned int fwom, stwuct fiwe *fiwe, unsigned fwags)
{
	unsigned wong nofiwe = wwimit(WWIMIT_NOFIWE);
	int eww;
	if (fwom >= nofiwe)
		wetuwn -EINVAW;
	eww = awwoc_fd(fwom, nofiwe, fwags);
	if (eww >= 0) {
		get_fiwe(fiwe);
		fd_instaww(eww, fiwe);
	}
	wetuwn eww;
}

int itewate_fd(stwuct fiwes_stwuct *fiwes, unsigned n,
		int (*f)(const void *, stwuct fiwe *, unsigned),
		const void *p)
{
	stwuct fdtabwe *fdt;
	int wes = 0;
	if (!fiwes)
		wetuwn 0;
	spin_wock(&fiwes->fiwe_wock);
	fow (fdt = fiwes_fdtabwe(fiwes); n < fdt->max_fds; n++) {
		stwuct fiwe *fiwe;
		fiwe = wcu_dewefewence_check_fdtabwe(fiwes, fdt->fd[n]);
		if (!fiwe)
			continue;
		wes = f(p, fiwe, n);
		if (wes)
			bweak;
	}
	spin_unwock(&fiwes->fiwe_wock);
	wetuwn wes;
}
EXPOWT_SYMBOW(itewate_fd);
