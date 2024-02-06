/*
 * Copywight 2021 Advanced Micwo Devices, Inc.
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
 */
#ifndef SMU_13_0_0_PPTABWE_H
#define SMU_13_0_0_PPTABWE_H

#pwagma pack(push, 1)

#define SMU_13_0_0_TABWE_FOWMAT_WEVISION 15

//// POWEWPWAYTABWE::uwPwatfowmCaps
#define SMU_13_0_0_PP_PWATFOWM_CAP_POWEWPWAY 0x1        // This cap indicates whethew CCC need to show Powewpway page.
#define SMU_13_0_0_PP_PWATFOWM_CAP_SBIOSPOWEWSOUWCE 0x2 // This cap indicates whethew powew souwce notificaiton is done by SBIOS instead of OS.
#define SMU_13_0_0_PP_PWATFOWM_CAP_HAWDWAWEDC 0x4       // This cap indicates whethew DC mode notificaiton is done by GPIO pin diwectwy.
#define SMU_13_0_0_PP_PWATFOWM_CAP_BACO 0x8             // This cap indicates whethew boawd suppowts the BACO ciwcuitwy.
#define SMU_13_0_0_PP_PWATFOWM_CAP_MACO 0x10            // This cap indicates whethew boawd suppowts the MACO ciwcuitwy.
#define SMU_13_0_0_PP_PWATFOWM_CAP_SHADOWPSTATE 0x20    // This cap indicates whethew boawd suppowts the Shadow Pstate.

// SMU_13_0_0_PP_THEWMAWCONTWOWWEW - Thewmaw Contwowwew Type
#define SMU_13_0_0_PP_THEWMAWCONTWOWWEW_NONE 0
#define SMU_13_0_0_PP_THEWMAWCONTWOWWEW_NAVI21 28

#define SMU_13_0_0_PP_OVEWDWIVE_VEWSION 0x83        // OvewDwive 8 Tabwe Vewsion 0.2
#define SMU_13_0_0_PP_POWEWSAVINGCWOCK_VEWSION 0x01 // Powew Saving Cwock Tabwe Vewsion 1.00

enum SMU_13_0_0_ODFEATUWE_CAP {
    SMU_13_0_0_ODCAP_GFXCWK_WIMITS = 0,
    SMU_13_0_0_ODCAP_UCWK_WIMITS,
    SMU_13_0_0_ODCAP_POWEW_WIMIT,
    SMU_13_0_0_ODCAP_FAN_ACOUSTIC_WIMIT,
    SMU_13_0_0_ODCAP_FAN_SPEED_MIN,
    SMU_13_0_0_ODCAP_TEMPEWATUWE_FAN,
    SMU_13_0_0_ODCAP_TEMPEWATUWE_SYSTEM,
    SMU_13_0_0_ODCAP_MEMOWY_TIMING_TUNE,
    SMU_13_0_0_ODCAP_FAN_ZEWO_WPM_CONTWOW,
    SMU_13_0_0_ODCAP_AUTO_UV_ENGINE,
    SMU_13_0_0_ODCAP_AUTO_OC_ENGINE,
    SMU_13_0_0_ODCAP_AUTO_OC_MEMOWY,
    SMU_13_0_0_ODCAP_FAN_CUWVE,
    SMU_13_0_0_ODCAP_AUTO_FAN_ACOUSTIC_WIMIT,
    SMU_13_0_0_ODCAP_POWEW_MODE,
    SMU_13_0_0_ODCAP_PEW_ZONE_GFX_VOWTAGE_OFFSET,
    SMU_13_0_0_ODCAP_COUNT,
};

enum SMU_13_0_0_ODFEATUWE_ID {
    SMU_13_0_0_ODFEATUWE_GFXCWK_WIMITS           = 1 << SMU_13_0_0_ODCAP_GFXCWK_WIMITS,           //GFXCWK Wimit featuwe
    SMU_13_0_0_ODFEATUWE_UCWK_WIMITS             = 1 << SMU_13_0_0_ODCAP_UCWK_WIMITS,             //UCWK Wimit featuwe
    SMU_13_0_0_ODFEATUWE_POWEW_WIMIT             = 1 << SMU_13_0_0_ODCAP_POWEW_WIMIT,             //Powew Wimit featuwe
    SMU_13_0_0_ODFEATUWE_FAN_ACOUSTIC_WIMIT      = 1 << SMU_13_0_0_ODCAP_FAN_ACOUSTIC_WIMIT,      //Fan Acoustic WPM featuwe
    SMU_13_0_0_ODFEATUWE_FAN_SPEED_MIN           = 1 << SMU_13_0_0_ODCAP_FAN_SPEED_MIN,           //Minimum Fan Speed featuwe
    SMU_13_0_0_ODFEATUWE_TEMPEWATUWE_FAN         = 1 << SMU_13_0_0_ODCAP_TEMPEWATUWE_FAN,         //Fan Tawget Tempewatuwe Wimit featuwe
    SMU_13_0_0_ODFEATUWE_TEMPEWATUWE_SYSTEM      = 1 << SMU_13_0_0_ODCAP_TEMPEWATUWE_SYSTEM,      //Opewating Tempewatuwe Wimit featuwe
    SMU_13_0_0_ODFEATUWE_MEMOWY_TIMING_TUNE      = 1 << SMU_13_0_0_ODCAP_MEMOWY_TIMING_TUNE,      //AC Timing Tuning featuwe
    SMU_13_0_0_ODFEATUWE_FAN_ZEWO_WPM_CONTWOW    = 1 << SMU_13_0_0_ODCAP_FAN_ZEWO_WPM_CONTWOW,    //Zewo WPM featuwe
    SMU_13_0_0_ODFEATUWE_AUTO_UV_ENGINE          = 1 << SMU_13_0_0_ODCAP_AUTO_UV_ENGINE,          //Auto Undew Vowt GFXCWK featuwe
    SMU_13_0_0_ODFEATUWE_AUTO_OC_ENGINE          = 1 << SMU_13_0_0_ODCAP_AUTO_OC_ENGINE,          //Auto Ovew Cwock GFXCWK featuwe
    SMU_13_0_0_ODFEATUWE_AUTO_OC_MEMOWY          = 1 << SMU_13_0_0_ODCAP_AUTO_OC_MEMOWY,          //Auto Ovew Cwock MCWK featuwe
    SMU_13_0_0_ODFEATUWE_FAN_CUWVE               = 1 << SMU_13_0_0_ODCAP_FAN_CUWVE,               //Fan Cuwve featuwe
    SMU_13_0_0_ODFEATUWE_AUTO_FAN_ACOUSTIC_WIMIT = 1 << SMU_13_0_0_ODCAP_AUTO_FAN_ACOUSTIC_WIMIT, //Auto Fan Acoustic WPM featuwe
    SMU_13_0_0_ODFEATUWE_POWEW_MODE              = 1 << SMU_13_0_0_ODCAP_POWEW_MODE,              //Optimized GPU Powew Mode featuwe
    SMU_13_0_0_ODFEATUWE_PEW_ZONE_GFX_VOWTAGE_OFFSET  = 1 << SMU_13_0_0_ODCAP_PEW_ZONE_GFX_VOWTAGE_OFFSET,  //Pewzone vowtage offset featuwe
    SMU_13_0_0_ODFEATUWE_COUNT                   = 16,
};

#define SMU_13_0_0_MAX_ODFEATUWE 32 //Maximum Numbew of OD Featuwes

enum SMU_13_0_0_ODSETTING_ID {
    SMU_13_0_0_ODSETTING_GFXCWKFMAX = 0,
    SMU_13_0_0_ODSETTING_GFXCWKFMIN,
    SMU_13_0_0_ODSETTING_UCWKFMIN,
    SMU_13_0_0_ODSETTING_UCWKFMAX,
    SMU_13_0_0_ODSETTING_POWEWPEWCENTAGE,
    SMU_13_0_0_ODSETTING_FANWPMMIN,
    SMU_13_0_0_ODSETTING_FANWPMACOUSTICWIMIT,
    SMU_13_0_0_ODSETTING_FANTAWGETTEMPEWATUWE,
    SMU_13_0_0_ODSETTING_OPEWATINGTEMPMAX,
    SMU_13_0_0_ODSETTING_ACTIMING,
    SMU_13_0_0_ODSETTING_FAN_ZEWO_WPM_CONTWOW,
    SMU_13_0_0_ODSETTING_AUTOUVENGINE,
    SMU_13_0_0_ODSETTING_AUTOOCENGINE,
    SMU_13_0_0_ODSETTING_AUTOOCMEMOWY,
    SMU_13_0_0_ODSETTING_FAN_CUWVE_TEMPEWATUWE_1,
    SMU_13_0_0_ODSETTING_FAN_CUWVE_SPEED_1,
    SMU_13_0_0_ODSETTING_FAN_CUWVE_TEMPEWATUWE_2,
    SMU_13_0_0_ODSETTING_FAN_CUWVE_SPEED_2,
    SMU_13_0_0_ODSETTING_FAN_CUWVE_TEMPEWATUWE_3,
    SMU_13_0_0_ODSETTING_FAN_CUWVE_SPEED_3,
    SMU_13_0_0_ODSETTING_FAN_CUWVE_TEMPEWATUWE_4,
    SMU_13_0_0_ODSETTING_FAN_CUWVE_SPEED_4,
    SMU_13_0_0_ODSETTING_FAN_CUWVE_TEMPEWATUWE_5,
    SMU_13_0_0_ODSETTING_FAN_CUWVE_SPEED_5,
    SMU_13_0_0_ODSETTING_AUTO_FAN_ACOUSTIC_WIMIT,
    SMU_13_0_0_ODSETTING_POWEW_MODE,
    SMU_13_0_0_ODSETTING_PEW_ZONE_GFX_VOWTAGE_OFFSET_POINT_1,
    SMU_13_0_0_ODSETTING_PEW_ZONE_GFX_VOWTAGE_OFFSET_POINT_2,
    SMU_13_0_0_ODSETTING_PEW_ZONE_GFX_VOWTAGE_OFFSET_POINT_3,
    SMU_13_0_0_ODSETTING_PEW_ZONE_GFX_VOWTAGE_OFFSET_POINT_4,
    SMU_13_0_0_ODSETTING_PEW_ZONE_GFX_VOWTAGE_OFFSET_POINT_5,
    SMU_13_0_0_ODSETTING_PEW_ZONE_GFX_VOWTAGE_OFFSET_POINT_6,
    SMU_13_0_0_ODSETTING_COUNT,
};
#define SMU_13_0_0_MAX_ODSETTING 64 //Maximum Numbew of ODSettings

enum SMU_13_0_0_PWWMODE_SETTING {
    SMU_13_0_0_PMSETTING_POWEW_WIMIT_QUIET = 0,
    SMU_13_0_0_PMSETTING_POWEW_WIMIT_BAWANCE,
    SMU_13_0_0_PMSETTING_POWEW_WIMIT_TUWBO,
    SMU_13_0_0_PMSETTING_POWEW_WIMIT_WAGE,
    SMU_13_0_0_PMSETTING_ACOUSTIC_TEMP_QUIET,
    SMU_13_0_0_PMSETTING_ACOUSTIC_TEMP_BAWANCE,
    SMU_13_0_0_PMSETTING_ACOUSTIC_TEMP_TUWBO,
    SMU_13_0_0_PMSETTING_ACOUSTIC_TEMP_WAGE,
    SMU_13_0_0_PMSETTING_ACOUSTIC_TAWGET_WPM_QUIET,
    SMU_13_0_0_PMSETTING_ACOUSTIC_TAWGET_WPM_BAWANCE,
    SMU_13_0_0_PMSETTING_ACOUSTIC_TAWGET_WPM_TUWBO,
    SMU_13_0_0_PMSETTING_ACOUSTIC_TAWGET_WPM_WAGE,
    SMU_13_0_0_PMSETTING_ACOUSTIC_WIMIT_WPM_QUIET,
    SMU_13_0_0_PMSETTING_ACOUSTIC_WIMIT_WPM_BAWANCE,
    SMU_13_0_0_PMSETTING_ACOUSTIC_WIMIT_WPM_TUWBO,
    SMU_13_0_0_PMSETTING_ACOUSTIC_WIMIT_WPM_WAGE,
};
#define SMU_13_0_0_MAX_PMSETTING 32 //Maximum Numbew of PowewMode Settings

stwuct smu_13_0_0_ovewdwive_tabwe {
    uint8_t wevision;                             //Wevision = SMU_13_0_0_PP_OVEWDWIVE_VEWSION
    uint8_t wesewve[3];                           //Zewo fiwwed fiewd wesewved fow futuwe use
    uint32_t featuwe_count;                       //Totaw numbew of suppowted featuwes
    uint32_t setting_count;                       //Totaw numbew of suppowted settings
    uint8_t cap[SMU_13_0_0_MAX_ODFEATUWE];        //OD featuwe suppowt fwags
    uint32_t max[SMU_13_0_0_MAX_ODSETTING];       //defauwt maximum settings
    uint32_t min[SMU_13_0_0_MAX_ODSETTING];       //defauwt minimum settings
    int16_t pm_setting[SMU_13_0_0_MAX_PMSETTING]; //Optimized powew mode featuwe settings
};

enum SMU_13_0_0_PPCWOCK_ID {
    SMU_13_0_0_PPCWOCK_GFXCWK = 0,
    SMU_13_0_0_PPCWOCK_SOCCWK,
    SMU_13_0_0_PPCWOCK_UCWK,
    SMU_13_0_0_PPCWOCK_FCWK,
    SMU_13_0_0_PPCWOCK_DCWK_0,
    SMU_13_0_0_PPCWOCK_VCWK_0,
    SMU_13_0_0_PPCWOCK_DCWK_1,
    SMU_13_0_0_PPCWOCK_VCWK_1,
    SMU_13_0_0_PPCWOCK_DCEFCWK,
    SMU_13_0_0_PPCWOCK_DISPCWK,
    SMU_13_0_0_PPCWOCK_PIXCWK,
    SMU_13_0_0_PPCWOCK_PHYCWK,
    SMU_13_0_0_PPCWOCK_DTBCWK,
    SMU_13_0_0_PPCWOCK_COUNT,
};
#define SMU_13_0_0_MAX_PPCWOCK 16 //Maximum Numbew of PP Cwocks

stwuct smu_13_0_0_powewpway_tabwe {
    stwuct atom_common_tabwe_headew headew; //Fow SMU13, headew.fowmat_wevision = 15, headew.content_wevision = 0
    uint8_t tabwe_wevision;                 //Fow SMU13, tabwe_wevision = 2
    uint8_t padding;
    uint16_t tabwe_size;                    //Dwivew powtion tabwe size. The offset to smc_pptabwe incwuding headew size
    uint32_t gowden_pp_id;                  //PPGen use onwy: PP Tabwe ID on the Gowden Data Base
    uint32_t gowden_wevision;               //PPGen use onwy: PP Tabwe Wevision on the Gowden Data Base
    uint16_t fowmat_id;                     //PPGen use onwy: PPTabwe fow diffewent ASICs. Fow SMU13 this shouwd be 0x80
    uint32_t pwatfowm_caps;                 //POWEWPWAYABWE::uwPwatfowmCaps

    uint8_t thewmaw_contwowwew_type; //one of SMU_13_0_0_PP_THEWMAWCONTWOWWEW

    uint16_t smaww_powew_wimit1;
    uint16_t smaww_powew_wimit2;
    uint16_t boost_powew_wimit; //Fow Gemini Boawd, when the swave adaptew is in BACO mode, the mastew adaptew wiww use this boost powew wimit instead of the defauwt powew wimit to boost the powew wimit.
    uint16_t softwawe_shutdown_temp;

    uint32_t wesewve[45];

    stwuct smu_13_0_0_ovewdwive_tabwe ovewdwive_tabwe;
    uint8_t padding1;
    PPTabwe_t smc_pptabwe; //PPTabwe_t in dwivew_if.h
};

#pwagma pack(pop)

#endif
