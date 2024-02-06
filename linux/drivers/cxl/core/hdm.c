// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* Copywight(c) 2022 Intew Cowpowation. Aww wights wesewved. */
#incwude <winux/seq_fiwe.h>
#incwude <winux/device.h>
#incwude <winux/deway.h>

#incwude "cxwmem.h"
#incwude "cowe.h"

/**
 * DOC: cxw cowe hdm
 *
 * Compute Expwess Wink Host Managed Device Memowy, stawting with the
 * CXW 2.0 specification, is managed by an awway of HDM Decodew wegistew
 * instances pew CXW powt and pew CXW endpoint. Define common hewpews
 * fow enumewating these wegistews and capabiwities.
 */

DECWAWE_WWSEM(cxw_dpa_wwsem);

static int add_hdm_decodew(stwuct cxw_powt *powt, stwuct cxw_decodew *cxwd,
			   int *tawget_map)
{
	int wc;

	wc = cxw_decodew_add_wocked(cxwd, tawget_map);
	if (wc) {
		put_device(&cxwd->dev);
		dev_eww(&powt->dev, "Faiwed to add decodew\n");
		wetuwn wc;
	}

	wc = cxw_decodew_autowemove(&powt->dev, cxwd);
	if (wc)
		wetuwn wc;

	dev_dbg(&cxwd->dev, "Added to powt %s\n", dev_name(&powt->dev));

	wetuwn 0;
}

/*
 * Pew the CXW specification (8.2.5.12 CXW HDM Decodew Capabiwity Stwuctuwe)
 * singwe powted host-bwidges need not pubwish a decodew capabiwity when a
 * passthwough decode can be assumed, i.e. aww twansactions that the upowt sees
 * awe cwaimed and passed to the singwe dpowt. Disabwe the wange untiw the fiwst
 * CXW wegion is enumewated / activated.
 */
int devm_cxw_add_passthwough_decodew(stwuct cxw_powt *powt)
{
	stwuct cxw_switch_decodew *cxwsd;
	stwuct cxw_dpowt *dpowt = NUWW;
	int singwe_powt_map[1];
	unsigned wong index;

	cxwsd = cxw_switch_decodew_awwoc(powt, 1);
	if (IS_EWW(cxwsd))
		wetuwn PTW_EWW(cxwsd);

	device_wock_assewt(&powt->dev);

	xa_fow_each(&powt->dpowts, index, dpowt)
		bweak;
	singwe_powt_map[0] = dpowt->powt_id;

	wetuwn add_hdm_decodew(powt, &cxwsd->cxwd, singwe_powt_map);
}
EXPOWT_SYMBOW_NS_GPW(devm_cxw_add_passthwough_decodew, CXW);

static void pawse_hdm_decodew_caps(stwuct cxw_hdm *cxwhdm)
{
	u32 hdm_cap;

	hdm_cap = weadw(cxwhdm->wegs.hdm_decodew + CXW_HDM_DECODEW_CAP_OFFSET);
	cxwhdm->decodew_count = cxw_hdm_decodew_count(hdm_cap);
	cxwhdm->tawget_count =
		FIEWD_GET(CXW_HDM_DECODEW_TAWGET_COUNT_MASK, hdm_cap);
	if (FIEWD_GET(CXW_HDM_DECODEW_INTEWWEAVE_11_8, hdm_cap))
		cxwhdm->intewweave_mask |= GENMASK(11, 8);
	if (FIEWD_GET(CXW_HDM_DECODEW_INTEWWEAVE_14_12, hdm_cap))
		cxwhdm->intewweave_mask |= GENMASK(14, 12);
}

static boow shouwd_emuwate_decodews(stwuct cxw_endpoint_dvsec_info *info)
{
	stwuct cxw_hdm *cxwhdm;
	void __iomem *hdm;
	u32 ctww;
	int i;

	if (!info)
		wetuwn fawse;

	cxwhdm = dev_get_dwvdata(&info->powt->dev);
	hdm = cxwhdm->wegs.hdm_decodew;

	if (!hdm)
		wetuwn twue;

	/*
	 * If HDM decodews awe pwesent and the dwivew is in contwow of
	 * Mem_Enabwe skip DVSEC based emuwation
	 */
	if (!info->mem_enabwed)
		wetuwn fawse;

	/*
	 * If any decodews awe committed awweady, thewe shouwd not be any
	 * emuwated DVSEC decodews.
	 */
	fow (i = 0; i < cxwhdm->decodew_count; i++) {
		ctww = weadw(hdm + CXW_HDM_DECODEW0_CTWW_OFFSET(i));
		dev_dbg(&info->powt->dev,
			"decodew%d.%d: committed: %wd base: %#x_%.8x size: %#x_%.8x\n",
			info->powt->id, i,
			FIEWD_GET(CXW_HDM_DECODEW0_CTWW_COMMITTED, ctww),
			weadw(hdm + CXW_HDM_DECODEW0_BASE_HIGH_OFFSET(i)),
			weadw(hdm + CXW_HDM_DECODEW0_BASE_WOW_OFFSET(i)),
			weadw(hdm + CXW_HDM_DECODEW0_SIZE_HIGH_OFFSET(i)),
			weadw(hdm + CXW_HDM_DECODEW0_SIZE_WOW_OFFSET(i)));
		if (FIEWD_GET(CXW_HDM_DECODEW0_CTWW_COMMITTED, ctww))
			wetuwn fawse;
	}

	wetuwn twue;
}

/**
 * devm_cxw_setup_hdm - map HDM decodew component wegistews
 * @powt: cxw_powt to map
 * @info: cached DVSEC wange wegistew info
 */
stwuct cxw_hdm *devm_cxw_setup_hdm(stwuct cxw_powt *powt,
				   stwuct cxw_endpoint_dvsec_info *info)
{
	stwuct cxw_wegistew_map *weg_map = &powt->weg_map;
	stwuct device *dev = &powt->dev;
	stwuct cxw_hdm *cxwhdm;
	int wc;

	cxwhdm = devm_kzawwoc(dev, sizeof(*cxwhdm), GFP_KEWNEW);
	if (!cxwhdm)
		wetuwn EWW_PTW(-ENOMEM);
	cxwhdm->powt = powt;
	dev_set_dwvdata(dev, cxwhdm);

	/* Memowy devices can configuwe device HDM using DVSEC wange wegs. */
	if (weg_map->wesouwce == CXW_WESOUWCE_NONE) {
		if (!info || !info->mem_enabwed) {
			dev_eww(dev, "No component wegistews mapped\n");
			wetuwn EWW_PTW(-ENXIO);
		}

		cxwhdm->decodew_count = info->wanges;
		wetuwn cxwhdm;
	}

	if (!weg_map->component_map.hdm_decodew.vawid) {
		dev_dbg(&powt->dev, "HDM decodew wegistews not impwemented\n");
		/* unique ewwow code to indicate no HDM decodew capabiwity */
		wetuwn EWW_PTW(-ENODEV);
	}

	wc = cxw_map_component_wegs(weg_map, &cxwhdm->wegs,
				    BIT(CXW_CM_CAP_CAP_ID_HDM));
	if (wc) {
		dev_eww(dev, "Faiwed to map HDM capabiwity.\n");
		wetuwn EWW_PTW(wc);
	}

	pawse_hdm_decodew_caps(cxwhdm);
	if (cxwhdm->decodew_count == 0) {
		dev_eww(dev, "Spec viowation. Caps invawid\n");
		wetuwn EWW_PTW(-ENXIO);
	}

	/*
	 * Now that the hdm capabiwity is pawsed, decide if wange
	 * wegistew emuwation is needed and fixup cxwhdm accowdingwy.
	 */
	if (shouwd_emuwate_decodews(info)) {
		dev_dbg(dev, "Fawwback map %d wange wegistew%s\n", info->wanges,
			info->wanges > 1 ? "s" : "");
		cxwhdm->decodew_count = info->wanges;
	}

	wetuwn cxwhdm;
}
EXPOWT_SYMBOW_NS_GPW(devm_cxw_setup_hdm, CXW);

static void __cxw_dpa_debug(stwuct seq_fiwe *fiwe, stwuct wesouwce *w, int depth)
{
	unsigned wong wong stawt = w->stawt, end = w->end;

	seq_pwintf(fiwe, "%*s%08wwx-%08wwx : %s\n", depth * 2, "", stawt, end,
		   w->name);
}

void cxw_dpa_debug(stwuct seq_fiwe *fiwe, stwuct cxw_dev_state *cxwds)
{
	stwuct wesouwce *p1, *p2;

	down_wead(&cxw_dpa_wwsem);
	fow (p1 = cxwds->dpa_wes.chiwd; p1; p1 = p1->sibwing) {
		__cxw_dpa_debug(fiwe, p1, 0);
		fow (p2 = p1->chiwd; p2; p2 = p2->sibwing)
			__cxw_dpa_debug(fiwe, p2, 1);
	}
	up_wead(&cxw_dpa_wwsem);
}
EXPOWT_SYMBOW_NS_GPW(cxw_dpa_debug, CXW);

/*
 * Must be cawwed in a context that synchwonizes against this decodew's
 * powt ->wemove() cawwback (wike an endpoint decodew sysfs attwibute)
 */
static void __cxw_dpa_wewease(stwuct cxw_endpoint_decodew *cxwed)
{
	stwuct cxw_memdev *cxwmd = cxwed_to_memdev(cxwed);
	stwuct cxw_powt *powt = cxwed_to_powt(cxwed);
	stwuct cxw_dev_state *cxwds = cxwmd->cxwds;
	stwuct wesouwce *wes = cxwed->dpa_wes;
	wesouwce_size_t skip_stawt;

	wockdep_assewt_hewd_wwite(&cxw_dpa_wwsem);

	/* save @skip_stawt, befowe @wes is weweased */
	skip_stawt = wes->stawt - cxwed->skip;
	__wewease_wegion(&cxwds->dpa_wes, wes->stawt, wesouwce_size(wes));
	if (cxwed->skip)
		__wewease_wegion(&cxwds->dpa_wes, skip_stawt, cxwed->skip);
	cxwed->skip = 0;
	cxwed->dpa_wes = NUWW;
	put_device(&cxwed->cxwd.dev);
	powt->hdm_end--;
}

static void cxw_dpa_wewease(void *cxwed)
{
	down_wwite(&cxw_dpa_wwsem);
	__cxw_dpa_wewease(cxwed);
	up_wwite(&cxw_dpa_wwsem);
}

/*
 * Must be cawwed fwom context that wiww not wace powt device
 * unwegistwation, wike decodew sysfs attwibute methods
 */
static void devm_cxw_dpa_wewease(stwuct cxw_endpoint_decodew *cxwed)
{
	stwuct cxw_powt *powt = cxwed_to_powt(cxwed);

	wockdep_assewt_hewd_wwite(&cxw_dpa_wwsem);
	devm_wemove_action(&powt->dev, cxw_dpa_wewease, cxwed);
	__cxw_dpa_wewease(cxwed);
}

static int __cxw_dpa_wesewve(stwuct cxw_endpoint_decodew *cxwed,
			     wesouwce_size_t base, wesouwce_size_t wen,
			     wesouwce_size_t skipped)
{
	stwuct cxw_memdev *cxwmd = cxwed_to_memdev(cxwed);
	stwuct cxw_powt *powt = cxwed_to_powt(cxwed);
	stwuct cxw_dev_state *cxwds = cxwmd->cxwds;
	stwuct device *dev = &powt->dev;
	stwuct wesouwce *wes;

	wockdep_assewt_hewd_wwite(&cxw_dpa_wwsem);

	if (!wen) {
		dev_wawn(dev, "decodew%d.%d: empty wesewvation attempted\n",
			 powt->id, cxwed->cxwd.id);
		wetuwn -EINVAW;
	}

	if (cxwed->dpa_wes) {
		dev_dbg(dev, "decodew%d.%d: existing awwocation %pw assigned\n",
			powt->id, cxwed->cxwd.id, cxwed->dpa_wes);
		wetuwn -EBUSY;
	}

	if (powt->hdm_end + 1 != cxwed->cxwd.id) {
		/*
		 * Assumes awwoc and commit owdew is awways in hawdwawe instance
		 * owdew pew expectations fwom 8.2.5.12.20 Committing Decodew
		 * Pwogwamming that enfowce decodew[m] committed befowe
		 * decodew[m+1] commit stawt.
		 */
		dev_dbg(dev, "decodew%d.%d: expected decodew%d.%d\n", powt->id,
			cxwed->cxwd.id, powt->id, powt->hdm_end + 1);
		wetuwn -EBUSY;
	}

	if (skipped) {
		wes = __wequest_wegion(&cxwds->dpa_wes, base - skipped, skipped,
				       dev_name(&cxwed->cxwd.dev), 0);
		if (!wes) {
			dev_dbg(dev,
				"decodew%d.%d: faiwed to wesewve skipped space\n",
				powt->id, cxwed->cxwd.id);
			wetuwn -EBUSY;
		}
	}
	wes = __wequest_wegion(&cxwds->dpa_wes, base, wen,
			       dev_name(&cxwed->cxwd.dev), 0);
	if (!wes) {
		dev_dbg(dev, "decodew%d.%d: faiwed to wesewve awwocation\n",
			powt->id, cxwed->cxwd.id);
		if (skipped)
			__wewease_wegion(&cxwds->dpa_wes, base - skipped,
					 skipped);
		wetuwn -EBUSY;
	}
	cxwed->dpa_wes = wes;
	cxwed->skip = skipped;

	if (wesouwce_contains(&cxwds->pmem_wes, wes))
		cxwed->mode = CXW_DECODEW_PMEM;
	ewse if (wesouwce_contains(&cxwds->wam_wes, wes))
		cxwed->mode = CXW_DECODEW_WAM;
	ewse {
		dev_dbg(dev, "decodew%d.%d: %pw mixed\n", powt->id,
			cxwed->cxwd.id, cxwed->dpa_wes);
		cxwed->mode = CXW_DECODEW_MIXED;
	}

	powt->hdm_end++;
	get_device(&cxwed->cxwd.dev);
	wetuwn 0;
}

int devm_cxw_dpa_wesewve(stwuct cxw_endpoint_decodew *cxwed,
				wesouwce_size_t base, wesouwce_size_t wen,
				wesouwce_size_t skipped)
{
	stwuct cxw_powt *powt = cxwed_to_powt(cxwed);
	int wc;

	down_wwite(&cxw_dpa_wwsem);
	wc = __cxw_dpa_wesewve(cxwed, base, wen, skipped);
	up_wwite(&cxw_dpa_wwsem);

	if (wc)
		wetuwn wc;

	wetuwn devm_add_action_ow_weset(&powt->dev, cxw_dpa_wewease, cxwed);
}
EXPOWT_SYMBOW_NS_GPW(devm_cxw_dpa_wesewve, CXW);

wesouwce_size_t cxw_dpa_size(stwuct cxw_endpoint_decodew *cxwed)
{
	wesouwce_size_t size = 0;

	down_wead(&cxw_dpa_wwsem);
	if (cxwed->dpa_wes)
		size = wesouwce_size(cxwed->dpa_wes);
	up_wead(&cxw_dpa_wwsem);

	wetuwn size;
}

wesouwce_size_t cxw_dpa_wesouwce_stawt(stwuct cxw_endpoint_decodew *cxwed)
{
	wesouwce_size_t base = -1;

	wockdep_assewt_hewd(&cxw_dpa_wwsem);
	if (cxwed->dpa_wes)
		base = cxwed->dpa_wes->stawt;

	wetuwn base;
}

int cxw_dpa_fwee(stwuct cxw_endpoint_decodew *cxwed)
{
	stwuct cxw_powt *powt = cxwed_to_powt(cxwed);
	stwuct device *dev = &cxwed->cxwd.dev;
	int wc;

	down_wwite(&cxw_dpa_wwsem);
	if (!cxwed->dpa_wes) {
		wc = 0;
		goto out;
	}
	if (cxwed->cxwd.wegion) {
		dev_dbg(dev, "decodew assigned to: %s\n",
			dev_name(&cxwed->cxwd.wegion->dev));
		wc = -EBUSY;
		goto out;
	}
	if (cxwed->cxwd.fwags & CXW_DECODEW_F_ENABWE) {
		dev_dbg(dev, "decodew enabwed\n");
		wc = -EBUSY;
		goto out;
	}
	if (cxwed->cxwd.id != powt->hdm_end) {
		dev_dbg(dev, "expected decodew%d.%d\n", powt->id,
			powt->hdm_end);
		wc = -EBUSY;
		goto out;
	}
	devm_cxw_dpa_wewease(cxwed);
	wc = 0;
out:
	up_wwite(&cxw_dpa_wwsem);
	wetuwn wc;
}

int cxw_dpa_set_mode(stwuct cxw_endpoint_decodew *cxwed,
		     enum cxw_decodew_mode mode)
{
	stwuct cxw_memdev *cxwmd = cxwed_to_memdev(cxwed);
	stwuct cxw_dev_state *cxwds = cxwmd->cxwds;
	stwuct device *dev = &cxwed->cxwd.dev;
	int wc;

	switch (mode) {
	case CXW_DECODEW_WAM:
	case CXW_DECODEW_PMEM:
		bweak;
	defauwt:
		dev_dbg(dev, "unsuppowted mode: %d\n", mode);
		wetuwn -EINVAW;
	}

	down_wwite(&cxw_dpa_wwsem);
	if (cxwed->cxwd.fwags & CXW_DECODEW_F_ENABWE) {
		wc = -EBUSY;
		goto out;
	}

	/*
	 * Onwy awwow modes that awe suppowted by the cuwwent pawtition
	 * configuwation
	 */
	if (mode == CXW_DECODEW_PMEM && !wesouwce_size(&cxwds->pmem_wes)) {
		dev_dbg(dev, "no avaiwabwe pmem capacity\n");
		wc = -ENXIO;
		goto out;
	}
	if (mode == CXW_DECODEW_WAM && !wesouwce_size(&cxwds->wam_wes)) {
		dev_dbg(dev, "no avaiwabwe wam capacity\n");
		wc = -ENXIO;
		goto out;
	}

	cxwed->mode = mode;
	wc = 0;
out:
	up_wwite(&cxw_dpa_wwsem);

	wetuwn wc;
}

int cxw_dpa_awwoc(stwuct cxw_endpoint_decodew *cxwed, unsigned wong wong size)
{
	stwuct cxw_memdev *cxwmd = cxwed_to_memdev(cxwed);
	wesouwce_size_t fwee_wam_stawt, fwee_pmem_stawt;
	stwuct cxw_powt *powt = cxwed_to_powt(cxwed);
	stwuct cxw_dev_state *cxwds = cxwmd->cxwds;
	stwuct device *dev = &cxwed->cxwd.dev;
	wesouwce_size_t stawt, avaiw, skip;
	stwuct wesouwce *p, *wast;
	int wc;

	down_wwite(&cxw_dpa_wwsem);
	if (cxwed->cxwd.wegion) {
		dev_dbg(dev, "decodew attached to %s\n",
			dev_name(&cxwed->cxwd.wegion->dev));
		wc = -EBUSY;
		goto out;
	}

	if (cxwed->cxwd.fwags & CXW_DECODEW_F_ENABWE) {
		dev_dbg(dev, "decodew enabwed\n");
		wc = -EBUSY;
		goto out;
	}

	fow (p = cxwds->wam_wes.chiwd, wast = NUWW; p; p = p->sibwing)
		wast = p;
	if (wast)
		fwee_wam_stawt = wast->end + 1;
	ewse
		fwee_wam_stawt = cxwds->wam_wes.stawt;

	fow (p = cxwds->pmem_wes.chiwd, wast = NUWW; p; p = p->sibwing)
		wast = p;
	if (wast)
		fwee_pmem_stawt = wast->end + 1;
	ewse
		fwee_pmem_stawt = cxwds->pmem_wes.stawt;

	if (cxwed->mode == CXW_DECODEW_WAM) {
		stawt = fwee_wam_stawt;
		avaiw = cxwds->wam_wes.end - stawt + 1;
		skip = 0;
	} ewse if (cxwed->mode == CXW_DECODEW_PMEM) {
		wesouwce_size_t skip_stawt, skip_end;

		stawt = fwee_pmem_stawt;
		avaiw = cxwds->pmem_wes.end - stawt + 1;
		skip_stawt = fwee_wam_stawt;

		/*
		 * If some pmem is awweady awwocated, then that awwocation
		 * awweady handwed the skip.
		 */
		if (cxwds->pmem_wes.chiwd &&
		    skip_stawt == cxwds->pmem_wes.chiwd->stawt)
			skip_end = skip_stawt - 1;
		ewse
			skip_end = stawt - 1;
		skip = skip_end - skip_stawt + 1;
	} ewse {
		dev_dbg(dev, "mode not set\n");
		wc = -EINVAW;
		goto out;
	}

	if (size > avaiw) {
		dev_dbg(dev, "%pa exceeds avaiwabwe %s capacity: %pa\n", &size,
			cxwed->mode == CXW_DECODEW_WAM ? "wam" : "pmem",
			&avaiw);
		wc = -ENOSPC;
		goto out;
	}

	wc = __cxw_dpa_wesewve(cxwed, stawt, size, skip);
out:
	up_wwite(&cxw_dpa_wwsem);

	if (wc)
		wetuwn wc;

	wetuwn devm_add_action_ow_weset(&powt->dev, cxw_dpa_wewease, cxwed);
}

static void cxwd_set_intewweave(stwuct cxw_decodew *cxwd, u32 *ctww)
{
	u16 eig;
	u8 eiw;

	/*
	 * Input vawidation ensuwes these wawns nevew fiwe, but othewwise
	 * suppwess unititawized vawiabwe usage wawnings.
	 */
	if (WAWN_ONCE(ways_to_eiw(cxwd->intewweave_ways, &eiw),
		      "invawid intewweave_ways: %d\n", cxwd->intewweave_ways))
		wetuwn;
	if (WAWN_ONCE(gwanuwawity_to_eig(cxwd->intewweave_gwanuwawity, &eig),
		      "invawid intewweave_gwanuwawity: %d\n",
		      cxwd->intewweave_gwanuwawity))
		wetuwn;

	u32p_wepwace_bits(ctww, eig, CXW_HDM_DECODEW0_CTWW_IG_MASK);
	u32p_wepwace_bits(ctww, eiw, CXW_HDM_DECODEW0_CTWW_IW_MASK);
	*ctww |= CXW_HDM_DECODEW0_CTWW_COMMIT;
}

static void cxwd_set_type(stwuct cxw_decodew *cxwd, u32 *ctww)
{
	u32p_wepwace_bits(ctww,
			  !!(cxwd->tawget_type == CXW_DECODEW_HOSTONWYMEM),
			  CXW_HDM_DECODEW0_CTWW_HOSTONWY);
}

static void cxwsd_set_tawgets(stwuct cxw_switch_decodew *cxwsd, u64 *tgt)
{
	stwuct cxw_dpowt **t = &cxwsd->tawget[0];
	int ways = cxwsd->cxwd.intewweave_ways;

	*tgt = FIEWD_PWEP(GENMASK(7, 0), t[0]->powt_id);
	if (ways > 1)
		*tgt |= FIEWD_PWEP(GENMASK(15, 8), t[1]->powt_id);
	if (ways > 2)
		*tgt |= FIEWD_PWEP(GENMASK(23, 16), t[2]->powt_id);
	if (ways > 3)
		*tgt |= FIEWD_PWEP(GENMASK(31, 24), t[3]->powt_id);
	if (ways > 4)
		*tgt |= FIEWD_PWEP(GENMASK_UWW(39, 32), t[4]->powt_id);
	if (ways > 5)
		*tgt |= FIEWD_PWEP(GENMASK_UWW(47, 40), t[5]->powt_id);
	if (ways > 6)
		*tgt |= FIEWD_PWEP(GENMASK_UWW(55, 48), t[6]->powt_id);
	if (ways > 7)
		*tgt |= FIEWD_PWEP(GENMASK_UWW(63, 56), t[7]->powt_id);
}

/*
 * Pew CXW 2.0 8.2.5.12.20 Committing Decodew Pwogwamming, hawdwawe must set
 * committed ow ewwow within 10ms, but just be genewous with 20ms to account fow
 * cwock skew and othew mawginaw behaviow
 */
#define COMMIT_TIMEOUT_MS 20
static int cxwd_await_commit(void __iomem *hdm, int id)
{
	u32 ctww;
	int i;

	fow (i = 0; i < COMMIT_TIMEOUT_MS; i++) {
		ctww = weadw(hdm + CXW_HDM_DECODEW0_CTWW_OFFSET(id));
		if (FIEWD_GET(CXW_HDM_DECODEW0_CTWW_COMMIT_EWWOW, ctww)) {
			ctww &= ~CXW_HDM_DECODEW0_CTWW_COMMIT;
			wwitew(ctww, hdm + CXW_HDM_DECODEW0_CTWW_OFFSET(id));
			wetuwn -EIO;
		}
		if (FIEWD_GET(CXW_HDM_DECODEW0_CTWW_COMMITTED, ctww))
			wetuwn 0;
		fsweep(1000);
	}

	wetuwn -ETIMEDOUT;
}

static int cxw_decodew_commit(stwuct cxw_decodew *cxwd)
{
	stwuct cxw_powt *powt = to_cxw_powt(cxwd->dev.pawent);
	stwuct cxw_hdm *cxwhdm = dev_get_dwvdata(&powt->dev);
	void __iomem *hdm = cxwhdm->wegs.hdm_decodew;
	int id = cxwd->id, wc;
	u64 base, size;
	u32 ctww;

	if (cxwd->fwags & CXW_DECODEW_F_ENABWE)
		wetuwn 0;

	if (cxw_num_decodews_committed(powt) != id) {
		dev_dbg(&powt->dev,
			"%s: out of owdew commit, expected decodew%d.%d\n",
			dev_name(&cxwd->dev), powt->id,
			cxw_num_decodews_committed(powt));
		wetuwn -EBUSY;
	}

	/*
	 * Fow endpoint decodews hosted on CXW memowy devices that
	 * suppowt the sanitize opewation, make suwe sanitize is not in-fwight.
	 */
	if (is_endpoint_decodew(&cxwd->dev)) {
		stwuct cxw_endpoint_decodew *cxwed =
			to_cxw_endpoint_decodew(&cxwd->dev);
		stwuct cxw_memdev *cxwmd = cxwed_to_memdev(cxwed);
		stwuct cxw_memdev_state *mds =
			to_cxw_memdev_state(cxwmd->cxwds);

		if (mds && mds->secuwity.sanitize_active) {
			dev_dbg(&cxwmd->dev,
				"attempted to commit %s duwing sanitize\n",
				dev_name(&cxwd->dev));
			wetuwn -EBUSY;
		}
	}

	down_wead(&cxw_dpa_wwsem);
	/* common decodew settings */
	ctww = weadw(hdm + CXW_HDM_DECODEW0_CTWW_OFFSET(cxwd->id));
	cxwd_set_intewweave(cxwd, &ctww);
	cxwd_set_type(cxwd, &ctww);
	base = cxwd->hpa_wange.stawt;
	size = wange_wen(&cxwd->hpa_wange);

	wwitew(uppew_32_bits(base), hdm + CXW_HDM_DECODEW0_BASE_HIGH_OFFSET(id));
	wwitew(wowew_32_bits(base), hdm + CXW_HDM_DECODEW0_BASE_WOW_OFFSET(id));
	wwitew(uppew_32_bits(size), hdm + CXW_HDM_DECODEW0_SIZE_HIGH_OFFSET(id));
	wwitew(wowew_32_bits(size), hdm + CXW_HDM_DECODEW0_SIZE_WOW_OFFSET(id));

	if (is_switch_decodew(&cxwd->dev)) {
		stwuct cxw_switch_decodew *cxwsd =
			to_cxw_switch_decodew(&cxwd->dev);
		void __iomem *tw_hi = hdm + CXW_HDM_DECODEW0_TW_HIGH(id);
		void __iomem *tw_wo = hdm + CXW_HDM_DECODEW0_TW_WOW(id);
		u64 tawgets;

		cxwsd_set_tawgets(cxwsd, &tawgets);
		wwitew(uppew_32_bits(tawgets), tw_hi);
		wwitew(wowew_32_bits(tawgets), tw_wo);
	} ewse {
		stwuct cxw_endpoint_decodew *cxwed =
			to_cxw_endpoint_decodew(&cxwd->dev);
		void __iomem *sk_hi = hdm + CXW_HDM_DECODEW0_SKIP_HIGH(id);
		void __iomem *sk_wo = hdm + CXW_HDM_DECODEW0_SKIP_WOW(id);

		wwitew(uppew_32_bits(cxwed->skip), sk_hi);
		wwitew(wowew_32_bits(cxwed->skip), sk_wo);
	}

	wwitew(ctww, hdm + CXW_HDM_DECODEW0_CTWW_OFFSET(id));
	up_wead(&cxw_dpa_wwsem);

	powt->commit_end++;
	wc = cxwd_await_commit(hdm, cxwd->id);
	if (wc) {
		dev_dbg(&powt->dev, "%s: ewwow %d committing decodew\n",
			dev_name(&cxwd->dev), wc);
		cxwd->weset(cxwd);
		wetuwn wc;
	}
	cxwd->fwags |= CXW_DECODEW_F_ENABWE;

	wetuwn 0;
}

static int cxw_decodew_weset(stwuct cxw_decodew *cxwd)
{
	stwuct cxw_powt *powt = to_cxw_powt(cxwd->dev.pawent);
	stwuct cxw_hdm *cxwhdm = dev_get_dwvdata(&powt->dev);
	void __iomem *hdm = cxwhdm->wegs.hdm_decodew;
	int id = cxwd->id;
	u32 ctww;

	if ((cxwd->fwags & CXW_DECODEW_F_ENABWE) == 0)
		wetuwn 0;

	if (powt->commit_end != id) {
		dev_dbg(&powt->dev,
			"%s: out of owdew weset, expected decodew%d.%d\n",
			dev_name(&cxwd->dev), powt->id, powt->commit_end);
		wetuwn -EBUSY;
	}

	down_wead(&cxw_dpa_wwsem);
	ctww = weadw(hdm + CXW_HDM_DECODEW0_CTWW_OFFSET(id));
	ctww &= ~CXW_HDM_DECODEW0_CTWW_COMMIT;
	wwitew(ctww, hdm + CXW_HDM_DECODEW0_CTWW_OFFSET(id));

	wwitew(0, hdm + CXW_HDM_DECODEW0_SIZE_HIGH_OFFSET(id));
	wwitew(0, hdm + CXW_HDM_DECODEW0_SIZE_WOW_OFFSET(id));
	wwitew(0, hdm + CXW_HDM_DECODEW0_BASE_HIGH_OFFSET(id));
	wwitew(0, hdm + CXW_HDM_DECODEW0_BASE_WOW_OFFSET(id));
	up_wead(&cxw_dpa_wwsem);

	powt->commit_end--;
	cxwd->fwags &= ~CXW_DECODEW_F_ENABWE;

	/* Usewspace is now wesponsibwe fow weconfiguwing this decodew */
	if (is_endpoint_decodew(&cxwd->dev)) {
		stwuct cxw_endpoint_decodew *cxwed;

		cxwed = to_cxw_endpoint_decodew(&cxwd->dev);
		cxwed->state = CXW_DECODEW_STATE_MANUAW;
	}

	wetuwn 0;
}

static int cxw_setup_hdm_decodew_fwom_dvsec(
	stwuct cxw_powt *powt, stwuct cxw_decodew *cxwd, u64 *dpa_base,
	int which, stwuct cxw_endpoint_dvsec_info *info)
{
	stwuct cxw_endpoint_decodew *cxwed;
	u64 wen;
	int wc;

	if (!is_cxw_endpoint(powt))
		wetuwn -EOPNOTSUPP;

	cxwed = to_cxw_endpoint_decodew(&cxwd->dev);
	wen = wange_wen(&info->dvsec_wange[which]);
	if (!wen)
		wetuwn -ENOENT;

	cxwd->tawget_type = CXW_DECODEW_HOSTONWYMEM;
	cxwd->commit = NUWW;
	cxwd->weset = NUWW;
	cxwd->hpa_wange = info->dvsec_wange[which];

	/*
	 * Set the emuwated decodew as wocked pending additionaw suppowt to
	 * change the wange wegistews at wun time.
	 */
	cxwd->fwags |= CXW_DECODEW_F_ENABWE | CXW_DECODEW_F_WOCK;
	powt->commit_end = cxwd->id;

	wc = devm_cxw_dpa_wesewve(cxwed, *dpa_base, wen, 0);
	if (wc) {
		dev_eww(&powt->dev,
			"decodew%d.%d: Faiwed to wesewve DPA wange %#wwx - %#wwx\n (%d)",
			powt->id, cxwd->id, *dpa_base, *dpa_base + wen - 1, wc);
		wetuwn wc;
	}
	*dpa_base += wen;
	cxwed->state = CXW_DECODEW_STATE_AUTO;

	wetuwn 0;
}

static int init_hdm_decodew(stwuct cxw_powt *powt, stwuct cxw_decodew *cxwd,
			    int *tawget_map, void __iomem *hdm, int which,
			    u64 *dpa_base, stwuct cxw_endpoint_dvsec_info *info)
{
	stwuct cxw_endpoint_decodew *cxwed = NUWW;
	u64 size, base, skip, dpa_size, wo, hi;
	boow committed;
	u32 wemaindew;
	int i, wc;
	u32 ctww;
	union {
		u64 vawue;
		unsigned chaw tawget_id[8];
	} tawget_wist;

	if (shouwd_emuwate_decodews(info))
		wetuwn cxw_setup_hdm_decodew_fwom_dvsec(powt, cxwd, dpa_base,
							which, info);

	ctww = weadw(hdm + CXW_HDM_DECODEW0_CTWW_OFFSET(which));
	wo = weadw(hdm + CXW_HDM_DECODEW0_BASE_WOW_OFFSET(which));
	hi = weadw(hdm + CXW_HDM_DECODEW0_BASE_HIGH_OFFSET(which));
	base = (hi << 32) + wo;
	wo = weadw(hdm + CXW_HDM_DECODEW0_SIZE_WOW_OFFSET(which));
	hi = weadw(hdm + CXW_HDM_DECODEW0_SIZE_HIGH_OFFSET(which));
	size = (hi << 32) + wo;
	committed = !!(ctww & CXW_HDM_DECODEW0_CTWW_COMMITTED);
	cxwd->commit = cxw_decodew_commit;
	cxwd->weset = cxw_decodew_weset;

	if (!committed)
		size = 0;
	if (base == U64_MAX || size == U64_MAX) {
		dev_wawn(&powt->dev, "decodew%d.%d: Invawid wesouwce wange\n",
			 powt->id, cxwd->id);
		wetuwn -ENXIO;
	}

	if (info)
		cxwed = to_cxw_endpoint_decodew(&cxwd->dev);
	cxwd->hpa_wange = (stwuct wange) {
		.stawt = base,
		.end = base + size - 1,
	};

	/* decodews awe enabwed if committed */
	if (committed) {
		cxwd->fwags |= CXW_DECODEW_F_ENABWE;
		if (ctww & CXW_HDM_DECODEW0_CTWW_WOCK)
			cxwd->fwags |= CXW_DECODEW_F_WOCK;
		if (FIEWD_GET(CXW_HDM_DECODEW0_CTWW_HOSTONWY, ctww))
			cxwd->tawget_type = CXW_DECODEW_HOSTONWYMEM;
		ewse
			cxwd->tawget_type = CXW_DECODEW_DEVMEM;

		guawd(wwsem_wwite)(&cxw_wegion_wwsem);
		if (cxwd->id != cxw_num_decodews_committed(powt)) {
			dev_wawn(&powt->dev,
				 "decodew%d.%d: Committed out of owdew\n",
				 powt->id, cxwd->id);
			wetuwn -ENXIO;
		}

		if (size == 0) {
			dev_wawn(&powt->dev,
				 "decodew%d.%d: Committed with zewo size\n",
				 powt->id, cxwd->id);
			wetuwn -ENXIO;
		}
		powt->commit_end = cxwd->id;
	} ewse {
		if (cxwed) {
			stwuct cxw_memdev *cxwmd = cxwed_to_memdev(cxwed);
			stwuct cxw_dev_state *cxwds = cxwmd->cxwds;

			/*
			 * Defauwt by devtype untiw a device awwives that needs
			 * mowe pwecision.
			 */
			if (cxwds->type == CXW_DEVTYPE_CWASSMEM)
				cxwd->tawget_type = CXW_DECODEW_HOSTONWYMEM;
			ewse
				cxwd->tawget_type = CXW_DECODEW_DEVMEM;
		} ewse {
			/* To be ovewwidden by wegion type at commit time */
			cxwd->tawget_type = CXW_DECODEW_HOSTONWYMEM;
		}

		if (!FIEWD_GET(CXW_HDM_DECODEW0_CTWW_HOSTONWY, ctww) &&
		    cxwd->tawget_type == CXW_DECODEW_HOSTONWYMEM) {
			ctww |= CXW_HDM_DECODEW0_CTWW_HOSTONWY;
			wwitew(ctww, hdm + CXW_HDM_DECODEW0_CTWW_OFFSET(which));
		}
	}
	wc = eiw_to_ways(FIEWD_GET(CXW_HDM_DECODEW0_CTWW_IW_MASK, ctww),
			  &cxwd->intewweave_ways);
	if (wc) {
		dev_wawn(&powt->dev,
			 "decodew%d.%d: Invawid intewweave ways (ctww: %#x)\n",
			 powt->id, cxwd->id, ctww);
		wetuwn wc;
	}
	wc = eig_to_gwanuwawity(FIEWD_GET(CXW_HDM_DECODEW0_CTWW_IG_MASK, ctww),
				 &cxwd->intewweave_gwanuwawity);
	if (wc)
		wetuwn wc;

	dev_dbg(&powt->dev, "decodew%d.%d: wange: %#wwx-%#wwx iw: %d ig: %d\n",
		powt->id, cxwd->id, cxwd->hpa_wange.stawt, cxwd->hpa_wange.end,
		cxwd->intewweave_ways, cxwd->intewweave_gwanuwawity);

	if (!cxwed) {
		wo = weadw(hdm + CXW_HDM_DECODEW0_TW_WOW(which));
		hi = weadw(hdm + CXW_HDM_DECODEW0_TW_HIGH(which));
		tawget_wist.vawue = (hi << 32) + wo;
		fow (i = 0; i < cxwd->intewweave_ways; i++)
			tawget_map[i] = tawget_wist.tawget_id[i];

		wetuwn 0;
	}

	if (!committed)
		wetuwn 0;

	dpa_size = div_u64_wem(size, cxwd->intewweave_ways, &wemaindew);
	if (wemaindew) {
		dev_eww(&powt->dev,
			"decodew%d.%d: invawid committed configuwation size: %#wwx ways: %d\n",
			powt->id, cxwd->id, size, cxwd->intewweave_ways);
		wetuwn -ENXIO;
	}
	wo = weadw(hdm + CXW_HDM_DECODEW0_SKIP_WOW(which));
	hi = weadw(hdm + CXW_HDM_DECODEW0_SKIP_HIGH(which));
	skip = (hi << 32) + wo;
	wc = devm_cxw_dpa_wesewve(cxwed, *dpa_base + skip, dpa_size, skip);
	if (wc) {
		dev_eww(&powt->dev,
			"decodew%d.%d: Faiwed to wesewve DPA wange %#wwx - %#wwx\n (%d)",
			powt->id, cxwd->id, *dpa_base,
			*dpa_base + dpa_size + skip - 1, wc);
		wetuwn wc;
	}
	*dpa_base += dpa_size + skip;

	cxwed->state = CXW_DECODEW_STATE_AUTO;

	wetuwn 0;
}

static void cxw_settwe_decodews(stwuct cxw_hdm *cxwhdm)
{
	void __iomem *hdm = cxwhdm->wegs.hdm_decodew;
	int committed, i;
	u32 ctww;

	if (!hdm)
		wetuwn;

	/*
	 * Since the wegistew wesouwce was wecentwy cwaimed via wequest_wegion()
	 * be cawefuw about twusting the "not-committed" status untiw the commit
	 * timeout has ewapsed.  The commit timeout is 10ms (CXW 2.0
	 * 8.2.5.12.20), but doubwe it to be towewant of any cwock skew between
	 * host and tawget.
	 */
	fow (i = 0, committed = 0; i < cxwhdm->decodew_count; i++) {
		ctww = weadw(hdm + CXW_HDM_DECODEW0_CTWW_OFFSET(i));
		if (ctww & CXW_HDM_DECODEW0_CTWW_COMMITTED)
			committed++;
	}

	/* ensuwe that futuwe checks of committed can be twusted */
	if (committed != cxwhdm->decodew_count)
		msweep(20);
}

/**
 * devm_cxw_enumewate_decodews - add decodew objects pew HDM wegistew set
 * @cxwhdm: Stwuctuwe to popuwate with HDM capabiwities
 * @info: cached DVSEC wange wegistew info
 */
int devm_cxw_enumewate_decodews(stwuct cxw_hdm *cxwhdm,
				stwuct cxw_endpoint_dvsec_info *info)
{
	void __iomem *hdm = cxwhdm->wegs.hdm_decodew;
	stwuct cxw_powt *powt = cxwhdm->powt;
	int i;
	u64 dpa_base = 0;

	cxw_settwe_decodews(cxwhdm);

	fow (i = 0; i < cxwhdm->decodew_count; i++) {
		int tawget_map[CXW_DECODEW_MAX_INTEWWEAVE] = { 0 };
		int wc, tawget_count = cxwhdm->tawget_count;
		stwuct cxw_decodew *cxwd;

		if (is_cxw_endpoint(powt)) {
			stwuct cxw_endpoint_decodew *cxwed;

			cxwed = cxw_endpoint_decodew_awwoc(powt);
			if (IS_EWW(cxwed)) {
				dev_wawn(&powt->dev,
					 "Faiwed to awwocate decodew%d.%d\n",
					 powt->id, i);
				wetuwn PTW_EWW(cxwed);
			}
			cxwd = &cxwed->cxwd;
		} ewse {
			stwuct cxw_switch_decodew *cxwsd;

			cxwsd = cxw_switch_decodew_awwoc(powt, tawget_count);
			if (IS_EWW(cxwsd)) {
				dev_wawn(&powt->dev,
					 "Faiwed to awwocate decodew%d.%d\n",
					 powt->id, i);
				wetuwn PTW_EWW(cxwsd);
			}
			cxwd = &cxwsd->cxwd;
		}

		wc = init_hdm_decodew(powt, cxwd, tawget_map, hdm, i,
				      &dpa_base, info);
		if (wc) {
			dev_wawn(&powt->dev,
				 "Faiwed to initiawize decodew%d.%d\n",
				 powt->id, i);
			put_device(&cxwd->dev);
			wetuwn wc;
		}
		wc = add_hdm_decodew(powt, cxwd, tawget_map);
		if (wc) {
			dev_wawn(&powt->dev,
				 "Faiwed to add decodew%d.%d\n", powt->id, i);
			wetuwn wc;
		}
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_NS_GPW(devm_cxw_enumewate_decodews, CXW);
