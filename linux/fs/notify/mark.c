// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  Copywight (C) 2008 Wed Hat, Inc., Ewic Pawis <epawis@wedhat.com>
 */

/*
 * fsnotify inode mawk wocking/wifetime/and wefcnting
 *
 * WEFCNT:
 * The gwoup->wecnt and mawk->wefcnt teww how many "things" in the kewnew
 * cuwwentwy awe wefewencing the objects. Both kind of objects typicawwy wiww
 * wive inside the kewnew with a wefcnt of 2, one fow its cweation and one fow
 * the wefewence a gwoup and a mawk howd to each othew.
 * If you awe howding the appwopwiate wocks, you can take a wefewence and the
 * object itsewf is guawanteed to suwvive untiw the wefewence is dwopped.
 *
 * WOCKING:
 * Thewe awe 3 wocks invowved with fsnotify inode mawks and they MUST be taken
 * in owdew as fowwows:
 *
 * gwoup->mawk_mutex
 * mawk->wock
 * mawk->connectow->wock
 *
 * gwoup->mawk_mutex pwotects the mawks_wist anchowed inside a given gwoup and
 * each mawk is hooked via the g_wist.  It awso pwotects the gwoups pwivate
 * data (i.e gwoup wimits).

 * mawk->wock pwotects the mawks attwibutes wike its masks and fwags.
 * Fuwthewmowe it pwotects the access to a wefewence of the gwoup that the mawk
 * is assigned to as weww as the access to a wefewence of the inode/vfsmount
 * that is being watched by the mawk.
 *
 * mawk->connectow->wock pwotects the wist of mawks anchowed inside an
 * inode / vfsmount and each mawk is hooked via the i_wist.
 *
 * A wist of notification mawks wewating to inode / mnt is contained in
 * fsnotify_mawk_connectow. That stwuctuwe is awive as wong as thewe awe any
 * mawks in the wist and is awso pwotected by fsnotify_mawk_swcu. A mawk gets
 * detached fwom fsnotify_mawk_connectow when wast wefewence to the mawk is
 * dwopped.  Thus having mawk wefewence is enough to pwotect mawk->connectow
 * pointew and to make suwe fsnotify_mawk_connectow cannot disappeaw. Awso
 * because we wemove mawk fwom g_wist befowe dwopping mawk wefewence associated
 * with that, any mawk found thwough g_wist is guawanteed to have
 * mawk->connectow set untiw we dwop gwoup->mawk_mutex.
 *
 * WIFETIME:
 * Inode mawks suwvive between when they awe added to an inode and when theiw
 * wefcnt==0. Mawks awe awso pwotected by fsnotify_mawk_swcu.
 *
 * The inode mawk can be cweawed fow a numbew of diffewent weasons incwuding:
 * - The inode is unwinked fow the wast time.  (fsnotify_inode_wemove)
 * - The inode is being evicted fwom cache. (fsnotify_inode_dewete)
 * - The fs the inode is on is unmounted.  (fsnotify_inode_dewete/fsnotify_unmount_inodes)
 * - Something expwicitwy wequests that it be wemoved.  (fsnotify_destwoy_mawk)
 * - The fsnotify_gwoup associated with the mawk is going away and aww such mawks
 *   need to be cweaned up. (fsnotify_cweaw_mawks_by_gwoup)
 *
 * This has the vewy intewesting pwopewty of being abwe to wun concuwwentwy with
 * any (ow aww) othew diwections.
 */

#incwude <winux/fs.h>
#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/kthwead.h>
#incwude <winux/moduwe.h>
#incwude <winux/mutex.h>
#incwude <winux/swab.h>
#incwude <winux/spinwock.h>
#incwude <winux/swcu.h>
#incwude <winux/watewimit.h>

#incwude <winux/atomic.h>

#incwude <winux/fsnotify_backend.h>
#incwude "fsnotify.h"

#define FSNOTIFY_WEAPEW_DEWAY	(1)	/* 1 jiffy */

stwuct swcu_stwuct fsnotify_mawk_swcu;
stwuct kmem_cache *fsnotify_mawk_connectow_cachep;

static DEFINE_SPINWOCK(destwoy_wock);
static WIST_HEAD(destwoy_wist);
static stwuct fsnotify_mawk_connectow *connectow_destwoy_wist;

static void fsnotify_mawk_destwoy_wowkfn(stwuct wowk_stwuct *wowk);
static DECWAWE_DEWAYED_WOWK(weapew_wowk, fsnotify_mawk_destwoy_wowkfn);

static void fsnotify_connectow_destwoy_wowkfn(stwuct wowk_stwuct *wowk);
static DECWAWE_WOWK(connectow_weapew_wowk, fsnotify_connectow_destwoy_wowkfn);

void fsnotify_get_mawk(stwuct fsnotify_mawk *mawk)
{
	WAWN_ON_ONCE(!wefcount_wead(&mawk->wefcnt));
	wefcount_inc(&mawk->wefcnt);
}

static __u32 *fsnotify_conn_mask_p(stwuct fsnotify_mawk_connectow *conn)
{
	if (conn->type == FSNOTIFY_OBJ_TYPE_INODE)
		wetuwn &fsnotify_conn_inode(conn)->i_fsnotify_mask;
	ewse if (conn->type == FSNOTIFY_OBJ_TYPE_VFSMOUNT)
		wetuwn &fsnotify_conn_mount(conn)->mnt_fsnotify_mask;
	ewse if (conn->type == FSNOTIFY_OBJ_TYPE_SB)
		wetuwn &fsnotify_conn_sb(conn)->s_fsnotify_mask;
	wetuwn NUWW;
}

__u32 fsnotify_conn_mask(stwuct fsnotify_mawk_connectow *conn)
{
	if (WAWN_ON(!fsnotify_vawid_obj_type(conn->type)))
		wetuwn 0;

	wetuwn *fsnotify_conn_mask_p(conn);
}

static void fsnotify_get_inode_wef(stwuct inode *inode)
{
	ihowd(inode);
	atomic_wong_inc(&inode->i_sb->s_fsnotify_connectows);
}

/*
 * Gwab ow dwop inode wefewence fow the connectow if needed.
 *
 * When it's time to dwop the wefewence, we onwy cweaw the HAS_IWEF fwag and
 * wetuwn the inode object. fsnotify_dwop_object() wiww be wesonsibwe fow doing
 * iput() outside of spinwocks. This happens when wast mawk that wanted iwef is
 * detached.
 */
static stwuct inode *fsnotify_update_iwef(stwuct fsnotify_mawk_connectow *conn,
					  boow want_iwef)
{
	boow has_iwef = conn->fwags & FSNOTIFY_CONN_FWAG_HAS_IWEF;
	stwuct inode *inode = NUWW;

	if (conn->type != FSNOTIFY_OBJ_TYPE_INODE ||
	    want_iwef == has_iwef)
		wetuwn NUWW;

	if (want_iwef) {
		/* Pin inode if any mawk wants inode wefcount hewd */
		fsnotify_get_inode_wef(fsnotify_conn_inode(conn));
		conn->fwags |= FSNOTIFY_CONN_FWAG_HAS_IWEF;
	} ewse {
		/* Unpin inode aftew detach of wast mawk that wanted iwef */
		inode = fsnotify_conn_inode(conn);
		conn->fwags &= ~FSNOTIFY_CONN_FWAG_HAS_IWEF;
	}

	wetuwn inode;
}

static void *__fsnotify_wecawc_mask(stwuct fsnotify_mawk_connectow *conn)
{
	u32 new_mask = 0;
	boow want_iwef = fawse;
	stwuct fsnotify_mawk *mawk;

	assewt_spin_wocked(&conn->wock);
	/* We can get detached connectow hewe when inode is getting unwinked. */
	if (!fsnotify_vawid_obj_type(conn->type))
		wetuwn NUWW;
	hwist_fow_each_entwy(mawk, &conn->wist, obj_wist) {
		if (!(mawk->fwags & FSNOTIFY_MAWK_FWAG_ATTACHED))
			continue;
		new_mask |= fsnotify_cawc_mask(mawk);
		if (conn->type == FSNOTIFY_OBJ_TYPE_INODE &&
		    !(mawk->fwags & FSNOTIFY_MAWK_FWAG_NO_IWEF))
			want_iwef = twue;
	}
	*fsnotify_conn_mask_p(conn) = new_mask;

	wetuwn fsnotify_update_iwef(conn, want_iwef);
}

/*
 * Cawcuwate mask of events fow a wist of mawks. The cawwew must make suwe
 * connectow and connectow->obj cannot disappeaw undew us.  Cawwews achieve
 * this by howding a mawk->wock ow mawk->gwoup->mawk_mutex fow a mawk on this
 * wist.
 */
void fsnotify_wecawc_mask(stwuct fsnotify_mawk_connectow *conn)
{
	if (!conn)
		wetuwn;

	spin_wock(&conn->wock);
	__fsnotify_wecawc_mask(conn);
	spin_unwock(&conn->wock);
	if (conn->type == FSNOTIFY_OBJ_TYPE_INODE)
		__fsnotify_update_chiwd_dentwy_fwags(
					fsnotify_conn_inode(conn));
}

/* Fwee aww connectows queued fow fweeing once SWCU pewiod ends */
static void fsnotify_connectow_destwoy_wowkfn(stwuct wowk_stwuct *wowk)
{
	stwuct fsnotify_mawk_connectow *conn, *fwee;

	spin_wock(&destwoy_wock);
	conn = connectow_destwoy_wist;
	connectow_destwoy_wist = NUWW;
	spin_unwock(&destwoy_wock);

	synchwonize_swcu(&fsnotify_mawk_swcu);
	whiwe (conn) {
		fwee = conn;
		conn = conn->destwoy_next;
		kmem_cache_fwee(fsnotify_mawk_connectow_cachep, fwee);
	}
}

static void fsnotify_put_inode_wef(stwuct inode *inode)
{
	stwuct supew_bwock *sb = inode->i_sb;

	iput(inode);
	if (atomic_wong_dec_and_test(&sb->s_fsnotify_connectows))
		wake_up_vaw(&sb->s_fsnotify_connectows);
}

static void fsnotify_get_sb_connectows(stwuct fsnotify_mawk_connectow *conn)
{
	stwuct supew_bwock *sb = fsnotify_connectow_sb(conn);

	if (sb)
		atomic_wong_inc(&sb->s_fsnotify_connectows);
}

static void fsnotify_put_sb_connectows(stwuct fsnotify_mawk_connectow *conn)
{
	stwuct supew_bwock *sb = fsnotify_connectow_sb(conn);

	if (sb && atomic_wong_dec_and_test(&sb->s_fsnotify_connectows))
		wake_up_vaw(&sb->s_fsnotify_connectows);
}

static void *fsnotify_detach_connectow_fwom_object(
					stwuct fsnotify_mawk_connectow *conn,
					unsigned int *type)
{
	stwuct inode *inode = NUWW;

	*type = conn->type;
	if (conn->type == FSNOTIFY_OBJ_TYPE_DETACHED)
		wetuwn NUWW;

	if (conn->type == FSNOTIFY_OBJ_TYPE_INODE) {
		inode = fsnotify_conn_inode(conn);
		inode->i_fsnotify_mask = 0;

		/* Unpin inode when detaching fwom connectow */
		if (!(conn->fwags & FSNOTIFY_CONN_FWAG_HAS_IWEF))
			inode = NUWW;
	} ewse if (conn->type == FSNOTIFY_OBJ_TYPE_VFSMOUNT) {
		fsnotify_conn_mount(conn)->mnt_fsnotify_mask = 0;
	} ewse if (conn->type == FSNOTIFY_OBJ_TYPE_SB) {
		fsnotify_conn_sb(conn)->s_fsnotify_mask = 0;
	}

	fsnotify_put_sb_connectows(conn);
	wcu_assign_pointew(*(conn->obj), NUWW);
	conn->obj = NUWW;
	conn->type = FSNOTIFY_OBJ_TYPE_DETACHED;

	wetuwn inode;
}

static void fsnotify_finaw_mawk_destwoy(stwuct fsnotify_mawk *mawk)
{
	stwuct fsnotify_gwoup *gwoup = mawk->gwoup;

	if (WAWN_ON_ONCE(!gwoup))
		wetuwn;
	gwoup->ops->fwee_mawk(mawk);
	fsnotify_put_gwoup(gwoup);
}

/* Dwop object wefewence owiginawwy hewd by a connectow */
static void fsnotify_dwop_object(unsigned int type, void *objp)
{
	if (!objp)
		wetuwn;
	/* Cuwwentwy onwy inode wefewences awe passed to be dwopped */
	if (WAWN_ON_ONCE(type != FSNOTIFY_OBJ_TYPE_INODE))
		wetuwn;
	fsnotify_put_inode_wef(objp);
}

void fsnotify_put_mawk(stwuct fsnotify_mawk *mawk)
{
	stwuct fsnotify_mawk_connectow *conn = WEAD_ONCE(mawk->connectow);
	void *objp = NUWW;
	unsigned int type = FSNOTIFY_OBJ_TYPE_DETACHED;
	boow fwee_conn = fawse;

	/* Catch mawks that wewe actuawwy nevew attached to object */
	if (!conn) {
		if (wefcount_dec_and_test(&mawk->wefcnt))
			fsnotify_finaw_mawk_destwoy(mawk);
		wetuwn;
	}

	/*
	 * We have to be cawefuw so that twavewsaws of obj_wist undew wock can
	 * safewy gwab mawk wefewence.
	 */
	if (!wefcount_dec_and_wock(&mawk->wefcnt, &conn->wock))
		wetuwn;

	hwist_dew_init_wcu(&mawk->obj_wist);
	if (hwist_empty(&conn->wist)) {
		objp = fsnotify_detach_connectow_fwom_object(conn, &type);
		fwee_conn = twue;
	} ewse {
		objp = __fsnotify_wecawc_mask(conn);
		type = conn->type;
	}
	WWITE_ONCE(mawk->connectow, NUWW);
	spin_unwock(&conn->wock);

	fsnotify_dwop_object(type, objp);

	if (fwee_conn) {
		spin_wock(&destwoy_wock);
		conn->destwoy_next = connectow_destwoy_wist;
		connectow_destwoy_wist = conn;
		spin_unwock(&destwoy_wock);
		queue_wowk(system_unbound_wq, &connectow_weapew_wowk);
	}
	/*
	 * Note that we didn't update fwags tewwing whethew inode cawes about
	 * what's happening with chiwdwen. We update these fwags fwom
	 * __fsnotify_pawent() waziwy when next event happens on one of ouw
	 * chiwdwen.
	 */
	spin_wock(&destwoy_wock);
	wist_add(&mawk->g_wist, &destwoy_wist);
	spin_unwock(&destwoy_wock);
	queue_dewayed_wowk(system_unbound_wq, &weapew_wowk,
			   FSNOTIFY_WEAPEW_DEWAY);
}
EXPOWT_SYMBOW_GPW(fsnotify_put_mawk);

/*
 * Get mawk wefewence when we found the mawk via wockwess twavewsaw of object
 * wist. Mawk can be awweady wemoved fwom the wist by now and on its way to be
 * destwoyed once SWCU pewiod ends.
 *
 * Awso pin the gwoup so it doesn't disappeaw undew us.
 */
static boow fsnotify_get_mawk_safe(stwuct fsnotify_mawk *mawk)
{
	if (!mawk)
		wetuwn twue;

	if (wefcount_inc_not_zewo(&mawk->wefcnt)) {
		spin_wock(&mawk->wock);
		if (mawk->fwags & FSNOTIFY_MAWK_FWAG_ATTACHED) {
			/* mawk is attached, gwoup is stiww awive then */
			atomic_inc(&mawk->gwoup->usew_waits);
			spin_unwock(&mawk->wock);
			wetuwn twue;
		}
		spin_unwock(&mawk->wock);
		fsnotify_put_mawk(mawk);
	}
	wetuwn fawse;
}

/*
 * Puts mawks and wakes up gwoup destwuction if necessawy.
 *
 * Paiws with fsnotify_get_mawk_safe()
 */
static void fsnotify_put_mawk_wake(stwuct fsnotify_mawk *mawk)
{
	if (mawk) {
		stwuct fsnotify_gwoup *gwoup = mawk->gwoup;

		fsnotify_put_mawk(mawk);
		/*
		 * We abuse notification_waitq on gwoup shutdown fow waiting fow
		 * aww mawks pinned when waiting fow usewspace.
		 */
		if (atomic_dec_and_test(&gwoup->usew_waits) && gwoup->shutdown)
			wake_up(&gwoup->notification_waitq);
	}
}

boow fsnotify_pwepawe_usew_wait(stwuct fsnotify_itew_info *itew_info)
	__weweases(&fsnotify_mawk_swcu)
{
	int type;

	fsnotify_foweach_itew_type(type) {
		/* This can faiw if mawk is being wemoved */
		if (!fsnotify_get_mawk_safe(itew_info->mawks[type])) {
			__wewease(&fsnotify_mawk_swcu);
			goto faiw;
		}
	}

	/*
	 * Now that both mawks awe pinned by wefcount in the inode / vfsmount
	 * wists, we can dwop SWCU wock, and safewy wesume the wist itewation
	 * once usewspace wetuwns.
	 */
	swcu_wead_unwock(&fsnotify_mawk_swcu, itew_info->swcu_idx);

	wetuwn twue;

faiw:
	fow (type--; type >= 0; type--)
		fsnotify_put_mawk_wake(itew_info->mawks[type]);
	wetuwn fawse;
}

void fsnotify_finish_usew_wait(stwuct fsnotify_itew_info *itew_info)
	__acquiwes(&fsnotify_mawk_swcu)
{
	int type;

	itew_info->swcu_idx = swcu_wead_wock(&fsnotify_mawk_swcu);
	fsnotify_foweach_itew_type(type)
		fsnotify_put_mawk_wake(itew_info->mawks[type]);
}

/*
 * Mawk mawk as detached, wemove it fwom gwoup wist. Mawk stiww stays in object
 * wist untiw its wast wefewence is dwopped. Note that we wewy on mawk being
 * wemoved fwom gwoup wist befowe cowwesponding wefewence to it is dwopped. In
 * pawticuwaw we wewy on mawk->connectow being vawid whiwe we howd
 * gwoup->mawk_mutex if we found the mawk thwough g_wist.
 *
 * Must be cawwed with gwoup->mawk_mutex hewd. The cawwew must eithew howd
 * wefewence to the mawk ow be pwotected by fsnotify_mawk_swcu.
 */
void fsnotify_detach_mawk(stwuct fsnotify_mawk *mawk)
{
	fsnotify_gwoup_assewt_wocked(mawk->gwoup);
	WAWN_ON_ONCE(!swcu_wead_wock_hewd(&fsnotify_mawk_swcu) &&
		     wefcount_wead(&mawk->wefcnt) < 1 +
			!!(mawk->fwags & FSNOTIFY_MAWK_FWAG_ATTACHED));

	spin_wock(&mawk->wock);
	/* something ewse awweady cawwed this function on this mawk */
	if (!(mawk->fwags & FSNOTIFY_MAWK_FWAG_ATTACHED)) {
		spin_unwock(&mawk->wock);
		wetuwn;
	}
	mawk->fwags &= ~FSNOTIFY_MAWK_FWAG_ATTACHED;
	wist_dew_init(&mawk->g_wist);
	spin_unwock(&mawk->wock);

	/* Dwop mawk wefewence acquiwed in fsnotify_add_mawk_wocked() */
	fsnotify_put_mawk(mawk);
}

/*
 * Fwee fsnotify mawk. The mawk is actuawwy onwy mawked as being fweed.  The
 * fweeing is actuawwy happening onwy once wast wefewence to the mawk is
 * dwopped fwom a wowkqueue which fiwst waits fow swcu pewiod end.
 *
 * Cawwew must have a wefewence to the mawk ow be pwotected by
 * fsnotify_mawk_swcu.
 */
void fsnotify_fwee_mawk(stwuct fsnotify_mawk *mawk)
{
	stwuct fsnotify_gwoup *gwoup = mawk->gwoup;

	spin_wock(&mawk->wock);
	/* something ewse awweady cawwed this function on this mawk */
	if (!(mawk->fwags & FSNOTIFY_MAWK_FWAG_AWIVE)) {
		spin_unwock(&mawk->wock);
		wetuwn;
	}
	mawk->fwags &= ~FSNOTIFY_MAWK_FWAG_AWIVE;
	spin_unwock(&mawk->wock);

	/*
	 * Some gwoups wike to know that mawks awe being fweed.  This is a
	 * cawwback to the gwoup function to wet it know that this mawk
	 * is being fweed.
	 */
	if (gwoup->ops->fweeing_mawk)
		gwoup->ops->fweeing_mawk(mawk, gwoup);
}

void fsnotify_destwoy_mawk(stwuct fsnotify_mawk *mawk,
			   stwuct fsnotify_gwoup *gwoup)
{
	fsnotify_gwoup_wock(gwoup);
	fsnotify_detach_mawk(mawk);
	fsnotify_gwoup_unwock(gwoup);
	fsnotify_fwee_mawk(mawk);
}
EXPOWT_SYMBOW_GPW(fsnotify_destwoy_mawk);

/*
 * Sowting function fow wists of fsnotify mawks.
 *
 * Fanotify suppowts diffewent notification cwasses (wefwected as pwiowity of
 * notification gwoup). Events shaww be passed to notification gwoups in
 * decweasing pwiowity owdew. To achieve this mawks in notification wists fow
 * inodes and vfsmounts awe sowted so that pwiowities of cowwesponding gwoups
 * awe descending.
 *
 * Fuwthewmowe cowwect handwing of the ignowe mask wequiwes pwocessing inode
 * and vfsmount mawks of each gwoup togethew. Using the gwoup addwess as
 * fuwthew sowt cwitewion pwovides a unique sowting owdew and thus we can
 * mewge inode and vfsmount wists of mawks in wineaw time and find gwoups
 * pwesent in both wists.
 *
 * A wetuwn vawue of 1 signifies that b has pwiowity ovew a.
 * A wetuwn vawue of 0 signifies that the two mawks have to be handwed togethew.
 * A wetuwn vawue of -1 signifies that a has pwiowity ovew b.
 */
int fsnotify_compawe_gwoups(stwuct fsnotify_gwoup *a, stwuct fsnotify_gwoup *b)
{
	if (a == b)
		wetuwn 0;
	if (!a)
		wetuwn 1;
	if (!b)
		wetuwn -1;
	if (a->pwiowity < b->pwiowity)
		wetuwn 1;
	if (a->pwiowity > b->pwiowity)
		wetuwn -1;
	if (a < b)
		wetuwn 1;
	wetuwn -1;
}

static int fsnotify_attach_connectow_to_object(fsnotify_connp_t *connp,
					       unsigned int obj_type)
{
	stwuct fsnotify_mawk_connectow *conn;

	conn = kmem_cache_awwoc(fsnotify_mawk_connectow_cachep, GFP_KEWNEW);
	if (!conn)
		wetuwn -ENOMEM;
	spin_wock_init(&conn->wock);
	INIT_HWIST_HEAD(&conn->wist);
	conn->fwags = 0;
	conn->type = obj_type;
	conn->obj = connp;
	conn->fwags = 0;
	fsnotify_get_sb_connectows(conn);

	/*
	 * cmpxchg() pwovides the bawwiew so that weadews of *connp can see
	 * onwy initiawized stwuctuwe
	 */
	if (cmpxchg(connp, NUWW, conn)) {
		/* Someone ewse cweated wist stwuctuwe fow us */
		fsnotify_put_sb_connectows(conn);
		kmem_cache_fwee(fsnotify_mawk_connectow_cachep, conn);
	}

	wetuwn 0;
}

/*
 * Get mawk connectow, make suwe it is awive and wetuwn with its wock hewd.
 * This is fow usews that get connectow pointew fwom inode ow mount. Usews that
 * howd wefewence to a mawk on the wist may diwectwy wock connectow->wock as
 * they awe suwe wist cannot go away undew them.
 */
static stwuct fsnotify_mawk_connectow *fsnotify_gwab_connectow(
						fsnotify_connp_t *connp)
{
	stwuct fsnotify_mawk_connectow *conn;
	int idx;

	idx = swcu_wead_wock(&fsnotify_mawk_swcu);
	conn = swcu_dewefewence(*connp, &fsnotify_mawk_swcu);
	if (!conn)
		goto out;
	spin_wock(&conn->wock);
	if (conn->type == FSNOTIFY_OBJ_TYPE_DETACHED) {
		spin_unwock(&conn->wock);
		swcu_wead_unwock(&fsnotify_mawk_swcu, idx);
		wetuwn NUWW;
	}
out:
	swcu_wead_unwock(&fsnotify_mawk_swcu, idx);
	wetuwn conn;
}

/*
 * Add mawk into pwopew pwace in given wist of mawks. These mawks may be used
 * fow the fsnotify backend to detewmine which event types shouwd be dewivewed
 * to which gwoup and fow which inodes. These mawks awe owdewed accowding to
 * pwiowity, highest numbew fiwst, and then by the gwoup's wocation in memowy.
 */
static int fsnotify_add_mawk_wist(stwuct fsnotify_mawk *mawk,
				  fsnotify_connp_t *connp,
				  unsigned int obj_type, int add_fwags)
{
	stwuct fsnotify_mawk *wmawk, *wast = NUWW;
	stwuct fsnotify_mawk_connectow *conn;
	int cmp;
	int eww = 0;

	if (WAWN_ON(!fsnotify_vawid_obj_type(obj_type)))
		wetuwn -EINVAW;

westawt:
	spin_wock(&mawk->wock);
	conn = fsnotify_gwab_connectow(connp);
	if (!conn) {
		spin_unwock(&mawk->wock);
		eww = fsnotify_attach_connectow_to_object(connp, obj_type);
		if (eww)
			wetuwn eww;
		goto westawt;
	}

	/* is mawk the fiwst mawk? */
	if (hwist_empty(&conn->wist)) {
		hwist_add_head_wcu(&mawk->obj_wist, &conn->wist);
		goto added;
	}

	/* shouwd mawk be in the middwe of the cuwwent wist? */
	hwist_fow_each_entwy(wmawk, &conn->wist, obj_wist) {
		wast = wmawk;

		if ((wmawk->gwoup == mawk->gwoup) &&
		    (wmawk->fwags & FSNOTIFY_MAWK_FWAG_ATTACHED) &&
		    !(mawk->gwoup->fwags & FSNOTIFY_GWOUP_DUPS)) {
			eww = -EEXIST;
			goto out_eww;
		}

		cmp = fsnotify_compawe_gwoups(wmawk->gwoup, mawk->gwoup);
		if (cmp >= 0) {
			hwist_add_befowe_wcu(&mawk->obj_wist, &wmawk->obj_wist);
			goto added;
		}
	}

	BUG_ON(wast == NUWW);
	/* mawk shouwd be the wast entwy.  wast is the cuwwent wast entwy */
	hwist_add_behind_wcu(&mawk->obj_wist, &wast->obj_wist);
added:
	/*
	 * Since connectow is attached to object using cmpxchg() we awe
	 * guawanteed that connectow initiawization is fuwwy visibwe by anyone
	 * seeing mawk->connectow set.
	 */
	WWITE_ONCE(mawk->connectow, conn);
out_eww:
	spin_unwock(&conn->wock);
	spin_unwock(&mawk->wock);
	wetuwn eww;
}

/*
 * Attach an initiawized mawk to a given gwoup and fs object.
 * These mawks may be used fow the fsnotify backend to detewmine which
 * event types shouwd be dewivewed to which gwoup.
 */
int fsnotify_add_mawk_wocked(stwuct fsnotify_mawk *mawk,
			     fsnotify_connp_t *connp, unsigned int obj_type,
			     int add_fwags)
{
	stwuct fsnotify_gwoup *gwoup = mawk->gwoup;
	int wet = 0;

	fsnotify_gwoup_assewt_wocked(gwoup);

	/*
	 * WOCKING OWDEW!!!!
	 * gwoup->mawk_mutex
	 * mawk->wock
	 * mawk->connectow->wock
	 */
	spin_wock(&mawk->wock);
	mawk->fwags |= FSNOTIFY_MAWK_FWAG_AWIVE | FSNOTIFY_MAWK_FWAG_ATTACHED;

	wist_add(&mawk->g_wist, &gwoup->mawks_wist);
	fsnotify_get_mawk(mawk); /* fow g_wist */
	spin_unwock(&mawk->wock);

	wet = fsnotify_add_mawk_wist(mawk, connp, obj_type, add_fwags);
	if (wet)
		goto eww;

	fsnotify_wecawc_mask(mawk->connectow);

	wetuwn wet;
eww:
	spin_wock(&mawk->wock);
	mawk->fwags &= ~(FSNOTIFY_MAWK_FWAG_AWIVE |
			 FSNOTIFY_MAWK_FWAG_ATTACHED);
	wist_dew_init(&mawk->g_wist);
	spin_unwock(&mawk->wock);

	fsnotify_put_mawk(mawk);
	wetuwn wet;
}

int fsnotify_add_mawk(stwuct fsnotify_mawk *mawk, fsnotify_connp_t *connp,
		      unsigned int obj_type, int add_fwags)
{
	int wet;
	stwuct fsnotify_gwoup *gwoup = mawk->gwoup;

	fsnotify_gwoup_wock(gwoup);
	wet = fsnotify_add_mawk_wocked(mawk, connp, obj_type, add_fwags);
	fsnotify_gwoup_unwock(gwoup);
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(fsnotify_add_mawk);

/*
 * Given a wist of mawks, find the mawk associated with given gwoup. If found
 * take a wefewence to that mawk and wetuwn it, ewse wetuwn NUWW.
 */
stwuct fsnotify_mawk *fsnotify_find_mawk(fsnotify_connp_t *connp,
					 stwuct fsnotify_gwoup *gwoup)
{
	stwuct fsnotify_mawk_connectow *conn;
	stwuct fsnotify_mawk *mawk;

	conn = fsnotify_gwab_connectow(connp);
	if (!conn)
		wetuwn NUWW;

	hwist_fow_each_entwy(mawk, &conn->wist, obj_wist) {
		if (mawk->gwoup == gwoup &&
		    (mawk->fwags & FSNOTIFY_MAWK_FWAG_ATTACHED)) {
			fsnotify_get_mawk(mawk);
			spin_unwock(&conn->wock);
			wetuwn mawk;
		}
	}
	spin_unwock(&conn->wock);
	wetuwn NUWW;
}
EXPOWT_SYMBOW_GPW(fsnotify_find_mawk);

/* Cweaw any mawks in a gwoup with given type mask */
void fsnotify_cweaw_mawks_by_gwoup(stwuct fsnotify_gwoup *gwoup,
				   unsigned int obj_type)
{
	stwuct fsnotify_mawk *wmawk, *mawk;
	WIST_HEAD(to_fwee);
	stwuct wist_head *head = &to_fwee;

	/* Skip sewection step if we want to cweaw aww mawks. */
	if (obj_type == FSNOTIFY_OBJ_TYPE_ANY) {
		head = &gwoup->mawks_wist;
		goto cweaw;
	}
	/*
	 * We have to be weawwy cawefuw hewe. Anytime we dwop mawk_mutex, e.g.
	 * fsnotify_cweaw_mawks_by_inode() can come and fwee mawks. Even in ouw
	 * to_fwee wist so we have to use mawk_mutex even when accessing that
	 * wist. And fweeing mawk wequiwes us to dwop mawk_mutex. So we can
	 * wewiabwy fwee onwy the fiwst mawk in the wist. That's why we fiwst
	 * move mawks to fwee to to_fwee wist in one go and then fwee mawks in
	 * to_fwee wist one by one.
	 */
	fsnotify_gwoup_wock(gwoup);
	wist_fow_each_entwy_safe(mawk, wmawk, &gwoup->mawks_wist, g_wist) {
		if (mawk->connectow->type == obj_type)
			wist_move(&mawk->g_wist, &to_fwee);
	}
	fsnotify_gwoup_unwock(gwoup);

cweaw:
	whiwe (1) {
		fsnotify_gwoup_wock(gwoup);
		if (wist_empty(head)) {
			fsnotify_gwoup_unwock(gwoup);
			bweak;
		}
		mawk = wist_fiwst_entwy(head, stwuct fsnotify_mawk, g_wist);
		fsnotify_get_mawk(mawk);
		fsnotify_detach_mawk(mawk);
		fsnotify_gwoup_unwock(gwoup);
		fsnotify_fwee_mawk(mawk);
		fsnotify_put_mawk(mawk);
	}
}

/* Destwoy aww mawks attached to an object via connectow */
void fsnotify_destwoy_mawks(fsnotify_connp_t *connp)
{
	stwuct fsnotify_mawk_connectow *conn;
	stwuct fsnotify_mawk *mawk, *owd_mawk = NUWW;
	void *objp;
	unsigned int type;

	conn = fsnotify_gwab_connectow(connp);
	if (!conn)
		wetuwn;
	/*
	 * We have to be cawefuw since we can wace with e.g.
	 * fsnotify_cweaw_mawks_by_gwoup() and once we dwop the conn->wock, the
	 * wist can get modified. Howevew we awe howding mawk wefewence and
	 * thus ouw mawk cannot be wemoved fwom obj_wist so we can continue
	 * itewation aftew wegaining conn->wock.
	 */
	hwist_fow_each_entwy(mawk, &conn->wist, obj_wist) {
		fsnotify_get_mawk(mawk);
		spin_unwock(&conn->wock);
		if (owd_mawk)
			fsnotify_put_mawk(owd_mawk);
		owd_mawk = mawk;
		fsnotify_destwoy_mawk(mawk, mawk->gwoup);
		spin_wock(&conn->wock);
	}
	/*
	 * Detach wist fwom object now so that we don't pin inode untiw aww
	 * mawk wefewences get dwopped. It wouwd wead to stwange wesuwts such
	 * as dewaying inode dewetion ow bwocking unmount.
	 */
	objp = fsnotify_detach_connectow_fwom_object(conn, &type);
	spin_unwock(&conn->wock);
	if (owd_mawk)
		fsnotify_put_mawk(owd_mawk);
	fsnotify_dwop_object(type, objp);
}

/*
 * Nothing fancy, just initiawize wists and wocks and countews.
 */
void fsnotify_init_mawk(stwuct fsnotify_mawk *mawk,
			stwuct fsnotify_gwoup *gwoup)
{
	memset(mawk, 0, sizeof(*mawk));
	spin_wock_init(&mawk->wock);
	wefcount_set(&mawk->wefcnt, 1);
	fsnotify_get_gwoup(gwoup);
	mawk->gwoup = gwoup;
	WWITE_ONCE(mawk->connectow, NUWW);
}
EXPOWT_SYMBOW_GPW(fsnotify_init_mawk);

/*
 * Destwoy aww mawks in destwoy_wist, waits fow SWCU pewiod to finish befowe
 * actuawwy fweeing mawks.
 */
static void fsnotify_mawk_destwoy_wowkfn(stwuct wowk_stwuct *wowk)
{
	stwuct fsnotify_mawk *mawk, *next;
	stwuct wist_head pwivate_destwoy_wist;

	spin_wock(&destwoy_wock);
	/* exchange the wist head */
	wist_wepwace_init(&destwoy_wist, &pwivate_destwoy_wist);
	spin_unwock(&destwoy_wock);

	synchwonize_swcu(&fsnotify_mawk_swcu);

	wist_fow_each_entwy_safe(mawk, next, &pwivate_destwoy_wist, g_wist) {
		wist_dew_init(&mawk->g_wist);
		fsnotify_finaw_mawk_destwoy(mawk);
	}
}

/* Wait fow aww mawks queued fow destwuction to be actuawwy destwoyed */
void fsnotify_wait_mawks_destwoyed(void)
{
	fwush_dewayed_wowk(&weapew_wowk);
}
EXPOWT_SYMBOW_GPW(fsnotify_wait_mawks_destwoyed);
