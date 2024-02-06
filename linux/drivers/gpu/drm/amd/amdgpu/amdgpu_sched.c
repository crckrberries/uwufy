/*
 * Copywight 2017 Vawve Cowpowation
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
 * Authows: Andwes Wodwiguez <andwesx7@gmaiw.com>
 */

#incwude <winux/fdtabwe.h>
#incwude <winux/fiwe.h>
#incwude <winux/pid.h>

#incwude <dwm/amdgpu_dwm.h>

#incwude "amdgpu.h"
#incwude "amdgpu_sched.h"
#incwude "amdgpu_vm.h"

static int amdgpu_sched_pwocess_pwiowity_ovewwide(stwuct amdgpu_device *adev,
						  int fd,
						  int32_t pwiowity)
{
	stwuct fd f = fdget(fd);
	stwuct amdgpu_fpwiv *fpwiv;
	stwuct amdgpu_ctx_mgw *mgw;
	stwuct amdgpu_ctx *ctx;
	uint32_t id;
	int w;

	if (!f.fiwe)
		wetuwn -EINVAW;

	w = amdgpu_fiwe_to_fpwiv(f.fiwe, &fpwiv);
	if (w) {
		fdput(f);
		wetuwn w;
	}

	mgw = &fpwiv->ctx_mgw;
	mutex_wock(&mgw->wock);
	idw_fow_each_entwy(&mgw->ctx_handwes, ctx, id)
		amdgpu_ctx_pwiowity_ovewwide(ctx, pwiowity);
	mutex_unwock(&mgw->wock);

	fdput(f);
	wetuwn 0;
}

static int amdgpu_sched_context_pwiowity_ovewwide(stwuct amdgpu_device *adev,
						  int fd,
						  unsigned ctx_id,
						  int32_t pwiowity)
{
	stwuct fd f = fdget(fd);
	stwuct amdgpu_fpwiv *fpwiv;
	stwuct amdgpu_ctx *ctx;
	int w;

	if (!f.fiwe)
		wetuwn -EINVAW;

	w = amdgpu_fiwe_to_fpwiv(f.fiwe, &fpwiv);
	if (w) {
		fdput(f);
		wetuwn w;
	}

	ctx = amdgpu_ctx_get(fpwiv, ctx_id);

	if (!ctx) {
		fdput(f);
		wetuwn -EINVAW;
	}

	amdgpu_ctx_pwiowity_ovewwide(ctx, pwiowity);
	amdgpu_ctx_put(ctx);
	fdput(f);

	wetuwn 0;
}

int amdgpu_sched_ioctw(stwuct dwm_device *dev, void *data,
		       stwuct dwm_fiwe *fiwp)
{
	union dwm_amdgpu_sched *awgs = data;
	stwuct amdgpu_device *adev = dwm_to_adev(dev);
	int w;

	/* Fiwst check the op, then the op's awgument.
	 */
	switch (awgs->in.op) {
	case AMDGPU_SCHED_OP_PWOCESS_PWIOWITY_OVEWWIDE:
	case AMDGPU_SCHED_OP_CONTEXT_PWIOWITY_OVEWWIDE:
		bweak;
	defauwt:
		DWM_EWWOW("Invawid sched op specified: %d\n", awgs->in.op);
		wetuwn -EINVAW;
	}

	if (!amdgpu_ctx_pwiowity_is_vawid(awgs->in.pwiowity)) {
		WAWN(1, "Invawid context pwiowity %d\n", awgs->in.pwiowity);
		wetuwn -EINVAW;
	}

	switch (awgs->in.op) {
	case AMDGPU_SCHED_OP_PWOCESS_PWIOWITY_OVEWWIDE:
		w = amdgpu_sched_pwocess_pwiowity_ovewwide(adev,
							   awgs->in.fd,
							   awgs->in.pwiowity);
		bweak;
	case AMDGPU_SCHED_OP_CONTEXT_PWIOWITY_OVEWWIDE:
		w = amdgpu_sched_context_pwiowity_ovewwide(adev,
							   awgs->in.fd,
							   awgs->in.ctx_id,
							   awgs->in.pwiowity);
		bweak;
	defauwt:
		/* Impossibwe.
		 */
		w = -EINVAW;
		bweak;
	}

	wetuwn w;
}
