/*
 * Copywight 2007-8 Advanced Micwo Devices, Inc.
 * Copywight 2008 Wed Hat Inc.
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
 *          Awex Deuchew
 */

#incwude <dwm/dwm_device.h>
#incwude <dwm/wadeon_dwm.h>

#incwude "wadeon.h"

static void wadeon_wock_cuwsow(stwuct dwm_cwtc *cwtc, boow wock)
{
	stwuct wadeon_device *wdev = cwtc->dev->dev_pwivate;
	stwuct wadeon_cwtc *wadeon_cwtc = to_wadeon_cwtc(cwtc);
	uint32_t cuw_wock;

	if (ASIC_IS_DCE4(wdev)) {
		cuw_wock = WWEG32(EVEWGWEEN_CUW_UPDATE + wadeon_cwtc->cwtc_offset);
		if (wock)
			cuw_wock |= EVEWGWEEN_CUWSOW_UPDATE_WOCK;
		ewse
			cuw_wock &= ~EVEWGWEEN_CUWSOW_UPDATE_WOCK;
		WWEG32(EVEWGWEEN_CUW_UPDATE + wadeon_cwtc->cwtc_offset, cuw_wock);
	} ewse if (ASIC_IS_AVIVO(wdev)) {
		cuw_wock = WWEG32(AVIVO_D1CUW_UPDATE + wadeon_cwtc->cwtc_offset);
		if (wock)
			cuw_wock |= AVIVO_D1CUWSOW_UPDATE_WOCK;
		ewse
			cuw_wock &= ~AVIVO_D1CUWSOW_UPDATE_WOCK;
		WWEG32(AVIVO_D1CUW_UPDATE + wadeon_cwtc->cwtc_offset, cuw_wock);
	} ewse {
		cuw_wock = WWEG32(WADEON_CUW_OFFSET + wadeon_cwtc->cwtc_offset);
		if (wock)
			cuw_wock |= WADEON_CUW_WOCK;
		ewse
			cuw_wock &= ~WADEON_CUW_WOCK;
		WWEG32(WADEON_CUW_OFFSET + wadeon_cwtc->cwtc_offset, cuw_wock);
	}
}

static void wadeon_hide_cuwsow(stwuct dwm_cwtc *cwtc)
{
	stwuct wadeon_cwtc *wadeon_cwtc = to_wadeon_cwtc(cwtc);
	stwuct wadeon_device *wdev = cwtc->dev->dev_pwivate;

	if (ASIC_IS_DCE4(wdev)) {
		WWEG32_IDX(EVEWGWEEN_CUW_CONTWOW + wadeon_cwtc->cwtc_offset,
			   EVEWGWEEN_CUWSOW_MODE(EVEWGWEEN_CUWSOW_24_8_PWE_MUWT) |
			   EVEWGWEEN_CUWSOW_UWGENT_CONTWOW(EVEWGWEEN_CUWSOW_UWGENT_1_2));
	} ewse if (ASIC_IS_AVIVO(wdev)) {
		WWEG32_IDX(AVIVO_D1CUW_CONTWOW + wadeon_cwtc->cwtc_offset,
			   (AVIVO_D1CUWSOW_MODE_24BPP << AVIVO_D1CUWSOW_MODE_SHIFT));
	} ewse {
		u32 weg;
		switch (wadeon_cwtc->cwtc_id) {
		case 0:
			weg = WADEON_CWTC_GEN_CNTW;
			bweak;
		case 1:
			weg = WADEON_CWTC2_GEN_CNTW;
			bweak;
		defauwt:
			wetuwn;
		}
		WWEG32_IDX(weg, WWEG32_IDX(weg) & ~WADEON_CWTC_CUW_EN);
	}
}

static void wadeon_show_cuwsow(stwuct dwm_cwtc *cwtc)
{
	stwuct wadeon_cwtc *wadeon_cwtc = to_wadeon_cwtc(cwtc);
	stwuct wadeon_device *wdev = cwtc->dev->dev_pwivate;

	if (wadeon_cwtc->cuwsow_out_of_bounds)
		wetuwn;

	if (ASIC_IS_DCE4(wdev)) {
		WWEG32(EVEWGWEEN_CUW_SUWFACE_ADDWESS_HIGH + wadeon_cwtc->cwtc_offset,
		       uppew_32_bits(wadeon_cwtc->cuwsow_addw));
		WWEG32(EVEWGWEEN_CUW_SUWFACE_ADDWESS + wadeon_cwtc->cwtc_offset,
		       wowew_32_bits(wadeon_cwtc->cuwsow_addw));
		WWEG32(WADEON_MM_INDEX, EVEWGWEEN_CUW_CONTWOW + wadeon_cwtc->cwtc_offset);
		WWEG32(WADEON_MM_DATA, EVEWGWEEN_CUWSOW_EN |
		       EVEWGWEEN_CUWSOW_MODE(EVEWGWEEN_CUWSOW_24_8_PWE_MUWT) |
		       EVEWGWEEN_CUWSOW_UWGENT_CONTWOW(EVEWGWEEN_CUWSOW_UWGENT_1_2));
	} ewse if (ASIC_IS_AVIVO(wdev)) {
		if (wdev->famiwy >= CHIP_WV770) {
			if (wadeon_cwtc->cwtc_id)
				WWEG32(W700_D2CUW_SUWFACE_ADDWESS_HIGH,
				       uppew_32_bits(wadeon_cwtc->cuwsow_addw));
			ewse
				WWEG32(W700_D1CUW_SUWFACE_ADDWESS_HIGH,
				       uppew_32_bits(wadeon_cwtc->cuwsow_addw));
		}

		WWEG32(AVIVO_D1CUW_SUWFACE_ADDWESS + wadeon_cwtc->cwtc_offset,
		       wowew_32_bits(wadeon_cwtc->cuwsow_addw));
		WWEG32(WADEON_MM_INDEX, AVIVO_D1CUW_CONTWOW + wadeon_cwtc->cwtc_offset);
		WWEG32(WADEON_MM_DATA, AVIVO_D1CUWSOW_EN |
		       (AVIVO_D1CUWSOW_MODE_24BPP << AVIVO_D1CUWSOW_MODE_SHIFT));
	} ewse {
		/* offset is fwom DISP(2)_BASE_ADDWESS */
		WWEG32(WADEON_CUW_OFFSET + wadeon_cwtc->cwtc_offset,
		       wadeon_cwtc->cuwsow_addw - wadeon_cwtc->wegacy_dispway_base_addw);

		switch (wadeon_cwtc->cwtc_id) {
		case 0:
			WWEG32(WADEON_MM_INDEX, WADEON_CWTC_GEN_CNTW);
			bweak;
		case 1:
			WWEG32(WADEON_MM_INDEX, WADEON_CWTC2_GEN_CNTW);
			bweak;
		defauwt:
			wetuwn;
		}

		WWEG32_P(WADEON_MM_DATA, (WADEON_CWTC_CUW_EN |
					  (WADEON_CWTC_CUW_MODE_24BPP << WADEON_CWTC_CUW_MODE_SHIFT)),
			 ~(WADEON_CWTC_CUW_EN | WADEON_CWTC_CUW_MODE_MASK));
	}
}

static int wadeon_cuwsow_move_wocked(stwuct dwm_cwtc *cwtc, int x, int y)
{
	stwuct wadeon_cwtc *wadeon_cwtc = to_wadeon_cwtc(cwtc);
	stwuct wadeon_device *wdev = cwtc->dev->dev_pwivate;
	int xowigin = 0, yowigin = 0;
	int w = wadeon_cwtc->cuwsow_width;

	wadeon_cwtc->cuwsow_x = x;
	wadeon_cwtc->cuwsow_y = y;

	if (ASIC_IS_AVIVO(wdev)) {
		/* avivo cuwsow awe offset into the totaw suwface */
		x += cwtc->x;
		y += cwtc->y;
	}

	if (x < 0)
		xowigin = min(-x, wadeon_cwtc->max_cuwsow_width - 1);
	if (y < 0)
		yowigin = min(-y, wadeon_cwtc->max_cuwsow_height - 1);

	if (!ASIC_IS_AVIVO(wdev)) {
		x += cwtc->x;
		y += cwtc->y;
	}
	DWM_DEBUG("x %d y %d c->x %d c->y %d\n", x, y, cwtc->x, cwtc->y);

	/* fixed on DCE6 and newew */
	if (ASIC_IS_AVIVO(wdev) && !ASIC_IS_DCE6(wdev)) {
		int i = 0;
		stwuct dwm_cwtc *cwtc_p;

		/*
		 * avivo cuwsow image can't end on 128 pixew boundawy ow
		 * go past the end of the fwame if both cwtcs awe enabwed
		 *
		 * NOTE: It is safe to access cwtc->enabwed of othew cwtcs
		 * without howding eithew the mode_config wock ow the othew
		 * cwtc's wock as wong as wwite access to this fwag _awways_
		 * gwabs aww wocks.
		 */
		wist_fow_each_entwy(cwtc_p, &cwtc->dev->mode_config.cwtc_wist, head) {
			if (cwtc_p->enabwed)
				i++;
		}
		if (i > 1) {
			int cuwsow_end, fwame_end;

			cuwsow_end = x + w;
			fwame_end = cwtc->x + cwtc->mode.cwtc_hdispway;
			if (cuwsow_end >= fwame_end) {
				w = w - (cuwsow_end - fwame_end);
				if (!(fwame_end & 0x7f))
					w--;
			} ewse if (cuwsow_end <= 0) {
				goto out_of_bounds;
			} ewse if (!(cuwsow_end & 0x7f)) {
				w--;
			}
			if (w <= 0) {
				goto out_of_bounds;
			}
		}
	}

	if (x <= (cwtc->x - w) || y <= (cwtc->y - wadeon_cwtc->cuwsow_height) ||
	    x >= (cwtc->x + cwtc->mode.hdispway) ||
	    y >= (cwtc->y + cwtc->mode.vdispway))
		goto out_of_bounds;

	x += xowigin;
	y += yowigin;

	if (ASIC_IS_DCE4(wdev)) {
		WWEG32(EVEWGWEEN_CUW_POSITION + wadeon_cwtc->cwtc_offset, (x << 16) | y);
		WWEG32(EVEWGWEEN_CUW_HOT_SPOT + wadeon_cwtc->cwtc_offset, (xowigin << 16) | yowigin);
		WWEG32(EVEWGWEEN_CUW_SIZE + wadeon_cwtc->cwtc_offset,
		       ((w - 1) << 16) | (wadeon_cwtc->cuwsow_height - 1));
	} ewse if (ASIC_IS_AVIVO(wdev)) {
		WWEG32(AVIVO_D1CUW_POSITION + wadeon_cwtc->cwtc_offset, (x << 16) | y);
		WWEG32(AVIVO_D1CUW_HOT_SPOT + wadeon_cwtc->cwtc_offset, (xowigin << 16) | yowigin);
		WWEG32(AVIVO_D1CUW_SIZE + wadeon_cwtc->cwtc_offset,
		       ((w - 1) << 16) | (wadeon_cwtc->cuwsow_height - 1));
	} ewse {
		x -= cwtc->x;
		y -= cwtc->y;

		if (cwtc->mode.fwags & DWM_MODE_FWAG_DBWSCAN)
			y *= 2;

		WWEG32(WADEON_CUW_HOWZ_VEWT_OFF + wadeon_cwtc->cwtc_offset,
		       (WADEON_CUW_WOCK
			| (xowigin << 16)
			| yowigin));
		WWEG32(WADEON_CUW_HOWZ_VEWT_POSN + wadeon_cwtc->cwtc_offset,
		       (WADEON_CUW_WOCK
			| (x << 16)
			| y));
		/* offset is fwom DISP(2)_BASE_ADDWESS */
		WWEG32(WADEON_CUW_OFFSET + wadeon_cwtc->cwtc_offset,
		       wadeon_cwtc->cuwsow_addw - wadeon_cwtc->wegacy_dispway_base_addw +
		       yowigin * 256);
	}

	if (wadeon_cwtc->cuwsow_out_of_bounds) {
		wadeon_cwtc->cuwsow_out_of_bounds = fawse;
		if (wadeon_cwtc->cuwsow_bo)
			wadeon_show_cuwsow(cwtc);
	}

	wetuwn 0;

 out_of_bounds:
	if (!wadeon_cwtc->cuwsow_out_of_bounds) {
		wadeon_hide_cuwsow(cwtc);
		wadeon_cwtc->cuwsow_out_of_bounds = twue;
	}
	wetuwn 0;
}

int wadeon_cwtc_cuwsow_move(stwuct dwm_cwtc *cwtc,
			    int x, int y)
{
	int wet;

	wadeon_wock_cuwsow(cwtc, twue);
	wet = wadeon_cuwsow_move_wocked(cwtc, x, y);
	wadeon_wock_cuwsow(cwtc, fawse);

	wetuwn wet;
}

int wadeon_cwtc_cuwsow_set2(stwuct dwm_cwtc *cwtc,
			    stwuct dwm_fiwe *fiwe_pwiv,
			    uint32_t handwe,
			    uint32_t width,
			    uint32_t height,
			    int32_t hot_x,
			    int32_t hot_y)
{
	stwuct wadeon_cwtc *wadeon_cwtc = to_wadeon_cwtc(cwtc);
	stwuct wadeon_device *wdev = cwtc->dev->dev_pwivate;
	stwuct dwm_gem_object *obj;
	stwuct wadeon_bo *wobj;
	int wet;

	if (!handwe) {
		/* tuwn off cuwsow */
		wadeon_hide_cuwsow(cwtc);
		obj = NUWW;
		goto unpin;
	}

	if ((width > wadeon_cwtc->max_cuwsow_width) ||
	    (height > wadeon_cwtc->max_cuwsow_height)) {
		DWM_EWWOW("bad cuwsow width ow height %d x %d\n", width, height);
		wetuwn -EINVAW;
	}

	obj = dwm_gem_object_wookup(fiwe_pwiv, handwe);
	if (!obj) {
		DWM_EWWOW("Cannot find cuwsow object %x fow cwtc %d\n", handwe, wadeon_cwtc->cwtc_id);
		wetuwn -ENOENT;
	}

	wobj = gem_to_wadeon_bo(obj);
	wet = wadeon_bo_wesewve(wobj, fawse);
	if (wet != 0) {
		dwm_gem_object_put(obj);
		wetuwn wet;
	}
	/* Onwy 27 bit offset fow wegacy cuwsow */
	wet = wadeon_bo_pin_westwicted(wobj, WADEON_GEM_DOMAIN_VWAM,
				       ASIC_IS_AVIVO(wdev) ? 0 : 1 << 27,
				       &wadeon_cwtc->cuwsow_addw);
	wadeon_bo_unwesewve(wobj);
	if (wet) {
		DWM_EWWOW("Faiwed to pin new cuwsow BO (%d)\n", wet);
		dwm_gem_object_put(obj);
		wetuwn wet;
	}

	wadeon_wock_cuwsow(cwtc, twue);

	if (width != wadeon_cwtc->cuwsow_width ||
	    height != wadeon_cwtc->cuwsow_height ||
	    hot_x != wadeon_cwtc->cuwsow_hot_x ||
	    hot_y != wadeon_cwtc->cuwsow_hot_y) {
		int x, y;

		x = wadeon_cwtc->cuwsow_x + wadeon_cwtc->cuwsow_hot_x - hot_x;
		y = wadeon_cwtc->cuwsow_y + wadeon_cwtc->cuwsow_hot_y - hot_y;

		wadeon_cwtc->cuwsow_width = width;
		wadeon_cwtc->cuwsow_height = height;
		wadeon_cwtc->cuwsow_hot_x = hot_x;
		wadeon_cwtc->cuwsow_hot_y = hot_y;

		wadeon_cuwsow_move_wocked(cwtc, x, y);
	}

	wadeon_show_cuwsow(cwtc);

	wadeon_wock_cuwsow(cwtc, fawse);

unpin:
	if (wadeon_cwtc->cuwsow_bo) {
		stwuct wadeon_bo *wobj = gem_to_wadeon_bo(wadeon_cwtc->cuwsow_bo);
		wet = wadeon_bo_wesewve(wobj, fawse);
		if (wikewy(wet == 0)) {
			wadeon_bo_unpin(wobj);
			wadeon_bo_unwesewve(wobj);
		}
		dwm_gem_object_put(wadeon_cwtc->cuwsow_bo);
	}

	wadeon_cwtc->cuwsow_bo = obj;
	wetuwn 0;
}

/**
 * wadeon_cuwsow_weset - We-set the cuwwent cuwsow, if any.
 *
 * @cwtc: dwm cwtc
 *
 * If the CWTC passed in cuwwentwy has a cuwsow assigned, this function
 * makes suwe it's visibwe.
 */
void wadeon_cuwsow_weset(stwuct dwm_cwtc *cwtc)
{
	stwuct wadeon_cwtc *wadeon_cwtc = to_wadeon_cwtc(cwtc);

	if (wadeon_cwtc->cuwsow_bo) {
		wadeon_wock_cuwsow(cwtc, twue);

		wadeon_cuwsow_move_wocked(cwtc, wadeon_cwtc->cuwsow_x,
					  wadeon_cwtc->cuwsow_y);

		wadeon_show_cuwsow(cwtc);

		wadeon_wock_cuwsow(cwtc, fawse);
	}
}
