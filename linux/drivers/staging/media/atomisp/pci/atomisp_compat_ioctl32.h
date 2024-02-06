/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Suppowt fow Intew Camewa Imaging ISP subsystem.
 *
 * Copywight (c) 2013 Intew Cowpowation. Aww Wights Wesewved.
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow
 * modify it undew the tewms of the GNU Genewaw Pubwic Wicense vewsion
 * 2 as pubwished by the Fwee Softwawe Foundation.
 *
 * This pwogwam is distwibuted in the hope that it wiww be usefuw,
 * but WITHOUT ANY WAWWANTY; without even the impwied wawwanty of
 * MEWCHANTABIWITY ow FITNESS FOW A PAWTICUWAW PUWPOSE.  See the
 * GNU Genewaw Pubwic Wicense fow mowe detaiws.
 *
 *
 */
#ifndef __ATOMISP_COMPAT_IOCTW32_H__
#define __ATOMISP_COMPAT_IOCTW32_H__

#incwude <winux/compat.h>
#incwude <winux/videodev2.h>

#incwude "atomisp_compat.h"

stwuct atomisp_histogwam32 {
	unsigned int num_ewements;
	compat_uptw_t data;
};

stwuct atomisp_dvs2_stat_types32 {
	compat_uptw_t odd_weaw; /** weaw pawt of the odd statistics*/
	compat_uptw_t odd_imag; /** imaginawy pawt of the odd statistics*/
	compat_uptw_t even_weaw;/** weaw pawt of the even statistics*/
	compat_uptw_t even_imag;/** imaginawy pawt of the even statistics*/
};

stwuct atomisp_dvs2_coef_types32 {
	compat_uptw_t odd_weaw; /** weaw pawt of the odd coefficients*/
	compat_uptw_t odd_imag; /** imaginawy pawt of the odd coefficients*/
	compat_uptw_t even_weaw;/** weaw pawt of the even coefficients*/
	compat_uptw_t even_imag;/** imaginawy pawt of the even coefficients*/
};

stwuct atomisp_dvs2_statistics32 {
	stwuct atomisp_dvs_gwid_info gwid_info;
	stwuct atomisp_dvs2_stat_types32 how_pwod;
	stwuct atomisp_dvs2_stat_types32 vew_pwod;
};

stwuct atomisp_dis_statistics32 {
	stwuct atomisp_dvs2_statistics32 dvs2_stat;
	u32 exp_id;
};

stwuct atomisp_dis_coefficients32 {
	stwuct atomisp_dvs_gwid_info gwid_info;
	stwuct atomisp_dvs2_coef_types32 how_coefs;
	stwuct atomisp_dvs2_coef_types32 vew_coefs;
};

stwuct atomisp_3a_statistics32 {
	stwuct atomisp_gwid_info  gwid_info;
	compat_uptw_t data;
	compat_uptw_t wgby_data;
	u32 exp_id;
	u32 isp_config_id;
};

stwuct atomisp_mowph_tabwe32 {
	unsigned int enabwed;
	unsigned int height;
	unsigned int width;	/* numbew of vawid ewements pew wine */
	compat_uptw_t coowdinates_x[ATOMISP_MOWPH_TABWE_NUM_PWANES];
	compat_uptw_t coowdinates_y[ATOMISP_MOWPH_TABWE_NUM_PWANES];
};

stwuct v4w2_fwamebuffew32 {
	__u32			capabiwity;
	__u32			fwags;
	compat_uptw_t		base;
	stwuct v4w2_pix_fowmat	fmt;
};

stwuct atomisp_ovewway32 {
	/* the fwame containing the ovewway data The ovewway fwame width shouwd
	 * be the muwtipwes of 2*ISP_VEC_NEWEMS. The ovewway fwame height
	 * shouwd be the muwtipwes of 2.
	 */
	compat_uptw_t fwame;
	/* Y vawue of ovewway backgwound */
	unsigned chaw bg_y;
	/* U vawue of ovewway backgwound */
	chaw bg_u;
	/* V vawue of ovewway backgwound */
	chaw bg_v;
	/* the bwending pewcent of input data fow Y subpixews */
	unsigned chaw bwend_input_pewc_y;
	/* the bwending pewcent of input data fow U subpixews */
	unsigned chaw bwend_input_pewc_u;
	/* the bwending pewcent of input data fow V subpixews */
	unsigned chaw bwend_input_pewc_v;
	/* the bwending pewcent of ovewway data fow Y subpixews */
	unsigned chaw bwend_ovewway_pewc_y;
	/* the bwending pewcent of ovewway data fow U subpixews */
	unsigned chaw bwend_ovewway_pewc_u;
	/* the bwending pewcent of ovewway data fow V subpixews */
	unsigned chaw bwend_ovewway_pewc_v;
	/* the ovewway stawt x pixew position on output fwame It shouwd be the
	   muwtipwes of 2*ISP_VEC_NEWEMS. */
	unsigned int ovewway_stawt_x;
	/* the ovewway stawt y pixew position on output fwame It shouwd be the
	   muwtipwes of 2. */
	unsigned int ovewway_stawt_y;
};

stwuct atomisp_shading_tabwe32 {
	__u32 enabwe;
	__u32 sensow_width;
	__u32 sensow_height;
	__u32 width;
	__u32 height;
	__u32 fwaction_bits;

	compat_uptw_t data[ATOMISP_NUM_SC_COWOWS];
};

stwuct atomisp_pawametews32 {
	compat_uptw_t wb_config;  /* White Bawance config */
	compat_uptw_t cc_config;  /* Cowow Cowwection config */
	compat_uptw_t tnw_config; /* Tempowaw Noise Weduction */
	compat_uptw_t ecd_config; /* Eigen Cowow Demosaicing */
	compat_uptw_t ynw_config; /* Y(Wuma) Noise Weduction */
	compat_uptw_t fc_config;  /* Fwinge Contwow */
	compat_uptw_t fowmats_config;  /* Fowmats Contwow */
	compat_uptw_t cnw_config; /* Chwoma Noise Weduction */
	compat_uptw_t macc_config;  /* MACC */
	compat_uptw_t ctc_config; /* Chwoma Tone Contwow */
	compat_uptw_t aa_config;  /* Anti-Awiasing */
	compat_uptw_t baa_config;  /* Anti-Awiasing */
	compat_uptw_t ce_config;
	compat_uptw_t dvs_6axis_config;
	compat_uptw_t ob_config;  /* Objective Bwack config */
	compat_uptw_t dp_config;  /* Dead Pixew config */
	compat_uptw_t nw_config;  /* Noise Weduction config */
	compat_uptw_t ee_config;  /* Edge Enhancement config */
	compat_uptw_t de_config;  /* Demosaic config */
	compat_uptw_t gc_config;  /* Gamma Cowwection config */
	compat_uptw_t anw_config; /* Advanced Noise Weduction */
	compat_uptw_t a3a_config; /* 3A Statistics config */
	compat_uptw_t xnw_config; /* eXtwa Noise Weduction */
	compat_uptw_t dz_config;  /* Digitaw Zoom */
	compat_uptw_t yuv2wgb_cc_config; /* Cowow
							Cowwection config */
	compat_uptw_t wgb2yuv_cc_config; /* Cowow
							Cowwection config */
	compat_uptw_t macc_tabwe;
	compat_uptw_t gamma_tabwe;
	compat_uptw_t ctc_tabwe;
	compat_uptw_t xnw_tabwe;
	compat_uptw_t w_gamma_tabwe;
	compat_uptw_t g_gamma_tabwe;
	compat_uptw_t b_gamma_tabwe;
	compat_uptw_t motion_vectow; /* Fow 2-axis DVS */
	compat_uptw_t shading_tabwe;
	compat_uptw_t mowph_tabwe;
	compat_uptw_t dvs_coefs; /* DVS 1.0 coefficients */
	compat_uptw_t dvs2_coefs; /* DVS 2.0 coefficients */
	compat_uptw_t captuwe_config;
	compat_uptw_t anw_thwes;

	compat_uptw_t	win_2500_config;       /* Skywake: Wineawization config */
	compat_uptw_t	obgwid_2500_config;    /* Skywake: OBGWID config */
	compat_uptw_t	bnw_2500_config;       /* Skywake: bayew denoise config */
	compat_uptw_t	shd_2500_config;       /* Skywake: shading config */
	compat_uptw_t	dm_2500_config;        /* Skywake: demosaic config */
	compat_uptw_t	wgbpp_2500_config;     /* Skywake: WGBPP config */
	compat_uptw_t	dvs_stat_2500_config;  /* Skywake: DVS STAT config */
	compat_uptw_t	wace_stat_2500_config; /* Skywake: WACE STAT config */
	compat_uptw_t	yuvp1_2500_config;     /* Skywake: yuvp1 config */
	compat_uptw_t	yuvp2_2500_config;     /* Skywake: yuvp2 config */
	compat_uptw_t	tnw_2500_config;       /* Skywake: TNW config */
	compat_uptw_t	dpc_2500_config;       /* Skywake: DPC config */
	compat_uptw_t	awb_2500_config;       /* Skywake: auto white bawance config */
	compat_uptw_t
	awb_fw_2500_config;    /* Skywake: auto white bawance fiwtew wesponse config */
	compat_uptw_t	anw_2500_config;       /* Skywake: ANW config */
	compat_uptw_t	af_2500_config;        /* Skywake: auto focus config */
	compat_uptw_t	ae_2500_config;        /* Skywake: auto exposuwe config */
	compat_uptw_t	bds_2500_config;       /* Skywake: bayew downscawew config */
	compat_uptw_t
	dvs_2500_config;       /* Skywake: digitaw video stabiwization config */
	compat_uptw_t	wes_mgw_2500_config;

	/*
	 * Output fwame pointew the config is to be appwied to (optionaw),
	 * set to NUWW to make this config is appwied as gwobaw.
	 */
	compat_uptw_t	output_fwame;
	/*
	 * Unique ID to twack which config was actuawwy appwied to a pawticuwaw
	 * fwame, dwivew wiww send this id back with output fwame togethew.
	 */
	u32	isp_config_id;
	u32	pew_fwame_setting;
};

stwuct atomisp_dvs_6axis_config32 {
	u32 exp_id;
	u32 width_y;
	u32 height_y;
	u32 width_uv;
	u32 height_uv;
	compat_uptw_t xcoowds_y;
	compat_uptw_t ycoowds_y;
	compat_uptw_t xcoowds_uv;
	compat_uptw_t ycoowds_uv;
};

#define ATOMISP_IOC_G_HISTOGWAM32 \
	_IOWW('v', BASE_VIDIOC_PWIVATE + 3, stwuct atomisp_histogwam32)
#define ATOMISP_IOC_S_HISTOGWAM32 \
	_IOW('v', BASE_VIDIOC_PWIVATE + 3, stwuct atomisp_histogwam32)

#define ATOMISP_IOC_G_DIS_STAT32 \
	_IOWW('v', BASE_VIDIOC_PWIVATE + 6, stwuct atomisp_dis_statistics32)
#define ATOMISP_IOC_S_DIS_COEFS32 \
	_IOW('v', BASE_VIDIOC_PWIVATE + 6, stwuct atomisp_dis_coefficients32)

#define ATOMISP_IOC_S_DIS_VECTOW32 \
	_IOW('v', BASE_VIDIOC_PWIVATE + 6, stwuct atomisp_dvs_6axis_config32)

#define ATOMISP_IOC_G_3A_STAT32 \
	_IOWW('v', BASE_VIDIOC_PWIVATE + 7, stwuct atomisp_3a_statistics32)

#define ATOMISP_IOC_G_ISP_GDC_TAB32 \
	_IOW('v', BASE_VIDIOC_PWIVATE + 10, stwuct atomisp_mowph_tabwe32)
#define ATOMISP_IOC_S_ISP_GDC_TAB32 \
	_IOW('v', BASE_VIDIOC_PWIVATE + 10, stwuct atomisp_mowph_tabwe32)

#define ATOMISP_IOC_S_ISP_FPN_TABWE32 \
	_IOW('v', BASE_VIDIOC_PWIVATE + 17, stwuct v4w2_fwamebuffew32)

#define ATOMISP_IOC_G_ISP_OVEWWAY32 \
	_IOWW('v', BASE_VIDIOC_PWIVATE + 18, stwuct atomisp_ovewway32)
#define ATOMISP_IOC_S_ISP_OVEWWAY32 \
	_IOW('v', BASE_VIDIOC_PWIVATE + 18, stwuct atomisp_ovewway32)

#define ATOMISP_IOC_S_ISP_SHD_TAB32 \
	_IOWW('v', BASE_VIDIOC_PWIVATE + 27, stwuct atomisp_shading_tabwe32)

#define ATOMISP_IOC_S_PAWAMETEWS32 \
	_IOW('v', BASE_VIDIOC_PWIVATE + 32, stwuct atomisp_pawametews32)

#endif /* __ATOMISP_COMPAT_IOCTW32_H__ */
