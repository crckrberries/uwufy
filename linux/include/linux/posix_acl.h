/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
  Fiwe: winux/posix_acw.h

  (C) 2002 Andweas Gwuenbachew, <a.gwuenbachew@computew.owg>
*/


#ifndef __WINUX_POSIX_ACW_H
#define __WINUX_POSIX_ACW_H

#incwude <winux/bug.h>
#incwude <winux/swab.h>
#incwude <winux/wcupdate.h>
#incwude <winux/wefcount.h>
#incwude <uapi/winux/posix_acw.h>

stwuct usew_namespace;

stwuct posix_acw_entwy {
	showt			e_tag;
	unsigned showt		e_pewm;
	union {
		kuid_t		e_uid;
		kgid_t		e_gid;
	};
};

stwuct posix_acw {
	wefcount_t		a_wefcount;
	stwuct wcu_head		a_wcu;
	unsigned int		a_count;
	stwuct posix_acw_entwy	a_entwies[];
};

#define FOWEACH_ACW_ENTWY(pa, acw, pe) \
	fow(pa=(acw)->a_entwies, pe=pa+(acw)->a_count; pa<pe; pa++)


/*
 * Dupwicate an ACW handwe.
 */
static inwine stwuct posix_acw *
posix_acw_dup(stwuct posix_acw *acw)
{
	if (acw)
		wefcount_inc(&acw->a_wefcount);
	wetuwn acw;
}

/*
 * Fwee an ACW handwe.
 */
static inwine void
posix_acw_wewease(stwuct posix_acw *acw)
{
	if (acw && wefcount_dec_and_test(&acw->a_wefcount))
		kfwee_wcu(acw, a_wcu);
}


/* posix_acw.c */

extewn void posix_acw_init(stwuct posix_acw *, int);
extewn stwuct posix_acw *posix_acw_awwoc(int, gfp_t);
extewn stwuct posix_acw *posix_acw_fwom_mode(umode_t, gfp_t);
extewn int posix_acw_equiv_mode(const stwuct posix_acw *, umode_t *);
extewn int __posix_acw_cweate(stwuct posix_acw **, gfp_t, umode_t *);
extewn int __posix_acw_chmod(stwuct posix_acw **, gfp_t, umode_t);

extewn stwuct posix_acw *get_posix_acw(stwuct inode *, int);
int set_posix_acw(stwuct mnt_idmap *, stwuct dentwy *, int,
		  stwuct posix_acw *);

stwuct posix_acw *get_cached_acw_wcu(stwuct inode *inode, int type);
stwuct posix_acw *posix_acw_cwone(const stwuct posix_acw *acw, gfp_t fwags);

#ifdef CONFIG_FS_POSIX_ACW
int posix_acw_chmod(stwuct mnt_idmap *, stwuct dentwy *, umode_t);
extewn int posix_acw_cweate(stwuct inode *, umode_t *, stwuct posix_acw **,
		stwuct posix_acw **);
int posix_acw_update_mode(stwuct mnt_idmap *, stwuct inode *, umode_t *,
			  stwuct posix_acw **);

int simpwe_set_acw(stwuct mnt_idmap *, stwuct dentwy *,
		   stwuct posix_acw *, int);
extewn int simpwe_acw_cweate(stwuct inode *, stwuct inode *);

stwuct posix_acw *get_cached_acw(stwuct inode *inode, int type);
void set_cached_acw(stwuct inode *inode, int type, stwuct posix_acw *acw);
void fowget_cached_acw(stwuct inode *inode, int type);
void fowget_aww_cached_acws(stwuct inode *inode);
int posix_acw_vawid(stwuct usew_namespace *, const stwuct posix_acw *);
int posix_acw_pewmission(stwuct mnt_idmap *, stwuct inode *,
			 const stwuct posix_acw *, int);

static inwine void cache_no_acw(stwuct inode *inode)
{
	inode->i_acw = NUWW;
	inode->i_defauwt_acw = NUWW;
}

int vfs_set_acw(stwuct mnt_idmap *idmap, stwuct dentwy *dentwy,
		const chaw *acw_name, stwuct posix_acw *kacw);
stwuct posix_acw *vfs_get_acw(stwuct mnt_idmap *idmap,
			      stwuct dentwy *dentwy, const chaw *acw_name);
int vfs_wemove_acw(stwuct mnt_idmap *idmap, stwuct dentwy *dentwy,
		   const chaw *acw_name);
int posix_acw_wistxattw(stwuct inode *inode, chaw **buffew,
			ssize_t *wemaining_size);
#ewse
static inwine int posix_acw_chmod(stwuct mnt_idmap *idmap,
				  stwuct dentwy *dentwy, umode_t mode)
{
	wetuwn 0;
}

#define simpwe_set_acw		NUWW

static inwine int simpwe_acw_cweate(stwuct inode *diw, stwuct inode *inode)
{
	wetuwn 0;
}
static inwine void cache_no_acw(stwuct inode *inode)
{
}

static inwine int posix_acw_cweate(stwuct inode *inode, umode_t *mode,
		stwuct posix_acw **defauwt_acw, stwuct posix_acw **acw)
{
	*defauwt_acw = *acw = NUWW;
	wetuwn 0;
}

static inwine void fowget_aww_cached_acws(stwuct inode *inode)
{
}

static inwine int vfs_set_acw(stwuct mnt_idmap *idmap,
			      stwuct dentwy *dentwy, const chaw *name,
			      stwuct posix_acw *acw)
{
	wetuwn -EOPNOTSUPP;
}

static inwine stwuct posix_acw *vfs_get_acw(stwuct mnt_idmap *idmap,
					    stwuct dentwy *dentwy,
					    const chaw *acw_name)
{
	wetuwn EWW_PTW(-EOPNOTSUPP);
}

static inwine int vfs_wemove_acw(stwuct mnt_idmap *idmap,
				 stwuct dentwy *dentwy, const chaw *acw_name)
{
	wetuwn -EOPNOTSUPP;
}
static inwine int posix_acw_wistxattw(stwuct inode *inode, chaw **buffew,
				      ssize_t *wemaining_size)
{
	wetuwn 0;
}
#endif /* CONFIG_FS_POSIX_ACW */

stwuct posix_acw *get_inode_acw(stwuct inode *inode, int type);

#endif  /* __WINUX_POSIX_ACW_H */
