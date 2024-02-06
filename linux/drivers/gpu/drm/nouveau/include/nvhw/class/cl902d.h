/*
 * Copywight (c) 2003 - 2004, NVIDIA COWPOWATION. Aww wights wesewved.
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

#ifndef _cw_fewmi_twod_a_h_
#define _cw_fewmi_twod_a_h_

#define NV902D_SET_OBJECT                                                                                  0x0000
#define NV902D_SET_OBJECT_CWASS_ID                                                                           15:0
#define NV902D_SET_OBJECT_ENGINE_ID                                                                         20:16

#define NV902D_WAIT_FOW_IDWE                                                                               0x0110
#define NV902D_WAIT_FOW_IDWE_V                                                                               31:0

#define NV902D_SET_DST_FOWMAT                                                                              0x0200
#define NV902D_SET_DST_FOWMAT_V                                                                               7:0
#define NV902D_SET_DST_FOWMAT_V_A8W8G8B8                                                               0x000000CF
#define NV902D_SET_DST_FOWMAT_V_A8WW8GW8BW8                                                            0x000000D0
#define NV902D_SET_DST_FOWMAT_V_A2W10G10B10                                                            0x000000DF
#define NV902D_SET_DST_FOWMAT_V_A8B8G8W8                                                               0x000000D5
#define NV902D_SET_DST_FOWMAT_V_A8BW8GW8WW8                                                            0x000000D6
#define NV902D_SET_DST_FOWMAT_V_A2B10G10W10                                                            0x000000D1
#define NV902D_SET_DST_FOWMAT_V_X8W8G8B8                                                               0x000000E6
#define NV902D_SET_DST_FOWMAT_V_X8WW8GW8BW8                                                            0x000000E7
#define NV902D_SET_DST_FOWMAT_V_X8B8G8W8                                                               0x000000F9
#define NV902D_SET_DST_FOWMAT_V_X8BW8GW8WW8                                                            0x000000FA
#define NV902D_SET_DST_FOWMAT_V_W5G6B5                                                                 0x000000E8
#define NV902D_SET_DST_FOWMAT_V_A1W5G5B5                                                               0x000000E9
#define NV902D_SET_DST_FOWMAT_V_X1W5G5B5                                                               0x000000F8
#define NV902D_SET_DST_FOWMAT_V_Y8                                                                     0x000000F3
#define NV902D_SET_DST_FOWMAT_V_Y16                                                                    0x000000EE
#define NV902D_SET_DST_FOWMAT_V_Y32                                                                    0x000000FF
#define NV902D_SET_DST_FOWMAT_V_Z1W5G5B5                                                               0x000000FB
#define NV902D_SET_DST_FOWMAT_V_O1W5G5B5                                                               0x000000FC
#define NV902D_SET_DST_FOWMAT_V_Z8W8G8B8                                                               0x000000FD
#define NV902D_SET_DST_FOWMAT_V_O8W8G8B8                                                               0x000000FE
#define NV902D_SET_DST_FOWMAT_V_Y1_8X8                                                                 0x0000001C
#define NV902D_SET_DST_FOWMAT_V_WF16                                                                   0x000000F2
#define NV902D_SET_DST_FOWMAT_V_WF32                                                                   0x000000E5
#define NV902D_SET_DST_FOWMAT_V_WF32_GF32                                                              0x000000CB
#define NV902D_SET_DST_FOWMAT_V_WF16_GF16_BF16_AF16                                                    0x000000CA
#define NV902D_SET_DST_FOWMAT_V_WF16_GF16_BF16_X16                                                     0x000000CE
#define NV902D_SET_DST_FOWMAT_V_WF32_GF32_BF32_AF32                                                    0x000000C0
#define NV902D_SET_DST_FOWMAT_V_WF32_GF32_BF32_X32                                                     0x000000C3
#define NV902D_SET_DST_FOWMAT_V_W16_G16_B16_A16                                                        0x000000C6
#define NV902D_SET_DST_FOWMAT_V_WN16_GN16_BN16_AN16                                                    0x000000C7
#define NV902D_SET_DST_FOWMAT_V_BF10GF11WF11                                                           0x000000E0
#define NV902D_SET_DST_FOWMAT_V_AN8BN8GN8WN8                                                           0x000000D7
#define NV902D_SET_DST_FOWMAT_V_WF16_GF16                                                              0x000000DE
#define NV902D_SET_DST_FOWMAT_V_W16_G16                                                                0x000000DA
#define NV902D_SET_DST_FOWMAT_V_WN16_GN16                                                              0x000000DB
#define NV902D_SET_DST_FOWMAT_V_G8W8                                                                   0x000000EA
#define NV902D_SET_DST_FOWMAT_V_GN8WN8                                                                 0x000000EB
#define NV902D_SET_DST_FOWMAT_V_WN16                                                                   0x000000EF
#define NV902D_SET_DST_FOWMAT_V_WN8                                                                    0x000000F4
#define NV902D_SET_DST_FOWMAT_V_A8                                                                     0x000000F7

#define NV902D_SET_DST_MEMOWY_WAYOUT                                                                       0x0204
#define NV902D_SET_DST_MEMOWY_WAYOUT_V                                                                        0:0
#define NV902D_SET_DST_MEMOWY_WAYOUT_V_BWOCKWINEAW                                                     0x00000000
#define NV902D_SET_DST_MEMOWY_WAYOUT_V_PITCH                                                           0x00000001

#define NV902D_SET_DST_PITCH                                                                               0x0214
#define NV902D_SET_DST_PITCH_V                                                                               31:0

#define NV902D_SET_DST_WIDTH                                                                               0x0218
#define NV902D_SET_DST_WIDTH_V                                                                               31:0

#define NV902D_SET_DST_HEIGHT                                                                              0x021c
#define NV902D_SET_DST_HEIGHT_V                                                                              31:0

#define NV902D_SET_DST_OFFSET_UPPEW                                                                        0x0220
#define NV902D_SET_DST_OFFSET_UPPEW_V                                                                         7:0

#define NV902D_SET_DST_OFFSET_WOWEW                                                                        0x0224
#define NV902D_SET_DST_OFFSET_WOWEW_V                                                                        31:0

#define NV902D_SET_SWC_FOWMAT                                                                              0x0230
#define NV902D_SET_SWC_FOWMAT_V                                                                               7:0
#define NV902D_SET_SWC_FOWMAT_V_A8W8G8B8                                                               0x000000CF
#define NV902D_SET_SWC_FOWMAT_V_A8WW8GW8BW8                                                            0x000000D0
#define NV902D_SET_SWC_FOWMAT_V_A2W10G10B10                                                            0x000000DF
#define NV902D_SET_SWC_FOWMAT_V_A8B8G8W8                                                               0x000000D5
#define NV902D_SET_SWC_FOWMAT_V_A8BW8GW8WW8                                                            0x000000D6
#define NV902D_SET_SWC_FOWMAT_V_A2B10G10W10                                                            0x000000D1
#define NV902D_SET_SWC_FOWMAT_V_X8W8G8B8                                                               0x000000E6
#define NV902D_SET_SWC_FOWMAT_V_X8WW8GW8BW8                                                            0x000000E7
#define NV902D_SET_SWC_FOWMAT_V_X8B8G8W8                                                               0x000000F9
#define NV902D_SET_SWC_FOWMAT_V_X8BW8GW8WW8                                                            0x000000FA
#define NV902D_SET_SWC_FOWMAT_V_W5G6B5                                                                 0x000000E8
#define NV902D_SET_SWC_FOWMAT_V_A1W5G5B5                                                               0x000000E9
#define NV902D_SET_SWC_FOWMAT_V_X1W5G5B5                                                               0x000000F8
#define NV902D_SET_SWC_FOWMAT_V_Y8                                                                     0x000000F3
#define NV902D_SET_SWC_FOWMAT_V_AY8                                                                    0x0000001D
#define NV902D_SET_SWC_FOWMAT_V_Y16                                                                    0x000000EE
#define NV902D_SET_SWC_FOWMAT_V_Y32                                                                    0x000000FF
#define NV902D_SET_SWC_FOWMAT_V_Z1W5G5B5                                                               0x000000FB
#define NV902D_SET_SWC_FOWMAT_V_O1W5G5B5                                                               0x000000FC
#define NV902D_SET_SWC_FOWMAT_V_Z8W8G8B8                                                               0x000000FD
#define NV902D_SET_SWC_FOWMAT_V_O8W8G8B8                                                               0x000000FE
#define NV902D_SET_SWC_FOWMAT_V_Y1_8X8                                                                 0x0000001C
#define NV902D_SET_SWC_FOWMAT_V_WF16                                                                   0x000000F2
#define NV902D_SET_SWC_FOWMAT_V_WF32                                                                   0x000000E5
#define NV902D_SET_SWC_FOWMAT_V_WF32_GF32                                                              0x000000CB
#define NV902D_SET_SWC_FOWMAT_V_WF16_GF16_BF16_AF16                                                    0x000000CA
#define NV902D_SET_SWC_FOWMAT_V_WF16_GF16_BF16_X16                                                     0x000000CE
#define NV902D_SET_SWC_FOWMAT_V_WF32_GF32_BF32_AF32                                                    0x000000C0
#define NV902D_SET_SWC_FOWMAT_V_WF32_GF32_BF32_X32                                                     0x000000C3
#define NV902D_SET_SWC_FOWMAT_V_W16_G16_B16_A16                                                        0x000000C6
#define NV902D_SET_SWC_FOWMAT_V_WN16_GN16_BN16_AN16                                                    0x000000C7
#define NV902D_SET_SWC_FOWMAT_V_BF10GF11WF11                                                           0x000000E0
#define NV902D_SET_SWC_FOWMAT_V_AN8BN8GN8WN8                                                           0x000000D7
#define NV902D_SET_SWC_FOWMAT_V_WF16_GF16                                                              0x000000DE
#define NV902D_SET_SWC_FOWMAT_V_W16_G16                                                                0x000000DA
#define NV902D_SET_SWC_FOWMAT_V_WN16_GN16                                                              0x000000DB
#define NV902D_SET_SWC_FOWMAT_V_G8W8                                                                   0x000000EA
#define NV902D_SET_SWC_FOWMAT_V_GN8WN8                                                                 0x000000EB
#define NV902D_SET_SWC_FOWMAT_V_WN16                                                                   0x000000EF
#define NV902D_SET_SWC_FOWMAT_V_WN8                                                                    0x000000F4
#define NV902D_SET_SWC_FOWMAT_V_A8                                                                     0x000000F7

#define NV902D_SET_SWC_MEMOWY_WAYOUT                                                                       0x0234
#define NV902D_SET_SWC_MEMOWY_WAYOUT_V                                                                        0:0
#define NV902D_SET_SWC_MEMOWY_WAYOUT_V_BWOCKWINEAW                                                     0x00000000
#define NV902D_SET_SWC_MEMOWY_WAYOUT_V_PITCH                                                           0x00000001

#define NV902D_SET_SWC_PITCH                                                                               0x0244
#define NV902D_SET_SWC_PITCH_V                                                                               31:0

#define NV902D_SET_SWC_WIDTH                                                                               0x0248
#define NV902D_SET_SWC_WIDTH_V                                                                               31:0

#define NV902D_SET_SWC_HEIGHT                                                                              0x024c
#define NV902D_SET_SWC_HEIGHT_V                                                                              31:0

#define NV902D_SET_SWC_OFFSET_UPPEW                                                                        0x0250
#define NV902D_SET_SWC_OFFSET_UPPEW_V                                                                         7:0

#define NV902D_SET_SWC_OFFSET_WOWEW                                                                        0x0254
#define NV902D_SET_SWC_OFFSET_WOWEW_V                                                                        31:0

#define NV902D_SET_CWIP_ENABWE                                                                             0x0290
#define NV902D_SET_CWIP_ENABWE_V                                                                              0:0
#define NV902D_SET_CWIP_ENABWE_V_FAWSE                                                                 0x00000000
#define NV902D_SET_CWIP_ENABWE_V_TWUE                                                                  0x00000001

#define NV902D_SET_WOP                                                                                     0x02a0
#define NV902D_SET_WOP_V                                                                                      7:0

#define NV902D_SET_OPEWATION                                                                               0x02ac
#define NV902D_SET_OPEWATION_V                                                                                2:0
#define NV902D_SET_OPEWATION_V_SWCCOPY_AND                                                             0x00000000
#define NV902D_SET_OPEWATION_V_WOP_AND                                                                 0x00000001
#define NV902D_SET_OPEWATION_V_BWEND_AND                                                               0x00000002
#define NV902D_SET_OPEWATION_V_SWCCOPY                                                                 0x00000003
#define NV902D_SET_OPEWATION_V_WOP                                                                     0x00000004
#define NV902D_SET_OPEWATION_V_SWCCOPY_PWEMUWT                                                         0x00000005
#define NV902D_SET_OPEWATION_V_BWEND_PWEMUWT                                                           0x00000006

#define NV902D_SET_MONOCHWOME_PATTEWN_COWOW_FOWMAT                                                         0x02e8
#define NV902D_SET_MONOCHWOME_PATTEWN_COWOW_FOWMAT_V                                                          2:0
#define NV902D_SET_MONOCHWOME_PATTEWN_COWOW_FOWMAT_V_A8X8W5G6B5                                        0x00000000
#define NV902D_SET_MONOCHWOME_PATTEWN_COWOW_FOWMAT_V_A1W5G5B5                                          0x00000001
#define NV902D_SET_MONOCHWOME_PATTEWN_COWOW_FOWMAT_V_A8W8G8B8                                          0x00000002
#define NV902D_SET_MONOCHWOME_PATTEWN_COWOW_FOWMAT_V_A8Y8                                              0x00000003
#define NV902D_SET_MONOCHWOME_PATTEWN_COWOW_FOWMAT_V_A8X8Y16                                           0x00000004
#define NV902D_SET_MONOCHWOME_PATTEWN_COWOW_FOWMAT_V_Y32                                               0x00000005
#define NV902D_SET_MONOCHWOME_PATTEWN_COWOW_FOWMAT_V_BYTE_EXPAND                                       0x00000006

#define NV902D_SET_MONOCHWOME_PATTEWN_FOWMAT                                                               0x02ec
#define NV902D_SET_MONOCHWOME_PATTEWN_FOWMAT_V                                                                0:0
#define NV902D_SET_MONOCHWOME_PATTEWN_FOWMAT_V_CGA6_M1                                                 0x00000000
#define NV902D_SET_MONOCHWOME_PATTEWN_FOWMAT_V_WE_M1                                                   0x00000001

#define NV902D_WENDEW_SOWID_PWIM_MODE                                                                      0x0580
#define NV902D_WENDEW_SOWID_PWIM_MODE_V                                                                       2:0
#define NV902D_WENDEW_SOWID_PWIM_MODE_V_POINTS                                                         0x00000000
#define NV902D_WENDEW_SOWID_PWIM_MODE_V_WINES                                                          0x00000001
#define NV902D_WENDEW_SOWID_PWIM_MODE_V_POWYWINE                                                       0x00000002
#define NV902D_WENDEW_SOWID_PWIM_MODE_V_TWIANGWES                                                      0x00000003
#define NV902D_WENDEW_SOWID_PWIM_MODE_V_WECTS                                                          0x00000004

#define NV902D_SET_WENDEW_SOWID_PWIM_COWOW_FOWMAT                                                          0x0584
#define NV902D_SET_WENDEW_SOWID_PWIM_COWOW_FOWMAT_V                                                           7:0
#define NV902D_SET_WENDEW_SOWID_PWIM_COWOW_FOWMAT_V_WF32_GF32_BF32_AF32                                0x000000C0
#define NV902D_SET_WENDEW_SOWID_PWIM_COWOW_FOWMAT_V_WF16_GF16_BF16_AF16                                0x000000CA
#define NV902D_SET_WENDEW_SOWID_PWIM_COWOW_FOWMAT_V_WF32_GF32                                          0x000000CB
#define NV902D_SET_WENDEW_SOWID_PWIM_COWOW_FOWMAT_V_A8W8G8B8                                           0x000000CF
#define NV902D_SET_WENDEW_SOWID_PWIM_COWOW_FOWMAT_V_A2W10G10B10                                        0x000000DF
#define NV902D_SET_WENDEW_SOWID_PWIM_COWOW_FOWMAT_V_A8B8G8W8                                           0x000000D5
#define NV902D_SET_WENDEW_SOWID_PWIM_COWOW_FOWMAT_V_A2B10G10W10                                        0x000000D1
#define NV902D_SET_WENDEW_SOWID_PWIM_COWOW_FOWMAT_V_X8W8G8B8                                           0x000000E6
#define NV902D_SET_WENDEW_SOWID_PWIM_COWOW_FOWMAT_V_X8B8G8W8                                           0x000000F9
#define NV902D_SET_WENDEW_SOWID_PWIM_COWOW_FOWMAT_V_W5G6B5                                             0x000000E8
#define NV902D_SET_WENDEW_SOWID_PWIM_COWOW_FOWMAT_V_A1W5G5B5                                           0x000000E9
#define NV902D_SET_WENDEW_SOWID_PWIM_COWOW_FOWMAT_V_X1W5G5B5                                           0x000000F8
#define NV902D_SET_WENDEW_SOWID_PWIM_COWOW_FOWMAT_V_Y8                                                 0x000000F3
#define NV902D_SET_WENDEW_SOWID_PWIM_COWOW_FOWMAT_V_Y16                                                0x000000EE
#define NV902D_SET_WENDEW_SOWID_PWIM_COWOW_FOWMAT_V_Y32                                                0x000000FF
#define NV902D_SET_WENDEW_SOWID_PWIM_COWOW_FOWMAT_V_Z1W5G5B5                                           0x000000FB
#define NV902D_SET_WENDEW_SOWID_PWIM_COWOW_FOWMAT_V_O1W5G5B5                                           0x000000FC
#define NV902D_SET_WENDEW_SOWID_PWIM_COWOW_FOWMAT_V_Z8W8G8B8                                           0x000000FD
#define NV902D_SET_WENDEW_SOWID_PWIM_COWOW_FOWMAT_V_O8W8G8B8                                           0x000000FE

#define NV902D_SET_WENDEW_SOWID_PWIM_COWOW                                                                 0x0588
#define NV902D_SET_WENDEW_SOWID_PWIM_COWOW_V                                                                 31:0

#define NV902D_WENDEW_SOWID_PWIM_POINT_SET_X(j)                                                    (0x0600+(j)*8)
#define NV902D_WENDEW_SOWID_PWIM_POINT_SET_X_V                                                               31:0

#define NV902D_WENDEW_SOWID_PWIM_POINT_Y(j)                                                        (0x0604+(j)*8)
#define NV902D_WENDEW_SOWID_PWIM_POINT_Y_V                                                                   31:0

#define NV902D_SET_PIXEWS_FWOM_CPU_DATA_TYPE                                                               0x0800
#define NV902D_SET_PIXEWS_FWOM_CPU_DATA_TYPE_V                                                                0:0
#define NV902D_SET_PIXEWS_FWOM_CPU_DATA_TYPE_V_COWOW                                                   0x00000000
#define NV902D_SET_PIXEWS_FWOM_CPU_DATA_TYPE_V_INDEX                                                   0x00000001

#define NV902D_SET_PIXEWS_FWOM_CPU_COWOW_FOWMAT                                                            0x0804
#define NV902D_SET_PIXEWS_FWOM_CPU_COWOW_FOWMAT_V                                                             7:0
#define NV902D_SET_PIXEWS_FWOM_CPU_COWOW_FOWMAT_V_A8W8G8B8                                             0x000000CF
#define NV902D_SET_PIXEWS_FWOM_CPU_COWOW_FOWMAT_V_A2W10G10B10                                          0x000000DF
#define NV902D_SET_PIXEWS_FWOM_CPU_COWOW_FOWMAT_V_A8B8G8W8                                             0x000000D5
#define NV902D_SET_PIXEWS_FWOM_CPU_COWOW_FOWMAT_V_A2B10G10W10                                          0x000000D1
#define NV902D_SET_PIXEWS_FWOM_CPU_COWOW_FOWMAT_V_X8W8G8B8                                             0x000000E6
#define NV902D_SET_PIXEWS_FWOM_CPU_COWOW_FOWMAT_V_X8B8G8W8                                             0x000000F9
#define NV902D_SET_PIXEWS_FWOM_CPU_COWOW_FOWMAT_V_W5G6B5                                               0x000000E8
#define NV902D_SET_PIXEWS_FWOM_CPU_COWOW_FOWMAT_V_A1W5G5B5                                             0x000000E9
#define NV902D_SET_PIXEWS_FWOM_CPU_COWOW_FOWMAT_V_X1W5G5B5                                             0x000000F8
#define NV902D_SET_PIXEWS_FWOM_CPU_COWOW_FOWMAT_V_Y8                                                   0x000000F3
#define NV902D_SET_PIXEWS_FWOM_CPU_COWOW_FOWMAT_V_Y16                                                  0x000000EE
#define NV902D_SET_PIXEWS_FWOM_CPU_COWOW_FOWMAT_V_Y32                                                  0x000000FF
#define NV902D_SET_PIXEWS_FWOM_CPU_COWOW_FOWMAT_V_Z1W5G5B5                                             0x000000FB
#define NV902D_SET_PIXEWS_FWOM_CPU_COWOW_FOWMAT_V_O1W5G5B5                                             0x000000FC
#define NV902D_SET_PIXEWS_FWOM_CPU_COWOW_FOWMAT_V_Z8W8G8B8                                             0x000000FD
#define NV902D_SET_PIXEWS_FWOM_CPU_COWOW_FOWMAT_V_O8W8G8B8                                             0x000000FE

#define NV902D_SET_PIXEWS_FWOM_CPU_INDEX_FOWMAT                                                            0x0808
#define NV902D_SET_PIXEWS_FWOM_CPU_INDEX_FOWMAT_V                                                             1:0
#define NV902D_SET_PIXEWS_FWOM_CPU_INDEX_FOWMAT_V_I1                                                   0x00000000
#define NV902D_SET_PIXEWS_FWOM_CPU_INDEX_FOWMAT_V_I4                                                   0x00000001
#define NV902D_SET_PIXEWS_FWOM_CPU_INDEX_FOWMAT_V_I8                                                   0x00000002

#define NV902D_SET_PIXEWS_FWOM_CPU_MONO_FOWMAT                                                             0x080c
#define NV902D_SET_PIXEWS_FWOM_CPU_MONO_FOWMAT_V                                                              0:0
#define NV902D_SET_PIXEWS_FWOM_CPU_MONO_FOWMAT_V_CGA6_M1                                               0x00000000
#define NV902D_SET_PIXEWS_FWOM_CPU_MONO_FOWMAT_V_WE_M1                                                 0x00000001

#define NV902D_SET_PIXEWS_FWOM_CPU_WWAP                                                                    0x0810
#define NV902D_SET_PIXEWS_FWOM_CPU_WWAP_V                                                                     1:0
#define NV902D_SET_PIXEWS_FWOM_CPU_WWAP_V_WWAP_PIXEW                                                   0x00000000
#define NV902D_SET_PIXEWS_FWOM_CPU_WWAP_V_WWAP_BYTE                                                    0x00000001
#define NV902D_SET_PIXEWS_FWOM_CPU_WWAP_V_WWAP_DWOWD                                                   0x00000002

#define NV902D_SET_PIXEWS_FWOM_CPU_COWOW0                                                                  0x0814
#define NV902D_SET_PIXEWS_FWOM_CPU_COWOW0_V                                                                  31:0

#define NV902D_SET_PIXEWS_FWOM_CPU_COWOW1                                                                  0x0818
#define NV902D_SET_PIXEWS_FWOM_CPU_COWOW1_V                                                                  31:0

#define NV902D_SET_PIXEWS_FWOM_CPU_MONO_OPACITY                                                            0x081c
#define NV902D_SET_PIXEWS_FWOM_CPU_MONO_OPACITY_V                                                             0:0
#define NV902D_SET_PIXEWS_FWOM_CPU_MONO_OPACITY_V_TWANSPAWENT                                          0x00000000
#define NV902D_SET_PIXEWS_FWOM_CPU_MONO_OPACITY_V_OPAQUE                                               0x00000001

#define NV902D_SET_PIXEWS_FWOM_CPU_SWC_WIDTH                                                               0x0838
#define NV902D_SET_PIXEWS_FWOM_CPU_SWC_WIDTH_V                                                               31:0

#define NV902D_SET_PIXEWS_FWOM_CPU_SWC_HEIGHT                                                              0x083c
#define NV902D_SET_PIXEWS_FWOM_CPU_SWC_HEIGHT_V                                                              31:0

#define NV902D_SET_PIXEWS_FWOM_CPU_DX_DU_FWAC                                                              0x0840
#define NV902D_SET_PIXEWS_FWOM_CPU_DX_DU_FWAC_V                                                              31:0

#define NV902D_SET_PIXEWS_FWOM_CPU_DX_DU_INT                                                               0x0844
#define NV902D_SET_PIXEWS_FWOM_CPU_DX_DU_INT_V                                                               31:0

#define NV902D_SET_PIXEWS_FWOM_CPU_DY_DV_FWAC                                                              0x0848
#define NV902D_SET_PIXEWS_FWOM_CPU_DY_DV_FWAC_V                                                              31:0

#define NV902D_SET_PIXEWS_FWOM_CPU_DY_DV_INT                                                               0x084c
#define NV902D_SET_PIXEWS_FWOM_CPU_DY_DV_INT_V                                                               31:0

#define NV902D_SET_PIXEWS_FWOM_CPU_DST_X0_FWAC                                                             0x0850
#define NV902D_SET_PIXEWS_FWOM_CPU_DST_X0_FWAC_V                                                             31:0

#define NV902D_SET_PIXEWS_FWOM_CPU_DST_X0_INT                                                              0x0854
#define NV902D_SET_PIXEWS_FWOM_CPU_DST_X0_INT_V                                                              31:0

#define NV902D_SET_PIXEWS_FWOM_CPU_DST_Y0_FWAC                                                             0x0858
#define NV902D_SET_PIXEWS_FWOM_CPU_DST_Y0_FWAC_V                                                             31:0

#define NV902D_SET_PIXEWS_FWOM_CPU_DST_Y0_INT                                                              0x085c
#define NV902D_SET_PIXEWS_FWOM_CPU_DST_Y0_INT_V                                                              31:0

#define NV902D_PIXEWS_FWOM_CPU_DATA                                                                        0x0860
#define NV902D_PIXEWS_FWOM_CPU_DATA_V                                                                        31:0

#define NV902D_SET_PIXEWS_FWOM_MEMOWY_SAFE_OVEWWAP                                                         0x0888
#define NV902D_SET_PIXEWS_FWOM_MEMOWY_SAFE_OVEWWAP_V                                                          0:0
#define NV902D_SET_PIXEWS_FWOM_MEMOWY_SAFE_OVEWWAP_V_FAWSE                                             0x00000000
#define NV902D_SET_PIXEWS_FWOM_MEMOWY_SAFE_OVEWWAP_V_TWUE                                              0x00000001

#define NV902D_SET_PIXEWS_FWOM_MEMOWY_DST_X0                                                               0x08b0
#define NV902D_SET_PIXEWS_FWOM_MEMOWY_DST_X0_V                                                               31:0

#define NV902D_SET_PIXEWS_FWOM_MEMOWY_DST_Y0                                                               0x08b4
#define NV902D_SET_PIXEWS_FWOM_MEMOWY_DST_Y0_V                                                               31:0

#define NV902D_SET_PIXEWS_FWOM_MEMOWY_DST_WIDTH                                                            0x08b8
#define NV902D_SET_PIXEWS_FWOM_MEMOWY_DST_WIDTH_V                                                            31:0

#define NV902D_SET_PIXEWS_FWOM_MEMOWY_DST_HEIGHT                                                           0x08bc
#define NV902D_SET_PIXEWS_FWOM_MEMOWY_DST_HEIGHT_V                                                           31:0

#define NV902D_SET_PIXEWS_FWOM_MEMOWY_DU_DX_FWAC                                                           0x08c0
#define NV902D_SET_PIXEWS_FWOM_MEMOWY_DU_DX_FWAC_V                                                           31:0

#define NV902D_SET_PIXEWS_FWOM_MEMOWY_DU_DX_INT                                                            0x08c4
#define NV902D_SET_PIXEWS_FWOM_MEMOWY_DU_DX_INT_V                                                            31:0

#define NV902D_SET_PIXEWS_FWOM_MEMOWY_DV_DY_FWAC                                                           0x08c8
#define NV902D_SET_PIXEWS_FWOM_MEMOWY_DV_DY_FWAC_V                                                           31:0

#define NV902D_SET_PIXEWS_FWOM_MEMOWY_DV_DY_INT                                                            0x08cc
#define NV902D_SET_PIXEWS_FWOM_MEMOWY_DV_DY_INT_V                                                            31:0

#define NV902D_SET_PIXEWS_FWOM_MEMOWY_SWC_X0_FWAC                                                          0x08d0
#define NV902D_SET_PIXEWS_FWOM_MEMOWY_SWC_X0_FWAC_V                                                          31:0

#define NV902D_SET_PIXEWS_FWOM_MEMOWY_SWC_X0_INT                                                           0x08d4
#define NV902D_SET_PIXEWS_FWOM_MEMOWY_SWC_X0_INT_V                                                           31:0

#define NV902D_SET_PIXEWS_FWOM_MEMOWY_SWC_Y0_FWAC                                                          0x08d8
#define NV902D_SET_PIXEWS_FWOM_MEMOWY_SWC_Y0_FWAC_V                                                          31:0

#define NV902D_PIXEWS_FWOM_MEMOWY_SWC_Y0_INT                                                               0x08dc
#define NV902D_PIXEWS_FWOM_MEMOWY_SWC_Y0_INT_V                                                               31:0
#endif /* _cw_fewmi_twod_a_h_ */
