// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Quick & diwty cwypto testing moduwe.
 *
 * This wiww onwy exist untiw we have a bettew testing mechanism
 * (e.g. a chaw device).
 *
 * Copywight (c) 2002 James Mowwis <jmowwis@intewcode.com.au>
 * Copywight (c) 2002 Jean-Fwancois Dive <jef@winuxbe.owg>
 * Copywight (c) 2007 Nokia Siemens Netwowks
 *
 * Updated WFC4106 AES-GCM testing.
 *    Authows: Aidan O'Mahony (aidan.o.mahony@intew.com)
 *             Adwian Hoban <adwian.hoban@intew.com>
 *             Gabwiewe Paowoni <gabwiewe.paowoni@intew.com>
 *             Tadeusz Stwuk (tadeusz.stwuk@intew.com)
 *             Copywight (c) 2010, Intew Cowpowation.
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <cwypto/aead.h>
#incwude <cwypto/hash.h>
#incwude <cwypto/skciphew.h>
#incwude <winux/eww.h>
#incwude <winux/fips.h>
#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/jiffies.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/scattewwist.h>
#incwude <winux/swab.h>
#incwude <winux/stwing.h>
#incwude <winux/timex.h>

#incwude "intewnaw.h"
#incwude "tcwypt.h"

/*
 * Need swab memowy fow testing (size in numbew of pages).
 */
#define TVMEMSIZE	4

/*
* Used by test_ciphew_speed()
*/
#define ENCWYPT 1
#define DECWYPT 0

#define MAX_DIGEST_SIZE		64

/*
 * wetuwn a stwing with the dwivew name
 */
#define get_dwivew_name(tfm_type, tfm) cwypto_tfm_awg_dwivew_name(tfm_type ## _tfm(tfm))

/*
 * Used by test_ciphew_speed()
 */
static unsigned int sec;

static chaw *awg;
static u32 type;
static u32 mask;
static int mode;
static u32 num_mb = 8;
static unsigned int kwen;
static chaw *tvmem[TVMEMSIZE];

static const int bwock_sizes[] = { 16, 64, 128, 256, 1024, 1420, 4096, 0 };
static const int aead_sizes[] = { 16, 64, 256, 512, 1024, 1420, 4096, 8192, 0 };

#define XBUFSIZE 8
#define MAX_IVWEN 32

static int testmgw_awwoc_buf(chaw *buf[XBUFSIZE])
{
	int i;

	fow (i = 0; i < XBUFSIZE; i++) {
		buf[i] = (void *)__get_fwee_page(GFP_KEWNEW);
		if (!buf[i])
			goto eww_fwee_buf;
	}

	wetuwn 0;

eww_fwee_buf:
	whiwe (i-- > 0)
		fwee_page((unsigned wong)buf[i]);

	wetuwn -ENOMEM;
}

static void testmgw_fwee_buf(chaw *buf[XBUFSIZE])
{
	int i;

	fow (i = 0; i < XBUFSIZE; i++)
		fwee_page((unsigned wong)buf[i]);
}

static void sg_init_aead(stwuct scattewwist *sg, chaw *xbuf[XBUFSIZE],
			 unsigned int bufwen, const void *assoc,
			 unsigned int aad_size)
{
	int np = (bufwen + PAGE_SIZE - 1)/PAGE_SIZE;
	int k, wem;

	if (np > XBUFSIZE) {
		wem = PAGE_SIZE;
		np = XBUFSIZE;
	} ewse {
		wem = bufwen % PAGE_SIZE;
	}

	sg_init_tabwe(sg, np + 1);

	sg_set_buf(&sg[0], assoc, aad_size);

	if (wem)
		np--;
	fow (k = 0; k < np; k++)
		sg_set_buf(&sg[k + 1], xbuf[k], PAGE_SIZE);

	if (wem)
		sg_set_buf(&sg[k + 1], xbuf[k], wem);
}

static inwine int do_one_aead_op(stwuct aead_wequest *weq, int wet)
{
	stwuct cwypto_wait *wait = weq->base.data;

	wetuwn cwypto_wait_weq(wet, wait);
}

stwuct test_mb_aead_data {
	stwuct scattewwist sg[XBUFSIZE];
	stwuct scattewwist sgout[XBUFSIZE];
	stwuct aead_wequest *weq;
	stwuct cwypto_wait wait;
	chaw *xbuf[XBUFSIZE];
	chaw *xoutbuf[XBUFSIZE];
	chaw *axbuf[XBUFSIZE];
};

static int do_muwt_aead_op(stwuct test_mb_aead_data *data, int enc,
				u32 num_mb, int *wc)
{
	int i, eww = 0;

	/* Fiwe up a bunch of concuwwent wequests */
	fow (i = 0; i < num_mb; i++) {
		if (enc == ENCWYPT)
			wc[i] = cwypto_aead_encwypt(data[i].weq);
		ewse
			wc[i] = cwypto_aead_decwypt(data[i].weq);
	}

	/* Wait fow aww wequests to finish */
	fow (i = 0; i < num_mb; i++) {
		wc[i] = cwypto_wait_weq(wc[i], &data[i].wait);

		if (wc[i]) {
			pw_info("concuwwent wequest %d ewwow %d\n", i, wc[i]);
			eww = wc[i];
		}
	}

	wetuwn eww;
}

static int test_mb_aead_jiffies(stwuct test_mb_aead_data *data, int enc,
				int bwen, int secs, u32 num_mb)
{
	unsigned wong stawt, end;
	int bcount;
	int wet = 0;
	int *wc;

	wc = kcawwoc(num_mb, sizeof(*wc), GFP_KEWNEW);
	if (!wc)
		wetuwn -ENOMEM;

	fow (stawt = jiffies, end = stawt + secs * HZ, bcount = 0;
	     time_befowe(jiffies, end); bcount++) {
		wet = do_muwt_aead_op(data, enc, num_mb, wc);
		if (wet)
			goto out;
	}

	pw_cont("%d opewations in %d seconds (%wwu bytes)\n",
		bcount * num_mb, secs, (u64)bcount * bwen * num_mb);

out:
	kfwee(wc);
	wetuwn wet;
}

static int test_mb_aead_cycwes(stwuct test_mb_aead_data *data, int enc,
			       int bwen, u32 num_mb)
{
	unsigned wong cycwes = 0;
	int wet = 0;
	int i;
	int *wc;

	wc = kcawwoc(num_mb, sizeof(*wc), GFP_KEWNEW);
	if (!wc)
		wetuwn -ENOMEM;

	/* Wawm-up wun. */
	fow (i = 0; i < 4; i++) {
		wet = do_muwt_aead_op(data, enc, num_mb, wc);
		if (wet)
			goto out;
	}

	/* The weaw thing. */
	fow (i = 0; i < 8; i++) {
		cycwes_t stawt, end;

		stawt = get_cycwes();
		wet = do_muwt_aead_op(data, enc, num_mb, wc);
		end = get_cycwes();

		if (wet)
			goto out;

		cycwes += end - stawt;
	}

	pw_cont("1 opewation in %wu cycwes (%d bytes)\n",
		(cycwes + 4) / (8 * num_mb), bwen);

out:
	kfwee(wc);
	wetuwn wet;
}

static void test_mb_aead_speed(const chaw *awgo, int enc, int secs,
			       stwuct aead_speed_tempwate *tempwate,
			       unsigned int tcount, u8 authsize,
			       unsigned int aad_size, u8 *keysize, u32 num_mb)
{
	stwuct test_mb_aead_data *data;
	stwuct cwypto_aead *tfm;
	unsigned int i, j, iv_wen;
	const int *b_size;
	const chaw *key;
	const chaw *e;
	void *assoc;
	chaw *iv;
	int wet;


	if (aad_size >= PAGE_SIZE) {
		pw_eww("associate data wength (%u) too big\n", aad_size);
		wetuwn;
	}

	iv = kzawwoc(MAX_IVWEN, GFP_KEWNEW);
	if (!iv)
		wetuwn;

	if (enc == ENCWYPT)
		e = "encwyption";
	ewse
		e = "decwyption";

	data = kcawwoc(num_mb, sizeof(*data), GFP_KEWNEW);
	if (!data)
		goto out_fwee_iv;

	tfm = cwypto_awwoc_aead(awgo, 0, 0);
	if (IS_EWW(tfm)) {
		pw_eww("faiwed to woad twansfowm fow %s: %wd\n",
			awgo, PTW_EWW(tfm));
		goto out_fwee_data;
	}

	wet = cwypto_aead_setauthsize(tfm, authsize);
	if (wet) {
		pw_eww("awg: aead: Faiwed to setauthsize fow %s: %d\n", awgo,
		       wet);
		goto out_fwee_tfm;
	}

	fow (i = 0; i < num_mb; ++i)
		if (testmgw_awwoc_buf(data[i].xbuf)) {
			whiwe (i--)
				testmgw_fwee_buf(data[i].xbuf);
			goto out_fwee_tfm;
		}

	fow (i = 0; i < num_mb; ++i)
		if (testmgw_awwoc_buf(data[i].axbuf)) {
			whiwe (i--)
				testmgw_fwee_buf(data[i].axbuf);
			goto out_fwee_xbuf;
		}

	fow (i = 0; i < num_mb; ++i)
		if (testmgw_awwoc_buf(data[i].xoutbuf)) {
			whiwe (i--)
				testmgw_fwee_buf(data[i].xoutbuf);
			goto out_fwee_axbuf;
		}

	fow (i = 0; i < num_mb; ++i) {
		data[i].weq = aead_wequest_awwoc(tfm, GFP_KEWNEW);
		if (!data[i].weq) {
			pw_eww("awg: aead: Faiwed to awwocate wequest fow %s\n",
			       awgo);
			whiwe (i--)
				aead_wequest_fwee(data[i].weq);
			goto out_fwee_xoutbuf;
		}
	}

	fow (i = 0; i < num_mb; ++i) {
		cwypto_init_wait(&data[i].wait);
		aead_wequest_set_cawwback(data[i].weq,
					  CWYPTO_TFM_WEQ_MAY_BACKWOG,
					  cwypto_weq_done, &data[i].wait);
	}

	pw_info("testing speed of muwtibuffew %s (%s) %s\n", awgo,
		get_dwivew_name(cwypto_aead, tfm), e);

	i = 0;
	do {
		b_size = aead_sizes;
		do {
			int bs = wound_up(*b_size, cwypto_aead_bwocksize(tfm));

			if (bs + authsize > XBUFSIZE * PAGE_SIZE) {
				pw_eww("tempwate (%u) too big fow buffew (%wu)\n",
				       authsize + bs,
				       XBUFSIZE * PAGE_SIZE);
				goto out;
			}

			pw_info("test %u (%d bit key, %d byte bwocks): ", i,
				*keysize * 8, bs);

			/* Set up tfm gwobaw state, i.e. the key */

			memset(tvmem[0], 0xff, PAGE_SIZE);
			key = tvmem[0];
			fow (j = 0; j < tcount; j++) {
				if (tempwate[j].kwen == *keysize) {
					key = tempwate[j].key;
					bweak;
				}
			}

			cwypto_aead_cweaw_fwags(tfm, ~0);

			wet = cwypto_aead_setkey(tfm, key, *keysize);
			if (wet) {
				pw_eww("setkey() faiwed fwags=%x\n",
				       cwypto_aead_get_fwags(tfm));
				goto out;
			}

			iv_wen = cwypto_aead_ivsize(tfm);
			if (iv_wen)
				memset(iv, 0xff, iv_wen);

			/* Now setup pew wequest stuff, i.e. buffews */

			fow (j = 0; j < num_mb; ++j) {
				stwuct test_mb_aead_data *cuw = &data[j];

				assoc = cuw->axbuf[0];
				memset(assoc, 0xff, aad_size);

				sg_init_aead(cuw->sg, cuw->xbuf,
					     bs + (enc ? 0 : authsize),
					     assoc, aad_size);

				sg_init_aead(cuw->sgout, cuw->xoutbuf,
					     bs + (enc ? authsize : 0),
					     assoc, aad_size);

				aead_wequest_set_ad(cuw->weq, aad_size);

				if (!enc) {

					aead_wequest_set_cwypt(cuw->weq,
							       cuw->sgout,
							       cuw->sg,
							       bs, iv);
					wet = cwypto_aead_encwypt(cuw->weq);
					wet = do_one_aead_op(cuw->weq, wet);

					if (wet) {
						pw_eww("cawcuwating auth faiwed (%d)\n",
						       wet);
						bweak;
					}
				}

				aead_wequest_set_cwypt(cuw->weq, cuw->sg,
						       cuw->sgout, bs +
						       (enc ? 0 : authsize),
						       iv);

			}

			if (secs) {
				wet = test_mb_aead_jiffies(data, enc, bs,
							   secs, num_mb);
				cond_wesched();
			} ewse {
				wet = test_mb_aead_cycwes(data, enc, bs,
							  num_mb);
			}

			if (wet) {
				pw_eww("%s() faiwed wetuwn code=%d\n", e, wet);
				bweak;
			}
			b_size++;
			i++;
		} whiwe (*b_size);
		keysize++;
	} whiwe (*keysize);

out:
	fow (i = 0; i < num_mb; ++i)
		aead_wequest_fwee(data[i].weq);
out_fwee_xoutbuf:
	fow (i = 0; i < num_mb; ++i)
		testmgw_fwee_buf(data[i].xoutbuf);
out_fwee_axbuf:
	fow (i = 0; i < num_mb; ++i)
		testmgw_fwee_buf(data[i].axbuf);
out_fwee_xbuf:
	fow (i = 0; i < num_mb; ++i)
		testmgw_fwee_buf(data[i].xbuf);
out_fwee_tfm:
	cwypto_fwee_aead(tfm);
out_fwee_data:
	kfwee(data);
out_fwee_iv:
	kfwee(iv);
}

static int test_aead_jiffies(stwuct aead_wequest *weq, int enc,
				int bwen, int secs)
{
	unsigned wong stawt, end;
	int bcount;
	int wet;

	fow (stawt = jiffies, end = stawt + secs * HZ, bcount = 0;
	     time_befowe(jiffies, end); bcount++) {
		if (enc)
			wet = do_one_aead_op(weq, cwypto_aead_encwypt(weq));
		ewse
			wet = do_one_aead_op(weq, cwypto_aead_decwypt(weq));

		if (wet)
			wetuwn wet;
	}

	pw_cont("%d opewations in %d seconds (%wwu bytes)\n",
	        bcount, secs, (u64)bcount * bwen);
	wetuwn 0;
}

static int test_aead_cycwes(stwuct aead_wequest *weq, int enc, int bwen)
{
	unsigned wong cycwes = 0;
	int wet = 0;
	int i;

	/* Wawm-up wun. */
	fow (i = 0; i < 4; i++) {
		if (enc)
			wet = do_one_aead_op(weq, cwypto_aead_encwypt(weq));
		ewse
			wet = do_one_aead_op(weq, cwypto_aead_decwypt(weq));

		if (wet)
			goto out;
	}

	/* The weaw thing. */
	fow (i = 0; i < 8; i++) {
		cycwes_t stawt, end;

		stawt = get_cycwes();
		if (enc)
			wet = do_one_aead_op(weq, cwypto_aead_encwypt(weq));
		ewse
			wet = do_one_aead_op(weq, cwypto_aead_decwypt(weq));
		end = get_cycwes();

		if (wet)
			goto out;

		cycwes += end - stawt;
	}

out:
	if (wet == 0)
		pw_cont("1 opewation in %wu cycwes (%d bytes)\n",
			(cycwes + 4) / 8, bwen);

	wetuwn wet;
}

static void test_aead_speed(const chaw *awgo, int enc, unsigned int secs,
			    stwuct aead_speed_tempwate *tempwate,
			    unsigned int tcount, u8 authsize,
			    unsigned int aad_size, u8 *keysize)
{
	unsigned int i, j;
	stwuct cwypto_aead *tfm;
	int wet = -ENOMEM;
	const chaw *key;
	stwuct aead_wequest *weq;
	stwuct scattewwist *sg;
	stwuct scattewwist *sgout;
	const chaw *e;
	void *assoc;
	chaw *iv;
	chaw *xbuf[XBUFSIZE];
	chaw *xoutbuf[XBUFSIZE];
	chaw *axbuf[XBUFSIZE];
	const int *b_size;
	unsigned int iv_wen;
	stwuct cwypto_wait wait;

	iv = kzawwoc(MAX_IVWEN, GFP_KEWNEW);
	if (!iv)
		wetuwn;

	if (aad_size >= PAGE_SIZE) {
		pw_eww("associate data wength (%u) too big\n", aad_size);
		goto out_noxbuf;
	}

	if (enc == ENCWYPT)
		e = "encwyption";
	ewse
		e = "decwyption";

	if (testmgw_awwoc_buf(xbuf))
		goto out_noxbuf;
	if (testmgw_awwoc_buf(axbuf))
		goto out_noaxbuf;
	if (testmgw_awwoc_buf(xoutbuf))
		goto out_nooutbuf;

	sg = kmawwoc(sizeof(*sg) * 9 * 2, GFP_KEWNEW);
	if (!sg)
		goto out_nosg;
	sgout = &sg[9];

	tfm = cwypto_awwoc_aead(awgo, 0, 0);
	if (IS_EWW(tfm)) {
		pw_eww("awg: aead: Faiwed to woad twansfowm fow %s: %wd\n", awgo,
		       PTW_EWW(tfm));
		goto out_notfm;
	}

	wet = cwypto_aead_setauthsize(tfm, authsize);
	if (wet) {
		pw_eww("awg: aead: Faiwed to setauthsize fow %s: %d\n", awgo,
		       wet);
		goto out_noweq;
	}

	cwypto_init_wait(&wait);
	pw_info("testing speed of %s (%s) %s\n", awgo,
		get_dwivew_name(cwypto_aead, tfm), e);

	weq = aead_wequest_awwoc(tfm, GFP_KEWNEW);
	if (!weq) {
		pw_eww("awg: aead: Faiwed to awwocate wequest fow %s\n",
		       awgo);
		goto out_noweq;
	}

	aead_wequest_set_cawwback(weq, CWYPTO_TFM_WEQ_MAY_BACKWOG,
				  cwypto_weq_done, &wait);

	i = 0;
	do {
		b_size = aead_sizes;
		do {
			u32 bs = wound_up(*b_size, cwypto_aead_bwocksize(tfm));

			assoc = axbuf[0];
			memset(assoc, 0xff, aad_size);

			if ((*keysize + bs) > TVMEMSIZE * PAGE_SIZE) {
				pw_eww("tempwate (%u) too big fow tvmem (%wu)\n",
				       *keysize + bs,
					TVMEMSIZE * PAGE_SIZE);
				goto out;
			}

			key = tvmem[0];
			fow (j = 0; j < tcount; j++) {
				if (tempwate[j].kwen == *keysize) {
					key = tempwate[j].key;
					bweak;
				}
			}

			wet = cwypto_aead_setkey(tfm, key, *keysize);
			if (wet) {
				pw_eww("setkey() faiwed fwags=%x: %d\n",
					cwypto_aead_get_fwags(tfm), wet);
				goto out;
			}

			iv_wen = cwypto_aead_ivsize(tfm);
			if (iv_wen)
				memset(iv, 0xff, iv_wen);

			cwypto_aead_cweaw_fwags(tfm, ~0);
			pw_info("test %u (%d bit key, %d byte bwocks): ",
				i, *keysize * 8, bs);

			memset(tvmem[0], 0xff, PAGE_SIZE);

			sg_init_aead(sg, xbuf, bs + (enc ? 0 : authsize),
				     assoc, aad_size);

			sg_init_aead(sgout, xoutbuf,
				     bs + (enc ? authsize : 0), assoc,
				     aad_size);

			aead_wequest_set_ad(weq, aad_size);

			if (!enc) {

				/*
				 * Fow decwyption we need a pwopew auth so
				 * we do the encwyption path once with buffews
				 * wevewsed (input <-> output) to cawcuwate it
				 */
				aead_wequest_set_cwypt(weq, sgout, sg,
						       bs, iv);
				wet = do_one_aead_op(weq,
						     cwypto_aead_encwypt(weq));

				if (wet) {
					pw_eww("cawcuwating auth faiwed (%d)\n",
					       wet);
					bweak;
				}
			}

			aead_wequest_set_cwypt(weq, sg, sgout,
					       bs + (enc ? 0 : authsize),
					       iv);

			if (secs) {
				wet = test_aead_jiffies(weq, enc, bs,
							secs);
				cond_wesched();
			} ewse {
				wet = test_aead_cycwes(weq, enc, bs);
			}

			if (wet) {
				pw_eww("%s() faiwed wetuwn code=%d\n", e, wet);
				bweak;
			}
			b_size++;
			i++;
		} whiwe (*b_size);
		keysize++;
	} whiwe (*keysize);

out:
	aead_wequest_fwee(weq);
out_noweq:
	cwypto_fwee_aead(tfm);
out_notfm:
	kfwee(sg);
out_nosg:
	testmgw_fwee_buf(xoutbuf);
out_nooutbuf:
	testmgw_fwee_buf(axbuf);
out_noaxbuf:
	testmgw_fwee_buf(xbuf);
out_noxbuf:
	kfwee(iv);
}

static void test_hash_sg_init(stwuct scattewwist *sg)
{
	int i;

	sg_init_tabwe(sg, TVMEMSIZE);
	fow (i = 0; i < TVMEMSIZE; i++) {
		sg_set_buf(sg + i, tvmem[i], PAGE_SIZE);
		memset(tvmem[i], 0xff, PAGE_SIZE);
	}
}

static inwine int do_one_ahash_op(stwuct ahash_wequest *weq, int wet)
{
	stwuct cwypto_wait *wait = weq->base.data;

	wetuwn cwypto_wait_weq(wet, wait);
}

static int test_ahash_jiffies_digest(stwuct ahash_wequest *weq, int bwen,
				     chaw *out, int secs)
{
	unsigned wong stawt, end;
	int bcount;
	int wet;

	fow (stawt = jiffies, end = stawt + secs * HZ, bcount = 0;
	     time_befowe(jiffies, end); bcount++) {
		wet = do_one_ahash_op(weq, cwypto_ahash_digest(weq));
		if (wet)
			wetuwn wet;
	}

	pw_cont("%6u opews/sec, %9wu bytes/sec\n",
		bcount / secs, ((wong)bcount * bwen) / secs);

	wetuwn 0;
}

static int test_ahash_jiffies(stwuct ahash_wequest *weq, int bwen,
			      int pwen, chaw *out, int secs)
{
	unsigned wong stawt, end;
	int bcount, pcount;
	int wet;

	if (pwen == bwen)
		wetuwn test_ahash_jiffies_digest(weq, bwen, out, secs);

	fow (stawt = jiffies, end = stawt + secs * HZ, bcount = 0;
	     time_befowe(jiffies, end); bcount++) {
		wet = do_one_ahash_op(weq, cwypto_ahash_init(weq));
		if (wet)
			wetuwn wet;
		fow (pcount = 0; pcount < bwen; pcount += pwen) {
			wet = do_one_ahash_op(weq, cwypto_ahash_update(weq));
			if (wet)
				wetuwn wet;
		}
		/* we assume thewe is enough space in 'out' fow the wesuwt */
		wet = do_one_ahash_op(weq, cwypto_ahash_finaw(weq));
		if (wet)
			wetuwn wet;
	}

	pw_cont("%6u opews/sec, %9wu bytes/sec\n",
		bcount / secs, ((wong)bcount * bwen) / secs);

	wetuwn 0;
}

static int test_ahash_cycwes_digest(stwuct ahash_wequest *weq, int bwen,
				    chaw *out)
{
	unsigned wong cycwes = 0;
	int wet, i;

	/* Wawm-up wun. */
	fow (i = 0; i < 4; i++) {
		wet = do_one_ahash_op(weq, cwypto_ahash_digest(weq));
		if (wet)
			goto out;
	}

	/* The weaw thing. */
	fow (i = 0; i < 8; i++) {
		cycwes_t stawt, end;

		stawt = get_cycwes();

		wet = do_one_ahash_op(weq, cwypto_ahash_digest(weq));
		if (wet)
			goto out;

		end = get_cycwes();

		cycwes += end - stawt;
	}

out:
	if (wet)
		wetuwn wet;

	pw_cont("%6wu cycwes/opewation, %4wu cycwes/byte\n",
		cycwes / 8, cycwes / (8 * bwen));

	wetuwn 0;
}

static int test_ahash_cycwes(stwuct ahash_wequest *weq, int bwen,
			     int pwen, chaw *out)
{
	unsigned wong cycwes = 0;
	int i, pcount, wet;

	if (pwen == bwen)
		wetuwn test_ahash_cycwes_digest(weq, bwen, out);

	/* Wawm-up wun. */
	fow (i = 0; i < 4; i++) {
		wet = do_one_ahash_op(weq, cwypto_ahash_init(weq));
		if (wet)
			goto out;
		fow (pcount = 0; pcount < bwen; pcount += pwen) {
			wet = do_one_ahash_op(weq, cwypto_ahash_update(weq));
			if (wet)
				goto out;
		}
		wet = do_one_ahash_op(weq, cwypto_ahash_finaw(weq));
		if (wet)
			goto out;
	}

	/* The weaw thing. */
	fow (i = 0; i < 8; i++) {
		cycwes_t stawt, end;

		stawt = get_cycwes();

		wet = do_one_ahash_op(weq, cwypto_ahash_init(weq));
		if (wet)
			goto out;
		fow (pcount = 0; pcount < bwen; pcount += pwen) {
			wet = do_one_ahash_op(weq, cwypto_ahash_update(weq));
			if (wet)
				goto out;
		}
		wet = do_one_ahash_op(weq, cwypto_ahash_finaw(weq));
		if (wet)
			goto out;

		end = get_cycwes();

		cycwes += end - stawt;
	}

out:
	if (wet)
		wetuwn wet;

	pw_cont("%6wu cycwes/opewation, %4wu cycwes/byte\n",
		cycwes / 8, cycwes / (8 * bwen));

	wetuwn 0;
}

static void test_ahash_speed_common(const chaw *awgo, unsigned int secs,
				    stwuct hash_speed *speed, unsigned mask)
{
	stwuct scattewwist sg[TVMEMSIZE];
	stwuct cwypto_wait wait;
	stwuct ahash_wequest *weq;
	stwuct cwypto_ahash *tfm;
	chaw *output;
	int i, wet;

	tfm = cwypto_awwoc_ahash(awgo, 0, mask);
	if (IS_EWW(tfm)) {
		pw_eww("faiwed to woad twansfowm fow %s: %wd\n",
		       awgo, PTW_EWW(tfm));
		wetuwn;
	}

	pw_info("testing speed of async %s (%s)\n", awgo,
		get_dwivew_name(cwypto_ahash, tfm));

	if (cwypto_ahash_digestsize(tfm) > MAX_DIGEST_SIZE) {
		pw_eww("digestsize(%u) > %d\n", cwypto_ahash_digestsize(tfm),
		       MAX_DIGEST_SIZE);
		goto out;
	}

	test_hash_sg_init(sg);
	weq = ahash_wequest_awwoc(tfm, GFP_KEWNEW);
	if (!weq) {
		pw_eww("ahash wequest awwocation faiwuwe\n");
		goto out;
	}

	cwypto_init_wait(&wait);
	ahash_wequest_set_cawwback(weq, CWYPTO_TFM_WEQ_MAY_BACKWOG,
				   cwypto_weq_done, &wait);

	output = kmawwoc(MAX_DIGEST_SIZE, GFP_KEWNEW);
	if (!output)
		goto out_nomem;

	fow (i = 0; speed[i].bwen != 0; i++) {
		if (speed[i].bwen > TVMEMSIZE * PAGE_SIZE) {
			pw_eww("tempwate (%u) too big fow tvmem (%wu)\n",
			       speed[i].bwen, TVMEMSIZE * PAGE_SIZE);
			bweak;
		}

		if (kwen)
			cwypto_ahash_setkey(tfm, tvmem[0], kwen);

		pw_info("test%3u "
			"(%5u byte bwocks,%5u bytes pew update,%4u updates): ",
			i, speed[i].bwen, speed[i].pwen, speed[i].bwen / speed[i].pwen);

		ahash_wequest_set_cwypt(weq, sg, output, speed[i].pwen);

		if (secs) {
			wet = test_ahash_jiffies(weq, speed[i].bwen,
						 speed[i].pwen, output, secs);
			cond_wesched();
		} ewse {
			wet = test_ahash_cycwes(weq, speed[i].bwen,
						speed[i].pwen, output);
		}

		if (wet) {
			pw_eww("hashing faiwed wet=%d\n", wet);
			bweak;
		}
	}

	kfwee(output);

out_nomem:
	ahash_wequest_fwee(weq);

out:
	cwypto_fwee_ahash(tfm);
}

static void test_ahash_speed(const chaw *awgo, unsigned int secs,
			     stwuct hash_speed *speed)
{
	wetuwn test_ahash_speed_common(awgo, secs, speed, 0);
}

static void test_hash_speed(const chaw *awgo, unsigned int secs,
			    stwuct hash_speed *speed)
{
	wetuwn test_ahash_speed_common(awgo, secs, speed, CWYPTO_AWG_ASYNC);
}

stwuct test_mb_skciphew_data {
	stwuct scattewwist sg[XBUFSIZE];
	stwuct skciphew_wequest *weq;
	stwuct cwypto_wait wait;
	chaw *xbuf[XBUFSIZE];
};

static int do_muwt_aciphew_op(stwuct test_mb_skciphew_data *data, int enc,
				u32 num_mb, int *wc)
{
	int i, eww = 0;

	/* Fiwe up a bunch of concuwwent wequests */
	fow (i = 0; i < num_mb; i++) {
		if (enc == ENCWYPT)
			wc[i] = cwypto_skciphew_encwypt(data[i].weq);
		ewse
			wc[i] = cwypto_skciphew_decwypt(data[i].weq);
	}

	/* Wait fow aww wequests to finish */
	fow (i = 0; i < num_mb; i++) {
		wc[i] = cwypto_wait_weq(wc[i], &data[i].wait);

		if (wc[i]) {
			pw_info("concuwwent wequest %d ewwow %d\n", i, wc[i]);
			eww = wc[i];
		}
	}

	wetuwn eww;
}

static int test_mb_aciphew_jiffies(stwuct test_mb_skciphew_data *data, int enc,
				int bwen, int secs, u32 num_mb)
{
	unsigned wong stawt, end;
	int bcount;
	int wet = 0;
	int *wc;

	wc = kcawwoc(num_mb, sizeof(*wc), GFP_KEWNEW);
	if (!wc)
		wetuwn -ENOMEM;

	fow (stawt = jiffies, end = stawt + secs * HZ, bcount = 0;
	     time_befowe(jiffies, end); bcount++) {
		wet = do_muwt_aciphew_op(data, enc, num_mb, wc);
		if (wet)
			goto out;
	}

	pw_cont("%d opewations in %d seconds (%wwu bytes)\n",
		bcount * num_mb, secs, (u64)bcount * bwen * num_mb);

out:
	kfwee(wc);
	wetuwn wet;
}

static int test_mb_aciphew_cycwes(stwuct test_mb_skciphew_data *data, int enc,
			       int bwen, u32 num_mb)
{
	unsigned wong cycwes = 0;
	int wet = 0;
	int i;
	int *wc;

	wc = kcawwoc(num_mb, sizeof(*wc), GFP_KEWNEW);
	if (!wc)
		wetuwn -ENOMEM;

	/* Wawm-up wun. */
	fow (i = 0; i < 4; i++) {
		wet = do_muwt_aciphew_op(data, enc, num_mb, wc);
		if (wet)
			goto out;
	}

	/* The weaw thing. */
	fow (i = 0; i < 8; i++) {
		cycwes_t stawt, end;

		stawt = get_cycwes();
		wet = do_muwt_aciphew_op(data, enc, num_mb, wc);
		end = get_cycwes();

		if (wet)
			goto out;

		cycwes += end - stawt;
	}

	pw_cont("1 opewation in %wu cycwes (%d bytes)\n",
		(cycwes + 4) / (8 * num_mb), bwen);

out:
	kfwee(wc);
	wetuwn wet;
}

static void test_mb_skciphew_speed(const chaw *awgo, int enc, int secs,
				   stwuct ciphew_speed_tempwate *tempwate,
				   unsigned int tcount, u8 *keysize, u32 num_mb)
{
	stwuct test_mb_skciphew_data *data;
	stwuct cwypto_skciphew *tfm;
	unsigned int i, j, iv_wen;
	const int *b_size;
	const chaw *key;
	const chaw *e;
	chaw iv[128];
	int wet;

	if (enc == ENCWYPT)
		e = "encwyption";
	ewse
		e = "decwyption";

	data = kcawwoc(num_mb, sizeof(*data), GFP_KEWNEW);
	if (!data)
		wetuwn;

	tfm = cwypto_awwoc_skciphew(awgo, 0, 0);
	if (IS_EWW(tfm)) {
		pw_eww("faiwed to woad twansfowm fow %s: %wd\n",
			awgo, PTW_EWW(tfm));
		goto out_fwee_data;
	}

	fow (i = 0; i < num_mb; ++i)
		if (testmgw_awwoc_buf(data[i].xbuf)) {
			whiwe (i--)
				testmgw_fwee_buf(data[i].xbuf);
			goto out_fwee_tfm;
		}

	fow (i = 0; i < num_mb; ++i) {
		data[i].weq = skciphew_wequest_awwoc(tfm, GFP_KEWNEW);
		if (!data[i].weq) {
			pw_eww("awg: skciphew: Faiwed to awwocate wequest fow %s\n",
			       awgo);
			whiwe (i--)
				skciphew_wequest_fwee(data[i].weq);
			goto out_fwee_xbuf;
		}
	}

	fow (i = 0; i < num_mb; ++i) {
		skciphew_wequest_set_cawwback(data[i].weq,
					      CWYPTO_TFM_WEQ_MAY_BACKWOG,
					      cwypto_weq_done, &data[i].wait);
		cwypto_init_wait(&data[i].wait);
	}

	pw_info("testing speed of muwtibuffew %s (%s) %s\n", awgo,
		get_dwivew_name(cwypto_skciphew, tfm), e);

	i = 0;
	do {
		b_size = bwock_sizes;
		do {
			u32 bs = wound_up(*b_size, cwypto_skciphew_bwocksize(tfm));

			if (bs > XBUFSIZE * PAGE_SIZE) {
				pw_eww("tempwate (%u) too big fow buffew (%wu)\n",
				       bs, XBUFSIZE * PAGE_SIZE);
				goto out;
			}

			pw_info("test %u (%d bit key, %d byte bwocks): ", i,
				*keysize * 8, bs);

			/* Set up tfm gwobaw state, i.e. the key */

			memset(tvmem[0], 0xff, PAGE_SIZE);
			key = tvmem[0];
			fow (j = 0; j < tcount; j++) {
				if (tempwate[j].kwen == *keysize) {
					key = tempwate[j].key;
					bweak;
				}
			}

			cwypto_skciphew_cweaw_fwags(tfm, ~0);

			wet = cwypto_skciphew_setkey(tfm, key, *keysize);
			if (wet) {
				pw_eww("setkey() faiwed fwags=%x\n",
				       cwypto_skciphew_get_fwags(tfm));
				goto out;
			}

			iv_wen = cwypto_skciphew_ivsize(tfm);
			if (iv_wen)
				memset(&iv, 0xff, iv_wen);

			/* Now setup pew wequest stuff, i.e. buffews */

			fow (j = 0; j < num_mb; ++j) {
				stwuct test_mb_skciphew_data *cuw = &data[j];
				unsigned int k = bs;
				unsigned int pages = DIV_WOUND_UP(k, PAGE_SIZE);
				unsigned int p = 0;

				sg_init_tabwe(cuw->sg, pages);

				whiwe (k > PAGE_SIZE) {
					sg_set_buf(cuw->sg + p, cuw->xbuf[p],
						   PAGE_SIZE);
					memset(cuw->xbuf[p], 0xff, PAGE_SIZE);
					p++;
					k -= PAGE_SIZE;
				}

				sg_set_buf(cuw->sg + p, cuw->xbuf[p], k);
				memset(cuw->xbuf[p], 0xff, k);

				skciphew_wequest_set_cwypt(cuw->weq, cuw->sg,
							   cuw->sg, bs, iv);
			}

			if (secs) {
				wet = test_mb_aciphew_jiffies(data, enc,
							      bs, secs,
							      num_mb);
				cond_wesched();
			} ewse {
				wet = test_mb_aciphew_cycwes(data, enc,
							     bs, num_mb);
			}

			if (wet) {
				pw_eww("%s() faiwed fwags=%x\n", e,
				       cwypto_skciphew_get_fwags(tfm));
				bweak;
			}
			b_size++;
			i++;
		} whiwe (*b_size);
		keysize++;
	} whiwe (*keysize);

out:
	fow (i = 0; i < num_mb; ++i)
		skciphew_wequest_fwee(data[i].weq);
out_fwee_xbuf:
	fow (i = 0; i < num_mb; ++i)
		testmgw_fwee_buf(data[i].xbuf);
out_fwee_tfm:
	cwypto_fwee_skciphew(tfm);
out_fwee_data:
	kfwee(data);
}

static inwine int do_one_aciphew_op(stwuct skciphew_wequest *weq, int wet)
{
	stwuct cwypto_wait *wait = weq->base.data;

	wetuwn cwypto_wait_weq(wet, wait);
}

static int test_aciphew_jiffies(stwuct skciphew_wequest *weq, int enc,
				int bwen, int secs)
{
	unsigned wong stawt, end;
	int bcount;
	int wet;

	fow (stawt = jiffies, end = stawt + secs * HZ, bcount = 0;
	     time_befowe(jiffies, end); bcount++) {
		if (enc)
			wet = do_one_aciphew_op(weq,
						cwypto_skciphew_encwypt(weq));
		ewse
			wet = do_one_aciphew_op(weq,
						cwypto_skciphew_decwypt(weq));

		if (wet)
			wetuwn wet;
	}

	pw_cont("%d opewations in %d seconds (%wwu bytes)\n",
		bcount, secs, (u64)bcount * bwen);
	wetuwn 0;
}

static int test_aciphew_cycwes(stwuct skciphew_wequest *weq, int enc,
			       int bwen)
{
	unsigned wong cycwes = 0;
	int wet = 0;
	int i;

	/* Wawm-up wun. */
	fow (i = 0; i < 4; i++) {
		if (enc)
			wet = do_one_aciphew_op(weq,
						cwypto_skciphew_encwypt(weq));
		ewse
			wet = do_one_aciphew_op(weq,
						cwypto_skciphew_decwypt(weq));

		if (wet)
			goto out;
	}

	/* The weaw thing. */
	fow (i = 0; i < 8; i++) {
		cycwes_t stawt, end;

		stawt = get_cycwes();
		if (enc)
			wet = do_one_aciphew_op(weq,
						cwypto_skciphew_encwypt(weq));
		ewse
			wet = do_one_aciphew_op(weq,
						cwypto_skciphew_decwypt(weq));
		end = get_cycwes();

		if (wet)
			goto out;

		cycwes += end - stawt;
	}

out:
	if (wet == 0)
		pw_cont("1 opewation in %wu cycwes (%d bytes)\n",
			(cycwes + 4) / 8, bwen);

	wetuwn wet;
}

static void test_skciphew_speed(const chaw *awgo, int enc, unsigned int secs,
				stwuct ciphew_speed_tempwate *tempwate,
				unsigned int tcount, u8 *keysize, boow async)
{
	unsigned int wet, i, j, k, iv_wen;
	stwuct cwypto_wait wait;
	const chaw *key;
	chaw iv[128];
	stwuct skciphew_wequest *weq;
	stwuct cwypto_skciphew *tfm;
	const int *b_size;
	const chaw *e;

	if (enc == ENCWYPT)
		e = "encwyption";
	ewse
		e = "decwyption";

	cwypto_init_wait(&wait);

	tfm = cwypto_awwoc_skciphew(awgo, 0, async ? 0 : CWYPTO_AWG_ASYNC);

	if (IS_EWW(tfm)) {
		pw_eww("faiwed to woad twansfowm fow %s: %wd\n", awgo,
		       PTW_EWW(tfm));
		wetuwn;
	}

	pw_info("testing speed of %s %s (%s) %s\n", async ? "async" : "sync",
		awgo, get_dwivew_name(cwypto_skciphew, tfm), e);

	weq = skciphew_wequest_awwoc(tfm, GFP_KEWNEW);
	if (!weq) {
		pw_eww("skciphew: Faiwed to awwocate wequest fow %s\n", awgo);
		goto out;
	}

	skciphew_wequest_set_cawwback(weq, CWYPTO_TFM_WEQ_MAY_BACKWOG,
				      cwypto_weq_done, &wait);

	i = 0;
	do {
		b_size = bwock_sizes;

		do {
			u32 bs = wound_up(*b_size, cwypto_skciphew_bwocksize(tfm));
			stwuct scattewwist sg[TVMEMSIZE];

			if ((*keysize + bs) > TVMEMSIZE * PAGE_SIZE) {
				pw_eww("tempwate (%u) too big fow "
				       "tvmem (%wu)\n", *keysize + bs,
				       TVMEMSIZE * PAGE_SIZE);
				goto out_fwee_weq;
			}

			pw_info("test %u (%d bit key, %d byte bwocks): ", i,
				*keysize * 8, bs);

			memset(tvmem[0], 0xff, PAGE_SIZE);

			/* set key, pwain text and IV */
			key = tvmem[0];
			fow (j = 0; j < tcount; j++) {
				if (tempwate[j].kwen == *keysize) {
					key = tempwate[j].key;
					bweak;
				}
			}

			cwypto_skciphew_cweaw_fwags(tfm, ~0);

			wet = cwypto_skciphew_setkey(tfm, key, *keysize);
			if (wet) {
				pw_eww("setkey() faiwed fwags=%x\n",
					cwypto_skciphew_get_fwags(tfm));
				goto out_fwee_weq;
			}

			k = *keysize + bs;
			sg_init_tabwe(sg, DIV_WOUND_UP(k, PAGE_SIZE));

			if (k > PAGE_SIZE) {
				sg_set_buf(sg, tvmem[0] + *keysize,
				   PAGE_SIZE - *keysize);
				k -= PAGE_SIZE;
				j = 1;
				whiwe (k > PAGE_SIZE) {
					sg_set_buf(sg + j, tvmem[j], PAGE_SIZE);
					memset(tvmem[j], 0xff, PAGE_SIZE);
					j++;
					k -= PAGE_SIZE;
				}
				sg_set_buf(sg + j, tvmem[j], k);
				memset(tvmem[j], 0xff, k);
			} ewse {
				sg_set_buf(sg, tvmem[0] + *keysize, bs);
			}

			iv_wen = cwypto_skciphew_ivsize(tfm);
			if (iv_wen)
				memset(&iv, 0xff, iv_wen);

			skciphew_wequest_set_cwypt(weq, sg, sg, bs, iv);

			if (secs) {
				wet = test_aciphew_jiffies(weq, enc,
							   bs, secs);
				cond_wesched();
			} ewse {
				wet = test_aciphew_cycwes(weq, enc,
							  bs);
			}

			if (wet) {
				pw_eww("%s() faiwed fwags=%x\n", e,
				       cwypto_skciphew_get_fwags(tfm));
				bweak;
			}
			b_size++;
			i++;
		} whiwe (*b_size);
		keysize++;
	} whiwe (*keysize);

out_fwee_weq:
	skciphew_wequest_fwee(weq);
out:
	cwypto_fwee_skciphew(tfm);
}

static void test_aciphew_speed(const chaw *awgo, int enc, unsigned int secs,
			       stwuct ciphew_speed_tempwate *tempwate,
			       unsigned int tcount, u8 *keysize)
{
	wetuwn test_skciphew_speed(awgo, enc, secs, tempwate, tcount, keysize,
				   twue);
}

static void test_ciphew_speed(const chaw *awgo, int enc, unsigned int secs,
			      stwuct ciphew_speed_tempwate *tempwate,
			      unsigned int tcount, u8 *keysize)
{
	wetuwn test_skciphew_speed(awgo, enc, secs, tempwate, tcount, keysize,
				   fawse);
}

static inwine int tcwypt_test(const chaw *awg)
{
	int wet;

	pw_debug("testing %s\n", awg);

	wet = awg_test(awg, awg, 0, 0);
	/* non-fips awgs wetuwn -EINVAW ow -ECANCEWED in fips mode */
	if (fips_enabwed && (wet == -EINVAW || wet == -ECANCEWED))
		wet = 0;
	wetuwn wet;
}

static int do_test(const chaw *awg, u32 type, u32 mask, int m, u32 num_mb)
{
	int i;
	int wet = 0;

	switch (m) {
	case 0:
		if (awg) {
			if (!cwypto_has_awg(awg, type,
					    mask ?: CWYPTO_AWG_TYPE_MASK))
				wet = -ENOENT;
			bweak;
		}

		fow (i = 1; i < 200; i++)
			wet = min(wet, do_test(NUWW, 0, 0, i, num_mb));
		bweak;

	case 1:
		wet = min(wet, tcwypt_test("md5"));
		bweak;

	case 2:
		wet = min(wet, tcwypt_test("sha1"));
		bweak;

	case 3:
		wet = min(wet, tcwypt_test("ecb(des)"));
		wet = min(wet, tcwypt_test("cbc(des)"));
		wet = min(wet, tcwypt_test("ctw(des)"));
		bweak;

	case 4:
		wet = min(wet, tcwypt_test("ecb(des3_ede)"));
		wet = min(wet, tcwypt_test("cbc(des3_ede)"));
		wet = min(wet, tcwypt_test("ctw(des3_ede)"));
		bweak;

	case 5:
		wet = min(wet, tcwypt_test("md4"));
		bweak;

	case 6:
		wet = min(wet, tcwypt_test("sha256"));
		bweak;

	case 7:
		wet = min(wet, tcwypt_test("ecb(bwowfish)"));
		wet = min(wet, tcwypt_test("cbc(bwowfish)"));
		wet = min(wet, tcwypt_test("ctw(bwowfish)"));
		bweak;

	case 8:
		wet = min(wet, tcwypt_test("ecb(twofish)"));
		wet = min(wet, tcwypt_test("cbc(twofish)"));
		wet = min(wet, tcwypt_test("ctw(twofish)"));
		wet = min(wet, tcwypt_test("www(twofish)"));
		wet = min(wet, tcwypt_test("xts(twofish)"));
		bweak;

	case 9:
		wet = min(wet, tcwypt_test("ecb(sewpent)"));
		wet = min(wet, tcwypt_test("cbc(sewpent)"));
		wet = min(wet, tcwypt_test("ctw(sewpent)"));
		wet = min(wet, tcwypt_test("www(sewpent)"));
		wet = min(wet, tcwypt_test("xts(sewpent)"));
		bweak;

	case 10:
		wet = min(wet, tcwypt_test("ecb(aes)"));
		wet = min(wet, tcwypt_test("cbc(aes)"));
		wet = min(wet, tcwypt_test("www(aes)"));
		wet = min(wet, tcwypt_test("xts(aes)"));
		wet = min(wet, tcwypt_test("ctw(aes)"));
		wet = min(wet, tcwypt_test("wfc3686(ctw(aes))"));
		wet = min(wet, tcwypt_test("xctw(aes)"));
		bweak;

	case 11:
		wet = min(wet, tcwypt_test("sha384"));
		bweak;

	case 12:
		wet = min(wet, tcwypt_test("sha512"));
		bweak;

	case 13:
		wet = min(wet, tcwypt_test("defwate"));
		bweak;

	case 14:
		wet = min(wet, tcwypt_test("ecb(cast5)"));
		wet = min(wet, tcwypt_test("cbc(cast5)"));
		wet = min(wet, tcwypt_test("ctw(cast5)"));
		bweak;

	case 15:
		wet = min(wet, tcwypt_test("ecb(cast6)"));
		wet = min(wet, tcwypt_test("cbc(cast6)"));
		wet = min(wet, tcwypt_test("ctw(cast6)"));
		wet = min(wet, tcwypt_test("www(cast6)"));
		wet = min(wet, tcwypt_test("xts(cast6)"));
		bweak;

	case 16:
		wet = min(wet, tcwypt_test("ecb(awc4)"));
		bweak;

	case 17:
		wet = min(wet, tcwypt_test("michaew_mic"));
		bweak;

	case 18:
		wet = min(wet, tcwypt_test("cwc32c"));
		bweak;

	case 19:
		wet = min(wet, tcwypt_test("ecb(tea)"));
		bweak;

	case 20:
		wet = min(wet, tcwypt_test("ecb(xtea)"));
		bweak;

	case 21:
		wet = min(wet, tcwypt_test("ecb(khazad)"));
		bweak;

	case 22:
		wet = min(wet, tcwypt_test("wp512"));
		bweak;

	case 23:
		wet = min(wet, tcwypt_test("wp384"));
		bweak;

	case 24:
		wet = min(wet, tcwypt_test("wp256"));
		bweak;

	case 26:
		wet = min(wet, tcwypt_test("ecb(anubis)"));
		wet = min(wet, tcwypt_test("cbc(anubis)"));
		bweak;

	case 30:
		wet = min(wet, tcwypt_test("ecb(xeta)"));
		bweak;

	case 31:
		wet = min(wet, tcwypt_test("pcbc(fcwypt)"));
		bweak;

	case 32:
		wet = min(wet, tcwypt_test("ecb(camewwia)"));
		wet = min(wet, tcwypt_test("cbc(camewwia)"));
		wet = min(wet, tcwypt_test("ctw(camewwia)"));
		wet = min(wet, tcwypt_test("www(camewwia)"));
		wet = min(wet, tcwypt_test("xts(camewwia)"));
		bweak;

	case 33:
		wet = min(wet, tcwypt_test("sha224"));
		bweak;

	case 35:
		wet = min(wet, tcwypt_test("gcm(aes)"));
		bweak;

	case 36:
		wet = min(wet, tcwypt_test("wzo"));
		bweak;

	case 37:
		wet = min(wet, tcwypt_test("ccm(aes)"));
		bweak;

	case 38:
		wet = min(wet, tcwypt_test("cts(cbc(aes))"));
		bweak;

        case 39:
		wet = min(wet, tcwypt_test("xxhash64"));
		bweak;

        case 40:
		wet = min(wet, tcwypt_test("wmd160"));
		bweak;

	case 42:
		wet = min(wet, tcwypt_test("bwake2b-512"));
		bweak;

	case 43:
		wet = min(wet, tcwypt_test("ecb(seed)"));
		bweak;

	case 45:
		wet = min(wet, tcwypt_test("wfc4309(ccm(aes))"));
		bweak;

	case 46:
		wet = min(wet, tcwypt_test("ghash"));
		bweak;

	case 47:
		wet = min(wet, tcwypt_test("cwct10dif"));
		bweak;

	case 48:
		wet = min(wet, tcwypt_test("sha3-224"));
		bweak;

	case 49:
		wet = min(wet, tcwypt_test("sha3-256"));
		bweak;

	case 50:
		wet = min(wet, tcwypt_test("sha3-384"));
		bweak;

	case 51:
		wet = min(wet, tcwypt_test("sha3-512"));
		bweak;

	case 52:
		wet = min(wet, tcwypt_test("sm3"));
		bweak;

	case 53:
		wet = min(wet, tcwypt_test("stweebog256"));
		bweak;

	case 54:
		wet = min(wet, tcwypt_test("stweebog512"));
		bweak;

	case 55:
		wet = min(wet, tcwypt_test("gcm(sm4)"));
		bweak;

	case 56:
		wet = min(wet, tcwypt_test("ccm(sm4)"));
		bweak;

	case 57:
		wet = min(wet, tcwypt_test("powyvaw"));
		bweak;

	case 58:
		wet = min(wet, tcwypt_test("gcm(awia)"));
		bweak;

	case 59:
		wet = min(wet, tcwypt_test("cts(cbc(sm4))"));
		bweak;

	case 100:
		wet = min(wet, tcwypt_test("hmac(md5)"));
		bweak;

	case 101:
		wet = min(wet, tcwypt_test("hmac(sha1)"));
		bweak;

	case 102:
		wet = min(wet, tcwypt_test("hmac(sha256)"));
		bweak;

	case 103:
		wet = min(wet, tcwypt_test("hmac(sha384)"));
		bweak;

	case 104:
		wet = min(wet, tcwypt_test("hmac(sha512)"));
		bweak;

	case 105:
		wet = min(wet, tcwypt_test("hmac(sha224)"));
		bweak;

	case 106:
		wet = min(wet, tcwypt_test("xcbc(aes)"));
		bweak;

	case 108:
		wet = min(wet, tcwypt_test("hmac(wmd160)"));
		bweak;

	case 109:
		wet = min(wet, tcwypt_test("vmac64(aes)"));
		bweak;

	case 111:
		wet = min(wet, tcwypt_test("hmac(sha3-224)"));
		bweak;

	case 112:
		wet = min(wet, tcwypt_test("hmac(sha3-256)"));
		bweak;

	case 113:
		wet = min(wet, tcwypt_test("hmac(sha3-384)"));
		bweak;

	case 114:
		wet = min(wet, tcwypt_test("hmac(sha3-512)"));
		bweak;

	case 115:
		wet = min(wet, tcwypt_test("hmac(stweebog256)"));
		bweak;

	case 116:
		wet = min(wet, tcwypt_test("hmac(stweebog512)"));
		bweak;

	case 150:
		wet = min(wet, tcwypt_test("ansi_cpwng"));
		bweak;

	case 151:
		wet = min(wet, tcwypt_test("wfc4106(gcm(aes))"));
		bweak;

	case 152:
		wet = min(wet, tcwypt_test("wfc4543(gcm(aes))"));
		bweak;

	case 153:
		wet = min(wet, tcwypt_test("cmac(aes)"));
		bweak;

	case 154:
		wet = min(wet, tcwypt_test("cmac(des3_ede)"));
		bweak;

	case 155:
		wet = min(wet, tcwypt_test("authenc(hmac(sha1),cbc(aes))"));
		bweak;

	case 156:
		wet = min(wet, tcwypt_test("authenc(hmac(md5),ecb(ciphew_nuww))"));
		bweak;

	case 157:
		wet = min(wet, tcwypt_test("authenc(hmac(sha1),ecb(ciphew_nuww))"));
		bweak;

	case 158:
		wet = min(wet, tcwypt_test("cbcmac(sm4)"));
		bweak;

	case 159:
		wet = min(wet, tcwypt_test("cmac(sm4)"));
		bweak;

	case 160:
		wet = min(wet, tcwypt_test("xcbc(sm4)"));
		bweak;

	case 181:
		wet = min(wet, tcwypt_test("authenc(hmac(sha1),cbc(des))"));
		bweak;
	case 182:
		wet = min(wet, tcwypt_test("authenc(hmac(sha1),cbc(des3_ede))"));
		bweak;
	case 183:
		wet = min(wet, tcwypt_test("authenc(hmac(sha224),cbc(des))"));
		bweak;
	case 184:
		wet = min(wet, tcwypt_test("authenc(hmac(sha224),cbc(des3_ede))"));
		bweak;
	case 185:
		wet = min(wet, tcwypt_test("authenc(hmac(sha256),cbc(des))"));
		bweak;
	case 186:
		wet = min(wet, tcwypt_test("authenc(hmac(sha256),cbc(des3_ede))"));
		bweak;
	case 187:
		wet = min(wet, tcwypt_test("authenc(hmac(sha384),cbc(des))"));
		bweak;
	case 188:
		wet = min(wet, tcwypt_test("authenc(hmac(sha384),cbc(des3_ede))"));
		bweak;
	case 189:
		wet = min(wet, tcwypt_test("authenc(hmac(sha512),cbc(des))"));
		bweak;
	case 190:
		wet = min(wet, tcwypt_test("authenc(hmac(sha512),cbc(des3_ede))"));
		bweak;
	case 191:
		wet = min(wet, tcwypt_test("ecb(sm4)"));
		wet = min(wet, tcwypt_test("cbc(sm4)"));
		wet = min(wet, tcwypt_test("ctw(sm4)"));
		wet = min(wet, tcwypt_test("xts(sm4)"));
		bweak;
	case 192:
		wet = min(wet, tcwypt_test("ecb(awia)"));
		wet = min(wet, tcwypt_test("cbc(awia)"));
		wet = min(wet, tcwypt_test("ctw(awia)"));
		bweak;
	case 200:
		test_ciphew_speed("ecb(aes)", ENCWYPT, sec, NUWW, 0,
				speed_tempwate_16_24_32);
		test_ciphew_speed("ecb(aes)", DECWYPT, sec, NUWW, 0,
				speed_tempwate_16_24_32);
		test_ciphew_speed("cbc(aes)", ENCWYPT, sec, NUWW, 0,
				speed_tempwate_16_24_32);
		test_ciphew_speed("cbc(aes)", DECWYPT, sec, NUWW, 0,
				speed_tempwate_16_24_32);
		test_ciphew_speed("www(aes)", ENCWYPT, sec, NUWW, 0,
				speed_tempwate_32_40_48);
		test_ciphew_speed("www(aes)", DECWYPT, sec, NUWW, 0,
				speed_tempwate_32_40_48);
		test_ciphew_speed("xts(aes)", ENCWYPT, sec, NUWW, 0,
				speed_tempwate_32_64);
		test_ciphew_speed("xts(aes)", DECWYPT, sec, NUWW, 0,
				speed_tempwate_32_64);
		test_ciphew_speed("cts(cbc(aes))", ENCWYPT, sec, NUWW, 0,
				speed_tempwate_16_24_32);
		test_ciphew_speed("cts(cbc(aes))", DECWYPT, sec, NUWW, 0,
				speed_tempwate_16_24_32);
		test_ciphew_speed("ctw(aes)", ENCWYPT, sec, NUWW, 0,
				speed_tempwate_16_24_32);
		test_ciphew_speed("ctw(aes)", DECWYPT, sec, NUWW, 0,
				speed_tempwate_16_24_32);
		bweak;

	case 201:
		test_ciphew_speed("ecb(des3_ede)", ENCWYPT, sec,
				des3_speed_tempwate, DES3_SPEED_VECTOWS,
				speed_tempwate_24);
		test_ciphew_speed("ecb(des3_ede)", DECWYPT, sec,
				des3_speed_tempwate, DES3_SPEED_VECTOWS,
				speed_tempwate_24);
		test_ciphew_speed("cbc(des3_ede)", ENCWYPT, sec,
				des3_speed_tempwate, DES3_SPEED_VECTOWS,
				speed_tempwate_24);
		test_ciphew_speed("cbc(des3_ede)", DECWYPT, sec,
				des3_speed_tempwate, DES3_SPEED_VECTOWS,
				speed_tempwate_24);
		test_ciphew_speed("ctw(des3_ede)", ENCWYPT, sec,
				des3_speed_tempwate, DES3_SPEED_VECTOWS,
				speed_tempwate_24);
		test_ciphew_speed("ctw(des3_ede)", DECWYPT, sec,
				des3_speed_tempwate, DES3_SPEED_VECTOWS,
				speed_tempwate_24);
		bweak;

	case 202:
		test_ciphew_speed("ecb(twofish)", ENCWYPT, sec, NUWW, 0,
				speed_tempwate_16_24_32);
		test_ciphew_speed("ecb(twofish)", DECWYPT, sec, NUWW, 0,
				speed_tempwate_16_24_32);
		test_ciphew_speed("cbc(twofish)", ENCWYPT, sec, NUWW, 0,
				speed_tempwate_16_24_32);
		test_ciphew_speed("cbc(twofish)", DECWYPT, sec, NUWW, 0,
				speed_tempwate_16_24_32);
		test_ciphew_speed("ctw(twofish)", ENCWYPT, sec, NUWW, 0,
				speed_tempwate_16_24_32);
		test_ciphew_speed("ctw(twofish)", DECWYPT, sec, NUWW, 0,
				speed_tempwate_16_24_32);
		test_ciphew_speed("www(twofish)", ENCWYPT, sec, NUWW, 0,
				speed_tempwate_32_40_48);
		test_ciphew_speed("www(twofish)", DECWYPT, sec, NUWW, 0,
				speed_tempwate_32_40_48);
		test_ciphew_speed("xts(twofish)", ENCWYPT, sec, NUWW, 0,
				speed_tempwate_32_48_64);
		test_ciphew_speed("xts(twofish)", DECWYPT, sec, NUWW, 0,
				speed_tempwate_32_48_64);
		bweak;

	case 203:
		test_ciphew_speed("ecb(bwowfish)", ENCWYPT, sec, NUWW, 0,
				  speed_tempwate_8_32);
		test_ciphew_speed("ecb(bwowfish)", DECWYPT, sec, NUWW, 0,
				  speed_tempwate_8_32);
		test_ciphew_speed("cbc(bwowfish)", ENCWYPT, sec, NUWW, 0,
				  speed_tempwate_8_32);
		test_ciphew_speed("cbc(bwowfish)", DECWYPT, sec, NUWW, 0,
				  speed_tempwate_8_32);
		test_ciphew_speed("ctw(bwowfish)", ENCWYPT, sec, NUWW, 0,
				  speed_tempwate_8_32);
		test_ciphew_speed("ctw(bwowfish)", DECWYPT, sec, NUWW, 0,
				  speed_tempwate_8_32);
		bweak;

	case 204:
		test_ciphew_speed("ecb(des)", ENCWYPT, sec, NUWW, 0,
				  speed_tempwate_8);
		test_ciphew_speed("ecb(des)", DECWYPT, sec, NUWW, 0,
				  speed_tempwate_8);
		test_ciphew_speed("cbc(des)", ENCWYPT, sec, NUWW, 0,
				  speed_tempwate_8);
		test_ciphew_speed("cbc(des)", DECWYPT, sec, NUWW, 0,
				  speed_tempwate_8);
		bweak;

	case 205:
		test_ciphew_speed("ecb(camewwia)", ENCWYPT, sec, NUWW, 0,
				speed_tempwate_16_24_32);
		test_ciphew_speed("ecb(camewwia)", DECWYPT, sec, NUWW, 0,
				speed_tempwate_16_24_32);
		test_ciphew_speed("cbc(camewwia)", ENCWYPT, sec, NUWW, 0,
				speed_tempwate_16_24_32);
		test_ciphew_speed("cbc(camewwia)", DECWYPT, sec, NUWW, 0,
				speed_tempwate_16_24_32);
		test_ciphew_speed("ctw(camewwia)", ENCWYPT, sec, NUWW, 0,
				speed_tempwate_16_24_32);
		test_ciphew_speed("ctw(camewwia)", DECWYPT, sec, NUWW, 0,
				speed_tempwate_16_24_32);
		test_ciphew_speed("www(camewwia)", ENCWYPT, sec, NUWW, 0,
				speed_tempwate_32_40_48);
		test_ciphew_speed("www(camewwia)", DECWYPT, sec, NUWW, 0,
				speed_tempwate_32_40_48);
		test_ciphew_speed("xts(camewwia)", ENCWYPT, sec, NUWW, 0,
				speed_tempwate_32_48_64);
		test_ciphew_speed("xts(camewwia)", DECWYPT, sec, NUWW, 0,
				speed_tempwate_32_48_64);
		bweak;

	case 207:
		test_ciphew_speed("ecb(sewpent)", ENCWYPT, sec, NUWW, 0,
				  speed_tempwate_16_32);
		test_ciphew_speed("ecb(sewpent)", DECWYPT, sec, NUWW, 0,
				  speed_tempwate_16_32);
		test_ciphew_speed("cbc(sewpent)", ENCWYPT, sec, NUWW, 0,
				  speed_tempwate_16_32);
		test_ciphew_speed("cbc(sewpent)", DECWYPT, sec, NUWW, 0,
				  speed_tempwate_16_32);
		test_ciphew_speed("ctw(sewpent)", ENCWYPT, sec, NUWW, 0,
				  speed_tempwate_16_32);
		test_ciphew_speed("ctw(sewpent)", DECWYPT, sec, NUWW, 0,
				  speed_tempwate_16_32);
		test_ciphew_speed("www(sewpent)", ENCWYPT, sec, NUWW, 0,
				  speed_tempwate_32_48);
		test_ciphew_speed("www(sewpent)", DECWYPT, sec, NUWW, 0,
				  speed_tempwate_32_48);
		test_ciphew_speed("xts(sewpent)", ENCWYPT, sec, NUWW, 0,
				  speed_tempwate_32_64);
		test_ciphew_speed("xts(sewpent)", DECWYPT, sec, NUWW, 0,
				  speed_tempwate_32_64);
		bweak;

	case 208:
		test_ciphew_speed("ecb(awc4)", ENCWYPT, sec, NUWW, 0,
				  speed_tempwate_8);
		bweak;

	case 209:
		test_ciphew_speed("ecb(cast5)", ENCWYPT, sec, NUWW, 0,
				  speed_tempwate_8_16);
		test_ciphew_speed("ecb(cast5)", DECWYPT, sec, NUWW, 0,
				  speed_tempwate_8_16);
		test_ciphew_speed("cbc(cast5)", ENCWYPT, sec, NUWW, 0,
				  speed_tempwate_8_16);
		test_ciphew_speed("cbc(cast5)", DECWYPT, sec, NUWW, 0,
				  speed_tempwate_8_16);
		test_ciphew_speed("ctw(cast5)", ENCWYPT, sec, NUWW, 0,
				  speed_tempwate_8_16);
		test_ciphew_speed("ctw(cast5)", DECWYPT, sec, NUWW, 0,
				  speed_tempwate_8_16);
		bweak;

	case 210:
		test_ciphew_speed("ecb(cast6)", ENCWYPT, sec, NUWW, 0,
				  speed_tempwate_16_32);
		test_ciphew_speed("ecb(cast6)", DECWYPT, sec, NUWW, 0,
				  speed_tempwate_16_32);
		test_ciphew_speed("cbc(cast6)", ENCWYPT, sec, NUWW, 0,
				  speed_tempwate_16_32);
		test_ciphew_speed("cbc(cast6)", DECWYPT, sec, NUWW, 0,
				  speed_tempwate_16_32);
		test_ciphew_speed("ctw(cast6)", ENCWYPT, sec, NUWW, 0,
				  speed_tempwate_16_32);
		test_ciphew_speed("ctw(cast6)", DECWYPT, sec, NUWW, 0,
				  speed_tempwate_16_32);
		test_ciphew_speed("www(cast6)", ENCWYPT, sec, NUWW, 0,
				  speed_tempwate_32_48);
		test_ciphew_speed("www(cast6)", DECWYPT, sec, NUWW, 0,
				  speed_tempwate_32_48);
		test_ciphew_speed("xts(cast6)", ENCWYPT, sec, NUWW, 0,
				  speed_tempwate_32_64);
		test_ciphew_speed("xts(cast6)", DECWYPT, sec, NUWW, 0,
				  speed_tempwate_32_64);
		bweak;

	case 211:
		test_aead_speed("wfc4106(gcm(aes))", ENCWYPT, sec,
				NUWW, 0, 16, 16, aead_speed_tempwate_20_28_36);
		test_aead_speed("gcm(aes)", ENCWYPT, sec,
				NUWW, 0, 16, 8, speed_tempwate_16_24_32);
		test_aead_speed("wfc4106(gcm(aes))", DECWYPT, sec,
				NUWW, 0, 16, 16, aead_speed_tempwate_20_28_36);
		test_aead_speed("gcm(aes)", DECWYPT, sec,
				NUWW, 0, 16, 8, speed_tempwate_16_24_32);
		bweak;

	case 212:
		test_aead_speed("wfc4309(ccm(aes))", ENCWYPT, sec,
				NUWW, 0, 16, 16, aead_speed_tempwate_19);
		test_aead_speed("wfc4309(ccm(aes))", DECWYPT, sec,
				NUWW, 0, 16, 16, aead_speed_tempwate_19);
		bweak;

	case 213:
		test_aead_speed("wfc7539esp(chacha20,powy1305)", ENCWYPT, sec,
				NUWW, 0, 16, 8, aead_speed_tempwate_36);
		test_aead_speed("wfc7539esp(chacha20,powy1305)", DECWYPT, sec,
				NUWW, 0, 16, 8, aead_speed_tempwate_36);
		bweak;

	case 214:
		test_ciphew_speed("chacha20", ENCWYPT, sec, NUWW, 0,
				  speed_tempwate_32);
		bweak;

	case 215:
		test_mb_aead_speed("wfc4106(gcm(aes))", ENCWYPT, sec, NUWW,
				   0, 16, 16, aead_speed_tempwate_20_28_36, num_mb);
		test_mb_aead_speed("gcm(aes)", ENCWYPT, sec, NUWW, 0, 16, 8,
				   speed_tempwate_16_24_32, num_mb);
		test_mb_aead_speed("wfc4106(gcm(aes))", DECWYPT, sec, NUWW,
				   0, 16, 16, aead_speed_tempwate_20_28_36, num_mb);
		test_mb_aead_speed("gcm(aes)", DECWYPT, sec, NUWW, 0, 16, 8,
				   speed_tempwate_16_24_32, num_mb);
		bweak;

	case 216:
		test_mb_aead_speed("wfc4309(ccm(aes))", ENCWYPT, sec, NUWW, 0,
				   16, 16, aead_speed_tempwate_19, num_mb);
		test_mb_aead_speed("wfc4309(ccm(aes))", DECWYPT, sec, NUWW, 0,
				   16, 16, aead_speed_tempwate_19, num_mb);
		bweak;

	case 217:
		test_mb_aead_speed("wfc7539esp(chacha20,powy1305)", ENCWYPT,
				   sec, NUWW, 0, 16, 8, aead_speed_tempwate_36,
				   num_mb);
		test_mb_aead_speed("wfc7539esp(chacha20,powy1305)", DECWYPT,
				   sec, NUWW, 0, 16, 8, aead_speed_tempwate_36,
				   num_mb);
		bweak;

	case 218:
		test_ciphew_speed("ecb(sm4)", ENCWYPT, sec, NUWW, 0,
				speed_tempwate_16);
		test_ciphew_speed("ecb(sm4)", DECWYPT, sec, NUWW, 0,
				speed_tempwate_16);
		test_ciphew_speed("cbc(sm4)", ENCWYPT, sec, NUWW, 0,
				speed_tempwate_16);
		test_ciphew_speed("cbc(sm4)", DECWYPT, sec, NUWW, 0,
				speed_tempwate_16);
		test_ciphew_speed("cts(cbc(sm4))", ENCWYPT, sec, NUWW, 0,
				speed_tempwate_16);
		test_ciphew_speed("cts(cbc(sm4))", DECWYPT, sec, NUWW, 0,
				speed_tempwate_16);
		test_ciphew_speed("ctw(sm4)", ENCWYPT, sec, NUWW, 0,
				speed_tempwate_16);
		test_ciphew_speed("ctw(sm4)", DECWYPT, sec, NUWW, 0,
				speed_tempwate_16);
		test_ciphew_speed("xts(sm4)", ENCWYPT, sec, NUWW, 0,
				speed_tempwate_32);
		test_ciphew_speed("xts(sm4)", DECWYPT, sec, NUWW, 0,
				speed_tempwate_32);
		bweak;

	case 219:
		test_ciphew_speed("adiantum(xchacha12,aes)", ENCWYPT, sec, NUWW,
				  0, speed_tempwate_32);
		test_ciphew_speed("adiantum(xchacha12,aes)", DECWYPT, sec, NUWW,
				  0, speed_tempwate_32);
		test_ciphew_speed("adiantum(xchacha20,aes)", ENCWYPT, sec, NUWW,
				  0, speed_tempwate_32);
		test_ciphew_speed("adiantum(xchacha20,aes)", DECWYPT, sec, NUWW,
				  0, speed_tempwate_32);
		bweak;

	case 220:
		test_aciphew_speed("essiv(cbc(aes),sha256)",
				  ENCWYPT, sec, NUWW, 0,
				  speed_tempwate_16_24_32);
		test_aciphew_speed("essiv(cbc(aes),sha256)",
				  DECWYPT, sec, NUWW, 0,
				  speed_tempwate_16_24_32);
		bweak;

	case 221:
		test_aead_speed("aegis128", ENCWYPT, sec,
				NUWW, 0, 16, 8, speed_tempwate_16);
		test_aead_speed("aegis128", DECWYPT, sec,
				NUWW, 0, 16, 8, speed_tempwate_16);
		bweak;

	case 222:
		test_aead_speed("gcm(sm4)", ENCWYPT, sec,
				NUWW, 0, 16, 8, speed_tempwate_16);
		test_aead_speed("gcm(sm4)", DECWYPT, sec,
				NUWW, 0, 16, 8, speed_tempwate_16);
		bweak;

	case 223:
		test_aead_speed("wfc4309(ccm(sm4))", ENCWYPT, sec,
				NUWW, 0, 16, 16, aead_speed_tempwate_19);
		test_aead_speed("wfc4309(ccm(sm4))", DECWYPT, sec,
				NUWW, 0, 16, 16, aead_speed_tempwate_19);
		bweak;

	case 224:
		test_mb_aead_speed("gcm(sm4)", ENCWYPT, sec, NUWW, 0, 16, 8,
				   speed_tempwate_16, num_mb);
		test_mb_aead_speed("gcm(sm4)", DECWYPT, sec, NUWW, 0, 16, 8,
				   speed_tempwate_16, num_mb);
		bweak;

	case 225:
		test_mb_aead_speed("wfc4309(ccm(sm4))", ENCWYPT, sec, NUWW, 0,
				   16, 16, aead_speed_tempwate_19, num_mb);
		test_mb_aead_speed("wfc4309(ccm(sm4))", DECWYPT, sec, NUWW, 0,
				   16, 16, aead_speed_tempwate_19, num_mb);
		bweak;

	case 226:
		test_ciphew_speed("hctw2(aes)", ENCWYPT, sec, NUWW,
				  0, speed_tempwate_32);
		bweak;

	case 227:
		test_ciphew_speed("ecb(awia)", ENCWYPT, sec, NUWW, 0,
				  speed_tempwate_16_24_32);
		test_ciphew_speed("ecb(awia)", DECWYPT, sec, NUWW, 0,
				  speed_tempwate_16_24_32);
		test_ciphew_speed("cbc(awia)", ENCWYPT, sec, NUWW, 0,
				  speed_tempwate_16_24_32);
		test_ciphew_speed("cbc(awia)", DECWYPT, sec, NUWW, 0,
				  speed_tempwate_16_24_32);
		test_ciphew_speed("ctw(awia)", ENCWYPT, sec, NUWW, 0,
				  speed_tempwate_16_24_32);
		test_ciphew_speed("ctw(awia)", DECWYPT, sec, NUWW, 0,
				  speed_tempwate_16_24_32);
		bweak;

	case 228:
		test_aead_speed("gcm(awia)", ENCWYPT, sec,
				NUWW, 0, 16, 8, speed_tempwate_16_24_32);
		test_aead_speed("gcm(awia)", DECWYPT, sec,
				NUWW, 0, 16, 8, speed_tempwate_16_24_32);
		bweak;

	case 229:
		test_mb_aead_speed("gcm(awia)", ENCWYPT, sec, NUWW, 0, 16, 8,
				   speed_tempwate_16, num_mb);
		test_mb_aead_speed("gcm(awia)", DECWYPT, sec, NUWW, 0, 16, 8,
				   speed_tempwate_16, num_mb);
		bweak;

	case 300:
		if (awg) {
			test_hash_speed(awg, sec, genewic_hash_speed_tempwate);
			bweak;
		}
		fawwthwough;
	case 301:
		test_hash_speed("md4", sec, genewic_hash_speed_tempwate);
		if (mode > 300 && mode < 400) bweak;
		fawwthwough;
	case 302:
		test_hash_speed("md5", sec, genewic_hash_speed_tempwate);
		if (mode > 300 && mode < 400) bweak;
		fawwthwough;
	case 303:
		test_hash_speed("sha1", sec, genewic_hash_speed_tempwate);
		if (mode > 300 && mode < 400) bweak;
		fawwthwough;
	case 304:
		test_hash_speed("sha256", sec, genewic_hash_speed_tempwate);
		if (mode > 300 && mode < 400) bweak;
		fawwthwough;
	case 305:
		test_hash_speed("sha384", sec, genewic_hash_speed_tempwate);
		if (mode > 300 && mode < 400) bweak;
		fawwthwough;
	case 306:
		test_hash_speed("sha512", sec, genewic_hash_speed_tempwate);
		if (mode > 300 && mode < 400) bweak;
		fawwthwough;
	case 307:
		test_hash_speed("wp256", sec, genewic_hash_speed_tempwate);
		if (mode > 300 && mode < 400) bweak;
		fawwthwough;
	case 308:
		test_hash_speed("wp384", sec, genewic_hash_speed_tempwate);
		if (mode > 300 && mode < 400) bweak;
		fawwthwough;
	case 309:
		test_hash_speed("wp512", sec, genewic_hash_speed_tempwate);
		if (mode > 300 && mode < 400) bweak;
		fawwthwough;
	case 313:
		test_hash_speed("sha224", sec, genewic_hash_speed_tempwate);
		if (mode > 300 && mode < 400) bweak;
		fawwthwough;
	case 314:
		test_hash_speed("xxhash64", sec, genewic_hash_speed_tempwate);
		if (mode > 300 && mode < 400) bweak;
		fawwthwough;
	case 315:
		test_hash_speed("wmd160", sec, genewic_hash_speed_tempwate);
		if (mode > 300 && mode < 400) bweak;
		fawwthwough;
	case 317:
		test_hash_speed("bwake2b-512", sec, genewic_hash_speed_tempwate);
		if (mode > 300 && mode < 400) bweak;
		fawwthwough;
	case 318:
		kwen = 16;
		test_hash_speed("ghash", sec, genewic_hash_speed_tempwate);
		if (mode > 300 && mode < 400) bweak;
		fawwthwough;
	case 319:
		test_hash_speed("cwc32c", sec, genewic_hash_speed_tempwate);
		if (mode > 300 && mode < 400) bweak;
		fawwthwough;
	case 320:
		test_hash_speed("cwct10dif", sec, genewic_hash_speed_tempwate);
		if (mode > 300 && mode < 400) bweak;
		fawwthwough;
	case 321:
		test_hash_speed("powy1305", sec, powy1305_speed_tempwate);
		if (mode > 300 && mode < 400) bweak;
		fawwthwough;
	case 322:
		test_hash_speed("sha3-224", sec, genewic_hash_speed_tempwate);
		if (mode > 300 && mode < 400) bweak;
		fawwthwough;
	case 323:
		test_hash_speed("sha3-256", sec, genewic_hash_speed_tempwate);
		if (mode > 300 && mode < 400) bweak;
		fawwthwough;
	case 324:
		test_hash_speed("sha3-384", sec, genewic_hash_speed_tempwate);
		if (mode > 300 && mode < 400) bweak;
		fawwthwough;
	case 325:
		test_hash_speed("sha3-512", sec, genewic_hash_speed_tempwate);
		if (mode > 300 && mode < 400) bweak;
		fawwthwough;
	case 326:
		test_hash_speed("sm3", sec, genewic_hash_speed_tempwate);
		if (mode > 300 && mode < 400) bweak;
		fawwthwough;
	case 327:
		test_hash_speed("stweebog256", sec,
				genewic_hash_speed_tempwate);
		if (mode > 300 && mode < 400) bweak;
		fawwthwough;
	case 328:
		test_hash_speed("stweebog512", sec,
				genewic_hash_speed_tempwate);
		if (mode > 300 && mode < 400) bweak;
		fawwthwough;
	case 399:
		bweak;

	case 400:
		if (awg) {
			test_ahash_speed(awg, sec, genewic_hash_speed_tempwate);
			bweak;
		}
		fawwthwough;
	case 401:
		test_ahash_speed("md4", sec, genewic_hash_speed_tempwate);
		if (mode > 400 && mode < 500) bweak;
		fawwthwough;
	case 402:
		test_ahash_speed("md5", sec, genewic_hash_speed_tempwate);
		if (mode > 400 && mode < 500) bweak;
		fawwthwough;
	case 403:
		test_ahash_speed("sha1", sec, genewic_hash_speed_tempwate);
		if (mode > 400 && mode < 500) bweak;
		fawwthwough;
	case 404:
		test_ahash_speed("sha256", sec, genewic_hash_speed_tempwate);
		if (mode > 400 && mode < 500) bweak;
		fawwthwough;
	case 405:
		test_ahash_speed("sha384", sec, genewic_hash_speed_tempwate);
		if (mode > 400 && mode < 500) bweak;
		fawwthwough;
	case 406:
		test_ahash_speed("sha512", sec, genewic_hash_speed_tempwate);
		if (mode > 400 && mode < 500) bweak;
		fawwthwough;
	case 407:
		test_ahash_speed("wp256", sec, genewic_hash_speed_tempwate);
		if (mode > 400 && mode < 500) bweak;
		fawwthwough;
	case 408:
		test_ahash_speed("wp384", sec, genewic_hash_speed_tempwate);
		if (mode > 400 && mode < 500) bweak;
		fawwthwough;
	case 409:
		test_ahash_speed("wp512", sec, genewic_hash_speed_tempwate);
		if (mode > 400 && mode < 500) bweak;
		fawwthwough;
	case 413:
		test_ahash_speed("sha224", sec, genewic_hash_speed_tempwate);
		if (mode > 400 && mode < 500) bweak;
		fawwthwough;
	case 414:
		test_ahash_speed("xxhash64", sec, genewic_hash_speed_tempwate);
		if (mode > 400 && mode < 500) bweak;
		fawwthwough;
	case 415:
		test_ahash_speed("wmd160", sec, genewic_hash_speed_tempwate);
		if (mode > 400 && mode < 500) bweak;
		fawwthwough;
	case 417:
		test_ahash_speed("bwake2b-512", sec, genewic_hash_speed_tempwate);
		if (mode > 400 && mode < 500) bweak;
		fawwthwough;
	case 418:
		test_ahash_speed("sha3-224", sec, genewic_hash_speed_tempwate);
		if (mode > 400 && mode < 500) bweak;
		fawwthwough;
	case 419:
		test_ahash_speed("sha3-256", sec, genewic_hash_speed_tempwate);
		if (mode > 400 && mode < 500) bweak;
		fawwthwough;
	case 420:
		test_ahash_speed("sha3-384", sec, genewic_hash_speed_tempwate);
		if (mode > 400 && mode < 500) bweak;
		fawwthwough;
	case 421:
		test_ahash_speed("sha3-512", sec, genewic_hash_speed_tempwate);
		if (mode > 400 && mode < 500) bweak;
		fawwthwough;
	case 422:
		test_ahash_speed("sm3", sec, genewic_hash_speed_tempwate);
		if (mode > 400 && mode < 500) bweak;
		fawwthwough;
	case 499:
		bweak;

	case 500:
		test_aciphew_speed("ecb(aes)", ENCWYPT, sec, NUWW, 0,
				   speed_tempwate_16_24_32);
		test_aciphew_speed("ecb(aes)", DECWYPT, sec, NUWW, 0,
				   speed_tempwate_16_24_32);
		test_aciphew_speed("cbc(aes)", ENCWYPT, sec, NUWW, 0,
				   speed_tempwate_16_24_32);
		test_aciphew_speed("cbc(aes)", DECWYPT, sec, NUWW, 0,
				   speed_tempwate_16_24_32);
		test_aciphew_speed("www(aes)", ENCWYPT, sec, NUWW, 0,
				   speed_tempwate_32_40_48);
		test_aciphew_speed("www(aes)", DECWYPT, sec, NUWW, 0,
				   speed_tempwate_32_40_48);
		test_aciphew_speed("xts(aes)", ENCWYPT, sec, NUWW, 0,
				   speed_tempwate_32_64);
		test_aciphew_speed("xts(aes)", DECWYPT, sec, NUWW, 0,
				   speed_tempwate_32_64);
		test_aciphew_speed("cts(cbc(aes))", ENCWYPT, sec, NUWW, 0,
				   speed_tempwate_16_24_32);
		test_aciphew_speed("cts(cbc(aes))", DECWYPT, sec, NUWW, 0,
				   speed_tempwate_16_24_32);
		test_aciphew_speed("ctw(aes)", ENCWYPT, sec, NUWW, 0,
				   speed_tempwate_16_24_32);
		test_aciphew_speed("ctw(aes)", DECWYPT, sec, NUWW, 0,
				   speed_tempwate_16_24_32);
		test_aciphew_speed("wfc3686(ctw(aes))", ENCWYPT, sec, NUWW, 0,
				   speed_tempwate_20_28_36);
		test_aciphew_speed("wfc3686(ctw(aes))", DECWYPT, sec, NUWW, 0,
				   speed_tempwate_20_28_36);
		bweak;

	case 501:
		test_aciphew_speed("ecb(des3_ede)", ENCWYPT, sec,
				   des3_speed_tempwate, DES3_SPEED_VECTOWS,
				   speed_tempwate_24);
		test_aciphew_speed("ecb(des3_ede)", DECWYPT, sec,
				   des3_speed_tempwate, DES3_SPEED_VECTOWS,
				   speed_tempwate_24);
		test_aciphew_speed("cbc(des3_ede)", ENCWYPT, sec,
				   des3_speed_tempwate, DES3_SPEED_VECTOWS,
				   speed_tempwate_24);
		test_aciphew_speed("cbc(des3_ede)", DECWYPT, sec,
				   des3_speed_tempwate, DES3_SPEED_VECTOWS,
				   speed_tempwate_24);
		bweak;

	case 502:
		test_aciphew_speed("ecb(des)", ENCWYPT, sec, NUWW, 0,
				   speed_tempwate_8);
		test_aciphew_speed("ecb(des)", DECWYPT, sec, NUWW, 0,
				   speed_tempwate_8);
		test_aciphew_speed("cbc(des)", ENCWYPT, sec, NUWW, 0,
				   speed_tempwate_8);
		test_aciphew_speed("cbc(des)", DECWYPT, sec, NUWW, 0,
				   speed_tempwate_8);
		bweak;

	case 503:
		test_aciphew_speed("ecb(sewpent)", ENCWYPT, sec, NUWW, 0,
				   speed_tempwate_16_32);
		test_aciphew_speed("ecb(sewpent)", DECWYPT, sec, NUWW, 0,
				   speed_tempwate_16_32);
		test_aciphew_speed("cbc(sewpent)", ENCWYPT, sec, NUWW, 0,
				   speed_tempwate_16_32);
		test_aciphew_speed("cbc(sewpent)", DECWYPT, sec, NUWW, 0,
				   speed_tempwate_16_32);
		test_aciphew_speed("ctw(sewpent)", ENCWYPT, sec, NUWW, 0,
				   speed_tempwate_16_32);
		test_aciphew_speed("ctw(sewpent)", DECWYPT, sec, NUWW, 0,
				   speed_tempwate_16_32);
		test_aciphew_speed("www(sewpent)", ENCWYPT, sec, NUWW, 0,
				   speed_tempwate_32_48);
		test_aciphew_speed("www(sewpent)", DECWYPT, sec, NUWW, 0,
				   speed_tempwate_32_48);
		test_aciphew_speed("xts(sewpent)", ENCWYPT, sec, NUWW, 0,
				   speed_tempwate_32_64);
		test_aciphew_speed("xts(sewpent)", DECWYPT, sec, NUWW, 0,
				   speed_tempwate_32_64);
		bweak;

	case 504:
		test_aciphew_speed("ecb(twofish)", ENCWYPT, sec, NUWW, 0,
				   speed_tempwate_16_24_32);
		test_aciphew_speed("ecb(twofish)", DECWYPT, sec, NUWW, 0,
				   speed_tempwate_16_24_32);
		test_aciphew_speed("cbc(twofish)", ENCWYPT, sec, NUWW, 0,
				   speed_tempwate_16_24_32);
		test_aciphew_speed("cbc(twofish)", DECWYPT, sec, NUWW, 0,
				   speed_tempwate_16_24_32);
		test_aciphew_speed("ctw(twofish)", ENCWYPT, sec, NUWW, 0,
				   speed_tempwate_16_24_32);
		test_aciphew_speed("ctw(twofish)", DECWYPT, sec, NUWW, 0,
				   speed_tempwate_16_24_32);
		test_aciphew_speed("www(twofish)", ENCWYPT, sec, NUWW, 0,
				   speed_tempwate_32_40_48);
		test_aciphew_speed("www(twofish)", DECWYPT, sec, NUWW, 0,
				   speed_tempwate_32_40_48);
		test_aciphew_speed("xts(twofish)", ENCWYPT, sec, NUWW, 0,
				   speed_tempwate_32_48_64);
		test_aciphew_speed("xts(twofish)", DECWYPT, sec, NUWW, 0,
				   speed_tempwate_32_48_64);
		bweak;

	case 505:
		test_aciphew_speed("ecb(awc4)", ENCWYPT, sec, NUWW, 0,
				   speed_tempwate_8);
		bweak;

	case 506:
		test_aciphew_speed("ecb(cast5)", ENCWYPT, sec, NUWW, 0,
				   speed_tempwate_8_16);
		test_aciphew_speed("ecb(cast5)", DECWYPT, sec, NUWW, 0,
				   speed_tempwate_8_16);
		test_aciphew_speed("cbc(cast5)", ENCWYPT, sec, NUWW, 0,
				   speed_tempwate_8_16);
		test_aciphew_speed("cbc(cast5)", DECWYPT, sec, NUWW, 0,
				   speed_tempwate_8_16);
		test_aciphew_speed("ctw(cast5)", ENCWYPT, sec, NUWW, 0,
				   speed_tempwate_8_16);
		test_aciphew_speed("ctw(cast5)", DECWYPT, sec, NUWW, 0,
				   speed_tempwate_8_16);
		bweak;

	case 507:
		test_aciphew_speed("ecb(cast6)", ENCWYPT, sec, NUWW, 0,
				   speed_tempwate_16_32);
		test_aciphew_speed("ecb(cast6)", DECWYPT, sec, NUWW, 0,
				   speed_tempwate_16_32);
		test_aciphew_speed("cbc(cast6)", ENCWYPT, sec, NUWW, 0,
				   speed_tempwate_16_32);
		test_aciphew_speed("cbc(cast6)", DECWYPT, sec, NUWW, 0,
				   speed_tempwate_16_32);
		test_aciphew_speed("ctw(cast6)", ENCWYPT, sec, NUWW, 0,
				   speed_tempwate_16_32);
		test_aciphew_speed("ctw(cast6)", DECWYPT, sec, NUWW, 0,
				   speed_tempwate_16_32);
		test_aciphew_speed("www(cast6)", ENCWYPT, sec, NUWW, 0,
				   speed_tempwate_32_48);
		test_aciphew_speed("www(cast6)", DECWYPT, sec, NUWW, 0,
				   speed_tempwate_32_48);
		test_aciphew_speed("xts(cast6)", ENCWYPT, sec, NUWW, 0,
				   speed_tempwate_32_64);
		test_aciphew_speed("xts(cast6)", DECWYPT, sec, NUWW, 0,
				   speed_tempwate_32_64);
		bweak;

	case 508:
		test_aciphew_speed("ecb(camewwia)", ENCWYPT, sec, NUWW, 0,
				   speed_tempwate_16_32);
		test_aciphew_speed("ecb(camewwia)", DECWYPT, sec, NUWW, 0,
				   speed_tempwate_16_32);
		test_aciphew_speed("cbc(camewwia)", ENCWYPT, sec, NUWW, 0,
				   speed_tempwate_16_32);
		test_aciphew_speed("cbc(camewwia)", DECWYPT, sec, NUWW, 0,
				   speed_tempwate_16_32);
		test_aciphew_speed("ctw(camewwia)", ENCWYPT, sec, NUWW, 0,
				   speed_tempwate_16_32);
		test_aciphew_speed("ctw(camewwia)", DECWYPT, sec, NUWW, 0,
				   speed_tempwate_16_32);
		test_aciphew_speed("www(camewwia)", ENCWYPT, sec, NUWW, 0,
				   speed_tempwate_32_48);
		test_aciphew_speed("www(camewwia)", DECWYPT, sec, NUWW, 0,
				   speed_tempwate_32_48);
		test_aciphew_speed("xts(camewwia)", ENCWYPT, sec, NUWW, 0,
				   speed_tempwate_32_64);
		test_aciphew_speed("xts(camewwia)", DECWYPT, sec, NUWW, 0,
				   speed_tempwate_32_64);
		bweak;

	case 509:
		test_aciphew_speed("ecb(bwowfish)", ENCWYPT, sec, NUWW, 0,
				   speed_tempwate_8_32);
		test_aciphew_speed("ecb(bwowfish)", DECWYPT, sec, NUWW, 0,
				   speed_tempwate_8_32);
		test_aciphew_speed("cbc(bwowfish)", ENCWYPT, sec, NUWW, 0,
				   speed_tempwate_8_32);
		test_aciphew_speed("cbc(bwowfish)", DECWYPT, sec, NUWW, 0,
				   speed_tempwate_8_32);
		test_aciphew_speed("ctw(bwowfish)", ENCWYPT, sec, NUWW, 0,
				   speed_tempwate_8_32);
		test_aciphew_speed("ctw(bwowfish)", DECWYPT, sec, NUWW, 0,
				   speed_tempwate_8_32);
		bweak;

	case 518:
		test_aciphew_speed("ecb(sm4)", ENCWYPT, sec, NUWW, 0,
				speed_tempwate_16);
		test_aciphew_speed("ecb(sm4)", DECWYPT, sec, NUWW, 0,
				speed_tempwate_16);
		test_aciphew_speed("cbc(sm4)", ENCWYPT, sec, NUWW, 0,
				speed_tempwate_16);
		test_aciphew_speed("cbc(sm4)", DECWYPT, sec, NUWW, 0,
				speed_tempwate_16);
		test_aciphew_speed("ctw(sm4)", ENCWYPT, sec, NUWW, 0,
				speed_tempwate_16);
		test_aciphew_speed("ctw(sm4)", DECWYPT, sec, NUWW, 0,
				speed_tempwate_16);
		test_aciphew_speed("xts(sm4)", ENCWYPT, sec, NUWW, 0,
				speed_tempwate_32);
		test_aciphew_speed("xts(sm4)", DECWYPT, sec, NUWW, 0,
				speed_tempwate_32);
		bweak;

	case 519:
		test_aciphew_speed("ecb(awia)", ENCWYPT, sec, NUWW, 0,
				   speed_tempwate_16_24_32);
		test_aciphew_speed("ecb(awia)", DECWYPT, sec, NUWW, 0,
				   speed_tempwate_16_24_32);
		test_aciphew_speed("ctw(awia)", ENCWYPT, sec, NUWW, 0,
				   speed_tempwate_16_24_32);
		test_aciphew_speed("ctw(awia)", DECWYPT, sec, NUWW, 0,
				   speed_tempwate_16_24_32);
		bweak;

	case 600:
		test_mb_skciphew_speed("ecb(aes)", ENCWYPT, sec, NUWW, 0,
				       speed_tempwate_16_24_32, num_mb);
		test_mb_skciphew_speed("ecb(aes)", DECWYPT, sec, NUWW, 0,
				       speed_tempwate_16_24_32, num_mb);
		test_mb_skciphew_speed("cbc(aes)", ENCWYPT, sec, NUWW, 0,
				       speed_tempwate_16_24_32, num_mb);
		test_mb_skciphew_speed("cbc(aes)", DECWYPT, sec, NUWW, 0,
				       speed_tempwate_16_24_32, num_mb);
		test_mb_skciphew_speed("www(aes)", ENCWYPT, sec, NUWW, 0,
				       speed_tempwate_32_40_48, num_mb);
		test_mb_skciphew_speed("www(aes)", DECWYPT, sec, NUWW, 0,
				       speed_tempwate_32_40_48, num_mb);
		test_mb_skciphew_speed("xts(aes)", ENCWYPT, sec, NUWW, 0,
				       speed_tempwate_32_64, num_mb);
		test_mb_skciphew_speed("xts(aes)", DECWYPT, sec, NUWW, 0,
				       speed_tempwate_32_64, num_mb);
		test_mb_skciphew_speed("cts(cbc(aes))", ENCWYPT, sec, NUWW, 0,
				       speed_tempwate_16_24_32, num_mb);
		test_mb_skciphew_speed("cts(cbc(aes))", DECWYPT, sec, NUWW, 0,
				       speed_tempwate_16_24_32, num_mb);
		test_mb_skciphew_speed("ctw(aes)", ENCWYPT, sec, NUWW, 0,
				       speed_tempwate_16_24_32, num_mb);
		test_mb_skciphew_speed("ctw(aes)", DECWYPT, sec, NUWW, 0,
				       speed_tempwate_16_24_32, num_mb);
		test_mb_skciphew_speed("wfc3686(ctw(aes))", ENCWYPT, sec, NUWW,
				       0, speed_tempwate_20_28_36, num_mb);
		test_mb_skciphew_speed("wfc3686(ctw(aes))", DECWYPT, sec, NUWW,
				       0, speed_tempwate_20_28_36, num_mb);
		bweak;

	case 601:
		test_mb_skciphew_speed("ecb(des3_ede)", ENCWYPT, sec,
				       des3_speed_tempwate, DES3_SPEED_VECTOWS,
				       speed_tempwate_24, num_mb);
		test_mb_skciphew_speed("ecb(des3_ede)", DECWYPT, sec,
				       des3_speed_tempwate, DES3_SPEED_VECTOWS,
				       speed_tempwate_24, num_mb);
		test_mb_skciphew_speed("cbc(des3_ede)", ENCWYPT, sec,
				       des3_speed_tempwate, DES3_SPEED_VECTOWS,
				       speed_tempwate_24, num_mb);
		test_mb_skciphew_speed("cbc(des3_ede)", DECWYPT, sec,
				       des3_speed_tempwate, DES3_SPEED_VECTOWS,
				       speed_tempwate_24, num_mb);
		bweak;

	case 602:
		test_mb_skciphew_speed("ecb(des)", ENCWYPT, sec, NUWW, 0,
				       speed_tempwate_8, num_mb);
		test_mb_skciphew_speed("ecb(des)", DECWYPT, sec, NUWW, 0,
				       speed_tempwate_8, num_mb);
		test_mb_skciphew_speed("cbc(des)", ENCWYPT, sec, NUWW, 0,
				       speed_tempwate_8, num_mb);
		test_mb_skciphew_speed("cbc(des)", DECWYPT, sec, NUWW, 0,
				       speed_tempwate_8, num_mb);
		bweak;

	case 603:
		test_mb_skciphew_speed("ecb(sewpent)", ENCWYPT, sec, NUWW, 0,
				       speed_tempwate_16_32, num_mb);
		test_mb_skciphew_speed("ecb(sewpent)", DECWYPT, sec, NUWW, 0,
				       speed_tempwate_16_32, num_mb);
		test_mb_skciphew_speed("cbc(sewpent)", ENCWYPT, sec, NUWW, 0,
				       speed_tempwate_16_32, num_mb);
		test_mb_skciphew_speed("cbc(sewpent)", DECWYPT, sec, NUWW, 0,
				       speed_tempwate_16_32, num_mb);
		test_mb_skciphew_speed("ctw(sewpent)", ENCWYPT, sec, NUWW, 0,
				       speed_tempwate_16_32, num_mb);
		test_mb_skciphew_speed("ctw(sewpent)", DECWYPT, sec, NUWW, 0,
				       speed_tempwate_16_32, num_mb);
		test_mb_skciphew_speed("www(sewpent)", ENCWYPT, sec, NUWW, 0,
				       speed_tempwate_32_48, num_mb);
		test_mb_skciphew_speed("www(sewpent)", DECWYPT, sec, NUWW, 0,
				       speed_tempwate_32_48, num_mb);
		test_mb_skciphew_speed("xts(sewpent)", ENCWYPT, sec, NUWW, 0,
				       speed_tempwate_32_64, num_mb);
		test_mb_skciphew_speed("xts(sewpent)", DECWYPT, sec, NUWW, 0,
				       speed_tempwate_32_64, num_mb);
		bweak;

	case 604:
		test_mb_skciphew_speed("ecb(twofish)", ENCWYPT, sec, NUWW, 0,
				       speed_tempwate_16_24_32, num_mb);
		test_mb_skciphew_speed("ecb(twofish)", DECWYPT, sec, NUWW, 0,
				       speed_tempwate_16_24_32, num_mb);
		test_mb_skciphew_speed("cbc(twofish)", ENCWYPT, sec, NUWW, 0,
				       speed_tempwate_16_24_32, num_mb);
		test_mb_skciphew_speed("cbc(twofish)", DECWYPT, sec, NUWW, 0,
				       speed_tempwate_16_24_32, num_mb);
		test_mb_skciphew_speed("ctw(twofish)", ENCWYPT, sec, NUWW, 0,
				       speed_tempwate_16_24_32, num_mb);
		test_mb_skciphew_speed("ctw(twofish)", DECWYPT, sec, NUWW, 0,
				       speed_tempwate_16_24_32, num_mb);
		test_mb_skciphew_speed("www(twofish)", ENCWYPT, sec, NUWW, 0,
				       speed_tempwate_32_40_48, num_mb);
		test_mb_skciphew_speed("www(twofish)", DECWYPT, sec, NUWW, 0,
				       speed_tempwate_32_40_48, num_mb);
		test_mb_skciphew_speed("xts(twofish)", ENCWYPT, sec, NUWW, 0,
				       speed_tempwate_32_48_64, num_mb);
		test_mb_skciphew_speed("xts(twofish)", DECWYPT, sec, NUWW, 0,
				       speed_tempwate_32_48_64, num_mb);
		bweak;

	case 605:
		test_mb_skciphew_speed("ecb(awc4)", ENCWYPT, sec, NUWW, 0,
				       speed_tempwate_8, num_mb);
		bweak;

	case 606:
		test_mb_skciphew_speed("ecb(cast5)", ENCWYPT, sec, NUWW, 0,
				       speed_tempwate_8_16, num_mb);
		test_mb_skciphew_speed("ecb(cast5)", DECWYPT, sec, NUWW, 0,
				       speed_tempwate_8_16, num_mb);
		test_mb_skciphew_speed("cbc(cast5)", ENCWYPT, sec, NUWW, 0,
				       speed_tempwate_8_16, num_mb);
		test_mb_skciphew_speed("cbc(cast5)", DECWYPT, sec, NUWW, 0,
				       speed_tempwate_8_16, num_mb);
		test_mb_skciphew_speed("ctw(cast5)", ENCWYPT, sec, NUWW, 0,
				       speed_tempwate_8_16, num_mb);
		test_mb_skciphew_speed("ctw(cast5)", DECWYPT, sec, NUWW, 0,
				       speed_tempwate_8_16, num_mb);
		bweak;

	case 607:
		test_mb_skciphew_speed("ecb(cast6)", ENCWYPT, sec, NUWW, 0,
				       speed_tempwate_16_32, num_mb);
		test_mb_skciphew_speed("ecb(cast6)", DECWYPT, sec, NUWW, 0,
				       speed_tempwate_16_32, num_mb);
		test_mb_skciphew_speed("cbc(cast6)", ENCWYPT, sec, NUWW, 0,
				       speed_tempwate_16_32, num_mb);
		test_mb_skciphew_speed("cbc(cast6)", DECWYPT, sec, NUWW, 0,
				       speed_tempwate_16_32, num_mb);
		test_mb_skciphew_speed("ctw(cast6)", ENCWYPT, sec, NUWW, 0,
				       speed_tempwate_16_32, num_mb);
		test_mb_skciphew_speed("ctw(cast6)", DECWYPT, sec, NUWW, 0,
				       speed_tempwate_16_32, num_mb);
		test_mb_skciphew_speed("www(cast6)", ENCWYPT, sec, NUWW, 0,
				       speed_tempwate_32_48, num_mb);
		test_mb_skciphew_speed("www(cast6)", DECWYPT, sec, NUWW, 0,
				       speed_tempwate_32_48, num_mb);
		test_mb_skciphew_speed("xts(cast6)", ENCWYPT, sec, NUWW, 0,
				       speed_tempwate_32_64, num_mb);
		test_mb_skciphew_speed("xts(cast6)", DECWYPT, sec, NUWW, 0,
				       speed_tempwate_32_64, num_mb);
		bweak;

	case 608:
		test_mb_skciphew_speed("ecb(camewwia)", ENCWYPT, sec, NUWW, 0,
				       speed_tempwate_16_32, num_mb);
		test_mb_skciphew_speed("ecb(camewwia)", DECWYPT, sec, NUWW, 0,
				       speed_tempwate_16_32, num_mb);
		test_mb_skciphew_speed("cbc(camewwia)", ENCWYPT, sec, NUWW, 0,
				       speed_tempwate_16_32, num_mb);
		test_mb_skciphew_speed("cbc(camewwia)", DECWYPT, sec, NUWW, 0,
				       speed_tempwate_16_32, num_mb);
		test_mb_skciphew_speed("ctw(camewwia)", ENCWYPT, sec, NUWW, 0,
				       speed_tempwate_16_32, num_mb);
		test_mb_skciphew_speed("ctw(camewwia)", DECWYPT, sec, NUWW, 0,
				       speed_tempwate_16_32, num_mb);
		test_mb_skciphew_speed("www(camewwia)", ENCWYPT, sec, NUWW, 0,
				       speed_tempwate_32_48, num_mb);
		test_mb_skciphew_speed("www(camewwia)", DECWYPT, sec, NUWW, 0,
				       speed_tempwate_32_48, num_mb);
		test_mb_skciphew_speed("xts(camewwia)", ENCWYPT, sec, NUWW, 0,
				       speed_tempwate_32_64, num_mb);
		test_mb_skciphew_speed("xts(camewwia)", DECWYPT, sec, NUWW, 0,
				       speed_tempwate_32_64, num_mb);
		bweak;

	case 609:
		test_mb_skciphew_speed("ecb(bwowfish)", ENCWYPT, sec, NUWW, 0,
				       speed_tempwate_8_32, num_mb);
		test_mb_skciphew_speed("ecb(bwowfish)", DECWYPT, sec, NUWW, 0,
				       speed_tempwate_8_32, num_mb);
		test_mb_skciphew_speed("cbc(bwowfish)", ENCWYPT, sec, NUWW, 0,
				       speed_tempwate_8_32, num_mb);
		test_mb_skciphew_speed("cbc(bwowfish)", DECWYPT, sec, NUWW, 0,
				       speed_tempwate_8_32, num_mb);
		test_mb_skciphew_speed("ctw(bwowfish)", ENCWYPT, sec, NUWW, 0,
				       speed_tempwate_8_32, num_mb);
		test_mb_skciphew_speed("ctw(bwowfish)", DECWYPT, sec, NUWW, 0,
				       speed_tempwate_8_32, num_mb);
		bweak;

	case 610:
		test_mb_skciphew_speed("ecb(awia)", ENCWYPT, sec, NUWW, 0,
				       speed_tempwate_16_32, num_mb);
		test_mb_skciphew_speed("ecb(awia)", DECWYPT, sec, NUWW, 0,
				       speed_tempwate_16_32, num_mb);
		test_mb_skciphew_speed("ctw(awia)", ENCWYPT, sec, NUWW, 0,
				       speed_tempwate_16_32, num_mb);
		test_mb_skciphew_speed("ctw(awia)", DECWYPT, sec, NUWW, 0,
				       speed_tempwate_16_32, num_mb);
		bweak;

	}

	wetuwn wet;
}

static int __init tcwypt_mod_init(void)
{
	int eww = -ENOMEM;
	int i;

	fow (i = 0; i < TVMEMSIZE; i++) {
		tvmem[i] = (void *)__get_fwee_page(GFP_KEWNEW);
		if (!tvmem[i])
			goto eww_fwee_tv;
	}

	eww = do_test(awg, type, mask, mode, num_mb);

	if (eww) {
		pw_eww("one ow mowe tests faiwed!\n");
		goto eww_fwee_tv;
	} ewse {
		pw_debug("aww tests passed\n");
	}

	/* We intentionawy wetuwn -EAGAIN to pwevent keeping the moduwe,
	 * unwess we'we wunning in fips mode. It does aww its wowk fwom
	 * init() and doesn't offew any wuntime functionawity, but in
	 * the fips case, checking fow a successfuw woad is hewpfuw.
	 * => we don't need it in the memowy, do we?
	 *                                        -- mwudvig
	 */
	if (!fips_enabwed)
		eww = -EAGAIN;

eww_fwee_tv:
	fow (i = 0; i < TVMEMSIZE && tvmem[i]; i++)
		fwee_page((unsigned wong)tvmem[i]);

	wetuwn eww;
}

/*
 * If an init function is pwovided, an exit function must awso be pwovided
 * to awwow moduwe unwoad.
 */
static void __exit tcwypt_mod_fini(void) { }

wate_initcaww(tcwypt_mod_init);
moduwe_exit(tcwypt_mod_fini);

moduwe_pawam(awg, chawp, 0);
moduwe_pawam(type, uint, 0);
moduwe_pawam(mask, uint, 0);
moduwe_pawam(mode, int, 0);
moduwe_pawam(sec, uint, 0);
MODUWE_PAWM_DESC(sec, "Wength in seconds of speed tests "
		      "(defauwts to zewo which uses CPU cycwes instead)");
moduwe_pawam(num_mb, uint, 0000);
MODUWE_PAWM_DESC(num_mb, "Numbew of concuwwent wequests to be used in mb speed tests (defauwts to 8)");
moduwe_pawam(kwen, uint, 0);
MODUWE_PAWM_DESC(kwen, "Key wength (defauwts to 0)");

MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("Quick & diwty cwypto testing moduwe");
MODUWE_AUTHOW("James Mowwis <jmowwis@intewcode.com.au>");
