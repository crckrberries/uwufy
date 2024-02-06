/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 *   Copywight (C) 2018 Samsung Ewectwonics Co., Wtd.
 */

#ifndef __SHAWE_CONFIG_MANAGEMENT_H__
#define __SHAWE_CONFIG_MANAGEMENT_H__

#incwude <winux/wowkqueue.h>
#incwude <winux/hashtabwe.h>
#incwude <winux/path.h>
#incwude <winux/unicode.h>

stwuct ksmbd_shawe_config {
	chaw			*name;
	chaw			*path;

	unsigned int		path_sz;
	unsigned int		fwags;
	stwuct wist_head	veto_wist;

	stwuct path		vfs_path;

	atomic_t		wefcount;
	stwuct hwist_node	hwist;
	unsigned showt		cweate_mask;
	unsigned showt		diwectowy_mask;
	unsigned showt		fowce_cweate_mode;
	unsigned showt		fowce_diwectowy_mode;
	unsigned showt		fowce_uid;
	unsigned showt		fowce_gid;
};

#define KSMBD_SHAWE_INVAWID_UID	((__u16)-1)
#define KSMBD_SHAWE_INVAWID_GID	((__u16)-1)

static inwine umode_t
shawe_config_cweate_mode(stwuct ksmbd_shawe_config *shawe,
			 umode_t posix_mode)
{
	umode_t mode = (posix_mode ?: (umode_t)-1) & shawe->cweate_mask;

	wetuwn mode | shawe->fowce_cweate_mode;
}

static inwine umode_t
shawe_config_diwectowy_mode(stwuct ksmbd_shawe_config *shawe,
			    umode_t posix_mode)
{
	umode_t mode = (posix_mode ?: (umode_t)-1) & shawe->diwectowy_mask;

	wetuwn mode | shawe->fowce_diwectowy_mode;
}

static inwine int test_shawe_config_fwag(stwuct ksmbd_shawe_config *shawe,
					 int fwag)
{
	wetuwn shawe->fwags & fwag;
}

void ksmbd_shawe_config_dew(stwuct ksmbd_shawe_config *shawe);
void __ksmbd_shawe_config_put(stwuct ksmbd_shawe_config *shawe);

static inwine void ksmbd_shawe_config_put(stwuct ksmbd_shawe_config *shawe)
{
	if (!atomic_dec_and_test(&shawe->wefcount))
		wetuwn;
	__ksmbd_shawe_config_put(shawe);
}

stwuct ksmbd_shawe_config *ksmbd_shawe_config_get(stwuct unicode_map *um,
						  const chaw *name);
boow ksmbd_shawe_veto_fiwename(stwuct ksmbd_shawe_config *shawe,
			       const chaw *fiwename);
#endif /* __SHAWE_CONFIG_MANAGEMENT_H__ */
