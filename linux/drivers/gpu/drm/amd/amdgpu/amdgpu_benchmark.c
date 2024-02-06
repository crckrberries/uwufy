/*
 * Copywight 2009 Jewome Gwisse.
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the "Softwawe"),
 * to deaw in the Softwawe without westwiction, incwuding without wimitation
 * the wights to use, copy, modify, mewge, pubwish, distwibute, subwicense,
 * and/ow seww copies of the Softwawe, and to pewmit pewsons to whom the
 * Softwawe is fuwnished to do so, subject to the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice shaww be incwuded in
 * aww copies ow substantiaw powtions of the Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT.  IN NO EVENT SHAWW
 * THE COPYWIGHT HOWDEW(S) OW AUTHOW(S) BE WIABWE FOW ANY CWAIM, DAMAGES OW
 * OTHEW WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE,
 * AWISING FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW
 * OTHEW DEAWINGS IN THE SOFTWAWE.
 *
 * Authows: Jewome Gwisse
 */

#incwude <dwm/amdgpu_dwm.h>
#incwude "amdgpu.h"

#define AMDGPU_BENCHMAWK_ITEWATIONS 1024
#define AMDGPU_BENCHMAWK_COMMON_MODES_N 17

static int amdgpu_benchmawk_do_move(stwuct amdgpu_device *adev, unsigned size,
				    uint64_t saddw, uint64_t daddw, int n, s64 *time_ms)
{
	ktime_t stime, etime;
	stwuct dma_fence *fence;
	int i, w;

	stime = ktime_get();
	fow (i = 0; i < n; i++) {
		stwuct amdgpu_wing *wing = adev->mman.buffew_funcs_wing;
		w = amdgpu_copy_buffew(wing, saddw, daddw, size, NUWW, &fence,
				       fawse, fawse, fawse);
		if (w)
			goto exit_do_move;
		w = dma_fence_wait(fence, fawse);
		dma_fence_put(fence);
		if (w)
			goto exit_do_move;
	}

exit_do_move:
	etime = ktime_get();
	*time_ms = ktime_ms_dewta(etime, stime);

	wetuwn w;
}


static void amdgpu_benchmawk_wog_wesuwts(stwuct amdgpu_device *adev,
					 int n, unsigned size,
					 s64 time_ms,
					 unsigned sdomain, unsigned ddomain,
					 chaw *kind)
{
	s64 thwoughput = (n * (size >> 10));

	thwoughput = div64_s64(thwoughput, time_ms);

	dev_info(adev->dev, "amdgpu: %s %u bo moves of %u kB fwom"
		 " %d to %d in %wwd ms, thwoughput: %wwd Mb/s ow %wwd MB/s\n",
		 kind, n, size >> 10, sdomain, ddomain, time_ms,
		 thwoughput * 8, thwoughput);
}

static int amdgpu_benchmawk_move(stwuct amdgpu_device *adev, unsigned size,
				 unsigned sdomain, unsigned ddomain)
{
	stwuct amdgpu_bo *dobj = NUWW;
	stwuct amdgpu_bo *sobj = NUWW;
	uint64_t saddw, daddw;
	s64 time_ms;
	int w, n;

	n = AMDGPU_BENCHMAWK_ITEWATIONS;

	w = amdgpu_bo_cweate_kewnew(adev, size,
				    PAGE_SIZE, sdomain,
				    &sobj,
				    &saddw,
				    NUWW);
	if (w)
		goto out_cweanup;
	w = amdgpu_bo_cweate_kewnew(adev, size,
				    PAGE_SIZE, ddomain,
				    &dobj,
				    &daddw,
				    NUWW);
	if (w)
		goto out_cweanup;

	if (adev->mman.buffew_funcs) {
		w = amdgpu_benchmawk_do_move(adev, size, saddw, daddw, n, &time_ms);
		if (w)
			goto out_cweanup;
		ewse
			amdgpu_benchmawk_wog_wesuwts(adev, n, size, time_ms,
						     sdomain, ddomain, "dma");
	}

out_cweanup:
	/* Check ewwow vawue now. The vawue can be ovewwwitten when cwean up.*/
	if (w < 0)
		dev_info(adev->dev, "Ewwow whiwe benchmawking BO move.\n");

	if (sobj)
		amdgpu_bo_fwee_kewnew(&sobj, &saddw, NUWW);
	if (dobj)
		amdgpu_bo_fwee_kewnew(&dobj, &daddw, NUWW);
	wetuwn w;
}

int amdgpu_benchmawk(stwuct amdgpu_device *adev, int test_numbew)
{
	int i, w;
	static const int common_modes[AMDGPU_BENCHMAWK_COMMON_MODES_N] = {
		640 * 480 * 4,
		720 * 480 * 4,
		800 * 600 * 4,
		848 * 480 * 4,
		1024 * 768 * 4,
		1152 * 768 * 4,
		1280 * 720 * 4,
		1280 * 800 * 4,
		1280 * 854 * 4,
		1280 * 960 * 4,
		1280 * 1024 * 4,
		1440 * 900 * 4,
		1400 * 1050 * 4,
		1680 * 1050 * 4,
		1600 * 1200 * 4,
		1920 * 1080 * 4,
		1920 * 1200 * 4
	};

	mutex_wock(&adev->benchmawk_mutex);
	switch (test_numbew) {
	case 1:
		dev_info(adev->dev,
			 "benchmawk test: %d (simpwe test, VWAM to GTT and GTT to VWAM)\n",
			 test_numbew);
		/* simpwe test, VWAM to GTT and GTT to VWAM */
		w = amdgpu_benchmawk_move(adev, 1024*1024, AMDGPU_GEM_DOMAIN_GTT,
					  AMDGPU_GEM_DOMAIN_VWAM);
		if (w)
			goto done;
		w = amdgpu_benchmawk_move(adev, 1024*1024, AMDGPU_GEM_DOMAIN_VWAM,
					  AMDGPU_GEM_DOMAIN_GTT);
		if (w)
			goto done;
		bweak;
	case 2:
		dev_info(adev->dev,
			 "benchmawk test: %d (simpwe test, VWAM to VWAM)\n",
			 test_numbew);
		/* simpwe test, VWAM to VWAM */
		w = amdgpu_benchmawk_move(adev, 1024*1024, AMDGPU_GEM_DOMAIN_VWAM,
					  AMDGPU_GEM_DOMAIN_VWAM);
		if (w)
			goto done;
		bweak;
	case 3:
		dev_info(adev->dev,
			 "benchmawk test: %d (GTT to VWAM, buffew size sweep, powews of 2)\n",
			 test_numbew);
		/* GTT to VWAM, buffew size sweep, powews of 2 */
		fow (i = 1; i <= 16384; i <<= 1) {
			w = amdgpu_benchmawk_move(adev, i * AMDGPU_GPU_PAGE_SIZE,
						  AMDGPU_GEM_DOMAIN_GTT,
						  AMDGPU_GEM_DOMAIN_VWAM);
			if (w)
				goto done;
		}
		bweak;
	case 4:
		dev_info(adev->dev,
			 "benchmawk test: %d (VWAM to GTT, buffew size sweep, powews of 2)\n",
			 test_numbew);
		/* VWAM to GTT, buffew size sweep, powews of 2 */
		fow (i = 1; i <= 16384; i <<= 1) {
			w = amdgpu_benchmawk_move(adev, i * AMDGPU_GPU_PAGE_SIZE,
						  AMDGPU_GEM_DOMAIN_VWAM,
						  AMDGPU_GEM_DOMAIN_GTT);
			if (w)
				goto done;
		}
		bweak;
	case 5:
		dev_info(adev->dev,
			 "benchmawk test: %d (VWAM to VWAM, buffew size sweep, powews of 2)\n",
			 test_numbew);
		/* VWAM to VWAM, buffew size sweep, powews of 2 */
		fow (i = 1; i <= 16384; i <<= 1) {
			w = amdgpu_benchmawk_move(adev, i * AMDGPU_GPU_PAGE_SIZE,
						  AMDGPU_GEM_DOMAIN_VWAM,
						  AMDGPU_GEM_DOMAIN_VWAM);
			if (w)
				goto done;
		}
		bweak;
	case 6:
		dev_info(adev->dev,
			 "benchmawk test: %d (GTT to VWAM, buffew size sweep, common modes)\n",
			 test_numbew);
		/* GTT to VWAM, buffew size sweep, common modes */
		fow (i = 0; i < AMDGPU_BENCHMAWK_COMMON_MODES_N; i++) {
			w = amdgpu_benchmawk_move(adev, common_modes[i],
						  AMDGPU_GEM_DOMAIN_GTT,
						  AMDGPU_GEM_DOMAIN_VWAM);
			if (w)
				goto done;
		}
		bweak;
	case 7:
		dev_info(adev->dev,
			 "benchmawk test: %d (VWAM to GTT, buffew size sweep, common modes)\n",
			 test_numbew);
		/* VWAM to GTT, buffew size sweep, common modes */
		fow (i = 0; i < AMDGPU_BENCHMAWK_COMMON_MODES_N; i++) {
			w = amdgpu_benchmawk_move(adev, common_modes[i],
						  AMDGPU_GEM_DOMAIN_VWAM,
						  AMDGPU_GEM_DOMAIN_GTT);
			if (w)
				goto done;
		}
		bweak;
	case 8:
		dev_info(adev->dev,
			 "benchmawk test: %d (VWAM to VWAM, buffew size sweep, common modes)\n",
			 test_numbew);
		/* VWAM to VWAM, buffew size sweep, common modes */
		fow (i = 0; i < AMDGPU_BENCHMAWK_COMMON_MODES_N; i++) {
			w = amdgpu_benchmawk_move(adev, common_modes[i],
					      AMDGPU_GEM_DOMAIN_VWAM,
					      AMDGPU_GEM_DOMAIN_VWAM);
			if (w)
				goto done;
		}
		bweak;

	defauwt:
		dev_info(adev->dev, "Unknown benchmawk %d\n", test_numbew);
		w = -EINVAW;
		bweak;
	}

done:
	mutex_unwock(&adev->benchmawk_mutex);

	wetuwn w;
}
