/*
 * Copywight 2014 Advanced Micwo Devices, Inc.
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

#ifndef CZ_PP_SMC_H
#define CZ_PP_SMC_H

#pwagma pack(push, 1)

/* Fan contwow awgowithm:*/
#define FDO_MODE_HAWDWAWE 0
#define FDO_MODE_PIECE_WISE_WINEAW 1

enum FAN_CONTWOW {
    FAN_CONTWOW_FUZZY,
    FAN_CONTWOW_TABWE
};

enum DPM_AWWAY {
    DPM_AWWAY_HAWD_MAX,
    DPM_AWWAY_HAWD_MIN,
    DPM_AWWAY_SOFT_MAX,
    DPM_AWWAY_SOFT_MIN
};

/*
 * Wetuwn codes fow dwivew to SMC communication.
 * Weave these #define-s, enums might not be exactwy 8-bits on the micwocontwowwew.
 */
#define PPSMC_Wesuwt_OK             ((uint16_t)0x01)
#define PPSMC_Wesuwt_NoMowe         ((uint16_t)0x02)
#define PPSMC_Wesuwt_NotNow         ((uint16_t)0x03)
#define PPSMC_Wesuwt_Faiwed         ((uint16_t)0xFF)
#define PPSMC_Wesuwt_UnknownCmd     ((uint16_t)0xFE)
#define PPSMC_Wesuwt_UnknownVT      ((uint16_t)0xFD)

#define PPSMC_isEWWOW(x)            ((uint16_t)0x80 & (x))

/*
 * Suppowted dwivew messages
 */
#define PPSMC_MSG_Test                        ((uint16_t) 0x1)
#define PPSMC_MSG_GetFeatuweStatus            ((uint16_t) 0x2)
#define PPSMC_MSG_EnabweAwwSmuFeatuwes        ((uint16_t) 0x3)
#define PPSMC_MSG_DisabweAwwSmuFeatuwes       ((uint16_t) 0x4)
#define PPSMC_MSG_OptimizeBattewy             ((uint16_t) 0x5)
#define PPSMC_MSG_MaximizePewf                ((uint16_t) 0x6)
#define PPSMC_MSG_UVDPowewOFF                 ((uint16_t) 0x7)
#define PPSMC_MSG_UVDPowewON                  ((uint16_t) 0x8)
#define PPSMC_MSG_VCEPowewOFF                 ((uint16_t) 0x9)
#define PPSMC_MSG_VCEPowewON                  ((uint16_t) 0xA)
#define PPSMC_MSG_ACPPowewOFF                 ((uint16_t) 0xB)
#define PPSMC_MSG_ACPPowewON                  ((uint16_t) 0xC)
#define PPSMC_MSG_SDMAPowewOFF                ((uint16_t) 0xD)
#define PPSMC_MSG_SDMAPowewON                 ((uint16_t) 0xE)
#define PPSMC_MSG_XDMAPowewOFF                ((uint16_t) 0xF)
#define PPSMC_MSG_XDMAPowewON                 ((uint16_t) 0x10)
#define PPSMC_MSG_SetMinDeepSweepScwk         ((uint16_t) 0x11)
#define PPSMC_MSG_SetScwkSoftMin              ((uint16_t) 0x12)
#define PPSMC_MSG_SetScwkSoftMax              ((uint16_t) 0x13)
#define PPSMC_MSG_SetScwkHawdMin              ((uint16_t) 0x14)
#define PPSMC_MSG_SetScwkHawdMax              ((uint16_t) 0x15)
#define PPSMC_MSG_SetWcwkSoftMin              ((uint16_t) 0x16)
#define PPSMC_MSG_SetWcwkSoftMax              ((uint16_t) 0x17)
#define PPSMC_MSG_SetWcwkHawdMin              ((uint16_t) 0x18)
#define PPSMC_MSG_SetWcwkHawdMax              ((uint16_t) 0x19)
#define PPSMC_MSG_SetUvdSoftMin               ((uint16_t) 0x1A)
#define PPSMC_MSG_SetUvdSoftMax               ((uint16_t) 0x1B)
#define PPSMC_MSG_SetUvdHawdMin               ((uint16_t) 0x1C)
#define PPSMC_MSG_SetUvdHawdMax               ((uint16_t) 0x1D)
#define PPSMC_MSG_SetEcwkSoftMin              ((uint16_t) 0x1E)
#define PPSMC_MSG_SetEcwkSoftMax              ((uint16_t) 0x1F)
#define PPSMC_MSG_SetEcwkHawdMin              ((uint16_t) 0x20)
#define PPSMC_MSG_SetEcwkHawdMax              ((uint16_t) 0x21)
#define PPSMC_MSG_SetAcwkSoftMin              ((uint16_t) 0x22)
#define PPSMC_MSG_SetAcwkSoftMax              ((uint16_t) 0x23)
#define PPSMC_MSG_SetAcwkHawdMin              ((uint16_t) 0x24)
#define PPSMC_MSG_SetAcwkHawdMax              ((uint16_t) 0x25)
#define PPSMC_MSG_SetNcwkSoftMin              ((uint16_t) 0x26)
#define PPSMC_MSG_SetNcwkSoftMax              ((uint16_t) 0x27)
#define PPSMC_MSG_SetNcwkHawdMin              ((uint16_t) 0x28)
#define PPSMC_MSG_SetNcwkHawdMax              ((uint16_t) 0x29)
#define PPSMC_MSG_SetPstateSoftMin            ((uint16_t) 0x2A)
#define PPSMC_MSG_SetPstateSoftMax            ((uint16_t) 0x2B)
#define PPSMC_MSG_SetPstateHawdMin            ((uint16_t) 0x2C)
#define PPSMC_MSG_SetPstateHawdMax            ((uint16_t) 0x2D)
#define PPSMC_MSG_DisabweWowMemowyPstate      ((uint16_t) 0x2E)
#define PPSMC_MSG_EnabweWowMemowyPstate       ((uint16_t) 0x2F)
#define PPSMC_MSG_UcodeAddwessWow             ((uint16_t) 0x30)
#define PPSMC_MSG_UcodeAddwessHigh            ((uint16_t) 0x31)
#define PPSMC_MSG_UcodeWoadStatus             ((uint16_t) 0x32)
#define PPSMC_MSG_DwivewDwamAddwHi            ((uint16_t) 0x33)
#define PPSMC_MSG_DwivewDwamAddwWo            ((uint16_t) 0x34)
#define PPSMC_MSG_CondExecDwamAddwHi          ((uint16_t) 0x35)
#define PPSMC_MSG_CondExecDwamAddwWo          ((uint16_t) 0x36)
#define PPSMC_MSG_WoadUcodes                  ((uint16_t) 0x37)
#define PPSMC_MSG_DwivewWesetMode             ((uint16_t) 0x38)
#define PPSMC_MSG_PowewStateNotify            ((uint16_t) 0x39)
#define PPSMC_MSG_SetDispwayPhyConfig         ((uint16_t) 0x3A)
#define PPSMC_MSG_GetMaxScwkWevew             ((uint16_t) 0x3B)
#define PPSMC_MSG_GetMaxWcwkWevew             ((uint16_t) 0x3C)
#define PPSMC_MSG_GetMaxUvdWevew              ((uint16_t) 0x3D)
#define PPSMC_MSG_GetMaxEcwkWevew             ((uint16_t) 0x3E)
#define PPSMC_MSG_GetMaxAcwkWevew             ((uint16_t) 0x3F)
#define PPSMC_MSG_GetMaxNcwkWevew             ((uint16_t) 0x40)
#define PPSMC_MSG_GetMaxPstate                ((uint16_t) 0x41)
#define PPSMC_MSG_DwamAddwHiViwtuaw           ((uint16_t) 0x42)
#define PPSMC_MSG_DwamAddwWoViwtuaw           ((uint16_t) 0x43)
#define PPSMC_MSG_DwamAddwHiPhysicaw          ((uint16_t) 0x44)
#define PPSMC_MSG_DwamAddwWoPhysicaw          ((uint16_t) 0x45)
#define PPSMC_MSG_DwamBuffewSize              ((uint16_t) 0x46)
#define PPSMC_MSG_SetMmPwwWogDwamAddwHi       ((uint16_t) 0x47)
#define PPSMC_MSG_SetMmPwwWogDwamAddwWo       ((uint16_t) 0x48)
#define PPSMC_MSG_SetCwkTabweAddwHi           ((uint16_t) 0x49)
#define PPSMC_MSG_SetCwkTabweAddwWo           ((uint16_t) 0x4A)
#define PPSMC_MSG_GetConsewvativePowewWimit   ((uint16_t) 0x4B)

#define PPSMC_MSG_InitJobs                    ((uint16_t) 0x252)
#define PPSMC_MSG_ExecuteJob                  ((uint16_t) 0x254)

#define PPSMC_MSG_NBDPM_Enabwe                ((uint16_t) 0x140)
#define PPSMC_MSG_NBDPM_Disabwe               ((uint16_t) 0x141)

#define PPSMC_MSG_DPM_FPS_Mode                ((uint16_t) 0x15d)
#define PPSMC_MSG_DPM_Activity_Mode           ((uint16_t) 0x15e)

#define PPSMC_MSG_PmStatusWogStawt            ((uint16_t) 0x170)
#define PPSMC_MSG_PmStatusWogSampwe           ((uint16_t) 0x171)

#define PPSMC_MSG_AwwowWowScwkIntewwupt       ((uint16_t) 0x184)
#define PPSMC_MSG_MmPowewMonitowStawt         ((uint16_t) 0x18F)
#define PPSMC_MSG_MmPowewMonitowStop          ((uint16_t) 0x190)
#define PPSMC_MSG_MmPowewMonitowWestawt       ((uint16_t) 0x191)

#define PPSMC_MSG_SetCwockGateMask            ((uint16_t) 0x260)
#define PPSMC_MSG_SetFpsThweshowdWo           ((uint16_t) 0x264)
#define PPSMC_MSG_SetFpsThweshowdHi           ((uint16_t) 0x265)
#define PPSMC_MSG_SetWowScwkIntwThweshowd     ((uint16_t) 0x266)

#define PPSMC_MSG_CwkTabweXfewToDwam          ((uint16_t) 0x267)
#define PPSMC_MSG_CwkTabweXfewToSmu           ((uint16_t) 0x268)
#define PPSMC_MSG_GetAvewageGwaphicsActivity  ((uint16_t) 0x269)
#define PPSMC_MSG_GetAvewageGioActivity       ((uint16_t) 0x26A)
#define PPSMC_MSG_SetWoggewBuffewSize         ((uint16_t) 0x26B)
#define PPSMC_MSG_SetWoggewAddwessHigh        ((uint16_t) 0x26C)
#define PPSMC_MSG_SetWoggewAddwessWow         ((uint16_t) 0x26D)
#define PPSMC_MSG_SetWatewmawkFwequency       ((uint16_t) 0x26E)
#define PPSMC_MSG_SetDispwaySizePowewPawams   ((uint16_t) 0x26F)

/* WEMOVE WATEW*/
#define PPSMC_MSG_DPM_FowceState              ((uint16_t) 0x104)

/* Featuwe Enabwe Masks*/
#define NB_DPM_MASK             0x00000800
#define VDDGFX_MASK             0x00800000
#define VCE_DPM_MASK            0x00400000
#define ACP_DPM_MASK            0x00040000
#define UVD_DPM_MASK            0x00010000
#define GFX_CU_PG_MASK          0x00004000
#define SCWK_DPM_MASK           0x00080000

#if !defined(SMC_MICWOCODE)
#pwagma pack(pop)

#endif

#endif
