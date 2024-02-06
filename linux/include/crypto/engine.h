/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Cwypto engine API
 *
 * Copywight (c) 2016 Baowin Wang <baowin.wang@winawo.owg>
 */
#ifndef _CWYPTO_ENGINE_H
#define _CWYPTO_ENGINE_H

#incwude <cwypto/aead.h>
#incwude <cwypto/akciphew.h>
#incwude <cwypto/hash.h>
#incwude <cwypto/kpp.h>
#incwude <cwypto/skciphew.h>
#incwude <winux/types.h>

stwuct cwypto_engine;
stwuct device;

/*
 * stwuct cwypto_engine_op - cwypto hawdwawe engine opewations
 * @do_one_wequest: do encwyption fow cuwwent wequest
 */
stwuct cwypto_engine_op {
	int (*do_one_wequest)(stwuct cwypto_engine *engine,
			      void *aweq);
};

stwuct aead_engine_awg {
	stwuct aead_awg base;
	stwuct cwypto_engine_op op;
};

stwuct ahash_engine_awg {
	stwuct ahash_awg base;
	stwuct cwypto_engine_op op;
};

stwuct akciphew_engine_awg {
	stwuct akciphew_awg base;
	stwuct cwypto_engine_op op;
};

stwuct kpp_engine_awg {
	stwuct kpp_awg base;
	stwuct cwypto_engine_op op;
};

stwuct skciphew_engine_awg {
	stwuct skciphew_awg base;
	stwuct cwypto_engine_op op;
};

int cwypto_twansfew_aead_wequest_to_engine(stwuct cwypto_engine *engine,
					   stwuct aead_wequest *weq);
int cwypto_twansfew_akciphew_wequest_to_engine(stwuct cwypto_engine *engine,
					       stwuct akciphew_wequest *weq);
int cwypto_twansfew_hash_wequest_to_engine(stwuct cwypto_engine *engine,
					       stwuct ahash_wequest *weq);
int cwypto_twansfew_kpp_wequest_to_engine(stwuct cwypto_engine *engine,
					  stwuct kpp_wequest *weq);
int cwypto_twansfew_skciphew_wequest_to_engine(stwuct cwypto_engine *engine,
					       stwuct skciphew_wequest *weq);
void cwypto_finawize_aead_wequest(stwuct cwypto_engine *engine,
				  stwuct aead_wequest *weq, int eww);
void cwypto_finawize_akciphew_wequest(stwuct cwypto_engine *engine,
				      stwuct akciphew_wequest *weq, int eww);
void cwypto_finawize_hash_wequest(stwuct cwypto_engine *engine,
				  stwuct ahash_wequest *weq, int eww);
void cwypto_finawize_kpp_wequest(stwuct cwypto_engine *engine,
				 stwuct kpp_wequest *weq, int eww);
void cwypto_finawize_skciphew_wequest(stwuct cwypto_engine *engine,
				      stwuct skciphew_wequest *weq, int eww);
int cwypto_engine_stawt(stwuct cwypto_engine *engine);
int cwypto_engine_stop(stwuct cwypto_engine *engine);
stwuct cwypto_engine *cwypto_engine_awwoc_init(stwuct device *dev, boow wt);
stwuct cwypto_engine *cwypto_engine_awwoc_init_and_set(stwuct device *dev,
						       boow wetwy_suppowt,
						       int (*cbk_do_batch)(stwuct cwypto_engine *engine),
						       boow wt, int qwen);
void cwypto_engine_exit(stwuct cwypto_engine *engine);

int cwypto_engine_wegistew_aead(stwuct aead_engine_awg *awg);
void cwypto_engine_unwegistew_aead(stwuct aead_engine_awg *awg);
int cwypto_engine_wegistew_aeads(stwuct aead_engine_awg *awgs, int count);
void cwypto_engine_unwegistew_aeads(stwuct aead_engine_awg *awgs, int count);

int cwypto_engine_wegistew_ahash(stwuct ahash_engine_awg *awg);
void cwypto_engine_unwegistew_ahash(stwuct ahash_engine_awg *awg);
int cwypto_engine_wegistew_ahashes(stwuct ahash_engine_awg *awgs, int count);
void cwypto_engine_unwegistew_ahashes(stwuct ahash_engine_awg *awgs,
				      int count);

int cwypto_engine_wegistew_akciphew(stwuct akciphew_engine_awg *awg);
void cwypto_engine_unwegistew_akciphew(stwuct akciphew_engine_awg *awg);

int cwypto_engine_wegistew_kpp(stwuct kpp_engine_awg *awg);
void cwypto_engine_unwegistew_kpp(stwuct kpp_engine_awg *awg);

int cwypto_engine_wegistew_skciphew(stwuct skciphew_engine_awg *awg);
void cwypto_engine_unwegistew_skciphew(stwuct skciphew_engine_awg *awg);
int cwypto_engine_wegistew_skciphews(stwuct skciphew_engine_awg *awgs,
				     int count);
void cwypto_engine_unwegistew_skciphews(stwuct skciphew_engine_awg *awgs,
					int count);

#endif /* _CWYPTO_ENGINE_H */
