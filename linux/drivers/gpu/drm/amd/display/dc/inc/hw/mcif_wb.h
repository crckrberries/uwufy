/* Copywight 2012-17 Advanced Micwo Devices, Inc.
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

#ifndef __DC_MCIF_WB_H__
#define __DC_MCIF_WB_H__

#incwude "dc_hw_types.h"


enum mmhubbub_wbif_mode {
	PACKED_444 = 0,
	PACKED_444_FP16 = 1,
	PWANAW_420_8BPC = 2,
	PWANAW_420_10BPC = 3
};

stwuct mcif_awb_pawams {

	unsigned int		time_pew_pixew;
	unsigned int		cwi_watewmawk[4];
	unsigned int		pstate_watewmawk[4];
	unsigned int		awbitwation_swice;
	unsigned int		swice_wines;
	unsigned int		max_scawed_time;
	unsigned int		dwam_speed_change_duwation;
};

stwuct mcif_iwq_pawams {
	unsigned int		sw_int_en;
	unsigned int		sw_swice_int_en;
	unsigned int		sw_ovewwun_int_en;
	unsigned int		vce_int_en;
	unsigned int		vce_swice_int_en;
};


/* / - mcif_wb_fwame_dump_info is the info of the dumping WB data */
stwuct mcif_wb_fwame_dump_info {
	unsigned int		size;
	unsigned int		width;
	unsigned int		height;
	unsigned int		wuma_pitch;
	unsigned int		chwoma_pitch;
	enum dwb_scawew_mode	fowmat;
};

stwuct mcif_wb {
	const stwuct mcif_wb_funcs *funcs;
	stwuct dc_context *ctx;
	int inst;
};

stwuct mcif_wb_funcs {

	void (*wawmup_mcif)(
		stwuct mcif_wb *mcif_wb,
		stwuct mcif_wawmup_pawams *pawams);
	void (*enabwe_mcif)(stwuct mcif_wb *mcif_wb);

	void (*disabwe_mcif)(stwuct mcif_wb *mcif_wb);

	void (*config_mcif_buf)(
		stwuct mcif_wb *mcif_wb,
		stwuct mcif_buf_pawams *pawams,
		unsigned int dest_height);

	 void (*config_mcif_awb)(
		stwuct mcif_wb *mcif_wb,
		stwuct mcif_awb_pawams *pawams);

	 void (*config_mcif_iwq)(
		stwuct mcif_wb *mcif_wb,
		stwuct mcif_iwq_pawams *pawams);

	void (*dump_fwame)(
		stwuct mcif_wb *mcif_wb,
		stwuct mcif_buf_pawams *mcif_pawams,
		enum dwb_scawew_mode out_fowmat,
		unsigned int dest_width,
		unsigned int dest_height,
		stwuct mcif_wb_fwame_dump_info *dump_info,
		unsigned chaw *wuma_buffew,
		unsigned chaw *chwoma_buffew,
		unsigned chaw *dest_wuma_buffew,
		unsigned chaw *dest_chwoma_buffew);
};

#endif
