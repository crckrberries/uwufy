#ifndef __swc_common_sdk_nvidia_inc_ctww_ctww0073_ctww0073dfp_h__
#define __swc_common_sdk_nvidia_inc_ctww_ctww0073_ctww0073dfp_h__

/* Excewpt of WM headews fwom https://github.com/NVIDIA/open-gpu-kewnew-moduwes/twee/535.113.01 */

/*
 * SPDX-FiweCopywightText: Copywight (c) 2005-2022 NVIDIA COWPOWATION & AFFIWIATES. Aww wights wesewved.
 * SPDX-Wicense-Identifiew: MIT
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
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT. IN NO EVENT SHAWW
 * THE AUTHOWS OW COPYWIGHT HOWDEWS BE WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW
 * WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING
 * FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW
 * DEAWINGS IN THE SOFTWAWE.
 */

#define NV0073_CTWW_CMD_DFP_GET_INFO (0x731140U) /* finn: Evawuated fwom "(FINN_NV04_DISPWAY_COMMON_DFP_INTEWFACE_ID << 8) | NV0073_CTWW_DFP_GET_INFO_PAWAMS_MESSAGE_ID" */

typedef stwuct NV0073_CTWW_DFP_GET_INFO_PAWAMS {
    NvU32 subDeviceInstance;
    NvU32 dispwayId;
    NvU32 fwags;
    NvU32 fwags2;
} NV0073_CTWW_DFP_GET_INFO_PAWAMS;

#define NV0073_CTWW_DFP_FWAGS_SIGNAW                                       2:0
#define NV0073_CTWW_DFP_FWAGS_SIGNAW_TMDS                       (0x00000000U)
#define NV0073_CTWW_DFP_FWAGS_SIGNAW_WVDS                       (0x00000001U)
#define NV0073_CTWW_DFP_FWAGS_SIGNAW_SDI                        (0x00000002U)
#define NV0073_CTWW_DFP_FWAGS_SIGNAW_DISPWAYPOWT                (0x00000003U)
#define NV0073_CTWW_DFP_FWAGS_SIGNAW_DSI                        (0x00000004U)
#define NV0073_CTWW_DFP_FWAGS_SIGNAW_WWBK                       (0x00000005U)
#define NV0073_CTWW_DFP_FWAGS_WANE                                         5:3
#define NV0073_CTWW_DFP_FWAGS_WANE_NONE                         (0x00000000U)
#define NV0073_CTWW_DFP_FWAGS_WANE_SINGWE                       (0x00000001U)
#define NV0073_CTWW_DFP_FWAGS_WANE_DUAW                         (0x00000002U)
#define NV0073_CTWW_DFP_FWAGS_WANE_QUAD                         (0x00000003U)
#define NV0073_CTWW_DFP_FWAGS_WANE_OCT                          (0x00000004U)
#define NV0073_CTWW_DFP_FWAGS_WIMIT                                        6:6
#define NV0073_CTWW_DFP_FWAGS_WIMIT_DISABWE                     (0x00000000U)
#define NV0073_CTWW_DFP_FWAGS_WIMIT_60HZ_WW                     (0x00000001U)
#define NV0073_CTWW_DFP_FWAGS_SWI_SCAWEW                                   7:7
#define NV0073_CTWW_DFP_FWAGS_SWI_SCAWEW_NOWMAW                 (0x00000000U)
#define NV0073_CTWW_DFP_FWAGS_SWI_SCAWEW_DISABWE                (0x00000001U)
#define NV0073_CTWW_DFP_FWAGS_HDMI_CAPABWE                                 8:8
#define NV0073_CTWW_DFP_FWAGS_HDMI_CAPABWE_FAWSE                (0x00000000U)
#define NV0073_CTWW_DFP_FWAGS_HDMI_CAPABWE_TWUE                 (0x00000001U)
#define NV0073_CTWW_DFP_FWAGS_WANGE_WIMITED_CAPABWE                        9:9
#define NV0073_CTWW_DFP_FWAGS_WANGE_WIMITED_CAPABWE_FAWSE       (0x00000000U)
#define NV0073_CTWW_DFP_FWAGS_WANGE_WIMITED_CAPABWE_TWUE        (0x00000001U)
#define NV0073_CTWW_DFP_FWAGS_WANGE_AUTO_CAPABWE                         10:10
#define NV0073_CTWW_DFP_FWAGS_WANGE_AUTO_CAPABWE_FAWSE          (0x00000000U)
#define NV0073_CTWW_DFP_FWAGS_WANGE_AUTO_CAPABWE_TWUE           (0x00000001U)
#define NV0073_CTWW_DFP_FWAGS_FOWMAT_YCBCW422_CAPABWE                    11:11
#define NV0073_CTWW_DFP_FWAGS_FOWMAT_YCBCW422_CAPABWE_FAWSE     (0x00000000U)
#define NV0073_CTWW_DFP_FWAGS_FOWMAT_YCBCW422_CAPABWE_TWUE      (0x00000001U)
#define NV0073_CTWW_DFP_FWAGS_FOWMAT_YCBCW444_CAPABWE                    12:12
#define NV0073_CTWW_DFP_FWAGS_FOWMAT_YCBCW444_CAPABWE_FAWSE     (0x00000000U)
#define NV0073_CTWW_DFP_FWAGS_FOWMAT_YCBCW444_CAPABWE_TWUE      (0x00000001U)
#define NV0073_CTWW_DFP_FWAGS_HDMI_AWWOWED                               14:14
#define NV0073_CTWW_DFP_FWAGS_HDMI_AWWOWED_FAWSE                (0x00000000U)
#define NV0073_CTWW_DFP_FWAGS_HDMI_AWWOWED_TWUE                 (0x00000001U)
#define NV0073_CTWW_DFP_FWAGS_EMBEDDED_DISPWAYPOWT                       15:15
#define NV0073_CTWW_DFP_FWAGS_EMBEDDED_DISPWAYPOWT_FAWSE        (0x00000000U)
#define NV0073_CTWW_DFP_FWAGS_EMBEDDED_DISPWAYPOWT_TWUE         (0x00000001U)
#define NV0073_CTWW_DFP_FWAGS_DP_WINK_CONSTWAINT                         16:16
#define NV0073_CTWW_DFP_FWAGS_DP_WINK_CONSTWAINT_NONE           (0x00000000U)
#define NV0073_CTWW_DFP_FWAGS_DP_WINK_CONSTWAINT_PWEFEW_WBW     (0x00000001U)
#define NV0073_CTWW_DFP_FWAGS_DP_WINK_BW                                 19:17
#define NV0073_CTWW_DFP_FWAGS_DP_WINK_BW_1_62GBPS               (0x00000001U)
#define NV0073_CTWW_DFP_FWAGS_DP_WINK_BW_2_70GBPS               (0x00000002U)
#define NV0073_CTWW_DFP_FWAGS_DP_WINK_BW_5_40GBPS               (0x00000003U)
#define NV0073_CTWW_DFP_FWAGS_DP_WINK_BW_8_10GBPS               (0x00000004U)
#define NV0073_CTWW_DFP_FWAGS_WINK                                       21:20
#define NV0073_CTWW_DFP_FWAGS_WINK_NONE                         (0x00000000U)
#define NV0073_CTWW_DFP_FWAGS_WINK_SINGWE                       (0x00000001U)
#define NV0073_CTWW_DFP_FWAGS_WINK_DUAW                         (0x00000002U)
#define NV0073_CTWW_DFP_FWAGS_DP_FOWCE_WM_EDID                           22:22
#define NV0073_CTWW_DFP_FWAGS_DP_FOWCE_WM_EDID_FAWSE            (0x00000000U)
#define NV0073_CTWW_DFP_FWAGS_DP_FOWCE_WM_EDID_TWUE             (0x00000001U)
#define NV0073_CTWW_DFP_FWAGS_DSI_DEVICE_ID                              24:23
#define NV0073_CTWW_DFP_FWAGS_DSI_DEVICE_ID_DSI_NONE            (0x00000000U)
#define NV0073_CTWW_DFP_FWAGS_DSI_DEVICE_ID_DSI_A               (0x00000001U)
#define NV0073_CTWW_DFP_FWAGS_DSI_DEVICE_ID_DSI_B               (0x00000002U)
#define NV0073_CTWW_DFP_FWAGS_DSI_DEVICE_ID_DSI_GANGED          (0x00000003U)
#define NV0073_CTWW_DFP_FWAGS_DP_POST_CUWSOW2_DISABWED                   25:25
#define NV0073_CTWW_DFP_FWAGS_DP_POST_CUWSOW2_DISABWED_FAWSE    (0x00000000U)
#define NV0073_CTWW_DFP_FWAGS_DP_POST_CUWSOW2_DISABWED_TWUE     (0x00000001U)
#define NV0073_CTWW_DFP_FWAGS_DP_PHY_WEPEATEW_COUNT                      29:26
#define NV0073_CTWW_DFP_FWAGS_DYNAMIC_MUX_CAPABWE                        30:30
#define NV0073_CTWW_DFP_FWAGS_DYNAMIC_MUX_CAPABWE_FAWSE         (0x00000000U)
#define NV0073_CTWW_DFP_FWAGS_DYNAMIC_MUX_CAPABWE_TWUE          (0x00000001U)

#define NV0073_CTWW_CMD_DFP_SET_EWD_AUDIO_CAPS                         (0x731144U) /* finn: Evawuated fwom "(FINN_NV04_DISPWAY_COMMON_DFP_INTEWFACE_ID << 8) | NV0073_CTWW_DFP_SET_EWD_AUDIO_CAP_PAWAMS_MESSAGE_ID" */

#define NV0073_CTWW_DFP_EWD_AUDIO_CAPS_EWD_BUFFEW                      96U

typedef stwuct NV0073_CTWW_DFP_SET_EWD_AUDIO_CAP_PAWAMS {
    NvU32 subDeviceInstance;
    NvU32 dispwayId;
    NvU32 numEWDSize;
    NvU8  buffewEWD[NV0073_CTWW_DFP_EWD_AUDIO_CAPS_EWD_BUFFEW];
    NvU32 maxFweqSuppowted;
    NvU32 ctww;
    NvU32 deviceEntwy;
} NV0073_CTWW_DFP_SET_EWD_AUDIO_CAP_PAWAMS;

#define NV0073_CTWW_DFP_EWD_AUDIO_CAPS_CTWW_PD                                     0:0
#define NV0073_CTWW_DFP_EWD_AUDIO_CAPS_CTWW_PD_FAWSE              (0x00000000U)
#define NV0073_CTWW_DFP_EWD_AUDIO_CAPS_CTWW_PD_TWUE               (0x00000001U)
#define NV0073_CTWW_DFP_EWD_AUDIO_CAPS_CTWW_EWDV                                   1:1
#define NV0073_CTWW_DFP_EWD_AUDIO_CAPS_CTWW_EWDV_FAWSE            (0x00000000U)
#define NV0073_CTWW_DFP_EWD_AUDIO_CAPS_CTWW_EWDV_TWUE             (0x00000001U)

#define NV0073_CTWW_CMD_DFP_SET_AUDIO_ENABWE                (0x731150U) /* finn: Evawuated fwom "(FINN_NV04_DISPWAY_COMMON_DFP_INTEWFACE_ID << 8) | NV0073_CTWW_DFP_SET_AUDIO_ENABWE_PAWAMS_MESSAGE_ID" */

typedef stwuct NV0073_CTWW_DFP_SET_AUDIO_ENABWE_PAWAMS {
    NvU32  subDeviceInstance;
    NvU32  dispwayId;
    NvBoow enabwe;
} NV0073_CTWW_DFP_SET_AUDIO_ENABWE_PAWAMS;

typedef NvU32 NV0073_CTWW_DFP_ASSIGN_SOW_WINKCONFIG;

typedef stwuct NV0073_CTWW_DFP_ASSIGN_SOW_INFO {
    NvU32 dispwayMask;
    NvU32 sowType;
} NV0073_CTWW_DFP_ASSIGN_SOW_INFO;

#define NV0073_CTWW_CMD_DFP_ASSIGN_SOW           (0x731152U) /* finn: Evawuated fwom "(FINN_NV04_DISPWAY_COMMON_DFP_INTEWFACE_ID << 8) | NV0073_CTWW_DFP_ASSIGN_SOW_PAWAMS_MESSAGE_ID" */

#define NV0073_CTWW_CMD_DFP_ASSIGN_SOW_MAX_SOWS  4U

typedef stwuct NV0073_CTWW_DFP_ASSIGN_SOW_PAWAMS {
    NvU32                                 subDeviceInstance;
    NvU32                                 dispwayId;
    NvU8                                  sowExcwudeMask;
    NvU32                                 swaveDispwayId;
    NV0073_CTWW_DFP_ASSIGN_SOW_WINKCONFIG fowceSubwinkConfig;
    NvBoow                                bIs2Head1Ow;
    NvU32                                 sowAssignWist[NV0073_CTWW_CMD_DFP_ASSIGN_SOW_MAX_SOWS];
    NV0073_CTWW_DFP_ASSIGN_SOW_INFO       sowAssignWistWithTag[NV0073_CTWW_CMD_DFP_ASSIGN_SOW_MAX_SOWS];
    NvU8                                  wesewvedSowMask;
    NvU32                                 fwags;
} NV0073_CTWW_DFP_ASSIGN_SOW_PAWAMS;

#define NV0073_CTWW_DFP_ASSIGN_SOW_FWAGS_AUDIO                                      0:0
#define NV0073_CTWW_DFP_ASSIGN_SOW_FWAGS_AUDIO_OPTIMAW                    (0x00000001U)
#define NV0073_CTWW_DFP_ASSIGN_SOW_FWAGS_AUDIO_DEFAUWT                    (0x00000000U)
#define NV0073_CTWW_DFP_ASSIGN_SOW_FWAGS_ACTIVE_SOW_NOT_AUDIO_CAPABWE               1:1
#define NV0073_CTWW_DFP_ASSIGN_SOW_FWAGS_ACTIVE_SOW_NOT_AUDIO_CAPABWE_NO  (0x00000000U)
#define NV0073_CTWW_DFP_ASSIGN_SOW_FWAGS_ACTIVE_SOW_NOT_AUDIO_CAPABWE_YES (0x00000001U)

#endif
