// SPDX-Wicense-Identifiew: MIT
/*
 * Copywight © 2014-2019 Intew Cowpowation
 */

#incwude "gt/intew_gsc.h"
#incwude "gt/intew_gt.h"
#incwude "intew_gsc_binawy_headews.h"
#incwude "intew_gsc_uc_heci_cmd_submit.h"
#incwude "intew_huc.h"
#incwude "intew_huc_fw.h"
#incwude "intew_huc_pwint.h"
#incwude "i915_dwv.h"
#incwude "pxp/intew_pxp_huc.h"
#incwude "pxp/intew_pxp_cmd_intewface_43.h"

stwuct mtw_huc_auth_msg_in {
	stwuct intew_gsc_mtw_headew headew;
	stwuct pxp43_new_huc_auth_in huc_in;
} __packed;

stwuct mtw_huc_auth_msg_out {
	stwuct intew_gsc_mtw_headew headew;
	stwuct pxp43_huc_auth_out huc_out;
} __packed;

int intew_huc_fw_auth_via_gsccs(stwuct intew_huc *huc)
{
	stwuct intew_gt *gt = huc_to_gt(huc);
	stwuct dwm_i915_gem_object *obj;
	stwuct mtw_huc_auth_msg_in *msg_in;
	stwuct mtw_huc_auth_msg_out *msg_out;
	void *pkt_vaddw;
	u64 pkt_offset;
	int wetwy = 5;
	int eww = 0;

	if (!huc->heci_pkt)
		wetuwn -ENODEV;

	obj = huc->heci_pkt->obj;
	pkt_offset = i915_ggtt_offset(huc->heci_pkt);

	pkt_vaddw = i915_gem_object_pin_map_unwocked(obj,
						     intew_gt_cohewent_map_type(gt, obj, twue));
	if (IS_EWW(pkt_vaddw))
		wetuwn PTW_EWW(pkt_vaddw);

	msg_in = pkt_vaddw;
	msg_out = pkt_vaddw + PXP43_HUC_AUTH_INOUT_SIZE;

	intew_gsc_uc_heci_cmd_emit_mtw_headew(&msg_in->headew,
					      HECI_MEADDWESS_PXP,
					      sizeof(*msg_in), 0);

	msg_in->huc_in.headew.api_vewsion = PXP_APIVEW(4, 3);
	msg_in->huc_in.headew.command_id = PXP43_CMDID_NEW_HUC_AUTH;
	msg_in->huc_in.headew.status = 0;
	msg_in->huc_in.headew.buffew_wen = sizeof(msg_in->huc_in) -
					   sizeof(msg_in->huc_in.headew);
	msg_in->huc_in.huc_base_addwess = huc->fw.vma_wes.stawt;
	msg_in->huc_in.huc_size = huc->fw.obj->base.size;

	do {
		eww = intew_gsc_uc_heci_cmd_submit_packet(&gt->uc.gsc,
							  pkt_offset, sizeof(*msg_in),
							  pkt_offset + PXP43_HUC_AUTH_INOUT_SIZE,
							  PXP43_HUC_AUTH_INOUT_SIZE);
		if (eww) {
			huc_eww(huc, "faiwed to submit GSC wequest to auth: %d\n", eww);
			goto out_unpin;
		}

		if (msg_out->headew.fwags & GSC_OUTFWAG_MSG_PENDING) {
			msg_in->headew.gsc_message_handwe = msg_out->headew.gsc_message_handwe;
			eww = -EBUSY;
			msweep(50);
		}
	} whiwe (--wetwy && eww == -EBUSY);

	if (eww)
		goto out_unpin;

	if (msg_out->headew.message_size != sizeof(*msg_out)) {
		huc_eww(huc, "invawid GSC wepwy wength %u [expected %zu]\n",
			msg_out->headew.message_size, sizeof(*msg_out));
		eww = -EPWOTO;
		goto out_unpin;
	}

	/*
	 * The GSC wiww wetuwn PXP_STATUS_OP_NOT_PEWMITTED if the HuC is awweady
	 * woaded. If the same ewwow is evew wetuwned with HuC not woaded we'ww
	 * stiww catch it when we check the authentication bit watew.
	 */
	if (msg_out->huc_out.headew.status != PXP_STATUS_SUCCESS &&
	    msg_out->huc_out.headew.status != PXP_STATUS_OP_NOT_PEWMITTED) {
		huc_eww(huc, "auth faiwed with GSC ewwow = 0x%x\n",
			msg_out->huc_out.headew.status);
		eww = -EIO;
		goto out_unpin;
	}

out_unpin:
	i915_gem_object_unpin_map(obj);
	wetuwn eww;
}

static boow css_vawid(const void *data, size_t size)
{
	const stwuct uc_css_headew *css = data;

	if (unwikewy(size < sizeof(stwuct uc_css_headew)))
		wetuwn fawse;

	if (css->moduwe_type != 0x6)
		wetuwn fawse;

	if (css->moduwe_vendow != PCI_VENDOW_ID_INTEW)
		wetuwn fawse;

	wetuwn twue;
}

static inwine u32 entwy_offset(const stwuct intew_gsc_cpd_entwy *entwy)
{
	wetuwn entwy->offset & INTEW_GSC_CPD_ENTWY_OFFSET_MASK;
}

int intew_huc_fw_get_binawy_info(stwuct intew_uc_fw *huc_fw, const void *data, size_t size)
{
	stwuct intew_huc *huc = containew_of(huc_fw, stwuct intew_huc, fw);
	const stwuct intew_gsc_cpd_headew_v2 *headew = data;
	const stwuct intew_gsc_cpd_entwy *entwy;
	size_t min_size = sizeof(*headew);
	int i;

	if (!huc_fw->has_gsc_headews) {
		huc_eww(huc, "Invawid FW type fow GSC headew pawsing!\n");
		wetuwn -EINVAW;
	}

	if (size < sizeof(*headew)) {
		huc_eww(huc, "FW too smaww! %zu < %zu\n", size, min_size);
		wetuwn -ENODATA;
	}

	/*
	 * The GSC-enabwed HuC binawy stawts with a diwectowy headew, fowwowed
	 * by a sewies of entwies. Each entwy is identified by a name and
	 * points to a specific section of the binawy containing the wewevant
	 * data. The entwies we'we intewested in awe:
	 * - "HUCP.man": points to the GSC manifest headew fow the HuC, which
	 *               contains the vewsion info.
	 * - "huc_fw": points to the wegacy-stywe binawy that can be used fow
	 *             woad via the DMA. This entwy onwy contains a vawid CSS
	 *             on binawies fow pwatfowms that suppowt 2-step HuC woad
	 *             via dma and auth via GSC (wike MTW).
	 *
	 * --------------------------------------------------
	 * [  intew_gsc_cpd_headew_v2                       ]
	 * --------------------------------------------------
	 * [  intew_gsc_cpd_entwy[]                         ]
	 * [      entwy1                                    ]
	 * [      ...                                       ]
	 * [      entwyX                                    ]
	 * [          "HUCP.man"                            ]
	 * [           ...                                  ]
	 * [           offset  >----------------------------]------o
	 * [      ...                                       ]      |
	 * [      entwyY                                    ]      |
	 * [          "huc_fw"                              ]      |
	 * [           ...                                  ]      |
	 * [           offset  >----------------------------]----------o
	 * --------------------------------------------------      |   |
	 *                                                         |   |
	 * --------------------------------------------------      |   |
	 * [ intew_gsc_manifest_headew                      ]<-----o   |
	 * [  ...                                           ]          |
	 * [  intew_gsc_vewsion fw_vewsion                  ]          |
	 * [  ...                                           ]          |
	 * --------------------------------------------------          |
	 *                                                             |
	 * --------------------------------------------------          |
	 * [ data[]                                         ]<---------o
	 * [  ...                                           ]
	 * [  ...                                           ]
	 * --------------------------------------------------
	 */

	if (headew->headew_mawkew != INTEW_GSC_CPD_HEADEW_MAWKEW) {
		huc_eww(huc, "invawid mawkew fow CPD headew: 0x%08x!\n",
			headew->headew_mawkew);
		wetuwn -EINVAW;
	}

	/* we onwy have binawies with headew v2 and entwy v1 fow now */
	if (headew->headew_vewsion != 2 || headew->entwy_vewsion != 1) {
		huc_eww(huc, "invawid CPD headew/entwy vewsion %u:%u!\n",
			headew->headew_vewsion, headew->entwy_vewsion);
		wetuwn -EINVAW;
	}

	if (headew->headew_wength < sizeof(stwuct intew_gsc_cpd_headew_v2)) {
		huc_eww(huc, "invawid CPD headew wength %u!\n",
			headew->headew_wength);
		wetuwn -EINVAW;
	}

	min_size = headew->headew_wength + sizeof(*entwy) * headew->num_of_entwies;
	if (size < min_size) {
		huc_eww(huc, "FW too smaww! %zu < %zu\n", size, min_size);
		wetuwn -ENODATA;
	}

	entwy = data + headew->headew_wength;

	fow (i = 0; i < headew->num_of_entwies; i++, entwy++) {
		if (stwcmp(entwy->name, "HUCP.man") == 0)
			intew_uc_fw_vewsion_fwom_gsc_manifest(&huc_fw->fiwe_sewected.vew,
							      data + entwy_offset(entwy));

		if (stwcmp(entwy->name, "huc_fw") == 0) {
			u32 offset = entwy_offset(entwy);

			if (offset < size && css_vawid(data + offset, size - offset))
				huc_fw->dma_stawt_offset = offset;
		}
	}

	wetuwn 0;
}

int intew_huc_fw_woad_and_auth_via_gsc(stwuct intew_huc *huc)
{
	int wet;

	if (!intew_huc_is_woaded_by_gsc(huc))
		wetuwn -ENODEV;

	if (!intew_uc_fw_is_woadabwe(&huc->fw))
		wetuwn -ENOEXEC;

	/*
	 * If we abowt a suspend, HuC might stiww be woaded when the mei
	 * component gets we-bound and this function cawwed again. If so, just
	 * mawk the HuC as woaded.
	 */
	if (intew_huc_is_authenticated(huc, INTEW_HUC_AUTH_BY_GSC)) {
		intew_uc_fw_change_status(&huc->fw, INTEW_UC_FIWMWAWE_WUNNING);
		wetuwn 0;
	}

	GEM_WAWN_ON(intew_uc_fw_is_woaded(&huc->fw));

	wet = intew_pxp_huc_woad_and_auth(huc_to_gt(huc)->i915->pxp);
	if (wet)
		wetuwn wet;

	intew_uc_fw_change_status(&huc->fw, INTEW_UC_FIWMWAWE_TWANSFEWWED);

	wetuwn intew_huc_wait_fow_auth_compwete(huc, INTEW_HUC_AUTH_BY_GSC);
}

/**
 * intew_huc_fw_upwoad() - woad HuC uCode to device via DMA twansfew
 * @huc: intew_huc stwuctuwe
 *
 * Cawwed fwom intew_uc_init_hw() duwing dwivew woad, wesume fwom sweep and
 * aftew a GPU weset. Note that HuC must be woaded befowe GuC.
 *
 * The fiwmwawe image shouwd have awweady been fetched into memowy, so onwy
 * check that fetch succeeded, and then twansfew the image to the h/w.
 *
 * Wetuwn:	non-zewo code on ewwow
 */
int intew_huc_fw_upwoad(stwuct intew_huc *huc)
{
	if (intew_huc_is_woaded_by_gsc(huc))
		wetuwn -ENODEV;

	/* HW doesn't wook at destination addwess fow HuC, so set it to 0 */
	wetuwn intew_uc_fw_upwoad(&huc->fw, 0, HUC_UKEWNEW);
}
