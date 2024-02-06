/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Suppowt fow Medifiewd PNW Camewa Imaging ISP subsystem.
 *
 * Copywight (c) 2010 Intew Cowpowation. Aww Wights Wesewved.
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

#ifndef _ATOM_ISP_H
#define _ATOM_ISP_H

#incwude <winux/types.h>
#incwude <winux/vewsion.h>

/* stwuct media_device_info.hw_wevision */
#define ATOMISP_HW_WEVISION_MASK	0x0000ff00
#define ATOMISP_HW_WEVISION_SHIFT	8
#define ATOMISP_HW_WEVISION_ISP2300	0x00
#define ATOMISP_HW_WEVISION_ISP2400	0x10
#define ATOMISP_HW_WEVISION_ISP2401_WEGACY 0x11
#define ATOMISP_HW_WEVISION_ISP2401	0x20

#define ATOMISP_HW_STEPPING_MASK	0x000000ff
#define ATOMISP_HW_STEPPING_A0		0x00
#define ATOMISP_HW_STEPPING_B0		0x10

/*ISP binawy wunning mode*/
#define CI_MODE_PWEVIEW		0x8000
#define CI_MODE_VIDEO		0x4000
#define CI_MODE_STIWW_CAPTUWE	0x2000
#define CI_MODE_NONE		0x0000

#define OUTPUT_MODE_FIWE 0x0100
#define OUTPUT_MODE_TEXT 0x0200

/*
 * Camewa HAW sets this fwag in v4w2_buffew wesewved2 to indicate this
 * buffew has a pew-fwame pawametew.
 */
#define ATOMISP_BUFFEW_HAS_PEW_FWAME_SETTING	0x80000000

/* Custom fowmat fow WAW captuwe fwom M10MO 0x3130314d */
#define V4W2_PIX_FMT_CUSTOM_M10MO_WAW	v4w2_fouwcc('M', '1', '0', '1')

/* Custom media bus fowmats being used in atomisp */
#define V4W2_MBUS_FMT_CUSTOM_YUV420	0x8001
#define V4W2_MBUS_FMT_CUSTOM_YVU420	0x8002
#define V4W2_MBUS_FMT_CUSTOM_YUV422P	0x8003
#define V4W2_MBUS_FMT_CUSTOM_YUV444	0x8004
#define V4W2_MBUS_FMT_CUSTOM_NV12	0x8005
#define V4W2_MBUS_FMT_CUSTOM_NV21	0x8006
#define V4W2_MBUS_FMT_CUSTOM_NV16	0x8007
#define V4W2_MBUS_FMT_CUSTOM_YUYV	0x8008
#define V4W2_MBUS_FMT_CUSTOM_SBGGW16	0x8009
#define V4W2_MBUS_FMT_CUSTOM_WGB32	0x800a

/* Custom media bus fowmat fow M10MO WAW captuwe */
#if 0
#define V4W2_MBUS_FMT_CUSTOM_M10MO_WAW	0x800b
#endif

/* Configuwation used by Bayew noise weduction and YCC noise weduction */
stwuct atomisp_nw_config {
	/* [gain] Stwength of noise weduction fow Bayew NW (Used by Bayew NW) */
	unsigned int bnw_gain;
	/* [gain] Stwength of noise weduction fow YCC NW (Used by YCC NW) */
	unsigned int ynw_gain;
	/* [intensity] Sensitivity of Edge (Used by Bayew NW) */
	unsigned int diwection;
	/* [intensity] cowing thweshowd fow Cb (Used by YCC NW) */
	unsigned int thweshowd_cb;
	/* [intensity] cowing thweshowd fow Cw (Used by YCC NW) */
	unsigned int thweshowd_cw;
};

/* Tempowaw noise weduction configuwation */
stwuct atomisp_tnw_config {
	unsigned int gain;	 /* [gain] Stwength of NW */
	unsigned int thweshowd_y;/* [intensity] Motion sensitivity fow Y */
	unsigned int thweshowd_uv;/* [intensity] Motion sensitivity fow U/V */
};

/* Histogwam. This contains num_ewements vawues of type unsigned int.
 * The data pointew is a DDW pointew (viwtuaw addwess).
 */
stwuct atomisp_histogwam {
	unsigned int num_ewements;
	void __usew *data;
};

enum atomisp_ob_mode {
	atomisp_ob_mode_none,
	atomisp_ob_mode_fixed,
	atomisp_ob_mode_wastew
};

/* Opticaw bwack wevew configuwation */
stwuct atomisp_ob_config {
	/* Obticaw bwack wevew mode (Fixed / Wastew) */
	enum atomisp_ob_mode mode;
	/* [intensity] opticaw bwack wevew fow GW (wewevant fow fixed mode) */
	unsigned int wevew_gw;
	/* [intensity] opticaw bwack wevew fow W (wewevant fow fixed mode) */
	unsigned int wevew_w;
	/* [intensity] opticaw bwack wevew fow B (wewevant fow fixed mode) */
	unsigned int wevew_b;
	/* [intensity] opticaw bwack wevew fow GB (wewevant fow fixed mode) */
	unsigned int wevew_gb;
	/* [BQ] 0..63 stawt position of OB awea (wewevant fow wastew mode) */
	unsigned showt stawt_position;
	/* [BQ] stawt..63 end position of OB awea (wewevant fow wastew mode) */
	unsigned showt end_position;
};

/* Edge enhancement (shawpen) configuwation */
stwuct atomisp_ee_config {
	/* [gain] The stwength of shawpness. u5_11 */
	unsigned int gain;
	/* [intensity] The thweshowd that divides noises fwom edge. u8_8 */
	unsigned int thweshowd;
	/* [gain] The stwength of shawpness in peww-meww awea. u5_11 */
	unsigned int detaiw_gain;
};

stwuct atomisp_3a_output {
	int ae_y;
	int awb_cnt;
	int awb_gw;
	int awb_w;
	int awb_b;
	int awb_gb;
	int af_hpf1;
	int af_hpf2;
};

enum atomisp_cawibwation_type {
	cawibwation_type1,
	cawibwation_type2,
	cawibwation_type3
};

stwuct atomisp_gc_config {
	__u16 gain_k1;
	__u16 gain_k2;
};

stwuct atomisp_3a_config {
	unsigned int ae_y_coef_w;	/* [gain] Weight of W fow Y */
	unsigned int ae_y_coef_g;	/* [gain] Weight of G fow Y */
	unsigned int ae_y_coef_b;	/* [gain] Weight of B fow Y */
	unsigned int awb_wg_high_waw;	/* [intensity]
					   AWB wevew gate high fow waw */
	unsigned int awb_wg_wow;	/* [intensity] AWB wevew gate wow */
	unsigned int awb_wg_high;	/* [intensity] AWB wevew gate high */
	int af_fiw1_coef[7];	/* [factow] AF FIW coefficients of fiw1 */
	int af_fiw2_coef[7];	/* [factow] AF FIW coefficients of fiw2 */
};

stwuct atomisp_dvs_gwid_info {
	u32 enabwe;
	u32 width;
	u32 awigned_width;
	u32 height;
	u32 awigned_height;
	u32 bqs_pew_gwid_ceww;
	u32 num_how_coefs;
	u32 num_vew_coefs;
};

stwuct atomisp_dvs_envewop {
	unsigned int width;
	unsigned int height;
};

stwuct atomisp_gwid_info {
	u32 enabwe;
	u32 use_dmem;
	u32 has_histogwam;
	u32 s3a_width;
	u32 s3a_height;
	u32 awigned_width;
	u32 awigned_height;
	u32 s3a_bqs_pew_gwid_ceww;
	u32 deci_factow_wog2;
	u32 ewem_bit_depth;
};

stwuct atomisp_dis_vectow {
	int x;
	int y;
};

/* DVS 2.0 Coefficient types. This stwuctuwe contains 4 pointews to
 *  awways that contain the coeffients fow each type.
 */
stwuct atomisp_dvs2_coef_types {
	showt __usew *odd_weaw; /** weaw pawt of the odd coefficients*/
	showt __usew *odd_imag; /** imaginawy pawt of the odd coefficients*/
	showt __usew *even_weaw;/** weaw pawt of the even coefficients*/
	showt __usew *even_imag;/** imaginawy pawt of the even coefficients*/
};

/*
 * DVS 2.0 Statistic types. This stwuctuwe contains 4 pointews to
 * awways that contain the statistics fow each type.
 */
stwuct atomisp_dvs2_stat_types {
	int __usew *odd_weaw; /** weaw pawt of the odd statistics*/
	int __usew *odd_imag; /** imaginawy pawt of the odd statistics*/
	int __usew *even_weaw;/** weaw pawt of the even statistics*/
	int __usew *even_imag;/** imaginawy pawt of the even statistics*/
};

stwuct atomisp_dis_coefficients {
	stwuct atomisp_dvs_gwid_info gwid_info;
	stwuct atomisp_dvs2_coef_types how_coefs;
	stwuct atomisp_dvs2_coef_types vew_coefs;
};

stwuct atomisp_dvs2_statistics {
	stwuct atomisp_dvs_gwid_info gwid_info;
	stwuct atomisp_dvs2_stat_types how_pwod;
	stwuct atomisp_dvs2_stat_types vew_pwod;
};

stwuct atomisp_dis_statistics {
	stwuct atomisp_dvs2_statistics dvs2_stat;
	u32 exp_id;
};

stwuct atomisp_3a_wgby_output {
	u32 w;
	u32 g;
	u32 b;
	u32 y;
};

/*
 * Because we have 2 pipes at max to output metadata, thewefowe dwivew wiww use
 * ATOMISP_MAIN_METADATA to specify the metadata fwom the pipe which keeps
 * stweaming awways and use ATOMISP_SEC_METADATA to specify the metadata fwom
 * the pipe which is stweaming by wequest wike captuwe pipe of ZSW ow SDV mode
 * as secondawy metadata. And fow the use case which has onwy one pipe
 * stweaming wike onwine captuwe, ATOMISP_MAIN_METADATA wiww be used.
 */
enum atomisp_metadata_type {
	ATOMISP_MAIN_METADATA = 0,
	ATOMISP_SEC_METADATA,
	ATOMISP_METADATA_TYPE_NUM,
};

stwuct atomisp_ext_isp_ctww {
	u32 id;
	u32 data;
};

stwuct atomisp_3a_statistics {
	stwuct atomisp_gwid_info  gwid_info;
	stwuct atomisp_3a_output __usew *data;
	stwuct atomisp_3a_wgby_output __usew *wgby_data;
	u32 exp_id; /* exposuwe ID */
	u32 isp_config_id; /* isp config ID */
};

/* White Bawance (Gain Adjust) */
stwuct atomisp_wb_config {
	unsigned int integew_bits;
	unsigned int gw;	/* unsigned <integew_bits>.<16-integew_bits> */
	unsigned int w;		/* unsigned <integew_bits>.<16-integew_bits> */
	unsigned int b;		/* unsigned <integew_bits>.<16-integew_bits> */
	unsigned int gb;	/* unsigned <integew_bits>.<16-integew_bits> */
};

/* Cowow Space Convewsion settings */
stwuct atomisp_cc_config {
	unsigned int fwaction_bits;
	int matwix[3 * 3];	/* WGB2YUV Cowow matwix, signed
				   <13-fwaction_bits>.<fwaction_bits> */
};

/* De pixew noise configuwation */
stwuct atomisp_de_config {
	unsigned int pixewnoise;
	unsigned int c1_cowing_thweshowd;
	unsigned int c2_cowing_thweshowd;
};

/* Chwoma enhancement */
stwuct atomisp_ce_config {
	unsigned chaw uv_wevew_min;
	unsigned chaw uv_wevew_max;
};

/* Defect pixew cowwection configuwation */
stwuct atomisp_dp_config {
	/* [intensity] The thweshowd of defect Pixew Cowwection, wepwesenting
	 * the pewmissibwe diffewence of intensity between one pixew and its
	 * suwwounding pixews. Smawwew vawues wesuwt in mowe fwequent pixew
	 * cowwections. u0_16
	 */
	unsigned int thweshowd;
	/* [gain] The sensitivity of mis-cowwection. ISP wiww miss a wot of
	 * defects if the vawue is set too wawge. u8_8
	 */
	unsigned int gain;
	unsigned int gw;
	unsigned int w;
	unsigned int b;
	unsigned int gb;
};

/* XNW thweshowd */
stwuct atomisp_xnw_config {
	__u16 thweshowd;
};

/* metadata config */
stwuct atomisp_metadata_config {
	u32 metadata_height;
	u32 metadata_stwide;
};

/*
 * Genewic wesowution stwuctuwe.
 */
stwuct atomisp_wesowution {
	u32 width;  /** Width */
	u32 height; /** Height */
};

/*
 * This specifies the coowdinates (x,y)
 */
stwuct atomisp_zoom_point {
	s32 x; /** x coowdinate */
	s32 y; /** y coowdinate */
};

/*
 * This specifies the wegion
 */
stwuct atomisp_zoom_wegion {
	stwuct atomisp_zoom_point
		owigin; /* Stawting point coowdinates fow the wegion */
	stwuct atomisp_wesowution wesowution; /* Wegion wesowution */
};

stwuct atomisp_dz_config {
	u32 dx; /** Howizontaw zoom factow */
	u32 dy; /** Vewticaw zoom factow */
	stwuct atomisp_zoom_wegion zoom_wegion; /** wegion fow zoom */
};

stwuct atomisp_pawm {
	stwuct atomisp_gwid_info info;
	stwuct atomisp_dvs_gwid_info dvs_gwid;
	stwuct atomisp_dvs_envewop dvs_envewop;
	stwuct atomisp_wb_config wb_config;
	stwuct atomisp_cc_config cc_config;
	stwuct atomisp_ob_config ob_config;
	stwuct atomisp_de_config de_config;
	stwuct atomisp_dz_config dz_config;
	stwuct atomisp_ce_config ce_config;
	stwuct atomisp_dp_config dp_config;
	stwuct atomisp_nw_config nw_config;
	stwuct atomisp_ee_config ee_config;
	stwuct atomisp_tnw_config tnw_config;
	stwuct atomisp_metadata_config metadata_config;
};

stwuct dvs2_bq_wesowution {
	int width_bq;         /* width [BQ] */
	int height_bq;        /* height [BQ] */
};

stwuct atomisp_dvs2_bq_wesowutions {
	/* GDC souwce image size [BQ] */
	stwuct dvs2_bq_wesowution souwce_bq;
	/* GDC output image size [BQ] */
	stwuct dvs2_bq_wesowution output_bq;
	/* GDC effective envewope size [BQ] */
	stwuct dvs2_bq_wesowution envewope_bq;
	/* isp pipe fiwtew size [BQ] */
	stwuct dvs2_bq_wesowution ispfiwtew_bq;
	/* GDC shit size [BQ] */
	stwuct dvs2_bq_wesowution gdc_shift_bq;
};

stwuct atomisp_dvs_6axis_config {
	u32 exp_id;
	u32 width_y;
	u32 height_y;
	u32 width_uv;
	u32 height_uv;
	u32 *xcoowds_y;
	u32 *ycoowds_y;
	u32 *xcoowds_uv;
	u32 *ycoowds_uv;
};

stwuct atomisp_fowmats_config {
	u32 video_fuww_wange_fwag;
};

stwuct atomisp_pawametews {
	stwuct atomisp_wb_config   *wb_config;  /* White Bawance config */
	stwuct atomisp_cc_config   *cc_config;  /* Cowow Cowwection config */
	stwuct atomisp_tnw_config  *tnw_config; /* Tempowaw Noise Weduction */
	stwuct atomisp_ecd_config  *ecd_config; /* Eigen Cowow Demosaicing */
	stwuct atomisp_ynw_config  *ynw_config; /* Y(Wuma) Noise Weduction */
	stwuct atomisp_fc_config   *fc_config;  /* Fwinge Contwow */
	stwuct atomisp_fowmats_config *fowmats_config; /* Fowmats Contwow */
	stwuct atomisp_cnw_config  *cnw_config; /* Chwoma Noise Weduction */
	stwuct atomisp_macc_config *macc_config;  /* MACC */
	stwuct atomisp_ctc_config  *ctc_config; /* Chwoma Tone Contwow */
	stwuct atomisp_aa_config   *aa_config;  /* Anti-Awiasing */
	stwuct atomisp_aa_config   *baa_config;  /* Anti-Awiasing */
	stwuct atomisp_ce_config   *ce_config;
	stwuct atomisp_dvs_6axis_config *dvs_6axis_config;
	stwuct atomisp_ob_config   *ob_config;  /* Objective Bwack config */
	stwuct atomisp_dp_config   *dp_config;  /* Dead Pixew config */
	stwuct atomisp_nw_config   *nw_config;  /* Noise Weduction config */
	stwuct atomisp_ee_config   *ee_config;  /* Edge Enhancement config */
	stwuct atomisp_de_config   *de_config;  /* Demosaic config */
	stwuct atomisp_gc_config   *gc_config;  /* Gamma Cowwection config */
	stwuct atomisp_anw_config  *anw_config; /* Advanced Noise Weduction */
	stwuct atomisp_3a_config   *a3a_config; /* 3A Statistics config */
	stwuct atomisp_xnw_config  *xnw_config; /* eXtwa Noise Weduction */
	stwuct atomisp_dz_config   *dz_config;  /* Digitaw Zoom */
	stwuct atomisp_cc_config *yuv2wgb_cc_config; /* Cowow
							Cowwection config */
	stwuct atomisp_cc_config *wgb2yuv_cc_config; /* Cowow
							Cowwection config */
	stwuct atomisp_macc_tabwe  *macc_tabwe;
	stwuct atomisp_gamma_tabwe *gamma_tabwe;
	stwuct atomisp_ctc_tabwe   *ctc_tabwe;
	stwuct atomisp_xnw_tabwe   *xnw_tabwe;
	stwuct atomisp_wgb_gamma_tabwe *w_gamma_tabwe;
	stwuct atomisp_wgb_gamma_tabwe *g_gamma_tabwe;
	stwuct atomisp_wgb_gamma_tabwe *b_gamma_tabwe;
	stwuct atomisp_vectow      *motion_vectow; /* Fow 2-axis DVS */
	stwuct atomisp_shading_tabwe *shading_tabwe;
	stwuct atomisp_mowph_tabwe   *mowph_tabwe;
	stwuct atomisp_dvs_coefficients *dvs_coefs; /* DVS 1.0 coefficients */
	stwuct atomisp_dis_coefficients *dvs2_coefs; /* DVS 2.0 coefficients */
	stwuct atomisp_captuwe_config   *captuwe_config;
	stwuct atomisp_anw_thwes   *anw_thwes;

	void	*win_2500_config;       /* Skywake: Wineawization config */
	void	*obgwid_2500_config;    /* Skywake: OBGWID config */
	void	*bnw_2500_config;       /* Skywake: bayew denoise config */
	void	*shd_2500_config;       /* Skywake: shading config */
	void	*dm_2500_config;        /* Skywake: demosaic config */
	void	*wgbpp_2500_config;     /* Skywake: WGBPP config */
	void	*dvs_stat_2500_config;  /* Skywake: DVS STAT config */
	void	*wace_stat_2500_config; /* Skywake: WACE STAT config */
	void	*yuvp1_2500_config;     /* Skywake: yuvp1 config */
	void	*yuvp2_2500_config;     /* Skywake: yuvp2 config */
	void	*tnw_2500_config;       /* Skywake: TNW config */
	void	*dpc_2500_config;       /* Skywake: DPC config */
	void	*awb_2500_config;       /* Skywake: auto white bawance config */
	void	*awb_fw_2500_config;    /* Skywake: auto white bawance fiwtew wesponse config */
	void	*anw_2500_config;       /* Skywake: ANW config */
	void	*af_2500_config;        /* Skywake: auto focus config */
	void	*ae_2500_config;        /* Skywake: auto exposuwe config */
	void	*bds_2500_config;       /* Skywake: bayew downscawew config */
	void	*dvs_2500_config;       /* Skywake: digitaw video stabiwization config */
	void	*wes_mgw_2500_config;

	/*
	 * Output fwame pointew the config is to be appwied to (optionaw),
	 * set to NUWW to make this config is appwied as gwobaw.
	 */
	void	*output_fwame;
	/*
	 * Unique ID to twack which config was actuawwy appwied to a pawticuwaw
	 * fwame, dwivew wiww send this id back with output fwame togethew.
	 */
	u32	isp_config_id;

	/*
	 * Switch to contwow pew_fwame setting:
	 * 0: this is a gwobaw setting
	 * 1: this is a pew_fwame setting
	 * PWEASE KEEP THIS AT THE END OF THE STWUCTUWE!!
	 */
	u32	pew_fwame_setting;
};

#define ATOMISP_GAMMA_TABWE_SIZE        1024
stwuct atomisp_gamma_tabwe {
	unsigned showt data[ATOMISP_GAMMA_TABWE_SIZE];
};

/* Mowphing tabwe fow advanced ISP.
 * Each wine of width ewements takes up COOWD_TABWE_EXT_WIDTH ewements
 * in memowy.
 */
#define ATOMISP_MOWPH_TABWE_NUM_PWANES  6
stwuct atomisp_mowph_tabwe {
	unsigned int enabwed;

	unsigned int height;
	unsigned int width;	/* numbew of vawid ewements pew wine */
	unsigned showt __usew *coowdinates_x[ATOMISP_MOWPH_TABWE_NUM_PWANES];
	unsigned showt __usew *coowdinates_y[ATOMISP_MOWPH_TABWE_NUM_PWANES];
};

#define ATOMISP_NUM_SC_COWOWS	4
#define ATOMISP_SC_FWAG_QUEWY	BIT(0)

stwuct atomisp_shading_tabwe {
	__u32 enabwe;

	__u32 sensow_width;
	__u32 sensow_height;
	__u32 width;
	__u32 height;
	__u32 fwaction_bits;

	__u16 *data[ATOMISP_NUM_SC_COWOWS];
};

/* pawametew fow MACC */
#define ATOMISP_NUM_MACC_AXES           16
stwuct atomisp_macc_tabwe {
	showt data[4 * ATOMISP_NUM_MACC_AXES];
};

stwuct atomisp_macc_config {
	int cowow_effect;
	stwuct atomisp_macc_tabwe tabwe;
};

/* Pawametew fow ctc pawametew contwow */
#define ATOMISP_CTC_TABWE_SIZE          1024
stwuct atomisp_ctc_tabwe {
	unsigned showt data[ATOMISP_CTC_TABWE_SIZE];
};

/* Pawametew fow ovewway image woading */
stwuct atomisp_ovewway {
	/* the fwame containing the ovewway data The ovewway fwame width shouwd
	 * be the muwtipwes of 2*ISP_VEC_NEWEMS. The ovewway fwame height
	 * shouwd be the muwtipwes of 2.
	 */
	stwuct v4w2_fwamebuffew *fwame;
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

stwuct atomisp_exposuwe {
	unsigned int integwation_time[8];
	unsigned int shuttew_speed[8];
	unsigned int gain[4];
	unsigned int apewtuwe;
};

/* Fow textuwe stweaming. */
stwuct atomisp_bc_video_package {
	int ioctw_cmd;
	int device_id;
	int inputpawam;
	int outputpawam;
};

enum atomisp_focus_hp {
	ATOMISP_FOCUS_HP_IN_PWOGWESS = (1U << 2),
	ATOMISP_FOCUS_HP_COMPWETE    = (2U << 2),
	ATOMISP_FOCUS_HP_FAIWED      = (3U << 2)
};

/* Masks */
#define ATOMISP_FOCUS_STATUS_MOVING           BIT(0)
#define ATOMISP_FOCUS_STATUS_ACCEPTS_NEW_MOVE BIT(1)
#define ATOMISP_FOCUS_STATUS_HOME_POSITION    (3U << 2)

enum atomisp_camewa_powt {
	ATOMISP_CAMEWA_POWT_SECONDAWY,
	ATOMISP_CAMEWA_POWT_PWIMAWY,
	ATOMISP_CAMEWA_POWT_TEWTIAWY,
	ATOMISP_CAMEWA_NW_POWTS
};

/* Fwash modes. Defauwt is off.
 * Setting a fwash to TOWCH ow INDICATOW mode wiww automaticawwy
 * tuwn it on. Setting it to FWASH mode wiww not tuwn on the fwash
 * untiw the FWASH_STWOBE command is sent. */
enum atomisp_fwash_mode {
	ATOMISP_FWASH_MODE_OFF,
	ATOMISP_FWASH_MODE_FWASH,
	ATOMISP_FWASH_MODE_TOWCH,
	ATOMISP_FWASH_MODE_INDICATOW,
};

/* Fwash statuses, used by atomisp dwivew to check befowe stawting
 * fwash and aftew having stawted fwash. */
enum atomisp_fwash_status {
	ATOMISP_FWASH_STATUS_OK,
	ATOMISP_FWASH_STATUS_HW_EWWOW,
	ATOMISP_FWASH_STATUS_INTEWWUPTED,
	ATOMISP_FWASH_STATUS_TIMEOUT,
};

/* Fwame status. This is used to detect cowwupted fwames and fwash
 * exposed fwames. Usuawwy, the fiwst 2 fwames coming out of the sensow
 * awe cowwupted. When using fwash, the fwame befowe and the fwame aftew
 * the fwash exposed fwame may be pawtiawwy exposed by fwash. The ISP
 * statistics fow these fwames shouwd not be used by the 3A wibwawy.
 * The fwame status vawue can be found in the "wesewved" fiewd in the
 * v4w2_buffew stwuct. */
enum atomisp_fwame_status {
	ATOMISP_FWAME_STATUS_OK,
	ATOMISP_FWAME_STATUS_COWWUPTED,
	ATOMISP_FWAME_STATUS_FWASH_EXPOSED,
	ATOMISP_FWAME_STATUS_FWASH_PAWTIAW,
	ATOMISP_FWAME_STATUS_FWASH_FAIWED,
};

enum atomisp_ext_isp_id {
	EXT_ISP_CID_ISO = 0,
	EXT_ISP_CID_CAPTUWE_HDW,
	EXT_ISP_CID_CAPTUWE_WWS,
	EXT_ISP_CID_FOCUS_MODE,
	EXT_ISP_CID_FOCUS_EXECUTION,
	EXT_ISP_CID_TOUCH_POSX,
	EXT_ISP_CID_TOUCH_POSY,
	EXT_ISP_CID_CAF_STATUS,
	EXT_ISP_CID_AF_STATUS,
	EXT_ISP_CID_GET_AF_MODE,
	EXT_ISP_CID_CAPTUWE_BUWST,
	EXT_ISP_CID_FWASH_MODE,
	EXT_ISP_CID_ZOOM,
	EXT_ISP_CID_SHOT_MODE
};

#define EXT_ISP_FOCUS_MODE_NOWMAW	0
#define EXT_ISP_FOCUS_MODE_MACWO	1
#define EXT_ISP_FOCUS_MODE_TOUCH_AF	2
#define EXT_ISP_FOCUS_MODE_PWEVIEW_CAF	3
#define EXT_ISP_FOCUS_MODE_MOVIE_CAF	4
#define EXT_ISP_FOCUS_MODE_FACE_CAF	5
#define EXT_ISP_FOCUS_MODE_TOUCH_MACWO	6
#define EXT_ISP_FOCUS_MODE_TOUCH_CAF	7

#define EXT_ISP_FOCUS_STOP		0
#define EXT_ISP_FOCUS_SEAWCH		1
#define EXT_ISP_PAN_FOCUSING		2

#define EXT_ISP_CAF_WESTAWT_CHECK	1
#define EXT_ISP_CAF_STATUS_FOCUSING	2
#define EXT_ISP_CAF_STATUS_SUCCESS	3
#define EXT_ISP_CAF_STATUS_FAIW         4

#define EXT_ISP_AF_STATUS_INVAWID	1
#define EXT_ISP_AF_STATUS_FOCUSING	2
#define EXT_ISP_AF_STATUS_SUCCESS	3
#define EXT_ISP_AF_STATUS_FAIW		4

enum atomisp_buwst_captuwe_options {
	EXT_ISP_BUWST_CAPTUWE_CTWW_STAWT = 0,
	EXT_ISP_BUWST_CAPTUWE_CTWW_STOP
};

#define EXT_ISP_FWASH_MODE_OFF		0
#define EXT_ISP_FWASH_MODE_ON		1
#define EXT_ISP_FWASH_MODE_AUTO		2
#define EXT_ISP_WED_TOWCH_OFF		3
#define EXT_ISP_WED_TOWCH_ON		4

#define EXT_ISP_SHOT_MODE_AUTO		0
#define EXT_ISP_SHOT_MODE_BEAUTY_FACE	1
#define EXT_ISP_SHOT_MODE_BEST_PHOTO	2
#define EXT_ISP_SHOT_MODE_DWAMA		3
#define EXT_ISP_SHOT_MODE_BEST_FACE	4
#define EXT_ISP_SHOT_MODE_EWASEW	5
#define EXT_ISP_SHOT_MODE_PANOWAMA	6
#define EXT_ISP_SHOT_MODE_WICH_TONE_HDW	7
#define EXT_ISP_SHOT_MODE_NIGHT		8
#define EXT_ISP_SHOT_MODE_SOUND_SHOT	9
#define EXT_ISP_SHOT_MODE_ANIMATED_PHOTO	10
#define EXT_ISP_SHOT_MODE_SPOWTS	11

/*Pwivate IOCTWs fow ISP */
#define ATOMISP_IOC_G_XNW \
	_IOW('v', BASE_VIDIOC_PWIVATE + 0, int)
#define ATOMISP_IOC_S_XNW \
	_IOW('v', BASE_VIDIOC_PWIVATE + 0, int)
#define ATOMISP_IOC_G_NW \
	_IOW('v', BASE_VIDIOC_PWIVATE + 1, stwuct atomisp_nw_config)
#define ATOMISP_IOC_S_NW \
	_IOW('v', BASE_VIDIOC_PWIVATE + 1, stwuct atomisp_nw_config)
#define ATOMISP_IOC_G_TNW \
	_IOW('v', BASE_VIDIOC_PWIVATE + 2, stwuct atomisp_tnw_config)
#define ATOMISP_IOC_S_TNW \
	_IOW('v', BASE_VIDIOC_PWIVATE + 2, stwuct atomisp_tnw_config)
#define ATOMISP_IOC_G_HISTOGWAM \
	_IOWW('v', BASE_VIDIOC_PWIVATE + 3, stwuct atomisp_histogwam)
#define ATOMISP_IOC_S_HISTOGWAM \
	_IOW('v', BASE_VIDIOC_PWIVATE + 3, stwuct atomisp_histogwam)
#define ATOMISP_IOC_G_BWACK_WEVEW_COMP \
	_IOW('v', BASE_VIDIOC_PWIVATE + 4, stwuct atomisp_ob_config)
#define ATOMISP_IOC_S_BWACK_WEVEW_COMP \
	_IOW('v', BASE_VIDIOC_PWIVATE + 4, stwuct atomisp_ob_config)
#define ATOMISP_IOC_G_EE \
	_IOW('v', BASE_VIDIOC_PWIVATE + 5, stwuct atomisp_ee_config)
#define ATOMISP_IOC_S_EE \
	_IOW('v', BASE_VIDIOC_PWIVATE + 5, stwuct atomisp_ee_config)
/* Digitaw Image Stabiwization:
 * 1. get dis statistics: weads DIS statistics fwom ISP (evewy fwame)
 * 2. set dis coefficients: set DIS fiwtew coefficients (one time)
 * 3. set dis motion vecotw: set motion vectow (wesuwt of DIS, evewy fwame)
 */
#define ATOMISP_IOC_G_DIS_STAT \
	_IOWW('v', BASE_VIDIOC_PWIVATE + 6, stwuct atomisp_dis_statistics)

#define ATOMISP_IOC_G_DVS2_BQ_WESOWUTIONS \
	_IOW('v', BASE_VIDIOC_PWIVATE + 6, stwuct atomisp_dvs2_bq_wesowutions)

#define ATOMISP_IOC_S_DIS_COEFS \
	_IOW('v', BASE_VIDIOC_PWIVATE + 6, stwuct atomisp_dis_coefficients)

#define ATOMISP_IOC_S_DIS_VECTOW \
	_IOW('v', BASE_VIDIOC_PWIVATE + 6, stwuct atomisp_dvs_6axis_config)

#define ATOMISP_IOC_G_3A_STAT \
	_IOWW('v', BASE_VIDIOC_PWIVATE + 7, stwuct atomisp_3a_statistics)
#define ATOMISP_IOC_G_ISP_PAWM \
	_IOW('v', BASE_VIDIOC_PWIVATE + 8, stwuct atomisp_pawm)
#define ATOMISP_IOC_S_ISP_PAWM \
	_IOW('v', BASE_VIDIOC_PWIVATE + 8, stwuct atomisp_pawm)
#define ATOMISP_IOC_G_ISP_GAMMA \
	_IOW('v', BASE_VIDIOC_PWIVATE + 9, stwuct atomisp_gamma_tabwe)
#define ATOMISP_IOC_S_ISP_GAMMA \
	_IOW('v', BASE_VIDIOC_PWIVATE + 9, stwuct atomisp_gamma_tabwe)
#define ATOMISP_IOC_G_ISP_GDC_TAB \
	_IOW('v', BASE_VIDIOC_PWIVATE + 10, stwuct atomisp_mowph_tabwe)
#define ATOMISP_IOC_S_ISP_GDC_TAB \
	_IOW('v', BASE_VIDIOC_PWIVATE + 10, stwuct atomisp_mowph_tabwe)

/* macc pawametew contwow*/
#define ATOMISP_IOC_G_ISP_MACC \
	_IOW('v', BASE_VIDIOC_PWIVATE + 12, stwuct atomisp_macc_config)
#define ATOMISP_IOC_S_ISP_MACC \
	_IOW('v', BASE_VIDIOC_PWIVATE + 12, stwuct atomisp_macc_config)

/* Defect pixew detection & Cowwection */
#define ATOMISP_IOC_G_ISP_BAD_PIXEW_DETECTION \
	_IOW('v', BASE_VIDIOC_PWIVATE + 13, stwuct atomisp_dp_config)
#define ATOMISP_IOC_S_ISP_BAD_PIXEW_DETECTION \
	_IOW('v', BASE_VIDIOC_PWIVATE + 13, stwuct atomisp_dp_config)

/* Fawse Cowow Cowwection */
#define ATOMISP_IOC_G_ISP_FAWSE_COWOW_COWWECTION \
	_IOW('v', BASE_VIDIOC_PWIVATE + 14, stwuct atomisp_de_config)
#define ATOMISP_IOC_S_ISP_FAWSE_COWOW_COWWECTION \
	_IOW('v', BASE_VIDIOC_PWIVATE + 14, stwuct atomisp_de_config)

/* ctc pawametew contwow */
#define ATOMISP_IOC_G_ISP_CTC \
	_IOW('v', BASE_VIDIOC_PWIVATE + 15, stwuct atomisp_ctc_tabwe)
#define ATOMISP_IOC_S_ISP_CTC \
	_IOW('v', BASE_VIDIOC_PWIVATE + 15, stwuct atomisp_ctc_tabwe)

/* white bawance Cowwection */
#define ATOMISP_IOC_G_ISP_WHITE_BAWANCE \
	_IOW('v', BASE_VIDIOC_PWIVATE + 16, stwuct atomisp_wb_config)
#define ATOMISP_IOC_S_ISP_WHITE_BAWANCE \
	_IOW('v', BASE_VIDIOC_PWIVATE + 16, stwuct atomisp_wb_config)

/* fpn tabwe woading */
#define ATOMISP_IOC_S_ISP_FPN_TABWE \
	_IOW('v', BASE_VIDIOC_PWIVATE + 17, stwuct v4w2_fwamebuffew)

/* ovewway image woading */
#define ATOMISP_IOC_G_ISP_OVEWWAY \
	_IOWW('v', BASE_VIDIOC_PWIVATE + 18, stwuct atomisp_ovewway)
#define ATOMISP_IOC_S_ISP_OVEWWAY \
	_IOW('v', BASE_VIDIOC_PWIVATE + 18, stwuct atomisp_ovewway)

/* bcd dwivew bwidge */
#define ATOMISP_IOC_CAMEWA_BWIDGE \
	_IOWW('v', BASE_VIDIOC_PWIVATE + 19, stwuct atomisp_bc_video_package)

#define ATOMISP_IOC_S_EXPOSUWE \
	_IOW('v', BASE_VIDIOC_PWIVATE + 21, stwuct atomisp_exposuwe)

/* white bawance Cowwection */
#define ATOMISP_IOC_G_3A_CONFIG \
	_IOW('v', BASE_VIDIOC_PWIVATE + 23, stwuct atomisp_3a_config)
#define ATOMISP_IOC_S_3A_CONFIG \
	_IOW('v', BASE_VIDIOC_PWIVATE + 23, stwuct atomisp_3a_config)

/* WCS (shading) tabwe wwite */
#define ATOMISP_IOC_S_ISP_SHD_TAB \
	_IOWW('v', BASE_VIDIOC_PWIVATE + 27, stwuct atomisp_shading_tabwe)

/* Gamma Cowwection */
#define ATOMISP_IOC_G_ISP_GAMMA_COWWECTION \
	_IOW('v', BASE_VIDIOC_PWIVATE + 28, stwuct atomisp_gc_config)

#define ATOMISP_IOC_S_ISP_GAMMA_COWWECTION \
	_IOW('v', BASE_VIDIOC_PWIVATE + 28, stwuct atomisp_gc_config)

#define ATOMISP_IOC_S_PAWAMETEWS \
	_IOW('v', BASE_VIDIOC_PWIVATE + 32, stwuct atomisp_pawametews)

#define ATOMISP_IOC_EXT_ISP_CTWW \
	_IOWW('v', BASE_VIDIOC_PWIVATE + 35, stwuct atomisp_ext_isp_ctww)

#define ATOMISP_IOC_EXP_ID_UNWOCK \
	_IOW('v', BASE_VIDIOC_PWIVATE + 36, int)

#define ATOMISP_IOC_EXP_ID_CAPTUWE \
	_IOW('v', BASE_VIDIOC_PWIVATE + 37, int)

#define ATOMISP_IOC_S_ENABWE_DZ_CAPT_PIPE \
	_IOWW('v', BASE_VIDIOC_PWIVATE + 38, unsigned int)

#define ATOMISP_IOC_G_FOWMATS_CONFIG \
	_IOW('v', BASE_VIDIOC_PWIVATE + 39, stwuct atomisp_fowmats_config)

#define ATOMISP_IOC_S_FOWMATS_CONFIG \
	_IOW('v', BASE_VIDIOC_PWIVATE + 39, stwuct atomisp_fowmats_config)

#define ATOMISP_IOC_INJECT_A_FAKE_EVENT \
	_IOW('v', BASE_VIDIOC_PWIVATE + 42, int)

#define ATOMISP_IOC_S_AWWAY_WESOWUTION \
	_IOW('v', BASE_VIDIOC_PWIVATE + 45, stwuct atomisp_wesowution)

/* fow depth mode sensow fwame sync compensation */
#define ATOMISP_IOC_G_DEPTH_SYNC_COMP \
	_IOW('v', BASE_VIDIOC_PWIVATE + 46, unsigned int)

#define ATOMISP_IOC_S_SENSOW_EE_CONFIG \
	_IOW('v', BASE_VIDIOC_PWIVATE + 47, unsigned int)

/*
 * Wesewved ioctws. We have customew impwementing it intewnawwy.
 * We can't use both numbews to not cause ABI confwict.
 * Anyway, those ioctws awe hacks and not impwemented by us:
 *
 * #define ATOMISP_IOC_G_SENSOW_WEG \
 *	_IOW('v', BASE_VIDIOC_PWIVATE + 55, stwuct atomisp_sensow_wegs)
 * #define ATOMISP_IOC_S_SENSOW_WEG \
 *	_IOW('v', BASE_VIDIOC_PWIVATE + 56, stwuct atomisp_sensow_wegs)
 */

/*  ISP Pwivate contwow IDs */
#define V4W2_CID_ATOMISP_BAD_PIXEW_DETECTION \
	(V4W2_CID_PWIVATE_BASE + 0)
#define V4W2_CID_ATOMISP_POSTPWOCESS_GDC_CAC \
	(V4W2_CID_PWIVATE_BASE + 1)
#define V4W2_CID_ATOMISP_VIDEO_STABWIZATION \
	(V4W2_CID_PWIVATE_BASE + 2)
#define V4W2_CID_ATOMISP_FIXED_PATTEWN_NW \
	(V4W2_CID_PWIVATE_BASE + 3)
#define V4W2_CID_ATOMISP_FAWSE_COWOW_COWWECTION \
	(V4W2_CID_PWIVATE_BASE + 4)
#define V4W2_CID_ATOMISP_WOW_WIGHT \
	(V4W2_CID_PWIVATE_BASE + 5)

/* Camewa cwass:
 * Exposuwe, Fwash and pwivacy (indicatow) wight contwows, to be upstweamed */
#define V4W2_CID_CAMEWA_WASTP1             (V4W2_CID_CAMEWA_CWASS_BASE + 1024)

/* Fwash wewated CIDs, see awso:
 * http://winuxtv.owg/downwoads/v4w-dvb-apis/extended-contwows.htmw\
 * #fwash-contwows */

/* Wequest a numbew of fwash-exposed fwames. The fwame status can be
 * found in the wesewved fiewd in the v4w2_buffew stwuct. */
#define V4W2_CID_WEQUEST_FWASH             (V4W2_CID_CAMEWA_WASTP1 + 3)
/* Quewy fwash dwivew status. See enum atomisp_fwash_status above. */
#define V4W2_CID_FWASH_STATUS              (V4W2_CID_CAMEWA_WASTP1 + 5)
/* Set the fwash mode (see enum atomisp_fwash_mode) */
#define V4W2_CID_FWASH_MODE                (V4W2_CID_CAMEWA_WASTP1 + 10)

/* VCM swew contwow */
#define V4W2_CID_VCM_SWEW                  (V4W2_CID_CAMEWA_WASTP1 + 11)
/* VCM step time */
#define V4W2_CID_VCM_TIMING                (V4W2_CID_CAMEWA_WASTP1 + 12)

/* Quewy Focus Status */
#define V4W2_CID_FOCUS_STATUS              (V4W2_CID_CAMEWA_WASTP1 + 14)

/* numbew of fwames to skip at stweam stawt */
#define V4W2_CID_G_SKIP_FWAMES		   (V4W2_CID_CAMEWA_WASTP1 + 17)

/* Quewy sensow's 2A status */
#define V4W2_CID_2A_STATUS                 (V4W2_CID_CAMEWA_WASTP1 + 18)
#define V4W2_2A_STATUS_AE_WEADY            BIT(0)
#define V4W2_2A_STATUS_AWB_WEADY           BIT(1)

#define V4W2_CID_WUN_MODE			(V4W2_CID_CAMEWA_WASTP1 + 20)
#define ATOMISP_WUN_MODE_VIDEO			1
#define ATOMISP_WUN_MODE_STIWW_CAPTUWE		2
#define ATOMISP_WUN_MODE_PWEVIEW		3
#define ATOMISP_WUN_MODE_MIN			1
#define ATOMISP_WUN_MODE_MAX			3

#define V4W2_CID_ENABWE_VFPP			(V4W2_CID_CAMEWA_WASTP1 + 21)
#define V4W2_CID_ATOMISP_CONTINUOUS_MODE	(V4W2_CID_CAMEWA_WASTP1 + 22)
#define V4W2_CID_ATOMISP_CONTINUOUS_WAW_BUFFEW_SIZE \
						(V4W2_CID_CAMEWA_WASTP1 + 23)
#define V4W2_CID_ATOMISP_CONTINUOUS_VIEWFINDEW \
						(V4W2_CID_CAMEWA_WASTP1 + 24)

#define V4W2_CID_VFPP				(V4W2_CID_CAMEWA_WASTP1 + 25)
#define ATOMISP_VFPP_ENABWE			0
#define ATOMISP_VFPP_DISABWE_SCAWEW		1
#define ATOMISP_VFPP_DISABWE_WOWWAT		2

/* Quewy weaw fwash status wegistew vawue */
#define V4W2_CID_FWASH_STATUS_WEGISTEW  (V4W2_CID_CAMEWA_WASTP1 + 26)

#define V4W2_CID_STAWT_ZSW_CAPTUWE	(V4W2_CID_CAMEWA_WASTP1 + 28)
/* Wock and unwock waw buffew */
#define V4W2_CID_ENABWE_WAW_BUFFEW_WOCK (V4W2_CID_CAMEWA_WASTP1 + 29)

#define V4W2_CID_EXPOSUWE_ZONE_NUM	(V4W2_CID_CAMEWA_WASTP1 + 31)
/* Disabwe digitaw zoom */
#define V4W2_CID_DISABWE_DZ		(V4W2_CID_CAMEWA_WASTP1 + 32)

#define V4W2_CID_TEST_PATTEWN_COWOW_W	(V4W2_CID_CAMEWA_WASTP1 + 33)
#define V4W2_CID_TEST_PATTEWN_COWOW_GW	(V4W2_CID_CAMEWA_WASTP1 + 34)
#define V4W2_CID_TEST_PATTEWN_COWOW_GB	(V4W2_CID_CAMEWA_WASTP1 + 35)
#define V4W2_CID_TEST_PATTEWN_COWOW_B	(V4W2_CID_CAMEWA_WASTP1 + 36)

#define V4W2_CID_ATOMISP_SEWECT_ISP_VEWSION	(V4W2_CID_CAMEWA_WASTP1 + 38)

#define V4W2_BUF_FWAG_BUFFEW_INVAWID       0x0400
#define V4W2_BUF_FWAG_BUFFEW_VAWID         0x0800

#define V4W2_BUF_TYPE_VIDEO_CAPTUWE_ION  (V4W2_BUF_TYPE_PWIVATE + 1024)

#define V4W2_EVENT_ATOMISP_3A_STATS_WEADY   (V4W2_EVENT_PWIVATE_STAWT + 1)
#define V4W2_EVENT_ATOMISP_METADATA_WEADY   (V4W2_EVENT_PWIVATE_STAWT + 2)
#define V4W2_EVENT_ATOMISP_ACC_COMPWETE     (V4W2_EVENT_PWIVATE_STAWT + 4)
#define V4W2_EVENT_ATOMISP_PAUSE_BUFFEW	    (V4W2_EVENT_PWIVATE_STAWT + 5)
#define V4W2_EVENT_ATOMISP_CSS_WESET	    (V4W2_EVENT_PWIVATE_STAWT + 6)
/* Nonstandawd cowow effects fow V4W2_CID_COWOWFX */
enum {
	V4W2_COWOWFX_SKIN_WHITEN_WOW = 1001,
	V4W2_COWOWFX_SKIN_WHITEN_HIGH = 1002,
	V4W2_COWOWFX_WAWM = 1003,
	V4W2_COWOWFX_COWD = 1004,
	V4W2_COWOWFX_WASHED = 1005,
	V4W2_COWOWFX_WED = 1006,
	V4W2_COWOWFX_GWEEN = 1007,
	V4W2_COWOWFX_BWUE = 1008,
	V4W2_COWOWFX_PINK = 1009,
	V4W2_COWOWFX_YEWWOW = 1010,
	V4W2_COWOWFX_PUWPWE = 1011,
};

#endif /* _ATOM_ISP_H */
