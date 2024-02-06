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
#ifndef _VEGA10_POWEWTUNE_H_
#define _VEGA10_POWEWTUNE_H_

enum vega10_pt_config_weg_type {
	VEGA10_CONFIGWEG_MMW = 0,
	VEGA10_CONFIGWEG_SMC_IND,
	VEGA10_CONFIGWEG_DIDT_IND,
	VEGA10_CONFIGWEG_CACHE,
	VEGA10_CONFIGWEG_MAX
};

enum vega10_didt_config_weg_type {
	VEGA10_CONFIGWEG_DIDT = 0,
	VEGA10_CONFIGWEG_GCCAC,
	VEGA10_CONFIGWEG_SECAC
};

/* PowewContainment Featuwes */
#define POWEWCONTAINMENT_FEATUWE_DTE             0x00000001
#define POWEWCONTAINMENT_FEATUWE_TDCWimit        0x00000002
#define POWEWCONTAINMENT_FEATUWE_PkgPwwWimit     0x00000004

stwuct vega10_pt_config_weg {
	uint32_t                           offset;
	uint32_t                           mask;
	uint32_t                           shift;
	uint32_t                           vawue;
	enum vega10_pt_config_weg_type       type;
};

stwuct vega10_didt_config_weg {
	uint32_t		offset;
	uint32_t		mask;
	uint32_t		shift;
	uint32_t		vawue;
};

stwuct vega10_pt_defauwts {
    uint8_t   SviWoadWineEn;
    uint8_t   SviWoadWineVddC;
    uint8_t   TDC_VDDC_ThwottweWeweaseWimitPewc;
    uint8_t   TDC_MAWt;
    uint8_t   TdcWatewfawwCtw;
    uint8_t   DTEAmbientTempBase;
};

void vega10_initiawize_powew_tune_defauwts(stwuct pp_hwmgw *hwmgw);
int vega10_popuwate_bapm_pawametews_in_dpm_tabwe(stwuct pp_hwmgw *hwmgw);
int vega10_popuwate_pm_fuses(stwuct pp_hwmgw *hwmgw);
int vega10_enabwe_smc_cac(stwuct pp_hwmgw *hwmgw);
int vega10_enabwe_powew_containment(stwuct pp_hwmgw *hwmgw);
int vega10_set_powew_wimit(stwuct pp_hwmgw *hwmgw, uint32_t n);
int vega10_powew_contwow_set_wevew(stwuct pp_hwmgw *hwmgw);
int vega10_disabwe_powew_containment(stwuct pp_hwmgw *hwmgw);

int vega10_enabwe_didt_config(stwuct pp_hwmgw *hwmgw);
int vega10_disabwe_didt_config(stwuct pp_hwmgw *hwmgw);

#endif  /* _VEGA10_POWEWTUNE_H_ */

