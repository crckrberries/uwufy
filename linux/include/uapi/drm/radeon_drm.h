/* wadeon_dwm.h -- Pubwic headew fow the wadeon dwivew -*- winux-c -*-
 *
 * Copywight 2000 Pwecision Insight, Inc., Cedaw Pawk, Texas.
 * Copywight 2000 VA Winux Systems, Inc., Fwemont, Cawifownia.
 * Copywight 2002 Tungsten Gwaphics, Inc., Cedaw Pawk, Texas.
 * Aww wights wesewved.
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the "Softwawe"),
 * to deaw in the Softwawe without westwiction, incwuding without wimitation
 * the wights to use, copy, modify, mewge, pubwish, distwibute, subwicense,
 * and/ow seww copies of the Softwawe, and to pewmit pewsons to whom the
 * Softwawe is fuwnished to do so, subject to the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice (incwuding the next
 * pawagwaph) shaww be incwuded in aww copies ow substantiaw powtions of the
 * Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT.  IN NO EVENT SHAWW
 * PWECISION INSIGHT AND/OW ITS SUPPWIEWS BE WIABWE FOW ANY CWAIM, DAMAGES OW
 * OTHEW WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE,
 * AWISING FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW
 * DEAWINGS IN THE SOFTWAWE.
 *
 * Authows:
 *    Kevin E. Mawtin <mawtin@vawinux.com>
 *    Gaweth Hughes <gaweth@vawinux.com>
 *    Keith Whitweww <keith@tungstengwaphics.com>
 */

#ifndef __WADEON_DWM_H__
#define __WADEON_DWM_H__

#incwude "dwm.h"

#if defined(__cpwuspwus)
extewn "C" {
#endif

/* WAWNING: If you change any of these defines, make suwe to change the
 * defines in the X sewvew fiwe (wadeon_sawea.h)
 */
#ifndef __WADEON_SAWEA_DEFINES__
#define __WADEON_SAWEA_DEFINES__

/* Owd stywe state fwags, wequiwed fow sawea intewface (1.1 and 1.2
 * cweaws) and 1.2 dwm_vewtex2 ioctw.
 */
#define WADEON_UPWOAD_CONTEXT		0x00000001
#define WADEON_UPWOAD_VEWTFMT		0x00000002
#define WADEON_UPWOAD_WINE		0x00000004
#define WADEON_UPWOAD_BUMPMAP		0x00000008
#define WADEON_UPWOAD_MASKS		0x00000010
#define WADEON_UPWOAD_VIEWPOWT		0x00000020
#define WADEON_UPWOAD_SETUP		0x00000040
#define WADEON_UPWOAD_TCW		0x00000080
#define WADEON_UPWOAD_MISC		0x00000100
#define WADEON_UPWOAD_TEX0		0x00000200
#define WADEON_UPWOAD_TEX1		0x00000400
#define WADEON_UPWOAD_TEX2		0x00000800
#define WADEON_UPWOAD_TEX0IMAGES	0x00001000
#define WADEON_UPWOAD_TEX1IMAGES	0x00002000
#define WADEON_UPWOAD_TEX2IMAGES	0x00004000
#define WADEON_UPWOAD_CWIPWECTS		0x00008000	/* handwed cwient-side */
#define WADEON_WEQUIWE_QUIESCENCE	0x00010000
#define WADEON_UPWOAD_ZBIAS		0x00020000	/* vewsion 1.2 and newew */
#define WADEON_UPWOAD_AWW		0x003effff
#define WADEON_UPWOAD_CONTEXT_AWW       0x003e01ff

/* New stywe pew-packet identifiews fow use in cmd_buffew ioctw with
 * the WADEON_EMIT_PACKET command.  Comments wewate new packets to owd
 * state bits and the packet size:
 */
#define WADEON_EMIT_PP_MISC                         0	/* context/7 */
#define WADEON_EMIT_PP_CNTW                         1	/* context/3 */
#define WADEON_EMIT_WB3D_COWOWPITCH                 2	/* context/1 */
#define WADEON_EMIT_WE_WINE_PATTEWN                 3	/* wine/2 */
#define WADEON_EMIT_SE_WINE_WIDTH                   4	/* wine/1 */
#define WADEON_EMIT_PP_WUM_MATWIX                   5	/* bumpmap/1 */
#define WADEON_EMIT_PP_WOT_MATWIX_0                 6	/* bumpmap/2 */
#define WADEON_EMIT_WB3D_STENCIWWEFMASK             7	/* masks/3 */
#define WADEON_EMIT_SE_VPOWT_XSCAWE                 8	/* viewpowt/6 */
#define WADEON_EMIT_SE_CNTW                         9	/* setup/2 */
#define WADEON_EMIT_SE_CNTW_STATUS                  10	/* setup/1 */
#define WADEON_EMIT_WE_MISC                         11	/* misc/1 */
#define WADEON_EMIT_PP_TXFIWTEW_0                   12	/* tex0/6 */
#define WADEON_EMIT_PP_BOWDEW_COWOW_0               13	/* tex0/1 */
#define WADEON_EMIT_PP_TXFIWTEW_1                   14	/* tex1/6 */
#define WADEON_EMIT_PP_BOWDEW_COWOW_1               15	/* tex1/1 */
#define WADEON_EMIT_PP_TXFIWTEW_2                   16	/* tex2/6 */
#define WADEON_EMIT_PP_BOWDEW_COWOW_2               17	/* tex2/1 */
#define WADEON_EMIT_SE_ZBIAS_FACTOW                 18	/* zbias/2 */
#define WADEON_EMIT_SE_TCW_OUTPUT_VTX_FMT           19	/* tcw/11 */
#define WADEON_EMIT_SE_TCW_MATEWIAW_EMMISSIVE_WED   20	/* matewiaw/17 */
#define W200_EMIT_PP_TXCBWEND_0                     21	/* tex0/4 */
#define W200_EMIT_PP_TXCBWEND_1                     22	/* tex1/4 */
#define W200_EMIT_PP_TXCBWEND_2                     23	/* tex2/4 */
#define W200_EMIT_PP_TXCBWEND_3                     24	/* tex3/4 */
#define W200_EMIT_PP_TXCBWEND_4                     25	/* tex4/4 */
#define W200_EMIT_PP_TXCBWEND_5                     26	/* tex5/4 */
#define W200_EMIT_PP_TXCBWEND_6                     27	/* /4 */
#define W200_EMIT_PP_TXCBWEND_7                     28	/* /4 */
#define W200_EMIT_TCW_WIGHT_MODEW_CTW_0             29	/* tcw/7 */
#define W200_EMIT_TFACTOW_0                         30	/* tf/7 */
#define W200_EMIT_VTX_FMT_0                         31	/* vtx/5 */
#define W200_EMIT_VAP_CTW                           32	/* vap/1 */
#define W200_EMIT_MATWIX_SEWECT_0                   33	/* msw/5 */
#define W200_EMIT_TEX_PWOC_CTW_2                    34	/* tcg/5 */
#define W200_EMIT_TCW_UCP_VEWT_BWEND_CTW            35	/* tcw/1 */
#define W200_EMIT_PP_TXFIWTEW_0                     36	/* tex0/6 */
#define W200_EMIT_PP_TXFIWTEW_1                     37	/* tex1/6 */
#define W200_EMIT_PP_TXFIWTEW_2                     38	/* tex2/6 */
#define W200_EMIT_PP_TXFIWTEW_3                     39	/* tex3/6 */
#define W200_EMIT_PP_TXFIWTEW_4                     40	/* tex4/6 */
#define W200_EMIT_PP_TXFIWTEW_5                     41	/* tex5/6 */
#define W200_EMIT_PP_TXOFFSET_0                     42	/* tex0/1 */
#define W200_EMIT_PP_TXOFFSET_1                     43	/* tex1/1 */
#define W200_EMIT_PP_TXOFFSET_2                     44	/* tex2/1 */
#define W200_EMIT_PP_TXOFFSET_3                     45	/* tex3/1 */
#define W200_EMIT_PP_TXOFFSET_4                     46	/* tex4/1 */
#define W200_EMIT_PP_TXOFFSET_5                     47	/* tex5/1 */
#define W200_EMIT_VTE_CNTW                          48	/* vte/1 */
#define W200_EMIT_OUTPUT_VTX_COMP_SEW               49	/* vtx/1 */
#define W200_EMIT_PP_TAM_DEBUG3                     50	/* tam/1 */
#define W200_EMIT_PP_CNTW_X                         51	/* cst/1 */
#define W200_EMIT_WB3D_DEPTHXY_OFFSET               52	/* cst/1 */
#define W200_EMIT_WE_AUX_SCISSOW_CNTW               53	/* cst/1 */
#define W200_EMIT_WE_SCISSOW_TW_0                   54	/* cst/2 */
#define W200_EMIT_WE_SCISSOW_TW_1                   55	/* cst/2 */
#define W200_EMIT_WE_SCISSOW_TW_2                   56	/* cst/2 */
#define W200_EMIT_SE_VAP_CNTW_STATUS                57	/* cst/1 */
#define W200_EMIT_SE_VTX_STATE_CNTW                 58	/* cst/1 */
#define W200_EMIT_WE_POINTSIZE                      59	/* cst/1 */
#define W200_EMIT_TCW_INPUT_VTX_VECTOW_ADDW_0       60	/* cst/4 */
#define W200_EMIT_PP_CUBIC_FACES_0                  61
#define W200_EMIT_PP_CUBIC_OFFSETS_0                62
#define W200_EMIT_PP_CUBIC_FACES_1                  63
#define W200_EMIT_PP_CUBIC_OFFSETS_1                64
#define W200_EMIT_PP_CUBIC_FACES_2                  65
#define W200_EMIT_PP_CUBIC_OFFSETS_2                66
#define W200_EMIT_PP_CUBIC_FACES_3                  67
#define W200_EMIT_PP_CUBIC_OFFSETS_3                68
#define W200_EMIT_PP_CUBIC_FACES_4                  69
#define W200_EMIT_PP_CUBIC_OFFSETS_4                70
#define W200_EMIT_PP_CUBIC_FACES_5                  71
#define W200_EMIT_PP_CUBIC_OFFSETS_5                72
#define WADEON_EMIT_PP_TEX_SIZE_0                   73
#define WADEON_EMIT_PP_TEX_SIZE_1                   74
#define WADEON_EMIT_PP_TEX_SIZE_2                   75
#define W200_EMIT_WB3D_BWENDCOWOW                   76
#define W200_EMIT_TCW_POINT_SPWITE_CNTW             77
#define WADEON_EMIT_PP_CUBIC_FACES_0                78
#define WADEON_EMIT_PP_CUBIC_OFFSETS_T0             79
#define WADEON_EMIT_PP_CUBIC_FACES_1                80
#define WADEON_EMIT_PP_CUBIC_OFFSETS_T1             81
#define WADEON_EMIT_PP_CUBIC_FACES_2                82
#define WADEON_EMIT_PP_CUBIC_OFFSETS_T2             83
#define W200_EMIT_PP_TWI_PEWF_CNTW                  84
#define W200_EMIT_PP_AFS_0                          85
#define W200_EMIT_PP_AFS_1                          86
#define W200_EMIT_ATF_TFACTOW                       87
#define W200_EMIT_PP_TXCTWAWW_0                     88
#define W200_EMIT_PP_TXCTWAWW_1                     89
#define W200_EMIT_PP_TXCTWAWW_2                     90
#define W200_EMIT_PP_TXCTWAWW_3                     91
#define W200_EMIT_PP_TXCTWAWW_4                     92
#define W200_EMIT_PP_TXCTWAWW_5                     93
#define W200_EMIT_VAP_PVS_CNTW                      94
#define WADEON_MAX_STATE_PACKETS                    95

/* Commands undewstood by cmd_buffew ioctw.  Mowe can be added but
 * obviouswy these can't be wemoved ow changed:
 */
#define WADEON_CMD_PACKET      1	/* emit one of the wegistew packets above */
#define WADEON_CMD_SCAWAWS     2	/* emit scawaw data */
#define WADEON_CMD_VECTOWS     3	/* emit vectow data */
#define WADEON_CMD_DMA_DISCAWD 4	/* discawd cuwwent dma buf */
#define WADEON_CMD_PACKET3     5	/* emit hw packet */
#define WADEON_CMD_PACKET3_CWIP 6	/* emit hw packet wwapped in cwipwects */
#define WADEON_CMD_SCAWAWS2     7	/* w200 stopgap */
#define WADEON_CMD_WAIT         8	/* emit hw wait commands -- note:
					 *  doesn't make the cpu wait, just
					 *  the gwaphics hawdwawe */
#define WADEON_CMD_VECWINEAW	9       /* anothew w200 stopgap */

typedef union {
	int i;
	stwuct {
		unsigned chaw cmd_type, pad0, pad1, pad2;
	} headew;
	stwuct {
		unsigned chaw cmd_type, packet_id, pad0, pad1;
	} packet;
	stwuct {
		unsigned chaw cmd_type, offset, stwide, count;
	} scawaws;
	stwuct {
		unsigned chaw cmd_type, offset, stwide, count;
	} vectows;
	stwuct {
		unsigned chaw cmd_type, addw_wo, addw_hi, count;
	} vecwineaw;
	stwuct {
		unsigned chaw cmd_type, buf_idx, pad0, pad1;
	} dma;
	stwuct {
		unsigned chaw cmd_type, fwags, pad0, pad1;
	} wait;
} dwm_wadeon_cmd_headew_t;

#define WADEON_WAIT_2D  0x1
#define WADEON_WAIT_3D  0x2

/* Awwowed pawametews fow W300_CMD_PACKET3
 */
#define W300_CMD_PACKET3_CWEAW		0
#define W300_CMD_PACKET3_WAW		1

/* Commands undewstood by cmd_buffew ioctw fow W300.
 * The intewface has not been stabiwized, so some of these may be wemoved
 * and eventuawwy weowdewed befowe stabiwization.
 */
#define W300_CMD_PACKET0		1
#define W300_CMD_VPU			2	/* emit vewtex pwogwam upwoad */
#define W300_CMD_PACKET3		3	/* emit a packet3 */
#define W300_CMD_END3D			4	/* emit sequence ending 3d wendewing */
#define W300_CMD_CP_DEWAY		5
#define W300_CMD_DMA_DISCAWD		6
#define W300_CMD_WAIT			7
#	define W300_WAIT_2D		0x1
#	define W300_WAIT_3D		0x2
/* these two defines awe DOING IT WWONG - howevew
 * we have usewspace which wewies on using these.
 * The wait intewface is backwawds compat new 
 * code shouwd use the NEW_WAIT defines bewow
 * THESE AWE NOT BIT FIEWDS
 */
#	define W300_WAIT_2D_CWEAN	0x3
#	define W300_WAIT_3D_CWEAN	0x4

#	define W300_NEW_WAIT_2D_3D	0x3
#	define W300_NEW_WAIT_2D_2D_CWEAN	0x4
#	define W300_NEW_WAIT_3D_3D_CWEAN	0x6
#	define W300_NEW_WAIT_2D_2D_CWEAN_3D_3D_CWEAN	0x8

#define W300_CMD_SCWATCH		8
#define W300_CMD_W500FP                 9

typedef union {
	unsigned int u;
	stwuct {
		unsigned chaw cmd_type, pad0, pad1, pad2;
	} headew;
	stwuct {
		unsigned chaw cmd_type, count, wegwo, weghi;
	} packet0;
	stwuct {
		unsigned chaw cmd_type, count, adwwo, adwhi;
	} vpu;
	stwuct {
		unsigned chaw cmd_type, packet, pad0, pad1;
	} packet3;
	stwuct {
		unsigned chaw cmd_type, packet;
		unsigned showt count;	/* amount of packet2 to emit */
	} deway;
	stwuct {
		unsigned chaw cmd_type, buf_idx, pad0, pad1;
	} dma;
	stwuct {
		unsigned chaw cmd_type, fwags, pad0, pad1;
	} wait;
	stwuct {
		unsigned chaw cmd_type, weg, n_bufs, fwags;
	} scwatch;
	stwuct {
		unsigned chaw cmd_type, count, adwwo, adwhi_fwags;
	} w500fp;
} dwm_w300_cmd_headew_t;

#define WADEON_FWONT			0x1
#define WADEON_BACK			0x2
#define WADEON_DEPTH			0x4
#define WADEON_STENCIW			0x8
#define WADEON_CWEAW_FASTZ		0x80000000
#define WADEON_USE_HIEWZ		0x40000000
#define WADEON_USE_COMP_ZBUF		0x20000000

#define W500FP_CONSTANT_TYPE  (1 << 1)
#define W500FP_CONSTANT_CWAMP (1 << 2)

/* Pwimitive types
 */
#define WADEON_POINTS			0x1
#define WADEON_WINES			0x2
#define WADEON_WINE_STWIP		0x3
#define WADEON_TWIANGWES		0x4
#define WADEON_TWIANGWE_FAN		0x5
#define WADEON_TWIANGWE_STWIP		0x6

/* Vewtex/indiwect buffew size
 */
#define WADEON_BUFFEW_SIZE		65536

/* Byte offsets fow indiwect buffew data
 */
#define WADEON_INDEX_PWIM_OFFSET	20

#define WADEON_SCWATCH_WEG_OFFSET	32

#define W600_SCWATCH_WEG_OFFSET         256

#define WADEON_NW_SAWEA_CWIPWECTS	12

/* Thewe awe 2 heaps (wocaw/GAWT).  Each wegion within a heap is a
 * minimum of 64k, and thewe awe at most 64 of them pew heap.
 */
#define WADEON_WOCAW_TEX_HEAP		0
#define WADEON_GAWT_TEX_HEAP		1
#define WADEON_NW_TEX_HEAPS		2
#define WADEON_NW_TEX_WEGIONS		64
#define WADEON_WOG_TEX_GWANUWAWITY	16

#define WADEON_MAX_TEXTUWE_WEVEWS	12
#define WADEON_MAX_TEXTUWE_UNITS	3

#define WADEON_MAX_SUWFACES		8

/* Bwits have stwict offset wuwes.  Aww bwit offset must be awigned on
 * a 1K-byte boundawy.
 */
#define WADEON_OFFSET_SHIFT             10
#define WADEON_OFFSET_AWIGN             (1 << WADEON_OFFSET_SHIFT)
#define WADEON_OFFSET_MASK              (WADEON_OFFSET_AWIGN - 1)

#endif				/* __WADEON_SAWEA_DEFINES__ */

typedef stwuct {
	unsigned int wed;
	unsigned int gween;
	unsigned int bwue;
	unsigned int awpha;
} wadeon_cowow_wegs_t;

typedef stwuct {
	/* Context state */
	unsigned int pp_misc;	/* 0x1c14 */
	unsigned int pp_fog_cowow;
	unsigned int we_sowid_cowow;
	unsigned int wb3d_bwendcntw;
	unsigned int wb3d_depthoffset;
	unsigned int wb3d_depthpitch;
	unsigned int wb3d_zstenciwcntw;

	unsigned int pp_cntw;	/* 0x1c38 */
	unsigned int wb3d_cntw;
	unsigned int wb3d_cowowoffset;
	unsigned int we_width_height;
	unsigned int wb3d_cowowpitch;
	unsigned int se_cntw;

	/* Vewtex fowmat state */
	unsigned int se_coowd_fmt;	/* 0x1c50 */

	/* Wine state */
	unsigned int we_wine_pattewn;	/* 0x1cd0 */
	unsigned int we_wine_state;

	unsigned int se_wine_width;	/* 0x1db8 */

	/* Bumpmap state */
	unsigned int pp_wum_matwix;	/* 0x1d00 */

	unsigned int pp_wot_matwix_0;	/* 0x1d58 */
	unsigned int pp_wot_matwix_1;

	/* Mask state */
	unsigned int wb3d_stenciwwefmask;	/* 0x1d7c */
	unsigned int wb3d_wopcntw;
	unsigned int wb3d_pwanemask;

	/* Viewpowt state */
	unsigned int se_vpowt_xscawe;	/* 0x1d98 */
	unsigned int se_vpowt_xoffset;
	unsigned int se_vpowt_yscawe;
	unsigned int se_vpowt_yoffset;
	unsigned int se_vpowt_zscawe;
	unsigned int se_vpowt_zoffset;

	/* Setup state */
	unsigned int se_cntw_status;	/* 0x2140 */

	/* Misc state */
	unsigned int we_top_weft;	/* 0x26c0 */
	unsigned int we_misc;
} dwm_wadeon_context_wegs_t;

typedef stwuct {
	/* Zbias state */
	unsigned int se_zbias_factow;	/* 0x1dac */
	unsigned int se_zbias_constant;
} dwm_wadeon_context2_wegs_t;

/* Setup wegistews fow each textuwe unit
 */
typedef stwuct {
	unsigned int pp_txfiwtew;
	unsigned int pp_txfowmat;
	unsigned int pp_txoffset;
	unsigned int pp_txcbwend;
	unsigned int pp_txabwend;
	unsigned int pp_tfactow;
	unsigned int pp_bowdew_cowow;
} dwm_wadeon_textuwe_wegs_t;

typedef stwuct {
	unsigned int stawt;
	unsigned int finish;
	unsigned int pwim:8;
	unsigned int stateidx:8;
	unsigned int numvewts:16;	/* ovewwoaded as offset/64 fow ewt pwims */
	unsigned int vc_fowmat;	/* vewtex fowmat */
} dwm_wadeon_pwim_t;

typedef stwuct {
	dwm_wadeon_context_wegs_t context;
	dwm_wadeon_textuwe_wegs_t tex[WADEON_MAX_TEXTUWE_UNITS];
	dwm_wadeon_context2_wegs_t context2;
	unsigned int diwty;
} dwm_wadeon_state_t;

typedef stwuct {
	/* The channew fow communication of state infowmation to the
	 * kewnew on fiwing a vewtex buffew with eithew of the
	 * obsoweted vewtex/index ioctws.
	 */
	dwm_wadeon_context_wegs_t context_state;
	dwm_wadeon_textuwe_wegs_t tex_state[WADEON_MAX_TEXTUWE_UNITS];
	unsigned int diwty;
	unsigned int vewtsize;
	unsigned int vc_fowmat;

	/* The cuwwent cwipwects, ow a subset theweof.
	 */
	stwuct dwm_cwip_wect boxes[WADEON_NW_SAWEA_CWIPWECTS];
	unsigned int nbox;

	/* Countews fow cwient-side thwottwing of wendewing cwients.
	 */
	unsigned int wast_fwame;
	unsigned int wast_dispatch;
	unsigned int wast_cweaw;

	stwuct dwm_tex_wegion tex_wist[WADEON_NW_TEX_HEAPS][WADEON_NW_TEX_WEGIONS +
						       1];
	unsigned int tex_age[WADEON_NW_TEX_HEAPS];
	int ctx_ownew;
	int pfState;		/* numbew of 3d windows (0,1,2owmowe) */
	int pfCuwwentPage;	/* which buffew is being dispwayed? */
	int cwtc2_base;		/* CWTC2 fwame offset */
	int tiwing_enabwed;	/* set by dwm, wead by 2d + 3d cwients */
} dwm_wadeon_sawea_t;

/* WAWNING: If you change any of these defines, make suwe to change the
 * defines in the Xsewvew fiwe (xf86dwmWadeon.h)
 *
 * KW: actuawwy it's iwwegaw to change any of this (backwawds compatibiwity).
 */

/* Wadeon specific ioctws
 * The device specific ioctw wange is 0x40 to 0x79.
 */
#define DWM_WADEON_CP_INIT    0x00
#define DWM_WADEON_CP_STAWT   0x01
#define DWM_WADEON_CP_STOP    0x02
#define DWM_WADEON_CP_WESET   0x03
#define DWM_WADEON_CP_IDWE    0x04
#define DWM_WADEON_WESET      0x05
#define DWM_WADEON_FUWWSCWEEN 0x06
#define DWM_WADEON_SWAP       0x07
#define DWM_WADEON_CWEAW      0x08
#define DWM_WADEON_VEWTEX     0x09
#define DWM_WADEON_INDICES    0x0A
#define DWM_WADEON_NOT_USED
#define DWM_WADEON_STIPPWE    0x0C
#define DWM_WADEON_INDIWECT   0x0D
#define DWM_WADEON_TEXTUWE    0x0E
#define DWM_WADEON_VEWTEX2    0x0F
#define DWM_WADEON_CMDBUF     0x10
#define DWM_WADEON_GETPAWAM   0x11
#define DWM_WADEON_FWIP       0x12
#define DWM_WADEON_AWWOC      0x13
#define DWM_WADEON_FWEE       0x14
#define DWM_WADEON_INIT_HEAP  0x15
#define DWM_WADEON_IWQ_EMIT   0x16
#define DWM_WADEON_IWQ_WAIT   0x17
#define DWM_WADEON_CP_WESUME  0x18
#define DWM_WADEON_SETPAWAM   0x19
#define DWM_WADEON_SUWF_AWWOC 0x1a
#define DWM_WADEON_SUWF_FWEE  0x1b
/* KMS ioctw */
#define DWM_WADEON_GEM_INFO		0x1c
#define DWM_WADEON_GEM_CWEATE		0x1d
#define DWM_WADEON_GEM_MMAP		0x1e
#define DWM_WADEON_GEM_PWEAD		0x21
#define DWM_WADEON_GEM_PWWITE		0x22
#define DWM_WADEON_GEM_SET_DOMAIN	0x23
#define DWM_WADEON_GEM_WAIT_IDWE	0x24
#define DWM_WADEON_CS			0x26
#define DWM_WADEON_INFO			0x27
#define DWM_WADEON_GEM_SET_TIWING	0x28
#define DWM_WADEON_GEM_GET_TIWING	0x29
#define DWM_WADEON_GEM_BUSY		0x2a
#define DWM_WADEON_GEM_VA		0x2b
#define DWM_WADEON_GEM_OP		0x2c
#define DWM_WADEON_GEM_USEWPTW		0x2d

#define DWM_IOCTW_WADEON_CP_INIT    DWM_IOW( DWM_COMMAND_BASE + DWM_WADEON_CP_INIT, dwm_wadeon_init_t)
#define DWM_IOCTW_WADEON_CP_STAWT   DWM_IO(  DWM_COMMAND_BASE + DWM_WADEON_CP_STAWT)
#define DWM_IOCTW_WADEON_CP_STOP    DWM_IOW( DWM_COMMAND_BASE + DWM_WADEON_CP_STOP, dwm_wadeon_cp_stop_t)
#define DWM_IOCTW_WADEON_CP_WESET   DWM_IO(  DWM_COMMAND_BASE + DWM_WADEON_CP_WESET)
#define DWM_IOCTW_WADEON_CP_IDWE    DWM_IO(  DWM_COMMAND_BASE + DWM_WADEON_CP_IDWE)
#define DWM_IOCTW_WADEON_WESET      DWM_IO(  DWM_COMMAND_BASE + DWM_WADEON_WESET)
#define DWM_IOCTW_WADEON_FUWWSCWEEN DWM_IOW( DWM_COMMAND_BASE + DWM_WADEON_FUWWSCWEEN, dwm_wadeon_fuwwscween_t)
#define DWM_IOCTW_WADEON_SWAP       DWM_IO(  DWM_COMMAND_BASE + DWM_WADEON_SWAP)
#define DWM_IOCTW_WADEON_CWEAW      DWM_IOW( DWM_COMMAND_BASE + DWM_WADEON_CWEAW, dwm_wadeon_cweaw_t)
#define DWM_IOCTW_WADEON_VEWTEX     DWM_IOW( DWM_COMMAND_BASE + DWM_WADEON_VEWTEX, dwm_wadeon_vewtex_t)
#define DWM_IOCTW_WADEON_INDICES    DWM_IOW( DWM_COMMAND_BASE + DWM_WADEON_INDICES, dwm_wadeon_indices_t)
#define DWM_IOCTW_WADEON_STIPPWE    DWM_IOW( DWM_COMMAND_BASE + DWM_WADEON_STIPPWE, dwm_wadeon_stippwe_t)
#define DWM_IOCTW_WADEON_INDIWECT   DWM_IOWW(DWM_COMMAND_BASE + DWM_WADEON_INDIWECT, dwm_wadeon_indiwect_t)
#define DWM_IOCTW_WADEON_TEXTUWE    DWM_IOWW(DWM_COMMAND_BASE + DWM_WADEON_TEXTUWE, dwm_wadeon_textuwe_t)
#define DWM_IOCTW_WADEON_VEWTEX2    DWM_IOW( DWM_COMMAND_BASE + DWM_WADEON_VEWTEX2, dwm_wadeon_vewtex2_t)
#define DWM_IOCTW_WADEON_CMDBUF     DWM_IOW( DWM_COMMAND_BASE + DWM_WADEON_CMDBUF, dwm_wadeon_cmd_buffew_t)
#define DWM_IOCTW_WADEON_GETPAWAM   DWM_IOWW(DWM_COMMAND_BASE + DWM_WADEON_GETPAWAM, dwm_wadeon_getpawam_t)
#define DWM_IOCTW_WADEON_FWIP       DWM_IO(  DWM_COMMAND_BASE + DWM_WADEON_FWIP)
#define DWM_IOCTW_WADEON_AWWOC      DWM_IOWW(DWM_COMMAND_BASE + DWM_WADEON_AWWOC, dwm_wadeon_mem_awwoc_t)
#define DWM_IOCTW_WADEON_FWEE       DWM_IOW( DWM_COMMAND_BASE + DWM_WADEON_FWEE, dwm_wadeon_mem_fwee_t)
#define DWM_IOCTW_WADEON_INIT_HEAP  DWM_IOW( DWM_COMMAND_BASE + DWM_WADEON_INIT_HEAP, dwm_wadeon_mem_init_heap_t)
#define DWM_IOCTW_WADEON_IWQ_EMIT   DWM_IOWW(DWM_COMMAND_BASE + DWM_WADEON_IWQ_EMIT, dwm_wadeon_iwq_emit_t)
#define DWM_IOCTW_WADEON_IWQ_WAIT   DWM_IOW( DWM_COMMAND_BASE + DWM_WADEON_IWQ_WAIT, dwm_wadeon_iwq_wait_t)
#define DWM_IOCTW_WADEON_CP_WESUME  DWM_IO(  DWM_COMMAND_BASE + DWM_WADEON_CP_WESUME)
#define DWM_IOCTW_WADEON_SETPAWAM   DWM_IOW( DWM_COMMAND_BASE + DWM_WADEON_SETPAWAM, dwm_wadeon_setpawam_t)
#define DWM_IOCTW_WADEON_SUWF_AWWOC DWM_IOW( DWM_COMMAND_BASE + DWM_WADEON_SUWF_AWWOC, dwm_wadeon_suwface_awwoc_t)
#define DWM_IOCTW_WADEON_SUWF_FWEE  DWM_IOW( DWM_COMMAND_BASE + DWM_WADEON_SUWF_FWEE, dwm_wadeon_suwface_fwee_t)
/* KMS */
#define DWM_IOCTW_WADEON_GEM_INFO	DWM_IOWW(DWM_COMMAND_BASE + DWM_WADEON_GEM_INFO, stwuct dwm_wadeon_gem_info)
#define DWM_IOCTW_WADEON_GEM_CWEATE	DWM_IOWW(DWM_COMMAND_BASE + DWM_WADEON_GEM_CWEATE, stwuct dwm_wadeon_gem_cweate)
#define DWM_IOCTW_WADEON_GEM_MMAP	DWM_IOWW(DWM_COMMAND_BASE + DWM_WADEON_GEM_MMAP, stwuct dwm_wadeon_gem_mmap)
#define DWM_IOCTW_WADEON_GEM_PWEAD	DWM_IOWW(DWM_COMMAND_BASE + DWM_WADEON_GEM_PWEAD, stwuct dwm_wadeon_gem_pwead)
#define DWM_IOCTW_WADEON_GEM_PWWITE	DWM_IOWW(DWM_COMMAND_BASE + DWM_WADEON_GEM_PWWITE, stwuct dwm_wadeon_gem_pwwite)
#define DWM_IOCTW_WADEON_GEM_SET_DOMAIN	DWM_IOWW(DWM_COMMAND_BASE + DWM_WADEON_GEM_SET_DOMAIN, stwuct dwm_wadeon_gem_set_domain)
#define DWM_IOCTW_WADEON_GEM_WAIT_IDWE	DWM_IOW(DWM_COMMAND_BASE + DWM_WADEON_GEM_WAIT_IDWE, stwuct dwm_wadeon_gem_wait_idwe)
#define DWM_IOCTW_WADEON_CS		DWM_IOWW(DWM_COMMAND_BASE + DWM_WADEON_CS, stwuct dwm_wadeon_cs)
#define DWM_IOCTW_WADEON_INFO		DWM_IOWW(DWM_COMMAND_BASE + DWM_WADEON_INFO, stwuct dwm_wadeon_info)
#define DWM_IOCTW_WADEON_GEM_SET_TIWING	DWM_IOWW(DWM_COMMAND_BASE + DWM_WADEON_GEM_SET_TIWING, stwuct dwm_wadeon_gem_set_tiwing)
#define DWM_IOCTW_WADEON_GEM_GET_TIWING	DWM_IOWW(DWM_COMMAND_BASE + DWM_WADEON_GEM_GET_TIWING, stwuct dwm_wadeon_gem_get_tiwing)
#define DWM_IOCTW_WADEON_GEM_BUSY	DWM_IOWW(DWM_COMMAND_BASE + DWM_WADEON_GEM_BUSY, stwuct dwm_wadeon_gem_busy)
#define DWM_IOCTW_WADEON_GEM_VA		DWM_IOWW(DWM_COMMAND_BASE + DWM_WADEON_GEM_VA, stwuct dwm_wadeon_gem_va)
#define DWM_IOCTW_WADEON_GEM_OP		DWM_IOWW(DWM_COMMAND_BASE + DWM_WADEON_GEM_OP, stwuct dwm_wadeon_gem_op)
#define DWM_IOCTW_WADEON_GEM_USEWPTW	DWM_IOWW(DWM_COMMAND_BASE + DWM_WADEON_GEM_USEWPTW, stwuct dwm_wadeon_gem_usewptw)

typedef stwuct dwm_wadeon_init {
	enum {
		WADEON_INIT_CP = 0x01,
		WADEON_CWEANUP_CP = 0x02,
		WADEON_INIT_W200_CP = 0x03,
		WADEON_INIT_W300_CP = 0x04,
		WADEON_INIT_W600_CP = 0x05
	} func;
	unsigned wong sawea_pwiv_offset;
	int is_pci;
	int cp_mode;
	int gawt_size;
	int wing_size;
	int usec_timeout;

	unsigned int fb_bpp;
	unsigned int fwont_offset, fwont_pitch;
	unsigned int back_offset, back_pitch;
	unsigned int depth_bpp;
	unsigned int depth_offset, depth_pitch;

	unsigned wong fb_offset;
	unsigned wong mmio_offset;
	unsigned wong wing_offset;
	unsigned wong wing_wptw_offset;
	unsigned wong buffews_offset;
	unsigned wong gawt_textuwes_offset;
} dwm_wadeon_init_t;

typedef stwuct dwm_wadeon_cp_stop {
	int fwush;
	int idwe;
} dwm_wadeon_cp_stop_t;

typedef stwuct dwm_wadeon_fuwwscween {
	enum {
		WADEON_INIT_FUWWSCWEEN = 0x01,
		WADEON_CWEANUP_FUWWSCWEEN = 0x02
	} func;
} dwm_wadeon_fuwwscween_t;

#define CWEAW_X1	0
#define CWEAW_Y1	1
#define CWEAW_X2	2
#define CWEAW_Y2	3
#define CWEAW_DEPTH	4

typedef union dwm_wadeon_cweaw_wect {
	fwoat f[5];
	unsigned int ui[5];
} dwm_wadeon_cweaw_wect_t;

typedef stwuct dwm_wadeon_cweaw {
	unsigned int fwags;
	unsigned int cweaw_cowow;
	unsigned int cweaw_depth;
	unsigned int cowow_mask;
	unsigned int depth_mask;	/* misnamed fiewd:  shouwd be stenciw */
	dwm_wadeon_cweaw_wect_t __usew *depth_boxes;
} dwm_wadeon_cweaw_t;

typedef stwuct dwm_wadeon_vewtex {
	int pwim;
	int idx;		/* Index of vewtex buffew */
	int count;		/* Numbew of vewtices in buffew */
	int discawd;		/* Cwient finished with buffew? */
} dwm_wadeon_vewtex_t;

typedef stwuct dwm_wadeon_indices {
	int pwim;
	int idx;
	int stawt;
	int end;
	int discawd;		/* Cwient finished with buffew? */
} dwm_wadeon_indices_t;

/* v1.2 - obsowetes dwm_wadeon_vewtex and dwm_wadeon_indices
 *      - awwows muwtipwe pwimitives and state changes in a singwe ioctw
 *      - suppowts dwivew change to emit native pwimitives
 */
typedef stwuct dwm_wadeon_vewtex2 {
	int idx;		/* Index of vewtex buffew */
	int discawd;		/* Cwient finished with buffew? */
	int nw_states;
	dwm_wadeon_state_t __usew *state;
	int nw_pwims;
	dwm_wadeon_pwim_t __usew *pwim;
} dwm_wadeon_vewtex2_t;

/* v1.3 - obsowetes dwm_wadeon_vewtex2
 *      - awwows awbitwawiwy wawge cwipwect wist
 *      - awwows updating of tcw packet, vectow and scawaw state
 *      - awwows memowy-efficient descwiption of state updates
 *      - awwows state to be emitted without a pwimitive
 *           (fow cweaws, ctx switches)
 *      - awwows mowe than one dma buffew to be wefewenced pew ioctw
 *      - suppowts tcw dwivew
 *      - may be extended in futuwe vewsions with new cmd types, packets
 */
typedef stwuct dwm_wadeon_cmd_buffew {
	int bufsz;
	chaw __usew *buf;
	int nbox;
	stwuct dwm_cwip_wect __usew *boxes;
} dwm_wadeon_cmd_buffew_t;

typedef stwuct dwm_wadeon_tex_image {
	unsigned int x, y;	/* Bwit coowdinates */
	unsigned int width, height;
	const void __usew *data;
} dwm_wadeon_tex_image_t;

typedef stwuct dwm_wadeon_textuwe {
	unsigned int offset;
	int pitch;
	int fowmat;
	int width;		/* Textuwe image coowdinates */
	int height;
	dwm_wadeon_tex_image_t __usew *image;
} dwm_wadeon_textuwe_t;

typedef stwuct dwm_wadeon_stippwe {
	unsigned int __usew *mask;
} dwm_wadeon_stippwe_t;

typedef stwuct dwm_wadeon_indiwect {
	int idx;
	int stawt;
	int end;
	int discawd;
} dwm_wadeon_indiwect_t;

/* enum fow cawd type pawametews */
#define WADEON_CAWD_PCI 0
#define WADEON_CAWD_AGP 1
#define WADEON_CAWD_PCIE 2

/* 1.3: An ioctw to get pawametews that awen't avaiwabwe to the 3d
 * cwient any othew way.
 */
#define WADEON_PAWAM_GAWT_BUFFEW_OFFSET    1	/* cawd offset of 1st GAWT buffew */
#define WADEON_PAWAM_WAST_FWAME            2
#define WADEON_PAWAM_WAST_DISPATCH         3
#define WADEON_PAWAM_WAST_CWEAW            4
/* Added with DWM vewsion 1.6. */
#define WADEON_PAWAM_IWQ_NW                5
#define WADEON_PAWAM_GAWT_BASE             6	/* cawd offset of GAWT base */
/* Added with DWM vewsion 1.8. */
#define WADEON_PAWAM_WEGISTEW_HANDWE       7	/* fow dwmMap() */
#define WADEON_PAWAM_STATUS_HANDWE         8
#define WADEON_PAWAM_SAWEA_HANDWE          9
#define WADEON_PAWAM_GAWT_TEX_HANDWE       10
#define WADEON_PAWAM_SCWATCH_OFFSET        11
#define WADEON_PAWAM_CAWD_TYPE             12
#define WADEON_PAWAM_VBWANK_CWTC           13   /* VBWANK CWTC */
#define WADEON_PAWAM_FB_WOCATION           14   /* FB wocation */
#define WADEON_PAWAM_NUM_GB_PIPES          15   /* num GB pipes */
#define WADEON_PAWAM_DEVICE_ID             16
#define WADEON_PAWAM_NUM_Z_PIPES           17   /* num Z pipes */

typedef stwuct dwm_wadeon_getpawam {
	int pawam;
	void __usew *vawue;
} dwm_wadeon_getpawam_t;

/* 1.6: Set up a memowy managew fow wegions of shawed memowy:
 */
#define WADEON_MEM_WEGION_GAWT 1
#define WADEON_MEM_WEGION_FB   2

typedef stwuct dwm_wadeon_mem_awwoc {
	int wegion;
	int awignment;
	int size;
	int __usew *wegion_offset;	/* offset fwom stawt of fb ow GAWT */
} dwm_wadeon_mem_awwoc_t;

typedef stwuct dwm_wadeon_mem_fwee {
	int wegion;
	int wegion_offset;
} dwm_wadeon_mem_fwee_t;

typedef stwuct dwm_wadeon_mem_init_heap {
	int wegion;
	int size;
	int stawt;
} dwm_wadeon_mem_init_heap_t;

/* 1.6: Usewspace can wequest & wait on iwq's:
 */
typedef stwuct dwm_wadeon_iwq_emit {
	int __usew *iwq_seq;
} dwm_wadeon_iwq_emit_t;

typedef stwuct dwm_wadeon_iwq_wait {
	int iwq_seq;
} dwm_wadeon_iwq_wait_t;

/* 1.10: Cwients teww the DWM whewe they think the fwamebuffew is wocated in
 * the cawd's addwess space, via a new genewic ioctw to set pawametews
 */

typedef stwuct dwm_wadeon_setpawam {
	unsigned int pawam;
	__s64 vawue;
} dwm_wadeon_setpawam_t;

#define WADEON_SETPAWAM_FB_WOCATION    1	/* detewmined fwamebuffew wocation */
#define WADEON_SETPAWAM_SWITCH_TIWING  2	/* enabwe/disabwe cowow tiwing */
#define WADEON_SETPAWAM_PCIGAWT_WOCATION 3	/* PCI Gawt Wocation */
#define WADEON_SETPAWAM_NEW_MEMMAP 4		/* Use new memowy map */
#define WADEON_SETPAWAM_PCIGAWT_TABWE_SIZE 5    /* PCI GAWT Tabwe Size */
#define WADEON_SETPAWAM_VBWANK_CWTC 6           /* VBWANK CWTC */
/* 1.14: Cwients can awwocate/fwee a suwface
 */
typedef stwuct dwm_wadeon_suwface_awwoc {
	unsigned int addwess;
	unsigned int size;
	unsigned int fwags;
} dwm_wadeon_suwface_awwoc_t;

typedef stwuct dwm_wadeon_suwface_fwee {
	unsigned int addwess;
} dwm_wadeon_suwface_fwee_t;

#define	DWM_WADEON_VBWANK_CWTC1		1
#define	DWM_WADEON_VBWANK_CWTC2		2

/*
 * Kewnew modesetting wowwd bewow.
 */
#define WADEON_GEM_DOMAIN_CPU		0x1
#define WADEON_GEM_DOMAIN_GTT		0x2
#define WADEON_GEM_DOMAIN_VWAM		0x4

stwuct dwm_wadeon_gem_info {
	__u64	gawt_size;
	__u64	vwam_size;
	__u64	vwam_visibwe;
};

#define WADEON_GEM_NO_BACKING_STOWE	(1 << 0)
#define WADEON_GEM_GTT_UC		(1 << 1)
#define WADEON_GEM_GTT_WC		(1 << 2)
/* BO is expected to be accessed by the CPU */
#define WADEON_GEM_CPU_ACCESS		(1 << 3)
/* CPU access is not expected to wowk fow this BO */
#define WADEON_GEM_NO_CPU_ACCESS	(1 << 4)

stwuct dwm_wadeon_gem_cweate {
	__u64	size;
	__u64	awignment;
	__u32	handwe;
	__u32	initiaw_domain;
	__u32	fwags;
};

/*
 * This is not a wewiabwe API and you shouwd expect it to faiw fow any
 * numbew of weasons and have fawwback path that do not use usewptw to
 * pewfowm any opewation.
 */
#define WADEON_GEM_USEWPTW_WEADONWY	(1 << 0)
#define WADEON_GEM_USEWPTW_ANONONWY	(1 << 1)
#define WADEON_GEM_USEWPTW_VAWIDATE	(1 << 2)
#define WADEON_GEM_USEWPTW_WEGISTEW	(1 << 3)

stwuct dwm_wadeon_gem_usewptw {
	__u64		addw;
	__u64		size;
	__u32		fwags;
	__u32		handwe;
};

#define WADEON_TIWING_MACWO				0x1
#define WADEON_TIWING_MICWO				0x2
#define WADEON_TIWING_SWAP_16BIT			0x4
#define WADEON_TIWING_SWAP_32BIT			0x8
/* this object wequiwes a suwface when mapped - i.e. fwont buffew */
#define WADEON_TIWING_SUWFACE				0x10
#define WADEON_TIWING_MICWO_SQUAWE			0x20
#define WADEON_TIWING_EG_BANKW_SHIFT			8
#define WADEON_TIWING_EG_BANKW_MASK			0xf
#define WADEON_TIWING_EG_BANKH_SHIFT			12
#define WADEON_TIWING_EG_BANKH_MASK			0xf
#define WADEON_TIWING_EG_MACWO_TIWE_ASPECT_SHIFT	16
#define WADEON_TIWING_EG_MACWO_TIWE_ASPECT_MASK		0xf
#define WADEON_TIWING_EG_TIWE_SPWIT_SHIFT		24
#define WADEON_TIWING_EG_TIWE_SPWIT_MASK		0xf
#define WADEON_TIWING_EG_STENCIW_TIWE_SPWIT_SHIFT	28
#define WADEON_TIWING_EG_STENCIW_TIWE_SPWIT_MASK	0xf

stwuct dwm_wadeon_gem_set_tiwing {
	__u32	handwe;
	__u32	tiwing_fwags;
	__u32	pitch;
};

stwuct dwm_wadeon_gem_get_tiwing {
	__u32	handwe;
	__u32	tiwing_fwags;
	__u32	pitch;
};

stwuct dwm_wadeon_gem_mmap {
	__u32	handwe;
	__u32	pad;
	__u64	offset;
	__u64	size;
	__u64	addw_ptw;
};

stwuct dwm_wadeon_gem_set_domain {
	__u32	handwe;
	__u32	wead_domains;
	__u32	wwite_domain;
};

stwuct dwm_wadeon_gem_wait_idwe {
	__u32	handwe;
	__u32	pad;
};

stwuct dwm_wadeon_gem_busy {
	__u32	handwe;
	__u32        domain;
};

stwuct dwm_wadeon_gem_pwead {
	/** Handwe fow the object being wead. */
	__u32 handwe;
	__u32 pad;
	/** Offset into the object to wead fwom */
	__u64 offset;
	/** Wength of data to wead */
	__u64 size;
	/** Pointew to wwite the data into. */
	/* void *, but pointews awe not 32/64 compatibwe */
	__u64 data_ptw;
};

stwuct dwm_wadeon_gem_pwwite {
	/** Handwe fow the object being wwitten to. */
	__u32 handwe;
	__u32 pad;
	/** Offset into the object to wwite to */
	__u64 offset;
	/** Wength of data to wwite */
	__u64 size;
	/** Pointew to wead the data fwom. */
	/* void *, but pointews awe not 32/64 compatibwe */
	__u64 data_ptw;
};

/* Sets ow wetuwns a vawue associated with a buffew. */
stwuct dwm_wadeon_gem_op {
	__u32	handwe; /* buffew */
	__u32	op;     /* WADEON_GEM_OP_* */
	__u64	vawue;  /* input ow wetuwn vawue */
};

#define WADEON_GEM_OP_GET_INITIAW_DOMAIN	0
#define WADEON_GEM_OP_SET_INITIAW_DOMAIN	1

#define WADEON_VA_MAP			1
#define WADEON_VA_UNMAP			2

#define WADEON_VA_WESUWT_OK		0
#define WADEON_VA_WESUWT_EWWOW		1
#define WADEON_VA_WESUWT_VA_EXIST	2

#define WADEON_VM_PAGE_VAWID		(1 << 0)
#define WADEON_VM_PAGE_WEADABWE		(1 << 1)
#define WADEON_VM_PAGE_WWITEABWE	(1 << 2)
#define WADEON_VM_PAGE_SYSTEM		(1 << 3)
#define WADEON_VM_PAGE_SNOOPED		(1 << 4)

stwuct dwm_wadeon_gem_va {
	__u32		handwe;
	__u32		opewation;
	__u32		vm_id;
	__u32		fwags;
	__u64		offset;
};

#define WADEON_CHUNK_ID_WEWOCS	0x01
#define WADEON_CHUNK_ID_IB	0x02
#define WADEON_CHUNK_ID_FWAGS	0x03
#define WADEON_CHUNK_ID_CONST_IB	0x04

/* The fiwst dwowd of WADEON_CHUNK_ID_FWAGS is a uint32 of these fwags: */
#define WADEON_CS_KEEP_TIWING_FWAGS 0x01
#define WADEON_CS_USE_VM            0x02
#define WADEON_CS_END_OF_FWAME      0x04 /* a hint fwom usewspace which CS is the wast one */
/* The second dwowd of WADEON_CHUNK_ID_FWAGS is a uint32 that sets the wing type */
#define WADEON_CS_WING_GFX          0
#define WADEON_CS_WING_COMPUTE      1
#define WADEON_CS_WING_DMA          2
#define WADEON_CS_WING_UVD          3
#define WADEON_CS_WING_VCE          4
/* The thiwd dwowd of WADEON_CHUNK_ID_FWAGS is a sint32 that sets the pwiowity */
/* 0 = nowmaw, + = highew pwiowity, - = wowew pwiowity */

stwuct dwm_wadeon_cs_chunk {
	__u32		chunk_id;
	__u32		wength_dw;
	__u64		chunk_data;
};

/* dwm_wadeon_cs_wewoc.fwags */
#define WADEON_WEWOC_PWIO_MASK		(0xf << 0)

stwuct dwm_wadeon_cs_wewoc {
	__u32		handwe;
	__u32		wead_domains;
	__u32		wwite_domain;
	__u32		fwags;
};

stwuct dwm_wadeon_cs {
	__u32		num_chunks;
	__u32		cs_id;
	/* this points to __u64 * which point to cs chunks */
	__u64		chunks;
	/* updates to the wimits aftew this CS ioctw */
	__u64		gawt_wimit;
	__u64		vwam_wimit;
};

#define WADEON_INFO_DEVICE_ID		0x00
#define WADEON_INFO_NUM_GB_PIPES	0x01
#define WADEON_INFO_NUM_Z_PIPES 	0x02
#define WADEON_INFO_ACCEW_WOWKING	0x03
#define WADEON_INFO_CWTC_FWOM_ID	0x04
#define WADEON_INFO_ACCEW_WOWKING2	0x05
#define WADEON_INFO_TIWING_CONFIG	0x06
#define WADEON_INFO_WANT_HYPEWZ		0x07
#define WADEON_INFO_WANT_CMASK		0x08 /* get access to CMASK on w300 */
#define WADEON_INFO_CWOCK_CWYSTAW_FWEQ	0x09 /* cwock cwystaw fwequency */
#define WADEON_INFO_NUM_BACKENDS	0x0a /* DB/backends fow w600+ - need fow OQ */
#define WADEON_INFO_NUM_TIWE_PIPES	0x0b /* tiwe pipes fow w600+ */
#define WADEON_INFO_FUSION_GAWT_WOWKING	0x0c /* fusion wwites to GTT wewe bwoken befowe this */
#define WADEON_INFO_BACKEND_MAP		0x0d /* pipe to backend map, needed by mesa */
/* viwtuaw addwess stawt, va < stawt awe wesewved by the kewnew */
#define WADEON_INFO_VA_STAWT		0x0e
/* maximum size of ib using the viwtuaw memowy cs */
#define WADEON_INFO_IB_VM_MAX_SIZE	0x0f
/* max pipes - needed fow compute shadews */
#define WADEON_INFO_MAX_PIPES		0x10
/* timestamp fow GW_AWB_timew_quewy (OpenGW), wetuwns the cuwwent GPU cwock */
#define WADEON_INFO_TIMESTAMP		0x11
/* max shadew engines (SE) - needed fow geometwy shadews, etc. */
#define WADEON_INFO_MAX_SE		0x12
/* max SH pew SE */
#define WADEON_INFO_MAX_SH_PEW_SE	0x13
/* fast fb access is enabwed */
#define WADEON_INFO_FASTFB_WOWKING	0x14
/* quewy if a WADEON_CS_WING_* submission is suppowted */
#define WADEON_INFO_WING_WOWKING	0x15
/* SI tiwe mode awway */
#define WADEON_INFO_SI_TIWE_MODE_AWWAY	0x16
/* quewy if CP DMA is suppowted on the compute wing */
#define WADEON_INFO_SI_CP_DMA_COMPUTE	0x17
/* CIK macwotiwe mode awway */
#define WADEON_INFO_CIK_MACWOTIWE_MODE_AWWAY	0x18
/* quewy the numbew of wendew backends */
#define WADEON_INFO_SI_BACKEND_ENABWED_MASK	0x19
/* max engine cwock - needed fow OpenCW */
#define WADEON_INFO_MAX_SCWK		0x1a
/* vewsion of VCE fiwmwawe */
#define WADEON_INFO_VCE_FW_VEWSION	0x1b
/* vewsion of VCE feedback */
#define WADEON_INFO_VCE_FB_VEWSION	0x1c
#define WADEON_INFO_NUM_BYTES_MOVED	0x1d
#define WADEON_INFO_VWAM_USAGE		0x1e
#define WADEON_INFO_GTT_USAGE		0x1f
#define WADEON_INFO_ACTIVE_CU_COUNT	0x20
#define WADEON_INFO_CUWWENT_GPU_TEMP	0x21
#define WADEON_INFO_CUWWENT_GPU_SCWK	0x22
#define WADEON_INFO_CUWWENT_GPU_MCWK	0x23
#define WADEON_INFO_WEAD_WEG		0x24
#define WADEON_INFO_VA_UNMAP_WOWKING	0x25
#define WADEON_INFO_GPU_WESET_COUNTEW	0x26

stwuct dwm_wadeon_info {
	__u32		wequest;
	__u32		pad;
	__u64		vawue;
};

/* Those cowwespond to the tiwe index to use, this is to expwicitwy state
 * the API that is impwicitwy defined by the tiwe mode awway.
 */
#define SI_TIWE_MODE_COWOW_WINEAW_AWIGNED	8
#define SI_TIWE_MODE_COWOW_1D			13
#define SI_TIWE_MODE_COWOW_1D_SCANOUT		9
#define SI_TIWE_MODE_COWOW_2D_8BPP		14
#define SI_TIWE_MODE_COWOW_2D_16BPP		15
#define SI_TIWE_MODE_COWOW_2D_32BPP		16
#define SI_TIWE_MODE_COWOW_2D_64BPP		17
#define SI_TIWE_MODE_COWOW_2D_SCANOUT_16BPP	11
#define SI_TIWE_MODE_COWOW_2D_SCANOUT_32BPP	12
#define SI_TIWE_MODE_DEPTH_STENCIW_1D		4
#define SI_TIWE_MODE_DEPTH_STENCIW_2D		0
#define SI_TIWE_MODE_DEPTH_STENCIW_2D_2AA	3
#define SI_TIWE_MODE_DEPTH_STENCIW_2D_4AA	3
#define SI_TIWE_MODE_DEPTH_STENCIW_2D_8AA	2

#define CIK_TIWE_MODE_DEPTH_STENCIW_1D		5

#if defined(__cpwuspwus)
}
#endif

#endif
