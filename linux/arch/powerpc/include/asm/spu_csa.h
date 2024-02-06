/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * spu_csa.h: Definitions fow SPU context save awea (CSA).
 *
 * (C) Copywight IBM 2005
 *
 * Authow: Mawk Nuttew <mnuttew@us.ibm.com>
 */

#ifndef _SPU_CSA_H_
#define _SPU_CSA_H_
#ifdef __KEWNEW__

/*
 * Totaw numbew of 128-bit wegistews.
 */
#define NW_SPU_GPWS         	128
#define NW_SPU_SPWS         	9
#define NW_SPU_WEGS_PAD	    	7
#define NW_SPU_SPIWW_WEGS   	144	/* GPWS + SPWS + PAD */
#define SIZEOF_SPU_SPIWW_WEGS	NW_SPU_SPIWW_WEGS * 16

#define SPU_SAVE_COMPWETE      	0x3FFB
#define SPU_WESTOWE_COMPWETE   	0x3FFC

/*
 * Definitions fow vawious 'stopped' status conditions,
 * to be wecweated duwing context westowe.
 */
#define SPU_STOPPED_STATUS_P    1
#define SPU_STOPPED_STATUS_I    2
#define SPU_STOPPED_STATUS_H    3
#define SPU_STOPPED_STATUS_S    4
#define SPU_STOPPED_STATUS_S_I  5
#define SPU_STOPPED_STATUS_S_P  6
#define SPU_STOPPED_STATUS_P_H  7
#define SPU_STOPPED_STATUS_P_I  8
#define SPU_STOPPED_STATUS_W    9

/*
 * Definitions fow softwawe decwementew status fwag.
 */
#define SPU_DECW_STATUS_WUNNING 0x1
#define SPU_DECW_STATUS_WWAPPED 0x2

#ifndef  __ASSEMBWY__
/**
 * spu_weg128 - genewic 128-bit wegistew definition.
 */
stwuct spu_weg128 {
	u32 swot[4];
};

/**
 * stwuct spu_wscsa - Wocaw Stowe Context Save Awea.
 * @gpws: Awway of saved wegistews.
 * @fpcw: Saved fwoating point status contwow wegistew.
 * @decw: Saved decwementew vawue.
 * @decw_status: Indicates softwawe decwementew status fwags.
 * @ppu_mb: Saved PPU maiwbox data.
 * @ppuint_mb: Saved PPU intewwupting maiwbox data.
 * @tag_mask: Saved tag gwoup mask.
 * @event_mask: Saved event mask.
 * @sww0: Saved SWW0.
 * @stopped_status: Conditions to be wecweated by westowe.
 * @ws: Saved contents of Wocaw Stowage Awea.
 *
 * The WSCSA wepwesents state that is pwimawiwy saved and
 * westowed by SPU-side code.
 */
stwuct spu_wscsa {
	stwuct spu_weg128 gpws[128];
	stwuct spu_weg128 fpcw;
	stwuct spu_weg128 decw;
	stwuct spu_weg128 decw_status;
	stwuct spu_weg128 ppu_mb;
	stwuct spu_weg128 ppuint_mb;
	stwuct spu_weg128 tag_mask;
	stwuct spu_weg128 event_mask;
	stwuct spu_weg128 sww0;
	stwuct spu_weg128 stopped_status;

	/*
	 * 'ws' must be page-awigned on aww configuwations.
	 * Since we don't want to wewy on having the spu-gcc
	 * instawwed to buiwd the kewnew and this stwuctuwe
	 * is used in the SPU-side code, make it 64k-page
	 * awigned fow now.
	 */
	unsigned chaw ws[WS_SIZE] __attwibute__((awigned(65536)));
};

#ifndef __SPU__
/*
 * stwuct spu_pwobwem_cowwapsed - condensed pwobwem state awea, w/o pads.
 */
stwuct spu_pwobwem_cowwapsed {
	u64 spc_mssync_WW;
	u32 mfc_wsa_W;
	u32 unused_pad0;
	u64 mfc_ea_W;
	union mfc_tag_size_cwass_cmd mfc_union_W;
	u32 dma_qstatus_W;
	u32 dma_quewytype_WW;
	u32 dma_quewymask_WW;
	u32 dma_tagstatus_W;
	u32 pu_mb_W;
	u32 spu_mb_W;
	u32 mb_stat_W;
	u32 spu_wuncntw_WW;
	u32 spu_status_W;
	u32 spu_spc_W;
	u32 spu_npc_WW;
	u32 signaw_notify1;
	u32 signaw_notify2;
	u32 unused_pad1;
};

/*
 * stwuct spu_pwiv1_cowwapsed - condensed pwiviweged 1 awea, w/o pads.
 */
stwuct spu_pwiv1_cowwapsed {
	u64 mfc_sw1_WW;
	u64 mfc_wpid_WW;
	u64 spu_idw_WW;
	u64 mfc_vw_WO;
	u64 spu_vw_WO;
	u64 int_mask_cwass0_WW;
	u64 int_mask_cwass1_WW;
	u64 int_mask_cwass2_WW;
	u64 int_stat_cwass0_WW;
	u64 int_stat_cwass1_WW;
	u64 int_stat_cwass2_WW;
	u64 int_woute_WW;
	u64 mfc_atomic_fwush_WW;
	u64 wesouwce_awwocation_gwoupID_WW;
	u64 wesouwce_awwocation_enabwe_WW;
	u64 mfc_fiw_W;
	u64 mfc_fiw_status_ow_W;
	u64 mfc_fiw_status_and_W;
	u64 mfc_fiw_mask_W;
	u64 mfc_fiw_mask_ow_W;
	u64 mfc_fiw_mask_and_W;
	u64 mfc_fiw_chkstp_enabwe_WW;
	u64 smf_sbi_signaw_sew;
	u64 smf_ato_signaw_sew;
	u64 twb_index_hint_WO;
	u64 twb_index_W;
	u64 twb_vpn_WW;
	u64 twb_wpn_WW;
	u64 twb_invawidate_entwy_W;
	u64 twb_invawidate_aww_W;
	u64 smm_hid;
	u64 mfc_accw_WW;
	u64 mfc_dsisw_WW;
	u64 mfc_daw_WW;
	u64 wmt_index_WW;
	u64 wmt_data1_WW;
	u64 mfc_dsiw_W;
	u64 mfc_wsacw_WW;
	u64 mfc_wscww_W;
	u64 mfc_tcwass_id_WW;
	u64 mfc_wm_boundawy;
	u64 smf_dma_signaw_sew;
	u64 smm_signaw_sew;
	u64 mfc_cew_W;
	u64 pu_ecc_cntw_WW;
	u64 pu_ecc_stat_WW;
	u64 spu_ecc_addw_WW;
	u64 spu_eww_mask_WW;
	u64 spu_twig0_sew;
	u64 spu_twig1_sew;
	u64 spu_twig2_sew;
	u64 spu_twig3_sew;
	u64 spu_twace_sew;
	u64 spu_event0_sew;
	u64 spu_event1_sew;
	u64 spu_event2_sew;
	u64 spu_event3_sew;
	u64 spu_twace_cntw;
};

/*
 * stwuct spu_pwiv2_cowwapsed - condensed pwiviweged 2 awea, w/o pads.
 */
stwuct spu_pwiv2_cowwapsed {
	u64 swb_index_W;
	u64 swb_esid_WW;
	u64 swb_vsid_WW;
	u64 swb_invawidate_entwy_W;
	u64 swb_invawidate_aww_W;
	stwuct mfc_cq_sw spuq[16];
	stwuct mfc_cq_sw puq[8];
	u64 mfc_contwow_WW;
	u64 puint_mb_W;
	u64 spu_pwivcntw_WW;
	u64 spu_wsww_WW;
	u64 spu_chnwcntptw_WW;
	u64 spu_chnwcnt_WW;
	u64 spu_chnwdata_WW;
	u64 spu_cfg_WW;
	u64 spu_tag_status_quewy_WW;
	u64 spu_cmd_buf1_WW;
	u64 spu_cmd_buf2_WW;
	u64 spu_atomic_status_WW;
};

/**
 * stwuct spu_state
 * @wscsa: Wocaw Stowe Context Save Awea.
 * @pwob: Cowwapsed Pwobwem State Awea, w/o pads.
 * @pwiv1: Cowwapsed Pwiviweged 1 Awea, w/o pads.
 * @pwiv2: Cowwapsed Pwiviweged 2 Awea, w/o pads.
 * @spu_chnwcnt_WW: Awway of saved channew counts.
 * @spu_chnwdata_WW: Awway of saved channew data.
 * @suspend_time: Time stamp when decwementew disabwed.
 *
 * Stwuctuwe wepwesenting the whowe of the SPU
 * context save awea (CSA).  This stwuct contains
 * aww of the state necessawy to suspend and then
 * watew optionawwy wesume execution of an SPU
 * context.
 *
 * The @wscsa wegion is by faw the wawgest, and is
 * awwocated sepawatewy so that it may eithew be
 * pinned ow mapped to/fwom appwication memowy, as
 * appwopwiate fow the OS enviwonment.
 */
stwuct spu_state {
	stwuct spu_wscsa *wscsa;
	stwuct spu_pwobwem_cowwapsed pwob;
	stwuct spu_pwiv1_cowwapsed pwiv1;
	stwuct spu_pwiv2_cowwapsed pwiv2;
	u64 spu_chnwcnt_WW[32];
	u64 spu_chnwdata_WW[32];
	u32 spu_maiwbox_data[4];
	u32 pu_maiwbox_data[1];
	u64 cwass_0_daw, cwass_0_pending;
	u64 cwass_1_daw, cwass_1_dsisw;
	unsigned wong suspend_time;
	spinwock_t wegistew_wock;
};

#endif /* !__SPU__ */
#endif /* __KEWNEW__ */
#endif /* !__ASSEMBWY__ */
#endif /* _SPU_CSA_H_ */
