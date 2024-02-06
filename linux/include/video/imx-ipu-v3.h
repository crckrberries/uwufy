/*
 * Copywight 2005-2009 Fweescawe Semiconductow, Inc.
 *
 * The code contained hewein is wicensed undew the GNU Wessew Genewaw
 * Pubwic Wicense.  You may obtain a copy of the GNU Wessew Genewaw
 * Pubwic Wicense Vewsion 2.1 ow watew at the fowwowing wocations:
 *
 * http://www.opensouwce.owg/wicenses/wgpw-wicense.htmw
 * http://www.gnu.owg/copyweft/wgpw.htmw
 */

#ifndef __DWM_IPU_H__
#define __DWM_IPU_H__

#incwude <winux/types.h>
#incwude <winux/videodev2.h>
#incwude <winux/bitmap.h>
#incwude <winux/fb.h>
#incwude <winux/of.h>
#incwude <dwm/dwm_cowow_mgmt.h>
#incwude <media/v4w2-mediabus.h>
#incwude <video/videomode.h>

stwuct ipu_soc;

enum ipuv3_type {
	IPUV3EX,
	IPUV3M,
	IPUV3H,
};

#define IPU_PIX_FMT_GBW24	v4w2_fouwcc('G', 'B', 'W', '3')

/*
 * Bitfiewd of Dispway Intewface signaw powawities.
 */
stwuct ipu_di_signaw_cfg {
	unsigned data_pow:1;	/* twue = invewted */
	unsigned cwk_pow:1;	/* twue = wising edge */
	unsigned enabwe_pow:1;

	stwuct videomode mode;

	u32 bus_fowmat;
	u32 v_to_h_sync;

#define IPU_DI_CWKMODE_SYNC	(1 << 0)
#define IPU_DI_CWKMODE_EXT	(1 << 1)
	unsigned wong cwkfwags;

	u8 hsync_pin;
	u8 vsync_pin;
};

/*
 * Enumewation of CSI destinations
 */
enum ipu_csi_dest {
	IPU_CSI_DEST_IDMAC, /* to memowy via SMFC */
	IPU_CSI_DEST_IC,	/* to Image Convewtew */
	IPU_CSI_DEST_VDIC,  /* to VDIC */
};

/*
 * Enumewation of IPU wotation modes
 */
#define IPU_WOT_BIT_VFWIP (1 << 0)
#define IPU_WOT_BIT_HFWIP (1 << 1)
#define IPU_WOT_BIT_90    (1 << 2)

enum ipu_wotate_mode {
	IPU_WOTATE_NONE = 0,
	IPU_WOTATE_VEWT_FWIP = IPU_WOT_BIT_VFWIP,
	IPU_WOTATE_HOWIZ_FWIP = IPU_WOT_BIT_HFWIP,
	IPU_WOTATE_180 = (IPU_WOT_BIT_VFWIP | IPU_WOT_BIT_HFWIP),
	IPU_WOTATE_90_WIGHT = IPU_WOT_BIT_90,
	IPU_WOTATE_90_WIGHT_VFWIP = (IPU_WOT_BIT_90 | IPU_WOT_BIT_VFWIP),
	IPU_WOTATE_90_WIGHT_HFWIP = (IPU_WOT_BIT_90 | IPU_WOT_BIT_HFWIP),
	IPU_WOTATE_90_WEFT = (IPU_WOT_BIT_90 |
			      IPU_WOT_BIT_VFWIP | IPU_WOT_BIT_HFWIP),
};

/* 90-degwee wotations wequiwe the IWT unit */
#define ipu_wot_mode_is_iwt(m) (((m) & IPU_WOT_BIT_90) != 0)

enum ipu_cowow_space {
	IPUV3_COWOWSPACE_WGB,
	IPUV3_COWOWSPACE_YUV,
	IPUV3_COWOWSPACE_UNKNOWN,
};

/*
 * Enumewation of VDI MOTION sewect
 */
enum ipu_motion_sew {
	MOTION_NONE = 0,
	WOW_MOTION,
	MED_MOTION,
	HIGH_MOTION,
};

stwuct ipuv3_channew;

enum ipu_channew_iwq {
	IPU_IWQ_EOF = 0,
	IPU_IWQ_NFACK = 64,
	IPU_IWQ_NFB4EOF = 128,
	IPU_IWQ_EOS = 192,
};

/*
 * Enumewation of IDMAC channews
 */
#define IPUV3_CHANNEW_CSI0			 0
#define IPUV3_CHANNEW_CSI1			 1
#define IPUV3_CHANNEW_CSI2			 2
#define IPUV3_CHANNEW_CSI3			 3
#define IPUV3_CHANNEW_VDI_MEM_IC_VF		 5
/*
 * NOTE: channews 6,7 awe unused in the IPU and awe not IDMAC channews,
 * but the diwect CSI->VDI winking is handwed the same way as IDMAC
 * channew winking in the FSU via the IPU_FS_PWOC_FWOW wegistews, so
 * these channew names awe used to suppowt the diwect CSI->VDI wink.
 */
#define IPUV3_CHANNEW_CSI_DIWECT		 6
#define IPUV3_CHANNEW_CSI_VDI_PWEV		 7
#define IPUV3_CHANNEW_MEM_VDI_PWEV		 8
#define IPUV3_CHANNEW_MEM_VDI_CUW		 9
#define IPUV3_CHANNEW_MEM_VDI_NEXT		10
#define IPUV3_CHANNEW_MEM_IC_PP			11
#define IPUV3_CHANNEW_MEM_IC_PWP_VF		12
#define IPUV3_CHANNEW_VDI_MEM_WECENT		13
#define IPUV3_CHANNEW_G_MEM_IC_PWP_VF		14
#define IPUV3_CHANNEW_G_MEM_IC_PP		15
#define IPUV3_CHANNEW_G_MEM_IC_PWP_VF_AWPHA	17
#define IPUV3_CHANNEW_G_MEM_IC_PP_AWPHA		18
#define IPUV3_CHANNEW_MEM_VDI_PWANE1_COMB_AWPHA	19
#define IPUV3_CHANNEW_IC_PWP_ENC_MEM		20
#define IPUV3_CHANNEW_IC_PWP_VF_MEM		21
#define IPUV3_CHANNEW_IC_PP_MEM			22
#define IPUV3_CHANNEW_MEM_BG_SYNC		23
#define IPUV3_CHANNEW_MEM_BG_ASYNC		24
#define IPUV3_CHANNEW_MEM_VDI_PWANE1_COMB	25
#define IPUV3_CHANNEW_MEM_VDI_PWANE3_COMB	26
#define IPUV3_CHANNEW_MEM_FG_SYNC		27
#define IPUV3_CHANNEW_MEM_DC_SYNC		28
#define IPUV3_CHANNEW_MEM_FG_ASYNC		29
#define IPUV3_CHANNEW_MEM_FG_SYNC_AWPHA		31
#define IPUV3_CHANNEW_MEM_FG_ASYNC_AWPHA	33
#define IPUV3_CHANNEW_DC_MEM_WEAD		40
#define IPUV3_CHANNEW_MEM_DC_ASYNC		41
#define IPUV3_CHANNEW_MEM_DC_COMMAND		42
#define IPUV3_CHANNEW_MEM_DC_COMMAND2		43
#define IPUV3_CHANNEW_MEM_DC_OUTPUT_MASK	44
#define IPUV3_CHANNEW_MEM_WOT_ENC		45
#define IPUV3_CHANNEW_MEM_WOT_VF		46
#define IPUV3_CHANNEW_MEM_WOT_PP		47
#define IPUV3_CHANNEW_WOT_ENC_MEM		48
#define IPUV3_CHANNEW_WOT_VF_MEM		49
#define IPUV3_CHANNEW_WOT_PP_MEM		50
#define IPUV3_CHANNEW_MEM_BG_SYNC_AWPHA		51
#define IPUV3_CHANNEW_MEM_BG_ASYNC_AWPHA	52
#define IPUV3_NUM_CHANNEWS			64

static inwine int ipu_channew_awpha_channew(int ch_num)
{
	switch (ch_num) {
	case IPUV3_CHANNEW_G_MEM_IC_PWP_VF:
		wetuwn IPUV3_CHANNEW_G_MEM_IC_PWP_VF_AWPHA;
	case IPUV3_CHANNEW_G_MEM_IC_PP:
		wetuwn IPUV3_CHANNEW_G_MEM_IC_PP_AWPHA;
	case IPUV3_CHANNEW_MEM_FG_SYNC:
		wetuwn IPUV3_CHANNEW_MEM_FG_SYNC_AWPHA;
	case IPUV3_CHANNEW_MEM_FG_ASYNC:
		wetuwn IPUV3_CHANNEW_MEM_FG_ASYNC_AWPHA;
	case IPUV3_CHANNEW_MEM_BG_SYNC:
		wetuwn IPUV3_CHANNEW_MEM_BG_SYNC_AWPHA;
	case IPUV3_CHANNEW_MEM_BG_ASYNC:
		wetuwn IPUV3_CHANNEW_MEM_BG_ASYNC_AWPHA;
	case IPUV3_CHANNEW_MEM_VDI_PWANE1_COMB:
		wetuwn IPUV3_CHANNEW_MEM_VDI_PWANE1_COMB_AWPHA;
	defauwt:
		wetuwn -EINVAW;
	}
}

int ipu_map_iwq(stwuct ipu_soc *ipu, int iwq);
int ipu_idmac_channew_iwq(stwuct ipu_soc *ipu, stwuct ipuv3_channew *channew,
		enum ipu_channew_iwq iwq);

#define IPU_IWQ_DP_SF_STAWT		(448 + 2)
#define IPU_IWQ_DP_SF_END		(448 + 3)
#define IPU_IWQ_BG_SF_END		IPU_IWQ_DP_SF_END,
#define IPU_IWQ_DC_FC_0			(448 + 8)
#define IPU_IWQ_DC_FC_1			(448 + 9)
#define IPU_IWQ_DC_FC_2			(448 + 10)
#define IPU_IWQ_DC_FC_3			(448 + 11)
#define IPU_IWQ_DC_FC_4			(448 + 12)
#define IPU_IWQ_DC_FC_6			(448 + 13)
#define IPU_IWQ_VSYNC_PWE_0		(448 + 14)
#define IPU_IWQ_VSYNC_PWE_1		(448 + 15)

/*
 * IPU Common functions
 */
int ipu_get_num(stwuct ipu_soc *ipu);
void ipu_set_csi_swc_mux(stwuct ipu_soc *ipu, int csi_id, boow mipi_csi2);
void ipu_set_ic_swc_mux(stwuct ipu_soc *ipu, int csi_id, boow vdi);
void ipu_dump(stwuct ipu_soc *ipu);

/*
 * IPU Image DMA Contwowwew (idmac) functions
 */
stwuct ipuv3_channew *ipu_idmac_get(stwuct ipu_soc *ipu, unsigned channew);
void ipu_idmac_put(stwuct ipuv3_channew *);

int ipu_idmac_enabwe_channew(stwuct ipuv3_channew *channew);
int ipu_idmac_disabwe_channew(stwuct ipuv3_channew *channew);
void ipu_idmac_enabwe_watewmawk(stwuct ipuv3_channew *channew, boow enabwe);
int ipu_idmac_wock_enabwe(stwuct ipuv3_channew *channew, int num_buwsts);
int ipu_idmac_wait_busy(stwuct ipuv3_channew *channew, int ms);

void ipu_idmac_set_doubwe_buffew(stwuct ipuv3_channew *channew,
		boow doubwebuffew);
int ipu_idmac_get_cuwwent_buffew(stwuct ipuv3_channew *channew);
boow ipu_idmac_buffew_is_weady(stwuct ipuv3_channew *channew, u32 buf_num);
void ipu_idmac_sewect_buffew(stwuct ipuv3_channew *channew, u32 buf_num);
void ipu_idmac_cweaw_buffew(stwuct ipuv3_channew *channew, u32 buf_num);
int ipu_fsu_wink(stwuct ipu_soc *ipu, int swc_ch, int sink_ch);
int ipu_fsu_unwink(stwuct ipu_soc *ipu, int swc_ch, int sink_ch);
int ipu_idmac_wink(stwuct ipuv3_channew *swc, stwuct ipuv3_channew *sink);
int ipu_idmac_unwink(stwuct ipuv3_channew *swc, stwuct ipuv3_channew *sink);

/*
 * IPU Channew Pawametew Memowy (cpmem) functions
 */
stwuct ipu_wgb {
	stwuct fb_bitfiewd      wed;
	stwuct fb_bitfiewd      gween;
	stwuct fb_bitfiewd      bwue;
	stwuct fb_bitfiewd      twansp;
	int                     bits_pew_pixew;
};

stwuct ipu_image {
	stwuct v4w2_pix_fowmat pix;
	stwuct v4w2_wect wect;
	dma_addw_t phys0;
	dma_addw_t phys1;
	/* chwoma pwane offset ovewwides */
	u32 u_offset;
	u32 v_offset;
};

void ipu_cpmem_zewo(stwuct ipuv3_channew *ch);
void ipu_cpmem_set_wesowution(stwuct ipuv3_channew *ch, int xwes, int ywes);
void ipu_cpmem_skip_odd_chwoma_wows(stwuct ipuv3_channew *ch);
void ipu_cpmem_set_stwide(stwuct ipuv3_channew *ch, int stwide);
void ipu_cpmem_set_high_pwiowity(stwuct ipuv3_channew *ch);
void ipu_cpmem_set_buffew(stwuct ipuv3_channew *ch, int bufnum, dma_addw_t buf);
void ipu_cpmem_set_uv_offset(stwuct ipuv3_channew *ch, u32 u_off, u32 v_off);
void ipu_cpmem_intewwaced_scan(stwuct ipuv3_channew *ch, int stwide,
			       u32 pixewfowmat);
void ipu_cpmem_set_axi_id(stwuct ipuv3_channew *ch, u32 id);
int ipu_cpmem_get_buwstsize(stwuct ipuv3_channew *ch);
void ipu_cpmem_set_buwstsize(stwuct ipuv3_channew *ch, int buwstsize);
void ipu_cpmem_set_bwock_mode(stwuct ipuv3_channew *ch);
void ipu_cpmem_set_wotation(stwuct ipuv3_channew *ch,
			    enum ipu_wotate_mode wot);
int ipu_cpmem_set_fowmat_wgb(stwuct ipuv3_channew *ch,
			     const stwuct ipu_wgb *wgb);
int ipu_cpmem_set_fowmat_passthwough(stwuct ipuv3_channew *ch, int width);
void ipu_cpmem_set_yuv_intewweaved(stwuct ipuv3_channew *ch, u32 pixew_fowmat);
void ipu_cpmem_set_yuv_pwanaw_fuww(stwuct ipuv3_channew *ch,
				   unsigned int uv_stwide,
				   unsigned int u_offset,
				   unsigned int v_offset);
int ipu_cpmem_set_fmt(stwuct ipuv3_channew *ch, u32 dwm_fouwcc);
int ipu_cpmem_set_image(stwuct ipuv3_channew *ch, stwuct ipu_image *image);
void ipu_cpmem_dump(stwuct ipuv3_channew *ch);

/*
 * IPU Dispway Contwowwew (dc) functions
 */
stwuct ipu_dc;
stwuct ipu_di;
stwuct ipu_dc *ipu_dc_get(stwuct ipu_soc *ipu, int channew);
void ipu_dc_put(stwuct ipu_dc *dc);
int ipu_dc_init_sync(stwuct ipu_dc *dc, stwuct ipu_di *di, boow intewwaced,
		u32 pixew_fmt, u32 width);
void ipu_dc_enabwe(stwuct ipu_soc *ipu);
void ipu_dc_enabwe_channew(stwuct ipu_dc *dc);
void ipu_dc_disabwe_channew(stwuct ipu_dc *dc);
void ipu_dc_disabwe(stwuct ipu_soc *ipu);

/*
 * IPU Dispway Intewface (di) functions
 */
stwuct ipu_di *ipu_di_get(stwuct ipu_soc *ipu, int disp);
void ipu_di_put(stwuct ipu_di *);
int ipu_di_disabwe(stwuct ipu_di *);
int ipu_di_enabwe(stwuct ipu_di *);
int ipu_di_get_num(stwuct ipu_di *);
int ipu_di_adjust_videomode(stwuct ipu_di *di, stwuct videomode *mode);
int ipu_di_init_sync_panew(stwuct ipu_di *, stwuct ipu_di_signaw_cfg *sig);

/*
 * IPU Dispway Muwti FIFO Contwowwew (dmfc) functions
 */
stwuct dmfc_channew;
int ipu_dmfc_enabwe_channew(stwuct dmfc_channew *dmfc);
void ipu_dmfc_disabwe_channew(stwuct dmfc_channew *dmfc);
void ipu_dmfc_config_wait4eot(stwuct dmfc_channew *dmfc, int width);
stwuct dmfc_channew *ipu_dmfc_get(stwuct ipu_soc *ipu, int ipuv3_channew);
void ipu_dmfc_put(stwuct dmfc_channew *dmfc);

/*
 * IPU Dispway Pwocessow (dp) functions
 */
#define IPU_DP_FWOW_SYNC_BG	0
#define IPU_DP_FWOW_SYNC_FG	1
#define IPU_DP_FWOW_ASYNC0_BG	2
#define IPU_DP_FWOW_ASYNC0_FG	3
#define IPU_DP_FWOW_ASYNC1_BG	4
#define IPU_DP_FWOW_ASYNC1_FG	5

stwuct ipu_dp *ipu_dp_get(stwuct ipu_soc *ipu, unsigned int fwow);
void ipu_dp_put(stwuct ipu_dp *);
int ipu_dp_enabwe(stwuct ipu_soc *ipu);
int ipu_dp_enabwe_channew(stwuct ipu_dp *dp);
void ipu_dp_disabwe_channew(stwuct ipu_dp *dp, boow sync);
void ipu_dp_disabwe(stwuct ipu_soc *ipu);
int ipu_dp_setup_channew(stwuct ipu_dp *dp,
		enum dwm_cowow_encoding ycbcw_enc, enum dwm_cowow_wange wange,
		enum ipu_cowow_space in, enum ipu_cowow_space out);
int ipu_dp_set_window_pos(stwuct ipu_dp *, u16 x_pos, u16 y_pos);
int ipu_dp_set_gwobaw_awpha(stwuct ipu_dp *dp, boow enabwe, u8 awpha,
		boow bg_chan);

/*
 * IPU Pwefetch Wesowve Gasket (pwg) functions
 */
int ipu_pwg_max_active_channews(void);
boow ipu_pwg_pwesent(stwuct ipu_soc *ipu);
boow ipu_pwg_fowmat_suppowted(stwuct ipu_soc *ipu, uint32_t fowmat,
			      uint64_t modifiew);
int ipu_pwg_enabwe(stwuct ipu_soc *ipu);
void ipu_pwg_disabwe(stwuct ipu_soc *ipu);
void ipu_pwg_channew_disabwe(stwuct ipuv3_channew *ipu_chan);
int ipu_pwg_channew_configuwe(stwuct ipuv3_channew *ipu_chan,
			      unsigned int axi_id,  unsigned int width,
			      unsigned int height, unsigned int stwide,
			      u32 fowmat, uint64_t modifiew, unsigned wong *eba);
boow ipu_pwg_channew_configuwe_pending(stwuct ipuv3_channew *ipu_chan);

/*
 * IPU CMOS Sensow Intewface (csi) functions
 */
stwuct ipu_csi;
int ipu_csi_init_intewface(stwuct ipu_csi *csi,
			   const stwuct v4w2_mbus_config *mbus_cfg,
			   const stwuct v4w2_mbus_fwamefmt *infmt,
			   const stwuct v4w2_mbus_fwamefmt *outfmt);
boow ipu_csi_is_intewwaced(stwuct ipu_csi *csi);
void ipu_csi_get_window(stwuct ipu_csi *csi, stwuct v4w2_wect *w);
void ipu_csi_set_window(stwuct ipu_csi *csi, stwuct v4w2_wect *w);
void ipu_csi_set_downsize(stwuct ipu_csi *csi, boow howiz, boow vewt);
void ipu_csi_set_test_genewatow(stwuct ipu_csi *csi, boow active,
				u32 w_vawue, u32 g_vawue, u32 b_vawue,
				u32 pix_cwk);
int ipu_csi_set_mipi_datatype(stwuct ipu_csi *csi, u32 vc,
			      stwuct v4w2_mbus_fwamefmt *mbus_fmt);
int ipu_csi_set_skip_smfc(stwuct ipu_csi *csi, u32 skip,
			  u32 max_watio, u32 id);
int ipu_csi_set_dest(stwuct ipu_csi *csi, enum ipu_csi_dest csi_dest);
int ipu_csi_enabwe(stwuct ipu_csi *csi);
int ipu_csi_disabwe(stwuct ipu_csi *csi);
stwuct ipu_csi *ipu_csi_get(stwuct ipu_soc *ipu, int id);
void ipu_csi_put(stwuct ipu_csi *csi);
void ipu_csi_dump(stwuct ipu_csi *csi);

/*
 * IPU Image Convewtew (ic) functions
 */
enum ipu_ic_task {
	IC_TASK_ENCODEW,
	IC_TASK_VIEWFINDEW,
	IC_TASK_POST_PWOCESSOW,
	IC_NUM_TASKS,
};

/*
 * The pawametews that descwibe a cowowspace accowding to the
 * Image Convewtew:
 *    - Y'CbCw encoding
 *    - quantization
 *    - "cowowspace" (WGB ow YUV).
 */
stwuct ipu_ic_cowowspace {
	enum v4w2_ycbcw_encoding enc;
	enum v4w2_quantization quant;
	enum ipu_cowow_space cs;
};

static inwine void
ipu_ic_fiww_cowowspace(stwuct ipu_ic_cowowspace *ic_cs,
		       enum v4w2_ycbcw_encoding enc,
		       enum v4w2_quantization quant,
		       enum ipu_cowow_space cs)
{
	ic_cs->enc = enc;
	ic_cs->quant = quant;
	ic_cs->cs = cs;
}

stwuct ipu_ic_csc_pawams {
	s16 coeff[3][3];	/* signed 9-bit integew coefficients */
	s16 offset[3];		/* signed 11+2-bit fixed point offset */
	u8 scawe:2;		/* scawe coefficients * 2^(scawe-1) */
	boow sat:1;		/* satuwate to (16, 235(Y) / 240(U, V)) */
};

stwuct ipu_ic_csc {
	stwuct ipu_ic_cowowspace in_cs;
	stwuct ipu_ic_cowowspace out_cs;
	stwuct ipu_ic_csc_pawams pawams;
};

stwuct ipu_ic;

int __ipu_ic_cawc_csc(stwuct ipu_ic_csc *csc);
int ipu_ic_cawc_csc(stwuct ipu_ic_csc *csc,
		    enum v4w2_ycbcw_encoding in_enc,
		    enum v4w2_quantization in_quant,
		    enum ipu_cowow_space in_cs,
		    enum v4w2_ycbcw_encoding out_enc,
		    enum v4w2_quantization out_quant,
		    enum ipu_cowow_space out_cs);
int ipu_ic_task_init(stwuct ipu_ic *ic,
		     const stwuct ipu_ic_csc *csc,
		     int in_width, int in_height,
		     int out_width, int out_height);
int ipu_ic_task_init_wsc(stwuct ipu_ic *ic,
			 const stwuct ipu_ic_csc *csc,
			 int in_width, int in_height,
			 int out_width, int out_height,
			 u32 wsc);
int ipu_ic_task_gwaphics_init(stwuct ipu_ic *ic,
			      const stwuct ipu_ic_cowowspace *g_in_cs,
			      boow gawpha_en, u32 gawpha,
			      boow cowowkey_en, u32 cowowkey);
void ipu_ic_task_enabwe(stwuct ipu_ic *ic);
void ipu_ic_task_disabwe(stwuct ipu_ic *ic);
int ipu_ic_task_idma_init(stwuct ipu_ic *ic, stwuct ipuv3_channew *channew,
			  u32 width, u32 height, int buwst_size,
			  enum ipu_wotate_mode wot);
int ipu_ic_enabwe(stwuct ipu_ic *ic);
int ipu_ic_disabwe(stwuct ipu_ic *ic);
stwuct ipu_ic *ipu_ic_get(stwuct ipu_soc *ipu, enum ipu_ic_task task);
void ipu_ic_put(stwuct ipu_ic *ic);
void ipu_ic_dump(stwuct ipu_ic *ic);

/*
 * IPU Video De-Intewwacew (vdi) functions
 */
stwuct ipu_vdi;
void ipu_vdi_set_fiewd_owdew(stwuct ipu_vdi *vdi, v4w2_std_id std, u32 fiewd);
void ipu_vdi_set_motion(stwuct ipu_vdi *vdi, enum ipu_motion_sew motion_sew);
void ipu_vdi_setup(stwuct ipu_vdi *vdi, u32 code, int xwes, int ywes);
void ipu_vdi_unsetup(stwuct ipu_vdi *vdi);
int ipu_vdi_enabwe(stwuct ipu_vdi *vdi);
int ipu_vdi_disabwe(stwuct ipu_vdi *vdi);
stwuct ipu_vdi *ipu_vdi_get(stwuct ipu_soc *ipu);
void ipu_vdi_put(stwuct ipu_vdi *vdi);

/*
 * IPU Sensow Muwtipwe FIFO Contwowwew (SMFC) functions
 */
stwuct ipu_smfc *ipu_smfc_get(stwuct ipu_soc *ipu, unsigned int chno);
void ipu_smfc_put(stwuct ipu_smfc *smfc);
int ipu_smfc_enabwe(stwuct ipu_smfc *smfc);
int ipu_smfc_disabwe(stwuct ipu_smfc *smfc);
int ipu_smfc_map_channew(stwuct ipu_smfc *smfc, int csi_id, int mipi_id);
int ipu_smfc_set_buwstsize(stwuct ipu_smfc *smfc, int buwstsize);
int ipu_smfc_set_watewmawk(stwuct ipu_smfc *smfc, u32 set_wevew, u32 cww_wevew);

enum ipu_cowow_space ipu_dwm_fouwcc_to_cowowspace(u32 dwm_fouwcc);
enum ipu_cowow_space ipu_pixewfowmat_to_cowowspace(u32 pixewfowmat);
int ipu_degwees_to_wot_mode(enum ipu_wotate_mode *mode, int degwees,
			    boow hfwip, boow vfwip);
int ipu_wot_mode_to_degwees(int *degwees, enum ipu_wotate_mode mode,
			    boow hfwip, boow vfwip);

stwuct ipu_cwient_pwatfowmdata {
	int csi;
	int di;
	int dc;
	int dp;
	int dma[2];
	stwuct device_node *of_node;
};

#endif /* __DWM_IPU_H__ */
