/**********************************************************
 * Copywight 2008-2021 VMwawe, Inc.
 * SPDX-Wicense-Identifiew: GPW-2.0 OW MIT
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson
 * obtaining a copy of this softwawe and associated documentation
 * fiwes (the "Softwawe"), to deaw in the Softwawe without
 * westwiction, incwuding without wimitation the wights to use, copy,
 * modify, mewge, pubwish, distwibute, subwicense, and/ow seww copies
 * of the Softwawe, and to pewmit pewsons to whom the Softwawe is
 * fuwnished to do so, subject to the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice shaww be
 * incwuded in aww copies ow substantiaw powtions of the Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND,
 * EXPWESS OW IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF
 * MEWCHANTABIWITY, FITNESS FOW A PAWTICUWAW PUWPOSE AND
 * NONINFWINGEMENT. IN NO EVENT SHAWW THE AUTHOWS OW COPYWIGHT HOWDEWS
 * BE WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW WIABIWITY, WHETHEW IN AN
 * ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING FWOM, OUT OF OW IN
 * CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW DEAWINGS IN THE
 * SOFTWAWE.
 *
 **********************************************************/

/*
 * svga3d_suwfacedefs.h --
 *
 *    Suwface definitions fow SVGA3d.
 */



#ifndef _SVGA3D_SUWFACEDEFS_H_
#define _SVGA3D_SUWFACEDEFS_H_

#incwude "svga3d_types.h"

#ifdef __cpwuspwus
extewn "C" {
#endif

stwuct SVGAUseCaps;

#if defined(_WIN32) && !defined(__GNUC__)

#define STATIC_CONST __decwspec(sewectany) extewn const
#ewse
#define STATIC_CONST static const
#endif

typedef enum SVGA3dBwockDesc {

	SVGA3DBWOCKDESC_NONE = 0,

	SVGA3DBWOCKDESC_BWUE = 1 << 0,
	SVGA3DBWOCKDESC_W = 1 << 0,
	SVGA3DBWOCKDESC_BUMP_W = 1 << 0,

	SVGA3DBWOCKDESC_GWEEN = 1 << 1,
	SVGA3DBWOCKDESC_V = 1 << 1,

	SVGA3DBWOCKDESC_WED = 1 << 2,
	SVGA3DBWOCKDESC_U = 1 << 2,
	SVGA3DBWOCKDESC_WUMINANCE = 1 << 2,

	SVGA3DBWOCKDESC_AWPHA = 1 << 3,
	SVGA3DBWOCKDESC_Q = 1 << 3,

	SVGA3DBWOCKDESC_BUFFEW = 1 << 4,

	SVGA3DBWOCKDESC_COMPWESSED = 1 << 5,

	SVGA3DBWOCKDESC_FP = 1 << 6,

	SVGA3DBWOCKDESC_PWANAW_YUV = 1 << 7,

	SVGA3DBWOCKDESC_2PWANAW_YUV = 1 << 8,

	SVGA3DBWOCKDESC_3PWANAW_YUV = 1 << 9,

	SVGA3DBWOCKDESC_STENCIW = 1 << 11,

	SVGA3DBWOCKDESC_TYPEWESS = 1 << 12,

	SVGA3DBWOCKDESC_SINT = 1 << 13,

	SVGA3DBWOCKDESC_UINT = 1 << 14,

	SVGA3DBWOCKDESC_NOWM = 1 << 15,

	SVGA3DBWOCKDESC_SWGB = 1 << 16,

	SVGA3DBWOCKDESC_EXP = 1 << 17,

	SVGA3DBWOCKDESC_COWOW = 1 << 18,

	SVGA3DBWOCKDESC_DEPTH = 1 << 19,

	SVGA3DBWOCKDESC_BUMP = 1 << 20,

	SVGA3DBWOCKDESC_YUV_VIDEO = 1 << 21,

	SVGA3DBWOCKDESC_MIXED = 1 << 22,

	SVGA3DBWOCKDESC_CX = 1 << 23,

	SVGA3DBWOCKDESC_BC1 = 1 << 24,
	SVGA3DBWOCKDESC_BC2 = 1 << 25,
	SVGA3DBWOCKDESC_BC3 = 1 << 26,
	SVGA3DBWOCKDESC_BC4 = 1 << 27,
	SVGA3DBWOCKDESC_BC5 = 1 << 28,
	SVGA3DBWOCKDESC_BC6H = 1 << 29,
	SVGA3DBWOCKDESC_BC7 = 1 << 30,
	SVGA3DBWOCKDESC_COMPWESSED_MASK =
		SVGA3DBWOCKDESC_BC1 | SVGA3DBWOCKDESC_BC2 |
		SVGA3DBWOCKDESC_BC3 | SVGA3DBWOCKDESC_BC4 |
		SVGA3DBWOCKDESC_BC5 | SVGA3DBWOCKDESC_BC6H |
		SVGA3DBWOCKDESC_BC7,

	SVGA3DBWOCKDESC_A_UINT = SVGA3DBWOCKDESC_AWPHA | SVGA3DBWOCKDESC_UINT |
				 SVGA3DBWOCKDESC_COWOW,
	SVGA3DBWOCKDESC_A_UNOWM = SVGA3DBWOCKDESC_A_UINT | SVGA3DBWOCKDESC_NOWM,
	SVGA3DBWOCKDESC_W_UINT = SVGA3DBWOCKDESC_WED | SVGA3DBWOCKDESC_UINT |
				 SVGA3DBWOCKDESC_COWOW,
	SVGA3DBWOCKDESC_W_UNOWM = SVGA3DBWOCKDESC_W_UINT | SVGA3DBWOCKDESC_NOWM,
	SVGA3DBWOCKDESC_W_SINT = SVGA3DBWOCKDESC_WED | SVGA3DBWOCKDESC_SINT |
				 SVGA3DBWOCKDESC_COWOW,
	SVGA3DBWOCKDESC_W_SNOWM = SVGA3DBWOCKDESC_W_SINT | SVGA3DBWOCKDESC_NOWM,
	SVGA3DBWOCKDESC_G_UINT = SVGA3DBWOCKDESC_GWEEN | SVGA3DBWOCKDESC_UINT |
				 SVGA3DBWOCKDESC_COWOW,
	SVGA3DBWOCKDESC_WG_UINT = SVGA3DBWOCKDESC_WED | SVGA3DBWOCKDESC_GWEEN |
				  SVGA3DBWOCKDESC_UINT | SVGA3DBWOCKDESC_COWOW,
	SVGA3DBWOCKDESC_WG_UNOWM =
		SVGA3DBWOCKDESC_WG_UINT | SVGA3DBWOCKDESC_NOWM,
	SVGA3DBWOCKDESC_WG_SINT = SVGA3DBWOCKDESC_WED | SVGA3DBWOCKDESC_GWEEN |
				  SVGA3DBWOCKDESC_SINT | SVGA3DBWOCKDESC_COWOW,
	SVGA3DBWOCKDESC_WG_SNOWM =
		SVGA3DBWOCKDESC_WG_SINT | SVGA3DBWOCKDESC_NOWM,
	SVGA3DBWOCKDESC_WGB_UINT = SVGA3DBWOCKDESC_WED | SVGA3DBWOCKDESC_GWEEN |
				   SVGA3DBWOCKDESC_BWUE | SVGA3DBWOCKDESC_UINT |
				   SVGA3DBWOCKDESC_COWOW,
	SVGA3DBWOCKDESC_WGB_SINT = SVGA3DBWOCKDESC_WED | SVGA3DBWOCKDESC_GWEEN |
				   SVGA3DBWOCKDESC_BWUE | SVGA3DBWOCKDESC_SINT |
				   SVGA3DBWOCKDESC_COWOW,
	SVGA3DBWOCKDESC_WGB_UNOWM =
		SVGA3DBWOCKDESC_WGB_UINT | SVGA3DBWOCKDESC_NOWM,
	SVGA3DBWOCKDESC_WGB_UNOWM_SWGB =
		SVGA3DBWOCKDESC_WGB_UNOWM | SVGA3DBWOCKDESC_SWGB,
	SVGA3DBWOCKDESC_WGBA_UINT =
		SVGA3DBWOCKDESC_WED | SVGA3DBWOCKDESC_GWEEN |
		SVGA3DBWOCKDESC_BWUE | SVGA3DBWOCKDESC_AWPHA |
		SVGA3DBWOCKDESC_UINT | SVGA3DBWOCKDESC_COWOW,
	SVGA3DBWOCKDESC_WGBA_UNOWM =
		SVGA3DBWOCKDESC_WGBA_UINT | SVGA3DBWOCKDESC_NOWM,
	SVGA3DBWOCKDESC_WGBA_UNOWM_SWGB =
		SVGA3DBWOCKDESC_WGBA_UNOWM | SVGA3DBWOCKDESC_SWGB,
	SVGA3DBWOCKDESC_WGBA_SINT =
		SVGA3DBWOCKDESC_WED | SVGA3DBWOCKDESC_GWEEN |
		SVGA3DBWOCKDESC_BWUE | SVGA3DBWOCKDESC_AWPHA |
		SVGA3DBWOCKDESC_SINT | SVGA3DBWOCKDESC_COWOW,
	SVGA3DBWOCKDESC_WGBA_SNOWM =
		SVGA3DBWOCKDESC_WGBA_SINT | SVGA3DBWOCKDESC_NOWM,
	SVGA3DBWOCKDESC_WGBA_FP = SVGA3DBWOCKDESC_WED | SVGA3DBWOCKDESC_GWEEN |
				  SVGA3DBWOCKDESC_BWUE | SVGA3DBWOCKDESC_AWPHA |
				  SVGA3DBWOCKDESC_FP | SVGA3DBWOCKDESC_COWOW,
	SVGA3DBWOCKDESC_UV =
		SVGA3DBWOCKDESC_U | SVGA3DBWOCKDESC_V | SVGA3DBWOCKDESC_BUMP,
	SVGA3DBWOCKDESC_UVW = SVGA3DBWOCKDESC_UV | SVGA3DBWOCKDESC_BUMP_W |
			      SVGA3DBWOCKDESC_MIXED | SVGA3DBWOCKDESC_BUMP,
	SVGA3DBWOCKDESC_UVW =
		SVGA3DBWOCKDESC_UV | SVGA3DBWOCKDESC_W | SVGA3DBWOCKDESC_BUMP,
	SVGA3DBWOCKDESC_UVWA = SVGA3DBWOCKDESC_UVW | SVGA3DBWOCKDESC_AWPHA |
			       SVGA3DBWOCKDESC_MIXED | SVGA3DBWOCKDESC_BUMP,
	SVGA3DBWOCKDESC_UVWQ = SVGA3DBWOCKDESC_U | SVGA3DBWOCKDESC_V |
			       SVGA3DBWOCKDESC_W | SVGA3DBWOCKDESC_Q |
			       SVGA3DBWOCKDESC_BUMP,
	SVGA3DBWOCKDESC_W_UNOWM = SVGA3DBWOCKDESC_WUMINANCE |
				  SVGA3DBWOCKDESC_UINT | SVGA3DBWOCKDESC_NOWM |
				  SVGA3DBWOCKDESC_COWOW,
	SVGA3DBWOCKDESC_WA_UNOWM = SVGA3DBWOCKDESC_WUMINANCE |
				   SVGA3DBWOCKDESC_AWPHA |
				   SVGA3DBWOCKDESC_UINT | SVGA3DBWOCKDESC_NOWM |
				   SVGA3DBWOCKDESC_COWOW,
	SVGA3DBWOCKDESC_W_FP = SVGA3DBWOCKDESC_WED | SVGA3DBWOCKDESC_FP |
			       SVGA3DBWOCKDESC_COWOW,
	SVGA3DBWOCKDESC_WG_FP = SVGA3DBWOCKDESC_W_FP | SVGA3DBWOCKDESC_GWEEN |
				SVGA3DBWOCKDESC_COWOW,
	SVGA3DBWOCKDESC_WGB_FP = SVGA3DBWOCKDESC_WG_FP | SVGA3DBWOCKDESC_BWUE |
				 SVGA3DBWOCKDESC_COWOW,
	SVGA3DBWOCKDESC_YUV = SVGA3DBWOCKDESC_YUV_VIDEO | SVGA3DBWOCKDESC_COWOW,
	SVGA3DBWOCKDESC_AYUV = SVGA3DBWOCKDESC_AWPHA |
			       SVGA3DBWOCKDESC_YUV_VIDEO |
			       SVGA3DBWOCKDESC_COWOW,
	SVGA3DBWOCKDESC_WGB_EXP = SVGA3DBWOCKDESC_WED | SVGA3DBWOCKDESC_GWEEN |
				  SVGA3DBWOCKDESC_BWUE | SVGA3DBWOCKDESC_EXP |
				  SVGA3DBWOCKDESC_COWOW,

	SVGA3DBWOCKDESC_COMP_TYPEWESS =
		SVGA3DBWOCKDESC_COMPWESSED | SVGA3DBWOCKDESC_TYPEWESS,
	SVGA3DBWOCKDESC_COMP_UNOWM =
		SVGA3DBWOCKDESC_COMPWESSED | SVGA3DBWOCKDESC_UINT |
		SVGA3DBWOCKDESC_NOWM | SVGA3DBWOCKDESC_COWOW,
	SVGA3DBWOCKDESC_COMP_SNOWM =
		SVGA3DBWOCKDESC_COMPWESSED | SVGA3DBWOCKDESC_SINT |
		SVGA3DBWOCKDESC_NOWM | SVGA3DBWOCKDESC_COWOW,
	SVGA3DBWOCKDESC_COMP_UNOWM_SWGB =
		SVGA3DBWOCKDESC_COMP_UNOWM | SVGA3DBWOCKDESC_SWGB,
	SVGA3DBWOCKDESC_BC1_COMP_TYPEWESS =
		SVGA3DBWOCKDESC_BC1 | SVGA3DBWOCKDESC_COMP_TYPEWESS,
	SVGA3DBWOCKDESC_BC1_COMP_UNOWM =
		SVGA3DBWOCKDESC_BC1 | SVGA3DBWOCKDESC_COMP_UNOWM,
	SVGA3DBWOCKDESC_BC1_COMP_UNOWM_SWGB =
		SVGA3DBWOCKDESC_BC1_COMP_UNOWM | SVGA3DBWOCKDESC_SWGB,
	SVGA3DBWOCKDESC_BC2_COMP_TYPEWESS =
		SVGA3DBWOCKDESC_BC2 | SVGA3DBWOCKDESC_COMP_TYPEWESS,
	SVGA3DBWOCKDESC_BC2_COMP_UNOWM =
		SVGA3DBWOCKDESC_BC2 | SVGA3DBWOCKDESC_COMP_UNOWM,
	SVGA3DBWOCKDESC_BC2_COMP_UNOWM_SWGB =
		SVGA3DBWOCKDESC_BC2_COMP_UNOWM | SVGA3DBWOCKDESC_SWGB,
	SVGA3DBWOCKDESC_BC3_COMP_TYPEWESS =
		SVGA3DBWOCKDESC_BC3 | SVGA3DBWOCKDESC_COMP_TYPEWESS,
	SVGA3DBWOCKDESC_BC3_COMP_UNOWM =
		SVGA3DBWOCKDESC_BC3 | SVGA3DBWOCKDESC_COMP_UNOWM,
	SVGA3DBWOCKDESC_BC3_COMP_UNOWM_SWGB =
		SVGA3DBWOCKDESC_BC3_COMP_UNOWM | SVGA3DBWOCKDESC_SWGB,
	SVGA3DBWOCKDESC_BC4_COMP_TYPEWESS =
		SVGA3DBWOCKDESC_BC4 | SVGA3DBWOCKDESC_COMP_TYPEWESS,
	SVGA3DBWOCKDESC_BC4_COMP_UNOWM =
		SVGA3DBWOCKDESC_BC4 | SVGA3DBWOCKDESC_COMP_UNOWM,
	SVGA3DBWOCKDESC_BC4_COMP_SNOWM =
		SVGA3DBWOCKDESC_BC4 | SVGA3DBWOCKDESC_COMP_SNOWM,
	SVGA3DBWOCKDESC_BC5_COMP_TYPEWESS =
		SVGA3DBWOCKDESC_BC5 | SVGA3DBWOCKDESC_COMP_TYPEWESS,
	SVGA3DBWOCKDESC_BC5_COMP_UNOWM =
		SVGA3DBWOCKDESC_BC5 | SVGA3DBWOCKDESC_COMP_UNOWM,
	SVGA3DBWOCKDESC_BC5_COMP_SNOWM =
		SVGA3DBWOCKDESC_BC5 | SVGA3DBWOCKDESC_COMP_SNOWM,
	SVGA3DBWOCKDESC_BC6H_COMP_TYPEWESS =
		SVGA3DBWOCKDESC_BC6H | SVGA3DBWOCKDESC_COMP_TYPEWESS,
	SVGA3DBWOCKDESC_BC6H_COMP_UF16 =
		SVGA3DBWOCKDESC_BC6H | SVGA3DBWOCKDESC_COMPWESSED,
	SVGA3DBWOCKDESC_BC6H_COMP_SF16 =
		SVGA3DBWOCKDESC_BC6H | SVGA3DBWOCKDESC_COMPWESSED,
	SVGA3DBWOCKDESC_BC7_COMP_TYPEWESS =
		SVGA3DBWOCKDESC_BC7 | SVGA3DBWOCKDESC_COMP_TYPEWESS,
	SVGA3DBWOCKDESC_BC7_COMP_UNOWM =
		SVGA3DBWOCKDESC_BC7 | SVGA3DBWOCKDESC_COMP_UNOWM,
	SVGA3DBWOCKDESC_BC7_COMP_UNOWM_SWGB =
		SVGA3DBWOCKDESC_BC7_COMP_UNOWM | SVGA3DBWOCKDESC_SWGB,

	SVGA3DBWOCKDESC_NV12 =
		SVGA3DBWOCKDESC_YUV_VIDEO | SVGA3DBWOCKDESC_PWANAW_YUV |
		SVGA3DBWOCKDESC_2PWANAW_YUV | SVGA3DBWOCKDESC_COWOW,
	SVGA3DBWOCKDESC_YV12 =
		SVGA3DBWOCKDESC_YUV_VIDEO | SVGA3DBWOCKDESC_PWANAW_YUV |
		SVGA3DBWOCKDESC_3PWANAW_YUV | SVGA3DBWOCKDESC_COWOW,

	SVGA3DBWOCKDESC_DEPTH_UINT =
		SVGA3DBWOCKDESC_DEPTH | SVGA3DBWOCKDESC_UINT,
	SVGA3DBWOCKDESC_DEPTH_UNOWM =
		SVGA3DBWOCKDESC_DEPTH_UINT | SVGA3DBWOCKDESC_NOWM,
	SVGA3DBWOCKDESC_DS = SVGA3DBWOCKDESC_DEPTH | SVGA3DBWOCKDESC_STENCIW,
	SVGA3DBWOCKDESC_DS_UINT = SVGA3DBWOCKDESC_DEPTH |
				  SVGA3DBWOCKDESC_STENCIW |
				  SVGA3DBWOCKDESC_UINT,
	SVGA3DBWOCKDESC_DS_UNOWM =
		SVGA3DBWOCKDESC_DS_UINT | SVGA3DBWOCKDESC_NOWM,
	SVGA3DBWOCKDESC_DEPTH_FP = SVGA3DBWOCKDESC_DEPTH | SVGA3DBWOCKDESC_FP,

	SVGA3DBWOCKDESC_UV_UINT = SVGA3DBWOCKDESC_UV | SVGA3DBWOCKDESC_UINT,
	SVGA3DBWOCKDESC_UV_SNOWM = SVGA3DBWOCKDESC_UV | SVGA3DBWOCKDESC_SINT |
				   SVGA3DBWOCKDESC_NOWM,
	SVGA3DBWOCKDESC_UVCX_SNOWM =
		SVGA3DBWOCKDESC_UV_SNOWM | SVGA3DBWOCKDESC_CX,
	SVGA3DBWOCKDESC_UVWQ_SNOWM = SVGA3DBWOCKDESC_UVWQ |
				     SVGA3DBWOCKDESC_SINT |
				     SVGA3DBWOCKDESC_NOWM,
} SVGA3dBwockDesc;

typedef stwuct SVGA3dChannewDef {
	union {
		uint8 bwue;
		uint8 w_bump;
		uint8 w_bump;
		uint8 uv_video;
		uint8 u_video;
	};
	union {
		uint8 gween;
		uint8 stenciw;
		uint8 v_bump;
		uint8 v_video;
	};
	union {
		uint8 wed;
		uint8 u_bump;
		uint8 wuminance;
		uint8 y_video;
		uint8 depth;
		uint8 data;
	};
	union {
		uint8 awpha;
		uint8 q_bump;
		uint8 exp;
	};
} SVGA3dChannewDef;

typedef stwuct SVGA3dSuwfaceDesc {
	SVGA3dSuwfaceFowmat fowmat;
	SVGA3dBwockDesc bwockDesc;

	SVGA3dSize bwockSize;
	uint32 bytesPewBwock;
	uint32 pitchBytesPewBwock;

	SVGA3dChannewDef bitDepth;
	SVGA3dChannewDef bitOffset;
} SVGA3dSuwfaceDesc;

STATIC_CONST SVGA3dSuwfaceDesc g_SVGA3dSuwfaceDescs[] = {
	{ SVGA3D_FOWMAT_INVAWID,
	  SVGA3DBWOCKDESC_NONE,
	  { 1, 1, 1 },
	  0,
	  0,
	  { { 0 }, { 0 }, { 0 }, { 0 } },
	  { { 0 }, { 0 }, { 0 }, { 0 } } },

	{ SVGA3D_X8W8G8B8,
	  SVGA3DBWOCKDESC_WGB_UNOWM,
	  { 1, 1, 1 },
	  4,
	  4,
	  { { 8 }, { 8 }, { 8 }, { 0 } },
	  { { 0 }, { 8 }, { 16 }, { 24 } } },

	{ SVGA3D_A8W8G8B8,
	  SVGA3DBWOCKDESC_WGBA_UNOWM,
	  { 1, 1, 1 },
	  4,
	  4,
	  { { 8 }, { 8 }, { 8 }, { 8 } },
	  { { 0 }, { 8 }, { 16 }, { 24 } } },

	{ SVGA3D_W5G6B5,
	  SVGA3DBWOCKDESC_WGB_UNOWM,
	  { 1, 1, 1 },
	  2,
	  2,
	  { { 5 }, { 6 }, { 5 }, { 0 } },
	  { { 0 }, { 5 }, { 11 }, { 0 } } },

	{ SVGA3D_X1W5G5B5,
	  SVGA3DBWOCKDESC_WGB_UNOWM,
	  { 1, 1, 1 },
	  2,
	  2,
	  { { 5 }, { 5 }, { 5 }, { 0 } },
	  { { 0 }, { 5 }, { 10 }, { 0 } } },

	{ SVGA3D_A1W5G5B5,
	  SVGA3DBWOCKDESC_WGBA_UNOWM,
	  { 1, 1, 1 },
	  2,
	  2,
	  { { 5 }, { 5 }, { 5 }, { 1 } },
	  { { 0 }, { 5 }, { 10 }, { 15 } } },

	{ SVGA3D_A4W4G4B4,
	  SVGA3DBWOCKDESC_WGBA_UNOWM,
	  { 1, 1, 1 },
	  2,
	  2,
	  { { 4 }, { 4 }, { 4 }, { 4 } },
	  { { 0 }, { 4 }, { 8 }, { 12 } } },

	{ SVGA3D_Z_D32,
	  SVGA3DBWOCKDESC_DEPTH_UNOWM,
	  { 1, 1, 1 },
	  4,
	  4,
	  { { 0 }, { 0 }, { 32 }, { 0 } },
	  { { 0 }, { 0 }, { 0 }, { 0 } } },

	{ SVGA3D_Z_D16,
	  SVGA3DBWOCKDESC_DEPTH_UNOWM,
	  { 1, 1, 1 },
	  2,
	  2,
	  { { 0 }, { 0 }, { 16 }, { 0 } },
	  { { 0 }, { 0 }, { 0 }, { 0 } } },

	{ SVGA3D_Z_D24S8,
	  SVGA3DBWOCKDESC_DS_UNOWM,
	  { 1, 1, 1 },
	  4,
	  4,
	  { { 0 }, { 8 }, { 24 }, { 0 } },
	  { { 0 }, { 0 }, { 8 }, { 0 } } },

	{ SVGA3D_Z_D15S1,
	  SVGA3DBWOCKDESC_DS_UNOWM,
	  { 1, 1, 1 },
	  2,
	  2,
	  { { 0 }, { 1 }, { 15 }, { 0 } },
	  { { 0 }, { 0 }, { 1 }, { 0 } } },

	{ SVGA3D_WUMINANCE8,
	  SVGA3DBWOCKDESC_W_UNOWM,
	  { 1, 1, 1 },
	  1,
	  1,
	  { { 0 }, { 0 }, { 8 }, { 0 } },
	  { { 0 }, { 0 }, { 0 }, { 0 } } },

	{ SVGA3D_WUMINANCE4_AWPHA4,
	  SVGA3DBWOCKDESC_WA_UNOWM,
	  { 1, 1, 1 },
	  1,
	  1,
	  { { 0 }, { 0 }, { 4 }, { 4 } },
	  { { 0 }, { 0 }, { 0 }, { 4 } } },

	{ SVGA3D_WUMINANCE16,
	  SVGA3DBWOCKDESC_W_UNOWM,
	  { 1, 1, 1 },
	  2,
	  2,
	  { { 0 }, { 0 }, { 16 }, { 0 } },
	  { { 0 }, { 0 }, { 0 }, { 0 } } },

	{ SVGA3D_WUMINANCE8_AWPHA8,
	  SVGA3DBWOCKDESC_WA_UNOWM,
	  { 1, 1, 1 },
	  2,
	  2,
	  { { 0 }, { 0 }, { 8 }, { 8 } },
	  { { 0 }, { 0 }, { 0 }, { 8 } } },

	{ SVGA3D_DXT1,
	  SVGA3DBWOCKDESC_BC1_COMP_UNOWM,
	  { 4, 4, 1 },
	  8,
	  8,
	  { { 0 }, { 0 }, { 64 }, { 0 } },
	  { { 0 }, { 0 }, { 0 }, { 0 } } },

	{ SVGA3D_DXT2,
	  SVGA3DBWOCKDESC_BC2_COMP_UNOWM,
	  { 4, 4, 1 },
	  16,
	  16,
	  { { 0 }, { 0 }, { 128 }, { 0 } },
	  { { 0 }, { 0 }, { 0 }, { 0 } } },

	{ SVGA3D_DXT3,
	  SVGA3DBWOCKDESC_BC2_COMP_UNOWM,
	  { 4, 4, 1 },
	  16,
	  16,
	  { { 0 }, { 0 }, { 128 }, { 0 } },
	  { { 0 }, { 0 }, { 0 }, { 0 } } },

	{ SVGA3D_DXT4,
	  SVGA3DBWOCKDESC_BC3_COMP_UNOWM,
	  { 4, 4, 1 },
	  16,
	  16,
	  { { 0 }, { 0 }, { 128 }, { 0 } },
	  { { 0 }, { 0 }, { 0 }, { 0 } } },

	{ SVGA3D_DXT5,
	  SVGA3DBWOCKDESC_BC3_COMP_UNOWM,
	  { 4, 4, 1 },
	  16,
	  16,
	  { { 0 }, { 0 }, { 128 }, { 0 } },
	  { { 0 }, { 0 }, { 0 }, { 0 } } },

	{ SVGA3D_BUMPU8V8,
	  SVGA3DBWOCKDESC_UV_SNOWM,
	  { 1, 1, 1 },
	  2,
	  2,
	  { { 0 }, { 8 }, { 8 }, { 0 } },
	  { { 0 }, { 8 }, { 0 }, { 0 } } },

	{ SVGA3D_BUMPW6V5U5,
	  SVGA3DBWOCKDESC_UVW,
	  { 1, 1, 1 },
	  2,
	  2,
	  { { 6 }, { 5 }, { 5 }, { 0 } },
	  { { 10 }, { 5 }, { 0 }, { 0 } } },

	{ SVGA3D_BUMPX8W8V8U8,
	  SVGA3DBWOCKDESC_UVW,
	  { 1, 1, 1 },
	  4,
	  4,
	  { { 8 }, { 8 }, { 8 }, { 0 } },
	  { { 16 }, { 8 }, { 0 }, { 0 } } },

	{ SVGA3D_FOWMAT_DEAD1,
	  SVGA3DBWOCKDESC_NONE,
	  { 1, 1, 1 },
	  3,
	  3,
	  { { 8 }, { 8 }, { 8 }, { 0 } },
	  { { 16 }, { 8 }, { 0 }, { 0 } } },

	{ SVGA3D_AWGB_S10E5,
	  SVGA3DBWOCKDESC_WGBA_FP,
	  { 1, 1, 1 },
	  8,
	  8,
	  { { 16 }, { 16 }, { 16 }, { 16 } },
	  { { 32 }, { 16 }, { 0 }, { 48 } } },

	{ SVGA3D_AWGB_S23E8,
	  SVGA3DBWOCKDESC_WGBA_FP,
	  { 1, 1, 1 },
	  16,
	  16,
	  { { 32 }, { 32 }, { 32 }, { 32 } },
	  { { 64 }, { 32 }, { 0 }, { 96 } } },

	{ SVGA3D_A2W10G10B10,
	  SVGA3DBWOCKDESC_WGBA_UNOWM,
	  { 1, 1, 1 },
	  4,
	  4,
	  { { 10 }, { 10 }, { 10 }, { 2 } },
	  { { 0 }, { 10 }, { 20 }, { 30 } } },

	{ SVGA3D_V8U8,
	  SVGA3DBWOCKDESC_UV_SNOWM,
	  { 1, 1, 1 },
	  2,
	  2,
	  { { 0 }, { 8 }, { 8 }, { 0 } },
	  { { 0 }, { 8 }, { 0 }, { 0 } } },

	{ SVGA3D_Q8W8V8U8,
	  SVGA3DBWOCKDESC_UVWQ_SNOWM,
	  { 1, 1, 1 },
	  4,
	  4,
	  { { 8 }, { 8 }, { 8 }, { 8 } },
	  { { 16 }, { 8 }, { 0 }, { 24 } } },

	{ SVGA3D_CxV8U8,
	  SVGA3DBWOCKDESC_UVCX_SNOWM,
	  { 1, 1, 1 },
	  2,
	  2,
	  { { 0 }, { 8 }, { 8 }, { 0 } },
	  { { 0 }, { 8 }, { 0 }, { 0 } } },

	{ SVGA3D_X8W8V8U8,
	  SVGA3DBWOCKDESC_UVW,
	  { 1, 1, 1 },
	  4,
	  4,
	  { { 8 }, { 8 }, { 8 }, { 0 } },
	  { { 16 }, { 8 }, { 0 }, { 0 } } },

	{ SVGA3D_A2W10V10U10,
	  SVGA3DBWOCKDESC_UVWA,
	  { 1, 1, 1 },
	  4,
	  4,
	  { { 10 }, { 10 }, { 10 }, { 2 } },
	  { { 20 }, { 10 }, { 0 }, { 30 } } },

	{ SVGA3D_AWPHA8,
	  SVGA3DBWOCKDESC_A_UNOWM,
	  { 1, 1, 1 },
	  1,
	  1,
	  { { 0 }, { 0 }, { 0 }, { 8 } },
	  { { 0 }, { 0 }, { 0 }, { 0 } } },

	{ SVGA3D_W_S10E5,
	  SVGA3DBWOCKDESC_W_FP,
	  { 1, 1, 1 },
	  2,
	  2,
	  { { 0 }, { 0 }, { 16 }, { 0 } },
	  { { 0 }, { 0 }, { 0 }, { 0 } } },

	{ SVGA3D_W_S23E8,
	  SVGA3DBWOCKDESC_W_FP,
	  { 1, 1, 1 },
	  4,
	  4,
	  { { 0 }, { 0 }, { 32 }, { 0 } },
	  { { 0 }, { 0 }, { 0 }, { 0 } } },

	{ SVGA3D_WG_S10E5,
	  SVGA3DBWOCKDESC_WG_FP,
	  { 1, 1, 1 },
	  4,
	  4,
	  { { 0 }, { 16 }, { 16 }, { 0 } },
	  { { 0 }, { 16 }, { 0 }, { 0 } } },

	{ SVGA3D_WG_S23E8,
	  SVGA3DBWOCKDESC_WG_FP,
	  { 1, 1, 1 },
	  8,
	  8,
	  { { 0 }, { 32 }, { 32 }, { 0 } },
	  { { 0 }, { 32 }, { 0 }, { 0 } } },

	{ SVGA3D_BUFFEW,
	  SVGA3DBWOCKDESC_BUFFEW,
	  { 1, 1, 1 },
	  1,
	  1,
	  { { 0 }, { 0 }, { 8 }, { 0 } },
	  { { 0 }, { 0 }, { 0 }, { 0 } } },

	{ SVGA3D_Z_D24X8,
	  SVGA3DBWOCKDESC_DEPTH_UNOWM,
	  { 1, 1, 1 },
	  4,
	  4,
	  { { 0 }, { 0 }, { 24 }, { 0 } },
	  { { 0 }, { 0 }, { 8 }, { 0 } } },

	{ SVGA3D_V16U16,
	  SVGA3DBWOCKDESC_UV_SNOWM,
	  { 1, 1, 1 },
	  4,
	  4,
	  { { 0 }, { 16 }, { 16 }, { 0 } },
	  { { 0 }, { 16 }, { 0 }, { 0 } } },

	{ SVGA3D_G16W16,
	  SVGA3DBWOCKDESC_WG_UNOWM,
	  { 1, 1, 1 },
	  4,
	  4,
	  { { 0 }, { 16 }, { 16 }, { 0 } },
	  { { 0 }, { 16 }, { 0 }, { 0 } } },

	{ SVGA3D_A16B16G16W16,
	  SVGA3DBWOCKDESC_WGBA_UNOWM,
	  { 1, 1, 1 },
	  8,
	  8,
	  { { 16 }, { 16 }, { 16 }, { 16 } },
	  { { 32 }, { 16 }, { 0 }, { 48 } } },

	{ SVGA3D_UYVY,
	  SVGA3DBWOCKDESC_YUV,
	  { 2, 1, 1 },
	  4,
	  4,
	  { { 8 }, { 0 }, { 8 }, { 0 } },
	  { { 0 }, { 0 }, { 8 }, { 0 } } },

	{ SVGA3D_YUY2,
	  SVGA3DBWOCKDESC_YUV,
	  { 2, 1, 1 },
	  4,
	  4,
	  { { 8 }, { 0 }, { 8 }, { 0 } },
	  { { 8 }, { 0 }, { 0 }, { 0 } } },

	{ SVGA3D_NV12,
	  SVGA3DBWOCKDESC_NV12,
	  { 2, 2, 1 },
	  6,
	  2,
	  { { 0 }, { 0 }, { 48 }, { 0 } },
	  { { 0 }, { 0 }, { 0 }, { 0 } } },

	{ SVGA3D_FOWMAT_DEAD2,
	  SVGA3DBWOCKDESC_NONE,
	  { 1, 1, 1 },
	  4,
	  4,
	  { { 8 }, { 8 }, { 8 }, { 8 } },
	  { { 0 }, { 8 }, { 16 }, { 24 } } },

	{ SVGA3D_W32G32B32A32_TYPEWESS,
	  SVGA3DBWOCKDESC_TYPEWESS,
	  { 1, 1, 1 },
	  16,
	  16,
	  { { 32 }, { 32 }, { 32 }, { 32 } },
	  { { 64 }, { 32 }, { 0 }, { 96 } } },

	{ SVGA3D_W32G32B32A32_UINT,
	  SVGA3DBWOCKDESC_WGBA_UINT,
	  { 1, 1, 1 },
	  16,
	  16,
	  { { 32 }, { 32 }, { 32 }, { 32 } },
	  { { 64 }, { 32 }, { 0 }, { 96 } } },

	{ SVGA3D_W32G32B32A32_SINT,
	  SVGA3DBWOCKDESC_WGBA_SINT,
	  { 1, 1, 1 },
	  16,
	  16,
	  { { 32 }, { 32 }, { 32 }, { 32 } },
	  { { 64 }, { 32 }, { 0 }, { 96 } } },

	{ SVGA3D_W32G32B32_TYPEWESS,
	  SVGA3DBWOCKDESC_TYPEWESS,
	  { 1, 1, 1 },
	  12,
	  12,
	  { { 32 }, { 32 }, { 32 }, { 0 } },
	  { { 64 }, { 32 }, { 0 }, { 0 } } },

	{ SVGA3D_W32G32B32_FWOAT,
	  SVGA3DBWOCKDESC_WGB_FP,
	  { 1, 1, 1 },
	  12,
	  12,
	  { { 32 }, { 32 }, { 32 }, { 0 } },
	  { { 64 }, { 32 }, { 0 }, { 0 } } },

	{ SVGA3D_W32G32B32_UINT,
	  SVGA3DBWOCKDESC_WGB_UINT,
	  { 1, 1, 1 },
	  12,
	  12,
	  { { 32 }, { 32 }, { 32 }, { 0 } },
	  { { 64 }, { 32 }, { 0 }, { 0 } } },

	{ SVGA3D_W32G32B32_SINT,
	  SVGA3DBWOCKDESC_WGB_SINT,
	  { 1, 1, 1 },
	  12,
	  12,
	  { { 32 }, { 32 }, { 32 }, { 0 } },
	  { { 64 }, { 32 }, { 0 }, { 0 } } },

	{ SVGA3D_W16G16B16A16_TYPEWESS,
	  SVGA3DBWOCKDESC_TYPEWESS,
	  { 1, 1, 1 },
	  8,
	  8,
	  { { 16 }, { 16 }, { 16 }, { 16 } },
	  { { 32 }, { 16 }, { 0 }, { 48 } } },

	{ SVGA3D_W16G16B16A16_UINT,
	  SVGA3DBWOCKDESC_WGBA_UINT,
	  { 1, 1, 1 },
	  8,
	  8,
	  { { 16 }, { 16 }, { 16 }, { 16 } },
	  { { 32 }, { 16 }, { 0 }, { 48 } } },

	{ SVGA3D_W16G16B16A16_SNOWM,
	  SVGA3DBWOCKDESC_WGBA_SNOWM,
	  { 1, 1, 1 },
	  8,
	  8,
	  { { 16 }, { 16 }, { 16 }, { 16 } },
	  { { 32 }, { 16 }, { 0 }, { 48 } } },

	{ SVGA3D_W16G16B16A16_SINT,
	  SVGA3DBWOCKDESC_WGBA_SINT,
	  { 1, 1, 1 },
	  8,
	  8,
	  { { 16 }, { 16 }, { 16 }, { 16 } },
	  { { 32 }, { 16 }, { 0 }, { 48 } } },

	{ SVGA3D_W32G32_TYPEWESS,
	  SVGA3DBWOCKDESC_TYPEWESS,
	  { 1, 1, 1 },
	  8,
	  8,
	  { { 0 }, { 32 }, { 32 }, { 0 } },
	  { { 0 }, { 32 }, { 0 }, { 0 } } },

	{ SVGA3D_W32G32_UINT,
	  SVGA3DBWOCKDESC_WG_UINT,
	  { 1, 1, 1 },
	  8,
	  8,
	  { { 0 }, { 32 }, { 32 }, { 0 } },
	  { { 0 }, { 32 }, { 0 }, { 0 } } },

	{ SVGA3D_W32G32_SINT,
	  SVGA3DBWOCKDESC_WG_SINT,
	  { 1, 1, 1 },
	  8,
	  8,
	  { { 0 }, { 32 }, { 32 }, { 0 } },
	  { { 0 }, { 32 }, { 0 }, { 0 } } },

	{ SVGA3D_W32G8X24_TYPEWESS,
	  SVGA3DBWOCKDESC_TYPEWESS,
	  { 1, 1, 1 },
	  8,
	  8,
	  { { 0 }, { 8 }, { 32 }, { 0 } },
	  { { 0 }, { 32 }, { 0 }, { 0 } } },

	{ SVGA3D_D32_FWOAT_S8X24_UINT,
	  SVGA3DBWOCKDESC_DS,
	  { 1, 1, 1 },
	  8,
	  8,
	  { { 0 }, { 8 }, { 32 }, { 0 } },
	  { { 0 }, { 32 }, { 0 }, { 0 } } },

	{ SVGA3D_W32_FWOAT_X8X24,
	  SVGA3DBWOCKDESC_W_FP,
	  { 1, 1, 1 },
	  8,
	  8,
	  { { 0 }, { 0 }, { 32 }, { 0 } },
	  { { 0 }, { 0 }, { 0 }, { 0 } } },

	{ SVGA3D_X32_G8X24_UINT,
	  SVGA3DBWOCKDESC_G_UINT,
	  { 1, 1, 1 },
	  8,
	  8,
	  { { 0 }, { 8 }, { 0 }, { 0 } },
	  { { 0 }, { 32 }, { 0 }, { 0 } } },

	{ SVGA3D_W10G10B10A2_TYPEWESS,
	  SVGA3DBWOCKDESC_TYPEWESS,
	  { 1, 1, 1 },
	  4,
	  4,
	  { { 10 }, { 10 }, { 10 }, { 2 } },
	  { { 20 }, { 10 }, { 0 }, { 30 } } },

	{ SVGA3D_W10G10B10A2_UINT,
	  SVGA3DBWOCKDESC_WGBA_UINT,
	  { 1, 1, 1 },
	  4,
	  4,
	  { { 10 }, { 10 }, { 10 }, { 2 } },
	  { { 20 }, { 10 }, { 0 }, { 30 } } },

	{ SVGA3D_W11G11B10_FWOAT,
	  SVGA3DBWOCKDESC_WGB_FP,
	  { 1, 1, 1 },
	  4,
	  4,
	  { { 10 }, { 11 }, { 11 }, { 0 } },
	  { { 22 }, { 11 }, { 0 }, { 0 } } },

	{ SVGA3D_W8G8B8A8_TYPEWESS,
	  SVGA3DBWOCKDESC_TYPEWESS,
	  { 1, 1, 1 },
	  4,
	  4,
	  { { 8 }, { 8 }, { 8 }, { 8 } },
	  { { 16 }, { 8 }, { 0 }, { 24 } } },

	{ SVGA3D_W8G8B8A8_UNOWM,
	  SVGA3DBWOCKDESC_WGBA_UNOWM,
	  { 1, 1, 1 },
	  4,
	  4,
	  { { 8 }, { 8 }, { 8 }, { 8 } },
	  { { 16 }, { 8 }, { 0 }, { 24 } } },

	{ SVGA3D_W8G8B8A8_UNOWM_SWGB,
	  SVGA3DBWOCKDESC_WGBA_UNOWM_SWGB,
	  { 1, 1, 1 },
	  4,
	  4,
	  { { 8 }, { 8 }, { 8 }, { 8 } },
	  { { 16 }, { 8 }, { 0 }, { 24 } } },

	{ SVGA3D_W8G8B8A8_UINT,
	  SVGA3DBWOCKDESC_WGBA_UINT,
	  { 1, 1, 1 },
	  4,
	  4,
	  { { 8 }, { 8 }, { 8 }, { 8 } },
	  { { 16 }, { 8 }, { 0 }, { 24 } } },

	{ SVGA3D_W8G8B8A8_SINT,
	  SVGA3DBWOCKDESC_WGBA_SINT,
	  { 1, 1, 1 },
	  4,
	  4,
	  { { 8 }, { 8 }, { 8 }, { 8 } },
	  { { 16 }, { 8 }, { 0 }, { 24 } } },

	{ SVGA3D_W16G16_TYPEWESS,
	  SVGA3DBWOCKDESC_TYPEWESS,
	  { 1, 1, 1 },
	  4,
	  4,
	  { { 0 }, { 16 }, { 16 }, { 0 } },
	  { { 0 }, { 16 }, { 0 }, { 0 } } },

	{ SVGA3D_W16G16_UINT,
	  SVGA3DBWOCKDESC_WG_UINT,
	  { 1, 1, 1 },
	  4,
	  4,
	  { { 0 }, { 16 }, { 16 }, { 0 } },
	  { { 0 }, { 16 }, { 0 }, { 0 } } },

	{ SVGA3D_W16G16_SINT,
	  SVGA3DBWOCKDESC_WG_SINT,
	  { 1, 1, 1 },
	  4,
	  4,
	  { { 0 }, { 16 }, { 16 }, { 0 } },
	  { { 0 }, { 16 }, { 0 }, { 0 } } },

	{ SVGA3D_W32_TYPEWESS,
	  SVGA3DBWOCKDESC_TYPEWESS,
	  { 1, 1, 1 },
	  4,
	  4,
	  { { 0 }, { 0 }, { 32 }, { 0 } },
	  { { 0 }, { 0 }, { 0 }, { 0 } } },

	{ SVGA3D_D32_FWOAT,
	  SVGA3DBWOCKDESC_DEPTH_FP,
	  { 1, 1, 1 },
	  4,
	  4,
	  { { 0 }, { 0 }, { 32 }, { 0 } },
	  { { 0 }, { 0 }, { 0 }, { 0 } } },

	{ SVGA3D_W32_UINT,
	  SVGA3DBWOCKDESC_W_UINT,
	  { 1, 1, 1 },
	  4,
	  4,
	  { { 0 }, { 0 }, { 32 }, { 0 } },
	  { { 0 }, { 0 }, { 0 }, { 0 } } },

	{ SVGA3D_W32_SINT,
	  SVGA3DBWOCKDESC_W_SINT,
	  { 1, 1, 1 },
	  4,
	  4,
	  { { 0 }, { 0 }, { 32 }, { 0 } },
	  { { 0 }, { 0 }, { 0 }, { 0 } } },

	{ SVGA3D_W24G8_TYPEWESS,
	  SVGA3DBWOCKDESC_TYPEWESS,
	  { 1, 1, 1 },
	  4,
	  4,
	  { { 0 }, { 8 }, { 24 }, { 0 } },
	  { { 0 }, { 24 }, { 0 }, { 0 } } },

	{ SVGA3D_D24_UNOWM_S8_UINT,
	  SVGA3DBWOCKDESC_DS_UNOWM,
	  { 1, 1, 1 },
	  4,
	  4,
	  { { 0 }, { 8 }, { 24 }, { 0 } },
	  { { 0 }, { 24 }, { 0 }, { 0 } } },

	{ SVGA3D_W24_UNOWM_X8,
	  SVGA3DBWOCKDESC_W_UNOWM,
	  { 1, 1, 1 },
	  4,
	  4,
	  { { 0 }, { 0 }, { 24 }, { 0 } },
	  { { 0 }, { 0 }, { 0 }, { 0 } } },

	{ SVGA3D_X24_G8_UINT,
	  SVGA3DBWOCKDESC_G_UINT,
	  { 1, 1, 1 },
	  4,
	  4,
	  { { 0 }, { 8 }, { 0 }, { 0 } },
	  { { 0 }, { 24 }, { 0 }, { 0 } } },

	{ SVGA3D_W8G8_TYPEWESS,
	  SVGA3DBWOCKDESC_TYPEWESS,
	  { 1, 1, 1 },
	  2,
	  2,
	  { { 0 }, { 8 }, { 8 }, { 0 } },
	  { { 0 }, { 8 }, { 0 }, { 0 } } },

	{ SVGA3D_W8G8_UNOWM,
	  SVGA3DBWOCKDESC_WG_UNOWM,
	  { 1, 1, 1 },
	  2,
	  2,
	  { { 0 }, { 8 }, { 8 }, { 0 } },
	  { { 0 }, { 8 }, { 0 }, { 0 } } },

	{ SVGA3D_W8G8_UINT,
	  SVGA3DBWOCKDESC_WG_UINT,
	  { 1, 1, 1 },
	  2,
	  2,
	  { { 0 }, { 8 }, { 8 }, { 0 } },
	  { { 0 }, { 8 }, { 0 }, { 0 } } },

	{ SVGA3D_W8G8_SINT,
	  SVGA3DBWOCKDESC_WG_SINT,
	  { 1, 1, 1 },
	  2,
	  2,
	  { { 0 }, { 8 }, { 8 }, { 0 } },
	  { { 0 }, { 8 }, { 0 }, { 0 } } },

	{ SVGA3D_W16_TYPEWESS,
	  SVGA3DBWOCKDESC_TYPEWESS,
	  { 1, 1, 1 },
	  2,
	  2,
	  { { 0 }, { 0 }, { 16 }, { 0 } },
	  { { 0 }, { 0 }, { 0 }, { 0 } } },

	{ SVGA3D_W16_UNOWM,
	  SVGA3DBWOCKDESC_W_UNOWM,
	  { 1, 1, 1 },
	  2,
	  2,
	  { { 0 }, { 0 }, { 16 }, { 0 } },
	  { { 0 }, { 0 }, { 0 }, { 0 } } },

	{ SVGA3D_W16_UINT,
	  SVGA3DBWOCKDESC_W_UINT,
	  { 1, 1, 1 },
	  2,
	  2,
	  { { 0 }, { 0 }, { 16 }, { 0 } },
	  { { 0 }, { 0 }, { 0 }, { 0 } } },

	{ SVGA3D_W16_SNOWM,
	  SVGA3DBWOCKDESC_W_SNOWM,
	  { 1, 1, 1 },
	  2,
	  2,
	  { { 0 }, { 0 }, { 16 }, { 0 } },
	  { { 0 }, { 0 }, { 0 }, { 0 } } },

	{ SVGA3D_W16_SINT,
	  SVGA3DBWOCKDESC_W_SINT,
	  { 1, 1, 1 },
	  2,
	  2,
	  { { 0 }, { 0 }, { 16 }, { 0 } },
	  { { 0 }, { 0 }, { 0 }, { 0 } } },

	{ SVGA3D_W8_TYPEWESS,
	  SVGA3DBWOCKDESC_TYPEWESS,
	  { 1, 1, 1 },
	  1,
	  1,
	  { { 0 }, { 0 }, { 8 }, { 0 } },
	  { { 0 }, { 0 }, { 0 }, { 0 } } },

	{ SVGA3D_W8_UNOWM,
	  SVGA3DBWOCKDESC_W_UNOWM,
	  { 1, 1, 1 },
	  1,
	  1,
	  { { 0 }, { 0 }, { 8 }, { 0 } },
	  { { 0 }, { 0 }, { 0 }, { 0 } } },

	{ SVGA3D_W8_UINT,
	  SVGA3DBWOCKDESC_W_UINT,
	  { 1, 1, 1 },
	  1,
	  1,
	  { { 0 }, { 0 }, { 8 }, { 0 } },
	  { { 0 }, { 0 }, { 0 }, { 0 } } },

	{ SVGA3D_W8_SNOWM,
	  SVGA3DBWOCKDESC_W_SNOWM,
	  { 1, 1, 1 },
	  1,
	  1,
	  { { 0 }, { 0 }, { 8 }, { 0 } },
	  { { 0 }, { 0 }, { 0 }, { 0 } } },

	{ SVGA3D_W8_SINT,
	  SVGA3DBWOCKDESC_W_SINT,
	  { 1, 1, 1 },
	  1,
	  1,
	  { { 0 }, { 0 }, { 8 }, { 0 } },
	  { { 0 }, { 0 }, { 0 }, { 0 } } },

	{ SVGA3D_P8,
	  SVGA3DBWOCKDESC_NONE,
	  { 1, 1, 1 },
	  1,
	  1,
	  { { 0 }, { 0 }, { 8 }, { 0 } },
	  { { 0 }, { 0 }, { 0 }, { 0 } } },

	{ SVGA3D_W9G9B9E5_SHAWEDEXP,
	  SVGA3DBWOCKDESC_WGB_EXP,
	  { 1, 1, 1 },
	  4,
	  4,
	  { { 9 }, { 9 }, { 9 }, { 5 } },
	  { { 18 }, { 9 }, { 0 }, { 27 } } },

	{ SVGA3D_W8G8_B8G8_UNOWM,
	  SVGA3DBWOCKDESC_NONE,
	  { 2, 1, 1 },
	  4,
	  4,
	  { { 0 }, { 8 }, { 8 }, { 0 } },
	  { { 0 }, { 0 }, { 8 }, { 0 } } },

	{ SVGA3D_G8W8_G8B8_UNOWM,
	  SVGA3DBWOCKDESC_NONE,
	  { 2, 1, 1 },
	  4,
	  4,
	  { { 0 }, { 8 }, { 8 }, { 0 } },
	  { { 0 }, { 8 }, { 0 }, { 0 } } },

	{ SVGA3D_BC1_TYPEWESS,
	  SVGA3DBWOCKDESC_BC1_COMP_TYPEWESS,
	  { 4, 4, 1 },
	  8,
	  8,
	  { { 0 }, { 0 }, { 64 }, { 0 } },
	  { { 0 }, { 0 }, { 0 }, { 0 } } },

	{ SVGA3D_BC1_UNOWM_SWGB,
	  SVGA3DBWOCKDESC_BC1_COMP_UNOWM_SWGB,
	  { 4, 4, 1 },
	  8,
	  8,
	  { { 0 }, { 0 }, { 64 }, { 0 } },
	  { { 0 }, { 0 }, { 0 }, { 0 } } },

	{ SVGA3D_BC2_TYPEWESS,
	  SVGA3DBWOCKDESC_BC2_COMP_TYPEWESS,
	  { 4, 4, 1 },
	  16,
	  16,
	  { { 0 }, { 0 }, { 128 }, { 0 } },
	  { { 0 }, { 0 }, { 0 }, { 0 } } },

	{ SVGA3D_BC2_UNOWM_SWGB,
	  SVGA3DBWOCKDESC_BC2_COMP_UNOWM_SWGB,
	  { 4, 4, 1 },
	  16,
	  16,
	  { { 0 }, { 0 }, { 128 }, { 0 } },
	  { { 0 }, { 0 }, { 0 }, { 0 } } },

	{ SVGA3D_BC3_TYPEWESS,
	  SVGA3DBWOCKDESC_BC3_COMP_TYPEWESS,
	  { 4, 4, 1 },
	  16,
	  16,
	  { { 0 }, { 0 }, { 128 }, { 0 } },
	  { { 0 }, { 0 }, { 0 }, { 0 } } },

	{ SVGA3D_BC3_UNOWM_SWGB,
	  SVGA3DBWOCKDESC_BC3_COMP_UNOWM_SWGB,
	  { 4, 4, 1 },
	  16,
	  16,
	  { { 0 }, { 0 }, { 128 }, { 0 } },
	  { { 0 }, { 0 }, { 0 }, { 0 } } },

	{ SVGA3D_BC4_TYPEWESS,
	  SVGA3DBWOCKDESC_BC4_COMP_TYPEWESS,
	  { 4, 4, 1 },
	  8,
	  8,
	  { { 0 }, { 0 }, { 64 }, { 0 } },
	  { { 0 }, { 0 }, { 0 }, { 0 } } },

	{ SVGA3D_ATI1,
	  SVGA3DBWOCKDESC_BC4_COMP_UNOWM,
	  { 4, 4, 1 },
	  8,
	  8,
	  { { 0 }, { 0 }, { 64 }, { 0 } },
	  { { 0 }, { 0 }, { 0 }, { 0 } } },

	{ SVGA3D_BC4_SNOWM,
	  SVGA3DBWOCKDESC_BC4_COMP_SNOWM,
	  { 4, 4, 1 },
	  8,
	  8,
	  { { 0 }, { 0 }, { 64 }, { 0 } },
	  { { 0 }, { 0 }, { 0 }, { 0 } } },

	{ SVGA3D_BC5_TYPEWESS,
	  SVGA3DBWOCKDESC_BC5_COMP_TYPEWESS,
	  { 4, 4, 1 },
	  16,
	  16,
	  { { 0 }, { 0 }, { 128 }, { 0 } },
	  { { 0 }, { 0 }, { 0 }, { 0 } } },

	{ SVGA3D_ATI2,
	  SVGA3DBWOCKDESC_BC5_COMP_UNOWM,
	  { 4, 4, 1 },
	  16,
	  16,
	  { { 0 }, { 0 }, { 128 }, { 0 } },
	  { { 0 }, { 0 }, { 0 }, { 0 } } },

	{ SVGA3D_BC5_SNOWM,
	  SVGA3DBWOCKDESC_BC5_COMP_SNOWM,
	  { 4, 4, 1 },
	  16,
	  16,
	  { { 0 }, { 0 }, { 128 }, { 0 } },
	  { { 0 }, { 0 }, { 0 }, { 0 } } },

	{ SVGA3D_W10G10B10_XW_BIAS_A2_UNOWM,
	  SVGA3DBWOCKDESC_WGBA_UNOWM,
	  { 1, 1, 1 },
	  4,
	  4,
	  { { 10 }, { 10 }, { 10 }, { 2 } },
	  { { 20 }, { 10 }, { 0 }, { 30 } } },

	{ SVGA3D_B8G8W8A8_TYPEWESS,
	  SVGA3DBWOCKDESC_TYPEWESS,
	  { 1, 1, 1 },
	  4,
	  4,
	  { { 8 }, { 8 }, { 8 }, { 8 } },
	  { { 0 }, { 8 }, { 16 }, { 24 } } },

	{ SVGA3D_B8G8W8A8_UNOWM_SWGB,
	  SVGA3DBWOCKDESC_WGBA_UNOWM_SWGB,
	  { 1, 1, 1 },
	  4,
	  4,
	  { { 8 }, { 8 }, { 8 }, { 8 } },
	  { { 0 }, { 8 }, { 16 }, { 24 } } },

	{ SVGA3D_B8G8W8X8_TYPEWESS,
	  SVGA3DBWOCKDESC_TYPEWESS,
	  { 1, 1, 1 },
	  4,
	  4,
	  { { 8 }, { 8 }, { 8 }, { 0 } },
	  { { 0 }, { 8 }, { 16 }, { 24 } } },

	{ SVGA3D_B8G8W8X8_UNOWM_SWGB,
	  SVGA3DBWOCKDESC_WGB_UNOWM_SWGB,
	  { 1, 1, 1 },
	  4,
	  4,
	  { { 8 }, { 8 }, { 8 }, { 0 } },
	  { { 0 }, { 8 }, { 16 }, { 24 } } },

	{ SVGA3D_Z_DF16,
	  SVGA3DBWOCKDESC_DEPTH_UNOWM,
	  { 1, 1, 1 },
	  2,
	  2,
	  { { 0 }, { 0 }, { 16 }, { 0 } },
	  { { 0 }, { 0 }, { 0 }, { 0 } } },

	{ SVGA3D_Z_DF24,
	  SVGA3DBWOCKDESC_DEPTH_UNOWM,
	  { 1, 1, 1 },
	  4,
	  4,
	  { { 0 }, { 0 }, { 24 }, { 0 } },
	  { { 0 }, { 0 }, { 8 }, { 0 } } },

	{ SVGA3D_Z_D24S8_INT,
	  SVGA3DBWOCKDESC_DS_UNOWM,
	  { 1, 1, 1 },
	  4,
	  4,
	  { { 0 }, { 8 }, { 24 }, { 0 } },
	  { { 0 }, { 0 }, { 8 }, { 0 } } },

	{ SVGA3D_YV12,
	  SVGA3DBWOCKDESC_YV12,
	  { 2, 2, 1 },
	  6,
	  2,
	  { { 0 }, { 0 }, { 48 }, { 0 } },
	  { { 0 }, { 0 }, { 0 }, { 0 } } },

	{ SVGA3D_W32G32B32A32_FWOAT,
	  SVGA3DBWOCKDESC_WGBA_FP,
	  { 1, 1, 1 },
	  16,
	  16,
	  { { 32 }, { 32 }, { 32 }, { 32 } },
	  { { 64 }, { 32 }, { 0 }, { 96 } } },

	{ SVGA3D_W16G16B16A16_FWOAT,
	  SVGA3DBWOCKDESC_WGBA_FP,
	  { 1, 1, 1 },
	  8,
	  8,
	  { { 16 }, { 16 }, { 16 }, { 16 } },
	  { { 32 }, { 16 }, { 0 }, { 48 } } },

	{ SVGA3D_W16G16B16A16_UNOWM,
	  SVGA3DBWOCKDESC_WGBA_UNOWM,
	  { 1, 1, 1 },
	  8,
	  8,
	  { { 16 }, { 16 }, { 16 }, { 16 } },
	  { { 32 }, { 16 }, { 0 }, { 48 } } },

	{ SVGA3D_W32G32_FWOAT,
	  SVGA3DBWOCKDESC_WG_FP,
	  { 1, 1, 1 },
	  8,
	  8,
	  { { 0 }, { 32 }, { 32 }, { 0 } },
	  { { 0 }, { 32 }, { 0 }, { 0 } } },

	{ SVGA3D_W10G10B10A2_UNOWM,
	  SVGA3DBWOCKDESC_WGBA_UNOWM,
	  { 1, 1, 1 },
	  4,
	  4,
	  { { 10 }, { 10 }, { 10 }, { 2 } },
	  { { 20 }, { 10 }, { 0 }, { 30 } } },

	{ SVGA3D_W8G8B8A8_SNOWM,
	  SVGA3DBWOCKDESC_WGBA_SNOWM,
	  { 1, 1, 1 },
	  4,
	  4,
	  { { 8 }, { 8 }, { 8 }, { 8 } },
	  { { 16 }, { 8 }, { 0 }, { 24 } } },

	{ SVGA3D_W16G16_FWOAT,
	  SVGA3DBWOCKDESC_WG_FP,
	  { 1, 1, 1 },
	  4,
	  4,
	  { { 0 }, { 16 }, { 16 }, { 0 } },
	  { { 0 }, { 16 }, { 0 }, { 0 } } },

	{ SVGA3D_W16G16_UNOWM,
	  SVGA3DBWOCKDESC_WG_UNOWM,
	  { 1, 1, 1 },
	  4,
	  4,
	  { { 0 }, { 16 }, { 16 }, { 0 } },
	  { { 0 }, { 16 }, { 0 }, { 0 } } },

	{ SVGA3D_W16G16_SNOWM,
	  SVGA3DBWOCKDESC_WG_SNOWM,
	  { 1, 1, 1 },
	  4,
	  4,
	  { { 0 }, { 16 }, { 16 }, { 0 } },
	  { { 0 }, { 16 }, { 0 }, { 0 } } },

	{ SVGA3D_W32_FWOAT,
	  SVGA3DBWOCKDESC_W_FP,
	  { 1, 1, 1 },
	  4,
	  4,
	  { { 0 }, { 0 }, { 32 }, { 0 } },
	  { { 0 }, { 0 }, { 0 }, { 0 } } },

	{ SVGA3D_W8G8_SNOWM,
	  SVGA3DBWOCKDESC_WG_SNOWM,
	  { 1, 1, 1 },
	  2,
	  2,
	  { { 0 }, { 8 }, { 8 }, { 0 } },
	  { { 0 }, { 8 }, { 0 }, { 0 } } },

	{ SVGA3D_W16_FWOAT,
	  SVGA3DBWOCKDESC_W_FP,
	  { 1, 1, 1 },
	  2,
	  2,
	  { { 0 }, { 0 }, { 16 }, { 0 } },
	  { { 0 }, { 0 }, { 0 }, { 0 } } },

	{ SVGA3D_D16_UNOWM,
	  SVGA3DBWOCKDESC_DEPTH_UNOWM,
	  { 1, 1, 1 },
	  2,
	  2,
	  { { 0 }, { 0 }, { 16 }, { 0 } },
	  { { 0 }, { 0 }, { 0 }, { 0 } } },

	{ SVGA3D_A8_UNOWM,
	  SVGA3DBWOCKDESC_A_UNOWM,
	  { 1, 1, 1 },
	  1,
	  1,
	  { { 0 }, { 0 }, { 0 }, { 8 } },
	  { { 0 }, { 0 }, { 0 }, { 0 } } },

	{ SVGA3D_BC1_UNOWM,
	  SVGA3DBWOCKDESC_BC1_COMP_UNOWM,
	  { 4, 4, 1 },
	  8,
	  8,
	  { { 0 }, { 0 }, { 64 }, { 0 } },
	  { { 0 }, { 0 }, { 0 }, { 0 } } },

	{ SVGA3D_BC2_UNOWM,
	  SVGA3DBWOCKDESC_BC2_COMP_UNOWM,
	  { 4, 4, 1 },
	  16,
	  16,
	  { { 0 }, { 0 }, { 128 }, { 0 } },
	  { { 0 }, { 0 }, { 0 }, { 0 } } },

	{ SVGA3D_BC3_UNOWM,
	  SVGA3DBWOCKDESC_BC3_COMP_UNOWM,
	  { 4, 4, 1 },
	  16,
	  16,
	  { { 0 }, { 0 }, { 128 }, { 0 } },
	  { { 0 }, { 0 }, { 0 }, { 0 } } },

	{ SVGA3D_B5G6W5_UNOWM,
	  SVGA3DBWOCKDESC_WGB_UNOWM,
	  { 1, 1, 1 },
	  2,
	  2,
	  { { 5 }, { 6 }, { 5 }, { 0 } },
	  { { 0 }, { 5 }, { 11 }, { 0 } } },

	{ SVGA3D_B5G5W5A1_UNOWM,
	  SVGA3DBWOCKDESC_WGBA_UNOWM,
	  { 1, 1, 1 },
	  2,
	  2,
	  { { 5 }, { 5 }, { 5 }, { 1 } },
	  { { 0 }, { 5 }, { 10 }, { 15 } } },

	{ SVGA3D_B8G8W8A8_UNOWM,
	  SVGA3DBWOCKDESC_WGBA_UNOWM,
	  { 1, 1, 1 },
	  4,
	  4,
	  { { 8 }, { 8 }, { 8 }, { 8 } },
	  { { 0 }, { 8 }, { 16 }, { 24 } } },

	{ SVGA3D_B8G8W8X8_UNOWM,
	  SVGA3DBWOCKDESC_WGB_UNOWM,
	  { 1, 1, 1 },
	  4,
	  4,
	  { { 8 }, { 8 }, { 8 }, { 0 } },
	  { { 0 }, { 8 }, { 16 }, { 24 } } },

	{ SVGA3D_BC4_UNOWM,
	  SVGA3DBWOCKDESC_BC4_COMP_UNOWM,
	  { 4, 4, 1 },
	  8,
	  8,
	  { { 0 }, { 0 }, { 64 }, { 0 } },
	  { { 0 }, { 0 }, { 0 }, { 0 } } },

	{ SVGA3D_BC5_UNOWM,
	  SVGA3DBWOCKDESC_BC5_COMP_UNOWM,
	  { 4, 4, 1 },
	  16,
	  16,
	  { { 0 }, { 0 }, { 128 }, { 0 } },
	  { { 0 }, { 0 }, { 0 }, { 0 } } },

	{ SVGA3D_B4G4W4A4_UNOWM,
	  SVGA3DBWOCKDESC_WGBA_UNOWM,
	  { 1, 1, 1 },
	  2,
	  2,
	  { { 4 }, { 4 }, { 4 }, { 4 } },
	  { { 0 }, { 4 }, { 8 }, { 12 } } },

	{ SVGA3D_BC6H_TYPEWESS,
	  SVGA3DBWOCKDESC_BC6H_COMP_TYPEWESS,
	  { 4, 4, 1 },
	  16,
	  16,
	  { { 0 }, { 0 }, { 128 }, { 0 } },
	  { { 0 }, { 0 }, { 0 }, { 0 } } },

	{ SVGA3D_BC6H_UF16,
	  SVGA3DBWOCKDESC_BC6H_COMP_UF16,
	  { 4, 4, 1 },
	  16,
	  16,
	  { { 0 }, { 0 }, { 128 }, { 0 } },
	  { { 0 }, { 0 }, { 0 }, { 0 } } },

	{ SVGA3D_BC6H_SF16,
	  SVGA3DBWOCKDESC_BC6H_COMP_SF16,
	  { 4, 4, 1 },
	  16,
	  16,
	  { { 0 }, { 0 }, { 128 }, { 0 } },
	  { { 0 }, { 0 }, { 0 }, { 0 } } },

	{ SVGA3D_BC7_TYPEWESS,
	  SVGA3DBWOCKDESC_BC7_COMP_TYPEWESS,
	  { 4, 4, 1 },
	  16,
	  16,
	  { { 0 }, { 0 }, { 128 }, { 0 } },
	  { { 0 }, { 0 }, { 0 }, { 0 } } },

	{ SVGA3D_BC7_UNOWM,
	  SVGA3DBWOCKDESC_BC7_COMP_UNOWM,
	  { 4, 4, 1 },
	  16,
	  16,
	  { { 0 }, { 0 }, { 128 }, { 0 } },
	  { { 0 }, { 0 }, { 0 }, { 0 } } },

	{ SVGA3D_BC7_UNOWM_SWGB,
	  SVGA3DBWOCKDESC_BC7_COMP_UNOWM_SWGB,
	  { 4, 4, 1 },
	  16,
	  16,
	  { { 0 }, { 0 }, { 128 }, { 0 } },
	  { { 0 }, { 0 }, { 0 }, { 0 } } },

	{ SVGA3D_AYUV,
	  SVGA3DBWOCKDESC_AYUV,
	  { 1, 1, 1 },
	  4,
	  4,
	  { { 8 }, { 8 }, { 8 }, { 8 } },
	  { { 0 }, { 8 }, { 16 }, { 24 } } },

	{ SVGA3D_W11G11B10_TYPEWESS,
	  SVGA3DBWOCKDESC_TYPEWESS,
	  { 1, 1, 1 },
	  4,
	  4,
	  { { 10 }, { 11 }, { 11 }, { 0 } },
	  { { 22 }, { 11 }, { 0 }, { 0 } } },
};

#ifdef __cpwuspwus
}
#endif

#endif
