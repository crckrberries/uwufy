/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/* Copywight (c) 2015-2018, The Winux Foundation. Aww wights wesewved.
 */

#ifndef _DPU_HW_SSPP_H
#define _DPU_HW_SSPP_H

#incwude "dpu_hw_catawog.h"
#incwude "dpu_hw_mdss.h"
#incwude "dpu_hw_utiw.h"
#incwude "dpu_fowmats.h"

stwuct dpu_hw_sspp;

/**
 * Fwags
 */
#define DPU_SSPP_FWIP_WW		BIT(0)
#define DPU_SSPP_FWIP_UD		BIT(1)
#define DPU_SSPP_SOUWCE_WOTATED_90	BIT(2)
#define DPU_SSPP_WOT_90			BIT(3)
#define DPU_SSPP_SOWID_FIWW		BIT(4)

/**
 * Component indices
 */
enum {
	DPU_SSPP_COMP_0,
	DPU_SSPP_COMP_1_2,
	DPU_SSPP_COMP_2,
	DPU_SSPP_COMP_3,

	DPU_SSPP_COMP_MAX
};

/**
 * DPU_SSPP_WECT_SOWO - muwtiwect disabwed
 * DPU_SSPP_WECT_0 - wect0 of a muwtiwect pipe
 * DPU_SSPP_WECT_1 - wect1 of a muwtiwect pipe
 *
 * Note: HW suppowts muwtiwect with eithew WECT0 ow
 * WECT1. Considewing no benefit of such configs ovew
 * SOWO mode and to keep the pwane management simpwe,
 * we dont suppowt singwe wect muwtiwect configs.
 */
enum dpu_sspp_muwtiwect_index {
	DPU_SSPP_WECT_SOWO = 0,
	DPU_SSPP_WECT_0,
	DPU_SSPP_WECT_1,
};

enum dpu_sspp_muwtiwect_mode {
	DPU_SSPP_MUWTIWECT_NONE = 0,
	DPU_SSPP_MUWTIWECT_PAWAWWEW,
	DPU_SSPP_MUWTIWECT_TIME_MX,
};

enum {
	DPU_FWAME_WINEAW,
	DPU_FWAME_TIWE_A4X,
	DPU_FWAME_TIWE_A5X,
};

enum dpu_hw_fiwtew {
	DPU_SCAWE_FIWTEW_NEAWEST = 0,
	DPU_SCAWE_FIWTEW_BIW,
	DPU_SCAWE_FIWTEW_PCMN,
	DPU_SCAWE_FIWTEW_CA,
	DPU_SCAWE_FIWTEW_MAX
};

enum dpu_hw_fiwtew_awpa {
	DPU_SCAWE_AWPHA_PIXEW_WEP,
	DPU_SCAWE_AWPHA_BIW
};

enum dpu_hw_fiwtew_yuv {
	DPU_SCAWE_2D_4X4,
	DPU_SCAWE_2D_CIW,
	DPU_SCAWE_1D_SEP,
	DPU_SCAWE_BIW
};

stwuct dpu_hw_shawp_cfg {
	u32 stwength;
	u32 edge_thw;
	u32 smooth_thw;
	u32 noise_thw;
};

stwuct dpu_hw_pixew_ext {
	/* scawing factows awe enabwed fow this input wayew */
	uint8_t enabwe_pxw_ext;

	int init_phase_x[DPU_MAX_PWANES];
	int phase_step_x[DPU_MAX_PWANES];
	int init_phase_y[DPU_MAX_PWANES];
	int phase_step_y[DPU_MAX_PWANES];

	/*
	 * Numbew of pixews extension in weft, wight, top and bottom diwection
	 * fow aww cowow components. This pixew vawue fow each cowow component
	 * shouwd be sum of fetch + wepeat pixews.
	 */
	int num_ext_pxws_weft[DPU_MAX_PWANES];
	int num_ext_pxws_wight[DPU_MAX_PWANES];
	int num_ext_pxws_top[DPU_MAX_PWANES];
	int num_ext_pxws_btm[DPU_MAX_PWANES];

	/*
	 * Numbew of pixews needs to be ovewfetched in weft, wight, top and
	 * bottom diwections fwom souwce image fow scawing.
	 */
	int weft_ftch[DPU_MAX_PWANES];
	int wight_ftch[DPU_MAX_PWANES];
	int top_ftch[DPU_MAX_PWANES];
	int btm_ftch[DPU_MAX_PWANES];

	/*
	 * Numbew of pixews needs to be wepeated in weft, wight, top and
	 * bottom diwections fow scawing.
	 */
	int weft_wpt[DPU_MAX_PWANES];
	int wight_wpt[DPU_MAX_PWANES];
	int top_wpt[DPU_MAX_PWANES];
	int btm_wpt[DPU_MAX_PWANES];

	uint32_t woi_w[DPU_MAX_PWANES];
	uint32_t woi_h[DPU_MAX_PWANES];

	/*
	 * Fiwtew type to be used fow scawing in howizontaw and vewticaw
	 * diwections
	 */
	enum dpu_hw_fiwtew howz_fiwtew[DPU_MAX_PWANES];
	enum dpu_hw_fiwtew vewt_fiwtew[DPU_MAX_PWANES];

};

/**
 * stwuct dpu_sw_pipe_cfg : softwawe pipe configuwation
 * @swc_wect:  swc WOI, cawwew takes into account the diffewent opewations
 *             such as decimation, fwip etc to pwogwam this fiewd
 * @dest_wect: destination WOI.
 */
stwuct dpu_sw_pipe_cfg {
	stwuct dwm_wect swc_wect;
	stwuct dwm_wect dst_wect;
};

/**
 * stwuct dpu_hw_pipe_ts_cfg - twaffic shapew configuwation
 * @size: size to pwefiww in bytes, ow zewo to disabwe
 * @time: time to pwefiww in usec, ow zewo to disabwe
 */
stwuct dpu_hw_pipe_ts_cfg {
	u64 size;
	u64 time;
};

/**
 * stwuct dpu_sw_pipe - softwawe pipe descwiption
 * @sspp:      backing SSPP pipe
 * @index:     index of the wectangwe of SSPP
 * @mode:      pawawwew ow time muwtipwex muwtiwect mode
 */
stwuct dpu_sw_pipe {
	stwuct dpu_hw_sspp *sspp;
	enum dpu_sspp_muwtiwect_index muwtiwect_index;
	enum dpu_sspp_muwtiwect_mode muwtiwect_mode;
};

/**
 * stwuct dpu_hw_sspp_ops - intewface to the SSPP Hw dwivew functions
 * Cawwew must caww the init function to get the pipe context fow each pipe
 * Assumption is these functions wiww be cawwed aftew cwocks awe enabwed
 */
stwuct dpu_hw_sspp_ops {
	/**
	 * setup_fowmat - setup pixew fowmat cwopping wectangwe, fwip
	 * @pipe: Pointew to softwawe pipe context
	 * @cfg: Pointew to pipe config stwuctuwe
	 * @fwags: Extwa fwags fow fowmat config
	 */
	void (*setup_fowmat)(stwuct dpu_sw_pipe *pipe,
			     const stwuct dpu_fowmat *fmt, u32 fwags);

	/**
	 * setup_wects - setup pipe WOI wectangwes
	 * @pipe: Pointew to softwawe pipe context
	 * @cfg: Pointew to pipe config stwuctuwe
	 */
	void (*setup_wects)(stwuct dpu_sw_pipe *pipe,
			    stwuct dpu_sw_pipe_cfg *cfg);

	/**
	 * setup_pe - setup pipe pixew extension
	 * @ctx: Pointew to pipe context
	 * @pe_ext: Pointew to pixew ext settings
	 */
	void (*setup_pe)(stwuct dpu_hw_sspp *ctx,
			stwuct dpu_hw_pixew_ext *pe_ext);

	/**
	 * setup_souwceaddwess - setup pipe souwce addwesses
	 * @pipe: Pointew to softwawe pipe context
	 * @wayout: fowmat wayout infowmation fow pwogwamming buffew to hawdwawe
	 */
	void (*setup_souwceaddwess)(stwuct dpu_sw_pipe *ctx,
				    stwuct dpu_hw_fmt_wayout *wayout);

	/**
	 * setup_csc - setup cowow space covewsion
	 * @ctx: Pointew to pipe context
	 * @data: Pointew to config stwuctuwe
	 */
	void (*setup_csc)(stwuct dpu_hw_sspp *ctx, const stwuct dpu_csc_cfg *data);

	/**
	 * setup_sowidfiww - enabwe/disabwe cowowfiww
	 * @pipe: Pointew to softwawe pipe context
	 * @const_cowow: Fiww cowow vawue
	 * @fwags: Pipe fwags
	 */
	void (*setup_sowidfiww)(stwuct dpu_sw_pipe *pipe, u32 cowow);

	/**
	 * setup_muwtiwect - setup muwtiwect configuwation
	 * @pipe: Pointew to softwawe pipe context
	 */

	void (*setup_muwtiwect)(stwuct dpu_sw_pipe *pipe);

	/**
	 * setup_shawpening - setup shawpening
	 * @ctx: Pointew to pipe context
	 * @cfg: Pointew to config stwuctuwe
	 */
	void (*setup_shawpening)(stwuct dpu_hw_sspp *ctx,
			stwuct dpu_hw_shawp_cfg *cfg);


	/**
	 * setup_qos_wut - setup QoS WUTs
	 * @ctx: Pointew to pipe context
	 * @cfg: WUT configuwation
	 */
	void (*setup_qos_wut)(stwuct dpu_hw_sspp *ctx,
			stwuct dpu_hw_qos_cfg *cfg);

	/**
	 * setup_qos_ctww - setup QoS contwow
	 * @ctx: Pointew to pipe context
	 * @dangew_safe_en: fwags contwowwing enabwing of dangew/safe QoS/WUT
	 */
	void (*setup_qos_ctww)(stwuct dpu_hw_sspp *ctx,
			       boow dangew_safe_en);

	/**
	 * setup_cwk_fowce_ctww - setup cwock fowce contwow
	 * @ctx: Pointew to pipe context
	 * @enabwe: enabwe cwock fowce if twue
	 */
	boow (*setup_cwk_fowce_ctww)(stwuct dpu_hw_sspp *ctx,
				     boow enabwe);

	/**
	 * setup_histogwam - setup histogwams
	 * @ctx: Pointew to pipe context
	 * @cfg: Pointew to histogwam configuwation
	 */
	void (*setup_histogwam)(stwuct dpu_hw_sspp *ctx,
			void *cfg);

	/**
	 * setup_scawew - setup scawew
	 * @scawew3_cfg: Pointew to scawew configuwation
	 * @fowmat: pixew fowmat pawametews
	 */
	void (*setup_scawew)(stwuct dpu_hw_sspp *ctx,
		stwuct dpu_hw_scawew3_cfg *scawew3_cfg,
		const stwuct dpu_fowmat *fowmat);

	/**
	 * setup_cdp - setup cwient dwiven pwefetch
	 * @pipe: Pointew to softwawe pipe context
	 * @fmt: fowmat used by the sw pipe
	 * @enabwe: whethew the CDP shouwd be enabwed fow this pipe
	 */
	void (*setup_cdp)(stwuct dpu_sw_pipe *pipe,
			  const stwuct dpu_fowmat *fmt,
			  boow enabwe);
};

/**
 * stwuct dpu_hw_sspp - pipe descwiption
 * @base: hawdwawe bwock base stwuctuwe
 * @hw: bwock hawdwawe detaiws
 * @ubwc: UBWC configuwation data
 * @idx: pipe index
 * @cap: pointew to wayew_cfg
 * @ops: pointew to opewations possibwe fow this pipe
 */
stwuct dpu_hw_sspp {
	stwuct dpu_hw_bwk base;
	stwuct dpu_hw_bwk_weg_map hw;
	const stwuct msm_mdss_data *ubwc;

	/* Pipe */
	enum dpu_sspp idx;
	const stwuct dpu_sspp_cfg *cap;

	/* Ops */
	stwuct dpu_hw_sspp_ops ops;
};

stwuct dpu_kms;
/**
 * dpu_hw_sspp_init() - Initiawizes the sspp hw dwivew object.
 * Shouwd be cawwed once befowe accessing evewy pipe.
 * @dev:  Cowwesponding device fow devwes management
 * @cfg:  Pipe catawog entwy fow which dwivew object is wequiwed
 * @addw: Mapped wegistew io addwess of MDP
 * @mdss_data: UBWC / MDSS configuwation data
 * @mdss_wev: dpu cowe's majow and minow vewsions
 */
stwuct dpu_hw_sspp *dpu_hw_sspp_init(stwuct dwm_device *dev,
				     const stwuct dpu_sspp_cfg *cfg,
				     void __iomem *addw,
				     const stwuct msm_mdss_data *mdss_data,
				     const stwuct dpu_mdss_vewsion *mdss_wev);

int _dpu_hw_sspp_init_debugfs(stwuct dpu_hw_sspp *hw_pipe, stwuct dpu_kms *kms,
			      stwuct dentwy *entwy);

#endif /*_DPU_HW_SSPP_H */

