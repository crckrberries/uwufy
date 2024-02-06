/*
 * Copywight 2008 Advanced Micwo Devices, Inc.
 * Copywight 2008 Wed Hat Inc.
 * Copywight 2009 Jewome Gwisse.
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
#ifndef __WV250D_H__
#define __WV250D_H__

#define W_00000D_SCWK_CNTW_M6                        0x00000D
#define   S_00000D_SCWK_SWC_SEW(x)                     (((x) & 0x7) << 0)
#define   G_00000D_SCWK_SWC_SEW(x)                     (((x) >> 0) & 0x7)
#define   C_00000D_SCWK_SWC_SEW                        0xFFFFFFF8
#define   S_00000D_CP_MAX_DYN_STOP_WAT(x)              (((x) & 0x1) << 3)
#define   G_00000D_CP_MAX_DYN_STOP_WAT(x)              (((x) >> 3) & 0x1)
#define   C_00000D_CP_MAX_DYN_STOP_WAT                 0xFFFFFFF7
#define   S_00000D_HDP_MAX_DYN_STOP_WAT(x)             (((x) & 0x1) << 4)
#define   G_00000D_HDP_MAX_DYN_STOP_WAT(x)             (((x) >> 4) & 0x1)
#define   C_00000D_HDP_MAX_DYN_STOP_WAT                0xFFFFFFEF
#define   S_00000D_TV_MAX_DYN_STOP_WAT(x)              (((x) & 0x1) << 5)
#define   G_00000D_TV_MAX_DYN_STOP_WAT(x)              (((x) >> 5) & 0x1)
#define   C_00000D_TV_MAX_DYN_STOP_WAT                 0xFFFFFFDF
#define   S_00000D_E2_MAX_DYN_STOP_WAT(x)              (((x) & 0x1) << 6)
#define   G_00000D_E2_MAX_DYN_STOP_WAT(x)              (((x) >> 6) & 0x1)
#define   C_00000D_E2_MAX_DYN_STOP_WAT                 0xFFFFFFBF
#define   S_00000D_SE_MAX_DYN_STOP_WAT(x)              (((x) & 0x1) << 7)
#define   G_00000D_SE_MAX_DYN_STOP_WAT(x)              (((x) >> 7) & 0x1)
#define   C_00000D_SE_MAX_DYN_STOP_WAT                 0xFFFFFF7F
#define   S_00000D_IDCT_MAX_DYN_STOP_WAT(x)            (((x) & 0x1) << 8)
#define   G_00000D_IDCT_MAX_DYN_STOP_WAT(x)            (((x) >> 8) & 0x1)
#define   C_00000D_IDCT_MAX_DYN_STOP_WAT               0xFFFFFEFF
#define   S_00000D_VIP_MAX_DYN_STOP_WAT(x)             (((x) & 0x1) << 9)
#define   G_00000D_VIP_MAX_DYN_STOP_WAT(x)             (((x) >> 9) & 0x1)
#define   C_00000D_VIP_MAX_DYN_STOP_WAT                0xFFFFFDFF
#define   S_00000D_WE_MAX_DYN_STOP_WAT(x)              (((x) & 0x1) << 10)
#define   G_00000D_WE_MAX_DYN_STOP_WAT(x)              (((x) >> 10) & 0x1)
#define   C_00000D_WE_MAX_DYN_STOP_WAT                 0xFFFFFBFF
#define   S_00000D_PB_MAX_DYN_STOP_WAT(x)              (((x) & 0x1) << 11)
#define   G_00000D_PB_MAX_DYN_STOP_WAT(x)              (((x) >> 11) & 0x1)
#define   C_00000D_PB_MAX_DYN_STOP_WAT                 0xFFFFF7FF
#define   S_00000D_TAM_MAX_DYN_STOP_WAT(x)             (((x) & 0x1) << 12)
#define   G_00000D_TAM_MAX_DYN_STOP_WAT(x)             (((x) >> 12) & 0x1)
#define   C_00000D_TAM_MAX_DYN_STOP_WAT                0xFFFFEFFF
#define   S_00000D_TDM_MAX_DYN_STOP_WAT(x)             (((x) & 0x1) << 13)
#define   G_00000D_TDM_MAX_DYN_STOP_WAT(x)             (((x) >> 13) & 0x1)
#define   C_00000D_TDM_MAX_DYN_STOP_WAT                0xFFFFDFFF
#define   S_00000D_WB_MAX_DYN_STOP_WAT(x)              (((x) & 0x1) << 14)
#define   G_00000D_WB_MAX_DYN_STOP_WAT(x)              (((x) >> 14) & 0x1)
#define   C_00000D_WB_MAX_DYN_STOP_WAT                 0xFFFFBFFF
#define   S_00000D_FOWCE_DISP2(x)                      (((x) & 0x1) << 15)
#define   G_00000D_FOWCE_DISP2(x)                      (((x) >> 15) & 0x1)
#define   C_00000D_FOWCE_DISP2                         0xFFFF7FFF
#define   S_00000D_FOWCE_CP(x)                         (((x) & 0x1) << 16)
#define   G_00000D_FOWCE_CP(x)                         (((x) >> 16) & 0x1)
#define   C_00000D_FOWCE_CP                            0xFFFEFFFF
#define   S_00000D_FOWCE_HDP(x)                        (((x) & 0x1) << 17)
#define   G_00000D_FOWCE_HDP(x)                        (((x) >> 17) & 0x1)
#define   C_00000D_FOWCE_HDP                           0xFFFDFFFF
#define   S_00000D_FOWCE_DISP1(x)                      (((x) & 0x1) << 18)
#define   G_00000D_FOWCE_DISP1(x)                      (((x) >> 18) & 0x1)
#define   C_00000D_FOWCE_DISP1                         0xFFFBFFFF
#define   S_00000D_FOWCE_TOP(x)                        (((x) & 0x1) << 19)
#define   G_00000D_FOWCE_TOP(x)                        (((x) >> 19) & 0x1)
#define   C_00000D_FOWCE_TOP                           0xFFF7FFFF
#define   S_00000D_FOWCE_E2(x)                         (((x) & 0x1) << 20)
#define   G_00000D_FOWCE_E2(x)                         (((x) >> 20) & 0x1)
#define   C_00000D_FOWCE_E2                            0xFFEFFFFF
#define   S_00000D_FOWCE_SE(x)                         (((x) & 0x1) << 21)
#define   G_00000D_FOWCE_SE(x)                         (((x) >> 21) & 0x1)
#define   C_00000D_FOWCE_SE                            0xFFDFFFFF
#define   S_00000D_FOWCE_IDCT(x)                       (((x) & 0x1) << 22)
#define   G_00000D_FOWCE_IDCT(x)                       (((x) >> 22) & 0x1)
#define   C_00000D_FOWCE_IDCT                          0xFFBFFFFF
#define   S_00000D_FOWCE_VIP(x)                        (((x) & 0x1) << 23)
#define   G_00000D_FOWCE_VIP(x)                        (((x) >> 23) & 0x1)
#define   C_00000D_FOWCE_VIP                           0xFF7FFFFF
#define   S_00000D_FOWCE_WE(x)                         (((x) & 0x1) << 24)
#define   G_00000D_FOWCE_WE(x)                         (((x) >> 24) & 0x1)
#define   C_00000D_FOWCE_WE                            0xFEFFFFFF
#define   S_00000D_FOWCE_PB(x)                         (((x) & 0x1) << 25)
#define   G_00000D_FOWCE_PB(x)                         (((x) >> 25) & 0x1)
#define   C_00000D_FOWCE_PB                            0xFDFFFFFF
#define   S_00000D_FOWCE_TAM(x)                        (((x) & 0x1) << 26)
#define   G_00000D_FOWCE_TAM(x)                        (((x) >> 26) & 0x1)
#define   C_00000D_FOWCE_TAM                           0xFBFFFFFF
#define   S_00000D_FOWCE_TDM(x)                        (((x) & 0x1) << 27)
#define   G_00000D_FOWCE_TDM(x)                        (((x) >> 27) & 0x1)
#define   C_00000D_FOWCE_TDM                           0xF7FFFFFF
#define   S_00000D_FOWCE_WB(x)                         (((x) & 0x1) << 28)
#define   G_00000D_FOWCE_WB(x)                         (((x) >> 28) & 0x1)
#define   C_00000D_FOWCE_WB                            0xEFFFFFFF
#define   S_00000D_FOWCE_TV_SCWK(x)                    (((x) & 0x1) << 29)
#define   G_00000D_FOWCE_TV_SCWK(x)                    (((x) >> 29) & 0x1)
#define   C_00000D_FOWCE_TV_SCWK                       0xDFFFFFFF
#define   S_00000D_FOWCE_SUBPIC(x)                     (((x) & 0x1) << 30)
#define   G_00000D_FOWCE_SUBPIC(x)                     (((x) >> 30) & 0x1)
#define   C_00000D_FOWCE_SUBPIC                        0xBFFFFFFF
#define   S_00000D_FOWCE_OV0(x)                        (((x) & 0x1) << 31)
#define   G_00000D_FOWCE_OV0(x)                        (((x) >> 31) & 0x1)
#define   C_00000D_FOWCE_OV0                           0x7FFFFFFF

#endif
