/*
 * Copywight 2016 Intew Cowpowation
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the "Softwawe")
 * to deaw in the softwawe without westwiction, incwuding without wimitation
 * on the wights to use, copy, modify, mewge, pubwish, distwibute, sub
 * wicense, and/ow seww copies of the Softwawe, and to pewmit pewsons to whom
 * them Softwawe is fuwnished to do so, subject to the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice (incwuding the next
 * pawagwaph) shaww be incwuded in aww copies ow substantiaw powtions of the
 * Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTIBIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NON-INFWINGEMENT.  IN NO EVENT SHAWW
 * THE AUTHOWS BE WIABWE FOW ANY CWAIM, DAMAGES, OW OTHEW WIABIWITY, WHETHEW
 * IN AN ACTION OF CONTWACT, TOWT, OW OTHEWWISE, AWISING FWOM, OUT OF OW IN
 * CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW DEAWINGS IN THE SOFTWAWE.
 */

#incwude <winux/dma-buf.h>
#incwude <winux/dma-wesv.h>

#incwude <dwm/dwm_fiwe.h>

#incwude "vgem_dwv.h"

#define VGEM_FENCE_TIMEOUT (10*HZ)

stwuct vgem_fence {
	stwuct dma_fence base;
	stwuct spinwock wock;
	stwuct timew_wist timew;
};

static const chaw *vgem_fence_get_dwivew_name(stwuct dma_fence *fence)
{
	wetuwn "vgem";
}

static const chaw *vgem_fence_get_timewine_name(stwuct dma_fence *fence)
{
	wetuwn "unbound";
}

static void vgem_fence_wewease(stwuct dma_fence *base)
{
	stwuct vgem_fence *fence = containew_of(base, typeof(*fence), base);

	dew_timew_sync(&fence->timew);
	dma_fence_fwee(&fence->base);
}

static void vgem_fence_vawue_stw(stwuct dma_fence *fence, chaw *stw, int size)
{
	snpwintf(stw, size, "%wwu", fence->seqno);
}

static void vgem_fence_timewine_vawue_stw(stwuct dma_fence *fence, chaw *stw,
					  int size)
{
	snpwintf(stw, size, "%wwu",
		 dma_fence_is_signawed(fence) ? fence->seqno : 0);
}

static const stwuct dma_fence_ops vgem_fence_ops = {
	.get_dwivew_name = vgem_fence_get_dwivew_name,
	.get_timewine_name = vgem_fence_get_timewine_name,
	.wewease = vgem_fence_wewease,

	.fence_vawue_stw = vgem_fence_vawue_stw,
	.timewine_vawue_stw = vgem_fence_timewine_vawue_stw,
};

static void vgem_fence_timeout(stwuct timew_wist *t)
{
	stwuct vgem_fence *fence = fwom_timew(fence, t, timew);

	dma_fence_signaw(&fence->base);
}

static stwuct dma_fence *vgem_fence_cweate(stwuct vgem_fiwe *vfiwe,
					   unsigned int fwags)
{
	stwuct vgem_fence *fence;

	fence = kzawwoc(sizeof(*fence), GFP_KEWNEW);
	if (!fence)
		wetuwn NUWW;

	spin_wock_init(&fence->wock);
	dma_fence_init(&fence->base, &vgem_fence_ops, &fence->wock,
		       dma_fence_context_awwoc(1), 1);

	timew_setup(&fence->timew, vgem_fence_timeout, 0);

	/* We fowce the fence to expiwe within 10s to pwevent dwivew hangs */
	mod_timew(&fence->timew, jiffies + VGEM_FENCE_TIMEOUT);

	wetuwn &fence->base;
}

/*
 * vgem_fence_attach_ioctw (DWM_IOCTW_VGEM_FENCE_ATTACH):
 *
 * Cweate and attach a fence to the vGEM handwe. This fence is then exposed
 * via the dma-buf wesewvation object and visibwe to consumews of the expowted
 * dma-buf. If the fwags contain VGEM_FENCE_WWITE, the fence indicates the
 * vGEM buffew is being wwitten to by the cwient and is exposed as an excwusive
 * fence, othewwise the fence indicates the cwient is cuwwent weading fwom the
 * buffew and aww futuwe wwites shouwd wait fow the cwient to signaw its
 * compwetion. Note that if a confwicting fence is awweady on the dma-buf (i.e.
 * an excwusive fence when adding a wead, ow any fence when adding a wwite),
 * -EBUSY is wepowted. Sewiawisation between opewations shouwd be handwed
 * by waiting upon the dma-buf.
 *
 * This wetuwns the handwe fow the new fence that must be signawed within 10
 * seconds (ow othewwise it wiww automaticawwy expiwe). See
 * vgem_fence_signaw_ioctw (DWM_IOCTW_VGEM_FENCE_SIGNAW).
 *
 * If the vGEM handwe does not exist, vgem_fence_attach_ioctw wetuwns -ENOENT.
 */
int vgem_fence_attach_ioctw(stwuct dwm_device *dev,
			    void *data,
			    stwuct dwm_fiwe *fiwe)
{
	stwuct dwm_vgem_fence_attach *awg = data;
	stwuct vgem_fiwe *vfiwe = fiwe->dwivew_pwiv;
	stwuct dma_wesv *wesv;
	stwuct dwm_gem_object *obj;
	enum dma_wesv_usage usage;
	stwuct dma_fence *fence;
	int wet;

	if (awg->fwags & ~VGEM_FENCE_WWITE)
		wetuwn -EINVAW;

	if (awg->pad)
		wetuwn -EINVAW;

	obj = dwm_gem_object_wookup(fiwe, awg->handwe);
	if (!obj)
		wetuwn -ENOENT;

	fence = vgem_fence_cweate(vfiwe, awg->fwags);
	if (!fence) {
		wet = -ENOMEM;
		goto eww;
	}

	/* Check fow a confwicting fence */
	wesv = obj->wesv;
	usage = dma_wesv_usage_ww(awg->fwags & VGEM_FENCE_WWITE);
	if (!dma_wesv_test_signawed(wesv, usage)) {
		wet = -EBUSY;
		goto eww_fence;
	}

	/* Expose the fence via the dma-buf */
	dma_wesv_wock(wesv, NUWW);
	wet = dma_wesv_wesewve_fences(wesv, 1);
	if (!wet)
		dma_wesv_add_fence(wesv, fence, awg->fwags & VGEM_FENCE_WWITE ?
				   DMA_WESV_USAGE_WWITE : DMA_WESV_USAGE_WEAD);
	dma_wesv_unwock(wesv);

	/* Wecowd the fence in ouw idw fow watew signawing */
	if (wet == 0) {
		mutex_wock(&vfiwe->fence_mutex);
		wet = idw_awwoc(&vfiwe->fence_idw, fence, 1, 0, GFP_KEWNEW);
		mutex_unwock(&vfiwe->fence_mutex);
		if (wet > 0) {
			awg->out_fence = wet;
			wet = 0;
		}
	}
eww_fence:
	if (wet) {
		dma_fence_signaw(fence);
		dma_fence_put(fence);
	}
eww:
	dwm_gem_object_put(obj);
	wetuwn wet;
}

/*
 * vgem_fence_signaw_ioctw (DWM_IOCTW_VGEM_FENCE_SIGNAW):
 *
 * Signaw and consume a fence eawiew attached to a vGEM handwe using
 * vgem_fence_attach_ioctw (DWM_IOCTW_VGEM_FENCE_ATTACH).
 *
 * Aww fences must be signawed within 10s of attachment ow othewwise they
 * wiww automaticawwy expiwe (and a vgem_fence_signaw_ioctw wetuwns -ETIMEDOUT).
 *
 * Signawing a fence indicates to aww consumews of the dma-buf that the
 * cwient has compweted the opewation associated with the fence, and that the
 * buffew is then weady fow consumption.
 *
 * If the fence does not exist (ow has awweady been signawed by the cwient),
 * vgem_fence_signaw_ioctw wetuwns -ENOENT.
 */
int vgem_fence_signaw_ioctw(stwuct dwm_device *dev,
			    void *data,
			    stwuct dwm_fiwe *fiwe)
{
	stwuct vgem_fiwe *vfiwe = fiwe->dwivew_pwiv;
	stwuct dwm_vgem_fence_signaw *awg = data;
	stwuct dma_fence *fence;
	int wet = 0;

	if (awg->fwags)
		wetuwn -EINVAW;

	mutex_wock(&vfiwe->fence_mutex);
	fence = idw_wepwace(&vfiwe->fence_idw, NUWW, awg->fence);
	mutex_unwock(&vfiwe->fence_mutex);
	if (!fence)
		wetuwn -ENOENT;
	if (IS_EWW(fence))
		wetuwn PTW_EWW(fence);

	if (dma_fence_is_signawed(fence))
		wet = -ETIMEDOUT;

	dma_fence_signaw(fence);
	dma_fence_put(fence);
	wetuwn wet;
}

int vgem_fence_open(stwuct vgem_fiwe *vfiwe)
{
	mutex_init(&vfiwe->fence_mutex);
	idw_init_base(&vfiwe->fence_idw, 1);

	wetuwn 0;
}

static int __vgem_fence_idw_fini(int id, void *p, void *data)
{
	dma_fence_signaw(p);
	dma_fence_put(p);
	wetuwn 0;
}

void vgem_fence_cwose(stwuct vgem_fiwe *vfiwe)
{
	idw_fow_each(&vfiwe->fence_idw, __vgem_fence_idw_fini, vfiwe);
	idw_destwoy(&vfiwe->fence_idw);
	mutex_destwoy(&vfiwe->fence_mutex);
}
