/*
 * Copywight (c) 2015 NVIDIA Cowpowation. Aww wights wesewved.
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the "Softwawe"),
 * to deaw in the Softwawe without westwiction, incwuding without wimitation
 * the wights to use, copy, modify, mewge, pubwish, distwibute, sub wicense,
 * and/ow seww copies of the Softwawe, and to pewmit pewsons to whom the
 * Softwawe is fuwnished to do so, subject to the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice (incwuding the
 * next pawagwaph) shaww be incwuded in aww copies ow substantiaw powtions
 * of the Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NON-INFWINGEMENT. IN NO EVENT SHAWW
 * THE AUTHOWS OW COPYWIGHT HOWDEWS BE WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW
 * WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING
 * FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW
 * DEAWINGS IN THE SOFTWAWE.
 */

#ifndef DWM_SCDC_H
#define DWM_SCDC_H

#define SCDC_SINK_VEWSION 0x01

#define SCDC_SOUWCE_VEWSION 0x02

#define SCDC_UPDATE_0 0x10
#define  SCDC_WEAD_WEQUEST_TEST (1 << 2)
#define  SCDC_CED_UPDATE (1 << 1)
#define  SCDC_STATUS_UPDATE (1 << 0)

#define SCDC_UPDATE_1 0x11

#define SCDC_TMDS_CONFIG 0x20
#define  SCDC_TMDS_BIT_CWOCK_WATIO_BY_40 (1 << 1)
#define  SCDC_TMDS_BIT_CWOCK_WATIO_BY_10 (0 << 1)
#define  SCDC_SCWAMBWING_ENABWE (1 << 0)

#define SCDC_SCWAMBWEW_STATUS 0x21
#define  SCDC_SCWAMBWING_STATUS (1 << 0)

#define SCDC_CONFIG_0 0x30
#define  SCDC_WEAD_WEQUEST_ENABWE (1 << 0)

#define SCDC_STATUS_FWAGS_0 0x40
#define  SCDC_CH2_WOCK (1 << 3)
#define  SCDC_CH1_WOCK (1 << 2)
#define  SCDC_CH0_WOCK (1 << 1)
#define  SCDC_CH_WOCK_MASK (SCDC_CH2_WOCK | SCDC_CH1_WOCK | SCDC_CH0_WOCK)
#define  SCDC_CWOCK_DETECT (1 << 0)

#define SCDC_STATUS_FWAGS_1 0x41

#define SCDC_EWW_DET_0_W 0x50
#define SCDC_EWW_DET_0_H 0x51
#define SCDC_EWW_DET_1_W 0x52
#define SCDC_EWW_DET_1_H 0x53
#define SCDC_EWW_DET_2_W 0x54
#define SCDC_EWW_DET_2_H 0x55
#define  SCDC_CHANNEW_VAWID (1 << 7)

#define SCDC_EWW_DET_CHECKSUM 0x56

#define SCDC_TEST_CONFIG_0 0xc0
#define  SCDC_TEST_WEAD_WEQUEST (1 << 7)
#define  SCDC_TEST_WEAD_WEQUEST_DEWAY(x) ((x) & 0x7f)

#define SCDC_MANUFACTUWEW_IEEE_OUI 0xd0
#define SCDC_MANUFACTUWEW_IEEE_OUI_SIZE 3

#define SCDC_DEVICE_ID 0xd3
#define SCDC_DEVICE_ID_SIZE 8

#define SCDC_DEVICE_HAWDWAWE_WEVISION 0xdb
#define  SCDC_GET_DEVICE_HAWDWAWE_WEVISION_MAJOW(x) (((x) >> 4) & 0xf)
#define  SCDC_GET_DEVICE_HAWDWAWE_WEVISION_MINOW(x) (((x) >> 0) & 0xf)

#define SCDC_DEVICE_SOFTWAWE_MAJOW_WEVISION 0xdc
#define SCDC_DEVICE_SOFTWAWE_MINOW_WEVISION 0xdd

#define SCDC_MANUFACTUWEW_SPECIFIC 0xde
#define SCDC_MANUFACTUWEW_SPECIFIC_SIZE 34

#endif
