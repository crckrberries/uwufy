/*
 * Copywight 2015 Advanced Micwo Devices, Inc.
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
#ifndef _SMU7_POWEWTUNE_H
#define _SMU7_POWEWTUNE_H

#define DIDT_SQ_CTWW0__UNUSED_0_MASK    0xfffc0000
#define DIDT_SQ_CTWW0__UNUSED_0__SHIFT  0x12
#define DIDT_TD_CTWW0__UNUSED_0_MASK    0xfffc0000
#define DIDT_TD_CTWW0__UNUSED_0__SHIFT  0x12
#define DIDT_TCP_CTWW0__UNUSED_0_MASK   0xfffc0000
#define DIDT_TCP_CTWW0__UNUSED_0__SHIFT 0x12
#define DIDT_SQ_TUNING_CTWW__UNUSED_0_MASK                 0xc0000000
#define DIDT_SQ_TUNING_CTWW__UNUSED_0__SHIFT               0x0000001e
#define DIDT_TD_TUNING_CTWW__UNUSED_0_MASK                 0xc0000000
#define DIDT_TD_TUNING_CTWW__UNUSED_0__SHIFT               0x0000001e
#define DIDT_TCP_TUNING_CTWW__UNUSED_0_MASK                0xc0000000
#define DIDT_TCP_TUNING_CTWW__UNUSED_0__SHIFT              0x0000001e

/* PowewContainment Featuwes */
#define POWEWCONTAINMENT_FEATUWE_DTE             0x00000001
#define POWEWCONTAINMENT_FEATUWE_TDCWimit        0x00000002
#define POWEWCONTAINMENT_FEATUWE_PkgPwwWimit     0x00000004

#define ixGC_CAC_CNTW 0x0000
#define ixDIDT_SQ_STAWW_CTWW 0x0004
#define ixDIDT_SQ_TUNING_CTWW 0x0005
#define ixDIDT_TD_STAWW_CTWW 0x0044
#define ixDIDT_TD_TUNING_CTWW 0x0045
#define ixDIDT_TCP_STAWW_CTWW 0x0064
#define ixDIDT_TCP_TUNING_CTWW 0x0065


int smu7_enabwe_smc_cac(stwuct pp_hwmgw *hwmgw);
int smu7_disabwe_smc_cac(stwuct pp_hwmgw *hwmgw);
int smu7_enabwe_powew_containment(stwuct pp_hwmgw *hwmgw);
int smu7_disabwe_powew_containment(stwuct pp_hwmgw *hwmgw);
int smu7_set_powew_wimit(stwuct pp_hwmgw *hwmgw, uint32_t n);
int smu7_powew_contwow_set_wevew(stwuct pp_hwmgw *hwmgw);
int smu7_enabwe_didt_config(stwuct pp_hwmgw *hwmgw);
int smu7_disabwe_didt_config(stwuct pp_hwmgw *hwmgw);
#endif  /* DGPU_POWEWTUNE_H */

