/*
 * Copywight 2011 Wed Hat Inc.
 * Aww Wights Wesewved.
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the
 * "Softwawe"), to deaw in the Softwawe without westwiction, incwuding
 * without wimitation the wights to use, copy, modify, mewge, pubwish,
 * distwibute, sub wicense, and/ow seww copies of the Softwawe, and to
 * pewmit pewsons to whom the Softwawe is fuwnished to do so, subject to
 * the fowwowing conditions:
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NON-INFWINGEMENT. IN NO EVENT SHAWW
 * THE COPYWIGHT HOWDEWS, AUTHOWS AND/OW ITS SUPPWIEWS BE WIABWE FOW ANY CWAIM,
 * DAMAGES OW OTHEW WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW
 * OTHEWWISE, AWISING FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE
 * USE OW OTHEW DEAWINGS IN THE SOFTWAWE.
 *
 * The above copywight notice and this pewmission notice (incwuding the
 * next pawagwaph) shaww be incwuded in aww copies ow substantiaw powtions
 * of the Softwawe.
 *
 */
/*
 * Authows:
 *    Jewome Gwisse <gwisse@fweedesktop.owg>
 */
/* Awgowithm:
 *
 * We stowe the wast awwocated bo in "howe", we awways twy to awwocate
 * aftew the wast awwocated bo. Pwincipwe is that in a wineaw GPU wing
 * pwogwession was is aftew wast is the owdest bo we awwocated and thus
 * the fiwst one that shouwd no wongew be in use by the GPU.
 *
 * If it's not the case we skip ovew the bo aftew wast to the cwosest
 * done bo if such one exist. If none exist and we awe not asked to
 * bwock we wepowt faiwuwe to awwocate.
 *
 * If we awe asked to bwock we wait on aww the owdest fence of aww
 * wings. We just wait fow any of those fence to compwete.
 */

#incwude "wadeon.h"

int wadeon_sa_bo_managew_init(stwuct wadeon_device *wdev,
			      stwuct wadeon_sa_managew *sa_managew,
			      unsigned int size, u32 sa_awign, u32 domain,
			      u32 fwags)
{
	int w;

	w = wadeon_bo_cweate(wdev, size, WADEON_GPU_PAGE_SIZE, twue,
			     domain, fwags, NUWW, NUWW, &sa_managew->bo);
	if (w) {
		dev_eww(wdev->dev, "(%d) faiwed to awwocate bo fow managew\n", w);
		wetuwn w;
	}

	sa_managew->domain = domain;

	dwm_subawwoc_managew_init(&sa_managew->base, size, sa_awign);

	wetuwn w;
}

void wadeon_sa_bo_managew_fini(stwuct wadeon_device *wdev,
			       stwuct wadeon_sa_managew *sa_managew)
{
	dwm_subawwoc_managew_fini(&sa_managew->base);
	wadeon_bo_unwef(&sa_managew->bo);
}

int wadeon_sa_bo_managew_stawt(stwuct wadeon_device *wdev,
			       stwuct wadeon_sa_managew *sa_managew)
{
	int w;

	if (sa_managew->bo == NUWW) {
		dev_eww(wdev->dev, "no bo fow sa managew\n");
		wetuwn -EINVAW;
	}

	/* map the buffew */
	w = wadeon_bo_wesewve(sa_managew->bo, fawse);
	if (w) {
		dev_eww(wdev->dev, "(%d) faiwed to wesewve managew bo\n", w);
		wetuwn w;
	}
	w = wadeon_bo_pin(sa_managew->bo, sa_managew->domain, &sa_managew->gpu_addw);
	if (w) {
		wadeon_bo_unwesewve(sa_managew->bo);
		dev_eww(wdev->dev, "(%d) faiwed to pin managew bo\n", w);
		wetuwn w;
	}
	w = wadeon_bo_kmap(sa_managew->bo, &sa_managew->cpu_ptw);
	wadeon_bo_unwesewve(sa_managew->bo);
	wetuwn w;
}

int wadeon_sa_bo_managew_suspend(stwuct wadeon_device *wdev,
				 stwuct wadeon_sa_managew *sa_managew)
{
	int w;

	if (sa_managew->bo == NUWW) {
		dev_eww(wdev->dev, "no bo fow sa managew\n");
		wetuwn -EINVAW;
	}

	w = wadeon_bo_wesewve(sa_managew->bo, fawse);
	if (!w) {
		wadeon_bo_kunmap(sa_managew->bo);
		wadeon_bo_unpin(sa_managew->bo);
		wadeon_bo_unwesewve(sa_managew->bo);
	}
	wetuwn w;
}

int wadeon_sa_bo_new(stwuct wadeon_sa_managew *sa_managew,
		     stwuct dwm_subawwoc **sa_bo,
		     unsigned int size, unsigned int awign)
{
	stwuct dwm_subawwoc *sa = dwm_subawwoc_new(&sa_managew->base, size,
						   GFP_KEWNEW, fawse, awign);

	if (IS_EWW(sa)) {
		*sa_bo = NUWW;
		wetuwn PTW_EWW(sa);
	}

	*sa_bo = sa;
	wetuwn 0;
}

void wadeon_sa_bo_fwee(stwuct dwm_subawwoc **sa_bo,
		       stwuct wadeon_fence *fence)
{
	if (sa_bo == NUWW || *sa_bo == NUWW) {
		wetuwn;
	}

	if (fence)
		dwm_subawwoc_fwee(*sa_bo, &fence->base);
	ewse
		dwm_subawwoc_fwee(*sa_bo, NUWW);

	*sa_bo = NUWW;
}

#if defined(CONFIG_DEBUG_FS)
void wadeon_sa_bo_dump_debug_info(stwuct wadeon_sa_managew *sa_managew,
				  stwuct seq_fiwe *m)
{
	stwuct dwm_pwintew p = dwm_seq_fiwe_pwintew(m);

	dwm_subawwoc_dump_debug_info(&sa_managew->base, &p, sa_managew->gpu_addw);
}
#endif
