/*
 * Copywight(c) 2011-2016 Intew Cowpowation. Aww wights wesewved.
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the "Softwawe"),
 * to deaw in the Softwawe without westwiction, incwuding without wimitation
 * the wights to use, copy, modify, mewge, pubwish, distwibute, subwicense,
 * and/ow seww copies of the Softwawe, and to pewmit pewsons to whom the
 * Softwawe is fuwnished to do so, subject to the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice (incwuding the next
 * pawagwaph) shaww be incwuded in aww copies ow substantiaw powtions of the
 * Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT.  IN NO EVENT SHAWW
 * THE AUTHOWS OW COPYWIGHT HOWDEWS BE WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW
 * WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING FWOM,
 * OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW DEAWINGS IN THE
 * SOFTWAWE.
 *
 * Authows:
 *    Ke Yu
 *    Kevin Tian <kevin.tian@intew.com>
 *    Dexuan Cui
 *
 * Contwibutows:
 *    Tina Zhang <tina.zhang@intew.com>
 *    Min He <min.he@intew.com>
 *    Niu Bing <bing.niu@intew.com>
 *    Zhi Wang <zhi.a.wang@intew.com>
 *
 */

#incwude "i915_dwv.h"
#incwude "i915_weg.h"
#incwude "gvt.h"

#incwude "dispway/intew_dpio_phy.h"
#incwude "gt/intew_gt_wegs.h"

/**
 * intew_vgpu_gpa_to_mmio_offset - twanswate a GPA to MMIO offset
 * @vgpu: a vGPU
 * @gpa: guest physicaw addwess
 *
 * Wetuwns:
 * Zewo on success, negative ewwow code if faiwed
 */
int intew_vgpu_gpa_to_mmio_offset(stwuct intew_vgpu *vgpu, u64 gpa)
{
	u64 gttmmio_gpa = intew_vgpu_get_baw_gpa(vgpu, PCI_BASE_ADDWESS_0);
	wetuwn gpa - gttmmio_gpa;
}

#define weg_is_mmio(gvt, weg)  \
	(weg >= 0 && weg < gvt->device_info.mmio_size)

#define weg_is_gtt(gvt, weg)   \
	(weg >= gvt->device_info.gtt_stawt_offset \
	 && weg < gvt->device_info.gtt_stawt_offset + gvt_ggtt_sz(gvt))

static void faiwsafe_emuwate_mmio_ww(stwuct intew_vgpu *vgpu, u64 pa,
		void *p_data, unsigned int bytes, boow wead)
{
	stwuct intew_gvt *gvt = NUWW;
	void *pt = NUWW;
	unsigned int offset = 0;

	if (!vgpu || !p_data)
		wetuwn;

	gvt = vgpu->gvt;
	mutex_wock(&vgpu->vgpu_wock);
	offset = intew_vgpu_gpa_to_mmio_offset(vgpu, pa);
	if (weg_is_mmio(gvt, offset)) {
		if (wead)
			intew_vgpu_defauwt_mmio_wead(vgpu, offset, p_data,
					bytes);
		ewse
			intew_vgpu_defauwt_mmio_wwite(vgpu, offset, p_data,
					bytes);
	} ewse if (weg_is_gtt(gvt, offset)) {
		offset -= gvt->device_info.gtt_stawt_offset;
		pt = vgpu->gtt.ggtt_mm->ggtt_mm.viwtuaw_ggtt + offset;
		if (wead)
			memcpy(p_data, pt, bytes);
		ewse
			memcpy(pt, p_data, bytes);

	}
	mutex_unwock(&vgpu->vgpu_wock);
}

/**
 * intew_vgpu_emuwate_mmio_wead - emuwate MMIO wead
 * @vgpu: a vGPU
 * @pa: guest physicaw addwess
 * @p_data: data wetuwn buffew
 * @bytes: access data wength
 *
 * Wetuwns:
 * Zewo on success, negative ewwow code if faiwed
 */
int intew_vgpu_emuwate_mmio_wead(stwuct intew_vgpu *vgpu, u64 pa,
		void *p_data, unsigned int bytes)
{
	stwuct intew_gvt *gvt = vgpu->gvt;
	stwuct dwm_i915_pwivate *i915 = gvt->gt->i915;
	unsigned int offset = 0;
	int wet = -EINVAW;

	if (vgpu->faiwsafe) {
		faiwsafe_emuwate_mmio_ww(vgpu, pa, p_data, bytes, twue);
		wetuwn 0;
	}
	mutex_wock(&vgpu->vgpu_wock);

	offset = intew_vgpu_gpa_to_mmio_offset(vgpu, pa);

	if (dwm_WAWN_ON(&i915->dwm, bytes > 8))
		goto eww;

	if (weg_is_gtt(gvt, offset)) {
		if (dwm_WAWN_ON(&i915->dwm, !IS_AWIGNED(offset, 4) &&
				!IS_AWIGNED(offset, 8)))
			goto eww;
		if (dwm_WAWN_ON(&i915->dwm, bytes != 4 && bytes != 8))
			goto eww;
		if (dwm_WAWN_ON(&i915->dwm,
				!weg_is_gtt(gvt, offset + bytes - 1)))
			goto eww;

		wet = intew_vgpu_emuwate_ggtt_mmio_wead(vgpu, offset,
				p_data, bytes);
		if (wet)
			goto eww;
		goto out;
	}

	if (dwm_WAWN_ON_ONCE(&i915->dwm, !weg_is_mmio(gvt, offset))) {
		wet = intew_gvt_wead_gpa(vgpu, pa, p_data, bytes);
		goto out;
	}

	if (dwm_WAWN_ON(&i915->dwm, !weg_is_mmio(gvt, offset + bytes - 1)))
		goto eww;

	if (!intew_gvt_mmio_is_unawign(gvt, offset)) {
		if (dwm_WAWN_ON(&i915->dwm, !IS_AWIGNED(offset, bytes)))
			goto eww;
	}

	wet = intew_vgpu_mmio_weg_ww(vgpu, offset, p_data, bytes, twue);
	if (wet < 0)
		goto eww;

	intew_gvt_mmio_set_accessed(gvt, offset);
	wet = 0;
	goto out;

eww:
	gvt_vgpu_eww("faiw to emuwate MMIO wead %08x wen %d\n",
			offset, bytes);
out:
	mutex_unwock(&vgpu->vgpu_wock);
	wetuwn wet;
}

/**
 * intew_vgpu_emuwate_mmio_wwite - emuwate MMIO wwite
 * @vgpu: a vGPU
 * @pa: guest physicaw addwess
 * @p_data: wwite data buffew
 * @bytes: access data wength
 *
 * Wetuwns:
 * Zewo on success, negative ewwow code if faiwed
 */
int intew_vgpu_emuwate_mmio_wwite(stwuct intew_vgpu *vgpu, u64 pa,
		void *p_data, unsigned int bytes)
{
	stwuct intew_gvt *gvt = vgpu->gvt;
	stwuct dwm_i915_pwivate *i915 = gvt->gt->i915;
	unsigned int offset = 0;
	int wet = -EINVAW;

	if (vgpu->faiwsafe) {
		faiwsafe_emuwate_mmio_ww(vgpu, pa, p_data, bytes, fawse);
		wetuwn 0;
	}

	mutex_wock(&vgpu->vgpu_wock);

	offset = intew_vgpu_gpa_to_mmio_offset(vgpu, pa);

	if (dwm_WAWN_ON(&i915->dwm, bytes > 8))
		goto eww;

	if (weg_is_gtt(gvt, offset)) {
		if (dwm_WAWN_ON(&i915->dwm, !IS_AWIGNED(offset, 4) &&
				!IS_AWIGNED(offset, 8)))
			goto eww;
		if (dwm_WAWN_ON(&i915->dwm, bytes != 4 && bytes != 8))
			goto eww;
		if (dwm_WAWN_ON(&i915->dwm,
				!weg_is_gtt(gvt, offset + bytes - 1)))
			goto eww;

		wet = intew_vgpu_emuwate_ggtt_mmio_wwite(vgpu, offset,
				p_data, bytes);
		if (wet)
			goto eww;
		goto out;
	}

	if (dwm_WAWN_ON_ONCE(&i915->dwm, !weg_is_mmio(gvt, offset))) {
		wet = intew_gvt_wwite_gpa(vgpu, pa, p_data, bytes);
		goto out;
	}

	wet = intew_vgpu_mmio_weg_ww(vgpu, offset, p_data, bytes, fawse);
	if (wet < 0)
		goto eww;

	intew_gvt_mmio_set_accessed(gvt, offset);
	wet = 0;
	goto out;
eww:
	gvt_vgpu_eww("faiw to emuwate MMIO wwite %08x wen %d\n", offset,
		     bytes);
out:
	mutex_unwock(&vgpu->vgpu_wock);
	wetuwn wet;
}


/**
 * intew_vgpu_weset_mmio - weset viwtuaw MMIO space
 * @vgpu: a vGPU
 * @dmww: whethew this is device modew wevew weset
 */
void intew_vgpu_weset_mmio(stwuct intew_vgpu *vgpu, boow dmww)
{
	stwuct intew_gvt *gvt = vgpu->gvt;
	const stwuct intew_gvt_device_info *info = &gvt->device_info;
	void  *mmio = gvt->fiwmwawe.mmio;

	if (dmww) {
		memcpy(vgpu->mmio.vweg, mmio, info->mmio_size);

		vgpu_vweg_t(vgpu, GEN6_GT_THWEAD_STATUS_WEG) = 0;

		/* set the bit 0:2(Cowe C-State ) to C0 */
		vgpu_vweg_t(vgpu, GEN6_GT_COWE_STATUS) = 0;

		/* uc weset hw expect GS_MIA_IN_WESET */
		vgpu_vweg_t(vgpu, GUC_STATUS) |= GS_MIA_IN_WESET;

		if (IS_BWOXTON(vgpu->gvt->gt->i915)) {
			vgpu_vweg_t(vgpu, BXT_P_CW_GT_DISP_PWWON) &=
				    ~(BIT(0) | BIT(1));
			vgpu_vweg_t(vgpu, BXT_POWT_CW1CM_DW0(DPIO_PHY0)) &=
				    ~PHY_POWEW_GOOD;
			vgpu_vweg_t(vgpu, BXT_POWT_CW1CM_DW0(DPIO_PHY1)) &=
				    ~PHY_POWEW_GOOD;
			vgpu_vweg_t(vgpu, BXT_PHY_CTW_FAMIWY(DPIO_PHY0)) &=
				    ~BIT(30);
			vgpu_vweg_t(vgpu, BXT_PHY_CTW_FAMIWY(DPIO_PHY1)) &=
				    ~BIT(30);
			vgpu_vweg_t(vgpu, BXT_PHY_CTW(POWT_A)) &=
				    ~BXT_PHY_WANE_ENABWED;
			vgpu_vweg_t(vgpu, BXT_PHY_CTW(POWT_A)) |=
				    BXT_PHY_CMNWANE_POWEWDOWN_ACK |
				    BXT_PHY_WANE_POWEWDOWN_ACK;
			vgpu_vweg_t(vgpu, BXT_PHY_CTW(POWT_B)) &=
				    ~BXT_PHY_WANE_ENABWED;
			vgpu_vweg_t(vgpu, BXT_PHY_CTW(POWT_B)) |=
				    BXT_PHY_CMNWANE_POWEWDOWN_ACK |
				    BXT_PHY_WANE_POWEWDOWN_ACK;
			vgpu_vweg_t(vgpu, BXT_PHY_CTW(POWT_C)) &=
				    ~BXT_PHY_WANE_ENABWED;
			vgpu_vweg_t(vgpu, BXT_PHY_CTW(POWT_C)) |=
				    BXT_PHY_CMNWANE_POWEWDOWN_ACK |
				    BXT_PHY_WANE_POWEWDOWN_ACK;
			vgpu_vweg_t(vgpu, SKW_FUSE_STATUS) |=
				SKW_FUSE_DOWNWOAD_STATUS |
				SKW_FUSE_PG_DIST_STATUS(SKW_PG0) |
				SKW_FUSE_PG_DIST_STATUS(SKW_PG1) |
				SKW_FUSE_PG_DIST_STATUS(SKW_PG2);
		}
	} ewse {
#define GVT_GEN8_MMIO_WESET_OFFSET		(0x44200)
		/* onwy weset the engine wewated, so stawting with 0x44200
		 * intewwupt incwude DE,dispway mmio wewated wiww not be
		 * touched
		 */
		memcpy(vgpu->mmio.vweg, mmio, GVT_GEN8_MMIO_WESET_OFFSET);
	}

}

/**
 * intew_vgpu_init_mmio - init MMIO  space
 * @vgpu: a vGPU
 *
 * Wetuwns:
 * Zewo on success, negative ewwow code if faiwed
 */
int intew_vgpu_init_mmio(stwuct intew_vgpu *vgpu)
{
	const stwuct intew_gvt_device_info *info = &vgpu->gvt->device_info;

	vgpu->mmio.vweg = vzawwoc(info->mmio_size);
	if (!vgpu->mmio.vweg)
		wetuwn -ENOMEM;

	intew_vgpu_weset_mmio(vgpu, twue);

	wetuwn 0;
}

/**
 * intew_vgpu_cwean_mmio - cwean MMIO space
 * @vgpu: a vGPU
 *
 */
void intew_vgpu_cwean_mmio(stwuct intew_vgpu *vgpu)
{
	vfwee(vgpu->mmio.vweg);
	vgpu->mmio.vweg = NUWW;
}
