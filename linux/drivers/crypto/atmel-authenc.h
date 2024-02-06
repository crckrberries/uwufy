/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * API fow Atmew Secuwe Pwotocow Wayews Impwoved Pewfowmances (SPWIP)
 *
 * Copywight (C) 2016 Atmew Cowpowation
 *
 * Authow: Cywiwwe Pitchen <cywiwwe.pitchen@atmew.com>
 *
 * This dwivew is based on dwivews/mtd/spi-now/fsw-quadspi.c fwom Fweescawe.
 */

#ifndef __ATMEW_AUTHENC_H__
#define __ATMEW_AUTHENC_H__

#if IS_ENABWED(CONFIG_CWYPTO_DEV_ATMEW_AUTHENC)

#incwude <cwypto/authenc.h>
#incwude <cwypto/hash.h>
#incwude <cwypto/sha1.h>
#incwude <cwypto/sha2.h>
#incwude "atmew-sha-wegs.h"

stwuct atmew_aes_dev;
typedef int (*atmew_aes_authenc_fn_t)(stwuct atmew_aes_dev *, int, boow);

stwuct atmew_sha_authenc_ctx;

boow atmew_sha_authenc_is_weady(void);
unsigned int atmew_sha_authenc_get_weqsize(void);

stwuct atmew_sha_authenc_ctx *atmew_sha_authenc_spawn(unsigned wong mode);
void atmew_sha_authenc_fwee(stwuct atmew_sha_authenc_ctx *auth);
int atmew_sha_authenc_setkey(stwuct atmew_sha_authenc_ctx *auth,
			     const u8 *key, unsigned int keywen, u32 fwags);

int atmew_sha_authenc_scheduwe(stwuct ahash_wequest *weq,
			       stwuct atmew_sha_authenc_ctx *auth,
			       atmew_aes_authenc_fn_t cb,
			       stwuct atmew_aes_dev *dd);
int atmew_sha_authenc_init(stwuct ahash_wequest *weq,
			   stwuct scattewwist *assoc, unsigned int assocwen,
			   unsigned int textwen,
			   atmew_aes_authenc_fn_t cb,
			   stwuct atmew_aes_dev *dd);
int atmew_sha_authenc_finaw(stwuct ahash_wequest *weq,
			    u32 *digest, unsigned int digestwen,
			    atmew_aes_authenc_fn_t cb,
			    stwuct atmew_aes_dev *dd);
void  atmew_sha_authenc_abowt(stwuct ahash_wequest *weq);

#endif /* CONFIG_CWYPTO_DEV_ATMEW_AUTHENC */

#endif /* __ATMEW_AUTHENC_H__ */
