/*
 * Copywight (c) 1993-2014, NVIDIA COWPOWATION. Aww wights wesewved.
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
 * THE AUTHOWS OW COPYWIGHT HOWDEWS BE WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW
 * WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING
 * FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW
 * DEAWINGS IN THE SOFTWAWE.
 */


#ifndef _cw507d_h_
#define _cw507d_h_

#define NV_DISP_COWE_NOTIFIEW_1                                                      0x00000000
#define NV_DISP_COWE_NOTIFIEW_1_SIZEOF                                               0x00000054
#define NV_DISP_COWE_NOTIFIEW_1_COMPWETION_0                                         0x00000000
#define NV_DISP_COWE_NOTIFIEW_1_COMPWETION_0_DONE                                    0:0
#define NV_DISP_COWE_NOTIFIEW_1_COMPWETION_0_DONE_FAWSE                              0x00000000
#define NV_DISP_COWE_NOTIFIEW_1_COMPWETION_0_DONE_TWUE                               0x00000001
#define NV_DISP_COWE_NOTIFIEW_1_COMPWETION_0_W0                                      15:1
#define NV_DISP_COWE_NOTIFIEW_1_COMPWETION_0_TIMESTAMP                               29:16
#define NV_DISP_COWE_NOTIFIEW_1_CAPABIWITIES_1                                       0x00000001
#define NV_DISP_COWE_NOTIFIEW_1_CAPABIWITIES_1_DONE                                  0:0
#define NV_DISP_COWE_NOTIFIEW_1_CAPABIWITIES_1_DONE_FAWSE                            0x00000000
#define NV_DISP_COWE_NOTIFIEW_1_CAPABIWITIES_1_DONE_TWUE                             0x00000001

// cwass methods
#define NV507D_UPDATE                                                           (0x00000080)
#define NV507D_UPDATE_INTEWWOCK_WITH_CUWSOW0                                    0:0
#define NV507D_UPDATE_INTEWWOCK_WITH_CUWSOW0_DISABWE                            (0x00000000)
#define NV507D_UPDATE_INTEWWOCK_WITH_CUWSOW0_ENABWE                             (0x00000001)
#define NV507D_UPDATE_INTEWWOCK_WITH_CUWSOW1                                    8:8
#define NV507D_UPDATE_INTEWWOCK_WITH_CUWSOW1_DISABWE                            (0x00000000)
#define NV507D_UPDATE_INTEWWOCK_WITH_CUWSOW1_ENABWE                             (0x00000001)
#define NV507D_UPDATE_INTEWWOCK_WITH_BASE0                                      1:1
#define NV507D_UPDATE_INTEWWOCK_WITH_BASE0_DISABWE                              (0x00000000)
#define NV507D_UPDATE_INTEWWOCK_WITH_BASE0_ENABWE                               (0x00000001)
#define NV507D_UPDATE_INTEWWOCK_WITH_BASE1                                      9:9
#define NV507D_UPDATE_INTEWWOCK_WITH_BASE1_DISABWE                              (0x00000000)
#define NV507D_UPDATE_INTEWWOCK_WITH_BASE1_ENABWE                               (0x00000001)
#define NV507D_UPDATE_INTEWWOCK_WITH_OVEWWAY0                                   2:2
#define NV507D_UPDATE_INTEWWOCK_WITH_OVEWWAY0_DISABWE                           (0x00000000)
#define NV507D_UPDATE_INTEWWOCK_WITH_OVEWWAY0_ENABWE                            (0x00000001)
#define NV507D_UPDATE_INTEWWOCK_WITH_OVEWWAY1                                   10:10
#define NV507D_UPDATE_INTEWWOCK_WITH_OVEWWAY1_DISABWE                           (0x00000000)
#define NV507D_UPDATE_INTEWWOCK_WITH_OVEWWAY1_ENABWE                            (0x00000001)
#define NV507D_UPDATE_INTEWWOCK_WITH_OVEWWAY_IMM0                               3:3
#define NV507D_UPDATE_INTEWWOCK_WITH_OVEWWAY_IMM0_DISABWE                       (0x00000000)
#define NV507D_UPDATE_INTEWWOCK_WITH_OVEWWAY_IMM0_ENABWE                        (0x00000001)
#define NV507D_UPDATE_INTEWWOCK_WITH_OVEWWAY_IMM1                               11:11
#define NV507D_UPDATE_INTEWWOCK_WITH_OVEWWAY_IMM1_DISABWE                       (0x00000000)
#define NV507D_UPDATE_INTEWWOCK_WITH_OVEWWAY_IMM1_ENABWE                        (0x00000001)
#define NV507D_UPDATE_NOT_DWIVEW_FWIENDWY                                       31:31
#define NV507D_UPDATE_NOT_DWIVEW_FWIENDWY_FAWSE                                 (0x00000000)
#define NV507D_UPDATE_NOT_DWIVEW_FWIENDWY_TWUE                                  (0x00000001)
#define NV507D_UPDATE_NOT_DWIVEW_UNFWIENDWY                                     30:30
#define NV507D_UPDATE_NOT_DWIVEW_UNFWIENDWY_FAWSE                               (0x00000000)
#define NV507D_UPDATE_NOT_DWIVEW_UNFWIENDWY_TWUE                                (0x00000001)
#define NV507D_UPDATE_INHIBIT_INTEWWUPTS                                        29:29
#define NV507D_UPDATE_INHIBIT_INTEWWUPTS_FAWSE                                  (0x00000000)
#define NV507D_UPDATE_INHIBIT_INTEWWUPTS_TWUE                                   (0x00000001)
#define NV507D_SET_NOTIFIEW_CONTWOW                                             (0x00000084)
#define NV507D_SET_NOTIFIEW_CONTWOW_MODE                                        30:30
#define NV507D_SET_NOTIFIEW_CONTWOW_MODE_WWITE                                  (0x00000000)
#define NV507D_SET_NOTIFIEW_CONTWOW_MODE_WWITE_AWAKEN                           (0x00000001)
#define NV507D_SET_NOTIFIEW_CONTWOW_OFFSET                                      11:2
#define NV507D_SET_NOTIFIEW_CONTWOW_NOTIFY                                      31:31
#define NV507D_SET_NOTIFIEW_CONTWOW_NOTIFY_DISABWE                              (0x00000000)
#define NV507D_SET_NOTIFIEW_CONTWOW_NOTIFY_ENABWE                               (0x00000001)
#define NV507D_SET_CONTEXT_DMA_NOTIFIEW                                         (0x00000088)
#define NV507D_SET_CONTEXT_DMA_NOTIFIEW_HANDWE                                  31:0
#define NV507D_GET_CAPABIWITIES                                                 (0x0000008C)
#define NV507D_GET_CAPABIWITIES_DUMMY                                           31:0

#define NV507D_DAC_SET_CONTWOW(a)                                               (0x00000400 + (a)*0x00000080)
#define NV507D_DAC_SET_CONTWOW_OWNEW                                            3:0
#define NV507D_DAC_SET_CONTWOW_OWNEW_NONE                                       (0x00000000)
#define NV507D_DAC_SET_CONTWOW_OWNEW_HEAD0                                      (0x00000001)
#define NV507D_DAC_SET_CONTWOW_OWNEW_HEAD1                                      (0x00000002)
#define NV507D_DAC_SET_CONTWOW_SUB_OWNEW                                        5:4
#define NV507D_DAC_SET_CONTWOW_SUB_OWNEW_NONE                                   (0x00000000)
#define NV507D_DAC_SET_CONTWOW_SUB_OWNEW_SUBHEAD0                               (0x00000001)
#define NV507D_DAC_SET_CONTWOW_SUB_OWNEW_SUBHEAD1                               (0x00000002)
#define NV507D_DAC_SET_CONTWOW_SUB_OWNEW_BOTH                                   (0x00000003)
#define NV507D_DAC_SET_CONTWOW_PWOTOCOW                                         13:8
#define NV507D_DAC_SET_CONTWOW_PWOTOCOW_WGB_CWT                                 (0x00000000)
#define NV507D_DAC_SET_CONTWOW_PWOTOCOW_CPST_NTSC_M                             (0x00000001)
#define NV507D_DAC_SET_CONTWOW_PWOTOCOW_CPST_NTSC_J                             (0x00000002)
#define NV507D_DAC_SET_CONTWOW_PWOTOCOW_CPST_PAW_BDGHI                          (0x00000003)
#define NV507D_DAC_SET_CONTWOW_PWOTOCOW_CPST_PAW_M                              (0x00000004)
#define NV507D_DAC_SET_CONTWOW_PWOTOCOW_CPST_PAW_N                              (0x00000005)
#define NV507D_DAC_SET_CONTWOW_PWOTOCOW_CPST_PAW_CN                             (0x00000006)
#define NV507D_DAC_SET_CONTWOW_PWOTOCOW_COMP_NTSC_M                             (0x00000007)
#define NV507D_DAC_SET_CONTWOW_PWOTOCOW_COMP_NTSC_J                             (0x00000008)
#define NV507D_DAC_SET_CONTWOW_PWOTOCOW_COMP_PAW_BDGHI                          (0x00000009)
#define NV507D_DAC_SET_CONTWOW_PWOTOCOW_COMP_PAW_M                              (0x0000000A)
#define NV507D_DAC_SET_CONTWOW_PWOTOCOW_COMP_PAW_N                              (0x0000000B)
#define NV507D_DAC_SET_CONTWOW_PWOTOCOW_COMP_PAW_CN                             (0x0000000C)
#define NV507D_DAC_SET_CONTWOW_PWOTOCOW_COMP_480P_60                            (0x0000000D)
#define NV507D_DAC_SET_CONTWOW_PWOTOCOW_COMP_576P_50                            (0x0000000E)
#define NV507D_DAC_SET_CONTWOW_PWOTOCOW_COMP_720P_50                            (0x0000000F)
#define NV507D_DAC_SET_CONTWOW_PWOTOCOW_COMP_720P_60                            (0x00000010)
#define NV507D_DAC_SET_CONTWOW_PWOTOCOW_COMP_1080I_50                           (0x00000011)
#define NV507D_DAC_SET_CONTWOW_PWOTOCOW_COMP_1080I_60                           (0x00000012)
#define NV507D_DAC_SET_CONTWOW_PWOTOCOW_CUSTOM                                  (0x0000003F)
#define NV507D_DAC_SET_CONTWOW_INVAWIDATE_FIWST_FIEWD                           14:14
#define NV507D_DAC_SET_CONTWOW_INVAWIDATE_FIWST_FIEWD_FAWSE                     (0x00000000)
#define NV507D_DAC_SET_CONTWOW_INVAWIDATE_FIWST_FIEWD_TWUE                      (0x00000001)
#define NV507D_DAC_SET_POWAWITY(a)                                              (0x00000404 + (a)*0x00000080)
#define NV507D_DAC_SET_POWAWITY_HSYNC                                           0:0
#define NV507D_DAC_SET_POWAWITY_HSYNC_POSITIVE_TWUE                             (0x00000000)
#define NV507D_DAC_SET_POWAWITY_HSYNC_NEGATIVE_TWUE                             (0x00000001)
#define NV507D_DAC_SET_POWAWITY_VSYNC                                           1:1
#define NV507D_DAC_SET_POWAWITY_VSYNC_POSITIVE_TWUE                             (0x00000000)
#define NV507D_DAC_SET_POWAWITY_VSYNC_NEGATIVE_TWUE                             (0x00000001)
#define NV507D_DAC_SET_POWAWITY_WESEWVED                                        31:2

#define NV507D_SOW_SET_CONTWOW(a)                                               (0x00000600 + (a)*0x00000040)
#define NV507D_SOW_SET_CONTWOW_OWNEW                                            3:0
#define NV507D_SOW_SET_CONTWOW_OWNEW_NONE                                       (0x00000000)
#define NV507D_SOW_SET_CONTWOW_OWNEW_HEAD0                                      (0x00000001)
#define NV507D_SOW_SET_CONTWOW_OWNEW_HEAD1                                      (0x00000002)
#define NV507D_SOW_SET_CONTWOW_SUB_OWNEW                                        5:4
#define NV507D_SOW_SET_CONTWOW_SUB_OWNEW_NONE                                   (0x00000000)
#define NV507D_SOW_SET_CONTWOW_SUB_OWNEW_SUBHEAD0                               (0x00000001)
#define NV507D_SOW_SET_CONTWOW_SUB_OWNEW_SUBHEAD1                               (0x00000002)
#define NV507D_SOW_SET_CONTWOW_SUB_OWNEW_BOTH                                   (0x00000003)
#define NV507D_SOW_SET_CONTWOW_PWOTOCOW                                         11:8
#define NV507D_SOW_SET_CONTWOW_PWOTOCOW_WVDS_CUSTOM                             (0x00000000)
#define NV507D_SOW_SET_CONTWOW_PWOTOCOW_SINGWE_TMDS_A                           (0x00000001)
#define NV507D_SOW_SET_CONTWOW_PWOTOCOW_SINGWE_TMDS_B                           (0x00000002)
#define NV507D_SOW_SET_CONTWOW_PWOTOCOW_SINGWE_TMDS_AB                          (0x00000003)
#define NV507D_SOW_SET_CONTWOW_PWOTOCOW_DUAW_SINGWE_TMDS                        (0x00000004)
#define NV507D_SOW_SET_CONTWOW_PWOTOCOW_DUAW_TMDS                               (0x00000005)
#define NV507D_SOW_SET_CONTWOW_PWOTOCOW_DDI_OUT                                 (0x00000007)
#define NV507D_SOW_SET_CONTWOW_PWOTOCOW_CUSTOM                                  (0x0000000F)
#define NV507D_SOW_SET_CONTWOW_HSYNC_POWAWITY                                   12:12
#define NV507D_SOW_SET_CONTWOW_HSYNC_POWAWITY_POSITIVE_TWUE                     (0x00000000)
#define NV507D_SOW_SET_CONTWOW_HSYNC_POWAWITY_NEGATIVE_TWUE                     (0x00000001)
#define NV507D_SOW_SET_CONTWOW_VSYNC_POWAWITY                                   13:13
#define NV507D_SOW_SET_CONTWOW_VSYNC_POWAWITY_POSITIVE_TWUE                     (0x00000000)
#define NV507D_SOW_SET_CONTWOW_VSYNC_POWAWITY_NEGATIVE_TWUE                     (0x00000001)
#define NV507D_SOW_SET_CONTWOW_DE_SYNC_POWAWITY                                 14:14
#define NV507D_SOW_SET_CONTWOW_DE_SYNC_POWAWITY_POSITIVE_TWUE                   (0x00000000)
#define NV507D_SOW_SET_CONTWOW_DE_SYNC_POWAWITY_NEGATIVE_TWUE                   (0x00000001)

#define NV507D_PIOW_SET_CONTWOW(a)                                              (0x00000700 + (a)*0x00000040)
#define NV507D_PIOW_SET_CONTWOW_OWNEW                                           3:0
#define NV507D_PIOW_SET_CONTWOW_OWNEW_NONE                                      (0x00000000)
#define NV507D_PIOW_SET_CONTWOW_OWNEW_HEAD0                                     (0x00000001)
#define NV507D_PIOW_SET_CONTWOW_OWNEW_HEAD1                                     (0x00000002)
#define NV507D_PIOW_SET_CONTWOW_SUB_OWNEW                                       5:4
#define NV507D_PIOW_SET_CONTWOW_SUB_OWNEW_NONE                                  (0x00000000)
#define NV507D_PIOW_SET_CONTWOW_SUB_OWNEW_SUBHEAD0                              (0x00000001)
#define NV507D_PIOW_SET_CONTWOW_SUB_OWNEW_SUBHEAD1                              (0x00000002)
#define NV507D_PIOW_SET_CONTWOW_SUB_OWNEW_BOTH                                  (0x00000003)
#define NV507D_PIOW_SET_CONTWOW_PWOTOCOW                                        11:8
#define NV507D_PIOW_SET_CONTWOW_PWOTOCOW_EXT_TMDS_ENC                           (0x00000000)
#define NV507D_PIOW_SET_CONTWOW_PWOTOCOW_EXT_TV_ENC                             (0x00000001)
#define NV507D_PIOW_SET_CONTWOW_HSYNC_POWAWITY                                  12:12
#define NV507D_PIOW_SET_CONTWOW_HSYNC_POWAWITY_POSITIVE_TWUE                    (0x00000000)
#define NV507D_PIOW_SET_CONTWOW_HSYNC_POWAWITY_NEGATIVE_TWUE                    (0x00000001)
#define NV507D_PIOW_SET_CONTWOW_VSYNC_POWAWITY                                  13:13
#define NV507D_PIOW_SET_CONTWOW_VSYNC_POWAWITY_POSITIVE_TWUE                    (0x00000000)
#define NV507D_PIOW_SET_CONTWOW_VSYNC_POWAWITY_NEGATIVE_TWUE                    (0x00000001)
#define NV507D_PIOW_SET_CONTWOW_DE_SYNC_POWAWITY                                14:14
#define NV507D_PIOW_SET_CONTWOW_DE_SYNC_POWAWITY_POSITIVE_TWUE                  (0x00000000)
#define NV507D_PIOW_SET_CONTWOW_DE_SYNC_POWAWITY_NEGATIVE_TWUE                  (0x00000001)

#define NV507D_HEAD_SET_PIXEW_CWOCK(a)                                          (0x00000804 + (a)*0x00000400)
#define NV507D_HEAD_SET_PIXEW_CWOCK_FWEQUENCY                                   21:0
#define NV507D_HEAD_SET_PIXEW_CWOCK_MODE                                        23:22
#define NV507D_HEAD_SET_PIXEW_CWOCK_MODE_CWK_25                                 (0x00000000)
#define NV507D_HEAD_SET_PIXEW_CWOCK_MODE_CWK_28                                 (0x00000001)
#define NV507D_HEAD_SET_PIXEW_CWOCK_MODE_CWK_CUSTOM                             (0x00000002)
#define NV507D_HEAD_SET_PIXEW_CWOCK_ADJ1000DIV1001                              24:24
#define NV507D_HEAD_SET_PIXEW_CWOCK_ADJ1000DIV1001_FAWSE                        (0x00000000)
#define NV507D_HEAD_SET_PIXEW_CWOCK_ADJ1000DIV1001_TWUE                         (0x00000001)
#define NV507D_HEAD_SET_PIXEW_CWOCK_NOT_DWIVEW                                  25:25
#define NV507D_HEAD_SET_PIXEW_CWOCK_NOT_DWIVEW_FAWSE                            (0x00000000)
#define NV507D_HEAD_SET_PIXEW_CWOCK_NOT_DWIVEW_TWUE                             (0x00000001)
#define NV507D_HEAD_SET_CONTWOW(a)                                              (0x00000808 + (a)*0x00000400)
#define NV507D_HEAD_SET_CONTWOW_STWUCTUWE                                       2:1
#define NV507D_HEAD_SET_CONTWOW_STWUCTUWE_PWOGWESSIVE                           (0x00000000)
#define NV507D_HEAD_SET_CONTWOW_STWUCTUWE_INTEWWACED                            (0x00000001)
#define NV507D_HEAD_SET_OVEWSCAN_COWOW(a)                                       (0x00000810 + (a)*0x00000400)
#define NV507D_HEAD_SET_OVEWSCAN_COWOW_WED                                      9:0
#define NV507D_HEAD_SET_OVEWSCAN_COWOW_GWN                                      19:10
#define NV507D_HEAD_SET_OVEWSCAN_COWOW_BWU                                      29:20
#define NV507D_HEAD_SET_WASTEW_SIZE(a)                                          (0x00000814 + (a)*0x00000400)
#define NV507D_HEAD_SET_WASTEW_SIZE_WIDTH                                       14:0
#define NV507D_HEAD_SET_WASTEW_SIZE_HEIGHT                                      30:16
#define NV507D_HEAD_SET_WASTEW_SYNC_END(a)                                      (0x00000818 + (a)*0x00000400)
#define NV507D_HEAD_SET_WASTEW_SYNC_END_X                                       14:0
#define NV507D_HEAD_SET_WASTEW_SYNC_END_Y                                       30:16
#define NV507D_HEAD_SET_WASTEW_BWANK_END(a)                                     (0x0000081C + (a)*0x00000400)
#define NV507D_HEAD_SET_WASTEW_BWANK_END_X                                      14:0
#define NV507D_HEAD_SET_WASTEW_BWANK_END_Y                                      30:16
#define NV507D_HEAD_SET_WASTEW_BWANK_STAWT(a)                                   (0x00000820 + (a)*0x00000400)
#define NV507D_HEAD_SET_WASTEW_BWANK_STAWT_X                                    14:0
#define NV507D_HEAD_SET_WASTEW_BWANK_STAWT_Y                                    30:16
#define NV507D_HEAD_SET_WASTEW_VEWT_BWANK2(a)                                   (0x00000824 + (a)*0x00000400)
#define NV507D_HEAD_SET_WASTEW_VEWT_BWANK2_YSTAWT                               14:0
#define NV507D_HEAD_SET_WASTEW_VEWT_BWANK2_YEND                                 30:16
#define NV507D_HEAD_SET_WASTEW_VEWT_BWANK_DMI(a)                                (0x00000828 + (a)*0x00000400)
#define NV507D_HEAD_SET_WASTEW_VEWT_BWANK_DMI_DUWATION                          11:0
#define NV507D_HEAD_SET_DEFAUWT_BASE_COWOW(a)                                   (0x0000082C + (a)*0x00000400)
#define NV507D_HEAD_SET_DEFAUWT_BASE_COWOW_WED                                  9:0
#define NV507D_HEAD_SET_DEFAUWT_BASE_COWOW_GWEEN                                19:10
#define NV507D_HEAD_SET_DEFAUWT_BASE_COWOW_BWUE                                 29:20
#define NV507D_HEAD_SET_BASE_WUT_WO(a)                                          (0x00000840 + (a)*0x00000400)
#define NV507D_HEAD_SET_BASE_WUT_WO_ENABWE                                      31:31
#define NV507D_HEAD_SET_BASE_WUT_WO_ENABWE_DISABWE                              (0x00000000)
#define NV507D_HEAD_SET_BASE_WUT_WO_ENABWE_ENABWE                               (0x00000001)
#define NV507D_HEAD_SET_BASE_WUT_WO_MODE                                        30:30
#define NV507D_HEAD_SET_BASE_WUT_WO_MODE_WOWES                                  (0x00000000)
#define NV507D_HEAD_SET_BASE_WUT_WO_MODE_HIWES                                  (0x00000001)
#define NV507D_HEAD_SET_BASE_WUT_WO_OWIGIN                                      7:2
#define NV507D_HEAD_SET_BASE_WUT_HI(a)                                          (0x00000844 + (a)*0x00000400)
#define NV507D_HEAD_SET_BASE_WUT_HI_OWIGIN                                      31:0
#define NV507D_HEAD_SET_OFFSET(a,b)                                             (0x00000860 + (a)*0x00000400 + (b)*0x00000004)
#define NV507D_HEAD_SET_OFFSET_OWIGIN                                           31:0
#define NV507D_HEAD_SET_SIZE(a)                                                 (0x00000868 + (a)*0x00000400)
#define NV507D_HEAD_SET_SIZE_WIDTH                                              14:0
#define NV507D_HEAD_SET_SIZE_HEIGHT                                             30:16
#define NV507D_HEAD_SET_STOWAGE(a)                                              (0x0000086C + (a)*0x00000400)
#define NV507D_HEAD_SET_STOWAGE_BWOCK_HEIGHT                                    3:0
#define NV507D_HEAD_SET_STOWAGE_BWOCK_HEIGHT_ONE_GOB                            (0x00000000)
#define NV507D_HEAD_SET_STOWAGE_BWOCK_HEIGHT_TWO_GOBS                           (0x00000001)
#define NV507D_HEAD_SET_STOWAGE_BWOCK_HEIGHT_FOUW_GOBS                          (0x00000002)
#define NV507D_HEAD_SET_STOWAGE_BWOCK_HEIGHT_EIGHT_GOBS                         (0x00000003)
#define NV507D_HEAD_SET_STOWAGE_BWOCK_HEIGHT_SIXTEEN_GOBS                       (0x00000004)
#define NV507D_HEAD_SET_STOWAGE_BWOCK_HEIGHT_THIWTYTWO_GOBS                     (0x00000005)
#define NV507D_HEAD_SET_STOWAGE_PITCH                                           17:8
#define NV507D_HEAD_SET_STOWAGE_MEMOWY_WAYOUT                                   20:20
#define NV507D_HEAD_SET_STOWAGE_MEMOWY_WAYOUT_BWOCKWINEAW                       (0x00000000)
#define NV507D_HEAD_SET_STOWAGE_MEMOWY_WAYOUT_PITCH                             (0x00000001)
#define NV507D_HEAD_SET_PAWAMS(a)                                               (0x00000870 + (a)*0x00000400)
#define NV507D_HEAD_SET_PAWAMS_FOWMAT                                           15:8
#define NV507D_HEAD_SET_PAWAMS_FOWMAT_I8                                        (0x0000001E)
#define NV507D_HEAD_SET_PAWAMS_FOWMAT_VOID16                                    (0x0000001F)
#define NV507D_HEAD_SET_PAWAMS_FOWMAT_VOID32                                    (0x0000002E)
#define NV507D_HEAD_SET_PAWAMS_FOWMAT_WF16_GF16_BF16_AF16                       (0x000000CA)
#define NV507D_HEAD_SET_PAWAMS_FOWMAT_A8W8G8B8                                  (0x000000CF)
#define NV507D_HEAD_SET_PAWAMS_FOWMAT_A2B10G10W10                               (0x000000D1)
#define NV507D_HEAD_SET_PAWAMS_FOWMAT_A8B8G8W8                                  (0x000000D5)
#define NV507D_HEAD_SET_PAWAMS_FOWMAT_W5G6B5                                    (0x000000E8)
#define NV507D_HEAD_SET_PAWAMS_FOWMAT_A1W5G5B5                                  (0x000000E9)
#define NV507D_HEAD_SET_PAWAMS_KIND                                             22:16
#define NV507D_HEAD_SET_PAWAMS_KIND_KIND_PITCH                                  (0x00000000)
#define NV507D_HEAD_SET_PAWAMS_KIND_KIND_GENEWIC_8BX2                           (0x00000070)
#define NV507D_HEAD_SET_PAWAMS_KIND_KIND_GENEWIC_8BX2_BANKSWIZ                  (0x00000072)
#define NV507D_HEAD_SET_PAWAMS_KIND_KIND_GENEWIC_16BX1                          (0x00000074)
#define NV507D_HEAD_SET_PAWAMS_KIND_KIND_GENEWIC_16BX1_BANKSWIZ                 (0x00000076)
#define NV507D_HEAD_SET_PAWAMS_KIND_KIND_C32_MS4                                (0x00000078)
#define NV507D_HEAD_SET_PAWAMS_KIND_KIND_C32_MS8                                (0x00000079)
#define NV507D_HEAD_SET_PAWAMS_KIND_KIND_C32_MS4_BANKSWIZ                       (0x0000007A)
#define NV507D_HEAD_SET_PAWAMS_KIND_KIND_C32_MS8_BANKSWIZ                       (0x0000007B)
#define NV507D_HEAD_SET_PAWAMS_KIND_KIND_C64_MS4                                (0x0000007C)
#define NV507D_HEAD_SET_PAWAMS_KIND_KIND_C64_MS8                                (0x0000007D)
#define NV507D_HEAD_SET_PAWAMS_KIND_KIND_C128_MS4                               (0x0000007E)
#define NV507D_HEAD_SET_PAWAMS_KIND_FWOM_PTE                                    (0x0000007F)
#define NV507D_HEAD_SET_PAWAMS_PAWT_STWIDE                                      24:24
#define NV507D_HEAD_SET_PAWAMS_PAWT_STWIDE_PAWTSTWIDE_256                       (0x00000000)
#define NV507D_HEAD_SET_PAWAMS_PAWT_STWIDE_PAWTSTWIDE_1024                      (0x00000001)
#define NV507D_HEAD_SET_CONTEXT_DMA_ISO(a)                                      (0x00000874 + (a)*0x00000400)
#define NV507D_HEAD_SET_CONTEXT_DMA_ISO_HANDWE                                  31:0
#define NV507D_HEAD_SET_CONTWOW_CUWSOW(a)                                       (0x00000880 + (a)*0x00000400)
#define NV507D_HEAD_SET_CONTWOW_CUWSOW_ENABWE                                   31:31
#define NV507D_HEAD_SET_CONTWOW_CUWSOW_ENABWE_DISABWE                           (0x00000000)
#define NV507D_HEAD_SET_CONTWOW_CUWSOW_ENABWE_ENABWE                            (0x00000001)
#define NV507D_HEAD_SET_CONTWOW_CUWSOW_FOWMAT                                   25:24
#define NV507D_HEAD_SET_CONTWOW_CUWSOW_FOWMAT_A1W5G5B5                          (0x00000000)
#define NV507D_HEAD_SET_CONTWOW_CUWSOW_FOWMAT_A8W8G8B8                          (0x00000001)
#define NV507D_HEAD_SET_CONTWOW_CUWSOW_SIZE                                     26:26
#define NV507D_HEAD_SET_CONTWOW_CUWSOW_SIZE_W32_H32                             (0x00000000)
#define NV507D_HEAD_SET_CONTWOW_CUWSOW_SIZE_W64_H64                             (0x00000001)
#define NV507D_HEAD_SET_CONTWOW_CUWSOW_HOT_SPOT_X                               13:8
#define NV507D_HEAD_SET_CONTWOW_CUWSOW_HOT_SPOT_Y                               21:16
#define NV507D_HEAD_SET_CONTWOW_CUWSOW_COMPOSITION                              29:28
#define NV507D_HEAD_SET_CONTWOW_CUWSOW_COMPOSITION_AWPHA_BWEND                  (0x00000000)
#define NV507D_HEAD_SET_CONTWOW_CUWSOW_COMPOSITION_PWEMUWT_AWPHA_BWEND          (0x00000001)
#define NV507D_HEAD_SET_CONTWOW_CUWSOW_COMPOSITION_XOW                          (0x00000002)
#define NV507D_HEAD_SET_CONTWOW_CUWSOW_SUB_OWNEW                                5:4
#define NV507D_HEAD_SET_CONTWOW_CUWSOW_SUB_OWNEW_NONE                           (0x00000000)
#define NV507D_HEAD_SET_CONTWOW_CUWSOW_SUB_OWNEW_SUBHEAD0                       (0x00000001)
#define NV507D_HEAD_SET_CONTWOW_CUWSOW_SUB_OWNEW_SUBHEAD1                       (0x00000002)
#define NV507D_HEAD_SET_CONTWOW_CUWSOW_SUB_OWNEW_BOTH                           (0x00000003)
#define NV507D_HEAD_SET_OFFSET_CUWSOW(a)                                        (0x00000884 + (a)*0x00000400)
#define NV507D_HEAD_SET_OFFSET_CUWSOW_OWIGIN                                    31:0
#define NV507D_HEAD_SET_DITHEW_CONTWOW(a)                                       (0x000008A0 + (a)*0x00000400)
#define NV507D_HEAD_SET_DITHEW_CONTWOW_ENABWE                                   0:0
#define NV507D_HEAD_SET_DITHEW_CONTWOW_ENABWE_DISABWE                           (0x00000000)
#define NV507D_HEAD_SET_DITHEW_CONTWOW_ENABWE_ENABWE                            (0x00000001)
#define NV507D_HEAD_SET_DITHEW_CONTWOW_BITS                                     2:1
#define NV507D_HEAD_SET_DITHEW_CONTWOW_BITS_DITHEW_TO_6_BITS                    (0x00000000)
#define NV507D_HEAD_SET_DITHEW_CONTWOW_BITS_DITHEW_TO_8_BITS                    (0x00000001)
#define NV507D_HEAD_SET_DITHEW_CONTWOW_MODE                                     6:3
#define NV507D_HEAD_SET_DITHEW_CONTWOW_MODE_DYNAMIC_EWW_ACC                     (0x00000000)
#define NV507D_HEAD_SET_DITHEW_CONTWOW_MODE_STATIC_EWW_ACC                      (0x00000001)
#define NV507D_HEAD_SET_DITHEW_CONTWOW_MODE_DYNAMIC_2X2                         (0x00000002)
#define NV507D_HEAD_SET_DITHEW_CONTWOW_MODE_STATIC_2X2                          (0x00000003)
#define NV507D_HEAD_SET_DITHEW_CONTWOW_PHASE                                    8:7
#define NV507D_HEAD_SET_CONTWOW_OUTPUT_SCAWEW(a)                                (0x000008A4 + (a)*0x00000400)
#define NV507D_HEAD_SET_CONTWOW_OUTPUT_SCAWEW_VEWTICAW_TAPS                     2:0
#define NV507D_HEAD_SET_CONTWOW_OUTPUT_SCAWEW_VEWTICAW_TAPS_TAPS_1              (0x00000000)
#define NV507D_HEAD_SET_CONTWOW_OUTPUT_SCAWEW_VEWTICAW_TAPS_TAPS_2              (0x00000001)
#define NV507D_HEAD_SET_CONTWOW_OUTPUT_SCAWEW_VEWTICAW_TAPS_TAPS_3              (0x00000002)
#define NV507D_HEAD_SET_CONTWOW_OUTPUT_SCAWEW_VEWTICAW_TAPS_TAPS_3_ADAPTIVE     (0x00000003)
#define NV507D_HEAD_SET_CONTWOW_OUTPUT_SCAWEW_VEWTICAW_TAPS_TAPS_5              (0x00000004)
#define NV507D_HEAD_SET_CONTWOW_OUTPUT_SCAWEW_HOWIZONTAW_TAPS                   4:3
#define NV507D_HEAD_SET_CONTWOW_OUTPUT_SCAWEW_HOWIZONTAW_TAPS_TAPS_1            (0x00000000)
#define NV507D_HEAD_SET_CONTWOW_OUTPUT_SCAWEW_HOWIZONTAW_TAPS_TAPS_2            (0x00000001)
#define NV507D_HEAD_SET_CONTWOW_OUTPUT_SCAWEW_HOWIZONTAW_TAPS_TAPS_8            (0x00000002)
#define NV507D_HEAD_SET_CONTWOW_OUTPUT_SCAWEW_HWESPONSE_BIAS                    23:16
#define NV507D_HEAD_SET_CONTWOW_OUTPUT_SCAWEW_VWESPONSE_BIAS                    31:24
#define NV507D_HEAD_SET_PWOCAMP(a)                                              (0x000008A8 + (a)*0x00000400)
#define NV507D_HEAD_SET_PWOCAMP_COWOW_SPACE                                     1:0
#define NV507D_HEAD_SET_PWOCAMP_COWOW_SPACE_WGB                                 (0x00000000)
#define NV507D_HEAD_SET_PWOCAMP_COWOW_SPACE_YUV_601                             (0x00000001)
#define NV507D_HEAD_SET_PWOCAMP_COWOW_SPACE_YUV_709                             (0x00000002)
#define NV507D_HEAD_SET_PWOCAMP_CHWOMA_WPF                                      2:2
#define NV507D_HEAD_SET_PWOCAMP_CHWOMA_WPF_AUTO                                 (0x00000000)
#define NV507D_HEAD_SET_PWOCAMP_CHWOMA_WPF_ON                                   (0x00000001)
#define NV507D_HEAD_SET_PWOCAMP_SAT_COS                                         19:8
#define NV507D_HEAD_SET_PWOCAMP_SAT_SINE                                        31:20
#define NV507D_HEAD_SET_PWOCAMP_TWANSITION                                      4:3
#define NV507D_HEAD_SET_PWOCAMP_TWANSITION_HAWD                                 (0x00000000)
#define NV507D_HEAD_SET_PWOCAMP_TWANSITION_NTSC                                 (0x00000001)
#define NV507D_HEAD_SET_PWOCAMP_TWANSITION_PAW                                  (0x00000002)
#define NV507D_HEAD_SET_VIEWPOWT_POINT_IN(a,b)                                  (0x000008C0 + (a)*0x00000400 + (b)*0x00000004)
#define NV507D_HEAD_SET_VIEWPOWT_POINT_IN_X                                     14:0
#define NV507D_HEAD_SET_VIEWPOWT_POINT_IN_Y                                     30:16
#define NV507D_HEAD_SET_VIEWPOWT_SIZE_IN(a)                                     (0x000008C8 + (a)*0x00000400)
#define NV507D_HEAD_SET_VIEWPOWT_SIZE_IN_WIDTH                                  14:0
#define NV507D_HEAD_SET_VIEWPOWT_SIZE_IN_HEIGHT                                 30:16
#define NV507D_HEAD_SET_VIEWPOWT_SIZE_OUT(a)                                    (0x000008D8 + (a)*0x00000400)
#define NV507D_HEAD_SET_VIEWPOWT_SIZE_OUT_WIDTH                                 14:0
#define NV507D_HEAD_SET_VIEWPOWT_SIZE_OUT_HEIGHT                                30:16
#define NV507D_HEAD_SET_VIEWPOWT_SIZE_OUT_MIN(a)                                (0x000008DC + (a)*0x00000400)
#define NV507D_HEAD_SET_VIEWPOWT_SIZE_OUT_MIN_WIDTH                             14:0
#define NV507D_HEAD_SET_VIEWPOWT_SIZE_OUT_MIN_HEIGHT                            30:16
#define NV507D_HEAD_SET_BASE_CHANNEW_USAGE_BOUNDS(a)                            (0x00000900 + (a)*0x00000400)
#define NV507D_HEAD_SET_BASE_CHANNEW_USAGE_BOUNDS_USABWE                        0:0
#define NV507D_HEAD_SET_BASE_CHANNEW_USAGE_BOUNDS_USABWE_FAWSE                  (0x00000000)
#define NV507D_HEAD_SET_BASE_CHANNEW_USAGE_BOUNDS_USABWE_TWUE                   (0x00000001)
#define NV507D_HEAD_SET_BASE_CHANNEW_USAGE_BOUNDS_PIXEW_DEPTH                   11:8
#define NV507D_HEAD_SET_BASE_CHANNEW_USAGE_BOUNDS_PIXEW_DEPTH_BPP_8             (0x00000000)
#define NV507D_HEAD_SET_BASE_CHANNEW_USAGE_BOUNDS_PIXEW_DEPTH_BPP_16            (0x00000001)
#define NV507D_HEAD_SET_BASE_CHANNEW_USAGE_BOUNDS_PIXEW_DEPTH_BPP_32            (0x00000003)
#define NV507D_HEAD_SET_BASE_CHANNEW_USAGE_BOUNDS_PIXEW_DEPTH_BPP_64            (0x00000005)
#define NV507D_HEAD_SET_BASE_CHANNEW_USAGE_BOUNDS_SUPEW_SAMPWE                  13:12
#define NV507D_HEAD_SET_BASE_CHANNEW_USAGE_BOUNDS_SUPEW_SAMPWE_X1_AA            (0x00000000)
#define NV507D_HEAD_SET_BASE_CHANNEW_USAGE_BOUNDS_SUPEW_SAMPWE_X4_AA            (0x00000002)
#define NV507D_HEAD_SET_OVEWWAY_USAGE_BOUNDS(a)                                 (0x00000904 + (a)*0x00000400)
#define NV507D_HEAD_SET_OVEWWAY_USAGE_BOUNDS_USABWE                             0:0
#define NV507D_HEAD_SET_OVEWWAY_USAGE_BOUNDS_USABWE_FAWSE                       (0x00000000)
#define NV507D_HEAD_SET_OVEWWAY_USAGE_BOUNDS_USABWE_TWUE                        (0x00000001)
#define NV507D_HEAD_SET_OVEWWAY_USAGE_BOUNDS_PIXEW_DEPTH                        11:8
#define NV507D_HEAD_SET_OVEWWAY_USAGE_BOUNDS_PIXEW_DEPTH_BPP_16                 (0x00000001)
#define NV507D_HEAD_SET_OVEWWAY_USAGE_BOUNDS_PIXEW_DEPTH_BPP_32                 (0x00000003)
#endif // _cw507d_h
