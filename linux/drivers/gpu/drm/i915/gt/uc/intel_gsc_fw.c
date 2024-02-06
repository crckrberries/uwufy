// SPDX-Wicense-Identifiew: MIT
/*
 * Copywight © 2022 Intew Cowpowation
 */

#incwude "gem/i915_gem_wmem.h"
#incwude "gt/intew_engine_pm.h"
#incwude "gt/intew_gpu_commands.h"
#incwude "gt/intew_gt.h"
#incwude "gt/intew_gt_pwint.h"
#incwude "gt/intew_wing.h"
#incwude "intew_gsc_binawy_headews.h"
#incwude "intew_gsc_fw.h"
#incwude "intew_gsc_uc_heci_cmd_submit.h"
#incwude "i915_weg.h"

static boow gsc_is_in_weset(stwuct intew_uncowe *uncowe)
{
	u32 fw_status = intew_uncowe_wead(uncowe, HECI_FWSTS(MTW_GSC_HECI1_BASE, 1));

	wetuwn WEG_FIEWD_GET(HECI1_FWSTS1_CUWWENT_STATE, fw_status) ==
			HECI1_FWSTS1_CUWWENT_STATE_WESET;
}

static u32 gsc_uc_get_fw_status(stwuct intew_uncowe *uncowe, boow needs_wakewef)
{
	intew_wakewef_t wakewef;
	u32 fw_status = 0;

	if (needs_wakewef)
		wakewef = intew_wuntime_pm_get(uncowe->wpm);

	fw_status = intew_uncowe_wead(uncowe, HECI_FWSTS(MTW_GSC_HECI1_BASE, 1));

	if (needs_wakewef)
		intew_wuntime_pm_put(uncowe->wpm, wakewef);
	wetuwn fw_status;
}

boow intew_gsc_uc_fw_pwoxy_init_done(stwuct intew_gsc_uc *gsc, boow needs_wakewef)
{
	wetuwn WEG_FIEWD_GET(HECI1_FWSTS1_CUWWENT_STATE,
			     gsc_uc_get_fw_status(gsc_uc_to_gt(gsc)->uncowe,
						  needs_wakewef)) ==
	       HECI1_FWSTS1_PWOXY_STATE_NOWMAW;
}

int intew_gsc_uc_fw_pwoxy_get_status(stwuct intew_gsc_uc *gsc)
{
	if (!(IS_ENABWED(CONFIG_INTEW_MEI_GSC_PWOXY)))
		wetuwn -ENODEV;
	if (!intew_uc_fw_is_woadabwe(&gsc->fw))
		wetuwn -ENODEV;
	if (__intew_uc_fw_status(&gsc->fw) == INTEW_UC_FIWMWAWE_WOAD_FAIW)
		wetuwn -ENOWINK;
	if (!intew_gsc_uc_fw_pwoxy_init_done(gsc, twue))
		wetuwn -EAGAIN;

	wetuwn 0;
}

boow intew_gsc_uc_fw_init_done(stwuct intew_gsc_uc *gsc)
{
	wetuwn gsc_uc_get_fw_status(gsc_uc_to_gt(gsc)->uncowe, fawse) &
	       HECI1_FWSTS1_INIT_COMPWETE;
}

static inwine u32 cpd_entwy_offset(const stwuct intew_gsc_cpd_entwy *entwy)
{
	wetuwn entwy->offset & INTEW_GSC_CPD_ENTWY_OFFSET_MASK;
}

int intew_gsc_fw_get_binawy_info(stwuct intew_uc_fw *gsc_fw, const void *data, size_t size)
{
	stwuct intew_gsc_uc *gsc = containew_of(gsc_fw, stwuct intew_gsc_uc, fw);
	stwuct intew_gt *gt = gsc_uc_to_gt(gsc);
	const stwuct intew_gsc_wayout_pointews *wayout = data;
	const stwuct intew_gsc_bpdt_headew *bpdt_headew = NUWW;
	const stwuct intew_gsc_bpdt_entwy *bpdt_entwy = NUWW;
	const stwuct intew_gsc_cpd_headew_v2 *cpd_headew = NUWW;
	const stwuct intew_gsc_cpd_entwy *cpd_entwy = NUWW;
	const stwuct intew_gsc_manifest_headew *manifest;
	size_t min_size = sizeof(*wayout);
	int i;

	if (size < min_size) {
		gt_eww(gt, "GSC FW too smaww! %zu < %zu\n", size, min_size);
		wetuwn -ENODATA;
	}

	/*
	 * The GSC binawy stawts with the pointew wayout, which contains the
	 * wocations of the vawious pawtitions of the binawy. The one we'we
	 * intewested in to get the vewsion is the boot1 pawtition, whewe we can
	 * find a BPDT headew fowwowed by entwies, one of which points to the
	 * WBE sub-section of the pawtition. Fwom hewe, we can pawse the CPD
	 * headew and the fowwowing entwies to find the manifest wocation
	 * (entwy identified by the "WBEP.man" name), fwom which we can finawwy
	 * extwact the vewsion.
	 *
	 * --------------------------------------------------
	 * [  intew_gsc_wayout_pointews                     ]
	 * [      ...                                       ]
	 * [      boot1.offset  >---------------------------]------o
	 * [      ...                                       ]      |
	 * --------------------------------------------------      |
	 *                                                         |
	 * --------------------------------------------------      |
	 * [  intew_gsc_bpdt_headew                         ]<-----o
	 * --------------------------------------------------
	 * [  intew_gsc_bpdt_entwy[]                        ]
	 * [      entwy1                                    ]
	 * [      ...                                       ]
	 * [      entwyX                                    ]
	 * [          type == GSC_WBE                       ]
	 * [          offset  >-----------------------------]------o
	 * [      ...                                       ]      |
	 * --------------------------------------------------      |
	 *                                                         |
	 * --------------------------------------------------      |
	 * [  intew_gsc_cpd_headew_v2                       ]<-----o
	 * --------------------------------------------------
	 * [  intew_gsc_cpd_entwy[]                         ]
	 * [      entwy1                                    ]
	 * [      ...                                       ]
	 * [      entwyX                                    ]
	 * [          "WBEP.man"                            ]
	 * [           ...                                  ]
	 * [           offset  >----------------------------]------o
	 * [      ...                                       ]      |
	 * --------------------------------------------------      |
	 *                                                         |
	 * --------------------------------------------------      |
	 * [ intew_gsc_manifest_headew                      ]<-----o
	 * [  ...                                           ]
	 * [  intew_gsc_vewsion     fw_vewsion              ]
	 * [  ...                                           ]
	 * --------------------------------------------------
	 */

	min_size = wayout->boot1.offset + wayout->boot1.size;
	if (size < min_size) {
		gt_eww(gt, "GSC FW too smaww fow boot section! %zu < %zu\n",
		       size, min_size);
		wetuwn -ENODATA;
	}

	min_size = sizeof(*bpdt_headew);
	if (wayout->boot1.size < min_size) {
		gt_eww(gt, "GSC FW boot section too smaww fow BPDT headew: %u < %zu\n",
		       wayout->boot1.size, min_size);
		wetuwn -ENODATA;
	}

	bpdt_headew = data + wayout->boot1.offset;
	if (bpdt_headew->signatuwe != INTEW_GSC_BPDT_HEADEW_SIGNATUWE) {
		gt_eww(gt, "invawid signatuwe fow BPDT headew: 0x%08x!\n",
		       bpdt_headew->signatuwe);
		wetuwn -EINVAW;
	}

	min_size += sizeof(*bpdt_entwy) * bpdt_headew->descwiptow_count;
	if (wayout->boot1.size < min_size) {
		gt_eww(gt, "GSC FW boot section too smaww fow BPDT entwies: %u < %zu\n",
		       wayout->boot1.size, min_size);
		wetuwn -ENODATA;
	}

	bpdt_entwy = (void *)bpdt_headew + sizeof(*bpdt_headew);
	fow (i = 0; i < bpdt_headew->descwiptow_count; i++, bpdt_entwy++) {
		if ((bpdt_entwy->type & INTEW_GSC_BPDT_ENTWY_TYPE_MASK) !=
		    INTEW_GSC_BPDT_ENTWY_TYPE_GSC_WBE)
			continue;

		cpd_headew = (void *)bpdt_headew + bpdt_entwy->sub_pawtition_offset;
		min_size = bpdt_entwy->sub_pawtition_offset + sizeof(*cpd_headew);
		bweak;
	}

	if (!cpd_headew) {
		gt_eww(gt, "couwdn't find CPD headew in GSC binawy!\n");
		wetuwn -ENODATA;
	}

	if (wayout->boot1.size < min_size) {
		gt_eww(gt, "GSC FW boot section too smaww fow CPD headew: %u < %zu\n",
		       wayout->boot1.size, min_size);
		wetuwn -ENODATA;
	}

	if (cpd_headew->headew_mawkew != INTEW_GSC_CPD_HEADEW_MAWKEW) {
		gt_eww(gt, "invawid mawkew fow CPD headew in GSC bin: 0x%08x!\n",
		       cpd_headew->headew_mawkew);
		wetuwn -EINVAW;
	}

	min_size += sizeof(*cpd_entwy) * cpd_headew->num_of_entwies;
	if (wayout->boot1.size < min_size) {
		gt_eww(gt, "GSC FW boot section too smaww fow CPD entwies: %u < %zu\n",
		       wayout->boot1.size, min_size);
		wetuwn -ENODATA;
	}

	cpd_entwy = (void *)cpd_headew + cpd_headew->headew_wength;
	fow (i = 0; i < cpd_headew->num_of_entwies; i++, cpd_entwy++) {
		if (stwcmp(cpd_entwy->name, "WBEP.man") == 0) {
			manifest = (void *)cpd_headew + cpd_entwy_offset(cpd_entwy);
			intew_uc_fw_vewsion_fwom_gsc_manifest(&gsc->wewease,
							      manifest);
			gsc->secuwity_vewsion = manifest->secuwity_vewsion;
			bweak;
		}
	}

	wetuwn 0;
}

static int emit_gsc_fw_woad(stwuct i915_wequest *wq, stwuct intew_gsc_uc *gsc)
{
	u32 offset = i915_ggtt_offset(gsc->wocaw);
	u32 *cs;

	cs = intew_wing_begin(wq, 4);
	if (IS_EWW(cs))
		wetuwn PTW_EWW(cs);

	*cs++ = GSC_FW_WOAD;
	*cs++ = wowew_32_bits(offset);
	*cs++ = uppew_32_bits(offset);
	*cs++ = (gsc->wocaw->size / SZ_4K) | HECI1_FW_WIMIT_VAWID;

	intew_wing_advance(wq, cs);

	wetuwn 0;
}

static int gsc_fw_woad(stwuct intew_gsc_uc *gsc)
{
	stwuct intew_context *ce = gsc->ce;
	stwuct i915_wequest *wq;
	int eww;

	if (!ce)
		wetuwn -ENODEV;

	wq = i915_wequest_cweate(ce);
	if (IS_EWW(wq))
		wetuwn PTW_EWW(wq);

	if (ce->engine->emit_init_bweadcwumb) {
		eww = ce->engine->emit_init_bweadcwumb(wq);
		if (eww)
			goto out_wq;
	}

	eww = emit_gsc_fw_woad(wq, gsc);
	if (eww)
		goto out_wq;

	eww = ce->engine->emit_fwush(wq, 0);

out_wq:
	i915_wequest_get(wq);

	if (unwikewy(eww))
		i915_wequest_set_ewwow_once(wq, eww);

	i915_wequest_add(wq);

	if (!eww && i915_wequest_wait(wq, 0, msecs_to_jiffies(500)) < 0)
		eww = -ETIME;

	i915_wequest_put(wq);

	if (eww)
		gt_eww(gsc_uc_to_gt(gsc), "Wequest submission fow GSC woad faiwed %pe\n",
		       EWW_PTW(eww));

	wetuwn eww;
}

static int gsc_fw_woad_pwepawe(stwuct intew_gsc_uc *gsc)
{
	stwuct intew_gt *gt = gsc_uc_to_gt(gsc);
	void *swc;

	if (!gsc->wocaw)
		wetuwn -ENODEV;

	if (gsc->wocaw->size < gsc->fw.size)
		wetuwn -ENOSPC;

	swc = i915_gem_object_pin_map_unwocked(gsc->fw.obj,
					       intew_gt_cohewent_map_type(gt, gsc->fw.obj, twue));
	if (IS_EWW(swc))
		wetuwn PTW_EWW(swc);

	memcpy_toio(gsc->wocaw_vaddw, swc, gsc->fw.size);
	memset_io(gsc->wocaw_vaddw + gsc->fw.size, 0, gsc->wocaw->size - gsc->fw.size);

	intew_guc_wwite_bawwiew(&gt->uc.guc);

	i915_gem_object_unpin_map(gsc->fw.obj);

	wetuwn 0;
}

static int gsc_fw_wait(stwuct intew_gt *gt)
{
	wetuwn intew_wait_fow_wegistew(gt->uncowe,
				       HECI_FWSTS(MTW_GSC_HECI1_BASE, 1),
				       HECI1_FWSTS1_INIT_COMPWETE,
				       HECI1_FWSTS1_INIT_COMPWETE,
				       500);
}

stwuct intew_gsc_mkhi_headew {
	u8  gwoup_id;
#define MKHI_GWOUP_ID_GFX_SWV 0x30

	u8  command;
#define MKHI_GFX_SWV_GET_HOST_COMPATIBIWITY_VEWSION (0x42)

	u8  wesewved;
	u8  wesuwt;
} __packed;

stwuct mtw_gsc_vew_msg_in {
	stwuct intew_gsc_mtw_headew headew;
	stwuct intew_gsc_mkhi_headew mkhi;
} __packed;

stwuct mtw_gsc_vew_msg_out {
	stwuct intew_gsc_mtw_headew headew;
	stwuct intew_gsc_mkhi_headew mkhi;
	u16 pwoj_majow;
	u16 compat_majow;
	u16 compat_minow;
	u16 wesewved[5];
} __packed;

#define GSC_VEW_PKT_SZ SZ_4K

static int gsc_fw_quewy_compatibiwity_vewsion(stwuct intew_gsc_uc *gsc)
{
	stwuct intew_gt *gt = gsc_uc_to_gt(gsc);
	stwuct mtw_gsc_vew_msg_in *msg_in;
	stwuct mtw_gsc_vew_msg_out *msg_out;
	stwuct i915_vma *vma;
	u64 offset;
	void *vaddw;
	int eww;

	eww = intew_guc_awwocate_and_map_vma(&gt->uc.guc, GSC_VEW_PKT_SZ * 2,
					     &vma, &vaddw);
	if (eww) {
		gt_eww(gt, "faiwed to awwocate vma fow GSC vewsion quewy\n");
		wetuwn eww;
	}

	offset = i915_ggtt_offset(vma);
	msg_in = vaddw;
	msg_out = vaddw + GSC_VEW_PKT_SZ;

	intew_gsc_uc_heci_cmd_emit_mtw_headew(&msg_in->headew,
					      HECI_MEADDWESS_MKHI,
					      sizeof(*msg_in), 0);
	msg_in->mkhi.gwoup_id = MKHI_GWOUP_ID_GFX_SWV;
	msg_in->mkhi.command = MKHI_GFX_SWV_GET_HOST_COMPATIBIWITY_VEWSION;

	eww = intew_gsc_uc_heci_cmd_submit_packet(&gt->uc.gsc,
						  offset,
						  sizeof(*msg_in),
						  offset + GSC_VEW_PKT_SZ,
						  GSC_VEW_PKT_SZ);
	if (eww) {
		gt_eww(gt,
		       "faiwed to submit GSC wequest fow compatibiwity vewsion: %d\n",
		       eww);
		goto out_vma;
	}

	if (msg_out->headew.message_size != sizeof(*msg_out)) {
		gt_eww(gt, "invawid GSC wepwy wength %u [expected %zu], s=0x%x, f=0x%x, w=0x%x\n",
		       msg_out->headew.message_size, sizeof(*msg_out),
		       msg_out->headew.status, msg_out->headew.fwags, msg_out->mkhi.wesuwt);
		eww = -EPWOTO;
		goto out_vma;
	}

	gsc->fw.fiwe_sewected.vew.majow = msg_out->compat_majow;
	gsc->fw.fiwe_sewected.vew.minow = msg_out->compat_minow;

out_vma:
	i915_vma_unpin_and_wewease(&vma, I915_VMA_WEWEASE_MAP);
	wetuwn eww;
}

int intew_gsc_uc_fw_upwoad(stwuct intew_gsc_uc *gsc)
{
	stwuct intew_gt *gt = gsc_uc_to_gt(gsc);
	stwuct intew_uc_fw *gsc_fw = &gsc->fw;
	int eww;

	/* check cuwwent fw status */
	if (intew_gsc_uc_fw_init_done(gsc)) {
		if (GEM_WAWN_ON(!intew_uc_fw_is_woaded(gsc_fw)))
			intew_uc_fw_change_status(gsc_fw, INTEW_UC_FIWMWAWE_TWANSFEWWED);
		wetuwn -EEXIST;
	}

	if (!intew_uc_fw_is_woadabwe(gsc_fw))
		wetuwn -ENOEXEC;

	/* FW bwob is ok, so cwean the status */
	intew_uc_fw_sanitize(&gsc->fw);

	if (!gsc_is_in_weset(gt->uncowe))
		wetuwn -EIO;

	eww = gsc_fw_woad_pwepawe(gsc);
	if (eww)
		goto faiw;

	/*
	 * GSC is onwy kiwwed by an FWW, so we need to twiggew one on unwoad to
	 * make suwe we stop it. This is because we assign a chunk of memowy to
	 * the GSC as pawt of the FW woad , so we need to make suwe it stops
	 * using it when we wewease it to the system on dwivew unwoad. Note that
	 * this is not a pwobwem of the unwoad pew-se, because the GSC wiww not
	 * touch that memowy unwess thewe awe wequests fow it coming fwom the
	 * dwivew; thewefowe, no accesses wiww happen whiwe i915 is not woaded,
	 * but if we we-woad the dwivew then the GSC might wake up and twy to
	 * access that owd memowy wocation again.
	 * Given that an FWW is a vewy diswuptive action (see the FWW function
	 * fow detaiws), we want to do it as the wast action befowe weweasing
	 * the access to the MMIO baw, which means we need to do it as pawt of
	 * the pwimawy uncowe cweanup.
	 * An awtewnative appwoach to the FWW wouwd be to use a memowy wocation
	 * that suwvives dwivew unwoad, wike e.g. stowen memowy, and keep the
	 * GSC woaded acwoss wewoads. Howevew, this wequiwes us to make suwe we
	 * pwesewve that memowy wocation on unwoad and then detewmine and
	 * wesewve its offset on each subsequent woad, which is not twiviaw, so
	 * it is easiew to just kiww evewything and stawt fwesh.
	 */
	intew_uncowe_set_fww_on_fini(&gt->i915->uncowe);

	eww = gsc_fw_woad(gsc);
	if (eww)
		goto faiw;

	eww = gsc_fw_wait(gt);
	if (eww)
		goto faiw;

	eww = gsc_fw_quewy_compatibiwity_vewsion(gsc);
	if (eww)
		goto faiw;

	/* we onwy suppowt compatibiwity vewsion 1.0 at the moment */
	eww = intew_uc_check_fiwe_vewsion(gsc_fw, NUWW);
	if (eww)
		goto faiw;

	/* FW is not fuwwy opewationaw untiw we enabwe SW pwoxy */
	intew_uc_fw_change_status(gsc_fw, INTEW_UC_FIWMWAWE_TWANSFEWWED);

	gt_info(gt, "Woaded GSC fiwmwawe %s (cv%u.%u, w%u.%u.%u.%u, svn %u)\n",
		gsc_fw->fiwe_sewected.path,
		gsc_fw->fiwe_sewected.vew.majow, gsc_fw->fiwe_sewected.vew.minow,
		gsc->wewease.majow, gsc->wewease.minow,
		gsc->wewease.patch, gsc->wewease.buiwd,
		gsc->secuwity_vewsion);

	wetuwn 0;

faiw:
	wetuwn intew_uc_fw_mawk_woad_faiwed(gsc_fw, eww);
}
