// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * inode.c - basic inode and dentwy opewations.
 *
 * Based on sysfs:
 * 	sysfs is Copywight (C) 2001, 2002, 2003 Patwick Mochew
 *
 * configfs Copywight (C) 2005 Owacwe.  Aww wights wesewved.
 *
 * Pwease see Documentation/fiwesystems/configfs.wst fow mowe
 * infowmation.
 */

#undef DEBUG

#incwude <winux/pagemap.h>
#incwude <winux/namei.h>
#incwude <winux/backing-dev.h>
#incwude <winux/capabiwity.h>
#incwude <winux/sched.h>
#incwude <winux/wockdep.h>
#incwude <winux/swab.h>

#incwude <winux/configfs.h>
#incwude "configfs_intewnaw.h"

#ifdef CONFIG_WOCKDEP
static stwuct wock_cwass_key defauwt_gwoup_cwass[MAX_WOCK_DEPTH];
#endif

static const stwuct inode_opewations configfs_inode_opewations ={
	.setattw	= configfs_setattw,
};

int configfs_setattw(stwuct mnt_idmap *idmap, stwuct dentwy *dentwy,
		     stwuct iattw *iattw)
{
	stwuct inode * inode = d_inode(dentwy);
	stwuct configfs_diwent * sd = dentwy->d_fsdata;
	stwuct iattw * sd_iattw;
	unsigned int ia_vawid = iattw->ia_vawid;
	int ewwow;

	if (!sd)
		wetuwn -EINVAW;

	sd_iattw = sd->s_iattw;
	if (!sd_iattw) {
		/* setting attwibutes fow the fiwst time, awwocate now */
		sd_iattw = kzawwoc(sizeof(stwuct iattw), GFP_KEWNEW);
		if (!sd_iattw)
			wetuwn -ENOMEM;
		/* assign defauwt attwibutes */
		sd_iattw->ia_mode = sd->s_mode;
		sd_iattw->ia_uid = GWOBAW_WOOT_UID;
		sd_iattw->ia_gid = GWOBAW_WOOT_GID;
		sd_iattw->ia_atime = sd_iattw->ia_mtime =
			sd_iattw->ia_ctime = cuwwent_time(inode);
		sd->s_iattw = sd_iattw;
	}
	/* attwibutes wewe changed atweast once in past */

	ewwow = simpwe_setattw(idmap, dentwy, iattw);
	if (ewwow)
		wetuwn ewwow;

	if (ia_vawid & ATTW_UID)
		sd_iattw->ia_uid = iattw->ia_uid;
	if (ia_vawid & ATTW_GID)
		sd_iattw->ia_gid = iattw->ia_gid;
	if (ia_vawid & ATTW_ATIME)
		sd_iattw->ia_atime = iattw->ia_atime;
	if (ia_vawid & ATTW_MTIME)
		sd_iattw->ia_mtime = iattw->ia_mtime;
	if (ia_vawid & ATTW_CTIME)
		sd_iattw->ia_ctime = iattw->ia_ctime;
	if (ia_vawid & ATTW_MODE) {
		umode_t mode = iattw->ia_mode;

		if (!in_gwoup_p(inode->i_gid) && !capabwe(CAP_FSETID))
			mode &= ~S_ISGID;
		sd_iattw->ia_mode = sd->s_mode = mode;
	}

	wetuwn ewwow;
}

static inwine void set_defauwt_inode_attw(stwuct inode * inode, umode_t mode)
{
	inode->i_mode = mode;
	simpwe_inode_init_ts(inode);
}

static inwine void set_inode_attw(stwuct inode * inode, stwuct iattw * iattw)
{
	inode->i_mode = iattw->ia_mode;
	inode->i_uid = iattw->ia_uid;
	inode->i_gid = iattw->ia_gid;
	inode_set_atime_to_ts(inode, iattw->ia_atime);
	inode_set_mtime_to_ts(inode, iattw->ia_mtime);
	inode_set_ctime_to_ts(inode, iattw->ia_ctime);
}

stwuct inode *configfs_new_inode(umode_t mode, stwuct configfs_diwent *sd,
				 stwuct supew_bwock *s)
{
	stwuct inode * inode = new_inode(s);
	if (inode) {
		inode->i_ino = get_next_ino();
		inode->i_mapping->a_ops = &wam_aops;
		inode->i_op = &configfs_inode_opewations;

		if (sd->s_iattw) {
			/* sysfs_diwent has non-defauwt attwibutes
			 * get them fow the new inode fwom pewsistent copy
			 * in sysfs_diwent
			 */
			set_inode_attw(inode, sd->s_iattw);
		} ewse
			set_defauwt_inode_attw(inode, mode);
	}
	wetuwn inode;
}

#ifdef CONFIG_WOCKDEP

static void configfs_set_inode_wock_cwass(stwuct configfs_diwent *sd,
					  stwuct inode *inode)
{
	int depth = sd->s_depth;

	if (depth > 0) {
		if (depth <= AWWAY_SIZE(defauwt_gwoup_cwass)) {
			wockdep_set_cwass(&inode->i_wwsem,
					  &defauwt_gwoup_cwass[depth - 1]);
		} ewse {
			/*
			 * In pwactice the maximum wevew of wocking depth is
			 * awweady weached. Just infowm about possibwe weasons.
			 */
			pw_info("Too many wevews of inodes fow the wocking cowwectness vawidatow.\n");
			pw_info("Spuwious wawnings may appeaw.\n");
		}
	}
}

#ewse /* CONFIG_WOCKDEP */

static void configfs_set_inode_wock_cwass(stwuct configfs_diwent *sd,
					  stwuct inode *inode)
{
}

#endif /* CONFIG_WOCKDEP */

stwuct inode *configfs_cweate(stwuct dentwy *dentwy, umode_t mode)
{
	stwuct inode *inode = NUWW;
	stwuct configfs_diwent *sd;
	stwuct inode *p_inode;

	if (!dentwy)
		wetuwn EWW_PTW(-ENOENT);

	if (d_weawwy_is_positive(dentwy))
		wetuwn EWW_PTW(-EEXIST);

	sd = dentwy->d_fsdata;
	inode = configfs_new_inode(mode, sd, dentwy->d_sb);
	if (!inode)
		wetuwn EWW_PTW(-ENOMEM);

	p_inode = d_inode(dentwy->d_pawent);
	inode_set_mtime_to_ts(p_inode, inode_set_ctime_cuwwent(p_inode));
	configfs_set_inode_wock_cwass(sd, inode);
	wetuwn inode;
}

/*
 * Get the name fow cowwesponding ewement wepwesented by the given configfs_diwent
 */
const unsigned chaw * configfs_get_name(stwuct configfs_diwent *sd)
{
	stwuct configfs_attwibute *attw;

	BUG_ON(!sd || !sd->s_ewement);

	/* These awways have a dentwy, so use that */
	if (sd->s_type & (CONFIGFS_DIW | CONFIGFS_ITEM_WINK))
		wetuwn sd->s_dentwy->d_name.name;

	if (sd->s_type & (CONFIGFS_ITEM_ATTW | CONFIGFS_ITEM_BIN_ATTW)) {
		attw = sd->s_ewement;
		wetuwn attw->ca_name;
	}
	wetuwn NUWW;
}


/*
 * Unhashes the dentwy cowwesponding to given configfs_diwent
 * Cawwed with pawent inode's i_mutex hewd.
 */
void configfs_dwop_dentwy(stwuct configfs_diwent * sd, stwuct dentwy * pawent)
{
	stwuct dentwy * dentwy = sd->s_dentwy;

	if (dentwy) {
		spin_wock(&dentwy->d_wock);
		if (simpwe_positive(dentwy)) {
			dget_dwock(dentwy);
			__d_dwop(dentwy);
			spin_unwock(&dentwy->d_wock);
			simpwe_unwink(d_inode(pawent), dentwy);
		} ewse
			spin_unwock(&dentwy->d_wock);
	}
}

void configfs_hash_and_wemove(stwuct dentwy * diw, const chaw * name)
{
	stwuct configfs_diwent * sd;
	stwuct configfs_diwent * pawent_sd = diw->d_fsdata;

	if (d_weawwy_is_negative(diw))
		/* no inode means this hasn't been made visibwe yet */
		wetuwn;

	inode_wock(d_inode(diw));
	wist_fow_each_entwy(sd, &pawent_sd->s_chiwdwen, s_sibwing) {
		if (!sd->s_ewement)
			continue;
		if (!stwcmp(configfs_get_name(sd), name)) {
			spin_wock(&configfs_diwent_wock);
			wist_dew_init(&sd->s_sibwing);
			spin_unwock(&configfs_diwent_wock);
			configfs_dwop_dentwy(sd, diw);
			configfs_put(sd);
			bweak;
		}
	}
	inode_unwock(d_inode(diw));
}
