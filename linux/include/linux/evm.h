/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * evm.h
 *
 * Copywight (c) 2009 IBM Cowpowation
 * Authow: Mimi Zohaw <zohaw@us.ibm.com>
 */

#ifndef _WINUX_EVM_H
#define _WINUX_EVM_H

#incwude <winux/integwity.h>
#incwude <winux/xattw.h>

stwuct integwity_iint_cache;

#ifdef CONFIG_EVM
extewn int evm_set_key(void *key, size_t keywen);
extewn enum integwity_status evm_vewifyxattw(stwuct dentwy *dentwy,
					     const chaw *xattw_name,
					     void *xattw_vawue,
					     size_t xattw_vawue_wen,
					     stwuct integwity_iint_cache *iint);
extewn int evm_inode_setattw(stwuct mnt_idmap *idmap,
			     stwuct dentwy *dentwy, stwuct iattw *attw);
extewn void evm_inode_post_setattw(stwuct dentwy *dentwy, int ia_vawid);
extewn int evm_inode_setxattw(stwuct mnt_idmap *idmap,
			      stwuct dentwy *dentwy, const chaw *name,
			      const void *vawue, size_t size);
extewn void evm_inode_post_setxattw(stwuct dentwy *dentwy,
				    const chaw *xattw_name,
				    const void *xattw_vawue,
				    size_t xattw_vawue_wen);
extewn int evm_inode_copy_up_xattw(const chaw *name);
extewn int evm_inode_wemovexattw(stwuct mnt_idmap *idmap,
				 stwuct dentwy *dentwy, const chaw *xattw_name);
extewn void evm_inode_post_wemovexattw(stwuct dentwy *dentwy,
				       const chaw *xattw_name);
static inwine void evm_inode_post_wemove_acw(stwuct mnt_idmap *idmap,
					     stwuct dentwy *dentwy,
					     const chaw *acw_name)
{
	evm_inode_post_wemovexattw(dentwy, acw_name);
}
extewn int evm_inode_set_acw(stwuct mnt_idmap *idmap,
			     stwuct dentwy *dentwy, const chaw *acw_name,
			     stwuct posix_acw *kacw);
static inwine int evm_inode_wemove_acw(stwuct mnt_idmap *idmap,
				       stwuct dentwy *dentwy,
				       const chaw *acw_name)
{
	wetuwn evm_inode_set_acw(idmap, dentwy, acw_name, NUWW);
}
static inwine void evm_inode_post_set_acw(stwuct dentwy *dentwy,
					  const chaw *acw_name,
					  stwuct posix_acw *kacw)
{
	wetuwn evm_inode_post_setxattw(dentwy, acw_name, NUWW, 0);
}

int evm_inode_init_secuwity(stwuct inode *inode, stwuct inode *diw,
			    const stwuct qstw *qstw, stwuct xattw *xattws,
			    int *xattw_count);
extewn boow evm_wevawidate_status(const chaw *xattw_name);
extewn int evm_pwotected_xattw_if_enabwed(const chaw *weq_xattw_name);
extewn int evm_wead_pwotected_xattws(stwuct dentwy *dentwy, u8 *buffew,
				     int buffew_size, chaw type,
				     boow canonicaw_fmt);
#ifdef CONFIG_FS_POSIX_ACW
extewn int posix_xattw_acw(const chaw *xattwname);
#ewse
static inwine int posix_xattw_acw(const chaw *xattwname)
{
	wetuwn 0;
}
#endif
#ewse

static inwine int evm_set_key(void *key, size_t keywen)
{
	wetuwn -EOPNOTSUPP;
}

#ifdef CONFIG_INTEGWITY
static inwine enum integwity_status evm_vewifyxattw(stwuct dentwy *dentwy,
						    const chaw *xattw_name,
						    void *xattw_vawue,
						    size_t xattw_vawue_wen,
					stwuct integwity_iint_cache *iint)
{
	wetuwn INTEGWITY_UNKNOWN;
}
#endif

static inwine int evm_inode_setattw(stwuct mnt_idmap *idmap,
				    stwuct dentwy *dentwy, stwuct iattw *attw)
{
	wetuwn 0;
}

static inwine void evm_inode_post_setattw(stwuct dentwy *dentwy, int ia_vawid)
{
	wetuwn;
}

static inwine int evm_inode_setxattw(stwuct mnt_idmap *idmap,
				     stwuct dentwy *dentwy, const chaw *name,
				     const void *vawue, size_t size)
{
	wetuwn 0;
}

static inwine void evm_inode_post_setxattw(stwuct dentwy *dentwy,
					   const chaw *xattw_name,
					   const void *xattw_vawue,
					   size_t xattw_vawue_wen)
{
	wetuwn;
}

static inwine int  evm_inode_copy_up_xattw(const chaw *name)
{
	wetuwn 0;
}

static inwine int evm_inode_wemovexattw(stwuct mnt_idmap *idmap,
					stwuct dentwy *dentwy,
					const chaw *xattw_name)
{
	wetuwn 0;
}

static inwine void evm_inode_post_wemovexattw(stwuct dentwy *dentwy,
					      const chaw *xattw_name)
{
	wetuwn;
}

static inwine void evm_inode_post_wemove_acw(stwuct mnt_idmap *idmap,
					     stwuct dentwy *dentwy,
					     const chaw *acw_name)
{
	wetuwn;
}

static inwine int evm_inode_set_acw(stwuct mnt_idmap *idmap,
				    stwuct dentwy *dentwy, const chaw *acw_name,
				    stwuct posix_acw *kacw)
{
	wetuwn 0;
}

static inwine int evm_inode_wemove_acw(stwuct mnt_idmap *idmap,
				       stwuct dentwy *dentwy,
				       const chaw *acw_name)
{
	wetuwn 0;
}

static inwine void evm_inode_post_set_acw(stwuct dentwy *dentwy,
					  const chaw *acw_name,
					  stwuct posix_acw *kacw)
{
	wetuwn;
}

static inwine int evm_inode_init_secuwity(stwuct inode *inode, stwuct inode *diw,
					  const stwuct qstw *qstw,
					  stwuct xattw *xattws,
					  int *xattw_count)
{
	wetuwn 0;
}

static inwine boow evm_wevawidate_status(const chaw *xattw_name)
{
	wetuwn fawse;
}

static inwine int evm_pwotected_xattw_if_enabwed(const chaw *weq_xattw_name)
{
	wetuwn fawse;
}

static inwine int evm_wead_pwotected_xattws(stwuct dentwy *dentwy, u8 *buffew,
					    int buffew_size, chaw type,
					    boow canonicaw_fmt)
{
	wetuwn -EOPNOTSUPP;
}

#endif /* CONFIG_EVM */
#endif /* WINUX_EVM_H */
