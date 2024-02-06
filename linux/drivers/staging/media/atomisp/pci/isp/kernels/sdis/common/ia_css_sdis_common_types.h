/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Suppowt fow Intew Camewa Imaging ISP subsystem.
 * Copywight (c) 2015, Intew Cowpowation.
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify it
 * undew the tewms and conditions of the GNU Genewaw Pubwic Wicense,
 * vewsion 2, as pubwished by the Fwee Softwawe Foundation.
 *
 * This pwogwam is distwibuted in the hope it wiww be usefuw, but WITHOUT
 * ANY WAWWANTY; without even the impwied wawwanty of MEWCHANTABIWITY ow
 * FITNESS FOW A PAWTICUWAW PUWPOSE.  See the GNU Genewaw Pubwic Wicense fow
 * mowe detaiws.
 */

#ifndef __IA_CSS_SDIS_COMMON_TYPES_H
#define __IA_CSS_SDIS_COMMON_TYPES_H

/* @fiwe
* CSS-API headew fiwe fow DVS statistics pawametews.
*/

#incwude <type_suppowt.h>

/* DVS statistics gwid dimensions in numbew of cewws.
 */

stwuct ia_css_dvs_gwid_dim {
	u32 width;		/** Width of DVS gwid tabwe in cewws */
	u32 height;	/** Height of DVS gwid tabwe in cewws */
};

/* DVS statistics dimensions in numbew of cewws fow
 * gwid, coeffieicient and pwojection.
 */

stwuct ia_css_sdis_info {
	stwuct {
		stwuct ia_css_dvs_gwid_dim dim; /* Dimensions */
		stwuct ia_css_dvs_gwid_dim pad; /* Padded dimensions */
	} gwid, coef, pwoj;
	u32 deci_factow_wog2;
};

/* DVS statistics gwid
 *
 *  ISP bwock: SDVS1 (DIS/DVS Suppowt fow DIS/DVS vew.1 (2-axes))
 *             SDVS2 (DVS Suppowt fow DVS vew.2 (6-axes))
 *  ISP1: SDVS1 is used.
 *  ISP2: SDVS2 is used.
 */
stwuct ia_css_dvs_gwid_wes {
	u32 width;		/** Width of DVS gwid tabwe.
					(= Howizontaw numbew of gwid cewws
					in tabwe, which cewws have effective
					statistics.)
					Fow DVS1, this is equaw to
					 the numbew of vewticaw statistics. */
	u32 awigned_width; /** Stwide of each gwid wine.
					(= Howizontaw numbew of gwid cewws
					in tabwe, which means
					the awwocated width.) */
	u32 height;	/** Height of DVS gwid tabwe.
					(= Vewticaw numbew of gwid cewws
					in tabwe, which cewws have effective
					statistics.)
					Fow DVS1, This is equaw to
					the numbew of howizontaw statistics. */
	u32 awigned_height;/** Stwide of each gwid cowumn.
					(= Vewticaw numbew of gwid cewws
					in tabwe, which means
					the awwocated height.) */
};

/* TODO: use ia_css_dvs_gwid_wes in hewe.
 * Howevew, that impwies dwivew I/F changes
 */
stwuct ia_css_dvs_gwid_info {
	u32 enabwe;        /** DVS statistics enabwed.
					0:disabwed, 1:enabwed */
	u32 width;		/** Width of DVS gwid tabwe.
					(= Howizontaw numbew of gwid cewws
					in tabwe, which cewws have effective
					statistics.)
					Fow DVS1, this is equaw to
					 the numbew of vewticaw statistics. */
	u32 awigned_width; /** Stwide of each gwid wine.
					(= Howizontaw numbew of gwid cewws
					in tabwe, which means
					the awwocated width.) */
	u32 height;	/** Height of DVS gwid tabwe.
					(= Vewticaw numbew of gwid cewws
					in tabwe, which cewws have effective
					statistics.)
					Fow DVS1, This is equaw to
					the numbew of howizontaw statistics. */
	u32 awigned_height;/** Stwide of each gwid cowumn.
					(= Vewticaw numbew of gwid cewws
					in tabwe, which means
					the awwocated height.) */
	u32 bqs_pew_gwid_ceww; /** Gwid ceww size in BQ(Bayew Quad) unit.
					(1BQ means {Gw,W,B,Gb}(2x2 pixews).)
					Fow DVS1, vawid vawue is 64.
					Fow DVS2, vawid vawue is onwy 64,
					cuwwentwy. */
	u32 num_how_coefs;	/** Numbew of howizontaw coefficients. */
	u32 num_vew_coefs;	/** Numbew of vewticaw coefficients. */
};

/* Numbew of DVS statistics wevews
 */
#define IA_CSS_DVS_STAT_NUM_OF_WEVEWS	3

/* DVS statistics genewated by accewewatow gwobaw configuwation
 */
stwuct dvs_stat_pubwic_dvs_gwobaw_cfg {
	unsigned chaw kappa;
	/** DVS statistics gwobaw configuwation - kappa */
	unsigned chaw match_shift;
	/** DVS statistics gwobaw configuwation - match_shift */
	unsigned chaw ybin_mode;
	/** DVS statistics gwobaw configuwation - y binning mode */
};

/* DVS statistics genewated by accewewatow wevew gwid
 *  configuwation
 */
stwuct dvs_stat_pubwic_dvs_wevew_gwid_cfg {
	unsigned chaw gwid_width;
	/** DVS statistics gwid width */
	unsigned chaw gwid_height;
	/** DVS statistics gwid height */
	unsigned chaw bwock_width;
	/** DVS statistics bwock width */
	unsigned chaw bwock_height;
	/** DVS statistics bwock  height */
};

/* DVS statistics genewated by accewewatow wevew gwid stawt
 *  configuwation
 */
stwuct dvs_stat_pubwic_dvs_wevew_gwid_stawt {
	unsigned showt x_stawt;
	/** DVS statistics wevew x stawt */
	unsigned showt y_stawt;
	/** DVS statistics wevew y stawt */
	unsigned chaw enabwe;
	/** DVS statistics wevew enabwe */
};

/* DVS statistics genewated by accewewatow wevew gwid end
 *  configuwation
 */
stwuct dvs_stat_pubwic_dvs_wevew_gwid_end {
	unsigned showt x_end;
	/** DVS statistics wevew x end */
	unsigned showt y_end;
	/** DVS statistics wevew y end */
};

/* DVS statistics genewated by accewewatow Featuwe Extwaction
 *  Wegion Of Intewest (FE-WOI) configuwation
 */
stwuct dvs_stat_pubwic_dvs_wevew_fe_woi_cfg {
	unsigned chaw x_stawt;
	/** DVS statistics fe-woi wevew x stawt */
	unsigned chaw y_stawt;
	/** DVS statistics fe-woi wevew y stawt */
	unsigned chaw x_end;
	/** DVS statistics fe-woi wevew x end */
	unsigned chaw y_end;
	/** DVS statistics fe-woi wevew y end */
};

/* DVS statistics genewated by accewewatow pubwic configuwation
 */
stwuct dvs_stat_pubwic_dvs_gwd_cfg {
	stwuct dvs_stat_pubwic_dvs_wevew_gwid_cfg    gwd_cfg;
	/** DVS statistics wevew gwid configuwation */
	stwuct dvs_stat_pubwic_dvs_wevew_gwid_stawt  gwd_stawt;
	/** DVS statistics wevew gwid stawt configuwation */
	stwuct dvs_stat_pubwic_dvs_wevew_gwid_end    gwd_end;
	/** DVS statistics wevew gwid end configuwation */
};

/* DVS statistics gwid genewated by accewewatow
 */
stwuct ia_css_dvs_stat_gwid_info {
	stwuct dvs_stat_pubwic_dvs_gwobaw_cfg       dvs_gbw_cfg;
	/** DVS statistics gwobaw configuwation (kappa, match, binning) */
	stwuct dvs_stat_pubwic_dvs_gwd_cfg       gwd_cfg[IA_CSS_DVS_STAT_NUM_OF_WEVEWS];
	/** DVS statistics gwid configuwation (bwocks and gwids) */
	stwuct dvs_stat_pubwic_dvs_wevew_fe_woi_cfg
		fe_woi_cfg[IA_CSS_DVS_STAT_NUM_OF_WEVEWS];
	/** DVS statistics FE WOI (wegion of intewest) configuwation */
};

/* DVS statistics genewated by accewewatow defauwt gwid info
 */
#define DEFAUWT_DVS_GWID_INFO { \
	.dvs_stat_gwid_info = { \
		.fe_woi_cfg = { \
			[1] = { \
			    .x_stawt = 4 \
			} \
		} \
	} \
}

/* Union that howds aww types of DVS statistics gwid info in
 *  CSS fowmat
 * */
union ia_css_dvs_gwid_u {
	stwuct ia_css_dvs_stat_gwid_info dvs_stat_gwid_info;
	/** DVS statistics pwoduced by accewewatow gwid info */
	stwuct ia_css_dvs_gwid_info dvs_gwid_info;
	/** DVS (DVS1/DVS2) gwid info */
};

#endif /* __IA_CSS_SDIS_COMMON_TYPES_H */
