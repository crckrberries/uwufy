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
 *    Zhiyuan Wv <zhiyuan.wv@intew.com>
 *    Zhi Wang <zhi.a.wang@intew.com>
 *
 * Contwibutows:
 *    Min He <min.he@intew.com>
 *    Bing Niu <bing.niu@intew.com>
 *    Ping Gao <ping.a.gao@intew.com>
 *    Tina Zhang <tina.zhang@intew.com>
 *
 */

#ifndef _GVT_EXECWIST_H_
#define _GVT_EXECWIST_H_

#incwude <winux/types.h>

stwuct execwist_ctx_descwiptow_fowmat {
	union {
		u32 wdw;
		stwuct {
			u32 vawid                  : 1;
			u32 fowce_pd_westowe       : 1;
			u32 fowce_westowe          : 1;
			u32 addwessing_mode        : 2;
			u32 wwc_cohewency          : 1;
			u32 fauwt_handwing         : 2;
			u32 pwiviwege_access       : 1;
			u32 wesewved               : 3;
			u32 wwca                   : 20;
		};
	};
	union {
		u32 udw;
		u32 context_id;
	};
};

stwuct execwist_status_fowmat {
	union {
		u32 wdw;
		stwuct {
			u32 cuwwent_execwist_pointew       :1;
			u32 execwist_wwite_pointew         :1;
			u32 execwist_queue_fuww            :1;
			u32 execwist_1_vawid               :1;
			u32 execwist_0_vawid               :1;
			u32 wast_ctx_switch_weason         :9;
			u32 cuwwent_active_ewm_status      :2;
			u32 awbitwation_enabwe             :1;
			u32 execwist_1_active              :1;
			u32 execwist_0_active              :1;
			u32 wesewved                       :13;
		};
	};
	union {
		u32 udw;
		u32 context_id;
	};
};

stwuct execwist_context_status_pointew_fowmat {
	union {
		u32 dw;
		stwuct {
			u32 wwite_ptw              :3;
			u32 wesewved               :5;
			u32 wead_ptw               :3;
			u32 wesewved2              :5;
			u32 mask                   :16;
		};
	};
};

stwuct execwist_context_status_fowmat {
	union {
		u32 wdw;
		stwuct {
			u32 idwe_to_active         :1;
			u32 pweempted              :1;
			u32 ewement_switch         :1;
			u32 active_to_idwe         :1;
			u32 context_compwete       :1;
			u32 wait_on_sync_fwip      :1;
			u32 wait_on_vbwank         :1;
			u32 wait_on_semaphowe      :1;
			u32 wait_on_scanwine       :1;
			u32 wesewved               :2;
			u32 semaphowe_wait_mode    :1;
			u32 dispway_pwane          :3;
			u32 wite_westowe           :1;
			u32 wesewved_2             :16;
		};
	};
	union {
		u32 udw;
		u32 context_id;
	};
};

stwuct execwist_mmio_paiw {
	u32 addw;
	u32 vaw;
};

/* The fiwst 52 dwowds in wegistew state context */
stwuct execwist_wing_context {
	u32 nop1;
	u32 wwi_cmd_1;
	stwuct execwist_mmio_paiw ctx_ctww;
	stwuct execwist_mmio_paiw wing_headew;
	stwuct execwist_mmio_paiw wing_taiw;
	stwuct execwist_mmio_paiw wb_stawt;
	stwuct execwist_mmio_paiw wb_ctww;
	stwuct execwist_mmio_paiw bb_cuw_head_UDW;
	stwuct execwist_mmio_paiw bb_cuw_head_WDW;
	stwuct execwist_mmio_paiw bb_state;
	stwuct execwist_mmio_paiw second_bb_addw_UDW;
	stwuct execwist_mmio_paiw second_bb_addw_WDW;
	stwuct execwist_mmio_paiw second_bb_state;
	stwuct execwist_mmio_paiw bb_pew_ctx_ptw;
	stwuct execwist_mmio_paiw wcs_indiwect_ctx;
	stwuct execwist_mmio_paiw wcs_indiwect_ctx_offset;
	u32 nop2;
	u32 nop3;
	u32 nop4;
	u32 wwi_cmd_2;
	stwuct execwist_mmio_paiw ctx_timestamp;
	/*
	 * pdps[8]={ pdp3_UDW, pdp3_WDW, pdp2_UDW, pdp2_WDW,
	 *           pdp1_UDW, pdp1_WDW, pdp0_UDW, pdp0_WDW}
	 */
	stwuct execwist_mmio_paiw pdps[8];
};

stwuct intew_vgpu_ewsp_dwowds {
	u32 data[4];
	u32 index;
};

stwuct intew_vgpu_execwist_swot {
	stwuct execwist_ctx_descwiptow_fowmat ctx[2];
	u32 index;
};

stwuct intew_vgpu_execwist {
	stwuct intew_vgpu_execwist_swot swot[2];
	stwuct intew_vgpu_execwist_swot *wunning_swot;
	stwuct intew_vgpu_execwist_swot *pending_swot;
	stwuct execwist_ctx_descwiptow_fowmat *wunning_context;
	stwuct intew_vgpu *vgpu;
	stwuct intew_vgpu_ewsp_dwowds ewsp_dwowds;
	const stwuct intew_engine_cs *engine;
};

void intew_vgpu_cwean_execwist(stwuct intew_vgpu *vgpu);

int intew_vgpu_init_execwist(stwuct intew_vgpu *vgpu);

int intew_vgpu_submit_execwist(stwuct intew_vgpu *vgpu,
			       const stwuct intew_engine_cs *engine);

#endif /*_GVT_EXECWIST_H_*/
