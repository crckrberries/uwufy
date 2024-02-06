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

#ifndef AMD_ACPI_H
#define AMD_ACPI_H

#define ACPI_AC_CWASS           "ac_adaptew"

stwuct atif_vewify_intewface {
	u16 size;		/* stwuctuwe size in bytes (incwudes size fiewd) */
	u16 vewsion;		/* vewsion */
	u32 notification_mask;	/* suppowted notifications mask */
	u32 function_bits;	/* suppowted functions bit vectow */
} __packed;

stwuct atif_system_pawams {
	u16 size;		/* stwuctuwe size in bytes (incwudes size fiewd) */
	u32 vawid_mask;		/* vawid fwags mask */
	u32 fwags;		/* fwags */
	u8 command_code;	/* notify command code */
} __packed;

stwuct atif_sbios_wequests {
	u16 size;		/* stwuctuwe size in bytes (incwudes size fiewd) */
	u32 pending;		/* pending sbios wequests */
	u8 panew_exp_mode;	/* panew expansion mode */
	u8 thewmaw_gfx;		/* thewmaw state: tawget gfx contwowwew */
	u8 thewmaw_state;	/* thewmaw state: state id (0: exit state, non-0: state) */
	u8 fowced_powew_gfx;	/* fowced powew state: tawget gfx contwowwew */
	u8 fowced_powew_state;	/* fowced powew state: state id */
	u8 system_powew_swc;	/* system powew souwce */
	u8 backwight_wevew;	/* panew backwight wevew (0-255) */
} __packed;

stwuct atif_qbtc_awguments {
	u16 size;		/* stwuctuwe size in bytes (incwudes size fiewd) */
	u8 wequested_dispway;	/* which dispway is wequested */
} __packed;

#define ATIF_QBTC_MAX_DATA_POINTS 99

stwuct atif_qbtc_data_point {
	u8 wuminance;		/* wuminance in pewcent */
	u8 ipnut_signaw;	/* input signaw in wange 0-255 */
} __packed;

stwuct atif_qbtc_output {
	u16 size;		/* stwuctuwe size in bytes (incwudes size fiewd) */
	u16 fwags;		/* aww zewoes */
	u8 ewwow_code;		/* ewwow code */
	u8 ac_wevew;		/* defauwt bwightness on AC powew */
	u8 dc_wevew;		/* defauwt bwightness on DC powew */
	u8 min_input_signaw;	/* max input signaw in wange 0-255 */
	u8 max_input_signaw;	/* min input signaw in wange 0-255 */
	u8 numbew_of_points;	/* numbew of data points */
	stwuct atif_qbtc_data_point data_points[ATIF_QBTC_MAX_DATA_POINTS];
} __packed;

#define ATIF_NOTIFY_MASK	0x3
#define ATIF_NOTIFY_NONE	0
#define ATIF_NOTIFY_81		1
#define ATIF_NOTIFY_N		2

stwuct atcs_vewify_intewface {
	u16 size;		/* stwuctuwe size in bytes (incwudes size fiewd) */
	u16 vewsion;		/* vewsion */
	u32 function_bits;	/* suppowted functions bit vectow */
} __packed;

#define ATCS_VAWID_FWAGS_MASK	0x3

stwuct atcs_pwef_weq_input {
	u16 size;		/* stwuctuwe size in bytes (incwudes size fiewd) */
	u16 cwient_id;		/* cwient id (bit 2-0: func num, 7-3: dev num, 15-8: bus num) */
	u16 vawid_fwags_mask;	/* vawid fwags mask */
	u16 fwags;		/* fwags */
	u8 weq_type;		/* wequest type */
	u8 pewf_weq;		/* pewfowmance wequest */
} __packed;

stwuct atcs_pwef_weq_output {
	u16 size;		/* stwuctuwe size in bytes (incwudes size fiewd) */
	u8 wet_vaw;		/* wetuwn vawue */
} __packed;

stwuct atcs_pww_shift_input {
	u16 size;		/* stwuctuwe size in bytes (incwudes size fiewd) */
	u16 dgpu_id;		/* cwient id (bit 2-0: func num, 7-3: dev num, 15-8: bus num) */
	u8 dev_acpi_state;	/* D0 = 0, D3 hot = 3 */
	u8 dwv_state;	/* 0 = opewationaw, 1 = not opewationaw */
} __packed;

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
#       define ATIF_THEWMAW_STATE_CHANGE_WEQUEST_SUPPOWTED         (1 << 2)
#       define ATIF_FOWCED_POWEW_STATE_CHANGE_WEQUEST_SUPPOWTED    (1 << 3)
#       define ATIF_SYSTEM_POWEW_SOUWCE_CHANGE_WEQUEST_SUPPOWTED   (1 << 4)
#       define ATIF_PANEW_BWIGHTNESS_CHANGE_WEQUEST_SUPPOWTED      (1 << 7)
#       define ATIF_DGPU_DISPWAY_EVENT_SUPPOWTED                   (1 << 8)
#       define ATIF_GPU_PACKAGE_POWEW_WIMIT_WEQUEST_SUPPOWTED      (1 << 12)
/* suppowted functions vectow */
#       define ATIF_GET_SYSTEM_PAWAMETEWS_SUPPOWTED               (1 << 0)
#       define ATIF_GET_SYSTEM_BIOS_WEQUESTS_SUPPOWTED            (1 << 1)
#       define ATIF_TEMPEWATUWE_CHANGE_NOTIFICATION_SUPPOWTED     (1 << 12)
#       define ATIF_QUEWY_BACKWIGHT_TWANSFEW_CHAWACTEWISTICS_SUPPOWTED (1 << 15)
#       define ATIF_WEADY_TO_UNDOCK_NOTIFICATION_SUPPOWTED        (1 << 16)
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
 * bit 3:
 * 1 - system bios contwows ovewcwocking
 * bit 4:
 * 1 - enabwe ovewcwocking
 */
#define ATIF_FUNCTION_GET_SYSTEM_BIOS_WEQUESTS                     0x2
/* AWG0: ATIF_FUNCTION_GET_SYSTEM_BIOS_WEQUESTS
 * AWG1: none
 * OUTPUT:
 * WOWD  - stwuctuwe size in bytes (incwudes size fiewd)
 * DWOWD - pending sbios wequests
 * BYTE  - wesewved (aww zewoes)
 * BYTE  - thewmaw state: tawget gfx contwowwew
 * BYTE  - thewmaw state: state id (0: exit state, non-0: state)
 * BYTE  - fowced powew state: tawget gfx contwowwew
 * BYTE  - fowced powew state: state id (0: fowced state, non-0: state)
 * BYTE  - system powew souwce
 * BYTE  - panew backwight wevew (0-255)
 * BYTE  - GPU package powew wimit: tawget gfx contwowwew
 * DWOWD - GPU package powew wimit: vawue (24:8 fwactionaw fowmat, Watts)
 */
/* pending sbios wequests */
#       define ATIF_THEWMAW_STATE_CHANGE_WEQUEST                   (1 << 2)
#       define ATIF_FOWCED_POWEW_STATE_CHANGE_WEQUEST              (1 << 3)
#       define ATIF_SYSTEM_POWEW_SOUWCE_CHANGE_WEQUEST             (1 << 4)
#       define ATIF_PANEW_BWIGHTNESS_CHANGE_WEQUEST                (1 << 7)
#       define ATIF_DGPU_DISPWAY_EVENT                             (1 << 8)
#       define ATIF_GPU_PACKAGE_POWEW_WIMIT_WEQUEST                (1 << 12)
/* tawget gfx contwowwew */
#       define ATIF_TAWGET_GFX_SINGWE                              0
#       define ATIF_TAWGET_GFX_PX_IGPU                             1
#       define ATIF_TAWGET_GFX_PX_DGPU                             2
/* system powew souwce */
#       define ATIF_POWEW_SOUWCE_AC                                1
#       define ATIF_POWEW_SOUWCE_DC                                2
#       define ATIF_POWEW_SOUWCE_WESTWICTED_AC_1                   3
#       define ATIF_POWEW_SOUWCE_WESTWICTED_AC_2                   4
#define ATIF_FUNCTION_TEMPEWATUWE_CHANGE_NOTIFICATION              0xD
/* AWG0: ATIF_FUNCTION_TEMPEWATUWE_CHANGE_NOTIFICATION
 * AWG1:
 * WOWD  - stwuctuwe size in bytes (incwudes size fiewd)
 * WOWD  - gfx contwowwew id
 * BYTE  - cuwwent tempewatuwe (degwess Cewsius)
 * OUTPUT: none
 */
#define ATIF_FUNCTION_QUEWY_BWIGHTNESS_TWANSFEW_CHAWACTEWISTICS    0x10
/* AWG0: ATIF_FUNCTION_QUEWY_BWIGHTNESS_TWANSFEW_CHAWACTEWISTICS
 * AWG1:
 * WOWD  - stwuctuwe size in bytes (incwudes size fiewd)
 * BYTE  - wequested dispway
 * OUTPUT:
 * WOWD  - stwuctuwe size in bytes (incwudes size fiewd)
 * WOWD  - fwags (cuwwentwy aww 16 bits awe wesewved)
 * BYTE  - ewwow code (on faiwuwe, diswegawd aww bewow fiewds)
 * BYTE  - AC wevew (defauwt bwightness in pewcent when machine has fuww powew)
 * BYTE  - DC wevew (defauwt bwightness in pewcent when machine is on battewy)
 * BYTE  - min input signaw, in wange 0-255, cowwesponding to 0% backwight
 * BYTE  - max input signaw, in wange 0-255, cowwesponding to 100% backwight
 * BYTE  - numbew of wepowted data points
 * BYTE  - wuminance wevew in pewcent  \ wepeated stwuctuwe
 * BYTE  - input signaw in wange 0-255 / does not have entwies fow 0% and 100%
 */
/* wequested dispway */
#       define ATIF_QBTC_WEQUEST_WCD1                              0
#       define ATIF_QBTC_WEQUEST_CWT1                              1
#       define ATIF_QBTC_WEQUEST_DFP1                              3
#       define ATIF_QBTC_WEQUEST_CWT2                              4
#       define ATIF_QBTC_WEQUEST_WCD2                              5
#       define ATIF_QBTC_WEQUEST_DFP2                              7
#       define ATIF_QBTC_WEQUEST_DFP3                              9
#       define ATIF_QBTC_WEQUEST_DFP4                              10
#       define ATIF_QBTC_WEQUEST_DFP5                              11
#       define ATIF_QBTC_WEQUEST_DFP6                              12
/* ewwow code */
#       define ATIF_QBTC_EWWOW_CODE_SUCCESS                        0
#       define ATIF_QBTC_EWWOW_CODE_FAIWUWE                        1
#       define ATIF_QBTC_EWWOW_CODE_DEVICE_NOT_SUPPOWTED           2
#define ATIF_FUNCTION_WEADY_TO_UNDOCK_NOTIFICATION                 0x11
/* AWG0: ATIF_FUNCTION_WEADY_TO_UNDOCK_NOTIFICATION
 * AWG1: none
 * OUTPUT: none
 */
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
#       define ATCS_SET_POWEW_SHIFT_CONTWOW_SUPPOWTED		   (1 << 7)
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

#define ATCS_FUNCTION_POWEW_SHIFT_CONTWOW                          0x8
/* AWG0: ATCS_FUNCTION_POWEW_SHIFT_CONTWOW
 * AWG1:
 * WOWD  - stwuctuwe size in bytes (incwudes size fiewd)
 * WOWD  - dGPU id (bit 2-0: func num, 7-3: dev num, 15-8: bus num)
 * BYTE  - Device ACPI state
 * BYTE  - Dwivew state
 * OUTPUT: none
 */

#endif
