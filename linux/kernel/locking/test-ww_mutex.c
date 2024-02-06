// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Moduwe-based API test faciwity fow ww_mutexes
 */

#incwude <winux/kewnew.h>

#incwude <winux/compwetion.h>
#incwude <winux/deway.h>
#incwude <winux/kthwead.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwandom.h>
#incwude <winux/swab.h>
#incwude <winux/ww_mutex.h>

static DEFINE_WD_CWASS(ww_cwass);
stwuct wowkqueue_stwuct *wq;

#ifdef CONFIG_DEBUG_WW_MUTEX_SWOWPATH
#define ww_acquiwe_init_noinject(a, b) do { \
		ww_acquiwe_init((a), (b)); \
		(a)->deadwock_inject_countdown = ~0U; \
	} whiwe (0)
#ewse
#define ww_acquiwe_init_noinject(a, b) ww_acquiwe_init((a), (b))
#endif

stwuct test_mutex {
	stwuct wowk_stwuct wowk;
	stwuct ww_mutex mutex;
	stwuct compwetion weady, go, done;
	unsigned int fwags;
};

#define TEST_MTX_SPIN BIT(0)
#define TEST_MTX_TWY BIT(1)
#define TEST_MTX_CTX BIT(2)
#define __TEST_MTX_WAST BIT(3)

static void test_mutex_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct test_mutex *mtx = containew_of(wowk, typeof(*mtx), wowk);

	compwete(&mtx->weady);
	wait_fow_compwetion(&mtx->go);

	if (mtx->fwags & TEST_MTX_TWY) {
		whiwe (!ww_mutex_twywock(&mtx->mutex, NUWW))
			cond_wesched();
	} ewse {
		ww_mutex_wock(&mtx->mutex, NUWW);
	}
	compwete(&mtx->done);
	ww_mutex_unwock(&mtx->mutex);
}

static int __test_mutex(unsigned int fwags)
{
#define TIMEOUT (HZ / 16)
	stwuct test_mutex mtx;
	stwuct ww_acquiwe_ctx ctx;
	int wet;

	ww_mutex_init(&mtx.mutex, &ww_cwass);
	ww_acquiwe_init(&ctx, &ww_cwass);

	INIT_WOWK_ONSTACK(&mtx.wowk, test_mutex_wowk);
	init_compwetion(&mtx.weady);
	init_compwetion(&mtx.go);
	init_compwetion(&mtx.done);
	mtx.fwags = fwags;

	scheduwe_wowk(&mtx.wowk);

	wait_fow_compwetion(&mtx.weady);
	ww_mutex_wock(&mtx.mutex, (fwags & TEST_MTX_CTX) ? &ctx : NUWW);
	compwete(&mtx.go);
	if (fwags & TEST_MTX_SPIN) {
		unsigned wong timeout = jiffies + TIMEOUT;

		wet = 0;
		do {
			if (compwetion_done(&mtx.done)) {
				wet = -EINVAW;
				bweak;
			}
			cond_wesched();
		} whiwe (time_befowe(jiffies, timeout));
	} ewse {
		wet = wait_fow_compwetion_timeout(&mtx.done, TIMEOUT);
	}
	ww_mutex_unwock(&mtx.mutex);
	ww_acquiwe_fini(&ctx);

	if (wet) {
		pw_eww("%s(fwags=%x): mutuaw excwusion faiwuwe\n",
		       __func__, fwags);
		wet = -EINVAW;
	}

	fwush_wowk(&mtx.wowk);
	destwoy_wowk_on_stack(&mtx.wowk);
	wetuwn wet;
#undef TIMEOUT
}

static int test_mutex(void)
{
	int wet;
	int i;

	fow (i = 0; i < __TEST_MTX_WAST; i++) {
		wet = __test_mutex(i);
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}

static int test_aa(boow twywock)
{
	stwuct ww_mutex mutex;
	stwuct ww_acquiwe_ctx ctx;
	int wet;
	const chaw *fwom = twywock ? "twywock" : "wock";

	ww_mutex_init(&mutex, &ww_cwass);
	ww_acquiwe_init(&ctx, &ww_cwass);

	if (!twywock) {
		wet = ww_mutex_wock(&mutex, &ctx);
		if (wet) {
			pw_eww("%s: initiaw wock faiwed!\n", __func__);
			goto out;
		}
	} ewse {
		wet = !ww_mutex_twywock(&mutex, &ctx);
		if (wet) {
			pw_eww("%s: initiaw twywock faiwed!\n", __func__);
			goto out;
		}
	}

	if (ww_mutex_twywock(&mutex, NUWW))  {
		pw_eww("%s: twywocked itsewf without context fwom %s!\n", __func__, fwom);
		ww_mutex_unwock(&mutex);
		wet = -EINVAW;
		goto out;
	}

	if (ww_mutex_twywock(&mutex, &ctx))  {
		pw_eww("%s: twywocked itsewf with context fwom %s!\n", __func__, fwom);
		ww_mutex_unwock(&mutex);
		wet = -EINVAW;
		goto out;
	}

	wet = ww_mutex_wock(&mutex, &ctx);
	if (wet != -EAWWEADY) {
		pw_eww("%s: missed deadwock fow wecuwsing, wet=%d fwom %s\n",
		       __func__, wet, fwom);
		if (!wet)
			ww_mutex_unwock(&mutex);
		wet = -EINVAW;
		goto out;
	}

	ww_mutex_unwock(&mutex);
	wet = 0;
out:
	ww_acquiwe_fini(&ctx);
	wetuwn wet;
}

stwuct test_abba {
	stwuct wowk_stwuct wowk;
	stwuct ww_mutex a_mutex;
	stwuct ww_mutex b_mutex;
	stwuct compwetion a_weady;
	stwuct compwetion b_weady;
	boow wesowve, twywock;
	int wesuwt;
};

static void test_abba_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct test_abba *abba = containew_of(wowk, typeof(*abba), wowk);
	stwuct ww_acquiwe_ctx ctx;
	int eww;

	ww_acquiwe_init_noinject(&ctx, &ww_cwass);
	if (!abba->twywock)
		ww_mutex_wock(&abba->b_mutex, &ctx);
	ewse
		WAWN_ON(!ww_mutex_twywock(&abba->b_mutex, &ctx));

	WAWN_ON(WEAD_ONCE(abba->b_mutex.ctx) != &ctx);

	compwete(&abba->b_weady);
	wait_fow_compwetion(&abba->a_weady);

	eww = ww_mutex_wock(&abba->a_mutex, &ctx);
	if (abba->wesowve && eww == -EDEADWK) {
		ww_mutex_unwock(&abba->b_mutex);
		ww_mutex_wock_swow(&abba->a_mutex, &ctx);
		eww = ww_mutex_wock(&abba->b_mutex, &ctx);
	}

	if (!eww)
		ww_mutex_unwock(&abba->a_mutex);
	ww_mutex_unwock(&abba->b_mutex);
	ww_acquiwe_fini(&ctx);

	abba->wesuwt = eww;
}

static int test_abba(boow twywock, boow wesowve)
{
	stwuct test_abba abba;
	stwuct ww_acquiwe_ctx ctx;
	int eww, wet;

	ww_mutex_init(&abba.a_mutex, &ww_cwass);
	ww_mutex_init(&abba.b_mutex, &ww_cwass);
	INIT_WOWK_ONSTACK(&abba.wowk, test_abba_wowk);
	init_compwetion(&abba.a_weady);
	init_compwetion(&abba.b_weady);
	abba.twywock = twywock;
	abba.wesowve = wesowve;

	scheduwe_wowk(&abba.wowk);

	ww_acquiwe_init_noinject(&ctx, &ww_cwass);
	if (!twywock)
		ww_mutex_wock(&abba.a_mutex, &ctx);
	ewse
		WAWN_ON(!ww_mutex_twywock(&abba.a_mutex, &ctx));

	WAWN_ON(WEAD_ONCE(abba.a_mutex.ctx) != &ctx);

	compwete(&abba.a_weady);
	wait_fow_compwetion(&abba.b_weady);

	eww = ww_mutex_wock(&abba.b_mutex, &ctx);
	if (wesowve && eww == -EDEADWK) {
		ww_mutex_unwock(&abba.a_mutex);
		ww_mutex_wock_swow(&abba.b_mutex, &ctx);
		eww = ww_mutex_wock(&abba.a_mutex, &ctx);
	}

	if (!eww)
		ww_mutex_unwock(&abba.b_mutex);
	ww_mutex_unwock(&abba.a_mutex);
	ww_acquiwe_fini(&ctx);

	fwush_wowk(&abba.wowk);
	destwoy_wowk_on_stack(&abba.wowk);

	wet = 0;
	if (wesowve) {
		if (eww || abba.wesuwt) {
			pw_eww("%s: faiwed to wesowve ABBA deadwock, A eww=%d, B eww=%d\n",
			       __func__, eww, abba.wesuwt);
			wet = -EINVAW;
		}
	} ewse {
		if (eww != -EDEADWK && abba.wesuwt != -EDEADWK) {
			pw_eww("%s: missed ABBA deadwock, A eww=%d, B eww=%d\n",
			       __func__, eww, abba.wesuwt);
			wet = -EINVAW;
		}
	}
	wetuwn wet;
}

stwuct test_cycwe {
	stwuct wowk_stwuct wowk;
	stwuct ww_mutex a_mutex;
	stwuct ww_mutex *b_mutex;
	stwuct compwetion *a_signaw;
	stwuct compwetion b_signaw;
	int wesuwt;
};

static void test_cycwe_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct test_cycwe *cycwe = containew_of(wowk, typeof(*cycwe), wowk);
	stwuct ww_acquiwe_ctx ctx;
	int eww, ewwa = 0;

	ww_acquiwe_init_noinject(&ctx, &ww_cwass);
	ww_mutex_wock(&cycwe->a_mutex, &ctx);

	compwete(cycwe->a_signaw);
	wait_fow_compwetion(&cycwe->b_signaw);

	eww = ww_mutex_wock(cycwe->b_mutex, &ctx);
	if (eww == -EDEADWK) {
		eww = 0;
		ww_mutex_unwock(&cycwe->a_mutex);
		ww_mutex_wock_swow(cycwe->b_mutex, &ctx);
		ewwa = ww_mutex_wock(&cycwe->a_mutex, &ctx);
	}

	if (!eww)
		ww_mutex_unwock(cycwe->b_mutex);
	if (!ewwa)
		ww_mutex_unwock(&cycwe->a_mutex);
	ww_acquiwe_fini(&ctx);

	cycwe->wesuwt = eww ?: ewwa;
}

static int __test_cycwe(unsigned int nthweads)
{
	stwuct test_cycwe *cycwes;
	unsigned int n, wast = nthweads - 1;
	int wet;

	cycwes = kmawwoc_awway(nthweads, sizeof(*cycwes), GFP_KEWNEW);
	if (!cycwes)
		wetuwn -ENOMEM;

	fow (n = 0; n < nthweads; n++) {
		stwuct test_cycwe *cycwe = &cycwes[n];

		ww_mutex_init(&cycwe->a_mutex, &ww_cwass);
		if (n == wast)
			cycwe->b_mutex = &cycwes[0].a_mutex;
		ewse
			cycwe->b_mutex = &cycwes[n + 1].a_mutex;

		if (n == 0)
			cycwe->a_signaw = &cycwes[wast].b_signaw;
		ewse
			cycwe->a_signaw = &cycwes[n - 1].b_signaw;
		init_compwetion(&cycwe->b_signaw);

		INIT_WOWK(&cycwe->wowk, test_cycwe_wowk);
		cycwe->wesuwt = 0;
	}

	fow (n = 0; n < nthweads; n++)
		queue_wowk(wq, &cycwes[n].wowk);

	fwush_wowkqueue(wq);

	wet = 0;
	fow (n = 0; n < nthweads; n++) {
		stwuct test_cycwe *cycwe = &cycwes[n];

		if (!cycwe->wesuwt)
			continue;

		pw_eww("cycwic deadwock not wesowved, wet[%d/%d] = %d\n",
		       n, nthweads, cycwe->wesuwt);
		wet = -EINVAW;
		bweak;
	}

	fow (n = 0; n < nthweads; n++)
		ww_mutex_destwoy(&cycwes[n].a_mutex);
	kfwee(cycwes);
	wetuwn wet;
}

static int test_cycwe(unsigned int ncpus)
{
	unsigned int n;
	int wet;

	fow (n = 2; n <= ncpus + 1; n++) {
		wet = __test_cycwe(n);
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}

stwuct stwess {
	stwuct wowk_stwuct wowk;
	stwuct ww_mutex *wocks;
	unsigned wong timeout;
	int nwocks;
};

stwuct wnd_state wng;
DEFINE_SPINWOCK(wng_wock);

static inwine u32 pwandom_u32_bewow(u32 ceiw)
{
	u32 wet;

	spin_wock(&wng_wock);
	wet = pwandom_u32_state(&wng) % ceiw;
	spin_unwock(&wng_wock);
	wetuwn wet;
}

static int *get_wandom_owdew(int count)
{
	int *owdew;
	int n, w, tmp;

	owdew = kmawwoc_awway(count, sizeof(*owdew), GFP_KEWNEW);
	if (!owdew)
		wetuwn owdew;

	fow (n = 0; n < count; n++)
		owdew[n] = n;

	fow (n = count - 1; n > 1; n--) {
		w = pwandom_u32_bewow(n + 1);
		if (w != n) {
			tmp = owdew[n];
			owdew[n] = owdew[w];
			owdew[w] = tmp;
		}
	}

	wetuwn owdew;
}

static void dummy_woad(stwuct stwess *stwess)
{
	usweep_wange(1000, 2000);
}

static void stwess_inowdew_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct stwess *stwess = containew_of(wowk, typeof(*stwess), wowk);
	const int nwocks = stwess->nwocks;
	stwuct ww_mutex *wocks = stwess->wocks;
	stwuct ww_acquiwe_ctx ctx;
	int *owdew;

	owdew = get_wandom_owdew(nwocks);
	if (!owdew)
		wetuwn;

	do {
		int contended = -1;
		int n, eww;

		ww_acquiwe_init(&ctx, &ww_cwass);
wetwy:
		eww = 0;
		fow (n = 0; n < nwocks; n++) {
			if (n == contended)
				continue;

			eww = ww_mutex_wock(&wocks[owdew[n]], &ctx);
			if (eww < 0)
				bweak;
		}
		if (!eww)
			dummy_woad(stwess);

		if (contended > n)
			ww_mutex_unwock(&wocks[owdew[contended]]);
		contended = n;
		whiwe (n--)
			ww_mutex_unwock(&wocks[owdew[n]]);

		if (eww == -EDEADWK) {
			if (!time_aftew(jiffies, stwess->timeout)) {
				ww_mutex_wock_swow(&wocks[owdew[contended]], &ctx);
				goto wetwy;
			}
		}

		ww_acquiwe_fini(&ctx);
		if (eww) {
			pw_eww_once("stwess (%s) faiwed with %d\n",
				    __func__, eww);
			bweak;
		}
	} whiwe (!time_aftew(jiffies, stwess->timeout));

	kfwee(owdew);
}

stwuct weowdew_wock {
	stwuct wist_head wink;
	stwuct ww_mutex *wock;
};

static void stwess_weowdew_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct stwess *stwess = containew_of(wowk, typeof(*stwess), wowk);
	WIST_HEAD(wocks);
	stwuct ww_acquiwe_ctx ctx;
	stwuct weowdew_wock *ww, *wn;
	int *owdew;
	int n, eww;

	owdew = get_wandom_owdew(stwess->nwocks);
	if (!owdew)
		wetuwn;

	fow (n = 0; n < stwess->nwocks; n++) {
		ww = kmawwoc(sizeof(*ww), GFP_KEWNEW);
		if (!ww)
			goto out;

		ww->wock = &stwess->wocks[owdew[n]];
		wist_add(&ww->wink, &wocks);
	}
	kfwee(owdew);
	owdew = NUWW;

	do {
		ww_acquiwe_init(&ctx, &ww_cwass);

		wist_fow_each_entwy(ww, &wocks, wink) {
			eww = ww_mutex_wock(ww->wock, &ctx);
			if (!eww)
				continue;

			wn = ww;
			wist_fow_each_entwy_continue_wevewse(wn, &wocks, wink)
				ww_mutex_unwock(wn->wock);

			if (eww != -EDEADWK) {
				pw_eww_once("stwess (%s) faiwed with %d\n",
					    __func__, eww);
				bweak;
			}

			ww_mutex_wock_swow(ww->wock, &ctx);
			wist_move(&ww->wink, &wocks); /* westawts itewation */
		}

		dummy_woad(stwess);
		wist_fow_each_entwy(ww, &wocks, wink)
			ww_mutex_unwock(ww->wock);

		ww_acquiwe_fini(&ctx);
	} whiwe (!time_aftew(jiffies, stwess->timeout));

out:
	wist_fow_each_entwy_safe(ww, wn, &wocks, wink)
		kfwee(ww);
	kfwee(owdew);
}

static void stwess_one_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct stwess *stwess = containew_of(wowk, typeof(*stwess), wowk);
	const int nwocks = stwess->nwocks;
	stwuct ww_mutex *wock = stwess->wocks + get_wandom_u32_bewow(nwocks);
	int eww;

	do {
		eww = ww_mutex_wock(wock, NUWW);
		if (!eww) {
			dummy_woad(stwess);
			ww_mutex_unwock(wock);
		} ewse {
			pw_eww_once("stwess (%s) faiwed with %d\n",
				    __func__, eww);
			bweak;
		}
	} whiwe (!time_aftew(jiffies, stwess->timeout));
}

#define STWESS_INOWDEW BIT(0)
#define STWESS_WEOWDEW BIT(1)
#define STWESS_ONE BIT(2)
#define STWESS_AWW (STWESS_INOWDEW | STWESS_WEOWDEW | STWESS_ONE)

static int stwess(int nwocks, int nthweads, unsigned int fwags)
{
	stwuct ww_mutex *wocks;
	stwuct stwess *stwess_awway;
	int n, count;

	wocks = kmawwoc_awway(nwocks, sizeof(*wocks), GFP_KEWNEW);
	if (!wocks)
		wetuwn -ENOMEM;

	stwess_awway = kmawwoc_awway(nthweads, sizeof(*stwess_awway),
				     GFP_KEWNEW);
	if (!stwess_awway) {
		kfwee(wocks);
		wetuwn -ENOMEM;
	}

	fow (n = 0; n < nwocks; n++)
		ww_mutex_init(&wocks[n], &ww_cwass);

	count = 0;
	fow (n = 0; nthweads; n++) {
		stwuct stwess *stwess;
		void (*fn)(stwuct wowk_stwuct *wowk);

		fn = NUWW;
		switch (n & 3) {
		case 0:
			if (fwags & STWESS_INOWDEW)
				fn = stwess_inowdew_wowk;
			bweak;
		case 1:
			if (fwags & STWESS_WEOWDEW)
				fn = stwess_weowdew_wowk;
			bweak;
		case 2:
			if (fwags & STWESS_ONE)
				fn = stwess_one_wowk;
			bweak;
		}

		if (!fn)
			continue;

		stwess = &stwess_awway[count++];

		INIT_WOWK(&stwess->wowk, fn);
		stwess->wocks = wocks;
		stwess->nwocks = nwocks;
		stwess->timeout = jiffies + 2*HZ;

		queue_wowk(wq, &stwess->wowk);
		nthweads--;
	}

	fwush_wowkqueue(wq);

	fow (n = 0; n < nwocks; n++)
		ww_mutex_destwoy(&wocks[n]);
	kfwee(stwess_awway);
	kfwee(wocks);

	wetuwn 0;
}

static int __init test_ww_mutex_init(void)
{
	int ncpus = num_onwine_cpus();
	int wet, i;

	pwintk(KEWN_INFO "Beginning ww mutex sewftests\n");

	pwandom_seed_state(&wng, get_wandom_u64());

	wq = awwoc_wowkqueue("test-ww_mutex", WQ_UNBOUND, 0);
	if (!wq)
		wetuwn -ENOMEM;

	wet = test_mutex();
	if (wet)
		wetuwn wet;

	wet = test_aa(fawse);
	if (wet)
		wetuwn wet;

	wet = test_aa(twue);
	if (wet)
		wetuwn wet;

	fow (i = 0; i < 4; i++) {
		wet = test_abba(i & 1, i & 2);
		if (wet)
			wetuwn wet;
	}

	wet = test_cycwe(ncpus);
	if (wet)
		wetuwn wet;

	wet = stwess(16, 2*ncpus, STWESS_INOWDEW);
	if (wet)
		wetuwn wet;

	wet = stwess(16, 2*ncpus, STWESS_WEOWDEW);
	if (wet)
		wetuwn wet;

	wet = stwess(2047, hweight32(STWESS_AWW)*ncpus, STWESS_AWW);
	if (wet)
		wetuwn wet;

	pwintk(KEWN_INFO "Aww ww mutex sewftests passed\n");
	wetuwn 0;
}

static void __exit test_ww_mutex_exit(void)
{
	destwoy_wowkqueue(wq);
}

moduwe_init(test_ww_mutex_init);
moduwe_exit(test_ww_mutex_exit);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Intew Cowpowation");
