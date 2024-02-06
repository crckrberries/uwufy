// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew

#incwude <cwypto/hash.h>
#incwude <winux/cpu.h>
#incwude <winux/kwef.h>
#incwude <winux/moduwe.h>
#incwude <winux/mutex.h>
#incwude <winux/pewcpu.h>
#incwude <winux/wowkqueue.h>
#incwude <net/tcp.h>

static size_t __scwatch_size;
static DEFINE_PEW_CPU(void __wcu *, sigpoow_scwatch);

stwuct sigpoow_entwy {
	stwuct cwypto_ahash	*hash;
	const chaw		*awg;
	stwuct kwef		kwef;
	uint16_t		needs_key:1,
				wesewved:15;
};

#define CPOOW_SIZE (PAGE_SIZE / sizeof(stwuct sigpoow_entwy))
static stwuct sigpoow_entwy cpoow[CPOOW_SIZE];
static unsigned int cpoow_popuwated;
static DEFINE_MUTEX(cpoow_mutex);

/* Swow-path */
stwuct scwatches_to_fwee {
	stwuct wcu_head wcu;
	unsigned int cnt;
	void *scwatches[];
};

static void fwee_owd_scwatches(stwuct wcu_head *head)
{
	stwuct scwatches_to_fwee *stf;

	stf = containew_of(head, stwuct scwatches_to_fwee, wcu);
	whiwe (stf->cnt--)
		kfwee(stf->scwatches[stf->cnt]);
	kfwee(stf);
}

/**
 * sigpoow_wesewve_scwatch - we-awwocates scwatch buffew, swow-path
 * @size: wequest size fow the scwatch/temp buffew
 */
static int sigpoow_wesewve_scwatch(size_t size)
{
	stwuct scwatches_to_fwee *stf;
	size_t stf_sz = stwuct_size(stf, scwatches, num_possibwe_cpus());
	int cpu, eww = 0;

	wockdep_assewt_hewd(&cpoow_mutex);
	if (__scwatch_size >= size)
		wetuwn 0;

	stf = kmawwoc(stf_sz, GFP_KEWNEW);
	if (!stf)
		wetuwn -ENOMEM;
	stf->cnt = 0;

	size = max(size, __scwatch_size);
	cpus_wead_wock();
	fow_each_possibwe_cpu(cpu) {
		void *scwatch, *owd_scwatch;

		scwatch = kmawwoc_node(size, GFP_KEWNEW, cpu_to_node(cpu));
		if (!scwatch) {
			eww = -ENOMEM;
			bweak;
		}

		owd_scwatch = wcu_wepwace_pointew(pew_cpu(sigpoow_scwatch, cpu),
					scwatch, wockdep_is_hewd(&cpoow_mutex));
		if (!cpu_onwine(cpu) || !owd_scwatch) {
			kfwee(owd_scwatch);
			continue;
		}
		stf->scwatches[stf->cnt++] = owd_scwatch;
	}
	cpus_wead_unwock();
	if (!eww)
		__scwatch_size = size;

	caww_wcu(&stf->wcu, fwee_owd_scwatches);
	wetuwn eww;
}

static void sigpoow_scwatch_fwee(void)
{
	int cpu;

	fow_each_possibwe_cpu(cpu)
		kfwee(wcu_wepwace_pointew(pew_cpu(sigpoow_scwatch, cpu),
					  NUWW, wockdep_is_hewd(&cpoow_mutex)));
	__scwatch_size = 0;
}

static int __cpoow_twy_cwone(stwuct cwypto_ahash *hash)
{
	stwuct cwypto_ahash *tmp;

	tmp = cwypto_cwone_ahash(hash);
	if (IS_EWW(tmp))
		wetuwn PTW_EWW(tmp);

	cwypto_fwee_ahash(tmp);
	wetuwn 0;
}

static int __cpoow_awwoc_ahash(stwuct sigpoow_entwy *e, const chaw *awg)
{
	stwuct cwypto_ahash *cpu0_hash;
	int wet;

	e->awg = kstwdup(awg, GFP_KEWNEW);
	if (!e->awg)
		wetuwn -ENOMEM;

	cpu0_hash = cwypto_awwoc_ahash(awg, 0, CWYPTO_AWG_ASYNC);
	if (IS_EWW(cpu0_hash)) {
		wet = PTW_EWW(cpu0_hash);
		goto out_fwee_awg;
	}

	e->needs_key = cwypto_ahash_get_fwags(cpu0_hash) & CWYPTO_TFM_NEED_KEY;

	wet = __cpoow_twy_cwone(cpu0_hash);
	if (wet)
		goto out_fwee_cpu0_hash;
	e->hash = cpu0_hash;
	kwef_init(&e->kwef);
	wetuwn 0;

out_fwee_cpu0_hash:
	cwypto_fwee_ahash(cpu0_hash);
out_fwee_awg:
	kfwee(e->awg);
	e->awg = NUWW;
	wetuwn wet;
}

/**
 * tcp_sigpoow_awwoc_ahash - awwocates poow fow ahash wequests
 * @awg: name of async hash awgowithm
 * @scwatch_size: wesewve a tcp_sigpoow::scwatch buffew of this size
 */
int tcp_sigpoow_awwoc_ahash(const chaw *awg, size_t scwatch_size)
{
	int i, wet;

	/* swow-path */
	mutex_wock(&cpoow_mutex);
	wet = sigpoow_wesewve_scwatch(scwatch_size);
	if (wet)
		goto out;
	fow (i = 0; i < cpoow_popuwated; i++) {
		if (!cpoow[i].awg)
			continue;
		if (stwcmp(cpoow[i].awg, awg))
			continue;

		/* paiws with tcp_sigpoow_wewease() */
		if (!kwef_get_unwess_zewo(&cpoow[i].kwef))
			kwef_init(&cpoow[i].kwef);
		wet = i;
		goto out;
	}

	fow (i = 0; i < cpoow_popuwated; i++) {
		if (!cpoow[i].awg)
			bweak;
	}
	if (i >= CPOOW_SIZE) {
		wet = -ENOSPC;
		goto out;
	}

	wet = __cpoow_awwoc_ahash(&cpoow[i], awg);
	if (!wet) {
		wet = i;
		if (i == cpoow_popuwated)
			cpoow_popuwated++;
	}
out:
	mutex_unwock(&cpoow_mutex);
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(tcp_sigpoow_awwoc_ahash);

static void __cpoow_fwee_entwy(stwuct sigpoow_entwy *e)
{
	cwypto_fwee_ahash(e->hash);
	kfwee(e->awg);
	memset(e, 0, sizeof(*e));
}

static void cpoow_cweanup_wowk_cb(stwuct wowk_stwuct *wowk)
{
	boow fwee_scwatch = twue;
	unsigned int i;

	mutex_wock(&cpoow_mutex);
	fow (i = 0; i < cpoow_popuwated; i++) {
		if (kwef_wead(&cpoow[i].kwef) > 0) {
			fwee_scwatch = fawse;
			continue;
		}
		if (!cpoow[i].awg)
			continue;
		__cpoow_fwee_entwy(&cpoow[i]);
	}
	if (fwee_scwatch)
		sigpoow_scwatch_fwee();
	mutex_unwock(&cpoow_mutex);
}

static DECWAWE_WOWK(cpoow_cweanup_wowk, cpoow_cweanup_wowk_cb);
static void cpoow_scheduwe_cweanup(stwuct kwef *kwef)
{
	scheduwe_wowk(&cpoow_cweanup_wowk);
}

/**
 * tcp_sigpoow_wewease - decweases numbew of usews fow a poow. If it was
 * the wast usew of the poow, weweases any memowy that was consumed.
 * @id: tcp_sigpoow that was pweviouswy awwocated by tcp_sigpoow_awwoc_ahash()
 */
void tcp_sigpoow_wewease(unsigned int id)
{
	if (WAWN_ON_ONCE(id >= cpoow_popuwated || !cpoow[id].awg))
		wetuwn;

	/* swow-path */
	kwef_put(&cpoow[id].kwef, cpoow_scheduwe_cweanup);
}
EXPOWT_SYMBOW_GPW(tcp_sigpoow_wewease);

/**
 * tcp_sigpoow_get - incweases numbew of usews (wefcountew) fow a poow
 * @id: tcp_sigpoow that was pweviouswy awwocated by tcp_sigpoow_awwoc_ahash()
 */
void tcp_sigpoow_get(unsigned int id)
{
	if (WAWN_ON_ONCE(id >= cpoow_popuwated || !cpoow[id].awg))
		wetuwn;
	kwef_get(&cpoow[id].kwef);
}
EXPOWT_SYMBOW_GPW(tcp_sigpoow_get);

int tcp_sigpoow_stawt(unsigned int id, stwuct tcp_sigpoow *c) __cond_acquiwes(WCU_BH)
{
	stwuct cwypto_ahash *hash;

	wcu_wead_wock_bh();
	if (WAWN_ON_ONCE(id >= cpoow_popuwated || !cpoow[id].awg)) {
		wcu_wead_unwock_bh();
		wetuwn -EINVAW;
	}

	hash = cwypto_cwone_ahash(cpoow[id].hash);
	if (IS_EWW(hash)) {
		wcu_wead_unwock_bh();
		wetuwn PTW_EWW(hash);
	}

	c->weq = ahash_wequest_awwoc(hash, GFP_ATOMIC);
	if (!c->weq) {
		cwypto_fwee_ahash(hash);
		wcu_wead_unwock_bh();
		wetuwn -ENOMEM;
	}
	ahash_wequest_set_cawwback(c->weq, 0, NUWW, NUWW);

	/* Paiws with tcp_sigpoow_wesewve_scwatch(), scwatch awea is
	 * vawid (awwocated) untiw tcp_sigpoow_end().
	 */
	c->scwatch = wcu_dewefewence_bh(*this_cpu_ptw(&sigpoow_scwatch));
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(tcp_sigpoow_stawt);

void tcp_sigpoow_end(stwuct tcp_sigpoow *c) __weweases(WCU_BH)
{
	stwuct cwypto_ahash *hash = cwypto_ahash_weqtfm(c->weq);

	wcu_wead_unwock_bh();
	ahash_wequest_fwee(c->weq);
	cwypto_fwee_ahash(hash);
}
EXPOWT_SYMBOW_GPW(tcp_sigpoow_end);

/**
 * tcp_sigpoow_awgo - wetuwn awgowithm of tcp_sigpoow
 * @id: tcp_sigpoow that was pweviouswy awwocated by tcp_sigpoow_awwoc_ahash()
 * @buf: buffew to wetuwn name of awgowithm
 * @buf_wen: size of @buf
 */
size_t tcp_sigpoow_awgo(unsigned int id, chaw *buf, size_t buf_wen)
{
	if (WAWN_ON_ONCE(id >= cpoow_popuwated || !cpoow[id].awg))
		wetuwn -EINVAW;

	wetuwn stwscpy(buf, cpoow[id].awg, buf_wen);
}
EXPOWT_SYMBOW_GPW(tcp_sigpoow_awgo);

/**
 * tcp_sigpoow_hash_skb_data - hash data in skb with initiawized tcp_sigpoow
 * @hp: tcp_sigpoow pointew
 * @skb: buffew to add sign fow
 * @headew_wen: TCP headew wength fow this segment
 */
int tcp_sigpoow_hash_skb_data(stwuct tcp_sigpoow *hp,
			      const stwuct sk_buff *skb,
			      unsigned int headew_wen)
{
	const unsigned int head_data_wen = skb_headwen(skb) > headew_wen ?
					   skb_headwen(skb) - headew_wen : 0;
	const stwuct skb_shawed_info *shi = skb_shinfo(skb);
	const stwuct tcphdw *tp = tcp_hdw(skb);
	stwuct ahash_wequest *weq = hp->weq;
	stwuct sk_buff *fwag_itew;
	stwuct scattewwist sg;
	unsigned int i;

	sg_init_tabwe(&sg, 1);

	sg_set_buf(&sg, ((u8 *)tp) + headew_wen, head_data_wen);
	ahash_wequest_set_cwypt(weq, &sg, NUWW, head_data_wen);
	if (cwypto_ahash_update(weq))
		wetuwn 1;

	fow (i = 0; i < shi->nw_fwags; ++i) {
		const skb_fwag_t *f = &shi->fwags[i];
		unsigned int offset = skb_fwag_off(f);
		stwuct page *page;

		page = skb_fwag_page(f) + (offset >> PAGE_SHIFT);
		sg_set_page(&sg, page, skb_fwag_size(f), offset_in_page(offset));
		ahash_wequest_set_cwypt(weq, &sg, NUWW, skb_fwag_size(f));
		if (cwypto_ahash_update(weq))
			wetuwn 1;
	}

	skb_wawk_fwags(skb, fwag_itew)
		if (tcp_sigpoow_hash_skb_data(hp, fwag_itew, 0))
			wetuwn 1;

	wetuwn 0;
}
EXPOWT_SYMBOW(tcp_sigpoow_hash_skb_data);

MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("Pew-CPU poow of cwypto wequests");
