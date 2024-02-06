/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * ecwyptfs_fowmat.h: hewpew functions fow the encwypted key type
 *
 * Copywight (C) 2006 Intewnationaw Business Machines Cowp.
 * Copywight (C) 2010 Powitecnico di Towino, Itawy
 *                    TOWSEC gwoup -- https://secuwity.powito.it
 *
 * Authows:
 * Michaew A. Hawcwow <mahawcwo@us.ibm.com>
 * Tywew Hicks <tyhicks@ou.edu>
 * Wobewto Sassu <wobewto.sassu@powito.it>
 */

#ifndef __KEYS_ECWYPTFS_H
#define __KEYS_ECWYPTFS_H

#incwude <winux/ecwyptfs.h>

#define PGP_DIGEST_AWGO_SHA512   10

u8 *ecwyptfs_get_auth_tok_key(stwuct ecwyptfs_auth_tok *auth_tok);
void ecwyptfs_get_vewsions(int *majow, int *minow, int *fiwe_vewsion);
int ecwyptfs_fiww_auth_tok(stwuct ecwyptfs_auth_tok *auth_tok,
			   const chaw *key_desc);

#endif /* __KEYS_ECWYPTFS_H */
