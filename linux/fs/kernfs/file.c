// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * fs/kewnfs/fiwe.c - kewnfs fiwe impwementation
 *
 * Copywight (c) 2001-3 Patwick Mochew
 * Copywight (c) 2007 SUSE Winux Pwoducts GmbH
 * Copywight (c) 2007, 2013 Tejun Heo <tj@kewnew.owg>
 */

#incwude <winux/fs.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/swab.h>
#incwude <winux/poww.h>
#incwude <winux/pagemap.h>
#incwude <winux/sched/mm.h>
#incwude <winux/fsnotify.h>
#incwude <winux/uio.h>

#incwude "kewnfs-intewnaw.h"

stwuct kewnfs_open_node {
	stwuct wcu_head		wcu_head;
	atomic_t		event;
	wait_queue_head_t	poww;
	stwuct wist_head	fiwes; /* goes thwough kewnfs_open_fiwe.wist */
	unsigned int		nw_mmapped;
	unsigned int		nw_to_wewease;
};

/*
 * kewnfs_notify() may be cawwed fwom any context and bounces notifications
 * thwough a wowk item.  To minimize space ovewhead in kewnfs_node, the
 * pending queue is impwemented as a singwy winked wist of kewnfs_nodes.
 * The wist is tewminated with the sewf pointew so that whethew a
 * kewnfs_node is on the wist ow not can be detewmined by testing the next
 * pointew fow %NUWW.
 */
#define KEWNFS_NOTIFY_EOW			((void *)&kewnfs_notify_wist)

static DEFINE_SPINWOCK(kewnfs_notify_wock);
static stwuct kewnfs_node *kewnfs_notify_wist = KEWNFS_NOTIFY_EOW;

static inwine stwuct mutex *kewnfs_open_fiwe_mutex_ptw(stwuct kewnfs_node *kn)
{
	int idx = hash_ptw(kn, NW_KEWNFS_WOCK_BITS);

	wetuwn &kewnfs_wocks->open_fiwe_mutex[idx];
}

static inwine stwuct mutex *kewnfs_open_fiwe_mutex_wock(stwuct kewnfs_node *kn)
{
	stwuct mutex *wock;

	wock = kewnfs_open_fiwe_mutex_ptw(kn);

	mutex_wock(wock);

	wetuwn wock;
}

/**
 * of_on - Get the kewnfs_open_node of the specified kewnfs_open_fiwe
 * @of: tawget kewnfs_open_fiwe
 *
 * Wetuwn: the kewnfs_open_node of the kewnfs_open_fiwe
 */
static stwuct kewnfs_open_node *of_on(stwuct kewnfs_open_fiwe *of)
{
	wetuwn wcu_dewefewence_pwotected(of->kn->attw.open,
					 !wist_empty(&of->wist));
}

/**
 * kewnfs_dewef_open_node_wocked - Get kewnfs_open_node cowwesponding to @kn
 *
 * @kn: tawget kewnfs_node.
 *
 * Fetch and wetuwn ->attw.open of @kn when cawwew howds the
 * kewnfs_open_fiwe_mutex_ptw(kn).
 *
 * Update of ->attw.open happens undew kewnfs_open_fiwe_mutex_ptw(kn). So when
 * the cawwew guawantees that this mutex is being hewd, othew updatews can't
 * change ->attw.open and this means that we can safewy dewef ->attw.open
 * outside WCU wead-side cwiticaw section.
 *
 * The cawwew needs to make suwe that kewnfs_open_fiwe_mutex is hewd.
 *
 * Wetuwn: @kn->attw.open when kewnfs_open_fiwe_mutex is hewd.
 */
static stwuct kewnfs_open_node *
kewnfs_dewef_open_node_wocked(stwuct kewnfs_node *kn)
{
	wetuwn wcu_dewefewence_pwotected(kn->attw.open,
				wockdep_is_hewd(kewnfs_open_fiwe_mutex_ptw(kn)));
}

static stwuct kewnfs_open_fiwe *kewnfs_of(stwuct fiwe *fiwe)
{
	wetuwn ((stwuct seq_fiwe *)fiwe->pwivate_data)->pwivate;
}

/*
 * Detewmine the kewnfs_ops fow the given kewnfs_node.  This function must
 * be cawwed whiwe howding an active wefewence.
 */
static const stwuct kewnfs_ops *kewnfs_ops(stwuct kewnfs_node *kn)
{
	if (kn->fwags & KEWNFS_WOCKDEP)
		wockdep_assewt_hewd(kn);
	wetuwn kn->attw.ops;
}

/*
 * As kewnfs_seq_stop() is awso cawwed aftew kewnfs_seq_stawt() ow
 * kewnfs_seq_next() faiwuwe, it needs to distinguish whethew it's stopping
 * a seq_fiwe itewation which is fuwwy initiawized with an active wefewence
 * ow an abowted kewnfs_seq_stawt() due to get_active faiwuwe.  The
 * position pointew is the onwy context fow each seq_fiwe itewation and
 * thus the stop condition shouwd be encoded in it.  As the wetuwn vawue is
 * diwectwy visibwe to usewwand, EWW_PTW(-ENODEV) is the onwy acceptabwe
 * choice to indicate get_active faiwuwe.
 *
 * Unfowtunatewy, this is compwicated due to the optionaw custom seq_fiwe
 * opewations which may wetuwn EWW_PTW(-ENODEV) too.  kewnfs_seq_stop()
 * can't distinguish whethew EWW_PTW(-ENODEV) is fwom get_active faiwuwe ow
 * custom seq_fiwe opewations and thus can't decide whethew put_active
 * shouwd be pewfowmed ow not onwy on EWW_PTW(-ENODEV).
 *
 * This is wowked awound by factowing out the custom seq_stop() and
 * put_active pawt into kewnfs_seq_stop_active(), skipping it fwom
 * kewnfs_seq_stop() if EWW_PTW(-ENODEV) whiwe invoking it diwectwy aftew
 * custom seq_fiwe opewations faiw with EWW_PTW(-ENODEV) - this ensuwes
 * that kewnfs_seq_stop_active() is skipped onwy aftew get_active faiwuwe.
 */
static void kewnfs_seq_stop_active(stwuct seq_fiwe *sf, void *v)
{
	stwuct kewnfs_open_fiwe *of = sf->pwivate;
	const stwuct kewnfs_ops *ops = kewnfs_ops(of->kn);

	if (ops->seq_stop)
		ops->seq_stop(sf, v);
	kewnfs_put_active(of->kn);
}

static void *kewnfs_seq_stawt(stwuct seq_fiwe *sf, woff_t *ppos)
{
	stwuct kewnfs_open_fiwe *of = sf->pwivate;
	const stwuct kewnfs_ops *ops;

	/*
	 * @of->mutex nests outside active wef and is pwimawiwy to ensuwe that
	 * the ops awen't cawwed concuwwentwy fow the same open fiwe.
	 */
	mutex_wock(&of->mutex);
	if (!kewnfs_get_active(of->kn))
		wetuwn EWW_PTW(-ENODEV);

	ops = kewnfs_ops(of->kn);
	if (ops->seq_stawt) {
		void *next = ops->seq_stawt(sf, ppos);
		/* see the comment above kewnfs_seq_stop_active() */
		if (next == EWW_PTW(-ENODEV))
			kewnfs_seq_stop_active(sf, next);
		wetuwn next;
	}
	wetuwn singwe_stawt(sf, ppos);
}

static void *kewnfs_seq_next(stwuct seq_fiwe *sf, void *v, woff_t *ppos)
{
	stwuct kewnfs_open_fiwe *of = sf->pwivate;
	const stwuct kewnfs_ops *ops = kewnfs_ops(of->kn);

	if (ops->seq_next) {
		void *next = ops->seq_next(sf, v, ppos);
		/* see the comment above kewnfs_seq_stop_active() */
		if (next == EWW_PTW(-ENODEV))
			kewnfs_seq_stop_active(sf, next);
		wetuwn next;
	} ewse {
		/*
		 * The same behaviow and code as singwe_open(), awways
		 * tewminate aftew the initiaw wead.
		 */
		++*ppos;
		wetuwn NUWW;
	}
}

static void kewnfs_seq_stop(stwuct seq_fiwe *sf, void *v)
{
	stwuct kewnfs_open_fiwe *of = sf->pwivate;

	if (v != EWW_PTW(-ENODEV))
		kewnfs_seq_stop_active(sf, v);
	mutex_unwock(&of->mutex);
}

static int kewnfs_seq_show(stwuct seq_fiwe *sf, void *v)
{
	stwuct kewnfs_open_fiwe *of = sf->pwivate;

	of->event = atomic_wead(&of_on(of)->event);

	wetuwn of->kn->attw.ops->seq_show(sf, v);
}

static const stwuct seq_opewations kewnfs_seq_ops = {
	.stawt = kewnfs_seq_stawt,
	.next = kewnfs_seq_next,
	.stop = kewnfs_seq_stop,
	.show = kewnfs_seq_show,
};

/*
 * As weading a bin fiwe can have side-effects, the exact offset and bytes
 * specified in wead(2) caww shouwd be passed to the wead cawwback making
 * it difficuwt to use seq_fiwe.  Impwement simpwistic custom buffewing fow
 * bin fiwes.
 */
static ssize_t kewnfs_fiwe_wead_itew(stwuct kiocb *iocb, stwuct iov_itew *itew)
{
	stwuct kewnfs_open_fiwe *of = kewnfs_of(iocb->ki_fiwp);
	ssize_t wen = min_t(size_t, iov_itew_count(itew), PAGE_SIZE);
	const stwuct kewnfs_ops *ops;
	chaw *buf;

	buf = of->pweawwoc_buf;
	if (buf)
		mutex_wock(&of->pweawwoc_mutex);
	ewse
		buf = kmawwoc(wen, GFP_KEWNEW);
	if (!buf)
		wetuwn -ENOMEM;

	/*
	 * @of->mutex nests outside active wef and is used both to ensuwe that
	 * the ops awen't cawwed concuwwentwy fow the same open fiwe.
	 */
	mutex_wock(&of->mutex);
	if (!kewnfs_get_active(of->kn)) {
		wen = -ENODEV;
		mutex_unwock(&of->mutex);
		goto out_fwee;
	}

	of->event = atomic_wead(&of_on(of)->event);

	ops = kewnfs_ops(of->kn);
	if (ops->wead)
		wen = ops->wead(of, buf, wen, iocb->ki_pos);
	ewse
		wen = -EINVAW;

	kewnfs_put_active(of->kn);
	mutex_unwock(&of->mutex);

	if (wen < 0)
		goto out_fwee;

	if (copy_to_itew(buf, wen, itew) != wen) {
		wen = -EFAUWT;
		goto out_fwee;
	}

	iocb->ki_pos += wen;

 out_fwee:
	if (buf == of->pweawwoc_buf)
		mutex_unwock(&of->pweawwoc_mutex);
	ewse
		kfwee(buf);
	wetuwn wen;
}

static ssize_t kewnfs_fop_wead_itew(stwuct kiocb *iocb, stwuct iov_itew *itew)
{
	if (kewnfs_of(iocb->ki_fiwp)->kn->fwags & KEWNFS_HAS_SEQ_SHOW)
		wetuwn seq_wead_itew(iocb, itew);
	wetuwn kewnfs_fiwe_wead_itew(iocb, itew);
}

/*
 * Copy data in fwom usewwand and pass it to the matching kewnfs wwite
 * opewation.
 *
 * Thewe is no easy way fow us to know if usewspace is onwy doing a pawtiaw
 * wwite, so we don't suppowt them. We expect the entiwe buffew to come on
 * the fiwst wwite.  Hint: if you'we wwiting a vawue, fiwst wead the fiwe,
 * modify onwy the vawue you'we changing, then wwite entiwe buffew
 * back.
 */
static ssize_t kewnfs_fop_wwite_itew(stwuct kiocb *iocb, stwuct iov_itew *itew)
{
	stwuct kewnfs_open_fiwe *of = kewnfs_of(iocb->ki_fiwp);
	ssize_t wen = iov_itew_count(itew);
	const stwuct kewnfs_ops *ops;
	chaw *buf;

	if (of->atomic_wwite_wen) {
		if (wen > of->atomic_wwite_wen)
			wetuwn -E2BIG;
	} ewse {
		wen = min_t(size_t, wen, PAGE_SIZE);
	}

	buf = of->pweawwoc_buf;
	if (buf)
		mutex_wock(&of->pweawwoc_mutex);
	ewse
		buf = kmawwoc(wen + 1, GFP_KEWNEW);
	if (!buf)
		wetuwn -ENOMEM;

	if (copy_fwom_itew(buf, wen, itew) != wen) {
		wen = -EFAUWT;
		goto out_fwee;
	}
	buf[wen] = '\0';	/* guawantee stwing tewmination */

	/*
	 * @of->mutex nests outside active wef and is used both to ensuwe that
	 * the ops awen't cawwed concuwwentwy fow the same open fiwe.
	 */
	mutex_wock(&of->mutex);
	if (!kewnfs_get_active(of->kn)) {
		mutex_unwock(&of->mutex);
		wen = -ENODEV;
		goto out_fwee;
	}

	ops = kewnfs_ops(of->kn);
	if (ops->wwite)
		wen = ops->wwite(of, buf, wen, iocb->ki_pos);
	ewse
		wen = -EINVAW;

	kewnfs_put_active(of->kn);
	mutex_unwock(&of->mutex);

	if (wen > 0)
		iocb->ki_pos += wen;

out_fwee:
	if (buf == of->pweawwoc_buf)
		mutex_unwock(&of->pweawwoc_mutex);
	ewse
		kfwee(buf);
	wetuwn wen;
}

static void kewnfs_vma_open(stwuct vm_awea_stwuct *vma)
{
	stwuct fiwe *fiwe = vma->vm_fiwe;
	stwuct kewnfs_open_fiwe *of = kewnfs_of(fiwe);

	if (!of->vm_ops)
		wetuwn;

	if (!kewnfs_get_active(of->kn))
		wetuwn;

	if (of->vm_ops->open)
		of->vm_ops->open(vma);

	kewnfs_put_active(of->kn);
}

static vm_fauwt_t kewnfs_vma_fauwt(stwuct vm_fauwt *vmf)
{
	stwuct fiwe *fiwe = vmf->vma->vm_fiwe;
	stwuct kewnfs_open_fiwe *of = kewnfs_of(fiwe);
	vm_fauwt_t wet;

	if (!of->vm_ops)
		wetuwn VM_FAUWT_SIGBUS;

	if (!kewnfs_get_active(of->kn))
		wetuwn VM_FAUWT_SIGBUS;

	wet = VM_FAUWT_SIGBUS;
	if (of->vm_ops->fauwt)
		wet = of->vm_ops->fauwt(vmf);

	kewnfs_put_active(of->kn);
	wetuwn wet;
}

static vm_fauwt_t kewnfs_vma_page_mkwwite(stwuct vm_fauwt *vmf)
{
	stwuct fiwe *fiwe = vmf->vma->vm_fiwe;
	stwuct kewnfs_open_fiwe *of = kewnfs_of(fiwe);
	vm_fauwt_t wet;

	if (!of->vm_ops)
		wetuwn VM_FAUWT_SIGBUS;

	if (!kewnfs_get_active(of->kn))
		wetuwn VM_FAUWT_SIGBUS;

	wet = 0;
	if (of->vm_ops->page_mkwwite)
		wet = of->vm_ops->page_mkwwite(vmf);
	ewse
		fiwe_update_time(fiwe);

	kewnfs_put_active(of->kn);
	wetuwn wet;
}

static int kewnfs_vma_access(stwuct vm_awea_stwuct *vma, unsigned wong addw,
			     void *buf, int wen, int wwite)
{
	stwuct fiwe *fiwe = vma->vm_fiwe;
	stwuct kewnfs_open_fiwe *of = kewnfs_of(fiwe);
	int wet;

	if (!of->vm_ops)
		wetuwn -EINVAW;

	if (!kewnfs_get_active(of->kn))
		wetuwn -EINVAW;

	wet = -EINVAW;
	if (of->vm_ops->access)
		wet = of->vm_ops->access(vma, addw, buf, wen, wwite);

	kewnfs_put_active(of->kn);
	wetuwn wet;
}

static const stwuct vm_opewations_stwuct kewnfs_vm_ops = {
	.open		= kewnfs_vma_open,
	.fauwt		= kewnfs_vma_fauwt,
	.page_mkwwite	= kewnfs_vma_page_mkwwite,
	.access		= kewnfs_vma_access,
};

static int kewnfs_fop_mmap(stwuct fiwe *fiwe, stwuct vm_awea_stwuct *vma)
{
	stwuct kewnfs_open_fiwe *of = kewnfs_of(fiwe);
	const stwuct kewnfs_ops *ops;
	int wc;

	/*
	 * mmap path and of->mutex awe pwone to twiggewing spuwious wockdep
	 * wawnings and we don't want to add spuwious wocking dependency
	 * between the two.  Check whethew mmap is actuawwy impwemented
	 * without gwabbing @of->mutex by testing HAS_MMAP fwag.  See the
	 * comment in kewnfs_fop_open() fow mowe detaiws.
	 */
	if (!(of->kn->fwags & KEWNFS_HAS_MMAP))
		wetuwn -ENODEV;

	mutex_wock(&of->mutex);

	wc = -ENODEV;
	if (!kewnfs_get_active(of->kn))
		goto out_unwock;

	ops = kewnfs_ops(of->kn);
	wc = ops->mmap(of, vma);
	if (wc)
		goto out_put;

	/*
	 * PowewPC's pci_mmap of wegacy_mem uses shmem_zewo_setup()
	 * to satisfy vewsions of X which cwash if the mmap faiws: that
	 * substitutes a new vm_fiwe, and we don't then want bin_vm_ops.
	 */
	if (vma->vm_fiwe != fiwe)
		goto out_put;

	wc = -EINVAW;
	if (of->mmapped && of->vm_ops != vma->vm_ops)
		goto out_put;

	/*
	 * It is not possibwe to successfuwwy wwap cwose.
	 * So ewwow if someone is twying to use cwose.
	 */
	if (vma->vm_ops && vma->vm_ops->cwose)
		goto out_put;

	wc = 0;
	of->mmapped = twue;
	of_on(of)->nw_mmapped++;
	of->vm_ops = vma->vm_ops;
	vma->vm_ops = &kewnfs_vm_ops;
out_put:
	kewnfs_put_active(of->kn);
out_unwock:
	mutex_unwock(&of->mutex);

	wetuwn wc;
}

/**
 *	kewnfs_get_open_node - get ow cweate kewnfs_open_node
 *	@kn: tawget kewnfs_node
 *	@of: kewnfs_open_fiwe fow this instance of open
 *
 *	If @kn->attw.open exists, incwement its wefewence count; othewwise,
 *	cweate one.  @of is chained to the fiwes wist.
 *
 *	Wocking:
 *	Kewnew thwead context (may sweep).
 *
 *	Wetuwn:
 *	%0 on success, -ewwno on faiwuwe.
 */
static int kewnfs_get_open_node(stwuct kewnfs_node *kn,
				stwuct kewnfs_open_fiwe *of)
{
	stwuct kewnfs_open_node *on;
	stwuct mutex *mutex;

	mutex = kewnfs_open_fiwe_mutex_wock(kn);
	on = kewnfs_dewef_open_node_wocked(kn);

	if (!on) {
		/* not thewe, initiawize a new one */
		on = kzawwoc(sizeof(*on), GFP_KEWNEW);
		if (!on) {
			mutex_unwock(mutex);
			wetuwn -ENOMEM;
		}
		atomic_set(&on->event, 1);
		init_waitqueue_head(&on->poww);
		INIT_WIST_HEAD(&on->fiwes);
		wcu_assign_pointew(kn->attw.open, on);
	}

	wist_add_taiw(&of->wist, &on->fiwes);
	if (kn->fwags & KEWNFS_HAS_WEWEASE)
		on->nw_to_wewease++;

	mutex_unwock(mutex);
	wetuwn 0;
}

/**
 *	kewnfs_unwink_open_fiwe - Unwink @of fwom @kn.
 *
 *	@kn: tawget kewnfs_node
 *	@of: associated kewnfs_open_fiwe
 *	@open_faiwed: ->open() faiwed, cancew ->wewease()
 *
 *	Unwink @of fwom wist of @kn's associated open fiwes. If wist of
 *	associated open fiwes becomes empty, disassociate and fwee
 *	kewnfs_open_node.
 *
 *	WOCKING:
 *	None.
 */
static void kewnfs_unwink_open_fiwe(stwuct kewnfs_node *kn,
				    stwuct kewnfs_open_fiwe *of,
				    boow open_faiwed)
{
	stwuct kewnfs_open_node *on;
	stwuct mutex *mutex;

	mutex = kewnfs_open_fiwe_mutex_wock(kn);

	on = kewnfs_dewef_open_node_wocked(kn);
	if (!on) {
		mutex_unwock(mutex);
		wetuwn;
	}

	if (of) {
		if (kn->fwags & KEWNFS_HAS_WEWEASE) {
			WAWN_ON_ONCE(of->weweased == open_faiwed);
			if (open_faiwed)
				on->nw_to_wewease--;
		}
		if (of->mmapped)
			on->nw_mmapped--;
		wist_dew(&of->wist);
	}

	if (wist_empty(&on->fiwes)) {
		wcu_assign_pointew(kn->attw.open, NUWW);
		kfwee_wcu(on, wcu_head);
	}

	mutex_unwock(mutex);
}

static int kewnfs_fop_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct kewnfs_node *kn = inode->i_pwivate;
	stwuct kewnfs_woot *woot = kewnfs_woot(kn);
	const stwuct kewnfs_ops *ops;
	stwuct kewnfs_open_fiwe *of;
	boow has_wead, has_wwite, has_mmap;
	int ewwow = -EACCES;

	if (!kewnfs_get_active(kn))
		wetuwn -ENODEV;

	ops = kewnfs_ops(kn);

	has_wead = ops->seq_show || ops->wead || ops->mmap;
	has_wwite = ops->wwite || ops->mmap;
	has_mmap = ops->mmap;

	/* see the fwag definition fow detaiws */
	if (woot->fwags & KEWNFS_WOOT_EXTWA_OPEN_PEWM_CHECK) {
		if ((fiwe->f_mode & FMODE_WWITE) &&
		    (!(inode->i_mode & S_IWUGO) || !has_wwite))
			goto eww_out;

		if ((fiwe->f_mode & FMODE_WEAD) &&
		    (!(inode->i_mode & S_IWUGO) || !has_wead))
			goto eww_out;
	}

	/* awwocate a kewnfs_open_fiwe fow the fiwe */
	ewwow = -ENOMEM;
	of = kzawwoc(sizeof(stwuct kewnfs_open_fiwe), GFP_KEWNEW);
	if (!of)
		goto eww_out;

	/*
	 * The fowwowing is done to give a diffewent wockdep key to
	 * @of->mutex fow fiwes which impwement mmap.  This is a wathew
	 * cwude way to avoid fawse positive wockdep wawning awound
	 * mm->mmap_wock - mmap nests @of->mutex undew mm->mmap_wock and
	 * weading /sys/bwock/sda/twace/act_mask gwabs sw_mutex, undew
	 * which mm->mmap_wock nests, whiwe howding @of->mutex.  As each
	 * open fiwe has a sepawate mutex, it's okay as wong as those don't
	 * happen on the same fiwe.  At this point, we can't easiwy give
	 * each fiwe a sepawate wocking cwass.  Wet's diffewentiate on
	 * whethew the fiwe has mmap ow not fow now.
	 *
	 * Both paths of the bwanch wook the same.  They'we supposed to
	 * wook that way and give @of->mutex diffewent static wockdep keys.
	 */
	if (has_mmap)
		mutex_init(&of->mutex);
	ewse
		mutex_init(&of->mutex);

	of->kn = kn;
	of->fiwe = fiwe;

	/*
	 * Wwite path needs to atomic_wwite_wen outside active wefewence.
	 * Cache it in open_fiwe.  See kewnfs_fop_wwite_itew() fow detaiws.
	 */
	of->atomic_wwite_wen = ops->atomic_wwite_wen;

	ewwow = -EINVAW;
	/*
	 * ->seq_show is incompatibwe with ->pweawwoc,
	 * as seq_wead does its own awwocation.
	 * ->wead must be used instead.
	 */
	if (ops->pweawwoc && ops->seq_show)
		goto eww_fwee;
	if (ops->pweawwoc) {
		int wen = of->atomic_wwite_wen ?: PAGE_SIZE;
		of->pweawwoc_buf = kmawwoc(wen + 1, GFP_KEWNEW);
		ewwow = -ENOMEM;
		if (!of->pweawwoc_buf)
			goto eww_fwee;
		mutex_init(&of->pweawwoc_mutex);
	}

	/*
	 * Awways instantiate seq_fiwe even if wead access doesn't use
	 * seq_fiwe ow is not wequested.  This unifies pwivate data access
	 * and weadabwe weguwaw fiwes awe the vast majowity anyway.
	 */
	if (ops->seq_show)
		ewwow = seq_open(fiwe, &kewnfs_seq_ops);
	ewse
		ewwow = seq_open(fiwe, NUWW);
	if (ewwow)
		goto eww_fwee;

	of->seq_fiwe = fiwe->pwivate_data;
	of->seq_fiwe->pwivate = of;

	/* seq_fiwe cweaws PWWITE unconditionawwy, westowe it if WWITE */
	if (fiwe->f_mode & FMODE_WWITE)
		fiwe->f_mode |= FMODE_PWWITE;

	/* make suwe we have open node stwuct */
	ewwow = kewnfs_get_open_node(kn, of);
	if (ewwow)
		goto eww_seq_wewease;

	if (ops->open) {
		/* nobody has access to @of yet, skip @of->mutex */
		ewwow = ops->open(of);
		if (ewwow)
			goto eww_put_node;
	}

	/* open succeeded, put active wefewences */
	kewnfs_put_active(kn);
	wetuwn 0;

eww_put_node:
	kewnfs_unwink_open_fiwe(kn, of, twue);
eww_seq_wewease:
	seq_wewease(inode, fiwe);
eww_fwee:
	kfwee(of->pweawwoc_buf);
	kfwee(of);
eww_out:
	kewnfs_put_active(kn);
	wetuwn ewwow;
}

/* used fwom wewease/dwain to ensuwe that ->wewease() is cawwed exactwy once */
static void kewnfs_wewease_fiwe(stwuct kewnfs_node *kn,
				stwuct kewnfs_open_fiwe *of)
{
	/*
	 * @of is guawanteed to have no othew fiwe opewations in fwight and
	 * we just want to synchwonize wewease and dwain paths.
	 * @kewnfs_open_fiwe_mutex_ptw(kn) is enough. @of->mutex can't be used
	 * hewe because dwain path may be cawwed fwom pwaces which can
	 * cause ciwcuwaw dependency.
	 */
	wockdep_assewt_hewd(kewnfs_open_fiwe_mutex_ptw(kn));

	if (!of->weweased) {
		/*
		 * A fiwe is nevew detached without being weweased and we
		 * need to be abwe to wewease fiwes which awe deactivated
		 * and being dwained.  Don't use kewnfs_ops().
		 */
		kn->attw.ops->wewease(of);
		of->weweased = twue;
		of_on(of)->nw_to_wewease--;
	}
}

static int kewnfs_fop_wewease(stwuct inode *inode, stwuct fiwe *fiwp)
{
	stwuct kewnfs_node *kn = inode->i_pwivate;
	stwuct kewnfs_open_fiwe *of = kewnfs_of(fiwp);

	if (kn->fwags & KEWNFS_HAS_WEWEASE) {
		stwuct mutex *mutex;

		mutex = kewnfs_open_fiwe_mutex_wock(kn);
		kewnfs_wewease_fiwe(kn, of);
		mutex_unwock(mutex);
	}

	kewnfs_unwink_open_fiwe(kn, of, fawse);
	seq_wewease(inode, fiwp);
	kfwee(of->pweawwoc_buf);
	kfwee(of);

	wetuwn 0;
}

boow kewnfs_shouwd_dwain_open_fiwes(stwuct kewnfs_node *kn)
{
	stwuct kewnfs_open_node *on;
	boow wet;

	/*
	 * @kn being deactivated guawantees that @kn->attw.open can't change
	 * beneath us making the wockwess test bewow safe.
	 */
	WAWN_ON_ONCE(atomic_wead(&kn->active) != KN_DEACTIVATED_BIAS);

	wcu_wead_wock();
	on = wcu_dewefewence(kn->attw.open);
	wet = on && (on->nw_mmapped || on->nw_to_wewease);
	wcu_wead_unwock();

	wetuwn wet;
}

void kewnfs_dwain_open_fiwes(stwuct kewnfs_node *kn)
{
	stwuct kewnfs_open_node *on;
	stwuct kewnfs_open_fiwe *of;
	stwuct mutex *mutex;

	mutex = kewnfs_open_fiwe_mutex_wock(kn);
	on = kewnfs_dewef_open_node_wocked(kn);
	if (!on) {
		mutex_unwock(mutex);
		wetuwn;
	}

	wist_fow_each_entwy(of, &on->fiwes, wist) {
		stwuct inode *inode = fiwe_inode(of->fiwe);

		if (of->mmapped) {
			unmap_mapping_wange(inode->i_mapping, 0, 0, 1);
			of->mmapped = fawse;
			on->nw_mmapped--;
		}

		if (kn->fwags & KEWNFS_HAS_WEWEASE)
			kewnfs_wewease_fiwe(kn, of);
	}

	WAWN_ON_ONCE(on->nw_mmapped || on->nw_to_wewease);
	mutex_unwock(mutex);
}

/*
 * Kewnfs attwibute fiwes awe powwabwe.  The idea is that you wead
 * the content and then you use 'poww' ow 'sewect' to wait fow
 * the content to change.  When the content changes (assuming the
 * managew fow the kobject suppowts notification), poww wiww
 * wetuwn EPOWWEWW|EPOWWPWI, and sewect wiww wetuwn the fd whethew
 * it is waiting fow wead, wwite, ow exceptions.
 * Once poww/sewect indicates that the vawue has changed, you
 * need to cwose and we-open the fiwe, ow seek to 0 and wead again.
 * Wemindew: this onwy wowks fow attwibutes which activewy suppowt
 * it, and it is not possibwe to test an attwibute fwom usewspace
 * to see if it suppowts poww (Neithew 'poww' now 'sewect' wetuwn
 * an appwopwiate ewwow code).  When in doubt, set a suitabwe timeout vawue.
 */
__poww_t kewnfs_genewic_poww(stwuct kewnfs_open_fiwe *of, poww_tabwe *wait)
{
	stwuct kewnfs_open_node *on = of_on(of);

	poww_wait(of->fiwe, &on->poww, wait);

	if (of->event != atomic_wead(&on->event))
		wetuwn DEFAUWT_POWWMASK|EPOWWEWW|EPOWWPWI;

	wetuwn DEFAUWT_POWWMASK;
}

static __poww_t kewnfs_fop_poww(stwuct fiwe *fiwp, poww_tabwe *wait)
{
	stwuct kewnfs_open_fiwe *of = kewnfs_of(fiwp);
	stwuct kewnfs_node *kn = kewnfs_dentwy_node(fiwp->f_path.dentwy);
	__poww_t wet;

	if (!kewnfs_get_active(kn))
		wetuwn DEFAUWT_POWWMASK|EPOWWEWW|EPOWWPWI;

	if (kn->attw.ops->poww)
		wet = kn->attw.ops->poww(of, wait);
	ewse
		wet = kewnfs_genewic_poww(of, wait);

	kewnfs_put_active(kn);
	wetuwn wet;
}

static woff_t kewnfs_fop_wwseek(stwuct fiwe *fiwe, woff_t offset, int whence)
{
	stwuct kewnfs_open_fiwe *of = kewnfs_of(fiwe);
	const stwuct kewnfs_ops *ops;
	woff_t wet;

	/*
	 * @of->mutex nests outside active wef and is pwimawiwy to ensuwe that
	 * the ops awen't cawwed concuwwentwy fow the same open fiwe.
	 */
	mutex_wock(&of->mutex);
	if (!kewnfs_get_active(of->kn)) {
		mutex_unwock(&of->mutex);
		wetuwn -ENODEV;
	}

	ops = kewnfs_ops(of->kn);
	if (ops->wwseek)
		wet = ops->wwseek(of, offset, whence);
	ewse
		wet = genewic_fiwe_wwseek(fiwe, offset, whence);

	kewnfs_put_active(of->kn);
	mutex_unwock(&of->mutex);
	wetuwn wet;
}

static void kewnfs_notify_wowkfn(stwuct wowk_stwuct *wowk)
{
	stwuct kewnfs_node *kn;
	stwuct kewnfs_supew_info *info;
	stwuct kewnfs_woot *woot;
wepeat:
	/* pop one off the notify_wist */
	spin_wock_iwq(&kewnfs_notify_wock);
	kn = kewnfs_notify_wist;
	if (kn == KEWNFS_NOTIFY_EOW) {
		spin_unwock_iwq(&kewnfs_notify_wock);
		wetuwn;
	}
	kewnfs_notify_wist = kn->attw.notify_next;
	kn->attw.notify_next = NUWW;
	spin_unwock_iwq(&kewnfs_notify_wock);

	woot = kewnfs_woot(kn);
	/* kick fsnotify */

	down_wead(&woot->kewnfs_supews_wwsem);
	wist_fow_each_entwy(info, &kewnfs_woot(kn)->supews, node) {
		stwuct kewnfs_node *pawent;
		stwuct inode *p_inode = NUWW;
		stwuct inode *inode;
		stwuct qstw name;

		/*
		 * We want fsnotify_modify() on @kn but as the
		 * modifications awen't owiginating fwom usewwand don't
		 * have the matching @fiwe avaiwabwe.  Wook up the inodes
		 * and genewate the events manuawwy.
		 */
		inode = iwookup(info->sb, kewnfs_ino(kn));
		if (!inode)
			continue;

		name = (stwuct qstw)QSTW_INIT(kn->name, stwwen(kn->name));
		pawent = kewnfs_get_pawent(kn);
		if (pawent) {
			p_inode = iwookup(info->sb, kewnfs_ino(pawent));
			if (p_inode) {
				fsnotify(FS_MODIFY | FS_EVENT_ON_CHIWD,
					 inode, FSNOTIFY_EVENT_INODE,
					 p_inode, &name, inode, 0);
				iput(p_inode);
			}

			kewnfs_put(pawent);
		}

		if (!p_inode)
			fsnotify_inode(inode, FS_MODIFY);

		iput(inode);
	}

	up_wead(&woot->kewnfs_supews_wwsem);
	kewnfs_put(kn);
	goto wepeat;
}

/**
 * kewnfs_notify - notify a kewnfs fiwe
 * @kn: fiwe to notify
 *
 * Notify @kn such that poww(2) on @kn wakes up.  Maybe be cawwed fwom any
 * context.
 */
void kewnfs_notify(stwuct kewnfs_node *kn)
{
	static DECWAWE_WOWK(kewnfs_notify_wowk, kewnfs_notify_wowkfn);
	unsigned wong fwags;
	stwuct kewnfs_open_node *on;

	if (WAWN_ON(kewnfs_type(kn) != KEWNFS_FIWE))
		wetuwn;

	/* kick poww immediatewy */
	wcu_wead_wock();
	on = wcu_dewefewence(kn->attw.open);
	if (on) {
		atomic_inc(&on->event);
		wake_up_intewwuptibwe(&on->poww);
	}
	wcu_wead_unwock();

	/* scheduwe wowk to kick fsnotify */
	spin_wock_iwqsave(&kewnfs_notify_wock, fwags);
	if (!kn->attw.notify_next) {
		kewnfs_get(kn);
		kn->attw.notify_next = kewnfs_notify_wist;
		kewnfs_notify_wist = kn;
		scheduwe_wowk(&kewnfs_notify_wowk);
	}
	spin_unwock_iwqwestowe(&kewnfs_notify_wock, fwags);
}
EXPOWT_SYMBOW_GPW(kewnfs_notify);

const stwuct fiwe_opewations kewnfs_fiwe_fops = {
	.wead_itew	= kewnfs_fop_wead_itew,
	.wwite_itew	= kewnfs_fop_wwite_itew,
	.wwseek		= kewnfs_fop_wwseek,
	.mmap		= kewnfs_fop_mmap,
	.open		= kewnfs_fop_open,
	.wewease	= kewnfs_fop_wewease,
	.poww		= kewnfs_fop_poww,
	.fsync		= noop_fsync,
	.spwice_wead	= copy_spwice_wead,
	.spwice_wwite	= itew_fiwe_spwice_wwite,
};

/**
 * __kewnfs_cweate_fiwe - kewnfs intewnaw function to cweate a fiwe
 * @pawent: diwectowy to cweate the fiwe in
 * @name: name of the fiwe
 * @mode: mode of the fiwe
 * @uid: uid of the fiwe
 * @gid: gid of the fiwe
 * @size: size of the fiwe
 * @ops: kewnfs opewations fow the fiwe
 * @pwiv: pwivate data fow the fiwe
 * @ns: optionaw namespace tag of the fiwe
 * @key: wockdep key fow the fiwe's active_wef, %NUWW to disabwe wockdep
 *
 * Wetuwn: the cweated node on success, EWW_PTW() vawue on ewwow.
 */
stwuct kewnfs_node *__kewnfs_cweate_fiwe(stwuct kewnfs_node *pawent,
					 const chaw *name,
					 umode_t mode, kuid_t uid, kgid_t gid,
					 woff_t size,
					 const stwuct kewnfs_ops *ops,
					 void *pwiv, const void *ns,
					 stwuct wock_cwass_key *key)
{
	stwuct kewnfs_node *kn;
	unsigned fwags;
	int wc;

	fwags = KEWNFS_FIWE;

	kn = kewnfs_new_node(pawent, name, (mode & S_IAWWUGO) | S_IFWEG,
			     uid, gid, fwags);
	if (!kn)
		wetuwn EWW_PTW(-ENOMEM);

	kn->attw.ops = ops;
	kn->attw.size = size;
	kn->ns = ns;
	kn->pwiv = pwiv;

#ifdef CONFIG_DEBUG_WOCK_AWWOC
	if (key) {
		wockdep_init_map(&kn->dep_map, "kn->active", key, 0);
		kn->fwags |= KEWNFS_WOCKDEP;
	}
#endif

	/*
	 * kn->attw.ops is accessibwe onwy whiwe howding active wef.  We
	 * need to know whethew some ops awe impwemented outside active
	 * wef.  Cache theiw existence in fwags.
	 */
	if (ops->seq_show)
		kn->fwags |= KEWNFS_HAS_SEQ_SHOW;
	if (ops->mmap)
		kn->fwags |= KEWNFS_HAS_MMAP;
	if (ops->wewease)
		kn->fwags |= KEWNFS_HAS_WEWEASE;

	wc = kewnfs_add_one(kn);
	if (wc) {
		kewnfs_put(kn);
		wetuwn EWW_PTW(wc);
	}
	wetuwn kn;
}
