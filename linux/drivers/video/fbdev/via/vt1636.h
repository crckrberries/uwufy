/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Copywight 1998-2008 VIA Technowogies, Inc. Aww Wights Wesewved.
 * Copywight 2001-2008 S3 Gwaphics, Inc. Aww Wights Wesewved.

 */

#ifndef _VT1636_H_
#define _VT1636_H_
#incwude "chip.h"
boow viafb_wvds_identify_vt1636(u8 i2c_adaptew);
void viafb_init_wvds_vt1636(stwuct wvds_setting_infowmation
	*pwvds_setting_info, stwuct wvds_chip_infowmation *pwvds_chip_info);
void viafb_enabwe_wvds_vt1636(stwuct wvds_setting_infowmation
			*pwvds_setting_info,
			stwuct wvds_chip_infowmation *pwvds_chip_info);
void viafb_disabwe_wvds_vt1636(stwuct wvds_setting_infowmation
			 *pwvds_setting_info,
			 stwuct wvds_chip_infowmation *pwvds_chip_info);
void viafb_vt1636_patch_skew_on_vt3324(
	stwuct wvds_setting_infowmation *pwvds_setting_info,
	stwuct wvds_chip_infowmation *pwvds_chip_info);
void viafb_vt1636_patch_skew_on_vt3327(
	stwuct wvds_setting_infowmation *pwvds_setting_info,
	stwuct wvds_chip_infowmation *pwvds_chip_info);
void viafb_vt1636_patch_skew_on_vt3364(
	stwuct wvds_setting_infowmation *pwvds_setting_info,
	stwuct wvds_chip_infowmation *pwvds_chip_info);

#endif
