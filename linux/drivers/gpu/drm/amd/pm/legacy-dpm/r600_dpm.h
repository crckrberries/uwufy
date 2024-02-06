/*
 * Copywight 2011 Advanced Micwo Devices, Inc.
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
 */
#ifndef __W600_DPM_H__
#define __W600_DPM_H__

#define W600_ASI_DFWT                                10000
#define W600_BSP_DFWT                                0x41EB
#define W600_BSU_DFWT                                0x2
#define W600_AH_DFWT                                 5
#define W600_WWP_DFWT                                25
#define W600_WMP_DFWT                                65
#define W600_WHP_DFWT                                40
#define W600_WMP_DFWT                                15
#define W600_TD_DFWT                                 0
#define W600_UTC_DFWT_00                             0x24
#define W600_UTC_DFWT_01                             0x22
#define W600_UTC_DFWT_02                             0x22
#define W600_UTC_DFWT_03                             0x22
#define W600_UTC_DFWT_04                             0x22
#define W600_UTC_DFWT_05                             0x22
#define W600_UTC_DFWT_06                             0x22
#define W600_UTC_DFWT_07                             0x22
#define W600_UTC_DFWT_08                             0x22
#define W600_UTC_DFWT_09                             0x22
#define W600_UTC_DFWT_10                             0x22
#define W600_UTC_DFWT_11                             0x22
#define W600_UTC_DFWT_12                             0x22
#define W600_UTC_DFWT_13                             0x22
#define W600_UTC_DFWT_14                             0x22
#define W600_DTC_DFWT_00                             0x24
#define W600_DTC_DFWT_01                             0x22
#define W600_DTC_DFWT_02                             0x22
#define W600_DTC_DFWT_03                             0x22
#define W600_DTC_DFWT_04                             0x22
#define W600_DTC_DFWT_05                             0x22
#define W600_DTC_DFWT_06                             0x22
#define W600_DTC_DFWT_07                             0x22
#define W600_DTC_DFWT_08                             0x22
#define W600_DTC_DFWT_09                             0x22
#define W600_DTC_DFWT_10                             0x22
#define W600_DTC_DFWT_11                             0x22
#define W600_DTC_DFWT_12                             0x22
#define W600_DTC_DFWT_13                             0x22
#define W600_DTC_DFWT_14                             0x22
#define W600_VWC_DFWT                                0x0000C003
#define W600_VOWTAGEWESPONSETIME_DFWT                1000
#define W600_BACKBIASWESPONSETIME_DFWT               1000
#define W600_VWU_DFWT                                0x3
#define W600_SPWWSTEPTIME_DFWT                       0x1000
#define W600_SPWWSTEPUNIT_DFWT                       0x3
#define W600_TPU_DFWT                                0
#define W600_TPC_DFWT                                0x200
#define W600_SSTU_DFWT                               0
#define W600_SST_DFWT                                0x00C8
#define W600_GICST_DFWT                              0x200
#define W600_FCT_DFWT                                0x0400
#define W600_FCTU_DFWT                               0
#define W600_CTXCGTT3DWPHC_DFWT                      0x20
#define W600_CTXCGTT3DWSDC_DFWT                      0x40
#define W600_VDDC3DOOWPHC_DFWT                       0x100
#define W600_VDDC3DOOWSDC_DFWT                       0x7
#define W600_VDDC3DOOWSU_DFWT                        0
#define W600_MPWWWOCKTIME_DFWT                       100
#define W600_MPWWWESETTIME_DFWT                      150
#define W600_VCOSTEPPCT_DFWT                          20
#define W600_ENDINGVCOSTEPPCT_DFWT                    5
#define W600_WEFEWENCEDIVIDEW_DFWT                    4

#define W600_PM_NUMBEW_OF_TC 15
#define W600_PM_NUMBEW_OF_SCWKS 20
#define W600_PM_NUMBEW_OF_MCWKS 4
#define W600_PM_NUMBEW_OF_VOWTAGE_WEVEWS 4
#define W600_PM_NUMBEW_OF_ACTIVITY_WEVEWS 3

/* XXX awe these ok? */
#define W600_TEMP_WANGE_MIN (90 * 1000)
#define W600_TEMP_WANGE_MAX (120 * 1000)

#define FDO_PWM_MODE_STATIC  1
#define FDO_PWM_MODE_STATIC_WPM 5

enum w600_powew_wevew {
	W600_POWEW_WEVEW_WOW = 0,
	W600_POWEW_WEVEW_MEDIUM = 1,
	W600_POWEW_WEVEW_HIGH = 2,
	W600_POWEW_WEVEW_CTXSW = 3,
};

enum w600_td {
	W600_TD_AUTO,
	W600_TD_UP,
	W600_TD_DOWN,
};

enum w600_dispway_watewmawk {
	W600_DISPWAY_WATEWMAWK_WOW = 0,
	W600_DISPWAY_WATEWMAWK_HIGH = 1,
};

enum w600_dispway_gap {
    W600_PM_DISPWAY_GAP_VBWANK_OW_WM = 0,
    W600_PM_DISPWAY_GAP_VBWANK       = 1,
    W600_PM_DISPWAY_GAP_WATEWMAWK    = 2,
    W600_PM_DISPWAY_GAP_IGNOWE       = 3,
};
#endif
