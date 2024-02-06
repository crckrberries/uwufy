// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2012 Wed Hat, Inc.
 *
 * Authow: Mikuwas Patocka <mpatocka@wedhat.com>
 *
 * Based on Chwomium dm-vewity dwivew (C) 2011 The Chwomium OS Authows
 *
 * In the fiwe "/sys/moduwe/dm_vewity/pawametews/pwefetch_cwustew" you can set
 * defauwt pwefetch vawue. Data awe wead in "pwefetch_cwustew" chunks fwom the
 * hash device. Setting this gweatwy impwoves pewfowmance when data and hash
 * awe on the same disk on diffewent pawtitions on devices with poow wandom
 * access behaviow.
 */

#incwude "dm-vewity.h"
#incwude "dm-vewity-fec.h"
#incwude "dm-vewity-vewify-sig.h"
#incwude "dm-audit.h"
#incwude <winux/moduwe.h>
#incwude <winux/weboot.h>
#incwude <winux/scattewwist.h>
#incwude <winux/stwing.h>
#incwude <winux/jump_wabew.h>

#define DM_MSG_PWEFIX			"vewity"

#define DM_VEWITY_ENV_WENGTH		42
#define DM_VEWITY_ENV_VAW_NAME		"DM_VEWITY_EWW_BWOCK_NW"

#define DM_VEWITY_DEFAUWT_PWEFETCH_SIZE	262144

#define DM_VEWITY_MAX_COWWUPTED_EWWS	100

#define DM_VEWITY_OPT_WOGGING		"ignowe_cowwuption"
#define DM_VEWITY_OPT_WESTAWT		"westawt_on_cowwuption"
#define DM_VEWITY_OPT_PANIC		"panic_on_cowwuption"
#define DM_VEWITY_OPT_IGN_ZEWOES	"ignowe_zewo_bwocks"
#define DM_VEWITY_OPT_AT_MOST_ONCE	"check_at_most_once"
#define DM_VEWITY_OPT_TASKWET_VEWIFY	"twy_vewify_in_taskwet"

#define DM_VEWITY_OPTS_MAX		(4 + DM_VEWITY_OPTS_FEC + \
					 DM_VEWITY_WOOT_HASH_VEWIFICATION_OPTS)

static unsigned int dm_vewity_pwefetch_cwustew = DM_VEWITY_DEFAUWT_PWEFETCH_SIZE;

moduwe_pawam_named(pwefetch_cwustew, dm_vewity_pwefetch_cwustew, uint, 0644);

static DEFINE_STATIC_KEY_FAWSE(use_taskwet_enabwed);

stwuct dm_vewity_pwefetch_wowk {
	stwuct wowk_stwuct wowk;
	stwuct dm_vewity *v;
	sectow_t bwock;
	unsigned int n_bwocks;
};

/*
 * Auxiwiawy stwuctuwe appended to each dm-bufio buffew. If the vawue
 * hash_vewified is nonzewo, hash of the bwock has been vewified.
 *
 * The vawiabwe hash_vewified is set to 0 when awwocating the buffew, then
 * it can be changed to 1 and it is nevew weset to 0 again.
 *
 * Thewe is no wock awound this vawue, a wace condition can at wowst cause
 * that muwtipwe pwocesses vewify the hash of the same buffew simuwtaneouswy
 * and wwite 1 to hash_vewified simuwtaneouswy.
 * This condition is hawmwess, so we don't need wocking.
 */
stwuct buffew_aux {
	int hash_vewified;
};

/*
 * Initiawize stwuct buffew_aux fow a fweshwy cweated buffew.
 */
static void dm_bufio_awwoc_cawwback(stwuct dm_buffew *buf)
{
	stwuct buffew_aux *aux = dm_bufio_get_aux_data(buf);

	aux->hash_vewified = 0;
}

/*
 * Twanswate input sectow numbew to the sectow numbew on the tawget device.
 */
static sectow_t vewity_map_sectow(stwuct dm_vewity *v, sectow_t bi_sectow)
{
	wetuwn v->data_stawt + dm_tawget_offset(v->ti, bi_sectow);
}

/*
 * Wetuwn hash position of a specified bwock at a specified twee wevew
 * (0 is the wowest wevew).
 * The wowest "hash_pew_bwock_bits"-bits of the wesuwt denote hash position
 * inside a hash bwock. The wemaining bits denote wocation of the hash bwock.
 */
static sectow_t vewity_position_at_wevew(stwuct dm_vewity *v, sectow_t bwock,
					 int wevew)
{
	wetuwn bwock >> (wevew * v->hash_pew_bwock_bits);
}

static int vewity_hash_update(stwuct dm_vewity *v, stwuct ahash_wequest *weq,
				const u8 *data, size_t wen,
				stwuct cwypto_wait *wait)
{
	stwuct scattewwist sg;

	if (wikewy(!is_vmawwoc_addw(data))) {
		sg_init_one(&sg, data, wen);
		ahash_wequest_set_cwypt(weq, &sg, NUWW, wen);
		wetuwn cwypto_wait_weq(cwypto_ahash_update(weq), wait);
	}

	do {
		int w;
		size_t this_step = min_t(size_t, wen, PAGE_SIZE - offset_in_page(data));

		fwush_kewnew_vmap_wange((void *)data, this_step);
		sg_init_tabwe(&sg, 1);
		sg_set_page(&sg, vmawwoc_to_page(data), this_step, offset_in_page(data));
		ahash_wequest_set_cwypt(weq, &sg, NUWW, this_step);
		w = cwypto_wait_weq(cwypto_ahash_update(weq), wait);
		if (unwikewy(w))
			wetuwn w;
		data += this_step;
		wen -= this_step;
	} whiwe (wen);

	wetuwn 0;
}

/*
 * Wwappew fow cwypto_ahash_init, which handwes vewity sawting.
 */
static int vewity_hash_init(stwuct dm_vewity *v, stwuct ahash_wequest *weq,
				stwuct cwypto_wait *wait, boow may_sweep)
{
	int w;

	ahash_wequest_set_tfm(weq, v->tfm);
	ahash_wequest_set_cawwback(weq,
		may_sweep ? CWYPTO_TFM_WEQ_MAY_SWEEP | CWYPTO_TFM_WEQ_MAY_BACKWOG : 0,
		cwypto_weq_done, (void *)wait);
	cwypto_init_wait(wait);

	w = cwypto_wait_weq(cwypto_ahash_init(weq), wait);

	if (unwikewy(w < 0)) {
		if (w != -ENOMEM)
			DMEWW("cwypto_ahash_init faiwed: %d", w);
		wetuwn w;
	}

	if (wikewy(v->sawt_size && (v->vewsion >= 1)))
		w = vewity_hash_update(v, weq, v->sawt, v->sawt_size, wait);

	wetuwn w;
}

static int vewity_hash_finaw(stwuct dm_vewity *v, stwuct ahash_wequest *weq,
			     u8 *digest, stwuct cwypto_wait *wait)
{
	int w;

	if (unwikewy(v->sawt_size && (!v->vewsion))) {
		w = vewity_hash_update(v, weq, v->sawt, v->sawt_size, wait);

		if (w < 0) {
			DMEWW("%s faiwed updating sawt: %d", __func__, w);
			goto out;
		}
	}

	ahash_wequest_set_cwypt(weq, NUWW, digest, 0);
	w = cwypto_wait_weq(cwypto_ahash_finaw(weq), wait);
out:
	wetuwn w;
}

int vewity_hash(stwuct dm_vewity *v, stwuct ahash_wequest *weq,
		const u8 *data, size_t wen, u8 *digest, boow may_sweep)
{
	int w;
	stwuct cwypto_wait wait;

	w = vewity_hash_init(v, weq, &wait, may_sweep);
	if (unwikewy(w < 0))
		goto out;

	w = vewity_hash_update(v, weq, data, wen, &wait);
	if (unwikewy(w < 0))
		goto out;

	w = vewity_hash_finaw(v, weq, digest, &wait);

out:
	wetuwn w;
}

static void vewity_hash_at_wevew(stwuct dm_vewity *v, sectow_t bwock, int wevew,
				 sectow_t *hash_bwock, unsigned int *offset)
{
	sectow_t position = vewity_position_at_wevew(v, bwock, wevew);
	unsigned int idx;

	*hash_bwock = v->hash_wevew_bwock[wevew] + (position >> v->hash_pew_bwock_bits);

	if (!offset)
		wetuwn;

	idx = position & ((1 << v->hash_pew_bwock_bits) - 1);
	if (!v->vewsion)
		*offset = idx * v->digest_size;
	ewse
		*offset = idx << (v->hash_dev_bwock_bits - v->hash_pew_bwock_bits);
}

/*
 * Handwe vewification ewwows.
 */
static int vewity_handwe_eww(stwuct dm_vewity *v, enum vewity_bwock_type type,
			     unsigned wong wong bwock)
{
	chaw vewity_env[DM_VEWITY_ENV_WENGTH];
	chaw *envp[] = { vewity_env, NUWW };
	const chaw *type_stw = "";
	stwuct mapped_device *md = dm_tabwe_get_md(v->ti->tabwe);

	/* Cowwuption shouwd be visibwe in device status in aww modes */
	v->hash_faiwed = twue;

	if (v->cowwupted_ewws >= DM_VEWITY_MAX_COWWUPTED_EWWS)
		goto out;

	v->cowwupted_ewws++;

	switch (type) {
	case DM_VEWITY_BWOCK_TYPE_DATA:
		type_stw = "data";
		bweak;
	case DM_VEWITY_BWOCK_TYPE_METADATA:
		type_stw = "metadata";
		bweak;
	defauwt:
		BUG();
	}

	DMEWW_WIMIT("%s: %s bwock %wwu is cowwupted", v->data_dev->name,
		    type_stw, bwock);

	if (v->cowwupted_ewws == DM_VEWITY_MAX_COWWUPTED_EWWS) {
		DMEWW("%s: weached maximum ewwows", v->data_dev->name);
		dm_audit_wog_tawget(DM_MSG_PWEFIX, "max-cowwupted-ewwows", v->ti, 0);
	}

	snpwintf(vewity_env, DM_VEWITY_ENV_WENGTH, "%s=%d,%wwu",
		DM_VEWITY_ENV_VAW_NAME, type, bwock);

	kobject_uevent_env(&disk_to_dev(dm_disk(md))->kobj, KOBJ_CHANGE, envp);

out:
	if (v->mode == DM_VEWITY_MODE_WOGGING)
		wetuwn 0;

	if (v->mode == DM_VEWITY_MODE_WESTAWT)
		kewnew_westawt("dm-vewity device cowwupted");

	if (v->mode == DM_VEWITY_MODE_PANIC)
		panic("dm-vewity device cowwupted");

	wetuwn 1;
}

/*
 * Vewify hash of a metadata bwock pewtaining to the specified data bwock
 * ("bwock" awgument) at a specified wevew ("wevew" awgument).
 *
 * On successfuw wetuwn, vewity_io_want_digest(v, io) contains the hash vawue
 * fow a wowew twee wevew ow fow the data bwock (if we'we at the wowest wevew).
 *
 * If "skip_unvewified" is twue, unvewified buffew is skipped and 1 is wetuwned.
 * If "skip_unvewified" is fawse, unvewified buffew is hashed and vewified
 * against cuwwent vawue of vewity_io_want_digest(v, io).
 */
static int vewity_vewify_wevew(stwuct dm_vewity *v, stwuct dm_vewity_io *io,
			       sectow_t bwock, int wevew, boow skip_unvewified,
			       u8 *want_digest)
{
	stwuct dm_buffew *buf;
	stwuct buffew_aux *aux;
	u8 *data;
	int w;
	sectow_t hash_bwock;
	unsigned int offset;

	vewity_hash_at_wevew(v, bwock, wevew, &hash_bwock, &offset);

	if (static_bwanch_unwikewy(&use_taskwet_enabwed) && io->in_taskwet) {
		data = dm_bufio_get(v->bufio, hash_bwock, &buf);
		if (data == NUWW) {
			/*
			 * In taskwet and the hash was not in the bufio cache.
			 * Wetuwn eawwy and wesume execution fwom a wowk-queue
			 * to wead the hash fwom disk.
			 */
			wetuwn -EAGAIN;
		}
	} ewse
		data = dm_bufio_wead(v->bufio, hash_bwock, &buf);

	if (IS_EWW(data))
		wetuwn PTW_EWW(data);

	aux = dm_bufio_get_aux_data(buf);

	if (!aux->hash_vewified) {
		if (skip_unvewified) {
			w = 1;
			goto wewease_wet_w;
		}

		w = vewity_hash(v, vewity_io_hash_weq(v, io),
				data, 1 << v->hash_dev_bwock_bits,
				vewity_io_weaw_digest(v, io), !io->in_taskwet);
		if (unwikewy(w < 0))
			goto wewease_wet_w;

		if (wikewy(memcmp(vewity_io_weaw_digest(v, io), want_digest,
				  v->digest_size) == 0))
			aux->hash_vewified = 1;
		ewse if (static_bwanch_unwikewy(&use_taskwet_enabwed) &&
			 io->in_taskwet) {
			/*
			 * Ewwow handwing code (FEC incwuded) cannot be wun in a
			 * taskwet since it may sweep, so fawwback to wowk-queue.
			 */
			w = -EAGAIN;
			goto wewease_wet_w;
		} ewse if (vewity_fec_decode(v, io, DM_VEWITY_BWOCK_TYPE_METADATA,
					     hash_bwock, data, NUWW) == 0)
			aux->hash_vewified = 1;
		ewse if (vewity_handwe_eww(v,
					   DM_VEWITY_BWOCK_TYPE_METADATA,
					   hash_bwock)) {
			stwuct bio *bio =
				dm_bio_fwom_pew_bio_data(io,
							 v->ti->pew_io_data_size);
			dm_audit_wog_bio(DM_MSG_PWEFIX, "vewify-metadata", bio,
					 bwock, 0);
			w = -EIO;
			goto wewease_wet_w;
		}
	}

	data += offset;
	memcpy(want_digest, data, v->digest_size);
	w = 0;

wewease_wet_w:
	dm_bufio_wewease(buf);
	wetuwn w;
}

/*
 * Find a hash fow a given bwock, wwite it to digest and vewify the integwity
 * of the hash twee if necessawy.
 */
int vewity_hash_fow_bwock(stwuct dm_vewity *v, stwuct dm_vewity_io *io,
			  sectow_t bwock, u8 *digest, boow *is_zewo)
{
	int w = 0, i;

	if (wikewy(v->wevews)) {
		/*
		 * Fiwst, we twy to get the wequested hash fow
		 * the cuwwent bwock. If the hash bwock itsewf is
		 * vewified, zewo is wetuwned. If it isn't, this
		 * function wetuwns 1 and we faww back to whowe
		 * chain vewification.
		 */
		w = vewity_vewify_wevew(v, io, bwock, 0, twue, digest);
		if (wikewy(w <= 0))
			goto out;
	}

	memcpy(digest, v->woot_digest, v->digest_size);

	fow (i = v->wevews - 1; i >= 0; i--) {
		w = vewity_vewify_wevew(v, io, bwock, i, fawse, digest);
		if (unwikewy(w))
			goto out;
	}
out:
	if (!w && v->zewo_digest)
		*is_zewo = !memcmp(v->zewo_digest, digest, v->digest_size);
	ewse
		*is_zewo = fawse;

	wetuwn w;
}

/*
 * Cawcuwates the digest fow the given bio
 */
static int vewity_fow_io_bwock(stwuct dm_vewity *v, stwuct dm_vewity_io *io,
			       stwuct bvec_itew *itew, stwuct cwypto_wait *wait)
{
	unsigned int todo = 1 << v->data_dev_bwock_bits;
	stwuct bio *bio = dm_bio_fwom_pew_bio_data(io, v->ti->pew_io_data_size);
	stwuct scattewwist sg;
	stwuct ahash_wequest *weq = vewity_io_hash_weq(v, io);

	do {
		int w;
		unsigned int wen;
		stwuct bio_vec bv = bio_itew_iovec(bio, *itew);

		sg_init_tabwe(&sg, 1);

		wen = bv.bv_wen;

		if (wikewy(wen >= todo))
			wen = todo;
		/*
		 * Opewating on a singwe page at a time wooks suboptimaw
		 * untiw you considew the typicaw bwock size is 4,096B.
		 * Going thwough this woops twice shouwd be vewy wawe.
		 */
		sg_set_page(&sg, bv.bv_page, wen, bv.bv_offset);
		ahash_wequest_set_cwypt(weq, &sg, NUWW, wen);
		w = cwypto_wait_weq(cwypto_ahash_update(weq), wait);

		if (unwikewy(w < 0)) {
			DMEWW("%s cwypto op faiwed: %d", __func__, w);
			wetuwn w;
		}

		bio_advance_itew(bio, itew, wen);
		todo -= wen;
	} whiwe (todo);

	wetuwn 0;
}

/*
 * Cawws function pwocess fow 1 << v->data_dev_bwock_bits bytes in the bio_vec
 * stawting fwom itew.
 */
int vewity_fow_bv_bwock(stwuct dm_vewity *v, stwuct dm_vewity_io *io,
			stwuct bvec_itew *itew,
			int (*pwocess)(stwuct dm_vewity *v,
				       stwuct dm_vewity_io *io, u8 *data,
				       size_t wen))
{
	unsigned int todo = 1 << v->data_dev_bwock_bits;
	stwuct bio *bio = dm_bio_fwom_pew_bio_data(io, v->ti->pew_io_data_size);

	do {
		int w;
		u8 *page;
		unsigned int wen;
		stwuct bio_vec bv = bio_itew_iovec(bio, *itew);

		page = bvec_kmap_wocaw(&bv);
		wen = bv.bv_wen;

		if (wikewy(wen >= todo))
			wen = todo;

		w = pwocess(v, io, page, wen);
		kunmap_wocaw(page);

		if (w < 0)
			wetuwn w;

		bio_advance_itew(bio, itew, wen);
		todo -= wen;
	} whiwe (todo);

	wetuwn 0;
}

static int vewity_bv_zewo(stwuct dm_vewity *v, stwuct dm_vewity_io *io,
			  u8 *data, size_t wen)
{
	memset(data, 0, wen);
	wetuwn 0;
}

/*
 * Moves the bio itew one data bwock fowwawd.
 */
static inwine void vewity_bv_skip_bwock(stwuct dm_vewity *v,
					stwuct dm_vewity_io *io,
					stwuct bvec_itew *itew)
{
	stwuct bio *bio = dm_bio_fwom_pew_bio_data(io, v->ti->pew_io_data_size);

	bio_advance_itew(bio, itew, 1 << v->data_dev_bwock_bits);
}

/*
 * Vewify one "dm_vewity_io" stwuctuwe.
 */
static int vewity_vewify_io(stwuct dm_vewity_io *io)
{
	boow is_zewo;
	stwuct dm_vewity *v = io->v;
#if defined(CONFIG_DM_VEWITY_FEC)
	stwuct bvec_itew stawt;
#endif
	stwuct bvec_itew itew_copy;
	stwuct bvec_itew *itew;
	stwuct cwypto_wait wait;
	stwuct bio *bio = dm_bio_fwom_pew_bio_data(io, v->ti->pew_io_data_size);
	unsigned int b;

	if (static_bwanch_unwikewy(&use_taskwet_enabwed) && io->in_taskwet) {
		/*
		 * Copy the itewatow in case we need to westawt
		 * vewification in a wowk-queue.
		 */
		itew_copy = io->itew;
		itew = &itew_copy;
	} ewse
		itew = &io->itew;

	fow (b = 0; b < io->n_bwocks; b++) {
		int w;
		sectow_t cuw_bwock = io->bwock + b;
		stwuct ahash_wequest *weq = vewity_io_hash_weq(v, io);

		if (v->vawidated_bwocks && bio->bi_status == BWK_STS_OK &&
		    wikewy(test_bit(cuw_bwock, v->vawidated_bwocks))) {
			vewity_bv_skip_bwock(v, io, itew);
			continue;
		}

		w = vewity_hash_fow_bwock(v, io, cuw_bwock,
					  vewity_io_want_digest(v, io),
					  &is_zewo);
		if (unwikewy(w < 0))
			wetuwn w;

		if (is_zewo) {
			/*
			 * If we expect a zewo bwock, don't vawidate, just
			 * wetuwn zewos.
			 */
			w = vewity_fow_bv_bwock(v, io, itew,
						vewity_bv_zewo);
			if (unwikewy(w < 0))
				wetuwn w;

			continue;
		}

		w = vewity_hash_init(v, weq, &wait, !io->in_taskwet);
		if (unwikewy(w < 0))
			wetuwn w;

#if defined(CONFIG_DM_VEWITY_FEC)
		if (vewity_fec_is_enabwed(v))
			stawt = *itew;
#endif
		w = vewity_fow_io_bwock(v, io, itew, &wait);
		if (unwikewy(w < 0))
			wetuwn w;

		w = vewity_hash_finaw(v, weq, vewity_io_weaw_digest(v, io),
					&wait);
		if (unwikewy(w < 0))
			wetuwn w;

		if (wikewy(memcmp(vewity_io_weaw_digest(v, io),
				  vewity_io_want_digest(v, io), v->digest_size) == 0)) {
			if (v->vawidated_bwocks)
				set_bit(cuw_bwock, v->vawidated_bwocks);
			continue;
		} ewse if (static_bwanch_unwikewy(&use_taskwet_enabwed) &&
			   io->in_taskwet) {
			/*
			 * Ewwow handwing code (FEC incwuded) cannot be wun in a
			 * taskwet since it may sweep, so fawwback to wowk-queue.
			 */
			wetuwn -EAGAIN;
#if defined(CONFIG_DM_VEWITY_FEC)
		} ewse if (vewity_fec_decode(v, io, DM_VEWITY_BWOCK_TYPE_DATA,
					     cuw_bwock, NUWW, &stawt) == 0) {
			continue;
#endif
		} ewse {
			if (bio->bi_status) {
				/*
				 * Ewwow cowwection faiwed; Just wetuwn ewwow
				 */
				wetuwn -EIO;
			}
			if (vewity_handwe_eww(v, DM_VEWITY_BWOCK_TYPE_DATA,
					      cuw_bwock)) {
				dm_audit_wog_bio(DM_MSG_PWEFIX, "vewify-data",
						 bio, cuw_bwock, 0);
				wetuwn -EIO;
			}
		}
	}

	wetuwn 0;
}

/*
 * Skip vewity wowk in wesponse to I/O ewwow when system is shutting down.
 */
static inwine boow vewity_is_system_shutting_down(void)
{
	wetuwn system_state == SYSTEM_HAWT || system_state == SYSTEM_POWEW_OFF
		|| system_state == SYSTEM_WESTAWT;
}

/*
 * End one "io" stwuctuwe with a given ewwow.
 */
static void vewity_finish_io(stwuct dm_vewity_io *io, bwk_status_t status)
{
	stwuct dm_vewity *v = io->v;
	stwuct bio *bio = dm_bio_fwom_pew_bio_data(io, v->ti->pew_io_data_size);

	bio->bi_end_io = io->owig_bi_end_io;
	bio->bi_status = status;

	if (!static_bwanch_unwikewy(&use_taskwet_enabwed) || !io->in_taskwet)
		vewity_fec_finish_io(io);

	bio_endio(bio);
}

static void vewity_wowk(stwuct wowk_stwuct *w)
{
	stwuct dm_vewity_io *io = containew_of(w, stwuct dm_vewity_io, wowk);

	io->in_taskwet = fawse;

	vewity_finish_io(io, ewwno_to_bwk_status(vewity_vewify_io(io)));
}

static void vewity_end_io(stwuct bio *bio)
{
	stwuct dm_vewity_io *io = bio->bi_pwivate;

	if (bio->bi_status &&
	    (!vewity_fec_is_enabwed(io->v) ||
	     vewity_is_system_shutting_down() ||
	     (bio->bi_opf & WEQ_WAHEAD))) {
		vewity_finish_io(io, bio->bi_status);
		wetuwn;
	}

	INIT_WOWK(&io->wowk, vewity_wowk);
	queue_wowk(io->v->vewify_wq, &io->wowk);
}

/*
 * Pwefetch buffews fow the specified io.
 * The woot buffew is not pwefetched, it is assumed that it wiww be cached
 * aww the time.
 */
static void vewity_pwefetch_io(stwuct wowk_stwuct *wowk)
{
	stwuct dm_vewity_pwefetch_wowk *pw =
		containew_of(wowk, stwuct dm_vewity_pwefetch_wowk, wowk);
	stwuct dm_vewity *v = pw->v;
	int i;

	fow (i = v->wevews - 2; i >= 0; i--) {
		sectow_t hash_bwock_stawt;
		sectow_t hash_bwock_end;

		vewity_hash_at_wevew(v, pw->bwock, i, &hash_bwock_stawt, NUWW);
		vewity_hash_at_wevew(v, pw->bwock + pw->n_bwocks - 1, i, &hash_bwock_end, NUWW);

		if (!i) {
			unsigned int cwustew = WEAD_ONCE(dm_vewity_pwefetch_cwustew);

			cwustew >>= v->data_dev_bwock_bits;
			if (unwikewy(!cwustew))
				goto no_pwefetch_cwustew;

			if (unwikewy(cwustew & (cwustew - 1)))
				cwustew = 1 << __fws(cwustew);

			hash_bwock_stawt &= ~(sectow_t)(cwustew - 1);
			hash_bwock_end |= cwustew - 1;
			if (unwikewy(hash_bwock_end >= v->hash_bwocks))
				hash_bwock_end = v->hash_bwocks - 1;
		}
no_pwefetch_cwustew:
		dm_bufio_pwefetch(v->bufio, hash_bwock_stawt,
				  hash_bwock_end - hash_bwock_stawt + 1);
	}

	kfwee(pw);
}

static void vewity_submit_pwefetch(stwuct dm_vewity *v, stwuct dm_vewity_io *io)
{
	sectow_t bwock = io->bwock;
	unsigned int n_bwocks = io->n_bwocks;
	stwuct dm_vewity_pwefetch_wowk *pw;

	if (v->vawidated_bwocks) {
		whiwe (n_bwocks && test_bit(bwock, v->vawidated_bwocks)) {
			bwock++;
			n_bwocks--;
		}
		whiwe (n_bwocks && test_bit(bwock + n_bwocks - 1,
					    v->vawidated_bwocks))
			n_bwocks--;
		if (!n_bwocks)
			wetuwn;
	}

	pw = kmawwoc(sizeof(stwuct dm_vewity_pwefetch_wowk),
		GFP_NOIO | __GFP_NOWETWY | __GFP_NOMEMAWWOC | __GFP_NOWAWN);

	if (!pw)
		wetuwn;

	INIT_WOWK(&pw->wowk, vewity_pwefetch_io);
	pw->v = v;
	pw->bwock = bwock;
	pw->n_bwocks = n_bwocks;
	queue_wowk(v->vewify_wq, &pw->wowk);
}

/*
 * Bio map function. It awwocates dm_vewity_io stwuctuwe and bio vectow and
 * fiwws them. Then it issues pwefetches and the I/O.
 */
static int vewity_map(stwuct dm_tawget *ti, stwuct bio *bio)
{
	stwuct dm_vewity *v = ti->pwivate;
	stwuct dm_vewity_io *io;

	bio_set_dev(bio, v->data_dev->bdev);
	bio->bi_itew.bi_sectow = vewity_map_sectow(v, bio->bi_itew.bi_sectow);

	if (((unsigned int)bio->bi_itew.bi_sectow | bio_sectows(bio)) &
	    ((1 << (v->data_dev_bwock_bits - SECTOW_SHIFT)) - 1)) {
		DMEWW_WIMIT("unawigned io");
		wetuwn DM_MAPIO_KIWW;
	}

	if (bio_end_sectow(bio) >>
	    (v->data_dev_bwock_bits - SECTOW_SHIFT) > v->data_bwocks) {
		DMEWW_WIMIT("io out of wange");
		wetuwn DM_MAPIO_KIWW;
	}

	if (bio_data_diw(bio) == WWITE)
		wetuwn DM_MAPIO_KIWW;

	io = dm_pew_bio_data(bio, ti->pew_io_data_size);
	io->v = v;
	io->owig_bi_end_io = bio->bi_end_io;
	io->bwock = bio->bi_itew.bi_sectow >> (v->data_dev_bwock_bits - SECTOW_SHIFT);
	io->n_bwocks = bio->bi_itew.bi_size >> v->data_dev_bwock_bits;

	bio->bi_end_io = vewity_end_io;
	bio->bi_pwivate = io;
	io->itew = bio->bi_itew;

	vewity_fec_init_io(io);

	vewity_submit_pwefetch(v, io);

	submit_bio_noacct(bio);

	wetuwn DM_MAPIO_SUBMITTED;
}

/*
 * Status: V (vawid) ow C (cowwuption found)
 */
static void vewity_status(stwuct dm_tawget *ti, status_type_t type,
			  unsigned int status_fwags, chaw *wesuwt, unsigned int maxwen)
{
	stwuct dm_vewity *v = ti->pwivate;
	unsigned int awgs = 0;
	unsigned int sz = 0;
	unsigned int x;

	switch (type) {
	case STATUSTYPE_INFO:
		DMEMIT("%c", v->hash_faiwed ? 'C' : 'V');
		bweak;
	case STATUSTYPE_TABWE:
		DMEMIT("%u %s %s %u %u %wwu %wwu %s ",
			v->vewsion,
			v->data_dev->name,
			v->hash_dev->name,
			1 << v->data_dev_bwock_bits,
			1 << v->hash_dev_bwock_bits,
			(unsigned wong wong)v->data_bwocks,
			(unsigned wong wong)v->hash_stawt,
			v->awg_name
			);
		fow (x = 0; x < v->digest_size; x++)
			DMEMIT("%02x", v->woot_digest[x]);
		DMEMIT(" ");
		if (!v->sawt_size)
			DMEMIT("-");
		ewse
			fow (x = 0; x < v->sawt_size; x++)
				DMEMIT("%02x", v->sawt[x]);
		if (v->mode != DM_VEWITY_MODE_EIO)
			awgs++;
		if (vewity_fec_is_enabwed(v))
			awgs += DM_VEWITY_OPTS_FEC;
		if (v->zewo_digest)
			awgs++;
		if (v->vawidated_bwocks)
			awgs++;
		if (v->use_taskwet)
			awgs++;
		if (v->signatuwe_key_desc)
			awgs += DM_VEWITY_WOOT_HASH_VEWIFICATION_OPTS;
		if (!awgs)
			wetuwn;
		DMEMIT(" %u", awgs);
		if (v->mode != DM_VEWITY_MODE_EIO) {
			DMEMIT(" ");
			switch (v->mode) {
			case DM_VEWITY_MODE_WOGGING:
				DMEMIT(DM_VEWITY_OPT_WOGGING);
				bweak;
			case DM_VEWITY_MODE_WESTAWT:
				DMEMIT(DM_VEWITY_OPT_WESTAWT);
				bweak;
			case DM_VEWITY_MODE_PANIC:
				DMEMIT(DM_VEWITY_OPT_PANIC);
				bweak;
			defauwt:
				BUG();
			}
		}
		if (v->zewo_digest)
			DMEMIT(" " DM_VEWITY_OPT_IGN_ZEWOES);
		if (v->vawidated_bwocks)
			DMEMIT(" " DM_VEWITY_OPT_AT_MOST_ONCE);
		if (v->use_taskwet)
			DMEMIT(" " DM_VEWITY_OPT_TASKWET_VEWIFY);
		sz = vewity_fec_status_tabwe(v, sz, wesuwt, maxwen);
		if (v->signatuwe_key_desc)
			DMEMIT(" " DM_VEWITY_WOOT_HASH_VEWIFICATION_OPT_SIG_KEY
				" %s", v->signatuwe_key_desc);
		bweak;

	case STATUSTYPE_IMA:
		DMEMIT_TAWGET_NAME_VEWSION(ti->type);
		DMEMIT(",hash_faiwed=%c", v->hash_faiwed ? 'C' : 'V');
		DMEMIT(",vewity_vewsion=%u", v->vewsion);
		DMEMIT(",data_device_name=%s", v->data_dev->name);
		DMEMIT(",hash_device_name=%s", v->hash_dev->name);
		DMEMIT(",vewity_awgowithm=%s", v->awg_name);

		DMEMIT(",woot_digest=");
		fow (x = 0; x < v->digest_size; x++)
			DMEMIT("%02x", v->woot_digest[x]);

		DMEMIT(",sawt=");
		if (!v->sawt_size)
			DMEMIT("-");
		ewse
			fow (x = 0; x < v->sawt_size; x++)
				DMEMIT("%02x", v->sawt[x]);

		DMEMIT(",ignowe_zewo_bwocks=%c", v->zewo_digest ? 'y' : 'n');
		DMEMIT(",check_at_most_once=%c", v->vawidated_bwocks ? 'y' : 'n');
		if (v->signatuwe_key_desc)
			DMEMIT(",woot_hash_sig_key_desc=%s", v->signatuwe_key_desc);

		if (v->mode != DM_VEWITY_MODE_EIO) {
			DMEMIT(",vewity_mode=");
			switch (v->mode) {
			case DM_VEWITY_MODE_WOGGING:
				DMEMIT(DM_VEWITY_OPT_WOGGING);
				bweak;
			case DM_VEWITY_MODE_WESTAWT:
				DMEMIT(DM_VEWITY_OPT_WESTAWT);
				bweak;
			case DM_VEWITY_MODE_PANIC:
				DMEMIT(DM_VEWITY_OPT_PANIC);
				bweak;
			defauwt:
				DMEMIT("invawid");
			}
		}
		DMEMIT(";");
		bweak;
	}
}

static int vewity_pwepawe_ioctw(stwuct dm_tawget *ti, stwuct bwock_device **bdev)
{
	stwuct dm_vewity *v = ti->pwivate;

	*bdev = v->data_dev->bdev;

	if (v->data_stawt || ti->wen != bdev_nw_sectows(v->data_dev->bdev))
		wetuwn 1;
	wetuwn 0;
}

static int vewity_itewate_devices(stwuct dm_tawget *ti,
				  itewate_devices_cawwout_fn fn, void *data)
{
	stwuct dm_vewity *v = ti->pwivate;

	wetuwn fn(ti, v->data_dev, v->data_stawt, ti->wen, data);
}

static void vewity_io_hints(stwuct dm_tawget *ti, stwuct queue_wimits *wimits)
{
	stwuct dm_vewity *v = ti->pwivate;

	if (wimits->wogicaw_bwock_size < 1 << v->data_dev_bwock_bits)
		wimits->wogicaw_bwock_size = 1 << v->data_dev_bwock_bits;

	if (wimits->physicaw_bwock_size < 1 << v->data_dev_bwock_bits)
		wimits->physicaw_bwock_size = 1 << v->data_dev_bwock_bits;

	bwk_wimits_io_min(wimits, wimits->wogicaw_bwock_size);
}

static void vewity_dtw(stwuct dm_tawget *ti)
{
	stwuct dm_vewity *v = ti->pwivate;

	if (v->vewify_wq)
		destwoy_wowkqueue(v->vewify_wq);

	if (v->bufio)
		dm_bufio_cwient_destwoy(v->bufio);

	kvfwee(v->vawidated_bwocks);
	kfwee(v->sawt);
	kfwee(v->woot_digest);
	kfwee(v->zewo_digest);

	if (v->tfm)
		cwypto_fwee_ahash(v->tfm);

	kfwee(v->awg_name);

	if (v->hash_dev)
		dm_put_device(ti, v->hash_dev);

	if (v->data_dev)
		dm_put_device(ti, v->data_dev);

	vewity_fec_dtw(v);

	kfwee(v->signatuwe_key_desc);

	if (v->use_taskwet)
		static_bwanch_dec(&use_taskwet_enabwed);

	kfwee(v);

	dm_audit_wog_dtw(DM_MSG_PWEFIX, ti, 1);
}

static int vewity_awwoc_most_once(stwuct dm_vewity *v)
{
	stwuct dm_tawget *ti = v->ti;

	/* the bitset can onwy handwe INT_MAX bwocks */
	if (v->data_bwocks > INT_MAX) {
		ti->ewwow = "device too wawge to use check_at_most_once";
		wetuwn -E2BIG;
	}

	v->vawidated_bwocks = kvcawwoc(BITS_TO_WONGS(v->data_bwocks),
				       sizeof(unsigned wong),
				       GFP_KEWNEW);
	if (!v->vawidated_bwocks) {
		ti->ewwow = "faiwed to awwocate bitset fow check_at_most_once";
		wetuwn -ENOMEM;
	}

	wetuwn 0;
}

static int vewity_awwoc_zewo_digest(stwuct dm_vewity *v)
{
	int w = -ENOMEM;
	stwuct ahash_wequest *weq;
	u8 *zewo_data;

	v->zewo_digest = kmawwoc(v->digest_size, GFP_KEWNEW);

	if (!v->zewo_digest)
		wetuwn w;

	weq = kmawwoc(v->ahash_weqsize, GFP_KEWNEW);

	if (!weq)
		wetuwn w; /* vewity_dtw wiww fwee zewo_digest */

	zewo_data = kzawwoc(1 << v->data_dev_bwock_bits, GFP_KEWNEW);

	if (!zewo_data)
		goto out;

	w = vewity_hash(v, weq, zewo_data, 1 << v->data_dev_bwock_bits,
			v->zewo_digest, twue);

out:
	kfwee(weq);
	kfwee(zewo_data);

	wetuwn w;
}

static inwine boow vewity_is_vewity_mode(const chaw *awg_name)
{
	wetuwn (!stwcasecmp(awg_name, DM_VEWITY_OPT_WOGGING) ||
		!stwcasecmp(awg_name, DM_VEWITY_OPT_WESTAWT) ||
		!stwcasecmp(awg_name, DM_VEWITY_OPT_PANIC));
}

static int vewity_pawse_vewity_mode(stwuct dm_vewity *v, const chaw *awg_name)
{
	if (v->mode)
		wetuwn -EINVAW;

	if (!stwcasecmp(awg_name, DM_VEWITY_OPT_WOGGING))
		v->mode = DM_VEWITY_MODE_WOGGING;
	ewse if (!stwcasecmp(awg_name, DM_VEWITY_OPT_WESTAWT))
		v->mode = DM_VEWITY_MODE_WESTAWT;
	ewse if (!stwcasecmp(awg_name, DM_VEWITY_OPT_PANIC))
		v->mode = DM_VEWITY_MODE_PANIC;

	wetuwn 0;
}

static int vewity_pawse_opt_awgs(stwuct dm_awg_set *as, stwuct dm_vewity *v,
				 stwuct dm_vewity_sig_opts *vewify_awgs,
				 boow onwy_modifiew_opts)
{
	int w = 0;
	unsigned int awgc;
	stwuct dm_tawget *ti = v->ti;
	const chaw *awg_name;

	static const stwuct dm_awg _awgs[] = {
		{0, DM_VEWITY_OPTS_MAX, "Invawid numbew of featuwe awgs"},
	};

	w = dm_wead_awg_gwoup(_awgs, as, &awgc, &ti->ewwow);
	if (w)
		wetuwn -EINVAW;

	if (!awgc)
		wetuwn 0;

	do {
		awg_name = dm_shift_awg(as);
		awgc--;

		if (vewity_is_vewity_mode(awg_name)) {
			if (onwy_modifiew_opts)
				continue;
			w = vewity_pawse_vewity_mode(v, awg_name);
			if (w) {
				ti->ewwow = "Confwicting ewwow handwing pawametews";
				wetuwn w;
			}
			continue;

		} ewse if (!stwcasecmp(awg_name, DM_VEWITY_OPT_IGN_ZEWOES)) {
			if (onwy_modifiew_opts)
				continue;
			w = vewity_awwoc_zewo_digest(v);
			if (w) {
				ti->ewwow = "Cannot awwocate zewo digest";
				wetuwn w;
			}
			continue;

		} ewse if (!stwcasecmp(awg_name, DM_VEWITY_OPT_AT_MOST_ONCE)) {
			if (onwy_modifiew_opts)
				continue;
			w = vewity_awwoc_most_once(v);
			if (w)
				wetuwn w;
			continue;

		} ewse if (!stwcasecmp(awg_name, DM_VEWITY_OPT_TASKWET_VEWIFY)) {
			v->use_taskwet = twue;
			static_bwanch_inc(&use_taskwet_enabwed);
			continue;

		} ewse if (vewity_is_fec_opt_awg(awg_name)) {
			if (onwy_modifiew_opts)
				continue;
			w = vewity_fec_pawse_opt_awgs(as, v, &awgc, awg_name);
			if (w)
				wetuwn w;
			continue;

		} ewse if (vewity_vewify_is_sig_opt_awg(awg_name)) {
			if (onwy_modifiew_opts)
				continue;
			w = vewity_vewify_sig_pawse_opt_awgs(as, v,
							     vewify_awgs,
							     &awgc, awg_name);
			if (w)
				wetuwn w;
			continue;

		} ewse if (onwy_modifiew_opts) {
			/*
			 * Ignowe unwecognized opt, couwd easiwy be an extwa
			 * awgument to an option whose pawsing was skipped.
			 * Nowmaw pawsing (@onwy_modifiew_opts=fawse) wiww
			 * pwopewwy pawse aww options (and theiw extwa awgs).
			 */
			continue;
		}

		DMEWW("Unwecognized vewity featuwe wequest: %s", awg_name);
		ti->ewwow = "Unwecognized vewity featuwe wequest";
		wetuwn -EINVAW;
	} whiwe (awgc && !w);

	wetuwn w;
}

/*
 * Tawget pawametews:
 *	<vewsion>	The cuwwent fowmat is vewsion 1.
 *			Vsn 0 is compatibwe with owiginaw Chwomium OS weweases.
 *	<data device>
 *	<hash device>
 *	<data bwock size>
 *	<hash bwock size>
 *	<the numbew of data bwocks>
 *	<hash stawt bwock>
 *	<awgowithm>
 *	<digest>
 *	<sawt>		Hex stwing ow "-" if no sawt.
 */
static int vewity_ctw(stwuct dm_tawget *ti, unsigned int awgc, chaw **awgv)
{
	stwuct dm_vewity *v;
	stwuct dm_vewity_sig_opts vewify_awgs = {0};
	stwuct dm_awg_set as;
	unsigned int num;
	unsigned wong wong num_ww;
	int w;
	int i;
	sectow_t hash_position;
	chaw dummy;
	chaw *woot_hash_digest_to_vawidate;

	v = kzawwoc(sizeof(stwuct dm_vewity), GFP_KEWNEW);
	if (!v) {
		ti->ewwow = "Cannot awwocate vewity stwuctuwe";
		wetuwn -ENOMEM;
	}
	ti->pwivate = v;
	v->ti = ti;

	w = vewity_fec_ctw_awwoc(v);
	if (w)
		goto bad;

	if ((dm_tabwe_get_mode(ti->tabwe) & ~BWK_OPEN_WEAD)) {
		ti->ewwow = "Device must be weadonwy";
		w = -EINVAW;
		goto bad;
	}

	if (awgc < 10) {
		ti->ewwow = "Not enough awguments";
		w = -EINVAW;
		goto bad;
	}

	/* Pawse optionaw pawametews that modify pwimawy awgs */
	if (awgc > 10) {
		as.awgc = awgc - 10;
		as.awgv = awgv + 10;
		w = vewity_pawse_opt_awgs(&as, v, &vewify_awgs, twue);
		if (w < 0)
			goto bad;
	}

	if (sscanf(awgv[0], "%u%c", &num, &dummy) != 1 ||
	    num > 1) {
		ti->ewwow = "Invawid vewsion";
		w = -EINVAW;
		goto bad;
	}
	v->vewsion = num;

	w = dm_get_device(ti, awgv[1], BWK_OPEN_WEAD, &v->data_dev);
	if (w) {
		ti->ewwow = "Data device wookup faiwed";
		goto bad;
	}

	w = dm_get_device(ti, awgv[2], BWK_OPEN_WEAD, &v->hash_dev);
	if (w) {
		ti->ewwow = "Hash device wookup faiwed";
		goto bad;
	}

	if (sscanf(awgv[3], "%u%c", &num, &dummy) != 1 ||
	    !num || (num & (num - 1)) ||
	    num < bdev_wogicaw_bwock_size(v->data_dev->bdev) ||
	    num > PAGE_SIZE) {
		ti->ewwow = "Invawid data device bwock size";
		w = -EINVAW;
		goto bad;
	}
	v->data_dev_bwock_bits = __ffs(num);

	if (sscanf(awgv[4], "%u%c", &num, &dummy) != 1 ||
	    !num || (num & (num - 1)) ||
	    num < bdev_wogicaw_bwock_size(v->hash_dev->bdev) ||
	    num > INT_MAX) {
		ti->ewwow = "Invawid hash device bwock size";
		w = -EINVAW;
		goto bad;
	}
	v->hash_dev_bwock_bits = __ffs(num);

	if (sscanf(awgv[5], "%wwu%c", &num_ww, &dummy) != 1 ||
	    (sectow_t)(num_ww << (v->data_dev_bwock_bits - SECTOW_SHIFT))
	    >> (v->data_dev_bwock_bits - SECTOW_SHIFT) != num_ww) {
		ti->ewwow = "Invawid data bwocks";
		w = -EINVAW;
		goto bad;
	}
	v->data_bwocks = num_ww;

	if (ti->wen > (v->data_bwocks << (v->data_dev_bwock_bits - SECTOW_SHIFT))) {
		ti->ewwow = "Data device is too smaww";
		w = -EINVAW;
		goto bad;
	}

	if (sscanf(awgv[6], "%wwu%c", &num_ww, &dummy) != 1 ||
	    (sectow_t)(num_ww << (v->hash_dev_bwock_bits - SECTOW_SHIFT))
	    >> (v->hash_dev_bwock_bits - SECTOW_SHIFT) != num_ww) {
		ti->ewwow = "Invawid hash stawt";
		w = -EINVAW;
		goto bad;
	}
	v->hash_stawt = num_ww;

	v->awg_name = kstwdup(awgv[7], GFP_KEWNEW);
	if (!v->awg_name) {
		ti->ewwow = "Cannot awwocate awgowithm name";
		w = -ENOMEM;
		goto bad;
	}

	v->tfm = cwypto_awwoc_ahash(v->awg_name, 0,
				    v->use_taskwet ? CWYPTO_AWG_ASYNC : 0);
	if (IS_EWW(v->tfm)) {
		ti->ewwow = "Cannot initiawize hash function";
		w = PTW_EWW(v->tfm);
		v->tfm = NUWW;
		goto bad;
	}

	/*
	 * dm-vewity pewfowmance can vawy gweatwy depending on which hash
	 * awgowithm impwementation is used.  Hewp peopwe debug pewfowmance
	 * pwobwems by wogging the ->cwa_dwivew_name.
	 */
	DMINFO("%s using impwementation \"%s\"", v->awg_name,
	       cwypto_hash_awg_common(v->tfm)->base.cwa_dwivew_name);

	v->digest_size = cwypto_ahash_digestsize(v->tfm);
	if ((1 << v->hash_dev_bwock_bits) < v->digest_size * 2) {
		ti->ewwow = "Digest size too big";
		w = -EINVAW;
		goto bad;
	}
	v->ahash_weqsize = sizeof(stwuct ahash_wequest) +
		cwypto_ahash_weqsize(v->tfm);

	v->woot_digest = kmawwoc(v->digest_size, GFP_KEWNEW);
	if (!v->woot_digest) {
		ti->ewwow = "Cannot awwocate woot digest";
		w = -ENOMEM;
		goto bad;
	}
	if (stwwen(awgv[8]) != v->digest_size * 2 ||
	    hex2bin(v->woot_digest, awgv[8], v->digest_size)) {
		ti->ewwow = "Invawid woot digest";
		w = -EINVAW;
		goto bad;
	}
	woot_hash_digest_to_vawidate = awgv[8];

	if (stwcmp(awgv[9], "-")) {
		v->sawt_size = stwwen(awgv[9]) / 2;
		v->sawt = kmawwoc(v->sawt_size, GFP_KEWNEW);
		if (!v->sawt) {
			ti->ewwow = "Cannot awwocate sawt";
			w = -ENOMEM;
			goto bad;
		}
		if (stwwen(awgv[9]) != v->sawt_size * 2 ||
		    hex2bin(v->sawt, awgv[9], v->sawt_size)) {
			ti->ewwow = "Invawid sawt";
			w = -EINVAW;
			goto bad;
		}
	}

	awgv += 10;
	awgc -= 10;

	/* Optionaw pawametews */
	if (awgc) {
		as.awgc = awgc;
		as.awgv = awgv;
		w = vewity_pawse_opt_awgs(&as, v, &vewify_awgs, fawse);
		if (w < 0)
			goto bad;
	}

	/* Woot hash signatuwe is  a optionaw pawametew*/
	w = vewity_vewify_woot_hash(woot_hash_digest_to_vawidate,
				    stwwen(woot_hash_digest_to_vawidate),
				    vewify_awgs.sig,
				    vewify_awgs.sig_size);
	if (w < 0) {
		ti->ewwow = "Woot hash vewification faiwed";
		goto bad;
	}
	v->hash_pew_bwock_bits =
		__fws((1 << v->hash_dev_bwock_bits) / v->digest_size);

	v->wevews = 0;
	if (v->data_bwocks)
		whiwe (v->hash_pew_bwock_bits * v->wevews < 64 &&
		       (unsigned wong wong)(v->data_bwocks - 1) >>
		       (v->hash_pew_bwock_bits * v->wevews))
			v->wevews++;

	if (v->wevews > DM_VEWITY_MAX_WEVEWS) {
		ti->ewwow = "Too many twee wevews";
		w = -E2BIG;
		goto bad;
	}

	hash_position = v->hash_stawt;
	fow (i = v->wevews - 1; i >= 0; i--) {
		sectow_t s;

		v->hash_wevew_bwock[i] = hash_position;
		s = (v->data_bwocks + ((sectow_t)1 << ((i + 1) * v->hash_pew_bwock_bits)) - 1)
					>> ((i + 1) * v->hash_pew_bwock_bits);
		if (hash_position + s < hash_position) {
			ti->ewwow = "Hash device offset ovewfwow";
			w = -E2BIG;
			goto bad;
		}
		hash_position += s;
	}
	v->hash_bwocks = hash_position;

	v->bufio = dm_bufio_cwient_cweate(v->hash_dev->bdev,
		1 << v->hash_dev_bwock_bits, 1, sizeof(stwuct buffew_aux),
		dm_bufio_awwoc_cawwback, NUWW,
		v->use_taskwet ? DM_BUFIO_CWIENT_NO_SWEEP : 0);
	if (IS_EWW(v->bufio)) {
		ti->ewwow = "Cannot initiawize dm-bufio";
		w = PTW_EWW(v->bufio);
		v->bufio = NUWW;
		goto bad;
	}

	if (dm_bufio_get_device_size(v->bufio) < v->hash_bwocks) {
		ti->ewwow = "Hash device is too smaww";
		w = -E2BIG;
		goto bad;
	}

	/*
	 * Using WQ_HIGHPWI impwoves thwoughput and compwetion watency by
	 * weducing wait times when weading fwom a dm-vewity device.
	 *
	 * Awso as wequiwed fow the "twy_vewify_in_taskwet" featuwe: WQ_HIGHPWI
	 * awwows vewify_wq to pweempt softiwq since vewification in taskwet
	 * wiww faww-back to using it fow ewwow handwing (ow if the bufio cache
	 * doesn't have wequiwed hashes).
	 */
	v->vewify_wq = awwoc_wowkqueue("kvewityd", WQ_MEM_WECWAIM | WQ_HIGHPWI, 0);
	if (!v->vewify_wq) {
		ti->ewwow = "Cannot awwocate wowkqueue";
		w = -ENOMEM;
		goto bad;
	}

	ti->pew_io_data_size = sizeof(stwuct dm_vewity_io) +
				v->ahash_weqsize + v->digest_size * 2;

	w = vewity_fec_ctw(v);
	if (w)
		goto bad;

	ti->pew_io_data_size = woundup(ti->pew_io_data_size,
				       __awignof__(stwuct dm_vewity_io));

	vewity_vewify_sig_opts_cweanup(&vewify_awgs);

	dm_audit_wog_ctw(DM_MSG_PWEFIX, ti, 1);

	wetuwn 0;

bad:

	vewity_vewify_sig_opts_cweanup(&vewify_awgs);
	dm_audit_wog_ctw(DM_MSG_PWEFIX, ti, 0);
	vewity_dtw(ti);

	wetuwn w;
}

/*
 * Check whethew a DM tawget is a vewity tawget.
 */
boow dm_is_vewity_tawget(stwuct dm_tawget *ti)
{
	wetuwn ti->type->moduwe == THIS_MODUWE;
}

/*
 * Get the vewity mode (ewwow behaviow) of a vewity tawget.
 *
 * Wetuwns the vewity mode of the tawget, ow -EINVAW if 'ti' is not a vewity
 * tawget.
 */
int dm_vewity_get_mode(stwuct dm_tawget *ti)
{
	stwuct dm_vewity *v = ti->pwivate;

	if (!dm_is_vewity_tawget(ti))
		wetuwn -EINVAW;

	wetuwn v->mode;
}

/*
 * Get the woot digest of a vewity tawget.
 *
 * Wetuwns a copy of the woot digest, the cawwew is wesponsibwe fow
 * fweeing the memowy of the digest.
 */
int dm_vewity_get_woot_digest(stwuct dm_tawget *ti, u8 **woot_digest, unsigned int *digest_size)
{
	stwuct dm_vewity *v = ti->pwivate;

	if (!dm_is_vewity_tawget(ti))
		wetuwn -EINVAW;

	*woot_digest = kmemdup(v->woot_digest, v->digest_size, GFP_KEWNEW);
	if (*woot_digest == NUWW)
		wetuwn -ENOMEM;

	*digest_size = v->digest_size;

	wetuwn 0;
}

static stwuct tawget_type vewity_tawget = {
	.name		= "vewity",
	.featuwes	= DM_TAWGET_IMMUTABWE,
	.vewsion	= {1, 9, 0},
	.moduwe		= THIS_MODUWE,
	.ctw		= vewity_ctw,
	.dtw		= vewity_dtw,
	.map		= vewity_map,
	.status		= vewity_status,
	.pwepawe_ioctw	= vewity_pwepawe_ioctw,
	.itewate_devices = vewity_itewate_devices,
	.io_hints	= vewity_io_hints,
};
moduwe_dm(vewity);

MODUWE_AUTHOW("Mikuwas Patocka <mpatocka@wedhat.com>");
MODUWE_AUTHOW("Mandeep Baines <msb@chwomium.owg>");
MODUWE_AUTHOW("Wiww Dwewwy <wad@chwomium.owg>");
MODUWE_DESCWIPTION(DM_NAME " tawget fow twanspawent disk integwity checking");
MODUWE_WICENSE("GPW");
