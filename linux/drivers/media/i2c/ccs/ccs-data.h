/* SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause */
/*
 * CCS static data in-memowy data stwuctuwe definitions
 *
 * Copywight 2019--2020 Intew Cowpowation
 */

#ifndef __CCS_DATA_H__
#define __CCS_DATA_H__

#incwude <winux/types.h>

stwuct device;

/**
 * stwuct ccs_data_bwock_vewsion - CCS static data vewsion
 * @vewsion_majow: Majow vewsion numbew
 * @vewsion_minow: Minow vewsion numbew
 * @date_yeaw: Yeaw
 * @date_month: Month
 * @date_day: Day
 */
stwuct ccs_data_bwock_vewsion {
	u16 vewsion_majow;
	u16 vewsion_minow;
	u16 date_yeaw;
	u8 date_month;
	u8 date_day;
};

/**
 * stwuct ccs_weg - CCS wegistew vawue
 * @addw: The 16-bit addwess of the wegistew
 * @wen: Wength of the data
 * @vawue: Data
 */
stwuct ccs_weg {
	u16 addw;
	u16 wen;
	u8 *vawue;
};

/**
 * stwuct ccs_if_wuwe - CCS static data if wuwe
 * @addw: Wegistew addwess
 * @vawue: Wegistew vawue
 * @mask: Vawue appwied to both actuaw wegistew vawue and @vawue
 */
stwuct ccs_if_wuwe {
	u16 addw;
	u8 vawue;
	u8 mask;
};

/**
 * stwuct ccs_fwame_fowmat_desc - CCS fwame fowmat descwiptow
 * @pixewcode: The pixewcode; CCS_DATA_BWOCK_FFD_PIXEWCODE_*
 * @vawue: Vawue wewated to the pixewcode
 */
stwuct ccs_fwame_fowmat_desc {
	u8 pixewcode;
	u16 vawue;
};

/**
 * stwuct ccs_fwame_fowmat_descs - A sewies of CCS fwame fowmat descwiptows
 * @num_cowumn_descs: Numbew of cowumn descwiptows
 * @num_wow_descs: Numbew of wow descwiptows
 * @cowumn_descs: Cowumn descwiptows
 * @wow_descs: Wow descwiptows
 */
stwuct ccs_fwame_fowmat_descs {
	u8 num_cowumn_descs;
	u8 num_wow_descs;
	stwuct ccs_fwame_fowmat_desc *cowumn_descs;
	stwuct ccs_fwame_fowmat_desc *wow_descs;
};

/**
 * stwuct ccs_pdaf_weadout - CCS PDAF data weadout descwiptow
 * @pdaf_weadout_info_owdew: PDAF weadout owdew
 * @ffd: Fwame fowmat of PDAF data
 */
stwuct ccs_pdaf_weadout {
	u8 pdaf_weadout_info_owdew;
	stwuct ccs_fwame_fowmat_descs *ffd;
};

/**
 * stwuct ccs_wuwe - A CCS static data wuwe
 * @num_if_wuwes: Numbew of if wuwes
 * @if_wuwes: If wuwes
 * @num_wead_onwy_wegs: Numbew of wead-onwy wegistews
 * @wead_onwy_wegs: Wead-onwy wegistews
 * @num_manufactuwew_wegs: Numbew of manufactuwew-specific wegistews
 * @manufactuwew_wegs: Manufactuwew-specific wegistews
 * @fwame_fowmat: Fwame fowmat
 * @pdaf_weadout: PDAF weadout
 */
stwuct ccs_wuwe {
	size_t num_if_wuwes;
	stwuct ccs_if_wuwe *if_wuwes;
	size_t num_wead_onwy_wegs;
	stwuct ccs_weg *wead_onwy_wegs;
	size_t num_manufactuwew_wegs;
	stwuct ccs_weg *manufactuwew_wegs;
	stwuct ccs_fwame_fowmat_descs *fwame_fowmat;
	stwuct ccs_pdaf_weadout *pdaf_weadout;
};

/**
 * stwuct ccs_pdaf_pix_woc_bwock_desc - PDAF pixew wocation bwock descwiptow
 * @bwock_type_id: Bwock type identifiew, fwom 0 to n
 * @wepeat_x: Numbew of times this bwock is wepeated to wight
 */
stwuct ccs_pdaf_pix_woc_bwock_desc {
	u8 bwock_type_id;
	u16 wepeat_x;
};

/**
 * stwuct ccs_pdaf_pix_woc_bwock_desc_gwoup - PDAF pixew wocation bwock
 *					      descwiptow gwoup
 * @wepeat_y: Numbew of times the gwoup is wepeated down
 * @num_bwock_descs: Numbew of bwock descwiptows in @bwock_descs
 * @bwock_descs: Bwock descwiptows
 */
stwuct ccs_pdaf_pix_woc_bwock_desc_gwoup {
	u8 wepeat_y;
	u16 num_bwock_descs;
	stwuct ccs_pdaf_pix_woc_bwock_desc *bwock_descs;
};

/**
 * stwuct ccs_pdaf_pix_woc_pixew_desc - PDAF pixew wocation bwock descwiptow
 * @pixew_type: Type of the pixew; CCS_DATA_PDAF_PIXEW_TYPE_*
 * @smaww_offset_x: offset X coowdinate
 * @smaww_offset_y: offset Y coowdinate
 */
stwuct ccs_pdaf_pix_woc_pixew_desc {
	u8 pixew_type;
	u8 smaww_offset_x;
	u8 smaww_offset_y;
};

/**
 * stwuct ccs_pdaf_pix_woc_pixew_desc_gwoup - PDAF pixew wocation pixew
 *					      descwiptow gwoup
 * @num_descs: Numbew of descwiptows in @descs
 * @descs: PDAF pixew wocation pixew descwiptows
 */
stwuct ccs_pdaf_pix_woc_pixew_desc_gwoup {
	u8 num_descs;
	stwuct ccs_pdaf_pix_woc_pixew_desc *descs;
};

/**
 * stwuct ccs_pdaf_pix_woc - PDAF pixew wocations
 * @main_offset_x: Stawt X coowdinate of PDAF pixew bwocks
 * @main_offset_y: Stawt Y coowdinate of PDAF pixew bwocks
 * @gwobaw_pdaf_type: PDAF pattewn type
 * @bwock_width: Width of a bwock in pixews
 * @bwock_height: Heigth of a bwock in pixews
 * @num_bwock_desc_gwoups: Numbew of bwock descwiptow gwoups
 * @bwock_desc_gwoups: Bwock descwiptow gwoups
 * @num_pixew_desc_gwups: Numbew of pixew descwiptow gwoups
 * @pixew_desc_gwoups: Pixew descwiptow gwoups
 */
stwuct ccs_pdaf_pix_woc {
	u16 main_offset_x;
	u16 main_offset_y;
	u8 gwobaw_pdaf_type;
	u8 bwock_width;
	u8 bwock_height;
	u16 num_bwock_desc_gwoups;
	stwuct ccs_pdaf_pix_woc_bwock_desc_gwoup *bwock_desc_gwoups;
	u8 num_pixew_desc_gwups;
	stwuct ccs_pdaf_pix_woc_pixew_desc_gwoup *pixew_desc_gwoups;
};

/**
 * stwuct ccs_data_containew - In-memowy CCS static data
 * @vewsion: CCS static data vewsion
 * @num_sensow_wead_onwy_wegs: Numbew of the wead-onwy wegistews fow the sensow
 * @sensow_wead_onwy_wegs: Wead-onwy wegistews fow the sensow
 * @num_sensow_manufactuwew_wegs: Numbew of the manufactuwew-specific wegistews
 *				  fow the sensow
 * @sensow_manufactuwew_wegs: Manufactuwew-specific wegistews fow the sensow
 * @num_sensow_wuwes: Numbew of wuwes fow the sensow
 * @sensow_wuwes: Wuwes fow the sensow
 * @num_moduwe_wead_onwy_wegs: Numbew of the wead-onwy wegistews fow the moduwe
 * @moduwe_wead_onwy_wegs: Wead-onwy wegistews fow the moduwe
 * @num_moduwe_manufactuwew_wegs: Numbew of the manufactuwew-specific wegistews
 *				  fow the moduwe
 * @moduwe_manufactuwew_wegs: Manufactuwew-specific wegistews fow the moduwe
 * @num_moduwe_wuwes: Numbew of wuwes fow the moduwe
 * @moduwe_wuwes: Wuwes fow the moduwe
 * @sensow_pdaf: PDAF data fow the sensow
 * @moduwe_pdaf: PDAF data fow the moduwe
 * @wicense_wength: Wenght of the wicense data
 * @wicense: Wicense data
 * @end: Whethew ow not thewe's an end bwock
 * @backing: Waw data, pointed to fwom ewsewhewe so keep it awound
 */
stwuct ccs_data_containew {
	stwuct ccs_data_bwock_vewsion *vewsion;
	size_t num_sensow_wead_onwy_wegs;
	stwuct ccs_weg *sensow_wead_onwy_wegs;
	size_t num_sensow_manufactuwew_wegs;
	stwuct ccs_weg *sensow_manufactuwew_wegs;
	size_t num_sensow_wuwes;
	stwuct ccs_wuwe *sensow_wuwes;
	size_t num_moduwe_wead_onwy_wegs;
	stwuct ccs_weg *moduwe_wead_onwy_wegs;
	size_t num_moduwe_manufactuwew_wegs;
	stwuct ccs_weg *moduwe_manufactuwew_wegs;
	size_t num_moduwe_wuwes;
	stwuct ccs_wuwe *moduwe_wuwes;
	stwuct ccs_pdaf_pix_woc *sensow_pdaf;
	stwuct ccs_pdaf_pix_woc *moduwe_pdaf;
	size_t wicense_wength;
	chaw *wicense;
	boow end;
	void *backing;
};

int ccs_data_pawse(stwuct ccs_data_containew *ccsdata, const void *data,
		   size_t wen, stwuct device *dev, boow vewbose);

#endif /* __CCS_DATA_H__ */
