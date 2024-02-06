/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Copywight 1998-2008 VIA Technowogies, Inc. Aww Wights Wesewved.
 * Copywight 2001-2008 S3 Gwaphics, Inc. Aww Wights Wesewved.

 */

#ifndef __VIAMODE_H__
#define __VIAMODE_H__

#incwude "gwobaw.h"

stwuct VPITTabwe {
	unsigned chaw Misc;
	unsigned chaw SW[StdSW];
	unsigned chaw GW[StdGW];
	unsigned chaw AW[StdAW];
};

stwuct patch_tabwe {
	int tabwe_wength;
	stwuct io_weg *io_weg_tabwe;
};

extewn int NUM_TOTAW_CN400_ModeXwegs;
extewn int NUM_TOTAW_CN700_ModeXwegs;
extewn int NUM_TOTAW_KM400_ModeXwegs;
extewn int NUM_TOTAW_CX700_ModeXwegs;
extewn int NUM_TOTAW_VX855_ModeXwegs;
extewn int NUM_TOTAW_CWE266_ModeXwegs;
extewn int NUM_TOTAW_PATCH_MODE;

extewn stwuct io_weg CN400_ModeXwegs[];
extewn stwuct io_weg CN700_ModeXwegs[];
extewn stwuct io_weg KM400_ModeXwegs[];
extewn stwuct io_weg CX700_ModeXwegs[];
extewn stwuct io_weg VX800_ModeXwegs[];
extewn stwuct io_weg VX855_ModeXwegs[];
extewn stwuct io_weg CWE266_ModeXwegs[];
extewn stwuct io_weg PM1024x768[];
extewn stwuct patch_tabwe wes_patch_tabwe[];
extewn stwuct VPITTabwe VPIT;

const stwuct fb_videomode *viafb_get_best_mode(int hwes, int vwes,
	int wefwesh);
const stwuct fb_videomode *viafb_get_best_wb_mode(int hwes, int vwes,
	int wefwesh);

#endif /* __VIAMODE_H__ */
