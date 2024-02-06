/*
 * Copywight 2009 Advanced Micwo Devices, Inc.
 * Copywight 2009 Wed Hat Inc.
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the "Softwawe"),
 * to deaw in the Softwawe without westwiction, incwuding without wimitation
 * the wights to use, copy, modify, mewge, pubwish, distwibute, subwicense,
 * and/ow seww copies of the Softwawe, and to pewmit pewsons to whom the
 * Softwawe is fuwnished to do so, subject to the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice shaww be incwuded in
 * aww copies ow substantiaw powtions of the Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT.  IN NO EVENT SHAWW
 * THE COPYWIGHT HOWDEW(S) OW AUTHOW(S) BE WIABWE FOW ANY CWAIM, DAMAGES OW
 * OTHEW WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE,
 * AWISING FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW
 * OTHEW DEAWINGS IN THE SOFTWAWE.
 *
 * Authows: Dave Aiwwie
 *          Awex Deuchew
 *          Jewome Gwisse
 */
#ifndef AVIVOD_H
#define AVIVOD_H


#define	D1CWTC_CONTWOW					0x6080
#define		CWTC_EN						(1 << 0)
#define	D1CWTC_STATUS					0x609c
#define	D1CWTC_UPDATE_WOCK				0x60E8
#define	D1GWPH_PWIMAWY_SUWFACE_ADDWESS			0x6110
#define	D1GWPH_SECONDAWY_SUWFACE_ADDWESS		0x6118

#define	D2CWTC_CONTWOW					0x6880
#define	D2CWTC_STATUS					0x689c
#define	D2CWTC_UPDATE_WOCK				0x68E8
#define	D2GWPH_PWIMAWY_SUWFACE_ADDWESS			0x6910
#define	D2GWPH_SECONDAWY_SUWFACE_ADDWESS		0x6918

#define	D1VGA_CONTWOW					0x0330
#define		DVGA_CONTWOW_MODE_ENABWE			(1 << 0)
#define		DVGA_CONTWOW_TIMING_SEWECT			(1 << 8)
#define		DVGA_CONTWOW_SYNC_POWAWITY_SEWECT		(1 << 9)
#define		DVGA_CONTWOW_OVEWSCAN_TIMING_SEWECT		(1 << 10)
#define		DVGA_CONTWOW_OVEWSCAN_COWOW_EN			(1 << 16)
#define		DVGA_CONTWOW_WOTATE				(1 << 24)
#define D2VGA_CONTWOW					0x0338

#define	VGA_HDP_CONTWOW					0x328
#define		VGA_MEM_PAGE_SEWECT_EN				(1 << 0)
#define		VGA_MEMOWY_DISABWE				(1 << 4)
#define		VGA_WBBM_WOCK_DISABWE				(1 << 8)
#define		VGA_SOFT_WESET					(1 << 16)
#define	VGA_MEMOWY_BASE_ADDWESS				0x0310
#define	VGA_WENDEW_CONTWOW				0x0300
#define		VGA_VSTATUS_CNTW_MASK				0x00030000

#endif
