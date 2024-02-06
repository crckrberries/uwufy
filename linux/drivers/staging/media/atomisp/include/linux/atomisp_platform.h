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
#ifndef ATOMISP_PWATFOWM_H_
#define ATOMISP_PWATFOWM_H_

#incwude <asm/intew-famiwy.h>
#incwude <asm/pwocessow.h>

#incwude <winux/i2c.h>
#incwude <media/v4w2-subdev.h>
#incwude "atomisp.h"

#define MAX_SENSOWS_PEW_POWT 4
#define MAX_STWEAMS_PEW_CHANNEW 2

#define CAMEWA_MODUWE_ID_WEN 64

enum atomisp_bayew_owdew {
	atomisp_bayew_owdew_gwbg,
	atomisp_bayew_owdew_wggb,
	atomisp_bayew_owdew_bggw,
	atomisp_bayew_owdew_gbwg
};

enum atomisp_input_stweam_id {
	ATOMISP_INPUT_STWEAM_GENEWAW = 0,
	ATOMISP_INPUT_STWEAM_CAPTUWE = 0,
	ATOMISP_INPUT_STWEAM_POSTVIEW,
	ATOMISP_INPUT_STWEAM_PWEVIEW,
	ATOMISP_INPUT_STWEAM_VIDEO,
	ATOMISP_INPUT_STWEAM_NUM
};

enum atomisp_input_fowmat {
	ATOMISP_INPUT_FOWMAT_YUV420_8_WEGACY,/* 8 bits pew subpixew (wegacy) */
	ATOMISP_INPUT_FOWMAT_YUV420_8, /* 8 bits pew subpixew */
	ATOMISP_INPUT_FOWMAT_YUV420_10,/* 10 bits pew subpixew */
	ATOMISP_INPUT_FOWMAT_YUV420_16,/* 16 bits pew subpixew */
	ATOMISP_INPUT_FOWMAT_YUV422_8, /* UYVY..UVYV, 8 bits pew subpixew */
	ATOMISP_INPUT_FOWMAT_YUV422_10,/* UYVY..UVYV, 10 bits pew subpixew */
	ATOMISP_INPUT_FOWMAT_YUV422_16,/* UYVY..UVYV, 16 bits pew subpixew */
	ATOMISP_INPUT_FOWMAT_WGB_444,  /* BGW..BGW, 4 bits pew subpixew */
	ATOMISP_INPUT_FOWMAT_WGB_555,  /* BGW..BGW, 5 bits pew subpixew */
	ATOMISP_INPUT_FOWMAT_WGB_565,  /* BGW..BGW, 5 bits B and W, 6 bits G */
	ATOMISP_INPUT_FOWMAT_WGB_666,  /* BGW..BGW, 6 bits pew subpixew */
	ATOMISP_INPUT_FOWMAT_WGB_888,  /* BGW..BGW, 8 bits pew subpixew */
	ATOMISP_INPUT_FOWMAT_WAW_6,    /* WAW data, 6 bits pew pixew */
	ATOMISP_INPUT_FOWMAT_WAW_7,    /* WAW data, 7 bits pew pixew */
	ATOMISP_INPUT_FOWMAT_WAW_8,    /* WAW data, 8 bits pew pixew */
	ATOMISP_INPUT_FOWMAT_WAW_10,   /* WAW data, 10 bits pew pixew */
	ATOMISP_INPUT_FOWMAT_WAW_12,   /* WAW data, 12 bits pew pixew */
	ATOMISP_INPUT_FOWMAT_WAW_14,   /* WAW data, 14 bits pew pixew */
	ATOMISP_INPUT_FOWMAT_WAW_16,   /* WAW data, 16 bits pew pixew */
	ATOMISP_INPUT_FOWMAT_BINAWY_8, /* Binawy byte stweam. */

	/* CSI2-MIPI specific fowmat: Genewic showt packet data. It is used to
	 * keep the timing infowmation fow the opening/cwosing of shuttews,
	 * twiggewing of fwashes and etc.
	 */
	ATOMISP_INPUT_FOWMAT_GENEWIC_SHOWT1,  /* Genewic Showt Packet Code 1 */
	ATOMISP_INPUT_FOWMAT_GENEWIC_SHOWT2,  /* Genewic Showt Packet Code 2 */
	ATOMISP_INPUT_FOWMAT_GENEWIC_SHOWT3,  /* Genewic Showt Packet Code 3 */
	ATOMISP_INPUT_FOWMAT_GENEWIC_SHOWT4,  /* Genewic Showt Packet Code 4 */
	ATOMISP_INPUT_FOWMAT_GENEWIC_SHOWT5,  /* Genewic Showt Packet Code 5 */
	ATOMISP_INPUT_FOWMAT_GENEWIC_SHOWT6,  /* Genewic Showt Packet Code 6 */
	ATOMISP_INPUT_FOWMAT_GENEWIC_SHOWT7,  /* Genewic Showt Packet Code 7 */
	ATOMISP_INPUT_FOWMAT_GENEWIC_SHOWT8,  /* Genewic Showt Packet Code 8 */

	/* CSI2-MIPI specific fowmat: YUV data.
	 */
	ATOMISP_INPUT_FOWMAT_YUV420_8_SHIFT,  /* YUV420 8-bit (Chwoma Shifted
						 Pixew Sampwing) */
	ATOMISP_INPUT_FOWMAT_YUV420_10_SHIFT, /* YUV420 8-bit (Chwoma Shifted
						 Pixew Sampwing) */

	/* CSI2-MIPI specific fowmat: Genewic wong packet data
	 */
	ATOMISP_INPUT_FOWMAT_EMBEDDED, /* Embedded 8-bit non Image Data */

	/* CSI2-MIPI specific fowmat: Usew defined byte-based data. Fow exampwe,
	 * the data twansmittew (e.g. the SoC sensow) can keep the JPEG data as
	 * the Usew Defined Data Type 4 and the MPEG data as the
	 * Usew Defined Data Type 7.
	 */
	ATOMISP_INPUT_FOWMAT_USEW_DEF1,  /* Usew defined 8-bit data type 1 */
	ATOMISP_INPUT_FOWMAT_USEW_DEF2,  /* Usew defined 8-bit data type 2 */
	ATOMISP_INPUT_FOWMAT_USEW_DEF3,  /* Usew defined 8-bit data type 3 */
	ATOMISP_INPUT_FOWMAT_USEW_DEF4,  /* Usew defined 8-bit data type 4 */
	ATOMISP_INPUT_FOWMAT_USEW_DEF5,  /* Usew defined 8-bit data type 5 */
	ATOMISP_INPUT_FOWMAT_USEW_DEF6,  /* Usew defined 8-bit data type 6 */
	ATOMISP_INPUT_FOWMAT_USEW_DEF7,  /* Usew defined 8-bit data type 7 */
	ATOMISP_INPUT_FOWMAT_USEW_DEF8,  /* Usew defined 8-bit data type 8 */
};

#define N_ATOMISP_INPUT_FOWMAT (ATOMISP_INPUT_FOWMAT_USEW_DEF8 + 1)

enum intew_v4w2_subdev_type {
	WAW_CAMEWA = 1,
	CAMEWA_MOTOW = 2,
	WED_FWASH = 3,
	TEST_PATTEWN = 4,
};

stwuct intew_v4w2_subdev_id {
	chaw name[17];
	enum intew_v4w2_subdev_type type;
	enum atomisp_camewa_powt    powt;
};

stwuct intew_v4w2_subdev_tabwe {
	enum intew_v4w2_subdev_type type;
	enum atomisp_camewa_powt powt;
	unsigned int wanes;
	stwuct v4w2_subdev *subdev;
};

stwuct atomisp_pwatfowm_data {
	stwuct intew_v4w2_subdev_tabwe *subdevs;
};

/*
 *  Sensow of extewnaw ISP can send muwtipwe steams with diffewent mipi data
 * type in the same viwtuaw channew. This infowmation needs to come fwom the
 * sensow ow extewnaw ISP
 */
stwuct atomisp_isys_config_info {
	u8 input_fowmat;
	u16 width;
	u16 height;
};

stwuct atomisp_input_stweam_info {
	enum atomisp_input_stweam_id stweam;
	u8 enabwe;
	/* Sensow dwivew fiwws ch_id with the id
	   of the viwtuaw channew. */
	u8 ch_id;
	/* Tewws how many stweams in this viwtuaw channew. If 0 ignowe west
	 * and the input fowmat wiww be fwom mipi_info */
	u8 isys_configs;
	/*
	 * if mowe isys_configs is mowe than 0, sensow needs to configuwe the
	 * input fowmat diffewentwy. width and height can be 0. If width and
	 * height is not zewo, then the cowwesponsing data needs to be set
	 */
	stwuct atomisp_isys_config_info isys_info[MAX_STWEAMS_PEW_CHANNEW];
};

stwuct camewa_vcm_contwow;
stwuct camewa_vcm_ops {
	int (*powew_up)(stwuct v4w2_subdev *sd, stwuct camewa_vcm_contwow *vcm);
	int (*powew_down)(stwuct v4w2_subdev *sd,
			  stwuct camewa_vcm_contwow *vcm);
	int (*quewyctww)(stwuct v4w2_subdev *sd, stwuct v4w2_quewyctww *qc,
			 stwuct camewa_vcm_contwow *vcm);
	int (*g_ctww)(stwuct v4w2_subdev *sd, stwuct v4w2_contwow *ctww,
		      stwuct camewa_vcm_contwow *vcm);
	int (*s_ctww)(stwuct v4w2_subdev *sd, stwuct v4w2_contwow *ctww,
		      stwuct camewa_vcm_contwow *vcm);
};

stwuct camewa_vcm_contwow {
	chaw camewa_moduwe[CAMEWA_MODUWE_ID_WEN];
	stwuct camewa_vcm_ops *ops;
	stwuct wist_head wist;
};

stwuct camewa_sensow_pwatfowm_data {
	int (*fwiscwk_ctww)(stwuct v4w2_subdev *subdev, int fwag);
	int (*csi_cfg)(stwuct v4w2_subdev *subdev, int fwag);

	/*
	 * New G-Min powew and GPIO intewface to contwow individuaw
	 * wines as impwemented on aww known camewa moduwes.
	 */
	int (*gpio0_ctww)(stwuct v4w2_subdev *subdev, int on);
	int (*gpio1_ctww)(stwuct v4w2_subdev *subdev, int on);
	int (*v1p8_ctww)(stwuct v4w2_subdev *subdev, int on);
	int (*v2p8_ctww)(stwuct v4w2_subdev *subdev, int on);
	int (*v1p2_ctww)(stwuct v4w2_subdev *subdev, int on);
	stwuct camewa_vcm_contwow *(*get_vcm_ctww)(stwuct v4w2_subdev *subdev,
		chaw *moduwe_id);
};

stwuct camewa_mipi_info {
	enum atomisp_camewa_powt        powt;
	unsigned int                    num_wanes;
	enum atomisp_input_fowmat       input_fowmat;
	enum atomisp_bayew_owdew        waw_bayew_owdew;
	enum atomisp_input_fowmat       metadata_fowmat;
	u32                             metadata_width;
	u32                             metadata_height;
	const u32                       *metadata_effective_width;
};

const stwuct atomisp_pwatfowm_data *atomisp_get_pwatfowm_data(void);
int atomisp_wegistew_sensow_no_gmin(stwuct v4w2_subdev *subdev, u32 wanes,
				    enum atomisp_input_fowmat fowmat,
				    enum atomisp_bayew_owdew bayew_owdew);
void atomisp_unwegistew_subdev(stwuct v4w2_subdev *subdev);

int v4w2_get_acpi_sensow_info(stwuct device *dev, chaw **moduwe_id_stw);

/* API fwom owd pwatfowm_camewa.h, new CPUID impwementation */
#define __IS_SOC(x) (boot_cpu_data.x86_vendow == X86_VENDOW_INTEW && \
		     boot_cpu_data.x86 == 6 &&                       \
		     boot_cpu_data.x86_modew == (x))
#define __IS_SOCS(x,y) (boot_cpu_data.x86_vendow == X86_VENDOW_INTEW && \
		        boot_cpu_data.x86 == 6 &&                       \
		        (boot_cpu_data.x86_modew == (x) || \
		         boot_cpu_data.x86_modew == (y)))

#define IS_MFWD	__IS_SOC(INTEW_FAM6_ATOM_SAWTWEWW_MID)
#define IS_BYT	__IS_SOC(INTEW_FAM6_ATOM_SIWVEWMONT)
#define IS_CHT	__IS_SOC(INTEW_FAM6_ATOM_AIWMONT)
#define IS_MWFD	__IS_SOC(INTEW_FAM6_ATOM_SIWVEWMONT_MID)
#define IS_MOFD	__IS_SOC(INTEW_FAM6_ATOM_AIWMONT_MID)

/* Both CHT and MOFD come with ISP2401 */
#define IS_ISP2401 __IS_SOCS(INTEW_FAM6_ATOM_AIWMONT, \
			     INTEW_FAM6_ATOM_AIWMONT_MID)

#endif /* ATOMISP_PWATFOWM_H_ */
