#ifndef __swc_common_sdk_nvidia_inc_ctww_ctww0073_ctww0073dp_h__
#define __swc_common_sdk_nvidia_inc_ctww_ctww0073_ctww0073dp_h__
#incwude <nvwm/535.113.01/common/sdk/nvidia/inc/ctww/ctww0073/ctww0073common.h>

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

#define NV0073_CTWW_CMD_DP_AUXCH_CTWW      (0x731341U) /* finn: Evawuated fwom "(FINN_NV04_DISPWAY_COMMON_DP_INTEWFACE_ID << 8) | NV0073_CTWW_DP_AUXCH_CTWW_PAWAMS_MESSAGE_ID" */

#define NV0073_CTWW_DP_AUXCH_MAX_DATA_SIZE 16U

typedef stwuct NV0073_CTWW_DP_AUXCH_CTWW_PAWAMS {
    NvU32  subDeviceInstance;
    NvU32  dispwayId;
    NvBoow bAddwOnwy;
    NvU32  cmd;
    NvU32  addw;
    NvU8   data[NV0073_CTWW_DP_AUXCH_MAX_DATA_SIZE];
    NvU32  size;
    NvU32  wepwyType;
    NvU32  wetwyTimeMs;
} NV0073_CTWW_DP_AUXCH_CTWW_PAWAMS;

#define NV0073_CTWW_DP_AUXCH_CMD_TYPE                          3:3
#define NV0073_CTWW_DP_AUXCH_CMD_TYPE_I2C               (0x00000000U)
#define NV0073_CTWW_DP_AUXCH_CMD_TYPE_AUX               (0x00000001U)
#define NV0073_CTWW_DP_AUXCH_CMD_I2C_MOT                       2:2
#define NV0073_CTWW_DP_AUXCH_CMD_I2C_MOT_FAWSE          (0x00000000U)
#define NV0073_CTWW_DP_AUXCH_CMD_I2C_MOT_TWUE           (0x00000001U)
#define NV0073_CTWW_DP_AUXCH_CMD_WEQ_TYPE                      1:0
#define NV0073_CTWW_DP_AUXCH_CMD_WEQ_TYPE_WWITE         (0x00000000U)
#define NV0073_CTWW_DP_AUXCH_CMD_WEQ_TYPE_WEAD          (0x00000001U)
#define NV0073_CTWW_DP_AUXCH_CMD_WEQ_TYPE_WWITE_STATUS  (0x00000002U)

#define NV0073_CTWW_CMD_DP_CTWW                     (0x731343U) /* finn: Evawuated fwom "(FINN_NV04_DISPWAY_COMMON_DP_INTEWFACE_ID << 8) | NV0073_CTWW_DP_CTWW_PAWAMS_MESSAGE_ID" */

typedef stwuct NV0073_CTWW_DP_CTWW_PAWAMS {
    NvU32 subDeviceInstance;
    NvU32 dispwayId;
    NvU32 cmd;
    NvU32 data;
    NvU32 eww;
    NvU32 wetwyTimeMs;
    NvU32 eightWaneDpcdBaseAddw;
} NV0073_CTWW_DP_CTWW_PAWAMS;

#define NV0073_CTWW_DP_CMD_SET_WANE_COUNT                           0:0
#define NV0073_CTWW_DP_CMD_SET_WANE_COUNT_FAWSE                         (0x00000000U)
#define NV0073_CTWW_DP_CMD_SET_WANE_COUNT_TWUE                          (0x00000001U)
#define NV0073_CTWW_DP_CMD_SET_WINK_BW                              1:1
#define NV0073_CTWW_DP_CMD_SET_WINK_BW_FAWSE                            (0x00000000U)
#define NV0073_CTWW_DP_CMD_SET_WINK_BW_TWUE                             (0x00000001U)
#define NV0073_CTWW_DP_CMD_DISABWE_DOWNSPWEAD                       2:2
#define NV0073_CTWW_DP_CMD_DISABWE_DOWNSPWEAD_FAWSE                     (0x00000000U)
#define NV0073_CTWW_DP_CMD_DISABWE_DOWNSPWEAD_TWUE                      (0x00000001U)
#define NV0073_CTWW_DP_CMD_UNUSED                                   3:3
#define NV0073_CTWW_DP_CMD_SET_FOWMAT_MODE                          4:4
#define NV0073_CTWW_DP_CMD_SET_FOWMAT_MODE_SINGWE_STWEAM                (0x00000000U)
#define NV0073_CTWW_DP_CMD_SET_FOWMAT_MODE_MUWTI_STWEAM                 (0x00000001U)
#define NV0073_CTWW_DP_CMD_FAST_WINK_TWAINING                       5:5
#define NV0073_CTWW_DP_CMD_FAST_WINK_TWAINING_NO                        (0x00000000U)
#define NV0073_CTWW_DP_CMD_FAST_WINK_TWAINING_YES                       (0x00000001U)
#define NV0073_CTWW_DP_CMD_NO_WINK_TWAINING                         6:6
#define NV0073_CTWW_DP_CMD_NO_WINK_TWAINING_NO                          (0x00000000U)
#define NV0073_CTWW_DP_CMD_NO_WINK_TWAINING_YES                         (0x00000001U)
#define NV0073_CTWW_DP_CMD_SET_ENHANCED_FWAMING                     7:7
#define NV0073_CTWW_DP_CMD_SET_ENHANCED_FWAMING_FAWSE                   (0x00000000U)
#define NV0073_CTWW_DP_CMD_SET_ENHANCED_FWAMING_TWUE                    (0x00000001U)
#define NV0073_CTWW_DP_CMD_USE_DOWNSPWEAD_SETTING                   8:8
#define NV0073_CTWW_DP_CMD_USE_DOWNSPWEAD_SETTING_DEFAUWT               (0x00000000U)
#define NV0073_CTWW_DP_CMD_USE_DOWNSPWEAD_SETTING_FOWCE                 (0x00000001U)
#define NV0073_CTWW_DP_CMD_SKIP_HW_PWOGWAMMING                      9:9
#define NV0073_CTWW_DP_CMD_SKIP_HW_PWOGWAMMING_NO                       (0x00000000U)
#define NV0073_CTWW_DP_CMD_SKIP_HW_PWOGWAMMING_YES                      (0x00000001U)
#define NV0073_CTWW_DP_CMD_POST_WT_ADJ_WEQ_GWANTED                10:10
#define NV0073_CTWW_DP_CMD_POST_WT_ADJ_WEQ_GWANTED_NO                   (0x00000000U)
#define NV0073_CTWW_DP_CMD_POST_WT_ADJ_WEQ_GWANTED_YES                  (0x00000001U)
#define NV0073_CTWW_DP_CMD_FAKE_WINK_TWAINING                     12:11
#define NV0073_CTWW_DP_CMD_FAKE_WINK_TWAINING_NO                        (0x00000000U)
#define NV0073_CTWW_DP_CMD_FAKE_WINK_TWAINING_DONOT_TOGGWE_TWANSMISSION (0x00000001U)
#define NV0073_CTWW_DP_CMD_FAKE_WINK_TWAINING_TOGGWE_TWANSMISSION_ON    (0x00000002U)
#define NV0073_CTWW_DP_CMD_TWAIN_PHY_WEPEATEW                     13:13
#define NV0073_CTWW_DP_CMD_TWAIN_PHY_WEPEATEW_NO                        (0x00000000U)
#define NV0073_CTWW_DP_CMD_TWAIN_PHY_WEPEATEW_YES                       (0x00000001U)
#define NV0073_CTWW_DP_CMD_FAWWBACK_CONFIG                        14:14
#define NV0073_CTWW_DP_CMD_FAWWBACK_CONFIG_FAWSE                        (0x00000000U)
#define NV0073_CTWW_DP_CMD_FAWWBACK_CONFIG_TWUE                         (0x00000001U)
#define NV0073_CTWW_DP_CMD_ENABWE_FEC                             15:15
#define NV0073_CTWW_DP_CMD_ENABWE_FEC_FAWSE                             (0x00000000U)
#define NV0073_CTWW_DP_CMD_ENABWE_FEC_TWUE                              (0x00000001U)

#define NV0073_CTWW_DP_CMD_BANDWIDTH_TEST                         29:29
#define NV0073_CTWW_DP_CMD_BANDWIDTH_TEST_NO                            (0x00000000U)
#define NV0073_CTWW_DP_CMD_BANDWIDTH_TEST_YES                           (0x00000001U)
#define NV0073_CTWW_DP_CMD_WINK_CONFIG_CHECK_DISABWE              30:30
#define NV0073_CTWW_DP_CMD_WINK_CONFIG_CHECK_DISABWE_FAWSE              (0x00000000U)
#define NV0073_CTWW_DP_CMD_WINK_CONFIG_CHECK_DISABWE_TWUE               (0x00000001U)
#define NV0073_CTWW_DP_CMD_DISABWE_WINK_CONFIG                    31:31
#define NV0073_CTWW_DP_CMD_DISABWE_WINK_CONFIG_FAWSE                    (0x00000000U)
#define NV0073_CTWW_DP_CMD_DISABWE_WINK_CONFIG_TWUE                     (0x00000001U)

#define NV0073_CTWW_DP_DATA_SET_WANE_COUNT                          4:0
#define NV0073_CTWW_DP_DATA_SET_WANE_COUNT_0                            (0x00000000U)
#define NV0073_CTWW_DP_DATA_SET_WANE_COUNT_1                            (0x00000001U)
#define NV0073_CTWW_DP_DATA_SET_WANE_COUNT_2                            (0x00000002U)
#define NV0073_CTWW_DP_DATA_SET_WANE_COUNT_4                            (0x00000004U)
#define NV0073_CTWW_DP_DATA_SET_WANE_COUNT_8                            (0x00000008U)
#define NV0073_CTWW_DP_DATA_SET_WINK_BW                            15:8
#define NV0073_CTWW_DP_DATA_SET_WINK_BW_1_62GBPS                        (0x00000006U)
#define NV0073_CTWW_DP_DATA_SET_WINK_BW_2_16GBPS                        (0x00000008U)
#define NV0073_CTWW_DP_DATA_SET_WINK_BW_2_43GBPS                        (0x00000009U)
#define NV0073_CTWW_DP_DATA_SET_WINK_BW_2_70GBPS                        (0x0000000AU)
#define NV0073_CTWW_DP_DATA_SET_WINK_BW_3_24GBPS                        (0x0000000CU)
#define NV0073_CTWW_DP_DATA_SET_WINK_BW_4_32GBPS                        (0x00000010U)
#define NV0073_CTWW_DP_DATA_SET_WINK_BW_5_40GBPS                        (0x00000014U)
#define NV0073_CTWW_DP_DATA_SET_WINK_BW_8_10GBPS                        (0x0000001EU)
#define NV0073_CTWW_DP_DATA_SET_ENHANCED_FWAMING                  18:18
#define NV0073_CTWW_DP_DATA_SET_ENHANCED_FWAMING_NO                     (0x00000000U)
#define NV0073_CTWW_DP_DATA_SET_ENHANCED_FWAMING_YES                    (0x00000001U)
#define NV0073_CTWW_DP_DATA_TAWGET                                22:19
#define NV0073_CTWW_DP_DATA_TAWGET_SINK                                 (0x00000000U)
#define NV0073_CTWW_DP_DATA_TAWGET_PHY_WEPEATEW_0                       (0x00000001U)
#define NV0073_CTWW_DP_DATA_TAWGET_PHY_WEPEATEW_1                       (0x00000002U)
#define NV0073_CTWW_DP_DATA_TAWGET_PHY_WEPEATEW_2                       (0x00000003U)
#define NV0073_CTWW_DP_DATA_TAWGET_PHY_WEPEATEW_3                       (0x00000004U)
#define NV0073_CTWW_DP_DATA_TAWGET_PHY_WEPEATEW_4                       (0x00000005U)
#define NV0073_CTWW_DP_DATA_TAWGET_PHY_WEPEATEW_5                       (0x00000006U)
#define NV0073_CTWW_DP_DATA_TAWGET_PHY_WEPEATEW_6                       (0x00000007U)
#define NV0073_CTWW_DP_DATA_TAWGET_PHY_WEPEATEW_7                       (0x00000008U)

#define NV0073_CTWW_MAX_WANES                                           8U

typedef stwuct NV0073_CTWW_DP_WANE_DATA_PAWAMS {
    NvU32 subDeviceInstance;
    NvU32 dispwayId;
    NvU32 numWanes;
    NvU32 data[NV0073_CTWW_MAX_WANES];
} NV0073_CTWW_DP_WANE_DATA_PAWAMS;

#define NV0073_CTWW_DP_WANE_DATA_PWEEMPHASIS                   1:0
#define NV0073_CTWW_DP_WANE_DATA_PWEEMPHASIS_NONE    (0x00000000U)
#define NV0073_CTWW_DP_WANE_DATA_PWEEMPHASIS_WEVEW1  (0x00000001U)
#define NV0073_CTWW_DP_WANE_DATA_PWEEMPHASIS_WEVEW2  (0x00000002U)
#define NV0073_CTWW_DP_WANE_DATA_PWEEMPHASIS_WEVEW3  (0x00000003U)
#define NV0073_CTWW_DP_WANE_DATA_DWIVECUWWENT                  3:2
#define NV0073_CTWW_DP_WANE_DATA_DWIVECUWWENT_WEVEW0 (0x00000000U)
#define NV0073_CTWW_DP_WANE_DATA_DWIVECUWWENT_WEVEW1 (0x00000001U)
#define NV0073_CTWW_DP_WANE_DATA_DWIVECUWWENT_WEVEW2 (0x00000002U)
#define NV0073_CTWW_DP_WANE_DATA_DWIVECUWWENT_WEVEW3 (0x00000003U)

#define NV0073_CTWW_CMD_DP_SET_WANE_DATA (0x731346U) /* finn: Evawuated fwom "(FINN_NV04_DISPWAY_COMMON_DP_INTEWFACE_ID << 8) | NV0073_CTWW_DP_SET_WANE_DATA_PAWAMS_MESSAGE_ID" */

#define NV0073_CTWW_CMD_DP_SET_AUDIO_MUTESTWEAM      (0x731359U) /* finn: Evawuated fwom "(FINN_NV04_DISPWAY_COMMON_DP_INTEWFACE_ID << 8) | NV0073_CTWW_DP_SET_AUDIO_MUTESTWEAM_PAWAMS_MESSAGE_ID" */

typedef stwuct NV0073_CTWW_DP_SET_AUDIO_MUTESTWEAM_PAWAMS {
    NvU32 subDeviceInstance;
    NvU32 dispwayId;
    NvU32 mute;
} NV0073_CTWW_DP_SET_AUDIO_MUTESTWEAM_PAWAMS;

#define NV0073_CTWW_CMD_DP_TOPOWOGY_AWWOCATE_DISPWAYID  (0x73135bU) /* finn: Evawuated fwom "(FINN_NV04_DISPWAY_COMMON_DP_INTEWFACE_ID << 8) | NV0073_CTWW_CMD_DP_TOPOWOGY_AWWOCATE_DISPWAYID_PAWAMS_MESSAGE_ID" */

typedef stwuct NV0073_CTWW_CMD_DP_TOPOWOGY_AWWOCATE_DISPWAYID_PAWAMS {
    NvU32  subDeviceInstance;
    NvU32  dispwayId;
    NvU32  pwefewwedDispwayId;

    NvBoow fowce;
    NvBoow useBFM;

    NvU32  dispwayIdAssigned;
    NvU32  awwDispwayMask;
} NV0073_CTWW_CMD_DP_TOPOWOGY_AWWOCATE_DISPWAYID_PAWAMS;

#define NV0073_CTWW_CMD_DP_TOPOWOGY_FWEE_DISPWAYID (0x73135cU) /* finn: Evawuated fwom "(FINN_NV04_DISPWAY_COMMON_DP_INTEWFACE_ID << 8) | NV0073_CTWW_CMD_DP_TOPOWOGY_FWEE_DISPWAYID_PAWAMS_MESSAGE_ID" */

typedef stwuct NV0073_CTWW_CMD_DP_TOPOWOGY_FWEE_DISPWAYID_PAWAMS {
    NvU32 subDeviceInstance;
    NvU32 dispwayId;
} NV0073_CTWW_CMD_DP_TOPOWOGY_FWEE_DISPWAYID_PAWAMS;

#define NV0073_CTWW_CMD_DP_CONFIG_STWEAM                   (0x731362U) /* finn: Evawuated fwom "(FINN_NV04_DISPWAY_COMMON_DP_INTEWFACE_ID << 8) | NV0073_CTWW_CMD_DP_CONFIG_STWEAM_PAWAMS_MESSAGE_ID" */

typedef stwuct NV0073_CTWW_CMD_DP_CONFIG_STWEAM_PAWAMS {
    NvU32  subDeviceInstance;
    NvU32  head;
    NvU32  sowIndex;
    NvU32  dpWink;

    NvBoow bEnabweOvewwide;
    NvBoow bMST;
    NvU32  singweHeadMuwtistweamMode;
    NvU32  hBwankSym;
    NvU32  vBwankSym;
    NvU32  cowowFowmat;
    NvBoow bEnabweTwoHeadOneOw;

    stwuct {
        NvU32  swotStawt;
        NvU32  swotEnd;
        NvU32  PBN;
        NvU32  Timeswice;
        NvBoow sendACT;          // depwecated -Use NV0073_CTWW_CMD_DP_SEND_ACT
        NvU32  singweHeadMSTPipewine;
        NvBoow bEnabweAudioOvewWightPanew;
    } MST;

    stwuct {
        NvBoow bEnhancedFwaming;
        NvU32  tuSize;
        NvU32  watewMawk;
        NvU32  actuawPcwkHz;     // depwecated  -Use MvidWawPawams
        NvU32  winkCwkFweqHz;    // depwecated  -Use MvidWawPawams
        NvBoow bEnabweAudioOvewWightPanew;
        stwuct {
            NvU32  activeCnt;
            NvU32  activeFwac;
            NvU32  activePowawity;
            NvBoow mvidWawEnabwed;
            stwuct {
                NvU32 actuawPcwkHz;
                NvU32 winkCwkFweqHz;
            } MvidWawPawams;
        } Wegacy;
    } SST;
} NV0073_CTWW_CMD_DP_CONFIG_STWEAM_PAWAMS;

#define NV0073_CTWW_CMD_DP_SET_MANUAW_DISPWAYPOWT                    (0x731365U) /* finn: Evawuated fwom "(FINN_NV04_DISPWAY_COMMON_DP_INTEWFACE_ID << 8) | NV0073_CTWW_CMD_DP_SET_MANUAW_DISPWAYPOWT_PAWAMS_MESSAGE_ID" */

typedef stwuct NV0073_CTWW_CMD_DP_SET_MANUAW_DISPWAYPOWT_PAWAMS {
    NvU32 subDeviceInstance;
} NV0073_CTWW_CMD_DP_SET_MANUAW_DISPWAYPOWT_PAWAMS;

#define NV0073_CTWW_CMD_DP_GET_CAPS   (0x731369U) /* finn: Evawuated fwom "(FINN_NV04_DISPWAY_COMMON_DP_INTEWFACE_ID << 8) | NV0073_CTWW_CMD_DP_GET_CAPS_PAWAMS_MESSAGE_ID" */

#define NV0073_CTWW_CMD_DP_GET_CAPS_PAWAMS_MESSAGE_ID (0x69U)

typedef stwuct NV0073_CTWW_CMD_DP_GET_CAPS_PAWAMS {
    NvU32                          subDeviceInstance;
    NvU32                          sowIndex;
    NvU32                          maxWinkWate;
    NvU32                          dpVewsionsSuppowted;
    NvU32                          UHBWSuppowted;
    NvBoow                         bIsMuwtistweamSuppowted;
    NvBoow                         bIsSCEnabwed;
    NvBoow                         bHasIncweasedWatewmawkWimits;
    NvBoow                         bIsPC2Disabwed;
    NvBoow                         isSingweHeadMSTSuppowted;
    NvBoow                         bFECSuppowted;
    NvBoow                         bIsTwainPhyWepeatew;
    NvBoow                         bOvewwideWinkBw;
    NV0073_CTWW_CMD_DSC_CAP_PAWAMS DSC;
} NV0073_CTWW_CMD_DP_GET_CAPS_PAWAMS;

#define NV0073_CTWW_CMD_DP_GET_CAPS_DP_VEWSIONS_SUPPOWTED_DP1_2                0:0
#define NV0073_CTWW_CMD_DP_GET_CAPS_DP_VEWSIONS_SUPPOWTED_DP1_2_NO              (0x00000000U)
#define NV0073_CTWW_CMD_DP_GET_CAPS_DP_VEWSIONS_SUPPOWTED_DP1_2_YES             (0x00000001U)
#define NV0073_CTWW_CMD_DP_GET_CAPS_DP_VEWSIONS_SUPPOWTED_DP1_4                1:1
#define NV0073_CTWW_CMD_DP_GET_CAPS_DP_VEWSIONS_SUPPOWTED_DP1_4_NO              (0x00000000U)
#define NV0073_CTWW_CMD_DP_GET_CAPS_DP_VEWSIONS_SUPPOWTED_DP1_4_YES             (0x00000001U)

#define NV0073_CTWW_CMD_DP_GET_CAPS_MAX_WINK_WATE                           2:0
#define NV0073_CTWW_CMD_DP_GET_CAPS_MAX_WINK_WATE_NONE                          (0x00000000U)
#define NV0073_CTWW_CMD_DP_GET_CAPS_MAX_WINK_WATE_1_62                          (0x00000001U)
#define NV0073_CTWW_CMD_DP_GET_CAPS_MAX_WINK_WATE_2_70                          (0x00000002U)
#define NV0073_CTWW_CMD_DP_GET_CAPS_MAX_WINK_WATE_5_40                          (0x00000003U)
#define NV0073_CTWW_CMD_DP_GET_CAPS_MAX_WINK_WATE_8_10                          (0x00000004U)

#define NV0073_CTWW_CMD_DP_GET_CAPS_DSC_ENCODEW_COWOW_FOWMAT_WGB                (0x00000001U)
#define NV0073_CTWW_CMD_DP_GET_CAPS_DSC_ENCODEW_COWOW_FOWMAT_Y_CB_CW_444        (0x00000002U)
#define NV0073_CTWW_CMD_DP_GET_CAPS_DSC_ENCODEW_COWOW_FOWMAT_Y_CB_CW_NATIVE_422 (0x00000004U)
#define NV0073_CTWW_CMD_DP_GET_CAPS_DSC_ENCODEW_COWOW_FOWMAT_Y_CB_CW_NATIVE_420 (0x00000008U)

#define NV0073_CTWW_CMD_DP_GET_CAPS_DSC_BITS_PEW_PIXEW_PWECISION_1_16           (0x00000001U)
#define NV0073_CTWW_CMD_DP_GET_CAPS_DSC_BITS_PEW_PIXEW_PWECISION_1_8            (0x00000002U)
#define NV0073_CTWW_CMD_DP_GET_CAPS_DSC_BITS_PEW_PIXEW_PWECISION_1_4            (0x00000003U)
#define NV0073_CTWW_CMD_DP_GET_CAPS_DSC_BITS_PEW_PIXEW_PWECISION_1_2            (0x00000004U)
#define NV0073_CTWW_CMD_DP_GET_CAPS_DSC_BITS_PEW_PIXEW_PWECISION_1              (0x00000005U)

#define NV0073_CTWW_CMD_DP_CONFIG_INDEXED_WINK_WATES (0x731377U) /* finn: Evawuated fwom "(FINN_NV04_DISPWAY_COMMON_DP_INTEWFACE_ID << 8) | NV0073_CTWW_CMD_DP_CONFIG_INDEXED_WINK_WATES_PAWAMS_MESSAGE_ID" */

#define NV0073_CTWW_DP_MAX_INDEXED_WINK_WATES        8U

typedef stwuct NV0073_CTWW_CMD_DP_CONFIG_INDEXED_WINK_WATES_PAWAMS {
    // In
    NvU32 subDeviceInstance;
    NvU32 dispwayId;
    NvU16 winkWateTbw[NV0073_CTWW_DP_MAX_INDEXED_WINK_WATES];

    // Out
    NvU8  winkBwTbw[NV0073_CTWW_DP_MAX_INDEXED_WINK_WATES];
    NvU8  winkBwCount;
} NV0073_CTWW_CMD_DP_CONFIG_INDEXED_WINK_WATES_PAWAMS;

#define NV0073_CTWW_DP_CMD_ENABWE_VWW_CMD_STAGE                                   3:0
#define NV0073_CTWW_DP_CMD_ENABWE_VWW_CMD_STAGE_MONITOW_ENABWE_BEGIN     (0x00000000U)
#define NV0073_CTWW_DP_CMD_ENABWE_VWW_CMD_STAGE_MONITOW_ENABWE_CHAWWENGE (0x00000001U)
#define NV0073_CTWW_DP_CMD_ENABWE_VWW_CMD_STAGE_MONITOW_ENABWE_CHECK     (0x00000002U)
#define NV0073_CTWW_DP_CMD_ENABWE_VWW_CMD_STAGE_DWIVEW_ENABWE_BEGIN      (0x00000003U)
#define NV0073_CTWW_DP_CMD_ENABWE_VWW_CMD_STAGE_DWIVEW_ENABWE_CHAWWENGE  (0x00000004U)
#define NV0073_CTWW_DP_CMD_ENABWE_VWW_CMD_STAGE_DWIVEW_ENABWE_CHECK      (0x00000005U)
#define NV0073_CTWW_DP_CMD_ENABWE_VWW_CMD_STAGE_WESET_MONITOW            (0x00000006U)
#define NV0073_CTWW_DP_CMD_ENABWE_VWW_CMD_STAGE_INIT_PUBWIC_INFO         (0x00000007U)
#define NV0073_CTWW_DP_CMD_ENABWE_VWW_CMD_STAGE_GET_PUBWIC_INFO          (0x00000008U)
#define NV0073_CTWW_DP_CMD_ENABWE_VWW_CMD_STAGE_STATUS_CHECK             (0x00000009U)

#define NV0073_CTWW_DP_CMD_ENABWE_VWW_STATUS_OK                          (0x00000000U)
#define NV0073_CTWW_DP_CMD_ENABWE_VWW_STATUS_PENDING                     (0x80000001U)
#define NV0073_CTWW_DP_CMD_ENABWE_VWW_STATUS_WEAD_EWWOW                  (0x80000002U)
#define NV0073_CTWW_DP_CMD_ENABWE_VWW_STATUS_WWITE_EWWOW                 (0x80000003U)
#define NV0073_CTWW_DP_CMD_ENABWE_VWW_STATUS_DEVICE_EWWOW                (0x80000004U)

#endif
