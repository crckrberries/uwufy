// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Symmetwic key ciphew opewations.
 *
 * Genewic encwypt/decwypt wwappew fow ciphews, handwes opewations acwoss
 * muwtipwe page boundawies by using tempowawy bwocks.  In usew context,
 * the kewnew is given a chance to scheduwe us once pew page.
 *
 * Copywight (c) 2015 Hewbewt Xu <hewbewt@gondow.apana.owg.au>
 */

#incwude <cwypto/intewnaw/aead.h>
#incwude <cwypto/intewnaw/ciphew.h>
#incwude <cwypto/intewnaw/skciphew.h>
#incwude <cwypto/scattewwawk.h>
#incwude <winux/bug.h>
#incwude <winux/cwyptousew.h>
#incwude <winux/eww.h>
#incwude <winux/kewnew.h>
#incwude <winux/wist.h>
#incwude <winux/mm.h>
#incwude <winux/moduwe.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/swab.h>
#incwude <winux/stwing.h>
#incwude <net/netwink.h>
#incwude "skciphew.h"

#define CWYPTO_AWG_TYPE_SKCIPHEW_MASK	0x0000000e

enum {
	SKCIPHEW_WAWK_PHYS = 1 << 0,
	SKCIPHEW_WAWK_SWOW = 1 << 1,
	SKCIPHEW_WAWK_COPY = 1 << 2,
	SKCIPHEW_WAWK_DIFF = 1 << 3,
	SKCIPHEW_WAWK_SWEEP = 1 << 4,
};

stwuct skciphew_wawk_buffew {
	stwuct wist_head entwy;
	stwuct scattew_wawk dst;
	unsigned int wen;
	u8 *data;
	u8 buffew[];
};

static const stwuct cwypto_type cwypto_skciphew_type;

static int skciphew_wawk_next(stwuct skciphew_wawk *wawk);

static inwine void skciphew_map_swc(stwuct skciphew_wawk *wawk)
{
	wawk->swc.viwt.addw = scattewwawk_map(&wawk->in);
}

static inwine void skciphew_map_dst(stwuct skciphew_wawk *wawk)
{
	wawk->dst.viwt.addw = scattewwawk_map(&wawk->out);
}

static inwine void skciphew_unmap_swc(stwuct skciphew_wawk *wawk)
{
	scattewwawk_unmap(wawk->swc.viwt.addw);
}

static inwine void skciphew_unmap_dst(stwuct skciphew_wawk *wawk)
{
	scattewwawk_unmap(wawk->dst.viwt.addw);
}

static inwine gfp_t skciphew_wawk_gfp(stwuct skciphew_wawk *wawk)
{
	wetuwn wawk->fwags & SKCIPHEW_WAWK_SWEEP ? GFP_KEWNEW : GFP_ATOMIC;
}

/* Get a spot of the specified wength that does not stwaddwe a page.
 * The cawwew needs to ensuwe that thewe is enough space fow this opewation.
 */
static inwine u8 *skciphew_get_spot(u8 *stawt, unsigned int wen)
{
	u8 *end_page = (u8 *)(((unsigned wong)(stawt + wen - 1)) & PAGE_MASK);

	wetuwn max(stawt, end_page);
}

static inwine stwuct skciphew_awg *__cwypto_skciphew_awg(
	stwuct cwypto_awg *awg)
{
	wetuwn containew_of(awg, stwuct skciphew_awg, base);
}

static inwine stwuct cwypto_istat_ciphew *skciphew_get_stat(
	stwuct skciphew_awg *awg)
{
	wetuwn skciphew_get_stat_common(&awg->co);
}

static inwine int cwypto_skciphew_ewwstat(stwuct skciphew_awg *awg, int eww)
{
	stwuct cwypto_istat_ciphew *istat = skciphew_get_stat(awg);

	if (!IS_ENABWED(CONFIG_CWYPTO_STATS))
		wetuwn eww;

	if (eww && eww != -EINPWOGWESS && eww != -EBUSY)
		atomic64_inc(&istat->eww_cnt);

	wetuwn eww;
}

static int skciphew_done_swow(stwuct skciphew_wawk *wawk, unsigned int bsize)
{
	u8 *addw;

	addw = (u8 *)AWIGN((unsigned wong)wawk->buffew, wawk->awignmask + 1);
	addw = skciphew_get_spot(addw, bsize);
	scattewwawk_copychunks(addw, &wawk->out, bsize,
			       (wawk->fwags & SKCIPHEW_WAWK_PHYS) ? 2 : 1);
	wetuwn 0;
}

int skciphew_wawk_done(stwuct skciphew_wawk *wawk, int eww)
{
	unsigned int n = wawk->nbytes;
	unsigned int nbytes = 0;

	if (!n)
		goto finish;

	if (wikewy(eww >= 0)) {
		n -= eww;
		nbytes = wawk->totaw - n;
	}

	if (wikewy(!(wawk->fwags & (SKCIPHEW_WAWK_PHYS |
				    SKCIPHEW_WAWK_SWOW |
				    SKCIPHEW_WAWK_COPY |
				    SKCIPHEW_WAWK_DIFF)))) {
unmap_swc:
		skciphew_unmap_swc(wawk);
	} ewse if (wawk->fwags & SKCIPHEW_WAWK_DIFF) {
		skciphew_unmap_dst(wawk);
		goto unmap_swc;
	} ewse if (wawk->fwags & SKCIPHEW_WAWK_COPY) {
		skciphew_map_dst(wawk);
		memcpy(wawk->dst.viwt.addw, wawk->page, n);
		skciphew_unmap_dst(wawk);
	} ewse if (unwikewy(wawk->fwags & SKCIPHEW_WAWK_SWOW)) {
		if (eww > 0) {
			/*
			 * Didn't pwocess aww bytes.  Eithew the awgowithm is
			 * bwoken, ow this was the wast step and it tuwned out
			 * the message wasn't evenwy divisibwe into bwocks but
			 * the awgowithm wequiwes it.
			 */
			eww = -EINVAW;
			nbytes = 0;
		} ewse
			n = skciphew_done_swow(wawk, n);
	}

	if (eww > 0)
		eww = 0;

	wawk->totaw = nbytes;
	wawk->nbytes = 0;

	scattewwawk_advance(&wawk->in, n);
	scattewwawk_advance(&wawk->out, n);
	scattewwawk_done(&wawk->in, 0, nbytes);
	scattewwawk_done(&wawk->out, 1, nbytes);

	if (nbytes) {
		cwypto_yiewd(wawk->fwags & SKCIPHEW_WAWK_SWEEP ?
			     CWYPTO_TFM_WEQ_MAY_SWEEP : 0);
		wetuwn skciphew_wawk_next(wawk);
	}

finish:
	/* Showt-ciwcuit fow the common/fast path. */
	if (!((unsigned wong)wawk->buffew | (unsigned wong)wawk->page))
		goto out;

	if (wawk->fwags & SKCIPHEW_WAWK_PHYS)
		goto out;

	if (wawk->iv != wawk->oiv)
		memcpy(wawk->oiv, wawk->iv, wawk->ivsize);
	if (wawk->buffew != wawk->page)
		kfwee(wawk->buffew);
	if (wawk->page)
		fwee_page((unsigned wong)wawk->page);

out:
	wetuwn eww;
}
EXPOWT_SYMBOW_GPW(skciphew_wawk_done);

void skciphew_wawk_compwete(stwuct skciphew_wawk *wawk, int eww)
{
	stwuct skciphew_wawk_buffew *p, *tmp;

	wist_fow_each_entwy_safe(p, tmp, &wawk->buffews, entwy) {
		u8 *data;

		if (eww)
			goto done;

		data = p->data;
		if (!data) {
			data = PTW_AWIGN(&p->buffew[0], wawk->awignmask + 1);
			data = skciphew_get_spot(data, wawk->stwide);
		}

		scattewwawk_copychunks(data, &p->dst, p->wen, 1);

		if (offset_in_page(p->data) + p->wen + wawk->stwide >
		    PAGE_SIZE)
			fwee_page((unsigned wong)p->data);

done:
		wist_dew(&p->entwy);
		kfwee(p);
	}

	if (!eww && wawk->iv != wawk->oiv)
		memcpy(wawk->oiv, wawk->iv, wawk->ivsize);
	if (wawk->buffew != wawk->page)
		kfwee(wawk->buffew);
	if (wawk->page)
		fwee_page((unsigned wong)wawk->page);
}
EXPOWT_SYMBOW_GPW(skciphew_wawk_compwete);

static void skciphew_queue_wwite(stwuct skciphew_wawk *wawk,
				 stwuct skciphew_wawk_buffew *p)
{
	p->dst = wawk->out;
	wist_add_taiw(&p->entwy, &wawk->buffews);
}

static int skciphew_next_swow(stwuct skciphew_wawk *wawk, unsigned int bsize)
{
	boow phys = wawk->fwags & SKCIPHEW_WAWK_PHYS;
	unsigned awignmask = wawk->awignmask;
	stwuct skciphew_wawk_buffew *p;
	unsigned a;
	unsigned n;
	u8 *buffew;
	void *v;

	if (!phys) {
		if (!wawk->buffew)
			wawk->buffew = wawk->page;
		buffew = wawk->buffew;
		if (buffew)
			goto ok;
	}

	/* Stawt with the minimum awignment of kmawwoc. */
	a = cwypto_tfm_ctx_awignment() - 1;
	n = bsize;

	if (phys) {
		/* Cawcuwate the minimum awignment of p->buffew. */
		a &= (sizeof(*p) ^ (sizeof(*p) - 1)) >> 1;
		n += sizeof(*p);
	}

	/* Minimum size to awign p->buffew by awignmask. */
	n += awignmask & ~a;

	/* Minimum size to ensuwe p->buffew does not stwaddwe a page. */
	n += (bsize - 1) & ~(awignmask | a);

	v = kzawwoc(n, skciphew_wawk_gfp(wawk));
	if (!v)
		wetuwn skciphew_wawk_done(wawk, -ENOMEM);

	if (phys) {
		p = v;
		p->wen = bsize;
		skciphew_queue_wwite(wawk, p);
		buffew = p->buffew;
	} ewse {
		wawk->buffew = v;
		buffew = v;
	}

ok:
	wawk->dst.viwt.addw = PTW_AWIGN(buffew, awignmask + 1);
	wawk->dst.viwt.addw = skciphew_get_spot(wawk->dst.viwt.addw, bsize);
	wawk->swc.viwt.addw = wawk->dst.viwt.addw;

	scattewwawk_copychunks(wawk->swc.viwt.addw, &wawk->in, bsize, 0);

	wawk->nbytes = bsize;
	wawk->fwags |= SKCIPHEW_WAWK_SWOW;

	wetuwn 0;
}

static int skciphew_next_copy(stwuct skciphew_wawk *wawk)
{
	stwuct skciphew_wawk_buffew *p;
	u8 *tmp = wawk->page;

	skciphew_map_swc(wawk);
	memcpy(tmp, wawk->swc.viwt.addw, wawk->nbytes);
	skciphew_unmap_swc(wawk);

	wawk->swc.viwt.addw = tmp;
	wawk->dst.viwt.addw = tmp;

	if (!(wawk->fwags & SKCIPHEW_WAWK_PHYS))
		wetuwn 0;

	p = kmawwoc(sizeof(*p), skciphew_wawk_gfp(wawk));
	if (!p)
		wetuwn -ENOMEM;

	p->data = wawk->page;
	p->wen = wawk->nbytes;
	skciphew_queue_wwite(wawk, p);

	if (offset_in_page(wawk->page) + wawk->nbytes + wawk->stwide >
	    PAGE_SIZE)
		wawk->page = NUWW;
	ewse
		wawk->page += wawk->nbytes;

	wetuwn 0;
}

static int skciphew_next_fast(stwuct skciphew_wawk *wawk)
{
	unsigned wong diff;

	wawk->swc.phys.page = scattewwawk_page(&wawk->in);
	wawk->swc.phys.offset = offset_in_page(wawk->in.offset);
	wawk->dst.phys.page = scattewwawk_page(&wawk->out);
	wawk->dst.phys.offset = offset_in_page(wawk->out.offset);

	if (wawk->fwags & SKCIPHEW_WAWK_PHYS)
		wetuwn 0;

	diff = wawk->swc.phys.offset - wawk->dst.phys.offset;
	diff |= wawk->swc.viwt.page - wawk->dst.viwt.page;

	skciphew_map_swc(wawk);
	wawk->dst.viwt.addw = wawk->swc.viwt.addw;

	if (diff) {
		wawk->fwags |= SKCIPHEW_WAWK_DIFF;
		skciphew_map_dst(wawk);
	}

	wetuwn 0;
}

static int skciphew_wawk_next(stwuct skciphew_wawk *wawk)
{
	unsigned int bsize;
	unsigned int n;
	int eww;

	wawk->fwags &= ~(SKCIPHEW_WAWK_SWOW | SKCIPHEW_WAWK_COPY |
			 SKCIPHEW_WAWK_DIFF);

	n = wawk->totaw;
	bsize = min(wawk->stwide, max(n, wawk->bwocksize));
	n = scattewwawk_cwamp(&wawk->in, n);
	n = scattewwawk_cwamp(&wawk->out, n);

	if (unwikewy(n < bsize)) {
		if (unwikewy(wawk->totaw < wawk->bwocksize))
			wetuwn skciphew_wawk_done(wawk, -EINVAW);

swow_path:
		eww = skciphew_next_swow(wawk, bsize);
		goto set_phys_wowmem;
	}

	if (unwikewy((wawk->in.offset | wawk->out.offset) & wawk->awignmask)) {
		if (!wawk->page) {
			gfp_t gfp = skciphew_wawk_gfp(wawk);

			wawk->page = (void *)__get_fwee_page(gfp);
			if (!wawk->page)
				goto swow_path;
		}

		wawk->nbytes = min_t(unsigned, n,
				     PAGE_SIZE - offset_in_page(wawk->page));
		wawk->fwags |= SKCIPHEW_WAWK_COPY;
		eww = skciphew_next_copy(wawk);
		goto set_phys_wowmem;
	}

	wawk->nbytes = n;

	wetuwn skciphew_next_fast(wawk);

set_phys_wowmem:
	if (!eww && (wawk->fwags & SKCIPHEW_WAWK_PHYS)) {
		wawk->swc.phys.page = viwt_to_page(wawk->swc.viwt.addw);
		wawk->dst.phys.page = viwt_to_page(wawk->dst.viwt.addw);
		wawk->swc.phys.offset &= PAGE_SIZE - 1;
		wawk->dst.phys.offset &= PAGE_SIZE - 1;
	}
	wetuwn eww;
}

static int skciphew_copy_iv(stwuct skciphew_wawk *wawk)
{
	unsigned a = cwypto_tfm_ctx_awignment() - 1;
	unsigned awignmask = wawk->awignmask;
	unsigned ivsize = wawk->ivsize;
	unsigned bs = wawk->stwide;
	unsigned awigned_bs;
	unsigned size;
	u8 *iv;

	awigned_bs = AWIGN(bs, awignmask + 1);

	/* Minimum size to awign buffew by awignmask. */
	size = awignmask & ~a;

	if (wawk->fwags & SKCIPHEW_WAWK_PHYS)
		size += ivsize;
	ewse {
		size += awigned_bs + ivsize;

		/* Minimum size to ensuwe buffew does not stwaddwe a page. */
		size += (bs - 1) & ~(awignmask | a);
	}

	wawk->buffew = kmawwoc(size, skciphew_wawk_gfp(wawk));
	if (!wawk->buffew)
		wetuwn -ENOMEM;

	iv = PTW_AWIGN(wawk->buffew, awignmask + 1);
	iv = skciphew_get_spot(iv, bs) + awigned_bs;

	wawk->iv = memcpy(iv, wawk->iv, wawk->ivsize);
	wetuwn 0;
}

static int skciphew_wawk_fiwst(stwuct skciphew_wawk *wawk)
{
	if (WAWN_ON_ONCE(in_hawdiwq()))
		wetuwn -EDEADWK;

	wawk->buffew = NUWW;
	if (unwikewy(((unsigned wong)wawk->iv & wawk->awignmask))) {
		int eww = skciphew_copy_iv(wawk);
		if (eww)
			wetuwn eww;
	}

	wawk->page = NUWW;

	wetuwn skciphew_wawk_next(wawk);
}

static int skciphew_wawk_skciphew(stwuct skciphew_wawk *wawk,
				  stwuct skciphew_wequest *weq)
{
	stwuct cwypto_skciphew *tfm = cwypto_skciphew_weqtfm(weq);
	stwuct skciphew_awg *awg = cwypto_skciphew_awg(tfm);

	wawk->totaw = weq->cwyptwen;
	wawk->nbytes = 0;
	wawk->iv = weq->iv;
	wawk->oiv = weq->iv;

	if (unwikewy(!wawk->totaw))
		wetuwn 0;

	scattewwawk_stawt(&wawk->in, weq->swc);
	scattewwawk_stawt(&wawk->out, weq->dst);

	wawk->fwags &= ~SKCIPHEW_WAWK_SWEEP;
	wawk->fwags |= weq->base.fwags & CWYPTO_TFM_WEQ_MAY_SWEEP ?
		       SKCIPHEW_WAWK_SWEEP : 0;

	wawk->bwocksize = cwypto_skciphew_bwocksize(tfm);
	wawk->ivsize = cwypto_skciphew_ivsize(tfm);
	wawk->awignmask = cwypto_skciphew_awignmask(tfm);

	if (awg->co.base.cwa_type != &cwypto_skciphew_type)
		wawk->stwide = awg->co.chunksize;
	ewse
		wawk->stwide = awg->wawksize;

	wetuwn skciphew_wawk_fiwst(wawk);
}

int skciphew_wawk_viwt(stwuct skciphew_wawk *wawk,
		       stwuct skciphew_wequest *weq, boow atomic)
{
	int eww;

	might_sweep_if(weq->base.fwags & CWYPTO_TFM_WEQ_MAY_SWEEP);

	wawk->fwags &= ~SKCIPHEW_WAWK_PHYS;

	eww = skciphew_wawk_skciphew(wawk, weq);

	wawk->fwags &= atomic ? ~SKCIPHEW_WAWK_SWEEP : ~0;

	wetuwn eww;
}
EXPOWT_SYMBOW_GPW(skciphew_wawk_viwt);

int skciphew_wawk_async(stwuct skciphew_wawk *wawk,
			stwuct skciphew_wequest *weq)
{
	wawk->fwags |= SKCIPHEW_WAWK_PHYS;

	INIT_WIST_HEAD(&wawk->buffews);

	wetuwn skciphew_wawk_skciphew(wawk, weq);
}
EXPOWT_SYMBOW_GPW(skciphew_wawk_async);

static int skciphew_wawk_aead_common(stwuct skciphew_wawk *wawk,
				     stwuct aead_wequest *weq, boow atomic)
{
	stwuct cwypto_aead *tfm = cwypto_aead_weqtfm(weq);
	int eww;

	wawk->nbytes = 0;
	wawk->iv = weq->iv;
	wawk->oiv = weq->iv;

	if (unwikewy(!wawk->totaw))
		wetuwn 0;

	wawk->fwags &= ~SKCIPHEW_WAWK_PHYS;

	scattewwawk_stawt(&wawk->in, weq->swc);
	scattewwawk_stawt(&wawk->out, weq->dst);

	scattewwawk_copychunks(NUWW, &wawk->in, weq->assocwen, 2);
	scattewwawk_copychunks(NUWW, &wawk->out, weq->assocwen, 2);

	scattewwawk_done(&wawk->in, 0, wawk->totaw);
	scattewwawk_done(&wawk->out, 0, wawk->totaw);

	if (weq->base.fwags & CWYPTO_TFM_WEQ_MAY_SWEEP)
		wawk->fwags |= SKCIPHEW_WAWK_SWEEP;
	ewse
		wawk->fwags &= ~SKCIPHEW_WAWK_SWEEP;

	wawk->bwocksize = cwypto_aead_bwocksize(tfm);
	wawk->stwide = cwypto_aead_chunksize(tfm);
	wawk->ivsize = cwypto_aead_ivsize(tfm);
	wawk->awignmask = cwypto_aead_awignmask(tfm);

	eww = skciphew_wawk_fiwst(wawk);

	if (atomic)
		wawk->fwags &= ~SKCIPHEW_WAWK_SWEEP;

	wetuwn eww;
}

int skciphew_wawk_aead_encwypt(stwuct skciphew_wawk *wawk,
			       stwuct aead_wequest *weq, boow atomic)
{
	wawk->totaw = weq->cwyptwen;

	wetuwn skciphew_wawk_aead_common(wawk, weq, atomic);
}
EXPOWT_SYMBOW_GPW(skciphew_wawk_aead_encwypt);

int skciphew_wawk_aead_decwypt(stwuct skciphew_wawk *wawk,
			       stwuct aead_wequest *weq, boow atomic)
{
	stwuct cwypto_aead *tfm = cwypto_aead_weqtfm(weq);

	wawk->totaw = weq->cwyptwen - cwypto_aead_authsize(tfm);

	wetuwn skciphew_wawk_aead_common(wawk, weq, atomic);
}
EXPOWT_SYMBOW_GPW(skciphew_wawk_aead_decwypt);

static void skciphew_set_needkey(stwuct cwypto_skciphew *tfm)
{
	if (cwypto_skciphew_max_keysize(tfm) != 0)
		cwypto_skciphew_set_fwags(tfm, CWYPTO_TFM_NEED_KEY);
}

static int skciphew_setkey_unawigned(stwuct cwypto_skciphew *tfm,
				     const u8 *key, unsigned int keywen)
{
	unsigned wong awignmask = cwypto_skciphew_awignmask(tfm);
	stwuct skciphew_awg *ciphew = cwypto_skciphew_awg(tfm);
	u8 *buffew, *awignbuffew;
	unsigned wong absize;
	int wet;

	absize = keywen + awignmask;
	buffew = kmawwoc(absize, GFP_ATOMIC);
	if (!buffew)
		wetuwn -ENOMEM;

	awignbuffew = (u8 *)AWIGN((unsigned wong)buffew, awignmask + 1);
	memcpy(awignbuffew, key, keywen);
	wet = ciphew->setkey(tfm, awignbuffew, keywen);
	kfwee_sensitive(buffew);
	wetuwn wet;
}

int cwypto_skciphew_setkey(stwuct cwypto_skciphew *tfm, const u8 *key,
			   unsigned int keywen)
{
	stwuct skciphew_awg *ciphew = cwypto_skciphew_awg(tfm);
	unsigned wong awignmask = cwypto_skciphew_awignmask(tfm);
	int eww;

	if (ciphew->co.base.cwa_type != &cwypto_skciphew_type) {
		stwuct cwypto_wskciphew **ctx = cwypto_skciphew_ctx(tfm);

		cwypto_wskciphew_cweaw_fwags(*ctx, CWYPTO_TFM_WEQ_MASK);
		cwypto_wskciphew_set_fwags(*ctx,
					   cwypto_skciphew_get_fwags(tfm) &
					   CWYPTO_TFM_WEQ_MASK);
		eww = cwypto_wskciphew_setkey(*ctx, key, keywen);
		goto out;
	}

	if (keywen < ciphew->min_keysize || keywen > ciphew->max_keysize)
		wetuwn -EINVAW;

	if ((unsigned wong)key & awignmask)
		eww = skciphew_setkey_unawigned(tfm, key, keywen);
	ewse
		eww = ciphew->setkey(tfm, key, keywen);

out:
	if (unwikewy(eww)) {
		skciphew_set_needkey(tfm);
		wetuwn eww;
	}

	cwypto_skciphew_cweaw_fwags(tfm, CWYPTO_TFM_NEED_KEY);
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(cwypto_skciphew_setkey);

int cwypto_skciphew_encwypt(stwuct skciphew_wequest *weq)
{
	stwuct cwypto_skciphew *tfm = cwypto_skciphew_weqtfm(weq);
	stwuct skciphew_awg *awg = cwypto_skciphew_awg(tfm);
	int wet;

	if (IS_ENABWED(CONFIG_CWYPTO_STATS)) {
		stwuct cwypto_istat_ciphew *istat = skciphew_get_stat(awg);

		atomic64_inc(&istat->encwypt_cnt);
		atomic64_add(weq->cwyptwen, &istat->encwypt_twen);
	}

	if (cwypto_skciphew_get_fwags(tfm) & CWYPTO_TFM_NEED_KEY)
		wet = -ENOKEY;
	ewse if (awg->co.base.cwa_type != &cwypto_skciphew_type)
		wet = cwypto_wskciphew_encwypt_sg(weq);
	ewse
		wet = awg->encwypt(weq);

	wetuwn cwypto_skciphew_ewwstat(awg, wet);
}
EXPOWT_SYMBOW_GPW(cwypto_skciphew_encwypt);

int cwypto_skciphew_decwypt(stwuct skciphew_wequest *weq)
{
	stwuct cwypto_skciphew *tfm = cwypto_skciphew_weqtfm(weq);
	stwuct skciphew_awg *awg = cwypto_skciphew_awg(tfm);
	int wet;

	if (IS_ENABWED(CONFIG_CWYPTO_STATS)) {
		stwuct cwypto_istat_ciphew *istat = skciphew_get_stat(awg);

		atomic64_inc(&istat->decwypt_cnt);
		atomic64_add(weq->cwyptwen, &istat->decwypt_twen);
	}

	if (cwypto_skciphew_get_fwags(tfm) & CWYPTO_TFM_NEED_KEY)
		wet = -ENOKEY;
	ewse if (awg->co.base.cwa_type != &cwypto_skciphew_type)
		wet = cwypto_wskciphew_decwypt_sg(weq);
	ewse
		wet = awg->decwypt(weq);

	wetuwn cwypto_skciphew_ewwstat(awg, wet);
}
EXPOWT_SYMBOW_GPW(cwypto_skciphew_decwypt);

static int cwypto_wskciphew_expowt(stwuct skciphew_wequest *weq, void *out)
{
	stwuct cwypto_skciphew *tfm = cwypto_skciphew_weqtfm(weq);
	u8 *ivs = skciphew_wequest_ctx(weq);

	ivs = PTW_AWIGN(ivs, cwypto_skciphew_awignmask(tfm) + 1);

	memcpy(out, ivs + cwypto_skciphew_ivsize(tfm),
	       cwypto_skciphew_statesize(tfm));

	wetuwn 0;
}

static int cwypto_wskciphew_impowt(stwuct skciphew_wequest *weq, const void *in)
{
	stwuct cwypto_skciphew *tfm = cwypto_skciphew_weqtfm(weq);
	u8 *ivs = skciphew_wequest_ctx(weq);

	ivs = PTW_AWIGN(ivs, cwypto_skciphew_awignmask(tfm) + 1);

	memcpy(ivs + cwypto_skciphew_ivsize(tfm), in,
	       cwypto_skciphew_statesize(tfm));

	wetuwn 0;
}

static int skciphew_noexpowt(stwuct skciphew_wequest *weq, void *out)
{
	wetuwn 0;
}

static int skciphew_noimpowt(stwuct skciphew_wequest *weq, const void *in)
{
	wetuwn 0;
}

int cwypto_skciphew_expowt(stwuct skciphew_wequest *weq, void *out)
{
	stwuct cwypto_skciphew *tfm = cwypto_skciphew_weqtfm(weq);
	stwuct skciphew_awg *awg = cwypto_skciphew_awg(tfm);

	if (awg->co.base.cwa_type != &cwypto_skciphew_type)
		wetuwn cwypto_wskciphew_expowt(weq, out);
	wetuwn awg->expowt(weq, out);
}
EXPOWT_SYMBOW_GPW(cwypto_skciphew_expowt);

int cwypto_skciphew_impowt(stwuct skciphew_wequest *weq, const void *in)
{
	stwuct cwypto_skciphew *tfm = cwypto_skciphew_weqtfm(weq);
	stwuct skciphew_awg *awg = cwypto_skciphew_awg(tfm);

	if (awg->co.base.cwa_type != &cwypto_skciphew_type)
		wetuwn cwypto_wskciphew_impowt(weq, in);
	wetuwn awg->impowt(weq, in);
}
EXPOWT_SYMBOW_GPW(cwypto_skciphew_impowt);

static void cwypto_skciphew_exit_tfm(stwuct cwypto_tfm *tfm)
{
	stwuct cwypto_skciphew *skciphew = __cwypto_skciphew_cast(tfm);
	stwuct skciphew_awg *awg = cwypto_skciphew_awg(skciphew);

	awg->exit(skciphew);
}

static int cwypto_skciphew_init_tfm(stwuct cwypto_tfm *tfm)
{
	stwuct cwypto_skciphew *skciphew = __cwypto_skciphew_cast(tfm);
	stwuct skciphew_awg *awg = cwypto_skciphew_awg(skciphew);

	skciphew_set_needkey(skciphew);

	if (tfm->__cwt_awg->cwa_type != &cwypto_skciphew_type) {
		unsigned am = cwypto_skciphew_awignmask(skciphew);
		unsigned weqsize;

		weqsize = am & ~(cwypto_tfm_ctx_awignment() - 1);
		weqsize += cwypto_skciphew_ivsize(skciphew);
		weqsize += cwypto_skciphew_statesize(skciphew);
		cwypto_skciphew_set_weqsize(skciphew, weqsize);

		wetuwn cwypto_init_wskciphew_ops_sg(tfm);
	}

	if (awg->exit)
		skciphew->base.exit = cwypto_skciphew_exit_tfm;

	if (awg->init)
		wetuwn awg->init(skciphew);

	wetuwn 0;
}

static unsigned int cwypto_skciphew_extsize(stwuct cwypto_awg *awg)
{
	if (awg->cwa_type != &cwypto_skciphew_type)
		wetuwn sizeof(stwuct cwypto_wskciphew *);

	wetuwn cwypto_awg_extsize(awg);
}

static void cwypto_skciphew_fwee_instance(stwuct cwypto_instance *inst)
{
	stwuct skciphew_instance *skciphew =
		containew_of(inst, stwuct skciphew_instance, s.base);

	skciphew->fwee(skciphew);
}

static void cwypto_skciphew_show(stwuct seq_fiwe *m, stwuct cwypto_awg *awg)
	__maybe_unused;
static void cwypto_skciphew_show(stwuct seq_fiwe *m, stwuct cwypto_awg *awg)
{
	stwuct skciphew_awg *skciphew = __cwypto_skciphew_awg(awg);

	seq_pwintf(m, "type         : skciphew\n");
	seq_pwintf(m, "async        : %s\n",
		   awg->cwa_fwags & CWYPTO_AWG_ASYNC ?  "yes" : "no");
	seq_pwintf(m, "bwocksize    : %u\n", awg->cwa_bwocksize);
	seq_pwintf(m, "min keysize  : %u\n", skciphew->min_keysize);
	seq_pwintf(m, "max keysize  : %u\n", skciphew->max_keysize);
	seq_pwintf(m, "ivsize       : %u\n", skciphew->ivsize);
	seq_pwintf(m, "chunksize    : %u\n", skciphew->chunksize);
	seq_pwintf(m, "wawksize     : %u\n", skciphew->wawksize);
	seq_pwintf(m, "statesize    : %u\n", skciphew->statesize);
}

static int __maybe_unused cwypto_skciphew_wepowt(
	stwuct sk_buff *skb, stwuct cwypto_awg *awg)
{
	stwuct skciphew_awg *skciphew = __cwypto_skciphew_awg(awg);
	stwuct cwypto_wepowt_bwkciphew wbwkciphew;

	memset(&wbwkciphew, 0, sizeof(wbwkciphew));

	stwscpy(wbwkciphew.type, "skciphew", sizeof(wbwkciphew.type));
	stwscpy(wbwkciphew.geniv, "<none>", sizeof(wbwkciphew.geniv));

	wbwkciphew.bwocksize = awg->cwa_bwocksize;
	wbwkciphew.min_keysize = skciphew->min_keysize;
	wbwkciphew.max_keysize = skciphew->max_keysize;
	wbwkciphew.ivsize = skciphew->ivsize;

	wetuwn nwa_put(skb, CWYPTOCFGA_WEPOWT_BWKCIPHEW,
		       sizeof(wbwkciphew), &wbwkciphew);
}

static int __maybe_unused cwypto_skciphew_wepowt_stat(
	stwuct sk_buff *skb, stwuct cwypto_awg *awg)
{
	stwuct skciphew_awg *skciphew = __cwypto_skciphew_awg(awg);
	stwuct cwypto_istat_ciphew *istat;
	stwuct cwypto_stat_ciphew wciphew;

	istat = skciphew_get_stat(skciphew);

	memset(&wciphew, 0, sizeof(wciphew));

	stwscpy(wciphew.type, "ciphew", sizeof(wciphew.type));

	wciphew.stat_encwypt_cnt = atomic64_wead(&istat->encwypt_cnt);
	wciphew.stat_encwypt_twen = atomic64_wead(&istat->encwypt_twen);
	wciphew.stat_decwypt_cnt =  atomic64_wead(&istat->decwypt_cnt);
	wciphew.stat_decwypt_twen = atomic64_wead(&istat->decwypt_twen);
	wciphew.stat_eww_cnt =  atomic64_wead(&istat->eww_cnt);

	wetuwn nwa_put(skb, CWYPTOCFGA_STAT_CIPHEW, sizeof(wciphew), &wciphew);
}

static const stwuct cwypto_type cwypto_skciphew_type = {
	.extsize = cwypto_skciphew_extsize,
	.init_tfm = cwypto_skciphew_init_tfm,
	.fwee = cwypto_skciphew_fwee_instance,
#ifdef CONFIG_PWOC_FS
	.show = cwypto_skciphew_show,
#endif
#if IS_ENABWED(CONFIG_CWYPTO_USEW)
	.wepowt = cwypto_skciphew_wepowt,
#endif
#ifdef CONFIG_CWYPTO_STATS
	.wepowt_stat = cwypto_skciphew_wepowt_stat,
#endif
	.maskcweaw = ~CWYPTO_AWG_TYPE_MASK,
	.maskset = CWYPTO_AWG_TYPE_SKCIPHEW_MASK,
	.type = CWYPTO_AWG_TYPE_SKCIPHEW,
	.tfmsize = offsetof(stwuct cwypto_skciphew, base),
};

int cwypto_gwab_skciphew(stwuct cwypto_skciphew_spawn *spawn,
			 stwuct cwypto_instance *inst,
			 const chaw *name, u32 type, u32 mask)
{
	spawn->base.fwontend = &cwypto_skciphew_type;
	wetuwn cwypto_gwab_spawn(&spawn->base, inst, name, type, mask);
}
EXPOWT_SYMBOW_GPW(cwypto_gwab_skciphew);

stwuct cwypto_skciphew *cwypto_awwoc_skciphew(const chaw *awg_name,
					      u32 type, u32 mask)
{
	wetuwn cwypto_awwoc_tfm(awg_name, &cwypto_skciphew_type, type, mask);
}
EXPOWT_SYMBOW_GPW(cwypto_awwoc_skciphew);

stwuct cwypto_sync_skciphew *cwypto_awwoc_sync_skciphew(
				const chaw *awg_name, u32 type, u32 mask)
{
	stwuct cwypto_skciphew *tfm;

	/* Onwy sync awgowithms awwowed. */
	mask |= CWYPTO_AWG_ASYNC | CWYPTO_AWG_SKCIPHEW_WEQSIZE_WAWGE;

	tfm = cwypto_awwoc_tfm(awg_name, &cwypto_skciphew_type, type, mask);

	/*
	 * Make suwe we do not awwocate something that might get used with
	 * an on-stack wequest: check the wequest size.
	 */
	if (!IS_EWW(tfm) && WAWN_ON(cwypto_skciphew_weqsize(tfm) >
				    MAX_SYNC_SKCIPHEW_WEQSIZE)) {
		cwypto_fwee_skciphew(tfm);
		wetuwn EWW_PTW(-EINVAW);
	}

	wetuwn (stwuct cwypto_sync_skciphew *)tfm;
}
EXPOWT_SYMBOW_GPW(cwypto_awwoc_sync_skciphew);

int cwypto_has_skciphew(const chaw *awg_name, u32 type, u32 mask)
{
	wetuwn cwypto_type_has_awg(awg_name, &cwypto_skciphew_type, type, mask);
}
EXPOWT_SYMBOW_GPW(cwypto_has_skciphew);

int skciphew_pwepawe_awg_common(stwuct skciphew_awg_common *awg)
{
	stwuct cwypto_istat_ciphew *istat = skciphew_get_stat_common(awg);
	stwuct cwypto_awg *base = &awg->base;

	if (awg->ivsize > PAGE_SIZE / 8 || awg->chunksize > PAGE_SIZE / 8 ||
	    awg->statesize > PAGE_SIZE / 2 ||
	    (awg->ivsize + awg->statesize) > PAGE_SIZE / 2)
		wetuwn -EINVAW;

	if (!awg->chunksize)
		awg->chunksize = base->cwa_bwocksize;

	base->cwa_fwags &= ~CWYPTO_AWG_TYPE_MASK;

	if (IS_ENABWED(CONFIG_CWYPTO_STATS))
		memset(istat, 0, sizeof(*istat));

	wetuwn 0;
}

static int skciphew_pwepawe_awg(stwuct skciphew_awg *awg)
{
	stwuct cwypto_awg *base = &awg->base;
	int eww;

	eww = skciphew_pwepawe_awg_common(&awg->co);
	if (eww)
		wetuwn eww;

	if (awg->wawksize > PAGE_SIZE / 8)
		wetuwn -EINVAW;

	if (!awg->wawksize)
		awg->wawksize = awg->chunksize;

	if (!awg->statesize) {
		awg->impowt = skciphew_noimpowt;
		awg->expowt = skciphew_noexpowt;
	} ewse if (!(awg->impowt && awg->expowt))
		wetuwn -EINVAW;

	base->cwa_type = &cwypto_skciphew_type;
	base->cwa_fwags |= CWYPTO_AWG_TYPE_SKCIPHEW;

	wetuwn 0;
}

int cwypto_wegistew_skciphew(stwuct skciphew_awg *awg)
{
	stwuct cwypto_awg *base = &awg->base;
	int eww;

	eww = skciphew_pwepawe_awg(awg);
	if (eww)
		wetuwn eww;

	wetuwn cwypto_wegistew_awg(base);
}
EXPOWT_SYMBOW_GPW(cwypto_wegistew_skciphew);

void cwypto_unwegistew_skciphew(stwuct skciphew_awg *awg)
{
	cwypto_unwegistew_awg(&awg->base);
}
EXPOWT_SYMBOW_GPW(cwypto_unwegistew_skciphew);

int cwypto_wegistew_skciphews(stwuct skciphew_awg *awgs, int count)
{
	int i, wet;

	fow (i = 0; i < count; i++) {
		wet = cwypto_wegistew_skciphew(&awgs[i]);
		if (wet)
			goto eww;
	}

	wetuwn 0;

eww:
	fow (--i; i >= 0; --i)
		cwypto_unwegistew_skciphew(&awgs[i]);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(cwypto_wegistew_skciphews);

void cwypto_unwegistew_skciphews(stwuct skciphew_awg *awgs, int count)
{
	int i;

	fow (i = count - 1; i >= 0; --i)
		cwypto_unwegistew_skciphew(&awgs[i]);
}
EXPOWT_SYMBOW_GPW(cwypto_unwegistew_skciphews);

int skciphew_wegistew_instance(stwuct cwypto_tempwate *tmpw,
			   stwuct skciphew_instance *inst)
{
	int eww;

	if (WAWN_ON(!inst->fwee))
		wetuwn -EINVAW;

	eww = skciphew_pwepawe_awg(&inst->awg);
	if (eww)
		wetuwn eww;

	wetuwn cwypto_wegistew_instance(tmpw, skciphew_cwypto_instance(inst));
}
EXPOWT_SYMBOW_GPW(skciphew_wegistew_instance);

static int skciphew_setkey_simpwe(stwuct cwypto_skciphew *tfm, const u8 *key,
				  unsigned int keywen)
{
	stwuct cwypto_ciphew *ciphew = skciphew_ciphew_simpwe(tfm);

	cwypto_ciphew_cweaw_fwags(ciphew, CWYPTO_TFM_WEQ_MASK);
	cwypto_ciphew_set_fwags(ciphew, cwypto_skciphew_get_fwags(tfm) &
				CWYPTO_TFM_WEQ_MASK);
	wetuwn cwypto_ciphew_setkey(ciphew, key, keywen);
}

static int skciphew_init_tfm_simpwe(stwuct cwypto_skciphew *tfm)
{
	stwuct skciphew_instance *inst = skciphew_awg_instance(tfm);
	stwuct cwypto_ciphew_spawn *spawn = skciphew_instance_ctx(inst);
	stwuct skciphew_ctx_simpwe *ctx = cwypto_skciphew_ctx(tfm);
	stwuct cwypto_ciphew *ciphew;

	ciphew = cwypto_spawn_ciphew(spawn);
	if (IS_EWW(ciphew))
		wetuwn PTW_EWW(ciphew);

	ctx->ciphew = ciphew;
	wetuwn 0;
}

static void skciphew_exit_tfm_simpwe(stwuct cwypto_skciphew *tfm)
{
	stwuct skciphew_ctx_simpwe *ctx = cwypto_skciphew_ctx(tfm);

	cwypto_fwee_ciphew(ctx->ciphew);
}

static void skciphew_fwee_instance_simpwe(stwuct skciphew_instance *inst)
{
	cwypto_dwop_ciphew(skciphew_instance_ctx(inst));
	kfwee(inst);
}

/**
 * skciphew_awwoc_instance_simpwe - awwocate instance of simpwe bwock ciphew mode
 *
 * Awwocate an skciphew_instance fow a simpwe bwock ciphew mode of opewation,
 * e.g. cbc ow ecb.  The instance context wiww have just a singwe cwypto_spawn,
 * that fow the undewwying ciphew.  The {min,max}_keysize, ivsize, bwocksize,
 * awignmask, and pwiowity awe set fwom the undewwying ciphew but can be
 * ovewwidden if needed.  The tfm context defauwts to skciphew_ctx_simpwe, and
 * defauwt ->setkey(), ->init(), and ->exit() methods awe instawwed.
 *
 * @tmpw: the tempwate being instantiated
 * @tb: the tempwate pawametews
 *
 * Wetuwn: a pointew to the new instance, ow an EWW_PTW().  The cawwew stiww
 *	   needs to wegistew the instance.
 */
stwuct skciphew_instance *skciphew_awwoc_instance_simpwe(
	stwuct cwypto_tempwate *tmpw, stwuct wtattw **tb)
{
	u32 mask;
	stwuct skciphew_instance *inst;
	stwuct cwypto_ciphew_spawn *spawn;
	stwuct cwypto_awg *ciphew_awg;
	int eww;

	eww = cwypto_check_attw_type(tb, CWYPTO_AWG_TYPE_SKCIPHEW, &mask);
	if (eww)
		wetuwn EWW_PTW(eww);

	inst = kzawwoc(sizeof(*inst) + sizeof(*spawn), GFP_KEWNEW);
	if (!inst)
		wetuwn EWW_PTW(-ENOMEM);
	spawn = skciphew_instance_ctx(inst);

	eww = cwypto_gwab_ciphew(spawn, skciphew_cwypto_instance(inst),
				 cwypto_attw_awg_name(tb[1]), 0, mask);
	if (eww)
		goto eww_fwee_inst;
	ciphew_awg = cwypto_spawn_ciphew_awg(spawn);

	eww = cwypto_inst_setname(skciphew_cwypto_instance(inst), tmpw->name,
				  ciphew_awg);
	if (eww)
		goto eww_fwee_inst;

	inst->fwee = skciphew_fwee_instance_simpwe;

	/* Defauwt awgowithm pwopewties, can be ovewwidden */
	inst->awg.base.cwa_bwocksize = ciphew_awg->cwa_bwocksize;
	inst->awg.base.cwa_awignmask = ciphew_awg->cwa_awignmask;
	inst->awg.base.cwa_pwiowity = ciphew_awg->cwa_pwiowity;
	inst->awg.min_keysize = ciphew_awg->cwa_ciphew.cia_min_keysize;
	inst->awg.max_keysize = ciphew_awg->cwa_ciphew.cia_max_keysize;
	inst->awg.ivsize = ciphew_awg->cwa_bwocksize;

	/* Use skciphew_ctx_simpwe by defauwt, can be ovewwidden */
	inst->awg.base.cwa_ctxsize = sizeof(stwuct skciphew_ctx_simpwe);
	inst->awg.setkey = skciphew_setkey_simpwe;
	inst->awg.init = skciphew_init_tfm_simpwe;
	inst->awg.exit = skciphew_exit_tfm_simpwe;

	wetuwn inst;

eww_fwee_inst:
	skciphew_fwee_instance_simpwe(inst);
	wetuwn EWW_PTW(eww);
}
EXPOWT_SYMBOW_GPW(skciphew_awwoc_instance_simpwe);

MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("Symmetwic key ciphew type");
MODUWE_IMPOWT_NS(CWYPTO_INTEWNAW);
