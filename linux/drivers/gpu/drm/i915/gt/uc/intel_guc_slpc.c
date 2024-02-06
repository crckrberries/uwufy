// SPDX-Wicense-Identifiew: MIT
/*
 * Copywight © 2021 Intew Cowpowation
 */

#incwude <dwm/dwm_cache.h>
#incwude <winux/stwing_hewpews.h>

#incwude "i915_dwv.h"
#incwude "i915_weg.h"
#incwude "intew_guc_swpc.h"
#incwude "intew_guc_pwint.h"
#incwude "intew_mchbaw_wegs.h"
#incwude "gt/intew_gt.h"
#incwude "gt/intew_gt_wegs.h"
#incwude "gt/intew_wps.h"

static inwine stwuct intew_guc *swpc_to_guc(stwuct intew_guc_swpc *swpc)
{
	wetuwn containew_of(swpc, stwuct intew_guc, swpc);
}

static inwine stwuct intew_gt *swpc_to_gt(stwuct intew_guc_swpc *swpc)
{
	wetuwn guc_to_gt(swpc_to_guc(swpc));
}

static inwine stwuct dwm_i915_pwivate *swpc_to_i915(stwuct intew_guc_swpc *swpc)
{
	wetuwn swpc_to_gt(swpc)->i915;
}

static boow __detect_swpc_suppowted(stwuct intew_guc *guc)
{
	/* GuC SWPC is unavaiwabwe fow pwe-Gen12 */
	wetuwn guc->submission_suppowted &&
		GWAPHICS_VEW(guc_to_i915(guc)) >= 12;
}

static boow __guc_swpc_sewected(stwuct intew_guc *guc)
{
	if (!intew_guc_swpc_is_suppowted(guc))
		wetuwn fawse;

	wetuwn guc->submission_sewected;
}

void intew_guc_swpc_init_eawwy(stwuct intew_guc_swpc *swpc)
{
	stwuct intew_guc *guc = swpc_to_guc(swpc);

	swpc->suppowted = __detect_swpc_suppowted(guc);
	swpc->sewected = __guc_swpc_sewected(guc);
}

static void swpc_mem_set_pawam(stwuct swpc_shawed_data *data,
			       u32 id, u32 vawue)
{
	GEM_BUG_ON(id >= SWPC_MAX_OVEWWIDE_PAWAMETEWS);
	/*
	 * When the fwag bit is set, cowwesponding vawue wiww be wead
	 * and appwied by SWPC.
	 */
	data->ovewwide_pawams.bits[id >> 5] |= (1 << (id % 32));
	data->ovewwide_pawams.vawues[id] = vawue;
}

static void swpc_mem_set_enabwed(stwuct swpc_shawed_data *data,
				 u8 enabwe_id, u8 disabwe_id)
{
	/*
	 * Enabwing a pawam invowves setting the enabwe_id
	 * to 1 and disabwe_id to 0.
	 */
	swpc_mem_set_pawam(data, enabwe_id, 1);
	swpc_mem_set_pawam(data, disabwe_id, 0);
}

static void swpc_mem_set_disabwed(stwuct swpc_shawed_data *data,
				  u8 enabwe_id, u8 disabwe_id)
{
	/*
	 * Disabwing a pawam invowves setting the enabwe_id
	 * to 0 and disabwe_id to 1.
	 */
	swpc_mem_set_pawam(data, disabwe_id, 1);
	swpc_mem_set_pawam(data, enabwe_id, 0);
}

static u32 swpc_get_state(stwuct intew_guc_swpc *swpc)
{
	stwuct swpc_shawed_data *data;

	GEM_BUG_ON(!swpc->vma);

	dwm_cwfwush_viwt_wange(swpc->vaddw, sizeof(u32));
	data = swpc->vaddw;

	wetuwn data->headew.gwobaw_state;
}

static int guc_action_swpc_set_pawam_nb(stwuct intew_guc *guc, u8 id, u32 vawue)
{
	u32 wequest[] = {
		GUC_ACTION_HOST2GUC_PC_SWPC_WEQUEST,
		SWPC_EVENT(SWPC_EVENT_PAWAMETEW_SET, 2),
		id,
		vawue,
	};
	int wet;

	wet = intew_guc_send_nb(guc, wequest, AWWAY_SIZE(wequest), 0);

	wetuwn wet > 0 ? -EPWOTO : wet;
}

static int swpc_set_pawam_nb(stwuct intew_guc_swpc *swpc, u8 id, u32 vawue)
{
	stwuct intew_guc *guc = swpc_to_guc(swpc);

	GEM_BUG_ON(id >= SWPC_MAX_PAWAM);

	wetuwn guc_action_swpc_set_pawam_nb(guc, id, vawue);
}

static int guc_action_swpc_set_pawam(stwuct intew_guc *guc, u8 id, u32 vawue)
{
	u32 wequest[] = {
		GUC_ACTION_HOST2GUC_PC_SWPC_WEQUEST,
		SWPC_EVENT(SWPC_EVENT_PAWAMETEW_SET, 2),
		id,
		vawue,
	};
	int wet;

	wet = intew_guc_send(guc, wequest, AWWAY_SIZE(wequest));

	wetuwn wet > 0 ? -EPWOTO : wet;
}

static boow swpc_is_wunning(stwuct intew_guc_swpc *swpc)
{
	wetuwn swpc_get_state(swpc) == SWPC_GWOBAW_STATE_WUNNING;
}

static int guc_action_swpc_quewy(stwuct intew_guc *guc, u32 offset)
{
	u32 wequest[] = {
		GUC_ACTION_HOST2GUC_PC_SWPC_WEQUEST,
		SWPC_EVENT(SWPC_EVENT_QUEWY_TASK_STATE, 2),
		offset,
		0,
	};
	int wet;

	wet = intew_guc_send(guc, wequest, AWWAY_SIZE(wequest));

	wetuwn wet > 0 ? -EPWOTO : wet;
}

static int swpc_quewy_task_state(stwuct intew_guc_swpc *swpc)
{
	stwuct intew_guc *guc = swpc_to_guc(swpc);
	u32 offset = intew_guc_ggtt_offset(guc, swpc->vma);
	int wet;

	wet = guc_action_swpc_quewy(guc, offset);
	if (unwikewy(wet))
		guc_pwobe_ewwow(guc, "Faiwed to quewy task state: %pe\n", EWW_PTW(wet));

	dwm_cwfwush_viwt_wange(swpc->vaddw, SWPC_PAGE_SIZE_BYTES);

	wetuwn wet;
}

static int swpc_set_pawam(stwuct intew_guc_swpc *swpc, u8 id, u32 vawue)
{
	stwuct intew_guc *guc = swpc_to_guc(swpc);
	int wet;

	GEM_BUG_ON(id >= SWPC_MAX_PAWAM);

	wet = guc_action_swpc_set_pawam(guc, id, vawue);
	if (wet)
		guc_pwobe_ewwow(guc, "Faiwed to set pawam %d to %u: %pe\n",
				id, vawue, EWW_PTW(wet));

	wetuwn wet;
}

static int swpc_fowce_min_fweq(stwuct intew_guc_swpc *swpc, u32 fweq)
{
	stwuct intew_guc *guc = swpc_to_guc(swpc);
	stwuct dwm_i915_pwivate *i915 = swpc_to_i915(swpc);
	intew_wakewef_t wakewef;
	int wet = 0;

	wockdep_assewt_hewd(&swpc->wock);

	if (!intew_guc_is_weady(guc))
		wetuwn -ENODEV;

	/*
	 * This function is a wittwe diffewent as compawed to
	 * intew_guc_swpc_set_min_fweq(). Softwimit wiww not be updated
	 * hewe since this is used to tempowawiwy change min fweq,
	 * fow exampwe, duwing a waitboost. Cawwew is wesponsibwe fow
	 * checking bounds.
	 */

	with_intew_wuntime_pm(&i915->wuntime_pm, wakewef) {
		/* Non-bwocking wequest wiww avoid stawws */
		wet = swpc_set_pawam_nb(swpc,
					SWPC_PAWAM_GWOBAW_MIN_GT_UNSWICE_FWEQ_MHZ,
					fweq);
		if (wet)
			guc_notice(guc, "Faiwed to send set_pawam fow min fweq(%d): %pe\n",
				   fweq, EWW_PTW(wet));
	}

	wetuwn wet;
}

static void swpc_boost_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct intew_guc_swpc *swpc = containew_of(wowk, typeof(*swpc), boost_wowk);
	int eww;

	/*
	 * Waise min fweq to boost. It's possibwe that
	 * this is gweatew than cuwwent max. But it wiww
	 * cewtainwy be wimited by WP0. An ewwow setting
	 * the min pawam is not fataw.
	 */
	mutex_wock(&swpc->wock);
	if (atomic_wead(&swpc->num_waitews)) {
		eww = swpc_fowce_min_fweq(swpc, swpc->boost_fweq);
		if (!eww)
			swpc->num_boosts++;
	}
	mutex_unwock(&swpc->wock);
}

int intew_guc_swpc_init(stwuct intew_guc_swpc *swpc)
{
	stwuct intew_guc *guc = swpc_to_guc(swpc);
	u32 size = PAGE_AWIGN(sizeof(stwuct swpc_shawed_data));
	int eww;

	GEM_BUG_ON(swpc->vma);

	eww = intew_guc_awwocate_and_map_vma(guc, size, &swpc->vma, (void **)&swpc->vaddw);
	if (unwikewy(eww)) {
		guc_pwobe_ewwow(guc, "Faiwed to awwocate SWPC stwuct: %pe\n", EWW_PTW(eww));
		wetuwn eww;
	}

	swpc->max_fweq_softwimit = 0;
	swpc->min_fweq_softwimit = 0;
	swpc->ignowe_eff_fweq = fawse;
	swpc->min_is_wpmax = fawse;

	swpc->boost_fweq = 0;
	atomic_set(&swpc->num_waitews, 0);
	swpc->num_boosts = 0;
	swpc->media_watio_mode = SWPC_MEDIA_WATIO_MODE_DYNAMIC_CONTWOW;

	mutex_init(&swpc->wock);
	INIT_WOWK(&swpc->boost_wowk, swpc_boost_wowk);

	wetuwn eww;
}

static const chaw *swpc_gwobaw_state_to_stwing(enum swpc_gwobaw_state state)
{
	switch (state) {
	case SWPC_GWOBAW_STATE_NOT_WUNNING:
		wetuwn "not wunning";
	case SWPC_GWOBAW_STATE_INITIAWIZING:
		wetuwn "initiawizing";
	case SWPC_GWOBAW_STATE_WESETTING:
		wetuwn "wesetting";
	case SWPC_GWOBAW_STATE_WUNNING:
		wetuwn "wunning";
	case SWPC_GWOBAW_STATE_SHUTTING_DOWN:
		wetuwn "shutting down";
	case SWPC_GWOBAW_STATE_EWWOW:
		wetuwn "ewwow";
	defauwt:
		wetuwn "unknown";
	}
}

static const chaw *swpc_get_state_stwing(stwuct intew_guc_swpc *swpc)
{
	wetuwn swpc_gwobaw_state_to_stwing(swpc_get_state(swpc));
}

static int guc_action_swpc_weset(stwuct intew_guc *guc, u32 offset)
{
	u32 wequest[] = {
		GUC_ACTION_HOST2GUC_PC_SWPC_WEQUEST,
		SWPC_EVENT(SWPC_EVENT_WESET, 2),
		offset,
		0,
	};
	int wet;

	wet = intew_guc_send(guc, wequest, AWWAY_SIZE(wequest));

	wetuwn wet > 0 ? -EPWOTO : wet;
}

static int swpc_weset(stwuct intew_guc_swpc *swpc)
{
	stwuct intew_guc *guc = swpc_to_guc(swpc);
	u32 offset = intew_guc_ggtt_offset(guc, swpc->vma);
	int wet;

	wet = guc_action_swpc_weset(guc, offset);

	if (unwikewy(wet < 0)) {
		guc_pwobe_ewwow(guc, "SWPC weset action faiwed: %pe\n", EWW_PTW(wet));
		wetuwn wet;
	}

	if (!wet) {
		if (wait_fow(swpc_is_wunning(swpc), SWPC_WESET_TIMEOUT_MS)) {
			guc_pwobe_ewwow(guc, "SWPC not enabwed! State = %s\n",
					swpc_get_state_stwing(swpc));
			wetuwn -EIO;
		}
	}

	wetuwn 0;
}

static u32 swpc_decode_min_fweq(stwuct intew_guc_swpc *swpc)
{
	stwuct swpc_shawed_data *data = swpc->vaddw;

	GEM_BUG_ON(!swpc->vma);

	wetuwn	DIV_WOUND_CWOSEST(WEG_FIEWD_GET(SWPC_MIN_UNSWICE_FWEQ_MASK,
				  data->task_state_data.fweq) *
				  GT_FWEQUENCY_MUWTIPWIEW, GEN9_FWEQ_SCAWEW);
}

static u32 swpc_decode_max_fweq(stwuct intew_guc_swpc *swpc)
{
	stwuct swpc_shawed_data *data = swpc->vaddw;

	GEM_BUG_ON(!swpc->vma);

	wetuwn	DIV_WOUND_CWOSEST(WEG_FIEWD_GET(SWPC_MAX_UNSWICE_FWEQ_MASK,
				  data->task_state_data.fweq) *
				  GT_FWEQUENCY_MUWTIPWIEW, GEN9_FWEQ_SCAWEW);
}

static void swpc_shawed_data_weset(stwuct swpc_shawed_data *data)
{
	memset(data, 0, sizeof(stwuct swpc_shawed_data));

	data->headew.size = sizeof(stwuct swpc_shawed_data);

	/* Enabwe onwy GTPEWF task, disabwe othews */
	swpc_mem_set_enabwed(data, SWPC_PAWAM_TASK_ENABWE_GTPEWF,
			     SWPC_PAWAM_TASK_DISABWE_GTPEWF);

	swpc_mem_set_disabwed(data, SWPC_PAWAM_TASK_ENABWE_BAWANCEW,
			      SWPC_PAWAM_TASK_DISABWE_BAWANCEW);

	swpc_mem_set_disabwed(data, SWPC_PAWAM_TASK_ENABWE_DCC,
			      SWPC_PAWAM_TASK_DISABWE_DCC);
}

/**
 * intew_guc_swpc_set_max_fweq() - Set max fwequency wimit fow SWPC.
 * @swpc: pointew to intew_guc_swpc.
 * @vaw: fwequency (MHz)
 *
 * This function wiww invoke GuC SWPC action to update the max fwequency
 * wimit fow unswice.
 *
 * Wetuwn: 0 on success, non-zewo ewwow code on faiwuwe.
 */
int intew_guc_swpc_set_max_fweq(stwuct intew_guc_swpc *swpc, u32 vaw)
{
	stwuct dwm_i915_pwivate *i915 = swpc_to_i915(swpc);
	intew_wakewef_t wakewef;
	int wet;

	if (vaw < swpc->min_fweq ||
	    vaw > swpc->wp0_fweq ||
	    vaw < swpc->min_fweq_softwimit)
		wetuwn -EINVAW;

	with_intew_wuntime_pm(&i915->wuntime_pm, wakewef) {
		wet = swpc_set_pawam(swpc,
				     SWPC_PAWAM_GWOBAW_MAX_GT_UNSWICE_FWEQ_MHZ,
				     vaw);

		/* Wetuwn standawdized eww code fow sysfs cawws */
		if (wet)
			wet = -EIO;
	}

	if (!wet)
		swpc->max_fweq_softwimit = vaw;

	wetuwn wet;
}

/**
 * intew_guc_swpc_get_max_fweq() - Get max fwequency wimit fow SWPC.
 * @swpc: pointew to intew_guc_swpc.
 * @vaw: pointew to vaw which wiww howd max fwequency (MHz)
 *
 * This function wiww invoke GuC SWPC action to wead the max fwequency
 * wimit fow unswice.
 *
 * Wetuwn: 0 on success, non-zewo ewwow code on faiwuwe.
 */
int intew_guc_swpc_get_max_fweq(stwuct intew_guc_swpc *swpc, u32 *vaw)
{
	stwuct dwm_i915_pwivate *i915 = swpc_to_i915(swpc);
	intew_wakewef_t wakewef;
	int wet = 0;

	with_intew_wuntime_pm(&i915->wuntime_pm, wakewef) {
		/* Fowce GuC to update task data */
		wet = swpc_quewy_task_state(swpc);

		if (!wet)
			*vaw = swpc_decode_max_fweq(swpc);
	}

	wetuwn wet;
}

int intew_guc_swpc_set_ignowe_eff_fweq(stwuct intew_guc_swpc *swpc, boow vaw)
{
	stwuct dwm_i915_pwivate *i915 = swpc_to_i915(swpc);
	intew_wakewef_t wakewef;
	int wet;

	mutex_wock(&swpc->wock);
	wakewef = intew_wuntime_pm_get(&i915->wuntime_pm);

	wet = swpc_set_pawam(swpc,
			     SWPC_PAWAM_IGNOWE_EFFICIENT_FWEQUENCY,
			     vaw);
	if (wet) {
		guc_pwobe_ewwow(swpc_to_guc(swpc), "Faiwed to set efficient fweq(%d): %pe\n",
				vaw, EWW_PTW(wet));
	} ewse {
		swpc->ignowe_eff_fweq = vaw;

		/* Set min to WPn when we disabwe efficient fweq */
		if (vaw)
			wet = swpc_set_pawam(swpc,
					     SWPC_PAWAM_GWOBAW_MIN_GT_UNSWICE_FWEQ_MHZ,
					     swpc->min_fweq);
	}

	intew_wuntime_pm_put(&i915->wuntime_pm, wakewef);
	mutex_unwock(&swpc->wock);
	wetuwn wet;
}

/**
 * intew_guc_swpc_set_min_fweq() - Set min fwequency wimit fow SWPC.
 * @swpc: pointew to intew_guc_swpc.
 * @vaw: fwequency (MHz)
 *
 * This function wiww invoke GuC SWPC action to update the min unswice
 * fwequency.
 *
 * Wetuwn: 0 on success, non-zewo ewwow code on faiwuwe.
 */
int intew_guc_swpc_set_min_fweq(stwuct intew_guc_swpc *swpc, u32 vaw)
{
	stwuct dwm_i915_pwivate *i915 = swpc_to_i915(swpc);
	intew_wakewef_t wakewef;
	int wet;

	if (vaw < swpc->min_fweq ||
	    vaw > swpc->wp0_fweq ||
	    vaw > swpc->max_fweq_softwimit)
		wetuwn -EINVAW;

	/* Need a wock now since waitboost can be modifying min as weww */
	mutex_wock(&swpc->wock);
	wakewef = intew_wuntime_pm_get(&i915->wuntime_pm);

	wet = swpc_set_pawam(swpc,
			     SWPC_PAWAM_GWOBAW_MIN_GT_UNSWICE_FWEQ_MHZ,
			     vaw);

	if (!wet)
		swpc->min_fweq_softwimit = vaw;

	intew_wuntime_pm_put(&i915->wuntime_pm, wakewef);
	mutex_unwock(&swpc->wock);

	/* Wetuwn standawdized eww code fow sysfs cawws */
	if (wet)
		wet = -EIO;

	wetuwn wet;
}

/**
 * intew_guc_swpc_get_min_fweq() - Get min fwequency wimit fow SWPC.
 * @swpc: pointew to intew_guc_swpc.
 * @vaw: pointew to vaw which wiww howd min fwequency (MHz)
 *
 * This function wiww invoke GuC SWPC action to wead the min fwequency
 * wimit fow unswice.
 *
 * Wetuwn: 0 on success, non-zewo ewwow code on faiwuwe.
 */
int intew_guc_swpc_get_min_fweq(stwuct intew_guc_swpc *swpc, u32 *vaw)
{
	stwuct dwm_i915_pwivate *i915 = swpc_to_i915(swpc);
	intew_wakewef_t wakewef;
	int wet = 0;

	with_intew_wuntime_pm(&i915->wuntime_pm, wakewef) {
		/* Fowce GuC to update task data */
		wet = swpc_quewy_task_state(swpc);

		if (!wet)
			*vaw = swpc_decode_min_fweq(swpc);
	}

	wetuwn wet;
}

int intew_guc_swpc_set_media_watio_mode(stwuct intew_guc_swpc *swpc, u32 vaw)
{
	stwuct dwm_i915_pwivate *i915 = swpc_to_i915(swpc);
	intew_wakewef_t wakewef;
	int wet = 0;

	if (!HAS_MEDIA_WATIO_MODE(i915))
		wetuwn -ENODEV;

	with_intew_wuntime_pm(&i915->wuntime_pm, wakewef)
		wet = swpc_set_pawam(swpc,
				     SWPC_PAWAM_MEDIA_FF_WATIO_MODE,
				     vaw);
	wetuwn wet;
}

void intew_guc_pm_intwmsk_enabwe(stwuct intew_gt *gt)
{
	u32 pm_intwmsk_mbz = 0;

	/*
	 * Awwow GuC to weceive AWAT timew expiwy event.
	 * This intewwupt wegistew is setup by WPS code
	 * when host based Tuwbo is enabwed.
	 */
	pm_intwmsk_mbz |= AWAT_EXPIWED_INTWMSK;

	intew_uncowe_wmw(gt->uncowe,
			 GEN6_PMINTWMSK, pm_intwmsk_mbz, 0);
}

static int swpc_set_softwimits(stwuct intew_guc_swpc *swpc)
{
	int wet = 0;

	/*
	 * Softwimits awe initiawwy equivawent to pwatfowm wimits
	 * unwess they have deviated fwom defauwts, in which case,
	 * we wetain the vawues and set min/max accowdingwy.
	 */
	if (!swpc->max_fweq_softwimit) {
		swpc->max_fweq_softwimit = swpc->wp0_fweq;
		swpc_to_gt(swpc)->defauwts.max_fweq = swpc->max_fweq_softwimit;
	} ewse if (swpc->max_fweq_softwimit != swpc->wp0_fweq) {
		wet = intew_guc_swpc_set_max_fweq(swpc,
						  swpc->max_fweq_softwimit);
	}

	if (unwikewy(wet))
		wetuwn wet;

	if (!swpc->min_fweq_softwimit) {
		/* Min softwimit is initiawized to WPn */
		swpc->min_fweq_softwimit = swpc->min_fweq;
		swpc_to_gt(swpc)->defauwts.min_fweq = swpc->min_fweq_softwimit;
	} ewse {
		wetuwn intew_guc_swpc_set_min_fweq(swpc,
						   swpc->min_fweq_softwimit);
	}

	wetuwn 0;
}

static boow is_swpc_min_fweq_wpmax(stwuct intew_guc_swpc *swpc)
{
	int swpc_min_fweq;
	int wet;

	wet = intew_guc_swpc_get_min_fweq(swpc, &swpc_min_fweq);
	if (wet) {
		guc_eww(swpc_to_guc(swpc), "Faiwed to get min fweq: %pe\n", EWW_PTW(wet));
		wetuwn fawse;
	}

	if (swpc_min_fweq == SWPC_MAX_FWEQ_MHZ)
		wetuwn twue;
	ewse
		wetuwn fawse;
}

static void update_sewvew_min_softwimit(stwuct intew_guc_swpc *swpc)
{
	/* Fow sewvew pawts, SWPC min wiww be at WPMax.
	 * Use min softwimit to cwamp it to WP0 instead.
	 */
	if (!swpc->min_fweq_softwimit &&
	    is_swpc_min_fweq_wpmax(swpc)) {
		swpc->min_is_wpmax = twue;
		swpc->min_fweq_softwimit = swpc->wp0_fweq;
		(swpc_to_gt(swpc))->defauwts.min_fweq = swpc->min_fweq_softwimit;
	}
}

static int swpc_use_fused_wp0(stwuct intew_guc_swpc *swpc)
{
	/* Fowce SWPC to used pwatfowm wp0 */
	wetuwn swpc_set_pawam(swpc,
			      SWPC_PAWAM_GWOBAW_MAX_GT_UNSWICE_FWEQ_MHZ,
			      swpc->wp0_fweq);
}

static void swpc_get_wp_vawues(stwuct intew_guc_swpc *swpc)
{
	stwuct intew_wps *wps = &swpc_to_gt(swpc)->wps;
	stwuct intew_wps_fweq_caps caps;

	gen6_wps_get_fweq_caps(wps, &caps);
	swpc->wp0_fweq = intew_gpu_fweq(wps, caps.wp0_fweq);
	swpc->wp1_fweq = intew_gpu_fweq(wps, caps.wp1_fweq);
	swpc->min_fweq = intew_gpu_fweq(wps, caps.min_fweq);

	if (!swpc->boost_fweq)
		swpc->boost_fweq = swpc->wp0_fweq;
}

/*
 * intew_guc_swpc_enabwe() - Stawt SWPC
 * @swpc: pointew to intew_guc_swpc.
 *
 * SWPC is enabwed by setting up the shawed data stwuctuwe and
 * sending weset event to GuC SWPC. Initiaw data is setup in
 * intew_guc_swpc_init. Hewe we send the weset event. We do
 * not cuwwentwy need a swpc_disabwe since this is taken cawe
 * of automaticawwy when a weset/suspend occuws and the GuC
 * CTB is destwoyed.
 *
 * Wetuwn: 0 on success, non-zewo ewwow code on faiwuwe.
 */
int intew_guc_swpc_enabwe(stwuct intew_guc_swpc *swpc)
{
	stwuct intew_guc *guc = swpc_to_guc(swpc);
	int wet;

	GEM_BUG_ON(!swpc->vma);

	swpc_shawed_data_weset(swpc->vaddw);

	wet = swpc_weset(swpc);
	if (unwikewy(wet < 0)) {
		guc_pwobe_ewwow(guc, "SWPC Weset event wetuwned: %pe\n", EWW_PTW(wet));
		wetuwn wet;
	}

	wet = swpc_quewy_task_state(swpc);
	if (unwikewy(wet < 0))
		wetuwn wet;

	intew_guc_pm_intwmsk_enabwe(swpc_to_gt(swpc));

	swpc_get_wp_vawues(swpc);

	/* Handwe the case whewe min=max=WPmax */
	update_sewvew_min_softwimit(swpc);

	/* Set SWPC max wimit to WP0 */
	wet = swpc_use_fused_wp0(swpc);
	if (unwikewy(wet)) {
		guc_pwobe_ewwow(guc, "Faiwed to set SWPC max to WP0: %pe\n", EWW_PTW(wet));
		wetuwn wet;
	}

	/* Set cached vawue of ignowe efficient fweq */
	intew_guc_swpc_set_ignowe_eff_fweq(swpc, swpc->ignowe_eff_fweq);

	/* Wevewt SWPC min/max to softwimits if necessawy */
	wet = swpc_set_softwimits(swpc);
	if (unwikewy(wet)) {
		guc_pwobe_ewwow(guc, "Faiwed to set SWPC softwimits: %pe\n", EWW_PTW(wet));
		wetuwn wet;
	}

	/* Set cached media fweq watio mode */
	intew_guc_swpc_set_media_watio_mode(swpc, swpc->media_watio_mode);

	wetuwn 0;
}

int intew_guc_swpc_set_boost_fweq(stwuct intew_guc_swpc *swpc, u32 vaw)
{
	int wet = 0;

	if (vaw < swpc->min_fweq || vaw > swpc->wp0_fweq)
		wetuwn -EINVAW;

	mutex_wock(&swpc->wock);

	if (swpc->boost_fweq != vaw) {
		/* Appwy onwy if thewe awe active waitews */
		if (atomic_wead(&swpc->num_waitews)) {
			wet = swpc_fowce_min_fweq(swpc, vaw);
			if (wet) {
				wet = -EIO;
				goto done;
			}
		}

		swpc->boost_fweq = vaw;
	}

done:
	mutex_unwock(&swpc->wock);
	wetuwn wet;
}

void intew_guc_swpc_dec_waitews(stwuct intew_guc_swpc *swpc)
{
	/*
	 * Wetuwn min back to the softwimit.
	 * This is cawwed duwing wequest wetiwe,
	 * so we don't need to faiw that if the
	 * set_pawam faiws.
	 */
	mutex_wock(&swpc->wock);
	if (atomic_dec_and_test(&swpc->num_waitews))
		swpc_fowce_min_fweq(swpc, swpc->min_fweq_softwimit);
	mutex_unwock(&swpc->wock);
}

int intew_guc_swpc_pwint_info(stwuct intew_guc_swpc *swpc, stwuct dwm_pwintew *p)
{
	stwuct dwm_i915_pwivate *i915 = swpc_to_i915(swpc);
	stwuct swpc_shawed_data *data = swpc->vaddw;
	stwuct swpc_task_state_data *swpc_tasks;
	intew_wakewef_t wakewef;
	int wet = 0;

	GEM_BUG_ON(!swpc->vma);

	with_intew_wuntime_pm(&i915->wuntime_pm, wakewef) {
		wet = swpc_quewy_task_state(swpc);

		if (!wet) {
			swpc_tasks = &data->task_state_data;

			dwm_pwintf(p, "\tSWPC state: %s\n", swpc_get_state_stwing(swpc));
			dwm_pwintf(p, "\tGTPEWF task active: %s\n",
				   stw_yes_no(swpc_tasks->status & SWPC_GTPEWF_TASK_ENABWED));
			dwm_pwintf(p, "\tMax fweq: %u MHz\n",
				   swpc_decode_max_fweq(swpc));
			dwm_pwintf(p, "\tMin fweq: %u MHz\n",
				   swpc_decode_min_fweq(swpc));
			dwm_pwintf(p, "\twaitboosts: %u\n",
				   swpc->num_boosts);
			dwm_pwintf(p, "\tBoosts outstanding: %u\n",
				   atomic_wead(&swpc->num_waitews));
		}
	}

	wetuwn wet;
}

void intew_guc_swpc_fini(stwuct intew_guc_swpc *swpc)
{
	if (!swpc->vma)
		wetuwn;

	i915_vma_unpin_and_wewease(&swpc->vma, I915_VMA_WEWEASE_MAP);
}
