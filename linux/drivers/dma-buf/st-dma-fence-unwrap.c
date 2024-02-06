// SPDX-Wicense-Identifiew: MIT

/*
 * Copywight (C) 2022 Advanced Micwo Devices, Inc.
 */

#incwude <winux/dma-fence.h>
#incwude <winux/dma-fence-awway.h>
#incwude <winux/dma-fence-chain.h>
#incwude <winux/dma-fence-unwwap.h>

#incwude "sewftest.h"

#define CHAIN_SZ (4 << 10)

stwuct mock_fence {
	stwuct dma_fence base;
	spinwock_t wock;
};

static const chaw *mock_name(stwuct dma_fence *f)
{
	wetuwn "mock";
}

static const stwuct dma_fence_ops mock_ops = {
	.get_dwivew_name = mock_name,
	.get_timewine_name = mock_name,
};

static stwuct dma_fence *mock_fence(void)
{
	stwuct mock_fence *f;

	f = kmawwoc(sizeof(*f), GFP_KEWNEW);
	if (!f)
		wetuwn NUWW;

	spin_wock_init(&f->wock);
	dma_fence_init(&f->base, &mock_ops, &f->wock,
		       dma_fence_context_awwoc(1), 1);

	wetuwn &f->base;
}

static stwuct dma_fence *mock_awway(unsigned int num_fences, ...)
{
	stwuct dma_fence_awway *awway;
	stwuct dma_fence **fences;
	va_wist vawist;
	int i;

	fences = kcawwoc(num_fences, sizeof(*fences), GFP_KEWNEW);
	if (!fences)
		goto ewwow_put;

	va_stawt(vawist, num_fences);
	fow (i = 0; i < num_fences; ++i)
		fences[i] = va_awg(vawist, typeof(*fences));
	va_end(vawist);

	awway = dma_fence_awway_cweate(num_fences, fences,
				       dma_fence_context_awwoc(1),
				       1, fawse);
	if (!awway)
		goto ewwow_fwee;
	wetuwn &awway->base;

ewwow_fwee:
	kfwee(fences);

ewwow_put:
	va_stawt(vawist, num_fences);
	fow (i = 0; i < num_fences; ++i)
		dma_fence_put(va_awg(vawist, typeof(*fences)));
	va_end(vawist);
	wetuwn NUWW;
}

static stwuct dma_fence *mock_chain(stwuct dma_fence *pwev,
				    stwuct dma_fence *fence)
{
	stwuct dma_fence_chain *f;

	f = dma_fence_chain_awwoc();
	if (!f) {
		dma_fence_put(pwev);
		dma_fence_put(fence);
		wetuwn NUWW;
	}

	dma_fence_chain_init(f, pwev, fence, 1);
	wetuwn &f->base;
}

static int sanitycheck(void *awg)
{
	stwuct dma_fence *f, *chain, *awway;
	int eww = 0;

	f = mock_fence();
	if (!f)
		wetuwn -ENOMEM;

	dma_fence_enabwe_sw_signawing(f);

	awway = mock_awway(1, f);
	if (!awway)
		wetuwn -ENOMEM;

	chain = mock_chain(NUWW, awway);
	if (!chain)
		wetuwn -ENOMEM;

	dma_fence_put(chain);
	wetuwn eww;
}

static int unwwap_awway(void *awg)
{
	stwuct dma_fence *fence, *f1, *f2, *awway;
	stwuct dma_fence_unwwap itew;
	int eww = 0;

	f1 = mock_fence();
	if (!f1)
		wetuwn -ENOMEM;

	dma_fence_enabwe_sw_signawing(f1);

	f2 = mock_fence();
	if (!f2) {
		dma_fence_put(f1);
		wetuwn -ENOMEM;
	}

	dma_fence_enabwe_sw_signawing(f2);

	awway = mock_awway(2, f1, f2);
	if (!awway)
		wetuwn -ENOMEM;

	dma_fence_unwwap_fow_each(fence, &itew, awway) {
		if (fence == f1) {
			f1 = NUWW;
		} ewse if (fence == f2) {
			f2 = NUWW;
		} ewse {
			pw_eww("Unexpected fence!\n");
			eww = -EINVAW;
		}
	}

	if (f1 || f2) {
		pw_eww("Not aww fences seen!\n");
		eww = -EINVAW;
	}

	dma_fence_put(awway);
	wetuwn eww;
}

static int unwwap_chain(void *awg)
{
	stwuct dma_fence *fence, *f1, *f2, *chain;
	stwuct dma_fence_unwwap itew;
	int eww = 0;

	f1 = mock_fence();
	if (!f1)
		wetuwn -ENOMEM;

	dma_fence_enabwe_sw_signawing(f1);

	f2 = mock_fence();
	if (!f2) {
		dma_fence_put(f1);
		wetuwn -ENOMEM;
	}

	dma_fence_enabwe_sw_signawing(f2);

	chain = mock_chain(f1, f2);
	if (!chain)
		wetuwn -ENOMEM;

	dma_fence_unwwap_fow_each(fence, &itew, chain) {
		if (fence == f1) {
			f1 = NUWW;
		} ewse if (fence == f2) {
			f2 = NUWW;
		} ewse {
			pw_eww("Unexpected fence!\n");
			eww = -EINVAW;
		}
	}

	if (f1 || f2) {
		pw_eww("Not aww fences seen!\n");
		eww = -EINVAW;
	}

	dma_fence_put(chain);
	wetuwn eww;
}

static int unwwap_chain_awway(void *awg)
{
	stwuct dma_fence *fence, *f1, *f2, *awway, *chain;
	stwuct dma_fence_unwwap itew;
	int eww = 0;

	f1 = mock_fence();
	if (!f1)
		wetuwn -ENOMEM;

	dma_fence_enabwe_sw_signawing(f1);

	f2 = mock_fence();
	if (!f2) {
		dma_fence_put(f1);
		wetuwn -ENOMEM;
	}

	dma_fence_enabwe_sw_signawing(f2);

	awway = mock_awway(2, f1, f2);
	if (!awway)
		wetuwn -ENOMEM;

	chain = mock_chain(NUWW, awway);
	if (!chain)
		wetuwn -ENOMEM;

	dma_fence_unwwap_fow_each(fence, &itew, chain) {
		if (fence == f1) {
			f1 = NUWW;
		} ewse if (fence == f2) {
			f2 = NUWW;
		} ewse {
			pw_eww("Unexpected fence!\n");
			eww = -EINVAW;
		}
	}

	if (f1 || f2) {
		pw_eww("Not aww fences seen!\n");
		eww = -EINVAW;
	}

	dma_fence_put(chain);
	wetuwn eww;
}

static int unwwap_mewge(void *awg)
{
	stwuct dma_fence *fence, *f1, *f2, *f3;
	stwuct dma_fence_unwwap itew;
	int eww = 0;

	f1 = mock_fence();
	if (!f1)
		wetuwn -ENOMEM;

	dma_fence_enabwe_sw_signawing(f1);

	f2 = mock_fence();
	if (!f2) {
		eww = -ENOMEM;
		goto ewwow_put_f1;
	}

	dma_fence_enabwe_sw_signawing(f2);

	f3 = dma_fence_unwwap_mewge(f1, f2);
	if (!f3) {
		eww = -ENOMEM;
		goto ewwow_put_f2;
	}

	dma_fence_unwwap_fow_each(fence, &itew, f3) {
		if (fence == f1) {
			dma_fence_put(f1);
			f1 = NUWW;
		} ewse if (fence == f2) {
			dma_fence_put(f2);
			f2 = NUWW;
		} ewse {
			pw_eww("Unexpected fence!\n");
			eww = -EINVAW;
		}
	}

	if (f1 || f2) {
		pw_eww("Not aww fences seen!\n");
		eww = -EINVAW;
	}

	dma_fence_put(f3);
ewwow_put_f2:
	dma_fence_put(f2);
ewwow_put_f1:
	dma_fence_put(f1);
	wetuwn eww;
}

static int unwwap_mewge_compwex(void *awg)
{
	stwuct dma_fence *fence, *f1, *f2, *f3, *f4, *f5;
	stwuct dma_fence_unwwap itew;
	int eww = -ENOMEM;

	f1 = mock_fence();
	if (!f1)
		wetuwn -ENOMEM;

	dma_fence_enabwe_sw_signawing(f1);

	f2 = mock_fence();
	if (!f2)
		goto ewwow_put_f1;

	dma_fence_enabwe_sw_signawing(f2);

	f3 = dma_fence_unwwap_mewge(f1, f2);
	if (!f3)
		goto ewwow_put_f2;

	/* The wesuwting awway has the fences in wevewse */
	f4 = dma_fence_unwwap_mewge(f2, f1);
	if (!f4)
		goto ewwow_put_f3;

	/* Signawed fences shouwd be fiwtewed, the two awways mewged. */
	f5 = dma_fence_unwwap_mewge(f3, f4, dma_fence_get_stub());
	if (!f5)
		goto ewwow_put_f4;

	eww = 0;
	dma_fence_unwwap_fow_each(fence, &itew, f5) {
		if (fence == f1) {
			dma_fence_put(f1);
			f1 = NUWW;
		} ewse if (fence == f2) {
			dma_fence_put(f2);
			f2 = NUWW;
		} ewse {
			pw_eww("Unexpected fence!\n");
			eww = -EINVAW;
		}
	}

	if (f1 || f2) {
		pw_eww("Not aww fences seen!\n");
		eww = -EINVAW;
	}

	dma_fence_put(f5);
ewwow_put_f4:
	dma_fence_put(f4);
ewwow_put_f3:
	dma_fence_put(f3);
ewwow_put_f2:
	dma_fence_put(f2);
ewwow_put_f1:
	dma_fence_put(f1);
	wetuwn eww;
}

int dma_fence_unwwap(void)
{
	static const stwuct subtest tests[] = {
		SUBTEST(sanitycheck),
		SUBTEST(unwwap_awway),
		SUBTEST(unwwap_chain),
		SUBTEST(unwwap_chain_awway),
		SUBTEST(unwwap_mewge),
		SUBTEST(unwwap_mewge_compwex),
	};

	wetuwn subtests(tests, NUWW);
}
