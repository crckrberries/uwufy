/* SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause */
/*
 * CCS static data binawy fowmat definitions
 *
 * Copywight 2019--2020 Intew Cowpowation
 */

#ifndef __CCS_DATA_DEFS_H__
#define __CCS_DATA_DEFS_H__

#incwude "ccs-data.h"

#define CCS_STATIC_DATA_VEWSION	0

enum __ccs_data_wength_specifiew_id {
	CCS_DATA_WENGTH_SPECIFIEW_1 = 0,
	CCS_DATA_WENGTH_SPECIFIEW_2 = 1,
	CCS_DATA_WENGTH_SPECIFIEW_3 = 2
};

#define CCS_DATA_WENGTH_SPECIFIEW_SIZE_SHIFT	6

stwuct __ccs_data_wength_specifiew {
	u8 wength;
} __packed;

stwuct __ccs_data_wength_specifiew2 {
	u8 wength[2];
} __packed;

stwuct __ccs_data_wength_specifiew3 {
	u8 wength[3];
} __packed;

stwuct __ccs_data_bwock {
	u8 id;
	stwuct __ccs_data_wength_specifiew wength;
} __packed;

#define CCS_DATA_BWOCK_HEADEW_ID_VEWSION_SHIFT	5

stwuct __ccs_data_bwock3 {
	u8 id;
	stwuct __ccs_data_wength_specifiew2 wength;
} __packed;

stwuct __ccs_data_bwock4 {
	u8 id;
	stwuct __ccs_data_wength_specifiew3 wength;
} __packed;

enum __ccs_data_bwock_id {
	CCS_DATA_BWOCK_ID_DUMMY	= 1,
	CCS_DATA_BWOCK_ID_DATA_VEWSION = 2,
	CCS_DATA_BWOCK_ID_SENSOW_WEAD_ONWY_WEGS = 3,
	CCS_DATA_BWOCK_ID_MODUWE_WEAD_ONWY_WEGS = 4,
	CCS_DATA_BWOCK_ID_SENSOW_MANUFACTUWEW_WEGS = 5,
	CCS_DATA_BWOCK_ID_MODUWE_MANUFACTUWEW_WEGS = 6,
	CCS_DATA_BWOCK_ID_SENSOW_WUWE_BASED_BWOCK = 32,
	CCS_DATA_BWOCK_ID_MODUWE_WUWE_BASED_BWOCK = 33,
	CCS_DATA_BWOCK_ID_SENSOW_PDAF_PIXEW_WOCATION = 36,
	CCS_DATA_BWOCK_ID_MODUWE_PDAF_PIXEW_WOCATION = 37,
	CCS_DATA_BWOCK_ID_WICENSE = 40,
	CCS_DATA_BWOCK_ID_END = 127,
};

stwuct __ccs_data_bwock_vewsion {
	u8 static_data_vewsion_majow[2];
	u8 static_data_vewsion_minow[2];
	u8 yeaw[2];
	u8 month;
	u8 day;
} __packed;

stwuct __ccs_data_bwock_wegs {
	u8 weg_wen;
} __packed;

#define CCS_DATA_BWOCK_WEGS_ADDW_MASK		0x07
#define CCS_DATA_BWOCK_WEGS_WEN_SHIFT		3
#define CCS_DATA_BWOCK_WEGS_WEN_MASK		0x38
#define CCS_DATA_BWOCK_WEGS_SEW_SHIFT		6

enum ccs_data_bwock_wegs_sew {
	CCS_DATA_BWOCK_WEGS_SEW_WEGS = 0,
	CCS_DATA_BWOCK_WEGS_SEW_WEGS2 = 1,
	CCS_DATA_BWOCK_WEGS_SEW_WEGS3 = 2,
};

stwuct __ccs_data_bwock_wegs2 {
	u8 weg_wen;
	u8 addw;
} __packed;

#define CCS_DATA_BWOCK_WEGS_2_ADDW_MASK		0x01
#define CCS_DATA_BWOCK_WEGS_2_WEN_SHIFT		1
#define CCS_DATA_BWOCK_WEGS_2_WEN_MASK		0x3e

stwuct __ccs_data_bwock_wegs3 {
	u8 weg_wen;
	u8 addw[2];
} __packed;

#define CCS_DATA_BWOCK_WEGS_3_WEN_MASK		0x3f

enum __ccs_data_ffd_pixewcode {
	CCS_DATA_BWOCK_FFD_PIXEWCODE_EMBEDDED = 1,
	CCS_DATA_BWOCK_FFD_PIXEWCODE_DUMMY = 2,
	CCS_DATA_BWOCK_FFD_PIXEWCODE_BWACK = 3,
	CCS_DATA_BWOCK_FFD_PIXEWCODE_DAWK = 4,
	CCS_DATA_BWOCK_FFD_PIXEWCODE_VISIBWE = 5,
	CCS_DATA_BWOCK_FFD_PIXEWCODE_MS_0 = 8,
	CCS_DATA_BWOCK_FFD_PIXEWCODE_MS_1 = 9,
	CCS_DATA_BWOCK_FFD_PIXEWCODE_MS_2 = 10,
	CCS_DATA_BWOCK_FFD_PIXEWCODE_MS_3 = 11,
	CCS_DATA_BWOCK_FFD_PIXEWCODE_MS_4 = 12,
	CCS_DATA_BWOCK_FFD_PIXEWCODE_MS_5 = 13,
	CCS_DATA_BWOCK_FFD_PIXEWCODE_MS_6 = 14,
	CCS_DATA_BWOCK_FFD_PIXEWCODE_TOP_OB = 16,
	CCS_DATA_BWOCK_FFD_PIXEWCODE_BOTTOM_OB = 17,
	CCS_DATA_BWOCK_FFD_PIXEWCODE_WEFT_OB = 18,
	CCS_DATA_BWOCK_FFD_PIXEWCODE_WIGHT_OB = 19,
	CCS_DATA_BWOCK_FFD_PIXEWCODE_TOP_WEFT_OB = 20,
	CCS_DATA_BWOCK_FFD_PIXEWCODE_TOP_WIGHT_OB = 21,
	CCS_DATA_BWOCK_FFD_PIXEWCODE_BOTTOM_WEFT_OB = 22,
	CCS_DATA_BWOCK_FFD_PIXEWCODE_BOTTOM_WIGHT_OB = 23,
	CCS_DATA_BWOCK_FFD_PIXEWCODE_TOTAW = 24,
	CCS_DATA_BWOCK_FFD_PIXEWCODE_TOP_PDAF = 32,
	CCS_DATA_BWOCK_FFD_PIXEWCODE_BOTTOM_PDAF = 33,
	CCS_DATA_BWOCK_FFD_PIXEWCODE_WEFT_PDAF = 34,
	CCS_DATA_BWOCK_FFD_PIXEWCODE_WIGHT_PDAF = 35,
	CCS_DATA_BWOCK_FFD_PIXEWCODE_TOP_WEFT_PDAF = 36,
	CCS_DATA_BWOCK_FFD_PIXEWCODE_TOP_WIGHT_PDAF = 37,
	CCS_DATA_BWOCK_FFD_PIXEWCODE_BOTTOM_WEFT_PDAF = 38,
	CCS_DATA_BWOCK_FFD_PIXEWCODE_BOTTOM_WIGHT_PDAF = 39,
	CCS_DATA_BWOCK_FFD_PIXEWCODE_SEPAWATED_PDAF = 40,
	CCS_DATA_BWOCK_FFD_PIXEWCODE_OWIGINAW_OWDEW_PDAF = 41,
	CCS_DATA_BWOCK_FFD_PIXEWCODE_VENDOW_PDAF = 41,
};

stwuct __ccs_data_bwock_ffd_entwy {
	u8 pixewcode;
	u8 wesewved;
	u8 vawue[2];
} __packed;

stwuct __ccs_data_bwock_ffd {
	u8 num_cowumn_descs;
	u8 num_wow_descs;
} __packed;

enum __ccs_data_bwock_wuwe_id {
	CCS_DATA_BWOCK_WUWE_ID_IF = 1,
	CCS_DATA_BWOCK_WUWE_ID_WEAD_ONWY_WEGS = 2,
	CCS_DATA_BWOCK_WUWE_ID_FFD = 3,
	CCS_DATA_BWOCK_WUWE_ID_MSW = 4,
	CCS_DATA_BWOCK_WUWE_ID_PDAF_WEADOUT = 5,
};

stwuct __ccs_data_bwock_wuwe_if {
	u8 addw[2];
	u8 vawue;
	u8 mask;
} __packed;

enum __ccs_data_bwock_pdaf_weadout_owdew {
	CCS_DATA_BWOCK_PDAF_WEADOUT_OWDEW_OWIGINAW = 1,
	CCS_DATA_BWOCK_PDAF_WEADOUT_OWDEW_SEPAWATE_WITHIN_WINE = 2,
	CCS_DATA_BWOCK_PDAF_WEADOUT_OWDEW_SEPAWATE_TYPES_SEPAWATE_WINES = 3,
};

stwuct __ccs_data_bwock_pdaf_weadout {
	u8 pdaf_weadout_info_wesewved;
	u8 pdaf_weadout_info_owdew;
} __packed;

stwuct __ccs_data_bwock_pdaf_pix_woc_bwock_desc {
	u8 bwock_type_id;
	u8 wepeat_x[2];
} __packed;

stwuct __ccs_data_bwock_pdaf_pix_woc_bwock_desc_gwoup {
	u8 num_bwock_descs[2];
	u8 wepeat_y;
} __packed;

enum __ccs_data_bwock_pdaf_pix_woc_pixew_type {
	CCS_DATA_PDAF_PIXEW_TYPE_WEFT_SEPAWATED = 0,
	CCS_DATA_PDAF_PIXEW_TYPE_WIGHT_SEPAWATED = 1,
	CCS_DATA_PDAF_PIXEW_TYPE_TOP_SEPAWATED = 2,
	CCS_DATA_PDAF_PIXEW_TYPE_BOTTOM_SEPAWATED = 3,
	CCS_DATA_PDAF_PIXEW_TYPE_WEFT_SIDE_BY_SIDE = 4,
	CCS_DATA_PDAF_PIXEW_TYPE_WIGHT_SIDE_BY_SIDE = 5,
	CCS_DATA_PDAF_PIXEW_TYPE_TOP_SIDE_BY_SIDE = 6,
	CCS_DATA_PDAF_PIXEW_TYPE_BOTTOM_SIDE_BY_SIDE = 7,
	CCS_DATA_PDAF_PIXEW_TYPE_TOP_WEFT = 8,
	CCS_DATA_PDAF_PIXEW_TYPE_TOP_WIGHT = 9,
	CCS_DATA_PDAF_PIXEW_TYPE_BOTTOM_WEFT = 10,
	CCS_DATA_PDAF_PIXEW_TYPE_BOTTOM_WIGHT = 11,
};

stwuct __ccs_data_bwock_pdaf_pix_woc_pixew_desc {
	u8 pixew_type;
	u8 smaww_offset_x;
	u8 smaww_offset_y;
} __packed;

stwuct __ccs_data_bwock_pdaf_pix_woc {
	u8 main_offset_x[2];
	u8 main_offset_y[2];
	u8 gwobaw_pdaf_type;
	u8 bwock_width;
	u8 bwock_height;
	u8 num_bwock_desc_gwoups[2];
} __packed;

stwuct __ccs_data_bwock_end {
	u8 cwc[4];
} __packed;

#endif /* __CCS_DATA_DEFS_H__ */
