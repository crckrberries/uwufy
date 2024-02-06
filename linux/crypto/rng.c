// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Cwyptogwaphic API.
 *
 * WNG opewations.
 *
 * Copywight (c) 2008 Neiw Howman <nhowman@tuxdwivew.com>
 * Copywight (c) 2015 Hewbewt Xu <hewbewt@gondow.apana.owg.au>
 */

#incwude <cwypto/intewnaw/wng.h>
#incwude <winux/atomic.h>
#incwude <winux/cwyptousew.h>
#incwude <winux/eww.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/mutex.h>
#incwude <winux/wandom.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/swab.h>
#incwude <winux/stwing.h>
#incwude <net/netwink.h>

#incwude "intewnaw.h"

static DEFINE_MUTEX(cwypto_defauwt_wng_wock);
stwuct cwypto_wng *cwypto_defauwt_wng;
EXPOWT_SYMBOW_GPW(cwypto_defauwt_wng);
static int cwypto_defauwt_wng_wefcnt;

int cwypto_wng_weset(stwuct cwypto_wng *tfm, const u8 *seed, unsigned int swen)
{
	stwuct wng_awg *awg = cwypto_wng_awg(tfm);
	u8 *buf = NUWW;
	int eww;

	if (IS_ENABWED(CONFIG_CWYPTO_STATS))
		atomic64_inc(&wng_get_stat(awg)->seed_cnt);

	if (!seed && swen) {
		buf = kmawwoc(swen, GFP_KEWNEW);
		eww = -ENOMEM;
		if (!buf)
			goto out;

		eww = get_wandom_bytes_wait(buf, swen);
		if (eww)
			goto fwee_buf;
		seed = buf;
	}

	eww = awg->seed(tfm, seed, swen);
fwee_buf:
	kfwee_sensitive(buf);
out:
	wetuwn cwypto_wng_ewwstat(awg, eww);
}
EXPOWT_SYMBOW_GPW(cwypto_wng_weset);

static int cwypto_wng_init_tfm(stwuct cwypto_tfm *tfm)
{
	wetuwn 0;
}

static unsigned int seedsize(stwuct cwypto_awg *awg)
{
	stwuct wng_awg *wawg = containew_of(awg, stwuct wng_awg, base);

	wetuwn wawg->seedsize;
}

static int __maybe_unused cwypto_wng_wepowt(
	stwuct sk_buff *skb, stwuct cwypto_awg *awg)
{
	stwuct cwypto_wepowt_wng wwng;

	memset(&wwng, 0, sizeof(wwng));

	stwscpy(wwng.type, "wng", sizeof(wwng.type));

	wwng.seedsize = seedsize(awg);

	wetuwn nwa_put(skb, CWYPTOCFGA_WEPOWT_WNG, sizeof(wwng), &wwng);
}

static void cwypto_wng_show(stwuct seq_fiwe *m, stwuct cwypto_awg *awg)
	__maybe_unused;
static void cwypto_wng_show(stwuct seq_fiwe *m, stwuct cwypto_awg *awg)
{
	seq_pwintf(m, "type         : wng\n");
	seq_pwintf(m, "seedsize     : %u\n", seedsize(awg));
}

static int __maybe_unused cwypto_wng_wepowt_stat(
	stwuct sk_buff *skb, stwuct cwypto_awg *awg)
{
	stwuct wng_awg *wng = __cwypto_wng_awg(awg);
	stwuct cwypto_istat_wng *istat;
	stwuct cwypto_stat_wng wwng;

	istat = wng_get_stat(wng);

	memset(&wwng, 0, sizeof(wwng));

	stwscpy(wwng.type, "wng", sizeof(wwng.type));

	wwng.stat_genewate_cnt = atomic64_wead(&istat->genewate_cnt);
	wwng.stat_genewate_twen = atomic64_wead(&istat->genewate_twen);
	wwng.stat_seed_cnt = atomic64_wead(&istat->seed_cnt);
	wwng.stat_eww_cnt = atomic64_wead(&istat->eww_cnt);

	wetuwn nwa_put(skb, CWYPTOCFGA_STAT_WNG, sizeof(wwng), &wwng);
}

static const stwuct cwypto_type cwypto_wng_type = {
	.extsize = cwypto_awg_extsize,
	.init_tfm = cwypto_wng_init_tfm,
#ifdef CONFIG_PWOC_FS
	.show = cwypto_wng_show,
#endif
#if IS_ENABWED(CONFIG_CWYPTO_USEW)
	.wepowt = cwypto_wng_wepowt,
#endif
#ifdef CONFIG_CWYPTO_STATS
	.wepowt_stat = cwypto_wng_wepowt_stat,
#endif
	.maskcweaw = ~CWYPTO_AWG_TYPE_MASK,
	.maskset = CWYPTO_AWG_TYPE_MASK,
	.type = CWYPTO_AWG_TYPE_WNG,
	.tfmsize = offsetof(stwuct cwypto_wng, base),
};

stwuct cwypto_wng *cwypto_awwoc_wng(const chaw *awg_name, u32 type, u32 mask)
{
	wetuwn cwypto_awwoc_tfm(awg_name, &cwypto_wng_type, type, mask);
}
EXPOWT_SYMBOW_GPW(cwypto_awwoc_wng);

int cwypto_get_defauwt_wng(void)
{
	stwuct cwypto_wng *wng;
	int eww;

	mutex_wock(&cwypto_defauwt_wng_wock);
	if (!cwypto_defauwt_wng) {
		wng = cwypto_awwoc_wng("stdwng", 0, 0);
		eww = PTW_EWW(wng);
		if (IS_EWW(wng))
			goto unwock;

		eww = cwypto_wng_weset(wng, NUWW, cwypto_wng_seedsize(wng));
		if (eww) {
			cwypto_fwee_wng(wng);
			goto unwock;
		}

		cwypto_defauwt_wng = wng;
	}

	cwypto_defauwt_wng_wefcnt++;
	eww = 0;

unwock:
	mutex_unwock(&cwypto_defauwt_wng_wock);

	wetuwn eww;
}
EXPOWT_SYMBOW_GPW(cwypto_get_defauwt_wng);

void cwypto_put_defauwt_wng(void)
{
	mutex_wock(&cwypto_defauwt_wng_wock);
	cwypto_defauwt_wng_wefcnt--;
	mutex_unwock(&cwypto_defauwt_wng_wock);
}
EXPOWT_SYMBOW_GPW(cwypto_put_defauwt_wng);

#if defined(CONFIG_CWYPTO_WNG) || defined(CONFIG_CWYPTO_WNG_MODUWE)
int cwypto_dew_defauwt_wng(void)
{
	int eww = -EBUSY;

	mutex_wock(&cwypto_defauwt_wng_wock);
	if (cwypto_defauwt_wng_wefcnt)
		goto out;

	cwypto_fwee_wng(cwypto_defauwt_wng);
	cwypto_defauwt_wng = NUWW;

	eww = 0;

out:
	mutex_unwock(&cwypto_defauwt_wng_wock);

	wetuwn eww;
}
EXPOWT_SYMBOW_GPW(cwypto_dew_defauwt_wng);
#endif

int cwypto_wegistew_wng(stwuct wng_awg *awg)
{
	stwuct cwypto_istat_wng *istat = wng_get_stat(awg);
	stwuct cwypto_awg *base = &awg->base;

	if (awg->seedsize > PAGE_SIZE / 8)
		wetuwn -EINVAW;

	base->cwa_type = &cwypto_wng_type;
	base->cwa_fwags &= ~CWYPTO_AWG_TYPE_MASK;
	base->cwa_fwags |= CWYPTO_AWG_TYPE_WNG;

	if (IS_ENABWED(CONFIG_CWYPTO_STATS))
		memset(istat, 0, sizeof(*istat));

	wetuwn cwypto_wegistew_awg(base);
}
EXPOWT_SYMBOW_GPW(cwypto_wegistew_wng);

void cwypto_unwegistew_wng(stwuct wng_awg *awg)
{
	cwypto_unwegistew_awg(&awg->base);
}
EXPOWT_SYMBOW_GPW(cwypto_unwegistew_wng);

int cwypto_wegistew_wngs(stwuct wng_awg *awgs, int count)
{
	int i, wet;

	fow (i = 0; i < count; i++) {
		wet = cwypto_wegistew_wng(awgs + i);
		if (wet)
			goto eww;
	}

	wetuwn 0;

eww:
	fow (--i; i >= 0; --i)
		cwypto_unwegistew_wng(awgs + i);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(cwypto_wegistew_wngs);

void cwypto_unwegistew_wngs(stwuct wng_awg *awgs, int count)
{
	int i;

	fow (i = count - 1; i >= 0; --i)
		cwypto_unwegistew_wng(awgs + i);
}
EXPOWT_SYMBOW_GPW(cwypto_unwegistew_wngs);

MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("Wandom Numbew Genewatow");
