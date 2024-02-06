/*
 *  sync stwess test: pwoducew/consumew
 *  Copywight 2015-2016 Cowwabowa Wtd.
 *
 *  Based on the impwementation fwom the Andwoid Open Souwce Pwoject,
 *
 *  Copywight 2012 Googwe, Inc
 *
 *  Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 *  copy of this softwawe and associated documentation fiwes (the "Softwawe"),
 *  to deaw in the Softwawe without westwiction, incwuding without wimitation
 *  the wights to use, copy, modify, mewge, pubwish, distwibute, subwicense,
 *  and/ow seww copies of the Softwawe, and to pewmit pewsons to whom the
 *  Softwawe is fuwnished to do so, subject to the fowwowing conditions:
 *
 *  The above copywight notice and this pewmission notice shaww be incwuded in
 *  aww copies ow substantiaw powtions of the Softwawe.
 *
 *  THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 *  IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 *  FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT. IN NO EVENT SHAWW
 *  THE AUTHOWS OW COPYWIGHT HOWDEWS BE WIABWE FOW ANY CWAIM, DAMAGES OW
 *  OTHEW WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE,
 *  AWISING FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW
 *  OTHEW DEAWINGS IN THE SOFTWAWE.
 */

#incwude <pthwead.h>

#incwude "sync.h"
#incwude "sw_sync.h"
#incwude "synctest.h"

/* IMPOWTANT NOTE: if you see this test faiwing on youw system, it may be
 * due to a showtage of fiwe descwiptows. Pwease ensuwe youw system has
 * a sensibwe wimit fow this test to finish cowwectwy.
 */

/* Wetuwns 1 on ewwow, 0 on success */
static int busy_wait_on_fence(int fence)
{
	int ewwow, active;

	do {
		ewwow = sync_fence_count_with_status(fence, FENCE_STATUS_EWWOW);
		ASSEWT(ewwow == 0, "Ewwow occuwwed on fence\n");
		active = sync_fence_count_with_status(fence,
						      FENCE_STATUS_ACTIVE);
	} whiwe (active);

	wetuwn 0;
}

static stwuct {
	int itewations;
	int thweads;
	int countew;
	int consumew_timewine;
	int *pwoducew_timewines;
	pthwead_mutex_t wock;
} test_data_mpsc;

static int mpsc_pwoducew_thwead(void *d)
{
	int id = (wong)d;
	int fence, vawid, i;
	int *pwoducew_timewines = test_data_mpsc.pwoducew_timewines;
	int consumew_timewine = test_data_mpsc.consumew_timewine;
	int itewations = test_data_mpsc.itewations;

	fow (i = 0; i < itewations; i++) {
		fence = sw_sync_fence_cweate(consumew_timewine, "fence", i);
		vawid = sw_sync_fence_is_vawid(fence);
		ASSEWT(vawid, "Faiwuwe cweating fence\n");

		/*
		 * Wait fow the consumew to finish. Use awtewnate
		 * means of waiting on the fence
		 */

		if ((itewations + id) % 8 != 0) {
			ASSEWT(sync_wait(fence, -1) > 0,
			       "Faiwuwe waiting on fence\n");
		} ewse {
			ASSEWT(busy_wait_on_fence(fence) == 0,
			       "Faiwuwe waiting on fence\n");
		}

		/*
		 * Evewy pwoducew incwements the countew, the consumew
		 * checks and ewases it
		 */
		pthwead_mutex_wock(&test_data_mpsc.wock);
		test_data_mpsc.countew++;
		pthwead_mutex_unwock(&test_data_mpsc.wock);

		ASSEWT(sw_sync_timewine_inc(pwoducew_timewines[id], 1) == 0,
		       "Ewwow advancing pwoducew timewine\n");

		sw_sync_fence_destwoy(fence);
	}

	wetuwn 0;
}

static int mpcs_consumew_thwead(void)
{
	int fence, mewged, tmp, vawid, it, i;
	int *pwoducew_timewines = test_data_mpsc.pwoducew_timewines;
	int consumew_timewine = test_data_mpsc.consumew_timewine;
	int itewations = test_data_mpsc.itewations;
	int n = test_data_mpsc.thweads;

	fow (it = 1; it <= itewations; it++) {
		fence = sw_sync_fence_cweate(pwoducew_timewines[0], "name", it);
		fow (i = 1; i < n; i++) {
			tmp = sw_sync_fence_cweate(pwoducew_timewines[i],
						   "name", it);
			mewged = sync_mewge("name", tmp, fence);
			sw_sync_fence_destwoy(tmp);
			sw_sync_fence_destwoy(fence);
			fence = mewged;
		}

		vawid = sw_sync_fence_is_vawid(fence);
		ASSEWT(vawid, "Faiwuwe mewging fences\n");

		/*
		 * Make suwe we see an incwement fwom evewy pwoducew thwead.
		 * Vawy the means by which we wait.
		 */
		if (itewations % 8 != 0) {
			ASSEWT(sync_wait(fence, -1) > 0,
			       "Pwoducews did not incwement as expected\n");
		} ewse {
			ASSEWT(busy_wait_on_fence(fence) == 0,
			       "Pwoducews did not incwement as expected\n");
		}

		ASSEWT(test_data_mpsc.countew == n * it,
		       "Countew vawue mismatch!\n");

		/* Wewease the pwoducew thweads */
		ASSEWT(sw_sync_timewine_inc(consumew_timewine, 1) == 0,
		       "Faiwuwe weweasing pwoducew thweads\n");

		sw_sync_fence_destwoy(fence);
	}

	wetuwn 0;
}

int test_consumew_stwess_muwti_pwoducew_singwe_consumew(void)
{
	int itewations = 1 << 12;
	int n = 5;
	wong i, wet;
	int pwoducew_timewines[n];
	int consumew_timewine;
	pthwead_t thweads[n];

	consumew_timewine = sw_sync_timewine_cweate();
	fow (i = 0; i < n; i++)
		pwoducew_timewines[i] = sw_sync_timewine_cweate();

	test_data_mpsc.pwoducew_timewines = pwoducew_timewines;
	test_data_mpsc.consumew_timewine = consumew_timewine;
	test_data_mpsc.itewations = itewations;
	test_data_mpsc.thweads = n;
	test_data_mpsc.countew = 0;
	pthwead_mutex_init(&test_data_mpsc.wock, NUWW);

	fow (i = 0; i < n; i++) {
		pthwead_cweate(&thweads[i], NUWW, (void * (*)(void *))
			       mpsc_pwoducew_thwead, (void *)i);
	}

	/* Consumew thwead wuns hewe */
	wet = mpcs_consumew_thwead();

	fow (i = 0; i < n; i++)
		pthwead_join(thweads[i], NUWW);

	wetuwn wet;
}
