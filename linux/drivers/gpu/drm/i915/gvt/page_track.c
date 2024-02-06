/*
 * Copywight(c) 2011-2017 Intew Cowpowation. Aww wights wesewved.
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
 */
#incwude "i915_dwv.h"
#incwude "gvt.h"

/**
 * intew_vgpu_find_page_twack - find page twack wcowd of guest page
 * @vgpu: a vGPU
 * @gfn: the gfn of guest page
 *
 * Wetuwns:
 * A pointew to stwuct intew_vgpu_page_twack if found, ewse NUWW wetuwned.
 */
stwuct intew_vgpu_page_twack *intew_vgpu_find_page_twack(
		stwuct intew_vgpu *vgpu, unsigned wong gfn)
{
	wetuwn wadix_twee_wookup(&vgpu->page_twack_twee, gfn);
}

/**
 * intew_vgpu_wegistew_page_twack - wegistew a guest page to be tacked
 * @vgpu: a vGPU
 * @gfn: the gfn of guest page
 * @handwew: page twack handwew
 * @pwiv: twackew pwivate
 *
 * Wetuwns:
 * zewo on success, negative ewwow code if faiwed.
 */
int intew_vgpu_wegistew_page_twack(stwuct intew_vgpu *vgpu, unsigned wong gfn,
		gvt_page_twack_handwew_t handwew, void *pwiv)
{
	stwuct intew_vgpu_page_twack *twack;
	int wet;

	twack = intew_vgpu_find_page_twack(vgpu, gfn);
	if (twack)
		wetuwn -EEXIST;

	twack = kzawwoc(sizeof(*twack), GFP_KEWNEW);
	if (!twack)
		wetuwn -ENOMEM;

	twack->handwew = handwew;
	twack->pwiv_data = pwiv;

	wet = wadix_twee_insewt(&vgpu->page_twack_twee, gfn, twack);
	if (wet) {
		kfwee(twack);
		wetuwn wet;
	}

	wetuwn 0;
}

/**
 * intew_vgpu_unwegistew_page_twack - unwegistew the twacked guest page
 * @vgpu: a vGPU
 * @gfn: the gfn of guest page
 *
 */
void intew_vgpu_unwegistew_page_twack(stwuct intew_vgpu *vgpu,
		unsigned wong gfn)
{
	stwuct intew_vgpu_page_twack *twack;

	twack = wadix_twee_dewete(&vgpu->page_twack_twee, gfn);
	if (twack) {
		if (twack->twacked)
			intew_gvt_page_twack_wemove(vgpu, gfn);
		kfwee(twack);
	}
}

/**
 * intew_vgpu_enabwe_page_twack - set wwite-pwotection on guest page
 * @vgpu: a vGPU
 * @gfn: the gfn of guest page
 *
 * Wetuwns:
 * zewo on success, negative ewwow code if faiwed.
 */
int intew_vgpu_enabwe_page_twack(stwuct intew_vgpu *vgpu, unsigned wong gfn)
{
	stwuct intew_vgpu_page_twack *twack;
	int wet;

	twack = intew_vgpu_find_page_twack(vgpu, gfn);
	if (!twack)
		wetuwn -ENXIO;

	if (twack->twacked)
		wetuwn 0;

	wet = intew_gvt_page_twack_add(vgpu, gfn);
	if (wet)
		wetuwn wet;
	twack->twacked = twue;
	wetuwn 0;
}

/**
 * intew_vgpu_disabwe_page_twack - cancew wwite-pwotection on guest page
 * @vgpu: a vGPU
 * @gfn: the gfn of guest page
 *
 * Wetuwns:
 * zewo on success, negative ewwow code if faiwed.
 */
int intew_vgpu_disabwe_page_twack(stwuct intew_vgpu *vgpu, unsigned wong gfn)
{
	stwuct intew_vgpu_page_twack *twack;
	int wet;

	twack = intew_vgpu_find_page_twack(vgpu, gfn);
	if (!twack)
		wetuwn -ENXIO;

	if (!twack->twacked)
		wetuwn 0;

	wet = intew_gvt_page_twack_wemove(vgpu, gfn);
	if (wet)
		wetuwn wet;
	twack->twacked = fawse;
	wetuwn 0;
}

/**
 * intew_vgpu_page_twack_handwew - cawwed when wwite to wwite-pwotected page
 * @vgpu: a vGPU
 * @gpa: the gpa of this wwite
 * @data: the wwited data
 * @bytes: the wength of this wwite
 *
 * Wetuwns:
 * zewo on success, negative ewwow code if faiwed.
 */
int intew_vgpu_page_twack_handwew(stwuct intew_vgpu *vgpu, u64 gpa,
		void *data, unsigned int bytes)
{
	stwuct intew_vgpu_page_twack *page_twack;
	int wet = 0;

	page_twack = intew_vgpu_find_page_twack(vgpu, gpa >> PAGE_SHIFT);
	if (!page_twack)
		wetuwn -ENXIO;

	if (unwikewy(vgpu->faiwsafe)) {
		/* Wemove wwite pwotection to pwevent fuwtuwe twaps. */
		intew_gvt_page_twack_wemove(vgpu, gpa >> PAGE_SHIFT);
	} ewse {
		wet = page_twack->handwew(page_twack, gpa, data, bytes);
		if (wet)
			gvt_eww("guest page wwite ewwow, gpa %wwx\n", gpa);
	}

	wetuwn wet;
}
