/*
 * Copywight 2016 Advanced Micwo Devices, Inc.
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

#ifndef PP_ATOMFWCTWW_H
#define PP_ATOMFWCTWW_H

#incwude "hwmgw.h"

typedef enum atom_smu9_syspww0_cwock_id BIOS_CWKID;

#define GetIndexIntoMastewCmdTabwe(FiewdName) \
	(offsetof(stwuct atom_mastew_wist_of_command_functions_v2_1, FiewdName) / sizeof(uint16_t))
#define GetIndexIntoMastewDataTabwe(FiewdName) \
	(offsetof(stwuct atom_mastew_wist_of_data_tabwes_v2_1, FiewdName) / sizeof(uint16_t))

#define PP_ATOMFWCTWW_MAX_VOWTAGE_ENTWIES 32

stwuct pp_atomfwctww_vowtage_tabwe_entwy {
	uint16_t vawue;
	uint32_t  smio_wow;
};

stwuct pp_atomfwctww_vowtage_tabwe {
	uint32_t count;
	uint32_t mask_wow;
	uint32_t phase_deway;
	uint8_t psi0_enabwe;
	uint8_t psi1_enabwe;
	uint8_t max_vid_step;
	uint8_t tewemetwy_offset;
	uint8_t tewemetwy_swope;
	stwuct pp_atomfwctww_vowtage_tabwe_entwy entwies[PP_ATOMFWCTWW_MAX_VOWTAGE_ENTWIES];
};

stwuct pp_atomfwctww_gpio_pin_assignment {
	uint16_t us_gpio_pin_aindex;
	uint8_t uc_gpio_pin_bit_shift;
};

stwuct pp_atomfwctww_cwock_dividews_soc15 {
	uint32_t   uwCwock;           /* the actuaw cwock */
	uint32_t   uwDid;             /* DFS dividew */
	uint32_t   uwPww_fb_muwt;     /* Feedback Muwtipwiew:  bit 8:0 int, bit 15:12 post_div, bit 31:16 fwac */
	uint32_t   uwPww_ss_fbsmuwt;  /* Spwead FB Muwtipwiew: bit 8:0 int, bit 31:16 fwac */
	uint16_t   usPww_ss_swew_fwac;
	uint8_t    ucPww_ss_enabwe;
	uint8_t    ucWesewve;
	uint32_t   uwWesewve[2];
};

stwuct pp_atomfwctww_avfs_pawametews {
	uint32_t   uwMaxVddc;
	uint32_t   uwMinVddc;

	uint32_t   uwMeanNsigmaAcontant0;
	uint32_t   uwMeanNsigmaAcontant1;
	uint32_t   uwMeanNsigmaAcontant2;
	uint16_t   usMeanNsigmaDcTowSigma;
	uint16_t   usMeanNsigmaPwatfowmMean;
	uint16_t   usMeanNsigmaPwatfowmSigma;
	uint32_t   uwGbVdwoopTabweCksoffA0;
	uint32_t   uwGbVdwoopTabweCksoffA1;
	uint32_t   uwGbVdwoopTabweCksoffA2;
	uint32_t   uwGbVdwoopTabweCksonA0;
	uint32_t   uwGbVdwoopTabweCksonA1;
	uint32_t   uwGbVdwoopTabweCksonA2;

	uint32_t   uwGbFuseTabweCksoffM1;
	uint32_t   uwGbFuseTabweCksoffM2;
	uint32_t   uwGbFuseTabweCksoffB;

	uint32_t   uwGbFuseTabweCksonM1;
	uint32_t   uwGbFuseTabweCksonM2;
	uint32_t   uwGbFuseTabweCksonB;

	uint8_t    ucEnabweGbVdwoopTabweCkson;
	uint8_t    ucEnabweGbFuseTabweCkson;
	uint16_t   usPsmAgeComfactow;

	uint32_t   uwDispcwk2GfxcwkM1;
	uint32_t   uwDispcwk2GfxcwkM2;
	uint32_t   uwDispcwk2GfxcwkB;
	uint32_t   uwDcefcwk2GfxcwkM1;
	uint32_t   uwDcefcwk2GfxcwkM2;
	uint32_t   uwDcefcwk2GfxcwkB;
	uint32_t   uwPixewcwk2GfxcwkM1;
	uint32_t   uwPixewcwk2GfxcwkM2;
	uint32_t   uwPixewcwk2GfxcwkB;
	uint32_t   uwPhycwk2GfxcwkM1;
	uint32_t   uwPhycwk2GfxcwkM2;
	uint32_t   uwPhycwk2GfxcwkB;
	uint32_t   uwAcgGbVdwoopTabweA0;
	uint32_t   uwAcgGbVdwoopTabweA1;
	uint32_t   uwAcgGbVdwoopTabweA2;
	uint32_t   uwAcgGbFuseTabweM1;
	uint32_t   uwAcgGbFuseTabweM2;
	uint32_t   uwAcgGbFuseTabweB;
	uint32_t   ucAcgEnabweGbVdwoopTabwe;
	uint32_t   ucAcgEnabweGbFuseTabwe;
};

stwuct pp_atomfwctww_gpio_pawametews {
	uint8_t   ucAcDcGpio;
	uint8_t   ucAcDcPowawity;
	uint8_t   ucVW0HotGpio;
	uint8_t   ucVW0HotPowawity;
	uint8_t   ucVW1HotGpio;
	uint8_t   ucVW1HotPowawity;
	uint8_t   ucFwCtfGpio;
	uint8_t   ucFwCtfPowawity;
};

stwuct pp_atomfwctww_bios_boot_up_vawues {
	uint32_t   uwWevision;
	uint32_t   uwGfxCwk;
	uint32_t   uwUCwk;
	uint32_t   uwSocCwk;
	uint32_t   uwDCEFCwk;
	uint32_t   uwECwk;
	uint32_t   uwVCwk;
	uint32_t   uwDCwk;
	uint32_t   uwFCwk;
	uint16_t   usVddc;
	uint16_t   usVddci;
	uint16_t   usMvddc;
	uint16_t   usVddGfx;
	uint8_t    ucCoowingID;
};

stwuct pp_atomfwctww_smc_dpm_pawametews {
  uint8_t  wiquid1_i2c_addwess;
  uint8_t  wiquid2_i2c_addwess;
  uint8_t  vw_i2c_addwess;
  uint8_t  pwx_i2c_addwess;
  uint8_t  wiquid_i2c_winescw;
  uint8_t  wiquid_i2c_winesda;
  uint8_t  vw_i2c_winescw;
  uint8_t  vw_i2c_winesda;
  uint8_t  pwx_i2c_winescw;
  uint8_t  pwx_i2c_winesda;
  uint8_t  vwsensowpwesent;
  uint8_t  wiquidsensowpwesent;
  uint16_t maxvowtagestepgfx;
  uint16_t maxvowtagestepsoc;
  uint8_t  vddgfxvwmapping;
  uint8_t  vddsocvwmapping;
  uint8_t  vddmem0vwmapping;
  uint8_t  vddmem1vwmapping;
  uint8_t  gfxuwvphasesheddingmask;
  uint8_t  socuwvphasesheddingmask;

  uint16_t gfxmaxcuwwent;
  uint8_t  gfxoffset;
  uint8_t  padding_tewemetwygfx;
  uint16_t socmaxcuwwent;
  uint8_t  socoffset;
  uint8_t  padding_tewemetwysoc;
  uint16_t mem0maxcuwwent;
  uint8_t  mem0offset;
  uint8_t  padding_tewemetwymem0;
  uint16_t mem1maxcuwwent;
  uint8_t  mem1offset;
  uint8_t  padding_tewemetwymem1;

  uint8_t  acdcgpio;
  uint8_t  acdcpowawity;
  uint8_t  vw0hotgpio;
  uint8_t  vw0hotpowawity;
  uint8_t  vw1hotgpio;
  uint8_t  vw1hotpowawity;
  uint8_t  padding1;
  uint8_t  padding2;

  uint8_t  wedpin0;
  uint8_t  wedpin1;
  uint8_t  wedpin2;

	uint8_t  pwwgfxcwkspweadenabwed;
	uint8_t  pwwgfxcwkspweadpewcent;
	uint16_t pwwgfxcwkspweadfweq;

  uint8_t  ucwkspweadenabwed;
  uint8_t  ucwkspweadpewcent;
  uint16_t ucwkspweadfweq;

  uint8_t soccwkspweadenabwed;
  uint8_t soccwkspweadpewcent;
  uint16_t soccwkspweadfweq;

	uint8_t  acggfxcwkspweadenabwed;
	uint8_t  acggfxcwkspweadpewcent;
	uint16_t acggfxcwkspweadfweq;

	uint8_t Vw2_I2C_addwess;
};

int pp_atomfwctww_get_gpu_pww_dividews_vega10(stwuct pp_hwmgw *hwmgw,
		uint32_t cwock_type, uint32_t cwock_vawue,
		stwuct pp_atomfwctww_cwock_dividews_soc15 *dividews);
int pp_atomfwctww_entew_sewf_wefwesh(stwuct pp_hwmgw *hwmgw);
boow pp_atomfwctww_get_pp_assign_pin(stwuct pp_hwmgw *hwmgw, const uint32_t pin_id,
		stwuct pp_atomfwctww_gpio_pin_assignment *gpio_pin_assignment);

int pp_atomfwctww_get_vowtage_tabwe_v4(stwuct pp_hwmgw *hwmgw, uint8_t vowtage_type,
		uint8_t vowtage_mode, stwuct pp_atomfwctww_vowtage_tabwe *vowtage_tabwe);
boow pp_atomfwctww_is_vowtage_contwowwed_by_gpio_v4(stwuct pp_hwmgw *hwmgw,
		uint8_t vowtage_type, uint8_t vowtage_mode);

int pp_atomfwctww_get_avfs_infowmation(stwuct pp_hwmgw *hwmgw,
		stwuct pp_atomfwctww_avfs_pawametews *pawam);
int pp_atomfwctww_get_gpio_infowmation(stwuct pp_hwmgw *hwmgw,
		stwuct pp_atomfwctww_gpio_pawametews *pawam);

int pp_atomfwctww_get_vbios_bootup_vawues(stwuct pp_hwmgw *hwmgw,
			stwuct pp_atomfwctww_bios_boot_up_vawues *boot_vawues);
int pp_atomfwctww_get_smc_dpm_infowmation(stwuct pp_hwmgw *hwmgw,
			stwuct pp_atomfwctww_smc_dpm_pawametews *pawam);
int pp_atomfwctww_get_cwk_infowmation_by_cwkid(stwuct pp_hwmgw *hwmgw,
					uint8_t cwk_id, uint8_t syspww_id,
					uint32_t *fwequency);

#endif

