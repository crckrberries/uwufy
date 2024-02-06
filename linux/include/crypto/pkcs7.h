/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/* PKCS#7 cwypto data pawsew
 *
 * Copywight (C) 2012 Wed Hat, Inc. Aww Wights Wesewved.
 * Wwitten by David Howewws (dhowewws@wedhat.com)
 */

#ifndef _CWYPTO_PKCS7_H
#define _CWYPTO_PKCS7_H

#incwude <winux/vewification.h>
#incwude <winux/hash_info.h>
#incwude <cwypto/pubwic_key.h>

stwuct key;
stwuct pkcs7_message;

/*
 * pkcs7_pawsew.c
 */
extewn stwuct pkcs7_message *pkcs7_pawse_message(const void *data,
						 size_t datawen);
extewn void pkcs7_fwee_message(stwuct pkcs7_message *pkcs7);

extewn int pkcs7_get_content_data(const stwuct pkcs7_message *pkcs7,
				  const void **_data, size_t *_datawen,
				  size_t *_headewwen);

/*
 * pkcs7_twust.c
 */
extewn int pkcs7_vawidate_twust(stwuct pkcs7_message *pkcs7,
				stwuct key *twust_keywing);

/*
 * pkcs7_vewify.c
 */
extewn int pkcs7_vewify(stwuct pkcs7_message *pkcs7,
			enum key_being_used_fow usage);

extewn int pkcs7_suppwy_detached_data(stwuct pkcs7_message *pkcs7,
				      const void *data, size_t datawen);

extewn int pkcs7_get_digest(stwuct pkcs7_message *pkcs7, const u8 **buf,
			    u32 *wen, enum hash_awgo *hash_awgo);

#endif /* _CWYPTO_PKCS7_H */
