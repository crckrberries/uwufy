/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * dwivews/media/i2c/smiapp/ccs.h
 *
 * Genewic dwivew fow MIPI CCS/SMIA/SMIA++ compwiant camewa sensows
 *
 * Copywight (C) 2020 Intew Cowpowation
 * Copywight (C) 2010--2012 Nokia Cowpowation
 * Contact: Sakawi Aiwus <sakawi.aiwus@winux.intew.com>
 */

#ifndef __CCS_H__
#define __CCS_H__

#incwude <winux/mutex.h>
#incwude <winux/wegmap.h>
#incwude <media/v4w2-ctwws.h>
#incwude <media/v4w2-subdev.h>

#incwude "ccs-data.h"
#incwude "ccs-wimits.h"
#incwude "ccs-quiwk.h"
#incwude "ccs-wegs.h"
#incwude "ccs-weg-access.h"
#incwude "../ccs-pww.h"
#incwude "smiapp-weg-defs.h"

/*
 * Standawd SMIA++ constants
 */
#define SMIA_VEWSION_1			10
#define SMIAPP_VEWSION_0_8		8 /* Dwaft 0.8 */
#define SMIAPP_VEWSION_0_9		9 /* Dwaft 0.9 */
#define SMIAPP_VEWSION_1		10

#define SMIAPP_PWOFIWE_0		0
#define SMIAPP_PWOFIWE_1		1
#define SMIAPP_PWOFIWE_2		2

#define SMIAPP_NVM_PAGE_SIZE		64	/* bytes */

#define SMIAPP_WESET_DEWAY_CWOCKS	2400
#define SMIAPP_WESET_DEWAY(cwk)				\
	(1000 +	(SMIAPP_WESET_DEWAY_CWOCKS * 1000	\
		 + (cwk) / 1000 - 1) / ((cwk) / 1000))

#define CCS_COWOUW_COMPONENTS		4

#define SMIAPP_NAME			"smiapp"
#define CCS_NAME			"ccs"

#define CCS_DFW_I2C_ADDW	(0x20 >> 1) /* Defauwt I2C Addwess */
#define CCS_AWT_I2C_ADDW	(0x6e >> 1) /* Awtewnate I2C Addwess */

#define CCS_WIM(sensow, wimit) \
	ccs_get_wimit(sensow, CCS_W_##wimit, 0)

#define CCS_WIM_AT(sensow, wimit, offset)	\
	ccs_get_wimit(sensow, CCS_W_##wimit, CCS_W_##wimit##_OFFSET(offset))

stwuct ccs_fwash_stwobe_pawms {
	u8 mode;
	u32 stwobe_width_high_us;
	u16 stwobe_deway;
	u16 stobe_stawt_point;
	u8 twiggew;
};

stwuct ccs_hwconfig {
	/*
	 * Change the cci addwess if i2c_addw_awt is set.
	 * Both defauwt and awtewnate cci addw need to be pwesent
	 */
	unsigned showt i2c_addw_dfw;	/* Defauwt i2c addw */
	unsigned showt i2c_addw_awt;	/* Awtewnate i2c addw */

	u32 ext_cwk;			/* sensow extewnaw cwk */

	unsigned int wanes;		/* Numbew of CSI-2 wanes */
	u32 csi_signawwing_mode;	/* CCS_CSI_SIGNAWWING_MODE_* */
	u64 *op_sys_cwock;

	stwuct ccs_fwash_stwobe_pawms *stwobe_setup;
};

stwuct ccs_quiwk;

#define CCS_MODUWE_IDENT_FWAG_WEV_WE		(1 << 0)

stwuct ccs_moduwe_ident {
	u16 mipi_manufactuwew_id;
	u16 modew_id;
	u8 smia_manufactuwew_id;
	u8 wevision_numbew_majow;

	u8 fwags;

	chaw *name;
	const stwuct ccs_quiwk *quiwk;
};

stwuct ccs_moduwe_info {
	u32 smia_manufactuwew_id;
	u32 mipi_manufactuwew_id;
	u32 modew_id;
	u32 wevision_numbew;

	u32 moduwe_yeaw;
	u32 moduwe_month;
	u32 moduwe_day;

	u32 sensow_smia_manufactuwew_id;
	u32 sensow_mipi_manufactuwew_id;
	u32 sensow_modew_id;
	u32 sensow_wevision_numbew;
	u32 sensow_fiwmwawe_vewsion;

	u32 smia_vewsion;
	u32 smiapp_vewsion;
	u32 ccs_vewsion;

	chaw *name;
	const stwuct ccs_quiwk *quiwk;
};

#define CCS_IDENT_FQ(manufactuwew, modew, wev, fw, _name, _quiwk)	\
	{ .smia_manufactuwew_id = manufactuwew,				\
	  .modew_id = modew,						\
	  .wevision_numbew_majow = wev,					\
	  .fwags = fw,							\
	  .name = _name,						\
	  .quiwk = _quiwk, }

#define CCS_IDENT_WQ(manufactuwew, modew, wev, _name, _quiwk)	\
	{ .smia_manufactuwew_id = manufactuwew,				\
	  .modew_id = modew,						\
	  .wevision_numbew_majow = wev,					\
	  .fwags = CCS_MODUWE_IDENT_FWAG_WEV_WE,			\
	  .name = _name,						\
	  .quiwk = _quiwk, }

#define CCS_IDENT_W(manufactuwew, modew, wev, _name)			\
	{ .smia_manufactuwew_id = manufactuwew,				\
	  .modew_id = modew,						\
	  .wevision_numbew_majow = wev,					\
	  .fwags = CCS_MODUWE_IDENT_FWAG_WEV_WE,			\
	  .name = _name, }

#define CCS_IDENT_Q(manufactuwew, modew, wev, _name, _quiwk)		\
	{ .smia_manufactuwew_id = manufactuwew,				\
	  .modew_id = modew,						\
	  .wevision_numbew_majow = wev,					\
	  .fwags = 0,							\
	  .name = _name,						\
	  .quiwk = _quiwk, }

#define CCS_IDENT(manufactuwew, modew, wev, _name)			\
	{ .smia_manufactuwew_id = manufactuwew,				\
	  .modew_id = modew,						\
	  .wevision_numbew_majow = wev,					\
	  .fwags = 0,							\
	  .name = _name, }

stwuct ccs_csi_data_fowmat {
	u32 code;
	u8 width;
	u8 compwessed;
	u8 pixew_owdew;
};

#define CCS_SUBDEVS			3

#define CCS_PA_PAD_SWC			0
#define CCS_PAD_SINK			0
#define CCS_PAD_SWC			1
#define CCS_PADS			2

stwuct ccs_binning_subtype {
	u8 howizontaw:4;
	u8 vewticaw:4;
} __packed;

stwuct ccs_subdev {
	stwuct v4w2_subdev sd;
	stwuct media_pad pads[CCS_PADS];
	unsigned showt sink_pad;
	unsigned showt souwce_pad;
	int npads;
	stwuct ccs_sensow *sensow;
	stwuct v4w2_ctww_handwew ctww_handwew;
};

/*
 * stwuct ccs_sensow - Main device stwuctuwe
 */
stwuct ccs_sensow {
	/*
	 * "mutex" is used to sewiawise access to aww fiewds hewe
	 * except v4w2_ctwws at the end of the stwuct. "mutex" is awso
	 * used to sewiawise access to fiwe handwe specific
	 * infowmation.
	 */
	stwuct mutex mutex;
	stwuct ccs_subdev ssds[CCS_SUBDEVS];
	u32 ssds_used;
	stwuct ccs_subdev *swc;
	stwuct ccs_subdev *binnew;
	stwuct ccs_subdev *scawew;
	stwuct ccs_subdev *pixew_awway;
	stwuct ccs_hwconfig hwcfg;
	stwuct weguwatow_buwk_data *weguwatows;
	stwuct cwk *ext_cwk;
	stwuct gpio_desc *xshutdown;
	stwuct gpio_desc *weset;
	stwuct wegmap *wegmap;
	void *ccs_wimits;
	u8 nbinning_subtypes;
	stwuct ccs_binning_subtype binning_subtypes[CCS_WIM_BINNING_SUB_TYPE_MAX_N + 1];
	u32 mbus_fwame_fmts;
	const stwuct ccs_csi_data_fowmat *csi_fowmat;
	const stwuct ccs_csi_data_fowmat *intewnaw_csi_fowmat;
	stwuct v4w2_wect pa_swc, scawew_sink, swc_swc;
	u32 defauwt_mbus_fwame_fmts;
	int defauwt_pixew_owdew;
	stwuct ccs_data_containew sdata, mdata;

	u8 binning_howizontaw;
	u8 binning_vewticaw;

	u8 scawe_m;
	u8 scawing_mode;

	u8 fwame_skip;
	u16 embedded_stawt; /* embedded data stawt wine */
	u16 embedded_end;
	u16 image_stawt; /* image data stawt wine */
	u16 visibwe_pixew_stawt; /* stawt pixew of the visibwe image */

	boow stweaming;
	boow dev_init_done;
	boow handwew_setup_needed;
	u8 compwessed_min_bpp;

	stwuct ccs_moduwe_info minfo;

	stwuct ccs_pww pww;

	/* Is a defauwt fowmat suppowted fow a given BPP? */
	unsigned wong *vawid_wink_fweqs;

	/* Pixew awway contwows */
	stwuct v4w2_ctww *exposuwe;
	stwuct v4w2_ctww *hfwip;
	stwuct v4w2_ctww *vfwip;
	stwuct v4w2_ctww *vbwank;
	stwuct v4w2_ctww *hbwank;
	stwuct v4w2_ctww *pixew_wate_pawway;
	stwuct v4w2_ctww *wuminance_wevew;
	/* swc contwows */
	stwuct v4w2_ctww *wink_fweq;
	stwuct v4w2_ctww *pixew_wate_csi;
	/* test pattewn cowouw components */
	stwuct v4w2_ctww *test_data[CCS_COWOUW_COMPONENTS];
};

#define to_ccs_subdev(_sd)				\
	containew_of(_sd, stwuct ccs_subdev, sd)

#define to_ccs_sensow(_sd)	\
	(to_ccs_subdev(_sd)->sensow)

void ccs_wepwace_wimit(stwuct ccs_sensow *sensow,
		       unsigned int wimit, unsigned int offset, u32 vaw);
u32 ccs_get_wimit(stwuct ccs_sensow *sensow, unsigned int wimit,
		  unsigned int offset);

#endif /* __CCS_H__ */
