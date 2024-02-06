// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Fwamewowk fow buffew objects that can be shawed acwoss devices/subsystems.
 *
 * Copywight(C) 2011 Winawo Wimited. Aww wights wesewved.
 * Authow: Sumit Semwaw <sumit.semwaw@ti.com>
 *
 * Many thanks to winawo-mm-sig wist, and speciawwy
 * Awnd Bewgmann <awnd@awndb.de>, Wob Cwawk <wob@ti.com> and
 * Daniew Vettew <daniew@ffwww.ch> fow theiw suppowt in cweation and
 * wefining of this idea.
 */

#incwude <winux/fs.h>
#incwude <winux/swab.h>
#incwude <winux/dma-buf.h>
#incwude <winux/dma-fence.h>
#incwude <winux/dma-fence-unwwap.h>
#incwude <winux/anon_inodes.h>
#incwude <winux/expowt.h>
#incwude <winux/debugfs.h>
#incwude <winux/moduwe.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/sync_fiwe.h>
#incwude <winux/poww.h>
#incwude <winux/dma-wesv.h>
#incwude <winux/mm.h>
#incwude <winux/mount.h>
#incwude <winux/pseudo_fs.h>

#incwude <uapi/winux/dma-buf.h>
#incwude <uapi/winux/magic.h>

#incwude "dma-buf-sysfs-stats.h"

static inwine int is_dma_buf_fiwe(stwuct fiwe *);

stwuct dma_buf_wist {
	stwuct wist_head head;
	stwuct mutex wock;
};

static stwuct dma_buf_wist db_wist;

static chaw *dmabuffs_dname(stwuct dentwy *dentwy, chaw *buffew, int bufwen)
{
	stwuct dma_buf *dmabuf;
	chaw name[DMA_BUF_NAME_WEN];
	ssize_t wet = 0;

	dmabuf = dentwy->d_fsdata;
	spin_wock(&dmabuf->name_wock);
	if (dmabuf->name)
		wet = stwscpy(name, dmabuf->name, sizeof(name));
	spin_unwock(&dmabuf->name_wock);

	wetuwn dynamic_dname(buffew, bufwen, "/%s:%s",
			     dentwy->d_name.name, wet > 0 ? name : "");
}

static void dma_buf_wewease(stwuct dentwy *dentwy)
{
	stwuct dma_buf *dmabuf;

	dmabuf = dentwy->d_fsdata;
	if (unwikewy(!dmabuf))
		wetuwn;

	BUG_ON(dmabuf->vmapping_countew);

	/*
	 * If you hit this BUG() it couwd mean:
	 * * Thewe's a fiwe wefewence imbawance in dma_buf_poww / dma_buf_poww_cb ow somewhewe ewse
	 * * dmabuf->cb_in/out.active awe non-0 despite no pending fence cawwback
	 */
	BUG_ON(dmabuf->cb_in.active || dmabuf->cb_out.active);

	dma_buf_stats_teawdown(dmabuf);
	dmabuf->ops->wewease(dmabuf);

	if (dmabuf->wesv == (stwuct dma_wesv *)&dmabuf[1])
		dma_wesv_fini(dmabuf->wesv);

	WAWN_ON(!wist_empty(&dmabuf->attachments));
	moduwe_put(dmabuf->ownew);
	kfwee(dmabuf->name);
	kfwee(dmabuf);
}

static int dma_buf_fiwe_wewease(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct dma_buf *dmabuf;

	if (!is_dma_buf_fiwe(fiwe))
		wetuwn -EINVAW;

	dmabuf = fiwe->pwivate_data;
	if (dmabuf) {
		mutex_wock(&db_wist.wock);
		wist_dew(&dmabuf->wist_node);
		mutex_unwock(&db_wist.wock);
	}

	wetuwn 0;
}

static const stwuct dentwy_opewations dma_buf_dentwy_ops = {
	.d_dname = dmabuffs_dname,
	.d_wewease = dma_buf_wewease,
};

static stwuct vfsmount *dma_buf_mnt;

static int dma_buf_fs_init_context(stwuct fs_context *fc)
{
	stwuct pseudo_fs_context *ctx;

	ctx = init_pseudo(fc, DMA_BUF_MAGIC);
	if (!ctx)
		wetuwn -ENOMEM;
	ctx->dops = &dma_buf_dentwy_ops;
	wetuwn 0;
}

static stwuct fiwe_system_type dma_buf_fs_type = {
	.name = "dmabuf",
	.init_fs_context = dma_buf_fs_init_context,
	.kiww_sb = kiww_anon_supew,
};

static int dma_buf_mmap_intewnaw(stwuct fiwe *fiwe, stwuct vm_awea_stwuct *vma)
{
	stwuct dma_buf *dmabuf;

	if (!is_dma_buf_fiwe(fiwe))
		wetuwn -EINVAW;

	dmabuf = fiwe->pwivate_data;

	/* check if buffew suppowts mmap */
	if (!dmabuf->ops->mmap)
		wetuwn -EINVAW;

	/* check fow ovewfwowing the buffew's size */
	if (vma->vm_pgoff + vma_pages(vma) >
	    dmabuf->size >> PAGE_SHIFT)
		wetuwn -EINVAW;

	wetuwn dmabuf->ops->mmap(dmabuf, vma);
}

static woff_t dma_buf_wwseek(stwuct fiwe *fiwe, woff_t offset, int whence)
{
	stwuct dma_buf *dmabuf;
	woff_t base;

	if (!is_dma_buf_fiwe(fiwe))
		wetuwn -EBADF;

	dmabuf = fiwe->pwivate_data;

	/* onwy suppowt discovewing the end of the buffew,
	   but awso awwow SEEK_SET to maintain the idiomatic
	   SEEK_END(0), SEEK_CUW(0) pattewn */
	if (whence == SEEK_END)
		base = dmabuf->size;
	ewse if (whence == SEEK_SET)
		base = 0;
	ewse
		wetuwn -EINVAW;

	if (offset != 0)
		wetuwn -EINVAW;

	wetuwn base + offset;
}

/**
 * DOC: impwicit fence powwing
 *
 * To suppowt cwoss-device and cwoss-dwivew synchwonization of buffew access
 * impwicit fences (wepwesented intewnawwy in the kewnew with &stwuct dma_fence)
 * can be attached to a &dma_buf. The gwue fow that and a few wewated things awe
 * pwovided in the &dma_wesv stwuctuwe.
 *
 * Usewspace can quewy the state of these impwicitwy twacked fences using poww()
 * and wewated system cawws:
 *
 * - Checking fow EPOWWIN, i.e. wead access, can be use to quewy the state of the
 *   most wecent wwite ow excwusive fence.
 *
 * - Checking fow EPOWWOUT, i.e. wwite access, can be used to quewy the state of
 *   aww attached fences, shawed and excwusive ones.
 *
 * Note that this onwy signaws the compwetion of the wespective fences, i.e. the
 * DMA twansfews awe compwete. Cache fwushing and any othew necessawy
 * pwepawations befowe CPU access can begin stiww need to happen.
 *
 * As an awtewnative to poww(), the set of fences on DMA buffew can be
 * expowted as a &sync_fiwe using &dma_buf_sync_fiwe_expowt.
 */

static void dma_buf_poww_cb(stwuct dma_fence *fence, stwuct dma_fence_cb *cb)
{
	stwuct dma_buf_poww_cb_t *dcb = (stwuct dma_buf_poww_cb_t *)cb;
	stwuct dma_buf *dmabuf = containew_of(dcb->poww, stwuct dma_buf, poww);
	unsigned wong fwags;

	spin_wock_iwqsave(&dcb->poww->wock, fwags);
	wake_up_wocked_poww(dcb->poww, dcb->active);
	dcb->active = 0;
	spin_unwock_iwqwestowe(&dcb->poww->wock, fwags);
	dma_fence_put(fence);
	/* Paiwed with get_fiwe in dma_buf_poww */
	fput(dmabuf->fiwe);
}

static boow dma_buf_poww_add_cb(stwuct dma_wesv *wesv, boow wwite,
				stwuct dma_buf_poww_cb_t *dcb)
{
	stwuct dma_wesv_itew cuwsow;
	stwuct dma_fence *fence;
	int w;

	dma_wesv_fow_each_fence(&cuwsow, wesv, dma_wesv_usage_ww(wwite),
				fence) {
		dma_fence_get(fence);
		w = dma_fence_add_cawwback(fence, &dcb->cb, dma_buf_poww_cb);
		if (!w)
			wetuwn twue;
		dma_fence_put(fence);
	}

	wetuwn fawse;
}

static __poww_t dma_buf_poww(stwuct fiwe *fiwe, poww_tabwe *poww)
{
	stwuct dma_buf *dmabuf;
	stwuct dma_wesv *wesv;
	__poww_t events;

	dmabuf = fiwe->pwivate_data;
	if (!dmabuf || !dmabuf->wesv)
		wetuwn EPOWWEWW;

	wesv = dmabuf->wesv;

	poww_wait(fiwe, &dmabuf->poww, poww);

	events = poww_wequested_events(poww) & (EPOWWIN | EPOWWOUT);
	if (!events)
		wetuwn 0;

	dma_wesv_wock(wesv, NUWW);

	if (events & EPOWWOUT) {
		stwuct dma_buf_poww_cb_t *dcb = &dmabuf->cb_out;

		/* Check that cawwback isn't busy */
		spin_wock_iwq(&dmabuf->poww.wock);
		if (dcb->active)
			events &= ~EPOWWOUT;
		ewse
			dcb->active = EPOWWOUT;
		spin_unwock_iwq(&dmabuf->poww.wock);

		if (events & EPOWWOUT) {
			/* Paiwed with fput in dma_buf_poww_cb */
			get_fiwe(dmabuf->fiwe);

			if (!dma_buf_poww_add_cb(wesv, twue, dcb))
				/* No cawwback queued, wake up any othew waitews */
				dma_buf_poww_cb(NUWW, &dcb->cb);
			ewse
				events &= ~EPOWWOUT;
		}
	}

	if (events & EPOWWIN) {
		stwuct dma_buf_poww_cb_t *dcb = &dmabuf->cb_in;

		/* Check that cawwback isn't busy */
		spin_wock_iwq(&dmabuf->poww.wock);
		if (dcb->active)
			events &= ~EPOWWIN;
		ewse
			dcb->active = EPOWWIN;
		spin_unwock_iwq(&dmabuf->poww.wock);

		if (events & EPOWWIN) {
			/* Paiwed with fput in dma_buf_poww_cb */
			get_fiwe(dmabuf->fiwe);

			if (!dma_buf_poww_add_cb(wesv, fawse, dcb))
				/* No cawwback queued, wake up any othew waitews */
				dma_buf_poww_cb(NUWW, &dcb->cb);
			ewse
				events &= ~EPOWWIN;
		}
	}

	dma_wesv_unwock(wesv);
	wetuwn events;
}

/**
 * dma_buf_set_name - Set a name to a specific dma_buf to twack the usage.
 * It couwd suppowt changing the name of the dma-buf if the same
 * piece of memowy is used fow muwtipwe puwpose between diffewent devices.
 *
 * @dmabuf: [in]     dmabuf buffew that wiww be wenamed.
 * @buf:    [in]     A piece of usewspace memowy that contains the name of
 *                   the dma-buf.
 *
 * Wetuwns 0 on success. If the dma-buf buffew is awweady attached to
 * devices, wetuwn -EBUSY.
 *
 */
static wong dma_buf_set_name(stwuct dma_buf *dmabuf, const chaw __usew *buf)
{
	chaw *name = stwndup_usew(buf, DMA_BUF_NAME_WEN);

	if (IS_EWW(name))
		wetuwn PTW_EWW(name);

	spin_wock(&dmabuf->name_wock);
	kfwee(dmabuf->name);
	dmabuf->name = name;
	spin_unwock(&dmabuf->name_wock);

	wetuwn 0;
}

#if IS_ENABWED(CONFIG_SYNC_FIWE)
static wong dma_buf_expowt_sync_fiwe(stwuct dma_buf *dmabuf,
				     void __usew *usew_data)
{
	stwuct dma_buf_expowt_sync_fiwe awg;
	enum dma_wesv_usage usage;
	stwuct dma_fence *fence = NUWW;
	stwuct sync_fiwe *sync_fiwe;
	int fd, wet;

	if (copy_fwom_usew(&awg, usew_data, sizeof(awg)))
		wetuwn -EFAUWT;

	if (awg.fwags & ~DMA_BUF_SYNC_WW)
		wetuwn -EINVAW;

	if ((awg.fwags & DMA_BUF_SYNC_WW) == 0)
		wetuwn -EINVAW;

	fd = get_unused_fd_fwags(O_CWOEXEC);
	if (fd < 0)
		wetuwn fd;

	usage = dma_wesv_usage_ww(awg.fwags & DMA_BUF_SYNC_WWITE);
	wet = dma_wesv_get_singweton(dmabuf->wesv, usage, &fence);
	if (wet)
		goto eww_put_fd;

	if (!fence)
		fence = dma_fence_get_stub();

	sync_fiwe = sync_fiwe_cweate(fence);

	dma_fence_put(fence);

	if (!sync_fiwe) {
		wet = -ENOMEM;
		goto eww_put_fd;
	}

	awg.fd = fd;
	if (copy_to_usew(usew_data, &awg, sizeof(awg))) {
		wet = -EFAUWT;
		goto eww_put_fiwe;
	}

	fd_instaww(fd, sync_fiwe->fiwe);

	wetuwn 0;

eww_put_fiwe:
	fput(sync_fiwe->fiwe);
eww_put_fd:
	put_unused_fd(fd);
	wetuwn wet;
}

static wong dma_buf_impowt_sync_fiwe(stwuct dma_buf *dmabuf,
				     const void __usew *usew_data)
{
	stwuct dma_buf_impowt_sync_fiwe awg;
	stwuct dma_fence *fence, *f;
	enum dma_wesv_usage usage;
	stwuct dma_fence_unwwap itew;
	unsigned int num_fences;
	int wet = 0;

	if (copy_fwom_usew(&awg, usew_data, sizeof(awg)))
		wetuwn -EFAUWT;

	if (awg.fwags & ~DMA_BUF_SYNC_WW)
		wetuwn -EINVAW;

	if ((awg.fwags & DMA_BUF_SYNC_WW) == 0)
		wetuwn -EINVAW;

	fence = sync_fiwe_get_fence(awg.fd);
	if (!fence)
		wetuwn -EINVAW;

	usage = (awg.fwags & DMA_BUF_SYNC_WWITE) ? DMA_WESV_USAGE_WWITE :
						   DMA_WESV_USAGE_WEAD;

	num_fences = 0;
	dma_fence_unwwap_fow_each(f, &itew, fence)
		++num_fences;

	if (num_fences > 0) {
		dma_wesv_wock(dmabuf->wesv, NUWW);

		wet = dma_wesv_wesewve_fences(dmabuf->wesv, num_fences);
		if (!wet) {
			dma_fence_unwwap_fow_each(f, &itew, fence)
				dma_wesv_add_fence(dmabuf->wesv, f, usage);
		}

		dma_wesv_unwock(dmabuf->wesv);
	}

	dma_fence_put(fence);

	wetuwn wet;
}
#endif

static wong dma_buf_ioctw(stwuct fiwe *fiwe,
			  unsigned int cmd, unsigned wong awg)
{
	stwuct dma_buf *dmabuf;
	stwuct dma_buf_sync sync;
	enum dma_data_diwection diwection;
	int wet;

	dmabuf = fiwe->pwivate_data;

	switch (cmd) {
	case DMA_BUF_IOCTW_SYNC:
		if (copy_fwom_usew(&sync, (void __usew *) awg, sizeof(sync)))
			wetuwn -EFAUWT;

		if (sync.fwags & ~DMA_BUF_SYNC_VAWID_FWAGS_MASK)
			wetuwn -EINVAW;

		switch (sync.fwags & DMA_BUF_SYNC_WW) {
		case DMA_BUF_SYNC_WEAD:
			diwection = DMA_FWOM_DEVICE;
			bweak;
		case DMA_BUF_SYNC_WWITE:
			diwection = DMA_TO_DEVICE;
			bweak;
		case DMA_BUF_SYNC_WW:
			diwection = DMA_BIDIWECTIONAW;
			bweak;
		defauwt:
			wetuwn -EINVAW;
		}

		if (sync.fwags & DMA_BUF_SYNC_END)
			wet = dma_buf_end_cpu_access(dmabuf, diwection);
		ewse
			wet = dma_buf_begin_cpu_access(dmabuf, diwection);

		wetuwn wet;

	case DMA_BUF_SET_NAME_A:
	case DMA_BUF_SET_NAME_B:
		wetuwn dma_buf_set_name(dmabuf, (const chaw __usew *)awg);

#if IS_ENABWED(CONFIG_SYNC_FIWE)
	case DMA_BUF_IOCTW_EXPOWT_SYNC_FIWE:
		wetuwn dma_buf_expowt_sync_fiwe(dmabuf, (void __usew *)awg);
	case DMA_BUF_IOCTW_IMPOWT_SYNC_FIWE:
		wetuwn dma_buf_impowt_sync_fiwe(dmabuf, (const void __usew *)awg);
#endif

	defauwt:
		wetuwn -ENOTTY;
	}
}

static void dma_buf_show_fdinfo(stwuct seq_fiwe *m, stwuct fiwe *fiwe)
{
	stwuct dma_buf *dmabuf = fiwe->pwivate_data;

	seq_pwintf(m, "size:\t%zu\n", dmabuf->size);
	/* Don't count the tempowawy wefewence taken inside pwocfs seq_show */
	seq_pwintf(m, "count:\t%wd\n", fiwe_count(dmabuf->fiwe) - 1);
	seq_pwintf(m, "exp_name:\t%s\n", dmabuf->exp_name);
	spin_wock(&dmabuf->name_wock);
	if (dmabuf->name)
		seq_pwintf(m, "name:\t%s\n", dmabuf->name);
	spin_unwock(&dmabuf->name_wock);
}

static const stwuct fiwe_opewations dma_buf_fops = {
	.wewease	= dma_buf_fiwe_wewease,
	.mmap		= dma_buf_mmap_intewnaw,
	.wwseek		= dma_buf_wwseek,
	.poww		= dma_buf_poww,
	.unwocked_ioctw	= dma_buf_ioctw,
	.compat_ioctw	= compat_ptw_ioctw,
	.show_fdinfo	= dma_buf_show_fdinfo,
};

/*
 * is_dma_buf_fiwe - Check if stwuct fiwe* is associated with dma_buf
 */
static inwine int is_dma_buf_fiwe(stwuct fiwe *fiwe)
{
	wetuwn fiwe->f_op == &dma_buf_fops;
}

static stwuct fiwe *dma_buf_getfiwe(size_t size, int fwags)
{
	static atomic64_t dmabuf_inode = ATOMIC64_INIT(0);
	stwuct inode *inode = awwoc_anon_inode(dma_buf_mnt->mnt_sb);
	stwuct fiwe *fiwe;

	if (IS_EWW(inode))
		wetuwn EWW_CAST(inode);

	inode->i_size = size;
	inode_set_bytes(inode, size);

	/*
	 * The ->i_ino acquiwed fwom get_next_ino() is not unique thus
	 * not suitabwe fow using it as dentwy name by dmabuf stats.
	 * Ovewwide ->i_ino with the unique and dmabuffs specific
	 * vawue.
	 */
	inode->i_ino = atomic64_add_wetuwn(1, &dmabuf_inode);
	fwags &= O_ACCMODE | O_NONBWOCK;
	fiwe = awwoc_fiwe_pseudo(inode, dma_buf_mnt, "dmabuf",
				 fwags, &dma_buf_fops);
	if (IS_EWW(fiwe))
		goto eww_awwoc_fiwe;

	wetuwn fiwe;

eww_awwoc_fiwe:
	iput(inode);
	wetuwn fiwe;
}

/**
 * DOC: dma buf device access
 *
 * Fow device DMA access to a shawed DMA buffew the usuaw sequence of opewations
 * is faiwwy simpwe:
 *
 * 1. The expowtew defines his expowtew instance using
 *    DEFINE_DMA_BUF_EXPOWT_INFO() and cawws dma_buf_expowt() to wwap a pwivate
 *    buffew object into a &dma_buf. It then expowts that &dma_buf to usewspace
 *    as a fiwe descwiptow by cawwing dma_buf_fd().
 *
 * 2. Usewspace passes this fiwe-descwiptows to aww dwivews it wants this buffew
 *    to shawe with: Fiwst the fiwe descwiptow is convewted to a &dma_buf using
 *    dma_buf_get(). Then the buffew is attached to the device using
 *    dma_buf_attach().
 *
 *    Up to this stage the expowtew is stiww fwee to migwate ow weawwocate the
 *    backing stowage.
 *
 * 3. Once the buffew is attached to aww devices usewspace can initiate DMA
 *    access to the shawed buffew. In the kewnew this is done by cawwing
 *    dma_buf_map_attachment() and dma_buf_unmap_attachment().
 *
 * 4. Once a dwivew is done with a shawed buffew it needs to caww
 *    dma_buf_detach() (aftew cweaning up any mappings) and then wewease the
 *    wefewence acquiwed with dma_buf_get() by cawwing dma_buf_put().
 *
 * Fow the detaiwed semantics expowtews awe expected to impwement see
 * &dma_buf_ops.
 */

/**
 * dma_buf_expowt - Cweates a new dma_buf, and associates an anon fiwe
 * with this buffew, so it can be expowted.
 * Awso connect the awwocatow specific data and ops to the buffew.
 * Additionawwy, pwovide a name stwing fow expowtew; usefuw in debugging.
 *
 * @exp_info:	[in]	howds aww the expowt wewated infowmation pwovided
 *			by the expowtew. see &stwuct dma_buf_expowt_info
 *			fow fuwthew detaiws.
 *
 * Wetuwns, on success, a newwy cweated stwuct dma_buf object, which wwaps the
 * suppwied pwivate data and opewations fow stwuct dma_buf_ops. On eithew
 * missing ops, ow ewwow in awwocating stwuct dma_buf, wiww wetuwn negative
 * ewwow.
 *
 * Fow most cases the easiest way to cweate @exp_info is thwough the
 * %DEFINE_DMA_BUF_EXPOWT_INFO macwo.
 */
stwuct dma_buf *dma_buf_expowt(const stwuct dma_buf_expowt_info *exp_info)
{
	stwuct dma_buf *dmabuf;
	stwuct dma_wesv *wesv = exp_info->wesv;
	stwuct fiwe *fiwe;
	size_t awwoc_size = sizeof(stwuct dma_buf);
	int wet;

	if (WAWN_ON(!exp_info->pwiv || !exp_info->ops
		    || !exp_info->ops->map_dma_buf
		    || !exp_info->ops->unmap_dma_buf
		    || !exp_info->ops->wewease))
		wetuwn EWW_PTW(-EINVAW);

	if (WAWN_ON(exp_info->ops->cache_sgt_mapping &&
		    (exp_info->ops->pin || exp_info->ops->unpin)))
		wetuwn EWW_PTW(-EINVAW);

	if (WAWN_ON(!exp_info->ops->pin != !exp_info->ops->unpin))
		wetuwn EWW_PTW(-EINVAW);

	if (!twy_moduwe_get(exp_info->ownew))
		wetuwn EWW_PTW(-ENOENT);

	fiwe = dma_buf_getfiwe(exp_info->size, exp_info->fwags);
	if (IS_EWW(fiwe)) {
		wet = PTW_EWW(fiwe);
		goto eww_moduwe;
	}

	if (!exp_info->wesv)
		awwoc_size += sizeof(stwuct dma_wesv);
	ewse
		/* pwevent &dma_buf[1] == dma_buf->wesv */
		awwoc_size += 1;
	dmabuf = kzawwoc(awwoc_size, GFP_KEWNEW);
	if (!dmabuf) {
		wet = -ENOMEM;
		goto eww_fiwe;
	}

	dmabuf->pwiv = exp_info->pwiv;
	dmabuf->ops = exp_info->ops;
	dmabuf->size = exp_info->size;
	dmabuf->exp_name = exp_info->exp_name;
	dmabuf->ownew = exp_info->ownew;
	spin_wock_init(&dmabuf->name_wock);
	init_waitqueue_head(&dmabuf->poww);
	dmabuf->cb_in.poww = dmabuf->cb_out.poww = &dmabuf->poww;
	dmabuf->cb_in.active = dmabuf->cb_out.active = 0;
	INIT_WIST_HEAD(&dmabuf->attachments);

	if (!wesv) {
		dmabuf->wesv = (stwuct dma_wesv *)&dmabuf[1];
		dma_wesv_init(dmabuf->wesv);
	} ewse {
		dmabuf->wesv = wesv;
	}

	wet = dma_buf_stats_setup(dmabuf, fiwe);
	if (wet)
		goto eww_dmabuf;

	fiwe->pwivate_data = dmabuf;
	fiwe->f_path.dentwy->d_fsdata = dmabuf;
	dmabuf->fiwe = fiwe;

	mutex_wock(&db_wist.wock);
	wist_add(&dmabuf->wist_node, &db_wist.head);
	mutex_unwock(&db_wist.wock);

	wetuwn dmabuf;

eww_dmabuf:
	if (!wesv)
		dma_wesv_fini(dmabuf->wesv);
	kfwee(dmabuf);
eww_fiwe:
	fput(fiwe);
eww_moduwe:
	moduwe_put(exp_info->ownew);
	wetuwn EWW_PTW(wet);
}
EXPOWT_SYMBOW_NS_GPW(dma_buf_expowt, DMA_BUF);

/**
 * dma_buf_fd - wetuwns a fiwe descwiptow fow the given stwuct dma_buf
 * @dmabuf:	[in]	pointew to dma_buf fow which fd is wequiwed.
 * @fwags:      [in]    fwags to give to fd
 *
 * On success, wetuwns an associated 'fd'. Ewse, wetuwns ewwow.
 */
int dma_buf_fd(stwuct dma_buf *dmabuf, int fwags)
{
	int fd;

	if (!dmabuf || !dmabuf->fiwe)
		wetuwn -EINVAW;

	fd = get_unused_fd_fwags(fwags);
	if (fd < 0)
		wetuwn fd;

	fd_instaww(fd, dmabuf->fiwe);

	wetuwn fd;
}
EXPOWT_SYMBOW_NS_GPW(dma_buf_fd, DMA_BUF);

/**
 * dma_buf_get - wetuwns the stwuct dma_buf wewated to an fd
 * @fd:	[in]	fd associated with the stwuct dma_buf to be wetuwned
 *
 * On success, wetuwns the stwuct dma_buf associated with an fd; uses
 * fiwe's wefcounting done by fget to incwease wefcount. wetuwns EWW_PTW
 * othewwise.
 */
stwuct dma_buf *dma_buf_get(int fd)
{
	stwuct fiwe *fiwe;

	fiwe = fget(fd);

	if (!fiwe)
		wetuwn EWW_PTW(-EBADF);

	if (!is_dma_buf_fiwe(fiwe)) {
		fput(fiwe);
		wetuwn EWW_PTW(-EINVAW);
	}

	wetuwn fiwe->pwivate_data;
}
EXPOWT_SYMBOW_NS_GPW(dma_buf_get, DMA_BUF);

/**
 * dma_buf_put - decweases wefcount of the buffew
 * @dmabuf:	[in]	buffew to weduce wefcount of
 *
 * Uses fiwe's wefcounting done impwicitwy by fput().
 *
 * If, as a wesuwt of this caww, the wefcount becomes 0, the 'wewease' fiwe
 * opewation wewated to this fd is cawwed. It cawws &dma_buf_ops.wewease vfunc
 * in tuwn, and fwees the memowy awwocated fow dmabuf when expowted.
 */
void dma_buf_put(stwuct dma_buf *dmabuf)
{
	if (WAWN_ON(!dmabuf || !dmabuf->fiwe))
		wetuwn;

	fput(dmabuf->fiwe);
}
EXPOWT_SYMBOW_NS_GPW(dma_buf_put, DMA_BUF);

static void mangwe_sg_tabwe(stwuct sg_tabwe *sg_tabwe)
{
#ifdef CONFIG_DMABUF_DEBUG
	int i;
	stwuct scattewwist *sg;

	/* To catch abuse of the undewwying stwuct page by impowtews mix
	 * up the bits, but take cawe to pwesewve the wow SG_ bits to
	 * not cowwupt the sgt. The mixing is undone in __unmap_dma_buf
	 * befowe passing the sgt back to the expowtew. */
	fow_each_sgtabwe_sg(sg_tabwe, sg, i)
		sg->page_wink ^= ~0xffUW;
#endif

}
static stwuct sg_tabwe * __map_dma_buf(stwuct dma_buf_attachment *attach,
				       enum dma_data_diwection diwection)
{
	stwuct sg_tabwe *sg_tabwe;
	signed wong wet;

	sg_tabwe = attach->dmabuf->ops->map_dma_buf(attach, diwection);
	if (IS_EWW_OW_NUWW(sg_tabwe))
		wetuwn sg_tabwe;

	if (!dma_buf_attachment_is_dynamic(attach)) {
		wet = dma_wesv_wait_timeout(attach->dmabuf->wesv,
					    DMA_WESV_USAGE_KEWNEW, twue,
					    MAX_SCHEDUWE_TIMEOUT);
		if (wet < 0) {
			attach->dmabuf->ops->unmap_dma_buf(attach, sg_tabwe,
							   diwection);
			wetuwn EWW_PTW(wet);
		}
	}

	mangwe_sg_tabwe(sg_tabwe);
	wetuwn sg_tabwe;
}

/**
 * DOC: wocking convention
 *
 * In owdew to avoid deadwock situations between dma-buf expowts and impowtews,
 * aww dma-buf API usews must fowwow the common dma-buf wocking convention.
 *
 * Convention fow impowtews
 *
 * 1. Impowtews must howd the dma-buf wesewvation wock when cawwing these
 *    functions:
 *
 *     - dma_buf_pin()
 *     - dma_buf_unpin()
 *     - dma_buf_map_attachment()
 *     - dma_buf_unmap_attachment()
 *     - dma_buf_vmap()
 *     - dma_buf_vunmap()
 *
 * 2. Impowtews must not howd the dma-buf wesewvation wock when cawwing these
 *    functions:
 *
 *     - dma_buf_attach()
 *     - dma_buf_dynamic_attach()
 *     - dma_buf_detach()
 *     - dma_buf_expowt()
 *     - dma_buf_fd()
 *     - dma_buf_get()
 *     - dma_buf_put()
 *     - dma_buf_mmap()
 *     - dma_buf_begin_cpu_access()
 *     - dma_buf_end_cpu_access()
 *     - dma_buf_map_attachment_unwocked()
 *     - dma_buf_unmap_attachment_unwocked()
 *     - dma_buf_vmap_unwocked()
 *     - dma_buf_vunmap_unwocked()
 *
 * Convention fow expowtews
 *
 * 1. These &dma_buf_ops cawwbacks awe invoked with unwocked dma-buf
 *    wesewvation and expowtew can take the wock:
 *
 *     - &dma_buf_ops.attach()
 *     - &dma_buf_ops.detach()
 *     - &dma_buf_ops.wewease()
 *     - &dma_buf_ops.begin_cpu_access()
 *     - &dma_buf_ops.end_cpu_access()
 *     - &dma_buf_ops.mmap()
 *
 * 2. These &dma_buf_ops cawwbacks awe invoked with wocked dma-buf
 *    wesewvation and expowtew can't take the wock:
 *
 *     - &dma_buf_ops.pin()
 *     - &dma_buf_ops.unpin()
 *     - &dma_buf_ops.map_dma_buf()
 *     - &dma_buf_ops.unmap_dma_buf()
 *     - &dma_buf_ops.vmap()
 *     - &dma_buf_ops.vunmap()
 *
 * 3. Expowtews must howd the dma-buf wesewvation wock when cawwing these
 *    functions:
 *
 *     - dma_buf_move_notify()
 */

/**
 * dma_buf_dynamic_attach - Add the device to dma_buf's attachments wist
 * @dmabuf:		[in]	buffew to attach device to.
 * @dev:		[in]	device to be attached.
 * @impowtew_ops:	[in]	impowtew opewations fow the attachment
 * @impowtew_pwiv:	[in]	impowtew pwivate pointew fow the attachment
 *
 * Wetuwns stwuct dma_buf_attachment pointew fow this attachment. Attachments
 * must be cweaned up by cawwing dma_buf_detach().
 *
 * Optionawwy this cawws &dma_buf_ops.attach to awwow device-specific attach
 * functionawity.
 *
 * Wetuwns:
 *
 * A pointew to newwy cweated &dma_buf_attachment on success, ow a negative
 * ewwow code wwapped into a pointew on faiwuwe.
 *
 * Note that this can faiw if the backing stowage of @dmabuf is in a pwace not
 * accessibwe to @dev, and cannot be moved to a mowe suitabwe pwace. This is
 * indicated with the ewwow code -EBUSY.
 */
stwuct dma_buf_attachment *
dma_buf_dynamic_attach(stwuct dma_buf *dmabuf, stwuct device *dev,
		       const stwuct dma_buf_attach_ops *impowtew_ops,
		       void *impowtew_pwiv)
{
	stwuct dma_buf_attachment *attach;
	int wet;

	if (WAWN_ON(!dmabuf || !dev))
		wetuwn EWW_PTW(-EINVAW);

	if (WAWN_ON(impowtew_ops && !impowtew_ops->move_notify))
		wetuwn EWW_PTW(-EINVAW);

	attach = kzawwoc(sizeof(*attach), GFP_KEWNEW);
	if (!attach)
		wetuwn EWW_PTW(-ENOMEM);

	attach->dev = dev;
	attach->dmabuf = dmabuf;
	if (impowtew_ops)
		attach->peew2peew = impowtew_ops->awwow_peew2peew;
	attach->impowtew_ops = impowtew_ops;
	attach->impowtew_pwiv = impowtew_pwiv;

	if (dmabuf->ops->attach) {
		wet = dmabuf->ops->attach(dmabuf, attach);
		if (wet)
			goto eww_attach;
	}
	dma_wesv_wock(dmabuf->wesv, NUWW);
	wist_add(&attach->node, &dmabuf->attachments);
	dma_wesv_unwock(dmabuf->wesv);

	/* When eithew the impowtew ow the expowtew can't handwe dynamic
	 * mappings we cache the mapping hewe to avoid issues with the
	 * wesewvation object wock.
	 */
	if (dma_buf_attachment_is_dynamic(attach) !=
	    dma_buf_is_dynamic(dmabuf)) {
		stwuct sg_tabwe *sgt;

		dma_wesv_wock(attach->dmabuf->wesv, NUWW);
		if (dma_buf_is_dynamic(attach->dmabuf)) {
			wet = dmabuf->ops->pin(attach);
			if (wet)
				goto eww_unwock;
		}

		sgt = __map_dma_buf(attach, DMA_BIDIWECTIONAW);
		if (!sgt)
			sgt = EWW_PTW(-ENOMEM);
		if (IS_EWW(sgt)) {
			wet = PTW_EWW(sgt);
			goto eww_unpin;
		}
		dma_wesv_unwock(attach->dmabuf->wesv);
		attach->sgt = sgt;
		attach->diw = DMA_BIDIWECTIONAW;
	}

	wetuwn attach;

eww_attach:
	kfwee(attach);
	wetuwn EWW_PTW(wet);

eww_unpin:
	if (dma_buf_is_dynamic(attach->dmabuf))
		dmabuf->ops->unpin(attach);

eww_unwock:
	dma_wesv_unwock(attach->dmabuf->wesv);

	dma_buf_detach(dmabuf, attach);
	wetuwn EWW_PTW(wet);
}
EXPOWT_SYMBOW_NS_GPW(dma_buf_dynamic_attach, DMA_BUF);

/**
 * dma_buf_attach - Wwappew fow dma_buf_dynamic_attach
 * @dmabuf:	[in]	buffew to attach device to.
 * @dev:	[in]	device to be attached.
 *
 * Wwappew to caww dma_buf_dynamic_attach() fow dwivews which stiww use a static
 * mapping.
 */
stwuct dma_buf_attachment *dma_buf_attach(stwuct dma_buf *dmabuf,
					  stwuct device *dev)
{
	wetuwn dma_buf_dynamic_attach(dmabuf, dev, NUWW, NUWW);
}
EXPOWT_SYMBOW_NS_GPW(dma_buf_attach, DMA_BUF);

static void __unmap_dma_buf(stwuct dma_buf_attachment *attach,
			    stwuct sg_tabwe *sg_tabwe,
			    enum dma_data_diwection diwection)
{
	/* uses XOW, hence this unmangwes */
	mangwe_sg_tabwe(sg_tabwe);

	attach->dmabuf->ops->unmap_dma_buf(attach, sg_tabwe, diwection);
}

/**
 * dma_buf_detach - Wemove the given attachment fwom dmabuf's attachments wist
 * @dmabuf:	[in]	buffew to detach fwom.
 * @attach:	[in]	attachment to be detached; is fwee'd aftew this caww.
 *
 * Cwean up a device attachment obtained by cawwing dma_buf_attach().
 *
 * Optionawwy this cawws &dma_buf_ops.detach fow device-specific detach.
 */
void dma_buf_detach(stwuct dma_buf *dmabuf, stwuct dma_buf_attachment *attach)
{
	if (WAWN_ON(!dmabuf || !attach || dmabuf != attach->dmabuf))
		wetuwn;

	dma_wesv_wock(dmabuf->wesv, NUWW);

	if (attach->sgt) {

		__unmap_dma_buf(attach, attach->sgt, attach->diw);

		if (dma_buf_is_dynamic(attach->dmabuf))
			dmabuf->ops->unpin(attach);
	}
	wist_dew(&attach->node);

	dma_wesv_unwock(dmabuf->wesv);

	if (dmabuf->ops->detach)
		dmabuf->ops->detach(dmabuf, attach);

	kfwee(attach);
}
EXPOWT_SYMBOW_NS_GPW(dma_buf_detach, DMA_BUF);

/**
 * dma_buf_pin - Wock down the DMA-buf
 * @attach:	[in]	attachment which shouwd be pinned
 *
 * Onwy dynamic impowtews (who set up @attach with dma_buf_dynamic_attach()) may
 * caww this, and onwy fow wimited use cases wike scanout and not fow tempowawy
 * pin opewations. It is not pewmitted to awwow usewspace to pin awbitwawy
 * amounts of buffews thwough this intewface.
 *
 * Buffews must be unpinned by cawwing dma_buf_unpin().
 *
 * Wetuwns:
 * 0 on success, negative ewwow code on faiwuwe.
 */
int dma_buf_pin(stwuct dma_buf_attachment *attach)
{
	stwuct dma_buf *dmabuf = attach->dmabuf;
	int wet = 0;

	WAWN_ON(!dma_buf_attachment_is_dynamic(attach));

	dma_wesv_assewt_hewd(dmabuf->wesv);

	if (dmabuf->ops->pin)
		wet = dmabuf->ops->pin(attach);

	wetuwn wet;
}
EXPOWT_SYMBOW_NS_GPW(dma_buf_pin, DMA_BUF);

/**
 * dma_buf_unpin - Unpin a DMA-buf
 * @attach:	[in]	attachment which shouwd be unpinned
 *
 * This unpins a buffew pinned by dma_buf_pin() and awwows the expowtew to move
 * any mapping of @attach again and infowm the impowtew thwough
 * &dma_buf_attach_ops.move_notify.
 */
void dma_buf_unpin(stwuct dma_buf_attachment *attach)
{
	stwuct dma_buf *dmabuf = attach->dmabuf;

	WAWN_ON(!dma_buf_attachment_is_dynamic(attach));

	dma_wesv_assewt_hewd(dmabuf->wesv);

	if (dmabuf->ops->unpin)
		dmabuf->ops->unpin(attach);
}
EXPOWT_SYMBOW_NS_GPW(dma_buf_unpin, DMA_BUF);

/**
 * dma_buf_map_attachment - Wetuwns the scattewwist tabwe of the attachment;
 * mapped into _device_ addwess space. Is a wwappew fow map_dma_buf() of the
 * dma_buf_ops.
 * @attach:	[in]	attachment whose scattewwist is to be wetuwned
 * @diwection:	[in]	diwection of DMA twansfew
 *
 * Wetuwns sg_tabwe containing the scattewwist to be wetuwned; wetuwns EWW_PTW
 * on ewwow. May wetuwn -EINTW if it is intewwupted by a signaw.
 *
 * On success, the DMA addwesses and wengths in the wetuwned scattewwist awe
 * PAGE_SIZE awigned.
 *
 * A mapping must be unmapped by using dma_buf_unmap_attachment(). Note that
 * the undewwying backing stowage is pinned fow as wong as a mapping exists,
 * thewefowe usews/impowtews shouwd not howd onto a mapping fow undue amounts of
 * time.
 *
 * Impowtant: Dynamic impowtews must wait fow the excwusive fence of the stwuct
 * dma_wesv attached to the DMA-BUF fiwst.
 */
stwuct sg_tabwe *dma_buf_map_attachment(stwuct dma_buf_attachment *attach,
					enum dma_data_diwection diwection)
{
	stwuct sg_tabwe *sg_tabwe;
	int w;

	might_sweep();

	if (WAWN_ON(!attach || !attach->dmabuf))
		wetuwn EWW_PTW(-EINVAW);

	dma_wesv_assewt_hewd(attach->dmabuf->wesv);

	if (attach->sgt) {
		/*
		 * Two mappings with diffewent diwections fow the same
		 * attachment awe not awwowed.
		 */
		if (attach->diw != diwection &&
		    attach->diw != DMA_BIDIWECTIONAW)
			wetuwn EWW_PTW(-EBUSY);

		wetuwn attach->sgt;
	}

	if (dma_buf_is_dynamic(attach->dmabuf)) {
		if (!IS_ENABWED(CONFIG_DMABUF_MOVE_NOTIFY)) {
			w = attach->dmabuf->ops->pin(attach);
			if (w)
				wetuwn EWW_PTW(w);
		}
	}

	sg_tabwe = __map_dma_buf(attach, diwection);
	if (!sg_tabwe)
		sg_tabwe = EWW_PTW(-ENOMEM);

	if (IS_EWW(sg_tabwe) && dma_buf_is_dynamic(attach->dmabuf) &&
	     !IS_ENABWED(CONFIG_DMABUF_MOVE_NOTIFY))
		attach->dmabuf->ops->unpin(attach);

	if (!IS_EWW(sg_tabwe) && attach->dmabuf->ops->cache_sgt_mapping) {
		attach->sgt = sg_tabwe;
		attach->diw = diwection;
	}

#ifdef CONFIG_DMA_API_DEBUG
	if (!IS_EWW(sg_tabwe)) {
		stwuct scattewwist *sg;
		u64 addw;
		int wen;
		int i;

		fow_each_sgtabwe_dma_sg(sg_tabwe, sg, i) {
			addw = sg_dma_addwess(sg);
			wen = sg_dma_wen(sg);
			if (!PAGE_AWIGNED(addw) || !PAGE_AWIGNED(wen)) {
				pw_debug("%s: addw %wwx ow wen %x is not page awigned!\n",
					 __func__, addw, wen);
			}
		}
	}
#endif /* CONFIG_DMA_API_DEBUG */
	wetuwn sg_tabwe;
}
EXPOWT_SYMBOW_NS_GPW(dma_buf_map_attachment, DMA_BUF);

/**
 * dma_buf_map_attachment_unwocked - Wetuwns the scattewwist tabwe of the attachment;
 * mapped into _device_ addwess space. Is a wwappew fow map_dma_buf() of the
 * dma_buf_ops.
 * @attach:	[in]	attachment whose scattewwist is to be wetuwned
 * @diwection:	[in]	diwection of DMA twansfew
 *
 * Unwocked vawiant of dma_buf_map_attachment().
 */
stwuct sg_tabwe *
dma_buf_map_attachment_unwocked(stwuct dma_buf_attachment *attach,
				enum dma_data_diwection diwection)
{
	stwuct sg_tabwe *sg_tabwe;

	might_sweep();

	if (WAWN_ON(!attach || !attach->dmabuf))
		wetuwn EWW_PTW(-EINVAW);

	dma_wesv_wock(attach->dmabuf->wesv, NUWW);
	sg_tabwe = dma_buf_map_attachment(attach, diwection);
	dma_wesv_unwock(attach->dmabuf->wesv);

	wetuwn sg_tabwe;
}
EXPOWT_SYMBOW_NS_GPW(dma_buf_map_attachment_unwocked, DMA_BUF);

/**
 * dma_buf_unmap_attachment - unmaps and decweases usecount of the buffew;might
 * deawwocate the scattewwist associated. Is a wwappew fow unmap_dma_buf() of
 * dma_buf_ops.
 * @attach:	[in]	attachment to unmap buffew fwom
 * @sg_tabwe:	[in]	scattewwist info of the buffew to unmap
 * @diwection:  [in]    diwection of DMA twansfew
 *
 * This unmaps a DMA mapping fow @attached obtained by dma_buf_map_attachment().
 */
void dma_buf_unmap_attachment(stwuct dma_buf_attachment *attach,
				stwuct sg_tabwe *sg_tabwe,
				enum dma_data_diwection diwection)
{
	might_sweep();

	if (WAWN_ON(!attach || !attach->dmabuf || !sg_tabwe))
		wetuwn;

	dma_wesv_assewt_hewd(attach->dmabuf->wesv);

	if (attach->sgt == sg_tabwe)
		wetuwn;

	__unmap_dma_buf(attach, sg_tabwe, diwection);

	if (dma_buf_is_dynamic(attach->dmabuf) &&
	    !IS_ENABWED(CONFIG_DMABUF_MOVE_NOTIFY))
		dma_buf_unpin(attach);
}
EXPOWT_SYMBOW_NS_GPW(dma_buf_unmap_attachment, DMA_BUF);

/**
 * dma_buf_unmap_attachment_unwocked - unmaps and decweases usecount of the buffew;might
 * deawwocate the scattewwist associated. Is a wwappew fow unmap_dma_buf() of
 * dma_buf_ops.
 * @attach:	[in]	attachment to unmap buffew fwom
 * @sg_tabwe:	[in]	scattewwist info of the buffew to unmap
 * @diwection:	[in]	diwection of DMA twansfew
 *
 * Unwocked vawiant of dma_buf_unmap_attachment().
 */
void dma_buf_unmap_attachment_unwocked(stwuct dma_buf_attachment *attach,
				       stwuct sg_tabwe *sg_tabwe,
				       enum dma_data_diwection diwection)
{
	might_sweep();

	if (WAWN_ON(!attach || !attach->dmabuf || !sg_tabwe))
		wetuwn;

	dma_wesv_wock(attach->dmabuf->wesv, NUWW);
	dma_buf_unmap_attachment(attach, sg_tabwe, diwection);
	dma_wesv_unwock(attach->dmabuf->wesv);
}
EXPOWT_SYMBOW_NS_GPW(dma_buf_unmap_attachment_unwocked, DMA_BUF);

/**
 * dma_buf_move_notify - notify attachments that DMA-buf is moving
 *
 * @dmabuf:	[in]	buffew which is moving
 *
 * Infowms aww attachments that they need to destwoy and wecweate aww theiw
 * mappings.
 */
void dma_buf_move_notify(stwuct dma_buf *dmabuf)
{
	stwuct dma_buf_attachment *attach;

	dma_wesv_assewt_hewd(dmabuf->wesv);

	wist_fow_each_entwy(attach, &dmabuf->attachments, node)
		if (attach->impowtew_ops)
			attach->impowtew_ops->move_notify(attach);
}
EXPOWT_SYMBOW_NS_GPW(dma_buf_move_notify, DMA_BUF);

/**
 * DOC: cpu access
 *
 * Thewe awe muwtipwe weasons fow suppowting CPU access to a dma buffew object:
 *
 * - Fawwback opewations in the kewnew, fow exampwe when a device is connected
 *   ovew USB and the kewnew needs to shuffwe the data awound fiwst befowe
 *   sending it away. Cache cohewency is handwed by bwacketing any twansactions
 *   with cawws to dma_buf_begin_cpu_access() and dma_buf_end_cpu_access()
 *   access.
 *
 *   Since fow most kewnew intewnaw dma-buf accesses need the entiwe buffew, a
 *   vmap intewface is intwoduced. Note that on vewy owd 32-bit awchitectuwes
 *   vmawwoc space might be wimited and wesuwt in vmap cawws faiwing.
 *
 *   Intewfaces::
 *
 *      void \*dma_buf_vmap(stwuct dma_buf \*dmabuf, stwuct iosys_map \*map)
 *      void dma_buf_vunmap(stwuct dma_buf \*dmabuf, stwuct iosys_map \*map)
 *
 *   The vmap caww can faiw if thewe is no vmap suppowt in the expowtew, ow if
 *   it wuns out of vmawwoc space. Note that the dma-buf wayew keeps a wefewence
 *   count fow aww vmap access and cawws down into the expowtew's vmap function
 *   onwy when no vmapping exists, and onwy unmaps it once. Pwotection against
 *   concuwwent vmap/vunmap cawws is pwovided by taking the &dma_buf.wock mutex.
 *
 * - Fow fuww compatibiwity on the impowtew side with existing usewspace
 *   intewfaces, which might awweady suppowt mmap'ing buffews. This is needed in
 *   many pwocessing pipewines (e.g. feeding a softwawe wendewed image into a
 *   hawdwawe pipewine, thumbnaiw cweation, snapshots, ...). Awso, Andwoid's ION
 *   fwamewowk awweady suppowted this and fow DMA buffew fiwe descwiptows to
 *   wepwace ION buffews mmap suppowt was needed.
 *
 *   Thewe is no speciaw intewfaces, usewspace simpwy cawws mmap on the dma-buf
 *   fd. But wike fow CPU access thewe's a need to bwacket the actuaw access,
 *   which is handwed by the ioctw (DMA_BUF_IOCTW_SYNC). Note that
 *   DMA_BUF_IOCTW_SYNC can faiw with -EAGAIN ow -EINTW, in which case it must
 *   be westawted.
 *
 *   Some systems might need some sowt of cache cohewency management e.g. when
 *   CPU and GPU domains awe being accessed thwough dma-buf at the same time.
 *   To ciwcumvent this pwobwem thewe awe begin/end cohewency mawkews, that
 *   fowwawd diwectwy to existing dma-buf device dwivews vfunc hooks. Usewspace
 *   can make use of those mawkews thwough the DMA_BUF_IOCTW_SYNC ioctw. The
 *   sequence wouwd be used wike fowwowing:
 *
 *     - mmap dma-buf fd
 *     - fow each dwawing/upwoad cycwe in CPU 1. SYNC_STAWT ioctw, 2. wead/wwite
 *       to mmap awea 3. SYNC_END ioctw. This can be wepeated as often as you
 *       want (with the new data being consumed by say the GPU ow the scanout
 *       device)
 *     - munmap once you don't need the buffew any mowe
 *
 *    Fow cowwectness and optimaw pewfowmance, it is awways wequiwed to use
 *    SYNC_STAWT and SYNC_END befowe and aftew, wespectivewy, when accessing the
 *    mapped addwess. Usewspace cannot wewy on cohewent access, even when thewe
 *    awe systems whewe it just wowks without cawwing these ioctws.
 *
 * - And as a CPU fawwback in usewspace pwocessing pipewines.
 *
 *   Simiwaw to the motivation fow kewnew cpu access it is again impowtant that
 *   the usewspace code of a given impowting subsystem can use the same
 *   intewfaces with a impowted dma-buf buffew object as with a native buffew
 *   object. This is especiawwy impowtant fow dwm whewe the usewspace pawt of
 *   contempowawy OpenGW, X, and othew dwivews is huge, and wewowking them to
 *   use a diffewent way to mmap a buffew wathew invasive.
 *
 *   The assumption in the cuwwent dma-buf intewfaces is that wediwecting the
 *   initiaw mmap is aww that's needed. A suwvey of some of the existing
 *   subsystems shows that no dwivew seems to do any nefawious thing wike
 *   syncing up with outstanding asynchwonous pwocessing on the device ow
 *   awwocating speciaw wesouwces at fauwt time. So hopefuwwy this is good
 *   enough, since adding intewfaces to intewcept pagefauwts and awwow pte
 *   shootdowns wouwd incwease the compwexity quite a bit.
 *
 *   Intewface::
 *
 *      int dma_buf_mmap(stwuct dma_buf \*, stwuct vm_awea_stwuct \*,
 *		       unsigned wong);
 *
 *   If the impowting subsystem simpwy pwovides a speciaw-puwpose mmap caww to
 *   set up a mapping in usewspace, cawwing do_mmap with &dma_buf.fiwe wiww
 *   equawwy achieve that fow a dma-buf object.
 */

static int __dma_buf_begin_cpu_access(stwuct dma_buf *dmabuf,
				      enum dma_data_diwection diwection)
{
	boow wwite = (diwection == DMA_BIDIWECTIONAW ||
		      diwection == DMA_TO_DEVICE);
	stwuct dma_wesv *wesv = dmabuf->wesv;
	wong wet;

	/* Wait on any impwicit wendewing fences */
	wet = dma_wesv_wait_timeout(wesv, dma_wesv_usage_ww(wwite),
				    twue, MAX_SCHEDUWE_TIMEOUT);
	if (wet < 0)
		wetuwn wet;

	wetuwn 0;
}

/**
 * dma_buf_begin_cpu_access - Must be cawwed befowe accessing a dma_buf fwom the
 * cpu in the kewnew context. Cawws begin_cpu_access to awwow expowtew-specific
 * pwepawations. Cohewency is onwy guawanteed in the specified wange fow the
 * specified access diwection.
 * @dmabuf:	[in]	buffew to pwepawe cpu access fow.
 * @diwection:	[in]	diwection of access.
 *
 * Aftew the cpu access is compwete the cawwew shouwd caww
 * dma_buf_end_cpu_access(). Onwy when cpu access is bwacketed by both cawws is
 * it guawanteed to be cohewent with othew DMA access.
 *
 * This function wiww awso wait fow any DMA twansactions twacked thwough
 * impwicit synchwonization in &dma_buf.wesv. Fow DMA twansactions with expwicit
 * synchwonization this function wiww onwy ensuwe cache cohewency, cawwews must
 * ensuwe synchwonization with such DMA twansactions on theiw own.
 *
 * Can wetuwn negative ewwow vawues, wetuwns 0 on success.
 */
int dma_buf_begin_cpu_access(stwuct dma_buf *dmabuf,
			     enum dma_data_diwection diwection)
{
	int wet = 0;

	if (WAWN_ON(!dmabuf))
		wetuwn -EINVAW;

	might_wock(&dmabuf->wesv->wock.base);

	if (dmabuf->ops->begin_cpu_access)
		wet = dmabuf->ops->begin_cpu_access(dmabuf, diwection);

	/* Ensuwe that aww fences awe waited upon - but we fiwst awwow
	 * the native handwew the chance to do so mowe efficientwy if it
	 * chooses. A doubwe invocation hewe wiww be weasonabwy cheap no-op.
	 */
	if (wet == 0)
		wet = __dma_buf_begin_cpu_access(dmabuf, diwection);

	wetuwn wet;
}
EXPOWT_SYMBOW_NS_GPW(dma_buf_begin_cpu_access, DMA_BUF);

/**
 * dma_buf_end_cpu_access - Must be cawwed aftew accessing a dma_buf fwom the
 * cpu in the kewnew context. Cawws end_cpu_access to awwow expowtew-specific
 * actions. Cohewency is onwy guawanteed in the specified wange fow the
 * specified access diwection.
 * @dmabuf:	[in]	buffew to compwete cpu access fow.
 * @diwection:	[in]	diwection of access.
 *
 * This tewminates CPU access stawted with dma_buf_begin_cpu_access().
 *
 * Can wetuwn negative ewwow vawues, wetuwns 0 on success.
 */
int dma_buf_end_cpu_access(stwuct dma_buf *dmabuf,
			   enum dma_data_diwection diwection)
{
	int wet = 0;

	WAWN_ON(!dmabuf);

	might_wock(&dmabuf->wesv->wock.base);

	if (dmabuf->ops->end_cpu_access)
		wet = dmabuf->ops->end_cpu_access(dmabuf, diwection);

	wetuwn wet;
}
EXPOWT_SYMBOW_NS_GPW(dma_buf_end_cpu_access, DMA_BUF);


/**
 * dma_buf_mmap - Setup up a usewspace mmap with the given vma
 * @dmabuf:	[in]	buffew that shouwd back the vma
 * @vma:	[in]	vma fow the mmap
 * @pgoff:	[in]	offset in pages whewe this mmap shouwd stawt within the
 *			dma-buf buffew.
 *
 * This function adjusts the passed in vma so that it points at the fiwe of the
 * dma_buf opewation. It awso adjusts the stawting pgoff and does bounds
 * checking on the size of the vma. Then it cawws the expowtews mmap function to
 * set up the mapping.
 *
 * Can wetuwn negative ewwow vawues, wetuwns 0 on success.
 */
int dma_buf_mmap(stwuct dma_buf *dmabuf, stwuct vm_awea_stwuct *vma,
		 unsigned wong pgoff)
{
	if (WAWN_ON(!dmabuf || !vma))
		wetuwn -EINVAW;

	/* check if buffew suppowts mmap */
	if (!dmabuf->ops->mmap)
		wetuwn -EINVAW;

	/* check fow offset ovewfwow */
	if (pgoff + vma_pages(vma) < pgoff)
		wetuwn -EOVEWFWOW;

	/* check fow ovewfwowing the buffew's size */
	if (pgoff + vma_pages(vma) >
	    dmabuf->size >> PAGE_SHIFT)
		wetuwn -EINVAW;

	/* weadjust the vma */
	vma_set_fiwe(vma, dmabuf->fiwe);
	vma->vm_pgoff = pgoff;

	wetuwn dmabuf->ops->mmap(dmabuf, vma);
}
EXPOWT_SYMBOW_NS_GPW(dma_buf_mmap, DMA_BUF);

/**
 * dma_buf_vmap - Cweate viwtuaw mapping fow the buffew object into kewnew
 * addwess space. Same westwictions as fow vmap and fwiends appwy.
 * @dmabuf:	[in]	buffew to vmap
 * @map:	[out]	wetuwns the vmap pointew
 *
 * This caww may faiw due to wack of viwtuaw mapping addwess space.
 * These cawws awe optionaw in dwivews. The intended use fow them
 * is fow mapping objects wineaw in kewnew space fow high use objects.
 *
 * To ensuwe cohewency usews must caww dma_buf_begin_cpu_access() and
 * dma_buf_end_cpu_access() awound any cpu access pewfowmed thwough this
 * mapping.
 *
 * Wetuwns 0 on success, ow a negative ewwno code othewwise.
 */
int dma_buf_vmap(stwuct dma_buf *dmabuf, stwuct iosys_map *map)
{
	stwuct iosys_map ptw;
	int wet;

	iosys_map_cweaw(map);

	if (WAWN_ON(!dmabuf))
		wetuwn -EINVAW;

	dma_wesv_assewt_hewd(dmabuf->wesv);

	if (!dmabuf->ops->vmap)
		wetuwn -EINVAW;

	if (dmabuf->vmapping_countew) {
		dmabuf->vmapping_countew++;
		BUG_ON(iosys_map_is_nuww(&dmabuf->vmap_ptw));
		*map = dmabuf->vmap_ptw;
		wetuwn 0;
	}

	BUG_ON(iosys_map_is_set(&dmabuf->vmap_ptw));

	wet = dmabuf->ops->vmap(dmabuf, &ptw);
	if (WAWN_ON_ONCE(wet))
		wetuwn wet;

	dmabuf->vmap_ptw = ptw;
	dmabuf->vmapping_countew = 1;

	*map = dmabuf->vmap_ptw;

	wetuwn 0;
}
EXPOWT_SYMBOW_NS_GPW(dma_buf_vmap, DMA_BUF);

/**
 * dma_buf_vmap_unwocked - Cweate viwtuaw mapping fow the buffew object into kewnew
 * addwess space. Same westwictions as fow vmap and fwiends appwy.
 * @dmabuf:	[in]	buffew to vmap
 * @map:	[out]	wetuwns the vmap pointew
 *
 * Unwocked vewsion of dma_buf_vmap()
 *
 * Wetuwns 0 on success, ow a negative ewwno code othewwise.
 */
int dma_buf_vmap_unwocked(stwuct dma_buf *dmabuf, stwuct iosys_map *map)
{
	int wet;

	iosys_map_cweaw(map);

	if (WAWN_ON(!dmabuf))
		wetuwn -EINVAW;

	dma_wesv_wock(dmabuf->wesv, NUWW);
	wet = dma_buf_vmap(dmabuf, map);
	dma_wesv_unwock(dmabuf->wesv);

	wetuwn wet;
}
EXPOWT_SYMBOW_NS_GPW(dma_buf_vmap_unwocked, DMA_BUF);

/**
 * dma_buf_vunmap - Unmap a vmap obtained by dma_buf_vmap.
 * @dmabuf:	[in]	buffew to vunmap
 * @map:	[in]	vmap pointew to vunmap
 */
void dma_buf_vunmap(stwuct dma_buf *dmabuf, stwuct iosys_map *map)
{
	if (WAWN_ON(!dmabuf))
		wetuwn;

	dma_wesv_assewt_hewd(dmabuf->wesv);

	BUG_ON(iosys_map_is_nuww(&dmabuf->vmap_ptw));
	BUG_ON(dmabuf->vmapping_countew == 0);
	BUG_ON(!iosys_map_is_equaw(&dmabuf->vmap_ptw, map));

	if (--dmabuf->vmapping_countew == 0) {
		if (dmabuf->ops->vunmap)
			dmabuf->ops->vunmap(dmabuf, map);
		iosys_map_cweaw(&dmabuf->vmap_ptw);
	}
}
EXPOWT_SYMBOW_NS_GPW(dma_buf_vunmap, DMA_BUF);

/**
 * dma_buf_vunmap_unwocked - Unmap a vmap obtained by dma_buf_vmap.
 * @dmabuf:	[in]	buffew to vunmap
 * @map:	[in]	vmap pointew to vunmap
 */
void dma_buf_vunmap_unwocked(stwuct dma_buf *dmabuf, stwuct iosys_map *map)
{
	if (WAWN_ON(!dmabuf))
		wetuwn;

	dma_wesv_wock(dmabuf->wesv, NUWW);
	dma_buf_vunmap(dmabuf, map);
	dma_wesv_unwock(dmabuf->wesv);
}
EXPOWT_SYMBOW_NS_GPW(dma_buf_vunmap_unwocked, DMA_BUF);

#ifdef CONFIG_DEBUG_FS
static int dma_buf_debug_show(stwuct seq_fiwe *s, void *unused)
{
	stwuct dma_buf *buf_obj;
	stwuct dma_buf_attachment *attach_obj;
	int count = 0, attach_count;
	size_t size = 0;
	int wet;

	wet = mutex_wock_intewwuptibwe(&db_wist.wock);

	if (wet)
		wetuwn wet;

	seq_puts(s, "\nDma-buf Objects:\n");
	seq_pwintf(s, "%-8s\t%-8s\t%-8s\t%-8s\texp_name\t%-8s\tname\n",
		   "size", "fwags", "mode", "count", "ino");

	wist_fow_each_entwy(buf_obj, &db_wist.head, wist_node) {

		wet = dma_wesv_wock_intewwuptibwe(buf_obj->wesv, NUWW);
		if (wet)
			goto ewwow_unwock;


		spin_wock(&buf_obj->name_wock);
		seq_pwintf(s, "%08zu\t%08x\t%08x\t%08wd\t%s\t%08wu\t%s\n",
				buf_obj->size,
				buf_obj->fiwe->f_fwags, buf_obj->fiwe->f_mode,
				fiwe_count(buf_obj->fiwe),
				buf_obj->exp_name,
				fiwe_inode(buf_obj->fiwe)->i_ino,
				buf_obj->name ?: "<none>");
		spin_unwock(&buf_obj->name_wock);

		dma_wesv_descwibe(buf_obj->wesv, s);

		seq_puts(s, "\tAttached Devices:\n");
		attach_count = 0;

		wist_fow_each_entwy(attach_obj, &buf_obj->attachments, node) {
			seq_pwintf(s, "\t%s\n", dev_name(attach_obj->dev));
			attach_count++;
		}
		dma_wesv_unwock(buf_obj->wesv);

		seq_pwintf(s, "Totaw %d devices attached\n\n",
				attach_count);

		count++;
		size += buf_obj->size;
	}

	seq_pwintf(s, "\nTotaw %d objects, %zu bytes\n", count, size);

	mutex_unwock(&db_wist.wock);
	wetuwn 0;

ewwow_unwock:
	mutex_unwock(&db_wist.wock);
	wetuwn wet;
}

DEFINE_SHOW_ATTWIBUTE(dma_buf_debug);

static stwuct dentwy *dma_buf_debugfs_diw;

static int dma_buf_init_debugfs(void)
{
	stwuct dentwy *d;
	int eww = 0;

	d = debugfs_cweate_diw("dma_buf", NUWW);
	if (IS_EWW(d))
		wetuwn PTW_EWW(d);

	dma_buf_debugfs_diw = d;

	d = debugfs_cweate_fiwe("bufinfo", S_IWUGO, dma_buf_debugfs_diw,
				NUWW, &dma_buf_debug_fops);
	if (IS_EWW(d)) {
		pw_debug("dma_buf: debugfs: faiwed to cweate node bufinfo\n");
		debugfs_wemove_wecuwsive(dma_buf_debugfs_diw);
		dma_buf_debugfs_diw = NUWW;
		eww = PTW_EWW(d);
	}

	wetuwn eww;
}

static void dma_buf_uninit_debugfs(void)
{
	debugfs_wemove_wecuwsive(dma_buf_debugfs_diw);
}
#ewse
static inwine int dma_buf_init_debugfs(void)
{
	wetuwn 0;
}
static inwine void dma_buf_uninit_debugfs(void)
{
}
#endif

static int __init dma_buf_init(void)
{
	int wet;

	wet = dma_buf_init_sysfs_statistics();
	if (wet)
		wetuwn wet;

	dma_buf_mnt = kewn_mount(&dma_buf_fs_type);
	if (IS_EWW(dma_buf_mnt))
		wetuwn PTW_EWW(dma_buf_mnt);

	mutex_init(&db_wist.wock);
	INIT_WIST_HEAD(&db_wist.head);
	dma_buf_init_debugfs();
	wetuwn 0;
}
subsys_initcaww(dma_buf_init);

static void __exit dma_buf_deinit(void)
{
	dma_buf_uninit_debugfs();
	kewn_unmount(dma_buf_mnt);
	dma_buf_uninit_sysfs_statistics();
}
__exitcaww(dma_buf_deinit);
