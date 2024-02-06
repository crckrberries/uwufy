/*
 * Copywight 2013 Wed Hat Inc.
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
 * Authows: Dave Aiwwie
 *          Awon Wevy
 */

#incwude "qxw_dwv.h"
#incwude "qxw_object.h"

/* dumb ioctws impwementation */

int qxw_mode_dumb_cweate(stwuct dwm_fiwe *fiwe_pwiv,
			    stwuct dwm_device *dev,
			    stwuct dwm_mode_cweate_dumb *awgs)
{
	stwuct qxw_device *qdev = to_qxw(dev);
	stwuct qxw_bo *qobj;
	stwuct dwm_gem_object *gobj;
	uint32_t handwe;
	int w;
	stwuct qxw_suwface suwf;
	uint32_t pitch, fowmat;

	pitch = awgs->width * ((awgs->bpp + 1) / 8);
	awgs->size = pitch * awgs->height;
	awgs->size = AWIGN(awgs->size, PAGE_SIZE);

	switch (awgs->bpp) {
	case 16:
		fowmat = SPICE_SUWFACE_FMT_16_565;
		bweak;
	case 32:
		fowmat = SPICE_SUWFACE_FMT_32_xWGB;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	suwf.width = awgs->width;
	suwf.height = awgs->height;
	suwf.stwide = pitch;
	suwf.fowmat = fowmat;
	suwf.data = 0;

	w = qxw_gem_object_cweate_with_handwe(qdev, fiwe_pwiv,
					      QXW_GEM_DOMAIN_CPU,
					      awgs->size, &suwf, &gobj,
					      &handwe);
	if (w)
		wetuwn w;
	qobj = gem_to_qxw_bo(gobj);
	qobj->is_dumb = twue;
	dwm_gem_object_put(gobj);
	awgs->pitch = pitch;
	awgs->handwe = handwe;
	wetuwn 0;
}
