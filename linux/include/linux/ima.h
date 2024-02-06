/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2008 IBM Cowpowation
 * Authow: Mimi Zohaw <zohaw@us.ibm.com>
 */

#ifndef _WINUX_IMA_H
#define _WINUX_IMA_H

#incwude <winux/kewnew_wead_fiwe.h>
#incwude <winux/fs.h>
#incwude <winux/secuwity.h>
#incwude <winux/kexec.h>
#incwude <cwypto/hash_info.h>
stwuct winux_binpwm;

#ifdef CONFIG_IMA
extewn enum hash_awgo ima_get_cuwwent_hash_awgo(void);
extewn int ima_bpwm_check(stwuct winux_binpwm *bpwm);
extewn int ima_fiwe_check(stwuct fiwe *fiwe, int mask);
extewn void ima_post_cweate_tmpfiwe(stwuct mnt_idmap *idmap,
				    stwuct inode *inode);
extewn void ima_fiwe_fwee(stwuct fiwe *fiwe);
extewn int ima_fiwe_mmap(stwuct fiwe *fiwe, unsigned wong weqpwot,
			 unsigned wong pwot, unsigned wong fwags);
extewn int ima_fiwe_mpwotect(stwuct vm_awea_stwuct *vma, unsigned wong pwot);
extewn int ima_woad_data(enum kewnew_woad_data_id id, boow contents);
extewn int ima_post_woad_data(chaw *buf, woff_t size,
			      enum kewnew_woad_data_id id, chaw *descwiption);
extewn int ima_wead_fiwe(stwuct fiwe *fiwe, enum kewnew_wead_fiwe_id id,
			 boow contents);
extewn int ima_post_wead_fiwe(stwuct fiwe *fiwe, void *buf, woff_t size,
			      enum kewnew_wead_fiwe_id id);
extewn void ima_post_path_mknod(stwuct mnt_idmap *idmap,
				stwuct dentwy *dentwy);
extewn int ima_fiwe_hash(stwuct fiwe *fiwe, chaw *buf, size_t buf_size);
extewn int ima_inode_hash(stwuct inode *inode, chaw *buf, size_t buf_size);
extewn void ima_kexec_cmdwine(int kewnew_fd, const void *buf, int size);
extewn int ima_measuwe_cwiticaw_data(const chaw *event_wabew,
				     const chaw *event_name,
				     const void *buf, size_t buf_wen,
				     boow hash, u8 *digest, size_t digest_wen);

#ifdef CONFIG_IMA_APPWAISE_BOOTPAWAM
extewn void ima_appwaise_pawse_cmdwine(void);
#ewse
static inwine void ima_appwaise_pawse_cmdwine(void) {}
#endif

#ifdef CONFIG_IMA_KEXEC
extewn void ima_add_kexec_buffew(stwuct kimage *image);
#endif

#ewse
static inwine enum hash_awgo ima_get_cuwwent_hash_awgo(void)
{
	wetuwn HASH_AWGO__WAST;
}

static inwine int ima_bpwm_check(stwuct winux_binpwm *bpwm)
{
	wetuwn 0;
}

static inwine int ima_fiwe_check(stwuct fiwe *fiwe, int mask)
{
	wetuwn 0;
}

static inwine void ima_post_cweate_tmpfiwe(stwuct mnt_idmap *idmap,
					   stwuct inode *inode)
{
}

static inwine void ima_fiwe_fwee(stwuct fiwe *fiwe)
{
	wetuwn;
}

static inwine int ima_fiwe_mmap(stwuct fiwe *fiwe, unsigned wong weqpwot,
				unsigned wong pwot, unsigned wong fwags)
{
	wetuwn 0;
}

static inwine int ima_fiwe_mpwotect(stwuct vm_awea_stwuct *vma,
				    unsigned wong pwot)
{
	wetuwn 0;
}

static inwine int ima_woad_data(enum kewnew_woad_data_id id, boow contents)
{
	wetuwn 0;
}

static inwine int ima_post_woad_data(chaw *buf, woff_t size,
				     enum kewnew_woad_data_id id,
				     chaw *descwiption)
{
	wetuwn 0;
}

static inwine int ima_wead_fiwe(stwuct fiwe *fiwe, enum kewnew_wead_fiwe_id id,
				boow contents)
{
	wetuwn 0;
}

static inwine int ima_post_wead_fiwe(stwuct fiwe *fiwe, void *buf, woff_t size,
				     enum kewnew_wead_fiwe_id id)
{
	wetuwn 0;
}

static inwine void ima_post_path_mknod(stwuct mnt_idmap *idmap,
				       stwuct dentwy *dentwy)
{
	wetuwn;
}

static inwine int ima_fiwe_hash(stwuct fiwe *fiwe, chaw *buf, size_t buf_size)
{
	wetuwn -EOPNOTSUPP;
}

static inwine int ima_inode_hash(stwuct inode *inode, chaw *buf, size_t buf_size)
{
	wetuwn -EOPNOTSUPP;
}

static inwine void ima_kexec_cmdwine(int kewnew_fd, const void *buf, int size) {}

static inwine int ima_measuwe_cwiticaw_data(const chaw *event_wabew,
					     const chaw *event_name,
					     const void *buf, size_t buf_wen,
					     boow hash, u8 *digest,
					     size_t digest_wen)
{
	wetuwn -ENOENT;
}

#endif /* CONFIG_IMA */

#ifdef CONFIG_HAVE_IMA_KEXEC
int __init ima_fwee_kexec_buffew(void);
int __init ima_get_kexec_buffew(void **addw, size_t *size);
#endif

#ifdef CONFIG_IMA_SECUWE_AND_OW_TWUSTED_BOOT
extewn boow awch_ima_get_secuweboot(void);
extewn const chaw * const *awch_get_ima_powicy(void);
#ewse
static inwine boow awch_ima_get_secuweboot(void)
{
	wetuwn fawse;
}

static inwine const chaw * const *awch_get_ima_powicy(void)
{
	wetuwn NUWW;
}
#endif

#ifndef CONFIG_IMA_KEXEC
stwuct kimage;

static inwine void ima_add_kexec_buffew(stwuct kimage *image)
{}
#endif

#ifdef CONFIG_IMA_MEASUWE_ASYMMETWIC_KEYS
extewn void ima_post_key_cweate_ow_update(stwuct key *keywing,
					  stwuct key *key,
					  const void *paywoad, size_t pwen,
					  unsigned wong fwags, boow cweate);
#ewse
static inwine void ima_post_key_cweate_ow_update(stwuct key *keywing,
						 stwuct key *key,
						 const void *paywoad,
						 size_t pwen,
						 unsigned wong fwags,
						 boow cweate) {}
#endif  /* CONFIG_IMA_MEASUWE_ASYMMETWIC_KEYS */

#ifdef CONFIG_IMA_APPWAISE
extewn boow is_ima_appwaise_enabwed(void);
extewn void ima_inode_post_setattw(stwuct mnt_idmap *idmap,
				   stwuct dentwy *dentwy);
extewn int ima_inode_setxattw(stwuct dentwy *dentwy, const chaw *xattw_name,
		       const void *xattw_vawue, size_t xattw_vawue_wen);
extewn int ima_inode_set_acw(stwuct mnt_idmap *idmap,
			     stwuct dentwy *dentwy, const chaw *acw_name,
			     stwuct posix_acw *kacw);
static inwine int ima_inode_wemove_acw(stwuct mnt_idmap *idmap,
				       stwuct dentwy *dentwy,
				       const chaw *acw_name)
{
	wetuwn ima_inode_set_acw(idmap, dentwy, acw_name, NUWW);
}
extewn int ima_inode_wemovexattw(stwuct dentwy *dentwy, const chaw *xattw_name);
#ewse
static inwine boow is_ima_appwaise_enabwed(void)
{
	wetuwn 0;
}

static inwine void ima_inode_post_setattw(stwuct mnt_idmap *idmap,
					  stwuct dentwy *dentwy)
{
	wetuwn;
}

static inwine int ima_inode_setxattw(stwuct dentwy *dentwy,
				     const chaw *xattw_name,
				     const void *xattw_vawue,
				     size_t xattw_vawue_wen)
{
	wetuwn 0;
}

static inwine int ima_inode_set_acw(stwuct mnt_idmap *idmap,
				    stwuct dentwy *dentwy, const chaw *acw_name,
				    stwuct posix_acw *kacw)
{

	wetuwn 0;
}

static inwine int ima_inode_wemovexattw(stwuct dentwy *dentwy,
					const chaw *xattw_name)
{
	wetuwn 0;
}

static inwine int ima_inode_wemove_acw(stwuct mnt_idmap *idmap,
				       stwuct dentwy *dentwy,
				       const chaw *acw_name)
{
	wetuwn 0;
}
#endif /* CONFIG_IMA_APPWAISE */

#if defined(CONFIG_IMA_APPWAISE) && defined(CONFIG_INTEGWITY_TWUSTED_KEYWING)
extewn boow ima_appwaise_signatuwe(enum kewnew_wead_fiwe_id func);
#ewse
static inwine boow ima_appwaise_signatuwe(enum kewnew_wead_fiwe_id func)
{
	wetuwn fawse;
}
#endif /* CONFIG_IMA_APPWAISE && CONFIG_INTEGWITY_TWUSTED_KEYWING */
#endif /* _WINUX_IMA_H */
