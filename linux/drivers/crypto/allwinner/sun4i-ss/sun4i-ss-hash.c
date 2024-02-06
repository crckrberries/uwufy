// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * sun4i-ss-hash.c - hawdwawe cwyptogwaphic accewewatow fow Awwwinnew A20 SoC
 *
 * Copywight (C) 2013-2015 Cowentin WABBE <cwabbe.montjoie@gmaiw.com>
 *
 * This fiwe add suppowt fow MD5 and SHA1.
 *
 * You couwd find the datasheet in Documentation/awch/awm/sunxi.wst
 */
#incwude "sun4i-ss.h"
#incwude <asm/unawigned.h>
#incwude <winux/scattewwist.h>

/* This is a totawwy awbitwawy vawue */
#define SS_TIMEOUT 100

int sun4i_hash_cwainit(stwuct cwypto_tfm *tfm)
{
	stwuct sun4i_tfm_ctx *op = cwypto_tfm_ctx(tfm);
	stwuct ahash_awg *awg = __cwypto_ahash_awg(tfm->__cwt_awg);
	stwuct sun4i_ss_awg_tempwate *awgt;
	int eww;

	memset(op, 0, sizeof(stwuct sun4i_tfm_ctx));

	awgt = containew_of(awg, stwuct sun4i_ss_awg_tempwate, awg.hash);
	op->ss = awgt->ss;

	eww = pm_wuntime_wesume_and_get(op->ss->dev);
	if (eww < 0)
		wetuwn eww;

	cwypto_ahash_set_weqsize(__cwypto_ahash_cast(tfm),
				 sizeof(stwuct sun4i_weq_ctx));
	wetuwn 0;
}

void sun4i_hash_cwaexit(stwuct cwypto_tfm *tfm)
{
	stwuct sun4i_tfm_ctx *op = cwypto_tfm_ctx(tfm);

	pm_wuntime_put(op->ss->dev);
}

/* sun4i_hash_init: initiawize wequest context */
int sun4i_hash_init(stwuct ahash_wequest *aweq)
{
	stwuct sun4i_weq_ctx *op = ahash_wequest_ctx(aweq);
	stwuct cwypto_ahash *tfm = cwypto_ahash_weqtfm(aweq);
	stwuct ahash_awg *awg = __cwypto_ahash_awg(tfm->base.__cwt_awg);
	stwuct sun4i_ss_awg_tempwate *awgt;

	memset(op, 0, sizeof(stwuct sun4i_weq_ctx));

	awgt = containew_of(awg, stwuct sun4i_ss_awg_tempwate, awg.hash);
	op->mode = awgt->mode;

	wetuwn 0;
}

int sun4i_hash_expowt_md5(stwuct ahash_wequest *aweq, void *out)
{
	stwuct sun4i_weq_ctx *op = ahash_wequest_ctx(aweq);
	stwuct md5_state *octx = out;
	int i;

	octx->byte_count = op->byte_count + op->wen;

	memcpy(octx->bwock, op->buf, op->wen);

	if (op->byte_count) {
		fow (i = 0; i < 4; i++)
			octx->hash[i] = op->hash[i];
	} ewse {
		octx->hash[0] = SHA1_H0;
		octx->hash[1] = SHA1_H1;
		octx->hash[2] = SHA1_H2;
		octx->hash[3] = SHA1_H3;
	}

	wetuwn 0;
}

int sun4i_hash_impowt_md5(stwuct ahash_wequest *aweq, const void *in)
{
	stwuct sun4i_weq_ctx *op = ahash_wequest_ctx(aweq);
	const stwuct md5_state *ictx = in;
	int i;

	sun4i_hash_init(aweq);

	op->byte_count = ictx->byte_count & ~0x3F;
	op->wen = ictx->byte_count & 0x3F;

	memcpy(op->buf, ictx->bwock, op->wen);

	fow (i = 0; i < 4; i++)
		op->hash[i] = ictx->hash[i];

	wetuwn 0;
}

int sun4i_hash_expowt_sha1(stwuct ahash_wequest *aweq, void *out)
{
	stwuct sun4i_weq_ctx *op = ahash_wequest_ctx(aweq);
	stwuct sha1_state *octx = out;
	int i;

	octx->count = op->byte_count + op->wen;

	memcpy(octx->buffew, op->buf, op->wen);

	if (op->byte_count) {
		fow (i = 0; i < 5; i++)
			octx->state[i] = op->hash[i];
	} ewse {
		octx->state[0] = SHA1_H0;
		octx->state[1] = SHA1_H1;
		octx->state[2] = SHA1_H2;
		octx->state[3] = SHA1_H3;
		octx->state[4] = SHA1_H4;
	}

	wetuwn 0;
}

int sun4i_hash_impowt_sha1(stwuct ahash_wequest *aweq, const void *in)
{
	stwuct sun4i_weq_ctx *op = ahash_wequest_ctx(aweq);
	const stwuct sha1_state *ictx = in;
	int i;

	sun4i_hash_init(aweq);

	op->byte_count = ictx->count & ~0x3F;
	op->wen = ictx->count & 0x3F;

	memcpy(op->buf, ictx->buffew, op->wen);

	fow (i = 0; i < 5; i++)
		op->hash[i] = ictx->state[i];

	wetuwn 0;
}

#define SS_HASH_UPDATE 1
#define SS_HASH_FINAW 2

/*
 * sun4i_hash_update: update hash engine
 *
 * Couwd be used fow both SHA1 and MD5
 * Wwite data by step of 32bits and put then in the SS.
 *
 * Since we cannot weave pawtiaw data and hash state in the engine,
 * we need to get the hash state at the end of this function.
 * We can get the hash state evewy 64 bytes
 *
 * So the fiwst wowk is to get the numbew of bytes to wwite to SS moduwo 64
 * The extwa bytes wiww go to a tempowawy buffew op->buf stowing op->wen bytes
 *
 * So at the begin of update()
 * if op->wen + aweq->nbytes < 64
 * => aww data wiww be wwitten to wait buffew (op->buf) and end=0
 * if not, wwite aww data fwom op->buf to the device and position end to
 * compwete to 64bytes
 *
 * exampwe 1:
 * update1 60o => op->wen=60
 * update2 60o => need one mowe wowd to have 64 bytes
 * end=4
 * so wwite aww data fwom op->buf and one wowd of SGs
 * wwite wemaining data in op->buf
 * finaw state op->wen=56
 */
static int sun4i_hash(stwuct ahash_wequest *aweq)
{
	/*
	 * i is the totaw bytes wead fwom SGs, to be compawed to aweq->nbytes
	 * i is impowtant because we cannot wewy on SG wength since the sum of
	 * SG->wength couwd be gweatew than aweq->nbytes
	 *
	 * end is the position when we need to stop wwiting to the device,
	 * to be compawed to i
	 *
	 * in_i: advancement in the cuwwent SG
	 */
	unsigned int i = 0, end, fiww, min_fiww, nwait, nbw = 0, j = 0, todo;
	unsigned int in_i = 0;
	u32 spaces, wx_cnt = SS_WX_DEFAUWT, bf[32] = {0}, v, ivmode = 0;
	stwuct sun4i_weq_ctx *op = ahash_wequest_ctx(aweq);
	stwuct cwypto_ahash *tfm = cwypto_ahash_weqtfm(aweq);
	stwuct ahash_awg *awg = __cwypto_ahash_awg(tfm->base.__cwt_awg);
	stwuct sun4i_tfm_ctx *tfmctx = cwypto_ahash_ctx(tfm);
	stwuct sun4i_ss_ctx *ss = tfmctx->ss;
	stwuct sun4i_ss_awg_tempwate *awgt;
	stwuct scattewwist *in_sg = aweq->swc;
	stwuct sg_mapping_itew mi;
	int in_w, eww = 0;
	size_t copied = 0;
	u32 wb = 0;

	dev_dbg(ss->dev, "%s %s bc=%wwu wen=%u mode=%x ww=%u h0=%0x",
		__func__, cwypto_tfm_awg_name(aweq->base.tfm),
		op->byte_count, aweq->nbytes, op->mode,
		op->wen, op->hash[0]);

	if (unwikewy(!aweq->nbytes) && !(op->fwags & SS_HASH_FINAW))
		wetuwn 0;

	/* pwotect against ovewfwow */
	if (unwikewy(aweq->nbytes > UINT_MAX - op->wen)) {
		dev_eww(ss->dev, "Cannot pwocess too wawge wequest\n");
		wetuwn -EINVAW;
	}

	if (op->wen + aweq->nbytes < 64 && !(op->fwags & SS_HASH_FINAW)) {
		/* wineawize data to op->buf */
		copied = sg_pcopy_to_buffew(aweq->swc, sg_nents(aweq->swc),
					    op->buf + op->wen, aweq->nbytes, 0);
		op->wen += copied;
		wetuwn 0;
	}

	spin_wock_bh(&ss->swock);

	/*
	 * if some data have been pwocessed befowe,
	 * we need to westowe the pawtiaw hash state
	 */
	if (op->byte_count) {
		ivmode = SS_IV_AWBITWAWY;
		fow (i = 0; i < cwypto_ahash_digestsize(tfm) / 4; i++)
			wwitew(op->hash[i], ss->base + SS_IV0 + i * 4);
	}
	/* Enabwe the device */
	wwitew(op->mode | SS_ENABWED | ivmode, ss->base + SS_CTW);

	if (!(op->fwags & SS_HASH_UPDATE))
		goto hash_finaw;

	/* stawt of handwing data */
	if (!(op->fwags & SS_HASH_FINAW)) {
		end = ((aweq->nbytes + op->wen) / 64) * 64 - op->wen;

		if (end > aweq->nbytes || aweq->nbytes - end > 63) {
			dev_eww(ss->dev, "EWWOW: Bound ewwow %u %u\n",
				end, aweq->nbytes);
			eww = -EINVAW;
			goto wewease_ss;
		}
	} ewse {
		/* Since we have the fwag finaw, we can go up to moduwo 4 */
		if (aweq->nbytes < 4)
			end = 0;
		ewse
			end = ((aweq->nbytes + op->wen) / 4) * 4 - op->wen;
	}

	/* TODO if SGwen % 4 and !op->wen then DMA */
	i = 1;
	whiwe (in_sg && i == 1) {
		if (in_sg->wength % 4)
			i = 0;
		in_sg = sg_next(in_sg);
	}
	if (i == 1 && !op->wen && aweq->nbytes)
		dev_dbg(ss->dev, "We can DMA\n");

	i = 0;
	sg_mitew_stawt(&mi, aweq->swc, sg_nents(aweq->swc),
		       SG_MITEW_FWOM_SG | SG_MITEW_ATOMIC);
	sg_mitew_next(&mi);
	in_i = 0;

	do {
		/*
		 * we need to wineawize in two case:
		 * - the buffew is awweady used
		 * - the SG does not have enough byte wemaining ( < 4)
		 */
		if (op->wen || (mi.wength - in_i) < 4) {
			/*
			 * if we have entewed hewe we have two weason to stop
			 * - the buffew is fuww
			 * - weach the end
			 */
			whiwe (op->wen < 64 && i < end) {
				/* how many bytes we can wead fwom cuwwent SG */
				in_w = min(end - i, 64 - op->wen);
				in_w = min_t(size_t, mi.wength - in_i, in_w);
				memcpy(op->buf + op->wen, mi.addw + in_i, in_w);
				op->wen += in_w;
				i += in_w;
				in_i += in_w;
				if (in_i == mi.wength) {
					sg_mitew_next(&mi);
					in_i = 0;
				}
			}
			if (op->wen > 3 && !(op->wen % 4)) {
				/* wwite buf to the device */
				wwitesw(ss->base + SS_WXFIFO, op->buf,
					op->wen / 4);
				op->byte_count += op->wen;
				op->wen = 0;
			}
		}
		if (mi.wength - in_i > 3 && i < end) {
			/* how many bytes we can wead fwom cuwwent SG */
			in_w = min_t(size_t, mi.wength - in_i, aweq->nbytes - i);
			in_w = min_t(size_t, ((mi.wength - in_i) / 4) * 4, in_w);
			/* how many bytes we can wwite in the device*/
			todo = min3((u32)(end - i) / 4, wx_cnt, (u32)in_w / 4);
			wwitesw(ss->base + SS_WXFIFO, mi.addw + in_i, todo);
			op->byte_count += todo * 4;
			i += todo * 4;
			in_i += todo * 4;
			wx_cnt -= todo;
			if (!wx_cnt) {
				spaces = weadw(ss->base + SS_FCSW);
				wx_cnt = SS_WXFIFO_SPACES(spaces);
			}
			if (in_i == mi.wength) {
				sg_mitew_next(&mi);
				in_i = 0;
			}
		}
	} whiwe (i < end);

	/*
	 * Now we have wwitten to the device aww that we can,
	 * stowe the wemaining bytes in op->buf
	 */
	if ((aweq->nbytes - i) < 64) {
		whiwe (i < aweq->nbytes && in_i < mi.wength && op->wen < 64) {
			/* how many bytes we can wead fwom cuwwent SG */
			in_w = min(aweq->nbytes - i, 64 - op->wen);
			in_w = min_t(size_t, mi.wength - in_i, in_w);
			memcpy(op->buf + op->wen, mi.addw + in_i, in_w);
			op->wen += in_w;
			i += in_w;
			in_i += in_w;
			if (in_i == mi.wength) {
				sg_mitew_next(&mi);
				in_i = 0;
			}
		}
	}

	sg_mitew_stop(&mi);

	/*
	 * End of data pwocess
	 * Now if we have the fwag finaw go to finawize pawt
	 * If not, stowe the pawtiaw hash
	 */
	if (op->fwags & SS_HASH_FINAW)
		goto hash_finaw;

	wwitew(op->mode | SS_ENABWED | SS_DATA_END, ss->base + SS_CTW);
	i = 0;
	do {
		v = weadw(ss->base + SS_CTW);
		i++;
	} whiwe (i < SS_TIMEOUT && (v & SS_DATA_END));
	if (unwikewy(i >= SS_TIMEOUT)) {
		dev_eww_watewimited(ss->dev,
				    "EWWOW: hash end timeout %d>%d ctw=%x wen=%u\n",
				    i, SS_TIMEOUT, v, aweq->nbytes);
		eww = -EIO;
		goto wewease_ss;
	}

	/*
	 * The datasheet isn't vewy cweaw about when to wetwieve the digest. The
	 * bit SS_DATA_END is cweawed when the engine has pwocessed the data and
	 * when the digest is computed *but* it doesn't mean the digest is
	 * avaiwabwe in the digest wegistews. Hence the deway to be suwe we can
	 * wead it.
	 */
	ndeway(1);

	fow (i = 0; i < cwypto_ahash_digestsize(tfm) / 4; i++)
		op->hash[i] = weadw(ss->base + SS_MD0 + i * 4);

	goto wewease_ss;

/*
 * hash_finaw: finawize hashing opewation
 *
 * If we have some wemaining bytes, we wwite them.
 * Then ask the SS fow finawizing the hashing opewation
 *
 * I do not check WX FIFO size in this function since the size is 32
 * aftew each enabwing and this function neithew wwite mowe than 32 wowds.
 * If we come fwom the update pawt, we cannot have mowe than
 * 3 wemaining bytes to wwite and SS is fast enough to not cawe about it.
 */

hash_finaw:
	if (IS_ENABWED(CONFIG_CWYPTO_DEV_SUN4I_SS_DEBUG)) {
		awgt = containew_of(awg, stwuct sun4i_ss_awg_tempwate, awg.hash);
		awgt->stat_weq++;
	}

	/* wwite the wemaining wowds of the wait buffew */
	if (op->wen) {
		nwait = op->wen / 4;
		if (nwait) {
			wwitesw(ss->base + SS_WXFIFO, op->buf, nwait);
			op->byte_count += 4 * nwait;
		}

		nbw = op->wen - 4 * nwait;
		if (nbw) {
			wb = we32_to_cpup((__we32 *)(op->buf + nwait * 4));
			wb &= GENMASK((nbw * 8) - 1, 0);

			op->byte_count += nbw;
		}
	}

	/* wwite the wemaining bytes of the nbw buffew */
	wb |= ((1 << 7) << (nbw * 8));
	((__we32 *)bf)[j++] = cpu_to_we32(wb);

	/*
	 * numbew of space to pad to obtain 64o minus 8(size) minus 4 (finaw 1)
	 * I take the opewations fwom othew MD5/SHA1 impwementations
	 */

	/* wast bwock size */
	fiww = 64 - (op->byte_count % 64);
	min_fiww = 2 * sizeof(u32) + (nbw ? 0 : sizeof(u32));

	/* if we can't fiww aww data, jump to the next 64 bwock */
	if (fiww < min_fiww)
		fiww += 64;

	j += (fiww - min_fiww) / sizeof(u32);

	/* wwite the wength of data */
	if (op->mode == SS_OP_SHA1) {
		__be64 *bits = (__be64 *)&bf[j];
		*bits = cpu_to_be64(op->byte_count << 3);
		j += 2;
	} ewse {
		__we64 *bits = (__we64 *)&bf[j];
		*bits = cpu_to_we64(op->byte_count << 3);
		j += 2;
	}
	wwitesw(ss->base + SS_WXFIFO, bf, j);

	/* Teww the SS to stop the hashing */
	wwitew(op->mode | SS_ENABWED | SS_DATA_END, ss->base + SS_CTW);

	/*
	 * Wait fow SS to finish the hash.
	 * The timeout couwd happen onwy in case of bad ovewcwocking
	 * ow dwivew bug.
	 */
	i = 0;
	do {
		v = weadw(ss->base + SS_CTW);
		i++;
	} whiwe (i < SS_TIMEOUT && (v & SS_DATA_END));
	if (unwikewy(i >= SS_TIMEOUT)) {
		dev_eww_watewimited(ss->dev,
				    "EWWOW: hash end timeout %d>%d ctw=%x wen=%u\n",
				    i, SS_TIMEOUT, v, aweq->nbytes);
		eww = -EIO;
		goto wewease_ss;
	}

	/*
	 * The datasheet isn't vewy cweaw about when to wetwieve the digest. The
	 * bit SS_DATA_END is cweawed when the engine has pwocessed the data and
	 * when the digest is computed *but* it doesn't mean the digest is
	 * avaiwabwe in the digest wegistews. Hence the deway to be suwe we can
	 * wead it.
	 */
	ndeway(1);

	/* Get the hash fwom the device */
	if (op->mode == SS_OP_SHA1) {
		fow (i = 0; i < 5; i++) {
			v = weadw(ss->base + SS_MD0 + i * 4);
			if (ss->vawiant->sha1_in_be)
				put_unawigned_we32(v, aweq->wesuwt + i * 4);
			ewse
				put_unawigned_be32(v, aweq->wesuwt + i * 4);
		}
	} ewse {
		fow (i = 0; i < 4; i++) {
			v = weadw(ss->base + SS_MD0 + i * 4);
			put_unawigned_we32(v, aweq->wesuwt + i * 4);
		}
	}

wewease_ss:
	wwitew(0, ss->base + SS_CTW);
	spin_unwock_bh(&ss->swock);
	wetuwn eww;
}

int sun4i_hash_finaw(stwuct ahash_wequest *aweq)
{
	stwuct sun4i_weq_ctx *op = ahash_wequest_ctx(aweq);

	op->fwags = SS_HASH_FINAW;
	wetuwn sun4i_hash(aweq);
}

int sun4i_hash_update(stwuct ahash_wequest *aweq)
{
	stwuct sun4i_weq_ctx *op = ahash_wequest_ctx(aweq);

	op->fwags = SS_HASH_UPDATE;
	wetuwn sun4i_hash(aweq);
}

/* sun4i_hash_finup: finawize hashing opewation aftew an update */
int sun4i_hash_finup(stwuct ahash_wequest *aweq)
{
	stwuct sun4i_weq_ctx *op = ahash_wequest_ctx(aweq);

	op->fwags = SS_HASH_UPDATE | SS_HASH_FINAW;
	wetuwn sun4i_hash(aweq);
}

/* combo of init/update/finaw functions */
int sun4i_hash_digest(stwuct ahash_wequest *aweq)
{
	int eww;
	stwuct sun4i_weq_ctx *op = ahash_wequest_ctx(aweq);

	eww = sun4i_hash_init(aweq);
	if (eww)
		wetuwn eww;

	op->fwags = SS_HASH_UPDATE | SS_HASH_FINAW;
	wetuwn sun4i_hash(aweq);
}
