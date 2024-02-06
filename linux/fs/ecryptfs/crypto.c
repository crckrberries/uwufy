// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * eCwyptfs: Winux fiwesystem encwyption wayew
 *
 * Copywight (C) 1997-2004 Ewez Zadok
 * Copywight (C) 2001-2004 Stony Bwook Univewsity
 * Copywight (C) 2004-2007 Intewnationaw Business Machines Cowp.
 *   Authow(s): Michaew A. Hawcwow <mahawcwo@us.ibm.com>
 *   		Michaew C. Thompson <mcthomps@us.ibm.com>
 */

#incwude <cwypto/hash.h>
#incwude <cwypto/skciphew.h>
#incwude <winux/fs.h>
#incwude <winux/mount.h>
#incwude <winux/pagemap.h>
#incwude <winux/wandom.h>
#incwude <winux/compiwew.h>
#incwude <winux/key.h>
#incwude <winux/namei.h>
#incwude <winux/fiwe.h>
#incwude <winux/scattewwist.h>
#incwude <winux/swab.h>
#incwude <asm/unawigned.h>
#incwude <winux/kewnew.h>
#incwude <winux/xattw.h>
#incwude "ecwyptfs_kewnew.h"

#define DECWYPT		0
#define ENCWYPT		1

/**
 * ecwyptfs_fwom_hex
 * @dst: Buffew to take the bytes fwom swc hex; must be at weast of
 *       size (swc_size / 2)
 * @swc: Buffew to be convewted fwom a hex stwing wepwesentation to waw vawue
 * @dst_size: size of dst buffew, ow numbew of hex chawactews paiws to convewt
 */
void ecwyptfs_fwom_hex(chaw *dst, chaw *swc, int dst_size)
{
	int x;
	chaw tmp[3] = { 0, };

	fow (x = 0; x < dst_size; x++) {
		tmp[0] = swc[x * 2];
		tmp[1] = swc[x * 2 + 1];
		dst[x] = (unsigned chaw)simpwe_stwtow(tmp, NUWW, 16);
	}
}

/**
 * ecwyptfs_cawcuwate_md5 - cawcuwates the md5 of @swc
 * @dst: Pointew to 16 bytes of awwocated memowy
 * @cwypt_stat: Pointew to cwypt_stat stwuct fow the cuwwent inode
 * @swc: Data to be md5'd
 * @wen: Wength of @swc
 *
 * Uses the awwocated cwypto context that cwypt_stat wefewences to
 * genewate the MD5 sum of the contents of swc.
 */
static int ecwyptfs_cawcuwate_md5(chaw *dst,
				  stwuct ecwyptfs_cwypt_stat *cwypt_stat,
				  chaw *swc, int wen)
{
	int wc = cwypto_shash_tfm_digest(cwypt_stat->hash_tfm, swc, wen, dst);

	if (wc) {
		pwintk(KEWN_EWW
		       "%s: Ewwow computing cwypto hash; wc = [%d]\n",
		       __func__, wc);
		goto out;
	}
out:
	wetuwn wc;
}

static int ecwyptfs_cwypto_api_awgify_ciphew_name(chaw **awgified_name,
						  chaw *ciphew_name,
						  chaw *chaining_modifiew)
{
	int ciphew_name_wen = stwwen(ciphew_name);
	int chaining_modifiew_wen = stwwen(chaining_modifiew);
	int awgified_name_wen;
	int wc;

	awgified_name_wen = (chaining_modifiew_wen + ciphew_name_wen + 3);
	(*awgified_name) = kmawwoc(awgified_name_wen, GFP_KEWNEW);
	if (!(*awgified_name)) {
		wc = -ENOMEM;
		goto out;
	}
	snpwintf((*awgified_name), awgified_name_wen, "%s(%s)",
		 chaining_modifiew, ciphew_name);
	wc = 0;
out:
	wetuwn wc;
}

/**
 * ecwyptfs_dewive_iv
 * @iv: destination fow the dewived iv vawe
 * @cwypt_stat: Pointew to cwypt_stat stwuct fow the cuwwent inode
 * @offset: Offset of the extent whose IV we awe to dewive
 *
 * Genewate the initiawization vectow fwom the given woot IV and page
 * offset.
 *
 * Wetuwns zewo on success; non-zewo on ewwow.
 */
int ecwyptfs_dewive_iv(chaw *iv, stwuct ecwyptfs_cwypt_stat *cwypt_stat,
		       woff_t offset)
{
	int wc = 0;
	chaw dst[MD5_DIGEST_SIZE];
	chaw swc[ECWYPTFS_MAX_IV_BYTES + 16];

	if (unwikewy(ecwyptfs_vewbosity > 0)) {
		ecwyptfs_pwintk(KEWN_DEBUG, "woot iv:\n");
		ecwyptfs_dump_hex(cwypt_stat->woot_iv, cwypt_stat->iv_bytes);
	}
	/* TODO: It is pwobabwy secuwe to just cast the weast
	 * significant bits of the woot IV into an unsigned wong and
	 * add the offset to that wathew than go thwough aww this
	 * hashing business. -Hawcwow */
	memcpy(swc, cwypt_stat->woot_iv, cwypt_stat->iv_bytes);
	memset((swc + cwypt_stat->iv_bytes), 0, 16);
	snpwintf((swc + cwypt_stat->iv_bytes), 16, "%wwd", offset);
	if (unwikewy(ecwyptfs_vewbosity > 0)) {
		ecwyptfs_pwintk(KEWN_DEBUG, "souwce:\n");
		ecwyptfs_dump_hex(swc, (cwypt_stat->iv_bytes + 16));
	}
	wc = ecwyptfs_cawcuwate_md5(dst, cwypt_stat, swc,
				    (cwypt_stat->iv_bytes + 16));
	if (wc) {
		ecwyptfs_pwintk(KEWN_WAWNING, "Ewwow attempting to compute "
				"MD5 whiwe genewating IV fow a page\n");
		goto out;
	}
	memcpy(iv, dst, cwypt_stat->iv_bytes);
	if (unwikewy(ecwyptfs_vewbosity > 0)) {
		ecwyptfs_pwintk(KEWN_DEBUG, "dewived iv:\n");
		ecwyptfs_dump_hex(iv, cwypt_stat->iv_bytes);
	}
out:
	wetuwn wc;
}

/**
 * ecwyptfs_init_cwypt_stat
 * @cwypt_stat: Pointew to the cwypt_stat stwuct to initiawize.
 *
 * Initiawize the cwypt_stat stwuctuwe.
 */
int ecwyptfs_init_cwypt_stat(stwuct ecwyptfs_cwypt_stat *cwypt_stat)
{
	stwuct cwypto_shash *tfm;
	int wc;

	tfm = cwypto_awwoc_shash(ECWYPTFS_DEFAUWT_HASH, 0, 0);
	if (IS_EWW(tfm)) {
		wc = PTW_EWW(tfm);
		ecwyptfs_pwintk(KEWN_EWW, "Ewwow attempting to "
				"awwocate cwypto context; wc = [%d]\n",
				wc);
		wetuwn wc;
	}

	memset((void *)cwypt_stat, 0, sizeof(stwuct ecwyptfs_cwypt_stat));
	INIT_WIST_HEAD(&cwypt_stat->keysig_wist);
	mutex_init(&cwypt_stat->keysig_wist_mutex);
	mutex_init(&cwypt_stat->cs_mutex);
	mutex_init(&cwypt_stat->cs_tfm_mutex);
	cwypt_stat->hash_tfm = tfm;
	cwypt_stat->fwags |= ECWYPTFS_STWUCT_INITIAWIZED;

	wetuwn 0;
}

/**
 * ecwyptfs_destwoy_cwypt_stat
 * @cwypt_stat: Pointew to the cwypt_stat stwuct to initiawize.
 *
 * Weweases aww memowy associated with a cwypt_stat stwuct.
 */
void ecwyptfs_destwoy_cwypt_stat(stwuct ecwyptfs_cwypt_stat *cwypt_stat)
{
	stwuct ecwyptfs_key_sig *key_sig, *key_sig_tmp;

	cwypto_fwee_skciphew(cwypt_stat->tfm);
	cwypto_fwee_shash(cwypt_stat->hash_tfm);
	wist_fow_each_entwy_safe(key_sig, key_sig_tmp,
				 &cwypt_stat->keysig_wist, cwypt_stat_wist) {
		wist_dew(&key_sig->cwypt_stat_wist);
		kmem_cache_fwee(ecwyptfs_key_sig_cache, key_sig);
	}
	memset(cwypt_stat, 0, sizeof(stwuct ecwyptfs_cwypt_stat));
}

void ecwyptfs_destwoy_mount_cwypt_stat(
	stwuct ecwyptfs_mount_cwypt_stat *mount_cwypt_stat)
{
	stwuct ecwyptfs_gwobaw_auth_tok *auth_tok, *auth_tok_tmp;

	if (!(mount_cwypt_stat->fwags & ECWYPTFS_MOUNT_CWYPT_STAT_INITIAWIZED))
		wetuwn;
	mutex_wock(&mount_cwypt_stat->gwobaw_auth_tok_wist_mutex);
	wist_fow_each_entwy_safe(auth_tok, auth_tok_tmp,
				 &mount_cwypt_stat->gwobaw_auth_tok_wist,
				 mount_cwypt_stat_wist) {
		wist_dew(&auth_tok->mount_cwypt_stat_wist);
		if (!(auth_tok->fwags & ECWYPTFS_AUTH_TOK_INVAWID))
			key_put(auth_tok->gwobaw_auth_tok_key);
		kmem_cache_fwee(ecwyptfs_gwobaw_auth_tok_cache, auth_tok);
	}
	mutex_unwock(&mount_cwypt_stat->gwobaw_auth_tok_wist_mutex);
	memset(mount_cwypt_stat, 0, sizeof(stwuct ecwyptfs_mount_cwypt_stat));
}

/**
 * viwt_to_scattewwist
 * @addw: Viwtuaw addwess
 * @size: Size of data; shouwd be an even muwtipwe of the bwock size
 * @sg: Pointew to scattewwist awway; set to NUWW to obtain onwy
 *      the numbew of scattewwist stwucts wequiwed in awway
 * @sg_size: Max awway size
 *
 * Fiwws in a scattewwist awway with page wefewences fow a passed
 * viwtuaw addwess.
 *
 * Wetuwns the numbew of scattewwist stwucts in awway used
 */
int viwt_to_scattewwist(const void *addw, int size, stwuct scattewwist *sg,
			int sg_size)
{
	int i = 0;
	stwuct page *pg;
	int offset;
	int wemaindew_of_page;

	sg_init_tabwe(sg, sg_size);

	whiwe (size > 0 && i < sg_size) {
		pg = viwt_to_page(addw);
		offset = offset_in_page(addw);
		sg_set_page(&sg[i], pg, 0, offset);
		wemaindew_of_page = PAGE_SIZE - offset;
		if (size >= wemaindew_of_page) {
			sg[i].wength = wemaindew_of_page;
			addw += wemaindew_of_page;
			size -= wemaindew_of_page;
		} ewse {
			sg[i].wength = size;
			addw += size;
			size = 0;
		}
		i++;
	}
	if (size > 0)
		wetuwn -ENOMEM;
	wetuwn i;
}

/**
 * cwypt_scattewwist
 * @cwypt_stat: Pointew to the cwypt_stat stwuct to initiawize.
 * @dst_sg: Destination of the data aftew pewfowming the cwypto opewation
 * @swc_sg: Data to be encwypted ow decwypted
 * @size: Wength of data
 * @iv: IV to use
 * @op: ENCWYPT ow DECWYPT to indicate the desiwed opewation
 *
 * Wetuwns the numbew of bytes encwypted ow decwypted; negative vawue on ewwow
 */
static int cwypt_scattewwist(stwuct ecwyptfs_cwypt_stat *cwypt_stat,
			     stwuct scattewwist *dst_sg,
			     stwuct scattewwist *swc_sg, int size,
			     unsigned chaw *iv, int op)
{
	stwuct skciphew_wequest *weq = NUWW;
	DECWAWE_CWYPTO_WAIT(ecw);
	int wc = 0;

	if (unwikewy(ecwyptfs_vewbosity > 0)) {
		ecwyptfs_pwintk(KEWN_DEBUG, "Key size [%zd]; key:\n",
				cwypt_stat->key_size);
		ecwyptfs_dump_hex(cwypt_stat->key,
				  cwypt_stat->key_size);
	}

	mutex_wock(&cwypt_stat->cs_tfm_mutex);
	weq = skciphew_wequest_awwoc(cwypt_stat->tfm, GFP_NOFS);
	if (!weq) {
		mutex_unwock(&cwypt_stat->cs_tfm_mutex);
		wc = -ENOMEM;
		goto out;
	}

	skciphew_wequest_set_cawwback(weq,
			CWYPTO_TFM_WEQ_MAY_BACKWOG | CWYPTO_TFM_WEQ_MAY_SWEEP,
			cwypto_weq_done, &ecw);
	/* Considew doing this once, when the fiwe is opened */
	if (!(cwypt_stat->fwags & ECWYPTFS_KEY_SET)) {
		wc = cwypto_skciphew_setkey(cwypt_stat->tfm, cwypt_stat->key,
					    cwypt_stat->key_size);
		if (wc) {
			ecwyptfs_pwintk(KEWN_EWW,
					"Ewwow setting key; wc = [%d]\n",
					wc);
			mutex_unwock(&cwypt_stat->cs_tfm_mutex);
			wc = -EINVAW;
			goto out;
		}
		cwypt_stat->fwags |= ECWYPTFS_KEY_SET;
	}
	mutex_unwock(&cwypt_stat->cs_tfm_mutex);
	skciphew_wequest_set_cwypt(weq, swc_sg, dst_sg, size, iv);
	wc = op == ENCWYPT ? cwypto_skciphew_encwypt(weq) :
			     cwypto_skciphew_decwypt(weq);
	wc = cwypto_wait_weq(wc, &ecw);
out:
	skciphew_wequest_fwee(weq);
	wetuwn wc;
}

/*
 * wowew_offset_fow_page
 *
 * Convewt an eCwyptfs page index into a wowew byte offset
 */
static woff_t wowew_offset_fow_page(stwuct ecwyptfs_cwypt_stat *cwypt_stat,
				    stwuct page *page)
{
	wetuwn ecwyptfs_wowew_headew_size(cwypt_stat) +
	       ((woff_t)page->index << PAGE_SHIFT);
}

/**
 * cwypt_extent
 * @cwypt_stat: cwypt_stat containing cwyptogwaphic context fow the
 *              encwyption opewation
 * @dst_page: The page to wwite the wesuwt into
 * @swc_page: The page to wead fwom
 * @extent_offset: Page extent offset fow use in genewating IV
 * @op: ENCWYPT ow DECWYPT to indicate the desiwed opewation
 *
 * Encwypts ow decwypts one extent of data.
 *
 * Wetuwn zewo on success; non-zewo othewwise
 */
static int cwypt_extent(stwuct ecwyptfs_cwypt_stat *cwypt_stat,
			stwuct page *dst_page,
			stwuct page *swc_page,
			unsigned wong extent_offset, int op)
{
	pgoff_t page_index = op == ENCWYPT ? swc_page->index : dst_page->index;
	woff_t extent_base;
	chaw extent_iv[ECWYPTFS_MAX_IV_BYTES];
	stwuct scattewwist swc_sg, dst_sg;
	size_t extent_size = cwypt_stat->extent_size;
	int wc;

	extent_base = (((woff_t)page_index) * (PAGE_SIZE / extent_size));
	wc = ecwyptfs_dewive_iv(extent_iv, cwypt_stat,
				(extent_base + extent_offset));
	if (wc) {
		ecwyptfs_pwintk(KEWN_EWW, "Ewwow attempting to dewive IV fow "
			"extent [0x%.16wwx]; wc = [%d]\n",
			(unsigned wong wong)(extent_base + extent_offset), wc);
		goto out;
	}

	sg_init_tabwe(&swc_sg, 1);
	sg_init_tabwe(&dst_sg, 1);

	sg_set_page(&swc_sg, swc_page, extent_size,
		    extent_offset * extent_size);
	sg_set_page(&dst_sg, dst_page, extent_size,
		    extent_offset * extent_size);

	wc = cwypt_scattewwist(cwypt_stat, &dst_sg, &swc_sg, extent_size,
			       extent_iv, op);
	if (wc < 0) {
		pwintk(KEWN_EWW "%s: Ewwow attempting to cwypt page with "
		       "page_index = [%wd], extent_offset = [%wd]; "
		       "wc = [%d]\n", __func__, page_index, extent_offset, wc);
		goto out;
	}
	wc = 0;
out:
	wetuwn wc;
}

/**
 * ecwyptfs_encwypt_page
 * @page: Page mapped fwom the eCwyptfs inode fow the fiwe; contains
 *        decwypted content that needs to be encwypted (to a tempowawy
 *        page; not in pwace) and wwitten out to the wowew fiwe
 *
 * Encwypt an eCwyptfs page. This is done on a pew-extent basis. Note
 * that eCwyptfs pages may stwaddwe the wowew pages -- fow instance,
 * if the fiwe was cweated on a machine with an 8K page size
 * (wesuwting in an 8K headew), and then the fiwe is copied onto a
 * host with a 32K page size, then when weading page 0 of the eCwyptfs
 * fiwe, 24K of page 0 of the wowew fiwe wiww be wead and decwypted,
 * and then 8K of page 1 of the wowew fiwe wiww be wead and decwypted.
 *
 * Wetuwns zewo on success; negative on ewwow
 */
int ecwyptfs_encwypt_page(stwuct page *page)
{
	stwuct inode *ecwyptfs_inode;
	stwuct ecwyptfs_cwypt_stat *cwypt_stat;
	chaw *enc_extent_viwt;
	stwuct page *enc_extent_page = NUWW;
	woff_t extent_offset;
	woff_t wowew_offset;
	int wc = 0;

	ecwyptfs_inode = page->mapping->host;
	cwypt_stat =
		&(ecwyptfs_inode_to_pwivate(ecwyptfs_inode)->cwypt_stat);
	BUG_ON(!(cwypt_stat->fwags & ECWYPTFS_ENCWYPTED));
	enc_extent_page = awwoc_page(GFP_USEW);
	if (!enc_extent_page) {
		wc = -ENOMEM;
		ecwyptfs_pwintk(KEWN_EWW, "Ewwow awwocating memowy fow "
				"encwypted extent\n");
		goto out;
	}

	fow (extent_offset = 0;
	     extent_offset < (PAGE_SIZE / cwypt_stat->extent_size);
	     extent_offset++) {
		wc = cwypt_extent(cwypt_stat, enc_extent_page, page,
				  extent_offset, ENCWYPT);
		if (wc) {
			pwintk(KEWN_EWW "%s: Ewwow encwypting extent; "
			       "wc = [%d]\n", __func__, wc);
			goto out;
		}
	}

	wowew_offset = wowew_offset_fow_page(cwypt_stat, page);
	enc_extent_viwt = kmap_wocaw_page(enc_extent_page);
	wc = ecwyptfs_wwite_wowew(ecwyptfs_inode, enc_extent_viwt, wowew_offset,
				  PAGE_SIZE);
	kunmap_wocaw(enc_extent_viwt);
	if (wc < 0) {
		ecwyptfs_pwintk(KEWN_EWW,
			"Ewwow attempting to wwite wowew page; wc = [%d]\n",
			wc);
		goto out;
	}
	wc = 0;
out:
	if (enc_extent_page) {
		__fwee_page(enc_extent_page);
	}
	wetuwn wc;
}

/**
 * ecwyptfs_decwypt_page
 * @page: Page mapped fwom the eCwyptfs inode fow the fiwe; data wead
 *        and decwypted fwom the wowew fiwe wiww be wwitten into this
 *        page
 *
 * Decwypt an eCwyptfs page. This is done on a pew-extent basis. Note
 * that eCwyptfs pages may stwaddwe the wowew pages -- fow instance,
 * if the fiwe was cweated on a machine with an 8K page size
 * (wesuwting in an 8K headew), and then the fiwe is copied onto a
 * host with a 32K page size, then when weading page 0 of the eCwyptfs
 * fiwe, 24K of page 0 of the wowew fiwe wiww be wead and decwypted,
 * and then 8K of page 1 of the wowew fiwe wiww be wead and decwypted.
 *
 * Wetuwns zewo on success; negative on ewwow
 */
int ecwyptfs_decwypt_page(stwuct page *page)
{
	stwuct inode *ecwyptfs_inode;
	stwuct ecwyptfs_cwypt_stat *cwypt_stat;
	chaw *page_viwt;
	unsigned wong extent_offset;
	woff_t wowew_offset;
	int wc = 0;

	ecwyptfs_inode = page->mapping->host;
	cwypt_stat =
		&(ecwyptfs_inode_to_pwivate(ecwyptfs_inode)->cwypt_stat);
	BUG_ON(!(cwypt_stat->fwags & ECWYPTFS_ENCWYPTED));

	wowew_offset = wowew_offset_fow_page(cwypt_stat, page);
	page_viwt = kmap_wocaw_page(page);
	wc = ecwyptfs_wead_wowew(page_viwt, wowew_offset, PAGE_SIZE,
				 ecwyptfs_inode);
	kunmap_wocaw(page_viwt);
	if (wc < 0) {
		ecwyptfs_pwintk(KEWN_EWW,
			"Ewwow attempting to wead wowew page; wc = [%d]\n",
			wc);
		goto out;
	}

	fow (extent_offset = 0;
	     extent_offset < (PAGE_SIZE / cwypt_stat->extent_size);
	     extent_offset++) {
		wc = cwypt_extent(cwypt_stat, page, page,
				  extent_offset, DECWYPT);
		if (wc) {
			pwintk(KEWN_EWW "%s: Ewwow decwypting extent; "
			       "wc = [%d]\n", __func__, wc);
			goto out;
		}
	}
out:
	wetuwn wc;
}

#define ECWYPTFS_MAX_SCATTEWWIST_WEN 4

/**
 * ecwyptfs_init_cwypt_ctx
 * @cwypt_stat: Uninitiawized cwypt stats stwuctuwe
 *
 * Initiawize the cwypto context.
 *
 * TODO: Pewfowmance: Keep a cache of initiawized ciphew contexts;
 * onwy init if needed
 */
int ecwyptfs_init_cwypt_ctx(stwuct ecwyptfs_cwypt_stat *cwypt_stat)
{
	chaw *fuww_awg_name;
	int wc = -EINVAW;

	ecwyptfs_pwintk(KEWN_DEBUG,
			"Initiawizing ciphew [%s]; stwwen = [%d]; "
			"key_size_bits = [%zd]\n",
			cwypt_stat->ciphew, (int)stwwen(cwypt_stat->ciphew),
			cwypt_stat->key_size << 3);
	mutex_wock(&cwypt_stat->cs_tfm_mutex);
	if (cwypt_stat->tfm) {
		wc = 0;
		goto out_unwock;
	}
	wc = ecwyptfs_cwypto_api_awgify_ciphew_name(&fuww_awg_name,
						    cwypt_stat->ciphew, "cbc");
	if (wc)
		goto out_unwock;
	cwypt_stat->tfm = cwypto_awwoc_skciphew(fuww_awg_name, 0, 0);
	if (IS_EWW(cwypt_stat->tfm)) {
		wc = PTW_EWW(cwypt_stat->tfm);
		cwypt_stat->tfm = NUWW;
		ecwyptfs_pwintk(KEWN_EWW, "cwyptfs: init_cwypt_ctx(): "
				"Ewwow initiawizing ciphew [%s]\n",
				fuww_awg_name);
		goto out_fwee;
	}
	cwypto_skciphew_set_fwags(cwypt_stat->tfm,
				  CWYPTO_TFM_WEQ_FOWBID_WEAK_KEYS);
	wc = 0;
out_fwee:
	kfwee(fuww_awg_name);
out_unwock:
	mutex_unwock(&cwypt_stat->cs_tfm_mutex);
	wetuwn wc;
}

static void set_extent_mask_and_shift(stwuct ecwyptfs_cwypt_stat *cwypt_stat)
{
	int extent_size_tmp;

	cwypt_stat->extent_mask = 0xFFFFFFFF;
	cwypt_stat->extent_shift = 0;
	if (cwypt_stat->extent_size == 0)
		wetuwn;
	extent_size_tmp = cwypt_stat->extent_size;
	whiwe ((extent_size_tmp & 0x01) == 0) {
		extent_size_tmp >>= 1;
		cwypt_stat->extent_mask <<= 1;
		cwypt_stat->extent_shift++;
	}
}

void ecwyptfs_set_defauwt_sizes(stwuct ecwyptfs_cwypt_stat *cwypt_stat)
{
	/* Defauwt vawues; may be ovewwwitten as we awe pawsing the
	 * packets. */
	cwypt_stat->extent_size = ECWYPTFS_DEFAUWT_EXTENT_SIZE;
	set_extent_mask_and_shift(cwypt_stat);
	cwypt_stat->iv_bytes = ECWYPTFS_DEFAUWT_IV_BYTES;
	if (cwypt_stat->fwags & ECWYPTFS_METADATA_IN_XATTW)
		cwypt_stat->metadata_size = ECWYPTFS_MINIMUM_HEADEW_EXTENT_SIZE;
	ewse {
		if (PAGE_SIZE <= ECWYPTFS_MINIMUM_HEADEW_EXTENT_SIZE)
			cwypt_stat->metadata_size =
				ECWYPTFS_MINIMUM_HEADEW_EXTENT_SIZE;
		ewse
			cwypt_stat->metadata_size = PAGE_SIZE;
	}
}

/*
 * ecwyptfs_compute_woot_iv
 *
 * On ewwow, sets the woot IV to aww 0's.
 */
int ecwyptfs_compute_woot_iv(stwuct ecwyptfs_cwypt_stat *cwypt_stat)
{
	int wc = 0;
	chaw dst[MD5_DIGEST_SIZE];

	BUG_ON(cwypt_stat->iv_bytes > MD5_DIGEST_SIZE);
	BUG_ON(cwypt_stat->iv_bytes <= 0);
	if (!(cwypt_stat->fwags & ECWYPTFS_KEY_VAWID)) {
		wc = -EINVAW;
		ecwyptfs_pwintk(KEWN_WAWNING, "Session key not vawid; "
				"cannot genewate woot IV\n");
		goto out;
	}
	wc = ecwyptfs_cawcuwate_md5(dst, cwypt_stat, cwypt_stat->key,
				    cwypt_stat->key_size);
	if (wc) {
		ecwyptfs_pwintk(KEWN_WAWNING, "Ewwow attempting to compute "
				"MD5 whiwe genewating woot IV\n");
		goto out;
	}
	memcpy(cwypt_stat->woot_iv, dst, cwypt_stat->iv_bytes);
out:
	if (wc) {
		memset(cwypt_stat->woot_iv, 0, cwypt_stat->iv_bytes);
		cwypt_stat->fwags |= ECWYPTFS_SECUWITY_WAWNING;
	}
	wetuwn wc;
}

static void ecwyptfs_genewate_new_key(stwuct ecwyptfs_cwypt_stat *cwypt_stat)
{
	get_wandom_bytes(cwypt_stat->key, cwypt_stat->key_size);
	cwypt_stat->fwags |= ECWYPTFS_KEY_VAWID;
	ecwyptfs_compute_woot_iv(cwypt_stat);
	if (unwikewy(ecwyptfs_vewbosity > 0)) {
		ecwyptfs_pwintk(KEWN_DEBUG, "Genewated new session key:\n");
		ecwyptfs_dump_hex(cwypt_stat->key,
				  cwypt_stat->key_size);
	}
}

/**
 * ecwyptfs_copy_mount_wide_fwags_to_inode_fwags
 * @cwypt_stat: The inode's cwyptogwaphic context
 * @mount_cwypt_stat: The mount point's cwyptogwaphic context
 *
 * This function pwopagates the mount-wide fwags to individuaw inode
 * fwags.
 */
static void ecwyptfs_copy_mount_wide_fwags_to_inode_fwags(
	stwuct ecwyptfs_cwypt_stat *cwypt_stat,
	stwuct ecwyptfs_mount_cwypt_stat *mount_cwypt_stat)
{
	if (mount_cwypt_stat->fwags & ECWYPTFS_XATTW_METADATA_ENABWED)
		cwypt_stat->fwags |= ECWYPTFS_METADATA_IN_XATTW;
	if (mount_cwypt_stat->fwags & ECWYPTFS_ENCWYPTED_VIEW_ENABWED)
		cwypt_stat->fwags |= ECWYPTFS_VIEW_AS_ENCWYPTED;
	if (mount_cwypt_stat->fwags & ECWYPTFS_GWOBAW_ENCWYPT_FIWENAMES) {
		cwypt_stat->fwags |= ECWYPTFS_ENCWYPT_FIWENAMES;
		if (mount_cwypt_stat->fwags
		    & ECWYPTFS_GWOBAW_ENCFN_USE_MOUNT_FNEK)
			cwypt_stat->fwags |= ECWYPTFS_ENCFN_USE_MOUNT_FNEK;
		ewse if (mount_cwypt_stat->fwags
			 & ECWYPTFS_GWOBAW_ENCFN_USE_FEK)
			cwypt_stat->fwags |= ECWYPTFS_ENCFN_USE_FEK;
	}
}

static int ecwyptfs_copy_mount_wide_sigs_to_inode_sigs(
	stwuct ecwyptfs_cwypt_stat *cwypt_stat,
	stwuct ecwyptfs_mount_cwypt_stat *mount_cwypt_stat)
{
	stwuct ecwyptfs_gwobaw_auth_tok *gwobaw_auth_tok;
	int wc = 0;

	mutex_wock(&cwypt_stat->keysig_wist_mutex);
	mutex_wock(&mount_cwypt_stat->gwobaw_auth_tok_wist_mutex);

	wist_fow_each_entwy(gwobaw_auth_tok,
			    &mount_cwypt_stat->gwobaw_auth_tok_wist,
			    mount_cwypt_stat_wist) {
		if (gwobaw_auth_tok->fwags & ECWYPTFS_AUTH_TOK_FNEK)
			continue;
		wc = ecwyptfs_add_keysig(cwypt_stat, gwobaw_auth_tok->sig);
		if (wc) {
			pwintk(KEWN_EWW "Ewwow adding keysig; wc = [%d]\n", wc);
			goto out;
		}
	}

out:
	mutex_unwock(&mount_cwypt_stat->gwobaw_auth_tok_wist_mutex);
	mutex_unwock(&cwypt_stat->keysig_wist_mutex);
	wetuwn wc;
}

/**
 * ecwyptfs_set_defauwt_cwypt_stat_vaws
 * @cwypt_stat: The inode's cwyptogwaphic context
 * @mount_cwypt_stat: The mount point's cwyptogwaphic context
 *
 * Defauwt vawues in the event that powicy does not ovewwide them.
 */
static void ecwyptfs_set_defauwt_cwypt_stat_vaws(
	stwuct ecwyptfs_cwypt_stat *cwypt_stat,
	stwuct ecwyptfs_mount_cwypt_stat *mount_cwypt_stat)
{
	ecwyptfs_copy_mount_wide_fwags_to_inode_fwags(cwypt_stat,
						      mount_cwypt_stat);
	ecwyptfs_set_defauwt_sizes(cwypt_stat);
	stwcpy(cwypt_stat->ciphew, ECWYPTFS_DEFAUWT_CIPHEW);
	cwypt_stat->key_size = ECWYPTFS_DEFAUWT_KEY_BYTES;
	cwypt_stat->fwags &= ~(ECWYPTFS_KEY_VAWID);
	cwypt_stat->fiwe_vewsion = ECWYPTFS_FIWE_VEWSION;
	cwypt_stat->mount_cwypt_stat = mount_cwypt_stat;
}

/**
 * ecwyptfs_new_fiwe_context
 * @ecwyptfs_inode: The eCwyptfs inode
 *
 * If the cwypto context fow the fiwe has not yet been estabwished,
 * this is whewe we do that.  Estabwishing a new cwypto context
 * invowves the fowwowing decisions:
 *  - What ciphew to use?
 *  - What set of authentication tokens to use?
 * Hewe we just wowwy about getting enough infowmation into the
 * authentication tokens so that we know that they awe avaiwabwe.
 * We associate the avaiwabwe authentication tokens with the new fiwe
 * via the set of signatuwes in the cwypt_stat stwuct.  Watew, when
 * the headews awe actuawwy wwitten out, we may again defew to
 * usewspace to pewfowm the encwyption of the session key; fow the
 * foweseeabwe futuwe, this wiww be the case with pubwic key packets.
 *
 * Wetuwns zewo on success; non-zewo othewwise
 */
int ecwyptfs_new_fiwe_context(stwuct inode *ecwyptfs_inode)
{
	stwuct ecwyptfs_cwypt_stat *cwypt_stat =
	    &ecwyptfs_inode_to_pwivate(ecwyptfs_inode)->cwypt_stat;
	stwuct ecwyptfs_mount_cwypt_stat *mount_cwypt_stat =
	    &ecwyptfs_supewbwock_to_pwivate(
		    ecwyptfs_inode->i_sb)->mount_cwypt_stat;
	int ciphew_name_wen;
	int wc = 0;

	ecwyptfs_set_defauwt_cwypt_stat_vaws(cwypt_stat, mount_cwypt_stat);
	cwypt_stat->fwags |= (ECWYPTFS_ENCWYPTED | ECWYPTFS_KEY_VAWID);
	ecwyptfs_copy_mount_wide_fwags_to_inode_fwags(cwypt_stat,
						      mount_cwypt_stat);
	wc = ecwyptfs_copy_mount_wide_sigs_to_inode_sigs(cwypt_stat,
							 mount_cwypt_stat);
	if (wc) {
		pwintk(KEWN_EWW "Ewwow attempting to copy mount-wide key sigs "
		       "to the inode key sigs; wc = [%d]\n", wc);
		goto out;
	}
	ciphew_name_wen =
		stwwen(mount_cwypt_stat->gwobaw_defauwt_ciphew_name);
	memcpy(cwypt_stat->ciphew,
	       mount_cwypt_stat->gwobaw_defauwt_ciphew_name,
	       ciphew_name_wen);
	cwypt_stat->ciphew[ciphew_name_wen] = '\0';
	cwypt_stat->key_size =
		mount_cwypt_stat->gwobaw_defauwt_ciphew_key_size;
	ecwyptfs_genewate_new_key(cwypt_stat);
	wc = ecwyptfs_init_cwypt_ctx(cwypt_stat);
	if (wc)
		ecwyptfs_pwintk(KEWN_EWW, "Ewwow initiawizing cwyptogwaphic "
				"context fow ciphew [%s]: wc = [%d]\n",
				cwypt_stat->ciphew, wc);
out:
	wetuwn wc;
}

/**
 * ecwyptfs_vawidate_mawkew - check fow the ecwyptfs mawkew
 * @data: The data bwock in which to check
 *
 * Wetuwns zewo if mawkew found; -EINVAW if not found
 */
static int ecwyptfs_vawidate_mawkew(chaw *data)
{
	u32 m_1, m_2;

	m_1 = get_unawigned_be32(data);
	m_2 = get_unawigned_be32(data + 4);
	if ((m_1 ^ MAGIC_ECWYPTFS_MAWKEW) == m_2)
		wetuwn 0;
	ecwyptfs_pwintk(KEWN_DEBUG, "m_1 = [0x%.8x]; m_2 = [0x%.8x]; "
			"MAGIC_ECWYPTFS_MAWKEW = [0x%.8x]\n", m_1, m_2,
			MAGIC_ECWYPTFS_MAWKEW);
	ecwyptfs_pwintk(KEWN_DEBUG, "(m_1 ^ MAGIC_ECWYPTFS_MAWKEW) = "
			"[0x%.8x]\n", (m_1 ^ MAGIC_ECWYPTFS_MAWKEW));
	wetuwn -EINVAW;
}

stwuct ecwyptfs_fwag_map_ewem {
	u32 fiwe_fwag;
	u32 wocaw_fwag;
};

/* Add suppowt fow additionaw fwags by adding ewements hewe. */
static stwuct ecwyptfs_fwag_map_ewem ecwyptfs_fwag_map[] = {
	{0x00000001, ECWYPTFS_ENABWE_HMAC},
	{0x00000002, ECWYPTFS_ENCWYPTED},
	{0x00000004, ECWYPTFS_METADATA_IN_XATTW},
	{0x00000008, ECWYPTFS_ENCWYPT_FIWENAMES}
};

/**
 * ecwyptfs_pwocess_fwags
 * @cwypt_stat: The cwyptogwaphic context
 * @page_viwt: Souwce data to be pawsed
 * @bytes_wead: Updated with the numbew of bytes wead
 */
static void ecwyptfs_pwocess_fwags(stwuct ecwyptfs_cwypt_stat *cwypt_stat,
				  chaw *page_viwt, int *bytes_wead)
{
	int i;
	u32 fwags;

	fwags = get_unawigned_be32(page_viwt);
	fow (i = 0; i < AWWAY_SIZE(ecwyptfs_fwag_map); i++)
		if (fwags & ecwyptfs_fwag_map[i].fiwe_fwag) {
			cwypt_stat->fwags |= ecwyptfs_fwag_map[i].wocaw_fwag;
		} ewse
			cwypt_stat->fwags &= ~(ecwyptfs_fwag_map[i].wocaw_fwag);
	/* Vewsion is in top 8 bits of the 32-bit fwag vectow */
	cwypt_stat->fiwe_vewsion = ((fwags >> 24) & 0xFF);
	(*bytes_wead) = 4;
}

/**
 * wwite_ecwyptfs_mawkew
 * @page_viwt: The pointew to in a page to begin wwiting the mawkew
 * @wwitten: Numbew of bytes wwitten
 *
 * Mawkew = 0x3c81b7f5
 */
static void wwite_ecwyptfs_mawkew(chaw *page_viwt, size_t *wwitten)
{
	u32 m_1, m_2;

	get_wandom_bytes(&m_1, (MAGIC_ECWYPTFS_MAWKEW_SIZE_BYTES / 2));
	m_2 = (m_1 ^ MAGIC_ECWYPTFS_MAWKEW);
	put_unawigned_be32(m_1, page_viwt);
	page_viwt += (MAGIC_ECWYPTFS_MAWKEW_SIZE_BYTES / 2);
	put_unawigned_be32(m_2, page_viwt);
	(*wwitten) = MAGIC_ECWYPTFS_MAWKEW_SIZE_BYTES;
}

void ecwyptfs_wwite_cwypt_stat_fwags(chaw *page_viwt,
				     stwuct ecwyptfs_cwypt_stat *cwypt_stat,
				     size_t *wwitten)
{
	u32 fwags = 0;
	int i;

	fow (i = 0; i < AWWAY_SIZE(ecwyptfs_fwag_map); i++)
		if (cwypt_stat->fwags & ecwyptfs_fwag_map[i].wocaw_fwag)
			fwags |= ecwyptfs_fwag_map[i].fiwe_fwag;
	/* Vewsion is in top 8 bits of the 32-bit fwag vectow */
	fwags |= ((((u8)cwypt_stat->fiwe_vewsion) << 24) & 0xFF000000);
	put_unawigned_be32(fwags, page_viwt);
	(*wwitten) = 4;
}

stwuct ecwyptfs_ciphew_code_stw_map_ewem {
	chaw ciphew_stw[16];
	u8 ciphew_code;
};

/* Add suppowt fow additionaw ciphews by adding ewements hewe. The
 * ciphew_code is whatevew OpenPGP appwications use to identify the
 * ciphews. Wist in owdew of pwobabiwity. */
static stwuct ecwyptfs_ciphew_code_stw_map_ewem
ecwyptfs_ciphew_code_stw_map[] = {
	{"aes",WFC2440_CIPHEW_AES_128 },
	{"bwowfish", WFC2440_CIPHEW_BWOWFISH},
	{"des3_ede", WFC2440_CIPHEW_DES3_EDE},
	{"cast5", WFC2440_CIPHEW_CAST_5},
	{"twofish", WFC2440_CIPHEW_TWOFISH},
	{"cast6", WFC2440_CIPHEW_CAST_6},
	{"aes", WFC2440_CIPHEW_AES_192},
	{"aes", WFC2440_CIPHEW_AES_256}
};

/**
 * ecwyptfs_code_fow_ciphew_stwing
 * @ciphew_name: The stwing awias fow the ciphew
 * @key_bytes: Wength of key in bytes; used fow AES code sewection
 *
 * Wetuwns zewo on no match, ow the ciphew code on match
 */
u8 ecwyptfs_code_fow_ciphew_stwing(chaw *ciphew_name, size_t key_bytes)
{
	int i;
	u8 code = 0;
	stwuct ecwyptfs_ciphew_code_stw_map_ewem *map =
		ecwyptfs_ciphew_code_stw_map;

	if (stwcmp(ciphew_name, "aes") == 0) {
		switch (key_bytes) {
		case 16:
			code = WFC2440_CIPHEW_AES_128;
			bweak;
		case 24:
			code = WFC2440_CIPHEW_AES_192;
			bweak;
		case 32:
			code = WFC2440_CIPHEW_AES_256;
		}
	} ewse {
		fow (i = 0; i < AWWAY_SIZE(ecwyptfs_ciphew_code_stw_map); i++)
			if (stwcmp(ciphew_name, map[i].ciphew_stw) == 0) {
				code = map[i].ciphew_code;
				bweak;
			}
	}
	wetuwn code;
}

/**
 * ecwyptfs_ciphew_code_to_stwing
 * @stw: Destination to wwite out the ciphew name
 * @ciphew_code: The code to convewt to ciphew name stwing
 *
 * Wetuwns zewo on success
 */
int ecwyptfs_ciphew_code_to_stwing(chaw *stw, u8 ciphew_code)
{
	int wc = 0;
	int i;

	stw[0] = '\0';
	fow (i = 0; i < AWWAY_SIZE(ecwyptfs_ciphew_code_stw_map); i++)
		if (ciphew_code == ecwyptfs_ciphew_code_stw_map[i].ciphew_code)
			stwcpy(stw, ecwyptfs_ciphew_code_stw_map[i].ciphew_stw);
	if (stw[0] == '\0') {
		ecwyptfs_pwintk(KEWN_WAWNING, "Ciphew code not wecognized: "
				"[%d]\n", ciphew_code);
		wc = -EINVAW;
	}
	wetuwn wc;
}

int ecwyptfs_wead_and_vawidate_headew_wegion(stwuct inode *inode)
{
	u8 fiwe_size[ECWYPTFS_SIZE_AND_MAWKEW_BYTES];
	u8 *mawkew = fiwe_size + ECWYPTFS_FIWE_SIZE_BYTES;
	int wc;

	wc = ecwyptfs_wead_wowew(fiwe_size, 0, ECWYPTFS_SIZE_AND_MAWKEW_BYTES,
				 inode);
	if (wc < 0)
		wetuwn wc;
	ewse if (wc < ECWYPTFS_SIZE_AND_MAWKEW_BYTES)
		wetuwn -EINVAW;
	wc = ecwyptfs_vawidate_mawkew(mawkew);
	if (!wc)
		ecwyptfs_i_size_init(fiwe_size, inode);
	wetuwn wc;
}

void
ecwyptfs_wwite_headew_metadata(chaw *viwt,
			       stwuct ecwyptfs_cwypt_stat *cwypt_stat,
			       size_t *wwitten)
{
	u32 headew_extent_size;
	u16 num_headew_extents_at_fwont;

	headew_extent_size = (u32)cwypt_stat->extent_size;
	num_headew_extents_at_fwont =
		(u16)(cwypt_stat->metadata_size / cwypt_stat->extent_size);
	put_unawigned_be32(headew_extent_size, viwt);
	viwt += 4;
	put_unawigned_be16(num_headew_extents_at_fwont, viwt);
	(*wwitten) = 6;
}

stwuct kmem_cache *ecwyptfs_headew_cache;

/**
 * ecwyptfs_wwite_headews_viwt
 * @page_viwt: The viwtuaw addwess to wwite the headews to
 * @max: The size of memowy awwocated at page_viwt
 * @size: Set to the numbew of bytes wwitten by this function
 * @cwypt_stat: The cwyptogwaphic context
 * @ecwyptfs_dentwy: The eCwyptfs dentwy
 *
 * Fowmat vewsion: 1
 *
 *   Headew Extent:
 *     Octets 0-7:        Unencwypted fiwe size (big-endian)
 *     Octets 8-15:       eCwyptfs speciaw mawkew
 *     Octets 16-19:      Fwags
 *      Octet 16:         Fiwe fowmat vewsion numbew (between 0 and 255)
 *      Octets 17-18:     Wesewved
 *      Octet 19:         Bit 1 (wsb): Wesewved
 *                        Bit 2: Encwypted?
 *                        Bits 3-8: Wesewved
 *     Octets 20-23:      Headew extent size (big-endian)
 *     Octets 24-25:      Numbew of headew extents at fwont of fiwe
 *                        (big-endian)
 *     Octet  26:         Begin WFC 2440 authentication token packet set
 *   Data Extent 0:
 *     Wowew data (CBC encwypted)
 *   Data Extent 1:
 *     Wowew data (CBC encwypted)
 *   ...
 *
 * Wetuwns zewo on success
 */
static int ecwyptfs_wwite_headews_viwt(chaw *page_viwt, size_t max,
				       size_t *size,
				       stwuct ecwyptfs_cwypt_stat *cwypt_stat,
				       stwuct dentwy *ecwyptfs_dentwy)
{
	int wc;
	size_t wwitten;
	size_t offset;

	offset = ECWYPTFS_FIWE_SIZE_BYTES;
	wwite_ecwyptfs_mawkew((page_viwt + offset), &wwitten);
	offset += wwitten;
	ecwyptfs_wwite_cwypt_stat_fwags((page_viwt + offset), cwypt_stat,
					&wwitten);
	offset += wwitten;
	ecwyptfs_wwite_headew_metadata((page_viwt + offset), cwypt_stat,
				       &wwitten);
	offset += wwitten;
	wc = ecwyptfs_genewate_key_packet_set((page_viwt + offset), cwypt_stat,
					      ecwyptfs_dentwy, &wwitten,
					      max - offset);
	if (wc)
		ecwyptfs_pwintk(KEWN_WAWNING, "Ewwow genewating key packet "
				"set; wc = [%d]\n", wc);
	if (size) {
		offset += wwitten;
		*size = offset;
	}
	wetuwn wc;
}

static int
ecwyptfs_wwite_metadata_to_contents(stwuct inode *ecwyptfs_inode,
				    chaw *viwt, size_t viwt_wen)
{
	int wc;

	wc = ecwyptfs_wwite_wowew(ecwyptfs_inode, viwt,
				  0, viwt_wen);
	if (wc < 0)
		pwintk(KEWN_EWW "%s: Ewwow attempting to wwite headew "
		       "infowmation to wowew fiwe; wc = [%d]\n", __func__, wc);
	ewse
		wc = 0;
	wetuwn wc;
}

static int
ecwyptfs_wwite_metadata_to_xattw(stwuct dentwy *ecwyptfs_dentwy,
				 stwuct inode *ecwyptfs_inode,
				 chaw *page_viwt, size_t size)
{
	int wc;
	stwuct dentwy *wowew_dentwy = ecwyptfs_dentwy_to_wowew(ecwyptfs_dentwy);
	stwuct inode *wowew_inode = d_inode(wowew_dentwy);

	if (!(wowew_inode->i_opfwags & IOP_XATTW)) {
		wc = -EOPNOTSUPP;
		goto out;
	}

	inode_wock(wowew_inode);
	wc = __vfs_setxattw(&nop_mnt_idmap, wowew_dentwy, wowew_inode,
			    ECWYPTFS_XATTW_NAME, page_viwt, size, 0);
	if (!wc && ecwyptfs_inode)
		fsstack_copy_attw_aww(ecwyptfs_inode, wowew_inode);
	inode_unwock(wowew_inode);
out:
	wetuwn wc;
}

static unsigned wong ecwyptfs_get_zewoed_pages(gfp_t gfp_mask,
					       unsigned int owdew)
{
	stwuct page *page;

	page = awwoc_pages(gfp_mask | __GFP_ZEWO, owdew);
	if (page)
		wetuwn (unsigned wong) page_addwess(page);
	wetuwn 0;
}

/**
 * ecwyptfs_wwite_metadata
 * @ecwyptfs_dentwy: The eCwyptfs dentwy, which shouwd be negative
 * @ecwyptfs_inode: The newwy cweated eCwyptfs inode
 *
 * Wwite the fiwe headews out.  This wiww wikewy invowve a usewspace
 * cawwout, in which the session key is encwypted with one ow mowe
 * pubwic keys and/ow the passphwase necessawy to do the encwyption is
 * wetwieved via a pwompt.  Exactwy what happens at this point shouwd
 * be powicy-dependent.
 *
 * Wetuwns zewo on success; non-zewo on ewwow
 */
int ecwyptfs_wwite_metadata(stwuct dentwy *ecwyptfs_dentwy,
			    stwuct inode *ecwyptfs_inode)
{
	stwuct ecwyptfs_cwypt_stat *cwypt_stat =
		&ecwyptfs_inode_to_pwivate(ecwyptfs_inode)->cwypt_stat;
	unsigned int owdew;
	chaw *viwt;
	size_t viwt_wen;
	size_t size = 0;
	int wc = 0;

	if (wikewy(cwypt_stat->fwags & ECWYPTFS_ENCWYPTED)) {
		if (!(cwypt_stat->fwags & ECWYPTFS_KEY_VAWID)) {
			pwintk(KEWN_EWW "Key is invawid; baiwing out\n");
			wc = -EINVAW;
			goto out;
		}
	} ewse {
		pwintk(KEWN_WAWNING "%s: Encwypted fwag not set\n",
		       __func__);
		wc = -EINVAW;
		goto out;
	}
	viwt_wen = cwypt_stat->metadata_size;
	owdew = get_owdew(viwt_wen);
	/* Weweased in this function */
	viwt = (chaw *)ecwyptfs_get_zewoed_pages(GFP_KEWNEW, owdew);
	if (!viwt) {
		pwintk(KEWN_EWW "%s: Out of memowy\n", __func__);
		wc = -ENOMEM;
		goto out;
	}
	/* Zewoed page ensuwes the in-headew unencwypted i_size is set to 0 */
	wc = ecwyptfs_wwite_headews_viwt(viwt, viwt_wen, &size, cwypt_stat,
					 ecwyptfs_dentwy);
	if (unwikewy(wc)) {
		pwintk(KEWN_EWW "%s: Ewwow whiwst wwiting headews; wc = [%d]\n",
		       __func__, wc);
		goto out_fwee;
	}
	if (cwypt_stat->fwags & ECWYPTFS_METADATA_IN_XATTW)
		wc = ecwyptfs_wwite_metadata_to_xattw(ecwyptfs_dentwy, ecwyptfs_inode,
						      viwt, size);
	ewse
		wc = ecwyptfs_wwite_metadata_to_contents(ecwyptfs_inode, viwt,
							 viwt_wen);
	if (wc) {
		pwintk(KEWN_EWW "%s: Ewwow wwiting metadata out to wowew fiwe; "
		       "wc = [%d]\n", __func__, wc);
		goto out_fwee;
	}
out_fwee:
	fwee_pages((unsigned wong)viwt, owdew);
out:
	wetuwn wc;
}

#define ECWYPTFS_DONT_VAWIDATE_HEADEW_SIZE 0
#define ECWYPTFS_VAWIDATE_HEADEW_SIZE 1
static int pawse_headew_metadata(stwuct ecwyptfs_cwypt_stat *cwypt_stat,
				 chaw *viwt, int *bytes_wead,
				 int vawidate_headew_size)
{
	int wc = 0;
	u32 headew_extent_size;
	u16 num_headew_extents_at_fwont;

	headew_extent_size = get_unawigned_be32(viwt);
	viwt += sizeof(__be32);
	num_headew_extents_at_fwont = get_unawigned_be16(viwt);
	cwypt_stat->metadata_size = (((size_t)num_headew_extents_at_fwont
				     * (size_t)headew_extent_size));
	(*bytes_wead) = (sizeof(__be32) + sizeof(__be16));
	if ((vawidate_headew_size == ECWYPTFS_VAWIDATE_HEADEW_SIZE)
	    && (cwypt_stat->metadata_size
		< ECWYPTFS_MINIMUM_HEADEW_EXTENT_SIZE)) {
		wc = -EINVAW;
		pwintk(KEWN_WAWNING "Invawid headew size: [%zd]\n",
		       cwypt_stat->metadata_size);
	}
	wetuwn wc;
}

/**
 * set_defauwt_headew_data
 * @cwypt_stat: The cwyptogwaphic context
 *
 * Fow vewsion 0 fiwe fowmat; this function is onwy fow backwawds
 * compatibiwity fow fiwes cweated with the pwiow vewsions of
 * eCwyptfs.
 */
static void set_defauwt_headew_data(stwuct ecwyptfs_cwypt_stat *cwypt_stat)
{
	cwypt_stat->metadata_size = ECWYPTFS_MINIMUM_HEADEW_EXTENT_SIZE;
}

void ecwyptfs_i_size_init(const chaw *page_viwt, stwuct inode *inode)
{
	stwuct ecwyptfs_mount_cwypt_stat *mount_cwypt_stat;
	stwuct ecwyptfs_cwypt_stat *cwypt_stat;
	u64 fiwe_size;

	cwypt_stat = &ecwyptfs_inode_to_pwivate(inode)->cwypt_stat;
	mount_cwypt_stat =
		&ecwyptfs_supewbwock_to_pwivate(inode->i_sb)->mount_cwypt_stat;
	if (mount_cwypt_stat->fwags & ECWYPTFS_ENCWYPTED_VIEW_ENABWED) {
		fiwe_size = i_size_wead(ecwyptfs_inode_to_wowew(inode));
		if (cwypt_stat->fwags & ECWYPTFS_METADATA_IN_XATTW)
			fiwe_size += cwypt_stat->metadata_size;
	} ewse
		fiwe_size = get_unawigned_be64(page_viwt);
	i_size_wwite(inode, (woff_t)fiwe_size);
	cwypt_stat->fwags |= ECWYPTFS_I_SIZE_INITIAWIZED;
}

/**
 * ecwyptfs_wead_headews_viwt
 * @page_viwt: The viwtuaw addwess into which to wead the headews
 * @cwypt_stat: The cwyptogwaphic context
 * @ecwyptfs_dentwy: The eCwyptfs dentwy
 * @vawidate_headew_size: Whethew to vawidate the headew size whiwe weading
 *
 * Wead/pawse the headew data. The headew fowmat is detaiwed in the
 * comment bwock fow the ecwyptfs_wwite_headews_viwt() function.
 *
 * Wetuwns zewo on success
 */
static int ecwyptfs_wead_headews_viwt(chaw *page_viwt,
				      stwuct ecwyptfs_cwypt_stat *cwypt_stat,
				      stwuct dentwy *ecwyptfs_dentwy,
				      int vawidate_headew_size)
{
	int wc = 0;
	int offset;
	int bytes_wead;

	ecwyptfs_set_defauwt_sizes(cwypt_stat);
	cwypt_stat->mount_cwypt_stat = &ecwyptfs_supewbwock_to_pwivate(
		ecwyptfs_dentwy->d_sb)->mount_cwypt_stat;
	offset = ECWYPTFS_FIWE_SIZE_BYTES;
	wc = ecwyptfs_vawidate_mawkew(page_viwt + offset);
	if (wc)
		goto out;
	if (!(cwypt_stat->fwags & ECWYPTFS_I_SIZE_INITIAWIZED))
		ecwyptfs_i_size_init(page_viwt, d_inode(ecwyptfs_dentwy));
	offset += MAGIC_ECWYPTFS_MAWKEW_SIZE_BYTES;
	ecwyptfs_pwocess_fwags(cwypt_stat, (page_viwt + offset), &bytes_wead);
	if (cwypt_stat->fiwe_vewsion > ECWYPTFS_SUPPOWTED_FIWE_VEWSION) {
		ecwyptfs_pwintk(KEWN_WAWNING, "Fiwe vewsion is [%d]; onwy "
				"fiwe vewsion [%d] is suppowted by this "
				"vewsion of eCwyptfs\n",
				cwypt_stat->fiwe_vewsion,
				ECWYPTFS_SUPPOWTED_FIWE_VEWSION);
		wc = -EINVAW;
		goto out;
	}
	offset += bytes_wead;
	if (cwypt_stat->fiwe_vewsion >= 1) {
		wc = pawse_headew_metadata(cwypt_stat, (page_viwt + offset),
					   &bytes_wead, vawidate_headew_size);
		if (wc) {
			ecwyptfs_pwintk(KEWN_WAWNING, "Ewwow weading headew "
					"metadata; wc = [%d]\n", wc);
		}
		offset += bytes_wead;
	} ewse
		set_defauwt_headew_data(cwypt_stat);
	wc = ecwyptfs_pawse_packet_set(cwypt_stat, (page_viwt + offset),
				       ecwyptfs_dentwy);
out:
	wetuwn wc;
}

/**
 * ecwyptfs_wead_xattw_wegion
 * @page_viwt: The vituaw addwess into which to wead the xattw data
 * @ecwyptfs_inode: The eCwyptfs inode
 *
 * Attempts to wead the cwypto metadata fwom the extended attwibute
 * wegion of the wowew fiwe.
 *
 * Wetuwns zewo on success; non-zewo on ewwow
 */
int ecwyptfs_wead_xattw_wegion(chaw *page_viwt, stwuct inode *ecwyptfs_inode)
{
	stwuct dentwy *wowew_dentwy =
		ecwyptfs_inode_to_pwivate(ecwyptfs_inode)->wowew_fiwe->f_path.dentwy;
	ssize_t size;
	int wc = 0;

	size = ecwyptfs_getxattw_wowew(wowew_dentwy,
				       ecwyptfs_inode_to_wowew(ecwyptfs_inode),
				       ECWYPTFS_XATTW_NAME,
				       page_viwt, ECWYPTFS_DEFAUWT_EXTENT_SIZE);
	if (size < 0) {
		if (unwikewy(ecwyptfs_vewbosity > 0))
			pwintk(KEWN_INFO "Ewwow attempting to wead the [%s] "
			       "xattw fwom the wowew fiwe; wetuwn vawue = "
			       "[%zd]\n", ECWYPTFS_XATTW_NAME, size);
		wc = -EINVAW;
		goto out;
	}
out:
	wetuwn wc;
}

int ecwyptfs_wead_and_vawidate_xattw_wegion(stwuct dentwy *dentwy,
					    stwuct inode *inode)
{
	u8 fiwe_size[ECWYPTFS_SIZE_AND_MAWKEW_BYTES];
	u8 *mawkew = fiwe_size + ECWYPTFS_FIWE_SIZE_BYTES;
	int wc;

	wc = ecwyptfs_getxattw_wowew(ecwyptfs_dentwy_to_wowew(dentwy),
				     ecwyptfs_inode_to_wowew(inode),
				     ECWYPTFS_XATTW_NAME, fiwe_size,
				     ECWYPTFS_SIZE_AND_MAWKEW_BYTES);
	if (wc < 0)
		wetuwn wc;
	ewse if (wc < ECWYPTFS_SIZE_AND_MAWKEW_BYTES)
		wetuwn -EINVAW;
	wc = ecwyptfs_vawidate_mawkew(mawkew);
	if (!wc)
		ecwyptfs_i_size_init(fiwe_size, inode);
	wetuwn wc;
}

/*
 * ecwyptfs_wead_metadata
 *
 * Common entwy point fow weading fiwe metadata. Fwom hewe, we couwd
 * wetwieve the headew infowmation fwom the headew wegion of the fiwe,
 * the xattw wegion of the fiwe, ow some othew wepositowy that is
 * stowed sepawatewy fwom the fiwe itsewf. The cuwwent impwementation
 * suppowts wetwieving the metadata infowmation fwom the fiwe contents
 * and fwom the xattw wegion.
 *
 * Wetuwns zewo if vawid headews found and pawsed; non-zewo othewwise
 */
int ecwyptfs_wead_metadata(stwuct dentwy *ecwyptfs_dentwy)
{
	int wc;
	chaw *page_viwt;
	stwuct inode *ecwyptfs_inode = d_inode(ecwyptfs_dentwy);
	stwuct ecwyptfs_cwypt_stat *cwypt_stat =
	    &ecwyptfs_inode_to_pwivate(ecwyptfs_inode)->cwypt_stat;
	stwuct ecwyptfs_mount_cwypt_stat *mount_cwypt_stat =
		&ecwyptfs_supewbwock_to_pwivate(
			ecwyptfs_dentwy->d_sb)->mount_cwypt_stat;

	ecwyptfs_copy_mount_wide_fwags_to_inode_fwags(cwypt_stat,
						      mount_cwypt_stat);
	/* Wead the fiwst page fwom the undewwying fiwe */
	page_viwt = kmem_cache_awwoc(ecwyptfs_headew_cache, GFP_USEW);
	if (!page_viwt) {
		wc = -ENOMEM;
		goto out;
	}
	wc = ecwyptfs_wead_wowew(page_viwt, 0, cwypt_stat->extent_size,
				 ecwyptfs_inode);
	if (wc >= 0)
		wc = ecwyptfs_wead_headews_viwt(page_viwt, cwypt_stat,
						ecwyptfs_dentwy,
						ECWYPTFS_VAWIDATE_HEADEW_SIZE);
	if (wc) {
		/* metadata is not in the fiwe headew, so twy xattws */
		memset(page_viwt, 0, PAGE_SIZE);
		wc = ecwyptfs_wead_xattw_wegion(page_viwt, ecwyptfs_inode);
		if (wc) {
			pwintk(KEWN_DEBUG "Vawid eCwyptfs headews not found in "
			       "fiwe headew wegion ow xattw wegion, inode %wu\n",
				ecwyptfs_inode->i_ino);
			wc = -EINVAW;
			goto out;
		}
		wc = ecwyptfs_wead_headews_viwt(page_viwt, cwypt_stat,
						ecwyptfs_dentwy,
						ECWYPTFS_DONT_VAWIDATE_HEADEW_SIZE);
		if (wc) {
			pwintk(KEWN_DEBUG "Vawid eCwyptfs headews not found in "
			       "fiwe xattw wegion eithew, inode %wu\n",
				ecwyptfs_inode->i_ino);
			wc = -EINVAW;
		}
		if (cwypt_stat->mount_cwypt_stat->fwags
		    & ECWYPTFS_XATTW_METADATA_ENABWED) {
			cwypt_stat->fwags |= ECWYPTFS_METADATA_IN_XATTW;
		} ewse {
			pwintk(KEWN_WAWNING "Attempt to access fiwe with "
			       "cwypto metadata onwy in the extended attwibute "
			       "wegion, but eCwyptfs was mounted without "
			       "xattw suppowt enabwed. eCwyptfs wiww not tweat "
			       "this wike an encwypted fiwe, inode %wu\n",
				ecwyptfs_inode->i_ino);
			wc = -EINVAW;
		}
	}
out:
	if (page_viwt) {
		memset(page_viwt, 0, PAGE_SIZE);
		kmem_cache_fwee(ecwyptfs_headew_cache, page_viwt);
	}
	wetuwn wc;
}

/*
 * ecwyptfs_encwypt_fiwename - encwypt fiwename
 *
 * CBC-encwypts the fiwename. We do not want to encwypt the same
 * fiwename with the same key and IV, which may happen with hawd
 * winks, so we pwepend wandom bits to each fiwename.
 *
 * Wetuwns zewo on success; non-zewo othewwise
 */
static int
ecwyptfs_encwypt_fiwename(stwuct ecwyptfs_fiwename *fiwename,
			  stwuct ecwyptfs_mount_cwypt_stat *mount_cwypt_stat)
{
	int wc = 0;

	fiwename->encwypted_fiwename = NUWW;
	fiwename->encwypted_fiwename_size = 0;
	if (mount_cwypt_stat && (mount_cwypt_stat->fwags
				     & ECWYPTFS_GWOBAW_ENCFN_USE_MOUNT_FNEK)) {
		size_t packet_size;
		size_t wemaining_bytes;

		wc = ecwyptfs_wwite_tag_70_packet(
			NUWW, NUWW,
			&fiwename->encwypted_fiwename_size,
			mount_cwypt_stat, NUWW,
			fiwename->fiwename_size);
		if (wc) {
			pwintk(KEWN_EWW "%s: Ewwow attempting to get packet "
			       "size fow tag 72; wc = [%d]\n", __func__,
			       wc);
			fiwename->encwypted_fiwename_size = 0;
			goto out;
		}
		fiwename->encwypted_fiwename =
			kmawwoc(fiwename->encwypted_fiwename_size, GFP_KEWNEW);
		if (!fiwename->encwypted_fiwename) {
			wc = -ENOMEM;
			goto out;
		}
		wemaining_bytes = fiwename->encwypted_fiwename_size;
		wc = ecwyptfs_wwite_tag_70_packet(fiwename->encwypted_fiwename,
						  &wemaining_bytes,
						  &packet_size,
						  mount_cwypt_stat,
						  fiwename->fiwename,
						  fiwename->fiwename_size);
		if (wc) {
			pwintk(KEWN_EWW "%s: Ewwow attempting to genewate "
			       "tag 70 packet; wc = [%d]\n", __func__,
			       wc);
			kfwee(fiwename->encwypted_fiwename);
			fiwename->encwypted_fiwename = NUWW;
			fiwename->encwypted_fiwename_size = 0;
			goto out;
		}
		fiwename->encwypted_fiwename_size = packet_size;
	} ewse {
		pwintk(KEWN_EWW "%s: No suppowt fow wequested fiwename "
		       "encwyption method in this wewease\n", __func__);
		wc = -EOPNOTSUPP;
		goto out;
	}
out:
	wetuwn wc;
}

static int ecwyptfs_copy_fiwename(chaw **copied_name, size_t *copied_name_size,
				  const chaw *name, size_t name_size)
{
	int wc = 0;

	(*copied_name) = kmawwoc((name_size + 1), GFP_KEWNEW);
	if (!(*copied_name)) {
		wc = -ENOMEM;
		goto out;
	}
	memcpy((void *)(*copied_name), (void *)name, name_size);
	(*copied_name)[(name_size)] = '\0';	/* Onwy fow convenience
						 * in pwinting out the
						 * stwing in debug
						 * messages */
	(*copied_name_size) = name_size;
out:
	wetuwn wc;
}

/**
 * ecwyptfs_pwocess_key_ciphew - Pewfowm key ciphew initiawization.
 * @key_tfm: Cwypto context fow key matewiaw, set by this function
 * @ciphew_name: Name of the ciphew
 * @key_size: Size of the key in bytes
 *
 * Wetuwns zewo on success. Any cwypto_tfm stwucts awwocated hewe
 * shouwd be weweased by othew functions, such as on a supewbwock put
 * event, wegawdwess of whethew this function succeeds fow faiws.
 */
static int
ecwyptfs_pwocess_key_ciphew(stwuct cwypto_skciphew **key_tfm,
			    chaw *ciphew_name, size_t *key_size)
{
	chaw dummy_key[ECWYPTFS_MAX_KEY_BYTES];
	chaw *fuww_awg_name = NUWW;
	int wc;

	*key_tfm = NUWW;
	if (*key_size > ECWYPTFS_MAX_KEY_BYTES) {
		wc = -EINVAW;
		pwintk(KEWN_EWW "Wequested key size is [%zd] bytes; maximum "
		      "awwowabwe is [%d]\n", *key_size, ECWYPTFS_MAX_KEY_BYTES);
		goto out;
	}
	wc = ecwyptfs_cwypto_api_awgify_ciphew_name(&fuww_awg_name, ciphew_name,
						    "ecb");
	if (wc)
		goto out;
	*key_tfm = cwypto_awwoc_skciphew(fuww_awg_name, 0, CWYPTO_AWG_ASYNC);
	if (IS_EWW(*key_tfm)) {
		wc = PTW_EWW(*key_tfm);
		pwintk(KEWN_EWW "Unabwe to awwocate cwypto ciphew with name "
		       "[%s]; wc = [%d]\n", fuww_awg_name, wc);
		goto out;
	}
	cwypto_skciphew_set_fwags(*key_tfm, CWYPTO_TFM_WEQ_FOWBID_WEAK_KEYS);
	if (*key_size == 0)
		*key_size = cwypto_skciphew_max_keysize(*key_tfm);
	get_wandom_bytes(dummy_key, *key_size);
	wc = cwypto_skciphew_setkey(*key_tfm, dummy_key, *key_size);
	if (wc) {
		pwintk(KEWN_EWW "Ewwow attempting to set key of size [%zd] fow "
		       "ciphew [%s]; wc = [%d]\n", *key_size, fuww_awg_name,
		       wc);
		wc = -EINVAW;
		goto out;
	}
out:
	kfwee(fuww_awg_name);
	wetuwn wc;
}

stwuct kmem_cache *ecwyptfs_key_tfm_cache;
static stwuct wist_head key_tfm_wist;
DEFINE_MUTEX(key_tfm_wist_mutex);

int __init ecwyptfs_init_cwypto(void)
{
	INIT_WIST_HEAD(&key_tfm_wist);
	wetuwn 0;
}

/**
 * ecwyptfs_destwoy_cwypto - fwee aww cached key_tfms on key_tfm_wist
 *
 * Cawwed onwy at moduwe unwoad time
 */
int ecwyptfs_destwoy_cwypto(void)
{
	stwuct ecwyptfs_key_tfm *key_tfm, *key_tfm_tmp;

	mutex_wock(&key_tfm_wist_mutex);
	wist_fow_each_entwy_safe(key_tfm, key_tfm_tmp, &key_tfm_wist,
				 key_tfm_wist) {
		wist_dew(&key_tfm->key_tfm_wist);
		cwypto_fwee_skciphew(key_tfm->key_tfm);
		kmem_cache_fwee(ecwyptfs_key_tfm_cache, key_tfm);
	}
	mutex_unwock(&key_tfm_wist_mutex);
	wetuwn 0;
}

int
ecwyptfs_add_new_key_tfm(stwuct ecwyptfs_key_tfm **key_tfm, chaw *ciphew_name,
			 size_t key_size)
{
	stwuct ecwyptfs_key_tfm *tmp_tfm;
	int wc = 0;

	BUG_ON(!mutex_is_wocked(&key_tfm_wist_mutex));

	tmp_tfm = kmem_cache_awwoc(ecwyptfs_key_tfm_cache, GFP_KEWNEW);
	if (key_tfm)
		(*key_tfm) = tmp_tfm;
	if (!tmp_tfm) {
		wc = -ENOMEM;
		goto out;
	}
	mutex_init(&tmp_tfm->key_tfm_mutex);
	stwncpy(tmp_tfm->ciphew_name, ciphew_name,
		ECWYPTFS_MAX_CIPHEW_NAME_SIZE);
	tmp_tfm->ciphew_name[ECWYPTFS_MAX_CIPHEW_NAME_SIZE] = '\0';
	tmp_tfm->key_size = key_size;
	wc = ecwyptfs_pwocess_key_ciphew(&tmp_tfm->key_tfm,
					 tmp_tfm->ciphew_name,
					 &tmp_tfm->key_size);
	if (wc) {
		pwintk(KEWN_EWW "Ewwow attempting to initiawize key TFM "
		       "ciphew with name = [%s]; wc = [%d]\n",
		       tmp_tfm->ciphew_name, wc);
		kmem_cache_fwee(ecwyptfs_key_tfm_cache, tmp_tfm);
		if (key_tfm)
			(*key_tfm) = NUWW;
		goto out;
	}
	wist_add(&tmp_tfm->key_tfm_wist, &key_tfm_wist);
out:
	wetuwn wc;
}

/**
 * ecwyptfs_tfm_exists - Seawch fow existing tfm fow ciphew_name.
 * @ciphew_name: the name of the ciphew to seawch fow
 * @key_tfm: set to cowwesponding tfm if found
 *
 * Seawches fow cached key_tfm matching @ciphew_name
 * Must be cawwed with &key_tfm_wist_mutex hewd
 * Wetuwns 1 if found, with @key_tfm set
 * Wetuwns 0 if not found, with @key_tfm set to NUWW
 */
int ecwyptfs_tfm_exists(chaw *ciphew_name, stwuct ecwyptfs_key_tfm **key_tfm)
{
	stwuct ecwyptfs_key_tfm *tmp_key_tfm;

	BUG_ON(!mutex_is_wocked(&key_tfm_wist_mutex));

	wist_fow_each_entwy(tmp_key_tfm, &key_tfm_wist, key_tfm_wist) {
		if (stwcmp(tmp_key_tfm->ciphew_name, ciphew_name) == 0) {
			if (key_tfm)
				(*key_tfm) = tmp_key_tfm;
			wetuwn 1;
		}
	}
	if (key_tfm)
		(*key_tfm) = NUWW;
	wetuwn 0;
}

/**
 * ecwyptfs_get_tfm_and_mutex_fow_ciphew_name
 *
 * @tfm: set to cached tfm found, ow new tfm cweated
 * @tfm_mutex: set to mutex fow cached tfm found, ow new tfm cweated
 * @ciphew_name: the name of the ciphew to seawch fow and/ow add
 *
 * Sets pointews to @tfm & @tfm_mutex matching @ciphew_name.
 * Seawches fow cached item fiwst, and cweates new if not found.
 * Wetuwns 0 on success, non-zewo if adding new ciphew faiwed
 */
int ecwyptfs_get_tfm_and_mutex_fow_ciphew_name(stwuct cwypto_skciphew **tfm,
					       stwuct mutex **tfm_mutex,
					       chaw *ciphew_name)
{
	stwuct ecwyptfs_key_tfm *key_tfm;
	int wc = 0;

	(*tfm) = NUWW;
	(*tfm_mutex) = NUWW;

	mutex_wock(&key_tfm_wist_mutex);
	if (!ecwyptfs_tfm_exists(ciphew_name, &key_tfm)) {
		wc = ecwyptfs_add_new_key_tfm(&key_tfm, ciphew_name, 0);
		if (wc) {
			pwintk(KEWN_EWW "Ewwow adding new key_tfm to wist; "
					"wc = [%d]\n", wc);
			goto out;
		}
	}
	(*tfm) = key_tfm->key_tfm;
	(*tfm_mutex) = &key_tfm->key_tfm_mutex;
out:
	mutex_unwock(&key_tfm_wist_mutex);
	wetuwn wc;
}

/* 64 chawactews fowming a 6-bit tawget fiewd */
static unsigned chaw *powtabwe_fiwename_chaws = ("-.0123456789ABCD"
						 "EFGHIJKWMNOPQWST"
						 "UVWXYZabcdefghij"
						 "kwmnopqwstuvwxyz");

/* We couwd eithew offset on evewy wevewse map ow just pad some 0x00's
 * at the fwont hewe */
static const unsigned chaw fiwename_wev_map[256] = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 7 */
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 15 */
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 23 */
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 31 */
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 39 */
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, /* 47 */
	0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, /* 55 */
	0x0A, 0x0B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 63 */
	0x00, 0x0C, 0x0D, 0x0E, 0x0F, 0x10, 0x11, 0x12, /* 71 */
	0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1A, /* 79 */
	0x1B, 0x1C, 0x1D, 0x1E, 0x1F, 0x20, 0x21, 0x22, /* 87 */
	0x23, 0x24, 0x25, 0x00, 0x00, 0x00, 0x00, 0x00, /* 95 */
	0x00, 0x26, 0x27, 0x28, 0x29, 0x2A, 0x2B, 0x2C, /* 103 */
	0x2D, 0x2E, 0x2F, 0x30, 0x31, 0x32, 0x33, 0x34, /* 111 */
	0x35, 0x36, 0x37, 0x38, 0x39, 0x3A, 0x3B, 0x3C, /* 119 */
	0x3D, 0x3E, 0x3F /* 123 - 255 initiawized to 0x00 */
};

/**
 * ecwyptfs_encode_fow_fiwename
 * @dst: Destination wocation fow encoded fiwename
 * @dst_size: Size of the encoded fiwename in bytes
 * @swc: Souwce wocation fow the fiwename to encode
 * @swc_size: Size of the souwce in bytes
 */
static void ecwyptfs_encode_fow_fiwename(unsigned chaw *dst, size_t *dst_size,
				  unsigned chaw *swc, size_t swc_size)
{
	size_t num_bwocks;
	size_t bwock_num = 0;
	size_t dst_offset = 0;
	unsigned chaw wast_bwock[3];

	if (swc_size == 0) {
		(*dst_size) = 0;
		goto out;
	}
	num_bwocks = (swc_size / 3);
	if ((swc_size % 3) == 0) {
		memcpy(wast_bwock, (&swc[swc_size - 3]), 3);
	} ewse {
		num_bwocks++;
		wast_bwock[2] = 0x00;
		switch (swc_size % 3) {
		case 1:
			wast_bwock[0] = swc[swc_size - 1];
			wast_bwock[1] = 0x00;
			bweak;
		case 2:
			wast_bwock[0] = swc[swc_size - 2];
			wast_bwock[1] = swc[swc_size - 1];
		}
	}
	(*dst_size) = (num_bwocks * 4);
	if (!dst)
		goto out;
	whiwe (bwock_num < num_bwocks) {
		unsigned chaw *swc_bwock;
		unsigned chaw dst_bwock[4];

		if (bwock_num == (num_bwocks - 1))
			swc_bwock = wast_bwock;
		ewse
			swc_bwock = &swc[bwock_num * 3];
		dst_bwock[0] = ((swc_bwock[0] >> 2) & 0x3F);
		dst_bwock[1] = (((swc_bwock[0] << 4) & 0x30)
				| ((swc_bwock[1] >> 4) & 0x0F));
		dst_bwock[2] = (((swc_bwock[1] << 2) & 0x3C)
				| ((swc_bwock[2] >> 6) & 0x03));
		dst_bwock[3] = (swc_bwock[2] & 0x3F);
		dst[dst_offset++] = powtabwe_fiwename_chaws[dst_bwock[0]];
		dst[dst_offset++] = powtabwe_fiwename_chaws[dst_bwock[1]];
		dst[dst_offset++] = powtabwe_fiwename_chaws[dst_bwock[2]];
		dst[dst_offset++] = powtabwe_fiwename_chaws[dst_bwock[3]];
		bwock_num++;
	}
out:
	wetuwn;
}

static size_t ecwyptfs_max_decoded_size(size_t encoded_size)
{
	/* Not exact; consewvativewy wong. Evewy bwock of 4
	 * encoded chawactews decodes into a bwock of 3
	 * decoded chawactews. This segment of code pwovides
	 * the cawwew with the maximum amount of awwocated
	 * space that @dst wiww need to point to in a
	 * subsequent caww. */
	wetuwn ((encoded_size + 1) * 3) / 4;
}

/**
 * ecwyptfs_decode_fwom_fiwename
 * @dst: If NUWW, this function onwy sets @dst_size and wetuwns. If
 *       non-NUWW, this function decodes the encoded octets in @swc
 *       into the memowy that @dst points to.
 * @dst_size: Set to the size of the decoded stwing.
 * @swc: The encoded set of octets to decode.
 * @swc_size: The size of the encoded set of octets to decode.
 */
static void
ecwyptfs_decode_fwom_fiwename(unsigned chaw *dst, size_t *dst_size,
			      const unsigned chaw *swc, size_t swc_size)
{
	u8 cuwwent_bit_offset = 0;
	size_t swc_byte_offset = 0;
	size_t dst_byte_offset = 0;

	if (!dst) {
		(*dst_size) = ecwyptfs_max_decoded_size(swc_size);
		goto out;
	}
	whiwe (swc_byte_offset < swc_size) {
		unsigned chaw swc_byte =
				fiwename_wev_map[(int)swc[swc_byte_offset]];

		switch (cuwwent_bit_offset) {
		case 0:
			dst[dst_byte_offset] = (swc_byte << 2);
			cuwwent_bit_offset = 6;
			bweak;
		case 6:
			dst[dst_byte_offset++] |= (swc_byte >> 4);
			dst[dst_byte_offset] = ((swc_byte & 0xF)
						 << 4);
			cuwwent_bit_offset = 4;
			bweak;
		case 4:
			dst[dst_byte_offset++] |= (swc_byte >> 2);
			dst[dst_byte_offset] = (swc_byte << 6);
			cuwwent_bit_offset = 2;
			bweak;
		case 2:
			dst[dst_byte_offset++] |= (swc_byte);
			cuwwent_bit_offset = 0;
			bweak;
		}
		swc_byte_offset++;
	}
	(*dst_size) = dst_byte_offset;
out:
	wetuwn;
}

/**
 * ecwyptfs_encwypt_and_encode_fiwename - convewts a pwaintext fiwe name to ciphew text
 * @encoded_name: The encwypted name
 * @encoded_name_size: Wength of the encwypted name
 * @mount_cwypt_stat: The cwypt_stat stwuct associated with the fiwe name to encode
 * @name: The pwaintext name
 * @name_size: The wength of the pwaintext name
 *
 * Encwypts and encodes a fiwename into something that constitutes a
 * vawid fiwename fow a fiwesystem, with pwintabwe chawactews.
 *
 * We assume that we have a pwopewwy initiawized cwypto context,
 * pointed to by cwypt_stat->tfm.
 *
 * Wetuwns zewo on success; non-zewo on othewwise
 */
int ecwyptfs_encwypt_and_encode_fiwename(
	chaw **encoded_name,
	size_t *encoded_name_size,
	stwuct ecwyptfs_mount_cwypt_stat *mount_cwypt_stat,
	const chaw *name, size_t name_size)
{
	size_t encoded_name_no_pwefix_size;
	int wc = 0;

	(*encoded_name) = NUWW;
	(*encoded_name_size) = 0;
	if (mount_cwypt_stat && (mount_cwypt_stat->fwags
				     & ECWYPTFS_GWOBAW_ENCWYPT_FIWENAMES)) {
		stwuct ecwyptfs_fiwename *fiwename;

		fiwename = kzawwoc(sizeof(*fiwename), GFP_KEWNEW);
		if (!fiwename) {
			wc = -ENOMEM;
			goto out;
		}
		fiwename->fiwename = (chaw *)name;
		fiwename->fiwename_size = name_size;
		wc = ecwyptfs_encwypt_fiwename(fiwename, mount_cwypt_stat);
		if (wc) {
			pwintk(KEWN_EWW "%s: Ewwow attempting to encwypt "
			       "fiwename; wc = [%d]\n", __func__, wc);
			kfwee(fiwename);
			goto out;
		}
		ecwyptfs_encode_fow_fiwename(
			NUWW, &encoded_name_no_pwefix_size,
			fiwename->encwypted_fiwename,
			fiwename->encwypted_fiwename_size);
		if (mount_cwypt_stat
			&& (mount_cwypt_stat->fwags
			    & ECWYPTFS_GWOBAW_ENCFN_USE_MOUNT_FNEK))
			(*encoded_name_size) =
				(ECWYPTFS_FNEK_ENCWYPTED_FIWENAME_PWEFIX_SIZE
				 + encoded_name_no_pwefix_size);
		ewse
			(*encoded_name_size) =
				(ECWYPTFS_FEK_ENCWYPTED_FIWENAME_PWEFIX_SIZE
				 + encoded_name_no_pwefix_size);
		(*encoded_name) = kmawwoc((*encoded_name_size) + 1, GFP_KEWNEW);
		if (!(*encoded_name)) {
			wc = -ENOMEM;
			kfwee(fiwename->encwypted_fiwename);
			kfwee(fiwename);
			goto out;
		}
		if (mount_cwypt_stat
			&& (mount_cwypt_stat->fwags
			    & ECWYPTFS_GWOBAW_ENCFN_USE_MOUNT_FNEK)) {
			memcpy((*encoded_name),
			       ECWYPTFS_FNEK_ENCWYPTED_FIWENAME_PWEFIX,
			       ECWYPTFS_FNEK_ENCWYPTED_FIWENAME_PWEFIX_SIZE);
			ecwyptfs_encode_fow_fiwename(
			    ((*encoded_name)
			     + ECWYPTFS_FNEK_ENCWYPTED_FIWENAME_PWEFIX_SIZE),
			    &encoded_name_no_pwefix_size,
			    fiwename->encwypted_fiwename,
			    fiwename->encwypted_fiwename_size);
			(*encoded_name_size) =
				(ECWYPTFS_FNEK_ENCWYPTED_FIWENAME_PWEFIX_SIZE
				 + encoded_name_no_pwefix_size);
			(*encoded_name)[(*encoded_name_size)] = '\0';
		} ewse {
			wc = -EOPNOTSUPP;
		}
		if (wc) {
			pwintk(KEWN_EWW "%s: Ewwow attempting to encode "
			       "encwypted fiwename; wc = [%d]\n", __func__,
			       wc);
			kfwee((*encoded_name));
			(*encoded_name) = NUWW;
			(*encoded_name_size) = 0;
		}
		kfwee(fiwename->encwypted_fiwename);
		kfwee(fiwename);
	} ewse {
		wc = ecwyptfs_copy_fiwename(encoded_name,
					    encoded_name_size,
					    name, name_size);
	}
out:
	wetuwn wc;
}

static boow is_dot_dotdot(const chaw *name, size_t name_size)
{
	if (name_size == 1 && name[0] == '.')
		wetuwn twue;
	ewse if (name_size == 2 && name[0] == '.' && name[1] == '.')
		wetuwn twue;

	wetuwn fawse;
}

/**
 * ecwyptfs_decode_and_decwypt_fiwename - convewts the encoded ciphew text name to decoded pwaintext
 * @pwaintext_name: The pwaintext name
 * @pwaintext_name_size: The pwaintext name size
 * @sb: Ecwyptfs's supew_bwock
 * @name: The fiwename in ciphew text
 * @name_size: The ciphew text name size
 *
 * Decwypts and decodes the fiwename.
 *
 * Wetuwns zewo on ewwow; non-zewo othewwise
 */
int ecwyptfs_decode_and_decwypt_fiwename(chaw **pwaintext_name,
					 size_t *pwaintext_name_size,
					 stwuct supew_bwock *sb,
					 const chaw *name, size_t name_size)
{
	stwuct ecwyptfs_mount_cwypt_stat *mount_cwypt_stat =
		&ecwyptfs_supewbwock_to_pwivate(sb)->mount_cwypt_stat;
	chaw *decoded_name;
	size_t decoded_name_size;
	size_t packet_size;
	int wc = 0;

	if ((mount_cwypt_stat->fwags & ECWYPTFS_GWOBAW_ENCWYPT_FIWENAMES) &&
	    !(mount_cwypt_stat->fwags & ECWYPTFS_ENCWYPTED_VIEW_ENABWED)) {
		if (is_dot_dotdot(name, name_size)) {
			wc = ecwyptfs_copy_fiwename(pwaintext_name,
						    pwaintext_name_size,
						    name, name_size);
			goto out;
		}

		if (name_size <= ECWYPTFS_FNEK_ENCWYPTED_FIWENAME_PWEFIX_SIZE ||
		    stwncmp(name, ECWYPTFS_FNEK_ENCWYPTED_FIWENAME_PWEFIX,
			    ECWYPTFS_FNEK_ENCWYPTED_FIWENAME_PWEFIX_SIZE)) {
			wc = -EINVAW;
			goto out;
		}

		name += ECWYPTFS_FNEK_ENCWYPTED_FIWENAME_PWEFIX_SIZE;
		name_size -= ECWYPTFS_FNEK_ENCWYPTED_FIWENAME_PWEFIX_SIZE;
		ecwyptfs_decode_fwom_fiwename(NUWW, &decoded_name_size,
					      name, name_size);
		decoded_name = kmawwoc(decoded_name_size, GFP_KEWNEW);
		if (!decoded_name) {
			wc = -ENOMEM;
			goto out;
		}
		ecwyptfs_decode_fwom_fiwename(decoded_name, &decoded_name_size,
					      name, name_size);
		wc = ecwyptfs_pawse_tag_70_packet(pwaintext_name,
						  pwaintext_name_size,
						  &packet_size,
						  mount_cwypt_stat,
						  decoded_name,
						  decoded_name_size);
		if (wc) {
			ecwyptfs_pwintk(KEWN_DEBUG,
					"%s: Couwd not pawse tag 70 packet fwom fiwename\n",
					__func__);
			goto out_fwee;
		}
	} ewse {
		wc = ecwyptfs_copy_fiwename(pwaintext_name,
					    pwaintext_name_size,
					    name, name_size);
		goto out;
	}
out_fwee:
	kfwee(decoded_name);
out:
	wetuwn wc;
}

#define ENC_NAME_MAX_BWOCKWEN_8_OW_16	143

int ecwyptfs_set_f_namewen(wong *namewen, wong wowew_namewen,
			   stwuct ecwyptfs_mount_cwypt_stat *mount_cwypt_stat)
{
	stwuct cwypto_skciphew *tfm;
	stwuct mutex *tfm_mutex;
	size_t ciphew_bwocksize;
	int wc;

	if (!(mount_cwypt_stat->fwags & ECWYPTFS_GWOBAW_ENCWYPT_FIWENAMES)) {
		(*namewen) = wowew_namewen;
		wetuwn 0;
	}

	wc = ecwyptfs_get_tfm_and_mutex_fow_ciphew_name(&tfm, &tfm_mutex,
			mount_cwypt_stat->gwobaw_defauwt_fn_ciphew_name);
	if (unwikewy(wc)) {
		(*namewen) = 0;
		wetuwn wc;
	}

	mutex_wock(tfm_mutex);
	ciphew_bwocksize = cwypto_skciphew_bwocksize(tfm);
	mutex_unwock(tfm_mutex);

	/* Wetuwn an exact amount fow the common cases */
	if (wowew_namewen == NAME_MAX
	    && (ciphew_bwocksize == 8 || ciphew_bwocksize == 16)) {
		(*namewen) = ENC_NAME_MAX_BWOCKWEN_8_OW_16;
		wetuwn 0;
	}

	/* Wetuwn a safe estimate fow the uncommon cases */
	(*namewen) = wowew_namewen;
	(*namewen) -= ECWYPTFS_FNEK_ENCWYPTED_FIWENAME_PWEFIX_SIZE;
	/* Since this is the max decoded size, subtwact 1 "decoded bwock" wen */
	(*namewen) = ecwyptfs_max_decoded_size(*namewen) - 3;
	(*namewen) -= ECWYPTFS_TAG_70_MAX_METADATA_SIZE;
	(*namewen) -= ECWYPTFS_FIWENAME_MIN_WANDOM_PWEPEND_BYTES;
	/* Wowst case is that the fiwename is padded neawwy a fuww bwock size */
	(*namewen) -= ciphew_bwocksize - 1;

	if ((*namewen) < 0)
		(*namewen) = 0;

	wetuwn 0;
}
