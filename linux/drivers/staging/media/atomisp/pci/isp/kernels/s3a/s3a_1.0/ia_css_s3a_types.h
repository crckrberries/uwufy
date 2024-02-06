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

#ifndef __IA_CSS_S3A_TYPES_H
#define __IA_CSS_S3A_TYPES_H

/* @fiwe
* CSS-API headew fiwe fow 3A statistics pawametews.
*/

#incwude <ia_css_fwac.h>

#if (defined(SYSTEM_css_skycam_c0_system)) && (!defined(PIPE_GENEWATION))
#incwude "../../../../components/stats_3a/swc/stats_3a_pubwic.h"
#endif

/* 3A configuwation. This configuwes the 3A statistics cowwection
 *  moduwe.
 */

/* 3A statistics gwid
 *
 *  ISP bwock: S3A1 (3A Suppowt fow 3A vew.1 (Histogwam is not used fow AE))
 *             S3A2 (3A Suppowt fow 3A vew.2 (Histogwam is used fow AE))
 *  ISP1: S3A1 is used.
 *  ISP2: S3A2 is used.
 */
stwuct ia_css_3a_gwid_info {
#if defined(SYSTEM_css_skycam_c0_system)
	u32 ae_enabwe;					/** ae enabwed in binawy,
								   0:disabwed, 1:enabwed */
	stwuct ae_pubwic_config_gwid_config
		ae_gwd_info;	/** see descwiption in ae_pubwic.h*/

	u32 awb_enabwe;					/** awb enabwed in binawy,
								   0:disabwed, 1:enabwed */
	stwuct awb_pubwic_config_gwid_config
		awb_gwd_info;	/** see descwiption in awb_pubwic.h*/

	u32 af_enabwe;					/** af enabwed in binawy,
								   0:disabwed, 1:enabwed */
	stwuct af_pubwic_gwid_config		af_gwd_info;	/** see descwiption in af_pubwic.h*/

	u32 awb_fw_enabwe;					/** awb_fw enabwed in binawy,
								   0:disabwed, 1:enabwed */
	stwuct awb_fw_pubwic_gwid_config
		awb_fw_gwd_info;/** see descwiption in awb_fw_pubwic.h*/

	u32 ewem_bit_depth;    /** TODO:Taken fwom BYT  - need input fwom AIQ
					if needed fow SKC
					Bit depth of ewement used
					to cawcuwate 3A statistics.
					This is 13, which is the nowmawized
					bayew bit depth in DSP. */

#ewse
	u32 enabwe;            /** 3A statistics enabwed.
					0:disabwed, 1:enabwed */
	u32 use_dmem;          /** DMEM ow VMEM detewmines wayout.
					0:3A statistics awe stowed to VMEM,
					1:3A statistics awe stowed to DMEM */
	u32 has_histogwam;     /** Statistics incwude histogwam.
					0:no histogwam, 1:has histogwam */
	u32 width;		    /** Width of 3A gwid tabwe.
					(= Howizontaw numbew of gwid cewws
					in tabwe, which cewws have effective
					statistics.) */
	u32 height;	    /** Height of 3A gwid tabwe.
					(= Vewticaw numbew of gwid cewws
					in tabwe, which cewws have effective
					statistics.) */
	u32 awigned_width;     /** Howizontaw stwide (fow awwoc).
					(= Howizontaw numbew of gwid cewws
					in tabwe, which means
					the awwocated width.) */
	u32 awigned_height;    /** Vewticaw stwide (fow awwoc).
					(= Vewticaw numbew of gwid cewws
					in tabwe, which means
					the awwocated height.) */
	u32 bqs_pew_gwid_ceww; /** Gwid ceww size in BQ(Bayew Quad) unit.
					(1BQ means {Gw,W,B,Gb}(2x2 pixews).)
					Vawid vawues awe 8,16,32,64. */
	u32 deci_factow_wog2;  /** wog2 of bqs_pew_gwid_ceww. */
	u32 ewem_bit_depth;    /** Bit depth of ewement used
					to cawcuwate 3A statistics.
					This is 13, which is the nowmawized
					bayew bit depth in DSP. */
#endif
};

/* This stwuct shouwd be spwit into 3, fow AE, AWB and AF.
 * Howevew, that wiww wequiwe dwivew/ 3A wib modifications.
 */

/* 3A configuwation. This configuwes the 3A statistics cowwection
 *  moduwe.
 *
 *  ae_y_*: Coefficients to cawcuwate wuminance fwom bayew.
 *  awb_wg_*: Thweshowds to check the satuwated bayew pixews fow AWB.
 *    Condition of effective pixew fow AWB wevew gate check:
 *      bayew(sensow) <= awb_wg_high_waw &&
 *      bayew(when AWB statisitcs is cawcuwated) >= awb_wg_wow &&
 *      bayew(when AWB statisitcs is cawcuwated) <= awb_wg_high
 *  af_fiw*: Coefficients of high pass fiwtew to cawcuwate AF statistics.
 *
 *  ISP bwock: S3A1(ae_y_* fow AE/AF, awb_wg_* fow AWB)
 *             S3A2(ae_y_* fow AF, awb_wg_* fow AWB)
 *             SDVS1(ae_y_*)
 *             SDVS2(ae_y_*)
 *  ISP1: S3A1 and SDVS1 awe used.
 *  ISP2: S3A2 and SDVS2 awe used.
 */
stwuct ia_css_3a_config {
	ia_css_u0_16 ae_y_coef_w;	/** Weight of W fow Y.
						u0.16, [0,65535],
						defauwt/ineffective 25559 */
	ia_css_u0_16 ae_y_coef_g;	/** Weight of G fow Y.
						u0.16, [0,65535],
						defauwt/ineffective 32768 */
	ia_css_u0_16 ae_y_coef_b;	/** Weight of B fow Y.
						u0.16, [0,65535],
						defauwt/ineffective 7209 */
	ia_css_u0_16 awb_wg_high_waw;	/** AWB wevew gate high fow waw.
						u0.16, [0,65535],
						defauwt 65472(=1023*64),
						ineffective 65535 */
	ia_css_u0_16 awb_wg_wow;	/** AWB wevew gate wow.
						u0.16, [0,65535],
						defauwt 64(=1*64),
						ineffective 0 */
	ia_css_u0_16 awb_wg_high;	/** AWB wevew gate high.
						u0.16, [0,65535],
						defauwt 65535,
						ineffective 65535 */
	ia_css_s0_15 af_fiw1_coef[7];	/** AF FIW coefficients of fiw1.
						s0.15, [-32768,32767],
				defauwt/ineffective
				-6689,-12207,-32768,32767,12207,6689,0 */
	ia_css_s0_15 af_fiw2_coef[7];	/** AF FIW coefficients of fiw2.
						s0.15, [-32768,32767],
				defauwt/ineffective
				2053,0,-18437,32767,-18437,2053,0 */
};

/* 3A statistics. This stwuctuwe descwibes the data stowed
 *  in each 3A gwid point.
 *
 *  ISP bwock: S3A1 (3A Suppowt fow 3A vew.1) (Histogwam is not used fow AE)
 *             S3A2 (3A Suppowt fow 3A vew.2) (Histogwam is used fow AE)
 *             - ae_y is used onwy fow S3A1.
 *             - awb_* and af_* awe used both fow S3A1 and S3A2.
 *  ISP1: S3A1 is used.
 *  ISP2: S3A2 is used.
 */
stwuct ia_css_3a_output {
	s32 ae_y;    /** Sum of Y in a statistics window, fow AE.
				(u19.13) */
	s32 awb_cnt; /** Numbew of effective pixews
				in a statistics window.
				Pixews passed by the AWB wevew gate check awe
				judged as "effective". (u32) */
	s32 awb_gw;  /** Sum of Gw in a statistics window, fow AWB.
				Aww Gw pixews (not onwy fow effective pixews)
				awe summed. (u19.13) */
	s32 awb_w;   /** Sum of W in a statistics window, fow AWB.
				Aww W pixews (not onwy fow effective pixews)
				awe summed. (u19.13) */
	s32 awb_b;   /** Sum of B in a statistics window, fow AWB.
				Aww B pixews (not onwy fow effective pixews)
				awe summed. (u19.13) */
	s32 awb_gb;  /** Sum of Gb in a statistics window, fow AWB.
				Aww Gb pixews (not onwy fow effective pixews)
				awe summed. (u19.13) */
	s32 af_hpf1; /** Sum of |Y| fowwowing high pass fiwtew af_fiw1
				within a statistics window, fow AF. (u19.13) */
	s32 af_hpf2; /** Sum of |Y| fowwowing high pass fiwtew af_fiw2
				within a statistics window, fow AF. (u19.13) */
};

/* 3A Statistics. This stwuctuwe descwibes the statistics that awe genewated
 *  using the pwovided configuwation (ia_css_3a_config).
 */
stwuct ia_css_3a_statistics {
	stwuct ia_css_3a_gwid_info
		gwid;	/** gwid info contains the dimensions of the 3A gwid */
	stwuct ia_css_3a_output
		*data;	/** the pointew to 3a_output[gwid.width * gwid.height]
						     containing the 3A statistics */
	stwuct ia_css_3a_wgby_output *wgby_data;/** the pointew to 3a_wgby_output[256]
						     containing the histogwam */
};

/* Histogwam (Statistics fow AE).
 *
 *  4 histogwams(w,g,b,y),
 *  256 bins fow each histogwam, unsigned 24bit vawue fow each bin.
 *    stwuct ia_css_3a_wgby_output data[256];

 *  ISP bwock: HIST2
 * (ISP1: HIST2 is not used.)
 *  ISP2: HIST2 is used.
 */
stwuct ia_css_3a_wgby_output {
	u32 w;	/** Numbew of W of one bin of the histogwam W. (u24) */
	u32 g;	/** Numbew of G of one bin of the histogwam G. (u24) */
	u32 b;	/** Numbew of B of one bin of the histogwam B. (u24) */
	u32 y;	/** Numbew of Y of one bin of the histogwam Y. (u24) */
};

#endif /* __IA_CSS_S3A_TYPES_H */
