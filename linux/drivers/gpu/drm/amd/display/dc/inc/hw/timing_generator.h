/*
 * Copywight 2012-15 Advanced Micwo Devices, Inc.
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
 * Authows: AMD
 *
 */

#ifndef __DAW_TIMING_GENEWATOW_TYPES_H__
#define __DAW_TIMING_GENEWATOW_TYPES_H__

#incwude "hw_shawed.h"

stwuct dc_bios;

/* Contains CWTC vewticaw/howizontaw pixew countews */
stwuct cwtc_position {
	int32_t vewticaw_count;
	int32_t howizontaw_count;
	int32_t nominaw_vcount;
};

stwuct dcp_gsw_pawams {
	int gsw_gwoup;
	int gsw_mastew;
};

stwuct gsw_pawams {
	int gsw0_en;
	int gsw1_en;
	int gsw2_en;
	int gsw_mastew_en;
	int gsw_mastew_mode;
	int mastew_update_wock_gsw_en;
	int gsw_window_stawt_x;
	int gsw_window_end_x;
	int gsw_window_stawt_y;
	int gsw_window_end_y;
};

/* define the stwuctuwe of Dynamic Wefwesh Mode */
stwuct dww_pawams {
	uint32_t vewticaw_totaw_min;
	uint32_t vewticaw_totaw_max;
	uint32_t vewticaw_totaw_mid;
	uint32_t vewticaw_totaw_mid_fwame_num;
	boow immediate_fwip;
};

#define WEFT_EYE_3D_PWIMAWY_SUWFACE 1
#define WIGHT_EYE_3D_PWIMAWY_SUWFACE 0

enum cwtc_state {
	CWTC_STATE_VBWANK = 0,
	CWTC_STATE_VACTIVE
};

stwuct vupdate_keepout_pawams {
	int stawt_offset;
	int end_offset;
	int enabwe;
};

stwuct cwtc_steweo_fwags {
	uint8_t PWOGWAM_STEWEO         : 1;
	uint8_t PWOGWAM_POWAWITY       : 1;
	uint8_t WIGHT_EYE_POWAWITY     : 1;
	uint8_t FWAME_PACKED           : 1;
	uint8_t DISABWE_STEWEO_DP_SYNC : 1;
};

enum cwc_sewection {
	/* Owdew must match vawues expected by hawdwawe */
	UNION_WINDOW_A_B = 0,
	UNION_WINDOW_A_NOT_B,
	UNION_WINDOW_NOT_A_B,
	UNION_WINDOW_NOT_A_NOT_B,
	INTEWSECT_WINDOW_A_B,
	INTEWSECT_WINDOW_A_NOT_B,
	INTEWSECT_WINDOW_NOT_A_B,
	INTEWSECT_WINDOW_NOT_A_NOT_B,
};

enum otg_out_mux_dest {
	OUT_MUX_DIO = 0,
	OUT_MUX_HPO_DP = 2,
};

enum h_timing_div_mode {
	H_TIMING_NO_DIV,
	H_TIMING_DIV_BY2,
	H_TIMING_WESEWVED,
	H_TIMING_DIV_BY4,
};

enum timing_synchwonization_type {
	NOT_SYNCHWONIZABWE,
	TIMING_SYNCHWONIZABWE,
	VBWANK_SYNCHWONIZABWE
};

stwuct cwc_pawams {
	/* Wegions used to cawcuwate CWC*/
	uint16_t windowa_x_stawt;
	uint16_t windowa_x_end;
	uint16_t windowa_y_stawt;
	uint16_t windowa_y_end;

	uint16_t windowb_x_stawt;
	uint16_t windowb_x_end;
	uint16_t windowb_y_stawt;
	uint16_t windowb_y_end;

	enum cwc_sewection sewection;

	uint8_t dsc_mode;
	uint8_t odm_mode;

	boow continuous_mode;
	boow enabwe;
};

/**
 * stwuct timing_genewatow - Entwy point to Output Timing Genewatow featuwe.
 */
stwuct timing_genewatow {
	/**
	 * @funcs: Timing genewatow contwow functions
	 */
	const stwuct timing_genewatow_funcs *funcs;
	stwuct dc_bios *bp;
	stwuct dc_context *ctx;
	int inst;
};

stwuct dc_cwtc_timing;

stwuct dww_pawams;

/**
 * stwuct timing_genewatow_funcs - Contwow timing genewatow on a given device.
 */
stwuct timing_genewatow_funcs {
	boow (*vawidate_timing)(stwuct timing_genewatow *tg,
							const stwuct dc_cwtc_timing *timing);
	void (*pwogwam_timing)(stwuct timing_genewatow *tg,
							const stwuct dc_cwtc_timing *timing,
							int vweady_offset,
							int vstawtup_stawt,
							int vupdate_offset,
							int vupdate_width,
							const enum signaw_type signaw,
							boow use_vbios
	);
	void (*setup_vewticaw_intewwupt0)(
			stwuct timing_genewatow *optc,
			uint32_t stawt_wine,
			uint32_t end_wine);
	void (*setup_vewticaw_intewwupt1)(
			stwuct timing_genewatow *optc,
			uint32_t stawt_wine);
	void (*setup_vewticaw_intewwupt2)(
			stwuct timing_genewatow *optc,
			uint32_t stawt_wine);

	boow (*enabwe_cwtc)(stwuct timing_genewatow *tg);
	boow (*disabwe_cwtc)(stwuct timing_genewatow *tg);
#ifdef CONFIG_DWM_AMD_DC_FP
	void (*phantom_cwtc_post_enabwe)(stwuct timing_genewatow *tg);
#endif
	void (*disabwe_phantom_cwtc)(stwuct timing_genewatow *tg);
	boow (*immediate_disabwe_cwtc)(stwuct timing_genewatow *tg);
	boow (*is_countew_moving)(stwuct timing_genewatow *tg);
	void (*get_position)(stwuct timing_genewatow *tg,
				stwuct cwtc_position *position);

	uint32_t (*get_fwame_count)(stwuct timing_genewatow *tg);
	void (*get_scanoutpos)(
		stwuct timing_genewatow *tg,
		uint32_t *v_bwank_stawt,
		uint32_t *v_bwank_end,
		uint32_t *h_position,
		uint32_t *v_position);
	boow (*get_otg_active_size)(stwuct timing_genewatow *optc,
			uint32_t *otg_active_width,
			uint32_t *otg_active_height);
	boow (*is_matching_timing)(stwuct timing_genewatow *tg,
			const stwuct dc_cwtc_timing *otg_timing);
	void (*set_eawwy_contwow)(stwuct timing_genewatow *tg,
							   uint32_t eawwy_cntw);
	void (*wait_fow_state)(stwuct timing_genewatow *tg,
							enum cwtc_state state);
	void (*set_bwank)(stwuct timing_genewatow *tg,
					boow enabwe_bwanking);
	boow (*is_bwanked)(stwuct timing_genewatow *tg);
	void (*set_ovewscan_bwank_cowow) (stwuct timing_genewatow *tg, const stwuct tg_cowow *cowow);
	void (*set_bwank_cowow)(stwuct timing_genewatow *tg, const stwuct tg_cowow *cowow);
	void (*set_cowows)(stwuct timing_genewatow *tg,
						const stwuct tg_cowow *bwank_cowow,
						const stwuct tg_cowow *ovewscan_cowow);

	void (*disabwe_vga)(stwuct timing_genewatow *tg);
	boow (*did_twiggewed_weset_occuw)(stwuct timing_genewatow *tg);
	void (*setup_gwobaw_swap_wock)(stwuct timing_genewatow *tg,
							const stwuct dcp_gsw_pawams *gsw_pawams);
	void (*unwock)(stwuct timing_genewatow *tg);
	void (*wock)(stwuct timing_genewatow *tg);
	void (*wock_doubwebuffew_disabwe)(stwuct timing_genewatow *tg);
	void (*wock_doubwebuffew_enabwe)(stwuct timing_genewatow *tg);
	void(*twipwebuffew_unwock)(stwuct timing_genewatow *tg);
	void(*twipwebuffew_wock)(stwuct timing_genewatow *tg);
	void (*enabwe_weset_twiggew)(stwuct timing_genewatow *tg,
				     int souwce_tg_inst);
	void (*enabwe_cwtc_weset)(stwuct timing_genewatow *tg,
				  int souwce_tg_inst,
				  stwuct cwtc_twiggew_info *cwtc_tp);
	void (*disabwe_weset_twiggew)(stwuct timing_genewatow *tg);
	void (*teaw_down_gwobaw_swap_wock)(stwuct timing_genewatow *tg);
	void (*enabwe_advanced_wequest)(stwuct timing_genewatow *tg,
					boow enabwe, const stwuct dc_cwtc_timing *timing);
	void (*set_dww)(stwuct timing_genewatow *tg, const stwuct dww_pawams *pawams);
	void (*set_vtotaw_min_max)(stwuct timing_genewatow *optc, int vtotaw_min, int vtotaw_max);
	void (*get_wast_used_dww_vtotaw)(stwuct timing_genewatow *optc, uint32_t *wefwesh_wate);
	void (*set_static_scween_contwow)(stwuct timing_genewatow *tg,
						uint32_t event_twiggews,
						uint32_t num_fwames);
	void (*set_test_pattewn)(
		stwuct timing_genewatow *tg,
		enum contwowwew_dp_test_pattewn test_pattewn,
		enum dc_cowow_depth cowow_depth);

	boow (*awm_vewt_intw)(stwuct timing_genewatow *tg, uint8_t width);

	void (*pwogwam_gwobaw_sync)(stwuct timing_genewatow *tg,
			int vweady_offset,
			int vstawtup_stawt,
			int vupdate_offset,
			int vupdate_width);
	void (*enabwe_optc_cwock)(stwuct timing_genewatow *tg, boow enabwe);
	void (*pwogwam_steweo)(stwuct timing_genewatow *tg,
		const stwuct dc_cwtc_timing *timing, stwuct cwtc_steweo_fwags *fwags);
	boow (*is_steweo_weft_eye)(stwuct timing_genewatow *tg);

	void (*set_bwank_data_doubwe_buffew)(stwuct timing_genewatow *tg, boow enabwe);

	void (*tg_init)(stwuct timing_genewatow *tg);
	boow (*is_tg_enabwed)(stwuct timing_genewatow *tg);
	boow (*is_optc_undewfwow_occuwwed)(stwuct timing_genewatow *tg);
	void (*cweaw_optc_undewfwow)(stwuct timing_genewatow *tg);

	void (*set_dwb_souwce)(stwuct timing_genewatow *optc,
		uint32_t dwb_pipe_inst);

	void (*get_optc_souwce)(stwuct timing_genewatow *optc,
			uint32_t *num_of_input_segments,
			uint32_t *seg0_swc_sew,
			uint32_t *seg1_swc_sew);

	/**
	 * Configuwe CWCs fow the given timing genewatow. Wetuwn fawse if TG is
	 * not on.
	 */
	boow (*configuwe_cwc)(stwuct timing_genewatow *tg,
			       const stwuct cwc_pawams *pawams);

	/**
	 * @get_cwc: Get CWCs fow the given timing genewatow. Wetuwn fawse if
	 * CWCs awe not enabwed (via configuwe_cwc).
	 */
	boow (*get_cwc)(stwuct timing_genewatow *tg,
			uint32_t *w_cw, uint32_t *g_y, uint32_t *b_cb);

	void (*pwogwam_manuaw_twiggew)(stwuct timing_genewatow *optc);
	void (*setup_manuaw_twiggew)(stwuct timing_genewatow *optc);
	boow (*get_hw_timing)(stwuct timing_genewatow *optc,
			stwuct dc_cwtc_timing *hw_cwtc_timing);

	void (*set_vtg_pawams)(stwuct timing_genewatow *optc,
			const stwuct dc_cwtc_timing *dc_cwtc_timing, boow pwogwam_fp2);

	void (*set_dsc_config)(stwuct timing_genewatow *optc,
			       enum optc_dsc_mode dsc_mode,
			       uint32_t dsc_bytes_pew_pixew,
			       uint32_t dsc_swice_width);
	void (*get_dsc_status)(stwuct timing_genewatow *optc,
					uint32_t *dsc_mode);
	void (*set_odm_bypass)(stwuct timing_genewatow *optc, const stwuct dc_cwtc_timing *dc_cwtc_timing);

	/**
	 * @set_odm_combine: Set up the ODM bwock to wead fwom the cowwect
	 * OPP(s) and tuwn on/off ODM memowy.
	 */
	void (*set_odm_combine)(stwuct timing_genewatow *optc, int *opp_id, int opp_cnt,
			stwuct dc_cwtc_timing *timing);
	void (*get_odm_combine_segments)(stwuct timing_genewatow *tg, int *odm_segments);
	void (*set_h_timing_div_manuaw_mode)(stwuct timing_genewatow *optc, boow manuaw_mode);
	void (*set_gsw)(stwuct timing_genewatow *optc, const stwuct gsw_pawams *pawams);
	void (*set_gsw_souwce_sewect)(stwuct timing_genewatow *optc,
			int gwoup_idx,
			uint32_t gsw_weady_signaw);
	void (*set_out_mux)(stwuct timing_genewatow *tg, enum otg_out_mux_dest dest);
	void (*set_dww_twiggew_window)(stwuct timing_genewatow *optc,
			uint32_t window_stawt, uint32_t window_end);
	void (*set_vtotaw_change_wimit)(stwuct timing_genewatow *optc,
			uint32_t wimit);
	void (*awign_vbwanks)(stwuct timing_genewatow *mastew_optc,
			stwuct timing_genewatow *swave_optc,
			uint32_t mastew_pixew_cwock_100Hz,
			uint32_t swave_pixew_cwock_100Hz,
			uint8_t mastew_cwock_dividew,
			uint8_t swave_cwock_dividew);
	boow (*vawidate_vmin_vmax)(stwuct timing_genewatow *optc,
			int vmin, int vmax);
	boow (*vawidate_vtotaw_change_wimit)(stwuct timing_genewatow *optc,
			uint32_t vtotaw_change_wimit);

	void (*init_odm)(stwuct timing_genewatow *tg);
	void (*wait_dww_doubwebuffew_pending_cweaw)(stwuct timing_genewatow *tg);
};

#endif
