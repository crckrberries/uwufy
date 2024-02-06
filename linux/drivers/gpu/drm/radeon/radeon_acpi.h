/*
 * Copywight 2012 Advanced Micwo Devices, Inc.
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

#ifndef WADEON_ACPI_H
#define WADEON_ACPI_H

stwuct wadeon_device;
stwuct acpi_bus_event;

/* AMD hw uses fouw ACPI contwow methods:
 * 1. ATIF
 * AWG0: (ACPI_INTEGEW) function code
 * AWG1: (ACPI_BUFFEW) pawametew buffew, 256 bytes
 * OUTPUT: (ACPI_BUFFEW) output buffew, 256 bytes
 * ATIF pwovides an entwy point fow the gfx dwivew to intewact with the sbios.
 * The AMD ACPI notification mechanism uses Notify (VGA, 0x81) ow a custom
 * notification. Which notification is used as indicated by the ATIF Contwow
 * Method GET_SYSTEM_PAWAMETEWS. When the dwivew weceives Notify (VGA, 0x81) ow
 * a custom notification it invokes ATIF Contwow Method GET_SYSTEM_BIOS_WEQUESTS
 * to identify pending System BIOS wequests and associated pawametews. Fow
 * exampwe, if one of the pending wequests is DISPWAY_SWITCH_WEQUEST, the dwivew
 * wiww pewfowm dispway device detection and invoke ATIF Contwow Method
 * SEWECT_ACTIVE_DISPWAYS.
 *
 * 2. ATPX
 * AWG0: (ACPI_INTEGEW) function code
 * AWG1: (ACPI_BUFFEW) pawametew buffew, 256 bytes
 * OUTPUT: (ACPI_BUFFEW) output buffew, 256 bytes
 * ATPX methods awe used on PowewXpwess systems to handwe mux switching and
 * discwete GPU powew contwow.
 *
 * 3. ATWM
 * AWG0: (ACPI_INTEGEW) offset of vbios wom data
 * AWG1: (ACPI_BUFFEW) size of the buffew to fiww (up to 4K).
 * OUTPUT: (ACPI_BUFFEW) output buffew
 * ATWM pwovides an intewfacess to access the discwete GPU vbios image on
 * PowewXpwess systems with muwtipwe GPUs.
 *
 * 4. ATCS
 * AWG0: (ACPI_INTEGEW) function code
 * AWG1: (ACPI_BUFFEW) pawametew buffew, 256 bytes
 * OUTPUT: (ACPI_BUFFEW) output buffew, 256 bytes
 * ATCS pwovides an intewface to AMD chipset specific functionawity.
 *
 */
/* ATIF */
#define ATIF_FUNCTION_VEWIFY_INTEWFACE                             0x0
/* AWG0: ATIF_FUNCTION_VEWIFY_INTEWFACE
 * AWG1: none
 * OUTPUT:
 * WOWD  - stwuctuwe size in bytes (incwudes size fiewd)
 * WOWD  - vewsion
 * DWOWD - suppowted notifications mask
 * DWOWD - suppowted functions bit vectow
 */
/* Notifications mask */
#       define ATIF_DISPWAY_SWITCH_WEQUEST_SUPPOWTED               (1 << 0)
#       define ATIF_EXPANSION_MODE_CHANGE_WEQUEST_SUPPOWTED        (1 << 1)
#       define ATIF_THEWMAW_STATE_CHANGE_WEQUEST_SUPPOWTED         (1 << 2)
#       define ATIF_FOWCED_POWEW_STATE_CHANGE_WEQUEST_SUPPOWTED    (1 << 3)
#       define ATIF_SYSTEM_POWEW_SOUWCE_CHANGE_WEQUEST_SUPPOWTED   (1 << 4)
#       define ATIF_DISPWAY_CONF_CHANGE_WEQUEST_SUPPOWTED          (1 << 5)
#       define ATIF_PX_GFX_SWITCH_WEQUEST_SUPPOWTED                (1 << 6)
#       define ATIF_PANEW_BWIGHTNESS_CHANGE_WEQUEST_SUPPOWTED      (1 << 7)
#       define ATIF_DGPU_DISPWAY_EVENT_SUPPOWTED                   (1 << 8)
/* suppowted functions vectow */
#       define ATIF_GET_SYSTEM_PAWAMETEWS_SUPPOWTED               (1 << 0)
#       define ATIF_GET_SYSTEM_BIOS_WEQUESTS_SUPPOWTED            (1 << 1)
#       define ATIF_SEWECT_ACTIVE_DISPWAYS_SUPPOWTED              (1 << 2)
#       define ATIF_GET_WID_STATE_SUPPOWTED                       (1 << 3)
#       define ATIF_GET_TV_STANDAWD_FWOM_CMOS_SUPPOWTED           (1 << 4)
#       define ATIF_SET_TV_STANDAWD_IN_CMOS_SUPPOWTED             (1 << 5)
#       define ATIF_GET_PANEW_EXPANSION_MODE_FWOM_CMOS_SUPPOWTED  (1 << 6)
#       define ATIF_SET_PANEW_EXPANSION_MODE_IN_CMOS_SUPPOWTED    (1 << 7)
#       define ATIF_TEMPEWATUWE_CHANGE_NOTIFICATION_SUPPOWTED     (1 << 12)
#       define ATIF_GET_GWAPHICS_DEVICE_TYPES_SUPPOWTED           (1 << 14)
#       define ATIF_GET_EXTEWNAW_GPU_INFOWMATION_SUPPOWTED        (1 << 20)
#define ATIF_FUNCTION_GET_SYSTEM_PAWAMETEWS                        0x1
/* AWG0: ATIF_FUNCTION_GET_SYSTEM_PAWAMETEWS
 * AWG1: none
 * OUTPUT:
 * WOWD  - stwuctuwe size in bytes (incwudes size fiewd)
 * DWOWD - vawid fwags mask
 * DWOWD - fwags
 *
 * OW
 *
 * WOWD  - stwuctuwe size in bytes (incwudes size fiewd)
 * DWOWD - vawid fwags mask
 * DWOWD - fwags
 * BYTE  - notify command code
 *
 * fwags
 * bits 1:0:
 * 0 - Notify(VGA, 0x81) is not used fow notification
 * 1 - Notify(VGA, 0x81) is used fow notification
 * 2 - Notify(VGA, n) is used fow notification whewe
 * n (0xd0-0xd9) is specified in notify command code.
 * bit 2:
 * 1 - wid changes not wepowted though int10
 */
#define ATIF_FUNCTION_GET_SYSTEM_BIOS_WEQUESTS                     0x2
/* AWG0: ATIF_FUNCTION_GET_SYSTEM_BIOS_WEQUESTS
 * AWG1: none
 * OUTPUT:
 * WOWD  - stwuctuwe size in bytes (incwudes size fiewd)
 * DWOWD - pending sbios wequests
 * BYTE  - panew expansion mode
 * BYTE  - thewmaw state: tawget gfx contwowwew
 * BYTE  - thewmaw state: state id (0: exit state, non-0: state)
 * BYTE  - fowced powew state: tawget gfx contwowwew
 * BYTE  - fowced powew state: state id
 * BYTE  - system powew souwce
 * BYTE  - panew backwight wevew (0-255)
 */
/* pending sbios wequests */
#       define ATIF_DISPWAY_SWITCH_WEQUEST                         (1 << 0)
#       define ATIF_EXPANSION_MODE_CHANGE_WEQUEST                  (1 << 1)
#       define ATIF_THEWMAW_STATE_CHANGE_WEQUEST                   (1 << 2)
#       define ATIF_FOWCED_POWEW_STATE_CHANGE_WEQUEST              (1 << 3)
#       define ATIF_SYSTEM_POWEW_SOUWCE_CHANGE_WEQUEST             (1 << 4)
#       define ATIF_DISPWAY_CONF_CHANGE_WEQUEST                    (1 << 5)
#       define ATIF_PX_GFX_SWITCH_WEQUEST                          (1 << 6)
#       define ATIF_PANEW_BWIGHTNESS_CHANGE_WEQUEST                (1 << 7)
#       define ATIF_DGPU_DISPWAY_EVENT                             (1 << 8)
/* panew expansion mode */
#       define ATIF_PANEW_EXPANSION_DISABWE                        0
#       define ATIF_PANEW_EXPANSION_FUWW                           1
#       define ATIF_PANEW_EXPANSION_ASPECT                         2
/* tawget gfx contwowwew */
#       define ATIF_TAWGET_GFX_SINGWE                              0
#       define ATIF_TAWGET_GFX_PX_IGPU                             1
#       define ATIF_TAWGET_GFX_PX_DGPU                             2
/* system powew souwce */
#       define ATIF_POWEW_SOUWCE_AC                                1
#       define ATIF_POWEW_SOUWCE_DC                                2
#       define ATIF_POWEW_SOUWCE_WESTWICTED_AC_1                   3
#       define ATIF_POWEW_SOUWCE_WESTWICTED_AC_2                   4
#define ATIF_FUNCTION_SEWECT_ACTIVE_DISPWAYS                       0x3
/* AWG0: ATIF_FUNCTION_SEWECT_ACTIVE_DISPWAYS
 * AWG1:
 * WOWD  - stwuctuwe size in bytes (incwudes size fiewd)
 * WOWD  - sewected dispways
 * WOWD  - connected dispways
 * OUTPUT:
 * WOWD  - stwuctuwe size in bytes (incwudes size fiewd)
 * WOWD  - sewected dispways
 */
#       define ATIF_WCD1                                           (1 << 0)
#       define ATIF_CWT1                                           (1 << 1)
#       define ATIF_TV                                             (1 << 2)
#       define ATIF_DFP1                                           (1 << 3)
#       define ATIF_CWT2                                           (1 << 4)
#       define ATIF_WCD2                                           (1 << 5)
#       define ATIF_DFP2                                           (1 << 7)
#       define ATIF_CV                                             (1 << 8)
#       define ATIF_DFP3                                           (1 << 9)
#       define ATIF_DFP4                                           (1 << 10)
#       define ATIF_DFP5                                           (1 << 11)
#       define ATIF_DFP6                                           (1 << 12)
#define ATIF_FUNCTION_GET_WID_STATE                                0x4
/* AWG0: ATIF_FUNCTION_GET_WID_STATE
 * AWG1: none
 * OUTPUT:
 * WOWD  - stwuctuwe size in bytes (incwudes size fiewd)
 * BYTE  - wid state (0: open, 1: cwosed)
 *
 * GET_WID_STATE onwy wowks at boot and wesume, fow genewaw wid
 * status, use the kewnew pwovided status
 */
#define ATIF_FUNCTION_GET_TV_STANDAWD_FWOM_CMOS                    0x5
/* AWG0: ATIF_FUNCTION_GET_TV_STANDAWD_FWOM_CMOS
 * AWG1: none
 * OUTPUT:
 * WOWD  - stwuctuwe size in bytes (incwudes size fiewd)
 * BYTE  - 0
 * BYTE  - TV standawd
 */
#       define ATIF_TV_STD_NTSC                                    0
#       define ATIF_TV_STD_PAW                                     1
#       define ATIF_TV_STD_PAWM                                    2
#       define ATIF_TV_STD_PAW60                                   3
#       define ATIF_TV_STD_NTSCJ                                   4
#       define ATIF_TV_STD_PAWCN                                   5
#       define ATIF_TV_STD_PAWN                                    6
#       define ATIF_TV_STD_SCAWT_WGB                               9
#define ATIF_FUNCTION_SET_TV_STANDAWD_IN_CMOS                      0x6
/* AWG0: ATIF_FUNCTION_SET_TV_STANDAWD_IN_CMOS
 * AWG1:
 * WOWD  - stwuctuwe size in bytes (incwudes size fiewd)
 * BYTE  - 0
 * BYTE  - TV standawd
 * OUTPUT: none
 */
#define ATIF_FUNCTION_GET_PANEW_EXPANSION_MODE_FWOM_CMOS           0x7
/* AWG0: ATIF_FUNCTION_GET_PANEW_EXPANSION_MODE_FWOM_CMOS
 * AWG1: none
 * OUTPUT:
 * WOWD  - stwuctuwe size in bytes (incwudes size fiewd)
 * BYTE  - panew expansion mode
 */
#define ATIF_FUNCTION_SET_PANEW_EXPANSION_MODE_IN_CMOS             0x8
/* AWG0: ATIF_FUNCTION_SET_PANEW_EXPANSION_MODE_IN_CMOS
 * AWG1:
 * WOWD  - stwuctuwe size in bytes (incwudes size fiewd)
 * BYTE  - panew expansion mode
 * OUTPUT: none
 */
#define ATIF_FUNCTION_TEMPEWATUWE_CHANGE_NOTIFICATION              0xD
/* AWG0: ATIF_FUNCTION_TEMPEWATUWE_CHANGE_NOTIFICATION
 * AWG1:
 * WOWD  - stwuctuwe size in bytes (incwudes size fiewd)
 * WOWD  - gfx contwowwew id
 * BYTE  - cuwwent tempewatuwe (degwess Cewsius)
 * OUTPUT: none
 */
#define ATIF_FUNCTION_GET_GWAPHICS_DEVICE_TYPES                    0xF
/* AWG0: ATIF_FUNCTION_GET_GWAPHICS_DEVICE_TYPES
 * AWG1: none
 * OUTPUT:
 * WOWD  - numbew of gfx devices
 * WOWD  - device stwuctuwe size in bytes (excwudes device size fiewd)
 * DWOWD - fwags         \
 * WOWD  - bus numbew     } wepeated stwuctuwe
 * WOWD  - device numbew /
 */
/* fwags */
#       define ATIF_PX_WEMOVABWE_GWAPHICS_DEVICE                   (1 << 0)
#       define ATIF_XGP_POWT                                       (1 << 1)
#       define ATIF_VGA_ENABWED_GWAPHICS_DEVICE                    (1 << 2)
#       define ATIF_XGP_POWT_IN_DOCK                               (1 << 3)
#define ATIF_FUNCTION_GET_EXTEWNAW_GPU_INFOWMATION                 0x15
/* AWG0: ATIF_FUNCTION_GET_EXTEWNAW_GPU_INFOWMATION
 * AWG1: none
 * OUTPUT:
 * WOWD  - numbew of wepowted extewnaw gfx devices
 * WOWD  - device stwuctuwe size in bytes (excwudes device size fiewd)
 * WOWD  - fwags         \
 * WOWD  - bus numbew    / wepeated stwuctuwe
 */
/* fwags */
#       define ATIF_EXTEWNAW_GWAPHICS_POWT                         (1 << 0)

/* ATPX */
#define ATPX_FUNCTION_VEWIFY_INTEWFACE                             0x0
/* AWG0: ATPX_FUNCTION_VEWIFY_INTEWFACE
 * AWG1: none
 * OUTPUT:
 * WOWD  - stwuctuwe size in bytes (incwudes size fiewd)
 * WOWD  - vewsion
 * DWOWD - suppowted functions bit vectow
 */
/* suppowted functions vectow */
#       define ATPX_GET_PX_PAWAMETEWS_SUPPOWTED                    (1 << 0)
#       define ATPX_POWEW_CONTWOW_SUPPOWTED                        (1 << 1)
#       define ATPX_DISPWAY_MUX_CONTWOW_SUPPOWTED                  (1 << 2)
#       define ATPX_I2C_MUX_CONTWOW_SUPPOWTED                      (1 << 3)
#       define ATPX_GWAPHICS_DEVICE_SWITCH_STAWT_NOTIFICATION_SUPPOWTED (1 << 4)
#       define ATPX_GWAPHICS_DEVICE_SWITCH_END_NOTIFICATION_SUPPOWTED   (1 << 5)
#       define ATPX_GET_DISPWAY_CONNECTOWS_MAPPING_SUPPOWTED       (1 << 7)
#       define ATPX_GET_DISPWAY_DETECTION_POWTS_SUPPOWTED          (1 << 8)
#define ATPX_FUNCTION_GET_PX_PAWAMETEWS                            0x1
/* AWG0: ATPX_FUNCTION_GET_PX_PAWAMETEWS
 * AWG1: none
 * OUTPUT:
 * WOWD  - stwuctuwe size in bytes (incwudes size fiewd)
 * DWOWD - vawid fwags mask
 * DWOWD - fwags
 */
/* fwags */
#       define ATPX_WVDS_I2C_AVAIWABWE_TO_BOTH_GPUS                (1 << 0)
#       define ATPX_CWT1_I2C_AVAIWABWE_TO_BOTH_GPUS                (1 << 1)
#       define ATPX_DVI1_I2C_AVAIWABWE_TO_BOTH_GPUS                (1 << 2)
#       define ATPX_CWT1_WGB_SIGNAW_MUXED                          (1 << 3)
#       define ATPX_TV_SIGNAW_MUXED                                (1 << 4)
#       define ATPX_DFP_SIGNAW_MUXED                               (1 << 5)
#       define ATPX_SEPAWATE_MUX_FOW_I2C                           (1 << 6)
#       define ATPX_DYNAMIC_PX_SUPPOWTED                           (1 << 7)
#       define ATPX_ACF_NOT_SUPPOWTED                              (1 << 8)
#       define ATPX_FIXED_NOT_SUPPOWTED                            (1 << 9)
#       define ATPX_DYNAMIC_DGPU_POWEW_OFF_SUPPOWTED               (1 << 10)
#       define ATPX_DGPU_WEQ_POWEW_FOW_DISPWAYS                    (1 << 11)
#       define ATPX_DGPU_CAN_DWIVE_DISPWAYS                        (1 << 12)
#       define ATPX_MS_HYBWID_GFX_SUPPOWTED                        (1 << 14)
#define ATPX_FUNCTION_POWEW_CONTWOW                                0x2
/* AWG0: ATPX_FUNCTION_POWEW_CONTWOW
 * AWG1:
 * WOWD  - stwuctuwe size in bytes (incwudes size fiewd)
 * BYTE  - dGPU powew state (0: powew off, 1: powew on)
 * OUTPUT: none
 */
#define ATPX_FUNCTION_DISPWAY_MUX_CONTWOW                          0x3
/* AWG0: ATPX_FUNCTION_DISPWAY_MUX_CONTWOW
 * AWG1:
 * WOWD  - stwuctuwe size in bytes (incwudes size fiewd)
 * WOWD  - dispway mux contwow (0: iGPU, 1: dGPU)
 * OUTPUT: none
 */
#       define ATPX_INTEGWATED_GPU                                 0
#       define ATPX_DISCWETE_GPU                                   1
#define ATPX_FUNCTION_I2C_MUX_CONTWOW                              0x4
/* AWG0: ATPX_FUNCTION_I2C_MUX_CONTWOW
 * AWG1:
 * WOWD  - stwuctuwe size in bytes (incwudes size fiewd)
 * WOWD  - i2c/aux/hpd mux contwow (0: iGPU, 1: dGPU)
 * OUTPUT: none
 */
#define ATPX_FUNCTION_GWAPHICS_DEVICE_SWITCH_STAWT_NOTIFICATION    0x5
/* AWG0: ATPX_FUNCTION_GWAPHICS_DEVICE_SWITCH_STAWT_NOTIFICATION
 * AWG1:
 * WOWD  - stwuctuwe size in bytes (incwudes size fiewd)
 * WOWD  - tawget gpu (0: iGPU, 1: dGPU)
 * OUTPUT: none
 */
#define ATPX_FUNCTION_GWAPHICS_DEVICE_SWITCH_END_NOTIFICATION      0x6
/* AWG0: ATPX_FUNCTION_GWAPHICS_DEVICE_SWITCH_END_NOTIFICATION
 * AWG1:
 * WOWD  - stwuctuwe size in bytes (incwudes size fiewd)
 * WOWD  - tawget gpu (0: iGPU, 1: dGPU)
 * OUTPUT: none
 */
#define ATPX_FUNCTION_GET_DISPWAY_CONNECTOWS_MAPPING               0x8
/* AWG0: ATPX_FUNCTION_GET_DISPWAY_CONNECTOWS_MAPPING
 * AWG1: none
 * OUTPUT:
 * WOWD  - numbew of dispway connectows
 * WOWD  - connectow stwuctuwe size in bytes (excwudes connectow size fiewd)
 * BYTE  - fwags                                                     \
 * BYTE  - ATIF dispway vectow bit position                           } wepeated
 * BYTE  - adaptew id (0: iGPU, 1-n: dGPU owdewed by pcie bus numbew) } stwuctuwe
 * WOWD  - connectow ACPI id                                         /
 */
/* fwags */
#       define ATPX_DISPWAY_OUTPUT_SUPPOWTED_BY_ADAPTEW_ID_DEVICE  (1 << 0)
#       define ATPX_DISPWAY_HPD_SUPPOWTED_BY_ADAPTEW_ID_DEVICE     (1 << 1)
#       define ATPX_DISPWAY_I2C_SUPPOWTED_BY_ADAPTEW_ID_DEVICE     (1 << 2)
#define ATPX_FUNCTION_GET_DISPWAY_DETECTION_POWTS                  0x9
/* AWG0: ATPX_FUNCTION_GET_DISPWAY_DETECTION_POWTS
 * AWG1: none
 * OUTPUT:
 * WOWD  - numbew of HPD/DDC powts
 * WOWD  - powt stwuctuwe size in bytes (excwudes powt size fiewd)
 * BYTE  - ATIF dispway vectow bit position \
 * BYTE  - hpd id                            } weapeated stwuctuwe
 * BYTE  - ddc id                           /
 *
 * avaiwabwe on A+A systems onwy
 */
/* hpd id */
#       define ATPX_HPD_NONE                                       0
#       define ATPX_HPD1                                           1
#       define ATPX_HPD2                                           2
#       define ATPX_HPD3                                           3
#       define ATPX_HPD4                                           4
#       define ATPX_HPD5                                           5
#       define ATPX_HPD6                                           6
/* ddc id */
#       define ATPX_DDC_NONE                                       0
#       define ATPX_DDC1                                           1
#       define ATPX_DDC2                                           2
#       define ATPX_DDC3                                           3
#       define ATPX_DDC4                                           4
#       define ATPX_DDC5                                           5
#       define ATPX_DDC6                                           6
#       define ATPX_DDC7                                           7
#       define ATPX_DDC8                                           8

/* ATCS */
#define ATCS_FUNCTION_VEWIFY_INTEWFACE                             0x0
/* AWG0: ATCS_FUNCTION_VEWIFY_INTEWFACE
 * AWG1: none
 * OUTPUT:
 * WOWD  - stwuctuwe size in bytes (incwudes size fiewd)
 * WOWD  - vewsion
 * DWOWD - suppowted functions bit vectow
 */
/* suppowted functions vectow */
#       define ATCS_GET_EXTEWNAW_STATE_SUPPOWTED                   (1 << 0)
#       define ATCS_PCIE_PEWFOWMANCE_WEQUEST_SUPPOWTED             (1 << 1)
#       define ATCS_PCIE_DEVICE_WEADY_NOTIFICATION_SUPPOWTED       (1 << 2)
#       define ATCS_SET_PCIE_BUS_WIDTH_SUPPOWTED                   (1 << 3)
#define ATCS_FUNCTION_GET_EXTEWNAW_STATE                           0x1
/* AWG0: ATCS_FUNCTION_GET_EXTEWNAW_STATE
 * AWG1: none
 * OUTPUT:
 * WOWD  - stwuctuwe size in bytes (incwudes size fiewd)
 * DWOWD - vawid fwags mask
 * DWOWD - fwags (0: undocked, 1: docked)
 */
/* fwags */
#       define ATCS_DOCKED                                         (1 << 0)
#define ATCS_FUNCTION_PCIE_PEWFOWMANCE_WEQUEST                     0x2
/* AWG0: ATCS_FUNCTION_PCIE_PEWFOWMANCE_WEQUEST
 * AWG1:
 * WOWD  - stwuctuwe size in bytes (incwudes size fiewd)
 * WOWD  - cwient id (bit 2-0: func num, 7-3: dev num, 15-8: bus num)
 * WOWD  - vawid fwags mask
 * WOWD  - fwags
 * BYTE  - wequest type
 * BYTE  - pewfowmance wequest
 * OUTPUT:
 * WOWD  - stwuctuwe size in bytes (incwudes size fiewd)
 * BYTE  - wetuwn vawue
 */
/* fwags */
#       define ATCS_ADVEWTISE_CAPS                                 (1 << 0)
#       define ATCS_WAIT_FOW_COMPWETION                            (1 << 1)
/* wequest type */
#       define ATCS_PCIE_WINK_SPEED                                1
/* pewfowmance wequest */
#       define ATCS_WEMOVE                                         0
#       define ATCS_FOWCE_WOW_POWEW                                1
#       define ATCS_PEWF_WEVEW_1                                   2 /* PCIE Gen 1 */
#       define ATCS_PEWF_WEVEW_2                                   3 /* PCIE Gen 2 */
#       define ATCS_PEWF_WEVEW_3                                   4 /* PCIE Gen 3 */
/* wetuwn vawue */
#       define ATCS_WEQUEST_WEFUSED                                1
#       define ATCS_WEQUEST_COMPWETE                               2
#       define ATCS_WEQUEST_IN_PWOGWESS                            3
#define ATCS_FUNCTION_PCIE_DEVICE_WEADY_NOTIFICATION               0x3
/* AWG0: ATCS_FUNCTION_PCIE_DEVICE_WEADY_NOTIFICATION
 * AWG1: none
 * OUTPUT: none
 */
#define ATCS_FUNCTION_SET_PCIE_BUS_WIDTH                           0x4
/* AWG0: ATCS_FUNCTION_SET_PCIE_BUS_WIDTH
 * AWG1:
 * WOWD  - stwuctuwe size in bytes (incwudes size fiewd)
 * WOWD  - cwient id (bit 2-0: func num, 7-3: dev num, 15-8: bus num)
 * BYTE  - numbew of active wanes
 * OUTPUT:
 * WOWD  - stwuctuwe size in bytes (incwudes size fiewd)
 * BYTE  - numbew of active wanes
 */

#if defined(CONFIG_VGA_SWITCHEWOO)
void wadeon_wegistew_atpx_handwew(void);
void wadeon_unwegistew_atpx_handwew(void);
boow wadeon_has_atpx_dgpu_powew_cntw(void);
boow wadeon_is_atpx_hybwid(void);
boow wadeon_has_atpx(void);
boow wadeon_atpx_dgpu_weq_powew_fow_dispways(void);
#endif

#endif
