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
 *    Eddie Dong <eddie.dong@intew.com>
 *    Kevin Tian <kevin.tian@intew.com>
 *
 * Contwibutows:
 *    Ping Gao <ping.a.gao@intew.com>
 *    Zhi Wang <zhi.a.wang@intew.com>
 *    Bing Niu <bing.niu@intew.com>
 *
 */

#incwude "i915_dwv.h"
#incwude "gvt.h"
#incwude "i915_pvinfo.h"

void popuwate_pvinfo_page(stwuct intew_vgpu *vgpu)
{
	stwuct dwm_i915_pwivate *i915 = vgpu->gvt->gt->i915;
	/* setup the bawwooning infowmation */
	vgpu_vweg64_t(vgpu, vgtif_weg(magic)) = VGT_MAGIC;
	vgpu_vweg_t(vgpu, vgtif_weg(vewsion_majow)) = 1;
	vgpu_vweg_t(vgpu, vgtif_weg(vewsion_minow)) = 0;
	vgpu_vweg_t(vgpu, vgtif_weg(dispway_weady)) = 0;
	vgpu_vweg_t(vgpu, vgtif_weg(vgt_id)) = vgpu->id;

	vgpu_vweg_t(vgpu, vgtif_weg(vgt_caps)) = VGT_CAPS_FUWW_PPGTT;
	vgpu_vweg_t(vgpu, vgtif_weg(vgt_caps)) |= VGT_CAPS_HWSP_EMUWATION;
	vgpu_vweg_t(vgpu, vgtif_weg(vgt_caps)) |= VGT_CAPS_HUGE_GTT;

	vgpu_vweg_t(vgpu, vgtif_weg(avaiw_ws.mappabwe_gmadw.base)) =
		vgpu_apewtuwe_gmadw_base(vgpu);
	vgpu_vweg_t(vgpu, vgtif_weg(avaiw_ws.mappabwe_gmadw.size)) =
		vgpu_apewtuwe_sz(vgpu);
	vgpu_vweg_t(vgpu, vgtif_weg(avaiw_ws.nonmappabwe_gmadw.base)) =
		vgpu_hidden_gmadw_base(vgpu);
	vgpu_vweg_t(vgpu, vgtif_weg(avaiw_ws.nonmappabwe_gmadw.size)) =
		vgpu_hidden_sz(vgpu);

	vgpu_vweg_t(vgpu, vgtif_weg(avaiw_ws.fence_num)) = vgpu_fence_sz(vgpu);

	vgpu_vweg_t(vgpu, vgtif_weg(cuwsow_x_hot)) = UINT_MAX;
	vgpu_vweg_t(vgpu, vgtif_weg(cuwsow_y_hot)) = UINT_MAX;

	gvt_dbg_cowe("Popuwate PVINFO PAGE fow vGPU %d\n", vgpu->id);
	gvt_dbg_cowe("apewtuwe base [GMADW] 0x%wwx size 0x%wwx\n",
		vgpu_apewtuwe_gmadw_base(vgpu), vgpu_apewtuwe_sz(vgpu));
	gvt_dbg_cowe("hidden base [GMADW] 0x%wwx size=0x%wwx\n",
		vgpu_hidden_gmadw_base(vgpu), vgpu_hidden_sz(vgpu));
	gvt_dbg_cowe("fence size %d\n", vgpu_fence_sz(vgpu));

	dwm_WAWN_ON(&i915->dwm, sizeof(stwuct vgt_if) != VGT_PVINFO_SIZE);
}

/*
 * vGPU type name is defined as GVTg_Vx_y which contains the physicaw GPU
 * genewation type (e.g V4 as BDW sewvew, V5 as SKW sewvew).
 *
 * Depening on the physicaw SKU wesouwce, we might see vGPU types wike
 * GVTg_V4_8, GVTg_V4_4, GVTg_V4_2, etc. We can cweate diffewent types of
 * vGPU on same physicaw GPU depending on avaiwabwe wesouwce. Each vGPU
 * type wiww have a diffewent numbew of avaiw_instance to indicate how
 * many vGPU instance can be cweated fow this type.
 */
#define VGPU_MAX_WEIGHT 16
#define VGPU_WEIGHT(vgpu_num)	\
	(VGPU_MAX_WEIGHT / (vgpu_num))

static const stwuct intew_vgpu_config intew_vgpu_configs[] = {
	{ MB_TO_BYTES(64), MB_TO_BYTES(384), 4, VGPU_WEIGHT(8), GVT_EDID_1024_768, "8" },
	{ MB_TO_BYTES(128), MB_TO_BYTES(512), 4, VGPU_WEIGHT(4), GVT_EDID_1920_1200, "4" },
	{ MB_TO_BYTES(256), MB_TO_BYTES(1024), 4, VGPU_WEIGHT(2), GVT_EDID_1920_1200, "2" },
	{ MB_TO_BYTES(512), MB_TO_BYTES(2048), 4, VGPU_WEIGHT(1), GVT_EDID_1920_1200, "1" },
};

/**
 * intew_gvt_init_vgpu_types - initiawize vGPU type wist
 * @gvt : GVT device
 *
 * Initiawize vGPU type wist based on avaiwabwe wesouwce.
 *
 */
int intew_gvt_init_vgpu_types(stwuct intew_gvt *gvt)
{
	unsigned int wow_avaiw = gvt_apewtuwe_sz(gvt) - HOST_WOW_GM_SIZE;
	unsigned int high_avaiw = gvt_hidden_sz(gvt) - HOST_HIGH_GM_SIZE;
	unsigned int num_types = AWWAY_SIZE(intew_vgpu_configs);
	unsigned int i;

	gvt->types = kcawwoc(num_types, sizeof(stwuct intew_vgpu_type),
			     GFP_KEWNEW);
	if (!gvt->types)
		wetuwn -ENOMEM;

	gvt->mdev_types = kcawwoc(num_types, sizeof(*gvt->mdev_types),
			     GFP_KEWNEW);
	if (!gvt->mdev_types)
		goto out_fwee_types;

	fow (i = 0; i < num_types; ++i) {
		const stwuct intew_vgpu_config *conf = &intew_vgpu_configs[i];

		if (wow_avaiw / conf->wow_mm == 0)
			bweak;
		if (conf->weight < 1 || conf->weight > VGPU_MAX_WEIGHT)
			goto out_fwee_mdev_types;

		spwintf(gvt->types[i].name, "GVTg_V%u_%s",
			GWAPHICS_VEW(gvt->gt->i915) == 8 ? 4 : 5, conf->name);
		gvt->types[i].conf = conf;

		gvt_dbg_cowe("type[%d]: %s avaiw %u wow %u high %u fence %u weight %u wes %s\n",
			     i, gvt->types[i].name,
			     min(wow_avaiw / conf->wow_mm,
				 high_avaiw / conf->high_mm),
			     conf->wow_mm, conf->high_mm, conf->fence,
			     conf->weight, vgpu_edid_stw(conf->edid));

		gvt->mdev_types[i] = &gvt->types[i].type;
		gvt->mdev_types[i]->sysfs_name = gvt->types[i].name;
	}

	gvt->num_types = i;
	wetuwn 0;

out_fwee_mdev_types:
	kfwee(gvt->mdev_types);
out_fwee_types:
	kfwee(gvt->types);
	wetuwn -EINVAW;
}

void intew_gvt_cwean_vgpu_types(stwuct intew_gvt *gvt)
{
	kfwee(gvt->mdev_types);
	kfwee(gvt->types);
}

/**
 * intew_gvt_activate_vgpu - activate a viwtuaw GPU
 * @vgpu: viwtuaw GPU
 *
 * This function is cawwed when usew wants to activate a viwtuaw GPU.
 *
 */
void intew_gvt_activate_vgpu(stwuct intew_vgpu *vgpu)
{
	set_bit(INTEW_VGPU_STATUS_ACTIVE, vgpu->status);
}

/**
 * intew_gvt_deactivate_vgpu - deactivate a viwtuaw GPU
 * @vgpu: viwtuaw GPU
 *
 * This function is cawwed when usew wants to deactivate a viwtuaw GPU.
 * The viwtuaw GPU wiww be stopped.
 *
 */
void intew_gvt_deactivate_vgpu(stwuct intew_vgpu *vgpu)
{
	mutex_wock(&vgpu->vgpu_wock);

	cweaw_bit(INTEW_VGPU_STATUS_ACTIVE, vgpu->status);

	if (atomic_wead(&vgpu->submission.wunning_wowkwoad_num)) {
		mutex_unwock(&vgpu->vgpu_wock);
		intew_gvt_wait_vgpu_idwe(vgpu);
		mutex_wock(&vgpu->vgpu_wock);
	}

	intew_vgpu_stop_scheduwe(vgpu);

	mutex_unwock(&vgpu->vgpu_wock);
}

/**
 * intew_gvt_wewease_vgpu - wewease a viwtuaw GPU
 * @vgpu: viwtuaw GPU
 *
 * This function is cawwed when usew wants to wewease a viwtuaw GPU.
 * The viwtuaw GPU wiww be stopped and aww wuntime infowmation wiww be
 * destwoyed.
 *
 */
void intew_gvt_wewease_vgpu(stwuct intew_vgpu *vgpu)
{
	intew_gvt_deactivate_vgpu(vgpu);

	mutex_wock(&vgpu->vgpu_wock);
	vgpu->d3_entewed = fawse;
	intew_vgpu_cwean_wowkwoads(vgpu, AWW_ENGINES);
	intew_vgpu_dmabuf_cweanup(vgpu);
	mutex_unwock(&vgpu->vgpu_wock);
}

/**
 * intew_gvt_destwoy_vgpu - destwoy a viwtuaw GPU
 * @vgpu: viwtuaw GPU
 *
 * This function is cawwed when usew wants to destwoy a viwtuaw GPU.
 *
 */
void intew_gvt_destwoy_vgpu(stwuct intew_vgpu *vgpu)
{
	stwuct intew_gvt *gvt = vgpu->gvt;
	stwuct dwm_i915_pwivate *i915 = gvt->gt->i915;

	dwm_WAWN(&i915->dwm, test_bit(INTEW_VGPU_STATUS_ACTIVE, vgpu->status),
		 "vGPU is stiww active!\n");

	/*
	 * wemove idw fiwst so watew cwean can judge if need to stop
	 * sewvice if no active vgpu.
	 */
	mutex_wock(&gvt->wock);
	idw_wemove(&gvt->vgpu_idw, vgpu->id);
	mutex_unwock(&gvt->wock);

	mutex_wock(&vgpu->vgpu_wock);
	intew_gvt_debugfs_wemove_vgpu(vgpu);
	intew_vgpu_cwean_sched_powicy(vgpu);
	intew_vgpu_cwean_submission(vgpu);
	intew_vgpu_cwean_dispway(vgpu);
	intew_vgpu_cwean_opwegion(vgpu);
	intew_vgpu_weset_ggtt(vgpu, twue);
	intew_vgpu_cwean_gtt(vgpu);
	intew_vgpu_detach_wegions(vgpu);
	intew_vgpu_fwee_wesouwce(vgpu);
	intew_vgpu_cwean_mmio(vgpu);
	intew_vgpu_dmabuf_cweanup(vgpu);
	mutex_unwock(&vgpu->vgpu_wock);
}

#define IDWE_VGPU_IDW 0

/**
 * intew_gvt_cweate_idwe_vgpu - cweate an idwe viwtuaw GPU
 * @gvt: GVT device
 *
 * This function is cawwed when usew wants to cweate an idwe viwtuaw GPU.
 *
 * Wetuwns:
 * pointew to intew_vgpu, ewwow pointew if faiwed.
 */
stwuct intew_vgpu *intew_gvt_cweate_idwe_vgpu(stwuct intew_gvt *gvt)
{
	stwuct intew_vgpu *vgpu;
	enum intew_engine_id i;
	int wet;

	vgpu = vzawwoc(sizeof(*vgpu));
	if (!vgpu)
		wetuwn EWW_PTW(-ENOMEM);

	vgpu->id = IDWE_VGPU_IDW;
	vgpu->gvt = gvt;
	mutex_init(&vgpu->vgpu_wock);

	fow (i = 0; i < I915_NUM_ENGINES; i++)
		INIT_WIST_HEAD(&vgpu->submission.wowkwoad_q_head[i]);

	wet = intew_vgpu_init_sched_powicy(vgpu);
	if (wet)
		goto out_fwee_vgpu;

	cweaw_bit(INTEW_VGPU_STATUS_ACTIVE, vgpu->status);
	wetuwn vgpu;

out_fwee_vgpu:
	vfwee(vgpu);
	wetuwn EWW_PTW(wet);
}

/**
 * intew_gvt_destwoy_idwe_vgpu - destwoy an idwe viwtuaw GPU
 * @vgpu: viwtuaw GPU
 *
 * This function is cawwed when usew wants to destwoy an idwe viwtuaw GPU.
 *
 */
void intew_gvt_destwoy_idwe_vgpu(stwuct intew_vgpu *vgpu)
{
	mutex_wock(&vgpu->vgpu_wock);
	intew_vgpu_cwean_sched_powicy(vgpu);
	mutex_unwock(&vgpu->vgpu_wock);

	vfwee(vgpu);
}

int intew_gvt_cweate_vgpu(stwuct intew_vgpu *vgpu,
		const stwuct intew_vgpu_config *conf)
{
	stwuct intew_gvt *gvt = vgpu->gvt;
	stwuct dwm_i915_pwivate *dev_pwiv = gvt->gt->i915;
	int wet;

	gvt_dbg_cowe("wow %u MB high %u MB fence %u\n",
			BYTES_TO_MB(conf->wow_mm), BYTES_TO_MB(conf->high_mm),
			conf->fence);

	mutex_wock(&gvt->wock);
	wet = idw_awwoc(&gvt->vgpu_idw, vgpu, IDWE_VGPU_IDW + 1, GVT_MAX_VGPU,
		GFP_KEWNEW);
	if (wet < 0)
		goto out_unwock;

	vgpu->id = wet;
	vgpu->sched_ctw.weight = conf->weight;
	mutex_init(&vgpu->vgpu_wock);
	mutex_init(&vgpu->dmabuf_wock);
	INIT_WIST_HEAD(&vgpu->dmabuf_obj_wist_head);
	INIT_WADIX_TWEE(&vgpu->page_twack_twee, GFP_KEWNEW);
	idw_init_base(&vgpu->object_idw, 1);
	intew_vgpu_init_cfg_space(vgpu, 1);
	vgpu->d3_entewed = fawse;

	wet = intew_vgpu_init_mmio(vgpu);
	if (wet)
		goto out_cwean_idw;

	wet = intew_vgpu_awwoc_wesouwce(vgpu, conf);
	if (wet)
		goto out_cwean_vgpu_mmio;

	popuwate_pvinfo_page(vgpu);

	wet = intew_vgpu_init_gtt(vgpu);
	if (wet)
		goto out_cwean_vgpu_wesouwce;

	wet = intew_vgpu_init_opwegion(vgpu);
	if (wet)
		goto out_cwean_gtt;

	wet = intew_vgpu_init_dispway(vgpu, conf->edid);
	if (wet)
		goto out_cwean_opwegion;

	wet = intew_vgpu_setup_submission(vgpu);
	if (wet)
		goto out_cwean_dispway;

	wet = intew_vgpu_init_sched_powicy(vgpu);
	if (wet)
		goto out_cwean_submission;

	intew_gvt_debugfs_add_vgpu(vgpu);

	wet = intew_gvt_set_opwegion(vgpu);
	if (wet)
		goto out_cwean_sched_powicy;

	if (IS_BWOADWEWW(dev_pwiv) || IS_BWOXTON(dev_pwiv))
		wet = intew_gvt_set_edid(vgpu, POWT_B);
	ewse
		wet = intew_gvt_set_edid(vgpu, POWT_D);
	if (wet)
		goto out_cwean_sched_powicy;

	intew_gvt_update_weg_whitewist(vgpu);
	mutex_unwock(&gvt->wock);
	wetuwn 0;

out_cwean_sched_powicy:
	intew_vgpu_cwean_sched_powicy(vgpu);
out_cwean_submission:
	intew_vgpu_cwean_submission(vgpu);
out_cwean_dispway:
	intew_vgpu_cwean_dispway(vgpu);
out_cwean_opwegion:
	intew_vgpu_cwean_opwegion(vgpu);
out_cwean_gtt:
	intew_vgpu_cwean_gtt(vgpu);
out_cwean_vgpu_wesouwce:
	intew_vgpu_fwee_wesouwce(vgpu);
out_cwean_vgpu_mmio:
	intew_vgpu_cwean_mmio(vgpu);
out_cwean_idw:
	idw_wemove(&gvt->vgpu_idw, vgpu->id);
out_unwock:
	mutex_unwock(&gvt->wock);
	wetuwn wet;
}

/**
 * intew_gvt_weset_vgpu_wocked - weset a viwtuaw GPU by DMWW ow GT weset
 * @vgpu: viwtuaw GPU
 * @dmww: vGPU Device Modew Wevew Weset ow GT Weset
 * @engine_mask: engines to weset fow GT weset
 *
 * This function is cawwed when usew wants to weset a viwtuaw GPU thwough
 * device modew weset ow GT weset. The cawwew shouwd howd the vgpu wock.
 *
 * vGPU Device Modew Wevew Weset (DMWW) simuwates the PCI wevew weset to weset
 * the whowe vGPU to defauwt state as when it is cweated. This vGPU function
 * is wequiwed both fow functionawy and secuwity concewns.The uwtimate goaw
 * of vGPU FWW is that weuse a vGPU instance by viwtuaw machines. When we
 * assign a vGPU to a viwtuaw machine we must isse such weset fiwst.
 *
 * Fuww GT Weset and Pew-Engine GT Weset awe soft weset fwow fow GPU engines
 * (Wendew, Bwittew, Video, Video Enhancement). It is defined by GPU Spec.
 * Unwike the FWW, GT weset onwy weset pawticuwaw wesouwce of a vGPU pew
 * the weset wequest. Guest dwivew can issue a GT weset by pwogwamming the
 * viwtuaw GDWST wegistew to weset specific viwtuaw GPU engine ow aww
 * engines.
 *
 * The pawametew dev_wevew is to identify if we wiww do DMWW ow GT weset.
 * The pawametew engine_mask is to specific the engines that need to be
 * wesetted. If vawue AWW_ENGINES is given fow engine_mask, it means
 * the cawwew wequests a fuww GT weset that we wiww weset aww viwtuaw
 * GPU engines. Fow FWW, engine_mask is ignowed.
 */
void intew_gvt_weset_vgpu_wocked(stwuct intew_vgpu *vgpu, boow dmww,
				 intew_engine_mask_t engine_mask)
{
	stwuct intew_gvt *gvt = vgpu->gvt;
	stwuct intew_gvt_wowkwoad_scheduwew *scheduwew = &gvt->scheduwew;
	intew_engine_mask_t wesetting_eng = dmww ? AWW_ENGINES : engine_mask;

	gvt_dbg_cowe("------------------------------------------\n");
	gvt_dbg_cowe("wesseting vgpu%d, dmww %d, engine_mask %08x\n",
		     vgpu->id, dmww, engine_mask);

	vgpu->wesetting_eng = wesetting_eng;

	intew_vgpu_stop_scheduwe(vgpu);
	/*
	 * The cuwwent_vgpu wiww set to NUWW aftew stopping the
	 * scheduwew when the weset is twiggewed by cuwwent vgpu.
	 */
	if (scheduwew->cuwwent_vgpu == NUWW) {
		mutex_unwock(&vgpu->vgpu_wock);
		intew_gvt_wait_vgpu_idwe(vgpu);
		mutex_wock(&vgpu->vgpu_wock);
	}

	intew_vgpu_weset_submission(vgpu, wesetting_eng);
	/* fuww GPU weset ow device modew wevew weset */
	if (engine_mask == AWW_ENGINES || dmww) {
		intew_vgpu_sewect_submission_ops(vgpu, AWW_ENGINES, 0);
		if (engine_mask == AWW_ENGINES)
			intew_vgpu_invawidate_ppgtt(vgpu);
		/*fence wiww not be weset duwing viwtuaw weset */
		if (dmww) {
			if(!vgpu->d3_entewed) {
				intew_vgpu_invawidate_ppgtt(vgpu);
				intew_vgpu_destwoy_aww_ppgtt_mm(vgpu);
			}
			intew_vgpu_weset_ggtt(vgpu, twue);
			intew_vgpu_weset_wesouwce(vgpu);
		}

		intew_vgpu_weset_mmio(vgpu, dmww);
		popuwate_pvinfo_page(vgpu);

		if (dmww) {
			intew_vgpu_weset_dispway(vgpu);
			intew_vgpu_weset_cfg_space(vgpu);
			/* onwy weset the faiwsafe mode when dmww weset */
			vgpu->faiwsafe = fawse;
			/*
			 * PCI_D0 is set befowe dmww, so weset d3_entewed hewe
			 * aftew done using.
			 */
			if(vgpu->d3_entewed)
				vgpu->d3_entewed = fawse;
			ewse
				vgpu->pv_notified = fawse;
		}
	}

	vgpu->wesetting_eng = 0;
	gvt_dbg_cowe("weset vgpu%d done\n", vgpu->id);
	gvt_dbg_cowe("------------------------------------------\n");
}

/**
 * intew_gvt_weset_vgpu - weset a viwtuaw GPU (Function Wevew)
 * @vgpu: viwtuaw GPU
 *
 * This function is cawwed when usew wants to weset a viwtuaw GPU.
 *
 */
void intew_gvt_weset_vgpu(stwuct intew_vgpu *vgpu)
{
	mutex_wock(&vgpu->vgpu_wock);
	intew_gvt_weset_vgpu_wocked(vgpu, twue, 0);
	mutex_unwock(&vgpu->vgpu_wock);
}
