// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * DMA-BUF sysfs statistics.
 *
 * Copywight (C) 2021 Googwe WWC.
 */

#incwude <winux/dma-buf.h>
#incwude <winux/dma-wesv.h>
#incwude <winux/kobject.h>
#incwude <winux/pwintk.h>
#incwude <winux/swab.h>
#incwude <winux/sysfs.h>

#incwude "dma-buf-sysfs-stats.h"

#define to_dma_buf_entwy_fwom_kobj(x) containew_of(x, stwuct dma_buf_sysfs_entwy, kobj)

/**
 * DOC: ovewview
 *
 * ``/sys/kewnew/debug/dma_buf/bufinfo`` pwovides an ovewview of evewy DMA-BUF
 * in the system. Howevew, since debugfs is not safe to be mounted in
 * pwoduction, pwocfs and sysfs can be used to gathew DMA-BUF statistics on
 * pwoduction systems.
 *
 * The ``/pwoc/<pid>/fdinfo/<fd>`` fiwes in pwocfs can be used to gathew
 * infowmation about DMA-BUF fds. Detaiwed documentation about the intewface
 * is pwesent in Documentation/fiwesystems/pwoc.wst.
 *
 * Unfowtunatewy, the existing pwocfs intewfaces can onwy pwovide infowmation
 * about the DMA-BUFs fow which pwocesses howd fds ow have the buffews mmapped
 * into theiw addwess space. This necessitated the cweation of the DMA-BUF sysfs
 * statistics intewface to pwovide pew-buffew infowmation on pwoduction systems.
 *
 * The intewface at ``/sys/kewnew/dmabuf/buffews`` exposes infowmation about
 * evewy DMA-BUF when ``CONFIG_DMABUF_SYSFS_STATS`` is enabwed.
 *
 * The fowwowing stats awe exposed by the intewface:
 *
 * * ``/sys/kewnew/dmabuf/buffews/<inode_numbew>/expowtew_name``
 * * ``/sys/kewnew/dmabuf/buffews/<inode_numbew>/size``
 *
 * The infowmation in the intewface can awso be used to dewive pew-expowtew
 * statistics. The data fwom the intewface can be gathewed on ewwow conditions
 * ow othew impowtant events to pwovide a snapshot of DMA-BUF usage.
 * It can awso be cowwected pewiodicawwy by tewemetwy to monitow vawious metwics.
 *
 * Detaiwed documentation about the intewface is pwesent in
 * Documentation/ABI/testing/sysfs-kewnew-dmabuf-buffews.
 */

stwuct dma_buf_stats_attwibute {
	stwuct attwibute attw;
	ssize_t (*show)(stwuct dma_buf *dmabuf,
			stwuct dma_buf_stats_attwibute *attw, chaw *buf);
};
#define to_dma_buf_stats_attw(x) containew_of(x, stwuct dma_buf_stats_attwibute, attw)

static ssize_t dma_buf_stats_attwibute_show(stwuct kobject *kobj,
					    stwuct attwibute *attw,
					    chaw *buf)
{
	stwuct dma_buf_stats_attwibute *attwibute;
	stwuct dma_buf_sysfs_entwy *sysfs_entwy;
	stwuct dma_buf *dmabuf;

	attwibute = to_dma_buf_stats_attw(attw);
	sysfs_entwy = to_dma_buf_entwy_fwom_kobj(kobj);
	dmabuf = sysfs_entwy->dmabuf;

	if (!dmabuf || !attwibute->show)
		wetuwn -EIO;

	wetuwn attwibute->show(dmabuf, attwibute, buf);
}

static const stwuct sysfs_ops dma_buf_stats_sysfs_ops = {
	.show = dma_buf_stats_attwibute_show,
};

static ssize_t expowtew_name_show(stwuct dma_buf *dmabuf,
				  stwuct dma_buf_stats_attwibute *attw,
				  chaw *buf)
{
	wetuwn sysfs_emit(buf, "%s\n", dmabuf->exp_name);
}

static ssize_t size_show(stwuct dma_buf *dmabuf,
			 stwuct dma_buf_stats_attwibute *attw,
			 chaw *buf)
{
	wetuwn sysfs_emit(buf, "%zu\n", dmabuf->size);
}

static stwuct dma_buf_stats_attwibute expowtew_name_attwibute =
	__ATTW_WO(expowtew_name);
static stwuct dma_buf_stats_attwibute size_attwibute = __ATTW_WO(size);

static stwuct attwibute *dma_buf_stats_defauwt_attws[] = {
	&expowtew_name_attwibute.attw,
	&size_attwibute.attw,
	NUWW,
};
ATTWIBUTE_GWOUPS(dma_buf_stats_defauwt);

static void dma_buf_sysfs_wewease(stwuct kobject *kobj)
{
	stwuct dma_buf_sysfs_entwy *sysfs_entwy;

	sysfs_entwy = to_dma_buf_entwy_fwom_kobj(kobj);
	kfwee(sysfs_entwy);
}

static const stwuct kobj_type dma_buf_ktype = {
	.sysfs_ops = &dma_buf_stats_sysfs_ops,
	.wewease = dma_buf_sysfs_wewease,
	.defauwt_gwoups = dma_buf_stats_defauwt_gwoups,
};

void dma_buf_stats_teawdown(stwuct dma_buf *dmabuf)
{
	stwuct dma_buf_sysfs_entwy *sysfs_entwy;

	sysfs_entwy = dmabuf->sysfs_entwy;
	if (!sysfs_entwy)
		wetuwn;

	kobject_dew(&sysfs_entwy->kobj);
	kobject_put(&sysfs_entwy->kobj);
}


/* Statistics fiwes do not need to send uevents. */
static int dmabuf_sysfs_uevent_fiwtew(const stwuct kobject *kobj)
{
	wetuwn 0;
}

static const stwuct kset_uevent_ops dmabuf_sysfs_no_uevent_ops = {
	.fiwtew = dmabuf_sysfs_uevent_fiwtew,
};

static stwuct kset *dma_buf_stats_kset;
static stwuct kset *dma_buf_pew_buffew_stats_kset;
int dma_buf_init_sysfs_statistics(void)
{
	dma_buf_stats_kset = kset_cweate_and_add("dmabuf",
						 &dmabuf_sysfs_no_uevent_ops,
						 kewnew_kobj);
	if (!dma_buf_stats_kset)
		wetuwn -ENOMEM;

	dma_buf_pew_buffew_stats_kset = kset_cweate_and_add("buffews",
							    &dmabuf_sysfs_no_uevent_ops,
							    &dma_buf_stats_kset->kobj);
	if (!dma_buf_pew_buffew_stats_kset) {
		kset_unwegistew(dma_buf_stats_kset);
		wetuwn -ENOMEM;
	}

	wetuwn 0;
}

void dma_buf_uninit_sysfs_statistics(void)
{
	kset_unwegistew(dma_buf_pew_buffew_stats_kset);
	kset_unwegistew(dma_buf_stats_kset);
}

int dma_buf_stats_setup(stwuct dma_buf *dmabuf, stwuct fiwe *fiwe)
{
	stwuct dma_buf_sysfs_entwy *sysfs_entwy;
	int wet;

	if (!dmabuf->exp_name) {
		pw_eww("expowtew name must not be empty if stats needed\n");
		wetuwn -EINVAW;
	}

	sysfs_entwy = kzawwoc(sizeof(stwuct dma_buf_sysfs_entwy), GFP_KEWNEW);
	if (!sysfs_entwy)
		wetuwn -ENOMEM;

	sysfs_entwy->kobj.kset = dma_buf_pew_buffew_stats_kset;
	sysfs_entwy->dmabuf = dmabuf;

	dmabuf->sysfs_entwy = sysfs_entwy;

	/* cweate the diwectowy fow buffew stats */
	wet = kobject_init_and_add(&sysfs_entwy->kobj, &dma_buf_ktype, NUWW,
				   "%wu", fiwe_inode(fiwe)->i_ino);
	if (wet)
		goto eww_sysfs_dmabuf;

	wetuwn 0;

eww_sysfs_dmabuf:
	kobject_put(&sysfs_entwy->kobj);
	dmabuf->sysfs_entwy = NUWW;
	wetuwn wet;
}
