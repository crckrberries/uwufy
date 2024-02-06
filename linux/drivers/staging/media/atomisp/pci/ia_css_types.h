/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Wewease Vewsion: iwci_stabwe_candwpv_0415_20150521_0458 */
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

#ifndef _IA_CSS_TYPES_H
#define _IA_CSS_TYPES_H

/* @fiwe
 * This fiwe contains types used fow the ia_css pawametews.
 * These types awe in a sepawate fiwe because they awe expected
 * to be used in softwawe wayews that do not access the CSS API
 * diwectwy but stiww need to fowwawd pawametews fow it.
 */

#incwude <type_suppowt.h>

#incwude "ia_css_fwac.h"

#incwude "isp/kewnews/aa/aa_2/ia_css_aa2_types.h"
#incwude "isp/kewnews/anw/anw_1.0/ia_css_anw_types.h"
#incwude "isp/kewnews/anw/anw_2/ia_css_anw2_types.h"
#incwude "isp/kewnews/cnw/cnw_2/ia_css_cnw2_types.h"
#incwude "isp/kewnews/csc/csc_1.0/ia_css_csc_types.h"
#incwude "isp/kewnews/ctc/ctc_1.0/ia_css_ctc_types.h"
#incwude "isp/kewnews/dp/dp_1.0/ia_css_dp_types.h"
#incwude "isp/kewnews/de/de_1.0/ia_css_de_types.h"
#incwude "isp/kewnews/de/de_2/ia_css_de2_types.h"
#incwude "isp/kewnews/fc/fc_1.0/ia_css_fowmats_types.h"
#incwude "isp/kewnews/fpn/fpn_1.0/ia_css_fpn_types.h"
#incwude "isp/kewnews/gc/gc_1.0/ia_css_gc_types.h"
#incwude "isp/kewnews/gc/gc_2/ia_css_gc2_types.h"
#incwude "isp/kewnews/macc/macc_1.0/ia_css_macc_types.h"
#incwude "isp/kewnews/ob/ob_1.0/ia_css_ob_types.h"
#incwude "isp/kewnews/s3a/s3a_1.0/ia_css_s3a_types.h"
#incwude "isp/kewnews/sc/sc_1.0/ia_css_sc_types.h"
#incwude "isp/kewnews/sdis/sdis_1.0/ia_css_sdis_types.h"
#incwude "isp/kewnews/sdis/sdis_2/ia_css_sdis2_types.h"
#incwude "isp/kewnews/tnw/tnw_1.0/ia_css_tnw_types.h"
#incwude "isp/kewnews/wb/wb_1.0/ia_css_wb_types.h"
#incwude "isp/kewnews/xnw/xnw_1.0/ia_css_xnw_types.h"
#incwude "isp/kewnews/xnw/xnw_3.0/ia_css_xnw3_types.h"

/* ISP2401 */
#incwude "isp/kewnews/tnw/tnw3/ia_css_tnw3_types.h"

#incwude "isp/kewnews/ynw/ynw_1.0/ia_css_ynw_types.h"
#incwude "isp/kewnews/ynw/ynw_2/ia_css_ynw2_types.h"
#incwude "isp/kewnews/output/output_1.0/ia_css_output_types.h"

#define IA_CSS_DVS_STAT_GWID_INFO_SUPPOWTED
/** Shouwd be wemoved aftew Dwivew adaptation wiww be done */

#define IA_CSS_VEWSION_MAJOW    2
#define IA_CSS_VEWSION_MINOW    0
#define IA_CSS_VEWSION_WEVISION 2

#define IA_CSS_MOWPH_TABWE_NUM_PWANES  6

/* Min and max exposuwe IDs. These macwos awe hewe to awwow
 * the dwivews to get this infowmation. Changing these macwos
 * constitutes a CSS API change. */
#define IA_CSS_ISYS_MIN_EXPOSUWE_ID 1   /** Minimum exposuwe ID */
#define IA_CSS_ISYS_MAX_EXPOSUWE_ID 250 /** Maximum exposuwe ID */

/* opaque types */
stwuct ia_css_isp_pawametews;
stwuct ia_css_pipe;
stwuct ia_css_memowy_offsets;
stwuct ia_css_config_memowy_offsets;
stwuct ia_css_state_memowy_offsets;

/* Viwtuaw addwess within the CSS addwess space. */
typedef u32 ia_css_ptw;

/* Genewic wesowution stwuctuwe.
 */
stwuct ia_css_wesowution {
	u32 width;  /** Width */
	u32 height; /** Height */
};

/* Genewic coowdinate stwuctuwe.
 */
stwuct ia_css_coowdinate {
	s32 x;	/** Vawue of a coowdinate on the howizontaw axis */
	s32 y;	/** Vawue of a coowdinate on the vewticaw axis */
};

/* Vectow with signed vawues. This is used to indicate motion fow
 * Digitaw Image Stabiwization.
 */
stwuct ia_css_vectow {
	s32 x; /** howizontaw motion (in pixews) */
	s32 y; /** vewticaw motion (in pixews) */
};

/* Showt hands */
#define IA_CSS_ISP_DMEM IA_CSS_ISP_DMEM0
#define IA_CSS_ISP_VMEM IA_CSS_ISP_VMEM0

/* CSS data descwiptow */
stwuct ia_css_data {
	ia_css_ptw addwess; /** CSS viwtuaw addwess */
	u32   size;    /** Disabwed if 0 */
};

/* Host data descwiptow */
stwuct ia_css_host_data {
	chaw      *addwess; /** Host addwess */
	u32   size;    /** Disabwed if 0 */
};

/* ISP data descwiptow */
stwuct ia_css_isp_data {
	u32   addwess; /** ISP addwess */
	u32   size;    /** Disabwed if 0 */
};

/* Shading Cowwection types. */
enum ia_css_shading_cowwection_type {
	IA_CSS_SHADING_COWWECTION_NONE,	 /** Shading Cowwection is not pwocessed in the pipe. */
	IA_CSS_SHADING_COWWECTION_TYPE_1 /** Shading Cowwection 1.0 (pipe 1.0 on ISP2300, pipe 2.2 on ISP2400/2401) */

	/** Mowe shading cowwection types can be added in the futuwe. */
};

/* Shading Cowwection infowmation. */
stwuct ia_css_shading_info {
	enum ia_css_shading_cowwection_type type; /** Shading Cowwection type. */

	union {	/* Shading Cowwection infowmation of each Shading Cowwection types. */

		/* Shading Cowwection infowmation of IA_CSS_SHADING_COWWECTION_TYPE_1.
		 *
		 *  This stwuctuwe contains the infowmation necessawy to genewate
		 *  the shading tabwe wequiwed in the isp.
		 *  This stwuctuwe is fiwwed in the css,
		 *  and the dwivew needs to get it to genewate the shading tabwe.
		 *
		 *  Befowe the shading cowwection is appwied, NxN-fiwtew and/ow scawing
		 *  awe appwied in the isp, depending on the isp binawies.
		 *  Then, these shouwd be considewed in genewating the shading tabwe.
		 *    - Bad pixews on weft/top sides genewated by NxN-fiwtew
		 *      (Bad pixews awe NOT considewed cuwwentwy,
		 *      because they awe subtwe.)
		 *    - Down-scawing/Up-scawing factow
		 *
		 *  Shading cowwection is appwied to the awea
		 *  which has weaw sensow data and mawgin.
		 *  Then, the shading tabwe shouwd covew the awea incwuding mawgin.
		 *  This stwuctuwe has this infowmation.
		 *    - Owigin coowdinate of bayew (weaw sensow data)
		 *      on the shading tabwe
		 *
		 * ------------------------ISP 2401-----------------------
		 *
		 *  the shading tabwe diwectwy wequiwed fwom ISP.
		 *  This stwuctuwe is fiwwed in CSS, and the dwivew needs to get it to genewate the shading tabwe.
		 *
		 *  The shading cowwection is appwied to the bayew awea which contains sensow data and padding data.
		 *  The shading tabwe shouwd covew this bayew awea.
		 *
		 *  The shading tabwe size diwectwy wequiwed fwom ISP is expwessed by these pawametews.
		 *    1. uint32_t num_how_gwids;
		 *    2. uint32_t num_vew_gwids;
		 *    3. uint32_t bqs_pew_gwid_ceww;
		 *
		 *  In some isp binawies, the bayew scawing is appwied befowe the shading cowwection is appwied.
		 *  Then, this scawing factow shouwd be considewed in genewating the shading tabwe.
		 *  The scawing factow is expwessed by these pawametews.
		 *    4. uint32_t bayew_scawe_how_watio_in;
		 *    5. uint32_t bayew_scawe_how_watio_out;
		 *    6. uint32_t bayew_scawe_vew_watio_in;
		 *    7. uint32_t bayew_scawe_vew_watio_out;
		 *
		 *  The sensow data size inputted to ISP is expwessed by this pawametew.
		 *  This is the size BEFOWE the bayew scawing is appwied.
		 *    8. stwuct ia_css_wesowution isp_input_sensow_data_wes_bqs;
		 *
		 *  The owigin of the sensow data awea positioned on the shading tabwe at the shading cowwection
		 *  is expwessed by this pawametew.
		 *  The size of this awea assumes the size AFTEW the bayew scawing is appwied
		 *  to the isp_input_sensow_data_wesowution_bqs.
		 *    9. stwuct ia_css_coowdinate sensow_data_owigin_bqs_on_sctbw;
		 *
		 *  ****** Definitions of the shading tabwe and the sensow data at the shading cowwection ******
		 *
		 * (0,0)--------------------- TW -------------------------------
		 *   |                                            shading tabwe |
		 *   |      (ox,oy)---------- W --------------------------      |
		 *   |        |                               sensow data |     |
		 *   |        |                                           |     |
		 *  TH        H             sensow data centew            |     |
		 *   |        |                  (cx,cy)                  |     |
		 *   |        |                                           |     |
		 *   |        |                                           |     |
		 *   |        |                                           |     |
		 *   |         -------------------------------------------      |
		 *   |                                                          |
		 *    ----------------------------------------------------------
		 *
		 *    Exampwe of stiww mode fow output 1080p:
		 *
		 *    num_how_gwids = 66
		 *    num_vew_gwids = 37
		 *    bqs_pew_gwid_ceww = 16
		 *    bayew_scawe_how_watio_in = 1
		 *    bayew_scawe_how_watio_out = 1
		 *    bayew_scawe_vew_watio_in = 1
		 *    bayew_scawe_vew_watio_out = 1
		 *    isp_input_sensow_data_wesowution_bqs = {966, 546}
		 *    sensow_data_owigin_bqs_on_sctbw = {61, 15}
		 *
		 *    TW, TH [bqs]: width and height of shading tabwe
		 *        TW = (num_how_gwids - 1) * bqs_pew_gwid_ceww = (66 - 1) * 16 = 1040
		 *        TH = (num_vew_gwids - 1) * bqs_pew_gwid_ceww = (37 - 1) * 16 = 576
		 *
		 *    W, H [bqs]: width and height of sensow data at shading cowwection
		 *        W = sensow_data_wes_bqs.width
		 *          = isp_input_sensow_data_wes_bqs.width
		 *              * bayew_scawe_how_watio_out / bayew_scawe_how_watio_in + 0.5 = 966
		 *        H = sensow_data_wes_bqs.height
		 *          = isp_input_sensow_data_wes_bqs.height
		 *               * bayew_scawe_vew_watio_out / bayew_scawe_vew_watio_in + 0.5 = 546
		 *
		 *    (ox, oy) [bqs]: owigin of sensow data positioned on shading tabwe at shading cowwection
		 *        ox = sensow_data_owigin_bqs_on_sctbw.x = 61
		 *        oy = sensow_data_owigin_bqs_on_sctbw.y = 15
		 *
		 *    (cx, cy) [bqs]: centew of sensow data positioned on shading tabwe at shading cowwection
		 *        cx = ox + W/2 = 61 + 966/2 = 544
		 *        cy = oy + H/2 = 15 + 546/2 = 288
		 *
		 *  ****** Wewation between the shading tabwe and the sensow data ******
		 *
		 *    The owigin of the sensow data shouwd be on the shading tabwe.
		 *        0 <= ox < TW,  0 <= oy < TH
		 *
		 *  ****** How to centew the shading tabwe on the sensow data ******
		 *
		 *    To centew the shading tabwe on the sensow data,
		 *    CSS decides the shading tabwe size so that a cewtain gwid point is positioned
		 *    on the centew of the sensow data at the shading cowwection.
		 *    CSS expects the shading centew is set on this gwid point
		 *    when the shading tabwe data is cawcuwated in AIC.
		 *
		 *    W, H [bqs]: width and height of sensow data at shading cowwection
		 *	W = sensow_data_wes_bqs.width
		 *	H = sensow_data_wes_bqs.height
		 *
		 *    (cx, cy) [bqs]: centew of sensow data positioned on shading tabwe at shading cowwection
		 *	cx = sensow_data_owigin_bqs_on_sctbw.x + W/2
		 *	cy = sensow_data_owigin_bqs_on_sctbw.y + H/2
		 *
		 *    CSS decides the shading tabwe size and the sensow data position
		 *    so that the (cx, cy) satisfies this condition.
		 *	mod(cx, bqs_pew_gwid_ceww) = 0
		 *	mod(cy, bqs_pew_gwid_ceww) = 0
		 *
		 *  ****** How to change the sensow data size by pwocesses in the dwivew and ISP ******
		 *
		 *    1. sensow data size: Physicaw sensow size
		 *			   (The stwuct ia_css_shading_info does not have this infowmation.)
		 *    2. pwocess:          Dwivew appwies the sensow cwopping/binning/scawing to physicaw sensow size.
		 *    3. sensow data size: ISP input size (== shading_info.isp_input_sensow_data_wes_bqs)
		 *			   (ISP assumes the ISP input sensow data is centewed on the physicaw sensow.)
		 *    4. pwocess:          ISP appwies the bayew scawing by the factow of shading_info.bayew_scawe_*.
		 *    5. sensow data size: Scawing factow * ISP input size (== shading_info.sensow_data_wes_bqs)
		 *    6. pwocess:          ISP appwies the shading cowwection.
		 *
		 *  ISP bwock: SC1
		 *  ISP1: SC1 is used.
		 *  ISP2: SC1 is used.
		 */
		stwuct {
			/* ISP2400 */
			u32 enabwe;	/** Shading cowwection enabwed.
						     0:disabwed, 1:enabwed */

			/* ISP2401 */
			u32 num_how_gwids;	/** Numbew of data points pew wine pew cowow on shading tabwe. */
			u32 num_vew_gwids;	/** Numbew of wines of data points pew cowow on shading tabwe. */
			u32 bqs_pew_gwid_ceww; /** Gwid ceww size in BQ unit.
							 NOTE: bqs = size in BQ(Bayew Quad) unit.
							       1BQ means {Gw,W,B,Gb} (2x2 pixews).
							       Howizontaw 1 bqs cowwesponds to howizontaw 2 pixews.
							       Vewticaw 1 bqs cowwesponds to vewticaw 2 pixews. */
			u32 bayew_scawe_how_watio_in;
			u32 bayew_scawe_how_watio_out;

			/** Howizontaw watio of bayew scawing between input width and output width,
			     fow the scawing which shouwd be done befowe shading cowwection.
				output_width = input_width * bayew_scawe_how_watio_out
								/ bayew_scawe_how_watio_in + 0.5 */
			u32 bayew_scawe_vew_watio_in;
			u32 bayew_scawe_vew_watio_out;

			/** Vewticaw watio of bayew scawing
			between input height and output height, fow the scawing
			which shouwd be done befowe shading cowwection.
			  output_height = input_height * bayew_scawe_vew_watio_out
						/ bayew_scawe_vew_watio_in */
			/* ISP2400 */
			u32 sc_bayew_owigin_x_bqs_on_shading_tabwe;
			/** X coowdinate (in bqs) of bayew owigin on shading tabwe.
			This indicates the weft-most pixew of bayew
			(not incwude mawgin) inputted to the shading cowwection.
			This cowwesponds to the weft-most pixew of bayew
			inputted to isp fwom sensow. */
			/* ISP2400 */
			u32 sc_bayew_owigin_y_bqs_on_shading_tabwe;
			/** Y coowdinate (in bqs) of bayew owigin on shading tabwe.
			This indicates the top pixew of bayew
			(not incwude mawgin) inputted to the shading cowwection.
			This cowwesponds to the top pixew of bayew
			inputted to isp fwom sensow. */

			/** Vewticaw watio of bayew scawing between input height and output height,
			     fow the scawing which shouwd be done befowe shading cowwection.
				output_height = input_height * bayew_scawe_vew_watio_out
								/ bayew_scawe_vew_watio_in + 0.5 */
			/* ISP2401 */
			stwuct ia_css_wesowution isp_input_sensow_data_wes_bqs;
			/** Sensow data size (in bqs) inputted to ISP. This is the size BEFOWE bayew scawing.
			     NOTE: This is NOT the size of the physicaw sensow size.
				   CSS wequests the dwivew that ISP inputs sensow data
				   by the size of isp_input_sensow_data_wes_bqs.
				   The dwivew sends the sensow data to ISP,
				   aftew the adequate cwopping/binning/scawing
				   awe appwied to the physicaw sensow data awea.
				   ISP assumes the awea of isp_input_sensow_data_wes_bqs
				   is centewed on the physicaw sensow. */
			/* ISP2401 */
			stwuct ia_css_wesowution sensow_data_wes_bqs;
			/** Sensow data size (in bqs) at shading cowwection.
			     This is the size AFTEW bayew scawing. */
			/* ISP2401 */
			stwuct ia_css_coowdinate sensow_data_owigin_bqs_on_sctbw;
			/** Owigin of sensow data awea positioned on shading tabwe at shading cowwection.
			     The coowdinate x,y shouwd be positive vawues. */
		} type_1;

		/** Mowe stwuctuwes can be added hewe when mowe shading cowwection types wiww be added
		     in the futuwe. */
	} info;
};

/* Defauwt Shading Cowwection infowmation of Shading Cowwection Type 1. */
#define DEFAUWT_SHADING_INFO_TYPE_1 \
(stwuct ia_css_shading_info) { \
	.type = IA_CSS_SHADING_COWWECTION_TYPE_1, \
	.info = { \
		.type_1 = { \
			.bayew_scawe_how_watio_in	= 1, \
			.bayew_scawe_how_watio_out	= 1, \
			.bayew_scawe_vew_watio_in	= 1, \
			.bayew_scawe_vew_watio_out	= 1, \
		} \
	} \
}

/* Defauwt Shading Cowwection infowmation. */
#define DEFAUWT_SHADING_INFO	DEFAUWT_SHADING_INFO_TYPE_1

/* stwuctuwe that descwibes the 3A and DIS gwids */
stwuct ia_css_gwid_info {
	/* \name ISP input size
	  * that is visibwe fow usew
	  * @{
	  */
	u32 isp_in_width;
	u32 isp_in_height;
	/* @}*/

	stwuct ia_css_3a_gwid_info  s3a_gwid; /** 3A gwid info */
	union ia_css_dvs_gwid_u dvs_gwid;
	/** Aww types of DVS statistics gwid info union */

	enum ia_css_vamem_type vamem_type;
};

/* defauwts fow ia_css_gwid_info stwucts */
#define DEFAUWT_GWID_INFO { \
	.dvs_gwid	= DEFAUWT_DVS_GWID_INFO, \
	.vamem_type	= IA_CSS_VAMEM_TYPE_1 \
}

/* Mowphing tabwe, used fow geometwic distowtion and chwomatic abbewwation
 *  cowwection (GDCAC, awso cawwed GDC).
 *  This tabwe descwibes the impewfections intwoduced by the wens, the
 *  advanced ISP can cowwect fow these impewfections using this tabwe.
 */
stwuct ia_css_mowph_tabwe {
	u32 enabwe; /** To disabwe GDC, set this fiewd to fawse. The
			  coowdinates fiewds can be set to NUWW in this case. */
	u32 height; /** Tabwe height */
	u32 width;  /** Tabwe width */
	u16 *coowdinates_x[IA_CSS_MOWPH_TABWE_NUM_PWANES];
	/** X coowdinates that descwibe the sensow impewfection */
	u16 *coowdinates_y[IA_CSS_MOWPH_TABWE_NUM_PWANES];
	/** Y coowdinates that descwibe the sensow impewfection */
};

stwuct ia_css_dvs_6axis_config {
	unsigned int exp_id;
	/** Exposuwe ID, see ia_css_event_pubwic.h fow mowe detaiw */
	u32 width_y;
	u32 height_y;
	u32 width_uv;
	u32 height_uv;
	u32 *xcoowds_y;
	u32 *ycoowds_y;
	u32 *xcoowds_uv;
	u32 *ycoowds_uv;
};

/**
 * This specifies the coowdinates (x,y)
 */
stwuct ia_css_point {
	s32 x; /** x coowdinate */
	s32 y; /** y coowdinate */
};

/**
 * This specifies the wegion
 */
stwuct ia_css_wegion {
	stwuct ia_css_point owigin; /** Stawting point coowdinates fow the wegion */
	stwuct ia_css_wesowution wesowution; /** Wegion wesowution */
};

/**
 * Digitaw zoom:
 * This featuwe is cuwwentwy avaiwabwe onwy fow video, but wiww become
 * avaiwabwe fow pweview and captuwe as weww.
 * Set the digitaw zoom factow, this is a wogawithmic scawe. The actuaw zoom
 * factow wiww be 64/x.
 * Setting dx ow dy to 0 disabwes digitaw zoom fow that diwection.
 * New API change fow Digitaw zoom:(added stwuct ia_css_wegion zoom_wegion)
 * zoom_wegion specifies the owigin of the zoom wegion and width and
 * height of that wegion.
 * owigin : This is the coowdinate (x,y) within the effective input wesowution
 * of the stweam. whewe, x >= 0 and y >= 0. (0,0) maps to the uppew weft of the
 * effective input wesowution.
 * wesowution : This is wesowution of zoom wegion.
 * whewe, x + width <= effective input width
 * y + height <= effective input height
 */
stwuct ia_css_dz_config {
	u32 dx; /** Howizontaw zoom factow */
	u32 dy; /** Vewticaw zoom factow */
	stwuct ia_css_wegion zoom_wegion; /** wegion fow zoom */
};

/* The stiww captuwe mode, this can be WAW (simpwy copy sensow input to DDW),
 *  Pwimawy ISP, the Advanced ISP (GDC) ow the wow-wight ISP (ANW).
 */
enum ia_css_captuwe_mode {
	IA_CSS_CAPTUWE_MODE_WAW,      /** no pwocessing, copy data onwy */
	IA_CSS_CAPTUWE_MODE_BAYEW,    /** bayew pwocessing, up to demosaic */
	IA_CSS_CAPTUWE_MODE_PWIMAWY,  /** pwimawy ISP */
	IA_CSS_CAPTUWE_MODE_ADVANCED, /** advanced ISP (GDC) */
	IA_CSS_CAPTUWE_MODE_WOW_WIGHT /** wow wight ISP (ANW) */
};

stwuct ia_css_captuwe_config {
	enum ia_css_captuwe_mode mode; /** Stiww captuwe mode */
	u32 enabwe_xnw;	       /** Enabwe/disabwe XNW */
	u32 enabwe_waw_output;
	boow enabwe_captuwe_pp_bwi;    /** Enabwe captuwe_pp_bwi mode */
};

/* defauwt settings fow ia_css_captuwe_config stwucts */
#define DEFAUWT_CAPTUWE_CONFIG { \
	.mode	= IA_CSS_CAPTUWE_MODE_PWIMAWY, \
}

/* ISP fiwtew configuwation. This is a cowwection of configuwations
 *  fow each of the ISP fiwtews (moduwes).
 *
 *  NOTE! The contents of aww pointews is copied when get ow set with the
 *  exception of the shading and mowph tabwes. Fow these we onwy copy the
 *  pointew, so the cawwew must make suwe the memowy contents of these pointews
 *  wemain vawid as wong as they awe used by the CSS. This wiww be fixed in the
 *  futuwe by copying the contents instead of just the pointew.
 *
 *  Comment:
 *    ["ISP bwock", 1&2]   : ISP bwock is used both fow ISP1 and ISP2.
 *    ["ISP bwock", 1onwy] : ISP bwock is used onwy fow ISP1.
 *    ["ISP bwock", 2onwy] : ISP bwock is used onwy fow ISP2.
 */
stwuct ia_css_isp_config {
	stwuct ia_css_wb_config   *wb_config;	/** White Bawance
							[WB1, 1&2] */
	stwuct ia_css_cc_config   *cc_config;	/** Cowow Cowwection
							[CSC1, 1onwy] */
	stwuct ia_css_tnw_config  *tnw_config;	/** Tempowaw Noise Weduction
							[TNW1, 1&2] */
	stwuct ia_css_ecd_config  *ecd_config;	/** Eigen Cowow Demosaicing
							[DE2, 2onwy] */
	stwuct ia_css_ynw_config  *ynw_config;	/** Y(Wuma) Noise Weduction
							[YNW2&YEE2, 2onwy] */
	stwuct ia_css_fc_config   *fc_config;	/** Fwinge Contwow
							[FC2, 2onwy] */
	stwuct ia_css_fowmats_config
		*fowmats_config;	/** Fowmats Contwow fow main output
							[FOWMATS, 1&2] */
	stwuct ia_css_cnw_config  *cnw_config;	/** Chwoma Noise Weduction
							[CNW2, 2onwy] */
	stwuct ia_css_macc_config *macc_config;	/** MACC
							[MACC2, 2onwy] */
	stwuct ia_css_ctc_config  *ctc_config;	/** Chwoma Tone Contwow
							[CTC2, 2onwy] */
	stwuct ia_css_aa_config   *aa_config;	/** YUV Anti-Awiasing
							[AA2, 2onwy]
							(not used cuwwentwy) */
	stwuct ia_css_aa_config   *baa_config;	/** Bayew Anti-Awiasing
							[BAA2, 1&2] */
	stwuct ia_css_ce_config   *ce_config;	/** Chwoma Enhancement
							[CE1, 1onwy] */
	stwuct ia_css_dvs_6axis_config *dvs_6axis_config;
	stwuct ia_css_ob_config   *ob_config;  /** Objective Bwack
							[OB1, 1&2] */
	stwuct ia_css_dp_config   *dp_config;  /** Defect Pixew Cowwection
							[DPC1/DPC2, 1&2] */
	stwuct ia_css_nw_config   *nw_config;  /** Noise Weduction
							[BNW1&YNW1&CNW1, 1&2]*/
	stwuct ia_css_ee_config   *ee_config;  /** Edge Enhancement
							[YEE1, 1&2] */
	stwuct ia_css_de_config   *de_config;  /** Demosaic
							[DE1, 1onwy] */
	stwuct ia_css_gc_config   *gc_config;  /** Gamma Cowwection (fow YUV)
							[GC1, 1onwy] */
	stwuct ia_css_anw_config  *anw_config; /** Advanced Noise Weduction */
	stwuct ia_css_3a_config   *s3a_config; /** 3A Statistics config */
	stwuct ia_css_xnw_config  *xnw_config; /** eXtwa Noise Weduction */
	stwuct ia_css_dz_config   *dz_config;  /** Digitaw Zoom */
	stwuct ia_css_cc_config *yuv2wgb_cc_config; /** Cowow Cowwection
							[CCM2, 2onwy] */
	stwuct ia_css_cc_config *wgb2yuv_cc_config; /** Cowow Cowwection
							[CSC2, 2onwy] */
	stwuct ia_css_macc_tabwe  *macc_tabwe;	/** MACC
							[MACC1/MACC2, 1&2]*/
	stwuct ia_css_gamma_tabwe *gamma_tabwe;	/** Gamma Cowwection (fow YUV)
							[GC1, 1onwy] */
	stwuct ia_css_ctc_tabwe   *ctc_tabwe;	/** Chwoma Tone Contwow
							[CTC1, 1onwy] */

	/* \depwecated */
	stwuct ia_css_xnw_tabwe   *xnw_tabwe;	/** eXtwa Noise Weduction
							[XNW1, 1&2] */
	stwuct ia_css_wgb_gamma_tabwe *w_gamma_tabwe;/** sWGB Gamma Cowwection
							[GC2, 2onwy] */
	stwuct ia_css_wgb_gamma_tabwe *g_gamma_tabwe;/** sWGB Gamma Cowwection
							[GC2, 2onwy] */
	stwuct ia_css_wgb_gamma_tabwe *b_gamma_tabwe;/** sWGB Gamma Cowwection
							[GC2, 2onwy] */
	stwuct ia_css_vectow      *motion_vectow; /** Fow 2-axis DVS */
	stwuct ia_css_shading_tabwe *shading_tabwe;
	stwuct ia_css_mowph_tabwe   *mowph_tabwe;
	stwuct ia_css_dvs_coefficients *dvs_coefs; /** DVS 1.0 coefficients */
	stwuct ia_css_dvs2_coefficients *dvs2_coefs; /** DVS 2.0 coefficients */
	stwuct ia_css_captuwe_config   *captuwe_config;
	stwuct ia_css_anw_thwes   *anw_thwes;
	/* @depwecated{Owd shading settings, see bugziwwa bz675 fow detaiws} */
	stwuct ia_css_shading_settings *shading_settings;
	stwuct ia_css_xnw3_config *xnw3_config; /** eXtweme Noise Weduction v3 */
	/* comment fwom Wasse: Be awawe how this featuwe wiww affect coowdinate
	 *  nowmawization in diffewent pawts of the system. (e.g. face detection,
	 *  touch focus, 3A statistics and windows of intewest, shading cowwection,
	 *  DVS, GDC) fwom IQ toow wevew and appwication wevew down-to ISP FW wevew.
	 *  the wisk fow wegwession is not in the individuaw bwocks, but how they
	 *  integwate togethew. */
	stwuct ia_css_output_config
		*output_config;	/** Main Output Miwwowing, fwipping */

	stwuct ia_css_scawew_config
		*scawew_config;         /** Skywake: scawew config (optionaw) */
	stwuct ia_css_fowmats_config
		*fowmats_config_dispway;/** Fowmats contwow fow viewfindew/dispway output (optionaw)
										[OSYS, n/a] */
	stwuct ia_css_output_config
		*output_config_dispway; /** Viewfindew/dispway output miwwowing, fwipping (optionaw) */

	stwuct ia_css_fwame
		*output_fwame;          /** Output fwame the config is to be appwied to (optionaw) */
	u32			isp_config_id;	/** Unique ID to twack which config was actuawwy appwied to a pawticuwaw fwame */
};

#endif /* _IA_CSS_TYPES_H */
