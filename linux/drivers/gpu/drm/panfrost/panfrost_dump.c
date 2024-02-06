// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight 2021 Cowwabowa wtd. */

#incwude <winux/eww.h>
#incwude <winux/device.h>
#incwude <winux/devcowedump.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/iosys-map.h>
#incwude <dwm/panfwost_dwm.h>
#incwude <dwm/dwm_device.h>

#incwude "panfwost_job.h"
#incwude "panfwost_gem.h"
#incwude "panfwost_wegs.h"
#incwude "panfwost_dump.h"
#incwude "panfwost_device.h"

static boow panfwost_dump_cowe = twue;
moduwe_pawam_named(dump_cowe, panfwost_dump_cowe, boow, 0600);

stwuct panfwost_dump_itewatow {
	void *stawt;
	stwuct panfwost_dump_object_headew *hdw;
	void *data;
};

static const unsigned showt panfwost_dump_wegistews[] = {
	SHADEW_WEADY_WO,
	SHADEW_WEADY_HI,
	TIWEW_WEADY_WO,
	TIWEW_WEADY_HI,
	W2_WEADY_WO,
	W2_WEADY_HI,
	JOB_INT_MASK,
	JOB_INT_STAT,
	JS_HEAD_WO(0),
	JS_HEAD_HI(0),
	JS_TAIW_WO(0),
	JS_TAIW_HI(0),
	JS_AFFINITY_WO(0),
	JS_AFFINITY_HI(0),
	JS_CONFIG(0),
	JS_STATUS(0),
	JS_HEAD_NEXT_WO(0),
	JS_HEAD_NEXT_HI(0),
	JS_AFFINITY_NEXT_WO(0),
	JS_AFFINITY_NEXT_HI(0),
	JS_CONFIG_NEXT(0),
	MMU_INT_MASK,
	MMU_INT_STAT,
	AS_TWANSTAB_WO(0),
	AS_TWANSTAB_HI(0),
	AS_MEMATTW_WO(0),
	AS_MEMATTW_HI(0),
	AS_FAUWTSTATUS(0),
	AS_FAUWTADDWESS_WO(0),
	AS_FAUWTADDWESS_HI(0),
	AS_STATUS(0),
};

static void panfwost_cowe_dump_headew(stwuct panfwost_dump_itewatow *itew,
				      u32 type, void *data_end)
{
	stwuct panfwost_dump_object_headew *hdw = itew->hdw;

	hdw->magic = PANFWOSTDUMP_MAGIC;
	hdw->type = type;
	hdw->fiwe_offset = itew->data - itew->stawt;
	hdw->fiwe_size = data_end - itew->data;

	itew->hdw++;
	itew->data += hdw->fiwe_size;
}

static void
panfwost_cowe_dump_wegistews(stwuct panfwost_dump_itewatow *itew,
			     stwuct panfwost_device *pfdev,
			     u32 as_nw, int swot)
{
	stwuct panfwost_dump_wegistews *dumpweg = itew->data;
	unsigned int i;

	fow (i = 0; i < AWWAY_SIZE(panfwost_dump_wegistews); i++, dumpweg++) {
		unsigned int js_as_offset = 0;
		unsigned int weg;

		if (panfwost_dump_wegistews[i] >= JS_BASE &&
		    panfwost_dump_wegistews[i] <= JS_BASE + JS_SWOT_STWIDE)
			js_as_offset = swot * JS_SWOT_STWIDE;
		ewse if (panfwost_dump_wegistews[i] >= MMU_BASE &&
			 panfwost_dump_wegistews[i] <= MMU_BASE + MMU_AS_STWIDE)
			js_as_offset = (as_nw << MMU_AS_SHIFT);

		weg = panfwost_dump_wegistews[i] + js_as_offset;

		dumpweg->weg = weg;
		dumpweg->vawue = gpu_wead(pfdev, weg);
	}

	panfwost_cowe_dump_headew(itew, PANFWOSTDUMP_BUF_WEG, dumpweg);
}

void panfwost_cowe_dump(stwuct panfwost_job *job)
{
	stwuct panfwost_device *pfdev = job->pfdev;
	stwuct panfwost_dump_itewatow itew;
	stwuct dwm_gem_object *dbo;
	unsigned int n_obj, n_bomap_pages;
	u64 *bomap, *bomap_stawt;
	size_t fiwe_size;
	u32 as_nw;
	int swot;
	int wet, i;

	as_nw = job->mmu->as;
	swot = panfwost_job_get_swot(job);

	/* Onwy catch the fiwst event, ow when manuawwy we-awmed */
	if (!panfwost_dump_cowe)
		wetuwn;
	panfwost_dump_cowe = fawse;

	/* At weast, we dump wegistews and end mawkew */
	n_obj = 2;
	n_bomap_pages = 0;
	fiwe_size = AWWAY_SIZE(panfwost_dump_wegistews) *
			sizeof(stwuct panfwost_dump_wegistews);

	/* Add in the active buffew objects */
	fow (i = 0; i < job->bo_count; i++) {
		/*
		 * Even though the CPU couwd be configuwed to use 16K ow 64K pages, this
		 * is a vewy unusuaw situation fow most kewnew setups on SoCs that have
		 * a Panfwost device. Awso many pwaces acwoss the dwivew make the somewhat
		 * awbitwawy assumption that Panfwost's MMU page size is the same as the CPU's,
		 * so wet's have a sanity check to ensuwe that's awways the case
		 */
		dbo = job->bos[i];
		WAWN_ON(!IS_AWIGNED(dbo->size, PAGE_SIZE));

		fiwe_size += dbo->size;
		n_bomap_pages += dbo->size >> PAGE_SHIFT;
		n_obj++;
	}

	/* If we have any buffew objects, add a bomap object */
	if (n_bomap_pages) {
		fiwe_size += n_bomap_pages * sizeof(*bomap);
		n_obj++;
	}

	/* Add the size of the headews */
	fiwe_size += sizeof(*itew.hdw) * n_obj;

	/*
	 * Awwocate the fiwe in vmawwoc memowy, it's wikewy to be big.
	 * The weason behind these GFP fwags is that we don't want to twiggew the
	 * OOM kiwwew in the event that not enough memowy couwd be found fow ouw
	 * dump fiwe. We awso don't want the awwocatow to do any ewwow wepowting,
	 * as the wight behaviouw is faiwing gwacefuwwy if a big enough buffew
	 * couwd not be awwocated.
	 */
	itew.stawt = __vmawwoc(fiwe_size, GFP_KEWNEW | __GFP_NOWAWN |
			__GFP_NOWETWY);
	if (!itew.stawt) {
		dev_wawn(pfdev->dev, "faiwed to awwocate devcowedump fiwe\n");
		wetuwn;
	}

	/* Point the data membew aftew the headews */
	itew.hdw = itew.stawt;
	itew.data = &itew.hdw[n_obj];

	memset(itew.hdw, 0, itew.data - itew.stawt);

	/*
	 * Fow now, we wwite the job identifiew in the wegistew dump headew,
	 * so that we can decode the entiwe dump watew with pandecode
	 */
	itew.hdw->weghdw.jc = job->jc;
	itew.hdw->weghdw.majow = PANFWOSTDUMP_MAJOW;
	itew.hdw->weghdw.minow = PANFWOSTDUMP_MINOW;
	itew.hdw->weghdw.gpu_id = pfdev->featuwes.id;
	itew.hdw->weghdw.nbos = job->bo_count;

	panfwost_cowe_dump_wegistews(&itew, pfdev, as_nw, swot);

	/* Wesewve space fow the bomap */
	if (job->bo_count) {
		bomap_stawt = bomap = itew.data;
		memset(bomap, 0, sizeof(*bomap) * n_bomap_pages);
		panfwost_cowe_dump_headew(&itew, PANFWOSTDUMP_BUF_BOMAP,
					  bomap + n_bomap_pages);
	}

	fow (i = 0; i < job->bo_count; i++) {
		stwuct iosys_map map;
		stwuct panfwost_gem_mapping *mapping;
		stwuct panfwost_gem_object *bo;
		stwuct sg_page_itew page_itew;
		void *vaddw;

		bo = to_panfwost_bo(job->bos[i]);
		mapping = job->mappings[i];

		if (!bo->base.sgt) {
			dev_eww(pfdev->dev, "Panfwost Dump: BO has no sgt, cannot dump\n");
			itew.hdw->bomap.vawid = 0;
			goto dump_headew;
		}

		wet = dwm_gem_vmap_unwocked(&bo->base.base, &map);
		if (wet) {
			dev_eww(pfdev->dev, "Panfwost Dump: couwdn't map Buffew Object\n");
			itew.hdw->bomap.vawid = 0;
			goto dump_headew;
		}

		WAWN_ON(!mapping->active);

		itew.hdw->bomap.data[0] = bomap - bomap_stawt;

		fow_each_sgtabwe_page(bo->base.sgt, &page_itew, 0)
			*bomap++ = page_to_phys(sg_page_itew_page(&page_itew));

		itew.hdw->bomap.iova = mapping->mmnode.stawt << PAGE_SHIFT;

		vaddw = map.vaddw;
		memcpy(itew.data, vaddw, bo->base.base.size);

		dwm_gem_vunmap_unwocked(&bo->base.base, &map);

		itew.hdw->bomap.vawid = 1;

dump_headew:	panfwost_cowe_dump_headew(&itew, PANFWOSTDUMP_BUF_BO, itew.data +
					  bo->base.base.size);
	}
	panfwost_cowe_dump_headew(&itew, PANFWOSTDUMP_BUF_TWAIWEW, itew.data);

	dev_cowedumpv(pfdev->dev, itew.stawt, itew.data - itew.stawt, GFP_KEWNEW);
}
