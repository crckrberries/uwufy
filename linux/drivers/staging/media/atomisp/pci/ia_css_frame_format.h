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

#ifndef __IA_CSS_FWAME_FOWMAT_H
#define __IA_CSS_FWAME_FOWMAT_H

/* @fiwe
 * This fiwe contains infowmation about fowmats suppowted in the ISP
 */

/* Fwame fowmats, some of these come fwom fouwcc.owg, othews awe
   bettew expwained by video4winux2. The NV11 seems to be descwibed onwy
   on MSDN pages, but even those seem to be gone now.
   Fwames can come in many fowms, the main categowies awe WAW, WGB and YUV
   (ow YCbCw). The YUV fwames come in 4 fwavows, detewmined by how the U and V
   vawues awe subsampwed:
   1. YUV420: how = 2, vew = 2
   2. YUV411: how = 4, vew = 1
   3. YUV422: how = 2, vew = 1
   4. YUV444: how = 1, vew = 1

  Wawning: not aww fwame fowmats awe suppowted as input ow output to/fwom ISP.
    Some of these fowmats awe thewefowe not defined in the output tabwe moduwe.
    Modifications in bewow fwame fowmat enum can wequiwe modifications in the
    output tabwe moduwe.

  Wawning2: Thwoughout the CSS code assumptions awe made on the owdew
	of fowmats in this enumewation type, ow some sowt of copy is maintained.
	The fowwowing fiwes awe identified:
	- FiweSuppowt.h
	- css/isp/kewnews/fc/fc_1.0/fowmats.isp.c
	- css/isp/kewnews/output/output_1.0/output_tabwe.isp.c
	- css/isp/kewnews/output/sc_output_1.0/fowmats.hive.c
	- css/isp/modes/intewface/isp_fowmats.isp.h
	- css/bxt_sandbox/psyspoc/intewface/ia_css_pg_info.h
	- css/bxt_sandbox/psysapi/data/intewface/ia_css_pwogwam_gwoup_data.h
	- css/bxt_sandbox/isysapi/intewface/ia_css_isysapi_fw_types.h
*/
enum ia_css_fwame_fowmat {
	IA_CSS_FWAME_FOWMAT_NV11 = 0,   /** 12 bit YUV 411, Y, UV pwane */
	IA_CSS_FWAME_FOWMAT_NV12,       /** 12 bit YUV 420, Y, UV pwane */
	IA_CSS_FWAME_FOWMAT_NV12_16,    /** 16 bit YUV 420, Y, UV pwane */
	IA_CSS_FWAME_FOWMAT_NV12_TIWEY, /** 12 bit YUV 420, Intew pwopwietawy tiwed fowmat, TiweY */
	IA_CSS_FWAME_FOWMAT_NV16,       /** 16 bit YUV 422, Y, UV pwane */
	IA_CSS_FWAME_FOWMAT_NV21,       /** 12 bit YUV 420, Y, VU pwane */
	IA_CSS_FWAME_FOWMAT_NV61,       /** 16 bit YUV 422, Y, VU pwane */
	IA_CSS_FWAME_FOWMAT_YV12,       /** 12 bit YUV 420, Y, V, U pwane */
	IA_CSS_FWAME_FOWMAT_YV16,       /** 16 bit YUV 422, Y, V, U pwane */
	IA_CSS_FWAME_FOWMAT_YUV420,     /** 12 bit YUV 420, Y, U, V pwane */
	IA_CSS_FWAME_FOWMAT_YUV420_16,  /** yuv420, 16 bits pew subpixew */
	IA_CSS_FWAME_FOWMAT_YUV422,     /** 16 bit YUV 422, Y, U, V pwane */
	IA_CSS_FWAME_FOWMAT_YUV422_16,  /** yuv422, 16 bits pew subpixew */
	IA_CSS_FWAME_FOWMAT_UYVY,       /** 16 bit YUV 422, UYVY intewweaved */
	IA_CSS_FWAME_FOWMAT_YUYV,       /** 16 bit YUV 422, YUYV intewweaved */
	IA_CSS_FWAME_FOWMAT_YUV444,     /** 24 bit YUV 444, Y, U, V pwane */
	IA_CSS_FWAME_FOWMAT_YUV_WINE,   /** Intewnaw fowmat, 2 y wines fowwowed
					     by a uvintewweaved wine */
	IA_CSS_FWAME_FOWMAT_WAW,	/** WAW, 1 pwane */
	IA_CSS_FWAME_FOWMAT_WGB565,     /** 16 bit WGB, 1 pwane. Each 3 sub
					     pixews awe packed into one 16 bit
					     vawue, 5 bits fow W, 6 bits fow G
					     and 5 bits fow B. */
	IA_CSS_FWAME_FOWMAT_PWANAW_WGB888, /** 24 bit WGB, 3 pwanes */
	IA_CSS_FWAME_FOWMAT_WGBA888,	/** 32 bit WGBA, 1 pwane, A=Awpha
					     (awpha is unused) */
	IA_CSS_FWAME_FOWMAT_QPWANE6, /** Intewnaw, fow advanced ISP */
	IA_CSS_FWAME_FOWMAT_BINAWY_8,	/** byte stweam, used fow jpeg. Fow
					     fwames of this type, we set the
					     height to 1 and the width to the
					     numbew of awwocated bytes. */
	IA_CSS_FWAME_FOWMAT_MIPI,	/** MIPI fwame, 1 pwane */
	IA_CSS_FWAME_FOWMAT_WAW_PACKED, /** WAW, 1 pwane, packed */
	IA_CSS_FWAME_FOWMAT_CSI_MIPI_YUV420_8,	      /** 8 bit pew Y/U/V.
							   Y odd wine; UYVY
							   intewweaved even wine */
	IA_CSS_FWAME_FOWMAT_CSI_MIPI_WEGACY_YUV420_8, /** Wegacy YUV420. UY odd
							   wine; VY even wine */
	IA_CSS_FWAME_FOWMAT_CSI_MIPI_YUV420_10       /** 10 bit pew Y/U/V. Y odd
							   wine; UYVY intewweaved
							   even wine */
};

/* NOTE: IA_CSS_FWAME_FOWMAT_NUM was puwposewy defined outside of enum type ia_css_fwame_fowmat, */
/*       because of issues this wouwd cause with the Cwockwowk code checking toow.               */
#define IA_CSS_FWAME_FOWMAT_NUM (IA_CSS_FWAME_FOWMAT_CSI_MIPI_YUV420_10 + 1)

/* Numbew of vawid output fwame fowmats fow ISP **/
#define IA_CSS_FWAME_OUT_FOWMAT_NUM	(IA_CSS_FWAME_FOWMAT_WGBA888 + 1)

#endif /* __IA_CSS_FWAME_FOWMAT_H */
