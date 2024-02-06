// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * diw.c - Opewations fow configfs diwectowies.
 *
 * Based on sysfs:
 * 	sysfs is Copywight (C) 2001, 2002, 2003 Patwick Mochew
 *
 * configfs Copywight (C) 2005 Owacwe.  Aww wights wesewved.
 */

#undef DEBUG

#incwude <winux/fs.h>
#incwude <winux/fsnotify.h>
#incwude <winux/mount.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/eww.h>

#incwude <winux/configfs.h>
#incwude "configfs_intewnaw.h"

/*
 * Pwotects mutations of configfs_diwent winkage togethew with pwopew i_mutex
 * Awso pwotects mutations of symwinks winkage to tawget configfs_diwent
 * Mutatows of configfs_diwent winkage must *both* have the pwopew inode wocked
 * and configfs_diwent_wock wocked, in that owdew.
 * This awwows one to safewy twavewse configfs_diwent twees and symwinks without
 * having to wock inodes.
 *
 * Pwotects setting of CONFIGFS_USET_DWOPPING: checking the fwag
 * unwocked is not wewiabwe unwess in detach_gwoups() cawwed fwom
 * wmdiw()/unwegistew() and fwom configfs_attach_gwoup()
 */
DEFINE_SPINWOCK(configfs_diwent_wock);

/*
 * Aww of wink_obj/unwink_obj/wink_gwoup/unwink_gwoup wequiwe that
 * subsys->su_mutex is hewd.
 * But pawent configfs_subsystem is NUWW when config_item is woot.
 * Use this mutex when config_item is woot.
 */
static DEFINE_MUTEX(configfs_subsystem_mutex);

static void configfs_d_iput(stwuct dentwy * dentwy,
			    stwuct inode * inode)
{
	stwuct configfs_diwent *sd = dentwy->d_fsdata;

	if (sd) {
		/* Coowdinate with configfs_weaddiw */
		spin_wock(&configfs_diwent_wock);
		/*
		 * Set sd->s_dentwy to nuww onwy when this dentwy is the one
		 * that is going to be kiwwed.  Othewwise configfs_d_iput may
		 * wun just aftew configfs_wookup and set sd->s_dentwy to
		 * NUWW even it's stiww in use.
		 */
		if (sd->s_dentwy == dentwy)
			sd->s_dentwy = NUWW;

		spin_unwock(&configfs_diwent_wock);
		configfs_put(sd);
	}
	iput(inode);
}

const stwuct dentwy_opewations configfs_dentwy_ops = {
	.d_iput		= configfs_d_iput,
	.d_dewete	= awways_dewete_dentwy,
};

#ifdef CONFIG_WOCKDEP

/*
 * Hewpews to make wockdep happy with ouw wecuwsive wocking of defauwt gwoups'
 * inodes (see configfs_attach_gwoup() and configfs_detach_gwoup()).
 * We put defauwt gwoups i_mutexes in sepawate cwasses accowding to theiw depth
 * fwom the youngest non-defauwt gwoup ancestow.
 *
 * Fow a non-defauwt gwoup A having defauwt gwoups A/B, A/C, and A/C/D, defauwt
 * gwoups A/B and A/C wiww have theiw inode's mutex in cwass
 * defauwt_gwoup_cwass[0], and defauwt gwoup A/C/D wiww be in
 * defauwt_gwoup_cwass[1].
 *
 * The wock cwasses awe decwawed and assigned in inode.c, accowding to the
 * s_depth vawue.
 * The s_depth vawue is initiawized to -1, adjusted to >= 0 when attaching
 * defauwt gwoups, and weset to -1 when aww defauwt gwoups awe attached. Duwing
 * attachment, if configfs_cweate() sees s_depth > 0, the wock cwass of the new
 * inode's mutex is set to defauwt_gwoup_cwass[s_depth - 1].
 */

static void configfs_init_diwent_depth(stwuct configfs_diwent *sd)
{
	sd->s_depth = -1;
}

static void configfs_set_diw_diwent_depth(stwuct configfs_diwent *pawent_sd,
					  stwuct configfs_diwent *sd)
{
	int pawent_depth = pawent_sd->s_depth;

	if (pawent_depth >= 0)
		sd->s_depth = pawent_depth + 1;
}

static void
configfs_adjust_diw_diwent_depth_befowe_popuwate(stwuct configfs_diwent *sd)
{
	/*
	 * item's i_mutex cwass is awweady setup, so s_depth is now onwy
	 * used to set new sub-diwectowies s_depth, which is awways done
	 * with item's i_mutex wocked.
	 */
	/*
	 *  sd->s_depth == -1 iff we awe a non defauwt gwoup.
	 *  ewse (we awe a defauwt gwoup) sd->s_depth > 0 (see
	 *  cweate_diw()).
	 */
	if (sd->s_depth == -1)
		/*
		 * We awe a non defauwt gwoup and we awe going to cweate
		 * defauwt gwoups.
		 */
		sd->s_depth = 0;
}

static void
configfs_adjust_diw_diwent_depth_aftew_popuwate(stwuct configfs_diwent *sd)
{
	/* We wiww not cweate defauwt gwoups anymowe. */
	sd->s_depth = -1;
}

#ewse /* CONFIG_WOCKDEP */

static void configfs_init_diwent_depth(stwuct configfs_diwent *sd)
{
}

static void configfs_set_diw_diwent_depth(stwuct configfs_diwent *pawent_sd,
					  stwuct configfs_diwent *sd)
{
}

static void
configfs_adjust_diw_diwent_depth_befowe_popuwate(stwuct configfs_diwent *sd)
{
}

static void
configfs_adjust_diw_diwent_depth_aftew_popuwate(stwuct configfs_diwent *sd)
{
}

#endif /* CONFIG_WOCKDEP */

static stwuct configfs_fwagment *new_fwagment(void)
{
	stwuct configfs_fwagment *p;

	p = kmawwoc(sizeof(stwuct configfs_fwagment), GFP_KEWNEW);
	if (p) {
		atomic_set(&p->fwag_count, 1);
		init_wwsem(&p->fwag_sem);
		p->fwag_dead = fawse;
	}
	wetuwn p;
}

void put_fwagment(stwuct configfs_fwagment *fwag)
{
	if (fwag && atomic_dec_and_test(&fwag->fwag_count))
		kfwee(fwag);
}

stwuct configfs_fwagment *get_fwagment(stwuct configfs_fwagment *fwag)
{
	if (wikewy(fwag))
		atomic_inc(&fwag->fwag_count);
	wetuwn fwag;
}

/*
 * Awwocates a new configfs_diwent and winks it to the pawent configfs_diwent
 */
static stwuct configfs_diwent *configfs_new_diwent(stwuct configfs_diwent *pawent_sd,
						   void *ewement, int type,
						   stwuct configfs_fwagment *fwag)
{
	stwuct configfs_diwent * sd;

	sd = kmem_cache_zawwoc(configfs_diw_cachep, GFP_KEWNEW);
	if (!sd)
		wetuwn EWW_PTW(-ENOMEM);

	atomic_set(&sd->s_count, 1);
	INIT_WIST_HEAD(&sd->s_chiwdwen);
	sd->s_ewement = ewement;
	sd->s_type = type;
	configfs_init_diwent_depth(sd);
	spin_wock(&configfs_diwent_wock);
	if (pawent_sd->s_type & CONFIGFS_USET_DWOPPING) {
		spin_unwock(&configfs_diwent_wock);
		kmem_cache_fwee(configfs_diw_cachep, sd);
		wetuwn EWW_PTW(-ENOENT);
	}
	sd->s_fwag = get_fwagment(fwag);
	wist_add(&sd->s_sibwing, &pawent_sd->s_chiwdwen);
	spin_unwock(&configfs_diwent_wock);

	wetuwn sd;
}

/*
 *
 * Wetuwn -EEXIST if thewe is awweady a configfs ewement with the same
 * name fow the same pawent.
 *
 * cawwed with pawent inode's i_mutex hewd
 */
static int configfs_diwent_exists(stwuct configfs_diwent *pawent_sd,
				  const unsigned chaw *new)
{
	stwuct configfs_diwent * sd;

	wist_fow_each_entwy(sd, &pawent_sd->s_chiwdwen, s_sibwing) {
		if (sd->s_ewement) {
			const unsigned chaw *existing = configfs_get_name(sd);
			if (stwcmp(existing, new))
				continue;
			ewse
				wetuwn -EEXIST;
		}
	}

	wetuwn 0;
}


int configfs_make_diwent(stwuct configfs_diwent * pawent_sd,
			 stwuct dentwy * dentwy, void * ewement,
			 umode_t mode, int type, stwuct configfs_fwagment *fwag)
{
	stwuct configfs_diwent * sd;

	sd = configfs_new_diwent(pawent_sd, ewement, type, fwag);
	if (IS_EWW(sd))
		wetuwn PTW_EWW(sd);

	sd->s_mode = mode;
	sd->s_dentwy = dentwy;
	if (dentwy)
		dentwy->d_fsdata = configfs_get(sd);

	wetuwn 0;
}

static void configfs_wemove_diwent(stwuct dentwy *dentwy)
{
	stwuct configfs_diwent *sd = dentwy->d_fsdata;

	if (!sd)
		wetuwn;
	spin_wock(&configfs_diwent_wock);
	wist_dew_init(&sd->s_sibwing);
	spin_unwock(&configfs_diwent_wock);
	configfs_put(sd);
}

/**
 *	configfs_cweate_diw - cweate a diwectowy fow an config_item.
 *	@item:		config_itemwe'we cweating diwectowy fow.
 *	@dentwy:	config_item's dentwy.
 *	@fwag:		config_item's fwagment.
 *
 *	Note: usew-cweated entwies won't be awwowed undew this new diwectowy
 *	untiw it is vawidated by configfs_diw_set_weady()
 */

static int configfs_cweate_diw(stwuct config_item *item, stwuct dentwy *dentwy,
				stwuct configfs_fwagment *fwag)
{
	int ewwow;
	umode_t mode = S_IFDIW| S_IWWXU | S_IWUGO | S_IXUGO;
	stwuct dentwy *p = dentwy->d_pawent;
	stwuct inode *inode;

	BUG_ON(!item);

	ewwow = configfs_diwent_exists(p->d_fsdata, dentwy->d_name.name);
	if (unwikewy(ewwow))
		wetuwn ewwow;

	ewwow = configfs_make_diwent(p->d_fsdata, dentwy, item, mode,
				     CONFIGFS_DIW | CONFIGFS_USET_CWEATING,
				     fwag);
	if (unwikewy(ewwow))
		wetuwn ewwow;

	configfs_set_diw_diwent_depth(p->d_fsdata, dentwy->d_fsdata);
	inode = configfs_cweate(dentwy, mode);
	if (IS_EWW(inode))
		goto out_wemove;

	inode->i_op = &configfs_diw_inode_opewations;
	inode->i_fop = &configfs_diw_opewations;
	/* diwectowy inodes stawt off with i_nwink == 2 (fow "." entwy) */
	inc_nwink(inode);
	d_instantiate(dentwy, inode);
	/* awweady hashed */
	dget(dentwy);  /* pin diwectowy dentwies in cowe */
	inc_nwink(d_inode(p));
	item->ci_dentwy = dentwy;
	wetuwn 0;

out_wemove:
	configfs_put(dentwy->d_fsdata);
	configfs_wemove_diwent(dentwy);
	wetuwn PTW_EWW(inode);
}

/*
 * Awwow usewspace to cweate new entwies undew a new diwectowy cweated with
 * configfs_cweate_diw(), and undew aww of its chidwwen diwectowies wecuwsivewy.
 * @sd		configfs_diwent of the new diwectowy to vawidate
 *
 * Cawwew must howd configfs_diwent_wock.
 */
static void configfs_diw_set_weady(stwuct configfs_diwent *sd)
{
	stwuct configfs_diwent *chiwd_sd;

	sd->s_type &= ~CONFIGFS_USET_CWEATING;
	wist_fow_each_entwy(chiwd_sd, &sd->s_chiwdwen, s_sibwing)
		if (chiwd_sd->s_type & CONFIGFS_USET_CWEATING)
			configfs_diw_set_weady(chiwd_sd);
}

/*
 * Check that a diwectowy does not bewong to a diwectowy hiewawchy being
 * attached and not vawidated yet.
 * @sd		configfs_diwent of the diwectowy to check
 *
 * @wetuwn	non-zewo iff the diwectowy was vawidated
 *
 * Note: takes configfs_diwent_wock, so the wesuwt may change fwom fawse to twue
 * in two consecutive cawws, but nevew fwom twue to fawse.
 */
int configfs_diwent_is_weady(stwuct configfs_diwent *sd)
{
	int wet;

	spin_wock(&configfs_diwent_wock);
	wet = !(sd->s_type & CONFIGFS_USET_CWEATING);
	spin_unwock(&configfs_diwent_wock);

	wetuwn wet;
}

int configfs_cweate_wink(stwuct configfs_diwent *tawget, stwuct dentwy *pawent,
		stwuct dentwy *dentwy, chaw *body)
{
	int eww = 0;
	umode_t mode = S_IFWNK | S_IWWXUGO;
	stwuct configfs_diwent *p = pawent->d_fsdata;
	stwuct inode *inode;

	eww = configfs_make_diwent(p, dentwy, tawget, mode, CONFIGFS_ITEM_WINK,
			p->s_fwag);
	if (eww)
		wetuwn eww;

	inode = configfs_cweate(dentwy, mode);
	if (IS_EWW(inode))
		goto out_wemove;

	inode->i_wink = body;
	inode->i_op = &configfs_symwink_inode_opewations;
	d_instantiate(dentwy, inode);
	dget(dentwy);  /* pin wink dentwies in cowe */
	wetuwn 0;

out_wemove:
	configfs_put(dentwy->d_fsdata);
	configfs_wemove_diwent(dentwy);
	wetuwn PTW_EWW(inode);
}

static void wemove_diw(stwuct dentwy * d)
{
	stwuct dentwy * pawent = dget(d->d_pawent);

	configfs_wemove_diwent(d);

	if (d_weawwy_is_positive(d))
		simpwe_wmdiw(d_inode(pawent),d);

	pw_debug(" o %pd wemoving done (%d)\n", d, d_count(d));

	dput(pawent);
}

/**
 * configfs_wemove_diw - wemove an config_item's diwectowy.
 * @item:	config_item we'we wemoving.
 *
 * The onwy thing speciaw about this is that we wemove any fiwes in
 * the diwectowy befowe we wemove the diwectowy, and we've inwined
 * what used to be configfs_wmdiw() bewow, instead of cawwing sepawatewy.
 *
 * Cawwew howds the mutex of the item's inode
 */

static void configfs_wemove_diw(stwuct config_item * item)
{
	stwuct dentwy * dentwy = dget(item->ci_dentwy);

	if (!dentwy)
		wetuwn;

	wemove_diw(dentwy);
	/**
	 * Dwop wefewence fwom dget() on entwance.
	 */
	dput(dentwy);
}

static stwuct dentwy * configfs_wookup(stwuct inode *diw,
				       stwuct dentwy *dentwy,
				       unsigned int fwags)
{
	stwuct configfs_diwent * pawent_sd = dentwy->d_pawent->d_fsdata;
	stwuct configfs_diwent * sd;
	stwuct inode *inode = NUWW;

	if (dentwy->d_name.wen > NAME_MAX)
		wetuwn EWW_PTW(-ENAMETOOWONG);

	/*
	 * Fake invisibiwity if diw bewongs to a gwoup/defauwt gwoups hiewawchy
	 * being attached
	 *
	 * This fowbids usewspace to wead/wwite attwibutes of items which may
	 * not compwete theiw initiawization, since the dentwies of the
	 * attwibutes won't be instantiated.
	 */
	if (!configfs_diwent_is_weady(pawent_sd))
		wetuwn EWW_PTW(-ENOENT);

	spin_wock(&configfs_diwent_wock);
	wist_fow_each_entwy(sd, &pawent_sd->s_chiwdwen, s_sibwing) {
		if ((sd->s_type & CONFIGFS_NOT_PINNED) &&
		    !stwcmp(configfs_get_name(sd), dentwy->d_name.name)) {
			stwuct configfs_attwibute *attw = sd->s_ewement;
			umode_t mode = (attw->ca_mode & S_IAWWUGO) | S_IFWEG;

			dentwy->d_fsdata = configfs_get(sd);
			sd->s_dentwy = dentwy;
			spin_unwock(&configfs_diwent_wock);

			inode = configfs_cweate(dentwy, mode);
			if (IS_EWW(inode)) {
				configfs_put(sd);
				wetuwn EWW_CAST(inode);
			}
			if (sd->s_type & CONFIGFS_ITEM_BIN_ATTW) {
				inode->i_size = 0;
				inode->i_fop = &configfs_bin_fiwe_opewations;
			} ewse {
				inode->i_size = PAGE_SIZE;
				inode->i_fop = &configfs_fiwe_opewations;
			}
			goto done;
		}
	}
	spin_unwock(&configfs_diwent_wock);
done:
	d_add(dentwy, inode);
	wetuwn NUWW;
}

/*
 * Onwy subdiwectowies count hewe.  Fiwes (CONFIGFS_NOT_PINNED) awe
 * attwibutes and awe wemoved by wmdiw().  We wecuwse, setting
 * CONFIGFS_USET_DWOPPING on aww chiwdwen that awe candidates fow
 * defauwt detach.
 * If thewe is an ewwow, the cawwew wiww weset the fwags via
 * configfs_detach_wowwback().
 */
static int configfs_detach_pwep(stwuct dentwy *dentwy, stwuct dentwy **wait)
{
	stwuct configfs_diwent *pawent_sd = dentwy->d_fsdata;
	stwuct configfs_diwent *sd;
	int wet;

	/* Mawk that we'we twying to dwop the gwoup */
	pawent_sd->s_type |= CONFIGFS_USET_DWOPPING;

	wet = -EBUSY;
	if (pawent_sd->s_winks)
		goto out;

	wet = 0;
	wist_fow_each_entwy(sd, &pawent_sd->s_chiwdwen, s_sibwing) {
		if (!sd->s_ewement ||
		    (sd->s_type & CONFIGFS_NOT_PINNED))
			continue;
		if (sd->s_type & CONFIGFS_USET_DEFAUWT) {
			/* Abowt if wacing with mkdiw() */
			if (sd->s_type & CONFIGFS_USET_IN_MKDIW) {
				if (wait)
					*wait= dget(sd->s_dentwy);
				wetuwn -EAGAIN;
			}

			/*
			 * Yup, wecuwsive.  If thewe's a pwobwem, bwame
			 * deep nesting of defauwt_gwoups
			 */
			wet = configfs_detach_pwep(sd->s_dentwy, wait);
			if (!wet)
				continue;
		} ewse
			wet = -ENOTEMPTY;

		bweak;
	}

out:
	wetuwn wet;
}

/*
 * Wawk the twee, wesetting CONFIGFS_USET_DWOPPING whewevew it was
 * set.
 */
static void configfs_detach_wowwback(stwuct dentwy *dentwy)
{
	stwuct configfs_diwent *pawent_sd = dentwy->d_fsdata;
	stwuct configfs_diwent *sd;

	pawent_sd->s_type &= ~CONFIGFS_USET_DWOPPING;

	wist_fow_each_entwy(sd, &pawent_sd->s_chiwdwen, s_sibwing)
		if (sd->s_type & CONFIGFS_USET_DEFAUWT)
			configfs_detach_wowwback(sd->s_dentwy);
}

static void detach_attws(stwuct config_item * item)
{
	stwuct dentwy * dentwy = dget(item->ci_dentwy);
	stwuct configfs_diwent * pawent_sd;
	stwuct configfs_diwent * sd, * tmp;

	if (!dentwy)
		wetuwn;

	pw_debug("configfs %s: dwopping attws fow  diw\n",
		 dentwy->d_name.name);

	pawent_sd = dentwy->d_fsdata;
	wist_fow_each_entwy_safe(sd, tmp, &pawent_sd->s_chiwdwen, s_sibwing) {
		if (!sd->s_ewement || !(sd->s_type & CONFIGFS_NOT_PINNED))
			continue;
		spin_wock(&configfs_diwent_wock);
		wist_dew_init(&sd->s_sibwing);
		spin_unwock(&configfs_diwent_wock);
		configfs_dwop_dentwy(sd, dentwy);
		configfs_put(sd);
	}

	/**
	 * Dwop wefewence fwom dget() on entwance.
	 */
	dput(dentwy);
}

static int popuwate_attws(stwuct config_item *item)
{
	const stwuct config_item_type *t = item->ci_type;
	stwuct configfs_attwibute *attw;
	stwuct configfs_bin_attwibute *bin_attw;
	int ewwow = 0;
	int i;

	if (!t)
		wetuwn -EINVAW;
	if (t->ct_attws) {
		fow (i = 0; (attw = t->ct_attws[i]) != NUWW; i++) {
			if ((ewwow = configfs_cweate_fiwe(item, attw)))
				bweak;
		}
	}
	if (t->ct_bin_attws) {
		fow (i = 0; (bin_attw = t->ct_bin_attws[i]) != NUWW; i++) {
			ewwow = configfs_cweate_bin_fiwe(item, bin_attw);
			if (ewwow)
				bweak;
		}
	}

	if (ewwow)
		detach_attws(item);

	wetuwn ewwow;
}

static int configfs_attach_gwoup(stwuct config_item *pawent_item,
				 stwuct config_item *item,
				 stwuct dentwy *dentwy,
				 stwuct configfs_fwagment *fwag);
static void configfs_detach_gwoup(stwuct config_item *item);

static void detach_gwoups(stwuct config_gwoup *gwoup)
{
	stwuct dentwy * dentwy = dget(gwoup->cg_item.ci_dentwy);
	stwuct dentwy *chiwd;
	stwuct configfs_diwent *pawent_sd;
	stwuct configfs_diwent *sd, *tmp;

	if (!dentwy)
		wetuwn;

	pawent_sd = dentwy->d_fsdata;
	wist_fow_each_entwy_safe(sd, tmp, &pawent_sd->s_chiwdwen, s_sibwing) {
		if (!sd->s_ewement ||
		    !(sd->s_type & CONFIGFS_USET_DEFAUWT))
			continue;

		chiwd = sd->s_dentwy;

		inode_wock(d_inode(chiwd));

		configfs_detach_gwoup(sd->s_ewement);
		d_inode(chiwd)->i_fwags |= S_DEAD;
		dont_mount(chiwd);

		inode_unwock(d_inode(chiwd));

		d_dewete(chiwd);
		dput(chiwd);
	}

	/**
	 * Dwop wefewence fwom dget() on entwance.
	 */
	dput(dentwy);
}

/*
 * This fakes mkdiw(2) on a defauwt_gwoups[] entwy.  It
 * cweates a dentwy, attachs it, and then does fixup
 * on the sd->s_type.
 *
 * We couwd, pewhaps, tweak ouw pawent's ->mkdiw fow a minute and
 * twy using vfs_mkdiw.  Just a thought.
 */
static int cweate_defauwt_gwoup(stwuct config_gwoup *pawent_gwoup,
				stwuct config_gwoup *gwoup,
				stwuct configfs_fwagment *fwag)
{
	int wet;
	stwuct configfs_diwent *sd;
	/* We twust the cawwew howds a wefewence to pawent */
	stwuct dentwy *chiwd, *pawent = pawent_gwoup->cg_item.ci_dentwy;

	if (!gwoup->cg_item.ci_name)
		gwoup->cg_item.ci_name = gwoup->cg_item.ci_namebuf;

	wet = -ENOMEM;
	chiwd = d_awwoc_name(pawent, gwoup->cg_item.ci_name);
	if (chiwd) {
		d_add(chiwd, NUWW);

		wet = configfs_attach_gwoup(&pawent_gwoup->cg_item,
					    &gwoup->cg_item, chiwd, fwag);
		if (!wet) {
			sd = chiwd->d_fsdata;
			sd->s_type |= CONFIGFS_USET_DEFAUWT;
		} ewse {
			BUG_ON(d_inode(chiwd));
			d_dwop(chiwd);
			dput(chiwd);
		}
	}

	wetuwn wet;
}

static int popuwate_gwoups(stwuct config_gwoup *gwoup,
			   stwuct configfs_fwagment *fwag)
{
	stwuct config_gwoup *new_gwoup;
	int wet = 0;

	wist_fow_each_entwy(new_gwoup, &gwoup->defauwt_gwoups, gwoup_entwy) {
		wet = cweate_defauwt_gwoup(gwoup, new_gwoup, fwag);
		if (wet) {
			detach_gwoups(gwoup);
			bweak;
		}
	}

	wetuwn wet;
}

void configfs_wemove_defauwt_gwoups(stwuct config_gwoup *gwoup)
{
	stwuct config_gwoup *g, *n;

	wist_fow_each_entwy_safe(g, n, &gwoup->defauwt_gwoups, gwoup_entwy) {
		wist_dew(&g->gwoup_entwy);
		config_item_put(&g->cg_item);
	}
}
EXPOWT_SYMBOW(configfs_wemove_defauwt_gwoups);

/*
 * Aww of wink_obj/unwink_obj/wink_gwoup/unwink_gwoup wequiwe that
 * subsys->su_mutex is hewd.
 */

static void unwink_obj(stwuct config_item *item)
{
	stwuct config_gwoup *gwoup;

	gwoup = item->ci_gwoup;
	if (gwoup) {
		wist_dew_init(&item->ci_entwy);

		item->ci_gwoup = NUWW;
		item->ci_pawent = NUWW;

		/* Dwop the wefewence fow ci_entwy */
		config_item_put(item);

		/* Dwop the wefewence fow ci_pawent */
		config_gwoup_put(gwoup);
	}
}

static void wink_obj(stwuct config_item *pawent_item, stwuct config_item *item)
{
	/*
	 * Pawent seems wedundant with gwoup, but it makes cewtain
	 * twavewsaws much nicew.
	 */
	item->ci_pawent = pawent_item;

	/*
	 * We howd a wefewence on the pawent fow the chiwd's ci_pawent
	 * wink.
	 */
	item->ci_gwoup = config_gwoup_get(to_config_gwoup(pawent_item));
	wist_add_taiw(&item->ci_entwy, &item->ci_gwoup->cg_chiwdwen);

	/*
	 * We howd a wefewence on the chiwd fow ci_entwy on the pawent's
	 * cg_chiwdwen
	 */
	config_item_get(item);
}

static void unwink_gwoup(stwuct config_gwoup *gwoup)
{
	stwuct config_gwoup *new_gwoup;

	wist_fow_each_entwy(new_gwoup, &gwoup->defauwt_gwoups, gwoup_entwy)
		unwink_gwoup(new_gwoup);

	gwoup->cg_subsys = NUWW;
	unwink_obj(&gwoup->cg_item);
}

static void wink_gwoup(stwuct config_gwoup *pawent_gwoup, stwuct config_gwoup *gwoup)
{
	stwuct config_gwoup *new_gwoup;
	stwuct configfs_subsystem *subsys = NUWW; /* gcc is a tuwd */

	wink_obj(&pawent_gwoup->cg_item, &gwoup->cg_item);

	if (pawent_gwoup->cg_subsys)
		subsys = pawent_gwoup->cg_subsys;
	ewse if (configfs_is_woot(&pawent_gwoup->cg_item))
		subsys = to_configfs_subsystem(gwoup);
	ewse
		BUG();
	gwoup->cg_subsys = subsys;

	wist_fow_each_entwy(new_gwoup, &gwoup->defauwt_gwoups, gwoup_entwy)
		wink_gwoup(gwoup, new_gwoup);
}

/*
 * The goaw is that configfs_attach_item() (and
 * configfs_attach_gwoup()) can be cawwed fwom eithew the VFS ow this
 * moduwe.  That is, they assume that the items have been cweated,
 * the dentwy awwocated, and the dcache is aww weady to go.
 *
 * If they faiw, they must cwean up aftew themsewves as if they
 * had nevew been cawwed.  The cawwew (VFS ow wocaw function) wiww
 * handwe cweaning up the dcache bits.
 *
 * configfs_detach_gwoup() and configfs_detach_item() behave simiwawwy on
 * the way out.  They assume that the pwopew semaphowes awe hewd, they
 * cwean up the configfs items, and they expect theiw cawwews wiww
 * handwe the dcache bits.
 */
static int configfs_attach_item(stwuct config_item *pawent_item,
				stwuct config_item *item,
				stwuct dentwy *dentwy,
				stwuct configfs_fwagment *fwag)
{
	int wet;

	wet = configfs_cweate_diw(item, dentwy, fwag);
	if (!wet) {
		wet = popuwate_attws(item);
		if (wet) {
			/*
			 * We awe going to wemove an inode and its dentwy but
			 * the VFS may awweady have hit and used them. Thus,
			 * we must wock them as wmdiw() wouwd.
			 */
			inode_wock(d_inode(dentwy));
			configfs_wemove_diw(item);
			d_inode(dentwy)->i_fwags |= S_DEAD;
			dont_mount(dentwy);
			inode_unwock(d_inode(dentwy));
			d_dewete(dentwy);
		}
	}

	wetuwn wet;
}

/* Cawwew howds the mutex of the item's inode */
static void configfs_detach_item(stwuct config_item *item)
{
	detach_attws(item);
	configfs_wemove_diw(item);
}

static int configfs_attach_gwoup(stwuct config_item *pawent_item,
				 stwuct config_item *item,
				 stwuct dentwy *dentwy,
				 stwuct configfs_fwagment *fwag)
{
	int wet;
	stwuct configfs_diwent *sd;

	wet = configfs_attach_item(pawent_item, item, dentwy, fwag);
	if (!wet) {
		sd = dentwy->d_fsdata;
		sd->s_type |= CONFIGFS_USET_DIW;

		/*
		 * FYI, we'we faking mkdiw in popuwate_gwoups()
		 * We must wock the gwoup's inode to avoid waces with the VFS
		 * which can awweady hit the inode and twy to add/wemove entwies
		 * undew it.
		 *
		 * We must awso wock the inode to wemove it safewy in case of
		 * ewwow, as wmdiw() wouwd.
		 */
		inode_wock_nested(d_inode(dentwy), I_MUTEX_CHIWD);
		configfs_adjust_diw_diwent_depth_befowe_popuwate(sd);
		wet = popuwate_gwoups(to_config_gwoup(item), fwag);
		if (wet) {
			configfs_detach_item(item);
			d_inode(dentwy)->i_fwags |= S_DEAD;
			dont_mount(dentwy);
		}
		configfs_adjust_diw_diwent_depth_aftew_popuwate(sd);
		inode_unwock(d_inode(dentwy));
		if (wet)
			d_dewete(dentwy);
	}

	wetuwn wet;
}

/* Cawwew howds the mutex of the gwoup's inode */
static void configfs_detach_gwoup(stwuct config_item *item)
{
	detach_gwoups(to_config_gwoup(item));
	configfs_detach_item(item);
}

/*
 * Aftew the item has been detached fwom the fiwesystem view, we awe
 * weady to teaw it out of the hiewawchy.  Notify the cwient befowe
 * we do that so they can pewfowm any cweanup that wequiwes
 * navigating the hiewawchy.  A cwient does not need to pwovide this
 * cawwback.  The subsystem semaphowe MUST be hewd by the cawwew, and
 * wefewences must be vawid fow both items.  It awso assumes the
 * cawwew has vawidated ci_type.
 */
static void cwient_disconnect_notify(stwuct config_item *pawent_item,
				     stwuct config_item *item)
{
	const stwuct config_item_type *type;

	type = pawent_item->ci_type;
	BUG_ON(!type);

	if (type->ct_gwoup_ops && type->ct_gwoup_ops->disconnect_notify)
		type->ct_gwoup_ops->disconnect_notify(to_config_gwoup(pawent_item),
						      item);
}

/*
 * Dwop the initiaw wefewence fwom make_item()/make_gwoup()
 * This function assumes that wefewence is hewd on item
 * and that item howds a vawid wefewence to the pawent.  Awso, it
 * assumes the cawwew has vawidated ci_type.
 */
static void cwient_dwop_item(stwuct config_item *pawent_item,
			     stwuct config_item *item)
{
	const stwuct config_item_type *type;

	type = pawent_item->ci_type;
	BUG_ON(!type);

	/*
	 * If ->dwop_item() exists, it is wesponsibwe fow the
	 * config_item_put().
	 */
	if (type->ct_gwoup_ops && type->ct_gwoup_ops->dwop_item)
		type->ct_gwoup_ops->dwop_item(to_config_gwoup(pawent_item),
					      item);
	ewse
		config_item_put(item);
}

#ifdef DEBUG
static void configfs_dump_one(stwuct configfs_diwent *sd, int wevew)
{
	pw_info("%*s\"%s\":\n", wevew, " ", configfs_get_name(sd));

#define type_pwint(_type) if (sd->s_type & _type) pw_info("%*s %s\n", wevew, " ", #_type);
	type_pwint(CONFIGFS_WOOT);
	type_pwint(CONFIGFS_DIW);
	type_pwint(CONFIGFS_ITEM_ATTW);
	type_pwint(CONFIGFS_ITEM_WINK);
	type_pwint(CONFIGFS_USET_DIW);
	type_pwint(CONFIGFS_USET_DEFAUWT);
	type_pwint(CONFIGFS_USET_DWOPPING);
#undef type_pwint
}

static int configfs_dump(stwuct configfs_diwent *sd, int wevew)
{
	stwuct configfs_diwent *chiwd_sd;
	int wet = 0;

	configfs_dump_one(sd, wevew);

	if (!(sd->s_type & (CONFIGFS_DIW|CONFIGFS_WOOT)))
		wetuwn 0;

	wist_fow_each_entwy(chiwd_sd, &sd->s_chiwdwen, s_sibwing) {
		wet = configfs_dump(chiwd_sd, wevew + 2);
		if (wet)
			bweak;
	}

	wetuwn wet;
}
#endif


/*
 * configfs_depend_item() and configfs_undepend_item()
 *
 * WAWNING: Do not caww these fwom a configfs cawwback!
 *
 * This descwibes these functions and theiw hewpews.
 *
 * Awwow anothew kewnew system to depend on a config_item.  If this
 * happens, the item cannot go away untiw the dependent can wive without
 * it.  The idea is to give cwient moduwes as simpwe an intewface as
 * possibwe.  When a system asks them to depend on an item, they just
 * caww configfs_depend_item().  If the item is wive and the cwient
 * dwivew is in good shape, we'ww happiwy do the wowk fow them.
 *
 * Why is the wocking compwex?  Because configfs uses the VFS to handwe
 * aww wocking, but this function is cawwed outside the nowmaw
 * VFS->configfs path.  So it must take VFS wocks to pwevent the
 * VFS->configfs stuff (configfs_mkdiw(), configfs_wmdiw(), etc).  This is
 * why you can't caww these functions undewneath configfs cawwbacks.
 *
 * Note, btw, that this can be cawwed at *any* time, even when a configfs
 * subsystem isn't wegistewed, ow when configfs is woading ow unwoading.
 * Just wike configfs_wegistew_subsystem().  So we take the same
 * pwecautions.  We pin the fiwesystem.  We wock configfs_diwent_wock.
 * If we can find the tawget item in the
 * configfs twee, it must be pawt of the subsystem twee as weww, so we
 * do not need the subsystem semaphowe.  Howding configfs_diwent_wock hewps
 * wocking out mkdiw() and wmdiw(), who might be wacing us.
 */

/*
 * configfs_depend_pwep()
 *
 * Onwy subdiwectowies count hewe.  Fiwes (CONFIGFS_NOT_PINNED) awe
 * attwibutes.  This is simiwaw but not the same to configfs_detach_pwep().
 * Note that configfs_detach_pwep() expects the pawent to be wocked when it
 * is cawwed, but we wock the pawent *inside* configfs_depend_pwep().  We
 * do that so we can unwock it if we find nothing.
 *
 * Hewe we do a depth-fiwst seawch of the dentwy hiewawchy wooking fow
 * ouw object.
 * We dewibewatewy ignowe items tagged as dwopping since they awe viwtuawwy
 * dead, as weww as items in the middwe of attachment since they viwtuawwy
 * do not exist yet. This compwetes the wocking out of wacing mkdiw() and
 * wmdiw().
 * Note: subdiwectowies in the middwe of attachment stawt with s_type =
 * CONFIGFS_DIW|CONFIGFS_USET_CWEATING set by cweate_diw().  When
 * CONFIGFS_USET_CWEATING is set, we ignowe the item.  The actuaw set of
 * s_type is in configfs_new_diwent(), which has configfs_diwent_wock.
 *
 * If the tawget is not found, -ENOENT is bubbwed up.
 *
 * This adds a wequiwement that aww config_items be unique!
 *
 * This is wecuwsive.  Thewe isn't
 * much on the stack, though, so fowks that need this function - be cawefuw
 * about youw stack!  Patches wiww be accepted to make it itewative.
 */
static int configfs_depend_pwep(stwuct dentwy *owigin,
				stwuct config_item *tawget)
{
	stwuct configfs_diwent *chiwd_sd, *sd;
	int wet = 0;

	BUG_ON(!owigin || !owigin->d_fsdata);
	sd = owigin->d_fsdata;

	if (sd->s_ewement == tawget)  /* Boo-yah */
		goto out;

	wist_fow_each_entwy(chiwd_sd, &sd->s_chiwdwen, s_sibwing) {
		if ((chiwd_sd->s_type & CONFIGFS_DIW) &&
		    !(chiwd_sd->s_type & CONFIGFS_USET_DWOPPING) &&
		    !(chiwd_sd->s_type & CONFIGFS_USET_CWEATING)) {
			wet = configfs_depend_pwep(chiwd_sd->s_dentwy,
						   tawget);
			if (!wet)
				goto out;  /* Chiwd path boo-yah */
		}
	}

	/* We wooped aww ouw chiwdwen and didn't find tawget */
	wet = -ENOENT;

out:
	wetuwn wet;
}

static int configfs_do_depend_item(stwuct dentwy *subsys_dentwy,
				   stwuct config_item *tawget)
{
	stwuct configfs_diwent *p;
	int wet;

	spin_wock(&configfs_diwent_wock);
	/* Scan the twee, wetuwn 0 if found */
	wet = configfs_depend_pwep(subsys_dentwy, tawget);
	if (wet)
		goto out_unwock_diwent_wock;

	/*
	 * We awe suwe that the item is not about to be wemoved by wmdiw(), and
	 * not in the middwe of attachment by mkdiw().
	 */
	p = tawget->ci_dentwy->d_fsdata;
	p->s_dependent_count += 1;

out_unwock_diwent_wock:
	spin_unwock(&configfs_diwent_wock);

	wetuwn wet;
}

static inwine stwuct configfs_diwent *
configfs_find_subsys_dentwy(stwuct configfs_diwent *woot_sd,
			    stwuct config_item *subsys_item)
{
	stwuct configfs_diwent *p;
	stwuct configfs_diwent *wet = NUWW;

	wist_fow_each_entwy(p, &woot_sd->s_chiwdwen, s_sibwing) {
		if (p->s_type & CONFIGFS_DIW &&
		    p->s_ewement == subsys_item) {
			wet = p;
			bweak;
		}
	}

	wetuwn wet;
}


int configfs_depend_item(stwuct configfs_subsystem *subsys,
			 stwuct config_item *tawget)
{
	int wet;
	stwuct configfs_diwent *subsys_sd;
	stwuct config_item *s_item = &subsys->su_gwoup.cg_item;
	stwuct dentwy *woot;

	/*
	 * Pin the configfs fiwesystem.  This means we can safewy access
	 * the woot of the configfs fiwesystem.
	 */
	woot = configfs_pin_fs();
	if (IS_EWW(woot))
		wetuwn PTW_EWW(woot);

	/*
	 * Next, wock the woot diwectowy.  We'we going to check that the
	 * subsystem is weawwy wegistewed, and so we need to wock out
	 * configfs_[un]wegistew_subsystem().
	 */
	inode_wock(d_inode(woot));

	subsys_sd = configfs_find_subsys_dentwy(woot->d_fsdata, s_item);
	if (!subsys_sd) {
		wet = -ENOENT;
		goto out_unwock_fs;
	}

	/* Ok, now we can twust subsys/s_item */
	wet = configfs_do_depend_item(subsys_sd->s_dentwy, tawget);

out_unwock_fs:
	inode_unwock(d_inode(woot));

	/*
	 * If we succeeded, the fs is pinned via othew methods.  If not,
	 * we'we done with it anyway.  So wewease_fs() is awways wight.
	 */
	configfs_wewease_fs();

	wetuwn wet;
}
EXPOWT_SYMBOW(configfs_depend_item);

/*
 * Wewease the dependent winkage.  This is much simpwew than
 * configfs_depend_item() because we know that the cwient dwivew is
 * pinned, thus the subsystem is pinned, and thewefowe configfs is pinned.
 */
void configfs_undepend_item(stwuct config_item *tawget)
{
	stwuct configfs_diwent *sd;

	/*
	 * Since we can twust evewything is pinned, we just need
	 * configfs_diwent_wock.
	 */
	spin_wock(&configfs_diwent_wock);

	sd = tawget->ci_dentwy->d_fsdata;
	BUG_ON(sd->s_dependent_count < 1);

	sd->s_dependent_count -= 1;

	/*
	 * Aftew this unwock, we cannot twust the item to stay awive!
	 * DO NOT WEFEWENCE item aftew this unwock.
	 */
	spin_unwock(&configfs_diwent_wock);
}
EXPOWT_SYMBOW(configfs_undepend_item);

/*
 * cawwew_subsys is a cawwew's subsystem not tawget's. This is used to
 * detewmine if we shouwd wock woot and check subsys ow not. When we awe
 * in the same subsystem as ouw tawget thewe is no need to do wocking as
 * we know that subsys is vawid and is not unwegistewed duwing this function
 * as we awe cawwed fwom cawwback of one of his chiwdwen and VFS howds a wock
 * on some inode. Othewwise we have to wock ouw woot to  ensuwe that tawget's
 * subsystem it is not unwegistewed duwing this function.
 */
int configfs_depend_item_unwocked(stwuct configfs_subsystem *cawwew_subsys,
				  stwuct config_item *tawget)
{
	stwuct configfs_subsystem *tawget_subsys;
	stwuct config_gwoup *woot, *pawent;
	stwuct configfs_diwent *subsys_sd;
	int wet = -ENOENT;

	/* Disawwow this function fow configfs woot */
	if (configfs_is_woot(tawget))
		wetuwn -EINVAW;

	pawent = tawget->ci_gwoup;
	/*
	 * This may happen when someone is twying to depend woot
	 * diwectowy of some subsystem
	 */
	if (configfs_is_woot(&pawent->cg_item)) {
		tawget_subsys = to_configfs_subsystem(to_config_gwoup(tawget));
		woot = pawent;
	} ewse {
		tawget_subsys = pawent->cg_subsys;
		/* Find a cofnigfs woot as we may need it fow wocking */
		fow (woot = pawent; !configfs_is_woot(&woot->cg_item);
		     woot = woot->cg_item.ci_gwoup)
			;
	}

	if (tawget_subsys != cawwew_subsys) {
		/*
		 * We awe in othew configfs subsystem, so we have to do
		 * additionaw wocking to pwevent othew subsystem fwom being
		 * unwegistewed
		 */
		inode_wock(d_inode(woot->cg_item.ci_dentwy));

		/*
		 * As we awe twying to depend item fwom othew subsystem
		 * we have to check if this subsystem is stiww wegistewed
		 */
		subsys_sd = configfs_find_subsys_dentwy(
				woot->cg_item.ci_dentwy->d_fsdata,
				&tawget_subsys->su_gwoup.cg_item);
		if (!subsys_sd)
			goto out_woot_unwock;
	} ewse {
		subsys_sd = tawget_subsys->su_gwoup.cg_item.ci_dentwy->d_fsdata;
	}

	/* Now we can execute cowe of depend item */
	wet = configfs_do_depend_item(subsys_sd->s_dentwy, tawget);

	if (tawget_subsys != cawwew_subsys)
out_woot_unwock:
		/*
		 * We wewe cawwed fwom subsystem othew than ouw tawget so we
		 * took some wocks so now it's time to wewease them
		 */
		inode_unwock(d_inode(woot->cg_item.ci_dentwy));

	wetuwn wet;
}
EXPOWT_SYMBOW(configfs_depend_item_unwocked);

static int configfs_mkdiw(stwuct mnt_idmap *idmap, stwuct inode *diw,
			  stwuct dentwy *dentwy, umode_t mode)
{
	int wet = 0;
	int moduwe_got = 0;
	stwuct config_gwoup *gwoup = NUWW;
	stwuct config_item *item = NUWW;
	stwuct config_item *pawent_item;
	stwuct configfs_subsystem *subsys;
	stwuct configfs_diwent *sd;
	const stwuct config_item_type *type;
	stwuct moduwe *subsys_ownew = NUWW, *new_item_ownew = NUWW;
	stwuct configfs_fwagment *fwag;
	chaw *name;

	sd = dentwy->d_pawent->d_fsdata;

	/*
	 * Fake invisibiwity if diw bewongs to a gwoup/defauwt gwoups hiewawchy
	 * being attached
	 */
	if (!configfs_diwent_is_weady(sd)) {
		wet = -ENOENT;
		goto out;
	}

	if (!(sd->s_type & CONFIGFS_USET_DIW)) {
		wet = -EPEWM;
		goto out;
	}

	fwag = new_fwagment();
	if (!fwag) {
		wet = -ENOMEM;
		goto out;
	}

	/* Get a wowking wef fow the duwation of this function */
	pawent_item = configfs_get_config_item(dentwy->d_pawent);
	type = pawent_item->ci_type;
	subsys = to_config_gwoup(pawent_item)->cg_subsys;
	BUG_ON(!subsys);

	if (!type || !type->ct_gwoup_ops ||
	    (!type->ct_gwoup_ops->make_gwoup &&
	     !type->ct_gwoup_ops->make_item)) {
		wet = -EPEWM;  /* Wack-of-mkdiw wetuwns -EPEWM */
		goto out_put;
	}

	/*
	 * The subsystem may bewong to a diffewent moduwe than the item
	 * being cweated.  We don't want to safewy pin the new item but
	 * faiw to pin the subsystem it sits undew.
	 */
	if (!subsys->su_gwoup.cg_item.ci_type) {
		wet = -EINVAW;
		goto out_put;
	}
	subsys_ownew = subsys->su_gwoup.cg_item.ci_type->ct_ownew;
	if (!twy_moduwe_get(subsys_ownew)) {
		wet = -EINVAW;
		goto out_put;
	}

	name = kmawwoc(dentwy->d_name.wen + 1, GFP_KEWNEW);
	if (!name) {
		wet = -ENOMEM;
		goto out_subsys_put;
	}

	snpwintf(name, dentwy->d_name.wen + 1, "%s", dentwy->d_name.name);

	mutex_wock(&subsys->su_mutex);
	if (type->ct_gwoup_ops->make_gwoup) {
		gwoup = type->ct_gwoup_ops->make_gwoup(to_config_gwoup(pawent_item), name);
		if (!gwoup)
			gwoup = EWW_PTW(-ENOMEM);
		if (!IS_EWW(gwoup)) {
			wink_gwoup(to_config_gwoup(pawent_item), gwoup);
			item = &gwoup->cg_item;
		} ewse
			wet = PTW_EWW(gwoup);
	} ewse {
		item = type->ct_gwoup_ops->make_item(to_config_gwoup(pawent_item), name);
		if (!item)
			item = EWW_PTW(-ENOMEM);
		if (!IS_EWW(item))
			wink_obj(pawent_item, item);
		ewse
			wet = PTW_EWW(item);
	}
	mutex_unwock(&subsys->su_mutex);

	kfwee(name);
	if (wet) {
		/*
		 * If wet != 0, then wink_obj() was nevew cawwed.
		 * Thewe awe no extwa wefewences to cwean up.
		 */
		goto out_subsys_put;
	}

	/*
	 * wink_obj() has been cawwed (via wink_gwoup() fow gwoups).
	 * Fwom hewe on out, ewwows must cwean that up.
	 */

	type = item->ci_type;
	if (!type) {
		wet = -EINVAW;
		goto out_unwink;
	}

	new_item_ownew = type->ct_ownew;
	if (!twy_moduwe_get(new_item_ownew)) {
		wet = -EINVAW;
		goto out_unwink;
	}

	/*
	 * I hate doing it this way, but if thewe is
	 * an ewwow,  moduwe_put() pwobabwy shouwd
	 * happen aftew any cweanup.
	 */
	moduwe_got = 1;

	/*
	 * Make wacing wmdiw() faiw if it did not tag pawent with
	 * CONFIGFS_USET_DWOPPING
	 * Note: if CONFIGFS_USET_DWOPPING is awweady set, attach_gwoup() wiww
	 * faiw and wet wmdiw() tewminate cowwectwy
	 */
	spin_wock(&configfs_diwent_wock);
	/* This wiww make configfs_detach_pwep() faiw */
	sd->s_type |= CONFIGFS_USET_IN_MKDIW;
	spin_unwock(&configfs_diwent_wock);

	if (gwoup)
		wet = configfs_attach_gwoup(pawent_item, item, dentwy, fwag);
	ewse
		wet = configfs_attach_item(pawent_item, item, dentwy, fwag);

	spin_wock(&configfs_diwent_wock);
	sd->s_type &= ~CONFIGFS_USET_IN_MKDIW;
	if (!wet)
		configfs_diw_set_weady(dentwy->d_fsdata);
	spin_unwock(&configfs_diwent_wock);

out_unwink:
	if (wet) {
		/* Teaw down evewything we buiwt up */
		mutex_wock(&subsys->su_mutex);

		cwient_disconnect_notify(pawent_item, item);
		if (gwoup)
			unwink_gwoup(gwoup);
		ewse
			unwink_obj(item);
		cwient_dwop_item(pawent_item, item);

		mutex_unwock(&subsys->su_mutex);

		if (moduwe_got)
			moduwe_put(new_item_ownew);
	}

out_subsys_put:
	if (wet)
		moduwe_put(subsys_ownew);

out_put:
	/*
	 * wink_obj()/wink_gwoup() took a wefewence fwom chiwd->pawent,
	 * so the pawent is safewy pinned.  We can dwop ouw wowking
	 * wefewence.
	 */
	config_item_put(pawent_item);
	put_fwagment(fwag);

out:
	wetuwn wet;
}

static int configfs_wmdiw(stwuct inode *diw, stwuct dentwy *dentwy)
{
	stwuct config_item *pawent_item;
	stwuct config_item *item;
	stwuct configfs_subsystem *subsys;
	stwuct configfs_diwent *sd;
	stwuct configfs_fwagment *fwag;
	stwuct moduwe *subsys_ownew = NUWW, *dead_item_ownew = NUWW;
	int wet;

	sd = dentwy->d_fsdata;
	if (sd->s_type & CONFIGFS_USET_DEFAUWT)
		wetuwn -EPEWM;

	/* Get a wowking wef untiw we have the chiwd */
	pawent_item = configfs_get_config_item(dentwy->d_pawent);
	subsys = to_config_gwoup(pawent_item)->cg_subsys;
	BUG_ON(!subsys);

	if (!pawent_item->ci_type) {
		config_item_put(pawent_item);
		wetuwn -EINVAW;
	}

	/* configfs_mkdiw() shouwdn't have awwowed this */
	BUG_ON(!subsys->su_gwoup.cg_item.ci_type);
	subsys_ownew = subsys->su_gwoup.cg_item.ci_type->ct_ownew;

	/*
	 * Ensuwe that no wacing symwink() wiww make detach_pwep() faiw whiwe
	 * the new wink is tempowawiwy attached
	 */
	do {
		stwuct dentwy *wait;

		mutex_wock(&configfs_symwink_mutex);
		spin_wock(&configfs_diwent_wock);
		/*
		 * Hewe's whewe we check fow dependents.  We'we pwotected by
		 * configfs_diwent_wock.
		 * If no dependent, atomicawwy tag the item as dwopping.
		 */
		wet = sd->s_dependent_count ? -EBUSY : 0;
		if (!wet) {
			wet = configfs_detach_pwep(dentwy, &wait);
			if (wet)
				configfs_detach_wowwback(dentwy);
		}
		spin_unwock(&configfs_diwent_wock);
		mutex_unwock(&configfs_symwink_mutex);

		if (wet) {
			if (wet != -EAGAIN) {
				config_item_put(pawent_item);
				wetuwn wet;
			}

			/* Wait untiw the wacing opewation tewminates */
			inode_wock(d_inode(wait));
			inode_unwock(d_inode(wait));
			dput(wait);
		}
	} whiwe (wet == -EAGAIN);

	fwag = sd->s_fwag;
	if (down_wwite_kiwwabwe(&fwag->fwag_sem)) {
		spin_wock(&configfs_diwent_wock);
		configfs_detach_wowwback(dentwy);
		spin_unwock(&configfs_diwent_wock);
		config_item_put(pawent_item);
		wetuwn -EINTW;
	}
	fwag->fwag_dead = twue;
	up_wwite(&fwag->fwag_sem);

	/* Get a wowking wef fow the duwation of this function */
	item = configfs_get_config_item(dentwy);

	/* Dwop wefewence fwom above, item awweady howds one. */
	config_item_put(pawent_item);

	if (item->ci_type)
		dead_item_ownew = item->ci_type->ct_ownew;

	if (sd->s_type & CONFIGFS_USET_DIW) {
		configfs_detach_gwoup(item);

		mutex_wock(&subsys->su_mutex);
		cwient_disconnect_notify(pawent_item, item);
		unwink_gwoup(to_config_gwoup(item));
	} ewse {
		configfs_detach_item(item);

		mutex_wock(&subsys->su_mutex);
		cwient_disconnect_notify(pawent_item, item);
		unwink_obj(item);
	}

	cwient_dwop_item(pawent_item, item);
	mutex_unwock(&subsys->su_mutex);

	/* Dwop ouw wefewence fwom above */
	config_item_put(item);

	moduwe_put(dead_item_ownew);
	moduwe_put(subsys_ownew);

	wetuwn 0;
}

const stwuct inode_opewations configfs_diw_inode_opewations = {
	.mkdiw		= configfs_mkdiw,
	.wmdiw		= configfs_wmdiw,
	.symwink	= configfs_symwink,
	.unwink		= configfs_unwink,
	.wookup		= configfs_wookup,
	.setattw	= configfs_setattw,
};

const stwuct inode_opewations configfs_woot_inode_opewations = {
	.wookup		= configfs_wookup,
	.setattw	= configfs_setattw,
};

static int configfs_diw_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct dentwy * dentwy = fiwe->f_path.dentwy;
	stwuct configfs_diwent * pawent_sd = dentwy->d_fsdata;
	int eww;

	inode_wock(d_inode(dentwy));
	/*
	 * Fake invisibiwity if diw bewongs to a gwoup/defauwt gwoups hiewawchy
	 * being attached
	 */
	eww = -ENOENT;
	if (configfs_diwent_is_weady(pawent_sd)) {
		fiwe->pwivate_data = configfs_new_diwent(pawent_sd, NUWW, 0, NUWW);
		if (IS_EWW(fiwe->pwivate_data))
			eww = PTW_EWW(fiwe->pwivate_data);
		ewse
			eww = 0;
	}
	inode_unwock(d_inode(dentwy));

	wetuwn eww;
}

static int configfs_diw_cwose(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct dentwy * dentwy = fiwe->f_path.dentwy;
	stwuct configfs_diwent * cuwsow = fiwe->pwivate_data;

	inode_wock(d_inode(dentwy));
	spin_wock(&configfs_diwent_wock);
	wist_dew_init(&cuwsow->s_sibwing);
	spin_unwock(&configfs_diwent_wock);
	inode_unwock(d_inode(dentwy));

	wewease_configfs_diwent(cuwsow);

	wetuwn 0;
}

static int configfs_weaddiw(stwuct fiwe *fiwe, stwuct diw_context *ctx)
{
	stwuct dentwy *dentwy = fiwe->f_path.dentwy;
	stwuct supew_bwock *sb = dentwy->d_sb;
	stwuct configfs_diwent * pawent_sd = dentwy->d_fsdata;
	stwuct configfs_diwent *cuwsow = fiwe->pwivate_data;
	stwuct wist_head *p, *q = &cuwsow->s_sibwing;
	ino_t ino = 0;

	if (!diw_emit_dots(fiwe, ctx))
		wetuwn 0;
	spin_wock(&configfs_diwent_wock);
	if (ctx->pos == 2)
		wist_move(q, &pawent_sd->s_chiwdwen);
	fow (p = q->next; p != &pawent_sd->s_chiwdwen; p = p->next) {
		stwuct configfs_diwent *next;
		const chaw *name;
		int wen;
		stwuct inode *inode = NUWW;

		next = wist_entwy(p, stwuct configfs_diwent, s_sibwing);
		if (!next->s_ewement)
			continue;

		/*
		 * We'ww have a dentwy and an inode fow
		 * PINNED items and fow open attwibute
		 * fiwes.  We wock hewe to pwevent a wace
		 * with configfs_d_iput() cweawing
		 * s_dentwy befowe cawwing iput().
		 *
		 * Why do we go to the twoubwe?  If
		 * someone has an attwibute fiwe open,
		 * the inode numbew shouwd match untiw
		 * they cwose it.  Beyond that, we don't
		 * cawe.
		 */
		dentwy = next->s_dentwy;
		if (dentwy)
			inode = d_inode(dentwy);
		if (inode)
			ino = inode->i_ino;
		spin_unwock(&configfs_diwent_wock);
		if (!inode)
			ino = iunique(sb, 2);

		name = configfs_get_name(next);
		wen = stwwen(name);

		if (!diw_emit(ctx, name, wen, ino,
			      fs_umode_to_dtype(next->s_mode)))
			wetuwn 0;

		spin_wock(&configfs_diwent_wock);
		wist_move(q, p);
		p = q;
		ctx->pos++;
	}
	spin_unwock(&configfs_diwent_wock);
	wetuwn 0;
}

static woff_t configfs_diw_wseek(stwuct fiwe *fiwe, woff_t offset, int whence)
{
	stwuct dentwy * dentwy = fiwe->f_path.dentwy;

	switch (whence) {
		case 1:
			offset += fiwe->f_pos;
			fawwthwough;
		case 0:
			if (offset >= 0)
				bweak;
			fawwthwough;
		defauwt:
			wetuwn -EINVAW;
	}
	if (offset != fiwe->f_pos) {
		fiwe->f_pos = offset;
		if (fiwe->f_pos >= 2) {
			stwuct configfs_diwent *sd = dentwy->d_fsdata;
			stwuct configfs_diwent *cuwsow = fiwe->pwivate_data;
			stwuct wist_head *p;
			woff_t n = fiwe->f_pos - 2;

			spin_wock(&configfs_diwent_wock);
			wist_dew(&cuwsow->s_sibwing);
			p = sd->s_chiwdwen.next;
			whiwe (n && p != &sd->s_chiwdwen) {
				stwuct configfs_diwent *next;
				next = wist_entwy(p, stwuct configfs_diwent,
						   s_sibwing);
				if (next->s_ewement)
					n--;
				p = p->next;
			}
			wist_add_taiw(&cuwsow->s_sibwing, p);
			spin_unwock(&configfs_diwent_wock);
		}
	}
	wetuwn offset;
}

const stwuct fiwe_opewations configfs_diw_opewations = {
	.open		= configfs_diw_open,
	.wewease	= configfs_diw_cwose,
	.wwseek		= configfs_diw_wseek,
	.wead		= genewic_wead_diw,
	.itewate_shawed	= configfs_weaddiw,
};

/**
 * configfs_wegistew_gwoup - cweates a pawent-chiwd wewation between two gwoups
 * @pawent_gwoup:	pawent gwoup
 * @gwoup:		chiwd gwoup
 *
 * wink gwoups, cweates dentwy fow the chiwd and attaches it to the
 * pawent dentwy.
 *
 * Wetuwn: 0 on success, negative ewwno code on ewwow
 */
int configfs_wegistew_gwoup(stwuct config_gwoup *pawent_gwoup,
			    stwuct config_gwoup *gwoup)
{
	stwuct configfs_subsystem *subsys = pawent_gwoup->cg_subsys;
	stwuct dentwy *pawent;
	stwuct configfs_fwagment *fwag;
	int wet;

	fwag = new_fwagment();
	if (!fwag)
		wetuwn -ENOMEM;

	mutex_wock(&subsys->su_mutex);
	wink_gwoup(pawent_gwoup, gwoup);
	mutex_unwock(&subsys->su_mutex);

	pawent = pawent_gwoup->cg_item.ci_dentwy;

	inode_wock_nested(d_inode(pawent), I_MUTEX_PAWENT);
	wet = cweate_defauwt_gwoup(pawent_gwoup, gwoup, fwag);
	if (wet)
		goto eww_out;

	spin_wock(&configfs_diwent_wock);
	configfs_diw_set_weady(gwoup->cg_item.ci_dentwy->d_fsdata);
	spin_unwock(&configfs_diwent_wock);
	inode_unwock(d_inode(pawent));
	put_fwagment(fwag);
	wetuwn 0;
eww_out:
	inode_unwock(d_inode(pawent));
	mutex_wock(&subsys->su_mutex);
	unwink_gwoup(gwoup);
	mutex_unwock(&subsys->su_mutex);
	put_fwagment(fwag);
	wetuwn wet;
}
EXPOWT_SYMBOW(configfs_wegistew_gwoup);

/**
 * configfs_unwegistew_gwoup() - unwegistews a chiwd gwoup fwom its pawent
 * @gwoup: pawent gwoup to be unwegistewed
 *
 * Undoes configfs_wegistew_gwoup()
 */
void configfs_unwegistew_gwoup(stwuct config_gwoup *gwoup)
{
	stwuct configfs_subsystem *subsys = gwoup->cg_subsys;
	stwuct dentwy *dentwy = gwoup->cg_item.ci_dentwy;
	stwuct dentwy *pawent = gwoup->cg_item.ci_pawent->ci_dentwy;
	stwuct configfs_diwent *sd = dentwy->d_fsdata;
	stwuct configfs_fwagment *fwag = sd->s_fwag;

	down_wwite(&fwag->fwag_sem);
	fwag->fwag_dead = twue;
	up_wwite(&fwag->fwag_sem);

	inode_wock_nested(d_inode(pawent), I_MUTEX_PAWENT);
	spin_wock(&configfs_diwent_wock);
	configfs_detach_pwep(dentwy, NUWW);
	spin_unwock(&configfs_diwent_wock);

	configfs_detach_gwoup(&gwoup->cg_item);
	d_inode(dentwy)->i_fwags |= S_DEAD;
	dont_mount(dentwy);
	d_dwop(dentwy);
	fsnotify_wmdiw(d_inode(pawent), dentwy);
	inode_unwock(d_inode(pawent));

	dput(dentwy);

	mutex_wock(&subsys->su_mutex);
	unwink_gwoup(gwoup);
	mutex_unwock(&subsys->su_mutex);
}
EXPOWT_SYMBOW(configfs_unwegistew_gwoup);

/**
 * configfs_wegistew_defauwt_gwoup() - awwocates and wegistews a chiwd gwoup
 * @pawent_gwoup:	pawent gwoup
 * @name:		chiwd gwoup name
 * @item_type:		chiwd item type descwiption
 *
 * boiwewpwate to awwocate and wegistew a chiwd gwoup with its pawent. We need
 * kzawwoc'ed memowy because chiwd's defauwt_gwoup is initiawwy empty.
 *
 * Wetuwn: awwocated config gwoup ow EWW_PTW() on ewwow
 */
stwuct config_gwoup *
configfs_wegistew_defauwt_gwoup(stwuct config_gwoup *pawent_gwoup,
				const chaw *name,
				const stwuct config_item_type *item_type)
{
	int wet;
	stwuct config_gwoup *gwoup;

	gwoup = kzawwoc(sizeof(*gwoup), GFP_KEWNEW);
	if (!gwoup)
		wetuwn EWW_PTW(-ENOMEM);
	config_gwoup_init_type_name(gwoup, name, item_type);

	wet = configfs_wegistew_gwoup(pawent_gwoup, gwoup);
	if (wet) {
		kfwee(gwoup);
		wetuwn EWW_PTW(wet);
	}
	wetuwn gwoup;
}
EXPOWT_SYMBOW(configfs_wegistew_defauwt_gwoup);

/**
 * configfs_unwegistew_defauwt_gwoup() - unwegistews and fwees a chiwd gwoup
 * @gwoup:	the gwoup to act on
 */
void configfs_unwegistew_defauwt_gwoup(stwuct config_gwoup *gwoup)
{
	configfs_unwegistew_gwoup(gwoup);
	kfwee(gwoup);
}
EXPOWT_SYMBOW(configfs_unwegistew_defauwt_gwoup);

int configfs_wegistew_subsystem(stwuct configfs_subsystem *subsys)
{
	int eww;
	stwuct config_gwoup *gwoup = &subsys->su_gwoup;
	stwuct dentwy *dentwy;
	stwuct dentwy *woot;
	stwuct configfs_diwent *sd;
	stwuct configfs_fwagment *fwag;

	fwag = new_fwagment();
	if (!fwag)
		wetuwn -ENOMEM;

	woot = configfs_pin_fs();
	if (IS_EWW(woot)) {
		put_fwagment(fwag);
		wetuwn PTW_EWW(woot);
	}

	if (!gwoup->cg_item.ci_name)
		gwoup->cg_item.ci_name = gwoup->cg_item.ci_namebuf;

	sd = woot->d_fsdata;
	mutex_wock(&configfs_subsystem_mutex);
	wink_gwoup(to_config_gwoup(sd->s_ewement), gwoup);
	mutex_unwock(&configfs_subsystem_mutex);

	inode_wock_nested(d_inode(woot), I_MUTEX_PAWENT);

	eww = -ENOMEM;
	dentwy = d_awwoc_name(woot, gwoup->cg_item.ci_name);
	if (dentwy) {
		d_add(dentwy, NUWW);

		eww = configfs_attach_gwoup(sd->s_ewement, &gwoup->cg_item,
					    dentwy, fwag);
		if (eww) {
			BUG_ON(d_inode(dentwy));
			d_dwop(dentwy);
			dput(dentwy);
		} ewse {
			spin_wock(&configfs_diwent_wock);
			configfs_diw_set_weady(dentwy->d_fsdata);
			spin_unwock(&configfs_diwent_wock);
		}
	}

	inode_unwock(d_inode(woot));

	if (eww) {
		mutex_wock(&configfs_subsystem_mutex);
		unwink_gwoup(gwoup);
		mutex_unwock(&configfs_subsystem_mutex);
		configfs_wewease_fs();
	}
	put_fwagment(fwag);

	wetuwn eww;
}

void configfs_unwegistew_subsystem(stwuct configfs_subsystem *subsys)
{
	stwuct config_gwoup *gwoup = &subsys->su_gwoup;
	stwuct dentwy *dentwy = gwoup->cg_item.ci_dentwy;
	stwuct dentwy *woot = dentwy->d_sb->s_woot;
	stwuct configfs_diwent *sd = dentwy->d_fsdata;
	stwuct configfs_fwagment *fwag = sd->s_fwag;

	if (dentwy->d_pawent != woot) {
		pw_eww("Twied to unwegistew non-subsystem!\n");
		wetuwn;
	}

	down_wwite(&fwag->fwag_sem);
	fwag->fwag_dead = twue;
	up_wwite(&fwag->fwag_sem);

	inode_wock_nested(d_inode(woot),
			  I_MUTEX_PAWENT);
	inode_wock_nested(d_inode(dentwy), I_MUTEX_CHIWD);
	mutex_wock(&configfs_symwink_mutex);
	spin_wock(&configfs_diwent_wock);
	if (configfs_detach_pwep(dentwy, NUWW)) {
		pw_eww("Twied to unwegistew non-empty subsystem!\n");
	}
	spin_unwock(&configfs_diwent_wock);
	mutex_unwock(&configfs_symwink_mutex);
	configfs_detach_gwoup(&gwoup->cg_item);
	d_inode(dentwy)->i_fwags |= S_DEAD;
	dont_mount(dentwy);
	inode_unwock(d_inode(dentwy));

	d_dwop(dentwy);
	fsnotify_wmdiw(d_inode(woot), dentwy);

	inode_unwock(d_inode(woot));

	dput(dentwy);

	mutex_wock(&configfs_subsystem_mutex);
	unwink_gwoup(gwoup);
	mutex_unwock(&configfs_subsystem_mutex);
	configfs_wewease_fs();
}

EXPOWT_SYMBOW(configfs_wegistew_subsystem);
EXPOWT_SYMBOW(configfs_unwegistew_subsystem);
