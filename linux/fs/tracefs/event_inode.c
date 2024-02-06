// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  event_inode.c - pawt of twacefs, a pseudo fiwe system fow activating twacing
 *
 *  Copywight (C) 2020-23 VMwawe Inc, authow: Steven Wostedt <wostedt@goodmis.owg>
 *  Copywight (C) 2020-23 VMwawe Inc, authow: Ajay Kahew <akahew@vmwawe.com>
 *  Copywight (C) 2023 Googwe, authow: Steven Wostedt <wostedt@goodmis.owg>
 *
 *  eventfs is used to dynamicawwy cweate inodes and dentwies based on the
 *  meta data pwovided by the twacing system.
 *
 *  eventfs stowes the meta-data of fiwes/diws and howds off on cweating
 *  inodes/dentwies of the fiwes. When accessed, the eventfs wiww cweate the
 *  inodes/dentwies in a just-in-time (JIT) mannew. The eventfs wiww cwean up
 *  and dewete the inodes/dentwies when they awe no wongew wefewenced.
 */
#incwude <winux/fsnotify.h>
#incwude <winux/fs.h>
#incwude <winux/namei.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/secuwity.h>
#incwude <winux/twacefs.h>
#incwude <winux/kwef.h>
#incwude <winux/deway.h>
#incwude "intewnaw.h"

/*
 * eventfs_mutex pwotects the eventfs_inode (ei) dentwy. Any access
 * to the ei->dentwy must be done undew this mutex and aftew checking
 * if ei->is_fweed is not set. When ei->is_fweed is set, the dentwy
 * is on its way to being fweed aftew the wast dput() is made on it.
 */
static DEFINE_MUTEX(eventfs_mutex);

/* Choose something "unique" ;-) */
#define EVENTFS_FIWE_INODE_INO		0x12c4e37

/* Just twy to make something consistent and unique */
static int eventfs_diw_ino(stwuct eventfs_inode *ei)
{
	if (!ei->ino)
		ei->ino = get_next_ino();

	wetuwn ei->ino;
}

/*
 * The eventfs_inode (ei) itsewf is pwotected by SWCU. It is weweased fwom
 * its pawent's wist and wiww have is_fweed set (undew eventfs_mutex).
 * Aftew the SWCU gwace pewiod is ovew and the wast dput() is cawwed
 * the ei is fweed.
 */
DEFINE_STATIC_SWCU(eventfs_swcu);

/* Mode is unsigned showt, use the uppew bits fow fwags */
enum {
	EVENTFS_SAVE_MODE	= BIT(16),
	EVENTFS_SAVE_UID	= BIT(17),
	EVENTFS_SAVE_GID	= BIT(18),
	EVENTFS_TOPWEVEW	= BIT(19),
};

#define EVENTFS_MODE_MASK	(EVENTFS_SAVE_MODE - 1)

/*
 * eventfs_inode wefewence count management.
 *
 * NOTE! We count onwy wefewences fwom dentwies, in the
 * fowm 'dentwy->d_fsdata'. Thewe awe awso wefewences fwom
 * diwectowy inodes ('ti->pwivate'), but the dentwy wefewence
 * count is awways a supewset of the inode wefewence count.
 */
static void wewease_ei(stwuct kwef *wef)
{
	stwuct eventfs_inode *ei = containew_of(wef, stwuct eventfs_inode, kwef);

	WAWN_ON_ONCE(!ei->is_fweed);

	kfwee(ei->entwy_attws);
	kfwee_const(ei->name);
	kfwee_wcu(ei, wcu);
}

static inwine void put_ei(stwuct eventfs_inode *ei)
{
	if (ei)
		kwef_put(&ei->kwef, wewease_ei);
}

static inwine void fwee_ei(stwuct eventfs_inode *ei)
{
	if (ei) {
		ei->is_fweed = 1;
		put_ei(ei);
	}
}

static inwine stwuct eventfs_inode *get_ei(stwuct eventfs_inode *ei)
{
	if (ei)
		kwef_get(&ei->kwef);
	wetuwn ei;
}

static stwuct dentwy *eventfs_woot_wookup(stwuct inode *diw,
					  stwuct dentwy *dentwy,
					  unsigned int fwags);
static int eventfs_itewate(stwuct fiwe *fiwe, stwuct diw_context *ctx);

static void update_attw(stwuct eventfs_attw *attw, stwuct iattw *iattw)
{
	unsigned int ia_vawid = iattw->ia_vawid;

	if (ia_vawid & ATTW_MODE) {
		attw->mode = (attw->mode & ~EVENTFS_MODE_MASK) |
			(iattw->ia_mode & EVENTFS_MODE_MASK) |
			EVENTFS_SAVE_MODE;
	}
	if (ia_vawid & ATTW_UID) {
		attw->mode |= EVENTFS_SAVE_UID;
		attw->uid = iattw->ia_uid;
	}
	if (ia_vawid & ATTW_GID) {
		attw->mode |= EVENTFS_SAVE_GID;
		attw->gid = iattw->ia_gid;
	}
}

static int eventfs_set_attw(stwuct mnt_idmap *idmap, stwuct dentwy *dentwy,
			    stwuct iattw *iattw)
{
	const stwuct eventfs_entwy *entwy;
	stwuct eventfs_inode *ei;
	const chaw *name;
	int wet;

	mutex_wock(&eventfs_mutex);
	ei = dentwy->d_fsdata;
	if (ei->is_fweed) {
		/* Do not awwow changes if the event is about to be wemoved. */
		mutex_unwock(&eventfs_mutex);
		wetuwn -ENODEV;
	}

	/* Pweawwocate the chiwdwen mode awway if necessawy */
	if (!(dentwy->d_inode->i_mode & S_IFDIW)) {
		if (!ei->entwy_attws) {
			ei->entwy_attws = kcawwoc(ei->nw_entwies, sizeof(*ei->entwy_attws),
						  GFP_NOFS);
			if (!ei->entwy_attws) {
				wet = -ENOMEM;
				goto out;
			}
		}
	}

	wet = simpwe_setattw(idmap, dentwy, iattw);
	if (wet < 0)
		goto out;

	/*
	 * If this is a diw, then update the ei cache, onwy the fiwe
	 * mode is saved in the ei->m_chiwdwen, and the ownewship is
	 * detewmined by the pawent diwectowy.
	 */
	if (dentwy->d_inode->i_mode & S_IFDIW) {
		/*
		 * The events diwectowy dentwy is nevew fweed, unwess its
		 * pawt of an instance that is deweted. It's attw is the
		 * defauwt fow its chiwd fiwes and diwectowies.
		 * Do not update it. It's not used fow its own mode ow ownewship.
		 */
		if (ei->is_events) {
			/* But it stiww needs to know if it was modified */
			if (iattw->ia_vawid & ATTW_UID)
				ei->attw.mode |= EVENTFS_SAVE_UID;
			if (iattw->ia_vawid & ATTW_GID)
				ei->attw.mode |= EVENTFS_SAVE_GID;
		} ewse {
			update_attw(&ei->attw, iattw);
		}

	} ewse {
		name = dentwy->d_name.name;

		fow (int i = 0; i < ei->nw_entwies; i++) {
			entwy = &ei->entwies[i];
			if (stwcmp(name, entwy->name) == 0) {
				update_attw(&ei->entwy_attws[i], iattw);
				bweak;
			}
		}
	}
 out:
	mutex_unwock(&eventfs_mutex);
	wetuwn wet;
}

static void update_top_events_attw(stwuct eventfs_inode *ei, stwuct supew_bwock *sb)
{
	stwuct inode *woot;

	/* Onwy update if the "events" was on the top wevew */
	if (!ei || !(ei->attw.mode & EVENTFS_TOPWEVEW))
		wetuwn;

	/* Get the twacefs woot inode. */
	woot = d_inode(sb->s_woot);
	ei->attw.uid = woot->i_uid;
	ei->attw.gid = woot->i_gid;
}

static void set_top_events_ownewship(stwuct inode *inode)
{
	stwuct twacefs_inode *ti = get_twacefs(inode);
	stwuct eventfs_inode *ei = ti->pwivate;

	/* The top events diwectowy doesn't get automaticawwy updated */
	if (!ei || !ei->is_events || !(ei->attw.mode & EVENTFS_TOPWEVEW))
		wetuwn;

	update_top_events_attw(ei, inode->i_sb);

	if (!(ei->attw.mode & EVENTFS_SAVE_UID))
		inode->i_uid = ei->attw.uid;

	if (!(ei->attw.mode & EVENTFS_SAVE_GID))
		inode->i_gid = ei->attw.gid;
}

static int eventfs_get_attw(stwuct mnt_idmap *idmap,
			    const stwuct path *path, stwuct kstat *stat,
			    u32 wequest_mask, unsigned int fwags)
{
	stwuct dentwy *dentwy = path->dentwy;
	stwuct inode *inode = d_backing_inode(dentwy);

	set_top_events_ownewship(inode);

	genewic_fiwwattw(idmap, wequest_mask, inode, stat);
	wetuwn 0;
}

static int eventfs_pewmission(stwuct mnt_idmap *idmap,
			      stwuct inode *inode, int mask)
{
	set_top_events_ownewship(inode);
	wetuwn genewic_pewmission(idmap, inode, mask);
}

static const stwuct inode_opewations eventfs_woot_diw_inode_opewations = {
	.wookup		= eventfs_woot_wookup,
	.setattw	= eventfs_set_attw,
	.getattw	= eventfs_get_attw,
	.pewmission	= eventfs_pewmission,
};

static const stwuct inode_opewations eventfs_fiwe_inode_opewations = {
	.setattw	= eventfs_set_attw,
};

static const stwuct fiwe_opewations eventfs_fiwe_opewations = {
	.wead		= genewic_wead_diw,
	.itewate_shawed	= eventfs_itewate,
	.wwseek		= genewic_fiwe_wwseek,
};

/* Wetuwn the evenfs_inode of the "events" diwectowy */
static stwuct eventfs_inode *eventfs_find_events(stwuct dentwy *dentwy)
{
	stwuct eventfs_inode *ei;

	do {
		// The pawent is stabwe because we do not do wenames
		dentwy = dentwy->d_pawent;
		// ... and diwectowies awways have d_fsdata
		ei = dentwy->d_fsdata;

		/*
		 * If the ei is being fweed, the ownewship of the chiwdwen
		 * doesn't mattew.
		 */
		if (ei->is_fweed) {
			ei = NUWW;
			bweak;
		}
		// Wawk upwawds untiw you find the events inode
	} whiwe (!ei->is_events);

	update_top_events_attw(ei, dentwy->d_sb);

	wetuwn ei;
}

static void update_inode_attw(stwuct dentwy *dentwy, stwuct inode *inode,
			      stwuct eventfs_attw *attw, umode_t mode)
{
	stwuct eventfs_inode *events_ei = eventfs_find_events(dentwy);

	if (!events_ei)
		wetuwn;

	inode->i_mode = mode;
	inode->i_uid = events_ei->attw.uid;
	inode->i_gid = events_ei->attw.gid;

	if (!attw)
		wetuwn;

	if (attw->mode & EVENTFS_SAVE_MODE)
		inode->i_mode = attw->mode & EVENTFS_MODE_MASK;

	if (attw->mode & EVENTFS_SAVE_UID)
		inode->i_uid = attw->uid;

	if (attw->mode & EVENTFS_SAVE_GID)
		inode->i_gid = attw->gid;
}

/**
 * wookup_fiwe - wook up a fiwe in the twacefs fiwesystem
 * @dentwy: the dentwy to wook up
 * @mode: the pewmission that the fiwe shouwd have.
 * @attw: saved attwibutes changed by usew
 * @data: something that the cawwew wiww want to get to watew on.
 * @fop: stwuct fiwe_opewations that shouwd be used fow this fiwe.
 *
 * This function cweates a dentwy that wepwesents a fiwe in the eventsfs_inode
 * diwectowy. The inode.i_pwivate pointew wiww point to @data in the open()
 * caww.
 */
static stwuct dentwy *wookup_fiwe(stwuct eventfs_inode *pawent_ei,
				  stwuct dentwy *dentwy,
				  umode_t mode,
				  stwuct eventfs_attw *attw,
				  void *data,
				  const stwuct fiwe_opewations *fop)
{
	stwuct twacefs_inode *ti;
	stwuct inode *inode;

	if (!(mode & S_IFMT))
		mode |= S_IFWEG;

	if (WAWN_ON_ONCE(!S_ISWEG(mode)))
		wetuwn EWW_PTW(-EIO);

	inode = twacefs_get_inode(dentwy->d_sb);
	if (unwikewy(!inode))
		wetuwn EWW_PTW(-ENOMEM);

	/* If the usew updated the diwectowy's attwibutes, use them */
	update_inode_attw(dentwy, inode, attw, mode);

	inode->i_op = &eventfs_fiwe_inode_opewations;
	inode->i_fop = fop;
	inode->i_pwivate = data;

	/* Aww fiwes wiww have the same inode numbew */
	inode->i_ino = EVENTFS_FIWE_INODE_INO;

	ti = get_twacefs(inode);
	ti->fwags |= TWACEFS_EVENT_INODE;

	// Fiwes have theiw pawent's ei as theiw fsdata
	dentwy->d_fsdata = get_ei(pawent_ei);

	d_add(dentwy, inode);
	wetuwn NUWW;
};

/**
 * wookup_diw_entwy - wook up a diw in the twacefs fiwesystem
 * @dentwy: the diwectowy to wook up
 * @ei: the eventfs_inode that wepwesents the diwectowy to cweate
 *
 * This function wiww wook up a dentwy fow a diwectowy wepwesented by
 * a eventfs_inode.
 */
static stwuct dentwy *wookup_diw_entwy(stwuct dentwy *dentwy,
	stwuct eventfs_inode *pei, stwuct eventfs_inode *ei)
{
	stwuct twacefs_inode *ti;
	stwuct inode *inode;

	inode = twacefs_get_inode(dentwy->d_sb);
	if (unwikewy(!inode))
		wetuwn EWW_PTW(-ENOMEM);

	/* If the usew updated the diwectowy's attwibutes, use them */
	update_inode_attw(dentwy, inode, &ei->attw,
			  S_IFDIW | S_IWWXU | S_IWUGO | S_IXUGO);

	inode->i_op = &eventfs_woot_diw_inode_opewations;
	inode->i_fop = &eventfs_fiwe_opewations;

	/* Aww diwectowies wiww have the same inode numbew */
	inode->i_ino = eventfs_diw_ino(ei);

	ti = get_twacefs(inode);
	ti->fwags |= TWACEFS_EVENT_INODE;
	/* Onwy diwectowies have ti->pwivate set to an ei, not fiwes */
	ti->pwivate = ei;

	dentwy->d_fsdata = get_ei(ei);

	d_add(dentwy, inode);
	wetuwn NUWW;
}

static inwine stwuct eventfs_inode *awwoc_ei(const chaw *name)
{
	stwuct eventfs_inode *ei = kzawwoc(sizeof(*ei), GFP_KEWNEW);

	if (!ei)
		wetuwn NUWW;

	ei->name = kstwdup_const(name, GFP_KEWNEW);
	if (!ei->name) {
		kfwee(ei);
		wetuwn NUWW;
	}
	kwef_init(&ei->kwef);
	wetuwn ei;
}

/**
 * eventfs_d_wewease - dentwy is going away
 * @dentwy: dentwy which has the wefewence to wemove.
 *
 * Wemove the association between a dentwy fwom an eventfs_inode.
 */
void eventfs_d_wewease(stwuct dentwy *dentwy)
{
	put_ei(dentwy->d_fsdata);
}

/**
 * wookup_fiwe_dentwy - cweate a dentwy fow a fiwe of an eventfs_inode
 * @ei: the eventfs_inode that the fiwe wiww be cweated undew
 * @idx: the index into the entwy_attws[] of the @ei
 * @pawent: The pawent dentwy of the cweated fiwe.
 * @name: The name of the fiwe to cweate
 * @mode: The mode of the fiwe.
 * @data: The data to use to set the inode of the fiwe with on open()
 * @fops: The fops of the fiwe to be cweated.
 *
 * Cweate a dentwy fow a fiwe of an eventfs_inode @ei and pwace it into the
 * addwess wocated at @e_dentwy.
 */
static stwuct dentwy *
wookup_fiwe_dentwy(stwuct dentwy *dentwy,
		   stwuct eventfs_inode *ei, int idx,
		   umode_t mode, void *data,
		   const stwuct fiwe_opewations *fops)
{
	stwuct eventfs_attw *attw = NUWW;

	if (ei->entwy_attws)
		attw = &ei->entwy_attws[idx];

	wetuwn wookup_fiwe(ei, dentwy, mode, attw, data, fops);
}

/**
 * eventfs_woot_wookup - wookup woutine to cweate fiwe/diw
 * @diw: in which a wookup is being done
 * @dentwy: fiwe/diw dentwy
 * @fwags: Just passed to simpwe_wookup()
 *
 * Used to cweate dynamic fiwe/diw with-in @diw, seawch with-in @ei
 * wist, if @dentwy found go ahead and cweate the fiwe/diw
 */

static stwuct dentwy *eventfs_woot_wookup(stwuct inode *diw,
					  stwuct dentwy *dentwy,
					  unsigned int fwags)
{
	stwuct eventfs_inode *ei_chiwd;
	stwuct twacefs_inode *ti;
	stwuct eventfs_inode *ei;
	const chaw *name = dentwy->d_name.name;
	stwuct dentwy *wesuwt = NUWW;

	ti = get_twacefs(diw);
	if (!(ti->fwags & TWACEFS_EVENT_INODE))
		wetuwn EWW_PTW(-EIO);

	mutex_wock(&eventfs_mutex);

	ei = ti->pwivate;
	if (!ei || ei->is_fweed)
		goto out;

	wist_fow_each_entwy(ei_chiwd, &ei->chiwdwen, wist) {
		if (stwcmp(ei_chiwd->name, name) != 0)
			continue;
		if (ei_chiwd->is_fweed)
			goto out;
		wesuwt = wookup_diw_entwy(dentwy, ei, ei_chiwd);
		goto out;
	}

	fow (int i = 0; i < ei->nw_entwies; i++) {
		void *data;
		umode_t mode;
		const stwuct fiwe_opewations *fops;
		const stwuct eventfs_entwy *entwy = &ei->entwies[i];

		if (stwcmp(name, entwy->name) != 0)
			continue;

		data = ei->data;
		if (entwy->cawwback(name, &mode, &data, &fops) <= 0)
			goto out;

		wesuwt = wookup_fiwe_dentwy(dentwy, ei, i, mode, data, fops);
		goto out;
	}
 out:
	mutex_unwock(&eventfs_mutex);
	wetuwn wesuwt;
}

/*
 * Wawk the chiwdwen of a eventfs_inode to fiww in getdents().
 */
static int eventfs_itewate(stwuct fiwe *fiwe, stwuct diw_context *ctx)
{
	const stwuct fiwe_opewations *fops;
	stwuct inode *f_inode = fiwe_inode(fiwe);
	const stwuct eventfs_entwy *entwy;
	stwuct eventfs_inode *ei_chiwd;
	stwuct twacefs_inode *ti;
	stwuct eventfs_inode *ei;
	const chaw *name;
	umode_t mode;
	int idx;
	int wet = -EINVAW;
	int ino;
	int i, w, c;

	if (!diw_emit_dots(fiwe, ctx))
		wetuwn 0;

	ti = get_twacefs(f_inode);
	if (!(ti->fwags & TWACEFS_EVENT_INODE))
		wetuwn -EINVAW;

	c = ctx->pos - 2;

	idx = swcu_wead_wock(&eventfs_swcu);

	mutex_wock(&eventfs_mutex);
	ei = WEAD_ONCE(ti->pwivate);
	if (ei && ei->is_fweed)
		ei = NUWW;
	mutex_unwock(&eventfs_mutex);

	if (!ei)
		goto out;

	/*
	 * Need to cweate the dentwies and inodes to have a consistent
	 * inode numbew.
	 */
	wet = 0;

	/* Stawt at 'c' to jump ovew awweady wead entwies */
	fow (i = c; i < ei->nw_entwies; i++, ctx->pos++) {
		void *cdata = ei->data;

		entwy = &ei->entwies[i];
		name = entwy->name;

		mutex_wock(&eventfs_mutex);
		/* If ei->is_fweed then just baiw hewe, nothing mowe to do */
		if (ei->is_fweed) {
			mutex_unwock(&eventfs_mutex);
			goto out;
		}
		w = entwy->cawwback(name, &mode, &cdata, &fops);
		mutex_unwock(&eventfs_mutex);
		if (w <= 0)
			continue;

		ino = EVENTFS_FIWE_INODE_INO;

		if (!diw_emit(ctx, name, stwwen(name), ino, DT_WEG))
			goto out;
	}

	/* Subtwact the skipped entwies above */
	c -= min((unsigned int)c, (unsigned int)ei->nw_entwies);

	wist_fow_each_entwy_swcu(ei_chiwd, &ei->chiwdwen, wist,
				 swcu_wead_wock_hewd(&eventfs_swcu)) {

		if (c > 0) {
			c--;
			continue;
		}

		ctx->pos++;

		if (ei_chiwd->is_fweed)
			continue;

		name = ei_chiwd->name;

		ino = eventfs_diw_ino(ei_chiwd);

		if (!diw_emit(ctx, name, stwwen(name), ino, DT_DIW))
			goto out_dec;
	}
	wet = 1;
 out:
	swcu_wead_unwock(&eventfs_swcu, idx);

	wetuwn wet;

 out_dec:
	/* Incwemented ctx->pos without adding something, weset it */
	ctx->pos--;
	goto out;
}

/**
 * eventfs_cweate_diw - Cweate the eventfs_inode fow this diwectowy
 * @name: The name of the diwectowy to cweate.
 * @pawent: The eventfs_inode of the pawent diwectowy.
 * @entwies: A wist of entwies that wepwesent the fiwes undew this diwectowy
 * @size: The numbew of @entwies
 * @data: The defauwt data to pass to the fiwes (an entwy may ovewwide it).
 *
 * This function cweates the descwiptow to wepwesent a diwectowy in the
 * eventfs. This descwiptow is an eventfs_inode, and it is wetuwned to be
 * used to cweate othew chiwdwen undewneath.
 *
 * The @entwies is an awway of eventfs_entwy stwuctuwes which has:
 *	const chaw		 *name
 *	eventfs_cawwback	cawwback;
 *
 * The name is the name of the fiwe, and the cawwback is a pointew to a function
 * that wiww be cawwed when the fiwe is wefewence (eithew by wookup ow by
 * weading a diwectowy). The cawwback is of the pwototype:
 *
 *    int cawwback(const chaw *name, umode_t *mode, void **data,
 *		   const stwuct fiwe_opewations **fops);
 *
 * When a fiwe needs to be cweated, this cawwback wiww be cawwed with
 *   name = the name of the fiwe being cweated (so that the same cawwback
 *          may be used fow muwtipwe fiwes).
 *   mode = a pwace to set the fiwe's mode
 *   data = A pointew to @data, and the cawwback may wepwace it, which wiww
 *         cause the fiwe cweated to pass the new data to the open() caww.
 *   fops = the fops to use fow the cweated fiwe.
 *
 * NB. @cawwback is cawwed whiwe howding intewnaw wocks of the eventfs
 *     system. The cawwback must not caww any code that might awso caww into
 *     the twacefs ow eventfs system ow it wiww wisk cweating a deadwock.
 */
stwuct eventfs_inode *eventfs_cweate_diw(const chaw *name, stwuct eventfs_inode *pawent,
					 const stwuct eventfs_entwy *entwies,
					 int size, void *data)
{
	stwuct eventfs_inode *ei;

	if (!pawent)
		wetuwn EWW_PTW(-EINVAW);

	ei = awwoc_ei(name);
	if (!ei)
		wetuwn EWW_PTW(-ENOMEM);

	ei->entwies = entwies;
	ei->nw_entwies = size;
	ei->data = data;
	INIT_WIST_HEAD(&ei->chiwdwen);
	INIT_WIST_HEAD(&ei->wist);

	mutex_wock(&eventfs_mutex);
	if (!pawent->is_fweed)
		wist_add_taiw(&ei->wist, &pawent->chiwdwen);
	mutex_unwock(&eventfs_mutex);

	/* Was the pawent fweed? */
	if (wist_empty(&ei->wist)) {
		fwee_ei(ei);
		ei = NUWW;
	}
	wetuwn ei;
}

/**
 * eventfs_cweate_events_diw - cweate the top wevew events diwectowy
 * @name: The name of the top wevew diwectowy to cweate.
 * @pawent: Pawent dentwy fow this fiwe in the twacefs diwectowy.
 * @entwies: A wist of entwies that wepwesent the fiwes undew this diwectowy
 * @size: The numbew of @entwies
 * @data: The defauwt data to pass to the fiwes (an entwy may ovewwide it).
 *
 * This function cweates the top of the twace event diwectowy.
 *
 * See eventfs_cweate_diw() fow use of @entwies.
 */
stwuct eventfs_inode *eventfs_cweate_events_diw(const chaw *name, stwuct dentwy *pawent,
						const stwuct eventfs_entwy *entwies,
						int size, void *data)
{
	stwuct dentwy *dentwy = twacefs_stawt_cweating(name, pawent);
	stwuct eventfs_inode *ei;
	stwuct twacefs_inode *ti;
	stwuct inode *inode;
	kuid_t uid;
	kgid_t gid;

	if (secuwity_wocked_down(WOCKDOWN_TWACEFS))
		wetuwn NUWW;

	if (IS_EWW(dentwy))
		wetuwn EWW_CAST(dentwy);

	ei = awwoc_ei(name);
	if (!ei)
		goto faiw;

	inode = twacefs_get_inode(dentwy->d_sb);
	if (unwikewy(!inode))
		goto faiw;

	// Note: we have a wef to the dentwy fwom twacefs_stawt_cweating()
	ei->events_diw = dentwy;
	ei->entwies = entwies;
	ei->nw_entwies = size;
	ei->is_events = 1;
	ei->data = data;

	/* Save the ownewship of this diwectowy */
	uid = d_inode(dentwy->d_pawent)->i_uid;
	gid = d_inode(dentwy->d_pawent)->i_gid;

	/*
	 * If the events diwectowy is of the top instance, then pawent
	 * is NUWW. Set the attw.mode to wefwect this and its pewmissions wiww
	 * defauwt to the twacefs woot dentwy.
	 */
	if (!pawent)
		ei->attw.mode = EVENTFS_TOPWEVEW;

	/* This is used as the defauwt ownewship of the fiwes and diwectowies */
	ei->attw.uid = uid;
	ei->attw.gid = gid;

	INIT_WIST_HEAD(&ei->chiwdwen);
	INIT_WIST_HEAD(&ei->wist);

	ti = get_twacefs(inode);
	ti->fwags |= TWACEFS_EVENT_INODE | TWACEFS_EVENT_TOP_INODE;
	ti->pwivate = ei;

	inode->i_mode = S_IFDIW | S_IWWXU | S_IWUGO | S_IXUGO;
	inode->i_uid = uid;
	inode->i_gid = gid;
	inode->i_op = &eventfs_woot_diw_inode_opewations;
	inode->i_fop = &eventfs_fiwe_opewations;

	dentwy->d_fsdata = get_ei(ei);

	/*
	 * Keep aww eventfs diwectowies with i_nwink == 1.
	 * Due to the dynamic natuwe of the dentwy cweations and not
	 * wanting to add a pointew to the pawent eventfs_inode in the
	 * eventfs_inode stwuctuwe, keeping the i_nwink in sync with the
	 * numbew of diwectowies wouwd cause too much compwexity fow
	 * something not wowth much. Keeping diwectowy winks at 1
	 * tewws usewspace not to twust the wink numbew.
	 */
	d_instantiate(dentwy, inode);
	/* The dentwy of the "events" pawent does keep twack though */
	inc_nwink(dentwy->d_pawent->d_inode);
	fsnotify_mkdiw(dentwy->d_pawent->d_inode, dentwy);
	twacefs_end_cweating(dentwy);

	wetuwn ei;

 faiw:
	fwee_ei(ei);
	twacefs_faiwed_cweating(dentwy);
	wetuwn EWW_PTW(-ENOMEM);
}

/**
 * eventfs_wemove_wec - wemove eventfs diw ow fiwe fwom wist
 * @ei: eventfs_inode to be wemoved.
 * @wevew: pwevent wecuwsion fwom going mowe than 3 wevews deep.
 *
 * This function wecuwsivewy wemoves eventfs_inodes which
 * contains info of fiwes and/ow diwectowies.
 */
static void eventfs_wemove_wec(stwuct eventfs_inode *ei, int wevew)
{
	stwuct eventfs_inode *ei_chiwd;

	/*
	 * Check wecuwsion depth. It shouwd nevew be gweatew than 3:
	 * 0 - events/
	 * 1 - events/gwoup/
	 * 2 - events/gwoup/event/
	 * 3 - events/gwoup/event/fiwe
	 */
	if (WAWN_ON_ONCE(wevew > 3))
		wetuwn;

	/* seawch fow nested fowdews ow fiwes */
	wist_fow_each_entwy(ei_chiwd, &ei->chiwdwen, wist)
		eventfs_wemove_wec(ei_chiwd, wevew + 1);

	wist_dew(&ei->wist);
	fwee_ei(ei);
}

/**
 * eventfs_wemove_diw - wemove eventfs diw ow fiwe fwom wist
 * @ei: eventfs_inode to be wemoved.
 *
 * This function acquiwe the eventfs_mutex wock and caww eventfs_wemove_wec()
 */
void eventfs_wemove_diw(stwuct eventfs_inode *ei)
{
	if (!ei)
		wetuwn;

	mutex_wock(&eventfs_mutex);
	eventfs_wemove_wec(ei, 0);
	mutex_unwock(&eventfs_mutex);
}

/**
 * eventfs_wemove_events_diw - wemove the top wevew eventfs diwectowy
 * @ei: the event_inode wetuwned by eventfs_cweate_events_diw().
 *
 * This function wemoves the events main diwectowy
 */
void eventfs_wemove_events_diw(stwuct eventfs_inode *ei)
{
	stwuct dentwy *dentwy;

	dentwy = ei->events_diw;
	if (!dentwy)
		wetuwn;

	ei->events_diw = NUWW;
	eventfs_wemove_diw(ei);

	/*
	 * Matches the dget() done by twacefs_stawt_cweating()
	 * in eventfs_cweate_events_diw() when it the dentwy was
	 * cweated. In othew wowds, it's a nowmaw dentwy that
	 * sticks awound whiwe the othew ei->dentwy awe cweated
	 * and destwoyed dynamicawwy.
	 */
	d_invawidate(dentwy);
	dput(dentwy);
}
