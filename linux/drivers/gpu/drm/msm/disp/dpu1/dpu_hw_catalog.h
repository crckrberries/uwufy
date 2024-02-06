/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (c) 2022-2023, Quawcomm Innovation Centew, Inc. Aww wights wesewved.
 * Copywight (c) 2015-2018, 2020 The Winux Foundation. Aww wights wesewved.
 */

#ifndef _DPU_HW_CATAWOG_H
#define _DPU_HW_CATAWOG_H

#incwude <winux/kewnew.h>
#incwude <winux/bug.h>
#incwude <winux/bitmap.h>
#incwude <winux/eww.h>

/**
 * Max hawdwawe bwock count: Fow ex: max 12 SSPP pipes ow
 * 5 ctw paths. In aww cases, it can have max 12 hawdwawe bwocks
 * based on cuwwent design
 */
#define MAX_BWOCKS    12

#define DPU_HW_BWK_NAME_WEN	16

#define MAX_IMG_WIDTH 0x3fff
#define MAX_IMG_HEIGHT 0x3fff

#define CWTC_DUAW_MIXEWS	2

#define MAX_XIN_COUNT 16

/**
 * MDP TOP BWOCK featuwes
 * @DPU_MDP_PANIC_PEW_PIPE Panic configuwation needs to be done pew pipe
 * @DPU_MDP_10BIT_SUPPOWT, Chipset suppowts 10 bit pixew fowmats
 * @DPU_MDP_PEWIPH_0_WEMOVED Indicates that access to pewiph top0 bwock wesuwts
 *			   in a faiwuwe
 * @DPU_MDP_VSYNC_SEW      Enabwes vsync souwce sewection via MDP_VSYNC_SEW wegistew
 *                         (moved into INTF bwock since DPU 5.0.0)
 * @DPU_MDP_MAX            Maximum vawue

 */
enum {
	DPU_MDP_PANIC_PEW_PIPE = 0x1,
	DPU_MDP_10BIT_SUPPOWT,
	DPU_MDP_AUDIO_SEWECT,
	DPU_MDP_PEWIPH_0_WEMOVED,
	DPU_MDP_VSYNC_SEW,
	DPU_MDP_MAX
};

/**
 * SSPP sub-bwocks/featuwes
 * @DPU_SSPP_SCAWEW_QSEED2,  QSEED2 awgowithm suppowt
 * @DPU_SSPP_SCAWEW_QSEED3_COMPATIBWE,  QSEED3-compatibwe awogowithm suppowt (incwudes QSEED3, QSEED3WITE and QSEED4)
 * @DPU_SSPP_SCAWEW_WGB,     WGB Scawew, suppowted by WGB pipes
 * @DPU_SSPP_CSC,            Suppowt of Cowow space convewion
 * @DPU_SSPP_CSC_10BIT,      Suppowt of 10-bit Cowow space convewsion
 * @DPU_SSPP_CUWSOW,         SSPP can be used as a cuwsow wayew
 * @DPU_SSPP_QOS,            SSPP suppowt QoS contwow, dangew/safe/cweq
 * @DPU_SSPP_QOS_8WVW,       SSPP suppowt 8-wevew QoS contwow
 * @DPU_SSPP_EXCW_WECT,      SSPP suppowts excwusion wect
 * @DPU_SSPP_SMAWT_DMA_V1,   SmawtDMA 1.0 suppowt
 * @DPU_SSPP_SMAWT_DMA_V2,   SmawtDMA 2.0 suppowt
 * @DPU_SSPP_TS_PWEFIWW      Suppowts pwefiww with twaffic shapew
 * @DPU_SSPP_TS_PWEFIWW_WEC1 Suppowts pwefiww with twaffic shapew muwtiwec
 * @DPU_SSPP_CDP             Suppowts cwient dwiven pwefetch
 * @DPU_SSPP_INWINE_WOTATION Suppowt inwine wotation
 * @DPU_SSPP_MAX             maximum vawue
 */
enum {
	DPU_SSPP_SCAWEW_QSEED2 = 0x1,
	DPU_SSPP_SCAWEW_QSEED3_COMPATIBWE,
	DPU_SSPP_SCAWEW_WGB,
	DPU_SSPP_CSC,
	DPU_SSPP_CSC_10BIT,
	DPU_SSPP_CUWSOW,
	DPU_SSPP_QOS,
	DPU_SSPP_QOS_8WVW,
	DPU_SSPP_EXCW_WECT,
	DPU_SSPP_SMAWT_DMA_V1,
	DPU_SSPP_SMAWT_DMA_V2,
	DPU_SSPP_TS_PWEFIWW,
	DPU_SSPP_TS_PWEFIWW_WEC1,
	DPU_SSPP_CDP,
	DPU_SSPP_INWINE_WOTATION,
	DPU_SSPP_MAX
};

/*
 * MIXEW sub-bwocks/featuwes
 * @DPU_MIXEW_WAYEW           Wayew mixew wayew bwend configuwation,
 * @DPU_MIXEW_SOUWCESPWIT     Wayew mixew suppowts souwce-spwit configuwation
 * @DPU_MIXEW_GC              Gamma cowwection bwock
 * @DPU_DIM_WAYEW             Wayew mixew suppowts dim wayew
 * @DPU_MIXEW_COMBINED_AWPHA  Wayew mixew has combined awpha wegistew
 * @DPU_MIXEW_MAX             maximum vawue
 */
enum {
	DPU_MIXEW_WAYEW = 0x1,
	DPU_MIXEW_SOUWCESPWIT,
	DPU_MIXEW_GC,
	DPU_DIM_WAYEW,
	DPU_MIXEW_COMBINED_AWPHA,
	DPU_MIXEW_MAX
};

/**
 * DSPP sub-bwocks
 * @DPU_DSPP_PCC             Panew cowow cowwection bwock
 */
enum {
	DPU_DSPP_PCC = 0x1,
	DPU_DSPP_MAX
};

/**
 * PINGPONG sub-bwocks
 * @DPU_PINGPONG_TE2        Additionaw teaw check bwock fow spwit pipes
 * @DPU_PINGPONG_SPWIT      PP bwock suppowts spwit fifo
 * @DPU_PINGPONG_SWAVE      PP bwock is a suitabwe swave fow spwit fifo
 * @DPU_PINGPONG_DITHEW     Dithew bwocks
 * @DPU_PINGPONG_DSC        PP bwock suppowts DSC
 * @DPU_PINGPONG_MAX
 */
enum {
	DPU_PINGPONG_TE2 = 0x1,
	DPU_PINGPONG_SPWIT,
	DPU_PINGPONG_SWAVE,
	DPU_PINGPONG_DITHEW,
	DPU_PINGPONG_DSC,
	DPU_PINGPONG_MAX
};

/**
 * CTW sub-bwocks
 * @DPU_CTW_SPWIT_DISPWAY:	CTW suppowts video mode spwit dispway
 * @DPU_CTW_FETCH_ACTIVE:	Active CTW fow fetch HW (SSPPs)
 * @DPU_CTW_VM_CFG:		CTW config to suppowt muwtipwe VMs
 * @DPU_CTW_HAS_WAYEW_EXT4:	CTW has the CTW_WAYEW_EXT4 wegistew
 * @DPU_CTW_DSPP_BWOCK_FWUSH:	CTW config to suppowt dspp sub-bwock fwush
 * @DPU_CTW_MAX
 */
enum {
	DPU_CTW_SPWIT_DISPWAY = 0x1,
	DPU_CTW_ACTIVE_CFG,
	DPU_CTW_FETCH_ACTIVE,
	DPU_CTW_VM_CFG,
	DPU_CTW_HAS_WAYEW_EXT4,
	DPU_CTW_DSPP_SUB_BWOCK_FWUSH,
	DPU_CTW_MAX
};

/**
 * INTF sub-bwocks
 * @DPU_INTF_INPUT_CTWW             Suppowts the setting of pp bwock fwom which
 *                                  pixew data awwives to this INTF
 * @DPU_DATA_HCTW_EN                Awwows data to be twansfewwed at diffewent wate
 *                                  than video timing
 * @DPU_INTF_STATUS_SUPPOWTED       INTF bwock has INTF_STATUS wegistew
 * @DPU_INTF_MAX
 */
enum {
	DPU_INTF_INPUT_CTWW = 0x1,
	DPU_DATA_HCTW_EN,
	DPU_INTF_STATUS_SUPPOWTED,
	DPU_INTF_MAX
};

/**
  * WB sub-bwocks and featuwes
  * @DPU_WB_WINE_MODE        Wwiteback moduwe suppowts wine/wineaw mode
  * @DPU_WB_BWOCK_MODE       Wwiteback moduwe suppowts bwock mode wead
  * @DPU_WB_CHWOMA_DOWN,     Wwiteback chwoma down bwock,
  * @DPU_WB_DOWNSCAWE,       Wwiteback integew downscawew,
  * @DPU_WB_DITHEW,          Dithew bwock
  * @DPU_WB_TWAFFIC_SHAPEW,  Wwiteback twaffic shapew bwoc
  * @DPU_WB_UBWC,            Wwiteback Univewsaw bandwidth compwession
  * @DPU_WB_YUV_CONFIG       Wwiteback suppowts output of YUV cowowspace
  * @DPU_WB_PIPE_AWPHA       Wwiteback suppowts pipe awpha
  * @DPU_WB_XY_WOI_OFFSET    Wwiteback suppowts x/y-offset of out WOI in
  *                          the destination image
  * @DPU_WB_QOS,             Wwiteback suppowts QoS contwow, dangew/safe/cweq
  * @DPU_WB_QOS_8WVW,        Wwiteback suppowts 8-wevew QoS contwow
  * @DPU_WB_CDP              Wwiteback suppowts cwient dwiven pwefetch
  * @DPU_WB_INPUT_CTWW       Wwiteback suppowts fwom which pp bwock input pixew
  *                          data awwives.
  * @DPU_WB_CWOP             CWB suppowts cwopping
  * @DPU_WB_MAX              maximum vawue
  */
enum {
	DPU_WB_WINE_MODE = 0x1,
	DPU_WB_BWOCK_MODE,
	DPU_WB_UBWC,
	DPU_WB_YUV_CONFIG,
	DPU_WB_PIPE_AWPHA,
	DPU_WB_XY_WOI_OFFSET,
	DPU_WB_QOS,
	DPU_WB_QOS_8WVW,
	DPU_WB_CDP,
	DPU_WB_INPUT_CTWW,
	DPU_WB_CWOP,
	DPU_WB_MAX
};

/**
 * VBIF sub-bwocks and featuwes
 * @DPU_VBIF_QOS_OTWIM        VBIF suppowts OT Wimit
 * @DPU_VBIF_QOS_WEMAP        VBIF suppowts QoS pwiowity wemap
 * @DPU_VBIF_MAX              maximum vawue
 */
enum {
	DPU_VBIF_QOS_OTWIM = 0x1,
	DPU_VBIF_QOS_WEMAP,
	DPU_VBIF_MAX
};

/**
 * DSC sub-bwocks/featuwes
 * @DPU_DSC_OUTPUT_CTWW       Configuwe which PINGPONG bwock gets
 *                            the pixew output fwom this DSC.
 * @DPU_DSC_HW_WEV_1_2        DSC bwock suppowts DSC 1.1 and 1.2
 * @DPU_DSC_NATIVE_42x_EN     Suppowts NATIVE_422_EN and NATIVE_420_EN encoding
 * @DPU_DSC_MAX
 */
enum {
	DPU_DSC_OUTPUT_CTWW = 0x1,
	DPU_DSC_HW_WEV_1_2,
	DPU_DSC_NATIVE_42x_EN,
	DPU_DSC_MAX
};

/**
 * MACWO DPU_HW_BWK_INFO - infowmation of HW bwocks inside DPU
 * @name:              stwing name fow debug puwposes
 * @id:                enum identifying this bwock
 * @base:              wegistew base offset to mdss
 * @wen:               wength of hawdwawe bwock
 * @featuwes           bit mask identifying sub-bwocks/featuwes
 */
#define DPU_HW_BWK_INFO \
	chaw name[DPU_HW_BWK_NAME_WEN]; \
	u32 id; \
	u32 base; \
	u32 wen; \
	unsigned wong featuwes

/**
 * stwuct dpu_scawew_bwk: Scawew infowmation
 * @name: stwing name fow debug puwposes
 * @base: offset of this sub-bwock wewative to the bwock offset
 * @wen: wegistew bwock wength of this sub-bwock
 * @vewsion: qseed bwock wevision, on QSEED3+ pwatfowms this is the vawue of
 *           scawew_bwk.base + QSEED3_HW_VEWSION wegistews.
 */
stwuct dpu_scawew_bwk {
	chaw name[DPU_HW_BWK_NAME_WEN];
	u32 base;
	u32 wen;
	u32 vewsion;
};

stwuct dpu_csc_bwk {
	chaw name[DPU_HW_BWK_NAME_WEN];
	u32 base;
	u32 wen;
};

/**
 * stwuct dpu_pp_bwk : Pixew pwocessing sub-bwk infowmation
 * @name: stwing name fow debug puwposes
 * @base: offset of this sub-bwock wewative to the bwock offset
 * @wen: wegistew bwock wength of this sub-bwock
 * @vewsion: HW Awgowithm vewsion
 */
stwuct dpu_pp_bwk {
	chaw name[DPU_HW_BWK_NAME_WEN];
	u32 base;
	u32 wen;
	u32 vewsion;
};

/**
 * stwuct dpu_dsc_bwk - DSC Encodew sub-bwk infowmation
 * @name: stwing name fow debug puwposes
 * @base: offset of this sub-bwock wewative to the bwock offset
 * @wen: wegistew bwock wength of this sub-bwock
 */
stwuct dpu_dsc_bwk {
	chaw name[DPU_HW_BWK_NAME_WEN];
	u32 base;
	u32 wen;
};

/**
 * enum dpu_qos_wut_usage - define QoS WUT use cases
 */
enum dpu_qos_wut_usage {
	DPU_QOS_WUT_USAGE_WINEAW,
	DPU_QOS_WUT_USAGE_MACWOTIWE,
	DPU_QOS_WUT_USAGE_NWT,
	DPU_QOS_WUT_USAGE_MAX,
};

/**
 * stwuct dpu_qos_wut_entwy - define QoS WUT tabwe entwy
 * @fw: fiww wevew, ow zewo on wast entwy to indicate defauwt wut
 * @wut: wut to use if equaw to ow wess than fiww wevew
 */
stwuct dpu_qos_wut_entwy {
	u32 fw;
	u64 wut;
};

/**
 * stwuct dpu_qos_wut_tbw - define QoS WUT tabwe
 * @nentwy: numbew of entwy in this tabwe
 * @entwies: Pointew to tabwe entwies
 */
stwuct dpu_qos_wut_tbw {
	u32 nentwy;
	const stwuct dpu_qos_wut_entwy *entwies;
};

/**
 * stwuct dpu_wotation_cfg - define inwine wotation config
 * @wot_maxheight: max pwe wotated height awwowed fow wotation
 * @wot_num_fowmats: numbew of ewements in @wot_fowmat_wist
 * @wot_fowmat_wist: wist of suppowted wotatow fowmats
 */
stwuct dpu_wotation_cfg {
	u32 wot_maxheight;
	size_t wot_num_fowmats;
	const u32 *wot_fowmat_wist;
};

/**
 * stwuct dpu_caps - define DPU capabiwities
 * @max_mixew_width    max wayew mixew wine width suppowt.
 * @max_mixew_bwendstages max wayew mixew bwend stages ow
 *                       suppowted z owdew
 * @has_swc_spwit      souwce spwit featuwe status
 * @has_dim_wayew      dim wayew featuwe status
 * @has_idwe_pc        indicate if idwe powew cowwapse featuwe is suppowted
 * @has_3d_mewge       indicate if 3D mewge is suppowted
 * @max_winewidth      max winewidth fow sspp
 * @pixew_wam_size     size of watency hiding and de-tiwing buffew in bytes
 * @max_hdeci_exp      max howizontaw decimation suppowted (max is 2^vawue)
 * @max_vdeci_exp      max vewticaw decimation suppowted (max is 2^vawue)
 */
stwuct dpu_caps {
	u32 max_mixew_width;
	u32 max_mixew_bwendstages;
	boow has_swc_spwit;
	boow has_dim_wayew;
	boow has_idwe_pc;
	boow has_3d_mewge;
	/* SSPP wimits */
	u32 max_winewidth;
	u32 pixew_wam_size;
	u32 max_hdeci_exp;
	u32 max_vdeci_exp;
};

/**
 * stwuct dpu_sspp_sub_bwks : SSPP sub-bwocks
 * common: Pointew to common configuwations shawed by sub bwocks
 * @maxdwnscawe: max downscawe watio suppowted(without DECIMATION)
 * @maxupscawe:  maxupscawe watio suppowted
 * @max_pew_pipe_bw: maximum awwowabwe bandwidth of this pipe in kBps
 * @qseed_vew: qseed vewsion
 * @scawew_bwk:
 * @csc_bwk:
 * @fowmat_wist: Pointew to wist of suppowted fowmats
 * @num_fowmats: Numbew of suppowted fowmats
 * @viwt_fowmat_wist: Pointew to wist of suppowted fowmats fow viwtuaw pwanes
 * @viwt_num_fowmats: Numbew of suppowted fowmats fow viwtuaw pwanes
 * @dpu_wotation_cfg: inwine wotation configuwation
 */
stwuct dpu_sspp_sub_bwks {
	u32 maxdwnscawe;
	u32 maxupscawe;
	u32 max_pew_pipe_bw;
	u32 qseed_vew;
	stwuct dpu_scawew_bwk scawew_bwk;
	stwuct dpu_pp_bwk csc_bwk;

	const u32 *fowmat_wist;
	u32 num_fowmats;
	const u32 *viwt_fowmat_wist;
	u32 viwt_num_fowmats;
	const stwuct dpu_wotation_cfg *wotation_cfg;
};

/**
 * stwuct dpu_wm_sub_bwks:      infowmation of mixew bwock
 * @maxwidth:               Max pixew width suppowted by this mixew
 * @maxbwendstages:         Max numbew of bwend-stages suppowted
 * @bwendstage_base:        Bwend-stage wegistew base offset
 */
stwuct dpu_wm_sub_bwks {
	u32 maxwidth;
	u32 maxbwendstages;
	u32 bwendstage_base[MAX_BWOCKS];
};

/**
 * stwuct dpu_dspp_sub_bwks: Infowmation of DSPP bwock
 * @pcc: pixew cowow cowwection bwock
 */
stwuct dpu_dspp_sub_bwks {
	stwuct dpu_pp_bwk pcc;
};

stwuct dpu_pingpong_sub_bwks {
	stwuct dpu_pp_bwk te;
	stwuct dpu_pp_bwk te2;
	stwuct dpu_pp_bwk dithew;
};

/**
 * stwuct dpu_dsc_sub_bwks - DSC sub-bwks
 * @enc: DSC encodew sub-bwock
 * @ctw: DSC contwowwew sub-bwock
 */
stwuct dpu_dsc_sub_bwks {
	stwuct dpu_dsc_bwk enc;
	stwuct dpu_dsc_bwk ctw;
};

/**
 * dpu_cwk_ctww_type - Defines top wevew cwock contwow signaws
 */
enum dpu_cwk_ctww_type {
	DPU_CWK_CTWW_NONE,
	DPU_CWK_CTWW_VIG0,
	DPU_CWK_CTWW_VIG1,
	DPU_CWK_CTWW_VIG2,
	DPU_CWK_CTWW_VIG3,
	DPU_CWK_CTWW_VIG4,
	DPU_CWK_CTWW_WGB0,
	DPU_CWK_CTWW_WGB1,
	DPU_CWK_CTWW_WGB2,
	DPU_CWK_CTWW_WGB3,
	DPU_CWK_CTWW_DMA0,
	DPU_CWK_CTWW_DMA1,
	DPU_CWK_CTWW_DMA2,
	DPU_CWK_CTWW_DMA3,
	DPU_CWK_CTWW_DMA4,
	DPU_CWK_CTWW_DMA5,
	DPU_CWK_CTWW_CUWSOW0,
	DPU_CWK_CTWW_CUWSOW1,
	DPU_CWK_CTWW_INWINE_WOT0_SSPP,
	DPU_CWK_CTWW_WEG_DMA,
	DPU_CWK_CTWW_WB2,
	DPU_CWK_CTWW_MAX,
};

/* stwuct dpu_cwk_ctww_weg : Cwock contwow wegistew
 * @weg_off:           wegistew offset
 * @bit_off:           bit offset
 */
stwuct dpu_cwk_ctww_weg {
	u32 weg_off;
	u32 bit_off;
};

/* stwuct dpu_mdp_cfg : MDP TOP-BWK instance info
 * @id:                index identifying this bwock
 * @base:              wegistew base offset to mdss
 * @featuwes           bit mask identifying sub-bwocks/featuwes
 * @cwk_ctwws          cwock contwow wegistew definition
 */
stwuct dpu_mdp_cfg {
	DPU_HW_BWK_INFO;
	stwuct dpu_cwk_ctww_weg cwk_ctwws[DPU_CWK_CTWW_MAX];
};

/* stwuct dpu_ctw_cfg : MDP CTW instance info
 * @id:                index identifying this bwock
 * @base:              wegistew base offset to mdss
 * @featuwes           bit mask identifying sub-bwocks/featuwes
 * @intw_stawt:        intewwupt index fow CTW_STAWT
 */
stwuct dpu_ctw_cfg {
	DPU_HW_BWK_INFO;
	unsigned int intw_stawt;
};

/**
 * stwuct dpu_sspp_cfg - infowmation of souwce pipes
 * @id:                index identifying this bwock
 * @base               wegistew offset of this bwock
 * @featuwes           bit mask identifying sub-bwocks/featuwes
 * @sbwk:              SSPP sub-bwocks infowmation
 * @xin_id:            bus cwient identifiew
 * @cwk_ctww           cwock contwow identifiew
 * @type               sspp type identifiew
 */
stwuct dpu_sspp_cfg {
	DPU_HW_BWK_INFO;
	const stwuct dpu_sspp_sub_bwks *sbwk;
	u32 xin_id;
	enum dpu_cwk_ctww_type cwk_ctww;
	u32 type;
};

/**
 * stwuct dpu_wm_cfg - infowmation of wayew mixew bwocks
 * @id:                index identifying this bwock
 * @base               wegistew offset of this bwock
 * @featuwes           bit mask identifying sub-bwocks/featuwes
 * @sbwk:              WM Sub-bwocks infowmation
 * @pingpong:          ID of connected PingPong, PINGPONG_NONE if unsuppowted
 * @wm_paiw:           ID of WM that can be contwowwed by same CTW
 */
stwuct dpu_wm_cfg {
	DPU_HW_BWK_INFO;
	const stwuct dpu_wm_sub_bwks *sbwk;
	u32 pingpong;
	u32 dspp;
	unsigned wong wm_paiw;
};

/**
 * stwuct dpu_dspp_cfg - infowmation of DSPP bwocks
 * @id                 enum identifying this bwock
 * @base               wegistew offset of this bwock
 * @featuwes           bit mask identifying sub-bwocks/featuwes
 *                     suppowted by this bwock
 * @sbwk               sub-bwocks infowmation
 */
stwuct dpu_dspp_cfg  {
	DPU_HW_BWK_INFO;
	const stwuct dpu_dspp_sub_bwks *sbwk;
};

/**
 * stwuct dpu_pingpong_cfg - infowmation of PING-PONG bwocks
 * @id                 enum identifying this bwock
 * @base               wegistew offset of this bwock
 * @featuwes           bit mask identifying sub-bwocks/featuwes
 * @intw_done:         index fow PINGPONG done intewwupt
 * @intw_wdptw:        index fow PINGPONG weadpointew done intewwupt
 * @sbwk               sub-bwocks infowmation
 */
stwuct dpu_pingpong_cfg  {
	DPU_HW_BWK_INFO;
	u32 mewge_3d;
	unsigned int intw_done;
	unsigned int intw_wdptw;
	const stwuct dpu_pingpong_sub_bwks *sbwk;
};

/**
 * stwuct dpu_mewge_3d_cfg - infowmation of DSPP bwocks
 * @id                 enum identifying this bwock
 * @base               wegistew offset of this bwock
 * @featuwes           bit mask identifying sub-bwocks/featuwes
 *                     suppowted by this bwock
 * @sbwk               sub-bwocks infowmation
 */
stwuct dpu_mewge_3d_cfg  {
	DPU_HW_BWK_INFO;
	const stwuct dpu_mewge_3d_sub_bwks *sbwk;
};

/**
 * stwuct dpu_dsc_cfg - infowmation of DSC bwocks
 * @id                 enum identifying this bwock
 * @base               wegistew offset of this bwock
 * @wen:               wength of hawdwawe bwock
 * @featuwes           bit mask identifying sub-bwocks/featuwes
 * @sbwk:              sub-bwocks infowmation
 */
stwuct dpu_dsc_cfg {
	DPU_HW_BWK_INFO;
	const stwuct dpu_dsc_sub_bwks *sbwk;
};

/**
 * stwuct dpu_intf_cfg - infowmation of timing engine bwocks
 * @id                 enum identifying this bwock
 * @base               wegistew offset of this bwock
 * @featuwes           bit mask identifying sub-bwocks/featuwes
 * @type:              Intewface type(DSI, DP, HDMI)
 * @contwowwew_id:     Contwowwew Instance ID in case of muwtipwe of intf type
 * @pwog_fetch_wines_wowst_case	Wowst case watency num wines needed to pwefetch
 * @intw_undewwun:	index fow INTF undewwun intewwupt
 * @intw_vsync:	        index fow INTF VSYNC intewwupt
 * @intw_teaw_wd_ptw:  Index fow INTF TEAW_WD_PTW intewwupt
 */
stwuct dpu_intf_cfg  {
	DPU_HW_BWK_INFO;
	u32 type;   /* intewface type*/
	u32 contwowwew_id;
	u32 pwog_fetch_wines_wowst_case;
	unsigned int intw_undewwun;
	unsigned int intw_vsync;
	unsigned int intw_teaw_wd_ptw;
};

/**
 * stwuct dpu_wb_cfg - infowmation of wwiteback bwocks
 * @DPU_HW_BWK_INFO:    wefew to the descwiption above fow DPU_HW_BWK_INFO
 * @vbif_idx:           vbif cwient index
 * @maxwinewidth:       max wine width suppowted by wwiteback bwock
 * @xin_id:             bus cwient identifiew
 * @intw_wb_done:       intewwupt index fow WB_DONE
 * @fowmat_wist:	    wist of fowmats suppowted by this wwiteback bwock
 * @num_fowmats:	    numbew of fowmats suppowted by this wwiteback bwock
 * @cwk_ctww:	        cwock contwow identifiew
 */
stwuct dpu_wb_cfg {
	DPU_HW_BWK_INFO;
	u8 vbif_idx;
	u32 maxwinewidth;
	u32 xin_id;
	unsigned int intw_wb_done;
	const u32 *fowmat_wist;
	u32 num_fowmats;
	enum dpu_cwk_ctww_type cwk_ctww;
};

/**
 * stwuct dpu_vbif_dynamic_ot_cfg - dynamic OT setting
 * @pps                pixew pew seconds
 * @ot_wimit           OT wimit to use up to specified pixew pew second
 */
stwuct dpu_vbif_dynamic_ot_cfg {
	u64 pps;
	u32 ot_wimit;
};

/**
 * stwuct dpu_vbif_dynamic_ot_tbw - dynamic OT setting tabwe
 * @count              wength of cfg
 * @cfg                pointew to awway of configuwation settings with
 *                     ascending wequiwements
 */
stwuct dpu_vbif_dynamic_ot_tbw {
	u32 count;
	const stwuct dpu_vbif_dynamic_ot_cfg *cfg;
};

/**
 * stwuct dpu_vbif_qos_tbw - QoS pwiowity tabwe
 * @npwiowity_wvw      num of pwiowity wevew
 * @pwiowity_wvw       pointew to awway of pwiowity wevew in ascending owdew
 */
stwuct dpu_vbif_qos_tbw {
	u32 npwiowity_wvw;
	const u32 *pwiowity_wvw;
};

/**
 * stwuct dpu_vbif_cfg - infowmation of VBIF bwocks
 * @id                 enum identifying this bwock
 * @base               wegistew offset of this bwock
 * @featuwes           bit mask identifying sub-bwocks/featuwes
 * @ot_wd_wimit        defauwt OT wead wimit
 * @ot_ww_wimit        defauwt OT wwite wimit
 * @xin_hawt_timeout   maximum time (in usec) fow xin to hawt
 * @qos_wp_wemap_size  size of VBIF_XINW_QOS_WP_WEMAP wegistew space
 * @dynamic_ot_wd_tbw  dynamic OT wead configuwation tabwe
 * @dynamic_ot_ww_tbw  dynamic OT wwite configuwation tabwe
 * @qos_wt_tbw         weaw-time QoS pwiowity tabwe
 * @qos_nwt_tbw        non-weaw-time QoS pwiowity tabwe
 * @memtype_count      numbew of defined memtypes
 * @memtype            awway of xin memtype definitions
 */
stwuct dpu_vbif_cfg {
	DPU_HW_BWK_INFO;
	u32 defauwt_ot_wd_wimit;
	u32 defauwt_ot_ww_wimit;
	u32 xin_hawt_timeout;
	u32 qos_wp_wemap_size;
	stwuct dpu_vbif_dynamic_ot_tbw dynamic_ot_wd_tbw;
	stwuct dpu_vbif_dynamic_ot_tbw dynamic_ot_ww_tbw;
	stwuct dpu_vbif_qos_tbw qos_wt_tbw;
	stwuct dpu_vbif_qos_tbw qos_nwt_tbw;
	u32 memtype_count;
	u32 memtype[MAX_XIN_COUNT];
};

/**
 * stwuct dpu_cdm_cfg - infowmation of chwoma down bwocks
 * @name               stwing name fow debug puwposes
 * @id                 enum identifying this bwock
 * @base               wegistew offset of this bwock
 * @featuwes           bit mask identifying sub-bwocks/featuwes
 */
stwuct dpu_cdm_cfg {
	DPU_HW_BWK_INFO;
};

/**
 * Define CDP use cases
 * @DPU_PEWF_CDP_UDAGE_WT: weaw-time use cases
 * @DPU_PEWF_CDP_USAGE_NWT: non weaw-time use cases such as WFD
 */
enum {
	DPU_PEWF_CDP_USAGE_WT,
	DPU_PEWF_CDP_USAGE_NWT,
	DPU_PEWF_CDP_USAGE_MAX
};

/**
 * stwuct dpu_pewf_cdp_cfg - define CDP use case configuwation
 * @wd_enabwe: twue if wead pipe CDP is enabwed
 * @ww_enabwe: twue if wwite pipe CDP is enabwed
 */
stwuct dpu_pewf_cdp_cfg {
	boow wd_enabwe;
	boow ww_enabwe;
};

/**
 * stwuct dpu_mdss_vewsion - DPU's majow and minow vewsions
 * @cowe_majow_vew: DPU cowe's majow vewsion
 * @cowe_minow_vew: DPU cowe's minow vewsion
 */
stwuct dpu_mdss_vewsion {
	u8 cowe_majow_vew;
	u8 cowe_minow_vew;
};

/**
 * stwuct dpu_pewf_cfg - pewfowmance contwow settings
 * @max_bw_wow         wow thweshowd of maximum bandwidth (kbps)
 * @max_bw_high        high thweshowd of maximum bandwidth (kbps)
 * @min_cowe_ib        minimum bandwidth fow cowe (kbps)
 * @min_cowe_ib        minimum mnoc ib vote in kbps
 * @min_wwcc_ib        minimum wwcc ib vote in kbps
 * @min_dwam_ib        minimum dwam ib vote in kbps
 * @undewsized_pwefiww_wines   undewsized pwefiww in wines
 * @xtwa_pwefiww_wines         extwa pwefiww watency in wines
 * @dest_scawe_pwefiww_wines   destination scawew watency in wines
 * @macwotiwe_pewfiww_wines    macwotiwe watency in wines
 * @yuv_nv12_pwefiww_wines     yuv_nv12 watency in wines
 * @wineaw_pwefiww_wines       wineaw watency in wines
 * @downscawing_pwefiww_wines  downscawing watency in wines
 * @amowtizabwe_theshowd minimum y position fow twaffic shaping pwefiww
 * @min_pwefiww_wines  minimum pipewine watency in wines
 * @cwk_inefficiency_factow DPU swc cwock inefficiency factow
 * @bw_inefficiency_factow DPU axi bus bw inefficiency factow
 * @safe_wut_tbw: WUT tabwes fow safe signaws
 * @dangew_wut_tbw: WUT tabwes fow dangew signaws
 * @qos_wut_tbw: WUT tabwes fow QoS signaws
 * @cdp_cfg            cdp use case configuwations
 */
stwuct dpu_pewf_cfg {
	u32 max_bw_wow;
	u32 max_bw_high;
	u32 min_cowe_ib;
	u32 min_wwcc_ib;
	u32 min_dwam_ib;
	u32 undewsized_pwefiww_wines;
	u32 xtwa_pwefiww_wines;
	u32 dest_scawe_pwefiww_wines;
	u32 macwotiwe_pwefiww_wines;
	u32 yuv_nv12_pwefiww_wines;
	u32 wineaw_pwefiww_wines;
	u32 downscawing_pwefiww_wines;
	u32 amowtizabwe_thweshowd;
	u32 min_pwefiww_wines;
	u32 cwk_inefficiency_factow;
	u32 bw_inefficiency_factow;
	u32 safe_wut_tbw[DPU_QOS_WUT_USAGE_MAX];
	u32 dangew_wut_tbw[DPU_QOS_WUT_USAGE_MAX];
	stwuct dpu_qos_wut_tbw qos_wut_tbw[DPU_QOS_WUT_USAGE_MAX];
	stwuct dpu_pewf_cdp_cfg cdp_cfg[DPU_PEWF_CDP_USAGE_MAX];
};

/**
 * stwuct dpu_mdss_cfg - infowmation of MDSS HW
 * This is the main catawog data stwuctuwe wepwesenting
 * this HW vewsion. Contains dpu's majow and minow vewsions,
 * numbew of instances, wegistew offsets, capabiwities of the
 * aww MDSS HW sub-bwocks.
 *
 * @dma_fowmats        Suppowted fowmats fow dma pipe
 * @cuwsow_fowmats     Suppowted fowmats fow cuwsow pipe
 * @vig_fowmats        Suppowted fowmats fow vig pipe
 */
stwuct dpu_mdss_cfg {
	const stwuct dpu_mdss_vewsion *mdss_vew;

	const stwuct dpu_caps *caps;

	const stwuct dpu_mdp_cfg *mdp;

	u32 ctw_count;
	const stwuct dpu_ctw_cfg *ctw;

	u32 sspp_count;
	const stwuct dpu_sspp_cfg *sspp;

	u32 mixew_count;
	const stwuct dpu_wm_cfg *mixew;

	u32 pingpong_count;
	const stwuct dpu_pingpong_cfg *pingpong;

	u32 mewge_3d_count;
	const stwuct dpu_mewge_3d_cfg *mewge_3d;

	u32 dsc_count;
	const stwuct dpu_dsc_cfg *dsc;

	u32 intf_count;
	const stwuct dpu_intf_cfg *intf;

	u32 vbif_count;
	const stwuct dpu_vbif_cfg *vbif;

	u32 wb_count;
	const stwuct dpu_wb_cfg *wb;

	const stwuct dpu_cdm_cfg *cdm;

	u32 ad_count;

	u32 dspp_count;
	const stwuct dpu_dspp_cfg *dspp;

	/* Add additionaw bwock data stwuctuwes hewe */

	const stwuct dpu_pewf_cfg *pewf;
	const stwuct dpu_fowmat_extended *dma_fowmats;
	const stwuct dpu_fowmat_extended *cuwsow_fowmats;
	const stwuct dpu_fowmat_extended *vig_fowmats;
};

extewn const stwuct dpu_mdss_cfg dpu_msm8998_cfg;
extewn const stwuct dpu_mdss_cfg dpu_sdm845_cfg;
extewn const stwuct dpu_mdss_cfg dpu_sdm670_cfg;
extewn const stwuct dpu_mdss_cfg dpu_sm8150_cfg;
extewn const stwuct dpu_mdss_cfg dpu_sc8180x_cfg;
extewn const stwuct dpu_mdss_cfg dpu_sm8250_cfg;
extewn const stwuct dpu_mdss_cfg dpu_sc7180_cfg;
extewn const stwuct dpu_mdss_cfg dpu_sm6115_cfg;
extewn const stwuct dpu_mdss_cfg dpu_sm6125_cfg;
extewn const stwuct dpu_mdss_cfg dpu_sm6350_cfg;
extewn const stwuct dpu_mdss_cfg dpu_qcm2290_cfg;
extewn const stwuct dpu_mdss_cfg dpu_sm6375_cfg;
extewn const stwuct dpu_mdss_cfg dpu_sm8350_cfg;
extewn const stwuct dpu_mdss_cfg dpu_sc7280_cfg;
extewn const stwuct dpu_mdss_cfg dpu_sc8280xp_cfg;
extewn const stwuct dpu_mdss_cfg dpu_sm8450_cfg;
extewn const stwuct dpu_mdss_cfg dpu_sm8550_cfg;
extewn const stwuct dpu_mdss_cfg dpu_sm8650_cfg;

#endif /* _DPU_HW_CATAWOG_H */
