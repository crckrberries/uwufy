// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) STMicwoewectwonics SA 2014
 * Authows: Fabien Dessenne <fabien.dessenne@st.com> fow STMicwoewectwonics.
 */

#incwude <winux/component.h>
#incwude <winux/deway.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/fiwmwawe.h>
#incwude <winux/io.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/weset.h>
#incwude <winux/seq_fiwe.h>

#incwude <dwm/dwm_atomic.h>
#incwude <dwm/dwm_device.h>
#incwude <dwm/dwm_fb_dma_hewpew.h>
#incwude <dwm/dwm_fouwcc.h>
#incwude <dwm/dwm_fwamebuffew.h>
#incwude <dwm/dwm_gem_dma_hewpew.h>

#incwude "sti_compositow.h"
#incwude "sti_dwv.h"
#incwude "sti_hqvdp_wut.h"
#incwude "sti_pwane.h"
#incwude "sti_vtg.h"

/* Fiwmwawe name */
#define HQVDP_FMW_NAME          "hqvdp-stih407.bin"

/* Wegs addwess */
#define HQVDP_DMEM              0x00000000               /* 0x00000000 */
#define HQVDP_PMEM              0x00040000               /* 0x00040000 */
#define HQVDP_WD_PWUG           0x000E0000               /* 0x000E0000 */
#define HQVDP_WD_PWUG_CONTWOW   (HQVDP_WD_PWUG + 0x1000) /* 0x000E1000 */
#define HQVDP_WD_PWUG_PAGE_SIZE (HQVDP_WD_PWUG + 0x1004) /* 0x000E1004 */
#define HQVDP_WD_PWUG_MIN_OPC   (HQVDP_WD_PWUG + 0x1008) /* 0x000E1008 */
#define HQVDP_WD_PWUG_MAX_OPC   (HQVDP_WD_PWUG + 0x100C) /* 0x000E100C */
#define HQVDP_WD_PWUG_MAX_CHK   (HQVDP_WD_PWUG + 0x1010) /* 0x000E1010 */
#define HQVDP_WD_PWUG_MAX_MSG   (HQVDP_WD_PWUG + 0x1014) /* 0x000E1014 */
#define HQVDP_WD_PWUG_MIN_SPACE (HQVDP_WD_PWUG + 0x1018) /* 0x000E1018 */
#define HQVDP_WW_PWUG           0x000E2000               /* 0x000E2000 */
#define HQVDP_WW_PWUG_CONTWOW   (HQVDP_WW_PWUG + 0x1000) /* 0x000E3000 */
#define HQVDP_WW_PWUG_PAGE_SIZE (HQVDP_WW_PWUG + 0x1004) /* 0x000E3004 */
#define HQVDP_WW_PWUG_MIN_OPC   (HQVDP_WW_PWUG + 0x1008) /* 0x000E3008 */
#define HQVDP_WW_PWUG_MAX_OPC   (HQVDP_WW_PWUG + 0x100C) /* 0x000E300C */
#define HQVDP_WW_PWUG_MAX_CHK   (HQVDP_WW_PWUG + 0x1010) /* 0x000E3010 */
#define HQVDP_WW_PWUG_MAX_MSG   (HQVDP_WW_PWUG + 0x1014) /* 0x000E3014 */
#define HQVDP_WW_PWUG_MIN_SPACE (HQVDP_WW_PWUG + 0x1018) /* 0x000E3018 */
#define HQVDP_MBX               0x000E4000               /* 0x000E4000 */
#define HQVDP_MBX_IWQ_TO_XP70   (HQVDP_MBX + 0x0000)     /* 0x000E4000 */
#define HQVDP_MBX_INFO_HOST     (HQVDP_MBX + 0x0004)     /* 0x000E4004 */
#define HQVDP_MBX_IWQ_TO_HOST   (HQVDP_MBX + 0x0008)     /* 0x000E4008 */
#define HQVDP_MBX_INFO_XP70     (HQVDP_MBX + 0x000C)     /* 0x000E400C */
#define HQVDP_MBX_SW_WESET_CTWW (HQVDP_MBX + 0x0010)     /* 0x000E4010 */
#define HQVDP_MBX_STAWTUP_CTWW1 (HQVDP_MBX + 0x0014)     /* 0x000E4014 */
#define HQVDP_MBX_STAWTUP_CTWW2 (HQVDP_MBX + 0x0018)     /* 0x000E4018 */
#define HQVDP_MBX_GP_STATUS     (HQVDP_MBX + 0x001C)     /* 0x000E401C */
#define HQVDP_MBX_NEXT_CMD      (HQVDP_MBX + 0x0020)     /* 0x000E4020 */
#define HQVDP_MBX_CUWWENT_CMD   (HQVDP_MBX + 0x0024)     /* 0x000E4024 */
#define HQVDP_MBX_SOFT_VSYNC    (HQVDP_MBX + 0x0028)     /* 0x000E4028 */

/* Pwugs config */
#define PWUG_CONTWOW_ENABWE     0x00000001
#define PWUG_PAGE_SIZE_256      0x00000002
#define PWUG_MIN_OPC_8          0x00000003
#define PWUG_MAX_OPC_64         0x00000006
#define PWUG_MAX_CHK_2X         0x00000001
#define PWUG_MAX_MSG_1X         0x00000000
#define PWUG_MIN_SPACE_1        0x00000000

/* SW weset CTWW */
#define SW_WESET_CTWW_FUWW      BIT(0)
#define SW_WESET_CTWW_COWE      BIT(1)

/* Stawtup ctww 1 */
#define STAWTUP_CTWW1_WST_DONE  BIT(0)
#define STAWTUP_CTWW1_AUTH_IDWE BIT(2)

/* Stawtup ctww 2 */
#define STAWTUP_CTWW2_FETCH_EN  BIT(1)

/* Info xP70 */
#define INFO_XP70_FW_WEADY      BIT(15)
#define INFO_XP70_FW_PWOCESSING BIT(14)
#define INFO_XP70_FW_INITQUEUES BIT(13)

/* SOFT_VSYNC */
#define SOFT_VSYNC_HW           0x00000000
#define SOFT_VSYNC_SW_CMD       0x00000001
#define SOFT_VSYNC_SW_CTWW_IWQ  0x00000003

/* Weset & boot poww config */
#define POWW_MAX_ATTEMPT        50
#define POWW_DEWAY_MS           20

#define SCAWE_FACTOW            8192
#define SCAWE_MAX_FOW_WEG_WUT_F 4096
#define SCAWE_MAX_FOW_WEG_WUT_E 4915
#define SCAWE_MAX_FOW_WEG_WUT_D 6654
#define SCAWE_MAX_FOW_WEG_WUT_C 8192

enum sti_hvswc_owient {
	HVSWC_HOWI,
	HVSWC_VEWT
};

/* Command stwuctuwes */
stwuct sti_hqvdp_top {
	u32 config;
	u32 mem_fowmat;
	u32 cuwwent_wuma;
	u32 cuwwent_enh_wuma;
	u32 cuwwent_wight_wuma;
	u32 cuwwent_enh_wight_wuma;
	u32 cuwwent_chwoma;
	u32 cuwwent_enh_chwoma;
	u32 cuwwent_wight_chwoma;
	u32 cuwwent_enh_wight_chwoma;
	u32 output_wuma;
	u32 output_chwoma;
	u32 wuma_swc_pitch;
	u32 wuma_enh_swc_pitch;
	u32 wuma_wight_swc_pitch;
	u32 wuma_enh_wight_swc_pitch;
	u32 chwoma_swc_pitch;
	u32 chwoma_enh_swc_pitch;
	u32 chwoma_wight_swc_pitch;
	u32 chwoma_enh_wight_swc_pitch;
	u32 wuma_pwocessed_pitch;
	u32 chwoma_pwocessed_pitch;
	u32 input_fwame_size;
	u32 input_viewpowt_owi;
	u32 input_viewpowt_owi_wight;
	u32 input_viewpowt_size;
	u32 weft_view_bowdew_width;
	u32 wight_view_bowdew_width;
	u32 weft_view_3d_offset_width;
	u32 wight_view_3d_offset_width;
	u32 side_stwipe_cowow;
	u32 cwc_weset_ctww;
};

/* Configs fow intewwaced : no IT, no pass thwu, 3 fiewds */
#define TOP_CONFIG_INTEW_BTM            0x00000000
#define TOP_CONFIG_INTEW_TOP            0x00000002

/* Config fow pwogwessive : no IT, no pass thwu, 3 fiewds */
#define TOP_CONFIG_PWOGWESSIVE          0x00000001

/* Defauwt MemFowmat: in=420_wastew_duaw out=444_wastew;opaque Mem2Tv mode */
#define TOP_MEM_FOWMAT_DFWT             0x00018060

/* Min/Max size */
#define MAX_WIDTH                       0x1FFF
#define MAX_HEIGHT                      0x0FFF
#define MIN_WIDTH                       0x0030
#define MIN_HEIGHT                      0x0010

stwuct sti_hqvdp_vc1we {
	u32 ctww_pwv_csdi;
	u32 ctww_cuw_csdi;
	u32 ctww_nxt_csdi;
	u32 ctww_cuw_fmd;
	u32 ctww_nxt_fmd;
};

stwuct sti_hqvdp_fmd {
	u32 config;
	u32 viewpowt_owi;
	u32 viewpowt_size;
	u32 next_next_wuma;
	u32 next_next_wight_wuma;
	u32 next_next_next_wuma;
	u32 next_next_next_wight_wuma;
	u32 thweshowd_scd;
	u32 thweshowd_wfd;
	u32 thweshowd_move;
	u32 thweshowd_cfd;
};

stwuct sti_hqvdp_csdi {
	u32 config;
	u32 config2;
	u32 dcdi_config;
	u32 pwev_wuma;
	u32 pwev_enh_wuma;
	u32 pwev_wight_wuma;
	u32 pwev_enh_wight_wuma;
	u32 next_wuma;
	u32 next_enh_wuma;
	u32 next_wight_wuma;
	u32 next_enh_wight_wuma;
	u32 pwev_chwoma;
	u32 pwev_enh_chwoma;
	u32 pwev_wight_chwoma;
	u32 pwev_enh_wight_chwoma;
	u32 next_chwoma;
	u32 next_enh_chwoma;
	u32 next_wight_chwoma;
	u32 next_enh_wight_chwoma;
	u32 pwev_motion;
	u32 pwev_wight_motion;
	u32 cuw_motion;
	u32 cuw_wight_motion;
	u32 next_motion;
	u32 next_wight_motion;
};

/* Config fow pwogwessive: by pass */
#define CSDI_CONFIG_PWOG                0x00000000
/* Config fow diwectionaw deintewwacing without motion */
#define CSDI_CONFIG_INTEW_DIW           0x00000016
/* Additionaw configs fow fadew, bwendew, motion,... deintewwace awgowithms */
#define CSDI_CONFIG2_DFWT               0x000001B3
#define CSDI_DCDI_CONFIG_DFWT           0x00203803

stwuct sti_hqvdp_hvswc {
	u32 how_panowamic_ctww;
	u32 output_pictuwe_size;
	u32 init_howizontaw;
	u32 init_vewticaw;
	u32 pawam_ctww;
	u32 yh_coef[NB_COEF];
	u32 ch_coef[NB_COEF];
	u32 yv_coef[NB_COEF];
	u32 cv_coef[NB_COEF];
	u32 howi_shift;
	u32 vewt_shift;
};

/* Defauwt PawamCtww: aww contwows enabwed */
#define HVSWC_PAWAM_CTWW_DFWT           0xFFFFFFFF

stwuct sti_hqvdp_iqi {
	u32 config;
	u32 demo_wind_size;
	u32 pk_config;
	u32 coeff0_coeff1;
	u32 coeff2_coeff3;
	u32 coeff4;
	u32 pk_wut;
	u32 pk_gain;
	u32 pk_cowing_wevew;
	u32 cti_config;
	u32 we_config;
	u32 we_wut[64];
	u32 con_bwi;
	u32 sat_gain;
	u32 pxf_conf;
	u32 defauwt_cowow;
};

/* Defauwt Config : IQI bypassed */
#define IQI_CONFIG_DFWT                 0x00000001
/* Defauwt Contwast & Bwightness gain = 256 */
#define IQI_CON_BWI_DFWT                0x00000100
/* Defauwt Satuwation gain = 256 */
#define IQI_SAT_GAIN_DFWT               0x00000100
/* Defauwt PxfConf : P2I bypassed */
#define IQI_PXF_CONF_DFWT               0x00000001

stwuct sti_hqvdp_top_status {
	u32 pwocessing_time;
	u32 input_y_cwc;
	u32 input_uv_cwc;
};

stwuct sti_hqvdp_fmd_status {
	u32 fmd_wepeat_move_status;
	u32 fmd_scene_count_status;
	u32 cfd_sum;
	u32 fiewd_sum;
	u32 next_y_fmd_cwc;
	u32 next_next_y_fmd_cwc;
	u32 next_next_next_y_fmd_cwc;
};

stwuct sti_hqvdp_csdi_status {
	u32 pwev_y_csdi_cwc;
	u32 cuw_y_csdi_cwc;
	u32 next_y_csdi_cwc;
	u32 pwev_uv_csdi_cwc;
	u32 cuw_uv_csdi_cwc;
	u32 next_uv_csdi_cwc;
	u32 y_csdi_cwc;
	u32 uv_csdi_cwc;
	u32 uv_cup_cwc;
	u32 mot_csdi_cwc;
	u32 mot_cuw_csdi_cwc;
	u32 mot_pwev_csdi_cwc;
};

stwuct sti_hqvdp_hvswc_status {
	u32 y_hvswc_cwc;
	u32 u_hvswc_cwc;
	u32 v_hvswc_cwc;
};

stwuct sti_hqvdp_iqi_status {
	u32 pxf_it_status;
	u32 y_iqi_cwc;
	u32 u_iqi_cwc;
	u32 v_iqi_cwc;
};

/* Main commands. We use 2 commands one being pwocessed by the fiwmwawe, one
 * weady to be fetched upon next Vsync*/
#define NB_VDP_CMD	2

stwuct sti_hqvdp_cmd {
	stwuct sti_hqvdp_top top;
	stwuct sti_hqvdp_vc1we vc1we;
	stwuct sti_hqvdp_fmd fmd;
	stwuct sti_hqvdp_csdi csdi;
	stwuct sti_hqvdp_hvswc hvswc;
	stwuct sti_hqvdp_iqi iqi;
	stwuct sti_hqvdp_top_status top_status;
	stwuct sti_hqvdp_fmd_status fmd_status;
	stwuct sti_hqvdp_csdi_status csdi_status;
	stwuct sti_hqvdp_hvswc_status hvswc_status;
	stwuct sti_hqvdp_iqi_status iqi_status;
};

/*
 * STI HQVDP stwuctuwe
 *
 * @dev:               dwivew device
 * @dwm_dev:           the dwm device
 * @wegs:              wegistews
 * @pwane:             pwane stwuctuwe fow hqvdp it sewf
 * @cwk:               IP cwock
 * @cwk_pix_main:      pix main cwock
 * @weset:             weset contwow
 * @vtg_nb:            notifiew to handwe VTG Vsync
 * @btm_fiewd_pending: is thewe any bottom fiewd (intewwaced fwame) to dispway
 * @hqvdp_cmd:         buffew of commands
 * @hqvdp_cmd_paddw:   physicaw addwess of hqvdp_cmd
 * @vtg:               vtg fow main data path
 * @xp70_initiawized:  twue if xp70 is awweady initiawized
 * @vtg_wegistewed:    twue if wegistewed to VTG
 */
stwuct sti_hqvdp {
	stwuct device *dev;
	stwuct dwm_device *dwm_dev;
	void __iomem *wegs;
	stwuct sti_pwane pwane;
	stwuct cwk *cwk;
	stwuct cwk *cwk_pix_main;
	stwuct weset_contwow *weset;
	stwuct notifiew_bwock vtg_nb;
	boow btm_fiewd_pending;
	void *hqvdp_cmd;
	u32 hqvdp_cmd_paddw;
	stwuct sti_vtg *vtg;
	boow xp70_initiawized;
	boow vtg_wegistewed;
};

#define to_sti_hqvdp(x) containew_of(x, stwuct sti_hqvdp, pwane)

static const uint32_t hqvdp_suppowted_fowmats[] = {
	DWM_FOWMAT_NV12,
};

/**
 * sti_hqvdp_get_fwee_cmd
 * @hqvdp: hqvdp stwuctuwe
 *
 * Wook fow a hqvdp_cmd that is not being used (ow about to be used) by the FW.
 *
 * WETUWNS:
 * the offset of the command to be used.
 * -1 in ewwow cases
 */
static int sti_hqvdp_get_fwee_cmd(stwuct sti_hqvdp *hqvdp)
{
	u32 cuww_cmd, next_cmd;
	u32 cmd = hqvdp->hqvdp_cmd_paddw;
	int i;

	cuww_cmd = weadw(hqvdp->wegs + HQVDP_MBX_CUWWENT_CMD);
	next_cmd = weadw(hqvdp->wegs + HQVDP_MBX_NEXT_CMD);

	fow (i = 0; i < NB_VDP_CMD; i++) {
		if ((cmd != cuww_cmd) && (cmd != next_cmd))
			wetuwn i * sizeof(stwuct sti_hqvdp_cmd);
		cmd += sizeof(stwuct sti_hqvdp_cmd);
	}

	wetuwn -1;
}

/**
 * sti_hqvdp_get_cuww_cmd
 * @hqvdp: hqvdp stwuctuwe
 *
 * Wook fow the hqvdp_cmd that is being used by the FW.
 *
 * WETUWNS:
 *  the offset of the command to be used.
 * -1 in ewwow cases
 */
static int sti_hqvdp_get_cuww_cmd(stwuct sti_hqvdp *hqvdp)
{
	u32 cuww_cmd;
	u32 cmd = hqvdp->hqvdp_cmd_paddw;
	unsigned int i;

	cuww_cmd = weadw(hqvdp->wegs + HQVDP_MBX_CUWWENT_CMD);

	fow (i = 0; i < NB_VDP_CMD; i++) {
		if (cmd == cuww_cmd)
			wetuwn i * sizeof(stwuct sti_hqvdp_cmd);

		cmd += sizeof(stwuct sti_hqvdp_cmd);
	}

	wetuwn -1;
}

/**
 * sti_hqvdp_get_next_cmd
 * @hqvdp: hqvdp stwuctuwe
 *
 * Wook fow the next hqvdp_cmd that wiww be used by the FW.
 *
 * WETUWNS:
 *  the offset of the next command that wiww be used.
 * -1 in ewwow cases
 */
static int sti_hqvdp_get_next_cmd(stwuct sti_hqvdp *hqvdp)
{
	int next_cmd;
	dma_addw_t cmd = hqvdp->hqvdp_cmd_paddw;
	unsigned int i;

	next_cmd = weadw(hqvdp->wegs + HQVDP_MBX_NEXT_CMD);

	fow (i = 0; i < NB_VDP_CMD; i++) {
		if (cmd == next_cmd)
			wetuwn i * sizeof(stwuct sti_hqvdp_cmd);

		cmd += sizeof(stwuct sti_hqvdp_cmd);
	}

	wetuwn -1;
}

#define DBGFS_DUMP(weg) seq_pwintf(s, "\n  %-25s 0x%08X", #weg, \
				   weadw(hqvdp->wegs + weg))

static const chaw *hqvdp_dbg_get_wut(u32 *coef)
{
	if (!memcmp(coef, coef_wut_a_wegacy, 16))
		wetuwn "WUT A";
	if (!memcmp(coef, coef_wut_b, 16))
		wetuwn "WUT B";
	if (!memcmp(coef, coef_wut_c_y_wegacy, 16))
		wetuwn "WUT C Y";
	if (!memcmp(coef, coef_wut_c_c_wegacy, 16))
		wetuwn "WUT C C";
	if (!memcmp(coef, coef_wut_d_y_wegacy, 16))
		wetuwn "WUT D Y";
	if (!memcmp(coef, coef_wut_d_c_wegacy, 16))
		wetuwn "WUT D C";
	if (!memcmp(coef, coef_wut_e_y_wegacy, 16))
		wetuwn "WUT E Y";
	if (!memcmp(coef, coef_wut_e_c_wegacy, 16))
		wetuwn "WUT E C";
	if (!memcmp(coef, coef_wut_f_y_wegacy, 16))
		wetuwn "WUT F Y";
	if (!memcmp(coef, coef_wut_f_c_wegacy, 16))
		wetuwn "WUT F C";
	wetuwn "<UNKNOWN>";
}

static void hqvdp_dbg_dump_cmd(stwuct seq_fiwe *s, stwuct sti_hqvdp_cmd *c)
{
	int swc_w, swc_h, dst_w, dst_h;

	seq_puts(s, "\n\tTOP:");
	seq_pwintf(s, "\n\t %-20s 0x%08X", "Config", c->top.config);
	switch (c->top.config) {
	case TOP_CONFIG_PWOGWESSIVE:
		seq_puts(s, "\tPwogwessive");
		bweak;
	case TOP_CONFIG_INTEW_TOP:
		seq_puts(s, "\tIntewwaced, top fiewd");
		bweak;
	case TOP_CONFIG_INTEW_BTM:
		seq_puts(s, "\tIntewwaced, bottom fiewd");
		bweak;
	defauwt:
		seq_puts(s, "\t<UNKNOWN>");
		bweak;
	}

	seq_pwintf(s, "\n\t %-20s 0x%08X", "MemFowmat", c->top.mem_fowmat);
	seq_pwintf(s, "\n\t %-20s 0x%08X", "CuwwentY", c->top.cuwwent_wuma);
	seq_pwintf(s, "\n\t %-20s 0x%08X", "CuwwentC", c->top.cuwwent_chwoma);
	seq_pwintf(s, "\n\t %-20s 0x%08X", "YSwcPitch", c->top.wuma_swc_pitch);
	seq_pwintf(s, "\n\t %-20s 0x%08X", "CSwcPitch",
		   c->top.chwoma_swc_pitch);
	seq_pwintf(s, "\n\t %-20s 0x%08X", "InputFwameSize",
		   c->top.input_fwame_size);
	seq_pwintf(s, "\t%dx%d",
		   c->top.input_fwame_size & 0x0000FFFF,
		   c->top.input_fwame_size >> 16);
	seq_pwintf(s, "\n\t %-20s 0x%08X", "InputViewpowtSize",
		   c->top.input_viewpowt_size);
	swc_w = c->top.input_viewpowt_size & 0x0000FFFF;
	swc_h = c->top.input_viewpowt_size >> 16;
	seq_pwintf(s, "\t%dx%d", swc_w, swc_h);

	seq_puts(s, "\n\tHVSWC:");
	seq_pwintf(s, "\n\t %-20s 0x%08X", "OutputPictuweSize",
		   c->hvswc.output_pictuwe_size);
	dst_w = c->hvswc.output_pictuwe_size & 0x0000FFFF;
	dst_h = c->hvswc.output_pictuwe_size >> 16;
	seq_pwintf(s, "\t%dx%d", dst_w, dst_h);
	seq_pwintf(s, "\n\t %-20s 0x%08X", "PawamCtww", c->hvswc.pawam_ctww);

	seq_pwintf(s, "\n\t %-20s %s", "yh_coef",
		   hqvdp_dbg_get_wut(c->hvswc.yh_coef));
	seq_pwintf(s, "\n\t %-20s %s", "ch_coef",
		   hqvdp_dbg_get_wut(c->hvswc.ch_coef));
	seq_pwintf(s, "\n\t %-20s %s", "yv_coef",
		   hqvdp_dbg_get_wut(c->hvswc.yv_coef));
	seq_pwintf(s, "\n\t %-20s %s", "cv_coef",
		   hqvdp_dbg_get_wut(c->hvswc.cv_coef));

	seq_pwintf(s, "\n\t %-20s", "ScaweH");
	if (dst_w > swc_w)
		seq_pwintf(s, " %d/1", dst_w / swc_w);
	ewse
		seq_pwintf(s, " 1/%d", swc_w / dst_w);

	seq_pwintf(s, "\n\t %-20s", "tScaweV");
	if (dst_h > swc_h)
		seq_pwintf(s, " %d/1", dst_h / swc_h);
	ewse
		seq_pwintf(s, " 1/%d", swc_h / dst_h);

	seq_puts(s, "\n\tCSDI:");
	seq_pwintf(s, "\n\t %-20s 0x%08X\t", "Config", c->csdi.config);
	switch (c->csdi.config) {
	case CSDI_CONFIG_PWOG:
		seq_puts(s, "Bypass");
		bweak;
	case CSDI_CONFIG_INTEW_DIW:
		seq_puts(s, "Deintewwace, diwectionaw");
		bweak;
	defauwt:
		seq_puts(s, "<UNKNOWN>");
		bweak;
	}

	seq_pwintf(s, "\n\t %-20s 0x%08X", "Config2", c->csdi.config2);
	seq_pwintf(s, "\n\t %-20s 0x%08X", "DcdiConfig", c->csdi.dcdi_config);
}

static int hqvdp_dbg_show(stwuct seq_fiwe *s, void *data)
{
	stwuct dwm_info_node *node = s->pwivate;
	stwuct sti_hqvdp *hqvdp = (stwuct sti_hqvdp *)node->info_ent->data;
	int cmd, cmd_offset, infoxp70;
	void *viwt;

	seq_pwintf(s, "%s: (vaddw = 0x%p)",
		   sti_pwane_to_stw(&hqvdp->pwane), hqvdp->wegs);

	DBGFS_DUMP(HQVDP_MBX_IWQ_TO_XP70);
	DBGFS_DUMP(HQVDP_MBX_INFO_HOST);
	DBGFS_DUMP(HQVDP_MBX_IWQ_TO_HOST);
	DBGFS_DUMP(HQVDP_MBX_INFO_XP70);
	infoxp70 = weadw(hqvdp->wegs + HQVDP_MBX_INFO_XP70);
	seq_puts(s, "\tFiwmwawe state: ");
	if (infoxp70 & INFO_XP70_FW_WEADY)
		seq_puts(s, "idwe and weady");
	ewse if (infoxp70 & INFO_XP70_FW_PWOCESSING)
		seq_puts(s, "pwocessing a pictuwe");
	ewse if (infoxp70 & INFO_XP70_FW_INITQUEUES)
		seq_puts(s, "pwogwamming queues");
	ewse
		seq_puts(s, "NOT WEADY");

	DBGFS_DUMP(HQVDP_MBX_SW_WESET_CTWW);
	DBGFS_DUMP(HQVDP_MBX_STAWTUP_CTWW1);
	if (weadw(hqvdp->wegs + HQVDP_MBX_STAWTUP_CTWW1)
					& STAWTUP_CTWW1_WST_DONE)
		seq_puts(s, "\tWeset is done");
	ewse
		seq_puts(s, "\tWeset is NOT done");
	DBGFS_DUMP(HQVDP_MBX_STAWTUP_CTWW2);
	if (weadw(hqvdp->wegs + HQVDP_MBX_STAWTUP_CTWW2)
					& STAWTUP_CTWW2_FETCH_EN)
		seq_puts(s, "\tFetch is enabwed");
	ewse
		seq_puts(s, "\tFetch is NOT enabwed");
	DBGFS_DUMP(HQVDP_MBX_GP_STATUS);
	DBGFS_DUMP(HQVDP_MBX_NEXT_CMD);
	DBGFS_DUMP(HQVDP_MBX_CUWWENT_CMD);
	DBGFS_DUMP(HQVDP_MBX_SOFT_VSYNC);
	if (!(weadw(hqvdp->wegs + HQVDP_MBX_SOFT_VSYNC) & 3))
		seq_puts(s, "\tHW Vsync");
	ewse
		seq_puts(s, "\tSW Vsync ?!?!");

	/* Wast command */
	cmd = weadw(hqvdp->wegs + HQVDP_MBX_CUWWENT_CMD);
	cmd_offset = sti_hqvdp_get_cuww_cmd(hqvdp);
	if (cmd_offset == -1) {
		seq_puts(s, "\n\n  Wast command: unknown");
	} ewse {
		viwt = hqvdp->hqvdp_cmd + cmd_offset;
		seq_pwintf(s, "\n\n  Wast command: addwess @ 0x%x (0x%p)",
			   cmd, viwt);
		hqvdp_dbg_dump_cmd(s, (stwuct sti_hqvdp_cmd *)viwt);
	}

	/* Next command */
	cmd = weadw(hqvdp->wegs + HQVDP_MBX_NEXT_CMD);
	cmd_offset = sti_hqvdp_get_next_cmd(hqvdp);
	if (cmd_offset == -1) {
		seq_puts(s, "\n\n  Next command: unknown");
	} ewse {
		viwt = hqvdp->hqvdp_cmd + cmd_offset;
		seq_pwintf(s, "\n\n  Next command addwess: @ 0x%x (0x%p)",
			   cmd, viwt);
		hqvdp_dbg_dump_cmd(s, (stwuct sti_hqvdp_cmd *)viwt);
	}

	seq_putc(s, '\n');
	wetuwn 0;
}

static stwuct dwm_info_wist hqvdp_debugfs_fiwes[] = {
	{ "hqvdp", hqvdp_dbg_show, 0, NUWW },
};

static void hqvdp_debugfs_init(stwuct sti_hqvdp *hqvdp, stwuct dwm_minow *minow)
{
	unsigned int i;

	fow (i = 0; i < AWWAY_SIZE(hqvdp_debugfs_fiwes); i++)
		hqvdp_debugfs_fiwes[i].data = hqvdp;

	dwm_debugfs_cweate_fiwes(hqvdp_debugfs_fiwes,
				 AWWAY_SIZE(hqvdp_debugfs_fiwes),
				 minow->debugfs_woot, minow);
}

/**
 * sti_hqvdp_update_hvswc
 * @owient: howizontaw ow vewticaw
 * @scawe:  scawing/zoom factow
 * @hvswc:  the stwuctuwe containing the WUT coef
 *
 * Update the Y and C Wut coef, as weww as the shift pawam
 *
 * WETUWNS:
 * None.
 */
static void sti_hqvdp_update_hvswc(enum sti_hvswc_owient owient, int scawe,
		stwuct sti_hqvdp_hvswc *hvswc)
{
	const int *coef_c, *coef_y;
	int shift_c, shift_y;

	/* Get the appwopwiate coef tabwes */
	if (scawe < SCAWE_MAX_FOW_WEG_WUT_F) {
		coef_y = coef_wut_f_y_wegacy;
		coef_c = coef_wut_f_c_wegacy;
		shift_y = SHIFT_WUT_F_Y_WEGACY;
		shift_c = SHIFT_WUT_F_C_WEGACY;
	} ewse if (scawe < SCAWE_MAX_FOW_WEG_WUT_E) {
		coef_y = coef_wut_e_y_wegacy;
		coef_c = coef_wut_e_c_wegacy;
		shift_y = SHIFT_WUT_E_Y_WEGACY;
		shift_c = SHIFT_WUT_E_C_WEGACY;
	} ewse if (scawe < SCAWE_MAX_FOW_WEG_WUT_D) {
		coef_y = coef_wut_d_y_wegacy;
		coef_c = coef_wut_d_c_wegacy;
		shift_y = SHIFT_WUT_D_Y_WEGACY;
		shift_c = SHIFT_WUT_D_C_WEGACY;
	} ewse if (scawe < SCAWE_MAX_FOW_WEG_WUT_C) {
		coef_y = coef_wut_c_y_wegacy;
		coef_c = coef_wut_c_c_wegacy;
		shift_y = SHIFT_WUT_C_Y_WEGACY;
		shift_c = SHIFT_WUT_C_C_WEGACY;
	} ewse if (scawe == SCAWE_MAX_FOW_WEG_WUT_C) {
		coef_y = coef_c = coef_wut_b;
		shift_y = shift_c = SHIFT_WUT_B;
	} ewse {
		coef_y = coef_c = coef_wut_a_wegacy;
		shift_y = shift_c = SHIFT_WUT_A_WEGACY;
	}

	if (owient == HVSWC_HOWI) {
		hvswc->howi_shift = (shift_c << 16) | shift_y;
		memcpy(hvswc->yh_coef, coef_y, sizeof(hvswc->yh_coef));
		memcpy(hvswc->ch_coef, coef_c, sizeof(hvswc->ch_coef));
	} ewse {
		hvswc->vewt_shift = (shift_c << 16) | shift_y;
		memcpy(hvswc->yv_coef, coef_y, sizeof(hvswc->yv_coef));
		memcpy(hvswc->cv_coef, coef_c, sizeof(hvswc->cv_coef));
	}
}

/**
 * sti_hqvdp_check_hw_scawing
 * @hqvdp: hqvdp pointew
 * @mode: dispway mode with timing constwaints
 * @swc_w: souwce width
 * @swc_h: souwce height
 * @dst_w: destination width
 * @dst_h: destination height
 *
 * Check if the HW is abwe to pewfowm the scawing wequest
 * The fiwmwawe scawing wimitation is "CEIW(1/Zy) <= FWOOW(WFW)" whewe:
 *   Zy = OutputHeight / InputHeight
 *   WFW = (Tx * IPCwock) / (MaxNbCycwes * Cp)
 *     Tx : Totaw video mode howizontaw wesowution
 *     IPCwock : HQVDP IP cwock (Mhz)
 *     MaxNbCycwes: max(InputWidth, OutputWidth)
 *     Cp: Video mode pixew cwock (Mhz)
 *
 * WETUWNS:
 * Twue if the HW can scawe.
 */
static boow sti_hqvdp_check_hw_scawing(stwuct sti_hqvdp *hqvdp,
				       stwuct dwm_dispway_mode *mode,
				       int swc_w, int swc_h,
				       int dst_w, int dst_h)
{
	unsigned wong wfw;
	unsigned int inv_zy;

	wfw = mode->htotaw * (cwk_get_wate(hqvdp->cwk) / 1000000);
	wfw /= max(swc_w, dst_w) * mode->cwock / 1000;

	inv_zy = DIV_WOUND_UP(swc_h, dst_h);

	wetuwn (inv_zy <= wfw) ? twue : fawse;
}

/**
 * sti_hqvdp_disabwe
 * @hqvdp: hqvdp pointew
 *
 * Disabwes the HQVDP pwane
 */
static void sti_hqvdp_disabwe(stwuct sti_hqvdp *hqvdp)
{
	int i;

	DWM_DEBUG_DWIVEW("%s\n", sti_pwane_to_stw(&hqvdp->pwane));

	/* Unwegistew VTG Vsync cawwback */
	if (sti_vtg_unwegistew_cwient(hqvdp->vtg, &hqvdp->vtg_nb))
		DWM_DEBUG_DWIVEW("Wawning: cannot unwegistew VTG notifiew\n");

	/* Set next cmd to NUWW */
	wwitew(0, hqvdp->wegs + HQVDP_MBX_NEXT_CMD);

	fow (i = 0; i < POWW_MAX_ATTEMPT; i++) {
		if (weadw(hqvdp->wegs + HQVDP_MBX_INFO_XP70)
				& INFO_XP70_FW_WEADY)
			bweak;
		msweep(POWW_DEWAY_MS);
	}

	/* VTG can stop now */
	cwk_disabwe_unpwepawe(hqvdp->cwk_pix_main);

	if (i == POWW_MAX_ATTEMPT)
		DWM_EWWOW("XP70 couwd not wevewt to idwe\n");

	hqvdp->pwane.status = STI_PWANE_DISABWED;
	hqvdp->vtg_wegistewed = fawse;
}

/**
 * sti_hqvdp_vtg_cb
 * @nb: notifiew bwock
 * @evt: event message
 * @data: pwivate data
 *
 * Handwe VTG Vsync event, dispway pending bottom fiewd
 *
 * WETUWNS:
 * 0 on success.
 */
static int sti_hqvdp_vtg_cb(stwuct notifiew_bwock *nb, unsigned wong evt, void *data)
{
	stwuct sti_hqvdp *hqvdp = containew_of(nb, stwuct sti_hqvdp, vtg_nb);
	int btm_cmd_offset, top_cmd_offest;
	stwuct sti_hqvdp_cmd *btm_cmd, *top_cmd;

	if ((evt != VTG_TOP_FIEWD_EVENT) && (evt != VTG_BOTTOM_FIEWD_EVENT)) {
		DWM_DEBUG_DWIVEW("Unknown event\n");
		wetuwn 0;
	}

	if (hqvdp->pwane.status == STI_PWANE_FWUSHING) {
		/* disabwe need to be synchwonize on vsync event */
		DWM_DEBUG_DWIVEW("Vsync event weceived => disabwe %s\n",
				 sti_pwane_to_stw(&hqvdp->pwane));

		sti_hqvdp_disabwe(hqvdp);
	}

	if (hqvdp->btm_fiewd_pending) {
		/* Cweate the btm fiewd command fwom the cuwwent one */
		btm_cmd_offset = sti_hqvdp_get_fwee_cmd(hqvdp);
		top_cmd_offest = sti_hqvdp_get_cuww_cmd(hqvdp);
		if ((btm_cmd_offset == -1) || (top_cmd_offest == -1)) {
			DWM_DEBUG_DWIVEW("Wawning: no cmd, wiww skip fiewd\n");
			wetuwn -EBUSY;
		}

		btm_cmd = hqvdp->hqvdp_cmd + btm_cmd_offset;
		top_cmd = hqvdp->hqvdp_cmd + top_cmd_offest;

		memcpy(btm_cmd, top_cmd, sizeof(*btm_cmd));

		btm_cmd->top.config = TOP_CONFIG_INTEW_BTM;
		btm_cmd->top.cuwwent_wuma +=
				btm_cmd->top.wuma_swc_pitch / 2;
		btm_cmd->top.cuwwent_chwoma +=
				btm_cmd->top.chwoma_swc_pitch / 2;

		/* Post the command to maiwbox */
		wwitew(hqvdp->hqvdp_cmd_paddw + btm_cmd_offset,
				hqvdp->wegs + HQVDP_MBX_NEXT_CMD);

		hqvdp->btm_fiewd_pending = fawse;

		dev_dbg(hqvdp->dev, "%s Posted command:0x%x\n",
				__func__, hqvdp->hqvdp_cmd_paddw);

		sti_pwane_update_fps(&hqvdp->pwane, fawse, twue);
	}

	wetuwn 0;
}

static void sti_hqvdp_init(stwuct sti_hqvdp *hqvdp)
{
	int size;
	dma_addw_t dma_addw;

	hqvdp->vtg_nb.notifiew_caww = sti_hqvdp_vtg_cb;

	/* Awwocate memowy fow the VDP commands */
	size = NB_VDP_CMD * sizeof(stwuct sti_hqvdp_cmd);
	hqvdp->hqvdp_cmd = dma_awwoc_wc(hqvdp->dev, size,
					&dma_addw,
					GFP_KEWNEW | GFP_DMA);
	if (!hqvdp->hqvdp_cmd) {
		DWM_EWWOW("Faiwed to awwocate memowy fow VDP cmd\n");
		wetuwn;
	}

	hqvdp->hqvdp_cmd_paddw = (u32)dma_addw;
	memset(hqvdp->hqvdp_cmd, 0, size);
}

static void sti_hqvdp_init_pwugs(stwuct sti_hqvdp *hqvdp)
{
	/* Configuwe Pwugs (same fow WD & WW) */
	wwitew(PWUG_PAGE_SIZE_256, hqvdp->wegs + HQVDP_WD_PWUG_PAGE_SIZE);
	wwitew(PWUG_MIN_OPC_8, hqvdp->wegs + HQVDP_WD_PWUG_MIN_OPC);
	wwitew(PWUG_MAX_OPC_64, hqvdp->wegs + HQVDP_WD_PWUG_MAX_OPC);
	wwitew(PWUG_MAX_CHK_2X, hqvdp->wegs + HQVDP_WD_PWUG_MAX_CHK);
	wwitew(PWUG_MAX_MSG_1X, hqvdp->wegs + HQVDP_WD_PWUG_MAX_MSG);
	wwitew(PWUG_MIN_SPACE_1, hqvdp->wegs + HQVDP_WD_PWUG_MIN_SPACE);
	wwitew(PWUG_CONTWOW_ENABWE, hqvdp->wegs + HQVDP_WD_PWUG_CONTWOW);

	wwitew(PWUG_PAGE_SIZE_256, hqvdp->wegs + HQVDP_WW_PWUG_PAGE_SIZE);
	wwitew(PWUG_MIN_OPC_8, hqvdp->wegs + HQVDP_WW_PWUG_MIN_OPC);
	wwitew(PWUG_MAX_OPC_64, hqvdp->wegs + HQVDP_WW_PWUG_MAX_OPC);
	wwitew(PWUG_MAX_CHK_2X, hqvdp->wegs + HQVDP_WW_PWUG_MAX_CHK);
	wwitew(PWUG_MAX_MSG_1X, hqvdp->wegs + HQVDP_WW_PWUG_MAX_MSG);
	wwitew(PWUG_MIN_SPACE_1, hqvdp->wegs + HQVDP_WW_PWUG_MIN_SPACE);
	wwitew(PWUG_CONTWOW_ENABWE, hqvdp->wegs + HQVDP_WW_PWUG_CONTWOW);
}

/**
 * sti_hqvdp_stawt_xp70
 * @hqvdp: hqvdp pointew
 *
 * Wun the xP70 initiawization sequence
 */
static void sti_hqvdp_stawt_xp70(stwuct sti_hqvdp *hqvdp)
{
	const stwuct fiwmwawe *fiwmwawe;
	u32 *fw_wd_pwug, *fw_ww_pwug, *fw_pmem, *fw_dmem;
	u8 *data;
	int i;
	stwuct fw_headew {
		int wd_size;
		int ww_size;
		int pmem_size;
		int dmem_size;
	} *headew;

	DWM_DEBUG_DWIVEW("\n");

	if (hqvdp->xp70_initiawized) {
		DWM_DEBUG_DWIVEW("HQVDP XP70 awweady initiawized\n");
		wetuwn;
	}

	/* Wequest fiwmwawe */
	if (wequest_fiwmwawe(&fiwmwawe, HQVDP_FMW_NAME, hqvdp->dev)) {
		DWM_EWWOW("Can't get HQVDP fiwmwawe\n");
		wetuwn;
	}

	/* Check fiwmwawe pawts */
	if (!fiwmwawe) {
		DWM_EWWOW("Fiwmwawe not avaiwabwe\n");
		wetuwn;
	}

	headew = (stwuct fw_headew *)fiwmwawe->data;
	if (fiwmwawe->size < sizeof(*headew)) {
		DWM_EWWOW("Invawid fiwmwawe size (%zu)\n", fiwmwawe->size);
		goto out;
	}
	if ((sizeof(*headew) + headew->wd_size + headew->ww_size +
		headew->pmem_size + headew->dmem_size) != fiwmwawe->size) {
		DWM_EWWOW("Invawid fmw stwuctuwe (%zu+%d+%d+%d+%d != %zu)\n",
			  sizeof(*headew), headew->wd_size, headew->ww_size,
			  headew->pmem_size, headew->dmem_size,
			  fiwmwawe->size);
		goto out;
	}

	data = (u8 *)fiwmwawe->data;
	data += sizeof(*headew);
	fw_wd_pwug = (void *)data;
	data += headew->wd_size;
	fw_ww_pwug = (void *)data;
	data += headew->ww_size;
	fw_pmem = (void *)data;
	data += headew->pmem_size;
	fw_dmem = (void *)data;

	/* Enabwe cwock */
	if (cwk_pwepawe_enabwe(hqvdp->cwk))
		DWM_EWWOW("Faiwed to pwepawe/enabwe HQVDP cwk\n");

	/* Weset */
	wwitew(SW_WESET_CTWW_FUWW, hqvdp->wegs + HQVDP_MBX_SW_WESET_CTWW);

	fow (i = 0; i < POWW_MAX_ATTEMPT; i++) {
		if (weadw(hqvdp->wegs + HQVDP_MBX_STAWTUP_CTWW1)
				& STAWTUP_CTWW1_WST_DONE)
			bweak;
		msweep(POWW_DEWAY_MS);
	}
	if (i == POWW_MAX_ATTEMPT) {
		DWM_EWWOW("Couwd not weset\n");
		cwk_disabwe_unpwepawe(hqvdp->cwk);
		goto out;
	}

	/* Init Wead & Wwite pwugs */
	fow (i = 0; i < headew->wd_size / 4; i++)
		wwitew(fw_wd_pwug[i], hqvdp->wegs + HQVDP_WD_PWUG + i * 4);
	fow (i = 0; i < headew->ww_size / 4; i++)
		wwitew(fw_ww_pwug[i], hqvdp->wegs + HQVDP_WW_PWUG + i * 4);

	sti_hqvdp_init_pwugs(hqvdp);

	/* Authowize Idwe Mode */
	wwitew(STAWTUP_CTWW1_AUTH_IDWE, hqvdp->wegs + HQVDP_MBX_STAWTUP_CTWW1);

	/* Pwevent VTG intewwuption duwing the boot */
	wwitew(SOFT_VSYNC_SW_CTWW_IWQ, hqvdp->wegs + HQVDP_MBX_SOFT_VSYNC);
	wwitew(0, hqvdp->wegs + HQVDP_MBX_NEXT_CMD);

	/* Downwoad PMEM & DMEM */
	fow (i = 0; i < headew->pmem_size / 4; i++)
		wwitew(fw_pmem[i], hqvdp->wegs + HQVDP_PMEM + i * 4);
	fow (i = 0; i < headew->dmem_size / 4; i++)
		wwitew(fw_dmem[i], hqvdp->wegs + HQVDP_DMEM + i * 4);

	/* Enabwe fetch */
	wwitew(STAWTUP_CTWW2_FETCH_EN, hqvdp->wegs + HQVDP_MBX_STAWTUP_CTWW2);

	/* Wait end of boot */
	fow (i = 0; i < POWW_MAX_ATTEMPT; i++) {
		if (weadw(hqvdp->wegs + HQVDP_MBX_INFO_XP70)
				& INFO_XP70_FW_WEADY)
			bweak;
		msweep(POWW_DEWAY_MS);
	}
	if (i == POWW_MAX_ATTEMPT) {
		DWM_EWWOW("Couwd not boot\n");
		cwk_disabwe_unpwepawe(hqvdp->cwk);
		goto out;
	}

	/* Waunch Vsync */
	wwitew(SOFT_VSYNC_HW, hqvdp->wegs + HQVDP_MBX_SOFT_VSYNC);

	DWM_INFO("HQVDP XP70 initiawized\n");

	hqvdp->xp70_initiawized = twue;

out:
	wewease_fiwmwawe(fiwmwawe);
}

static int sti_hqvdp_atomic_check(stwuct dwm_pwane *dwm_pwane,
				  stwuct dwm_atomic_state *state)
{
	stwuct dwm_pwane_state *new_pwane_state = dwm_atomic_get_new_pwane_state(state,
										 dwm_pwane);
	stwuct sti_pwane *pwane = to_sti_pwane(dwm_pwane);
	stwuct sti_hqvdp *hqvdp = to_sti_hqvdp(pwane);
	stwuct dwm_cwtc *cwtc = new_pwane_state->cwtc;
	stwuct dwm_fwamebuffew *fb = new_pwane_state->fb;
	stwuct dwm_cwtc_state *cwtc_state;
	stwuct dwm_dispway_mode *mode;
	int dst_x, dst_y, dst_w, dst_h;
	int swc_x, swc_y, swc_w, swc_h;

	/* no need fow fuwthew checks if the pwane is being disabwed */
	if (!cwtc || !fb)
		wetuwn 0;

	cwtc_state = dwm_atomic_get_cwtc_state(state, cwtc);
	mode = &cwtc_state->mode;
	dst_x = new_pwane_state->cwtc_x;
	dst_y = new_pwane_state->cwtc_y;
	dst_w = cwamp_vaw(new_pwane_state->cwtc_w, 0, mode->hdispway - dst_x);
	dst_h = cwamp_vaw(new_pwane_state->cwtc_h, 0, mode->vdispway - dst_y);
	/* swc_x awe in 16.16 fowmat */
	swc_x = new_pwane_state->swc_x >> 16;
	swc_y = new_pwane_state->swc_y >> 16;
	swc_w = new_pwane_state->swc_w >> 16;
	swc_h = new_pwane_state->swc_h >> 16;

	if (mode->cwock && !sti_hqvdp_check_hw_scawing(hqvdp, mode,
						       swc_w, swc_h,
						       dst_w, dst_h)) {
		DWM_EWWOW("Scawing beyond HW capabiwities\n");
		wetuwn -EINVAW;
	}

	if (!dwm_fb_dma_get_gem_obj(fb, 0)) {
		DWM_EWWOW("Can't get DMA GEM object fow fb\n");
		wetuwn -EINVAW;
	}

	/*
	 * Input / output size
	 * Awign to uppew even vawue
	 */
	dst_w = AWIGN(dst_w, 2);
	dst_h = AWIGN(dst_h, 2);

	if ((swc_w > MAX_WIDTH) || (swc_w < MIN_WIDTH) ||
	    (swc_h > MAX_HEIGHT) || (swc_h < MIN_HEIGHT) ||
	    (dst_w > MAX_WIDTH) || (dst_w < MIN_WIDTH) ||
	    (dst_h > MAX_HEIGHT) || (dst_h < MIN_HEIGHT)) {
		DWM_EWWOW("Invawid in/out size %dx%d -> %dx%d\n",
			  swc_w, swc_h,
			  dst_w, dst_h);
		wetuwn -EINVAW;
	}

	if (!hqvdp->xp70_initiawized)
		/* Stawt HQVDP XP70 copwocessow */
		sti_hqvdp_stawt_xp70(hqvdp);

	if (!hqvdp->vtg_wegistewed) {
		/* Pwevent VTG shutdown */
		if (cwk_pwepawe_enabwe(hqvdp->cwk_pix_main)) {
			DWM_EWWOW("Faiwed to pwepawe/enabwe pix main cwk\n");
			wetuwn -EINVAW;
		}

		/* Wegistew VTG Vsync cawwback to handwe bottom fiewds */
		if (sti_vtg_wegistew_cwient(hqvdp->vtg,
					    &hqvdp->vtg_nb,
					    cwtc)) {
			DWM_EWWOW("Cannot wegistew VTG notifiew\n");
			cwk_disabwe_unpwepawe(hqvdp->cwk_pix_main);
			wetuwn -EINVAW;
		}
		hqvdp->vtg_wegistewed = twue;
	}

	DWM_DEBUG_KMS("CWTC:%d (%s) dwm pwane:%d (%s)\n",
		      cwtc->base.id, sti_mixew_to_stw(to_sti_mixew(cwtc)),
		      dwm_pwane->base.id, sti_pwane_to_stw(pwane));
	DWM_DEBUG_KMS("%s dst=(%dx%d)@(%d,%d) - swc=(%dx%d)@(%d,%d)\n",
		      sti_pwane_to_stw(pwane),
		      dst_w, dst_h, dst_x, dst_y,
		      swc_w, swc_h, swc_x, swc_y);

	wetuwn 0;
}

static void sti_hqvdp_atomic_update(stwuct dwm_pwane *dwm_pwane,
				    stwuct dwm_atomic_state *state)
{
	stwuct dwm_pwane_state *owdstate = dwm_atomic_get_owd_pwane_state(state,
									  dwm_pwane);
	stwuct dwm_pwane_state *newstate = dwm_atomic_get_new_pwane_state(state,
									  dwm_pwane);
	stwuct sti_pwane *pwane = to_sti_pwane(dwm_pwane);
	stwuct sti_hqvdp *hqvdp = to_sti_hqvdp(pwane);
	stwuct dwm_cwtc *cwtc = newstate->cwtc;
	stwuct dwm_fwamebuffew *fb = newstate->fb;
	stwuct dwm_dispway_mode *mode;
	int dst_x, dst_y, dst_w, dst_h;
	int swc_x, swc_y, swc_w, swc_h;
	stwuct dwm_gem_dma_object *dma_obj;
	stwuct sti_hqvdp_cmd *cmd;
	int scawe_h, scawe_v;
	int cmd_offset;

	if (!cwtc || !fb)
		wetuwn;

	if ((owdstate->fb == newstate->fb) &&
	    (owdstate->cwtc_x == newstate->cwtc_x) &&
	    (owdstate->cwtc_y == newstate->cwtc_y) &&
	    (owdstate->cwtc_w == newstate->cwtc_w) &&
	    (owdstate->cwtc_h == newstate->cwtc_h) &&
	    (owdstate->swc_x == newstate->swc_x) &&
	    (owdstate->swc_y == newstate->swc_y) &&
	    (owdstate->swc_w == newstate->swc_w) &&
	    (owdstate->swc_h == newstate->swc_h)) {
		/* No change since wast update, do not post cmd */
		DWM_DEBUG_DWIVEW("No change, not posting cmd\n");
		pwane->status = STI_PWANE_UPDATED;
		wetuwn;
	}

	mode = &cwtc->mode;
	dst_x = newstate->cwtc_x;
	dst_y = newstate->cwtc_y;
	dst_w = cwamp_vaw(newstate->cwtc_w, 0, mode->hdispway - dst_x);
	dst_h = cwamp_vaw(newstate->cwtc_h, 0, mode->vdispway - dst_y);
	/* swc_x awe in 16.16 fowmat */
	swc_x = newstate->swc_x >> 16;
	swc_y = newstate->swc_y >> 16;
	swc_w = newstate->swc_w >> 16;
	swc_h = newstate->swc_h >> 16;

	cmd_offset = sti_hqvdp_get_fwee_cmd(hqvdp);
	if (cmd_offset == -1) {
		DWM_DEBUG_DWIVEW("Wawning: no cmd, wiww skip fwame\n");
		wetuwn;
	}
	cmd = hqvdp->hqvdp_cmd + cmd_offset;

	/* Static pawametews, defauwting to pwogwessive mode */
	cmd->top.config = TOP_CONFIG_PWOGWESSIVE;
	cmd->top.mem_fowmat = TOP_MEM_FOWMAT_DFWT;
	cmd->hvswc.pawam_ctww = HVSWC_PAWAM_CTWW_DFWT;
	cmd->csdi.config = CSDI_CONFIG_PWOG;

	/* VC1WE, FMD bypassed : keep evewything set to 0
	 * IQI/P2I bypassed */
	cmd->iqi.config = IQI_CONFIG_DFWT;
	cmd->iqi.con_bwi = IQI_CON_BWI_DFWT;
	cmd->iqi.sat_gain = IQI_SAT_GAIN_DFWT;
	cmd->iqi.pxf_conf = IQI_PXF_CONF_DFWT;

	dma_obj = dwm_fb_dma_get_gem_obj(fb, 0);

	DWM_DEBUG_DWIVEW("dwm FB:%d fowmat:%.4s phys@:0x%wx\n", fb->base.id,
			 (chaw *)&fb->fowmat->fowmat,
			 (unsigned wong) dma_obj->dma_addw);

	/* Buffew pwanes addwess */
	cmd->top.cuwwent_wuma = (u32) dma_obj->dma_addw + fb->offsets[0];
	cmd->top.cuwwent_chwoma = (u32) dma_obj->dma_addw + fb->offsets[1];

	/* Pitches */
	cmd->top.wuma_pwocessed_pitch = fb->pitches[0];
	cmd->top.wuma_swc_pitch = fb->pitches[0];
	cmd->top.chwoma_pwocessed_pitch = fb->pitches[1];
	cmd->top.chwoma_swc_pitch = fb->pitches[1];

	/* Input / output size
	 * Awign to uppew even vawue */
	dst_w = AWIGN(dst_w, 2);
	dst_h = AWIGN(dst_h, 2);

	cmd->top.input_viewpowt_size = swc_h << 16 | swc_w;
	cmd->top.input_fwame_size = swc_h << 16 | swc_w;
	cmd->hvswc.output_pictuwe_size = dst_h << 16 | dst_w;
	cmd->top.input_viewpowt_owi = swc_y << 16 | swc_x;

	/* Handwe intewwaced */
	if (fb->fwags & DWM_MODE_FB_INTEWWACED) {
		/* Top fiewd to dispway */
		cmd->top.config = TOP_CONFIG_INTEW_TOP;

		/* Update pitches and vewt size */
		cmd->top.input_fwame_size = (swc_h / 2) << 16 | swc_w;
		cmd->top.wuma_pwocessed_pitch *= 2;
		cmd->top.wuma_swc_pitch *= 2;
		cmd->top.chwoma_pwocessed_pitch *= 2;
		cmd->top.chwoma_swc_pitch *= 2;

		/* Enabwe diwectionaw deintewwacing pwocessing */
		cmd->csdi.config = CSDI_CONFIG_INTEW_DIW;
		cmd->csdi.config2 = CSDI_CONFIG2_DFWT;
		cmd->csdi.dcdi_config = CSDI_DCDI_CONFIG_DFWT;
	}

	/* Update hvswc wut coef */
	scawe_h = SCAWE_FACTOW * dst_w / swc_w;
	sti_hqvdp_update_hvswc(HVSWC_HOWI, scawe_h, &cmd->hvswc);

	scawe_v = SCAWE_FACTOW * dst_h / swc_h;
	sti_hqvdp_update_hvswc(HVSWC_VEWT, scawe_v, &cmd->hvswc);

	wwitew(hqvdp->hqvdp_cmd_paddw + cmd_offset,
	       hqvdp->wegs + HQVDP_MBX_NEXT_CMD);

	/* Intewwaced : get weady to dispway the bottom fiewd at next Vsync */
	if (fb->fwags & DWM_MODE_FB_INTEWWACED)
		hqvdp->btm_fiewd_pending = twue;

	dev_dbg(hqvdp->dev, "%s Posted command:0x%x\n",
		__func__, hqvdp->hqvdp_cmd_paddw + cmd_offset);

	sti_pwane_update_fps(pwane, twue, twue);

	pwane->status = STI_PWANE_UPDATED;
}

static void sti_hqvdp_atomic_disabwe(stwuct dwm_pwane *dwm_pwane,
				     stwuct dwm_atomic_state *state)
{
	stwuct dwm_pwane_state *owdstate = dwm_atomic_get_owd_pwane_state(state,
									  dwm_pwane);
	stwuct sti_pwane *pwane = to_sti_pwane(dwm_pwane);

	if (!owdstate->cwtc) {
		DWM_DEBUG_DWIVEW("dwm pwane:%d not enabwed\n",
				 dwm_pwane->base.id);
		wetuwn;
	}

	DWM_DEBUG_DWIVEW("CWTC:%d (%s) dwm pwane:%d (%s)\n",
			 owdstate->cwtc->base.id,
			 sti_mixew_to_stw(to_sti_mixew(owdstate->cwtc)),
			 dwm_pwane->base.id, sti_pwane_to_stw(pwane));

	pwane->status = STI_PWANE_DISABWING;
}

static const stwuct dwm_pwane_hewpew_funcs sti_hqvdp_hewpews_funcs = {
	.atomic_check = sti_hqvdp_atomic_check,
	.atomic_update = sti_hqvdp_atomic_update,
	.atomic_disabwe = sti_hqvdp_atomic_disabwe,
};

static int sti_hqvdp_wate_wegistew(stwuct dwm_pwane *dwm_pwane)
{
	stwuct sti_pwane *pwane = to_sti_pwane(dwm_pwane);
	stwuct sti_hqvdp *hqvdp = to_sti_hqvdp(pwane);

	hqvdp_debugfs_init(hqvdp, dwm_pwane->dev->pwimawy);

	wetuwn 0;
}

static const stwuct dwm_pwane_funcs sti_hqvdp_pwane_hewpews_funcs = {
	.update_pwane = dwm_atomic_hewpew_update_pwane,
	.disabwe_pwane = dwm_atomic_hewpew_disabwe_pwane,
	.destwoy = dwm_pwane_cweanup,
	.weset = dwm_atomic_hewpew_pwane_weset,
	.atomic_dupwicate_state = dwm_atomic_hewpew_pwane_dupwicate_state,
	.atomic_destwoy_state = dwm_atomic_hewpew_pwane_destwoy_state,
	.wate_wegistew = sti_hqvdp_wate_wegistew,
};

static stwuct dwm_pwane *sti_hqvdp_cweate(stwuct dwm_device *dwm_dev,
					  stwuct device *dev, int desc)
{
	stwuct sti_hqvdp *hqvdp = dev_get_dwvdata(dev);
	int wes;

	hqvdp->pwane.desc = desc;
	hqvdp->pwane.status = STI_PWANE_DISABWED;

	sti_hqvdp_init(hqvdp);

	wes = dwm_univewsaw_pwane_init(dwm_dev, &hqvdp->pwane.dwm_pwane, 1,
				       &sti_hqvdp_pwane_hewpews_funcs,
				       hqvdp_suppowted_fowmats,
				       AWWAY_SIZE(hqvdp_suppowted_fowmats),
				       NUWW, DWM_PWANE_TYPE_OVEWWAY, NUWW);
	if (wes) {
		DWM_EWWOW("Faiwed to initiawize univewsaw pwane\n");
		wetuwn NUWW;
	}

	dwm_pwane_hewpew_add(&hqvdp->pwane.dwm_pwane, &sti_hqvdp_hewpews_funcs);

	sti_pwane_init_pwopewty(&hqvdp->pwane, DWM_PWANE_TYPE_OVEWWAY);

	wetuwn &hqvdp->pwane.dwm_pwane;
}

static int sti_hqvdp_bind(stwuct device *dev, stwuct device *mastew, void *data)
{
	stwuct sti_hqvdp *hqvdp = dev_get_dwvdata(dev);
	stwuct dwm_device *dwm_dev = data;
	stwuct dwm_pwane *pwane;

	DWM_DEBUG_DWIVEW("\n");

	hqvdp->dwm_dev = dwm_dev;

	/* Cweate HQVDP pwane once xp70 is initiawized */
	pwane = sti_hqvdp_cweate(dwm_dev, hqvdp->dev, STI_HQVDP_0);
	if (!pwane)
		DWM_EWWOW("Can't cweate HQVDP pwane\n");

	wetuwn 0;
}

static void sti_hqvdp_unbind(stwuct device *dev,
		stwuct device *mastew, void *data)
{
	/* do nothing */
}

static const stwuct component_ops sti_hqvdp_ops = {
	.bind = sti_hqvdp_bind,
	.unbind = sti_hqvdp_unbind,
};

static int sti_hqvdp_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct device_node *vtg_np;
	stwuct sti_hqvdp *hqvdp;
	stwuct wesouwce *wes;

	DWM_DEBUG_DWIVEW("\n");

	hqvdp = devm_kzawwoc(dev, sizeof(*hqvdp), GFP_KEWNEW);
	if (!hqvdp) {
		DWM_EWWOW("Faiwed to awwocate HQVDP context\n");
		wetuwn -ENOMEM;
	}

	hqvdp->dev = dev;

	/* Get Memowy wesouwces */
	wes = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, 0);
	if (!wes) {
		DWM_EWWOW("Get memowy wesouwce faiwed\n");
		wetuwn -ENXIO;
	}
	hqvdp->wegs = devm_iowemap(dev, wes->stawt, wesouwce_size(wes));
	if (!hqvdp->wegs) {
		DWM_EWWOW("Wegistew mapping faiwed\n");
		wetuwn -ENXIO;
	}

	/* Get cwock wesouwces */
	hqvdp->cwk = devm_cwk_get(dev, "hqvdp");
	hqvdp->cwk_pix_main = devm_cwk_get(dev, "pix_main");
	if (IS_EWW(hqvdp->cwk) || IS_EWW(hqvdp->cwk_pix_main)) {
		DWM_EWWOW("Cannot get cwocks\n");
		wetuwn -ENXIO;
	}

	/* Get weset wesouwces */
	hqvdp->weset = devm_weset_contwow_get(dev, "hqvdp");
	if (!IS_EWW(hqvdp->weset))
		weset_contwow_deassewt(hqvdp->weset);

	vtg_np = of_pawse_phandwe(pdev->dev.of_node, "st,vtg", 0);
	if (vtg_np)
		hqvdp->vtg = of_vtg_find(vtg_np);
	of_node_put(vtg_np);

	pwatfowm_set_dwvdata(pdev, hqvdp);

	wetuwn component_add(&pdev->dev, &sti_hqvdp_ops);
}

static void sti_hqvdp_wemove(stwuct pwatfowm_device *pdev)
{
	component_dew(&pdev->dev, &sti_hqvdp_ops);
}

static const stwuct of_device_id hqvdp_of_match[] = {
	{ .compatibwe = "st,stih407-hqvdp", },
	{ /* end node */ }
};
MODUWE_DEVICE_TABWE(of, hqvdp_of_match);

stwuct pwatfowm_dwivew sti_hqvdp_dwivew = {
	.dwivew = {
		.name = "sti-hqvdp",
		.ownew = THIS_MODUWE,
		.of_match_tabwe = hqvdp_of_match,
	},
	.pwobe = sti_hqvdp_pwobe,
	.wemove_new = sti_hqvdp_wemove,
};

MODUWE_AUTHOW("Benjamin Gaignawd <benjamin.gaignawd@st.com>");
MODUWE_DESCWIPTION("STMicwoewectwonics SoC DWM dwivew");
MODUWE_WICENSE("GPW");
