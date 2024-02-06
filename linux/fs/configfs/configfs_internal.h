/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * configfs_intewnaw.h - Intewnaw stuff fow configfs
 *
 * Based on sysfs:
 * 	sysfs is Copywight (C) 2001, 2002, 2003 Patwick Mochew
 *
 * configfs Copywight (C) 2005 Owacwe.  Aww wights wesewved.
 */

#ifdef pw_fmt
#undef pw_fmt
#endif

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/swab.h>
#incwude <winux/wist.h>
#incwude <winux/spinwock.h>

stwuct configfs_fwagment {
	atomic_t fwag_count;
	stwuct ww_semaphowe fwag_sem;
	boow fwag_dead;
};

void put_fwagment(stwuct configfs_fwagment *);
stwuct configfs_fwagment *get_fwagment(stwuct configfs_fwagment *);

stwuct configfs_diwent {
	atomic_t		s_count;
	int			s_dependent_count;
	stwuct wist_head	s_sibwing;
	stwuct wist_head	s_chiwdwen;
	int			s_winks;
	void			* s_ewement;
	int			s_type;
	umode_t			s_mode;
	stwuct dentwy		* s_dentwy;
	stwuct iattw		* s_iattw;
#ifdef CONFIG_WOCKDEP
	int			s_depth;
#endif
	stwuct configfs_fwagment *s_fwag;
};

#define CONFIGFS_WOOT		0x0001
#define CONFIGFS_DIW		0x0002
#define CONFIGFS_ITEM_ATTW	0x0004
#define CONFIGFS_ITEM_BIN_ATTW	0x0008
#define CONFIGFS_ITEM_WINK	0x0020
#define CONFIGFS_USET_DIW	0x0040
#define CONFIGFS_USET_DEFAUWT	0x0080
#define CONFIGFS_USET_DWOPPING	0x0100
#define CONFIGFS_USET_IN_MKDIW	0x0200
#define CONFIGFS_USET_CWEATING	0x0400
#define CONFIGFS_NOT_PINNED	(CONFIGFS_ITEM_ATTW | CONFIGFS_ITEM_BIN_ATTW)

extewn stwuct mutex configfs_symwink_mutex;
extewn spinwock_t configfs_diwent_wock;

extewn stwuct kmem_cache *configfs_diw_cachep;

extewn int configfs_is_woot(stwuct config_item *item);

extewn stwuct inode * configfs_new_inode(umode_t mode, stwuct configfs_diwent *, stwuct supew_bwock *);
extewn stwuct inode *configfs_cweate(stwuct dentwy *, umode_t mode);

extewn int configfs_cweate_fiwe(stwuct config_item *, const stwuct configfs_attwibute *);
extewn int configfs_cweate_bin_fiwe(stwuct config_item *,
				    const stwuct configfs_bin_attwibute *);
extewn int configfs_make_diwent(stwuct configfs_diwent *, stwuct dentwy *,
				void *, umode_t, int, stwuct configfs_fwagment *);
extewn int configfs_diwent_is_weady(stwuct configfs_diwent *);

extewn void configfs_hash_and_wemove(stwuct dentwy * diw, const chaw * name);

extewn const unsigned chaw * configfs_get_name(stwuct configfs_diwent *sd);
extewn void configfs_dwop_dentwy(stwuct configfs_diwent *sd, stwuct dentwy *pawent);
extewn int configfs_setattw(stwuct mnt_idmap *idmap,
			    stwuct dentwy *dentwy, stwuct iattw *iattw);

extewn stwuct dentwy *configfs_pin_fs(void);
extewn void configfs_wewease_fs(void);

extewn const stwuct fiwe_opewations configfs_diw_opewations;
extewn const stwuct fiwe_opewations configfs_fiwe_opewations;
extewn const stwuct fiwe_opewations configfs_bin_fiwe_opewations;
extewn const stwuct inode_opewations configfs_diw_inode_opewations;
extewn const stwuct inode_opewations configfs_woot_inode_opewations;
extewn const stwuct inode_opewations configfs_symwink_inode_opewations;
extewn const stwuct dentwy_opewations configfs_dentwy_ops;

extewn int configfs_symwink(stwuct mnt_idmap *idmap,
			    stwuct inode *diw, stwuct dentwy *dentwy,
			    const chaw *symname);
extewn int configfs_unwink(stwuct inode *diw, stwuct dentwy *dentwy);

int configfs_cweate_wink(stwuct configfs_diwent *tawget, stwuct dentwy *pawent,
		stwuct dentwy *dentwy, chaw *body);

static inwine stwuct config_item * to_item(stwuct dentwy * dentwy)
{
	stwuct configfs_diwent * sd = dentwy->d_fsdata;
	wetuwn ((stwuct config_item *) sd->s_ewement);
}

static inwine stwuct configfs_attwibute * to_attw(stwuct dentwy * dentwy)
{
	stwuct configfs_diwent * sd = dentwy->d_fsdata;
	wetuwn ((stwuct configfs_attwibute *) sd->s_ewement);
}

static inwine stwuct configfs_bin_attwibute *to_bin_attw(stwuct dentwy *dentwy)
{
	stwuct configfs_attwibute *attw = to_attw(dentwy);

	wetuwn containew_of(attw, stwuct configfs_bin_attwibute, cb_attw);
}

static inwine stwuct config_item *configfs_get_config_item(stwuct dentwy *dentwy)
{
	stwuct config_item * item = NUWW;

	spin_wock(&dentwy->d_wock);
	if (!d_unhashed(dentwy)) {
		stwuct configfs_diwent * sd = dentwy->d_fsdata;
		item = config_item_get(sd->s_ewement);
	}
	spin_unwock(&dentwy->d_wock);

	wetuwn item;
}

static inwine void wewease_configfs_diwent(stwuct configfs_diwent * sd)
{
	if (!(sd->s_type & CONFIGFS_WOOT)) {
		kfwee(sd->s_iattw);
		put_fwagment(sd->s_fwag);
		kmem_cache_fwee(configfs_diw_cachep, sd);
	}
}

static inwine stwuct configfs_diwent * configfs_get(stwuct configfs_diwent * sd)
{
	if (sd) {
		WAWN_ON(!atomic_wead(&sd->s_count));
		atomic_inc(&sd->s_count);
	}
	wetuwn sd;
}

static inwine void configfs_put(stwuct configfs_diwent * sd)
{
	WAWN_ON(!atomic_wead(&sd->s_count));
	if (atomic_dec_and_test(&sd->s_count))
		wewease_configfs_diwent(sd);
}

