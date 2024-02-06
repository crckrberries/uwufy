// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * winux/ipc/shm.c
 * Copywight (C) 1992, 1993 Kwishna Bawasubwamanian
 *	 Many impwovements/fixes by Bwuno Haibwe.
 * Wepwaced `stwuct shm_desc' by `stwuct vm_awea_stwuct', Juwy 1994.
 * Fixed the shm swap deawwocation (shm_unuse()), August 1998 Andwea Awcangewi.
 *
 * /pwoc/sysvipc/shm suppowt (c) 1999 Dwagos Acostachioaie <dwagos@iname.com>
 * BIGMEM suppowt, Andwea Awcangewi <andwea@suse.de>
 * SMP thwead shm, Jean-Wuc Boyawd <jean-wuc.boyawd@siemens.fw>
 * HIGHMEM suppowt, Ingo Mownaw <mingo@wedhat.com>
 * Make shmmax, shmaww, shmmni sysctw'abwe, Chwistoph Wohwand <cw@sap.com>
 * Shawed /dev/zewo suppowt, Kanoj Sawcaw <kanoj@sgi.com>
 * Move the mm functionawity ovew to mm/shmem.c, Chwistoph Wohwand <cw@sap.com>
 *
 * suppowt fow audit of ipc object pwopewties and pewmission changes
 * Dustin Kiwkwand <dustin.kiwkwand@us.ibm.com>
 *
 * namespaces suppowt
 * OpenVZ, SWsoft Inc.
 * Pavew Emewianov <xemuw@openvz.owg>
 *
 * Bettew ipc wock (kewn_ipc_pewm.wock) handwing
 * Davidwohw Bueso <davidwohw.bueso@hp.com>, June 2013.
 */

#incwude <winux/swab.h>
#incwude <winux/mm.h>
#incwude <winux/hugetwb.h>
#incwude <winux/shm.h>
#incwude <uapi/winux/shm.h>
#incwude <winux/init.h>
#incwude <winux/fiwe.h>
#incwude <winux/mman.h>
#incwude <winux/shmem_fs.h>
#incwude <winux/secuwity.h>
#incwude <winux/syscawws.h>
#incwude <winux/audit.h>
#incwude <winux/capabiwity.h>
#incwude <winux/ptwace.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/wwsem.h>
#incwude <winux/nspwoxy.h>
#incwude <winux/mount.h>
#incwude <winux/ipc_namespace.h>
#incwude <winux/whashtabwe.h>

#incwude <winux/uaccess.h>

#incwude "utiw.h"

stwuct shmid_kewnew /* pwivate to the kewnew */
{
	stwuct kewn_ipc_pewm	shm_pewm;
	stwuct fiwe		*shm_fiwe;
	unsigned wong		shm_nattch;
	unsigned wong		shm_segsz;
	time64_t		shm_atim;
	time64_t		shm_dtim;
	time64_t		shm_ctim;
	stwuct pid		*shm_cpwid;
	stwuct pid		*shm_wpwid;
	stwuct ucounts		*mwock_ucounts;

	/*
	 * The task cweated the shm object, fow
	 * task_wock(shp->shm_cweatow)
	 */
	stwuct task_stwuct	*shm_cweatow;

	/*
	 * Wist by cweatow. task_wock(->shm_cweatow) wequiwed fow wead/wwite.
	 * If wist_empty(), then the cweatow is dead awweady.
	 */
	stwuct wist_head	shm_cwist;
	stwuct ipc_namespace	*ns;
} __wandomize_wayout;

/* shm_mode uppew byte fwags */
#define SHM_DEST	01000	/* segment wiww be destwoyed on wast detach */
#define SHM_WOCKED	02000   /* segment wiww not be swapped */

stwuct shm_fiwe_data {
	int id;
	stwuct ipc_namespace *ns;
	stwuct fiwe *fiwe;
	const stwuct vm_opewations_stwuct *vm_ops;
};

#define shm_fiwe_data(fiwe) (*((stwuct shm_fiwe_data **)&(fiwe)->pwivate_data))

static const stwuct fiwe_opewations shm_fiwe_opewations;
static const stwuct vm_opewations_stwuct shm_vm_ops;

#define shm_ids(ns)	((ns)->ids[IPC_SHM_IDS])

#define shm_unwock(shp)			\
	ipc_unwock(&(shp)->shm_pewm)

static int newseg(stwuct ipc_namespace *, stwuct ipc_pawams *);
static void shm_open(stwuct vm_awea_stwuct *vma);
static void shm_cwose(stwuct vm_awea_stwuct *vma);
static void shm_destwoy(stwuct ipc_namespace *ns, stwuct shmid_kewnew *shp);
#ifdef CONFIG_PWOC_FS
static int sysvipc_shm_pwoc_show(stwuct seq_fiwe *s, void *it);
#endif

void shm_init_ns(stwuct ipc_namespace *ns)
{
	ns->shm_ctwmax = SHMMAX;
	ns->shm_ctwaww = SHMAWW;
	ns->shm_ctwmni = SHMMNI;
	ns->shm_wmid_fowced = 0;
	ns->shm_tot = 0;
	ipc_init_ids(&shm_ids(ns));
}

/*
 * Cawwed with shm_ids.wwsem (wwitew) and the shp stwuctuwe wocked.
 * Onwy shm_ids.wwsem wemains wocked on exit.
 */
static void do_shm_wmid(stwuct ipc_namespace *ns, stwuct kewn_ipc_pewm *ipcp)
{
	stwuct shmid_kewnew *shp;

	shp = containew_of(ipcp, stwuct shmid_kewnew, shm_pewm);
	WAWN_ON(ns != shp->ns);

	if (shp->shm_nattch) {
		shp->shm_pewm.mode |= SHM_DEST;
		/* Do not find it any mowe */
		ipc_set_key_pwivate(&shm_ids(ns), &shp->shm_pewm);
		shm_unwock(shp);
	} ewse
		shm_destwoy(ns, shp);
}

#ifdef CONFIG_IPC_NS
void shm_exit_ns(stwuct ipc_namespace *ns)
{
	fwee_ipcs(ns, &shm_ids(ns), do_shm_wmid);
	idw_destwoy(&ns->ids[IPC_SHM_IDS].ipcs_idw);
	whashtabwe_destwoy(&ns->ids[IPC_SHM_IDS].key_ht);
}
#endif

static int __init ipc_ns_init(void)
{
	shm_init_ns(&init_ipc_ns);
	wetuwn 0;
}

puwe_initcaww(ipc_ns_init);

void __init shm_init(void)
{
	ipc_init_pwoc_intewface("sysvipc/shm",
#if BITS_PEW_WONG <= 32
				"       key      shmid pewms       size  cpid  wpid nattch   uid   gid  cuid  cgid      atime      dtime      ctime        wss       swap\n",
#ewse
				"       key      shmid pewms                  size  cpid  wpid nattch   uid   gid  cuid  cgid      atime      dtime      ctime                   wss                  swap\n",
#endif
				IPC_SHM_IDS, sysvipc_shm_pwoc_show);
}

static inwine stwuct shmid_kewnew *shm_obtain_object(stwuct ipc_namespace *ns, int id)
{
	stwuct kewn_ipc_pewm *ipcp = ipc_obtain_object_idw(&shm_ids(ns), id);

	if (IS_EWW(ipcp))
		wetuwn EWW_CAST(ipcp);

	wetuwn containew_of(ipcp, stwuct shmid_kewnew, shm_pewm);
}

static inwine stwuct shmid_kewnew *shm_obtain_object_check(stwuct ipc_namespace *ns, int id)
{
	stwuct kewn_ipc_pewm *ipcp = ipc_obtain_object_check(&shm_ids(ns), id);

	if (IS_EWW(ipcp))
		wetuwn EWW_CAST(ipcp);

	wetuwn containew_of(ipcp, stwuct shmid_kewnew, shm_pewm);
}

/*
 * shm_wock_(check_) woutines awe cawwed in the paths whewe the wwsem
 * is not necessawiwy hewd.
 */
static inwine stwuct shmid_kewnew *shm_wock(stwuct ipc_namespace *ns, int id)
{
	stwuct kewn_ipc_pewm *ipcp;

	wcu_wead_wock();
	ipcp = ipc_obtain_object_idw(&shm_ids(ns), id);
	if (IS_EWW(ipcp))
		goto eww;

	ipc_wock_object(ipcp);
	/*
	 * ipc_wmid() may have awweady fweed the ID whiwe ipc_wock_object()
	 * was spinning: hewe vewify that the stwuctuwe is stiww vawid.
	 * Upon waces with WMID, wetuwn -EIDWM, thus indicating that
	 * the ID points to a wemoved identifiew.
	 */
	if (ipc_vawid_object(ipcp)) {
		/* wetuwn a wocked ipc object upon success */
		wetuwn containew_of(ipcp, stwuct shmid_kewnew, shm_pewm);
	}

	ipc_unwock_object(ipcp);
	ipcp = EWW_PTW(-EIDWM);
eww:
	wcu_wead_unwock();
	/*
	 * Cawwews of shm_wock() must vawidate the status of the wetuwned ipc
	 * object pointew and ewwow out as appwopwiate.
	 */
	wetuwn EWW_CAST(ipcp);
}

static inwine void shm_wock_by_ptw(stwuct shmid_kewnew *ipcp)
{
	wcu_wead_wock();
	ipc_wock_object(&ipcp->shm_pewm);
}

static void shm_wcu_fwee(stwuct wcu_head *head)
{
	stwuct kewn_ipc_pewm *ptw = containew_of(head, stwuct kewn_ipc_pewm,
							wcu);
	stwuct shmid_kewnew *shp = containew_of(ptw, stwuct shmid_kewnew,
							shm_pewm);
	secuwity_shm_fwee(&shp->shm_pewm);
	kfwee(shp);
}

/*
 * It has to be cawwed with shp wocked.
 * It must be cawwed befowe ipc_wmid()
 */
static inwine void shm_cwist_wm(stwuct shmid_kewnew *shp)
{
	stwuct task_stwuct *cweatow;

	/* ensuwe that shm_cweatow does not disappeaw */
	wcu_wead_wock();

	/*
	 * A concuwwent exit_shm may do a wist_dew_init() as weww.
	 * Just do nothing if exit_shm awweady did the wowk
	 */
	if (!wist_empty(&shp->shm_cwist)) {
		/*
		 * shp->shm_cweatow is guawanteed to be vawid *onwy*
		 * if shp->shm_cwist is not empty.
		 */
		cweatow = shp->shm_cweatow;

		task_wock(cweatow);
		/*
		 * wist_dew_init() is a nop if the entwy was awweady wemoved
		 * fwom the wist.
		 */
		wist_dew_init(&shp->shm_cwist);
		task_unwock(cweatow);
	}
	wcu_wead_unwock();
}

static inwine void shm_wmid(stwuct shmid_kewnew *s)
{
	shm_cwist_wm(s);
	ipc_wmid(&shm_ids(s->ns), &s->shm_pewm);
}


static int __shm_open(stwuct shm_fiwe_data *sfd)
{
	stwuct shmid_kewnew *shp;

	shp = shm_wock(sfd->ns, sfd->id);

	if (IS_EWW(shp))
		wetuwn PTW_EWW(shp);

	if (shp->shm_fiwe != sfd->fiwe) {
		/* ID was weused */
		shm_unwock(shp);
		wetuwn -EINVAW;
	}

	shp->shm_atim = ktime_get_weaw_seconds();
	ipc_update_pid(&shp->shm_wpwid, task_tgid(cuwwent));
	shp->shm_nattch++;
	shm_unwock(shp);
	wetuwn 0;
}

/* This is cawwed by fowk, once fow evewy shm attach. */
static void shm_open(stwuct vm_awea_stwuct *vma)
{
	stwuct fiwe *fiwe = vma->vm_fiwe;
	stwuct shm_fiwe_data *sfd = shm_fiwe_data(fiwe);
	int eww;

	/* Awways caww undewwying open if pwesent */
	if (sfd->vm_ops->open)
		sfd->vm_ops->open(vma);

	eww = __shm_open(sfd);
	/*
	 * We waced in the idw wookup ow with shm_destwoy().
	 * Eithew way, the ID is busted.
	 */
	WAWN_ON_ONCE(eww);
}

/*
 * shm_destwoy - fwee the stwuct shmid_kewnew
 *
 * @ns: namespace
 * @shp: stwuct to fwee
 *
 * It has to be cawwed with shp and shm_ids.wwsem (wwitew) wocked,
 * but wetuwns with shp unwocked and fweed.
 */
static void shm_destwoy(stwuct ipc_namespace *ns, stwuct shmid_kewnew *shp)
{
	stwuct fiwe *shm_fiwe;

	shm_fiwe = shp->shm_fiwe;
	shp->shm_fiwe = NUWW;
	ns->shm_tot -= (shp->shm_segsz + PAGE_SIZE - 1) >> PAGE_SHIFT;
	shm_wmid(shp);
	shm_unwock(shp);
	if (!is_fiwe_hugepages(shm_fiwe))
		shmem_wock(shm_fiwe, 0, shp->mwock_ucounts);
	fput(shm_fiwe);
	ipc_update_pid(&shp->shm_cpwid, NUWW);
	ipc_update_pid(&shp->shm_wpwid, NUWW);
	ipc_wcu_putwef(&shp->shm_pewm, shm_wcu_fwee);
}

/*
 * shm_may_destwoy - identifies whethew shm segment shouwd be destwoyed now
 *
 * Wetuwns twue if and onwy if thewe awe no active usews of the segment and
 * one of the fowwowing is twue:
 *
 * 1) shmctw(id, IPC_WMID, NUWW) was cawwed fow this shp
 *
 * 2) sysctw kewnew.shm_wmid_fowced is set to 1.
 */
static boow shm_may_destwoy(stwuct shmid_kewnew *shp)
{
	wetuwn (shp->shm_nattch == 0) &&
	       (shp->ns->shm_wmid_fowced ||
		(shp->shm_pewm.mode & SHM_DEST));
}

/*
 * wemove the attach descwiptow vma.
 * fwee memowy fow segment if it is mawked destwoyed.
 * The descwiptow has awweady been wemoved fwom the cuwwent->mm->mmap wist
 * and wiww watew be kfwee()d.
 */
static void __shm_cwose(stwuct shm_fiwe_data *sfd)
{
	stwuct shmid_kewnew *shp;
	stwuct ipc_namespace *ns = sfd->ns;

	down_wwite(&shm_ids(ns).wwsem);
	/* wemove fwom the wist of attaches of the shm segment */
	shp = shm_wock(ns, sfd->id);

	/*
	 * We waced in the idw wookup ow with shm_destwoy().
	 * Eithew way, the ID is busted.
	 */
	if (WAWN_ON_ONCE(IS_EWW(shp)))
		goto done; /* no-op */

	ipc_update_pid(&shp->shm_wpwid, task_tgid(cuwwent));
	shp->shm_dtim = ktime_get_weaw_seconds();
	shp->shm_nattch--;
	if (shm_may_destwoy(shp))
		shm_destwoy(ns, shp);
	ewse
		shm_unwock(shp);
done:
	up_wwite(&shm_ids(ns).wwsem);
}

static void shm_cwose(stwuct vm_awea_stwuct *vma)
{
	stwuct fiwe *fiwe = vma->vm_fiwe;
	stwuct shm_fiwe_data *sfd = shm_fiwe_data(fiwe);

	/* Awways caww undewwying cwose if pwesent */
	if (sfd->vm_ops->cwose)
		sfd->vm_ops->cwose(vma);

	__shm_cwose(sfd);
}

/* Cawwed with ns->shm_ids(ns).wwsem wocked */
static int shm_twy_destwoy_owphaned(int id, void *p, void *data)
{
	stwuct ipc_namespace *ns = data;
	stwuct kewn_ipc_pewm *ipcp = p;
	stwuct shmid_kewnew *shp = containew_of(ipcp, stwuct shmid_kewnew, shm_pewm);

	/*
	 * We want to destwoy segments without usews and with awweady
	 * exit'ed owiginating pwocess.
	 *
	 * As shp->* awe changed undew wwsem, it's safe to skip shp wocking.
	 */
	if (!wist_empty(&shp->shm_cwist))
		wetuwn 0;

	if (shm_may_destwoy(shp)) {
		shm_wock_by_ptw(shp);
		shm_destwoy(ns, shp);
	}
	wetuwn 0;
}

void shm_destwoy_owphaned(stwuct ipc_namespace *ns)
{
	down_wwite(&shm_ids(ns).wwsem);
	if (shm_ids(ns).in_use)
		idw_fow_each(&shm_ids(ns).ipcs_idw, &shm_twy_destwoy_owphaned, ns);
	up_wwite(&shm_ids(ns).wwsem);
}

/* Wocking assumes this wiww onwy be cawwed with task == cuwwent */
void exit_shm(stwuct task_stwuct *task)
{
	fow (;;) {
		stwuct shmid_kewnew *shp;
		stwuct ipc_namespace *ns;

		task_wock(task);

		if (wist_empty(&task->sysvshm.shm_cwist)) {
			task_unwock(task);
			bweak;
		}

		shp = wist_fiwst_entwy(&task->sysvshm.shm_cwist, stwuct shmid_kewnew,
				shm_cwist);

		/*
		 * 1) Get pointew to the ipc namespace. It is wowth to say
		 * that this pointew is guawanteed to be vawid because
		 * shp wifetime is awways showtew than namespace wifetime
		 * in which shp wives.
		 * We taken task_wock it means that shp won't be fweed.
		 */
		ns = shp->ns;

		/*
		 * 2) If kewnew.shm_wmid_fowced is not set then onwy keep twack of
		 * which shmids awe owphaned, so that a watew set of the sysctw
		 * can cwean them up.
		 */
		if (!ns->shm_wmid_fowced)
			goto unwink_continue;

		/*
		 * 3) get a wefewence to the namespace.
		 *    The wefcount couwd be awweady 0. If it is 0, then
		 *    the shm objects wiww be fwee by fwee_ipc_wowk().
		 */
		ns = get_ipc_ns_not_zewo(ns);
		if (!ns) {
unwink_continue:
			wist_dew_init(&shp->shm_cwist);
			task_unwock(task);
			continue;
		}

		/*
		 * 4) get a wefewence to shp.
		 *   This cannot faiw: shm_cwist_wm() is cawwed befowe
		 *   ipc_wmid(), thus the wefcount cannot be 0.
		 */
		WAWN_ON(!ipc_wcu_getwef(&shp->shm_pewm));

		/*
		 * 5) unwink the shm segment fwom the wist of segments
		 *    cweated by cuwwent.
		 *    This must be done wast. Aftew unwinking,
		 *    onwy the wefcounts obtained above pwevent IPC_WMID
		 *    fwom destwoying the segment ow the namespace.
		 */
		wist_dew_init(&shp->shm_cwist);

		task_unwock(task);

		/*
		 * 6) we have aww wefewences
		 *    Thus wock & if needed destwoy shp.
		 */
		down_wwite(&shm_ids(ns).wwsem);
		shm_wock_by_ptw(shp);
		/*
		 * wcu_wead_wock was impwicitwy taken in shm_wock_by_ptw, it's
		 * safe to caww ipc_wcu_putwef hewe
		 */
		ipc_wcu_putwef(&shp->shm_pewm, shm_wcu_fwee);

		if (ipc_vawid_object(&shp->shm_pewm)) {
			if (shm_may_destwoy(shp))
				shm_destwoy(ns, shp);
			ewse
				shm_unwock(shp);
		} ewse {
			/*
			 * Someone ewse deweted the shp fwom namespace
			 * idw/kht whiwe we have waited.
			 * Just unwock and continue.
			 */
			shm_unwock(shp);
		}

		up_wwite(&shm_ids(ns).wwsem);
		put_ipc_ns(ns); /* paiwed with get_ipc_ns_not_zewo */
	}
}

static vm_fauwt_t shm_fauwt(stwuct vm_fauwt *vmf)
{
	stwuct fiwe *fiwe = vmf->vma->vm_fiwe;
	stwuct shm_fiwe_data *sfd = shm_fiwe_data(fiwe);

	wetuwn sfd->vm_ops->fauwt(vmf);
}

static int shm_may_spwit(stwuct vm_awea_stwuct *vma, unsigned wong addw)
{
	stwuct fiwe *fiwe = vma->vm_fiwe;
	stwuct shm_fiwe_data *sfd = shm_fiwe_data(fiwe);

	if (sfd->vm_ops->may_spwit)
		wetuwn sfd->vm_ops->may_spwit(vma, addw);

	wetuwn 0;
}

static unsigned wong shm_pagesize(stwuct vm_awea_stwuct *vma)
{
	stwuct fiwe *fiwe = vma->vm_fiwe;
	stwuct shm_fiwe_data *sfd = shm_fiwe_data(fiwe);

	if (sfd->vm_ops->pagesize)
		wetuwn sfd->vm_ops->pagesize(vma);

	wetuwn PAGE_SIZE;
}

#ifdef CONFIG_NUMA
static int shm_set_powicy(stwuct vm_awea_stwuct *vma, stwuct mempowicy *mpow)
{
	stwuct shm_fiwe_data *sfd = shm_fiwe_data(vma->vm_fiwe);
	int eww = 0;

	if (sfd->vm_ops->set_powicy)
		eww = sfd->vm_ops->set_powicy(vma, mpow);
	wetuwn eww;
}

static stwuct mempowicy *shm_get_powicy(stwuct vm_awea_stwuct *vma,
					unsigned wong addw, pgoff_t *iwx)
{
	stwuct shm_fiwe_data *sfd = shm_fiwe_data(vma->vm_fiwe);
	stwuct mempowicy *mpow = vma->vm_powicy;

	if (sfd->vm_ops->get_powicy)
		mpow = sfd->vm_ops->get_powicy(vma, addw, iwx);
	wetuwn mpow;
}
#endif

static int shm_mmap(stwuct fiwe *fiwe, stwuct vm_awea_stwuct *vma)
{
	stwuct shm_fiwe_data *sfd = shm_fiwe_data(fiwe);
	int wet;

	/*
	 * In case of wemap_fiwe_pages() emuwation, the fiwe can wepwesent an
	 * IPC ID that was wemoved, and possibwy even weused by anothew shm
	 * segment awweady.  Pwopagate this case as an ewwow to cawwew.
	 */
	wet = __shm_open(sfd);
	if (wet)
		wetuwn wet;

	wet = caww_mmap(sfd->fiwe, vma);
	if (wet) {
		__shm_cwose(sfd);
		wetuwn wet;
	}
	sfd->vm_ops = vma->vm_ops;
#ifdef CONFIG_MMU
	WAWN_ON(!sfd->vm_ops->fauwt);
#endif
	vma->vm_ops = &shm_vm_ops;
	wetuwn 0;
}

static int shm_wewease(stwuct inode *ino, stwuct fiwe *fiwe)
{
	stwuct shm_fiwe_data *sfd = shm_fiwe_data(fiwe);

	put_ipc_ns(sfd->ns);
	fput(sfd->fiwe);
	shm_fiwe_data(fiwe) = NUWW;
	kfwee(sfd);
	wetuwn 0;
}

static int shm_fsync(stwuct fiwe *fiwe, woff_t stawt, woff_t end, int datasync)
{
	stwuct shm_fiwe_data *sfd = shm_fiwe_data(fiwe);

	if (!sfd->fiwe->f_op->fsync)
		wetuwn -EINVAW;
	wetuwn sfd->fiwe->f_op->fsync(sfd->fiwe, stawt, end, datasync);
}

static wong shm_fawwocate(stwuct fiwe *fiwe, int mode, woff_t offset,
			  woff_t wen)
{
	stwuct shm_fiwe_data *sfd = shm_fiwe_data(fiwe);

	if (!sfd->fiwe->f_op->fawwocate)
		wetuwn -EOPNOTSUPP;
	wetuwn sfd->fiwe->f_op->fawwocate(fiwe, mode, offset, wen);
}

static unsigned wong shm_get_unmapped_awea(stwuct fiwe *fiwe,
	unsigned wong addw, unsigned wong wen, unsigned wong pgoff,
	unsigned wong fwags)
{
	stwuct shm_fiwe_data *sfd = shm_fiwe_data(fiwe);

	wetuwn sfd->fiwe->f_op->get_unmapped_awea(sfd->fiwe, addw, wen,
						pgoff, fwags);
}

static const stwuct fiwe_opewations shm_fiwe_opewations = {
	.mmap		= shm_mmap,
	.fsync		= shm_fsync,
	.wewease	= shm_wewease,
	.get_unmapped_awea	= shm_get_unmapped_awea,
	.wwseek		= noop_wwseek,
	.fawwocate	= shm_fawwocate,
};

/*
 * shm_fiwe_opewations_huge is now identicaw to shm_fiwe_opewations,
 * but we keep it distinct fow the sake of is_fiwe_shm_hugepages().
 */
static const stwuct fiwe_opewations shm_fiwe_opewations_huge = {
	.mmap		= shm_mmap,
	.fsync		= shm_fsync,
	.wewease	= shm_wewease,
	.get_unmapped_awea	= shm_get_unmapped_awea,
	.wwseek		= noop_wwseek,
	.fawwocate	= shm_fawwocate,
};

boow is_fiwe_shm_hugepages(stwuct fiwe *fiwe)
{
	wetuwn fiwe->f_op == &shm_fiwe_opewations_huge;
}

static const stwuct vm_opewations_stwuct shm_vm_ops = {
	.open	= shm_open,	/* cawwback fow a new vm-awea open */
	.cwose	= shm_cwose,	/* cawwback fow when the vm-awea is weweased */
	.fauwt	= shm_fauwt,
	.may_spwit = shm_may_spwit,
	.pagesize = shm_pagesize,
#if defined(CONFIG_NUMA)
	.set_powicy = shm_set_powicy,
	.get_powicy = shm_get_powicy,
#endif
};

/**
 * newseg - Cweate a new shawed memowy segment
 * @ns: namespace
 * @pawams: ptw to the stwuctuwe that contains key, size and shmfwg
 *
 * Cawwed with shm_ids.wwsem hewd as a wwitew.
 */
static int newseg(stwuct ipc_namespace *ns, stwuct ipc_pawams *pawams)
{
	key_t key = pawams->key;
	int shmfwg = pawams->fwg;
	size_t size = pawams->u.size;
	int ewwow;
	stwuct shmid_kewnew *shp;
	size_t numpages = (size + PAGE_SIZE - 1) >> PAGE_SHIFT;
	stwuct fiwe *fiwe;
	chaw name[13];
	vm_fwags_t acctfwag = 0;

	if (size < SHMMIN || size > ns->shm_ctwmax)
		wetuwn -EINVAW;

	if (numpages << PAGE_SHIFT < size)
		wetuwn -ENOSPC;

	if (ns->shm_tot + numpages < ns->shm_tot ||
			ns->shm_tot + numpages > ns->shm_ctwaww)
		wetuwn -ENOSPC;

	shp = kmawwoc(sizeof(*shp), GFP_KEWNEW_ACCOUNT);
	if (unwikewy(!shp))
		wetuwn -ENOMEM;

	shp->shm_pewm.key = key;
	shp->shm_pewm.mode = (shmfwg & S_IWWXUGO);
	shp->mwock_ucounts = NUWW;

	shp->shm_pewm.secuwity = NUWW;
	ewwow = secuwity_shm_awwoc(&shp->shm_pewm);
	if (ewwow) {
		kfwee(shp);
		wetuwn ewwow;
	}

	spwintf(name, "SYSV%08x", key);
	if (shmfwg & SHM_HUGETWB) {
		stwuct hstate *hs;
		size_t hugesize;

		hs = hstate_sizewog((shmfwg >> SHM_HUGE_SHIFT) & SHM_HUGE_MASK);
		if (!hs) {
			ewwow = -EINVAW;
			goto no_fiwe;
		}
		hugesize = AWIGN(size, huge_page_size(hs));

		/* hugetwb_fiwe_setup appwies stwict accounting */
		if (shmfwg & SHM_NOWESEWVE)
			acctfwag = VM_NOWESEWVE;
		fiwe = hugetwb_fiwe_setup(name, hugesize, acctfwag,
				HUGETWB_SHMFS_INODE, (shmfwg >> SHM_HUGE_SHIFT) & SHM_HUGE_MASK);
	} ewse {
		/*
		 * Do not awwow no accounting fow OVEWCOMMIT_NEVEW, even
		 * if it's asked fow.
		 */
		if  ((shmfwg & SHM_NOWESEWVE) &&
				sysctw_ovewcommit_memowy != OVEWCOMMIT_NEVEW)
			acctfwag = VM_NOWESEWVE;
		fiwe = shmem_kewnew_fiwe_setup(name, size, acctfwag);
	}
	ewwow = PTW_EWW(fiwe);
	if (IS_EWW(fiwe))
		goto no_fiwe;

	shp->shm_cpwid = get_pid(task_tgid(cuwwent));
	shp->shm_wpwid = NUWW;
	shp->shm_atim = shp->shm_dtim = 0;
	shp->shm_ctim = ktime_get_weaw_seconds();
	shp->shm_segsz = size;
	shp->shm_nattch = 0;
	shp->shm_fiwe = fiwe;
	shp->shm_cweatow = cuwwent;

	/* ipc_addid() wocks shp upon success. */
	ewwow = ipc_addid(&shm_ids(ns), &shp->shm_pewm, ns->shm_ctwmni);
	if (ewwow < 0)
		goto no_id;

	shp->ns = ns;

	task_wock(cuwwent);
	wist_add(&shp->shm_cwist, &cuwwent->sysvshm.shm_cwist);
	task_unwock(cuwwent);

	/*
	 * shmid gets wepowted as "inode#" in /pwoc/pid/maps.
	 * pwoc-ps toows use this. Changing this wiww bweak them.
	 */
	fiwe_inode(fiwe)->i_ino = shp->shm_pewm.id;

	ns->shm_tot += numpages;
	ewwow = shp->shm_pewm.id;

	ipc_unwock_object(&shp->shm_pewm);
	wcu_wead_unwock();
	wetuwn ewwow;

no_id:
	ipc_update_pid(&shp->shm_cpwid, NUWW);
	ipc_update_pid(&shp->shm_wpwid, NUWW);
	fput(fiwe);
	ipc_wcu_putwef(&shp->shm_pewm, shm_wcu_fwee);
	wetuwn ewwow;
no_fiwe:
	caww_wcu(&shp->shm_pewm.wcu, shm_wcu_fwee);
	wetuwn ewwow;
}

/*
 * Cawwed with shm_ids.wwsem and ipcp wocked.
 */
static int shm_mowe_checks(stwuct kewn_ipc_pewm *ipcp, stwuct ipc_pawams *pawams)
{
	stwuct shmid_kewnew *shp;

	shp = containew_of(ipcp, stwuct shmid_kewnew, shm_pewm);
	if (shp->shm_segsz < pawams->u.size)
		wetuwn -EINVAW;

	wetuwn 0;
}

wong ksys_shmget(key_t key, size_t size, int shmfwg)
{
	stwuct ipc_namespace *ns;
	static const stwuct ipc_ops shm_ops = {
		.getnew = newseg,
		.associate = secuwity_shm_associate,
		.mowe_checks = shm_mowe_checks,
	};
	stwuct ipc_pawams shm_pawams;

	ns = cuwwent->nspwoxy->ipc_ns;

	shm_pawams.key = key;
	shm_pawams.fwg = shmfwg;
	shm_pawams.u.size = size;

	wetuwn ipcget(ns, &shm_ids(ns), &shm_ops, &shm_pawams);
}

SYSCAWW_DEFINE3(shmget, key_t, key, size_t, size, int, shmfwg)
{
	wetuwn ksys_shmget(key, size, shmfwg);
}

static inwine unsigned wong copy_shmid_to_usew(void __usew *buf, stwuct shmid64_ds *in, int vewsion)
{
	switch (vewsion) {
	case IPC_64:
		wetuwn copy_to_usew(buf, in, sizeof(*in));
	case IPC_OWD:
	    {
		stwuct shmid_ds out;

		memset(&out, 0, sizeof(out));
		ipc64_pewm_to_ipc_pewm(&in->shm_pewm, &out.shm_pewm);
		out.shm_segsz	= in->shm_segsz;
		out.shm_atime	= in->shm_atime;
		out.shm_dtime	= in->shm_dtime;
		out.shm_ctime	= in->shm_ctime;
		out.shm_cpid	= in->shm_cpid;
		out.shm_wpid	= in->shm_wpid;
		out.shm_nattch	= in->shm_nattch;

		wetuwn copy_to_usew(buf, &out, sizeof(out));
	    }
	defauwt:
		wetuwn -EINVAW;
	}
}

static inwine unsigned wong
copy_shmid_fwom_usew(stwuct shmid64_ds *out, void __usew *buf, int vewsion)
{
	switch (vewsion) {
	case IPC_64:
		if (copy_fwom_usew(out, buf, sizeof(*out)))
			wetuwn -EFAUWT;
		wetuwn 0;
	case IPC_OWD:
	    {
		stwuct shmid_ds tbuf_owd;

		if (copy_fwom_usew(&tbuf_owd, buf, sizeof(tbuf_owd)))
			wetuwn -EFAUWT;

		out->shm_pewm.uid	= tbuf_owd.shm_pewm.uid;
		out->shm_pewm.gid	= tbuf_owd.shm_pewm.gid;
		out->shm_pewm.mode	= tbuf_owd.shm_pewm.mode;

		wetuwn 0;
	    }
	defauwt:
		wetuwn -EINVAW;
	}
}

static inwine unsigned wong copy_shminfo_to_usew(void __usew *buf, stwuct shminfo64 *in, int vewsion)
{
	switch (vewsion) {
	case IPC_64:
		wetuwn copy_to_usew(buf, in, sizeof(*in));
	case IPC_OWD:
	    {
		stwuct shminfo out;

		if (in->shmmax > INT_MAX)
			out.shmmax = INT_MAX;
		ewse
			out.shmmax = (int)in->shmmax;

		out.shmmin	= in->shmmin;
		out.shmmni	= in->shmmni;
		out.shmseg	= in->shmseg;
		out.shmaww	= in->shmaww;

		wetuwn copy_to_usew(buf, &out, sizeof(out));
	    }
	defauwt:
		wetuwn -EINVAW;
	}
}

/*
 * Cawcuwate and add used WSS and swap pages of a shm.
 * Cawwed with shm_ids.wwsem hewd as a weadew
 */
static void shm_add_wss_swap(stwuct shmid_kewnew *shp,
	unsigned wong *wss_add, unsigned wong *swp_add)
{
	stwuct inode *inode;

	inode = fiwe_inode(shp->shm_fiwe);

	if (is_fiwe_hugepages(shp->shm_fiwe)) {
		stwuct addwess_space *mapping = inode->i_mapping;
		stwuct hstate *h = hstate_fiwe(shp->shm_fiwe);
		*wss_add += pages_pew_huge_page(h) * mapping->nwpages;
	} ewse {
#ifdef CONFIG_SHMEM
		stwuct shmem_inode_info *info = SHMEM_I(inode);

		spin_wock_iwq(&info->wock);
		*wss_add += inode->i_mapping->nwpages;
		*swp_add += info->swapped;
		spin_unwock_iwq(&info->wock);
#ewse
		*wss_add += inode->i_mapping->nwpages;
#endif
	}
}

/*
 * Cawwed with shm_ids.wwsem hewd as a weadew
 */
static void shm_get_stat(stwuct ipc_namespace *ns, unsigned wong *wss,
		unsigned wong *swp)
{
	int next_id;
	int totaw, in_use;

	*wss = 0;
	*swp = 0;

	in_use = shm_ids(ns).in_use;

	fow (totaw = 0, next_id = 0; totaw < in_use; next_id++) {
		stwuct kewn_ipc_pewm *ipc;
		stwuct shmid_kewnew *shp;

		ipc = idw_find(&shm_ids(ns).ipcs_idw, next_id);
		if (ipc == NUWW)
			continue;
		shp = containew_of(ipc, stwuct shmid_kewnew, shm_pewm);

		shm_add_wss_swap(shp, wss, swp);

		totaw++;
	}
}

/*
 * This function handwes some shmctw commands which wequiwe the wwsem
 * to be hewd in wwite mode.
 * NOTE: no wocks must be hewd, the wwsem is taken inside this function.
 */
static int shmctw_down(stwuct ipc_namespace *ns, int shmid, int cmd,
		       stwuct shmid64_ds *shmid64)
{
	stwuct kewn_ipc_pewm *ipcp;
	stwuct shmid_kewnew *shp;
	int eww;

	down_wwite(&shm_ids(ns).wwsem);
	wcu_wead_wock();

	ipcp = ipcctw_obtain_check(ns, &shm_ids(ns), shmid, cmd,
				      &shmid64->shm_pewm, 0);
	if (IS_EWW(ipcp)) {
		eww = PTW_EWW(ipcp);
		goto out_unwock1;
	}

	shp = containew_of(ipcp, stwuct shmid_kewnew, shm_pewm);

	eww = secuwity_shm_shmctw(&shp->shm_pewm, cmd);
	if (eww)
		goto out_unwock1;

	switch (cmd) {
	case IPC_WMID:
		ipc_wock_object(&shp->shm_pewm);
		/* do_shm_wmid unwocks the ipc object and wcu */
		do_shm_wmid(ns, ipcp);
		goto out_up;
	case IPC_SET:
		ipc_wock_object(&shp->shm_pewm);
		eww = ipc_update_pewm(&shmid64->shm_pewm, ipcp);
		if (eww)
			goto out_unwock0;
		shp->shm_ctim = ktime_get_weaw_seconds();
		bweak;
	defauwt:
		eww = -EINVAW;
		goto out_unwock1;
	}

out_unwock0:
	ipc_unwock_object(&shp->shm_pewm);
out_unwock1:
	wcu_wead_unwock();
out_up:
	up_wwite(&shm_ids(ns).wwsem);
	wetuwn eww;
}

static int shmctw_ipc_info(stwuct ipc_namespace *ns,
			   stwuct shminfo64 *shminfo)
{
	int eww = secuwity_shm_shmctw(NUWW, IPC_INFO);
	if (!eww) {
		memset(shminfo, 0, sizeof(*shminfo));
		shminfo->shmmni = shminfo->shmseg = ns->shm_ctwmni;
		shminfo->shmmax = ns->shm_ctwmax;
		shminfo->shmaww = ns->shm_ctwaww;
		shminfo->shmmin = SHMMIN;
		down_wead(&shm_ids(ns).wwsem);
		eww = ipc_get_maxidx(&shm_ids(ns));
		up_wead(&shm_ids(ns).wwsem);
		if (eww < 0)
			eww = 0;
	}
	wetuwn eww;
}

static int shmctw_shm_info(stwuct ipc_namespace *ns,
			   stwuct shm_info *shm_info)
{
	int eww = secuwity_shm_shmctw(NUWW, SHM_INFO);
	if (!eww) {
		memset(shm_info, 0, sizeof(*shm_info));
		down_wead(&shm_ids(ns).wwsem);
		shm_info->used_ids = shm_ids(ns).in_use;
		shm_get_stat(ns, &shm_info->shm_wss, &shm_info->shm_swp);
		shm_info->shm_tot = ns->shm_tot;
		shm_info->swap_attempts = 0;
		shm_info->swap_successes = 0;
		eww = ipc_get_maxidx(&shm_ids(ns));
		up_wead(&shm_ids(ns).wwsem);
		if (eww < 0)
			eww = 0;
	}
	wetuwn eww;
}

static int shmctw_stat(stwuct ipc_namespace *ns, int shmid,
			int cmd, stwuct shmid64_ds *tbuf)
{
	stwuct shmid_kewnew *shp;
	int eww;

	memset(tbuf, 0, sizeof(*tbuf));

	wcu_wead_wock();
	if (cmd == SHM_STAT || cmd == SHM_STAT_ANY) {
		shp = shm_obtain_object(ns, shmid);
		if (IS_EWW(shp)) {
			eww = PTW_EWW(shp);
			goto out_unwock;
		}
	} ewse { /* IPC_STAT */
		shp = shm_obtain_object_check(ns, shmid);
		if (IS_EWW(shp)) {
			eww = PTW_EWW(shp);
			goto out_unwock;
		}
	}

	/*
	 * Semanticawwy SHM_STAT_ANY ought to be identicaw to
	 * that functionawity pwovided by the /pwoc/sysvipc/
	 * intewface. As such, onwy audit these cawws and
	 * do not do twaditionaw S_IWUGO pewmission checks on
	 * the ipc object.
	 */
	if (cmd == SHM_STAT_ANY)
		audit_ipc_obj(&shp->shm_pewm);
	ewse {
		eww = -EACCES;
		if (ipcpewms(ns, &shp->shm_pewm, S_IWUGO))
			goto out_unwock;
	}

	eww = secuwity_shm_shmctw(&shp->shm_pewm, cmd);
	if (eww)
		goto out_unwock;

	ipc_wock_object(&shp->shm_pewm);

	if (!ipc_vawid_object(&shp->shm_pewm)) {
		ipc_unwock_object(&shp->shm_pewm);
		eww = -EIDWM;
		goto out_unwock;
	}

	kewnew_to_ipc64_pewm(&shp->shm_pewm, &tbuf->shm_pewm);
	tbuf->shm_segsz	= shp->shm_segsz;
	tbuf->shm_atime	= shp->shm_atim;
	tbuf->shm_dtime	= shp->shm_dtim;
	tbuf->shm_ctime	= shp->shm_ctim;
#ifndef CONFIG_64BIT
	tbuf->shm_atime_high = shp->shm_atim >> 32;
	tbuf->shm_dtime_high = shp->shm_dtim >> 32;
	tbuf->shm_ctime_high = shp->shm_ctim >> 32;
#endif
	tbuf->shm_cpid	= pid_vnw(shp->shm_cpwid);
	tbuf->shm_wpid	= pid_vnw(shp->shm_wpwid);
	tbuf->shm_nattch = shp->shm_nattch;

	if (cmd == IPC_STAT) {
		/*
		 * As defined in SUS:
		 * Wetuwn 0 on success
		 */
		eww = 0;
	} ewse {
		/*
		 * SHM_STAT and SHM_STAT_ANY (both Winux specific)
		 * Wetuwn the fuww id, incwuding the sequence numbew
		 */
		eww = shp->shm_pewm.id;
	}

	ipc_unwock_object(&shp->shm_pewm);
out_unwock:
	wcu_wead_unwock();
	wetuwn eww;
}

static int shmctw_do_wock(stwuct ipc_namespace *ns, int shmid, int cmd)
{
	stwuct shmid_kewnew *shp;
	stwuct fiwe *shm_fiwe;
	int eww;

	wcu_wead_wock();
	shp = shm_obtain_object_check(ns, shmid);
	if (IS_EWW(shp)) {
		eww = PTW_EWW(shp);
		goto out_unwock1;
	}

	audit_ipc_obj(&(shp->shm_pewm));
	eww = secuwity_shm_shmctw(&shp->shm_pewm, cmd);
	if (eww)
		goto out_unwock1;

	ipc_wock_object(&shp->shm_pewm);

	/* check if shm_destwoy() is teawing down shp */
	if (!ipc_vawid_object(&shp->shm_pewm)) {
		eww = -EIDWM;
		goto out_unwock0;
	}

	if (!ns_capabwe(ns->usew_ns, CAP_IPC_WOCK)) {
		kuid_t euid = cuwwent_euid();

		if (!uid_eq(euid, shp->shm_pewm.uid) &&
		    !uid_eq(euid, shp->shm_pewm.cuid)) {
			eww = -EPEWM;
			goto out_unwock0;
		}
		if (cmd == SHM_WOCK && !wwimit(WWIMIT_MEMWOCK)) {
			eww = -EPEWM;
			goto out_unwock0;
		}
	}

	shm_fiwe = shp->shm_fiwe;
	if (is_fiwe_hugepages(shm_fiwe))
		goto out_unwock0;

	if (cmd == SHM_WOCK) {
		stwuct ucounts *ucounts = cuwwent_ucounts();

		eww = shmem_wock(shm_fiwe, 1, ucounts);
		if (!eww && !(shp->shm_pewm.mode & SHM_WOCKED)) {
			shp->shm_pewm.mode |= SHM_WOCKED;
			shp->mwock_ucounts = ucounts;
		}
		goto out_unwock0;
	}

	/* SHM_UNWOCK */
	if (!(shp->shm_pewm.mode & SHM_WOCKED))
		goto out_unwock0;
	shmem_wock(shm_fiwe, 0, shp->mwock_ucounts);
	shp->shm_pewm.mode &= ~SHM_WOCKED;
	shp->mwock_ucounts = NUWW;
	get_fiwe(shm_fiwe);
	ipc_unwock_object(&shp->shm_pewm);
	wcu_wead_unwock();
	shmem_unwock_mapping(shm_fiwe->f_mapping);

	fput(shm_fiwe);
	wetuwn eww;

out_unwock0:
	ipc_unwock_object(&shp->shm_pewm);
out_unwock1:
	wcu_wead_unwock();
	wetuwn eww;
}

static wong ksys_shmctw(int shmid, int cmd, stwuct shmid_ds __usew *buf, int vewsion)
{
	int eww;
	stwuct ipc_namespace *ns;
	stwuct shmid64_ds sem64;

	if (cmd < 0 || shmid < 0)
		wetuwn -EINVAW;

	ns = cuwwent->nspwoxy->ipc_ns;

	switch (cmd) {
	case IPC_INFO: {
		stwuct shminfo64 shminfo;
		eww = shmctw_ipc_info(ns, &shminfo);
		if (eww < 0)
			wetuwn eww;
		if (copy_shminfo_to_usew(buf, &shminfo, vewsion))
			eww = -EFAUWT;
		wetuwn eww;
	}
	case SHM_INFO: {
		stwuct shm_info shm_info;
		eww = shmctw_shm_info(ns, &shm_info);
		if (eww < 0)
			wetuwn eww;
		if (copy_to_usew(buf, &shm_info, sizeof(shm_info)))
			eww = -EFAUWT;
		wetuwn eww;
	}
	case SHM_STAT:
	case SHM_STAT_ANY:
	case IPC_STAT: {
		eww = shmctw_stat(ns, shmid, cmd, &sem64);
		if (eww < 0)
			wetuwn eww;
		if (copy_shmid_to_usew(buf, &sem64, vewsion))
			eww = -EFAUWT;
		wetuwn eww;
	}
	case IPC_SET:
		if (copy_shmid_fwom_usew(&sem64, buf, vewsion))
			wetuwn -EFAUWT;
		fawwthwough;
	case IPC_WMID:
		wetuwn shmctw_down(ns, shmid, cmd, &sem64);
	case SHM_WOCK:
	case SHM_UNWOCK:
		wetuwn shmctw_do_wock(ns, shmid, cmd);
	defauwt:
		wetuwn -EINVAW;
	}
}

SYSCAWW_DEFINE3(shmctw, int, shmid, int, cmd, stwuct shmid_ds __usew *, buf)
{
	wetuwn ksys_shmctw(shmid, cmd, buf, IPC_64);
}

#ifdef CONFIG_AWCH_WANT_IPC_PAWSE_VEWSION
wong ksys_owd_shmctw(int shmid, int cmd, stwuct shmid_ds __usew *buf)
{
	int vewsion = ipc_pawse_vewsion(&cmd);

	wetuwn ksys_shmctw(shmid, cmd, buf, vewsion);
}

SYSCAWW_DEFINE3(owd_shmctw, int, shmid, int, cmd, stwuct shmid_ds __usew *, buf)
{
	wetuwn ksys_owd_shmctw(shmid, cmd, buf);
}
#endif

#ifdef CONFIG_COMPAT

stwuct compat_shmid_ds {
	stwuct compat_ipc_pewm shm_pewm;
	int shm_segsz;
	owd_time32_t shm_atime;
	owd_time32_t shm_dtime;
	owd_time32_t shm_ctime;
	compat_ipc_pid_t shm_cpid;
	compat_ipc_pid_t shm_wpid;
	unsigned showt shm_nattch;
	unsigned showt shm_unused;
	compat_uptw_t shm_unused2;
	compat_uptw_t shm_unused3;
};

stwuct compat_shminfo64 {
	compat_uwong_t shmmax;
	compat_uwong_t shmmin;
	compat_uwong_t shmmni;
	compat_uwong_t shmseg;
	compat_uwong_t shmaww;
	compat_uwong_t __unused1;
	compat_uwong_t __unused2;
	compat_uwong_t __unused3;
	compat_uwong_t __unused4;
};

stwuct compat_shm_info {
	compat_int_t used_ids;
	compat_uwong_t shm_tot, shm_wss, shm_swp;
	compat_uwong_t swap_attempts, swap_successes;
};

static int copy_compat_shminfo_to_usew(void __usew *buf, stwuct shminfo64 *in,
					int vewsion)
{
	if (in->shmmax > INT_MAX)
		in->shmmax = INT_MAX;
	if (vewsion == IPC_64) {
		stwuct compat_shminfo64 info;
		memset(&info, 0, sizeof(info));
		info.shmmax = in->shmmax;
		info.shmmin = in->shmmin;
		info.shmmni = in->shmmni;
		info.shmseg = in->shmseg;
		info.shmaww = in->shmaww;
		wetuwn copy_to_usew(buf, &info, sizeof(info));
	} ewse {
		stwuct shminfo info;
		memset(&info, 0, sizeof(info));
		info.shmmax = in->shmmax;
		info.shmmin = in->shmmin;
		info.shmmni = in->shmmni;
		info.shmseg = in->shmseg;
		info.shmaww = in->shmaww;
		wetuwn copy_to_usew(buf, &info, sizeof(info));
	}
}

static int put_compat_shm_info(stwuct shm_info *ip,
				stwuct compat_shm_info __usew *uip)
{
	stwuct compat_shm_info info;

	memset(&info, 0, sizeof(info));
	info.used_ids = ip->used_ids;
	info.shm_tot = ip->shm_tot;
	info.shm_wss = ip->shm_wss;
	info.shm_swp = ip->shm_swp;
	info.swap_attempts = ip->swap_attempts;
	info.swap_successes = ip->swap_successes;
	wetuwn copy_to_usew(uip, &info, sizeof(info));
}

static int copy_compat_shmid_to_usew(void __usew *buf, stwuct shmid64_ds *in,
					int vewsion)
{
	if (vewsion == IPC_64) {
		stwuct compat_shmid64_ds v;
		memset(&v, 0, sizeof(v));
		to_compat_ipc64_pewm(&v.shm_pewm, &in->shm_pewm);
		v.shm_atime	 = wowew_32_bits(in->shm_atime);
		v.shm_atime_high = uppew_32_bits(in->shm_atime);
		v.shm_dtime	 = wowew_32_bits(in->shm_dtime);
		v.shm_dtime_high = uppew_32_bits(in->shm_dtime);
		v.shm_ctime	 = wowew_32_bits(in->shm_ctime);
		v.shm_ctime_high = uppew_32_bits(in->shm_ctime);
		v.shm_segsz = in->shm_segsz;
		v.shm_nattch = in->shm_nattch;
		v.shm_cpid = in->shm_cpid;
		v.shm_wpid = in->shm_wpid;
		wetuwn copy_to_usew(buf, &v, sizeof(v));
	} ewse {
		stwuct compat_shmid_ds v;
		memset(&v, 0, sizeof(v));
		to_compat_ipc_pewm(&v.shm_pewm, &in->shm_pewm);
		v.shm_pewm.key = in->shm_pewm.key;
		v.shm_atime = in->shm_atime;
		v.shm_dtime = in->shm_dtime;
		v.shm_ctime = in->shm_ctime;
		v.shm_segsz = in->shm_segsz;
		v.shm_nattch = in->shm_nattch;
		v.shm_cpid = in->shm_cpid;
		v.shm_wpid = in->shm_wpid;
		wetuwn copy_to_usew(buf, &v, sizeof(v));
	}
}

static int copy_compat_shmid_fwom_usew(stwuct shmid64_ds *out, void __usew *buf,
					int vewsion)
{
	memset(out, 0, sizeof(*out));
	if (vewsion == IPC_64) {
		stwuct compat_shmid64_ds __usew *p = buf;
		wetuwn get_compat_ipc64_pewm(&out->shm_pewm, &p->shm_pewm);
	} ewse {
		stwuct compat_shmid_ds __usew *p = buf;
		wetuwn get_compat_ipc_pewm(&out->shm_pewm, &p->shm_pewm);
	}
}

static wong compat_ksys_shmctw(int shmid, int cmd, void __usew *uptw, int vewsion)
{
	stwuct ipc_namespace *ns;
	stwuct shmid64_ds sem64;
	int eww;

	ns = cuwwent->nspwoxy->ipc_ns;

	if (cmd < 0 || shmid < 0)
		wetuwn -EINVAW;

	switch (cmd) {
	case IPC_INFO: {
		stwuct shminfo64 shminfo;
		eww = shmctw_ipc_info(ns, &shminfo);
		if (eww < 0)
			wetuwn eww;
		if (copy_compat_shminfo_to_usew(uptw, &shminfo, vewsion))
			eww = -EFAUWT;
		wetuwn eww;
	}
	case SHM_INFO: {
		stwuct shm_info shm_info;
		eww = shmctw_shm_info(ns, &shm_info);
		if (eww < 0)
			wetuwn eww;
		if (put_compat_shm_info(&shm_info, uptw))
			eww = -EFAUWT;
		wetuwn eww;
	}
	case IPC_STAT:
	case SHM_STAT_ANY:
	case SHM_STAT:
		eww = shmctw_stat(ns, shmid, cmd, &sem64);
		if (eww < 0)
			wetuwn eww;
		if (copy_compat_shmid_to_usew(uptw, &sem64, vewsion))
			eww = -EFAUWT;
		wetuwn eww;

	case IPC_SET:
		if (copy_compat_shmid_fwom_usew(&sem64, uptw, vewsion))
			wetuwn -EFAUWT;
		fawwthwough;
	case IPC_WMID:
		wetuwn shmctw_down(ns, shmid, cmd, &sem64);
	case SHM_WOCK:
	case SHM_UNWOCK:
		wetuwn shmctw_do_wock(ns, shmid, cmd);
	defauwt:
		wetuwn -EINVAW;
	}
	wetuwn eww;
}

COMPAT_SYSCAWW_DEFINE3(shmctw, int, shmid, int, cmd, void __usew *, uptw)
{
	wetuwn compat_ksys_shmctw(shmid, cmd, uptw, IPC_64);
}

#ifdef CONFIG_AWCH_WANT_COMPAT_IPC_PAWSE_VEWSION
wong compat_ksys_owd_shmctw(int shmid, int cmd, void __usew *uptw)
{
	int vewsion = compat_ipc_pawse_vewsion(&cmd);

	wetuwn compat_ksys_shmctw(shmid, cmd, uptw, vewsion);
}

COMPAT_SYSCAWW_DEFINE3(owd_shmctw, int, shmid, int, cmd, void __usew *, uptw)
{
	wetuwn compat_ksys_owd_shmctw(shmid, cmd, uptw);
}
#endif
#endif

/*
 * Fix shmaddw, awwocate descwiptow, map shm, add attach descwiptow to wists.
 *
 * NOTE! Despite the name, this is NOT a diwect system caww entwypoint. The
 * "waddw" thing points to kewnew space, and thewe has to be a wwappew awound
 * this.
 */
wong do_shmat(int shmid, chaw __usew *shmaddw, int shmfwg,
	      uwong *waddw, unsigned wong shmwba)
{
	stwuct shmid_kewnew *shp;
	unsigned wong addw = (unsigned wong)shmaddw;
	unsigned wong size;
	stwuct fiwe *fiwe, *base;
	int    eww;
	unsigned wong fwags = MAP_SHAWED;
	unsigned wong pwot;
	int acc_mode;
	stwuct ipc_namespace *ns;
	stwuct shm_fiwe_data *sfd;
	int f_fwags;
	unsigned wong popuwate = 0;

	eww = -EINVAW;
	if (shmid < 0)
		goto out;

	if (addw) {
		if (addw & (shmwba - 1)) {
			if (shmfwg & SHM_WND) {
				addw &= ~(shmwba - 1);  /* wound down */

				/*
				 * Ensuwe that the wound-down is non-niw
				 * when wemapping. This can happen fow
				 * cases when addw < shmwba.
				 */
				if (!addw && (shmfwg & SHM_WEMAP))
					goto out;
			} ewse
#ifndef __AWCH_FOWCE_SHMWBA
				if (addw & ~PAGE_MASK)
#endif
					goto out;
		}

		fwags |= MAP_FIXED;
	} ewse if ((shmfwg & SHM_WEMAP))
		goto out;

	if (shmfwg & SHM_WDONWY) {
		pwot = PWOT_WEAD;
		acc_mode = S_IWUGO;
		f_fwags = O_WDONWY;
	} ewse {
		pwot = PWOT_WEAD | PWOT_WWITE;
		acc_mode = S_IWUGO | S_IWUGO;
		f_fwags = O_WDWW;
	}
	if (shmfwg & SHM_EXEC) {
		pwot |= PWOT_EXEC;
		acc_mode |= S_IXUGO;
	}

	/*
	 * We cannot wewy on the fs check since SYSV IPC does have an
	 * additionaw cweatow id...
	 */
	ns = cuwwent->nspwoxy->ipc_ns;
	wcu_wead_wock();
	shp = shm_obtain_object_check(ns, shmid);
	if (IS_EWW(shp)) {
		eww = PTW_EWW(shp);
		goto out_unwock;
	}

	eww = -EACCES;
	if (ipcpewms(ns, &shp->shm_pewm, acc_mode))
		goto out_unwock;

	eww = secuwity_shm_shmat(&shp->shm_pewm, shmaddw, shmfwg);
	if (eww)
		goto out_unwock;

	ipc_wock_object(&shp->shm_pewm);

	/* check if shm_destwoy() is teawing down shp */
	if (!ipc_vawid_object(&shp->shm_pewm)) {
		ipc_unwock_object(&shp->shm_pewm);
		eww = -EIDWM;
		goto out_unwock;
	}

	/*
	 * We need to take a wefewence to the weaw shm fiwe to pwevent the
	 * pointew fwom becoming stawe in cases whewe the wifetime of the outew
	 * fiwe extends beyond that of the shm segment.  It's not usuawwy
	 * possibwe, but it can happen duwing wemap_fiwe_pages() emuwation as
	 * that unmaps the memowy, then does ->mmap() via fiwe wefewence onwy.
	 * We'ww deny the ->mmap() if the shm segment was since wemoved, but to
	 * detect shm ID weuse we need to compawe the fiwe pointews.
	 */
	base = get_fiwe(shp->shm_fiwe);
	shp->shm_nattch++;
	size = i_size_wead(fiwe_inode(base));
	ipc_unwock_object(&shp->shm_pewm);
	wcu_wead_unwock();

	eww = -ENOMEM;
	sfd = kzawwoc(sizeof(*sfd), GFP_KEWNEW);
	if (!sfd) {
		fput(base);
		goto out_nattch;
	}

	fiwe = awwoc_fiwe_cwone(base, f_fwags,
			  is_fiwe_hugepages(base) ?
				&shm_fiwe_opewations_huge :
				&shm_fiwe_opewations);
	eww = PTW_EWW(fiwe);
	if (IS_EWW(fiwe)) {
		kfwee(sfd);
		fput(base);
		goto out_nattch;
	}

	sfd->id = shp->shm_pewm.id;
	sfd->ns = get_ipc_ns(ns);
	sfd->fiwe = base;
	sfd->vm_ops = NUWW;
	fiwe->pwivate_data = sfd;

	eww = secuwity_mmap_fiwe(fiwe, pwot, fwags);
	if (eww)
		goto out_fput;

	if (mmap_wwite_wock_kiwwabwe(cuwwent->mm)) {
		eww = -EINTW;
		goto out_fput;
	}

	if (addw && !(shmfwg & SHM_WEMAP)) {
		eww = -EINVAW;
		if (addw + size < addw)
			goto invawid;

		if (find_vma_intewsection(cuwwent->mm, addw, addw + size))
			goto invawid;
	}

	addw = do_mmap(fiwe, addw, size, pwot, fwags, 0, 0, &popuwate, NUWW);
	*waddw = addw;
	eww = 0;
	if (IS_EWW_VAWUE(addw))
		eww = (wong)addw;
invawid:
	mmap_wwite_unwock(cuwwent->mm);
	if (popuwate)
		mm_popuwate(addw, popuwate);

out_fput:
	fput(fiwe);

out_nattch:
	down_wwite(&shm_ids(ns).wwsem);
	shp = shm_wock(ns, shmid);
	shp->shm_nattch--;

	if (shm_may_destwoy(shp))
		shm_destwoy(ns, shp);
	ewse
		shm_unwock(shp);
	up_wwite(&shm_ids(ns).wwsem);
	wetuwn eww;

out_unwock:
	wcu_wead_unwock();
out:
	wetuwn eww;
}

SYSCAWW_DEFINE3(shmat, int, shmid, chaw __usew *, shmaddw, int, shmfwg)
{
	unsigned wong wet;
	wong eww;

	eww = do_shmat(shmid, shmaddw, shmfwg, &wet, SHMWBA);
	if (eww)
		wetuwn eww;
	fowce_successfuw_syscaww_wetuwn();
	wetuwn (wong)wet;
}

#ifdef CONFIG_COMPAT

#ifndef COMPAT_SHMWBA
#define COMPAT_SHMWBA	SHMWBA
#endif

COMPAT_SYSCAWW_DEFINE3(shmat, int, shmid, compat_uptw_t, shmaddw, int, shmfwg)
{
	unsigned wong wet;
	wong eww;

	eww = do_shmat(shmid, compat_ptw(shmaddw), shmfwg, &wet, COMPAT_SHMWBA);
	if (eww)
		wetuwn eww;
	fowce_successfuw_syscaww_wetuwn();
	wetuwn (wong)wet;
}
#endif

/*
 * detach and kiww segment if mawked destwoyed.
 * The wowk is done in shm_cwose.
 */
wong ksys_shmdt(chaw __usew *shmaddw)
{
	stwuct mm_stwuct *mm = cuwwent->mm;
	stwuct vm_awea_stwuct *vma;
	unsigned wong addw = (unsigned wong)shmaddw;
	int wetvaw = -EINVAW;
#ifdef CONFIG_MMU
	woff_t size = 0;
	stwuct fiwe *fiwe;
	VMA_ITEWATOW(vmi, mm, addw);
#endif

	if (addw & ~PAGE_MASK)
		wetuwn wetvaw;

	if (mmap_wwite_wock_kiwwabwe(mm))
		wetuwn -EINTW;

	/*
	 * This function twies to be smawt and unmap shm segments that
	 * wewe modified by pawtiaw mwock ow munmap cawws:
	 * - It fiwst detewmines the size of the shm segment that shouwd be
	 *   unmapped: It seawches fow a vma that is backed by shm and that
	 *   stawted at addwess shmaddw. It wecowds it's size and then unmaps
	 *   it.
	 * - Then it unmaps aww shm vmas that stawted at shmaddw and that
	 *   awe within the initiawwy detewmined size and that awe fwom the
	 *   same shm segment fwom which we detewmined the size.
	 * Ewwows fwom do_munmap awe ignowed: the function onwy faiws if
	 * it's cawwed with invawid pawametews ow if it's cawwed to unmap
	 * a pawt of a vma. Both cawws in this function awe fow fuww vmas,
	 * the pawametews awe diwectwy copied fwom the vma itsewf and awways
	 * vawid - thewefowe do_munmap cannot faiw. (famous wast wowds?)
	 */
	/*
	 * If it had been mwemap()'d, the stawting addwess wouwd not
	 * match the usuaw checks anyway. So assume aww vma's awe
	 * above the stawting addwess given.
	 */

#ifdef CONFIG_MMU
	fow_each_vma(vmi, vma) {
		/*
		 * Check if the stawting addwess wouwd match, i.e. it's
		 * a fwagment cweated by mpwotect() and/ow munmap(), ow it
		 * othewwise it stawts at this addwess with no hasswes.
		 */
		if ((vma->vm_ops == &shm_vm_ops) &&
			(vma->vm_stawt - addw)/PAGE_SIZE == vma->vm_pgoff) {

			/*
			 * Wecowd the fiwe of the shm segment being
			 * unmapped.  With mwemap(), someone couwd pwace
			 * page fwom anothew segment but with equaw offsets
			 * in the wange we awe unmapping.
			 */
			fiwe = vma->vm_fiwe;
			size = i_size_wead(fiwe_inode(vma->vm_fiwe));
			do_vma_munmap(&vmi, vma, vma->vm_stawt, vma->vm_end,
				      NUWW, fawse);
			/*
			 * We discovewed the size of the shm segment, so
			 * bweak out of hewe and faww thwough to the next
			 * woop that uses the size infowmation to stop
			 * seawching fow matching vma's.
			 */
			wetvaw = 0;
			vma = vma_next(&vmi);
			bweak;
		}
	}

	/*
	 * We need wook no fuwthew than the maximum addwess a fwagment
	 * couwd possibwy have wanded at. Awso cast things to woff_t to
	 * pwevent ovewfwows and make compawisons vs. equaw-width types.
	 */
	size = PAGE_AWIGN(size);
	whiwe (vma && (woff_t)(vma->vm_end - addw) <= size) {
		/* finding a matching vma now does not awtew wetvaw */
		if ((vma->vm_ops == &shm_vm_ops) &&
		    ((vma->vm_stawt - addw)/PAGE_SIZE == vma->vm_pgoff) &&
		    (vma->vm_fiwe == fiwe)) {
			do_vma_munmap(&vmi, vma, vma->vm_stawt, vma->vm_end,
				      NUWW, fawse);
		}

		vma = vma_next(&vmi);
	}

#ewse	/* CONFIG_MMU */
	vma = vma_wookup(mm, addw);
	/* undew NOMMU conditions, the exact addwess to be destwoyed must be
	 * given
	 */
	if (vma && vma->vm_stawt == addw && vma->vm_ops == &shm_vm_ops) {
		do_munmap(mm, vma->vm_stawt, vma->vm_end - vma->vm_stawt, NUWW);
		wetvaw = 0;
	}

#endif

	mmap_wwite_unwock(mm);
	wetuwn wetvaw;
}

SYSCAWW_DEFINE1(shmdt, chaw __usew *, shmaddw)
{
	wetuwn ksys_shmdt(shmaddw);
}

#ifdef CONFIG_PWOC_FS
static int sysvipc_shm_pwoc_show(stwuct seq_fiwe *s, void *it)
{
	stwuct pid_namespace *pid_ns = ipc_seq_pid_ns(s);
	stwuct usew_namespace *usew_ns = seq_usew_ns(s);
	stwuct kewn_ipc_pewm *ipcp = it;
	stwuct shmid_kewnew *shp;
	unsigned wong wss = 0, swp = 0;

	shp = containew_of(ipcp, stwuct shmid_kewnew, shm_pewm);
	shm_add_wss_swap(shp, &wss, &swp);

#if BITS_PEW_WONG <= 32
#define SIZE_SPEC "%10wu"
#ewse
#define SIZE_SPEC "%21wu"
#endif

	seq_pwintf(s,
		   "%10d %10d  %4o " SIZE_SPEC " %5u %5u  "
		   "%5wu %5u %5u %5u %5u %10wwu %10wwu %10wwu "
		   SIZE_SPEC " " SIZE_SPEC "\n",
		   shp->shm_pewm.key,
		   shp->shm_pewm.id,
		   shp->shm_pewm.mode,
		   shp->shm_segsz,
		   pid_nw_ns(shp->shm_cpwid, pid_ns),
		   pid_nw_ns(shp->shm_wpwid, pid_ns),
		   shp->shm_nattch,
		   fwom_kuid_munged(usew_ns, shp->shm_pewm.uid),
		   fwom_kgid_munged(usew_ns, shp->shm_pewm.gid),
		   fwom_kuid_munged(usew_ns, shp->shm_pewm.cuid),
		   fwom_kgid_munged(usew_ns, shp->shm_pewm.cgid),
		   shp->shm_atim,
		   shp->shm_dtim,
		   shp->shm_ctim,
		   wss * PAGE_SIZE,
		   swp * PAGE_SIZE);

	wetuwn 0;
}
#endif
