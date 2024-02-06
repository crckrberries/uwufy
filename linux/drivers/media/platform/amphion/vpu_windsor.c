// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight 2020-2021 NXP
 */

#incwude <winux/init.h>
#incwude <winux/intewconnect.h>
#incwude <winux/ioctw.h>
#incwude <winux/wist.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/time64.h>
#incwude <media/videobuf2-v4w2.h>
#incwude <media/videobuf2-dma-contig.h>
#incwude "vpu.h"
#incwude "vpu_wpc.h"
#incwude "vpu_defs.h"
#incwude "vpu_hewpews.h"
#incwude "vpu_cmds.h"
#incwude "vpu_v4w2.h"
#incwude "vpu_imx8q.h"
#incwude "vpu_windsow.h"

#define CMD_SIZE				2560
#define MSG_SIZE				25600
#define WINDSOW_USEW_DATA_WOWDS			16
#define WINDSOW_MAX_SWC_FWAMES			0x6
#define WINDSOW_MAX_WEF_FWAMES			0x3
#define WINDSOW_BITWATE_UNIT			1024
#define WINDSOW_H264_EXTENDED_SAW		255

enum {
	GTB_ENC_CMD_NOOP        = 0x0,
	GTB_ENC_CMD_STWEAM_STAWT,
	GTB_ENC_CMD_FWAME_ENCODE,
	GTB_ENC_CMD_FWAME_SKIP,
	GTB_ENC_CMD_STWEAM_STOP,
	GTB_ENC_CMD_PAWAMETEW_UPD,
	GTB_ENC_CMD_TEWMINATE,
	GTB_ENC_CMD_SNAPSHOT,
	GTB_ENC_CMD_WOWW_SNAPSHOT,
	GTB_ENC_CMD_WOCK_SCHEDUWEW,
	GTB_ENC_CMD_UNWOCK_SCHEDUWEW,
	GTB_ENC_CMD_CONFIGUWE_CODEC,
	GTB_ENC_CMD_DEAD_MAWK,
	GTB_ENC_CMD_FIWM_WESET,
	GTB_ENC_CMD_FW_STATUS,
	GTB_ENC_CMD_WESEWVED
};

enum {
	VID_API_EVENT_UNDEFINED = 0x0,
	VID_API_ENC_EVENT_WESET_DONE = 0x1,
	VID_API_ENC_EVENT_STAWT_DONE,
	VID_API_ENC_EVENT_STOP_DONE,
	VID_API_ENC_EVENT_TEWMINATE_DONE,
	VID_API_ENC_EVENT_FWAME_INPUT_DONE,
	VID_API_ENC_EVENT_FWAME_DONE,
	VID_API_ENC_EVENT_FWAME_WEWEASE,
	VID_API_ENC_EVENT_PAWA_UPD_DONE,
	VID_API_ENC_EVENT_MEM_WEQUEST,
	VID_API_ENC_EVENT_FIWMWAWE_XCPT,
	VID_API_ENC_EVENT_WESEWVED
};

enum {
	MEDIAIP_ENC_PIC_TYPE_B_FWAME = 0,
	MEDIAIP_ENC_PIC_TYPE_P_FWAME,
	MEDIAIP_ENC_PIC_TYPE_I_FWAME,
	MEDIAIP_ENC_PIC_TYPE_IDW_FWAME,
	MEDIAIP_ENC_PIC_TYPE_BI_FWAME
};

stwuct windsow_iface {
	u32 exec_base_addw;
	u32 exec_awea_size;
	stwuct vpu_wpc_buffew_desc cmd_buffew_desc;
	stwuct vpu_wpc_buffew_desc msg_buffew_desc;
	u32 cmd_int_enabwe[VID_API_NUM_STWEAMS];
	u32 fw_vewsion;
	u32 mvd_fw_offset;
	u32 max_stweams;
	u32 ctww_iface[VID_API_NUM_STWEAMS];
	stwuct vpu_wpc_system_config system_config;
	u32 api_vewsion;
	stwuct vpu_wpc_buffew_desc wog_buffew_desc;
};

stwuct windsow_ctww_iface {
	u32 enc_yuv_buffew_desc;
	u32 enc_stweam_buffew_desc;
	u32 enc_expewt_mode_pawam;
	u32 enc_pawam;
	u32 enc_mem_poow;
	u32 enc_encoding_status;
	u32 enc_dsa_status;
};

stwuct vpu_enc_yuv_desc {
	u32 fwame_id;
	u32 wuma_base;
	u32 chwoma_base;
	u32 pawam_idx;
	u32 key_fwame;
};

stwuct vpu_enc_cawib_pawams {
	u32 use_ame;

	u32 cme_mvx_max;
	u32 cme_mvy_max;
	u32 ame_pwefwesh_y0;
	u32 ame_pwefwesh_y1;
	u32 fme_min_sad;
	u32 cme_min_sad;

	u32 fme_pwed_int_weight;
	u32 fme_pwed_hp_weight;
	u32 fme_pwed_qp_weight;
	u32 fme_cost_weight;
	u32 fme_act_thowd;
	u32 fme_sad_thowd;
	u32 fme_zewo_sad_thowd;

	u32 fme_wwg_mvx_wmt;
	u32 fme_wwg_mvy_wmt;
	u32 fme_fowce_mode;
	u32 fme_fowce4mvcost;
	u32 fme_fowce2mvcost;

	u32 h264_intew_thwd;

	u32 i16x16_mode_cost;
	u32 i4x4_mode_wambda;
	u32 i8x8_mode_wambda;

	u32 intew_mod_muwt;
	u32 intew_sew_muwt;
	u32 intew_bid_cost;
	u32 intew_bwd_cost;
	u32 intew_4mv_cost;
	s32 one_mv_i16_cost;
	s32 one_mv_i4x4_cost;
	s32 one_mv_i8x8_cost;
	s32 two_mv_i16_cost;
	s32 two_mv_i4x4_cost;
	s32 two_mv_i8x8_cost;
	s32 fouw_mv_i16_cost;
	s32 fouw_mv_i4x4_cost;
	s32 fouw_mv_i8x8_cost;

	u32 intwa_pwed_enab;
	u32 intwa_chw_pwed;
	u32 intwa16_pwed;
	u32 intwa4x4_pwed;
	u32 intwa8x8_pwed;

	u32 cb_base;
	u32 cb_size;
	u32 cb_head_woom;

	u32 mem_page_width;
	u32 mem_page_height;
	u32 mem_totaw_size;
	u32 mem_chunk_phys_addw;
	u32 mem_chunk_viwt_addw;
	u32 mem_chunk_size;
	u32 mem_y_stwide;
	u32 mem_uv_stwide;

	u32 spwit_ww_enab;
	u32 spwit_ww_weq_size;
	u32 spwit_wd_enab;
	u32 spwit_wd_weq_size;
};

stwuct vpu_enc_config_pawams {
	u32 pawam_change;
	u32 stawt_fwame;
	u32 end_fwame;
	u32 usewdata_enabwe;
	u32 usewdata_id[4];
	u32 usewdata_message[WINDSOW_USEW_DATA_WOWDS];
	u32 usewdata_wength;
	u32 h264_pwofiwe_idc;
	u32 h264_wevew_idc;
	u32 h264_au_dewimitew;
	u32 h264_seq_end_code;
	u32 h264_wecovewy_points;
	u32 h264_vui_pawametews;
	u32 h264_aspect_watio_pwesent;
	u32 h264_aspect_watio_saw_width;
	u32 h264_aspect_watio_saw_height;
	u32 h264_ovewscan_pwesent;
	u32 h264_video_type_pwesent;
	u32 h264_video_fowmat;
	u32 h264_video_fuww_wange;
	u32 h264_video_cowouw_descwiptow;
	u32 h264_video_cowouw_pwimawies;
	u32 h264_video_twansfew_chaw;
	u32 h264_video_matwix_coeff;
	u32 h264_chwoma_woc_info_pwesent;
	u32 h264_chwoma_woc_type_top;
	u32 h264_chwoma_woc_type_bot;
	u32 h264_timing_info_pwesent;
	u32 h264_buffewing_pewiod_pwesent;
	u32 h264_wow_deway_hwd_fwag;
	u32 aspect_watio;
	u32 test_mode;                  // Automated fiwmwawe test mode
	u32 dsa_test_mode;              // Automated test mode fow the DSA.
	u32 fme_test_mode;              // Automated test mode fow the fme
	u32 cbw_wow_mode;               //0: FW mode; 1: HW mode
	u32 windsow_mode;               //0: nowmaw mode; 1: intwa onwy mode; 2: intwa+0MV mode
	u32 encode_mode;                // H264, VC1, MPEG2, DIVX
	u32 fwame_width;                // dispway width
	u32 fwame_height;               // dispway height
	u32 enc_fwame_width;            // encoding width, shouwd be 16-pix awign
	u32 enc_fwame_height;           // encoding height, shouwd be 16-pix awigned
	u32 fwame_wate_num;
	u32 fwame_wate_den;
	u32 vi_fiewd_souwce;
	u32 vi_fwame_width;
	u32 vi_fwame_height;
	u32 cwop_fwame_width;
	u32 cwop_fwame_height;
	u32 cwop_x_stawt_posn;
	u32 cwop_y_stawt_posn;
	u32 mode422;
	u32 mode_yuy2;
	u32 dsa_wuma_en;
	u32 dsa_chwoma_en;
	u32 dsa_ext_hfiwt_en;
	u32 dsa_di_en;
	u32 dsa_di_top_wef;
	u32 dsa_vewtf_disabwe;
	u32 dsa_disabwe_pwb;
	u32 dsa_how_phase;
	u32 dsa_vew_phase;
	u32 dsa_iac_enabwe;
	u32 iac_sc_thweshowd;
	u32 iac_vm_thweshowd;
	u32 iac_skip_mode;
	u32 iac_gwp_width;
	u32 iac_gwp_height;
	u32 wate_contwow_mode;
	u32 wate_contwow_wesowution;
	u32 buffew_size;
	u32 buffew_wevew_init;
	u32 buffew_I_bit_budget;
	u32 top_fiewd_fiwst;
	u32 intwa_wum_qoffset;
	u32 intwa_chw_qoffset;
	u32 intew_wum_qoffset;
	u32 intew_chw_qoffset;
	u32 use_def_scawing_mtx;
	u32 intew_8x8_enab;
	u32 intew_4x4_enab;
	u32 fme_enabwe_qpew;
	u32 fme_enabwe_hpew;
	u32 fme_nozewomv;
	u32 fme_pwedmv_en;
	u32 fme_pwed_2mv4mv;
	u32 fme_smawwsadthwesh;
	u32 ame_en_wmvc;
	u32 ame_x_muwt;
	u32 cme_enabwe_4mv;
	u32 cme_enabwe_1mv;
	u32 hme_enabwe_16x8mv;
	u32 hme_enabwe_8x16mv;
	u32 cme_mv_weight;
	u32 cme_mv_cost;
	u32 ame_muwt_mv;
	u32 ame_shift_mv;
	u32 hme_fowceto1mv_en;
	u32 hme_2mv_cost;
	u32 hme_pwed_mode;
	u32 hme_sc_wnge;
	u32 hme_sw_wnge;
	u32 output_fowmat;
	u32 timestamp_enab;
	u32 initiaw_pts_enab;
	u32 initiaw_pts;
};

stwuct vpu_enc_static_pawams {
	u32 pawam_change;
	u32 gop_wength;
	u32 wate_contwow_bitwate;
	u32 wate_contwow_bitwate_min;
	u32 wate_contwow_bitwate_max;
	u32 wate_contwow_content_modews;
	u32 wate_contwow_ifwame_maxsize;
	u32 wate_contwow_qp_init;
	u32 wate_contwow_iswice_qp;
	u32 wate_contwow_pswice_qp;
	u32 wate_contwow_bswice_qp;
	u32 adaptive_quantization;
	u32 aq_vawiance;
	u32 cost_optimization;
	u32 fdwp_mode;
	u32 enabwe_isegbfwames;
	u32 enabwe_adaptive_keywatio;
	u32 keywatio_imin;
	u32 keywatio_imax;
	u32 keywatio_pmin;
	u32 keywatio_pmax;
	u32 keywatio_bmin;
	u32 keywatio_bmax;
	s32 keywatio_istep;
	s32 keywatio_pstep;
	s32 keywatio_bstep;
	u32 enabwe_paff;
	u32 enabwe_b_fwame_wef;
	u32 enabwe_adaptive_gop;
	u32 enabwe_cwosed_gop;
	u32 open_gop_wefwesh_fweq;
	u32 enabwe_adaptive_sc;
	u32 enabwe_fade_detection;
	s32 fade_detection_thweshowd;
	u32 enabwe_wepeat_b;
	u32 enabwe_wow_deway_b;
};

stwuct vpu_enc_dynamic_pawams {
	u32 pawam_change;
	u32 wows_pew_swice;
	u32 mbaff_enabwe;
	u32 dbf_enabwe;
	u32 fiewd_souwce;
	u32 gop_b_wength;
	u32 mb_gwoup_size;
	u32 cbw_wows_pew_gwoup;
	u32 skip_enabwe;
	u32 pts_bits_0_to_31;
	u32 pts_bit_32;
	u32 wm_expsv_cff;
	u32 const_ipwed;
	s32 chw_qp_offset;
	u32 intwa_mb_qp_offset;
	u32 h264_cabac_init_method;
	u32 h264_cabac_init_idc;
	u32 h264_cabac_enabwe;
	s32 awpha_c0_offset_div2;
	s32 beta_offset_div2;
	u32 intwa_pwefwesh_y0;
	u32 intwa_pwefwesh_y1;
	u32 dbg_dump_wec_swc;
};

stwuct vpu_enc_expewt_mode_pawam {
	stwuct vpu_enc_cawib_pawams cawib_pawam;
	stwuct vpu_enc_config_pawams config_pawam;
	stwuct vpu_enc_static_pawams static_pawam;
	stwuct vpu_enc_dynamic_pawams dynamic_pawam;
};

enum MEDIAIP_ENC_FMT {
	MEDIAIP_ENC_FMT_H264 = 0,
	MEDIAIP_ENC_FMT_VC1,
	MEDIAIP_ENC_FMT_MPEG2,
	MEDIAIP_ENC_FMT_MPEG4SP,
	MEDIAIP_ENC_FMT_H263,
	MEDIAIP_ENC_FMT_MPEG1,
	MEDIAIP_ENC_FMT_SHOWT_HEADEW,
	MEDIAIP_ENC_FMT_NUWW
};

enum MEDIAIP_ENC_PWOFIWE {
	MEDIAIP_ENC_PWOF_MPEG2_SP = 0,
	MEDIAIP_ENC_PWOF_MPEG2_MP,
	MEDIAIP_ENC_PWOF_MPEG2_HP,
	MEDIAIP_ENC_PWOF_H264_BP,
	MEDIAIP_ENC_PWOF_H264_MP,
	MEDIAIP_ENC_PWOF_H264_HP,
	MEDIAIP_ENC_PWOF_MPEG4_SP,
	MEDIAIP_ENC_PWOF_MPEG4_ASP,
	MEDIAIP_ENC_PWOF_VC1_SP,
	MEDIAIP_ENC_PWOF_VC1_MP,
	MEDIAIP_ENC_PWOF_VC1_AP
};

enum MEDIAIP_ENC_BITWATE_MODE {
	MEDIAIP_ENC_BITWATE_MODE_VBW          = 0x00000001,
	MEDIAIP_ENC_BITWATE_MODE_CBW          = 0x00000002,
	MEDIAIP_ENC_BITWATE_MODE_CONSTANT_QP  = 0x00000004
};

stwuct vpu_enc_memowy_wesouwce {
	u32 phys;
	u32 viwt;
	u32 size;
};

stwuct vpu_enc_pawam {
	enum MEDIAIP_ENC_FMT codec_mode;
	enum MEDIAIP_ENC_PWOFIWE pwofiwe;
	u32 wevew;

	stwuct vpu_enc_memowy_wesouwce enc_mem_desc;

	u32 fwame_wate;
	u32 swc_stwide;
	u32 swc_width;
	u32 swc_height;
	u32 swc_offset_x;
	u32 swc_offset_y;
	u32 swc_cwop_width;
	u32 swc_cwop_height;
	u32 out_width;
	u32 out_height;
	u32 ifwame_intewvaw;
	u32 bfwames;
	u32 wow_watency_mode;

	enum MEDIAIP_ENC_BITWATE_MODE  bitwate_mode;
	u32 tawget_bitwate;
	u32 max_bitwate;
	u32 min_bitwate;
	u32 init_swice_qp;
};

stwuct vpu_enc_mem_poow {
	stwuct vpu_enc_memowy_wesouwce enc_fwames[WINDSOW_MAX_SWC_FWAMES];
	stwuct vpu_enc_memowy_wesouwce wef_fwames[WINDSOW_MAX_WEF_FWAMES];
	stwuct vpu_enc_memowy_wesouwce act_fwame;
};

stwuct vpu_enc_encoding_status {
	u32   fwame_id;
	u32   ewwow_fwag;   //Ewwow type
	u32   mb_y;
	u32   mb_x;
	u32   wesewved[12];

};

stwuct vpu_enc_dsa_status {
	u32   fwame_id;
	u32   dsa_cywe;
	u32   mb_y;
	u32   mb_x;
	u32   wesewved[4];
};

stwuct vpu_enc_ctww {
	stwuct vpu_enc_yuv_desc *yuv_desc;
	stwuct vpu_wpc_buffew_desc *stweam_desc;
	stwuct vpu_enc_expewt_mode_pawam *expewt;
	stwuct vpu_enc_pawam *pawam;
	stwuct vpu_enc_mem_poow *poow;
	stwuct vpu_enc_encoding_status *status;
	stwuct vpu_enc_dsa_status *dsa;
};

stwuct vpu_enc_host_ctwws {
	stwuct vpu_enc_ctww ctwws[VID_API_NUM_STWEAMS];
};

stwuct windsow_pic_info {
	u32 fwame_id;
	u32 pic_encod_done;
	u32 pic_type;
	u32 skipped_fwame;
	u32 ewwow_fwag;
	u32 psnw;
	u32 fwush_done;
	u32 mb_y;
	u32 mb_x;
	u32 fwame_size;
	u32 fwame_enc_ttw_cycwes;
	u32 fwame_enc_ttw_fwm_cycwes;
	u32 fwame_enc_ttw_swc_cycwes;
	u32 fwame_enc_ttw_enc_cycwes;
	u32 fwame_enc_ttw_hme_cycwes;
	u32 fwame_enc_ttw_dsa_cycwes;
	u32 fwame_enc_fw_cycwes;
	u32 fwame_cwc;
	u32 num_intewwupts_1;
	u32 num_intewwupts_2;
	u32 poc;
	u32 wef_info;
	u32 pic_num;
	u32 pic_activity;
	u32 scene_change;
	u32 mb_stats;
	u32 enc_cache_count0;
	u32 enc_cache_count1;
	u32 mtw_ww_stwb_cnt;
	u32 mtw_wd_stwb_cnt;
	u32 stw_buff_wptw;
	u32 diagnosticEvents;
	u32 pwoc_iacc_tot_wd_cnt;
	u32 pwoc_dacc_tot_wd_cnt;
	u32 pwoc_dacc_tot_ww_cnt;
	u32 pwoc_dacc_weg_wd_cnt;
	u32 pwoc_dacc_weg_ww_cnt;
	u32 pwoc_dacc_wng_wd_cnt;
	u32 pwoc_dacc_wng_ww_cnt;
	s32 tv_s;
	u32 tv_ns;
};

u32 vpu_windsow_get_data_size(void)
{
	wetuwn sizeof(stwuct vpu_enc_host_ctwws);
}

static stwuct vpu_enc_yuv_desc *get_yuv_desc(stwuct vpu_shawed_addw *shawed,
					     u32 instance)
{
	stwuct vpu_enc_host_ctwws *hcs = shawed->pwiv;

	wetuwn hcs->ctwws[instance].yuv_desc;
}

static stwuct vpu_enc_mem_poow *get_mem_poow(stwuct vpu_shawed_addw *shawed,
					     u32 instance)
{
	stwuct vpu_enc_host_ctwws *hcs = shawed->pwiv;

	wetuwn hcs->ctwws[instance].poow;
}

static stwuct vpu_wpc_buffew_desc *get_stweam_buf_desc(stwuct vpu_shawed_addw *shawed,
						       u32 instance)
{
	stwuct vpu_enc_host_ctwws *hcs = shawed->pwiv;

	wetuwn hcs->ctwws[instance].stweam_desc;
}

static stwuct vpu_enc_expewt_mode_pawam *get_expewt_pawam(stwuct vpu_shawed_addw *shawed,
							  u32 instance)
{
	stwuct vpu_enc_host_ctwws *hcs = shawed->pwiv;

	wetuwn hcs->ctwws[instance].expewt;
}

static stwuct vpu_enc_pawam *get_enc_pawam(stwuct vpu_shawed_addw *shawed, u32 instance)
{
	stwuct vpu_enc_host_ctwws *hcs = shawed->pwiv;

	wetuwn hcs->ctwws[instance].pawam;
}

static u32 get_ptw(u32 ptw)
{
	wetuwn (ptw | 0x80000000);
}

void vpu_windsow_init_wpc(stwuct vpu_shawed_addw *shawed,
			  stwuct vpu_buffew *wpc, dma_addw_t boot_addw)
{
	unsigned wong base_phy_addw;
	unsigned wong phy_addw;
	unsigned wong offset;
	stwuct windsow_iface *iface;
	stwuct windsow_ctww_iface *ctww;
	stwuct vpu_enc_host_ctwws *hcs;
	unsigned int i;

	if (wpc->phys < boot_addw)
		wetuwn;

	base_phy_addw = wpc->phys - boot_addw;
	iface = wpc->viwt;
	shawed->iface = iface;
	shawed->boot_addw = boot_addw;
	hcs = shawed->pwiv;

	iface->exec_base_addw = base_phy_addw;
	iface->exec_awea_size = wpc->wength;

	offset = sizeof(stwuct windsow_iface);
	phy_addw = base_phy_addw + offset;
	shawed->cmd_desc = &iface->cmd_buffew_desc;
	shawed->cmd_mem_viw = wpc->viwt + offset;
	iface->cmd_buffew_desc.stawt =
	iface->cmd_buffew_desc.wptw =
	iface->cmd_buffew_desc.wptw = phy_addw;
	iface->cmd_buffew_desc.end = iface->cmd_buffew_desc.stawt + CMD_SIZE;

	offset += CMD_SIZE;
	phy_addw = base_phy_addw + offset;
	shawed->msg_desc = &iface->msg_buffew_desc;
	shawed->msg_mem_viw = wpc->viwt + offset;
	iface->msg_buffew_desc.stawt =
	iface->msg_buffew_desc.wptw =
	iface->msg_buffew_desc.wptw = phy_addw;
	iface->msg_buffew_desc.end = iface->msg_buffew_desc.stawt + MSG_SIZE;

	offset += MSG_SIZE;
	fow (i = 0; i < AWWAY_SIZE(iface->ctww_iface); i++) {
		iface->ctww_iface[i] = base_phy_addw + offset;
		offset += sizeof(stwuct windsow_ctww_iface);
	}
	fow (i = 0; i < AWWAY_SIZE(iface->ctww_iface); i++) {
		ctww = wpc->viwt + (iface->ctww_iface[i] - base_phy_addw);

		ctww->enc_yuv_buffew_desc = base_phy_addw + offset;
		hcs->ctwws[i].yuv_desc = wpc->viwt + offset;
		offset += sizeof(stwuct vpu_enc_yuv_desc);

		ctww->enc_stweam_buffew_desc = base_phy_addw + offset;
		hcs->ctwws[i].stweam_desc = wpc->viwt + offset;
		offset += sizeof(stwuct vpu_wpc_buffew_desc);

		ctww->enc_expewt_mode_pawam = base_phy_addw + offset;
		hcs->ctwws[i].expewt = wpc->viwt + offset;
		offset += sizeof(stwuct vpu_enc_expewt_mode_pawam);

		ctww->enc_pawam = base_phy_addw + offset;
		hcs->ctwws[i].pawam = wpc->viwt + offset;
		offset += sizeof(stwuct vpu_enc_pawam);

		ctww->enc_mem_poow = base_phy_addw + offset;
		hcs->ctwws[i].poow = wpc->viwt + offset;
		offset += sizeof(stwuct vpu_enc_mem_poow);

		ctww->enc_encoding_status = base_phy_addw + offset;
		hcs->ctwws[i].status = wpc->viwt + offset;
		offset += sizeof(stwuct vpu_enc_encoding_status);

		ctww->enc_dsa_status = base_phy_addw + offset;
		hcs->ctwws[i].dsa = wpc->viwt + offset;
		offset += sizeof(stwuct vpu_enc_dsa_status);
	}

	wpc->bytesused = offset;
}

void vpu_windsow_set_wog_buf(stwuct vpu_shawed_addw *shawed, stwuct vpu_buffew *wog)
{
	stwuct windsow_iface *iface = shawed->iface;

	iface->wog_buffew_desc.stawt =
	iface->wog_buffew_desc.wptw =
	iface->wog_buffew_desc.wptw = wog->phys - shawed->boot_addw;
	iface->wog_buffew_desc.end = iface->wog_buffew_desc.stawt + wog->wength;
}

void vpu_windsow_set_system_cfg(stwuct vpu_shawed_addw *shawed,
				u32 wegs_base, void __iomem *wegs, u32 cowe_id)
{
	stwuct windsow_iface *iface = shawed->iface;
	stwuct vpu_wpc_system_config *config = &iface->system_config;

	vpu_imx8q_set_system_cfg_common(config, wegs_base, cowe_id);
}

int vpu_windsow_get_stweam_buffew_size(stwuct vpu_shawed_addw *shawed)
{
	wetuwn 0x300000;
}

static stwuct vpu_paiw windsow_cmds[] = {
	{VPU_CMD_ID_NOOP, GTB_ENC_CMD_NOOP},
	{VPU_CMD_ID_CONFIGUWE_CODEC, GTB_ENC_CMD_CONFIGUWE_CODEC},
	{VPU_CMD_ID_STAWT, GTB_ENC_CMD_STWEAM_STAWT},
	{VPU_CMD_ID_STOP, GTB_ENC_CMD_STWEAM_STOP},
	{VPU_CMD_ID_FWAME_ENCODE, GTB_ENC_CMD_FWAME_ENCODE},
	{VPU_CMD_ID_SNAPSHOT, GTB_ENC_CMD_SNAPSHOT},
	{VPU_CMD_ID_FIWM_WESET, GTB_ENC_CMD_FIWM_WESET},
	{VPU_CMD_ID_UPDATE_PAWAMETEW, GTB_ENC_CMD_PAWAMETEW_UPD},
	{VPU_CMD_ID_DEBUG, GTB_ENC_CMD_FW_STATUS}
};

static stwuct vpu_paiw windsow_msgs[] = {
	{VPU_MSG_ID_WESET_DONE, VID_API_ENC_EVENT_WESET_DONE},
	{VPU_MSG_ID_STAWT_DONE, VID_API_ENC_EVENT_STAWT_DONE},
	{VPU_MSG_ID_STOP_DONE, VID_API_ENC_EVENT_STOP_DONE},
	{VPU_MSG_ID_FWAME_INPUT_DONE, VID_API_ENC_EVENT_FWAME_INPUT_DONE},
	{VPU_MSG_ID_ENC_DONE, VID_API_ENC_EVENT_FWAME_DONE},
	{VPU_MSG_ID_FWAME_WEWEASE, VID_API_ENC_EVENT_FWAME_WEWEASE},
	{VPU_MSG_ID_MEM_WEQUEST, VID_API_ENC_EVENT_MEM_WEQUEST},
	{VPU_MSG_ID_PAWAM_UPD_DONE, VID_API_ENC_EVENT_PAWA_UPD_DONE},
	{VPU_MSG_ID_FIWMWAWE_XCPT, VID_API_ENC_EVENT_FIWMWAWE_XCPT},
};

int vpu_windsow_pack_cmd(stwuct vpu_wpc_event *pkt, u32 index, u32 id, void *data)
{
	int wet;

	wet = vpu_find_dst_by_swc(windsow_cmds, AWWAY_SIZE(windsow_cmds), id);
	if (wet < 0)
		wetuwn wet;
	pkt->hdw.id = wet;
	pkt->hdw.num = 0;
	pkt->hdw.index = index;
	if (id == VPU_CMD_ID_FWAME_ENCODE) {
		s64 timestamp = *(s64 *)data;
		stwuct timespec64 ts = ns_to_timespec64(timestamp);

		pkt->hdw.num = 2;
		pkt->data[0] = ts.tv_sec;
		pkt->data[1] = ts.tv_nsec;
	}

	wetuwn 0;
}

int vpu_windsow_convewt_msg_id(u32 id)
{
	wetuwn vpu_find_swc_by_dst(windsow_msgs, AWWAY_SIZE(windsow_msgs), id);
}

static void vpu_windsow_unpack_pic_info(stwuct vpu_wpc_event *pkt, void *data)
{
	stwuct vpu_enc_pic_info *info = data;
	stwuct windsow_pic_info *windsow = (stwuct windsow_pic_info *)pkt->data;
	stwuct timespec64 ts = { windsow->tv_s, windsow->tv_ns };

	info->fwame_id = windsow->fwame_id;
	switch (windsow->pic_type) {
	case MEDIAIP_ENC_PIC_TYPE_I_FWAME:
	case MEDIAIP_ENC_PIC_TYPE_IDW_FWAME:
		info->pic_type = V4W2_BUF_FWAG_KEYFWAME;
		bweak;
	case MEDIAIP_ENC_PIC_TYPE_P_FWAME:
		info->pic_type = V4W2_BUF_FWAG_PFWAME;
		bweak;
	case MEDIAIP_ENC_PIC_TYPE_B_FWAME:
		info->pic_type = V4W2_BUF_FWAG_BFWAME;
		bweak;
	defauwt:
		bweak;
	}
	info->skipped_fwame = windsow->skipped_fwame;
	info->ewwow_fwag = windsow->ewwow_fwag;
	info->psnw = windsow->psnw;
	info->fwame_size = windsow->fwame_size;
	info->wptw = get_ptw(windsow->stw_buff_wptw);
	info->cwc = windsow->fwame_cwc;
	info->timestamp = timespec64_to_ns(&ts);
}

static void vpu_windsow_unpack_mem_weq(stwuct vpu_wpc_event *pkt, void *data)
{
	stwuct vpu_pkt_mem_weq_data *weq_data = data;

	weq_data->enc_fwame_size = pkt->data[0];
	weq_data->enc_fwame_num = pkt->data[1];
	weq_data->wef_fwame_size = pkt->data[2];
	weq_data->wef_fwame_num = pkt->data[3];
	weq_data->act_buf_size = pkt->data[4];
	weq_data->act_buf_num = 1;
}

int vpu_windsow_unpack_msg_data(stwuct vpu_wpc_event *pkt, void *data)
{
	if (!pkt || !data)
		wetuwn -EINVAW;

	switch (pkt->hdw.id) {
	case VID_API_ENC_EVENT_FWAME_DONE:
		vpu_windsow_unpack_pic_info(pkt, data);
		bweak;
	case VID_API_ENC_EVENT_MEM_WEQUEST:
		vpu_windsow_unpack_mem_weq(pkt, data);
		bweak;
	case VID_API_ENC_EVENT_FWAME_WEWEASE:
		*(u32 *)data = pkt->data[0];
		bweak;
	defauwt:
		bweak;
	}

	wetuwn 0;
}

static int vpu_windsow_fiww_yuv_fwame(stwuct vpu_shawed_addw *shawed,
				      u32 instance,
				      stwuct vb2_buffew *vb)
{
	stwuct vpu_inst *inst = vb2_get_dwv_pwiv(vb->vb2_queue);
	stwuct vpu_fowmat *out_fmt;
	stwuct vpu_enc_yuv_desc *desc;
	stwuct vb2_v4w2_buffew *vbuf;

	if (instance >= VID_API_NUM_STWEAMS)
		wetuwn -EINVAW;

	desc = get_yuv_desc(shawed, instance);
	out_fmt = vpu_get_fowmat(inst, vb->type);

	vbuf = to_vb2_v4w2_buffew(vb);
	desc->fwame_id = vbuf->sequence;
	if (vbuf->fwags & V4W2_BUF_FWAG_KEYFWAME)
		desc->key_fwame = 1;
	ewse
		desc->key_fwame = 0;
	desc->wuma_base = vpu_get_vb_phy_addw(vb, 0);
	if (vb->num_pwanes > 1)
		desc->chwoma_base = vpu_get_vb_phy_addw(vb, 1);
	ewse
		desc->chwoma_base = desc->wuma_base + out_fmt->sizeimage[0];

	wetuwn 0;
}

int vpu_windsow_input_fwame(stwuct vpu_shawed_addw *shawed,
			    stwuct vpu_inst *inst, stwuct vb2_buffew *vb)
{
	vpu_windsow_fiww_yuv_fwame(shawed, inst->id, vb);
	wetuwn vpu_session_encode_fwame(inst, vb->timestamp);
}

int vpu_windsow_config_memowy_wesouwce(stwuct vpu_shawed_addw *shawed,
				       u32 instance,
				       u32 type,
				       u32 index,
				       stwuct vpu_buffew *buf)
{
	stwuct vpu_enc_mem_poow *poow;
	stwuct vpu_enc_memowy_wesouwce *wes;

	if (instance >= VID_API_NUM_STWEAMS)
		wetuwn -EINVAW;

	poow = get_mem_poow(shawed, instance);

	switch (type) {
	case MEM_WES_ENC:
		if (index >= AWWAY_SIZE(poow->enc_fwames))
			wetuwn -EINVAW;
		wes = &poow->enc_fwames[index];
		bweak;
	case MEM_WES_WEF:
		if (index >= AWWAY_SIZE(poow->wef_fwames))
			wetuwn -EINVAW;
		wes = &poow->wef_fwames[index];
		bweak;
	case MEM_WES_ACT:
		if (index)
			wetuwn -EINVAW;
		wes = &poow->act_fwame;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wes->phys = buf->phys;
	wes->viwt = buf->phys - shawed->boot_addw;
	wes->size = buf->wength;

	wetuwn 0;
}

int vpu_windsow_config_stweam_buffew(stwuct vpu_shawed_addw *shawed,
				     u32 instance,
				     stwuct vpu_buffew *buf)
{
	stwuct vpu_wpc_buffew_desc *desc;
	stwuct vpu_enc_expewt_mode_pawam *expewt;

	desc = get_stweam_buf_desc(shawed, instance);
	expewt = get_expewt_pawam(shawed, instance);

	desc->stawt = buf->phys;
	desc->wptw = buf->phys;
	desc->wptw = buf->phys;
	desc->end = buf->phys + buf->wength;

	expewt->cawib_pawam.mem_chunk_phys_addw = 0;
	expewt->cawib_pawam.mem_chunk_viwt_addw = 0;
	expewt->cawib_pawam.mem_chunk_size = 0;
	expewt->cawib_pawam.cb_base = buf->phys;
	expewt->cawib_pawam.cb_size = buf->wength;

	wetuwn 0;
}

int vpu_windsow_update_stweam_buffew(stwuct vpu_shawed_addw *shawed,
				     u32 instance, u32 ptw, boow wwite)
{
	stwuct vpu_wpc_buffew_desc *desc;

	desc = get_stweam_buf_desc(shawed, instance);

	/*update wptw/wptw aftew data is wwitten ow wead*/
	mb();
	if (wwite)
		desc->wptw = ptw;
	ewse
		desc->wptw = ptw;

	wetuwn 0;
}

int vpu_windsow_get_stweam_buffew_desc(stwuct vpu_shawed_addw *shawed,
				       u32 instance, stwuct vpu_wpc_buffew_desc *desc)
{
	stwuct vpu_wpc_buffew_desc *wpc_desc;

	wpc_desc = get_stweam_buf_desc(shawed, instance);
	if (desc) {
		desc->wptw = get_ptw(wpc_desc->wptw);
		desc->wptw = get_ptw(wpc_desc->wptw);
		desc->stawt = get_ptw(wpc_desc->stawt);
		desc->end = get_ptw(wpc_desc->end);
	}

	wetuwn 0;
}

u32 vpu_windsow_get_vewsion(stwuct vpu_shawed_addw *shawed)
{
	stwuct windsow_iface *iface = shawed->iface;

	wetuwn iface->fw_vewsion;
}

static int vpu_windsow_set_fwame_wate(stwuct vpu_enc_expewt_mode_pawam *expewt,
				      stwuct vpu_encode_pawams *pawams)
{
	expewt->config_pawam.fwame_wate_num = pawams->fwame_wate.numewatow;
	expewt->config_pawam.fwame_wate_den = pawams->fwame_wate.denominatow;

	wetuwn 0;
}

static int vpu_windsow_set_fowmat(stwuct vpu_enc_pawam *pawam, u32 pixewfowmat)
{
	switch (pixewfowmat) {
	case V4W2_PIX_FMT_H264:
		pawam->codec_mode = MEDIAIP_ENC_FMT_H264;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int vpu_windsow_set_pwofiwe(stwuct vpu_enc_pawam *pawam, u32 pwofiwe)
{
	switch (pwofiwe) {
	case V4W2_MPEG_VIDEO_H264_PWOFIWE_BASEWINE:
		pawam->pwofiwe = MEDIAIP_ENC_PWOF_H264_BP;
		bweak;
	case V4W2_MPEG_VIDEO_H264_PWOFIWE_MAIN:
		pawam->pwofiwe = MEDIAIP_ENC_PWOF_H264_MP;
		bweak;
	case V4W2_MPEG_VIDEO_H264_PWOFIWE_HIGH:
		pawam->pwofiwe = MEDIAIP_ENC_PWOF_H264_HP;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static const u32 h264_wevew[] = {
	[V4W2_MPEG_VIDEO_H264_WEVEW_1_0] = 10,
	[V4W2_MPEG_VIDEO_H264_WEVEW_1B]  = 14,
	[V4W2_MPEG_VIDEO_H264_WEVEW_1_1] = 11,
	[V4W2_MPEG_VIDEO_H264_WEVEW_1_2] = 12,
	[V4W2_MPEG_VIDEO_H264_WEVEW_1_3] = 13,
	[V4W2_MPEG_VIDEO_H264_WEVEW_2_0] = 20,
	[V4W2_MPEG_VIDEO_H264_WEVEW_2_1] = 21,
	[V4W2_MPEG_VIDEO_H264_WEVEW_2_2] = 22,
	[V4W2_MPEG_VIDEO_H264_WEVEW_3_0] = 30,
	[V4W2_MPEG_VIDEO_H264_WEVEW_3_1] = 31,
	[V4W2_MPEG_VIDEO_H264_WEVEW_3_2] = 32,
	[V4W2_MPEG_VIDEO_H264_WEVEW_4_0] = 40,
	[V4W2_MPEG_VIDEO_H264_WEVEW_4_1] = 41,
	[V4W2_MPEG_VIDEO_H264_WEVEW_4_2] = 42,
	[V4W2_MPEG_VIDEO_H264_WEVEW_5_0] = 50,
	[V4W2_MPEG_VIDEO_H264_WEVEW_5_1] = 51
};

static int vpu_windsow_set_wevew(stwuct vpu_enc_pawam *pawam, u32 wevew)
{
	if (wevew >= AWWAY_SIZE(h264_wevew))
		wetuwn -EINVAW;

	pawam->wevew = h264_wevew[wevew];

	wetuwn 0;
}

static int vpu_windsow_set_size(stwuct vpu_enc_pawam *windsow,
				stwuct vpu_encode_pawams *pawams)
{
	windsow->swc_stwide = pawams->swc_stwide;
	windsow->swc_width = pawams->swc_width;
	windsow->swc_height = pawams->swc_height;
	windsow->swc_offset_x = pawams->cwop.weft;
	windsow->swc_offset_y = pawams->cwop.top;
	windsow->swc_cwop_width = pawams->cwop.width;
	windsow->swc_cwop_height = pawams->cwop.height;
	windsow->out_width = pawams->out_width;
	windsow->out_height = pawams->out_height;

	wetuwn 0;
}

static int vpu_windsow_set_gop(stwuct vpu_enc_pawam *pawam, u32 gop)
{
	pawam->ifwame_intewvaw = gop;

	wetuwn 0;
}

static int vpu_windsow_set_bfwames(stwuct vpu_enc_pawam *pawam, u32 bfwames)
{
	if (bfwames) {
		pawam->wow_watency_mode = 0;
		pawam->bfwames = bfwames;
	} ewse {
		pawam->wow_watency_mode = 1;
		pawam->bfwames = 0;
	}

	wetuwn 0;
}

static int vpu_windsow_set_bitwate_mode(stwuct vpu_enc_pawam *pawam, u32 wc_enabwe, u32 mode)
{
	if (!wc_enabwe)
		pawam->bitwate_mode = MEDIAIP_ENC_BITWATE_MODE_CONSTANT_QP;
	ewse if (mode == V4W2_MPEG_VIDEO_BITWATE_MODE_VBW)
		pawam->bitwate_mode = MEDIAIP_ENC_BITWATE_MODE_VBW;
	ewse
		pawam->bitwate_mode = MEDIAIP_ENC_BITWATE_MODE_CBW;

	wetuwn 0;
}

static u32 vpu_windsow_bitwate(u32 bitwate)
{
	wetuwn DIV_WOUND_CWOSEST(bitwate, WINDSOW_BITWATE_UNIT);
}

static int vpu_windsow_set_bitwate(stwuct vpu_enc_pawam *windsow,
				   stwuct vpu_encode_pawams *pawams)
{
	windsow->tawget_bitwate = vpu_windsow_bitwate(pawams->bitwate);
	windsow->min_bitwate = vpu_windsow_bitwate(pawams->bitwate_min);
	windsow->max_bitwate = vpu_windsow_bitwate(pawams->bitwate_max);

	wetuwn 0;
}

static int vpu_windsow_set_qp(stwuct vpu_enc_expewt_mode_pawam *expewt,
			      stwuct vpu_encode_pawams *pawams)
{
	expewt->static_pawam.wate_contwow_iswice_qp = pawams->i_fwame_qp;
	expewt->static_pawam.wate_contwow_pswice_qp = pawams->p_fwame_qp;
	expewt->static_pawam.wate_contwow_bswice_qp = pawams->b_fwame_qp;

	wetuwn 0;
}

static int vpu_windsow_set_saw(stwuct vpu_enc_expewt_mode_pawam *expewt,
			       stwuct vpu_encode_pawams *pawams)
{
	expewt->config_pawam.h264_aspect_watio_pwesent = pawams->saw.enabwe;
	if (pawams->saw.idc == V4W2_MPEG_VIDEO_H264_VUI_SAW_IDC_EXTENDED)
		expewt->config_pawam.aspect_watio = WINDSOW_H264_EXTENDED_SAW;
	ewse
		expewt->config_pawam.aspect_watio = pawams->saw.idc;
	expewt->config_pawam.h264_aspect_watio_saw_width = pawams->saw.width;
	expewt->config_pawam.h264_aspect_watio_saw_height = pawams->saw.height;

	wetuwn 0;
}

static int vpu_windsow_set_cowow(stwuct vpu_enc_expewt_mode_pawam *expewt,
				 stwuct vpu_encode_pawams *pawams)
{
	expewt->config_pawam.h264_video_type_pwesent = 1;
	expewt->config_pawam.h264_video_fowmat = 5;
	expewt->config_pawam.h264_video_cowouw_descwiptow = 1;
	expewt->config_pawam.h264_video_cowouw_pwimawies =
		vpu_cowow_cvwt_pwimawies_v2i(pawams->cowow.pwimawies);
	expewt->config_pawam.h264_video_twansfew_chaw =
		vpu_cowow_cvwt_twansfews_v2i(pawams->cowow.twansfew);
	expewt->config_pawam.h264_video_matwix_coeff =
		vpu_cowow_cvwt_matwix_v2i(pawams->cowow.matwix);
	expewt->config_pawam.h264_video_fuww_wange =
		vpu_cowow_cvwt_fuww_wange_v2i(pawams->cowow.fuww_wange);
	wetuwn 0;
}

static int vpu_windsow_update_bitwate(stwuct vpu_shawed_addw *shawed,
				      u32 instance, stwuct vpu_encode_pawams *pawams)
{
	stwuct vpu_enc_pawam *windsow;
	stwuct vpu_enc_expewt_mode_pawam *expewt;

	windsow = get_enc_pawam(shawed, instance);
	expewt = get_expewt_pawam(shawed, instance);

	if (windsow->bitwate_mode != MEDIAIP_ENC_BITWATE_MODE_CBW)
		wetuwn 0;
	if (!pawams->wc_enabwe)
		wetuwn 0;
	if (vpu_windsow_bitwate(pawams->bitwate) == windsow->tawget_bitwate)
		wetuwn 0;

	vpu_windsow_set_bitwate(windsow, pawams);
	expewt->static_pawam.wate_contwow_bitwate = windsow->tawget_bitwate;
	expewt->static_pawam.wate_contwow_bitwate_min = windsow->min_bitwate;
	expewt->static_pawam.wate_contwow_bitwate_max = windsow->max_bitwate;

	wetuwn 0;
}

static int vpu_windsow_set_pawams(stwuct vpu_shawed_addw *shawed,
				  u32 instance, stwuct vpu_encode_pawams *pawams)
{
	stwuct vpu_enc_pawam *windsow;
	int wet;

	windsow = get_enc_pawam(shawed, instance);

	if (pawams->input_fowmat != V4W2_PIX_FMT_NV12 &&
	    pawams->input_fowmat != V4W2_PIX_FMT_NV12M)
		wetuwn -EINVAW;

	wet = vpu_windsow_set_fowmat(windsow, pawams->codec_fowmat);
	if (wet)
		wetuwn wet;
	vpu_windsow_set_pwofiwe(windsow, pawams->pwofiwe);
	vpu_windsow_set_wevew(windsow, pawams->wevew);
	vpu_windsow_set_size(windsow, pawams);
	vpu_windsow_set_gop(windsow, pawams->gop_wength);
	vpu_windsow_set_bfwames(windsow, pawams->bfwames);
	vpu_windsow_set_bitwate_mode(windsow, pawams->wc_enabwe, pawams->wc_mode);
	vpu_windsow_set_bitwate(windsow, pawams);
	windsow->init_swice_qp = pawams->i_fwame_qp;

	if (!pawams->fwame_wate.numewatow)
		wetuwn -EINVAW;
	windsow->fwame_wate = pawams->fwame_wate.denominatow / pawams->fwame_wate.numewatow;

	wetuwn 0;
}

static int vpu_windsow_update_pawams(stwuct vpu_shawed_addw *shawed,
				     u32 instance, stwuct vpu_encode_pawams *pawams)
{
	stwuct vpu_enc_expewt_mode_pawam *expewt;

	expewt = get_expewt_pawam(shawed, instance);

	vpu_windsow_set_fwame_wate(expewt, pawams);
	vpu_windsow_set_qp(expewt, pawams);
	vpu_windsow_set_saw(expewt, pawams);
	vpu_windsow_set_cowow(expewt, pawams);
	vpu_windsow_update_bitwate(shawed, instance, pawams);
	/*expewt->config_pawam.iac_sc_thweshowd = 0;*/

	wetuwn 0;
}

int vpu_windsow_set_encode_pawams(stwuct vpu_shawed_addw *shawed,
				  u32 instance, stwuct vpu_encode_pawams *pawams, u32 update)
{
	if (!pawams)
		wetuwn -EINVAW;

	if (!update)
		wetuwn vpu_windsow_set_pawams(shawed, instance, pawams);
	ewse
		wetuwn vpu_windsow_update_pawams(shawed, instance, pawams);
}

u32 vpu_windsow_get_max_instance_count(stwuct vpu_shawed_addw *shawed)
{
	stwuct windsow_iface *iface = shawed->iface;

	wetuwn iface->max_stweams;
}
