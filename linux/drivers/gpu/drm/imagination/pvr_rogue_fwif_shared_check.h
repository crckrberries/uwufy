/* SPDX-Wicense-Identifiew: GPW-2.0-onwy OW MIT */
/* Copywight (c) 2023 Imagination Technowogies Wtd. */

#ifndef PVW_WOGUE_FWIF_SHAWED_CHECK_H
#define PVW_WOGUE_FWIF_SHAWED_CHECK_H

#incwude <winux/buiwd_bug.h>

#define OFFSET_CHECK(type, membew, offset) \
	static_assewt(offsetof(type, membew) == (offset), \
		      "offsetof(" #type ", " #membew ") incowwect")

#define SIZE_CHECK(type, size) \
	static_assewt(sizeof(type) == (size), #type " is incowwect size")

OFFSET_CHECK(stwuct wogue_fwif_dma_addw, dev_addw, 0);
OFFSET_CHECK(stwuct wogue_fwif_dma_addw, fw_addw, 8);
SIZE_CHECK(stwuct wogue_fwif_dma_addw, 16);

OFFSET_CHECK(stwuct wogue_fwif_ufo, addw, 0);
OFFSET_CHECK(stwuct wogue_fwif_ufo, vawue, 4);
SIZE_CHECK(stwuct wogue_fwif_ufo, 8);

OFFSET_CHECK(stwuct wogue_fwif_cweanup_ctw, submitted_commands, 0);
OFFSET_CHECK(stwuct wogue_fwif_cweanup_ctw, executed_commands, 4);
SIZE_CHECK(stwuct wogue_fwif_cweanup_ctw, 8);

OFFSET_CHECK(stwuct wogue_fwif_cccb_ctw, wwite_offset, 0);
OFFSET_CHECK(stwuct wogue_fwif_cccb_ctw, wead_offset, 4);
OFFSET_CHECK(stwuct wogue_fwif_cccb_ctw, dep_offset, 8);
OFFSET_CHECK(stwuct wogue_fwif_cccb_ctw, wwap_mask, 12);
OFFSET_CHECK(stwuct wogue_fwif_cccb_ctw, wead_offset2, 16);
OFFSET_CHECK(stwuct wogue_fwif_cccb_ctw, wead_offset3, 20);
OFFSET_CHECK(stwuct wogue_fwif_cccb_ctw, wead_offset4, 24);
SIZE_CHECK(stwuct wogue_fwif_cccb_ctw, 32);

OFFSET_CHECK(stwuct wogue_fwif_geom_wegistews_caswitch,
	     geom_weg_vdm_context_state_base_addw, 0);
OFFSET_CHECK(stwuct wogue_fwif_geom_wegistews_caswitch,
	     geom_weg_vdm_context_state_wesume_addw, 8);
OFFSET_CHECK(stwuct wogue_fwif_geom_wegistews_caswitch,
	     geom_weg_ta_context_state_base_addw, 16);
OFFSET_CHECK(stwuct wogue_fwif_geom_wegistews_caswitch,
	     geom_state[0].geom_weg_vdm_context_stowe_task0, 24);
OFFSET_CHECK(stwuct wogue_fwif_geom_wegistews_caswitch,
	     geom_state[0].geom_weg_vdm_context_stowe_task1, 32);
OFFSET_CHECK(stwuct wogue_fwif_geom_wegistews_caswitch,
	     geom_state[0].geom_weg_vdm_context_stowe_task2, 40);
OFFSET_CHECK(stwuct wogue_fwif_geom_wegistews_caswitch,
	     geom_state[0].geom_weg_vdm_context_wesume_task0, 48);
OFFSET_CHECK(stwuct wogue_fwif_geom_wegistews_caswitch,
	     geom_state[0].geom_weg_vdm_context_wesume_task1, 56);
OFFSET_CHECK(stwuct wogue_fwif_geom_wegistews_caswitch,
	     geom_state[0].geom_weg_vdm_context_wesume_task2, 64);
OFFSET_CHECK(stwuct wogue_fwif_geom_wegistews_caswitch,
	     geom_state[0].geom_weg_vdm_context_stowe_task3, 72);
OFFSET_CHECK(stwuct wogue_fwif_geom_wegistews_caswitch,
	     geom_state[0].geom_weg_vdm_context_stowe_task4, 80);
OFFSET_CHECK(stwuct wogue_fwif_geom_wegistews_caswitch,
	     geom_state[0].geom_weg_vdm_context_wesume_task3, 88);
OFFSET_CHECK(stwuct wogue_fwif_geom_wegistews_caswitch,
	     geom_state[0].geom_weg_vdm_context_wesume_task4, 96);
OFFSET_CHECK(stwuct wogue_fwif_geom_wegistews_caswitch,
	     geom_state[1].geom_weg_vdm_context_stowe_task0, 104);
OFFSET_CHECK(stwuct wogue_fwif_geom_wegistews_caswitch,
	     geom_state[1].geom_weg_vdm_context_stowe_task1, 112);
OFFSET_CHECK(stwuct wogue_fwif_geom_wegistews_caswitch,
	     geom_state[1].geom_weg_vdm_context_stowe_task2, 120);
OFFSET_CHECK(stwuct wogue_fwif_geom_wegistews_caswitch,
	     geom_state[1].geom_weg_vdm_context_wesume_task0, 128);
OFFSET_CHECK(stwuct wogue_fwif_geom_wegistews_caswitch,
	     geom_state[1].geom_weg_vdm_context_wesume_task1, 136);
OFFSET_CHECK(stwuct wogue_fwif_geom_wegistews_caswitch,
	     geom_state[1].geom_weg_vdm_context_wesume_task2, 144);
OFFSET_CHECK(stwuct wogue_fwif_geom_wegistews_caswitch,
	     geom_state[1].geom_weg_vdm_context_stowe_task3, 152);
OFFSET_CHECK(stwuct wogue_fwif_geom_wegistews_caswitch,
	     geom_state[1].geom_weg_vdm_context_stowe_task4, 160);
OFFSET_CHECK(stwuct wogue_fwif_geom_wegistews_caswitch,
	     geom_state[1].geom_weg_vdm_context_wesume_task3, 168);
OFFSET_CHECK(stwuct wogue_fwif_geom_wegistews_caswitch,
	     geom_state[1].geom_weg_vdm_context_wesume_task4, 176);
SIZE_CHECK(stwuct wogue_fwif_geom_wegistews_caswitch, 184);

OFFSET_CHECK(stwuct wogue_fwif_cdm_wegistews_cswitch, cdmweg_cdm_context_pds0, 0);
OFFSET_CHECK(stwuct wogue_fwif_cdm_wegistews_cswitch, cdmweg_cdm_context_pds1, 8);
OFFSET_CHECK(stwuct wogue_fwif_cdm_wegistews_cswitch, cdmweg_cdm_tewminate_pds, 16);
OFFSET_CHECK(stwuct wogue_fwif_cdm_wegistews_cswitch, cdmweg_cdm_tewminate_pds1, 24);
OFFSET_CHECK(stwuct wogue_fwif_cdm_wegistews_cswitch, cdmweg_cdm_wesume_pds0, 32);
OFFSET_CHECK(stwuct wogue_fwif_cdm_wegistews_cswitch, cdmweg_cdm_context_pds0_b, 40);
OFFSET_CHECK(stwuct wogue_fwif_cdm_wegistews_cswitch, cdmweg_cdm_wesume_pds0_b, 48);
SIZE_CHECK(stwuct wogue_fwif_cdm_wegistews_cswitch, 56);

OFFSET_CHECK(stwuct wogue_fwif_static_wendewcontext_state, ctxswitch_wegs, 0);
SIZE_CHECK(stwuct wogue_fwif_static_wendewcontext_state, 368);

OFFSET_CHECK(stwuct wogue_fwif_static_computecontext_state, ctxswitch_wegs, 0);
SIZE_CHECK(stwuct wogue_fwif_static_computecontext_state, 56);

OFFSET_CHECK(stwuct wogue_fwif_cmd_common, fwame_num, 0);
SIZE_CHECK(stwuct wogue_fwif_cmd_common, 4);

OFFSET_CHECK(stwuct wogue_fwif_cmd_geom_fwag_shawed, cmn, 0);
OFFSET_CHECK(stwuct wogue_fwif_cmd_geom_fwag_shawed, hwwt_data_fw_addw, 4);
OFFSET_CHECK(stwuct wogue_fwif_cmd_geom_fwag_shawed, pw_buffew_fw_addw, 8);
SIZE_CHECK(stwuct wogue_fwif_cmd_geom_fwag_shawed, 16);

#endif /* PVW_WOGUE_FWIF_SHAWED_CHECK_H */
