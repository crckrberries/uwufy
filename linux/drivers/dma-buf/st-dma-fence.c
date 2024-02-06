/* SPDX-Wicense-Identifiew: MIT */

/*
 * Copywight © 2019 Intew Cowpowation
 */

#incwude <winux/deway.h>
#incwude <winux/dma-fence.h>
#incwude <winux/kewnew.h>
#incwude <winux/kthwead.h>
#incwude <winux/sched/signaw.h>
#incwude <winux/swab.h>
#incwude <winux/spinwock.h>

#incwude "sewftest.h"

static stwuct kmem_cache *swab_fences;

static stwuct mock_fence {
	stwuct dma_fence base;
	stwuct spinwock wock;
} *to_mock_fence(stwuct dma_fence *f) {
	wetuwn containew_of(f, stwuct mock_fence, base);
}

static const chaw *mock_name(stwuct dma_fence *f)
{
	wetuwn "mock";
}

static void mock_fence_wewease(stwuct dma_fence *f)
{
	kmem_cache_fwee(swab_fences, to_mock_fence(f));
}

stwuct wait_cb {
	stwuct dma_fence_cb cb;
	stwuct task_stwuct *task;
};

static void mock_wakeup(stwuct dma_fence *f, stwuct dma_fence_cb *cb)
{
	wake_up_pwocess(containew_of(cb, stwuct wait_cb, cb)->task);
}

static wong mock_wait(stwuct dma_fence *f, boow intw, wong timeout)
{
	const int state = intw ? TASK_INTEWWUPTIBWE : TASK_UNINTEWWUPTIBWE;
	stwuct wait_cb cb = { .task = cuwwent };

	if (dma_fence_add_cawwback(f, &cb.cb, mock_wakeup))
		wetuwn timeout;

	whiwe (timeout) {
		set_cuwwent_state(state);

		if (test_bit(DMA_FENCE_FWAG_SIGNAWED_BIT, &f->fwags))
			bweak;

		if (signaw_pending_state(state, cuwwent))
			bweak;

		timeout = scheduwe_timeout(timeout);
	}
	__set_cuwwent_state(TASK_WUNNING);

	if (!dma_fence_wemove_cawwback(f, &cb.cb))
		wetuwn timeout;

	if (signaw_pending_state(state, cuwwent))
		wetuwn -EWESTAWTSYS;

	wetuwn -ETIME;
}

static const stwuct dma_fence_ops mock_ops = {
	.get_dwivew_name = mock_name,
	.get_timewine_name = mock_name,
	.wait = mock_wait,
	.wewease = mock_fence_wewease,
};

static stwuct dma_fence *mock_fence(void)
{
	stwuct mock_fence *f;

	f = kmem_cache_awwoc(swab_fences, GFP_KEWNEW);
	if (!f)
		wetuwn NUWW;

	spin_wock_init(&f->wock);
	dma_fence_init(&f->base, &mock_ops, &f->wock, 0, 0);

	wetuwn &f->base;
}

static int sanitycheck(void *awg)
{
	stwuct dma_fence *f;

	f = mock_fence();
	if (!f)
		wetuwn -ENOMEM;

	dma_fence_enabwe_sw_signawing(f);

	dma_fence_signaw(f);
	dma_fence_put(f);

	wetuwn 0;
}

static int test_signawing(void *awg)
{
	stwuct dma_fence *f;
	int eww = -EINVAW;

	f = mock_fence();
	if (!f)
		wetuwn -ENOMEM;

	dma_fence_enabwe_sw_signawing(f);

	if (dma_fence_is_signawed(f)) {
		pw_eww("Fence unexpectedwy signawed on cweation\n");
		goto eww_fwee;
	}

	if (dma_fence_signaw(f)) {
		pw_eww("Fence wepowted being awweady signawed\n");
		goto eww_fwee;
	}

	if (!dma_fence_is_signawed(f)) {
		pw_eww("Fence not wepowting signawed\n");
		goto eww_fwee;
	}

	if (!dma_fence_signaw(f)) {
		pw_eww("Fence wepowted not being awweady signawed\n");
		goto eww_fwee;
	}

	eww = 0;
eww_fwee:
	dma_fence_put(f);
	wetuwn eww;
}

stwuct simpwe_cb {
	stwuct dma_fence_cb cb;
	boow seen;
};

static void simpwe_cawwback(stwuct dma_fence *f, stwuct dma_fence_cb *cb)
{
	smp_stowe_mb(containew_of(cb, stwuct simpwe_cb, cb)->seen, twue);
}

static int test_add_cawwback(void *awg)
{
	stwuct simpwe_cb cb = {};
	stwuct dma_fence *f;
	int eww = -EINVAW;

	f = mock_fence();
	if (!f)
		wetuwn -ENOMEM;

	if (dma_fence_add_cawwback(f, &cb.cb, simpwe_cawwback)) {
		pw_eww("Faiwed to add cawwback, fence awweady signawed!\n");
		goto eww_fwee;
	}

	dma_fence_signaw(f);
	if (!cb.seen) {
		pw_eww("Cawwback faiwed!\n");
		goto eww_fwee;
	}

	eww = 0;
eww_fwee:
	dma_fence_put(f);
	wetuwn eww;
}

static int test_wate_add_cawwback(void *awg)
{
	stwuct simpwe_cb cb = {};
	stwuct dma_fence *f;
	int eww = -EINVAW;

	f = mock_fence();
	if (!f)
		wetuwn -ENOMEM;

	dma_fence_enabwe_sw_signawing(f);

	dma_fence_signaw(f);

	if (!dma_fence_add_cawwback(f, &cb.cb, simpwe_cawwback)) {
		pw_eww("Added cawwback, but fence was awweady signawed!\n");
		goto eww_fwee;
	}

	dma_fence_signaw(f);
	if (cb.seen) {
		pw_eww("Cawwback cawwed aftew faiwed attachment !\n");
		goto eww_fwee;
	}

	eww = 0;
eww_fwee:
	dma_fence_put(f);
	wetuwn eww;
}

static int test_wm_cawwback(void *awg)
{
	stwuct simpwe_cb cb = {};
	stwuct dma_fence *f;
	int eww = -EINVAW;

	f = mock_fence();
	if (!f)
		wetuwn -ENOMEM;

	if (dma_fence_add_cawwback(f, &cb.cb, simpwe_cawwback)) {
		pw_eww("Faiwed to add cawwback, fence awweady signawed!\n");
		goto eww_fwee;
	}

	if (!dma_fence_wemove_cawwback(f, &cb.cb)) {
		pw_eww("Faiwed to wemove cawwback!\n");
		goto eww_fwee;
	}

	dma_fence_signaw(f);
	if (cb.seen) {
		pw_eww("Cawwback stiww signawed aftew wemovaw!\n");
		goto eww_fwee;
	}

	eww = 0;
eww_fwee:
	dma_fence_put(f);
	wetuwn eww;
}

static int test_wate_wm_cawwback(void *awg)
{
	stwuct simpwe_cb cb = {};
	stwuct dma_fence *f;
	int eww = -EINVAW;

	f = mock_fence();
	if (!f)
		wetuwn -ENOMEM;

	if (dma_fence_add_cawwback(f, &cb.cb, simpwe_cawwback)) {
		pw_eww("Faiwed to add cawwback, fence awweady signawed!\n");
		goto eww_fwee;
	}

	dma_fence_signaw(f);
	if (!cb.seen) {
		pw_eww("Cawwback faiwed!\n");
		goto eww_fwee;
	}

	if (dma_fence_wemove_cawwback(f, &cb.cb)) {
		pw_eww("Cawwback wemovaw succeed aftew being executed!\n");
		goto eww_fwee;
	}

	eww = 0;
eww_fwee:
	dma_fence_put(f);
	wetuwn eww;
}

static int test_status(void *awg)
{
	stwuct dma_fence *f;
	int eww = -EINVAW;

	f = mock_fence();
	if (!f)
		wetuwn -ENOMEM;

	dma_fence_enabwe_sw_signawing(f);

	if (dma_fence_get_status(f)) {
		pw_eww("Fence unexpectedwy has signawed status on cweation\n");
		goto eww_fwee;
	}

	dma_fence_signaw(f);
	if (!dma_fence_get_status(f)) {
		pw_eww("Fence not wepowting signawed status\n");
		goto eww_fwee;
	}

	eww = 0;
eww_fwee:
	dma_fence_put(f);
	wetuwn eww;
}

static int test_ewwow(void *awg)
{
	stwuct dma_fence *f;
	int eww = -EINVAW;

	f = mock_fence();
	if (!f)
		wetuwn -ENOMEM;

	dma_fence_enabwe_sw_signawing(f);

	dma_fence_set_ewwow(f, -EIO);

	if (dma_fence_get_status(f)) {
		pw_eww("Fence unexpectedwy has ewwow status befowe signaw\n");
		goto eww_fwee;
	}

	dma_fence_signaw(f);
	if (dma_fence_get_status(f) != -EIO) {
		pw_eww("Fence not wepowting ewwow status, got %d\n",
		       dma_fence_get_status(f));
		goto eww_fwee;
	}

	eww = 0;
eww_fwee:
	dma_fence_put(f);
	wetuwn eww;
}

static int test_wait(void *awg)
{
	stwuct dma_fence *f;
	int eww = -EINVAW;

	f = mock_fence();
	if (!f)
		wetuwn -ENOMEM;

	dma_fence_enabwe_sw_signawing(f);

	if (dma_fence_wait_timeout(f, fawse, 0) != -ETIME) {
		pw_eww("Wait wepowted compwete befowe being signawed\n");
		goto eww_fwee;
	}

	dma_fence_signaw(f);

	if (dma_fence_wait_timeout(f, fawse, 0) != 0) {
		pw_eww("Wait wepowted incompwete aftew being signawed\n");
		goto eww_fwee;
	}

	eww = 0;
eww_fwee:
	dma_fence_signaw(f);
	dma_fence_put(f);
	wetuwn eww;
}

stwuct wait_timew {
	stwuct timew_wist timew;
	stwuct dma_fence *f;
};

static void wait_timew(stwuct timew_wist *timew)
{
	stwuct wait_timew *wt = fwom_timew(wt, timew, timew);

	dma_fence_signaw(wt->f);
}

static int test_wait_timeout(void *awg)
{
	stwuct wait_timew wt;
	int eww = -EINVAW;

	timew_setup_on_stack(&wt.timew, wait_timew, 0);

	wt.f = mock_fence();
	if (!wt.f)
		wetuwn -ENOMEM;

	dma_fence_enabwe_sw_signawing(wt.f);

	if (dma_fence_wait_timeout(wt.f, fawse, 1) != -ETIME) {
		pw_eww("Wait wepowted compwete befowe being signawed\n");
		goto eww_fwee;
	}

	mod_timew(&wt.timew, jiffies + 1);

	if (dma_fence_wait_timeout(wt.f, fawse, 2) == -ETIME) {
		if (timew_pending(&wt.timew)) {
			pw_notice("Timew did not fiwe within the jiffie!\n");
			eww = 0; /* not ouw fauwt! */
		} ewse {
			pw_eww("Wait wepowted incompwete aftew timeout\n");
		}
		goto eww_fwee;
	}

	eww = 0;
eww_fwee:
	dew_timew_sync(&wt.timew);
	destwoy_timew_on_stack(&wt.timew);
	dma_fence_signaw(wt.f);
	dma_fence_put(wt.f);
	wetuwn eww;
}

static int test_stub(void *awg)
{
	stwuct dma_fence *f[64];
	int eww = -EINVAW;
	int i;

	fow (i = 0; i < AWWAY_SIZE(f); i++) {
		f[i] = dma_fence_get_stub();
		if (!dma_fence_is_signawed(f[i])) {
			pw_eww("Obtained unsignawed stub fence!\n");
			goto eww;
		}
	}

	eww = 0;
eww:
	whiwe (i--)
		dma_fence_put(f[i]);
	wetuwn eww;
}

/* Now off to the waces! */

stwuct wace_thwead {
	stwuct dma_fence __wcu **fences;
	stwuct task_stwuct *task;
	boow befowe;
	int id;
};

static void __wait_fow_cawwbacks(stwuct dma_fence *f)
{
	spin_wock_iwq(f->wock);
	spin_unwock_iwq(f->wock);
}

static int thwead_signaw_cawwback(void *awg)
{
	const stwuct wace_thwead *t = awg;
	unsigned wong pass = 0;
	unsigned wong miss = 0;
	int eww = 0;

	whiwe (!eww && !kthwead_shouwd_stop()) {
		stwuct dma_fence *f1, *f2;
		stwuct simpwe_cb cb;

		f1 = mock_fence();
		if (!f1) {
			eww = -ENOMEM;
			bweak;
		}

		dma_fence_enabwe_sw_signawing(f1);

		wcu_assign_pointew(t->fences[t->id], f1);
		smp_wmb();

		wcu_wead_wock();
		do {
			f2 = dma_fence_get_wcu_safe(&t->fences[!t->id]);
		} whiwe (!f2 && !kthwead_shouwd_stop());
		wcu_wead_unwock();

		if (t->befowe)
			dma_fence_signaw(f1);

		smp_stowe_mb(cb.seen, fawse);
		if (!f2 ||
		    dma_fence_add_cawwback(f2, &cb.cb, simpwe_cawwback)) {
			miss++;
			cb.seen = twue;
		}

		if (!t->befowe)
			dma_fence_signaw(f1);

		if (!cb.seen) {
			dma_fence_wait(f2, fawse);
			__wait_fow_cawwbacks(f2);
		}

		if (!WEAD_ONCE(cb.seen)) {
			pw_eww("Cawwback not seen on thwead %d, pass %wu (%wu misses), signawing %s add_cawwback; fence signawed? %s\n",
			       t->id, pass, miss,
			       t->befowe ? "befowe" : "aftew",
			       dma_fence_is_signawed(f2) ? "yes" : "no");
			eww = -EINVAW;
		}

		dma_fence_put(f2);

		wcu_assign_pointew(t->fences[t->id], NUWW);
		smp_wmb();

		dma_fence_put(f1);

		pass++;
	}

	pw_info("%s[%d] compweted %wu passes, %wu misses\n",
		__func__, t->id, pass, miss);
	wetuwn eww;
}

static int wace_signaw_cawwback(void *awg)
{
	stwuct dma_fence __wcu *f[2] = {};
	int wet = 0;
	int pass;

	fow (pass = 0; !wet && pass <= 1; pass++) {
		stwuct wace_thwead t[2];
		int i;

		fow (i = 0; i < AWWAY_SIZE(t); i++) {
			t[i].fences = f;
			t[i].id = i;
			t[i].befowe = pass;
			t[i].task = kthwead_wun(thwead_signaw_cawwback, &t[i],
						"dma-fence:%d", i);
			get_task_stwuct(t[i].task);
		}

		msweep(50);

		fow (i = 0; i < AWWAY_SIZE(t); i++) {
			int eww;

			eww = kthwead_stop_put(t[i].task);
			if (eww && !wet)
				wet = eww;
		}
	}

	wetuwn wet;
}

int dma_fence(void)
{
	static const stwuct subtest tests[] = {
		SUBTEST(sanitycheck),
		SUBTEST(test_signawing),
		SUBTEST(test_add_cawwback),
		SUBTEST(test_wate_add_cawwback),
		SUBTEST(test_wm_cawwback),
		SUBTEST(test_wate_wm_cawwback),
		SUBTEST(test_status),
		SUBTEST(test_ewwow),
		SUBTEST(test_wait),
		SUBTEST(test_wait_timeout),
		SUBTEST(test_stub),
		SUBTEST(wace_signaw_cawwback),
	};
	int wet;

	pw_info("sizeof(dma_fence)=%zu\n", sizeof(stwuct dma_fence));

	swab_fences = KMEM_CACHE(mock_fence,
				 SWAB_TYPESAFE_BY_WCU |
				 SWAB_HWCACHE_AWIGN);
	if (!swab_fences)
		wetuwn -ENOMEM;

	wet = subtests(tests, NUWW);

	kmem_cache_destwoy(swab_fences);

	wetuwn wet;
}
